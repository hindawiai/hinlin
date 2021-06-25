<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम CC770 and AN82527 CAN controllers on the platक्रमm bus
 *
 * Copyright (C) 2009, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 */

/*
 * If platक्रमm data are used you should have similar definitions
 * in your board-specअगरic code:
 *
 *   अटल काष्ठा cc770_platक्रमm_data myboard_cc770_pdata = अणु
 *           .osc_freq = 16000000,
 *           .cir = 0x41,
 *           .cor = 0x20,
 *           .bcr = 0x40,
 *   पूर्ण;
 *
 * Please see include/linux/can/platक्रमm/cc770.h क्रम description of
 * above fields.
 *
 * If the device tree is used, you need a CAN node definition in your
 * DTS file similar to:
 *
 *   can@3,100 अणु
 *           compatible = "bosch,cc770";
 *           reg = <3 0x100 0x80>;
 *           पूर्णांकerrupts = <2 0>;
 *           पूर्णांकerrupt-parent = <&mpic>;
 *           bosch,बाह्यal-घड़ी-frequency = <16000000>;
 *   पूर्ण;
 *
 * See "Documentation/devicetree/bindings/net/can/cc770.txt" क्रम further
 * inक्रमmation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/platक्रमm/cc770.h>

#समावेश "cc770.h"

#घोषणा DRV_NAME "cc770_platform"

MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_DESCRIPTION("Socket-CAN driver for CC770 on the platform bus");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);

#घोषणा CC770_PLATFORM_CAN_CLOCK  16000000

अटल u8 cc770_platक्रमm_पढ़ो_reg(स्थिर काष्ठा cc770_priv *priv, पूर्णांक reg)
अणु
	वापस ioपढ़ो8(priv->reg_base + reg);
पूर्ण

अटल व्योम cc770_platक्रमm_ग_लिखो_reg(स्थिर काष्ठा cc770_priv *priv, पूर्णांक reg,
				     u8 val)
अणु
	ioग_लिखो8(val, priv->reg_base + reg);
पूर्ण

अटल पूर्णांक cc770_get_of_node_data(काष्ठा platक्रमm_device *pdev,
				  काष्ठा cc770_priv *priv)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर u32 *prop;
	पूर्णांक prop_size;
	u32 clkext;

	prop = of_get_property(np, "bosch,external-clock-frequency",
			       &prop_size);
	अगर (prop && (prop_size ==  माप(u32)))
		clkext = *prop;
	अन्यथा
		clkext = CC770_PLATFORM_CAN_CLOCK; /* शेष */
	priv->can.घड़ी.freq = clkext;

	/* The प्रणाली घड़ी may not exceed 10 MHz */
	अगर (priv->can.घड़ी.freq > 10000000) अणु
		priv->cpu_पूर्णांकerface |= CPUIF_DSC;
		priv->can.घड़ी.freq /= 2;
	पूर्ण

	/* The memory घड़ी may not exceed 8 MHz */
	अगर (priv->can.घड़ी.freq > 8000000)
		priv->cpu_पूर्णांकerface |= CPUIF_DMC;

	अगर (of_get_property(np, "bosch,divide-memory-clock", शून्य))
		priv->cpu_पूर्णांकerface |= CPUIF_DMC;
	अगर (of_get_property(np, "bosch,iso-low-speed-mux", शून्य))
		priv->cpu_पूर्णांकerface |= CPUIF_MUX;

	अगर (!of_get_property(np, "bosch,no-comperator-bypass", शून्य))
		priv->bus_config |= BUSCFG_CBY;
	अगर (of_get_property(np, "bosch,disconnect-rx0-input", शून्य))
		priv->bus_config |= BUSCFG_DR0;
	अगर (of_get_property(np, "bosch,disconnect-rx1-input", शून्य))
		priv->bus_config |= BUSCFG_DR1;
	अगर (of_get_property(np, "bosch,disconnect-tx1-output", शून्य))
		priv->bus_config |= BUSCFG_DT1;
	अगर (of_get_property(np, "bosch,polarity-dominant", शून्य))
		priv->bus_config |= BUSCFG_POL;

	prop = of_get_property(np, "bosch,clock-out-frequency", &prop_size);
	अगर (prop && (prop_size == माप(u32)) && *prop > 0) अणु
		u32 cdv = clkext / *prop;
		पूर्णांक slew;

		अगर (cdv > 0 && cdv < 16) अणु
			priv->cpu_पूर्णांकerface |= CPUIF_CEN;
			priv->clkout |= (cdv - 1) & CLKOUT_CD_MASK;

			prop = of_get_property(np, "bosch,slew-rate",
					       &prop_size);
			अगर (prop && (prop_size == माप(u32))) अणु
				slew = *prop;
			पूर्ण अन्यथा अणु
				/* Determine शेष slew rate */
				slew = (CLKOUT_SL_MASK >>
					CLKOUT_SL_SHIFT) -
					((cdv * clkext - 1) / 8000000);
				अगर (slew < 0)
					slew = 0;
			पूर्ण
			priv->clkout |= (slew << CLKOUT_SL_SHIFT) &
				CLKOUT_SL_MASK;
		पूर्ण अन्यथा अणु
			dev_dbg(&pdev->dev, "invalid clock-out-frequency\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cc770_get_platक्रमm_data(काष्ठा platक्रमm_device *pdev,
				   काष्ठा cc770_priv *priv)
