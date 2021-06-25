<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 ARM Limited */

#अगर_अघोषित _MTE_COMMON_UTIL_H
#घोषणा _MTE_COMMON_UTIL_H

#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <sys/auxv.h>
#समावेश <sys/mman.h>
#समावेश <sys/prctl.h>
#समावेश "mte_def.h"
#समावेश "kselftest.h"

क्रमागत mte_mem_type अणु
	USE_MALLOC,
	USE_MMAP,
	USE_MPROTECT,
पूर्ण;

क्रमागत mte_mode अणु
	MTE_NONE_ERR,
	MTE_SYNC_ERR,
	MTE_ASYNC_ERR,
पूर्ण;

काष्ठा mte_fault_cxt अणु
	/* Address start which triggers mte tag fault */
	अचिन्हित दीर्घ trig_addr;
	/* Address range क्रम mte tag fault and negative value means underflow */
	sमाप_प्रकार trig_range;
	/* siginfo si code */
	अचिन्हित दीर्घ trig_si_code;
	/* Flag to denote अगर correct fault caught */
	bool fault_valid;
पूर्ण;

बाह्य काष्ठा mte_fault_cxt cur_mte_cxt;

/* MTE utility functions */
व्योम mte_शेष_handler(पूर्णांक signum, siginfo_t *si, व्योम *uc);
व्योम mte_रेजिस्टर_संकेत(पूर्णांक संकेत, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *));
व्योम mte_रुको_after_trig(व्योम);
व्योम *mte_allocate_memory(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping, bool tags);
व्योम *mte_allocate_memory_tag_range(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping,
				    माप_प्रकार range_beक्रमe, माप_प्रकार range_after);
व्योम *mte_allocate_file_memory(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping,
			       bool tags, पूर्णांक fd);
व्योम *mte_allocate_file_memory_tag_range(माप_प्रकार size, पूर्णांक mem_type, पूर्णांक mapping,
					 माप_प्रकार range_beक्रमe, माप_प्रकार range_after, पूर्णांक fd);
व्योम mte_मुक्त_memory(व्योम *ptr, माप_प्रकार size, पूर्णांक mem_type, bool tags);
व्योम mte_मुक्त_memory_tag_range(व्योम *ptr, माप_प्रकार size, पूर्णांक mem_type,
			       माप_प्रकार range_beक्रमe, माप_प्रकार range_after);
व्योम *mte_insert_tags(व्योम *ptr, माप_प्रकार size);
व्योम mte_clear_tags(व्योम *ptr, माप_प्रकार size);
पूर्णांक mte_शेष_setup(व्योम);
व्योम mte_restore_setup(व्योम);
पूर्णांक mte_चयन_mode(पूर्णांक mte_option, अचिन्हित दीर्घ incl_mask);
व्योम mte_initialize_current_context(पूर्णांक mode, uपूर्णांकptr_t ptr, sमाप_प्रकार range);

/* Common utility functions */
पूर्णांक create_temp_file(व्योम);

/* Assembly MTE utility functions */
व्योम *mte_insert_अक्रमom_tag(व्योम *ptr);
व्योम *mte_insert_new_tag(व्योम *ptr);
व्योम *mte_get_tag_address(व्योम *ptr);
व्योम mte_set_tag_address_range(व्योम *ptr, पूर्णांक range);
व्योम mte_clear_tag_address_range(व्योम *ptr, पूर्णांक range);
व्योम mte_disable_pstate_tco(व्योम);
व्योम mte_enable_pstate_tco(व्योम);
अचिन्हित पूर्णांक mte_get_pstate_tco(व्योम);

/* Test framework अटल अंतरभूत functions/macros */
अटल अंतरभूत व्योम evaluate_test(पूर्णांक err, स्थिर अक्षर *msg)
अणु
	अगर (err == KSFT_PASS)
		ksft_test_result_pass(msg);
	अन्यथा अगर (err == KSFT_FAIL)
		ksft_test_result_fail(msg);
पूर्ण

अटल अंतरभूत पूर्णांक check_allocated_memory(व्योम *ptr, माप_प्रकार size,
					 पूर्णांक mem_type, bool tags)
अणु
	अगर (ptr == शून्य) अणु
		ksft_prपूर्णांक_msg("FAIL: memory allocation\n");
		वापस KSFT_FAIL;
	पूर्ण

	अगर (tags && !MT_FETCH_TAG((uपूर्णांकptr_t)ptr)) अणु
		ksft_prपूर्णांक_msg("FAIL: tag not found at addr(%p)\n", ptr);
		mte_मुक्त_memory((व्योम *)ptr, size, mem_type, false);
		वापस KSFT_FAIL;
	पूर्ण

	वापस KSFT_PASS;
पूर्ण

अटल अंतरभूत पूर्णांक check_allocated_memory_range(व्योम *ptr, माप_प्रकार size, पूर्णांक mem_type,
					       माप_प्रकार range_beक्रमe, माप_प्रकार range_after)
अणु
	अगर (ptr == शून्य) अणु
		ksft_prपूर्णांक_msg("FAIL: memory allocation\n");
		वापस KSFT_FAIL;
	पूर्ण

	अगर (!MT_FETCH_TAG((uपूर्णांकptr_t)ptr)) अणु
		ksft_prपूर्णांक_msg("FAIL: tag not found at addr(%p)\n", ptr);
		mte_मुक्त_memory_tag_range((व्योम *)ptr, size, mem_type, range_beक्रमe,
					  range_after);
		वापस KSFT_FAIL;
	पूर्ण
	वापस KSFT_PASS;
पूर्ण

#पूर्ण_अगर /* _MTE_COMMON_UTIL_H */
