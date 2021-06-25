<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_UTIL_PERF_HOOKS_H
#घोषणा PERF_UTIL_PERF_HOOKS_H

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

प्रकार व्योम (*perf_hook_func_t)(व्योम *ctx);
काष्ठा perf_hook_desc अणु
	स्थिर अक्षर * स्थिर hook_name;
	perf_hook_func_t * स्थिर p_hook_func;
	व्योम *hook_ctx;
पूर्ण;

बाह्य व्योम perf_hooks__invoke(स्थिर काष्ठा perf_hook_desc *);
बाह्य व्योम perf_hooks__recover(व्योम);

#घोषणा PERF_HOOK(name)					\
बाह्य काष्ठा perf_hook_desc __perf_hook_desc_##name;	\
अटल अंतरभूत व्योम perf_hooks__invoke_##name(व्योम)	\
अणु 							\
	perf_hooks__invoke(&__perf_hook_desc_##name);	\
पूर्ण

#समावेश "perf-hooks-list.h"
#अघोषित PERF_HOOK

बाह्य पूर्णांक
perf_hooks__set_hook(स्थिर अक्षर *hook_name,
		     perf_hook_func_t hook_func,
		     व्योम *hook_ctx);

बाह्य perf_hook_func_t
perf_hooks__get_hook(स्थिर अक्षर *hook_name);

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
