<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * perf_hooks.c
 *
 * Copyright (C) 2016 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2016 Huawei Inc.
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समलाँघ.स>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश "util/debug.h"
#समावेश "util/perf-hooks.h"

अटल sigलाँघ_बफ jmpbuf;
अटल स्थिर काष्ठा perf_hook_desc *current_perf_hook;

व्योम perf_hooks__invoke(स्थिर काष्ठा perf_hook_desc *desc)
अणु
	अगर (!(desc && desc->p_hook_func && *desc->p_hook_func))
		वापस;

	अगर (sigबनाओ_लाँघ(jmpbuf, 1)) अणु
		pr_warning("Fatal error (SEGFAULT) in perf hook '%s'\n",
			   desc->hook_name);
		*(current_perf_hook->p_hook_func) = शून्य;
	पूर्ण अन्यथा अणु
		current_perf_hook = desc;
		(**desc->p_hook_func)(desc->hook_ctx);
	पूर्ण
	current_perf_hook = शून्य;
पूर्ण

व्योम perf_hooks__recover(व्योम)
अणु
	अगर (current_perf_hook)
		sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

#घोषणा PERF_HOOK(name)					\
perf_hook_func_t __perf_hook_func_##name = शून्य;	\
काष्ठा perf_hook_desc __perf_hook_desc_##name =		\
	अणु.hook_name = #name,				\
	 .p_hook_func = &__perf_hook_func_##name,	\
	 .hook_ctx = शून्यपूर्ण;
#समावेश "perf-hooks-list.h"
#अघोषित PERF_HOOK

#घोषणा PERF_HOOK(name)		\
	&__perf_hook_desc_##name,

अटल काष्ठा perf_hook_desc *perf_hooks[] = अणु
#समावेश "perf-hooks-list.h"
पूर्ण;
#अघोषित PERF_HOOK

पूर्णांक perf_hooks__set_hook(स्थिर अक्षर *hook_name,
			 perf_hook_func_t hook_func,
			 व्योम *hook_ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(perf_hooks); i++) अणु
		अगर (म_भेद(hook_name, perf_hooks[i]->hook_name) != 0)
			जारी;

		अगर (*(perf_hooks[i]->p_hook_func))
			pr_warning("Overwrite existing hook: %s\n", hook_name);
		*(perf_hooks[i]->p_hook_func) = hook_func;
		perf_hooks[i]->hook_ctx = hook_ctx;
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

perf_hook_func_t perf_hooks__get_hook(स्थिर अक्षर *hook_name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(perf_hooks); i++) अणु
		अगर (म_भेद(hook_name, perf_hooks[i]->hook_name) != 0)
			जारी;

		वापस *(perf_hooks[i]->p_hook_func);
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण
