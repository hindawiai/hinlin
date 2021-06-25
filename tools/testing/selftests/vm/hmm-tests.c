<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HMM stands क्रम Heterogeneous Memory Management, it is a helper layer inside
 * the linux kernel to help device drivers mirror a process address space in
 * the device. This allows the device to use the same address space which
 * makes communication and data exchange a lot easier.
 *
 * This framework's sole purpose is to exercise various code paths inside
 * the kernel to make sure that HMM perक्रमms as expected and to flush out any
 * bugs.
 */

#समावेश "../kselftest_harness.h"

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <strings.h>
#समावेश <समय.स>
#समावेश <pthपढ़ो.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <sys/ioctl.h>

#समावेश "./local_config.h"
#अगर_घोषित LOCAL_CONFIG_HAVE_LIBHUGETLBFS
#समावेश <hugetlbfs.h>
#पूर्ण_अगर

/*
 * This is a निजी UAPI to the kernel test module so it isn't exported
 * in the usual include/uapi/... directory.
 */
#समावेश "../../../../lib/test_hmm_uapi.h"

काष्ठा hmm_buffer अणु
	व्योम		*ptr;
	व्योम		*mirror;
	अचिन्हित दीर्घ	size;
	पूर्णांक		fd;
	uपूर्णांक64_t	cpages;
	uपूर्णांक64_t	faults;
पूर्ण;

#घोषणा TWOMEG		(1 << 21)
#घोषणा HMM_BUFFER_SIZE (1024 << 12)
#घोषणा HMM_PATH_MAX    64
#घोषणा NTIMES		10

#घोषणा ALIGN(x, a) (((x) + (a - 1)) & (~((a) - 1)))

FIXTURE(hmm)
अणु
	पूर्णांक		fd;
	अचिन्हित पूर्णांक	page_size;
	अचिन्हित पूर्णांक	page_shअगरt;
पूर्ण;

FIXTURE(hmm2)
अणु
	पूर्णांक		fd0;
	पूर्णांक		fd1;
	अचिन्हित पूर्णांक	page_size;
	अचिन्हित पूर्णांक	page_shअगरt;
पूर्ण;

अटल पूर्णांक hmm_खोलो(पूर्णांक unit)
अणु
	अक्षर pathname[HMM_PATH_MAX];
	पूर्णांक fd;

	snम_लिखो(pathname, माप(pathname), "/dev/hmm_dmirror%d", unit);
	fd = खोलो(pathname, O_RDWR, 0);
	अगर (fd < 0)
		ख_लिखो(मानक_त्रुटि, "could not open hmm dmirror driver (%s)\n",
			pathname);
	वापस fd;
पूर्ण

FIXTURE_SETUP(hmm)
अणु
	self->page_size = sysconf(_SC_PAGE_SIZE);
	self->page_shअगरt = ffs(self->page_size) - 1;

	self->fd = hmm_खोलो(0);
	ASSERT_GE(self->fd, 0);
पूर्ण

FIXTURE_SETUP(hmm2)
अणु
	self->page_size = sysconf(_SC_PAGE_SIZE);
	self->page_shअगरt = ffs(self->page_size) - 1;

	self->fd0 = hmm_खोलो(0);
	ASSERT_GE(self->fd0, 0);
	self->fd1 = hmm_खोलो(1);
	ASSERT_GE(self->fd1, 0);
पूर्ण

FIXTURE_TEARDOWN(hmm)
अणु
	पूर्णांक ret = बंद(self->fd);

	ASSERT_EQ(ret, 0);
	self->fd = -1;
पूर्ण

FIXTURE_TEARDOWN(hmm2)
अणु
	पूर्णांक ret = बंद(self->fd0);

	ASSERT_EQ(ret, 0);
	self->fd0 = -1;

	ret = बंद(self->fd1);
	ASSERT_EQ(ret, 0);
	self->fd1 = -1;
पूर्ण

