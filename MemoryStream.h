#pragma once
#include <memory.h>

class MemoryStream
{
private:
   char* m_pData;
   size_t m_index;
   size_t m_length;
public:

   enum Status
   {
      Success = 0,
      EndOfStream
   };

   MemoryStream(size_t length, void* data)
      :m_index(0)
   {
      m_pData = new char[length];
      memcpy(m_pData, data, length);
      m_length = length;
   }

   Status getChar(char &result)
   {
      if (m_index == m_length)
         return EndOfStream;
      result = m_pData[m_index++];
      return Success;
   }

   Status reset()
   {
      m_index = 0;
      return Success;
   }
};

