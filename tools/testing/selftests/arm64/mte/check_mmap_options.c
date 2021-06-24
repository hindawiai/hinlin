<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <ucontext.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"
#समावेश "mte_def.h"

#घोषणा RUNS			(MT_TAG_COUNT)
#घोषणा UNDERFLOW		MT_GRANULE_SIZE
#घोषणा OVERFLOW		MT_GRANULE_SIZE
#घोषणा TAG_CHECK_ON		0
#घोषणा TAG_CHECK_OFF		1

अटल माप_प्रकार page_size;
अटल पूर्णांक sizes[] = अणु
	1, 537, 989, 1269, MT_GRANULE_SIZE - 1, MT_GRANULE_SIZE,
	/* page size - 1*/ 0, /* page_size */ 0, /* page size + 1 */ 0
पूर्ण;

अटल पूर्णांक check_mte_memory(अक्षर *ptr, पूर्णांक size, पूर्णांक mode, पूर्णांक tag_check)
अणु
	mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, size);
	स_रखो(ptr, '1', size);
	mte_रुको_after_trig();
	अगर (cur_mte_cxt.fault_valid == true)
		वापस KSFT_FAIL;

	mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, -UNDERFLOW);
	स_रखो(ptr - UNDERFLOW, '2', UNDERFLOW);
	mte_रुको_after_trig();
	अगर (cur_mte_cxt.fault_valid == false && tag_check == TAG_CHECK_ON)
		वापस KSFT_FAIL;
	अगर (cur_mte_cxt.fault_valid == true && tag_check == TAG_CHECK_OFF)
		वापस KSFT_FAIL;

	mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, size + OVERFLOW);
	स_रखो(ptr + size, '3', OVERFLOW);
	mte_रुको_after_trig();
	अगर (cur_mte_cxt.fault_valid == false && tag_check == TAG_CHECK_ON)
		वापस KSFT_FAIL;
	अगर (cur_mte_cxt.fault_valid == true && tag_check == TAG_CHECK_OFF)
		वापस KSFT_FAIL;

	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक check_anonymous_memory_mapping(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping, पूर्णांक tag_check)
अणु
	अक्षर *ptr, *map_ptr;
	पूर्णांक run, result, map_size;
	पूर्णांक item = माप(sizes)/माप(पूर्णांक);

	item = माप(sizes)/माप(पूर्णांक);
	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	क्रम (run = 0; run < item; run++) अणु
		map_size = sizes[run] + OVERFLOW + UNDERFLOW;
		map_ptr = (अक्षर *)mte_allocate_memory(map_size, mem_type, mapping, false);
		अगर (check_allocated_memory(map_ptr, map_size, mem_type, false) != KSFT_PASS)
			वापस KSFT_FAIL;

		ptr = map_ptr + UNDERFLOW;
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, sizes[run]);
		/* Only mte enabled memory will allow tag insertion */
		ptr = mte_insert_tags((व्योम *)ptr, sizes[run]);
		अगर (!ptr || cur_mte_cxt.fault_valid == true) अणु
			ksft_prपूर्णांक_msg("FAIL: Insert tags on anonymous mmap memory\n");
			munmap((व्योम *)map_ptr, map_size);
			वापस KSFT_FAIL;
		पूर्ण
		result = check_mte_memory(ptr, sizes[run], mode, tag_check);
		mte_clear_tags((व्योम *)ptr, sizes[run]);
		mte_मुक्त_memory((व्योम *)map_ptr, map_size, mem_type, false);
		अगर (result == KSFT_FAIL)
			वापस KSFT_FAIL;
	पूर्ण
	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक check_file_memory_mapping(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping, पूर्णांक tag_check)
अणु
	अक्षर *ptr, *map_ptr;
	पूर्णांक run, fd, map_size;
	पूर्णांक total = माप(sizes)/माप(पूर्णांक);
	पूर्णांक result = KSFT_PASS;

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	क्रम (run = 0; run < total; run++) अणु
		fd = create_temp_file();
		अगर (fd == -1)
			वापस KSFT_FAIL;

		map_size = sizes[run] + UNDERFLOW + OVERFLOW;
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
		result = check_mte_memory(ptr, sizes[run], mode, tag_check);
		mte_clear_tags((व्योम *)ptr, sizes[run]);
		munmap((व्योम *)map_ptr, map_size);
		बंद(fd);
		अगर (result == KSFT_FAIL)
			अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक check_clear_prot_mte_flag(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping)
