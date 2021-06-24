<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  drbd.h
  Kernel module क्रम 2.6.x Kernels

  This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

  Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
  Copyright (C) 2001-2008, Philipp Reisner <philipp.reisner@linbit.com>.
  Copyright (C) 2001-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


*/
#अगर_अघोषित DRBD_H
#घोषणा DRBD_H
#समावेश <यंत्र/types.h>

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#अन्यथा
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <सीमा.स>

/* Although the Linux source code makes a dअगरference between
   generic endianness and the bitfields' endianness, there is no
   architecture as of Linux-2.6.24-rc4 where the bitfields' endianness
   करोes not match the generic endianness. */

#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा __LITTLE_ENDIAN_BITFIELD
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा __BIG_ENDIAN_BITFIELD
#अन्यथा
# error "sorry, weird endianness on this box"
#पूर्ण_अगर

#पूर्ण_अगर

बाह्य स्थिर अक्षर *drbd_buildtag(व्योम);
#घोषणा REL_VERSION "8.4.11"
#घोषणा API_VERSION 1
#घोषणा PRO_VERSION_MIN 86
#घोषणा PRO_VERSION_MAX 101


क्रमागत drbd_io_error_p अणु
	EP_PASS_ON, /* FIXME should the better be named "Ignore"? */
	EP_CALL_HELPER,
	EP_DETACH
पूर्ण;

क्रमागत drbd_fencing_p अणु
	FP_NOT_AVAIL = -1, /* Not a policy */
	FP_DONT_CARE = 0,
	FP_RESOURCE,
	FP_STONITH
पूर्ण;

क्रमागत drbd_disconnect_p अणु
	DP_RECONNECT,
	DP_DROP_NET_CONF,
	DP_FREEZE_IO
पूर्ण;

क्रमागत drbd_after_sb_p अणु
	ASB_DISCONNECT,
	ASB_DISCARD_YOUNGER_PRI,
	ASB_DISCARD_OLDER_PRI,
	ASB_DISCARD_ZERO_CHG,
	ASB_DISCARD_LEAST_CHG,
	ASB_DISCARD_LOCAL,
	ASB_DISCARD_REMOTE,
	ASB_CONSENSUS,
	ASB_DISCARD_SECONDARY,
	ASB_CALL_HELPER,
	ASB_VIOLENTLY
पूर्ण;

क्रमागत drbd_on_no_data अणु
	OND_IO_ERROR,
	OND_SUSPEND_IO
पूर्ण;

क्रमागत drbd_on_congestion अणु
	OC_BLOCK,
	OC_PULL_AHEAD,
	OC_DISCONNECT,
पूर्ण;

क्रमागत drbd_पढ़ो_balancing अणु
	RB_PREFER_LOCAL,
	RB_PREFER_REMOTE,
	RB_ROUND_ROBIN,
	RB_LEAST_PENDING,
	RB_CONGESTED_REMOTE,
	RB_32K_STRIPING,
	RB_64K_STRIPING,
	RB_128K_STRIPING,
	RB_256K_STRIPING,
	RB_512K_STRIPING,
	RB_1M_STRIPING,
पूर्ण;

