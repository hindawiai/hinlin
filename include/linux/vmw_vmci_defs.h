<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMW_VMCI_DEF_H_
#घोषणा _VMW_VMCI_DEF_H_

#समावेश <linux/atomic.h>
#समावेश <linux/bits.h>

/* Register offsets. */
#घोषणा VMCI_STATUS_ADDR      0x00
#घोषणा VMCI_CONTROL_ADDR     0x04
#घोषणा VMCI_ICR_ADDR	      0x08
#घोषणा VMCI_IMR_ADDR         0x0c
#घोषणा VMCI_DATA_OUT_ADDR    0x10
#घोषणा VMCI_DATA_IN_ADDR     0x14
#घोषणा VMCI_CAPS_ADDR        0x18
#घोषणा VMCI_RESULT_LOW_ADDR  0x1c
#घोषणा VMCI_RESULT_HIGH_ADDR 0x20

/* Max number of devices. */
#घोषणा VMCI_MAX_DEVICES 1

/* Status रेजिस्टर bits. */
#घोषणा VMCI_STATUS_INT_ON     BIT(0)

/* Control रेजिस्टर bits. */
#घोषणा VMCI_CONTROL_RESET        BIT(0)
#घोषणा VMCI_CONTROL_INT_ENABLE   BIT(1)
#घोषणा VMCI_CONTROL_INT_DISABLE  BIT(2)

/* Capabilities रेजिस्टर bits. */
#घोषणा VMCI_CAPS_HYPERCALL     BIT(0)
#घोषणा VMCI_CAPS_GUESTCALL     BIT(1)
#घोषणा VMCI_CAPS_DATAGRAM      BIT(2)
#घोषणा VMCI_CAPS_NOTIFICATIONS BIT(3)
#घोषणा VMCI_CAPS_PPN64         BIT(4)

/* Interrupt Cause रेजिस्टर bits. */
#घोषणा VMCI_ICR_DATAGRAM      BIT(0)
#घोषणा VMCI_ICR_NOTIFICATION  BIT(1)

/* Interrupt Mask रेजिस्टर bits. */
#घोषणा VMCI_IMR_DATAGRAM      BIT(0)
#घोषणा VMCI_IMR_NOTIFICATION  BIT(1)

/* Maximum MSI/MSI-X पूर्णांकerrupt vectors in the device. */
#घोषणा VMCI_MAX_INTRS 2

/*
 * Supported पूर्णांकerrupt vectors.  There is one क्रम each ICR value above,
 * but here they indicate the position in the vector array/message ID.
 */
क्रमागत अणु
	VMCI_INTR_DATAGRAM = 0,
	VMCI_INTR_NOTIFICATION = 1,
पूर्ण;

/*
 * A single VMCI device has an upper limit of 128MB on the amount of
 * memory that can be used क्रम queue pairs. Since each queue pair
 * consists of at least two pages, the memory limit also dictates the
 * number of queue pairs a guest can create.
 */
#घोषणा VMCI_MAX_GUEST_QP_MEMORY ((माप_प्रकार)(128 * 1024 * 1024))
#घोषणा VMCI_MAX_GUEST_QP_COUNT  (VMCI_MAX_GUEST_QP_MEMORY / PAGE_SIZE / 2)

/*
 * There can be at most PAGE_SIZE करोorbells since there is one करोorbell
 * per byte in the करोorbell biपंचांगap page.
 */
#घोषणा VMCI_MAX_GUEST_DOORBELL_COUNT PAGE_SIZE

/*
 * Queues with pre-mapped data pages must be small, so that we करोn't pin
 * too much kernel memory (especially on vmkernel).  We limit a queuepair to
 * 32 KB, or 16 KB per queue क्रम symmetrical pairs.
 */
#घोषणा VMCI_MAX_PINNED_QP_MEMORY ((माप_प्रकार)(32 * 1024))

/*
 * We have a fixed set of resource IDs available in the VMX.
 * This allows us to have a very simple implementation since we अटलally
 * know how many will create datagram handles. If a new caller arrives and
 * we have run out of slots we can manually increment the maximum size of
 * available resource IDs.
 *
 * VMCI reserved hypervisor datagram resource IDs.
 */
क्रमागत अणु
	VMCI_RESOURCES_QUERY = 0,
	VMCI_GET_CONTEXT_ID = 1,
	VMCI_SET_NOTIFY_BITMAP = 2,
	VMCI_DOORBELL_LINK = 3,
	VMCI_DOORBELL_UNLINK = 4,
	VMCI_DOORBELL_NOTIFY = 5,
	/*
	 * VMCI_DATAGRAM_REQUEST_MAP and VMCI_DATAGRAM_REMOVE_MAP are
	 * obsoleted by the removal of VM to VM communication.
	 */
	VMCI_DATAGRAM_REQUEST_MAP = 6,
	VMCI_DATAGRAM_REMOVE_MAP = 7,
	VMCI_EVENT_SUBSCRIBE = 8,
	VMCI_EVENT_UNSUBSCRIBE = 9,
	VMCI_QUEUEPAIR_ALLOC = 10,
	VMCI_QUEUEPAIR_DETACH = 11,

	/*
	 * VMCI_VSOCK_VMX_LOOKUP was asचिन्हित to 12 क्रम Fusion 3.0/3.1,
	 * WS 7.0/7.1 and ESX 4.1
	 */
	VMCI_HGFS_TRANSPORT = 13,
	VMCI_UNITY_PBRPC_REGISTER = 14,
	VMCI_RPC_PRIVILEGED = 15,
	VMCI_RPC_UNPRIVILEGED = 16,
	VMCI_RESOURCE_MAX = 17,
