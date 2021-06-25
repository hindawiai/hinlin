<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Cisco Systems, Inc.
 *
 * Portions based on tcm_loop_fabric_scsi.c and libfc/fc_fcp.c
 *
 * Copyright (c) 2007 Intel Corporation. All rights reserved.
 * Copyright (c) 2008 Red Hat, Inc.  All rights reserved.
 * Copyright (c) 2008 Mike Christie
 * Copyright (c) 2009 Rising Tide, Inc.
 * Copyright (c) 2009 Linux-iSCSI.org
 * Copyright (c) 2009 Nicholas A. Bellinger <nab@linux-iscsi.org>
 */

/* XXX TBD some includes may be extraneous */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/utsname.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/hash.h>
#समावेश <linux/ratelimit.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/libfc.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश "tcm_fc.h"

/*
 * Deliver पढ़ो data back to initiator.
 * XXX TBD handle resource problems later.
 */
पूर्णांक ft_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ft_cmd *cmd = container_of(se_cmd, काष्ठा ft_cmd, se_cmd);
	काष्ठा fc_frame *fp = शून्य;
	काष्ठा fc_exch *ep;
	काष्ठा fc_lport *lport;
	काष्ठा scatterlist *sg = शून्य;
	माप_प्रकार reमुख्यing;
	u32 f_ctl = FC_FC_EX_CTX | FC_FC_REL_OFF;
	u32 mem_off = 0;
	u32 fh_off = 0;
	u32 frame_off = 0;
	माप_प्रकार frame_len = 0;
	माप_प्रकार mem_len = 0;
	माप_प्रकार tlen;
	माप_प्रकार off_in_page;
	काष्ठा page *page = शून्य;
	पूर्णांक use_sg;
	पूर्णांक error;
	व्योम *page_addr;
	व्योम *from;
	व्योम *to = शून्य;

	अगर (cmd->पातed)
		वापस 0;

	अगर (se_cmd->scsi_status == SAM_STAT_TASK_SET_FULL)
		जाओ queue_status;

	ep = fc_seq_exch(cmd->seq);
	lport = ep->lp;
	cmd->seq = fc_seq_start_next(cmd->seq);

	reमुख्यing = se_cmd->data_length;

	/*
	 * Setup to use first mem list entry, unless no data.
	 */
	BUG_ON(reमुख्यing && !se_cmd->t_data_sg);
	अगर (reमुख्यing) अणु
		sg = se_cmd->t_data_sg;
		mem_len = sg->length;
		mem_off = sg->offset;
		page = sg_page(sg);
	पूर्ण

	/* no scatter/gather in skb क्रम odd word length due to fc_seq_send() */
	use_sg = !(reमुख्यing % 4);

	जबतक (reमुख्यing) अणु
		काष्ठा fc_seq *seq = cmd->seq;

		अगर (!seq) अणु
			pr_debug("%s: Command aborted, xid 0x%x\n",
				 __func__, ep->xid);
			अवरोध;
		पूर्ण
		अगर (!mem_len) अणु
			sg = sg_next(sg);
			mem_len = min((माप_प्रकार)sg->length, reमुख्यing);
			mem_off = sg->offset;
			page = sg_page(sg);
		पूर्ण
		अगर (!frame_len) अणु
			/*
			 * If lport's has capability of Large Send Offload LSO)
			 * , then allow 'frame_len' to be as big as 'lso_max'
			 * अगर indicated transfer length is >= lport->lso_max
			 */
			frame_len = (lport->seq_offload) ? lport->lso_max :
							  cmd->sess->max_frame;
			frame_len = min(frame_len, reमुख्यing);
			fp = fc_frame_alloc(lport, use_sg ? 0 : frame_len);
			अगर (!fp)
				वापस -ENOMEM;
			to = fc_frame_payload_get(fp, 0);
			fh_off = frame_off;
			frame_off += frame_len;
			/*
			 * Setup the frame's max payload which is used by base
			 * driver to indicate HW about max frame size, so that
			 * HW can करो fragmentation appropriately based on
			 * "gso_max_size" of underline netdev.
			 */
			fr_max_payload(fp) = cmd->sess->max_frame;
		पूर्ण
		tlen = min(mem_len, frame_len);

		अगर (use_sg) अणु
			off_in_page = mem_off;
			BUG_ON(!page);
			get_page(page);
			skb_fill_page_desc(fp_skb(fp),
					   skb_shinfo(fp_skb(fp))->nr_frags,
					   page, off_in_page, tlen);
			fr_len(fp) += tlen;
			fp_skb(fp)->data_len += tlen;
			fp_skb(fp)->truesize += page_size(page);
		पूर्ण अन्यथा अणु
			BUG_ON(!page);
			from = kmap_atomic(page + (mem_off >> PAGE_SHIFT));
			page_addr = from;
			from += offset_in_page(mem_off);
			tlen = min(tlen, (माप_प्रकार)(PAGE_SIZE -
						offset_in_page(mem_off)));
			स_नकल(to, from, tlen);
			kunmap_atomic(page_addr);
			to += tlen;
		पूर्ण

		mem_off += tlen;
		mem_len -= tlen;
		frame_len -= tlen;
		reमुख्यing -= tlen;

		अगर (frame_len &&
		    (skb_shinfo(fp_skb(fp))->nr_frags < FC_FRAME_SG_LEN))
			जारी;
		अगर (!reमुख्यing)
			f_ctl |= FC_FC_END_SEQ;
		fc_fill_fc_hdr(fp, FC_RCTL_DD_SOL_DATA, ep->did, ep->sid,
			       FC_TYPE_FCP, f_ctl, fh_off);
		error = fc_seq_send(lport, seq, fp);
		अगर (error) अणु
			pr_info_ratelimited("%s: Failed to send frame %p, "
						"xid <0x%x>, remaining %zu, "
						"lso_max <0x%x>\n",
						__func__, fp, ep->xid,
						reमुख्यing, lport->lso_max);
			/*
			 * Go ahead and set TASK_SET_FULL status ignoring the
			 * rest of the DataIN, and immediately attempt to
			 * send the response via ft_queue_status() in order
			 * to notअगरy the initiator that it should reduce it's
			 * per LUN queue_depth.
			 */
			se_cmd->scsi_status = SAM_STAT_TASK_SET_FULL;
			अवरोध;
		पूर्ण
	पूर्ण
