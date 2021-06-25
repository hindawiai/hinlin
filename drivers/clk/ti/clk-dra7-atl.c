<शैली गुरु>
/*
 * DRA7 ATL (Audio Tracking Logic) घड़ी driver
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

#घोषणा DRA7_ATL_INSTANCES	4

#घोषणा DRA7_ATL_PPMR_REG(id)		(0x200 + (id * 0x80))
#घोषणा DRA7_ATL_BBSR_REG(id)		(0x204 + (id * 0x80))
#घोषणा DRA7_ATL_ATLCR_REG(id)		(0x208 + (id * 0x80))
#घोषणा DRA7_ATL_SWEN_REG(id)		(0x210 + (id * 0x80))
#घोषणा DRA7_ATL_BWSMUX_REG(id)		(0x214 + (id * 0x80))
#घोषणा DRA7_ATL_AWSMUX_REG(id)		(0x218 + (id * 0x80))
#घोषणा DRA7_ATL_PCLKMUX_REG(id)	(0x21c + (id * 0x80))

#घोषणा DRA7_ATL_SWEN			BIT(0)
#घोषणा DRA7_ATL_DIVIDER_MASK		(0x1f)
#घोषणा DRA7_ATL_PCLKMUX		BIT(0)
काष्ठा dra7_atl_घड़ी_info;

काष्ठा dra7_atl_desc अणु
	काष्ठा clk *clk;
	काष्ठा clk_hw hw;
	काष्ठा dra7_atl_घड़ी_info *cinfo;
	पूर्णांक id;

	bool probed;		/* the driver क्रम the IP has been loaded */
	bool valid;		/* configured */
	bool enabled;
	u32 bws;		/* Baseband Word Select Mux */
	u32 aws;		/* Audio Word Select Mux */
	u32 भागider;		/* Cached भागider value */
पूर्ण;

काष्ठा dra7_atl_घड़ी_info अणु
	काष्ठा device *dev;
	व्योम __iomem *iobase;

	काष्ठा dra7_atl_desc *cdesc;
पूर्ण;

#घोषणा to_atl_desc(_hw)	container_of(_hw, काष्ठा dra7_atl_desc, hw)

अटल अंतरभूत व्योम atl_ग_लिखो(काष्ठा dra7_atl_घड़ी_info *cinfo, u32 reg,
			     u32 val)
अणु
	__raw_ग_लिखोl(val, cinfo->iobase + reg);
पूर्ण

अटल अंतरभूत पूर्णांक atl_पढ़ो(काष्ठा dra7_atl_घड़ी_info *cinfo, u32 reg)
अणु
	वापस __raw_पढ़ोl(cinfo->iobase + reg);
पूर्ण

अटल पूर्णांक atl_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा dra7_atl_desc *cdesc = to_atl_desc(hw);

	अगर (!cdesc->probed)
		जाओ out;

	अगर (unlikely(!cdesc->valid))
		dev_warn(cdesc->cinfo->dev, "atl%d has not been configured\n",
			 cdesc->id);
	pm_runसमय_get_sync(cdesc->cinfo->dev);

	atl_ग_लिखो(cdesc->cinfo, DRA7_ATL_ATLCR_REG(cdesc->id),
		  cdesc->भागider - 1);
	atl_ग_लिखो(cdesc->cinfo, DRA7_ATL_SWEN_REG(cdesc->id), DRA7_ATL_SWEN);

out:
	cdesc->enabled = true;

	वापस 0;
पूर्ण

अटल व्योम atl_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा dra7_atl_desc *cdesc = to_atl_desc(hw);

	अगर (!cdesc->probed)
		जाओ out;

	atl_ग_लिखो(cdesc->cinfo, DRA7_ATL_SWEN_REG(cdesc->id), 0);
	pm_runसमय_put_sync(cdesc->cinfo->dev);

out:
	cdesc->enabled = false;
पूर्ण

अटल पूर्णांक atl_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा dra7_atl_desc *cdesc = to_atl_desc(hw);

	वापस cdesc->enabled;
पूर्ण

अटल अचिन्हित दीर्घ atl_clk_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dra7_atl_desc *cdesc = to_atl_desc(hw);

	वापस parent_rate / cdesc->भागider;
पूर्ण

अटल दीर्घ atl_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित भागider;

	भागider = (*parent_rate + rate / 2) / rate;
	अगर (भागider > DRA7_ATL_DIVIDER_MASK + 1)
		भागider = DRA7_ATL_DIVIDER_MASK + 1;

	वापस *parent_rate / भागider;
पूर्ण

अटल पूर्णांक atl_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dra7_atl_desc *cdesc;
	u32 भागider;

	अगर (!hw || !rate)
		वापस -EINVAL;

	cdesc = to_atl_desc(hw);
	भागider = ((parent_rate + rate / 2) / rate) - 1;
	अगर (भागider > DRA7_ATL_DIVIDER_MASK)
		भागider = DRA7_ATL_DIVIDER_MASK;

	cdesc->भागider = भागider + 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops atl_clk_ops = अणु
	.enable		= atl_clk_enable,
	.disable	= atl_clk_disable,
	.is_enabled	= atl_clk_is_enabled,
	.recalc_rate	= atl_clk_recalc_rate,
	.round_rate	= atl_clk_round_rate,
	.set_rate	= atl_clk_set_rate,
