<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC64_KDUMP_H
#घोषणा _PPC64_KDUMP_H

#समावेश <यंत्र/page.h>

#घोषणा KDUMP_KERNELBASE	0x2000000

/* How many bytes to reserve at zero क्रम kdump. The reserve limit should
 * be greater or equal to the trampoline's end address.
 * Reserve to the end of the FWNMI area, see head_64.S */
#घोषणा KDUMP_RESERVE_LIMIT	0x10000 /* 64K */

#अगर_घोषित CONFIG_CRASH_DUMP

/*
 * On PPC64 translation is disabled during trampoline setup, so we use
 * physical addresses. Though on PPC32 translation is alपढ़ोy enabled,
 * so we can't करो the same. Luckily create_trampoline() creates relative
 * branches, so we can just add the PAGE_OFFSET and करोn't worry about it.
 */
#अगर_घोषित __घातerpc64__
#घोषणा KDUMP_TRAMPOLINE_START	0x0100
#घोषणा KDUMP_TRAMPOLINE_END	0x3000
#अन्यथा
#घोषणा KDUMP_TRAMPOLINE_START	(0x0100 + PAGE_OFFSET)
#घोषणा KDUMP_TRAMPOLINE_END	(0x3000 + PAGE_OFFSET)
#पूर्ण_अगर /* __घातerpc64__ */

#घोषणा KDUMP_MIN_TCE_ENTRIES	2048

#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_CRASH_DUMP) && !defined(CONFIG_NONSTATIC_KERNEL)
बाह्य व्योम reserve_kdump_trampoline(व्योम);
बाह्य व्योम setup_kdump_trampoline(व्योम);
#अन्यथा
/* !CRASH_DUMP || !NONSTATIC_KERNEL */
अटल अंतरभूत व्योम reserve_kdump_trampoline(व्योम) अणु ; पूर्ण
अटल अंतरभूत व्योम setup_kdump_trampoline(व्योम) अणु ; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __PPC64_KDUMP_H */
