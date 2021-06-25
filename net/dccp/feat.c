<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/feat.c
 *
 *  Feature negotiation क्रम the DCCP protocol (RFC 4340, section 6)
 *
 *  Copyright (c) 2008 Gerrit Renker <gerrit@erg.abdn.ac.uk>
 *  Rewrote from scratch, some bits from earlier code by
 *  Copyright (c) 2005 Andrea Bittau <a.bittau@cs.ucl.ac.uk>
 *
 *  ASSUMPTIONS
 *  -----------
 *  o Feature negotiation is coordinated with connection setup (as in TCP), wild
 *    changes of parameters of an established connection are not supported.
 *  o Changing non-negotiable (NN) values is supported in state OPEN/PARTOPEN.
 *  o All currently known SP features have 1-byte quantities. If in the future
 *    extensions of RFCs 4340..42 define features with item lengths larger than
 *    one byte, a feature-specअगरic extension of the code will be required.
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "ccid.h"
#समावेश "feat.h"

/* feature-specअगरic sysctls - initialised to the शेषs from RFC 4340, 6.4 */
अचिन्हित दीर्घ	sysctl_dccp_sequence_winकरोw __पढ़ो_mostly = 100;
पूर्णांक		sysctl_dccp_rx_ccid	    __पढ़ो_mostly = 2,
		sysctl_dccp_tx_ccid	    __पढ़ो_mostly = 2;

/*
 * Feature activation handlers.
 *
 * These all use an u64 argument, to provide enough room क्रम NN/SP features. At
 * this stage the negotiated values have been checked to be within their range.
 */
अटल पूर्णांक dccp_hdlr_ccid(काष्ठा sock *sk, u64 ccid, bool rx)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा ccid *new_ccid = ccid_new(ccid, sk, rx);

	अगर (new_ccid == शून्य)
		वापस -ENOMEM;

	अगर (rx) अणु
		ccid_hc_rx_delete(dp->dccps_hc_rx_ccid, sk);
		dp->dccps_hc_rx_ccid = new_ccid;
	पूर्ण अन्यथा अणु
		ccid_hc_tx_delete(dp->dccps_hc_tx_ccid, sk);
		dp->dccps_hc_tx_ccid = new_ccid;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dccp_hdlr_seq_win(काष्ठा sock *sk, u64 seq_win, bool rx)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	अगर (rx) अणु
		dp->dccps_r_seq_win = seq_win;
		/* propagate changes to update SWL/SWH */
		dccp_update_gsr(sk, dp->dccps_gsr);
	पूर्ण अन्यथा अणु
		dp->dccps_l_seq_win = seq_win;
		/* propagate changes to update AWL */
		dccp_update_gss(sk, dp->dccps_gss);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dccp_hdlr_ack_ratio(काष्ठा sock *sk, u64 ratio, bool rx)
अणु
	अगर (rx)
		dccp_sk(sk)->dccps_r_ack_ratio = ratio;
	अन्यथा
		dccp_sk(sk)->dccps_l_ack_ratio = ratio;
	वापस 0;
पूर्ण

अटल पूर्णांक dccp_hdlr_ackvec(काष्ठा sock *sk, u64 enable, bool rx)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	अगर (rx) अणु
		अगर (enable && dp->dccps_hc_rx_ackvec == शून्य) अणु
			dp->dccps_hc_rx_ackvec = dccp_ackvec_alloc(gfp_any());
			अगर (dp->dccps_hc_rx_ackvec == शून्य)
				वापस -ENOMEM;
		पूर्ण अन्यथा अगर (!enable) अणु
			dccp_ackvec_मुक्त(dp->dccps_hc_rx_ackvec);
			dp->dccps_hc_rx_ackvec = शून्य;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dccp_hdlr_ndp(काष्ठा sock *sk, u64 enable, bool rx)
अणु
	अगर (!rx)
		dccp_sk(sk)->dccps_send_ndp_count = (enable > 0);
	वापस 0;
पूर्ण

/*
 * Minimum Checksum Coverage is located at the RX side (9.2.1). This means that
 * `rx' holds when the sending peer inक्रमms about his partial coverage via a
 * ChangeR() option. In the other हाल, we are the sender and the receiver
 * announces its coverage via ChangeL() options. The policy here is to honour
 * such communication by enabling the corresponding partial coverage - but only
 * अगर it has not been set manually beक्रमe; the warning here means that all
 * packets will be dropped.
 */
अटल पूर्णांक dccp_hdlr_min_cscov(काष्ठा sock *sk, u64 cscov, bool rx)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	अगर (rx)
		dp->dccps_pcrlen = cscov;
	अन्यथा अणु
		अगर (dp->dccps_pcslen == 0)
			dp->dccps_pcslen = cscov;
		अन्यथा अगर (cscov > dp->dccps_pcslen)
			DCCP_WARN("CsCov %u too small, peer requires >= %u\n",
				  dp->dccps_pcslen, (u8)cscov);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	u8			feat_num;		/* DCCPF_xxx */
	क्रमागत dccp_feat_type	rxtx;			/* RX or TX  */
	क्रमागत dccp_feat_type	reconciliation;		/* SP or NN  */
	u8			शेष_value;		/* as in 6.4 */
	पूर्णांक (*activation_hdlr)(काष्ठा sock *sk, u64 val, bool rx);
/*
 *    Lookup table क्रम location and type of features (from RFC 4340/4342)
 *  +--------------------------+----+-----+----+----+---------+-----------+
 *  | Feature                  | Location | Reconc. | Initial |  Section  |
 *  |                          | RX | TX  | SP | NN |  Value  | Reference |
 *  +--------------------------+----+-----+----+----+---------+-----------+
 *  | DCCPF_CCID               |    |  X  | X  |    |   2     | 10        |
 *  | DCCPF_SHORT_SEQNOS       |    |  X  | X  |    |   0     |  7.6.1    |
 *  | DCCPF_SEQUENCE_WINDOW    |    |  X  |    | X  | 100     |  7.5.2    |
 *  | DCCPF_ECN_INCAPABLE      | X  |     | X  |    |   0     | 12.1      |
 *  | DCCPF_ACK_RATIO          |    |  X  |    | X  |   2     | 11.3      |
 *  | DCCPF_SEND_ACK_VECTOR    | X  |     | X  |    |   0     | 11.5      |
 *  | DCCPF_SEND_NDP_COUNT     |    |  X  | X  |    |   0     |  7.7.2    |
 *  | DCCPF_MIN_CSUM_COVER     | X  |     | X  |    |   0     |  9.2.1    |
 *  | DCCPF_DATA_CHECKSUM      | X  |     | X  |    |   0     |  9.3.1    |
 *  | DCCPF_SEND_LEV_RATE      | X  |     | X  |    |   0     | 4342/8.4  |
 *  +--------------------------+----+-----+----+----+---------+-----------+
 */
पूर्ण dccp_feat_table[] = अणु
	अणु DCCPF_CCID,		 FEAT_AT_TX, FEAT_SP, 2,   dccp_hdlr_ccid     पूर्ण,
	अणु DCCPF_SHORT_SEQNOS,	 FEAT_AT_TX, FEAT_SP, 0,   शून्य पूर्ण,
	अणु DCCPF_SEQUENCE_WINDOW, FEAT_AT_TX, FEAT_NN, 100, dccp_hdlr_seq_win  पूर्ण,
	अणु DCCPF_ECN_INCAPABLE,	 FEAT_AT_RX, FEAT_SP, 0,   शून्य पूर्ण,
	अणु DCCPF_ACK_RATIO,	 FEAT_AT_TX, FEAT_NN, 2,   dccp_hdlr_ack_ratioपूर्ण,
	अणु DCCPF_SEND_ACK_VECTOR, FEAT_AT_RX, FEAT_SP, 0,   dccp_hdlr_ackvec   पूर्ण,
	अणु DCCPF_SEND_NDP_COUNT,  FEAT_AT_TX, FEAT_SP, 0,   dccp_hdlr_ndp      पूर्ण,
	अणु DCCPF_MIN_CSUM_COVER,  FEAT_AT_RX, FEAT_SP, 0,   dccp_hdlr_min_cscovपूर्ण,
	अणु DCCPF_DATA_CHECKSUM,	 FEAT_AT_RX, FEAT_SP, 0,   शून्य पूर्ण,
	अणु DCCPF_SEND_LEV_RATE,	 FEAT_AT_RX, FEAT_SP, 0,   शून्य पूर्ण,
पूर्ण;
#घोषणा DCCP_FEAT_SUPPORTED_MAX		ARRAY_SIZE(dccp_feat_table)

