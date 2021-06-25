<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DVB USB framework
 *
 * Copyright (C) 2004-6 Patrick Boettcher <patrick.boettcher@posteo.de>
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित DVB_USB_H
#घोषणा DVB_USB_H

#समावेश <linux/usb/input.h>
#समावेश <linux/firmware.h>
#समावेश <media/rc-core.h>
#समावेश <media/media-device.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb-usb-ids.h>

/*
 * device file: /dev/dvb/adapter[0-1]/frontend[0-2]
 *
 * |-- device
 * |   |-- adapter0
 * |   |   |-- frontend0
 * |   |   |-- frontend1
 * |   |   `-- frontend2
 * |   `-- adapter1
 * |       |-- frontend0
 * |       |-- frontend1
 * |       `-- frontend2
 *
 *
 * Commonly used variable names:
 * d = poपूर्णांकer to device (काष्ठा dvb_usb_device *)
 * adap = poपूर्णांकer to adapter (काष्ठा dvb_usb_adapter *)
 * fe = poपूर्णांकer to frontend (काष्ठा dvb_frontend *)
 *
 * Use macros defined in that file to resolve needed poपूर्णांकers.
 */

/* helper macros क्रम every DVB USB driver use */
#घोषणा adap_to_d(adap) (container_of(adap, काष्ठा dvb_usb_device, \
		adapter[adap->id]))
#घोषणा adap_to_priv(adap) (adap_to_d(adap)->priv)
#घोषणा fe_to_adap(fe) ((काष्ठा dvb_usb_adapter *) ((fe)->dvb->priv))
#घोषणा fe_to_d(fe) (adap_to_d(fe_to_adap(fe)))
#घोषणा fe_to_priv(fe) (fe_to_d(fe)->priv)
#घोषणा d_to_priv(d) (d->priv)

#घोषणा dvb_usb_dbg_usb_control_msg(udev, r, t, v, i, b, l) अणु \
	अक्षर *direction; \
	अगर (t == (USB_TYPE_VENDOR | USB_सूची_OUT)) \
		direction = ">>>"; \
	अन्यथा \
		direction = "<<<"; \
	dev_dbg(&udev->dev, "%s: %02x %02x %02x %02x %02x %02x %02x %02x " \
			"%s %*ph\n",  __func__, t, r, v & 0xff, v >> 8, \
			i & 0xff, i >> 8, l & 0xff, l >> 8, direction, l, b); \
पूर्ण

#घोषणा DVB_USB_STREAM_BULK(endpoपूर्णांक_, count_, size_) अणु \
	.type = USB_BULK, \
	.count = count_, \
	.endpoपूर्णांक = endpoपूर्णांक_, \
	.u = अणु \
		.bulk = अणु \
			.buffersize = size_, \
		पूर्ण \
	पूर्ण \
पूर्ण

#घोषणा DVB_USB_STREAM_ISOC(endpoपूर्णांक_, count_, frames_, size_, पूर्णांकerval_) अणु \
	.type = USB_ISOC, \
	.count = count_, \
	.endpoपूर्णांक = endpoपूर्णांक_, \
	.u = अणु \
		.isoc = अणु \
			.framesperurb = frames_, \
			.framesize = size_,\
			.पूर्णांकerval = पूर्णांकerval_, \
		पूर्ण \
	पूर्ण \
पूर्ण

#घोषणा DVB_USB_DEVICE(vend, prod, props_, name_, rc) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.driver_info = (kernel_uदीर्घ_t) &((स्थिर काष्ठा dvb_usb_driver_info) अणु \
		.props = (props_), \
		.name = (name_), \
		.rc_map = (rc), \
	पूर्ण)

काष्ठा dvb_usb_device;
काष्ठा dvb_usb_adapter;

/**
 * काष्ठा dvb_usb_driver_info - काष्ठाure क्रम carrying all needed data from the
 *	device driver to the general
 * dvb usb routines
 * @name: device name
 * @rc_map: name of rc codes table
 * @props: काष्ठाure containing all device properties
 */
काष्ठा dvb_usb_driver_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *rc_map;
	स्थिर काष्ठा dvb_usb_device_properties *props;
पूर्ण;

/**
 * काष्ठा dvb_usb_rc - काष्ठाure क्रम remote controller configuration
 * @map_name: name of rc codes table
 * @allowed_protos: protocol(s) supported by the driver
 * @change_protocol: callback to change protocol
 * @query: called to query an event from the device
 * @पूर्णांकerval: समय in ms between two queries
 * @driver_type: used to poपूर्णांक अगर a device supports raw mode
 * @bulk_mode: device supports bulk mode क्रम rc (disable polling mode)
 * @समयout: set to length of last space beक्रमe raw IR goes idle
 */
