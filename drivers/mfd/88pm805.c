<शैली गुरु>
/*
 * Base driver क्रम Marvell 88PM805
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
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/88pm80x.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

अटल स्थिर काष्ठा i2c_device_id pm80x_id_table[] = अणु
	अणु"88PM805", 0पूर्ण,
	अणुपूर्ण /* शून्य terminated */
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pm80x_id_table);

/* Interrupt Number in 88PM805 */
क्रमागत अणु
	PM805_IRQ_LDO_OFF,	/*0 */
	PM805_IRQ_SRC_DPLL_LOCK,	/*1 */
	PM805_IRQ_CLIP_FAULT,
	PM805_IRQ_MIC_CONFLICT,
	PM805_IRQ_HP2_SHRT,
	PM805_IRQ_HP1_SHRT,	/*5 */
	PM805_IRQ_FINE_PLL_FAULT,
	PM805_IRQ_RAW_PLL_FAULT,
	PM805_IRQ_VOLP_BTN_DET,
	PM805_IRQ_VOLM_BTN_DET,
	PM805_IRQ_SHRT_BTN_DET,	/*10 */
	PM805_IRQ_MIC_DET,	/*11 */

	PM805_MAX_IRQ,
पूर्ण;

अटल काष्ठा resource codec_resources[] = अणु
	अणु
	 /* Headset microphone insertion or removal */
	 .name = "micin",
	 .start = PM805_IRQ_MIC_DET,
	 .end = PM805_IRQ_MIC_DET,
	 .flags = IORESOURCE_IRQ,
	 पूर्ण,
	अणु
	 /* Audio लघु HP1 */
	 .name = "audio-short1",
	 .start = PM805_IRQ_HP1_SHRT,
	 .end = PM805_IRQ_HP1_SHRT,
	 .flags = IORESOURCE_IRQ,
	 पूर्ण,
	अणु
	 /* Audio लघु HP2 */
	 .name = "audio-short2",
	 .start = PM805_IRQ_HP2_SHRT,
	 .end = PM805_IRQ_HP2_SHRT,
	 .flags = IORESOURCE_IRQ,
	 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell codec_devs[] = अणु
	अणु
	 .name = "88pm80x-codec",
	 .num_resources = ARRAY_SIZE(codec_resources),
	 .resources = &codec_resources[0],
	 .id = -1,
	 पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq pm805_irqs[] = अणु
	/* INT0 */
	[PM805_IRQ_LDO_OFF] = अणु
		.mask = PM805_INT1_HP1_SHRT,
	पूर्ण,
	[PM805_IRQ_SRC_DPLL_LOCK] = अणु
		.mask = PM805_INT1_HP2_SHRT,
	पूर्ण,
	[PM805_IRQ_CLIP_FAULT] = अणु
		.mask = PM805_INT1_MIC_CONFLICT,
	पूर्ण,
	[PM805_IRQ_MIC_CONFLICT] = अणु
		.mask = PM805_INT1_CLIP_FAULT,
	पूर्ण,
	[PM805_IRQ_HP2_SHRT] = अणु
		.mask = PM805_INT1_LDO_OFF,
	पूर्ण,
	[PM805_IRQ_HP1_SHRT] = अणु
		.mask = PM805_INT1_SRC_DPLL_LOCK,
	पूर्ण,
	/* INT1 */
	[PM805_IRQ_FINE_PLL_FAULT] = अणु
		.reg_offset = 1,
		.mask = PM805_INT2_MIC_DET,
	पूर्ण,
	[PM805_IRQ_RAW_PLL_FAULT] = अणु
		.reg_offset = 1,
		.mask = PM805_INT2_SHRT_BTN_DET,
	पूर्ण,
	[PM805_IRQ_VOLP_BTN_DET] = अणु
		.reg_offset = 1,
		.mask = PM805_INT2_VOLM_BTN_DET,
	पूर्ण,
	[PM805_IRQ_VOLM_BTN_DET] = अणु
		.reg_offset = 1,
		.mask = PM805_INT2_VOLP_BTN_DET,
	पूर्ण,
	[PM805_IRQ_SHRT_BTN_DET] = अणु
		.reg_offset = 1,
		.mask = PM805_INT2_RAW_PLL_FAULT,
	पूर्ण,
	[PM805_IRQ_MIC_DET] = अणु
		.reg_offset = 1,
		.mask = PM805_INT2_FINE_PLL_FAULT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक device_irq_init_805(काष्ठा pm80x_chip *chip)
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
	    PM805_STATUS0_INT_CLEAR | PM805_STATUS0_INV_INT |
	    PM800_STATUS0_INT_MASK;

	data = PM805_STATUS0_INT_CLEAR;
	ret = regmap_update_bits(map, PM805_INT_STATUS0, mask, data);
	/*
	 * PM805_INT_STATUS is under 32K घड़ी करोमुख्य, so need to
	 * add proper delay beक्रमe the next I2C रेजिस्टर access.
	 */
	usleep_range(1000, 3000);

	अगर (ret < 0)
		जाओ out;

	ret =
	    regmap_add_irq_chip(chip->regmap, chip->irq, flags, -1,
				chip->regmap_irq_chip, &chip->irq_data);

