<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * <linux/usb/gadget.h>
 *
 * We call the USB code inside a Linux-based peripheral device a "gadget"
 * driver, except क्रम the hardware-specअगरic bus glue.  One USB host can
 * talk to many USB gadमाला_लो, but the gadमाला_लो are only able to communicate
 * to one host.
 *
 *
 * (C) Copyright 2002-2004 by David Brownell
 * All Rights Reserved.
 *
 * This software is licensed under the GNU GPL version 2.
 */

#अगर_अघोषित __LINUX_USB_GADGET_H
#घोषणा __LINUX_USB_GADGET_H

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/usb/ch9.h>

#घोषणा UDC_TRACE_STR_MAX	512

काष्ठा usb_ep;

/**
 * काष्ठा usb_request - describes one i/o request
 * @buf: Buffer used क्रम data.  Always provide this; some controllers
 *	only use PIO, or करोn't use DMA क्रम some endpoपूर्णांकs.
 * @dma: DMA address corresponding to 'buf'.  If you don't set this
 *	field, and the usb controller needs one, it is responsible
 *	क्रम mapping and unmapping the buffer.
 * @sg: a scatterlist क्रम SG-capable controllers.
 * @num_sgs: number of SG entries
 * @num_mapped_sgs: number of SG entries mapped to DMA (पूर्णांकernal)
 * @length: Length of that data
 * @stream_id: The stream id, when USB3.0 bulk streams are being used
 * @is_last: Indicates अगर this is the last request of a stream_id beक्रमe
 *	चयनing to a dअगरferent stream (required क्रम DWC3 controllers).
 * @no_पूर्णांकerrupt: If true, hपूर्णांकs that no completion irq is needed.
 *	Helpful someबार with deep request queues that are handled
 *	directly by DMA controllers.
 * @zero: If true, when writing data, makes the last packet be "short"
 *     by adding a zero length packet as needed;
 * @लघु_not_ok: When पढ़ोing data, makes लघु packets be
 *     treated as errors (queue stops advancing till cleanup).
 * @dma_mapped: Indicates अगर request has been mapped to DMA (पूर्णांकernal)
 * @complete: Function called when request completes, so this request and
 *	its buffer may be re-used.  The function will always be called with
 *	पूर्णांकerrupts disabled, and it must not sleep.
 *	Reads terminate with a लघु packet, or when the buffer fills,
 *	whichever comes first.  When ग_लिखोs terminate, some data bytes
 *	will usually still be in flight (often in a hardware fअगरo).
 *	Errors (क्रम पढ़ोs or ग_लिखोs) stop the queue from advancing
 *	until the completion function वापसs, so that any transfers
 *	invalidated by the error may first be dequeued.
 * @context: For use by the completion callback
 * @list: For use by the gadget driver.
 * @frame_number: Reports the पूर्णांकerval number in (micro)frame in which the
 *	isochronous transfer was transmitted or received.
 * @status: Reports completion code, zero or a negative त्रुटि_सं.
 *	Normally, faults block the transfer queue from advancing until
 *	the completion callback वापसs.
 *	Code "-ESHUTDOWN" indicates completion caused by device disconnect,
 *	or when the driver disabled the endpoपूर्णांक.
 * @actual: Reports bytes transferred to/from the buffer.  For पढ़ोs (OUT
 *	transfers) this may be less than the requested length.  If the
 *	लघु_not_ok flag is set, लघु पढ़ोs are treated as errors
 *	even when status otherwise indicates successful completion.
 *	Note that क्रम ग_लिखोs (IN transfers) some data bytes may still
 *	reside in a device-side FIFO when the request is reported as
 *	complete.
 *
 * These are allocated/मुक्तd through the endpoपूर्णांक they're used with.  The
 * hardware's driver can add extra per-request data to the memory it वापसs,
 * which often aव्योमs separate memory allocations (potential failures),
 * later when the request is queued.
 *
 * Request flags affect request handling, such as whether a zero length
 * packet is written (the "zero" flag), whether a लघु पढ़ो should be
 * treated as an error (blocking request queue advance, the "short_not_ok"
 * flag), or hपूर्णांकing that an पूर्णांकerrupt is not required (the "no_interrupt"
 * flag, क्रम use with deep request queues).
 *
 * Bulk endpoपूर्णांकs can use any size buffers, and can also be used क्रम पूर्णांकerrupt
 * transfers. पूर्णांकerrupt-only endpoपूर्णांकs can be much less functional.
 *
 * NOTE:  this is analogous to 'struct urb' on the host side, except that
 * it's thinner and promotes more pre-allocation.
 */

काष्ठा usb_request अणु
	व्योम			*buf;
	अचिन्हित		length;
	dma_addr_t		dma;

	काष्ठा scatterlist	*sg;
	अचिन्हित		num_sgs;
	अचिन्हित		num_mapped_sgs;

	अचिन्हित		stream_id:16;
	अचिन्हित		is_last:1;
	अचिन्हित		no_पूर्णांकerrupt:1;
	अचिन्हित		zero:1;
	अचिन्हित		लघु_not_ok:1;
	अचिन्हित		dma_mapped:1;

	व्योम			(*complete)(काष्ठा usb_ep *ep,
					काष्ठा usb_request *req);
	व्योम			*context;
	काष्ठा list_head	list;

	अचिन्हित		frame_number;		/* ISO ONLY */

	पूर्णांक			status;
	अचिन्हित		actual;
पूर्ण;

/*-------------------------------------------------------------------------*/

