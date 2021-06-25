<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम CC770 and AN82527 CAN controllers on the legacy ISA bus
 *
 * Copyright (C) 2009, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

/*
 * Bosch CC770 and Intel AN82527 CAN controllers on the ISA or PC-104 bus.
 * The I/O port or memory address and the IRQ number must be specअगरied via
 * module parameters:
 *
 *   insmod cc770_isa.ko port=0x310,0x380 irq=7,11
 *
 * क्रम ISA devices using I/O ports or:
 *
 *   insmod cc770_isa.ko mem=0xd1000,0xd1000 irq=7,11
 *
 * क्रम memory mapped ISA devices.
 *
 * Indirect access via address and data port is supported as well:
 *
 *   insmod cc770_isa.ko port=0x310,0x380 indirect=1 irq=7,11
 *
 * Furthermore, the following mode parameter can be defined:
 *
 *   clk: External oscillator घड़ी frequency (शेष=16000000 [16 MHz])
 *   cir: CPU पूर्णांकerface रेजिस्टर (शेष=0x40 [DSC])
 *   bcr: Bus configuration रेजिस्टर (शेष=0x40 [CBY])
 *   cor: Clockout रेजिस्टर (शेष=0x00)
 *
 * Note: क्रम clk, cir, bcr and cor, the first argument re-defines the
 * शेष क्रम all other devices, e.g.:
 *
 *   insmod cc770_isa.ko mem=0xd1000,0xd1000 irq=7,11 clk=24000000
 *
 * is equivalent to
 *
 *   insmod cc770_isa.ko mem=0xd1000,0xd1000 irq=7,11 clk=24000000,24000000
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/platक्रमm/cc770.h>

#समावेश "cc770.h"

#घोषणा MAXDEV 8

MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_DESCRIPTION("Socket-CAN driver for CC770 on the ISA bus");
MODULE_LICENSE("GPL v2");

#घोषणा CLK_DEFAULT	16000000	/* 16 MHz */
#घोषणा COR_DEFAULT	0x00
#घोषणा BCR_DEFAULT	BUSCFG_CBY

