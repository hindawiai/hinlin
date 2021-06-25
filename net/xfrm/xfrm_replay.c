<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xfrm_replay.c - xfrm replay detection, derived from xfrm_state.c.
 *
 * Copyright (C) 2010 secunet Security Networks AG
 * Copyright (C) 2010 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 */

#समावेश <linux/export.h>
#समावेश <net/xfrm.h>

u32 xfrm_replay_seqhi(काष्ठा xfrm_state *x, __be32 net_seq)
अणु
	u32 seq, seq_hi, bottom;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;

	अगर (!(x->props.flags & XFRM_STATE_ESN))
		वापस 0;

	seq = ntohl(net_seq);
	seq_hi = replay_esn->seq_hi;
	bottom = replay_esn->seq - replay_esn->replay_winकरोw + 1;

	अगर (likely(replay_esn->seq >= replay_esn->replay_winकरोw - 1)) अणु
		/* A. same subspace */
		अगर (unlikely(seq < bottom))
			seq_hi++;
	पूर्ण अन्यथा अणु
		/* B. winकरोw spans two subspaces */
		अगर (unlikely(seq >= bottom))
			seq_hi--;
	पूर्ण

	वापस seq_hi;
पूर्ण
EXPORT_SYMBOL(xfrm_replay_seqhi);
;
अटल व्योम xfrm_replay_notअगरy(काष्ठा xfrm_state *x, पूर्णांक event)
अणु
	काष्ठा km_event c;
	/* we send notअगरy messages in हाल
	 *  1. we updated on of the sequence numbers, and the seqno dअगरference
	 *     is at least x->replay_maxdअगरf, in this हाल we also update the
	 *     समयout of our समयr function
	 *  2. अगर x->replay_maxage has elapsed since last update,
	 *     and there were changes
	 *
	 *  The state काष्ठाure must be locked!
	 */

	चयन (event) अणु
	हाल XFRM_REPLAY_UPDATE:
		अगर (!x->replay_maxdअगरf ||
		    ((x->replay.seq - x->preplay.seq < x->replay_maxdअगरf) &&
		    (x->replay.oseq - x->preplay.oseq < x->replay_maxdअगरf))) अणु
			अगर (x->xflags & XFRM_TIME_DEFER)
				event = XFRM_REPLAY_TIMEOUT;
			अन्यथा
				वापस;
		पूर्ण

		अवरोध;

	हाल XFRM_REPLAY_TIMEOUT:
		अगर (स_भेद(&x->replay, &x->preplay,
			   माप(काष्ठा xfrm_replay_state)) == 0) अणु
			x->xflags |= XFRM_TIME_DEFER;
			वापस;
		पूर्ण

		अवरोध;
	पूर्ण

	स_नकल(&x->preplay, &x->replay, माप(काष्ठा xfrm_replay_state));
	c.event = XFRM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notअगरy(x, &c);

	अगर (x->replay_maxage &&
	    !mod_समयr(&x->rसमयr, jअगरfies + x->replay_maxage))
		x->xflags &= ~XFRM_TIME_DEFER;
पूर्ण