/**
 * dccp_feat_index  -  Hash function to map feature number पूर्णांकo array position
 * @feat_num: feature to hash, one of %dccp_feature_numbers
 *
 * Returns consecutive array index or -1 अगर the feature is not understood.
 */
अटल पूर्णांक dccp_feat_index(u8 feat_num)
अणु
	/* The first 9 entries are occupied by the types from RFC 4340, 6.4 */
	अगर (feat_num > DCCPF_RESERVED && feat_num <= DCCPF_DATA_CHECKSUM)
		वापस feat_num - 1;

	/*
	 * Other features: add हालs क्रम new feature types here after adding
	 * them to the above table.
	 */
	चयन (feat_num) अणु
	हाल DCCPF_SEND_LEV_RATE:
			वापस DCCP_FEAT_SUPPORTED_MAX - 1;
	पूर्ण
	वापस -1;
पूर्ण

अटल u8 dccp_feat_type(u8 feat_num)
अणु
	पूर्णांक idx = dccp_feat_index(feat_num);

	अगर (idx < 0)
		वापस FEAT_UNKNOWN;
	वापस dccp_feat_table[idx].reconciliation;
पूर्ण

अटल पूर्णांक dccp_feat_शेष_value(u8 feat_num)
अणु
	पूर्णांक idx = dccp_feat_index(feat_num);
	/*
	 * There are no शेष values क्रम unknown features, so encountering a
	 * negative index here indicates a serious problem somewhere अन्यथा.
	 */
	DCCP_BUG_ON(idx < 0);

	वापस idx < 0 ? 0 : dccp_feat_table[idx].शेष_value;
पूर्ण

/*
 *	Debugging and verbose-prपूर्णांकing section
 */
अटल स्थिर अक्षर *dccp_feat_fname(स्थिर u8 feat)
अणु
	अटल स्थिर अक्षर *स्थिर feature_names[] = अणु
		[DCCPF_RESERVED]	= "Reserved",
		[DCCPF_CCID]		= "CCID",
		[DCCPF_SHORT_SEQNOS]	= "Allow Short Seqnos",
		[DCCPF_SEQUENCE_WINDOW]	= "Sequence Window",
		[DCCPF_ECN_INCAPABLE]	= "ECN Incapable",
		[DCCPF_ACK_RATIO]	= "Ack Ratio",
		[DCCPF_SEND_ACK_VECTOR]	= "Send ACK Vector",
		[DCCPF_SEND_NDP_COUNT]	= "Send NDP Count",
		[DCCPF_MIN_CSUM_COVER]	= "Min. Csum Coverage",
		[DCCPF_DATA_CHECKSUM]	= "Send Data Checksum",
	पूर्ण;
	अगर (feat > DCCPF_DATA_CHECKSUM && feat < DCCPF_MIN_CCID_SPECIFIC)
		वापस feature_names[DCCPF_RESERVED];

	अगर (feat ==  DCCPF_SEND_LEV_RATE)
		वापस "Send Loss Event Rate";
	अगर (feat >= DCCPF_MIN_CCID_SPECIFIC)
		वापस "CCID-specific";

	वापस feature_names[feat];
पूर्ण

अटल स्थिर अक्षर *स्थिर dccp_feat_sname[] = अणु
	"DEFAULT", "INITIALISING", "CHANGING", "UNSTABLE", "STABLE",
पूर्ण;

#अगर_घोषित CONFIG_IP_DCCP_DEBUG
अटल स्थिर अक्षर *dccp_feat_oname(स्थिर u8 opt)
अणु
	चयन (opt) अणु
	हाल DCCPO_CHANGE_L:  वापस "Change_L";
	हाल DCCPO_CONFIRM_L: वापस "Confirm_L";
	हाल DCCPO_CHANGE_R:  वापस "Change_R";
	हाल DCCPO_CONFIRM_R: वापस "Confirm_R";
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम dccp_feat_prपूर्णांकval(u8 feat_num, dccp_feat_val स्थिर *val)
अणु
	u8 i, type = dccp_feat_type(feat_num);

	अगर (val == शून्य || (type == FEAT_SP && val->sp.vec == शून्य))
		dccp_pr_debug_cat("(NULL)");
	अन्यथा अगर (type == FEAT_SP)
		क्रम (i = 0; i < val->sp.len; i++)
			dccp_pr_debug_cat("%s%u", i ? " " : "", val->sp.vec[i]);
	अन्यथा अगर (type == FEAT_NN)
		dccp_pr_debug_cat("%llu", (अचिन्हित दीर्घ दीर्घ)val->nn);
	अन्यथा
		dccp_pr_debug_cat("unknown type %u", type);
पूर्ण

अटल व्योम dccp_feat_prपूर्णांकvals(u8 feat_num, u8 *list, u8 len)
अणु
	u8 type = dccp_feat_type(feat_num);
	dccp_feat_val fval = अणु .sp.vec = list, .sp.len = len पूर्ण;

	अगर (type == FEAT_NN)
		fval.nn = dccp_decode_value_var(list, len);
	dccp_feat_prपूर्णांकval(feat_num, &fval);
पूर्ण

अटल व्योम dccp_feat_prपूर्णांक_entry(काष्ठा dccp_feat_entry स्थिर *entry)
अणु
	dccp_debug("   * %s %s = ", entry->is_local ? "local" : "remote",
				    dccp_feat_fname(entry->feat_num));
	dccp_feat_prपूर्णांकval(entry->feat_num, &entry->val);
	dccp_pr_debug_cat(", state=%s %s\n", dccp_feat_sname[entry->state],
			  entry->needs_confirm ? "(Confirm pending)" : "");
पूर्ण

#घोषणा dccp_feat_prपूर्णांक_opt(opt, feat, val, len, mandatory)	करो अणु	      \
	dccp_pr_debug("%s(%s, ", dccp_feat_oname(opt), dccp_feat_fname(feat));\
	dccp_feat_prपूर्णांकvals(feat, val, len);				      \
	dccp_pr_debug_cat(") %s\n", mandatory ? "!" : "");	पूर्ण जबतक (0)

#घोषणा dccp_feat_prपूर्णांक_fnlist(fn_list)  अणु		\
	स्थिर काष्ठा dccp_feat_entry *___entry;		\
							\
	dccp_pr_debug("List Dump:\n");			\
	list_क्रम_each_entry(___entry, fn_list, node)	\
		dccp_feat_prपूर्णांक_entry(___entry);	\
पूर्ण
#अन्यथा	/* ! CONFIG_IP_DCCP_DEBUG */
#घोषणा dccp_feat_prपूर्णांक_opt(opt, feat, val, len, mandatory)
#घोषणा dccp_feat_prपूर्णांक_fnlist(fn_list)
#पूर्ण_अगर

अटल पूर्णांक __dccp_feat_activate(काष्ठा sock *sk, स्थिर पूर्णांक idx,
				स्थिर bool is_local, dccp_feat_val स्थिर *fval)
अणु
	bool rx;
	u64 val;

	अगर (idx < 0 || idx >= DCCP_FEAT_SUPPORTED_MAX)
		वापस -1;
	अगर (dccp_feat_table[idx].activation_hdlr == शून्य)
		वापस 0;

	अगर (fval == शून्य) अणु
		val = dccp_feat_table[idx].शेष_value;
	पूर्ण अन्यथा अगर (dccp_feat_table[idx].reconciliation == FEAT_SP) अणु
		अगर (fval->sp.vec == शून्य) अणु
			/*
			 * This can happen when an empty Confirm is sent
			 * क्रम an SP (i.e. known) feature. In this हाल
			 * we would be using the शेष anyway.
			 */
			DCCP_CRIT("Feature #%d undefined: using default", idx);
			val = dccp_feat_table[idx].शेष_value;
		पूर्ण अन्यथा अणु
			val = fval->sp.vec[0];
		पूर्ण
	पूर्ण अन्यथा अणु
		val = fval->nn;
	पूर्ण

	/* Location is RX अगर this is a local-RX or remote-TX feature */
	rx = (is_local == (dccp_feat_table[idx].rxtx == FEAT_AT_RX));

	dccp_debug("   -> activating %s %s, %sval=%llu\n", rx ? "RX" : "TX",
		   dccp_feat_fname(dccp_feat_table[idx].feat_num),
		   fval ? "" : "default ",  (अचिन्हित दीर्घ दीर्घ)val);

	वापस dccp_feat_table[idx].activation_hdlr(sk, val, rx);
पूर्ण

