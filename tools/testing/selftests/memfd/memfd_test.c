<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#घोषणा MEMFD_STR	"memfd:"
#घोषणा MEMFD_HUGE_STR	"memfd-hugetlb:"
#घोषणा SHARED_FT_STR	"(shared file-table)"

#घोषणा MFD_DEF_SIZE 8192
#घोषणा STACK_SIZE 65536

/*
 * Default is not to test hugetlbfs
 */
अटल माप_प्रकार mfd_def_size = MFD_DEF_SIZE;
अटल स्थिर अक्षर *memfd_str = MEMFD_STR;

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

अटल पूर्णांक mfd_निश्चित_reखोलो_fd(पूर्णांक fd_in)
अणु
	पूर्णांक r, fd;
	अक्षर path[100];

	प्र_लिखो(path, "/proc/self/fd/%d", fd_in);

	fd = खोलो(path, O_RDWR);
	अगर (fd < 0) अणु
		म_लिखो("re-open of existing fd %d failed\n", fd_in);
		पात();
	पूर्ण

	वापस fd;
पूर्ण

अटल व्योम mfd_fail_new(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक r;

	r = sys_memfd_create(name, flags);
	अगर (r >= 0) अणु
		म_लिखो("memfd_create(\"%s\", %u) succeeded, but failure expected\n",
		       name, flags);
		बंद(r);
		पात();
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक mfd_निश्चित_get_seals(पूर्णांक fd)
अणु
	पूर्णांक r;

	r = fcntl(fd, F_GET_SEALS);
	अगर (r < 0) अणु
		म_लिखो("GET_SEALS(%d) failed: %m\n", fd);
		पात();
	पूर्ण

	वापस (अचिन्हित पूर्णांक)r;
पूर्ण

अटल व्योम mfd_निश्चित_has_seals(पूर्णांक fd, अचिन्हित पूर्णांक seals)
अणु
	अचिन्हित पूर्णांक s;

	s = mfd_निश्चित_get_seals(fd);
	अगर (s != seals) अणु
		म_लिखो("%u != %u = GET_SEALS(%d)\n", seals, s, fd);
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_निश्चित_add_seals(पूर्णांक fd, अचिन्हित पूर्णांक seals)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक s;

	s = mfd_निश्चित_get_seals(fd);
	r = fcntl(fd, F_ADD_SEALS, seals);
	अगर (r < 0) अणु
		म_लिखो("ADD_SEALS(%d, %u -> %u) failed: %m\n", fd, s, seals);
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_fail_add_seals(पूर्णांक fd, अचिन्हित पूर्णांक seals)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक s;

	r = fcntl(fd, F_GET_SEALS);
	अगर (r < 0)
		s = 0;
	अन्यथा
		s = (अचिन्हित पूर्णांक)r;

	r = fcntl(fd, F_ADD_SEALS, seals);
	अगर (r >= 0) अणु
		म_लिखो("ADD_SEALS(%d, %u -> %u) didn't fail as expected\n",
				fd, s, seals);
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_निश्चित_size(पूर्णांक fd, माप_प्रकार size)
अणु
	काष्ठा stat st;
	पूर्णांक r;

	r = ख_स्थिति(fd, &st);
	अगर (r < 0) अणु
		म_लिखो("fstat(%d) failed: %m\n", fd);
		पात();
	पूर्ण अन्यथा अगर (st.st_size != size) अणु
		म_लिखो("wrong file size %lld, but expected %lld\n",
		       (दीर्घ दीर्घ)st.st_size, (दीर्घ दीर्घ)size);
		पात();
	पूर्ण
पूर्ण

अटल पूर्णांक mfd_निश्चित_dup(पूर्णांक fd)
अणु
	पूर्णांक r;

	r = dup(fd);
	अगर (r < 0) अणु
		म_लिखो("dup(%d) failed: %m\n", fd);
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
		 PROT_READ,
		 MAP_PRIVATE,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक mfd_निश्चित_खोलो(पूर्णांक fd, पूर्णांक flags, mode_t mode)
अणु
	अक्षर buf[512];
	पूर्णांक r;

	प्र_लिखो(buf, "/proc/self/fd/%d", fd);
	r = खोलो(buf, flags, mode);
	अगर (r < 0) अणु
		म_लिखो("open(%s) failed: %m\n", buf);
		पात();
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम mfd_fail_खोलो(पूर्णांक fd, पूर्णांक flags, mode_t mode)
अणु
	अक्षर buf[512];
	पूर्णांक r;

	प्र_लिखो(buf, "/proc/self/fd/%d", fd);
	r = खोलो(buf, flags, mode);
	अगर (r >= 0) अणु
		म_लिखो("open(%s) didn't fail as expected\n", buf);
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_निश्चित_पढ़ो(पूर्णांक fd)
अणु
	अक्षर buf[16];
	व्योम *p;
	sमाप_प्रकार l;

	l = पढ़ो(fd, buf, माप(buf));
	अगर (l != माप(buf)) अणु
		म_लिखो("read() failed: %m\n");
		पात();
	पूर्ण

	/* verअगरy PROT_READ *is* allowed */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ,
		 MAP_PRIVATE,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण
	munmap(p, mfd_def_size);

	/* verअगरy MAP_PRIVATE is *always* allowed (even writable) */
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
	munmap(p, mfd_def_size);
पूर्ण

/* Test that PROT_READ + MAP_SHARED mappings work. */
अटल व्योम mfd_निश्चित_पढ़ो_shared(पूर्णांक fd)
अणु
	व्योम *p;

	/* verअगरy PROT_READ and MAP_SHARED *is* allowed */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण
	munmap(p, mfd_def_size);
पूर्ण

अटल व्योम mfd_निश्चित_विभाजन_निजी_ग_लिखो(पूर्णांक fd)
अणु
	पूर्णांक *p;
	pid_t pid;

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

	p[0] = 22;

	pid = विभाजन();
	अगर (pid == 0) अणु
		p[0] = 33;
		निकास(0);
	पूर्ण अन्यथा अणु
		रुकोpid(pid, शून्य, 0);

		अगर (p[0] != 22) अणु
			म_लिखो("MAP_PRIVATE copy-on-write failed: %m\n");
			पात();
		पूर्ण
	पूर्ण

	munmap(p, mfd_def_size);
पूर्ण

अटल व्योम mfd_निश्चित_ग_लिखो(पूर्णांक fd)
अणु
	sमाप_प्रकार l;
	व्योम *p;
	पूर्णांक r;

	/*
	 * huegtlbfs करोes not support ग_लिखो, but we want to
	 * verअगरy everything अन्यथा here.
	 */
	अगर (!hugetlbfs_test) अणु
		/* verअगरy ग_लिखो() succeeds */
		l = ग_लिखो(fd, "\0\0\0\0", 4);
		अगर (l != 4) अणु
			म_लिखो("write() failed: %m\n");
			पात();
		पूर्ण
	पूर्ण

	/* verअगरy PROT_READ | PROT_WRITE is allowed */
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
	*(अक्षर *)p = 0;
	munmap(p, mfd_def_size);

	/* verअगरy PROT_WRITE is allowed */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_WRITE,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण
	*(अक्षर *)p = 0;
	munmap(p, mfd_def_size);

	/* verअगरy PROT_READ with MAP_SHARED is allowed and a following
	 * mprotect(PROT_WRITE) allows writing */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("mmap() failed: %m\n");
		पात();
	पूर्ण

	r = mprotect(p, mfd_def_size, PROT_READ | PROT_WRITE);
	अगर (r < 0) अणु
		म_लिखो("mprotect() failed: %m\n");
		पात();
	पूर्ण

	*(अक्षर *)p = 0;
	munmap(p, mfd_def_size);

	/* verअगरy PUNCH_HOLE works */
	r = fallocate(fd,
		      FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE,
		      0,
		      mfd_def_size);
	अगर (r < 0) अणु
		म_लिखो("fallocate(PUNCH_HOLE) failed: %m\n");
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_fail_ग_लिखो(पूर्णांक fd)
अणु
	sमाप_प्रकार l;
	व्योम *p;
	पूर्णांक r;

	/* verअगरy ग_लिखो() fails */
	l = ग_लिखो(fd, "data", 4);
	अगर (l != -EPERM) अणु
		म_लिखो("expected EPERM on write(), but got %d: %m\n", (पूर्णांक)l);
		पात();
	पूर्ण

	/* verअगरy PROT_READ | PROT_WRITE is not allowed */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ | PROT_WRITE,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p != MAP_FAILED) अणु
		म_लिखो("mmap() didn't fail as expected\n");
		पात();
	पूर्ण

	/* verअगरy PROT_WRITE is not allowed */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_WRITE,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p != MAP_FAILED) अणु
		म_लिखो("mmap() didn't fail as expected\n");
		पात();
	पूर्ण

	/* Verअगरy PROT_READ with MAP_SHARED with a following mprotect is not
	 * allowed. Note that क्रम r/w the kernel alपढ़ोy prevents the mmap. */
	p = mmap(शून्य,
		 mfd_def_size,
		 PROT_READ,
		 MAP_SHARED,
		 fd,
		 0);
	अगर (p != MAP_FAILED) अणु
		r = mprotect(p, mfd_def_size, PROT_READ | PROT_WRITE);
		अगर (r >= 0) अणु
			म_लिखो("mmap()+mprotect() didn't fail as expected\n");
			पात();
		पूर्ण
	पूर्ण

	/* verअगरy PUNCH_HOLE fails */
	r = fallocate(fd,
		      FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE,
		      0,
		      mfd_def_size);
	अगर (r >= 0) अणु
		म_लिखो("fallocate(PUNCH_HOLE) didn't fail as expected\n");
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_निश्चित_shrink(पूर्णांक fd)
अणु
	पूर्णांक r, fd2;

	r = ftruncate(fd, mfd_def_size / 2);
	अगर (r < 0) अणु
		म_लिखो("ftruncate(SHRINK) failed: %m\n");
		पात();
	पूर्ण

	mfd_निश्चित_size(fd, mfd_def_size / 2);

	fd2 = mfd_निश्चित_खोलो(fd,
			      O_RDWR | O_CREAT | O_TRUNC,
			      S_IRUSR | S_IWUSR);
	बंद(fd2);

	mfd_निश्चित_size(fd, 0);
