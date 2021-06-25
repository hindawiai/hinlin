<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Versatile OF physmap driver add-on
 *
 * Copyright (c) 2016, Linaro Limited
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>
#समावेश "physmap-versatile.h"

अटल काष्ठा regmap *syscon_regmap;

क्रमागत versatile_flashprot अणु
	INTEGRATOR_AP_FLASHPROT,
	INTEGRATOR_CP_FLASHPROT,
	VERSATILE_FLASHPROT,
	REALVIEW_FLASHPROT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id syscon_match[] = अणु
	अणु
		.compatible = "arm,integrator-ap-syscon",
		.data = (व्योम *)INTEGRATOR_AP_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,integrator-cp-syscon",
		.data = (व्योम *)INTEGRATOR_CP_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,core-module-versatile",
		.data = (व्योम *)VERSATILE_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,realview-eb-syscon",
		.data = (व्योम *)REALVIEW_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb1176-syscon",
		.data = (व्योम *)REALVIEW_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb11mp-syscon",
		.data = (व्योम *)REALVIEW_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pba8-syscon",
		.data = (व्योम *)REALVIEW_FLASHPROT,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pbx-syscon",
		.data = (व्योम *)REALVIEW_FLASHPROT,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*
 * Flash protection handling क्रम the Integrator/AP
 */
#घोषणा INTEGRATOR_SC_CTRLS_OFFSET	0x08
#घोषणा INTEGRATOR_SC_CTRLC_OFFSET	0x0C
#घोषणा INTEGRATOR_SC_CTRL_FLVPPEN	BIT(1)
#घोषणा INTEGRATOR_SC_CTRL_FLWP		BIT(2)

#घोषणा INTEGRATOR_EBI_CSR1_OFFSET	0x04
/* The manual says bit 2, the code says bit 3, trust the code */
#घोषणा INTEGRATOR_EBI_WRITE_ENABLE	BIT(3)
#घोषणा INTEGRATOR_EBI_LOCK_OFFSET	0x20
#घोषणा INTEGRATOR_EBI_LOCK_VAL		0xA05F

अटल स्थिर काष्ठा of_device_id ebi_match[] = अणु
	अणु .compatible = "arm,external-bus-interface"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक ap_flash_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *ebi;
	व्योम __iomem *ebi_base;
	u32 val;
	पूर्णांक ret;

	/* Look up the EBI */
	ebi = of_find_matching_node(शून्य, ebi_match);
	अगर (!ebi) अणु
		वापस -ENODEV;
	पूर्ण
	ebi_base = of_iomap(ebi, 0);
	अगर (!ebi_base)
		वापस -ENODEV;

	/* Clear VPP and ग_लिखो protection bits */
	ret = regmap_ग_लिखो(syscon_regmap,
		INTEGRATOR_SC_CTRLC_OFFSET,
		INTEGRATOR_SC_CTRL_FLVPPEN | INTEGRATOR_SC_CTRL_FLWP);
	अगर (ret)
		dev_err(&pdev->dev, "error clearing Integrator VPP/WP\n");

	/* Unlock the EBI */
	ग_लिखोl(INTEGRATOR_EBI_LOCK_VAL, ebi_base + INTEGRATOR_EBI_LOCK_OFFSET);

	/* Enable ग_लिखो cycles on the EBI, CSR1 (flash) */
	val = पढ़ोl(ebi_base + INTEGRATOR_EBI_CSR1_OFFSET);
	val |= INTEGRATOR_EBI_WRITE_ENABLE;
	ग_लिखोl(val, ebi_base + INTEGRATOR_EBI_CSR1_OFFSET);

	/* Lock the EBI again */
	ग_लिखोl(0, ebi_base + INTEGRATOR_EBI_LOCK_OFFSET);
	iounmap(ebi_base);

	वापस 0;
पूर्ण

