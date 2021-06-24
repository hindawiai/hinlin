<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_MMU_H
#घोषणा _ASM_ARC_MMU_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/thपढ़ोs.h>	/* NR_CPUS */
#पूर्ण_अगर

#अगर defined(CONFIG_ARC_MMU_V1)
#घोषणा CONFIG_ARC_MMU_VER 1
#या_अगर defined(CONFIG_ARC_MMU_V2)
#घोषणा CONFIG_ARC_MMU_VER 2
#या_अगर defined(CONFIG_ARC_MMU_V3)
#घोषणा CONFIG_ARC_MMU_VER 3
#या_अगर defined(CONFIG_ARC_MMU_V4)
#घोषणा CONFIG_ARC_MMU_VER 4
#पूर्ण_अगर

/* MMU Management regs */
#घोषणा ARC_REG_MMU_BCR		0x06f
#अगर (CONFIG_ARC_MMU_VER < 4)
#घोषणा ARC_REG_TLBPD0		0x405
#घोषणा ARC_REG_TLBPD1		0x406
#घोषणा ARC_REG_TLBPD1HI	0	/* Dummy: allows code sharing with ARC700 */
#घोषणा ARC_REG_TLBINDEX	0x407
#घोषणा ARC_REG_TLBCOMMAND	0x408
#घोषणा ARC_REG_PID		0x409
#घोषणा ARC_REG_SCRATCH_DATA0	0x418
#अन्यथा
#घोषणा ARC_REG_TLBPD0		0x460
#घोषणा ARC_REG_TLBPD1		0x461
#घोषणा ARC_REG_TLBPD1HI	0x463
#घोषणा ARC_REG_TLBINDEX	0x464
#घोषणा ARC_REG_TLBCOMMAND	0x465
#घोषणा ARC_REG_PID		0x468
#घोषणा ARC_REG_SCRATCH_DATA0	0x46c
#पूर्ण_अगर

#अगर defined(CONFIG_ISA_ARCV2) || !defined(CONFIG_SMP)
#घोषणा	ARC_USE_SCRATCH_REG
#पूर्ण_अगर

/* Bits in MMU PID रेजिस्टर */
#घोषणा __TLB_ENABLE		(1 << 31)
#घोषणा __PROG_ENABLE		(1 << 30)
#घोषणा MMU_ENABLE		(__TLB_ENABLE | __PROG_ENABLE)

/* Error code अगर probe fails */
#घोषणा TLB_LKUP_ERR		0x80000000

#अगर (CONFIG_ARC_MMU_VER < 4)
#घोषणा TLB_DUP_ERR	(TLB_LKUP_ERR | 0x00000001)
#अन्यथा
#घोषणा TLB_DUP_ERR	(TLB_LKUP_ERR | 0x40000000)
#पूर्ण_अगर

/* TLB Commands */
#घोषणा TLBWrite    0x1
#घोषणा TLBRead     0x2
#घोषणा TLBGetIndex 0x3
#घोषणा TLBProbe    0x4

#अगर (CONFIG_ARC_MMU_VER >= 2)
#घोषणा TLBWriteNI  0x5		/* ग_लिखो JTLB without inv uTLBs */
#घोषणा TLBIVUTLB   0x6		/* explicitly inv uTLBs */
#अन्यथा
#घोषणा TLBWriteNI  TLBWrite	/* Not present in hardware, fallback */
#पूर्ण_अगर

#अगर (CONFIG_ARC_MMU_VER >= 4)
#घोषणा TLBInsertEntry	0x7
#घोषणा TLBDeleteEntry	0x8
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ asid[NR_CPUS];	/* 8 bit MMU PID + Generation cycle */
पूर्ण mm_context_t;

#अगर_घोषित CONFIG_ARC_DBG_TLB_PARANOIA
व्योम tlb_paranoid_check(अचिन्हित पूर्णांक mm_asid, अचिन्हित दीर्घ address);
#अन्यथा
#घोषणा tlb_paranoid_check(a, b)
#पूर्ण_अगर

व्योम arc_mmu_init(व्योम);
बाह्य अक्षर *arc_mmu_mumbojumbo(पूर्णांक cpu_id, अक्षर *buf, पूर्णांक len);
व्योम पढ़ो_decode_mmu_bcr(व्योम);

अटल अंतरभूत पूर्णांक is_pae40_enabled(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARC_HAS_PAE40);
पूर्ण

बाह्य पूर्णांक pae40_exist_but_not_enab(व्योम);

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर
