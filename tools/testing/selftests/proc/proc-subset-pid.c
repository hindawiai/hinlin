<शैली गुरु>
/*
 * Copyright (c) 2021 Alexey Dobriyan <aकरोbriyan@gmail.com>
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
 * Test that "mount -t proc -o subset=pid" hides everything but pids,
 * /proc/self and /proc/thपढ़ो-self.
 */
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mount.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <dirent.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>

अटल अंतरभूत bool streq(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	वापस म_भेद(a, b) == 0;
पूर्ण

अटल व्योम make_निजी_proc(व्योम)
अणु
	अगर (unshare(CLONE_NEWNS) == -1) अणु
		अगर (त्रुटि_सं == ENOSYS || त्रुटि_सं == EPERM) अणु
			निकास(4);
		पूर्ण
		निकास(1);
	पूर्ण
	अगर (mount(शून्य, "/", शून्य, MS_PRIVATE|MS_REC, शून्य) == -1) अणु
		निकास(1);
	पूर्ण
	अगर (mount(शून्य, "/proc", "proc", 0, "subset=pid") == -1) अणु
		निकास(1);
	पूर्ण
पूर्ण

अटल bool string_is_pid(स्थिर अक्षर *s)
अणु
	जबतक (1) अणु
		चयन (*s++) अणु
		हाल '0':case '1':case '2':case '3':case '4':
		हाल '5':case '6':case '7':case '8':case '9':
			जारी;

		हाल '\0':
			वापस true;

		शेष:
			वापस false;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	make_निजी_proc();

	सूची *d = सूची_खोलो("/proc");
	निश्चित(d);

	काष्ठा dirent *de;

	bool करोt = false;
	bool करोt_करोt = false;
	bool self = false;
	bool thपढ़ो_self = false;

	जबतक ((de = सूची_पढ़ो(d))) अणु
		अगर (streq(de->d_name, ".")) अणु
			निश्चित(!करोt);
			करोt = true;
			निश्चित(de->d_type == DT_सूची);
		पूर्ण अन्यथा अगर (streq(de->d_name, "..")) अणु
			निश्चित(!करोt_करोt);
			करोt_करोt = true;
			निश्चित(de->d_type == DT_सूची);
		पूर्ण अन्यथा अगर (streq(de->d_name, "self")) अणु
			निश्चित(!self);
			self = true;
			निश्चित(de->d_type == DT_LNK);
		पूर्ण अन्यथा अगर (streq(de->d_name, "thread-self")) अणु
			निश्चित(!thपढ़ो_self);
			thपढ़ो_self = true;
			निश्चित(de->d_type == DT_LNK);
		पूर्ण अन्यथा अणु
			अगर (!string_is_pid(de->d_name)) अणु
				ख_लिखो(मानक_त्रुटि, "d_name '%s'\n", de->d_name);
				निश्चित(0);
			पूर्ण
			निश्चित(de->d_type == DT_सूची);
		पूर्ण
	पूर्ण

	अक्षर c;
	पूर्णांक rv = पढ़ोlink("/proc/cpuinfo", &c, 1);
	निश्चित(rv == -1 && त्रुटि_सं == ENOENT);

	पूर्णांक fd = खोलो("/proc/cpuinfo", O_RDONLY);
	निश्चित(fd == -1 && त्रुटि_सं == ENOENT);

	वापस 0;
पूर्ण
