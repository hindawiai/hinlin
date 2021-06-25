<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * exynos_ppmu.c - Exynos PPMU (Platक्रमm Perक्रमmance Monitoring Unit) support
 *
 * Copyright (c) 2014-2015 Samsung Electronics Co., Ltd.
 * Author : Chanwoo Choi <cw00.choi@samsung.com>
 *
 * This driver is based on drivers/devfreq/exynos/exynos_ppmu.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/suspend.h>
#समावेश <linux/devfreq-event.h>

#समावेश "exynos-ppmu.h"

क्रमागत exynos_ppmu_type अणु
	EXYNOS_TYPE_PPMU,
	EXYNOS_TYPE_PPMU_V2,
पूर्ण;

काष्ठा exynos_ppmu_data अणु
	काष्ठा clk *clk;
पूर्ण;

काष्ठा exynos_ppmu अणु
	काष्ठा devfreq_event_dev **edev;
	काष्ठा devfreq_event_desc *desc;
	अचिन्हित पूर्णांक num_events;

	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	काष्ठा exynos_ppmu_data ppmu;
	क्रमागत exynos_ppmu_type ppmu_type;
पूर्ण;

#घोषणा PPMU_EVENT(name)			\
	अणु "ppmu-event0-"#name, PPMU_PMNCNT0 पूर्ण,	\
	अणु "ppmu-event1-"#name, PPMU_PMNCNT1 पूर्ण,	\
	अणु "ppmu-event2-"#name, PPMU_PMNCNT2 पूर्ण,	\
	अणु "ppmu-event3-"#name, PPMU_PMNCNT3 पूर्ण

अटल काष्ठा __exynos_ppmu_events अणु
	अक्षर *name;
	पूर्णांक id;
पूर्ण ppmu_events[] = अणु
	/* For Exynos3250, Exynos4 and Exynos5260 */
	PPMU_EVENT(g3d),
	PPMU_EVENT(fsys),

	/* For Exynos4 SoCs and Exynos3250 */
	PPMU_EVENT(dmc0),
	PPMU_EVENT(dmc1),
	PPMU_EVENT(cpu),
	PPMU_EVENT(rightbus),
	PPMU_EVENT(leftbus),
	PPMU_EVENT(lcd0),
	PPMU_EVENT(camअगर),

	/* Only क्रम Exynos3250 and Exynos5260 */
	PPMU_EVENT(mfc),

	/* Only क्रम Exynos4 SoCs */
	PPMU_EVENT(mfc-left),
	PPMU_EVENT(mfc-right),

	/* Only क्रम Exynos5260 SoCs */
	PPMU_EVENT(drex0-s0),
	PPMU_EVENT(drex0-s1),
	PPMU_EVENT(drex1-s0),
	PPMU_EVENT(drex1-s1),
	PPMU_EVENT(eagle),
	PPMU_EVENT(kfc),
	PPMU_EVENT(isp),
	PPMU_EVENT(fimc),
	PPMU_EVENT(gscl),
	PPMU_EVENT(mscl),
	PPMU_EVENT(fimd0x),
	PPMU_EVENT(fimd1x),

	/* Only क्रम Exynos5433 SoCs */
	PPMU_EVENT(d0-cpu),
	PPMU_EVENT(d0-general),
	PPMU_EVENT(d0-rt),
	PPMU_EVENT(d1-cpu),
	PPMU_EVENT(d1-general),
	PPMU_EVENT(d1-rt),

	/* For Exynos5422 SoC */
	PPMU_EVENT(dmc0_0),
	PPMU_EVENT(dmc0_1),
	PPMU_EVENT(dmc1_0),
	PPMU_EVENT(dmc1_1),
पूर्ण;

अटल पूर्णांक __exynos_ppmu_find_ppmu_id(स्थिर अक्षर *edev_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ppmu_events); i++)
		अगर (!म_भेद(edev_name, ppmu_events[i].name))
			वापस ppmu_events[i].id;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक exynos_ppmu_find_ppmu_id(काष्ठा devfreq_event_dev *edev)
अणु
	वापस __exynos_ppmu_find_ppmu_id(edev->desc->name);