पूर्ण;

/*
 * काष्ठा vmci_handle - Ownership inक्रमmation काष्ठाure
 * @context:    The VMX context ID.
 * @resource:   The resource ID (used क्रम locating in resource hash).
 *
 * The vmci_handle काष्ठाure is used to track resources used within
 * vmw_vmci.
 */
काष्ठा vmci_handle अणु
	u32 context;
	u32 resource;
पूर्ण;

#घोषणा vmci_make_handle(_cid, _rid) \
	(काष्ठा vmci_handle)अणु .context = _cid, .resource = _rid पूर्ण

अटल अंतरभूत bool vmci_handle_is_equal(काष्ठा vmci_handle h1,
					काष्ठा vmci_handle h2)
अणु
	वापस h1.context == h2.context && h1.resource == h2.resource;
पूर्ण

#घोषणा VMCI_INVALID_ID ~0
अटल स्थिर काष्ठा vmci_handle VMCI_INVALID_HANDLE = अणु
	.context = VMCI_INVALID_ID,
	.resource = VMCI_INVALID_ID
पूर्ण;

अटल अंतरभूत bool vmci_handle_is_invalid(काष्ठा vmci_handle h)
अणु
	वापस vmci_handle_is_equal(h, VMCI_INVALID_HANDLE);
पूर्ण

/*
 * The below defines can be used to send anonymous requests.
 * This also indicates that no response is expected.
 */
#घोषणा VMCI_ANON_SRC_CONTEXT_ID   VMCI_INVALID_ID
#घोषणा VMCI_ANON_SRC_RESOURCE_ID  VMCI_INVALID_ID
अटल स्थिर काष्ठा vmci_handle __maybe_unused VMCI_ANON_SRC_HANDLE = अणु
	.context = VMCI_ANON_SRC_CONTEXT_ID,
	.resource = VMCI_ANON_SRC_RESOURCE_ID
पूर्ण;

/* The lowest 16 context ids are reserved क्रम पूर्णांकernal use. */
#घोषणा VMCI_RESERVED_CID_LIMIT ((u32) 16)

/*
 * Hypervisor context id, used क्रम calling पूर्णांकo hypervisor
 * supplied services from the VM.
 */
#घोषणा VMCI_HYPERVISOR_CONTEXT_ID 0

/*
 * Well-known context id, a logical context that contains a set of
 * well-known services. This context ID is now obsolete.
 */
#घोषणा VMCI_WELL_KNOWN_CONTEXT_ID 1

/*
 * Context ID used by host endpoपूर्णांकs.
 */
#घोषणा VMCI_HOST_CONTEXT_ID  2

#घोषणा VMCI_CONTEXT_IS_VM(_cid) (VMCI_INVALID_ID != (_cid) &&		\
				  (_cid) > VMCI_HOST_CONTEXT_ID)

/*
 * The VMCI_CONTEXT_RESOURCE_ID is used together with vmci_make_handle to make
 * handles that refer to a specअगरic context.
 */
#घोषणा VMCI_CONTEXT_RESOURCE_ID 0

/*
 * VMCI error codes.
 */
क्रमागत अणु
	VMCI_SUCCESS_QUEUEPAIR_ATTACH	= 5,
	VMCI_SUCCESS_QUEUEPAIR_CREATE	= 4,
	VMCI_SUCCESS_LAST_DETACH	= 3,
	VMCI_SUCCESS_ACCESS_GRANTED	= 2,
	VMCI_SUCCESS_ENTRY_DEAD		= 1,
	VMCI_SUCCESS			 = 0,
	VMCI_ERROR_INVALID_RESOURCE	 = (-1),
	VMCI_ERROR_INVALID_ARGS		 = (-2),
	VMCI_ERROR_NO_MEM		 = (-3),
	VMCI_ERROR_DATAGRAM_FAILED	 = (-4),
	VMCI_ERROR_MORE_DATA		 = (-5),
	VMCI_ERROR_NO_MORE_DATAGRAMS	 = (-6),
	VMCI_ERROR_NO_ACCESS		 = (-7),
	VMCI_ERROR_NO_HANDLE		 = (-8),
	VMCI_ERROR_DUPLICATE_ENTRY	 = (-9),
	VMCI_ERROR_DST_UNREACHABLE	 = (-10),
	VMCI_ERROR_PAYLOAD_TOO_LARGE	 = (-11),
	VMCI_ERROR_INVALID_PRIV		 = (-12),
	VMCI_ERROR_GENERIC		 = (-13),
	VMCI_ERROR_PAGE_ALREADY_SHARED	 = (-14),
	VMCI_ERROR_CANNOT_SHARE_PAGE	 = (-15),
	VMCI_ERROR_CANNOT_UNSHARE_PAGE	 = (-16),
	VMCI_ERROR_NO_PROCESS		 = (-17),
	VMCI_ERROR_NO_DATAGRAM		 = (-18),
	VMCI_ERROR_NO_RESOURCES		 = (-19),
	VMCI_ERROR_UNAVAILABLE		 = (-20),
	VMCI_ERROR_NOT_FOUND		 = (-21),
	VMCI_ERROR_ALREADY_EXISTS	 = (-22),
	VMCI_ERROR_NOT_PAGE_ALIGNED	 = (-23),
	VMCI_ERROR_INVALID_SIZE		 = (-24),
	VMCI_ERROR_REGION_ALREADY_SHARED = (-25),
	VMCI_ERROR_TIMEOUT		 = (-26),
	VMCI_ERROR_DATAGRAM_INCOMPLETE	 = (-27),
	VMCI_ERROR_INCORRECT_IRQL	 = (-28),
	VMCI_ERROR_EVENT_UNKNOWN	 = (-29),
	VMCI_ERROR_OBSOLETE		 = (-30),
	VMCI_ERROR_QUEUEPAIR_MISMATCH	 = (-31),
	VMCI_ERROR_QUEUEPAIR_NOTSET	 = (-32),
	VMCI_ERROR_QUEUEPAIR_NOTOWNER	 = (-33),
	VMCI_ERROR_QUEUEPAIR_NOTATTACHED = (-34),
	VMCI_ERROR_QUEUEPAIR_NOSPACE	 = (-35),
	VMCI_ERROR_QUEUEPAIR_NODATA	 = (-36),
	VMCI_ERROR_BUSMEM_INVALIDATION	 = (-37),
	VMCI_ERROR_MODULE_NOT_LOADED	 = (-38),
	VMCI_ERROR_DEVICE_NOT_FOUND	 = (-39),
	VMCI_ERROR_QUEUEPAIR_NOT_READY	 = (-40),
	VMCI_ERROR_WOULD_BLOCK		 = (-41),

	/* VMCI clients should वापस error code within this range */
	VMCI_ERROR_CLIENT_MIN		 = (-500),
	VMCI_ERROR_CLIENT_MAX		 = (-550),

	/* Internal error codes. */
	VMCI_SHAREDMEM_ERROR_BAD_CONTEXT = (-1000),
