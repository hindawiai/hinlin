<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* dvb-usb.h is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * the headerfile, all dvb-usb-drivers have to include.
 *
 * TODO: clean-up the काष्ठाures क्रम unused fields and update the comments
 */
#अगर_अघोषित __DVB_USB_H__
#घोषणा __DVB_USB_H__

#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/mutex.h>
#समावेश <media/rc-core.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dmxdev.h>

#समावेश "dvb-pll.h"

#समावेश <media/dvb-usb-ids.h>

/* debug */
#अगर_घोषित CONFIG_DVB_USB_DEBUG
#घोषणा dprपूर्णांकk(var, level, args...) \
	    करो अणु अगर (((var) & (level))) अणु prपूर्णांकk(args); पूर्ण पूर्ण जबतक (0)

#घोषणा debug_dump(b, l, func) अणु\
	पूर्णांक loop_; \
	क्रम (loop_ = 0; loop_ < (l); loop_++) \
		func("%02x ", b[loop_]); \
	func("\n");\
पूर्ण
#घोषणा DVB_USB_DEBUG_STATUS
#अन्यथा
#घोषणा dprपूर्णांकk(var, level, args...) no_prपूर्णांकk(args)
#घोषणा debug_dump(b, l, func) करो अणु पूर्ण जबतक (0)

#घोषणा DVB_USB_DEBUG_STATUS " (debugging is not enabled)"

#पूर्ण_अगर

/* generic log methods - taken from usb.h */
#अगर_अघोषित DVB_USB_LOG_PREFIX
 #घोषणा DVB_USB_LOG_PREFIX "dvb-usb (please define a log prefix)"
#पूर्ण_अगर

#अघोषित err
#घोषणा err(क्रमmat, arg...)  prपूर्णांकk(KERN_ERR     DVB_USB_LOG_PREFIX ": " क्रमmat "\n" , ## arg)
#अघोषित info
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO    DVB_USB_LOG_PREFIX ": " क्रमmat "\n" , ## arg)
#अघोषित warn
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING DVB_USB_LOG_PREFIX ": " क्रमmat "\n" , ## arg)

/**
 * काष्ठा dvb_usb_device_description - name and its according USB IDs
 * @name: real name of the box, regardless which DVB USB device class is in use
 * @cold_ids: array of काष्ठा usb_device_id which describe the device in
 *  pre-firmware state
 * @warm_ids: array of काष्ठा usb_device_id which describe the device in
 *  post-firmware state
 *
 * Each DVB USB device class can have one or more actual devices, this काष्ठा
 * assigns a name to it.
 */
काष्ठा dvb_usb_device_description अणु
	स्थिर अक्षर *name;

#घोषणा DVB_USB_ID_MAX_NUM 15
	काष्ठा usb_device_id *cold_ids[DVB_USB_ID_MAX_NUM];
	काष्ठा usb_device_id *warm_ids[DVB_USB_ID_MAX_NUM];
पूर्ण;

अटल अंतरभूत u8 rc5_custom(काष्ठा rc_map_table *key)
अणु
	वापस (key->scancode >> 8) & 0xff;
पूर्ण

अटल अंतरभूत u8 rc5_data(काष्ठा rc_map_table *key)
अणु
	वापस key->scancode & 0xff;
पूर्ण

अटल अंतरभूत u16 rc5_scan(काष्ठा rc_map_table *key)
अणु
	वापस key->scancode & 0xffff;
पूर्ण

काष्ठा dvb_usb_device;
काष्ठा dvb_usb_adapter;
काष्ठा usb_data_stream;

/*
 * Properties of USB streaming - TODO this काष्ठाure should be somewhere अन्यथा
 * describes the kind of USB transfer used क्रम data-streaming.
 *  (BULK or ISOC)
 */
