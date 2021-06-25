<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2002 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * This header represents the काष्ठाures and स्थिरants needed to support
 * the SCTP Extension to the Sockets API.
 *
 * This SCTP implementation is मुक्त software;
 * you can redistribute it and/or modअगरy it under the terms of
 * the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This SCTP implementation is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 *                 ************************
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with GNU CC; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Or submit a bug report through the following website:
 *    http://www.sf.net/projects/lksctp
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll    <piggy@acm.org>
 *    R. Stewart               <अक्रमall@sctp.chicago.il.us>
 *    K. Morneau               <kmorneau@cisco.com>
 *    Q. Xie                   <qxie1@email.mot.com>
 *    Karl Knutson             <karl@athena.chicago.il.us>
 *    Jon Grimm                <jgrimm@us.ibm.com>
 *    Daisy Chang              <daisyc@us.ibm.com>
 *    Ryan Layer               <rmlayer@us.ibm.com>
 *    Ardelle Fan              <ardelle.fan@पूर्णांकel.com>
 *    Sridhar Samudrala        <sri@us.ibm.com>
 *    Inaky Perez-Gonzalez     <inaky.gonzalez@पूर्णांकel.com>
 *    Vlad Yasevich            <vladislav.yasevich@hp.com>
 *
 * Any bugs reported given to us we will try to fix... any fixes shared will
 * be incorporated पूर्णांकo the next SCTP release.
 */

#अगर_अघोषित _UAPI_SCTP_H
#घोषणा _UAPI_SCTP_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>

प्रकार __s32 sctp_assoc_t;

#घोषणा SCTP_FUTURE_ASSOC	0
#घोषणा SCTP_CURRENT_ASSOC	1
#घोषणा SCTP_ALL_ASSOC		2

/* The following symbols come from the Sockets API Extensions क्रम
 * SCTP <draft-ietf-tsvwg-sctpsocket-07.txt>.
 */
#घोषणा SCTP_RTOINFO	0
#घोषणा SCTP_ASSOCINFO  1
#घोषणा SCTP_INITMSG	2
#घोषणा SCTP_NODELAY	3		/* Get/set nodelay option. */
#घोषणा SCTP_AUTOCLOSE	4
#घोषणा SCTP_SET_PEER_PRIMARY_ADDR 5
#घोषणा SCTP_PRIMARY_ADDR	6
#घोषणा SCTP_ADAPTATION_LAYER	7
#घोषणा SCTP_DISABLE_FRAGMENTS	8
#घोषणा SCTP_PEER_ADDR_PARAMS	9
#घोषणा SCTP_DEFAULT_SEND_PARAM	10
#घोषणा SCTP_EVENTS	11
#घोषणा SCTP_I_WANT_MAPPED_V4_ADDR 12	/* Turn on/off mapped v4 addresses  */
#घोषणा SCTP_MAXSEG	13		/* Get/set maximum fragment. */
#घोषणा SCTP_STATUS	14
#घोषणा SCTP_GET_PEER_ADDR_INFO	15
#घोषणा SCTP_DELAYED_ACK_TIME	16
#घोषणा SCTP_DELAYED_ACK SCTP_DELAYED_ACK_TIME
#घोषणा SCTP_DELAYED_SACK SCTP_DELAYED_ACK_TIME
#घोषणा SCTP_CONTEXT	17
#घोषणा SCTP_FRAGMENT_INTERLEAVE	18
#घोषणा SCTP_PARTIAL_DELIVERY_POINT	19 /* Set/Get partial delivery poपूर्णांक */
#घोषणा SCTP_MAX_BURST	20		/* Set/Get max burst */
#घोषणा SCTP_AUTH_CHUNK	21	/* Set only: add a chunk type to authenticate */
#घोषणा SCTP_HMAC_IDENT	22
#घोषणा SCTP_AUTH_KEY	23
#घोषणा SCTP_AUTH_ACTIVE_KEY	24
#घोषणा SCTP_AUTH_DELETE_KEY	25
#घोषणा SCTP_PEER_AUTH_CHUNKS	26	/* Read only */
#घोषणा SCTP_LOCAL_AUTH_CHUNKS	27	/* Read only */
#घोषणा SCTP_GET_ASSOC_NUMBER	28	/* Read only */
#घोषणा SCTP_GET_ASSOC_ID_LIST	29	/* Read only */
#घोषणा SCTP_AUTO_ASCONF       30
#घोषणा SCTP_PEER_ADDR_THLDS	31
#घोषणा SCTP_RECVRCVINFO	32
#घोषणा SCTP_RECVNXTINFO	33
#घोषणा SCTP_DEFAULT_SNDINFO	34
#घोषणा SCTP_AUTH_DEACTIVATE_KEY	35
#घोषणा SCTP_REUSE_PORT		36
#घोषणा SCTP_PEER_ADDR_THLDS_V2	37

/* Internal Socket Options. Some of the sctp library functions are
 * implemented using these socket options.
 */
#घोषणा SCTP_SOCKOPT_BINDX_ADD	100	/* BINDX requests क्रम adding addrs */
#घोषणा SCTP_SOCKOPT_BINDX_REM	101	/* BINDX requests क्रम removing addrs. */
#घोषणा SCTP_SOCKOPT_PEELOFF	102	/* peel off association. */
/* Options 104-106 are deprecated and हटाओd. Do not use this space */
#घोषणा SCTP_SOCKOPT_CONNECTX_OLD	107	/* CONNECTX old requests. */
#घोषणा SCTP_GET_PEER_ADDRS	108		/* Get all peer address. */
#घोषणा SCTP_GET_LOCAL_ADDRS	109		/* Get all local address. */
#घोषणा SCTP_SOCKOPT_CONNECTX	110		/* CONNECTX requests. */
#घोषणा SCTP_SOCKOPT_CONNECTX3	111	/* CONNECTX requests (updated) */
#घोषणा SCTP_GET_ASSOC_STATS	112	/* Read only */
#घोषणा SCTP_PR_SUPPORTED	113
#घोषणा SCTP_DEFAULT_PRINFO	114
#घोषणा SCTP_PR_ASSOC_STATUS	115
#घोषणा SCTP_PR_STREAM_STATUS	116
#घोषणा SCTP_RECONFIG_SUPPORTED	117
#घोषणा SCTP_ENABLE_STREAM_RESET	118
#घोषणा SCTP_RESET_STREAMS	119
#घोषणा SCTP_RESET_ASSOC	120
#घोषणा SCTP_ADD_STREAMS	121
#घोषणा SCTP_SOCKOPT_PEELOFF_FLAGS 122
#घोषणा SCTP_STREAM_SCHEDULER	123
#घोषणा SCTP_STREAM_SCHEDULER_VALUE	124
#घोषणा SCTP_INTERLEAVING_SUPPORTED	125
#घोषणा SCTP_SENDMSG_CONNECT	126
#घोषणा SCTP_EVENT	127
#घोषणा SCTP_ASCONF_SUPPORTED	128
#घोषणा SCTP_AUTH_SUPPORTED	129
#घोषणा SCTP_ECN_SUPPORTED	130
#घोषणा SCTP_EXPOSE_POTENTIALLY_FAILED_STATE	131
#घोषणा SCTP_EXPOSE_PF_STATE	SCTP_EXPOSE_POTENTIALLY_FAILED_STATE
#घोषणा SCTP_REMOTE_UDP_ENCAPS_PORT	132