पूर्ण

अटल व्योम mfd_fail_shrink(पूर्णांक fd)
अणु
	पूर्णांक r;

	r = ftruncate(fd, mfd_def_size / 2);
	अगर (r >= 0) अणु
		म_लिखो("ftruncate(SHRINK) didn't fail as expected\n");
		पात();
	पूर्ण

	mfd_fail_खोलो(fd,
		      O_RDWR | O_CREAT | O_TRUNC,
		      S_IRUSR | S_IWUSR);
पूर्ण

अटल व्योम mfd_निश्चित_grow(पूर्णांक fd)
अणु
	पूर्णांक r;

	r = ftruncate(fd, mfd_def_size * 2);
	अगर (r < 0) अणु
		म_लिखो("ftruncate(GROW) failed: %m\n");
		पात();
	पूर्ण

	mfd_निश्चित_size(fd, mfd_def_size * 2);

	r = fallocate(fd,
		      0,
		      0,
		      mfd_def_size * 4);
	अगर (r < 0) अणु
		म_लिखो("fallocate(ALLOC) failed: %m\n");
		पात();
	पूर्ण

	mfd_निश्चित_size(fd, mfd_def_size * 4);
पूर्ण

अटल व्योम mfd_fail_grow(पूर्णांक fd)
अणु
	पूर्णांक r;

	r = ftruncate(fd, mfd_def_size * 2);
	अगर (r >= 0) अणु
		म_लिखो("ftruncate(GROW) didn't fail as expected\n");
		पात();
	पूर्ण

	r = fallocate(fd,
		      0,
		      0,
		      mfd_def_size * 4);
	अगर (r >= 0) अणु
		म_लिखो("fallocate(ALLOC) didn't fail as expected\n");
		पात();
	पूर्ण
