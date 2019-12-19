// html_tag.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <Windows.h>
#include "MemoryStream.h"
#include "TagFinder.h"

int main(int count, char** args)
{
   if (count != 2) {
      puts("Add path to test file as parameter");
   }
   FILE* file = nullptr;
   if (fopen_s(&file, args[1], "rb") != 0)
   {
      puts("Failed to open file\n");
      return 1;
   }
   if (fseek(file, 0, SEEK_END))
      return 1;
   size_t length = ftell(file);
   char* buffer = new char[length];
   fseek(file, 0, SEEK_SET);
   if (fread_s(buffer, length, 1, length, file) != length) {
      puts("failed to read file");
      return 1;
   }
   fclose(file);

   MemoryStream testFile = MemoryStream(length, buffer);
   TagFinder finder = TagFinder(testFile, true);
   clock_t beforeTimeTotal = clock();
   for (int i = 0; i < 100; i++) {
      clock_t beforeTime = clock();
      finder.Read();
      printf("Time Taken = %dms\n", clock() - beforeTime);
      testFile.reset();
   }
   printf("Total Time Taken = %dms\n", clock() - beforeTimeTotal);
   return 0;
}
