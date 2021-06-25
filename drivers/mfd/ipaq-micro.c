<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Compaq iPAQ h3xxx Aपंचांगel microcontroller companion support
 *
 * This is an Aपंचांगel AT90LS8535 with a special flashed-in firmware that
 * implements the special protocol used by this driver.
 *
 * based on previous kernel 2.4 version by Andrew Christian
 * Author : Alessandro Gardich <gremlin@gremlin.it>
 * Author : Dmitry Artamonow <mad_soft@inbox.ru>
 * Author : Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ipaq-micro.h>
#समावेश <linux/माला.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

#समावेश <mach/hardware.h>

अटल व्योम ipaq_micro_trigger_tx(काष्ठा ipaq_micro *micro)
अणु
	काष्ठा ipaq_micro_txdev *tx = &micro->tx;
	काष्ठा ipaq_micro_msg *msg = micro->msg;
	पूर्णांक i, bp;
	u8 checksum;
	u32 val;

	bp = 0;
	tx->buf[bp++] = CHAR_SOF;

	checksum = ((msg->id & 0x0f) << 4) | (msg->tx_len & 0x0f);
	tx->buf[bp++] = checksum;

	क्रम (i = 0; i < msg->tx_len; i++) अणु
		tx->buf[bp++] = msg->tx_data[i];
		checksum += msg->tx_data[i];
	पूर्ण

	tx->buf[bp++] = checksum;
	tx->len = bp;
	tx->index = 0;

	/* Enable पूर्णांकerrupt */
	val = पढ़ोl(micro->base + UTCR3);
	val |= UTCR3_TIE;
	ग_लिखोl(val, micro->base + UTCR3);
पूर्ण

पूर्णांक ipaq_micro_tx_msg(काष्ठा ipaq_micro *micro, काष्ठा ipaq_micro_msg *msg)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(micro->dev, "TX msg: %02x, %d bytes\n", msg->id, msg->tx_len);

	spin_lock_irqsave(&micro->lock, flags);
	अगर (micro->msg) अणु
		list_add_tail(&msg->node, &micro->queue);
		spin_unlock_irqrestore(&micro->lock, flags);
		वापस 0;
	पूर्ण
	micro->msg = msg;
	ipaq_micro_trigger_tx(micro);
	spin_unlock_irqrestore(&micro->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipaq_micro_tx_msg);

अटल व्योम micro_rx_msg(काष्ठा ipaq_micro *micro, u8 id, पूर्णांक len, u8 *data)
अणु
	पूर्णांक i;

	dev_dbg(micro->dev, "RX msg: %02x, %d bytes\n", id, len);

	spin_lock(&micro->lock);
	चयन (id) अणु
	हाल MSG_VERSION:
	हाल MSG_EEPROM_READ:
	हाल MSG_EEPROM_WRITE:
	हाल MSG_BACKLIGHT:
	हाल MSG_NOTIFY_LED:
	हाल MSG_THERMAL_SENSOR:
	हाल MSG_BATTERY:
		/* Handle synchronous messages */
		अगर (micro->msg && micro->msg->id == id) अणु
			काष्ठा ipaq_micro_msg *msg = micro->msg;

			स_नकल(msg->rx_data, data, len);
			msg->rx_len = len;
			complete(&micro->msg->ack);
			अगर (!list_empty(&micro->queue)) अणु
				micro->msg = list_entry(micro->queue.next,
							काष्ठा ipaq_micro_msg,
							node);
				list_del_init(&micro->msg->node);
				ipaq_micro_trigger_tx(micro);
			पूर्ण अन्यथा
				micro->msg = शून्य;
			dev_dbg(micro->dev, "OK RX message 0x%02x\n", id);
		पूर्ण अन्यथा अणु
			dev_err(micro->dev,
				"out of band RX message 0x%02x\n", id);
			अगर (!micro->msg)
				dev_info(micro->dev, "no message queued\n");
			अन्यथा
				dev_info(micro->dev, "expected message %02x\n",
					 micro->msg->id);
		पूर्ण
		अवरोध;
	हाल MSG_KEYBOARD:
		अगर (micro->key)
			micro->key(micro->key_data, len, data);
		अन्यथा
			dev_dbg(micro->dev, "key message ignored, no handle\n");
		अवरोध;
	हाल MSG_TOUCHSCREEN:
		अगर (micro->ts)
			micro->ts(micro->ts_data, len, data);
		अन्यथा
			dev_dbg(micro->dev, "touchscreen message ignored, no handle\n");
		अवरोध;
	शेष:
		dev_err(micro->dev,
			"unknown msg %d [%d] ", id, len);
		क्रम (i = 0; i < len; ++i)
			pr_cont("0x%02x ", data[i]);
		pr_cont("\n");
	पूर्ण
	spin_unlock(&micro->lock);