अटल पूर्णांक hmm_dmirror_cmd(पूर्णांक fd,
			   अचिन्हित दीर्घ request,
			   काष्ठा hmm_buffer *buffer,
			   अचिन्हित दीर्घ npages)
अणु
	काष्ठा hmm_dmirror_cmd cmd;
	पूर्णांक ret;

	/* Simulate a device पढ़ोing प्रणाली memory. */
	cmd.addr = (__u64)buffer->ptr;
	cmd.ptr = (__u64)buffer->mirror;
	cmd.npages = npages;

	क्रम (;;) अणु
		ret = ioctl(fd, request, &cmd);
		अगर (ret == 0)
			अवरोध;
		अगर (त्रुटि_सं == EINTR)
			जारी;
		वापस -त्रुटि_सं;
	पूर्ण
	buffer->cpages = cmd.cpages;
	buffer->faults = cmd.faults;

	वापस 0;
पूर्ण

अटल व्योम hmm_buffer_मुक्त(काष्ठा hmm_buffer *buffer)
अणु
	अगर (buffer == शून्य)
		वापस;

	अगर (buffer->ptr)
		munmap(buffer->ptr, buffer->size);
	मुक्त(buffer->mirror);
	मुक्त(buffer);
पूर्ण

/*
 * Create a temporary file that will be deleted on बंद.
 */
अटल पूर्णांक hmm_create_file(अचिन्हित दीर्घ size)
अणु
	अक्षर path[HMM_PATH_MAX];
	पूर्णांक fd;

	म_नकल(path, "/tmp");
	fd = खोलो(path, O_TMPखाता | O_EXCL | O_RDWR, 0600);
	अगर (fd >= 0) अणु
		पूर्णांक r;

		करो अणु
			r = ftruncate(fd, size);
		पूर्ण जबतक (r == -1 && त्रुटि_सं == EINTR);
		अगर (!r)
			वापस fd;
		बंद(fd);
	पूर्ण
	वापस -1;
पूर्ण

/*
 * Return a अक्रमom अचिन्हित number.
 */
अटल अचिन्हित पूर्णांक hmm_अक्रमom(व्योम)
अणु
	अटल पूर्णांक fd = -1;
	अचिन्हित पूर्णांक r;

	अगर (fd < 0) अणु
		fd = खोलो("/dev/urandom", O_RDONLY);
		अगर (fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d failed to open /dev/urandom\n",
					__खाता__, __LINE__);
			वापस ~0U;
		पूर्ण
	पूर्ण
	पढ़ो(fd, &r, माप(r));
	वापस r;
पूर्ण

अटल व्योम hmm_nanosleep(अचिन्हित पूर्णांक n)
अणु
	काष्ठा बारpec t;

	t.tv_sec = 0;
	t.tv_nsec = n;
	nanosleep(&t, शून्य);
पूर्ण

/*
 * Simple शून्य test of device खोलो/बंद.
 */
TEST_F(hmm, खोलो_बंद)
अणु
पूर्ण

/*
 * Read निजी anonymous memory.
 */
TEST_F(hmm, anon_पढ़ो)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;
	पूर्णांक val;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/*
	 * Initialize buffer in प्रणाली memory but leave the first two pages
	 * zero (pte_none and pfn_zero).
	 */
	i = 2 * self->page_size / माप(*ptr);
	क्रम (ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Set buffer permission to पढ़ो-only. */
	ret = mprotect(buffer->ptr, size, PROT_READ);
	ASSERT_EQ(ret, 0);

	/* Populate the CPU page table with a special zero page. */
	val = *(पूर्णांक *)(buffer->ptr + self->page_size);
	ASSERT_EQ(val, 0);

	/* Simulate a device पढ़ोing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_READ, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device पढ़ो. */
	ptr = buffer->mirror;
	क्रम (i = 0; i < 2 * self->page_size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], 0);
	क्रम (; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Read निजी anonymous memory which has been रक्षित with
 * mprotect() PROT_NONE.
 */
TEST_F(hmm, anon_पढ़ो_prot)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize buffer in प्रणाली memory. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Initialize mirror buffer so we can verअगरy it isn't written. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = -i;

	/* Protect buffer from पढ़ोing. */
	ret = mprotect(buffer->ptr, size, PROT_NONE);
	ASSERT_EQ(ret, 0);

	/* Simulate a device पढ़ोing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_READ, buffer, npages);
	ASSERT_EQ(ret, -EFAULT);

	/* Allow CPU to पढ़ो the buffer so we can check it. */
	ret = mprotect(buffer->ptr, size, PROT_READ);
	ASSERT_EQ(ret, 0);
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], -i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Write निजी anonymous memory.
 */
