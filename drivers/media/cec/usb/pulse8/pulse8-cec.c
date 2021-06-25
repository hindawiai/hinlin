<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Pulse Eight HDMI CEC driver
 *
 * Copyright 2016 Hans Verkuil <hverkuil@xs4all.nl
 */

/*
 * Notes:
 *
 * - Devices with firmware version < 2 करो not store their configuration in
 *   EEPROM.
 *
 * - In स्वतःnomous mode, only messages from a TV will be acknowledged, even
 *   polling messages. Upon receiving a message from a TV, the करोngle will
 *   respond to messages from any logical address.
 *
 * - In स्वतःnomous mode, the करोngle will by शेष reply Feature Abort
 *   [Unrecognized Opcode] when it receives Give Device Venकरोr ID. It will
 *   however observe venकरोr ID's reported by other devices and possibly
 *   alter this behavior. When TV's (and TV's only) report that their venकरोr ID
 *   is LG (0x00e091), the करोngle will itself reply that it has the same venकरोr
 *   ID, and it will respond to at least one venकरोr specअगरic command.
 *
 * - In स्वतःnomous mode, the करोngle is known to attempt wakeup अगर it receives
 *   <User Control Pressed> ["Power On"], ["Power] or ["Power Toggle"], or अगर it
 *   receives <Set Stream Path> with its own physical address. It also करोes this
 *   अगर it receives <Venकरोr Specअगरic Command> [0x03 0x00] from an LG TV.
 */

#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>

#समावेश <media/cec.h>