पूर्ण

/*
 * The devfreq-event ops काष्ठाure क्रम PPMU v1.1
 */
अटल पूर्णांक exynos_ppmu_disable(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	पूर्णांक ret;
	u32 pmnc;

	/* Disable all counters */
	ret = regmap_ग_लिखो(info->regmap, PPMU_CNTENC,
				PPMU_CCNT_MASK |
				PPMU_PMCNT0_MASK |
				PPMU_PMCNT1_MASK |
				PPMU_PMCNT2_MASK |
				PPMU_PMCNT3_MASK);
	अगर (ret < 0)
		वापस ret;

	/* Disable PPMU */
	ret = regmap_पढ़ो(info->regmap, PPMU_PMNC, &pmnc);
	अगर (ret < 0)
		वापस ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_ग_लिखो(info->regmap, PPMU_PMNC, pmnc);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ppmu_set_event(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	पूर्णांक id = exynos_ppmu_find_ppmu_id(edev);
	पूर्णांक ret;
	u32 pmnc, cntens;

	अगर (id < 0)
		वापस id;

	/* Enable specअगरic counter */
	ret = regmap_पढ़ो(info->regmap, PPMU_CNTENS, &cntens);
	अगर (ret < 0)
		वापस ret;

	cntens |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_ग_लिखो(info->regmap, PPMU_CNTENS, cntens);
	अगर (ret < 0)
		वापस ret;

	/* Set the event of proper data type monitoring */
	ret = regmap_ग_लिखो(info->regmap, PPMU_BEVTxSEL(id),
			   edev->desc->event_type);
	अगर (ret < 0)
		वापस ret;

	/* Reset cycle counter/perक्रमmance counter and enable PPMU */
	ret = regmap_पढ़ो(info->regmap, PPMU_PMNC, &pmnc);
	अगर (ret < 0)
		वापस ret;

	pmnc &= ~(PPMU_PMNC_ENABLE_MASK
			| PPMU_PMNC_COUNTER_RESET_MASK
			| PPMU_PMNC_CC_RESET_MASK);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_ENABLE_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_COUNTER_RESET_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_CC_RESET_SHIFT);
	ret = regmap_ग_लिखो(info->regmap, PPMU_PMNC, pmnc);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ppmu_get_event(काष्ठा devfreq_event_dev *edev,
				काष्ठा devfreq_event_data *edata)
अणु
	काष्ठा exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	पूर्णांक id = exynos_ppmu_find_ppmu_id(edev);
	अचिन्हित पूर्णांक total_count, load_count;
	अचिन्हित पूर्णांक pmcnt3_high, pmcnt3_low;
	अचिन्हित पूर्णांक pmnc, cntenc;
	पूर्णांक ret;

	अगर (id < 0)
		वापस -EINVAL;

	/* Disable PPMU */
	ret = regmap_पढ़ो(info->regmap, PPMU_PMNC, &pmnc);
	अगर (ret < 0)
		वापस ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_ग_लिखो(info->regmap, PPMU_PMNC, pmnc);
	अगर (ret < 0)
		वापस ret;

	/* Read cycle count */
	ret = regmap_पढ़ो(info->regmap, PPMU_CCNT, &total_count);
	अगर (ret < 0)
		वापस ret;
	edata->total_count = total_count;

	/* Read perक्रमmance count */
	चयन (id) अणु
	हाल PPMU_PMNCNT0:
	हाल PPMU_PMNCNT1:
	हाल PPMU_PMNCNT2:
		ret = regmap_पढ़ो(info->regmap, PPMU_PMNCT(id), &load_count);
		अगर (ret < 0)
			वापस ret;
		edata->load_count = load_count;
		अवरोध;
	हाल PPMU_PMNCNT3:
		ret = regmap_पढ़ो(info->regmap, PPMU_PMCNT3_HIGH, &pmcnt3_high);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_पढ़ो(info->regmap, PPMU_PMCNT3_LOW, &pmcnt3_low);
		अगर (ret < 0)
			वापस ret;

		edata->load_count = ((pmcnt3_high << 8) | pmcnt3_low);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Disable specअगरic counter */
	ret = regmap_पढ़ो(info->regmap, PPMU_CNTENC, &cntenc);
	अगर (ret < 0)
		वापस ret;

	cntenc |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_ग_लिखो(info->regmap, PPMU_CNTENC, cntenc);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&edev->dev, "%s (event: %ld/%ld)\n", edev->desc->name,
					edata->load_count, edata->total_count);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devfreq_event_ops exynos_ppmu_ops = अणु
	.disable = exynos_ppmu_disable,
	.set_event = exynos_ppmu_set_event,
	.get_event = exynos_ppmu_get_event,
