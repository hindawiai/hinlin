<शैली गुरु>
/*
 * Base driver क्रम Marvell 88PM800
 *
 * Copyright (C) 2012 Marvell International Ltd.
 * Haojian Zhuang <haojian.zhuang@marvell.com>
 * Joseph(Yossi) Hanin <yhanin@marvell.com>
 * Qiao Zhou <zhouqiao@marvell.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/88pm80x.h>
#समावेश <linux/slab.h>

/* Interrupt Registers */
#घोषणा PM800_INT_STATUS1		(0x05)
#घोषणा PM800_ONKEY_INT_STS1		(1 << 0)
#घोषणा PM800_EXTON_INT_STS1		(1 << 1)
#घोषणा PM800_CHG_INT_STS1			(1 << 2)
#घोषणा PM800_BAT_INT_STS1			(1 << 3)
#घोषणा PM800_RTC_INT_STS1			(1 << 4)
#घोषणा PM800_CLASSD_OC_INT_STS1	(1 << 5)

#घोषणा PM800_INT_STATUS2		(0x06)
#घोषणा PM800_VBAT_INT_STS2		(1 << 0)
#घोषणा PM800_VSYS_INT_STS2		(1 << 1)
#घोषणा PM800_VCHG_INT_STS2		(1 << 2)
#घोषणा PM800_TINT_INT_STS2		(1 << 3)
#घोषणा PM800_GPADC0_INT_STS2	(1 << 4)
#घोषणा PM800_TBAT_INT_STS2		(1 << 5)
#घोषणा PM800_GPADC2_INT_STS2	(1 << 6)
#घोषणा PM800_GPADC3_INT_STS2	(1 << 7)

#घोषणा PM800_INT_STATUS3		(0x07)

#घोषणा PM800_INT_STATUS4		(0x08)
#घोषणा PM800_GPIO0_INT_STS4		(1 << 0)
#घोषणा PM800_GPIO1_INT_STS4		(1 << 1)
#घोषणा PM800_GPIO2_INT_STS4		(1 << 2)
#घोषणा PM800_GPIO3_INT_STS4		(1 << 3)
#घोषणा PM800_GPIO4_INT_STS4		(1 << 4)

#घोषणा PM800_INT_ENA_1		(0x09)
#घोषणा PM800_ONKEY_INT_ENA1		(1 << 0)
#घोषणा PM800_EXTON_INT_ENA1		(1 << 1)
#घोषणा PM800_CHG_INT_ENA1			(1 << 2)
#घोषणा PM800_BAT_INT_ENA1			(1 << 3)
#घोषणा PM800_RTC_INT_ENA1			(1 << 4)
#घोषणा PM800_CLASSD_OC_INT_ENA1	(1 << 5)

#घोषणा PM800_INT_ENA_2		(0x0A)
#घोषणा PM800_VBAT_INT_ENA2		(1 << 0)
#घोषणा PM800_VSYS_INT_ENA2		(1 << 1)
#घोषणा PM800_VCHG_INT_ENA2		(1 << 2)
#घोषणा PM800_TINT_INT_ENA2		(1 << 3)

#घोषणा PM800_INT_ENA_3		(0x0B)
#घोषणा PM800_GPADC0_INT_ENA3		(1 << 0)
#घोषणा PM800_GPADC1_INT_ENA3		(1 << 1)
#घोषणा PM800_GPADC2_INT_ENA3		(1 << 2)
#घोषणा PM800_GPADC3_INT_ENA3		(1 << 3)
#घोषणा PM800_GPADC4_INT_ENA3		(1 << 4)

#घोषणा PM800_INT_ENA_4		(0x0C)
#घोषणा PM800_GPIO0_INT_ENA4		(1 << 0)
#घोषणा PM800_GPIO1_INT_ENA4		(1 << 1)
#घोषणा PM800_GPIO2_INT_ENA4		(1 << 2)
#घोषणा PM800_GPIO3_INT_ENA4		(1 << 3)
#घोषणा PM800_GPIO4_INT_ENA4		(1 << 4)

/* number of INT_ENA & INT_STATUS regs */
#घोषणा PM800_INT_REG_NUM			(4)