MODULE_AUTHOR("Hans Verkuil <hverkuil@xs4all.nl>");
MODULE_DESCRIPTION("Pulse Eight HDMI CEC driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
अटल पूर्णांक persistent_config;
module_param(debug, पूर्णांक, 0644);
module_param(persistent_config, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");
MODULE_PARM_DESC(persistent_config, "read config from persistent memory (0-1)");

क्रमागत pulse8_msgcodes अणु
	MSGCODE_NOTHING = 0,
	MSGCODE_PING,
	MSGCODE_TIMEOUT_ERROR,
	MSGCODE_HIGH_ERROR,
	MSGCODE_LOW_ERROR,
	MSGCODE_FRAME_START,
	MSGCODE_FRAME_DATA,
	MSGCODE_RECEIVE_FAILED,
	MSGCODE_COMMAND_ACCEPTED,	/* 0x08 */
	MSGCODE_COMMAND_REJECTED,
	MSGCODE_SET_ACK_MASK,
	MSGCODE_TRANSMIT,
	MSGCODE_TRANSMIT_EOM,
	MSGCODE_TRANSMIT_IDLETIME,
	MSGCODE_TRANSMIT_ACK_POLARITY,
	MSGCODE_TRANSMIT_LINE_TIMEOUT,
	MSGCODE_TRANSMIT_SUCCEEDED,	/* 0x10 */
	MSGCODE_TRANSMIT_FAILED_LINE,
	MSGCODE_TRANSMIT_FAILED_ACK,
	MSGCODE_TRANSMIT_FAILED_TIMEOUT_DATA,
	MSGCODE_TRANSMIT_FAILED_TIMEOUT_LINE,
	MSGCODE_FIRMWARE_VERSION,
	MSGCODE_START_BOOTLOADER,
	MSGCODE_GET_BUILDDATE,
	MSGCODE_SET_CONTROLLED,		/* 0x18 */
	MSGCODE_GET_AUTO_ENABLED,
	MSGCODE_SET_AUTO_ENABLED,
	MSGCODE_GET_DEFAULT_LOGICAL_ADDRESS,
	MSGCODE_SET_DEFAULT_LOGICAL_ADDRESS,
	MSGCODE_GET_LOGICAL_ADDRESS_MASK,
	MSGCODE_SET_LOGICAL_ADDRESS_MASK,
	MSGCODE_GET_PHYSICAL_ADDRESS,
	MSGCODE_SET_PHYSICAL_ADDRESS,	/* 0x20 */
	MSGCODE_GET_DEVICE_TYPE,
	MSGCODE_SET_DEVICE_TYPE,
	MSGCODE_GET_HDMI_VERSION,	/* Removed in FW >= 10 */
	MSGCODE_SET_HDMI_VERSION,
	MSGCODE_GET_OSD_NAME,
	MSGCODE_SET_OSD_NAME,
	MSGCODE_WRITE_EEPROM,
	MSGCODE_GET_ADAPTER_TYPE,	/* 0x28 */
	MSGCODE_SET_ACTIVE_SOURCE,
	MSGCODE_GET_AUTO_POWER_ON,	/* New क्रम FW >= 10 */
	MSGCODE_SET_AUTO_POWER_ON,

	MSGCODE_FRAME_EOM = 0x80,
	MSGCODE_FRAME_ACK = 0x40,
पूर्ण;

अटल स्थिर अक्षर * स्थिर pulse8_msgnames[] = अणु
	"NOTHING",
	"PING",
	"TIMEOUT_ERROR",
	"HIGH_ERROR",
	"LOW_ERROR",
	"FRAME_START",
	"FRAME_DATA",
	"RECEIVE_FAILED",
	"COMMAND_ACCEPTED",
	"COMMAND_REJECTED",
	"SET_ACK_MASK",
	"TRANSMIT",
	"TRANSMIT_EOM",
	"TRANSMIT_IDLETIME",
	"TRANSMIT_ACK_POLARITY",
	"TRANSMIT_LINE_TIMEOUT",
	"TRANSMIT_SUCCEEDED",
	"TRANSMIT_FAILED_LINE",
	"TRANSMIT_FAILED_ACK",
	"TRANSMIT_FAILED_TIMEOUT_DATA",
	"TRANSMIT_FAILED_TIMEOUT_LINE",
	"FIRMWARE_VERSION",
	"START_BOOTLOADER",
	"GET_BUILDDATE",
	"SET_CONTROLLED",
	"GET_AUTO_ENABLED",
	"SET_AUTO_ENABLED",
	"GET_DEFAULT_LOGICAL_ADDRESS",
	"SET_DEFAULT_LOGICAL_ADDRESS",
	"GET_LOGICAL_ADDRESS_MASK",
	"SET_LOGICAL_ADDRESS_MASK",
	"GET_PHYSICAL_ADDRESS",
	"SET_PHYSICAL_ADDRESS",
	"GET_DEVICE_TYPE",
	"SET_DEVICE_TYPE",
	"GET_HDMI_VERSION",
	"SET_HDMI_VERSION",
	"GET_OSD_NAME",
	"SET_OSD_NAME",
	"WRITE_EEPROM",
	"GET_ADAPTER_TYPE",
	"SET_ACTIVE_SOURCE",
	"GET_AUTO_POWER_ON",
	"SET_AUTO_POWER_ON",
पूर्ण;

अटल स्थिर अक्षर *pulse8_msgname(u8 cmd)
अणु
	अटल अक्षर unknown_msg[5];

	अगर ((cmd & 0x3f) < ARRAY_SIZE(pulse8_msgnames))
		वापस pulse8_msgnames[cmd & 0x3f];
	snम_लिखो(unknown_msg, माप(unknown_msg), "0x%02x", cmd);
	वापस unknown_msg;
पूर्ण

#घोषणा MSGSTART	0xff
#घोषणा MSGEND		0xfe
#घोषणा MSGESC		0xfd
#घोषणा MSGOFFSET	3

#घोषणा DATA_SIZE 256

#घोषणा PING_PERIOD	(15 * HZ)

#घोषणा NUM_MSGS 8

काष्ठा pulse8 अणु
	काष्ठा device *dev;
	काष्ठा serio *serio;
	काष्ठा cec_adapter *adap;
	अचिन्हित पूर्णांक vers;

	काष्ठा delayed_work ping_eeprom_work;

	काष्ठा work_काष्ठा irq_work;
	काष्ठा cec_msg rx_msg[NUM_MSGS];
	अचिन्हित पूर्णांक rx_msg_cur_idx, rx_msg_num;
	/* protect rx_msg_cur_idx and rx_msg_num */
	spinlock_t msg_lock;
	u8 new_rx_msg[CEC_MAX_MSG_SIZE];
	u8 new_rx_msg_len;

	काष्ठा work_काष्ठा tx_work;
	u32 tx_करोne_status;
	u32 tx_संकेत_मुक्त_समय;
	काष्ठा cec_msg tx_msg;
	bool tx_msg_is_bcast;

	काष्ठा completion cmd_करोne;
	u8 data[DATA_SIZE];
	अचिन्हित पूर्णांक len;
	u8 buf[DATA_SIZE];
	अचिन्हित पूर्णांक idx;
	bool escape;
	bool started;

	/* locks access to the adapter */
	काष्ठा mutex lock;
	bool config_pending;
	bool restoring_config;
	bool स्वतःnomous;
पूर्ण;

अटल पूर्णांक pulse8_send(काष्ठा serio *serio, स्थिर u8 *command, u8 cmd_len)
अणु
	पूर्णांक err = 0;

	err = serio_ग_लिखो(serio, MSGSTART);
	अगर (err)
		वापस err;
	क्रम (; !err && cmd_len; command++, cmd_len--) अणु
		अगर (*command >= MSGESC) अणु
			err = serio_ग_लिखो(serio, MSGESC);
			अगर (!err)
				err = serio_ग_लिखो(serio, *command - MSGOFFSET);
		पूर्ण अन्यथा अणु
			err = serio_ग_लिखो(serio, *command);
		पूर्ण
	पूर्ण
	अगर (!err)
		err = serio_ग_लिखो(serio, MSGEND);

	वापस err;
पूर्ण

अटल पूर्णांक pulse8_send_and_रुको_once(काष्ठा pulse8 *pulse8,
				     स्थिर u8 *cmd, u8 cmd_len,
				     u8 response, u8 size)
अणु
	पूर्णांक err;

	अगर (debug > 1)
		dev_info(pulse8->dev, "transmit %s: %*ph\n",
			 pulse8_msgname(cmd[0]), cmd_len, cmd);
	init_completion(&pulse8->cmd_करोne);

	err = pulse8_send(pulse8->serio, cmd, cmd_len);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&pulse8->cmd_करोne, HZ))
		वापस -ETIMEDOUT;
	अगर ((pulse8->data[0] & 0x3f) == MSGCODE_COMMAND_REJECTED &&
	    cmd[0] != MSGCODE_SET_CONTROLLED &&
	    cmd[0] != MSGCODE_SET_AUTO_ENABLED &&
	    cmd[0] != MSGCODE_GET_BUILDDATE)
		वापस -ENOTTY;
	अगर (response &&
	    ((pulse8->data[0] & 0x3f) != response || pulse8->len < size + 1)) अणु
		dev_info(pulse8->dev, "transmit %s failed with %s\n",
			 pulse8_msgname(cmd[0]),
			 pulse8_msgname(pulse8->data[0]));
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pulse8_send_and_रुको(काष्ठा pulse8 *pulse8,
				स्थिर u8 *cmd, u8 cmd_len, u8 response, u8 size)
