<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * userspace पूर्णांकerface क्रम pi433 radio module
 *
 * Pi433 is a 433MHz radio module क्रम the Raspberry Pi.
 * It is based on the HopeRf Module RFM69CW. Thereक्रमe inside of this
 * driver, you'll find an असलtraction of the rf69 chip.
 *
 * If needed, this driver could be extended, to also support other
 * devices, basing on HopeRfs rf69.
 *
 * The driver can also be extended, to support other modules of
 * HopeRf with a similar पूर्णांकerace - e. g. RFM69HCW, RFM12, RFM95, ...
 *
 * Copyright (C) 2016 Wolf-Entwicklungen
 *	Marcus Wolf <linux@wolf-entwicklungen.de>
 */

#अघोषित DEBUG

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/err.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spi/spi.h>
#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>
#पूर्ण_अगर

#समावेश "pi433_if.h"
#समावेश "rf69.h"

#घोषणा N_PI433_MINORS		BIT(MINORBITS) /*32*/	/* ... up to 256 */
#घोषणा MAX_MSG_SIZE		900	/* min: FIFO_SIZE! */
#घोषणा MSG_FIFO_SIZE		65536   /* 65536 = 2^16  */
#घोषणा NUM_DIO			2

अटल dev_t pi433_dev;
अटल DEFINE_IDR(pi433_idr);
अटल DEFINE_MUTEX(minor_lock); /* Protect idr accesses */

अटल काष्ठा class *pi433_class; /* मुख्यly क्रम udev to create /dev/pi433 */

/*
 * tx config is instance specअगरic
 * so with each खोलो a new tx config काष्ठा is needed
 */
/*
 * rx config is device specअगरic
 * so we have just one rx config, ebedded in device काष्ठा
 */
काष्ठा pi433_device अणु
	/* device handling related values */
	dev_t			devt;
	पूर्णांक			minor;
	काष्ठा device		*dev;
	काष्ठा cdev		*cdev;
	काष्ठा spi_device	*spi;

	/* irq related values */
	काष्ठा gpio_desc	*gpiod[NUM_DIO];
	पूर्णांक			irq_num[NUM_DIO];
	u8			irq_state[NUM_DIO];

	/* tx related values */
	STRUCT_KFIFO_REC_1(MSG_FIFO_SIZE) tx_fअगरo;
	काष्ठा mutex		tx_fअगरo_lock; /* serialize userspace ग_लिखोrs */
	काष्ठा task_काष्ठा	*tx_task_काष्ठा;
	रुको_queue_head_t	tx_रुको_queue;
	u8			मुक्त_in_fअगरo;
	अक्षर			buffer[MAX_MSG_SIZE];

	/* rx related values */
	काष्ठा pi433_rx_cfg	rx_cfg;
	u8			*rx_buffer;
	अचिन्हित पूर्णांक		rx_buffer_size;
	u32			rx_bytes_to_drop;
	u32			rx_bytes_dropped;
	अचिन्हित पूर्णांक		rx_position;
	काष्ठा mutex		rx_lock;
	रुको_queue_head_t	rx_रुको_queue;

	/* fअगरo रुको queue */
	काष्ठा task_काष्ठा	*fअगरo_task_काष्ठा;
	रुको_queue_head_t	fअगरo_रुको_queue;

	/* flags */
	bool			rx_active;
	bool			tx_active;
	bool			पूर्णांकerrupt_rx_allowed;
पूर्ण;

काष्ठा pi433_instance अणु
	काष्ठा pi433_device	*device;
	काष्ठा pi433_tx_cfg	tx_cfg;
पूर्ण;

/*-------------------------------------------------------------------------*/

