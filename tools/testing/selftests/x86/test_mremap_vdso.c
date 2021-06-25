<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 32-bit test to check vDSO mremap.
 *
 * Copyright (c) 2016 Dmitry Safonov
 * Suggested-by: Andrew Lutomirski
 */
/*
 * Can be built अटलally:
 * gcc -Os -Wall -अटल -m32 test_mremap_vdso.c
 */
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <माला.स>

#समावेश <sys/mman.h>
#समावेश <sys/auxv.h>
#समावेश <sys/syscall.h>
#समावेश <sys/रुको.h>

#घोषणा PAGE_SIZE	4096

अटल पूर्णांक try_to_remap(व्योम *vdso_addr, अचिन्हित दीर्घ size)
अणु
	व्योम *dest_addr, *new_addr;

	/* Searching क्रम memory location where to remap */
	dest_addr = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	अगर (dest_addr == MAP_FAILED) अणु
		म_लिखो("[WARN]\tmmap failed (%d): %m\n", त्रुटि_सं);
		वापस 0;
	पूर्ण

	म_लिखो("[NOTE]\tMoving vDSO: [%p, %#lx] -> [%p, %#lx]\n",
		vdso_addr, (अचिन्हित दीर्घ)vdso_addr + size,
		dest_addr, (अचिन्हित दीर्घ)dest_addr + size);
	ख_साफ(मानक_निकास);

	new_addr = mremap(vdso_addr, size, size,
			MREMAP_FIXED|MREMAP_MAYMOVE, dest_addr);
	अगर ((अचिन्हित दीर्घ)new_addr == (अचिन्हित दीर्घ)-1) अणु
		munmap(dest_addr, size);
		अगर (त्रुटि_सं == EINVAL) अणु
			म_लिखो("[NOTE]\tvDSO partial move failed, will try with bigger size\n");
			वापस -1; /* Retry with larger */
		पूर्ण
		म_लिखो("[FAIL]\tmremap failed (%d): %m\n", त्रुटि_सं);
		वापस 1;
	पूर्ण

	वापस 0;

पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	pid_t child;

	child = विभाजन();
	अगर (child == -1) अणु
		म_लिखो("[WARN]\tfailed to fork (%d): %m\n", त्रुटि_सं);
		वापस 1;
	पूर्ण

	अगर (child == 0) अणु
		अचिन्हित दीर्घ vdso_size = PAGE_SIZE;
		अचिन्हित दीर्घ auxval;
		पूर्णांक ret = -1;

		auxval = getauxval(AT_SYSINFO_EHDR);
		म_लिखो("\tAT_SYSINFO_EHDR is %#lx\n", auxval);
		अगर (!auxval || auxval == -ENOENT) अणु
			म_लिखो("[WARN]\tgetauxval failed\n");
			वापस 0;
		पूर्ण

		/* Simpler than parsing ELF header */
		जबतक (ret < 0) अणु
			ret = try_to_remap((व्योम *)auxval, vdso_size);
			vdso_size += PAGE_SIZE;
		पूर्ण

#अगर_घोषित __i386__
		/* Glibc is likely to explode now - निकास with raw syscall */
		यंत्र अस्थिर ("int $0x80" : : "a" (__NR_निकास), "b" (!!ret));
#अन्यथा /* __x86_64__ */
		syscall(SYS_निकास, ret);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		पूर्णांक status;

		अगर (रुकोpid(child, &status, 0) != child ||
			!WIFEXITED(status)) अणु
			म_लिखो("[FAIL]\tmremap() of the vDSO does not work on this kernel!\n");
			वापस 1;
		पूर्ण अन्यथा अगर (WEXITSTATUS(status) != 0) अणु
			म_लिखो("[FAIL]\tChild failed with %d\n",
					WEXITSTATUS(status));
			वापस 1;
		पूर्ण
		म_लिखो("[OK]\n");
	पूर्ण

	वापस 0;
पूर्ण