अणु
	u8 cmd_sc[2];
	पूर्णांक err;

	err = pulse8_send_and_रुको_once(pulse8, cmd, cmd_len, response, size);
	अगर (err != -ENOTTY)
		वापस err;

	cmd_sc[0] = MSGCODE_SET_CONTROLLED;
	cmd_sc[1] = 1;
	err = pulse8_send_and_रुको_once(pulse8, cmd_sc, 2,
					MSGCODE_COMMAND_ACCEPTED, 1);
	अगर (!err)
		err = pulse8_send_and_रुको_once(pulse8, cmd, cmd_len,
						response, size);
	वापस err == -ENOTTY ? -EIO : err;
पूर्ण

अटल व्योम pulse8_tx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pulse8 *pulse8 = container_of(work, काष्ठा pulse8, tx_work);
	काष्ठा cec_msg *msg = &pulse8->tx_msg;
	अचिन्हित पूर्णांक i;
	u8 cmd[2];
	पूर्णांक err;

	अगर (msg->len == 0)
		वापस;

	mutex_lock(&pulse8->lock);
	cmd[0] = MSGCODE_TRANSMIT_IDLETIME;
	cmd[1] = pulse8->tx_संकेत_मुक्त_समय;
	err = pulse8_send_and_रुको(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 1);
	cmd[0] = MSGCODE_TRANSMIT_ACK_POLARITY;
	cmd[1] = cec_msg_is_broadcast(msg);
	pulse8->tx_msg_is_bcast = cec_msg_is_broadcast(msg);
	अगर (!err)
		err = pulse8_send_and_रुको(pulse8, cmd, 2,
					   MSGCODE_COMMAND_ACCEPTED, 1);
	cmd[0] = msg->len == 1 ? MSGCODE_TRANSMIT_EOM : MSGCODE_TRANSMIT;
	cmd[1] = msg->msg[0];
	अगर (!err)
		err = pulse8_send_and_रुको(pulse8, cmd, 2,
					   MSGCODE_COMMAND_ACCEPTED, 1);
	अगर (!err && msg->len > 1) अणु
		क्रम (i = 1; !err && i < msg->len; i++) अणु
			cmd[0] = ((i == msg->len - 1)) ?
				MSGCODE_TRANSMIT_EOM : MSGCODE_TRANSMIT;
			cmd[1] = msg->msg[i];
			err = pulse8_send_and_रुको(pulse8, cmd, 2,
						   MSGCODE_COMMAND_ACCEPTED, 1);
		पूर्ण
	पूर्ण
	अगर (err && debug)
		dev_info(pulse8->dev, "%s(0x%02x) failed with error %d for msg %*ph\n",
			 pulse8_msgname(cmd[0]), cmd[1],
			 err, msg->len, msg->msg);
	msg->len = 0;
	mutex_unlock(&pulse8->lock);
	अगर (err)
		cec_transmit_attempt_करोne(pulse8->adap, CEC_TX_STATUS_ERROR);