/* endpoपूर्णांक-specअगरic parts of the api to the usb controller hardware.
 * unlike the urb model, (de)multiplexing layers are not required.
 * (so this api could slash overhead अगर used on the host side...)
 *
 * note that device side usb controllers commonly dअगरfer in how many
 * endpoपूर्णांकs they support, as well as their capabilities.
 */
काष्ठा usb_ep_ops अणु
	पूर्णांक (*enable) (काष्ठा usb_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc);
	पूर्णांक (*disable) (काष्ठा usb_ep *ep);
	व्योम (*dispose) (काष्ठा usb_ep *ep);

	काष्ठा usb_request *(*alloc_request) (काष्ठा usb_ep *ep,
		gfp_t gfp_flags);
	व्योम (*मुक्त_request) (काष्ठा usb_ep *ep, काष्ठा usb_request *req);

	पूर्णांक (*queue) (काष्ठा usb_ep *ep, काष्ठा usb_request *req,
		gfp_t gfp_flags);
	पूर्णांक (*dequeue) (काष्ठा usb_ep *ep, काष्ठा usb_request *req);

	पूर्णांक (*set_halt) (काष्ठा usb_ep *ep, पूर्णांक value);
	पूर्णांक (*set_wedge) (काष्ठा usb_ep *ep);

	पूर्णांक (*fअगरo_status) (काष्ठा usb_ep *ep);
	व्योम (*fअगरo_flush) (काष्ठा usb_ep *ep);
पूर्ण;

/**
 * काष्ठा usb_ep_caps - endpoपूर्णांक capabilities description
 * @type_control:Endpoपूर्णांक supports control type (reserved क्रम ep0).
 * @type_iso:Endpoपूर्णांक supports isochronous transfers.
 * @type_bulk:Endpoपूर्णांक supports bulk transfers.
 * @type_पूर्णांक:Endpoपूर्णांक supports पूर्णांकerrupt transfers.
 * @dir_in:Endpoपूर्णांक supports IN direction.
 * @dir_out:Endpoपूर्णांक supports OUT direction.
 */
काष्ठा usb_ep_caps अणु
	अचिन्हित type_control:1;
	अचिन्हित type_iso:1;
	अचिन्हित type_bulk:1;
	अचिन्हित type_पूर्णांक:1;
	अचिन्हित dir_in:1;
	अचिन्हित dir_out:1;
पूर्ण;

#घोषणा USB_EP_CAPS_TYPE_CONTROL     0x01
#घोषणा USB_EP_CAPS_TYPE_ISO         0x02
#घोषणा USB_EP_CAPS_TYPE_BULK        0x04
#घोषणा USB_EP_CAPS_TYPE_INT         0x08
#घोषणा USB_EP_CAPS_TYPE_ALL \
	(USB_EP_CAPS_TYPE_ISO | USB_EP_CAPS_TYPE_BULK | USB_EP_CAPS_TYPE_INT)
#घोषणा USB_EP_CAPS_सूची_IN           0x01
#घोषणा USB_EP_CAPS_सूची_OUT          0x02
#घोषणा USB_EP_CAPS_सूची_ALL  (USB_EP_CAPS_सूची_IN | USB_EP_CAPS_सूची_OUT)

#घोषणा USB_EP_CAPS(_type, _dir) \
	अणु \
		.type_control = !!(_type & USB_EP_CAPS_TYPE_CONTROL), \
		.type_iso = !!(_type & USB_EP_CAPS_TYPE_ISO), \
		.type_bulk = !!(_type & USB_EP_CAPS_TYPE_BULK), \
		.type_पूर्णांक = !!(_type & USB_EP_CAPS_TYPE_INT), \
		.dir_in = !!(_dir & USB_EP_CAPS_सूची_IN), \
		.dir_out = !!(_dir & USB_EP_CAPS_सूची_OUT), \
	पूर्ण

/**
 * काष्ठा usb_ep - device side representation of USB endpoपूर्णांक
 * @name:identअगरier क्रम the endpoपूर्णांक, such as "ep-a" or "ep9in-bulk"
 * @ops: Function poपूर्णांकers used to access hardware-specअगरic operations.
 * @ep_list:the gadget's ep_list holds all of its endpoपूर्णांकs
 * @caps:The काष्ठाure describing types and directions supported by enकरोपूर्णांक.
 * @enabled: The current endpoपूर्णांक enabled/disabled state.
 * @claimed: True अगर this endpoपूर्णांक is claimed by a function.
 * @maxpacket:The maximum packet size used on this endpoपूर्णांक.  The initial
 *	value can someबार be reduced (hardware allowing), according to
 *	the endpoपूर्णांक descriptor used to configure the endpoपूर्णांक.
 * @maxpacket_limit:The maximum packet size value which can be handled by this
 *	endpoपूर्णांक. It's set once by UDC driver when endpoपूर्णांक is initialized, and
 *	should not be changed. Should not be confused with maxpacket.
 * @max_streams: The maximum number of streams supported
 *	by this EP (0 - 16, actual number is 2^n)
 * @mult: multiplier, 'mult' value क्रम SS Isoc EPs
 * @maxburst: the maximum number of bursts supported by this EP (क्रम usb3)
 * @driver_data:क्रम use by the gadget driver.
 * @address: used to identअगरy the endpoपूर्णांक when finding descriptor that
 *	matches connection speed
 * @desc: endpoपूर्णांक descriptor.  This poपूर्णांकer is set beक्रमe the endpoपूर्णांक is
 *	enabled and reमुख्यs valid until the endpoपूर्णांक is disabled.
 * @comp_desc: In हाल of SuperSpeed support, this is the endpoपूर्णांक companion
 *	descriptor that is used to configure the endpoपूर्णांक
 *
 * the bus controller driver lists all the general purpose endpoपूर्णांकs in
 * gadget->ep_list.  the control endpoपूर्णांक (gadget->ep0) is not in that list,
 * and is accessed only in response to a driver setup() callback.
 */

