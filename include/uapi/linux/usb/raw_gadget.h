<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * USB Raw Gadget driver.
 *
 * See Documentation/usb/raw-gadget.rst क्रम more details.
 */

#अगर_अघोषित _UAPI__LINUX_USB_RAW_GADGET_H
#घोषणा _UAPI__LINUX_USB_RAW_GADGET_H

#समावेश <यंत्र/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/ch9.h>

/* Maximum length of driver_name/device_name in the usb_raw_init काष्ठा. */
#घोषणा UDC_NAME_LENGTH_MAX 128

/*
 * काष्ठा usb_raw_init - argument क्रम USB_RAW_IOCTL_INIT ioctl.
 * @speed: The speed of the emulated USB device, takes the same values as
 *     the usb_device_speed क्रमागत: USB_SPEED_FULL, USB_SPEED_HIGH, etc.
 * @driver_name: The name of the UDC driver.
 * @device_name: The name of a UDC instance.
 *
 * The last two fields identअगरy a UDC the gadget driver should bind to.
 * For example, Dummy UDC has "dummy_udc" as its driver_name and "dummy_udc.N"
 * as its device_name, where N in the index of the Dummy UDC instance.
 * At the same समय the dwc2 driver that is used on Raspberry Pi Zero, has
 * "20980000.usb" as both driver_name and device_name.
 */
काष्ठा usb_raw_init अणु
	__u8	driver_name[UDC_NAME_LENGTH_MAX];
	__u8	device_name[UDC_NAME_LENGTH_MAX];
	__u8	speed;
पूर्ण;

/* The type of event fetched with the USB_RAW_IOCTL_EVENT_FETCH ioctl. */
क्रमागत usb_raw_event_type अणु
	USB_RAW_EVENT_INVALID = 0,

	/* This event is queued when the driver has bound to a UDC. */
	USB_RAW_EVENT_CONNECT = 1,

	/* This event is queued when a new control request arrived to ep0. */
	USB_RAW_EVENT_CONTROL = 2,

	/* The list might grow in the future. */
पूर्ण;

/*
 * काष्ठा usb_raw_event - argument क्रम USB_RAW_IOCTL_EVENT_FETCH ioctl.
 * @type: The type of the fetched event.
 * @length: Length of the data buffer. Updated by the driver and set to the
 *     actual length of the fetched event data.
 * @data: A buffer to store the fetched event data.
 *
 * Currently the fetched data buffer is empty क्रम USB_RAW_EVENT_CONNECT,
 * and contains काष्ठा usb_ctrlrequest क्रम USB_RAW_EVENT_CONTROL.
 */
काष्ठा usb_raw_event अणु
	__u32		type;
	__u32		length;
	__u8		data[0];
पूर्ण;

#घोषणा USB_RAW_IO_FLAGS_ZERO	0x0001
#घोषणा USB_RAW_IO_FLAGS_MASK	0x0001

अटल अंतरभूत पूर्णांक usb_raw_io_flags_valid(__u16 flags)
अणु
	वापस (flags & ~USB_RAW_IO_FLAGS_MASK) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक usb_raw_io_flags_zero(__u16 flags)
अणु
	वापस (flags & USB_RAW_IO_FLAGS_ZERO);
पूर्ण

/*
 * काष्ठा usb_raw_ep_io - argument क्रम USB_RAW_IOCTL_EP0/EP_WRITE/READ ioctls.
 * @ep: Endpoपूर्णांक handle as वापसed by USB_RAW_IOCTL_EP_ENABLE क्रम
 *     USB_RAW_IOCTL_EP_WRITE/READ. Ignored क्रम USB_RAW_IOCTL_EP0_WRITE/READ.
 * @flags: When USB_RAW_IO_FLAGS_ZERO is specअगरied, the zero flag is set on
 *     the submitted USB request, see include/linux/usb/gadget.h क्रम details.
 * @length: Length of data.
 * @data: Data to send क्रम USB_RAW_IOCTL_EP0/EP_WRITE. Buffer to store received
 *     data क्रम USB_RAW_IOCTL_EP0/EP_READ.
 */
काष्ठा usb_raw_ep_io अणु
	__u16		ep;
	__u16		flags;
	__u32		length;
	__u8		data[0];
पूर्ण;

/* Maximum number of non-control endpoपूर्णांकs in काष्ठा usb_raw_eps_info. */
#घोषणा USB_RAW_EPS_NUM_MAX	30

/* Maximum length of UDC endpoपूर्णांक name in काष्ठा usb_raw_ep_info. */
#घोषणा USB_RAW_EP_NAME_MAX	16

/* Used as addr in काष्ठा usb_raw_ep_info अगर endpoपूर्णांक accepts any address. */
#घोषणा USB_RAW_EP_ADDR_ANY	0xff

/*
 * काष्ठा usb_raw_ep_caps - exposes endpoपूर्णांक capabilities from काष्ठा usb_ep
 *     (technically from its member काष्ठा usb_ep_caps).
 */
काष्ठा usb_raw_ep_caps अणु
	__u32	type_control	: 1;
	__u32	type_iso	: 1;
	__u32	type_bulk	: 1;
	__u32	type_पूर्णांक	: 1;
	__u32	dir_in		: 1;
	__u32	dir_out		: 1;
पूर्ण;

/*
 * काष्ठा usb_raw_ep_limits - exposes endpoपूर्णांक limits from काष्ठा usb_ep.
 * @maxpacket_limit: Maximum packet size value supported by this endpoपूर्णांक.
 * @max_streams: maximum number of streams supported by this endpoपूर्णांक
 *     (actual number is 2^n).
 * @reserved: Empty, reserved क्रम potential future extensions.
 */