पूर्ण

अटल व्योम pulse8_irq_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pulse8 *pulse8 =
		container_of(work, काष्ठा pulse8, irq_work);
	अचिन्हित दीर्घ flags;
	u32 status;

	spin_lock_irqsave(&pulse8->msg_lock, flags);
	जबतक (pulse8->rx_msg_num) अणु
		spin_unlock_irqrestore(&pulse8->msg_lock, flags);
		अगर (debug)
			dev_info(pulse8->dev, "adap received %*ph\n",
				 pulse8->rx_msg[pulse8->rx_msg_cur_idx].len,
				 pulse8->rx_msg[pulse8->rx_msg_cur_idx].msg);
		cec_received_msg(pulse8->adap,
				 &pulse8->rx_msg[pulse8->rx_msg_cur_idx]);
		spin_lock_irqsave(&pulse8->msg_lock, flags);
		अगर (pulse8->rx_msg_num)
			pulse8->rx_msg_num--;
		pulse8->rx_msg_cur_idx =
			(pulse8->rx_msg_cur_idx + 1) % NUM_MSGS;
	पूर्ण
	spin_unlock_irqrestore(&pulse8->msg_lock, flags);

	mutex_lock(&pulse8->lock);
	status = pulse8->tx_करोne_status;
	pulse8->tx_करोne_status = 0;
	mutex_unlock(&pulse8->lock);
	अगर (status)
		cec_transmit_attempt_करोne(pulse8->adap, status);
पूर्ण