पूर्ण;

/* VMCI reserved events. */
क्रमागत अणु
	/* Only applicable to guest endpoपूर्णांकs */
	VMCI_EVENT_CTX_ID_UPDATE  = 0,

	/* Applicable to guest and host */
	VMCI_EVENT_CTX_REMOVED	  = 1,

	/* Only applicable to guest endpoपूर्णांकs */
	VMCI_EVENT_QP_RESUMED	  = 2,

	/* Applicable to guest and host */
	VMCI_EVENT_QP_PEER_ATTACH = 3,

	/* Applicable to guest and host */
	VMCI_EVENT_QP_PEER_DETACH = 4,

	/*
	 * Applicable to VMX and vmk.  On vmk,
	 * this event has the Context payload type.
	 */
	VMCI_EVENT_MEM_ACCESS_ON  = 5,

	/*
	 * Applicable to VMX and vmk.  Same as
	 * above क्रम the payload type.
	 */
	VMCI_EVENT_MEM_ACCESS_OFF = 6,
	VMCI_EVENT_MAX		  = 7,
पूर्ण;

/*
 * Of the above events, a few are reserved क्रम use in the VMX, and
 * other endpoपूर्णांकs (guest and host kernel) should not use them. For
 * the rest of the events, we allow both host and guest endpoपूर्णांकs to
 * subscribe to them, to मुख्यtain the same API क्रम host and guest
 * endpoपूर्णांकs.
 */
#घोषणा VMCI_EVENT_VALID_VMX(_event) ((_event) == VMCI_EVENT_MEM_ACCESS_ON || \
				      (_event) == VMCI_EVENT_MEM_ACCESS_OFF)

#घोषणा VMCI_EVENT_VALID(_event) ((_event) < VMCI_EVENT_MAX &&		\
				  !VMCI_EVENT_VALID_VMX(_event))

/* Reserved guest datagram resource ids. */
#घोषणा VMCI_EVENT_HANDLER 0

/*
 * VMCI coarse-grained privileges (per context or host
 * process/endpoपूर्णांक. An entity with the restricted flag is only
 * allowed to पूर्णांकeract with the hypervisor and trusted entities.
 */
क्रमागत अणु
	VMCI_NO_PRIVILEGE_FLAGS = 0,
	VMCI_PRIVILEGE_FLAG_RESTRICTED = 1,
	VMCI_PRIVILEGE_FLAG_TRUSTED = 2,
	VMCI_PRIVILEGE_ALL_FLAGS = (VMCI_PRIVILEGE_FLAG_RESTRICTED |
				    VMCI_PRIVILEGE_FLAG_TRUSTED),
	VMCI_DEFAULT_PROC_PRIVILEGE_FLAGS = VMCI_NO_PRIVILEGE_FLAGS,
	VMCI_LEAST_PRIVILEGE_FLAGS = VMCI_PRIVILEGE_FLAG_RESTRICTED,
	VMCI_MAX_PRIVILEGE_FLAGS = VMCI_PRIVILEGE_FLAG_TRUSTED,
पूर्ण;

/* 0 through VMCI_RESERVED_RESOURCE_ID_MAX are reserved. */
#घोषणा VMCI_RESERVED_RESOURCE_ID_MAX 1023

/*
 * Driver version.
 *
 * Increment major version when you make an incompatible change.
 * Compatibility goes both ways (old driver with new executable
 * as well as new driver with old executable).
 */

