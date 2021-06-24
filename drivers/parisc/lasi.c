<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	LASI Device Driver
 *
 *	(c) Copyright 1999 Red Hat Software
 *	Portions (c) Copyright 1999 The Puffin Group Inc.
 *	Portions (c) Copyright 1999 Hewlett-Packard
 *
 *	by Alan Cox <alan@redhat.com> and 
 * 	   Alex deVries <alex@onefishtwo.ca>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/led.h>

#समावेश "gsc.h"


#घोषणा LASI_VER	0xC008	/* LASI Version */

#घोषणा LASI_IO_CONF	0x7FFFE	/* LASI primary configuration रेजिस्टर */
#घोषणा LASI_IO_CONF2	0x7FFFF	/* LASI secondary configuration रेजिस्टर */

अटल व्योम lasi_choose_irq(काष्ठा parisc_device *dev, व्योम *ctrl)
अणु
	पूर्णांक irq;

	चयन (dev->id.sversion) अणु
		हाल 0x74:	irq =  7; अवरोध; /* Centronics */
		हाल 0x7B:	irq = 13; अवरोध; /* Audio */
		हाल 0x81:	irq = 14; अवरोध; /* Lasi itself */
		हाल 0x82:	irq =  9; अवरोध; /* SCSI */
		हाल 0x83:	irq = 20; अवरोध; /* Floppy */
		हाल 0x84:	irq = 26; अवरोध; /* PS/2 Keyboard */
		हाल 0x87:	irq = 18; अवरोध; /* ISDN */
		हाल 0x8A:	irq =  8; अवरोध; /* LAN */
		हाल 0x8C:	irq =  5; अवरोध; /* RS232 */
		हाल 0x8D:	irq = (dev->hw_path == 13) ? 16 : 17; अवरोध;
						 /* Telephone */
		शेष: 	वापस;		 /* unknown */
	पूर्ण

	gsc_asic_assign_irq(ctrl, irq, &dev->irq);
पूर्ण

अटल व्योम __init
lasi_init_irq(काष्ठा gsc_asic *this_lasi)
अणु
	अचिन्हित दीर्घ lasi_base = this_lasi->hpa;

	/* Stop LASI barking क्रम a bit */
	gsc_ग_लिखोl(0x00000000, lasi_base+OFFSET_IMR);

	/* clear pending पूर्णांकerrupts */
	gsc_पढ़ोl(lasi_base+OFFSET_IRR);

	/* We're not really convinced we want to reset the onboard
         * devices. Firmware करोes it क्रम us...
	 */

	/* Resets */
	/* gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0x2000);*/	/* Parallel */
	अगर(pdc_add_valid(lasi_base+0x4004) == PDC_OK)
		gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0x4004);	/* Audio */
	/* gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0x5000);*/	/* Serial */ 
	/* gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0x6000);*/	/* SCSI */
	gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0x7000);	/* LAN */
	gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0x8000);	/* Keyboard */
	gsc_ग_लिखोl(0xFFFFFFFF, lasi_base+0xA000);	/* FDC */
	
	/* Ok we hit it on the head with a hammer, our Dog is now
	** comatose and muzzled.  Devices will now unmask LASI
	** पूर्णांकerrupts as they are रेजिस्टरed as irq's in the LASI range.
	*/
	/* XXX: I thought it was `awks that got `it on the `ead with an
	 * `ammer.  -- willy
	 */
पूर्ण


/*
   ** lasi_led_init()
   ** 
   ** lasi_led_init() initializes the LED controller on the LASI.
   **
   ** Since Mirage and Electra machines use a dअगरferent LED
   ** address रेजिस्टर, we need to check क्रम these machines 
   ** explicitly.
 */

#अगर_अघोषित CONFIG_CHASSIS_LCD_LED

#घोषणा lasi_led_init(x)	/* nothing */

#अन्यथा