out:
	वापस ret;
पूर्ण

अटल व्योम device_irq_निकास_805(काष्ठा pm80x_chip *chip)
अणु
	regmap_del_irq_chip(chip->irq, chip->irq_data);
पूर्ण

अटल काष्ठा regmap_irq_chip pm805_irq_chip = अणु
	.name = "88pm805",
	.irqs = pm805_irqs,
	.num_irqs = ARRAY_SIZE(pm805_irqs),

	.num_regs = 2,
	.status_base = PM805_INT_STATUS1,
	.mask_base = PM805_INT_MASK1,
	.ack_base = PM805_INT_STATUS1,
पूर्ण;

अटल पूर्णांक device_805_init(काष्ठा pm80x_chip *chip)
अणु
	पूर्णांक ret = 0;
	काष्ठा regmap *map = chip->regmap;

	अगर (!map) अणु
		dev_err(chip->dev, "regmap is invalid\n");
		वापस -EINVAL;
	पूर्ण

	chip->regmap_irq_chip = &pm805_irq_chip;

	ret = device_irq_init_805(chip);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to init pm805 irq!\n");
		जाओ out_irq_init;
	पूर्ण

	ret = mfd_add_devices(chip->dev, 0, &codec_devs[0],
			      ARRAY_SIZE(codec_devs), &codec_resources[0], 0,
			      शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add codec subdev\n");
		जाओ out_codec;
	पूर्ण अन्यथा
		dev_info(chip->dev, "[%s]:Added mfd codec_devs\n", __func__);

	वापस 0;

out_codec:
	device_irq_निकास_805(chip);
out_irq_init:
	वापस ret;
पूर्ण

अटल पूर्णांक pm805_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा pm80x_chip *chip;
	काष्ठा pm80x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);

	ret = pm80x_init(client);
	अगर (ret) अणु
		dev_err(&client->dev, "pm805_init fail!\n");
		जाओ out_init;
	पूर्ण

	chip = i2c_get_clientdata(client);

	ret = device_805_init(chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to initialize 88pm805 devices\n");
		जाओ err_805_init;
	पूर्ण

	अगर (pdata && pdata->plat_config)
		pdata->plat_config(chip, pdata);

err_805_init:
	pm80x_deinit();
out_init:
	वापस ret;
पूर्ण

अटल पूर्णांक pm805_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pm80x_chip *chip = i2c_get_clientdata(client);

	mfd_हटाओ_devices(chip->dev);
	device_irq_निकास_805(chip);

	pm80x_deinit();

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver pm805_driver = अणु
	.driver = अणु
		.name = "88PM805",
		.pm = &pm80x_pm_ops,
		पूर्ण,
	.probe = pm805_probe,
	.हटाओ = pm805_हटाओ,
	.id_table = pm80x_id_table,
पूर्ण;

अटल पूर्णांक __init pm805_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&pm805_driver);
पूर्ण
subsys_initcall(pm805_i2c_init);

अटल व्योम __निकास pm805_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&pm805_driver);
पूर्ण
module_निकास(pm805_i2c_निकास);

MODULE_DESCRIPTION("PMIC Driver for Marvell 88PM805");
MODULE_AUTHOR("Qiao Zhou <zhouqiao@marvell.com>");
MODULE_LICENSE("GPL");
