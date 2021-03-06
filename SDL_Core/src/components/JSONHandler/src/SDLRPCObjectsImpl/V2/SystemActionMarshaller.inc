/* Copyright (c) 2013 Ford Motor Company */

/* C++ code produced by gperf version 3.0.3 */
/* Command-line: gperf --output-file=./src/components/JSONHandler/src/SDLRPCObjectsImpl/V2/SystemActionMarshaller.inc ./src/components/JSONHandler/src/SDLRPCObjectsImpl/V2/SystemActionMarshaller.gp  */
/* Computed positions: -k'' */


#define TOTAL_KEYWORDS 3
#define MIN_WORD_LENGTH 11
#define MAX_WORD_LENGTH 14
#define MIN_HASH_VALUE 11
#define MAX_HASH_VALUE 14
/* maximum key range = 4, duplicates = 0 */

class SystemAction_intHash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const struct NsSmartDeviceLinkRPCV2::PerfectHashTable *getPointer (const char *str, unsigned int len);
};

inline /*ARGSUSED*/
unsigned int
SystemAction_intHash::hash (register const char *str, register unsigned int len)
{
  return len;
}

const struct NsSmartDeviceLinkRPCV2::PerfectHashTable *
SystemAction_intHash::getPointer (register const char *str, register unsigned int len)
{
  static const unsigned char lengthtable[] =
    {
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11, 12,  0,
      14
    };
  static const struct NsSmartDeviceLinkRPCV2::PerfectHashTable wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
#line 18 "./src/components/JSONHandler/src/SDLRPCObjectsImpl/V2/SystemActionMarshaller.gp"
      {"STEAL_FOCUS",1},
#line 19 "./src/components/JSONHandler/src/SDLRPCObjectsImpl/V2/SystemActionMarshaller.gp"
      {"KEEP_CONTEXT",2},
      {""},
#line 17 "./src/components/JSONHandler/src/SDLRPCObjectsImpl/V2/SystemActionMarshaller.gp"
      {"DEFAULT_ACTION",0}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        if (len == lengthtable[key])
          {
            register const char *s = wordlist[key].name;

            if (*str == *s && !memcmp (str + 1, s + 1, len - 1))
              return &wordlist[key];
          }
    }
  return 0;
}
