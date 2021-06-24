<शैली गुरु>
/*
 * Copyright (c) 2019 Alexey Dobriyan <aकरोbriyan@gmail.com>
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
/* Test that खोलो(O_TMPखाता), linkat() करोesn't screw accounting. */
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/mount.h>
#समावेश <unistd.h>

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक fd;

	अगर (unshare(CLONE_NEWNS) == -1) अणु
		अगर (त्रुटि_सं == ENOSYS || त्रुटि_सं == EPERM) अणु
			ख_लिखो(मानक_त्रुटि, "error: unshare, errno %d\n", त्रुटि_सं);
			वापस 4;
		पूर्ण
		ख_लिखो(मानक_त्रुटि, "error: unshare, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण
	अगर (mount(शून्य, "/", शून्य, MS_PRIVATE|MS_REC, शून्य) == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: mount '/', errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण

	/* Our heroes: 1 root inode, 1 O_TMPखाता inode, 1 permanent inode. */
	अगर (mount(शून्य, "/tmp", "tmpfs", 0, "nr_inodes=3") == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: mount tmpfs, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण

	fd = खोलोat(AT_FDCWD, "/tmp", O_WRONLY|O_TMPखाता, 0600);
	अगर (fd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: open 1, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण
	अगर (linkat(fd, "", AT_FDCWD, "/tmp/1", AT_EMPTY_PATH) == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: linkat, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण
	बंद(fd);

	fd = खोलोat(AT_FDCWD, "/tmp", O_WRONLY|O_TMPखाता, 0600);
	अगर (fd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: open 2, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
