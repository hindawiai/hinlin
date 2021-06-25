<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ChromeOS Wilco Embedded Controller
 *
 * Copyright 2018 Google LLC
 */

#अगर_अघोषित WILCO_EC_H
#घोषणा WILCO_EC_H

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

/* Message flags क्रम using the mailbox() पूर्णांकerface */
#घोषणा WILCO_EC_FLAG_NO_RESPONSE	BIT(0) /* EC करोes not respond */

/* Normal commands have a maximum 32 bytes of data */
#घोषणा EC_MAILBOX_DATA_SIZE		32

काष्ठा device;
काष्ठा resource;
काष्ठा platक्रमm_device;

/**
 * काष्ठा wilco_ec_device - Wilco Embedded Controller handle.
 * @dev: Device handle.
 * @mailbox_lock: Mutex to ensure one mailbox command at a समय.
 * @io_command: I/O port क्रम mailbox command.  Provided by ACPI.
 * @io_data: I/O port क्रम mailbox data.  Provided by ACPI.
 * @io_packet: I/O port क्रम mailbox packet data.  Provided by ACPI.
 * @data_buffer: Buffer used क्रम EC communication.  The same buffer
 *               is used to hold the request and the response.
 * @data_size: Size of the data buffer used क्रम EC communication.
 * @debugfs_pdev: The child platक्रमm_device used by the debugfs sub-driver.
 * @rtc_pdev: The child platक्रमm_device used by the RTC sub-driver.
 * @अक्षरger_pdev: Child platक्रमm_device used by the अक्षरger config sub-driver.
 * @telem_pdev: The child platक्रमm_device used by the telemetry sub-driver.
 */
काष्ठा wilco_ec_device अणु
	काष्ठा device *dev;
	काष्ठा mutex mailbox_lock;
	काष्ठा resource *io_command;
	काष्ठा resource *io_data;
	काष्ठा resource *io_packet;
	व्योम *data_buffer;
	माप_प्रकार data_size;
	काष्ठा platक्रमm_device *debugfs_pdev;
	काष्ठा platक्रमm_device *rtc_pdev;
	काष्ठा platक्रमm_device *अक्षरger_pdev;
	काष्ठा platक्रमm_device *telem_pdev;
पूर्ण;

/**
 * काष्ठा wilco_ec_request - Mailbox request message क्रमmat.
 * @काष्ठा_version: Should be %EC_MAILBOX_PROTO_VERSION
 * @checksum: Sum of all bytes must be 0.
 * @mailbox_id: Mailbox identअगरier, specअगरies the command set.
 * @mailbox_version: Mailbox पूर्णांकerface version %EC_MAILBOX_VERSION
 * @reserved: Set to zero.
 * @data_size: Length of following data.
 */
काष्ठा wilco_ec_request अणु
	u8 काष्ठा_version;
	u8 checksum;
	u16 mailbox_id;
	u8 mailbox_version;
	u8 reserved;
	u16 data_size;
पूर्ण __packed;

/**
 * काष्ठा wilco_ec_response - Mailbox response message क्रमmat.
 * @काष्ठा_version: Should be %EC_MAILBOX_PROTO_VERSION
 * @checksum: Sum of all bytes must be 0.
 * @result: Result code from the EC.  Non-zero indicates an error.
 * @data_size: Length of the response data buffer.
 * @reserved: Set to zero.
 * @data: Response data buffer.  Max size is %EC_MAILBOX_DATA_SIZE_EXTENDED.
 */
काष्ठा wilco_ec_response अणु
	u8 काष्ठा_version;
	u8 checksum;
	u16 result;
	u16 data_size;
	u8 reserved[2];
	u8 data[];
पूर्ण __packed;

/**
 * क्रमागत wilco_ec_msg_type - Message type to select a set of command codes.
 * @WILCO_EC_MSG_LEGACY: Legacy EC messages क्रम standard EC behavior.
 * @WILCO_EC_MSG_PROPERTY: Get/Set/Sync EC controlled NVRAM property.
 * @WILCO_EC_MSG_TELEMETRY: Request telemetry data from the EC.
 */
क्रमागत wilco_ec_msg_type अणु
	WILCO_EC_MSG_LEGACY = 0x00f0,
	WILCO_EC_MSG_PROPERTY = 0x00f2,
	WILCO_EC_MSG_TELEMETRY = 0x00f5,
पूर्ण;

