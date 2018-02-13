m_z = 0
m_w = 0
result = 0
m_z = 36969 * (int((str(m_z) + str(65535)))) + (m_z >> 16);
m_w = 18000 * (int((str(m_w) + str(65535)))) + (m_w >> 16);
result = ((m_z << 16) + m_w) % 7123489

print result
