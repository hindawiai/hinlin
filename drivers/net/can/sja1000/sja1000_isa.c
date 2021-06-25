<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/platक्रमm/sja1000.h>

#समावेश "sja1000.h"

#घोषणा DRV_NAME "sja1000_isa"

#घोषणा MAXDEV 8

MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_DESCRIPTION("Socket-CAN driver for SJA1000 on the ISA bus");
MODULE_LICENSE("GPL v2");

#घोषणा CLK_DEFAULT	16000000	/* 16 MHz */
#घोषणा CDR_DEFAULT	(CDR_CBP | CDR_CLK_OFF)
#घोषणा OCR_DEFAULT	OCR_TX0_PUSHPULL

अटल अचिन्हित दीर्घ port[MAXDEV];
अटल अचिन्हित दीर्घ mem[MAXDEV];
अटल पूर्णांक irq[MAXDEV];
अटल पूर्णांक clk[MAXDEV];
अटल अचिन्हित अक्षर cdr[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = 0xffपूर्ण;
अटल अचिन्हित अक्षर ocr[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = 0xffपूर्ण;
अटल पूर्णांक indirect[MAXDEV] = अणु[0 ... (MAXDEV - 1)] = -1पूर्ण;
अटल spinlock_t indirect_lock[MAXDEV];  /* lock क्रम indirect access mode */

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

module_param_array(cdr, byte, शून्य, 0444);
MODULE_PARM_DESC(cdr, "Clock divider register "
		 "(default=0x48 [CDR_CBP | CDR_CLK_OFF])");

module_param_array(ocr, byte, शून्य, 0444);
MODULE_PARM_DESC(ocr, "Output control register "
		 "(default=0x18 [OCR_TX0_PUSHPULL])");

#घोषणा SJA1000_IOSIZE          0x20
#घोषणा SJA1000_IOSIZE_INसूचीECT 0x02

अटल काष्ठा platक्रमm_device *sja1000_isa_devs[MAXDEV];

अटल u8 sja1000_isa_mem_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	वापस पढ़ोb(priv->reg_base + reg);
पूर्ण

अटल व्योम sja1000_isa_mem_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
				      पूर्णांक reg, u8 val)
अणु
	ग_लिखोb(val, priv->reg_base + reg);
पूर्ण

अटल u8 sja1000_isa_port_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	वापस inb((अचिन्हित दीर्घ)priv->reg_base + reg);
पूर्ण

अटल व्योम sja1000_isa_port_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
				       पूर्णांक reg, u8 val)
अणु
	outb(val, (अचिन्हित दीर्घ)priv->reg_base + reg);
पूर्ण

अटल u8 sja1000_isa_port_पढ़ो_reg_indirect(स्थिर काष्ठा sja1000_priv *priv,
					     पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags, base = (अचिन्हित दीर्घ)priv->reg_base;
	u8 पढ़ोval;

	spin_lock_irqsave(&indirect_lock[priv->dev->dev_id], flags);
	outb(reg, base);
	पढ़ोval = inb(base + 1);
	spin_unlock_irqrestore(&indirect_lock[priv->dev->dev_id], flags);

	वापस पढ़ोval;
पूर्ण

अटल व्योम sja1000_isa_port_ग_लिखो_reg_indirect(स्थिर काष्ठा sja1000_priv *priv,
						पूर्णांक reg, u8 val)
अणु
	अचिन्हित दीर्घ flags, base = (अचिन्हित दीर्घ)priv->reg_base;

	spin_lock_irqsave(&indirect_lock[priv->dev->dev_id], flags);
	outb(reg, base);
	outb(val, base + 1);
	spin_unlock_irqrestore(&indirect_lock[priv->dev->dev_id], flags);
पूर्ण

अटल पूर्णांक sja1000_isa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा sja1000_priv *priv;
	व्योम __iomem *base = शून्य;
	पूर्णांक iosize = SJA1000_IOSIZE;
	पूर्णांक idx = pdev->id;
	पूर्णांक err;

	dev_dbg(&pdev->dev, "probing idx=%d: port=%#lx, mem=%#lx, irq=%d\n",
		idx, port[idx], mem[idx], irq[idx]);

	अगर (mem[idx]) अणु
		अगर (!request_mem_region(mem[idx], iosize, DRV_NAME)) अणु
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
			iosize = SJA1000_IOSIZE_INसूचीECT;
		अगर (!request_region(port[idx], iosize, DRV_NAME)) अणु
			err = -EBUSY;
			जाओ निकास;
		पूर्ण
	पूर्ण

	dev = alloc_sja1000dev(0);
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
		priv->पढ़ो_reg = sja1000_isa_mem_पढ़ो_reg;
		priv->ग_लिखो_reg = sja1000_isa_mem_ग_लिखो_reg;
	पूर्ण अन्यथा अणु
		priv->reg_base = (व्योम __iomem *)port[idx];
		dev->base_addr = port[idx];

		अगर (iosize == SJA1000_IOSIZE_INसूचीECT) अणु
			priv->पढ़ो_reg = sja1000_isa_port_पढ़ो_reg_indirect;
			priv->ग_लिखो_reg = sja1000_isa_port_ग_लिखो_reg_indirect;
			spin_lock_init(&indirect_lock[idx]);
		पूर्ण अन्यथा अणु
			priv->पढ़ो_reg = sja1000_isa_port_पढ़ो_reg;
			priv->ग_लिखो_reg = sja1000_isa_port_ग_लिखो_reg;
		पूर्ण
	पूर्ण

	अगर (clk[idx])
		priv->can.घड़ी.freq = clk[idx] / 2;
	अन्यथा अगर (clk[0])
		priv->can.घड़ी.freq = clk[0] / 2;
	अन्यथा
		priv->can.घड़ी.freq = CLK_DEFAULT / 2;

	अगर (ocr[idx] != 0xff)
		priv->ocr = ocr[idx];
	अन्यथा अगर (ocr[0] != 0xff)
		priv->ocr = ocr[0];
	अन्यथा
		priv->ocr = OCR_DEFAULT;

	अगर (cdr[idx] != 0xff)
		priv->cdr = cdr[idx];
	अन्यथा अगर (cdr[0] != 0xff)
		priv->cdr = cdr[0];
	अन्यथा
		priv->cdr = CDR_DEFAULT;

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->dev_id = idx;

	err = रेजिस्टर_sja1000dev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "registering %s failed (err=%d)\n",
			DRV_NAME, err);
		जाओ निकास_unmap;
	पूर्ण

	dev_info(&pdev->dev, "%s device registered (reg_base=0x%p, irq=%d)\n",
		 DRV_NAME, priv->reg_base, dev->irq);
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

