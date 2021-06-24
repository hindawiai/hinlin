<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	WAX Device Driver
 *
 *	(c) Copyright 2000 The Puffin Group Inc.
 *
 *	by Helge Deller <deller@gmx.de>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>

#समावेश "gsc.h"

#घोषणा WAX_GSC_IRQ	7	/* Hardcoded Interrupt क्रम GSC */

अटल व्योम wax_choose_irq(काष्ठा parisc_device *dev, व्योम *ctrl)
अणु
	पूर्णांक irq;

	चयन (dev->id.sversion) अणु
		हाल 0x73:	irq =  1; अवरोध; /* i8042 General */
		हाल 0x8c:	irq =  6; अवरोध; /* Serial */
		हाल 0x90:	irq = 10; अवरोध; /* EISA */
		शेष:	वापस;		 /* Unknown */
	पूर्ण

	gsc_asic_assign_irq(ctrl, irq, &dev->irq);

	चयन (dev->id.sversion) अणु
		हाल 0x73:	irq =  2; अवरोध; /* i8042 High-priority */
		हाल 0x90:	irq =  0; अवरोध; /* EISA NMI */
		शेष:	वापस;		 /* No secondary IRQ */
	पूर्ण

	gsc_asic_assign_irq(ctrl, irq, &dev->aux_irq);
पूर्ण

अटल व्योम __init
wax_init_irq(काष्ठा gsc_asic *wax)
अणु
	अचिन्हित दीर्घ base = wax->hpa;

	/* Wax-off */
	gsc_ग_लिखोl(0x00000000, base+OFFSET_IMR);

	/* clear pending पूर्णांकerrupts */
	gsc_पढ़ोl(base+OFFSET_IRR);

	/* We're not really convinced we want to reset the onboard
         * devices. Firmware करोes it क्रम us...
	 */

	/* Resets */
//	gsc_ग_लिखोl(0xFFFFFFFF, base+0x1000); /* HIL */
//	gsc_ग_लिखोl(0xFFFFFFFF, base+0x2000); /* RS232-B on Wax */
पूर्ण

अटल पूर्णांक __init wax_init_chip(काष्ठा parisc_device *dev)
अणु
	काष्ठा gsc_asic *wax;
	काष्ठा parisc_device *parent;
	काष्ठा gsc_irq gsc_irq;
	पूर्णांक ret;

	wax = kzalloc(माप(*wax), GFP_KERNEL);
	अगर (!wax)
		वापस -ENOMEM;

	wax->name = "wax";
	wax->hpa = dev->hpa.start;

	wax->version = 0;   /* gsc_पढ़ोb(wax->hpa+WAX_VER); */
	prपूर्णांकk(KERN_INFO "%s at 0x%lx found.\n", wax->name, wax->hpa);

	/* Stop wax hissing क्रम a bit */
	wax_init_irq(wax);

	/* the IRQ wax should use */
	dev->irq = gsc_claim_irq(&gsc_irq, WAX_GSC_IRQ);
	अगर (dev->irq < 0) अणु
		prपूर्णांकk(KERN_ERR "%s(): cannot get GSC irq\n",
				__func__);
		kमुक्त(wax);
		वापस -EBUSY;
	पूर्ण

	wax->eim = ((u32) gsc_irq.txn_addr) | gsc_irq.txn_data;

	ret = request_irq(gsc_irq.irq, gsc_asic_पूर्णांकr, 0, "wax", wax);
	अगर (ret < 0) अणु
		kमुक्त(wax);
		वापस ret;
	पूर्ण

	/* enable IRQ's क्रम devices below WAX */
	gsc_ग_लिखोl(wax->eim, wax->hpa + OFFSET_IAR);

	/* Done init'ing, रेजिस्टर this driver */
	ret = gsc_common_setup(dev, wax);
	अगर (ret) अणु
		kमुक्त(wax);
		वापस ret;
	पूर्ण

	gsc_fixup_irqs(dev, wax, wax_choose_irq);
	/* On 715-class machines, Wax EISA is a sibling of Wax, not a child. */
	parent = parisc_parent(dev);
	अगर (parent->id.hw_type != HPHW_IOA) अणु
		gsc_fixup_irqs(parent, wax, wax_choose_irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id wax_tbl[] __initस्थिर = अणु
  	अणु HPHW_BA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0008e पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, wax_tbl);

काष्ठा parisc_driver wax_driver __refdata = अणु
	.name =		"wax",
	.id_table =	wax_tbl,
	.probe =	wax_init_chip,
पूर्ण;
