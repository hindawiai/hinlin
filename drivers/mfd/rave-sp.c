<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Multअगरunction core driver क्रम Zodiac Inflight Innovations RAVE
 * Supervisory Processor(SP) MCU that is connected via dedicated UART
 * port
 *
 * Copyright (C) 2017 Zodiac Inflight Innovations
 */

#समावेश <linux/atomic.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rave-sp.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/serdev.h>
#समावेश <यंत्र/unaligned.h>

/*
 * UART protocol using following entities:
 *  - message to MCU => ACK response
 *  - event from MCU => event ACK
 *
 * Frame काष्ठाure:
 * <STX> <DATA> <CHECKSUM> <ETX>
 * Where:
 * - STX - is start of transmission अक्षरacter
 * - ETX - end of transmission
 * - DATA - payload
 * - CHECKSUM - checksum calculated on <DATA>
 *
 * If <DATA> or <CHECKSUM> contain one of control अक्षरacters, then it is
 * escaped using <DLE> control code. Added <DLE> करोes not participate in
 * checksum calculation.
 */
#घोषणा RAVE_SP_STX			0x02
#घोषणा RAVE_SP_ETX			0x03
#घोषणा RAVE_SP_DLE			0x10

#घोषणा RAVE_SP_MAX_DATA_SIZE		64
#घोषणा RAVE_SP_CHECKSUM_8B2C		1
#घोषणा RAVE_SP_CHECKSUM_CCITT		2
#घोषणा RAVE_SP_CHECKSUM_SIZE		RAVE_SP_CHECKSUM_CCITT
/*
 * We करोn't store STX, ETX and unescaped bytes, so Rx is only
 * DATA + CSUM
 */
#घोषणा RAVE_SP_RX_BUFFER_SIZE				\
	(RAVE_SP_MAX_DATA_SIZE + RAVE_SP_CHECKSUM_SIZE)

#घोषणा RAVE_SP_STX_ETX_SIZE		2
/*
 * For Tx we have to have space क्रम everything, STX, EXT and
 * potentially stuffed DATA + CSUM data + csum
 */
#घोषणा RAVE_SP_TX_BUFFER_SIZE				\
	(RAVE_SP_STX_ETX_SIZE + 2 * RAVE_SP_RX_BUFFER_SIZE)

/**
 * क्रमागत rave_sp_deframer_state - Possible state क्रम de-framer
 *
 * @RAVE_SP_EXPECT_SOF:		 Scanning input क्रम start-of-frame marker
 * @RAVE_SP_EXPECT_DATA:	 Got start of frame marker, collecting frame
 * @RAVE_SP_EXPECT_ESCAPED_DATA: Got escape अक्षरacter, collecting escaped byte
 */
क्रमागत rave_sp_deframer_state अणु
	RAVE_SP_EXPECT_SOF,
	RAVE_SP_EXPECT_DATA,
	RAVE_SP_EXPECT_ESCAPED_DATA,
पूर्ण;

/**
 * काष्ठा rave_sp_deframer - Device protocol deframer
 *
 * @state:  Current state of the deframer
 * @data:   Buffer used to collect deframed data
 * @length: Number of bytes de-framed so far
 */
काष्ठा rave_sp_deframer अणु
	क्रमागत rave_sp_deframer_state state;
	अचिन्हित अक्षर data[RAVE_SP_RX_BUFFER_SIZE];
	माप_प्रकार length;
पूर्ण;

/**
 * काष्ठा rave_sp_reply - Reply as per RAVE device protocol
 *
 * @length:	Expected reply length
 * @data:	Buffer to store reply payload in
 * @code:	Expected reply code
 * @ackid:	Expected reply ACK ID
 * @received:   Successful reply reception completion
 */
काष्ठा rave_sp_reply अणु
	माप_प्रकार length;
	व्योम  *data;
	u8     code;
	u8     ackid;
	काष्ठा completion received;
पूर्ण;

/**
 * काष्ठा rave_sp_checksum - Variant specअगरic checksum implementation details
 *
 * @length:	Calculated checksum length
 * @subroutine:	Utilized checksum algorithm implementation
 */
काष्ठा rave_sp_checksum अणु
	माप_प्रकार length;
	व्योम (*subroutine)(स्थिर u8 *, माप_प्रकार, u8 *);