/**
 * dccp_feat_activate  -  Activate feature value on socket
 * @sk: fully connected DCCP socket (after handshake is complete)
 * @feat_num: feature to activate, one of %dccp_feature_numbers
 * @local: whether local (1) or remote (0) @feat_num is meant
 * @fval: the value (SP or NN) to activate, or शून्य to use the शेष value
 *
 * For general use this function is preferable over __dccp_feat_activate().
 */
अटल पूर्णांक dccp_feat_activate(काष्ठा sock *sk, u8 feat_num, bool local,
			      dccp_feat_val स्थिर *fval)
अणु
	वापस __dccp_feat_activate(sk, dccp_feat_index(feat_num), local, fval);
पूर्ण

/* Test क्रम "Req'd" feature (RFC 4340, 6.4) */
अटल अंतरभूत पूर्णांक dccp_feat_must_be_understood(u8 feat_num)
अणु
	वापस	feat_num == DCCPF_CCID || feat_num == DCCPF_SHORT_SEQNOS ||
		feat_num == DCCPF_SEQUENCE_WINDOW;
पूर्ण

/* copy स्थिरructor, fval must not alपढ़ोy contain allocated memory */
अटल पूर्णांक dccp_feat_clone_sp_val(dccp_feat_val *fval, u8 स्थिर *val, u8 len)
अणु
	fval->sp.len = len;
	अगर (fval->sp.len > 0) अणु
		fval->sp.vec = kmemdup(val, len, gfp_any());
		अगर (fval->sp.vec == शून्य) अणु
			fval->sp.len = 0;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dccp_feat_val_deकाष्ठाor(u8 feat_num, dccp_feat_val *val)
अणु
	अगर (unlikely(val == शून्य))
		वापस;
	अगर (dccp_feat_type(feat_num) == FEAT_SP)
		kमुक्त(val->sp.vec);
	स_रखो(val, 0, माप(*val));
पूर्ण

अटल काष्ठा dccp_feat_entry *
	      dccp_feat_clone_entry(काष्ठा dccp_feat_entry स्थिर *original)
अणु
	काष्ठा dccp_feat_entry *new;
	u8 type = dccp_feat_type(original->feat_num);

	अगर (type == FEAT_UNKNOWN)
		वापस शून्य;

	new = kmemdup(original, माप(काष्ठा dccp_feat_entry), gfp_any());
	अगर (new == शून्य)
		वापस शून्य;

	अगर (type == FEAT_SP && dccp_feat_clone_sp_val(&new->val,
						      original->val.sp.vec,
						      original->val.sp.len)) अणु
		kमुक्त(new);
		वापस शून्य;
	पूर्ण
	वापस new;
पूर्ण

अटल व्योम dccp_feat_entry_deकाष्ठाor(काष्ठा dccp_feat_entry *entry)
अणु
	अगर (entry != शून्य) अणु
		dccp_feat_val_deकाष्ठाor(entry->feat_num, &entry->val);
		kमुक्त(entry);
	पूर्ण
पूर्ण

/*
 * List management functions
 *
 * Feature negotiation lists rely on and मुख्यtain the following invariants:
 * - each feat_num in the list is known, i.e. we know its type and शेष value
 * - each feat_num/is_local combination is unique (old entries are overwritten)
 * - SP values are always freshly allocated
 * - list is sorted in increasing order of feature number (faster lookup)
 */
अटल काष्ठा dccp_feat_entry *dccp_feat_list_lookup(काष्ठा list_head *fn_list,
						     u8 feat_num, bool is_local)
अणु
	काष्ठा dccp_feat_entry *entry;

	list_क्रम_each_entry(entry, fn_list, node) अणु
		अगर (entry->feat_num == feat_num && entry->is_local == is_local)
			वापस entry;
		अन्यथा अगर (entry->feat_num > feat_num)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * dccp_feat_entry_new  -  Central list update routine (called by all others)
 * @head:  list to add to
 * @feat:  feature number
 * @local: whether the local (1) or remote feature with number @feat is meant
 *
 * This is the only स्थिरructor and serves to ensure the above invariants.
 */
अटल काष्ठा dccp_feat_entry *
	      dccp_feat_entry_new(काष्ठा list_head *head, u8 feat, bool local)
अणु
	काष्ठा dccp_feat_entry *entry;

	list_क्रम_each_entry(entry, head, node)
		अगर (entry->feat_num == feat && entry->is_local == local) अणु
			dccp_feat_val_deकाष्ठाor(entry->feat_num, &entry->val);
			वापस entry;
		पूर्ण अन्यथा अगर (entry->feat_num > feat) अणु
			head = &entry->node;
			अवरोध;
		पूर्ण

	entry = kदो_स्मृति(माप(*entry), gfp_any());
	अगर (entry != शून्य) अणु
		entry->feat_num = feat;
		entry->is_local = local;
		list_add_tail(&entry->node, head);
	पूर्ण
	वापस entry;
पूर्ण

/**
 * dccp_feat_push_change  -  Add/overग_लिखो a Change option in the list
 * @fn_list: feature-negotiation list to update
 * @feat: one of %dccp_feature_numbers
 * @local: whether local (1) or remote (0) @feat_num is meant
 * @mandatory: whether to use Mandatory feature negotiation options
 * @fval: poपूर्णांकer to NN/SP value to be inserted (will be copied)
 */
अटल पूर्णांक dccp_feat_push_change(काष्ठा list_head *fn_list, u8 feat, u8 local,
				 u8 mandatory, dccp_feat_val *fval)
अणु
	काष्ठा dccp_feat_entry *new = dccp_feat_entry_new(fn_list, feat, local);

	अगर (new == शून्य)
		वापस -ENOMEM;

	new->feat_num	     = feat;
	new->is_local	     = local;
	new->state	     = FEAT_INITIALISING;
	new->needs_confirm   = false;
	new->empty_confirm   = false;
	new->val	     = *fval;
	new->needs_mandatory = mandatory;

	वापस 0;
पूर्ण

/**
 * dccp_feat_push_confirm  -  Add a Confirm entry to the FN list
 * @fn_list: feature-negotiation list to add to
 * @feat: one of %dccp_feature_numbers
 * @local: whether local (1) or remote (0) @feat_num is being confirmed
 * @fval: poपूर्णांकer to NN/SP value to be inserted or शून्य
 *
 * Returns 0 on success, a Reset code क्रम further processing otherwise.
 */
अटल पूर्णांक dccp_feat_push_confirm(काष्ठा list_head *fn_list, u8 feat, u8 local,
				  dccp_feat_val *fval)
अणु
	काष्ठा dccp_feat_entry *new = dccp_feat_entry_new(fn_list, feat, local);

	अगर (new == शून्य)
		वापस DCCP_RESET_CODE_TOO_BUSY;

	new->feat_num	     = feat;
	new->is_local	     = local;
	new->state	     = FEAT_STABLE;	/* transition in 6.6.2 */
	new->needs_confirm   = true;
	new->empty_confirm   = (fval == शून्य);
	new->val.nn	     = 0;		/* zeroes the whole काष्ठाure */
	अगर (!new->empty_confirm)
		new->val     = *fval;
	new->needs_mandatory = false;

	वापस 0;
पूर्ण

अटल पूर्णांक dccp_push_empty_confirm(काष्ठा list_head *fn_list, u8 feat, u8 local)
अणु
	वापस dccp_feat_push_confirm(fn_list, feat, local, शून्य);
पूर्ण

अटल अंतरभूत व्योम dccp_feat_list_pop(काष्ठा dccp_feat_entry *entry)
अणु
	list_del(&entry->node);
	dccp_feat_entry_deकाष्ठाor(entry);
पूर्ण

व्योम dccp_feat_list_purge(काष्ठा list_head *fn_list)
अणु
	काष्ठा dccp_feat_entry *entry, *next;

	list_क्रम_each_entry_safe(entry, next, fn_list, node)
		dccp_feat_entry_deकाष्ठाor(entry);
	INIT_LIST_HEAD(fn_list);
पूर्ण
EXPORT_SYMBOL_GPL(dccp_feat_list_purge);

/* generate @to as full clone of @from - @to must not contain any nodes */
पूर्णांक dccp_feat_clone_list(काष्ठा list_head स्थिर *from, काष्ठा list_head *to)
अणु
	काष्ठा dccp_feat_entry *entry, *new;

	INIT_LIST_HEAD(to);
	list_क्रम_each_entry(entry, from, node) अणु
		new = dccp_feat_clone_entry(entry);
		अगर (new == शून्य)
			जाओ cloning_failed;
		list_add_tail(&new->node, to);
	पूर्ण
	वापस 0;

