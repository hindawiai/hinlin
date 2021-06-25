<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  net/dccp/options.c
 *
 *  An implementation of the DCCP protocol
 *  Copyright (c) 2005 Aristeu Sergio Rozanski Filho <aris@cathedralद_असल.org>
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@ghostprotocols.net>
 *  Copyright (c) 2005 Ian McDonald <ian.mcकरोnald@jandi.co.nz>
 */
#समावेश <linux/dccp.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>

#समावेश "ackvec.h"
#समावेश "ccid.h"
#समावेश "dccp.h"
#समावेश "feat.h"

u64 dccp_decode_value_var(स्थिर u8 *bf, स्थिर u8 len)
अणु
	u64 value = 0;

	अगर (len >= DCCP_OPTVAL_MAXLEN)
		value += ((u64)*bf++) << 40;
	अगर (len > 4)
		value += ((u64)*bf++) << 32;
	अगर (len > 3)
		value += ((u64)*bf++) << 24;
	अगर (len > 2)
		value += ((u64)*bf++) << 16;
	अगर (len > 1)
		value += ((u64)*bf++) << 8;
	अगर (len > 0)
		value += *bf;

	वापस value;
पूर्ण

/**
 * dccp_parse_options  -  Parse DCCP options present in @skb
 * @sk: client|server|listening dccp socket (when @dreq != शून्य)
 * @dreq: request socket to use during connection setup, or शून्य
 * @skb: frame to parse
 */
