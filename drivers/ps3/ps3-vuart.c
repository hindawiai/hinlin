<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 भव uart
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/ps3.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>

#समावेश "vuart.h"

MODULE_AUTHOR("Sony Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PS3 vuart");

/**
 * vuart - An पूर्णांकer-partition data link service.
 *  port 0: PS3 AV Settings.
 *  port 2: PS3 System Manager.
 *
 * The vuart provides a bi-directional byte stream data link between logical
 * partitions.  Its primary role is as a communications link between the guest
 * OS and the प्रणाली policy module.  The current HV करोes not support any
 * connections other than those listed.
 */

क्रमागत अणुPORT_COUNT = 3,पूर्ण;

क्रमागत vuart_param अणु
	PARAM_TX_TRIGGER = 0,
	PARAM_RX_TRIGGER = 1,
	PARAM_INTERRUPT_MASK = 2,
	PARAM_RX_BUF_SIZE = 3, /* पढ़ो only */
	PARAM_RX_BYTES = 4, /* पढ़ो only */
	PARAM_TX_BUF_SIZE = 5, /* पढ़ो only */
	PARAM_TX_BYTES = 6, /* पढ़ो only */
	PARAM_INTERRUPT_STATUS = 7, /* पढ़ो only */
पूर्ण;

क्रमागत vuart_पूर्णांकerrupt_bit अणु
	INTERRUPT_BIT_TX = 0,
	INTERRUPT_BIT_RX = 1,
	INTERRUPT_BIT_DISCONNECT = 2,
पूर्ण;

क्रमागत vuart_पूर्णांकerrupt_mask अणु
	INTERRUPT_MASK_TX = 1,
	INTERRUPT_MASK_RX = 2,
	INTERRUPT_MASK_DISCONNECT = 4,
पूर्ण;

/**
 * काष्ठा ps3_vuart_port_priv - निजी vuart device data.
 */

काष्ठा ps3_vuart_port_priv अणु
	u64 पूर्णांकerrupt_mask;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा list_head head;
	पूर्ण tx_list;
	काष्ठा अणु
		काष्ठा ps3_vuart_work work;
		अचिन्हित दीर्घ bytes_held;
		spinlock_t lock;
		काष्ठा list_head head;
	पूर्ण rx_list;
	काष्ठा ps3_vuart_stats stats;
पूर्ण;