cloning_failed:
	dccp_feat_list_purge(to);
	वापस -ENOMEM;
पूर्ण

/**
 * dccp_feat_valid_nn_length  -  Enक्रमce length स्थिरraपूर्णांकs on NN options
 * @feat_num: feature to वापस length of, one of %dccp_feature_numbers
 *
 * Length is between 0 and %DCCP_OPTVAL_MAXLEN. Used क्रम outgoing packets only,
 * incoming options are accepted as दीर्घ as their values are valid.
 */
अटल u8 dccp_feat_valid_nn_length(u8 feat_num)
अणु
	अगर (feat_num == DCCPF_ACK_RATIO)	/* RFC 4340, 11.3 and 6.6.8 */
		वापस 2;
	अगर (feat_num == DCCPF_SEQUENCE_WINDOW)	/* RFC 4340, 7.5.2 and 6.5  */
		वापस 6;
	वापस 0;
पूर्ण

अटल u8 dccp_feat_is_valid_nn_val(u8 feat_num, u64 val)
अणु
	चयन (feat_num) अणु
	हाल DCCPF_ACK_RATIO:
		वापस val <= DCCPF_ACK_RATIO_MAX;
	हाल DCCPF_SEQUENCE_WINDOW:
		वापस val >= DCCPF_SEQ_WMIN && val <= DCCPF_SEQ_WMAX;
	पूर्ण
	वापस 0;	/* feature unknown - so we can't tell */
पूर्ण

/* check that SP values are within the ranges defined in RFC 4340 */
अटल u8 dccp_feat_is_valid_sp_val(u8 feat_num, u8 val)
अणु
	चयन (feat_num) अणु
	हाल DCCPF_CCID:
		वापस val == DCCPC_CCID2 || val == DCCPC_CCID3;
	/* Type-check Boolean feature values: */
	हाल DCCPF_SHORT_SEQNOS:
	हाल DCCPF_ECN_INCAPABLE:
	हाल DCCPF_SEND_ACK_VECTOR:
	हाल DCCPF_SEND_NDP_COUNT:
	हाल DCCPF_DATA_CHECKSUM:
	हाल DCCPF_SEND_LEV_RATE:
		वापस val < 2;
	हाल DCCPF_MIN_CSUM_COVER:
		वापस val < 16;
	पूर्ण
	वापस 0;			/* feature unknown */
पूर्ण

अटल u8 dccp_feat_sp_list_ok(u8 feat_num, u8 स्थिर *sp_list, u8 sp_len)
अणु
	अगर (sp_list == शून्य || sp_len < 1)
		वापस 0;
	जबतक (sp_len--)
		अगर (!dccp_feat_is_valid_sp_val(feat_num, *sp_list++))
			वापस 0;
	वापस 1;
पूर्ण

/**
 * dccp_feat_insert_opts  -  Generate FN options from current list state
 * @skb: next sk_buff to be sent to the peer
 * @dp: क्रम client during handshake and general negotiation
 * @dreq: used by the server only (all Changes/Confirms in LISTEN/RESPOND)
 */
पूर्णांक dccp_feat_insert_opts(काष्ठा dccp_sock *dp, काष्ठा dccp_request_sock *dreq,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा list_head *fn = dreq ? &dreq->dreq_featneg : &dp->dccps_featneg;
	काष्ठा dccp_feat_entry *pos, *next;
	u8 opt, type, len, *ptr, nn_in_nbo[DCCP_OPTVAL_MAXLEN];
	bool rpt;

	/* put entries पूर्णांकo @skb in the order they appear in the list */
	list_क्रम_each_entry_safe_reverse(pos, next, fn, node) अणु
		opt  = dccp_feat_genopt(pos);
		type = dccp_feat_type(pos->feat_num);
		rpt  = false;

		अगर (pos->empty_confirm) अणु
			len = 0;
			ptr = शून्य;
		पूर्ण अन्यथा अणु
			अगर (type == FEAT_SP) अणु
				len = pos->val.sp.len;
				ptr = pos->val.sp.vec;
				rpt = pos->needs_confirm;
			पूर्ण अन्यथा अगर (type == FEAT_NN) अणु
				len = dccp_feat_valid_nn_length(pos->feat_num);
				ptr = nn_in_nbo;
				dccp_encode_value_var(pos->val.nn, ptr, len);
			पूर्ण अन्यथा अणु
				DCCP_BUG("unknown feature %u", pos->feat_num);
				वापस -1;
			पूर्ण
		पूर्ण
		dccp_feat_prपूर्णांक_opt(opt, pos->feat_num, ptr, len, 0);

		अगर (dccp_insert_fn_opt(skb, opt, pos->feat_num, ptr, len, rpt))
			वापस -1;
		अगर (pos->needs_mandatory && dccp_insert_option_mandatory(skb))
			वापस -1;

		अगर (skb->sk->sk_state == DCCP_OPEN &&
		    (opt == DCCPO_CONFIRM_R || opt == DCCPO_CONFIRM_L)) अणु
			/*
			 * Confirms करोn't get retransmitted (6.6.3) once the
			 * connection is in state OPEN
			 */
			dccp_feat_list_pop(pos);
		पूर्ण अन्यथा अणु
			/*
			 * Enter CHANGING after transmitting the Change
			 * option (6.6.2).
			 */
			अगर (pos->state == FEAT_INITIALISING)
				pos->state = FEAT_CHANGING;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * __feat_रेजिस्टर_nn  -  Register new NN value on socket
 * @fn: feature-negotiation list to रेजिस्टर with
 * @feat: an NN feature from %dccp_feature_numbers
 * @mandatory: use Mandatory option अगर 1
 * @nn_val: value to रेजिस्टर (restricted to 4 bytes)
 *
 * Note that NN features are local by definition (RFC 4340, 6.3.2).
 */
अटल पूर्णांक __feat_रेजिस्टर_nn(काष्ठा list_head *fn, u8 feat,
			      u8 mandatory, u64 nn_val)
अणु
	dccp_feat_val fval = अणु .nn = nn_val पूर्ण;

	अगर (dccp_feat_type(feat) != FEAT_NN ||
	    !dccp_feat_is_valid_nn_val(feat, nn_val))
		वापस -EINVAL;

	/* Don't bother with शेष values, they will be activated anyway. */
	अगर (nn_val - (u64)dccp_feat_शेष_value(feat) == 0)
		वापस 0;

	वापस dccp_feat_push_change(fn, feat, 1, mandatory, &fval);
पूर्ण

/**
 * __feat_रेजिस्टर_sp  -  Register new SP value/list on socket
 * @fn: feature-negotiation list to रेजिस्टर with
 * @feat: an SP feature from %dccp_feature_numbers
 * @is_local: whether the local (1) or the remote (0) @feat is meant
 * @mandatory: use Mandatory option अगर 1
 * @sp_val: SP value followed by optional preference list
 * @sp_len: length of @sp_val in bytes
 */
अटल पूर्णांक __feat_रेजिस्टर_sp(काष्ठा list_head *fn, u8 feat, u8 is_local,
			      u8 mandatory, u8 स्थिर *sp_val, u8 sp_len)
अणु
	dccp_feat_val fval;

	अगर (dccp_feat_type(feat) != FEAT_SP ||
	    !dccp_feat_sp_list_ok(feat, sp_val, sp_len))
		वापस -EINVAL;

	/* Aव्योम negotiating alien CCIDs by only advertising supported ones */
	अगर (feat == DCCPF_CCID && !ccid_support_check(sp_val, sp_len))
		वापस -EOPNOTSUPP;

	अगर (dccp_feat_clone_sp_val(&fval, sp_val, sp_len))
		वापस -ENOMEM;

	अगर (dccp_feat_push_change(fn, feat, is_local, mandatory, &fval)) अणु
		kमुक्त(fval.sp.vec);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dccp_feat_रेजिस्टर_sp  -  Register requests to change SP feature values
 * @sk: client or listening socket
 * @feat: one of %dccp_feature_numbers
 * @is_local: whether the local (1) or remote (0) @feat is meant
 * @list: array of preferred values, in descending order of preference
 * @len: length of @list in bytes
 */
पूर्णांक dccp_feat_रेजिस्टर_sp(काष्ठा sock *sk, u8 feat, u8 is_local,
			  u8 स्थिर *list, u8 len)
अणु	 /* any changes must be रेजिस्टरed beक्रमe establishing the connection */
	अगर (sk->sk_state != DCCP_CLOSED)
		वापस -EISCONN;
	अगर (dccp_feat_type(feat) != FEAT_SP)
		वापस -EINVAL;
	वापस __feat_रेजिस्टर_sp(&dccp_sk(sk)->dccps_featneg, feat, is_local,
				  0, list, len);
पूर्ण

/**
 * dccp_feat_nn_get  -  Query current/pending value of NN feature
 * @sk: DCCP socket of an established connection
 * @feat: NN feature number from %dccp_feature_numbers
 *
 * For a known NN feature, वापसs value currently being negotiated, or
 * current (confirmed) value अगर no negotiation is going on.
 */
u64 dccp_feat_nn_get(काष्ठा sock *sk, u8 feat)
अणु
	अगर (dccp_feat_type(feat) == FEAT_NN) अणु
		काष्ठा dccp_sock *dp = dccp_sk(sk);
		काष्ठा dccp_feat_entry *entry;

		entry = dccp_feat_list_lookup(&dp->dccps_featneg, feat, 1);
		अगर (entry != शून्य)
			वापस entry->val.nn;

		चयन (feat) अणु
		हाल DCCPF_ACK_RATIO:
			वापस dp->dccps_l_ack_ratio;
		हाल DCCPF_SEQUENCE_WINDOW:
			वापस dp->dccps_l_seq_win;
		पूर्ण
	पूर्ण
	DCCP_BUG("attempt to look up unsupported feature %u", feat);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_feat_nn_get);

