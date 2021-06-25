<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>

#घोषणा CUR_DRV_CAL_SEL			GENMASK(13, 12)
#घोषणा SLP_LDOVIBR_PD_EN		BIT(9)
#घोषणा LDO_VIBR_PD			BIT(8)
#घोषणा SC2730_CUR_DRV_CAL_SEL		0
#घोषणा SC2730_SLP_LDOVIBR_PD_EN	BIT(14)
#घोषणा SC2730_LDO_VIBR_PD		BIT(13)

काष्ठा sc27xx_vibra_data अणु
	u32 cur_drv_cal_sel;
	u32 slp_pd_en;
	u32 lकरो_pd;
पूर्ण;

काष्ठा vibra_info अणु
	काष्ठा input_dev	*input_dev;
	काष्ठा work_काष्ठा	play_work;
	काष्ठा regmap		*regmap;
	स्थिर काष्ठा sc27xx_vibra_data *data;
	u32			base;
	u32			strength;
	bool			enabled;
पूर्ण;

अटल स्थिर काष्ठा sc27xx_vibra_data sc2731_data = अणु
	.cur_drv_cal_sel = CUR_DRV_CAL_SEL,
	.slp_pd_en = SLP_LDOVIBR_PD_EN,
	.lकरो_pd = LDO_VIBR_PD,
पूर्ण;

अटल स्थिर काष्ठा sc27xx_vibra_data sc2730_data = अणु
	.cur_drv_cal_sel = SC2730_CUR_DRV_CAL_SEL,
	.slp_pd_en = SC2730_SLP_LDOVIBR_PD_EN,
	.lकरो_pd = SC2730_LDO_VIBR_PD,
पूर्ण;

अटल स्थिर काष्ठा sc27xx_vibra_data sc2721_data = अणु
	.cur_drv_cal_sel = CUR_DRV_CAL_SEL,
	.slp_pd_en = SLP_LDOVIBR_PD_EN,
	.lकरो_pd = LDO_VIBR_PD,
पूर्ण;

अटल व्योम sc27xx_vibra_set(काष्ठा vibra_info *info, bool on)
अणु
	स्थिर काष्ठा sc27xx_vibra_data *data = info->data;
	अगर (on) अणु
		regmap_update_bits(info->regmap, info->base, data->lकरो_pd, 0);
		regmap_update_bits(info->regmap, info->base,
				   data->slp_pd_en, 0);
		info->enabled = true;
	पूर्ण अन्यथा अणु
		regmap_update_bits(info->regmap, info->base, data->lकरो_pd,
				   data->lकरो_pd);
		regmap_update_bits(info->regmap, info->base,
				   data->slp_pd_en, data->slp_pd_en);
		info->enabled = false;
	पूर्ण
पूर्ण

अटल पूर्णांक sc27xx_vibra_hw_init(काष्ठा vibra_info *info)
अणु
	स्थिर काष्ठा sc27xx_vibra_data *data = info->data;

	अगर (!data->cur_drv_cal_sel)
		वापस 0;

	वापस regmap_update_bits(info->regmap, info->base,
				  data->cur_drv_cal_sel, 0);
पूर्ण

अटल व्योम sc27xx_vibra_play_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vibra_info *info = container_of(work, काष्ठा vibra_info,
					       play_work);

	अगर (info->strength && !info->enabled)
		sc27xx_vibra_set(info, true);
	अन्यथा अगर (info->strength == 0 && info->enabled)
		sc27xx_vibra_set(info, false);
पूर्ण

अटल पूर्णांक sc27xx_vibra_play(काष्ठा input_dev *input, व्योम *data,
			     काष्ठा ff_effect *effect)
अणु
	काष्ठा vibra_info *info = input_get_drvdata(input);

	info->strength = effect->u.rumble.weak_magnitude;
	schedule_work(&info->play_work);

	वापस 0;
पूर्ण

अटल व्योम sc27xx_vibra_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा vibra_info *info = input_get_drvdata(input);

	cancel_work_sync(&info->play_work);
	अगर (info->enabled)
		sc27xx_vibra_set(info, false);
पूर्ण

अटल पूर्णांक sc27xx_vibra_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vibra_info *info;
	स्थिर काष्ठा sc27xx_vibra_data *data;
	पूर्णांक error;

	data = device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "no matching driver data found\n");
		वापस -EINVAL;
	पूर्ण

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!info->regmap) अणु
		dev_err(&pdev->dev, "failed to get vibrator regmap.\n");
		वापस -ENODEV;
	पूर्ण

	error = device_property_पढ़ो_u32(&pdev->dev, "reg", &info->base);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to get vibrator base address.\n");
		वापस error;
	पूर्ण

	info->input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!info->input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate input device.\n");
		वापस -ENOMEM;
	पूर्ण

	info->input_dev->name = "sc27xx:vibrator";
	info->input_dev->id.version = 0;
	info->input_dev->बंद = sc27xx_vibra_बंद;
	info->data = data;

	input_set_drvdata(info->input_dev, info);
	input_set_capability(info->input_dev, EV_FF, FF_RUMBLE);
	INIT_WORK(&info->play_work, sc27xx_vibra_play_work);
	info->enabled = false;

	error = sc27xx_vibra_hw_init(info);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to initialize the vibrator.\n");
		वापस error;
	पूर्ण

	error = input_ff_create_memless(info->input_dev, शून्य,
					sc27xx_vibra_play);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register vibrator to FF.\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(info->input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device.\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sc27xx_vibra_of_match[] = अणु
	अणु .compatible = "sprd,sc2721-vibrator", .data = &sc2721_data पूर्ण,
	अणु .compatible = "sprd,sc2730-vibrator", .data = &sc2730_data पूर्ण,
	अणु .compatible = "sprd,sc2731-vibrator", .data = &sc2731_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sc27xx_vibra_of_match);

अटल काष्ठा platक्रमm_driver sc27xx_vibra_driver = अणु
	.driver = अणु
		.name = "sc27xx-vibrator",
		.of_match_table = sc27xx_vibra_of_match,
	पूर्ण,
	.probe = sc27xx_vibra_probe,
पूर्ण;

module_platक्रमm_driver(sc27xx_vibra_driver);

MODULE_DESCRIPTION("Spreadtrum SC27xx Vibrator Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Xiaotong Lu <xiaotong.lu@spreadtrum.com>");
