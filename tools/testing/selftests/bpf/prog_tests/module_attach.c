<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश "test_module_attach.skel.h"

अटल पूर्णांक duration;

अटल पूर्णांक trigger_module_test_पढ़ो(पूर्णांक पढ़ो_sz)
अणु
	पूर्णांक fd, err;

	fd = खोलो("/sys/kernel/bpf_testmod", O_RDONLY);
	err = -त्रुटि_सं;
	अगर (CHECK(fd < 0, "testmod_file_open", "failed: %d\n", err))
		वापस err;

	पढ़ो(fd, शून्य, पढ़ो_sz);
	बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक trigger_module_test_ग_लिखो(पूर्णांक ग_लिखो_sz)
अणु
	पूर्णांक fd, err;
	अक्षर *buf = दो_स्मृति(ग_लिखो_sz);

	अगर (!buf)
		वापस -ENOMEM;

	स_रखो(buf, 'a', ग_लिखो_sz);
	buf[ग_लिखो_sz-1] = '\0';

	fd = खोलो("/sys/kernel/bpf_testmod", O_WRONLY);
	err = -त्रुटि_सं;
	अगर (CHECK(fd < 0, "testmod_file_open", "failed: %d\n", err)) अणु
		मुक्त(buf);
		वापस err;
	पूर्ण

	ग_लिखो(fd, buf, ग_लिखो_sz);
	बंद(fd);
	मुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक delete_module(स्थिर अक्षर *name, पूर्णांक flags)
अणु
	वापस syscall(__NR_delete_module, name, flags);
पूर्ण

व्योम test_module_attach(व्योम)
अणु
	स्थिर पूर्णांक READ_SZ = 456;
	स्थिर पूर्णांक WRITE_SZ = 457;
	काष्ठा test_module_attach* skel;
	काष्ठा test_module_attach__bss *bss;
	काष्ठा bpf_link *link;
	पूर्णांक err;

	skel = test_module_attach__खोलो();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;

	err = bpf_program__set_attach_target(skel->progs.handle_fentry_manual,
					     0, "bpf_testmod_test_read");
	ASSERT_OK(err, "set_attach_target");

	err = test_module_attach__load(skel);
	अगर (CHECK(err, "skel_load", "failed to load skeleton\n"))
		वापस;

	bss = skel->bss;

	err = test_module_attach__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	/* trigger tracepoपूर्णांक */
	ASSERT_OK(trigger_module_test_पढ़ो(READ_SZ), "trigger_read");
	ASSERT_OK(trigger_module_test_ग_लिखो(WRITE_SZ), "trigger_write");

	ASSERT_EQ(bss->raw_tp_पढ़ो_sz, READ_SZ, "raw_tp");
	ASSERT_EQ(bss->raw_tp_bare_ग_लिखो_sz, WRITE_SZ, "raw_tp_bare");
	ASSERT_EQ(bss->tp_btf_पढ़ो_sz, READ_SZ, "tp_btf");
	ASSERT_EQ(bss->fentry_पढ़ो_sz, READ_SZ, "fentry");
	ASSERT_EQ(bss->fentry_manual_पढ़ो_sz, READ_SZ, "fentry_manual");
	ASSERT_EQ(bss->fनिकास_पढ़ो_sz, READ_SZ, "fexit");
	ASSERT_EQ(bss->fनिकास_ret, -EIO, "fexit_tet");
	ASSERT_EQ(bss->भ_शेष_ret_पढ़ो_sz, READ_SZ, "fmod_ret");

	test_module_attach__detach(skel);

	/* attach fentry/fनिकास and make sure it get's module reference */
	link = bpf_program__attach(skel->progs.handle_fentry);
	अगर (!ASSERT_OK_PTR(link, "attach_fentry"))
		जाओ cleanup;

	ASSERT_ERR(delete_module("bpf_testmod", 0), "delete_module");
	bpf_link__destroy(link);

	link = bpf_program__attach(skel->progs.handle_fनिकास);
	अगर (!ASSERT_OK_PTR(link, "attach_fexit"))
		जाओ cleanup;

	ASSERT_ERR(delete_module("bpf_testmod", 0), "delete_module");
	bpf_link__destroy(link);

cleanup:
	test_module_attach__destroy(skel);
पूर्ण