/**
 * dccp_feat_संकेत_nn_change  -  Update NN values क्रम an established connection
 * @sk: DCCP socket of an established connection
 * @feat: NN feature number from %dccp_feature_numbers
 * @nn_val: the new value to use
 *
 * This function is used to communicate NN updates out-of-band.
 */
पूर्णांक dccp_feat_संकेत_nn_change(काष्ठा sock *sk, u8 feat, u64 nn_val)
अणु
	काष्ठा list_head *fn = &dccp_sk(sk)->dccps_featneg;
	dccp_feat_val fval = अणु .nn = nn_val पूर्ण;
	काष्ठा dccp_feat_entry *entry;

	अगर (sk->sk_state != DCCP_OPEN && sk->sk_state != DCCP_PARTOPEN)
		वापस 0;

	अगर (dccp_feat_type(feat) != FEAT_NN ||
	    !dccp_feat_is_valid_nn_val(feat, nn_val))
		वापस -EINVAL;

	अगर (nn_val == dccp_feat_nn_get(sk, feat))
		वापस 0;	/* alपढ़ोy set or negotiation under way */

	entry = dccp_feat_list_lookup(fn, feat, 1);
	अगर (entry != शून्य) अणु
		dccp_pr_debug("Clobbering existing NN entry %llu -> %llu\n",
			      (अचिन्हित दीर्घ दीर्घ)entry->val.nn,
			      (अचिन्हित दीर्घ दीर्घ)nn_val);
		dccp_feat_list_pop(entry);
	पूर्ण

	inet_csk_schedule_ack(sk);
	वापस dccp_feat_push_change(fn, feat, 1, 0, &fval);
पूर्ण
EXPORT_SYMBOL_GPL(dccp_feat_संकेत_nn_change);

/*
 *	Tracking features whose value depend on the choice of CCID
 *
 * This is deचिन्हित with an extension in mind so that a list walk could be करोne
 * beक्रमe activating any features. However, the existing framework was found to
 * work satisfactorily up until now, the स्वतःmatic verअगरication is left खोलो.
 * When adding new CCIDs, add a corresponding dependency table here.
 */
अटल स्थिर काष्ठा ccid_dependency *dccp_feat_ccid_deps(u8 ccid, bool is_local)
अणु
	अटल स्थिर काष्ठा ccid_dependency ccid2_dependencies[2][2] = अणु
		/*
		 * CCID2 mandates Ack Vectors (RFC 4341, 4.): as CCID is a TX
		 * feature and Send Ack Vector is an RX feature, `is_local'
		 * needs to be reversed.
		 */
		अणु	/* Dependencies of the receiver-side (remote) CCID2 */
			अणु
				.dependent_feat	= DCCPF_SEND_ACK_VECTOR,
				.is_local	= true,
				.is_mandatory	= true,
				.val		= 1
			पूर्ण,
			अणु 0, 0, 0, 0 पूर्ण
		पूर्ण,
		अणु	/* Dependencies of the sender-side (local) CCID2 */
			अणु
				.dependent_feat	= DCCPF_SEND_ACK_VECTOR,
				.is_local	= false,
				.is_mandatory	= true,
				.val		= 1
			पूर्ण,
			अणु 0, 0, 0, 0 पूर्ण
		पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा ccid_dependency ccid3_dependencies[2][5] = अणु
		अणु	/*
			 * Dependencies of the receiver-side CCID3
			 */
			अणु	/* locally disable Ack Vectors */
				.dependent_feat	= DCCPF_SEND_ACK_VECTOR,
				.is_local	= true,
				.is_mandatory	= false,
				.val		= 0
			पूर्ण,
			अणु	/* see below why Send Loss Event Rate is on */
				.dependent_feat	= DCCPF_SEND_LEV_RATE,
				.is_local	= true,
				.is_mandatory	= true,
				.val		= 1
			पूर्ण,
			अणु	/* NDP Count is needed as per RFC 4342, 6.1.1 */
				.dependent_feat	= DCCPF_SEND_NDP_COUNT,
				.is_local	= false,
				.is_mandatory	= true,
				.val		= 1
			पूर्ण,
			अणु 0, 0, 0, 0 पूर्ण,
		पूर्ण,
		अणु	/*
			 * CCID3 at the TX side: we request that the HC-receiver
			 * will not send Ack Vectors (they will be ignored, so
			 * Mandatory is not set); we enable Send Loss Event Rate
			 * (Mandatory since the implementation करोes not support
			 * the Loss Intervals option of RFC 4342, 8.6).
			 * The last two options are क्रम peer's inक्रमmation only.
			*/
			अणु
				.dependent_feat	= DCCPF_SEND_ACK_VECTOR,
				.is_local	= false,
				.is_mandatory	= false,
				.val		= 0
			पूर्ण,
			अणु
				.dependent_feat	= DCCPF_SEND_LEV_RATE,
				.is_local	= false,
				.is_mandatory	= true,
				.val		= 1
			पूर्ण,
			अणु	/* this CCID करोes not support Ack Ratio */
				.dependent_feat	= DCCPF_ACK_RATIO,
				.is_local	= true,
				.is_mandatory	= false,
				.val		= 0
			पूर्ण,
			अणु	/* tell receiver we are sending NDP counts */
				.dependent_feat	= DCCPF_SEND_NDP_COUNT,
				.is_local	= true,
				.is_mandatory	= false,
				.val		= 1
			पूर्ण,
			अणु 0, 0, 0, 0 पूर्ण
		पूर्ण
	पूर्ण;
	चयन (ccid) अणु
	हाल DCCPC_CCID2:
		वापस ccid2_dependencies[is_local];
	हाल DCCPC_CCID3:
		वापस ccid3_dependencies[is_local];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * dccp_feat_propagate_ccid - Resolve dependencies of features on choice of CCID
 * @fn: feature-negotiation list to update
 * @id: CCID number to track
 * @is_local: whether TX CCID (1) or RX CCID (0) is meant
 *
 * This function needs to be called after रेजिस्टरing all other features.
 */
अटल पूर्णांक dccp_feat_propagate_ccid(काष्ठा list_head *fn, u8 id, bool is_local)
अणु
	स्थिर काष्ठा ccid_dependency *table = dccp_feat_ccid_deps(id, is_local);
	पूर्णांक i, rc = (table == शून्य);

	क्रम (i = 0; rc == 0 && table[i].dependent_feat != DCCPF_RESERVED; i++)
		अगर (dccp_feat_type(table[i].dependent_feat) == FEAT_SP)
			rc = __feat_रेजिस्टर_sp(fn, table[i].dependent_feat,
						    table[i].is_local,
						    table[i].is_mandatory,
						    &table[i].val, 1);
		अन्यथा
			rc = __feat_रेजिस्टर_nn(fn, table[i].dependent_feat,
						    table[i].is_mandatory,
						    table[i].val);
	वापस rc;
पूर्ण

/**
 * dccp_feat_finalise_settings  -  Finalise settings beक्रमe starting negotiation
 * @dp: client or listening socket (settings will be inherited)
 *
 * This is called after all registrations (socket initialisation, sysctls, and
 * sockopt calls), and beक्रमe sending the first packet containing Change options
 * (ie. client-Request or server-Response), to ensure पूर्णांकernal consistency.
 */
