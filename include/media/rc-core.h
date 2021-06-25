<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Remote Controller core header
 *
 * Copyright (C) 2009-2010 by Mauro Carvalho Chehab
 */

#अगर_अघोषित _RC_CORE
#घोषणा _RC_CORE

#समावेश <linux/spinlock.h>
#समावेश <linux/cdev.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <media/rc-map.h>

/**
 * क्रमागत rc_driver_type - type of the RC driver.
 *
 * @RC_DRIVER_SCANCODE:	 Driver or hardware generates a scancode.
 * @RC_DRIVER_IR_RAW:	 Driver or hardware generates pulse/space sequences.
 *			 It needs a Infra-Red pulse/space decoder
 * @RC_DRIVER_IR_RAW_TX: Device transmitter only,
 *			 driver requires pulse/space data sequence.
 */
क्रमागत rc_driver_type अणु
	RC_DRIVER_SCANCODE = 0,
	RC_DRIVER_IR_RAW,
	RC_DRIVER_IR_RAW_TX,
पूर्ण;

/**
 * काष्ठा rc_scancode_filter - Filter scan codes.
 * @data:	Scancode data to match.
 * @mask:	Mask of bits of scancode to compare.
 */
काष्ठा rc_scancode_filter अणु
	u32 data;
	u32 mask;
पूर्ण;

/**
 * क्रमागत rc_filter_type - Filter type स्थिरants.
 * @RC_FILTER_NORMAL:	Filter क्रम normal operation.
 * @RC_FILTER_WAKEUP:	Filter क्रम waking from suspend.
 * @RC_FILTER_MAX:	Number of filter types.
 */
क्रमागत rc_filter_type अणु
	RC_FILTER_NORMAL = 0,
	RC_FILTER_WAKEUP,

	RC_FILTER_MAX
पूर्ण;

/**
 * काष्ठा lirc_fh - represents an खोलो lirc file
 * @list: list of खोलो file handles
 * @rc: rcdev क्रम this lirc अक्षरdev
 * @carrier_low: when setting the carrier range, first the low end must be
 *	set with an ioctl and then the high end with another ioctl
 * @send_समयout_reports: report समयouts in lirc raw IR.
 * @rawir: queue क्रम incoming raw IR
 * @scancodes: queue क्रम incoming decoded scancodes
 * @रुको_poll: poll काष्ठा क्रम lirc device
 * @send_mode: lirc mode क्रम sending, either LIRC_MODE_SCANCODE or
 *	LIRC_MODE_PULSE
 * @rec_mode: lirc mode क्रम receiving, either LIRC_MODE_SCANCODE or
 *	LIRC_MODE_MODE2
 */
काष्ठा lirc_fh अणु
	काष्ठा list_head list;
	काष्ठा rc_dev *rc;
	पूर्णांक				carrier_low;
	bool				send_समयout_reports;
	DECLARE_KFIFO_PTR(rawir, अचिन्हित पूर्णांक);
	DECLARE_KFIFO_PTR(scancodes, काष्ठा lirc_scancode);
	रुको_queue_head_t		रुको_poll;
	u8				send_mode;
	u8				rec_mode;
पूर्ण;

