"""autogenerated by genmsg_py from readings.msg. Do not edit."""
import roslib.message
import struct


class readings(roslib.message.Message):
  _md5sum = "37e95a4fa8f8c129aebc2b4aedd99f4d"
  _type = "odorsimulation/readings"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64 r0
float64 r1
float64 r2
float64 r3
float64 r4

"""
  __slots__ = ['r0','r1','r2','r3','r4']
  _slot_types = ['float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       r0,r1,r2,r3,r4
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(readings, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.r0 is None:
        self.r0 = 0.
      if self.r1 is None:
        self.r1 = 0.
      if self.r2 is None:
        self.r2 = 0.
      if self.r3 is None:
        self.r3 = 0.
      if self.r4 is None:
        self.r4 = 0.
    else:
      self.r0 = 0.
      self.r1 = 0.
      self.r2 = 0.
      self.r3 = 0.
      self.r4 = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self
      buff.write(_struct_5d.pack(_x.r0, _x.r1, _x.r2, _x.r3, _x.r4))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.r0, _x.r1, _x.r2, _x.r3, _x.r4,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self
      buff.write(_struct_5d.pack(_x.r0, _x.r1, _x.r2, _x.r3, _x.r4))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.r0, _x.r1, _x.r2, _x.r3, _x.r4,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_5d = struct.Struct("<5d")
