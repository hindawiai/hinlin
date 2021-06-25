<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 ARM Ltd.
 */
#अगर_अघोषित __ASM_PGTABLE_PROT_H
#घोषणा __ASM_PGTABLE_PROT_H

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/pgtable-hwdef.h>

#समावेश <linux/स्थिर.h>

/*
 * Software defined PTE bits definition.
 */
#घोषणा PTE_WRITE		(PTE_DBM)		 /* same as DBM (51) */
#घोषणा PTE_सूचीTY		(_AT(pteval_t, 1) << 55)
#घोषणा PTE_SPECIAL		(_AT(pteval_t, 1) << 56)
#घोषणा PTE_DEVMAP		(_AT(pteval_t, 1) << 57)
#घोषणा PTE_PROT_NONE		(_AT(pteval_t, 1) << 58) /* only when !PTE_VALID */

/*
 * This bit indicates that the entry is present i.e. pmd_page()
 * still poपूर्णांकs to a valid huge page in memory even अगर the pmd
 * has been invalidated.
 */
#घोषणा PMD_PRESENT_INVALID	(_AT(pteval_t, 1) << 59) /* only when !PMD_SECT_VALID */

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/pgtable-types.h>

बाह्य bool arm64_use_ng_mappings;

#घोषणा _PROT_DEFAULT		(PTE_TYPE_PAGE | PTE_AF | PTE_SHARED)
#घोषणा _PROT_SECT_DEFAULT	(PMD_TYPE_SECT | PMD_SECT_AF | PMD_SECT_S)

#घोषणा PTE_MAYBE_NG		(arm64_use_ng_mappings ? PTE_NG : 0)
#घोषणा PMD_MAYBE_NG		(arm64_use_ng_mappings ? PMD_SECT_NG : 0)

/*
 * If we have userspace only BTI we करोn't want to mark kernel pages
 * guarded even अगर the प्रणाली करोes support BTI.
 */
#अगर_घोषित CONFIG_ARM64_BTI_KERNEL
#घोषणा PTE_MAYBE_GP		(प्रणाली_supports_bti() ? PTE_GP : 0)
#अन्यथा
#घोषणा PTE_MAYBE_GP		0
#पूर्ण_अगर

#घोषणा PROT_DEFAULT		(_PROT_DEFAULT | PTE_MAYBE_NG)
#घोषणा PROT_SECT_DEFAULT	(_PROT_SECT_DEFAULT | PMD_MAYBE_NG)

#घोषणा PROT_DEVICE_nGnRnE	(PROT_DEFAULT | PTE_PXN | PTE_UXN | PTE_WRITE | PTE_ATTRINDX(MT_DEVICE_nGnRnE))
#घोषणा PROT_DEVICE_nGnRE	(PROT_DEFAULT | PTE_PXN | PTE_UXN | PTE_WRITE | PTE_ATTRINDX(MT_DEVICE_nGnRE))
#घोषणा PROT_NORMAL_NC		(PROT_DEFAULT | PTE_PXN | PTE_UXN | PTE_WRITE | PTE_ATTRINDX(MT_NORMAL_NC))
#घोषणा PROT_NORMAL_WT		(PROT_DEFAULT | PTE_PXN | PTE_UXN | PTE_WRITE | PTE_ATTRINDX(MT_NORMAL_WT))
#घोषणा PROT_NORMAL		(PROT_DEFAULT | PTE_PXN | PTE_UXN | PTE_WRITE | PTE_ATTRINDX(MT_NORMAL))
#घोषणा PROT_NORMAL_TAGGED	(PROT_DEFAULT | PTE_PXN | PTE_UXN | PTE_WRITE | PTE_ATTRINDX(MT_NORMAL_TAGGED))

