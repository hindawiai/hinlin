<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_TEST_LLVM_H
#घोषणा PERF_TEST_LLVM_H

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#समावेश <मानकघोष.स> /* क्रम माप_प्रकार */
#समावेश <stdbool.h> /* क्रम bool */

बाह्य स्थिर अक्षर test_llvm__bpf_base_prog[];
बाह्य स्थिर अक्षर test_llvm__bpf_test_kbuild_prog[];
बाह्य स्थिर अक्षर test_llvm__bpf_test_prologue_prog[];
बाह्य स्थिर अक्षर test_llvm__bpf_test_relocation[];

क्रमागत test_llvm__testहाल अणु
	LLVM_TESTCASE_BASE,
	LLVM_TESTCASE_KBUILD,
	LLVM_TESTCASE_BPF_PROLOGUE,
	LLVM_TESTCASE_BPF_RELOCATION,
	__LLVM_TESTCASE_MAX,
पूर्ण;

पूर्णांक test_llvm__fetch_bpf_obj(व्योम **p_obj_buf, माप_प्रकार *p_obj_buf_sz,
			     क्रमागत test_llvm__testहाल index, bool क्रमce,
			     bool *should_load_fail);
#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
