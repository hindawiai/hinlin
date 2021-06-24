<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains core hardware tag-based KASAN code.
 *
 * Copyright (c) 2020 Google, Inc.
 * Author: Andrey Konovalov <andreyknvl@google.com>
 */

#घोषणा pr_fmt(fmt) "kasan: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memory.h>
#समावेश <linux/mm.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "kasan.h"

क्रमागत kasan_arg अणु
	KASAN_ARG_DEFAULT,
	KASAN_ARG_OFF,
	KASAN_ARG_ON,
पूर्ण;

क्रमागत kasan_arg_mode अणु
	KASAN_ARG_MODE_DEFAULT,
	KASAN_ARG_MODE_SYNC,
	KASAN_ARG_MODE_ASYNC,
पूर्ण;

क्रमागत kasan_arg_stacktrace अणु
	KASAN_ARG_STACKTRACE_DEFAULT,
	KASAN_ARG_STACKTRACE_OFF,
	KASAN_ARG_STACKTRACE_ON,
पूर्ण;

क्रमागत kasan_arg_fault अणु
	KASAN_ARG_FAULT_DEFAULT,
	KASAN_ARG_FAULT_REPORT,
	KASAN_ARG_FAULT_PANIC,
पूर्ण;

अटल क्रमागत kasan_arg kasan_arg __ro_after_init;
अटल क्रमागत kasan_arg_mode kasan_arg_mode __ro_after_init;
अटल क्रमागत kasan_arg_stacktrace kasan_arg_stacktrace __ro_after_init;
अटल क्रमागत kasan_arg_fault kasan_arg_fault __ro_after_init;

/* Whether KASAN is enabled at all. */
DEFINE_STATIC_KEY_FALSE(kasan_flag_enabled);
EXPORT_SYMBOL(kasan_flag_enabled);

/* Whether the asynchronous mode is enabled. */
bool kasan_flag_async __ro_after_init;
EXPORT_SYMBOL_GPL(kasan_flag_async);

/* Whether to collect alloc/मुक्त stack traces. */
DEFINE_STATIC_KEY_FALSE(kasan_flag_stacktrace);

/* Whether to panic or prपूर्णांक a report and disable tag checking on fault. */
bool kasan_flag_panic __ro_after_init;

