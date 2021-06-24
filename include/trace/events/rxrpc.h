<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* AF_RXRPC tracepoपूर्णांकs
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rxrpc

#अगर !defined(_TRACE_RXRPC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RXRPC_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/errqueue.h>

/*
 * Define क्रमागतs क्रम tracing inक्रमmation.
 *
 * These should all be kept sorted, making it easier to match the string
 * mapping tables further on.
 */
#अगर_अघोषित __RXRPC_DECLARE_TRACE_ENUMS_ONCE_ONLY
#घोषणा __RXRPC_DECLARE_TRACE_ENUMS_ONCE_ONLY

क्रमागत rxrpc_skb_trace अणु
	rxrpc_skb_cleaned,
	rxrpc_skb_मुक्तd,
	rxrpc_skb_got,
	rxrpc_skb_lost,
	rxrpc_skb_new,
	rxrpc_skb_purged,
	rxrpc_skb_received,
	rxrpc_skb_rotated,
	rxrpc_skb_seen,
	rxrpc_skb_unshared,
	rxrpc_skb_unshared_nomem,
पूर्ण;

क्रमागत rxrpc_local_trace अणु
	rxrpc_local_got,
	rxrpc_local_new,
	rxrpc_local_processing,
	rxrpc_local_put,
	rxrpc_local_queued,
पूर्ण;

क्रमागत rxrpc_peer_trace अणु
	rxrpc_peer_got,
	rxrpc_peer_new,
	rxrpc_peer_processing,
	rxrpc_peer_put,
पूर्ण;

क्रमागत rxrpc_conn_trace अणु
	rxrpc_conn_got,
	rxrpc_conn_new_client,
	rxrpc_conn_new_service,
	rxrpc_conn_put_client,
	rxrpc_conn_put_service,
	rxrpc_conn_queued,
	rxrpc_conn_reap_service,
	rxrpc_conn_seen,
पूर्ण;

क्रमागत rxrpc_client_trace अणु
	rxrpc_client_activate_chans,
	rxrpc_client_alloc,
	rxrpc_client_chan_activate,
	rxrpc_client_chan_disconnect,
	rxrpc_client_chan_pass,
	rxrpc_client_chan_रुको_failed,
	rxrpc_client_cleanup,
	rxrpc_client_discard,
	rxrpc_client_duplicate,
	rxrpc_client_exposed,
	rxrpc_client_replace,
	rxrpc_client_to_active,
	rxrpc_client_to_idle,
पूर्ण;

क्रमागत rxrpc_call_trace अणु
	rxrpc_call_connected,
	rxrpc_call_error,
	rxrpc_call_got,
	rxrpc_call_got_kernel,
	rxrpc_call_got_userid,
	rxrpc_call_new_client,
	rxrpc_call_new_service,
	rxrpc_call_put,
	rxrpc_call_put_kernel,
	rxrpc_call_put_noqueue,
	rxrpc_call_put_userid,
	rxrpc_call_queued,
	rxrpc_call_queued_ref,
	rxrpc_call_release,
	rxrpc_call_seen,
पूर्ण;

क्रमागत rxrpc_transmit_trace अणु
	rxrpc_transmit_aरुको_reply,
	rxrpc_transmit_end,
	rxrpc_transmit_queue,
	rxrpc_transmit_queue_last,
	rxrpc_transmit_rotate,
	rxrpc_transmit_rotate_last,
	rxrpc_transmit_रुको,
पूर्ण;

क्रमागत rxrpc_receive_trace अणु
	rxrpc_receive_end,
	rxrpc_receive_front,
	rxrpc_receive_incoming,
	rxrpc_receive_queue,
	rxrpc_receive_queue_last,
	rxrpc_receive_rotate,
पूर्ण;

क्रमागत rxrpc_recvmsg_trace अणु
	rxrpc_recvmsg_cont,
	rxrpc_recvmsg_data_वापस,
	rxrpc_recvmsg_dequeue,
	rxrpc_recvmsg_enter,
	rxrpc_recvmsg_full,
	rxrpc_recvmsg_hole,
	rxrpc_recvmsg_next,
	rxrpc_recvmsg_requeue,
	rxrpc_recvmsg_वापस,
	rxrpc_recvmsg_terminal,
	rxrpc_recvmsg_to_be_accepted,
	rxrpc_recvmsg_रुको,
पूर्ण;

क्रमागत rxrpc_rtt_tx_trace अणु
	rxrpc_rtt_tx_cancel,
	rxrpc_rtt_tx_data,
	rxrpc_rtt_tx_no_slot,
	rxrpc_rtt_tx_ping,
पूर्ण;

क्रमागत rxrpc_rtt_rx_trace अणु
	rxrpc_rtt_rx_cancel,
	rxrpc_rtt_rx_lost,
	rxrpc_rtt_rx_obsolete,
	rxrpc_rtt_rx_ping_response,
	rxrpc_rtt_rx_requested_ack,
पूर्ण;

क्रमागत rxrpc_समयr_trace अणु
	rxrpc_समयr_begin,
	rxrpc_समयr_exp_ack,
	rxrpc_समयr_exp_hard,
	rxrpc_समयr_exp_idle,
	rxrpc_समयr_exp_keepalive,
	rxrpc_समयr_exp_lost_ack,
	rxrpc_समयr_exp_normal,
	rxrpc_समयr_exp_ping,
	rxrpc_समयr_exp_resend,
	rxrpc_समयr_expired,
	rxrpc_समयr_init_क्रम_reply,
	rxrpc_समयr_init_क्रम_send_reply,
	rxrpc_समयr_restart,
	rxrpc_समयr_set_क्रम_ack,
	rxrpc_समयr_set_क्रम_hard,
	rxrpc_समयr_set_क्रम_idle,
	rxrpc_समयr_set_क्रम_keepalive,
	rxrpc_समयr_set_क्रम_lost_ack,
	rxrpc_समयr_set_क्रम_normal,
	rxrpc_समयr_set_क्रम_ping,
	rxrpc_समयr_set_क्रम_resend,
	rxrpc_समयr_set_क्रम_send,
पूर्ण;

क्रमागत rxrpc_propose_ack_trace अणु
	rxrpc_propose_ack_client_tx_end,
	rxrpc_propose_ack_input_data,
	rxrpc_propose_ack_ping_क्रम_check_lअगरe,
	rxrpc_propose_ack_ping_क्रम_keepalive,
	rxrpc_propose_ack_ping_क्रम_lost_ack,
	rxrpc_propose_ack_ping_क्रम_lost_reply,
	rxrpc_propose_ack_ping_क्रम_params,
	rxrpc_propose_ack_processing_op,
	rxrpc_propose_ack_respond_to_ack,
	rxrpc_propose_ack_respond_to_ping,
	rxrpc_propose_ack_retry_tx,
	rxrpc_propose_ack_rotate_rx,
	rxrpc_propose_ack_terminal_ack,
पूर्ण;

क्रमागत rxrpc_propose_ack_outcome अणु
	rxrpc_propose_ack_subsume,
	rxrpc_propose_ack_update,
	rxrpc_propose_ack_use,
पूर्ण;

क्रमागत rxrpc_congest_change अणु
	rxrpc_cong_begin_retransmission,
	rxrpc_cong_cleared_nacks,
	rxrpc_cong_new_low_nack,
	rxrpc_cong_no_change,
	rxrpc_cong_progress,
	rxrpc_cong_retransmit_again,
	rxrpc_cong_rtt_winकरोw_end,
	rxrpc_cong_saw_nack,
