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
// Test /proc/*/fd lookup.

#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश "proc.h"

/* lstat(2) has more "coverage" in हाल non-symlink pops up somehow. */
अटल व्योम test_lookup_pass(स्थिर अक्षर *pathname)
अणु
	काष्ठा stat st;
	sमाप_प्रकार rv;

	स_रखो(&st, 0, माप(काष्ठा stat));
	rv = lstat(pathname, &st);
	निश्चित(rv == 0);
	निश्चित(S_ISLNK(st.st_mode));
पूर्ण

अटल व्योम test_lookup_fail(स्थिर अक्षर *pathname)
अणु
	काष्ठा stat st;
	sमाप_प्रकार rv;

	rv = lstat(pathname, &st);
	निश्चित(rv == -1 && त्रुटि_सं == ENOENT);
पूर्ण

अटल व्योम test_lookup(अचिन्हित पूर्णांक fd)
अणु
	अक्षर buf[64];
	अचिन्हित पूर्णांक c;
	अचिन्हित पूर्णांक u;
	पूर्णांक i;

	snम_लिखो(buf, माप(buf), "/proc/self/fd/%u", fd);
	test_lookup_pass(buf);

	/* leading junk */
	क्रम (c = 1; c <= 255; c++) अणु
		अगर (c == '/')
			जारी;
		snम_लिखो(buf, माप(buf), "/proc/self/fd/%c%u", c, fd);
		test_lookup_fail(buf);
	पूर्ण

	/* trailing junk */
	क्रम (c = 1; c <= 255; c++) अणु
		अगर (c == '/')
			जारी;
		snम_लिखो(buf, माप(buf), "/proc/self/fd/%u%c", fd, c);
		test_lookup_fail(buf);
	पूर्ण

	क्रम (i = पूर्णांक_न्यून; i < पूर्णांक_न्यून + 1024; i++) अणु
		snम_लिखो(buf, माप(buf), "/proc/self/fd/%d", i);
		test_lookup_fail(buf);
	पूर्ण
	क्रम (i = -1024; i < 0; i++) अणु
		snम_लिखो(buf, माप(buf), "/proc/self/fd/%d", i);
		test_lookup_fail(buf);
	पूर्ण
	क्रम (u = पूर्णांक_उच्च - 1024; u <= (अचिन्हित पूर्णांक)पूर्णांक_उच्च + 1024; u++) अणु
		snम_लिखो(buf, माप(buf), "/proc/self/fd/%u", u);
		test_lookup_fail(buf);
	पूर्ण
	क्रम (u = अच_पूर्णांक_उच्च - 1024; u != 0; u++) अणु
		snम_लिखो(buf, माप(buf), "/proc/self/fd/%u", u);
		test_lookup_fail(buf);
	पूर्ण


पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा dirent *de;
	अचिन्हित पूर्णांक fd, target_fd;

	अगर (unshare(CLONE_खाताS) == -1)
		वापस 1;

	/* Wipe fdtable. */
	करो अणु
		सूची *d;

		d = सूची_खोलो("/proc/self/fd");
		अगर (!d)
			वापस 1;

		de = xसूची_पढ़ो(d);
		निश्चित(de->d_type == DT_सूची);
		निश्चित(streq(de->d_name, "."));

		de = xसूची_पढ़ो(d);
		निश्चित(de->d_type == DT_सूची);
		निश्चित(streq(de->d_name, ".."));
next:
		de = xसूची_पढ़ो(d);
		अगर (de) अणु
			अचिन्हित दीर्घ दीर्घ fd_ull;
			अचिन्हित पूर्णांक fd;
			अक्षर *end;

			निश्चित(de->d_type == DT_LNK);

			fd_ull = xम_से_अदीर्घl(de->d_name, &end);
			निश्चित(*end == '\0');
			निश्चित(fd_ull == (अचिन्हित पूर्णांक)fd_ull);

			fd = fd_ull;
			अगर (fd == dirfd(d))
				जाओ next;
			बंद(fd);
		पूर्ण

		बंद_सूची(d);
	पूर्ण जबतक (de);

	/* Now fdtable is clean. */

	fd = खोलो("/", O_PATH|O_सूचीECTORY);
	निश्चित(fd == 0);
	test_lookup(fd);
	बंद(fd);

	/* Clean again! */

	fd = खोलो("/", O_PATH|O_सूचीECTORY);
	निश्चित(fd == 0);
	/* Default RLIMIT_NOखाता-1 */
	target_fd = 1023;
	जबतक (target_fd > 0) अणु
		अगर (dup2(fd, target_fd) == target_fd)
			अवरोध;
		target_fd /= 2;
	पूर्ण
	निश्चित(target_fd > 0);
	बंद(fd);
	test_lookup(target_fd);
	बंद(target_fd);

	वापस 0;
पूर्ण
