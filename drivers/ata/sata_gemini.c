<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cortina Systems Gemini SATA bridge add-on to Faraday FTIDE010
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/reset.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश "sata_gemini.h"

#घोषणा DRV_NAME "gemini_sata_bridge"

/**
 * काष्ठा sata_gemini - a state container क्रम a Gemini SATA bridge
 * @dev: the containing device
 * @base: remapped I/O memory base
 * @muxmode: the current muxing mode
 * @ide_pins: अगर the device is using the plain IDE पूर्णांकerface pins
 * @sata_bridge: अगर the device enables the SATA bridge
 * @sata0_reset: SATA0 reset handler
 * @sata1_reset: SATA1 reset handler
 * @sata0_pclk: SATA0 PCLK handler
 * @sata1_pclk: SATA1 PCLK handler
 */
काष्ठा sata_gemini अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	क्रमागत gemini_muxmode muxmode;
	bool ide_pins;
	bool sata_bridge;
	काष्ठा reset_control *sata0_reset;
	काष्ठा reset_control *sata1_reset;
	काष्ठा clk *sata0_pclk;
	काष्ठा clk *sata1_pclk;
पूर्ण;

/* Miscellaneous Control Register */
#घोषणा GEMINI_GLOBAL_MISC_CTRL		0x30
/*
 * Values of IDE IOMUX bits in the misc control रेजिस्टर
 *
 * Bits 26:24 are "IDE IO Select", which decides what SATA
 * adapters are connected to which of the two IDE/ATA
 * controllers in the Gemini. We can connect the two IDE blocks
 * to one SATA adapter each, both acting as master, or one IDE
 * blocks to two SATA adapters so the IDE block can act in a
 * master/slave configuration.
 *
 * We also bring out dअगरferent blocks on the actual IDE
 * pins (not SATA pins) अगर (and only अगर) these are muxed in.
 *
 * 111-100 - Reserved
 * Mode 0: 000 - ata0 master <-> sata0
 *               ata1 master <-> sata1
 *               ata0 slave पूर्णांकerface brought out on IDE pads
 * Mode 1: 001 - ata0 master <-> sata0
 *               ata1 master <-> sata1
 *               ata1 slave पूर्णांकerface brought out on IDE pads
 * Mode 2: 010 - ata1 master <-> sata1
 *               ata1 slave  <-> sata0
 *               ata0 master and slave पूर्णांकerfaces brought out
 *                    on IDE pads
 * Mode 3: 011 - ata0 master <-> sata0
 *               ata1 slave  <-> sata1
 *               ata1 master and slave पूर्णांकerfaces brought out
 *                    on IDE pads
 */
#घोषणा GEMINI_IDE_IOMUX_MASK			(7 << 24)
#घोषणा GEMINI_IDE_IOMUX_MODE0			(0 << 24)
#घोषणा GEMINI_IDE_IOMUX_MODE1			(1 << 24)
#घोषणा GEMINI_IDE_IOMUX_MODE2			(2 << 24)
#घोषणा GEMINI_IDE_IOMUX_MODE3			(3 << 24)
#घोषणा GEMINI_IDE_IOMUX_SHIFT			(24)

/*
 * Registers directly controlling the PATA<->SATA adapters
 */
#घोषणा GEMINI_SATA_ID				0x00
#घोषणा GEMINI_SATA_PHY_ID			0x04
#घोषणा GEMINI_SATA0_STATUS			0x08
#घोषणा GEMINI_SATA1_STATUS			0x0c
#घोषणा GEMINI_SATA0_CTRL			0x18
#घोषणा GEMINI_SATA1_CTRL			0x1c

#घोषणा GEMINI_SATA_STATUS_BIST_DONE		BIT(5)
#घोषणा GEMINI_SATA_STATUS_BIST_OK		BIT(4)
#घोषणा GEMINI_SATA_STATUS_PHY_READY		BIT(0)

