<शैली गुरु>
/*
 * Copyright तऊ 2018 Alexey Dobriyan <aकरोbriyan@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
// Test that /proc/$KERNEL_THREAD/fd/ is empty.

#अघोषित न_संशोधन
#समावेश <sys/syscall.h>
#समावेश <निश्चित.स>
#समावेश <dirent.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

#समावेश "proc.h"

#घोषणा PF_KHTREAD 0x00200000

/*
 * Test क्रम kernel thपढ़ोness atomically with खोलोat().
 *
 * Return /proc/$PID/fd descriptor अगर process is kernel thपढ़ो.
 * Return -1 अगर a process is userspace process.
 */
अटल पूर्णांक kernel_thपढ़ो_fd(अचिन्हित पूर्णांक pid)
अणु
	अचिन्हित पूर्णांक flags = 0;
	अक्षर buf[4096];
	पूर्णांक dir_fd, fd;
	sमाप_प्रकार rv;

	snम_लिखो(buf, माप(buf), "/proc/%u", pid);
	dir_fd = खोलो(buf, O_RDONLY|O_सूचीECTORY);
	अगर (dir_fd == -1)
		वापस -1;

	/*
	 * Believe it or not, काष्ठा task_काष्ठा::flags is directly exposed
	 * to userspace!
	 */
	fd = खोलोat(dir_fd, "stat", O_RDONLY);
	अगर (fd == -1) अणु
		बंद(dir_fd);
		वापस -1;
	पूर्ण
	rv = पढ़ो(fd, buf, माप(buf));
	बंद(fd);
	अगर (0 < rv && rv <= माप(buf)) अणु
		अचिन्हित दीर्घ दीर्घ flags_ull;
		अक्षर *p, *end;
		पूर्णांक i;

		निश्चित(buf[rv - 1] == '\n');
		buf[rv - 1] = '\0';

		/* Search backwards: ->comm can contain whitespace and ')'. */
		क्रम (i = 0; i < 43; i++) अणु
			p = म_खोजप(buf, ' ');
			निश्चित(p);
			*p = '\0';
		पूर्ण

		p = म_खोजप(buf, ' ');
		निश्चित(p);

		flags_ull = xम_से_अदीर्घl(p + 1, &end);
		निश्चित(*end == '\0');
		निश्चित(flags_ull == (अचिन्हित पूर्णांक)flags_ull);

		flags = flags_ull;
	पूर्ण

	fd = -1;
	अगर (flags & PF_KHTREAD) अणु
		fd = खोलोat(dir_fd, "fd", O_RDONLY|O_सूचीECTORY);
	पूर्ण
	बंद(dir_fd);
	वापस fd;
पूर्ण

अटल व्योम test_सूची_पढ़ो(पूर्णांक fd)
अणु
	सूची *d;
	काष्ठा dirent *de;

	d = fकरोpendir(fd);
	निश्चित(d);

	de = xसूची_पढ़ो(d);
	निश्चित(streq(de->d_name, "."));
	निश्चित(de->d_type == DT_सूची);

	de = xसूची_पढ़ो(d);
	निश्चित(streq(de->d_name, ".."));
	निश्चित(de->d_type == DT_सूची);

	de = xसूची_पढ़ो(d);
	निश्चित(!de);
पूर्ण

अटल अंतरभूत पूर्णांक sys_statx(पूर्णांक dirfd, स्थिर अक्षर *pathname, पूर्णांक flags,
			    अचिन्हित पूर्णांक mask, व्योम *stx)
अणु
	वापस syscall(SYS_statx, dirfd, pathname, flags, mask, stx);
पूर्ण

अटल व्योम test_lookup_fail(पूर्णांक fd, स्थिर अक्षर *pathname)
अणु
	अक्षर stx[256] __attribute__((aligned(8)));
	पूर्णांक rv;

	rv = sys_statx(fd, pathname, AT_SYMLINK_NOFOLLOW, 0, (व्योम *)stx);
	निश्चित(rv == -1 && त्रुटि_सं == ENOENT);
पूर्ण

अटल व्योम test_lookup(पूर्णांक fd)
अणु
	अक्षर buf[64];
	अचिन्हित पूर्णांक u;
	पूर्णांक i;

	क्रम (i = पूर्णांक_न्यून; i < पूर्णांक_न्यून + 1024; i++) अणु
		snम_लिखो(buf, माप(buf), "%d", i);
		test_lookup_fail(fd, buf);
	पूर्ण
	क्रम (i = -1024; i < 1024; i++) अणु
		snम_लिखो(buf, माप(buf), "%d", i);
		test_lookup_fail(fd, buf);
	पूर्ण
	क्रम (u = पूर्णांक_उच्च - 1024; u < (अचिन्हित पूर्णांक)पूर्णांक_उच्च + 1024; u++) अणु
		snम_लिखो(buf, माप(buf), "%u", u);
		test_lookup_fail(fd, buf);
	पूर्ण
	क्रम (u = अच_पूर्णांक_उच्च - 1024; u != 0; u++) अणु
		snम_लिखो(buf, माप(buf), "%u", u);
		test_lookup_fail(fd, buf);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	अचिन्हित पूर्णांक pid;
	पूर्णांक fd;

	/*
	 * In theory this will loop indefinitely अगर kernel thपढ़ोs are exiled
	 * from /proc.
	 *
	 * Start with kthपढ़ोd.
	 */
	pid = 2;
	जबतक ((fd = kernel_thपढ़ो_fd(pid)) == -1 && pid < 1024) अणु
		pid++;
	पूर्ण
	/* EACCES अगर run as non-root. */
	अगर (pid >= 1024)
		वापस 1;

	test_सूची_पढ़ो(fd);
	test_lookup(fd);

	वापस 0;
पूर्ण