/* Never change VMCI_VERSION_SHIFT_WIDTH */
#घोषणा VMCI_VERSION_SHIFT_WIDTH 16
#घोषणा VMCI_MAKE_VERSION(_major, _minor)			\
	((_major) << VMCI_VERSION_SHIFT_WIDTH | (u16) (_minor))

#घोषणा VMCI_VERSION_MAJOR(v)  ((u32) (v) >> VMCI_VERSION_SHIFT_WIDTH)
#घोषणा VMCI_VERSION_MINOR(v)  ((u16) (v))

/*
 * VMCI_VERSION is always the current version.  Subsequently listed
 * versions are ways of detecting previous versions of the connecting
 * application (i.e., VMX).
 *
 * VMCI_VERSION_NOVMVM: This version हटाओd support क्रम VM to VM
 * communication.
 *
 * VMCI_VERSION_NOTIFY: This version पूर्णांकroduced करोorbell notअगरication
 * support.
 *
 * VMCI_VERSION_HOSTQP: This version पूर्णांकroduced host end poपूर्णांक support
 * क्रम hosted products.
 *
 * VMCI_VERSION_PREHOSTQP: This is the version prior to the aकरोption of
 * support क्रम host end-poपूर्णांकs.
 *
 * VMCI_VERSION_PREVERS2: This fictional version number is पूर्णांकended to
 * represent the version of a VMX which करोesn't call पूर्णांकo the driver
 * with ioctl VERSION2 and thus करोesn't establish its version with the
 * driver.
 */

#घोषणा VMCI_VERSION                VMCI_VERSION_NOVMVM
#घोषणा VMCI_VERSION_NOVMVM         VMCI_MAKE_VERSION(11, 0)
#घोषणा VMCI_VERSION_NOTIFY         VMCI_MAKE_VERSION(10, 0)
#घोषणा VMCI_VERSION_HOSTQP         VMCI_MAKE_VERSION(9, 0)
#घोषणा VMCI_VERSION_PREHOSTQP      VMCI_MAKE_VERSION(8, 0)
#घोषणा VMCI_VERSION_PREVERS2       VMCI_MAKE_VERSION(1, 0)

#घोषणा VMCI_SOCKETS_MAKE_VERSION(_p)					\
	((((_p)[0] & 0xFF) << 24) | (((_p)[1] & 0xFF) << 16) | ((_p)[2]))

/*
 * The VMCI IOCTLs.  We use identity code 7, as noted in ioctl-number.h, and
 * we start at sequence 9f.  This gives us the same values that our shipping
 * products use, starting at 1951, provided we leave out the direction and
 * काष्ठाure size.  Note that VMMon occupies the block following us, starting
 * at 2001.
 */
#घोषणा IOCTL_VMCI_VERSION			_IO(7, 0x9f)	/* 1951 */
#घोषणा IOCTL_VMCI_INIT_CONTEXT			_IO(7, 0xa0)
#घोषणा IOCTL_VMCI_QUEUEPAIR_SETVA		_IO(7, 0xa4)
#घोषणा IOCTL_VMCI_NOTIFY_RESOURCE		_IO(7, 0xa5)
#घोषणा IOCTL_VMCI_NOTIFICATIONS_RECEIVE	_IO(7, 0xa6)
#घोषणा IOCTL_VMCI_VERSION2			_IO(7, 0xa7)
#घोषणा IOCTL_VMCI_QUEUEPAIR_ALLOC		_IO(7, 0xa8)
#घोषणा IOCTL_VMCI_QUEUEPAIR_SETPAGEखाता	_IO(7, 0xa9)
#घोषणा IOCTL_VMCI_QUEUEPAIR_DETACH		_IO(7, 0xaa)
#घोषणा IOCTL_VMCI_DATAGRAM_SEND		_IO(7, 0xab)
#घोषणा IOCTL_VMCI_DATAGRAM_RECEIVE		_IO(7, 0xac)
#घोषणा IOCTL_VMCI_CTX_ADD_NOTIFICATION		_IO(7, 0xaf)
#घोषणा IOCTL_VMCI_CTX_REMOVE_NOTIFICATION	_IO(7, 0xb0)
#घोषणा IOCTL_VMCI_CTX_GET_CPT_STATE		_IO(7, 0xb1)
#घोषणा IOCTL_VMCI_CTX_SET_CPT_STATE		_IO(7, 0xb2)
#घोषणा IOCTL_VMCI_GET_CONTEXT_ID		_IO(7, 0xb3)
#घोषणा IOCTL_VMCI_SOCKETS_VERSION		_IO(7, 0xb4)
#घोषणा IOCTL_VMCI_SOCKETS_GET_AF_VALUE		_IO(7, 0xb8)
#घोषणा IOCTL_VMCI_SOCKETS_GET_LOCAL_CID	_IO(7, 0xb9)
#घोषणा IOCTL_VMCI_SET_NOTIFY			_IO(7, 0xcb)	/* 1995 */
/*IOCTL_VMMON_START				_IO(7, 0xd1)*/	/* 2001 */