/* PR-SCTP policies */
#घोषणा SCTP_PR_SCTP_NONE	0x0000
#घोषणा SCTP_PR_SCTP_TTL	0x0010
#घोषणा SCTP_PR_SCTP_RTX	0x0020
#घोषणा SCTP_PR_SCTP_PRIO	0x0030
#घोषणा SCTP_PR_SCTP_MAX	SCTP_PR_SCTP_PRIO
#घोषणा SCTP_PR_SCTP_MASK	0x0030

#घोषणा __SCTP_PR_INDEX(x)	((x >> 4) - 1)
#घोषणा SCTP_PR_INDEX(x)	__SCTP_PR_INDEX(SCTP_PR_SCTP_ ## x)

#घोषणा SCTP_PR_POLICY(x)	((x) & SCTP_PR_SCTP_MASK)
#घोषणा SCTP_PR_SET_POLICY(flags, x)	\
	करो अणु				\
		flags &= ~SCTP_PR_SCTP_MASK;	\
		flags |= x;		\
	पूर्ण जबतक (0)

#घोषणा SCTP_PR_TTL_ENABLED(x)	(SCTP_PR_POLICY(x) == SCTP_PR_SCTP_TTL)
#घोषणा SCTP_PR_RTX_ENABLED(x)	(SCTP_PR_POLICY(x) == SCTP_PR_SCTP_RTX)
#घोषणा SCTP_PR_PRIO_ENABLED(x)	(SCTP_PR_POLICY(x) == SCTP_PR_SCTP_PRIO)

/* For enable stream reset */
#घोषणा SCTP_ENABLE_RESET_STREAM_REQ	0x01
#घोषणा SCTP_ENABLE_RESET_ASSOC_REQ	0x02
#घोषणा SCTP_ENABLE_CHANGE_ASSOC_REQ	0x04
#घोषणा SCTP_ENABLE_STRRESET_MASK	0x07

#घोषणा SCTP_STREAM_RESET_INCOMING	0x01
#घोषणा SCTP_STREAM_RESET_OUTGOING	0x02

/* These are bit fields क्रम msghdr->msg_flags.  See section 5.1.  */
/* On user space Linux, these live in <bits/socket.h> as an क्रमागत.  */
क्रमागत sctp_msg_flags अणु
	MSG_NOTIFICATION = 0x8000,
#घोषणा MSG_NOTIFICATION MSG_NOTIFICATION
पूर्ण;

/* 5.3.1 SCTP Initiation Structure (SCTP_INIT)
 *
 *   This cmsghdr काष्ठाure provides inक्रमmation क्रम initializing new
 *   SCTP associations with sendmsg().  The SCTP_INITMSG socket option
 *   uses this same data काष्ठाure.  This काष्ठाure is not used क्रम
 *   recvmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   ----------------------
 *   IPPROTO_SCTP  SCTP_INIT      काष्ठा sctp_iniपंचांगsg
 */
काष्ठा sctp_iniपंचांगsg अणु
	__u16 sinit_num_ostreams;
	__u16 sinit_max_instreams;
	__u16 sinit_max_attempts;
	__u16 sinit_max_init_समयo;
पूर्ण;

/* 5.3.2 SCTP Header Inक्रमmation Structure (SCTP_SNDRCV)
 *
 *   This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg() and
 *   describes SCTP header inक्रमmation about a received message through
 *   recvmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   ----------------------
 *   IPPROTO_SCTP  SCTP_SNDRCV    काष्ठा sctp_sndrcvinfo
 */
काष्ठा sctp_sndrcvinfo अणु
	__u16 sinfo_stream;
	__u16 sinfo_ssn;
	__u16 sinfo_flags;
	__u32 sinfo_ppid;
	__u32 sinfo_context;
	__u32 sinfo_समयtolive;
	__u32 sinfo_tsn;
	__u32 sinfo_cumtsn;
	sctp_assoc_t sinfo_assoc_id;
पूर्ण;

/* 5.3.4 SCTP Send Inक्रमmation Structure (SCTP_SNDINFO)
 *
 *   This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   -------------------
 *   IPPROTO_SCTP  SCTP_SNDINFO   काष्ठा sctp_sndinfo
 */
काष्ठा sctp_sndinfo अणु
	__u16 snd_sid;
	__u16 snd_flags;
	__u32 snd_ppid;
	__u32 snd_context;
	sctp_assoc_t snd_assoc_id;
पूर्ण;

/* 5.3.5 SCTP Receive Inक्रमmation Structure (SCTP_RCVINFO)
 *
 *   This cmsghdr काष्ठाure describes SCTP receive inक्रमmation
 *   about a received message through recvmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   -------------------
 *   IPPROTO_SCTP  SCTP_RCVINFO   काष्ठा sctp_rcvinfo
 */
काष्ठा sctp_rcvinfo अणु
	__u16 rcv_sid;
	__u16 rcv_ssn;
	__u16 rcv_flags;
	__u32 rcv_ppid;
	__u32 rcv_tsn;
	__u32 rcv_cumtsn;
	__u32 rcv_context;
	sctp_assoc_t rcv_assoc_id;
पूर्ण;

/* 5.3.6 SCTP Next Receive Inक्रमmation Structure (SCTP_NXTINFO)
 *
 *   This cmsghdr काष्ठाure describes SCTP receive inक्रमmation
 *   of the next message that will be delivered through recvmsg()
 *   अगर this inक्रमmation is alपढ़ोy available when delivering
 *   the current message.
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   -------------------
 *   IPPROTO_SCTP  SCTP_NXTINFO   काष्ठा sctp_nxtinfo
 */
काष्ठा sctp_nxtinfo अणु
	__u16 nxt_sid;
	__u16 nxt_flags;
	__u32 nxt_ppid;
	__u32 nxt_length;
	sctp_assoc_t nxt_assoc_id;
पूर्ण;

