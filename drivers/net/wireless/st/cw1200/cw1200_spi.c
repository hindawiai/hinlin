<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mac80211 SPI driver क्रम ST-Ericsson CW1200 device
 *
 * Copyright (c) 2011, Sagrad Inc.
 * Author:  Solomon Peachy <speachy@sagrad.com>
 *
 * Based on cw1200_sdio.c
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/mac80211.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/device.h>

#समावेश "cw1200.h"
#समावेश "hwbus.h"
#समावेश <linux/platक्रमm_data/net-cw1200.h>
#समावेश "hwio.h"

MODULE_AUTHOR("Solomon Peachy <speachy@sagrad.com>");
MODULE_DESCRIPTION("mac80211 ST-Ericsson CW1200 SPI driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:cw1200_wlan_spi");

/* #घोषणा SPI_DEBUG */

काष्ठा hwbus_priv अणु
	काष्ठा spi_device	*func;
	काष्ठा cw1200_common	*core;
	स्थिर काष्ठा cw1200_platक्रमm_data_spi *pdata;
	spinlock_t		lock; /* Serialize all bus operations */
	रुको_queue_head_t       wq;
	पूर्णांक claimed;
पूर्ण;

#घोषणा SDIO_TO_SPI_ADDR(addr) ((addr & 0x1f)>>2)
#घोषणा SET_WRITE 0x7FFF /* usage: and operation */
#घोषणा SET_READ 0x8000  /* usage: or operation */

/* Notes on byte ordering:
   LE:  B0 B1 B2 B3
   BE:  B3 B2 B1 B0

   Hardware expects 32-bit data to be written as 16-bit BE words:

   B1 B0 B3 B2
*/

अटल पूर्णांक cw1200_spi_स_नकल_fromio(काष्ठा hwbus_priv *self,
				     अचिन्हित पूर्णांक addr,
				     व्योम *dst, पूर्णांक count)
अणु
	पूर्णांक ret, i;
	u16 regaddr;
	काष्ठा spi_message      m;

	काष्ठा spi_transfer     t_addr = अणु
		.tx_buf         = &regaddr,
		.len            = माप(regaddr),
	पूर्ण;
	काष्ठा spi_transfer     t_msg = अणु
		.rx_buf         = dst,
		.len            = count,
	पूर्ण;

	regaddr = (SDIO_TO_SPI_ADDR(addr))<<12;
	regaddr |= SET_READ;
	regaddr |= (count>>1);

#अगर_घोषित SPI_DEBUG
	pr_info("READ : %04d from 0x%02x (%04x)\n", count, addr, regaddr);
#पूर्ण_अगर

	/* Header is LE16 */
	regaddr = cpu_to_le16(regaddr);

	/* We have to byteswap अगर the SPI bus is limited to 8b operation
	   or we are running on a Big Endian प्रणाली
	*/
#अगर defined(__LITTLE_ENDIAN)
	अगर (self->func->bits_per_word == 8)
#पूर्ण_अगर
		regaddr = swab16(regaddr);

	spi_message_init(&m);
	spi_message_add_tail(&t_addr, &m);
	spi_message_add_tail(&t_msg, &m);
	ret = spi_sync(self->func, &m);

#अगर_घोषित SPI_DEBUG
	pr_info("READ : ");
	क्रम (i = 0; i < t_addr.len; i++)
		prपूर्णांकk("%02x ", ((u8 *)t_addr.tx_buf)[i]);
	prपूर्णांकk(" : ");
	क्रम (i = 0; i < t_msg.len; i++)
		prपूर्णांकk("%02x ", ((u8 *)t_msg.rx_buf)[i]);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	/* We have to byteswap अगर the SPI bus is limited to 8b operation
	   or we are running on a Big Endian प्रणाली
	*/
#अगर defined(__LITTLE_ENDIAN)
	अगर (self->func->bits_per_word == 8)
