<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <ucontext.h>
#समावेश <sys/रुको.h>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"
#समावेश "mte_def.h"

#घोषणा BUFFER_SIZE		(5 * MT_GRANULE_SIZE)
#घोषणा RUNS			(MT_TAG_COUNT)
#घोषणा UNDERFLOW		MT_GRANULE_SIZE
#घोषणा OVERFLOW		MT_GRANULE_SIZE

अटल माप_प्रकार page_size;
अटल पूर्णांक sizes[] = अणु
	1, 537, 989, 1269, MT_GRANULE_SIZE - 1, MT_GRANULE_SIZE,
	/* page size - 1*/ 0, /* page_size */ 0, /* page size + 1 */ 0
पूर्ण;

अटल पूर्णांक check_child_tag_inheritance(अक्षर *ptr, पूर्णांक size, पूर्णांक mode)
अणु
	पूर्णांक i, parent_tag, child_tag, fault, child_status;
	pid_t child;

	parent_tag = MT_FETCH_TAG((uपूर्णांकptr_t)ptr);
	fault = 0;

	child = विभाजन();
	अगर (child == -1) अणु
		ksft_prपूर्णांक_msg("FAIL: child process creation\n");
		वापस KSFT_FAIL;
	पूर्ण अन्यथा अगर (child == 0) अणु
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, size);
		/* Do copy on ग_लिखो */
		स_रखो(ptr, '1', size);
		mte_रुको_after_trig();
		अगर (cur_mte_cxt.fault_valid == true) अणु
			fault = 1;
			जाओ check_child_tag_inheritance_err;
		पूर्ण
		क्रम (i = 0 ; i < size ; i += MT_GRANULE_SIZE) अणु
			child_tag = MT_FETCH_TAG((uपूर्णांकptr_t)(mte_get_tag_address(ptr + i)));
			अगर (parent_tag != child_tag) अणु
				ksft_prपूर्णांक_msg("FAIL: child mte tag mismatch\n");
				fault = 1;
				जाओ check_child_tag_inheritance_err;
			पूर्ण
		पूर्ण
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, -UNDERFLOW);
		स_रखो(ptr - UNDERFLOW, '2', UNDERFLOW);
		mte_रुको_after_trig();
		अगर (cur_mte_cxt.fault_valid == false) अणु
			fault = 1;
			जाओ check_child_tag_inheritance_err;
		पूर्ण
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, size + OVERFLOW);
		स_रखो(ptr + size, '3', OVERFLOW);
		mte_रुको_after_trig();
		अगर (cur_mte_cxt.fault_valid == false) अणु
			fault = 1;
			जाओ check_child_tag_inheritance_err;
		पूर्ण
check_child_tag_inheritance_err:
		_निकास(fault);
	पूर्ण
	/* Wait क्रम child process to terminate */
	रुको(&child_status);
	अगर (WIFEXITED(child_status))
		fault = WEXITSTATUS(child_status);
	अन्यथा
		fault = 1;
	वापस (fault) ? KSFT_FAIL : KSFT_PASS;
पूर्ण

अटल पूर्णांक check_child_memory_mapping(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping)
अणु
	अक्षर *ptr;
	पूर्णांक run, result;
	पूर्णांक item = माप(sizes)/माप(पूर्णांक);

	item = माप(sizes)/माप(पूर्णांक);
	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	क्रम (run = 0; run < item; run++) अणु
		ptr = (अक्षर *)mte_allocate_memory_tag_range(sizes[run], mem_type, mapping,
							    UNDERFLOW, OVERFLOW);
		अगर (check_allocated_memory_range(ptr, sizes[run], mem_type,
						 UNDERFLOW, OVERFLOW) != KSFT_PASS)
			वापस KSFT_FAIL;
		result = check_child_tag_inheritance(ptr, sizes[run], mode);
		mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[run], mem_type, UNDERFLOW, OVERFLOW);
		अगर (result == KSFT_FAIL)
			वापस result;
	पूर्ण
	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक check_child_file_mapping(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping)
अणु
	अक्षर *ptr, *map_ptr;
	पूर्णांक run, fd, map_size, result = KSFT_PASS;
	पूर्णांक total = माप(sizes)/माप(पूर्णांक);

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	क्रम (run = 0; run < total; run++) अणु
		fd = create_temp_file();
		अगर (fd == -1)
			वापस KSFT_FAIL;

		map_size = sizes[run] + OVERFLOW + UNDERFLOW;
		map_ptr = (अक्षर *)mte_allocate_file_memory(map_size, mem_type, mapping, false, fd);
		अगर (check_allocated_memory(map_ptr, map_size, mem_type, false) != KSFT_PASS) अणु
			बंद(fd);
			वापस KSFT_FAIL;
		पूर्ण
		ptr = map_ptr + UNDERFLOW;
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, sizes[run]);
		/* Only mte enabled memory will allow tag insertion */
		ptr = mte_insert_tags((व्योम *)ptr, sizes[run]);
		अगर (!ptr || cur_mte_cxt.fault_valid == true) अणु
			ksft_prपूर्णांक_msg("FAIL: Insert tags on file based memory\n");
			munmap((व्योम *)map_ptr, map_size);
			बंद(fd);
			वापस KSFT_FAIL;
		पूर्ण
		result = check_child_tag_inheritance(ptr, sizes[run], mode);
		mte_clear_tags((व्योम *)ptr, sizes[run]);
		munmap((व्योम *)map_ptr, map_size);
		बंद(fd);
		अगर (result != KSFT_PASS)
			वापस KSFT_FAIL;
	पूर्ण
	वापस KSFT_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;
	पूर्णांक item = माप(sizes)/माप(पूर्णांक);

	page_size = getpagesize();
	अगर (!page_size) अणु
		ksft_prपूर्णांक_msg("ERR: Unable to get page size\n");
		वापस KSFT_FAIL;
	पूर्ण
	sizes[item - 3] = page_size - 1;
	sizes[item - 2] = page_size;
	sizes[item - 1] = page_size + 1;

	err = mte_शेष_setup();
	अगर (err)
		वापस err;

	/* Register संक_अंश handler */
	mte_रेजिस्टर_संकेत(संक_अंश, mte_शेष_handler);
	mte_रेजिस्टर_संकेत(SIGBUS, mte_शेष_handler);

	/* Set test plan */
	ksft_set_plan(12);

	evaluate_test(check_child_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE),
		"Check child anonymous memory with private mapping, precise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED),
		"Check child anonymous memory with shared mapping, precise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_PRIVATE),
		"Check child anonymous memory with private mapping, imprecise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_SHARED),
		"Check child anonymous memory with shared mapping, imprecise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE),
		"Check child anonymous memory with private mapping, precise mode and mmap/mprotect memory\n");
	evaluate_test(check_child_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_SHARED),
		"Check child anonymous memory with shared mapping, precise mode and mmap/mprotect memory\n");

	evaluate_test(check_child_file_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE),
		"Check child file memory with private mapping, precise mode and mmap memory\n");
	evaluate_test(check_child_file_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED),
		"Check child file memory with shared mapping, precise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_PRIVATE),
		"Check child file memory with private mapping, imprecise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_SHARED),
		"Check child file memory with shared mapping, imprecise mode and mmap memory\n");
	evaluate_test(check_child_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE),
		"Check child file memory with private mapping, precise mode and mmap/mprotect memory\n");
	evaluate_test(check_child_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_SHARED),
		"Check child file memory with shared mapping, precise mode and mmap/mprotect memory\n");

	mte_restore_setup();
	ksft_prपूर्णांक_cnts();
	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
