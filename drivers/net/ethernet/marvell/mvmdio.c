<शैली गुरु>
/*
 * Driver क्रम the MDIO पूर्णांकerface of Marvell network पूर्णांकerfaces.
 *
 * Since the MDIO पूर्णांकerface of Marvell network पूर्णांकerfaces is shared
 * between all network पूर्णांकerfaces, having a single driver allows to
 * handle concurrent accesses properly (you may have four Ethernet
 * ports, but they in fact share the same SMI पूर्णांकerface to access
 * the MDIO bus). This driver is currently used by the mvneta and
 * mv643xx_eth drivers.
 *
 * Copyright (C) 2012 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>

#घोषणा MVMDIO_SMI_DATA_SHIFT		0
#घोषणा MVMDIO_SMI_PHY_ADDR_SHIFT	16
#घोषणा MVMDIO_SMI_PHY_REG_SHIFT	21
#घोषणा MVMDIO_SMI_READ_OPERATION	BIT(26)
#घोषणा MVMDIO_SMI_WRITE_OPERATION	0
#घोषणा MVMDIO_SMI_READ_VALID		BIT(27)
#घोषणा MVMDIO_SMI_BUSY			BIT(28)
#घोषणा MVMDIO_ERR_INT_CAUSE		0x007C
#घोषणा  MVMDIO_ERR_INT_SMI_DONE	0x00000010
#घोषणा MVMDIO_ERR_INT_MASK		0x0080

#घोषणा MVMDIO_XSMI_MGNT_REG		0x0
#घोषणा  MVMDIO_XSMI_PHYADDR_SHIFT	16
#घोषणा  MVMDIO_XSMI_DEVADDR_SHIFT	21
#घोषणा  MVMDIO_XSMI_WRITE_OPERATION	(0x5 << 26)
#घोषणा  MVMDIO_XSMI_READ_OPERATION	(0x7 << 26)
#घोषणा  MVMDIO_XSMI_READ_VALID		BIT(29)
#घोषणा  MVMDIO_XSMI_BUSY		BIT(30)
#घोषणा MVMDIO_XSMI_ADDR_REG		0x8

/*
 * SMI Timeout measurements:
 * - Kirkwood 88F6281 (Globalscale Dreamplug): 45us to 95us (Interrupt)
 * - Armada 370       (Globalscale Mirabox):   41us to 43us (Polled)
 */
#घोषणा MVMDIO_SMI_TIMEOUT		1000 /* 1000us = 1ms */
#घोषणा MVMDIO_SMI_POLL_INTERVAL_MIN	45
#घोषणा MVMDIO_SMI_POLL_INTERVAL_MAX	55

#घोषणा MVMDIO_XSMI_POLL_INTERVAL_MIN	150
#घोषणा MVMDIO_XSMI_POLL_INTERVAL_MAX	160

काष्ठा orion_mdio_dev अणु
	व्योम __iomem *regs;
	काष्ठा clk *clk[4];
	/*
	 * If we have access to the error पूर्णांकerrupt pin (which is
	 * somewhat misnamed as it not only reflects पूर्णांकernal errors
	 * but also reflects SMI completion), use that to रुको क्रम
	 * SMI access completion instead of polling the SMI busy bit.
	 */
	पूर्णांक err_पूर्णांकerrupt;
	रुको_queue_head_t smi_busy_रुको;
पूर्ण;

क्रमागत orion_mdio_bus_type अणु
	BUS_TYPE_SMI,
	BUS_TYPE_XSMI
पूर्ण;

काष्ठा orion_mdio_ops अणु
	पूर्णांक (*is_करोne)(काष्ठा orion_mdio_dev *);
	अचिन्हित पूर्णांक poll_पूर्णांकerval_min;
	अचिन्हित पूर्णांक poll_पूर्णांकerval_max;
पूर्ण;

/* Wait क्रम the SMI unit to be पढ़ोy क्रम another operation
 */
अटल पूर्णांक orion_mdio_रुको_पढ़ोy(स्थिर काष्ठा orion_mdio_ops *ops,
				 काष्ठा mii_bus *bus)