अटल अचिन्हित दीर्घ port[MAXDEV];
अटल अचिन्हित दीर्घ mem[MAXDEV];
अटल पूर्णांक irq[MAXDEV];
अटल पूर्णांक clk[MAXDEV];
अटल u8 cir[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = 0xffपूर्ण;
अटल u8 cor[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = 0xffपूर्ण;
अटल u8 bcr[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = 0xffपूर्ण;
अटल पूर्णांक indirect[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = -1पूर्ण;

module_param_hw_array(port, uदीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "I/O port number");

module_param_hw_array(mem, uदीर्घ, iomem, शून्य, 0444);
MODULE_PARM_DESC(mem, "I/O memory address");

module_param_hw_array(indirect, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(indirect, "Indirect access via address and data port");

module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ number");

module_param_array(clk, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(clk, "External oscillator clock frequency "
		 "(default=16000000 [16 MHz])");

module_param_array(cir, byte, शून्य, 0444);
MODULE_PARM_DESC(cir, "CPU interface register (default=0x40 [DSC])");

module_param_array(cor, byte, शून्य, 0444);
MODULE_PARM_DESC(cor, "Clockout register (default=0x00)");

module_param_array(bcr, byte, शून्य, 0444);
MODULE_PARM_DESC(bcr, "Bus configuration register (default=0x40 [CBY])");

#घोषणा CC770_IOSIZE          0x20
#घोषणा CC770_IOSIZE_INसूचीECT 0x02

/* Spinlock क्रम cc770_isa_port_ग_लिखो_reg_indirect
 * and cc770_isa_port_पढ़ो_reg_indirect
 */
अटल DEFINE_SPINLOCK(cc770_isa_port_lock);

अटल काष्ठा platक्रमm_device *cc770_isa_devs[MAXDEV];

अटल u8 cc770_isa_mem_पढ़ो_reg(स्थिर काष्ठा cc770_priv *priv, पूर्णांक reg)
अणु
	वापस पढ़ोb(priv->reg_base + reg);
पूर्ण

अटल व्योम cc770_isa_mem_ग_लिखो_reg(स्थिर काष्ठा cc770_priv *priv,
				      पूर्णांक reg, u8 val)
अणु
	ग_लिखोb(val, priv->reg_base + reg);
पूर्ण

अटल u8 cc770_isa_port_पढ़ो_reg(स्थिर काष्ठा cc770_priv *priv, पूर्णांक reg)
अणु
	वापस inb((अचिन्हित दीर्घ)priv->reg_base + reg);
पूर्ण

अटल व्योम cc770_isa_port_ग_लिखो_reg(स्थिर काष्ठा cc770_priv *priv,
				       पूर्णांक reg, u8 val)
अणु
	outb(val, (अचिन्हित दीर्घ)priv->reg_base + reg);
पूर्ण

अटल u8 cc770_isa_port_पढ़ो_reg_indirect(स्थिर काष्ठा cc770_priv *priv,
					     पूर्णांक reg)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)priv->reg_base;
	अचिन्हित दीर्घ flags;
	u8 val;

	spin_lock_irqsave(&cc770_isa_port_lock, flags);
	outb(reg, base);
	val = inb(base + 1);
	spin_unlock_irqrestore(&cc770_isa_port_lock, flags);

	वापस val;
पूर्ण

अटल व्योम cc770_isa_port_ग_लिखो_reg_indirect(स्थिर काष्ठा cc770_priv *priv,
						पूर्णांक reg, u8 val)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)priv->reg_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cc770_isa_port_lock, flags);
	outb(reg, base);
	outb(val, base + 1);
	spin_unlock_irqrestore(&cc770_isa_port_lock, flags);
पूर्ण

अटल पूर्णांक cc770_isa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा cc770_priv *priv;
	व्योम __iomem *base = शून्य;
	पूर्णांक iosize = CC770_IOSIZE;
	पूर्णांक idx = pdev->id;
	पूर्णांक err;
	u32 clkपंचांगp;

	dev_dbg(&pdev->dev, "probing idx=%d: port=%#lx, mem=%#lx, irq=%d\n",
		idx, port[idx], mem[idx], irq[idx]);
	अगर (mem[idx]) अणु
		अगर (!request_mem_region(mem[idx], iosize, KBUILD_MODNAME)) अणु
			err = -EBUSY;
			जाओ निकास;
		पूर्ण
		base = ioremap(mem[idx], iosize);
		अगर (!base) अणु
			err = -ENOMEM;
			जाओ निकास_release;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (indirect[idx] > 0 ||
		    (indirect[idx] == -1 && indirect[0] > 0))
			iosize = CC770_IOSIZE_INसूचीECT;
		अगर (!request_region(port[idx], iosize, KBUILD_MODNAME)) अणु
			err = -EBUSY;
			जाओ निकास;
		पूर्ण
	पूर्ण

	dev = alloc_cc770dev(0);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ निकास_unmap;
	पूर्ण
	priv = netdev_priv(dev);

	dev->irq = irq[idx];
	priv->irq_flags = IRQF_SHARED;
	अगर (mem[idx]) अणु
		priv->reg_base = base;
		dev->base_addr = mem[idx];
		priv->पढ़ो_reg = cc770_isa_mem_पढ़ो_reg;
		priv->ग_लिखो_reg = cc770_isa_mem_ग_लिखो_reg;
	पूर्ण अन्यथा अणु
		priv->reg_base = (व्योम __iomem *)port[idx];
		dev->base_addr = port[idx];

		अगर (iosize == CC770_IOSIZE_INसूचीECT) अणु
			priv->पढ़ो_reg = cc770_isa_port_पढ़ो_reg_indirect;
			priv->ग_लिखो_reg = cc770_isa_port_ग_लिखो_reg_indirect;
		पूर्ण अन्यथा अणु
			priv->पढ़ो_reg = cc770_isa_port_पढ़ो_reg;
			priv->ग_लिखो_reg = cc770_isa_port_ग_लिखो_reg;
		पूर्ण
	पूर्ण

	अगर (clk[idx])
		clkपंचांगp = clk[idx];
	अन्यथा अगर (clk[0])
		clkपंचांगp = clk[0];
	अन्यथा
		clkपंचांगp = CLK_DEFAULT;
	priv->can.घड़ी.freq = clkपंचांगp;

	अगर (cir[idx] != 0xff) अणु
		priv->cpu_पूर्णांकerface = cir[idx];
	पूर्ण अन्यथा अगर (cir[0] != 0xff) अणु
		priv->cpu_पूर्णांकerface = cir[0];
	पूर्ण अन्यथा अणु
		/* The प्रणाली घड़ी may not exceed 10 MHz */
		अगर (clkपंचांगp > 10000000) अणु
			priv->cpu_पूर्णांकerface |= CPUIF_DSC;
			clkपंचांगp /= 2;
		पूर्ण
		/* The memory घड़ी may not exceed 8 MHz */
		अगर (clkपंचांगp > 8000000)
			priv->cpu_पूर्णांकerface |= CPUIF_DMC;
	पूर्ण

	अगर (priv->cpu_पूर्णांकerface & CPUIF_DSC)
		priv->can.घड़ी.freq /= 2;

	अगर (bcr[idx] != 0xff)
		priv->bus_config = bcr[idx];
	अन्यथा अगर (bcr[0] != 0xff)
		priv->bus_config = bcr[0];
	अन्यथा
		priv->bus_config = BCR_DEFAULT;

	अगर (cor[idx] != 0xff)
		priv->clkout = cor[idx];
	अन्यथा अगर (cor[0] != 0xff)
		priv->clkout = cor[0];
	अन्यथा
		priv->clkout = COR_DEFAULT;

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = रेजिस्टर_cc770dev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"couldn't register device (err=%d)\n", err);
		जाओ निकास_unmap;
	पूर्ण

	dev_info(&pdev->dev, "device registered (reg_base=0x%p, irq=%d)\n",
		 priv->reg_base, dev->irq);
	वापस 0;

 निकास_unmap:
	अगर (mem[idx])
		iounmap(base);
 निकास_release:
	अगर (mem[idx])
		release_mem_region(mem[idx], iosize);
	अन्यथा
		release_region(port[idx], iosize);
 निकास:
	वापस err;
पूर्ण

अटल पूर्णांक cc770_isa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	पूर्णांक idx = pdev->id;

	unरेजिस्टर_cc770dev(dev);

	अगर (mem[idx]) अणु
		iounmap(priv->reg_base);
		release_mem_region(mem[idx], CC770_IOSIZE);
	पूर्ण अन्यथा अणु
		अगर (priv->पढ़ो_reg == cc770_isa_port_पढ़ो_reg_indirect)
			release_region(port[idx], CC770_IOSIZE_INसूचीECT);
		अन्यथा
			release_region(port[idx], CC770_IOSIZE);
	पूर्ण
	मुक्त_cc770dev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cc770_isa_driver = अणु
	.probe = cc770_isa_probe,
	.हटाओ = cc770_isa_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cc770_isa_init(व्योम)
अणु
	पूर्णांक idx, err;

	क्रम (idx = 0; idx < ARRAY_SIZE(cc770_isa_devs); idx++) अणु
		अगर ((port[idx] || mem[idx]) && irq[idx]) अणु
			cc770_isa_devs[idx] =
				platक्रमm_device_alloc(KBUILD_MODNAME, idx);
			अगर (!cc770_isa_devs[idx]) अणु
				err = -ENOMEM;
				जाओ निकास_मुक्त_devices;
			पूर्ण
			err = platक्रमm_device_add(cc770_isa_devs[idx]);
			अगर (err) अणु
				platक्रमm_device_put(cc770_isa_devs[idx]);
				जाओ निकास_मुक्त_devices;
			पूर्ण
			pr_debug("platform device %d: port=%#lx, mem=%#lx, "
				 "irq=%d\n",
				 idx, port[idx], mem[idx], irq[idx]);
		पूर्ण अन्यथा अगर (idx == 0 || port[idx] || mem[idx]) अणु
			pr_err("insufficient parameters supplied\n");
			err = -EINVAL;
			जाओ निकास_मुक्त_devices;
		पूर्ण
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&cc770_isa_driver);
	अगर (err)
		जाओ निकास_मुक्त_devices;

	pr_info("driver for max. %d devices registered\n", MAXDEV);

	वापस 0;

निकास_मुक्त_devices:
	जबतक (--idx >= 0) अणु
		अगर (cc770_isa_devs[idx])
			platक्रमm_device_unरेजिस्टर(cc770_isa_devs[idx]);
	पूर्ण

	वापस err;
पूर्ण
module_init(cc770_isa_init);

अटल व्योम __निकास cc770_isa_निकास(व्योम)
अणु
	पूर्णांक idx;

	platक्रमm_driver_unरेजिस्टर(&cc770_isa_driver);
	क्रम (idx = 0; idx < ARRAY_SIZE(cc770_isa_devs); idx++) अणु
		अगर (cc770_isa_devs[idx])
			platक्रमm_device_unरेजिस्टर(cc770_isa_devs[idx]);
	पूर्ण
पूर्ण
module_निकास(cc770_isa_निकास);