#घोषणा PROT_SECT_DEVICE_nGnRE	(PROT_SECT_DEFAULT | PMD_SECT_PXN | PMD_SECT_UXN | PMD_ATTRINDX(MT_DEVICE_nGnRE))
#घोषणा PROT_SECT_NORMAL	(PROT_SECT_DEFAULT | PMD_SECT_PXN | PMD_SECT_UXN | PMD_ATTRINDX(MT_NORMAL))
#घोषणा PROT_SECT_NORMAL_EXEC	(PROT_SECT_DEFAULT | PMD_SECT_UXN | PMD_ATTRINDX(MT_NORMAL))

#घोषणा _PAGE_DEFAULT		(_PROT_DEFAULT | PTE_ATTRINDX(MT_NORMAL))

#घोषणा PAGE_KERNEL		__pgprot(PROT_NORMAL)
#घोषणा PAGE_KERNEL_RO		__pgprot((PROT_NORMAL & ~PTE_WRITE) | PTE_RDONLY)
#घोषणा PAGE_KERNEL_ROX		__pgprot((PROT_NORMAL & ~(PTE_WRITE | PTE_PXN)) | PTE_RDONLY)
#घोषणा PAGE_KERNEL_EXEC	__pgprot(PROT_NORMAL & ~PTE_PXN)
#घोषणा PAGE_KERNEL_EXEC_CONT	__pgprot((PROT_NORMAL & ~PTE_PXN) | PTE_CONT)

#घोषणा PAGE_S2_MEMATTR(attr, has_fwb)					\
	(अणु								\
		u64 __val;						\
		अगर (has_fwb)						\
			__val = PTE_S2_MEMATTR(MT_S2_FWB_ ## attr);	\
		अन्यथा							\
			__val = PTE_S2_MEMATTR(MT_S2_ ## attr);		\
		__val;							\
	 पूर्ण)

#घोषणा PAGE_NONE		__pgprot(((_PAGE_DEFAULT) & ~PTE_VALID) | PTE_PROT_NONE | PTE_RDONLY | PTE_NG | PTE_PXN | PTE_UXN)
/* shared+writable pages are clean by शेष, hence PTE_RDONLY|PTE_WRITE */
#घोषणा PAGE_SHARED		__pgprot(_PAGE_DEFAULT | PTE_USER | PTE_RDONLY | PTE_NG | PTE_PXN | PTE_UXN | PTE_WRITE)
#घोषणा PAGE_SHARED_EXEC	__pgprot(_PAGE_DEFAULT | PTE_USER | PTE_RDONLY | PTE_NG | PTE_PXN | PTE_WRITE)
#घोषणा PAGE_READONLY		__pgprot(_PAGE_DEFAULT | PTE_USER | PTE_RDONLY | PTE_NG | PTE_PXN | PTE_UXN)
#घोषणा PAGE_READONLY_EXEC	__pgprot(_PAGE_DEFAULT | PTE_USER | PTE_RDONLY | PTE_NG | PTE_PXN)
#घोषणा PAGE_EXECONLY		__pgprot(_PAGE_DEFAULT | PTE_RDONLY | PTE_NG | PTE_PXN)

#घोषणा __P000  PAGE_NONE
#घोषणा __P001  PAGE_READONLY
#घोषणा __P010  PAGE_READONLY
#घोषणा __P011  PAGE_READONLY
#घोषणा __P100  PAGE_EXECONLY
#घोषणा __P101  PAGE_READONLY_EXEC
#घोषणा __P110  PAGE_READONLY_EXEC
#घोषणा __P111  PAGE_READONLY_EXEC

#घोषणा __S000  PAGE_NONE
#घोषणा __S001  PAGE_READONLY
#घोषणा __S010  PAGE_SHARED
#घोषणा __S011  PAGE_SHARED
#घोषणा __S100  PAGE_EXECONLY
#घोषणा __S101  PAGE_READONLY_EXEC
#घोषणा __S110  PAGE_SHARED_EXEC
#घोषणा __S111  PAGE_SHARED_EXEC

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_PGTABLE_PROT_H */
