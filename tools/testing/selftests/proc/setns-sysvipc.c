<शैली गुरु>
/*
 * Copyright तऊ 2019 Alexey Dobriyan <aकरोbriyan@gmail.com>
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
/*
 * Test that setns(CLONE_NEWIPC) poपूर्णांकs to new /proc/sysvipc content even
 * अगर old one is in dcache.
 */
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>

अटल pid_t pid = -1;

अटल व्योम f(व्योम)
अणु
	अगर (pid > 0) अणु
		समाप्त(pid, संक_इति);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक fd[2];
	अक्षर _ = 0;
	पूर्णांक nsfd;

	निकास_पर(f);

	/* Check क्रम priviledges and syscall availability straight away. */
	अगर (unshare(CLONE_NEWIPC) == -1) अणु
		अगर (त्रुटि_सं == ENOSYS || त्रुटि_सं == EPERM) अणु
			वापस 4;
		पूर्ण
		वापस 1;
	पूर्ण
	/* Distinguisher between two otherwise empty IPC namespaces. */
	अगर (shmget(IPC_PRIVATE, 1, IPC_CREAT) == -1) अणु
		वापस 1;
	पूर्ण

	अगर (pipe(fd) == -1) अणु
		वापस 1;
	पूर्ण

	pid = विभाजन();
	अगर (pid == -1) अणु
		वापस 1;
	पूर्ण

	अगर (pid == 0) अणु
		अगर (unshare(CLONE_NEWIPC) == -1) अणु
			वापस 1;
		पूर्ण

		अगर (ग_लिखो(fd[1], &_, 1) != 1) अणु
			वापस 1;
		पूर्ण

		छोड़ो();

		वापस 0;
	पूर्ण

	अगर (पढ़ो(fd[0], &_, 1) != 1) अणु
		वापस 1;
	पूर्ण

	अणु
		अक्षर buf[64];
		snम_लिखो(buf, माप(buf), "/proc/%u/ns/ipc", pid);
		nsfd = खोलो(buf, O_RDONLY);
		अगर (nsfd == -1) अणु
			वापस 1;
		पूर्ण
	पूर्ण

	/* Reliably pin dentry पूर्णांकo dcache. */
	(व्योम)खोलो("/proc/sysvipc/shm", O_RDONLY);

	अगर (setns(nsfd, CLONE_NEWIPC) == -1) अणु
		वापस 1;
	पूर्ण

	समाप्त(pid, संक_इति);
	pid = 0;

	अणु
		अक्षर buf[4096];
		sमाप_प्रकार rv;
		पूर्णांक fd;

		fd = खोलो("/proc/sysvipc/shm", O_RDONLY);
		अगर (fd == -1) अणु
			वापस 1;
		पूर्ण

#घोषणा S32 "       key      shmid perms       size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime        rss       swap\n"
#घोषणा S64 "       key      shmid perms                  size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime                   rss                  swap\n"
		rv = पढ़ो(fd, buf, माप(buf));
		अगर (rv == म_माप(S32)) अणु
			निश्चित(स_भेद(buf, S32, म_माप(S32)) == 0);
		पूर्ण अन्यथा अगर (rv == म_माप(S64)) अणु
			निश्चित(स_भेद(buf, S64, म_माप(S64)) == 0);
		पूर्ण अन्यथा अणु
			निश्चित(0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