#घोषणा GEMINI_SATA_CTRL_PHY_BIST_EN		BIT(14)
#घोषणा GEMINI_SATA_CTRL_PHY_FORCE_IDLE		BIT(13)
#घोषणा GEMINI_SATA_CTRL_PHY_FORCE_READY	BIT(12)
#घोषणा GEMINI_SATA_CTRL_PHY_AFE_LOOP_EN	BIT(10)
#घोषणा GEMINI_SATA_CTRL_PHY_DIG_LOOP_EN	BIT(9)
#घोषणा GEMINI_SATA_CTRL_HOTPLUG_DETECT_EN	BIT(4)
#घोषणा GEMINI_SATA_CTRL_ATAPI_EN		BIT(3)
#घोषणा GEMINI_SATA_CTRL_BUS_WITH_20		BIT(2)
#घोषणा GEMINI_SATA_CTRL_SLAVE_EN		BIT(1)
#घोषणा GEMINI_SATA_CTRL_EN			BIT(0)

/*
 * There is only ever one instance of this bridge on a प्रणाली,
 * so create a singleton so that the FTIDE010 instances can grab
 * a reference to it.
 */
अटल काष्ठा sata_gemini *sg_singleton;

काष्ठा sata_gemini *gemini_sata_bridge_get(व्योम)
अणु
	अगर (sg_singleton)
		वापस sg_singleton;
	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण
EXPORT_SYMBOL(gemini_sata_bridge_get);

bool gemini_sata_bridge_enabled(काष्ठा sata_gemini *sg, bool is_ata1)
अणु
	अगर (!sg->sata_bridge)
		वापस false;
	/*
	 * In muxmode 2 and 3 one of the ATA controllers is
	 * actually not connected to any SATA bridge.
	 */
	अगर ((sg->muxmode == GEMINI_MUXMODE_2) &&
	    !is_ata1)
		वापस false;
	अगर ((sg->muxmode == GEMINI_MUXMODE_3) &&
	    is_ata1)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(gemini_sata_bridge_enabled);

क्रमागत gemini_muxmode gemini_sata_get_muxmode(काष्ठा sata_gemini *sg)
अणु
	वापस sg->muxmode;
पूर्ण
EXPORT_SYMBOL(gemini_sata_get_muxmode);

अटल पूर्णांक gemini_sata_setup_bridge(काष्ठा sata_gemini *sg,
				    अचिन्हित पूर्णांक bridge)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * 1);
	bool bridge_online;
	u32 val;

	अगर (bridge == 0) अणु
		val = GEMINI_SATA_CTRL_HOTPLUG_DETECT_EN | GEMINI_SATA_CTRL_EN;
		/* SATA0 slave mode is only used in muxmode 2 */
		अगर (sg->muxmode == GEMINI_MUXMODE_2)
			val |= GEMINI_SATA_CTRL_SLAVE_EN;
		ग_लिखोl(val, sg->base + GEMINI_SATA0_CTRL);
	पूर्ण अन्यथा अणु
		val = GEMINI_SATA_CTRL_HOTPLUG_DETECT_EN | GEMINI_SATA_CTRL_EN;
		/* SATA1 slave mode is only used in muxmode 3 */
		अगर (sg->muxmode == GEMINI_MUXMODE_3)
			val |= GEMINI_SATA_CTRL_SLAVE_EN;
		ग_लिखोl(val, sg->base + GEMINI_SATA1_CTRL);
	पूर्ण

	/* Venकरोr code रुकोs 10 ms here */
	msleep(10);

	/* Wait क्रम PHY to become पढ़ोy */
	करो अणु
		msleep(100);

		अगर (bridge == 0)
			val = पढ़ोl(sg->base + GEMINI_SATA0_STATUS);
		अन्यथा
			val = पढ़ोl(sg->base + GEMINI_SATA1_STATUS);
		अगर (val & GEMINI_SATA_STATUS_PHY_READY)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	bridge_online = !!(val & GEMINI_SATA_STATUS_PHY_READY);

	dev_info(sg->dev, "SATA%d PHY %s\n", bridge,
		 bridge_online ? "ready" : "not ready");

	वापस bridge_online ? 0: -ENODEV;
