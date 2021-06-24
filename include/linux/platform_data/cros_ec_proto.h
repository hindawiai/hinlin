<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ChromeOS Embedded Controller protocol पूर्णांकerface.
 *
 * Copyright (C) 2012 Google, Inc
 */

#अगर_अघोषित __LINUX_CROS_EC_PROTO_H
#घोषणा __LINUX_CROS_EC_PROTO_H

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>

#समावेश <linux/platक्रमm_data/cros_ec_commands.h>

#घोषणा CROS_EC_DEV_NAME	"cros_ec"
#घोषणा CROS_EC_DEV_FP_NAME	"cros_fp"
#घोषणा CROS_EC_DEV_ISH_NAME	"cros_ish"
#घोषणा CROS_EC_DEV_PD_NAME	"cros_pd"
#घोषणा CROS_EC_DEV_SCP_NAME	"cros_scp"
#घोषणा CROS_EC_DEV_TP_NAME	"cros_tp"

/*
 * The EC is unresponsive क्रम a समय after a reboot command.  Add a
 * simple delay to make sure that the bus stays locked.
 */
#घोषणा EC_REBOOT_DELAY_MS		50

/*
 * Max bus-specअगरic overhead incurred by request/responses.
 * I2C requires 1 additional byte क्रम requests.
 * I2C requires 2 additional bytes क्रम responses.
 * SPI requires up to 32 additional bytes क्रम responses.
 */
#घोषणा EC_PROTO_VERSION_UNKNOWN	0
#घोषणा EC_MAX_REQUEST_OVERHEAD		1
#घोषणा EC_MAX_RESPONSE_OVERHEAD	32

/*
 * Command पूर्णांकerface between EC and AP, क्रम LPC, I2C and SPI पूर्णांकerfaces.
 */
क्रमागत अणु
	EC_MSG_TX_HEADER_BYTES	= 3,
	EC_MSG_TX_TRAILER_BYTES	= 1,
	EC_MSG_TX_PROTO_BYTES	= EC_MSG_TX_HEADER_BYTES +
				  EC_MSG_TX_TRAILER_BYTES,
	EC_MSG_RX_PROTO_BYTES	= 3,

	/* Max length of messages क्रम proto 2*/
	EC_PROTO2_MSG_BYTES	= EC_PROTO2_MAX_PARAM_SIZE +
				  EC_MSG_TX_PROTO_BYTES,

	EC_MAX_MSG_BYTES	= 64 * 1024,
पूर्ण;

/**
 * काष्ठा cros_ec_command - Inक्रमmation about a ChromeOS EC command.
 * @version: Command version number (often 0).
 * @command: Command to send (EC_CMD_...).
 * @outsize: Outgoing length in bytes.
 * @insize: Max number of bytes to accept from the EC.
 * @result: EC's response to the command (separate from communication failure).
 * @data: Where to put the incoming data from EC and outgoing data to EC.
 */
काष्ठा cros_ec_command अणु
	uपूर्णांक32_t version;
	uपूर्णांक32_t command;
	uपूर्णांक32_t outsize;
	uपूर्णांक32_t insize;
	uपूर्णांक32_t result;
	uपूर्णांक8_t data[];
पूर्ण;

