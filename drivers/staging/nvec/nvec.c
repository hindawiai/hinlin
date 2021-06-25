<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVEC: NVIDIA compliant embedded controller पूर्णांकerface
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.lauchpad.net>
 *
 * Authors:  Pierre-Hugues Husson <phhusson@मुक्त.fr>
 *           Ilya Petrov <ilya.muromec@gmail.com>
 *           Marc Dietrich <marvin24@gmx.de>
 *           Julian Andres Klode <jak@jak-linux.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "nvec.h"

#घोषणा I2C_CNFG			0x00
#घोषणा I2C_CNFG_PACKET_MODE_EN		BIT(10)
#घोषणा I2C_CNFG_NEW_MASTER_SFM		BIT(11)
#घोषणा I2C_CNFG_DEBOUNCE_CNT_SHIFT	12

#घोषणा I2C_SL_CNFG		0x20
#घोषणा I2C_SL_NEWSL		BIT(2)
#घोषणा I2C_SL_NACK		BIT(1)
#घोषणा I2C_SL_RESP		BIT(0)
#घोषणा I2C_SL_IRQ		BIT(3)
#घोषणा END_TRANS		BIT(4)
#घोषणा RCVD			BIT(2)
#घोषणा RNW			BIT(1)

#घोषणा I2C_SL_RCVD		0x24
#घोषणा I2C_SL_STATUS		0x28
#घोषणा I2C_SL_ADDR1		0x2c
#घोषणा I2C_SL_ADDR2		0x30
#घोषणा I2C_SL_DELAY_COUNT	0x3c

/**
 * क्रमागत nvec_msg_category - Message categories क्रम nvec_msg_alloc()
 * @NVEC_MSG_RX: The message is an incoming message (from EC)
 * @NVEC_MSG_TX: The message is an outgoing message (to EC)
 */
क्रमागत nvec_msg_category  अणु
	NVEC_MSG_RX,
	NVEC_MSG_TX,
पूर्ण;

क्रमागत nvec_sleep_subcmds अणु
	GLOBAL_EVENTS,
	AP_PWR_DOWN,
	AP_SUSPEND,
पूर्ण;

#घोषणा CNF_EVENT_REPORTING 0x01
#घोषणा GET_FIRMWARE_VERSION 0x15
#घोषणा LID_SWITCH BIT(1)
#घोषणा PWR_BUTTON BIT(15)

अटल काष्ठा nvec_chip *nvec_घातer_handle;

अटल स्थिर काष्ठा mfd_cell nvec_devices[] = अणु
	अणु
		.name = "nvec-kbd",
	पूर्ण,
	अणु
		.name = "nvec-mouse",
	पूर्ण,
	अणु
		.name = "nvec-power",
		.id = 0,
	पूर्ण,
	अणु
		.name = "nvec-power",
		.id = 1,
	पूर्ण,
	अणु
		.name = "nvec-paz00",
	पूर्ण,
पूर्ण;

/**
 * nvec_रेजिस्टर_notअगरier - Register a notअगरier with nvec
 * @nvec: A &काष्ठा nvec_chip
 * @nb: The notअगरier block to रेजिस्टर
 *
 * Registers a notअगरier with @nvec. The notअगरier will be added to an atomic
 * notअगरier chain that is called क्रम all received messages except those that
 * correspond to a request initiated by nvec_ग_लिखो_sync().
 */
पूर्णांक nvec_रेजिस्टर_notअगरier(काष्ठा nvec_chip *nvec, काष्ठा notअगरier_block *nb,
			   अचिन्हित पूर्णांक events)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&nvec->notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(nvec_रेजिस्टर_notअगरier);

/**
 * nvec_unरेजिस्टर_notअगरier - Unरेजिस्टर a notअगरier with nvec
 * @nvec: A &काष्ठा nvec_chip
 * @nb: The notअगरier block to unरेजिस्टर
 *
 * Unरेजिस्टरs a notअगरier with @nvec. The notअगरier will be हटाओd from the
 * atomic notअगरier chain.
 */