पूर्ण

अटल व्योम mfd_निश्चित_grow_ग_लिखो(पूर्णांक fd)
अणु
	अटल अक्षर *buf;
	sमाप_प्रकार l;

	/* hugetlbfs करोes not support ग_लिखो */
	अगर (hugetlbfs_test)
		वापस;

	buf = दो_स्मृति(mfd_def_size * 8);
	अगर (!buf) अणु
		म_लिखो("malloc(%zu) failed: %m\n", mfd_def_size * 8);
		पात();
	पूर्ण

	l = pग_लिखो(fd, buf, mfd_def_size * 8, 0);
	अगर (l != (mfd_def_size * 8)) अणु
		म_लिखो("pwrite() failed: %m\n");
		पात();
	पूर्ण

	mfd_निश्चित_size(fd, mfd_def_size * 8);
पूर्ण

अटल व्योम mfd_fail_grow_ग_लिखो(पूर्णांक fd)
अणु
	अटल अक्षर *buf;
	sमाप_प्रकार l;

	/* hugetlbfs करोes not support ग_लिखो */
	अगर (hugetlbfs_test)
		वापस;

	buf = दो_स्मृति(mfd_def_size * 8);
	अगर (!buf) अणु
		म_लिखो("malloc(%zu) failed: %m\n", mfd_def_size * 8);
		पात();
	पूर्ण

	l = pग_लिखो(fd, buf, mfd_def_size * 8, 0);
	अगर (l == (mfd_def_size * 8)) अणु
		म_लिखो("pwrite() didn't fail as expected\n");
		पात();
	पूर्ण
