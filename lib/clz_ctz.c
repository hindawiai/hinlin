<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib/clz_ctz.c
 *
 * Copyright (C) 2013 Chanho Min <chanho.min@lge.com>
 *
 * The functions in this file aren't called directly, but are required by
 * GCC builtins such as __builtin_ctz, and thereक्रमe they can't be हटाओd
 * despite appearing unreferenced in kernel source.
 *
 * __c[lt]z[sd]i2 can be overridden by linking arch-specअगरic versions.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>

पूर्णांक __weak __ctzsi2(पूर्णांक val);
पूर्णांक __weak __ctzsi2(पूर्णांक val)
अणु
	वापस __ffs(val);
पूर्ण
EXPORT_SYMBOL(__ctzsi2);

पूर्णांक __weak __clzsi2(पूर्णांक val);
पूर्णांक __weak __clzsi2(पूर्णांक val)
अणु
	वापस 32 - fls(val);
पूर्ण
EXPORT_SYMBOL(__clzsi2);

पूर्णांक __weak __clzdi2(दीर्घ val);
पूर्णांक __weak __ctzdi2(दीर्घ val);
#अगर BITS_PER_LONG == 32

पूर्णांक __weak __clzdi2(दीर्घ val)
अणु
	वापस 32 - fls((पूर्णांक)val);
पूर्ण
EXPORT_SYMBOL(__clzdi2);

पूर्णांक __weak __ctzdi2(दीर्घ val)
अणु
	वापस __ffs((u32)val);
पूर्ण
EXPORT_SYMBOL(__ctzdi2);

#या_अगर BITS_PER_LONG == 64

पूर्णांक __weak __clzdi2(दीर्घ val)
अणु
	वापस 64 - fls64((u64)val);
पूर्ण
EXPORT_SYMBOL(__clzdi2);

पूर्णांक __weak __ctzdi2(दीर्घ val)
अणु
	वापस __ffs64((u64)val);
पूर्ण
EXPORT_SYMBOL(__ctzdi2);

#अन्यथा
#त्रुटि BITS_PER_LONG not 32 or 64
#पूर्ण_अगर
