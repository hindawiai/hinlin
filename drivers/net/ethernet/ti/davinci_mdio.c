<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DaVinci MDIO Module driver
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * Shamelessly ripped out of davinci_emac.c, original copyrights follow:
 *
 * Copyright (C) 2009 Texas Instruments.
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/phy.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/davinci_emac.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/pinctrl/consumer.h>

/*
 * This समयout definition is a worst-हाल ultra defensive measure against
 * unexpected controller lock ups.  Ideally, we should never ever hit this
 * scenario in practice.
 */
#घोषणा MDIO_TIMEOUT		100 /* msecs */

#घोषणा PHY_REG_MASK		0x1f
#घोषणा PHY_ID_MASK		0x1f

#घोषणा DEF_OUT_FREQ		2200000		/* 2.2 MHz */

काष्ठा davinci_mdio_of_param अणु
	पूर्णांक स्वतःsuspend_delay_ms;
पूर्ण;

काष्ठा davinci_mdio_regs अणु
	u32	version;
	u32	control;
#घोषणा CONTROL_IDLE		BIT(31)
#घोषणा CONTROL_ENABLE		BIT(30)
#घोषणा CONTROL_MAX_DIV		(0xffff)

	u32	alive;
	u32	link;
	u32	linkपूर्णांकraw;
	u32	linkपूर्णांकmasked;
	u32	__reserved_0[2];
	u32	userपूर्णांकraw;
	u32	userपूर्णांकmasked;
	u32	userपूर्णांकmaskset;
	u32	userपूर्णांकmaskclr;
	u32	__reserved_1[20];

	काष्ठा अणु
		u32	access;
#घोषणा USERACCESS_GO		BIT(31)
#घोषणा USERACCESS_WRITE	BIT(30)
#घोषणा USERACCESS_ACK		BIT(29)
#घोषणा USERACCESS_READ		(0)
#घोषणा USERACCESS_DATA		(0xffff)

		u32	physel;
	पूर्ण	user[0];
पूर्ण;

अटल स्थिर काष्ठा mdio_platक्रमm_data शेष_pdata = अणु
	.bus_freq = DEF_OUT_FREQ,
पूर्ण;

काष्ठा davinci_mdio_data अणु
	काष्ठा mdio_platक्रमm_data pdata;
	काष्ठा davinci_mdio_regs __iomem *regs;
	काष्ठा clk	*clk;
	काष्ठा device	*dev;
	काष्ठा mii_bus	*bus;
	bool            active_in_suspend;
	अचिन्हित दीर्घ	access_समय; /* jअगरfies */
	/* Indicates that driver shouldn't modअगरy phy_mask in हाल
	 * अगर MDIO bus is रेजिस्टरed from DT.
	 */
	bool		skip_scan;
	u32		clk_भाग;
पूर्ण;

अटल व्योम davinci_mdio_init_clk(काष्ठा davinci_mdio_data *data)
अणु
	u32 mdio_in, भाग, mdio_out_khz, access_समय;

	mdio_in = clk_get_rate(data->clk);
	भाग = (mdio_in / data->pdata.bus_freq) - 1;
	अगर (भाग > CONTROL_MAX_DIV)
		भाग = CONTROL_MAX_DIV;

	data->clk_भाग = भाग;
	/*
	 * One mdio transaction consists of:
	 *	32 bits of preamble
	 *	32 bits of transferred data
	 *	24 bits of bus yield (not needed unless shared?)
	 */
	mdio_out_khz = mdio_in / (1000 * (भाग + 1));
	access_समय  = (88 * 1000) / mdio_out_khz;

	/*
	 * In the worst हाल, we could be kicking off a user-access immediately
	 * after the mdio bus scan state-machine triggered its own पढ़ो.  If
	 * so, our request could get deferred by one access cycle.  We
	 * defensively allow क्रम 4 access cycles.
	 */
	data->access_समय = usecs_to_jअगरfies(access_समय * 4);
	अगर (!data->access_समय)
		data->access_समय = 1;
पूर्ण

अटल व्योम davinci_mdio_enable(काष्ठा davinci_mdio_data *data)
अणु
	/* set enable and घड़ी भागider */
	ग_लिखोl(data->clk_भाग | CONTROL_ENABLE, &data->regs->control);
पूर्ण

