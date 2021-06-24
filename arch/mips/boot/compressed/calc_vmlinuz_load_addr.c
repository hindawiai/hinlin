<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010 "Wu Zhangjin" <wuzhangjin@gmail.com>
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/sizes.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित दीर्घ दीर्घ vmlinux_size, vmlinux_load_addr, vmlinuz_load_addr;
	काष्ठा stat sb;

	अगर (argc != 3) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s <pathname> <vmlinux_load_addr>\n",
				argv[0]);
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (stat(argv[1], &sb) == -1) अणु
		लिखो_त्रुटि("stat");
		वापस निकास_त्रुटि;
	पूर्ण

	/* Convert hex अक्षरacters to dec number */
	त्रुटि_सं = 0;
	अगर (माला_पूछो(argv[2], "%llx", &vmlinux_load_addr) != 1) अणु
		अगर (त्रुटि_सं != 0)
			लिखो_त्रुटि("sscanf");
		अन्यथा
			ख_लिखो(मानक_त्रुटि, "No matching characters\n");

		वापस निकास_त्रुटि;
	पूर्ण

	vmlinux_size = (uपूर्णांक64_t)sb.st_size;
	vmlinuz_load_addr = vmlinux_load_addr + vmlinux_size;

	/*
	 * Align with 64KB: KEXEC needs load sections to be aligned to PAGE_SIZE,
	 * which may be as large as 64KB depending on the kernel configuration.
	 */

	vmlinuz_load_addr += (SZ_64K - vmlinux_size % SZ_64K);

	म_लिखो("0x%llx\n", vmlinuz_load_addr);

	वापस निकास_सफल;
पूर्ण