पूर्ण;

क्रमागत rxrpc_tx_poपूर्णांक अणु
	rxrpc_tx_poपूर्णांक_call_पात,
	rxrpc_tx_poपूर्णांक_call_ack,
	rxrpc_tx_poपूर्णांक_call_data_frag,
	rxrpc_tx_poपूर्णांक_call_data_nofrag,
	rxrpc_tx_poपूर्णांक_call_final_resend,
	rxrpc_tx_poपूर्णांक_conn_पात,
	rxrpc_tx_poपूर्णांक_rxkad_challenge,
	rxrpc_tx_poपूर्णांक_rxkad_response,
	rxrpc_tx_poपूर्णांक_reject,
	rxrpc_tx_poपूर्णांक_version_keepalive,
	rxrpc_tx_poपूर्णांक_version_reply,
पूर्ण;

#पूर्ण_अगर /* end __RXRPC_DECLARE_TRACE_ENUMS_ONCE_ONLY */

/*
 * Declare tracing inक्रमmation क्रमागतs and their string mappings क्रम display.
 */
#घोषणा rxrpc_skb_traces \
	EM(rxrpc_skb_cleaned,			"CLN") \
	EM(rxrpc_skb_मुक्तd,			"FRE") \
	EM(rxrpc_skb_got,			"GOT") \
	EM(rxrpc_skb_lost,			"*L*") \
	EM(rxrpc_skb_new,			"NEW") \
	EM(rxrpc_skb_purged,			"PUR") \
	EM(rxrpc_skb_received,			"RCV") \
	EM(rxrpc_skb_rotated,			"ROT") \
	EM(rxrpc_skb_seen,			"SEE") \
	EM(rxrpc_skb_unshared,			"UNS") \
	E_(rxrpc_skb_unshared_nomem,		"US0")

#घोषणा rxrpc_local_traces \
	EM(rxrpc_local_got,			"GOT") \
	EM(rxrpc_local_new,			"NEW") \
	EM(rxrpc_local_processing,		"PRO") \
	EM(rxrpc_local_put,			"PUT") \
	E_(rxrpc_local_queued,			"QUE")

#घोषणा rxrpc_peer_traces \
	EM(rxrpc_peer_got,			"GOT") \
	EM(rxrpc_peer_new,			"NEW") \
	EM(rxrpc_peer_processing,		"PRO") \
	E_(rxrpc_peer_put,			"PUT")

#घोषणा rxrpc_conn_traces \
	EM(rxrpc_conn_got,			"GOT") \
	EM(rxrpc_conn_new_client,		"NWc") \
	EM(rxrpc_conn_new_service,		"NWs") \
	EM(rxrpc_conn_put_client,		"PTc") \
	EM(rxrpc_conn_put_service,		"PTs") \
	EM(rxrpc_conn_queued,			"QUE") \
	EM(rxrpc_conn_reap_service,		"RPs") \
	E_(rxrpc_conn_seen,			"SEE")

#घोषणा rxrpc_client_traces \
	EM(rxrpc_client_activate_chans,		"Activa") \
	EM(rxrpc_client_alloc,			"Alloc ") \
	EM(rxrpc_client_chan_activate,		"ChActv") \
	EM(rxrpc_client_chan_disconnect,	"ChDisc") \
	EM(rxrpc_client_chan_pass,		"ChPass") \
	EM(rxrpc_client_chan_रुको_failed,	"ChWtFl") \
	EM(rxrpc_client_cleanup,		"Clean ") \
	EM(rxrpc_client_discard,		"Discar") \
	EM(rxrpc_client_duplicate,		"Duplic") \
	EM(rxrpc_client_exposed,		"Expose") \
	EM(rxrpc_client_replace,		"Replac") \
	EM(rxrpc_client_to_active,		"->Actv") \
	E_(rxrpc_client_to_idle,		"->Idle")

#घोषणा rxrpc_call_traces \
	EM(rxrpc_call_connected,		"CON") \
	EM(rxrpc_call_error,			"*E*") \
	EM(rxrpc_call_got,			"GOT") \
	EM(rxrpc_call_got_kernel,		"Gke") \
	EM(rxrpc_call_got_userid,		"Gus") \
	EM(rxrpc_call_new_client,		"NWc") \
	EM(rxrpc_call_new_service,		"NWs") \
	EM(rxrpc_call_put,			"PUT") \
	EM(rxrpc_call_put_kernel,		"Pke") \
	EM(rxrpc_call_put_noqueue,		"PNQ") \
	EM(rxrpc_call_put_userid,		"Pus") \
	EM(rxrpc_call_queued,			"QUE") \
	EM(rxrpc_call_queued_ref,		"QUR") \
	EM(rxrpc_call_release,			"RLS") \
	E_(rxrpc_call_seen,			"SEE")

#घोषणा rxrpc_transmit_traces \
	EM(rxrpc_transmit_aरुको_reply,		"AWR") \
	EM(rxrpc_transmit_end,			"END") \
	EM(rxrpc_transmit_queue,		"QUE") \
	EM(rxrpc_transmit_queue_last,		"QLS") \
	EM(rxrpc_transmit_rotate,		"ROT") \
	EM(rxrpc_transmit_rotate_last,		"RLS") \
	E_(rxrpc_transmit_रुको,			"WAI")

#घोषणा rxrpc_receive_traces \
	EM(rxrpc_receive_end,			"END") \
	EM(rxrpc_receive_front,			"FRN") \
	EM(rxrpc_receive_incoming,		"INC") \
	EM(rxrpc_receive_queue,			"QUE") \
	EM(rxrpc_receive_queue_last,		"QLS") \
	E_(rxrpc_receive_rotate,		"ROT")

#घोषणा rxrpc_recvmsg_traces \
	EM(rxrpc_recvmsg_cont,			"CONT") \
	EM(rxrpc_recvmsg_data_वापस,		"DATA") \
	EM(rxrpc_recvmsg_dequeue,		"DEQU") \
	EM(rxrpc_recvmsg_enter,			"ENTR") \
	EM(rxrpc_recvmsg_full,			"FULL") \
	EM(rxrpc_recvmsg_hole,			"HOLE") \
	EM(rxrpc_recvmsg_next,			"NEXT") \
	EM(rxrpc_recvmsg_requeue,		"REQU") \
	EM(rxrpc_recvmsg_वापस,		"RETN") \
	EM(rxrpc_recvmsg_terminal,		"TERM") \
	EM(rxrpc_recvmsg_to_be_accepted,	"TBAC") \
	E_(rxrpc_recvmsg_रुको,			"WAIT")

#घोषणा rxrpc_rtt_tx_traces \
	EM(rxrpc_rtt_tx_cancel,			"CNCE") \
	EM(rxrpc_rtt_tx_data,			"DATA") \
	EM(rxrpc_rtt_tx_no_slot,		"FULL") \
	E_(rxrpc_rtt_tx_ping,			"PING")

#घोषणा rxrpc_rtt_rx_traces \
	EM(rxrpc_rtt_rx_cancel,			"CNCL") \
	EM(rxrpc_rtt_rx_obsolete,		"OBSL") \
	EM(rxrpc_rtt_rx_lost,			"LOST") \
	EM(rxrpc_rtt_rx_ping_response,		"PONG") \
	E_(rxrpc_rtt_rx_requested_ack,		"RACK")