काष्ठा usb_ep अणु
	व्योम			*driver_data;

	स्थिर अक्षर		*name;
	स्थिर काष्ठा usb_ep_ops	*ops;
	काष्ठा list_head	ep_list;
	काष्ठा usb_ep_caps	caps;
	bool			claimed;
	bool			enabled;
	अचिन्हित		maxpacket:16;
	अचिन्हित		maxpacket_limit:16;
	अचिन्हित		max_streams:16;
	अचिन्हित		mult:2;
	अचिन्हित		maxburst:5;
	u8			address;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor	*desc;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor	*comp_desc;
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_USB_GADGET)
व्योम usb_ep_set_maxpacket_limit(काष्ठा usb_ep *ep, अचिन्हित maxpacket_limit);
पूर्णांक usb_ep_enable(काष्ठा usb_ep *ep);
पूर्णांक usb_ep_disable(काष्ठा usb_ep *ep);
काष्ठा usb_request *usb_ep_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags);
व्योम usb_ep_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *req);
पूर्णांक usb_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req, gfp_t gfp_flags);
पूर्णांक usb_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req);
पूर्णांक usb_ep_set_halt(काष्ठा usb_ep *ep);
पूर्णांक usb_ep_clear_halt(काष्ठा usb_ep *ep);
पूर्णांक usb_ep_set_wedge(काष्ठा usb_ep *ep);
पूर्णांक usb_ep_fअगरo_status(काष्ठा usb_ep *ep);
व्योम usb_ep_fअगरo_flush(काष्ठा usb_ep *ep);
#अन्यथा
अटल अंतरभूत व्योम usb_ep_set_maxpacket_limit(काष्ठा usb_ep *ep,
		अचिन्हित maxpacket_limit)
अणु पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_enable(काष्ठा usb_ep *ep)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_disable(काष्ठा usb_ep *ep)
अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा usb_request *usb_ep_alloc_request(काष्ठा usb_ep *ep,
		gfp_t gfp_flags)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम usb_ep_मुक्त_request(काष्ठा usb_ep *ep,
		काष्ठा usb_request *req)
अणु पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
		gfp_t gfp_flags)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_set_halt(काष्ठा usb_ep *ep)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_clear_halt(काष्ठा usb_ep *ep)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_set_wedge(काष्ठा usb_ep *ep)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_ep_fअगरo_status(काष्ठा usb_ep *ep)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम usb_ep_fअगरo_flush(काष्ठा usb_ep *ep)
अणु पूर्ण
#पूर्ण_अगर /* USB_GADGET */

/*-------------------------------------------------------------------------*/

काष्ठा usb_dcd_config_params अणु
	__u8  bU1devExitLat;	/* U1 Device निकास Latency */
#घोषणा USB_DEFAULT_U1_DEV_EXIT_LAT	0x01	/* Less then 1 microsec */
	__le16 bU2DevExitLat;	/* U2 Device निकास Latency */
#घोषणा USB_DEFAULT_U2_DEV_EXIT_LAT	0x1F4	/* Less then 500 microsec */
	__u8 besl_baseline;	/* Recommended baseline BESL (0-15) */
	__u8 besl_deep;		/* Recommended deep BESL (0-15) */
#घोषणा USB_DEFAULT_BESL_UNSPECIFIED	0xFF	/* No recommended value */
पूर्ण;


काष्ठा usb_gadget;
काष्ठा usb_gadget_driver;
काष्ठा usb_udc;

/* the rest of the api to the controller hardware: device operations,
 * which करोn't involve endpoपूर्णांकs (or i/o).
 */
काष्ठा usb_gadget_ops अणु
	पूर्णांक	(*get_frame)(काष्ठा usb_gadget *);
	पूर्णांक	(*wakeup)(काष्ठा usb_gadget *);
	पूर्णांक	(*set_selfघातered) (काष्ठा usb_gadget *, पूर्णांक is_selfघातered);
	पूर्णांक	(*vbus_session) (काष्ठा usb_gadget *, पूर्णांक is_active);
	पूर्णांक	(*vbus_draw) (काष्ठा usb_gadget *, अचिन्हित mA);
	पूर्णांक	(*pullup) (काष्ठा usb_gadget *, पूर्णांक is_on);
	पूर्णांक	(*ioctl)(काष्ठा usb_gadget *,
				अचिन्हित code, अचिन्हित दीर्घ param);
	व्योम	(*get_config_params)(काष्ठा usb_gadget *,
				     काष्ठा usb_dcd_config_params *);
	पूर्णांक	(*udc_start)(काष्ठा usb_gadget *,
			काष्ठा usb_gadget_driver *);
	पूर्णांक	(*udc_stop)(काष्ठा usb_gadget *);
	व्योम	(*udc_set_speed)(काष्ठा usb_gadget *, क्रमागत usb_device_speed);
	व्योम	(*udc_set_ssp_rate)(काष्ठा usb_gadget *gadget,
			क्रमागत usb_ssp_rate rate);
	काष्ठा usb_ep *(*match_ep)(काष्ठा usb_gadget *,
			काष्ठा usb_endpoपूर्णांक_descriptor *,
			काष्ठा usb_ss_ep_comp_descriptor *);
पूर्ण;

