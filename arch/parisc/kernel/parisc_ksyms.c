<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Architecture-specअगरic kernel symbols
 *
 *    Copyright (C) 2000-2001 Riअक्षरd Hirst <rhirst with parisc-linux.org>
 *    Copyright (C) 2001 Dave Kennedy
 *    Copyright (C) 2001 Paul Bame <bame at parisc-linux.org>
 *    Copyright (C) 2001-2003 Grant Grundler <grundler with parisc-linux.org>
 *    Copyright (C) 2002-2003 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2002 Ranकरोlph Chung <tausq at parisc-linux.org>
 *    Copyright (C) 2002-2007 Helge Deller <deller with parisc-linux.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>

#समावेश <linux/माला.स>
EXPORT_SYMBOL(स_रखो);
EXPORT_SYMBOL(म_माप);
EXPORT_SYMBOL(म_नकल);
EXPORT_SYMBOL(म_नकलन);
EXPORT_SYMBOL(म_जोड़ो);

#समावेश <linux/atomic.h>
EXPORT_SYMBOL(__xchg8);
EXPORT_SYMBOL(__xchg32);
EXPORT_SYMBOL(__cmpxchg_u32);
EXPORT_SYMBOL(__cmpxchg_u64);
#अगर_घोषित CONFIG_SMP
EXPORT_SYMBOL(__atomic_hash);
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
EXPORT_SYMBOL(__xchg64);
#पूर्ण_अगर

#समावेश <linux/uaccess.h>
EXPORT_SYMBOL(lclear_user);
EXPORT_SYMBOL(lstrnlen_user);

#अगर_अघोषित CONFIG_64BIT
/* Needed so insmod can set dp value */
बाह्य पूर्णांक $global$;
EXPORT_SYMBOL($global$);
#पूर्ण_अगर

#समावेश <यंत्र/पन.स>
EXPORT_SYMBOL(स_नकल_toio);
EXPORT_SYMBOL(स_नकल_fromio);
EXPORT_SYMBOL(स_रखो_io);

बाह्य व्योम $$भागI(व्योम);
बाह्य व्योम $$भागU(व्योम);
बाह्य व्योम $$remI(व्योम);
बाह्य व्योम $$remU(व्योम);
बाह्य व्योम $$mulI(व्योम);
बाह्य व्योम $$भागU_3(व्योम);
बाह्य व्योम $$भागU_5(व्योम);
बाह्य व्योम $$भागU_6(व्योम);
बाह्य व्योम $$भागU_9(व्योम);
बाह्य व्योम $$भागU_10(व्योम);
बाह्य व्योम $$भागU_12(व्योम);
बाह्य व्योम $$भागU_7(व्योम);
बाह्य व्योम $$भागU_14(व्योम);
बाह्य व्योम $$भागU_15(व्योम);
बाह्य व्योम $$भागI_3(व्योम);
बाह्य व्योम $$भागI_5(व्योम);
बाह्य व्योम $$भागI_6(व्योम);
बाह्य व्योम $$भागI_7(व्योम);
बाह्य व्योम $$भागI_9(व्योम);
बाह्य व्योम $$भागI_10(व्योम);
बाह्य व्योम $$भागI_12(व्योम);
बाह्य व्योम $$भागI_14(व्योम);
बाह्य व्योम $$भागI_15(व्योम);

EXPORT_SYMBOL($$भागI);
EXPORT_SYMBOL($$भागU);
EXPORT_SYMBOL($$remI);
EXPORT_SYMBOL($$remU);
EXPORT_SYMBOL($$mulI);
EXPORT_SYMBOL($$भागU_3);
EXPORT_SYMBOL($$भागU_5);
EXPORT_SYMBOL($$भागU_6);
EXPORT_SYMBOL($$भागU_9);
EXPORT_SYMBOL($$भागU_10);
EXPORT_SYMBOL($$भागU_12);
EXPORT_SYMBOL($$भागU_7);
EXPORT_SYMBOL($$भागU_14);
EXPORT_SYMBOL($$भागU_15);
EXPORT_SYMBOL($$भागI_3);
EXPORT_SYMBOL($$भागI_5);
EXPORT_SYMBOL($$भागI_6);
EXPORT_SYMBOL($$भागI_7);
EXPORT_SYMBOL($$भागI_9);
EXPORT_SYMBOL($$भागI_10);
EXPORT_SYMBOL($$भागI_12);
EXPORT_SYMBOL($$भागI_14);
EXPORT_SYMBOL($$भागI_15);

बाह्य व्योम __ashrdi3(व्योम);
बाह्य व्योम __ashldi3(व्योम);
बाह्य व्योम __lshrdi3(व्योम);
बाह्य व्योम __muldi3(व्योम);
बाह्य व्योम __ucmpdi2(व्योम);

EXPORT_SYMBOL(__ashrdi3);
EXPORT_SYMBOL(__ashldi3);
EXPORT_SYMBOL(__lshrdi3);
EXPORT_SYMBOL(__muldi3);
EXPORT_SYMBOL(__ucmpdi2);

यंत्रlinkage व्योम * __canonicalize_funcptr_क्रम_compare(व्योम *);
EXPORT_SYMBOL(__canonicalize_funcptr_क्रम_compare);

#अगर_घोषित CONFIG_64BIT
बाह्य व्योम __भागdi3(व्योम);
बाह्य व्योम __uभागdi3(व्योम);
बाह्य व्योम __umoddi3(व्योम);
बाह्य व्योम __moddi3(व्योम);

EXPORT_SYMBOL(__भागdi3);
EXPORT_SYMBOL(__uभागdi3);
EXPORT_SYMBOL(__umoddi3);
EXPORT_SYMBOL(__moddi3);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_64BIT
बाह्य व्योम $$dyncall(व्योम);
EXPORT_SYMBOL($$dyncall);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_TRACER
बाह्य व्योम _mcount(व्योम);
EXPORT_SYMBOL(_mcount);
#पूर्ण_अगर

/* from pacache.S -- needed क्रम clear/copy_page */
EXPORT_SYMBOL(clear_page_यंत्र);
EXPORT_SYMBOL(copy_page_यंत्र);
