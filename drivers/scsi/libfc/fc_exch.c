<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 * Copyright(c) 2008 Red Hat, Inc.  All rights reserved.
 * Copyright(c) 2008 Mike Christie
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * Fibre Channel exchange and sequence handling.
 */

#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/log2.h>

#समावेश <scsi/fc/fc_fc2.h>

#समावेश <scsi/libfc.h>

#समावेश "fc_libfc.h"

u16	fc_cpu_mask;		/* cpu mask क्रम possible cpus */
EXPORT_SYMBOL(fc_cpu_mask);
अटल u16	fc_cpu_order;	/* 2's घातer to represent total possible cpus */
अटल काष्ठा kmem_cache *fc_em_cachep;	       /* cache क्रम exchanges */
अटल काष्ठा workqueue_काष्ठा *fc_exch_workqueue;

/*
 * Structure and function definitions क्रम managing Fibre Channel Exchanges
 * and Sequences.
 *
 * The three primary काष्ठाures used here are fc_exch_mgr, fc_exch, and fc_seq.
 *
 * fc_exch_mgr holds the exchange state क्रम an N port
 *
 * fc_exch holds state क्रम one exchange and links to its active sequence.
 *
 * fc_seq holds the state क्रम an inभागidual sequence.
 */

/**
 * काष्ठा fc_exch_pool - Per cpu exchange pool
 * @next_index:	  Next possible मुक्त exchange index
 * @total_exches: Total allocated exchanges
 * @lock:	  Exch pool lock
 * @ex_list:	  List of exchanges
 * @left:	  Cache of मुक्त slot in exch array
 * @right:	  Cache of मुक्त slot in exch array
 *
 * This काष्ठाure manages per cpu exchanges in array of exchange poपूर्णांकers.
 * This array is allocated followed by काष्ठा fc_exch_pool memory क्रम
 * asचिन्हित range of exchanges to per cpu pool.
 */
काष्ठा fc_exch_pool अणु
	spinlock_t	 lock;
	काष्ठा list_head ex_list;
	u16		 next_index;
	u16		 total_exches;

	u16		 left;
	u16		 right;
पूर्ण ____cacheline_aligned_in_smp;

/**
 * काष्ठा fc_exch_mgr - The Exchange Manager (EM).
 * @class:	    Default class क्रम new sequences
 * @kref:	    Reference counter
 * @min_xid:	    Minimum exchange ID
 * @max_xid:	    Maximum exchange ID
 * @ep_pool:	    Reserved exchange poपूर्णांकers
 * @pool_max_index: Max exch array index in exch pool
 * @pool:	    Per cpu exch pool
 * @lport:	    Local exchange port
 * @stats:	    Statistics काष्ठाure
 *
 * This काष्ठाure is the center क्रम creating exchanges and sequences.
 * It manages the allocation of exchange IDs.
 */
काष्ठा fc_exch_mgr अणु
	काष्ठा fc_exch_pool __percpu *pool;
	mempool_t	*ep_pool;
	काष्ठा fc_lport	*lport;
	क्रमागत fc_class	class;
	काष्ठा kref	kref;
	u16		min_xid;
	u16		max_xid;
	u16		pool_max_index;

	काष्ठा अणु
		atomic_t no_मुक्त_exch;
		atomic_t no_मुक्त_exch_xid;
		atomic_t xid_not_found;
		atomic_t xid_busy;
		atomic_t seq_not_found;
		atomic_t non_bls_resp;
	पूर्ण stats;
पूर्ण;

/**
 * काष्ठा fc_exch_mgr_anchor - primary काष्ठाure क्रम list of EMs
 * @ema_list: Exchange Manager Anchor list
 * @mp:	      Exchange Manager associated with this anchor
 * @match:    Routine to determine अगर this anchor's EM should be used
 *
 * When walking the list of anchors the match routine will be called
 * क्रम each anchor to determine अगर that EM should be used. The last
 * anchor in the list will always match to handle any exchanges not
 * handled by other EMs. The non-शेष EMs would be added to the
 * anchor list by HW that provides offloads.
 */
काष्ठा fc_exch_mgr_anchor अणु
	काष्ठा list_head ema_list;
	काष्ठा fc_exch_mgr *mp;
	bool (*match)(काष्ठा fc_frame *);
पूर्ण;

अटल व्योम fc_exch_rrq(काष्ठा fc_exch *);
अटल व्योम fc_seq_ls_acc(काष्ठा fc_frame *);
अटल व्योम fc_seq_ls_rjt(काष्ठा fc_frame *, क्रमागत fc_els_rjt_reason,
			  क्रमागत fc_els_rjt_explan);
अटल व्योम fc_exch_els_rec(काष्ठा fc_frame *);
अटल व्योम fc_exch_els_rrq(काष्ठा fc_frame *);

/*
 * Internal implementation notes.
 *
 * The exchange manager is one by शेष in libfc but LLD may choose
 * to have one per CPU. The sequence manager is one per exchange manager
 * and currently never separated.
 *
 * Section 9.8 in FC-FS-2 specअगरies:  "The SEQ_ID is a one-byte field
 * asचिन्हित by the Sequence Initiator that shall be unique क्रम a specअगरic
 * D_ID and S_ID pair जबतक the Sequence is खोलो."   Note that it isn't
 * qualअगरied by exchange ID, which one might think it would be.
 * In practice this limits the number of खोलो sequences and exchanges to 256
 * per session.	 For most tarमाला_लो we could treat this limit as per exchange.
 *
 * The exchange and its sequence are मुक्तd when the last sequence is received.
 * It's possible क्रम the remote port to leave an exchange खोलो without
 * sending any sequences.
 *
 * Notes on reference counts:
 *
 * Exchanges are reference counted and exchange माला_लो मुक्तd when the reference
 * count becomes zero.
 *
 * Timeouts:
 * Sequences are समयd out क्रम E_D_TOV and R_A_TOV.
 *
 * Sequence event handling:
 *
 * The following events may occur on initiator sequences:
 *
 *	Send.
 *	    For now, the whole thing is sent.
 *	Receive ACK
 *	    This applies only to class F.
 *	    The sequence is marked complete.
 *	ULP completion.
 *	    The upper layer calls fc_exch_करोne() when करोne
 *	    with exchange and sequence tuple.
 *	RX-inferred completion.
 *	    When we receive the next sequence on the same exchange, we can
 *	    retire the previous sequence ID.  (XXX not implemented).
 *	Timeout.
 *	    R_A_TOV मुक्तs the sequence ID.  If we're रुकोing क्रम ACK,
 *	    E_D_TOV causes पात and calls upper layer response handler
 *	    with FC_EX_TIMEOUT error.
 *	Receive RJT
 *	    XXX defer.
 *	Send ABTS
 *	    On समयout.
 *
 * The following events may occur on recipient sequences:
 *
 *	Receive
 *	    Allocate sequence क्रम first frame received.
 *	    Hold during receive handler.
 *	    Release when final frame received.
 *	    Keep status of last N of these क्रम the ELS RES command.  XXX TBD.
 *	Receive ABTS
 *	    Deallocate sequence
 *	Send RJT
 *	    Deallocate
 *
 * For now, we neglect conditions where only part of a sequence was
 * received or transmitted, or where out-of-order receipt is detected.
 */

/*
 * Locking notes:
 *
 * The EM code run in a per-CPU worker thपढ़ो.
 *
 * To protect against concurrency between a worker thपढ़ो code and समयrs,
 * sequence allocation and deallocation must be locked.
 *  - exchange refcnt can be करोne atomicly without locks.
 *  - sequence allocation must be locked by exch lock.
 *  - If the EM pool lock and ex_lock must be taken at the same समय, then the
 *    EM pool lock must be taken beक्रमe the ex_lock.
 */

/*
 * opcode names क्रम debugging.
 */
अटल अक्षर *fc_exch_rctl_names[] = FC_RCTL_NAMES_INIT;

/**
 * fc_exch_name_lookup() - Lookup name by opcode
 * @op:	       Opcode to be looked up
 * @table:     Opcode/name table
 * @max_index: Index not to be exceeded
 *
 * This routine is used to determine a human-पढ़ोable string identअगरying
 * a R_CTL opcode.
 */
अटल अंतरभूत स्थिर अक्षर *fc_exch_name_lookup(अचिन्हित पूर्णांक op, अक्षर **table,
					      अचिन्हित पूर्णांक max_index)
अणु
	स्थिर अक्षर *name = शून्य;

	अगर (op < max_index)
		name = table[op];
	अगर (!name)
		name = "unknown";
	वापस name;
पूर्ण

/**
 * fc_exch_rctl_name() - Wrapper routine क्रम fc_exch_name_lookup()
 * @op: The opcode to be looked up
 */
अटल स्थिर अक्षर *fc_exch_rctl_name(अचिन्हित पूर्णांक op)
अणु
	वापस fc_exch_name_lookup(op, fc_exch_rctl_names,
				   ARRAY_SIZE(fc_exch_rctl_names));
पूर्ण

/**
 * fc_exch_hold() - Increment an exchange's reference count
 * @ep: Echange to be held
 */
अटल अंतरभूत व्योम fc_exch_hold(काष्ठा fc_exch *ep)
अणु
	atomic_inc(&ep->ex_refcnt);
पूर्ण

/**
 * fc_exch_setup_hdr() - Initialize a FC header by initializing some fields
 *			 and determine SOF and खातापूर्ण.
 * @ep:	   The exchange to that will use the header
 * @fp:	   The frame whose header is to be modअगरied
 * @f_ctl: F_CTL bits that will be used क्रम the frame header
 *
 * The fields initialized by this routine are: fh_ox_id, fh_rx_id,
 * fh_seq_id, fh_seq_cnt and the SOF and खातापूर्ण.
 */
अटल व्योम fc_exch_setup_hdr(काष्ठा fc_exch *ep, काष्ठा fc_frame *fp,
			      u32 f_ctl)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	u16 fill;

	fr_sof(fp) = ep->class;
	अगर (ep->seq.cnt)
		fr_sof(fp) = fc_sof_normal(ep->class);

	अगर (f_ctl & FC_FC_END_SEQ) अणु
		fr_eof(fp) = FC_खातापूर्ण_T;
		अगर (fc_sof_needs_ack((क्रमागत fc_sof)ep->class))
			fr_eof(fp) = FC_खातापूर्ण_N;
		/*
		 * From F_CTL.
		 * The number of fill bytes to make the length a 4-byte
		 * multiple is the low order 2-bits of the f_ctl.
		 * The fill itself will have been cleared by the frame
		 * allocation.
		 * After this, the length will be even, as expected by
		 * the transport.
		 */
		fill = fr_len(fp) & 3;
		अगर (fill) अणु
			fill = 4 - fill;
			/* TODO, this may be a problem with fragmented skb */
			skb_put(fp_skb(fp), fill);
			hton24(fh->fh_f_ctl, f_ctl | fill);
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(fr_len(fp) % 4 != 0);	/* no pad to non last frame */
		fr_eof(fp) = FC_खातापूर्ण_N;
	पूर्ण

	/* Initialize reमुख्यing fh fields from fc_fill_fc_hdr */
	fh->fh_ox_id = htons(ep->oxid);
	fh->fh_rx_id = htons(ep->rxid);
	fh->fh_seq_id = ep->seq.id;
	fh->fh_seq_cnt = htons(ep->seq.cnt);
पूर्ण

/**
 * fc_exch_release() - Decrement an exchange's reference count
 * @ep: Exchange to be released
 *
 * If the reference count reaches zero and the exchange is complete,
 * it is मुक्तd.
 */
अटल व्योम fc_exch_release(काष्ठा fc_exch *ep)
अणु
	काष्ठा fc_exch_mgr *mp;

	अगर (atomic_dec_and_test(&ep->ex_refcnt)) अणु
		mp = ep->em;
		अगर (ep->deकाष्ठाor)
			ep->deकाष्ठाor(&ep->seq, ep->arg);
		WARN_ON(!(ep->esb_stat & ESB_ST_COMPLETE));
		mempool_मुक्त(ep, mp->ep_pool);
	पूर्ण
पूर्ण

/**
 * fc_exch_समयr_cancel() - cancel exch समयr
 * @ep:		The exchange whose समयr to be canceled
 */
अटल अंतरभूत व्योम fc_exch_समयr_cancel(काष्ठा fc_exch *ep)
अणु
	अगर (cancel_delayed_work(&ep->समयout_work)) अणु
		FC_EXCH_DBG(ep, "Exchange timer canceled\n");
		atomic_dec(&ep->ex_refcnt); /* drop hold क्रम समयr */
	पूर्ण
पूर्ण

/**
 * fc_exch_समयr_set_locked() - Start a समयr क्रम an exchange w/ the
 *				the exchange lock held
 * @ep:		The exchange whose समयr will start
 * @समयr_msec: The समयout period
 *
 * Used क्रम upper level protocols to समय out the exchange.
 * The समयr is cancelled when it fires or when the exchange completes.
 */
अटल अंतरभूत व्योम fc_exch_समयr_set_locked(काष्ठा fc_exch *ep,
					    अचिन्हित पूर्णांक समयr_msec)
