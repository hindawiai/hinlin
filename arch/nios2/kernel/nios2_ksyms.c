<शैली गुरु>
/*
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>

/* string functions */

EXPORT_SYMBOL(स_नकल);
EXPORT_SYMBOL(स_रखो);
EXPORT_SYMBOL(स_हटाओ);

/* memory management */

EXPORT_SYMBOL(empty_zero_page);
EXPORT_SYMBOL(flush_icache_range);

/*
 * libgcc functions - functions that are used पूर्णांकernally by the
 * compiler...  (prototypes are not correct though, but that
 * करोesn't really matter since they're not versioned).
 */
#घोषणा DECLARE_EXPORT(name)	बाह्य व्योम name(व्योम); EXPORT_SYMBOL(name)

DECLARE_EXPORT(__gcc_bcmp);
DECLARE_EXPORT(__भागsi3);
DECLARE_EXPORT(__moddi3);
DECLARE_EXPORT(__modsi3);
DECLARE_EXPORT(__uभागmoddi4);
DECLARE_EXPORT(__uभागsi3);
DECLARE_EXPORT(__umoddi3);
DECLARE_EXPORT(__umodsi3);
DECLARE_EXPORT(__muldi3);
DECLARE_EXPORT(__ucmpdi2);
DECLARE_EXPORT(__lshrdi3);
DECLARE_EXPORT(__ashldi3);
DECLARE_EXPORT(__ashrdi3);