queue_status:
	वापस ft_queue_status(se_cmd);
पूर्ण

अटल व्योम ft_execute_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ft_cmd *cmd = container_of(work, काष्ठा ft_cmd, work);

	target_execute_cmd(&cmd->se_cmd);
पूर्ण

/*
 * Receive ग_लिखो data frame.
 */
व्योम ft_recv_ग_लिखो_data(काष्ठा ft_cmd *cmd, काष्ठा fc_frame *fp)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा fc_seq *seq = cmd->seq;
	काष्ठा fc_exch *ep;
	काष्ठा fc_lport *lport;
	काष्ठा fc_frame_header *fh;
	काष्ठा scatterlist *sg = शून्य;
	u32 mem_off = 0;
	u32 rel_off;
	माप_प्रकार frame_len;
	माप_प्रकार mem_len = 0;
	माप_प्रकार tlen;
	काष्ठा page *page = शून्य;
	व्योम *page_addr;
	व्योम *from;
	व्योम *to;
	u32 f_ctl;
	व्योम *buf;

	fh = fc_frame_header_get(fp);
	अगर (!(ntoh24(fh->fh_f_ctl) & FC_FC_REL_OFF))
		जाओ drop;

	f_ctl = ntoh24(fh->fh_f_ctl);
	ep = fc_seq_exch(seq);
	lport = ep->lp;
	अगर (cmd->was_ddp_setup) अणु
		BUG_ON(!lport);
		/*
		 * Since DDP (Large Rx offload) was setup क्रम this request,
		 * payload is expected to be copied directly to user buffers.
		 */
		buf = fc_frame_payload_get(fp, 1);
		अगर (buf)
			pr_err("%s: xid 0x%x, f_ctl 0x%x, cmd->sg %p, "
				"cmd->sg_cnt 0x%x. DDP was setup"
				" hence not expected to receive frame with "
				"payload, Frame will be dropped if"
				"'Sequence Initiative' bit in f_ctl is"
				"not set\n", __func__, ep->xid, f_ctl,
				se_cmd->t_data_sg, se_cmd->t_data_nents);
		/*
		 * Invalidate HW DDP context अगर it was setup क्रम respective
		 * command. Invalidation of HW DDP context is requited in both
		 * situation (success and error).
		 */
		ft_invl_hw_context(cmd);

		/*
		 * If "Sequence Initiative (TSI)" bit set in f_ctl, means last
		 * ग_लिखो data frame is received successfully where payload is
		 * posted directly to user buffer and only the last frame's
		 * header is posted in receive queue.
		 *
		 * If "Sequence Initiative (TSI)" bit is not set, means error
		 * condition w.r.t. DDP, hence drop the packet and let explict
		 * ABORTS from other end of exchange समयr trigger the recovery.
		 */
		अगर (f_ctl & FC_FC_SEQ_INIT)
			जाओ last_frame;
		अन्यथा
			जाओ drop;
	पूर्ण

	rel_off = ntohl(fh->fh_parm_offset);
	frame_len = fr_len(fp);
	अगर (frame_len <= माप(*fh))
		जाओ drop;
	frame_len -= माप(*fh);
	from = fc_frame_payload_get(fp, 0);
	अगर (rel_off >= se_cmd->data_length)
		जाओ drop;
	अगर (frame_len + rel_off > se_cmd->data_length)
		frame_len = se_cmd->data_length - rel_off;

	/*
	 * Setup to use first mem list entry, unless no data.
	 */
	BUG_ON(frame_len && !se_cmd->t_data_sg);
	अगर (frame_len) अणु
		sg = se_cmd->t_data_sg;
		mem_len = sg->length;
		mem_off = sg->offset;
		page = sg_page(sg);
	पूर्ण

	जबतक (frame_len) अणु
		अगर (!mem_len) अणु
			sg = sg_next(sg);
			mem_len = sg->length;
			mem_off = sg->offset;
			page = sg_page(sg);
		पूर्ण
		अगर (rel_off >= mem_len) अणु
			rel_off -= mem_len;
			mem_len = 0;
			जारी;
		पूर्ण
		mem_off += rel_off;
		mem_len -= rel_off;
		rel_off = 0;

		tlen = min(mem_len, frame_len);

		to = kmap_atomic(page + (mem_off >> PAGE_SHIFT));
		page_addr = to;
		to += offset_in_page(mem_off);
		tlen = min(tlen, (माप_प्रकार)(PAGE_SIZE -
					  offset_in_page(mem_off)));
		स_नकल(to, from, tlen);
		kunmap_atomic(page_addr);

		from += tlen;
		frame_len -= tlen;
		mem_off += tlen;
		mem_len -= tlen;
		cmd->ग_लिखो_data_len += tlen;
	पूर्ण
