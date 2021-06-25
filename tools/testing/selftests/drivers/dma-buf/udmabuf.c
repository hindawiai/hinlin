<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <दो_स्मृति.h>

#समावेश <sys/ioctl.h>
#समावेश <sys/syscall.h>
#समावेश <linux/memfd.h>
#समावेश <linux/udmabuf.h>

#घोषणा TEST_PREFIX	"drivers/dma-buf/udmabuf"
#घोषणा NUM_PAGES       4

अटल पूर्णांक memfd_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_memfd_create, name, flags);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा udmabuf_create create;
	पूर्णांक devfd, memfd, buf, ret;
	off_t size;
	व्योम *mem;

	devfd = खोलो("/dev/udmabuf", O_RDWR);
	अगर (devfd < 0) अणु
		म_लिखो("%s: [skip,no-udmabuf]\n", TEST_PREFIX);
		निकास(77);
	पूर्ण

	memfd = memfd_create("udmabuf-test", MFD_ALLOW_SEALING);
	अगर (memfd < 0) अणु
		म_लिखो("%s: [skip,no-memfd]\n", TEST_PREFIX);
		निकास(77);
	पूर्ण

	ret = fcntl(memfd, F_ADD_SEALS, F_SEAL_SHRINK);
	अगर (ret < 0) अणु
		म_लिखो("%s: [skip,fcntl-add-seals]\n", TEST_PREFIX);
		निकास(77);
	पूर्ण


	size = getpagesize() * NUM_PAGES;
	ret = ftruncate(memfd, size);
	अगर (ret == -1) अणु
		म_लिखो("%s: [FAIL,memfd-truncate]\n", TEST_PREFIX);
		निकास(1);
	पूर्ण

	स_रखो(&create, 0, माप(create));

	/* should fail (offset not page aligned) */
	create.memfd  = memfd;
	create.offset = getpagesize()/2;
	create.size   = getpagesize();
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	अगर (buf >= 0) अणु
		म_लिखो("%s: [FAIL,test-1]\n", TEST_PREFIX);
		निकास(1);
	पूर्ण

	/* should fail (size not multiple of page) */
	create.memfd  = memfd;
	create.offset = 0;
	create.size   = getpagesize()/2;
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	अगर (buf >= 0) अणु
		म_लिखो("%s: [FAIL,test-2]\n", TEST_PREFIX);
		निकास(1);
	पूर्ण

	/* should fail (not memfd) */
	create.memfd  = 0; /* मानक_निवेश */
	create.offset = 0;
	create.size   = size;
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	अगर (buf >= 0) अणु
		म_लिखो("%s: [FAIL,test-3]\n", TEST_PREFIX);
		निकास(1);
	पूर्ण

	/* should work */
	create.memfd  = memfd;
	create.offset = 0;
	create.size   = size;
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	अगर (buf < 0) अणु
		म_लिखो("%s: [FAIL,test-4]\n", TEST_PREFIX);
		निकास(1);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "%s: ok\n", TEST_PREFIX);
	बंद(buf);
	बंद(memfd);
	बंद(devfd);
	वापस 0;
पूर्ण
