<शैली गुरु>
/*
 * Copyright तऊ 2020 Alexey Gladkov <gladkov.alexey@gmail.com>
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
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <sys/mount.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा stat proc_st1, proc_st2;
	अक्षर procbuff[] = "/tmp/proc.XXXXXX/meminfo";
	अक्षर procdir1[] = "/tmp/proc.XXXXXX";
	अक्षर procdir2[] = "/tmp/proc.XXXXXX";

	निश्चित(mkdtemp(procdir1) != शून्य);
	निश्चित(mkdtemp(procdir2) != शून्य);

	निश्चित(!mount("proc", procdir1, "proc", 0, "hidepid=1"));
	निश्चित(!mount("proc", procdir2, "proc", 0, "hidepid=2"));

	snम_लिखो(procbuff, माप(procbuff), "%s/meminfo", procdir1);
	निश्चित(!stat(procbuff, &proc_st1));

	snम_लिखो(procbuff, माप(procbuff), "%s/meminfo", procdir2);
	निश्चित(!stat(procbuff, &proc_st2));

	umount(procdir1);
	umount(procdir2);

	निश्चित(proc_st1.st_dev != proc_st2.st_dev);

	वापस 0;
पूर्ण