पूर्णांक dccp_parse_options(काष्ठा sock *sk, काष्ठा dccp_request_sock *dreq,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	स्थिर काष्ठा dccp_hdr *dh = dccp_hdr(skb);
	स्थिर u8 pkt_type = DCCP_SKB_CB(skb)->dccpd_type;
	अचिन्हित अक्षर *options = (अचिन्हित अक्षर *)dh + dccp_hdr_len(skb);
	अचिन्हित अक्षर *opt_ptr = options;
	स्थिर अचिन्हित अक्षर *opt_end = (अचिन्हित अक्षर *)dh +
					(dh->dccph_करोff * 4);
	काष्ठा dccp_options_received *opt_recv = &dp->dccps_options_received;
	अचिन्हित अक्षर opt, len;
	अचिन्हित अक्षर *value;
	u32 elapsed_समय;
	__be32 opt_val;
	पूर्णांक rc;
	पूर्णांक mandatory = 0;

	स_रखो(opt_recv, 0, माप(*opt_recv));

	opt = len = 0;
	जबतक (opt_ptr != opt_end) अणु
		opt   = *opt_ptr++;
		len   = 0;
		value = शून्य;

		/* Check अगर this isn't a single byte option */
		अगर (opt > DCCPO_MAX_RESERVED) अणु
			अगर (opt_ptr == opt_end)
				जाओ out_nonsensical_length;

			len = *opt_ptr++;
			अगर (len < 2)
				जाओ out_nonsensical_length;
			/*
			 * Remove the type and len fields, leaving
			 * just the value size
			 */
			len	-= 2;
			value	= opt_ptr;
			opt_ptr += len;

			अगर (opt_ptr > opt_end)
				जाओ out_nonsensical_length;
		पूर्ण

		/*
		 * CCID-specअगरic options are ignored during connection setup, as
		 * negotiation may still be in progress (see RFC 4340, 10.3).
		 * The same applies to Ack Vectors, as these depend on the CCID.
		 */
		अगर (dreq != शून्य && (opt >= DCCPO_MIN_RX_CCID_SPECIFIC ||
		    opt == DCCPO_ACK_VECTOR_0 || opt == DCCPO_ACK_VECTOR_1))
			जाओ ignore_option;

		चयन (opt) अणु
		हाल DCCPO_PADDING:
			अवरोध;
		हाल DCCPO_MANDATORY:
			अगर (mandatory)
				जाओ out_invalid_option;
			अगर (pkt_type != DCCP_PKT_DATA)
				mandatory = 1;
			अवरोध;
		हाल DCCPO_NDP_COUNT:
			अगर (len > 6)
				जाओ out_invalid_option;

			opt_recv->dccpor_ndp = dccp_decode_value_var(value, len);
			dccp_pr_debug("%s opt: NDP count=%llu\n", dccp_role(sk),
				      (अचिन्हित दीर्घ दीर्घ)opt_recv->dccpor_ndp);
			अवरोध;
		हाल DCCPO_CHANGE_L ... DCCPO_CONFIRM_R:
			अगर (pkt_type == DCCP_PKT_DATA)      /* RFC 4340, 6 */
				अवरोध;
			अगर (len == 0)
				जाओ out_invalid_option;
			rc = dccp_feat_parse_options(sk, dreq, mandatory, opt,
						    *value, value + 1, len - 1);
			अगर (rc)
				जाओ out_featneg_failed;
			अवरोध;
		हाल DCCPO_TIMESTAMP:
			अगर (len != 4)
				जाओ out_invalid_option;
			/*
			 * RFC 4340 13.1: "The precise समय corresponding to
			 * Timestamp Value zero is not specअगरied". We use
			 * zero to indicate असलence of a meaningful बारtamp.
			 */
			opt_val = get_unaligned((__be32 *)value);
			अगर (unlikely(opt_val == 0)) अणु
				DCCP_WARN("Timestamp with zero value\n");
				अवरोध;
			पूर्ण

			अगर (dreq != शून्य) अणु
				dreq->dreq_बारtamp_echo = ntohl(opt_val);
				dreq->dreq_बारtamp_समय = dccp_बारtamp();
			पूर्ण अन्यथा अणु
				opt_recv->dccpor_बारtamp =
					dp->dccps_बारtamp_echo = ntohl(opt_val);
				dp->dccps_बारtamp_समय = dccp_बारtamp();
			पूर्ण
			dccp_pr_debug("%s rx opt: TIMESTAMP=%u, ackno=%llu\n",
				      dccp_role(sk), ntohl(opt_val),
				      (अचिन्हित दीर्घ दीर्घ)
				      DCCP_SKB_CB(skb)->dccpd_ack_seq);
			/* schedule an Ack in हाल this sender is quiescent */
			inet_csk_schedule_ack(sk);
			अवरोध;
		हाल DCCPO_TIMESTAMP_ECHO:
			अगर (len != 4 && len != 6 && len != 8)
				जाओ out_invalid_option;

			opt_val = get_unaligned((__be32 *)value);
			opt_recv->dccpor_बारtamp_echo = ntohl(opt_val);

			dccp_pr_debug("%s rx opt: TIMESTAMP_ECHO=%u, len=%d, "
				      "ackno=%llu", dccp_role(sk),
				      opt_recv->dccpor_बारtamp_echo,
				      len + 2,
				      (अचिन्हित दीर्घ दीर्घ)
				      DCCP_SKB_CB(skb)->dccpd_ack_seq);

			value += 4;

			अगर (len == 4) अणु		/* no elapsed समय included */
				dccp_pr_debug_cat("\n");
				अवरोध;
			पूर्ण

			अगर (len == 6) अणु		/* 2-byte elapsed समय */
				__be16 opt_val2 = get_unaligned((__be16 *)value);
				elapsed_समय = ntohs(opt_val2);
			पूर्ण अन्यथा अणु		/* 4-byte elapsed समय */
				opt_val = get_unaligned((__be32 *)value);
				elapsed_समय = ntohl(opt_val);
			पूर्ण

			dccp_pr_debug_cat(", ELAPSED_TIME=%u\n", elapsed_समय);

			/* Give precedence to the biggest ELAPSED_TIME */
			अगर (elapsed_समय > opt_recv->dccpor_elapsed_समय)
				opt_recv->dccpor_elapsed_समय = elapsed_समय;
			अवरोध;
		हाल DCCPO_ELAPSED_TIME:
			अगर (dccp_packet_without_ack(skb))   /* RFC 4340, 13.2 */
				अवरोध;

			अगर (len == 2) अणु
				__be16 opt_val2 = get_unaligned((__be16 *)value);
				elapsed_समय = ntohs(opt_val2);
			पूर्ण अन्यथा अगर (len == 4) अणु
				opt_val = get_unaligned((__be32 *)value);
				elapsed_समय = ntohl(opt_val);
			पूर्ण अन्यथा अणु
				जाओ out_invalid_option;
			पूर्ण

			अगर (elapsed_समय > opt_recv->dccpor_elapsed_समय)
				opt_recv->dccpor_elapsed_समय = elapsed_समय;

			dccp_pr_debug("%s rx opt: ELAPSED_TIME=%d\n",
				      dccp_role(sk), elapsed_समय);
			अवरोध;
		हाल DCCPO_MIN_RX_CCID_SPECIFIC ... DCCPO_MAX_RX_CCID_SPECIFIC:
			अगर (ccid_hc_rx_parse_options(dp->dccps_hc_rx_ccid, sk,
						     pkt_type, opt, value, len))
				जाओ out_invalid_option;
			अवरोध;
		हाल DCCPO_ACK_VECTOR_0:
		हाल DCCPO_ACK_VECTOR_1:
			अगर (dccp_packet_without_ack(skb))   /* RFC 4340, 11.4 */
				अवरोध;
			/*
			 * Ack vectors are processed by the TX CCID अगर it is
			 * पूर्णांकerested. The RX CCID need not parse Ack Vectors,
			 * since it is only पूर्णांकerested in clearing old state.
			 */
			fallthrough;
		हाल DCCPO_MIN_TX_CCID_SPECIFIC ... DCCPO_MAX_TX_CCID_SPECIFIC:
			अगर (ccid_hc_tx_parse_options(dp->dccps_hc_tx_ccid, sk,
						     pkt_type, opt, value, len))
				जाओ out_invalid_option;
			अवरोध;
		शेष:
			DCCP_CRIT("DCCP(%p): option %d(len=%d) not "
				  "implemented, ignoring", sk, opt, len);
			अवरोध;
		पूर्ण
ignore_option:
		अगर (opt != DCCPO_MANDATORY)
			mandatory = 0;
	पूर्ण

	/* mandatory was the last byte in option list -> reset connection */
	अगर (mandatory)
		जाओ out_invalid_option;

out_nonsensical_length:
	/* RFC 4340, 5.8: ignore option and all reमुख्यing option space */
	वापस 0;

out_invalid_option:
	DCCP_INC_STATS(DCCP_MIB_INVALIDOPT);
	rc = DCCP_RESET_CODE_OPTION_ERROR;
out_featneg_failed:
	DCCP_WARN("DCCP(%p): Option %d (len=%d) error=%u\n", sk, opt, len, rc);
	DCCP_SKB_CB(skb)->dccpd_reset_code = rc;
	DCCP_SKB_CB(skb)->dccpd_reset_data[0] = opt;
	DCCP_SKB_CB(skb)->dccpd_reset_data[1] = len > 0 ? value[0] : 0;
	DCCP_SKB_CB(skb)->dccpd_reset_data[2] = len > 1 ? value[1] : 0;
	वापस -1;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_parse_options);

व्योम dccp_encode_value_var(स्थिर u64 value, u8 *to, स्थिर u8 len)
अणु
	अगर (len >= DCCP_OPTVAL_MAXLEN)
		*to++ = (value & 0xFF0000000000ull) >> 40;
	अगर (len > 4)
		*to++ = (value & 0xFF00000000ull) >> 32;
	अगर (len > 3)
		*to++ = (value & 0xFF000000) >> 24;
	अगर (len > 2)
		*to++ = (value & 0xFF0000) >> 16;
	अगर (len > 1)
		*to++ = (value & 0xFF00) >> 8;
	अगर (len > 0)
		*to++ = (value & 0xFF);
पूर्ण

अटल अंतरभूत u8 dccp_ndp_len(स्थिर u64 ndp)
अणु
	अगर (likely(ndp <= 0xFF))
		वापस 1;
	वापस likely(ndp <= अच_लघु_उच्च) ? 2 : (ndp <= अच_पूर्णांक_उच्च ? 4 : 6);
पूर्ण

पूर्णांक dccp_insert_option(काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर option,
		       स्थिर व्योम *value, स्थिर अचिन्हित अक्षर len)
अणु
	अचिन्हित अक्षर *to;

	अगर (DCCP_SKB_CB(skb)->dccpd_opt_len + len + 2 > DCCP_MAX_OPT_LEN)
		वापस -1;

	DCCP_SKB_CB(skb)->dccpd_opt_len += len + 2;

	to    = skb_push(skb, len + 2);
	*to++ = option;
	*to++ = len + 2;

	स_नकल(to, value, len);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dccp_insert_option);

