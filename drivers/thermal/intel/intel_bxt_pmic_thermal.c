<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Broxton PMIC thermal driver
 *
 * Copyright (C) 2016 Intel Corporation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/thermal.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>

#घोषणा BXTWC_THRM0IRQ		0x4E04
#घोषणा BXTWC_THRM1IRQ		0x4E05
#घोषणा BXTWC_THRM2IRQ		0x4E06
#घोषणा BXTWC_MTHRM0IRQ		0x4E12
#घोषणा BXTWC_MTHRM1IRQ		0x4E13
#घोषणा BXTWC_MTHRM2IRQ		0x4E14
#घोषणा BXTWC_STHRM0IRQ		0x4F19
#घोषणा BXTWC_STHRM1IRQ		0x4F1A
#घोषणा BXTWC_STHRM2IRQ		0x4F1B

काष्ठा trip_config_map अणु
	u16 irq_reg;
	u16 irq_en;
	u16 evt_stat;
	u8 irq_mask;
	u8 irq_en_mask;
	u8 evt_mask;
	u8 trip_num;
पूर्ण;

काष्ठा thermal_irq_map अणु
	अक्षर handle[20];
	पूर्णांक num_trips;
	स्थिर काष्ठा trip_config_map *trip_config;
पूर्ण;

काष्ठा pmic_thermal_data अणु
	स्थिर काष्ठा thermal_irq_map *maps;
	पूर्णांक num_maps;
पूर्ण;

अटल स्थिर काष्ठा trip_config_map bxtwc_str0_trip_config[] = अणु
	अणु
		.irq_reg = BXTWC_THRM0IRQ,
		.irq_mask = 0x01,
		.irq_en = BXTWC_MTHRM0IRQ,
		.irq_en_mask = 0x01,
		.evt_stat = BXTWC_STHRM0IRQ,
		.evt_mask = 0x01,
		.trip_num = 0
	पूर्ण,
	अणु
		.irq_reg = BXTWC_THRM0IRQ,
		.irq_mask = 0x10,
		.irq_en = BXTWC_MTHRM0IRQ,
		.irq_en_mask = 0x10,
		.evt_stat = BXTWC_STHRM0IRQ,
		.evt_mask = 0x10,
		.trip_num = 1
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा trip_config_map bxtwc_str1_trip_config[] = अणु
	अणु
		.irq_reg = BXTWC_THRM0IRQ,
		.irq_mask = 0x02,
		.irq_en = BXTWC_MTHRM0IRQ,
		.irq_en_mask = 0x02,
		.evt_stat = BXTWC_STHRM0IRQ,
		.evt_mask = 0x02,
		.trip_num = 0
	पूर्ण,
	अणु
		.irq_reg = BXTWC_THRM0IRQ,
		.irq_mask = 0x20,
		.irq_en = BXTWC_MTHRM0IRQ,
		.irq_en_mask = 0x20,
		.evt_stat = BXTWC_STHRM0IRQ,
		.evt_mask = 0x20,
		.trip_num = 1
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा trip_config_map bxtwc_str2_trip_config[] = अणु
	अणु
		.irq_reg = BXTWC_THRM0IRQ,
		.irq_mask = 0x04,
		.irq_en = BXTWC_MTHRM0IRQ,
		.irq_en_mask = 0x04,
		.evt_stat = BXTWC_STHRM0IRQ,
		.evt_mask = 0x04,
		.trip_num = 0
	पूर्ण,
	अणु
		.irq_reg = BXTWC_THRM0IRQ,
		.irq_mask = 0x40,
		.irq_en = BXTWC_MTHRM0IRQ,
		.irq_en_mask = 0x40,
		.evt_stat = BXTWC_STHRM0IRQ,
		.evt_mask = 0x40,
		.trip_num = 1
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा trip_config_map bxtwc_str3_trip_config[] = अणु
	अणु
		.irq_reg = BXTWC_THRM2IRQ,
		.irq_mask = 0x10,
		.irq_en = BXTWC_MTHRM2IRQ,
		.irq_en_mask = 0x10,
		.evt_stat = BXTWC_STHRM2IRQ,
		.evt_mask = 0x10,
		.trip_num = 0
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा thermal_irq_map bxtwc_thermal_irq_map[] = अणु
	अणु
		.handle = "STR0",
		.trip_config = bxtwc_str0_trip_config,
		.num_trips = ARRAY_SIZE(bxtwc_str0_trip_config),
	पूर्ण,
	अणु
		.handle = "STR1",
		.trip_config = bxtwc_str1_trip_config,
		.num_trips = ARRAY_SIZE(bxtwc_str1_trip_config),
	पूर्ण,
	अणु
		.handle = "STR2",
		.trip_config = bxtwc_str2_trip_config,
		.num_trips = ARRAY_SIZE(bxtwc_str2_trip_config),
	पूर्ण,
	अणु
		.handle = "STR3",
		.trip_config = bxtwc_str3_trip_config,
		.num_trips = ARRAY_SIZE(bxtwc_str3_trip_config),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmic_thermal_data bxtwc_thermal_data = अणु
	.maps = bxtwc_thermal_irq_map,
	.num_maps = ARRAY_SIZE(bxtwc_thermal_irq_map),
