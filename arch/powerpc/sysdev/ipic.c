<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/sysdev/ipic.c
 *
 * IPIC routines implementations.
 *
 * Copyright 2005 Freescale Semiconductor, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fsl_devices.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/ipic.h>

#समावेश "ipic.h"

अटल काष्ठा ipic * primary_ipic;
अटल काष्ठा irq_chip ipic_level_irq_chip, ipic_edge_irq_chip;
अटल DEFINE_RAW_SPINLOCK(ipic_lock);

अटल काष्ठा ipic_info ipic_info[] = अणु
	[1] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 16,
		.prio_mask = 0,
	पूर्ण,
	[2] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 17,
		.prio_mask = 1,
	पूर्ण,
	[3] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 18,
		.prio_mask = 2,
	पूर्ण,
	[4] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 19,
		.prio_mask = 3,
	पूर्ण,
	[5] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 20,
		.prio_mask = 4,
	पूर्ण,
	[6] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 21,
		.prio_mask = 5,
	पूर्ण,
	[7] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 22,
		.prio_mask = 6,
	पूर्ण,
	[8] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_C,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 23,
		.prio_mask = 7,
	पूर्ण,
	[9] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 24,
		.prio_mask = 0,
	पूर्ण,
	[10] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 25,
		.prio_mask = 1,
	पूर्ण,
	[11] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 26,
		.prio_mask = 2,
	पूर्ण,
	[12] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 27,
		.prio_mask = 3,
	पूर्ण,
	[13] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 28,
		.prio_mask = 4,
	पूर्ण,
	[14] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 29,
		.prio_mask = 5,
	पूर्ण,
	[15] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 30,
		.prio_mask = 6,
	पूर्ण,
	[16] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_D,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 31,
		.prio_mask = 7,
	पूर्ण,
	[17] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 1,
		.prio_mask = 5,
	पूर्ण,
	[18] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 2,
		.prio_mask = 6,
	पूर्ण,
	[19] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 3,
		.prio_mask = 7,
	पूर्ण,
	[20] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 4,
		.prio_mask = 4,
	पूर्ण,
	[21] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 5,
		.prio_mask = 5,
	पूर्ण,
	[22] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 6,
		.prio_mask = 6,
	पूर्ण,
	[23] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 7,
		.prio_mask = 7,
	पूर्ण,
	[32] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 0,
		.prio_mask = 0,
	पूर्ण,
	[33] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 1,
		.prio_mask = 1,
	पूर्ण,
	[34] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 2,
		.prio_mask = 2,
	पूर्ण,
	[35] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 3,
		.prio_mask = 3,
	पूर्ण,
	[36] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 4,
		.prio_mask = 4,
	पूर्ण,
	[37] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 5,
		.prio_mask = 5,
	पूर्ण,
	[38] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 6,
		.prio_mask = 6,
	पूर्ण,
	[39] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_A,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 7,
		.prio_mask = 7,
	पूर्ण,
	[40] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 8,
		.prio_mask = 0,
	पूर्ण,
	[41] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 9,
		.prio_mask = 1,
	पूर्ण,
	[42] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 10,
		.prio_mask = 2,
	पूर्ण,
	[43] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 11,
		.prio_mask = 3,
	पूर्ण,
	[44] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 12,
		.prio_mask = 4,
	पूर्ण,
	[45] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 13,
		.prio_mask = 5,
	पूर्ण,
	[46] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 14,
		.prio_mask = 6,
	पूर्ण,
	[47] = अणु
		.mask	= IPIC_SIMSR_H,
		.prio	= IPIC_SIPRR_B,
		.क्रमce	= IPIC_SIFCR_H,
		.bit	= 15,
		.prio_mask = 7,
	पूर्ण,
	[48] = अणु
		.ack	= IPIC_SEPNR,
		.mask	= IPIC_SEMSR,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SEFCR,
		.bit	= 0,
		.prio_mask = 4,
	पूर्ण,
	[64] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 0,
		.prio_mask = 0,
	पूर्ण,
	[65] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 1,
		.prio_mask = 1,
	पूर्ण,
	[66] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 2,
		.prio_mask = 2,
	पूर्ण,
	[67] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_A,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 3,
		.prio_mask = 3,
	पूर्ण,
	[68] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 4,
		.prio_mask = 0,
	पूर्ण,
	[69] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 5,
		.prio_mask = 1,
	पूर्ण,
	[70] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 6,
		.prio_mask = 2,
	पूर्ण,
	[71] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= IPIC_SMPRR_B,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 7,
		.prio_mask = 3,
	पूर्ण,
	[72] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 8,
	पूर्ण,
	[73] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 9,
	पूर्ण,
	[74] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 10,
	पूर्ण,
	[75] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 11,
	पूर्ण,
	[76] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 12,
	पूर्ण,
	[77] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 13,
	पूर्ण,
	[78] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 14,
	पूर्ण,
	[79] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 15,
	पूर्ण,
	[80] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 16,
	पूर्ण,
	[81] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 17,
	पूर्ण,
	[82] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 18,
	पूर्ण,
	[83] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 19,
	पूर्ण,
	[84] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 20,
	पूर्ण,
	[85] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 21,
	पूर्ण,
	[86] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 22,
	पूर्ण,
	[87] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 23,
	पूर्ण,
	[88] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 24,
	पूर्ण,
	[89] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 25,
	पूर्ण,
	[90] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 26,
	पूर्ण,
	[91] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 27,
	पूर्ण,
	[94] = अणु
		.mask	= IPIC_SIMSR_L,
		.prio	= 0,
		.क्रमce	= IPIC_SIFCR_L,
		.bit	= 30,
	पूर्ण,