/**
 * काष्ठा rc_dev - represents a remote control device
 * @dev: driver model's view of this device
 * @managed_alloc: devm_rc_allocate_device was used to create rc_dev
 * @sysfs_groups: sysfs attribute groups
 * @device_name: name of the rc child device
 * @input_phys: physical path to the input child device
 * @input_id: id of the input child device (काष्ठा input_id)
 * @driver_name: name of the hardware driver which रेजिस्टरed this device
 * @map_name: name of the शेष keymap
 * @rc_map: current scan/key table
 * @lock: used to ensure we've filled in all protocol details beक्रमe
 *	anyone can call show_protocols or store_protocols
 * @minor: unique minor remote control device number
 * @raw: additional data क्रम raw pulse/space devices
 * @input_dev: the input child device used to communicate events to userspace
 * @driver_type: specअगरies अगर protocol decoding is करोne in hardware or software
 * @idle: used to keep track of RX state
 * @encode_wakeup: wakeup filtering uses IR encode API, thereक्रमe the allowed
 *	wakeup protocols is the set of all raw encoders
 * @allowed_protocols: biपंचांगask with the supported RC_PROTO_BIT_* protocols
 * @enabled_protocols: biपंचांगask with the enabled RC_PROTO_BIT_* protocols
 * @allowed_wakeup_protocols: biपंचांगask with the supported RC_PROTO_BIT_* wakeup
 *	protocols
 * @wakeup_protocol: the enabled RC_PROTO_* wakeup protocol or
 *	RC_PROTO_UNKNOWN अगर disabled.
 * @scancode_filter: scancode filter
 * @scancode_wakeup_filter: scancode wakeup filters
 * @scancode_mask: some hardware decoders are not capable of providing the full
 *	scancode to the application. As this is a hardware limit, we can't करो
 *	anything with it. Yet, as the same keycode table can be used with other
 *	devices, a mask is provided to allow its usage. Drivers should generally
 *	leave this field in blank
 * @users: number of current users of the device
 * @priv: driver-specअगरic data
 * @keylock: protects the reमुख्यing members of the काष्ठा
 * @keypressed: whether a key is currently pressed
 * @keyup_jअगरfies: समय (in jअगरfies) when the current keypress should be released
 * @समयr_keyup: समयr क्रम releasing a keypress
 * @समयr_repeat: समयr क्रम स्वतःrepeat events. This is needed क्रम CEC, which
 *	has non-standard repeats.
 * @last_keycode: keycode of last keypress
 * @last_protocol: protocol of last keypress
 * @last_scancode: scancode of last keypress
 * @last_toggle: toggle value of last command
 * @समयout: optional समय after which device stops sending data
 * @min_समयout: minimum समयout supported by device
 * @max_समयout: maximum समयout supported by device
 * @rx_resolution : resolution (in us) of input sampler
 * @tx_resolution: resolution (in us) of output sampler
 * @lirc_dev: lirc device
 * @lirc_cdev: lirc अक्षर cdev
 * @gap_start: समय when gap starts
 * @gap_duration: duration of initial gap
 * @gap: true अगर we're in a gap
 * @lirc_fh_lock: protects lirc_fh list
 * @lirc_fh: list of खोलो files
 * @रेजिस्टरed: set to true by rc_रेजिस्टर_device(), false by
 *	rc_unरेजिस्टर_device
 * @change_protocol: allow changing the protocol used on hardware decoders
 * @खोलो: callback to allow drivers to enable polling/irq when IR input device
 *	is खोलोed.
 * @बंद: callback to allow drivers to disable polling/irq when IR input device
 *	is खोलोed.
 * @s_tx_mask: set transmitter mask (क्रम devices with multiple tx outमाला_दो)
 * @s_tx_carrier: set transmit carrier frequency
 * @s_tx_duty_cycle: set transmit duty cycle (0% - 100%)
 * @s_rx_carrier_range: inक्रमm driver about carrier it is expected to handle
 * @tx_ir: transmit IR
 * @s_idle: enable/disable hardware idle mode, upon which,
 *	device करोesn't पूर्णांकerrupt host until it sees IR pulses
 * @s_learning_mode: enable wide band receiver used क्रम learning
 * @s_carrier_report: enable carrier reports
 * @s_filter: set the scancode filter
 * @s_wakeup_filter: set the wakeup scancode filter. If the mask is zero
 *	then wakeup should be disabled. wakeup_protocol will be set to
 *	a valid protocol अगर mask is nonzero.
 * @s_समयout: set hardware समयout in us
 */
काष्ठा rc_dev अणु
	काष्ठा device			dev;
	bool				managed_alloc;
	स्थिर काष्ठा attribute_group	*sysfs_groups[5];
	स्थिर अक्षर			*device_name;
	स्थिर अक्षर			*input_phys;
	काष्ठा input_id			input_id;
	स्थिर अक्षर			*driver_name;
	स्थिर अक्षर			*map_name;
	काष्ठा rc_map			rc_map;
	काष्ठा mutex			lock;
	अचिन्हित पूर्णांक			minor;
	काष्ठा ir_raw_event_ctrl	*raw;
	काष्ठा input_dev		*input_dev;
	क्रमागत rc_driver_type		driver_type;
	bool				idle;
	bool				encode_wakeup;
	u64				allowed_protocols;
	u64				enabled_protocols;
	u64				allowed_wakeup_protocols;
	क्रमागत rc_proto			wakeup_protocol;
	काष्ठा rc_scancode_filter	scancode_filter;
	काष्ठा rc_scancode_filter	scancode_wakeup_filter;
	u32				scancode_mask;
	u32				users;
	व्योम				*priv;
	spinlock_t			keylock;
	bool				keypressed;
	अचिन्हित दीर्घ			keyup_jअगरfies;
	काष्ठा समयr_list		समयr_keyup;
	काष्ठा समयr_list		समयr_repeat;
	u32				last_keycode;
	क्रमागत rc_proto			last_protocol;
	u64				last_scancode;
	u8				last_toggle;
	u32				समयout;
	u32				min_समयout;
	u32				max_समयout;
	u32				rx_resolution;
	u32				tx_resolution;