/**
 * काष्ठा wilco_ec_message - Request and response message.
 * @type: Mailbox message type.
 * @flags: Message flags, e.g. %WILCO_EC_FLAG_NO_RESPONSE.
 * @request_size: Number of bytes to send to the EC.
 * @request_data: Buffer containing the request data.
 * @response_size: Number of bytes to पढ़ो from EC.
 * @response_data: Buffer containing the response data, should be
 *                 response_size bytes and allocated by caller.
 */
काष्ठा wilco_ec_message अणु
	क्रमागत wilco_ec_msg_type type;
	u8 flags;
	माप_प्रकार request_size;
	व्योम *request_data;
	माप_प्रकार response_size;
	व्योम *response_data;
पूर्ण;

/**
 * wilco_ec_mailbox() - Send request to the EC and receive the response.
 * @ec: Wilco EC device.
 * @msg: Wilco EC message.
 *
 * Return: Number of bytes received or negative error code on failure.
 */
पूर्णांक wilco_ec_mailbox(काष्ठा wilco_ec_device *ec, काष्ठा wilco_ec_message *msg);

/**
 * wilco_keyboard_leds_init() - Set up the keyboard backlight LEDs.
 * @ec: EC device to query.
 *
 * After this call, the keyboard backlight will be exposed through a an LED
 * device at /sys/class/leds.
 *
 * This may sleep because it uses wilco_ec_mailbox().
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक wilco_keyboard_leds_init(काष्ठा wilco_ec_device *ec);

/*
 * A Property is typically a data item that is stored to NVRAM
 * by the EC. Each of these data items has an index associated
 * with it, known as the Property ID (PID). Properties may have
 * variable lengths, up to a max of WILCO_EC_PROPERTY_MAX_SIZE
 * bytes. Properties can be simple पूर्णांकegers, or they may be more
 * complex binary data.
 */

#घोषणा WILCO_EC_PROPERTY_MAX_SIZE	4

/**
 * काष्ठा ec_property_set_msg - Message to get or set a property.
 * @property_id: Which property to get or set.
 * @length: Number of bytes of |data| that are used.
 * @data: Actual property data.
 */
काष्ठा wilco_ec_property_msg अणु
	u32 property_id;
	पूर्णांक length;
	u8 data[WILCO_EC_PROPERTY_MAX_SIZE];
पूर्ण;

/**
 * wilco_ec_get_property() - Retrieve a property from the EC.
 * @ec: Embedded Controller device.
 * @prop_msg: Message क्रम request and response.
 *
 * The property_id field of |prop_msg| should be filled beक्रमe calling this
 * function. The result will be stored in the data and length fields.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक wilco_ec_get_property(काष्ठा wilco_ec_device *ec,
			  काष्ठा wilco_ec_property_msg *prop_msg);

/**
 * wilco_ec_set_property() - Store a property on the EC.
 * @ec: Embedded Controller device.
 * @prop_msg: Message क्रम request and response.
 *
 * The property_id, length, and data fields of |prop_msg| should be
 * filled beक्रमe calling this function.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक wilco_ec_set_property(काष्ठा wilco_ec_device *ec,
			  काष्ठा wilco_ec_property_msg *prop_msg);

/**
 * wilco_ec_get_byte_property() - Retrieve a byte-size property from the EC.
 * @ec: Embedded Controller device.
 * @property_id: Which property to retrieve.
 * @val: The result value, will be filled by this function.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक wilco_ec_get_byte_property(काष्ठा wilco_ec_device *ec, u32 property_id,
			       u8 *val);

/**
 * wilco_ec_get_byte_property() - Store a byte-size property on the EC.
 * @ec: Embedded Controller device.
 * @property_id: Which property to store.
 * @val: Value to store.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक wilco_ec_set_byte_property(काष्ठा wilco_ec_device *ec, u32 property_id,
			       u8 val);

/**
 * wilco_ec_add_sysfs() - Create sysfs entries
 * @ec: Wilco EC device
 *
 * wilco_ec_हटाओ_sysfs() needs to be called afterwards
 * to perक्रमm the necessary cleanup.
 *
 * Return: 0 on success or negative error code on failure.
 */
पूर्णांक wilco_ec_add_sysfs(काष्ठा wilco_ec_device *ec);
व्योम wilco_ec_हटाओ_sysfs(काष्ठा wilco_ec_device *ec);

#पूर्ण_अगर /* WILCO_EC_H */
