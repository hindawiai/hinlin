<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These are the state tables क्रम the SCTP state machine.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/skbuff.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

अटल स्थिर काष्ठा sctp_sm_table_entry
primitive_event_table[SCTP_NUM_PRIMITIVE_TYPES][SCTP_STATE_NUM_STATES];
अटल स्थिर काष्ठा sctp_sm_table_entry
other_event_table[SCTP_NUM_OTHER_TYPES][SCTP_STATE_NUM_STATES];
अटल स्थिर काष्ठा sctp_sm_table_entry
समयout_event_table[SCTP_NUM_TIMEOUT_TYPES][SCTP_STATE_NUM_STATES];

अटल स्थिर काष्ठा sctp_sm_table_entry *sctp_chunk_event_lookup(
						काष्ठा net *net,
						क्रमागत sctp_cid cid,
						क्रमागत sctp_state state);


अटल स्थिर काष्ठा sctp_sm_table_entry bug = अणु
	.fn = sctp_sf_bug,
	.name = "sctp_sf_bug"
पूर्ण;

#घोषणा DO_LOOKUP(_max, _type, _table)					\
(अणु									\
	स्थिर काष्ठा sctp_sm_table_entry *rtn;				\
									\
	अगर ((event_subtype._type > (_max))) अणु				\
		pr_warn("table %p possible attack: event %d exceeds max %d\n", \
			_table, event_subtype._type, _max);		\
		rtn = &bug;						\
	पूर्ण अन्यथा								\
		rtn = &_table[event_subtype._type][(पूर्णांक)state];		\
									\
	rtn;								\
पूर्ण)

स्थिर काष्ठा sctp_sm_table_entry *sctp_sm_lookup_event(
					काष्ठा net *net,
					क्रमागत sctp_event_type event_type,
					क्रमागत sctp_state state,
					जोड़ sctp_subtype event_subtype)
अणु
	चयन (event_type) अणु
	हाल SCTP_EVENT_T_CHUNK:
		वापस sctp_chunk_event_lookup(net, event_subtype.chunk, state);
	हाल SCTP_EVENT_T_TIMEOUT:
		वापस DO_LOOKUP(SCTP_EVENT_TIMEOUT_MAX, समयout,
				 समयout_event_table);
	हाल SCTP_EVENT_T_OTHER:
		वापस DO_LOOKUP(SCTP_EVENT_OTHER_MAX, other,
				 other_event_table);
	हाल SCTP_EVENT_T_PRIMITIVE:
		वापस DO_LOOKUP(SCTP_EVENT_PRIMITIVE_MAX, primitive,
				 primitive_event_table);
	शेष:
		/* Yikes!  We got an illegal event type.  */
		वापस &bug;
	पूर्ण
पूर्ण

#घोषणा TYPE_SCTP_FUNC(func) अणु.fn = func, .name = #funcपूर्ण

#घोषणा TYPE_SCTP_DATA अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_data_6_2), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_data_6_2), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_data_fast_4_4), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_DATA */

#घोषणा TYPE_SCTP_INIT अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_1B_init), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_1_siminit), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_1_siminit), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_2_dupinit), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_reshutack), \
पूर्ण /* TYPE_SCTP_INIT */

#घोषणा TYPE_SCTP_INIT_ACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_3_initack), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_1C_ack), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_INIT_ACK */

#घोषणा TYPE_SCTP_SACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_sack_6_2), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_SACK */

#घोषणा TYPE_SCTP_HEARTBEAT अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	/* This should not happen, but we are nice.  */ \
	TYPE_SCTP_FUNC(sctp_sf_beat_8_3), \
पूर्ण /* TYPE_SCTP_HEARTBEAT */

#घोषणा TYPE_SCTP_HEARTBEAT_ACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_violation), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_backbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_HEARTBEAT_ACK */

#घोषणा TYPE_SCTP_ABORT अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_pdiscard), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_रुको_पात), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_पात), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_1_पात), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_shutकरोwn_pending_पात), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutकरोwn_sent_पात), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_1_पात), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutकरोwn_ack_sent_पात), \
पूर्ण /* TYPE_SCTP_ABORT */

