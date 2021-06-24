<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#घोषणा _GNU_SOURCE

#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश "kselftest.h"
#समावेश "mte_common_util.h"
#समावेश "mte_def.h"

#घोषणा OVERFLOW_RANGE MT_GRANULE_SIZE

अटल पूर्णांक sizes[] = अणु
	1, 555, 1033, MT_GRANULE_SIZE - 1, MT_GRANULE_SIZE,
	/* page size - 1*/ 0, /* page_size */ 0, /* page size + 1 */ 0
पूर्ण;

क्रमागत mte_block_test_alloc अणु
	UNTAGGED_TAGGED,
	TAGGED_UNTAGGED,
	TAGGED_TAGGED,
	BLOCK_ALLOC_MAX,
पूर्ण;

अटल पूर्णांक check_buffer_by_byte(पूर्णांक mem_type, पूर्णांक mode)
अणु
	अक्षर *ptr;
	पूर्णांक i, j, item;
	bool err;

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	item = माप(sizes)/माप(पूर्णांक);

	क्रम (i = 0; i < item; i++) अणु
		ptr = (अक्षर *)mte_allocate_memory(sizes[i], mem_type, 0, true);
		अगर (check_allocated_memory(ptr, sizes[i], mem_type, true) != KSFT_PASS)
			वापस KSFT_FAIL;
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, sizes[i]);
		/* Set some value in tagged memory */
		क्रम (j = 0; j < sizes[i]; j++)
			ptr[j] = '1';
		mte_रुको_after_trig();
		err = cur_mte_cxt.fault_valid;
		/* Check the buffer whether it is filled. */
		क्रम (j = 0; j < sizes[i] && !err; j++) अणु
			अगर (ptr[j] != '1')
				err = true;
		पूर्ण
		mte_मुक्त_memory((व्योम *)ptr, sizes[i], mem_type, true);

		अगर (err)
			अवरोध;
	पूर्ण
	अगर (!err)
		वापस KSFT_PASS;
	अन्यथा
		वापस KSFT_FAIL;
पूर्ण

अटल पूर्णांक check_buffer_underflow_by_byte(पूर्णांक mem_type, पूर्णांक mode,
					  पूर्णांक underflow_range)
अणु
	अक्षर *ptr;
	पूर्णांक i, j, item, last_index;
	bool err;
	अक्षर *und_ptr = शून्य;

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	item = माप(sizes)/माप(पूर्णांक);
	क्रम (i = 0; i < item; i++) अणु
		ptr = (अक्षर *)mte_allocate_memory_tag_range(sizes[i], mem_type, 0,
							    underflow_range, 0);
		अगर (check_allocated_memory_range(ptr, sizes[i], mem_type,
					       underflow_range, 0) != KSFT_PASS)
			वापस KSFT_FAIL;

		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, -underflow_range);
		last_index = 0;
		/* Set some value in tagged memory and make the buffer underflow */
		क्रम (j = sizes[i] - 1; (j >= -underflow_range) &&
				       (!cur_mte_cxt.fault_valid); j--) अणु
			ptr[j] = '1';
			last_index = j;
		पूर्ण
		mte_रुको_after_trig();
		err = false;
		/* Check whether the buffer is filled */
		क्रम (j = 0; j < sizes[i]; j++) अणु
			अगर (ptr[j] != '1') अणु
				err = true;
				ksft_prपूर्णांक_msg("Buffer is not filled at index:%d of ptr:0x%lx\n",
						j, ptr);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (err)
			जाओ check_buffer_underflow_by_byte_err;

		चयन (mode) अणु
		हाल MTE_NONE_ERR:
			अगर (cur_mte_cxt.fault_valid == true || last_index != -underflow_range) अणु
				err = true;
				अवरोध;
			पूर्ण
			/* There were no fault so the underflow area should be filled */
			und_ptr = (अक्षर *) MT_CLEAR_TAG((माप_प्रकार) ptr - underflow_range);
			क्रम (j = 0 ; j < underflow_range; j++) अणु
				अगर (und_ptr[j] != '1') अणु
					err = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल MTE_ASYNC_ERR:
			/* Imprecise fault should occur otherwise वापस error */
			अगर (cur_mte_cxt.fault_valid == false) अणु
				err = true;
				अवरोध;
			पूर्ण
			/*
			 * The imprecise fault is checked after the ग_लिखो to the buffer,
			 * so the underflow area beक्रमe the fault should be filled.
			 */
			und_ptr = (अक्षर *) MT_CLEAR_TAG((माप_प्रकार) ptr);
			क्रम (j = last_index ; j < 0 ; j++) अणु
				अगर (und_ptr[j] != '1') अणु
					err = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल MTE_SYNC_ERR:
			/* Precise fault should occur otherwise वापस error */
			अगर (!cur_mte_cxt.fault_valid || (last_index != (-1))) अणु
				err = true;
				अवरोध;
			पूर्ण
			/* Underflow area should not be filled */
			und_ptr = (अक्षर *) MT_CLEAR_TAG((माप_प्रकार) ptr);
			अगर (und_ptr[-1] == '1')
				err = true;
			अवरोध;
		शेष:
			err = true;
		अवरोध;
		पूर्ण