अटल irqवापस_t pulse8_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा pulse8 *pulse8 = serio_get_drvdata(serio);
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक idx;

	अगर (!pulse8->started && data != MSGSTART)
		वापस IRQ_HANDLED;
	अगर (data == MSGESC) अणु
		pulse8->escape = true;
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (pulse8->escape) अणु
		data += MSGOFFSET;
		pulse8->escape = false;
	पूर्ण अन्यथा अगर (data == MSGEND) अणु
		u8 msgcode = pulse8->buf[0];

		अगर (debug > 1)
			dev_info(pulse8->dev, "received %s: %*ph\n",
				 pulse8_msgname(msgcode),
				 pulse8->idx, pulse8->buf);
		चयन (msgcode & 0x3f) अणु
		हाल MSGCODE_FRAME_START:
			/*
			 * Test अगर we are receiving a new msg when a previous
			 * message is still pending.
			 */
			अगर (!(msgcode & MSGCODE_FRAME_EOM)) अणु
				pulse8->new_rx_msg_len = 1;
				pulse8->new_rx_msg[0] = pulse8->buf[1];
				अवरोध;
			पूर्ण
			fallthrough;
		हाल MSGCODE_FRAME_DATA:
			अगर (pulse8->new_rx_msg_len < CEC_MAX_MSG_SIZE)
				pulse8->new_rx_msg[pulse8->new_rx_msg_len++] =
					pulse8->buf[1];
			अगर (!(msgcode & MSGCODE_FRAME_EOM))
				अवरोध;

			spin_lock_irqsave(&pulse8->msg_lock, irq_flags);
			idx = (pulse8->rx_msg_cur_idx + pulse8->rx_msg_num) %
				NUM_MSGS;
			अगर (pulse8->rx_msg_num == NUM_MSGS) अणु
				dev_warn(pulse8->dev,
					 "message queue is full, dropping %*ph\n",
					 pulse8->new_rx_msg_len,
					 pulse8->new_rx_msg);
				spin_unlock_irqrestore(&pulse8->msg_lock,
						       irq_flags);
				pulse8->new_rx_msg_len = 0;
				अवरोध;
			पूर्ण
			pulse8->rx_msg_num++;
			स_नकल(pulse8->rx_msg[idx].msg, pulse8->new_rx_msg,
			       pulse8->new_rx_msg_len);
			pulse8->rx_msg[idx].len = pulse8->new_rx_msg_len;
			spin_unlock_irqrestore(&pulse8->msg_lock, irq_flags);
			schedule_work(&pulse8->irq_work);
			pulse8->new_rx_msg_len = 0;
			अवरोध;
		हाल MSGCODE_TRANSMIT_SUCCEEDED:
			WARN_ON(pulse8->tx_करोne_status);
			pulse8->tx_करोne_status = CEC_TX_STATUS_OK;
			schedule_work(&pulse8->irq_work);
			अवरोध;
		हाल MSGCODE_TRANSMIT_FAILED_ACK:
			/*
			 * A NACK क्रम a broadcast message makes no sense, these
			 * seem to be spurious messages and are skipped.
			 */
			अगर (pulse8->tx_msg_is_bcast)
				अवरोध;
			WARN_ON(pulse8->tx_करोne_status);
			pulse8->tx_करोne_status = CEC_TX_STATUS_NACK;
			schedule_work(&pulse8->irq_work);
			अवरोध;
		हाल MSGCODE_TRANSMIT_FAILED_LINE:
		हाल MSGCODE_TRANSMIT_FAILED_TIMEOUT_DATA:
		हाल MSGCODE_TRANSMIT_FAILED_TIMEOUT_LINE:
			WARN_ON(pulse8->tx_करोne_status);
			pulse8->tx_करोne_status = CEC_TX_STATUS_ERROR;
			schedule_work(&pulse8->irq_work);
			अवरोध;
		हाल MSGCODE_HIGH_ERROR:
		हाल MSGCODE_LOW_ERROR:
		हाल MSGCODE_RECEIVE_FAILED:
		हाल MSGCODE_TIMEOUT_ERROR:
			pulse8->new_rx_msg_len = 0;
			अवरोध;
		हाल MSGCODE_COMMAND_ACCEPTED:
		हाल MSGCODE_COMMAND_REJECTED:
		शेष:
			अगर (pulse8->idx == 0)
				अवरोध;
			स_नकल(pulse8->data, pulse8->buf, pulse8->idx);
			pulse8->len = pulse8->idx;
			complete(&pulse8->cmd_करोne);
			अवरोध;
		पूर्ण
		pulse8->idx = 0;
		pulse8->started = false;
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (data == MSGSTART) अणु
		pulse8->idx = 0;
		pulse8->started = true;
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (pulse8->idx >= DATA_SIZE) अणु
		dev_dbg(pulse8->dev,
			"throwing away %d bytes of garbage\n", pulse8->idx);
		pulse8->idx = 0;
	पूर्ण
	pulse8->buf[pulse8->idx++] = data;
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pulse8_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा pulse8 *pulse8 = cec_get_drvdata(adap);
	u8 cmd[16];
	पूर्णांक err;

	mutex_lock(&pulse8->lock);
	cmd[0] = MSGCODE_SET_CONTROLLED;
	cmd[1] = enable;
	err = pulse8_send_and_रुको(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 1);
	अगर (!enable) अणु
		pulse8->rx_msg_num = 0;
		pulse8->tx_करोne_status = 0;
	पूर्ण
	mutex_unlock(&pulse8->lock);
	वापस enable ? err : 0;
पूर्ण