अणु
	काष्ठा orion_mdio_dev *dev = bus->priv;
	अचिन्हित दीर्घ समयout = usecs_to_jअगरfies(MVMDIO_SMI_TIMEOUT);
	अचिन्हित दीर्घ end = jअगरfies + समयout;
	पूर्णांक समयकरोut = 0;

	जबतक (1) अणु
	        अगर (ops->is_करोne(dev))
			वापस 0;
	        अन्यथा अगर (समयकरोut)
			अवरोध;

	        अगर (dev->err_पूर्णांकerrupt <= 0) अणु
			usleep_range(ops->poll_पूर्णांकerval_min,
				     ops->poll_पूर्णांकerval_max);

			अगर (समय_is_beक्रमe_jअगरfies(end))
				++समयकरोut;
	        पूर्ण अन्यथा अणु
			/* रुको_event_समयout करोes not guarantee a delay of at
			 * least one whole jअगरfie, so समयout must be no less
			 * than two.
			 */
			अगर (समयout < 2)
				समयout = 2;
			रुको_event_समयout(dev->smi_busy_रुको,
				           ops->is_करोne(dev), समयout);

			++समयकरोut;
	        पूर्ण
	पूर्ण

	dev_err(bus->parent, "Timeout: SMI busy for too long\n");
	वापस  -ETIMEDOUT;
पूर्ण

अटल पूर्णांक orion_mdio_smi_is_करोne(काष्ठा orion_mdio_dev *dev)
अणु
	वापस !(पढ़ोl(dev->regs) & MVMDIO_SMI_BUSY);
पूर्ण

अटल स्थिर काष्ठा orion_mdio_ops orion_mdio_smi_ops = अणु
	.is_करोne = orion_mdio_smi_is_करोne,
	.poll_पूर्णांकerval_min = MVMDIO_SMI_POLL_INTERVAL_MIN,
	.poll_पूर्णांकerval_max = MVMDIO_SMI_POLL_INTERVAL_MAX,
पूर्ण;

अटल पूर्णांक orion_mdio_smi_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id,
			       पूर्णांक regnum)
अणु
	काष्ठा orion_mdio_dev *dev = bus->priv;
	u32 val;
	पूर्णांक ret;

	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	ret = orion_mdio_रुको_पढ़ोy(&orion_mdio_smi_ops, bus);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(((mii_id << MVMDIO_SMI_PHY_ADDR_SHIFT) |
		(regnum << MVMDIO_SMI_PHY_REG_SHIFT)  |
		MVMDIO_SMI_READ_OPERATION),
	       dev->regs);

	ret = orion_mdio_रुको_पढ़ोy(&orion_mdio_smi_ops, bus);
	अगर (ret < 0)
		वापस ret;

	val = पढ़ोl(dev->regs);
	अगर (!(val & MVMDIO_SMI_READ_VALID)) अणु
		dev_err(bus->parent, "SMI bus read not valid\n");
		वापस -ENODEV;
	पूर्ण

	वापस val & GENMASK(15, 0);
पूर्ण

अटल पूर्णांक orion_mdio_smi_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id,
				पूर्णांक regnum, u16 value)
अणु
	काष्ठा orion_mdio_dev *dev = bus->priv;
	पूर्णांक ret;

	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	ret = orion_mdio_रुको_पढ़ोy(&orion_mdio_smi_ops, bus);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(((mii_id << MVMDIO_SMI_PHY_ADDR_SHIFT) |
		(regnum << MVMDIO_SMI_PHY_REG_SHIFT)  |
		MVMDIO_SMI_WRITE_OPERATION            |
		(value << MVMDIO_SMI_DATA_SHIFT)),
	       dev->regs);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_mdio_xsmi_is_करोne(काष्ठा orion_mdio_dev *dev)
अणु
	वापस !(पढ़ोl(dev->regs + MVMDIO_XSMI_MGNT_REG) & MVMDIO_XSMI_BUSY);
पूर्ण

अटल स्थिर काष्ठा orion_mdio_ops orion_mdio_xsmi_ops = अणु
	.is_करोne = orion_mdio_xsmi_is_करोne,
	.poll_पूर्णांकerval_min = MVMDIO_XSMI_POLL_INTERVAL_MIN,
	.poll_पूर्णांकerval_max = MVMDIO_XSMI_POLL_INTERVAL_MAX,
पूर्ण;

अटल पूर्णांक orion_mdio_xsmi_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id,
				पूर्णांक regnum)
