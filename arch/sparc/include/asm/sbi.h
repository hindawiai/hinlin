<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sbi.h:  SBI (Sbus Interface on sun4d) definitions
 *
 * Copyright (C) 1997 Jakub Jelinek <jj@sunsite.mff.cuni.cz>
 */

#अगर_अघोषित _SPARC_SBI_H
#घोषणा _SPARC_SBI_H

#समावेश <यंत्र/obपन.स>

/* SBI */
काष्ठा sbi_regs अणु
/* 0x0000 */	u32		cid;		/* Component ID */
/* 0x0004 */	u32		ctl;		/* Control */
/* 0x0008 */	u32		status;		/* Status */
		u32		_unused1;
		
/* 0x0010 */	u32		cfg0;		/* Slot0 config reg */
/* 0x0014 */	u32		cfg1;		/* Slot1 config reg */
/* 0x0018 */	u32		cfg2;		/* Slot2 config reg */
/* 0x001c */	u32		cfg3;		/* Slot3 config reg */

/* 0x0020 */	u32		stb0;		/* Streaming buf control क्रम slot 0 */
/* 0x0024 */	u32		stb1;		/* Streaming buf control क्रम slot 1 */
/* 0x0028 */	u32		stb2;		/* Streaming buf control क्रम slot 2 */
/* 0x002c */	u32		stb3;		/* Streaming buf control क्रम slot 3 */

/* 0x0030 */	u32		पूर्णांकr_state;	/* Interrupt state */
/* 0x0034 */	u32		पूर्णांकr_tid;	/* Interrupt target ID */
/* 0x0038 */	u32		पूर्णांकr_diag;	/* Interrupt diagnostics */
पूर्ण;

#घोषणा SBI_CID			0x02800000
#घोषणा SBI_CTL			0x02800004
#घोषणा SBI_STATUS		0x02800008
#घोषणा SBI_CFG0		0x02800010
#घोषणा SBI_CFG1		0x02800014
#घोषणा SBI_CFG2		0x02800018
#घोषणा SBI_CFG3		0x0280001c
#घोषणा SBI_STB0		0x02800020
#घोषणा SBI_STB1		0x02800024
#घोषणा SBI_STB2		0x02800028
#घोषणा SBI_STB3		0x0280002c
#घोषणा SBI_INTR_STATE		0x02800030
#घोषणा SBI_INTR_TID		0x02800034
#घोषणा SBI_INTR_DIAG		0x02800038

/* Burst bits क्रम 8, 16, 32, 64 are in cfgX रेजिस्टरs at bits 2, 3, 4, 5 respectively */
#घोषणा SBI_CFG_BURST_MASK	0x0000001e

/* How to make devid from sbi no */
#घोषणा SBI2DEVID(sbino) ((sbino<<4)|2)

/* पूर्णांकr_state has 4 bits क्रम slots 0 .. 3 and these bits are repeated क्रम each sbus irq level
 *
 *		   +-------+-------+-------+-------+-------+-------+-------+-------+
 *  SBUS IRQ LEVEL |   7   |   6   |   5   |   4   |   3   |   2   |   1   |       |
 *		   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ Reser |
 *  SLOT #         |3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|3|2|1|0|  ved  |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-------+
 *  Bits           31      27      23      19      15      11      7       3      0
 */


#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत पूर्णांक acquire_sbi(पूर्णांक devid, पूर्णांक mask)
अणु
	__यंत्र__ __अस्थिर__ ("swapa [%2] %3, %0" :
			      "=r" (mask) :
			      "0" (mask),
			      "r" (ECSR_DEV_BASE(devid) | SBI_INTR_STATE),
			      "i" (ASI_M_CTL));
	वापस mask;
पूर्ण

अटल अंतरभूत व्योम release_sbi(पूर्णांक devid, पूर्णांक mask)
अणु
	__यंत्र__ __अस्थिर__ ("sta %0, [%1] %2" : :
			      "r" (mask),
			      "r" (ECSR_DEV_BASE(devid) | SBI_INTR_STATE),
			      "i" (ASI_M_CTL));
पूर्ण

अटल अंतरभूत व्योम set_sbi_tid(पूर्णांक devid, पूर्णांक targetid)
अणु
	__यंत्र__ __अस्थिर__ ("sta %0, [%1] %2" : :
			      "r" (targetid),
			      "r" (ECSR_DEV_BASE(devid) | SBI_INTR_TID),
			      "i" (ASI_M_CTL));
पूर्ण

अटल अंतरभूत पूर्णांक get_sbi_ctl(पूर्णांक devid, पूर्णांक cfgno)
अणु
	पूर्णांक cfg;
	
	__यंत्र__ __अस्थिर__ ("lda [%1] %2, %0" :
			      "=r" (cfg) :
			      "r" ((ECSR_DEV_BASE(devid) | SBI_CFG0) + (cfgno<<2)),
			      "i" (ASI_M_CTL));
	वापस cfg;
पूर्ण

अटल अंतरभूत व्योम set_sbi_ctl(पूर्णांक devid, पूर्णांक cfgno, पूर्णांक cfg)
अणु
	__यंत्र__ __अस्थिर__ ("sta %0, [%1] %2" : :
			      "r" (cfg),
			      "r" ((ECSR_DEV_BASE(devid) | SBI_CFG0) + (cfgno<<2)),
			      "i" (ASI_M_CTL));
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* !(_SPARC_SBI_H) */