अटल पूर्णांक davinci_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा davinci_mdio_data *data = bus->priv;
	u32 phy_mask, ver;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(data->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(data->dev);
		वापस ret;
	पूर्ण

	/* रुको क्रम scan logic to settle */
	msleep(PHY_MAX_ADDR * data->access_समय);

	/* dump hardware version info */
	ver = पढ़ोl(&data->regs->version);
	dev_info(data->dev,
		 "davinci mdio revision %d.%d, bus freq %ld\n",
		 (ver >> 8) & 0xff, ver & 0xff,
		 data->pdata.bus_freq);

	अगर (data->skip_scan)
		जाओ करोne;

	/* get phy mask from the alive रेजिस्टर */
	phy_mask = पढ़ोl(&data->regs->alive);
	अगर (phy_mask) अणु
		/* restrict mdio bus to live phys only */
		dev_info(data->dev, "detected phy mask %x\n", ~phy_mask);
		phy_mask = ~phy_mask;
	पूर्ण अन्यथा अणु
		/* desperately scan all phys */
		dev_warn(data->dev, "no live phy, scanning all\n");
		phy_mask = 0;
	पूर्ण
	data->bus->phy_mask = phy_mask;

करोne:
	pm_runसमय_mark_last_busy(data->dev);
	pm_runसमय_put_स्वतःsuspend(data->dev);

	वापस 0;
पूर्ण

/* रुको until hardware is पढ़ोy क्रम another user access */
अटल अंतरभूत पूर्णांक रुको_क्रम_user_access(काष्ठा davinci_mdio_data *data)
अणु
	काष्ठा davinci_mdio_regs __iomem *regs = data->regs;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(MDIO_TIMEOUT);
	u32 reg;

	जबतक (समय_after(समयout, jअगरfies)) अणु
		reg = पढ़ोl(&regs->user[0].access);
		अगर ((reg & USERACCESS_GO) == 0)
			वापस 0;

		reg = पढ़ोl(&regs->control);
		अगर ((reg & CONTROL_IDLE) == 0) अणु
			usleep_range(100, 200);
			जारी;
		पूर्ण

		/*
		 * An emac soft_reset may have clobbered the mdio controller's
		 * state machine.  We need to reset and retry the current
		 * operation
		 */
		dev_warn(data->dev, "resetting idled controller\n");
		davinci_mdio_enable(data);
		वापस -EAGAIN;
	पूर्ण

	reg = पढ़ोl(&regs->user[0].access);
	अगर ((reg & USERACCESS_GO) == 0)
		वापस 0;

	dev_err(data->dev, "timed out waiting for user access\n");
	वापस -ETIMEDOUT;
पूर्ण

/* रुको until hardware state machine is idle */
अटल अंतरभूत पूर्णांक रुको_क्रम_idle(काष्ठा davinci_mdio_data *data)
अणु
	काष्ठा davinci_mdio_regs __iomem *regs = data->regs;
	u32 val, ret;

	ret = पढ़ोl_poll_समयout(&regs->control, val, val & CONTROL_IDLE,
				 0, MDIO_TIMEOUT * 1000);
	अगर (ret)
		dev_err(data->dev, "timed out waiting for idle\n");

	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक phy_reg)
