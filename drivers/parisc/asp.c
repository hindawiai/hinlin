<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	ASP Device Driver
 *
 *	(c) Copyright 2000 The Puffin Group Inc.
 *
 *	by Helge Deller <deller@gmx.de>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/led.h>

#समावेश "gsc.h"

#घोषणा ASP_GSC_IRQ	3		/* hardcoded पूर्णांकerrupt क्रम GSC */

#घोषणा ASP_VER_OFFSET 	0x20		/* offset of ASP version */

#घोषणा ASP_LED_ADDR	0xf0800020

#घोषणा VIPER_INT_WORD  0xFFFBF088      /* addr of viper पूर्णांकerrupt word */

अटल काष्ठा gsc_asic asp;

अटल व्योम asp_choose_irq(काष्ठा parisc_device *dev, व्योम *ctrl)
अणु
	पूर्णांक irq;

	चयन (dev->id.sversion) अणु
	हाल 0x71:	irq =  9; अवरोध; /* SCSI */
	हाल 0x72:	irq =  8; अवरोध; /* LAN */
	हाल 0x73:	irq =  1; अवरोध; /* HIL */
	हाल 0x74:	irq =  7; अवरोध; /* Centronics */
	हाल 0x75:	irq = (dev->hw_path == 4) ? 5 : 6; अवरोध; /* RS232 */
	हाल 0x76:	irq = 10; अवरोध; /* EISA BA */
	हाल 0x77:	irq = 11; अवरोध; /* Graphics1 */
	हाल 0x7a:	irq = 13; अवरोध; /* Audio (Bushmaster) */
	हाल 0x7b:	irq = 13; अवरोध; /* Audio (Scorpio) */
	हाल 0x7c:	irq =  3; अवरोध; /* FW SCSI */
	हाल 0x7d:	irq =  4; अवरोध; /* FDDI */
	हाल 0x7f:	irq = 13; अवरोध; /* Audio (Outfield) */
	शेष:	वापस;		 /* Unknown */
	पूर्ण

	gsc_asic_assign_irq(ctrl, irq, &dev->irq);

	चयन (dev->id.sversion) अणु
	हाल 0x73:	irq =  2; अवरोध; /* i8042 High-priority */
	हाल 0x76:	irq =  0; अवरोध; /* EISA BA */
	शेष:	वापस;		 /* Other */
	पूर्ण

	gsc_asic_assign_irq(ctrl, irq, &dev->aux_irq);
पूर्ण

/* There are two रेजिस्टर ranges we're पूर्णांकerested in.  Interrupt /
 * Status / LED are at 0xf080xxxx and Asp special रेजिस्टरs are at
 * 0xf082fxxx.  PDC only tells us that Asp is at 0xf082f000, so क्रम
 * the purposes of पूर्णांकerrupt handling, we have to tell other bits of
 * the kernel to look at the other रेजिस्टरs.
 */
#घोषणा ASP_INTERRUPT_ADDR 0xf0800000

अटल पूर्णांक __init asp_init_chip(काष्ठा parisc_device *dev)
अणु
	काष्ठा gsc_irq gsc_irq;
	पूर्णांक ret;

	asp.version = gsc_पढ़ोb(dev->hpa.start + ASP_VER_OFFSET) & 0xf;
	asp.name = (asp.version == 1) ? "Asp" : "Cutoff";
	asp.hpa = ASP_INTERRUPT_ADDR;

	prपूर्णांकk(KERN_INFO "%s version %d at 0x%lx found.\n", 
		asp.name, asp.version, (अचिन्हित दीर्घ)dev->hpa.start);

	/* the IRQ ASP should use */
	ret = -EBUSY;
	dev->irq = gsc_claim_irq(&gsc_irq, ASP_GSC_IRQ);
	अगर (dev->irq < 0) अणु
		prपूर्णांकk(KERN_ERR "%s(): cannot get GSC irq\n", __func__);
		जाओ out;
	पूर्ण

	asp.eim = ((u32) gsc_irq.txn_addr) | gsc_irq.txn_data;

	ret = request_irq(gsc_irq.irq, gsc_asic_पूर्णांकr, 0, "asp", &asp);
	अगर (ret < 0)
		जाओ out;

	/* Program VIPER to पूर्णांकerrupt on the ASP irq */
	gsc_ग_लिखोl((1 << (31 - ASP_GSC_IRQ)),VIPER_INT_WORD);

	/* Done init'ing, रेजिस्टर this driver */
	ret = gsc_common_setup(dev, &asp);
	अगर (ret)
		जाओ out;

	gsc_fixup_irqs(dev, &asp, asp_choose_irq);
	/* Mongoose is a sibling of Asp, not a child... */
	gsc_fixup_irqs(parisc_parent(dev), &asp, asp_choose_irq);

	/* initialize the chassis LEDs */ 
#अगर_घोषित CONFIG_CHASSIS_LCD_LED	
	रेजिस्टर_led_driver(DISPLAY_MODEL_OLD_ASP, LED_CMD_REG_NONE, 
		    ASP_LED_ADDR);
#पूर्ण_अगर

 out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id asp_tbl[] __initस्थिर = अणु
	अणु HPHW_BA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00070 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

काष्ठा parisc_driver asp_driver __refdata = अणु
	.name =		"asp",
	.id_table =	asp_tbl,
	.probe =	asp_init_chip,
पूर्ण;
