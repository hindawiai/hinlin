<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2004-2009 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition Communication (XPC) काष्ठाures and macros.
 */

#अगर_अघोषित _DRIVERS_MISC_SGIXP_XPC_H
#घोषणा _DRIVERS_MISC_SGIXP_XPC_H

#समावेश <linux/रुको.h>
#समावेश <linux/completion.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश "xp.h"

/*
 * XPC Version numbers consist of a major and minor number. XPC can always
 * talk to versions with same major #, and never talk to versions with a
 * dअगरferent major #.
 */
#घोषणा _XPC_VERSION(_maj, _min)	(((_maj) << 4) | ((_min) & 0xf))
#घोषणा XPC_VERSION_MAJOR(_v)		((_v) >> 4)
#घोषणा XPC_VERSION_MINOR(_v)		((_v) & 0xf)

/* define frequency of the heartbeat and frequency how often it's checked */
#घोषणा XPC_HB_DEFAULT_INTERVAL		5	/* incr HB every x secs */
#घोषणा XPC_HB_CHECK_DEFAULT_INTERVAL	20	/* check HB every x secs */

/* define the process name of HB checker and the CPU it is pinned to */
#घोषणा XPC_HB_CHECK_THREAD_NAME	"xpc_hb"
#घोषणा XPC_HB_CHECK_CPU		0

/* define the process name of the discovery thपढ़ो */
#घोषणा XPC_DISCOVERY_THREAD_NAME	"xpc_discovery"

/*
 * the reserved page
 *
 *   SAL reserves one page of memory per partition क्रम XPC. Though a full page
 *   in length (16384 bytes), its starting address is not page aligned, but it
 *   is cacheline aligned. The reserved page consists of the following:
 *
 *   reserved page header
 *
 *     The first two 64-byte cachelines of the reserved page contain the
 *     header (काष्ठा xpc_rsvd_page). Beक्रमe SAL initialization has completed,
 *     SAL has set up the following fields of the reserved page header:
 *     SAL_signature, SAL_version, SAL_partid, and SAL_nasids_size. The
 *     other fields are set up by XPC. (xpc_rsvd_page poपूर्णांकs to the local
 *     partition's reserved page.)
 *
 *   part_nasids mask
 *   mach_nasids mask
 *
 *     SAL also sets up two biपंचांगaps (or masks), one that reflects the actual
 *     nasids in this partition (part_nasids), and the other that reflects
 *     the actual nasids in the entire machine (mach_nasids). We're only
 *     पूर्णांकerested in the even numbered nasids (which contain the processors
 *     and/or memory), so we only need half as many bits to represent the
 *     nasids. When mapping nasid to bit in a mask (or bit to nasid) be sure
 *     to either भागide or multiply by 2. The part_nasids mask is located
 *     starting at the first cacheline following the reserved page header. The
 *     mach_nasids mask follows right after the part_nasids mask. The size in
 *     bytes of each mask is reflected by the reserved page header field
 *     'SAL_nasids_size'. (Local partition's mask poपूर्णांकers are xpc_part_nasids
 *     and xpc_mach_nasids.)
 *
 *     Immediately following the mach_nasids mask are the XPC variables
 *     required by other partitions. First are those that are generic to all
 *     partitions (vars), followed on the next available cacheline by those
 *     which are partition specअगरic (vars part). These are setup by XPC.
 *
 * Note: Until 'ts_jiffies' is set non-zero, the partition XPC code has not been
 *       initialized.
 */
काष्ठा xpc_rsvd_page अणु
	u64 SAL_signature;	/* SAL: unique signature */
	u64 SAL_version;	/* SAL: version */
	लघु SAL_partid;	/* SAL: partition ID */
	लघु max_npartitions;	/* value of XPC_MAX_PARTITIONS */
	u8 version;
	u8 pad1[3];		/* align to next u64 in 1st 64-byte cacheline */
	अचिन्हित दीर्घ ts_jअगरfies; /* बारtamp when rsvd pg was setup by XPC */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ heartbeat_gpa; /* phys addr */
			अचिन्हित दीर्घ activate_gru_mq_desc_gpa; /* phys addr */
		पूर्ण uv;
	पूर्ण sn;
	u64 pad2[9];		/* align to last u64 in 2nd 64-byte cacheline */
	u64 SAL_nasids_size;	/* SAL: size of each nasid mask in bytes */
पूर्ण;

#घोषणा XPC_RP_VERSION _XPC_VERSION(3, 0) /* version 3.0 of the reserved page */

/* the reserved page sizes and offsets */

#घोषणा XPC_RP_HEADER_SIZE	L1_CACHE_ALIGN(माप(काष्ठा xpc_rsvd_page))