/* GPIO पूर्णांकerrupt handlers */
अटल irqवापस_t DIO0_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pi433_device *device = dev_id;

	अगर (device->irq_state[DIO0] == DIO_PACKET_SENT) अणु
		device->मुक्त_in_fअगरo = FIFO_SIZE;
		dev_dbg(device->dev, "DIO0 irq: Packet sent\n");
		wake_up_पूर्णांकerruptible(&device->fअगरo_रुको_queue);
	पूर्ण अन्यथा अगर (device->irq_state[DIO0] == DIO_RSSI_DIO0) अणु
		dev_dbg(device->dev, "DIO0 irq: RSSI level over threshold\n");
		wake_up_पूर्णांकerruptible(&device->rx_रुको_queue);
	पूर्ण अन्यथा अगर (device->irq_state[DIO0] == DIO_PAYLOAD_READY) अणु
		dev_dbg(device->dev, "DIO0 irq: Payload ready\n");
		device->मुक्त_in_fअगरo = 0;
		wake_up_पूर्णांकerruptible(&device->fअगरo_रुको_queue);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t DIO1_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pi433_device *device = dev_id;

	अगर (device->irq_state[DIO1] == DIO_FIFO_NOT_EMPTY_DIO1) अणु
		device->मुक्त_in_fअगरo = FIFO_SIZE;
	पूर्ण अन्यथा अगर (device->irq_state[DIO1] == DIO_FIFO_LEVEL) अणु
		अगर (device->rx_active)
			device->मुक्त_in_fअगरo = FIFO_THRESHOLD - 1;
		अन्यथा
			device->मुक्त_in_fअगरo = FIFO_SIZE - FIFO_THRESHOLD - 1;
	पूर्ण
	dev_dbg(device->dev,
		"DIO1 irq: %d bytes free in fifo\n", device->मुक्त_in_fअगरo);
	wake_up_पूर्णांकerruptible(&device->fअगरo_रुको_queue);

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
rf69_set_rx_cfg(काष्ठा pi433_device *dev, काष्ठा pi433_rx_cfg *rx_cfg)
अणु
	पूर्णांक ret;
	पूर्णांक payload_length;

	/* receiver config */
	ret = rf69_set_frequency(dev->spi, rx_cfg->frequency);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_bit_rate(dev->spi, rx_cfg->bit_rate);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_modulation(dev->spi, rx_cfg->modulation);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_antenna_impedance(dev->spi, rx_cfg->antenna_impedance);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_rssi_threshold(dev->spi, rx_cfg->rssi_threshold);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_ook_threshold_dec(dev->spi, rx_cfg->threshold_decrement);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_bandwidth(dev->spi, rx_cfg->bw_mantisse,
				 rx_cfg->bw_exponent);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_bandwidth_during_afc(dev->spi, rx_cfg->bw_mantisse,
					    rx_cfg->bw_exponent);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_dagc(dev->spi, rx_cfg->dagc);
	अगर (ret < 0)
		वापस ret;

	dev->rx_bytes_to_drop = rx_cfg->bytes_to_drop;

	/* packet config */
	/* enable */
	अगर (rx_cfg->enable_sync == OPTION_ON) अणु
		ret = rf69_enable_sync(dev->spi);
		अगर (ret < 0)
			वापस ret;

		ret = rf69_set_fअगरo_fill_condition(dev->spi,
						   after_sync_पूर्णांकerrupt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_disable_sync(dev->spi);
		अगर (ret < 0)
			वापस ret;

		ret = rf69_set_fअगरo_fill_condition(dev->spi, always);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (rx_cfg->enable_length_byte == OPTION_ON) अणु
		ret = rf69_set_packet_क्रमmat(dev->spi, packet_length_var);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_set_packet_क्रमmat(dev->spi, packet_length_fix);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	ret = rf69_set_address_filtering(dev->spi,
					 rx_cfg->enable_address_filtering);
	अगर (ret < 0)
		वापस ret;

	अगर (rx_cfg->enable_crc == OPTION_ON) अणु
		ret = rf69_enable_crc(dev->spi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_disable_crc(dev->spi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* lengths */
	ret = rf69_set_sync_size(dev->spi, rx_cfg->sync_length);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_cfg->enable_length_byte == OPTION_ON) अणु
		ret = rf69_set_payload_length(dev->spi, 0xff);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (rx_cfg->fixed_message_length != 0) अणु
		payload_length = rx_cfg->fixed_message_length;
		अगर (rx_cfg->enable_length_byte  == OPTION_ON)
			payload_length++;
		अगर (rx_cfg->enable_address_filtering != filtering_off)
			payload_length++;
		ret = rf69_set_payload_length(dev->spi, payload_length);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_set_payload_length(dev->spi, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* values */
	अगर (rx_cfg->enable_sync == OPTION_ON) अणु
		ret = rf69_set_sync_values(dev->spi, rx_cfg->sync_pattern);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (rx_cfg->enable_address_filtering != filtering_off) अणु
		ret = rf69_set_node_address(dev->spi, rx_cfg->node_address);
		अगर (ret < 0)
			वापस ret;
		ret = rf69_set_broadcast_address(dev->spi,
						 rx_cfg->broadcast_address);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
rf69_set_tx_cfg(काष्ठा pi433_device *dev, काष्ठा pi433_tx_cfg *tx_cfg)
अणु
	पूर्णांक ret;

	ret = rf69_set_frequency(dev->spi, tx_cfg->frequency);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_bit_rate(dev->spi, tx_cfg->bit_rate);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_modulation(dev->spi, tx_cfg->modulation);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_deviation(dev->spi, tx_cfg->dev_frequency);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_pa_ramp(dev->spi, tx_cfg->pa_ramp);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_modulation_shaping(dev->spi, tx_cfg->mod_shaping);
	अगर (ret < 0)
		वापस ret;
	ret = rf69_set_tx_start_condition(dev->spi, tx_cfg->tx_start_condition);
	अगर (ret < 0)
		वापस ret;

	/* packet क्रमmat enable */
	अगर (tx_cfg->enable_preamble == OPTION_ON) अणु
		ret = rf69_set_preamble_length(dev->spi,
					       tx_cfg->preamble_length);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_set_preamble_length(dev->spi, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (tx_cfg->enable_sync == OPTION_ON) अणु
		ret = rf69_set_sync_size(dev->spi, tx_cfg->sync_length);
		अगर (ret < 0)
			वापस ret;
		ret = rf69_set_sync_values(dev->spi, tx_cfg->sync_pattern);
		अगर (ret < 0)
			वापस ret;
		ret = rf69_enable_sync(dev->spi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_disable_sync(dev->spi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (tx_cfg->enable_length_byte == OPTION_ON) अणु
		ret = rf69_set_packet_क्रमmat(dev->spi, packet_length_var);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_set_packet_क्रमmat(dev->spi, packet_length_fix);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (tx_cfg->enable_crc == OPTION_ON) अणु
		ret = rf69_enable_crc(dev->spi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = rf69_disable_crc(dev->spi);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
pi433_start_rx(काष्ठा pi433_device *dev)
अणु
	पूर्णांक retval;

	/* वापस without action, अगर no pending पढ़ो request */
	अगर (!dev->rx_active)
		वापस 0;

	/* setup क्रम receiving */
	retval = rf69_set_rx_cfg(dev, &dev->rx_cfg);
	अगर (retval)
		वापस retval;

	/* setup rssi irq */
	retval = rf69_set_dio_mapping(dev->spi, DIO0, DIO_RSSI_DIO0);
	अगर (retval < 0)
		वापस retval;
	dev->irq_state[DIO0] = DIO_RSSI_DIO0;
	irq_set_irq_type(dev->irq_num[DIO0], IRQ_TYPE_EDGE_RISING);

	/* setup fअगरo level पूर्णांकerrupt */
	retval = rf69_set_fअगरo_threshold(dev->spi, FIFO_SIZE - FIFO_THRESHOLD);
	अगर (retval < 0)
		वापस retval;
	retval = rf69_set_dio_mapping(dev->spi, DIO1, DIO_FIFO_LEVEL);
	अगर (retval < 0)
		वापस retval;
	dev->irq_state[DIO1] = DIO_FIFO_LEVEL;
	irq_set_irq_type(dev->irq_num[DIO1], IRQ_TYPE_EDGE_RISING);

	/* set module to receiving mode */
	retval = rf69_set_mode(dev->spi, receive);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
pi433_receive(व्योम *data)
अणु
	काष्ठा pi433_device *dev = data;
	काष्ठा spi_device *spi = dev->spi;
	पूर्णांक bytes_to_पढ़ो, bytes_total;
	पूर्णांक retval;

	dev->पूर्णांकerrupt_rx_allowed = false;

	/* रुको क्रम any tx to finish */
	dev_dbg(dev->dev, "rx: going to wait for any tx to finish");
	retval = रुको_event_पूर्णांकerruptible(dev->rx_रुको_queue, !dev->tx_active);
	अगर (retval) अणु
		/* रुको was पूर्णांकerrupted */
		dev->पूर्णांकerrupt_rx_allowed = true;
		wake_up_पूर्णांकerruptible(&dev->tx_रुको_queue);
		वापस retval;
	पूर्ण

	/* prepare status vars */
	dev->मुक्त_in_fअगरo = FIFO_SIZE;
	dev->rx_position = 0;
	dev->rx_bytes_dropped = 0;

	/* setup radio module to listen क्रम something "in the air" */
	retval = pi433_start_rx(dev);
	अगर (retval)
		वापस retval;

	/* now check RSSI, अगर low रुको क्रम getting high (RSSI पूर्णांकerrupt) */
	जबतक (!rf69_get_flag(dev->spi, rssi_exceeded_threshold)) अणु
		/* allow tx to पूर्णांकerrupt us जबतक रुकोing क्रम high RSSI */
		dev->पूर्णांकerrupt_rx_allowed = true;
		wake_up_पूर्णांकerruptible(&dev->tx_रुको_queue);

		/* रुको क्रम RSSI level to become high */
		dev_dbg(dev->dev, "rx: going to wait for high RSSI level");
		retval = रुको_event_पूर्णांकerruptible(dev->rx_रुको_queue,
						  rf69_get_flag(dev->spi,
								rssi_exceeded_threshold));
		अगर (retval) /* रुको was पूर्णांकerrupted */
			जाओ पात;
		dev->पूर्णांकerrupt_rx_allowed = false;

		/* cross check क्रम ongoing tx */
		अगर (!dev->tx_active)
			अवरोध;
	पूर्ण

	/* configure payload पढ़ोy irq */
	retval = rf69_set_dio_mapping(spi, DIO0, DIO_PAYLOAD_READY);
	अगर (retval < 0)
		जाओ पात;
	dev->irq_state[DIO0] = DIO_PAYLOAD_READY;
	irq_set_irq_type(dev->irq_num[DIO0], IRQ_TYPE_EDGE_RISING);

	/* fixed or unlimited length? */
	अगर (dev->rx_cfg.fixed_message_length != 0) अणु
		अगर (dev->rx_cfg.fixed_message_length > dev->rx_buffer_size) अणु
			retval = -1;
			जाओ पात;
		पूर्ण
		bytes_total = dev->rx_cfg.fixed_message_length;
		dev_dbg(dev->dev, "rx: msg len set to %d by fixed length",
			bytes_total);
	पूर्ण अन्यथा अणु
		bytes_total = dev->rx_buffer_size;
		dev_dbg(dev->dev, "rx: msg len set to %d as requested by read",
			bytes_total);
	पूर्ण

	/* length byte enabled? */
	अगर (dev->rx_cfg.enable_length_byte == OPTION_ON) अणु
		retval = रुको_event_पूर्णांकerruptible(dev->fअगरo_रुको_queue,
						  dev->मुक्त_in_fअगरo < FIFO_SIZE);
		अगर (retval) /* रुको was पूर्णांकerrupted */
			जाओ पात;

		rf69_पढ़ो_fअगरo(spi, (u8 *)&bytes_total, 1);
		अगर (bytes_total > dev->rx_buffer_size) अणु
			retval = -1;
			जाओ पात;
		पूर्ण
		dev->मुक्त_in_fअगरo++;
		dev_dbg(dev->dev, "rx: msg len reset to %d due to length byte",
			bytes_total);
	पूर्ण

	/* address byte enabled? */
	अगर (dev->rx_cfg.enable_address_filtering != filtering_off) अणु
		u8 dummy;

		bytes_total--;

		retval = रुको_event_पूर्णांकerruptible(dev->fअगरo_रुको_queue,
						  dev->मुक्त_in_fअगरo < FIFO_SIZE);
		अगर (retval) /* रुको was पूर्णांकerrupted */
			जाओ पात;

		rf69_पढ़ो_fअगरo(spi, &dummy, 1);
		dev->मुक्त_in_fअगरo++;
		dev_dbg(dev->dev, "rx: address byte stripped off");
	पूर्ण

	/* get payload */
	जबतक (dev->rx_position < bytes_total) अणु
		अगर (!rf69_get_flag(dev->spi, payload_पढ़ोy)) अणु
			retval = रुको_event_पूर्णांकerruptible(dev->fअगरo_रुको_queue,
							  dev->मुक्त_in_fअगरo < FIFO_SIZE);
			अगर (retval) /* रुको was पूर्णांकerrupted */
				जाओ पात;
		पूर्ण

		/* need to drop bytes or acquire? */
		अगर (dev->rx_bytes_to_drop > dev->rx_bytes_dropped)
			bytes_to_पढ़ो = dev->rx_bytes_to_drop -
					dev->rx_bytes_dropped;
		अन्यथा
			bytes_to_पढ़ो = bytes_total - dev->rx_position;

		/* access the fअगरo */
		अगर (bytes_to_पढ़ो > FIFO_SIZE - dev->मुक्त_in_fअगरo)
			bytes_to_पढ़ो = FIFO_SIZE - dev->मुक्त_in_fअगरo;
		retval = rf69_पढ़ो_fअगरo(spi,
					&dev->rx_buffer[dev->rx_position],
					bytes_to_पढ़ो);
		अगर (retval) /* पढ़ो failed */
			जाओ पात;

		dev->मुक्त_in_fअगरo += bytes_to_पढ़ो;

		/* adjust status vars */
		अगर (dev->rx_bytes_to_drop > dev->rx_bytes_dropped)
			dev->rx_bytes_dropped += bytes_to_पढ़ो;
		अन्यथा
			dev->rx_position += bytes_to_पढ़ो;
	पूर्ण

	/* rx करोne, रुको was पूर्णांकerrupted or error occurred */
पात:
	dev->पूर्णांकerrupt_rx_allowed = true;
	अगर (rf69_set_mode(dev->spi, standby))
		pr_err("rf69_set_mode(): radio module failed to go standby\n");
	wake_up_पूर्णांकerruptible(&dev->tx_रुको_queue);

	अगर (retval)
		वापस retval;
	अन्यथा
		वापस bytes_total;
पूर्ण

अटल पूर्णांक
pi433_tx_thपढ़ो(व्योम *data)
अणु
	काष्ठा pi433_device *device = data;
	काष्ठा spi_device *spi = device->spi;
	काष्ठा pi433_tx_cfg tx_cfg;
	माप_प्रकार size;
	bool   rx_पूर्णांकerrupted = false;
	पूर्णांक    position, repetitions;
	पूर्णांक    retval;

	जबतक (1) अणु
		/* रुको क्रम fअगरo to be populated or क्रम request to terminate*/
		dev_dbg(device->dev, "thread: going to wait for new messages");
		रुको_event_पूर्णांकerruptible(device->tx_रुको_queue,
					 (!kfअगरo_is_empty(&device->tx_fअगरo) ||
					  kthपढ़ो_should_stop()));
		अगर (kthपढ़ो_should_stop())
			वापस 0;

		/*
		 * get data from fअगरo in the following order:
		 * - tx_cfg
		 * - size of message
		 * - message
		 */
		retval = kfअगरo_out(&device->tx_fअगरo, &tx_cfg, माप(tx_cfg));
		अगर (retval != माप(tx_cfg)) अणु
			dev_dbg(device->dev,
				"reading tx_cfg from fifo failed: got %d byte(s), expected %d",
				retval, (अचिन्हित पूर्णांक)माप(tx_cfg));
			जारी;
		पूर्ण

		retval = kfअगरo_out(&device->tx_fअगरo, &size, माप(माप_प्रकार));
		अगर (retval != माप(माप_प्रकार)) अणु
			dev_dbg(device->dev,
				"reading msg size from fifo failed: got %d, expected %d",
				retval, (अचिन्हित पूर्णांक)माप(माप_प्रकार));
			जारी;
		पूर्ण

		/* use fixed message length, अगर requested */
		अगर (tx_cfg.fixed_message_length != 0)
			size = tx_cfg.fixed_message_length;

		/* increase size, अगर len byte is requested */
		अगर (tx_cfg.enable_length_byte == OPTION_ON)
			size++;

		/* increase size, अगर adr byte is requested */
		अगर (tx_cfg.enable_address_byte == OPTION_ON)
			size++;

		/* prime buffer */
		स_रखो(device->buffer, 0, size);
		position = 0;

		/* add length byte, अगर requested */
		अगर (tx_cfg.enable_length_byte  == OPTION_ON)
			/*
			 * according to spec, length byte itself must be
			 * excluded from the length calculation
			 */
			device->buffer[position++] = size - 1;

		/* add adr byte, अगर requested */
		अगर (tx_cfg.enable_address_byte == OPTION_ON)
			device->buffer[position++] = tx_cfg.address_byte;

		/* finally get message data from fअगरo */
		retval = kfअगरo_out(&device->tx_fअगरo, &device->buffer[position],
				   माप(device->buffer) - position);
		dev_dbg(device->dev,
			"read %d message byte(s) from fifo queue.", retval);

		/*
		 * अगर rx is active, we need to पूर्णांकerrupt the रुकोing क्रम
		 * incoming telegrams, to be able to send something.
		 * We are only allowed, अगर currently no reception takes
		 * place otherwise we need to  रुको क्रम the incoming telegram
		 * to finish
		 */
		रुको_event_पूर्णांकerruptible(device->tx_रुको_queue,
					 !device->rx_active ||
					  device->पूर्णांकerrupt_rx_allowed);

		/*
		 * prevent race conditions
		 * irq will be reenabled after tx config is set
		 */
		disable_irq(device->irq_num[DIO0]);
		device->tx_active = true;

		/* clear fअगरo, set fअगरo threshold, set payload length */
		retval = rf69_set_mode(spi, standby); /* this clears the fअगरo */
		अगर (retval < 0)
			वापस retval;

		अगर (device->rx_active && !rx_पूर्णांकerrupted) अणु
			/*
			 * rx is currently रुकोing क्रम a telegram;
			 * we need to set the radio module to standby
			 */
			rx_पूर्णांकerrupted = true;
		पूर्ण

		retval = rf69_set_fअगरo_threshold(spi, FIFO_THRESHOLD);
		अगर (retval < 0)
			वापस retval;
		अगर (tx_cfg.enable_length_byte == OPTION_ON) अणु
			retval = rf69_set_payload_length(spi, size * tx_cfg.repetitions);
			अगर (retval < 0)
				वापस retval;
		पूर्ण अन्यथा अणु
			retval = rf69_set_payload_length(spi, 0);
			अगर (retval < 0)
				वापस retval;
		पूर्ण

		/* configure the rf chip */
		retval = rf69_set_tx_cfg(device, &tx_cfg);
		अगर (retval < 0)
			वापस retval;

		/* enable fअगरo level पूर्णांकerrupt */
		retval = rf69_set_dio_mapping(spi, DIO1, DIO_FIFO_LEVEL);
		अगर (retval < 0)
			वापस retval;
		device->irq_state[DIO1] = DIO_FIFO_LEVEL;
		irq_set_irq_type(device->irq_num[DIO1], IRQ_TYPE_EDGE_FALLING);

		/* enable packet sent पूर्णांकerrupt */
		retval = rf69_set_dio_mapping(spi, DIO0, DIO_PACKET_SENT);
		अगर (retval < 0)
			वापस retval;
		device->irq_state[DIO0] = DIO_PACKET_SENT;
		irq_set_irq_type(device->irq_num[DIO0], IRQ_TYPE_EDGE_RISING);
		enable_irq(device->irq_num[DIO0]); /* was disabled by rx active check */

		/* enable transmission */
		retval = rf69_set_mode(spi, transmit);
		अगर (retval < 0)
			वापस retval;

		/* transfer this msg (and repetitions) to chip fअगरo */
		device->मुक्त_in_fअगरo = FIFO_SIZE;
		position = 0;
		repetitions = tx_cfg.repetitions;
		जबतक ((repetitions > 0) && (size > position)) अणु
			अगर ((size - position) > device->मुक्त_in_fअगरo) अणु
				/* msg to big क्रम fअगरo - take a part */
				पूर्णांक ग_लिखो_size = device->मुक्त_in_fअगरo;

				device->मुक्त_in_fअगरo = 0;
				rf69_ग_लिखो_fअगरo(spi,
						&device->buffer[position],
						ग_लिखो_size);
				position += ग_लिखो_size;
			पूर्ण अन्यथा अणु
				/* msg fits पूर्णांकo fअगरo - take all */
				device->मुक्त_in_fअगरo -= size;
				repetitions--;
				rf69_ग_लिखो_fअगरo(spi,
						&device->buffer[position],
						(size - position));
				position = 0; /* reset क्रम next repetition */
			पूर्ण

			retval = रुको_event_पूर्णांकerruptible(device->fअगरo_रुको_queue,
							  device->मुक्त_in_fअगरo > 0);
			अगर (retval) अणु
				dev_dbg(device->dev, "ABORT\n");
				जाओ पात;
			पूर्ण
		पूर्ण

		/* we are करोne. Wait क्रम packet to get sent */
		dev_dbg(device->dev,
			"thread: wait for packet to get sent/fifo to be empty");
		रुको_event_पूर्णांकerruptible(device->fअगरo_रुको_queue,
					 device->मुक्त_in_fअगरo == FIFO_SIZE ||
					 kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop())
			वापस 0;

		/* STOP_TRANSMISSION */
		dev_dbg(device->dev, "thread: Packet sent. Set mode to stby.");
		retval = rf69_set_mode(spi, standby);
		अगर (retval < 0)
			वापस retval;

		/* everything sent? */
		अगर (kfअगरo_is_empty(&device->tx_fअगरo)) अणु
पात:
			अगर (rx_पूर्णांकerrupted) अणु
				rx_पूर्णांकerrupted = false;
				pi433_start_rx(device);
			पूर्ण
			device->tx_active = false;
			wake_up_पूर्णांकerruptible(&device->rx_रुको_queue);
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल sमाप_प्रकार
pi433_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार size, loff_t *f_pos)
अणु
	काष्ठा pi433_instance	*instance;
	काष्ठा pi433_device	*device;
	पूर्णांक			bytes_received;
	sमाप_प्रकार			retval;

	/* check, whether पूर्णांकernal buffer is big enough क्रम requested size */
	अगर (size > MAX_MSG_SIZE)
		वापस -EMSGSIZE;

	instance = filp->निजी_data;
	device = instance->device;

	/* just one पढ़ो request at a समय */
	mutex_lock(&device->rx_lock);
	अगर (device->rx_active) अणु
		mutex_unlock(&device->rx_lock);
		वापस -EAGAIN;
	पूर्ण

	device->rx_active = true;
	mutex_unlock(&device->rx_lock);

	/* start receiving */
	/* will block until something was received*/
	device->rx_buffer_size = size;
	bytes_received = pi433_receive(device);

	/* release rx */
	mutex_lock(&device->rx_lock);
	device->rx_active = false;
	mutex_unlock(&device->rx_lock);

	/* अगर पढ़ो was successful copy to user space*/
	अगर (bytes_received > 0) अणु
		retval = copy_to_user(buf, device->rx_buffer, bytes_received);
		अगर (retval)
			वापस -EFAULT;
	पूर्ण

	वापस bytes_received;
पूर्ण

अटल sमाप_प्रकार
pi433_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
	    माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा pi433_instance	*instance;
	काष्ठा pi433_device	*device;
	पूर्णांक                     retval;
	अचिन्हित पूर्णांक		required, available, copied;

	instance = filp->निजी_data;
	device = instance->device;

	/*
	 * check, whether पूर्णांकernal buffer (tx thपढ़ो) is big enough
	 * क्रम requested size
	 */
	अगर (count > MAX_MSG_SIZE)
		वापस -EMSGSIZE;

	/*
	 * ग_लिखो the following sequence पूर्णांकo fअगरo:
	 * - tx_cfg
	 * - size of message
	 * - message
	 */
	mutex_lock(&device->tx_fअगरo_lock);

	required = माप(instance->tx_cfg) + माप(माप_प्रकार) + count;
	available = kfअगरo_avail(&device->tx_fअगरo);
	अगर (required > available) अणु
		dev_dbg(device->dev, "write to fifo failed: %d bytes required but %d available",
			required, available);
		mutex_unlock(&device->tx_fअगरo_lock);
		वापस -EAGAIN;
	पूर्ण

	retval = kfअगरo_in(&device->tx_fअगरo, &instance->tx_cfg,
			  माप(instance->tx_cfg));
	अगर (retval != माप(instance->tx_cfg))
		जाओ पात;

	retval = kfअगरo_in(&device->tx_fअगरo, &count, माप(माप_प्रकार));
	अगर (retval != माप(माप_प्रकार))
		जाओ पात;

	retval = kfअगरo_from_user(&device->tx_fअगरo, buf, count, &copied);
	अगर (retval || copied != count)
		जाओ पात;

	mutex_unlock(&device->tx_fअगरo_lock);

	/* start transfer */
	wake_up_पूर्णांकerruptible(&device->tx_रुको_queue);
	dev_dbg(device->dev, "write: generated new msg with %d bytes.", copied);

	वापस copied;

पात:
	dev_warn(device->dev,
		 "write to fifo failed, non recoverable: 0x%x", retval);
	mutex_unlock(&device->tx_fअगरo_lock);
	वापस -EAGAIN;
पूर्ण

अटल दीर्घ
pi433_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pi433_instance	*instance;
	काष्ठा pi433_device	*device;
	काष्ठा pi433_tx_cfg	tx_cfg;
	व्योम __user *argp = (व्योम __user *)arg;

	/* Check type and command number */
	अगर (_IOC_TYPE(cmd) != PI433_IOC_MAGIC)
		वापस -ENOTTY;

	instance = filp->निजी_data;
	device = instance->device;

	अगर (!device)
		वापस -ESHUTDOWN;

	चयन (cmd) अणु
	हाल PI433_IOC_RD_TX_CFG:
		अगर (copy_to_user(argp, &instance->tx_cfg,
				 माप(काष्ठा pi433_tx_cfg)))
			वापस -EFAULT;
		अवरोध;
	हाल PI433_IOC_WR_TX_CFG:
		अगर (copy_from_user(&tx_cfg, argp, माप(काष्ठा pi433_tx_cfg)))
			वापस -EFAULT;
		mutex_lock(&device->tx_fअगरo_lock);
		स_नकल(&instance->tx_cfg, &tx_cfg, माप(काष्ठा pi433_tx_cfg));
		mutex_unlock(&device->tx_fअगरo_lock);
		अवरोध;
	हाल PI433_IOC_RD_RX_CFG:
		अगर (copy_to_user(argp, &device->rx_cfg,
				 माप(काष्ठा pi433_rx_cfg)))
			वापस -EFAULT;
		अवरोध;
	हाल PI433_IOC_WR_RX_CFG:
		mutex_lock(&device->rx_lock);

		/* during pendig पढ़ो request, change of config not allowed */
		अगर (device->rx_active) अणु
			mutex_unlock(&device->rx_lock);
			वापस -EAGAIN;
		पूर्ण

		अगर (copy_from_user(&device->rx_cfg, argp,
				   माप(काष्ठा pi433_rx_cfg))) अणु
			mutex_unlock(&device->rx_lock);
			वापस -EFAULT;
		पूर्ण

		mutex_unlock(&device->rx_lock);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pi433_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा pi433_device	*device;
	काष्ठा pi433_instance	*instance;

	mutex_lock(&minor_lock);
	device = idr_find(&pi433_idr, iminor(inode));
	mutex_unlock(&minor_lock);
	अगर (!device) अणु
		pr_debug("device: minor %d unknown.\n", iminor(inode));
		वापस -ENODEV;
	पूर्ण

	instance = kzalloc(माप(*instance), GFP_KERNEL);
	अगर (!instance)
		वापस -ENOMEM;

	/* setup instance data*/
	instance->device = device;
	instance->tx_cfg.bit_rate = 4711;
	// TODO: fill instance->tx_cfg;

	/* instance data as context */
	filp->निजी_data = instance;
	stream_खोलो(inode, filp);

	वापस 0;
पूर्ण

अटल पूर्णांक pi433_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा pi433_instance	*instance;

	instance = filp->निजी_data;
	kमुक्त(instance);
	filp->निजी_data = शून्य;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक setup_gpio(काष्ठा pi433_device *device)
अणु
	अक्षर	name[5];
	पूर्णांक	retval;
	पूर्णांक	i;
	स्थिर irq_handler_t DIO_irq_handler[NUM_DIO] = अणु
		DIO0_irq_handler,
		DIO1_irq_handler
	पूर्ण;

	क्रम (i = 0; i < NUM_DIO; i++) अणु
		/* "construct" name and get the gpio descriptor */
		snम_लिखो(name, माप(name), "DIO%d", i);
		device->gpiod[i] = gpiod_get(&device->spi->dev, name,
					     0 /*GPIOD_IN*/);

		अगर (device->gpiod[i] == ERR_PTR(-ENOENT)) अणु
			dev_dbg(&device->spi->dev,
				"Could not find entry for %s. Ignoring.", name);
			जारी;
		पूर्ण

		अगर (device->gpiod[i] == ERR_PTR(-EBUSY))
			dev_dbg(&device->spi->dev, "%s is busy.", name);

		अगर (IS_ERR(device->gpiod[i])) अणु
			retval = PTR_ERR(device->gpiod[i]);
			/* release alपढ़ोy allocated gpios */
			क्रम (i--; i >= 0; i--) अणु
				मुक्त_irq(device->irq_num[i], device);
				gpiod_put(device->gpiod[i]);
			पूर्ण
			वापस retval;
		पूर्ण

		/* configure the pin */
		gpiod_unexport(device->gpiod[i]);
		retval = gpiod_direction_input(device->gpiod[i]);
		अगर (retval)
			वापस retval;

		/* configure irq */
		device->irq_num[i] = gpiod_to_irq(device->gpiod[i]);
		अगर (device->irq_num[i] < 0) अणु
			device->gpiod[i] = ERR_PTR(-EINVAL);
			वापस device->irq_num[i];
		पूर्ण
		retval = request_irq(device->irq_num[i],
				     DIO_irq_handler[i],
				     0, /* flags */
				     name,
				     device);

		अगर (retval)
			वापस retval;

		dev_dbg(&device->spi->dev, "%s successfully configured", name);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_gpio(काष्ठा pi433_device *device)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_DIO; i++) अणु
		/* check अगर gpiod is valid */
		अगर (IS_ERR(device->gpiod[i]))
			जारी;

		मुक्त_irq(device->irq_num[i], device);
		gpiod_put(device->gpiod[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक pi433_get_minor(काष्ठा pi433_device *device)
अणु
	पूर्णांक retval = -ENOMEM;

	mutex_lock(&minor_lock);
	retval = idr_alloc(&pi433_idr, device, 0, N_PI433_MINORS, GFP_KERNEL);
	अगर (retval >= 0) अणु
		device->minor = retval;
		retval = 0;
	पूर्ण अन्यथा अगर (retval == -ENOSPC) अणु
		dev_err(&device->spi->dev, "too many pi433 devices\n");
		retval = -EINVAL;
	पूर्ण
	mutex_unlock(&minor_lock);
	वापस retval;
पूर्ण

अटल व्योम pi433_मुक्त_minor(काष्ठा pi433_device *dev)
अणु
	mutex_lock(&minor_lock);
	idr_हटाओ(&pi433_idr, dev->minor);
	mutex_unlock(&minor_lock);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा file_operations pi433_fops = अणु
	.owner =	THIS_MODULE,
	/*
	 * REVISIT चयन to aio primitives, so that userspace
	 * माला_लो more complete API coverage.  It'll simplअगरy things
	 * too, except क्रम the locking.
	 */
	.ग_लिखो =	pi433_ग_लिखो,
	.पढ़ो =		pi433_पढ़ो,
	.unlocked_ioctl = pi433_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.खोलो =		pi433_खोलो,
	.release =	pi433_release,
	.llseek =	no_llseek,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक pi433_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा pi433_device	*device;
	पूर्णांक			retval;

	/* setup spi parameters */
	spi->mode = 0x00;
	spi->bits_per_word = 8;
	/*
	 * spi->max_speed_hz = 10000000;
	 * 1MHz alपढ़ोy set by device tree overlay
	 */

	retval = spi_setup(spi);
	अगर (retval) अणु
		dev_dbg(&spi->dev, "configuration of SPI interface failed!\n");
		वापस retval;
	पूर्ण

	dev_dbg(&spi->dev,
		"spi interface setup: mode 0x%2x, %d bits per word, %dhz max speed",
		spi->mode, spi->bits_per_word, spi->max_speed_hz);

	/* Ping the chip by पढ़ोing the version रेजिस्टर */
	retval = spi_w8r8(spi, 0x10);
	अगर (retval < 0)
		वापस retval;

	चयन (retval) अणु
	हाल 0x24:
		dev_dbg(&spi->dev, "found pi433 (ver. 0x%x)", retval);
		अवरोध;
	शेष:
		dev_dbg(&spi->dev, "unknown chip version: 0x%x", retval);
		वापस -ENODEV;
	पूर्ण

	/* Allocate driver data */
	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device)
		वापस -ENOMEM;

	/* Initialize the driver data */
	device->spi = spi;
	device->rx_active = false;
	device->tx_active = false;
	device->पूर्णांकerrupt_rx_allowed = false;

	/* init rx buffer */
	device->rx_buffer = kदो_स्मृति(MAX_MSG_SIZE, GFP_KERNEL);
	अगर (!device->rx_buffer) अणु
		retval = -ENOMEM;
		जाओ RX_failed;
	पूर्ण

	/* init रुको queues */
	init_रुकोqueue_head(&device->tx_रुको_queue);
	init_रुकोqueue_head(&device->rx_रुको_queue);
	init_रुकोqueue_head(&device->fअगरo_रुको_queue);

	/* init fअगरo */
	INIT_KFIFO(device->tx_fअगरo);

	/* init mutexes and locks */
	mutex_init(&device->tx_fअगरo_lock);
	mutex_init(&device->rx_lock);

	/* setup GPIO (including irq_handler) क्रम the dअगरferent DIOs */
	retval = setup_gpio(device);
	अगर (retval) अणु
		dev_dbg(&spi->dev, "setup of GPIOs failed");
		जाओ GPIO_failed;
	पूर्ण

	/* setup the radio module */
	retval = rf69_set_mode(spi, standby);
	अगर (retval < 0)
		जाओ minor_failed;
	retval = rf69_set_data_mode(spi, DATAMODUL_MODE_PACKET);
	अगर (retval < 0)
		जाओ minor_failed;
	retval = rf69_enable_amplअगरier(spi, MASK_PALEVEL_PA0);
	अगर (retval < 0)
		जाओ minor_failed;
	retval = rf69_disable_amplअगरier(spi, MASK_PALEVEL_PA1);
	अगर (retval < 0)
		जाओ minor_failed;
	retval = rf69_disable_amplअगरier(spi, MASK_PALEVEL_PA2);
	अगर (retval < 0)
		जाओ minor_failed;
	retval = rf69_set_output_घातer_level(spi, 13);
	अगर (retval < 0)
		जाओ minor_failed;
	retval = rf69_set_antenna_impedance(spi, fअगरty_ohm);
	अगर (retval < 0)
		जाओ minor_failed;

	/* determ minor number */
	retval = pi433_get_minor(device);
	अगर (retval) अणु
		dev_dbg(&spi->dev, "get of minor number failed");
		जाओ minor_failed;
	पूर्ण

	/* create device */
	device->devt = MKDEV(MAJOR(pi433_dev), device->minor);
	device->dev = device_create(pi433_class,
				    &spi->dev,
				    device->devt,
				    device,
				    "pi433.%d",
				    device->minor);
	अगर (IS_ERR(device->dev)) अणु
		pr_err("pi433: device register failed\n");
		retval = PTR_ERR(device->dev);
		जाओ device_create_failed;
	पूर्ण अन्यथा अणु
		dev_dbg(device->dev,
			"created device for major %d, minor %d\n",
			MAJOR(pi433_dev),
			device->minor);
	पूर्ण

	/* start tx thपढ़ो */
	device->tx_task_काष्ठा = kthपढ़ो_run(pi433_tx_thपढ़ो,
					     device,
					     "pi433.%d_tx_task",
					     device->minor);
	अगर (IS_ERR(device->tx_task_काष्ठा)) अणु
		dev_dbg(device->dev, "start of send thread failed");
		retval = PTR_ERR(device->tx_task_काष्ठा);
		जाओ send_thपढ़ो_failed;
	पूर्ण

	/* create cdev */
	device->cdev = cdev_alloc();
	अगर (!device->cdev) अणु
		dev_dbg(device->dev, "allocation of cdev failed");
		retval = -ENOMEM;
		जाओ cdev_failed;
	पूर्ण
	device->cdev->owner = THIS_MODULE;
	cdev_init(device->cdev, &pi433_fops);
	retval = cdev_add(device->cdev, device->devt, 1);
	अगर (retval) अणु
		dev_dbg(device->dev, "register of cdev failed");
		जाओ del_cdev;
	पूर्ण

	/* spi setup */
	spi_set_drvdata(spi, device);

	वापस 0;

del_cdev:
	cdev_del(device->cdev);
cdev_failed:
	kthपढ़ो_stop(device->tx_task_काष्ठा);
send_thपढ़ो_failed:
	device_destroy(pi433_class, device->devt);
device_create_failed:
	pi433_मुक्त_minor(device);
minor_failed:
	मुक्त_gpio(device);
GPIO_failed:
	kमुक्त(device->rx_buffer);
RX_failed:
	kमुक्त(device);

	वापस retval;
पूर्ण

अटल पूर्णांक pi433_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा pi433_device	*device = spi_get_drvdata(spi);

	/* मुक्त GPIOs */
	मुक्त_gpio(device);

	/* make sure ops on existing fds can पात cleanly */
	device->spi = शून्य;

	kthपढ़ो_stop(device->tx_task_काष्ठा);

	device_destroy(pi433_class, device->devt);

	cdev_del(device->cdev);

	pi433_मुक्त_minor(device);

	kमुक्त(device->rx_buffer);
	kमुक्त(device);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pi433_dt_ids[] = अणु
	अणु .compatible = "Smarthome-Wolf,pi433" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, pi433_dt_ids);

अटल काष्ठा spi_driver pi433_spi_driver = अणु
	.driver = अणु
		.name =		"pi433",
		.owner =	THIS_MODULE,
		.of_match_table = of_match_ptr(pi433_dt_ids),
	पूर्ण,
	.probe =	pi433_probe,
	.हटाओ =	pi433_हटाओ,

	/*
	 * NOTE:  suspend/resume methods are not necessary here.
	 * We करोn't करो anything except pass the requests to/from
	 * the underlying controller.  The refrigerator handles
	 * most issues; the controller driver handles the rest.
	 */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init pi433_init(व्योम)
अणु
	पूर्णांक status;

	/*
	 * If MAX_MSG_SIZE is smaller then FIFO_SIZE, the driver won't
	 * work stable - risk of buffer overflow
	 */
	अगर (MAX_MSG_SIZE < FIFO_SIZE)
		वापस -EINVAL;

	/*
	 * Claim device numbers.  Then रेजिस्टर a class
	 * that will key udev/mdev to add/हटाओ /dev nodes.  Last, रेजिस्टर
	 * Last, रेजिस्टर the driver which manages those device numbers.
	 */
	status = alloc_chrdev_region(&pi433_dev, 0, N_PI433_MINORS, "pi433");
	अगर (status < 0)
		वापस status;

	pi433_class = class_create(THIS_MODULE, "pi433");
	अगर (IS_ERR(pi433_class)) अणु
		unरेजिस्टर_chrdev(MAJOR(pi433_dev),
				  pi433_spi_driver.driver.name);
		वापस PTR_ERR(pi433_class);
	पूर्ण

	status = spi_रेजिस्टर_driver(&pi433_spi_driver);
	अगर (status < 0) अणु
		class_destroy(pi433_class);
		unरेजिस्टर_chrdev(MAJOR(pi433_dev),
				  pi433_spi_driver.driver.name);
	पूर्ण

	वापस status;
पूर्ण

module_init(pi433_init);

अटल व्योम __निकास pi433_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&pi433_spi_driver);
	class_destroy(pi433_class);
	unरेजिस्टर_chrdev(MAJOR(pi433_dev), pi433_spi_driver.driver.name);
पूर्ण
module_निकास(pi433_निकास);

MODULE_AUTHOR("Marcus Wolf, <linux@wolf-entwicklungen.de>");
MODULE_DESCRIPTION("Driver for Pi433");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:pi433");