अणु
	अगर (ep->state & (FC_EX_RST_CLEANUP | FC_EX_DONE))
		वापस;

	FC_EXCH_DBG(ep, "Exchange timer armed : %d msecs\n", समयr_msec);

	fc_exch_hold(ep);		/* hold क्रम समयr */
	अगर (!queue_delayed_work(fc_exch_workqueue, &ep->समयout_work,
				msecs_to_jअगरfies(समयr_msec))) अणु
		FC_EXCH_DBG(ep, "Exchange already queued\n");
		fc_exch_release(ep);
	पूर्ण
पूर्ण

/**
 * fc_exch_समयr_set() - Lock the exchange and set the समयr
 * @ep:		The exchange whose समयr will start
 * @समयr_msec: The समयout period
 */
अटल व्योम fc_exch_समयr_set(काष्ठा fc_exch *ep, अचिन्हित पूर्णांक समयr_msec)
अणु
	spin_lock_bh(&ep->ex_lock);
	fc_exch_समयr_set_locked(ep, समयr_msec);
	spin_unlock_bh(&ep->ex_lock);
पूर्ण

/**
 * fc_exch_करोne_locked() - Complete an exchange with the exchange lock held
 * @ep: The exchange that is complete
 *
 * Note: May sleep अगर invoked from outside a response handler.
 */
अटल पूर्णांक fc_exch_करोne_locked(काष्ठा fc_exch *ep)
अणु
	पूर्णांक rc = 1;

	/*
	 * We must check क्रम completion in हाल there are two thपढ़ोs
	 * tyring to complete this. But the rrq code will reuse the
	 * ep, and in that हाल we only clear the resp and set it as
	 * complete, so it can be reused by the समयr to send the rrq.
	 */
	अगर (ep->state & FC_EX_DONE)
		वापस rc;
	ep->esb_stat |= ESB_ST_COMPLETE;

	अगर (!(ep->esb_stat & ESB_ST_REC_QUAL)) अणु
		ep->state |= FC_EX_DONE;
		fc_exch_समयr_cancel(ep);
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा fc_exch fc_quarantine_exch;

/**
 * fc_exch_ptr_get() - Return an exchange from an exchange pool
 * @pool:  Exchange Pool to get an exchange from
 * @index: Index of the exchange within the pool
 *
 * Use the index to get an exchange from within an exchange pool. exches
 * will poपूर्णांक to an array of exchange poपूर्णांकers. The index will select
 * the exchange within the array.
 */
अटल अंतरभूत काष्ठा fc_exch *fc_exch_ptr_get(काष्ठा fc_exch_pool *pool,
					      u16 index)
अणु
	काष्ठा fc_exch **exches = (काष्ठा fc_exch **)(pool + 1);
	वापस exches[index];
पूर्ण

/**
 * fc_exch_ptr_set() - Assign an exchange to a slot in an exchange pool
 * @pool:  The pool to assign the exchange to
 * @index: The index in the pool where the exchange will be asचिन्हित
 * @ep:	   The exchange to assign to the pool
 */
अटल अंतरभूत व्योम fc_exch_ptr_set(काष्ठा fc_exch_pool *pool, u16 index,
				   काष्ठा fc_exch *ep)
अणु
	((काष्ठा fc_exch **)(pool + 1))[index] = ep;
पूर्ण

/**
 * fc_exch_delete() - Delete an exchange
 * @ep: The exchange to be deleted
 */
अटल व्योम fc_exch_delete(काष्ठा fc_exch *ep)
अणु
	काष्ठा fc_exch_pool *pool;
	u16 index;

	pool = ep->pool;
	spin_lock_bh(&pool->lock);
	WARN_ON(pool->total_exches <= 0);
	pool->total_exches--;

	/* update cache of मुक्त slot */
	index = (ep->xid - ep->em->min_xid) >> fc_cpu_order;
	अगर (!(ep->state & FC_EX_QUARANTINE)) अणु
		अगर (pool->left == FC_XID_UNKNOWN)
			pool->left = index;
		अन्यथा अगर (pool->right == FC_XID_UNKNOWN)
			pool->right = index;
		अन्यथा
			pool->next_index = index;
		fc_exch_ptr_set(pool, index, शून्य);
	पूर्ण अन्यथा अणु
		fc_exch_ptr_set(pool, index, &fc_quarantine_exch);
	पूर्ण
	list_del(&ep->ex_list);
	spin_unlock_bh(&pool->lock);
	fc_exch_release(ep);	/* drop hold क्रम exch in mp */
पूर्ण