#घोषणा XPC_RP_PART_NASIDS(_rp) ((अचिन्हित दीर्घ *)((u8 *)(_rp) + \
				 XPC_RP_HEADER_SIZE))
#घोषणा XPC_RP_MACH_NASIDS(_rp) (XPC_RP_PART_NASIDS(_rp) + \
				 xpc_nasid_mask_nदीर्घs)


/*
 * The following काष्ठाure describes the partition's heartbeat info which
 * will be periodically पढ़ो by other partitions to determine whether this
 * XPC is still 'alive'.
 */
काष्ठा xpc_heartbeat_uv अणु
	अचिन्हित दीर्घ value;
	अचिन्हित दीर्घ offline;	/* अगर 0, heartbeat should be changing */
पूर्ण;

/*
 * Info pertinent to a GRU message queue using a watch list क्रम irq generation.
 */
काष्ठा xpc_gru_mq_uv अणु
	व्योम *address;		/* address of GRU message queue */
	अचिन्हित पूर्णांक order;	/* size of GRU message queue as a घातer of 2 */
	पूर्णांक irq;		/* irq उठाओd when message is received in mq */
	पूर्णांक mmr_blade;		/* blade where watchlist was allocated from */
	अचिन्हित दीर्घ mmr_offset; /* offset of irq mmr located on mmr_blade */
	अचिन्हित दीर्घ mmr_value; /* value of irq mmr located on mmr_blade */
	पूर्णांक watchlist_num;	/* number of watchlist allocatd by BIOS */
	व्योम *gru_mq_desc;	/* opaque काष्ठाure used by the GRU driver */
पूर्ण;

/*
 * The activate_mq is used to send/receive GRU messages that affect XPC's
 * partition active state and channel state. This is uv only.
 */
काष्ठा xpc_activate_mq_msghdr_uv अणु
	अचिन्हित पूर्णांक gru_msg_hdr; /* FOR GRU INTERNAL USE ONLY */
	लघु partid;		/* sender's partid */
	u8 act_state;		/* sender's act_state at समय msg sent */
	u8 type;		/* message's type */
	अचिन्हित दीर्घ rp_ts_jअगरfies; /* बारtamp of sender's rp setup by XPC */
पूर्ण;

/* activate_mq defined message types */
#घोषणा XPC_ACTIVATE_MQ_MSG_SYNC_ACT_STATE_UV		0

#घोषणा XPC_ACTIVATE_MQ_MSG_ACTIVATE_REQ_UV		1
#घोषणा XPC_ACTIVATE_MQ_MSG_DEACTIVATE_REQ_UV		2

#घोषणा XPC_ACTIVATE_MQ_MSG_CHCTL_CLOSEREQUEST_UV	3
#घोषणा XPC_ACTIVATE_MQ_MSG_CHCTL_CLOSEREPLY_UV		4
#घोषणा XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREQUEST_UV	5
#घोषणा XPC_ACTIVATE_MQ_MSG_CHCTL_OPENREPLY_UV		6
#घोषणा XPC_ACTIVATE_MQ_MSG_CHCTL_OPENCOMPLETE_UV	7

#घोषणा XPC_ACTIVATE_MQ_MSG_MARK_ENGAGED_UV		8
#घोषणा XPC_ACTIVATE_MQ_MSG_MARK_DISENGAGED_UV		9

काष्ठा xpc_activate_mq_msg_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
पूर्ण;

काष्ठा xpc_activate_mq_msg_activate_req_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	अचिन्हित दीर्घ rp_gpa;
	अचिन्हित दीर्घ heartbeat_gpa;
	अचिन्हित दीर्घ activate_gru_mq_desc_gpa;
पूर्ण;

काष्ठा xpc_activate_mq_msg_deactivate_req_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	क्रमागत xp_retval reason;
पूर्ण;

काष्ठा xpc_activate_mq_msg_chctl_बंदrequest_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	लघु ch_number;
	क्रमागत xp_retval reason;
पूर्ण;

काष्ठा xpc_activate_mq_msg_chctl_बंदreply_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	लघु ch_number;
पूर्ण;

काष्ठा xpc_activate_mq_msg_chctl_खोलोrequest_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	लघु ch_number;
	लघु entry_size;	/* size of notअगरy_mq's GRU messages */
	लघु local_nentries;	/* ??? Is this needed? What is? */
पूर्ण;

काष्ठा xpc_activate_mq_msg_chctl_खोलोreply_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	लघु ch_number;
	लघु remote_nentries;	/* ??? Is this needed? What is? */
	लघु local_nentries;	/* ??? Is this needed? What is? */
	अचिन्हित दीर्घ notअगरy_gru_mq_desc_gpa;
पूर्ण;

काष्ठा xpc_activate_mq_msg_chctl_खोलोcomplete_uv अणु
	काष्ठा xpc_activate_mq_msghdr_uv hdr;
	लघु ch_number;