पूर्ण

अटल पूर्णांक idle_thपढ़ो_fn(व्योम *arg)
अणु
	sigset_t set;
	पूर्णांक sig;

	/* dummy रुकोer; संक_इति terminates us anyway */
	sigemptyset(&set);
	sigaddset(&set, संक_इति);
	sigरुको(&set, &sig);

	वापस 0;
पूर्ण

अटल pid_t spawn_idle_thपढ़ो(अचिन्हित पूर्णांक flags)
अणु
	uपूर्णांक8_t *stack;
	pid_t pid;

	stack = दो_स्मृति(STACK_SIZE);
	अगर (!stack) अणु
		म_लिखो("malloc(STACK_SIZE) failed: %m\n");
		पात();
	पूर्ण

	pid = clone(idle_thपढ़ो_fn,
		    stack + STACK_SIZE,
		    SIGCHLD | flags,
		    शून्य);
	अगर (pid < 0) अणु
		म_लिखो("clone() failed: %m\n");
		पात();
	पूर्ण

	वापस pid;
पूर्ण

अटल व्योम join_idle_thपढ़ो(pid_t pid)
अणु
	समाप्त(pid, संक_इति);
	रुकोpid(pid, शून्य, 0);
पूर्ण

/*
 * Test memfd_create() syscall
 * Verअगरy syscall-argument validation, including name checks, flag validation
 * and more.
 */
अटल व्योम test_create(व्योम)
अणु
	अक्षर buf[2048];
	पूर्णांक fd;

	म_लिखो("%s CREATE\n", memfd_str);

	/* test शून्य name */
	mfd_fail_new(शून्य, 0);

	/* test over-दीर्घ name (not zero-terminated) */
	स_रखो(buf, 0xff, माप(buf));
	mfd_fail_new(buf, 0);

	/* test over-दीर्घ zero-terminated name */
	स_रखो(buf, 0xff, माप(buf));
	buf[माप(buf) - 1] = 0;
	mfd_fail_new(buf, 0);

	/* verअगरy "" is a valid name */
	fd = mfd_निश्चित_new("", 0, 0);
	बंद(fd);

	/* verअगरy invalid O_* खोलो flags */
	mfd_fail_new("", 0x0100);
	mfd_fail_new("", ~MFD_CLOEXEC);
	mfd_fail_new("", ~MFD_ALLOW_SEALING);
	mfd_fail_new("", ~0);
	mfd_fail_new("", 0x80000000U);

	/* verअगरy MFD_CLOEXEC is allowed */
	fd = mfd_निश्चित_new("", 0, MFD_CLOEXEC);
	बंद(fd);

	/* verअगरy MFD_ALLOW_SEALING is allowed */
	fd = mfd_निश्चित_new("", 0, MFD_ALLOW_SEALING);
	बंद(fd);

	/* verअगरy MFD_ALLOW_SEALING | MFD_CLOEXEC is allowed */
	fd = mfd_निश्चित_new("", 0, MFD_ALLOW_SEALING | MFD_CLOEXEC);
	बंद(fd);