अटल पूर्णांक pulse8_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा pulse8 *pulse8 = cec_get_drvdata(adap);
	u16 mask = 0;
	u16 pa = adap->phys_addr;
	u8 cmd[16];
	पूर्णांक err = 0;

	mutex_lock(&pulse8->lock);
	अगर (log_addr != CEC_LOG_ADDR_INVALID)
		mask = 1 << log_addr;
	cmd[0] = MSGCODE_SET_ACK_MASK;
	cmd[1] = mask >> 8;
	cmd[2] = mask & 0xff;
	err = pulse8_send_and_रुको(pulse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	अगर ((err && mask != 0) || pulse8->restoring_config)
		जाओ unlock;

	cmd[0] = MSGCODE_SET_AUTO_ENABLED;
	cmd[1] = log_addr == CEC_LOG_ADDR_INVALID ? 0 : 1;
	err = pulse8_send_and_रुको(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	अगर (err)
		जाओ unlock;
	pulse8->स्वतःnomous = cmd[1];
	अगर (log_addr == CEC_LOG_ADDR_INVALID)
		जाओ unlock;

	cmd[0] = MSGCODE_SET_DEVICE_TYPE;
	cmd[1] = adap->log_addrs.primary_device_type[0];
	err = pulse8_send_and_रुको(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	अगर (err)
		जाओ unlock;

	चयन (adap->log_addrs.primary_device_type[0]) अणु
	हाल CEC_OP_PRIM_DEVTYPE_TV:
		mask = CEC_LOG_ADDR_MASK_TV;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_RECORD:
		mask = CEC_LOG_ADDR_MASK_RECORD;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_TUNER:
		mask = CEC_LOG_ADDR_MASK_TUNER;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_PLAYBACK:
		mask = CEC_LOG_ADDR_MASK_PLAYBACK;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM:
		mask = CEC_LOG_ADDR_MASK_AUDIOSYSTEM;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_SWITCH:
		mask = CEC_LOG_ADDR_MASK_UNREGISTERED;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_PROCESSOR:
		mask = CEC_LOG_ADDR_MASK_SPECIFIC;
		अवरोध;
	शेष:
		mask = 0;
		अवरोध;
	पूर्ण
	cmd[0] = MSGCODE_SET_LOGICAL_ADDRESS_MASK;
	cmd[1] = mask >> 8;
	cmd[2] = mask & 0xff;
	err = pulse8_send_and_रुको(pulse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	अगर (err)
		जाओ unlock;

	cmd[0] = MSGCODE_SET_DEFAULT_LOGICAL_ADDRESS;
	cmd[1] = log_addr;
	err = pulse8_send_and_रुको(pulse8, cmd, 2,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	अगर (err)
		जाओ unlock;

	cmd[0] = MSGCODE_SET_PHYSICAL_ADDRESS;
	cmd[1] = pa >> 8;
	cmd[2] = pa & 0xff;
	err = pulse8_send_and_रुको(pulse8, cmd, 3,
				   MSGCODE_COMMAND_ACCEPTED, 0);
	अगर (err)
		जाओ unlock;

	अगर (pulse8->vers < 10) अणु
		cmd[0] = MSGCODE_SET_HDMI_VERSION;
		cmd[1] = adap->log_addrs.cec_version;
		err = pulse8_send_and_रुको(pulse8, cmd, 2,
					   MSGCODE_COMMAND_ACCEPTED, 0);
		अगर (err)
			जाओ unlock;
	पूर्ण

	अगर (adap->log_addrs.osd_name[0]) अणु
		माप_प्रकार osd_len = म_माप(adap->log_addrs.osd_name);
		अक्षर *osd_str = cmd + 1;

		cmd[0] = MSGCODE_SET_OSD_NAME;
		strscpy(cmd + 1, adap->log_addrs.osd_name, माप(cmd) - 1);
		अगर (osd_len < 4) अणु
			स_रखो(osd_str + osd_len, ' ', 4 - osd_len);
			osd_len = 4;
			osd_str[osd_len] = '\0';
			strscpy(adap->log_addrs.osd_name, osd_str,
				माप(adap->log_addrs.osd_name));
		पूर्ण
		err = pulse8_send_and_रुको(pulse8, cmd, 1 + osd_len,
					   MSGCODE_COMMAND_ACCEPTED, 0);
		अगर (err)
			जाओ unlock;
	पूर्ण

unlock:
	अगर (pulse8->restoring_config)
		pulse8->restoring_config = false;
	अन्यथा
		pulse8->config_pending = true;
	mutex_unlock(&pulse8->lock);
	वापस log_addr == CEC_LOG_ADDR_INVALID ? 0 : err;
पूर्ण

अटल पूर्णांक pulse8_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				    u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा pulse8 *pulse8 = cec_get_drvdata(adap);

	pulse8->tx_msg = *msg;
	अगर (debug)
		dev_info(pulse8->dev, "adap transmit %*ph\n",
			 msg->len, msg->msg);
	pulse8->tx_संकेत_मुक्त_समय = संकेत_मुक्त_समय;
	schedule_work(&pulse8->tx_work);
	वापस 0;
पूर्ण

अटल व्योम pulse8_cec_adap_मुक्त(काष्ठा cec_adapter *adap)
अणु
	काष्ठा pulse8 *pulse8 = cec_get_drvdata(adap);

	cancel_delayed_work_sync(&pulse8->ping_eeprom_work);
	cancel_work_sync(&pulse8->irq_work);
	cancel_work_sync(&pulse8->tx_work);
	kमुक्त(pulse8);
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops pulse8_cec_adap_ops = अणु
	.adap_enable = pulse8_cec_adap_enable,
	.adap_log_addr = pulse8_cec_adap_log_addr,
	.adap_transmit = pulse8_cec_adap_transmit,
	.adap_मुक्त = pulse8_cec_adap_मुक्त,
पूर्ण;

अटल व्योम pulse8_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा pulse8 *pulse8 = serio_get_drvdata(serio);

	cec_unरेजिस्टर_adapter(pulse8->adap);
	serio_set_drvdata(serio, शून्य);
	serio_बंद(serio);
पूर्ण

अटल पूर्णांक pulse8_setup(काष्ठा pulse8 *pulse8, काष्ठा serio *serio,
			काष्ठा cec_log_addrs *log_addrs, u16 *pa)
अणु
	u8 *data = pulse8->data + 1;
	u8 cmd[2];
	पूर्णांक err;
	समय64_t date;

	pulse8->vers = 0;

	cmd[0] = MSGCODE_FIRMWARE_VERSION;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 2);
	अगर (err)
		वापस err;
	pulse8->vers = (data[0] << 8) | data[1];
	dev_info(pulse8->dev, "Firmware version %04x\n", pulse8->vers);
	अगर (pulse8->vers < 2) अणु
		*pa = CEC_PHYS_ADDR_INVALID;
		वापस 0;
	पूर्ण

	cmd[0] = MSGCODE_GET_BUILDDATE;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 4);
	अगर (err)
		वापस err;
	date = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	dev_info(pulse8->dev, "Firmware build date %ptT\n", &date);

	dev_dbg(pulse8->dev, "Persistent config:\n");
	cmd[0] = MSGCODE_GET_AUTO_ENABLED;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 1);
	अगर (err)
		वापस err;
	pulse8->स्वतःnomous = data[0];
	dev_dbg(pulse8->dev, "Autonomous mode: %s",
		data[0] ? "on" : "off");

	अगर (pulse8->vers >= 10) अणु
		cmd[0] = MSGCODE_GET_AUTO_POWER_ON;
		err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 1);
		अगर (!err)
			dev_dbg(pulse8->dev, "Auto Power On: %s",
				data[0] ? "on" : "off");
	पूर्ण

	cmd[0] = MSGCODE_GET_DEVICE_TYPE;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 1);
	अगर (err)
		वापस err;
	log_addrs->primary_device_type[0] = data[0];
	dev_dbg(pulse8->dev, "Primary device type: %d\n", data[0]);
	चयन (log_addrs->primary_device_type[0]) अणु
	हाल CEC_OP_PRIM_DEVTYPE_TV:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_TV;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_TV;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_RECORD:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_RECORD;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_RECORD;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_TUNER:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_TUNER;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_TUNER;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_PLAYBACK:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_PLAYBACK;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_PLAYBACK;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_AUDIOSYSTEM:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_PLAYBACK;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_AUDIOSYSTEM;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_SWITCH:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_UNREGISTERED;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_SWITCH;
		अवरोध;
	हाल CEC_OP_PRIM_DEVTYPE_PROCESSOR:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_SPECIFIC;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_SWITCH;
		अवरोध;
	शेष:
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_UNREGISTERED;
		log_addrs->all_device_types[0] = CEC_OP_ALL_DEVTYPE_SWITCH;
		dev_info(pulse8->dev, "Unknown Primary Device Type: %d\n",
			 log_addrs->primary_device_type[0]);
		अवरोध;
	पूर्ण

	cmd[0] = MSGCODE_GET_LOGICAL_ADDRESS_MASK;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 2);
	अगर (err)
		वापस err;
	log_addrs->log_addr_mask = (data[0] << 8) | data[1];
	dev_dbg(pulse8->dev, "Logical address ACK mask: %x\n",
		log_addrs->log_addr_mask);
	अगर (log_addrs->log_addr_mask)
		log_addrs->num_log_addrs = 1;

	cmd[0] = MSGCODE_GET_PHYSICAL_ADDRESS;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 1);
	अगर (err)
		वापस err;
	*pa = (data[0] << 8) | data[1];
	dev_dbg(pulse8->dev, "Physical address: %x.%x.%x.%x\n",
		cec_phys_addr_exp(*pa));

	log_addrs->cec_version = CEC_OP_CEC_VERSION_1_4;
	अगर (pulse8->vers < 10) अणु
		cmd[0] = MSGCODE_GET_HDMI_VERSION;
		err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 1);
		अगर (err)
			वापस err;
		log_addrs->cec_version = data[0];
		dev_dbg(pulse8->dev, "CEC version: %d\n", log_addrs->cec_version);
	पूर्ण

	cmd[0] = MSGCODE_GET_OSD_NAME;
	err = pulse8_send_and_रुको(pulse8, cmd, 1, cmd[0], 0);
	अगर (err)
		वापस err;
	strscpy(log_addrs->osd_name, data, माप(log_addrs->osd_name));
	dev_dbg(pulse8->dev, "OSD name: %s\n", log_addrs->osd_name);

	वापस 0;