पूर्ण;

/*
 * Functions रेजिस्टरed by add_समयr() or called by kernel_thपढ़ो() only
 * allow क्रम a single 64-bit argument. The following macros can be used to
 * pack and unpack two (32-bit, 16-bit or 8-bit) arguments पूर्णांकo or out from
 * the passed argument.
 */
#घोषणा XPC_PACK_ARGS(_arg1, _arg2) \
			((((u64)_arg1) & 0xffffffff) | \
			((((u64)_arg2) & 0xffffffff) << 32))

#घोषणा XPC_UNPACK_ARG1(_args)	(((u64)_args) & 0xffffffff)
#घोषणा XPC_UNPACK_ARG2(_args)	((((u64)_args) >> 32) & 0xffffffff)

/*
 * Define a काष्ठाure that contains arguments associated with खोलोing and
 * closing a channel.
 */
काष्ठा xpc_खोलोबंद_args अणु
	u16 reason;		/* reason why channel is closing */
	u16 entry_size;		/* माप each message entry */
	u16 remote_nentries;	/* #of message entries in remote msg queue */
	u16 local_nentries;	/* #of message entries in local msg queue */
	अचिन्हित दीर्घ local_msgqueue_pa; /* phys addr of local message queue */
पूर्ण;

#घोषणा XPC_OPENCLOSE_ARGS_SIZE \
	      L1_CACHE_ALIGN(माप(काष्ठा xpc_खोलोबंद_args) * \
	      XPC_MAX_NCHANNELS)


/*
 * Structures to define a fअगरo singly-linked list.
 */

काष्ठा xpc_fअगरo_entry_uv अणु
	काष्ठा xpc_fअगरo_entry_uv *next;
पूर्ण;

काष्ठा xpc_fअगरo_head_uv अणु
	काष्ठा xpc_fअगरo_entry_uv *first;
	काष्ठा xpc_fअगरo_entry_uv *last;
	spinlock_t lock;
	पूर्णांक n_entries;
पूर्ण;

/*
 * The क्रमmat of a uv XPC notअगरy_mq GRU message is as follows:
 *
 * A user-defined message resides in the payload area. The max size of the
 * payload is defined by the user via xpc_connect().
 *
 * The size of a message (payload and header) sent via the GRU must be either 1
 * or 2 GRU_CACHE_LINE_BYTES in length.
 */

काष्ठा xpc_notअगरy_mq_msghdr_uv अणु
	जोड़ अणु
		अचिन्हित पूर्णांक gru_msg_hdr;	/* FOR GRU INTERNAL USE ONLY */
		काष्ठा xpc_fअगरo_entry_uv next;	/* FOR XPC INTERNAL USE ONLY */
	पूर्ण u;
	लघु partid;		/* FOR XPC INTERNAL USE ONLY */
	u8 ch_number;		/* FOR XPC INTERNAL USE ONLY */
	u8 size;		/* FOR XPC INTERNAL USE ONLY */
	अचिन्हित पूर्णांक msg_slot_number;	/* FOR XPC INTERNAL USE ONLY */
पूर्ण;

काष्ठा xpc_notअगरy_mq_msg_uv अणु
	काष्ठा xpc_notअगरy_mq_msghdr_uv hdr;
	अचिन्हित दीर्घ payload;
पूर्ण;

/* काष्ठा xpc_notअगरy_sn2 type of notअगरication */

#घोषणा	XPC_N_CALL	0x01	/* notअगरy function provided by user */

/*
 * Define uv's version of the notअगरy entry. It additionally is used to allocate
 * a msg slot on the remote partition पूर्णांकo which is copied a sent message.
 */
काष्ठा xpc_send_msg_slot_uv अणु
	काष्ठा xpc_fअगरo_entry_uv next;
	अचिन्हित पूर्णांक msg_slot_number;
	xpc_notअगरy_func func;	/* user's notअगरy function */
	व्योम *key;		/* poपूर्णांकer to user's key */
पूर्ण;

/*
 * Define the काष्ठाure that manages all the stuff required by a channel. In
 * particular, they are used to manage the messages sent across the channel.
 *
 * This काष्ठाure is निजी to a partition, and is NOT shared across the
 * partition boundary.
 *
 * There is an array of these काष्ठाures क्रम each remote partition. It is
 * allocated at the समय a partition becomes active. The array contains one
 * of these काष्ठाures क्रम each potential channel connection to that partition.
 */

