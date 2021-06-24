<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2016 Broadcom
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MDIO_RATE_ADJ_EXT_OFFSET	0x000
#घोषणा MDIO_RATE_ADJ_INT_OFFSET	0x004
#घोषणा MDIO_RATE_ADJ_DIVIDENT_SHIFT	16

#घोषणा MDIO_SCAN_CTRL_OFFSET		0x008
#घोषणा MDIO_SCAN_CTRL_OVRIDE_EXT_MSTR	28

#घोषणा MDIO_PARAM_OFFSET		0x23c
#घोषणा MDIO_PARAM_MIIM_CYCLE		29
#घोषणा MDIO_PARAM_INTERNAL_SEL		25
#घोषणा MDIO_PARAM_BUS_ID		22
#घोषणा MDIO_PARAM_C45_SEL		21
#घोषणा MDIO_PARAM_PHY_ID		16
#घोषणा MDIO_PARAM_PHY_DATA		0

#घोषणा MDIO_READ_OFFSET		0x240
#घोषणा MDIO_READ_DATA_MASK		0xffff
#घोषणा MDIO_ADDR_OFFSET		0x244

#घोषणा MDIO_CTRL_OFFSET		0x248
#घोषणा MDIO_CTRL_WRITE_OP		0x1
#घोषणा MDIO_CTRL_READ_OP		0x2

#घोषणा MDIO_STAT_OFFSET		0x24c
#घोषणा MDIO_STAT_DONE			1

#घोषणा BUS_MAX_ADDR			32
#घोषणा EXT_BUS_START_ADDR		16

#घोषणा MDIO_REG_ADDR_SPACE_SIZE	0x250

#घोषणा MDIO_OPERATING_FREQUENCY	11000000
#घोषणा MDIO_RATE_ADJ_DIVIDENT		1

काष्ठा iproc_mdiomux_desc अणु
	व्योम *mux_handle;
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा mii_bus *mii_bus;
	काष्ठा clk *core_clk;
पूर्ण;

अटल व्योम mdio_mux_iproc_config(काष्ठा iproc_mdiomux_desc *md)
अणु
	u32 भागisor;
	u32 val;

	/* Disable बाह्यal mdio master access */
	val = पढ़ोl(md->base + MDIO_SCAN_CTRL_OFFSET);
	val |= BIT(MDIO_SCAN_CTRL_OVRIDE_EXT_MSTR);
	ग_लिखोl(val, md->base + MDIO_SCAN_CTRL_OFFSET);

	अगर (md->core_clk) अणु
		/* use rate adjust regs to derrive the mdio's operating
		 * frequency from the specअगरied core घड़ी
		 */
		भागisor = clk_get_rate(md->core_clk) / MDIO_OPERATING_FREQUENCY;
		भागisor = भागisor / (MDIO_RATE_ADJ_DIVIDENT + 1);
		val = भागisor;
		val |= MDIO_RATE_ADJ_DIVIDENT << MDIO_RATE_ADJ_DIVIDENT_SHIFT;
		ग_लिखोl(val, md->base + MDIO_RATE_ADJ_EXT_OFFSET);
		ग_लिखोl(val, md->base + MDIO_RATE_ADJ_INT_OFFSET);
	पूर्ण
पूर्ण

अटल पूर्णांक iproc_mdio_रुको_क्रम_idle(व्योम __iomem *base, bool result)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(base + MDIO_STAT_OFFSET, val,
				  (val & MDIO_STAT_DONE) == result,
				  2000, 1000000);
पूर्ण

/* start_miim_ops- Program and start MDIO transaction over mdio bus.
 * @base: Base address
 * @phyid: phyid of the selected bus.
 * @reg: रेजिस्टर offset to be पढ़ो/written.
 * @val :0 अगर पढ़ो op अन्यथा value to be written in @reg;
 * @op: Operation that need to be carried out.
 *      MDIO_CTRL_READ_OP: Read transaction.
 *      MDIO_CTRL_WRITE_OP: Write transaction.
 *
 * Return value: Successful Read operation वापसs पढ़ो reg values and ग_लिखो
 *      operation वापसs 0. Failure operation वापसs negative error code.
 */
अटल पूर्णांक start_miim_ops(व्योम __iomem *base,
			  u16 phyid, u32 reg, u16 val, u32 op)
अणु
	u32 param;
	पूर्णांक ret;

	ग_लिखोl(0, base + MDIO_CTRL_OFFSET);
	ret = iproc_mdio_रुको_क्रम_idle(base, 0);
	अगर (ret)
		जाओ err;

	param = पढ़ोl(base + MDIO_PARAM_OFFSET);
	param |= phyid << MDIO_PARAM_PHY_ID;
	param |= val << MDIO_PARAM_PHY_DATA;
	अगर (reg & MII_ADDR_C45)
		param |= BIT(MDIO_PARAM_C45_SEL);

	ग_लिखोl(param, base + MDIO_PARAM_OFFSET);

	ग_लिखोl(reg, base + MDIO_ADDR_OFFSET);

	ग_लिखोl(op, base + MDIO_CTRL_OFFSET);

	ret = iproc_mdio_रुको_क्रम_idle(base, 1);
	अगर (ret)
		जाओ err;

	अगर (op == MDIO_CTRL_READ_OP)
		ret = पढ़ोl(base + MDIO_READ_OFFSET) & MDIO_READ_DATA_MASK;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक iproc_mdiomux_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyid, पूर्णांक reg)
अणु
	काष्ठा iproc_mdiomux_desc *md = bus->priv;
	पूर्णांक ret;

	ret = start_miim_ops(md->base, phyid, reg, 0, MDIO_CTRL_READ_OP);
	अगर (ret < 0)
		dev_err(&bus->dev, "mdiomux read operation failed!!!");

	वापस ret;
