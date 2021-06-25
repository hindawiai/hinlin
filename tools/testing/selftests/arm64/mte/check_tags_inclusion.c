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
#घोषणा RUNS			(MT_TAG_COUNT * 2)
#घोषणा MTE_LAST_TAG_MASK	(0x7FFF)

अटल पूर्णांक verअगरy_mte_poपूर्णांकer_validity(अक्षर *ptr, पूर्णांक mode)
अणु
	mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, BUFFER_SIZE);
	/* Check the validity of the tagged poपूर्णांकer */
	स_रखो((व्योम *)ptr, '1', BUFFER_SIZE);
	mte_रुको_after_trig();
	अगर (cur_mte_cxt.fault_valid)
		वापस KSFT_FAIL;
	/* Proceed further क्रम nonzero tags */
	अगर (!MT_FETCH_TAG((uपूर्णांकptr_t)ptr))
		वापस KSFT_PASS;
	mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, BUFFER_SIZE + 1);
	/* Check the validity outside the range */
	ptr[BUFFER_SIZE] = '2';
	mte_रुको_after_trig();
	अगर (!cur_mte_cxt.fault_valid)
		वापस KSFT_FAIL;
	अन्यथा
		वापस KSFT_PASS;
पूर्ण

अटल पूर्णांक check_single_included_tags(पूर्णांक mem_type, पूर्णांक mode)
अणु
	अक्षर *ptr;
	पूर्णांक tag, run, result = KSFT_PASS;

	ptr = (अक्षर *)mte_allocate_memory(BUFFER_SIZE + MT_GRANULE_SIZE, mem_type, 0, false);
	अगर (check_allocated_memory(ptr, BUFFER_SIZE + MT_GRANULE_SIZE,
				   mem_type, false) != KSFT_PASS)
		वापस KSFT_FAIL;

	क्रम (tag = 0; (tag < MT_TAG_COUNT) && (result == KSFT_PASS); tag++) अणु
		mte_चयन_mode(mode, MT_INCLUDE_VALID_TAG(tag));
		/* Try to catch a excluded tag by a number of tries. */
		क्रम (run = 0; (run < RUNS) && (result == KSFT_PASS); run++) अणु
			ptr = (अक्षर *)mte_insert_tags(ptr, BUFFER_SIZE);
			/* Check tag value */
			अगर (MT_FETCH_TAG((uपूर्णांकptr_t)ptr) == tag) अणु
				ksft_prपूर्णांक_msg("FAIL: wrong tag = 0x%x with include mask=0x%x\n",
					       MT_FETCH_TAG((uपूर्णांकptr_t)ptr),
					       MT_INCLUDE_VALID_TAG(tag));
				result = KSFT_FAIL;
				अवरोध;
			पूर्ण
			result = verअगरy_mte_poपूर्णांकer_validity(ptr, mode);
		पूर्ण
	पूर्ण
	mte_मुक्त_memory_tag_range((व्योम *)ptr, BUFFER_SIZE, mem_type, 0, MT_GRANULE_SIZE);
	वापस result;
पूर्ण

अटल पूर्णांक check_multiple_included_tags(पूर्णांक mem_type, पूर्णांक mode)
अणु
	अक्षर *ptr;
	पूर्णांक tag, run, result = KSFT_PASS;
	अचिन्हित दीर्घ excl_mask = 0;

	ptr = (अक्षर *)mte_allocate_memory(BUFFER_SIZE + MT_GRANULE_SIZE, mem_type, 0, false);
	अगर (check_allocated_memory(ptr, BUFFER_SIZE + MT_GRANULE_SIZE,
				   mem_type, false) != KSFT_PASS)
		वापस KSFT_FAIL;

	क्रम (tag = 0; (tag < MT_TAG_COUNT - 1) && (result == KSFT_PASS); tag++) अणु
		excl_mask |= 1 << tag;
		mte_चयन_mode(mode, MT_INCLUDE_VALID_TAGS(excl_mask));
		/* Try to catch a excluded tag by a number of tries. */
		क्रम (run = 0; (run < RUNS) && (result == KSFT_PASS); run++) अणु
			ptr = (अक्षर *)mte_insert_tags(ptr, BUFFER_SIZE);
			/* Check tag value */
			अगर (MT_FETCH_TAG((uपूर्णांकptr_t)ptr) < tag) अणु
				ksft_prपूर्णांक_msg("FAIL: wrong tag = 0x%x with include mask=0x%x\n",
					       MT_FETCH_TAG((uपूर्णांकptr_t)ptr),
					       MT_INCLUDE_VALID_TAGS(excl_mask));
				result = KSFT_FAIL;
				अवरोध;
			पूर्ण
			result = verअगरy_mte_poपूर्णांकer_validity(ptr, mode);
		पूर्ण
	पूर्ण
	mte_मुक्त_memory_tag_range((व्योम *)ptr, BUFFER_SIZE, mem_type, 0, MT_GRANULE_SIZE);
	वापस result;