अणु
	काष्ठा orion_mdio_dev *dev = bus->priv;
	u16 dev_addr = (regnum >> 16) & GENMASK(4, 0);
	पूर्णांक ret;

	अगर (!(regnum & MII_ADDR_C45))
		वापस -EOPNOTSUPP;

	ret = orion_mdio_रुको_पढ़ोy(&orion_mdio_xsmi_ops, bus);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(regnum & GENMASK(15, 0), dev->regs + MVMDIO_XSMI_ADDR_REG);
	ग_लिखोl((mii_id << MVMDIO_XSMI_PHYADDR_SHIFT) |
	       (dev_addr << MVMDIO_XSMI_DEVADDR_SHIFT) |
	       MVMDIO_XSMI_READ_OPERATION,
	       dev->regs + MVMDIO_XSMI_MGNT_REG);

	ret = orion_mdio_रुको_पढ़ोy(&orion_mdio_xsmi_ops, bus);
	अगर (ret < 0)
		वापस ret;

	अगर (!(पढ़ोl(dev->regs + MVMDIO_XSMI_MGNT_REG) &
	      MVMDIO_XSMI_READ_VALID)) अणु
		dev_err(bus->parent, "XSMI bus read not valid\n");
		वापस -ENODEV;
	पूर्ण

	वापस पढ़ोl(dev->regs + MVMDIO_XSMI_MGNT_REG) & GENMASK(15, 0);
पूर्ण

अटल पूर्णांक orion_mdio_xsmi_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id,
				पूर्णांक regnum, u16 value)
अणु
	काष्ठा orion_mdio_dev *dev = bus->priv;
	u16 dev_addr = (regnum >> 16) & GENMASK(4, 0);
	पूर्णांक ret;

	अगर (!(regnum & MII_ADDR_C45))
		वापस -EOPNOTSUPP;

	ret = orion_mdio_रुको_पढ़ोy(&orion_mdio_xsmi_ops, bus);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(regnum & GENMASK(15, 0), dev->regs + MVMDIO_XSMI_ADDR_REG);
	ग_लिखोl((mii_id << MVMDIO_XSMI_PHYADDR_SHIFT) |
	       (dev_addr << MVMDIO_XSMI_DEVADDR_SHIFT) |
	       MVMDIO_XSMI_WRITE_OPERATION | value,
	       dev->regs + MVMDIO_XSMI_MGNT_REG);

	वापस 0;
पूर्ण