/* KEEP the order, करो not delete or insert. Only append. */
क्रमागत drbd_ret_code अणु
	ERR_CODE_BASE		= 100,
	NO_ERROR		= 101,
	ERR_LOCAL_ADDR		= 102,
	ERR_PEER_ADDR		= 103,
	ERR_OPEN_DISK		= 104,
	ERR_OPEN_MD_DISK	= 105,
	ERR_DISK_NOT_BDEV	= 107,
	ERR_MD_NOT_BDEV		= 108,
	ERR_DISK_TOO_SMALL	= 111,
	ERR_MD_DISK_TOO_SMALL	= 112,
	ERR_BDCLAIM_DISK	= 114,
	ERR_BDCLAIM_MD_DISK	= 115,
	ERR_MD_IDX_INVALID	= 116,
	ERR_IO_MD_DISK		= 118,
	ERR_MD_INVALID          = 119,
	ERR_AUTH_ALG		= 120,
	ERR_AUTH_ALG_ND		= 121,
	ERR_NOMEM		= 122,
	ERR_DISCARD_IMPOSSIBLE	= 123,
	ERR_DISK_CONFIGURED	= 124,
	ERR_NET_CONFIGURED	= 125,
	ERR_MANDATORY_TAG	= 126,
	ERR_MINOR_INVALID	= 127,
	ERR_INTR		= 129, /* EINTR */
	ERR_RESIZE_RESYNC	= 130,
	ERR_NO_PRIMARY		= 131,
	ERR_RESYNC_AFTER	= 132,
	ERR_RESYNC_AFTER_CYCLE	= 133,
	ERR_PAUSE_IS_SET	= 134,
	ERR_PAUSE_IS_CLEAR	= 135,
	ERR_PACKET_NR		= 137,
	ERR_NO_DISK		= 138,
	ERR_NOT_PROTO_C		= 139,
	ERR_NOMEM_BITMAP	= 140,
	ERR_INTEGRITY_ALG	= 141, /* DRBD 8.2 only */
	ERR_INTEGRITY_ALG_ND	= 142, /* DRBD 8.2 only */
	ERR_CPU_MASK_PARSE	= 143, /* DRBD 8.2 only */
	ERR_CSUMS_ALG		= 144, /* DRBD 8.2 only */
	ERR_CSUMS_ALG_ND	= 145, /* DRBD 8.2 only */
	ERR_VERIFY_ALG		= 146, /* DRBD 8.2 only */
	ERR_VERIFY_ALG_ND	= 147, /* DRBD 8.2 only */
	ERR_CSUMS_RESYNC_RUNNING= 148, /* DRBD 8.2 only */
	ERR_VERIFY_RUNNING	= 149, /* DRBD 8.2 only */
	ERR_DATA_NOT_CURRENT	= 150,
	ERR_CONNECTED		= 151, /* DRBD 8.3 only */
	ERR_PERM		= 152,
	ERR_NEED_APV_93		= 153,
	ERR_STONITH_AND_PROT_A  = 154,
	ERR_CONG_NOT_PROTO_A	= 155,
	ERR_PIC_AFTER_DEP	= 156,
	ERR_PIC_PEER_DEP	= 157,
	ERR_RES_NOT_KNOWN	= 158,
	ERR_RES_IN_USE		= 159,
	ERR_MINOR_CONFIGURED    = 160,
	ERR_MINOR_OR_VOLUME_EXISTS = 161,
	ERR_INVALID_REQUEST	= 162,
	ERR_NEED_APV_100	= 163,
	ERR_NEED_ALLOW_TWO_PRI  = 164,
	ERR_MD_UNCLEAN          = 165,
	ERR_MD_LAYOUT_CONNECTED = 166,
	ERR_MD_LAYOUT_TOO_BIG   = 167,
	ERR_MD_LAYOUT_TOO_SMALL = 168,
	ERR_MD_LAYOUT_NO_FIT    = 169,
	ERR_IMPLICIT_SHRINK     = 170,
	/* insert new ones above this line */
	AFTER_LAST_ERR_CODE
पूर्ण;

#घोषणा DRBD_PROT_A   1
#घोषणा DRBD_PROT_B   2
#घोषणा DRBD_PROT_C   3

क्रमागत drbd_role अणु
	R_UNKNOWN = 0,
	R_PRIMARY = 1,     /* role */
	R_SECONDARY = 2,   /* role */
	R_MASK = 3,
पूर्ण;

/* The order of these स्थिरants is important.
 * The lower ones (<C_WF_REPORT_PARAMS) indicate
 * that there is no socket!
 * >=C_WF_REPORT_PARAMS ==> There is a socket
 */
क्रमागत drbd_conns अणु
	C_STANDALONE,
	C_DISCONNECTING,  /* Temporal state on the way to StandAlone. */
	C_UNCONNECTED,    /* >= C_UNCONNECTED -> inc_net() succeeds */

	/* These temporal states are all used on the way
	 * from >= C_CONNECTED to Unconnected.
	 * The 'disconnect reason' states
	 * I करो not allow to change between them. */
	C_TIMEOUT,
	C_BROKEN_PIPE,
	C_NETWORK_FAILURE,
	C_PROTOCOL_ERROR,
	C_TEAR_DOWN,

	C_WF_CONNECTION,
	C_WF_REPORT_PARAMS, /* we have a socket */
	C_CONNECTED,      /* we have पूर्णांकroduced each other */
	C_STARTING_SYNC_S,  /* starting full sync by admin request. */
	C_STARTING_SYNC_T,  /* starting full sync by admin request. */
	C_WF_BITMAP_S,
	C_WF_BITMAP_T,
	C_WF_SYNC_UUID,

	/* All SyncStates are tested with this comparison
	 * xx >= C_SYNC_SOURCE && xx <= C_PAUSED_SYNC_T */
	C_SYNC_SOURCE,
	C_SYNC_TARGET,
	C_VERIFY_S,
	C_VERIFY_T,
	C_PAUSED_SYNC_S,
	C_PAUSED_SYNC_T,

	C_AHEAD,
	C_BEHIND,

	C_MASK = 31
