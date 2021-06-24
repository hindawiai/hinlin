<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा MDIO_DRV_NAME "Hi-HNS_MDIO"
#घोषणा MDIO_BUS_NAME "Hisilicon MII Bus"

#घोषणा MDIO_TIMEOUT			1000000

काष्ठा hns_mdio_sc_reg अणु
	u16 mdio_clk_en;
	u16 mdio_clk_dis;
	u16 mdio_reset_req;
	u16 mdio_reset_dreq;
	u16 mdio_clk_st;
	u16 mdio_reset_st;
पूर्ण;

काष्ठा hns_mdio_device अणु
	u8 __iomem *vbase;		/* mdio reg base address */
	काष्ठा regmap *subctrl_vbase;
	काष्ठा hns_mdio_sc_reg sc_reg;
पूर्ण;

/* mdio reg */
#घोषणा MDIO_COMMAND_REG		0x0
#घोषणा MDIO_ADDR_REG			0x4
#घोषणा MDIO_WDATA_REG			0x8
#घोषणा MDIO_RDATA_REG			0xc
#घोषणा MDIO_STA_REG			0x10

/* cfg phy bit map */
#घोषणा MDIO_CMD_DEVAD_M	0x1f
#घोषणा MDIO_CMD_DEVAD_S	0
#घोषणा MDIO_CMD_PRTAD_M	0x1f
#घोषणा MDIO_CMD_PRTAD_S	5
#घोषणा MDIO_CMD_OP_S		10
#घोषणा MDIO_CMD_ST_S		12
#घोषणा MDIO_CMD_START_B	14

#घोषणा MDIO_ADDR_DATA_M	0xffff
#घोषणा MDIO_ADDR_DATA_S	0

#घोषणा MDIO_WDATA_DATA_M	0xffff
#घोषणा MDIO_WDATA_DATA_S	0

#घोषणा MDIO_RDATA_DATA_M	0xffff
#घोषणा MDIO_RDATA_DATA_S	0

#घोषणा MDIO_STATE_STA_B	0

क्रमागत mdio_st_clause अणु
	MDIO_ST_CLAUSE_45 = 0,
	MDIO_ST_CLAUSE_22
पूर्ण;

क्रमागत mdio_c22_op_seq अणु
	MDIO_C22_WRITE = 1,
	MDIO_C22_READ = 2
पूर्ण;

क्रमागत mdio_c45_op_seq अणु
	MDIO_C45_WRITE_ADDR = 0,
	MDIO_C45_WRITE_DATA,
	MDIO_C45_READ_INCREMENT,
	MDIO_C45_READ
पूर्ण;

/* peri subctrl reg */
#घोषणा MDIO_SC_CLK_EN		0x338
#घोषणा MDIO_SC_CLK_DIS		0x33C
#घोषणा MDIO_SC_RESET_REQ	0xA38
#घोषणा MDIO_SC_RESET_DREQ	0xA3C
#घोषणा MDIO_SC_CLK_ST		0x531C
#घोषणा MDIO_SC_RESET_ST	0x5A1C

अटल व्योम mdio_ग_लिखो_reg(u8 __iomem *base, u32 reg, u32 value)
अणु
	ग_लिखोl_relaxed(value, base + reg);
पूर्ण

#घोषणा MDIO_WRITE_REG(a, reg, value) \
	mdio_ग_लिखो_reg((a)->vbase, (reg), (value))

अटल u32 mdio_पढ़ो_reg(u8 __iomem *base, u32 reg)
अणु
	वापस पढ़ोl_relaxed(base + reg);
पूर्ण

#घोषणा mdio_set_field(origin, mask, shअगरt, val) \
	करो अणु \
		(origin) &= (~((mask) << (shअगरt))); \
		(origin) |= (((val) & (mask)) << (shअगरt)); \
	पूर्ण जबतक (0)

#घोषणा mdio_get_field(origin, mask, shअगरt) (((origin) >> (shअगरt)) & (mask))

अटल व्योम mdio_set_reg_field(u8 __iomem *base, u32 reg, u32 mask, u32 shअगरt,
			       u32 val)
अणु
	u32 origin = mdio_पढ़ो_reg(base, reg);

	mdio_set_field(origin, mask, shअगरt, val);
	mdio_ग_लिखो_reg(base, reg, origin);
पूर्ण