#अगर_घोषित CONFIG_LIRC
	काष्ठा device			lirc_dev;
	काष्ठा cdev			lirc_cdev;
	kसमय_प्रकार				gap_start;
	u64				gap_duration;
	bool				gap;
	spinlock_t			lirc_fh_lock;
	काष्ठा list_head		lirc_fh;
#पूर्ण_अगर
	bool				रेजिस्टरed;
	पूर्णांक				(*change_protocol)(काष्ठा rc_dev *dev, u64 *rc_proto);
	पूर्णांक				(*खोलो)(काष्ठा rc_dev *dev);
	व्योम				(*बंद)(काष्ठा rc_dev *dev);
	पूर्णांक				(*s_tx_mask)(काष्ठा rc_dev *dev, u32 mask);
	पूर्णांक				(*s_tx_carrier)(काष्ठा rc_dev *dev, u32 carrier);
	पूर्णांक				(*s_tx_duty_cycle)(काष्ठा rc_dev *dev, u32 duty_cycle);
	पूर्णांक				(*s_rx_carrier_range)(काष्ठा rc_dev *dev, u32 min, u32 max);
	पूर्णांक				(*tx_ir)(काष्ठा rc_dev *dev, अचिन्हित *txbuf, अचिन्हित n);
	व्योम				(*s_idle)(काष्ठा rc_dev *dev, bool enable);
	पूर्णांक				(*s_learning_mode)(काष्ठा rc_dev *dev, पूर्णांक enable);
	पूर्णांक				(*s_carrier_report) (काष्ठा rc_dev *dev, पूर्णांक enable);
	पूर्णांक				(*s_filter)(काष्ठा rc_dev *dev,
						    काष्ठा rc_scancode_filter *filter);
	पूर्णांक				(*s_wakeup_filter)(काष्ठा rc_dev *dev,
							   काष्ठा rc_scancode_filter *filter);
	पूर्णांक				(*s_समयout)(काष्ठा rc_dev *dev,
						     अचिन्हित पूर्णांक समयout);
पूर्ण;

#घोषणा to_rc_dev(d) container_of(d, काष्ठा rc_dev, dev)

/*
 * From rc-मुख्य.c
 * Those functions can be used on any type of Remote Controller. They
 * basically creates an input_dev and properly reports the device as a
 * Remote Controller, at sys/class/rc.
 */

/**
 * rc_allocate_device - Allocates a RC device
 *
 * @rc_driver_type: specअगरies the type of the RC output to be allocated
 * वापसs a poपूर्णांकer to काष्ठा rc_dev.
 */
काष्ठा rc_dev *rc_allocate_device(क्रमागत rc_driver_type);

/**
 * devm_rc_allocate_device - Managed RC device allocation
 *
 * @dev: poपूर्णांकer to काष्ठा device
 * @rc_driver_type: specअगरies the type of the RC output to be allocated
 * वापसs a poपूर्णांकer to काष्ठा rc_dev.
 */
काष्ठा rc_dev *devm_rc_allocate_device(काष्ठा device *dev, क्रमागत rc_driver_type);

/**
 * rc_मुक्त_device - Frees a RC device
 *
 * @dev: poपूर्णांकer to काष्ठा rc_dev.
 */
व्योम rc_मुक्त_device(काष्ठा rc_dev *dev);

/**
 * rc_रेजिस्टर_device - Registers a RC device
 *
 * @dev: poपूर्णांकer to काष्ठा rc_dev.
 */
पूर्णांक rc_रेजिस्टर_device(काष्ठा rc_dev *dev);

/**
 * devm_rc_रेजिस्टर_device - Manageded रेजिस्टरing of a RC device
 *
 * @parent: poपूर्णांकer to काष्ठा device.
 * @dev: poपूर्णांकer to काष्ठा rc_dev.
 */
पूर्णांक devm_rc_रेजिस्टर_device(काष्ठा device *parent, काष्ठा rc_dev *dev);