TEST_F(hmm, anon_ग_लिखो)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Write निजी anonymous memory which has been रक्षित with
 * mprotect() PROT_READ.
 */
TEST_F(hmm, anon_ग_लिखो_prot)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Simulate a device पढ़ोing a zero page of memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_READ, buffer, 1);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, 1);
	ASSERT_EQ(buffer->faults, 1);

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, -EPERM);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], 0);

	/* Now allow writing and see that the zero page is replaced. */
	ret = mprotect(buffer->ptr, size, PROT_WRITE | PROT_READ);
	ASSERT_EQ(ret, 0);

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Check that a device writing an anonymous निजी mapping
 * will copy-on-ग_लिखो अगर a child process inherits the mapping.
 */
TEST_F(hmm, anon_ग_लिखो_child)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	pid_t pid;
	पूर्णांक child_fd;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize buffer->ptr so we can tell अगर it is written. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = -i;

	pid = विभाजन();
	अगर (pid == -1)
		ASSERT_EQ(pid, 0);
	अगर (pid != 0) अणु
		रुकोpid(pid, &ret, 0);
		ASSERT_EQ(WIFEXITED(ret), 1);

		/* Check that the parent's buffer did not change. */
		क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
			ASSERT_EQ(ptr[i], i);
		वापस;
	पूर्ण

	/* Check that we see the parent's values. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], -i);

	/* The child process needs its own mirror to its own mm. */
	child_fd = hmm_खोलो(0);
	ASSERT_GE(child_fd, 0);

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(child_fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], -i);

	बंद(child_fd);
	निकास(0);
पूर्ण

/*
 * Check that a device writing an anonymous shared mapping
 * will not copy-on-ग_लिखो अगर a child process inherits the mapping.
 */
TEST_F(hmm, anon_ग_लिखो_child_shared)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	pid_t pid;
	पूर्णांक child_fd;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_SHARED | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize buffer->ptr so we can tell अगर it is written. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = -i;

	pid = विभाजन();
	अगर (pid == -1)
		ASSERT_EQ(pid, 0);
	अगर (pid != 0) अणु
		रुकोpid(pid, &ret, 0);
		ASSERT_EQ(WIFEXITED(ret), 1);

		/* Check that the parent's buffer did change. */
		क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
			ASSERT_EQ(ptr[i], -i);
		वापस;
	पूर्ण

	/* Check that we see the parent's values. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], -i);

	/* The child process needs its own mirror to its own mm. */
	child_fd = hmm_खोलो(0);
	ASSERT_GE(child_fd, 0);

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(child_fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], -i);

	बंद(child_fd);
	निकास(0);
पूर्ण

/*
 * Write निजी anonymous huge page.
 */
TEST_F(hmm, anon_ग_लिखो_huge)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	व्योम *old_ptr;
	व्योम *map;
	पूर्णांक *ptr;
	पूर्णांक ret;

	size = 2 * TWOMEG;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	size = TWOMEG;
	npages = size >> self->page_shअगरt;
	map = (व्योम *)ALIGN((uपूर्णांकptr_t)buffer->ptr, size);
	ret = madvise(map, size, MADV_HUGEPAGE);
	ASSERT_EQ(ret, 0);
	old_ptr = buffer->ptr;
	buffer->ptr = map;

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	buffer->ptr = old_ptr;
	hmm_buffer_मुक्त(buffer);
पूर्ण

