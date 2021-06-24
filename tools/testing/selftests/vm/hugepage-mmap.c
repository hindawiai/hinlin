<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hugepage-mmap:
 *
 * Example of using huge page memory in a user application using the mmap
 * प्रणाली call.  Beक्रमe running this application, make sure that the
 * administrator has mounted the hugetlbfs fileप्रणाली (on some directory
 * like /mnt) using the command mount -t hugetlbfs nodev /mnt. In this
 * example, the app is requesting memory of size 256MB that is backed by
 * huge pages.
 *
 * For the ia64 architecture, the Linux kernel reserves Region number 4 क्रम
 * huge pages.  That means that अगर one requires a fixed address, a huge page
 * aligned address starting with 0x800000... will be required.  If a fixed
 * address is not required, the kernel will select an address in the proper
 * range.
 * Other architectures, such as ppc64, i386 or x86_64 are not so स्थिरrained.
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>

#घोषणा खाता_NAME "huge/hugepagefile"
#घोषणा LENGTH (256UL*1024*1024)
#घोषणा PROTECTION (PROT_READ | PROT_WRITE)

/* Only ia64 requires this */
#अगर_घोषित __ia64__
#घोषणा ADDR (व्योम *)(0x8000000000000000UL)
#घोषणा FLAGS (MAP_SHARED | MAP_FIXED)
#अन्यथा
#घोषणा ADDR (व्योम *)(0x0UL)
#घोषणा FLAGS (MAP_SHARED)
#पूर्ण_अगर

अटल व्योम check_bytes(अक्षर *addr)
अणु
	म_लिखो("First hex is %x\n", *((अचिन्हित पूर्णांक *)addr));
पूर्ण

अटल व्योम ग_लिखो_bytes(अक्षर *addr)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < LENGTH; i++)
		*(addr + i) = (अक्षर)i;
पूर्ण

अटल पूर्णांक पढ़ो_bytes(अक्षर *addr)
अणु
	अचिन्हित दीर्घ i;

	check_bytes(addr);
	क्रम (i = 0; i < LENGTH; i++)
		अगर (*(addr + i) != (अक्षर)i) अणु
			म_लिखो("Mismatch at %lu\n", i);
			वापस 1;
		पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	व्योम *addr;
	पूर्णांक fd, ret;

	fd = खोलो(खाता_NAME, O_CREAT | O_RDWR, 0755);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("Open failed");
		निकास(1);
	पूर्ण

	addr = mmap(ADDR, LENGTH, PROTECTION, FLAGS, fd, 0);
	अगर (addr == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		unlink(खाता_NAME);
		निकास(1);
	पूर्ण

	म_लिखो("Returned address is %p\n", addr);
	check_bytes(addr);
	ग_लिखो_bytes(addr);
	ret = पढ़ो_bytes(addr);

	munmap(addr, LENGTH);
	बंद(fd);
	unlink(खाता_NAME);

	वापस ret;
पूर्ण