पूर्ण;

क्रमागत drbd_disk_state अणु
	D_DISKLESS,
	D_ATTACHING,      /* In the process of पढ़ोing the meta-data */
	D_FAILED,         /* Becomes D_DISKLESS as soon as we told it the peer */
			  /* when >= D_FAILED it is legal to access mdev->ldev */
	D_NEGOTIATING,    /* Late attaching state, we need to talk to the peer */
	D_INCONSISTENT,
	D_OUTDATED,
	D_UNKNOWN,       /* Only used क्रम the peer, never क्रम myself */
	D_CONSISTENT,     /* Might be D_OUTDATED, might be D_UP_TO_DATE ... */
	D_UP_TO_DATE,       /* Only this disk state allows applications' IO ! */
	D_MASK = 15
पूर्ण;

जोड़ drbd_state अणु
/* According to gcc's करोcs is the ...
 * The order of allocation of bit-fields within a unit (C90 6.5.2.1, C99 6.7.2.1).
 * Determined by ABI.
 * poपूर्णांकed out by Maxim Uvarov q<muvarov@ru.mvista.com>
 * even though we transmit as "cpu_to_be32(state)",
 * the offsets of the bitfields still need to be swapped
 * on dअगरferent endianness.
 */
	काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
		अचिन्हित role:2 ;   /* 3/4	 primary/secondary/unknown */
		अचिन्हित peer:2 ;   /* 3/4	 primary/secondary/unknown */
		अचिन्हित conn:5 ;   /* 17/32	 cstates */
		अचिन्हित disk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित pdsk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित susp:1 ;   /* 2/2	 IO suspended no/yes (by user) */
		अचिन्हित aftr_isp:1 ; /* isp .. imposed sync छोड़ो */
		अचिन्हित peer_isp:1 ;
		अचिन्हित user_isp:1 ;
		अचिन्हित susp_nod:1 ; /* IO suspended because no data */
		अचिन्हित susp_fen:1 ; /* IO suspended because fence peer handler runs*/
		अचिन्हित _pad:9;   /* 0	 unused */
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
		अचिन्हित _pad:9;
		अचिन्हित susp_fen:1 ;
		अचिन्हित susp_nod:1 ;
		अचिन्हित user_isp:1 ;
		अचिन्हित peer_isp:1 ;
		अचिन्हित aftr_isp:1 ; /* isp .. imposed sync छोड़ो */
		अचिन्हित susp:1 ;   /* 2/2	 IO suspended  no/yes */
		अचिन्हित pdsk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित disk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित conn:5 ;   /* 17/32	 cstates */
		अचिन्हित peer:2 ;   /* 3/4	 primary/secondary/unknown */
		अचिन्हित role:2 ;   /* 3/4	 primary/secondary/unknown */
#अन्यथा
# error "this endianness is not supported"
#पूर्ण_अगर
	पूर्ण;
	अचिन्हित पूर्णांक i;
पूर्ण;

