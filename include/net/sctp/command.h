<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel Implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (C) 1999-2001 Cisco, Motorola
 *
 * This file is part of the SCTP kernel implementation
 *
 * These are the definitions needed क्रम the command object.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   La Monte H.P. Yarroll <piggy@acm.org>
 *   Karl Knutson <karl@athena.chicago.il.us>
 *   Ardelle Fan <ardelle.fan@पूर्णांकel.com>
 *   Sridhar Samudrala <sri@us.ibm.com>
 */

#अगर_अघोषित __net_sctp_command_h__
#घोषणा __net_sctp_command_h__

#समावेश <net/sctp/स्थिरants.h>
#समावेश <net/sctp/काष्ठाs.h>


क्रमागत sctp_verb अणु
	SCTP_CMD_NOP = 0,	/* Do nothing. */
	SCTP_CMD_NEW_ASOC,	/* Register a new association.  */
	SCTP_CMD_DELETE_TCB,	/* Delete the current association. */
	SCTP_CMD_NEW_STATE,	/* Enter a new state.  */
	SCTP_CMD_REPORT_TSN,	/* Record the arrival of a TSN.  */
	SCTP_CMD_GEN_SACK,	/* Send a Selective ACK (maybe).  */
	SCTP_CMD_PROCESS_SACK,	/* Process an inbound SACK.  */
	SCTP_CMD_GEN_INIT_ACK,	/* Generate an INIT ACK chunk.  */
	SCTP_CMD_PEER_INIT,	/* Process a INIT from the peer.  */
	SCTP_CMD_GEN_COOKIE_ECHO, /* Generate a COOKIE ECHO chunk. */
	SCTP_CMD_CHUNK_ULP,	/* Send a chunk to the sockets layer.  */
	SCTP_CMD_EVENT_ULP,	/* Send a notअगरication to the sockets layer. */
	SCTP_CMD_REPLY,		/* Send a chunk to our peer.  */
	SCTP_CMD_SEND_PKT,	/* Send a full packet to our peer.  */
	SCTP_CMD_RETRAN,	/* Mark a transport क्रम retransmission.  */
	SCTP_CMD_ECN_CE,        /* Do delayed CE processing.   */
	SCTP_CMD_ECN_ECNE,	/* Do delayed ECNE processing. */
	SCTP_CMD_ECN_CWR,	/* Do delayed CWR processing.  */
	SCTP_CMD_TIMER_START,	/* Start a समयr.  */
	SCTP_CMD_TIMER_START_ONCE, /* Start a समयr once */
	SCTP_CMD_TIMER_RESTART,	/* Restart a समयr. */
	SCTP_CMD_TIMER_STOP,	/* Stop a समयr. */
	SCTP_CMD_INIT_CHOOSE_TRANSPORT, /* Choose transport क्रम an INIT. */
	SCTP_CMD_INIT_COUNTER_RESET, /* Reset init counter. */
	SCTP_CMD_INIT_COUNTER_INC,   /* Increment init counter. */
	SCTP_CMD_INIT_RESTART,  /* High level, करो init समयr work. */
	SCTP_CMD_COOKIEECHO_RESTART,  /* High level, करो cookie-echo समयr work. */
	SCTP_CMD_INIT_FAILED,   /* High level, करो init failure work. */
	SCTP_CMD_REPORT_DUP,	/* Report a duplicate TSN.  */
	SCTP_CMD_STRIKE,	/* Mark a strike against a transport.  */
	SCTP_CMD_HB_TIMERS_START,    /* Start the heartbeat समयrs. */
	SCTP_CMD_HB_TIMER_UPDATE,    /* Update a heartbeat समयrs.  */
	SCTP_CMD_HB_TIMERS_STOP,     /* Stop the heartbeat समयrs.  */
	SCTP_CMD_TRANSPORT_HB_SENT,  /* Reset the status of a transport. */
	SCTP_CMD_TRANSPORT_IDLE,     /* Do manipulations on idle transport */
	SCTP_CMD_TRANSPORT_ON,       /* Mark the transport as active. */
	SCTP_CMD_REPORT_ERROR,   /* Pass this error back out of the sm. */
	SCTP_CMD_REPORT_BAD_TAG, /* Verअगरication tags didn't match. */
	SCTP_CMD_PROCESS_CTSN,   /* Sideeffect from shutकरोwn. */
	SCTP_CMD_ASSOC_FAILED,	 /* Handle association failure. */
	SCTP_CMD_DISCARD_PACKET, /* Discard the whole packet. */
	SCTP_CMD_GEN_SHUTDOWN,   /* Generate a SHUTDOWN chunk. */
	SCTP_CMD_PURGE_OUTQUEUE, /* Purge all data रुकोing to be sent. */
	SCTP_CMD_SETUP_T2,       /* Hi-level, setup T2-shutकरोwn parms.  */
	SCTP_CMD_RTO_PENDING,	 /* Set transport's rto_pending. */
	SCTP_CMD_PART_DELIVER,	 /* Partial data delivery considerations. */
	SCTP_CMD_RENEGE,         /* Renege data on an association. */
	SCTP_CMD_SETUP_T4,	 /* ADDIP, setup T4 RTO समयr parms. */
	SCTP_CMD_PROCESS_OPERR,  /* Process an ERROR chunk. */
	SCTP_CMD_REPORT_FWDTSN,	 /* Report new cumulative TSN Ack. */
	SCTP_CMD_PROCESS_FWDTSN, /* Skips were reported, so process further. */
	SCTP_CMD_CLEAR_INIT_TAG, /* Clears association peer's inittag. */
	SCTP_CMD_DEL_NON_PRIMARY, /* Removes non-primary peer transports. */
	SCTP_CMD_T3_RTX_TIMERS_STOP, /* Stops T3-rtx pending समयrs */
	SCTP_CMD_FORCE_PRIM_RETRAN,  /* Forces retrans. over primary path. */
	SCTP_CMD_SET_SK_ERR,	 /* Set sk_err */
	SCTP_CMD_ASSOC_CHANGE,	 /* generate and send assoc_change event */
	SCTP_CMD_ADAPTATION_IND, /* generate and send adaptation event */
	SCTP_CMD_PEER_NO_AUTH,   /* generate and send authentication event */
	SCTP_CMD_ASSOC_SHKEY,    /* generate the association shared keys */
	SCTP_CMD_T1_RETRAN,	 /* Mark क्रम retransmission after T1 समयout  */
	SCTP_CMD_UPDATE_INITTAG, /* Update peer inittag */
	SCTP_CMD_SEND_MSG,	 /* Send the whole use message */
	SCTP_CMD_PURGE_ASCONF_QUEUE, /* Purge all asconf queues.*/
	SCTP_CMD_SET_ASOC,	 /* Restore association context */
	SCTP_CMD_LAST