अटल पूर्णांक sja1000_isa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	पूर्णांक idx = pdev->id;

	unरेजिस्टर_sja1000dev(dev);

	अगर (mem[idx]) अणु
		iounmap(priv->reg_base);
		release_mem_region(mem[idx], SJA1000_IOSIZE);
	पूर्ण अन्यथा अणु
		अगर (priv->पढ़ो_reg == sja1000_isa_port_पढ़ो_reg_indirect)
			release_region(port[idx], SJA1000_IOSIZE_INसूचीECT);
		अन्यथा
			release_region(port[idx], SJA1000_IOSIZE);
	पूर्ण
	मुक्त_sja1000dev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sja1000_isa_driver = अणु
	.probe = sja1000_isa_probe,
	.हटाओ = sja1000_isa_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sja1000_isa_init(व्योम)
अणु
	पूर्णांक idx, err;

	क्रम (idx = 0; idx < MAXDEV; idx++) अणु
		अगर ((port[idx] || mem[idx]) && irq[idx]) अणु
			sja1000_isa_devs[idx] =
				platक्रमm_device_alloc(DRV_NAME, idx);
			अगर (!sja1000_isa_devs[idx]) अणु
				err = -ENOMEM;
				जाओ निकास_मुक्त_devices;
			पूर्ण
			err = platक्रमm_device_add(sja1000_isa_devs[idx]);
			अगर (err) अणु
				platक्रमm_device_put(sja1000_isa_devs[idx]);
				जाओ निकास_मुक्त_devices;
			पूर्ण
			pr_debug("%s: platform device %d: port=%#lx, mem=%#lx, "
				 "irq=%d\n",
				 DRV_NAME, idx, port[idx], mem[idx], irq[idx]);
		पूर्ण अन्यथा अगर (idx == 0 || port[idx] || mem[idx]) अणु
				pr_err("%s: insufficient parameters supplied\n",
				       DRV_NAME);
				err = -EINVAL;
				जाओ निकास_मुक्त_devices;
		पूर्ण
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&sja1000_isa_driver);
	अगर (err)
		जाओ निकास_मुक्त_devices;

	pr_info("Legacy %s driver for max. %d devices registered\n",
		DRV_NAME, MAXDEV);

	वापस 0;

निकास_मुक्त_devices:
	जबतक (--idx >= 0) अणु
		अगर (sja1000_isa_devs[idx])
			platक्रमm_device_unरेजिस्टर(sja1000_isa_devs[idx]);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास sja1000_isa_निकास(व्योम)
अणु
	पूर्णांक idx;

	platक्रमm_driver_unरेजिस्टर(&sja1000_isa_driver);
	क्रम (idx = 0; idx < MAXDEV; idx++) अणु
		अगर (sja1000_isa_devs[idx])
			platक्रमm_device_unरेजिस्टर(sja1000_isa_devs[idx]);
	पूर्ण
पूर्ण

module_init(sja1000_isa_init);
module_निकास(sja1000_isa_निकास);