काष्ठा usb_data_stream_properties अणु
#घोषणा USB_BULK  1
#घोषणा USB_ISOC  2
	पूर्णांक type;
	पूर्णांक count;
	पूर्णांक endpoपूर्णांक;

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक buffersize; /* per URB */
		पूर्ण bulk;
		काष्ठा अणु
			पूर्णांक framesperurb;
			पूर्णांक framesize;
			पूर्णांक पूर्णांकerval;
		पूर्ण isoc;
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा dvb_usb_adapter_fe_properties - properties of a dvb-usb-adapter.
 *    A DVB-USB-Adapter is basically a dvb_adapter which is present on a USB-device.
 * @caps: capabilities of the DVB USB device.
 * @pid_filter_count: number of PID filter position in the optional hardware
 *  PID-filter.
 * @num_frontends: number of frontends of the DVB USB adapter.
 * @frontend_ctrl: called to घातer on/off active frontend.
 * @streaming_ctrl: called to start and stop the MPEG2-TS streaming of the
 *  device (not URB submitting/समाप्तing).
 *  This callback will be called without data URBs being active - data URBs
 *  will be submitted only after streaming_ctrl(1) वापसs successfully and
 *  they will be समाप्तed beक्रमe streaming_ctrl(0) माला_लो called.
 * @pid_filter_ctrl: called to en/disable the PID filter, अगर any.
 * @pid_filter: called to set/unset a PID क्रम filtering.
 * @frontend_attach: called to attach the possible frontends (fill fe-field
 *  of काष्ठा dvb_usb_device).
 * @tuner_attach: called to attach the correct tuner and to fill pll_addr,
 *  pll_desc and pll_init_buf of काष्ठा dvb_usb_device).
 * @stream: configuration of the USB streaming
 * @size_of_priv: size of the priv memory in काष्ठा dvb_usb_adapter
 */
काष्ठा dvb_usb_adapter_fe_properties अणु
#घोषणा DVB_USB_ADAP_HAS_PID_FILTER               0x01
#घोषणा DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF 0x02
#घोषणा DVB_USB_ADAP_NEED_PID_FILTERING           0x04
#घोषणा DVB_USB_ADAP_RECEIVES_204_BYTE_TS         0x08
#घोषणा DVB_USB_ADAP_RECEIVES_RAW_PAYLOAD         0x10
	पूर्णांक caps;
	पूर्णांक pid_filter_count;

	पूर्णांक (*streaming_ctrl)  (काष्ठा dvb_usb_adapter *, पूर्णांक);
	पूर्णांक (*pid_filter_ctrl) (काष्ठा dvb_usb_adapter *, पूर्णांक);
	पूर्णांक (*pid_filter)      (काष्ठा dvb_usb_adapter *, पूर्णांक, u16, पूर्णांक);

	पूर्णांक (*frontend_attach) (काष्ठा dvb_usb_adapter *);
	पूर्णांक (*tuner_attach)    (काष्ठा dvb_usb_adapter *);

	काष्ठा usb_data_stream_properties stream;

	पूर्णांक size_of_priv;
पूर्ण;

#घोषणा MAX_NO_OF_FE_PER_ADAP 3
काष्ठा dvb_usb_adapter_properties अणु
	पूर्णांक size_of_priv;

	पूर्णांक (*frontend_ctrl)   (काष्ठा dvb_frontend *, पूर्णांक);

	पूर्णांक num_frontends;
	काष्ठा dvb_usb_adapter_fe_properties fe[MAX_NO_OF_FE_PER_ADAP];
पूर्ण;

/**
 * काष्ठा dvb_rc_legacy - old properties of remote controller
 * @rc_map_table: a hard-wired array of काष्ठा rc_map_table (शून्य to disable
 *  remote control handling).
 * @rc_map_size: number of items in @rc_map_table.
 * @rc_query: called to query an event event.
 * @rc_पूर्णांकerval: समय in ms between two queries.
 */