पूर्ण

अटल पूर्णांक pulse8_apply_persistent_config(काष्ठा pulse8 *pulse8,
					  काष्ठा cec_log_addrs *log_addrs,
					  u16 pa)
अणु
	पूर्णांक err;

	err = cec_s_log_addrs(pulse8->adap, log_addrs, false);
	अगर (err)
		वापस err;

	cec_s_phys_addr(pulse8->adap, pa, false);

	वापस 0;
पूर्ण

अटल व्योम pulse8_ping_eeprom_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pulse8 *pulse8 =
		container_of(work, काष्ठा pulse8, ping_eeprom_work.work);
	u8 cmd;

	mutex_lock(&pulse8->lock);
	cmd = MSGCODE_PING;
	pulse8_send_and_रुको(pulse8, &cmd, 1,
			     MSGCODE_COMMAND_ACCEPTED, 0);

	अगर (pulse8->vers < 2)
		जाओ unlock;

	अगर (pulse8->config_pending && persistent_config) अणु
		dev_dbg(pulse8->dev, "writing pending config to EEPROM\n");
		cmd = MSGCODE_WRITE_EEPROM;
		अगर (pulse8_send_and_रुको(pulse8, &cmd, 1,
					 MSGCODE_COMMAND_ACCEPTED, 0))
			dev_info(pulse8->dev, "failed to write pending config to EEPROM\n");
		अन्यथा
			pulse8->config_pending = false;
	पूर्ण
