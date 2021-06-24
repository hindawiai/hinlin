<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright (C) 2020 Google LLC.
 */

#समावेश <test_progs.h>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <दो_स्मृति.h>
#समावेश <मानककोष.स>

#समावेश "lsm.skel.h"

अक्षर *CMD_ARGS[] = अणु"true", शून्यपूर्ण;

#घोषणा GET_PAGE_ADDR(ADDR, PAGE_SIZE)					\
	(अक्षर *)(((अचिन्हित दीर्घ) (ADDR + PAGE_SIZE)) & ~(PAGE_SIZE-1))

पूर्णांक stack_mprotect(व्योम)
अणु
	व्योम *buf;
	दीर्घ sz;
	पूर्णांक ret;

	sz = sysconf(_SC_PAGESIZE);
	अगर (sz < 0)
		वापस sz;

	buf = alloca(sz * 3);
	ret = mprotect(GET_PAGE_ADDR(buf, sz), sz,
		       PROT_READ | PROT_WRITE | PROT_EXEC);
	वापस ret;
पूर्ण

पूर्णांक exec_cmd(पूर्णांक *monitored_pid)
अणु
	पूर्णांक child_pid, child_status;

	child_pid = विभाजन();
	अगर (child_pid == 0) अणु
		*monitored_pid = getpid();
		execvp(CMD_ARGS[0], CMD_ARGS);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (child_pid > 0) अणु
		रुकोpid(child_pid, &child_status, 0);
		वापस child_status;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक test_lsm(काष्ठा lsm *skel)
अणु
	काष्ठा bpf_link *link;
	पूर्णांक buf = 1234;
	पूर्णांक err;

	err = lsm__attach(skel);
	अगर (!ASSERT_OK(err, "attach"))
		वापस err;

	/* Check that alपढ़ोy linked program can't be attached again. */
	link = bpf_program__attach(skel->progs.test_पूर्णांक_hook);
	अगर (!ASSERT_ERR_PTR(link, "attach_link"))
		वापस -1;

	err = exec_cmd(&skel->bss->monitored_pid);
	अगर (!ASSERT_OK(err, "exec_cmd"))
		वापस err;

	ASSERT_EQ(skel->bss->bprm_count, 1, "bprm_count");

	skel->bss->monitored_pid = getpid();

	err = stack_mprotect();
	अगर (!ASSERT_EQ(त्रुटि_सं, EPERM, "stack_mprotect"))
		वापस err;

	ASSERT_EQ(skel->bss->mprotect_count, 1, "mprotect_count");

	syscall(__NR_setकरोमुख्यname, &buf, -2L);
	syscall(__NR_setकरोमुख्यname, 0, -3L);
	syscall(__NR_setकरोमुख्यname, ~0L, -4L);

	ASSERT_EQ(skel->bss->copy_test, 3, "copy_test");

	lsm__detach(skel);

	skel->bss->copy_test = 0;
	skel->bss->bprm_count = 0;
	skel->bss->mprotect_count = 0;
	वापस 0;
पूर्ण

व्योम test_test_lsm(व्योम)
अणु
	काष्ठा lsm *skel = शून्य;
	पूर्णांक err;

	skel = lsm__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "lsm_skel_load"))
		जाओ बंद_prog;

	err = test_lsm(skel);
	अगर (!ASSERT_OK(err, "test_lsm_first_attach"))
		जाओ बंद_prog;

	err = test_lsm(skel);
	ASSERT_OK(err, "test_lsm_second_attach");

बंद_prog:
	lsm__destroy(skel);
पूर्ण
