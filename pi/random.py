# private static uint GetUint()
# {
#     m_z = 36969 * (m_z & 65535) + (m_z >> 16);
#     m_w = 18000 * (m_w & 65535) + (m_w >> 16);
#     return (m_z << 16) + m_w;
# }


def getUint():
  m_z = 0
  m_w = 0

  m_z = 36969 * (str(m_z) + str(65535)) + (m_z >> 16)
  m_w = 18000 * (str(m_w) + str(65535)) + (m_w >> 16)
  return (m_z << 16) + m_w

getUint()