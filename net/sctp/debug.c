<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * This file converts numerical ID value to alphabetical names क्रम SCTP
 * terms such as chunk type, parameter समय, event type, etc.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 */

#समावेश <net/sctp/sctp.h>

/* These are prपूर्णांकable क्रमms of Chunk ID's from section 3.1.  */
अटल स्थिर अक्षर *स्थिर sctp_cid_tbl[SCTP_NUM_BASE_CHUNK_TYPES] = अणु
	"DATA",
	"INIT",
	"INIT_ACK",
	"SACK",
	"HEARTBEAT",
	"HEARTBEAT_ACK",
	"ABORT",
	"SHUTDOWN",
	"SHUTDOWN_ACK",
	"ERROR",
	"COOKIE_ECHO",
	"COOKIE_ACK",
	"ECN_ECNE",
	"ECN_CWR",
	"SHUTDOWN_COMPLETE",
पूर्ण;

/* Lookup "chunk type" debug name. */
स्थिर अक्षर *sctp_cname(स्थिर जोड़ sctp_subtype cid)
अणु
	अगर (cid.chunk <= SCTP_CID_BASE_MAX)
		वापस sctp_cid_tbl[cid.chunk];

	चयन (cid.chunk) अणु
	हाल SCTP_CID_ASCONF:
		वापस "ASCONF";

	हाल SCTP_CID_ASCONF_ACK:
		वापस "ASCONF_ACK";

	हाल SCTP_CID_FWD_TSN:
		वापस "FWD_TSN";

	हाल SCTP_CID_AUTH:
		वापस "AUTH";

	हाल SCTP_CID_RECONF:
		वापस "RECONF";

	हाल SCTP_CID_I_DATA:
		वापस "I_DATA";

	हाल SCTP_CID_I_FWD_TSN:
		वापस "I_FWD_TSN";

	शेष:
		अवरोध;
	पूर्ण

	वापस "unknown chunk";
पूर्ण

/* These are prपूर्णांकable क्रमms of the states.  */
स्थिर अक्षर *स्थिर sctp_state_tbl[SCTP_STATE_NUM_STATES] = अणु
	"STATE_CLOSED",
	"STATE_COOKIE_WAIT",
	"STATE_COOKIE_ECHOED",
	"STATE_ESTABLISHED",
	"STATE_SHUTDOWN_PENDING",
	"STATE_SHUTDOWN_SENT",
	"STATE_SHUTDOWN_RECEIVED",
	"STATE_SHUTDOWN_ACK_SENT",
पूर्ण;

/* Events that could change the state of an association.  */
स्थिर अक्षर *स्थिर sctp_evttype_tbl[] = अणु
	"EVENT_T_unknown",
	"EVENT_T_CHUNK",
	"EVENT_T_TIMEOUT",
	"EVENT_T_OTHER",
	"EVENT_T_PRIMITIVE"
पूर्ण;

/* Return value of a state function */
स्थिर अक्षर *स्थिर sctp_status_tbl[] = अणु
	"DISPOSITION_DISCARD",
	"DISPOSITION_CONSUME",
	"DISPOSITION_NOMEM",
	"DISPOSITION_DELETE_TCB",
	"DISPOSITION_ABORT",
	"DISPOSITION_VIOLATION",
	"DISPOSITION_NOT_IMPL",
	"DISPOSITION_ERROR",
	"DISPOSITION_BUG"
पूर्ण;

/* Prपूर्णांकable क्रमms of primitives */
अटल स्थिर अक्षर *स्थिर sctp_primitive_tbl[SCTP_NUM_PRIMITIVE_TYPES] = अणु
	"PRIMITIVE_ASSOCIATE",
	"PRIMITIVE_SHUTDOWN",
	"PRIMITIVE_ABORT",
	"PRIMITIVE_SEND",
	"PRIMITIVE_REQUESTHEARTBEAT",
	"PRIMITIVE_ASCONF",
पूर्ण;

/* Lookup primitive debug name. */
स्थिर अक्षर *sctp_pname(स्थिर जोड़ sctp_subtype id)
अणु
	अगर (id.primitive <= SCTP_EVENT_PRIMITIVE_MAX)
		वापस sctp_primitive_tbl[id.primitive];
	वापस "unknown_primitive";
पूर्ण

अटल स्थिर अक्षर *स्थिर sctp_other_tbl[] = अणु
	"NO_PENDING_TSN",
	"ICMP_PROTO_UNREACH",
पूर्ण;

/* Lookup "other" debug name. */
स्थिर अक्षर *sctp_oname(स्थिर जोड़ sctp_subtype id)
अणु
	अगर (id.other <= SCTP_EVENT_OTHER_MAX)
		वापस sctp_other_tbl[id.other];
	वापस "unknown 'other' event";
पूर्ण

अटल स्थिर अक्षर *स्थिर sctp_समयr_tbl[] = अणु
	"TIMEOUT_NONE",
	"TIMEOUT_T1_COOKIE",
	"TIMEOUT_T1_INIT",
	"TIMEOUT_T2_SHUTDOWN",
	"TIMEOUT_T3_RTX",
	"TIMEOUT_T4_RTO",
	"TIMEOUT_T5_SHUTDOWN_GUARD",
	"TIMEOUT_HEARTBEAT",
	"TIMEOUT_RECONF",
	"TIMEOUT_SACK",
	"TIMEOUT_AUTOCLOSE",
पूर्ण;

/* Lookup समयr debug name. */
स्थिर अक्षर *sctp_tname(स्थिर जोड़ sctp_subtype id)
अणु
	BUILD_BUG_ON(SCTP_EVENT_TIMEOUT_MAX + 1 != ARRAY_SIZE(sctp_समयr_tbl));

	अगर (id.समयout < ARRAY_SIZE(sctp_समयr_tbl))
		वापस sctp_समयr_tbl[id.समयout];
	वापस "unknown_timer";
पूर्ण
