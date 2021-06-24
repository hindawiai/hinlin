<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 */

#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/in6.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_FUNCTION_TRACER
बाह्य व्योम _mcount(व्योम);
EXPORT_SYMBOL(_mcount);
#पूर्ण_अगर

/*
 * Assembly functions that may be used (directly or indirectly) by modules
 */
EXPORT_SYMBOL(__copy_tofrom_user);
EXPORT_SYMBOL(__म_नकलन_user);

#अगर_घोषित CONFIG_OPT_LIB_ASM
EXPORT_SYMBOL(स_नकल);
EXPORT_SYMBOL(स_हटाओ);
#पूर्ण_अगर

EXPORT_SYMBOL(empty_zero_page);

EXPORT_SYMBOL(mbc);

बाह्य व्योम __भागsi3(व्योम);
EXPORT_SYMBOL(__भागsi3);
बाह्य व्योम __modsi3(व्योम);
EXPORT_SYMBOL(__modsi3);
बाह्य व्योम __mulsi3(व्योम);
EXPORT_SYMBOL(__mulsi3);
बाह्य व्योम __uभागsi3(व्योम);
EXPORT_SYMBOL(__uभागsi3);
बाह्य व्योम __umodsi3(व्योम);
EXPORT_SYMBOL(__umodsi3);
