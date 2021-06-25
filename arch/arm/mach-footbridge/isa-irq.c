<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-footbridge/irq.c
 *
 *  Copyright (C) 1996-2000 Russell King
 *
 *  Changelog:
 *   22-Aug-1998 RMK	Reकाष्ठाured IRQ routines
 *   03-Sep-1998 PJB	Merged CATS support
 *   20-Jan-1998 RMK	Started merge of EBSA286, CATS and NetWinder
 *   26-Jan-1999 PJB	Don't use IACK on CATS
 *   16-Mar-1999 RMK	Added स्वतःdetect of ISA PICs
 */
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "common.h"

अटल व्योम isa_mask_pic_lo_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq & 7);

	outb(inb(PIC_MASK_LO) | mask, PIC_MASK_LO);
पूर्ण

अटल व्योम isa_ack_pic_lo_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq & 7);

	outb(inb(PIC_MASK_LO) | mask, PIC_MASK_LO);
	outb(0x20, PIC_LO);
पूर्ण

अटल व्योम isa_unmask_pic_lo_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq & 7);

	outb(inb(PIC_MASK_LO) & ~mask, PIC_MASK_LO);
पूर्ण

अटल काष्ठा irq_chip isa_lo_chip = अणु
	.irq_ack	= isa_ack_pic_lo_irq,
	.irq_mask	= isa_mask_pic_lo_irq,
	.irq_unmask	= isa_unmask_pic_lo_irq,
पूर्ण;

अटल व्योम isa_mask_pic_hi_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq & 7);

	outb(inb(PIC_MASK_HI) | mask, PIC_MASK_HI);
पूर्ण

अटल व्योम isa_ack_pic_hi_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq & 7);

	outb(inb(PIC_MASK_HI) | mask, PIC_MASK_HI);
	outb(0x62, PIC_LO);
	outb(0x20, PIC_HI);
पूर्ण

अटल व्योम isa_unmask_pic_hi_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq & 7);

	outb(inb(PIC_MASK_HI) & ~mask, PIC_MASK_HI);
पूर्ण

अटल काष्ठा irq_chip isa_hi_chip = अणु
	.irq_ack	= isa_ack_pic_hi_irq,
	.irq_mask	= isa_mask_pic_hi_irq,
	.irq_unmask	= isa_unmask_pic_hi_irq,
पूर्ण;

अटल व्योम isa_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक isa_irq = *(अचिन्हित अक्षर *)PCIIACK_BASE;

	अगर (isa_irq < _ISA_IRQ(0) || isa_irq >= _ISA_IRQ(16)) अणु
		करो_bad_IRQ(desc);
		वापस;
	पूर्ण

	generic_handle_irq(isa_irq);
पूर्ण

अटल काष्ठा resource pic1_resource = अणु
	.name	= "pic1",
	.start	= 0x20,
	.end	= 0x3f,
पूर्ण;

अटल काष्ठा resource pic2_resource = अणु
	.name	= "pic2",
	.start	= 0xa0,
	.end	= 0xbf,
पूर्ण;

व्योम __init isa_init_irq(अचिन्हित पूर्णांक host_irq)
अणु
	अचिन्हित पूर्णांक irq;

	/*
	 * Setup, and then probe क्रम an ISA PIC
	 * If the PIC is not there, then we
	 * ignore the PIC.
	 */
	outb(0x11, PIC_LO);
	outb(_ISA_IRQ(0), PIC_MASK_LO);	/* IRQ number		*/
	outb(0x04, PIC_MASK_LO);	/* Slave on Ch2		*/
	outb(0x01, PIC_MASK_LO);	/* x86			*/
	outb(0xf5, PIC_MASK_LO);	/* pattern: 11110101	*/

	outb(0x11, PIC_HI);
	outb(_ISA_IRQ(8), PIC_MASK_HI);	/* IRQ number		*/
	outb(0x02, PIC_MASK_HI);	/* Slave on Ch1		*/
	outb(0x01, PIC_MASK_HI);	/* x86			*/
	outb(0xfa, PIC_MASK_HI);	/* pattern: 11111010	*/

	outb(0x0b, PIC_LO);
	outb(0x0b, PIC_HI);

	अगर (inb(PIC_MASK_LO) == 0xf5 && inb(PIC_MASK_HI) == 0xfa) अणु
		outb(0xff, PIC_MASK_LO);/* mask all IRQs	*/
		outb(0xff, PIC_MASK_HI);/* mask all IRQs	*/
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "IRQ: ISA PIC not found\n");
		host_irq = (अचिन्हित पूर्णांक)-1;
	पूर्ण

	अगर (host_irq != (अचिन्हित पूर्णांक)-1) अणु
		क्रम (irq = _ISA_IRQ(0); irq < _ISA_IRQ(8); irq++) अणु
			irq_set_chip_and_handler(irq, &isa_lo_chip,
						 handle_level_irq);
			irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
		पूर्ण

		क्रम (irq = _ISA_IRQ(8); irq < _ISA_IRQ(16); irq++) अणु
			irq_set_chip_and_handler(irq, &isa_hi_chip,
						 handle_level_irq);
			irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
		पूर्ण

		request_resource(&ioport_resource, &pic1_resource);
		request_resource(&ioport_resource, &pic2_resource);

		irq = IRQ_ISA_CASCADE;
		अगर (request_irq(irq, no_action, 0, "cascade", शून्य))
			pr_err("Failed to request irq %u (cascade)\n", irq);

		irq_set_chained_handler(host_irq, isa_irq_handler);

		/*
		 * On the NetWinder, करोn't स्वतःmatically
		 * enable ISA IRQ11 when it is requested.
		 * There appears to be a missing pull-up
		 * resistor on this line.
		 */
		अगर (machine_is_netwinder())
			irq_modअगरy_status(_ISA_IRQ(11),
				IRQ_NOREQUEST | IRQ_NOPROBE, IRQ_NOAUTOEN);
	पूर्ण
पूर्ण