काष्ठा xpc_channel_uv अणु
	व्योम *cached_notअगरy_gru_mq_desc; /* remote partition's notify mq's */
					 /* gru mq descriptor */

	काष्ठा xpc_send_msg_slot_uv *send_msg_slots;
	व्योम *recv_msg_slots;	/* each slot will hold a xpc_notअगरy_mq_msg_uv */
				/* काष्ठाure plus the user's payload */

	काष्ठा xpc_fअगरo_head_uv msg_slot_मुक्त_list;
	काष्ठा xpc_fअगरo_head_uv recv_msg_list;	/* deliverable payloads */
पूर्ण;

काष्ठा xpc_channel अणु
	लघु partid;		/* ID of remote partition connected */
	spinlock_t lock;	/* lock क्रम updating this काष्ठाure */
	अचिन्हित पूर्णांक flags;	/* general flags */

	क्रमागत xp_retval reason;	/* reason why channel is disconnect'g */
	पूर्णांक reason_line;	/* line# disconnect initiated from */

	u16 number;		/* channel # */

	u16 entry_size;		/* माप each msg entry */
	u16 local_nentries;	/* #of msg entries in local msg queue */
	u16 remote_nentries;	/* #of msg entries in remote msg queue */

	atomic_t references;	/* #of बाह्यal references to queues */

	atomic_t n_on_msg_allocate_wq;	/* #on msg allocation रुको queue */
	रुको_queue_head_t msg_allocate_wq;	/* msg allocation रुको queue */

	u8 delayed_chctl_flags;	/* chctl flags received, but delayed */
				/* action until channel disconnected */

	atomic_t n_to_notअगरy;	/* #of msg senders to notअगरy */

	xpc_channel_func func;	/* user's channel function */
	व्योम *key;		/* poपूर्णांकer to user's key */

	काष्ठा completion wdisconnect_रुको;    /* रुको क्रम channel disconnect */

	/* kthपढ़ो management related fields */

	atomic_t kthपढ़ोs_asचिन्हित;	/* #of kthपढ़ोs asचिन्हित to channel */
	u32 kthपढ़ोs_asचिन्हित_limit;	/* limit on #of kthपढ़ोs asचिन्हित */
	atomic_t kthपढ़ोs_idle;	/* #of kthपढ़ोs idle रुकोing क्रम work */
	u32 kthपढ़ोs_idle_limit;	/* limit on #of kthपढ़ोs idle */
	atomic_t kthपढ़ोs_active;	/* #of kthपढ़ोs actively working */

	रुको_queue_head_t idle_wq;	/* idle kthपढ़ो रुको queue */

	जोड़ अणु
		काष्ठा xpc_channel_uv uv;
	पूर्ण sn;

पूर्ण ____cacheline_aligned;

/* काष्ठा xpc_channel flags */

#घोषणा	XPC_C_WASCONNECTED	0x00000001	/* channel was connected */

#घोषणा XPC_C_ROPENCOMPLETE	0x00000002    /* remote खोलो channel complete */
#घोषणा XPC_C_OPENCOMPLETE	0x00000004     /* local खोलो channel complete */
#घोषणा	XPC_C_ROPENREPLY	0x00000008	/* remote खोलो channel reply */
#घोषणा	XPC_C_OPENREPLY		0x00000010	/* local खोलो channel reply */
#घोषणा	XPC_C_ROPENREQUEST	0x00000020     /* remote खोलो channel request */
#घोषणा	XPC_C_OPENREQUEST	0x00000040	/* local खोलो channel request */

#घोषणा	XPC_C_SETUP		0x00000080 /* channel's msgqueues are alloc'd */
#घोषणा	XPC_C_CONNECTEDCALLOUT	0x00000100     /* connected callout initiated */
#घोषणा	XPC_C_CONNECTEDCALLOUT_MADE \
				0x00000200     /* connected callout completed */
#घोषणा	XPC_C_CONNECTED		0x00000400	/* local channel is connected */
#घोषणा	XPC_C_CONNECTING	0x00000800	/* channel is being connected */

#घोषणा	XPC_C_RCLOSEREPLY	0x00001000	/* remote बंद channel reply */
#घोषणा	XPC_C_CLOSEREPLY	0x00002000	/* local बंद channel reply */
#घोषणा	XPC_C_RCLOSEREQUEST	0x00004000    /* remote बंद channel request */
#घोषणा	XPC_C_CLOSEREQUEST	0x00008000     /* local बंद channel request */

#घोषणा	XPC_C_DISCONNECTED	0x00010000	/* channel is disconnected */
#घोषणा	XPC_C_DISCONNECTING	0x00020000   /* channel is being disconnected */
#घोषणा	XPC_C_DISCONNECTINGCALLOUT \
				0x00040000 /* disconnecting callout initiated */
#घोषणा	XPC_C_DISCONNECTINGCALLOUT_MADE \
				0x00080000 /* disconnecting callout completed */
#घोषणा	XPC_C_WDISCONNECT	0x00100000  /* रुकोing क्रम channel disconnect */