check_buffer_underflow_by_byte_err:
		mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[i], mem_type, underflow_range, 0);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस (err ? KSFT_FAIL : KSFT_PASS);
पूर्ण

अटल पूर्णांक check_buffer_overflow_by_byte(पूर्णांक mem_type, पूर्णांक mode,
					  पूर्णांक overflow_range)
अणु
	अक्षर *ptr;
	पूर्णांक i, j, item, last_index;
	bool err;
	माप_प्रकार tagged_size, overflow_size;
	अक्षर *over_ptr = शून्य;

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	item = माप(sizes)/माप(पूर्णांक);
	क्रम (i = 0; i < item; i++) अणु
		ptr = (अक्षर *)mte_allocate_memory_tag_range(sizes[i], mem_type, 0,
							    0, overflow_range);
		अगर (check_allocated_memory_range(ptr, sizes[i], mem_type,
						 0, overflow_range) != KSFT_PASS)
			वापस KSFT_FAIL;

		tagged_size = MT_ALIGN_UP(sizes[i]);

		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, sizes[i] + overflow_range);

		/* Set some value in tagged memory and make the buffer underflow */
		क्रम (j = 0, last_index = 0 ; (j < (sizes[i] + overflow_range)) &&
					     (cur_mte_cxt.fault_valid == false); j++) अणु
			ptr[j] = '1';
			last_index = j;
		पूर्ण
		mte_रुको_after_trig();
		err = false;
		/* Check whether the buffer is filled */
		क्रम (j = 0; j < sizes[i]; j++) अणु
			अगर (ptr[j] != '1') अणु
				err = true;
				ksft_prपूर्णांक_msg("Buffer is not filled at index:%d of ptr:0x%lx\n",
						j, ptr);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (err)
			जाओ check_buffer_overflow_by_byte_err;

		overflow_size = overflow_range - (tagged_size - sizes[i]);

		चयन (mode) अणु
		हाल MTE_NONE_ERR:
			अगर ((cur_mte_cxt.fault_valid == true) ||
			    (last_index != (sizes[i] + overflow_range - 1))) अणु
				err = true;
				अवरोध;
			पूर्ण
			/* There were no fault so the overflow area should be filled */
			over_ptr = (अक्षर *) MT_CLEAR_TAG((माप_प्रकार) ptr + tagged_size);
			क्रम (j = 0 ; j < overflow_size; j++) अणु
				अगर (over_ptr[j] != '1') अणु
					err = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल MTE_ASYNC_ERR:
			/* Imprecise fault should occur otherwise वापस error */
			अगर (cur_mte_cxt.fault_valid == false) अणु
				err = true;
				अवरोध;
			पूर्ण
			/*
			 * The imprecise fault is checked after the ग_लिखो to the buffer,
			 * so the overflow area should be filled beक्रमe the fault.
			 */
			over_ptr = (अक्षर *) MT_CLEAR_TAG((माप_प्रकार) ptr);
			क्रम (j = tagged_size ; j < last_index; j++) अणु
				अगर (over_ptr[j] != '1') अणु
					err = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल MTE_SYNC_ERR:
			/* Precise fault should occur otherwise वापस error */
			अगर (!cur_mte_cxt.fault_valid || (last_index != tagged_size)) अणु
				err = true;
				अवरोध;
			पूर्ण
			/* Underflow area should not be filled */
			over_ptr = (अक्षर *) MT_CLEAR_TAG((माप_प्रकार) ptr + tagged_size);
			क्रम (j = 0 ; j < overflow_size; j++) अणु
				अगर (over_ptr[j] == '1')
					err = true;
			पूर्ण
			अवरोध;
		शेष:
			err = true;
		अवरोध;
		पूर्ण