#पूर्ण_अगर
	अणु
		uपूर्णांक16_t *buf = (uपूर्णांक16_t *)dst;
		क्रम (i = 0; i < ((count + 1) >> 1); i++)
			buf[i] = swab16(buf[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_spi_स_नकल_toio(काष्ठा hwbus_priv *self,
				   अचिन्हित पूर्णांक addr,
				   स्थिर व्योम *src, पूर्णांक count)
अणु
	पूर्णांक rval, i;
	u16 regaddr;
	काष्ठा spi_transfer     t_addr = अणु
		.tx_buf         = &regaddr,
		.len            = माप(regaddr),
	पूर्ण;
	काष्ठा spi_transfer     t_msg = अणु
		.tx_buf         = src,
		.len            = count,
	पूर्ण;
	काष्ठा spi_message      m;

	regaddr = (SDIO_TO_SPI_ADDR(addr))<<12;
	regaddr &= SET_WRITE;
	regaddr |= (count>>1);

#अगर_घोषित SPI_DEBUG
	pr_info("WRITE: %04d  to  0x%02x (%04x)\n", count, addr, regaddr);
#पूर्ण_अगर

	/* Header is LE16 */
	regaddr = cpu_to_le16(regaddr);

	/* We have to byteswap अगर the SPI bus is limited to 8b operation
	   or we are running on a Big Endian प्रणाली
	*/
#अगर defined(__LITTLE_ENDIAN)
	अगर (self->func->bits_per_word == 8)
#पूर्ण_अगर
	अणु
		uपूर्णांक16_t *buf = (uपूर्णांक16_t *)src;
	        regaddr = swab16(regaddr);
		क्रम (i = 0; i < ((count + 1) >> 1); i++)
			buf[i] = swab16(buf[i]);
	पूर्ण

#अगर_घोषित SPI_DEBUG
	pr_info("WRITE: ");
	क्रम (i = 0; i < t_addr.len; i++)
		prपूर्णांकk("%02x ", ((u8 *)t_addr.tx_buf)[i]);
	prपूर्णांकk(" : ");
	क्रम (i = 0; i < t_msg.len; i++)
		prपूर्णांकk("%02x ", ((u8 *)t_msg.tx_buf)[i]);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	spi_message_init(&m);
	spi_message_add_tail(&t_addr, &m);
	spi_message_add_tail(&t_msg, &m);
	rval = spi_sync(self->func, &m);

#अगर_घोषित SPI_DEBUG
	pr_info("WROTE: %d\n", m.actual_length);
#पूर्ण_अगर

#अगर defined(__LITTLE_ENDIAN)
	/* We have to byteswap अगर the SPI bus is limited to 8b operation */
	अगर (self->func->bits_per_word == 8)
#पूर्ण_अगर
	अणु
		uपूर्णांक16_t *buf = (uपूर्णांक16_t *)src;
		क्रम (i = 0; i < ((count + 1) >> 1); i++)
			buf[i] = swab16(buf[i]);
	पूर्ण
	वापस rval;
पूर्ण

अटल व्योम cw1200_spi_lock(काष्ठा hwbus_priv *self)
अणु
	अचिन्हित दीर्घ flags;

	DECLARE_WAITQUEUE(रुको, current);

	might_sleep();

	add_रुको_queue(&self->wq, &रुको);
	spin_lock_irqsave(&self->lock, flags);
	जबतक (1) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (!self->claimed)
			अवरोध;
		spin_unlock_irqrestore(&self->lock, flags);
		schedule();
		spin_lock_irqsave(&self->lock, flags);
	पूर्ण
	set_current_state(TASK_RUNNING);
	self->claimed = 1;
	spin_unlock_irqrestore(&self->lock, flags);
	हटाओ_रुको_queue(&self->wq, &रुको);

	वापस;
पूर्ण

अटल व्योम cw1200_spi_unlock(काष्ठा hwbus_priv *self)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&self->lock, flags);
	self->claimed = 0;
	spin_unlock_irqrestore(&self->lock, flags);
	wake_up(&self->wq);

	वापस;
पूर्ण

अटल irqवापस_t cw1200_spi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hwbus_priv *self = dev_id;

	अगर (self->core) अणु
		cw1200_spi_lock(self);
		cw1200_irq_handler(self->core);
		cw1200_spi_unlock(self);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक cw1200_spi_irq_subscribe(काष्ठा hwbus_priv *self)
अणु
	पूर्णांक ret;

	pr_debug("SW IRQ subscribe\n");

	ret = request_thपढ़ोed_irq(self->func->irq, शून्य,
				   cw1200_spi_irq_handler,
				   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				   "cw1200_wlan_irq", self);
	अगर (WARN_ON(ret < 0))
		जाओ निकास;

	ret = enable_irq_wake(self->func->irq);
	अगर (WARN_ON(ret))
		जाओ मुक्त_irq;

	वापस 0;

मुक्त_irq:
	मुक्त_irq(self->func->irq, self);
निकास:
	वापस ret;
पूर्ण

अटल व्योम cw1200_spi_irq_unsubscribe(काष्ठा hwbus_priv *self)
अणु
	pr_debug("SW IRQ unsubscribe\n");
	disable_irq_wake(self->func->irq);
	मुक्त_irq(self->func->irq, self);
पूर्ण

अटल पूर्णांक cw1200_spi_off(स्थिर काष्ठा cw1200_platक्रमm_data_spi *pdata)
अणु
	अगर (pdata->reset) अणु
		gpio_set_value(pdata->reset, 0);
		msleep(30); /* Min is 2 * CLK32K cycles */
		gpio_मुक्त(pdata->reset);
	पूर्ण

	अगर (pdata->घातer_ctrl)
		pdata->घातer_ctrl(pdata, false);
	अगर (pdata->clk_ctrl)
		pdata->clk_ctrl(pdata, false);

	वापस 0;
पूर्ण

अटल पूर्णांक cw1200_spi_on(स्थिर काष्ठा cw1200_platक्रमm_data_spi *pdata)
अणु
	/* Ensure I/Os are pulled low */
	अगर (pdata->reset) अणु
		gpio_request(pdata->reset, "cw1200_wlan_reset");
		gpio_direction_output(pdata->reset, 0);
	पूर्ण
	अगर (pdata->घातerup) अणु
		gpio_request(pdata->घातerup, "cw1200_wlan_powerup");
		gpio_direction_output(pdata->घातerup, 0);
	पूर्ण
	अगर (pdata->reset || pdata->घातerup)
		msleep(10); /* Settle समय? */

	/* Enable 3v3 and 1v8 to hardware */
	अगर (pdata->घातer_ctrl) अणु
		अगर (pdata->घातer_ctrl(pdata, true)) अणु
			pr_err("power_ctrl() failed!\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* Enable CLK32K */
	अगर (pdata->clk_ctrl) अणु
		अगर (pdata->clk_ctrl(pdata, true)) अणु
			pr_err("clk_ctrl() failed!\n");
			वापस -1;
		पूर्ण
		msleep(10); /* Delay until घड़ी is stable क्रम 2 cycles */
	पूर्ण

	/* Enable POWERUP संकेत */
	अगर (pdata->घातerup) अणु
		gpio_set_value(pdata->घातerup, 1);
		msleep(250); /* or more..? */
	पूर्ण
	/* Enable RSTn संकेत */
	अगर (pdata->reset) अणु
		gpio_set_value(pdata->reset, 1);
		msleep(50); /* Or more..? */
	पूर्ण
	वापस 0;
पूर्ण

अटल माप_प्रकार cw1200_spi_align_size(काष्ठा hwbus_priv *self, माप_प्रकार size)
अणु
	वापस size & 1 ? size + 1 : size;
पूर्ण

अटल पूर्णांक cw1200_spi_pm(काष्ठा hwbus_priv *self, bool suspend)
अणु
	वापस irq_set_irq_wake(self->func->irq, suspend);
पूर्ण

अटल स्थिर काष्ठा hwbus_ops cw1200_spi_hwbus_ops = अणु
	.hwbus_स_नकल_fromio	= cw1200_spi_स_नकल_fromio,
	.hwbus_स_नकल_toio	= cw1200_spi_स_नकल_toio,
	.lock			= cw1200_spi_lock,
	.unlock			= cw1200_spi_unlock,
	.align_size		= cw1200_spi_align_size,
	.घातer_mgmt		= cw1200_spi_pm,
पूर्ण;

/* Probe Function to be called by SPI stack when device is discovered */
अटल पूर्णांक cw1200_spi_probe(काष्ठा spi_device *func)
अणु
	स्थिर काष्ठा cw1200_platक्रमm_data_spi *plat_data =
		dev_get_platdata(&func->dev);
	काष्ठा hwbus_priv *self;
	पूर्णांक status;

	/* Sanity check speed */
	अगर (func->max_speed_hz > 52000000)
		func->max_speed_hz = 52000000;
	अगर (func->max_speed_hz < 1000000)
		func->max_speed_hz = 1000000;

	/* Fix up transfer size */
	अगर (plat_data->spi_bits_per_word)
		func->bits_per_word = plat_data->spi_bits_per_word;
	अगर (!func->bits_per_word)
		func->bits_per_word = 16;

	/* And finally.. */
	func->mode = SPI_MODE_0;

	pr_info("cw1200_wlan_spi: Probe called (CS %d M %d BPW %d CLK %d)\n",
		func->chip_select, func->mode, func->bits_per_word,
		func->max_speed_hz);

	अगर (cw1200_spi_on(plat_data)) अणु
		pr_err("spi_on() failed!\n");
		वापस -1;
	पूर्ण

	अगर (spi_setup(func)) अणु
		pr_err("spi_setup() failed!\n");
		वापस -1;
	पूर्ण

	self = devm_kzalloc(&func->dev, माप(*self), GFP_KERNEL);
	अगर (!self) अणु
		pr_err("Can't allocate SPI hwbus_priv.");
		वापस -ENOMEM;
	पूर्ण

	self->pdata = plat_data;
	self->func = func;
	spin_lock_init(&self->lock);

	spi_set_drvdata(func, self);

	init_रुकोqueue_head(&self->wq);

	status = cw1200_spi_irq_subscribe(self);

	status = cw1200_core_probe(&cw1200_spi_hwbus_ops,
				   self, &func->dev, &self->core,
				   self->pdata->ref_clk,
				   self->pdata->macaddr,
				   self->pdata->sdd_file,
				   self->pdata->have_5ghz);

	अगर (status) अणु
		cw1200_spi_irq_unsubscribe(self);
		cw1200_spi_off(plat_data);
	पूर्ण

	वापस status;
पूर्ण

/* Disconnect Function to be called by SPI stack when device is disconnected */
अटल पूर्णांक cw1200_spi_disconnect(काष्ठा spi_device *func)
अणु
	काष्ठा hwbus_priv *self = spi_get_drvdata(func);

	अगर (self) अणु
		cw1200_spi_irq_unsubscribe(self);
		अगर (self->core) अणु
			cw1200_core_release(self->core);
			self->core = शून्य;
		पूर्ण
	पूर्ण
	cw1200_spi_off(dev_get_platdata(&func->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cw1200_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा hwbus_priv *self = spi_get_drvdata(to_spi_device(dev));

	अगर (!cw1200_can_suspend(self->core))
		वापस -EAGAIN;

	/* XXX notअगरy host that we have to keep CW1200 घातered on? */
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cw1200_pm_ops, cw1200_spi_suspend, शून्य);

अटल काष्ठा spi_driver spi_driver = अणु
	.probe		= cw1200_spi_probe,
	.हटाओ		= cw1200_spi_disconnect,
	.driver = अणु
		.name		= "cw1200_wlan_spi",
		.pm		= IS_ENABLED(CONFIG_PM) ? &cw1200_pm_ops : शून्य,
	पूर्ण,
पूर्ण;

module_spi_driver(spi_driver);
