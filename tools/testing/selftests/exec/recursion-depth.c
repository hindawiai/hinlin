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
/* Test that poपूर्णांकing #! script पूर्णांकerpreter to self करोesn't recurse. */
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/mount.h>
#समावेश <unistd.h>

पूर्णांक मुख्य(व्योम)
अणु
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
	/* Require "exec" fileप्रणाली. */
	अगर (mount(शून्य, "/tmp", "ramfs", 0, शून्य) == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: mount ramfs, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण

#घोषणा खाताNAME "/tmp/1"

	पूर्णांक fd = creat(खाताNAME, 0700);
	अगर (fd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "error: creat, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण
#घोषणा S "#!" खाताNAME "\n"
	अगर (ग_लिखो(fd, S, म_माप(S)) != म_माप(S)) अणु
		ख_लिखो(मानक_त्रुटि, "error: write, errno %d\n", त्रुटि_सं);
		वापस 1;
	पूर्ण
	बंद(fd);

	पूर्णांक rv = execve(खाताNAME, शून्य, शून्य);
	अगर (rv == -1 && त्रुटि_सं == ELOOP) अणु
		वापस 0;
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "error: execve, rv %d, errno %d\n", rv, त्रुटि_सं);
	वापस 1;
पूर्ण