/* Interrupt Number in 88PM800 */
क्रमागत अणु
	PM800_IRQ_ONKEY,	/*EN1b0 *//*0 */
	PM800_IRQ_EXTON,	/*EN1b1 */
	PM800_IRQ_CHG,		/*EN1b2 */
	PM800_IRQ_BAT,		/*EN1b3 */
	PM800_IRQ_RTC,		/*EN1b4 */
	PM800_IRQ_CLASSD,	/*EN1b5 *//*5 */
	PM800_IRQ_VBAT,		/*EN2b0 */
	PM800_IRQ_VSYS,		/*EN2b1 */
	PM800_IRQ_VCHG,		/*EN2b2 */
	PM800_IRQ_TINT,		/*EN2b3 */
	PM800_IRQ_GPADC0,	/*EN3b0 *//*10 */
	PM800_IRQ_GPADC1,	/*EN3b1 */
	PM800_IRQ_GPADC2,	/*EN3b2 */
	PM800_IRQ_GPADC3,	/*EN3b3 */
	PM800_IRQ_GPADC4,	/*EN3b4 */
	PM800_IRQ_GPIO0,	/*EN4b0 *//*15 */
	PM800_IRQ_GPIO1,	/*EN4b1 */
	PM800_IRQ_GPIO2,	/*EN4b2 */
	PM800_IRQ_GPIO3,	/*EN4b3 */
	PM800_IRQ_GPIO4,	/*EN4b4 *//*19 */
	PM800_MAX_IRQ,
पूर्ण;

/* PM800: generation identअगरication number */
#घोषणा PM800_CHIP_GEN_ID_NUM	0x3

अटल स्थिर काष्ठा i2c_device_id pm80x_id_table[] = अणु
	अणु"88PM800", 0पूर्ण,
	अणुपूर्ण /* शून्य terminated */
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pm80x_id_table);

अटल स्थिर काष्ठा resource rtc_resources[] = अणु
	अणु
	 .name = "88pm80x-rtc",
	 .start = PM800_IRQ_RTC,
	 .end = PM800_IRQ_RTC,
	 .flags = IORESOURCE_IRQ,
	 पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell rtc_devs[] = अणु
	अणु
	 .name = "88pm80x-rtc",
	 .num_resources = ARRAY_SIZE(rtc_resources),
	 .resources = &rtc_resources[0],
	 .id = -1,
	 पूर्ण,
पूर्ण;

अटल काष्ठा resource onkey_resources[] = अणु
	अणु
	 .name = "88pm80x-onkey",
	 .start = PM800_IRQ_ONKEY,
	 .end = PM800_IRQ_ONKEY,
	 .flags = IORESOURCE_IRQ,
	 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell onkey_devs[] = अणु
	अणु
	 .name = "88pm80x-onkey",
	 .num_resources = 1,
	 .resources = &onkey_resources[0],
	 .id = -1,
	 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell regulator_devs[] = अणु
	अणु
	 .name = "88pm80x-regulator",
	 .id = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq pm800_irqs[] = अणु
	/* INT0 */
	[PM800_IRQ_ONKEY] = अणु
		.mask = PM800_ONKEY_INT_ENA1,
	पूर्ण,
	[PM800_IRQ_EXTON] = अणु
		.mask = PM800_EXTON_INT_ENA1,
	पूर्ण,
	[PM800_IRQ_CHG] = अणु
		.mask = PM800_CHG_INT_ENA1,
	पूर्ण,
	[PM800_IRQ_BAT] = अणु
		.mask = PM800_BAT_INT_ENA1,
	पूर्ण,
	[PM800_IRQ_RTC] = अणु
		.mask = PM800_RTC_INT_ENA1,
	पूर्ण,
	[PM800_IRQ_CLASSD] = अणु
		.mask = PM800_CLASSD_OC_INT_ENA1,
	पूर्ण,
	/* INT1 */
	[PM800_IRQ_VBAT] = अणु
		.reg_offset = 1,
		.mask = PM800_VBAT_INT_ENA2,
	पूर्ण,
	[PM800_IRQ_VSYS] = अणु
		.reg_offset = 1,
		.mask = PM800_VSYS_INT_ENA2,
	पूर्ण,
	[PM800_IRQ_VCHG] = अणु
		.reg_offset = 1,
		.mask = PM800_VCHG_INT_ENA2,
	पूर्ण,
	[PM800_IRQ_TINT] = अणु
		.reg_offset = 1,
		.mask = PM800_TINT_INT_ENA2,
	पूर्ण,
	/* INT2 */
	[PM800_IRQ_GPADC0] = अणु
		.reg_offset = 2,
		.mask = PM800_GPADC0_INT_ENA3,
	पूर्ण,
	[PM800_IRQ_GPADC1] = अणु
		.reg_offset = 2,
		.mask = PM800_GPADC1_INT_ENA3,
	पूर्ण,
	[PM800_IRQ_GPADC2] = अणु
		.reg_offset = 2,
		.mask = PM800_GPADC2_INT_ENA3,
	पूर्ण,
	[PM800_IRQ_GPADC3] = अणु
		.reg_offset = 2,
		.mask = PM800_GPADC3_INT_ENA3,
	पूर्ण,
	[PM800_IRQ_GPADC4] = अणु
		.reg_offset = 2,
		.mask = PM800_GPADC4_INT_ENA3,
	पूर्ण,
	/* INT3 */
	[PM800_IRQ_GPIO0] = अणु
		.reg_offset = 3,
		.mask = PM800_GPIO0_INT_ENA4,
	पूर्ण,
	[PM800_IRQ_GPIO1] = अणु
		.reg_offset = 3,
		.mask = PM800_GPIO1_INT_ENA4,
	पूर्ण,
	[PM800_IRQ_GPIO2] = अणु
		.reg_offset = 3,
		.mask = PM800_GPIO2_INT_ENA4,
	पूर्ण,
	[PM800_IRQ_GPIO3] = अणु
		.reg_offset = 3,
		.mask = PM800_GPIO3_INT_ENA4,
	पूर्ण,
	[PM800_IRQ_GPIO4] = अणु
		.reg_offset = 3,
		.mask = PM800_GPIO4_INT_ENA4,
	पूर्ण,
