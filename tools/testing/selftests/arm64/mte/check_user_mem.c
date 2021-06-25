<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <ucontext.h>
#समावेश <unistd.h>
#समावेश <sys/mman.h>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"
#समावेश "mte_def.h"

अटल माप_प्रकार page_sz;

अटल पूर्णांक check_usermem_access_fault(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping)
अणु
	पूर्णांक fd, i, err;
	अक्षर val = 'A';
	माप_प्रकार len, पढ़ो_len;
	व्योम *ptr, *ptr_next;

	err = KSFT_FAIL;
	len = 2 * page_sz;
	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	fd = create_temp_file();
	अगर (fd == -1)
		वापस KSFT_FAIL;
	क्रम (i = 0; i < len; i++)
		अगर (ग_लिखो(fd, &val, माप(val)) != माप(val))
			वापस KSFT_FAIL;
	lseek(fd, 0, 0);
	ptr = mte_allocate_memory(len, mem_type, mapping, true);
	अगर (check_allocated_memory(ptr, len, mem_type, true) != KSFT_PASS) अणु
		बंद(fd);
		वापस KSFT_FAIL;
	पूर्ण
	mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, len);
	/* Copy from file पूर्णांकo buffer with valid tag */
	पढ़ो_len = पढ़ो(fd, ptr, len);
	mte_रुको_after_trig();
	अगर (cur_mte_cxt.fault_valid || पढ़ो_len < len)
		जाओ usermem_acc_err;
	/* Verअगरy same pattern is पढ़ो */
	क्रम (i = 0; i < len; i++)
		अगर (*(अक्षर *)(ptr + i) != val)
			अवरोध;
	अगर (i < len)
		जाओ usermem_acc_err;

	/* Tag the next half of memory with dअगरferent value */
	ptr_next = (व्योम *)((अचिन्हित दीर्घ)ptr + page_sz);
	ptr_next = mte_insert_new_tag(ptr_next);
	mte_set_tag_address_range(ptr_next, page_sz);

	lseek(fd, 0, 0);
	/* Copy from file पूर्णांकo buffer with invalid tag */
	पढ़ो_len = पढ़ो(fd, ptr, len);
	mte_रुको_after_trig();
	/*
	 * Accessing user memory in kernel with invalid tag should fail in sync
	 * mode without fault but may not fail in async mode as per the
	 * implemented MTE userspace support in Arm64 kernel.
	 */
	अगर (mode == MTE_SYNC_ERR &&
	    !cur_mte_cxt.fault_valid && पढ़ो_len < len) अणु
		err = KSFT_PASS;
	पूर्ण अन्यथा अगर (mode == MTE_ASYNC_ERR &&
		   !cur_mte_cxt.fault_valid && पढ़ो_len == len) अणु
		err = KSFT_PASS;
	पूर्ण
usermem_acc_err:
	mte_मुक्त_memory((व्योम *)ptr, len, mem_type, true);
	बंद(fd);
	वापस err;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;

	page_sz = getpagesize();
	अगर (!page_sz) अणु
		ksft_prपूर्णांक_msg("ERR: Unable to get page size\n");
		वापस KSFT_FAIL;
	पूर्ण
	err = mte_शेष_setup();
	अगर (err)
		वापस err;

	/* Register संकेत handlers */
	mte_रेजिस्टर_संकेत(संक_अंश, mte_शेष_handler);

	/* Set test plan */
	ksft_set_plan(4);

	evaluate_test(check_usermem_access_fault(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE),
		"Check memory access from kernel in sync mode, private mapping and mmap memory\n");
	evaluate_test(check_usermem_access_fault(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED),
		"Check memory access from kernel in sync mode, shared mapping and mmap memory\n");

	evaluate_test(check_usermem_access_fault(USE_MMAP, MTE_ASYNC_ERR, MAP_PRIVATE),
		"Check memory access from kernel in async mode, private mapping and mmap memory\n");
	evaluate_test(check_usermem_access_fault(USE_MMAP, MTE_ASYNC_ERR, MAP_SHARED),
		"Check memory access from kernel in async mode, shared mapping and mmap memory\n");

	mte_restore_setup();
	ksft_prपूर्णांक_cnts();
	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