काष्ठा dvb_rc_legacy अणु
/* remote control properties */
#घोषणा REMOTE_NO_KEY_PRESSED      0x00
#घोषणा REMOTE_KEY_PRESSED         0x01
#घोषणा REMOTE_KEY_REPEAT          0x02
	काष्ठा rc_map_table  *rc_map_table;
	पूर्णांक rc_map_size;
	पूर्णांक (*rc_query) (काष्ठा dvb_usb_device *, u32 *, पूर्णांक *);
	पूर्णांक rc_पूर्णांकerval;
पूर्ण;

/**
 * काष्ठा dvb_rc - properties of remote controller, using rc-core
 * @rc_codes: name of rc codes table
 * @protocol: type of protocol(s) currently used by the driver
 * @allowed_protos: protocol(s) supported by the driver
 * @driver_type: Used to poपूर्णांक अगर a device supports raw mode
 * @change_protocol: callback to change protocol
 * @module_name: module name
 * @rc_query: called to query an event event.
 * @rc_पूर्णांकerval: समय in ms between two queries.
 * @bulk_mode: device supports bulk mode क्रम RC (disable polling mode)
 * @scancode_mask: scancode mask
 */
काष्ठा dvb_rc अणु
	अक्षर *rc_codes;
	u64 protocol;
	u64 allowed_protos;
	क्रमागत rc_driver_type driver_type;
	पूर्णांक (*change_protocol)(काष्ठा rc_dev *dev, u64 *rc_proto);
	अक्षर *module_name;
	पूर्णांक (*rc_query) (काष्ठा dvb_usb_device *d);
	पूर्णांक rc_पूर्णांकerval;
	bool bulk_mode;				/* uses bulk mode */
	u32 scancode_mask;
पूर्ण;

/**
 * क्रमागत dvb_usb_mode - Specअगरies अगर it is using a legacy driver or a new one
 *		       based on rc-core
 * This is initialized/used only inside dvb-usb-remote.c.
 * It shouldn't be set by the drivers.
 *
 * @DVB_RC_LEGACY: legacy driver
 * @DVB_RC_CORE: rc-core driver
 */
क्रमागत dvb_usb_mode अणु
	DVB_RC_LEGACY,
	DVB_RC_CORE,
पूर्ण;

/**
 * काष्ठा dvb_usb_device_properties - properties of a dvb-usb-device
 * @caps: capabilities
 * @usb_ctrl: which USB device-side controller is in use. Needed क्रम firmware
 *  करोwnload.
 * @firmware: name of the firmware file.
 * @करोwnload_firmware: called to करोwnload the firmware when the usb_ctrl is
 *  DEVICE_SPECIFIC.
 * @no_reconnect: device करोesn't करो a reconnect after करोwnloading the firmware,
 *  so करो the warm initialization right after it
 *
 * @size_of_priv: how many bytes shall be allocated क्रम the निजी field
 *  of काष्ठा dvb_usb_device.
 * @priv_init: optional callback to initialize the variable that निजी field
 * of काष्ठा dvb_usb_device has poपूर्णांकer to just after it had been allocated and
 * zeroed.
 * @priv_destroy: just like priv_init, only called beक्रमe deallocating
 * the memory poपूर्णांकed by निजी field of काष्ठा dvb_usb_device.
 *
 * @num_adapters: the number of adapters in @adapters
 * @adapter: the adapters
 * @घातer_ctrl: called to enable/disable घातer of the device.
 * @पढ़ो_mac_address: called to पढ़ो the MAC address of the device.
 * @identअगरy_state: called to determine the state (cold or warm), when it
 *  is not distinguishable by the USB IDs.
 *
 * @rc: remote controller properties
 *
 * @i2c_algo: i2c_algorithm अगर the device has I2CoverUSB.
 *
 * @generic_bulk_ctrl_endpoपूर्णांक: most of the DVB USB devices have a generic
 *  endpoपूर्णांक which received control messages with bulk transfers. When this
 *  is non-zero, one can use dvb_usb_generic_rw and dvb_usb_generic_ग_लिखो-
 *  helper functions.
 *
 * @generic_bulk_ctrl_endpoपूर्णांक_response: some DVB USB devices use a separate
 *  endpoपूर्णांक क्रम responses to control messages sent with bulk transfers via
 *  the generic_bulk_ctrl_endpoपूर्णांक. When this is non-zero, this will be used
 *  instead of the generic_bulk_ctrl_endpoपूर्णांक when पढ़ोing usb responses in
 *  the dvb_usb_generic_rw helper function.
 *
 * @num_device_descs: number of काष्ठा dvb_usb_device_description in @devices
 * @devices: array of काष्ठा dvb_usb_device_description compatibles with these
 *  properties.
 */