पूर्ण

अटल व्योम micro_process_अक्षर(काष्ठा ipaq_micro *micro, u8 ch)
अणु
	काष्ठा ipaq_micro_rxdev *rx = &micro->rx;

	चयन (rx->state) अणु
	हाल STATE_SOF:	/* Looking क्रम SOF */
		अगर (ch == CHAR_SOF)
			rx->state = STATE_ID; /* Next byte is the id and len */
		अवरोध;
	हाल STATE_ID: /* Looking क्रम id and len byte */
		rx->id = (ch & 0xf0) >> 4;
		rx->len = (ch & 0x0f);
		rx->index = 0;
		rx->chksum = ch;
		rx->state = (rx->len > 0) ? STATE_DATA : STATE_CHKSUM;
		अवरोध;
	हाल STATE_DATA: /* Looking क्रम 'len' data bytes */
		rx->chksum += ch;
		rx->buf[rx->index] = ch;
		अगर (++rx->index == rx->len)
			rx->state = STATE_CHKSUM;
		अवरोध;
	हाल STATE_CHKSUM: /* Looking क्रम the checksum */
		अगर (ch == rx->chksum)
			micro_rx_msg(micro, rx->id, rx->len, rx->buf);
		rx->state = STATE_SOF;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम micro_rx_अक्षरs(काष्ठा ipaq_micro *micro)
अणु
	u32 status, ch;

	जबतक ((status = पढ़ोl(micro->base + UTSR1)) & UTSR1_RNE) अणु
		ch = पढ़ोl(micro->base + UTDR);
		अगर (status & UTSR1_PRE)
			dev_err(micro->dev, "rx: parity error\n");
		अन्यथा अगर (status & UTSR1_FRE)
			dev_err(micro->dev, "rx: framing error\n");
		अन्यथा अगर (status & UTSR1_ROR)
			dev_err(micro->dev, "rx: overrun error\n");
		micro_process_अक्षर(micro, ch);
	पूर्ण
पूर्ण

अटल व्योम ipaq_micro_get_version(काष्ठा ipaq_micro *micro)
अणु
	काष्ठा ipaq_micro_msg msg = अणु
		.id = MSG_VERSION,
	पूर्ण;

	ipaq_micro_tx_msg_sync(micro, &msg);
	अगर (msg.rx_len == 4) अणु
		स_नकल(micro->version, msg.rx_data, 4);
		micro->version[4] = '\0';
	पूर्ण अन्यथा अगर (msg.rx_len == 9) अणु
		स_नकल(micro->version, msg.rx_data, 4);
		micro->version[4] = '\0';
		/* Bytes 4-7 are "pack", byte 8 is "boot type" */
	पूर्ण अन्यथा अणु
		dev_err(micro->dev,
			"illegal version message %d bytes\n", msg.rx_len);
	पूर्ण
पूर्ण

अटल व्योम ipaq_micro_eeprom_पढ़ो(काष्ठा ipaq_micro *micro,
				   u8 address, u8 len, u8 *data)
अणु
	काष्ठा ipaq_micro_msg msg = अणु
		.id = MSG_EEPROM_READ,
	पूर्ण;
	u8 i;

	क्रम (i = 0; i < len; i++) अणु
		msg.tx_data[0] = address + i;
		msg.tx_data[1] = 1;
		msg.tx_len = 2;
		ipaq_micro_tx_msg_sync(micro, &msg);
		स_नकल(data + (i * 2), msg.rx_data, 2);
	पूर्ण