पूर्ण;

काष्ठा rave_sp_version अणु
	u8     hardware;
	__le16 major;
	u8     minor;
	u8     letter[2];
पूर्ण __packed;

काष्ठा rave_sp_status अणु
	काष्ठा rave_sp_version bootloader_version;
	काष्ठा rave_sp_version firmware_version;
	u16 rdu_eeprom_flag;
	u16 dds_eeprom_flag;
	u8  pic_flag;
	u8  orientation;
	u32 etc;
	s16 temp[2];
	u8  backlight_current[3];
	u8  dip_चयन;
	u8  host_पूर्णांकerrupt;
	u16 voltage_28;
	u8  i2c_device_status;
	u8  घातer_status;
	u8  general_status;
	u8  deprecated1;
	u8  घातer_led_status;
	u8  deprecated2;
	u8  periph_घातer_shutoff;
पूर्ण __packed;

/**
 * काष्ठा rave_sp_variant_cmds - Variant specअगरic command routines
 *
 * @translate:	Generic to variant specअगरic command mapping routine
 * @get_status: Variant specअगरic implementation of CMD_GET_STATUS
 */
काष्ठा rave_sp_variant_cmds अणु
	पूर्णांक (*translate)(क्रमागत rave_sp_command);
	पूर्णांक (*get_status)(काष्ठा rave_sp *sp, काष्ठा rave_sp_status *);
पूर्ण;

/**
 * काष्ठा rave_sp_variant - RAVE supervisory processor core variant
 *
 * @checksum:	Variant specअगरic checksum implementation
 * @cmd:	Variant specअगरic command poपूर्णांकer table
 *
 */
काष्ठा rave_sp_variant अणु
	स्थिर काष्ठा rave_sp_checksum *checksum;
	काष्ठा rave_sp_variant_cmds cmd;
पूर्ण;

/**
 * काष्ठा rave_sp - RAVE supervisory processor core
 *
 * @serdev:			Poपूर्णांकer to underlying serdev
 * @deframer:			Stored state of the protocol deframer
 * @ackid:			ACK ID used in last reply sent to the device
 * @bus_lock:			Lock to serialize access to the device
 * @reply_lock:			Lock protecting @reply
 * @reply:			Poपूर्णांकer to memory to store reply payload
 *
 * @variant:			Device variant specअगरic inक्रमmation
 * @event_notअगरier_list:	Input event notअगरication chain
 *
 * @part_number_firmware:	Firmware version
 * @part_number_bootloader:	Bootloader version
 */
काष्ठा rave_sp अणु
	काष्ठा serdev_device *serdev;
	काष्ठा rave_sp_deframer deframer;
	atomic_t ackid;
	काष्ठा mutex bus_lock;
	काष्ठा mutex reply_lock;
	काष्ठा rave_sp_reply *reply;

	स्थिर काष्ठा rave_sp_variant *variant;
	काष्ठा blocking_notअगरier_head event_notअगरier_list;

	स्थिर अक्षर *part_number_firmware;
	स्थिर अक्षर *part_number_bootloader;
पूर्ण;

अटल bool rave_sp_id_is_event(u8 code)
अणु
	वापस (code & 0xF0) == RAVE_SP_EVNT_BASE;
पूर्ण

अटल व्योम rave_sp_unरेजिस्टर_event_notअगरier(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा rave_sp *sp = dev_get_drvdata(dev->parent);
	काष्ठा notअगरier_block *nb = *(काष्ठा notअगरier_block **)res;
	काष्ठा blocking_notअगरier_head *bnh = &sp->event_notअगरier_list;

	WARN_ON(blocking_notअगरier_chain_unरेजिस्टर(bnh, nb));
पूर्ण

पूर्णांक devm_rave_sp_रेजिस्टर_event_notअगरier(काष्ठा device *dev,
					 काष्ठा notअगरier_block *nb)
अणु
	काष्ठा rave_sp *sp = dev_get_drvdata(dev->parent);
	काष्ठा notअगरier_block **rcnb;
	पूर्णांक ret;

	rcnb = devres_alloc(rave_sp_unरेजिस्टर_event_notअगरier,
			    माप(*rcnb), GFP_KERNEL);
	अगर (!rcnb)
		वापस -ENOMEM;

	ret = blocking_notअगरier_chain_रेजिस्टर(&sp->event_notअगरier_list, nb);
	अगर (!ret) अणु
		*rcnb = nb;
		devres_add(dev, rcnb);
	पूर्ण अन्यथा अणु
		devres_मुक्त(rcnb);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_rave_sp_रेजिस्टर_event_notअगरier);

