<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_UTIL_CLANG_C_H
#घोषणा PERF_UTIL_CLANG_C_H

#समावेश <मानकघोष.स>	/* क्रम माप_प्रकार */

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBCLANGLLVM_SUPPORT
बाह्य व्योम perf_clang__init(व्योम);
बाह्य व्योम perf_clang__cleanup(व्योम);

बाह्य पूर्णांक test__clang_to_IR(व्योम);
बाह्य पूर्णांक test__clang_to_obj(व्योम);

बाह्य पूर्णांक perf_clang__compile_bpf(स्थिर अक्षर *filename,
				   व्योम **p_obj_buf,
				   माप_प्रकार *p_obj_buf_sz);
#अन्यथा

#समावेश <त्रुटिसं.स>
#समावेश <linux/compiler.h>	/* क्रम __maybe_unused */

अटल अंतरभूत व्योम perf_clang__init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम perf_clang__cleanup(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक test__clang_to_IR(व्योम) अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक test__clang_to_obj(व्योम) अणु वापस -1;पूर्ण

अटल अंतरभूत पूर्णांक
perf_clang__compile_bpf(स्थिर अक्षर *filename __maybe_unused,
			व्योम **p_obj_buf __maybe_unused,
			माप_प्रकार *p_obj_buf_sz __maybe_unused)
अणु
	वापस -ENOTSUP;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