काष्ठा dvb_usb_rc अणु
	स्थिर अक्षर *map_name;
	u64 allowed_protos;
	पूर्णांक (*change_protocol)(काष्ठा rc_dev *dev, u64 *rc_proto);
	पूर्णांक (*query) (काष्ठा dvb_usb_device *d);
	अचिन्हित पूर्णांक पूर्णांकerval;
	क्रमागत rc_driver_type driver_type;
	bool bulk_mode;
	पूर्णांक समयout;
पूर्ण;

/**
 * काष्ठा usb_data_stream_properties - usb streaming configuration क्रम adapter
 * @type: urb type
 * @count: count of used urbs
 * @endpoपूर्णांक: stream usb endpoपूर्णांक number
 * @u: जोड़ क्रम @bulk and @isoc
 */
काष्ठा usb_data_stream_properties अणु
#घोषणा USB_BULK  1
#घोषणा USB_ISOC  2
	u8 type;
	u8 count;
	u8 endpoपूर्णांक;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक buffersize; /* per URB */
		पूर्ण bulk;
		काष्ठा अणु
			पूर्णांक framesperurb;
			पूर्णांक framesize;
			पूर्णांक पूर्णांकerval;
		पूर्ण isoc;
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा dvb_usb_adapter_properties - properties of dvb usb device adapter
 * @caps: adapter capabilities
 * @pid_filter_count: pid count of adapter pid-filter
 * @pid_filter_ctrl: called to enable/disable pid-filter
 * @pid_filter: called to set/unset pid क्रम filtering
 * @stream: adapter usb stream configuration
 */
काष्ठा dvb_usb_adapter_properties अणु
#घोषणा MAX_NO_OF_FE_PER_ADAP 3
#घोषणा DVB_USB_ADAP_HAS_PID_FILTER               0x01
#घोषणा DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF 0x02
#घोषणा DVB_USB_ADAP_NEED_PID_FILTERING           0x04
	u8 caps;

	u8 pid_filter_count;
	पूर्णांक (*pid_filter_ctrl) (काष्ठा dvb_usb_adapter *, पूर्णांक);
	पूर्णांक (*pid_filter) (काष्ठा dvb_usb_adapter *, पूर्णांक, u16, पूर्णांक);

	काष्ठा usb_data_stream_properties stream;
पूर्ण;

/**
 * काष्ठा dvb_usb_device_properties - properties of a dvb-usb-device
 * @driver_name: name of the owning driver module
 * @owner: owner of the dvb_adapter
 * @adapter_nr: values from the DVB_DEFINE_MOD_OPT_ADAPTER_NR() macro
 * @bInterfaceNumber: usb पूर्णांकerface number driver binds
 * @size_of_priv: bytes allocated क्रम the driver निजी data
 * @generic_bulk_ctrl_endpoपूर्णांक: bulk control endpoपूर्णांक number क्रम sent
 * @generic_bulk_ctrl_endpoपूर्णांक_response: bulk control endpoपूर्णांक number क्रम
 *  receive
 * @generic_bulk_ctrl_delay: delay between bulk control sent and receive message
 * @probe: like probe on driver model
 * @disconnect: like disconnect on driver model
 * @identअगरy_state: called to determine the firmware state (cold or warm) and
 *  वापस possible firmware file name to be loaded
 * @firmware: name of the firmware file to be loaded
 * @करोwnload_firmware: called to करोwnload the firmware
 * @i2c_algo: i2c_algorithm अगर the device has i2c-adapter
 * @num_adapters: dvb usb device adapter count
 * @get_adapter_count: called to resolve adapter count
 * @adapter: array of all adapter properties of device
 * @घातer_ctrl: called to enable/disable घातer of the device
 * @पढ़ो_config: called to resolve device configuration
 * @पढ़ो_mac_address: called to resolve adapter mac-address
 * @frontend_attach: called to attach the possible frontends
 * @frontend_detach: called to detach the possible frontends
 * @tuner_attach: called to attach the possible tuners
 * @tuner_detach: called to detach the possible tuners
 * @frontend_ctrl: called to घातer on/off active frontend
 * @streaming_ctrl: called to start/stop the usb streaming of adapter
 * @init: called after adapters are created in order to finalize device
 *  configuration
 * @निकास: called when driver is unloaded
 * @get_rc_config: called to resolve used remote controller configuration
 * @get_stream_config: called to resolve input and output stream configuration
 *  of the adapter just beक्रमe streaming is started. input stream is transport
 *  stream from the demodulator and output stream is usb stream to host.
 */
