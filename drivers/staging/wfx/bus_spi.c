<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI पूर्णांकerface.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2011, Sagrad Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>

#समावेश "bus.h"
#समावेश "wfx.h"
#समावेश "hwio.h"
#समावेश "main.h"
#समावेश "bh.h"

#घोषणा SET_WRITE 0x7FFF        /* usage: and operation */
#घोषणा SET_READ 0x8000         /* usage: or operation */

#घोषणा WFX_RESET_INVERTED 1

अटल स्थिर काष्ठा wfx_platक्रमm_data wfx_spi_pdata = अणु
	.file_fw = "wfm_wf200",
	.file_pds = "wf200.pds",
	.use_rising_clk = true,
पूर्ण;

काष्ठा wfx_spi_priv अणु
	काष्ठा spi_device *func;
	काष्ठा wfx_dev *core;
	काष्ठा gpio_desc *gpio_reset;
	bool need_swab;
पूर्ण;

/*
 * WFx chip पढ़ो data 16bits at समय and place them directly पूर्णांकo (little
 * endian) CPU रेजिस्टर. So, chip expect byte order like "B1 B0 B3 B2" (जबतक
 * LE is "B0 B1 B2 B3" and BE is "B3 B2 B1 B0")
 *
 * A little endian host with bits_per_word == 16 should करो the right job
 * natively. The code below to support big endian host and commonly used SPI
 * 8bits.
 */
अटल पूर्णांक wfx_spi_copy_from_io(व्योम *priv, अचिन्हित पूर्णांक addr,
				व्योम *dst, माप_प्रकार count)