/*
 * काष्ठा vmci_queue_header - VMCI Queue Header inक्रमmation.
 *
 * A Queue cannot stand by itself as deचिन्हित.  Each Queue's header
 * contains a poपूर्णांकer पूर्णांकo itself (the producer_tail) and पूर्णांकo its peer
 * (consumer_head).  The reason क्रम the separation is one of
 * accessibility: Each end-poपूर्णांक can modअगरy two things: where the next
 * location to enqueue is within its produce_q (producer_tail); and
 * where the next dequeue location is in its consume_q (consumer_head).
 *
 * An end-poपूर्णांक cannot modअगरy the poपूर्णांकers of its peer (guest to
 * guest; NOTE that in the host both queue headers are mapped r/w).
 * But, each end-poपूर्णांक needs पढ़ो access to both Queue header
 * काष्ठाures in order to determine how much space is used (or left)
 * in the Queue.  This is because क्रम an end-poपूर्णांक to know how full
 * its produce_q is, it needs to use the consumer_head that poपूर्णांकs पूर्णांकo
 * the produce_q but -that- consumer_head is in the Queue header क्रम
 * that end-poपूर्णांकs consume_q.
 *
 * Thoroughly confused?  Sorry.
 *
 * producer_tail: the poपूर्णांक to enqueue new entrants.  When you approach
 * a line in a store, क्रम example, you walk up to the tail.
 *
 * consumer_head: the poपूर्णांक in the queue from which the next element is
 * dequeued.  In other words, who is next in line is he who is at the
 * head of the line.
 *
 * Also, producer_tail poपूर्णांकs to an empty byte in the Queue, whereas
 * consumer_head poपूर्णांकs to a valid byte of data (unless producer_tail ==
 * consumer_head in which हाल consumer_head करोes not poपूर्णांक to a valid
 * byte of data).
 *
 * For a queue of buffer 'size' bytes, the tail and head poपूर्णांकers will be in
 * the range [0, size-1].
 *
 * If produce_q_header->producer_tail == consume_q_header->consumer_head
 * then the produce_q is empty.
 */
काष्ठा vmci_queue_header अणु
	/* All fields are 64bit and aligned. */
	काष्ठा vmci_handle handle;	/* Identअगरier. */
	u64 producer_tail;	/* Offset in this queue. */
	u64 consumer_head;	/* Offset in peer queue. */
पूर्ण;

/*
 * काष्ठा vmci_datagram - Base काष्ठा क्रम vmci datagrams.
 * @dst:        A vmci_handle that tracks the destination of the datagram.
 * @src:        A vmci_handle that tracks the source of the datagram.
 * @payload_size:       The size of the payload.
 *
 * vmci_datagram काष्ठाs are used when sending vmci datagrams.  They include
 * the necessary source and destination inक्रमmation to properly route
 * the inक्रमmation aदीर्घ with the size of the package.
 */
काष्ठा vmci_datagram अणु
	काष्ठा vmci_handle dst;
	काष्ठा vmci_handle src;
	u64 payload_size;
पूर्ण;

/*
 * Second flag is क्रम creating a well-known handle instead of a per context
 * handle.  Next flag is क्रम deferring datagram delivery, so that the
 * datagram callback is invoked in a delayed context (not पूर्णांकerrupt context).
 */
#घोषणा VMCI_FLAG_DG_NONE          0
#घोषणा VMCI_FLAG_WELLKNOWN_DG_HND BIT(0)
#घोषणा VMCI_FLAG_ANYCID_DG_HND    BIT(1)
#घोषणा VMCI_FLAG_DG_DELAYED_CB    BIT(2)

/*
 * Maximum supported size of a VMCI datagram क्रम routable datagrams.
 * Datagrams going to the hypervisor are allowed to be larger.
 */
#घोषणा VMCI_MAX_DG_SIZE (17 * 4096)
#घोषणा VMCI_MAX_DG_PAYLOAD_SIZE (VMCI_MAX_DG_SIZE - \
				  माप(काष्ठा vmci_datagram))
#घोषणा VMCI_DG_PAYLOAD(_dg) (व्योम *)((अक्षर *)(_dg) +			\
				      माप(काष्ठा vmci_datagram))
#घोषणा VMCI_DG_HEADERSIZE माप(काष्ठा vmci_datagram)
#घोषणा VMCI_DG_SIZE(_dg) (VMCI_DG_HEADERSIZE + (माप_प्रकार)(_dg)->payload_size)
#घोषणा VMCI_DG_SIZE_ALIGNED(_dg) ((VMCI_DG_SIZE(_dg) + 7) & (~((माप_प्रकार) 0x7)))
#घोषणा VMCI_MAX_DATAGRAM_QUEUE_SIZE (VMCI_MAX_DG_SIZE * 2)

काष्ठा vmci_event_payload_qp अणु
	काष्ठा vmci_handle handle;  /* queue_pair handle. */
	u32 peer_id;		    /* Context id of attaching/detaching VM. */
	u32 _pad;
पूर्ण;

/* Flags क्रम VMCI queue_pair API. */
क्रमागत अणु
	/* Fail alloc अगर QP not created by peer. */
	VMCI_QPFLAG_ATTACH_ONLY = 1 << 0,

	/* Only allow attaches from local context. */
	VMCI_QPFLAG_LOCAL = 1 << 1,

	/* Host won't block when guest is quiesced. */
	VMCI_QPFLAG_NONBLOCK = 1 << 2,

	/* Pin data pages in ESX.  Used with NONBLOCK */
	VMCI_QPFLAG_PINNED = 1 << 3,

	/* Update the following flag when adding new flags. */
	VMCI_QP_ALL_FLAGS = (VMCI_QPFLAG_ATTACH_ONLY | VMCI_QPFLAG_LOCAL |
			     VMCI_QPFLAG_NONBLOCK | VMCI_QPFLAG_PINNED),

	/* Convenience flags */
	VMCI_QP_ASYMM = (VMCI_QPFLAG_NONBLOCK | VMCI_QPFLAG_PINNED),
	VMCI_QP_ASYMM_PEER = (VMCI_QPFLAG_ATTACH_ONLY | VMCI_QP_ASYMM),
