<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <net/tcp.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>

पूर्णांक nf_ct_seqadj_init(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
		      s32 off)
अणु
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_conn_seqadj *seqadj;
	काष्ठा nf_ct_seqadj *this_way;

	अगर (off == 0)
		वापस 0;

	set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);

	seqadj = nfct_seqadj(ct);
	this_way = &seqadj->seq[dir];
	this_way->offset_beक्रमe	 = off;
	this_way->offset_after	 = off;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_seqadj_init);

पूर्णांक nf_ct_seqadj_set(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
		     __be32 seq, s32 off)
अणु
	काष्ठा nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_ct_seqadj *this_way;

	अगर (off == 0)
		वापस 0;

	अगर (unlikely(!seqadj)) अणु
		WARN_ONCE(1, "Missing nfct_seqadj_ext_add() setup call\n");
		वापस 0;
	पूर्ण

	set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);

	spin_lock_bh(&ct->lock);
	this_way = &seqadj->seq[dir];
	अगर (this_way->offset_beक्रमe == this_way->offset_after ||
	    beक्रमe(this_way->correction_pos, ntohl(seq))) अणु
		this_way->correction_pos = ntohl(seq);
		this_way->offset_beक्रमe	 = this_way->offset_after;
		this_way->offset_after	+= off;
	पूर्ण
	spin_unlock_bh(&ct->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_seqadj_set);

व्योम nf_ct_tcp_seqadj_set(काष्ठा sk_buff *skb,
			  काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			  s32 off)
अणु
	स्थिर काष्ठा tcphdr *th;

	अगर (nf_ct_protonum(ct) != IPPROTO_TCP)
		वापस;

	th = (काष्ठा tcphdr *)(skb_network_header(skb) + ip_hdrlen(skb));
	nf_ct_seqadj_set(ct, ctinfo, th->seq, off);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_tcp_seqadj_set);

/* Adjust one found SACK option including checksum correction */
अटल व्योम nf_ct_sack_block_adjust(काष्ठा sk_buff *skb,
				    काष्ठा tcphdr *tcph,
				    अचिन्हित पूर्णांक sackoff,
				    अचिन्हित पूर्णांक sackend,
				    काष्ठा nf_ct_seqadj *seq)
अणु
	जबतक (sackoff < sackend) अणु
		काष्ठा tcp_sack_block_wire *sack;
		__be32 new_start_seq, new_end_seq;

		sack = (व्योम *)skb->data + sackoff;
		अगर (after(ntohl(sack->start_seq) - seq->offset_beक्रमe,
			  seq->correction_pos))
			new_start_seq = htonl(ntohl(sack->start_seq) -
					seq->offset_after);
		अन्यथा
			new_start_seq = htonl(ntohl(sack->start_seq) -
					seq->offset_beक्रमe);

		अगर (after(ntohl(sack->end_seq) - seq->offset_beक्रमe,
			  seq->correction_pos))
			new_end_seq = htonl(ntohl(sack->end_seq) -
				      seq->offset_after);
		अन्यथा
			new_end_seq = htonl(ntohl(sack->end_seq) -
				      seq->offset_beक्रमe);

		pr_debug("sack_adjust: start_seq: %u->%u, end_seq: %u->%u\n",
			 ntohl(sack->start_seq), ntohl(new_start_seq),
			 ntohl(sack->end_seq), ntohl(new_end_seq));

		inet_proto_csum_replace4(&tcph->check, skb,
					 sack->start_seq, new_start_seq, false);
		inet_proto_csum_replace4(&tcph->check, skb,
					 sack->end_seq, new_end_seq, false);
		sack->start_seq = new_start_seq;
		sack->end_seq = new_end_seq;
		sackoff += माप(*sack);
	पूर्ण
पूर्ण

