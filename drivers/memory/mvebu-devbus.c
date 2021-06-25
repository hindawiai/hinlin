<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell EBU SoC Device Bus Controller
 * (memory controller क्रम NOR/न_अंकD/SRAM/FPGA devices)
 *
 * Copyright (C) 2013-2014 Marvell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/mbus.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

/* Register definitions */
#घोषणा ARMADA_DEV_WIDTH_SHIFT		30
#घोषणा ARMADA_BADR_SKEW_SHIFT		28
#घोषणा ARMADA_RD_HOLD_SHIFT		23
#घोषणा ARMADA_ACC_NEXT_SHIFT		17
#घोषणा ARMADA_RD_SETUP_SHIFT		12
#घोषणा ARMADA_ACC_FIRST_SHIFT		6

#घोषणा ARMADA_SYNC_ENABLE_SHIFT	24
#घोषणा ARMADA_WR_HIGH_SHIFT		16
#घोषणा ARMADA_WR_LOW_SHIFT		8

#घोषणा ARMADA_READ_PARAM_OFFSET	0x0
#घोषणा ARMADA_WRITE_PARAM_OFFSET	0x4

#घोषणा ORION_RESERVED			(0x2 << 30)
#घोषणा ORION_BADR_SKEW_SHIFT		28
#घोषणा ORION_WR_HIGH_EXT_BIT		BIT(27)
#घोषणा ORION_WR_HIGH_EXT_MASK		0x8
#घोषणा ORION_WR_LOW_EXT_BIT		BIT(26)
#घोषणा ORION_WR_LOW_EXT_MASK		0x8
#घोषणा ORION_ALE_WR_EXT_BIT		BIT(25)
#घोषणा ORION_ALE_WR_EXT_MASK		0x8
#घोषणा ORION_ACC_NEXT_EXT_BIT		BIT(24)
#घोषणा ORION_ACC_NEXT_EXT_MASK		0x10
#घोषणा ORION_ACC_FIRST_EXT_BIT		BIT(23)
#घोषणा ORION_ACC_FIRST_EXT_MASK	0x10
#घोषणा ORION_TURN_OFF_EXT_BIT		BIT(22)
#घोषणा ORION_TURN_OFF_EXT_MASK		0x8
#घोषणा ORION_DEV_WIDTH_SHIFT		20
#घोषणा ORION_WR_HIGH_SHIFT		17
#घोषणा ORION_WR_HIGH_MASK		0x7
#घोषणा ORION_WR_LOW_SHIFT		14
#घोषणा ORION_WR_LOW_MASK		0x7
#घोषणा ORION_ALE_WR_SHIFT		11
#घोषणा ORION_ALE_WR_MASK		0x7
#घोषणा ORION_ACC_NEXT_SHIFT		7
#घोषणा ORION_ACC_NEXT_MASK		0xF
#घोषणा ORION_ACC_FIRST_SHIFT		3
#घोषणा ORION_ACC_FIRST_MASK		0xF
#घोषणा ORION_TURN_OFF_SHIFT		0
#घोषणा ORION_TURN_OFF_MASK		0x7

काष्ठा devbus_पढ़ो_params अणु
	u32 bus_width;
	u32 badr_skew;
	u32 turn_off;
	u32 acc_first;
	u32 acc_next;
	u32 rd_setup;
	u32 rd_hold;
पूर्ण;

काष्ठा devbus_ग_लिखो_params अणु
	u32 sync_enable;
	u32 wr_high;
	u32 wr_low;
	u32 ale_wr;
पूर्ण;

काष्ठा devbus अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	अचिन्हित दीर्घ tick_ps;
पूर्ण;

अटल पूर्णांक get_timing_param_ps(काष्ठा devbus *devbus,
			       काष्ठा device_node *node,
			       स्थिर अक्षर *name,
			       u32 *ticks)
अणु
	u32 समय_ps;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(node, name, &समय_ps);
	अगर (err < 0) अणु
		dev_err(devbus->dev, "%pOF has no '%s' property\n",
			node, name);
		वापस err;
	पूर्ण

	*ticks = (समय_ps + devbus->tick_ps - 1) / devbus->tick_ps;

	dev_dbg(devbus->dev, "%s: %u ps -> 0x%x\n",
		name, समय_ps, *ticks);
	वापस 0;
पूर्ण

अटल पूर्णांक devbus_get_timing_params(काष्ठा devbus *devbus,
				    काष्ठा device_node *node,
				    काष्ठा devbus_पढ़ो_params *r,
				    काष्ठा devbus_ग_लिखो_params *w)
