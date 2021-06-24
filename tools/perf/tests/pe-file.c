<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

// pe-file.exe and pe-file.exe.debug built with;
// x86_64-w64-mingw32-gcc -o pe-file.exe pe-file.c
//   -Wl,--file-alignment,4096 -Wl,--build-id
// x86_64-w64-mingw32-objcopy --only-keep-debug
//   --compress-debug-sections pe-file.exe pe-file.exe.debug
// x86_64-w64-mingw32-objcopy --strip-debug
//   --add-gnu-debuglink=pe-file.exe.debug pe-file.exe

पूर्णांक मुख्य(पूर्णांक argc, अक्षर स्थिर *argv[])
अणु
	वापस 0;
पूर्ण