#घोषणा TYPE_SCTP_SHUTDOWN अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_shutकरोwn_ack), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_shut_ctsn), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_SHUTDOWN */

#घोषणा TYPE_SCTP_SHUTDOWN_ACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_8_5_1_E_sa), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_8_5_1_E_sa), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_violation), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_violation), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_final), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_violation), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_final), \
पूर्ण /* TYPE_SCTP_SHUTDOWN_ACK */

#घोषणा TYPE_SCTP_ERROR अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_err), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_operr_notअगरy), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_operr_notअगरy), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_operr_notअगरy), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_ERROR */

#घोषणा TYPE_SCTP_COOKIE_ECHO अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_1D_ce), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_2_4_dupcook), \
पूर्ण /* TYPE_SCTP_COOKIE_ECHO */

#घोषणा TYPE_SCTP_COOKIE_ACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_5_1E_ca), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_COOKIE_ACK */

#घोषणा TYPE_SCTP_ECN_ECNE अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecne), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecne), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecne), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecne), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecne), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_ECN_ECNE */

#घोषणा TYPE_SCTP_ECN_CWR अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecn_cwr), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecn_cwr), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_ecn_cwr), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_ECN_CWR */

#घोषणा TYPE_SCTP_SHUTDOWN_COMPLETE अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_4_C), \
पूर्ण /* TYPE_SCTP_SHUTDOWN_COMPLETE */

/* The primary index क्रम this table is the chunk type.
 * The secondary index क्रम this table is the state.
 *
 * For base protocol (RFC 2960).
 */