पूर्णांक dccp_feat_finalise_settings(काष्ठा dccp_sock *dp)
अणु
	काष्ठा list_head *fn = &dp->dccps_featneg;
	काष्ठा dccp_feat_entry *entry;
	पूर्णांक i = 2, ccids[2] = अणु -1, -1 पूर्ण;

	/*
	 * Propagating CCIDs:
	 * 1) not useful to propagate CCID settings अगर this host advertises more
	 *    than one CCID: the choice of CCID  may still change - अगर this is
	 *    the client, or अगर this is the server and the client sends
	 *    singleton CCID values.
	 * 2) since is that propagate_ccid changes the list, we defer changing
	 *    the sorted list until after the traversal.
	 */
	list_क्रम_each_entry(entry, fn, node)
		अगर (entry->feat_num == DCCPF_CCID && entry->val.sp.len == 1)
			ccids[entry->is_local] = entry->val.sp.vec[0];
	जबतक (i--)
		अगर (ccids[i] > 0 && dccp_feat_propagate_ccid(fn, ccids[i], i))
			वापस -1;
	dccp_feat_prपूर्णांक_fnlist(fn);
	वापस 0;
पूर्ण

/**
 * dccp_feat_server_ccid_dependencies  -  Resolve CCID-dependent features
 * @dreq: server socket to resolve
 *
 * It is the server which resolves the dependencies once the CCID has been
 * fully negotiated. If no CCID has been negotiated, it uses the शेष CCID.
 */
पूर्णांक dccp_feat_server_ccid_dependencies(काष्ठा dccp_request_sock *dreq)
अणु
	काष्ठा list_head *fn = &dreq->dreq_featneg;
	काष्ठा dccp_feat_entry *entry;
	u8 is_local, ccid;

	क्रम (is_local = 0; is_local <= 1; is_local++) अणु
		entry = dccp_feat_list_lookup(fn, DCCPF_CCID, is_local);

		अगर (entry != शून्य && !entry->empty_confirm)
			ccid = entry->val.sp.vec[0];
		अन्यथा
			ccid = dccp_feat_शेष_value(DCCPF_CCID);

		अगर (dccp_feat_propagate_ccid(fn, ccid, is_local))
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* Select the first entry in @servlist that also occurs in @clilist (6.3.1) */
अटल पूर्णांक dccp_feat_preflist_match(u8 *servlist, u8 slen, u8 *clilist, u8 clen)
अणु
	u8 c, s;

	क्रम (s = 0; s < slen; s++)
		क्रम (c = 0; c < clen; c++)
			अगर (servlist[s] == clilist[c])
				वापस servlist[s];
	वापस -1;
पूर्ण

/**
 * dccp_feat_prefer  -  Move preferred entry to the start of array
 * @preferred_value: entry to move to start of array
 * @array: array of preferred entries
 * @array_len: size of the array
 *
 * Reorder the @array_len elements in @array so that @preferred_value comes
 * first. Returns >0 to indicate that @preferred_value करोes occur in @array.
 */
अटल u8 dccp_feat_prefer(u8 preferred_value, u8 *array, u8 array_len)
अणु
	u8 i, करोes_occur = 0;

	अगर (array != शून्य) अणु
		क्रम (i = 0; i < array_len; i++)
			अगर (array[i] == preferred_value) अणु
				array[i] = array[0];
				करोes_occur++;
			पूर्ण
		अगर (करोes_occur)
			array[0] = preferred_value;
	पूर्ण
	वापस करोes_occur;
पूर्ण

/**
 * dccp_feat_reconcile  -  Reconcile SP preference lists
 *  @fv: SP list to reconcile पूर्णांकo
 *  @arr: received SP preference list
 *  @len: length of @arr in bytes
 *  @is_server: whether this side is the server (and @fv is the server's list)
 *  @reorder: whether to reorder the list in @fv after reconciling with @arr
 * When successful, > 0 is वापसed and the reconciled list is in @fval.
 * A value of 0 means that negotiation failed (no shared entry).
 */
अटल पूर्णांक dccp_feat_reconcile(dccp_feat_val *fv, u8 *arr, u8 len,
			       bool is_server, bool reorder)
अणु
	पूर्णांक rc;

	अगर (!fv->sp.vec || !arr) अणु
		DCCP_CRIT("NULL feature value or array");
		वापस 0;
	पूर्ण

	अगर (is_server)
		rc = dccp_feat_preflist_match(fv->sp.vec, fv->sp.len, arr, len);
	अन्यथा
		rc = dccp_feat_preflist_match(arr, len, fv->sp.vec, fv->sp.len);

	अगर (!reorder)
		वापस rc;
	अगर (rc < 0)
		वापस 0;

	/*
	 * Reorder list: used क्रम activating features and in dccp_insert_fn_opt.
	 */
	वापस dccp_feat_prefer(rc, fv->sp.vec, fv->sp.len);
पूर्ण

/**
 * dccp_feat_change_recv  -  Process incoming ChangeL/R options
 * @fn: feature-negotiation list to update
 * @is_mandatory: whether the Change was preceded by a Mandatory option
 * @opt: %DCCPO_CHANGE_L or %DCCPO_CHANGE_R
 * @feat: one of %dccp_feature_numbers
 * @val: NN value or SP value/preference list
 * @len: length of @val in bytes
 * @server: whether this node is the server (1) or the client (0)
 */
अटल u8 dccp_feat_change_recv(काष्ठा list_head *fn, u8 is_mandatory, u8 opt,
				u8 feat, u8 *val, u8 len, स्थिर bool server)
अणु
	u8 defval, type = dccp_feat_type(feat);
	स्थिर bool local = (opt == DCCPO_CHANGE_R);
	काष्ठा dccp_feat_entry *entry;
	dccp_feat_val fval;

	अगर (len == 0 || type == FEAT_UNKNOWN)		/* 6.1 and 6.6.8 */
		जाओ unknown_feature_or_value;

	dccp_feat_prपूर्णांक_opt(opt, feat, val, len, is_mandatory);

	/*
	 *	Negotiation of NN features: Change R is invalid, so there is no
	 *	simultaneous negotiation; hence we करो not look up in the list.
	 */
	अगर (type == FEAT_NN) अणु
		अगर (local || len > माप(fval.nn))
			जाओ unknown_feature_or_value;

		/* 6.3.2: "The feature remote MUST accept any valid value..." */
		fval.nn = dccp_decode_value_var(val, len);
		अगर (!dccp_feat_is_valid_nn_val(feat, fval.nn))
			जाओ unknown_feature_or_value;

		वापस dccp_feat_push_confirm(fn, feat, local, &fval);
	पूर्ण

	/*
	 *	Unidirectional/simultaneous negotiation of SP features (6.3.1)
	 */
	entry = dccp_feat_list_lookup(fn, feat, local);
	अगर (entry == शून्य) अणु
		/*
		 * No particular preferences have been रेजिस्टरed. We deal with
		 * this situation by assuming that all valid values are equally
		 * acceptable, and apply the following checks:
		 * - अगर the peer's list is a singleton, we accept a valid value;
		 * - अगर we are the server, we first try to see अगर the peer (the
		 *   client) advertises the शेष value. If yes, we use it,
		 *   otherwise we accept the preferred value;
		 * - अन्यथा अगर we are the client, we use the first list element.
		 */
		अगर (dccp_feat_clone_sp_val(&fval, val, 1))
			वापस DCCP_RESET_CODE_TOO_BUSY;

		अगर (len > 1 && server) अणु
			defval = dccp_feat_शेष_value(feat);
			अगर (dccp_feat_preflist_match(&defval, 1, val, len) > -1)
				fval.sp.vec[0] = defval;
		पूर्ण अन्यथा अगर (!dccp_feat_is_valid_sp_val(feat, fval.sp.vec[0])) अणु
			kमुक्त(fval.sp.vec);
			जाओ unknown_feature_or_value;
		पूर्ण

		/* Treat unsupported CCIDs like invalid values */
		अगर (feat == DCCPF_CCID && !ccid_support_check(fval.sp.vec, 1)) अणु
			kमुक्त(fval.sp.vec);
			जाओ not_valid_or_not_known;
		पूर्ण

		वापस dccp_feat_push_confirm(fn, feat, local, &fval);

	पूर्ण अन्यथा अगर (entry->state == FEAT_UNSTABLE) अणु	/* 6.6.2 */
		वापस 0;
	पूर्ण

	अगर (dccp_feat_reconcile(&entry->val, val, len, server, true)) अणु
		entry->empty_confirm = false;
	पूर्ण अन्यथा अगर (is_mandatory) अणु
		वापस DCCP_RESET_CODE_MANDATORY_ERROR;
	पूर्ण अन्यथा अगर (entry->state == FEAT_INITIALISING) अणु
		/*
		 * Failed simultaneous negotiation (server only): try to `save'
		 * the connection by checking whether entry contains the शेष
		 * value क्रम @feat. If yes, send an empty Confirm to संकेत that
		 * the received Change was not understood - which implies using
		 * the शेष value.
		 * If this also fails, we use Reset as the last resort.
		 */
		WARN_ON(!server);
		defval = dccp_feat_शेष_value(feat);
		अगर (!dccp_feat_reconcile(&entry->val, &defval, 1, server, true))
			वापस DCCP_RESET_CODE_OPTION_ERROR;
		entry->empty_confirm = true;
	पूर्ण
	entry->needs_confirm   = true;
	entry->needs_mandatory = false;
	entry->state	       = FEAT_STABLE;
	वापस 0;