अणु

	काष्ठा cc770_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	priv->can.घड़ी.freq = pdata->osc_freq;
	अगर (priv->cpu_पूर्णांकerface & CPUIF_DSC)
		priv->can.घड़ी.freq /= 2;
	priv->clkout = pdata->cor;
	priv->bus_config = pdata->bcr;
	priv->cpu_पूर्णांकerface = pdata->cir;

	वापस 0;
पूर्ण

अटल पूर्णांक cc770_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा cc770_priv *priv;
	काष्ठा resource *mem;
	resource_माप_प्रकार mem_size;
	व्योम __iomem *base;
	पूर्णांक err, irq;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!mem || irq <= 0)
		वापस -ENODEV;

	mem_size = resource_size(mem);
	अगर (!request_mem_region(mem->start, mem_size, pdev->name))
		वापस -EBUSY;

	base = ioremap(mem->start, mem_size);
	अगर (!base) अणु
		err = -ENOMEM;
		जाओ निकास_release_mem;
	पूर्ण

	dev = alloc_cc770dev(0);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ निकास_unmap_mem;
	पूर्ण

	dev->irq = irq;
	priv = netdev_priv(dev);
	priv->पढ़ो_reg = cc770_platक्रमm_पढ़ो_reg;
	priv->ग_लिखो_reg = cc770_platक्रमm_ग_लिखो_reg;
	priv->irq_flags = IRQF_SHARED;
	priv->reg_base = base;

	अगर (pdev->dev.of_node)
		err = cc770_get_of_node_data(pdev, priv);
	अन्यथा अगर (dev_get_platdata(&pdev->dev))
		err = cc770_get_platक्रमm_data(pdev, priv);
	अन्यथा
		err = -ENODEV;
	अगर (err)
		जाओ निकास_मुक्त_cc770;

	dev_dbg(&pdev->dev,
		 "reg_base=0x%p irq=%d clock=%d cpu_interface=0x%02x "
		 "bus_config=0x%02x clkout=0x%02x\n",
		 priv->reg_base, dev->irq, priv->can.घड़ी.freq,
		 priv->cpu_पूर्णांकerface, priv->bus_config, priv->clkout);

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = रेजिस्टर_cc770dev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"couldn't register CC700 device (err=%d)\n", err);
		जाओ निकास_मुक्त_cc770;
	पूर्ण

	वापस 0;

निकास_मुक्त_cc770:
	मुक्त_cc770dev(dev);
निकास_unmap_mem:
	iounmap(base);
निकास_release_mem:
	release_mem_region(mem->start, mem_size);

	वापस err;
पूर्ण

अटल पूर्णांक cc770_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा cc770_priv *priv = netdev_priv(dev);
	काष्ठा resource *mem;

	unरेजिस्टर_cc770dev(dev);
	iounmap(priv->reg_base);
	मुक्त_cc770dev(dev);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(mem->start, resource_size(mem));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cc770_platक्रमm_table[] = अणु
	अणु.compatible = "bosch,cc770"पूर्ण, /* CC770 from Bosch */
	अणु.compatible = "intc,82527"पूर्ण,  /* AN82527 from Intel CP */
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cc770_platक्रमm_table);

अटल काष्ठा platक्रमm_driver cc770_platक्रमm_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = cc770_platक्रमm_table,
	पूर्ण,
	.probe = cc770_platक्रमm_probe,
	.हटाओ = cc770_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(cc770_platक्रमm_driver);