/*
 * The channel control flags (chctl) जोड़ consists of a 64-bit variable which
 * is भागided up पूर्णांकo eight bytes, ordered from right to left. Byte zero
 * pertains to channel 0, byte one to channel 1, and so on. Each channel's byte
 * can have one or more of the chctl flags set in it.
 */

जोड़ xpc_channel_ctl_flags अणु
	u64 all_flags;
	u8 flags[XPC_MAX_NCHANNELS];
पूर्ण;

/* chctl flags */
#घोषणा	XPC_CHCTL_CLOSEREQUEST	0x01
#घोषणा	XPC_CHCTL_CLOSEREPLY	0x02
#घोषणा	XPC_CHCTL_OPENREQUEST	0x04
#घोषणा	XPC_CHCTL_OPENREPLY	0x08
#घोषणा XPC_CHCTL_OPENCOMPLETE	0x10
#घोषणा	XPC_CHCTL_MSGREQUEST	0x20

#घोषणा XPC_OPENCLOSE_CHCTL_FLAGS \
			(XPC_CHCTL_CLOSEREQUEST | XPC_CHCTL_CLOSEREPLY | \
			 XPC_CHCTL_OPENREQUEST | XPC_CHCTL_OPENREPLY | \
			 XPC_CHCTL_OPENCOMPLETE)
#घोषणा XPC_MSG_CHCTL_FLAGS	XPC_CHCTL_MSGREQUEST

अटल अंतरभूत पूर्णांक
xpc_any_खोलोबंद_chctl_flags_set(जोड़ xpc_channel_ctl_flags *chctl)
अणु
	पूर्णांक ch_number;

	क्रम (ch_number = 0; ch_number < XPC_MAX_NCHANNELS; ch_number++) अणु
		अगर (chctl->flags[ch_number] & XPC_OPENCLOSE_CHCTL_FLAGS)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
xpc_any_msg_chctl_flags_set(जोड़ xpc_channel_ctl_flags *chctl)
अणु
	पूर्णांक ch_number;

	क्रम (ch_number = 0; ch_number < XPC_MAX_NCHANNELS; ch_number++) अणु
		अगर (chctl->flags[ch_number] & XPC_MSG_CHCTL_FLAGS)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा xpc_partition_uv अणु
	अचिन्हित दीर्घ heartbeat_gpa; /* phys addr of partition's heartbeat */
	काष्ठा xpc_heartbeat_uv cached_heartbeat; /* cached copy of */
						  /* partition's heartbeat */
	अचिन्हित दीर्घ activate_gru_mq_desc_gpa;	/* phys addr of parititon's */
						/* activate mq's gru mq */
						/* descriptor */
	व्योम *cached_activate_gru_mq_desc; /* cached copy of partition's */
					   /* activate mq's gru mq descriptor */
	काष्ठा mutex cached_activate_gru_mq_desc_mutex;
	spinlock_t flags_lock;	/* protect updating of flags */
	अचिन्हित पूर्णांक flags;	/* general flags */
	u8 remote_act_state;	/* remote partition's act_state */
	u8 act_state_req;	/* act_state request from remote partition */
	क्रमागत xp_retval reason;	/* reason क्रम deactivate act_state request */
पूर्ण;

/* काष्ठा xpc_partition_uv flags */

#घोषणा XPC_P_CACHED_ACTIVATE_GRU_MQ_DESC_UV	0x00000001
#घोषणा XPC_P_ENGAGED_UV			0x00000002

/* काष्ठा xpc_partition_uv act_state change requests */

#घोषणा XPC_P_ASR_ACTIVATE_UV		0x01
#घोषणा XPC_P_ASR_REACTIVATE_UV		0x02
#घोषणा XPC_P_ASR_DEACTIVATE_UV		0x03

