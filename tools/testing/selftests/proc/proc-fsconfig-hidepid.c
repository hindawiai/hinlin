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
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/mount.h>
#समावेश <linux/unistd.h>

अटल अंतरभूत पूर्णांक fsखोलो(स्थिर अक्षर *fsname, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_fsखोलो, fsname, flags);
पूर्ण

अटल अंतरभूत पूर्णांक fsconfig(पूर्णांक fd, अचिन्हित पूर्णांक cmd, स्थिर अक्षर *key, स्थिर व्योम *val, पूर्णांक aux)
अणु
	वापस syscall(__NR_fsconfig, fd, cmd, key, val, aux);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक fsfd, ret;
	पूर्णांक hidepid = 2;

	निश्चित((fsfd = fsखोलो("proc", 0)) != -1);

	ret = fsconfig(fsfd, FSCONFIG_SET_BINARY, "hidepid", &hidepid, 0);
	निश्चित(ret == -1);
	निश्चित(त्रुटि_सं == EINVAL);

	निश्चित(!fsconfig(fsfd, FSCONFIG_SET_STRING, "hidepid", "2", 0));
	निश्चित(!fsconfig(fsfd, FSCONFIG_SET_STRING, "hidepid", "invisible", 0));

	निश्चित(!बंद(fsfd));

	वापस 0;
पूर्ण