/* 5.3.7 SCTP PR-SCTP Inक्रमmation Structure (SCTP_PRINFO)
 *
 *   This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   -------------------
 *   IPPROTO_SCTP  SCTP_PRINFO    काष्ठा sctp_prinfo
 */
काष्ठा sctp_prinfo अणु
	__u16 pr_policy;
	__u32 pr_value;
पूर्ण;

/* 5.3.8 SCTP AUTH Inक्रमmation Structure (SCTP_AUTHINFO)
 *
 *   This cmsghdr काष्ठाure specअगरies SCTP options क्रम sendmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   -------------------
 *   IPPROTO_SCTP  SCTP_AUTHINFO  काष्ठा sctp_authinfo
 */
काष्ठा sctp_authinfo अणु
	__u16 auth_keynumber;
पूर्ण;

/*
 *  sinfo_flags: 16 bits (अचिन्हित पूर्णांकeger)
 *
 *   This field may contain any of the following flags and is composed of
 *   a bitwise OR of these values.
 */
क्रमागत sctp_sinfo_flags अणु
	SCTP_UNORDERED		= (1 << 0), /* Send/receive message unordered. */
	SCTP_ADDR_OVER		= (1 << 1), /* Override the primary destination. */
	SCTP_ABORT		= (1 << 2), /* Send an ABORT message to the peer. */
	SCTP_SACK_IMMEDIATELY	= (1 << 3), /* SACK should be sent without delay. */
	/* 2 bits here have been used by SCTP_PR_SCTP_MASK */
	SCTP_SENDALL		= (1 << 6),
	SCTP_PR_SCTP_ALL	= (1 << 7),
	SCTP_NOTIFICATION	= MSG_NOTIFICATION, /* Next message is not user msg but notअगरication. */
	SCTP_खातापूर्ण		= MSG_FIN,  /* Initiate graceful shutकरोwn process. */
पूर्ण;

प्रकार जोड़ अणु
	__u8   			raw;
	काष्ठा sctp_iniपंचांगsg	init;
	काष्ठा sctp_sndrcvinfo	sndrcv;
पूर्ण sctp_cmsg_data_t;

/* These are cmsg_types.  */
प्रकार क्रमागत sctp_cmsg_type अणु
	SCTP_INIT,		/* 5.2.1 SCTP Initiation Structure */
#घोषणा SCTP_INIT	SCTP_INIT
	SCTP_SNDRCV,		/* 5.2.2 SCTP Header Inक्रमmation Structure */
#घोषणा SCTP_SNDRCV	SCTP_SNDRCV
	SCTP_SNDINFO,		/* 5.3.4 SCTP Send Inक्रमmation Structure */
#घोषणा SCTP_SNDINFO	SCTP_SNDINFO
	SCTP_RCVINFO,		/* 5.3.5 SCTP Receive Inक्रमmation Structure */
#घोषणा SCTP_RCVINFO	SCTP_RCVINFO
	SCTP_NXTINFO,		/* 5.3.6 SCTP Next Receive Inक्रमmation Structure */
#घोषणा SCTP_NXTINFO	SCTP_NXTINFO
	SCTP_PRINFO,		/* 5.3.7 SCTP PR-SCTP Inक्रमmation Structure */
#घोषणा SCTP_PRINFO	SCTP_PRINFO
	SCTP_AUTHINFO,		/* 5.3.8 SCTP AUTH Inक्रमmation Structure */
#घोषणा SCTP_AUTHINFO	SCTP_AUTHINFO
	SCTP_DSTADDRV4,		/* 5.3.9 SCTP Destination IPv4 Address Structure */
#घोषणा SCTP_DSTADDRV4	SCTP_DSTADDRV4
	SCTP_DSTADDRV6,		/* 5.3.10 SCTP Destination IPv6 Address Structure */
#घोषणा SCTP_DSTADDRV6	SCTP_DSTADDRV6
पूर्ण sctp_cmsg_t;

/*
 * 5.3.1.1 SCTP_ASSOC_CHANGE
 *
 *   Communication notअगरications inक्रमm the ULP that an SCTP association
 *   has either begun or ended. The identअगरier क्रम a new association is
 *   provided by this notअगरicaion. The notअगरication inक्रमmation has the
 *   following क्रमmat:
 *
 */
काष्ठा sctp_assoc_change अणु
	__u16 sac_type;
	__u16 sac_flags;
	__u32 sac_length;
	__u16 sac_state;
	__u16 sac_error;
	__u16 sac_outbound_streams;
	__u16 sac_inbound_streams;
	sctp_assoc_t sac_assoc_id;
	__u8 sac_info[0];
पूर्ण;

/*
 *   sac_state: 32 bits (चिन्हित पूर्णांकeger)
 *
 *   This field holds one of a number of values that communicate the
 *   event that happened to the association.  They include:
 *
 *   Note:  The following state names deviate from the API draft as
 *   the names clash too easily with other kernel symbols.
 */
क्रमागत sctp_sac_state अणु
	SCTP_COMM_UP,
	SCTP_COMM_LOST,
	SCTP_RESTART,
	SCTP_SHUTDOWN_COMP,
	SCTP_CANT_STR_ASSOC,
पूर्ण;

/*
 * 5.3.1.2 SCTP_PEER_ADDR_CHANGE
 *
 *   When a destination address on a multi-homed peer encounters a change
 *   an पूर्णांकerface details event is sent.  The inक्रमmation has the
 *   following काष्ठाure:
 */
काष्ठा sctp_paddr_change अणु
	__u16 spc_type;
	__u16 spc_flags;
	__u32 spc_length;
	काष्ठा sockaddr_storage spc_aaddr;
	पूर्णांक spc_state;
	पूर्णांक spc_error;
	sctp_assoc_t spc_assoc_id;
पूर्ण __attribute__((packed, aligned(4)));

/*
 *    spc_state:  32 bits (चिन्हित पूर्णांकeger)
 *
 *   This field holds one of a number of values that communicate the
 *   event that happened to the address.  They include:
 */
क्रमागत sctp_spc_state अणु
	SCTP_ADDR_AVAILABLE,
	SCTP_ADDR_UNREACHABLE,
	SCTP_ADDR_REMOVED,
	SCTP_ADDR_ADDED,
	SCTP_ADDR_MADE_PRIM,
	SCTP_ADDR_CONFIRMED,
	SCTP_ADDR_POTENTIALLY_FAILED,
#घोषणा SCTP_ADDR_PF	SCTP_ADDR_POTENTIALLY_FAILED
पूर्ण;


/*
 * 5.3.1.3 SCTP_REMOTE_ERROR
 *
 *   A remote peer may send an Operational Error message to its peer.
 *   This message indicates a variety of error conditions on an
 *   association. The entire error TLV as it appears on the wire is
 *   included in a SCTP_REMOTE_ERROR event.  Please refer to the SCTP
 *   specअगरication [SCTP] and any extensions क्रम a list of possible
 *   error क्रमmats. SCTP error TLVs have the क्रमmat:
 */
