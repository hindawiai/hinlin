<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI da8xx master peripheral priority driver
 *
 * Copyright (C) 2016 BayLibre SAS
 *
 * Author:
 *   Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/regmap.h>

/*
 * REVISIT: Linux करोesn't have a good framework क्रम the kind of perक्रमmance
 * knobs this driver controls. We can't use device tree properties as it deals
 * with hardware configuration rather than description. We also करोn't want to
 * commit to मुख्यtaining some अक्रमom sysfs attributes.
 *
 * For now we just hardcode the रेजिस्टर values क्रम the boards that need
 * some changes (as is the हाल क्रम the LCD controller on da850-lcdk - the
 * first board we support here). When linux माला_लो an appropriate framework,
 * we'll easily convert the driver to it.
 */

#घोषणा DA8XX_MSTPRI0_OFFSET		0
#घोषणा DA8XX_MSTPRI1_OFFSET		4
#घोषणा DA8XX_MSTPRI2_OFFSET		8

क्रमागत अणु
	DA8XX_MSTPRI_ARM_I = 0,
	DA8XX_MSTPRI_ARM_D,
	DA8XX_MSTPRI_UPP,
	DA8XX_MSTPRI_SATA,
	DA8XX_MSTPRI_PRU0,
	DA8XX_MSTPRI_PRU1,
	DA8XX_MSTPRI_EDMA30TC0,
	DA8XX_MSTPRI_EDMA30TC1,
	DA8XX_MSTPRI_EDMA31TC0,
	DA8XX_MSTPRI_VPIF_DMA_0,
	DA8XX_MSTPRI_VPIF_DMA_1,
	DA8XX_MSTPRI_EMAC,
	DA8XX_MSTPRI_USB0CFG,
	DA8XX_MSTPRI_USB0CDMA,
	DA8XX_MSTPRI_UHPI,
	DA8XX_MSTPRI_USB1,
	DA8XX_MSTPRI_LCDC,
पूर्ण;

काष्ठा da8xx_mstpri_descr अणु
	पूर्णांक reg;
	पूर्णांक shअगरt;
	पूर्णांक mask;
पूर्ण;

अटल स्थिर काष्ठा da8xx_mstpri_descr da8xx_mstpri_priority_list[] = अणु
	[DA8XX_MSTPRI_ARM_I] = अणु
		.reg = DA8XX_MSTPRI0_OFFSET,
		.shअगरt = 0,
		.mask = 0x0000000f,
	पूर्ण,
	[DA8XX_MSTPRI_ARM_D] = अणु
		.reg = DA8XX_MSTPRI0_OFFSET,
		.shअगरt = 4,
		.mask = 0x000000f0,
	पूर्ण,
	[DA8XX_MSTPRI_UPP] = अणु
		.reg = DA8XX_MSTPRI0_OFFSET,
		.shअगरt = 16,
		.mask = 0x000f0000,
	पूर्ण,
	[DA8XX_MSTPRI_SATA] = अणु
		.reg = DA8XX_MSTPRI0_OFFSET,
		.shअगरt = 20,
		.mask = 0x00f00000,
	पूर्ण,
	[DA8XX_MSTPRI_PRU0] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 0,
		.mask = 0x0000000f,
	पूर्ण,
	[DA8XX_MSTPRI_PRU1] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 4,
		.mask = 0x000000f0,
	पूर्ण,
	[DA8XX_MSTPRI_EDMA30TC0] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 8,
		.mask = 0x00000f00,
	पूर्ण,
	[DA8XX_MSTPRI_EDMA30TC1] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 12,
		.mask = 0x0000f000,
	पूर्ण,
	[DA8XX_MSTPRI_EDMA31TC0] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 16,
		.mask = 0x000f0000,
	पूर्ण,
	[DA8XX_MSTPRI_VPIF_DMA_0] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 24,
		.mask = 0x0f000000,
	पूर्ण,
	[DA8XX_MSTPRI_VPIF_DMA_1] = अणु
		.reg = DA8XX_MSTPRI1_OFFSET,
		.shअगरt = 28,
		.mask = 0xf0000000,
	पूर्ण,
	[DA8XX_MSTPRI_EMAC] = अणु
		.reg = DA8XX_MSTPRI2_OFFSET,
		.shअगरt = 0,
		.mask = 0x0000000f,
	पूर्ण,
	[DA8XX_MSTPRI_USB0CFG] = अणु
		.reg = DA8XX_MSTPRI2_OFFSET,
		.shअगरt = 8,
		.mask = 0x00000f00,
	पूर्ण,
	[DA8XX_MSTPRI_USB0CDMA] = अणु
		.reg = DA8XX_MSTPRI2_OFFSET,
		.shअगरt = 12,
		.mask = 0x0000f000,
	पूर्ण,
	[DA8XX_MSTPRI_UHPI] = अणु
		.reg = DA8XX_MSTPRI2_OFFSET,
		.shअगरt = 20,
		.mask = 0x00f00000,
	पूर्ण,
	[DA8XX_MSTPRI_USB1] = अणु
		.reg = DA8XX_MSTPRI2_OFFSET,
		.shअगरt = 24,
		.mask = 0x0f000000,
	पूर्ण,
	[DA8XX_MSTPRI_LCDC] = अणु
		.reg = DA8XX_MSTPRI2_OFFSET,
		.shअगरt = 28,
		.mask = 0xf0000000,
	पूर्ण,