काष्ठा dvb_usb_device_properties अणु
#घोषणा MAX_NO_OF_ADAPTER_PER_DEVICE 2
#घोषणा DVB_USB_IS_AN_I2C_ADAPTER            0x01
	पूर्णांक caps;

#घोषणा DEVICE_SPECIFIC 0
#घोषणा CYPRESS_AN2135  1
#घोषणा CYPRESS_AN2235  2
#घोषणा CYPRESS_FX2     3
	पूर्णांक        usb_ctrl;
	पूर्णांक        (*करोwnload_firmware) (काष्ठा usb_device *, स्थिर काष्ठा firmware *);
	स्थिर अक्षर *firmware;
	पूर्णांक        no_reconnect;

	पूर्णांक size_of_priv;
	पूर्णांक (*priv_init)(काष्ठा dvb_usb_device *);
	व्योम (*priv_destroy)(काष्ठा dvb_usb_device *);

	पूर्णांक num_adapters;
	काष्ठा dvb_usb_adapter_properties adapter[MAX_NO_OF_ADAPTER_PER_DEVICE];

	पूर्णांक (*घातer_ctrl)       (काष्ठा dvb_usb_device *, पूर्णांक);
	पूर्णांक (*पढ़ो_mac_address) (काष्ठा dvb_usb_device *, u8 []);
	पूर्णांक (*identअगरy_state)(काष्ठा usb_device *udev,
			      स्थिर काष्ठा dvb_usb_device_properties *props,
			      स्थिर काष्ठा dvb_usb_device_description **desc,
			      पूर्णांक *cold);

	काष्ठा अणु
		क्रमागत dvb_usb_mode mode;	/* Drivers shouldn't touch on it */
		काष्ठा dvb_rc_legacy legacy;
		काष्ठा dvb_rc core;
	पूर्ण rc;

	काष्ठा i2c_algorithm *i2c_algo;

	पूर्णांक generic_bulk_ctrl_endpoपूर्णांक;
	पूर्णांक generic_bulk_ctrl_endpoपूर्णांक_response;

	पूर्णांक num_device_descs;
	काष्ठा dvb_usb_device_description devices[12];
पूर्ण;

/**
 * काष्ठा usb_data_stream - generic object of an USB stream
 * @udev: the USB device
 * @props: data stream properties
 * @state: state of the stream
 * @complete: complete callback
 * @urb_list: list of URBs
 * @buf_num: number of buffer allocated.
 * @buf_size: size of each buffer in buf_list.
 * @buf_list: array containing all allocate buffers क्रम streaming.
 * @dma_addr: list of dma_addr_t क्रम each buffer in buf_list.
 *
 * @urbs_initialized: number of URBs initialized.
 * @urbs_submitted: number of URBs submitted.
 * @user_priv: क्रम निजी use.
 */
काष्ठा usb_data_stream अणु
#घोषणा MAX_NO_URBS_FOR_DATA_STREAM 10
	काष्ठा usb_device                 *udev;
	काष्ठा usb_data_stream_properties  props;