अणु
	अक्षर *ptr, *map_ptr;
	पूर्णांक run, prot_flag, result, fd, map_size;
	पूर्णांक total = माप(sizes)/माप(पूर्णांक);

	prot_flag = PROT_READ | PROT_WRITE;
	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	क्रम (run = 0; run < total; run++) अणु
		map_size = sizes[run] + OVERFLOW + UNDERFLOW;
		ptr = (अक्षर *)mte_allocate_memory_tag_range(sizes[run], mem_type, mapping,
							    UNDERFLOW, OVERFLOW);
		अगर (check_allocated_memory_range(ptr, sizes[run], mem_type,
						 UNDERFLOW, OVERFLOW) != KSFT_PASS)
			वापस KSFT_FAIL;
		map_ptr = ptr - UNDERFLOW;
		/* Try to clear PROT_MTE property and verअगरy it by tag checking */
		अगर (mprotect(map_ptr, map_size, prot_flag)) अणु
			mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[run], mem_type,
						  UNDERFLOW, OVERFLOW);
			ksft_prपूर्णांक_msg("FAIL: mprotect not ignoring clear PROT_MTE property\n");
			वापस KSFT_FAIL;
		पूर्ण
		result = check_mte_memory(ptr, sizes[run], mode, TAG_CHECK_ON);
		mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[run], mem_type, UNDERFLOW, OVERFLOW);
		अगर (result != KSFT_PASS)
			वापस KSFT_FAIL;

		fd = create_temp_file();
		अगर (fd == -1)
			वापस KSFT_FAIL;
		ptr = (अक्षर *)mte_allocate_file_memory_tag_range(sizes[run], mem_type, mapping,
								 UNDERFLOW, OVERFLOW, fd);
		अगर (check_allocated_memory_range(ptr, sizes[run], mem_type,
						 UNDERFLOW, OVERFLOW) != KSFT_PASS) अणु
			बंद(fd);
			वापस KSFT_FAIL;
		पूर्ण
		map_ptr = ptr - UNDERFLOW;
		/* Try to clear PROT_MTE property and verअगरy it by tag checking */
		अगर (mprotect(map_ptr, map_size, prot_flag)) अणु
			ksft_prपूर्णांक_msg("FAIL: mprotect not ignoring clear PROT_MTE property\n");
			mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[run], mem_type,
						  UNDERFLOW, OVERFLOW);
			बंद(fd);
			वापस KSFT_FAIL;
		पूर्ण
		result = check_mte_memory(ptr, sizes[run], mode, TAG_CHECK_ON);
		mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[run], mem_type, UNDERFLOW, OVERFLOW);
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

	err = mte_शेष_setup();
	अगर (err)
		वापस err;
	page_size = getpagesize();
	अगर (!page_size) अणु
		ksft_prपूर्णांक_msg("ERR: Unable to get page size\n");
		वापस KSFT_FAIL;
	पूर्ण
	sizes[item - 3] = page_size - 1;
	sizes[item - 2] = page_size;
	sizes[item - 1] = page_size + 1;

	/* Register संकेत handlers */
	mte_रेजिस्टर_संकेत(SIGBUS, mte_शेष_handler);
	mte_रेजिस्टर_संकेत(संक_अंश, mte_शेष_handler);

	/* Set test plan */
	ksft_set_plan(22);

	mte_enable_pstate_tco();

	evaluate_test(check_anonymous_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE, TAG_CHECK_OFF),
	"Check anonymous memory with private mapping, sync error mode, mmap memory and tag check off\n");
	evaluate_test(check_file_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE, TAG_CHECK_OFF),
	"Check file memory with private mapping, sync error mode, mmap/mprotect memory and tag check off\n");

	mte_disable_pstate_tco();
	evaluate_test(check_anonymous_memory_mapping(USE_MMAP, MTE_NONE_ERR, MAP_PRIVATE, TAG_CHECK_OFF),
	"Check anonymous memory with private mapping, no error mode, mmap memory and tag check off\n");
	evaluate_test(check_file_memory_mapping(USE_MPROTECT, MTE_NONE_ERR, MAP_PRIVATE, TAG_CHECK_OFF),
	"Check file memory with private mapping, no error mode, mmap/mprotect memory and tag check off\n");

	evaluate_test(check_anonymous_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check anonymous memory with private mapping, sync error mode, mmap memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check anonymous memory with private mapping, sync error mode, mmap/mprotect memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check anonymous memory with shared mapping, sync error mode, mmap memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check anonymous memory with shared mapping, sync error mode, mmap/mprotect memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check anonymous memory with private mapping, async error mode, mmap memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MPROTECT, MTE_ASYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check anonymous memory with private mapping, async error mode, mmap/mprotect memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check anonymous memory with shared mapping, async error mode, mmap memory and tag check on\n");
	evaluate_test(check_anonymous_memory_mapping(USE_MPROTECT, MTE_ASYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check anonymous memory with shared mapping, async error mode, mmap/mprotect memory and tag check on\n");

	evaluate_test(check_file_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check file memory with private mapping, sync error mode, mmap memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check file memory with private mapping, sync error mode, mmap/mprotect memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check file memory with shared mapping, sync error mode, mmap memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MPROTECT, MTE_SYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check file memory with shared mapping, sync error mode, mmap/mprotect memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check file memory with private mapping, async error mode, mmap memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MPROTECT, MTE_ASYNC_ERR, MAP_PRIVATE, TAG_CHECK_ON),
	"Check file memory with private mapping, async error mode, mmap/mprotect memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MMAP, MTE_ASYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check file memory with shared mapping, async error mode, mmap memory and tag check on\n");
	evaluate_test(check_file_memory_mapping(USE_MPROTECT, MTE_ASYNC_ERR, MAP_SHARED, TAG_CHECK_ON),
	"Check file memory with shared mapping, async error mode, mmap/mprotect memory and tag check on\n");

	evaluate_test(check_clear_prot_mte_flag(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE),
	"Check clear PROT_MTE flags with private mapping, sync error mode and mmap memory\n");
	evaluate_test(check_clear_prot_mte_flag(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE),
	"Check clear PROT_MTE flags with private mapping and sync error mode and mmap/mprotect memory\n");

	mte_restore_setup();
	ksft_prपूर्णांक_cnts();
	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
