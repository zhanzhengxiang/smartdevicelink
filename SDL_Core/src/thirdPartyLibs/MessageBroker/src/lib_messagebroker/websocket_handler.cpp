/**
 * \file websocket_handler.cpp
 * \brief WebSocket Handler.
 * \author AKara
 */

#include <cstdio>

#include <cstring>
#include <sstream>
#include <netinet/in.h>

#ifdef _WIN32
#include <winsock2.h>
#endif//_WIN32

#include "websocket_handler.hpp"

#include "libMBDebugHelper.h"
#include "md5.h"

#include <openssl/sha.h>


namespace NsMessageBroker 
{
   int CWebSocketHandler::parseWebSocketData(char* Buffer, unsigned int& b_size)
   {
      // Please see RFC6455 standard protocol specification:
      //http://tools.ietf.org/html/rfc6455
      // Chapter 5.2
      DBG_MSG(("CWebSocketHandler::parseWebSocketData()b_size = %d\n", b_size));
      char* recBuffer = Buffer;
      unsigned int parsedBufferPosition = 0;
      unsigned int nextBufferPosition = 0;
      while (nextBufferPosition < b_size)
      {
         DBG_MSG(("CWebSocketHandler::parseWebSocketData()recBuffer[0] = %s\n", std::string(recBuffer, 1).c_str()));
         bool fin = (recBuffer[0] & 0x80) == 0x80;

         bool rsv1 = (recBuffer[0] & 0x40) == 0x40;
         bool rsv2 = (recBuffer[0] & 0x20) == 0x20;
         bool rsv3 = (recBuffer[0] & 0x10) == 0x10;

         unsigned char opCode = ((recBuffer[0] & 0x08) | (recBuffer[0] & 0x04) | (recBuffer[0] & 0x02) | (recBuffer[0] & 0x01));

         bool mask = (recBuffer[1] & 0x80) == 0x80;

         unsigned char payload = 
            (unsigned char)((recBuffer[1] & 0x40) | (recBuffer[1] & 0x20) | (recBuffer[1] & 0x10) |
            (recBuffer[1] & 0x08) | (recBuffer[1] & 0x04) | (recBuffer[1] & 0x02) | (recBuffer[1] & 0x01));
         unsigned long length = 0;
         DBG_MSG(("CWebSocketHandler::parseWebSocketData()fin:%d; rsv1:%d; rsv2:%d; rsv3:%d; opCode:%d; mask:%d; payload:%d\n", fin, rsv1, rsv2, rsv3, opCode, mask, payload));

         unsigned char position = 2; // current buffer position

         switch(payload) {
            case 126:
               {
                  length = (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  break;
               }
            case 127:
               {
                  length = (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  length <<=8;
                  length |= (unsigned char)recBuffer[position++];
                  break;
               }
            default:
               {
                  length = payload;
                  break;
               }
         }

         if (mask)
         {
            unsigned char maskKeys[4];
            maskKeys[0] = recBuffer[position++];
            maskKeys[1] = recBuffer[position++];
            maskKeys[2] = recBuffer[position++];
            maskKeys[3] = recBuffer[position++];
            DBG_MSG(("CWebSocketHandler::parseWebSocketData()maskKeys[0]:0x%02X; maskKeys[1]:0x%02X; maskKeys[2]:0x%02X; maskKeys[3]:0x%02X\n"
                     , maskKeys[0], maskKeys[1], maskKeys[2], maskKeys[3]));
            for( unsigned long i = position; i < position+length; i++)
            {
               recBuffer[i] = recBuffer[i] ^ maskKeys[(i-position)%4];
            }
         }
         DBG_MSG(("CWebSocketHandler::parseWebSocketData()length:%d; position:%d\n", (int)length, position));
         for( unsigned long i = position; i < position+length; i++)
         {
            Buffer[parsedBufferPosition++] = recBuffer[i];
         }
         nextBufferPosition += position+length;
         recBuffer += position+length;
         DBG_MSG(("CWebSocketHandler::parseWebSocketData()nextBufferPosition = %d; parsedBufferPosition = %d\n", nextBufferPosition, parsedBufferPosition));
         std::string message = std::string(Buffer, b_size);
      }
      b_size = parsedBufferPosition;
      return b_size;
   }

   int CWebSocketHandler::prepareWebSocketDataHeader(char* Buffer, unsigned long b_size)
   {
      unsigned long headerLength = 2;
      unsigned char payload;
      if (b_size >= 65536)
      {
         headerLength += 8;
         payload = 127;
      } else if(b_size >= 126)
      {
         headerLength += 2;
         payload = 126;
      } else
      {
         payload = b_size;
      }
      memset(Buffer, 0, headerLength);
      Buffer[0] = (char)0x80 | 0x01;
      Buffer[1] = (char)(Buffer[1] | (payload & 0x40) | (payload & 0x20) |
                                     (payload & 0x10) | (payload & 0x08) |
                                     (payload & 0x04) | (payload & 0x02) |
                                     (payload & 0x01));

      if (payload == 126)
      {
         Buffer[2] = (char)(b_size>>8);
         Buffer[3] = (char)b_size;
      } else if (payload == 127)
      {
         Buffer[9] = (char)(b_size);
         Buffer[8] = (char)(b_size>=8);
         Buffer[7] = (char)(b_size>=8);
         Buffer[6] = (char)(b_size>=8);
         Buffer[5] = (char)(b_size>=8);
         Buffer[4] = (char)(b_size>=8);
         Buffer[3] = (char)(b_size>=8);
         Buffer[2] = (char)(b_size>=8);
      }
      return headerLength;
}

   void CWebSocketHandler::handshake_0405(std::string &key)
   {
      static const char *websocket_magic_guid_04 =
                   "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
      char accept_buf[MAX_WEBSOCKET_04_KEY_LEN + 37];
      unsigned char hash[20] = {0xb3, 0x7a, 0x4f, 0x2c, 0xc0, 0x62, 0x4f, 0x16, 0x90, 0xf6, 0x46, 0x06, 0xcf, 0x38, 0x59, 0x45, 0xb2, 0xbe, 0xc4, 0xea};
      int accept_len;

      strcpy(accept_buf, key.c_str());
      strcpy(accept_buf + key.length(), websocket_magic_guid_04);

      SHA1((unsigned char *)accept_buf, key.length() + strlen(websocket_magic_guid_04), hash);

      accept_len = lws_b64_encode_string((char *)hash, 20, accept_buf, sizeof accept_buf);
      if (accept_len < 0)
      {
         fprintf(stderr, "Base64 encoded hash too long\n");
      }
      fprintf(stderr, "accept_buf: %s\n", accept_buf);
      key = accept_buf;
   }

   unsigned char * CWebSocketHandler::SHA1(const unsigned char *d, size_t n, unsigned char *md)
   {
      SHA_CTX ctx;

      SHA1_Init(&ctx);
      SHA1_Update(&ctx, d, n);
      SHA1_Final((unsigned char *)md, &ctx);

      return md;
   }

   int CWebSocketHandler::lws_b64_encode_string(const char *in, int in_len, char *out, int out_size)
   {
      unsigned char triple[3];
      int i;
      int len;
      int line = 0;
      int done = 0;

      while (in_len)
      {
         len = 0;
         for (i = 0; i < 3; i++)
         {
            if (in_len)
            {
               triple[i] = *in++;
               len++;
               in_len--;
            } else
               triple[i] = 0;
         }
         if (len)
         {

            if (done + 4 >= out_size)
               return -1;

            *out++ = encode[triple[0] >> 2];
            *out++ = encode[((triple[0] & 0x03) << 4) |
                          ((triple[1] & 0xf0) >> 4)];
            *out++ = (len > 1 ? encode[((triple[1] & 0x0f) << 2) |
                       ((triple[2] & 0xc0) >> 6)] : '=');
            *out++ = (len > 2 ? encode[triple[2] & 0x3f] : '=');

            done += 4;
            line += 4;
         }
         if (line >= 72)
         {

            if (done + 2 >= out_size)
               return -1;

            *out++ = '\r';
            *out++ = '\n';
            done += 2;
            line = 0;
         }
      }

      if (done + 1 >= out_size)
         return -1;

      *out++ = '\0';

      return done;
   }

   /*
    * returns length of decoded string in out, or -1 if out was too small
    * according to out_size
    */

   int CWebSocketHandler::lws_b64_decode_string(const char *in, char *out, int out_size)
   {
      int len;
      int i;
      int done = 0;
      unsigned char v;
      unsigned char quad[4];

      while (*in)
      {

         len = 0;
         for (i = 0; i < 4 && *in; i++)
         {

            v = 0;
            while (*in && !v)
            {

               v = *in++;
               v = (v < 43 || v > 122) ? 0 : decode[v - 43];
               if (v)
                  v = (v == '$') ? 0 : v - 61;
               if (*in)
               {
                  len++;
                  if (v)
                     quad[i] = v - 1;
               } else
                  quad[i] = 0;
            }
         }
         if (!len)
            continue;

         if (out_size < (done + len - 1))
            /* out buffer is too small */
            return -1;

         if (len >= 2)
            *out++ = quad[0] << 2 | quad[1] >> 4;
         if (len >= 3)
            *out++ = quad[1] << 4 | quad[2] >> 2;
         if (len >= 4)
            *out++ = ((quad[2] << 6) & 0xc0) | quad[3];

         done += len - 1;
      }

      if (done + 1 >= out_size)
         return -1;

      *out++ = '\0';

      return done;
   }

   int CWebSocketHandler::lws_b64_selftest(void)
   {
      char buf[64];
      int n;
      unsigned int test;
      static const char *plaintext[] = {"sanity check base 64"};
      static const char *coded[] = {"c2FuaXR5IGNoZWNrIGJhc2UgNjQ="};

      for (test = 0; test < sizeof plaintext / sizeof(plaintext[0]); test++)
      {

         buf[sizeof(buf) - 1] = '\0';
         n = lws_b64_encode_string(plaintext[test],
                     strlen(plaintext[test]), buf, sizeof buf);
         if (n != (int)strlen(coded[test]) || strcmp(buf, coded[test]))
         {
            fprintf(stderr, "Failed lws_b64 encode selftest "
                     "%d result '%s' %d\n", test, buf, n);
            return -1;
         }

         buf[sizeof(buf) - 1] = '\0';
         n = lws_b64_decode_string(coded[test], buf, sizeof buf);
         if (n != (int)strlen(plaintext[test]) ||
                      strcmp(buf, plaintext[test]))
         {
            fprintf(stderr, "Failed lws_b64 decode selftest "
                     "%d result '%s' %d\n", test, buf, n);
            return -1;
         }
      }

      return 0;
   }
   
   rawBytes CWebSocketHandler::handshake_hybi00(const std::string &key1, const std::string &key2, const rawBytes &key3)
   {
      if (key3.size() < 8)
      {
         DBG_MSG_ERROR(("key3's size is %d, less than 8 bytes\n", key3.size()));
         return rawBytes();
      }
      
      unsigned long number1 = extractNumber(key1);
      unsigned long number2 = extractNumber(key2);
      DBG_MSG(("number1 is %ld, number2 is %ld\n", number1, number2));
      
      if ((number1 == 0) || (number2 == 0))
      {
         return rawBytes();
      }
      
      // represent the numbers in big-endian format (network-byte order)
      unsigned long bigEndianNumber1 = htonl(number1);
      unsigned long bigEndianNumber2 = htonl(number2);
      
      // the temporary key consists of bytes of the first and second numbers
      // and the key3
      rawBytes key(8);
      memcpy(&key[0], &bigEndianNumber1, 4);
      memcpy(&key[4], &bigEndianNumber2, 4);
      key.insert(key.end(), key3.begin(), key3.begin() + 8);
      
      MD5 md5(std::string(key.begin(), key.end()));
      char digest[16];
      md5.getdigest(digest);
      rawBytes resultBytes(&digest[0], &digest[16]);
      
      return resultBytes;
   }
   
   unsigned long CWebSocketHandler::extractNumber(const std::string &key) const
   {
      // leave digits only
      // and count the number of spaces in the key
      std::string keyDigits;
      int spacesCountKey = 0;
      for (unsigned int index = 0; index < key.length(); ++index)
      {
         char keyChar = key[index];
         if (keyChar == ' ')
         {
            ++spacesCountKey;
         }
         else if (isdigit(keyChar))
         {
            keyDigits += keyChar;
         }
      }
      
      unsigned long result = 0;
      
      // convert string to number
      long long numberKey;
      if (std::stringstream(keyDigits) >> numberKey)
      {
         if (spacesCountKey != 0)
         {
            if (numberKey % spacesCountKey == 0)
            {
               // divide the number by the count
               result = numberKey / spacesCountKey;
            }
            else
            {
               // key is not an integral multiple of spaces count
            }
         }
         else
         {
            // the denominator is 0
         }
      }
      else
      {
         // couldn't convert
      }
      
      return result;
   }
   
} /* namespace NsMessageBroker */