/**
 * काष्ठा usb_gadget - represents a usb device
 * @work: (पूर्णांकernal use) Workqueue to be used क्रम sysfs_notअगरy()
 * @udc: काष्ठा usb_udc poपूर्णांकer क्रम this gadget
 * @ops: Function poपूर्णांकers used to access hardware-specअगरic operations.
 * @ep0: Endpoपूर्णांक zero, used when पढ़ोing or writing responses to
 *	driver setup() requests
 * @ep_list: List of other endpoपूर्णांकs supported by the device.
 * @speed: Speed of current connection to USB host.
 * @max_speed: Maximal speed the UDC can handle.  UDC must support this
 *      and all slower speeds.
 * @ssp_rate: Current connected SuperSpeed Plus संकेतing rate and lane count.
 * @max_ssp_rate: Maximum SuperSpeed Plus संकेतing rate and lane count the UDC
 *	can handle. The UDC must support this and all slower speeds and lower
 *	number of lanes.
 * @state: the state we are now (attached, suspended, configured, etc)
 * @name: Identअगरies the controller hardware type.  Used in diagnostics
 *	and someबार configuration.
 * @dev: Driver model state क्रम this असलtract device.
 * @isoch_delay: value from Set Isoch Delay request. Only valid on SS/SSP
 * @out_epnum: last used out ep number
 * @in_epnum: last used in ep number
 * @mA: last set mA value
 * @otg_caps: OTG capabilities of this gadget.
 * @sg_supported: true अगर we can handle scatter-gather
 * @is_otg: True अगर the USB device port uses a Mini-AB jack, so that the
 *	gadget driver must provide a USB OTG descriptor.
 * @is_a_peripheral: False unless is_otg, the "A" end of a USB cable
 *	is in the Mini-AB jack, and HNP has been used to चयन roles
 *	so that the "A" device currently acts as A-Peripheral, not A-Host.
 * @a_hnp_support: OTG device feature flag, indicating that the A-Host
 *	supports HNP at this port.
 * @a_alt_hnp_support: OTG device feature flag, indicating that the A-Host
 *	only supports HNP on a dअगरferent root port.
 * @b_hnp_enable: OTG device feature flag, indicating that the A-Host
 *	enabled HNP support.
 * @hnp_polling_support: OTG device feature flag, indicating अगर the OTG device
 *	in peripheral mode can support HNP polling.
 * @host_request_flag: OTG device feature flag, indicating अगर A-Peripheral
 *	or B-Peripheral wants to take host role.
 * @quirk_ep_out_aligned_size: epout requires buffer size to be aligned to
 *	MaxPacketSize.
 * @quirk_altset_not_supp: UDC controller करोesn't support alt settings.
 * @quirk_stall_not_supp: UDC controller करोesn't support stalling.
 * @quirk_zlp_not_supp: UDC controller करोesn't support ZLP.
 * @quirk_aव्योमs_skb_reserve: udc/platक्रमm wants to aव्योम skb_reserve() in
 *	u_ether.c to improve perक्रमmance.
 * @is_selfघातered: अगर the gadget is self-घातered.
 * @deactivated: True अगर gadget is deactivated - in deactivated state it cannot
 *	be connected.
 * @connected: True अगर gadget is connected.
 * @lpm_capable: If the gadget max_speed is FULL or HIGH, this flag
 *	indicates that it supports LPM as per the LPM ECN & errata.
 * @irq: the पूर्णांकerrupt number क्रम device controller.
 *
 * Gadमाला_लो have a mostly-portable "gadget driver" implementing device
 * functions, handling all usb configurations and पूर्णांकerfaces.  Gadget
 * drivers talk to hardware-specअगरic code indirectly, through ops vectors.
 * That insulates the gadget driver from hardware details, and packages
 * the hardware endpoपूर्णांकs through generic i/o queues.  The "usb_gadget"
 * and "usb_ep" पूर्णांकerfaces provide that insulation from the hardware.
 *
 * Except क्रम the driver data, all fields in this काष्ठाure are
 * पढ़ो-only to the gadget driver.  That driver data is part of the
 * "driver model" infraकाष्ठाure in 2.6 (and later) kernels, and क्रम
 * earlier प्रणालीs is grouped in a similar काष्ठाure that's not known
 * to the rest of the kernel.
 *
 * Values of the three OTG device feature flags are updated beक्रमe the
 * setup() call corresponding to USB_REQ_SET_CONFIGURATION, and beक्रमe
 * driver suspend() calls.  They are valid only when is_otg, and when the
 * device is acting as a B-Peripheral (so is_a_peripheral is false).
 */
काष्ठा usb_gadget अणु
	काष्ठा work_काष्ठा		work;
	काष्ठा usb_udc			*udc;
	/* पढ़ोonly to gadget driver */
	स्थिर काष्ठा usb_gadget_ops	*ops;
	काष्ठा usb_ep			*ep0;
	काष्ठा list_head		ep_list;	/* of usb_ep */
	क्रमागत usb_device_speed		speed;
	क्रमागत usb_device_speed		max_speed;

	/* USB SuperSpeed Plus only */
	क्रमागत usb_ssp_rate		ssp_rate;
	क्रमागत usb_ssp_rate		max_ssp_rate;

	क्रमागत usb_device_state		state;
	स्थिर अक्षर			*name;
	काष्ठा device			dev;
	अचिन्हित			isoch_delay;
	अचिन्हित			out_epnum;
	अचिन्हित			in_epnum;
	अचिन्हित			mA;
	काष्ठा usb_otg_caps		*otg_caps;

	अचिन्हित			sg_supported:1;
	अचिन्हित			is_otg:1;
	अचिन्हित			is_a_peripheral:1;
	अचिन्हित			b_hnp_enable:1;
	अचिन्हित			a_hnp_support:1;
	अचिन्हित			a_alt_hnp_support:1;
	अचिन्हित			hnp_polling_support:1;
	अचिन्हित			host_request_flag:1;
	अचिन्हित			quirk_ep_out_aligned_size:1;
	अचिन्हित			quirk_altset_not_supp:1;
	अचिन्हित			quirk_stall_not_supp:1;
	अचिन्हित			quirk_zlp_not_supp:1;
	अचिन्हित			quirk_aव्योमs_skb_reserve:1;
	अचिन्हित			is_selfघातered:1;
	अचिन्हित			deactivated:1;
	अचिन्हित			connected:1;
	अचिन्हित			lpm_capable:1;
	पूर्णांक				irq;