अणु
	पूर्णांक err;

	err = of_property_पढ़ो_u32(node, "devbus,bus-width", &r->bus_width);
	अगर (err < 0) अणु
		dev_err(devbus->dev,
			"%pOF has no 'devbus,bus-width' property\n",
			node);
		वापस err;
	पूर्ण

	/*
	 * The bus width is encoded पूर्णांकo the रेजिस्टर as 0 क्रम 8 bits,
	 * and 1 क्रम 16 bits, so we करो the necessary conversion here.
	 */
	अगर (r->bus_width == 8) अणु
		r->bus_width = 0;
	पूर्ण अन्यथा अगर (r->bus_width == 16) अणु
		r->bus_width = 1;
	पूर्ण अन्यथा अणु
		dev_err(devbus->dev, "invalid bus width %d\n", r->bus_width);
		वापस -EINVAL;
	पूर्ण

	err = get_timing_param_ps(devbus, node, "devbus,badr-skew-ps",
				  &r->badr_skew);
	अगर (err < 0)
		वापस err;

	err = get_timing_param_ps(devbus, node, "devbus,turn-off-ps",
				  &r->turn_off);
	अगर (err < 0)
		वापस err;

	err = get_timing_param_ps(devbus, node, "devbus,acc-first-ps",
				  &r->acc_first);
	अगर (err < 0)
		वापस err;

	err = get_timing_param_ps(devbus, node, "devbus,acc-next-ps",
				  &r->acc_next);
	अगर (err < 0)
		वापस err;

	अगर (of_device_is_compatible(devbus->dev->of_node, "marvell,mvebu-devbus")) अणु
		err = get_timing_param_ps(devbus, node, "devbus,rd-setup-ps",
					  &r->rd_setup);
		अगर (err < 0)
			वापस err;

		err = get_timing_param_ps(devbus, node, "devbus,rd-hold-ps",
					  &r->rd_hold);
		अगर (err < 0)
			वापस err;

		err = of_property_पढ़ो_u32(node, "devbus,sync-enable",
					   &w->sync_enable);
		अगर (err < 0) अणु
			dev_err(devbus->dev,
				"%pOF has no 'devbus,sync-enable' property\n",
				node);
			वापस err;
		पूर्ण
	पूर्ण

	err = get_timing_param_ps(devbus, node, "devbus,ale-wr-ps",
				  &w->ale_wr);
	अगर (err < 0)
		वापस err;

	err = get_timing_param_ps(devbus, node, "devbus,wr-low-ps",
				  &w->wr_low);
	अगर (err < 0)
		वापस err;

	err = get_timing_param_ps(devbus, node, "devbus,wr-high-ps",
				  &w->wr_high);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम devbus_orion_set_timing_params(काष्ठा devbus *devbus,
					  काष्ठा device_node *node,
					  काष्ठा devbus_पढ़ो_params *r,
					  काष्ठा devbus_ग_लिखो_params *w)
अणु
	u32 value;

	/*
	 * The hardware designers found it would be a good idea to
	 * split most of the values in the रेजिस्टर पूर्णांकo two fields:
	 * one containing all the low-order bits, and another one
	 * containing just the high-order bit. For all of those
	 * fields, we have to split the value पूर्णांकo these two parts.
	 */
	value =	(r->turn_off   & ORION_TURN_OFF_MASK)  << ORION_TURN_OFF_SHIFT  |
		(r->acc_first  & ORION_ACC_FIRST_MASK) << ORION_ACC_FIRST_SHIFT |
		(r->acc_next   & ORION_ACC_NEXT_MASK)  << ORION_ACC_NEXT_SHIFT  |
		(w->ale_wr     & ORION_ALE_WR_MASK)    << ORION_ALE_WR_SHIFT    |
		(w->wr_low     & ORION_WR_LOW_MASK)    << ORION_WR_LOW_SHIFT    |
		(w->wr_high    & ORION_WR_HIGH_MASK)   << ORION_WR_HIGH_SHIFT   |
		r->bus_width                           << ORION_DEV_WIDTH_SHIFT |
		((r->turn_off  & ORION_TURN_OFF_EXT_MASK)  ? ORION_TURN_OFF_EXT_BIT  : 0) |
		((r->acc_first & ORION_ACC_FIRST_EXT_MASK) ? ORION_ACC_FIRST_EXT_BIT : 0) |
		((r->acc_next  & ORION_ACC_NEXT_EXT_MASK)  ? ORION_ACC_NEXT_EXT_BIT  : 0) |
		((w->ale_wr    & ORION_ALE_WR_EXT_MASK)    ? ORION_ALE_WR_EXT_BIT    : 0) |
		((w->wr_low    & ORION_WR_LOW_EXT_MASK)    ? ORION_WR_LOW_EXT_BIT    : 0) |
		((w->wr_high   & ORION_WR_HIGH_EXT_MASK)   ? ORION_WR_HIGH_EXT_BIT   : 0) |
		(r->badr_skew << ORION_BADR_SKEW_SHIFT) |
		ORION_RESERVED;

	ग_लिखोl(value, devbus->base);
