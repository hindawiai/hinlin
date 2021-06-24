<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// SPI to CAN driver क्रम the Texas Instruments TCAN4x5x
// Copyright (C) 2018-19 Texas Instruments Incorporated - http://www.ti.com/

#समावेश "tcan4x5x.h"

#घोषणा TCAN4X5X_EXT_CLK_DEF 40000000

#घोषणा TCAN4X5X_DEV_ID0 0x00
#घोषणा TCAN4X5X_DEV_ID1 0x04
#घोषणा TCAN4X5X_REV 0x08
#घोषणा TCAN4X5X_STATUS 0x0C
#घोषणा TCAN4X5X_ERROR_STATUS 0x10
#घोषणा TCAN4X5X_CONTROL 0x14

#घोषणा TCAN4X5X_CONFIG 0x800
#घोषणा TCAN4X5X_TS_PRESCALE 0x804
#घोषणा TCAN4X5X_TEST_REG 0x808
#घोषणा TCAN4X5X_INT_FLAGS 0x820
#घोषणा TCAN4X5X_MCAN_INT_REG 0x824
#घोषणा TCAN4X5X_INT_EN 0x830

/* Interrupt bits */
#घोषणा TCAN4X5X_CANBUSTERMOPEN_INT_EN BIT(30)
#घोषणा TCAN4X5X_CANHCANL_INT_EN BIT(29)
#घोषणा TCAN4X5X_CANHBAT_INT_EN BIT(28)
#घोषणा TCAN4X5X_CANLGND_INT_EN BIT(27)
#घोषणा TCAN4X5X_CANBUSOPEN_INT_EN BIT(26)
#घोषणा TCAN4X5X_CANBUSGND_INT_EN BIT(25)
#घोषणा TCAN4X5X_CANBUSBAT_INT_EN BIT(24)
#घोषणा TCAN4X5X_UVSUP_INT_EN BIT(22)
#घोषणा TCAN4X5X_UVIO_INT_EN BIT(21)
#घोषणा TCAN4X5X_TSD_INT_EN BIT(19)
#घोषणा TCAN4X5X_ECCERR_INT_EN BIT(16)
#घोषणा TCAN4X5X_CANINT_INT_EN BIT(15)
#घोषणा TCAN4X5X_LWU_INT_EN BIT(14)
#घोषणा TCAN4X5X_CANSLNT_INT_EN BIT(10)
#घोषणा TCAN4X5X_CANDOM_INT_EN BIT(8)
#घोषणा TCAN4X5X_CANBUS_ERR_INT_EN BIT(5)
#घोषणा TCAN4X5X_BUS_FAULT BIT(4)
#घोषणा TCAN4X5X_MCAN_INT BIT(1)
#घोषणा TCAN4X5X_ENABLE_TCAN_INT \
	(TCAN4X5X_MCAN_INT | TCAN4X5X_BUS_FAULT | \
	 TCAN4X5X_CANBUS_ERR_INT_EN | TCAN4X5X_CANINT_INT_EN)