पूर्ण;

/* How many commands can you put in an काष्ठा sctp_cmd_seq?
 * This is a rather arbitrary number, ideally derived from a careful
 * analysis of the state functions, but in reality just taken from
 * thin air in the hopes othat we करोn't trigger a kernel panic.
 */
#घोषणा SCTP_MAX_NUM_COMMANDS 20

जोड़ sctp_arg अणु
	व्योम *zero_all;	/* Set to शून्य to clear the entire जोड़ */
	__s32 i32;
	__u32 u32;
	__be32 be32;
	__u16 u16;
	__u8 u8;
	पूर्णांक error;
	__be16 err;
	क्रमागत sctp_state state;
	क्रमागत sctp_event_समयout to;
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_bind_addr *bp;
	काष्ठा sctp_init_chunk *init;
	काष्ठा sctp_ulpevent *ulpevent;
	काष्ठा sctp_packet *packet;
	काष्ठा sctp_sackhdr *sackh;
	काष्ठा sctp_datamsg *msg;
पूर्ण;

/* We are simulating ML type स्थिरructors here.
 *
 * SCTP_ARG_CONSTRUCTOR(NAME, TYPE, ELT) builds a function called
 * SCTP_NAME() which takes an argument of type TYPE and वापसs an
 * जोड़ sctp_arg.  It करोes this by inserting the sole argument पूर्णांकo
 * the ELT जोड़ element of a local जोड़ sctp_arg.
 *
 * E.g., SCTP_ARG_CONSTRUCTOR(I32, __s32, i32) builds SCTP_I32(arg),
 * which takes an __s32 and वापसs a जोड़ sctp_arg containing the
 * __s32.  So, after foo = SCTP_I32(arg), foo.i32 == arg.
 */

#घोषणा SCTP_ARG_CONSTRUCTOR(name, type, elt) \
अटल अंतरभूत जोड़ sctp_arg	\
SCTP_## name (type arg)		\
अणु जोड़ sctp_arg retval;\
  retval.zero_all = शून्य;\
  retval.elt = arg;\
  वापस retval;\
पूर्ण