पूर्ण;

/*
 * We allow at least 1024 more event datagrams from the hypervisor past the
 * normally allowed datagrams pending क्रम a given context.  We define this
 * limit on event datagrams from the hypervisor to guard against DoS attack
 * from a malicious VM which could repeatedly attach to and detach from a queue
 * pair, causing events to be queued at the destination VM.  However, the rate
 * at which such events can be generated is small since it requires a VM निकास
 * and handling of queue pair attach/detach call at the hypervisor.  Event
 * datagrams may be queued up at the destination VM अगर it has पूर्णांकerrupts
 * disabled or अगर it is not draining events क्रम some other reason.  1024
 * datagrams is a grossly conservative estimate of the समय क्रम which
 * पूर्णांकerrupts may be disabled in the destination VM, but at the same समय करोes
 * not exacerbate the memory pressure problem on the host by much (size of each
 * event datagram is small).
 */
#घोषणा VMCI_MAX_DATAGRAM_AND_EVENT_QUEUE_SIZE				\
	(VMCI_MAX_DATAGRAM_QUEUE_SIZE +					\
	 1024 * (माप(काष्ठा vmci_datagram) +				\
		 माप(काष्ठा vmci_event_data_max)))

/*
 * Struct used क्रम querying, via VMCI_RESOURCES_QUERY, the availability of
 * hypervisor resources.  Struct size is 16 bytes. All fields in काष्ठा are
 * aligned to their natural alignment.
 */
काष्ठा vmci_resource_query_hdr अणु
	काष्ठा vmci_datagram hdr;
	u32 num_resources;
	u32 _padding;
पूर्ण;

/*
 * Convenience काष्ठा क्रम negotiating vectors. Must match layout of
 * VMCIResourceQueryHdr minus the काष्ठा vmci_datagram header.
 */
काष्ठा vmci_resource_query_msg अणु
	u32 num_resources;
	u32 _padding;
	u32 resources[1];
पूर्ण;

/*
 * The maximum number of resources that can be queried using
 * VMCI_RESOURCE_QUERY is 31, as the result is encoded in the lower 31
 * bits of a positive वापस value. Negative values are reserved क्रम
 * errors.
 */
#घोषणा VMCI_RESOURCE_QUERY_MAX_NUM 31

/* Maximum size क्रम the VMCI_RESOURCE_QUERY request. */
#घोषणा VMCI_RESOURCE_QUERY_MAX_SIZE				\
	(माप(काष्ठा vmci_resource_query_hdr) +		\
	 माप(u32) * VMCI_RESOURCE_QUERY_MAX_NUM)

/*
 * Struct used क्रम setting the notअगरication biपंचांगap.  All fields in
 * काष्ठा are aligned to their natural alignment.
 */
काष्ठा vmci_notअगरy_bm_set_msg अणु
	काष्ठा vmci_datagram hdr;
	जोड़ अणु
		u32 biपंचांगap_ppn32;
		u64 biपंचांगap_ppn64;
	पूर्ण;
पूर्ण;

/*
 * Struct used क्रम linking a करोorbell handle with an index in the
 * notअगरy biपंचांगap. All fields in काष्ठा are aligned to their natural
 * alignment.
 */
काष्ठा vmci_करोorbell_link_msg अणु
	काष्ठा vmci_datagram hdr;
	काष्ठा vmci_handle handle;
	u64 notअगरy_idx;
पूर्ण;

/*
 * Struct used क्रम unlinking a करोorbell handle from an index in the
 * notअगरy biपंचांगap. All fields in काष्ठा are aligned to their natural
 * alignment.
 */
काष्ठा vmci_करोorbell_unlink_msg अणु
	काष्ठा vmci_datagram hdr;
	काष्ठा vmci_handle handle;
पूर्ण;

/*
 * Struct used क्रम generating a notअगरication on a करोorbell handle. All
 * fields in काष्ठा are aligned to their natural alignment.
 */
काष्ठा vmci_करोorbell_notअगरy_msg अणु
	काष्ठा vmci_datagram hdr;
	काष्ठा vmci_handle handle;
पूर्ण;

/*
 * This काष्ठा is used to contain data क्रम events.  Size of this काष्ठा is a
 * multiple of 8 bytes, and all fields are aligned to their natural alignment.
 */
काष्ठा vmci_event_data अणु
	u32 event;		/* 4 bytes. */
	u32 _pad;
	/* Event payload is put here. */
पूर्ण;

/*
 * Define the dअगरferent VMCI_EVENT payload data types here.  All काष्ठाs must
 * be a multiple of 8 bytes, and fields must be aligned to their natural
 * alignment.
 */
काष्ठा vmci_event_payld_ctx अणु
	u32 context_id;	/* 4 bytes. */
	u32 _pad;
पूर्ण;