#घोषणा rxrpc_समयr_traces \
	EM(rxrpc_समयr_begin,			"Begin ") \
	EM(rxrpc_समयr_expired,			"*EXPR*") \
	EM(rxrpc_समयr_exp_ack,			"ExpAck") \
	EM(rxrpc_समयr_exp_hard,		"ExpHrd") \
	EM(rxrpc_समयr_exp_idle,		"ExpIdl") \
	EM(rxrpc_समयr_exp_keepalive,		"ExpKA ") \
	EM(rxrpc_समयr_exp_lost_ack,		"ExpLoA") \
	EM(rxrpc_समयr_exp_normal,		"ExpNml") \
	EM(rxrpc_समयr_exp_ping,		"ExpPng") \
	EM(rxrpc_समयr_exp_resend,		"ExpRsn") \
	EM(rxrpc_समयr_init_क्रम_reply,		"IniRpl") \
	EM(rxrpc_समयr_init_क्रम_send_reply,	"SndRpl") \
	EM(rxrpc_समयr_restart,			"Restrt") \
	EM(rxrpc_समयr_set_क्रम_ack,		"SetAck") \
	EM(rxrpc_समयr_set_क्रम_hard,		"SetHrd") \
	EM(rxrpc_समयr_set_क्रम_idle,		"SetIdl") \
	EM(rxrpc_समयr_set_क्रम_keepalive,	"KeepAl") \
	EM(rxrpc_समयr_set_क्रम_lost_ack,	"SetLoA") \
	EM(rxrpc_समयr_set_क्रम_normal,		"SetNml") \
	EM(rxrpc_समयr_set_क्रम_ping,		"SetPng") \
	EM(rxrpc_समयr_set_क्रम_resend,		"SetRTx") \
	E_(rxrpc_समयr_set_क्रम_send,		"SetSnd")

#घोषणा rxrpc_propose_ack_traces \
	EM(rxrpc_propose_ack_client_tx_end,	"ClTxEnd") \
	EM(rxrpc_propose_ack_input_data,	"DataIn ") \
	EM(rxrpc_propose_ack_ping_क्रम_check_lअगरe, "ChkLife") \
	EM(rxrpc_propose_ack_ping_क्रम_keepalive, "KeepAlv") \
	EM(rxrpc_propose_ack_ping_क्रम_lost_ack,	"LostAck") \
	EM(rxrpc_propose_ack_ping_क्रम_lost_reply, "LostRpl") \
	EM(rxrpc_propose_ack_ping_क्रम_params,	"Params ") \
	EM(rxrpc_propose_ack_processing_op,	"ProcOp ") \
	EM(rxrpc_propose_ack_respond_to_ack,	"Rsp2Ack") \
	EM(rxrpc_propose_ack_respond_to_ping,	"Rsp2Png") \
	EM(rxrpc_propose_ack_retry_tx,		"RetryTx") \
	EM(rxrpc_propose_ack_rotate_rx,		"RxAck  ") \
	E_(rxrpc_propose_ack_terminal_ack,	"ClTerm ")

#घोषणा rxrpc_propose_ack_outcomes \
	EM(rxrpc_propose_ack_subsume,		" Subsume") \
	EM(rxrpc_propose_ack_update,		" Update") \
	E_(rxrpc_propose_ack_use,		" New")

#घोषणा rxrpc_congest_modes \
	EM(RXRPC_CALL_CONGEST_AVOIDANCE,	"CongAvoid") \
	EM(RXRPC_CALL_FAST_RETRANSMIT,		"FastReTx ") \
	EM(RXRPC_CALL_PACKET_LOSS,		"PktLoss  ") \
	E_(RXRPC_CALL_SLOW_START,		"SlowStart")

#घोषणा rxrpc_congest_changes \
	EM(rxrpc_cong_begin_retransmission,	" Retrans") \
	EM(rxrpc_cong_cleared_nacks,		" Cleared") \
	EM(rxrpc_cong_new_low_nack,		" NewLowN") \
	EM(rxrpc_cong_no_change,		" -") \
	EM(rxrpc_cong_progress,			" Progres") \
	EM(rxrpc_cong_retransmit_again,		" ReTxAgn") \
	EM(rxrpc_cong_rtt_winकरोw_end,		" RttWinE") \
	E_(rxrpc_cong_saw_nack,			" SawNack")

#घोषणा rxrpc_pkts \
	EM(0,					"?00") \
	EM(RXRPC_PACKET_TYPE_DATA,		"DATA") \
	EM(RXRPC_PACKET_TYPE_ACK,		"ACK") \
	EM(RXRPC_PACKET_TYPE_BUSY,		"BUSY") \
	EM(RXRPC_PACKET_TYPE_ABORT,		"ABORT") \
	EM(RXRPC_PACKET_TYPE_ACKALL,		"ACKALL") \
	EM(RXRPC_PACKET_TYPE_CHALLENGE,		"CHALL") \
	EM(RXRPC_PACKET_TYPE_RESPONSE,		"RESP") \
	EM(RXRPC_PACKET_TYPE_DEBUG,		"DEBUG") \
	EM(9,					"?09") \
	EM(10,					"?10") \
	EM(11,					"?11") \
	EM(12,					"?12") \
	EM(RXRPC_PACKET_TYPE_VERSION,		"VERSION") \
	EM(14,					"?14") \
	E_(15,					"?15")

#घोषणा rxrpc_ack_names \
	EM(0,					"-0-") \
	EM(RXRPC_ACK_REQUESTED,			"REQ") \
	EM(RXRPC_ACK_DUPLICATE,			"DUP") \
	EM(RXRPC_ACK_OUT_OF_SEQUENCE,		"OOS") \
	EM(RXRPC_ACK_EXCEEDS_WINDOW,		"WIN") \
	EM(RXRPC_ACK_NOSPACE,			"MEM") \
	EM(RXRPC_ACK_PING,			"PNG") \
	EM(RXRPC_ACK_PING_RESPONSE,		"PNR") \
	EM(RXRPC_ACK_DELAY,			"DLY") \
	EM(RXRPC_ACK_IDLE,			"IDL") \
	E_(RXRPC_ACK__INVALID,			"-?-")

#घोषणा rxrpc_completions \
	EM(RXRPC_CALL_SUCCEEDED,		"Succeeded") \
	EM(RXRPC_CALL_REMOTELY_ABORTED,		"RemoteAbort") \
	EM(RXRPC_CALL_LOCALLY_ABORTED,		"LocalAbort") \
	EM(RXRPC_CALL_LOCAL_ERROR,		"LocalError") \
	E_(RXRPC_CALL_NETWORK_ERROR,		"NetError")

#घोषणा rxrpc_tx_poपूर्णांकs \
	EM(rxrpc_tx_poपूर्णांक_call_पात,		"CallAbort") \
	EM(rxrpc_tx_poपूर्णांक_call_ack,		"CallAck") \
	EM(rxrpc_tx_poपूर्णांक_call_data_frag,	"CallDataFrag") \
	EM(rxrpc_tx_poपूर्णांक_call_data_nofrag,	"CallDataNofrag") \
	EM(rxrpc_tx_poपूर्णांक_call_final_resend,	"CallFinalResend") \
	EM(rxrpc_tx_poपूर्णांक_conn_पात,		"ConnAbort") \
	EM(rxrpc_tx_poपूर्णांक_reject,		"Reject") \
	EM(rxrpc_tx_poपूर्णांक_rxkad_challenge,	"RxkadChall") \
	EM(rxrpc_tx_poपूर्णांक_rxkad_response,	"RxkadResp") \
	EM(rxrpc_tx_poपूर्णांक_version_keepalive,	"VerKeepalive") \
	E_(rxrpc_tx_poपूर्णांक_version_reply,	"VerReply")