अटल व्योम __init lasi_led_init(अचिन्हित दीर्घ lasi_hpa)
अणु
	अचिन्हित दीर्घ datareg;

	चयन (CPU_HVERSION) अणु
	/* Gecko machines have only one single LED, which can be permanently 
	   turned on by writing a zero पूर्णांकo the घातer control रेजिस्टर. */ 
	हाल 0x600:		/* Gecko (712/60) */
	हाल 0x601:		/* Gecko (712/80) */
	हाल 0x602:		/* Gecko (712/100) */
	हाल 0x603:		/* Anole 64 (743/64) */
	हाल 0x604:		/* Anole 100 (743/100) */
	हाल 0x605:		/* Gecko (712/120) */
		datareg = lasi_hpa + 0x0000C000;
		gsc_ग_लिखोb(0, datareg);
		वापस; /* no need to रेजिस्टर the LED पूर्णांकerrupt-function */  

	/* Mirage and Electra machines need special offsets */
	हाल 0x60A:		/* Mirage Jr (715/64) */
	हाल 0x60B:		/* Mirage 100 */
	हाल 0x60C:		/* Mirage 100+ */
	हाल 0x60D:		/* Electra 100 */
	हाल 0x60E:		/* Electra 120 */
		datareg = lasi_hpa - 0x00020000;
		अवरोध;

	शेष:
		datareg = lasi_hpa + 0x0000C000;
		अवरोध;
	पूर्ण

	रेजिस्टर_led_driver(DISPLAY_MODEL_LASI, LED_CMD_REG_NONE, datareg);
पूर्ण
#पूर्ण_अगर

/*
 * lasi_घातer_off
 *
 * Function क्रम lasi to turn off the घातer.  This is accomplished by setting a
 * 1 to PWR_ON_L in the Power Control Register
 * 
 */

अटल अचिन्हित दीर्घ lasi_घातer_off_hpa __पढ़ो_mostly;

अटल व्योम lasi_घातer_off(व्योम)
अणु
	अचिन्हित दीर्घ datareg;

	/* calculate addr of the Power Control Register */
	datareg = lasi_घातer_off_hpa + 0x0000C000;

	/* Power करोwn the machine */
	gsc_ग_लिखोl(0x02, datareg);
पूर्ण

अटल पूर्णांक __init lasi_init_chip(काष्ठा parisc_device *dev)
अणु
	बाह्य व्योम (*chassis_घातer_off)(व्योम);
	काष्ठा gsc_asic *lasi;
	काष्ठा gsc_irq gsc_irq;
	पूर्णांक ret;

	lasi = kzalloc(माप(*lasi), GFP_KERNEL);
	अगर (!lasi)
		वापस -ENOMEM;

	lasi->name = "Lasi";
	lasi->hpa = dev->hpa.start;

	/* Check the 4-bit (yes, only 4) version रेजिस्टर */
	lasi->version = gsc_पढ़ोl(lasi->hpa + LASI_VER) & 0xf;
	prपूर्णांकk(KERN_INFO "%s version %d at 0x%lx found.\n",
		lasi->name, lasi->version, lasi->hpa);

	/* initialize the chassis LEDs really early */ 
	lasi_led_init(lasi->hpa);

	/* Stop LASI barking क्रम a bit */
	lasi_init_irq(lasi);

	/* the IRQ lasi should use */
	dev->irq = gsc_alloc_irq(&gsc_irq);
	अगर (dev->irq < 0) अणु
		prपूर्णांकk(KERN_ERR "%s(): cannot get GSC irq\n",
				__func__);
		kमुक्त(lasi);
		वापस -EBUSY;
	पूर्ण

	lasi->eim = ((u32) gsc_irq.txn_addr) | gsc_irq.txn_data;

	ret = request_irq(gsc_irq.irq, gsc_asic_पूर्णांकr, 0, "lasi", lasi);
	अगर (ret < 0) अणु
		kमुक्त(lasi);
		वापस ret;
	पूर्ण

	/* enable IRQ's क्रम devices below LASI */
	gsc_ग_लिखोl(lasi->eim, lasi->hpa + OFFSET_IAR);

	/* Done init'ing, रेजिस्टर this driver */
	ret = gsc_common_setup(dev, lasi);
	अगर (ret) अणु
		kमुक्त(lasi);
		वापस ret;
	पूर्ण    

	gsc_fixup_irqs(dev, lasi, lasi_choose_irq);

	/* initialize the घातer off function */
	/* FIXME: Record the LASI HPA क्रम the घातer off function.  This should
	 * ensure that only the first LASI (the one controlling the घातer off)
	 * should set the HPA here */
	lasi_घातer_off_hpa = lasi->hpa;
	chassis_घातer_off = lasi_घातer_off;
	
	वापस ret;
पूर्ण

अटल काष्ठा parisc_device_id lasi_tbl[] __initdata = अणु
	अणु HPHW_BA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00081 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

काष्ठा parisc_driver lasi_driver __refdata = अणु
	.name =		"lasi",
	.id_table =	lasi_tbl,
	.probe =	lasi_init_chip,
पूर्ण;
