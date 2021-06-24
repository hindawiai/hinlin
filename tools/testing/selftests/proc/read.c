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
// Test
// 1) पढ़ो and lseek on every file in /proc
// 2) पढ़ोlink of every symlink in /proc
// 3) recursively (1) + (2) क्रम every directory in /proc
// 4) ग_लिखो to /proc/*/clear_refs and /proc/*/task/*/clear_refs
// 5) ग_लिखो to /proc/sysrq-trigger
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <dirent.h>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/vfs.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>

#समावेश "proc.h"

अटल व्योम f_reg(सूची *d, स्थिर अक्षर *filename)
अणु
	अक्षर buf[4096];
	पूर्णांक fd;
	sमाप_प्रकार rv;

	/* पढ़ो from /proc/kmsg can block */
	fd = खोलोat(dirfd(d), filename, O_RDONLY|O_NONBLOCK);
	अगर (fd == -1)
		वापस;
	/* काष्ठा proc_ops::proc_lseek is mandatory अगर file is seekable. */
	(व्योम)lseek(fd, 0, शुरू_से);
	rv = पढ़ो(fd, buf, माप(buf));
	निश्चित((0 <= rv && rv <= माप(buf)) || rv == -1);
	बंद(fd);
पूर्ण

अटल व्योम f_reg_ग_लिखो(सूची *d, स्थिर अक्षर *filename, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक fd;
	sमाप_प्रकार rv;

	fd = खोलोat(dirfd(d), filename, O_WRONLY);
	अगर (fd == -1)
		वापस;
	rv = ग_लिखो(fd, buf, len);
	निश्चित((0 <= rv && rv <= len) || rv == -1);
	बंद(fd);
पूर्ण

अटल व्योम f_lnk(सूची *d, स्थिर अक्षर *filename)
अणु
	अक्षर buf[4096];
	sमाप_प्रकार rv;

	rv = पढ़ोlinkat(dirfd(d), filename, buf, माप(buf));
	निश्चित((0 <= rv && rv <= माप(buf)) || rv == -1);
पूर्ण

अटल व्योम f(सूची *d, अचिन्हित पूर्णांक level)
अणु
	काष्ठा dirent *de;

	de = xसूची_पढ़ो(d);
	निश्चित(de->d_type == DT_सूची);
	निश्चित(streq(de->d_name, "."));

	de = xसूची_पढ़ो(d);
	निश्चित(de->d_type == DT_सूची);
	निश्चित(streq(de->d_name, ".."));

	जबतक ((de = xसूची_पढ़ो(d))) अणु
		निश्चित(!streq(de->d_name, "."));
		निश्चित(!streq(de->d_name, ".."));

		चयन (de->d_type) अणु
			सूची *dd;
			पूर्णांक fd;

		हाल DT_REG:
			अगर (level == 0 && streq(de->d_name, "sysrq-trigger")) अणु
				f_reg_ग_लिखो(d, de->d_name, "h", 1);
			पूर्ण अन्यथा अगर (level == 1 && streq(de->d_name, "clear_refs")) अणु
				f_reg_ग_लिखो(d, de->d_name, "1", 1);
			पूर्ण अन्यथा अगर (level == 3 && streq(de->d_name, "clear_refs")) अणु
				f_reg_ग_लिखो(d, de->d_name, "1", 1);
			पूर्ण अन्यथा अणु
				f_reg(d, de->d_name);
			पूर्ण
			अवरोध;
		हाल DT_सूची:
			fd = खोलोat(dirfd(d), de->d_name, O_सूचीECTORY|O_RDONLY);
			अगर (fd == -1)
				जारी;
			dd = fकरोpendir(fd);
			अगर (!dd)
				जारी;
			f(dd, level + 1);
			बंद_सूची(dd);
			अवरोध;
		हाल DT_LNK:
			f_lnk(d, de->d_name);
			अवरोध;
		शेष:
			निश्चित(0);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	सूची *d;
	काष्ठा statfs sfs;

	d = सूची_खोलो("/proc");
	अगर (!d)
		वापस 4;

	/* Ensure /proc is proc. */
	अगर (ख_स्थितिfs(dirfd(d), &sfs) == -1) अणु
		वापस 1;
	पूर्ण
	अगर (sfs.f_type != 0x9fa0) अणु
		ख_लिखो(मानक_त्रुटि, "error: unexpected f_type %lx\n", (दीर्घ)sfs.f_type);
		वापस 2;
	पूर्ण

	f(d, 0);

	वापस 0;
पूर्ण