अणु
	काष्ठा wfx_spi_priv *bus = priv;
	u16 regaddr = (addr << 12) | (count / 2) | SET_READ;
	काष्ठा spi_message      m;
	काष्ठा spi_transfer     t_addr = अणु
		.tx_buf         = &regaddr,
		.len            = माप(regaddr),
	पूर्ण;
	काष्ठा spi_transfer     t_msg = अणु
		.rx_buf         = dst,
		.len            = count,
	पूर्ण;
	u16 *dst16 = dst;
	पूर्णांक ret, i;

	WARN(count % 2, "buffer size must be a multiple of 2");

	cpu_to_le16s(&regaddr);
	अगर (bus->need_swab)
		swab16s(&regaddr);

	spi_message_init(&m);
	spi_message_add_tail(&t_addr, &m);
	spi_message_add_tail(&t_msg, &m);
	ret = spi_sync(bus->func, &m);

	अगर (bus->need_swab && addr == WFX_REG_CONFIG)
		क्रम (i = 0; i < count / 2; i++)
			swab16s(&dst16[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक wfx_spi_copy_to_io(व्योम *priv, अचिन्हित पूर्णांक addr,
			      स्थिर व्योम *src, माप_प्रकार count)
अणु
	काष्ठा wfx_spi_priv *bus = priv;
	u16 regaddr = (addr << 12) | (count / 2);
	// FIXME: use a bounce buffer
	u16 *src16 = (व्योम *)src;
	पूर्णांक ret, i;
	काष्ठा spi_message      m;
	काष्ठा spi_transfer     t_addr = अणु
		.tx_buf         = &regaddr,
		.len            = माप(regaddr),
	पूर्ण;
	काष्ठा spi_transfer     t_msg = अणु
		.tx_buf         = src,
		.len            = count,
	पूर्ण;

	WARN(count % 2, "buffer size must be a multiple of 2");
	WARN(regaddr & SET_READ, "bad addr or size overflow");

	cpu_to_le16s(&regaddr);

	// Register address and CONFIG content always use 16bit big endian
	// ("BADC" order)
	अगर (bus->need_swab)
		swab16s(&regaddr);
	अगर (bus->need_swab && addr == WFX_REG_CONFIG)
		क्रम (i = 0; i < count / 2; i++)
			swab16s(&src16[i]);

	spi_message_init(&m);
	spi_message_add_tail(&t_addr, &m);
	spi_message_add_tail(&t_msg, &m);
	ret = spi_sync(bus->func, &m);

	अगर (bus->need_swab && addr == WFX_REG_CONFIG)
		क्रम (i = 0; i < count / 2; i++)
			swab16s(&src16[i]);
	वापस ret;
पूर्ण

अटल व्योम wfx_spi_lock(व्योम *priv)
अणु
पूर्ण

अटल व्योम wfx_spi_unlock(व्योम *priv)
अणु
पूर्ण

अटल irqवापस_t wfx_spi_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा wfx_spi_priv *bus = priv;

	wfx_bh_request_rx(bus->core);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wfx_spi_irq_subscribe(व्योम *priv)
अणु
	काष्ठा wfx_spi_priv *bus = priv;
	u32 flags;

	flags = irq_get_trigger_type(bus->func->irq);
	अगर (!flags)
		flags = IRQF_TRIGGER_HIGH;
	flags |= IRQF_ONESHOT;
	वापस devm_request_thपढ़ोed_irq(&bus->func->dev, bus->func->irq, शून्य,
					 wfx_spi_irq_handler, IRQF_ONESHOT,
					 "wfx", bus);
पूर्ण

अटल पूर्णांक wfx_spi_irq_unsubscribe(व्योम *priv)
अणु
	काष्ठा wfx_spi_priv *bus = priv;

	devm_मुक्त_irq(&bus->func->dev, bus->func->irq, bus);
	वापस 0;
पूर्ण

अटल माप_प्रकार wfx_spi_align_size(व्योम *priv, माप_प्रकार size)
अणु
	// Most of SPI controllers aव्योम DMA अगर buffer size is not 32bit aligned
	वापस ALIGN(size, 4);
पूर्ण

अटल स्थिर काष्ठा hwbus_ops wfx_spi_hwbus_ops = अणु
	.copy_from_io = wfx_spi_copy_from_io,
	.copy_to_io = wfx_spi_copy_to_io,
	.irq_subscribe = wfx_spi_irq_subscribe,
	.irq_unsubscribe = wfx_spi_irq_unsubscribe,
	.lock			= wfx_spi_lock,
	.unlock			= wfx_spi_unlock,
	.align_size		= wfx_spi_align_size,
पूर्ण;

अटल पूर्णांक wfx_spi_probe(काष्ठा spi_device *func)
अणु
	काष्ठा wfx_spi_priv *bus;
	पूर्णांक ret;

	अगर (!func->bits_per_word)
		func->bits_per_word = 16;
	ret = spi_setup(func);
	अगर (ret)
		वापस ret;
	// Trace below is also displayed by spi_setup() अगर compiled with DEBUG
	dev_dbg(&func->dev, "SPI params: CS=%d, mode=%d bits/word=%d speed=%d\n",
		func->chip_select, func->mode, func->bits_per_word,
		func->max_speed_hz);
	अगर (func->bits_per_word != 16 && func->bits_per_word != 8)
		dev_warn(&func->dev, "unusual bits/word value: %d\n",
			 func->bits_per_word);
	अगर (func->max_speed_hz > 50000000)
		dev_warn(&func->dev, "%dHz is a very high speed\n",
			 func->max_speed_hz);

	bus = devm_kzalloc(&func->dev, माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;
	bus->func = func;
	अगर (func->bits_per_word == 8 || IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		bus->need_swab = true;
	spi_set_drvdata(func, bus);

	bus->gpio_reset = devm_gpiod_get_optional(&func->dev, "reset",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(bus->gpio_reset))
		वापस PTR_ERR(bus->gpio_reset);
	अगर (!bus->gpio_reset) अणु
		dev_warn(&func->dev,
			 "gpio reset is not defined, trying to load firmware anyway\n");
	पूर्ण अन्यथा अणु
		gpiod_set_consumer_name(bus->gpio_reset, "wfx reset");
		अगर (spi_get_device_id(func)->driver_data & WFX_RESET_INVERTED)
			gpiod_toggle_active_low(bus->gpio_reset);
		gpiod_set_value_cansleep(bus->gpio_reset, 1);
		usleep_range(100, 150);
		gpiod_set_value_cansleep(bus->gpio_reset, 0);
		usleep_range(2000, 2500);
	पूर्ण

	bus->core = wfx_init_common(&func->dev, &wfx_spi_pdata,
				    &wfx_spi_hwbus_ops, bus);
	अगर (!bus->core)
		वापस -EIO;

	वापस wfx_probe(bus->core);
पूर्ण

अटल पूर्णांक wfx_spi_हटाओ(काष्ठा spi_device *func)
अणु
	काष्ठा wfx_spi_priv *bus = spi_get_drvdata(func);

	wfx_release(bus->core);
	वापस 0;
पूर्ण

/*
 * For dynamic driver binding, kernel करोes not use OF to match driver. It only
 * use modalias and modalias is a copy of 'compatible' DT node with venकरोr
 * stripped.
 */
अटल स्थिर काष्ठा spi_device_id wfx_spi_id[] = अणु
	अणु "wfx-spi", WFX_RESET_INVERTED पूर्ण,
	अणु "wf200", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, wfx_spi_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id wfx_spi_of_match[] = अणु
	अणु .compatible = "silabs,wfx-spi", .data = (व्योम *)WFX_RESET_INVERTED पूर्ण,
	अणु .compatible = "silabs,wf200" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wfx_spi_of_match);
#पूर्ण_अगर

काष्ठा spi_driver wfx_spi_driver = अणु
	.driver = अणु
		.name = "wfx-spi",
		.of_match_table = of_match_ptr(wfx_spi_of_match),
	पूर्ण,
	.id_table = wfx_spi_id,
	.probe = wfx_spi_probe,
	.हटाओ = wfx_spi_हटाओ,
पूर्ण;