/**
 * काष्ठा cros_ec_device - Inक्रमmation about a ChromeOS EC device.
 * @phys_name: Name of physical comms layer (e.g. 'i2c-4').
 * @dev: Device poपूर्णांकer क्रम physical comms device
 * @was_wake_device: True अगर this device was set to wake the प्रणाली from
 *                   sleep at the last suspend.
 * @cros_class: The class काष्ठाure क्रम this device.
 * @cmd_पढ़ोmem: Direct पढ़ो of the EC memory-mapped region, अगर supported.
 *     @offset: Is within EC_LPC_ADDR_MEMMAP region.
 *     @bytes: Number of bytes to पढ़ो. zero means "read a string" (including
 *             the trailing '\0'). At most only EC_MEMMAP_SIZE bytes can be
 *             पढ़ो. Caller must ensure that the buffer is large enough क्रम the
 *             result when पढ़ोing a string.
 * @max_request: Max size of message requested.
 * @max_response: Max size of message response.
 * @max_passthru: Max sice of passthru message.
 * @proto_version: The protocol version used क्रम this device.
 * @priv: Private data.
 * @irq: Interrupt to use.
 * @id: Device id.
 * @din: Input buffer (क्रम data from EC). This buffer will always be
 *       dword-aligned and include enough space क्रम up to 7 word-alignment
 *       bytes also, so we can ensure that the body of the message is always
 *       dword-aligned (64-bit). We use this alignment to keep ARM and x86
 *       happy. Probably word alignment would be OK, there might be a small
 *       perक्रमmance advantage to using dword.
 * @करोut: Output buffer (क्रम data to EC). This buffer will always be
 *        dword-aligned and include enough space क्रम up to 7 word-alignment
 *        bytes also, so we can ensure that the body of the message is always
 *        dword-aligned (64-bit). We use this alignment to keep ARM and x86
 *        happy. Probably word alignment would be OK, there might be a small
 *        perक्रमmance advantage to using dword.
 * @din_size: Size of din buffer to allocate (zero to use अटल din).
 * @करोut_size: Size of करोut buffer to allocate (zero to use अटल करोut).
 * @wake_enabled: True अगर this device can wake the प्रणाली from sleep.
 * @suspended: True अगर this device had been suspended.
 * @cmd_xfer: Send command to EC and get response.
 *            Returns the number of bytes received अगर the communication
 *            succeeded, but that करोesn't mean the EC was happy with the
 *            command. The caller should check msg.result क्रम the EC's result
 *            code.
 * @pkt_xfer: Send packet to EC and get response.
 * @lock: One transaction at a समय.
 * @mkbp_event_supported: 0 अगर MKBP not supported. Otherwise its value is
 *                        the maximum supported version of the MKBP host event
 *                        command + 1.
 * @host_sleep_v1: True अगर this EC supports the sleep v1 command.
 * @event_notअगरier: Interrupt event notअगरier क्रम transport devices.
 * @event_data: Raw payload transferred with the MKBP event.
 * @event_size: Size in bytes of the event data.
 * @host_event_wake_mask: Mask of host events that cause wake from suspend.
 * @last_event_समय: exact समय from the hard irq when we got notअगरied of
 *     a new event.
 * @notअगरier_पढ़ोy: The notअगरier_block to let the kernel re-query EC
 *		    communication protocol when the EC sends
 *		    EC_HOST_EVENT_INTERFACE_READY.
 * @ec: The platक्रमm_device used by the mfd driver to पूर्णांकerface with the
 *      मुख्य EC.
 * @pd: The platक्रमm_device used by the mfd driver to पूर्णांकerface with the
 *      PD behind an EC.
 */
काष्ठा cros_ec_device अणु
	/* These are used by other drivers that want to talk to the EC */
	स्थिर अक्षर *phys_name;
	काष्ठा device *dev;
	bool was_wake_device;
	काष्ठा class *cros_class;
	पूर्णांक (*cmd_पढ़ोmem)(काष्ठा cros_ec_device *ec, अचिन्हित पूर्णांक offset,
			   अचिन्हित पूर्णांक bytes, व्योम *dest);

	/* These are used to implement the platक्रमm-specअगरic पूर्णांकerface */
	u16 max_request;
	u16 max_response;
	u16 max_passthru;
	u16 proto_version;
	व्योम *priv;
	पूर्णांक irq;
	u8 *din;
	u8 *करोut;
	पूर्णांक din_size;
	पूर्णांक करोut_size;
	bool wake_enabled;
	bool suspended;
	पूर्णांक (*cmd_xfer)(काष्ठा cros_ec_device *ec,
			काष्ठा cros_ec_command *msg);
	पूर्णांक (*pkt_xfer)(काष्ठा cros_ec_device *ec,
			काष्ठा cros_ec_command *msg);
	काष्ठा mutex lock;
	u8 mkbp_event_supported;
	bool host_sleep_v1;
	काष्ठा blocking_notअगरier_head event_notअगरier;

	काष्ठा ec_response_get_next_event_v1 event_data;
	पूर्णांक event_size;
	u32 host_event_wake_mask;
	u32 last_resume_result;
	kसमय_प्रकार last_event_समय;
	काष्ठा notअगरier_block notअगरier_पढ़ोy;

	/* The platक्रमm devices used by the mfd driver */
	काष्ठा platक्रमm_device *ec;
	काष्ठा platक्रमm_device *pd;