पूर्ण

पूर्णांक gemini_sata_start_bridge(काष्ठा sata_gemini *sg, अचिन्हित पूर्णांक bridge)
अणु
	काष्ठा clk *pclk;
	पूर्णांक ret;

	अगर (bridge == 0)
		pclk = sg->sata0_pclk;
	अन्यथा
		pclk = sg->sata1_pclk;
	clk_enable(pclk);
	msleep(10);

	/* Do not keep घड़ीing a bridge that is not online */
	ret = gemini_sata_setup_bridge(sg, bridge);
	अगर (ret)
		clk_disable(pclk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(gemini_sata_start_bridge);

व्योम gemini_sata_stop_bridge(काष्ठा sata_gemini *sg, अचिन्हित पूर्णांक bridge)
अणु
	अगर (bridge == 0)
		clk_disable(sg->sata0_pclk);
	अन्यथा अगर (bridge == 1)
		clk_disable(sg->sata1_pclk);
पूर्ण
EXPORT_SYMBOL(gemini_sata_stop_bridge);

पूर्णांक gemini_sata_reset_bridge(काष्ठा sata_gemini *sg,
			     अचिन्हित पूर्णांक bridge)
अणु
	अगर (bridge == 0)
		reset_control_reset(sg->sata0_reset);
	अन्यथा
		reset_control_reset(sg->sata1_reset);
	msleep(10);
	वापस gemini_sata_setup_bridge(sg, bridge);
पूर्ण
EXPORT_SYMBOL(gemini_sata_reset_bridge);

अटल पूर्णांक gemini_sata_bridge_init(काष्ठा sata_gemini *sg)
अणु
	काष्ठा device *dev = sg->dev;
	u32 sata_id, sata_phy_id;
	पूर्णांक ret;

	sg->sata0_pclk = devm_clk_get(dev, "SATA0_PCLK");
	अगर (IS_ERR(sg->sata0_pclk)) अणु
		dev_err(dev, "no SATA0 PCLK");
		वापस -ENODEV;
	पूर्ण
	sg->sata1_pclk = devm_clk_get(dev, "SATA1_PCLK");
	अगर (IS_ERR(sg->sata1_pclk)) अणु
		dev_err(dev, "no SATA1 PCLK");
		वापस -ENODEV;
	पूर्ण

	ret = clk_prepare_enable(sg->sata0_pclk);
	अगर (ret) अणु
		pr_err("failed to enable SATA0 PCLK\n");
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(sg->sata1_pclk);
	अगर (ret) अणु
		pr_err("failed to enable SATA1 PCLK\n");
		clk_disable_unprepare(sg->sata0_pclk);
		वापस ret;
	पूर्ण

	sg->sata0_reset = devm_reset_control_get_exclusive(dev, "sata0");
	अगर (IS_ERR(sg->sata0_reset)) अणु
		dev_err(dev, "no SATA0 reset controller\n");
		clk_disable_unprepare(sg->sata1_pclk);
		clk_disable_unprepare(sg->sata0_pclk);
		वापस PTR_ERR(sg->sata0_reset);
	पूर्ण
	sg->sata1_reset = devm_reset_control_get_exclusive(dev, "sata1");
	अगर (IS_ERR(sg->sata1_reset)) अणु
		dev_err(dev, "no SATA1 reset controller\n");
		clk_disable_unprepare(sg->sata1_pclk);
		clk_disable_unprepare(sg->sata0_pclk);
		वापस PTR_ERR(sg->sata1_reset);
	पूर्ण

	sata_id = पढ़ोl(sg->base + GEMINI_SATA_ID);
	sata_phy_id = पढ़ोl(sg->base + GEMINI_SATA_PHY_ID);
	sg->sata_bridge = true;
	clk_disable(sg->sata0_pclk);
	clk_disable(sg->sata1_pclk);

	dev_info(dev, "SATA ID %08x, PHY ID: %08x\n", sata_id, sata_phy_id);

	वापस 0;
पूर्ण

अटल पूर्णांक gemini_setup_ide_pins(काष्ठा device *dev)
अणु
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *ide_state;
	पूर्णांक ret;

	p = devm_pinctrl_get(dev);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	ide_state = pinctrl_lookup_state(p, "ide");
	अगर (IS_ERR(ide_state))
		वापस PTR_ERR(ide_state);

	ret = pinctrl_select_state(p, ide_state);
	अगर (ret) अणु
		dev_err(dev, "could not select IDE state\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gemini_sata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sata_gemini *sg;
	काष्ठा regmap *map;
	काष्ठा resource *res;
	क्रमागत gemini_muxmode muxmode;
	u32 gmode;
	u32 gmask;
	पूर्णांक ret;

	sg = devm_kzalloc(dev, माप(*sg), GFP_KERNEL);
	अगर (!sg)
		वापस -ENOMEM;
	sg->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	sg->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(sg->base))
		वापस PTR_ERR(sg->base);

	map = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "no global syscon\n");
		वापस PTR_ERR(map);
	पूर्ण

	/* Set up the SATA bridge अगर need be */
	अगर (of_property_पढ़ो_bool(np, "cortina,gemini-enable-sata-bridge")) अणु
		ret = gemini_sata_bridge_init(sg);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "cortina,gemini-enable-ide-pins"))
		sg->ide_pins = true;

	अगर (!sg->sata_bridge && !sg->ide_pins) अणु
		dev_err(dev, "neither SATA bridge or IDE output enabled\n");
		ret = -EINVAL;
		जाओ out_unprep_clk;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "cortina,gemini-ata-muxmode", &muxmode);
	अगर (ret) अणु
		dev_err(dev, "could not parse ATA muxmode\n");
		जाओ out_unprep_clk;
	पूर्ण
	अगर (muxmode > GEMINI_MUXMODE_3) अणु
		dev_err(dev, "illegal muxmode %d\n", muxmode);
		ret = -EINVAL;
		जाओ out_unprep_clk;
	पूर्ण
	sg->muxmode = muxmode;
	gmask = GEMINI_IDE_IOMUX_MASK;
	gmode = (muxmode << GEMINI_IDE_IOMUX_SHIFT);

	ret = regmap_update_bits(map, GEMINI_GLOBAL_MISC_CTRL, gmask, gmode);
	अगर (ret) अणु
		dev_err(dev, "unable to set up IDE muxing\n");
		ret = -ENODEV;
		जाओ out_unprep_clk;
	पूर्ण

	/*
	 * Route out the IDE pins अगर desired.
	 * This is करोne by looking up a special pin control state called
	 * "ide" that will route out the IDE pins.
	 */
	अगर (sg->ide_pins) अणु
		ret = gemini_setup_ide_pins(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_info(dev, "set up the Gemini IDE/SATA nexus\n");
	platक्रमm_set_drvdata(pdev, sg);
	sg_singleton = sg;

	वापस 0;

out_unprep_clk:
	अगर (sg->sata_bridge) अणु
		clk_unprepare(sg->sata1_pclk);
		clk_unprepare(sg->sata0_pclk);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gemini_sata_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sata_gemini *sg = platक्रमm_get_drvdata(pdev);

	अगर (sg->sata_bridge) अणु
		clk_unprepare(sg->sata1_pclk);
		clk_unprepare(sg->sata0_pclk);
	पूर्ण
	sg_singleton = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gemini_sata_of_match[] = अणु
	अणु
		.compatible = "cortina,gemini-sata-bridge",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver gemini_sata_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(gemini_sata_of_match),
	पूर्ण,
	.probe = gemini_sata_probe,
	.हटाओ = gemini_sata_हटाओ,
पूर्ण;
module_platक्रमm_driver(gemini_sata_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
