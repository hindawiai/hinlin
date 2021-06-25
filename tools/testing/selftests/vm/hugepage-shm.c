<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hugepage-shm:
 *
 * Example of using huge page memory in a user application using Sys V shared
 * memory प्रणाली calls.  In this example the app is requesting 256MB of
 * memory that is backed by huge pages.  The application uses the flag
 * SHM_HUGETLB in the shmget प्रणाली call to inक्रमm the kernel that it is
 * requesting huge pages.
 *
 * For the ia64 architecture, the Linux kernel reserves Region number 4 क्रम
 * huge pages.  That means that अगर one requires a fixed address, a huge page
 * aligned address starting with 0x800000... will be required.  If a fixed
 * address is not required, the kernel will select an address in the proper
 * range.
 * Other architectures, such as ppc64, i386 or x86_64 are not so स्थिरrained.
 *
 * Note: The शेष shared memory limit is quite low on many kernels,
 * you may need to increase it via:
 *
 * echo 268435456 > /proc/sys/kernel/shmmax
 *
 * This will increase the maximum size per shared memory segment to 256MB.
 * The other limit that you will hit eventually is shmall which is the
 * total amount of shared memory in pages. To set it to 16GB on a प्रणाली
 * with a 4kB pagesize करो:
 *
 * echo 4194304 > /proc/sys/kernel/shmall
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>
#समावेश <sys/mman.h>

#अगर_अघोषित SHM_HUGETLB
#घोषणा SHM_HUGETLB 04000
#पूर्ण_अगर

#घोषणा LENGTH (256UL*1024*1024)

#घोषणा dम_लिखो(x)  म_लिखो(x)

/* Only ia64 requires this */
#अगर_घोषित __ia64__
#घोषणा ADDR (व्योम *)(0x8000000000000000UL)
#घोषणा SHMAT_FLAGS (SHM_RND)
#अन्यथा
#घोषणा ADDR (व्योम *)(0x0UL)
#घोषणा SHMAT_FLAGS (0)
#पूर्ण_अगर

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक shmid;
	अचिन्हित दीर्घ i;
	अक्षर *shmaddr;

	shmid = shmget(2, LENGTH, SHM_HUGETLB | IPC_CREAT | SHM_R | SHM_W);
	अगर (shmid < 0) अणु
		लिखो_त्रुटि("shmget");
		निकास(1);
	पूर्ण
	म_लिखो("shmid: 0x%x\n", shmid);

	shmaddr = shmat(shmid, ADDR, SHMAT_FLAGS);
	अगर (shmaddr == (अक्षर *)-1) अणु
		लिखो_त्रुटि("Shared memory attach failure");
		shmctl(shmid, IPC_RMID, शून्य);
		निकास(2);
	पूर्ण
	म_लिखो("shmaddr: %p\n", shmaddr);

	dम_लिखो("Starting the writes:\n");
	क्रम (i = 0; i < LENGTH; i++) अणु
		shmaddr[i] = (अक्षर)(i);
		अगर (!(i % (1024 * 1024)))
			dम_लिखो(".");
	पूर्ण
	dम_लिखो("\n");

	dम_लिखो("Starting the Check...");
	क्रम (i = 0; i < LENGTH; i++)
		अगर (shmaddr[i] != (अक्षर)i) अणु
			म_लिखो("\nIndex %lu mismatched\n", i);
			निकास(3);
		पूर्ण
	dम_लिखो("Done.\n");

	अगर (shmdt((स्थिर व्योम *)shmaddr) != 0) अणु
		लिखो_त्रुटि("Detach failure");
		shmctl(shmid, IPC_RMID, शून्य);
		निकास(4);
	पूर्ण

	shmctl(shmid, IPC_RMID, शून्य);

	वापस 0;
पूर्ण