काष्ठा sctp_remote_error अणु
	__u16 sre_type;
	__u16 sre_flags;
	__u32 sre_length;
	__be16 sre_error;
	sctp_assoc_t sre_assoc_id;
	__u8 sre_data[0];
पूर्ण;


/*
 * 5.3.1.4 SCTP_SEND_FAILED
 *
 *   If SCTP cannot deliver a message it may वापस the message as a
 *   notअगरication.
 */
काष्ठा sctp_send_failed अणु
	__u16 ssf_type;
	__u16 ssf_flags;
	__u32 ssf_length;
	__u32 ssf_error;
	काष्ठा sctp_sndrcvinfo ssf_info;
	sctp_assoc_t ssf_assoc_id;
	__u8 ssf_data[0];
पूर्ण;

काष्ठा sctp_send_failed_event अणु
	__u16 ssf_type;
	__u16 ssf_flags;
	__u32 ssf_length;
	__u32 ssf_error;
	काष्ठा sctp_sndinfo ssfe_info;
	sctp_assoc_t ssf_assoc_id;
	__u8 ssf_data[0];
पूर्ण;

/*
 *   ssf_flags: 16 bits (अचिन्हित पूर्णांकeger)
 *
 *   The flag value will take one of the following values
 *
 *   SCTP_DATA_UNSENT  - Indicates that the data was never put on
 *                       the wire.
 *
 *   SCTP_DATA_SENT    - Indicates that the data was put on the wire.
 *                       Note that this करोes not necessarily mean that the
 *                       data was (or was not) successfully delivered.
 */
क्रमागत sctp_ssf_flags अणु
	SCTP_DATA_UNSENT,
	SCTP_DATA_SENT,
पूर्ण;

/*
 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
 *
 *   When a peer sends a SHUTDOWN, SCTP delivers this notअगरication to
 *   inक्रमm the application that it should cease sending data.
 */
काष्ठा sctp_shutकरोwn_event अणु
	__u16 sse_type;
	__u16 sse_flags;
	__u32 sse_length;
	sctp_assoc_t sse_assoc_id;
पूर्ण;

/*
 * 5.3.1.6 SCTP_ADAPTATION_INDICATION
 *
 *   When a peer sends a Adaptation Layer Indication parameter , SCTP
 *   delivers this notअगरication to inक्रमm the application
 *   that of the peers requested adaptation layer.
 */
काष्ठा sctp_adaptation_event अणु
	__u16 sai_type;
	__u16 sai_flags;
	__u32 sai_length;
	__u32 sai_adaptation_ind;
	sctp_assoc_t sai_assoc_id;
पूर्ण;

/*
 * 5.3.1.7 SCTP_PARTIAL_DELIVERY_EVENT
 *
 *   When a receiver is engaged in a partial delivery of a
 *   message this notअगरication will be used to indicate
 *   various events.
 */
काष्ठा sctp_pdapi_event अणु
	__u16 pdapi_type;
	__u16 pdapi_flags;
	__u32 pdapi_length;
	__u32 pdapi_indication;
	sctp_assoc_t pdapi_assoc_id;
	__u32 pdapi_stream;
	__u32 pdapi_seq;
पूर्ण;

क्रमागत अणु SCTP_PARTIAL_DELIVERY_ABORTED=0, पूर्ण;

/*
 * 5.3.1.8.  SCTP_AUTHENTICATION_EVENT
 *
 *  When a receiver is using authentication this message will provide
 *  notअगरications regarding new keys being made active as well as errors.
 */
काष्ठा sctp_authkey_event अणु
	__u16 auth_type;
	__u16 auth_flags;
	__u32 auth_length;
	__u16 auth_keynumber;
	__u16 auth_altkeynumber;
	__u32 auth_indication;
	sctp_assoc_t auth_assoc_id;
पूर्ण;

क्रमागत अणु
	SCTP_AUTH_NEW_KEY,
#घोषणा	SCTP_AUTH_NEWKEY	SCTP_AUTH_NEW_KEY /* compatible with beक्रमe */
	SCTP_AUTH_FREE_KEY,
	SCTP_AUTH_NO_AUTH,
पूर्ण;

/*
 * 6.1.9. SCTP_SENDER_DRY_EVENT
 *
 * When the SCTP stack has no more user data to send or retransmit, this
 * notअगरication is given to the user. Also, at the समय when a user app
 * subscribes to this event, अगर there is no data to be sent or
 * retransmit, the stack will immediately send up this notअगरication.
 */
काष्ठा sctp_sender_dry_event अणु
	__u16 sender_dry_type;
	__u16 sender_dry_flags;
	__u32 sender_dry_length;
	sctp_assoc_t sender_dry_assoc_id;
पूर्ण;

#घोषणा SCTP_STREAM_RESET_INCOMING_SSN	0x0001
#घोषणा SCTP_STREAM_RESET_OUTGOING_SSN	0x0002
#घोषणा SCTP_STREAM_RESET_DENIED	0x0004
#घोषणा SCTP_STREAM_RESET_FAILED	0x0008
काष्ठा sctp_stream_reset_event अणु
	__u16 strreset_type;
	__u16 strreset_flags;
	__u32 strreset_length;
	sctp_assoc_t strreset_assoc_id;
	__u16 strreset_stream_list[];
पूर्ण;

#घोषणा SCTP_ASSOC_RESET_DENIED		0x0004
#घोषणा SCTP_ASSOC_RESET_FAILED		0x0008
काष्ठा sctp_assoc_reset_event अणु
	__u16 assocreset_type;
	__u16 assocreset_flags;
	__u32 assocreset_length;
	sctp_assoc_t assocreset_assoc_id;
	__u32 assocreset_local_tsn;
	__u32 assocreset_remote_tsn;
पूर्ण;

#घोषणा SCTP_ASSOC_CHANGE_DENIED	0x0004
#घोषणा SCTP_ASSOC_CHANGE_FAILED	0x0008
#घोषणा SCTP_STREAM_CHANGE_DENIED	SCTP_ASSOC_CHANGE_DENIED
#घोषणा SCTP_STREAM_CHANGE_FAILED	SCTP_ASSOC_CHANGE_FAILED
काष्ठा sctp_stream_change_event अणु
	__u16 strchange_type;
	__u16 strchange_flags;
	__u32 strchange_length;
	sctp_assoc_t strchange_assoc_id;
	__u16 strchange_instrms;
	__u16 strchange_outstrms;
पूर्ण;