पूर्ण

अटल अक्षर *ipaq_micro_str(u8 *wअक्षर, u8 len)
अणु
	अक्षर retstr[256];
	u8 i;

	क्रम (i = 0; i < len / 2; i++)
		retstr[i] = wअक्षर[i * 2];
	वापस kstrdup(retstr, GFP_KERNEL);
पूर्ण

अटल u16 ipaq_micro_to_u16(u8 *data)
अणु
	वापस data[1] << 8 | data[0];
पूर्ण

अटल व्योम __init ipaq_micro_eeprom_dump(काष्ठा ipaq_micro *micro)
अणु
	u8 dump[256];
	अक्षर *str;

	ipaq_micro_eeprom_पढ़ो(micro, 0, 128, dump);
	str = ipaq_micro_str(dump, 10);
	अगर (str) अणु
		dev_info(micro->dev, "HW version %s\n", str);
		kमुक्त(str);
	पूर्ण
	str = ipaq_micro_str(dump+10, 40);
	अगर (str) अणु
		dev_info(micro->dev, "serial number: %s\n", str);
		/* Feed the अक्रमom pool with this */
		add_device_अक्रमomness(str, म_माप(str));
		kमुक्त(str);
	पूर्ण
	str = ipaq_micro_str(dump+50, 20);
	अगर (str) अणु
		dev_info(micro->dev, "module ID: %s\n", str);
		kमुक्त(str);
	पूर्ण
	str = ipaq_micro_str(dump+70, 10);
	अगर (str) अणु
		dev_info(micro->dev, "product revision: %s\n", str);
		kमुक्त(str);
	पूर्ण
	dev_info(micro->dev, "product ID: %u\n", ipaq_micro_to_u16(dump+80));
	dev_info(micro->dev, "frame rate: %u fps\n",
		 ipaq_micro_to_u16(dump+82));
	dev_info(micro->dev, "page mode: %u\n", ipaq_micro_to_u16(dump+84));
	dev_info(micro->dev, "country ID: %u\n", ipaq_micro_to_u16(dump+86));
	dev_info(micro->dev, "color display: %s\n",
		 ipaq_micro_to_u16(dump+88) ? "yes" : "no");
	dev_info(micro->dev, "ROM size: %u MiB\n", ipaq_micro_to_u16(dump+90));
	dev_info(micro->dev, "RAM size: %u KiB\n", ipaq_micro_to_u16(dump+92));
	dev_info(micro->dev, "screen: %u x %u\n",
		 ipaq_micro_to_u16(dump+94), ipaq_micro_to_u16(dump+96));
पूर्ण

अटल व्योम micro_tx_अक्षरs(काष्ठा ipaq_micro *micro)
अणु
	काष्ठा ipaq_micro_txdev *tx = &micro->tx;
	u32 val;

	जबतक ((tx->index < tx->len) &&
	       (पढ़ोl(micro->base + UTSR1) & UTSR1_TNF)) अणु
		ग_लिखोl(tx->buf[tx->index], micro->base + UTDR);
		tx->index++;
	पूर्ण

	/* Stop पूर्णांकerrupts */
	val = पढ़ोl(micro->base + UTCR3);
	val &= ~UTCR3_TIE;
	ग_लिखोl(val, micro->base + UTCR3);
पूर्ण