अटल काष्ठा ps3_vuart_port_priv *to_port_priv(
	काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	BUG_ON(!dev);
	BUG_ON(!dev->driver_priv);
	वापस (काष्ठा ps3_vuart_port_priv *)dev->driver_priv;
पूर्ण

/**
 * काष्ठा ports_bmp - biपंचांगap indicating ports needing service.
 *
 * A 256 bit पढ़ो only biपंचांगap indicating ports needing service.  Do not ग_लिखो
 * to these bits.  Must not cross a page boundary.
 */

काष्ठा ports_bmp अणु
	u64 status;
	u64 unused[3];
पूर्ण __attribute__((aligned(32)));

#घोषणा dump_ports_bmp(_b) _dump_ports_bmp(_b, __func__, __LINE__)
अटल व्योम __maybe_unused _dump_ports_bmp(
	स्थिर काष्ठा ports_bmp *bmp, स्थिर अक्षर *func, पूर्णांक line)
अणु
	pr_debug("%s:%d: ports_bmp: %016llxh\n", func, line, bmp->status);
पूर्ण

#घोषणा dump_port_params(_b) _dump_port_params(_b, __func__, __LINE__)
अटल व्योम __maybe_unused _dump_port_params(अचिन्हित पूर्णांक port_number,
	स्थिर अक्षर *func, पूर्णांक line)
अणु
#अगर defined(DEBUG)
	अटल स्थिर अक्षर *strings[] = अणु
		"tx_trigger      ",
		"rx_trigger      ",
		"interrupt_mask  ",
		"rx_buf_size     ",
		"rx_bytes        ",
		"tx_buf_size     ",
		"tx_bytes        ",
		"interrupt_status",
	पूर्ण;
	पूर्णांक result;
	अचिन्हित पूर्णांक i;
	u64 value;

	क्रम (i = 0; i < ARRAY_SIZE(strings); i++) अणु
		result = lv1_get_भव_uart_param(port_number, i, &value);

		अगर (result) अणु
			pr_debug("%s:%d: port_%u: %s failed: %s\n", func, line,
				port_number, strings[i], ps3_result(result));
			जारी;
		पूर्ण
		pr_debug("%s:%d: port_%u: %s = %lxh\n",
			func, line, port_number, strings[i], value);
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक ps3_vuart_get_triggers(काष्ठा ps3_प्रणाली_bus_device *dev,
	काष्ठा vuart_triggers *trig)
अणु
	पूर्णांक result;
	u64 size;
	u64 val;
	u64 tx;

	result = lv1_get_भव_uart_param(dev->port_number,
		PARAM_TX_TRIGGER, &tx);
	trig->tx = tx;

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: tx_trigger failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = lv1_get_भव_uart_param(dev->port_number,
		PARAM_RX_BUF_SIZE, &size);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: tx_buf_size failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = lv1_get_भव_uart_param(dev->port_number,
		PARAM_RX_TRIGGER, &val);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: rx_trigger failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	trig->rx = size - val;

	dev_dbg(&dev->core, "%s:%d: tx %lxh, rx %lxh\n", __func__, __LINE__,
		trig->tx, trig->rx);

	वापस result;
पूर्ण

पूर्णांक ps3_vuart_set_triggers(काष्ठा ps3_प्रणाली_bus_device *dev, अचिन्हित पूर्णांक tx,
	अचिन्हित पूर्णांक rx)
अणु
	पूर्णांक result;
	u64 size;

	result = lv1_set_भव_uart_param(dev->port_number,
		PARAM_TX_TRIGGER, tx);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: tx_trigger failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = lv1_get_भव_uart_param(dev->port_number,
		PARAM_RX_BUF_SIZE, &size);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: tx_buf_size failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = lv1_set_भव_uart_param(dev->port_number,
		PARAM_RX_TRIGGER, size - rx);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: rx_trigger failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	dev_dbg(&dev->core, "%s:%d: tx %xh, rx %xh\n", __func__, __LINE__,
		tx, rx);

	वापस result;
पूर्ण

अटल पूर्णांक ps3_vuart_get_rx_bytes_रुकोing(काष्ठा ps3_प्रणाली_bus_device *dev,
	u64 *bytes_रुकोing)
अणु
	पूर्णांक result;

	result = lv1_get_भव_uart_param(dev->port_number,
		PARAM_RX_BYTES, bytes_रुकोing);

	अगर (result)
		dev_dbg(&dev->core, "%s:%d: rx_bytes failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	dev_dbg(&dev->core, "%s:%d: %llxh\n", __func__, __LINE__,
		*bytes_रुकोing);
	वापस result;
पूर्ण

/**
 * ps3_vuart_set_पूर्णांकerrupt_mask - Enable/disable the port पूर्णांकerrupt sources.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 * @bmp: Logical OR of क्रमागत vuart_पूर्णांकerrupt_mask values. A zero bit disables.
 */

अटल पूर्णांक ps3_vuart_set_पूर्णांकerrupt_mask(काष्ठा ps3_प्रणाली_bus_device *dev,
	अचिन्हित दीर्घ mask)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	dev_dbg(&dev->core, "%s:%d: %lxh\n", __func__, __LINE__, mask);

	priv->पूर्णांकerrupt_mask = mask;

	result = lv1_set_भव_uart_param(dev->port_number,
		PARAM_INTERRUPT_MASK, priv->पूर्णांकerrupt_mask);

	अगर (result)
		dev_dbg(&dev->core, "%s:%d: interrupt_mask failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	वापस result;
पूर्ण

अटल पूर्णांक ps3_vuart_get_पूर्णांकerrupt_status(काष्ठा ps3_प्रणाली_bus_device *dev,
	अचिन्हित दीर्घ *status)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	u64 पंचांगp;

	result = lv1_get_भव_uart_param(dev->port_number,
		PARAM_INTERRUPT_STATUS, &पंचांगp);

	अगर (result)
		dev_dbg(&dev->core, "%s:%d: interrupt_status failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	*status = पंचांगp & priv->पूर्णांकerrupt_mask;

	dev_dbg(&dev->core, "%s:%d: m %llxh, s %llxh, m&s %lxh\n",
		__func__, __LINE__, priv->पूर्णांकerrupt_mask, पंचांगp, *status);

	वापस result;
पूर्ण

पूर्णांक ps3_vuart_enable_पूर्णांकerrupt_tx(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	वापस (priv->पूर्णांकerrupt_mask & INTERRUPT_MASK_TX) ? 0
		: ps3_vuart_set_पूर्णांकerrupt_mask(dev, priv->पूर्णांकerrupt_mask
		| INTERRUPT_MASK_TX);
पूर्ण

पूर्णांक ps3_vuart_enable_पूर्णांकerrupt_rx(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	वापस (priv->पूर्णांकerrupt_mask & INTERRUPT_MASK_RX) ? 0
		: ps3_vuart_set_पूर्णांकerrupt_mask(dev, priv->पूर्णांकerrupt_mask
		| INTERRUPT_MASK_RX);
पूर्ण

पूर्णांक ps3_vuart_enable_पूर्णांकerrupt_disconnect(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	वापस (priv->पूर्णांकerrupt_mask & INTERRUPT_MASK_DISCONNECT) ? 0
		: ps3_vuart_set_पूर्णांकerrupt_mask(dev, priv->पूर्णांकerrupt_mask
		| INTERRUPT_MASK_DISCONNECT);
पूर्ण

पूर्णांक ps3_vuart_disable_पूर्णांकerrupt_tx(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	वापस (priv->पूर्णांकerrupt_mask & INTERRUPT_MASK_TX)
		? ps3_vuart_set_पूर्णांकerrupt_mask(dev, priv->पूर्णांकerrupt_mask
		& ~INTERRUPT_MASK_TX) : 0;
पूर्ण

पूर्णांक ps3_vuart_disable_पूर्णांकerrupt_rx(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	वापस (priv->पूर्णांकerrupt_mask & INTERRUPT_MASK_RX)
		? ps3_vuart_set_पूर्णांकerrupt_mask(dev, priv->पूर्णांकerrupt_mask
		& ~INTERRUPT_MASK_RX) : 0;
पूर्ण

पूर्णांक ps3_vuart_disable_पूर्णांकerrupt_disconnect(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	वापस (priv->पूर्णांकerrupt_mask & INTERRUPT_MASK_DISCONNECT)
		? ps3_vuart_set_पूर्णांकerrupt_mask(dev, priv->पूर्णांकerrupt_mask
		& ~INTERRUPT_MASK_DISCONNECT) : 0;
पूर्ण

/**
 * ps3_vuart_raw_ग_लिखो - Low level ग_लिखो helper.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 *
 * Do not call ps3_vuart_raw_ग_लिखो directly, use ps3_vuart_ग_लिखो.
 */

अटल पूर्णांक ps3_vuart_raw_ग_लिखो(काष्ठा ps3_प्रणाली_bus_device *dev,
	स्थिर व्योम *buf, अचिन्हित पूर्णांक bytes, u64 *bytes_written)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	result = lv1_ग_लिखो_भव_uart(dev->port_number,
		ps3_mm_phys_to_lpar(__pa(buf)), bytes, bytes_written);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: lv1_write_virtual_uart failed: "
			"%s\n", __func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	priv->stats.bytes_written += *bytes_written;

	dev_dbg(&dev->core, "%s:%d: wrote %llxh/%xh=>%lxh\n", __func__, __LINE__,
		*bytes_written, bytes, priv->stats.bytes_written);

	वापस result;
पूर्ण

/**
 * ps3_vuart_raw_पढ़ो - Low level पढ़ो helper.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 *
 * Do not call ps3_vuart_raw_पढ़ो directly, use ps3_vuart_पढ़ो.
 */

अटल पूर्णांक ps3_vuart_raw_पढ़ो(काष्ठा ps3_प्रणाली_bus_device *dev, व्योम *buf,
	अचिन्हित पूर्णांक bytes, u64 *bytes_पढ़ो)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);

	dev_dbg(&dev->core, "%s:%d: %xh\n", __func__, __LINE__, bytes);

	result = lv1_पढ़ो_भव_uart(dev->port_number,
		ps3_mm_phys_to_lpar(__pa(buf)), bytes, bytes_पढ़ो);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: lv1_read_virtual_uart failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	priv->stats.bytes_पढ़ो += *bytes_पढ़ो;

	dev_dbg(&dev->core, "%s:%d: read %llxh/%xh=>%lxh\n", __func__, __LINE__,
		*bytes_पढ़ो, bytes, priv->stats.bytes_पढ़ो);

	वापस result;
पूर्ण

/**
 * ps3_vuart_clear_rx_bytes - Discard bytes received.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 * @bytes: Max byte count to discard, zero = all pending.
 *
 * Used to clear pending rx पूर्णांकerrupt source.  Will not block.
 */

व्योम ps3_vuart_clear_rx_bytes(काष्ठा ps3_प्रणाली_bus_device *dev,
	अचिन्हित पूर्णांक bytes)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	u64 bytes_रुकोing;
	व्योम *पंचांगp;

	result = ps3_vuart_get_rx_bytes_रुकोing(dev, &bytes_रुकोing);

	BUG_ON(result);

	bytes = bytes ? min(bytes, (अचिन्हित पूर्णांक)bytes_रुकोing) : bytes_रुकोing;

	dev_dbg(&dev->core, "%s:%d: %u\n", __func__, __LINE__, bytes);

	अगर (!bytes)
		वापस;

	/* Add some extra space क्रम recently arrived data. */

	bytes += 128;

	पंचांगp = kदो_स्मृति(bytes, GFP_KERNEL);

	अगर (!पंचांगp)
		वापस;

	ps3_vuart_raw_पढ़ो(dev, पंचांगp, bytes, &bytes_रुकोing);

	kमुक्त(पंचांगp);

	/* Don't include these bytes in the stats. */

	priv->stats.bytes_पढ़ो -= bytes_रुकोing;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_clear_rx_bytes);

/**
 * काष्ठा list_buffer - An element क्रम a port device fअगरo buffer list.
 */

काष्ठा list_buffer अणु
	काष्ठा list_head link;
	स्थिर अचिन्हित अक्षर *head;
	स्थिर अचिन्हित अक्षर *tail;
	अचिन्हित दीर्घ dbg_number;
	अचिन्हित अक्षर data[];
पूर्ण;

/**
 * ps3_vuart_ग_लिखो - the entry poपूर्णांक क्रम writing data to a port
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 *
 * If the port is idle on entry as much of the incoming data is written to
 * the port as the port will accept.  Otherwise a list buffer is created
 * and any remaning incoming data is copied to that buffer.  The buffer is
 * then enqueued क्रम transmision via the transmit पूर्णांकerrupt.
 */

पूर्णांक ps3_vuart_ग_लिखो(काष्ठा ps3_प्रणाली_bus_device *dev, स्थिर व्योम *buf,
	अचिन्हित पूर्णांक bytes)
अणु
	अटल अचिन्हित दीर्घ dbg_number;
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा list_buffer *lb;

	dev_dbg(&dev->core, "%s:%d: %u(%xh) bytes\n", __func__, __LINE__,
		bytes, bytes);

	spin_lock_irqsave(&priv->tx_list.lock, flags);

	अगर (list_empty(&priv->tx_list.head)) अणु
		u64 bytes_written;

		result = ps3_vuart_raw_ग_लिखो(dev, buf, bytes, &bytes_written);

		spin_unlock_irqrestore(&priv->tx_list.lock, flags);

		अगर (result) अणु
			dev_dbg(&dev->core,
				"%s:%d: ps3_vuart_raw_write failed\n",
				__func__, __LINE__);
			वापस result;
		पूर्ण

		अगर (bytes_written == bytes) अणु
			dev_dbg(&dev->core, "%s:%d: wrote %xh bytes\n",
				__func__, __LINE__, bytes);
			वापस 0;
		पूर्ण

		bytes -= bytes_written;
		buf += bytes_written;
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&priv->tx_list.lock, flags);

	lb = kदो_स्मृति(माप(काष्ठा list_buffer) + bytes, GFP_KERNEL);

	अगर (!lb)
		वापस -ENOMEM;

	स_नकल(lb->data, buf, bytes);
	lb->head = lb->data;
	lb->tail = lb->data + bytes;
	lb->dbg_number = ++dbg_number;

	spin_lock_irqsave(&priv->tx_list.lock, flags);
	list_add_tail(&lb->link, &priv->tx_list.head);
	ps3_vuart_enable_पूर्णांकerrupt_tx(dev);
	spin_unlock_irqrestore(&priv->tx_list.lock, flags);

	dev_dbg(&dev->core, "%s:%d: queued buf_%lu, %xh bytes\n",
		__func__, __LINE__, lb->dbg_number, bytes);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_ग_लिखो);

/**
 * ps3_vuart_queue_rx_bytes - Queue रुकोing bytes पूर्णांकo the buffer list.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 * @bytes_queued: Number of bytes queued to the buffer list.
 *
 * Must be called with priv->rx_list.lock held.
 */

अटल पूर्णांक ps3_vuart_queue_rx_bytes(काष्ठा ps3_प्रणाली_bus_device *dev,
	u64 *bytes_queued)
अणु
	अटल अचिन्हित दीर्घ dbg_number;
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	काष्ठा list_buffer *lb;
	u64 bytes;

	*bytes_queued = 0;

	result = ps3_vuart_get_rx_bytes_रुकोing(dev, &bytes);
	BUG_ON(result);

	अगर (result)
		वापस -EIO;

	अगर (!bytes)
		वापस 0;

	/* Add some extra space क्रम recently arrived data. */

	bytes += 128;

	lb = kदो_स्मृति(माप(काष्ठा list_buffer) + bytes, GFP_ATOMIC);

	अगर (!lb)
		वापस -ENOMEM;

	ps3_vuart_raw_पढ़ो(dev, lb->data, bytes, &bytes);

	lb->head = lb->data;
	lb->tail = lb->data + bytes;
	lb->dbg_number = ++dbg_number;

	list_add_tail(&lb->link, &priv->rx_list.head);
	priv->rx_list.bytes_held += bytes;

	dev_dbg(&dev->core, "%s:%d: buf_%lu: queued %llxh bytes\n",
		__func__, __LINE__, lb->dbg_number, bytes);

	*bytes_queued = bytes;

	वापस 0;
पूर्ण

/**
 * ps3_vuart_पढ़ो - The entry poपूर्णांक क्रम पढ़ोing data from a port.
 *
 * Queue data रुकोing at the port, and अगर enough bytes to satisfy the request
 * are held in the buffer list those bytes are dequeued and copied to the
 * caller's buffer.  Emptied list buffers are retiered.  If the request cannot
 * be statअगरied by bytes held in the list buffers -EAGAIN is वापसed.
 */

पूर्णांक ps3_vuart_पढ़ो(काष्ठा ps3_प्रणाली_bus_device *dev, व्योम *buf,
	अचिन्हित पूर्णांक bytes)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा list_buffer *lb, *n;
	अचिन्हित दीर्घ bytes_पढ़ो;

	dev_dbg(&dev->core, "%s:%d: %u(%xh) bytes\n", __func__, __LINE__,
		bytes, bytes);

	spin_lock_irqsave(&priv->rx_list.lock, flags);

	/* Queue rx bytes here क्रम polled पढ़ोs. */

	जबतक (priv->rx_list.bytes_held < bytes) अणु
		u64 पंचांगp;

		result = ps3_vuart_queue_rx_bytes(dev, &पंचांगp);
		अगर (result || !पंचांगp) अणु
			dev_dbg(&dev->core, "%s:%d: starved for %lxh bytes\n",
				__func__, __LINE__,
				bytes - priv->rx_list.bytes_held);
			spin_unlock_irqrestore(&priv->rx_list.lock, flags);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(lb, n, &priv->rx_list.head, link) अणु
		bytes_पढ़ो = min((अचिन्हित पूर्णांक)(lb->tail - lb->head), bytes);

		स_नकल(buf, lb->head, bytes_पढ़ो);
		buf += bytes_पढ़ो;
		bytes -= bytes_पढ़ो;
		priv->rx_list.bytes_held -= bytes_पढ़ो;

		अगर (bytes_पढ़ो < lb->tail - lb->head) अणु
			lb->head += bytes_पढ़ो;
			dev_dbg(&dev->core, "%s:%d: buf_%lu: dequeued %lxh "
				"bytes\n", __func__, __LINE__, lb->dbg_number,
				bytes_पढ़ो);
			spin_unlock_irqrestore(&priv->rx_list.lock, flags);
			वापस 0;
		पूर्ण

		dev_dbg(&dev->core, "%s:%d: buf_%lu: free, dequeued %lxh "
			"bytes\n", __func__, __LINE__, lb->dbg_number,
			bytes_पढ़ो);

		list_del(&lb->link);
		kमुक्त(lb);
	पूर्ण

	spin_unlock_irqrestore(&priv->rx_list.lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_पढ़ो);

/**
 * ps3_vuart_work - Asynchronous पढ़ो handler.
 */

अटल व्योम ps3_vuart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev =
		ps3_vuart_work_to_प्रणाली_bus_dev(work);
	काष्ठा ps3_vuart_port_driver *drv =
		ps3_प्रणाली_bus_dev_to_vuart_drv(dev);

	BUG_ON(!drv);
	drv->work(dev);
पूर्ण

पूर्णांक ps3_vuart_पढ़ो_async(काष्ठा ps3_प्रणाली_bus_device *dev, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (priv->rx_list.work.trigger) अणु
		dev_dbg(&dev->core, "%s:%d: warning, multiple calls\n",
			__func__, __LINE__);
		वापस -EAGAIN;
	पूर्ण

	BUG_ON(!bytes);

	spin_lock_irqsave(&priv->rx_list.lock, flags);
	अगर (priv->rx_list.bytes_held >= bytes) अणु
		dev_dbg(&dev->core, "%s:%d: schedule_work %xh bytes\n",
			__func__, __LINE__, bytes);
		schedule_work(&priv->rx_list.work.work);
		spin_unlock_irqrestore(&priv->rx_list.lock, flags);
		वापस 0;
	पूर्ण

	priv->rx_list.work.trigger = bytes;
	spin_unlock_irqrestore(&priv->rx_list.lock, flags);

	dev_dbg(&dev->core, "%s:%d: waiting for %u(%xh) bytes\n", __func__,
		__LINE__, bytes, bytes);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_पढ़ो_async);

व्योम ps3_vuart_cancel_async(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	to_port_priv(dev)->rx_list.work.trigger = 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_cancel_async);

/**
 * ps3_vuart_handle_पूर्णांकerrupt_tx - third stage transmit पूर्णांकerrupt handler
 *
 * Services the transmit पूर्णांकerrupt क्रम the port.  Writes as much data from the
 * buffer list as the port will accept.  Retires any emptied list buffers and
 * adjusts the final list buffer state क्रम a partial ग_लिखो.
 */

अटल पूर्णांक ps3_vuart_handle_पूर्णांकerrupt_tx(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result = 0;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा list_buffer *lb, *n;
	अचिन्हित दीर्घ bytes_total = 0;

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	spin_lock_irqsave(&priv->tx_list.lock, flags);

	list_क्रम_each_entry_safe(lb, n, &priv->tx_list.head, link) अणु

		u64 bytes_written;

		result = ps3_vuart_raw_ग_लिखो(dev, lb->head, lb->tail - lb->head,
			&bytes_written);

		अगर (result) अणु
			dev_dbg(&dev->core,
				"%s:%d: ps3_vuart_raw_write failed\n",
				__func__, __LINE__);
			अवरोध;
		पूर्ण

		bytes_total += bytes_written;

		अगर (bytes_written < lb->tail - lb->head) अणु
			lb->head += bytes_written;
			dev_dbg(&dev->core,
				"%s:%d cleared buf_%lu, %llxh bytes\n",
				__func__, __LINE__, lb->dbg_number,
				bytes_written);
			जाओ port_full;
		पूर्ण

		dev_dbg(&dev->core, "%s:%d free buf_%lu\n", __func__, __LINE__,
			lb->dbg_number);

		list_del(&lb->link);
		kमुक्त(lb);
	पूर्ण

	ps3_vuart_disable_पूर्णांकerrupt_tx(dev);
port_full:
	spin_unlock_irqrestore(&priv->tx_list.lock, flags);
	dev_dbg(&dev->core, "%s:%d wrote %lxh bytes total\n",
		__func__, __LINE__, bytes_total);
	वापस result;
पूर्ण

/**
 * ps3_vuart_handle_पूर्णांकerrupt_rx - third stage receive पूर्णांकerrupt handler
 *
 * Services the receive पूर्णांकerrupt क्रम the port.  Creates a list buffer and
 * copies all रुकोing port data to that buffer and enqueues the buffer in the
 * buffer list.  Buffer list data is dequeued via ps3_vuart_पढ़ो.
 */

अटल पूर्णांक ps3_vuart_handle_पूर्णांकerrupt_rx(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	अचिन्हित दीर्घ flags;
	u64 bytes;

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	spin_lock_irqsave(&priv->rx_list.lock, flags);
	result = ps3_vuart_queue_rx_bytes(dev, &bytes);

	अगर (result) अणु
		spin_unlock_irqrestore(&priv->rx_list.lock, flags);
		वापस result;
	पूर्ण

	अगर (priv->rx_list.work.trigger && priv->rx_list.bytes_held
		>= priv->rx_list.work.trigger) अणु
		dev_dbg(&dev->core, "%s:%d: schedule_work %lxh bytes\n",
			__func__, __LINE__, priv->rx_list.work.trigger);
		priv->rx_list.work.trigger = 0;
		schedule_work(&priv->rx_list.work.work);
	पूर्ण

	spin_unlock_irqrestore(&priv->rx_list.lock, flags);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_vuart_handle_पूर्णांकerrupt_disconnect(
	काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);
	BUG_ON("no support");
	वापस -1;
पूर्ण

/**
 * ps3_vuart_handle_port_पूर्णांकerrupt - second stage पूर्णांकerrupt handler
 *
 * Services any pending पूर्णांकerrupt types क्रम the port.  Passes control to the
 * third stage type specअगरic पूर्णांकerrupt handler.  Returns control to the first
 * stage handler after one iteration.
 */

अटल पूर्णांक ps3_vuart_handle_port_पूर्णांकerrupt(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	अचिन्हित दीर्घ status;

	result = ps3_vuart_get_पूर्णांकerrupt_status(dev, &status);

	अगर (result)
		वापस result;

	dev_dbg(&dev->core, "%s:%d: status: %lxh\n", __func__, __LINE__,
		status);

	अगर (status & INTERRUPT_MASK_DISCONNECT) अणु
		priv->stats.disconnect_पूर्णांकerrupts++;
		result = ps3_vuart_handle_पूर्णांकerrupt_disconnect(dev);
		अगर (result)
			ps3_vuart_disable_पूर्णांकerrupt_disconnect(dev);
	पूर्ण

	अगर (status & INTERRUPT_MASK_TX) अणु
		priv->stats.tx_पूर्णांकerrupts++;
		result = ps3_vuart_handle_पूर्णांकerrupt_tx(dev);
		अगर (result)
			ps3_vuart_disable_पूर्णांकerrupt_tx(dev);
	पूर्ण

	अगर (status & INTERRUPT_MASK_RX) अणु
		priv->stats.rx_पूर्णांकerrupts++;
		result = ps3_vuart_handle_पूर्णांकerrupt_rx(dev);
		अगर (result)
			ps3_vuart_disable_पूर्णांकerrupt_rx(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा vuart_bus_priv अणु
	काष्ठा ports_bmp *bmp;
	अचिन्हित पूर्णांक virq;
	काष्ठा mutex probe_mutex;
	पूर्णांक use_count;
	काष्ठा ps3_प्रणाली_bus_device *devices[PORT_COUNT];
पूर्ण vuart_bus_priv;

/**
 * ps3_vuart_irq_handler - first stage पूर्णांकerrupt handler
 *
 * Loops finding any पूर्णांकerrupting port and its associated instance data.
 * Passes control to the second stage port specअगरic पूर्णांकerrupt handler.  Loops
 * until all outstanding पूर्णांकerrupts are serviced.
 */

अटल irqवापस_t ps3_vuart_irq_handler(पूर्णांक irq, व्योम *_निजी)
अणु
	काष्ठा vuart_bus_priv *bus_priv = _निजी;

	BUG_ON(!bus_priv);

	जबतक (1) अणु
		अचिन्हित पूर्णांक port;

		dump_ports_bmp(bus_priv->bmp);

		port = (BITS_PER_LONG - 1) - __ilog2(bus_priv->bmp->status);

		अगर (port == BITS_PER_LONG)
			अवरोध;

		BUG_ON(port >= PORT_COUNT);
		BUG_ON(!bus_priv->devices[port]);

		ps3_vuart_handle_port_पूर्णांकerrupt(bus_priv->devices[port]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ps3_vuart_bus_पूर्णांकerrupt_get(व्योम)
अणु
	पूर्णांक result;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	vuart_bus_priv.use_count++;

	BUG_ON(vuart_bus_priv.use_count > 2);

	अगर (vuart_bus_priv.use_count != 1)
		वापस 0;

	BUG_ON(vuart_bus_priv.bmp);

	vuart_bus_priv.bmp = kzalloc(माप(काष्ठा ports_bmp), GFP_KERNEL);

	अगर (!vuart_bus_priv.bmp) अणु
		result = -ENOMEM;
		जाओ fail_bmp_दो_स्मृति;
	पूर्ण

	result = ps3_vuart_irq_setup(PS3_BINDING_CPU_ANY, vuart_bus_priv.bmp,
		&vuart_bus_priv.virq);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_vuart_irq_setup failed (%d)\n",
			__func__, __LINE__, result);
		result = -EPERM;
		जाओ fail_alloc_irq;
	पूर्ण

	result = request_irq(vuart_bus_priv.virq, ps3_vuart_irq_handler,
		0, "vuart", &vuart_bus_priv);

	अगर (result) अणु
		pr_debug("%s:%d: request_irq failed (%d)\n",
			__func__, __LINE__, result);
		जाओ fail_request_irq;
	पूर्ण

	pr_debug(" <- %s:%d: ok\n", __func__, __LINE__);
	वापस result;

fail_request_irq:
	ps3_vuart_irq_destroy(vuart_bus_priv.virq);
	vuart_bus_priv.virq = 0;
fail_alloc_irq:
	kमुक्त(vuart_bus_priv.bmp);
	vuart_bus_priv.bmp = शून्य;
fail_bmp_दो_स्मृति:
	vuart_bus_priv.use_count--;
	pr_debug(" <- %s:%d: failed\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_vuart_bus_पूर्णांकerrupt_put(व्योम)
अणु
	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	vuart_bus_priv.use_count--;

	BUG_ON(vuart_bus_priv.use_count < 0);

	अगर (vuart_bus_priv.use_count != 0)
		वापस 0;

	मुक्त_irq(vuart_bus_priv.virq, &vuart_bus_priv);

	ps3_vuart_irq_destroy(vuart_bus_priv.virq);
	vuart_bus_priv.virq = 0;

	kमुक्त(vuart_bus_priv.bmp);
	vuart_bus_priv.bmp = शून्य;

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस 0;
पूर्ण

अटल पूर्णांक ps3_vuart_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा ps3_vuart_port_driver *drv;
	काष्ठा ps3_vuart_port_priv *priv = शून्य;

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	drv = ps3_प्रणाली_bus_dev_to_vuart_drv(dev);
	BUG_ON(!drv);

	dev_dbg(&dev->core, "%s:%d: (%s)\n", __func__, __LINE__,
		drv->core.core.name);

	अगर (dev->port_number >= PORT_COUNT) अणु
		BUG();
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&vuart_bus_priv.probe_mutex);

	result = ps3_vuart_bus_पूर्णांकerrupt_get();

	अगर (result)
		जाओ fail_setup_पूर्णांकerrupt;

	अगर (vuart_bus_priv.devices[dev->port_number]) अणु
		dev_dbg(&dev->core, "%s:%d: port busy (%d)\n", __func__,
			__LINE__, dev->port_number);
		result = -EBUSY;
		जाओ fail_busy;
	पूर्ण

	vuart_bus_priv.devices[dev->port_number] = dev;

	/* Setup dev->driver_priv. */

	dev->driver_priv = kzalloc(माप(काष्ठा ps3_vuart_port_priv),
		GFP_KERNEL);

	अगर (!dev->driver_priv) अणु
		result = -ENOMEM;
		जाओ fail_dev_दो_स्मृति;
	पूर्ण

	priv = to_port_priv(dev);

	INIT_LIST_HEAD(&priv->tx_list.head);
	spin_lock_init(&priv->tx_list.lock);

	INIT_LIST_HEAD(&priv->rx_list.head);
	spin_lock_init(&priv->rx_list.lock);

	INIT_WORK(&priv->rx_list.work.work, ps3_vuart_work);
	priv->rx_list.work.trigger = 0;
	priv->rx_list.work.dev = dev;

	/* clear stale pending पूर्णांकerrupts */

	ps3_vuart_clear_rx_bytes(dev, 0);

	ps3_vuart_set_पूर्णांकerrupt_mask(dev, INTERRUPT_MASK_RX);

	ps3_vuart_set_triggers(dev, 1, 1);

	अगर (drv->probe)
		result = drv->probe(dev);
	अन्यथा अणु
		result = 0;
		dev_info(&dev->core, "%s:%d: no probe method\n", __func__,
			__LINE__);
	पूर्ण

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: drv->probe failed\n",
			__func__, __LINE__);
		जाओ fail_probe;
	पूर्ण

	mutex_unlock(&vuart_bus_priv.probe_mutex);

	वापस result;

fail_probe:
	ps3_vuart_set_पूर्णांकerrupt_mask(dev, 0);
	kमुक्त(dev->driver_priv);
	dev->driver_priv = शून्य;
fail_dev_दो_स्मृति:
	vuart_bus_priv.devices[dev->port_number] = शून्य;
fail_busy:
	ps3_vuart_bus_पूर्णांकerrupt_put();
fail_setup_पूर्णांकerrupt:
	mutex_unlock(&vuart_bus_priv.probe_mutex);
	dev_dbg(&dev->core, "%s:%d: failed\n", __func__, __LINE__);
	वापस result;
पूर्ण

/**
 * ps3_vuart_cleanup - common cleanup helper.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 *
 * Cleans पूर्णांकerrupts and HV resources.  Must be called with
 * vuart_bus_priv.probe_mutex held.  Used by ps3_vuart_हटाओ and
 * ps3_vuart_shutकरोwn.  After this call, polled पढ़ोing will still work.
 */

अटल पूर्णांक ps3_vuart_cleanup(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	ps3_vuart_cancel_async(dev);
	ps3_vuart_set_पूर्णांकerrupt_mask(dev, 0);
	ps3_vuart_bus_पूर्णांकerrupt_put();
	वापस 0;
पूर्ण

/**
 * ps3_vuart_हटाओ - Completely clean the device instance.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 *
 * Cleans all memory, पूर्णांकerrupts and HV resources.  After this call the
 * device can no दीर्घer be used.
 */

अटल व्योम ps3_vuart_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_priv *priv = to_port_priv(dev);
	काष्ठा ps3_vuart_port_driver *drv;

	BUG_ON(!dev);

	mutex_lock(&vuart_bus_priv.probe_mutex);

	dev_dbg(&dev->core, " -> %s:%d: match_id %d\n", __func__, __LINE__,
		dev->match_id);

	अगर (!dev->core.driver) अणु
		dev_dbg(&dev->core, "%s:%d: no driver bound\n", __func__,
			__LINE__);
		mutex_unlock(&vuart_bus_priv.probe_mutex);
		वापस;
	पूर्ण

	drv = ps3_प्रणाली_bus_dev_to_vuart_drv(dev);

	BUG_ON(!drv);

	अगर (drv->हटाओ) अणु
		drv->हटाओ(dev);
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->core, "%s:%d: no remove method\n", __func__,
		__LINE__);
		BUG();
	पूर्ण

	ps3_vuart_cleanup(dev);

	vuart_bus_priv.devices[dev->port_number] = शून्य;
	kमुक्त(priv);
	priv = शून्य;

	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);
	mutex_unlock(&vuart_bus_priv.probe_mutex);
पूर्ण

/**
 * ps3_vuart_shutकरोwn - Cleans पूर्णांकerrupts and HV resources.
 * @dev: The काष्ठा ps3_प्रणाली_bus_device instance.
 *
 * Cleans पूर्णांकerrupts and HV resources.  After this call the
 * device can still be used in polling mode.  This behavior required
 * by sys-manager to be able to complete the device घातer operation
 * sequence.
 */

अटल व्योम ps3_vuart_shutकरोwn(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_vuart_port_driver *drv;

	BUG_ON(!dev);

	mutex_lock(&vuart_bus_priv.probe_mutex);

	dev_dbg(&dev->core, " -> %s:%d: match_id %d\n", __func__, __LINE__,
		dev->match_id);

	अगर (!dev->core.driver) अणु
		dev_dbg(&dev->core, "%s:%d: no driver bound\n", __func__,
			__LINE__);
		mutex_unlock(&vuart_bus_priv.probe_mutex);
		वापस;
	पूर्ण

	drv = ps3_प्रणाली_bus_dev_to_vuart_drv(dev);

	BUG_ON(!drv);

	अगर (drv->shutकरोwn)
		drv->shutकरोwn(dev);
	अन्यथा अगर (drv->हटाओ) अणु
		dev_dbg(&dev->core, "%s:%d: no shutdown, calling remove\n",
			__func__, __LINE__);
		drv->हटाओ(dev);
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->core, "%s:%d: no shutdown method\n", __func__,
			__LINE__);
		BUG();
	पूर्ण

	ps3_vuart_cleanup(dev);

	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);

	mutex_unlock(&vuart_bus_priv.probe_mutex);
पूर्ण

अटल पूर्णांक __init ps3_vuart_bus_init(व्योम)
अणु
	pr_debug("%s:%d:\n", __func__, __LINE__);

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	mutex_init(&vuart_bus_priv.probe_mutex);

	वापस 0;
पूर्ण

अटल व्योम __निकास ps3_vuart_bus_निकास(व्योम)
अणु
	pr_debug("%s:%d:\n", __func__, __LINE__);
पूर्ण

core_initcall(ps3_vuart_bus_init);
module_निकास(ps3_vuart_bus_निकास);

/**
 * ps3_vuart_port_driver_रेजिस्टर - Add a vuart port device driver.
 */

पूर्णांक ps3_vuart_port_driver_रेजिस्टर(काष्ठा ps3_vuart_port_driver *drv)
अणु
	पूर्णांक result;

	pr_debug("%s:%d: (%s)\n", __func__, __LINE__, drv->core.core.name);

	BUG_ON(!drv->core.match_id);
	BUG_ON(!drv->core.core.name);

	drv->core.probe = ps3_vuart_probe;
	drv->core.हटाओ = ps3_vuart_हटाओ;
	drv->core.shutकरोwn = ps3_vuart_shutकरोwn;

	result = ps3_प्रणाली_bus_driver_रेजिस्टर(&drv->core);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_port_driver_रेजिस्टर);

/**
 * ps3_vuart_port_driver_unरेजिस्टर - Remove a vuart port device driver.
 */

व्योम ps3_vuart_port_driver_unरेजिस्टर(काष्ठा ps3_vuart_port_driver *drv)
अणु
	pr_debug("%s:%d: (%s)\n", __func__, __LINE__, drv->core.core.name);
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&drv->core);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_port_driver_unरेजिस्टर);