पूर्ण;

काष्ठा da8xx_mstpri_priority अणु
	पूर्णांक which;
	u32 val;
पूर्ण;

काष्ठा da8xx_mstpri_board_priorities अणु
	स्थिर अक्षर *board;
	स्थिर काष्ठा da8xx_mstpri_priority *priorities;
	माप_प्रकार numprio;
पूर्ण;

/*
 * Default memory settings of da850 करो not meet the throughput/latency
 * requirements of tilcdc. This results in the image displayed being
 * incorrect and the following warning being displayed by the LCDC
 * drm driver:
 *
 *   tilcdc da8xx_lcdc.0: tilcdc_crtc_irq(0x00000020): FIFO underfow
 */
अटल स्थिर काष्ठा da8xx_mstpri_priority da850_lcdk_priorities[] = अणु
	अणु
		.which = DA8XX_MSTPRI_LCDC,
		.val = 0,
	पूर्ण,
	अणु
		.which = DA8XX_MSTPRI_EDMA30TC1,
		.val = 0,
	पूर्ण,
	अणु
		.which = DA8XX_MSTPRI_EDMA30TC0,
		.val = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा da8xx_mstpri_board_priorities da8xx_mstpri_board_confs[] = अणु
	अणु
		.board = "ti,da850-lcdk",
		.priorities = da850_lcdk_priorities,
		.numprio = ARRAY_SIZE(da850_lcdk_priorities),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा da8xx_mstpri_board_priorities *
da8xx_mstpri_get_board_prio(व्योम)
अणु
	स्थिर काष्ठा da8xx_mstpri_board_priorities *board_prio;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(da8xx_mstpri_board_confs); i++) अणु
		board_prio = &da8xx_mstpri_board_confs[i];

		अगर (of_machine_is_compatible(board_prio->board))
			वापस board_prio;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक da8xx_mstpri_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा da8xx_mstpri_board_priorities *prio_list;
	स्थिर काष्ठा da8xx_mstpri_descr *prio_descr;
	स्थिर काष्ठा da8xx_mstpri_priority *prio;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	व्योम __iomem *mstpri;
	u32 reg;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mstpri = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mstpri)) अणु
		dev_err(dev, "unable to map MSTPRI registers\n");
		वापस PTR_ERR(mstpri);
	पूर्ण

	prio_list = da8xx_mstpri_get_board_prio();
	अगर (!prio_list) अणु
		dev_err(dev, "no master priorities defined for this board\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < prio_list->numprio; i++) अणु
		prio = &prio_list->priorities[i];
		prio_descr = &da8xx_mstpri_priority_list[prio->which];

		अगर (prio_descr->reg + माप(u32) > resource_size(res)) अणु
			dev_warn(dev, "register offset out of range\n");
			जारी;
		पूर्ण

		reg = पढ़ोl(mstpri + prio_descr->reg);
		reg &= ~prio_descr->mask;
		reg |= prio->val << prio_descr->shअगरt;

		ग_लिखोl(reg, mstpri + prio_descr->reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id da8xx_mstpri_of_match[] = अणु
	अणु .compatible = "ti,da850-mstpri", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver da8xx_mstpri_driver = अणु
	.probe = da8xx_mstpri_probe,
	.driver = अणु
		.name = "da8xx-mstpri",
		.of_match_table = da8xx_mstpri_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da8xx_mstpri_driver);

MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_DESCRIPTION("TI da8xx master peripheral priority driver");
MODULE_LICENSE("GPL v2");