अटल स्थिर काष्ठा sctp_sm_table_entry
chunk_event_table[SCTP_NUM_BASE_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_DATA,
	TYPE_SCTP_INIT,
	TYPE_SCTP_INIT_ACK,
	TYPE_SCTP_SACK,
	TYPE_SCTP_HEARTBEAT,
	TYPE_SCTP_HEARTBEAT_ACK,
	TYPE_SCTP_ABORT,
	TYPE_SCTP_SHUTDOWN,
	TYPE_SCTP_SHUTDOWN_ACK,
	TYPE_SCTP_ERROR,
	TYPE_SCTP_COOKIE_ECHO,
	TYPE_SCTP_COOKIE_ACK,
	TYPE_SCTP_ECN_ECNE,
	TYPE_SCTP_ECN_CWR,
	TYPE_SCTP_SHUTDOWN_COMPLETE,
पूर्ण; /* state_fn_t chunk_event_table[][] */

#घोषणा TYPE_SCTP_ASCONF अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_ASCONF */

#घोषणा TYPE_SCTP_ASCONF_ACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_asconf_ack), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_ASCONF_ACK */

/* The primary index क्रम this table is the chunk type.
 * The secondary index क्रम this table is the state.
 */
अटल स्थिर काष्ठा sctp_sm_table_entry
addip_chunk_event_table[SCTP_NUM_ADDIP_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_ASCONF,
	TYPE_SCTP_ASCONF_ACK,
पूर्ण; /*state_fn_t addip_chunk_event_table[][] */

#घोषणा TYPE_SCTP_FWD_TSN अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_fwd_tsn), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_fwd_tsn), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_fwd_tsn_fast), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_FWD_TSN */

/* The primary index क्रम this table is the chunk type.
 * The secondary index क्रम this table is the state.
 */
अटल स्थिर काष्ठा sctp_sm_table_entry
prsctp_chunk_event_table[SCTP_NUM_PRSCTP_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_FWD_TSN,
पूर्ण; /*state_fn_t prsctp_chunk_event_table[][] */

#घोषणा TYPE_SCTP_RECONF अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_reconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_reconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
पूर्ण /* TYPE_SCTP_RECONF */

/* The primary index क्रम this table is the chunk type.
 * The secondary index क्रम this table is the state.
 */
अटल स्थिर काष्ठा sctp_sm_table_entry
reconf_chunk_event_table[SCTP_NUM_RECONF_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_RECONF,
पूर्ण; /*state_fn_t reconf_chunk_event_table[][] */

#घोषणा TYPE_SCTP_AUTH अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ootb), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_discard_chunk), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_eat_auth), \
पूर्ण /* TYPE_SCTP_AUTH */

/* The primary index क्रम this table is the chunk type.
 * The secondary index क्रम this table is the state.
 */
अटल स्थिर काष्ठा sctp_sm_table_entry
auth_chunk_event_table[SCTP_NUM_AUTH_CHUNK_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_AUTH,
पूर्ण; /*state_fn_t auth_chunk_event_table[][] */

अटल स्थिर काष्ठा sctp_sm_table_entry
chunk_event_table_unknown[SCTP_STATE_NUM_STATES] = अणु
	/* SCTP_STATE_CLOSED */
	TYPE_SCTP_FUNC(sctp_sf_ootb),
	/* SCTP_STATE_COOKIE_WAIT */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_COOKIE_ECHOED */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_ESTABLISHED */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_PENDING */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_SENT */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_RECEIVED */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */
	TYPE_SCTP_FUNC(sctp_sf_unk_chunk),
पूर्ण;	/* chunk unknown */


#घोषणा TYPE_SCTP_PRIMITIVE_ASSOCIATE  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_asoc), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_not_impl), \
पूर्ण /* TYPE_SCTP_PRIMITIVE_ASSOCIATE */

#घोषणा TYPE_SCTP_PRIMITIVE_SHUTDOWN  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_रुको_prm_shutकरोwn), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_prm_shutकरोwn),\
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_prm_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_primitive), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_primitive), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_primitive), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_primitive), \
पूर्ण /* TYPE_SCTP_PRIMITIVE_SHUTDOWN */

#घोषणा TYPE_SCTP_PRIMITIVE_ABORT  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_रुको_prm_पात), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_echoed_prm_पात), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_1_prm_पात), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_shutकरोwn_pending_prm_पात), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutकरोwn_sent_prm_पात), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_1_prm_पात), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_shutकरोwn_ack_sent_prm_पात), \
पूर्ण /* TYPE_SCTP_PRIMITIVE_ABORT */

#घोषणा TYPE_SCTP_PRIMITIVE_SEND  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_send), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_send), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_send), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_error_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_error_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_error_shutकरोwn), \
पूर्ण /* TYPE_SCTP_PRIMITIVE_SEND */

#घोषणा TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_requestheartbeat),          \
पूर्ण /* TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT */

#घोषणा TYPE_SCTP_PRIMITIVE_ASCONF अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_asconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_asconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_asconf), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_asconf), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_error_shutकरोwn), \
पूर्ण /* TYPE_SCTP_PRIMITIVE_ASCONF */

#घोषणा TYPE_SCTP_PRIMITIVE_RECONF अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_error_बंदd), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_reconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_reconf), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_reconf), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_prm_reconf), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_error_shutकरोwn), \
पूर्ण /* TYPE_SCTP_PRIMITIVE_RECONF */

/* The primary index क्रम this table is the primitive type.
 * The secondary index क्रम this table is the state.
 */
अटल स्थिर काष्ठा sctp_sm_table_entry
primitive_event_table[SCTP_NUM_PRIMITIVE_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_PRIMITIVE_ASSOCIATE,
	TYPE_SCTP_PRIMITIVE_SHUTDOWN,
	TYPE_SCTP_PRIMITIVE_ABORT,
	TYPE_SCTP_PRIMITIVE_SEND,
	TYPE_SCTP_PRIMITIVE_REQUESTHEARTBEAT,
	TYPE_SCTP_PRIMITIVE_ASCONF,
	TYPE_SCTP_PRIMITIVE_RECONF,
पूर्ण;

#घोषणा TYPE_SCTP_OTHER_NO_PENDING_TSN  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_no_pending_tsn), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_start_shutकरोwn), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_9_2_shutकरोwn_ack), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
पूर्ण

#घोषणा TYPE_SCTP_OTHER_ICMP_PROTO_UNREACH  अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_cookie_रुको_icmp_पात), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_ignore_other), \
पूर्ण

अटल स्थिर काष्ठा sctp_sm_table_entry
other_event_table[SCTP_NUM_OTHER_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_OTHER_NO_PENDING_TSN,
	TYPE_SCTP_OTHER_ICMP_PROTO_UNREACH,
पूर्ण;

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_NONE अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_bug), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_t1_cookie_समयr_expire), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_T1_INIT अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_t1_init_समयr_expire), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_t2_समयr_expire), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_t2_समयr_expire), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_T3_RTX अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_3_3_rtx), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_3_3_rtx), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_3_3_rtx), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_3_3_rtx), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_T4_RTO अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_t4_समयr_expire), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_t5_समयr_expire), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_t5_समयr_expire), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_HEARTBEAT अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_sendbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_sendbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_sendbeat_8_3), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_SACK अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_2_sack), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_2_sack), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_करो_6_2_sack), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_AUTOCLOSE अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_स्वतःबंद_समयr_expire), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