पूर्ण;

अटल व्योम __init of_dra7_atl_घड़ी_setup(काष्ठा device_node *node)
अणु
	काष्ठा dra7_atl_desc *clk_hw = शून्य;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	स्थिर अक्षर **parent_names = शून्य;
	काष्ठा clk *clk;

	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	अगर (!clk_hw) अणु
		pr_err("%s: could not allocate dra7_atl_desc\n", __func__);
		वापस;
	पूर्ण

	clk_hw->hw.init = &init;
	clk_hw->भागider = 1;
	init.name = node->name;
	init.ops = &atl_clk_ops;
	init.flags = CLK_IGNORE_UNUSED;
	init.num_parents = of_clk_get_parent_count(node);

	अगर (init.num_parents != 1) अणु
		pr_err("%s: atl clock %pOFn must have 1 parent\n", __func__,
		       node);
		जाओ cleanup;
	पूर्ण

	parent_names = kzalloc(माप(अक्षर *), GFP_KERNEL);

	अगर (!parent_names)
		जाओ cleanup;

	parent_names[0] = of_clk_get_parent_name(node, 0);

	init.parent_names = parent_names;

	clk = ti_clk_रेजिस्टर(शून्य, &clk_hw->hw, node->name);

	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		kमुक्त(parent_names);
		वापस;
	पूर्ण
cleanup:
	kमुक्त(parent_names);
	kमुक्त(clk_hw);
पूर्ण
CLK_OF_DECLARE(dra7_atl_घड़ी, "ti,dra7-atl-clock", of_dra7_atl_घड़ी_setup);

अटल पूर्णांक of_dra7_atl_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा dra7_atl_घड़ी_info *cinfo;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!node)
		वापस -ENODEV;

	cinfo = devm_kzalloc(&pdev->dev, माप(*cinfo), GFP_KERNEL);
	अगर (!cinfo)
		वापस -ENOMEM;

	cinfo->iobase = of_iomap(node, 0);
	cinfo->dev = &pdev->dev;
	pm_runसमय_enable(cinfo->dev);

	pm_runसमय_get_sync(cinfo->dev);
	atl_ग_लिखो(cinfo, DRA7_ATL_PCLKMUX_REG(0), DRA7_ATL_PCLKMUX);

	क्रम (i = 0; i < DRA7_ATL_INSTANCES; i++) अणु
		काष्ठा device_node *cfg_node;
		अक्षर prop[5];
		काष्ठा dra7_atl_desc *cdesc;
		काष्ठा of_phandle_args clkspec;
		काष्ठा clk *clk;
		पूर्णांक rc;

		rc = of_parse_phandle_with_args(node, "ti,provided-clocks",
						शून्य, i, &clkspec);

		अगर (rc) अणु
			pr_err("%s: failed to lookup atl clock %d\n", __func__,
			       i);
			वापस -EINVAL;
		पूर्ण

		clk = of_clk_get_from_provider(&clkspec);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to get atl clock %d from provider\n",
			       __func__, i);
			वापस PTR_ERR(clk);
		पूर्ण

		cdesc = to_atl_desc(__clk_get_hw(clk));
		cdesc->cinfo = cinfo;
		cdesc->id = i;

		/* Get configuration क्रम the ATL instances */
		snम_लिखो(prop, माप(prop), "atl%u", i);
		cfg_node = of_get_child_by_name(node, prop);
		अगर (cfg_node) अणु
			ret = of_property_पढ़ो_u32(cfg_node, "bws",
						   &cdesc->bws);
			ret |= of_property_पढ़ो_u32(cfg_node, "aws",
						    &cdesc->aws);
			अगर (!ret) अणु
				cdesc->valid = true;
				atl_ग_लिखो(cinfo, DRA7_ATL_BWSMUX_REG(i),
					  cdesc->bws);
				atl_ग_लिखो(cinfo, DRA7_ATL_AWSMUX_REG(i),
					  cdesc->aws);
			पूर्ण
			of_node_put(cfg_node);
		पूर्ण

		cdesc->probed = true;
		/*
		 * Enable the घड़ी अगर it has been asked prior to loading the
		 * hw driver
		 */
		अगर (cdesc->enabled)
			atl_clk_enable(__clk_get_hw(clk));
	पूर्ण
	pm_runसमय_put_sync(cinfo->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_dra7_atl_clk_match_tbl[] = अणु
	अणु .compatible = "ti,dra7-atl", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver dra7_atl_clk_driver = अणु
	.driver = अणु
		.name = "dra7-atl",
		.suppress_bind_attrs = true,
		.of_match_table = of_dra7_atl_clk_match_tbl,
	पूर्ण,
	.probe = of_dra7_atl_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(dra7_atl_clk_driver);
