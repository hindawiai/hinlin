<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Christian Lamparter <chunkeey@web.de>
 * Copyright 2008       Johannes Berg <johannes@sipsolutions.net>
 *
 * This driver is a port from stlc45xx:
 *	Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

#समावेश "p54spi.h"
#समावेश "p54.h"

#समावेश "lmac.h"

#अगर_घोषित CONFIG_P54_SPI_DEFAULT_EEPROM
#समावेश "p54spi_eeprom.h"
#पूर्ण_अगर /* CONFIG_P54_SPI_DEFAULT_EEPROM */

MODULE_FIRMWARE("3826.arm");

/* gpios should be handled in board files and provided via platक्रमm data,
 * but because it's currently impossible क्रम p54spi to have a header file
 * in include/linux, let's use module paramaters क्रम now
 */

अटल पूर्णांक p54spi_gpio_घातer = 97;
module_param(p54spi_gpio_घातer, पूर्णांक, 0444);
MODULE_PARM_DESC(p54spi_gpio_घातer, "gpio number for power line");

अटल पूर्णांक p54spi_gpio_irq = 87;
module_param(p54spi_gpio_irq, पूर्णांक, 0444);
MODULE_PARM_DESC(p54spi_gpio_irq, "gpio number for irq line");

अटल व्योम p54spi_spi_पढ़ो(काष्ठा p54s_priv *priv, u8 address,
			      व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	__le16 addr;

	/* We first push the address */
	addr = cpu_to_le16(address << 8 | SPI_ADRS_READ_BIT_15);

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = &addr;
	t[0].len = माप(addr);
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	spi_sync(priv->spi, &m);
पूर्ण


अटल व्योम p54spi_spi_ग_लिखो(काष्ठा p54s_priv *priv, u8 address,
			     स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer t[3];
	काष्ठा spi_message m;
	__le16 addr;

	/* We first push the address */
	addr = cpu_to_le16(address << 8);

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = &addr;
	t[0].len = माप(addr);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = len & ~1;
	spi_message_add_tail(&t[1], &m);

	अगर (len % 2) अणु
		__le16 last_word;
		last_word = cpu_to_le16(((u8 *)buf)[len - 1]);

		t[2].tx_buf = &last_word;
		t[2].len = माप(last_word);
		spi_message_add_tail(&t[2], &m);
	पूर्ण

	spi_sync(priv->spi, &m);
पूर्ण

अटल u32 p54spi_पढ़ो32(काष्ठा p54s_priv *priv, u8 addr)
अणु
	__le32 val;

	p54spi_spi_पढ़ो(priv, addr, &val, माप(val));

	वापस le32_to_cpu(val);
पूर्ण

अटल अंतरभूत व्योम p54spi_ग_लिखो16(काष्ठा p54s_priv *priv, u8 addr, __le16 val)
अणु
	p54spi_spi_ग_लिखो(priv, addr, &val, माप(val));
पूर्ण

अटल अंतरभूत व्योम p54spi_ग_लिखो32(काष्ठा p54s_priv *priv, u8 addr, __le32 val)
अणु
	p54spi_spi_ग_लिखो(priv, addr, &val, माप(val));
पूर्ण

अटल पूर्णांक p54spi_रुको_bit(काष्ठा p54s_priv *priv, u16 reg, u32 bits)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2000; i++) अणु
		u32 buffer = p54spi_पढ़ो32(priv, reg);
		अगर ((buffer & bits) == bits)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक p54spi_spi_ग_लिखो_dma(काष्ठा p54s_priv *priv, __le32 base,
				स्थिर व्योम *buf, माप_प्रकार len)
अणु
	अगर (!p54spi_रुको_bit(priv, SPI_ADRS_DMA_WRITE_CTRL, HOST_ALLOWED)) अणु
		dev_err(&priv->spi->dev, "spi_write_dma not allowed "
			"to DMA write.\n");
		वापस -EAGAIN;
	पूर्ण

	p54spi_ग_लिखो16(priv, SPI_ADRS_DMA_WRITE_CTRL,
		       cpu_to_le16(SPI_DMA_WRITE_CTRL_ENABLE));

	p54spi_ग_लिखो16(priv, SPI_ADRS_DMA_WRITE_LEN, cpu_to_le16(len));
	p54spi_ग_लिखो32(priv, SPI_ADRS_DMA_WRITE_BASE, base);
	p54spi_spi_ग_लिखो(priv, SPI_ADRS_DMA_DATA, buf, len);
	वापस 0;
पूर्ण

अटल पूर्णांक p54spi_request_firmware(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54s_priv *priv = dev->priv;
	पूर्णांक ret;

	/* FIXME: should driver use it's own काष्ठा device? */
	ret = request_firmware(&priv->firmware, "3826.arm", &priv->spi->dev);

	अगर (ret < 0) अणु
		dev_err(&priv->spi->dev, "request_firmware() failed: %d", ret);
		वापस ret;
	पूर्ण

	ret = p54_parse_firmware(dev, priv->firmware);
	अगर (ret) अणु
		release_firmware(priv->firmware);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक p54spi_request_eeprom(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54s_priv *priv = dev->priv;
	स्थिर काष्ठा firmware *eeprom;
	पूर्णांक ret;

	/* allow users to customize their eeprom.
	 */

	ret = request_firmware_direct(&eeprom, "3826.eeprom", &priv->spi->dev);
	अगर (ret < 0) अणु
#अगर_घोषित CONFIG_P54_SPI_DEFAULT_EEPROM
		dev_info(&priv->spi->dev, "loading default eeprom...\n");
		ret = p54_parse_eeprom(dev, (व्योम *) p54spi_eeprom,
				       माप(p54spi_eeprom));
#अन्यथा
		dev_err(&priv->spi->dev, "Failed to request user eeprom\n");
#पूर्ण_अगर /* CONFIG_P54_SPI_DEFAULT_EEPROM */
	पूर्ण अन्यथा अणु
		dev_info(&priv->spi->dev, "loading user eeprom...\n");
		ret = p54_parse_eeprom(dev, (व्योम *) eeprom->data,
				       (पूर्णांक)eeprom->size);
		release_firmware(eeprom);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक p54spi_upload_firmware(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54s_priv *priv = dev->priv;
	अचिन्हित दीर्घ fw_len, _fw_len;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक err = 0;
	u8 *fw;

	fw_len = priv->firmware->size;
	fw = kmemdup(priv->firmware->data, fw_len, GFP_KERNEL);
	अगर (!fw)
		वापस -ENOMEM;

	/* stop the device */
	p54spi_ग_लिखो16(priv, SPI_ADRS_DEV_CTRL_STAT, cpu_to_le16(
		       SPI_CTRL_STAT_HOST_OVERRIDE | SPI_CTRL_STAT_HOST_RESET |
		       SPI_CTRL_STAT_START_HALTED));

	msleep(TARGET_BOOT_SLEEP);

	p54spi_ग_लिखो16(priv, SPI_ADRS_DEV_CTRL_STAT, cpu_to_le16(
		       SPI_CTRL_STAT_HOST_OVERRIDE |
		       SPI_CTRL_STAT_START_HALTED));

	msleep(TARGET_BOOT_SLEEP);

	जबतक (fw_len > 0) अणु
		_fw_len = min_t(दीर्घ, fw_len, SPI_MAX_PACKET_SIZE);

		err = p54spi_spi_ग_लिखो_dma(priv, cpu_to_le32(
					   ISL38XX_DEV_FIRMWARE_ADDR + offset),
					   (fw + offset), _fw_len);
		अगर (err < 0)
			जाओ out;

		fw_len -= _fw_len;
		offset += _fw_len;
	पूर्ण

	BUG_ON(fw_len != 0);

	/* enable host पूर्णांकerrupts */
	p54spi_ग_लिखो32(priv, SPI_ADRS_HOST_INT_EN,
		       cpu_to_le32(SPI_HOST_INTS_DEFAULT));

	/* boot the device */
	p54spi_ग_लिखो16(priv, SPI_ADRS_DEV_CTRL_STAT, cpu_to_le16(
		       SPI_CTRL_STAT_HOST_OVERRIDE | SPI_CTRL_STAT_HOST_RESET |
		       SPI_CTRL_STAT_RAM_BOOT));

	msleep(TARGET_BOOT_SLEEP);

	p54spi_ग_लिखो16(priv, SPI_ADRS_DEV_CTRL_STAT, cpu_to_le16(
		       SPI_CTRL_STAT_HOST_OVERRIDE | SPI_CTRL_STAT_RAM_BOOT));
	msleep(TARGET_BOOT_SLEEP);

out:
	kमुक्त(fw);
	वापस err;
पूर्ण

अटल व्योम p54spi_घातer_off(काष्ठा p54s_priv *priv)
अणु
	disable_irq(gpio_to_irq(p54spi_gpio_irq));
	gpio_set_value(p54spi_gpio_घातer, 0);
पूर्ण

अटल व्योम p54spi_घातer_on(काष्ठा p54s_priv *priv)
अणु
	gpio_set_value(p54spi_gpio_घातer, 1);
	enable_irq(gpio_to_irq(p54spi_gpio_irq));

	/* need to रुको a जबतक beक्रमe device can be accessed, the length
	 * is just a guess
	 */
	msleep(10);
पूर्ण

अटल अंतरभूत व्योम p54spi_पूर्णांक_ack(काष्ठा p54s_priv *priv, u32 val)
अणु
	p54spi_ग_लिखो32(priv, SPI_ADRS_HOST_INT_ACK, cpu_to_le32(val));
पूर्ण

अटल पूर्णांक p54spi_wakeup(काष्ठा p54s_priv *priv)
अणु
	/* wake the chip */
	p54spi_ग_लिखो32(priv, SPI_ADRS_ARM_INTERRUPTS,
		       cpu_to_le32(SPI_TARGET_INT_WAKEUP));

	/* And रुको क्रम the READY पूर्णांकerrupt */
	अगर (!p54spi_रुको_bit(priv, SPI_ADRS_HOST_INTERRUPTS,
			     SPI_HOST_INT_READY)) अणु
		dev_err(&priv->spi->dev, "INT_READY timeout\n");
		वापस -EBUSY;
	पूर्ण

	p54spi_पूर्णांक_ack(priv, SPI_HOST_INT_READY);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम p54spi_sleep(काष्ठा p54s_priv *priv)
अणु
	p54spi_ग_लिखो32(priv, SPI_ADRS_ARM_INTERRUPTS,
		       cpu_to_le32(SPI_TARGET_INT_SLEEP));
पूर्ण

अटल व्योम p54spi_पूर्णांक_पढ़ोy(काष्ठा p54s_priv *priv)
अणु
	p54spi_ग_लिखो32(priv, SPI_ADRS_HOST_INT_EN, cpu_to_le32(
		       SPI_HOST_INT_UPDATE | SPI_HOST_INT_SW_UPDATE));

	चयन (priv->fw_state) अणु
	हाल FW_STATE_BOOTING:
		priv->fw_state = FW_STATE_READY;
		complete(&priv->fw_comp);
		अवरोध;
	हाल FW_STATE_RESETTING:
		priv->fw_state = FW_STATE_READY;
		/* TODO: reinitialize state */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक p54spi_rx(काष्ठा p54s_priv *priv)
अणु
	काष्ठा sk_buff *skb;
	u16 len;
	u16 rx_head[2];
#घोषणा READAHEAD_SZ (माप(rx_head)-माप(u16))

	अगर (p54spi_wakeup(priv) < 0)
		वापस -EBUSY;

	/* Read data size and first data word in one SPI transaction
	 * This is workaround क्रम firmware/DMA bug,
	 * when first data word माला_लो lost under high load.
	 */
	p54spi_spi_पढ़ो(priv, SPI_ADRS_DMA_DATA, rx_head, माप(rx_head));
	len = rx_head[0];

	अगर (len == 0) अणु
		p54spi_sleep(priv);
		dev_err(&priv->spi->dev, "rx request of zero bytes\n");
		वापस 0;
	पूर्ण

	/* Firmware may insert up to 4 padding bytes after the lmac header,
	 * but it करोes not amend the size of SPI data transfer.
	 * Such packets has correct data size in header, thus referencing
	 * past the end of allocated skb. Reserve extra 4 bytes क्रम this हाल
	 */
	skb = dev_alloc_skb(len + 4);
	अगर (!skb) अणु
		p54spi_sleep(priv);
		dev_err(&priv->spi->dev, "could not alloc skb");
		वापस -ENOMEM;
	पूर्ण

	अगर (len <= READAHEAD_SZ) अणु
		skb_put_data(skb, rx_head + 1, len);
	पूर्ण अन्यथा अणु
		skb_put_data(skb, rx_head + 1, READAHEAD_SZ);
		p54spi_spi_पढ़ो(priv, SPI_ADRS_DMA_DATA,
				skb_put(skb, len - READAHEAD_SZ),
				len - READAHEAD_SZ);
	पूर्ण
	p54spi_sleep(priv);
	/* Put additional bytes to compensate क्रम the possible
	 * alignment-caused truncation
	 */
	skb_put(skb, 4);

	अगर (p54_rx(priv->hw, skb) == 0)
		dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण


अटल irqवापस_t p54spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *config)
अणु
	काष्ठा spi_device *spi = config;
	काष्ठा p54s_priv *priv = spi_get_drvdata(spi);

	ieee80211_queue_work(priv->hw, &priv->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक p54spi_tx_frame(काष्ठा p54s_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) skb->data;
	पूर्णांक ret = 0;

	अगर (p54spi_wakeup(priv) < 0)
		वापस -EBUSY;

	ret = p54spi_spi_ग_लिखो_dma(priv, hdr->req_id, skb->data, skb->len);
	अगर (ret < 0)
		जाओ out;

	अगर (!p54spi_रुको_bit(priv, SPI_ADRS_HOST_INTERRUPTS,
			     SPI_HOST_INT_WR_READY)) अणु
		dev_err(&priv->spi->dev, "WR_READY timeout\n");
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	p54spi_पूर्णांक_ack(priv, SPI_HOST_INT_WR_READY);

	अगर (FREE_AFTER_TX(skb))
		p54_मुक्त_skb(priv->hw, skb);
out:
	p54spi_sleep(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक p54spi_wq_tx(काष्ठा p54s_priv *priv)
अणु
	काष्ठा p54s_tx_info *entry;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा p54_tx_info *minfo;
	काष्ठा p54s_tx_info *dinfo;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&priv->tx_lock, flags);

	जबतक (!list_empty(&priv->tx_pending)) अणु
		entry = list_entry(priv->tx_pending.next,
				   काष्ठा p54s_tx_info, tx_list);

		list_del_init(&entry->tx_list);

		spin_unlock_irqrestore(&priv->tx_lock, flags);

		dinfo = container_of((व्योम *) entry, काष्ठा p54s_tx_info,
				     tx_list);
		minfo = container_of((व्योम *) dinfo, काष्ठा p54_tx_info,
				     data);
		info = container_of((व्योम *) minfo, काष्ठा ieee80211_tx_info,
				    rate_driver_data);
		skb = container_of((व्योम *) info, काष्ठा sk_buff, cb);

		ret = p54spi_tx_frame(priv, skb);

		अगर (ret < 0) अणु
			p54_मुक्त_skb(priv->hw, skb);
			वापस ret;
		पूर्ण

		spin_lock_irqsave(&priv->tx_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&priv->tx_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम p54spi_op_tx(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54s_priv *priv = dev->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा p54_tx_info *mi = (काष्ठा p54_tx_info *) info->rate_driver_data;
	काष्ठा p54s_tx_info *di = (काष्ठा p54s_tx_info *) mi->data;
	अचिन्हित दीर्घ flags;

	BUILD_BUG_ON(माप(*di) > माप((mi->data)));

	spin_lock_irqsave(&priv->tx_lock, flags);
	list_add_tail(&di->tx_list, &priv->tx_pending);
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	ieee80211_queue_work(priv->hw, &priv->work);
पूर्ण

अटल व्योम p54spi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा p54s_priv *priv = container_of(work, काष्ठा p54s_priv, work);
	u32 पूर्णांकs;
	पूर्णांक ret;

	mutex_lock(&priv->mutex);

	अगर (priv->fw_state == FW_STATE_OFF)
		जाओ out;

	पूर्णांकs = p54spi_पढ़ो32(priv, SPI_ADRS_HOST_INTERRUPTS);

	अगर (पूर्णांकs & SPI_HOST_INT_READY) अणु
		p54spi_पूर्णांक_पढ़ोy(priv);
		p54spi_पूर्णांक_ack(priv, SPI_HOST_INT_READY);
	पूर्ण

	अगर (priv->fw_state != FW_STATE_READY)
		जाओ out;

	अगर (पूर्णांकs & SPI_HOST_INT_UPDATE) अणु
		p54spi_पूर्णांक_ack(priv, SPI_HOST_INT_UPDATE);
		ret = p54spi_rx(priv);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	अगर (पूर्णांकs & SPI_HOST_INT_SW_UPDATE) अणु
		p54spi_पूर्णांक_ack(priv, SPI_HOST_INT_SW_UPDATE);
		ret = p54spi_rx(priv);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = p54spi_wq_tx(priv);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक p54spi_op_start(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54s_priv *priv = dev->priv;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&priv->mutex)) अणु
		ret = -EINTR;
		जाओ out;
	पूर्ण

	priv->fw_state = FW_STATE_BOOTING;

	p54spi_घातer_on(priv);

	ret = p54spi_upload_firmware(dev);
	अगर (ret < 0) अणु
		p54spi_घातer_off(priv);
		जाओ out_unlock;
	पूर्ण

	mutex_unlock(&priv->mutex);

	समयout = msecs_to_jअगरfies(2000);
	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->fw_comp,
							    समयout);
	अगर (!समयout) अणु
		dev_err(&priv->spi->dev, "firmware boot failed");
		p54spi_घातer_off(priv);
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&priv->mutex)) अणु
		ret = -EINTR;
		p54spi_घातer_off(priv);
		जाओ out;
	पूर्ण

	WARN_ON(priv->fw_state != FW_STATE_READY);

out_unlock:
	mutex_unlock(&priv->mutex);

out:
	वापस ret;
पूर्ण

अटल व्योम p54spi_op_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54s_priv *priv = dev->priv;
	अचिन्हित दीर्घ flags;

	mutex_lock(&priv->mutex);
	WARN_ON(priv->fw_state != FW_STATE_READY);

	p54spi_घातer_off(priv);
	spin_lock_irqsave(&priv->tx_lock, flags);
	INIT_LIST_HEAD(&priv->tx_pending);
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	priv->fw_state = FW_STATE_OFF;
	mutex_unlock(&priv->mutex);

	cancel_work_sync(&priv->work);
पूर्ण

अटल पूर्णांक p54spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा p54s_priv *priv = शून्य;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक ret = -EINVAL;

	hw = p54_init_common(माप(*priv));
	अगर (!hw) अणु
		dev_err(&spi->dev, "could not alloc ieee80211_hw");
		वापस -ENOMEM;
	पूर्ण

	priv = hw->priv;
	priv->hw = hw;
	spi_set_drvdata(spi, priv);
	priv->spi = spi;

	spi->bits_per_word = 16;
	spi->max_speed_hz = 24000000;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&priv->spi->dev, "spi_setup failed");
		जाओ err_मुक्त;
	पूर्ण

	ret = gpio_request(p54spi_gpio_घातer, "p54spi power");
	अगर (ret < 0) अणु
		dev_err(&priv->spi->dev, "power GPIO request failed: %d", ret);
		जाओ err_मुक्त;
	पूर्ण

	ret = gpio_request(p54spi_gpio_irq, "p54spi irq");
	अगर (ret < 0) अणु
		dev_err(&priv->spi->dev, "irq GPIO request failed: %d", ret);
		जाओ err_मुक्त_gpio_घातer;
	पूर्ण

	gpio_direction_output(p54spi_gpio_घातer, 0);
	gpio_direction_input(p54spi_gpio_irq);

	ret = request_irq(gpio_to_irq(p54spi_gpio_irq),
			  p54spi_पूर्णांकerrupt, 0, "p54spi",
			  priv->spi);
	अगर (ret < 0) अणु
		dev_err(&priv->spi->dev, "request_irq() failed");
		जाओ err_मुक्त_gpio_irq;
	पूर्ण

	irq_set_irq_type(gpio_to_irq(p54spi_gpio_irq), IRQ_TYPE_EDGE_RISING);

	disable_irq(gpio_to_irq(p54spi_gpio_irq));

	INIT_WORK(&priv->work, p54spi_work);
	init_completion(&priv->fw_comp);
	INIT_LIST_HEAD(&priv->tx_pending);
	mutex_init(&priv->mutex);
	spin_lock_init(&priv->tx_lock);
	SET_IEEE80211_DEV(hw, &spi->dev);
	priv->common.खोलो = p54spi_op_start;
	priv->common.stop = p54spi_op_stop;
	priv->common.tx = p54spi_op_tx;

	ret = p54spi_request_firmware(hw);
	अगर (ret < 0)
		जाओ err_मुक्त_common;

	ret = p54spi_request_eeprom(hw);
	अगर (ret)
		जाओ err_मुक्त_common;

	ret = p54_रेजिस्टर_common(hw, &priv->spi->dev);
	अगर (ret)
		जाओ err_मुक्त_common;

	वापस 0;

err_मुक्त_common:
	मुक्त_irq(gpio_to_irq(p54spi_gpio_irq), spi);
err_मुक्त_gpio_irq:
	gpio_मुक्त(p54spi_gpio_irq);
err_मुक्त_gpio_घातer:
	gpio_मुक्त(p54spi_gpio_घातer);
err_मुक्त:
	p54_मुक्त_common(priv->hw);
	वापस ret;
पूर्ण

अटल पूर्णांक p54spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा p54s_priv *priv = spi_get_drvdata(spi);

	p54_unरेजिस्टर_common(priv->hw);

	मुक्त_irq(gpio_to_irq(p54spi_gpio_irq), spi);

	gpio_मुक्त(p54spi_gpio_घातer);
	gpio_मुक्त(p54spi_gpio_irq);
	release_firmware(priv->firmware);

	mutex_destroy(&priv->mutex);

	p54_मुक्त_common(priv->hw);

	वापस 0;
पूर्ण


अटल काष्ठा spi_driver p54spi_driver = अणु
	.driver = अणु
		.name		= "p54spi",
	पूर्ण,

	.probe		= p54spi_probe,
	.हटाओ		= p54spi_हटाओ,
पूर्ण;

module_spi_driver(p54spi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Lamparter <chunkeey@web.de>");
MODULE_ALIAS("spi:cx3110x");
MODULE_ALIAS("spi:p54spi");
MODULE_ALIAS("spi:stlc45xx");