unlock:
	schedule_delayed_work(&pulse8->ping_eeprom_work, PING_PERIOD);
	mutex_unlock(&pulse8->lock);
पूर्ण

अटल पूर्णांक pulse8_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	u32 caps = CEC_CAP_DEFAULTS | CEC_CAP_PHYS_ADDR | CEC_CAP_MONITOR_ALL;
	काष्ठा pulse8 *pulse8;
	पूर्णांक err = -ENOMEM;
	काष्ठा cec_log_addrs log_addrs = अणुपूर्ण;
	u16 pa = CEC_PHYS_ADDR_INVALID;

	pulse8 = kzalloc(माप(*pulse8), GFP_KERNEL);

	अगर (!pulse8)
		वापस -ENOMEM;

	pulse8->serio = serio;
	pulse8->adap = cec_allocate_adapter(&pulse8_cec_adap_ops, pulse8,
					    dev_name(&serio->dev), caps, 1);
	err = PTR_ERR_OR_ZERO(pulse8->adap);
	अगर (err < 0) अणु
		kमुक्त(pulse8);
		वापस err;
	पूर्ण

	pulse8->dev = &serio->dev;
	serio_set_drvdata(serio, pulse8);
	INIT_WORK(&pulse8->irq_work, pulse8_irq_work_handler);
	INIT_WORK(&pulse8->tx_work, pulse8_tx_work_handler);
	INIT_DELAYED_WORK(&pulse8->ping_eeprom_work,
			  pulse8_ping_eeprom_work_handler);
	mutex_init(&pulse8->lock);
	spin_lock_init(&pulse8->msg_lock);
	pulse8->config_pending = false;

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ delete_adap;

	err = pulse8_setup(pulse8, serio, &log_addrs, &pa);
	अगर (err)
		जाओ बंद_serio;

	err = cec_रेजिस्टर_adapter(pulse8->adap, &serio->dev);
	अगर (err < 0)
		जाओ बंद_serio;

	pulse8->dev = &pulse8->adap->devnode.dev;

	अगर (persistent_config && pulse8->स्वतःnomous) अणु
		err = pulse8_apply_persistent_config(pulse8, &log_addrs, pa);
		अगर (err)
			जाओ बंद_serio;
		pulse8->restoring_config = true;
	पूर्ण

	schedule_delayed_work(&pulse8->ping_eeprom_work, PING_PERIOD);

	वापस 0;

बंद_serio:
	pulse8->serio = शून्य;
	serio_set_drvdata(serio, शून्य);
	serio_बंद(serio);
delete_adap:
	cec_delete_adapter(pulse8->adap);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा serio_device_id pulse8_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_PULSE8_CEC,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, pulse8_serio_ids);

अटल काष्ठा serio_driver pulse8_drv = अणु
	.driver		= अणु
		.name	= "pulse8-cec",
	पूर्ण,
	.description	= "Pulse Eight HDMI CEC driver",
	.id_table	= pulse8_serio_ids,
	.पूर्णांकerrupt	= pulse8_पूर्णांकerrupt,
	.connect	= pulse8_connect,
	.disconnect	= pulse8_disconnect,
पूर्ण;

module_serio_driver(pulse8_drv);
