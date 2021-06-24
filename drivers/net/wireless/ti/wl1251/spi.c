<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/swab.h>
#समावेश <linux/crc7.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/wl12xx.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "spi.h"

अटल irqवापस_t wl1251_irq(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wl1251 *wl;

	wl1251_debug(DEBUG_IRQ, "IRQ");

	wl = cookie;

	ieee80211_queue_work(wl->hw, &wl->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा spi_device *wl_to_spi(काष्ठा wl1251 *wl)
अणु
	वापस wl->अगर_priv;
पूर्ण

अटल व्योम wl1251_spi_reset(काष्ठा wl1251 *wl)
अणु
	u8 *cmd;
	काष्ठा spi_transfer t;
	काष्ठा spi_message m;

	cmd = kzalloc(WSPI_INIT_CMD_LEN, GFP_KERNEL);
	अगर (!cmd) अणु
		wl1251_error("could not allocate cmd for spi reset");
		वापस;
	पूर्ण

	स_रखो(&t, 0, माप(t));
	spi_message_init(&m);

	स_रखो(cmd, 0xff, WSPI_INIT_CMD_LEN);

	t.tx_buf = cmd;
	t.len = WSPI_INIT_CMD_LEN;
	spi_message_add_tail(&t, &m);

	spi_sync(wl_to_spi(wl), &m);

	wl1251_dump(DEBUG_SPI, "spi reset -> ", cmd, WSPI_INIT_CMD_LEN);

	kमुक्त(cmd);
पूर्ण

अटल व्योम wl1251_spi_wake(काष्ठा wl1251 *wl)
अणु
	काष्ठा spi_transfer t;
	काष्ठा spi_message m;
	u8 *cmd = kzalloc(WSPI_INIT_CMD_LEN, GFP_KERNEL);

	अगर (!cmd) अणु
		wl1251_error("could not allocate cmd for spi init");
		वापस;
	पूर्ण

	स_रखो(&t, 0, माप(t));
	spi_message_init(&m);

	/* Set WSPI_INIT_COMMAND
	 * the data is being send from the MSB to LSB
	 */
	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = WSPI_INIT_CMD_START | WSPI_INIT_CMD_TX;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = HW_ACCESS_WSPI_INIT_CMD_MASK << 3;
	cmd[5] |= HW_ACCESS_WSPI_FIXED_BUSY_LEN & WSPI_INIT_CMD_FIXEDBUSY_LEN;

	cmd[6] = WSPI_INIT_CMD_IOD | WSPI_INIT_CMD_IP | WSPI_INIT_CMD_CS
		| WSPI_INIT_CMD_WSPI | WSPI_INIT_CMD_WS;

	अगर (HW_ACCESS_WSPI_FIXED_BUSY_LEN == 0)
		cmd[6] |= WSPI_INIT_CMD_DIS_FIXEDBUSY;
	अन्यथा
		cmd[6] |= WSPI_INIT_CMD_EN_FIXEDBUSY;

	cmd[7] = crc7_be(0, cmd+2, WSPI_INIT_CMD_CRC_LEN) | WSPI_INIT_CMD_END;
	/*
	 * The above is the logical order; it must actually be stored
	 * in the buffer byte-swapped.
	 */
	__swab32s((u32 *)cmd);
	__swab32s((u32 *)cmd+1);

	t.tx_buf = cmd;
	t.len = WSPI_INIT_CMD_LEN;
	spi_message_add_tail(&t, &m);

	spi_sync(wl_to_spi(wl), &m);

	wl1251_dump(DEBUG_SPI, "spi init -> ", cmd, WSPI_INIT_CMD_LEN);

	kमुक्त(cmd);
पूर्ण

अटल व्योम wl1251_spi_reset_wake(काष्ठा wl1251 *wl)
अणु
	wl1251_spi_reset(wl);
	wl1251_spi_wake(wl);
पूर्ण

अटल व्योम wl1251_spi_पढ़ो(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf,
			    माप_प्रकार len)
अणु
	काष्ठा spi_transfer t[3];
	काष्ठा spi_message m;
	u8 *busy_buf;
	u32 *cmd;

	cmd = &wl->buffer_cmd;
	busy_buf = wl->buffer_busyword;

	*cmd = 0;
	*cmd |= WSPI_CMD_READ;
	*cmd |= (len << WSPI_CMD_BYTE_LENGTH_OFFSET) & WSPI_CMD_BYTE_LENGTH;
	*cmd |= addr & WSPI_CMD_BYTE_ADDR;

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = cmd;
	t[0].len = 4;
	spi_message_add_tail(&t[0], &m);

	/* Busy and non busy words पढ़ो */
	t[1].rx_buf = busy_buf;
	t[1].len = WL1251_BUSY_WORD_LEN;
	spi_message_add_tail(&t[1], &m);

	t[2].rx_buf = buf;
	t[2].len = len;
	spi_message_add_tail(&t[2], &m);

	spi_sync(wl_to_spi(wl), &m);

	/* FIXME: check busy words */

	wl1251_dump(DEBUG_SPI, "spi_read cmd -> ", cmd, माप(*cmd));
	wl1251_dump(DEBUG_SPI, "spi_read buf <- ", buf, len);
पूर्ण

अटल व्योम wl1251_spi_ग_लिखो(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf,
			     माप_प्रकार len)
अणु
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	u32 *cmd;

	cmd = &wl->buffer_cmd;

	*cmd = 0;
	*cmd |= WSPI_CMD_WRITE;
	*cmd |= (len << WSPI_CMD_BYTE_LENGTH_OFFSET) & WSPI_CMD_BYTE_LENGTH;
	*cmd |= addr & WSPI_CMD_BYTE_ADDR;

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = cmd;
	t[0].len = माप(*cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	spi_sync(wl_to_spi(wl), &m);

	wl1251_dump(DEBUG_SPI, "spi_write cmd -> ", cmd, माप(*cmd));
	wl1251_dump(DEBUG_SPI, "spi_write buf -> ", buf, len);
पूर्ण

अटल व्योम wl1251_spi_enable_irq(काष्ठा wl1251 *wl)
अणु
	वापस enable_irq(wl->irq);
पूर्ण

अटल व्योम wl1251_spi_disable_irq(काष्ठा wl1251 *wl)
अणु
	वापस disable_irq(wl->irq);
पूर्ण

अटल पूर्णांक wl1251_spi_set_घातer(काष्ठा wl1251 *wl, bool enable)
अणु
	अगर (gpio_is_valid(wl->घातer_gpio))
		gpio_set_value(wl->घातer_gpio, enable);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wl1251_अगर_operations wl1251_spi_ops = अणु
	.पढ़ो = wl1251_spi_पढ़ो,
	.ग_लिखो = wl1251_spi_ग_लिखो,
	.reset = wl1251_spi_reset_wake,
	.enable_irq = wl1251_spi_enable_irq,
	.disable_irq = wl1251_spi_disable_irq,
	.घातer = wl1251_spi_set_घातer,
पूर्ण;

अटल पूर्णांक wl1251_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wl1251_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा device_node *np = spi->dev.of_node;
	काष्ठा ieee80211_hw *hw;
	काष्ठा wl1251 *wl;
	पूर्णांक ret;

	अगर (!np && !pdata) अणु
		wl1251_error("no platform data");
		वापस -ENODEV;
	पूर्ण

	hw = wl1251_alloc_hw();
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	wl = hw->priv;

	SET_IEEE80211_DEV(hw, &spi->dev);
	spi_set_drvdata(spi, wl);
	wl->अगर_priv = spi;
	wl->अगर_ops = &wl1251_spi_ops;

	/* This is the only SPI value that we need to set here, the rest
	 * comes from the board-peripherals file
	 */
	spi->bits_per_word = 32;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		wl1251_error("spi_setup failed");
		जाओ out_मुक्त;
	पूर्ण

	अगर (np) अणु
		wl->use_eeprom = of_property_पढ़ो_bool(np, "ti,wl1251-has-eeprom");
		wl->घातer_gpio = of_get_named_gpio(np, "ti,power-gpio", 0);
	पूर्ण अन्यथा अगर (pdata) अणु
		wl->घातer_gpio = pdata->घातer_gpio;
		wl->use_eeprom = pdata->use_eeprom;
	पूर्ण

	अगर (wl->घातer_gpio == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ out_मुक्त;
	पूर्ण

	अगर (gpio_is_valid(wl->घातer_gpio)) अणु
		ret = devm_gpio_request_one(&spi->dev, wl->घातer_gpio,
					GPIOF_OUT_INIT_LOW, "wl1251 power");
		अगर (ret) अणु
			wl1251_error("Failed to request gpio: %d\n", ret);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		wl1251_error("set power gpio missing in platform data");
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	wl->irq = spi->irq;
	अगर (wl->irq < 0) अणु
		wl1251_error("irq missing in platform data");
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	irq_set_status_flags(wl->irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&spi->dev, wl->irq, wl1251_irq, 0,
							DRIVER_NAME, wl);
	अगर (ret < 0) अणु
		wl1251_error("request_irq() failed: %d", ret);
		जाओ out_मुक्त;
	पूर्ण

	irq_set_irq_type(wl->irq, IRQ_TYPE_EDGE_RISING);

	wl->vio = devm_regulator_get(&spi->dev, "vio");
	अगर (IS_ERR(wl->vio)) अणु
		ret = PTR_ERR(wl->vio);
		wl1251_error("vio regulator missing: %d", ret);
		जाओ out_मुक्त;
	पूर्ण

	ret = regulator_enable(wl->vio);
	अगर (ret)
		जाओ out_मुक्त;

	ret = wl1251_init_ieee80211(wl);
	अगर (ret)
		जाओ disable_regulator;

	वापस 0;

disable_regulator:
	regulator_disable(wl->vio);
out_मुक्त:
	ieee80211_मुक्त_hw(hw);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा wl1251 *wl = spi_get_drvdata(spi);

	wl1251_मुक्त_hw(wl);
	regulator_disable(wl->vio);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver wl1251_spi_driver = अणु
	.driver = अणु
		.name		= DRIVER_NAME,
	पूर्ण,

	.probe		= wl1251_spi_probe,
	.हटाओ		= wl1251_spi_हटाओ,
पूर्ण;

module_spi_driver(wl1251_spi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kalle Valo <kvalo@adurom.com>");
MODULE_ALIAS("spi:wl1251");