पूर्ण;

/*
 * The devfreq-event ops काष्ठाure क्रम PPMU v2.0
 */
अटल पूर्णांक exynos_ppmu_v2_disable(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	पूर्णांक ret;
	u32 pmnc, clear;

	/* Disable all counters */
	clear = (PPMU_CCNT_MASK | PPMU_PMCNT0_MASK | PPMU_PMCNT1_MASK
		| PPMU_PMCNT2_MASK | PPMU_PMCNT3_MASK);
	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_FLAG, clear);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_INTENC, clear);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CNTENC, clear);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CNT_RESET, clear);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CIG_CFG0, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CIG_CFG1, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CIG_CFG2, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CIG_RESULT, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CNT_AUTO, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CH_EV0_TYPE, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CH_EV1_TYPE, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CH_EV2_TYPE, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CH_EV3_TYPE, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_SM_ID_V, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_SM_ID_A, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_SM_OTHERS_V, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_SM_OTHERS_A, 0x0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_INTERRUPT_RESET, 0x0);
	अगर (ret < 0)
		वापस ret;

	/* Disable PPMU */
	ret = regmap_पढ़ो(info->regmap, PPMU_V2_PMNC, &pmnc);
	अगर (ret < 0)
		वापस ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_PMNC, pmnc);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ppmu_v2_set_event(काष्ठा devfreq_event_dev *edev)
अणु
	काष्ठा exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	अचिन्हित पूर्णांक pmnc, cntens;
	पूर्णांक id = exynos_ppmu_find_ppmu_id(edev);
	पूर्णांक ret;

	/* Enable all counters */
	ret = regmap_पढ़ो(info->regmap, PPMU_V2_CNTENS, &cntens);
	अगर (ret < 0)
		वापस ret;

	cntens |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CNTENS, cntens);
	अगर (ret < 0)
		वापस ret;

	/* Set the event of proper data type monitoring */
	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CH_EVx_TYPE(id),
			   edev->desc->event_type);
	अगर (ret < 0)
		वापस ret;

	/* Reset cycle counter/perक्रमmance counter and enable PPMU */
	ret = regmap_पढ़ो(info->regmap, PPMU_V2_PMNC, &pmnc);
	अगर (ret < 0)
		वापस ret;

	pmnc &= ~(PPMU_PMNC_ENABLE_MASK
			| PPMU_PMNC_COUNTER_RESET_MASK
			| PPMU_PMNC_CC_RESET_MASK
			| PPMU_PMNC_CC_DIVIDER_MASK
			| PPMU_V2_PMNC_START_MODE_MASK);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_ENABLE_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_COUNTER_RESET_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_CC_RESET_SHIFT);
	pmnc |= (PPMU_V2_MODE_MANUAL << PPMU_V2_PMNC_START_MODE_SHIFT);

	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_PMNC, pmnc);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ppmu_v2_get_event(काष्ठा devfreq_event_dev *edev,
				    काष्ठा devfreq_event_data *edata)