काष्ठा usb_raw_ep_limits अणु
	__u16	maxpacket_limit;
	__u16	max_streams;
	__u32	reserved;
पूर्ण;

/*
 * काष्ठा usb_raw_ep_info - stores inक्रमmation about a gadget endpoपूर्णांक.
 * @name: Name of the endpoपूर्णांक as it is defined in the UDC driver.
 * @addr: Address of the endpoपूर्णांक that must be specअगरied in the endpoपूर्णांक
 *     descriptor passed to USB_RAW_IOCTL_EP_ENABLE ioctl.
 * @caps: Endpoपूर्णांक capabilities.
 * @limits: Endpoपूर्णांक limits.
 */
काष्ठा usb_raw_ep_info अणु
	__u8				name[USB_RAW_EP_NAME_MAX];
	__u32				addr;
	काष्ठा usb_raw_ep_caps		caps;
	काष्ठा usb_raw_ep_limits	limits;
पूर्ण;

/*
 * काष्ठा usb_raw_eps_info - argument क्रम USB_RAW_IOCTL_EPS_INFO ioctl.
 * eps: Structures that store inक्रमmation about non-control endpoपूर्णांकs.
 */
काष्ठा usb_raw_eps_info अणु
	काष्ठा usb_raw_ep_info	eps[USB_RAW_EPS_NUM_MAX];
पूर्ण;

/*
 * Initializes a Raw Gadget instance.
 * Accepts a poपूर्णांकer to the usb_raw_init काष्ठा as an argument.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_INIT		_IOW('U', 0, काष्ठा usb_raw_init)

/*
 * Inकाष्ठाs Raw Gadget to bind to a UDC and start emulating a USB device.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_RUN		_IO('U', 1)

/*
 * A blocking ioctl that रुकोs क्रम an event and वापसs fetched event data to
 * the user.
 * Accepts a poपूर्णांकer to the usb_raw_event काष्ठा.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_EVENT_FETCH	_IOR('U', 2, काष्ठा usb_raw_event)

/*
 * Queues an IN (OUT क्रम READ) request as a response to the last setup request
 * received on endpoपूर्णांक 0 (provided that was an IN (OUT क्रम READ) request), and
 * रुकोs until the request is completed. Copies received data to user क्रम READ.
 * Accepts a poपूर्णांकer to the usb_raw_ep_io काष्ठा as an argument.
 * Returns length of transferred data on success or negative error code on
 * failure.
 */
#घोषणा USB_RAW_IOCTL_EP0_WRITE		_IOW('U', 3, काष्ठा usb_raw_ep_io)
#घोषणा USB_RAW_IOCTL_EP0_READ		_IOWR('U', 4, काष्ठा usb_raw_ep_io)

/*
 * Finds an endpoपूर्णांक that satisfies the parameters specअगरied in the provided
 * descriptors (address, transfer type, etc.) and enables it.
 * Accepts a poपूर्णांकer to the usb_raw_ep_descs काष्ठा as an argument.
 * Returns enabled endpoपूर्णांक handle on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_EP_ENABLE		_IOW('U', 5, काष्ठा usb_endpoपूर्णांक_descriptor)

/*
 * Disables specअगरied endpoपूर्णांक.
 * Accepts endpoपूर्णांक handle as an argument.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_EP_DISABLE	_IOW('U', 6, __u32)

/*
 * Queues an IN (OUT क्रम READ) request as a response to the last setup request
 * received on endpoपूर्णांक usb_raw_ep_io.ep (provided that was an IN (OUT क्रम READ)
 * request), and रुकोs until the request is completed. Copies received data to
 * user क्रम READ.
 * Accepts a poपूर्णांकer to the usb_raw_ep_io काष्ठा as an argument.
 * Returns length of transferred data on success or negative error code on
 * failure.
 */
#घोषणा USB_RAW_IOCTL_EP_WRITE		_IOW('U', 7, काष्ठा usb_raw_ep_io)
#घोषणा USB_RAW_IOCTL_EP_READ		_IOWR('U', 8, काष्ठा usb_raw_ep_io)

/*
 * Switches the gadget पूर्णांकo the configured state.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_CONFIGURE		_IO('U', 9)

/*
 * Constrains UDC VBUS घातer usage.
 * Accepts current limit in 2 mA units as an argument.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_VBUS_DRAW		_IOW('U', 10, __u32)

/*
 * Fills in the usb_raw_eps_info काष्ठाure with inक्रमmation about non-control
 * endpoपूर्णांकs available क्रम the currently connected UDC.
 * Returns the number of available endpoपूर्णांकs on success or negative error code
 * on failure.
 */
#घोषणा USB_RAW_IOCTL_EPS_INFO		_IOR('U', 11, काष्ठा usb_raw_eps_info)

/*
 * Stalls a pending control request on endpoपूर्णांक 0.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_EP0_STALL		_IO('U', 12)

/*
 * Sets or clears halt or wedge status of the endpoपूर्णांक.
 * Accepts endpoपूर्णांक handle as an argument.
 * Returns 0 on success or negative error code on failure.
 */
#घोषणा USB_RAW_IOCTL_EP_SET_HALT	_IOW('U', 13, __u32)
#घोषणा USB_RAW_IOCTL_EP_CLEAR_HALT	_IOW('U', 14, __u32)
#घोषणा USB_RAW_IOCTL_EP_SET_WEDGE	_IOW('U', 15, __u32)

#पूर्ण_अगर /* _UAPI__LINUX_USB_RAW_GADGET_H */