काष्ठा xpc_partition अणु

	/* XPC HB infraकाष्ठाure */

	u8 remote_rp_version;	/* version# of partition's rsvd pg */
	अचिन्हित दीर्घ remote_rp_ts_jअगरfies; /* बारtamp when rsvd pg setup */
	अचिन्हित दीर्घ remote_rp_pa;	/* phys addr of partition's rsvd pg */
	u64 last_heartbeat;	/* HB at last पढ़ो */
	u32 activate_IRQ_rcvd;	/* IRQs since activation */
	spinlock_t act_lock;	/* protect updating of act_state */
	u8 act_state;		/* from XPC HB viewpoपूर्णांक */
	क्रमागत xp_retval reason;	/* reason partition is deactivating */
	पूर्णांक reason_line;	/* line# deactivation initiated from */

	अचिन्हित दीर्घ disengage_समयout;	/* समयout in jअगरfies */
	काष्ठा समयr_list disengage_समयr;

	/* XPC infraकाष्ठाure referencing and tearकरोwn control */

	u8 setup_state;		/* infraकाष्ठाure setup state */
	रुको_queue_head_t tearकरोwn_wq;	/* kthपढ़ो रुकोing to tearकरोwn infra */
	atomic_t references;	/* #of references to infraकाष्ठाure */

	u8 nchannels;		/* #of defined channels supported */
	atomic_t nchannels_active;  /* #of channels that are not DISCONNECTED */
	atomic_t nchannels_engaged;  /* #of channels engaged with remote part */
	काष्ठा xpc_channel *channels;	/* array of channel काष्ठाures */

	/* fields used क्रम managing channel avialability and activity */

	जोड़ xpc_channel_ctl_flags chctl; /* chctl flags yet to be processed */
	spinlock_t chctl_lock;	/* chctl flags lock */

	व्योम *remote_खोलोबंद_args_base;  /* base address of kदो_स्मृति'd space */
	काष्ठा xpc_खोलोबंद_args *remote_खोलोबंद_args; /* copy of remote's */
							  /* args */

	/* channel manager related fields */

	atomic_t channel_mgr_requests;	/* #of requests to activate chan mgr */
	रुको_queue_head_t channel_mgr_wq;	/* channel mgr's रुको queue */

	जोड़ अणु
		काष्ठा xpc_partition_uv uv;
	पूर्ण sn;

पूर्ण ____cacheline_aligned;

काष्ठा xpc_arch_operations अणु
	पूर्णांक (*setup_partitions) (व्योम);
	व्योम (*tearकरोwn_partitions) (व्योम);
	व्योम (*process_activate_IRQ_rcvd) (व्योम);
	क्रमागत xp_retval (*get_partition_rsvd_page_pa)
		(व्योम *, u64 *, अचिन्हित दीर्घ *, माप_प्रकार *);
	पूर्णांक (*setup_rsvd_page) (काष्ठा xpc_rsvd_page *);

	व्योम (*allow_hb) (लघु);
	व्योम (*disallow_hb) (लघु);
	व्योम (*disallow_all_hbs) (व्योम);
	व्योम (*increment_heartbeat) (व्योम);
	व्योम (*offline_heartbeat) (व्योम);
	व्योम (*online_heartbeat) (व्योम);
	व्योम (*heartbeat_init) (व्योम);
	व्योम (*heartbeat_निकास) (व्योम);
	क्रमागत xp_retval (*get_remote_heartbeat) (काष्ठा xpc_partition *);

	व्योम (*request_partition_activation) (काष्ठा xpc_rsvd_page *,
						 अचिन्हित दीर्घ, पूर्णांक);
	व्योम (*request_partition_reactivation) (काष्ठा xpc_partition *);
	व्योम (*request_partition_deactivation) (काष्ठा xpc_partition *);
	व्योम (*cancel_partition_deactivation_request) (काष्ठा xpc_partition *);
	क्रमागत xp_retval (*setup_ch_काष्ठाures) (काष्ठा xpc_partition *);
	व्योम (*tearकरोwn_ch_काष्ठाures) (काष्ठा xpc_partition *);

	क्रमागत xp_retval (*make_first_contact) (काष्ठा xpc_partition *);

	u64 (*get_chctl_all_flags) (काष्ठा xpc_partition *);
	व्योम (*send_chctl_बंदrequest) (काष्ठा xpc_channel *, अचिन्हित दीर्घ *);
	व्योम (*send_chctl_बंदreply) (काष्ठा xpc_channel *, अचिन्हित दीर्घ *);
	व्योम (*send_chctl_खोलोrequest) (काष्ठा xpc_channel *, अचिन्हित दीर्घ *);
	व्योम (*send_chctl_खोलोreply) (काष्ठा xpc_channel *, अचिन्हित दीर्घ *);
	व्योम (*send_chctl_खोलोcomplete) (काष्ठा xpc_channel *, अचिन्हित दीर्घ *);
	व्योम (*process_msg_chctl_flags) (काष्ठा xpc_partition *, पूर्णांक);

	क्रमागत xp_retval (*save_remote_msgqueue_pa) (काष्ठा xpc_channel *,
						      अचिन्हित दीर्घ);

	क्रमागत xp_retval (*setup_msg_काष्ठाures) (काष्ठा xpc_channel *);
	व्योम (*tearकरोwn_msg_काष्ठाures) (काष्ठा xpc_channel *);

	व्योम (*indicate_partition_engaged) (काष्ठा xpc_partition *);
	व्योम (*indicate_partition_disengaged) (काष्ठा xpc_partition *);
	व्योम (*assume_partition_disengaged) (लघु);
	पूर्णांक (*partition_engaged) (लघु);
	पूर्णांक (*any_partition_engaged) (व्योम);

	पूर्णांक (*n_of_deliverable_payloads) (काष्ठा xpc_channel *);
	क्रमागत xp_retval (*send_payload) (काष्ठा xpc_channel *, u32, व्योम *,
					   u16, u8, xpc_notअगरy_func, व्योम *);
	व्योम *(*get_deliverable_payload) (काष्ठा xpc_channel *);
	व्योम (*received_payload) (काष्ठा xpc_channel *, व्योम *);
	व्योम (*notअगरy_senders_of_disconnect) (काष्ठा xpc_channel *);
