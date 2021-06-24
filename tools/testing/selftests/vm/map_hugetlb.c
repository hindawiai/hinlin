<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Example of using hugepage memory in a user application using the mmap
 * प्रणाली call with MAP_HUGETLB flag.  Beक्रमe running this program make
 * sure the administrator has allocated enough शेष sized huge pages
 * to cover the 256 MB allocation.
 *
 * For ia64 architecture, Linux kernel reserves Region number 4 क्रम hugepages.
 * That means the addresses starting with 0x800000... will need to be
 * specअगरied.  Specअगरying a fixed address is not required on ppc64, i386
 * or x86_64.
 */
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>

#घोषणा LENGTH (256UL*1024*1024)
#घोषणा PROTECTION (PROT_READ | PROT_WRITE)

#अगर_अघोषित MAP_HUGETLB
#घोषणा MAP_HUGETLB 0x40000 /* arch specअगरic */
#पूर्ण_अगर

#अगर_अघोषित MAP_HUGE_SHIFT
#घोषणा MAP_HUGE_SHIFT 26
#पूर्ण_अगर

#अगर_अघोषित MAP_HUGE_MASK
#घोषणा MAP_HUGE_MASK 0x3f
#पूर्ण_अगर

/* Only ia64 requires this */
#अगर_घोषित __ia64__
#घोषणा ADDR (व्योम *)(0x8000000000000000UL)
#घोषणा FLAGS (MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_FIXED)
#अन्यथा
#घोषणा ADDR (व्योम *)(0x0UL)
#घोषणा FLAGS (MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB)
#पूर्ण_अगर

अटल व्योम check_bytes(अक्षर *addr)
अणु
	म_लिखो("First hex is %x\n", *((अचिन्हित पूर्णांक *)addr));
पूर्ण

अटल व्योम ग_लिखो_bytes(अक्षर *addr, माप_प्रकार length)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < length; i++)
		*(addr + i) = (अक्षर)i;
पूर्ण

अटल पूर्णांक पढ़ो_bytes(अक्षर *addr, माप_प्रकार length)
अणु
	अचिन्हित दीर्घ i;

	check_bytes(addr);
	क्रम (i = 0; i < length; i++)
		अगर (*(addr + i) != (अक्षर)i) अणु
			म_लिखो("Mismatch at %lu\n", i);
			वापस 1;
		पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	व्योम *addr;
	पूर्णांक ret;
	माप_प्रकार length = LENGTH;
	पूर्णांक flags = FLAGS;
	पूर्णांक shअगरt = 0;

	अगर (argc > 1)
		length = म_से_द(argv[1]) << 20;
	अगर (argc > 2) अणु
		shअगरt = म_से_प(argv[2]);
		अगर (shअगरt)
			flags |= (shअगरt & MAP_HUGE_MASK) << MAP_HUGE_SHIFT;
	पूर्ण

	अगर (shअगरt)
		म_लिखो("%u kB hugepages\n", 1 << (shअगरt - 10));
	अन्यथा
		म_लिखो("Default size hugepages\n");
	म_लिखो("Mapping %lu Mbytes\n", (अचिन्हित दीर्घ)length >> 20);

	addr = mmap(ADDR, length, PROTECTION, flags, -1, 0);
	अगर (addr == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		निकास(1);
	पूर्ण

	म_लिखो("Returned address is %p\n", addr);
	check_bytes(addr);
	ग_लिखो_bytes(addr, length);
	ret = पढ़ो_bytes(addr, length);

	/* munmap() length of MAP_HUGETLB memory must be hugepage aligned */
	अगर (munmap(addr, length)) अणु
		लिखो_त्रुटि("munmap");
		निकास(1);
	पूर्ण

	वापस ret;
पूर्ण
