<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016,2017 IBM Corporation.
 */
#अगर_अघोषित _ASM_POWERPC_XIVE_REGS_H
#घोषणा _ASM_POWERPC_XIVE_REGS_H

/*
 * "magic" Event State Buffer (ESB) MMIO offsets.
 *
 * Each पूर्णांकerrupt source has a 2-bit state machine called ESB
 * which can be controlled by MMIO. It's made of 2 bits, P and
 * Q. P indicates that an पूर्णांकerrupt is pending (has been sent
 * to a queue and is रुकोing क्रम an EOI). Q indicates that the
 * पूर्णांकerrupt has been triggered जबतक pending.
 *
 * This acts as a coalescing mechanism in order to guarantee
 * that a given पूर्णांकerrupt only occurs at most once in a queue.
 *
 * When करोing an EOI, the Q bit will indicate अगर the पूर्णांकerrupt
 * needs to be re-triggered.
 *
 * The following offsets पूर्णांकo the ESB MMIO allow to पढ़ो or
 * manipulate the PQ bits. They must be used with an 8-bytes
 * load inकाष्ठाion. They all वापस the previous state of the
 * पूर्णांकerrupt (atomically).
 *
 * Additionally, some ESB pages support करोing an EOI via a
 * store at 0 and some ESBs support करोing a trigger via a
 * separate trigger page.
 */
#घोषणा XIVE_ESB_STORE_EOI	0x400 /* Store */
#घोषणा XIVE_ESB_LOAD_EOI	0x000 /* Load */
#घोषणा XIVE_ESB_GET		0x800 /* Load */
#घोषणा XIVE_ESB_SET_PQ_00	0xc00 /* Load */
#घोषणा XIVE_ESB_SET_PQ_01	0xd00 /* Load */
#घोषणा XIVE_ESB_SET_PQ_10	0xe00 /* Load */
#घोषणा XIVE_ESB_SET_PQ_11	0xf00 /* Load */

/*
 * Load-after-store ordering
 *
 * Adding this offset to the load address will enक्रमce
 * load-after-store ordering. This is required to use StoreEOI.
 */
#घोषणा XIVE_ESB_LD_ST_MO	0x40 /* Load-after-store ordering */

#घोषणा XIVE_ESB_VAL_P		0x2
#घोषणा XIVE_ESB_VAL_Q		0x1
#घोषणा XIVE_ESB_INVALID	0xFF

/*
 * Thपढ़ो Management (aka "TM") रेजिस्टरs
 */

/* TM रेजिस्टर offsets */
#घोषणा TM_QW0_USER		0x000 /* All rings */
#घोषणा TM_QW1_OS		0x010 /* Ring 0..2 */
#घोषणा TM_QW2_HV_POOL		0x020 /* Ring 0..1 */
#घोषणा TM_QW3_HV_PHYS		0x030 /* Ring 0..1 */

/* Byte offsets inside a QW             QW0 QW1 QW2 QW3 */
#घोषणा TM_NSR			0x0  /*  +   +   -   +  */
#घोषणा TM_CPPR			0x1  /*  -   +   -   +  */
#घोषणा TM_IPB			0x2  /*  -   +   +   +  */
#घोषणा TM_LSMFB		0x3  /*  -   +   +   +  */
#घोषणा TM_ACK_CNT		0x4  /*  -   +   -   -  */
#घोषणा TM_INC			0x5  /*  -   +   -   +  */
#घोषणा TM_AGE			0x6  /*  -   +   -   +  */
#घोषणा TM_PIPR			0x7  /*  -   +   -   +  */

#घोषणा TM_WORD0		0x0
#घोषणा TM_WORD1		0x4

/*
 * QW word 2 contains the valid bit at the top and other fields
 * depending on the QW.
 */