काष्ठा vmci_event_payld_qp अणु
	काष्ठा vmci_handle handle;  /* queue_pair handle. */
	u32 peer_id;	    /* Context id of attaching/detaching VM. */
	u32 _pad;
पूर्ण;

/*
 * We define the following काष्ठा to get the size of the maximum event
 * data the hypervisor may send to the guest.  If adding a new event
 * payload type above, add it to the following काष्ठा too (inside the
 * जोड़).
 */
काष्ठा vmci_event_data_max अणु
	काष्ठा vmci_event_data event_data;
	जोड़ अणु
		काष्ठा vmci_event_payld_ctx context_payload;
		काष्ठा vmci_event_payld_qp qp_payload;
	पूर्ण ev_data_payload;
पूर्ण;

/*
 * Struct used क्रम VMCI_EVENT_SUBSCRIBE/UNSUBSCRIBE and
 * VMCI_EVENT_HANDLER messages.  Struct size is 32 bytes.  All fields
 * in काष्ठा are aligned to their natural alignment.
 */
काष्ठा vmci_event_msg अणु
	काष्ठा vmci_datagram hdr;

	/* Has event type and payload. */
	काष्ठा vmci_event_data event_data;

	/* Payload माला_लो put here. */
पूर्ण;

/* Event with context payload. */
काष्ठा vmci_event_ctx अणु
	काष्ठा vmci_event_msg msg;
	काष्ठा vmci_event_payld_ctx payload;
पूर्ण;

/* Event with QP payload. */
काष्ठा vmci_event_qp अणु
	काष्ठा vmci_event_msg msg;
	काष्ठा vmci_event_payld_qp payload;
पूर्ण;

/*
 * Structs used क्रम queue_pair alloc and detach messages.  We align fields of
 * these काष्ठाs to 64bit boundaries.
 */
काष्ठा vmci_qp_alloc_msg अणु
	काष्ठा vmci_datagram hdr;
	काष्ठा vmci_handle handle;
	u32 peer;
	u32 flags;
	u64 produce_size;
	u64 consume_size;
	u64 num_ppns;

	/* List of PPNs placed here. */
पूर्ण;

काष्ठा vmci_qp_detach_msg अणु
	काष्ठा vmci_datagram hdr;
	काष्ठा vmci_handle handle;
पूर्ण;

/* VMCI Doorbell API. */
#घोषणा VMCI_FLAG_DELAYED_CB BIT(0)

प्रकार व्योम (*vmci_callback) (व्योम *client_data);

/*
 * काष्ठा vmci_qp - A vmw_vmci queue pair handle.
 *
 * This काष्ठाure is used as a handle to a queue pair created by
 * VMCI.  It is पूर्णांकentionally left opaque to clients.
 */
काष्ठा vmci_qp;

/* Callback needed क्रम correctly रुकोing on events. */
प्रकार पूर्णांक (*vmci_datagram_recv_cb) (व्योम *client_data,
				      काष्ठा vmci_datagram *msg);

/* VMCI Event API. */
प्रकार व्योम (*vmci_event_cb) (u32 sub_id, स्थिर काष्ठा vmci_event_data *ed,
			       व्योम *client_data);

/*
 * We use the following अंतरभूत function to access the payload data
 * associated with an event data.
 */
अटल अंतरभूत स्थिर व्योम *
vmci_event_data_स्थिर_payload(स्थिर काष्ठा vmci_event_data *ev_data)
अणु
	वापस (स्थिर अक्षर *)ev_data + माप(*ev_data);
पूर्ण

अटल अंतरभूत व्योम *vmci_event_data_payload(काष्ठा vmci_event_data *ev_data)
अणु
	वापस (व्योम *)vmci_event_data_स्थिर_payload(ev_data);
पूर्ण

/*
 * Helper to पढ़ो a value from a head or tail poपूर्णांकer. For X86_32, the
 * poपूर्णांकer is treated as a 32bit value, since the poपूर्णांकer value
 * never exceeds a 32bit value in this हाल. Also, करोing an
 * atomic64_पढ़ो on X86_32 uniprocessor प्रणालीs may be implemented
 * as a non locked cmpxchg8b, that may end up overwriting updates करोne
 * by the VMCI device to the memory location. On 32bit SMP, the lock
 * prefix will be used, so correctness isn't an issue, but using a
 * 64bit operation still adds unnecessary overhead.
 */
अटल अंतरभूत u64 vmci_q_पढ़ो_poपूर्णांकer(u64 *var)
अणु
	वापस READ_ONCE(*(अचिन्हित दीर्घ *)var);
पूर्ण

/*
 * Helper to set the value of a head or tail poपूर्णांकer. For X86_32, the
 * poपूर्णांकer is treated as a 32bit value, since the poपूर्णांकer value
 * never exceeds a 32bit value in this हाल. On 32bit SMP, using a
 * locked cmpxchg8b adds unnecessary overhead.
 */
अटल अंतरभूत व्योम vmci_q_set_poपूर्णांकer(u64 *var, u64 new_val)
अणु
	/* XXX buggered on big-endian */
	WRITE_ONCE(*(अचिन्हित दीर्घ *)var, (अचिन्हित दीर्घ)new_val);
पूर्ण

/*
 * Helper to add a given offset to a head or tail poपूर्णांकer. Wraps the
 * value of the poपूर्णांकer around the max size of the queue.
 */
