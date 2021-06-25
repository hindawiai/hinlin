<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IPIC निजी definitions and काष्ठाure.
 *
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2005 Freescale Semiconductor, Inc
 */
#अगर_अघोषित __IPIC_H__
#घोषणा __IPIC_H__

#समावेश <यंत्र/ipic.h>

#घोषणा NR_IPIC_INTS 128

/* External IRQS */
#घोषणा IPIC_IRQ_EXT0 48
#घोषणा IPIC_IRQ_EXT1 17
#घोषणा IPIC_IRQ_EXT7 23

/* Default Priority Registers */
#घोषणा IPIC_PRIORITY_DEFAULT 0x05309770

/* System Global Interrupt Configuration Register */
#घोषणा	SICFR_IPSA	0x00010000
#घोषणा	SICFR_IPSB	0x00020000
#घोषणा	SICFR_IPSC	0x00040000
#घोषणा	SICFR_IPSD	0x00080000
#घोषणा	SICFR_MPSA	0x00200000
#घोषणा	SICFR_MPSB	0x00400000

/* System External Interrupt Mask Register */
#घोषणा	SEMSR_SIRQ0	0x00008000

/* System Error Control Register */
#घोषणा SERCR_MCPR	0x00000001

काष्ठा ipic अणु
	अस्थिर u32 __iomem	*regs;

	/* The remapper क्रम this IPIC */
	काष्ठा irq_करोमुख्य		*irqhost;
पूर्ण;

काष्ठा ipic_info अणु
	u8	ack;		/* pending रेजिस्टर offset from base अगर the irq
				   supports ack operation */
	u8	mask;		/* mask रेजिस्टर offset from base */
	u8	prio;		/* priority रेजिस्टर offset from base */
	u8	क्रमce;		/* क्रमce रेजिस्टर offset from base */
	u8	bit;		/* रेजिस्टर bit position (as per करोc)
				   bit mask = 1 << (31 - bit) */
	u8	prio_mask;	/* priority mask value */
पूर्ण;

#पूर्ण_अगर /* __IPIC_H__ */