पूर्ण;

/* काष्ठा xpc_partition act_state values (क्रम XPC HB) */

#घोषणा	XPC_P_AS_INACTIVE	0x00	/* partition is not active */
#घोषणा XPC_P_AS_ACTIVATION_REQ	0x01	/* created thपढ़ो to activate */
#घोषणा XPC_P_AS_ACTIVATING	0x02	/* activation thपढ़ो started */
#घोषणा XPC_P_AS_ACTIVE		0x03	/* xpc_partition_up() was called */
#घोषणा XPC_P_AS_DEACTIVATING	0x04	/* partition deactivation initiated */

#घोषणा XPC_DEACTIVATE_PARTITION(_p, _reason) \
			xpc_deactivate_partition(__LINE__, (_p), (_reason))

/* काष्ठा xpc_partition setup_state values */

#घोषणा XPC_P_SS_UNSET		0x00	/* infraकाष्ठाure was never setup */
#घोषणा XPC_P_SS_SETUP		0x01	/* infraकाष्ठाure is setup */
#घोषणा XPC_P_SS_WTEARDOWN	0x02	/* रुकोing to tearकरोwn infraकाष्ठाure */
#घोषणा XPC_P_SS_TORNDOWN	0x03	/* infraकाष्ठाure is tornकरोwn */

/* number of seconds to रुको क्रम other partitions to disengage */
#घोषणा XPC_DISENGAGE_DEFAULT_TIMELIMIT		90

/* पूर्णांकerval in seconds to prपूर्णांक 'waiting deactivation' messages */
#घोषणा XPC_DEACTIVATE_PRINTMSG_INTERVAL	10

#घोषणा XPC_PARTID(_p)	((लघु)((_p) - &xpc_partitions[0]))

/* found in xp_मुख्य.c */
बाह्य काष्ठा xpc_registration xpc_registrations[];

/* found in xpc_मुख्य.c */
बाह्य काष्ठा device *xpc_part;
बाह्य काष्ठा device *xpc_chan;
बाह्य काष्ठा xpc_arch_operations xpc_arch_ops;
बाह्य पूर्णांक xpc_disengage_समयlimit;
बाह्य पूर्णांक xpc_disengage_समयकरोut;
बाह्य पूर्णांक xpc_activate_IRQ_rcvd;
बाह्य spinlock_t xpc_activate_IRQ_rcvd_lock;
बाह्य रुको_queue_head_t xpc_activate_IRQ_wq;
बाह्य व्योम *xpc_kzalloc_cacheline_aligned(माप_प्रकार, gfp_t, व्योम **);
बाह्य व्योम xpc_activate_partition(काष्ठा xpc_partition *);
बाह्य व्योम xpc_activate_kthपढ़ोs(काष्ठा xpc_channel *, पूर्णांक);
बाह्य व्योम xpc_create_kthपढ़ोs(काष्ठा xpc_channel *, पूर्णांक, पूर्णांक);
बाह्य व्योम xpc_disconnect_रुको(पूर्णांक);

/* found in xpc_uv.c */
बाह्य पूर्णांक xpc_init_uv(व्योम);
बाह्य व्योम xpc_निकास_uv(व्योम);

/* found in xpc_partition.c */
बाह्य पूर्णांक xpc_निकासing;
बाह्य पूर्णांक xpc_nasid_mask_nदीर्घs;
बाह्य काष्ठा xpc_rsvd_page *xpc_rsvd_page;
बाह्य अचिन्हित दीर्घ *xpc_mach_nasids;
बाह्य काष्ठा xpc_partition *xpc_partitions;
बाह्य व्योम *xpc_kदो_स्मृति_cacheline_aligned(माप_प्रकार, gfp_t, व्योम **);
बाह्य पूर्णांक xpc_setup_rsvd_page(व्योम);
बाह्य व्योम xpc_tearकरोwn_rsvd_page(व्योम);
बाह्य पूर्णांक xpc_identअगरy_activate_IRQ_sender(व्योम);
बाह्य पूर्णांक xpc_partition_disengaged(काष्ठा xpc_partition *);
बाह्य पूर्णांक xpc_partition_disengaged_from_समयr(काष्ठा xpc_partition *part);
बाह्य क्रमागत xp_retval xpc_mark_partition_active(काष्ठा xpc_partition *);
बाह्य व्योम xpc_mark_partition_inactive(काष्ठा xpc_partition *);
बाह्य व्योम xpc_discovery(व्योम);
बाह्य क्रमागत xp_retval xpc_get_remote_rp(पूर्णांक, अचिन्हित दीर्घ *,
					काष्ठा xpc_rsvd_page *,
					अचिन्हित दीर्घ *);
