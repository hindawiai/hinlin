<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#अगर_अघोषित __USBIP_COMMON_H
#घोषणा __USBIP_COMMON_H

#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/net.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/kcov.h>
#समावेश <uapi/linux/usbip.h>

#अघोषित pr_fmt

#अगर_घोषित DEBUG
#घोषणा pr_fmt(fmt)     KBUILD_MODNAME ": %s:%d: " fmt, __func__, __LINE__
#अन्यथा
#घोषणा pr_fmt(fmt)     KBUILD_MODNAME ": " fmt
#पूर्ण_अगर

क्रमागत अणु
	usbip_debug_xmit	= (1 << 0),
	usbip_debug_sysfs	= (1 << 1),
	usbip_debug_urb		= (1 << 2),
	usbip_debug_eh		= (1 << 3),

	usbip_debug_stub_cmp	= (1 << 8),
	usbip_debug_stub_dev	= (1 << 9),
	usbip_debug_stub_rx	= (1 << 10),
	usbip_debug_stub_tx	= (1 << 11),

	usbip_debug_vhci_rh	= (1 << 8),
	usbip_debug_vhci_hc	= (1 << 9),
	usbip_debug_vhci_rx	= (1 << 10),
	usbip_debug_vhci_tx	= (1 << 11),
	usbip_debug_vhci_sysfs  = (1 << 12)
पूर्ण;

#घोषणा usbip_dbg_flag_xmit	(usbip_debug_flag & usbip_debug_xmit)
#घोषणा usbip_dbg_flag_vhci_rh	(usbip_debug_flag & usbip_debug_vhci_rh)
#घोषणा usbip_dbg_flag_vhci_hc	(usbip_debug_flag & usbip_debug_vhci_hc)
#घोषणा usbip_dbg_flag_vhci_rx	(usbip_debug_flag & usbip_debug_vhci_rx)
#घोषणा usbip_dbg_flag_vhci_tx	(usbip_debug_flag & usbip_debug_vhci_tx)
#घोषणा usbip_dbg_flag_stub_rx	(usbip_debug_flag & usbip_debug_stub_rx)
#घोषणा usbip_dbg_flag_stub_tx	(usbip_debug_flag & usbip_debug_stub_tx)
#घोषणा usbip_dbg_flag_vhci_sysfs  (usbip_debug_flag & usbip_debug_vhci_sysfs)

बाह्य अचिन्हित दीर्घ usbip_debug_flag;
बाह्य काष्ठा device_attribute dev_attr_usbip_debug;