#अगर_घोषित LOCAL_CONFIG_HAVE_LIBHUGETLBFS
/*
 * Write huge TLBFS page.
 */
TEST_F(hmm, anon_ग_लिखो_hugetlbfs)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;
	दीर्घ pagesizes[4];
	पूर्णांक n, idx;

	/* Skip test अगर we can't allocate a hugetlbfs page. */

	n = gethugepagesizes(pagesizes, 4);
	अगर (n <= 0)
		SKIP(वापस, "Huge page size could not be determined");
	क्रम (idx = 0; --n > 0; ) अणु
		अगर (pagesizes[n] < pagesizes[idx])
			idx = n;
	पूर्ण
	size = ALIGN(TWOMEG, pagesizes[idx]);
	npages = size >> self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->ptr = get_hugepage_region(size, GHR_STRICT);
	अगर (buffer->ptr == शून्य) अणु
		मुक्त(buffer);
		SKIP(वापस, "Huge page could not be allocated");
	पूर्ण

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	मुक्त_hugepage_region(buffer->ptr);
	buffer->ptr = शून्य;
	hmm_buffer_मुक्त(buffer);
पूर्ण
#पूर्ण_अगर /* LOCAL_CONFIG_HAVE_LIBHUGETLBFS */

/*
 * Read mmap'ed file memory.
 */
TEST_F(hmm, file_पढ़ो)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;
	पूर्णांक fd;
	sमाप_प्रकार len;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	fd = hmm_create_file(size);
	ASSERT_GE(fd, 0);

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = fd;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	/* Write initial contents of the file. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = i;
	len = pग_लिखो(fd, buffer->mirror, size, 0);
	ASSERT_EQ(len, size);
	स_रखो(buffer->mirror, 0, size);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ,
			   MAP_SHARED,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Simulate a device पढ़ोing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_READ, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Write mmap'ed file memory.
 */
TEST_F(hmm, file_ग_लिखो)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;
	पूर्णांक fd;
	sमाप_प्रकार len;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	fd = hmm_create_file(size);
	ASSERT_GE(fd, 0);

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = fd;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_SHARED,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize data that the device will ग_लिखो to buffer->ptr. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Simulate a device writing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_WRITE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device wrote. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	/* Check that the device also wrote the file. */
	len = pपढ़ो(fd, buffer->mirror, size, 0);
	ASSERT_EQ(len, size);
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Migrate anonymous memory to device निजी memory.
 */
TEST_F(hmm, migrate)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize buffer in प्रणाली memory. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Migrate memory to device. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_MIGRATE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Migrate anonymous memory to device निजी memory and fault some of it back
 * to प्रणाली memory, then try migrating the resulting mix of प्रणाली and device
 * निजी memory to the device.
 */
TEST_F(hmm, migrate_fault)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize buffer in प्रणाली memory. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Migrate memory to device. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_MIGRATE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	/* Fault half the pages back to प्रणाली memory and check them. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / (2 * माप(*ptr)); ++i)
		ASSERT_EQ(ptr[i], i);

	/* Migrate memory to the device again. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_MIGRATE, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Migrate anonymous shared memory to device निजी memory.
 */
TEST_F(hmm, migrate_shared)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_SHARED | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Migrate memory to device. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_MIGRATE, buffer, npages);
	ASSERT_EQ(ret, -ENOENT);

	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Try to migrate various memory types to device निजी memory.
 */
TEST_F(hmm2, migrate_mixed)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	पूर्णांक *ptr;
	अचिन्हित अक्षर *p;
	पूर्णांक ret;
	पूर्णांक val;

	npages = 6;
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(size);
	ASSERT_NE(buffer->mirror, शून्य);

	/* Reserve a range of addresses. */
	buffer->ptr = mmap(शून्य, size,
			   PROT_NONE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);
	p = buffer->ptr;

	/* Migrating a रक्षित area should be an error. */
	ret = hmm_dmirror_cmd(self->fd1, HMM_DMIRROR_MIGRATE, buffer, npages);
	ASSERT_EQ(ret, -EINVAL);

	/* Punch a hole after the first page address. */
	ret = munmap(buffer->ptr + self->page_size, self->page_size);
	ASSERT_EQ(ret, 0);

	/* We expect an error अगर the vma करोesn't cover the range. */
	ret = hmm_dmirror_cmd(self->fd1, HMM_DMIRROR_MIGRATE, buffer, 3);
	ASSERT_EQ(ret, -EINVAL);

	/* Page 2 will be a पढ़ो-only zero page. */
	ret = mprotect(buffer->ptr + 2 * self->page_size, self->page_size,
				PROT_READ);
	ASSERT_EQ(ret, 0);
	ptr = (पूर्णांक *)(buffer->ptr + 2 * self->page_size);
	val = *ptr + 3;
	ASSERT_EQ(val, 3);

	/* Page 3 will be पढ़ो-only. */
	ret = mprotect(buffer->ptr + 3 * self->page_size, self->page_size,
				PROT_READ | PROT_WRITE);
	ASSERT_EQ(ret, 0);
	ptr = (पूर्णांक *)(buffer->ptr + 3 * self->page_size);
	*ptr = val;
	ret = mprotect(buffer->ptr + 3 * self->page_size, self->page_size,
				PROT_READ);
	ASSERT_EQ(ret, 0);

	/* Page 4-5 will be पढ़ो-ग_लिखो. */
	ret = mprotect(buffer->ptr + 4 * self->page_size, 2 * self->page_size,
				PROT_READ | PROT_WRITE);
	ASSERT_EQ(ret, 0);
	ptr = (पूर्णांक *)(buffer->ptr + 4 * self->page_size);
	*ptr = val;
	ptr = (पूर्णांक *)(buffer->ptr + 5 * self->page_size);
	*ptr = val;

	/* Now try to migrate pages 2-5 to device 1. */
	buffer->ptr = p + 2 * self->page_size;
	ret = hmm_dmirror_cmd(self->fd1, HMM_DMIRROR_MIGRATE, buffer, 4);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, 4);

	/* Page 5 won't be migrated to device 0 because it's on device 1. */
	buffer->ptr = p + 5 * self->page_size;
	ret = hmm_dmirror_cmd(self->fd0, HMM_DMIRROR_MIGRATE, buffer, 1);
	ASSERT_EQ(ret, -ENOENT);
	buffer->ptr = p;

	buffer->ptr = p;
	hmm_buffer_मुक्त(buffer);
पूर्ण

/*
 * Migrate anonymous memory to device निजी memory and fault it back to प्रणाली
 * memory multiple बार.
 */
TEST_F(hmm, migrate_multiple)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ c;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	क्रम (c = 0; c < NTIMES; c++) अणु
		buffer = दो_स्मृति(माप(*buffer));
		ASSERT_NE(buffer, शून्य);

		buffer->fd = -1;
		buffer->size = size;
		buffer->mirror = दो_स्मृति(size);
		ASSERT_NE(buffer->mirror, शून्य);

		buffer->ptr = mmap(शून्य, size,
				   PROT_READ | PROT_WRITE,
				   MAP_PRIVATE | MAP_ANONYMOUS,
				   buffer->fd, 0);
		ASSERT_NE(buffer->ptr, MAP_FAILED);

		/* Initialize buffer in प्रणाली memory. */
		क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
			ptr[i] = i;

		/* Migrate memory to device. */
		ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_MIGRATE, buffer,
				      npages);
		ASSERT_EQ(ret, 0);
		ASSERT_EQ(buffer->cpages, npages);

		/* Check what the device पढ़ो. */
		क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
			ASSERT_EQ(ptr[i], i);

		/* Fault pages back to प्रणाली memory and check them. */
		क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
			ASSERT_EQ(ptr[i], i);

		hmm_buffer_मुक्त(buffer);
	पूर्ण
पूर्ण

/*
 * Read anonymous memory multiple बार.
 */