check_buffer_overflow_by_byte_err:
		mte_मुक्त_memory_tag_range((व्योम *)ptr, sizes[i], mem_type, 0, overflow_range);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस (err ? KSFT_FAIL : KSFT_PASS);
पूर्ण

अटल पूर्णांक check_buffer_by_block_iterate(पूर्णांक mem_type, पूर्णांक mode, माप_प्रकार size)
अणु
	अक्षर *src, *dst;
	पूर्णांक j, result = KSFT_PASS;
	क्रमागत mte_block_test_alloc alloc_type = UNTAGGED_TAGGED;

	क्रम (alloc_type = UNTAGGED_TAGGED; alloc_type < (पूर्णांक) BLOCK_ALLOC_MAX; alloc_type++) अणु
		चयन (alloc_type) अणु
		हाल UNTAGGED_TAGGED:
			src = (अक्षर *)mte_allocate_memory(size, mem_type, 0, false);
			अगर (check_allocated_memory(src, size, mem_type, false) != KSFT_PASS)
				वापस KSFT_FAIL;

			dst = (अक्षर *)mte_allocate_memory(size, mem_type, 0, true);
			अगर (check_allocated_memory(dst, size, mem_type, true) != KSFT_PASS) अणु
				mte_मुक्त_memory((व्योम *)src, size, mem_type, false);
				वापस KSFT_FAIL;
			पूर्ण

			अवरोध;
		हाल TAGGED_UNTAGGED:
			dst = (अक्षर *)mte_allocate_memory(size, mem_type, 0, false);
			अगर (check_allocated_memory(dst, size, mem_type, false) != KSFT_PASS)
				वापस KSFT_FAIL;

			src = (अक्षर *)mte_allocate_memory(size, mem_type, 0, true);
			अगर (check_allocated_memory(src, size, mem_type, true) != KSFT_PASS) अणु
				mte_मुक्त_memory((व्योम *)dst, size, mem_type, false);
				वापस KSFT_FAIL;
			पूर्ण
			अवरोध;
		हाल TAGGED_TAGGED:
			src = (अक्षर *)mte_allocate_memory(size, mem_type, 0, true);
			अगर (check_allocated_memory(src, size, mem_type, true) != KSFT_PASS)
				वापस KSFT_FAIL;

			dst = (अक्षर *)mte_allocate_memory(size, mem_type, 0, true);
			अगर (check_allocated_memory(dst, size, mem_type, true) != KSFT_PASS) अणु
				mte_मुक्त_memory((व्योम *)src, size, mem_type, true);
				वापस KSFT_FAIL;
			पूर्ण
			अवरोध;
		शेष:
			वापस KSFT_FAIL;
		पूर्ण

		cur_mte_cxt.fault_valid = false;
		result = KSFT_PASS;
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)dst, size);
		/* Set some value in memory and copy*/
		स_रखो((व्योम *)src, (पूर्णांक)'1', size);
		स_नकल((व्योम *)dst, (व्योम *)src, size);
		mte_रुको_after_trig();
		अगर (cur_mte_cxt.fault_valid) अणु
			result = KSFT_FAIL;
			जाओ check_buffer_by_block_err;
		पूर्ण
		/* Check the buffer whether it is filled. */
		क्रम (j = 0; j < size; j++) अणु
			अगर (src[j] != dst[j] || src[j] != '1') अणु
				result = KSFT_FAIL;
				अवरोध;
			पूर्ण
		पूर्ण