last_frame:
	अगर (cmd->ग_लिखो_data_len == se_cmd->data_length) अणु
		INIT_WORK(&cmd->work, ft_execute_work);
		queue_work(cmd->sess->tport->tpg->workqueue, &cmd->work);
	पूर्ण
drop:
	fc_frame_मुक्त(fp);
पूर्ण

/*
 * Handle and cleanup any HW specअगरic resources अगर
 * received ABORTS, errors, समयouts.
 */
व्योम ft_invl_hw_context(काष्ठा ft_cmd *cmd)
अणु
	काष्ठा fc_seq *seq;
	काष्ठा fc_exch *ep = शून्य;
	काष्ठा fc_lport *lport = शून्य;

	BUG_ON(!cmd);
	seq = cmd->seq;

	/* Cleanup the DDP context in HW अगर DDP was setup */
	अगर (cmd->was_ddp_setup && seq) अणु
		ep = fc_seq_exch(seq);
		अगर (ep) अणु
			lport = ep->lp;
			अगर (lport && (ep->xid <= lport->lro_xid)) अणु
				/*
				 * "ddp_done" trigger invalidation of HW
				 * specअगरic DDP context
				 */
				cmd->ग_लिखो_data_len = lport->tt.ddp_करोne(lport,
								      ep->xid);

				/*
				 * Resetting same variable to indicate HW's
				 * DDP context has been invalidated to aव्योम
				 * re_invalidation of same context (context is
				 * identअगरied using ep->xid)
				 */
				cmd->was_ddp_setup = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