अटल irqवापस_t orion_mdio_err_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा orion_mdio_dev *dev = dev_id;

	अगर (पढ़ोl(dev->regs + MVMDIO_ERR_INT_CAUSE) &
			MVMDIO_ERR_INT_SMI_DONE) अणु
		ग_लिखोl(~MVMDIO_ERR_INT_SMI_DONE,
				dev->regs + MVMDIO_ERR_INT_CAUSE);
		wake_up(&dev->smi_busy_रुको);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक orion_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत orion_mdio_bus_type type;
	काष्ठा resource *r;
	काष्ठा mii_bus *bus;
	काष्ठा orion_mdio_dev *dev;
	पूर्णांक i, ret;

	type = (क्रमागत orion_mdio_bus_type)of_device_get_match_data(&pdev->dev);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "No SMI register address given\n");
		वापस -ENODEV;
	पूर्ण

	bus = devm_mdiobus_alloc_size(&pdev->dev,
				      माप(काष्ठा orion_mdio_dev));
	अगर (!bus)
		वापस -ENOMEM;

	चयन (type) अणु
	हाल BUS_TYPE_SMI:
		bus->पढ़ो = orion_mdio_smi_पढ़ो;
		bus->ग_लिखो = orion_mdio_smi_ग_लिखो;
		अवरोध;
	हाल BUS_TYPE_XSMI:
		bus->पढ़ो = orion_mdio_xsmi_पढ़ो;
		bus->ग_लिखो = orion_mdio_xsmi_ग_लिखो;
		अवरोध;
	पूर्ण

	bus->name = "orion_mdio_bus";
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mii",
		 dev_name(&pdev->dev));
	bus->parent = &pdev->dev;

	dev = bus->priv;
	dev->regs = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!dev->regs) अणु
		dev_err(&pdev->dev, "Unable to remap SMI register\n");
		वापस -ENODEV;
	पूर्ण

	init_रुकोqueue_head(&dev->smi_busy_रुको);

	अगर (pdev->dev.of_node) अणु
		क्रम (i = 0; i < ARRAY_SIZE(dev->clk); i++) अणु
			dev->clk[i] = of_clk_get(pdev->dev.of_node, i);
			अगर (PTR_ERR(dev->clk[i]) == -EPROBE_DEFER) अणु
				ret = -EPROBE_DEFER;
				जाओ out_clk;
			पूर्ण
			अगर (IS_ERR(dev->clk[i]))
				अवरोध;
			clk_prepare_enable(dev->clk[i]);
		पूर्ण

		अगर (!IS_ERR(of_clk_get(pdev->dev.of_node,
				       ARRAY_SIZE(dev->clk))))
			dev_warn(&pdev->dev,
				 "unsupported number of clocks, limiting to the first "
				 __stringअगरy(ARRAY_SIZE(dev->clk)) "\n");
	पूर्ण अन्यथा अणु
		dev->clk[0] = clk_get(&pdev->dev, शून्य);
		अगर (PTR_ERR(dev->clk[0]) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ out_clk;
		पूर्ण
		अगर (!IS_ERR(dev->clk[0]))
			clk_prepare_enable(dev->clk[0]);
	पूर्ण


	dev->err_पूर्णांकerrupt = platक्रमm_get_irq_optional(pdev, 0);
	अगर (dev->err_पूर्णांकerrupt > 0 &&
	    resource_size(r) < MVMDIO_ERR_INT_MASK + 4) अणु
		dev_err(&pdev->dev,
			"disabling interrupt, resource size is too small\n");
		dev->err_पूर्णांकerrupt = 0;
	पूर्ण
	अगर (dev->err_पूर्णांकerrupt > 0) अणु
		ret = devm_request_irq(&pdev->dev, dev->err_पूर्णांकerrupt,
					orion_mdio_err_irq,
					IRQF_SHARED, pdev->name, dev);
		अगर (ret)
			जाओ out_mdio;

		ग_लिखोl(MVMDIO_ERR_INT_SMI_DONE,
			dev->regs + MVMDIO_ERR_INT_MASK);

	पूर्ण अन्यथा अगर (dev->err_पूर्णांकerrupt == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ out_mdio;
	पूर्ण

	ret = of_mdiobus_रेजिस्टर(bus, pdev->dev.of_node);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot register MDIO bus (%d)\n", ret);
		जाओ out_mdio;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;

out_mdio:
	अगर (dev->err_पूर्णांकerrupt > 0)
		ग_लिखोl(0, dev->regs + MVMDIO_ERR_INT_MASK);

out_clk:
	क्रम (i = 0; i < ARRAY_SIZE(dev->clk); i++) अणु
		अगर (IS_ERR(dev->clk[i]))
			अवरोध;
		clk_disable_unprepare(dev->clk[i]);
		clk_put(dev->clk[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक orion_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);
	काष्ठा orion_mdio_dev *dev = bus->priv;
	पूर्णांक i;

	अगर (dev->err_पूर्णांकerrupt > 0)
		ग_लिखोl(0, dev->regs + MVMDIO_ERR_INT_MASK);
	mdiobus_unरेजिस्टर(bus);

	क्रम (i = 0; i < ARRAY_SIZE(dev->clk); i++) अणु
		अगर (IS_ERR(dev->clk[i]))
			अवरोध;
		clk_disable_unprepare(dev->clk[i]);
		clk_put(dev->clk[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id orion_mdio_match[] = अणु
	अणु .compatible = "marvell,orion-mdio", .data = (व्योम *)BUS_TYPE_SMI पूर्ण,
	अणु .compatible = "marvell,xmdio", .data = (व्योम *)BUS_TYPE_XSMI पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, orion_mdio_match);

अटल काष्ठा platक्रमm_driver orion_mdio_driver = अणु
	.probe = orion_mdio_probe,
	.हटाओ = orion_mdio_हटाओ,
	.driver = अणु
		.name = "orion-mdio",
		.of_match_table = orion_mdio_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(orion_mdio_driver);

MODULE_DESCRIPTION("Marvell MDIO interface driver");
MODULE_AUTHOR("Thomas Petazzoni <thomas.petazzoni@free-electrons.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:orion-mdio");