unknown_feature_or_value:
	अगर (!is_mandatory)
		वापस dccp_push_empty_confirm(fn, feat, local);

not_valid_or_not_known:
	वापस is_mandatory ? DCCP_RESET_CODE_MANDATORY_ERROR
			    : DCCP_RESET_CODE_OPTION_ERROR;
पूर्ण

/**
 * dccp_feat_confirm_recv  -  Process received Confirm options
 * @fn: feature-negotiation list to update
 * @is_mandatory: whether @opt was preceded by a Mandatory option
 * @opt: %DCCPO_CONFIRM_L or %DCCPO_CONFIRM_R
 * @feat: one of %dccp_feature_numbers
 * @val: NN value or SP value/preference list
 * @len: length of @val in bytes
 * @server: whether this node is server (1) or client (0)
 */
अटल u8 dccp_feat_confirm_recv(काष्ठा list_head *fn, u8 is_mandatory, u8 opt,
				 u8 feat, u8 *val, u8 len, स्थिर bool server)
अणु
	u8 *plist, plen, type = dccp_feat_type(feat);
	स्थिर bool local = (opt == DCCPO_CONFIRM_R);
	काष्ठा dccp_feat_entry *entry = dccp_feat_list_lookup(fn, feat, local);

	dccp_feat_prपूर्णांक_opt(opt, feat, val, len, is_mandatory);

	अगर (entry == शून्य) अणु	/* nothing queued: ignore or handle error */
		अगर (is_mandatory && type == FEAT_UNKNOWN)
			वापस DCCP_RESET_CODE_MANDATORY_ERROR;

		अगर (!local && type == FEAT_NN)		/* 6.3.2 */
			जाओ confirmation_failed;
		वापस 0;
	पूर्ण

	अगर (entry->state != FEAT_CHANGING)		/* 6.6.2 */
		वापस 0;

	अगर (len == 0) अणु
		अगर (dccp_feat_must_be_understood(feat))	/* 6.6.7 */
			जाओ confirmation_failed;
		/*
		 * Empty Confirm during connection setup: this means reverting
		 * to the `old' value, which in this हाल is the शेष. Since
		 * we handle शेष values स्वतःmatically when no other values
		 * have been set, we revert to the old value by removing this
		 * entry from the list.
		 */
		dccp_feat_list_pop(entry);
		वापस 0;
	पूर्ण

	अगर (type == FEAT_NN) अणु
		अगर (len > माप(entry->val.nn))
			जाओ confirmation_failed;

		अगर (entry->val.nn == dccp_decode_value_var(val, len))
			जाओ confirmation_succeeded;

		DCCP_WARN("Bogus Confirm for non-existing value\n");
		जाओ confirmation_failed;
	पूर्ण

	/*
	 * Parsing SP Confirms: the first element of @val is the preferred
	 * SP value which the peer confirms, the reमुख्यder depends on @len.
	 * Note that only the confirmed value need to be a valid SP value.
	 */
	अगर (!dccp_feat_is_valid_sp_val(feat, *val))
		जाओ confirmation_failed;

	अगर (len == 1) अणु		/* peer didn't supply a preference list */
		plist = val;
		plen  = len;
	पूर्ण अन्यथा अणु		/* preferred value + preference list */
		plist = val + 1;
		plen  = len - 1;
	पूर्ण

	/* Check whether the peer got the reconciliation right (6.6.8) */
	अगर (dccp_feat_reconcile(&entry->val, plist, plen, server, 0) != *val) अणु
		DCCP_WARN("Confirm selected the wrong value %u\n", *val);
		वापस DCCP_RESET_CODE_OPTION_ERROR;
	पूर्ण
	entry->val.sp.vec[0] = *val;

confirmation_succeeded:
	entry->state = FEAT_STABLE;
	वापस 0;

confirmation_failed:
	DCCP_WARN("Confirmation failed\n");
	वापस is_mandatory ? DCCP_RESET_CODE_MANDATORY_ERROR
			    : DCCP_RESET_CODE_OPTION_ERROR;
पूर्ण

/**
 * dccp_feat_handle_nn_established  -  Fast-path reception of NN options
 * @sk:		socket of an established DCCP connection
 * @mandatory:	whether @opt was preceded by a Mandatory option
 * @opt:	%DCCPO_CHANGE_L | %DCCPO_CONFIRM_R (NN only)
 * @feat:	NN number, one of %dccp_feature_numbers
 * @val:	NN value
 * @len:	length of @val in bytes
 *
 * This function combines the functionality of change_recv/confirm_recv, with
 * the following dअगरferences (reset codes are the same):
 *    - cleanup after receiving the Confirm;
 *    - values are directly activated after successful parsing;
 *    - deliberately restricted to NN features.
 * The restriction to NN features is essential since SP features can have non-
 * predictable outcomes (depending on the remote configuration), and are पूर्णांकer-
 * dependent (CCIDs क्रम instance cause further dependencies).
 */
अटल u8 dccp_feat_handle_nn_established(काष्ठा sock *sk, u8 mandatory, u8 opt,
					  u8 feat, u8 *val, u8 len)
अणु
	काष्ठा list_head *fn = &dccp_sk(sk)->dccps_featneg;
	स्थिर bool local = (opt == DCCPO_CONFIRM_R);
	काष्ठा dccp_feat_entry *entry;
	u8 type = dccp_feat_type(feat);
	dccp_feat_val fval;

	dccp_feat_prपूर्णांक_opt(opt, feat, val, len, mandatory);

	/* Ignore non-mandatory unknown and non-NN features */
	अगर (type == FEAT_UNKNOWN) अणु
		अगर (local && !mandatory)
			वापस 0;
		जाओ fast_path_unknown;
	पूर्ण अन्यथा अगर (type != FEAT_NN) अणु
		वापस 0;
	पूर्ण

	/*
	 * We करोn't accept empty Confirms, since in fast-path feature
	 * negotiation the values are enabled immediately after sending
	 * the Change option.
	 * Empty Changes on the other hand are invalid (RFC 4340, 6.1).
	 */
	अगर (len == 0 || len > माप(fval.nn))
		जाओ fast_path_unknown;

	अगर (opt == DCCPO_CHANGE_L) अणु
		fval.nn = dccp_decode_value_var(val, len);
		अगर (!dccp_feat_is_valid_nn_val(feat, fval.nn))
			जाओ fast_path_unknown;

		अगर (dccp_feat_push_confirm(fn, feat, local, &fval) ||
		    dccp_feat_activate(sk, feat, local, &fval))
			वापस DCCP_RESET_CODE_TOO_BUSY;

		/* set the `Ack Pending' flag to piggyback a Confirm */
		inet_csk_schedule_ack(sk);

	पूर्ण अन्यथा अगर (opt == DCCPO_CONFIRM_R) अणु
		entry = dccp_feat_list_lookup(fn, feat, local);
		अगर (entry == शून्य || entry->state != FEAT_CHANGING)
			वापस 0;

		fval.nn = dccp_decode_value_var(val, len);
		/*
		 * Just ignore a value that करोesn't match our current value.
		 * If the option changes twice within two RTTs, then at least
		 * one CONFIRM will be received क्रम the old value after a
		 * new CHANGE was sent.
		 */
		अगर (fval.nn != entry->val.nn)
			वापस 0;

		/* Only activate after receiving the Confirm option (6.6.1). */
		dccp_feat_activate(sk, feat, local, &fval);

		/* It has been confirmed - so हटाओ the entry */
		dccp_feat_list_pop(entry);

	पूर्ण अन्यथा अणु
		DCCP_WARN("Received illegal option %u\n", opt);
		जाओ fast_path_failed;
	पूर्ण
	वापस 0;