अटल व्योम csum_8b2c(स्थिर u8 *buf, माप_प्रकार size, u8 *crc)
अणु
	*crc = *buf++;
	size--;

	जबतक (size--)
		*crc += *buf++;

	*crc = 1 + ~(*crc);
पूर्ण

अटल व्योम csum_ccitt(स्थिर u8 *buf, माप_प्रकार size, u8 *crc)
अणु
	स्थिर u16 calculated = crc_ccitt_false(0xffff, buf, size);

	/*
	 * While the rest of the wire protocol is little-endian,
	 * CCITT-16 CRC in RDU2 device is sent out in big-endian order.
	 */
	put_unaligned_be16(calculated, crc);
पूर्ण

अटल व्योम *stuff(अचिन्हित अक्षर *dest, स्थिर अचिन्हित अक्षर *src, माप_प्रकार n)
अणु
	जबतक (n--) अणु
		स्थिर अचिन्हित अक्षर byte = *src++;

		चयन (byte) अणु
		हाल RAVE_SP_STX:
		हाल RAVE_SP_ETX:
		हाल RAVE_SP_DLE:
			*dest++ = RAVE_SP_DLE;
			fallthrough;
		शेष:
			*dest++ = byte;
		पूर्ण
	पूर्ण

	वापस dest;
पूर्ण

अटल पूर्णांक rave_sp_ग_लिखो(काष्ठा rave_sp *sp, स्थिर u8 *data, u8 data_size)
अणु
	स्थिर माप_प्रकार checksum_length = sp->variant->checksum->length;
	अचिन्हित अक्षर frame[RAVE_SP_TX_BUFFER_SIZE];
	अचिन्हित अक्षर crc[RAVE_SP_CHECKSUM_SIZE];
	अचिन्हित अक्षर *dest = frame;
	माप_प्रकार length;

	अगर (WARN_ON(checksum_length > माप(crc)))
		वापस -ENOMEM;

	अगर (WARN_ON(data_size > माप(frame)))
		वापस -ENOMEM;

	sp->variant->checksum->subroutine(data, data_size, crc);

	*dest++ = RAVE_SP_STX;
	dest = stuff(dest, data, data_size);
	dest = stuff(dest, crc, checksum_length);
	*dest++ = RAVE_SP_ETX;

	length = dest - frame;

	prपूर्णांक_hex_dump_debug("rave-sp tx: ", DUMP_PREFIX_NONE,
			     16, 1, frame, length, false);

	वापस serdev_device_ग_लिखो(sp->serdev, frame, length, HZ);
पूर्ण

अटल u8 rave_sp_reply_code(u8 command)
अणु
	/*
	 * There isn't a single rule that describes command code ->
	 * ACK code transक्रमmation, but, going through various
	 * versions of ICDs, there appear to be three distinct groups
	 * that can be described by simple transक्रमmation.
	 */
	चयन (command) अणु
	हाल 0xA0 ... 0xBE:
		/*
		 * Commands implemented by firmware found in RDU1 and
		 * older devices all seem to obey the following rule
		 */
		वापस command + 0x20;
	हाल 0xE0 ... 0xEF:
		/*
		 * Events emitted by all versions of the firmare use
		 * least signअगरicant bit to get an ACK code
		 */
		वापस command | 0x01;
	शेष:
		/*
		 * Commands implemented by firmware found in RDU2 are
		 * similar to "old" commands, but they use slightly
		 * dअगरferent offset
		 */
		वापस command + 0x40;
	पूर्ण
पूर्ण

पूर्णांक rave_sp_exec(काष्ठा rave_sp *sp,
		 व्योम *__data,  माप_प्रकार data_size,
		 व्योम *reply_data, माप_प्रकार reply_data_size)