#घोषणा MDIO_SET_REG_FIELD(dev, reg, mask, shअगरt, val) \
	mdio_set_reg_field((dev)->vbase, (reg), (mask), (shअगरt), (val))

अटल u32 mdio_get_reg_field(u8 __iomem *base, u32 reg, u32 mask, u32 shअगरt)
अणु
	u32 origin;

	origin = mdio_पढ़ो_reg(base, reg);
	वापस mdio_get_field(origin, mask, shअगरt);
पूर्ण

#घोषणा MDIO_GET_REG_FIELD(dev, reg, mask, shअगरt) \
		mdio_get_reg_field((dev)->vbase, (reg), (mask), (shअगरt))

#घोषणा MDIO_GET_REG_BIT(dev, reg, bit) \
		mdio_get_reg_field((dev)->vbase, (reg), 0x1ull, (bit))

#घोषणा MDIO_CHECK_SET_ST	1
#घोषणा MDIO_CHECK_CLR_ST	0

अटल पूर्णांक mdio_sc_cfg_reg_ग_लिखो(काष्ठा hns_mdio_device *mdio_dev,
				 u32 cfg_reg, u32 set_val,
				 u32 st_reg, u32 st_msk, u8 check_st)
अणु
	u32 समय_cnt;
	u32 reg_value;
	पूर्णांक ret;

	regmap_ग_लिखो(mdio_dev->subctrl_vbase, cfg_reg, set_val);

	क्रम (समय_cnt = MDIO_TIMEOUT; समय_cnt; समय_cnt--) अणु
		ret = regmap_पढ़ो(mdio_dev->subctrl_vbase, st_reg, &reg_value);
		अगर (ret)
			वापस ret;

		reg_value &= st_msk;
		अगर ((!!check_st) == (!!reg_value))
			अवरोध;
	पूर्ण

	अगर ((!!check_st) != (!!reg_value))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक hns_mdio_रुको_पढ़ोy(काष्ठा mii_bus *bus)
अणु
	काष्ठा hns_mdio_device *mdio_dev = bus->priv;
	u32 cmd_reg_value;
	पूर्णांक i;

	/* रुकोting क्रम MDIO_COMMAND_REG 's mdio_start==0 */
	/* after that can करो पढ़ो or ग_लिखो*/
	क्रम (i = 0; i < MDIO_TIMEOUT; i++) अणु
		cmd_reg_value = MDIO_GET_REG_BIT(mdio_dev,
						 MDIO_COMMAND_REG,
						 MDIO_CMD_START_B);
		अगर (!cmd_reg_value)
			अवरोध;
	पूर्ण
	अगर ((i == MDIO_TIMEOUT) && cmd_reg_value)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम hns_mdio_cmd_ग_लिखो(काष्ठा hns_mdio_device *mdio_dev,
			       u8 is_c45, u8 op, u8 phy_id, u16 cmd)
अणु
	u32 cmd_reg_value;
	u8 st = is_c45 ? MDIO_ST_CLAUSE_45 : MDIO_ST_CLAUSE_22;

	cmd_reg_value = st << MDIO_CMD_ST_S;
	cmd_reg_value |= op << MDIO_CMD_OP_S;
	cmd_reg_value |=
		(phy_id & MDIO_CMD_PRTAD_M) << MDIO_CMD_PRTAD_S;
	cmd_reg_value |= (cmd & MDIO_CMD_DEVAD_M) << MDIO_CMD_DEVAD_S;
	cmd_reg_value |= 1 << MDIO_CMD_START_B;

	MDIO_WRITE_REG(mdio_dev, MDIO_COMMAND_REG, cmd_reg_value);
पूर्ण

