<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the ICST307 VCO घड़ी found in the ARM Reference designs.
 * We wrap the custom पूर्णांकerface from <यंत्र/hardware/icst.h> पूर्णांकo the generic
 * घड़ी framework.
 *
 * Copyright (C) 2012-2015 Linus Walleij
 *
 * TODO: when all ARM reference designs are migrated to generic घड़ीs, the
 * ICST घड़ी code from the ARM tree should probably be merged पूर्णांकo this
 * file.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "icst.h"
#समावेश "clk-icst.h"

/* Magic unlocking token used on all Versatile boards */
#घोषणा VERSATILE_LOCK_VAL	0xA05F

#घोषणा VERSATILE_AUX_OSC_BITS 0x7FFFF
#घोषणा INTEGRATOR_AP_CM_BITS 0xFF
#घोषणा INTEGRATOR_AP_SYS_BITS 0xFF
#घोषणा INTEGRATOR_CP_CM_CORE_BITS 0x7FF
#घोषणा INTEGRATOR_CP_CM_MEM_BITS 0x7FF000

#घोषणा INTEGRATOR_AP_PCI_25_33_MHZ BIT(8)

/**
 * काष्ठा clk_icst - ICST VCO घड़ी wrapper
 * @hw: corresponding घड़ी hardware entry
 * @map: रेजिस्टर map
 * @vcoreg_off: VCO रेजिस्टर address
 * @lockreg_off: VCO lock रेजिस्टर address
 * @params: parameters क्रम this ICST instance
 * @rate: current rate
 * @ctype: the type of control रेजिस्टर क्रम the ICST
 */
काष्ठा clk_icst अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *map;
	u32 vcoreg_off;
	u32 lockreg_off;
	काष्ठा icst_params *params;
	अचिन्हित दीर्घ rate;
	क्रमागत icst_control_type ctype;
पूर्ण;

#घोषणा to_icst(_hw) container_of(_hw, काष्ठा clk_icst, hw)

/**
 * vco_get() - get ICST VCO settings from a certain ICST
 * @icst: the ICST घड़ी to get
 * @vco: the VCO काष्ठा to वापस the value in
 */
अटल पूर्णांक vco_get(काष्ठा clk_icst *icst, काष्ठा icst_vco *vco)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(icst->map, icst->vcoreg_off, &val);
	अगर (ret)
		वापस ret;

	/*
	 * The Integrator/AP core घड़ी can only access the low eight
	 * bits of the v PLL भागider. Bit 8 is tied low and always zero,
	 * r is hardwired to 22 and output भागider s is hardwired to 1
	 * (भागide by 2) according to the करोcument
	 * "Integrator CM926EJ-S, CM946E-S, CM966E-S, CM1026EJ-S and
	 * CM1136JF-S User Guide" ARM DUI 0138E, page 3-13 thru 3-14.
	 */
	अगर (icst->ctype == ICST_INTEGRATOR_AP_CM) अणु
		vco->v = val & INTEGRATOR_AP_CM_BITS;
		vco->r = 22;
		vco->s = 1;
		वापस 0;
	पूर्ण

	/*
	 * The Integrator/AP प्रणाली घड़ी on the base board can only
	 * access the low eight bits of the v PLL भागider. Bit 8 is tied low
	 * and always zero, r is hardwired to 46, and the output भागider is
	 * hardwired to 3 (भागide by 4) according to the करोcument
	 * "Integrator AP ASIC Development Motherboard" ARM DUI 0098B,
	 * page 3-16.
	 */
	अगर (icst->ctype == ICST_INTEGRATOR_AP_SYS) अणु
		vco->v = val & INTEGRATOR_AP_SYS_BITS;
		vco->r = 46;
		vco->s = 3;
		वापस 0;
	पूर्ण

	/*
	 * The Integrator/AP PCI घड़ी is using an odd pattern to create
	 * the child घड़ी, basically a single bit called DIVX/Y is used
	 * to select between two dअगरferent hardwired values: setting the
	 * bit to 0 yields v = 17, r = 22 and OD = 1, whereas setting the
	 * bit to 1 yields v = 14, r = 14 and OD = 1 giving the frequencies
	 * 33 or 25 MHz respectively.
	 */
	अगर (icst->ctype == ICST_INTEGRATOR_AP_PCI) अणु
		bool भागxy = !!(val & INTEGRATOR_AP_PCI_25_33_MHZ);

		vco->v = भागxy ? 17 : 14;
		vco->r = भागxy ? 22 : 14;
		vco->s = 1;
		वापस 0;
	पूर्ण

	/*
	 * The Integrator/CP core घड़ी can access the low eight bits
	 * of the v PLL भागider. Bit 8 is tied low and always zero,
	 * r is hardwired to 22 and the output भागider s is accessible
	 * in bits 8 thru 10 according to the करोcument
	 * "Integrator/CM940T, CM920T, CM740T, and CM720T User Guide"
	 * ARM DUI 0157A, page 3-20 thru 3-23 and 4-10.
	 */
	अगर (icst->ctype == ICST_INTEGRATOR_CP_CM_CORE) अणु
		vco->v = val & 0xFF;
		vco->r = 22;
		vco->s = (val >> 8) & 7;
		वापस 0;
	पूर्ण

	अगर (icst->ctype == ICST_INTEGRATOR_CP_CM_MEM) अणु
		vco->v = (val >> 12) & 0xFF;
		vco->r = 22;
		vco->s = (val >> 20) & 7;
		वापस 0;
	पूर्ण

	vco->v = val & 0x1ff;
	vco->r = (val >> 9) & 0x7f;
	vco->s = (val >> 16) & 03;
	वापस 0;