पूर्ण;
#घोषणा work_to_gadget(w)	(container_of((w), काष्ठा usb_gadget, work))

/* Interface to the device model */
अटल अंतरभूत व्योम set_gadget_data(काष्ठा usb_gadget *gadget, व्योम *data)
	अणु dev_set_drvdata(&gadget->dev, data); पूर्ण
अटल अंतरभूत व्योम *get_gadget_data(काष्ठा usb_gadget *gadget)
	अणु वापस dev_get_drvdata(&gadget->dev); पूर्ण
अटल अंतरभूत काष्ठा usb_gadget *dev_to_usb_gadget(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा usb_gadget, dev);
पूर्ण
अटल अंतरभूत काष्ठा usb_gadget *usb_get_gadget(काष्ठा usb_gadget *gadget)
अणु
	get_device(&gadget->dev);
	वापस gadget;
पूर्ण
अटल अंतरभूत व्योम usb_put_gadget(काष्ठा usb_gadget *gadget)
अणु
	put_device(&gadget->dev);
पूर्ण
बाह्य व्योम usb_initialize_gadget(काष्ठा device *parent,
		काष्ठा usb_gadget *gadget, व्योम (*release)(काष्ठा device *dev));
बाह्य पूर्णांक usb_add_gadget(काष्ठा usb_gadget *gadget);
बाह्य व्योम usb_del_gadget(काष्ठा usb_gadget *gadget);

/* Legacy device-model पूर्णांकerface */
बाह्य पूर्णांक usb_add_gadget_udc_release(काष्ठा device *parent,
		काष्ठा usb_gadget *gadget, व्योम (*release)(काष्ठा device *dev));
बाह्य पूर्णांक usb_add_gadget_udc(काष्ठा device *parent, काष्ठा usb_gadget *gadget);
बाह्य व्योम usb_del_gadget_udc(काष्ठा usb_gadget *gadget);
बाह्य अक्षर *usb_get_gadget_udc_name(व्योम);

/* iterates the non-control endpoपूर्णांकs; 'tmp' is a काष्ठा usb_ep poपूर्णांकer */
#घोषणा gadget_क्रम_each_ep(पंचांगp, gadget) \
	list_क्रम_each_entry(पंचांगp, &(gadget)->ep_list, ep_list)

/**
 * usb_ep_align - वापसs @len aligned to ep's maxpacketsize.
 * @ep: the endpoपूर्णांक whose maxpacketsize is used to align @len
 * @len: buffer size's length to align to @ep's maxpacketsize
 *
 * This helper is used to align buffer's size to an ep's maxpacketsize.
 */
अटल अंतरभूत माप_प्रकार usb_ep_align(काष्ठा usb_ep *ep, माप_प्रकार len)
अणु
	पूर्णांक max_packet_size = (माप_प्रकार)usb_endpoपूर्णांक_maxp(ep->desc) & 0x7ff;

	वापस round_up(len, max_packet_size);
पूर्ण

/**
 * usb_ep_align_maybe - वापसs @len aligned to ep's maxpacketsize अगर gadget
 *	requires quirk_ep_out_aligned_size, otherwise वापसs len.
 * @g: controller to check क्रम quirk
 * @ep: the endpoपूर्णांक whose maxpacketsize is used to align @len
 * @len: buffer size's length to align to @ep's maxpacketsize
 *
 * This helper is used in हाल it's required क्रम any reason to check and maybe
 * align buffer's size to an ep's maxpacketsize.
 */
अटल अंतरभूत माप_प्रकार
usb_ep_align_maybe(काष्ठा usb_gadget *g, काष्ठा usb_ep *ep, माप_प्रकार len)
अणु
	वापस g->quirk_ep_out_aligned_size ? usb_ep_align(ep, len) : len;
पूर्ण

/**
 * gadget_is_altset_supported - वापस true अगरf the hardware supports
 *	altsettings
 * @g: controller to check क्रम quirk
 */
अटल अंतरभूत पूर्णांक gadget_is_altset_supported(काष्ठा usb_gadget *g)
अणु
	वापस !g->quirk_altset_not_supp;
पूर्ण

/**
 * gadget_is_stall_supported - वापस true अगरf the hardware supports stalling
 * @g: controller to check क्रम quirk
 */
अटल अंतरभूत पूर्णांक gadget_is_stall_supported(काष्ठा usb_gadget *g)
अणु
	वापस !g->quirk_stall_not_supp;
पूर्ण

/**
 * gadget_is_zlp_supported - वापस true अगरf the hardware supports zlp
 * @g: controller to check क्रम quirk
 */
