<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ------------------------------------------------------------------------- */
/* i2c-elektor.c i2c-hw access क्रम PCF8584 style isa bus adaptes             */
/* ------------------------------------------------------------------------- */
/*   Copyright (C) 1995-97 Simon G. Vogl
                   1998-99 Hans Berglund

 */
/* ------------------------------------------------------------------------- */

/* With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi> and even
   Froकरो Looijaard <froकरोl@dds.nl> */

/* Partially reग_लिखोn by Oleg I. Vकरोvikin क्रम mmapped support of
   क्रम Alpha Processor Inc. UP-2000(+) boards */

#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>

#समावेश <linux/isa.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-pcf.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>

#समावेश "../algos/i2c-algo-pcf.h"

#घोषणा DEFAULT_BASE 0x330

अटल पूर्णांक base;
अटल u8 __iomem *base_iomem;

अटल पूर्णांक irq;
अटल पूर्णांक घड़ी  = 0x1c;
अटल पूर्णांक own    = 0x55;
अटल पूर्णांक mmapped;

/* vकरोvikin: हटाओd अटल काष्ठा i2c_pcf_isa gpi; code -
  this module in real supports only one device, due to missing arguments
  in some functions, called from the algo-pcf module. Someबार it's
  need to be reग_लिखोn - but क्रम now just हटाओ this क्रम simpler पढ़ोing */

अटल रुको_queue_head_t pcf_रुको;
अटल पूर्णांक pcf_pending;
अटल DEFINE_SPINLOCK(lock);

अटल काष्ठा i2c_adapter pcf_isa_ops;

/* ----- local functions ----------------------------------------------	*/

अटल व्योम pcf_isa_setbyte(व्योम *data, पूर्णांक ctl, पूर्णांक val)
अणु
	u8 __iomem *address = ctl ? (base_iomem + 1) : base_iomem;

	/* enable irq अगर any specअगरied क्रम serial operation */
	अगर (ctl && irq && (val & I2C_PCF_ESO)) अणु
		val |= I2C_PCF_ENI;
	पूर्ण

	pr_debug("%s: Write %p 0x%02X\n", pcf_isa_ops.name, address, val);
	ioग_लिखो8(val, address);
#अगर_घोषित __alpha__
	/* API UP2000 needs some hardware fudging to make the ग_लिखो stick */
	ioग_लिखो8(val, address);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक pcf_isa_getbyte(व्योम *data, पूर्णांक ctl)
अणु
	u8 __iomem *address = ctl ? (base_iomem + 1) : base_iomem;
	पूर्णांक val = ioपढ़ो8(address);

	pr_debug("%s: Read %p 0x%02X\n", pcf_isa_ops.name, address, val);
	वापस (val);
पूर्ण

अटल पूर्णांक pcf_isa_getown(व्योम *data)
अणु
	वापस (own);
पूर्ण


अटल पूर्णांक pcf_isa_अ_लोlock(व्योम *data)
अणु
	वापस (घड़ी);
पूर्ण

अटल व्योम pcf_isa_रुकोक्रमpin(व्योम *data)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक समयout = 2;
	अचिन्हित दीर्घ flags;

	अगर (irq > 0) अणु
		spin_lock_irqsave(&lock, flags);
		अगर (pcf_pending == 0) अणु
			spin_unlock_irqrestore(&lock, flags);
			prepare_to_रुको(&pcf_रुको, &रुको, TASK_INTERRUPTIBLE);
			अगर (schedule_समयout(समयout*HZ)) अणु
				spin_lock_irqsave(&lock, flags);
				अगर (pcf_pending == 1) अणु
					pcf_pending = 0;
				पूर्ण
				spin_unlock_irqrestore(&lock, flags);
			पूर्ण
			finish_रुको(&pcf_रुको, &रुको);
		पूर्ण अन्यथा अणु
			pcf_pending = 0;
			spin_unlock_irqrestore(&lock, flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		udelay(100);
	पूर्ण
पूर्ण


अटल irqवापस_t pcf_isa_handler(पूर्णांक this_irq, व्योम *dev_id) अणु
	spin_lock(&lock);
	pcf_pending = 1;
	spin_unlock(&lock);
	wake_up_पूर्णांकerruptible(&pcf_रुको);
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक pcf_isa_init(व्योम)
अणु
	अगर (!mmapped) अणु
		अगर (!request_region(base, 2, pcf_isa_ops.name)) अणु
			prपूर्णांकk(KERN_ERR "%s: requested I/O region (%#x:2) is "
			       "in use\n", pcf_isa_ops.name, base);
			वापस -ENODEV;
		पूर्ण
		base_iomem = ioport_map(base, 2);
		अगर (!base_iomem) अणु
			prपूर्णांकk(KERN_ERR "%s: remap of I/O region %#x failed\n",
			       pcf_isa_ops.name, base);
			release_region(base, 2);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!request_mem_region(base, 2, pcf_isa_ops.name)) अणु
			prपूर्णांकk(KERN_ERR "%s: requested memory region (%#x:2) "
			       "is in use\n", pcf_isa_ops.name, base);
			वापस -ENODEV;
		पूर्ण
		base_iomem = ioremap(base, 2);
		अगर (base_iomem == शून्य) अणु
			prपूर्णांकk(KERN_ERR "%s: remap of memory region %#x "
			       "failed\n", pcf_isa_ops.name, base);
			release_mem_region(base, 2);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	pr_debug("%s: registers %#x remapped to %p\n", pcf_isa_ops.name, base,
		 base_iomem);

	अगर (irq > 0) अणु
		अगर (request_irq(irq, pcf_isa_handler, 0, pcf_isa_ops.name,
				शून्य) < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: Request irq%d failed\n",
			       pcf_isa_ops.name, irq);
			irq = 0;
		पूर्ण अन्यथा
			enable_irq(irq);
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------
 * Encapsulate the above functions in the correct operations काष्ठाure.
 * This is only करोne when more than one hardware adapter is supported.
 */