पूर्णांक nvec_unरेजिस्टर_notअगरier(काष्ठा nvec_chip *nvec, काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&nvec->notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(nvec_unरेजिस्टर_notअगरier);

/**
 * nvec_status_notअगरier - The final notअगरier
 *
 * Prपूर्णांकs a message about control events not handled in the notअगरier
 * chain.
 */
अटल पूर्णांक nvec_status_notअगरier(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	काष्ठा nvec_chip *nvec = container_of(nb, काष्ठा nvec_chip,
						nvec_status_notअगरier);
	अचिन्हित अक्षर *msg = data;

	अगर (event_type != NVEC_CNTL)
		वापस NOTIFY_DONE;

	dev_warn(nvec->dev, "unhandled msg type %ld\n", event_type);
	prपूर्णांक_hex_dump(KERN_WARNING, "payload: ", DUMP_PREFIX_NONE, 16, 1,
		       msg, msg[1] + 2, true);

	वापस NOTIFY_OK;
पूर्ण

/**
 * nvec_msg_alloc:
 * @nvec: A &काष्ठा nvec_chip
 * @category: Pool category, see &क्रमागत nvec_msg_category
 *
 * Allocate a single &काष्ठा nvec_msg object from the message pool of
 * @nvec. The result shall be passed to nvec_msg_मुक्त() अगर no दीर्घer
 * used.
 *
 * Outgoing messages are placed in the upper 75% of the pool, keeping the
 * lower 25% available क्रम RX buffers only. The reason is to prevent a
 * situation where all buffers are full and a message is thus endlessly
 * retried because the response could never be processed.
 */
अटल काष्ठा nvec_msg *nvec_msg_alloc(काष्ठा nvec_chip *nvec,
				       क्रमागत nvec_msg_category category)
अणु
	पूर्णांक i = (category == NVEC_MSG_TX) ? (NVEC_POOL_SIZE / 4) : 0;

	क्रम (; i < NVEC_POOL_SIZE; i++) अणु
		अगर (atomic_xchg(&nvec->msg_pool[i].used, 1) == 0) अणु
			dev_vdbg(nvec->dev, "INFO: Allocate %i\n", i);
			वापस &nvec->msg_pool[i];
		पूर्ण
	पूर्ण

	dev_err(nvec->dev, "could not allocate %s buffer\n",
		(category == NVEC_MSG_TX) ? "TX" : "RX");

	वापस शून्य;
पूर्ण

/**
 * nvec_msg_मुक्त:
 * @nvec: A &काष्ठा nvec_chip
 * @msg:  A message (must be allocated by nvec_msg_alloc() and beदीर्घ to @nvec)
 *
 * Free the given message
 */
व्योम nvec_msg_मुक्त(काष्ठा nvec_chip *nvec, काष्ठा nvec_msg *msg)
अणु
	अगर (msg != &nvec->tx_scratch)
		dev_vdbg(nvec->dev, "INFO: Free %ti\n", msg - nvec->msg_pool);
	atomic_set(&msg->used, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nvec_msg_मुक्त);

/**
 * nvec_msg_is_event - Return %true अगर @msg is an event
 * @msg: A message
 */
अटल bool nvec_msg_is_event(काष्ठा nvec_msg *msg)
अणु
	वापस msg->data[0] >> 7;
पूर्ण

/**
 * nvec_msg_size - Get the size of a message
 * @msg: The message to get the size क्रम
 *
 * This only works क्रम received messages, not क्रम outgoing messages.
 */
अटल माप_प्रकार nvec_msg_size(काष्ठा nvec_msg *msg)
अणु
	bool is_event = nvec_msg_is_event(msg);
	पूर्णांक event_length = (msg->data[0] & 0x60) >> 5;

	/* क्रम variable size, payload size in byte 1 + count (1) + cmd (1) */
	अगर (!is_event || event_length == NVEC_VAR_SIZE)
		वापस (msg->pos || msg->size) ? (msg->data[1] + 2) : 0;
	अन्यथा अगर (event_length == NVEC_2BYTES)
		वापस 2;
	अन्यथा अगर (event_length == NVEC_3BYTES)
		वापस 3;
	वापस 0;
पूर्ण

/**
 * nvec_gpio_set_value - Set the GPIO value
 * @nvec: A &काष्ठा nvec_chip
 * @value: The value to ग_लिखो (0 or 1)
 *
 * Like gpio_set_value(), but generating debugging inक्रमmation
 */
अटल व्योम nvec_gpio_set_value(काष्ठा nvec_chip *nvec, पूर्णांक value)
अणु
	dev_dbg(nvec->dev, "GPIO changed from %u to %u\n",
		gpiod_get_value(nvec->gpiod), value);
	gpiod_set_value(nvec->gpiod, value);
पूर्ण

/**
 * nvec_ग_लिखो_async - Asynchronously ग_लिखो a message to NVEC
 * @nvec: An nvec_chip instance
 * @data: The message data, starting with the request type
 * @size: The size of @data
 *
 * Queue a single message to be transferred to the embedded controller
 * and वापस immediately.
 *
 * Returns: 0 on success, a negative error code on failure. If a failure
 * occurred, the nvec driver may prपूर्णांक an error.
 */
पूर्णांक nvec_ग_लिखो_async(काष्ठा nvec_chip *nvec, स्थिर अचिन्हित अक्षर *data,
		     लघु size)
अणु
	काष्ठा nvec_msg *msg;
	अचिन्हित दीर्घ flags;

	msg = nvec_msg_alloc(nvec, NVEC_MSG_TX);

	अगर (!msg)
		वापस -ENOMEM;

	msg->data[0] = size;
	स_नकल(msg->data + 1, data, size);
	msg->size = size + 1;

	spin_lock_irqsave(&nvec->tx_lock, flags);
	list_add_tail(&msg->node, &nvec->tx_data);
	spin_unlock_irqrestore(&nvec->tx_lock, flags);

	schedule_work(&nvec->tx_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nvec_ग_लिखो_async);

/**
 * nvec_ग_लिखो_sync - Write a message to nvec and पढ़ो the response
 * @nvec: An &काष्ठा nvec_chip
 * @data: The data to ग_लिखो
 * @size: The size of @data
 * @msg:  The response message received
 *
 * This is similar to nvec_ग_लिखो_async(), but रुकोs क्रम the
 * request to be answered beक्रमe वापसing. This function
 * uses a mutex and can thus not be called from e.g.
 * पूर्णांकerrupt handlers.
 *
 * Returns: 0 on success, a negative error code on failure.
 * The response message is वापसed in @msg. Shall be मुक्तd
 * with nvec_msg_मुक्त() once no दीर्घer used.
 *
 */
पूर्णांक nvec_ग_लिखो_sync(काष्ठा nvec_chip *nvec,
		    स्थिर अचिन्हित अक्षर *data, लघु size,
		    काष्ठा nvec_msg **msg)
अणु
	mutex_lock(&nvec->sync_ग_लिखो_mutex);

	*msg = शून्य;
	nvec->sync_ग_लिखो_pending = (data[1] << 8) + data[0];

	अगर (nvec_ग_लिखो_async(nvec, data, size) < 0) अणु
		mutex_unlock(&nvec->sync_ग_लिखो_mutex);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(nvec->dev, "nvec_sync_write: 0x%04x\n",
		nvec->sync_ग_लिखो_pending);
	अगर (!(रुको_क्रम_completion_समयout(&nvec->sync_ग_लिखो,
					  msecs_to_jअगरfies(2000)))) अणु
		dev_warn(nvec->dev,
			 "timeout waiting for sync write to complete\n");
		mutex_unlock(&nvec->sync_ग_लिखो_mutex);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(nvec->dev, "nvec_sync_write: pong!\n");

	*msg = nvec->last_sync_msg;

	mutex_unlock(&nvec->sync_ग_लिखो_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nvec_ग_लिखो_sync);

/**
 * nvec_toggle_global_events - enables or disables global event reporting
 * @nvec: nvec handle
 * @state: true क्रम enable, false क्रम disable
 *
 * This चयनes on/off global event reports by the embedded controller.
 */
अटल व्योम nvec_toggle_global_events(काष्ठा nvec_chip *nvec, bool state)
अणु
	अचिन्हित अक्षर global_events[] = अणु NVEC_SLEEP, GLOBAL_EVENTS, state पूर्ण;

	nvec_ग_लिखो_async(nvec, global_events, 3);
पूर्ण

/**
 * nvec_event_mask - fill the command string with event bitfield
 * ev: poपूर्णांकs to event command string
 * mask: bit to insert पूर्णांकo the event mask
 *
 * Configure event command expects a 32 bit bitfield which describes
 * which events to enable. The bitfield has the following काष्ठाure
 * (from highest byte to lowest):
 *	प्रणाली state bits 7-0
 *	प्रणाली state bits 15-8
 *	oem प्रणाली state bits 7-0
 *	oem प्रणाली state bits 15-8
 */
अटल व्योम nvec_event_mask(अक्षर *ev, u32 mask)
अणु
	ev[3] = mask >> 16 & 0xff;
	ev[4] = mask >> 24 & 0xff;
	ev[5] = mask >> 0  & 0xff;
	ev[6] = mask >> 8  & 0xff;
पूर्ण

/**
 * nvec_request_master - Process outgoing messages
 * @work: A &काष्ठा work_काष्ठा (the tx_worker member of &काष्ठा nvec_chip)
 *
 * Processes all outgoing requests by sending the request and aरुकोing the
 * response, then continuing with the next request. Once a request has a
 * matching response, it will be मुक्तd and हटाओd from the list.
 */
अटल व्योम nvec_request_master(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvec_chip *nvec = container_of(work, काष्ठा nvec_chip, tx_work);
	अचिन्हित दीर्घ flags;
	दीर्घ err;
	काष्ठा nvec_msg *msg;

	spin_lock_irqsave(&nvec->tx_lock, flags);
	जबतक (!list_empty(&nvec->tx_data)) अणु
		msg = list_first_entry(&nvec->tx_data, काष्ठा nvec_msg, node);
		spin_unlock_irqrestore(&nvec->tx_lock, flags);
		nvec_gpio_set_value(nvec, 0);
		err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&nvec->ec_transfer, msecs_to_jअगरfies(5000));

		अगर (err == 0) अणु
			dev_warn(nvec->dev, "timeout waiting for ec transfer\n");
			nvec_gpio_set_value(nvec, 1);
			msg->pos = 0;
		पूर्ण

		spin_lock_irqsave(&nvec->tx_lock, flags);

		अगर (err > 0) अणु
			list_del_init(&msg->node);
			nvec_msg_मुक्त(nvec, msg);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&nvec->tx_lock, flags);
पूर्ण

/**
 * parse_msg - Prपूर्णांक some inक्रमmation and call the notअगरiers on an RX message
 * @nvec: A &काष्ठा nvec_chip
 * @msg: A message received by @nvec
 *
 * Paarse some pieces of the message and then call the chain of notअगरiers
 * रेजिस्टरed via nvec_रेजिस्टर_notअगरier.
 */
अटल पूर्णांक parse_msg(काष्ठा nvec_chip *nvec, काष्ठा nvec_msg *msg)
अणु
	अगर ((msg->data[0] & 1 << 7) == 0 && msg->data[3]) अणु
		dev_err(nvec->dev, "ec responded %*ph\n", 4, msg->data);
		वापस -EINVAL;
	पूर्ण

	अगर ((msg->data[0] >> 7) == 1 && (msg->data[0] & 0x0f) == 5)
		prपूर्णांक_hex_dump(KERN_WARNING, "ec system event ",
			       DUMP_PREFIX_NONE, 16, 1, msg->data,
			       msg->data[1] + 2, true);

	atomic_notअगरier_call_chain(&nvec->notअगरier_list, msg->data[0] & 0x8f,
				   msg->data);

	वापस 0;
पूर्ण

/**
 * nvec_dispatch - Process messages received from the EC
 * @work: A &काष्ठा work_काष्ठा (the tx_worker member of &काष्ठा nvec_chip)
 *
 * Process messages previously received from the EC and put पूर्णांकo the RX
 * queue of the &काष्ठा nvec_chip instance associated with @work.
 */
अटल व्योम nvec_dispatch(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvec_chip *nvec = container_of(work, काष्ठा nvec_chip, rx_work);
	अचिन्हित दीर्घ flags;
	काष्ठा nvec_msg *msg;

	spin_lock_irqsave(&nvec->rx_lock, flags);
	जबतक (!list_empty(&nvec->rx_data)) अणु
		msg = list_first_entry(&nvec->rx_data, काष्ठा nvec_msg, node);
		list_del_init(&msg->node);
		spin_unlock_irqrestore(&nvec->rx_lock, flags);

		अगर (nvec->sync_ग_लिखो_pending ==
		      (msg->data[2] << 8) + msg->data[0]) अणु
			dev_dbg(nvec->dev, "sync write completed!\n");
			nvec->sync_ग_लिखो_pending = 0;
			nvec->last_sync_msg = msg;
			complete(&nvec->sync_ग_लिखो);
		पूर्ण अन्यथा अणु
			parse_msg(nvec, msg);
			nvec_msg_मुक्त(nvec, msg);
		पूर्ण
		spin_lock_irqsave(&nvec->rx_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&nvec->rx_lock, flags);
पूर्ण

/**
 * nvec_tx_completed - Complete the current transfer
 * @nvec: A &काष्ठा nvec_chip
 *
 * This is called when we have received an END_TRANS on a TX transfer.
 */
अटल व्योम nvec_tx_completed(काष्ठा nvec_chip *nvec)
अणु
	/* We got an END_TRANS, let's skip this, maybe there's an event */
	अगर (nvec->tx->pos != nvec->tx->size) अणु
		dev_err(nvec->dev, "premature END_TRANS, resending\n");
		nvec->tx->pos = 0;
		nvec_gpio_set_value(nvec, 0);
	पूर्ण अन्यथा अणु
		nvec->state = 0;
	पूर्ण
पूर्ण

/**
 * nvec_rx_completed - Complete the current transfer
 * @nvec: A &काष्ठा nvec_chip
 *
 * This is called when we have received an END_TRANS on a RX transfer.
 */
अटल व्योम nvec_rx_completed(काष्ठा nvec_chip *nvec)
अणु
	अगर (nvec->rx->pos != nvec_msg_size(nvec->rx)) अणु
		dev_err(nvec->dev, "RX incomplete: Expected %u bytes, got %u\n",
			(uपूर्णांक)nvec_msg_size(nvec->rx),
			(uपूर्णांक)nvec->rx->pos);

		nvec_msg_मुक्त(nvec, nvec->rx);
		nvec->state = 0;

		/* Battery quirk - Often incomplete, and likes to crash */
		अगर (nvec->rx->data[0] == NVEC_BAT)
			complete(&nvec->ec_transfer);

		वापस;
	पूर्ण

	spin_lock(&nvec->rx_lock);

	/*
	 * Add the received data to the work list and move the ring buffer
	 * poपूर्णांकer to the next entry.
	 */
	list_add_tail(&nvec->rx->node, &nvec->rx_data);

	spin_unlock(&nvec->rx_lock);

	nvec->state = 0;

	अगर (!nvec_msg_is_event(nvec->rx))
		complete(&nvec->ec_transfer);

	schedule_work(&nvec->rx_work);
पूर्ण

/**
 * nvec_invalid_flags - Send an error message about invalid flags and jump
 * @nvec: The nvec device
 * @status: The status flags
 * @reset: Whether we shall jump to state 0.
 */
अटल व्योम nvec_invalid_flags(काष्ठा nvec_chip *nvec, अचिन्हित पूर्णांक status,
			       bool reset)
अणु
	dev_err(nvec->dev, "unexpected status flags 0x%02x during state %i\n",
		status, nvec->state);
	अगर (reset)
		nvec->state = 0;
पूर्ण

/**
 * nvec_tx_set - Set the message to transfer (nvec->tx)
 * @nvec: A &काष्ठा nvec_chip
 *
 * Gets the first entry from the tx_data list of @nvec and sets the
 * tx member to it. If the tx_data list is empty, this uses the
 * tx_scratch message to send a no operation message.
 */
अटल व्योम nvec_tx_set(काष्ठा nvec_chip *nvec)
अणु
	spin_lock(&nvec->tx_lock);
	अगर (list_empty(&nvec->tx_data)) अणु
		dev_err(nvec->dev, "empty tx - sending no-op\n");
		स_नकल(nvec->tx_scratch.data, "\x02\x07\x02", 3);
		nvec->tx_scratch.size = 3;
		nvec->tx_scratch.pos = 0;
		nvec->tx = &nvec->tx_scratch;
		list_add_tail(&nvec->tx->node, &nvec->tx_data);
	पूर्ण अन्यथा अणु
		nvec->tx = list_first_entry(&nvec->tx_data, काष्ठा nvec_msg,
					    node);
		nvec->tx->pos = 0;
	पूर्ण
	spin_unlock(&nvec->tx_lock);

	dev_dbg(nvec->dev, "Sending message of length %u, command 0x%x\n",
		(uपूर्णांक)nvec->tx->size, nvec->tx->data[1]);
पूर्ण

/**
 * nvec_पूर्णांकerrupt - Interrupt handler
 * @irq: The IRQ
 * @dev: The nvec device
 *
 * Interrupt handler that fills our RX buffers and empties our TX
 * buffers. This uses a finite state machine with ridiculous amounts
 * of error checking, in order to be fairly reliable.
 */
अटल irqवापस_t nvec_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक received = 0;
	अचिन्हित अक्षर to_send = 0xff;
	स्थिर अचिन्हित दीर्घ irq_mask = I2C_SL_IRQ | END_TRANS | RCVD | RNW;
	काष्ठा nvec_chip *nvec = dev;
	अचिन्हित पूर्णांक state = nvec->state;

	status = पढ़ोl(nvec->base + I2C_SL_STATUS);

	/* Filter out some errors */
	अगर ((status & irq_mask) == 0 && (status & ~irq_mask) != 0) अणु
		dev_err(nvec->dev, "unexpected irq mask %lx\n", status);
		वापस IRQ_HANDLED;
	पूर्ण
	अगर ((status & I2C_SL_IRQ) == 0) अणु
		dev_err(nvec->dev, "Spurious IRQ\n");
		वापस IRQ_HANDLED;
	पूर्ण

	/* The EC did not request a पढ़ो, so it send us something, पढ़ो it */
	अगर ((status & RNW) == 0) अणु
		received = पढ़ोl(nvec->base + I2C_SL_RCVD);
		अगर (status & RCVD)
			ग_लिखोl(0, nvec->base + I2C_SL_RCVD);
	पूर्ण

	अगर (status == (I2C_SL_IRQ | RCVD))
		nvec->state = 0;

	चयन (nvec->state) अणु
	हाल 0:		/* Verअगरy that its a transfer start, the rest later */
		अगर (status != (I2C_SL_IRQ | RCVD))
			nvec_invalid_flags(nvec, status, false);
		अवरोध;
	हाल 1:		/* command byte */
		अगर (status != I2C_SL_IRQ) अणु
			nvec_invalid_flags(nvec, status, true);
		पूर्ण अन्यथा अणु
			nvec->rx = nvec_msg_alloc(nvec, NVEC_MSG_RX);
			/* Should not happen in a normal world */
			अगर (unlikely(!nvec->rx)) अणु
				nvec->state = 0;
				अवरोध;
			पूर्ण
			nvec->rx->data[0] = received;
			nvec->rx->pos = 1;
			nvec->state = 2;
		पूर्ण
		अवरोध;
	हाल 2:		/* first byte after command */
		अगर (status == (I2C_SL_IRQ | RNW | RCVD)) अणु
			udelay(33);
			अगर (nvec->rx->data[0] != 0x01) अणु
				dev_err(nvec->dev,
					"Read without prior read command\n");
				nvec->state = 0;
				अवरोध;
			पूर्ण
			nvec_msg_मुक्त(nvec, nvec->rx);
			nvec->state = 3;
			nvec_tx_set(nvec);
			to_send = nvec->tx->data[0];
			nvec->tx->pos = 1;
		पूर्ण अन्यथा अगर (status == (I2C_SL_IRQ)) अणु
			nvec->rx->data[1] = received;
			nvec->rx->pos = 2;
			nvec->state = 4;
		पूर्ण अन्यथा अणु
			nvec_invalid_flags(nvec, status, true);
		पूर्ण
		अवरोध;
	हाल 3:		/* EC करोes a block पढ़ो, we transmit data */
		अगर (status & END_TRANS) अणु
			nvec_tx_completed(nvec);
		पूर्ण अन्यथा अगर ((status & RNW) == 0 || (status & RCVD)) अणु
			nvec_invalid_flags(nvec, status, true);
		पूर्ण अन्यथा अगर (nvec->tx && nvec->tx->pos < nvec->tx->size) अणु
			to_send = nvec->tx->data[nvec->tx->pos++];
		पूर्ण अन्यथा अणु
			dev_err(nvec->dev,
				"tx buffer underflow on %p (%u > %u)\n",
				nvec->tx,
				(uपूर्णांक)(nvec->tx ? nvec->tx->pos : 0),
				(uपूर्णांक)(nvec->tx ? nvec->tx->size : 0));
			nvec->state = 0;
		पूर्ण
		अवरोध;
	हाल 4:		/* EC करोes some ग_लिखो, we पढ़ो the data */
		अगर ((status & (END_TRANS | RNW)) == END_TRANS)
			nvec_rx_completed(nvec);
		अन्यथा अगर (status & (RNW | RCVD))
			nvec_invalid_flags(nvec, status, true);
		अन्यथा अगर (nvec->rx && nvec->rx->pos < NVEC_MSG_SIZE)
			nvec->rx->data[nvec->rx->pos++] = received;
		अन्यथा
			dev_err(nvec->dev,
				"RX buffer overflow on %p: Trying to write byte %u of %u\n",
				nvec->rx, nvec->rx ? nvec->rx->pos : 0,
				NVEC_MSG_SIZE);
		अवरोध;
	शेष:
		nvec->state = 0;
	पूर्ण

	/* If we are told that a new transfer starts, verअगरy it */
	अगर ((status & (RCVD | RNW)) == RCVD) अणु
		अगर (received != nvec->i2c_addr)
			dev_err(nvec->dev,
				"received address 0x%02x, expected 0x%02x\n",
				received, nvec->i2c_addr);
		nvec->state = 1;
	पूर्ण

	/* Send data अगर requested, but not on end of transmission */
	अगर ((status & (RNW | END_TRANS)) == RNW)
		ग_लिखोl(to_send, nvec->base + I2C_SL_RCVD);

	/* If we have send the first byte */
	अगर (status == (I2C_SL_IRQ | RNW | RCVD))
		nvec_gpio_set_value(nvec, 1);

	dev_dbg(nvec->dev,
		"Handled: %s 0x%02x, %s 0x%02x in state %u [%s%s%s]\n",
		(status & RNW) == 0 ? "received" : "R=",
		received,
		(status & (RNW | END_TRANS)) ? "sent" : "S=",
		to_send,
		state,
		status & END_TRANS ? " END_TRANS" : "",
		status & RCVD ? " RCVD" : "",
		status & RNW ? " RNW" : "");

	/*
	 * TODO: A correct fix needs to be found क्रम this.
	 *
	 * We experience less incomplete messages with this delay than without
	 * it, but we करोn't know why. Help is appreciated.
	 */
	udelay(100);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tegra_init_i2c_slave(काष्ठा nvec_chip *nvec)
अणु
	u32 val;

	clk_prepare_enable(nvec->i2c_clk);

	reset_control_निश्चित(nvec->rst);
	udelay(2);
	reset_control_deनिश्चित(nvec->rst);

	val = I2C_CNFG_NEW_MASTER_SFM | I2C_CNFG_PACKET_MODE_EN |
	    (0x2 << I2C_CNFG_DEBOUNCE_CNT_SHIFT);
	ग_लिखोl(val, nvec->base + I2C_CNFG);

	clk_set_rate(nvec->i2c_clk, 8 * 80000);

	ग_लिखोl(I2C_SL_NEWSL, nvec->base + I2C_SL_CNFG);
	ग_लिखोl(0x1E, nvec->base + I2C_SL_DELAY_COUNT);

	ग_लिखोl(nvec->i2c_addr >> 1, nvec->base + I2C_SL_ADDR1);
	ग_लिखोl(0, nvec->base + I2C_SL_ADDR2);

	enable_irq(nvec->irq);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम nvec_disable_i2c_slave(काष्ठा nvec_chip *nvec)
अणु
	disable_irq(nvec->irq);
	ग_लिखोl(I2C_SL_NEWSL | I2C_SL_NACK, nvec->base + I2C_SL_CNFG);
	clk_disable_unprepare(nvec->i2c_clk);
पूर्ण
#पूर्ण_अगर

अटल व्योम nvec_घातer_off(व्योम)
अणु
	अक्षर ap_pwr_करोwn[] = अणु NVEC_SLEEP, AP_PWR_DOWN पूर्ण;

	nvec_toggle_global_events(nvec_घातer_handle, false);
	nvec_ग_लिखो_async(nvec_घातer_handle, ap_pwr_करोwn, 2);
पूर्ण

अटल पूर्णांक tegra_nvec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err, ret;
	काष्ठा clk *i2c_clk;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nvec_chip *nvec;
	काष्ठा nvec_msg *msg;
	व्योम __iomem *base;
	अक्षर	get_firmware_version[] = अणु NVEC_CNTL, GET_FIRMWARE_VERSION पूर्ण,
		unmute_speakers[] = अणु NVEC_OEM0, 0x10, 0x59, 0x95 पूर्ण,
		enable_event[7] = अणु NVEC_SYS, CNF_EVENT_REPORTING, true पूर्ण;

	अगर (!dev->of_node) अणु
		dev_err(dev, "must be instantiated using device tree\n");
		वापस -ENODEV;
	पूर्ण

	nvec = devm_kzalloc(dev, माप(काष्ठा nvec_chip), GFP_KERNEL);
	अगर (!nvec)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, nvec);
	nvec->dev = dev;

	अगर (of_property_पढ़ो_u32(dev->of_node, "slave-addr", &nvec->i2c_addr)) अणु
		dev_err(dev, "no i2c address specified");
		वापस -ENODEV;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	nvec->irq = platक्रमm_get_irq(pdev, 0);
	अगर (nvec->irq < 0)
		वापस -ENODEV;

	i2c_clk = devm_clk_get(dev, "div-clk");
	अगर (IS_ERR(i2c_clk)) अणु
		dev_err(dev, "failed to get controller clock\n");
		वापस -ENODEV;
	पूर्ण

	nvec->rst = devm_reset_control_get_exclusive(dev, "i2c");
	अगर (IS_ERR(nvec->rst)) अणु
		dev_err(dev, "failed to get controller reset\n");
		वापस PTR_ERR(nvec->rst);
	पूर्ण

	nvec->base = base;
	nvec->i2c_clk = i2c_clk;
	nvec->rx = &nvec->msg_pool[0];

	ATOMIC_INIT_NOTIFIER_HEAD(&nvec->notअगरier_list);

	init_completion(&nvec->sync_ग_लिखो);
	init_completion(&nvec->ec_transfer);
	mutex_init(&nvec->sync_ग_लिखो_mutex);
	spin_lock_init(&nvec->tx_lock);
	spin_lock_init(&nvec->rx_lock);
	INIT_LIST_HEAD(&nvec->rx_data);
	INIT_LIST_HEAD(&nvec->tx_data);
	INIT_WORK(&nvec->rx_work, nvec_dispatch);
	INIT_WORK(&nvec->tx_work, nvec_request_master);

	nvec->gpiod = devm_gpiod_get(dev, "request", GPIOD_OUT_HIGH);
	अगर (IS_ERR(nvec->gpiod)) अणु
		dev_err(dev, "couldn't request gpio\n");
		वापस PTR_ERR(nvec->gpiod);
	पूर्ण

	err = devm_request_irq(dev, nvec->irq, nvec_पूर्णांकerrupt, 0,
			       "nvec", nvec);
	अगर (err) अणु
		dev_err(dev, "couldn't request irq\n");
		वापस -ENODEV;
	पूर्ण
	disable_irq(nvec->irq);

	tegra_init_i2c_slave(nvec);

	/* enable event reporting */
	nvec_toggle_global_events(nvec, true);

	nvec->nvec_status_notअगरier.notअगरier_call = nvec_status_notअगरier;
	nvec_रेजिस्टर_notअगरier(nvec, &nvec->nvec_status_notअगरier, 0);

	nvec_घातer_handle = nvec;
	pm_घातer_off = nvec_घातer_off;

	/* Get Firmware Version */
	err = nvec_ग_लिखो_sync(nvec, get_firmware_version, 2, &msg);

	अगर (!err) अणु
		dev_warn(dev,
			 "ec firmware version %02x.%02x.%02x / %02x\n",
			 msg->data[4], msg->data[5],
			 msg->data[6], msg->data[7]);

		nvec_msg_मुक्त(nvec, msg);
	पूर्ण

	ret = mfd_add_devices(dev, 0, nvec_devices,
			      ARRAY_SIZE(nvec_devices), शून्य, 0, शून्य);
	अगर (ret)
		dev_err(dev, "error adding subdevices\n");

	/* unmute speakers? */
	nvec_ग_लिखो_async(nvec, unmute_speakers, 4);

	/* enable lid चयन event */
	nvec_event_mask(enable_event, LID_SWITCH);
	nvec_ग_लिखो_async(nvec, enable_event, 7);

	/* enable घातer button event */
	nvec_event_mask(enable_event, PWR_BUTTON);
	nvec_ग_लिखो_async(nvec, enable_event, 7);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_nvec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_chip *nvec = platक्रमm_get_drvdata(pdev);

	nvec_toggle_global_events(nvec, false);
	mfd_हटाओ_devices(nvec->dev);
	nvec_unरेजिस्टर_notअगरier(nvec, &nvec->nvec_status_notअगरier);
	cancel_work_sync(&nvec->rx_work);
	cancel_work_sync(&nvec->tx_work);
	/* FIXME: needs check whether nvec is responsible क्रम घातer off */
	pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nvec_suspend(काष्ठा device *dev)
अणु
	पूर्णांक err;
	काष्ठा nvec_chip *nvec = dev_get_drvdata(dev);
	काष्ठा nvec_msg *msg;
	अक्षर ap_suspend[] = अणु NVEC_SLEEP, AP_SUSPEND पूर्ण;

	dev_dbg(nvec->dev, "suspending\n");

	/* keep these sync or you'll अवरोध suspend */
	nvec_toggle_global_events(nvec, false);

	err = nvec_ग_लिखो_sync(nvec, ap_suspend, माप(ap_suspend), &msg);
	अगर (!err)
		nvec_msg_मुक्त(nvec, msg);

	nvec_disable_i2c_slave(nvec);

	वापस 0;
पूर्ण

अटल पूर्णांक nvec_resume(काष्ठा device *dev)
अणु
	काष्ठा nvec_chip *nvec = dev_get_drvdata(dev);

	dev_dbg(nvec->dev, "resuming\n");
	tegra_init_i2c_slave(nvec);
	nvec_toggle_global_events(nvec, true);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(nvec_pm_ops, nvec_suspend, nvec_resume);

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id nvidia_nvec_of_match[] = अणु
	अणु .compatible = "nvidia,nvec", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, nvidia_nvec_of_match);

अटल काष्ठा platक्रमm_driver nvec_device_driver = अणु
	.probe   = tegra_nvec_probe,
	.हटाओ  = tegra_nvec_हटाओ,
	.driver  = अणु
		.name = "nvec",
		.pm = &nvec_pm_ops,
		.of_match_table = nvidia_nvec_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(nvec_device_driver);

MODULE_ALIAS("platform:nvec");
MODULE_DESCRIPTION("NVIDIA compliant embedded controller interface");
MODULE_AUTHOR("Marc Dietrich <marvin24@gmx.de>");
MODULE_LICENSE("GPL");
