After playing around with usb and hid for a while I found it a great way for modenr usb device communcation.
Thanks to hidapi, implementing is verry doable. Something I missed though is a way to easily map reports back and forht.
That is why I decided to write something reusable fot this purpose.


This library represents a base implementation for USB communcation based on HID reports.

Each included language has a directly includable with the same features.

The features this proceject wants to provide is:
 - Mapping classes to hid reports
 - Finding / connecting hid devices
 - Sending receiving the reports based on the defined classes
 
The classes included are:

HRDevice:
	- Properties:
		- handle: The native usbhid connection instance
	- Methods:
		- HRDevice(vendorId, deviceId): Connect to the first device matching the provided vendor and device ID
		- HRDevice(handle): Create a HRDevice from an existing handle
		
		- get_report(report): Read / Return an HRReport
		- send_report(report): Send an HRReport

HRMapping:
	- Properties:
		- field: What variable to store this field in (c++ has pointers, otherwise a string)
		- type: Type of the data to encode / decode (float, int16, ...)
		- count: Indicates a list when the value is higher then 0
		- bits: A list of booleans stored in a integer value

HRReport
	- Properties:
		- reportId: The ID of the feature report, -1 if not relevant
		- fields: Array of mapping specification rules
	
	- Methods:
		- load_mapping(): Setup the binary mapping
		- get_report_size(): Returns the calculated report size in bytes
		
		- from_bytes(bytes): Populates the report from an array of bytes
		- to_bytes(): Maps the report data back into the byte format
		
		- get_report_bytes(device): Fetch the report bytes from the device
		- send_report_bytes(device, bytes): Send the report bytes to the device
		
		- from_device(device): Populates the report from a connected HRDevice through get_report() -> from_bytes()
		- to_device(device): Sends the report to a connected HRDevice through to_bytes() -> send_report()