काष्ठा dvb_usb_device_properties अणु
#घोषणा MAX_NO_OF_ADAPTER_PER_DEVICE 2
	स्थिर अक्षर *driver_name;
	काष्ठा module *owner;
	लघु *adapter_nr;

	u8 bInterfaceNumber;
	अचिन्हित पूर्णांक size_of_priv;
	u8 generic_bulk_ctrl_endpoपूर्णांक;
	u8 generic_bulk_ctrl_endpoपूर्णांक_response;
	अचिन्हित पूर्णांक generic_bulk_ctrl_delay;

	पूर्णांक (*probe)(काष्ठा dvb_usb_device *);
	व्योम (*disconnect)(काष्ठा dvb_usb_device *);
#घोषणा WARM                  0
#घोषणा COLD                  1
	पूर्णांक (*identअगरy_state) (काष्ठा dvb_usb_device *, स्थिर अक्षर **);
	स्थिर अक्षर *firmware;
#घोषणा RECONNECTS_USB        1
	पूर्णांक (*करोwnload_firmware) (काष्ठा dvb_usb_device *,
			स्थिर काष्ठा firmware *);

	काष्ठा i2c_algorithm *i2c_algo;

	अचिन्हित पूर्णांक num_adapters;
	पूर्णांक (*get_adapter_count) (काष्ठा dvb_usb_device *);
	काष्ठा dvb_usb_adapter_properties adapter[MAX_NO_OF_ADAPTER_PER_DEVICE];
	पूर्णांक (*घातer_ctrl) (काष्ठा dvb_usb_device *, पूर्णांक);
	पूर्णांक (*पढ़ो_config) (काष्ठा dvb_usb_device *d);
	पूर्णांक (*पढ़ो_mac_address) (काष्ठा dvb_usb_adapter *, u8 []);
	पूर्णांक (*frontend_attach) (काष्ठा dvb_usb_adapter *);
	पूर्णांक (*frontend_detach)(काष्ठा dvb_usb_adapter *);
	पूर्णांक (*tuner_attach) (काष्ठा dvb_usb_adapter *);
	पूर्णांक (*tuner_detach)(काष्ठा dvb_usb_adapter *);
	पूर्णांक (*frontend_ctrl) (काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*streaming_ctrl) (काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*init) (काष्ठा dvb_usb_device *);
	व्योम (*निकास) (काष्ठा dvb_usb_device *);
	पूर्णांक (*get_rc_config) (काष्ठा dvb_usb_device *, काष्ठा dvb_usb_rc *);
#घोषणा DVB_USB_FE_TS_TYPE_188        0
#घोषणा DVB_USB_FE_TS_TYPE_204        1
#घोषणा DVB_USB_FE_TS_TYPE_RAW        2
	पूर्णांक (*get_stream_config) (काष्ठा dvb_frontend *,  u8 *,
			काष्ठा usb_data_stream_properties *);
पूर्ण;

/**
 * काष्ठा usb_data_stream - generic object of an usb stream
 * @udev: USB device
 * @props: properties
 * @state: state of the data stream
 * @complete: complete callback
 * @urb_list: list of URBs
 * @buf_num: number of buffer allocated
 * @buf_size: size of each buffer in buf_list
 * @buf_list: array containing all allocate buffers क्रम streaming
 * @dma_addr: list of dma_addr_t क्रम each buffer in buf_list
 *
 * @urbs_initialized: number of URBs initialized
 * @urbs_submitted: number of URBs submitted
 * @user_priv: निजी poपूर्णांकer
 */
काष्ठा usb_data_stream अणु
#घोषणा MAX_NO_URBS_FOR_DATA_STREAM 10
	काष्ठा usb_device *udev;
	काष्ठा usb_data_stream_properties props;

#घोषणा USB_STATE_INIT    0x00
#घोषणा USB_STATE_URB_BUF 0x01
	u8 state;

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
 * काष्ठा dvb_usb_adapter - dvb adapter object on dvb usb device
 * @props: poपूर्णांकer to adapter properties
 * @stream: adapter the usb data stream
 * @id: index of this adapter (starting with 0)
 * @ts_type: transport stream, input stream, type
 * @suspend_resume_active: set when there is ongoing suspend / resume
 * @pid_filtering: is hardware pid_filtering used or not
 * @feed_count: current feed count
 * @max_feed_count: maimum feed count device can handle
 * @active_fe: active frontend
 * @state_bits: status bits
 * @dvb_adap: adapter dvb_adapter
 * @dmxdev: adapter dmxdev
 * @demux: adapter software demuxer
 * @dvb_net: adapter dvb_net पूर्णांकerfaces
 * @fe: adapter frontends
 * @fe_init: rerouted frontend-init function
 * @fe_sleep: rerouted frontend-sleep function
 */
