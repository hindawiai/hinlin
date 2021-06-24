<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 System Manager.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>

#समावेश "vuart.h"

/**
 * ps3_sys_manager - PS3 प्रणाली manager driver.
 *
 * The प्रणाली manager provides an asynchronous प्रणाली event notअगरication
 * mechanism क्रम reporting events like thermal alert and button presses to
 * guests.  It also provides support to control प्रणाली shutकरोwn and startup.
 *
 * The actual प्रणाली manager is implemented as an application running in the
 * प्रणाली policy module in lpar_1.  Guests communicate with the प्रणाली manager
 * through port 2 of the vuart using a simple packet message protocol.
 * Messages are comprised of a fixed field header followed by a message
 * specअगरic payload.
 */

/**
 * काष्ठा ps3_sys_manager_header - System manager message header.
 * @version: Header version, currently 1.
 * @size: Header size in bytes, currently 16.
 * @payload_size: Message payload size in bytes.
 * @service_id: Message type, one of क्रमागत ps3_sys_manager_service_id.
 * @request_tag: Unique number to identअगरy reply.
 */

काष्ठा ps3_sys_manager_header अणु
	/* version 1 */
	u8 version;
	u8 size;
	u16 reserved_1;
	u32 payload_size;
	u16 service_id;
	u16 reserved_2;
	u32 request_tag;
पूर्ण;

#घोषणा dump_sm_header(_h) _dump_sm_header(_h, __func__, __LINE__)
अटल व्योम __maybe_unused _dump_sm_header(
	स्थिर काष्ठा ps3_sys_manager_header *h, स्थिर अक्षर *func, पूर्णांक line)
अणु
	pr_debug("%s:%d: version:      %xh\n", func, line, h->version);
	pr_debug("%s:%d: size:         %xh\n", func, line, h->size);
	pr_debug("%s:%d: payload_size: %xh\n", func, line, h->payload_size);
	pr_debug("%s:%d: service_id:   %xh\n", func, line, h->service_id);
	pr_debug("%s:%d: request_tag:  %xh\n", func, line, h->request_tag);
पूर्ण

/**
 * @PS3_SM_RX_MSG_LEN_MIN - Shortest received message length.
 * @PS3_SM_RX_MSG_LEN_MAX - Longest received message length.
 *
 * Currently all messages received from the प्रणाली manager are either
 * (16 bytes header + 8 bytes payload = 24 bytes) or (16 bytes header
 * + 16 bytes payload = 32 bytes).  This knowledge is used to simplअगरy
 * the logic.
 */

क्रमागत अणु
	PS3_SM_RX_MSG_LEN_MIN = 24,
	PS3_SM_RX_MSG_LEN_MAX = 32,
पूर्ण;

/**
 * क्रमागत ps3_sys_manager_service_id - Message header service_id.
 * @PS3_SM_SERVICE_ID_REQUEST:       guest --> sys_manager.
 * @PS3_SM_SERVICE_ID_REQUEST_ERROR: guest <-- sys_manager.
 * @PS3_SM_SERVICE_ID_COMMAND:       guest <-- sys_manager.
 * @PS3_SM_SERVICE_ID_RESPONSE:      guest --> sys_manager.
 * @PS3_SM_SERVICE_ID_SET_ATTR:      guest --> sys_manager.
 * @PS3_SM_SERVICE_ID_EXTERN_EVENT:  guest <-- sys_manager.
 * @PS3_SM_SERVICE_ID_SET_NEXT_OP:   guest --> sys_manager.
 *
 * PS3_SM_SERVICE_ID_REQUEST_ERROR is वापसed क्रम invalid data values in a
 * a PS3_SM_SERVICE_ID_REQUEST message.  It also seems to be वापसed when
 * a REQUEST message is sent at the wrong समय.
 */