#घोषणा usbip_dbg_with_flag(flag, fmt, args...)		\
	करो अणु						\
		अगर (flag & usbip_debug_flag)		\
			pr_debug(fmt, ##args);		\
	पूर्ण जबतक (0)

#घोषणा usbip_dbg_sysfs(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_sysfs, fmt , ##args)
#घोषणा usbip_dbg_xmit(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_xmit, fmt , ##args)
#घोषणा usbip_dbg_urb(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_urb, fmt , ##args)
#घोषणा usbip_dbg_eh(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_eh, fmt , ##args)

#घोषणा usbip_dbg_vhci_rh(fmt, args...)	\
	usbip_dbg_with_flag(usbip_debug_vhci_rh, fmt , ##args)
#घोषणा usbip_dbg_vhci_hc(fmt, args...)	\
	usbip_dbg_with_flag(usbip_debug_vhci_hc, fmt , ##args)
#घोषणा usbip_dbg_vhci_rx(fmt, args...)	\
	usbip_dbg_with_flag(usbip_debug_vhci_rx, fmt , ##args)
#घोषणा usbip_dbg_vhci_tx(fmt, args...)	\
	usbip_dbg_with_flag(usbip_debug_vhci_tx, fmt , ##args)
#घोषणा usbip_dbg_vhci_sysfs(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_vhci_sysfs, fmt , ##args)

#घोषणा usbip_dbg_stub_cmp(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_stub_cmp, fmt , ##args)
#घोषणा usbip_dbg_stub_rx(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_stub_rx, fmt , ##args)
#घोषणा usbip_dbg_stub_tx(fmt, args...) \
	usbip_dbg_with_flag(usbip_debug_stub_tx, fmt , ##args)

/*
 * USB/IP request headers
 *
 * Each request is transferred across the network to its counterpart, which
 * facilitates the normal USB communication. The values contained in the headers
 * are basically the same as in a URB. Currently, four request types are
 * defined:
 *
 *  - USBIP_CMD_SUBMIT: a USB request block, corresponds to usb_submit_urb()
 *    (client to server)
 *
 *  - USBIP_RET_SUBMIT: the result of USBIP_CMD_SUBMIT
 *    (server to client)
 *
 *  - USBIP_CMD_UNLINK: an unlink request of a pending USBIP_CMD_SUBMIT,
 *    corresponds to usb_unlink_urb()
 *    (client to server)
 *
 *  - USBIP_RET_UNLINK: the result of USBIP_CMD_UNLINK
 *    (server to client)
 *
 */
#घोषणा USBIP_CMD_SUBMIT	0x0001
#घोषणा USBIP_CMD_UNLINK	0x0002
#घोषणा USBIP_RET_SUBMIT	0x0003
#घोषणा USBIP_RET_UNLINK	0x0004

#घोषणा USBIP_सूची_OUT	0x00
#घोषणा USBIP_सूची_IN	0x01

/*
 * Arbitrary limit क्रम the maximum number of isochronous packets in an URB,
 * compare क्रम example the uhci_submit_isochronous function in
 * drivers/usb/host/uhci-q.c
 */
#घोषणा USBIP_MAX_ISO_PACKETS 1024

/**
 * काष्ठा usbip_header_basic - data pertinent to every request
 * @command: the usbip request type
 * @seqnum: sequential number that identअगरies requests; incremented per
 *	    connection
 * @devid: specअगरies a remote USB device uniquely instead of busnum and devnum;
 *	   in the stub driver, this value is ((busnum << 16) | devnum)
 * @direction: direction of the transfer
 * @ep: endpoपूर्णांक number
 */
काष्ठा usbip_header_basic अणु
	__u32 command;
	__u32 seqnum;
	__u32 devid;
	__u32 direction;
	__u32 ep;
पूर्ण __packed;

/**
 * काष्ठा usbip_header_cmd_submit - USBIP_CMD_SUBMIT packet header
 * @transfer_flags: URB flags
 * @transfer_buffer_length: the data size क्रम (in) or (out) transfer
 * @start_frame: initial frame क्रम isochronous or पूर्णांकerrupt transfers
 * @number_of_packets: number of isochronous packets
 * @पूर्णांकerval: maximum समय क्रम the request on the server-side host controller
 * @setup: setup data क्रम a control request
 */
काष्ठा usbip_header_cmd_submit अणु
	__u32 transfer_flags;
	__s32 transfer_buffer_length;

	/* it is dअगरficult क्रम usbip to sync frames (reserved only?) */
	__s32 start_frame;
	__s32 number_of_packets;
	__s32 पूर्णांकerval;

	अचिन्हित अक्षर setup[8];
पूर्ण __packed;

/**
 * काष्ठा usbip_header_ret_submit - USBIP_RET_SUBMIT packet header
 * @status: वापस status of a non-iso request
 * @actual_length: number of bytes transferred
 * @start_frame: initial frame क्रम isochronous or पूर्णांकerrupt transfers
 * @number_of_packets: number of isochronous packets
 * @error_count: number of errors क्रम isochronous transfers
 */
काष्ठा usbip_header_ret_submit अणु
	__s32 status;
	__s32 actual_length;
	__s32 start_frame;
	__s32 number_of_packets;
	__s32 error_count;
पूर्ण __packed;

/**
 * काष्ठा usbip_header_cmd_unlink - USBIP_CMD_UNLINK packet header
 * @seqnum: the URB seqnum to unlink
 */
काष्ठा usbip_header_cmd_unlink अणु
	__u32 seqnum;
पूर्ण __packed;

/**
 * काष्ठा usbip_header_ret_unlink - USBIP_RET_UNLINK packet header
 * @status: वापस status of the request
 */
काष्ठा usbip_header_ret_unlink अणु
	__s32 status;
पूर्ण __packed;

/**
 * काष्ठा usbip_header - common header क्रम all usbip packets
 * @base: the basic header
 * @u: packet type dependent header
 */
काष्ठा usbip_header अणु
	काष्ठा usbip_header_basic base;

	जोड़ अणु
		काष्ठा usbip_header_cmd_submit	cmd_submit;
		काष्ठा usbip_header_ret_submit	ret_submit;
		काष्ठा usbip_header_cmd_unlink	cmd_unlink;
		काष्ठा usbip_header_ret_unlink	ret_unlink;
	पूर्ण u;
पूर्ण __packed;

/*
 * This is the same as usb_iso_packet_descriptor but packed क्रम pdu.
 */
काष्ठा usbip_iso_packet_descriptor अणु
	__u32 offset;
	__u32 length;			/* expected length */
	__u32 actual_length;
	__u32 status;
पूर्ण __packed;

क्रमागत usbip_side अणु
	USBIP_VHCI,
	USBIP_STUB,
	USBIP_VUDC,
पूर्ण;

/* event handler */
#घोषणा USBIP_EH_SHUTDOWN	(1 << 0)
#घोषणा USBIP_EH_BYE		(1 << 1)
#घोषणा USBIP_EH_RESET		(1 << 2)
#घोषणा USBIP_EH_UNUSABLE	(1 << 3)

#घोषणा	SDEV_EVENT_REMOVED	(USBIP_EH_SHUTDOWN | USBIP_EH_BYE)
#घोषणा	SDEV_EVENT_DOWN		(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
#घोषणा	SDEV_EVENT_ERROR_TCP	(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
#घोषणा	SDEV_EVENT_ERROR_SUBMIT	(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
#घोषणा	SDEV_EVENT_ERROR_MALLOC	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABLE)

#घोषणा VUDC_EVENT_REMOVED   (USBIP_EH_SHUTDOWN | USBIP_EH_RESET | USBIP_EH_BYE)
#घोषणा	VUDC_EVENT_DOWN		(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
#घोषणा	VUDC_EVENT_ERROR_TCP	(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
/* catastrophic emulated usb error */
#घोषणा	VUDC_EVENT_ERROR_USB	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABLE)
#घोषणा	VUDC_EVENT_ERROR_MALLOC	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABLE)

#घोषणा	VDEV_EVENT_REMOVED (USBIP_EH_SHUTDOWN | USBIP_EH_RESET | USBIP_EH_BYE)
#घोषणा	VDEV_EVENT_DOWN		(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
#घोषणा	VDEV_EVENT_ERROR_TCP	(USBIP_EH_SHUTDOWN | USBIP_EH_RESET)
#घोषणा	VDEV_EVENT_ERROR_MALLOC	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABLE)

/* a common काष्ठाure क्रम stub_device and vhci_device */
काष्ठा usbip_device अणु
	क्रमागत usbip_side side;
	क्रमागत usbip_device_status status;

	/* lock क्रम status */
	spinlock_t lock;

	/* mutex क्रम synchronizing sysfs store paths */
	काष्ठा mutex sysfs_lock;

	पूर्णांक sockfd;
	काष्ठा socket *tcp_socket;

	काष्ठा task_काष्ठा *tcp_rx;
	काष्ठा task_काष्ठा *tcp_tx;

	अचिन्हित दीर्घ event;
	रुको_queue_head_t eh_रुकोq;

	काष्ठा eh_ops अणु
		व्योम (*shutकरोwn)(काष्ठा usbip_device *);
		व्योम (*reset)(काष्ठा usbip_device *);
		व्योम (*unusable)(काष्ठा usbip_device *);
	पूर्ण eh_ops;

#अगर_घोषित CONFIG_KCOV
	u64 kcov_handle;
#पूर्ण_अगर
पूर्ण;

#घोषणा kthपढ़ो_get_run(thपढ़ोfn, data, namefmt, ...)			   \
(अणु									   \
	काष्ठा task_काष्ठा *__k						   \
		= kthपढ़ो_create(thपढ़ोfn, data, namefmt, ## __VA_ARGS__); \
	अगर (!IS_ERR(__k)) अणु						   \
		get_task_काष्ठा(__k);					   \
		wake_up_process(__k);					   \
	पूर्ण								   \
	__k;								   \
पूर्ण)

#घोषणा kthपढ़ो_stop_put(k)		\
	करो अणु				\
		kthपढ़ो_stop(k);	\
		put_task_काष्ठा(k);	\
	पूर्ण जबतक (0)

/* usbip_common.c */
व्योम usbip_dump_urb(काष्ठा urb *purb);
व्योम usbip_dump_header(काष्ठा usbip_header *pdu);

पूर्णांक usbip_recv(काष्ठा socket *sock, व्योम *buf, पूर्णांक size);

व्योम usbip_pack_pdu(काष्ठा usbip_header *pdu, काष्ठा urb *urb, पूर्णांक cmd,
		    पूर्णांक pack);
व्योम usbip_header_correct_endian(काष्ठा usbip_header *pdu, पूर्णांक send);

काष्ठा usbip_iso_packet_descriptor*
usbip_alloc_iso_desc_pdu(काष्ठा urb *urb, sमाप_प्रकार *bufflen);

/* some members of urb must be substituted beक्रमe. */
पूर्णांक usbip_recv_iso(काष्ठा usbip_device *ud, काष्ठा urb *urb);
व्योम usbip_pad_iso(काष्ठा usbip_device *ud, काष्ठा urb *urb);
पूर्णांक usbip_recv_xbuff(काष्ठा usbip_device *ud, काष्ठा urb *urb);

/* usbip_event.c */
पूर्णांक usbip_init_eh(व्योम);
व्योम usbip_finish_eh(व्योम);
पूर्णांक usbip_start_eh(काष्ठा usbip_device *ud);
व्योम usbip_stop_eh(काष्ठा usbip_device *ud);
व्योम usbip_event_add(काष्ठा usbip_device *ud, अचिन्हित दीर्घ event);
पूर्णांक usbip_event_happened(काष्ठा usbip_device *ud);
पूर्णांक usbip_in_eh(काष्ठा task_काष्ठा *task);

अटल अंतरभूत पूर्णांक पूर्णांकerface_to_busnum(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	वापस udev->bus->busnum;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकerface_to_devnum(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	वापस udev->devnum;
पूर्ण

#अगर_घोषित CONFIG_KCOV

अटल अंतरभूत व्योम usbip_kcov_handle_init(काष्ठा usbip_device *ud)
अणु
	ud->kcov_handle = kcov_common_handle();
पूर्ण

अटल अंतरभूत व्योम usbip_kcov_remote_start(काष्ठा usbip_device *ud)
अणु
	kcov_remote_start_common(ud->kcov_handle);
पूर्ण

अटल अंतरभूत व्योम usbip_kcov_remote_stop(व्योम)
अणु
	kcov_remote_stop();
पूर्ण

#अन्यथा /* CONFIG_KCOV */

अटल अंतरभूत व्योम usbip_kcov_handle_init(काष्ठा usbip_device *ud) अणु पूर्ण
अटल अंतरभूत व्योम usbip_kcov_remote_start(काष्ठा usbip_device *ud) अणु पूर्ण
अटल अंतरभूत व्योम usbip_kcov_remote_stop(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_KCOV */

#पूर्ण_अगर /* __USBIP_COMMON_H */