काष्ठा dvb_usb_adapter अणु
	स्थिर काष्ठा dvb_usb_adapter_properties *props;
	काष्ठा usb_data_stream stream;
	u8 id;
	u8 ts_type;
	bool suspend_resume_active;
	bool pid_filtering;
	u8 feed_count;
	u8 max_feed_count;
	s8 active_fe;
#घोषणा ADAP_INIT                0
#घोषणा ADAP_SLEEP               1
#घोषणा ADAP_STREAMING           2
	अचिन्हित दीर्घ state_bits;

	/* dvb */
	काष्ठा dvb_adapter   dvb_adap;
	काष्ठा dmxdev        dmxdev;
	काष्ठा dvb_demux     demux;
	काष्ठा dvb_net       dvb_net;

	काष्ठा dvb_frontend *fe[MAX_NO_OF_FE_PER_ADAP];
	पूर्णांक (*fe_init[MAX_NO_OF_FE_PER_ADAP]) (काष्ठा dvb_frontend *);
	पूर्णांक (*fe_sleep[MAX_NO_OF_FE_PER_ADAP]) (काष्ठा dvb_frontend *);
पूर्ण;

/**
 * काष्ठा dvb_usb_device - dvb usb device object
 * @props: device properties
 * @name: device name
 * @rc_map: name of rc codes table
 * @rc_polling_active: set when RC polling is active
 * @पूर्णांकf: poपूर्णांकer to the device's काष्ठा usb_पूर्णांकerface
 * @udev: poपूर्णांकer to the device's काष्ठा usb_device
 * @rc: remote controller configuration
 * @घातered: indicated whether the device is घातer or not
 * @usb_mutex: mutex क्रम usb control messages
 * @i2c_mutex: mutex क्रम i2c-transfers
 * @i2c_adap: device's i2c-adapter
 * @adapter: adapters
 * @rc_dev: rc device क्रम the remote control
 * @rc_phys: rc path
 * @rc_query_work: work क्रम polling remote
 * @priv: निजी data of the actual driver (allocate by dvb usb, size defined
 *  in size_of_priv of dvb_usb_properties).
 */
काष्ठा dvb_usb_device अणु
	स्थिर काष्ठा dvb_usb_device_properties *props;
	स्थिर अक्षर *name;
	स्थिर अक्षर *rc_map;
	bool rc_polling_active;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_device *udev;
	काष्ठा dvb_usb_rc rc;
	पूर्णांक घातered;

	/* locking */
	काष्ठा mutex usb_mutex;

	/* i2c */
	काष्ठा mutex i2c_mutex;
	काष्ठा i2c_adapter i2c_adap;

	काष्ठा dvb_usb_adapter adapter[MAX_NO_OF_ADAPTER_PER_DEVICE];

	/* remote control */
	काष्ठा rc_dev *rc_dev;
	अक्षर rc_phys[64];
	काष्ठा delayed_work rc_query_work;

	व्योम *priv;
पूर्ण;

बाह्य पूर्णांक dvb_usbv2_probe(काष्ठा usb_पूर्णांकerface *,
		स्थिर काष्ठा usb_device_id *);
बाह्य व्योम dvb_usbv2_disconnect(काष्ठा usb_पूर्णांकerface *);
बाह्य पूर्णांक dvb_usbv2_suspend(काष्ठा usb_पूर्णांकerface *, pm_message_t);
बाह्य पूर्णांक dvb_usbv2_resume(काष्ठा usb_पूर्णांकerface *);
बाह्य पूर्णांक dvb_usbv2_reset_resume(काष्ठा usb_पूर्णांकerface *);

/* the generic पढ़ो/ग_लिखो method क्रम device control */
बाह्य पूर्णांक dvb_usbv2_generic_rw(काष्ठा dvb_usb_device *, u8 *, u16, u8 *, u16);
बाह्य पूर्णांक dvb_usbv2_generic_ग_लिखो(काष्ठा dvb_usb_device *, u8 *, u16);
/* caller must hold lock when locked versions are called */
बाह्य पूर्णांक dvb_usbv2_generic_rw_locked(काष्ठा dvb_usb_device *,
		u8 *, u16, u8 *, u16);
बाह्य पूर्णांक dvb_usbv2_generic_ग_लिखो_locked(काष्ठा dvb_usb_device *, u8 *, u16);

#पूर्ण_अगर