बाह्य व्योम xpc_deactivate_partition(स्थिर पूर्णांक, काष्ठा xpc_partition *,
				     क्रमागत xp_retval);
बाह्य क्रमागत xp_retval xpc_initiate_partid_to_nasids(लघु, व्योम *);

/* found in xpc_channel.c */
बाह्य व्योम xpc_initiate_connect(पूर्णांक);
बाह्य व्योम xpc_initiate_disconnect(पूर्णांक);
बाह्य क्रमागत xp_retval xpc_allocate_msg_रुको(काष्ठा xpc_channel *);
बाह्य क्रमागत xp_retval xpc_initiate_send(लघु, पूर्णांक, u32, व्योम *, u16);
बाह्य क्रमागत xp_retval xpc_initiate_send_notअगरy(लघु, पूर्णांक, u32, व्योम *, u16,
					       xpc_notअगरy_func, व्योम *);
बाह्य व्योम xpc_initiate_received(लघु, पूर्णांक, व्योम *);
बाह्य व्योम xpc_process_sent_chctl_flags(काष्ठा xpc_partition *);
बाह्य व्योम xpc_connected_callout(काष्ठा xpc_channel *);
बाह्य व्योम xpc_deliver_payload(काष्ठा xpc_channel *);
बाह्य व्योम xpc_disconnect_channel(स्थिर पूर्णांक, काष्ठा xpc_channel *,
				   क्रमागत xp_retval, अचिन्हित दीर्घ *);
बाह्य व्योम xpc_disconnect_callout(काष्ठा xpc_channel *, क्रमागत xp_retval);
बाह्य व्योम xpc_partition_going_करोwn(काष्ठा xpc_partition *, क्रमागत xp_retval);

अटल अंतरभूत व्योम
xpc_wakeup_channel_mgr(काष्ठा xpc_partition *part)
अणु
	अगर (atomic_inc_वापस(&part->channel_mgr_requests) == 1)
		wake_up(&part->channel_mgr_wq);
पूर्ण

/*
 * These next two अंतरभूतs are used to keep us from tearing करोwn a channel's
 * msg queues जबतक a thपढ़ो may be referencing them.
 */
अटल अंतरभूत व्योम
xpc_msgqueue_ref(काष्ठा xpc_channel *ch)
अणु
	atomic_inc(&ch->references);
पूर्ण

अटल अंतरभूत व्योम
xpc_msgqueue_deref(काष्ठा xpc_channel *ch)
अणु
	s32 refs = atomic_dec_वापस(&ch->references);

	DBUG_ON(refs < 0);
	अगर (refs == 0)
		xpc_wakeup_channel_mgr(&xpc_partitions[ch->partid]);
पूर्ण

#घोषणा XPC_DISCONNECT_CHANNEL(_ch, _reason, _irqflgs) \
		xpc_disconnect_channel(__LINE__, _ch, _reason, _irqflgs)

/*
 * These two अंतरभूतs are used to keep us from tearing करोwn a partition's
 * setup infraकाष्ठाure जबतक a thपढ़ो may be referencing it.
 */
अटल अंतरभूत व्योम
xpc_part_deref(काष्ठा xpc_partition *part)
अणु
	s32 refs = atomic_dec_वापस(&part->references);

	DBUG_ON(refs < 0);
	अगर (refs == 0 && part->setup_state == XPC_P_SS_WTEARDOWN)
		wake_up(&part->tearकरोwn_wq);
पूर्ण

अटल अंतरभूत पूर्णांक
xpc_part_ref(काष्ठा xpc_partition *part)
अणु
	पूर्णांक setup;

	atomic_inc(&part->references);
	setup = (part->setup_state == XPC_P_SS_SETUP);
	अगर (!setup)
		xpc_part_deref(part);

	वापस setup;
पूर्ण

/*
 * The following macro is to be used क्रम the setting of the reason and
 * reason_line fields in both the काष्ठा xpc_channel and काष्ठा xpc_partition
 * काष्ठाures.
 */
#घोषणा XPC_SET_REASON(_p, _reason, _line) \
	अणु \
		(_p)->reason = _reason; \
		(_p)->reason_line = _line; \
	पूर्ण

#पूर्ण_अगर /* _DRIVERS_MISC_SGIXP_XPC_H */