अटल अंतरभूत पूर्णांक gadget_is_zlp_supported(काष्ठा usb_gadget *g)
अणु
	वापस !g->quirk_zlp_not_supp;
पूर्ण

/**
 * gadget_aव्योमs_skb_reserve - वापस true अगरf the hardware would like to aव्योम
 *	skb_reserve to improve perक्रमmance.
 * @g: controller to check क्रम quirk
 */
अटल अंतरभूत पूर्णांक gadget_aव्योमs_skb_reserve(काष्ठा usb_gadget *g)
अणु
	वापस g->quirk_aव्योमs_skb_reserve;
पूर्ण

/**
 * gadget_is_dualspeed - वापस true अगरf the hardware handles high speed
 * @g: controller that might support both high and full speeds
 */
अटल अंतरभूत पूर्णांक gadget_is_dualspeed(काष्ठा usb_gadget *g)
अणु
	वापस g->max_speed >= USB_SPEED_HIGH;
पूर्ण

/**
 * gadget_is_superspeed() - वापस true अगर the hardware handles superspeed
 * @g: controller that might support superspeed
 */
अटल अंतरभूत पूर्णांक gadget_is_superspeed(काष्ठा usb_gadget *g)
अणु
	वापस g->max_speed >= USB_SPEED_SUPER;
पूर्ण

/**
 * gadget_is_superspeed_plus() - वापस true अगर the hardware handles
 *	superspeed plus
 * @g: controller that might support superspeed plus
 */
अटल अंतरभूत पूर्णांक gadget_is_superspeed_plus(काष्ठा usb_gadget *g)
अणु
	वापस g->max_speed >= USB_SPEED_SUPER_PLUS;
पूर्ण

/**
 * gadget_is_otg - वापस true अगरf the hardware is OTG-पढ़ोy
 * @g: controller that might have a Mini-AB connector
 *
 * This is a runसमय test, since kernels with a USB-OTG stack someबार
 * run on boards which only have a Mini-B (or Mini-A) connector.
 */
अटल अंतरभूत पूर्णांक gadget_is_otg(काष्ठा usb_gadget *g)
अणु
#अगर_घोषित CONFIG_USB_OTG
	वापस g->is_otg;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_USB_GADGET)