पूर्ण

अटल पूर्णांक check_all_included_tags(पूर्णांक mem_type, पूर्णांक mode)
अणु
	अक्षर *ptr;
	पूर्णांक run, result = KSFT_PASS;

	ptr = (अक्षर *)mte_allocate_memory(BUFFER_SIZE + MT_GRANULE_SIZE, mem_type, 0, false);
	अगर (check_allocated_memory(ptr, BUFFER_SIZE + MT_GRANULE_SIZE,
				   mem_type, false) != KSFT_PASS)
		वापस KSFT_FAIL;

	mte_चयन_mode(mode, MT_INCLUDE_TAG_MASK);
	/* Try to catch a excluded tag by a number of tries. */
	क्रम (run = 0; (run < RUNS) && (result == KSFT_PASS); run++) अणु
		ptr = (अक्षर *)mte_insert_tags(ptr, BUFFER_SIZE);
		/*
		 * Here tag byte can be between 0x0 to 0xF (full allowed range)
		 * so no need to match so just verअगरy अगर it is writable.
		 */
		result = verअगरy_mte_poपूर्णांकer_validity(ptr, mode);
	पूर्ण
	mte_मुक्त_memory_tag_range((व्योम *)ptr, BUFFER_SIZE, mem_type, 0, MT_GRANULE_SIZE);
	वापस result;
पूर्ण

अटल पूर्णांक check_none_included_tags(पूर्णांक mem_type, पूर्णांक mode)
अणु
	अक्षर *ptr;
	पूर्णांक run;

	ptr = (अक्षर *)mte_allocate_memory(BUFFER_SIZE, mem_type, 0, false);
	अगर (check_allocated_memory(ptr, BUFFER_SIZE, mem_type, false) != KSFT_PASS)
		वापस KSFT_FAIL;

	mte_चयन_mode(mode, MT_EXCLUDE_TAG_MASK);
	/* Try to catch a excluded tag by a number of tries. */
	क्रम (run = 0; run < RUNS; run++) अणु
		ptr = (अक्षर *)mte_insert_tags(ptr, BUFFER_SIZE);
		/* Here all tags exluded so tag value generated should be 0 */
		अगर (MT_FETCH_TAG((uपूर्णांकptr_t)ptr)) अणु
			ksft_prपूर्णांक_msg("FAIL: included tag value found\n");
			mte_मुक्त_memory((व्योम *)ptr, BUFFER_SIZE, mem_type, true);
			वापस KSFT_FAIL;
		पूर्ण
		mte_initialize_current_context(mode, (uपूर्णांकptr_t)ptr, BUFFER_SIZE);
		/* Check the ग_लिखो validity of the untagged poपूर्णांकer */
		स_रखो((व्योम *)ptr, '1', BUFFER_SIZE);
		mte_रुको_after_trig();
		अगर (cur_mte_cxt.fault_valid)
			अवरोध;
	पूर्ण
	mte_मुक्त_memory((व्योम *)ptr, BUFFER_SIZE, mem_type, false);
	अगर (cur_mte_cxt.fault_valid)
		वापस KSFT_FAIL;
	अन्यथा
		वापस KSFT_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;

	err = mte_शेष_setup();
	अगर (err)
		वापस err;

	/* Register संक_अंश handler */
	mte_रेजिस्टर_संकेत(संक_अंश, mte_शेष_handler);

	/* Set test plan */
	ksft_set_plan(4);

	evaluate_test(check_single_included_tags(USE_MMAP, MTE_SYNC_ERR),
		      "Check an included tag value with sync mode\n");
	evaluate_test(check_multiple_included_tags(USE_MMAP, MTE_SYNC_ERR),
		      "Check different included tags value with sync mode\n");
	evaluate_test(check_none_included_tags(USE_MMAP, MTE_SYNC_ERR),
		      "Check none included tags value with sync mode\n");
	evaluate_test(check_all_included_tags(USE_MMAP, MTE_SYNC_ERR),
		      "Check all included tags value with sync mode\n");

	mte_restore_setup();
	ksft_prपूर्णांक_cnts();
	वापस ksft_get_fail_cnt() == 0 ? KSFT_PASS : KSFT_FAIL;
पूर्ण
