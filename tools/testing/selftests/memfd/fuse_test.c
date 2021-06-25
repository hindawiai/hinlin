<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * memfd GUP test-हाल
 * This tests memfd पूर्णांकeractions with get_user_pages(). We require the
 * fuse_mnt.c program to provide a fake direct-IO FUSE mount-poपूर्णांक क्रम us. This
 * file-प्रणाली delays _all_ पढ़ोs by 1s and क्रमces direct-IO. This means, any
 * पढ़ो() on files in that file-प्रणाली will pin the receive-buffer pages क्रम at
 * least 1s via get_user_pages().
 *
 * We use this trick to race ADD_SEALS against a ग_लिखो on a memfd object. The
 * ADD_SEALS must fail अगर the memfd pages are still pinned. Note that we use
 * the पढ़ो() syscall with our memory-mapped memfd object as receive buffer to
 * क्रमce the kernel to ग_लिखो पूर्णांकo our memfd object.
 */

#घोषणा _GNU_SOURCE
#घोषणा __EXPORTED_HEADERS__

#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <linux/fभाग.स>
#समावेश <fcntl.h>
#समावेश <linux/memfd.h>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "common.h"

#घोषणा MFD_DEF_SIZE 8192
#घोषणा STACK_SIZE 65536

अटल माप_प्रकार mfd_def_size = MFD_DEF_SIZE;