check_buffer_by_block_err:
		mte_मुक्त_memory((व्योम *)src, size, mem_type,
				MT_FETCH_TAG((uपूर्णांकptr_t)src) ? true : false);
		mte_मुक्त_memory((व्योम *)dst, size, mem_type,
				MT_FETCH_TAG((uपूर्णांकptr_t)dst) ? true : false);
		अगर (result != KSFT_PASS)
			वापस result;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक check_buffer_by_block(पूर्णांक mem_type, पूर्णांक mode)
अणु
	पूर्णांक i, item, result = KSFT_PASS;

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	item = माप(sizes)/माप(पूर्णांक);
	cur_mte_cxt.fault_valid = false;
	क्रम (i = 0; i < item; i++) अणु
		result = check_buffer_by_block_iterate(mem_type, mode, sizes[i]);
		अगर (result != KSFT_PASS)
			अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक compare_memory_tags(अक्षर *ptr, माप_प्रकार size, पूर्णांक tag)
अणु
	पूर्णांक i, new_tag;

	क्रम (i = 0 ; i < size ; i += MT_GRANULE_SIZE) अणु
		new_tag = MT_FETCH_TAG((uपूर्णांकptr_t)(mte_get_tag_address(ptr + i)));
		अगर (tag != new_tag) अणु
			ksft_prपूर्णांक_msg("FAIL: child mte tag mismatch\n");
			वापस KSFT_FAIL;
		पूर्ण
	पूर्ण
	वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक check_memory_initial_tags(पूर्णांक mem_type, पूर्णांक mode, पूर्णांक mapping)