अणु
	काष्ठा rave_sp_reply reply = अणु
		.data     = reply_data,
		.length   = reply_data_size,
		.received = COMPLETION_INITIALIZER_ONSTACK(reply.received),
	पूर्ण;
	अचिन्हित अक्षर *data = __data;
	पूर्णांक command, ret = 0;
	u8 ackid;

	command = sp->variant->cmd.translate(data[0]);
	अगर (command < 0)
		वापस command;

	ackid       = atomic_inc_वापस(&sp->ackid);
	reply.ackid = ackid;
	reply.code  = rave_sp_reply_code((u8)command),

	mutex_lock(&sp->bus_lock);

	mutex_lock(&sp->reply_lock);
	sp->reply = &reply;
	mutex_unlock(&sp->reply_lock);

	data[0] = command;
	data[1] = ackid;

	rave_sp_ग_लिखो(sp, data, data_size);

	अगर (!रुको_क्रम_completion_समयout(&reply.received, HZ)) अणु
		dev_err(&sp->serdev->dev, "Command timeout\n");
		ret = -ETIMEDOUT;

		mutex_lock(&sp->reply_lock);
		sp->reply = शून्य;
		mutex_unlock(&sp->reply_lock);
	पूर्ण

	mutex_unlock(&sp->bus_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rave_sp_exec);

अटल व्योम rave_sp_receive_event(काष्ठा rave_sp *sp,
				  स्थिर अचिन्हित अक्षर *data, माप_प्रकार length)
अणु
	u8 cmd[] = अणु
		[0] = rave_sp_reply_code(data[0]),
		[1] = data[1],
	पूर्ण;

	rave_sp_ग_लिखो(sp, cmd, माप(cmd));

	blocking_notअगरier_call_chain(&sp->event_notअगरier_list,
				     rave_sp_action_pack(data[0], data[2]),
				     शून्य);
पूर्ण

अटल व्योम rave_sp_receive_reply(काष्ठा rave_sp *sp,
				  स्थिर अचिन्हित अक्षर *data, माप_प्रकार length)
अणु
	काष्ठा device *dev = &sp->serdev->dev;
	काष्ठा rave_sp_reply *reply;
	स्थिर  माप_प्रकार payload_length = length - 2;

	mutex_lock(&sp->reply_lock);
	reply = sp->reply;

	अगर (reply) अणु
		अगर (reply->code == data[0] && reply->ackid == data[1] &&
		    payload_length >= reply->length) अणु
			/*
			 * We are relying on स_नकल(dst, src, 0) to be a no-op
			 * when handling commands that have a no-payload reply
			 */
			स_नकल(reply->data, &data[2], reply->length);
			complete(&reply->received);
			sp->reply = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Ignoring incorrect reply\n");
			dev_dbg(dev, "Code:   expected = 0x%08x received = 0x%08x\n",
				reply->code, data[0]);
			dev_dbg(dev, "ACK ID: expected = 0x%08x received = 0x%08x\n",
				reply->ackid, data[1]);
			dev_dbg(dev, "Length: expected = %zu received = %zu\n",
				reply->length, payload_length);
		पूर्ण
	पूर्ण

	mutex_unlock(&sp->reply_lock);
पूर्ण

अटल व्योम rave_sp_receive_frame(काष्ठा rave_sp *sp,
				  स्थिर अचिन्हित अक्षर *data,
				  माप_प्रकार length)
अणु
	स्थिर माप_प्रकार checksum_length = sp->variant->checksum->length;
	स्थिर माप_प्रकार payload_length  = length - checksum_length;
	स्थिर u8 *crc_reported       = &data[payload_length];
	काष्ठा device *dev           = &sp->serdev->dev;
	u8 crc_calculated[RAVE_SP_CHECKSUM_SIZE];

	अगर (unlikely(checksum_length > माप(crc_calculated))) अणु
		dev_warn(dev, "Checksum too long, dropping\n");
		वापस;
	पूर्ण

	prपूर्णांक_hex_dump_debug("rave-sp rx: ", DUMP_PREFIX_NONE,
			     16, 1, data, length, false);

	अगर (unlikely(length <= checksum_length)) अणु
		dev_warn(dev, "Dropping short frame\n");
		वापस;
	पूर्ण

	sp->variant->checksum->subroutine(data, payload_length,
					  crc_calculated);

	अगर (स_भेद(crc_calculated, crc_reported, checksum_length)) अणु
		dev_warn(dev, "Dropping bad frame\n");
		वापस;
	पूर्ण

	अगर (rave_sp_id_is_event(data[0]))
		rave_sp_receive_event(sp, data, length);
	अन्यथा
		rave_sp_receive_reply(sp, data, length);