अणु
	काष्ठा exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	पूर्णांक id = exynos_ppmu_find_ppmu_id(edev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक pmnc, cntenc;
	अचिन्हित पूर्णांक pmcnt_high, pmcnt_low;
	अचिन्हित पूर्णांक total_count, count;
	अचिन्हित दीर्घ load_count = 0;

	/* Disable PPMU */
	ret = regmap_पढ़ो(info->regmap, PPMU_V2_PMNC, &pmnc);
	अगर (ret < 0)
		वापस ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_PMNC, pmnc);
	अगर (ret < 0)
		वापस ret;

	/* Read cycle count and perक्रमmance count */
	ret = regmap_पढ़ो(info->regmap, PPMU_V2_CCNT, &total_count);
	अगर (ret < 0)
		वापस ret;
	edata->total_count = total_count;

	चयन (id) अणु
	हाल PPMU_PMNCNT0:
	हाल PPMU_PMNCNT1:
	हाल PPMU_PMNCNT2:
		ret = regmap_पढ़ो(info->regmap, PPMU_V2_PMNCT(id), &count);
		अगर (ret < 0)
			वापस ret;
		load_count = count;
		अवरोध;
	हाल PPMU_PMNCNT3:
		ret = regmap_पढ़ो(info->regmap, PPMU_V2_PMCNT3_HIGH,
						&pmcnt_high);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_पढ़ो(info->regmap, PPMU_V2_PMCNT3_LOW, &pmcnt_low);
		अगर (ret < 0)
			वापस ret;

		load_count = ((u64)((pmcnt_high & 0xff)) << 32)+ (u64)pmcnt_low;
		अवरोध;
	पूर्ण
	edata->load_count = load_count;

	/* Disable all counters */
	ret = regmap_पढ़ो(info->regmap, PPMU_V2_CNTENC, &cntenc);
	अगर (ret < 0)
		वापस 0;

	cntenc |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_ग_लिखो(info->regmap, PPMU_V2_CNTENC, cntenc);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&edev->dev, "%25s (load: %ld / %ld)\n", edev->desc->name,
					edata->load_count, edata->total_count);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devfreq_event_ops exynos_ppmu_v2_ops = अणु
	.disable = exynos_ppmu_v2_disable,
	.set_event = exynos_ppmu_v2_set_event,
	.get_event = exynos_ppmu_v2_get_event,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_ppmu_id_match[] = अणु
	अणु
		.compatible = "samsung,exynos-ppmu",
		.data = (व्योम *)EXYNOS_TYPE_PPMU,
	पूर्ण, अणु
		.compatible = "samsung,exynos-ppmu-v2",
		.data = (व्योम *)EXYNOS_TYPE_PPMU_V2,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_ppmu_id_match);

अटल पूर्णांक of_get_devfreq_events(काष्ठा device_node *np,
				 काष्ठा exynos_ppmu *info)
अणु
	काष्ठा devfreq_event_desc *desc;
	काष्ठा device *dev = info->dev;
	काष्ठा device_node *events_np, *node;
	पूर्णांक i, j, count;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक ret;

	events_np = of_get_child_by_name(np, "events");
	अगर (!events_np) अणु
		dev_err(dev,
			"failed to get child node of devfreq-event devices\n");
		वापस -EINVAL;
	पूर्ण

	count = of_get_child_count(events_np);
	desc = devm_kसुस्मृति(dev, count, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;
	info->num_events = count;

	of_id = of_match_device(exynos_ppmu_id_match, dev);
	अगर (of_id)
		info->ppmu_type = (क्रमागत exynos_ppmu_type)of_id->data;
	अन्यथा
		वापस -EINVAL;

	j = 0;
	क्रम_each_child_of_node(events_np, node) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ppmu_events); i++) अणु
			अगर (!ppmu_events[i].name)
				जारी;

			अगर (of_node_name_eq(node, ppmu_events[i].name))
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(ppmu_events)) अणु
			dev_warn(dev,
				"don't know how to configure events : %pOFn\n",
				node);
			जारी;
		पूर्ण

		चयन (info->ppmu_type) अणु
		हाल EXYNOS_TYPE_PPMU:
			desc[j].ops = &exynos_ppmu_ops;
			अवरोध;
		हाल EXYNOS_TYPE_PPMU_V2:
			desc[j].ops = &exynos_ppmu_v2_ops;
			अवरोध;
		पूर्ण

		desc[j].driver_data = info;

		of_property_पढ़ो_string(node, "event-name", &desc[j].name);
		ret = of_property_पढ़ो_u32(node, "event-data-type",
					   &desc[j].event_type);
		अगर (ret) अणु
			/* Set the event of proper data type counting.
			 * Check अगर the data type has been defined in DT,
			 * use शेष अगर not.
			 */
			अगर (info->ppmu_type == EXYNOS_TYPE_PPMU_V2) अणु
				पूर्णांक id;
				/* Not all रेजिस्टरs take the same value क्रम
				 * पढ़ो+ग_लिखो data count.
				 */
				id = __exynos_ppmu_find_ppmu_id(desc[j].name);

				चयन (id) अणु
				हाल PPMU_PMNCNT0:
				हाल PPMU_PMNCNT1:
				हाल PPMU_PMNCNT2:
					desc[j].event_type = PPMU_V2_RO_DATA_CNT
						| PPMU_V2_WO_DATA_CNT;
					अवरोध;
				हाल PPMU_PMNCNT3:
					desc[j].event_type =
						PPMU_V2_EVT3_RW_DATA_CNT;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				desc[j].event_type = PPMU_RO_DATA_CNT |
					PPMU_WO_DATA_CNT;
			पूर्ण
		पूर्ण

		j++;
	पूर्ण
	info->desc = desc;

	of_node_put(events_np);

	वापस 0;