अटल व्योम ap_flash_set_vpp(काष्ठा map_info *map, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on) अणु
		ret = regmap_ग_लिखो(syscon_regmap,
			INTEGRATOR_SC_CTRLS_OFFSET,
			INTEGRATOR_SC_CTRL_FLVPPEN | INTEGRATOR_SC_CTRL_FLWP);
		अगर (ret)
			pr_err("error enabling AP VPP\n");
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(syscon_regmap,
			INTEGRATOR_SC_CTRLC_OFFSET,
			INTEGRATOR_SC_CTRL_FLVPPEN | INTEGRATOR_SC_CTRL_FLWP);
		अगर (ret)
			pr_err("error disabling AP VPP\n");
	पूर्ण
पूर्ण

/*
 * Flash protection handling क्रम the Integrator/CP
 */

#घोषणा INTCP_FLASHPROG_OFFSET		0x04
#घोषणा CINTEGRATOR_FLVPPEN		BIT(0)
#घोषणा CINTEGRATOR_FLWREN		BIT(1)
#घोषणा CINTEGRATOR_FLMASK		BIT(0)|BIT(1)

अटल व्योम cp_flash_set_vpp(काष्ठा map_info *map, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on) अणु
		ret = regmap_update_bits(syscon_regmap,
				INTCP_FLASHPROG_OFFSET,
				CINTEGRATOR_FLMASK,
				CINTEGRATOR_FLVPPEN | CINTEGRATOR_FLWREN);
		अगर (ret)
			pr_err("error setting CP VPP\n");
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(syscon_regmap,
				INTCP_FLASHPROG_OFFSET,
				CINTEGRATOR_FLMASK,
				0);
		अगर (ret)
			pr_err("error setting CP VPP\n");
	पूर्ण
पूर्ण

/*
 * Flash protection handling क्रम the Versatiles and RealViews
 */

#घोषणा VERSATILE_SYS_FLASH_OFFSET            0x4C

अटल व्योम versatile_flash_set_vpp(काष्ठा map_info *map, पूर्णांक on)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(syscon_regmap, VERSATILE_SYS_FLASH_OFFSET,
				 0x01, !!on);
	अगर (ret)
		pr_err("error setting Versatile VPP\n");
पूर्ण

पूर्णांक of_flash_probe_versatile(काष्ठा platक्रमm_device *pdev,
			     काष्ठा device_node *np,
			     काष्ठा map_info *map)
अणु
	काष्ठा device_node *sysnp;
	स्थिर काष्ठा of_device_id *devid;
	काष्ठा regmap *rmap;
	अटल क्रमागत versatile_flashprot versatile_flashprot;
	पूर्णांक ret;

	/* Not all flash chips use this protection line */
	अगर (!of_device_is_compatible(np, "arm,versatile-flash"))
		वापस 0;

	/* For first chip probed, look up the syscon regmap */
	अगर (!syscon_regmap) अणु
		sysnp = of_find_matching_node_and_match(शून्य,
							syscon_match,
							&devid);
		अगर (!sysnp)
			वापस -ENODEV;

		versatile_flashprot = (क्रमागत versatile_flashprot)devid->data;
		rmap = syscon_node_to_regmap(sysnp);
		अगर (IS_ERR(rmap))
			वापस PTR_ERR(rmap);

		syscon_regmap = rmap;
	पूर्ण

	चयन (versatile_flashprot) अणु
	हाल INTEGRATOR_AP_FLASHPROT:
		ret = ap_flash_init(pdev);
		अगर (ret)
			वापस ret;
		map->set_vpp = ap_flash_set_vpp;
		dev_info(&pdev->dev, "Integrator/AP flash protection\n");
		अवरोध;
	हाल INTEGRATOR_CP_FLASHPROT:
		map->set_vpp = cp_flash_set_vpp;
		dev_info(&pdev->dev, "Integrator/CP flash protection\n");
		अवरोध;
	हाल VERSATILE_FLASHPROT:
	हाल REALVIEW_FLASHPROT:
		map->set_vpp = versatile_flash_set_vpp;
		dev_info(&pdev->dev, "versatile/realview flash protection\n");
		अवरोध;
	शेष:
		dev_info(&pdev->dev, "device marked as Versatile flash "
			 "but no system controller was found\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