/*
 * Export क्रमागत symbols via userspace.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b) TRACE_DEFINE_ENUM(a);
#घोषणा E_(a, b) TRACE_DEFINE_ENUM(a);

rxrpc_skb_traces;
rxrpc_local_traces;
rxrpc_conn_traces;
rxrpc_client_traces;
rxrpc_call_traces;
rxrpc_transmit_traces;
rxrpc_receive_traces;
rxrpc_recvmsg_traces;
rxrpc_rtt_tx_traces;
rxrpc_rtt_rx_traces;
rxrpc_समयr_traces;
rxrpc_propose_ack_traces;
rxrpc_propose_ack_outcomes;
rxrpc_congest_modes;
rxrpc_congest_changes;
rxrpc_tx_poपूर्णांकs;

/*
 * Now redefine the EM() and E_() macros to map the क्रमागतs to the strings that
 * will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b)	अणु a, b पूर्ण,
#घोषणा E_(a, b)	अणु a, b पूर्ण

TRACE_EVENT(rxrpc_local,
	    TP_PROTO(अचिन्हित पूर्णांक local_debug_id, क्रमागत rxrpc_local_trace op,
		     पूर्णांक usage, स्थिर व्योम *where),

	    TP_ARGS(local_debug_id, op, usage, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,	local		)
		    __field(पूर्णांक,		op		)
		    __field(पूर्णांक,		usage		)
		    __field(स्थिर व्योम *,	where		)
			     ),

	    TP_fast_assign(
		    __entry->local = local_debug_id;
		    __entry->op = op;
		    __entry->usage = usage;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("L=%08x %s u=%d sp=%pSR",
		      __entry->local,
		      __prपूर्णांक_symbolic(__entry->op, rxrpc_local_traces),
		      __entry->usage,
		      __entry->where)
	    );

TRACE_EVENT(rxrpc_peer,
	    TP_PROTO(अचिन्हित पूर्णांक peer_debug_id, क्रमागत rxrpc_peer_trace op,
		     पूर्णांक usage, स्थिर व्योम *where),

	    TP_ARGS(peer_debug_id, op, usage, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,	peer		)
		    __field(पूर्णांक,		op		)
		    __field(पूर्णांक,		usage		)
		    __field(स्थिर व्योम *,	where		)
			     ),

	    TP_fast_assign(
		    __entry->peer = peer_debug_id;
		    __entry->op = op;
		    __entry->usage = usage;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("P=%08x %s u=%d sp=%pSR",
		      __entry->peer,
		      __prपूर्णांक_symbolic(__entry->op, rxrpc_peer_traces),
		      __entry->usage,
		      __entry->where)
	    );

TRACE_EVENT(rxrpc_conn,
	    TP_PROTO(अचिन्हित पूर्णांक conn_debug_id, क्रमागत rxrpc_conn_trace op,
		     पूर्णांक usage, स्थिर व्योम *where),

	    TP_ARGS(conn_debug_id, op, usage, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,	conn		)
		    __field(पूर्णांक,		op		)
		    __field(पूर्णांक,		usage		)
		    __field(स्थिर व्योम *,	where		)
			     ),

	    TP_fast_assign(
		    __entry->conn = conn_debug_id;
		    __entry->op = op;
		    __entry->usage = usage;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("C=%08x %s u=%d sp=%pSR",
		      __entry->conn,
		      __prपूर्णांक_symbolic(__entry->op, rxrpc_conn_traces),
		      __entry->usage,
		      __entry->where)
	    );

TRACE_EVENT(rxrpc_client,
	    TP_PROTO(काष्ठा rxrpc_connection *conn, पूर्णांक channel,
		     क्रमागत rxrpc_client_trace op),

	    TP_ARGS(conn, channel, op),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		conn		)
		    __field(u32,			cid		)
		    __field(पूर्णांक,			channel		)
		    __field(पूर्णांक,			usage		)
		    __field(क्रमागत rxrpc_client_trace,	op		)
			     ),

	    TP_fast_assign(
		    __entry->conn = conn ? conn->debug_id : 0;
		    __entry->channel = channel;
		    __entry->usage = conn ? atomic_पढ़ो(&conn->usage) : -2;
		    __entry->op = op;
		    __entry->cid = conn ? conn->proto.cid : 0;
			   ),

	    TP_prपूर्णांकk("C=%08x h=%2d %s i=%08x u=%d",
		      __entry->conn,
		      __entry->channel,
		      __prपूर्णांक_symbolic(__entry->op, rxrpc_client_traces),
		      __entry->cid,
		      __entry->usage)
	    );

TRACE_EVENT(rxrpc_call,
	    TP_PROTO(अचिन्हित पूर्णांक call_debug_id, क्रमागत rxrpc_call_trace op,
		     पूर्णांक usage, स्थिर व्योम *where, स्थिर व्योम *aux),

	    TP_ARGS(call_debug_id, op, usage, where, aux),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(पूर्णांक,			op		)
		    __field(पूर्णांक,			usage		)
		    __field(स्थिर व्योम *,		where		)
		    __field(स्थिर व्योम *,		aux		)
			     ),

	    TP_fast_assign(
		    __entry->call = call_debug_id;
		    __entry->op = op;
		    __entry->usage = usage;
		    __entry->where = where;
		    __entry->aux = aux;
			   ),

	    TP_prपूर्णांकk("c=%08x %s u=%d sp=%pSR a=%p",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->op, rxrpc_call_traces),
		      __entry->usage,
		      __entry->where,
		      __entry->aux)
	    );

TRACE_EVENT(rxrpc_skb,
	    TP_PROTO(काष्ठा sk_buff *skb, क्रमागत rxrpc_skb_trace op,
		     पूर्णांक usage, पूर्णांक mod_count, u8 flags,    स्थिर व्योम *where),

	    TP_ARGS(skb, op, usage, mod_count, flags, where),

	    TP_STRUCT__entry(
		    __field(काष्ठा sk_buff *,		skb		)
		    __field(क्रमागत rxrpc_skb_trace,	op		)
		    __field(u8,				flags		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			mod_count	)
		    __field(स्थिर व्योम *,		where		)
			     ),

	    TP_fast_assign(
		    __entry->skb = skb;
		    __entry->flags = flags;
		    __entry->op = op;
		    __entry->usage = usage;
		    __entry->mod_count = mod_count;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("s=%p %cx %s u=%d m=%d p=%pSR",
		      __entry->skb,
		      __entry->flags & RXRPC_SKB_TX_BUFFER ? 'T' : 'R',
		      __prपूर्णांक_symbolic(__entry->op, rxrpc_skb_traces),
		      __entry->usage,
		      __entry->mod_count,
		      __entry->where)
	    );

TRACE_EVENT(rxrpc_rx_packet,
	    TP_PROTO(काष्ठा rxrpc_skb_priv *sp),

	    TP_ARGS(sp),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा rxrpc_host_header,	hdr		)
			     ),

	    TP_fast_assign(
		    स_नकल(&__entry->hdr, &sp->hdr, माप(__entry->hdr));
			   ),

	    TP_prपूर्णांकk("%08x:%08x:%08x:%04x %08x %08x %02x %02x %s",
		      __entry->hdr.epoch, __entry->hdr.cid,
		      __entry->hdr.callNumber, __entry->hdr.serviceId,
		      __entry->hdr.serial, __entry->hdr.seq,
		      __entry->hdr.type, __entry->hdr.flags,
		      __entry->hdr.type <= 15 ?
		      __prपूर्णांक_symbolic(__entry->hdr.type, rxrpc_pkts) : "?UNK")
	    );

TRACE_EVENT(rxrpc_rx_करोne,
	    TP_PROTO(पूर्णांक result, पूर्णांक पात_code),

	    TP_ARGS(result, पात_code),

	    TP_STRUCT__entry(
		    __field(पूर्णांक,			result		)
		    __field(पूर्णांक,			पात_code	)
			     ),

	    TP_fast_assign(
		    __entry->result = result;
		    __entry->पात_code = पात_code;
			   ),

	    TP_prपूर्णांकk("r=%d a=%d", __entry->result, __entry->पात_code)
	    );

TRACE_EVENT(rxrpc_पात,
	    TP_PROTO(अचिन्हित पूर्णांक call_nr, स्थिर अक्षर *why, u32 cid, u32 call_id,
		     rxrpc_seq_t seq, पूर्णांक पात_code, पूर्णांक error),

	    TP_ARGS(call_nr, why, cid, call_id, seq, पात_code, error),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call_nr		)
		    __array(अक्षर,			why, 4		)
		    __field(u32,			cid		)
		    __field(u32,			call_id		)
		    __field(rxrpc_seq_t,		seq		)
		    __field(पूर्णांक,			पात_code	)
		    __field(पूर्णांक,			error		)
			     ),

	    TP_fast_assign(
		    स_नकल(__entry->why, why, 4);
		    __entry->call_nr = call_nr;
		    __entry->cid = cid;
		    __entry->call_id = call_id;
		    __entry->पात_code = पात_code;
		    __entry->error = error;
		    __entry->seq = seq;
			   ),

	    TP_prपूर्णांकk("c=%08x %08x:%08x s=%u a=%d e=%d %s",
		      __entry->call_nr,
		      __entry->cid, __entry->call_id, __entry->seq,
		      __entry->पात_code, __entry->error, __entry->why)
	    );

TRACE_EVENT(rxrpc_call_complete,
	    TP_PROTO(काष्ठा rxrpc_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत rxrpc_call_completion,	compl		)
		    __field(पूर्णांक,			error		)
		    __field(u32,			पात_code	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->compl = call->completion;
		    __entry->error = call->error;
		    __entry->पात_code = call->पात_code;
			   ),

	    TP_prपूर्णांकk("c=%08x %s r=%d ac=%d",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->compl, rxrpc_completions),
		      __entry->error,
		      __entry->पात_code)
	    );

TRACE_EVENT(rxrpc_transmit,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_transmit_trace why),

	    TP_ARGS(call, why),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत rxrpc_transmit_trace,	why		)
		    __field(rxrpc_seq_t,		tx_hard_ack	)
		    __field(rxrpc_seq_t,		tx_top		)
		    __field(पूर्णांक,			tx_winsize	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->why = why;
		    __entry->tx_hard_ack = call->tx_hard_ack;
		    __entry->tx_top = call->tx_top;
		    __entry->tx_winsize = call->tx_winsize;
			   ),

	    TP_prपूर्णांकk("c=%08x %s f=%08x n=%u/%u",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_transmit_traces),
		      __entry->tx_hard_ack + 1,
		      __entry->tx_top - __entry->tx_hard_ack,
		      __entry->tx_winsize)
	    );

TRACE_EVENT(rxrpc_rx_data,
	    TP_PROTO(अचिन्हित पूर्णांक call, rxrpc_seq_t seq,
		     rxrpc_serial_t serial, u8 flags, u8 anno),

	    TP_ARGS(call, seq, serial, flags, anno),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_seq_t,		seq		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(u8,				flags		)
		    __field(u8,				anno		)
			     ),

	    TP_fast_assign(
		    __entry->call = call;
		    __entry->seq = seq;
		    __entry->serial = serial;
		    __entry->flags = flags;
		    __entry->anno = anno;
			   ),

	    TP_prपूर्णांकk("c=%08x DATA %08x q=%08x fl=%02x a=%02x",
		      __entry->call,
		      __entry->serial,
		      __entry->seq,
		      __entry->flags,
		      __entry->anno)
	    );

TRACE_EVENT(rxrpc_rx_ack,
	    TP_PROTO(काष्ठा rxrpc_call *call,
		     rxrpc_serial_t serial, rxrpc_serial_t ack_serial,
		     rxrpc_seq_t first, rxrpc_seq_t prev, u8 reason, u8 n_acks),

	    TP_ARGS(call, serial, ack_serial, first, prev, reason, n_acks),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(rxrpc_serial_t,		ack_serial	)
		    __field(rxrpc_seq_t,		first		)
		    __field(rxrpc_seq_t,		prev		)
		    __field(u8,				reason		)
		    __field(u8,				n_acks		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->serial = serial;
		    __entry->ack_serial = ack_serial;
		    __entry->first = first;
		    __entry->prev = prev;
		    __entry->reason = reason;
		    __entry->n_acks = n_acks;
			   ),

	    TP_prपूर्णांकk("c=%08x %08x %s r=%08x f=%08x p=%08x n=%u",
		      __entry->call,
		      __entry->serial,
		      __prपूर्णांक_symbolic(__entry->reason, rxrpc_ack_names),
		      __entry->ack_serial,
		      __entry->first,
		      __entry->prev,
		      __entry->n_acks)
	    );

TRACE_EVENT(rxrpc_rx_पात,
	    TP_PROTO(काष्ठा rxrpc_call *call, rxrpc_serial_t serial,
		     u32 पात_code),

	    TP_ARGS(call, serial, पात_code),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(u32,			पात_code	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->serial = serial;
		    __entry->पात_code = पात_code;
			   ),

	    TP_prपूर्णांकk("c=%08x ABORT %08x ac=%d",
		      __entry->call,
		      __entry->serial,
		      __entry->पात_code)
	    );

TRACE_EVENT(rxrpc_rx_rwind_change,
	    TP_PROTO(काष्ठा rxrpc_call *call, rxrpc_serial_t serial,
		     u32 rwind, bool wake),

	    TP_ARGS(call, serial, rwind, wake),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(u32,			rwind		)
		    __field(bool,			wake		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->serial = serial;
		    __entry->rwind = rwind;
		    __entry->wake = wake;
			   ),

	    TP_prपूर्णांकk("c=%08x %08x rw=%u%s",
		      __entry->call,
		      __entry->serial,
		      __entry->rwind,
		      __entry->wake ? " wake" : "")
	    );

TRACE_EVENT(rxrpc_tx_packet,
	    TP_PROTO(अचिन्हित पूर्णांक call_id, काष्ठा rxrpc_wire_header *whdr,
		     क्रमागत rxrpc_tx_poपूर्णांक where),

	    TP_ARGS(call_id, whdr, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			call	)
		    __field(क्रमागत rxrpc_tx_poपूर्णांक,		where	)
		    __field_काष्ठा(काष्ठा rxrpc_wire_header,	whdr	)
			     ),

	    TP_fast_assign(
		    __entry->call = call_id;
		    स_नकल(&__entry->whdr, whdr, माप(__entry->whdr));
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("c=%08x %08x:%08x:%08x:%04x %08x %08x %02x %02x %s %s",
		      __entry->call,
		      ntohl(__entry->whdr.epoch),
		      ntohl(__entry->whdr.cid),
		      ntohl(__entry->whdr.callNumber),
		      ntohs(__entry->whdr.serviceId),
		      ntohl(__entry->whdr.serial),
		      ntohl(__entry->whdr.seq),
		      __entry->whdr.type, __entry->whdr.flags,
		      __entry->whdr.type <= 15 ?
		      __prपूर्णांक_symbolic(__entry->whdr.type, rxrpc_pkts) : "?UNK",
		      __prपूर्णांक_symbolic(__entry->where, rxrpc_tx_poपूर्णांकs))
	    );

TRACE_EVENT(rxrpc_tx_data,
	    TP_PROTO(काष्ठा rxrpc_call *call, rxrpc_seq_t seq,
		     rxrpc_serial_t serial, u8 flags, bool retrans, bool lose),

	    TP_ARGS(call, seq, serial, flags, retrans, lose),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_seq_t,		seq		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(u32,			cid		)
		    __field(u32,			call_id		)
		    __field(u8,				flags		)
		    __field(bool,			retrans		)
		    __field(bool,			lose		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->cid = call->cid;
		    __entry->call_id = call->call_id;
		    __entry->seq = seq;
		    __entry->serial = serial;
		    __entry->flags = flags;
		    __entry->retrans = retrans;
		    __entry->lose = lose;
			   ),

	    TP_prपूर्णांकk("c=%08x DATA %08x:%08x %08x q=%08x fl=%02x%s%s",
		      __entry->call,
		      __entry->cid,
		      __entry->call_id,
		      __entry->serial,
		      __entry->seq,
		      __entry->flags,
		      __entry->retrans ? " *RETRANS*" : "",
		      __entry->lose ? " *LOSE*" : "")
	    );

TRACE_EVENT(rxrpc_tx_ack,
	    TP_PROTO(अचिन्हित पूर्णांक call, rxrpc_serial_t serial,
		     rxrpc_seq_t ack_first, rxrpc_serial_t ack_serial,
		     u8 reason, u8 n_acks),

	    TP_ARGS(call, serial, ack_first, ack_serial, reason, n_acks),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(rxrpc_seq_t,		ack_first	)
		    __field(rxrpc_serial_t,		ack_serial	)
		    __field(u8,				reason		)
		    __field(u8,				n_acks		)
			     ),

	    TP_fast_assign(
		    __entry->call = call;
		    __entry->serial = serial;
		    __entry->ack_first = ack_first;
		    __entry->ack_serial = ack_serial;
		    __entry->reason = reason;
		    __entry->n_acks = n_acks;
			   ),

	    TP_prपूर्णांकk(" c=%08x ACK  %08x %s f=%08x r=%08x n=%u",
		      __entry->call,
		      __entry->serial,
		      __prपूर्णांक_symbolic(__entry->reason, rxrpc_ack_names),
		      __entry->ack_first,
		      __entry->ack_serial,
		      __entry->n_acks)
	    );

TRACE_EVENT(rxrpc_receive,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_receive_trace why,
		     rxrpc_serial_t serial, rxrpc_seq_t seq),

	    TP_ARGS(call, why, serial, seq),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत rxrpc_receive_trace,	why		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(rxrpc_seq_t,		seq		)
		    __field(rxrpc_seq_t,		hard_ack	)
		    __field(rxrpc_seq_t,		top		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->why = why;
		    __entry->serial = serial;
		    __entry->seq = seq;
		    __entry->hard_ack = call->rx_hard_ack;
		    __entry->top = call->rx_top;
			   ),

	    TP_prपूर्णांकk("c=%08x %s r=%08x q=%08x w=%08x-%08x",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_receive_traces),
		      __entry->serial,
		      __entry->seq,
		      __entry->hard_ack,
		      __entry->top)
	    );

TRACE_EVENT(rxrpc_recvmsg,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_recvmsg_trace why,
		     rxrpc_seq_t seq, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
		     पूर्णांक ret),

	    TP_ARGS(call, why, seq, offset, len, ret),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत rxrpc_recvmsg_trace,	why		)
		    __field(rxrpc_seq_t,		seq		)
		    __field(अचिन्हित पूर्णांक,		offset		)
		    __field(अचिन्हित पूर्णांक,		len		)
		    __field(पूर्णांक,			ret		)
			     ),

	    TP_fast_assign(
		    __entry->call = call ? call->debug_id : 0;
		    __entry->why = why;
		    __entry->seq = seq;
		    __entry->offset = offset;
		    __entry->len = len;
		    __entry->ret = ret;
			   ),

	    TP_prपूर्णांकk("c=%08x %s q=%08x o=%u l=%u ret=%d",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_recvmsg_traces),
		      __entry->seq,
		      __entry->offset,
		      __entry->len,
		      __entry->ret)
	    );

TRACE_EVENT(rxrpc_rtt_tx,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_rtt_tx_trace why,
		     पूर्णांक slot, rxrpc_serial_t send_serial),

	    TP_ARGS(call, why, slot, send_serial),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत rxrpc_rtt_tx_trace,	why		)
		    __field(पूर्णांक,			slot		)
		    __field(rxrpc_serial_t,		send_serial	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->why = why;
		    __entry->slot = slot;
		    __entry->send_serial = send_serial;
			   ),

	    TP_prपूर्णांकk("c=%08x [%d] %s sr=%08x",
		      __entry->call,
		      __entry->slot,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_rtt_tx_traces),
		      __entry->send_serial)
	    );

TRACE_EVENT(rxrpc_rtt_rx,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_rtt_rx_trace why,
		     पूर्णांक slot,
		     rxrpc_serial_t send_serial, rxrpc_serial_t resp_serial,
		     u32 rtt, u32 rto),

	    TP_ARGS(call, why, slot, send_serial, resp_serial, rtt, rto),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत rxrpc_rtt_rx_trace,	why		)
		    __field(पूर्णांक,			slot		)
		    __field(rxrpc_serial_t,		send_serial	)
		    __field(rxrpc_serial_t,		resp_serial	)
		    __field(u32,			rtt		)
		    __field(u32,			rto		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->why = why;
		    __entry->slot = slot;
		    __entry->send_serial = send_serial;
		    __entry->resp_serial = resp_serial;
		    __entry->rtt = rtt;
		    __entry->rto = rto;
			   ),

	    TP_prपूर्णांकk("c=%08x [%d] %s sr=%08x rr=%08x rtt=%u rto=%u",
		      __entry->call,
		      __entry->slot,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_rtt_rx_traces),
		      __entry->send_serial,
		      __entry->resp_serial,
		      __entry->rtt,
		      __entry->rto)
	    );

TRACE_EVENT(rxrpc_समयr,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_समयr_trace why,
		     अचिन्हित दीर्घ now),

	    TP_ARGS(call, why, now),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			call		)
		    __field(क्रमागत rxrpc_समयr_trace,		why		)
		    __field(दीर्घ,				now		)
		    __field(दीर्घ,				ack_at		)
		    __field(दीर्घ,				ack_lost_at	)
		    __field(दीर्घ,				resend_at	)
		    __field(दीर्घ,				ping_at		)
		    __field(दीर्घ,				expect_rx_by	)
		    __field(दीर्घ,				expect_req_by	)
		    __field(दीर्घ,				expect_term_by	)
		    __field(दीर्घ,				समयr		)
			     ),

	    TP_fast_assign(
		    __entry->call		= call->debug_id;
		    __entry->why		= why;
		    __entry->now		= now;
		    __entry->ack_at		= call->ack_at;
		    __entry->ack_lost_at	= call->ack_lost_at;
		    __entry->resend_at		= call->resend_at;
		    __entry->expect_rx_by	= call->expect_rx_by;
		    __entry->expect_req_by	= call->expect_req_by;
		    __entry->expect_term_by	= call->expect_term_by;
		    __entry->समयr		= call->समयr.expires;
			   ),

	    TP_prपूर्णांकk("c=%08x %s a=%ld la=%ld r=%ld xr=%ld xq=%ld xt=%ld t=%ld",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_समयr_traces),
		      __entry->ack_at - __entry->now,
		      __entry->ack_lost_at - __entry->now,
		      __entry->resend_at - __entry->now,
		      __entry->expect_rx_by - __entry->now,
		      __entry->expect_req_by - __entry->now,
		      __entry->expect_term_by - __entry->now,
		      __entry->समयr - __entry->now)
	    );

TRACE_EVENT(rxrpc_rx_lose,
	    TP_PROTO(काष्ठा rxrpc_skb_priv *sp),

	    TP_ARGS(sp),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा rxrpc_host_header,	hdr		)
			     ),

	    TP_fast_assign(
		    स_नकल(&__entry->hdr, &sp->hdr, माप(__entry->hdr));
			   ),

	    TP_prपूर्णांकk("%08x:%08x:%08x:%04x %08x %08x %02x %02x %s *LOSE*",
		      __entry->hdr.epoch, __entry->hdr.cid,
		      __entry->hdr.callNumber, __entry->hdr.serviceId,
		      __entry->hdr.serial, __entry->hdr.seq,
		      __entry->hdr.type, __entry->hdr.flags,
		      __entry->hdr.type <= 15 ?
		      __prपूर्णांक_symbolic(__entry->hdr.type, rxrpc_pkts) : "?UNK")
	    );

TRACE_EVENT(rxrpc_propose_ack,
	    TP_PROTO(काष्ठा rxrpc_call *call, क्रमागत rxrpc_propose_ack_trace why,
		     u8 ack_reason, rxrpc_serial_t serial, bool immediate,
		     bool background, क्रमागत rxrpc_propose_ack_outcome outcome),

	    TP_ARGS(call, why, ack_reason, serial, immediate, background,
		    outcome),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			call		)
		    __field(क्रमागत rxrpc_propose_ack_trace,	why		)
		    __field(rxrpc_serial_t,			serial		)
		    __field(u8,					ack_reason	)
		    __field(bool,				immediate	)
		    __field(bool,				background	)
		    __field(क्रमागत rxrpc_propose_ack_outcome,	outcome		)
			     ),

	    TP_fast_assign(
		    __entry->call	= call->debug_id;
		    __entry->why	= why;
		    __entry->serial	= serial;
		    __entry->ack_reason	= ack_reason;
		    __entry->immediate	= immediate;
		    __entry->background	= background;
		    __entry->outcome	= outcome;
			   ),

	    TP_prपूर्णांकk("c=%08x %s %s r=%08x i=%u b=%u%s",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->why, rxrpc_propose_ack_traces),
		      __prपूर्णांक_symbolic(__entry->ack_reason, rxrpc_ack_names),
		      __entry->serial,
		      __entry->immediate,
		      __entry->background,
		      __prपूर्णांक_symbolic(__entry->outcome, rxrpc_propose_ack_outcomes))
	    );

TRACE_EVENT(rxrpc_retransmit,
	    TP_PROTO(काष्ठा rxrpc_call *call, rxrpc_seq_t seq, u8 annotation,
		     s64 expiry),

	    TP_ARGS(call, seq, annotation, expiry),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_seq_t,		seq		)
		    __field(u8,				annotation	)
		    __field(s64,			expiry		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->seq = seq;
		    __entry->annotation = annotation;
		    __entry->expiry = expiry;
			   ),

	    TP_prपूर्णांकk("c=%08x q=%x a=%02x xp=%lld",
		      __entry->call,
		      __entry->seq,
		      __entry->annotation,
		      __entry->expiry)
	    );

TRACE_EVENT(rxrpc_congest,
	    TP_PROTO(काष्ठा rxrpc_call *call, काष्ठा rxrpc_ack_summary *summary,
		     rxrpc_serial_t ack_serial, क्रमागत rxrpc_congest_change change),

	    TP_ARGS(call, summary, ack_serial, change),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			call		)
		    __field(क्रमागत rxrpc_congest_change,		change		)
		    __field(rxrpc_seq_t,			hard_ack	)
		    __field(rxrpc_seq_t,			top		)
		    __field(rxrpc_seq_t,			lowest_nak	)
		    __field(rxrpc_serial_t,			ack_serial	)
		    __field_काष्ठा(काष्ठा rxrpc_ack_summary,	sum		)
			     ),

	    TP_fast_assign(
		    __entry->call	= call->debug_id;
		    __entry->change	= change;
		    __entry->hard_ack	= call->tx_hard_ack;
		    __entry->top	= call->tx_top;
		    __entry->lowest_nak	= call->acks_lowest_nak;
		    __entry->ack_serial	= ack_serial;
		    स_नकल(&__entry->sum, summary, माप(__entry->sum));
			   ),

	    TP_prपूर्णांकk("c=%08x r=%08x %s q=%08x %s cw=%u ss=%u nr=%u,%u nw=%u,%u r=%u b=%u u=%u d=%u l=%x%s%s%s",
		      __entry->call,
		      __entry->ack_serial,
		      __prपूर्णांक_symbolic(__entry->sum.ack_reason, rxrpc_ack_names),
		      __entry->hard_ack,
		      __prपूर्णांक_symbolic(__entry->sum.mode, rxrpc_congest_modes),
		      __entry->sum.cwnd,
		      __entry->sum.ssthresh,
		      __entry->sum.nr_acks, __entry->sum.nr_nacks,
		      __entry->sum.nr_new_acks, __entry->sum.nr_new_nacks,
		      __entry->sum.nr_rot_new_acks,
		      __entry->top - __entry->hard_ack,
		      __entry->sum.cumulative_acks,
		      __entry->sum.dup_acks,
		      __entry->lowest_nak, __entry->sum.new_low_nack ? "!" : "",
		      __prपूर्णांक_symbolic(__entry->change, rxrpc_congest_changes),
		      __entry->sum.retrans_समयo ? " rTxTo" : "")
	    );

TRACE_EVENT(rxrpc_disconnect_call,
	    TP_PROTO(काष्ठा rxrpc_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(u32,			पात_code	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->पात_code = call->पात_code;
			   ),

	    TP_prपूर्णांकk("c=%08x ab=%08x",
		      __entry->call,
		      __entry->पात_code)
	    );

TRACE_EVENT(rxrpc_improper_term,
	    TP_PROTO(काष्ठा rxrpc_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(u32,			पात_code	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->पात_code = call->पात_code;
			   ),

	    TP_prपूर्णांकk("c=%08x ab=%08x",
		      __entry->call,
		      __entry->पात_code)
	    );

TRACE_EVENT(rxrpc_rx_eproto,
	    TP_PROTO(काष्ठा rxrpc_call *call, rxrpc_serial_t serial,
		     स्थिर अक्षर *why),

	    TP_ARGS(call, serial, why),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(rxrpc_serial_t,		serial		)
		    __field(स्थिर अक्षर *,		why		)
			     ),

	    TP_fast_assign(
		    __entry->call = call ? call->debug_id : 0;
		    __entry->serial = serial;
		    __entry->why = why;
			   ),

	    TP_prपूर्णांकk("c=%08x EPROTO %08x %s",
		      __entry->call,
		      __entry->serial,
		      __entry->why)
	    );

TRACE_EVENT(rxrpc_connect_call,
	    TP_PROTO(काष्ठा rxrpc_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(अचिन्हित दीर्घ,		user_call_ID	)
		    __field(u32,			cid		)
		    __field(u32,			call_id		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->user_call_ID = call->user_call_ID;
		    __entry->cid = call->cid;
		    __entry->call_id = call->call_id;
			   ),

	    TP_prपूर्णांकk("c=%08x u=%p %08x:%08x",
		      __entry->call,
		      (व्योम *)__entry->user_call_ID,
		      __entry->cid,
		      __entry->call_id)
	    );

TRACE_EVENT(rxrpc_resend,
	    TP_PROTO(काष्ठा rxrpc_call *call, पूर्णांक ix),

	    TP_ARGS(call, ix),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(पूर्णांक,			ix		)
		    __array(u8,				anno, 64	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->ix = ix;
		    स_नकल(__entry->anno, call->rxtx_annotations, 64);
			   ),

	    TP_prपूर्णांकk("c=%08x ix=%u a=%64phN",
		      __entry->call,
		      __entry->ix,
		      __entry->anno)
	    );

TRACE_EVENT(rxrpc_rx_icmp,
	    TP_PROTO(काष्ठा rxrpc_peer *peer, काष्ठा sock_extended_err *ee,
		     काष्ठा sockaddr_rxrpc *srx),

	    TP_ARGS(peer, ee, srx),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			peer	)
		    __field_काष्ठा(काष्ठा sock_extended_err,	ee	)
		    __field_काष्ठा(काष्ठा sockaddr_rxrpc,	srx	)
			     ),

	    TP_fast_assign(
		    __entry->peer = peer->debug_id;
		    स_नकल(&__entry->ee, ee, माप(__entry->ee));
		    स_नकल(&__entry->srx, srx, माप(__entry->srx));
			   ),

	    TP_prपूर्णांकk("P=%08x o=%u t=%u c=%u i=%u d=%u e=%d %pISp",
		      __entry->peer,
		      __entry->ee.ee_origin,
		      __entry->ee.ee_type,
		      __entry->ee.ee_code,
		      __entry->ee.ee_info,
		      __entry->ee.ee_data,
		      __entry->ee.ee_त्रुटि_सं,
		      &__entry->srx.transport)
	    );

TRACE_EVENT(rxrpc_tx_fail,
	    TP_PROTO(अचिन्हित पूर्णांक debug_id, rxrpc_serial_t serial, पूर्णांक ret,
		     क्रमागत rxrpc_tx_poपूर्णांक where),

	    TP_ARGS(debug_id, serial, ret, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		debug_id	)
		    __field(rxrpc_serial_t,		serial		)
		    __field(पूर्णांक,			ret		)
		    __field(क्रमागत rxrpc_tx_poपूर्णांक,	where		)
			     ),

	    TP_fast_assign(
		    __entry->debug_id = debug_id;
		    __entry->serial = serial;
		    __entry->ret = ret;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("c=%08x r=%x ret=%d %s",
		      __entry->debug_id,
		      __entry->serial,
		      __entry->ret,
		      __prपूर्णांक_symbolic(__entry->where, rxrpc_tx_poपूर्णांकs))
	    );

TRACE_EVENT(rxrpc_call_reset,
	    TP_PROTO(काष्ठा rxrpc_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		debug_id	)
		    __field(u32,			cid		)
		    __field(u32,			call_id		)
		    __field(rxrpc_serial_t,		call_serial	)
		    __field(rxrpc_serial_t,		conn_serial	)
		    __field(rxrpc_seq_t,		tx_seq		)
		    __field(rxrpc_seq_t,		rx_seq		)
			     ),

	    TP_fast_assign(
		    __entry->debug_id = call->debug_id;
		    __entry->cid = call->cid;
		    __entry->call_id = call->call_id;
		    __entry->call_serial = call->rx_serial;
		    __entry->conn_serial = call->conn->hi_serial;
		    __entry->tx_seq = call->tx_hard_ack;
		    __entry->rx_seq = call->ackr_seen;
			   ),

	    TP_prपूर्णांकk("c=%08x %08x:%08x r=%08x/%08x tx=%08x rx=%08x",
		      __entry->debug_id,
		      __entry->cid, __entry->call_id,
		      __entry->call_serial, __entry->conn_serial,
		      __entry->tx_seq, __entry->rx_seq)
	    );

TRACE_EVENT(rxrpc_notअगरy_socket,
	    TP_PROTO(अचिन्हित पूर्णांक debug_id, rxrpc_serial_t serial),

	    TP_ARGS(debug_id, serial),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		debug_id	)
		    __field(rxrpc_serial_t,		serial		)
			     ),

	    TP_fast_assign(
		    __entry->debug_id = debug_id;
		    __entry->serial = serial;
			   ),

	    TP_prपूर्णांकk("c=%08x r=%08x",
		      __entry->debug_id,
		      __entry->serial)
	    );

TRACE_EVENT(rxrpc_rx_discard_ack,
	    TP_PROTO(अचिन्हित पूर्णांक debug_id, rxrpc_serial_t serial,
		     rxrpc_seq_t first_soft_ack, rxrpc_seq_t call_ackr_first,
		     rxrpc_seq_t prev_pkt, rxrpc_seq_t call_ackr_prev),

	    TP_ARGS(debug_id, serial, first_soft_ack, call_ackr_first,
		    prev_pkt, call_ackr_prev),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,	debug_id	)
		    __field(rxrpc_serial_t,	serial		)
		    __field(rxrpc_seq_t,	first_soft_ack)
		    __field(rxrpc_seq_t,	call_ackr_first)
		    __field(rxrpc_seq_t,	prev_pkt)
		    __field(rxrpc_seq_t,	call_ackr_prev)
			     ),

	    TP_fast_assign(
		    __entry->debug_id		= debug_id;
		    __entry->serial		= serial;
		    __entry->first_soft_ack	= first_soft_ack;
		    __entry->call_ackr_first	= call_ackr_first;
		    __entry->prev_pkt		= prev_pkt;
		    __entry->call_ackr_prev	= call_ackr_prev;
			   ),

	    TP_prपूर्णांकk("c=%08x r=%08x %08x<%08x %08x<%08x",
		      __entry->debug_id,
		      __entry->serial,
		      __entry->first_soft_ack,
		      __entry->call_ackr_first,
		      __entry->prev_pkt,
		      __entry->call_ackr_prev)
	    );

#पूर्ण_अगर /* _TRACE_RXRPC_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
