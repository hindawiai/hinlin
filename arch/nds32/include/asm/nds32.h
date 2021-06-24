<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASM_NDS32_NDS32_H_
#घोषणा _ASM_NDS32_NDS32_H_

#समावेश <यंत्र/bitfield.h>
#समावेश <यंत्र/cachectl.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/init.h>
#समावेश <यंत्र/barrier.h>
#समावेश <nds32_पूर्णांकrinsic.h>

#अगर_घोषित CONFIG_CC_OPTIMIZE_FOR_SIZE
#घोषणा FP_OFFSET (-3)
#अन्यथा
#घोषणा FP_OFFSET (-2)
#पूर्ण_अगर
#घोषणा LP_OFFSET (-1)

बाह्य व्योम __init early_trap_init(व्योम);
अटल अंतरभूत व्योम GIE_ENABLE(व्योम)
अणु
	mb();
	__nds32__gie_en();
पूर्ण

अटल अंतरभूत व्योम GIE_DISABLE(व्योम)
अणु
	mb();
	__nds32__gie_dis();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ CACHE_SET(अचिन्हित अक्षर cache)
अणु

	अगर (cache == ICACHE)
		वापस 64 << ((__nds32__mfsr(NDS32_SR_ICM_CFG) & ICM_CFG_mskISET) >>
			      ICM_CFG_offISET);
	अन्यथा
		वापस 64 << ((__nds32__mfsr(NDS32_SR_DCM_CFG) & DCM_CFG_mskDSET) >>
			      DCM_CFG_offDSET);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ CACHE_WAY(अचिन्हित अक्षर cache)
अणु

	अगर (cache == ICACHE)
		वापस 1 +
		    ((__nds32__mfsr(NDS32_SR_ICM_CFG) & ICM_CFG_mskIWAY) >> ICM_CFG_offIWAY);
	अन्यथा
		वापस 1 +
		    ((__nds32__mfsr(NDS32_SR_DCM_CFG) & DCM_CFG_mskDWAY) >> DCM_CFG_offDWAY);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ CACHE_LINE_SIZE(अचिन्हित अक्षर cache)
अणु

	अगर (cache == ICACHE)
		वापस 8 <<
		    (((__nds32__mfsr(NDS32_SR_ICM_CFG) & ICM_CFG_mskISZ) >> ICM_CFG_offISZ) - 1);
	अन्यथा
		वापस 8 <<
		    (((__nds32__mfsr(NDS32_SR_DCM_CFG) & DCM_CFG_mskDSZ) >> DCM_CFG_offDSZ) - 1);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा IVB_BASE		PHYS_OFFSET	/* in user space क्रम पूर्णांकr/exc/trap/अवरोध table base, 64KB aligned
						 * We defined at the start of the physical memory */

/* dispatched sub-entry exception handler numbering */
#घोषणा RD_PROT			0	/* पढ़ो protrection */
#घोषणा WRT_PROT		1	/* ग_लिखो protection */
#घोषणा NOEXEC			2	/* non executable */
#घोषणा PAGE_MODIFY		3	/* page modअगरied */
#घोषणा ACC_BIT			4	/* access bit */
#घोषणा RESVED_PTE		5	/* reserved PTE attribute */
/* reserved 6 ~ 16 */

#पूर्ण_अगर /* _ASM_NDS32_NDS32_H_ */