/**
 * hns_mdio_ग_लिखो - access phy रेजिस्टर
 * @bus: mdio bus
 * @phy_id: phy id
 * @regnum: रेजिस्टर num
 * @data: रेजिस्टर value
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_mdio_ग_लिखो(काष्ठा mii_bus *bus,
			  पूर्णांक phy_id, पूर्णांक regnum, u16 data)
अणु
	पूर्णांक ret;
	काष्ठा hns_mdio_device *mdio_dev = (काष्ठा hns_mdio_device *)bus->priv;
	u8 devad = ((regnum >> 16) & 0x1f);
	u8 is_c45 = !!(regnum & MII_ADDR_C45);
	u16 reg = (u16)(regnum & 0xffff);
	u8 op;
	u16 cmd_reg_cfg;

	dev_dbg(&bus->dev, "mdio write %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, is_c45=%d, devad=%d, reg=%#x, write data=%d\n",
		phy_id, is_c45, devad, reg, data);

	/* रुको क्रम पढ़ोy */
	ret = hns_mdio_रुको_पढ़ोy(bus);
	अगर (ret) अणु
		dev_err(&bus->dev, "MDIO bus is busy\n");
		वापस ret;
	पूर्ण

	अगर (!is_c45) अणु
		cmd_reg_cfg = reg;
		op = MDIO_C22_WRITE;
	पूर्ण अन्यथा अणु
		/* config the cmd-reg to ग_लिखो addr*/
		MDIO_SET_REG_FIELD(mdio_dev, MDIO_ADDR_REG, MDIO_ADDR_DATA_M,
				   MDIO_ADDR_DATA_S, reg);

		hns_mdio_cmd_ग_लिखो(mdio_dev, is_c45,
				   MDIO_C45_WRITE_ADDR, phy_id, devad);

		/* check क्रम पढ़ो or ग_लिखो opt is finished */
		ret = hns_mdio_रुको_पढ़ोy(bus);
		अगर (ret) अणु
			dev_err(&bus->dev, "MDIO bus is busy\n");
			वापस ret;
		पूर्ण

		/* config the data needed writing */
		cmd_reg_cfg = devad;
		op = MDIO_C45_WRITE_DATA;
	पूर्ण

	MDIO_SET_REG_FIELD(mdio_dev, MDIO_WDATA_REG, MDIO_WDATA_DATA_M,
			   MDIO_WDATA_DATA_S, data);

	hns_mdio_cmd_ग_लिखो(mdio_dev, is_c45, op, phy_id, cmd_reg_cfg);

	वापस 0;
पूर्ण

/**
 * hns_mdio_पढ़ो - access phy रेजिस्टर
 * @bus: mdio bus
 * @phy_id: phy id
 * @regnum: रेजिस्टर num
 *
 * Return phy रेजिस्टर value
 */
अटल पूर्णांक hns_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	पूर्णांक ret;
	u16 reg_val;
	u8 devad = ((regnum >> 16) & 0x1f);
	u8 is_c45 = !!(regnum & MII_ADDR_C45);
	u16 reg = (u16)(regnum & 0xffff);
	काष्ठा hns_mdio_device *mdio_dev = (काष्ठा hns_mdio_device *)bus->priv;

	dev_dbg(&bus->dev, "mdio read %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, is_c45=%d, devad=%d, reg=%#x!\n",
		phy_id, is_c45, devad, reg);

	/* Step 1: रुको क्रम पढ़ोy */
	ret = hns_mdio_रुको_पढ़ोy(bus);
	अगर (ret) अणु
		dev_err(&bus->dev, "MDIO bus is busy\n");
		वापस ret;
	पूर्ण

	अगर (!is_c45) अणु
		hns_mdio_cmd_ग_लिखो(mdio_dev, is_c45,
				   MDIO_C22_READ, phy_id, reg);
	पूर्ण अन्यथा अणु
		MDIO_SET_REG_FIELD(mdio_dev, MDIO_ADDR_REG, MDIO_ADDR_DATA_M,
				   MDIO_ADDR_DATA_S, reg);

		/* Step 2; config the cmd-reg to ग_लिखो addr*/
		hns_mdio_cmd_ग_लिखो(mdio_dev, is_c45,
				   MDIO_C45_WRITE_ADDR, phy_id, devad);

		/* Step 3: check क्रम पढ़ो or ग_लिखो opt is finished */
		ret = hns_mdio_रुको_पढ़ोy(bus);
		अगर (ret) अणु
			dev_err(&bus->dev, "MDIO bus is busy\n");
			वापस ret;
		पूर्ण

		hns_mdio_cmd_ग_लिखो(mdio_dev, is_c45,
				   MDIO_C45_READ, phy_id, devad);
	पूर्ण

	/* Step 5: रुकोting क्रम MDIO_COMMAND_REG 's mdio_start==0,*/
	/* check क्रम पढ़ो or ग_लिखो opt is finished */
	ret = hns_mdio_रुको_पढ़ोy(bus);
	अगर (ret) अणु
		dev_err(&bus->dev, "MDIO bus is busy\n");
		वापस ret;
	पूर्ण

	reg_val = MDIO_GET_REG_BIT(mdio_dev, MDIO_STA_REG, MDIO_STATE_STA_B);
	अगर (reg_val) अणु
		dev_err(&bus->dev, " ERROR! MDIO Read failed!\n");
		वापस -EBUSY;
	पूर्ण

	/* Step 6; get out data*/
	reg_val = (u16)MDIO_GET_REG_FIELD(mdio_dev, MDIO_RDATA_REG,
					  MDIO_RDATA_DATA_M, MDIO_RDATA_DATA_S);

	वापस reg_val;