पूर्ण

अटल व्योम devbus_armada_set_timing_params(काष्ठा devbus *devbus,
					   काष्ठा device_node *node,
					   काष्ठा devbus_पढ़ो_params *r,
					   काष्ठा devbus_ग_लिखो_params *w)
अणु
	u32 value;

	/* Set पढ़ो timings */
	value = r->bus_width << ARMADA_DEV_WIDTH_SHIFT |
		r->badr_skew << ARMADA_BADR_SKEW_SHIFT |
		r->rd_hold   << ARMADA_RD_HOLD_SHIFT   |
		r->acc_next  << ARMADA_ACC_NEXT_SHIFT  |
		r->rd_setup  << ARMADA_RD_SETUP_SHIFT  |
		r->acc_first << ARMADA_ACC_FIRST_SHIFT |
		r->turn_off;

	dev_dbg(devbus->dev, "read parameters register 0x%p = 0x%x\n",
		devbus->base + ARMADA_READ_PARAM_OFFSET,
		value);

	ग_लिखोl(value, devbus->base + ARMADA_READ_PARAM_OFFSET);

	/* Set ग_लिखो timings */
	value = w->sync_enable  << ARMADA_SYNC_ENABLE_SHIFT |
		w->wr_low       << ARMADA_WR_LOW_SHIFT      |
		w->wr_high      << ARMADA_WR_HIGH_SHIFT     |
		w->ale_wr;

	dev_dbg(devbus->dev, "write parameters register: 0x%p = 0x%x\n",
		devbus->base + ARMADA_WRITE_PARAM_OFFSET,
		value);

	ग_लिखोl(value, devbus->base + ARMADA_WRITE_PARAM_OFFSET);
पूर्ण

अटल पूर्णांक mvebu_devbus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा devbus_पढ़ो_params r;
	काष्ठा devbus_ग_लिखो_params w;
	काष्ठा devbus *devbus;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	devbus = devm_kzalloc(&pdev->dev, माप(काष्ठा devbus), GFP_KERNEL);
	अगर (!devbus)
		वापस -ENOMEM;

	devbus->dev = dev;
	devbus->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(devbus->base))
		वापस PTR_ERR(devbus->base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);
	clk_prepare_enable(clk);

	/*
	 * Obtain घड़ी period in picoseconds,
	 * we need this in order to convert timing
	 * parameters from cycles to picoseconds.
	 */
	rate = clk_get_rate(clk) / 1000;
	devbus->tick_ps = 1000000000 / rate;

	dev_dbg(devbus->dev, "Setting timing parameter, tick is %lu ps\n",
		devbus->tick_ps);

	अगर (!of_property_पढ़ो_bool(node, "devbus,keep-config")) अणु
		/* Read the Device Tree node */
		err = devbus_get_timing_params(devbus, node, &r, &w);
		अगर (err < 0)
			वापस err;

		/* Set the new timing parameters */
		अगर (of_device_is_compatible(node, "marvell,orion-devbus"))
			devbus_orion_set_timing_params(devbus, node, &r, &w);
		अन्यथा
			devbus_armada_set_timing_params(devbus, node, &r, &w);
	पूर्ण

	/*
	 * We need to create a child device explicitly from here to
	 * guarantee that the child will be probed after the timing
	 * parameters क्रम the bus are written.
	 */
	err = of_platक्रमm_populate(node, शून्य, शून्य, dev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_devbus_of_match[] = अणु
	अणु .compatible = "marvell,mvebu-devbus" पूर्ण,
	अणु .compatible = "marvell,orion-devbus" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_devbus_of_match);

अटल काष्ठा platक्रमm_driver mvebu_devbus_driver = अणु
	.probe		= mvebu_devbus_probe,
	.driver		= अणु
		.name	= "mvebu-devbus",
		.of_match_table = mvebu_devbus_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mvebu_devbus_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mvebu_devbus_driver);
पूर्ण
module_init(mvebu_devbus_init);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ezequiel Garcia <ezequiel.garcia@free-electrons.com>");
MODULE_DESCRIPTION("Marvell EBU SoC Device Bus controller");