अणु
	अक्षर *ptr;
	पूर्णांक run, fd;
	पूर्णांक total = माप(sizes)/माप(पूर्णांक);

	mte_चयन_mode(mode, MTE_ALLOW_NON_ZERO_TAG);
	क्रम (run = 0; run < total; run++) अणु
		/* check initial tags क्रम anonymous mmap */
		ptr = (अक्षर *)mte_allocate_memory(sizes[run], mem_type, mapping, false);
		अगर (check_allocated_memory(ptr, sizes[run], mem_type, false) != KSFT_PASS)
			वापस KSFT_FAIL;
		अगर (compare_memory_tags(ptr, sizes[run], 0) != KSFT_PASS) अणु
			mte_मुक्त_memory((व्योम *)ptr, sizes[run], mem_type, false);
			वापस KSFT_FAIL;
		पूर्ण
		mte_मुक्त_memory((व्योम *)ptr, sizes[run], mem_type, false);

		/* check initial tags क्रम file mmap */
		fd = create_temp_file();
		अगर (fd == -1)
			वापस KSFT_FAIL;
		ptr = (अक्षर *)mte_allocate_file_memory(sizes[run], mem_type, mapping, false, fd);
		अगर (check_allocated_memory(ptr, sizes[run], mem_type, false) != KSFT_PASS) अणु
			बंद(fd);
			वापस KSFT_FAIL;
		पूर्ण
		अगर (compare_memory_tags(ptr, sizes[run], 0) != KSFT_PASS) अणु
			mte_मुक्त_memory((व्योम *)ptr, sizes[run], mem_type, false);
			बंद(fd);
			वापस KSFT_FAIL;
		पूर्ण
		mte_मुक्त_memory((व्योम *)ptr, sizes[run], mem_type, false);
		बंद(fd);
	पूर्ण
	वापस KSFT_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;
	माप_प्रकार page_size = getpagesize();
	पूर्णांक item = माप(sizes)/माप(पूर्णांक);

	sizes[item - 3] = page_size - 1;
	sizes[item - 2] = page_size;
	sizes[item - 1] = page_size + 1;

	err = mte_शेष_setup();
	अगर (err)
		वापस err;

	/* Register संक_अंश handler */
	mte_रेजिस्टर_संकेत(संक_अंश, mte_शेष_handler);

	/* Set test plan */
	ksft_set_plan(20);

	/* Buffer by byte tests */
	evaluate_test(check_buffer_by_byte(USE_MMAP, MTE_SYNC_ERR),
	"Check buffer correctness by byte with sync err mode and mmap memory\n");
	evaluate_test(check_buffer_by_byte(USE_MMAP, MTE_ASYNC_ERR),
	"Check buffer correctness by byte with async err mode and mmap memory\n");
	evaluate_test(check_buffer_by_byte(USE_MPROTECT, MTE_SYNC_ERR),
	"Check buffer correctness by byte with sync err mode and mmap/mprotect memory\n");
	evaluate_test(check_buffer_by_byte(USE_MPROTECT, MTE_ASYNC_ERR),
	"Check buffer correctness by byte with async err mode and mmap/mprotect memory\n");

	/* Check buffer underflow with underflow size as 16 */
	evaluate_test(check_buffer_underflow_by_byte(USE_MMAP, MTE_SYNC_ERR, MT_GRANULE_SIZE),
	"Check buffer write underflow by byte with sync mode and mmap memory\n");
	evaluate_test(check_buffer_underflow_by_byte(USE_MMAP, MTE_ASYNC_ERR, MT_GRANULE_SIZE),
	"Check buffer write underflow by byte with async mode and mmap memory\n");
	evaluate_test(check_buffer_underflow_by_byte(USE_MMAP, MTE_NONE_ERR, MT_GRANULE_SIZE),
	"Check buffer write underflow by byte with tag check fault ignore and mmap memory\n");

	/* Check buffer underflow with underflow size as page size */
	evaluate_test(check_buffer_underflow_by_byte(USE_MMAP, MTE_SYNC_ERR, page_size),
	"Check buffer write underflow by byte with sync mode and mmap memory\n");
	evaluate_test(check_buffer_underflow_by_byte(USE_MMAP, MTE_ASYNC_ERR, page_size),
	"Check buffer write underflow by byte with async mode and mmap memory\n");
	evaluate_test(check_buffer_underflow_by_byte(USE_MMAP, MTE_NONE_ERR, page_size),
	"Check buffer write underflow by byte with tag check fault ignore and mmap memory\n");

	/* Check buffer overflow with overflow size as 16 */
	evaluate_test(check_buffer_overflow_by_byte(USE_MMAP, MTE_SYNC_ERR, MT_GRANULE_SIZE),
	"Check buffer write overflow by byte with sync mode and mmap memory\n");
	evaluate_test(check_buffer_overflow_by_byte(USE_MMAP, MTE_ASYNC_ERR, MT_GRANULE_SIZE),
	"Check buffer write overflow by byte with async mode and mmap memory\n");
	evaluate_test(check_buffer_overflow_by_byte(USE_MMAP, MTE_NONE_ERR, MT_GRANULE_SIZE),
	"Check buffer write overflow by byte with tag fault ignore mode and mmap memory\n");

	/* Buffer by block tests */
	evaluate_test(check_buffer_by_block(USE_MMAP, MTE_SYNC_ERR),
	"Check buffer write correctness by block with sync mode and mmap memory\n");
	evaluate_test(check_buffer_by_block(USE_MMAP, MTE_ASYNC_ERR),
	"Check buffer write correctness by block with async mode and mmap memory\n");
	evaluate_test(check_buffer_by_block(USE_MMAP, MTE_NONE_ERR),
	"Check buffer write correctness by block with tag fault ignore and mmap memory\n");

	/* Initial tags are supposed to be 0 */
	evaluate_test(check_memory_initial_tags(USE_MMAP, MTE_SYNC_ERR, MAP_PRIVATE),
	"Check initial tags with private mapping, sync error mode and mmap memory\n");
	evaluate_test(check_memory_initial_tags(USE_MPROTECT, MTE_SYNC_ERR, MAP_PRIVATE),
	"Check initial tags with private mapping, sync error mode and mmap/mprotect memory\n");
	evaluate_test(check_memory_initial_tags(USE_MMAP, MTE_SYNC_ERR, MAP_SHARED),
	"Check initial tags with shared mapping, sync error mode and mmap memory\n");
	evaluate_test(check_memory_initial_tags(USE_MPROTECT, MTE_SYNC_ERR, MAP_SHARED),
	"Check initial tags with shared mapping, sync error mode and mmap/mprotect memory\n");

	mte_restore_setup();
	ksft_prपूर्णांक_cnts();
	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