अटल पूर्णांक mfd_निश्चित_new(स्थिर अक्षर *name, loff_t sz, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक r, fd;

	fd = sys_memfd_create(name, flags);
	अगर (fd < 0) अणु
		म_लिखो("memfd_create(\"%s\", %u) failed: %m\n",
		       name, flags);
		पात();
	पूर्ण

	r = ftruncate(fd, sz);
	अगर (r < 0) अणु
		म_लिखो("ftruncate(%llu) failed: %m\n", (अचिन्हित दीर्घ दीर्घ)sz);
		पात();
	पूर्ण

	वापस fd;
पूर्ण

अटल __u64 mfd_निश्चित_get_seals(पूर्णांक fd)
अणु
	दीर्घ r;

	r = fcntl(fd, F_GET_SEALS);
	अगर (r < 0) अणु
		म_लिखो("GET_SEALS(%d) failed: %m\n", fd);
		पात();
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम mfd_निश्चित_has_seals(पूर्णांक fd, __u64 seals)
अणु
	__u64 s;

	s = mfd_निश्चित_get_seals(fd);
	अगर (s != seals) अणु
		म_लिखो("%llu != %llu = GET_SEALS(%d)\n",
		       (अचिन्हित दीर्घ दीर्घ)seals, (अचिन्हित दीर्घ दीर्घ)s, fd);
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_निश्चित_add_seals(पूर्णांक fd, __u64 seals)
अणु
	दीर्घ r;
	__u64 s;

	s = mfd_निश्चित_get_seals(fd);
	r = fcntl(fd, F_ADD_SEALS, seals);
	अगर (r < 0) अणु
		म_लिखो("ADD_SEALS(%d, %llu -> %llu) failed: %m\n",
		       fd, (अचिन्हित दीर्घ दीर्घ)s, (अचिन्हित दीर्घ दीर्घ)seals);
		पात();
	पूर्ण
पूर्ण

अटल पूर्णांक mfd_busy_add_seals(पूर्णांक fd, __u64 seals)
अणु
	दीर्घ r;
	__u64 s;

	r = fcntl(fd, F_GET_SEALS);
	अगर (r < 0)
		s = 0;
	अन्यथा
		s = r;

	r = fcntl(fd, F_ADD_SEALS, seals);
	अगर (r < 0 && त्रुटि_सं != EBUSY) अणु
		म_लिखो("ADD_SEALS(%d, %llu -> %llu) didn't fail as expected with EBUSY: %m\n",
		       fd, (अचिन्हित दीर्घ दीर्घ)s, (अचिन्हित दीर्घ दीर्घ)seals);
		पात();
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम *mfd_निश्चित_mmap_shared(पूर्णांक fd)
अणु
	व्योम *p;

	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ | PROT_WRITE,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम *mfd_निश्चित_mmap_निजी(पूर्णांक fd)
अणु
	व्योम *p;

	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ | PROT_WRITE,
		 MAP_PRIVATE,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक global_mfd = -1;
अटल व्योम *global_p = शून्य;

अटल पूर्णांक sealing_thपढ़ो_fn(व्योम *arg)
अणु
	पूर्णांक sig, r;

	/*
	 * This thपढ़ो first रुकोs 200ms so any pending operation in the parent
	 * is correctly started. After that, it tries to seal @global_mfd as
	 * SEAL_WRITE. This _must_ fail as the parent thपढ़ो has a पढ़ो() पूर्णांकo
	 * that memory mapped object still ongoing.
	 * We then रुको one more second and try sealing again. This समय it
	 * must succeed as there shouldn't be anyone अन्यथा pinning the pages.
	 */

	/* रुको 200ms क्रम FUSE-request to be active */
	usleep(200000);

	/* unmount mapping beक्रमe sealing to aव्योम i_mmap_writable failures */
	munmap(global_p, mfd_def_size);

	/* Try sealing the global file; expect EBUSY or success. Current
	 * kernels will never succeed, but in the future, kernels might
	 * implement page-replacements or other fancy ways to aव्योम racing
	 * ग_लिखोs. */
	r = mfd_busy_add_seals(global_mfd, F_SEAL_WRITE);
	अगर (r >= 0) अणु
		म_लिखो("HURRAY! This kernel fixed GUP races!\n");
	पूर्ण अन्यथा अणु
		/* रुको 1s more so the FUSE-request is करोne */
		sleep(1);

		/* try sealing the global file again */
		mfd_निश्चित_add_seals(global_mfd, F_SEAL_WRITE);
	पूर्ण

	वापस 0;
पूर्ण

अटल pid_t spawn_sealing_thपढ़ो(व्योम)
अणु
	uपूर्णांक8_t *stack;
	pid_t pid;

	stack = दो_स्मृति(STACK_SIZE);
	अगर (!stack) अणु
		म_लिखो("malloc(STACK_SIZE) failed: %m\n");
		पात();
	पूर्ण

	pid = clone(sealing_thपढ़ो_fn,
		    stack + STACK_SIZE,
		    SIGCHLD | CLONE_खाताS | CLONE_FS | CLONE_VM,
		    शून्य);
	अगर (pid < 0) अणु
		म_लिखो("clone() failed: %m\n");
		पात();
	पूर्ण

	वापस pid;
पूर्ण

अटल व्योम join_sealing_thपढ़ो(pid_t pid)
अणु
	रुकोpid(pid, शून्य, 0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *zero;
	पूर्णांक fd, mfd, r;
	व्योम *p;
	पूर्णांक was_sealed;
	pid_t pid;

	अगर (argc < 2) अणु
		म_लिखो("error: please pass path to file in fuse_mnt mount-point\n");
		पात();
	पूर्ण

	अगर (argc >= 3) अणु
		अगर (!म_भेद(argv[2], "hugetlbfs")) अणु
			अचिन्हित दीर्घ hpage_size = शेष_huge_page_size();

			अगर (!hpage_size) अणु
				म_लिखो("Unable to determine huge page size\n");
				पात();
			पूर्ण

			hugetlbfs_test = 1;
			mfd_def_size = hpage_size * 2;
		पूर्ण अन्यथा अणु
			म_लिखो("Unknown option: %s\n", argv[2]);
			पात();
		पूर्ण
	पूर्ण

	zero = सुस्मृति(माप(*zero), mfd_def_size);

	/* खोलो FUSE memfd file क्रम GUP testing */
	म_लिखो("opening: %s\n", argv[1]);
	fd = खोलो(argv[1], O_RDONLY | O_CLOEXEC);
	अगर (fd < 0) अणु
		म_लिखो("cannot open(\"%s\"): %m\n", argv[1]);
		पात();
	पूर्ण

	/* create new memfd-object */
	mfd = mfd_निश्चित_new("kern_memfd_fuse",
			     mfd_def_size,
			     MFD_CLOEXEC | MFD_ALLOW_SEALING);

	/* mmap memfd-object क्रम writing */
	p = mfd_निश्चित_mmap_shared(mfd);

	/* pass mfd+mapping to a separate sealing-thपढ़ो which tries to seal
	 * the memfd objects with SEAL_WRITE जबतक we ग_लिखो पूर्णांकo it */
	global_mfd = mfd;
	global_p = p;
	pid = spawn_sealing_thपढ़ो();

	/* Use पढ़ो() on the FUSE file to पढ़ो पूर्णांकo our memory-mapped memfd
	 * object. This races the other thपढ़ो which tries to seal the
	 * memfd-object.
	 * If @fd is on the memfd-fake-FUSE-FS, the पढ़ो() is delayed by 1s.
	 * This guarantees that the receive-buffer is pinned क्रम 1s until the
	 * data is written पूर्णांकo it. The racing ADD_SEALS should thus fail as
	 * the pages are still pinned. */
	r = पढ़ो(fd, p, mfd_def_size);
	अगर (r < 0) अणु
		म_लिखो("read() failed: %m\n");
		पात();
	पूर्ण अन्यथा अगर (!r) अणु
		म_लिखो("unexpected EOF on read()\n");
		पात();
	पूर्ण

	was_sealed = mfd_निश्चित_get_seals(mfd) & F_SEAL_WRITE;

	/* Wait क्रम sealing-thपढ़ो to finish and verअगरy that it
	 * successfully sealed the file after the second try. */
	join_sealing_thपढ़ो(pid);
	mfd_निश्चित_has_seals(mfd, F_SEAL_WRITE);

	/* *IF* the memfd-object was sealed at the समय our पढ़ो() वापसed,
	 * then the kernel did a page-replacement or canceled the पढ़ो() (or
	 * whatever magic it did..). In that हाल, the memfd object is still
	 * all zero.
	 * In हाल the memfd-object was *not* sealed, the पढ़ो() was successfull
	 * and the memfd object must *not* be all zero.
	 * Note that in real scenarios, there might be a mixture of both, but
	 * in this test-हालs, we have explicit 200ms delays which should be
	 * enough to aव्योम any in-flight ग_लिखोs. */

	p = mfd_निश्चित_mmap_निजी(mfd);
	अगर (was_sealed && स_भेद(p, zero, mfd_def_size)) अणु
		म_लिखो("memfd sealed during read() but data not discarded\n");
		पात();
	पूर्ण अन्यथा अगर (!was_sealed && !स_भेद(p, zero, mfd_def_size)) अणु
		म_लिखो("memfd sealed after read() but data discarded\n");
		पात();
	पूर्ण

	बंद(mfd);
	बंद(fd);

	म_लिखो("fuse: DONE\n");
	मुक्त(zero);

	वापस 0;
पूर्ण