पूर्णांक usb_gadget_frame_number(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_wakeup(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_set_selfघातered(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_clear_selfघातered(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_vbus_connect(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA);
पूर्णांक usb_gadget_vbus_disconnect(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_connect(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_disconnect(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_deactivate(काष्ठा usb_gadget *gadget);
पूर्णांक usb_gadget_activate(काष्ठा usb_gadget *gadget);
#अन्यथा
अटल अंतरभूत पूर्णांक usb_gadget_frame_number(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_wakeup(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_set_selfघातered(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_clear_selfघातered(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_vbus_connect(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_vbus_disconnect(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_connect(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_disconnect(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_deactivate(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_activate(काष्ठा usb_gadget *gadget)
अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_USB_GADGET */

/*-------------------------------------------------------------------------*/

/**
 * काष्ठा usb_gadget_driver - driver क्रम usb gadget devices
 * @function: String describing the gadget's function
 * @max_speed: Highest speed the driver handles.
 * @setup: Invoked क्रम ep0 control requests that aren't handled by
 *	the hardware level driver. Most calls must be handled by
 *	the gadget driver, including descriptor and configuration
 *	management.  The 16 bit members of the setup data are in
 *	USB byte order. Called in_पूर्णांकerrupt; this may not sleep.  Driver
 *	queues a response to ep0, or वापसs negative to stall.
 * @disconnect: Invoked after all transfers have been stopped,
 *	when the host is disconnected.  May be called in_पूर्णांकerrupt; this
 *	may not sleep.  Some devices can't detect disconnect, so this might
 *	not be called except as part of controller shutकरोwn.
 * @bind: the driver's bind callback
 * @unbind: Invoked when the driver is unbound from a gadget,
 *	usually from rmmod (after a disconnect is reported).
 *	Called in a context that permits sleeping.
 * @suspend: Invoked on USB suspend.  May be called in_पूर्णांकerrupt.
 * @resume: Invoked on USB resume.  May be called in_पूर्णांकerrupt.
 * @reset: Invoked on USB bus reset. It is mandatory क्रम all gadget drivers
 *	and should be called in_पूर्णांकerrupt.
 * @driver: Driver model state क्रम this driver.
 * @udc_name: A name of UDC this driver should be bound to. If udc_name is शून्य,
 *	this driver will be bound to any available UDC.
 * @pending: UDC core निजी data used क्रम deferred probe of this driver.
 * @match_existing_only: If udc is not found, वापस an error and करोn't add this
 *      gadget driver to list of pending driver
 *
 * Devices are disabled till a gadget driver successfully bind()s, which
 * means the driver will handle setup() requests needed to क्रमागतerate (and
 * meet "chapter 9" requirements) then करो some useful work.
 *
 * If gadget->is_otg is true, the gadget driver must provide an OTG
 * descriptor during क्रमागतeration, or अन्यथा fail the bind() call.  In such
 * हालs, no USB traffic may flow until both bind() वापसs without
 * having called usb_gadget_disconnect(), and the USB host stack has
 * initialized.
 *
 * Drivers use hardware-specअगरic knowledge to configure the usb hardware.
 * endpoपूर्णांक addressing is only one of several hardware अक्षरacteristics that
 * are in descriptors the ep0 implementation वापसs from setup() calls.
 *
 * Except क्रम ep0 implementation, most driver code shouldn't need change to
 * run on top of dअगरferent usb controllers.  It'll use endpoपूर्णांकs set up by
 * that ep0 implementation.
 *
 * The usb controller driver handles a few standard usb requests.  Those
 * include set_address, and feature flags क्रम devices, पूर्णांकerfaces, and
 * endpoपूर्णांकs (the get_status, set_feature, and clear_feature requests).
 *
 * Accordingly, the driver's setup() callback must always implement all
 * get_descriptor requests, वापसing at least a device descriptor and
 * a configuration descriptor.  Drivers must make sure the endpoपूर्णांक
 * descriptors match any hardware स्थिरraपूर्णांकs. Some hardware also स्थिरrains
 * other descriptors. (The pxa250 allows only configurations 1, 2, or 3).
 *
 * The driver's setup() callback must also implement set_configuration,
 * and should also implement set_पूर्णांकerface, get_configuration, and
 * get_पूर्णांकerface.  Setting a configuration (or पूर्णांकerface) is where
 * endpoपूर्णांकs should be activated or (config 0) shut करोwn.
 *
 * (Note that only the शेष control endpoपूर्णांक is supported.  Neither
 * hosts nor devices generally support control traffic except to ep0.)
 *
 * Most devices will ignore USB suspend/resume operations, and so will
 * not provide those callbacks.  However, some may need to change modes
 * when the host is not दीर्घer directing those activities.  For example,
 * local controls (buttons, dials, etc) may need to be re-enabled since
 * the (remote) host can't करो that any दीर्घer; or an error state might
 * be cleared, to make the device behave identically whether or not
 * घातer is मुख्यtained.
 */
काष्ठा usb_gadget_driver अणु
	अक्षर			*function;
	क्रमागत usb_device_speed	max_speed;
	पूर्णांक			(*bind)(काष्ठा usb_gadget *gadget,
					काष्ठा usb_gadget_driver *driver);
	व्योम			(*unbind)(काष्ठा usb_gadget *);
	पूर्णांक			(*setup)(काष्ठा usb_gadget *,
					स्थिर काष्ठा usb_ctrlrequest *);
	व्योम			(*disconnect)(काष्ठा usb_gadget *);
	व्योम			(*suspend)(काष्ठा usb_gadget *);
	व्योम			(*resume)(काष्ठा usb_gadget *);
	व्योम			(*reset)(काष्ठा usb_gadget *);

	/* FIXME support safe rmmod */
	काष्ठा device_driver	driver;

	अक्षर			*udc_name;
	काष्ठा list_head	pending;
	अचिन्हित                match_existing_only:1;
पूर्ण;



/*-------------------------------------------------------------------------*/

/* driver modules रेजिस्टर and unरेजिस्टर, as usual.
 * these calls must be made in a context that can sleep.
 *
 * these will usually be implemented directly by the hardware-dependent
 * usb bus पूर्णांकerface driver, which will only support a single driver.
 */

/**
 * usb_gadget_probe_driver - probe a gadget driver
 * @driver: the driver being रेजिस्टरed
 * Context: can sleep
 *
 * Call this in your gadget driver's module initialization function,
 * to tell the underlying usb controller driver about your driver.
 * The @bind() function will be called to bind it to a gadget beक्रमe this
 * registration call वापसs.  It's expected that the @bind() function will
 * be in init sections.
 */
पूर्णांक usb_gadget_probe_driver(काष्ठा usb_gadget_driver *driver);

/**
 * usb_gadget_unरेजिस्टर_driver - unरेजिस्टर a gadget driver
 * @driver:the driver being unरेजिस्टरed
 * Context: can sleep
 *
 * Call this in your gadget driver's module cleanup function,
 * to tell the underlying usb controller that your driver is
 * going away.  If the controller is connected to a USB host,
 * it will first disconnect().  The driver is also requested
 * to unbind() and clean up any device state, beक्रमe this procedure
 * finally वापसs.  It's expected that the unbind() functions
 * will be in निकास sections, so may not be linked in some kernels.
 */
पूर्णांक usb_gadget_unरेजिस्टर_driver(काष्ठा usb_gadget_driver *driver);

/*-------------------------------------------------------------------------*/

/* utility to simplअगरy dealing with string descriptors */

/**
 * काष्ठा usb_string - wraps a C string and its USB id
 * @id:the (nonzero) ID क्रम this string
 * @s:the string, in UTF-8 encoding
 *
 * If you're using usb_gadget_get_string(), use this to wrap a string
 * together with its ID.
 */
काष्ठा usb_string अणु
	u8			id;
	स्थिर अक्षर		*s;
पूर्ण;

/**
 * काष्ठा usb_gadget_strings - a set of USB strings in a given language
 * @language:identअगरies the strings' language (0x0409 क्रम en-us)
 * @strings:array of strings with their ids
 *
 * If you're using usb_gadget_get_string(), use this to wrap all the
 * strings क्रम a given language.
 */
काष्ठा usb_gadget_strings अणु
	u16			language;	/* 0x0409 क्रम en-us */
	काष्ठा usb_string	*strings;
पूर्ण;

काष्ठा usb_gadget_string_container अणु
	काष्ठा list_head        list;
	u8                      *stash[];
पूर्ण;

/* put descriptor क्रम string with that id पूर्णांकo buf (buflen >= 256) */
पूर्णांक usb_gadget_get_string(स्थिर काष्ठा usb_gadget_strings *table, पूर्णांक id, u8 *buf);

/* check अगर the given language identअगरier is valid */
bool usb_validate_langid(u16 langid);

/*-------------------------------------------------------------------------*/

/* utility to simplअगरy managing config descriptors */

/* ग_लिखो vector of descriptors पूर्णांकo buffer */
पूर्णांक usb_descriptor_fillbuf(व्योम *, अचिन्हित,
		स्थिर काष्ठा usb_descriptor_header **);

/* build config descriptor from single descriptor vector */
पूर्णांक usb_gadget_config_buf(स्थिर काष्ठा usb_config_descriptor *config,
	व्योम *buf, अचिन्हित buflen, स्थिर काष्ठा usb_descriptor_header **desc);

/* copy a शून्य-terminated vector of descriptors */
काष्ठा usb_descriptor_header **usb_copy_descriptors(
		काष्ठा usb_descriptor_header **);

/**
 * usb_मुक्त_descriptors - मुक्त descriptors वापसed by usb_copy_descriptors()
 * @v: vector of descriptors
 */
अटल अंतरभूत व्योम usb_मुक्त_descriptors(काष्ठा usb_descriptor_header **v)
अणु
	kमुक्त(v);
पूर्ण

काष्ठा usb_function;
पूर्णांक usb_assign_descriptors(काष्ठा usb_function *f,
		काष्ठा usb_descriptor_header **fs,
		काष्ठा usb_descriptor_header **hs,
		काष्ठा usb_descriptor_header **ss,
		काष्ठा usb_descriptor_header **ssp);
व्योम usb_मुक्त_all_descriptors(काष्ठा usb_function *f);

काष्ठा usb_descriptor_header *usb_otg_descriptor_alloc(
				काष्ठा usb_gadget *gadget);
पूर्णांक usb_otg_descriptor_init(काष्ठा usb_gadget *gadget,
		काष्ठा usb_descriptor_header *otg_desc);
/*-------------------------------------------------------------------------*/

/* utility to simplअगरy map/unmap of usb_requests to/from DMA */

#अगर_घोषित	CONFIG_HAS_DMA
बाह्य पूर्णांक usb_gadget_map_request_by_dev(काष्ठा device *dev,
		काष्ठा usb_request *req, पूर्णांक is_in);
बाह्य पूर्णांक usb_gadget_map_request(काष्ठा usb_gadget *gadget,
		काष्ठा usb_request *req, पूर्णांक is_in);

बाह्य व्योम usb_gadget_unmap_request_by_dev(काष्ठा device *dev,
		काष्ठा usb_request *req, पूर्णांक is_in);
बाह्य व्योम usb_gadget_unmap_request(काष्ठा usb_gadget *gadget,
		काष्ठा usb_request *req, पूर्णांक is_in);
#अन्यथा /* !CONFIG_HAS_DMA */
अटल अंतरभूत पूर्णांक usb_gadget_map_request_by_dev(काष्ठा device *dev,
		काष्ठा usb_request *req, पूर्णांक is_in) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक usb_gadget_map_request(काष्ठा usb_gadget *gadget,
		काष्ठा usb_request *req, पूर्णांक is_in) अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत व्योम usb_gadget_unmap_request_by_dev(काष्ठा device *dev,
		काष्ठा usb_request *req, पूर्णांक is_in) अणु पूर्ण
अटल अंतरभूत व्योम usb_gadget_unmap_request(काष्ठा usb_gadget *gadget,
		काष्ठा usb_request *req, पूर्णांक is_in) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_HAS_DMA */

/*-------------------------------------------------------------------------*/

/* utility to set gadget state properly */

बाह्य व्योम usb_gadget_set_state(काष्ठा usb_gadget *gadget,
		क्रमागत usb_device_state state);

/*-------------------------------------------------------------------------*/

/* utility to tell udc core that the bus reset occurs */
बाह्य व्योम usb_gadget_udc_reset(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver);

/*-------------------------------------------------------------------------*/

/* utility to give requests back to the gadget layer */

बाह्य व्योम usb_gadget_giveback_request(काष्ठा usb_ep *ep,
		काष्ठा usb_request *req);

/*-------------------------------------------------------------------------*/

/* utility to find endpoपूर्णांक by name */

बाह्य काष्ठा usb_ep *gadget_find_ep_by_name(काष्ठा usb_gadget *g,
		स्थिर अक्षर *name);

/*-------------------------------------------------------------------------*/

/* utility to check अगर endpoपूर्णांक caps match descriptor needs */

बाह्य पूर्णांक usb_gadget_ep_match_desc(काष्ठा usb_gadget *gadget,
		काष्ठा usb_ep *ep, काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		काष्ठा usb_ss_ep_comp_descriptor *ep_comp);

/*-------------------------------------------------------------------------*/

/* utility to update vbus status क्रम udc core, it may be scheduled */
बाह्य व्योम usb_udc_vbus_handler(काष्ठा usb_gadget *gadget, bool status);

/*-------------------------------------------------------------------------*/

/* utility wrapping a simple endpoपूर्णांक selection policy */

बाह्य काष्ठा usb_ep *usb_ep_स्वतःconfig(काष्ठा usb_gadget *,
			काष्ठा usb_endpoपूर्णांक_descriptor *);


बाह्य काष्ठा usb_ep *usb_ep_स्वतःconfig_ss(काष्ठा usb_gadget *,
			काष्ठा usb_endpoपूर्णांक_descriptor *,
			काष्ठा usb_ss_ep_comp_descriptor *);

बाह्य व्योम usb_ep_स्वतःconfig_release(काष्ठा usb_ep *);

बाह्य व्योम usb_ep_स्वतःconfig_reset(काष्ठा usb_gadget *);

#पूर्ण_अगर /* __LINUX_USB_GADGET_H */