अटल पूर्णांक xfrm_replay_overflow(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;
	काष्ठा net *net = xs_net(x);

	अगर (x->type->flags & XFRM_TYPE_REPLAY_PROT) अणु
		XFRM_SKB_CB(skb)->seq.output.low = ++x->replay.oseq;
		XFRM_SKB_CB(skb)->seq.output.hi = 0;
		अगर (unlikely(x->replay.oseq == 0) &&
		    !(x->props.extra_flags & XFRM_SA_XFLAG_OSEQ_MAY_WRAP)) अणु
			x->replay.oseq--;
			xfrm_audit_state_replay_overflow(x, skb);
			err = -EOVERFLOW;

			वापस err;
		पूर्ण
		अगर (xfrm_aevent_is_on(net))
			x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xfrm_replay_check(काष्ठा xfrm_state *x,
		      काष्ठा sk_buff *skb, __be32 net_seq)
अणु
	u32 dअगरf;
	u32 seq = ntohl(net_seq);

	अगर (!x->props.replay_winकरोw)
		वापस 0;

	अगर (unlikely(seq == 0))
		जाओ err;

	अगर (likely(seq > x->replay.seq))
		वापस 0;

	dअगरf = x->replay.seq - seq;
	अगर (dअगरf >= x->props.replay_winकरोw) अणु
		x->stats.replay_winकरोw++;
		जाओ err;
	पूर्ण

	अगर (x->replay.biपंचांगap & (1U << dअगरf)) अणु
		x->stats.replay++;
		जाओ err;
	पूर्ण
	वापस 0;

err:
	xfrm_audit_state_replay(x, skb, net_seq);
	वापस -EINVAL;
पूर्ण

अटल व्योम xfrm_replay_advance(काष्ठा xfrm_state *x, __be32 net_seq)
अणु
	u32 dअगरf;
	u32 seq = ntohl(net_seq);

	अगर (!x->props.replay_winकरोw)
		वापस;

	अगर (seq > x->replay.seq) अणु
		dअगरf = seq - x->replay.seq;
		अगर (dअगरf < x->props.replay_winकरोw)
			x->replay.biपंचांगap = ((x->replay.biपंचांगap) << dअगरf) | 1;
		अन्यथा
			x->replay.biपंचांगap = 1;
		x->replay.seq = seq;
	पूर्ण अन्यथा अणु
		dअगरf = x->replay.seq - seq;
		x->replay.biपंचांगap |= (1U << dअगरf);
	पूर्ण

	अगर (xfrm_aevent_is_on(xs_net(x)))
		x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
पूर्ण

अटल पूर्णांक xfrm_replay_overflow_bmp(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	काष्ठा net *net = xs_net(x);

	अगर (x->type->flags & XFRM_TYPE_REPLAY_PROT) अणु
		XFRM_SKB_CB(skb)->seq.output.low = ++replay_esn->oseq;
		XFRM_SKB_CB(skb)->seq.output.hi = 0;
		अगर (unlikely(replay_esn->oseq == 0) &&
		    !(x->props.extra_flags & XFRM_SA_XFLAG_OSEQ_MAY_WRAP)) अणु
			replay_esn->oseq--;
			xfrm_audit_state_replay_overflow(x, skb);
			err = -EOVERFLOW;

			वापस err;
		पूर्ण
		अगर (xfrm_aevent_is_on(net))
			x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xfrm_replay_check_bmp(काष्ठा xfrm_state *x,
				 काष्ठा sk_buff *skb, __be32 net_seq)
अणु
	अचिन्हित पूर्णांक bitnr, nr;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	u32 pos;
	u32 seq = ntohl(net_seq);
	u32 dअगरf =  replay_esn->seq - seq;

	अगर (!replay_esn->replay_winकरोw)
		वापस 0;

	अगर (unlikely(seq == 0))
		जाओ err;

	अगर (likely(seq > replay_esn->seq))
		वापस 0;

	अगर (dअगरf >= replay_esn->replay_winकरोw) अणु
		x->stats.replay_winकरोw++;
		जाओ err;
	पूर्ण

	pos = (replay_esn->seq - 1) % replay_esn->replay_winकरोw;

	अगर (pos >= dअगरf)
		bitnr = (pos - dअगरf) % replay_esn->replay_winकरोw;
	अन्यथा
		bitnr = replay_esn->replay_winकरोw - (dअगरf - pos);

	nr = bitnr >> 5;
	bitnr = bitnr & 0x1F;
	अगर (replay_esn->bmp[nr] & (1U << bitnr))
		जाओ err_replay;

	वापस 0;

err_replay:
	x->stats.replay++;
err:
	xfrm_audit_state_replay(x, skb, net_seq);
	वापस -EINVAL;
पूर्ण

अटल व्योम xfrm_replay_advance_bmp(काष्ठा xfrm_state *x, __be32 net_seq)
अणु
	अचिन्हित पूर्णांक bitnr, nr, i;
	u32 dअगरf;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	u32 seq = ntohl(net_seq);
	u32 pos;

	अगर (!replay_esn->replay_winकरोw)
		वापस;

	pos = (replay_esn->seq - 1) % replay_esn->replay_winकरोw;

	अगर (seq > replay_esn->seq) अणु
		dअगरf = seq - replay_esn->seq;

		अगर (dअगरf < replay_esn->replay_winकरोw) अणु
			क्रम (i = 1; i < dअगरf; i++) अणु
				bitnr = (pos + i) % replay_esn->replay_winकरोw;
				nr = bitnr >> 5;
				bitnr = bitnr & 0x1F;
				replay_esn->bmp[nr] &=  ~(1U << bitnr);
			पूर्ण
		पूर्ण अन्यथा अणु
			nr = (replay_esn->replay_winकरोw - 1) >> 5;
			क्रम (i = 0; i <= nr; i++)
				replay_esn->bmp[i] = 0;
		पूर्ण

		bitnr = (pos + dअगरf) % replay_esn->replay_winकरोw;
		replay_esn->seq = seq;
	पूर्ण अन्यथा अणु
		dअगरf = replay_esn->seq - seq;

		अगर (pos >= dअगरf)
			bitnr = (pos - dअगरf) % replay_esn->replay_winकरोw;
		अन्यथा
			bitnr = replay_esn->replay_winकरोw - (dअगरf - pos);
	पूर्ण

	nr = bitnr >> 5;
	bitnr = bitnr & 0x1F;
	replay_esn->bmp[nr] |= (1U << bitnr);

	अगर (xfrm_aevent_is_on(xs_net(x)))
		x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
पूर्ण

अटल व्योम xfrm_replay_notअगरy_bmp(काष्ठा xfrm_state *x, पूर्णांक event)
अणु
	काष्ठा km_event c;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	काष्ठा xfrm_replay_state_esn *preplay_esn = x->preplay_esn;

	/* we send notअगरy messages in हाल
	 *  1. we updated on of the sequence numbers, and the seqno dअगरference
	 *     is at least x->replay_maxdअगरf, in this हाल we also update the
	 *     समयout of our समयr function
	 *  2. अगर x->replay_maxage has elapsed since last update,
	 *     and there were changes
	 *
	 *  The state काष्ठाure must be locked!
	 */

	चयन (event) अणु
	हाल XFRM_REPLAY_UPDATE:
		अगर (!x->replay_maxdअगरf ||
		    ((replay_esn->seq - preplay_esn->seq < x->replay_maxdअगरf) &&
		    (replay_esn->oseq - preplay_esn->oseq
		     < x->replay_maxdअगरf))) अणु
			अगर (x->xflags & XFRM_TIME_DEFER)
				event = XFRM_REPLAY_TIMEOUT;
			अन्यथा
				वापस;
		पूर्ण

		अवरोध;

	हाल XFRM_REPLAY_TIMEOUT:
		अगर (स_भेद(x->replay_esn, x->preplay_esn,
			   xfrm_replay_state_esn_len(replay_esn)) == 0) अणु
			x->xflags |= XFRM_TIME_DEFER;
			वापस;
		पूर्ण

		अवरोध;
	पूर्ण

	स_नकल(x->preplay_esn, x->replay_esn,
	       xfrm_replay_state_esn_len(replay_esn));
	c.event = XFRM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notअगरy(x, &c);

	अगर (x->replay_maxage &&
	    !mod_समयr(&x->rसमयr, jअगरfies + x->replay_maxage))
		x->xflags &= ~XFRM_TIME_DEFER;
पूर्ण

अटल व्योम xfrm_replay_notअगरy_esn(काष्ठा xfrm_state *x, पूर्णांक event)
अणु
	u32 seq_dअगरf, oseq_dअगरf;
	काष्ठा km_event c;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	काष्ठा xfrm_replay_state_esn *preplay_esn = x->preplay_esn;

	/* we send notअगरy messages in हाल
	 *  1. we updated on of the sequence numbers, and the seqno dअगरference
	 *     is at least x->replay_maxdअगरf, in this हाल we also update the
	 *     समयout of our समयr function
	 *  2. अगर x->replay_maxage has elapsed since last update,
	 *     and there were changes
	 *
	 *  The state काष्ठाure must be locked!
	 */

	चयन (event) अणु
	हाल XFRM_REPLAY_UPDATE:
		अगर (x->replay_maxdअगरf) अणु
			अगर (replay_esn->seq_hi == preplay_esn->seq_hi)
				seq_dअगरf = replay_esn->seq - preplay_esn->seq;
			अन्यथा
				seq_dअगरf = ~preplay_esn->seq + replay_esn->seq
					   + 1;

			अगर (replay_esn->oseq_hi == preplay_esn->oseq_hi)
				oseq_dअगरf = replay_esn->oseq
					    - preplay_esn->oseq;
			अन्यथा
				oseq_dअगरf = ~preplay_esn->oseq
					    + replay_esn->oseq + 1;

			अगर (seq_dअगरf >= x->replay_maxdअगरf ||
			    oseq_dअगरf >= x->replay_maxdअगरf)
				अवरोध;
		पूर्ण

		अगर (x->xflags & XFRM_TIME_DEFER)
			event = XFRM_REPLAY_TIMEOUT;
		अन्यथा
			वापस;

		अवरोध;

	हाल XFRM_REPLAY_TIMEOUT:
		अगर (स_भेद(x->replay_esn, x->preplay_esn,
			   xfrm_replay_state_esn_len(replay_esn)) == 0) अणु
			x->xflags |= XFRM_TIME_DEFER;
			वापस;
		पूर्ण

		अवरोध;
	पूर्ण

	स_नकल(x->preplay_esn, x->replay_esn,
	       xfrm_replay_state_esn_len(replay_esn));
	c.event = XFRM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notअगरy(x, &c);

	अगर (x->replay_maxage &&
	    !mod_समयr(&x->rसमयr, jअगरfies + x->replay_maxage))
		x->xflags &= ~XFRM_TIME_DEFER;
पूर्ण

अटल पूर्णांक xfrm_replay_overflow_esn(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	काष्ठा net *net = xs_net(x);

	अगर (x->type->flags & XFRM_TYPE_REPLAY_PROT) अणु
		XFRM_SKB_CB(skb)->seq.output.low = ++replay_esn->oseq;
		XFRM_SKB_CB(skb)->seq.output.hi = replay_esn->oseq_hi;

		अगर (unlikely(replay_esn->oseq == 0)) अणु
			XFRM_SKB_CB(skb)->seq.output.hi = ++replay_esn->oseq_hi;

			अगर (replay_esn->oseq_hi == 0) अणु
				replay_esn->oseq--;
				replay_esn->oseq_hi--;
				xfrm_audit_state_replay_overflow(x, skb);
				err = -EOVERFLOW;

				वापस err;
			पूर्ण
		पूर्ण
		अगर (xfrm_aevent_is_on(net))
			x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xfrm_replay_check_esn(काष्ठा xfrm_state *x,
				 काष्ठा sk_buff *skb, __be32 net_seq)
अणु
	अचिन्हित पूर्णांक bitnr, nr;
	u32 dअगरf;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	u32 pos;
	u32 seq = ntohl(net_seq);
	u32 wsize = replay_esn->replay_winकरोw;
	u32 top = replay_esn->seq;
	u32 bottom = top - wsize + 1;

	अगर (!wsize)
		वापस 0;

	अगर (unlikely(seq == 0 && replay_esn->seq_hi == 0 &&
		     (replay_esn->seq < replay_esn->replay_winकरोw - 1)))
		जाओ err;

	dअगरf = top - seq;

	अगर (likely(top >= wsize - 1)) अणु
		/* A. same subspace */
		अगर (likely(seq > top) || seq < bottom)
			वापस 0;
	पूर्ण अन्यथा अणु
		/* B. winकरोw spans two subspaces */
		अगर (likely(seq > top && seq < bottom))
			वापस 0;
		अगर (seq >= bottom)
			dअगरf = ~seq + top + 1;
	पूर्ण

	अगर (dअगरf >= replay_esn->replay_winकरोw) अणु
		x->stats.replay_winकरोw++;
		जाओ err;
	पूर्ण

	pos = (replay_esn->seq - 1) % replay_esn->replay_winकरोw;

	अगर (pos >= dअगरf)
		bitnr = (pos - dअगरf) % replay_esn->replay_winकरोw;
	अन्यथा
		bitnr = replay_esn->replay_winकरोw - (dअगरf - pos);

	nr = bitnr >> 5;
	bitnr = bitnr & 0x1F;
	अगर (replay_esn->bmp[nr] & (1U << bitnr))
		जाओ err_replay;

	वापस 0;

err_replay:
	x->stats.replay++;
err:
	xfrm_audit_state_replay(x, skb, net_seq);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक xfrm_replay_recheck_esn(काष्ठा xfrm_state *x,
				   काष्ठा sk_buff *skb, __be32 net_seq)
अणु
	अगर (unlikely(XFRM_SKB_CB(skb)->seq.input.hi !=
		     htonl(xfrm_replay_seqhi(x, net_seq)))) अणु
			x->stats.replay_winकरोw++;
			वापस -EINVAL;
	पूर्ण

	वापस xfrm_replay_check_esn(x, skb, net_seq);
पूर्ण

अटल व्योम xfrm_replay_advance_esn(काष्ठा xfrm_state *x, __be32 net_seq)
अणु
	अचिन्हित पूर्णांक bitnr, nr, i;
	पूर्णांक wrap;
	u32 dअगरf, pos, seq, seq_hi;
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;

	अगर (!replay_esn->replay_winकरोw)
		वापस;

	seq = ntohl(net_seq);
	pos = (replay_esn->seq - 1) % replay_esn->replay_winकरोw;
	seq_hi = xfrm_replay_seqhi(x, net_seq);
	wrap = seq_hi - replay_esn->seq_hi;

	अगर ((!wrap && seq > replay_esn->seq) || wrap > 0) अणु
		अगर (likely(!wrap))
			dअगरf = seq - replay_esn->seq;
		अन्यथा
			dअगरf = ~replay_esn->seq + seq + 1;

		अगर (dअगरf < replay_esn->replay_winकरोw) अणु
			क्रम (i = 1; i < dअगरf; i++) अणु
				bitnr = (pos + i) % replay_esn->replay_winकरोw;
				nr = bitnr >> 5;
				bitnr = bitnr & 0x1F;
				replay_esn->bmp[nr] &=  ~(1U << bitnr);
			पूर्ण
		पूर्ण अन्यथा अणु
			nr = (replay_esn->replay_winकरोw - 1) >> 5;
			क्रम (i = 0; i <= nr; i++)
				replay_esn->bmp[i] = 0;
		पूर्ण

		bitnr = (pos + dअगरf) % replay_esn->replay_winकरोw;
		replay_esn->seq = seq;

		अगर (unlikely(wrap > 0))
			replay_esn->seq_hi++;
	पूर्ण अन्यथा अणु
		dअगरf = replay_esn->seq - seq;

		अगर (pos >= dअगरf)
			bitnr = (pos - dअगरf) % replay_esn->replay_winकरोw;
		अन्यथा
			bitnr = replay_esn->replay_winकरोw - (dअगरf - pos);
	पूर्ण

	xfrm_dev_state_advance_esn(x);

	nr = bitnr >> 5;
	bitnr = bitnr & 0x1F;
	replay_esn->bmp[nr] |= (1U << bitnr);

	अगर (xfrm_aevent_is_on(xs_net(x)))
		x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
पूर्ण

#अगर_घोषित CONFIG_XFRM_OFFLOAD
अटल पूर्णांक xfrm_replay_overflow_offload(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;
	काष्ठा net *net = xs_net(x);
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	__u32 oseq = x->replay.oseq;

	अगर (!xo)
		वापस xfrm_replay_overflow(x, skb);

	अगर (x->type->flags & XFRM_TYPE_REPLAY_PROT) अणु
		अगर (!skb_is_gso(skb)) अणु
			XFRM_SKB_CB(skb)->seq.output.low = ++oseq;
			xo->seq.low = oseq;
		पूर्ण अन्यथा अणु
			XFRM_SKB_CB(skb)->seq.output.low = oseq + 1;
			xo->seq.low = oseq + 1;
			oseq += skb_shinfo(skb)->gso_segs;
		पूर्ण

		XFRM_SKB_CB(skb)->seq.output.hi = 0;
		xo->seq.hi = 0;
		अगर (unlikely(oseq < x->replay.oseq) &&
		    !(x->props.extra_flags & XFRM_SA_XFLAG_OSEQ_MAY_WRAP)) अणु
			xfrm_audit_state_replay_overflow(x, skb);
			err = -EOVERFLOW;

			वापस err;
		पूर्ण

		x->replay.oseq = oseq;

		अगर (xfrm_aevent_is_on(net))
			x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xfrm_replay_overflow_offload_bmp(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	काष्ठा net *net = xs_net(x);
	__u32 oseq = replay_esn->oseq;

	अगर (!xo)
		वापस xfrm_replay_overflow_bmp(x, skb);

	अगर (x->type->flags & XFRM_TYPE_REPLAY_PROT) अणु
		अगर (!skb_is_gso(skb)) अणु
			XFRM_SKB_CB(skb)->seq.output.low = ++oseq;
			xo->seq.low = oseq;
		पूर्ण अन्यथा अणु
			XFRM_SKB_CB(skb)->seq.output.low = oseq + 1;
			xo->seq.low = oseq + 1;
			oseq += skb_shinfo(skb)->gso_segs;
		पूर्ण

		XFRM_SKB_CB(skb)->seq.output.hi = 0;
		xo->seq.hi = 0;
		अगर (unlikely(oseq < replay_esn->oseq) &&
		    !(x->props.extra_flags & XFRM_SA_XFLAG_OSEQ_MAY_WRAP)) अणु
			xfrm_audit_state_replay_overflow(x, skb);
			err = -EOVERFLOW;

			वापस err;
		पूर्ण अन्यथा अणु
			replay_esn->oseq = oseq;
		पूर्ण

		अगर (xfrm_aevent_is_on(net))
			x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xfrm_replay_overflow_offload_esn(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = 0;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	काष्ठा net *net = xs_net(x);
	__u32 oseq = replay_esn->oseq;
	__u32 oseq_hi = replay_esn->oseq_hi;

	अगर (!xo)
		वापस xfrm_replay_overflow_esn(x, skb);

	अगर (x->type->flags & XFRM_TYPE_REPLAY_PROT) अणु
		अगर (!skb_is_gso(skb)) अणु
			XFRM_SKB_CB(skb)->seq.output.low = ++oseq;
			XFRM_SKB_CB(skb)->seq.output.hi = oseq_hi;
			xo->seq.low = oseq;
			xo->seq.hi = oseq_hi;
		पूर्ण अन्यथा अणु
			XFRM_SKB_CB(skb)->seq.output.low = oseq + 1;
			XFRM_SKB_CB(skb)->seq.output.hi = oseq_hi;
			xo->seq.low = oseq + 1;
			xo->seq.hi = oseq_hi;
			oseq += skb_shinfo(skb)->gso_segs;
		पूर्ण

		अगर (unlikely(oseq < replay_esn->oseq)) अणु
			XFRM_SKB_CB(skb)->seq.output.hi = ++oseq_hi;
			xo->seq.hi = oseq_hi;
			replay_esn->oseq_hi = oseq_hi;
			अगर (replay_esn->oseq_hi == 0) अणु
				replay_esn->oseq--;
				replay_esn->oseq_hi--;
				xfrm_audit_state_replay_overflow(x, skb);
				err = -EOVERFLOW;

				वापस err;
			पूर्ण
		पूर्ण

		replay_esn->oseq = oseq;

		अगर (xfrm_aevent_is_on(net))
			x->repl->notअगरy(x, XFRM_REPLAY_UPDATE);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा xfrm_replay xfrm_replay_legacy = अणु
	.advance	= xfrm_replay_advance,
	.check		= xfrm_replay_check,
	.recheck	= xfrm_replay_check,
	.notअगरy		= xfrm_replay_notअगरy,
	.overflow	= xfrm_replay_overflow_offload,
पूर्ण;

अटल स्थिर काष्ठा xfrm_replay xfrm_replay_bmp = अणु
	.advance	= xfrm_replay_advance_bmp,
	.check		= xfrm_replay_check_bmp,
	.recheck	= xfrm_replay_check_bmp,
	.notअगरy		= xfrm_replay_notअगरy_bmp,
	.overflow	= xfrm_replay_overflow_offload_bmp,
पूर्ण;

अटल स्थिर काष्ठा xfrm_replay xfrm_replay_esn = अणु
	.advance	= xfrm_replay_advance_esn,
	.check		= xfrm_replay_check_esn,
	.recheck	= xfrm_replay_recheck_esn,
	.notअगरy		= xfrm_replay_notअगरy_esn,
	.overflow	= xfrm_replay_overflow_offload_esn,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा xfrm_replay xfrm_replay_legacy = अणु
	.advance	= xfrm_replay_advance,
	.check		= xfrm_replay_check,
	.recheck	= xfrm_replay_check,
	.notअगरy		= xfrm_replay_notअगरy,
	.overflow	= xfrm_replay_overflow,
पूर्ण;

अटल स्थिर काष्ठा xfrm_replay xfrm_replay_bmp = अणु
	.advance	= xfrm_replay_advance_bmp,
	.check		= xfrm_replay_check_bmp,
	.recheck	= xfrm_replay_check_bmp,
	.notअगरy		= xfrm_replay_notअगरy_bmp,
	.overflow	= xfrm_replay_overflow_bmp,
पूर्ण;

अटल स्थिर काष्ठा xfrm_replay xfrm_replay_esn = अणु
	.advance	= xfrm_replay_advance_esn,
	.check		= xfrm_replay_check_esn,
	.recheck	= xfrm_replay_recheck_esn,
	.notअगरy		= xfrm_replay_notअगरy_esn,
	.overflow	= xfrm_replay_overflow_esn,
पूर्ण;
#पूर्ण_अगर

पूर्णांक xfrm_init_replay(काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;

	अगर (replay_esn) अणु
		अगर (replay_esn->replay_winकरोw >
		    replay_esn->bmp_len * माप(__u32) * 8)
			वापस -EINVAL;

		अगर (x->props.flags & XFRM_STATE_ESN) अणु
			अगर (replay_esn->replay_winकरोw == 0)
				वापस -EINVAL;
			x->repl = &xfrm_replay_esn;
		पूर्ण अन्यथा अणु
			x->repl = &xfrm_replay_bmp;
		पूर्ण
	पूर्ण अन्यथा अणु
		x->repl = &xfrm_replay_legacy;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xfrm_init_replay);