/*
 * Described in Section 7.3
 *   Ancillary Data and Notअगरication Interest Options
 */
काष्ठा sctp_event_subscribe अणु
	__u8 sctp_data_io_event;
	__u8 sctp_association_event;
	__u8 sctp_address_event;
	__u8 sctp_send_failure_event;
	__u8 sctp_peer_error_event;
	__u8 sctp_shutकरोwn_event;
	__u8 sctp_partial_delivery_event;
	__u8 sctp_adaptation_layer_event;
	__u8 sctp_authentication_event;
	__u8 sctp_sender_dry_event;
	__u8 sctp_stream_reset_event;
	__u8 sctp_assoc_reset_event;
	__u8 sctp_stream_change_event;
	__u8 sctp_send_failure_event_event;
पूर्ण;

/*
 * 5.3.1 SCTP Notअगरication Structure
 *
 *   The notअगरication काष्ठाure is defined as the जोड़ of all
 *   notअगरication types.
 *
 */
जोड़ sctp_notअगरication अणु
	काष्ठा अणु
		__u16 sn_type;             /* Notअगरication type. */
		__u16 sn_flags;
		__u32 sn_length;
	पूर्ण sn_header;
	काष्ठा sctp_assoc_change sn_assoc_change;
	काष्ठा sctp_paddr_change sn_paddr_change;
	काष्ठा sctp_remote_error sn_remote_error;
	काष्ठा sctp_send_failed sn_send_failed;
	काष्ठा sctp_shutकरोwn_event sn_shutकरोwn_event;
	काष्ठा sctp_adaptation_event sn_adaptation_event;
	काष्ठा sctp_pdapi_event sn_pdapi_event;
	काष्ठा sctp_authkey_event sn_authkey_event;
	काष्ठा sctp_sender_dry_event sn_sender_dry_event;
	काष्ठा sctp_stream_reset_event sn_strreset_event;
	काष्ठा sctp_assoc_reset_event sn_assocreset_event;
	काष्ठा sctp_stream_change_event sn_strchange_event;
	काष्ठा sctp_send_failed_event sn_send_failed_event;
पूर्ण;

/* Section 5.3.1
 * All standard values क्रम sn_type flags are greater than 2^15.
 * Values from 2^15 and करोwn are reserved.
 */

क्रमागत sctp_sn_type अणु
	SCTP_SN_TYPE_BASE	= (1<<15),
	SCTP_DATA_IO_EVENT	= SCTP_SN_TYPE_BASE,
#घोषणा SCTP_DATA_IO_EVENT		SCTP_DATA_IO_EVENT
	SCTP_ASSOC_CHANGE,
#घोषणा SCTP_ASSOC_CHANGE		SCTP_ASSOC_CHANGE
	SCTP_PEER_ADDR_CHANGE,
#घोषणा SCTP_PEER_ADDR_CHANGE		SCTP_PEER_ADDR_CHANGE
	SCTP_SEND_FAILED,
#घोषणा SCTP_SEND_FAILED		SCTP_SEND_FAILED
	SCTP_REMOTE_ERROR,
#घोषणा SCTP_REMOTE_ERROR		SCTP_REMOTE_ERROR
	SCTP_SHUTDOWN_EVENT,
#घोषणा SCTP_SHUTDOWN_EVENT		SCTP_SHUTDOWN_EVENT
	SCTP_PARTIAL_DELIVERY_EVENT,
#घोषणा SCTP_PARTIAL_DELIVERY_EVENT	SCTP_PARTIAL_DELIVERY_EVENT
	SCTP_ADAPTATION_INDICATION,
#घोषणा SCTP_ADAPTATION_INDICATION	SCTP_ADAPTATION_INDICATION
	SCTP_AUTHENTICATION_EVENT,
#घोषणा SCTP_AUTHENTICATION_INDICATION	SCTP_AUTHENTICATION_EVENT
	SCTP_SENDER_DRY_EVENT,
#घोषणा SCTP_SENDER_DRY_EVENT		SCTP_SENDER_DRY_EVENT
	SCTP_STREAM_RESET_EVENT,
#घोषणा SCTP_STREAM_RESET_EVENT		SCTP_STREAM_RESET_EVENT
	SCTP_ASSOC_RESET_EVENT,
#घोषणा SCTP_ASSOC_RESET_EVENT		SCTP_ASSOC_RESET_EVENT
	SCTP_STREAM_CHANGE_EVENT,
#घोषणा SCTP_STREAM_CHANGE_EVENT	SCTP_STREAM_CHANGE_EVENT
	SCTP_SEND_FAILED_EVENT,
#घोषणा SCTP_SEND_FAILED_EVENT		SCTP_SEND_FAILED_EVENT
	SCTP_SN_TYPE_MAX	= SCTP_SEND_FAILED_EVENT,
#घोषणा SCTP_SN_TYPE_MAX		SCTP_SN_TYPE_MAX
पूर्ण;

/* Notअगरication error codes used to fill up the error fields in some
 * notअगरications.
 * SCTP_PEER_ADDRESS_CHAGE 	: spc_error
 * SCTP_ASSOC_CHANGE		: sac_error
 * These names should be potentially included in the draft 04 of the SCTP
 * sockets API specअगरication.
 */
प्रकार क्रमागत sctp_sn_error अणु
	SCTP_FAILED_THRESHOLD,
	SCTP_RECEIVED_SACK,
	SCTP_HEARTBEAT_SUCCESS,
	SCTP_RESPONSE_TO_USER_REQ,
	SCTP_INTERNAL_ERROR,
	SCTP_SHUTDOWN_GUARD_EXPIRES,
	SCTP_PEER_FAULTY,
पूर्ण sctp_sn_error_t;

/*
 * 7.1.1 Retransmission Timeout Parameters (SCTP_RTOINFO)
 *
 *   The protocol parameters used to initialize and bound retransmission
 *   समयout (RTO) are tunable.  See [SCTP] क्रम more inक्रमmation on how
 *   these parameters are used in RTO calculation.
 */
काष्ठा sctp_rtoinfo अणु
	sctp_assoc_t	srto_assoc_id;
	__u32		srto_initial;
	__u32		srto_max;
	__u32		srto_min;
पूर्ण;

/*
 * 7.1.2 Association Parameters (SCTP_ASSOCINFO)
 *
 *   This option is used to both examine and set various association and
 *   endpoपूर्णांक parameters.
 */
काष्ठा sctp_assocparams अणु
	sctp_assoc_t	sasoc_assoc_id;
	__u16		sasoc_asocmaxrxt;
	__u16		sasoc_number_peer_destinations;
	__u32		sasoc_peer_rwnd;
	__u32		sasoc_local_rwnd;
	__u32		sasoc_cookie_lअगरe;
पूर्ण;

/*
 * 7.1.9 Set Peer Primary Address (SCTP_SET_PEER_PRIMARY_ADDR)
 *
 *  Requests that the peer mark the enबंदd address as the association
 *  primary. The enबंदd address must be one of the association's
 *  locally bound addresses. The following काष्ठाure is used to make a
 *   set primary request:
 */
काष्ठा sctp_setpeerprim अणु
	sctp_assoc_t            sspp_assoc_id;
	काष्ठा sockaddr_storage sspp_addr;
पूर्ण __attribute__((packed, aligned(4)));

/*
 * 7.1.10 Set Primary Address (SCTP_PRIMARY_ADDR)
 *
 *  Requests that the local SCTP stack use the enबंदd peer address as
 *  the association primary. The enबंदd address must be one of the
 *  association peer's addresses. The following काष्ठाure is used to
 *  make a set peer primary request:
 */
काष्ठा sctp_prim अणु
	sctp_assoc_t            ssp_assoc_id;
	काष्ठा sockaddr_storage ssp_addr;
पूर्ण __attribute__((packed, aligned(4)));

/* For backward compatibility use, define the old name too */
#घोषणा sctp_setprim	sctp_prim

/*
 * 7.1.11 Set Adaptation Layer Indicator (SCTP_ADAPTATION_LAYER)
 *
 * Requests that the local endpoपूर्णांक set the specअगरied Adaptation Layer
 * Indication parameter क्रम all future INIT and INIT-ACK exchanges.
 */
काष्ठा sctp_setadaptation अणु
	__u32	ssb_adaptation_ind;
पूर्ण;

/*
 * 7.1.13 Peer Address Parameters  (SCTP_PEER_ADDR_PARAMS)
 *
 *   Applications can enable or disable heartbeats क्रम any peer address
 *   of an association, modअगरy an address's heartbeat पूर्णांकerval, क्रमce a
 *   heartbeat to be sent immediately, and adjust the address's maximum
 *   number of retransmissions sent beक्रमe an address is considered
 *   unreachable. The following काष्ठाure is used to access and modअगरy an
 *   address's parameters:
 */
क्रमागत  sctp_spp_flags अणु
	SPP_HB_ENABLE = 1<<0,		/*Enable heartbeats*/
	SPP_HB_DISABLE = 1<<1,		/*Disable heartbeats*/
	SPP_HB = SPP_HB_ENABLE | SPP_HB_DISABLE,
	SPP_HB_DEMAND = 1<<2,		/*Send heartbeat immediately*/
	SPP_PMTUD_ENABLE = 1<<3,	/*Enable PMTU discovery*/
	SPP_PMTUD_DISABLE = 1<<4,	/*Disable PMTU discovery*/
	SPP_PMTUD = SPP_PMTUD_ENABLE | SPP_PMTUD_DISABLE,
	SPP_SACKDELAY_ENABLE = 1<<5,	/*Enable SACK*/
	SPP_SACKDELAY_DISABLE = 1<<6,	/*Disable SACK*/
	SPP_SACKDELAY = SPP_SACKDELAY_ENABLE | SPP_SACKDELAY_DISABLE,
	SPP_HB_TIME_IS_ZERO = 1<<7,	/* Set HB delay to 0 */
	SPP_IPV6_FLOWLABEL = 1<<8,
	SPP_DSCP = 1<<9,
पूर्ण;

काष्ठा sctp_paddrparams अणु
	sctp_assoc_t		spp_assoc_id;
	काष्ठा sockaddr_storage	spp_address;
	__u32			spp_hbपूर्णांकerval;
	__u16			spp_pathmaxrxt;
	__u32			spp_pathmtu;
	__u32			spp_sackdelay;
	__u32			spp_flags;
	__u32			spp_ipv6_flowlabel;
	__u8			spp_dscp;
पूर्ण __attribute__((packed, aligned(4)));

/*
 * 7.1.18.  Add a chunk that must be authenticated (SCTP_AUTH_CHUNK)
 *
 * This set option adds a chunk type that the user is requesting to be
 * received only in an authenticated way.  Changes to the list of chunks
 * will only effect future associations on the socket.
 */
काष्ठा sctp_authchunk अणु
	__u8		sauth_chunk;
पूर्ण;

/*
 * 7.1.19.  Get or set the list of supported HMAC Identअगरiers (SCTP_HMAC_IDENT)
 *
 * This option माला_लो or sets the list of HMAC algorithms that the local
 * endpoपूर्णांक requires the peer to use.
 */
#अगर_अघोषित __KERNEL__
/* This here is only used by user space as is. It might not be a good idea
 * to export/reveal the whole काष्ठाure with reserved fields etc.
 */
क्रमागत अणु
	SCTP_AUTH_HMAC_ID_SHA1 = 1,
	SCTP_AUTH_HMAC_ID_SHA256 = 3,
पूर्ण;
#पूर्ण_अगर

काष्ठा sctp_hmacalgo अणु
	__u32		shmac_num_idents;
	__u16		shmac_idents[];
पूर्ण;

/* Sadly, user and kernel space have dअगरferent names क्रम
 * this काष्ठाure member, so this is to not अवरोध anything.
 */
#घोषणा shmac_number_of_idents	shmac_num_idents

/*
 * 7.1.20.  Set a shared key (SCTP_AUTH_KEY)
 *
 * This option will set a shared secret key which is used to build an
 * association shared key.
 */
काष्ठा sctp_authkey अणु
	sctp_assoc_t	sca_assoc_id;
	__u16		sca_keynumber;
	__u16		sca_keylength;
	__u8		sca_key[];
पूर्ण;

/*
 * 7.1.21.  Get or set the active shared key (SCTP_AUTH_ACTIVE_KEY)
 *
 * This option will get or set the active shared key to be used to build
 * the association shared key.
 */

काष्ठा sctp_authkeyid अणु
	sctp_assoc_t	scact_assoc_id;
	__u16		scact_keynumber;
पूर्ण;


/*
 * 7.1.23.  Get or set delayed ack समयr (SCTP_DELAYED_SACK)
 *
 * This option will effect the way delayed acks are perक्रमmed.  This
 * option allows you to get or set the delayed ack समय, in
 * milliseconds.  It also allows changing the delayed ack frequency.
 * Changing the frequency to 1 disables the delayed sack algorithm.  If
 * the assoc_id is 0, then this sets or माला_लो the endpoपूर्णांकs शेष
 * values.  If the assoc_id field is non-zero, then the set or get
 * effects the specअगरied association क्रम the one to many model (the
 * assoc_id field is ignored by the one to one model).  Note that अगर
 * sack_delay or sack_freq are 0 when setting this option, then the
 * current values will reमुख्य unchanged.
 */
काष्ठा sctp_sack_info अणु
	sctp_assoc_t	sack_assoc_id;
	uपूर्णांक32_t	sack_delay;
	uपूर्णांक32_t	sack_freq;
पूर्ण;

काष्ठा sctp_assoc_value अणु
    sctp_assoc_t            assoc_id;
    uपूर्णांक32_t                assoc_value;
पूर्ण;

काष्ठा sctp_stream_value अणु
	sctp_assoc_t assoc_id;
	uपूर्णांक16_t stream_id;
	uपूर्णांक16_t stream_value;
पूर्ण;

/*
 * 7.2.2 Peer Address Inक्रमmation
 *
 *   Applications can retrieve inक्रमmation about a specअगरic peer address
 *   of an association, including its reachability state, congestion
 *   winकरोw, and retransmission समयr values.  This inक्रमmation is
 *   पढ़ो-only. The following काष्ठाure is used to access this
 *   inक्रमmation:
 */
काष्ठा sctp_paddrinfo अणु
	sctp_assoc_t		spinfo_assoc_id;
	काष्ठा sockaddr_storage	spinfo_address;
	__s32			spinfo_state;
	__u32			spinfo_cwnd;
	__u32			spinfo_srtt;
	__u32			spinfo_rto;
	__u32			spinfo_mtu;
पूर्ण __attribute__((packed, aligned(4)));

/* Peer addresses's state. */
/* UNKNOWN: Peer address passed by the upper layer in sendmsg or connect[x]
 * calls.
 * UNCONFIRMED: Peer address received in INIT/INIT-ACK address parameters.
 *              Not yet confirmed by a heartbeat and not available क्रम data
 *		transfers.
 * ACTIVE : Peer address confirmed, active and available क्रम data transfers.
 * INACTIVE: Peer address inactive and not available क्रम data transfers.
 */
क्रमागत sctp_spinfo_state अणु
	SCTP_INACTIVE,
	SCTP_PF,
#घोषणा	SCTP_POTENTIALLY_FAILED		SCTP_PF
	SCTP_ACTIVE,
	SCTP_UNCONFIRMED,
	SCTP_UNKNOWN = 0xffff  /* Value used क्रम transport state unknown */
पूर्ण;

/*
 * 7.2.1 Association Status (SCTP_STATUS)
 *
 *   Applications can retrieve current status inक्रमmation about an
 *   association, including association state, peer receiver winकरोw size,
 *   number of unacked data chunks, and number of data chunks pending
 *   receipt.  This inक्रमmation is पढ़ो-only.  The following काष्ठाure is
 *   used to access this inक्रमmation:
 */
काष्ठा sctp_status अणु
	sctp_assoc_t		sstat_assoc_id;
	__s32			sstat_state;
	__u32			sstat_rwnd;
	__u16			sstat_unackdata;
	__u16			sstat_penddata;
	__u16			sstat_instrms;
	__u16			sstat_outstrms;
	__u32			sstat_fragmentation_poपूर्णांक;
	काष्ठा sctp_paddrinfo	sstat_primary;
पूर्ण;

/*
 * 7.2.3.  Get the list of chunks the peer requires to be authenticated
 *         (SCTP_PEER_AUTH_CHUNKS)
 *
 * This option माला_लो a list of chunks क्रम a specअगरied association that
 * the peer requires to be received authenticated only.
 */
काष्ठा sctp_authchunks अणु
	sctp_assoc_t	gauth_assoc_id;
	__u32		gauth_number_of_chunks;
	uपूर्णांक8_t		gauth_chunks[];
पूर्ण;

/* The broken spelling has been released alपढ़ोy in lksctp-tools header,
 * so करोn't break anyone, now that it's fixed.
 */
#घोषणा guth_number_of_chunks	gauth_number_of_chunks

/* Association states.  */
क्रमागत sctp_sstat_state अणु
	SCTP_EMPTY                = 0,
	SCTP_CLOSED               = 1,
	SCTP_COOKIE_WAIT          = 2,
	SCTP_COOKIE_ECHOED        = 3,
	SCTP_ESTABLISHED          = 4,
	SCTP_SHUTDOWN_PENDING     = 5,
	SCTP_SHUTDOWN_SENT        = 6,
	SCTP_SHUTDOWN_RECEIVED    = 7,
	SCTP_SHUTDOWN_ACK_SENT    = 8,
पूर्ण;

/*
 * 8.2.6. Get the Current Identअगरiers of Associations
 *        (SCTP_GET_ASSOC_ID_LIST)
 *
 * This option माला_लो the current list of SCTP association identअगरiers of
 * the SCTP associations handled by a one-to-many style socket.
 */
काष्ठा sctp_assoc_ids अणु
	__u32		gaids_number_of_ids;
	sctp_assoc_t	gaids_assoc_id[];
पूर्ण;

/*
 * 8.3, 8.5 get all peer/local addresses in an association.
 * This parameter काष्ठा is used by SCTP_GET_PEER_ADDRS and
 * SCTP_GET_LOCAL_ADDRS socket options used पूर्णांकernally to implement
 * sctp_getpaddrs() and sctp_getladdrs() API.
 */
काष्ठा sctp_getaddrs_old अणु
	sctp_assoc_t            assoc_id;
	पूर्णांक			addr_num;
#अगर_घोषित __KERNEL__
	काष्ठा sockaddr		__user *addrs;
#अन्यथा
	काष्ठा sockaddr		*addrs;
#पूर्ण_अगर
पूर्ण;

काष्ठा sctp_getaddrs अणु
	sctp_assoc_t		assoc_id; /*input*/
	__u32			addr_num; /*output*/
	__u8			addrs[0]; /*output, variable size*/
पूर्ण;

/* A socket user request obtained via SCTP_GET_ASSOC_STATS that retrieves
 * association stats. All stats are counts except sas_maxrto and
 * sas_obs_rto_ipaddr. maxrto is the max observed rto + transport since
 * the last call. Will वापस 0 when RTO was not update since last call
 */
काष्ठा sctp_assoc_stats अणु
	sctp_assoc_t	sas_assoc_id;    /* Input */
					 /* Transport of observed max RTO */
	काष्ठा sockaddr_storage sas_obs_rto_ipaddr;
	__u64		sas_maxrto;      /* Maximum Observed RTO क्रम period */
	__u64		sas_isacks;	 /* SACKs received */
	__u64		sas_osacks;	 /* SACKs sent */
	__u64		sas_opackets;	 /* Packets sent */
	__u64		sas_ipackets;	 /* Packets received */
	__u64		sas_rtxchunks;   /* Retransmitted Chunks */
	__u64		sas_outofseqtsns;/* TSN received > next expected */
	__u64		sas_idupchunks;  /* Dups received (ordered+unordered) */
	__u64		sas_gapcnt;      /* Gap Acknowledgements Received */
	__u64		sas_ouodchunks;  /* Unordered data chunks sent */
	__u64		sas_iuodchunks;  /* Unordered data chunks received */
	__u64		sas_oodchunks;	 /* Ordered data chunks sent */
	__u64		sas_iodchunks;	 /* Ordered data chunks received */
	__u64		sas_octrlchunks; /* Control chunks sent */
	__u64		sas_ictrlchunks; /* Control chunks received */
