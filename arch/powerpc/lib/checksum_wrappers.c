<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) IBM Corporation, 2010
 *
 * Author: Anton Blanअक्षरd <anton@au.ibm.com>
 */
#समावेश <linux/export.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/checksum.h>
#समावेश <linux/uaccess.h>

__wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst,
			       पूर्णांक len)
अणु
	__wsum csum;

	अगर (unlikely(!user_पढ़ो_access_begin(src, len)))
		वापस 0;

	csum = csum_partial_copy_generic((व्योम __क्रमce *)src, dst, len);

	user_पढ़ो_access_end();
	वापस csum;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_from_user);

__wsum csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len)
अणु
	__wsum csum;

	अगर (unlikely(!user_ग_लिखो_access_begin(dst, len)))
		वापस 0;

	csum = csum_partial_copy_generic(src, (व्योम __क्रमce *)dst, len);

	user_ग_लिखो_access_end();
	वापस csum;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_to_user);