SCTP_ARG_CONSTRUCTOR(I32,	__s32, i32)
SCTP_ARG_CONSTRUCTOR(U32,	__u32, u32)
SCTP_ARG_CONSTRUCTOR(BE32,	__be32, be32)
SCTP_ARG_CONSTRUCTOR(U16,	__u16, u16)
SCTP_ARG_CONSTRUCTOR(U8,	__u8, u8)
SCTP_ARG_CONSTRUCTOR(ERROR,     पूर्णांक, error)
SCTP_ARG_CONSTRUCTOR(PERR,      __be16, err)	/* protocol error */
SCTP_ARG_CONSTRUCTOR(STATE,	क्रमागत sctp_state, state)
SCTP_ARG_CONSTRUCTOR(TO,	क्रमागत sctp_event_समयout, to)
SCTP_ARG_CONSTRUCTOR(CHUNK,	काष्ठा sctp_chunk *, chunk)
SCTP_ARG_CONSTRUCTOR(ASOC,	काष्ठा sctp_association *, asoc)
SCTP_ARG_CONSTRUCTOR(TRANSPORT,	काष्ठा sctp_transport *, transport)
SCTP_ARG_CONSTRUCTOR(BA,	काष्ठा sctp_bind_addr *, bp)
SCTP_ARG_CONSTRUCTOR(PEER_INIT,	काष्ठा sctp_init_chunk *, init)
SCTP_ARG_CONSTRUCTOR(ULPEVENT,  काष्ठा sctp_ulpevent *, ulpevent)
SCTP_ARG_CONSTRUCTOR(PACKET,	काष्ठा sctp_packet *, packet)
SCTP_ARG_CONSTRUCTOR(SACKH,	काष्ठा sctp_sackhdr *, sackh)
SCTP_ARG_CONSTRUCTOR(DATAMSG,	काष्ठा sctp_datamsg *, msg)

अटल अंतरभूत जोड़ sctp_arg SCTP_FORCE(व्योम)
अणु
	वापस SCTP_I32(1);
पूर्ण

अटल अंतरभूत जोड़ sctp_arg SCTP_NOFORCE(व्योम)
अणु
	वापस SCTP_I32(0);
पूर्ण

अटल अंतरभूत जोड़ sctp_arg SCTP_शून्य(व्योम)
अणु
	जोड़ sctp_arg retval;
	retval.zero_all = शून्य;
	वापस retval;
पूर्ण

काष्ठा sctp_cmd अणु
	जोड़ sctp_arg obj;
	क्रमागत sctp_verb verb;
पूर्ण;

काष्ठा sctp_cmd_seq अणु
	काष्ठा sctp_cmd cmds[SCTP_MAX_NUM_COMMANDS];
	काष्ठा sctp_cmd *last_used_slot;
	काष्ठा sctp_cmd *next_cmd;
पूर्ण;


/* Initialize a block of memory as a command sequence.
 * Return 0 अगर the initialization fails.
 */
अटल अंतरभूत पूर्णांक sctp_init_cmd_seq(काष्ठा sctp_cmd_seq *seq)
अणु
	/* cmds[] is filled backwards to simplअगरy the overflow BUG() check */
	seq->last_used_slot = seq->cmds + SCTP_MAX_NUM_COMMANDS;
	seq->next_cmd = seq->last_used_slot;
	वापस 1;		/* We always succeed.  */
पूर्ण


/* Add a command to an काष्ठा sctp_cmd_seq.
 *
 * Use the SCTP_* स्थिरructors defined by SCTP_ARG_CONSTRUCTOR() above
 * to wrap data which goes in the obj argument.
 */
अटल अंतरभूत व्योम sctp_add_cmd_sf(काष्ठा sctp_cmd_seq *seq,
				   क्रमागत sctp_verb verb, जोड़ sctp_arg obj)
अणु
	काष्ठा sctp_cmd *cmd = seq->last_used_slot - 1;

	BUG_ON(cmd < seq->cmds);

	cmd->verb = verb;
	cmd->obj = obj;
	seq->last_used_slot = cmd;
पूर्ण

/* Return the next command काष्ठाure in an sctp_cmd_seq.
 * Return शून्य at the end of the sequence.
 */
अटल अंतरभूत काष्ठा sctp_cmd *sctp_next_cmd(काष्ठा sctp_cmd_seq *seq)
अणु
	अगर (seq->next_cmd <= seq->last_used_slot)
		वापस शून्य;

	वापस --seq->next_cmd;
पूर्ण

#पूर्ण_अगर /* __net_sctp_command_h__ */