अटल पूर्णांक dccp_insert_option_ndp(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	u64 ndp = dp->dccps_ndp_count;

	अगर (dccp_non_data_packet(skb))
		++dp->dccps_ndp_count;
	अन्यथा
		dp->dccps_ndp_count = 0;

	अगर (ndp > 0) अणु
		अचिन्हित अक्षर *ptr;
		स्थिर पूर्णांक ndp_len = dccp_ndp_len(ndp);
		स्थिर पूर्णांक len = ndp_len + 2;

		अगर (DCCP_SKB_CB(skb)->dccpd_opt_len + len > DCCP_MAX_OPT_LEN)
			वापस -1;

		DCCP_SKB_CB(skb)->dccpd_opt_len += len;

		ptr = skb_push(skb, len);
		*ptr++ = DCCPO_NDP_COUNT;
		*ptr++ = len;
		dccp_encode_value_var(ndp, ptr, ndp_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dccp_elapsed_समय_len(स्थिर u32 elapsed_समय)
अणु
	वापस elapsed_समय == 0 ? 0 : elapsed_समय <= 0xFFFF ? 2 : 4;
पूर्ण

अटल पूर्णांक dccp_insert_option_बारtamp(काष्ठा sk_buff *skb)
अणु
	__be32 now = htonl(dccp_बारtamp());
	/* yes this will overflow but that is the poपूर्णांक as we want a
	 * 10 usec 32 bit समयr which mean it wraps every 11.9 hours */

	वापस dccp_insert_option(skb, DCCPO_TIMESTAMP, &now, माप(now));
पूर्ण

अटल पूर्णांक dccp_insert_option_बारtamp_echo(काष्ठा dccp_sock *dp,
					     काष्ठा dccp_request_sock *dreq,
					     काष्ठा sk_buff *skb)
अणु
	__be32 tstamp_echo;
	अचिन्हित अक्षर *to;
	u32 elapsed_समय, elapsed_समय_len, len;

	अगर (dreq != शून्य) अणु
		elapsed_समय = dccp_बारtamp() - dreq->dreq_बारtamp_समय;
		tstamp_echo  = htonl(dreq->dreq_बारtamp_echo);
		dreq->dreq_बारtamp_echo = 0;
	पूर्ण अन्यथा अणु
		elapsed_समय = dccp_बारtamp() - dp->dccps_बारtamp_समय;
		tstamp_echo  = htonl(dp->dccps_बारtamp_echo);
		dp->dccps_बारtamp_echo = 0;
	पूर्ण

	elapsed_समय_len = dccp_elapsed_समय_len(elapsed_समय);
	len = 6 + elapsed_समय_len;

	अगर (DCCP_SKB_CB(skb)->dccpd_opt_len + len > DCCP_MAX_OPT_LEN)
		वापस -1;

	DCCP_SKB_CB(skb)->dccpd_opt_len += len;

	to    = skb_push(skb, len);
	*to++ = DCCPO_TIMESTAMP_ECHO;
	*to++ = len;

	स_नकल(to, &tstamp_echo, 4);
	to += 4;

	अगर (elapsed_समय_len == 2) अणु
		स्थिर __be16 var16 = htons((u16)elapsed_समय);
		स_नकल(to, &var16, 2);
	पूर्ण अन्यथा अगर (elapsed_समय_len == 4) अणु
		स्थिर __be32 var32 = htonl(elapsed_समय);
		स_नकल(to, &var32, 4);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dccp_insert_option_ackvec(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	काष्ठा dccp_ackvec *av = dp->dccps_hc_rx_ackvec;
	काष्ठा dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
	स्थिर u16 buflen = dccp_ackvec_buflen(av);
	/* Figure out how many options करो we need to represent the ackvec */
	स्थिर u8 nr_opts = DIV_ROUND_UP(buflen, DCCP_SINGLE_OPT_MAXLEN);
	u16 len = buflen + 2 * nr_opts;
	u8 i, nonce = 0;
	स्थिर अचिन्हित अक्षर *tail, *from;
	अचिन्हित अक्षर *to;

	अगर (dcb->dccpd_opt_len + len > DCCP_MAX_OPT_LEN) अणु
		DCCP_WARN("Lacking space for %u bytes on %s packet\n", len,
			  dccp_packet_name(dcb->dccpd_type));
		वापस -1;
	पूर्ण
	/*
	 * Since Ack Vectors are variable-length, we can not always predict
	 * their size. To catch exception हालs where the space is running out
	 * on the skb, a separate Sync is scheduled to carry the Ack Vector.
	 */
	अगर (len > DCCPAV_MIN_OPTLEN &&
	    len + dcb->dccpd_opt_len + skb->len > dp->dccps_mss_cache) अणु
		DCCP_WARN("No space left for Ack Vector (%u) on skb (%u+%u), "
			  "MPS=%u ==> reduce payload size?\n", len, skb->len,
			  dcb->dccpd_opt_len, dp->dccps_mss_cache);
		dp->dccps_sync_scheduled = 1;
		वापस 0;
	पूर्ण
	dcb->dccpd_opt_len += len;

	to   = skb_push(skb, len);
	len  = buflen;
	from = av->av_buf + av->av_buf_head;
	tail = av->av_buf + DCCPAV_MAX_ACKVEC_LEN;

	क्रम (i = 0; i < nr_opts; ++i) अणु
		पूर्णांक copylen = len;

		अगर (len > DCCP_SINGLE_OPT_MAXLEN)
			copylen = DCCP_SINGLE_OPT_MAXLEN;

		/*
		 * RFC 4340, 12.2: Encode the Nonce Echo क्रम this Ack Vector via
		 * its type; ack_nonce is the sum of all inभागidual buf_nonce's.
		 */
		nonce ^= av->av_buf_nonce[i];

		*to++ = DCCPO_ACK_VECTOR_0 + av->av_buf_nonce[i];
		*to++ = copylen + 2;

		/* Check अगर buf_head wraps */
		अगर (from + copylen > tail) अणु
			स्थिर u16 tailsize = tail - from;

			स_नकल(to, from, tailsize);
			to	+= tailsize;
			len	-= tailsize;
			copylen	-= tailsize;
			from	= av->av_buf;
		पूर्ण

		स_नकल(to, from, copylen);
		from += copylen;
		to   += copylen;
		len  -= copylen;
	पूर्ण
	/*
	 * Each sent Ack Vector is recorded in the list, as per A.2 of RFC 4340.
	 */
	अगर (dccp_ackvec_update_records(av, dcb->dccpd_seq, nonce))
		वापस -ENOBUFS;
	वापस 0;
पूर्ण

/**
 * dccp_insert_option_mandatory  -  Mandatory option (5.8.2)
 * @skb: frame पूर्णांकo which to insert option
 *
 * Note that since we are using skb_push, this function needs to be called
 * _after_ inserting the option it is supposed to influence (stack order).
 */
पूर्णांक dccp_insert_option_mandatory(काष्ठा sk_buff *skb)
अणु
	अगर (DCCP_SKB_CB(skb)->dccpd_opt_len >= DCCP_MAX_OPT_LEN)
		वापस -1;

	DCCP_SKB_CB(skb)->dccpd_opt_len++;
	*(u8 *)skb_push(skb, 1) = DCCPO_MANDATORY;
	वापस 0;
पूर्ण

/**
 * dccp_insert_fn_opt  -  Insert single Feature-Negotiation option पूर्णांकo @skb
 * @skb: frame to insert feature negotiation option पूर्णांकo
 * @type: %DCCPO_CHANGE_L, %DCCPO_CHANGE_R, %DCCPO_CONFIRM_L, %DCCPO_CONFIRM_R
 * @feat: one out of %dccp_feature_numbers
 * @val: NN value or SP array (preferred element first) to copy
 * @len: true length of @val in bytes (excluding first element repetition)
 * @repeat_first: whether to copy the first element of @val twice
 *
 * The last argument is used to स्थिरruct Confirm options, where the preferred
 * value and the preference list appear separately (RFC 4340, 6.3.1). Preference
 * lists are kept such that the preferred entry is always first, so we only need
 * to copy twice, and aव्योम the overhead of cloning पूर्णांकo a bigger array.
 */
पूर्णांक dccp_insert_fn_opt(काष्ठा sk_buff *skb, u8 type, u8 feat,
		       u8 *val, u8 len, bool repeat_first)
अणु
	u8 tot_len, *to;

	/* take the `Feature' field and possible repetition पूर्णांकo account */
	अगर (len > (DCCP_SINGLE_OPT_MAXLEN - 2)) अणु
		DCCP_WARN("length %u for feature %u too large\n", len, feat);
		वापस -1;
	पूर्ण

	अगर (unlikely(val == शून्य || len == 0))
		len = repeat_first = false;
	tot_len = 3 + repeat_first + len;

	अगर (DCCP_SKB_CB(skb)->dccpd_opt_len + tot_len > DCCP_MAX_OPT_LEN) अणु
		DCCP_WARN("packet too small for feature %d option!\n", feat);
		वापस -1;
	पूर्ण
	DCCP_SKB_CB(skb)->dccpd_opt_len += tot_len;

	to    = skb_push(skb, tot_len);
	*to++ = type;
	*to++ = tot_len;
	*to++ = feat;

	अगर (repeat_first)
		*to++ = *val;
	अगर (len)
		स_नकल(to, val, len);
	वापस 0;
पूर्ण

/* The length of all options needs to be a multiple of 4 (5.8) */
अटल व्योम dccp_insert_option_padding(काष्ठा sk_buff *skb)
अणु
	पूर्णांक padding = DCCP_SKB_CB(skb)->dccpd_opt_len % 4;

	अगर (padding != 0) अणु
		padding = 4 - padding;
		स_रखो(skb_push(skb, padding), 0, padding);
		DCCP_SKB_CB(skb)->dccpd_opt_len += padding;
	पूर्ण
पूर्ण

पूर्णांक dccp_insert_options(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	DCCP_SKB_CB(skb)->dccpd_opt_len = 0;

	अगर (dp->dccps_send_ndp_count && dccp_insert_option_ndp(sk, skb))
		वापस -1;

	अगर (DCCP_SKB_CB(skb)->dccpd_type != DCCP_PKT_DATA) अणु

		/* Feature Negotiation */
		अगर (dccp_feat_insert_opts(dp, शून्य, skb))
			वापस -1;

		अगर (DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_REQUEST) अणु
			/*
			 * Obtain RTT sample from Request/Response exchange.
			 * This is currently used क्रम TFRC initialisation.
			 */
			अगर (dccp_insert_option_बारtamp(skb))
				वापस -1;

		पूर्ण अन्यथा अगर (dccp_ackvec_pending(sk) &&
			   dccp_insert_option_ackvec(sk, skb)) अणु
				वापस -1;
		पूर्ण
	पूर्ण

	अगर (dp->dccps_hc_rx_insert_options) अणु
		अगर (ccid_hc_rx_insert_options(dp->dccps_hc_rx_ccid, sk, skb))
			वापस -1;
		dp->dccps_hc_rx_insert_options = 0;
	पूर्ण

	अगर (dp->dccps_बारtamp_echo != 0 &&
	    dccp_insert_option_बारtamp_echo(dp, शून्य, skb))
		वापस -1;

	dccp_insert_option_padding(skb);
	वापस 0;
पूर्ण

पूर्णांक dccp_insert_options_rsk(काष्ठा dccp_request_sock *dreq, काष्ठा sk_buff *skb)
अणु
	DCCP_SKB_CB(skb)->dccpd_opt_len = 0;

	अगर (dccp_feat_insert_opts(शून्य, dreq, skb))
		वापस -1;

	/* Obtain RTT sample from Response/Ack exchange (used by TFRC). */
	अगर (dccp_insert_option_बारtamp(skb))
		वापस -1;

	अगर (dreq->dreq_बारtamp_echo != 0 &&
	    dccp_insert_option_बारtamp_echo(शून्य, dreq, skb))
		वापस -1;

	dccp_insert_option_padding(skb);
	वापस 0;
पूर्ण