क्रमागत ps3_sys_manager_service_id अणु
	/* version 1 */
	PS3_SM_SERVICE_ID_REQUEST = 1,
	PS3_SM_SERVICE_ID_RESPONSE = 2,
	PS3_SM_SERVICE_ID_COMMAND = 3,
	PS3_SM_SERVICE_ID_EXTERN_EVENT = 4,
	PS3_SM_SERVICE_ID_SET_NEXT_OP = 5,
	PS3_SM_SERVICE_ID_REQUEST_ERROR = 6,
	PS3_SM_SERVICE_ID_SET_ATTR = 8,
पूर्ण;

/**
 * क्रमागत ps3_sys_manager_attr - Notअगरication attribute (bit position mask).
 * @PS3_SM_ATTR_POWER: Power button.
 * @PS3_SM_ATTR_RESET: Reset button, not available on retail console.
 * @PS3_SM_ATTR_THERMAL: System thermal alert.
 * @PS3_SM_ATTR_CONTROLLER: Remote controller event.
 * @PS3_SM_ATTR_ALL: Logical OR of all.
 *
 * The guest tells the प्रणाली manager which events it is पूर्णांकerested in receiving
 * notice of by sending the प्रणाली manager a logical OR of notअगरication
 * attributes via the ps3_sys_manager_send_attr() routine.
 */

क्रमागत ps3_sys_manager_attr अणु
	/* version 1 */
	PS3_SM_ATTR_POWER = 1,
	PS3_SM_ATTR_RESET = 2,
	PS3_SM_ATTR_THERMAL = 4,
	PS3_SM_ATTR_CONTROLLER = 8, /* bogus? */
	PS3_SM_ATTR_ALL = 0x0f,
पूर्ण;

/**
 * क्रमागत ps3_sys_manager_event - External event type, reported by प्रणाली manager.
 * @PS3_SM_EVENT_POWER_PRESSED: payload.value =
 *  क्रमागत ps3_sys_manager_button_event.
 * @PS3_SM_EVENT_POWER_RELEASED: payload.value = समय pressed in millisec.
 * @PS3_SM_EVENT_RESET_PRESSED: payload.value =
 *  क्रमागत ps3_sys_manager_button_event.
 * @PS3_SM_EVENT_RESET_RELEASED: payload.value = समय pressed in millisec.
 * @PS3_SM_EVENT_THERMAL_ALERT: payload.value = thermal zone id.
 * @PS3_SM_EVENT_THERMAL_CLEARED: payload.value = thermal zone id.
 */

क्रमागत ps3_sys_manager_event अणु
	/* version 1 */
	PS3_SM_EVENT_POWER_PRESSED = 3,
	PS3_SM_EVENT_POWER_RELEASED = 4,
	PS3_SM_EVENT_RESET_PRESSED = 5,
	PS3_SM_EVENT_RESET_RELEASED = 6,
	PS3_SM_EVENT_THERMAL_ALERT = 7,
	PS3_SM_EVENT_THERMAL_CLEARED = 8,
	/* no info on controller events */
पूर्ण;

/**
 * क्रमागत ps3_sys_manager_button_event - Button event payload values.
 * @PS3_SM_BUTTON_EVENT_HARD: Hardware generated event.
 * @PS3_SM_BUTTON_EVENT_SOFT: Software generated event.
 */

क्रमागत ps3_sys_manager_button_event अणु
	PS3_SM_BUTTON_EVENT_HARD = 0,
	PS3_SM_BUTTON_EVENT_SOFT = 1,
पूर्ण;

/**
 * क्रमागत ps3_sys_manager_next_op - Operation to perक्रमm after lpar is destroyed.
 */

क्रमागत ps3_sys_manager_next_op अणु
	/* version 3 */
	PS3_SM_NEXT_OP_SYS_SHUTDOWN = 1,
	PS3_SM_NEXT_OP_SYS_REBOOT = 2,
	PS3_SM_NEXT_OP_LPAR_REBOOT = 0x82,
पूर्ण;