पूर्ण

/*
 * Test basic sealing
 * A very basic sealing test to see whether setting/retrieving seals works.
 */
अटल व्योम test_basic(व्योम)
अणु
	पूर्णांक fd;

	म_लिखो("%s BASIC\n", memfd_str);

	fd = mfd_निश्चित_new("kern_memfd_basic",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);

	/* add basic seals */
	mfd_निश्चित_has_seals(fd, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_SHRINK |
				 F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_SHRINK |
				 F_SEAL_WRITE);

	/* add them again */
	mfd_निश्चित_add_seals(fd, F_SEAL_SHRINK |
				 F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_SHRINK |
				 F_SEAL_WRITE);

	/* add more seals and seal against sealing */
	mfd_निश्चित_add_seals(fd, F_SEAL_GROW | F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd, F_SEAL_SHRINK |
				 F_SEAL_GROW |
				 F_SEAL_WRITE |
				 F_SEAL_SEAL);

	/* verअगरy that sealing no दीर्घer works */
	mfd_fail_add_seals(fd, F_SEAL_GROW);
	mfd_fail_add_seals(fd, 0);

	बंद(fd);

	/* verअगरy sealing करोes not work without MFD_ALLOW_SEALING */
	fd = mfd_निश्चित_new("kern_memfd_basic",
			    mfd_def_size,
			    MFD_CLOEXEC);
	mfd_निश्चित_has_seals(fd, F_SEAL_SEAL);
	mfd_fail_add_seals(fd, F_SEAL_SHRINK |
			       F_SEAL_GROW |
			       F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_SEAL);
	बंद(fd);
पूर्ण

/*
 * Test SEAL_WRITE
 * Test whether SEAL_WRITE actually prevents modअगरications.
 */
अटल व्योम test_seal_ग_लिखो(व्योम)
अणु
	पूर्णांक fd;

	म_लिखो("%s SEAL-WRITE\n", memfd_str);

	fd = mfd_निश्चित_new("kern_memfd_seal_write",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE);

	mfd_निश्चित_पढ़ो(fd);
	mfd_fail_ग_लिखो(fd);
	mfd_निश्चित_shrink(fd);
	mfd_निश्चित_grow(fd);
	mfd_fail_grow_ग_लिखो(fd);

	बंद(fd);
पूर्ण

/*
 * Test SEAL_FUTURE_WRITE
 * Test whether SEAL_FUTURE_WRITE actually prevents modअगरications.
 */
अटल व्योम test_seal_future_ग_लिखो(व्योम)
अणु
	पूर्णांक fd, fd2;
	व्योम *p;

	म_लिखो("%s SEAL-FUTURE-WRITE\n", memfd_str);

	fd = mfd_निश्चित_new("kern_memfd_seal_future_write",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);

	p = mfd_निश्चित_mmap_shared(fd);

	mfd_निश्चित_has_seals(fd, 0);

	mfd_निश्चित_add_seals(fd, F_SEAL_FUTURE_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_FUTURE_WRITE);

	/* पढ़ो should pass, ग_लिखोs should fail */
	mfd_निश्चित_पढ़ो(fd);
	mfd_निश्चित_पढ़ो_shared(fd);
	mfd_fail_ग_लिखो(fd);

	fd2 = mfd_निश्चित_reखोलो_fd(fd);
	/* पढ़ो should pass, ग_लिखोs should still fail */
	mfd_निश्चित_पढ़ो(fd2);
	mfd_निश्चित_पढ़ो_shared(fd2);
	mfd_fail_ग_लिखो(fd2);

	mfd_निश्चित_विभाजन_निजी_ग_लिखो(fd);

	munmap(p, mfd_def_size);
	बंद(fd2);
	बंद(fd);
पूर्ण

