<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "test_probe_read_user_str.skel.h"

अटल स्थिर अक्षर str1[] = "mestring";
अटल स्थिर अक्षर str2[] = "mestringalittlebigger";
अटल स्थिर अक्षर str3[] = "mestringblubblubblubblubblub";

अटल पूर्णांक test_one_str(काष्ठा test_probe_पढ़ो_user_str *skel, स्थिर अक्षर *str,
			माप_प्रकार len)
अणु
	पूर्णांक err, duration = 0;
	अक्षर buf[256];

	/* Ensure bytes after string are ones */
	स_रखो(buf, 1, माप(buf));
	स_नकल(buf, str, len);

	/* Give prog our userspace poपूर्णांकer */
	skel->bss->user_ptr = buf;

	/* Trigger tracepoपूर्णांक */
	usleep(1);

	/* Did helper fail? */
	अगर (CHECK(skel->bss->ret < 0, "prog_ret", "prog returned: %ld\n",
		  skel->bss->ret))
		वापस 1;

	/* Check that string was copied correctly */
	err = स_भेद(skel->bss->buf, str, len);
	अगर (CHECK(err, "memcmp", "prog copied wrong string"))
		वापस 1;

	/* Now check that no extra trailing bytes were copied */
	स_रखो(buf, 0, माप(buf));
	err = स_भेद(skel->bss->buf + len, buf, माप(buf) - len);
	अगर (CHECK(err, "memcmp", "trailing bytes were not stripped"))
		वापस 1;

	वापस 0;
पूर्ण

व्योम test_probe_पढ़ो_user_str(व्योम)
अणु
	काष्ठा test_probe_पढ़ो_user_str *skel;
	पूर्णांक err, duration = 0;

	skel = test_probe_पढ़ो_user_str__खोलो_and_load();
	अगर (CHECK(!skel, "test_probe_read_user_str__open_and_load",
		  "skeleton open and load failed\n"))
		वापस;

	/* Give pid to bpf prog so it करोesn't पढ़ो from anyone अन्यथा */
	skel->bss->pid = getpid();

	err = test_probe_पढ़ो_user_str__attach(skel);
	अगर (CHECK(err, "test_probe_read_user_str__attach",
		  "skeleton attach failed: %d\n", err))
		जाओ out;

	अगर (test_one_str(skel, str1, माप(str1)))
		जाओ out;
	अगर (test_one_str(skel, str2, माप(str2)))
		जाओ out;
	अगर (test_one_str(skel, str3, माप(str3)))
		जाओ out;

out:
	test_probe_पढ़ो_user_str__destroy(skel);
पूर्ण