पूर्ण

अटल पूर्णांक rave_sp_receive_buf(काष्ठा serdev_device *serdev,
			       स्थिर अचिन्हित अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा device *dev = &serdev->dev;
	काष्ठा rave_sp *sp = dev_get_drvdata(dev);
	काष्ठा rave_sp_deframer *deframer = &sp->deframer;
	स्थिर अचिन्हित अक्षर *src = buf;
	स्थिर अचिन्हित अक्षर *end = buf + size;

	जबतक (src < end) अणु
		स्थिर अचिन्हित अक्षर byte = *src++;

		चयन (deframer->state) अणु
		हाल RAVE_SP_EXPECT_SOF:
			अगर (byte == RAVE_SP_STX)
				deframer->state = RAVE_SP_EXPECT_DATA;
			अवरोध;

		हाल RAVE_SP_EXPECT_DATA:
			/*
			 * Treat special byte values first
			 */
			चयन (byte) अणु
			हाल RAVE_SP_ETX:
				rave_sp_receive_frame(sp,
						      deframer->data,
						      deframer->length);
				/*
				 * Once we extracted a complete frame
				 * out of a stream, we call it करोne
				 * and proceed to bailing out जबतक
				 * resetting the framer to initial
				 * state, regardless अगर we've consumed
				 * all of the stream or not.
				 */
				जाओ reset_framer;
			हाल RAVE_SP_STX:
				dev_warn(dev, "Bad frame: STX before ETX\n");
				/*
				 * If we encounter second "start of
				 * the frame" marker beक्रमe seeing
				 * corresponding "end of frame", we
				 * reset the framer and ignore both:
				 * frame started by first SOF and
				 * frame started by current SOF.
				 *
				 * NOTE: The above means that only the
				 * frame started by third SOF, sent
				 * after this one will have a chance
				 * to get throught.
				 */
				जाओ reset_framer;
			हाल RAVE_SP_DLE:
				deframer->state = RAVE_SP_EXPECT_ESCAPED_DATA;
				/*
				 * If we encounter escape sequence we
				 * need to skip it and collect the
				 * byte that follows. We करो it by
				 * क्रमcing the next iteration of the
				 * encompassing जबतक loop.
				 */
				जारी;
			पूर्ण
			/*
			 * For the rest of the bytes, that are not
			 * speical snoflakes, we करो the same thing
			 * that we करो to escaped data - collect it in
			 * deframer buffer
			 */

			fallthrough;

		हाल RAVE_SP_EXPECT_ESCAPED_DATA:
			अगर (deframer->length == माप(deframer->data)) अणु
				dev_warn(dev, "Bad frame: Too long\n");
				/*
				 * If the amount of data we've
				 * accumulated क्रम current frame so
				 * far starts to exceed the capacity
				 * of deframer's buffer, there's
				 * nothing अन्यथा we can करो but to
				 * discard that data and start
				 * assemblying a new frame again
				 */
				जाओ reset_framer;
			पूर्ण

			deframer->data[deframer->length++] = byte;

			/*
			 * We've extracted out special byte, now we
			 * can go back to regular data collecting
			 */
			deframer->state = RAVE_SP_EXPECT_DATA;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The only way to get out of the above loop and end up here
	 * is throught consuming all of the supplied data, so here we
	 * report that we processed it all.
	 */
	वापस size;

reset_framer:
	/*
	 * NOTE: A number of codepaths that will drop us here will करो
	 * so beक्रमe consuming all 'size' bytes of the data passed by
	 * serdev layer. We rely on the fact that serdev layer will
	 * re-execute this handler with the reमुख्यder of the Rx bytes
	 * once we report actual number of bytes that we processed.
	 */
	deframer->state  = RAVE_SP_EXPECT_SOF;
	deframer->length = 0;

	वापस src - buf;
पूर्ण

अटल पूर्णांक rave_sp_rdu1_cmd_translate(क्रमागत rave_sp_command command)
अणु
	अगर (command >= RAVE_SP_CMD_STATUS &&
	    command <= RAVE_SP_CMD_CONTROL_EVENTS)
		वापस command;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rave_sp_rdu2_cmd_translate(क्रमागत rave_sp_command command)
अणु
	अगर (command >= RAVE_SP_CMD_GET_FIRMWARE_VERSION &&
	    command <= RAVE_SP_CMD_GET_GPIO_STATE)
		वापस command;

	अगर (command == RAVE_SP_CMD_REQ_COPPER_REV) अणु
		/*
		 * As per RDU2 ICD 3.4.47 CMD_GET_COPPER_REV code is
		 * dअगरferent from that क्रम RDU1 and it is set to 0x28.
		 */
		वापस 0x28;
	पूर्ण

	वापस rave_sp_rdu1_cmd_translate(command);
पूर्ण

अटल पूर्णांक rave_sp_शेष_cmd_translate(क्रमागत rave_sp_command command)
अणु
	/*
	 * All of the following command codes were taken from "Table :
	 * Communications Protocol Message Types" in section 3.3
	 * "MESSAGE TYPES" of Rave PIC24 ICD.
	 */
	चयन (command) अणु
	हाल RAVE_SP_CMD_GET_FIRMWARE_VERSION:
		वापस 0x11;
	हाल RAVE_SP_CMD_GET_BOOTLOADER_VERSION:
		वापस 0x12;
	हाल RAVE_SP_CMD_BOOT_SOURCE:
		वापस 0x14;
	हाल RAVE_SP_CMD_SW_WDT:
		वापस 0x1C;
	हाल RAVE_SP_CMD_PET_WDT:
		वापस 0x1D;
	हाल RAVE_SP_CMD_RESET:
		वापस 0x1E;
	हाल RAVE_SP_CMD_RESET_REASON:
		वापस 0x1F;
	हाल RAVE_SP_CMD_RMB_EEPROM:
		वापस 0x20;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *devm_rave_sp_version(काष्ठा device *dev,
					काष्ठा rave_sp_version *version)
अणु
	/*
	 * NOTE: The क्रमmat string below uses %02d to display u16
	 * पूर्णांकentionally क्रम the sake of backwards compatibility with
	 * legacy software.
	 */
	वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "%02d%02d%02d.%c%c\n",
			      version->hardware,
			      le16_to_cpu(version->major),
			      version->minor,
			      version->letter[0],
			      version->letter[1]);
