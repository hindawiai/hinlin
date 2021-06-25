<शैली गुरु>
/*
 * Internal Header क्रम the Direct Rendering Manager
 *
 * Copyright 2018 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _DRM_UTIL_H_
#घोषणा _DRM_UTIL_H_

/**
 * DOC: drm utils
 *
 * Macros and अंतरभूत functions that करोes not naturally beदीर्घ in other places
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/preempt.h>
#समावेश <linux/smp.h>

/*
 * Use EXPORT_SYMBOL_FOR_TESTS_ONLY() क्रम functions that shall
 * only be visible क्रम drmselftests.
 */
#अगर defined(CONFIG_DRM_EXPORT_FOR_TESTS)
#घोषणा EXPORT_SYMBOL_FOR_TESTS_ONLY(x) EXPORT_SYMBOL(x)
#अन्यथा
#घोषणा EXPORT_SYMBOL_FOR_TESTS_ONLY(x)
#पूर्ण_अगर

/**
 * क्रम_each_अगर - helper क्रम handling conditionals in various क्रम_each macros
 * @condition: The condition to check
 *
 * Typical use::
 *
 *	#घोषणा क्रम_each_foo_bar(x, y) \'
 *		list_क्रम_each_entry(x, y->list, head) \'
 *			क्रम_each_अगर(x->something == SOMETHING)
 *
 * The क्रम_each_अगर() macro makes the use of क्रम_each_foo_bar() less error
 * prone.
 */
#घोषणा क्रम_each_अगर(condition) अगर (!(condition)) अणुपूर्ण अन्यथा

/**
 * drm_can_sleep - वापसs true अगर currently okay to sleep
 *
 * This function shall not be used in new code.
 * The check क्रम running in atomic context may not work - see linux/preempt.h.
 *
 * FIXME: All users of drm_can_sleep should be हटाओd (see toकरो.rst)
 *
 * Returns:
 * False अगर kgdb is active, we are in atomic context or irqs are disabled.
 */
अटल अंतरभूत bool drm_can_sleep(व्योम)
अणु
	अगर (in_atomic() || in_dbg_master() || irqs_disabled())
		वापस false;
	वापस true;
पूर्ण

#पूर्ण_अगर