अटल पूर्णांक fc_seq_send_locked(काष्ठा fc_lport *lport, काष्ठा fc_seq *sp,
			      काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_exch *ep;
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	पूर्णांक error = -ENXIO;
	u32 f_ctl;
	u8 fh_type = fh->fh_type;

	ep = fc_seq_exch(sp);

	अगर (ep->esb_stat & (ESB_ST_COMPLETE | ESB_ST_ABNORMAL)) अणु
		fc_frame_मुक्त(fp);
		जाओ out;
	पूर्ण

	WARN_ON(!(ep->esb_stat & ESB_ST_SEQ_INIT));

	f_ctl = ntoh24(fh->fh_f_ctl);
	fc_exch_setup_hdr(ep, fp, f_ctl);
	fr_encaps(fp) = ep->encaps;

	/*
	 * update sequence count अगर this frame is carrying
	 * multiple FC frames when sequence offload is enabled
	 * by LLD.
	 */
	अगर (fr_max_payload(fp))
		sp->cnt += DIV_ROUND_UP((fr_len(fp) - माप(*fh)),
					fr_max_payload(fp));
	अन्यथा
		sp->cnt++;

	/*
	 * Send the frame.
	 */
	error = lport->tt.frame_send(lport, fp);

	अगर (fh_type == FC_TYPE_BLS)
		जाओ out;

	/*
	 * Update the exchange and sequence flags,
	 * assuming all frames क्रम the sequence have been sent.
	 * We can only be called to send once क्रम each sequence.
	 */
	ep->f_ctl = f_ctl & ~FC_FC_FIRST_SEQ;	/* not first seq */
	अगर (f_ctl & FC_FC_SEQ_INIT)
		ep->esb_stat &= ~ESB_ST_SEQ_INIT;
out:
	वापस error;
पूर्ण

/**
 * fc_seq_send() - Send a frame using existing sequence/exchange pair
 * @lport: The local port that the exchange will be sent on
 * @sp:	   The sequence to be sent
 * @fp:	   The frame to be sent on the exchange
 *
 * Note: The frame will be मुक्तd either by a direct call to fc_frame_मुक्त(fp)
 * or indirectly by calling libfc_function_ढाँचा.frame_send().
 */
पूर्णांक fc_seq_send(काष्ठा fc_lport *lport, काष्ठा fc_seq *sp, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_exch *ep;
	पूर्णांक error;
	ep = fc_seq_exch(sp);
	spin_lock_bh(&ep->ex_lock);
	error = fc_seq_send_locked(lport, sp, fp);
	spin_unlock_bh(&ep->ex_lock);
	वापस error;
पूर्ण
EXPORT_SYMBOL(fc_seq_send);

/**
 * fc_seq_alloc() - Allocate a sequence क्रम a given exchange
 * @ep:	    The exchange to allocate a new sequence क्रम
 * @seq_id: The sequence ID to be used
 *
 * We करोn't support multiple originated sequences on the same exchange.
 * By implication, any previously originated sequence on this exchange
 * is complete, and we पुनः_स्मृतिate the same sequence.
 */
अटल काष्ठा fc_seq *fc_seq_alloc(काष्ठा fc_exch *ep, u8 seq_id)
अणु
	काष्ठा fc_seq *sp;

	sp = &ep->seq;
	sp->ssb_stat = 0;
	sp->cnt = 0;
	sp->id = seq_id;
	वापस sp;
पूर्ण

/**
 * fc_seq_start_next_locked() - Allocate a new sequence on the same
 *				exchange as the supplied sequence
 * @sp: The sequence/exchange to get a new sequence क्रम
 */
अटल काष्ठा fc_seq *fc_seq_start_next_locked(काष्ठा fc_seq *sp)
अणु
	काष्ठा fc_exch *ep = fc_seq_exch(sp);

	sp = fc_seq_alloc(ep, ep->seq_id++);
	FC_EXCH_DBG(ep, "f_ctl %6x seq %2x\n",
		    ep->f_ctl, sp->id);
	वापस sp;
पूर्ण

/**
 * fc_seq_start_next() - Lock the exchange and get a new sequence
 *			 क्रम a given sequence/exchange pair
 * @sp: The sequence/exchange to get a new exchange क्रम
 */
काष्ठा fc_seq *fc_seq_start_next(काष्ठा fc_seq *sp)
अणु
	काष्ठा fc_exch *ep = fc_seq_exch(sp);

	spin_lock_bh(&ep->ex_lock);
	sp = fc_seq_start_next_locked(sp);
	spin_unlock_bh(&ep->ex_lock);

	वापस sp;
पूर्ण
EXPORT_SYMBOL(fc_seq_start_next);

/*
 * Set the response handler क्रम the exchange associated with a sequence.
 *
 * Note: May sleep अगर invoked from outside a response handler.
 */
व्योम fc_seq_set_resp(काष्ठा fc_seq *sp,
		     व्योम (*resp)(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *),
		     व्योम *arg)
अणु
	काष्ठा fc_exch *ep = fc_seq_exch(sp);
	DEFINE_WAIT(रुको);

	spin_lock_bh(&ep->ex_lock);
	जबतक (ep->resp_active && ep->resp_task != current) अणु
		prepare_to_रुको(&ep->resp_wq, &रुको, TASK_UNINTERRUPTIBLE);
		spin_unlock_bh(&ep->ex_lock);

		schedule();

		spin_lock_bh(&ep->ex_lock);
	पूर्ण
	finish_रुको(&ep->resp_wq, &रुको);
	ep->resp = resp;
	ep->arg = arg;
	spin_unlock_bh(&ep->ex_lock);
पूर्ण
EXPORT_SYMBOL(fc_seq_set_resp);

/**
 * fc_exch_पात_locked() - Abort an exchange
 * @ep:	The exchange to be पातed
 * @समयr_msec: The period of समय to रुको beक्रमe पातing
 *
 * Abort an exchange and sequence. Generally called because of a
 * exchange समयout or an पात from the upper layer.
 *
 * A समयr_msec can be specअगरied क्रम पात समयout, अगर non-zero
 * समयr_msec value is specअगरied then exchange resp handler
 * will be called with समयout error अगर no response to पात.
 *
 * Locking notes:  Called with exch lock held
 *
 * Return value: 0 on success अन्यथा error code
 */
अटल पूर्णांक fc_exch_पात_locked(काष्ठा fc_exch *ep,
				अचिन्हित पूर्णांक समयr_msec)
अणु
	काष्ठा fc_seq *sp;
	काष्ठा fc_frame *fp;
	पूर्णांक error;

	FC_EXCH_DBG(ep, "exch: abort, time %d msecs\n", समयr_msec);
	अगर (ep->esb_stat & (ESB_ST_COMPLETE | ESB_ST_ABNORMAL) ||
	    ep->state & (FC_EX_DONE | FC_EX_RST_CLEANUP)) अणु
		FC_EXCH_DBG(ep, "exch: already completed esb %x state %x\n",
			    ep->esb_stat, ep->state);
		वापस -ENXIO;
	पूर्ण

	/*
	 * Send the पात on a new sequence अगर possible.
	 */
	sp = fc_seq_start_next_locked(&ep->seq);
	अगर (!sp)
		वापस -ENOMEM;

	अगर (समयr_msec)
		fc_exch_समयr_set_locked(ep, समयr_msec);

	अगर (ep->sid) अणु
		/*
		 * Send an पात क्रम the sequence that समयd out.
		 */
		fp = fc_frame_alloc(ep->lp, 0);
		अगर (fp) अणु
			ep->esb_stat |= ESB_ST_SEQ_INIT;
			fc_fill_fc_hdr(fp, FC_RCTL_BA_ABTS, ep->did, ep->sid,
				       FC_TYPE_BLS, FC_FC_END_SEQ |
				       FC_FC_SEQ_INIT, 0);
			error = fc_seq_send_locked(ep->lp, sp, fp);
		पूर्ण अन्यथा अणु
			error = -ENOBUFS;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If not logged पूर्णांकo the fabric, करोn't send ABTS but leave
		 * sequence active until next समयout.
		 */
		error = 0;
	पूर्ण
	ep->esb_stat |= ESB_ST_ABNORMAL;
	वापस error;
पूर्ण

/**
 * fc_seq_exch_पात() - Abort an exchange and sequence
 * @req_sp:	The sequence to be पातed
 * @समयr_msec: The period of समय to रुको beक्रमe पातing
 *
 * Generally called because of a समयout or an पात from the upper layer.
 *
 * Return value: 0 on success अन्यथा error code
 */
पूर्णांक fc_seq_exch_पात(स्थिर काष्ठा fc_seq *req_sp, अचिन्हित पूर्णांक समयr_msec)
अणु
	काष्ठा fc_exch *ep;
	पूर्णांक error;

	ep = fc_seq_exch(req_sp);
	spin_lock_bh(&ep->ex_lock);
	error = fc_exch_पात_locked(ep, समयr_msec);
	spin_unlock_bh(&ep->ex_lock);
	वापस error;
पूर्ण

/**
 * fc_invoke_resp() - invoke ep->resp()
 * @ep:	   The exchange to be operated on
 * @fp:	   The frame poपूर्णांकer to pass through to ->resp()
 * @sp:	   The sequence poपूर्णांकer to pass through to ->resp()
 *
 * Notes:
 * It is assumed that after initialization finished (this means the
 * first unlock of ex_lock after fc_exch_alloc()) ep->resp and ep->arg are
 * modअगरied only via fc_seq_set_resp(). This guarantees that none of these
 * two variables changes अगर ep->resp_active > 0.
 *
 * If an fc_seq_set_resp() call is busy modअगरying ep->resp and ep->arg when
 * this function is invoked, the first spin_lock_bh() call in this function
 * will रुको until fc_seq_set_resp() has finished modअगरying these variables.
 *
 * Since fc_exch_करोne() invokes fc_seq_set_resp() it is guaranteed that that
 * ep->resp() won't be invoked after fc_exch_करोne() has वापसed.
 *
 * The response handler itself may invoke fc_exch_करोne(), which will clear the
 * ep->resp poपूर्णांकer.
 *
 * Return value:
 * Returns true अगर and only अगर ep->resp has been invoked.
 */
अटल bool fc_invoke_resp(काष्ठा fc_exch *ep, काष्ठा fc_seq *sp,
			   काष्ठा fc_frame *fp)
अणु
	व्योम (*resp)(काष्ठा fc_seq *, काष्ठा fc_frame *fp, व्योम *arg);
	व्योम *arg;
	bool res = false;

	spin_lock_bh(&ep->ex_lock);
	ep->resp_active++;
	अगर (ep->resp_task != current)
		ep->resp_task = !ep->resp_task ? current : शून्य;
	resp = ep->resp;
	arg = ep->arg;
	spin_unlock_bh(&ep->ex_lock);

	अगर (resp) अणु
		resp(sp, fp, arg);
		res = true;
	पूर्ण

	spin_lock_bh(&ep->ex_lock);
	अगर (--ep->resp_active == 0)
		ep->resp_task = शून्य;
	spin_unlock_bh(&ep->ex_lock);

	अगर (ep->resp_active == 0)
		wake_up(&ep->resp_wq);

	वापस res;
पूर्ण

/**
 * fc_exch_समयout() - Handle exchange समयr expiration
 * @work: The work_काष्ठा identअगरying the exchange that समयd out
 */
अटल व्योम fc_exch_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_exch *ep = container_of(work, काष्ठा fc_exch,
					  समयout_work.work);
	काष्ठा fc_seq *sp = &ep->seq;
	u32 e_stat;
	पूर्णांक rc = 1;

	FC_EXCH_DBG(ep, "Exchange timed out state %x\n", ep->state);

	spin_lock_bh(&ep->ex_lock);
	अगर (ep->state & (FC_EX_RST_CLEANUP | FC_EX_DONE))
		जाओ unlock;

	e_stat = ep->esb_stat;
	अगर (e_stat & ESB_ST_COMPLETE) अणु
		ep->esb_stat = e_stat & ~ESB_ST_REC_QUAL;
		spin_unlock_bh(&ep->ex_lock);
		अगर (e_stat & ESB_ST_REC_QUAL)
			fc_exch_rrq(ep);
		जाओ करोne;
	पूर्ण अन्यथा अणु
		अगर (e_stat & ESB_ST_ABNORMAL)
			rc = fc_exch_करोne_locked(ep);
		spin_unlock_bh(&ep->ex_lock);
		अगर (!rc)
			fc_exch_delete(ep);
		fc_invoke_resp(ep, sp, ERR_PTR(-FC_EX_TIMEOUT));
		fc_seq_set_resp(sp, शून्य, ep->arg);
		fc_seq_exch_पात(sp, 2 * ep->r_a_tov);
		जाओ करोne;
	पूर्ण
unlock:
	spin_unlock_bh(&ep->ex_lock);
करोne:
	/*
	 * This release matches the hold taken when the समयr was set.
	 */
	fc_exch_release(ep);
पूर्ण

/**
 * fc_exch_em_alloc() - Allocate an exchange from a specअगरied EM.
 * @lport: The local port that the exchange is क्रम
 * @mp:	   The exchange manager that will allocate the exchange
 *
 * Returns poपूर्णांकer to allocated fc_exch with exch lock held.
 */
अटल काष्ठा fc_exch *fc_exch_em_alloc(काष्ठा fc_lport *lport,
					काष्ठा fc_exch_mgr *mp)
अणु
	काष्ठा fc_exch *ep;
	अचिन्हित पूर्णांक cpu;
	u16 index;
	काष्ठा fc_exch_pool *pool;

	/* allocate memory क्रम exchange */
	ep = mempool_alloc(mp->ep_pool, GFP_ATOMIC);
	अगर (!ep) अणु
		atomic_inc(&mp->stats.no_मुक्त_exch);
		जाओ out;
	पूर्ण
	स_रखो(ep, 0, माप(*ep));

	cpu = get_cpu();
	pool = per_cpu_ptr(mp->pool, cpu);
	spin_lock_bh(&pool->lock);
	put_cpu();

	/* peek cache of मुक्त slot */
	अगर (pool->left != FC_XID_UNKNOWN) अणु
		अगर (!WARN_ON(fc_exch_ptr_get(pool, pool->left))) अणु
			index = pool->left;
			pool->left = FC_XID_UNKNOWN;
			जाओ hit;
		पूर्ण
	पूर्ण
	अगर (pool->right != FC_XID_UNKNOWN) अणु
		अगर (!WARN_ON(fc_exch_ptr_get(pool, pool->right))) अणु
			index = pool->right;
			pool->right = FC_XID_UNKNOWN;
			जाओ hit;
		पूर्ण
	पूर्ण

	index = pool->next_index;
	/* allocate new exch from pool */
	जबतक (fc_exch_ptr_get(pool, index)) अणु
		index = index == mp->pool_max_index ? 0 : index + 1;
		अगर (index == pool->next_index)
			जाओ err;
	पूर्ण
	pool->next_index = index == mp->pool_max_index ? 0 : index + 1;
hit:
	fc_exch_hold(ep);	/* hold क्रम exch in mp */
	spin_lock_init(&ep->ex_lock);
	/*
	 * Hold exch lock क्रम caller to prevent fc_exch_reset()
	 * from releasing exch	जबतक fc_exch_alloc() caller is
	 * still working on exch.
	 */
	spin_lock_bh(&ep->ex_lock);

	fc_exch_ptr_set(pool, index, ep);
	list_add_tail(&ep->ex_list, &pool->ex_list);
	fc_seq_alloc(ep, ep->seq_id++);
	pool->total_exches++;
	spin_unlock_bh(&pool->lock);

	/*
	 *  update exchange
	 */
	ep->oxid = ep->xid = (index << fc_cpu_order | cpu) + mp->min_xid;
	ep->em = mp;
	ep->pool = pool;
	ep->lp = lport;
	ep->f_ctl = FC_FC_FIRST_SEQ;	/* next seq is first seq */
	ep->rxid = FC_XID_UNKNOWN;
	ep->class = mp->class;
	ep->resp_active = 0;
	init_रुकोqueue_head(&ep->resp_wq);
	INIT_DELAYED_WORK(&ep->समयout_work, fc_exch_समयout);
out:
	वापस ep;
err:
	spin_unlock_bh(&pool->lock);
	atomic_inc(&mp->stats.no_मुक्त_exch_xid);
	mempool_मुक्त(ep, mp->ep_pool);
	वापस शून्य;
पूर्ण

/**
 * fc_exch_alloc() - Allocate an exchange from an EM on a
 *		     local port's list of EMs.
 * @lport: The local port that will own the exchange
 * @fp:	   The FC frame that the exchange will be क्रम
 *
 * This function walks the list of exchange manager(EM)
 * anchors to select an EM क्रम a new exchange allocation. The
 * EM is selected when a शून्य match function poपूर्णांकer is encountered
 * or when a call to a match function वापसs true.
 */
अटल काष्ठा fc_exch *fc_exch_alloc(काष्ठा fc_lport *lport,
				     काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_exch_mgr_anchor *ema;
	काष्ठा fc_exch *ep;

	list_क्रम_each_entry(ema, &lport->ema_list, ema_list) अणु
		अगर (!ema->match || ema->match(fp)) अणु
			ep = fc_exch_em_alloc(lport, ema->mp);
			अगर (ep)
				वापस ep;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * fc_exch_find() - Lookup and hold an exchange
 * @mp:	 The exchange manager to lookup the exchange from
 * @xid: The XID of the exchange to look up
 */
अटल काष्ठा fc_exch *fc_exch_find(काष्ठा fc_exch_mgr *mp, u16 xid)
अणु
	काष्ठा fc_lport *lport = mp->lport;
	काष्ठा fc_exch_pool *pool;
	काष्ठा fc_exch *ep = शून्य;
	u16 cpu = xid & fc_cpu_mask;

	अगर (xid == FC_XID_UNKNOWN)
		वापस शून्य;

	अगर (cpu >= nr_cpu_ids || !cpu_possible(cpu)) अणु
		pr_err("host%u: lport %6.6x: xid %d invalid CPU %d\n:",
		       lport->host->host_no, lport->port_id, xid, cpu);
		वापस शून्य;
	पूर्ण

	अगर ((xid >= mp->min_xid) && (xid <= mp->max_xid)) अणु
		pool = per_cpu_ptr(mp->pool, cpu);
		spin_lock_bh(&pool->lock);
		ep = fc_exch_ptr_get(pool, (xid - mp->min_xid) >> fc_cpu_order);
		अगर (ep == &fc_quarantine_exch) अणु
			FC_LPORT_DBG(lport, "xid %x quarantined\n", xid);
			ep = शून्य;
		पूर्ण
		अगर (ep) अणु
			WARN_ON(ep->xid != xid);
			fc_exch_hold(ep);
		पूर्ण
		spin_unlock_bh(&pool->lock);
	पूर्ण
	वापस ep;
पूर्ण


/**
 * fc_exch_करोne() - Indicate that an exchange/sequence tuple is complete and
 *		    the memory allocated क्रम the related objects may be मुक्तd.
 * @sp: The sequence that has completed
 *
 * Note: May sleep अगर invoked from outside a response handler.
 */
व्योम fc_exch_करोne(काष्ठा fc_seq *sp)
अणु
	काष्ठा fc_exch *ep = fc_seq_exch(sp);
	पूर्णांक rc;

	spin_lock_bh(&ep->ex_lock);
	rc = fc_exch_करोne_locked(ep);
	spin_unlock_bh(&ep->ex_lock);

	fc_seq_set_resp(sp, शून्य, ep->arg);
	अगर (!rc)
		fc_exch_delete(ep);
पूर्ण
EXPORT_SYMBOL(fc_exch_करोne);

/**
 * fc_exch_resp() - Allocate a new exchange क्रम a response frame
 * @lport: The local port that the exchange was क्रम
 * @mp:	   The exchange manager to allocate the exchange from
 * @fp:	   The response frame
 *
 * Sets the responder ID in the frame header.
 */
अटल काष्ठा fc_exch *fc_exch_resp(काष्ठा fc_lport *lport,
				    काष्ठा fc_exch_mgr *mp,
				    काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_exch *ep;
	काष्ठा fc_frame_header *fh;

	ep = fc_exch_alloc(lport, fp);
	अगर (ep) अणु
		ep->class = fc_frame_class(fp);

		/*
		 * Set EX_CTX indicating we're responding on this exchange.
		 */
		ep->f_ctl |= FC_FC_EX_CTX;	/* we're responding */
		ep->f_ctl &= ~FC_FC_FIRST_SEQ;	/* not new */
		fh = fc_frame_header_get(fp);
		ep->sid = ntoh24(fh->fh_d_id);
		ep->did = ntoh24(fh->fh_s_id);
		ep->oid = ep->did;

		/*
		 * Allocated exchange has placed the XID in the
		 * originator field. Move it to the responder field,
		 * and set the originator XID from the frame.
		 */
		ep->rxid = ep->xid;
		ep->oxid = ntohs(fh->fh_ox_id);
		ep->esb_stat |= ESB_ST_RESP | ESB_ST_SEQ_INIT;
		अगर ((ntoh24(fh->fh_f_ctl) & FC_FC_SEQ_INIT) == 0)
			ep->esb_stat &= ~ESB_ST_SEQ_INIT;

		fc_exch_hold(ep);	/* hold क्रम caller */
		spin_unlock_bh(&ep->ex_lock);	/* lock from fc_exch_alloc */
	पूर्ण
	वापस ep;
पूर्ण

/**
 * fc_seq_lookup_recip() - Find a sequence where the other end
 *			   originated the sequence
 * @lport: The local port that the frame was sent to
 * @mp:	   The Exchange Manager to lookup the exchange from
 * @fp:	   The frame associated with the sequence we're looking क्रम
 *
 * If fc_pf_rjt_reason is FC_RJT_NONE then this function will have a hold
 * on the ep that should be released by the caller.
 */
अटल क्रमागत fc_pf_rjt_reason fc_seq_lookup_recip(काष्ठा fc_lport *lport,
						 काष्ठा fc_exch_mgr *mp,
						 काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fc_exch *ep = शून्य;
	काष्ठा fc_seq *sp = शून्य;
	क्रमागत fc_pf_rjt_reason reject = FC_RJT_NONE;
	u32 f_ctl;
	u16 xid;

	f_ctl = ntoh24(fh->fh_f_ctl);
	WARN_ON((f_ctl & FC_FC_SEQ_CTX) != 0);

	/*
	 * Lookup or create the exchange अगर we will be creating the sequence.
	 */
	अगर (f_ctl & FC_FC_EX_CTX) अणु
		xid = ntohs(fh->fh_ox_id);	/* we originated exch */
		ep = fc_exch_find(mp, xid);
		अगर (!ep) अणु
			atomic_inc(&mp->stats.xid_not_found);
			reject = FC_RJT_OX_ID;
			जाओ out;
		पूर्ण
		अगर (ep->rxid == FC_XID_UNKNOWN)
			ep->rxid = ntohs(fh->fh_rx_id);
		अन्यथा अगर (ep->rxid != ntohs(fh->fh_rx_id)) अणु
			reject = FC_RJT_OX_ID;
			जाओ rel;
		पूर्ण
	पूर्ण अन्यथा अणु
		xid = ntohs(fh->fh_rx_id);	/* we are the responder */

		/*
		 * Special हाल क्रम MDS issuing an ELS TEST with a
		 * bad rxid of 0.
		 * XXX take this out once we करो the proper reject.
		 */
		अगर (xid == 0 && fh->fh_r_ctl == FC_RCTL_ELS_REQ &&
		    fc_frame_payload_op(fp) == ELS_TEST) अणु
			fh->fh_rx_id = htons(FC_XID_UNKNOWN);
			xid = FC_XID_UNKNOWN;
		पूर्ण

		/*
		 * new sequence - find the exchange
		 */
		ep = fc_exch_find(mp, xid);
		अगर ((f_ctl & FC_FC_FIRST_SEQ) && fc_sof_is_init(fr_sof(fp))) अणु
			अगर (ep) अणु
				atomic_inc(&mp->stats.xid_busy);
				reject = FC_RJT_RX_ID;
				जाओ rel;
			पूर्ण
			ep = fc_exch_resp(lport, mp, fp);
			अगर (!ep) अणु
				reject = FC_RJT_EXCH_EST;	/* XXX */
				जाओ out;
			पूर्ण
			xid = ep->xid;	/* get our XID */
		पूर्ण अन्यथा अगर (!ep) अणु
			atomic_inc(&mp->stats.xid_not_found);
			reject = FC_RJT_RX_ID;	/* XID not found */
			जाओ out;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ep->ex_lock);
	/*
	 * At this poपूर्णांक, we have the exchange held.
	 * Find or create the sequence.
	 */
	अगर (fc_sof_is_init(fr_sof(fp))) अणु
		sp = &ep->seq;
		sp->ssb_stat |= SSB_ST_RESP;
		sp->id = fh->fh_seq_id;
	पूर्ण अन्यथा अणु
		sp = &ep->seq;
		अगर (sp->id != fh->fh_seq_id) अणु
			atomic_inc(&mp->stats.seq_not_found);
			अगर (f_ctl & FC_FC_END_SEQ) अणु
				/*
				 * Update sequence_id based on incoming last
				 * frame of sequence exchange. This is needed
				 * क्रम FC target where DDP has been used
				 * on target where, stack is indicated only
				 * about last frame's (payload _header) header.
				 * Whereas "seq_id" which is part of
				 * frame_header is allocated by initiator
				 * which is totally dअगरferent from "seq_id"
				 * allocated when XFER_RDY was sent by target.
				 * To aव्योम false -ve which results पूर्णांकo not
				 * sending RSP, hence ग_लिखो request on other
				 * end never finishes.
				 */
				sp->ssb_stat |= SSB_ST_RESP;
				sp->id = fh->fh_seq_id;
			पूर्ण अन्यथा अणु
				spin_unlock_bh(&ep->ex_lock);

				/* sequence/exch should exist */
				reject = FC_RJT_SEQ_ID;
				जाओ rel;
			पूर्ण
		पूर्ण
	पूर्ण
	WARN_ON(ep != fc_seq_exch(sp));

	अगर (f_ctl & FC_FC_SEQ_INIT)
		ep->esb_stat |= ESB_ST_SEQ_INIT;
	spin_unlock_bh(&ep->ex_lock);

	fr_seq(fp) = sp;
out:
	वापस reject;
rel:
	fc_exch_करोne(&ep->seq);
	fc_exch_release(ep);	/* hold from fc_exch_find/fc_exch_resp */
	वापस reject;
पूर्ण

/**
 * fc_seq_lookup_orig() - Find a sequence where this end
 *			  originated the sequence
 * @mp:	   The Exchange Manager to lookup the exchange from
 * @fp:	   The frame associated with the sequence we're looking क्रम
 *
 * Does not hold the sequence क्रम the caller.
 */
अटल काष्ठा fc_seq *fc_seq_lookup_orig(काष्ठा fc_exch_mgr *mp,
					 काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fc_exch *ep;
	काष्ठा fc_seq *sp = शून्य;
	u32 f_ctl;
	u16 xid;

	f_ctl = ntoh24(fh->fh_f_ctl);
	WARN_ON((f_ctl & FC_FC_SEQ_CTX) != FC_FC_SEQ_CTX);
	xid = ntohs((f_ctl & FC_FC_EX_CTX) ? fh->fh_ox_id : fh->fh_rx_id);
	ep = fc_exch_find(mp, xid);
	अगर (!ep)
		वापस शून्य;
	अगर (ep->seq.id == fh->fh_seq_id) अणु
		/*
		 * Save the RX_ID अगर we didn't previously know it.
		 */
		sp = &ep->seq;
		अगर ((f_ctl & FC_FC_EX_CTX) != 0 &&
		    ep->rxid == FC_XID_UNKNOWN) अणु
			ep->rxid = ntohs(fh->fh_rx_id);
		पूर्ण
	पूर्ण
	fc_exch_release(ep);
	वापस sp;
पूर्ण

/**
 * fc_exch_set_addr() - Set the source and destination IDs क्रम an exchange
 * @ep:	     The exchange to set the addresses क्रम
 * @orig_id: The originator's ID
 * @resp_id: The responder's ID
 *
 * Note this must be करोne beक्रमe the first sequence of the exchange is sent.
 */
अटल व्योम fc_exch_set_addr(काष्ठा fc_exch *ep,
			     u32 orig_id, u32 resp_id)
अणु
	ep->oid = orig_id;
	अगर (ep->esb_stat & ESB_ST_RESP) अणु
		ep->sid = resp_id;
		ep->did = orig_id;
	पूर्ण अन्यथा अणु
		ep->sid = orig_id;
		ep->did = resp_id;
	पूर्ण
पूर्ण

/**
 * fc_seq_els_rsp_send() - Send an ELS response using inक्रमmation from
 *			   the existing sequence/exchange.
 * @fp:	      The received frame
 * @els_cmd:  The ELS command to be sent
 * @els_data: The ELS data to be sent
 *
 * The received frame is not मुक्तd.
 */
व्योम fc_seq_els_rsp_send(काष्ठा fc_frame *fp, क्रमागत fc_els_cmd els_cmd,
			 काष्ठा fc_seq_els_data *els_data)
अणु
	चयन (els_cmd) अणु
	हाल ELS_LS_RJT:
		fc_seq_ls_rjt(fp, els_data->reason, els_data->explan);
		अवरोध;
	हाल ELS_LS_ACC:
		fc_seq_ls_acc(fp);
		अवरोध;
	हाल ELS_RRQ:
		fc_exch_els_rrq(fp);
		अवरोध;
	हाल ELS_REC:
		fc_exch_els_rec(fp);
		अवरोध;
	शेष:
		FC_LPORT_DBG(fr_dev(fp), "Invalid ELS CMD:%x\n", els_cmd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fc_seq_els_rsp_send);

/**
 * fc_seq_send_last() - Send a sequence that is the last in the exchange
 * @sp:	     The sequence that is to be sent
 * @fp:	     The frame that will be sent on the sequence
 * @rctl:    The R_CTL inक्रमmation to be sent
 * @fh_type: The frame header type
 */
अटल व्योम fc_seq_send_last(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			     क्रमागत fc_rctl rctl, क्रमागत fc_fh_type fh_type)
अणु
	u32 f_ctl;
	काष्ठा fc_exch *ep = fc_seq_exch(sp);

	f_ctl = FC_FC_LAST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT;
	f_ctl |= ep->f_ctl;
	fc_fill_fc_hdr(fp, rctl, ep->did, ep->sid, fh_type, f_ctl, 0);
	fc_seq_send_locked(ep->lp, sp, fp);
पूर्ण

/**
 * fc_seq_send_ack() - Send an acknowledgement that we've received a frame
 * @sp:	   The sequence to send the ACK on
 * @rx_fp: The received frame that is being acknoledged
 *
 * Send ACK_1 (or equiv.) indicating we received something.
 */
अटल व्योम fc_seq_send_ack(काष्ठा fc_seq *sp, स्थिर काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *rx_fh;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_exch *ep = fc_seq_exch(sp);
	काष्ठा fc_lport *lport = ep->lp;
	अचिन्हित पूर्णांक f_ctl;

	/*
	 * Don't send ACKs क्रम class 3.
	 */
	अगर (fc_sof_needs_ack(fr_sof(rx_fp))) अणु
		fp = fc_frame_alloc(lport, 0);
		अगर (!fp) अणु
			FC_EXCH_DBG(ep, "Drop ACK request, out of memory\n");
			वापस;
		पूर्ण

		fh = fc_frame_header_get(fp);
		fh->fh_r_ctl = FC_RCTL_ACK_1;
		fh->fh_type = FC_TYPE_BLS;

		/*
		 * Form f_ctl by inverting EX_CTX and SEQ_CTX (bits 23, 22).
		 * Echo FIRST_SEQ, LAST_SEQ, END_SEQ, END_CONN, SEQ_INIT.
		 * Bits 9-8 are meaningful (retransmitted or unidirectional).
		 * Last ACK uses bits 7-6 (जारी sequence),
		 * bits 5-4 are meaningful (what kind of ACK to use).
		 */
		rx_fh = fc_frame_header_get(rx_fp);
		f_ctl = ntoh24(rx_fh->fh_f_ctl);
		f_ctl &= FC_FC_EX_CTX | FC_FC_SEQ_CTX |
			FC_FC_FIRST_SEQ | FC_FC_LAST_SEQ |
			FC_FC_END_SEQ | FC_FC_END_CONN | FC_FC_SEQ_INIT |
			FC_FC_RETX_SEQ | FC_FC_UNI_TX;
		f_ctl ^= FC_FC_EX_CTX | FC_FC_SEQ_CTX;
		hton24(fh->fh_f_ctl, f_ctl);

		fc_exch_setup_hdr(ep, fp, f_ctl);
		fh->fh_seq_id = rx_fh->fh_seq_id;
		fh->fh_seq_cnt = rx_fh->fh_seq_cnt;
		fh->fh_parm_offset = htonl(1);	/* ack single frame */

		fr_sof(fp) = fr_sof(rx_fp);
		अगर (f_ctl & FC_FC_END_SEQ)
			fr_eof(fp) = FC_खातापूर्ण_T;
		अन्यथा
			fr_eof(fp) = FC_खातापूर्ण_N;

		lport->tt.frame_send(lport, fp);
	पूर्ण
पूर्ण

/**
 * fc_exch_send_ba_rjt() - Send BLS Reject
 * @rx_fp:  The frame being rejected
 * @reason: The reason the frame is being rejected
 * @explan: The explanation क्रम the rejection
 *
 * This is क्रम rejecting BA_ABTS only.
 */
अटल व्योम fc_exch_send_ba_rjt(काष्ठा fc_frame *rx_fp,
				क्रमागत fc_ba_rjt_reason reason,
				क्रमागत fc_ba_rjt_explan explan)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *rx_fh;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_ba_rjt *rp;
	काष्ठा fc_seq *sp;
	काष्ठा fc_lport *lport;
	अचिन्हित पूर्णांक f_ctl;

	lport = fr_dev(rx_fp);
	sp = fr_seq(rx_fp);
	fp = fc_frame_alloc(lport, माप(*rp));
	अगर (!fp) अणु
		FC_EXCH_DBG(fc_seq_exch(sp),
			     "Drop BA_RJT request, out of memory\n");
		वापस;
	पूर्ण
	fh = fc_frame_header_get(fp);
	rx_fh = fc_frame_header_get(rx_fp);

	स_रखो(fh, 0, माप(*fh) + माप(*rp));

	rp = fc_frame_payload_get(fp, माप(*rp));
	rp->br_reason = reason;
	rp->br_explan = explan;

	/*
	 * seq_id, cs_ctl, df_ctl and param/offset are zero.
	 */
	स_नकल(fh->fh_s_id, rx_fh->fh_d_id, 3);
	स_नकल(fh->fh_d_id, rx_fh->fh_s_id, 3);
	fh->fh_ox_id = rx_fh->fh_ox_id;
	fh->fh_rx_id = rx_fh->fh_rx_id;
	fh->fh_seq_cnt = rx_fh->fh_seq_cnt;
	fh->fh_r_ctl = FC_RCTL_BA_RJT;
	fh->fh_type = FC_TYPE_BLS;

	/*
	 * Form f_ctl by inverting EX_CTX and SEQ_CTX (bits 23, 22).
	 * Echo FIRST_SEQ, LAST_SEQ, END_SEQ, END_CONN, SEQ_INIT.
	 * Bits 9-8 are meaningful (retransmitted or unidirectional).
	 * Last ACK uses bits 7-6 (जारी sequence),
	 * bits 5-4 are meaningful (what kind of ACK to use).
	 * Always set LAST_SEQ, END_SEQ.
	 */
	f_ctl = ntoh24(rx_fh->fh_f_ctl);
	f_ctl &= FC_FC_EX_CTX | FC_FC_SEQ_CTX |
		FC_FC_END_CONN | FC_FC_SEQ_INIT |
		FC_FC_RETX_SEQ | FC_FC_UNI_TX;
	f_ctl ^= FC_FC_EX_CTX | FC_FC_SEQ_CTX;
	f_ctl |= FC_FC_LAST_SEQ | FC_FC_END_SEQ;
	f_ctl &= ~FC_FC_FIRST_SEQ;
	hton24(fh->fh_f_ctl, f_ctl);

	fr_sof(fp) = fc_sof_class(fr_sof(rx_fp));
	fr_eof(fp) = FC_खातापूर्ण_T;
	अगर (fc_sof_needs_ack(fr_sof(fp)))
		fr_eof(fp) = FC_खातापूर्ण_N;

	lport->tt.frame_send(lport, fp);
पूर्ण

/**
 * fc_exch_recv_abts() - Handle an incoming ABTS
 * @ep:	   The exchange the पात was on
 * @rx_fp: The ABTS frame
 *
 * This would be क्रम target mode usually, but could be due to lost
 * FCP transfer पढ़ोy, confirm or RRQ. We always handle this as an
 * exchange पात, ignoring the parameter.
 */
अटल व्योम fc_exch_recv_abts(काष्ठा fc_exch *ep, काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_ba_acc *ap;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_seq *sp;

	अगर (!ep)
		जाओ reject;

	FC_EXCH_DBG(ep, "exch: ABTS received\n");
	fp = fc_frame_alloc(ep->lp, माप(*ap));
	अगर (!fp) अणु
		FC_EXCH_DBG(ep, "Drop ABTS request, out of memory\n");
		जाओ मुक्त;
	पूर्ण

	spin_lock_bh(&ep->ex_lock);
	अगर (ep->esb_stat & ESB_ST_COMPLETE) अणु
		spin_unlock_bh(&ep->ex_lock);
		FC_EXCH_DBG(ep, "exch: ABTS rejected, exchange complete\n");
		fc_frame_मुक्त(fp);
		जाओ reject;
	पूर्ण
	अगर (!(ep->esb_stat & ESB_ST_REC_QUAL)) अणु
		ep->esb_stat |= ESB_ST_REC_QUAL;
		fc_exch_hold(ep);		/* hold क्रम REC_QUAL */
	पूर्ण
	fc_exch_समयr_set_locked(ep, ep->r_a_tov);
	fh = fc_frame_header_get(fp);
	ap = fc_frame_payload_get(fp, माप(*ap));
	स_रखो(ap, 0, माप(*ap));
	sp = &ep->seq;
	ap->ba_high_seq_cnt = htons(0xffff);
	अगर (sp->ssb_stat & SSB_ST_RESP) अणु
		ap->ba_seq_id = sp->id;
		ap->ba_seq_id_val = FC_BA_SEQ_ID_VAL;
		ap->ba_high_seq_cnt = fh->fh_seq_cnt;
		ap->ba_low_seq_cnt = htons(sp->cnt);
	पूर्ण
	sp = fc_seq_start_next_locked(sp);
	fc_seq_send_last(sp, fp, FC_RCTL_BA_ACC, FC_TYPE_BLS);
	ep->esb_stat |= ESB_ST_ABNORMAL;
	spin_unlock_bh(&ep->ex_lock);

मुक्त:
	fc_frame_मुक्त(rx_fp);
	वापस;

reject:
	fc_exch_send_ba_rjt(rx_fp, FC_BA_RJT_UNABLE, FC_BA_RJT_INV_XID);
	जाओ मुक्त;
पूर्ण

/**
 * fc_seq_assign() - Assign exchange and sequence क्रम incoming request
 * @lport: The local port that received the request
 * @fp:    The request frame
 *
 * On success, the sequence poपूर्णांकer will be वापसed and also in fr_seq(@fp).
 * A reference will be held on the exchange/sequence क्रम the caller, which
 * must call fc_seq_release().
 */
काष्ठा fc_seq *fc_seq_assign(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_exch_mgr_anchor *ema;

	WARN_ON(lport != fr_dev(fp));
	WARN_ON(fr_seq(fp));
	fr_seq(fp) = शून्य;

	list_क्रम_each_entry(ema, &lport->ema_list, ema_list)
		अगर ((!ema->match || ema->match(fp)) &&
		    fc_seq_lookup_recip(lport, ema->mp, fp) == FC_RJT_NONE)
			अवरोध;
	वापस fr_seq(fp);
पूर्ण
EXPORT_SYMBOL(fc_seq_assign);

/**
 * fc_seq_release() - Release the hold
 * @sp:    The sequence.
 */
व्योम fc_seq_release(काष्ठा fc_seq *sp)
अणु
	fc_exch_release(fc_seq_exch(sp));
पूर्ण
EXPORT_SYMBOL(fc_seq_release);

/**
 * fc_exch_recv_req() - Handler क्रम an incoming request
 * @lport: The local port that received the request
 * @mp:	   The EM that the exchange is on
 * @fp:	   The request frame
 *
 * This is used when the other end is originating the exchange
 * and the sequence.
 */
अटल व्योम fc_exch_recv_req(काष्ठा fc_lport *lport, काष्ठा fc_exch_mgr *mp,
			     काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fc_seq *sp = शून्य;
	काष्ठा fc_exch *ep = शून्य;
	क्रमागत fc_pf_rjt_reason reject;

	/* We can have the wrong fc_lport at this poपूर्णांक with NPIV, which is a
	 * problem now that we know a new exchange needs to be allocated
	 */
	lport = fc_vport_id_lookup(lport, ntoh24(fh->fh_d_id));
	अगर (!lport) अणु
		fc_frame_मुक्त(fp);
		वापस;
	पूर्ण
	fr_dev(fp) = lport;

	BUG_ON(fr_seq(fp));		/* XXX हटाओ later */

	/*
	 * If the RX_ID is 0xffff, करोn't allocate an exchange.
	 * The upper-level protocol may request one later, अगर needed.
	 */
	अगर (fh->fh_rx_id == htons(FC_XID_UNKNOWN))
		वापस fc_lport_recv(lport, fp);

	reject = fc_seq_lookup_recip(lport, mp, fp);
	अगर (reject == FC_RJT_NONE) अणु
		sp = fr_seq(fp);	/* sequence will be held */
		ep = fc_seq_exch(sp);
		fc_seq_send_ack(sp, fp);
		ep->encaps = fr_encaps(fp);

		/*
		 * Call the receive function.
		 *
		 * The receive function may allocate a new sequence
		 * over the old one, so we shouldn't change the
		 * sequence after this.
		 *
		 * The frame will be मुक्तd by the receive function.
		 * If new exch resp handler is valid then call that
		 * first.
		 */
		अगर (!fc_invoke_resp(ep, sp, fp))
			fc_lport_recv(lport, fp);
		fc_exch_release(ep);	/* release from lookup */
	पूर्ण अन्यथा अणु
		FC_LPORT_DBG(lport, "exch/seq lookup failed: reject %x\n",
			     reject);
		fc_frame_मुक्त(fp);
	पूर्ण
पूर्ण

/**
 * fc_exch_recv_seq_resp() - Handler क्रम an incoming response where the other
 *			     end is the originator of the sequence that is a
 *			     response to our initial exchange
 * @mp: The EM that the exchange is on
 * @fp: The response frame
 */
अटल व्योम fc_exch_recv_seq_resp(काष्ठा fc_exch_mgr *mp, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fc_seq *sp;
	काष्ठा fc_exch *ep;
	क्रमागत fc_sof sof;
	u32 f_ctl;
	पूर्णांक rc;

	ep = fc_exch_find(mp, ntohs(fh->fh_ox_id));
	अगर (!ep) अणु
		atomic_inc(&mp->stats.xid_not_found);
		जाओ out;
	पूर्ण
	अगर (ep->esb_stat & ESB_ST_COMPLETE) अणु
		atomic_inc(&mp->stats.xid_not_found);
		जाओ rel;
	पूर्ण
	अगर (ep->rxid == FC_XID_UNKNOWN)
		ep->rxid = ntohs(fh->fh_rx_id);
	अगर (ep->sid != 0 && ep->sid != ntoh24(fh->fh_d_id)) अणु
		atomic_inc(&mp->stats.xid_not_found);
		जाओ rel;
	पूर्ण
	अगर (ep->did != ntoh24(fh->fh_s_id) &&
	    ep->did != FC_FID_FLOGI) अणु
		atomic_inc(&mp->stats.xid_not_found);
		जाओ rel;
	पूर्ण
	sof = fr_sof(fp);
	sp = &ep->seq;
	अगर (fc_sof_is_init(sof)) अणु
		sp->ssb_stat |= SSB_ST_RESP;
		sp->id = fh->fh_seq_id;
	पूर्ण

	f_ctl = ntoh24(fh->fh_f_ctl);
	fr_seq(fp) = sp;

	spin_lock_bh(&ep->ex_lock);
	अगर (f_ctl & FC_FC_SEQ_INIT)
		ep->esb_stat |= ESB_ST_SEQ_INIT;
	spin_unlock_bh(&ep->ex_lock);

	अगर (fc_sof_needs_ack(sof))
		fc_seq_send_ack(sp, fp);

	अगर (fh->fh_type != FC_TYPE_FCP && fr_eof(fp) == FC_खातापूर्ण_T &&
	    (f_ctl & (FC_FC_LAST_SEQ | FC_FC_END_SEQ)) ==
	    (FC_FC_LAST_SEQ | FC_FC_END_SEQ)) अणु
		spin_lock_bh(&ep->ex_lock);
		rc = fc_exch_करोne_locked(ep);
		WARN_ON(fc_seq_exch(sp) != ep);
		spin_unlock_bh(&ep->ex_lock);
		अगर (!rc) अणु
			fc_exch_delete(ep);
		पूर्ण अन्यथा अणु
			FC_EXCH_DBG(ep, "ep is completed already,"
					"hence skip calling the resp\n");
			जाओ skip_resp;
		पूर्ण
	पूर्ण

	/*
	 * Call the receive function.
	 * The sequence is held (has a refcnt) क्रम us,
	 * but not क्रम the receive function.
	 *
	 * The receive function may allocate a new sequence
	 * over the old one, so we shouldn't change the
	 * sequence after this.
	 *
	 * The frame will be मुक्तd by the receive function.
	 * If new exch resp handler is valid then call that
	 * first.
	 */
	अगर (!fc_invoke_resp(ep, sp, fp))
		fc_frame_मुक्त(fp);

skip_resp:
	fc_exch_release(ep);
	वापस;
rel:
	fc_exch_release(ep);
out:
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_exch_recv_resp() - Handler क्रम a sequence where other end is
 *			 responding to our sequence
 * @mp: The EM that the exchange is on
 * @fp: The response frame
 */
अटल व्योम fc_exch_recv_resp(काष्ठा fc_exch_mgr *mp, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_seq *sp;

	sp = fc_seq_lookup_orig(mp, fp);	/* करोesn't hold sequence */

	अगर (!sp)
		atomic_inc(&mp->stats.xid_not_found);
	अन्यथा
		atomic_inc(&mp->stats.non_bls_resp);

	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_exch_abts_resp() - Handler क्रम a response to an ABT
 * @ep: The exchange that the frame is on
 * @fp: The response frame
 *
 * This response would be to an ABTS cancelling an exchange or sequence.
 * The response can be either BA_ACC or BA_RJT
 */
अटल व्योम fc_exch_abts_resp(काष्ठा fc_exch *ep, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_ba_acc *ap;
	काष्ठा fc_seq *sp;
	u16 low;
	u16 high;
	पूर्णांक rc = 1, has_rec = 0;

	fh = fc_frame_header_get(fp);
	FC_EXCH_DBG(ep, "exch: BLS rctl %x - %s\n", fh->fh_r_ctl,
		    fc_exch_rctl_name(fh->fh_r_ctl));

	अगर (cancel_delayed_work_sync(&ep->समयout_work)) अणु
		FC_EXCH_DBG(ep, "Exchange timer canceled due to ABTS response\n");
		fc_exch_release(ep);	/* release from pending समयr hold */
	पूर्ण

	spin_lock_bh(&ep->ex_lock);
	चयन (fh->fh_r_ctl) अणु
	हाल FC_RCTL_BA_ACC:
		ap = fc_frame_payload_get(fp, माप(*ap));
		अगर (!ap)
			अवरोध;

		/*
		 * Decide whether to establish a Recovery Qualअगरier.
		 * We करो this अगर there is a non-empty SEQ_CNT range and
		 * SEQ_ID is the same as the one we पातed.
		 */
		low = ntohs(ap->ba_low_seq_cnt);
		high = ntohs(ap->ba_high_seq_cnt);
		अगर ((ep->esb_stat & ESB_ST_REC_QUAL) == 0 &&
		    (ap->ba_seq_id_val != FC_BA_SEQ_ID_VAL ||
		     ap->ba_seq_id == ep->seq_id) && low != high) अणु
			ep->esb_stat |= ESB_ST_REC_QUAL;
			fc_exch_hold(ep);  /* hold क्रम recovery qualअगरier */
			has_rec = 1;
		पूर्ण
		अवरोध;
	हाल FC_RCTL_BA_RJT:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* करो we need to करो some other checks here. Can we reuse more of
	 * fc_exch_recv_seq_resp
	 */
	sp = &ep->seq;
	/*
	 * करो we want to check END_SEQ as well as LAST_SEQ here?
	 */
	अगर (ep->fh_type != FC_TYPE_FCP &&
	    ntoh24(fh->fh_f_ctl) & FC_FC_LAST_SEQ)
		rc = fc_exch_करोne_locked(ep);
	spin_unlock_bh(&ep->ex_lock);

	fc_exch_hold(ep);
	अगर (!rc)
		fc_exch_delete(ep);
	अगर (!fc_invoke_resp(ep, sp, fp))
		fc_frame_मुक्त(fp);
	अगर (has_rec)
		fc_exch_समयr_set(ep, ep->r_a_tov);
	fc_exch_release(ep);
पूर्ण

/**
 * fc_exch_recv_bls() - Handler क्रम a BLS sequence
 * @mp: The EM that the exchange is on
 * @fp: The request frame
 *
 * The BLS frame is always a sequence initiated by the remote side.
 * We may be either the originator or recipient of the exchange.
 */
अटल व्योम fc_exch_recv_bls(काष्ठा fc_exch_mgr *mp, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_exch *ep;
	u32 f_ctl;

	fh = fc_frame_header_get(fp);
	f_ctl = ntoh24(fh->fh_f_ctl);
	fr_seq(fp) = शून्य;

	ep = fc_exch_find(mp, (f_ctl & FC_FC_EX_CTX) ?
			  ntohs(fh->fh_ox_id) : ntohs(fh->fh_rx_id));
	अगर (ep && (f_ctl & FC_FC_SEQ_INIT)) अणु
		spin_lock_bh(&ep->ex_lock);
		ep->esb_stat |= ESB_ST_SEQ_INIT;
		spin_unlock_bh(&ep->ex_lock);
	पूर्ण
	अगर (f_ctl & FC_FC_SEQ_CTX) अणु
		/*
		 * A response to a sequence we initiated.
		 * This should only be ACKs क्रम class 2 or F.
		 */
		चयन (fh->fh_r_ctl) अणु
		हाल FC_RCTL_ACK_1:
		हाल FC_RCTL_ACK_0:
			अवरोध;
		शेष:
			अगर (ep)
				FC_EXCH_DBG(ep, "BLS rctl %x - %s received\n",
					    fh->fh_r_ctl,
					    fc_exch_rctl_name(fh->fh_r_ctl));
			अवरोध;
		पूर्ण
		fc_frame_मुक्त(fp);
	पूर्ण अन्यथा अणु
		चयन (fh->fh_r_ctl) अणु
		हाल FC_RCTL_BA_RJT:
		हाल FC_RCTL_BA_ACC:
			अगर (ep)
				fc_exch_abts_resp(ep, fp);
			अन्यथा
				fc_frame_मुक्त(fp);
			अवरोध;
		हाल FC_RCTL_BA_ABTS:
			अगर (ep)
				fc_exch_recv_abts(ep, fp);
			अन्यथा
				fc_frame_मुक्त(fp);
			अवरोध;
		शेष:			/* ignore junk */
			fc_frame_मुक्त(fp);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ep)
		fc_exch_release(ep);	/* release hold taken by fc_exch_find */
पूर्ण

/**
 * fc_seq_ls_acc() - Accept sequence with LS_ACC
 * @rx_fp: The received frame, not मुक्तd here.
 *
 * If this fails due to allocation or transmit congestion, assume the
 * originator will repeat the sequence.
 */
अटल व्योम fc_seq_ls_acc(काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_els_ls_acc *acc;
	काष्ठा fc_frame *fp;
	काष्ठा fc_seq *sp;

	lport = fr_dev(rx_fp);
	sp = fr_seq(rx_fp);
	fp = fc_frame_alloc(lport, माप(*acc));
	अगर (!fp) अणु
		FC_EXCH_DBG(fc_seq_exch(sp),
			    "exch: drop LS_ACC, out of memory\n");
		वापस;
	पूर्ण
	acc = fc_frame_payload_get(fp, माप(*acc));
	स_रखो(acc, 0, माप(*acc));
	acc->la_cmd = ELS_LS_ACC;
	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
पूर्ण

/**
 * fc_seq_ls_rjt() - Reject a sequence with ELS LS_RJT
 * @rx_fp: The received frame, not मुक्तd here.
 * @reason: The reason the sequence is being rejected
 * @explan: The explanation क्रम the rejection
 *
 * If this fails due to allocation or transmit congestion, assume the
 * originator will repeat the sequence.
 */
अटल व्योम fc_seq_ls_rjt(काष्ठा fc_frame *rx_fp, क्रमागत fc_els_rjt_reason reason,
			  क्रमागत fc_els_rjt_explan explan)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_els_ls_rjt *rjt;
	काष्ठा fc_frame *fp;
	काष्ठा fc_seq *sp;

	lport = fr_dev(rx_fp);
	sp = fr_seq(rx_fp);
	fp = fc_frame_alloc(lport, माप(*rjt));
	अगर (!fp) अणु
		FC_EXCH_DBG(fc_seq_exch(sp),
			    "exch: drop LS_ACC, out of memory\n");
		वापस;
	पूर्ण
	rjt = fc_frame_payload_get(fp, माप(*rjt));
	स_रखो(rjt, 0, माप(*rjt));
	rjt->er_cmd = ELS_LS_RJT;
	rjt->er_reason = reason;
	rjt->er_explan = explan;
	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
पूर्ण

/**
 * fc_exch_reset() - Reset an exchange
 * @ep: The exchange to be reset
 *
 * Note: May sleep अगर invoked from outside a response handler.
 */
अटल व्योम fc_exch_reset(काष्ठा fc_exch *ep)
अणु
	काष्ठा fc_seq *sp;
	पूर्णांक rc = 1;

	spin_lock_bh(&ep->ex_lock);
	ep->state |= FC_EX_RST_CLEANUP;
	fc_exch_समयr_cancel(ep);
	अगर (ep->esb_stat & ESB_ST_REC_QUAL)
		atomic_dec(&ep->ex_refcnt);	/* drop hold क्रम rec_qual */
	ep->esb_stat &= ~ESB_ST_REC_QUAL;
	sp = &ep->seq;
	rc = fc_exch_करोne_locked(ep);
	spin_unlock_bh(&ep->ex_lock);

	fc_exch_hold(ep);

	अगर (!rc) अणु
		fc_exch_delete(ep);
	पूर्ण अन्यथा अणु
		FC_EXCH_DBG(ep, "ep is completed already,"
				"hence skip calling the resp\n");
		जाओ skip_resp;
	पूर्ण

	fc_invoke_resp(ep, sp, ERR_PTR(-FC_EX_CLOSED));
skip_resp:
	fc_seq_set_resp(sp, शून्य, ep->arg);
	fc_exch_release(ep);
पूर्ण

/**
 * fc_exch_pool_reset() - Reset a per cpu exchange pool
 * @lport: The local port that the exchange pool is on
 * @pool:  The exchange pool to be reset
 * @sid:   The source ID
 * @did:   The destination ID
 *
 * Resets a per cpu exches pool, releasing all of its sequences
 * and exchanges. If sid is non-zero then reset only exchanges
 * we sourced from the local port's FID. If did is non-zero then
 * only reset exchanges destined क्रम the local port's FID.
 */
अटल व्योम fc_exch_pool_reset(काष्ठा fc_lport *lport,
			       काष्ठा fc_exch_pool *pool,
			       u32 sid, u32 did)
अणु
	काष्ठा fc_exch *ep;
	काष्ठा fc_exch *next;

	spin_lock_bh(&pool->lock);
restart:
	list_क्रम_each_entry_safe(ep, next, &pool->ex_list, ex_list) अणु
		अगर ((lport == ep->lp) &&
		    (sid == 0 || sid == ep->sid) &&
		    (did == 0 || did == ep->did)) अणु
			fc_exch_hold(ep);
			spin_unlock_bh(&pool->lock);

			fc_exch_reset(ep);

			fc_exch_release(ep);
			spin_lock_bh(&pool->lock);

			/*
			 * must restart loop inहाल जबतक lock
			 * was करोwn multiple eps were released.
			 */
			जाओ restart;
		पूर्ण
	पूर्ण
	pool->next_index = 0;
	pool->left = FC_XID_UNKNOWN;
	pool->right = FC_XID_UNKNOWN;
	spin_unlock_bh(&pool->lock);
पूर्ण

/**
 * fc_exch_mgr_reset() - Reset all EMs of a local port
 * @lport: The local port whose EMs are to be reset
 * @sid:   The source ID
 * @did:   The destination ID
 *
 * Reset all EMs associated with a given local port. Release all
 * sequences and exchanges. If sid is non-zero then reset only the
 * exchanges sent from the local port's FID. If did is non-zero then
 * reset only exchanges destined क्रम the local port's FID.
 */
व्योम fc_exch_mgr_reset(काष्ठा fc_lport *lport, u32 sid, u32 did)
अणु
	काष्ठा fc_exch_mgr_anchor *ema;
	अचिन्हित पूर्णांक cpu;

	list_क्रम_each_entry(ema, &lport->ema_list, ema_list) अणु
		क्रम_each_possible_cpu(cpu)
			fc_exch_pool_reset(lport,
					   per_cpu_ptr(ema->mp->pool, cpu),
					   sid, did);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_exch_mgr_reset);

/**
 * fc_exch_lookup() - find an exchange
 * @lport: The local port
 * @xid: The exchange ID
 *
 * Returns exchange poपूर्णांकer with hold क्रम caller, or शून्य अगर not found.
 */
अटल काष्ठा fc_exch *fc_exch_lookup(काष्ठा fc_lport *lport, u32 xid)
अणु
	काष्ठा fc_exch_mgr_anchor *ema;

	list_क्रम_each_entry(ema, &lport->ema_list, ema_list)
		अगर (ema->mp->min_xid <= xid && xid <= ema->mp->max_xid)
			वापस fc_exch_find(ema->mp, xid);
	वापस शून्य;
पूर्ण

/**
 * fc_exch_els_rec() - Handler क्रम ELS REC (Read Exchange Concise) requests
 * @rfp: The REC frame, not मुक्तd here.
 *
 * Note that the requesting port may be dअगरferent than the S_ID in the request.
 */
अटल व्योम fc_exch_els_rec(काष्ठा fc_frame *rfp)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_frame *fp;
	काष्ठा fc_exch *ep;
	काष्ठा fc_els_rec *rp;
	काष्ठा fc_els_rec_acc *acc;
	क्रमागत fc_els_rjt_reason reason = ELS_RJT_LOGIC;
	क्रमागत fc_els_rjt_explan explan;
	u32 sid;
	u16 xid, rxid, oxid;

	lport = fr_dev(rfp);
	rp = fc_frame_payload_get(rfp, माप(*rp));
	explan = ELS_EXPL_INV_LEN;
	अगर (!rp)
		जाओ reject;
	sid = ntoh24(rp->rec_s_id);
	rxid = ntohs(rp->rec_rx_id);
	oxid = ntohs(rp->rec_ox_id);

	explan = ELS_EXPL_OXID_RXID;
	अगर (sid == fc_host_port_id(lport->host))
		xid = oxid;
	अन्यथा
		xid = rxid;
	अगर (xid == FC_XID_UNKNOWN) अणु
		FC_LPORT_DBG(lport,
			     "REC request from %x: invalid rxid %x oxid %x\n",
			     sid, rxid, oxid);
		जाओ reject;
	पूर्ण
	ep = fc_exch_lookup(lport, xid);
	अगर (!ep) अणु
		FC_LPORT_DBG(lport,
			     "REC request from %x: rxid %x oxid %x not found\n",
			     sid, rxid, oxid);
		जाओ reject;
	पूर्ण
	FC_EXCH_DBG(ep, "REC request from %x: rxid %x oxid %x\n",
		    sid, rxid, oxid);
	अगर (ep->oid != sid || oxid != ep->oxid)
		जाओ rel;
	अगर (rxid != FC_XID_UNKNOWN && rxid != ep->rxid)
		जाओ rel;
	fp = fc_frame_alloc(lport, माप(*acc));
	अगर (!fp) अणु
		FC_EXCH_DBG(ep, "Drop REC request, out of memory\n");
		जाओ out;
	पूर्ण

	acc = fc_frame_payload_get(fp, माप(*acc));
	स_रखो(acc, 0, माप(*acc));
	acc->reca_cmd = ELS_LS_ACC;
	acc->reca_ox_id = rp->rec_ox_id;
	स_नकल(acc->reca_ofid, rp->rec_s_id, 3);
	acc->reca_rx_id = htons(ep->rxid);
	अगर (ep->sid == ep->oid)
		hton24(acc->reca_rfid, ep->did);
	अन्यथा
		hton24(acc->reca_rfid, ep->sid);
	acc->reca_fc4value = htonl(ep->seq.rec_data);
	acc->reca_e_stat = htonl(ep->esb_stat & (ESB_ST_RESP |
						 ESB_ST_SEQ_INIT |
						 ESB_ST_COMPLETE));
	fc_fill_reply_hdr(fp, rfp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
out:
	fc_exch_release(ep);
	वापस;

rel:
	fc_exch_release(ep);
reject:
	fc_seq_ls_rjt(rfp, reason, explan);
पूर्ण

/**
 * fc_exch_rrq_resp() - Handler क्रम RRQ responses
 * @sp:	 The sequence that the RRQ is on
 * @fp:	 The RRQ frame
 * @arg: The exchange that the RRQ is on
 *
 * TODO: fix error handler.
 */
अटल व्योम fc_exch_rrq_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fc_exch *पातed_ep = arg;
	अचिन्हित पूर्णांक op;

	अगर (IS_ERR(fp)) अणु
		पूर्णांक err = PTR_ERR(fp);

		अगर (err == -FC_EX_CLOSED || err == -FC_EX_TIMEOUT)
			जाओ cleanup;
		FC_EXCH_DBG(पातed_ep, "Cannot process RRQ, "
			    "frame error %d\n", err);
		वापस;
	पूर्ण

	op = fc_frame_payload_op(fp);
	fc_frame_मुक्त(fp);

	चयन (op) अणु
	हाल ELS_LS_RJT:
		FC_EXCH_DBG(पातed_ep, "LS_RJT for RRQ\n");
		fallthrough;
	हाल ELS_LS_ACC:
		जाओ cleanup;
	शेष:
		FC_EXCH_DBG(पातed_ep, "unexpected response op %x for RRQ\n",
			    op);
		वापस;
	पूर्ण

cleanup:
	fc_exch_करोne(&पातed_ep->seq);
	/* drop hold क्रम rec qual */
	fc_exch_release(पातed_ep);
पूर्ण


/**
 * fc_exch_seq_send() - Send a frame using a new exchange and sequence
 * @lport:	The local port to send the frame on
 * @fp:		The frame to be sent
 * @resp:	The response handler क्रम this request
 * @deकाष्ठाor: The deकाष्ठाor क्रम the exchange
 * @arg:	The argument to be passed to the response handler
 * @समयr_msec: The समयout period क्रम the exchange
 *
 * The exchange response handler is set in this routine to resp()
 * function poपूर्णांकer. It can be called in two scenarios: अगर a समयout
 * occurs or अगर a response frame is received क्रम the exchange. The
 * fc_frame poपूर्णांकer in response handler will also indicate समयout
 * as error using IS_ERR related macros.
 *
 * The exchange deकाष्ठाor handler is also set in this routine.
 * The deकाष्ठाor handler is invoked by EM layer when exchange
 * is about to मुक्त, this can be used by caller to मुक्त its
 * resources aदीर्घ with exchange मुक्त.
 *
 * The arg is passed back to resp and deकाष्ठाor handler.
 *
 * The समयout value (in msec) क्रम an exchange is set अगर non zero
 * समयr_msec argument is specअगरied. The समयr is canceled when
 * it fires or when the exchange is करोne. The exchange समयout handler
 * is रेजिस्टरed by EM layer.
 *
 * The frame poपूर्णांकer with some of the header's fields must be
 * filled beक्रमe calling this routine, those fields are:
 *
 * - routing control
 * - FC port did
 * - FC port sid
 * - FC header type
 * - frame control
 * - parameter or relative offset
 */
काष्ठा fc_seq *fc_exch_seq_send(काष्ठा fc_lport *lport,
				काष्ठा fc_frame *fp,
				व्योम (*resp)(काष्ठा fc_seq *,
					     काष्ठा fc_frame *fp,
					     व्योम *arg),
				व्योम (*deकाष्ठाor)(काष्ठा fc_seq *, व्योम *),
				व्योम *arg, u32 समयr_msec)
अणु
	काष्ठा fc_exch *ep;
	काष्ठा fc_seq *sp = शून्य;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_fcp_pkt *fsp = शून्य;
	पूर्णांक rc = 1;

	ep = fc_exch_alloc(lport, fp);
	अगर (!ep) अणु
		fc_frame_मुक्त(fp);
		वापस शून्य;
	पूर्ण
	ep->esb_stat |= ESB_ST_SEQ_INIT;
	fh = fc_frame_header_get(fp);
	fc_exch_set_addr(ep, ntoh24(fh->fh_s_id), ntoh24(fh->fh_d_id));
	ep->resp = resp;
	ep->deकाष्ठाor = deकाष्ठाor;
	ep->arg = arg;
	ep->r_a_tov = lport->r_a_tov;
	ep->lp = lport;
	sp = &ep->seq;

	ep->fh_type = fh->fh_type; /* save क्रम possbile समयout handling */
	ep->f_ctl = ntoh24(fh->fh_f_ctl);
	fc_exch_setup_hdr(ep, fp, ep->f_ctl);
	sp->cnt++;

	अगर (ep->xid <= lport->lro_xid && fh->fh_r_ctl == FC_RCTL_DD_UNSOL_CMD) अणु
		fsp = fr_fsp(fp);
		fc_fcp_ddp_setup(fr_fsp(fp), ep->xid);
	पूर्ण

	अगर (unlikely(lport->tt.frame_send(lport, fp)))
		जाओ err;

	अगर (समयr_msec)
		fc_exch_समयr_set_locked(ep, समयr_msec);
	ep->f_ctl &= ~FC_FC_FIRST_SEQ;	/* not first seq */

	अगर (ep->f_ctl & FC_FC_SEQ_INIT)
		ep->esb_stat &= ~ESB_ST_SEQ_INIT;
	spin_unlock_bh(&ep->ex_lock);
	वापस sp;
err:
	अगर (fsp)
		fc_fcp_ddp_करोne(fsp);
	rc = fc_exch_करोne_locked(ep);
	spin_unlock_bh(&ep->ex_lock);
	अगर (!rc)
		fc_exch_delete(ep);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(fc_exch_seq_send);

/**
 * fc_exch_rrq() - Send an ELS RRQ (Reinstate Recovery Qualअगरier) command
 * @ep: The exchange to send the RRQ on
 *
 * This tells the remote port to stop blocking the use of
 * the exchange and the seq_cnt range.
 */
अटल व्योम fc_exch_rrq(काष्ठा fc_exch *ep)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_els_rrq *rrq;
	काष्ठा fc_frame *fp;
	u32 did;

	lport = ep->lp;

	fp = fc_frame_alloc(lport, माप(*rrq));
	अगर (!fp)
		जाओ retry;

	rrq = fc_frame_payload_get(fp, माप(*rrq));
	स_रखो(rrq, 0, माप(*rrq));
	rrq->rrq_cmd = ELS_RRQ;
	hton24(rrq->rrq_s_id, ep->sid);
	rrq->rrq_ox_id = htons(ep->oxid);
	rrq->rrq_rx_id = htons(ep->rxid);

	did = ep->did;
	अगर (ep->esb_stat & ESB_ST_RESP)
		did = ep->sid;

	fc_fill_fc_hdr(fp, FC_RCTL_ELS_REQ, did,
		       lport->port_id, FC_TYPE_ELS,
		       FC_FC_FIRST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	अगर (fc_exch_seq_send(lport, fp, fc_exch_rrq_resp, शून्य, ep,
			     lport->e_d_tov))
		वापस;

retry:
	FC_EXCH_DBG(ep, "exch: RRQ send failed\n");
	spin_lock_bh(&ep->ex_lock);
	अगर (ep->state & (FC_EX_RST_CLEANUP | FC_EX_DONE)) अणु
		spin_unlock_bh(&ep->ex_lock);
		/* drop hold क्रम rec qual */
		fc_exch_release(ep);
		वापस;
	पूर्ण
	ep->esb_stat |= ESB_ST_REC_QUAL;
	fc_exch_समयr_set_locked(ep, ep->r_a_tov);
	spin_unlock_bh(&ep->ex_lock);
पूर्ण

/**
 * fc_exch_els_rrq() - Handler क्रम ELS RRQ (Reset Recovery Qualअगरier) requests
 * @fp: The RRQ frame, not मुक्तd here.
 */
अटल व्योम fc_exch_els_rrq(काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_exch *ep = शून्य;	/* request or subject exchange */
	काष्ठा fc_els_rrq *rp;
	u32 sid;
	u16 xid;
	क्रमागत fc_els_rjt_explan explan;

	lport = fr_dev(fp);
	rp = fc_frame_payload_get(fp, माप(*rp));
	explan = ELS_EXPL_INV_LEN;
	अगर (!rp)
		जाओ reject;

	/*
	 * lookup subject exchange.
	 */
	sid = ntoh24(rp->rrq_s_id);		/* subject source */
	xid = fc_host_port_id(lport->host) == sid ?
			ntohs(rp->rrq_ox_id) : ntohs(rp->rrq_rx_id);
	ep = fc_exch_lookup(lport, xid);
	explan = ELS_EXPL_OXID_RXID;
	अगर (!ep)
		जाओ reject;
	spin_lock_bh(&ep->ex_lock);
	FC_EXCH_DBG(ep, "RRQ request from %x: xid %x rxid %x oxid %x\n",
		    sid, xid, ntohs(rp->rrq_rx_id), ntohs(rp->rrq_ox_id));
	अगर (ep->oxid != ntohs(rp->rrq_ox_id))
		जाओ unlock_reject;
	अगर (ep->rxid != ntohs(rp->rrq_rx_id) &&
	    ep->rxid != FC_XID_UNKNOWN)
		जाओ unlock_reject;
	explan = ELS_EXPL_SID;
	अगर (ep->sid != sid)
		जाओ unlock_reject;

	/*
	 * Clear Recovery Qualअगरier state, and cancel समयr अगर complete.
	 */
	अगर (ep->esb_stat & ESB_ST_REC_QUAL) अणु
		ep->esb_stat &= ~ESB_ST_REC_QUAL;
		atomic_dec(&ep->ex_refcnt);	/* drop hold क्रम rec qual */
	पूर्ण
	अगर (ep->esb_stat & ESB_ST_COMPLETE)
		fc_exch_समयr_cancel(ep);

	spin_unlock_bh(&ep->ex_lock);

	/*
	 * Send LS_ACC.
	 */
	fc_seq_ls_acc(fp);
	जाओ out;

unlock_reject:
	spin_unlock_bh(&ep->ex_lock);
reject:
	fc_seq_ls_rjt(fp, ELS_RJT_LOGIC, explan);
out:
	अगर (ep)
		fc_exch_release(ep);	/* drop hold from fc_exch_find */
पूर्ण

/**
 * fc_exch_update_stats() - update exches stats to lport
 * @lport: The local port to update exchange manager stats
 */
व्योम fc_exch_update_stats(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_host_statistics *st;
	काष्ठा fc_exch_mgr_anchor *ema;
	काष्ठा fc_exch_mgr *mp;

	st = &lport->host_stats;

	list_क्रम_each_entry(ema, &lport->ema_list, ema_list) अणु
		mp = ema->mp;
		st->fc_no_मुक्त_exch += atomic_पढ़ो(&mp->stats.no_मुक्त_exch);
		st->fc_no_मुक्त_exch_xid +=
				atomic_पढ़ो(&mp->stats.no_मुक्त_exch_xid);
		st->fc_xid_not_found += atomic_पढ़ो(&mp->stats.xid_not_found);
		st->fc_xid_busy += atomic_पढ़ो(&mp->stats.xid_busy);
		st->fc_seq_not_found += atomic_पढ़ो(&mp->stats.seq_not_found);
		st->fc_non_bls_resp += atomic_पढ़ो(&mp->stats.non_bls_resp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_exch_update_stats);

/**
 * fc_exch_mgr_add() - Add an exchange manager to a local port's list of EMs
 * @lport: The local port to add the exchange manager to
 * @mp:	   The exchange manager to be added to the local port
 * @match: The match routine that indicates when this EM should be used
 */
काष्ठा fc_exch_mgr_anchor *fc_exch_mgr_add(काष्ठा fc_lport *lport,
					   काष्ठा fc_exch_mgr *mp,
					   bool (*match)(काष्ठा fc_frame *))
अणु
	काष्ठा fc_exch_mgr_anchor *ema;

	ema = kदो_स्मृति(माप(*ema), GFP_ATOMIC);
	अगर (!ema)
		वापस ema;

	ema->mp = mp;
	ema->match = match;
	/* add EM anchor to EM anchors list */
	list_add_tail(&ema->ema_list, &lport->ema_list);
	kref_get(&mp->kref);
	वापस ema;
पूर्ण
EXPORT_SYMBOL(fc_exch_mgr_add);

/**
 * fc_exch_mgr_destroy() - Destroy an exchange manager
 * @kref: The reference to the EM to be destroyed
 */
अटल व्योम fc_exch_mgr_destroy(काष्ठा kref *kref)
अणु
	काष्ठा fc_exch_mgr *mp = container_of(kref, काष्ठा fc_exch_mgr, kref);

	mempool_destroy(mp->ep_pool);
	मुक्त_percpu(mp->pool);
	kमुक्त(mp);
पूर्ण

/**
 * fc_exch_mgr_del() - Delete an EM from a local port's list
 * @ema: The exchange manager anchor identअगरying the EM to be deleted
 */
व्योम fc_exch_mgr_del(काष्ठा fc_exch_mgr_anchor *ema)
अणु
	/* हटाओ EM anchor from EM anchors list */
	list_del(&ema->ema_list);
	kref_put(&ema->mp->kref, fc_exch_mgr_destroy);
	kमुक्त(ema);
पूर्ण
EXPORT_SYMBOL(fc_exch_mgr_del);

/**
 * fc_exch_mgr_list_clone() - Share all exchange manager objects
 * @src: Source lport to clone exchange managers from
 * @dst: New lport that takes references to all the exchange managers
 */
पूर्णांक fc_exch_mgr_list_clone(काष्ठा fc_lport *src, काष्ठा fc_lport *dst)
अणु
	काष्ठा fc_exch_mgr_anchor *ema, *पंचांगp;

	list_क्रम_each_entry(ema, &src->ema_list, ema_list) अणु
		अगर (!fc_exch_mgr_add(dst, ema->mp, ema->match))
			जाओ err;
	पूर्ण
	वापस 0;
err:
	list_क्रम_each_entry_safe(ema, पंचांगp, &dst->ema_list, ema_list)
		fc_exch_mgr_del(ema);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(fc_exch_mgr_list_clone);

/**
 * fc_exch_mgr_alloc() - Allocate an exchange manager
 * @lport:   The local port that the new EM will be associated with
 * @class:   The शेष FC class क्रम new exchanges
 * @min_xid: The minimum XID क्रम exchanges from the new EM
 * @max_xid: The maximum XID क्रम exchanges from the new EM
 * @match:   The match routine क्रम the new EM
 */
काष्ठा fc_exch_mgr *fc_exch_mgr_alloc(काष्ठा fc_lport *lport,
				      क्रमागत fc_class class,
				      u16 min_xid, u16 max_xid,
				      bool (*match)(काष्ठा fc_frame *))
अणु
	काष्ठा fc_exch_mgr *mp;
	u16 pool_exch_range;
	माप_प्रकार pool_size;
	अचिन्हित पूर्णांक cpu;
	काष्ठा fc_exch_pool *pool;

	अगर (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN ||
	    (min_xid & fc_cpu_mask) != 0) अणु
		FC_LPORT_DBG(lport, "Invalid min_xid 0x:%x and max_xid 0x:%x\n",
			     min_xid, max_xid);
		वापस शून्य;
	पूर्ण

	/*
	 * allocate memory क्रम EM
	 */
	mp = kzalloc(माप(काष्ठा fc_exch_mgr), GFP_ATOMIC);
	अगर (!mp)
		वापस शून्य;

	mp->class = class;
	mp->lport = lport;
	/* adjust em exch xid range क्रम offload */
	mp->min_xid = min_xid;

       /* reduce range so per cpu pool fits पूर्णांकo PCPU_MIN_UNIT_SIZE pool */
	pool_exch_range = (PCPU_MIN_UNIT_SIZE - माप(*pool)) /
		माप(काष्ठा fc_exch *);
	अगर ((max_xid - min_xid + 1) / (fc_cpu_mask + 1) > pool_exch_range) अणु
		mp->max_xid = pool_exch_range * (fc_cpu_mask + 1) +
			min_xid - 1;
	पूर्ण अन्यथा अणु
		mp->max_xid = max_xid;
		pool_exch_range = (mp->max_xid - mp->min_xid + 1) /
			(fc_cpu_mask + 1);
	पूर्ण

	mp->ep_pool = mempool_create_slab_pool(2, fc_em_cachep);
	अगर (!mp->ep_pool)
		जाओ मुक्त_mp;

	/*
	 * Setup per cpu exch pool with entire exchange id range equally
	 * भागided across all cpus. The exch poपूर्णांकers array memory is
	 * allocated क्रम exch range per pool.
	 */
	mp->pool_max_index = pool_exch_range - 1;

	/*
	 * Allocate and initialize per cpu exch pool
	 */
	pool_size = माप(*pool) + pool_exch_range * माप(काष्ठा fc_exch *);
	mp->pool = __alloc_percpu(pool_size, __alignof__(काष्ठा fc_exch_pool));
	अगर (!mp->pool)
		जाओ मुक्त_mempool;
	क्रम_each_possible_cpu(cpu) अणु
		pool = per_cpu_ptr(mp->pool, cpu);
		pool->next_index = 0;
		pool->left = FC_XID_UNKNOWN;
		pool->right = FC_XID_UNKNOWN;
		spin_lock_init(&pool->lock);
		INIT_LIST_HEAD(&pool->ex_list);
	पूर्ण

	kref_init(&mp->kref);
	अगर (!fc_exch_mgr_add(lport, mp, match)) अणु
		मुक्त_percpu(mp->pool);
		जाओ मुक्त_mempool;
	पूर्ण

	/*
	 * Above kref_init() sets mp->kref to 1 and then
	 * call to fc_exch_mgr_add incremented mp->kref again,
	 * so adjust that extra increment.
	 */
	kref_put(&mp->kref, fc_exch_mgr_destroy);
	वापस mp;

मुक्त_mempool:
	mempool_destroy(mp->ep_pool);
मुक्त_mp:
	kमुक्त(mp);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(fc_exch_mgr_alloc);

/**
 * fc_exch_mgr_मुक्त() - Free all exchange managers on a local port
 * @lport: The local port whose EMs are to be मुक्तd
 */
व्योम fc_exch_mgr_मुक्त(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_exch_mgr_anchor *ema, *next;

	flush_workqueue(fc_exch_workqueue);
	list_क्रम_each_entry_safe(ema, next, &lport->ema_list, ema_list)
		fc_exch_mgr_del(ema);
पूर्ण
EXPORT_SYMBOL(fc_exch_mgr_मुक्त);

/**
 * fc_find_ema() - Lookup and वापस appropriate Exchange Manager Anchor depending
 * upon 'xid'.
 * @f_ctl: f_ctl
 * @lport: The local port the frame was received on
 * @fh: The received frame header
 */
अटल काष्ठा fc_exch_mgr_anchor *fc_find_ema(u32 f_ctl,
					      काष्ठा fc_lport *lport,
					      काष्ठा fc_frame_header *fh)
अणु
	काष्ठा fc_exch_mgr_anchor *ema;
	u16 xid;

	अगर (f_ctl & FC_FC_EX_CTX)
		xid = ntohs(fh->fh_ox_id);
	अन्यथा अणु
		xid = ntohs(fh->fh_rx_id);
		अगर (xid == FC_XID_UNKNOWN)
			वापस list_entry(lport->ema_list.prev,
					  typeof(*ema), ema_list);
	पूर्ण

	list_क्रम_each_entry(ema, &lport->ema_list, ema_list) अणु
		अगर ((xid >= ema->mp->min_xid) &&
		    (xid <= ema->mp->max_xid))
			वापस ema;
	पूर्ण
	वापस शून्य;
पूर्ण
/**
 * fc_exch_recv() - Handler क्रम received frames
 * @lport: The local port the frame was received on
 * @fp:	The received frame
 */
व्योम fc_exch_recv(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fc_exch_mgr_anchor *ema;
	u32 f_ctl;

	/* lport lock ? */
	अगर (!lport || lport->state == LPORT_ST_DISABLED) अणु
		FC_LIBFC_DBG("Receiving frames for an lport that "
			     "has not been initialized correctly\n");
		fc_frame_मुक्त(fp);
		वापस;
	पूर्ण

	f_ctl = ntoh24(fh->fh_f_ctl);
	ema = fc_find_ema(f_ctl, lport, fh);
	अगर (!ema) अणु
		FC_LPORT_DBG(lport, "Unable to find Exchange Manager Anchor,"
				    "fc_ctl <0x%x>, xid <0x%x>\n",
				     f_ctl,
				     (f_ctl & FC_FC_EX_CTX) ?
				     ntohs(fh->fh_ox_id) :
				     ntohs(fh->fh_rx_id));
		fc_frame_मुक्त(fp);
		वापस;
	पूर्ण

	/*
	 * If frame is marked invalid, just drop it.
	 */
	चयन (fr_eof(fp)) अणु
	हाल FC_खातापूर्ण_T:
		अगर (f_ctl & FC_FC_END_SEQ)
			skb_trim(fp_skb(fp), fr_len(fp) - FC_FC_FILL(f_ctl));
		fallthrough;
	हाल FC_खातापूर्ण_N:
		अगर (fh->fh_type == FC_TYPE_BLS)
			fc_exch_recv_bls(ema->mp, fp);
		अन्यथा अगर ((f_ctl & (FC_FC_EX_CTX | FC_FC_SEQ_CTX)) ==
			 FC_FC_EX_CTX)
			fc_exch_recv_seq_resp(ema->mp, fp);
		अन्यथा अगर (f_ctl & FC_FC_SEQ_CTX)
			fc_exch_recv_resp(ema->mp, fp);
		अन्यथा	/* no EX_CTX and no SEQ_CTX */
			fc_exch_recv_req(lport, ema->mp, fp);
		अवरोध;
	शेष:
		FC_LPORT_DBG(lport, "dropping invalid frame (eof %x)",
			     fr_eof(fp));
		fc_frame_मुक्त(fp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_exch_recv);

/**
 * fc_exch_init() - Initialize the exchange layer क्रम a local port
 * @lport: The local port to initialize the exchange layer क्रम
 */
पूर्णांक fc_exch_init(काष्ठा fc_lport *lport)
अणु
	अगर (!lport->tt.exch_mgr_reset)
		lport->tt.exch_mgr_reset = fc_exch_mgr_reset;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_exch_init);

/**
 * fc_setup_exch_mgr() - Setup an exchange manager
 */
पूर्णांक fc_setup_exch_mgr(व्योम)
अणु
	fc_em_cachep = kmem_cache_create("libfc_em", माप(काष्ठा fc_exch),
					 0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!fc_em_cachep)
		वापस -ENOMEM;

	/*
	 * Initialize fc_cpu_mask and fc_cpu_order. The
	 * fc_cpu_mask is set क्रम nr_cpu_ids rounded up
	 * to order of 2's * घातer and order is stored
	 * in fc_cpu_order as this is later required in
	 * mapping between an exch id and exch array index
	 * in per cpu exch pool.
	 *
	 * This round up is required to align fc_cpu_mask
	 * to exchange id's lower bits such that all incoming
	 * frames of an exchange माला_लो delivered to the same
	 * cpu on which exchange originated by simple bitwise
	 * AND operation between fc_cpu_mask and exchange id.
	 */
	fc_cpu_order = ilog2(roundup_घात_of_two(nr_cpu_ids));
	fc_cpu_mask = (1 << fc_cpu_order) - 1;

	fc_exch_workqueue = create_singlethपढ़ो_workqueue("fc_exch_workqueue");
	अगर (!fc_exch_workqueue)
		जाओ err;
	वापस 0;
err:
	kmem_cache_destroy(fc_em_cachep);
	वापस -ENOMEM;
पूर्ण

/**
 * fc_destroy_exch_mgr() - Destroy an exchange manager
 */
व्योम fc_destroy_exch_mgr(व्योम)
अणु
	destroy_workqueue(fc_exch_workqueue);
	kmem_cache_destroy(fc_em_cachep);
पूर्ण