/**
 * क्रमागत ps3_sys_manager_wake_source - Next-op wakeup source (bit position mask).
 * @PS3_SM_WAKE_DEFAULT: Disk insert, घातer button, eject button.
 * @PS3_SM_WAKE_W_O_L: Ether or wireless LAN.
 * @PS3_SM_WAKE_P_O_R: Power on reset.
 *
 * Additional wakeup sources when specअगरying PS3_SM_NEXT_OP_SYS_SHUTDOWN.
 * The प्रणाली will always wake from the PS3_SM_WAKE_DEFAULT sources.
 * Sources listed here are the only ones available to guests in the
 * other-os lpar.
 */

क्रमागत ps3_sys_manager_wake_source अणु
	/* version 3 */
	PS3_SM_WAKE_DEFAULT   = 0,
	PS3_SM_WAKE_W_O_L     = 0x00000400,
	PS3_SM_WAKE_P_O_R     = 0x80000000,
पूर्ण;

/**
 * user_wake_sources - User specअगरied wakeup sources.
 *
 * Logical OR of क्रमागत ps3_sys_manager_wake_source types.
 */

अटल u32 user_wake_sources = PS3_SM_WAKE_DEFAULT;

/**
 * क्रमागत ps3_sys_manager_cmd - Command from प्रणाली manager to guest.
 *
 * The guest completes the actions needed, then acks or naks the command via
 * ps3_sys_manager_send_response().  In the हाल of @PS3_SM_CMD_SHUTDOWN,
 * the guest must be fully prepared क्रम a प्रणाली घातeroff prior to acking the
 * command.
 */

क्रमागत ps3_sys_manager_cmd अणु
	/* version 1 */
	PS3_SM_CMD_SHUTDOWN = 1, /* shutकरोwn guest OS */
पूर्ण;

/**
 * ps3_sm_क्रमce_घातer_off - Poweroff helper.
 *
 * A global variable used to क्रमce a घातeroff when the घातer button has
 * been pressed irrespective of how init handles the ctrl_alt_del संकेत.
 *
 */

अटल अचिन्हित पूर्णांक ps3_sm_क्रमce_घातer_off;

/**
 * ps3_sys_manager_ग_लिखो - Helper to ग_लिखो a two part message to the vuart.
 *
 */

अटल पूर्णांक ps3_sys_manager_ग_लिखो(काष्ठा ps3_प्रणाली_bus_device *dev,
	स्थिर काष्ठा ps3_sys_manager_header *header, स्थिर व्योम *payload)
अणु
	पूर्णांक result;

	BUG_ON(header->version != 1);
	BUG_ON(header->size != 16);
	BUG_ON(header->payload_size != 8 && header->payload_size != 16);
	BUG_ON(header->service_id > 8);

	result = ps3_vuart_ग_लिखो(dev, header,
		माप(काष्ठा ps3_sys_manager_header));

	अगर (!result)
		result = ps3_vuart_ग_लिखो(dev, payload, header->payload_size);

	वापस result;
पूर्ण

/**
 * ps3_sys_manager_send_attr - Send a 'set attribute' to the प्रणाली manager.
 *
 */

अटल पूर्णांक ps3_sys_manager_send_attr(काष्ठा ps3_प्रणाली_bus_device *dev,
	क्रमागत ps3_sys_manager_attr attr)
अणु
	काष्ठा ps3_sys_manager_header header;
	काष्ठा अणु
		u8 version;
		u8 reserved_1[3];
		u32 attribute;
	पूर्ण payload;

	BUILD_BUG_ON(माप(payload) != 8);

	dev_dbg(&dev->core, "%s:%d: %xh\n", __func__, __LINE__, attr);

	स_रखो(&header, 0, माप(header));
	header.version = 1;
	header.size = 16;
	header.payload_size = 16;
	header.service_id = PS3_SM_SERVICE_ID_SET_ATTR;

	स_रखो(&payload, 0, माप(payload));
	payload.version = 1;
	payload.attribute = attr;

	वापस ps3_sys_manager_ग_लिखो(dev, &header, &payload);
पूर्ण

/**
 * ps3_sys_manager_send_next_op - Send a 'set next op' to the प्रणाली manager.
 *
 * Tell the प्रणाली manager what to करो after this lpar is destroyed.
 */