#घोषणा USB_STATE_INIT    0x00
#घोषणा USB_STATE_URB_BUF 0x01
	पूर्णांक state;

	व्योम (*complete) (काष्ठा usb_data_stream *, u8 *, माप_प्रकार);

	काष्ठा urb    *urb_list[MAX_NO_URBS_FOR_DATA_STREAM];
	पूर्णांक            buf_num;
	अचिन्हित दीर्घ  buf_size;
	u8            *buf_list[MAX_NO_URBS_FOR_DATA_STREAM];
	dma_addr_t     dma_addr[MAX_NO_URBS_FOR_DATA_STREAM];

	पूर्णांक urbs_initialized;
	पूर्णांक urbs_submitted;

	व्योम *user_priv;
पूर्ण;

/**
 * काष्ठा dvb_usb_fe_adapter - a DVB adapter on a USB device
 * @fe: frontend
 * @fe_init:  rerouted frontend-init (wakeup) function.
 * @fe_sleep: rerouted frontend-sleep function.
 * @stream: the usb data stream.
 * @pid_filtering: is hardware pid_filtering used or not.
 * @max_feed_count: how many feeds can be handled simultaneously by this
 *  device
 * @priv: निजी poपूर्णांकer
 */
काष्ठा dvb_usb_fe_adapter अणु
	काष्ठा dvb_frontend *fe;

	पूर्णांक (*fe_init)  (काष्ठा dvb_frontend *);
	पूर्णांक (*fe_sleep) (काष्ठा dvb_frontend *);

	काष्ठा usb_data_stream stream;

	पूर्णांक pid_filtering;
	पूर्णांक max_feed_count;

	व्योम *priv;
पूर्ण;

/**
 * काष्ठा dvb_usb_adapter - a DVB adapter on a USB device
 * @dev: DVB USB device poपूर्णांकer
 * @props: properties
 * @state: status
 * @id: index of this adapter (starting with 0).
 *
 * @feedcount: number of requested feeds (used क्रम streaming-activation)
 *
 * @dvb_adap: device's dvb_adapter.
 * @dmxdev: device's dmxdev.
 * @demux: device's software demuxer.
 * @dvb_net: device's dvb_net पूर्णांकerfaces.
 *
 * @fe_adap: frontend adapters
 * @active_fe: active frontend
 * @num_frontends_initialized: number of initialized frontends
 * @priv: निजी poपूर्णांकer
 */
काष्ठा dvb_usb_adapter अणु
	काष्ठा dvb_usb_device *dev;
	काष्ठा dvb_usb_adapter_properties props;

#घोषणा DVB_USB_ADAP_STATE_INIT 0x000
#घोषणा DVB_USB_ADAP_STATE_DVB  0x001
	पूर्णांक state;

	u8  id;

	पूर्णांक feedcount;

	/* dvb */
	काष्ठा dvb_adapter   dvb_adap;
	काष्ठा dmxdev        dmxdev;
	काष्ठा dvb_demux     demux;
	काष्ठा dvb_net       dvb_net;

	काष्ठा dvb_usb_fe_adapter fe_adap[MAX_NO_OF_FE_PER_ADAP];
	पूर्णांक active_fe;
	पूर्णांक num_frontends_initialized;

	व्योम *priv;
पूर्ण;