पूर्ण;

अटल irqवापस_t pmic_thermal_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	काष्ठा thermal_zone_device *tzd;
	काष्ठा pmic_thermal_data *td;
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	काष्ठा regmap *regmap;
	u8 reg_val, mask, irq_stat;
	u16 reg, evt_stat_reg;
	पूर्णांक i, j, ret;

	pmic = dev_get_drvdata(pdev->dev.parent);
	regmap = pmic->regmap;
	td = (काष्ठा pmic_thermal_data *)
		platक्रमm_get_device_id(pdev)->driver_data;

	/* Resolve thermal irqs */
	क्रम (i = 0; i < td->num_maps; i++) अणु
		क्रम (j = 0; j < td->maps[i].num_trips; j++) अणु
			reg = td->maps[i].trip_config[j].irq_reg;
			mask = td->maps[i].trip_config[j].irq_mask;
			/*
			 * Read the irq रेजिस्टर to resolve whether the
			 * पूर्णांकerrupt was triggered क्रम this sensor
			 */
			अगर (regmap_पढ़ो(regmap, reg, &ret))
				वापस IRQ_HANDLED;

			reg_val = (u8)ret;
			irq_stat = ((u8)ret & mask);

			अगर (!irq_stat)
				जारी;

			/*
			 * Read the status रेजिस्टर to find out what
			 * event occurred i.e a high or a low
			 */
			evt_stat_reg = td->maps[i].trip_config[j].evt_stat;
			अगर (regmap_पढ़ो(regmap, evt_stat_reg, &ret))
				वापस IRQ_HANDLED;

			tzd = thermal_zone_get_zone_by_name(td->maps[i].handle);
			अगर (!IS_ERR(tzd))
				thermal_zone_device_update(tzd,
						THERMAL_EVENT_UNSPECIFIED);

			/* Clear the appropriate irq */
			regmap_ग_लिखो(regmap, reg, reg_val & mask);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pmic_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap_irq_chip_data *regmap_irq_chip;
	काष्ठा pmic_thermal_data *thermal_data;
	पूर्णांक ret, irq, virq, i, j, pmic_irq_count;
	काष्ठा पूर्णांकel_soc_pmic *pmic;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	u16 reg;
	u8 mask;

	dev = &pdev->dev;
	pmic = dev_get_drvdata(pdev->dev.parent);
	अगर (!pmic) अणु
		dev_err(dev, "Failed to get struct intel_soc_pmic pointer\n");
		वापस -ENODEV;
	पूर्ण

	thermal_data = (काष्ठा pmic_thermal_data *)
				platक्रमm_get_device_id(pdev)->driver_data;
	अगर (!thermal_data) अणु
		dev_err(dev, "No thermal data initialized!!\n");
		वापस -ENODEV;
	पूर्ण

	regmap = pmic->regmap;
	regmap_irq_chip = pmic->irq_chip_data;

	pmic_irq_count = 0;
	जबतक ((irq = platक्रमm_get_irq(pdev, pmic_irq_count)) != -ENXIO) अणु
		virq = regmap_irq_get_virq(regmap_irq_chip, irq);
		अगर (virq < 0) अणु
			dev_err(dev, "failed to get virq by irq %d\n", irq);
			वापस virq;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, virq,
				शून्य, pmic_thermal_irq_handler,
				IRQF_ONESHOT, "pmic_thermal", pdev);

		अगर (ret) अणु
			dev_err(dev, "request irq(%d) failed: %d\n", virq, ret);
			वापस ret;
		पूर्ण
		pmic_irq_count++;
	पूर्ण

	/* Enable thermal पूर्णांकerrupts */
	क्रम (i = 0; i < thermal_data->num_maps; i++) अणु
		क्रम (j = 0; j < thermal_data->maps[i].num_trips; j++) अणु
			reg = thermal_data->maps[i].trip_config[j].irq_en;
			mask = thermal_data->maps[i].trip_config[j].irq_en_mask;
			ret = regmap_update_bits(regmap, reg, mask, 0x00);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id pmic_thermal_id_table[] = अणु
	अणु
		.name = "bxt_wcove_thermal",
		.driver_data = (kernel_uदीर्घ_t)&bxtwc_thermal_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pmic_thermal_driver = अणु
	.probe = pmic_thermal_probe,
	.driver = अणु
		.name = "pmic_thermal",
	पूर्ण,
	.id_table = pmic_thermal_id_table,
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, pmic_thermal_id_table);
module_platक्रमm_driver(pmic_thermal_driver);

MODULE_AUTHOR("Yegnesh S Iyer <yegnesh.s.iyer@intel.com>");
MODULE_DESCRIPTION("Intel Broxton PMIC Thermal Driver");
MODULE_LICENSE("GPL v2");
