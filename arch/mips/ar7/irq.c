<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006,2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2006,2007 Eugene Konev <ejka@खोलोwrt.org>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mach-ar7/ar7.h>

#घोषणा EXCEPT_OFFSET	0x80
#घोषणा PACE_OFFSET	0xA0
#घोषणा CHNLS_OFFSET	0x200

#घोषणा REG_OFFSET(irq, reg)	((irq) / 32 * 0x4 + reg * 0x10)
#घोषणा SEC_REG_OFFSET(reg)	(EXCEPT_OFFSET + reg * 0x8)
#घोषणा SEC_SR_OFFSET		(SEC_REG_OFFSET(0))	/* 0x80 */
#घोषणा CR_OFFSET(irq)		(REG_OFFSET(irq, 1))	/* 0x10 */
#घोषणा SEC_CR_OFFSET		(SEC_REG_OFFSET(1))	/* 0x88 */
#घोषणा ESR_OFFSET(irq)		(REG_OFFSET(irq, 2))	/* 0x20 */
#घोषणा SEC_ESR_OFFSET		(SEC_REG_OFFSET(2))	/* 0x90 */
#घोषणा ECR_OFFSET(irq)		(REG_OFFSET(irq, 3))	/* 0x30 */
#घोषणा SEC_ECR_OFFSET		(SEC_REG_OFFSET(3))	/* 0x98 */
#घोषणा PIR_OFFSET		(0x40)
#घोषणा MSR_OFFSET		(0x44)
#घोषणा PM_OFFSET(irq)		(REG_OFFSET(irq, 5))	/* 0x50 */
#घोषणा TM_OFFSET(irq)		(REG_OFFSET(irq, 6))	/* 0x60 */

#घोषणा REG(addr) ((u32 *)(KSEG1ADDR(AR7_REGS_IRQ) + addr))

#घोषणा CHNL_OFFSET(chnl) (CHNLS_OFFSET + (chnl * 4))

अटल पूर्णांक ar7_irq_base;

अटल व्योम ar7_unmask_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << ((d->irq - ar7_irq_base) % 32),
	       REG(ESR_OFFSET(d->irq - ar7_irq_base)));
पूर्ण

अटल व्योम ar7_mask_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << ((d->irq - ar7_irq_base) % 32),
	       REG(ECR_OFFSET(d->irq - ar7_irq_base)));
पूर्ण

अटल व्योम ar7_ack_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << ((d->irq - ar7_irq_base) % 32),
	       REG(CR_OFFSET(d->irq - ar7_irq_base)));
पूर्ण

अटल व्योम ar7_unmask_sec_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << (d->irq - ar7_irq_base - 40), REG(SEC_ESR_OFFSET));
पूर्ण

अटल व्योम ar7_mask_sec_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << (d->irq - ar7_irq_base - 40), REG(SEC_ECR_OFFSET));
पूर्ण

अटल व्योम ar7_ack_sec_irq(काष्ठा irq_data *d)
अणु
	ग_लिखोl(1 << (d->irq - ar7_irq_base - 40), REG(SEC_CR_OFFSET));
पूर्ण

अटल काष्ठा irq_chip ar7_irq_type = अणु
	.name = "AR7",
	.irq_unmask = ar7_unmask_irq,
	.irq_mask = ar7_mask_irq,
	.irq_ack = ar7_ack_irq
पूर्ण;

अटल काष्ठा irq_chip ar7_sec_irq_type = अणु
	.name = "AR7",
	.irq_unmask = ar7_unmask_sec_irq,
	.irq_mask = ar7_mask_sec_irq,
	.irq_ack = ar7_ack_sec_irq,
पूर्ण;

अटल व्योम __init ar7_irq_init(पूर्णांक base)
अणु
	पूर्णांक i;
	/*
	 * Disable पूर्णांकerrupts and clear pending
	 */
	ग_लिखोl(0xffffffff, REG(ECR_OFFSET(0)));
	ग_लिखोl(0xff, REG(ECR_OFFSET(32)));
	ग_लिखोl(0xffffffff, REG(SEC_ECR_OFFSET));
	ग_लिखोl(0xffffffff, REG(CR_OFFSET(0)));
	ग_लिखोl(0xff, REG(CR_OFFSET(32)));
	ग_लिखोl(0xffffffff, REG(SEC_CR_OFFSET));

	ar7_irq_base = base;

	क्रम (i = 0; i < 40; i++) अणु
		ग_लिखोl(i, REG(CHNL_OFFSET(i)));
		/* Primary IRQ's */
		irq_set_chip_and_handler(base + i, &ar7_irq_type,
					 handle_level_irq);
		/* Secondary IRQ's */
		अगर (i < 32)
			irq_set_chip_and_handler(base + i + 40,
						 &ar7_sec_irq_type,
						 handle_level_irq);
	पूर्ण

	अगर (request_irq(2, no_action, IRQF_NO_THREAD, "AR7 cascade interrupt",
			शून्य))
		pr_err("Failed to request irq 2 (AR7 cascade interrupt)\n");
	अगर (request_irq(ar7_irq_base, no_action, IRQF_NO_THREAD,
			"AR7 cascade interrupt", शून्य)) अणु
		pr_err("Failed to request irq %d (AR7 cascade interrupt)\n",
		       ar7_irq_base);
	पूर्ण
	set_c0_status(IE_IRQ0);
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	mips_cpu_irq_init();
	ar7_irq_init(8);
पूर्ण

अटल व्योम ar7_cascade(व्योम)
अणु
	u32 status;
	पूर्णांक i, irq;

	/* Primary IRQ's */
	irq = पढ़ोl(REG(PIR_OFFSET)) & 0x3f;
	अगर (irq) अणु
		करो_IRQ(ar7_irq_base + irq);
		वापस;
	पूर्ण

	/* Secondary IRQ's are cascaded through primary '0' */
	ग_लिखोl(1, REG(CR_OFFSET(irq)));
	status = पढ़ोl(REG(SEC_SR_OFFSET));
	क्रम (i = 0; i < 32; i++) अणु
		अगर (status & 1) अणु
			करो_IRQ(ar7_irq_base + i + 40);
			वापस;
		पूर्ण
		status >>= 1;
	पूर्ण

	spurious_पूर्णांकerrupt();
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending = पढ़ो_c0_status() & पढ़ो_c0_cause() & ST0_IM;
	अगर (pending & STATUSF_IP7)		/* cpu समयr */
		करो_IRQ(7);
	अन्यथा अगर (pending & STATUSF_IP2)		/* पूर्णांक0 hardware line */
		ar7_cascade();
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण
