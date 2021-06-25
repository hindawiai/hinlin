<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 2004-2008 Silicon Graphics, Inc. All rights reserved.
 */

/*
 * External Cross Partition (XP) काष्ठाures and defines.
 */

#अगर_अघोषित _DRIVERS_MISC_SGIXP_XP_H
#घोषणा _DRIVERS_MISC_SGIXP_XP_H

#समावेश <linux/mutex.h>

#अगर defined CONFIG_X86_UV || defined CONFIG_IA64_SGI_UV
#समावेश <यंत्र/uv/uv.h>
#पूर्ण_अगर

#अगर_घोषित USE_DBUG_ON
#घोषणा DBUG_ON(condition)	BUG_ON(condition)
#अन्यथा
#घोषणा DBUG_ON(condition)
#पूर्ण_अगर

/*
 * Define the maximum number of partitions the प्रणाली can possibly support.
 * It is based on the maximum number of hardware partitionable regions. The
 * term 'region' in this context refers to the minimum number of nodes that
 * can comprise an access protection grouping. The access protection is in
 * regards to memory, IPI and IOI.
 *
 * The maximum number of hardware partitionable regions is equal to the
 * maximum number of nodes in the entire प्रणाली भागided by the minimum number
 * of nodes that comprise an access protection grouping.
 */
#घोषणा XP_MAX_NPARTITIONS_SN2	64
#घोषणा XP_MAX_NPARTITIONS_UV	256

/*
 * XPC establishes channel connections between the local partition and any
 * other partition that is currently up. Over these channels, kernel-level
 * `users' can communicate with their counterparts on the other partitions.
 *
 * If the need क्रम additional channels arises, one can simply increase
 * XPC_MAX_NCHANNELS accordingly. If the day should come where that number
 * exceeds the असलolute MAXIMUM number of channels possible (eight), then one
 * will need to make changes to the XPC code to accommodate क्रम this.
 *
 * The असलolute maximum number of channels possible is limited to eight क्रम
 * perक्रमmance reasons on sn2 hardware. The पूर्णांकernal cross partition काष्ठाures
 * require sixteen bytes per channel, and eight allows all of this
 * पूर्णांकerface-shared info to fit in one 128-byte cacheline.
 */
#घोषणा XPC_MEM_CHANNEL		0	/* memory channel number */
#घोषणा	XPC_NET_CHANNEL		1	/* network channel number */

#घोषणा XPC_MAX_NCHANNELS	2	/* max #of channels allowed */

#अगर XPC_MAX_NCHANNELS > 8
#त्रुटि	XPC_MAX_NCHANNELS exceeds असलolute MAXIMUM possible.
#पूर्ण_अगर

/*
 * Define macro, XPC_MSG_SIZE(), is provided क्रम the user
 * that wants to fit as many msg entries as possible in a given memory size
 * (e.g. a memory page).
 */
#घोषणा XPC_MSG_MAX_SIZE	128
#घोषणा XPC_MSG_HDR_MAX_SIZE	16
#घोषणा XPC_MSG_PAYLOAD_MAX_SIZE (XPC_MSG_MAX_SIZE - XPC_MSG_HDR_MAX_SIZE)

#घोषणा XPC_MSG_SIZE(_payload_size) \
				ALIGN(XPC_MSG_HDR_MAX_SIZE + (_payload_size), \
				      is_uv_प्रणाली() ? 64 : 128)


/*
 * Define the वापस values and values passed to user's callout functions.
 * (It is important to add new value codes at the end just preceding
 * xpUnknownReason, which must have the highest numerical value.)
 */
क्रमागत xp_retval अणु
	xpSuccess = 0,

	xpNotConnected,		/*  1: channel is not connected */
	xpConnected,		/*  2: channel connected (खोलोed) */
	xpRETIRED1,		/*  3: (क्रमmerly xpDisconnected) */

	xpMsgReceived,		/*  4: message received */
	xpMsgDelivered,		/*  5: message delivered and acknowledged */

	xpRETIRED2,		/*  6: (क्रमmerly xpTransferFailed) */

	xpNoWait,		/*  7: operation would require रुको */
	xpRetry,		/*  8: retry operation */
	xpTimeout,		/*  9: समयout in xpc_allocate_msg_रुको() */
	xpInterrupted,		/* 10: पूर्णांकerrupted रुको */

	xpUnequalMsgSizes,	/* 11: message size disparity between sides */
	xpInvalidAddress,	/* 12: invalid address */

	xpNoMemory,		/* 13: no memory available क्रम XPC काष्ठाures */
	xpLackOfResources,	/* 14: insufficient resources क्रम operation */
	xpUnरेजिस्टरed,		/* 15: channel is not रेजिस्टरed */
	xpAlपढ़ोyRegistered,	/* 16: channel is alपढ़ोy रेजिस्टरed */

	xpPartitionDown,	/* 17: remote partition is करोwn */
	xpNotLoaded,		/* 18: XPC module is not loaded */
	xpUnloading,		/* 19: this side is unloading XPC module */

	xpBadMagic,		/* 20: XPC MAGIC string not found */

	xpReactivating,		/* 21: remote partition was reactivated */

	xpUnरेजिस्टरing,	/* 22: this side is unरेजिस्टरing channel */
	xpOtherUnरेजिस्टरing,	/* 23: other side is unरेजिस्टरing channel */

	xpCloneKThपढ़ो,		/* 24: cloning kernel thपढ़ो */
	xpCloneKThपढ़ोFailed,	/* 25: cloning kernel thपढ़ो failed */

	xpNoHeartbeat,		/* 26: remote partition has no heartbeat */

	xpPioReadError,		/* 27: PIO पढ़ो error */
	xpPhysAddrRegFailed,	/* 28: registration of phys addr range failed */

	xpRETIRED3,		/* 29: (क्रमmerly xpBteDirectoryError) */
	xpRETIRED4,		/* 30: (क्रमmerly xpBtePoisonError) */
	xpRETIRED5,		/* 31: (क्रमmerly xpBteWriteError) */
	xpRETIRED6,		/* 32: (क्रमmerly xpBteAccessError) */
	xpRETIRED7,		/* 33: (क्रमmerly xpBtePWriteError) */
	xpRETIRED8,		/* 34: (क्रमmerly xpBtePReadError) */
	xpRETIRED9,		/* 35: (क्रमmerly xpBteTimeOutError) */
	xpRETIRED10,		/* 36: (क्रमmerly xpBteXtalkError) */
	xpRETIRED11,		/* 37: (क्रमmerly xpBteNotAvailable) */
	xpRETIRED12,		/* 38: (क्रमmerly xpBteUnmappedError) */

	xpBadVersion,		/* 39: bad version number */
	xpVarsNotSet,		/* 40: the XPC variables are not set up */
	xpNoRsvdPageAddr,	/* 41: unable to get rsvd page's phys addr */
	xpInvalidPartid,	/* 42: invalid partition ID */
	xpLocalPartid,		/* 43: local partition ID */

	xpOtherGoingDown,	/* 44: other side going करोwn, reason unknown */
	xpSystemGoingDown,	/* 45: प्रणाली is going करोwn, reason unknown */
	xpSystemHalt,		/* 46: प्रणाली is being halted */
	xpSystemReboot,		/* 47: प्रणाली is being rebooted */
	xpSystemPoweroff,	/* 48: प्रणाली is being घातered off */

	xpDisconnecting,	/* 49: channel disconnecting (closing) */

	xpOpenCloseError,	/* 50: channel खोलो/बंद protocol error */

	xpDisconnected,		/* 51: channel disconnected (बंदd) */

	xpBteCopyError,		/* 52: bte_copy() वापसed error */
	xpSalError,		/* 53: sn SAL error */
	xpRsvdPageNotSet,	/* 54: the reserved page is not set up */
	xpPayloadTooBig,	/* 55: payload too large क्रम message slot */

	xpUnsupported,		/* 56: unsupported functionality or resource */
	xpNeedMoreInfo,		/* 57: more info is needed by SAL */

	xpGruCopyError,		/* 58: gru_copy_gru() वापसed error */
	xpGruSendMqError,	/* 59: gru send message queue related error */

	xpBadChannelNumber,	/* 60: invalid channel number */
	xpBadMsgType,		/* 61: invalid message type */
	xpBiosError,		/* 62: BIOS error */

	xpUnknownReason		/* 63: unknown reason - must be last in क्रमागत */
पूर्ण;

/*
 * Define the callout function type used by XPC to update the user on
 * connection activity and state changes via the user function रेजिस्टरed
 * by xpc_connect().
 *
 * Arguments:
 *
 *	reason - reason code.
 *	partid - partition ID associated with condition.
 *	ch_number - channel # associated with condition.
 *	data - poपूर्णांकer to optional data.
 *	key - poपूर्णांकer to optional user-defined value provided as the "key"
 *	      argument to xpc_connect().
 *
 * A reason code of xpConnected indicates that a connection has been
 * established to the specअगरied partition on the specअगरied channel. The data
 * argument indicates the max number of entries allowed in the message queue.
 *
 * A reason code of xpMsgReceived indicates that a XPC message arrived from
 * the specअगरied partition on the specअगरied channel. The data argument
 * specअगरies the address of the message's payload. The user must call
 * xpc_received() when finished with the payload.
 *
 * All other reason codes indicate failure. The data argmument is शून्य.
 * When a failure reason code is received, one can assume that the channel
 * is not connected.
 */
प्रकार व्योम (*xpc_channel_func) (क्रमागत xp_retval reason, लघु partid,
				  पूर्णांक ch_number, व्योम *data, व्योम *key);

/*
 * Define the callout function type used by XPC to notअगरy the user of
 * messages received and delivered via the user function रेजिस्टरed by
 * xpc_send_notअगरy().
 *
 * Arguments:
 *
 *	reason - reason code.
 *	partid - partition ID associated with condition.
 *	ch_number - channel # associated with condition.
 *	key - poपूर्णांकer to optional user-defined value provided as the "key"
 *	      argument to xpc_send_notअगरy().
 *
 * A reason code of xpMsgDelivered indicates that the message was delivered
 * to the पूर्णांकended recipient and that they have acknowledged its receipt by
 * calling xpc_received().
 *
 * All other reason codes indicate failure.
 *
 * NOTE: The user defined function must be callable by an पूर्णांकerrupt handler
 *       and thus cannot block.
 */
प्रकार व्योम (*xpc_notअगरy_func) (क्रमागत xp_retval reason, लघु partid,
				 पूर्णांक ch_number, व्योम *key);

/*
 * The following is a registration entry. There is a global array of these,
 * one per channel. It is used to record the connection registration made
 * by the users of XPC. As दीर्घ as a registration entry exists, क्रम any
 * partition that comes up, XPC will attempt to establish a connection on
 * that channel. Notअगरication that a connection has been made will occur via
 * the xpc_channel_func function.
 *
 * The 'func' field poपूर्णांकs to the function to call when aynchronous
 * notअगरication is required क्रम such events as: a connection established/lost,
 * or an incoming message received, or an error condition encountered. A
 * non-शून्य 'func' field indicates that there is an active registration क्रम
 * the channel.
 */
काष्ठा xpc_registration अणु
	काष्ठा mutex mutex;
	xpc_channel_func func;	/* function to call */
	व्योम *key;		/* poपूर्णांकer to user's key */
	u16 nentries;		/* #of msg entries in local msg queue */
	u16 entry_size;		/* message queue's message entry size */
	u32 asचिन्हित_limit;	/* limit on #of asचिन्हित kthपढ़ोs */
	u32 idle_limit;		/* limit on #of idle kthपढ़ोs */
पूर्ण ____cacheline_aligned;

#घोषणा XPC_CHANNEL_REGISTERED(_c)	(xpc_registrations[_c].func != शून्य)

/* the following are valid xpc_send() or xpc_send_notअगरy() flags */
#घोषणा XPC_WAIT	0	/* रुको flag */
#घोषणा XPC_NOWAIT	1	/* no रुको flag */

काष्ठा xpc_पूर्णांकerface अणु
	व्योम (*connect) (पूर्णांक);
	व्योम (*disconnect) (पूर्णांक);
	क्रमागत xp_retval (*send) (लघु, पूर्णांक, u32, व्योम *, u16);
	क्रमागत xp_retval (*send_notअगरy) (लघु, पूर्णांक, u32, व्योम *, u16,
					xpc_notअगरy_func, व्योम *);
	व्योम (*received) (लघु, पूर्णांक, व्योम *);
	क्रमागत xp_retval (*partid_to_nasids) (लघु, व्योम *);
पूर्ण;

बाह्य काष्ठा xpc_पूर्णांकerface xpc_पूर्णांकerface;

बाह्य व्योम xpc_set_पूर्णांकerface(व्योम (*)(पूर्णांक),
			      व्योम (*)(पूर्णांक),
			      क्रमागत xp_retval (*)(लघु, पूर्णांक, u32, व्योम *, u16),
			      क्रमागत xp_retval (*)(लघु, पूर्णांक, u32, व्योम *, u16,
						 xpc_notअगरy_func, व्योम *),
			      व्योम (*)(लघु, पूर्णांक, व्योम *),
			      क्रमागत xp_retval (*)(लघु, व्योम *));
बाह्य व्योम xpc_clear_पूर्णांकerface(व्योम);

बाह्य क्रमागत xp_retval xpc_connect(पूर्णांक, xpc_channel_func, व्योम *, u16,
				   u16, u32, u32);
बाह्य व्योम xpc_disconnect(पूर्णांक);

अटल अंतरभूत क्रमागत xp_retval
xpc_send(लघु partid, पूर्णांक ch_number, u32 flags, व्योम *payload,
	 u16 payload_size)
अणु
	अगर (!xpc_पूर्णांकerface.send)
		वापस xpNotLoaded;

	वापस xpc_पूर्णांकerface.send(partid, ch_number, flags, payload,
				  payload_size);
पूर्ण

अटल अंतरभूत क्रमागत xp_retval
xpc_send_notअगरy(लघु partid, पूर्णांक ch_number, u32 flags, व्योम *payload,
		u16 payload_size, xpc_notअगरy_func func, व्योम *key)
अणु
	अगर (!xpc_पूर्णांकerface.send_notअगरy)
		वापस xpNotLoaded;

	वापस xpc_पूर्णांकerface.send_notअगरy(partid, ch_number, flags, payload,
					 payload_size, func, key);
पूर्ण

अटल अंतरभूत व्योम
xpc_received(लघु partid, पूर्णांक ch_number, व्योम *payload)
अणु
	अगर (xpc_पूर्णांकerface.received)
		xpc_पूर्णांकerface.received(partid, ch_number, payload);
पूर्ण

अटल अंतरभूत क्रमागत xp_retval
xpc_partid_to_nasids(लघु partid, व्योम *nasids)
अणु
	अगर (!xpc_पूर्णांकerface.partid_to_nasids)
		वापस xpNotLoaded;

	वापस xpc_पूर्णांकerface.partid_to_nasids(partid, nasids);
पूर्ण

बाह्य लघु xp_max_npartitions;
बाह्य लघु xp_partition_id;
बाह्य u8 xp_region_size;

बाह्य अचिन्हित दीर्घ (*xp_pa) (व्योम *);
बाह्य अचिन्हित दीर्घ (*xp_socket_pa) (अचिन्हित दीर्घ);
बाह्य क्रमागत xp_retval (*xp_remote_स_नकल) (अचिन्हित दीर्घ, स्थिर अचिन्हित दीर्घ,
		       माप_प्रकार);
बाह्य पूर्णांक (*xp_cpu_to_nasid) (पूर्णांक);
बाह्य क्रमागत xp_retval (*xp_expand_memprotect) (अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य क्रमागत xp_retval (*xp_restrict_memprotect) (अचिन्हित दीर्घ, अचिन्हित दीर्घ);

बाह्य u64 xp_nofault_PIOR_target;
बाह्य पूर्णांक xp_nofault_PIOR(व्योम *);
बाह्य पूर्णांक xp_error_PIOR(व्योम);

बाह्य काष्ठा device *xp;
बाह्य क्रमागत xp_retval xp_init_uv(व्योम);
बाह्य व्योम xp_निकास_uv(व्योम);

#पूर्ण_अगर /* _DRIVERS_MISC_SGIXP_XP_H */