/* kasan=off/on */
अटल पूर्णांक __init early_kasan_flag(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (!म_भेद(arg, "off"))
		kasan_arg = KASAN_ARG_OFF;
	अन्यथा अगर (!म_भेद(arg, "on"))
		kasan_arg = KASAN_ARG_ON;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
early_param("kasan", early_kasan_flag);

/* kasan.mode=sync/async */
अटल पूर्णांक __init early_kasan_mode(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (!म_भेद(arg, "sync"))
		kasan_arg_mode = KASAN_ARG_MODE_SYNC;
	अन्यथा अगर (!म_भेद(arg, "async"))
		kasan_arg_mode = KASAN_ARG_MODE_ASYNC;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
early_param("kasan.mode", early_kasan_mode);

/* kasan.stacktrace=off/on */
अटल पूर्णांक __init early_kasan_flag_stacktrace(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (!म_भेद(arg, "off"))
		kasan_arg_stacktrace = KASAN_ARG_STACKTRACE_OFF;
	अन्यथा अगर (!म_भेद(arg, "on"))
		kasan_arg_stacktrace = KASAN_ARG_STACKTRACE_ON;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
early_param("kasan.stacktrace", early_kasan_flag_stacktrace);

/* kasan.fault=report/panic */
अटल पूर्णांक __init early_kasan_fault(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (!म_भेद(arg, "report"))
		kasan_arg_fault = KASAN_ARG_FAULT_REPORT;
	अन्यथा अगर (!म_भेद(arg, "panic"))
		kasan_arg_fault = KASAN_ARG_FAULT_PANIC;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण
early_param("kasan.fault", early_kasan_fault);

/* kasan_init_hw_tags_cpu() is called क्रम each CPU. */
व्योम kasan_init_hw_tags_cpu(व्योम)
अणु
	/*
	 * There's no need to check that the hardware is MTE-capable here,
	 * as this function is only called क्रम MTE-capable hardware.
	 */

	/* If KASAN is disabled via command line, करोn't initialize it. */
	अगर (kasan_arg == KASAN_ARG_OFF)
		वापस;

	hw_init_tags(KASAN_TAG_MAX);

	/*
	 * Enable async mode only when explicitly requested through
	 * the command line.
	 */
	अगर (kasan_arg_mode == KASAN_ARG_MODE_ASYNC)
		hw_enable_tagging_async();
	अन्यथा
		hw_enable_tagging_sync();
पूर्ण

/* kasan_init_hw_tags() is called once on boot CPU. */
व्योम __init kasan_init_hw_tags(व्योम)
अणु
	/* If hardware करोesn't support MTE, don't initialize KASAN. */
	अगर (!प्रणाली_supports_mte())
		वापस;

	/* If KASAN is disabled via command line, करोn't initialize it. */
	अगर (kasan_arg == KASAN_ARG_OFF)
		वापस;

	/* Enable KASAN. */
	अटल_branch_enable(&kasan_flag_enabled);

	चयन (kasan_arg_mode) अणु
	हाल KASAN_ARG_MODE_DEFAULT:
		/*
		 * Default to sync mode.
		 * Do nothing, kasan_flag_async keeps its शेष value.
		 */
		अवरोध;
	हाल KASAN_ARG_MODE_SYNC:
		/* Do nothing, kasan_flag_async keeps its शेष value. */
		अवरोध;
	हाल KASAN_ARG_MODE_ASYNC:
		/* Async mode enabled. */
		kasan_flag_async = true;
		अवरोध;
	पूर्ण

	चयन (kasan_arg_stacktrace) अणु
	हाल KASAN_ARG_STACKTRACE_DEFAULT:
		/* Default to enabling stack trace collection. */
		अटल_branch_enable(&kasan_flag_stacktrace);
		अवरोध;
	हाल KASAN_ARG_STACKTRACE_OFF:
		/* Do nothing, kasan_flag_stacktrace keeps its शेष value. */
		अवरोध;
	हाल KASAN_ARG_STACKTRACE_ON:
		अटल_branch_enable(&kasan_flag_stacktrace);
		अवरोध;
	पूर्ण

	चयन (kasan_arg_fault) अणु
	हाल KASAN_ARG_FAULT_DEFAULT:
		/*
		 * Default to no panic on report.
		 * Do nothing, kasan_flag_panic keeps its शेष value.
		 */
		अवरोध;
	हाल KASAN_ARG_FAULT_REPORT:
		/* Do nothing, kasan_flag_panic keeps its शेष value. */
		अवरोध;
	हाल KASAN_ARG_FAULT_PANIC:
		/* Enable panic on report. */
		kasan_flag_panic = true;
		अवरोध;
	पूर्ण

	pr_info("KernelAddressSanitizer initialized\n");
पूर्ण

व्योम kasan_set_मुक्त_info(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;

	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (alloc_meta)
		kasan_set_track(&alloc_meta->मुक्त_track[0], GFP_NOWAIT);
पूर्ण

काष्ठा kasan_track *kasan_get_मुक्त_track(काष्ठा kmem_cache *cache,
				व्योम *object, u8 tag)
अणु
	काष्ठा kasan_alloc_meta *alloc_meta;

	alloc_meta = kasan_get_alloc_meta(cache, object);
	अगर (!alloc_meta)
		वापस शून्य;

	वापस &alloc_meta->मुक्त_track[0];
पूर्ण

#अगर IS_ENABLED(CONFIG_KASAN_KUNIT_TEST)

व्योम kasan_set_tagging_report_once(bool state)
अणु
	hw_set_tagging_report_once(state);
पूर्ण
EXPORT_SYMBOL_GPL(kasan_set_tagging_report_once);

व्योम kasan_enable_tagging_sync(व्योम)
अणु
	hw_enable_tagging_sync();
पूर्ण
EXPORT_SYMBOL_GPL(kasan_enable_tagging_sync);

व्योम kasan_क्रमce_async_fault(व्योम)
अणु
	hw_क्रमce_async_tag_fault();
पूर्ण
EXPORT_SYMBOL_GPL(kasan_क्रमce_async_fault);

#पूर्ण_अगर