अणु
	काष्ठा davinci_mdio_data *data = bus->priv;
	u32 reg;
	पूर्णांक ret;

	अगर (phy_reg & ~PHY_REG_MASK || phy_id & ~PHY_ID_MASK)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(data->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(data->dev);
		वापस ret;
	पूर्ण

	reg = (USERACCESS_GO | USERACCESS_READ | (phy_reg << 21) |
	       (phy_id << 16));

	जबतक (1) अणु
		ret = रुको_क्रम_user_access(data);
		अगर (ret == -EAGAIN)
			जारी;
		अगर (ret < 0)
			अवरोध;

		ग_लिखोl(reg, &data->regs->user[0].access);

		ret = रुको_क्रम_user_access(data);
		अगर (ret == -EAGAIN)
			जारी;
		अगर (ret < 0)
			अवरोध;

		reg = पढ़ोl(&data->regs->user[0].access);
		ret = (reg & USERACCESS_ACK) ? (reg & USERACCESS_DATA) : -EIO;
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(data->dev);
	pm_runसमय_put_स्वतःsuspend(data->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id,
			      पूर्णांक phy_reg, u16 phy_data)
अणु
	काष्ठा davinci_mdio_data *data = bus->priv;
	u32 reg;
	पूर्णांक ret;

	अगर (phy_reg & ~PHY_REG_MASK || phy_id & ~PHY_ID_MASK)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(data->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(data->dev);
		वापस ret;
	पूर्ण

	reg = (USERACCESS_GO | USERACCESS_WRITE | (phy_reg << 21) |
		   (phy_id << 16) | (phy_data & USERACCESS_DATA));

	जबतक (1) अणु
		ret = रुको_क्रम_user_access(data);
		अगर (ret == -EAGAIN)
			जारी;
		अगर (ret < 0)
			अवरोध;

		ग_लिखोl(reg, &data->regs->user[0].access);

		ret = रुको_क्रम_user_access(data);
		अगर (ret == -EAGAIN)
			जारी;
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(data->dev);
	pm_runसमय_put_स्वतःsuspend(data->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mdio_probe_dt(काष्ठा mdio_platक्रमm_data *data,
			 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	u32 prop;

	अगर (!node)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(node, "bus_freq", &prop)) अणु
		dev_err(&pdev->dev, "Missing bus_freq property in the DT.\n");
		वापस -EINVAL;
	पूर्ण
	data->bus_freq = prop;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा davinci_mdio_of_param of_cpsw_mdio_data = अणु
	.स्वतःsuspend_delay_ms = 100,
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_mdio_of_mtable[] = अणु
	अणु .compatible = "ti,davinci_mdio", पूर्ण,
	अणु .compatible = "ti,cpsw-mdio", .data = &of_cpsw_mdio_dataपूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_mdio_of_mtable);
#पूर्ण_अगर

अटल पूर्णांक davinci_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा davinci_mdio_data *data;
	काष्ठा resource *res;
	काष्ठा phy_device *phy;
	पूर्णांक ret, addr;
	पूर्णांक स्वतःsuspend_delay_ms = -1;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->bus = devm_mdiobus_alloc(dev);
	अगर (!data->bus) अणु
		dev_err(dev, "failed to alloc mii bus\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		स्थिर काष्ठा davinci_mdio_of_param *of_mdio_data;

		ret = davinci_mdio_probe_dt(&data->pdata, pdev);
		अगर (ret)
			वापस ret;
		snम_लिखो(data->bus->id, MII_BUS_ID_SIZE, "%s", pdev->name);

		of_mdio_data = of_device_get_match_data(&pdev->dev);
		अगर (of_mdio_data) अणु
			स्वतःsuspend_delay_ms =
					of_mdio_data->स्वतःsuspend_delay_ms;
		पूर्ण
	पूर्ण अन्यथा अणु
		data->pdata = pdata ? (*pdata) : शेष_pdata;
		snम_लिखो(data->bus->id, MII_BUS_ID_SIZE, "%s-%x",
			 pdev->name, pdev->id);
	पूर्ण

	data->bus->name		= dev_name(dev);
	data->bus->पढ़ो		= davinci_mdio_पढ़ो;
	data->bus->ग_लिखो	= davinci_mdio_ग_लिखो;
	data->bus->reset	= davinci_mdio_reset;
	data->bus->parent	= dev;
	data->bus->priv		= data;

	data->clk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(data->clk)) अणु
		dev_err(dev, "failed to get device clock\n");
		वापस PTR_ERR(data->clk);
	पूर्ण

	dev_set_drvdata(dev, data);
	data->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;
	data->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!data->regs)
		वापस -ENOMEM;

	davinci_mdio_init_clk(data);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, स्वतःsuspend_delay_ms);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	/* रेजिस्टर the mii bus
	 * Create PHYs from DT only in हाल अगर PHY child nodes are explicitly
	 * defined to support backward compatibility with DTs which assume that
	 * Davinci MDIO will always scan the bus क्रम PHYs detection.
	 */
	अगर (dev->of_node && of_get_child_count(dev->of_node))
		data->skip_scan = true;

	ret = of_mdiobus_रेजिस्टर(data->bus, dev->of_node);
	अगर (ret)
		जाओ bail_out;

	/* scan and dump the bus */
	क्रम (addr = 0; addr < PHY_MAX_ADDR; addr++) अणु
		phy = mdiobus_get_phy(data->bus, addr);
		अगर (phy) अणु
			dev_info(dev, "phy[%d]: device %s, driver %s\n",
				 phy->mdio.addr, phydev_name(phy),
				 phy->drv ? phy->drv->name : "unknown");
		पूर्ण
	पूर्ण

	वापस 0;

bail_out:
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक davinci_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_mdio_data *data = platक्रमm_get_drvdata(pdev);

	अगर (data->bus)
		mdiobus_unरेजिस्टर(data->bus);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक davinci_mdio_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा davinci_mdio_data *data = dev_get_drvdata(dev);
	u32 ctrl;

	/* shutकरोwn the scan state machine */
	ctrl = पढ़ोl(&data->regs->control);
	ctrl &= ~CONTROL_ENABLE;
	ग_लिखोl(ctrl, &data->regs->control);
	रुको_क्रम_idle(data);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mdio_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा davinci_mdio_data *data = dev_get_drvdata(dev);

	davinci_mdio_enable(data);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक davinci_mdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा davinci_mdio_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	data->active_in_suspend = !pm_runसमय_status_suspended(dev);
	अगर (data->active_in_suspend)
		ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret < 0)
		वापस ret;

	/* Select sleep pin state */
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_mdio_resume(काष्ठा device *dev)
अणु
	काष्ठा davinci_mdio_data *data = dev_get_drvdata(dev);

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(dev);

	अगर (data->active_in_suspend)
		pm_runसमय_क्रमce_resume(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops davinci_mdio_pm_ops = अणु
	SET_RUNTIME_PM_OPS(davinci_mdio_runसमय_suspend,
			   davinci_mdio_runसमय_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(davinci_mdio_suspend, davinci_mdio_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver davinci_mdio_driver = अणु
	.driver = अणु
		.name	 = "davinci_mdio",
		.pm	 = &davinci_mdio_pm_ops,
		.of_match_table = of_match_ptr(davinci_mdio_of_mtable),
	पूर्ण,
	.probe = davinci_mdio_probe,
	.हटाओ = davinci_mdio_हटाओ,
पूर्ण;

अटल पूर्णांक __init davinci_mdio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&davinci_mdio_driver);
पूर्ण
device_initcall(davinci_mdio_init);

अटल व्योम __निकास davinci_mdio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&davinci_mdio_driver);
पूर्ण
module_निकास(davinci_mdio_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DaVinci MDIO driver");
