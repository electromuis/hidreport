import struct

class HRDevice:
    handle = None
    
    def __init__(self, deviceId = None, vendorId = None, handle = None):
        if handle:
            self.handle = handle
            return
    

class HRMappingRule:
    field = ''
    type = ''
    count = 0
    bits = 0
    
    def __init__(self, field, type, count=0, bits=0):
        self.field = field
        self.type = type
        self.count = count
        self.bits = bits

class HRReport:
    reportId = -1
    fields = []
    structMapping = ''
    reportSize = -1
    
    def __init__(self):
        self.load_mapping()
            
    def load_mapping(self):
        self.structMapping = '<'
        for f in self.fields:
            if 'count' in f:
                structMapping += str(f['count'])
            structMapping += f['type']
        
        self.reportSize = struct.calcsize(report_format)
    
    def get_report_size(self):
        return self.reportSize
            
    def from_bytes(self, bytes):
        pos = 0
        for f in self.fields:
            if 'count' in f:
                setattr(
                    self,
                    f['name'],
                    list(parsed_report[pos:pos+f['count']])
                )
                pos += f['count']
            elif 'bits' in f:
                bits = []
                for b in range(f['bits']):
                    bits.append((parsed_report[pos] & 1 << b) > 0)
                setattr(self, f['name'], bits)
                pos += 1
            else:
                setattr(self, f['name'], parsed_report[pos])
                pos += 1
                
    def get_report_bytes(self, device):
        