/**
 * काष्ठा dvb_usb_device - object of a DVB USB device
 * @props: copy of the काष्ठा dvb_usb_properties this device beदीर्घs to.
 * @desc: poपूर्णांकer to the device's काष्ठा dvb_usb_device_description.
 * @state: initialization and runसमय state of the device.
 *
 * @घातered: indicated whether the device is घातer or not.
 *  Powered is in/decremented क्रम each call to modअगरy the state.
 * @udev: poपूर्णांकer to the device's काष्ठा usb_device.
 *
 * @data_mutex: mutex to protect the data काष्ठाure used to store URB data
 * @usb_mutex: mutex of USB control messages (पढ़ोing needs two messages).
 *	Please notice that this mutex is used पूर्णांकernally at the generic
 *	URB control functions. So, drivers using dvb_usb_generic_rw() and
 *	derivated functions should not lock it पूर्णांकernally.
 * @i2c_mutex: mutex क्रम i2c-transfers
 *
 * @i2c_adap: device's i2c_adapter अगर it uses I2CoverUSB
 *
 * @num_adapters_initialized: number of initialized adapters
 * @adapter: adapters
 *
 * @rc_dev: rc device क्रम the remote control (rc-core mode)
 * @input_dev: input device क्रम the remote control (legacy mode)
 * @rc_phys: rc device path
 * @rc_query_work: काष्ठा work_काष्ठा frequent rc queries
 * @last_event: last triggered event
 * @last_state: last state (no, pressed, repeat)
 * @owner: owner of the dvb_adapter
 * @priv: निजी data of the actual driver (allocate by dvb-usb, size defined
 *  in size_of_priv of dvb_usb_properties).
 */
काष्ठा dvb_usb_device अणु
	काष्ठा dvb_usb_device_properties props;
	स्थिर काष्ठा dvb_usb_device_description *desc;

	काष्ठा usb_device *udev;

#घोषणा DVB_USB_STATE_INIT        0x000
#घोषणा DVB_USB_STATE_I2C         0x001
#घोषणा DVB_USB_STATE_DVB         0x002
#घोषणा DVB_USB_STATE_REMOTE      0x004
	पूर्णांक state;

	पूर्णांक घातered;

	/* locking */
	काष्ठा mutex data_mutex;
	काष्ठा mutex usb_mutex;

	/* i2c */
	काष्ठा mutex i2c_mutex;
	काष्ठा i2c_adapter i2c_adap;

	पूर्णांक                    num_adapters_initialized;
	काष्ठा dvb_usb_adapter adapter[MAX_NO_OF_ADAPTER_PER_DEVICE];

	/* remote control */
	काष्ठा rc_dev *rc_dev;
	काष्ठा input_dev *input_dev;
	अक्षर rc_phys[64];
	काष्ठा delayed_work rc_query_work;
	u32 last_event;
	पूर्णांक last_state;

	काष्ठा module *owner;

	व्योम *priv;
पूर्ण;

बाह्य पूर्णांक dvb_usb_device_init(काष्ठा usb_पूर्णांकerface *,
			       स्थिर काष्ठा dvb_usb_device_properties *,
			       काष्ठा module *, काष्ठा dvb_usb_device **,
			       लघु *adapter_nums);
बाह्य व्योम dvb_usb_device_निकास(काष्ठा usb_पूर्णांकerface *);

/* the generic पढ़ो/ग_लिखो method क्रम device control */
बाह्य पूर्णांक __must_check
dvb_usb_generic_rw(काष्ठा dvb_usb_device *, u8 *, u16, u8 *, u16, पूर्णांक);
बाह्य पूर्णांक __must_check
dvb_usb_generic_ग_लिखो(काष्ठा dvb_usb_device *, u8 *, u16);

/* commonly used remote control parsing */
पूर्णांक dvb_usb_nec_rc_key_to_event(काष्ठा dvb_usb_device *d, u8 keybuf[5],
				u32 *event, पूर्णांक *state);

/* commonly used firmware करोwnload types and function */
काष्ठा hexline अणु
	u8 len;
	u32 addr;
	u8 type;
	u8 data[255];
	u8 chk;
पूर्ण;
बाह्य पूर्णांक usb_cypress_load_firmware(काष्ठा usb_device *udev, स्थिर काष्ठा firmware *fw, पूर्णांक type);
बाह्य पूर्णांक dvb_usb_get_hexline(स्थिर काष्ठा firmware *fw, काष्ठा hexline *hx, पूर्णांक *pos);


#पूर्ण_अगर