पूर्ण;

अटल अंतरभूत u32 ipic_पढ़ो(अस्थिर u32 __iomem *base, अचिन्हित पूर्णांक reg)
अणु
	वापस in_be32(base + (reg >> 2));
पूर्ण

अटल अंतरभूत व्योम ipic_ग_लिखो(अस्थिर u32 __iomem *base, अचिन्हित पूर्णांक reg, u32 value)
अणु
	out_be32(base + (reg >> 2), value);
पूर्ण

अटल अंतरभूत काष्ठा ipic * ipic_from_irq(अचिन्हित पूर्णांक virq)
अणु
	वापस primary_ipic;
पूर्ण

अटल व्योम ipic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा ipic *ipic = ipic_from_irq(d->irq);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 temp;

	raw_spin_lock_irqsave(&ipic_lock, flags);

	temp = ipic_पढ़ो(ipic->regs, ipic_info[src].mask);
	temp |= (1 << (31 - ipic_info[src].bit));
	ipic_ग_लिखो(ipic->regs, ipic_info[src].mask, temp);

	raw_spin_unlock_irqrestore(&ipic_lock, flags);
पूर्ण

अटल व्योम ipic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा ipic *ipic = ipic_from_irq(d->irq);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 temp;

	raw_spin_lock_irqsave(&ipic_lock, flags);

	temp = ipic_पढ़ो(ipic->regs, ipic_info[src].mask);
	temp &= ~(1 << (31 - ipic_info[src].bit));
	ipic_ग_लिखो(ipic->regs, ipic_info[src].mask, temp);

	/* mb() can't guarantee that masking is finished.  But it करोes finish
	 * क्रम nearly all हालs. */
	mb();

	raw_spin_unlock_irqrestore(&ipic_lock, flags);
पूर्ण

अटल व्योम ipic_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा ipic *ipic = ipic_from_irq(d->irq);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 temp;

	raw_spin_lock_irqsave(&ipic_lock, flags);

	temp = 1 << (31 - ipic_info[src].bit);
	ipic_ग_लिखो(ipic->regs, ipic_info[src].ack, temp);

	/* mb() can't guarantee that ack is finished.  But it करोes finish
	 * क्रम nearly all हालs. */
	mb();

	raw_spin_unlock_irqrestore(&ipic_lock, flags);
पूर्ण

अटल व्योम ipic_mask_irq_and_ack(काष्ठा irq_data *d)
अणु
	काष्ठा ipic *ipic = ipic_from_irq(d->irq);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 temp;

	raw_spin_lock_irqsave(&ipic_lock, flags);

	temp = ipic_पढ़ो(ipic->regs, ipic_info[src].mask);
	temp &= ~(1 << (31 - ipic_info[src].bit));
	ipic_ग_लिखो(ipic->regs, ipic_info[src].mask, temp);

	temp = 1 << (31 - ipic_info[src].bit);
	ipic_ग_लिखो(ipic->regs, ipic_info[src].ack, temp);

	/* mb() can't guarantee that ack is finished.  But it करोes finish
	 * क्रम nearly all हालs. */
	mb();

	raw_spin_unlock_irqrestore(&ipic_lock, flags);
