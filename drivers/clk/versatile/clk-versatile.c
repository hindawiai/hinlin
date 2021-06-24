<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clock driver क्रम the ARM Integrator/AP, Integrator/CP, Versatile AB and
 * Versatile PB boards.
 * Copyright (C) 2012 Linus Walleij
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "icst.h"
#समावेश "clk-icst.h"

#घोषणा INTEGRATOR_HDR_LOCK_OFFSET	0x14

#घोषणा VERSATILE_SYS_OSCCLCD_OFFSET	0x1c
#घोषणा VERSATILE_SYS_LOCK_OFFSET	0x20

/* Base offset क्रम the core module */
अटल व्योम __iomem *cm_base;

अटल स्थिर काष्ठा icst_params cp_auxosc_params = अणु
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min 	= 8,
	.vd_max 	= 263,
	.rd_min 	= 3,
	.rd_max 	= 65,
	.s2भाग		= icst525_s2भाग,
	.idx2s		= icst525_idx2s,
पूर्ण;

अटल स्थिर काष्ठा clk_icst_desc cm_auxosc_desc __initस्थिर = अणु
	.params = &cp_auxosc_params,
	.vco_offset = 0x1c,
	.lock_offset = INTEGRATOR_HDR_LOCK_OFFSET,
पूर्ण;

अटल स्थिर काष्ठा icst_params versatile_auxosc_params = अणु
	.vco_max	= ICST307_VCO_MAX,
	.vco_min	= ICST307_VCO_MIN,
	.vd_min		= 4 + 8,
	.vd_max		= 511 + 8,
	.rd_min		= 1 + 2,
	.rd_max		= 127 + 2,
	.s2भाग		= icst307_s2भाग,
	.idx2s		= icst307_idx2s,
पूर्ण;

अटल स्थिर काष्ठा clk_icst_desc versatile_auxosc_desc __initस्थिर = अणु
	.params = &versatile_auxosc_params,
	.vco_offset = VERSATILE_SYS_OSCCLCD_OFFSET,
	.lock_offset = VERSATILE_SYS_LOCK_OFFSET,
पूर्ण;
अटल व्योम __init cm_osc_setup(काष्ठा device_node *np,
				स्थिर काष्ठा clk_icst_desc *desc)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *parent_name;

	अगर (!cm_base) अणु
		/* Remap the core module base अगर not करोne yet */
		काष्ठा device_node *parent;

		parent = of_get_parent(np);
		अगर (!parent) अणु
			pr_err("no parent on core module clock\n");
			वापस;
		पूर्ण
		cm_base = of_iomap(parent, 0);
		of_node_put(parent);
		अगर (!cm_base) अणु
			pr_err("could not remap core module base\n");
			वापस;
		पूर्ण
	पूर्ण

	parent_name = of_clk_get_parent_name(np, 0);
	clk = icst_clk_रेजिस्टर(शून्य, desc, clk_name, parent_name, cm_base);
	अगर (!IS_ERR(clk))
		of_clk_add_provider(np, of_clk_src_simple_get, clk);
पूर्ण

अटल व्योम __init of_पूर्णांकegrator_cm_osc_setup(काष्ठा device_node *np)
अणु
	cm_osc_setup(np, &cm_auxosc_desc);
पूर्ण
CLK_OF_DECLARE(पूर्णांकegrator_cm_auxosc_clk,
	"arm,integrator-cm-auxosc", of_पूर्णांकegrator_cm_osc_setup);

अटल व्योम __init of_versatile_cm_osc_setup(काष्ठा device_node *np)
अणु
	cm_osc_setup(np, &versatile_auxosc_desc);
पूर्ण
CLK_OF_DECLARE(versatile_cm_auxosc_clk,
	       "arm,versatile-cm-auxosc", of_versatile_cm_osc_setup);