/* MCAN Interrupt bits */
#घोषणा TCAN4X5X_MCAN_IR_ARA BIT(29)
#घोषणा TCAN4X5X_MCAN_IR_PED BIT(28)
#घोषणा TCAN4X5X_MCAN_IR_PEA BIT(27)
#घोषणा TCAN4X5X_MCAN_IR_WD BIT(26)
#घोषणा TCAN4X5X_MCAN_IR_BO BIT(25)
#घोषणा TCAN4X5X_MCAN_IR_EW BIT(24)
#घोषणा TCAN4X5X_MCAN_IR_EP BIT(23)
#घोषणा TCAN4X5X_MCAN_IR_ELO BIT(22)
#घोषणा TCAN4X5X_MCAN_IR_BEU BIT(21)
#घोषणा TCAN4X5X_MCAN_IR_BEC BIT(20)
#घोषणा TCAN4X5X_MCAN_IR_DRX BIT(19)
#घोषणा TCAN4X5X_MCAN_IR_TOO BIT(18)
#घोषणा TCAN4X5X_MCAN_IR_MRAF BIT(17)
#घोषणा TCAN4X5X_MCAN_IR_TSW BIT(16)
#घोषणा TCAN4X5X_MCAN_IR_TEFL BIT(15)
#घोषणा TCAN4X5X_MCAN_IR_TEFF BIT(14)
#घोषणा TCAN4X5X_MCAN_IR_TEFW BIT(13)
#घोषणा TCAN4X5X_MCAN_IR_TEFN BIT(12)
#घोषणा TCAN4X5X_MCAN_IR_TFE BIT(11)
#घोषणा TCAN4X5X_MCAN_IR_TCF BIT(10)
#घोषणा TCAN4X5X_MCAN_IR_TC BIT(9)
#घोषणा TCAN4X5X_MCAN_IR_HPM BIT(8)
#घोषणा TCAN4X5X_MCAN_IR_RF1L BIT(7)
#घोषणा TCAN4X5X_MCAN_IR_RF1F BIT(6)
#घोषणा TCAN4X5X_MCAN_IR_RF1W BIT(5)
#घोषणा TCAN4X5X_MCAN_IR_RF1N BIT(4)
#घोषणा TCAN4X5X_MCAN_IR_RF0L BIT(3)
#घोषणा TCAN4X5X_MCAN_IR_RF0F BIT(2)
#घोषणा TCAN4X5X_MCAN_IR_RF0W BIT(1)
#घोषणा TCAN4X5X_MCAN_IR_RF0N BIT(0)
#घोषणा TCAN4X5X_ENABLE_MCAN_INT \
	(TCAN4X5X_MCAN_IR_TC | TCAN4X5X_MCAN_IR_RF0N | \
	 TCAN4X5X_MCAN_IR_RF1N | TCAN4X5X_MCAN_IR_RF0F | \
	 TCAN4X5X_MCAN_IR_RF1F)

#घोषणा TCAN4X5X_MRAM_START 0x8000
#घोषणा TCAN4X5X_MCAN_OFFSET 0x1000

#घोषणा TCAN4X5X_CLEAR_ALL_INT 0xffffffff
#घोषणा TCAN4X5X_SET_ALL_INT 0xffffffff

#घोषणा TCAN4X5X_MODE_SEL_MASK (BIT(7) | BIT(6))
#घोषणा TCAN4X5X_MODE_SLEEP 0x00
#घोषणा TCAN4X5X_MODE_STANDBY BIT(6)
#घोषणा TCAN4X5X_MODE_NORMAL BIT(7)

#घोषणा TCAN4X5X_DISABLE_WAKE_MSK	(BIT(31) | BIT(30))
#घोषणा TCAN4X5X_DISABLE_INH_MSK	BIT(9)

#घोषणा TCAN4X5X_SW_RESET BIT(2)

#घोषणा TCAN4X5X_MCAN_CONFIGURED BIT(5)
#घोषणा TCAN4X5X_WATCHDOG_EN BIT(3)
#घोषणा TCAN4X5X_WD_60_MS_TIMER 0
#घोषणा TCAN4X5X_WD_600_MS_TIMER BIT(28)
#घोषणा TCAN4X5X_WD_3_S_TIMER BIT(29)
#घोषणा TCAN4X5X_WD_6_S_TIMER (BIT(28) | BIT(29))

अटल अंतरभूत काष्ठा tcan4x5x_priv *cdev_to_priv(काष्ठा m_can_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा tcan4x5x_priv, cdev);

पूर्ण

