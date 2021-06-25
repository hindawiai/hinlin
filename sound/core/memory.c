<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 * 
 *  Misc memory accessors
 */

#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <sound/core.h>

/**
 * copy_to_user_fromio - copy data from mmio-space to user-space
 * @dst: the destination poपूर्णांकer on user-space
 * @src: the source poपूर्णांकer on mmio
 * @count: the data size to copy in bytes
 *
 * Copies the data from mmio-space to user-space.
 *
 * Return: Zero अगर successful, or non-zero on failure.
 */
पूर्णांक copy_to_user_fromio(व्योम __user *dst, स्थिर अस्थिर व्योम __iomem *src, माप_प्रकार count)
अणु
#अगर defined(__i386__) || defined(CONFIG_SPARC32)
	वापस copy_to_user(dst, (स्थिर व्योम __क्रमce*)src, count) ? -EFAULT : 0;
#अन्यथा
	अक्षर buf[256];
	जबतक (count) अणु
		माप_प्रकार c = count;
		अगर (c > माप(buf))
			c = माप(buf);
		स_नकल_fromio(buf, (व्योम __iomem *)src, c);
		अगर (copy_to_user(dst, buf, c))
			वापस -EFAULT;
		count -= c;
		dst += c;
		src += c;
	पूर्ण
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(copy_to_user_fromio);

/**
 * copy_from_user_toio - copy data from user-space to mmio-space
 * @dst: the destination poपूर्णांकer on mmio-space
 * @src: the source poपूर्णांकer on user-space
 * @count: the data size to copy in bytes
 *
 * Copies the data from user-space to mmio-space.
 *
 * Return: Zero अगर successful, or non-zero on failure.
 */
पूर्णांक copy_from_user_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम __user *src, माप_प्रकार count)
अणु
#अगर defined(__i386__) || defined(CONFIG_SPARC32)
	वापस copy_from_user((व्योम __क्रमce *)dst, src, count) ? -EFAULT : 0;
#अन्यथा
	अक्षर buf[256];
	जबतक (count) अणु
		माप_प्रकार c = count;
		अगर (c > माप(buf))
			c = माप(buf);
		अगर (copy_from_user(buf, src, c))
			वापस -EFAULT;
		स_नकल_toio(dst, buf, c);
		count -= c;
		dst += c;
		src += c;
	पूर्ण
	वापस 0;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(copy_from_user_toio);