पूर्ण;

अटल पूर्णांक device_gpadc_init(काष्ठा pm80x_chip *chip,
				       काष्ठा pm80x_platक्रमm_data *pdata)
अणु
	काष्ठा pm80x_subchip *subchip = chip->subchip;
	काष्ठा regmap *map = subchip->regmap_gpadc;
	पूर्णांक data = 0, mask = 0, ret = 0;

	अगर (!map) अणु
		dev_warn(chip->dev,
			 "Warning: gpadc regmap is not available!\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * initialize GPADC without activating it turn on GPADC
	 * measurments
	 */
	ret = regmap_update_bits(map,
				 PM800_GPADC_MISC_CONFIG2,
				 PM800_GPADC_MISC_GPFSM_EN,
				 PM800_GPADC_MISC_GPFSM_EN);
	अगर (ret < 0)
		जाओ out;
	/*
	 * This function configures the ADC as requires क्रम
	 * CP implementation.CP करोes not "own" the ADC configuration
	 * रेजिस्टरs and relies on AP.
	 * Reason: enable स्वतःmatic ADC measurements needed
	 * क्रम CP to get VBAT and RF temperature पढ़ोings.
	 */
	ret = regmap_update_bits(map, PM800_GPADC_MEAS_EN1,
				 PM800_MEAS_EN1_VBAT, PM800_MEAS_EN1_VBAT);
	अगर (ret < 0)
		जाओ out;
	ret = regmap_update_bits(map, PM800_GPADC_MEAS_EN2,
				 (PM800_MEAS_EN2_RFTMP | PM800_MEAS_GP0_EN),
				 (PM800_MEAS_EN2_RFTMP | PM800_MEAS_GP0_EN));
	अगर (ret < 0)
		जाओ out;

	/*
	 * the defult of PM800 is GPADC operates at 100Ks/s rate
	 * and Number of GPADC slots with active current bias prior
	 * to GPADC sampling = 1 slot क्रम all GPADCs set क्रम
	 * Temprature mesurmants
	 */
	mask = (PM800_GPADC_GP_BIAS_EN0 | PM800_GPADC_GP_BIAS_EN1 |
		PM800_GPADC_GP_BIAS_EN2 | PM800_GPADC_GP_BIAS_EN3);

	अगर (pdata && (pdata->batt_det == 0))
		data = (PM800_GPADC_GP_BIAS_EN0 | PM800_GPADC_GP_BIAS_EN1 |
			PM800_GPADC_GP_BIAS_EN2 | PM800_GPADC_GP_BIAS_EN3);
	अन्यथा
		data = (PM800_GPADC_GP_BIAS_EN0 | PM800_GPADC_GP_BIAS_EN2 |
			PM800_GPADC_GP_BIAS_EN3);

	ret = regmap_update_bits(map, PM800_GP_BIAS_ENA1, mask, data);
	अगर (ret < 0)
		जाओ out;

	dev_info(chip->dev, "pm800 device_gpadc_init: Done\n");
	वापस 0;

out:
	dev_info(chip->dev, "pm800 device_gpadc_init: Failed!\n");
	वापस ret;
पूर्ण

अटल पूर्णांक device_onkey_init(काष्ठा pm80x_chip *chip,
				काष्ठा pm80x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = mfd_add_devices(chip->dev, 0, &onkey_devs[0],
			      ARRAY_SIZE(onkey_devs), &onkey_resources[0], 0,
			      शून्य);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to add onkey subdev\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक device_rtc_init(काष्ठा pm80x_chip *chip,
				काष्ठा pm80x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata) अणु
		rtc_devs[0].platक्रमm_data = pdata->rtc;
		rtc_devs[0].pdata_size =
				pdata->rtc ? माप(काष्ठा pm80x_rtc_pdata) : 0;
	पूर्ण
	ret = mfd_add_devices(chip->dev, 0, &rtc_devs[0],
			      ARRAY_SIZE(rtc_devs), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to add rtc subdev\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक device_regulator_init(काष्ठा pm80x_chip *chip,
					   काष्ठा pm80x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = mfd_add_devices(chip->dev, 0, &regulator_devs[0],
			      ARRAY_SIZE(regulator_devs), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to add regulator subdev\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक device_irq_init_800(काष्ठा pm80x_chip *chip)
अणु
	काष्ठा regmap *map = chip->regmap;
	अचिन्हित दीर्घ flags = IRQF_ONESHOT;
	पूर्णांक data, mask, ret = -EINVAL;

	अगर (!map || !chip->irq) अणु
		dev_err(chip->dev, "incorrect parameters\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * irq_mode defines the way of clearing पूर्णांकerrupt. it's पढ़ो-clear by
	 * शेष.
	 */
	mask =
	    PM800_WAKEUP2_INV_INT | PM800_WAKEUP2_INT_CLEAR |
	    PM800_WAKEUP2_INT_MASK;

	data = PM800_WAKEUP2_INT_CLEAR;
	ret = regmap_update_bits(map, PM800_WAKEUP2, mask, data);

	अगर (ret < 0)
		जाओ out;

	ret =
	    regmap_add_irq_chip(chip->regmap, chip->irq, flags, -1,
				chip->regmap_irq_chip, &chip->irq_data);

out:
	वापस ret;
पूर्ण

अटल व्योम device_irq_निकास_800(काष्ठा pm80x_chip *chip)
अणु
	regmap_del_irq_chip(chip->irq, chip->irq_data);
पूर्ण

अटल काष्ठा regmap_irq_chip pm800_irq_chip = अणु
	.name = "88pm800",
	.irqs = pm800_irqs,
	.num_irqs = ARRAY_SIZE(pm800_irqs),

	.num_regs = 4,
	.status_base = PM800_INT_STATUS1,
	.mask_base = PM800_INT_ENA_1,
	.ack_base = PM800_INT_STATUS1,
	.mask_invert = 1,
पूर्ण;

अटल पूर्णांक pm800_pages_init(काष्ठा pm80x_chip *chip)
अणु
	काष्ठा pm80x_subchip *subchip;
	काष्ठा i2c_client *client = chip->client;

	पूर्णांक ret = 0;

	subchip = chip->subchip;
	अगर (!subchip || !subchip->घातer_page_addr || !subchip->gpadc_page_addr)
		वापस -ENODEV;

	/* PM800 block घातer page */
	subchip->घातer_page = i2c_new_dummy_device(client->adapter,
					    subchip->घातer_page_addr);
	अगर (IS_ERR(subchip->घातer_page)) अणु
		ret = PTR_ERR(subchip->घातer_page);
		जाओ out;
	पूर्ण

	subchip->regmap_घातer = devm_regmap_init_i2c(subchip->घातer_page,
						     &pm80x_regmap_config);
	अगर (IS_ERR(subchip->regmap_घातer)) अणु
		ret = PTR_ERR(subchip->regmap_घातer);
		dev_err(chip->dev,
			"Failed to allocate regmap_power: %d\n", ret);
		जाओ out;
	पूर्ण

	i2c_set_clientdata(subchip->घातer_page, chip);

	/* PM800 block GPADC */
	subchip->gpadc_page = i2c_new_dummy_device(client->adapter,
					    subchip->gpadc_page_addr);
	अगर (IS_ERR(subchip->gpadc_page)) अणु
		ret = PTR_ERR(subchip->gpadc_page);
		जाओ out;
	पूर्ण

	subchip->regmap_gpadc = devm_regmap_init_i2c(subchip->gpadc_page,
						     &pm80x_regmap_config);
	अगर (IS_ERR(subchip->regmap_gpadc)) अणु
		ret = PTR_ERR(subchip->regmap_gpadc);
		dev_err(chip->dev,
			"Failed to allocate regmap_gpadc: %d\n", ret);
		जाओ out;
	पूर्ण
	i2c_set_clientdata(subchip->gpadc_page, chip);

out:
	वापस ret;
पूर्ण

अटल व्योम pm800_pages_निकास(काष्ठा pm80x_chip *chip)
अणु
	काष्ठा pm80x_subchip *subchip;

	subchip = chip->subchip;

	अगर (subchip && subchip->घातer_page)
		i2c_unरेजिस्टर_device(subchip->घातer_page);

	अगर (subchip && subchip->gpadc_page)
		i2c_unरेजिस्टर_device(subchip->gpadc_page);
पूर्ण

अटल पूर्णांक device_800_init(काष्ठा pm80x_chip *chip,
				     काष्ठा pm80x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	/*
	 * alarm wake up bit will be clear in device_irq_init(),
	 * पढ़ो beक्रमe that
	 */
	ret = regmap_पढ़ो(chip->regmap, PM800_RTC_CONTROL, &val);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read RTC register: %d\n", ret);
		जाओ out;
	पूर्ण
	अगर (val & PM800_ALARM_WAKEUP) अणु
		अगर (pdata && pdata->rtc)
			pdata->rtc->rtc_wakeup = 1;
	पूर्ण

	ret = device_gpadc_init(chip, pdata);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "[%s]Failed to init gpadc\n", __func__);
		जाओ out;
	पूर्ण

	chip->regmap_irq_chip = &pm800_irq_chip;

	ret = device_irq_init_800(chip);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "[%s]Failed to init pm800 irq\n", __func__);
		जाओ out;
	पूर्ण

	ret = device_onkey_init(chip, pdata);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to add onkey subdev\n");
		जाओ out_dev;
	पूर्ण

	ret = device_rtc_init(chip, pdata);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to add rtc subdev\n");
		जाओ out;
	पूर्ण

	ret = device_regulator_init(chip, pdata);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to add regulators subdev\n");
		जाओ out;
	पूर्ण

	वापस 0;
out_dev:
	mfd_हटाओ_devices(chip->dev);
	device_irq_निकास_800(chip);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pm800_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा pm80x_chip *chip;
	काष्ठा pm80x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा pm80x_subchip *subchip;

	ret = pm80x_init(client);
	अगर (ret) अणु
		dev_err(&client->dev, "pm800_init fail\n");
		जाओ out_init;
	पूर्ण

	chip = i2c_get_clientdata(client);

	/* init subchip क्रम PM800 */
	subchip =
	    devm_kzalloc(&client->dev, माप(काष्ठा pm80x_subchip),
			 GFP_KERNEL);
	अगर (!subchip) अणु
		ret = -ENOMEM;
		जाओ err_subchip_alloc;
	पूर्ण

	/* pm800 has 2 addtional pages to support घातer and gpadc. */
	subchip->घातer_page_addr = client->addr + 1;
	subchip->gpadc_page_addr = client->addr + 2;
	chip->subchip = subchip;

	ret = pm800_pages_init(chip);
	अगर (ret) अणु
		dev_err(&client->dev, "pm800_pages_init failed!\n");
		जाओ err_device_init;
	पूर्ण

	ret = device_800_init(chip, pdata);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to initialize 88pm800 devices\n");
		जाओ err_device_init;
	पूर्ण

	अगर (pdata && pdata->plat_config)
		pdata->plat_config(chip, pdata);

	वापस 0;

err_device_init:
	pm800_pages_निकास(chip);
err_subchip_alloc:
	pm80x_deinit();
out_init:
	वापस ret;
पूर्ण

अटल पूर्णांक pm800_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pm80x_chip *chip = i2c_get_clientdata(client);

	mfd_हटाओ_devices(chip->dev);
	device_irq_निकास_800(chip);

	pm800_pages_निकास(chip);
	pm80x_deinit();

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver pm800_driver = अणु
	.driver = अणु
		.name = "88PM800",
		.pm = &pm80x_pm_ops,
		पूर्ण,
	.probe = pm800_probe,
	.हटाओ = pm800_हटाओ,
	.id_table = pm80x_id_table,
पूर्ण;

अटल पूर्णांक __init pm800_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&pm800_driver);
पूर्ण
subsys_initcall(pm800_i2c_init);

अटल व्योम __निकास pm800_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&pm800_driver);
पूर्ण
module_निकास(pm800_i2c_निकास);

MODULE_DESCRIPTION("PMIC Driver for Marvell 88PM800");
MODULE_AUTHOR("Qiao Zhou <zhouqiao@marvell.com>");
MODULE_LICENSE("GPL");