पूर्ण;

/*
 * 8.1 sctp_bindx()
 *
 * The flags parameter is क्रमmed from the bitwise OR of zero or more of the
 * following currently defined flags:
 */
#घोषणा SCTP_BINDX_ADD_ADDR 0x01
#घोषणा SCTP_BINDX_REM_ADDR 0x02

/* This is the काष्ठाure that is passed as an argument(optval) to
 * माला_लोockopt(SCTP_SOCKOPT_PEELOFF).
 */
प्रकार काष्ठा अणु
	sctp_assoc_t associd;
	पूर्णांक sd;
पूर्ण sctp_peeloff_arg_t;

प्रकार काष्ठा अणु
	sctp_peeloff_arg_t p_arg;
	अचिन्हित flags;
पूर्ण sctp_peeloff_flags_arg_t;

/*
 *  Peer Address Thresholds socket option
 */
काष्ठा sctp_paddrthlds अणु
	sctp_assoc_t spt_assoc_id;
	काष्ठा sockaddr_storage spt_address;
	__u16 spt_pathmaxrxt;
	__u16 spt_pathpfthld;
पूर्ण;

/* Use a new काष्ठाure with spt_pathcpthld क्रम back compatibility */
काष्ठा sctp_paddrthlds_v2 अणु
	sctp_assoc_t spt_assoc_id;
	काष्ठा sockaddr_storage spt_address;
	__u16 spt_pathmaxrxt;
	__u16 spt_pathpfthld;
	__u16 spt_pathcpthld;
पूर्ण;

/*
 * Socket Option क्रम Getting the Association/Stream-Specअगरic PR-SCTP Status
 */
काष्ठा sctp_prstatus अणु
	sctp_assoc_t sprstat_assoc_id;
	__u16 sprstat_sid;
	__u16 sprstat_policy;
	__u64 sprstat_abanकरोned_unsent;
	__u64 sprstat_abanकरोned_sent;
पूर्ण;

काष्ठा sctp_शेष_prinfo अणु
	sctp_assoc_t pr_assoc_id;
	__u32 pr_value;
	__u16 pr_policy;
पूर्ण;

काष्ठा sctp_info अणु
	__u32	sctpi_tag;
	__u32	sctpi_state;
	__u32	sctpi_rwnd;
	__u16	sctpi_unackdata;
	__u16	sctpi_penddata;
	__u16	sctpi_instrms;
	__u16	sctpi_outstrms;
	__u32	sctpi_fragmentation_poपूर्णांक;
	__u32	sctpi_inqueue;
	__u32	sctpi_outqueue;
	__u32	sctpi_overall_error;
	__u32	sctpi_max_burst;
	__u32	sctpi_maxseg;
	__u32	sctpi_peer_rwnd;
	__u32	sctpi_peer_tag;
	__u8	sctpi_peer_capable;
	__u8	sctpi_peer_sack;
	__u16	__reserved1;

	/* assoc status info */
	__u64	sctpi_isacks;
	__u64	sctpi_osacks;
	__u64	sctpi_opackets;
	__u64	sctpi_ipackets;
	__u64	sctpi_rtxchunks;
	__u64	sctpi_outofseqtsns;
	__u64	sctpi_idupchunks;
	__u64	sctpi_gapcnt;
	__u64	sctpi_ouodchunks;
	__u64	sctpi_iuodchunks;
	__u64	sctpi_oodchunks;
	__u64	sctpi_iodchunks;
	__u64	sctpi_octrlchunks;
	__u64	sctpi_ictrlchunks;

	/* primary transport info */
	काष्ठा sockaddr_storage	sctpi_p_address;
	__s32	sctpi_p_state;
	__u32	sctpi_p_cwnd;
	__u32	sctpi_p_srtt;
	__u32	sctpi_p_rto;
	__u32	sctpi_p_hbपूर्णांकerval;
	__u32	sctpi_p_pathmaxrxt;
	__u32	sctpi_p_sackdelay;
	__u32	sctpi_p_sackfreq;
	__u32	sctpi_p_ssthresh;
	__u32	sctpi_p_partial_bytes_acked;
	__u32	sctpi_p_flight_size;
	__u16	sctpi_p_error;
	__u16	__reserved2;

	/* sctp sock info */
	__u32	sctpi_s_स्वतःबंद;
	__u32	sctpi_s_adaptation_ind;
	__u32	sctpi_s_pd_poपूर्णांक;
	__u8	sctpi_s_nodelay;
	__u8	sctpi_s_disable_fragments;
	__u8	sctpi_s_v4mapped;
	__u8	sctpi_s_frag_पूर्णांकerleave;
	__u32	sctpi_s_type;
	__u32	__reserved3;
पूर्ण;

काष्ठा sctp_reset_streams अणु
	sctp_assoc_t srs_assoc_id;
	uपूर्णांक16_t srs_flags;
	uपूर्णांक16_t srs_number_streams;	/* 0 == ALL */
	uपूर्णांक16_t srs_stream_list[];	/* list अगर srs_num_streams is not 0 */
पूर्ण;

काष्ठा sctp_add_streams अणु
	sctp_assoc_t sas_assoc_id;
	uपूर्णांक16_t sas_instrms;
	uपूर्णांक16_t sas_outstrms;
पूर्ण;

काष्ठा sctp_event अणु
	sctp_assoc_t se_assoc_id;
	uपूर्णांक16_t se_type;
	uपूर्णांक8_t se_on;
पूर्ण;

काष्ठा sctp_udpencaps अणु
	sctp_assoc_t sue_assoc_id;
	काष्ठा sockaddr_storage sue_address;
	uपूर्णांक16_t sue_port;
पूर्ण;

/* SCTP Stream schedulers */
क्रमागत sctp_sched_type अणु
	SCTP_SS_FCFS,
	SCTP_SS_DEFAULT = SCTP_SS_FCFS,
	SCTP_SS_PRIO,
	SCTP_SS_RR,
	SCTP_SS_MAX = SCTP_SS_RR
पूर्ण;

#पूर्ण_अगर /* _UAPI_SCTP_H */