#घोषणा TYPE_SCTP_EVENT_TIMEOUT_RECONF अणु \
	/* SCTP_STATE_CLOSED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_WAIT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_COOKIE_ECHOED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_ESTABLISHED */ \
	TYPE_SCTP_FUNC(sctp_sf_send_reconf), \
	/* SCTP_STATE_SHUTDOWN_PENDING */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_RECEIVED */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
	/* SCTP_STATE_SHUTDOWN_ACK_SENT */ \
	TYPE_SCTP_FUNC(sctp_sf_समयr_ignore), \
पूर्ण

अटल स्थिर काष्ठा sctp_sm_table_entry
समयout_event_table[SCTP_NUM_TIMEOUT_TYPES][SCTP_STATE_NUM_STATES] = अणु
	TYPE_SCTP_EVENT_TIMEOUT_NONE,
	TYPE_SCTP_EVENT_TIMEOUT_T1_COOKIE,
	TYPE_SCTP_EVENT_TIMEOUT_T1_INIT,
	TYPE_SCTP_EVENT_TIMEOUT_T2_SHUTDOWN,
	TYPE_SCTP_EVENT_TIMEOUT_T3_RTX,
	TYPE_SCTP_EVENT_TIMEOUT_T4_RTO,
	TYPE_SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD,
	TYPE_SCTP_EVENT_TIMEOUT_HEARTBEAT,
	TYPE_SCTP_EVENT_TIMEOUT_RECONF,
	TYPE_SCTP_EVENT_TIMEOUT_SACK,
	TYPE_SCTP_EVENT_TIMEOUT_AUTOCLOSE,
पूर्ण;

अटल स्थिर काष्ठा sctp_sm_table_entry *sctp_chunk_event_lookup(
						काष्ठा net *net,
						क्रमागत sctp_cid cid,
						क्रमागत sctp_state state)
अणु
	अगर (state > SCTP_STATE_MAX)
		वापस &bug;

	अगर (cid == SCTP_CID_I_DATA)
		cid = SCTP_CID_DATA;

	अगर (cid <= SCTP_CID_BASE_MAX)
		वापस &chunk_event_table[cid][state];

	चयन ((u16)cid) अणु
	हाल SCTP_CID_FWD_TSN:
	हाल SCTP_CID_I_FWD_TSN:
		वापस &prsctp_chunk_event_table[0][state];

	हाल SCTP_CID_ASCONF:
		वापस &addip_chunk_event_table[0][state];

	हाल SCTP_CID_ASCONF_ACK:
		वापस &addip_chunk_event_table[1][state];

	हाल SCTP_CID_RECONF:
		वापस &reconf_chunk_event_table[0][state];

	हाल SCTP_CID_AUTH:
		वापस &auth_chunk_event_table[0][state];
	पूर्ण

	वापस &chunk_event_table_unknown[state];
पूर्ण