पूर्ण

अटल काष्ठा regmap_config exynos_ppmu_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक exynos_ppmu_parse_dt(काष्ठा platक्रमm_device *pdev,
				काष्ठा exynos_ppmu *info)
अणु
	काष्ठा device *dev = info->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret = 0;

	अगर (!np) अणु
		dev_err(dev, "failed to find devicetree node\n");
		वापस -EINVAL;
	पूर्ण

	/* Maps the memory mapped IO to control PPMU रेजिस्टर */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	exynos_ppmu_regmap_config.max_रेजिस्टर = resource_size(res) - 4;
	info->regmap = devm_regmap_init_mmio(dev, base,
					&exynos_ppmu_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		dev_err(dev, "failed to initialize regmap\n");
		वापस PTR_ERR(info->regmap);
	पूर्ण

	info->ppmu.clk = devm_clk_get(dev, "ppmu");
	अगर (IS_ERR(info->ppmu.clk)) अणु
		info->ppmu.clk = शून्य;
		dev_warn(dev, "cannot get PPMU clock\n");
	पूर्ण

	ret = of_get_devfreq_events(np, info);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to parse exynos ppmu dt node\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ppmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_ppmu *info;
	काष्ठा devfreq_event_dev **edev;
	काष्ठा devfreq_event_desc *desc;
	पूर्णांक i, ret = 0, size;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;

	/* Parse dt data to get resource */
	ret = exynos_ppmu_parse_dt(pdev, info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"failed to parse devicetree for resource\n");
		वापस ret;
	पूर्ण
	desc = info->desc;

	size = माप(काष्ठा devfreq_event_dev *) * info->num_events;
	info->edev = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!info->edev)
		वापस -ENOMEM;

	edev = info->edev;
	platक्रमm_set_drvdata(pdev, info);

	क्रम (i = 0; i < info->num_events; i++) अणु
		edev[i] = devm_devfreq_event_add_edev(&pdev->dev, &desc[i]);
		अगर (IS_ERR(edev[i])) अणु
			dev_err(&pdev->dev,
				"failed to add devfreq-event device\n");
			वापस PTR_ERR(edev[i]);
		पूर्ण

		pr_info("exynos-ppmu: new PPMU device registered %s (%s)\n",
			dev_name(&pdev->dev), desc[i].name);
	पूर्ण

	ret = clk_prepare_enable(info->ppmu.clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare ppmu clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ppmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_ppmu *info = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(info->ppmu.clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_ppmu_driver = अणु
	.probe	= exynos_ppmu_probe,
	.हटाओ	= exynos_ppmu_हटाओ,
	.driver = अणु
		.name	= "exynos-ppmu",
		.of_match_table = exynos_ppmu_id_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(exynos_ppmu_driver);

MODULE_DESCRIPTION("Exynos PPMU(Platform Performance Monitoring Unit) driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL");