पूर्ण

अटल पूर्णांक ipic_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा ipic *ipic = ipic_from_irq(d->irq);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित पूर्णांक vold, vnew, edibit;

	अगर (flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_LEVEL_LOW;

	/* ipic supports only low निश्चितion and high-to-low change senses
	 */
	अगर (!(flow_type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_EDGE_FALLING))) अणु
		prपूर्णांकk(KERN_ERR "ipic: sense type 0x%x not supported\n",
			flow_type);
		वापस -EINVAL;
	पूर्ण
	/* ipic supports only edge mode on बाह्यal पूर्णांकerrupts */
	अगर ((flow_type & IRQ_TYPE_EDGE_FALLING) && !ipic_info[src].ack) अणु
		prपूर्णांकk(KERN_ERR "ipic: edge sense not supported on internal "
				"interrupts\n");
		वापस -EINVAL;

	पूर्ण

	irqd_set_trigger_type(d, flow_type);
	अगर (flow_type & IRQ_TYPE_LEVEL_LOW)  अणु
		irq_set_handler_locked(d, handle_level_irq);
		d->chip = &ipic_level_irq_chip;
	पूर्ण अन्यथा अणु
		irq_set_handler_locked(d, handle_edge_irq);
		d->chip = &ipic_edge_irq_chip;
	पूर्ण

	/* only EXT IRQ senses are programmable on ipic
	 * पूर्णांकernal IRQ senses are LEVEL_LOW
	 */
	अगर (src == IPIC_IRQ_EXT0)
		edibit = 15;
	अन्यथा
		अगर (src >= IPIC_IRQ_EXT1 && src <= IPIC_IRQ_EXT7)
			edibit = (14 - (src - IPIC_IRQ_EXT1));
		अन्यथा
			वापस (flow_type & IRQ_TYPE_LEVEL_LOW) ? 0 : -EINVAL;

	vold = ipic_पढ़ो(ipic->regs, IPIC_SECNR);
	अगर ((flow_type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_FALLING) अणु
		vnew = vold | (1 << edibit);
	पूर्ण अन्यथा अणु
		vnew = vold & ~(1 << edibit);
	पूर्ण
	अगर (vold != vnew)
		ipic_ग_लिखो(ipic->regs, IPIC_SECNR, vnew);
	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

/* level पूर्णांकerrupts and edge पूर्णांकerrupts have dअगरferent ack operations */
अटल काष्ठा irq_chip ipic_level_irq_chip = अणु
	.name		= "IPIC",
	.irq_unmask	= ipic_unmask_irq,
	.irq_mask	= ipic_mask_irq,
	.irq_mask_ack	= ipic_mask_irq,
	.irq_set_type	= ipic_set_irq_type,
पूर्ण;

अटल काष्ठा irq_chip ipic_edge_irq_chip = अणु
	.name		= "IPIC",
	.irq_unmask	= ipic_unmask_irq,
	.irq_mask	= ipic_mask_irq,
	.irq_mask_ack	= ipic_mask_irq_and_ack,
	.irq_ack	= ipic_ack_irq,
	.irq_set_type	= ipic_set_irq_type,
पूर्ण;

अटल पूर्णांक ipic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			   क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Exact match, unless ipic node is शून्य */
	काष्ठा device_node *of_node = irq_करोमुख्य_get_of_node(h);
	वापस of_node == शून्य || of_node == node;
पूर्ण

अटल पूर्णांक ipic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	काष्ठा ipic *ipic = h->host_data;

	irq_set_chip_data(virq, ipic);
	irq_set_chip_and_handler(virq, &ipic_level_irq_chip, handle_level_irq);

	/* Set शेष irq type */
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ipic_host_ops = अणु
	.match	= ipic_host_match,
	.map	= ipic_host_map,
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

काष्ठा ipic * __init ipic_init(काष्ठा device_node *node, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ipic	*ipic;
	काष्ठा resource res;
	u32 temp = 0, ret;

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret)
		वापस शून्य;

	ipic = kzalloc(माप(*ipic), GFP_KERNEL);
	अगर (ipic == शून्य)
		वापस शून्य;

	ipic->irqhost = irq_करोमुख्य_add_linear(node, NR_IPIC_INTS,
					      &ipic_host_ops, ipic);
	अगर (ipic->irqhost == शून्य) अणु
		kमुक्त(ipic);
		वापस शून्य;
	पूर्ण

	ipic->regs = ioremap(res.start, resource_size(&res));

	/* init hw */
	ipic_ग_लिखो(ipic->regs, IPIC_SICNR, 0x0);

	/* शेष priority scheme is grouped. If spपढ़ो mode is required
	 * configure SICFR accordingly */
	अगर (flags & IPIC_SPREADMODE_GRP_A)
		temp |= SICFR_IPSA;
	अगर (flags & IPIC_SPREADMODE_GRP_B)
		temp |= SICFR_IPSB;
	अगर (flags & IPIC_SPREADMODE_GRP_C)
		temp |= SICFR_IPSC;
	अगर (flags & IPIC_SPREADMODE_GRP_D)
		temp |= SICFR_IPSD;
	अगर (flags & IPIC_SPREADMODE_MIX_A)
		temp |= SICFR_MPSA;
	अगर (flags & IPIC_SPREADMODE_MIX_B)
		temp |= SICFR_MPSB;

	ipic_ग_लिखो(ipic->regs, IPIC_SICFR, temp);

	/* handle MCP route */
	temp = 0;
	अगर (flags & IPIC_DISABLE_MCP_OUT)
		temp = SERCR_MCPR;
	ipic_ग_लिखो(ipic->regs, IPIC_SERCR, temp);

	/* handle routing of IRQ0 to MCP */
	temp = ipic_पढ़ो(ipic->regs, IPIC_SEMSR);

	अगर (flags & IPIC_IRQ0_MCP)
		temp |= SEMSR_SIRQ0;
	अन्यथा
		temp &= ~SEMSR_SIRQ0;

	ipic_ग_लिखो(ipic->regs, IPIC_SEMSR, temp);

	primary_ipic = ipic;
	irq_set_शेष_host(primary_ipic->irqhost);

	ipic_ग_लिखो(ipic->regs, IPIC_SIMSR_H, 0);
	ipic_ग_लिखो(ipic->regs, IPIC_SIMSR_L, 0);

	prपूर्णांकk ("IPIC (%d IRQ sources) at %p\n", NR_IPIC_INTS,
			primary_ipic->regs);

	वापस ipic;
पूर्ण

व्योम ipic_set_शेष_priority(व्योम)
अणु
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SIPRR_A, IPIC_PRIORITY_DEFAULT);
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SIPRR_B, IPIC_PRIORITY_DEFAULT);
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SIPRR_C, IPIC_PRIORITY_DEFAULT);
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SIPRR_D, IPIC_PRIORITY_DEFAULT);
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SMPRR_A, IPIC_PRIORITY_DEFAULT);
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SMPRR_B, IPIC_PRIORITY_DEFAULT);
पूर्ण