fast_path_unknown:
	अगर (!mandatory)
		वापस dccp_push_empty_confirm(fn, feat, local);

fast_path_failed:
	वापस mandatory ? DCCP_RESET_CODE_MANDATORY_ERROR
			 : DCCP_RESET_CODE_OPTION_ERROR;
पूर्ण

/**
 * dccp_feat_parse_options  -  Process Feature-Negotiation Options
 * @sk: क्रम general use and used by the client during connection setup
 * @dreq: used by the server during connection setup
 * @mandatory: whether @opt was preceded by a Mandatory option
 * @opt: %DCCPO_CHANGE_L | %DCCPO_CHANGE_R | %DCCPO_CONFIRM_L | %DCCPO_CONFIRM_R
 * @feat: one of %dccp_feature_numbers
 * @val: value contents of @opt
 * @len: length of @val in bytes
 *
 * Returns 0 on success, a Reset code क्रम ending the connection otherwise.
 */
पूर्णांक dccp_feat_parse_options(काष्ठा sock *sk, काष्ठा dccp_request_sock *dreq,
			    u8 mandatory, u8 opt, u8 feat, u8 *val, u8 len)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा list_head *fn = dreq ? &dreq->dreq_featneg : &dp->dccps_featneg;
	bool server = false;

	चयन (sk->sk_state) अणु
	/*
	 *	Negotiation during connection setup
	 */
	हाल DCCP_LISTEN:
		server = true;
		fallthrough;
	हाल DCCP_REQUESTING:
		चयन (opt) अणु
		हाल DCCPO_CHANGE_L:
		हाल DCCPO_CHANGE_R:
			वापस dccp_feat_change_recv(fn, mandatory, opt, feat,
						     val, len, server);
		हाल DCCPO_CONFIRM_R:
		हाल DCCPO_CONFIRM_L:
			वापस dccp_feat_confirm_recv(fn, mandatory, opt, feat,
						      val, len, server);
		पूर्ण
		अवरोध;
	/*
	 *	Support क्रम exchanging NN options on an established connection.
	 */
	हाल DCCP_OPEN:
	हाल DCCP_PARTOPEN:
		वापस dccp_feat_handle_nn_established(sk, mandatory, opt, feat,
						       val, len);
	पूर्ण
	वापस 0;	/* ignore FN options in all other states */
पूर्ण

/**
 * dccp_feat_init  -  Seed feature negotiation with host-specअगरic शेषs
 * @sk: Socket to initialize.
 *
 * This initialises global शेषs, depending on the value of the sysctls.
 * These can later be overridden by रेजिस्टरing changes via setsockopt calls.
 * The last link in the chain is finalise_settings, to make sure that between
 * here and the start of actual feature negotiation no inconsistencies enter.
 *
 * All features not appearing below use either शेषs or are otherwise
 * later adjusted through dccp_feat_finalise_settings().
 */
पूर्णांक dccp_feat_init(काष्ठा sock *sk)
अणु
	काष्ठा list_head *fn = &dccp_sk(sk)->dccps_featneg;
	u8 on = 1, off = 0;
	पूर्णांक rc;
	काष्ठा अणु
		u8 *val;
		u8 len;
	पूर्ण tx, rx;

	/* Non-negotiable (NN) features */
	rc = __feat_रेजिस्टर_nn(fn, DCCPF_SEQUENCE_WINDOW, 0,
				    sysctl_dccp_sequence_winकरोw);
	अगर (rc)
		वापस rc;

	/* Server-priority (SP) features */

	/* Advertise that लघु seqnos are not supported (7.6.1) */
	rc = __feat_रेजिस्टर_sp(fn, DCCPF_SHORT_SEQNOS, true, true, &off, 1);
	अगर (rc)
		वापस rc;

	/* RFC 4340 12.1: "If a DCCP is not ECN capable, ..." */
	rc = __feat_रेजिस्टर_sp(fn, DCCPF_ECN_INCAPABLE, true, true, &on, 1);
	अगर (rc)
		वापस rc;

	/*
	 * We advertise the available list of CCIDs and reorder according to
	 * preferences, to aव्योम failure resulting from negotiating dअगरferent
	 * singleton values (which always leads to failure).
	 * These settings can still (later) be overridden via sockopts.
	 */
	अगर (ccid_get_builtin_ccids(&tx.val, &tx.len))
		वापस -ENOBUFS;
	अगर (ccid_get_builtin_ccids(&rx.val, &rx.len)) अणु
		kमुक्त(tx.val);
		वापस -ENOBUFS;
	पूर्ण

	अगर (!dccp_feat_prefer(sysctl_dccp_tx_ccid, tx.val, tx.len) ||
	    !dccp_feat_prefer(sysctl_dccp_rx_ccid, rx.val, rx.len))
		जाओ मुक्त_ccid_lists;

	rc = __feat_रेजिस्टर_sp(fn, DCCPF_CCID, true, false, tx.val, tx.len);
	अगर (rc)
		जाओ मुक्त_ccid_lists;

	rc = __feat_रेजिस्टर_sp(fn, DCCPF_CCID, false, false, rx.val, rx.len);

मुक्त_ccid_lists:
	kमुक्त(tx.val);
	kमुक्त(rx.val);
	वापस rc;
पूर्ण

पूर्णांक dccp_feat_activate_values(काष्ठा sock *sk, काष्ठा list_head *fn_list)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा dccp_feat_entry *cur, *next;
	पूर्णांक idx;
	dccp_feat_val *fvals[DCCP_FEAT_SUPPORTED_MAX][2] = अणु
		 [0 ... DCCP_FEAT_SUPPORTED_MAX-1] = अणु शून्य, शून्य पूर्ण
	पूर्ण;

	list_क्रम_each_entry(cur, fn_list, node) अणु
		/*
		 * An empty Confirm means that either an unknown feature type
		 * or an invalid value was present. In the first हाल there is
		 * nothing to activate, in the other the शेष value is used.
		 */
		अगर (cur->empty_confirm)
			जारी;

		idx = dccp_feat_index(cur->feat_num);
		अगर (idx < 0) अणु
			DCCP_BUG("Unknown feature %u", cur->feat_num);
			जाओ activation_failed;
		पूर्ण
		अगर (cur->state != FEAT_STABLE) अणु
			DCCP_CRIT("Negotiation of %s %s failed in state %s",
				  cur->is_local ? "local" : "remote",
				  dccp_feat_fname(cur->feat_num),
				  dccp_feat_sname[cur->state]);
			जाओ activation_failed;
		पूर्ण
		fvals[idx][cur->is_local] = &cur->val;
	पूर्ण

	/*
	 * Activate in decreasing order of index, so that the CCIDs are always
	 * activated as the last feature. This aव्योमs the हाल where a CCID
	 * relies on the initialisation of one or more features that it depends
	 * on (e.g. Send NDP Count, Send Ack Vector, and Ack Ratio features).
	 */
	क्रम (idx = DCCP_FEAT_SUPPORTED_MAX; --idx >= 0;)
		अगर (__dccp_feat_activate(sk, idx, 0, fvals[idx][0]) ||
		    __dccp_feat_activate(sk, idx, 1, fvals[idx][1])) अणु
			DCCP_CRIT("Could not activate %d", idx);
			जाओ activation_failed;
		पूर्ण

	/* Clean up Change options which have been confirmed alपढ़ोy */
	list_क्रम_each_entry_safe(cur, next, fn_list, node)
		अगर (!cur->needs_confirm)
			dccp_feat_list_pop(cur);

	dccp_pr_debug("Activation OK\n");
	वापस 0;

activation_failed:
	/*
	 * We clean up everything that may have been allocated, since
	 * it is dअगरficult to track at which stage negotiation failed.
	 * This is ok, since all allocation functions below are robust
	 * against शून्य arguments.
	 */
	ccid_hc_rx_delete(dp->dccps_hc_rx_ccid, sk);
	ccid_hc_tx_delete(dp->dccps_hc_tx_ccid, sk);
	dp->dccps_hc_rx_ccid = dp->dccps_hc_tx_ccid = शून्य;
	dccp_ackvec_मुक्त(dp->dccps_hc_rx_ackvec);
	dp->dccps_hc_rx_ackvec = शून्य;
	वापस -1;
पूर्ण
