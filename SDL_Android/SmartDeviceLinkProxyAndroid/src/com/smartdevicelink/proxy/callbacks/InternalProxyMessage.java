//
// Copyright (c) 2013 Ford Motor Company
//
package com.smartdevicelink.proxy.callbacks;

public class InternalProxyMessage {
	private String _functionName;
	
	public InternalProxyMessage(String functionName) {
		this._functionName = functionName;
	}
	
	public String getFunctionName() {
		return _functionName;
	}
}
