<शैली गुरु>
/*
 * arch/xtensa/kernel/xtensa_ksyms.c
 *
 * Export Xtensa-specअगरic functions क्रम loadable modules.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005  Tensilica Inc.
 *
 * Joe Taylor <joe@tensilica.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/in6.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ftrace.h>
#अगर_घोषित CONFIG_BLK_DEV_FD
#समावेश <यंत्र/floppy.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET
#समावेश <net/checksum.h>
#पूर्ण_अगर /* CONFIG_NET */


/*
 * String functions
 */
EXPORT_SYMBOL(स_रखो);
EXPORT_SYMBOL(स_नकल);
EXPORT_SYMBOL(स_हटाओ);
EXPORT_SYMBOL(__स_रखो);
EXPORT_SYMBOL(__स_नकल);
EXPORT_SYMBOL(__स_हटाओ);
#अगर_अघोषित CONFIG_GENERIC_STRNCPY_FROM_USER
EXPORT_SYMBOL(__म_नकलन_user);
#पूर्ण_अगर
EXPORT_SYMBOL(clear_page);
EXPORT_SYMBOL(copy_page);

EXPORT_SYMBOL(empty_zero_page);

/*
 * gcc पूर्णांकernal math functions
 */
बाह्य दीर्घ दीर्घ __ashrdi3(दीर्घ दीर्घ, पूर्णांक);
बाह्य दीर्घ दीर्घ __ashldi3(दीर्घ दीर्घ, पूर्णांक);
बाह्य दीर्घ दीर्घ __lshrdi3(दीर्घ दीर्घ, पूर्णांक);
बाह्य पूर्णांक __भागsi3(पूर्णांक, पूर्णांक);
बाह्य पूर्णांक __modsi3(पूर्णांक, पूर्णांक);
बाह्य दीर्घ दीर्घ __muldi3(दीर्घ दीर्घ, दीर्घ दीर्घ);
बाह्य पूर्णांक __mulsi3(पूर्णांक, पूर्णांक);
बाह्य अचिन्हित पूर्णांक __uभागsi3(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
बाह्य अचिन्हित पूर्णांक __umodsi3(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
बाह्य अचिन्हित दीर्घ दीर्घ __umoddi3(अचिन्हित दीर्घ दीर्घ, अचिन्हित दीर्घ दीर्घ);
बाह्य अचिन्हित दीर्घ दीर्घ __uभागdi3(अचिन्हित दीर्घ दीर्घ, अचिन्हित दीर्घ दीर्घ);
बाह्य पूर्णांक __ucmpdi2(पूर्णांक, पूर्णांक);

EXPORT_SYMBOL(__ashldi3);
EXPORT_SYMBOL(__ashrdi3);
EXPORT_SYMBOL(__lshrdi3);
EXPORT_SYMBOL(__भागsi3);
EXPORT_SYMBOL(__modsi3);
EXPORT_SYMBOL(__muldi3);
EXPORT_SYMBOL(__mulsi3);
EXPORT_SYMBOL(__uभागsi3);
EXPORT_SYMBOL(__umodsi3);
EXPORT_SYMBOL(__uभागdi3);
EXPORT_SYMBOL(__umoddi3);
EXPORT_SYMBOL(__ucmpdi2);

व्योम __xtensa_libgcc_winकरोw_spill(व्योम)
अणु
	BUG();
पूर्ण
EXPORT_SYMBOL(__xtensa_libgcc_winकरोw_spill);

अचिन्हित पूर्णांक __sync_fetch_and_and_4(अस्थिर व्योम *p, अचिन्हित पूर्णांक v)
अणु
	BUG();
पूर्ण
EXPORT_SYMBOL(__sync_fetch_and_and_4);

अचिन्हित पूर्णांक __sync_fetch_and_or_4(अस्थिर व्योम *p, अचिन्हित पूर्णांक v)
अणु
	BUG();
पूर्ण
EXPORT_SYMBOL(__sync_fetch_and_or_4);

/*
 * Networking support
 */
EXPORT_SYMBOL(csum_partial);
EXPORT_SYMBOL(csum_partial_copy_generic);

/*
 * Architecture-specअगरic symbols
 */
EXPORT_SYMBOL(__xtensa_copy_user);
EXPORT_SYMBOL(__invalidate_icache_range);

/*
 * Kernel hacking ...
 */

#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE)
// FIXME EXPORT_SYMBOL(screen_info);
#पूर्ण_अगर

बाह्य दीर्घ common_exception_वापस;
EXPORT_SYMBOL(common_exception_वापस);

#अगर_घोषित CONFIG_FUNCTION_TRACER
EXPORT_SYMBOL(_mcount);
#पूर्ण_अगर

EXPORT_SYMBOL(__invalidate_dcache_range);
#अगर XCHAL_DCACHE_IS_WRITEBACK
EXPORT_SYMBOL(__flush_dcache_range);
#पूर्ण_अगर