अटल व्योम tcan4x5x_check_wake(काष्ठा tcan4x5x_priv *priv)
अणु
	पूर्णांक wake_state = 0;

	अगर (priv->device_state_gpio)
		wake_state = gpiod_get_value(priv->device_state_gpio);

	अगर (priv->device_wake_gpio && wake_state) अणु
		gpiod_set_value(priv->device_wake_gpio, 0);
		usleep_range(5, 50);
		gpiod_set_value(priv->device_wake_gpio, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक tcan4x5x_reset(काष्ठा tcan4x5x_priv *priv)
अणु
	पूर्णांक ret = 0;

	अगर (priv->reset_gpio) अणु
		gpiod_set_value(priv->reset_gpio, 1);

		/* tpulse_width minimum 30us */
		usleep_range(30, 100);
		gpiod_set_value(priv->reset_gpio, 0);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(priv->regmap, TCAN4X5X_CONFIG,
				   TCAN4X5X_SW_RESET);
		अगर (ret)
			वापस ret;
	पूर्ण

	usleep_range(700, 1000);

	वापस ret;
पूर्ण

अटल u32 tcan4x5x_पढ़ो_reg(काष्ठा m_can_classdev *cdev, पूर्णांक reg)
अणु
	काष्ठा tcan4x5x_priv *priv = cdev_to_priv(cdev);
	u32 val;

	regmap_पढ़ो(priv->regmap, TCAN4X5X_MCAN_OFFSET + reg, &val);

	वापस val;
पूर्ण

अटल u32 tcan4x5x_पढ़ो_fअगरo(काष्ठा m_can_classdev *cdev, पूर्णांक addr_offset)
अणु
	काष्ठा tcan4x5x_priv *priv = cdev_to_priv(cdev);
	u32 val;

	regmap_पढ़ो(priv->regmap, TCAN4X5X_MRAM_START + addr_offset, &val);

	वापस val;
पूर्ण

अटल पूर्णांक tcan4x5x_ग_लिखो_reg(काष्ठा m_can_classdev *cdev, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा tcan4x5x_priv *priv = cdev_to_priv(cdev);

	वापस regmap_ग_लिखो(priv->regmap, TCAN4X5X_MCAN_OFFSET + reg, val);
पूर्ण

अटल पूर्णांक tcan4x5x_ग_लिखो_fअगरo(काष्ठा m_can_classdev *cdev,
			       पूर्णांक addr_offset, पूर्णांक val)
अणु
	काष्ठा tcan4x5x_priv *priv = cdev_to_priv(cdev);

	वापस regmap_ग_लिखो(priv->regmap, TCAN4X5X_MRAM_START + addr_offset, val);
पूर्ण

अटल पूर्णांक tcan4x5x_घातer_enable(काष्ठा regulator *reg, पूर्णांक enable)
अणु
	अगर (IS_ERR_OR_शून्य(reg))
		वापस 0;

	अगर (enable)
		वापस regulator_enable(reg);
	अन्यथा
		वापस regulator_disable(reg);
पूर्ण

अटल पूर्णांक tcan4x5x_ग_लिखो_tcan_reg(काष्ठा m_can_classdev *cdev,
				   पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा tcan4x5x_priv *priv = cdev_to_priv(cdev);

	वापस regmap_ग_लिखो(priv->regmap, reg, val);
पूर्ण

अटल पूर्णांक tcan4x5x_clear_पूर्णांकerrupts(काष्ठा m_can_classdev *cdev)
अणु
	पूर्णांक ret;

	ret = tcan4x5x_ग_लिखो_tcan_reg(cdev, TCAN4X5X_STATUS,
				      TCAN4X5X_CLEAR_ALL_INT);
	अगर (ret)
		वापस ret;

	ret = tcan4x5x_ग_लिखो_tcan_reg(cdev, TCAN4X5X_MCAN_INT_REG,
				      TCAN4X5X_ENABLE_MCAN_INT);
	अगर (ret)
		वापस ret;

	ret = tcan4x5x_ग_लिखो_tcan_reg(cdev, TCAN4X5X_INT_FLAGS,
				      TCAN4X5X_CLEAR_ALL_INT);
	अगर (ret)
		वापस ret;

	वापस tcan4x5x_ग_लिखो_tcan_reg(cdev, TCAN4X5X_ERROR_STATUS,
				       TCAN4X5X_CLEAR_ALL_INT);
पूर्ण

अटल पूर्णांक tcan4x5x_init(काष्ठा m_can_classdev *cdev)
अणु
	काष्ठा tcan4x5x_priv *tcan4x5x = cdev_to_priv(cdev);
	पूर्णांक ret;

	tcan4x5x_check_wake(tcan4x5x);

	ret = tcan4x5x_clear_पूर्णांकerrupts(cdev);
	अगर (ret)
		वापस ret;

	ret = tcan4x5x_ग_लिखो_tcan_reg(cdev, TCAN4X5X_INT_EN,
				      TCAN4X5X_ENABLE_TCAN_INT);
	अगर (ret)
		वापस ret;

	/* Zero out the MCAN buffers */
	m_can_init_ram(cdev);

	ret = regmap_update_bits(tcan4x5x->regmap, TCAN4X5X_CONFIG,
				 TCAN4X5X_MODE_SEL_MASK, TCAN4X5X_MODE_NORMAL);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक tcan4x5x_disable_wake(काष्ठा m_can_classdev *cdev)
अणु
	काष्ठा tcan4x5x_priv *tcan4x5x = cdev_to_priv(cdev);

	वापस regmap_update_bits(tcan4x5x->regmap, TCAN4X5X_CONFIG,
				  TCAN4X5X_DISABLE_WAKE_MSK, 0x00);
पूर्ण

अटल पूर्णांक tcan4x5x_disable_state(काष्ठा m_can_classdev *cdev)
अणु
	काष्ठा tcan4x5x_priv *tcan4x5x = cdev_to_priv(cdev);

	वापस regmap_update_bits(tcan4x5x->regmap, TCAN4X5X_CONFIG,
				  TCAN4X5X_DISABLE_INH_MSK, 0x01);
पूर्ण

अटल पूर्णांक tcan4x5x_get_gpios(काष्ठा m_can_classdev *cdev)
अणु
	काष्ठा tcan4x5x_priv *tcan4x5x = cdev_to_priv(cdev);
	पूर्णांक ret;

	tcan4x5x->device_wake_gpio = devm_gpiod_get(cdev->dev, "device-wake",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(tcan4x5x->device_wake_gpio)) अणु
		अगर (PTR_ERR(tcan4x5x->device_wake_gpio) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		tcan4x5x_disable_wake(cdev);
	पूर्ण

	tcan4x5x->reset_gpio = devm_gpiod_get_optional(cdev->dev, "reset",
						       GPIOD_OUT_LOW);
	अगर (IS_ERR(tcan4x5x->reset_gpio))
		tcan4x5x->reset_gpio = शून्य;

	ret = tcan4x5x_reset(tcan4x5x);
	अगर (ret)
		वापस ret;

	tcan4x5x->device_state_gpio = devm_gpiod_get_optional(cdev->dev,
							      "device-state",
							      GPIOD_IN);
	अगर (IS_ERR(tcan4x5x->device_state_gpio)) अणु
		tcan4x5x->device_state_gpio = शून्य;
		tcan4x5x_disable_state(cdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा m_can_ops tcan4x5x_ops = अणु
	.init = tcan4x5x_init,
	.पढ़ो_reg = tcan4x5x_पढ़ो_reg,
	.ग_लिखो_reg = tcan4x5x_ग_लिखो_reg,
	.ग_लिखो_fअगरo = tcan4x5x_ग_लिखो_fअगरo,
	.पढ़ो_fअगरo = tcan4x5x_पढ़ो_fअगरo,
	.clear_पूर्णांकerrupts = tcan4x5x_clear_पूर्णांकerrupts,
पूर्ण;

अटल पूर्णांक tcan4x5x_can_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tcan4x5x_priv *priv;
	काष्ठा m_can_classdev *mcan_class;
	पूर्णांक freq, ret;

	mcan_class = m_can_class_allocate_dev(&spi->dev,
					      माप(काष्ठा tcan4x5x_priv));
	अगर (!mcan_class)
		वापस -ENOMEM;

	priv = cdev_to_priv(mcan_class);

	priv->घातer = devm_regulator_get_optional(&spi->dev, "vsup");
	अगर (PTR_ERR(priv->घातer) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ out_m_can_class_मुक्त_dev;
	पूर्ण अन्यथा अणु
		priv->घातer = शून्य;
	पूर्ण

	m_can_class_get_घड़ीs(mcan_class);
	अगर (IS_ERR(mcan_class->cclk)) अणु
		dev_err(&spi->dev, "no CAN clock source defined\n");
		freq = TCAN4X5X_EXT_CLK_DEF;
	पूर्ण अन्यथा अणु
		freq = clk_get_rate(mcan_class->cclk);
	पूर्ण

	/* Sanity check */
	अगर (freq < 20000000 || freq > TCAN4X5X_EXT_CLK_DEF) अणु
		ret = -दुस्फल;
		जाओ out_m_can_class_मुक्त_dev;
	पूर्ण

	priv->spi = spi;

	mcan_class->pm_घड़ी_support = 0;
	mcan_class->can.घड़ी.freq = freq;
	mcan_class->dev = &spi->dev;
	mcan_class->ops = &tcan4x5x_ops;
	mcan_class->is_peripheral = true;
	mcan_class->net->irq = spi->irq;

	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret)
		जाओ out_m_can_class_मुक्त_dev;

	ret = tcan4x5x_regmap_init(priv);
	अगर (ret)
		जाओ out_m_can_class_मुक्त_dev;

	ret = tcan4x5x_घातer_enable(priv->घातer, 1);
	अगर (ret)
		जाओ out_m_can_class_मुक्त_dev;

	ret = tcan4x5x_get_gpios(mcan_class);
	अगर (ret)
		जाओ out_घातer;

	ret = tcan4x5x_init(mcan_class);
	अगर (ret)
		जाओ out_घातer;

	ret = m_can_class_रेजिस्टर(mcan_class);
	अगर (ret)
		जाओ out_घातer;

	netdev_info(mcan_class->net, "TCAN4X5X successfully initialized.\n");
	वापस 0;

out_घातer:
	tcan4x5x_घातer_enable(priv->घातer, 0);
 out_m_can_class_मुक्त_dev:
	m_can_class_मुक्त_dev(mcan_class->net);
	वापस ret;
पूर्ण

अटल पूर्णांक tcan4x5x_can_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा tcan4x5x_priv *priv = spi_get_drvdata(spi);

	m_can_class_unरेजिस्टर(&priv->cdev);

	tcan4x5x_घातer_enable(priv->घातer, 0);

	m_can_class_मुक्त_dev(priv->cdev.net);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tcan4x5x_of_match[] = अणु
	अणु
		.compatible = "ti,tcan4x5x",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tcan4x5x_of_match);

अटल स्थिर काष्ठा spi_device_id tcan4x5x_id_table[] = अणु
	अणु
		.name = "tcan4x5x",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, tcan4x5x_id_table);

अटल काष्ठा spi_driver tcan4x5x_can_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = tcan4x5x_of_match,
		.pm = शून्य,
	पूर्ण,
	.id_table = tcan4x5x_id_table,
	.probe = tcan4x5x_can_probe,
	.हटाओ = tcan4x5x_can_हटाओ,
पूर्ण;
module_spi_driver(tcan4x5x_can_driver);

MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_DESCRIPTION("Texas Instruments TCAN4x5x CAN driver");
MODULE_LICENSE("GPL v2");