/*
 * Test SEAL_SHRINK
 * Test whether SEAL_SHRINK actually prevents shrinking
 */
अटल व्योम test_seal_shrink(व्योम)
अणु
	पूर्णांक fd;

	म_लिखो("%s SEAL-SHRINK\n", memfd_str);

	fd = mfd_निश्चित_new("kern_memfd_seal_shrink",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd, F_SEAL_SHRINK);

	mfd_निश्चित_पढ़ो(fd);
	mfd_निश्चित_ग_लिखो(fd);
	mfd_fail_shrink(fd);
	mfd_निश्चित_grow(fd);
	mfd_निश्चित_grow_ग_लिखो(fd);

	बंद(fd);
पूर्ण

/*
 * Test SEAL_GROW
 * Test whether SEAL_GROW actually prevents growing
 */
अटल व्योम test_seal_grow(व्योम)
अणु
	पूर्णांक fd;

	म_लिखो("%s SEAL-GROW\n", memfd_str);

	fd = mfd_निश्चित_new("kern_memfd_seal_grow",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_GROW);
	mfd_निश्चित_has_seals(fd, F_SEAL_GROW);

	mfd_निश्चित_पढ़ो(fd);
	mfd_निश्चित_ग_लिखो(fd);
	mfd_निश्चित_shrink(fd);
	mfd_fail_grow(fd);
	mfd_fail_grow_ग_लिखो(fd);

	बंद(fd);
पूर्ण

/*
 * Test SEAL_SHRINK | SEAL_GROW
 * Test whether SEAL_SHRINK | SEAL_GROW actually prevents resizing
 */
अटल व्योम test_seal_resize(व्योम)
अणु
	पूर्णांक fd;

	म_लिखो("%s SEAL-RESIZE\n", memfd_str);

	fd = mfd_निश्चित_new("kern_memfd_seal_resize",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_SHRINK | F_SEAL_GROW);
	mfd_निश्चित_has_seals(fd, F_SEAL_SHRINK | F_SEAL_GROW);

	mfd_निश्चित_पढ़ो(fd);
	mfd_निश्चित_ग_लिखो(fd);
	mfd_fail_shrink(fd);
	mfd_fail_grow(fd);
	mfd_fail_grow_ग_लिखो(fd);

	बंद(fd);
पूर्ण

/*
 * Test sharing via dup()
 * Test that seals are shared between dupped FDs and they're all equal.
 */
अटल व्योम test_share_dup(अक्षर *banner, अक्षर *b_suffix)
अणु
	पूर्णांक fd, fd2;

	म_लिखो("%s %s %s\n", memfd_str, banner, b_suffix);

	fd = mfd_निश्चित_new("kern_memfd_share_dup",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);

	fd2 = mfd_निश्चित_dup(fd);
	mfd_निश्चित_has_seals(fd2, 0);

	mfd_निश्चित_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE);

	mfd_निश्चित_add_seals(fd2, F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK);

	mfd_निश्चित_add_seals(fd, F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK | F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK | F_SEAL_SEAL);

	mfd_fail_add_seals(fd, F_SEAL_GROW);
	mfd_fail_add_seals(fd2, F_SEAL_GROW);
	mfd_fail_add_seals(fd, F_SEAL_SEAL);
	mfd_fail_add_seals(fd2, F_SEAL_SEAL);

	बंद(fd2);

	mfd_fail_add_seals(fd, F_SEAL_GROW);
	बंद(fd);
पूर्ण

/*
 * Test sealing with active mmap()s
 * Modअगरying seals is only allowed अगर no other mmap() refs exist.
 */
अटल व्योम test_share_mmap(अक्षर *banner, अक्षर *b_suffix)
अणु
	पूर्णांक fd;
	व्योम *p;

	म_लिखो("%s %s %s\n", memfd_str,  banner, b_suffix);

	fd = mfd_निश्चित_new("kern_memfd_share_mmap",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);

	/* shared/writable ref prevents sealing WRITE, but allows others */
	p = mfd_निश्चित_mmap_shared(fd);
	mfd_fail_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd, F_SEAL_SHRINK);
	munmap(p, mfd_def_size);

	/* पढ़ोable ref allows sealing */
	p = mfd_निश्चित_mmap_निजी(fd);
	mfd_निश्चित_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK);
	munmap(p, mfd_def_size);

	बंद(fd);