/* TCP SACK sequence number adjusपंचांगent */
अटल अचिन्हित पूर्णांक nf_ct_sack_adjust(काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक protoff,
				      काष्ठा nf_conn *ct,
				      क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा tcphdr *tcph = (व्योम *)skb->data + protoff;
	काष्ठा nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	अचिन्हित पूर्णांक dir, optoff, optend;

	optoff = protoff + माप(काष्ठा tcphdr);
	optend = protoff + tcph->करोff * 4;

	अगर (skb_ensure_writable(skb, optend))
		वापस 0;

	tcph = (व्योम *)skb->data + protoff;
	dir = CTINFO2सूची(ctinfo);

	जबतक (optoff < optend) अणु
		/* Usually: option, length. */
		अचिन्हित अक्षर *op = skb->data + optoff;

		चयन (op[0]) अणु
		हाल TCPOPT_EOL:
			वापस 1;
		हाल TCPOPT_NOP:
			optoff++;
			जारी;
		शेष:
			/* no partial options */
			अगर (optoff + 1 == optend ||
			    optoff + op[1] > optend ||
			    op[1] < 2)
				वापस 0;
			अगर (op[0] == TCPOPT_SACK &&
			    op[1] >= 2+TCPOLEN_SACK_PERBLOCK &&
			    ((op[1] - 2) % TCPOLEN_SACK_PERBLOCK) == 0)
				nf_ct_sack_block_adjust(skb, tcph, optoff + 2,
							optoff+op[1],
							&seqadj->seq[!dir]);
			optoff += op[1];
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/* TCP sequence number adjusपंचांगent.  Returns 1 on success, 0 on failure */
पूर्णांक nf_ct_seq_adjust(काष्ठा sk_buff *skb,
		     काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
		     अचिन्हित पूर्णांक protoff)
अणु
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा tcphdr *tcph;
	__be32 newseq, newack;
	s32 seqoff, ackoff;
	काष्ठा nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	काष्ठा nf_ct_seqadj *this_way, *other_way;
	पूर्णांक res = 1;

	this_way  = &seqadj->seq[dir];
	other_way = &seqadj->seq[!dir];

	अगर (skb_ensure_writable(skb, protoff + माप(*tcph)))
		वापस 0;

	tcph = (व्योम *)skb->data + protoff;
	spin_lock_bh(&ct->lock);
	अगर (after(ntohl(tcph->seq), this_way->correction_pos))
		seqoff = this_way->offset_after;
	अन्यथा
		seqoff = this_way->offset_beक्रमe;

	newseq = htonl(ntohl(tcph->seq) + seqoff);
	inet_proto_csum_replace4(&tcph->check, skb, tcph->seq, newseq, false);
	pr_debug("Adjusting sequence number from %u->%u\n",
		 ntohl(tcph->seq), ntohl(newseq));
	tcph->seq = newseq;

	अगर (!tcph->ack)
		जाओ out;

	अगर (after(ntohl(tcph->ack_seq) - other_way->offset_beक्रमe,
		  other_way->correction_pos))
		ackoff = other_way->offset_after;
	अन्यथा
		ackoff = other_way->offset_beक्रमe;

	newack = htonl(ntohl(tcph->ack_seq) - ackoff);
	inet_proto_csum_replace4(&tcph->check, skb, tcph->ack_seq, newack,
				 false);
	pr_debug("Adjusting ack number from %u->%u, ack from %u->%u\n",
		 ntohl(tcph->seq), ntohl(newseq), ntohl(tcph->ack_seq),
		 ntohl(newack));
	tcph->ack_seq = newack;

	res = nf_ct_sack_adjust(skb, protoff, ct, ctinfo);
out:
	spin_unlock_bh(&ct->lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_seq_adjust);

s32 nf_ct_seq_offset(स्थिर काष्ठा nf_conn *ct,
		     क्रमागत ip_conntrack_dir dir,
		     u32 seq)
अणु
	काष्ठा nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	काष्ठा nf_ct_seqadj *this_way;

	अगर (!seqadj)
		वापस 0;

	this_way = &seqadj->seq[dir];
	वापस after(seq, this_way->correction_pos) ?
		 this_way->offset_after : this_way->offset_beक्रमe;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_seq_offset);

अटल स्थिर काष्ठा nf_ct_ext_type nf_ct_seqadj_extend = अणु
	.len	= माप(काष्ठा nf_conn_seqadj),
	.align	= __alignof__(काष्ठा nf_conn_seqadj),
	.id	= NF_CT_EXT_SEQADJ,
पूर्ण;

पूर्णांक nf_conntrack_seqadj_init(व्योम)
अणु
	वापस nf_ct_extend_रेजिस्टर(&nf_ct_seqadj_extend);
पूर्ण

व्योम nf_conntrack_seqadj_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&nf_ct_seqadj_extend);
पूर्ण