TEST_F(hmm, anon_पढ़ो_multiple)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ c;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	क्रम (c = 0; c < NTIMES; c++) अणु
		buffer = दो_स्मृति(माप(*buffer));
		ASSERT_NE(buffer, शून्य);

		buffer->fd = -1;
		buffer->size = size;
		buffer->mirror = दो_स्मृति(size);
		ASSERT_NE(buffer->mirror, शून्य);

		buffer->ptr = mmap(शून्य, size,
				   PROT_READ | PROT_WRITE,
				   MAP_PRIVATE | MAP_ANONYMOUS,
				   buffer->fd, 0);
		ASSERT_NE(buffer->ptr, MAP_FAILED);

		/* Initialize buffer in प्रणाली memory. */
		क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
			ptr[i] = i + c;

		/* Simulate a device पढ़ोing प्रणाली memory. */
		ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_READ, buffer,
				      npages);
		ASSERT_EQ(ret, 0);
		ASSERT_EQ(buffer->cpages, npages);
		ASSERT_EQ(buffer->faults, 1);

		/* Check what the device पढ़ो. */
		क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
			ASSERT_EQ(ptr[i], i + c);

		hmm_buffer_मुक्त(buffer);
	पूर्ण
पूर्ण

व्योम *unmap_buffer(व्योम *p)
अणु
	काष्ठा hmm_buffer *buffer = p;

	/* Delay क्रम a bit and then unmap buffer जबतक it is being पढ़ो. */
	hmm_nanosleep(hmm_अक्रमom() % 32000);
	munmap(buffer->ptr + buffer->size / 2, buffer->size / 2);
	buffer->ptr = शून्य;

	वापस शून्य;
पूर्ण

/*
 * Try पढ़ोing anonymous memory जबतक it is being unmapped.
 */
TEST_F(hmm, anon_tearकरोwn)
अणु
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ c;
	व्योम *ret;

	npages = ALIGN(HMM_BUFFER_SIZE, self->page_size) >> self->page_shअगरt;
	ASSERT_NE(npages, 0);
	size = npages << self->page_shअगरt;

	क्रम (c = 0; c < NTIMES; ++c) अणु
		pthपढ़ो_t thपढ़ो;
		काष्ठा hmm_buffer *buffer;
		अचिन्हित दीर्घ i;
		पूर्णांक *ptr;
		पूर्णांक rc;

		buffer = दो_स्मृति(माप(*buffer));
		ASSERT_NE(buffer, शून्य);

		buffer->fd = -1;
		buffer->size = size;
		buffer->mirror = दो_स्मृति(size);
		ASSERT_NE(buffer->mirror, शून्य);

		buffer->ptr = mmap(शून्य, size,
				   PROT_READ | PROT_WRITE,
				   MAP_PRIVATE | MAP_ANONYMOUS,
				   buffer->fd, 0);
		ASSERT_NE(buffer->ptr, MAP_FAILED);

		/* Initialize buffer in प्रणाली memory. */
		क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
			ptr[i] = i + c;

		rc = pthपढ़ो_create(&thपढ़ो, शून्य, unmap_buffer, buffer);
		ASSERT_EQ(rc, 0);

		/* Simulate a device पढ़ोing प्रणाली memory. */
		rc = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_READ, buffer,
				     npages);
		अगर (rc == 0) अणु
			ASSERT_EQ(buffer->cpages, npages);
			ASSERT_EQ(buffer->faults, 1);

			/* Check what the device पढ़ो. */
			क्रम (i = 0, ptr = buffer->mirror;
			     i < size / माप(*ptr);
			     ++i)
				ASSERT_EQ(ptr[i], i + c);
		पूर्ण

		pthपढ़ो_join(thपढ़ो, &ret);
		hmm_buffer_मुक्त(buffer);
	पूर्ण
पूर्ण

/*
 * Test memory snapshot without faulting in pages accessed by the device.
 */