पूर्ण

/**
 * vco_set() - commit changes to an ICST VCO
 * @icst: the ICST घड़ी to set
 * @vco: the VCO काष्ठा to set the changes from
 */
अटल पूर्णांक vco_set(काष्ठा clk_icst *icst, काष्ठा icst_vco vco)
अणु
	u32 mask;
	u32 val;
	पूर्णांक ret;

	/* Mask the bits used by the VCO */
	चयन (icst->ctype) अणु
	हाल ICST_INTEGRATOR_AP_CM:
		mask = INTEGRATOR_AP_CM_BITS;
		val = vco.v & 0xFF;
		अगर (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		अगर (vco.s != 1)
			pr_err("ICST error: tried to use VOD != 1\n");
		अगर (vco.r != 22)
			pr_err("ICST error: tried to use RDW != 22\n");
		अवरोध;
	हाल ICST_INTEGRATOR_AP_SYS:
		mask = INTEGRATOR_AP_SYS_BITS;
		val = vco.v & 0xFF;
		अगर (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		अगर (vco.s != 3)
			pr_err("ICST error: tried to use VOD != 1\n");
		अगर (vco.r != 46)
			pr_err("ICST error: tried to use RDW != 22\n");
		अवरोध;
	हाल ICST_INTEGRATOR_CP_CM_CORE:
		mask = INTEGRATOR_CP_CM_CORE_BITS; /* Uses 12 bits */
		val = (vco.v & 0xFF) | vco.s << 8;
		अगर (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		अगर (vco.r != 22)
			pr_err("ICST error: tried to use RDW != 22\n");
		अवरोध;
	हाल ICST_INTEGRATOR_CP_CM_MEM:
		mask = INTEGRATOR_CP_CM_MEM_BITS; /* Uses 12 bits */
		val = ((vco.v & 0xFF) << 12) | (vco.s << 20);
		अगर (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		अगर (vco.r != 22)
			pr_err("ICST error: tried to use RDW != 22\n");
		अवरोध;
	शेष:
		/* Regular auxilary oscillator */
		mask = VERSATILE_AUX_OSC_BITS;
		val = vco.v | (vco.r << 9) | (vco.s << 16);
		अवरोध;
	पूर्ण

	pr_debug("ICST: new val = 0x%08x\n", val);

	/* This magic unlocks the VCO so it can be controlled */
	ret = regmap_ग_लिखो(icst->map, icst->lockreg_off, VERSATILE_LOCK_VAL);
	अगर (ret)
		वापस ret;
	ret = regmap_update_bits(icst->map, icst->vcoreg_off, mask, val);
	अगर (ret)
		वापस ret;
	/* This locks the VCO again */
	ret = regmap_ग_लिखो(icst->map, icst->lockreg_off, 0);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ icst_recalc_rate(काष्ठा clk_hw *hw,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_icst *icst = to_icst(hw);
	काष्ठा icst_vco vco;
	पूर्णांक ret;

	अगर (parent_rate)
		icst->params->ref = parent_rate;
	ret = vco_get(icst, &vco);
	अगर (ret) अणु
		pr_err("ICST: could not get VCO setting\n");
		वापस 0;
	पूर्ण
	icst->rate = icst_hz(icst->params, vco);
	वापस icst->rate;
पूर्ण

अटल दीर्घ icst_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_icst *icst = to_icst(hw);
	काष्ठा icst_vco vco;

	अगर (icst->ctype == ICST_INTEGRATOR_AP_CM ||
	    icst->ctype == ICST_INTEGRATOR_CP_CM_CORE) अणु
		अगर (rate <= 12000000)
			वापस 12000000;
		अगर (rate >= 160000000)
			वापस 160000000;
		/* Slam to बंदst megahertz */
		वापस DIV_ROUND_CLOSEST(rate, 1000000) * 1000000;
	पूर्ण

	अगर (icst->ctype == ICST_INTEGRATOR_CP_CM_MEM) अणु
		अगर (rate <= 6000000)
			वापस 6000000;
		अगर (rate >= 66000000)
			वापस 66000000;
		/* Slam to बंदst 0.5 megahertz */
		वापस DIV_ROUND_CLOSEST(rate, 500000) * 500000;
	पूर्ण

	अगर (icst->ctype == ICST_INTEGRATOR_AP_SYS) अणु
		/* Divides between 3 and 50 MHz in steps of 0.25 MHz */
		अगर (rate <= 3000000)
			वापस 3000000;
		अगर (rate >= 50000000)
			वापस 5000000;
		/* Slam to बंदst 0.25 MHz */
		वापस DIV_ROUND_CLOSEST(rate, 250000) * 250000;
	पूर्ण

	अगर (icst->ctype == ICST_INTEGRATOR_AP_PCI) अणु
		/*
		 * If we're below or less than halfway from 25 to 33 MHz
		 * select 25 MHz
		 */
		अगर (rate <= 25000000 || rate < 29000000)
			वापस 25000000;
		/* Else just वापस the शेष frequency */
		वापस 33000000;
	पूर्ण

	vco = icst_hz_to_vco(icst->params, rate);
	वापस icst_hz(icst->params, vco);
पूर्ण

अटल पूर्णांक icst_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_icst *icst = to_icst(hw);
	काष्ठा icst_vco vco;

	अगर (icst->ctype == ICST_INTEGRATOR_AP_PCI) अणु
		/* This घड़ी is especially primitive */
		अचिन्हित पूर्णांक val;
		पूर्णांक ret;

		अगर (rate == 25000000) अणु
			val = 0;
		पूर्ण अन्यथा अगर (rate == 33000000) अणु
			val = INTEGRATOR_AP_PCI_25_33_MHZ;
		पूर्ण अन्यथा अणु
			pr_err("ICST: cannot set PCI frequency %lu\n",
			       rate);
			वापस -EINVAL;
		पूर्ण
		ret = regmap_ग_लिखो(icst->map, icst->lockreg_off,
				   VERSATILE_LOCK_VAL);
		अगर (ret)
			वापस ret;
		ret = regmap_update_bits(icst->map, icst->vcoreg_off,
					 INTEGRATOR_AP_PCI_25_33_MHZ,
					 val);
		अगर (ret)
			वापस ret;
		/* This locks the VCO again */
		ret = regmap_ग_लिखो(icst->map, icst->lockreg_off, 0);
		अगर (ret)
			वापस ret;
		वापस 0;
	पूर्ण

	अगर (parent_rate)
		icst->params->ref = parent_rate;
	vco = icst_hz_to_vco(icst->params, rate);
	icst->rate = icst_hz(icst->params, vco);
	वापस vco_set(icst, vco);
पूर्ण

अटल स्थिर काष्ठा clk_ops icst_ops = अणु
	.recalc_rate = icst_recalc_rate,
	.round_rate = icst_round_rate,
	.set_rate = icst_set_rate,
पूर्ण;

काष्ठा clk *icst_clk_setup(काष्ठा device *dev,
			   स्थिर काष्ठा clk_icst_desc *desc,
			   स्थिर अक्षर *name,
			   स्थिर अक्षर *parent_name,
			   काष्ठा regmap *map,
			   क्रमागत icst_control_type ctype)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_icst *icst;
	काष्ठा clk_init_data init;
	काष्ठा icst_params *pclone;

	icst = kzalloc(माप(*icst), GFP_KERNEL);
	अगर (!icst)
		वापस ERR_PTR(-ENOMEM);

	pclone = kmemdup(desc->params, माप(*pclone), GFP_KERNEL);
	अगर (!pclone) अणु
		kमुक्त(icst);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	init.name = name;
	init.ops = &icst_ops;
	init.flags = 0;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	icst->map = map;
	icst->hw.init = &init;
	icst->params = pclone;
	icst->vcoreg_off = desc->vco_offset;
	icst->lockreg_off = desc->lock_offset;
	icst->ctype = ctype;

	clk = clk_रेजिस्टर(dev, &icst->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(pclone);
		kमुक्त(icst);
	पूर्ण

	वापस clk;
पूर्ण
EXPORT_SYMBOL_GPL(icst_clk_setup);

काष्ठा clk *icst_clk_रेजिस्टर(काष्ठा device *dev,
			स्थिर काष्ठा clk_icst_desc *desc,
			स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name,
			व्योम __iomem *base)
अणु
	काष्ठा regmap_config icst_regmap_conf = अणु
		.reg_bits = 32,
		.val_bits = 32,
		.reg_stride = 4,
	पूर्ण;
	काष्ठा regmap *map;

	map = regmap_init_mmio(dev, base, &icst_regmap_conf);
	अगर (IS_ERR(map)) अणु
		pr_err("could not initialize ICST regmap\n");
		वापस ERR_CAST(map);
	पूर्ण
	वापस icst_clk_setup(dev, desc, name, parent_name, map,
			      ICST_VERSATILE);
पूर्ण
EXPORT_SYMBOL_GPL(icst_clk_रेजिस्टर);

#अगर_घोषित CONFIG_OF
/*
 * In a device tree, an memory-mapped ICST घड़ी appear as a child
 * of a syscon node. Assume this and probe it only as a child of a
 * syscon.
 */

अटल स्थिर काष्ठा icst_params icst525_params = अणु
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min		= 8,
	.vd_max		= 263,
	.rd_min		= 3,
	.rd_max		= 65,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल स्थिर काष्ठा icst_params icst307_params = अणु
	.vco_max	= ICST307_VCO_MAX,
	.vco_min	= ICST307_VCO_MIN,
	.vd_min		= 4 + 8,
	.vd_max		= 511 + 8,
	.rd_min		= 1 + 2,
	.rd_max		= 127 + 2,
	.s2भाग		= icst307_s2भाग,
	.idx2s		= icst307_idx2s,
पूर्ण;

/*
 * The core modules on the Integrator/AP and Integrator/CP have
 * especially crippled ICST525 control.
 */
अटल स्थिर काष्ठा icst_params icst525_apcp_cm_params = अणु
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	/* Minimum 12 MHz, VDW = 4 */
	.vd_min		= 12,
	/*
	 * Maximum 160 MHz, VDW = 152 क्रम all core modules, but
	 * CM926EJ-S, CM1026EJ-S and CM1136JF-S can actually
	 * go to 200 MHz (max VDW = 192).
	 */
	.vd_max		= 192,
	/* r is hardcoded to 22 and this is the actual भागisor, +2 */
	.rd_min		= 24,
	.rd_max		= 24,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल स्थिर काष्ठा icst_params icst525_ap_sys_params = अणु
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	/* Minimum 3 MHz, VDW = 4 */
	.vd_min		= 3,
	/* Maximum 50 MHz, VDW = 192 */
	.vd_max		= 50,
	/* r is hardcoded to 46 and this is the actual भागisor, +2 */
	.rd_min		= 48,
	.rd_max		= 48,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल स्थिर काष्ठा icst_params icst525_ap_pci_params = अणु
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	/* Minimum 25 MHz */
	.vd_min		= 25,
	/* Maximum 33 MHz */
	.vd_max		= 33,
	/* r is hardcoded to 14 or 22 and this is the actual भागisors +2 */
	.rd_min		= 16,
	.rd_max		= 24,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल व्योम __init of_syscon_icst_setup(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;
	काष्ठा regmap *map;
	काष्ठा clk_icst_desc icst_desc;
	स्थिर अक्षर *name = np->name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *regclk;
	क्रमागत icst_control_type ctype;

	/* We करो not release this reference, we are using it perpetually */
	parent = of_get_parent(np);
	अगर (!parent) अणु
		pr_err("no parent node for syscon ICST clock\n");
		वापस;
	पूर्ण
	map = syscon_node_to_regmap(parent);
	अगर (IS_ERR(map)) अणु
		pr_err("no regmap for syscon ICST clock parent\n");
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "vco-offset", &icst_desc.vco_offset)) अणु
		pr_err("no VCO register offset for ICST clock\n");
		वापस;
	पूर्ण
	अगर (of_property_पढ़ो_u32(np, "lock-offset", &icst_desc.lock_offset)) अणु
		pr_err("no lock register offset for ICST clock\n");
		वापस;
	पूर्ण

	अगर (of_device_is_compatible(np, "arm,syscon-icst525")) अणु
		icst_desc.params = &icst525_params;
		ctype = ICST_VERSATILE;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,syscon-icst307")) अणु
		icst_desc.params = &icst307_params;
		ctype = ICST_VERSATILE;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,syscon-icst525-integratorap-cm")) अणु
		icst_desc.params = &icst525_apcp_cm_params;
		ctype = ICST_INTEGRATOR_AP_CM;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,syscon-icst525-integratorap-sys")) अणु
		icst_desc.params = &icst525_ap_sys_params;
		ctype = ICST_INTEGRATOR_AP_SYS;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,syscon-icst525-integratorap-pci")) अणु
		icst_desc.params = &icst525_ap_pci_params;
		ctype = ICST_INTEGRATOR_AP_PCI;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,syscon-icst525-integratorcp-cm-core")) अणु
		icst_desc.params = &icst525_apcp_cm_params;
		ctype = ICST_INTEGRATOR_CP_CM_CORE;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "arm,syscon-icst525-integratorcp-cm-mem")) अणु
		icst_desc.params = &icst525_apcp_cm_params;
		ctype = ICST_INTEGRATOR_CP_CM_MEM;
	पूर्ण अन्यथा अणु
		pr_err("unknown ICST clock %s\n", name);
		वापस;
	पूर्ण

	/* Parent घड़ी name is not the same as node parent */
	parent_name = of_clk_get_parent_name(np, 0);

	regclk = icst_clk_setup(शून्य, &icst_desc, name, parent_name, map, ctype);
	अगर (IS_ERR(regclk)) अणु
		pr_err("error setting up syscon ICST clock %s\n", name);
		वापस;
	पूर्ण
	of_clk_add_provider(np, of_clk_src_simple_get, regclk);
	pr_debug("registered syscon ICST clock %s\n", name);
पूर्ण

CLK_OF_DECLARE(arm_syscon_icst525_clk,
	       "arm,syscon-icst525", of_syscon_icst_setup);
CLK_OF_DECLARE(arm_syscon_icst307_clk,
	       "arm,syscon-icst307", of_syscon_icst_setup);
CLK_OF_DECLARE(arm_syscon_पूर्णांकegratorap_cm_clk,
	       "arm,syscon-icst525-integratorap-cm", of_syscon_icst_setup);
CLK_OF_DECLARE(arm_syscon_पूर्णांकegratorap_sys_clk,
	       "arm,syscon-icst525-integratorap-sys", of_syscon_icst_setup);
CLK_OF_DECLARE(arm_syscon_पूर्णांकegratorap_pci_clk,
	       "arm,syscon-icst525-integratorap-pci", of_syscon_icst_setup);
CLK_OF_DECLARE(arm_syscon_पूर्णांकegratorcp_cm_core_clk,
	       "arm,syscon-icst525-integratorcp-cm-core", of_syscon_icst_setup);
CLK_OF_DECLARE(arm_syscon_पूर्णांकegratorcp_cm_mem_clk,
	       "arm,syscon-icst525-integratorcp-cm-mem", of_syscon_icst_setup);
#पूर्ण_अगर
