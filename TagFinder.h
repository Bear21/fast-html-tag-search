#pragma once
#include <cstdio>
#include <string>
#include <iostream>


class TagFinder
{
private:
   int readIndex;
public:
   TagFinder()
   {
   }

   void Read()
   {
      int c;
      while ((c = getc(stdin)) != EOF) {
         switch (c)
         {
         case '<':
            findEnd();
            break;
         default:
            break;
         }
      }
   }

   void findEnd()
   {
      std::string str;
      int c;
      while ((c = getc(stdin)) != EOF) {
         str.push_back(c);
         size_t length = str.length();

         switch (c) {
         case '<':
            return;
         case '>':
            std::cout << "Tag: " << str << std::endl;
            return;
         case '/':
            std::cout << ((str.length() == 1) ? "End Tag: " : "Tag: ") << str << findChar('>') << std::endl;
            return;
         case '"':
            str = str + findChar('"');
            break;
         case '\'':
            str = str + findChar('\'');
            break;
         case '!':
            exp();
            return;
         default:
            break;
         }
      }
   }

   std::string findChar(char match)
   {
      std::string str;
      int c;
      while ((c = getc(stdin)) != EOF) {
         str.push_back(c);
         size_t length = str.length();
         if (c == match)
            break;
      }
      return str;
   }

   void exp()
   {
      int c;
      while ((c = getc(stdin)) != EOF) {
         switch (c)
         {
         case '-':
            return tryComment();
         default:
            this->findChar('>');
            return;
         }
      }
   }

   void tryComment()
   {
      std::string str;
      int dashCount = 0;
      bool first = true;
      int c;
      while ((c = getc(stdin)) != EOF) {
         str.push_back(c);
         switch (c)
         {
         case '-':
            dashCount++;
            break;
         case '>':
            if (dashCount == 2) {
               std::cout << "Comment: " << str << std::endl;
               return;
            }
         default:
            dashCount = 0;
            break;
         }
      }
   }
};