अटल काष्ठा i2c_algo_pcf_data pcf_isa_data = अणु
	.setpcf	    = pcf_isa_setbyte,
	.getpcf	    = pcf_isa_getbyte,
	.getown	    = pcf_isa_getown,
	.अ_लोlock   = pcf_isa_अ_लोlock,
	.रुकोक्रमpin = pcf_isa_रुकोक्रमpin,
पूर्ण;

अटल काष्ठा i2c_adapter pcf_isa_ops = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo_data	= &pcf_isa_data,
	.name		= "i2c-elektor",
पूर्ण;

अटल पूर्णांक elektor_match(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
#अगर_घोषित __alpha__
	/* check to see we have memory mapped PCF8584 connected to the
	Cypress cy82c693 PCI-ISA bridge as on UP2000 board */
	अगर (base == 0) अणु
		काष्ठा pci_dev *cy693_dev;

		cy693_dev = pci_get_device(PCI_VENDOR_ID_CONTAQ,
					   PCI_DEVICE_ID_CONTAQ_82C693, शून्य);
		अगर (cy693_dev) अणु
			अचिन्हित अक्षर config;
			/* yeap, we've found cypress, let's check config */
			अगर (!pci_पढ़ो_config_byte(cy693_dev, 0x47, &config)) अणु

				dev_dbg(dev, "found cy82c693, config "
					"register 0x47 = 0x%02x\n", config);

				/* UP2000 board has this रेजिस्टर set to 0xe1,
				   but the most signअगरicant bit as seems can be
				   reset during the proper initialisation
				   sequence अगर guys from API decides to करो that
				   (so, we can even enable Tsunami Pchip
				   winकरोw क्रम the upper 1 Gb) */

				/* so just check क्रम ROMCS at 0xe0000,
				   ROMCS enabled क्रम ग_लिखोs
				   and बाह्यal XD Bus buffer in use. */
				अगर ((config & 0x7f) == 0x61) अणु
					/* seems to be UP2000 like board */
					base = 0xe0000;
					mmapped = 1;
					/* UP2000 drives ISA with
					   8.25 MHz (PCI/4) घड़ी
					   (this can be पढ़ो from cypress) */
					घड़ी = I2C_PCF_CLK | I2C_PCF_TRNS90;
					dev_info(dev, "found API UP2000 like "
						 "board, will probe PCF8584 "
						 "later\n");
				पूर्ण
			पूर्ण
			pci_dev_put(cy693_dev);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* sanity checks क्रम mmapped I/O */
	अगर (mmapped && base < 0xc8000) अणु
		dev_err(dev, "incorrect base address (%#x) specified "
		       "for mmapped I/O\n", base);
		वापस 0;
	पूर्ण

	अगर (base == 0) अणु
		base = DEFAULT_BASE;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक elektor_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	init_रुकोqueue_head(&pcf_रुको);
	अगर (pcf_isa_init())
		वापस -ENODEV;
	pcf_isa_ops.dev.parent = dev;
	अगर (i2c_pcf_add_bus(&pcf_isa_ops) < 0)
		जाओ fail;

	dev_info(dev, "found device at %#x\n", base);

	वापस 0;

 fail:
	अगर (irq > 0) अणु
		disable_irq(irq);
		मुक्त_irq(irq, शून्य);
	पूर्ण

	अगर (!mmapped) अणु
		ioport_unmap(base_iomem);
		release_region(base, 2);
	पूर्ण अन्यथा अणु
		iounmap(base_iomem);
		release_mem_region(base, 2);
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम elektor_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	i2c_del_adapter(&pcf_isa_ops);

	अगर (irq > 0) अणु
		disable_irq(irq);
		मुक्त_irq(irq, शून्य);
	पूर्ण

	अगर (!mmapped) अणु
		ioport_unmap(base_iomem);
		release_region(base, 2);
	पूर्ण अन्यथा अणु
		iounmap(base_iomem);
		release_mem_region(base, 2);
	पूर्ण
पूर्ण

अटल काष्ठा isa_driver i2c_elektor_driver = अणु
	.match		= elektor_match,
	.probe		= elektor_probe,
	.हटाओ		= elektor_हटाओ,
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "i2c-elektor",
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("Hans Berglund <hb@spacetec.no>");
MODULE_DESCRIPTION("I2C-Bus adapter routines for PCF8584 ISA bus adapter");
MODULE_LICENSE("GPL");

module_param_hw(base, पूर्णांक, ioport_or_iomem, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param(घड़ी, पूर्णांक, 0);
module_param(own, पूर्णांक, 0);
module_param_hw(mmapped, पूर्णांक, other, 0);
module_isa_driver(i2c_elektor_driver, 1);