पूर्ण

/**
 * hns_mdio_reset - reset mdio bus
 * @bus: mdio bus
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा hns_mdio_device *mdio_dev = (काष्ठा hns_mdio_device *)bus->priv;
	स्थिर काष्ठा hns_mdio_sc_reg *sc_reg;
	पूर्णांक ret;

	अगर (dev_of_node(bus->parent)) अणु
		अगर (!mdio_dev->subctrl_vbase) अणु
			dev_err(&bus->dev, "mdio sys ctl reg has not maped\n");
			वापस -ENODEV;
		पूर्ण

		sc_reg = &mdio_dev->sc_reg;
		/* 1. reset req, and पढ़ो reset st check */
		ret = mdio_sc_cfg_reg_ग_लिखो(mdio_dev, sc_reg->mdio_reset_req,
					    0x1, sc_reg->mdio_reset_st, 0x1,
					    MDIO_CHECK_SET_ST);
		अगर (ret) अणु
			dev_err(&bus->dev, "MDIO reset fail\n");
			वापस ret;
		पूर्ण

		/* 2. dis clk, and पढ़ो clk st check */
		ret = mdio_sc_cfg_reg_ग_लिखो(mdio_dev, sc_reg->mdio_clk_dis,
					    0x1, sc_reg->mdio_clk_st, 0x1,
					    MDIO_CHECK_CLR_ST);
		अगर (ret) अणु
			dev_err(&bus->dev, "MDIO dis clk fail\n");
			वापस ret;
		पूर्ण

		/* 3. reset dreq, and पढ़ो reset st check */
		ret = mdio_sc_cfg_reg_ग_लिखो(mdio_dev, sc_reg->mdio_reset_dreq,
					    0x1, sc_reg->mdio_reset_st, 0x1,
					    MDIO_CHECK_CLR_ST);
		अगर (ret) अणु
			dev_err(&bus->dev, "MDIO dis clk fail\n");
			वापस ret;
		पूर्ण

		/* 4. en clk, and पढ़ो clk st check */
		ret = mdio_sc_cfg_reg_ग_लिखो(mdio_dev, sc_reg->mdio_clk_en,
					    0x1, sc_reg->mdio_clk_st, 0x1,
					    MDIO_CHECK_SET_ST);
		अगर (ret)
			dev_err(&bus->dev, "MDIO en clk fail\n");
	पूर्ण अन्यथा अगर (is_acpi_node(bus->parent->fwnode)) अणु
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(bus->parent),
					 "_RST", शून्य, शून्य);
		अगर (ACPI_FAILURE(s)) अणु
			dev_err(&bus->dev, "Reset failed, return:%#x\n", s);
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&bus->dev, "Can not get cfg data from DT or ACPI\n");
		ret = -ENXIO;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * hns_mdio_probe - probe mdio device
 * @pdev: mdio platक्रमm device
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hns_mdio_device *mdio_dev;
	काष्ठा mii_bus *new_bus;
	पूर्णांक ret;

	अगर (!pdev) अणु
		dev_err(शून्य, "pdev is NULL!\r\n");
		वापस -ENODEV;
	पूर्ण

	mdio_dev = devm_kzalloc(&pdev->dev, माप(*mdio_dev), GFP_KERNEL);
	अगर (!mdio_dev)
		वापस -ENOMEM;

	new_bus = devm_mdiobus_alloc(&pdev->dev);
	अगर (!new_bus) अणु
		dev_err(&pdev->dev, "mdiobus_alloc fail!\n");
		वापस -ENOMEM;
	पूर्ण

	new_bus->name = MDIO_BUS_NAME;
	new_bus->पढ़ो = hns_mdio_पढ़ो;
	new_bus->ग_लिखो = hns_mdio_ग_लिखो;
	new_bus->reset = hns_mdio_reset;
	new_bus->priv = mdio_dev;
	new_bus->parent = &pdev->dev;

	mdio_dev->vbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdio_dev->vbase)) अणु
		ret = PTR_ERR(mdio_dev->vbase);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, new_bus);
	snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "%s-%s", "Mii",
		 dev_name(&pdev->dev));
	अगर (dev_of_node(&pdev->dev)) अणु
		काष्ठा of_phandle_args reg_args;

		ret = of_parse_phandle_with_fixed_args(pdev->dev.of_node,
						       "subctrl-vbase",
						       4,
						       0,
						       &reg_args);
		अगर (!ret) अणु
			mdio_dev->subctrl_vbase =
				syscon_node_to_regmap(reg_args.np);
			अगर (IS_ERR(mdio_dev->subctrl_vbase)) अणु
				dev_warn(&pdev->dev, "syscon_node_to_regmap error\n");
				mdio_dev->subctrl_vbase = शून्य;
			पूर्ण अन्यथा अणु
				अगर (reg_args.args_count == 4) अणु
					mdio_dev->sc_reg.mdio_clk_en =
						(u16)reg_args.args[0];
					mdio_dev->sc_reg.mdio_clk_dis =
						(u16)reg_args.args[0] + 4;
					mdio_dev->sc_reg.mdio_reset_req =
						(u16)reg_args.args[1];
					mdio_dev->sc_reg.mdio_reset_dreq =
						(u16)reg_args.args[1] + 4;
					mdio_dev->sc_reg.mdio_clk_st =
						(u16)reg_args.args[2];
					mdio_dev->sc_reg.mdio_reset_st =
						(u16)reg_args.args[3];
				पूर्ण अन्यथा अणु
					/* क्रम compatible */
					mdio_dev->sc_reg.mdio_clk_en =
						MDIO_SC_CLK_EN;
					mdio_dev->sc_reg.mdio_clk_dis =
						MDIO_SC_CLK_DIS;
					mdio_dev->sc_reg.mdio_reset_req =
						MDIO_SC_RESET_REQ;
					mdio_dev->sc_reg.mdio_reset_dreq =
						MDIO_SC_RESET_DREQ;
					mdio_dev->sc_reg.mdio_clk_st =
						MDIO_SC_CLK_ST;
					mdio_dev->sc_reg.mdio_reset_st =
						MDIO_SC_RESET_ST;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(&pdev->dev, "find syscon ret = %#x\n", ret);
			mdio_dev->subctrl_vbase = शून्य;
		पूर्ण

		ret = of_mdiobus_रेजिस्टर(new_bus, pdev->dev.of_node);
	पूर्ण अन्यथा अगर (is_acpi_node(pdev->dev.fwnode)) अणु
		/* Clear all the IRQ properties */
		स_रखो(new_bus->irq, PHY_POLL, 4 * PHY_MAX_ADDR);

		/* Mask out all PHYs from स्वतः probing. */
		new_bus->phy_mask = ~0;

		/* Register the MDIO bus */
		ret = mdiobus_रेजिस्टर(new_bus);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Can not get cfg data from DT or ACPI\n");
		ret = -ENXIO;
	पूर्ण

	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot register as MDIO bus!\n");
		platक्रमm_set_drvdata(pdev, शून्य);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hns_mdio_हटाओ - हटाओ mdio device
 * @pdev: mdio platक्रमm device
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus;

	bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus);
	platक्रमm_set_drvdata(pdev, शून्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hns_mdio_match[] = अणु
	अणु.compatible = "hisilicon,mdio"पूर्ण,
	अणु.compatible = "hisilicon,hns-mdio"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hns_mdio_match);

अटल स्थिर काष्ठा acpi_device_id hns_mdio_acpi_match[] = अणु
	अणु "HISI0141", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hns_mdio_acpi_match);

अटल काष्ठा platक्रमm_driver hns_mdio_driver = अणु
	.probe = hns_mdio_probe,
	.हटाओ = hns_mdio_हटाओ,
	.driver = अणु
		   .name = MDIO_DRV_NAME,
		   .of_match_table = hns_mdio_match,
		   .acpi_match_table = ACPI_PTR(hns_mdio_acpi_match),
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(hns_mdio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huawei Tech. Co., Ltd.");
MODULE_DESCRIPTION("Hisilicon HNS MDIO driver");
MODULE_ALIAS("platform:" MDIO_DRV_NAME);