TEST_F(hmm2, snapshot)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	पूर्णांक *ptr;
	अचिन्हित अक्षर *p;
	अचिन्हित अक्षर *m;
	पूर्णांक ret;
	पूर्णांक val;

	npages = 7;
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(npages);
	ASSERT_NE(buffer->mirror, शून्य);

	/* Reserve a range of addresses. */
	buffer->ptr = mmap(शून्य, size,
			   PROT_NONE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);
	p = buffer->ptr;

	/* Punch a hole after the first page address. */
	ret = munmap(buffer->ptr + self->page_size, self->page_size);
	ASSERT_EQ(ret, 0);

	/* Page 2 will be पढ़ो-only zero page. */
	ret = mprotect(buffer->ptr + 2 * self->page_size, self->page_size,
				PROT_READ);
	ASSERT_EQ(ret, 0);
	ptr = (पूर्णांक *)(buffer->ptr + 2 * self->page_size);
	val = *ptr + 3;
	ASSERT_EQ(val, 3);

	/* Page 3 will be पढ़ो-only. */
	ret = mprotect(buffer->ptr + 3 * self->page_size, self->page_size,
				PROT_READ | PROT_WRITE);
	ASSERT_EQ(ret, 0);
	ptr = (पूर्णांक *)(buffer->ptr + 3 * self->page_size);
	*ptr = val;
	ret = mprotect(buffer->ptr + 3 * self->page_size, self->page_size,
				PROT_READ);
	ASSERT_EQ(ret, 0);

	/* Page 4-6 will be पढ़ो-ग_लिखो. */
	ret = mprotect(buffer->ptr + 4 * self->page_size, 3 * self->page_size,
				PROT_READ | PROT_WRITE);
	ASSERT_EQ(ret, 0);
	ptr = (पूर्णांक *)(buffer->ptr + 4 * self->page_size);
	*ptr = val;

	/* Page 5 will be migrated to device 0. */
	buffer->ptr = p + 5 * self->page_size;
	ret = hmm_dmirror_cmd(self->fd0, HMM_DMIRROR_MIGRATE, buffer, 1);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, 1);

	/* Page 6 will be migrated to device 1. */
	buffer->ptr = p + 6 * self->page_size;
	ret = hmm_dmirror_cmd(self->fd1, HMM_DMIRROR_MIGRATE, buffer, 1);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, 1);

	/* Simulate a device snapshotting CPU pagetables. */
	buffer->ptr = p;
	ret = hmm_dmirror_cmd(self->fd0, HMM_DMIRROR_SNAPSHOT, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);

	/* Check what the device saw. */
	m = buffer->mirror;
	ASSERT_EQ(m[0], HMM_DMIRROR_PROT_ERROR);
	ASSERT_EQ(m[1], HMM_DMIRROR_PROT_ERROR);
	ASSERT_EQ(m[2], HMM_DMIRROR_PROT_ZERO | HMM_DMIRROR_PROT_READ);
	ASSERT_EQ(m[3], HMM_DMIRROR_PROT_READ);
	ASSERT_EQ(m[4], HMM_DMIRROR_PROT_WRITE);
	ASSERT_EQ(m[5], HMM_DMIRROR_PROT_DEV_PRIVATE_LOCAL |
			HMM_DMIRROR_PROT_WRITE);
	ASSERT_EQ(m[6], HMM_DMIRROR_PROT_NONE);

	hmm_buffer_मुक्त(buffer);
पूर्ण

#अगर_घोषित LOCAL_CONFIG_HAVE_LIBHUGETLBFS
/*
 * Test the hmm_range_fault() HMM_PFN_PMD flag क्रम large pages that
 * should be mapped by a large page table entry.
 */
