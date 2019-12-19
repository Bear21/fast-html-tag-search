#pragma once
#include <cstdio>
#include <string>
#include <iostream>
#include "MemoryStream.h"


class TagFinder
{
private:
   MemoryStream& m_Stream;
   bool m_Output;
   
   char m_Temp[8192];
public:
   TagFinder(MemoryStream& stream, bool writeOutput)
      :m_Stream(stream)
      , m_Output(writeOutput)
   {
   }

   void Read()
   {
      char c;
      while (m_Stream.getChar(c) == MemoryStream::Success) {
         switch (c)
         {
         case '<':
            FindEnd();
            break;
         default:
            break;
         }
      }
   }

   void FindEnd()
   {
      size_t length = 0;
      char c;
      while (m_Stream.getChar(c) == MemoryStream::Success) {
         m_Temp[length++] = c;

         switch (c) {
         case '<':
            return;
         case '>':
            m_Temp[length] = 0;
            //std::cout << "Tag: " << m_Temp << std::endl;
            if (m_Output)
               printf("Tag: %s\n", m_Temp);
            return;
         case '/':
         {
            int foundLength = length;
            FindChar('>', length);
            m_Temp[length] = 0;
            if (m_Output)
               printf("%s%s\n", ((foundLength == 1) ? "End Tag: " : "Void Tag: "), m_Temp);
            //std::cout << ((foundLength == 1) ? "End Tag: " : "Void Tag: ") << m_Temp << std::endl;
         }
            return;
         case '"':
            FindChar('"', length);
            break;
         case '\'':
            FindChar('\'', length);
            break;
         case '!':
            Exp(length);
            return;
         default:
            break;
         }
      }
   }

   void FindChar(char match, size_t& length)
   {
      char c;
      while (m_Stream.getChar(c) == MemoryStream::Success) {
         m_Temp[length++] = c;
         if (c == match)
            break;
      }
   }

   void Exp(size_t& length)
   {
      char c;
      while (m_Stream.getChar(c) == MemoryStream::Success) {
         switch (c)
         {
         case '-':
            return TryComment(length);
         default:
            this->FindChar('>', length);
            return;
         }
      }
   }

   void TryComment(size_t& length)
   {
      int dashCount = 0;
      bool first = true;
      char c;
      while (m_Stream.getChar(c) == MemoryStream::Success) {
         m_Temp[length++] = c;
         switch (c)
         {
         case '-':
            dashCount++;
            break;
         case '>':
            if (dashCount == 2) {
               m_Temp[length] = 0;
               if (m_Output)
                  printf("Comment: %s\n", m_Temp);
               //std::cout << "Comment: " << m_Temp << std::endl;
               return;
            }
         default:
            dashCount = 0;
            break;
         }
      }
   }
};