अटल पूर्णांक ps3_sys_manager_send_next_op(काष्ठा ps3_प्रणाली_bus_device *dev,
	क्रमागत ps3_sys_manager_next_op op,
	क्रमागत ps3_sys_manager_wake_source wake_source)
अणु
	काष्ठा ps3_sys_manager_header header;
	काष्ठा अणु
		u8 version;
		u8 type;
		u8 gos_id;
		u8 reserved_1;
		u32 wake_source;
		u8 reserved_2[8];
	पूर्ण payload;

	BUILD_BUG_ON(माप(payload) != 16);

	dev_dbg(&dev->core, "%s:%d: (%xh)\n", __func__, __LINE__, op);

	स_रखो(&header, 0, माप(header));
	header.version = 1;
	header.size = 16;
	header.payload_size = 16;
	header.service_id = PS3_SM_SERVICE_ID_SET_NEXT_OP;

	स_रखो(&payload, 0, माप(payload));
	payload.version = 3;
	payload.type = op;
	payload.gos_id = 3; /* other os */
	payload.wake_source = wake_source;

	वापस ps3_sys_manager_ग_लिखो(dev, &header, &payload);
पूर्ण

/**
 * ps3_sys_manager_send_request_shutकरोwn - Send 'request' to the प्रणाली manager.
 *
 * The guest sends this message to request an operation or action of the प्रणाली
 * manager.  The reply is a command message from the प्रणाली manager.  In the
 * command handler the guest perक्रमms the requested operation.  The result of
 * the command is then communicated back to the प्रणाली manager with a response
 * message.
 *
 * Currently, the only supported request is the 'shutdown self' request.
 */