क्रमागत drbd_state_rv अणु
	SS_CW_NO_NEED = 4,
	SS_CW_SUCCESS = 3,
	SS_NOTHING_TO_DO = 2,
	SS_SUCCESS = 1,
	SS_UNKNOWN_ERROR = 0, /* Used to sleep दीर्घer in _drbd_request_state */
	SS_TWO_PRIMARIES = -1,
	SS_NO_UP_TO_DATE_DISK = -2,
	SS_NO_LOCAL_DISK = -4,
	SS_NO_REMOTE_DISK = -5,
	SS_CONNECTED_OUTDATES = -6,
	SS_PRIMARY_NOP = -7,
	SS_RESYNC_RUNNING = -8,
	SS_ALREADY_STANDALONE = -9,
	SS_CW_FAILED_BY_PEER = -10,
	SS_IS_DISKLESS = -11,
	SS_DEVICE_IN_USE = -12,
	SS_NO_NET_CONFIG = -13,
	SS_NO_VERIFY_ALG = -14,       /* drbd-8.2 only */
	SS_NEED_CONNECTION = -15,    /* drbd-8.2 only */
	SS_LOWER_THAN_OUTDATED = -16,
	SS_NOT_SUPPORTED = -17,      /* drbd-8.2 only */
	SS_IN_TRANSIENT_STATE = -18,  /* Retry after the next state change */
	SS_CONCURRENT_ST_CHG = -19,   /* Concurrent cluster side state change! */
	SS_O_VOL_PEER_PRI = -20,
	SS_OUTDATE_WO_CONN = -21,
	SS_AFTER_LAST_ERROR = -22,    /* Keep this at bottom */
पूर्ण;

#घोषणा SHARED_SECRET_MAX 64

#घोषणा MDF_CONSISTENT		(1 << 0)
#घोषणा MDF_PRIMARY_IND		(1 << 1)
#घोषणा MDF_CONNECTED_IND	(1 << 2)
#घोषणा MDF_FULL_SYNC		(1 << 3)
#घोषणा MDF_WAS_UP_TO_DATE	(1 << 4)
#घोषणा MDF_PEER_OUT_DATED	(1 << 5)
#घोषणा MDF_CRASHED_PRIMARY	(1 << 6)
#घोषणा MDF_AL_CLEAN		(1 << 7)
#घोषणा MDF_AL_DISABLED		(1 << 8)

#घोषणा MAX_PEERS 32

क्रमागत drbd_uuid_index अणु
	UI_CURRENT,
	UI_BITMAP,
	UI_HISTORY_START,
	UI_HISTORY_END,
	UI_SIZE,      /* nl-packet: number of dirty bits */
	UI_FLAGS,     /* nl-packet: flags */
	UI_EXTENDED_SIZE   /* Everything. */
पूर्ण;

#घोषणा HISTORY_UUIDS MAX_PEERS

क्रमागत drbd_समयout_flag अणु
	UT_DEFAULT      = 0,
	UT_DEGRADED     = 1,
	UT_PEER_OUTDATED = 2,
पूर्ण;

क्रमागत drbd_notअगरication_type अणु
	NOTIFY_EXISTS,
	NOTIFY_CREATE,
	NOTIFY_CHANGE,
	NOTIFY_DESTROY,
	NOTIFY_CALL,
	NOTIFY_RESPONSE,

	NOTIFY_CONTINUES = 0x8000,
	NOTIFY_FLAGS = NOTIFY_CONTINUES,
पूर्ण;

क्रमागत drbd_peer_state अणु
	P_INCONSISTENT = 3,
	P_OUTDATED = 4,
	P_DOWN = 5,
	P_PRIMARY = 6,
	P_FENCING = 7,
पूर्ण;

#घोषणा UUID_JUST_CREATED ((__u64)4)

क्रमागत ग_लिखो_ordering_e अणु
	WO_NONE,
	WO_DRAIN_IO,
	WO_BDEV_FLUSH,
	WO_BIO_BARRIER
पूर्ण;

/* magic numbers used in meta data and network packets */
#घोषणा DRBD_MAGIC 0x83740267
#घोषणा DRBD_MAGIC_BIG 0x835a
#घोषणा DRBD_MAGIC_100 0x8620ec20

#घोषणा DRBD_MD_MAGIC_07   (DRBD_MAGIC+3)
#घोषणा DRBD_MD_MAGIC_08   (DRBD_MAGIC+4)
#घोषणा DRBD_MD_MAGIC_84_UNCLEAN	(DRBD_MAGIC+5)


/* how I came up with this magic?
 * base64 decode "actlog==" ;) */
#घोषणा DRBD_AL_MAGIC 0x69cb65a2

/* these are of type "int" */
#घोषणा DRBD_MD_INDEX_INTERNAL -1
#घोषणा DRBD_MD_INDEX_FLEX_EXT -2
#घोषणा DRBD_MD_INDEX_FLEX_INT -3

#घोषणा DRBD_CPU_MASK_SIZE 32

#पूर्ण_अगर