पूर्ण;

/**
 * काष्ठा cros_ec_platक्रमm - ChromeOS EC platक्रमm inक्रमmation.
 * @ec_name: Name of EC device (e.g. 'cros-ec', 'cros-pd', ...)
 *           used in /dev/ and sysfs.
 * @cmd_offset: Offset to apply क्रम each command. Set when
 *              रेजिस्टरing a device behind another one.
 */
काष्ठा cros_ec_platक्रमm अणु
	स्थिर अक्षर *ec_name;
	u16 cmd_offset;
पूर्ण;

/**
 * काष्ठा cros_ec_dev - ChromeOS EC device entry poपूर्णांक.
 * @class_dev: Device काष्ठाure used in sysfs.
 * @ec_dev: cros_ec_device काष्ठाure to talk to the physical device.
 * @dev: Poपूर्णांकer to the platक्रमm device.
 * @debug_info: cros_ec_debugfs काष्ठाure क्रम debugging inक्रमmation.
 * @has_kb_wake_angle: True अगर at least 2 accelerometer are connected to the EC.
 * @cmd_offset: Offset to apply क्रम each command.
 * @features: Features supported by the EC.
 */
काष्ठा cros_ec_dev अणु
	काष्ठा device class_dev;
	काष्ठा cros_ec_device *ec_dev;
	काष्ठा device *dev;
	काष्ठा cros_ec_debugfs *debug_info;
	bool has_kb_wake_angle;
	u16 cmd_offset;
	u32 features[2];
पूर्ण;

#घोषणा to_cros_ec_dev(dev)  container_of(dev, काष्ठा cros_ec_dev, class_dev)

पूर्णांक cros_ec_prepare_tx(काष्ठा cros_ec_device *ec_dev,
		       काष्ठा cros_ec_command *msg);

पूर्णांक cros_ec_check_result(काष्ठा cros_ec_device *ec_dev,
			 काष्ठा cros_ec_command *msg);

पूर्णांक cros_ec_cmd_xfer_status(काष्ठा cros_ec_device *ec_dev,
			    काष्ठा cros_ec_command *msg);

पूर्णांक cros_ec_query_all(काष्ठा cros_ec_device *ec_dev);

पूर्णांक cros_ec_get_next_event(काष्ठा cros_ec_device *ec_dev,
			   bool *wake_event,
			   bool *has_more_events);

u32 cros_ec_get_host_event(काष्ठा cros_ec_device *ec_dev);

पूर्णांक cros_ec_check_features(काष्ठा cros_ec_dev *ec, पूर्णांक feature);

पूर्णांक cros_ec_get_sensor_count(काष्ठा cros_ec_dev *ec);

/**
 * cros_ec_get_समय_ns() - Return समय in ns.
 *
 * This is the function used to record the समय क्रम last_event_समय in काष्ठा
 * cros_ec_device during the hard irq.
 *
 * Return: kसमय_प्रकार क्रमmat since boot.
 */
अटल अंतरभूत kसमय_प्रकार cros_ec_get_समय_ns(व्योम)
अणु
	वापस kसमय_get_bootसमय_ns();
पूर्ण

#पूर्ण_अगर /* __LINUX_CROS_EC_PROTO_H */