u32 ipic_get_mcp_status(व्योम)
अणु
	वापस primary_ipic ? ipic_पढ़ो(primary_ipic->regs, IPIC_SERSR) : 0;
पूर्ण

व्योम ipic_clear_mcp_status(u32 mask)
अणु
	ipic_ग_लिखो(primary_ipic->regs, IPIC_SERSR, mask);
पूर्ण

/* Return an पूर्णांकerrupt vector or 0 अगर no पूर्णांकerrupt is pending. */
अचिन्हित पूर्णांक ipic_get_irq(व्योम)
अणु
	पूर्णांक irq;

	BUG_ON(primary_ipic == शून्य);

#घोषणा IPIC_SIVCR_VECTOR_MASK	0x7f
	irq = ipic_पढ़ो(primary_ipic->regs, IPIC_SIVCR) & IPIC_SIVCR_VECTOR_MASK;

	अगर (irq == 0)    /* 0 --> no irq is pending */
		वापस 0;

	वापस irq_linear_revmap(primary_ipic->irqhost, irq);
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल काष्ठा अणु
	u32 sicfr;
	u32 siprr[2];
	u32 simsr[2];
	u32 sicnr;
	u32 smprr[2];
	u32 semsr;
	u32 secnr;
	u32 sermr;
	u32 sercr;
