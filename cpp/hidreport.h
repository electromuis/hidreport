#pragma once

#include "hidapi.h"

class HRDevice {
public:
	HRDevice(int vendorId, int deviceId);
	HRDevice(hid_device* handle);
	hid_device* GetHandle();
	
	template <class T>
	T get_report()
	{
		T report;
		if(!report.from_device(*this))
			throw "Getting report failed";
		
		return report;
	}
	
	template <class T>
	bool send_report(T report)
	{
		return report.to_device(*this);
	}
	
protected:
	hid_device* handle;
};

enum HRFieldType {
	HRFieldType_uint8;
	HRFieldType_uint16;
	HRFieldType_uint32;
};

class HRMappingRule {
public:
	HRMappingRule(void* field, HRFieldType type, int count = 0, int bits = 0);
	void from_bytes(byte* bytes);
	void to_bytes(byte* buffer);
	
protected:
	void* field;
	HRFieldType type;
	int count = 0;
	int bits = 0;
};

class HRReport {
public:
	HRReport(int reportId = -1);

	virtual void load_mapping() = 0;
	int get_report_size();
	
	void from_bytes(byte* bytes);
	void to_bytes(byte* buffer);
	
	virtual bool get_report_bytes(HRDevice& device, byte* buffer);
	virtual bool send_report_bytes(HRDevice& device, byte* bytes);
	
	bool from_device(HRDevice& device);
	bool to_device(HRDevice& device);
	
protected:
	int reportId = -1;
}