पूर्ण

अटल पूर्णांक rave_sp_rdu1_get_status(काष्ठा rave_sp *sp,
				   काष्ठा rave_sp_status *status)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_STATUS,
		[1] = 0
	पूर्ण;

	वापस rave_sp_exec(sp, cmd, माप(cmd), status, माप(*status));
पूर्ण

अटल पूर्णांक rave_sp_emulated_get_status(काष्ठा rave_sp *sp,
				       काष्ठा rave_sp_status *status)
अणु
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_GET_FIRMWARE_VERSION,
		[1] = 0,
	पूर्ण;
	पूर्णांक ret;

	ret = rave_sp_exec(sp, cmd, माप(cmd), &status->firmware_version,
			   माप(status->firmware_version));
	अगर (ret)
		वापस ret;

	cmd[0] = RAVE_SP_CMD_GET_BOOTLOADER_VERSION;
	वापस rave_sp_exec(sp, cmd, माप(cmd), &status->bootloader_version,
			    माप(status->bootloader_version));
पूर्ण

अटल पूर्णांक rave_sp_get_status(काष्ठा rave_sp *sp)
अणु
	काष्ठा device *dev = &sp->serdev->dev;
	काष्ठा rave_sp_status status;
	स्थिर अक्षर *version;
	पूर्णांक ret;

	ret = sp->variant->cmd.get_status(sp, &status);
	अगर (ret)
		वापस ret;

	version = devm_rave_sp_version(dev, &status.firmware_version);
	अगर (!version)
		वापस -ENOMEM;

	sp->part_number_firmware = version;

	version = devm_rave_sp_version(dev, &status.bootloader_version);
	अगर (!version)
		वापस -ENOMEM;

	sp->part_number_bootloader = version;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rave_sp_checksum rave_sp_checksum_8b2c = अणु
	.length     = 1,
	.subroutine = csum_8b2c,
पूर्ण;