पूर्ण

अटल पूर्णांक iproc_mdiomux_ग_लिखो(काष्ठा mii_bus *bus,
			       पूर्णांक phyid, पूर्णांक reg, u16 val)
अणु
	काष्ठा iproc_mdiomux_desc *md = bus->priv;
	पूर्णांक ret;

	/* Write val at reg offset */
	ret = start_miim_ops(md->base, phyid, reg, val, MDIO_CTRL_WRITE_OP);
	अगर (ret < 0)
		dev_err(&bus->dev, "mdiomux write operation failed!!!");

	वापस ret;
पूर्ण

अटल पूर्णांक mdio_mux_iproc_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
				    व्योम *data)
अणु
	काष्ठा iproc_mdiomux_desc *md = data;
	u32 param, bus_id;
	bool bus_dir;

	/* select bus and its properties */
	bus_dir = (desired_child < EXT_BUS_START_ADDR);
	bus_id = bus_dir ? desired_child : (desired_child - EXT_BUS_START_ADDR);

	param = (bus_dir ? 1 : 0) << MDIO_PARAM_INTERNAL_SEL;
	param |= (bus_id << MDIO_PARAM_BUS_ID);

	ग_लिखोl(param, md->base + MDIO_PARAM_OFFSET);
	वापस 0;
पूर्ण

अटल पूर्णांक mdio_mux_iproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_mdiomux_desc *md;
	काष्ठा mii_bus *bus;
	काष्ठा resource *res;
	पूर्णांक rc;

	md = devm_kzalloc(&pdev->dev, माप(*md), GFP_KERNEL);
	अगर (!md)
		वापस -ENOMEM;
	md->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res->start & 0xfff) अणु
		/* For backward compatibility in हाल the
		 * base address is specअगरied with an offset.
		 */
		dev_info(&pdev->dev, "fix base address in dt-blob\n");
		res->start &= ~0xfff;
		res->end = res->start + MDIO_REG_ADDR_SPACE_SIZE - 1;
	पूर्ण
	md->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(md->base))
		वापस PTR_ERR(md->base);

	md->mii_bus = devm_mdiobus_alloc(&pdev->dev);
	अगर (!md->mii_bus) अणु
		dev_err(&pdev->dev, "mdiomux bus alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	md->core_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (md->core_clk == ERR_PTR(-ENOENT) ||
	    md->core_clk == ERR_PTR(-EINVAL))
		md->core_clk = शून्य;
	अन्यथा अगर (IS_ERR(md->core_clk))
		वापस PTR_ERR(md->core_clk);

	rc = clk_prepare_enable(md->core_clk);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to enable core clk\n");
		वापस rc;
	पूर्ण

	bus = md->mii_bus;
	bus->priv = md;
	bus->name = "iProc MDIO mux bus";
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->पढ़ो = iproc_mdiomux_पढ़ो;
	bus->ग_लिखो = iproc_mdiomux_ग_लिखो;

	bus->phy_mask = ~0;
	bus->dev.of_node = pdev->dev.of_node;
	rc = mdiobus_रेजिस्टर(bus);
	अगर (rc) अणु
		dev_err(&pdev->dev, "mdiomux registration failed\n");
		जाओ out_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, md);

	rc = mdio_mux_init(md->dev, md->dev->of_node, mdio_mux_iproc_चयन_fn,
			   &md->mux_handle, md, md->mii_bus);
	अगर (rc) अणु
		dev_info(md->dev, "mdiomux initialization failed\n");
		जाओ out_रेजिस्टर;
	पूर्ण

	mdio_mux_iproc_config(md);

	dev_info(md->dev, "iProc mdiomux registered\n");
	वापस 0;

out_रेजिस्टर:
	mdiobus_unरेजिस्टर(bus);
out_clk:
	clk_disable_unprepare(md->core_clk);
	वापस rc;
पूर्ण

अटल पूर्णांक mdio_mux_iproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_mdiomux_desc *md = platक्रमm_get_drvdata(pdev);

	mdio_mux_uninit(md->mux_handle);
	mdiobus_unरेजिस्टर(md->mii_bus);
	clk_disable_unprepare(md->core_clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mdio_mux_iproc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iproc_mdiomux_desc *md = dev_get_drvdata(dev);

	clk_disable_unprepare(md->core_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mdio_mux_iproc_resume(काष्ठा device *dev)
अणु
	काष्ठा iproc_mdiomux_desc *md = dev_get_drvdata(dev);
	पूर्णांक rc;

	rc = clk_prepare_enable(md->core_clk);
	अगर (rc) अणु
		dev_err(md->dev, "failed to enable core clk\n");
		वापस rc;
	पूर्ण
	mdio_mux_iproc_config(md);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mdio_mux_iproc_pm_ops,
			 mdio_mux_iproc_suspend, mdio_mux_iproc_resume);

अटल स्थिर काष्ठा of_device_id mdio_mux_iproc_match[] = अणु
	अणु
		.compatible = "brcm,mdio-mux-iproc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mdio_mux_iproc_match);

अटल काष्ठा platक्रमm_driver mdiomux_iproc_driver = अणु
	.driver = अणु
		.name		= "mdio-mux-iproc",
		.of_match_table = mdio_mux_iproc_match,
		.pm		= &mdio_mux_iproc_pm_ops,
	पूर्ण,
	.probe		= mdio_mux_iproc_probe,
	.हटाओ		= mdio_mux_iproc_हटाओ,
पूर्ण;

module_platक्रमm_driver(mdiomux_iproc_driver);

MODULE_DESCRIPTION("iProc MDIO Mux Bus Driver");
MODULE_AUTHOR("Pramod Kumar <pramod.kumar@broadcom.com>");
MODULE_LICENSE("GPL v2");
