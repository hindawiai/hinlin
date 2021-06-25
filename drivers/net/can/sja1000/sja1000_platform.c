<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 Sascha Hauer, Pengutronix
 * Copyright (C) 2007 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/platक्रमm/sja1000.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>

#समावेश "sja1000.h"

#घोषणा DRV_NAME "sja1000_platform"
#घोषणा SP_CAN_CLOCK  (16000000 / 2)

MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_DESCRIPTION("Socket-CAN driver for SJA1000 on the platform bus");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_LICENSE("GPL v2");

काष्ठा sja1000_of_data अणु
	माप_प्रकार  priv_sz;
	पूर्णांक     (*init)(काष्ठा sja1000_priv *priv, काष्ठा device_node *of);
पूर्ण;

काष्ठा technologic_priv अणु
	spinlock_t      io_lock;
पूर्ण;

अटल u8 sp_पढ़ो_reg8(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	वापस ioपढ़ो8(priv->reg_base + reg);
पूर्ण

अटल व्योम sp_ग_लिखो_reg8(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg, u8 val)
अणु
	ioग_लिखो8(val, priv->reg_base + reg);
पूर्ण

अटल u8 sp_पढ़ो_reg16(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	वापस ioपढ़ो8(priv->reg_base + reg * 2);
पूर्ण

अटल व्योम sp_ग_लिखो_reg16(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg, u8 val)
अणु
	ioग_लिखो8(val, priv->reg_base + reg * 2);
पूर्ण

अटल u8 sp_पढ़ो_reg32(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	वापस ioपढ़ो8(priv->reg_base + reg * 4);
पूर्ण

अटल व्योम sp_ग_लिखो_reg32(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg, u8 val)
अणु
	ioग_लिखो8(val, priv->reg_base + reg * 4);
पूर्ण

अटल u8 sp_technologic_पढ़ो_reg16(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	काष्ठा technologic_priv *tp = priv->priv;
	अचिन्हित दीर्घ flags;
	u8 val;

	spin_lock_irqsave(&tp->io_lock, flags);
	ioग_लिखो16(reg, priv->reg_base + 0);
	val = ioपढ़ो16(priv->reg_base + 2);
	spin_unlock_irqrestore(&tp->io_lock, flags);

	वापस val;
पूर्ण

अटल व्योम sp_technologic_ग_लिखो_reg16(स्थिर काष्ठा sja1000_priv *priv,
				       पूर्णांक reg, u8 val)
अणु
	काष्ठा technologic_priv *tp = priv->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tp->io_lock, flags);
	ioग_लिखो16(reg, priv->reg_base + 0);
	ioग_लिखो16(val, priv->reg_base + 2);
	spin_unlock_irqrestore(&tp->io_lock, flags);
पूर्ण

अटल पूर्णांक sp_technologic_init(काष्ठा sja1000_priv *priv, काष्ठा device_node *of)
अणु
	काष्ठा technologic_priv *tp = priv->priv;

	priv->पढ़ो_reg = sp_technologic_पढ़ो_reg16;
	priv->ग_लिखो_reg = sp_technologic_ग_लिखो_reg16;
	spin_lock_init(&tp->io_lock);

	वापस 0;
पूर्ण

अटल व्योम sp_populate(काष्ठा sja1000_priv *priv,
			काष्ठा sja1000_platक्रमm_data *pdata,
			अचिन्हित दीर्घ resource_mem_flags)
अणु
	/* The CAN घड़ी frequency is half the oscillator घड़ी frequency */
	priv->can.घड़ी.freq = pdata->osc_freq / 2;
	priv->ocr = pdata->ocr;
	priv->cdr = pdata->cdr;

	चयन (resource_mem_flags & IORESOURCE_MEM_TYPE_MASK) अणु
	हाल IORESOURCE_MEM_32BIT:
		priv->पढ़ो_reg = sp_पढ़ो_reg32;
		priv->ग_लिखो_reg = sp_ग_लिखो_reg32;
		अवरोध;
	हाल IORESOURCE_MEM_16BIT:
		priv->पढ़ो_reg = sp_पढ़ो_reg16;
		priv->ग_लिखो_reg = sp_ग_लिखो_reg16;
		अवरोध;
	हाल IORESOURCE_MEM_8BIT:
	शेष:
		priv->पढ़ो_reg = sp_पढ़ो_reg8;
		priv->ग_लिखो_reg = sp_ग_लिखो_reg8;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sp_populate_of(काष्ठा sja1000_priv *priv, काष्ठा device_node *of)
अणु
	पूर्णांक err;
	u32 prop;

	err = of_property_पढ़ो_u32(of, "reg-io-width", &prop);
	अगर (err)
		prop = 1; /* 8 bit is शेष */

	चयन (prop) अणु
	हाल 4:
		priv->पढ़ो_reg = sp_पढ़ो_reg32;
		priv->ग_लिखो_reg = sp_ग_लिखो_reg32;
		अवरोध;
	हाल 2:
		priv->पढ़ो_reg = sp_पढ़ो_reg16;
		priv->ग_लिखो_reg = sp_ग_लिखो_reg16;
		अवरोध;
	हाल 1:
	शेष:
		priv->पढ़ो_reg = sp_पढ़ो_reg8;
		priv->ग_लिखो_reg = sp_ग_लिखो_reg8;
	पूर्ण

	err = of_property_पढ़ो_u32(of, "nxp,external-clock-frequency", &prop);
	अगर (!err)
		priv->can.घड़ी.freq = prop / 2;
	अन्यथा
		priv->can.घड़ी.freq = SP_CAN_CLOCK; /* शेष */

	err = of_property_पढ़ो_u32(of, "nxp,tx-output-mode", &prop);
	अगर (!err)
		priv->ocr |= prop & OCR_MODE_MASK;
	अन्यथा
		priv->ocr |= OCR_MODE_NORMAL; /* शेष */

	err = of_property_पढ़ो_u32(of, "nxp,tx-output-config", &prop);
	अगर (!err)
		priv->ocr |= (prop << OCR_TX_SHIFT) & OCR_TX_MASK;
	अन्यथा
		priv->ocr |= OCR_TX0_PULLDOWN; /* शेष */

	err = of_property_पढ़ो_u32(of, "nxp,clock-out-frequency", &prop);
	अगर (!err && prop) अणु
		u32 भागider = priv->can.घड़ी.freq * 2 / prop;

		अगर (भागider > 1)
			priv->cdr |= भागider / 2 - 1;
		अन्यथा
			priv->cdr |= CDR_CLKOUT_MASK;
	पूर्ण अन्यथा अणु
		priv->cdr |= CDR_CLK_OFF; /* शेष */
	पूर्ण

	अगर (!of_property_पढ़ो_bool(of, "nxp,no-comparator-bypass"))
		priv->cdr |= CDR_CBP; /* शेष */
पूर्ण

अटल काष्ठा sja1000_of_data technologic_data = अणु
	.priv_sz = माप(काष्ठा technologic_priv),
	.init = sp_technologic_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sp_of_table[] = अणु
	अणु .compatible = "nxp,sja1000", .data = शून्य, पूर्ण,
	अणु .compatible = "technologic,sja1000", .data = &technologic_data, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sp_of_table);

अटल पूर्णांक sp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err, irq = 0;
	व्योम __iomem *addr;
	काष्ठा net_device *dev;
	काष्ठा sja1000_priv *priv;
	काष्ठा resource *res_mem, *res_irq = शून्य;
	काष्ठा sja1000_platक्रमm_data *pdata;
	काष्ठा device_node *of = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा sja1000_of_data *of_data = शून्य;
	माप_प्रकार priv_sz = 0;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata && !of) अणु
		dev_err(&pdev->dev, "No platform data provided!\n");
		वापस -ENODEV;
	पूर्ण

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res_mem->start,
				     resource_size(res_mem), DRV_NAME))
		वापस -EBUSY;

	addr = devm_ioremap(&pdev->dev, res_mem->start,
				    resource_size(res_mem));
	अगर (!addr)
		वापस -ENOMEM;

	अगर (of)
		irq = irq_of_parse_and_map(of, 0);
	अन्यथा
		res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);

	अगर (!irq && !res_irq)
		वापस -ENODEV;

	of_id = of_match_device(sp_of_table, &pdev->dev);
	अगर (of_id && of_id->data) अणु
		of_data = of_id->data;
		priv_sz = of_data->priv_sz;
	पूर्ण

	dev = alloc_sja1000dev(priv_sz);
	अगर (!dev)
		वापस -ENOMEM;
	priv = netdev_priv(dev);

	अगर (res_irq) अणु
		irq = res_irq->start;
		priv->irq_flags = res_irq->flags & IRQF_TRIGGER_MASK;
		अगर (res_irq->flags & IORESOURCE_IRQ_SHAREABLE)
			priv->irq_flags |= IRQF_SHARED;
	पूर्ण अन्यथा अणु
		priv->irq_flags = IRQF_SHARED;
	पूर्ण

	dev->irq = irq;
	priv->reg_base = addr;

	अगर (of) अणु
		sp_populate_of(priv, of);

		अगर (of_data && of_data->init) अणु
			err = of_data->init(priv, of);
			अगर (err)
				जाओ निकास_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		sp_populate(priv, pdata, res_mem->flags);
	पूर्ण

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = रेजिस्टर_sja1000dev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "registering %s failed (err=%d)\n",
			DRV_NAME, err);
		जाओ निकास_मुक्त;
	पूर्ण

	dev_info(&pdev->dev, "%s device registered (reg_base=%p, irq=%d)\n",
		 DRV_NAME, priv->reg_base, dev->irq);
	वापस 0;

 निकास_मुक्त:
	मुक्त_sja1000dev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक sp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_sja1000dev(dev);
	मुक्त_sja1000dev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sp_driver = अणु
	.probe = sp_probe,
	.हटाओ = sp_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = sp_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sp_driver);