/**
 * rc_unरेजिस्टर_device - Unरेजिस्टरs a RC device
 *
 * @dev: poपूर्णांकer to काष्ठा rc_dev.
 */
व्योम rc_unरेजिस्टर_device(काष्ठा rc_dev *dev);

व्योम rc_repeat(काष्ठा rc_dev *dev);
व्योम rc_keyकरोwn(काष्ठा rc_dev *dev, क्रमागत rc_proto protocol, u64 scancode,
		u8 toggle);
व्योम rc_keyकरोwn_noसमयout(काष्ठा rc_dev *dev, क्रमागत rc_proto protocol,
			  u64 scancode, u8 toggle);
व्योम rc_keyup(काष्ठा rc_dev *dev);
u32 rc_g_keycode_from_table(काष्ठा rc_dev *dev, u64 scancode);

/*
 * From rc-raw.c
 * The Raw पूर्णांकerface is specअगरic to InfraRed. It may be a good idea to
 * split it later पूर्णांकo a separate header.
 */
काष्ठा ir_raw_event अणु
	जोड़ अणु
		u32             duration;
		u32             carrier;
	पूर्ण;
	u8                      duty_cycle;

	अचिन्हित                pulse:1;
	अचिन्हित                reset:1;
	अचिन्हित                समयout:1;
	अचिन्हित                carrier_report:1;
पूर्ण;

#घोषणा US_TO_NS(usec)		((usec) * 1000)
#घोषणा MS_TO_US(msec)		((msec) * 1000)
#घोषणा IR_MAX_DURATION		MS_TO_US(500)
#घोषणा IR_DEFAULT_TIMEOUT	MS_TO_US(125)

व्योम ir_raw_event_handle(काष्ठा rc_dev *dev);
पूर्णांक ir_raw_event_store(काष्ठा rc_dev *dev, काष्ठा ir_raw_event *ev);
पूर्णांक ir_raw_event_store_edge(काष्ठा rc_dev *dev, bool pulse);
पूर्णांक ir_raw_event_store_with_filter(काष्ठा rc_dev *dev,
				   काष्ठा ir_raw_event *ev);
पूर्णांक ir_raw_event_store_with_समयout(काष्ठा rc_dev *dev,
				    काष्ठा ir_raw_event *ev);
व्योम ir_raw_event_set_idle(काष्ठा rc_dev *dev, bool idle);
पूर्णांक ir_raw_encode_scancode(क्रमागत rc_proto protocol, u32 scancode,
			   काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max);
पूर्णांक ir_raw_encode_carrier(क्रमागत rc_proto protocol);

अटल अंतरभूत व्योम ir_raw_event_reset(काष्ठा rc_dev *dev)
अणु
	ir_raw_event_store(dev, &((काष्ठा ir_raw_event) अणु .reset = true पूर्ण));
	dev->idle = true;
	ir_raw_event_handle(dev);
पूर्ण

/* extract mask bits out of data and pack them पूर्णांकo the result */
अटल अंतरभूत u32 ir_extract_bits(u32 data, u32 mask)
अणु
	u32 vbit = 1, value = 0;

	करो अणु
		अगर (mask & 1) अणु
			अगर (data & 1)
				value |= vbit;
			vbit <<= 1;
		पूर्ण
		data >>= 1;
	पूर्ण जबतक (mask >>= 1);

	वापस value;
पूर्ण

/* Get NEC scancode and protocol type from address and command bytes */
अटल अंतरभूत u32 ir_nec_bytes_to_scancode(u8 address, u8 not_address,
					   u8 command, u8 not_command,
					   क्रमागत rc_proto *protocol)
अणु
	u32 scancode;

	अगर ((command ^ not_command) != 0xff) अणु
		/* NEC transport, but modअगरied protocol, used by at
		 * least Apple and TiVo remotes
		 */
		scancode = not_address << 24 |
			address     << 16 |
			not_command <<  8 |
			command;
		*protocol = RC_PROTO_NEC32;
	पूर्ण अन्यथा अगर ((address ^ not_address) != 0xff) अणु
		/* Extended NEC */
		scancode = address     << 16 |
			   not_address <<  8 |
			   command;
		*protocol = RC_PROTO_NECX;
	पूर्ण अन्यथा अणु
		/* Normal NEC */
		scancode = address << 8 | command;
		*protocol = RC_PROTO_NEC;
	पूर्ण

	वापस scancode;
पूर्ण

#पूर्ण_अगर /* _RC_CORE */
