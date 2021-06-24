<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _DCCP_FEAT_H
#घोषणा _DCCP_FEAT_H
/*
 *  net/dccp/feat.h
 *
 *  Feature negotiation क्रम the DCCP protocol (RFC 4340, section 6)
 *  Copyright (c) 2008 Gerrit Renker <gerrit@erg.abdn.ac.uk>
 *  Copyright (c) 2005 Andrea Bittau <a.bittau@cs.ucl.ac.uk>
 */
#समावेश <linux/types.h>
#समावेश "dccp.h"

/*
 * Known limit values
 */
/* Ack Ratio takes 2-byte पूर्णांकeger values (11.3) */
#घोषणा DCCPF_ACK_RATIO_MAX	0xFFFF
/* Wmin=32 and Wmax=2^46-1 from 7.5.2 */
#घोषणा DCCPF_SEQ_WMIN		32
#घोषणा DCCPF_SEQ_WMAX		0x3FFFFFFFFFFFull
/* Maximum number of SP values that fit in a single (Confirm) option */
#घोषणा DCCP_FEAT_MAX_SP_VALS	(DCCP_SINGLE_OPT_MAXLEN - 2)

क्रमागत dccp_feat_type अणु
	FEAT_AT_RX   = 1,	/* located at RX side of half-connection  */
	FEAT_AT_TX   = 2,	/* located at TX side of half-connection  */
	FEAT_SP      = 4,	/* server-priority reconciliation (6.3.1) */
	FEAT_NN	     = 8,	/* non-negotiable reconciliation (6.3.2)  */
	FEAT_UNKNOWN = 0xFF	/* not understood or invalid feature	  */
पूर्ण;

क्रमागत dccp_feat_state अणु
	FEAT_DEFAULT = 0,	/* using शेष values from 6.4 */
	FEAT_INITIALISING,	/* feature is being initialised  */
	FEAT_CHANGING,		/* Change sent but not confirmed yet */
	FEAT_UNSTABLE,		/* local modअगरication in state CHANGING */
	FEAT_STABLE		/* both ends (think they) agree */
पूर्ण;

/**
 * dccp_feat_val  -  Container क्रम SP or NN feature values
 * @nn:     single NN value
 * @sp.vec: single SP value plus optional preference list
 * @sp.len: length of @sp.vec in bytes
 */
प्रकार जोड़ अणु
	u64 nn;
	काष्ठा अणु
		u8	*vec;
		u8	len;
	पूर्ण   sp;
पूर्ण dccp_feat_val;

/**
 * काष्ठा feat_entry  -  Data काष्ठाure to perक्रमm feature negotiation
 * @val: feature's current value (SP features may have preference list)
 * @state: feature's current state
 * @feat_num: one of %dccp_feature_numbers
 * @needs_mandatory: whether Mandatory options should be sent
 * @needs_confirm: whether to send a Confirm instead of a Change
 * @empty_confirm: whether to send an empty Confirm (depends on @needs_confirm)
 * @is_local: feature location (1) or feature-remote (0)
 * @node: list poपूर्णांकers, entries arranged in FIFO order
 */
काष्ठा dccp_feat_entry अणु
	dccp_feat_val           val;
	क्रमागत dccp_feat_state    state:8;
	u8                      feat_num;

	bool			needs_mandatory,
				needs_confirm,
				empty_confirm,
				is_local;

	काष्ठा list_head	node;
पूर्ण;

अटल अंतरभूत u8 dccp_feat_genopt(काष्ठा dccp_feat_entry *entry)
अणु
	अगर (entry->needs_confirm)
		वापस entry->is_local ? DCCPO_CONFIRM_L : DCCPO_CONFIRM_R;
	वापस entry->is_local ? DCCPO_CHANGE_L : DCCPO_CHANGE_R;
पूर्ण

/**
 * काष्ठा ccid_dependency  -  Track changes resulting from choosing a CCID
 * @dependent_feat: one of %dccp_feature_numbers
 * @is_local: local (1) or remote (0) @dependent_feat
 * @is_mandatory: whether presence of @dependent_feat is mission-critical or not
 * @val: corresponding शेष value क्रम @dependent_feat (u8 is sufficient here)
 */
काष्ठा ccid_dependency अणु
	u8	dependent_feat;
	bool	is_local:1,
		is_mandatory:1;
	u8	val;
पूर्ण;

/*
 * Sysctls to seed शेषs क्रम feature negotiation
 */
बाह्य अचिन्हित दीर्घ sysctl_dccp_sequence_winकरोw;
बाह्य पूर्णांक	     sysctl_dccp_rx_ccid;
बाह्य पूर्णांक	     sysctl_dccp_tx_ccid;

पूर्णांक dccp_feat_init(काष्ठा sock *sk);
व्योम dccp_feat_initialise_sysctls(व्योम);
पूर्णांक dccp_feat_रेजिस्टर_sp(काष्ठा sock *sk, u8 feat, u8 is_local,
			  u8 स्थिर *list, u8 len);
पूर्णांक dccp_feat_parse_options(काष्ठा sock *, काष्ठा dccp_request_sock *,
			    u8 mand, u8 opt, u8 feat, u8 *val, u8 len);
पूर्णांक dccp_feat_clone_list(काष्ठा list_head स्थिर *, काष्ठा list_head *);

/*
 * Encoding variable-length options and their maximum length.
 *
 * This affects NN options (SP options are all u8) and other variable-length
 * options (see table 3 in RFC 4340). The limit is currently given the Sequence
 * Winकरोw NN value (sec. 7.5.2) and the NDP count (sec. 7.7) option, all other
 * options consume less than 6 bytes (बारtamps are 4 bytes).
 * When updating this स्थिरant (e.g. due to new पूर्णांकernet drafts / RFCs), make
 * sure that you also update all code which refers to it.
 */
#घोषणा DCCP_OPTVAL_MAXLEN	6

व्योम dccp_encode_value_var(स्थिर u64 value, u8 *to, स्थिर u8 len);
u64 dccp_decode_value_var(स्थिर u8 *bf, स्थिर u8 len);
u64 dccp_feat_nn_get(काष्ठा sock *sk, u8 feat);

पूर्णांक dccp_insert_option_mandatory(काष्ठा sk_buff *skb);
पूर्णांक dccp_insert_fn_opt(काष्ठा sk_buff *skb, u8 type, u8 feat, u8 *val, u8 len,
		       bool repeat_first);
#पूर्ण_अगर /* _DCCP_FEAT_H */
