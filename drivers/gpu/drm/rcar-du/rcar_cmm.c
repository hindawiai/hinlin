<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_cmm.c -- R-Car Display Unit Color Management Module
 *
 * Copyright (C) 2019 Jacopo Mondi <jacopo+renesas@jmondi.org>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_color_mgmt.h>

#समावेश "rcar_cmm.h"

#घोषणा CM2_LUT_CTRL		0x0000
#घोषणा CM2_LUT_CTRL_LUT_EN	BIT(0)
#घोषणा CM2_LUT_TBL_BASE	0x0600
#घोषणा CM2_LUT_TBL(__i)	(CM2_LUT_TBL_BASE + (__i) * 4)

काष्ठा rcar_cmm अणु
	व्योम __iomem *base;

	/*
	 * @lut:		1D-LUT state
	 * @lut.enabled:	1D-LUT enabled flag
	 */
	काष्ठा अणु
		bool enabled;
	पूर्ण lut;
पूर्ण;

अटल अंतरभूत पूर्णांक rcar_cmm_पढ़ो(काष्ठा rcar_cmm *rcmm, u32 reg)
अणु
	वापस ioपढ़ो32(rcmm->base + reg);
पूर्ण

अटल अंतरभूत व्योम rcar_cmm_ग_लिखो(काष्ठा rcar_cmm *rcmm, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, rcmm->base + reg);
पूर्ण

/*
 * rcar_cmm_lut_ग_लिखो() - Scale the DRM LUT table entries to hardware precision
 *			  and ग_लिखो to the CMM रेजिस्टरs
 * @rcmm: Poपूर्णांकer to the CMM device
 * @drm_lut: Poपूर्णांकer to the DRM LUT table
 */
अटल व्योम rcar_cmm_lut_ग_लिखो(काष्ठा rcar_cmm *rcmm,
			       स्थिर काष्ठा drm_color_lut *drm_lut)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < CM2_LUT_SIZE; ++i) अणु
		u32 entry = drm_color_lut_extract(drm_lut[i].red, 8) << 16
			  | drm_color_lut_extract(drm_lut[i].green, 8) << 8
			  | drm_color_lut_extract(drm_lut[i].blue, 8);

		rcar_cmm_ग_लिखो(rcmm, CM2_LUT_TBL(i), entry);
	पूर्ण
पूर्ण

/*
 * rcar_cmm_setup() - Configure the CMM unit
 * @pdev: The platक्रमm device associated with the CMM instance
 * @config: The CMM unit configuration
 *
 * Configure the CMM unit with the given configuration. Currently enabling,
 * disabling and programming of the 1-D LUT unit is supported.
 *
 * As rcar_cmm_setup() accesses the CMM रेजिस्टरs the unit should be घातered
 * and its functional घड़ी enabled. To guarantee this, beक्रमe any call to
 * this function is made, the CMM unit has to be enabled by calling
 * rcar_cmm_enable() first.
 *
 * TODO: Add support क्रम LUT द्विगुन buffer operations to aव्योम updating the
 * LUT table entries जबतक a frame is being displayed.
 */
पूर्णांक rcar_cmm_setup(काष्ठा platक्रमm_device *pdev,
		   स्थिर काष्ठा rcar_cmm_config *config)
अणु
	काष्ठा rcar_cmm *rcmm = platक्रमm_get_drvdata(pdev);

	/* Disable LUT अगर no table is provided. */
	अगर (!config->lut.table) अणु
		अगर (rcmm->lut.enabled) अणु
			rcar_cmm_ग_लिखो(rcmm, CM2_LUT_CTRL, 0);
			rcmm->lut.enabled = false;
		पूर्ण

		वापस 0;
	पूर्ण

	/* Enable LUT and program the new gamma table values. */
	अगर (!rcmm->lut.enabled) अणु
		rcar_cmm_ग_लिखो(rcmm, CM2_LUT_CTRL, CM2_LUT_CTRL_LUT_EN);
		rcmm->lut.enabled = true;
	पूर्ण

	rcar_cmm_lut_ग_लिखो(rcmm, config->lut.table);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_cmm_setup);

/*
 * rcar_cmm_enable() - Enable the CMM unit
 * @pdev: The platक्रमm device associated with the CMM instance
 *
 * When the output of the corresponding DU channel is routed to the CMM unit,
 * the unit shall be enabled beक्रमe the DU channel is started, and reमुख्य
 * enabled until the channel is stopped. The CMM unit shall be disabled with
 * rcar_cmm_disable().
 *
 * Calls to rcar_cmm_enable() and rcar_cmm_disable() are not reference-counted.
 * It is an error to attempt to enable an alपढ़ोy enabled CMM unit, or to
 * attempt to disable a disabled unit.
 */
पूर्णांक rcar_cmm_enable(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_cmm_enable);

/*
 * rcar_cmm_disable() - Disable the CMM unit
 * @pdev: The platक्रमm device associated with the CMM instance
 *
 * See rcar_cmm_enable() क्रम usage inक्रमmation.
 *
 * Disabling the CMM unit disable all the पूर्णांकernal processing blocks. The CMM
 * state shall thus be restored with rcar_cmm_setup() when re-enabling the CMM
 * unit after the next rcar_cmm_enable() call.
 */
व्योम rcar_cmm_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_cmm *rcmm = platक्रमm_get_drvdata(pdev);

	rcar_cmm_ग_लिखो(rcmm, CM2_LUT_CTRL, 0);
	rcmm->lut.enabled = false;

	pm_runसमय_put(&pdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(rcar_cmm_disable);

/*
 * rcar_cmm_init() - Initialize the CMM unit
 * @pdev: The platक्रमm device associated with the CMM instance
 *
 * Return: 0 on success, -EPROBE_DEFER अगर the CMM is not available yet,
 *         -ENODEV अगर the DRM_RCAR_CMM config option is disabled
 */
पूर्णांक rcar_cmm_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_cmm *rcmm = platक्रमm_get_drvdata(pdev);

	अगर (!rcmm)
		वापस -EPROBE_DEFER;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_cmm_init);

अटल पूर्णांक rcar_cmm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_cmm *rcmm;

	rcmm = devm_kzalloc(&pdev->dev, माप(*rcmm), GFP_KERNEL);
	अगर (!rcmm)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, rcmm);

	rcmm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rcmm->base))
		वापस PTR_ERR(rcmm->base);

	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_cmm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_cmm_of_table[] = अणु
	अणु .compatible = "renesas,rcar-gen3-cmm", पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-cmm", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_cmm_of_table);

अटल काष्ठा platक्रमm_driver rcar_cmm_platक्रमm_driver = अणु
	.probe		= rcar_cmm_probe,
	.हटाओ		= rcar_cmm_हटाओ,
	.driver		= अणु
		.name	= "rcar-cmm",
		.of_match_table = rcar_cmm_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rcar_cmm_platक्रमm_driver);

MODULE_AUTHOR("Jacopo Mondi <jacopo+renesas@jmondi.org>");
MODULE_DESCRIPTION("Renesas R-Car CMM Driver");
MODULE_LICENSE("GPL v2");