TEST_F(hmm, compound)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	पूर्णांक *ptr;
	अचिन्हित अक्षर *m;
	पूर्णांक ret;
	दीर्घ pagesizes[4];
	पूर्णांक n, idx;
	अचिन्हित दीर्घ i;

	/* Skip test अगर we can't allocate a hugetlbfs page. */

	n = gethugepagesizes(pagesizes, 4);
	अगर (n <= 0)
		वापस;
	क्रम (idx = 0; --n > 0; ) अणु
		अगर (pagesizes[n] < pagesizes[idx])
			idx = n;
	पूर्ण
	size = ALIGN(TWOMEG, pagesizes[idx]);
	npages = size >> self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->ptr = get_hugepage_region(size, GHR_STRICT);
	अगर (buffer->ptr == शून्य) अणु
		मुक्त(buffer);
		वापस;
	पूर्ण

	buffer->size = size;
	buffer->mirror = दो_स्मृति(npages);
	ASSERT_NE(buffer->mirror, शून्य);

	/* Initialize the pages the device will snapshot in buffer->ptr. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Simulate a device snapshotting CPU pagetables. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_SNAPSHOT, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);

	/* Check what the device saw. */
	m = buffer->mirror;
	क्रम (i = 0; i < npages; ++i)
		ASSERT_EQ(m[i], HMM_DMIRROR_PROT_WRITE |
				HMM_DMIRROR_PROT_PMD);

	/* Make the region पढ़ो-only. */
	ret = mprotect(buffer->ptr, size, PROT_READ);
	ASSERT_EQ(ret, 0);

	/* Simulate a device snapshotting CPU pagetables. */
	ret = hmm_dmirror_cmd(self->fd, HMM_DMIRROR_SNAPSHOT, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);

	/* Check what the device saw. */
	m = buffer->mirror;
	क्रम (i = 0; i < npages; ++i)
		ASSERT_EQ(m[i], HMM_DMIRROR_PROT_READ |
				HMM_DMIRROR_PROT_PMD);

	मुक्त_hugepage_region(buffer->ptr);
	buffer->ptr = शून्य;
	hmm_buffer_मुक्त(buffer);
पूर्ण
#पूर्ण_अगर /* LOCAL_CONFIG_HAVE_LIBHUGETLBFS */

/*
 * Test two devices पढ़ोing the same memory (द्विगुन mapped).
 */
TEST_F(hmm2, द्विगुन_map)
अणु
	काष्ठा hmm_buffer *buffer;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ i;
	पूर्णांक *ptr;
	पूर्णांक ret;

	npages = 6;
	size = npages << self->page_shअगरt;

	buffer = दो_स्मृति(माप(*buffer));
	ASSERT_NE(buffer, शून्य);

	buffer->fd = -1;
	buffer->size = size;
	buffer->mirror = दो_स्मृति(npages);
	ASSERT_NE(buffer->mirror, शून्य);

	/* Reserve a range of addresses. */
	buffer->ptr = mmap(शून्य, size,
			   PROT_READ | PROT_WRITE,
			   MAP_PRIVATE | MAP_ANONYMOUS,
			   buffer->fd, 0);
	ASSERT_NE(buffer->ptr, MAP_FAILED);

	/* Initialize buffer in प्रणाली memory. */
	क्रम (i = 0, ptr = buffer->ptr; i < size / माप(*ptr); ++i)
		ptr[i] = i;

	/* Make region पढ़ो-only. */
	ret = mprotect(buffer->ptr, size, PROT_READ);
	ASSERT_EQ(ret, 0);

	/* Simulate device 0 पढ़ोing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd0, HMM_DMIRROR_READ, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	/* Simulate device 1 पढ़ोing प्रणाली memory. */
	ret = hmm_dmirror_cmd(self->fd1, HMM_DMIRROR_READ, buffer, npages);
	ASSERT_EQ(ret, 0);
	ASSERT_EQ(buffer->cpages, npages);
	ASSERT_EQ(buffer->faults, 1);

	/* Check what the device पढ़ो. */
	क्रम (i = 0, ptr = buffer->mirror; i < size / माप(*ptr); ++i)
		ASSERT_EQ(ptr[i], i);

	/* Punch a hole after the first page address. */
	ret = munmap(buffer->ptr + self->page_size, self->page_size);
	ASSERT_EQ(ret, 0);

	hmm_buffer_मुक्त(buffer);
पूर्ण

TEST_HARNESS_MAIN