अटल व्योम micro_reset_comm(काष्ठा ipaq_micro *micro)
अणु
	काष्ठा ipaq_micro_rxdev *rx = &micro->rx;
	u32 val;

	अगर (micro->msg)
		complete(&micro->msg->ack);

	/* Initialize Serial channel protocol frame */
	rx->state = STATE_SOF;  /* Reset the state machine */

	/* Set up पूर्णांकerrupts */
	ग_लिखोl(0x01, micro->sdlc + 0x0); /* Select UART mode */

	/* Clean up CR3 */
	ग_लिखोl(0x0, micro->base + UTCR3);

	/* Format: 8N1 */
	ग_लिखोl(UTCR0_8BitData | UTCR0_1StpBit, micro->base + UTCR0);

	/* Baud rate: 115200 */
	ग_लिखोl(0x0, micro->base + UTCR1);
	ग_लिखोl(0x1, micro->base + UTCR2);

	/* Clear SR0 */
	ग_लिखोl(0xff, micro->base + UTSR0);

	/* Enable RX पूर्णांक, disable TX पूर्णांक */
	ग_लिखोl(UTCR3_TXE | UTCR3_RXE | UTCR3_RIE, micro->base + UTCR3);
	val = पढ़ोl(micro->base + UTCR3);
	val &= ~UTCR3_TIE;
	ग_लिखोl(val, micro->base + UTCR3);
पूर्ण

अटल irqवापस_t micro_serial_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipaq_micro *micro = dev_id;
	काष्ठा ipaq_micro_txdev *tx = &micro->tx;
	u32 status;

	status = पढ़ोl(micro->base + UTSR0);
	करो अणु
		अगर (status & (UTSR0_RID | UTSR0_RFS)) अणु
			अगर (status & UTSR0_RID)
				/* Clear the Receiver IDLE bit */
				ग_लिखोl(UTSR0_RID, micro->base + UTSR0);
			micro_rx_अक्षरs(micro);
		पूर्ण

		/* Clear अवरोध bits */
		अगर (status & (UTSR0_RBB | UTSR0_REB))
			ग_लिखोl(status & (UTSR0_RBB | UTSR0_REB),
			       micro->base + UTSR0);

		अगर (status & UTSR0_TFS)
			micro_tx_अक्षरs(micro);

		status = पढ़ोl(micro->base + UTSR0);

	पूर्ण जबतक (((tx->index < tx->len) && (status & UTSR0_TFS)) ||
		 (status & (UTSR0_RFS | UTSR0_RID)));

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा mfd_cell micro_cells[] = अणु
	अणु .name = "ipaq-micro-backlight", पूर्ण,
	अणु .name = "ipaq-micro-battery", पूर्ण,
	अणु .name = "ipaq-micro-keys", पूर्ण,
	अणु .name = "ipaq-micro-ts", पूर्ण,
	अणु .name = "ipaq-micro-leds", पूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused micro_resume(काष्ठा device *dev)
अणु
	काष्ठा ipaq_micro *micro = dev_get_drvdata(dev);

	micro_reset_comm(micro);
	mdelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक __init micro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipaq_micro *micro;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक irq;

	micro = devm_kzalloc(&pdev->dev, माप(*micro), GFP_KERNEL);
	अगर (!micro)
		वापस -ENOMEM;

	micro->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	micro->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(micro->base))
		वापस PTR_ERR(micro->base);

	micro->sdlc = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(micro->sdlc))
		वापस PTR_ERR(micro->sdlc);

	micro_reset_comm(micro);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!irq)
		वापस -EINVAL;
	ret = devm_request_irq(&pdev->dev, irq, micro_serial_isr,
			       IRQF_SHARED, "ipaq-micro",
			       micro);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to grab serial port IRQ\n");
		वापस ret;
	पूर्ण अन्यथा
		dev_info(&pdev->dev, "grabbed serial port IRQ\n");

	spin_lock_init(&micro->lock);
	INIT_LIST_HEAD(&micro->queue);
	platक्रमm_set_drvdata(pdev, micro);

	ret = mfd_add_devices(&pdev->dev, pdev->id, micro_cells,
			      ARRAY_SIZE(micro_cells), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error adding MFD cells");
		वापस ret;
	पूर्ण

	/* Check version */
	ipaq_micro_get_version(micro);
	dev_info(&pdev->dev, "Atmel micro ASIC version %s\n", micro->version);
	ipaq_micro_eeprom_dump(micro);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops micro_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(शून्य, micro_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver micro_device_driver = अणु
	.driver   = अणु
		.name	= "ipaq-h3xxx-micro",
		.pm	= &micro_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(micro_device_driver, micro_probe);