पूर्ण ipic_saved_state;

अटल पूर्णांक ipic_suspend(व्योम)
अणु
	काष्ठा ipic *ipic = primary_ipic;

	ipic_saved_state.sicfr = ipic_पढ़ो(ipic->regs, IPIC_SICFR);
	ipic_saved_state.siprr[0] = ipic_पढ़ो(ipic->regs, IPIC_SIPRR_A);
	ipic_saved_state.siprr[1] = ipic_पढ़ो(ipic->regs, IPIC_SIPRR_D);
	ipic_saved_state.simsr[0] = ipic_पढ़ो(ipic->regs, IPIC_SIMSR_H);
	ipic_saved_state.simsr[1] = ipic_पढ़ो(ipic->regs, IPIC_SIMSR_L);
	ipic_saved_state.sicnr = ipic_पढ़ो(ipic->regs, IPIC_SICNR);
	ipic_saved_state.smprr[0] = ipic_पढ़ो(ipic->regs, IPIC_SMPRR_A);
	ipic_saved_state.smprr[1] = ipic_पढ़ो(ipic->regs, IPIC_SMPRR_B);
	ipic_saved_state.semsr = ipic_पढ़ो(ipic->regs, IPIC_SEMSR);
	ipic_saved_state.secnr = ipic_पढ़ो(ipic->regs, IPIC_SECNR);
	ipic_saved_state.sermr = ipic_पढ़ो(ipic->regs, IPIC_SERMR);
	ipic_saved_state.sercr = ipic_पढ़ो(ipic->regs, IPIC_SERCR);

	अगर (fsl_deep_sleep()) अणु
		/* In deep sleep, make sure there can be no
		 * pending पूर्णांकerrupts, as this can cause
		 * problems on 831x.
		 */
		ipic_ग_लिखो(ipic->regs, IPIC_SIMSR_H, 0);
		ipic_ग_लिखो(ipic->regs, IPIC_SIMSR_L, 0);
		ipic_ग_लिखो(ipic->regs, IPIC_SEMSR, 0);
		ipic_ग_लिखो(ipic->regs, IPIC_SERMR, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipic_resume(व्योम)
अणु
	काष्ठा ipic *ipic = primary_ipic;

	ipic_ग_लिखो(ipic->regs, IPIC_SICFR, ipic_saved_state.sicfr);
	ipic_ग_लिखो(ipic->regs, IPIC_SIPRR_A, ipic_saved_state.siprr[0]);
	ipic_ग_लिखो(ipic->regs, IPIC_SIPRR_D, ipic_saved_state.siprr[1]);
	ipic_ग_लिखो(ipic->regs, IPIC_SIMSR_H, ipic_saved_state.simsr[0]);
	ipic_ग_लिखो(ipic->regs, IPIC_SIMSR_L, ipic_saved_state.simsr[1]);
	ipic_ग_लिखो(ipic->regs, IPIC_SICNR, ipic_saved_state.sicnr);
	ipic_ग_लिखो(ipic->regs, IPIC_SMPRR_A, ipic_saved_state.smprr[0]);
	ipic_ग_लिखो(ipic->regs, IPIC_SMPRR_B, ipic_saved_state.smprr[1]);
	ipic_ग_लिखो(ipic->regs, IPIC_SEMSR, ipic_saved_state.semsr);
	ipic_ग_लिखो(ipic->regs, IPIC_SECNR, ipic_saved_state.secnr);
	ipic_ग_लिखो(ipic->regs, IPIC_SERMR, ipic_saved_state.sermr);
	ipic_ग_लिखो(ipic->regs, IPIC_SERCR, ipic_saved_state.sercr);
पूर्ण
#अन्यथा
#घोषणा ipic_suspend शून्य
#घोषणा ipic_resume शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops ipic_syscore_ops = अणु
	.suspend = ipic_suspend,
	.resume = ipic_resume,
पूर्ण;

अटल पूर्णांक __init init_ipic_syscore(व्योम)
अणु
	अगर (!primary_ipic || !primary_ipic->regs)
		वापस -ENODEV;

	prपूर्णांकk(KERN_DEBUG "Registering ipic system core operations\n");
	रेजिस्टर_syscore_ops(&ipic_syscore_ops);

	वापस 0;
पूर्ण

subsys_initcall(init_ipic_syscore);