अटल स्थिर काष्ठा rave_sp_checksum rave_sp_checksum_ccitt = अणु
	.length     = 2,
	.subroutine = csum_ccitt,
पूर्ण;

अटल स्थिर काष्ठा rave_sp_variant rave_sp_legacy = अणु
	.checksum = &rave_sp_checksum_ccitt,
	.cmd = अणु
		.translate = rave_sp_शेष_cmd_translate,
		.get_status = rave_sp_emulated_get_status,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rave_sp_variant rave_sp_rdu1 = अणु
	.checksum = &rave_sp_checksum_8b2c,
	.cmd = अणु
		.translate = rave_sp_rdu1_cmd_translate,
		.get_status = rave_sp_rdu1_get_status,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rave_sp_variant rave_sp_rdu2 = अणु
	.checksum = &rave_sp_checksum_ccitt,
	.cmd = अणु
		.translate = rave_sp_rdu2_cmd_translate,
		.get_status = rave_sp_emulated_get_status,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rave_sp_dt_ids[] = अणु
	अणु .compatible = "zii,rave-sp-niu",  .data = &rave_sp_legacy पूर्ण,
	अणु .compatible = "zii,rave-sp-mezz", .data = &rave_sp_legacy पूर्ण,
	अणु .compatible = "zii,rave-sp-esb",  .data = &rave_sp_legacy पूर्ण,
	अणु .compatible = "zii,rave-sp-rdu1", .data = &rave_sp_rdu1   पूर्ण,
	अणु .compatible = "zii,rave-sp-rdu2", .data = &rave_sp_rdu2   पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा serdev_device_ops rave_sp_serdev_device_ops = अणु
	.receive_buf  = rave_sp_receive_buf,
	.ग_लिखो_wakeup = serdev_device_ग_लिखो_wakeup,
पूर्ण;

अटल पूर्णांक rave_sp_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा device *dev = &serdev->dev;
	स्थिर अक्षर *unknown = "unknown\n";
	काष्ठा rave_sp *sp;
	u32 baud;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(dev->of_node, "current-speed", &baud)) अणु
		dev_err(dev,
			"'current-speed' is not specified in device node\n");
		वापस -EINVAL;
	पूर्ण

	sp = devm_kzalloc(dev, माप(*sp), GFP_KERNEL);
	अगर (!sp)
		वापस -ENOMEM;

	sp->serdev = serdev;
	dev_set_drvdata(dev, sp);

	sp->variant = of_device_get_match_data(dev);
	अगर (!sp->variant)
		वापस -ENODEV;

	mutex_init(&sp->bus_lock);
	mutex_init(&sp->reply_lock);
	BLOCKING_INIT_NOTIFIER_HEAD(&sp->event_notअगरier_list);

	serdev_device_set_client_ops(serdev, &rave_sp_serdev_device_ops);
	ret = devm_serdev_device_खोलो(dev, serdev);
	अगर (ret)
		वापस ret;

	serdev_device_set_baudrate(serdev, baud);
	serdev_device_set_flow_control(serdev, false);

	ret = serdev_device_set_parity(serdev, SERDEV_PARITY_NONE);
	अगर (ret) अणु
		dev_err(dev, "Failed to set parity\n");
		वापस ret;
	पूर्ण

	ret = rave_sp_get_status(sp);
	अगर (ret) अणु
		dev_warn(dev, "Failed to get firmware status: %d\n", ret);
		sp->part_number_firmware   = unknown;
		sp->part_number_bootloader = unknown;
	पूर्ण

	/*
	 * Those strings alपढ़ोy have a \न embedded, so there's no
	 * need to have one in क्रमmat string.
	 */
	dev_info(dev, "Firmware version: %s",   sp->part_number_firmware);
	dev_info(dev, "Bootloader version: %s", sp->part_number_bootloader);

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

MODULE_DEVICE_TABLE(of, rave_sp_dt_ids);

अटल काष्ठा serdev_device_driver rave_sp_drv = अणु
	.probe			= rave_sp_probe,
	.driver = अणु
		.name		= "rave-sp",
		.of_match_table	= rave_sp_dt_ids,
	पूर्ण,
पूर्ण;
module_serdev_device_driver(rave_sp_drv);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Vostrikov <andrey.vostrikov@cogentembedded.com>");
MODULE_AUTHOR("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("RAVE SP core driver");
