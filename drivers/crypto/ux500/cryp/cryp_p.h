<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 */

#अगर_अघोषित _CRYP_P_H_
#घोषणा _CRYP_P_H_

#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>

#समावेश "cryp.h"
#समावेश "cryp_irqp.h"

/*
 * Generic Macros
 */
#घोषणा CRYP_SET_BITS(reg_name, mask) \
	ग_लिखोl_relaxed((पढ़ोl_relaxed(reg_name) | mask), reg_name)

#घोषणा CRYP_WRITE_BIT(reg_name, val, mask) \
	ग_लिखोl_relaxed(((पढ़ोl_relaxed(reg_name) & ~(mask)) |\
			((val) & (mask))), reg_name)

#घोषणा CRYP_TEST_BITS(reg_name, val) \
	(पढ़ोl_relaxed(reg_name) & (val))

#घोषणा CRYP_PUT_BITS(reg, val, shअगरt, mask) \
	ग_लिखोl_relaxed(((पढ़ोl_relaxed(reg) & ~(mask)) | \
		(((u32)val << shअगरt) & (mask))), reg)

/*
 * CRYP specअगरic Macros
 */
#घोषणा CRYP_PERIPHERAL_ID0		0xE3
#घोषणा CRYP_PERIPHERAL_ID1		0x05

#घोषणा CRYP_PERIPHERAL_ID2_DB8500	0x28
#घोषणा CRYP_PERIPHERAL_ID3		0x00

#घोषणा CRYP_PCELL_ID0			0x0D
#घोषणा CRYP_PCELL_ID1			0xF0
#घोषणा CRYP_PCELL_ID2			0x05
#घोषणा CRYP_PCELL_ID3			0xB1

/*
 * CRYP रेजिस्टर शेष values
 */
#घोषणा MAX_DEVICE_SUPPORT		2

/* Priv set, keyrden set and datatype 8bits swapped set as शेष. */
#घोषणा CRYP_CR_DEFAULT			0x0482
#घोषणा CRYP_DMACR_DEFAULT		0x0
#घोषणा CRYP_IMSC_DEFAULT		0x0
#घोषणा CRYP_DIN_DEFAULT		0x0
#घोषणा CRYP_DOUT_DEFAULT		0x0
#घोषणा CRYP_KEY_DEFAULT		0x0
#घोषणा CRYP_INIT_VECT_DEFAULT		0x0

/*
 * CRYP Control रेजिस्टर specअगरic mask
 */
#घोषणा CRYP_CR_SECURE_MASK		BIT(0)
#घोषणा CRYP_CR_PRLG_MASK		BIT(1)
#घोषणा CRYP_CR_ALGOसूची_MASK		BIT(2)
#घोषणा CRYP_CR_ALGOMODE_MASK		(BIT(5) | BIT(4) | BIT(3))
#घोषणा CRYP_CR_DATATYPE_MASK		(BIT(7) | BIT(6))
#घोषणा CRYP_CR_KEYSIZE_MASK		(BIT(9) | BIT(8))
#घोषणा CRYP_CR_KEYRDEN_MASK		BIT(10)
#घोषणा CRYP_CR_KSE_MASK		BIT(11)
#घोषणा CRYP_CR_START_MASK		BIT(12)
#घोषणा CRYP_CR_INIT_MASK		BIT(13)
#घोषणा CRYP_CR_FFLUSH_MASK		BIT(14)
#घोषणा CRYP_CR_CRYPEN_MASK		BIT(15)
#घोषणा CRYP_CR_CONTEXT_SAVE_MASK	(CRYP_CR_SECURE_MASK |\
					 CRYP_CR_PRLG_MASK |\
					 CRYP_CR_ALGOसूची_MASK |\
					 CRYP_CR_ALGOMODE_MASK |\
					 CRYP_CR_KEYSIZE_MASK |\
					 CRYP_CR_KEYRDEN_MASK |\
					 CRYP_CR_DATATYPE_MASK)


#घोषणा CRYP_SR_INFIFO_READY_MASK	(BIT(0) | BIT(1))
#घोषणा CRYP_SR_IFEM_MASK		BIT(0)
#घोषणा CRYP_SR_BUSY_MASK		BIT(4)

/*
 * Bit position used जबतक setting bits in रेजिस्टर
 */
#घोषणा CRYP_CR_PRLG_POS		1
#घोषणा CRYP_CR_ALGOसूची_POS		2
#घोषणा CRYP_CR_ALGOMODE_POS		3
#घोषणा CRYP_CR_DATATYPE_POS		6
#घोषणा CRYP_CR_KEYSIZE_POS		8
#घोषणा CRYP_CR_KEYRDEN_POS		10
#घोषणा CRYP_CR_KSE_POS			11
#घोषणा CRYP_CR_START_POS		12
#घोषणा CRYP_CR_INIT_POS		13
#घोषणा CRYP_CR_CRYPEN_POS		15

#घोषणा CRYP_SR_BUSY_POS		4

/*
 * CRYP PCRs------PC_न_अंकD control रेजिस्टर
 * BIT_MASK
 */
#घोषणा CRYP_DMA_REQ_MASK		(BIT(1) | BIT(0))
#घोषणा CRYP_DMA_REQ_MASK_POS		0


काष्ठा cryp_प्रणाली_context अणु
	/* CRYP Register काष्ठाure */
	काष्ठा cryp_रेजिस्टर *p_cryp_reg[MAX_DEVICE_SUPPORT];
पूर्ण;

#पूर्ण_अगर