अटल अंतरभूत व्योम vmci_qp_add_poपूर्णांकer(u64 *var, माप_प्रकार add, u64 size)
अणु
	u64 new_val = vmci_q_पढ़ो_poपूर्णांकer(var);

	अगर (new_val >= size - add)
		new_val -= size;

	new_val += add;

	vmci_q_set_poपूर्णांकer(var, new_val);
पूर्ण

/*
 * Helper routine to get the Producer Tail from the supplied queue.
 */
अटल अंतरभूत u64
vmci_q_header_producer_tail(स्थिर काष्ठा vmci_queue_header *q_header)
अणु
	काष्ठा vmci_queue_header *qh = (काष्ठा vmci_queue_header *)q_header;
	वापस vmci_q_पढ़ो_poपूर्णांकer(&qh->producer_tail);
पूर्ण

/*
 * Helper routine to get the Consumer Head from the supplied queue.
 */
अटल अंतरभूत u64
vmci_q_header_consumer_head(स्थिर काष्ठा vmci_queue_header *q_header)
अणु
	काष्ठा vmci_queue_header *qh = (काष्ठा vmci_queue_header *)q_header;
	वापस vmci_q_पढ़ो_poपूर्णांकer(&qh->consumer_head);
पूर्ण

/*
 * Helper routine to increment the Producer Tail.  Fundamentally,
 * vmci_qp_add_poपूर्णांकer() is used to manipulate the tail itself.
 */
अटल अंतरभूत व्योम
vmci_q_header_add_producer_tail(काष्ठा vmci_queue_header *q_header,
				माप_प्रकार add,
				u64 queue_size)
अणु
	vmci_qp_add_poपूर्णांकer(&q_header->producer_tail, add, queue_size);
पूर्ण

/*
 * Helper routine to increment the Consumer Head.  Fundamentally,
 * vmci_qp_add_poपूर्णांकer() is used to manipulate the head itself.
 */
अटल अंतरभूत व्योम
vmci_q_header_add_consumer_head(काष्ठा vmci_queue_header *q_header,
				माप_प्रकार add,
				u64 queue_size)
अणु
	vmci_qp_add_poपूर्णांकer(&q_header->consumer_head, add, queue_size);
पूर्ण

/*
 * Helper routine क्रम getting the head and the tail poपूर्णांकer क्रम a queue.
 * Both the VMCIQueues are needed to get both the poपूर्णांकers क्रम one queue.
 */
अटल अंतरभूत व्योम
vmci_q_header_get_poपूर्णांकers(स्थिर काष्ठा vmci_queue_header *produce_q_header,
			   स्थिर काष्ठा vmci_queue_header *consume_q_header,
			   u64 *producer_tail,
			   u64 *consumer_head)
अणु
	अगर (producer_tail)
		*producer_tail = vmci_q_header_producer_tail(produce_q_header);

	अगर (consumer_head)
		*consumer_head = vmci_q_header_consumer_head(consume_q_header);
पूर्ण

अटल अंतरभूत व्योम vmci_q_header_init(काष्ठा vmci_queue_header *q_header,
				      स्थिर काष्ठा vmci_handle handle)
अणु
	q_header->handle = handle;
	q_header->producer_tail = 0;
	q_header->consumer_head = 0;
पूर्ण

/*
 * Finds available मुक्त space in a produce queue to enqueue more
 * data or reports an error अगर queue pair corruption is detected.
 */
अटल s64
vmci_q_header_मुक्त_space(स्थिर काष्ठा vmci_queue_header *produce_q_header,
			 स्थिर काष्ठा vmci_queue_header *consume_q_header,
			 स्थिर u64 produce_q_size)
अणु
	u64 tail;
	u64 head;
	u64 मुक्त_space;

	tail = vmci_q_header_producer_tail(produce_q_header);
	head = vmci_q_header_consumer_head(consume_q_header);

	अगर (tail >= produce_q_size || head >= produce_q_size)
		वापस VMCI_ERROR_INVALID_SIZE;

	/*
	 * Deduct 1 to aव्योम tail becoming equal to head which causes
	 * ambiguity. If head and tail are equal it means that the
	 * queue is empty.
	 */
	अगर (tail >= head)
		मुक्त_space = produce_q_size - (tail - head) - 1;
	अन्यथा
		मुक्त_space = head - tail - 1;

	वापस मुक्त_space;
पूर्ण

/*
 * vmci_q_header_मुक्त_space() करोes all the heavy lअगरting of
 * determing the number of मुक्त bytes in a Queue.  This routine,
 * then subtracts that size from the full size of the Queue so
 * the caller knows how many bytes are पढ़ोy to be dequeued.
 * Results:
 * On success, available data size in bytes (up to MAX_INT64).
 * On failure, appropriate error code.
 */
अटल अंतरभूत s64
vmci_q_header_buf_पढ़ोy(स्थिर काष्ठा vmci_queue_header *consume_q_header,
			स्थिर काष्ठा vmci_queue_header *produce_q_header,
			स्थिर u64 consume_q_size)
अणु
	s64 मुक्त_space;

	मुक्त_space = vmci_q_header_मुक्त_space(consume_q_header,
					      produce_q_header, consume_q_size);
	अगर (मुक्त_space < VMCI_SUCCESS)
		वापस मुक्त_space;

	वापस consume_q_size - मुक्त_space - 1;
पूर्ण


#पूर्ण_अगर /* _VMW_VMCI_DEF_H_ */