अटल पूर्णांक ps3_sys_manager_send_request_shutकरोwn(
	काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा ps3_sys_manager_header header;
	काष्ठा अणु
		u8 version;
		u8 type;
		u8 gos_id;
		u8 reserved_1[13];
	पूर्ण payload;

	BUILD_BUG_ON(माप(payload) != 16);

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	स_रखो(&header, 0, माप(header));
	header.version = 1;
	header.size = 16;
	header.payload_size = 16;
	header.service_id = PS3_SM_SERVICE_ID_REQUEST;

	स_रखो(&payload, 0, माप(payload));
	payload.version = 1;
	payload.type = 1; /* shutकरोwn */
	payload.gos_id = 0; /* self */

	वापस ps3_sys_manager_ग_लिखो(dev, &header, &payload);
पूर्ण

/**
 * ps3_sys_manager_send_response - Send a 'response' to the प्रणाली manager.
 * @status: zero = success, others fail.
 *
 * The guest sends this message to the प्रणाली manager to acnowledge success or
 * failure of a command sent by the प्रणाली manager.
 */

अटल पूर्णांक ps3_sys_manager_send_response(काष्ठा ps3_प्रणाली_bus_device *dev,
	u64 status)
अणु
	काष्ठा ps3_sys_manager_header header;
	काष्ठा अणु
		u8 version;
		u8 reserved_1[3];
		u8 status;
		u8 reserved_2[11];
	पूर्ण payload;

	BUILD_BUG_ON(माप(payload) != 16);

	dev_dbg(&dev->core, "%s:%d: (%s)\n", __func__, __LINE__,
		(status ? "nak" : "ack"));

	स_रखो(&header, 0, माप(header));
	header.version = 1;
	header.size = 16;
	header.payload_size = 16;
	header.service_id = PS3_SM_SERVICE_ID_RESPONSE;

	स_रखो(&payload, 0, माप(payload));
	payload.version = 1;
	payload.status = status;

	वापस ps3_sys_manager_ग_लिखो(dev, &header, &payload);
पूर्ण

/**
 * ps3_sys_manager_handle_event - Second stage event msg handler.
 *
 */

अटल पूर्णांक ps3_sys_manager_handle_event(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा अणु
		u8 version;
		u8 type;
		u8 reserved_1[2];
		u32 value;
		u8 reserved_2[8];
	पूर्ण event;

	BUILD_BUG_ON(माप(event) != 16);

	result = ps3_vuart_पढ़ो(dev, &event, माप(event));
	BUG_ON(result && "need to retry here");

	अगर (event.version != 1) अणु
		dev_dbg(&dev->core, "%s:%d: unsupported event version (%u)\n",
			__func__, __LINE__, event.version);
		वापस -EIO;
	पूर्ण

	चयन (event.type) अणु
	हाल PS3_SM_EVENT_POWER_PRESSED:
		dev_dbg(&dev->core, "%s:%d: POWER_PRESSED (%s)\n",
			__func__, __LINE__,
			(event.value == PS3_SM_BUTTON_EVENT_SOFT ? "soft"
			: "hard"));
		ps3_sm_क्रमce_घातer_off = 1;
		/*
		 * A memory barrier is use here to sync memory since
		 * ps3_sys_manager_final_restart() could be called on
		 * another cpu.
		 */
		wmb();
		समाप्त_cad_pid(संक_विघ्न, 1); /* ctrl_alt_del */
		अवरोध;
	हाल PS3_SM_EVENT_POWER_RELEASED:
		dev_dbg(&dev->core, "%s:%d: POWER_RELEASED (%u ms)\n",
			__func__, __LINE__, event.value);
		अवरोध;
	हाल PS3_SM_EVENT_RESET_PRESSED:
		dev_dbg(&dev->core, "%s:%d: RESET_PRESSED (%s)\n",
			__func__, __LINE__,
			(event.value == PS3_SM_BUTTON_EVENT_SOFT ? "soft"
			: "hard"));
		ps3_sm_क्रमce_घातer_off = 0;
		/*
		 * A memory barrier is use here to sync memory since
		 * ps3_sys_manager_final_restart() could be called on
		 * another cpu.
		 */
		wmb();
		समाप्त_cad_pid(संक_विघ्न, 1); /* ctrl_alt_del */
		अवरोध;
	हाल PS3_SM_EVENT_RESET_RELEASED:
		dev_dbg(&dev->core, "%s:%d: RESET_RELEASED (%u ms)\n",
			__func__, __LINE__, event.value);
		अवरोध;
	हाल PS3_SM_EVENT_THERMAL_ALERT:
		dev_dbg(&dev->core, "%s:%d: THERMAL_ALERT (zone %u)\n",
			__func__, __LINE__, event.value);
		pr_info("PS3 Thermal Alert Zone %u\n", event.value);
		अवरोध;
	हाल PS3_SM_EVENT_THERMAL_CLEARED:
		dev_dbg(&dev->core, "%s:%d: THERMAL_CLEARED (zone %u)\n",
			__func__, __LINE__, event.value);
		अवरोध;
	शेष:
		dev_dbg(&dev->core, "%s:%d: unknown event (%u)\n",
			__func__, __LINE__, event.type);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
/**
 * ps3_sys_manager_handle_cmd - Second stage command msg handler.
 *
 * The प्रणाली manager sends this in reply to a 'request' message from the guest.
 */

अटल पूर्णांक ps3_sys_manager_handle_cmd(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा अणु
		u8 version;
		u8 type;
		u8 reserved_1[14];
	पूर्ण cmd;

	BUILD_BUG_ON(माप(cmd) != 16);

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	result = ps3_vuart_पढ़ो(dev, &cmd, माप(cmd));
	BUG_ON(result && "need to retry here");

	अगर (result)
		वापस result;

	अगर (cmd.version != 1) अणु
		dev_dbg(&dev->core, "%s:%d: unsupported cmd version (%u)\n",
			__func__, __LINE__, cmd.version);
		वापस -EIO;
	पूर्ण

	अगर (cmd.type != PS3_SM_CMD_SHUTDOWN) अणु
		dev_dbg(&dev->core, "%s:%d: unknown cmd (%u)\n",
			__func__, __LINE__, cmd.type);
		वापस -EIO;
	पूर्ण

	ps3_sys_manager_send_response(dev, 0);
	वापस 0;
पूर्ण

/**
 * ps3_sys_manager_handle_msg - First stage msg handler.
 *
 * Can be called directly to manually poll vuart and pump message handler.
 */

अटल पूर्णांक ps3_sys_manager_handle_msg(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा ps3_sys_manager_header header;

	result = ps3_vuart_पढ़ो(dev, &header,
		माप(काष्ठा ps3_sys_manager_header));

	अगर (result)
		वापस result;

	अगर (header.version != 1) अणु
		dev_dbg(&dev->core, "%s:%d: unsupported header version (%u)\n",
			__func__, __LINE__, header.version);
		dump_sm_header(&header);
		जाओ fail_header;
	पूर्ण

	BUILD_BUG_ON(माप(header) != 16);

	अगर (header.size != 16 || (header.payload_size != 8
		&& header.payload_size != 16)) अणु
		dump_sm_header(&header);
		BUG();
	पूर्ण

	चयन (header.service_id) अणु
	हाल PS3_SM_SERVICE_ID_EXTERN_EVENT:
		dev_dbg(&dev->core, "%s:%d: EVENT\n", __func__, __LINE__);
		वापस ps3_sys_manager_handle_event(dev);
	हाल PS3_SM_SERVICE_ID_COMMAND:
		dev_dbg(&dev->core, "%s:%d: COMMAND\n", __func__, __LINE__);
		वापस ps3_sys_manager_handle_cmd(dev);
	हाल PS3_SM_SERVICE_ID_REQUEST_ERROR:
		dev_dbg(&dev->core, "%s:%d: REQUEST_ERROR\n", __func__,
			__LINE__);
		dump_sm_header(&header);
		अवरोध;
	शेष:
		dev_dbg(&dev->core, "%s:%d: unknown service_id (%u)\n",
			__func__, __LINE__, header.service_id);
		अवरोध;
	पूर्ण
	जाओ fail_id;

fail_header:
	ps3_vuart_clear_rx_bytes(dev, 0);
	वापस -EIO;
fail_id:
	ps3_vuart_clear_rx_bytes(dev, header.payload_size);
	वापस -EIO;
पूर्ण

अटल व्योम ps3_sys_manager_fin(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	ps3_sys_manager_send_request_shutकरोwn(dev);

	pr_emerg("System Halted, OK to turn off power\n");

	जबतक (ps3_sys_manager_handle_msg(dev)) अणु
		/* छोड़ो until next DEC पूर्णांकerrupt */
		lv1_छोड़ो(0);
	पूर्ण

	जबतक (1) अणु
		/* छोड़ो, ignoring DEC पूर्णांकerrupt */
		lv1_छोड़ो(1);
	पूर्ण
पूर्ण

/**
 * ps3_sys_manager_final_घातer_off - The final platक्रमm machine_घातer_off routine.
 *
 * This routine never वापसs.  The routine disables asynchronous vuart पढ़ोs
 * then spins calling ps3_sys_manager_handle_msg() to receive and acknowledge
 * the shutकरोwn command sent from the प्रणाली manager.  Soon after the
 * acknowledgement is sent the lpar is destroyed by the HV.  This routine
 * should only be called from ps3_घातer_off() through
 * ps3_sys_manager_ops.घातer_off.
 */

अटल व्योम ps3_sys_manager_final_घातer_off(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	BUG_ON(!dev);

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	ps3_vuart_cancel_async(dev);

	ps3_sys_manager_send_next_op(dev, PS3_SM_NEXT_OP_SYS_SHUTDOWN,
		user_wake_sources);

	ps3_sys_manager_fin(dev);
पूर्ण

/**
 * ps3_sys_manager_final_restart - The final platक्रमm machine_restart routine.
 *
 * This routine never वापसs.  The routine disables asynchronous vuart पढ़ोs
 * then spins calling ps3_sys_manager_handle_msg() to receive and acknowledge
 * the shutकरोwn command sent from the प्रणाली manager.  Soon after the
 * acknowledgement is sent the lpar is destroyed by the HV.  This routine
 * should only be called from ps3_restart() through ps3_sys_manager_ops.restart.
 */

अटल व्योम ps3_sys_manager_final_restart(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	BUG_ON(!dev);

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	/* Check अगर we got here via a घातer button event. */

	अगर (ps3_sm_क्रमce_घातer_off) अणु
		dev_dbg(&dev->core, "%s:%d: forcing poweroff\n",
			__func__, __LINE__);
		ps3_sys_manager_final_घातer_off(dev);
	पूर्ण

	ps3_vuart_cancel_async(dev);

	ps3_sys_manager_send_attr(dev, 0);
	ps3_sys_manager_send_next_op(dev, PS3_SM_NEXT_OP_SYS_REBOOT,
		user_wake_sources);

	ps3_sys_manager_fin(dev);
पूर्ण

/**
 * ps3_sys_manager_get_wol - Get wake-on-lan setting.
 */

पूर्णांक ps3_sys_manager_get_wol(व्योम)
अणु
	pr_debug("%s:%d\n", __func__, __LINE__);

	वापस (user_wake_sources & PS3_SM_WAKE_W_O_L) != 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_sys_manager_get_wol);

/**
 * ps3_sys_manager_set_wol - Set wake-on-lan setting.
 */

व्योम ps3_sys_manager_set_wol(पूर्णांक state)
अणु
	अटल DEFINE_MUTEX(mutex);

	mutex_lock(&mutex);

	pr_debug("%s:%d: %d\n", __func__, __LINE__, state);

	अगर (state)
		user_wake_sources |= PS3_SM_WAKE_W_O_L;
	अन्यथा
		user_wake_sources &= ~PS3_SM_WAKE_W_O_L;
	mutex_unlock(&mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_sys_manager_set_wol);

/**
 * ps3_sys_manager_work - Asynchronous पढ़ो handler.
 *
 * Signaled when PS3_SM_RX_MSG_LEN_MIN bytes arrive at the vuart port.
 */

अटल व्योम ps3_sys_manager_work(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	ps3_sys_manager_handle_msg(dev);
	ps3_vuart_पढ़ो_async(dev, PS3_SM_RX_MSG_LEN_MIN);
पूर्ण

अटल पूर्णांक ps3_sys_manager_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा ps3_sys_manager_ops ops;

	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);

	ops.घातer_off = ps3_sys_manager_final_घातer_off;
	ops.restart = ps3_sys_manager_final_restart;
	ops.dev = dev;

	/* ps3_sys_manager_रेजिस्टर_ops copies ops. */

	ps3_sys_manager_रेजिस्टर_ops(&ops);

	result = ps3_sys_manager_send_attr(dev, PS3_SM_ATTR_ALL);
	BUG_ON(result);

	result = ps3_vuart_पढ़ो_async(dev, PS3_SM_RX_MSG_LEN_MIN);
	BUG_ON(result);

	वापस result;
पूर्ण

अटल पूर्णांक ps3_sys_manager_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);
	वापस 0;
पूर्ण

अटल व्योम ps3_sys_manager_shutकरोwn(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, "%s:%d\n", __func__, __LINE__);
पूर्ण

अटल काष्ठा ps3_vuart_port_driver ps3_sys_manager = अणु
	.core.match_id = PS3_MATCH_ID_SYSTEM_MANAGER,
	.core.core.name = "ps3_sys_manager",
	.probe = ps3_sys_manager_probe,
	.हटाओ = ps3_sys_manager_हटाओ,
	.shutकरोwn = ps3_sys_manager_shutकरोwn,
	.work = ps3_sys_manager_work,
पूर्ण;

अटल पूर्णांक __init ps3_sys_manager_init(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	वापस ps3_vuart_port_driver_रेजिस्टर(&ps3_sys_manager);
पूर्ण

module_init(ps3_sys_manager_init);
/* Module हटाओ not supported. */

MODULE_AUTHOR("Sony Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PS3 System Manager");
MODULE_ALIAS(PS3_MODULE_ALIAS_SYSTEM_MANAGER);
