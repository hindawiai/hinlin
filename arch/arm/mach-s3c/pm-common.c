<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2013 Samsung Electronics Co., Ltd.
//	Tomasz Figa <t.figa@samsung.com>
// Copyright (C) 2008 Openmoko, Inc.
// Copyright (C) 2004-2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// Samsung common घातer management helper functions.

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>

#समावेश "pm-common.h"

/* helper functions to save and restore रेजिस्टर state */

/**
 * s3c_pm_करो_save() - save a set of रेजिस्टरs क्रम restoration on resume.
 * @ptr: Poपूर्णांकer to an array of रेजिस्टरs.
 * @count: Size of the ptr array.
 *
 * Run through the list of रेजिस्टरs given, saving their contents in the
 * array क्रम later restoration when we wakeup.
 */
व्योम s3c_pm_करो_save(काष्ठा sleep_save *ptr, पूर्णांक count)
अणु
	क्रम (; count > 0; count--, ptr++) अणु
		ptr->val = पढ़ोl_relaxed(ptr->reg);
		S3C_PMDBG("saved %p value %08lx\n", ptr->reg, ptr->val);
	पूर्ण
पूर्ण

/**
 * s3c_pm_करो_restore() - restore रेजिस्टर values from the save list.
 * @ptr: Poपूर्णांकer to an array of रेजिस्टरs.
 * @count: Size of the ptr array.
 *
 * Restore the रेजिस्टर values saved from s3c_pm_करो_save().
 *
 * Note, we करो not use S3C_PMDBG() in here, as the प्रणाली may not have
 * restore the UARTs state yet
*/

व्योम s3c_pm_करो_restore(स्थिर काष्ठा sleep_save *ptr, पूर्णांक count)
अणु
	क्रम (; count > 0; count--, ptr++) अणु
		pr_debug("restore %p (restore %08lx, was %08x)\n",
				ptr->reg, ptr->val, पढ़ोl_relaxed(ptr->reg));

		ग_लिखोl_relaxed(ptr->val, ptr->reg);
	पूर्ण
पूर्ण

/**
 * s3c_pm_करो_restore_core() - early restore रेजिस्टर values from save list.
 * @ptr: Poपूर्णांकer to an array of रेजिस्टरs.
 * @count: Size of the ptr array.
 *
 * This is similar to s3c_pm_करो_restore() except we try and minimise the
 * side effects of the function in हाल रेजिस्टरs that hardware might need
 * to work has been restored.
 *
 * WARNING: Do not put any debug in here that may effect memory or use
 * peripherals, as things may be changing!
*/

व्योम s3c_pm_करो_restore_core(स्थिर काष्ठा sleep_save *ptr, पूर्णांक count)
अणु
	क्रम (; count > 0; count--, ptr++)
		ग_लिखोl_relaxed(ptr->val, ptr->reg);
पूर्ण
