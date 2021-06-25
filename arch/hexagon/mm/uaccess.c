<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

/*
 * Support क्रम user memory access from kernel.  This will
 * probably be अंतरभूतd क्रम perक्रमmance at some poपूर्णांक, but
 * क्रम ease of debug, and to a lesser degree क्रम code size,
 * we implement here as subroutines.
 */
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pgtable.h>

/*
 * For clear_user(), exploit previously defined copy_to_user function
 * and the fact that we've got a handy zero page defined in kernel/head.S
 *
 * dczero here would be even faster.
 */
__kernel_माप_प्रकार __clear_user_hexagon(व्योम __user *dest, अचिन्हित दीर्घ count)
अणु
	दीर्घ uncleared;

	जबतक (count > PAGE_SIZE) अणु
		uncleared = raw_copy_to_user(dest, &empty_zero_page, PAGE_SIZE);
		अगर (uncleared)
			वापस count - (PAGE_SIZE - uncleared);
		count -= PAGE_SIZE;
		dest += PAGE_SIZE;
	पूर्ण
	अगर (count)
		count = raw_copy_to_user(dest, &empty_zero_page, count);

	वापस count;
पूर्ण

अचिन्हित दीर्घ clear_user_hexagon(व्योम __user *dest, अचिन्हित दीर्घ count)
अणु
	अगर (!access_ok(dest, count))
		वापस count;
	अन्यथा
		वापस __clear_user_hexagon(dest, count);
पूर्ण
