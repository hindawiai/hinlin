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
/* Test that /proc/loadavg correctly reports last pid in pid namespace. */
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <sys/रुको.h>

पूर्णांक मुख्य(व्योम)
अणु
	pid_t pid;
	पूर्णांक wstatus;

	अगर (unshare(CLONE_NEWPID) == -1) अणु
		अगर (त्रुटि_सं == ENOSYS || त्रुटि_सं == EPERM)
			वापस 4;
		वापस 1;
	पूर्ण

	pid = विभाजन();
	अगर (pid == -1)
		वापस 1;
	अगर (pid == 0) अणु
		अक्षर buf[128], *p;
		पूर्णांक fd;
		sमाप_प्रकार rv;

		fd = खोलो("/proc/loadavg" , O_RDONLY);
		अगर (fd == -1)
			वापस 1;
		rv = पढ़ो(fd, buf, माप(buf));
		अगर (rv < 3)
			वापस 1;
		p = buf + rv;

		/* pid 1 */
		अगर (!(p[-3] == ' ' && p[-2] == '1' && p[-1] == '\n'))
			वापस 1;

		pid = विभाजन();
		अगर (pid == -1)
			वापस 1;
		अगर (pid == 0)
			वापस 0;
		अगर (रुकोpid(pid, शून्य, 0) == -1)
			वापस 1;

		lseek(fd, 0, शुरू_से);
		rv = पढ़ो(fd, buf, माप(buf));
		अगर (rv < 3)
			वापस 1;
		p = buf + rv;

		/* pid 2 */
		अगर (!(p[-3] == ' ' && p[-2] == '2' && p[-1] == '\n'))
			वापस 1;

		वापस 0;
	पूर्ण

	अगर (रुकोpid(pid, &wstatus, 0) == -1)
		वापस 1;
	अगर (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
		वापस 0;
	वापस 1;
पूर्ण