पूर्ण

/*
 * Test sealing with खोलो(/proc/self/fd/%d)
 * Via /proc we can get access to a separate file-context क्रम the same memfd.
 * This is *not* like dup(), but like a real separate खोलो(). Make sure the
 * semantics are as expected and we correctly check क्रम RDONLY / WRONLY / RDWR.
 */
अटल व्योम test_share_खोलो(अक्षर *banner, अक्षर *b_suffix)
अणु
	पूर्णांक fd, fd2;

	म_लिखो("%s %s %s\n", memfd_str, banner, b_suffix);

	fd = mfd_निश्चित_new("kern_memfd_share_open",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);

	fd2 = mfd_निश्चित_खोलो(fd, O_RDWR, 0);
	mfd_निश्चित_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE);

	mfd_निश्चित_add_seals(fd2, F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK);

	बंद(fd);
	fd = mfd_निश्चित_खोलो(fd2, O_RDONLY, 0);

	mfd_fail_add_seals(fd, F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK);

	बंद(fd2);
	fd2 = mfd_निश्चित_खोलो(fd, O_RDWR, 0);

	mfd_निश्चित_add_seals(fd2, F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK | F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK | F_SEAL_SEAL);

	बंद(fd2);
	बंद(fd);
पूर्ण

/*
 * Test sharing via विभाजन()
 * Test whether seal-modअगरications work as expected with विभाजनed childs.
 */
अटल व्योम test_share_विभाजन(अक्षर *banner, अक्षर *b_suffix)
अणु
	पूर्णांक fd;
	pid_t pid;

	म_लिखो("%s %s %s\n", memfd_str, banner, b_suffix);

	fd = mfd_निश्चित_new("kern_memfd_share_fork",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_निश्चित_has_seals(fd, 0);

	pid = spawn_idle_thपढ़ो(0);
	mfd_निश्चित_add_seals(fd, F_SEAL_SEAL);
	mfd_निश्चित_has_seals(fd, F_SEAL_SEAL);

	mfd_fail_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_SEAL);

	join_idle_thपढ़ो(pid);

	mfd_fail_add_seals(fd, F_SEAL_WRITE);
	mfd_निश्चित_has_seals(fd, F_SEAL_SEAL);

	बंद(fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	pid_t pid;

	अगर (argc == 2) अणु
		अगर (!म_भेद(argv[1], "hugetlbfs")) अणु
			अचिन्हित दीर्घ hpage_size = शेष_huge_page_size();

			अगर (!hpage_size) अणु
				म_लिखो("Unable to determine huge page size\n");
				पात();
			पूर्ण

			hugetlbfs_test = 1;
			memfd_str = MEMFD_HUGE_STR;
			mfd_def_size = hpage_size * 2;
		पूर्ण अन्यथा अणु
			म_लिखो("Unknown option: %s\n", argv[1]);
			पात();
		पूर्ण
	पूर्ण

	test_create();
	test_basic();

	test_seal_ग_लिखो();
	test_seal_future_ग_लिखो();
	test_seal_shrink();
	test_seal_grow();
	test_seal_resize();

	test_share_dup("SHARE-DUP", "");
	test_share_mmap("SHARE-MMAP", "");
	test_share_खोलो("SHARE-OPEN", "");
	test_share_विभाजन("SHARE-FORK", "");

	/* Run test-suite in a multi-thपढ़ोed environment with a shared
	 * file-table. */
	pid = spawn_idle_thपढ़ो(CLONE_खाताS | CLONE_FS | CLONE_VM);
	test_share_dup("SHARE-DUP", SHARED_FT_STR);
	test_share_mmap("SHARE-MMAP", SHARED_FT_STR);
	test_share_खोलो("SHARE-OPEN", SHARED_FT_STR);
	test_share_विभाजन("SHARE-FORK", SHARED_FT_STR);
	join_idle_thपढ़ो(pid);

	म_लिखो("memfd: DONE\n");

	वापस 0;
पूर्ण