#घोषणा TM_WORD2		0x8
#घोषणा   TM_QW0W2_VU		PPC_BIT32(0)
#घोषणा   TM_QW0W2_LOGIC_SERV	PPC_BITMASK32(1,31) // XX 2,31 ?
#घोषणा   TM_QW1W2_VO		PPC_BIT32(0)
#घोषणा   TM_QW1W2_OS_CAM	PPC_BITMASK32(8,31)
#घोषणा   TM_QW2W2_VP		PPC_BIT32(0)
#घोषणा   TM_QW2W2_POOL_CAM	PPC_BITMASK32(8,31)
#घोषणा   TM_QW3W2_VT		PPC_BIT32(0)
#घोषणा   TM_QW3W2_LP		PPC_BIT32(6)
#घोषणा   TM_QW3W2_LE		PPC_BIT32(7)
#घोषणा   TM_QW3W2_T		PPC_BIT32(31)

/*
 * In addition to normal loads to "peek" and ग_लिखोs (only when invalid)
 * using 4 and 8 bytes accesses, the above रेजिस्टरs support these
 * "special" byte operations:
 *
 *   - Byte load from QW0[NSR] - User level NSR (EBB)
 *   - Byte store to QW0[NSR] - User level NSR (EBB)
 *   - Byte load/store to QW1[CPPR] and QW3[CPPR] - CPPR access
 *   - Byte load from QW3[TM_WORD2] - Read VT||00000||LP||LE on thrd 0
 *                                    otherwise VT||0000000
 *   - Byte store to QW3[TM_WORD2] - Set VT bit (and LP/LE अगर present)
 *
 * Then we have all these "special" CI ops at these offset that trigger
 * all sorts of side effects:
 */
#घोषणा TM_SPC_ACK_EBB		0x800	/* Load8 ack EBB to reg*/
#घोषणा TM_SPC_ACK_OS_REG	0x810	/* Load16 ack OS irq to reg */
#घोषणा TM_SPC_PUSH_USR_CTX	0x808	/* Store32 Push/Validate user context */
#घोषणा TM_SPC_PULL_USR_CTX	0x808	/* Load32 Pull/Invalidate user context */
#घोषणा TM_SPC_SET_OS_PENDING	0x812	/* Store8 Set OS irq pending bit */
#घोषणा TM_SPC_PULL_OS_CTX	0x818	/* Load32/Load64 Pull/Invalidate OS context to reg */
#घोषणा TM_SPC_PULL_POOL_CTX	0x828	/* Load32/Load64 Pull/Invalidate Pool context to reg*/
#घोषणा TM_SPC_ACK_HV_REG	0x830	/* Load16 ack HV irq to reg */
#घोषणा TM_SPC_PULL_USR_CTX_OL	0xc08	/* Store8 Pull/Inval usr ctx to odd line */
#घोषणा TM_SPC_ACK_OS_EL	0xc10	/* Store8 ack OS irq to even line */
#घोषणा TM_SPC_ACK_HV_POOL_EL	0xc20	/* Store8 ack HV evt pool to even line */
#घोषणा TM_SPC_ACK_HV_EL	0xc30	/* Store8 ack HV irq to even line */
/* XXX more... */

/* NSR fields क्रम the various QW ack types */
#घोषणा TM_QW0_NSR_EB		PPC_BIT8(0)
#घोषणा TM_QW1_NSR_EO		PPC_BIT8(0)
#घोषणा TM_QW3_NSR_HE		PPC_BITMASK8(0,1)
#घोषणा  TM_QW3_NSR_HE_NONE	0
#घोषणा  TM_QW3_NSR_HE_POOL	1
#घोषणा  TM_QW3_NSR_HE_PHYS	2
#घोषणा  TM_QW3_NSR_HE_LSI	3
#घोषणा TM_QW3_NSR_I		PPC_BIT8(2)
#घोषणा TM_QW3_NSR_GRP_LVL	PPC_BIT8(3,7)

#पूर्ण_अगर /* _ASM_POWERPC_XIVE_REGS_H */
