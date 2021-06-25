<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chelsio Communications, Inc.
 */

#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/unaligned.h>
#समावेश <net/tcp.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश "cxgbit.h"

काष्ठा sge_opaque_hdr अणु
	व्योम *dev;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];
पूर्ण;

अटल स्थिर u8 cxgbit_digest_len[] = अणु0, 4, 4, 8पूर्ण;

#घोषणा TX_HDR_LEN (माप(काष्ठा sge_opaque_hdr) + \
		    माप(काष्ठा fw_ofld_tx_data_wr))

अटल काष्ठा sk_buff *
__cxgbit_alloc_skb(काष्ठा cxgbit_sock *csk, u32 len, bool iso)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u8 submode = 0;
	पूर्णांक errcode;
	अटल स्थिर u32 hdr_len = TX_HDR_LEN + ISCSI_HDR_LEN;

	अगर (len) अणु
		skb = alloc_skb_with_frags(hdr_len, len,
					   0, &errcode,
					   GFP_KERNEL);
		अगर (!skb)
			वापस शून्य;

		skb_reserve(skb, TX_HDR_LEN);
		skb_reset_transport_header(skb);
		__skb_put(skb, ISCSI_HDR_LEN);
		skb->data_len = len;
		skb->len += len;
		submode |= (csk->submode & CXGBIT_SUBMODE_DCRC);

	पूर्ण अन्यथा अणु
		u32 iso_len = iso ? माप(काष्ठा cpl_tx_data_iso) : 0;

		skb = alloc_skb(hdr_len + iso_len, GFP_KERNEL);
		अगर (!skb)
			वापस शून्य;

		skb_reserve(skb, TX_HDR_LEN + iso_len);
		skb_reset_transport_header(skb);
		__skb_put(skb, ISCSI_HDR_LEN);
	पूर्ण

	submode |= (csk->submode & CXGBIT_SUBMODE_HCRC);
	cxgbit_skcb_submode(skb) = submode;
	cxgbit_skcb_tx_extralen(skb) = cxgbit_digest_len[submode];
	cxgbit_skcb_flags(skb) |= SKCBF_TX_NEED_HDR;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *cxgbit_alloc_skb(काष्ठा cxgbit_sock *csk, u32 len)
अणु
	वापस __cxgbit_alloc_skb(csk, len, false);
पूर्ण

/*
 * cxgbit_is_ofld_imm - check whether a packet can be sent as immediate data
 * @skb: the packet
 *
 * Returns true अगर a packet can be sent as an offload WR with immediate
 * data.  We currently use the same limit as क्रम Ethernet packets.
 */
अटल पूर्णांक cxgbit_is_ofld_imm(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक length = skb->len;

	अगर (likely(cxgbit_skcb_flags(skb) & SKCBF_TX_NEED_HDR))
		length += माप(काष्ठा fw_ofld_tx_data_wr);

	अगर (likely(cxgbit_skcb_flags(skb) & SKCBF_TX_ISO))
		length += माप(काष्ठा cpl_tx_data_iso);

	वापस length <= MAX_IMM_OFLD_TX_DATA_WR_LEN;
पूर्ण

/*
 * cxgbit_sgl_len - calculates the size of an SGL of the given capacity
 * @n: the number of SGL entries
 * Calculates the number of flits needed क्रम a scatter/gather list that
 * can hold the given number of entries.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cxgbit_sgl_len(अचिन्हित पूर्णांक n)
अणु
	n--;
	वापस (3 * n) / 2 + (n & 1) + 2;
पूर्ण

/*
 * cxgbit_calc_tx_flits_ofld - calculate # of flits क्रम an offload packet
 * @skb: the packet
 *
 * Returns the number of flits needed क्रम the given offload packet.
 * These packets are alपढ़ोy fully स्थिरructed and no additional headers
 * will be added.
 */
अटल अचिन्हित पूर्णांक cxgbit_calc_tx_flits_ofld(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flits, cnt;

	अगर (cxgbit_is_ofld_imm(skb))
		वापस DIV_ROUND_UP(skb->len, 8);
	flits = skb_transport_offset(skb) / 8;
	cnt = skb_shinfo(skb)->nr_frags;
	अगर (skb_tail_poपूर्णांकer(skb) != skb_transport_header(skb))
		cnt++;
	वापस flits + cxgbit_sgl_len(cnt);
पूर्ण

#घोषणा CXGBIT_ISO_FSLICE 0x1
#घोषणा CXGBIT_ISO_LSLICE 0x2
अटल व्योम
cxgbit_cpl_tx_data_iso(काष्ठा sk_buff *skb, काष्ठा cxgbit_iso_info *iso_info)
अणु
	काष्ठा cpl_tx_data_iso *cpl;
	अचिन्हित पूर्णांक submode = cxgbit_skcb_submode(skb);
	अचिन्हित पूर्णांक fslice = !!(iso_info->flags & CXGBIT_ISO_FSLICE);
	अचिन्हित पूर्णांक lslice = !!(iso_info->flags & CXGBIT_ISO_LSLICE);

	cpl = __skb_push(skb, माप(*cpl));

	cpl->op_to_scsi = htonl(CPL_TX_DATA_ISO_OP_V(CPL_TX_DATA_ISO) |
			CPL_TX_DATA_ISO_FIRST_V(fslice) |
			CPL_TX_DATA_ISO_LAST_V(lslice) |
			CPL_TX_DATA_ISO_CPLHDRLEN_V(0) |
			CPL_TX_DATA_ISO_HDRCRC_V(submode & 1) |
			CPL_TX_DATA_ISO_PLDCRC_V(((submode >> 1) & 1)) |
			CPL_TX_DATA_ISO_IMMEDIATE_V(0) |
			CPL_TX_DATA_ISO_SCSI_V(2));

	cpl->ahs_len = 0;
	cpl->mpdu = htons(DIV_ROUND_UP(iso_info->mpdu, 4));
	cpl->burst_size = htonl(DIV_ROUND_UP(iso_info->burst_len, 4));
	cpl->len = htonl(iso_info->len);
	cpl->reserved2_seglen_offset = htonl(0);
	cpl->datasn_offset = htonl(0);
	cpl->buffer_offset = htonl(0);
	cpl->reserved3 = 0;

	__skb_pull(skb, माप(*cpl));
पूर्ण

अटल व्योम
cxgbit_tx_data_wr(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb, u32 dlen,
		  u32 len, u32 credits, u32 compl)
अणु
	काष्ठा fw_ofld_tx_data_wr *req;
	स्थिर काष्ठा cxgb4_lld_info *lldi = &csk->com.cdev->lldi;
	u32 submode = cxgbit_skcb_submode(skb);
	u32 wr_ulp_mode = 0;
	u32 hdr_size = माप(*req);
	u32 opcode = FW_OFLD_TX_DATA_WR;
	u32 immlen = 0;
	u32 क्रमce = is_t5(lldi->adapter_type) ? TX_FORCE_V(!submode) :
		    T6_TX_FORCE_F;

	अगर (cxgbit_skcb_flags(skb) & SKCBF_TX_ISO) अणु
		opcode = FW_ISCSI_TX_DATA_WR;
		immlen += माप(काष्ठा cpl_tx_data_iso);
		hdr_size += माप(काष्ठा cpl_tx_data_iso);
		submode |= 8;
	पूर्ण

	अगर (cxgbit_is_ofld_imm(skb))
		immlen += dlen;

	req = __skb_push(skb, hdr_size);
	req->op_to_immdlen = cpu_to_be32(FW_WR_OP_V(opcode) |
					FW_WR_COMPL_V(compl) |
					FW_WR_IMMDLEN_V(immlen));
	req->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(csk->tid) |
					FW_WR_LEN16_V(credits));
	req->plen = htonl(len);
	wr_ulp_mode = FW_OFLD_TX_DATA_WR_ULPMODE_V(ULP_MODE_ISCSI) |
				FW_OFLD_TX_DATA_WR_ULPSUBMODE_V(submode);

	req->tunnel_to_proxy = htonl((wr_ulp_mode) | क्रमce |
		 FW_OFLD_TX_DATA_WR_SHOVE_V(skb_peek(&csk->txq) ? 0 : 1));
पूर्ण

अटल व्योम cxgbit_arp_failure_skb_discard(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

व्योम cxgbit_push_tx_frames(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;

	जबतक (csk->wr_cred && ((skb = skb_peek(&csk->txq)) != शून्य)) अणु
		u32 dlen = skb->len;
		u32 len = skb->len;
		u32 credits_needed;
		u32 compl = 0;
		u32 flowclen16 = 0;
		u32 iso_cpl_len = 0;

		अगर (cxgbit_skcb_flags(skb) & SKCBF_TX_ISO)
			iso_cpl_len = माप(काष्ठा cpl_tx_data_iso);

		अगर (cxgbit_is_ofld_imm(skb))
			credits_needed = DIV_ROUND_UP(dlen + iso_cpl_len, 16);
		अन्यथा
			credits_needed = DIV_ROUND_UP((8 *
					cxgbit_calc_tx_flits_ofld(skb)) +
					iso_cpl_len, 16);

		अगर (likely(cxgbit_skcb_flags(skb) & SKCBF_TX_NEED_HDR))
			credits_needed += DIV_ROUND_UP(
				माप(काष्ठा fw_ofld_tx_data_wr), 16);
		/*
		 * Assumes the initial credits is large enough to support
		 * fw_flowc_wr plus largest possible first payload
		 */

		अगर (!test_and_set_bit(CSK_TX_DATA_SENT, &csk->com.flags)) अणु
			flowclen16 = cxgbit_send_tx_flowc_wr(csk);
			csk->wr_cred -= flowclen16;
			csk->wr_una_cred += flowclen16;
		पूर्ण

		अगर (csk->wr_cred < credits_needed) अणु
			pr_debug("csk 0x%p, skb %u/%u, wr %d < %u.\n",
				 csk, skb->len, skb->data_len,
				 credits_needed, csk->wr_cred);
			अवरोध;
		पूर्ण
		__skb_unlink(skb, &csk->txq);
		set_wr_txq(skb, CPL_PRIORITY_DATA, csk->txq_idx);
		skb->csum = (__क्रमce __wsum)(credits_needed + flowclen16);
		csk->wr_cred -= credits_needed;
		csk->wr_una_cred += credits_needed;

		pr_debug("csk 0x%p, skb %u/%u, wr %d, left %u, unack %u.\n",
			 csk, skb->len, skb->data_len, credits_needed,
			 csk->wr_cred, csk->wr_una_cred);

		अगर (likely(cxgbit_skcb_flags(skb) & SKCBF_TX_NEED_HDR)) अणु
			len += cxgbit_skcb_tx_extralen(skb);

			अगर ((csk->wr_una_cred >= (csk->wr_max_cred / 2)) ||
			    (!beक्रमe(csk->ग_लिखो_seq,
				     csk->snd_una + csk->snd_win))) अणु
				compl = 1;
				csk->wr_una_cred = 0;
			पूर्ण

			cxgbit_tx_data_wr(csk, skb, dlen, len, credits_needed,
					  compl);
			csk->snd_nxt += len;

		पूर्ण अन्यथा अगर ((cxgbit_skcb_flags(skb) & SKCBF_TX_FLAG_COMPL) ||
			   (csk->wr_una_cred >= (csk->wr_max_cred / 2))) अणु
			काष्ठा cpl_बंद_con_req *req =
				(काष्ठा cpl_बंद_con_req *)skb->data;
			req->wr.wr_hi |= htonl(FW_WR_COMPL_F);
			csk->wr_una_cred = 0;
		पूर्ण

		cxgbit_sock_enqueue_wr(csk, skb);
		t4_set_arp_err_handler(skb, csk,
				       cxgbit_arp_failure_skb_discard);

		pr_debug("csk 0x%p,%u, skb 0x%p, %u.\n",
			 csk, csk->tid, skb, len);

		cxgbit_l2t_send(csk->com.cdev, skb, csk->l2t);
	पूर्ण
पूर्ण

अटल व्योम cxgbit_unlock_sock(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff_head backlogq;
	काष्ठा sk_buff *skb;
	व्योम (*fn)(काष्ठा cxgbit_sock *, काष्ठा sk_buff *);

	skb_queue_head_init(&backlogq);

	spin_lock_bh(&csk->lock);
	जबतक (skb_queue_len(&csk->backlogq)) अणु
		skb_queue_splice_init(&csk->backlogq, &backlogq);
		spin_unlock_bh(&csk->lock);

		जबतक ((skb = __skb_dequeue(&backlogq))) अणु
			fn = cxgbit_skcb_rx_backlog_fn(skb);
			fn(csk, skb);
		पूर्ण

		spin_lock_bh(&csk->lock);
	पूर्ण

	csk->lock_owner = false;
	spin_unlock_bh(&csk->lock);
पूर्ण

अटल पूर्णांक cxgbit_queue_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;

	spin_lock_bh(&csk->lock);
	csk->lock_owner = true;
	spin_unlock_bh(&csk->lock);

	अगर (unlikely((csk->com.state != CSK_STATE_ESTABLISHED) ||
		     संकेत_pending(current))) अणु
		__kमुक्त_skb(skb);
		__skb_queue_purge(&csk->ppodq);
		ret = -1;
		जाओ unlock;
	पूर्ण

	csk->ग_लिखो_seq += skb->len +
			  cxgbit_skcb_tx_extralen(skb);

	skb_queue_splice_tail_init(&csk->ppodq, &csk->txq);
	__skb_queue_tail(&csk->txq, skb);
	cxgbit_push_tx_frames(csk);

unlock:
	cxgbit_unlock_sock(csk);
	वापस ret;
पूर्ण

अटल पूर्णांक
cxgbit_map_skb(काष्ठा iscsi_cmd *cmd, काष्ठा sk_buff *skb, u32 data_offset,
	       u32 data_length)
अणु
	u32 i = 0, nr_frags = MAX_SKB_FRAGS;
	u32 padding = ((-data_length) & 3);
	काष्ठा scatterlist *sg;
	काष्ठा page *page;
	अचिन्हित पूर्णांक page_off;

	अगर (padding)
		nr_frags--;

	/*
	 * We know each entry in t_data_sg contains a page.
	 */
	sg = &cmd->se_cmd.t_data_sg[data_offset / PAGE_SIZE];
	page_off = (data_offset % PAGE_SIZE);

	जबतक (data_length && (i < nr_frags)) अणु
		u32 cur_len = min_t(u32, data_length, sg->length - page_off);

		page = sg_page(sg);

		get_page(page);
		skb_fill_page_desc(skb, i, page, sg->offset + page_off,
				   cur_len);
		skb->data_len += cur_len;
		skb->len += cur_len;
		skb->truesize += cur_len;

		data_length -= cur_len;
		page_off = 0;
		sg = sg_next(sg);
		i++;
	पूर्ण

	अगर (data_length)
		वापस -1;

	अगर (padding) अणु
		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		अगर (!page)
			वापस -1;
		skb_fill_page_desc(skb, i, page, 0, padding);
		skb->data_len += padding;
		skb->len += padding;
		skb->truesize += padding;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
cxgbit_tx_datain_iso(काष्ठा cxgbit_sock *csk, काष्ठा iscsi_cmd *cmd,
		     काष्ठा iscsi_datain_req *dr)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा sk_buff *skb;
	काष्ठा iscsi_datain datain;
	काष्ठा cxgbit_iso_info iso_info;
	u32 data_length = cmd->se_cmd.data_length;
	u32 mrdsl = conn->conn_ops->MaxRecvDataSegmentLength;
	u32 num_pdu, plen, tx_data = 0;
	bool task_sense = !!(cmd->se_cmd.se_cmd_flags &
		SCF_TRANSPORT_TASK_SENSE);
	bool set_statsn = false;
	पूर्णांक ret = -1;

	जबतक (data_length) अणु
		num_pdu = (data_length + mrdsl - 1) / mrdsl;
		अगर (num_pdu > csk->max_iso_npdu)
			num_pdu = csk->max_iso_npdu;

		plen = num_pdu * mrdsl;
		अगर (plen > data_length)
			plen = data_length;

		skb = __cxgbit_alloc_skb(csk, 0, true);
		अगर (unlikely(!skb))
			वापस -ENOMEM;

		स_रखो(skb->data, 0, ISCSI_HDR_LEN);
		cxgbit_skcb_flags(skb) |= SKCBF_TX_ISO;
		cxgbit_skcb_submode(skb) |= (csk->submode &
				CXGBIT_SUBMODE_DCRC);
		cxgbit_skcb_tx_extralen(skb) = (num_pdu *
				cxgbit_digest_len[cxgbit_skcb_submode(skb)]) +
						((num_pdu - 1) * ISCSI_HDR_LEN);

		स_रखो(&datain, 0, माप(काष्ठा iscsi_datain));
		स_रखो(&iso_info, 0, माप(iso_info));

		अगर (!tx_data)
			iso_info.flags |= CXGBIT_ISO_FSLICE;

		अगर (!(data_length - plen)) अणु
			iso_info.flags |= CXGBIT_ISO_LSLICE;
			अगर (!task_sense) अणु
				datain.flags = ISCSI_FLAG_DATA_STATUS;
				iscsit_increment_maxcmdsn(cmd, conn->sess);
				cmd->stat_sn = conn->stat_sn++;
				set_statsn = true;
			पूर्ण
		पूर्ण

		iso_info.burst_len = num_pdu * mrdsl;
		iso_info.mpdu = mrdsl;
		iso_info.len = ISCSI_HDR_LEN + plen;

		cxgbit_cpl_tx_data_iso(skb, &iso_info);

		datain.offset = tx_data;
		datain.data_sn = cmd->data_sn - 1;

		iscsit_build_datain_pdu(cmd, conn, &datain,
					(काष्ठा iscsi_data_rsp *)skb->data,
					set_statsn);

		ret = cxgbit_map_skb(cmd, skb, tx_data, plen);
		अगर (unlikely(ret)) अणु
			__kमुक्त_skb(skb);
			जाओ out;
		पूर्ण

		ret = cxgbit_queue_skb(csk, skb);
		अगर (unlikely(ret))
			जाओ out;

		tx_data += plen;
		data_length -= plen;

		cmd->पढ़ो_data_करोne += plen;
		cmd->data_sn += num_pdu;
	पूर्ण

	dr->dr_complete = DATAIN_COMPLETE_NORMAL;

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
cxgbit_tx_datain(काष्ठा cxgbit_sock *csk, काष्ठा iscsi_cmd *cmd,
		 स्थिर काष्ठा iscsi_datain *datain)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 0;

	skb = cxgbit_alloc_skb(csk, 0);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	स_नकल(skb->data, cmd->pdu, ISCSI_HDR_LEN);

	अगर (datain->length) अणु
		cxgbit_skcb_submode(skb) |= (csk->submode &
				CXGBIT_SUBMODE_DCRC);
		cxgbit_skcb_tx_extralen(skb) =
				cxgbit_digest_len[cxgbit_skcb_submode(skb)];
	पूर्ण

	ret = cxgbit_map_skb(cmd, skb, datain->offset, datain->length);
	अगर (ret < 0) अणु
		__kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	वापस cxgbit_queue_skb(csk, skb);
पूर्ण

अटल पूर्णांक
cxgbit_xmit_datain_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		       काष्ठा iscsi_datain_req *dr,
		       स्थिर काष्ठा iscsi_datain *datain)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	u32 data_length = cmd->se_cmd.data_length;
	u32 padding = ((-data_length) & 3);
	u32 mrdsl = conn->conn_ops->MaxRecvDataSegmentLength;

	अगर ((data_length > mrdsl) && (!dr->recovery) &&
	    (!padding) && (!datain->offset) && csk->max_iso_npdu) अणु
		atomic_दीर्घ_add(data_length - datain->length,
				&conn->sess->tx_data_octets);
		वापस cxgbit_tx_datain_iso(csk, cmd, dr);
	पूर्ण

	वापस cxgbit_tx_datain(csk, cmd, datain);
पूर्ण

अटल पूर्णांक
cxgbit_xmit_nondatain_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			  स्थिर व्योम *data_buf, u32 data_buf_len)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	काष्ठा sk_buff *skb;
	u32 padding = ((-data_buf_len) & 3);

	skb = cxgbit_alloc_skb(csk, data_buf_len + padding);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	स_नकल(skb->data, cmd->pdu, ISCSI_HDR_LEN);

	अगर (data_buf_len) अणु
		u32 pad_bytes = 0;

		skb_store_bits(skb, ISCSI_HDR_LEN, data_buf, data_buf_len);

		अगर (padding)
			skb_store_bits(skb, ISCSI_HDR_LEN + data_buf_len,
				       &pad_bytes, padding);
	पूर्ण

	cxgbit_skcb_tx_extralen(skb) = cxgbit_digest_len[
				       cxgbit_skcb_submode(skb)];

	वापस cxgbit_queue_skb(csk, skb);
पूर्ण

पूर्णांक
cxgbit_xmit_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		काष्ठा iscsi_datain_req *dr, स्थिर व्योम *buf, u32 buf_len)
अणु
	अगर (dr)
		वापस cxgbit_xmit_datain_pdu(conn, cmd, dr, buf);
	अन्यथा
		वापस cxgbit_xmit_nondatain_pdu(conn, cmd, buf, buf_len);
पूर्ण

पूर्णांक cxgbit_validate_params(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	काष्ठा cxgbit_device *cdev = csk->com.cdev;
	काष्ठा iscsi_param *param;
	u32 max_xmitdsl;

	param = iscsi_find_param_from_key(MAXXMITDATASEGMENTLENGTH,
					  conn->param_list);
	अगर (!param)
		वापस -1;

	अगर (kstrtou32(param->value, 0, &max_xmitdsl) < 0)
		वापस -1;

	अगर (max_xmitdsl > cdev->mdsl) अणु
		अगर (iscsi_change_param_प्र_लिखो(
			conn, "MaxXmitDataSegmentLength=%u", cdev->mdsl))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgbit_set_digest(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_param *param;

	param = iscsi_find_param_from_key(HEADERDIGEST, conn->param_list);
	अगर (!param) अणु
		pr_err("param not found key %s\n", HEADERDIGEST);
		वापस -1;
	पूर्ण

	अगर (!म_भेद(param->value, CRC32C))
		csk->submode |= CXGBIT_SUBMODE_HCRC;

	param = iscsi_find_param_from_key(DATADIGEST, conn->param_list);
	अगर (!param) अणु
		csk->submode = 0;
		pr_err("param not found key %s\n", DATADIGEST);
		वापस -1;
	पूर्ण

	अगर (!म_भेद(param->value, CRC32C))
		csk->submode |= CXGBIT_SUBMODE_DCRC;

	अगर (cxgbit_setup_conn_digest(csk)) अणु
		csk->submode = 0;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgbit_set_iso_npdu(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_conn_ops *conn_ops = conn->conn_ops;
	काष्ठा iscsi_param *param;
	u32 mrdsl, mbl;
	u32 max_npdu, max_iso_npdu;
	u32 max_iso_payload;

	अगर (conn->login->leading_connection) अणु
		param = iscsi_find_param_from_key(MAXBURSTLENGTH,
						  conn->param_list);
		अगर (!param) अणु
			pr_err("param not found key %s\n", MAXBURSTLENGTH);
			वापस -1;
		पूर्ण

		अगर (kstrtou32(param->value, 0, &mbl) < 0)
			वापस -1;
	पूर्ण अन्यथा अणु
		mbl = conn->sess->sess_ops->MaxBurstLength;
	पूर्ण

	mrdsl = conn_ops->MaxRecvDataSegmentLength;
	max_npdu = mbl / mrdsl;

	max_iso_payload = roundकरोwn(CXGBIT_MAX_ISO_PAYLOAD, csk->emss);

	max_iso_npdu = max_iso_payload /
		       (ISCSI_HDR_LEN + mrdsl +
			cxgbit_digest_len[csk->submode]);

	csk->max_iso_npdu = min(max_npdu, max_iso_npdu);

	अगर (csk->max_iso_npdu <= 1)
		csk->max_iso_npdu = 0;

	वापस 0;
पूर्ण

/*
 * cxgbit_seq_pdu_inorder()
 * @csk: poपूर्णांकer to cxgbit socket काष्ठाure
 *
 * This function checks whether data sequence and data
 * pdu are in order.
 *
 * Return: वापसs -1 on error, 0 अगर data sequence and
 * data pdu are in order, 1 अगर data sequence or data pdu
 * is not in order.
 */
अटल पूर्णांक cxgbit_seq_pdu_inorder(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_param *param;

	अगर (conn->login->leading_connection) अणु
		param = iscsi_find_param_from_key(DATASEQUENCEINORDER,
						  conn->param_list);
		अगर (!param) अणु
			pr_err("param not found key %s\n", DATASEQUENCEINORDER);
			वापस -1;
		पूर्ण

		अगर (म_भेद(param->value, YES))
			वापस 1;

		param = iscsi_find_param_from_key(DATAPDUINORDER,
						  conn->param_list);
		अगर (!param) अणु
			pr_err("param not found key %s\n", DATAPDUINORDER);
			वापस -1;
		पूर्ण

		अगर (म_भेद(param->value, YES))
			वापस 1;

	पूर्ण अन्यथा अणु
		अगर (!conn->sess->sess_ops->DataSequenceInOrder)
			वापस 1;
		अगर (!conn->sess->sess_ops->DataPDUInOrder)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgbit_set_params(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	काष्ठा cxgbit_device *cdev = csk->com.cdev;
	काष्ठा cxgbi_ppm *ppm = *csk->com.cdev->lldi.iscsi_ppm;
	काष्ठा iscsi_conn_ops *conn_ops = conn->conn_ops;
	काष्ठा iscsi_param *param;
	u8 erl;

	अगर (conn_ops->MaxRecvDataSegmentLength > cdev->mdsl)
		conn_ops->MaxRecvDataSegmentLength = cdev->mdsl;

	अगर (cxgbit_set_digest(csk))
		वापस -1;

	अगर (conn->login->leading_connection) अणु
		param = iscsi_find_param_from_key(ERRORRECOVERYLEVEL,
						  conn->param_list);
		अगर (!param) अणु
			pr_err("param not found key %s\n", ERRORRECOVERYLEVEL);
			वापस -1;
		पूर्ण
		अगर (kstrtou8(param->value, 0, &erl) < 0)
			वापस -1;
	पूर्ण अन्यथा अणु
		erl = conn->sess->sess_ops->ErrorRecoveryLevel;
	पूर्ण

	अगर (!erl) अणु
		पूर्णांक ret;

		ret = cxgbit_seq_pdu_inorder(csk);
		अगर (ret < 0) अणु
			वापस -1;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			अगर (is_t5(cdev->lldi.adapter_type))
				जाओ enable_ddp;
			अन्यथा
				वापस 0;
		पूर्ण

		अगर (test_bit(CDEV_ISO_ENABLE, &cdev->flags)) अणु
			अगर (cxgbit_set_iso_npdu(csk))
				वापस -1;
		पूर्ण

enable_ddp:
		अगर (test_bit(CDEV_DDP_ENABLE, &cdev->flags)) अणु
			अगर (cxgbit_setup_conn_pgidx(csk,
						    ppm->tक्रमmat.pgsz_idx_dflt))
				वापस -1;
			set_bit(CSK_DDP_ENABLE, &csk->com.flags);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
cxgbit_put_login_tx(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login,
		    u32 length)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	काष्ठा sk_buff *skb;
	u32 padding_buf = 0;
	u8 padding = ((-length) & 3);

	skb = cxgbit_alloc_skb(csk, length + padding);
	अगर (!skb)
		वापस -ENOMEM;
	skb_store_bits(skb, 0, login->rsp, ISCSI_HDR_LEN);
	skb_store_bits(skb, ISCSI_HDR_LEN, login->rsp_buf, length);

	अगर (padding)
		skb_store_bits(skb, ISCSI_HDR_LEN + length,
			       &padding_buf, padding);

	अगर (login->login_complete) अणु
		अगर (cxgbit_set_params(conn)) अणु
			kमुक्त_skb(skb);
			वापस -1;
		पूर्ण

		set_bit(CSK_LOGIN_DONE, &csk->com.flags);
	पूर्ण

	अगर (cxgbit_queue_skb(csk, skb))
		वापस -1;

	अगर ((!login->login_complete) && (!login->login_failed))
		schedule_delayed_work(&conn->login_work, 0);

	वापस 0;
पूर्ण

अटल व्योम
cxgbit_skb_copy_to_sg(काष्ठा sk_buff *skb, काष्ठा scatterlist *sg,
		      अचिन्हित पूर्णांक nents, u32 skip)
अणु
	काष्ठा skb_seq_state st;
	स्थिर u8 *buf;
	अचिन्हित पूर्णांक consumed = 0, buf_len;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(skb);

	skb_prepare_seq_पढ़ो(skb, pdu_cb->करोffset,
			     pdu_cb->करोffset + pdu_cb->dlen,
			     &st);

	जबतक (true) अणु
		buf_len = skb_seq_पढ़ो(consumed, &buf, &st);
		अगर (!buf_len) अणु
			skb_पात_seq_पढ़ो(&st);
			अवरोध;
		पूर्ण

		consumed += sg_pcopy_from_buffer(sg, nents, (व्योम *)buf,
						 buf_len, skip + consumed);
	पूर्ण
पूर्ण

अटल काष्ठा iscsi_cmd *cxgbit_allocate_cmd(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा cxgbi_ppm *ppm = cdev2ppm(csk->com.cdev);
	काष्ठा cxgbit_cmd *ccmd;
	काष्ठा iscsi_cmd *cmd;

	cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
	अगर (!cmd) अणु
		pr_err("Unable to allocate iscsi_cmd + cxgbit_cmd\n");
		वापस शून्य;
	पूर्ण

	ccmd = iscsit_priv_cmd(cmd);
	ccmd->ttinfo.tag = ppm->tक्रमmat.no_ddp_mask;
	ccmd->setup_ddp = true;

	वापस cmd;
पूर्ण

अटल पूर्णांक
cxgbit_handle_immediate_data(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_scsi_req *hdr,
			     u32 length)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा cxgbit_sock *csk = conn->context;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);

	अगर (pdu_cb->flags & PDUCBF_RX_DCRC_ERR) अणु
		pr_err("ImmediateData CRC32C DataDigest error\n");
		अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
			pr_err("Unable to recover from"
			       " Immediate Data digest failure while"
			       " in ERL=0.\n");
			iscsit_reject_cmd(cmd, ISCSI_REASON_DATA_DIGEST_ERROR,
					  (अचिन्हित अक्षर *)hdr);
			वापस IMMEDIATE_DATA_CANNOT_RECOVER;
		पूर्ण

		iscsit_reject_cmd(cmd, ISCSI_REASON_DATA_DIGEST_ERROR,
				  (अचिन्हित अक्षर *)hdr);
		वापस IMMEDIATE_DATA_ERL1_CRC_FAILURE;
	पूर्ण

	अगर (cmd->se_cmd.se_cmd_flags & SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC) अणु
		काष्ठा cxgbit_cmd *ccmd = iscsit_priv_cmd(cmd);
		काष्ठा skb_shared_info *ssi = skb_shinfo(csk->skb);
		skb_frag_t *dfrag = &ssi->frags[pdu_cb->dfrag_idx];

		sg_init_table(&ccmd->sg, 1);
		sg_set_page(&ccmd->sg, skb_frag_page(dfrag),
				skb_frag_size(dfrag), skb_frag_off(dfrag));
		get_page(skb_frag_page(dfrag));

		cmd->se_cmd.t_data_sg = &ccmd->sg;
		cmd->se_cmd.t_data_nents = 1;

		ccmd->release = true;
	पूर्ण अन्यथा अणु
		काष्ठा scatterlist *sg = &cmd->se_cmd.t_data_sg[0];
		u32 sg_nents = max(1UL, DIV_ROUND_UP(pdu_cb->dlen, PAGE_SIZE));

		cxgbit_skb_copy_to_sg(csk->skb, sg, sg_nents, 0);
	पूर्ण

	cmd->ग_लिखो_data_करोne += pdu_cb->dlen;

	अगर (cmd->ग_लिखो_data_करोne == cmd->se_cmd.data_length) अणु
		spin_lock_bh(&cmd->istate_lock);
		cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
		cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
		spin_unlock_bh(&cmd->istate_lock);
	पूर्ण

	वापस IMMEDIATE_DATA_NORMAL_OPERATION;
पूर्ण

अटल पूर्णांक
cxgbit_get_immediate_data(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_scsi_req *hdr,
			  bool dump_payload)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	पूर्णांक cmdsn_ret = 0, immed_ret = IMMEDIATE_DATA_NORMAL_OPERATION;
	/*
	 * Special हाल क्रम Unsupported SAM WRITE Opcodes and ImmediateData=Yes.
	 */
	अगर (dump_payload)
		जाओ after_immediate_data;

	immed_ret = cxgbit_handle_immediate_data(cmd, hdr,
						 cmd->first_burst_len);
after_immediate_data:
	अगर (immed_ret == IMMEDIATE_DATA_NORMAL_OPERATION) अणु
		/*
		 * A PDU/CmdSN carrying Immediate Data passed
		 * DataCRC, check against ExpCmdSN/MaxCmdSN अगर
		 * Immediate Bit is not set.
		 */
		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
						(अचिन्हित अक्षर *)hdr,
						hdr->cmdsn);
		अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			वापस -1;

		अगर (cmd->sense_reason || cmdsn_ret == CMDSN_LOWER_THAN_EXP) अणु
			target_put_sess_cmd(&cmd->se_cmd);
			वापस 0;
		पूर्ण अन्यथा अगर (cmd->unsolicited_data) अणु
			iscsit_set_unsolicited_dataout(cmd);
		पूर्ण

	पूर्ण अन्यथा अगर (immed_ret == IMMEDIATE_DATA_ERL1_CRC_FAILURE) अणु
		/*
		 * Immediate Data failed DataCRC and ERL>=1,
		 * silently drop this PDU and let the initiator
		 * plug the CmdSN gap.
		 *
		 * FIXME: Send Unsolicited NOPIN with reserved
		 * TTT here to help the initiator figure out
		 * the missing CmdSN, although they should be
		 * पूर्णांकelligent enough to determine the missing
		 * CmdSN and issue a retry to plug the sequence.
		 */
		cmd->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, conn, cmd->i_state);
	पूर्ण अन्यथा /* immed_ret == IMMEDIATE_DATA_CANNOT_RECOVER */
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
cxgbit_handle_scsi_cmd(काष्ठा cxgbit_sock *csk, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_scsi_req *hdr = (काष्ठा iscsi_scsi_req *)pdu_cb->hdr;
	पूर्णांक rc;
	bool dump_payload = false;

	rc = iscsit_setup_scsi_cmd(conn, cmd, (अचिन्हित अक्षर *)hdr);
	अगर (rc < 0)
		वापस rc;

	अगर (pdu_cb->dlen && (pdu_cb->dlen == cmd->se_cmd.data_length) &&
	    (pdu_cb->nr_dfrags == 1))
		cmd->se_cmd.se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;

	rc = iscsit_process_scsi_cmd(conn, cmd, hdr);
	अगर (rc < 0)
		वापस 0;
	अन्यथा अगर (rc > 0)
		dump_payload = true;

	अगर (!pdu_cb->dlen)
		वापस 0;

	वापस cxgbit_get_immediate_data(cmd, hdr, dump_payload);
पूर्ण

अटल पूर्णांक cxgbit_handle_iscsi_dataout(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा scatterlist *sg_start;
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_cmd *cmd = शून्य;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *)pdu_cb->hdr;
	u32 data_offset = be32_to_cpu(hdr->offset);
	u32 data_len = pdu_cb->dlen;
	पूर्णांक rc, sg_nents, sg_off;
	bool dcrc_err = false;

	अगर (pdu_cb->flags & PDUCBF_RX_DDP_CMP) अणु
		u32 offset = be32_to_cpu(hdr->offset);
		u32 ddp_data_len;
		u32 payload_length = ntoh24(hdr->dlength);
		bool success = false;

		cmd = iscsit_find_cmd_from_itt_or_dump(conn, hdr->itt, 0);
		अगर (!cmd)
			वापस 0;

		ddp_data_len = offset - cmd->ग_लिखो_data_करोne;
		atomic_दीर्घ_add(ddp_data_len, &conn->sess->rx_data_octets);

		cmd->ग_लिखो_data_करोne = offset;
		cmd->next_burst_len = ddp_data_len;
		cmd->data_sn = be32_to_cpu(hdr->datasn);

		rc = __iscsit_check_dataout_hdr(conn, (अचिन्हित अक्षर *)hdr,
						cmd, payload_length, &success);
		अगर (rc < 0)
			वापस rc;
		अन्यथा अगर (!success)
			वापस 0;
	पूर्ण अन्यथा अणु
		rc = iscsit_check_dataout_hdr(conn, (अचिन्हित अक्षर *)hdr, &cmd);
		अगर (rc < 0)
			वापस rc;
		अन्यथा अगर (!cmd)
			वापस 0;
	पूर्ण

	अगर (pdu_cb->flags & PDUCBF_RX_DCRC_ERR) अणु
		pr_err("ITT: 0x%08x, Offset: %u, Length: %u,"
		       " DataSN: 0x%08x\n",
		       hdr->itt, hdr->offset, data_len,
		       hdr->datasn);

		dcrc_err = true;
		जाओ check_payload;
	पूर्ण

	pr_debug("DataOut data_len: %u, "
		"write_data_done: %u, data_length: %u\n",
		  data_len,  cmd->ग_लिखो_data_करोne,
		  cmd->se_cmd.data_length);

	अगर (!(pdu_cb->flags & PDUCBF_RX_DATA_DDPD)) अणु
		u32 skip = data_offset % PAGE_SIZE;

		sg_off = data_offset / PAGE_SIZE;
		sg_start = &cmd->se_cmd.t_data_sg[sg_off];
		sg_nents = max(1UL, DIV_ROUND_UP(skip + data_len, PAGE_SIZE));

		cxgbit_skb_copy_to_sg(csk->skb, sg_start, sg_nents, skip);
	पूर्ण

check_payload:

	rc = iscsit_check_dataout_payload(cmd, hdr, dcrc_err);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक cxgbit_handle_nop_out(काष्ठा cxgbit_sock *csk, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_nopout *hdr = (काष्ठा iscsi_nopout *)pdu_cb->hdr;
	अचिन्हित अक्षर *ping_data = शून्य;
	u32 payload_length = pdu_cb->dlen;
	पूर्णांक ret;

	ret = iscsit_setup_nop_out(conn, cmd, hdr);
	अगर (ret < 0)
		वापस 0;

	अगर (pdu_cb->flags & PDUCBF_RX_DCRC_ERR) अणु
		अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
			pr_err("Unable to recover from"
			       " NOPOUT Ping DataCRC failure while in"
			       " ERL=0.\n");
			ret = -1;
			जाओ out;
		पूर्ण अन्यथा अणु
			/*
			 * drop this PDU and let the
			 * initiator plug the CmdSN gap.
			 */
			pr_info("Dropping NOPOUT"
				" Command CmdSN: 0x%08x due to"
				" DataCRC error.\n", hdr->cmdsn);
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Handle NOP-OUT payload क्रम traditional iSCSI sockets
	 */
	अगर (payload_length && hdr->ttt == cpu_to_be32(0xFFFFFFFF)) अणु
		ping_data = kzalloc(payload_length + 1, GFP_KERNEL);
		अगर (!ping_data) अणु
			pr_err("Unable to allocate memory for"
				" NOPOUT ping data.\n");
			ret = -1;
			जाओ out;
		पूर्ण

		skb_copy_bits(csk->skb, pdu_cb->करोffset,
			      ping_data, payload_length);

		ping_data[payload_length] = '\0';
		/*
		 * Attach ping data to काष्ठा iscsi_cmd->buf_ptr.
		 */
		cmd->buf_ptr = ping_data;
		cmd->buf_ptr_size = payload_length;

		pr_debug("Got %u bytes of NOPOUT ping"
			" data.\n", payload_length);
		pr_debug("Ping Data: \"%s\"\n", ping_data);
	पूर्ण

	वापस iscsit_process_nop_out(conn, cmd, hdr);
out:
	अगर (cmd)
		iscsit_मुक्त_cmd(cmd, false);
	वापस ret;
पूर्ण

अटल पूर्णांक
cxgbit_handle_text_cmd(काष्ठा cxgbit_sock *csk, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_text *hdr = (काष्ठा iscsi_text *)pdu_cb->hdr;
	u32 payload_length = pdu_cb->dlen;
	पूर्णांक rc;
	अचिन्हित अक्षर *text_in = शून्य;

	rc = iscsit_setup_text_cmd(conn, cmd, hdr);
	अगर (rc < 0)
		वापस rc;

	अगर (pdu_cb->flags & PDUCBF_RX_DCRC_ERR) अणु
		अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
			pr_err("Unable to recover from"
			       " Text Data digest failure while in"
			       " ERL=0.\n");
			जाओ reject;
		पूर्ण अन्यथा अणु
			/*
			 * drop this PDU and let the
			 * initiator plug the CmdSN gap.
			 */
			pr_info("Dropping Text"
				" Command CmdSN: 0x%08x due to"
				" DataCRC error.\n", hdr->cmdsn);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (payload_length) अणु
		text_in = kzalloc(payload_length, GFP_KERNEL);
		अगर (!text_in) अणु
			pr_err("Unable to allocate text_in of payload_length: %u\n",
			       payload_length);
			वापस -ENOMEM;
		पूर्ण
		skb_copy_bits(csk->skb, pdu_cb->करोffset,
			      text_in, payload_length);

		text_in[payload_length - 1] = '\0';

		cmd->text_in_ptr = text_in;
	पूर्ण

	वापस iscsit_process_text_cmd(conn, cmd, hdr);

reject:
	वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
				 pdu_cb->hdr);
पूर्ण

अटल पूर्णांक cxgbit_target_rx_opcode(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_hdr *hdr = (काष्ठा iscsi_hdr *)pdu_cb->hdr;
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_cmd *cmd = शून्य;
	u8 opcode = (hdr->opcode & ISCSI_OPCODE_MASK);
	पूर्णांक ret = -EINVAL;

	चयन (opcode) अणु
	हाल ISCSI_OP_SCSI_CMD:
		cmd = cxgbit_allocate_cmd(csk);
		अगर (!cmd)
			जाओ reject;

		ret = cxgbit_handle_scsi_cmd(csk, cmd);
		अवरोध;
	हाल ISCSI_OP_SCSI_DATA_OUT:
		ret = cxgbit_handle_iscsi_dataout(csk);
		अवरोध;
	हाल ISCSI_OP_NOOP_OUT:
		अगर (hdr->ttt == cpu_to_be32(0xFFFFFFFF)) अणु
			cmd = cxgbit_allocate_cmd(csk);
			अगर (!cmd)
				जाओ reject;
		पूर्ण

		ret = cxgbit_handle_nop_out(csk, cmd);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		cmd = cxgbit_allocate_cmd(csk);
		अगर (!cmd)
			जाओ reject;

		ret = iscsit_handle_task_mgt_cmd(conn, cmd,
						 (अचिन्हित अक्षर *)hdr);
		अवरोध;
	हाल ISCSI_OP_TEXT:
		अगर (hdr->ttt != cpu_to_be32(0xFFFFFFFF)) अणु
			cmd = iscsit_find_cmd_from_itt(conn, hdr->itt);
			अगर (!cmd)
				जाओ reject;
		पूर्ण अन्यथा अणु
			cmd = cxgbit_allocate_cmd(csk);
			अगर (!cmd)
				जाओ reject;
		पूर्ण

		ret = cxgbit_handle_text_cmd(csk, cmd);
		अवरोध;
	हाल ISCSI_OP_LOGOUT:
		cmd = cxgbit_allocate_cmd(csk);
		अगर (!cmd)
			जाओ reject;

		ret = iscsit_handle_logout_cmd(conn, cmd, (अचिन्हित अक्षर *)hdr);
		अगर (ret > 0)
			रुको_क्रम_completion_समयout(&conn->conn_logout_comp,
						    SECONDS_FOR_LOGOUT_COMP
						    * HZ);
		अवरोध;
	हाल ISCSI_OP_SNACK:
		ret = iscsit_handle_snack(conn, (अचिन्हित अक्षर *)hdr);
		अवरोध;
	शेष:
		pr_err("Got unknown iSCSI OpCode: 0x%02x\n", opcode);
		dump_stack();
		अवरोध;
	पूर्ण

	वापस ret;

reject:
	वापस iscsit_add_reject(conn, ISCSI_REASON_BOOKMARK_NO_RESOURCES,
				 (अचिन्हित अक्षर *)hdr);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgbit_rx_opcode(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_hdr *hdr = pdu_cb->hdr;
	u8 opcode;

	अगर (pdu_cb->flags & PDUCBF_RX_HCRC_ERR) अणु
		atomic_दीर्घ_inc(&conn->sess->conn_digest_errors);
		जाओ transport_err;
	पूर्ण

	अगर (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT)
		जाओ transport_err;

	opcode = hdr->opcode & ISCSI_OPCODE_MASK;

	अगर (conn->sess->sess_ops->SessionType &&
	    ((!(opcode & ISCSI_OP_TEXT)) ||
	     (!(opcode & ISCSI_OP_LOGOUT)))) अणु
		pr_err("Received illegal iSCSI Opcode: 0x%02x"
			" while in Discovery Session, rejecting.\n", opcode);
		iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
				  (अचिन्हित अक्षर *)hdr);
		जाओ transport_err;
	पूर्ण

	अगर (cxgbit_target_rx_opcode(csk) < 0)
		जाओ transport_err;

	वापस 0;

transport_err:
	वापस -1;
पूर्ण

अटल पूर्णांक cxgbit_rx_login_pdu(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा iscsi_conn *conn = csk->conn;
	काष्ठा iscsi_login *login = conn->login;
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_rx_pdu_cb(csk->skb);
	काष्ठा iscsi_login_req *login_req;

	login_req = (काष्ठा iscsi_login_req *)login->req;
	स_नकल(login_req, pdu_cb->hdr, माप(*login_req));

	pr_debug("Got Login Command, Flags 0x%02x, ITT: 0x%08x,"
		" CmdSN: 0x%08x, ExpStatSN: 0x%08x, CID: %hu, Length: %u\n",
		login_req->flags, login_req->itt, login_req->cmdsn,
		login_req->exp_statsn, login_req->cid, pdu_cb->dlen);
	/*
	 * Setup the initial iscsi_login values from the leading
	 * login request PDU.
	 */
	अगर (login->first_request) अणु
		login_req = (काष्ठा iscsi_login_req *)login->req;
		login->leading_connection = (!login_req->tsih) ? 1 : 0;
		login->current_stage	= ISCSI_LOGIN_CURRENT_STAGE(
				login_req->flags);
		login->version_min	= login_req->min_version;
		login->version_max	= login_req->max_version;
		स_नकल(login->isid, login_req->isid, 6);
		login->cmd_sn		= be32_to_cpu(login_req->cmdsn);
		login->init_task_tag	= login_req->itt;
		login->initial_exp_statsn = be32_to_cpu(login_req->exp_statsn);
		login->cid		= be16_to_cpu(login_req->cid);
		login->tsih		= be16_to_cpu(login_req->tsih);
	पूर्ण

	अगर (iscsi_target_check_login_request(conn, login) < 0)
		वापस -1;

	स_रखो(login->req_buf, 0, MAX_KEY_VALUE_PAIRS);
	skb_copy_bits(csk->skb, pdu_cb->करोffset, login->req_buf, pdu_cb->dlen);

	वापस 0;
पूर्ण

अटल पूर्णांक
cxgbit_process_iscsi_pdu(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb, पूर्णांक idx)
अणु
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, idx);
	पूर्णांक ret;

	cxgbit_rx_pdu_cb(skb) = pdu_cb;

	csk->skb = skb;

	अगर (!test_bit(CSK_LOGIN_DONE, &csk->com.flags)) अणु
		ret = cxgbit_rx_login_pdu(csk);
		set_bit(CSK_LOGIN_PDU_DONE, &csk->com.flags);
	पूर्ण अन्यथा अणु
		ret = cxgbit_rx_opcode(csk);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cxgbit_lro_skb_dump(काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_info *ssi = skb_shinfo(skb);
	काष्ठा cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, 0);
	u8 i;

	pr_info("skb 0x%p, head 0x%p, 0x%p, len %u,%u, frags %u.\n",
		skb, skb->head, skb->data, skb->len, skb->data_len,
		ssi->nr_frags);
	pr_info("skb 0x%p, lro_cb, csk 0x%p, pdu %u, %u.\n",
		skb, lro_cb->csk, lro_cb->pdu_idx, lro_cb->pdu_totallen);

	क्रम (i = 0; i < lro_cb->pdu_idx; i++, pdu_cb++)
		pr_info("skb 0x%p, pdu %d, %u, f 0x%x, seq 0x%x, dcrc 0x%x, "
			"frags %u.\n",
			skb, i, pdu_cb->pdulen, pdu_cb->flags, pdu_cb->seq,
			pdu_cb->ddigest, pdu_cb->frags);
	क्रम (i = 0; i < ssi->nr_frags; i++)
		pr_info("skb 0x%p, frag %d, off %u, sz %u.\n",
			skb, i, skb_frag_off(&ssi->frags[i]),
			skb_frag_size(&ssi->frags[i]));
पूर्ण

अटल व्योम cxgbit_lro_hskb_reset(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb = csk->lro_hskb;
	काष्ठा skb_shared_info *ssi = skb_shinfo(skb);
	u8 i;

	स_रखो(skb->data, 0, LRO_SKB_MIN_HEADROOM);
	क्रम (i = 0; i < ssi->nr_frags; i++)
		put_page(skb_frag_page(&ssi->frags[i]));
	ssi->nr_frags = 0;
	skb->data_len = 0;
	skb->truesize -= skb->len;
	skb->len = 0;
पूर्ण

अटल व्योम
cxgbit_lro_skb_merge(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb, u8 pdu_idx)
अणु
	काष्ठा sk_buff *hskb = csk->lro_hskb;
	काष्ठा cxgbit_lro_pdu_cb *hpdu_cb = cxgbit_skb_lro_pdu_cb(hskb, 0);
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, pdu_idx);
	काष्ठा skb_shared_info *hssi = skb_shinfo(hskb);
	काष्ठा skb_shared_info *ssi = skb_shinfo(skb);
	अचिन्हित पूर्णांक len = 0;

	अगर (pdu_cb->flags & PDUCBF_RX_HDR) अणु
		u8 hfrag_idx = hssi->nr_frags;

		hpdu_cb->flags |= pdu_cb->flags;
		hpdu_cb->seq = pdu_cb->seq;
		hpdu_cb->hdr = pdu_cb->hdr;
		hpdu_cb->hlen = pdu_cb->hlen;

		स_नकल(&hssi->frags[hfrag_idx], &ssi->frags[pdu_cb->hfrag_idx],
		       माप(skb_frag_t));

		get_page(skb_frag_page(&hssi->frags[hfrag_idx]));
		hssi->nr_frags++;
		hpdu_cb->frags++;
		hpdu_cb->hfrag_idx = hfrag_idx;

		len = skb_frag_size(&hssi->frags[hfrag_idx]);
		hskb->len += len;
		hskb->data_len += len;
		hskb->truesize += len;
	पूर्ण

	अगर (pdu_cb->flags & PDUCBF_RX_DATA) अणु
		u8 dfrag_idx = hssi->nr_frags, i;

		hpdu_cb->flags |= pdu_cb->flags;
		hpdu_cb->dfrag_idx = dfrag_idx;

		len = 0;
		क्रम (i = 0; i < pdu_cb->nr_dfrags; dfrag_idx++, i++) अणु
			स_नकल(&hssi->frags[dfrag_idx],
			       &ssi->frags[pdu_cb->dfrag_idx + i],
			       माप(skb_frag_t));

			get_page(skb_frag_page(&hssi->frags[dfrag_idx]));

			len += skb_frag_size(&hssi->frags[dfrag_idx]);

			hssi->nr_frags++;
			hpdu_cb->frags++;
		पूर्ण

		hpdu_cb->dlen = pdu_cb->dlen;
		hpdu_cb->करोffset = hpdu_cb->hlen;
		hpdu_cb->nr_dfrags = pdu_cb->nr_dfrags;
		hskb->len += len;
		hskb->data_len += len;
		hskb->truesize += len;
	पूर्ण

	अगर (pdu_cb->flags & PDUCBF_RX_STATUS) अणु
		hpdu_cb->flags |= pdu_cb->flags;

		अगर (hpdu_cb->flags & PDUCBF_RX_DATA)
			hpdu_cb->flags &= ~PDUCBF_RX_DATA_DDPD;

		hpdu_cb->ddigest = pdu_cb->ddigest;
		hpdu_cb->pdulen = pdu_cb->pdulen;
	पूर्ण
पूर्ण

अटल पूर्णांक cxgbit_process_lro_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, 0);
	u8 pdu_idx = 0, last_idx = 0;
	पूर्णांक ret = 0;

	अगर (!pdu_cb->complete) अणु
		cxgbit_lro_skb_merge(csk, skb, 0);

		अगर (pdu_cb->flags & PDUCBF_RX_STATUS) अणु
			काष्ठा sk_buff *hskb = csk->lro_hskb;

			ret = cxgbit_process_iscsi_pdu(csk, hskb, 0);

			cxgbit_lro_hskb_reset(csk);

			अगर (ret < 0)
				जाओ out;
		पूर्ण

		pdu_idx = 1;
	पूर्ण

	अगर (lro_cb->pdu_idx)
		last_idx = lro_cb->pdu_idx - 1;

	क्रम (; pdu_idx <= last_idx; pdu_idx++) अणु
		ret = cxgbit_process_iscsi_pdu(csk, skb, pdu_idx);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर ((!lro_cb->complete) && lro_cb->pdu_idx)
		cxgbit_lro_skb_merge(csk, skb, lro_cb->pdu_idx);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक cxgbit_rx_lro_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	काष्ठा cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, 0);
	पूर्णांक ret = -1;

	अगर ((pdu_cb->flags & PDUCBF_RX_HDR) &&
	    (pdu_cb->seq != csk->rcv_nxt)) अणु
		pr_info("csk 0x%p, tid 0x%x, seq 0x%x != 0x%x.\n",
			csk, csk->tid, pdu_cb->seq, csk->rcv_nxt);
		cxgbit_lro_skb_dump(skb);
		वापस ret;
	पूर्ण

	csk->rcv_nxt += lro_cb->pdu_totallen;

	ret = cxgbit_process_lro_skb(csk, skb);

	csk->rx_credits += lro_cb->pdu_totallen;

	अगर (csk->rx_credits >= (csk->rcv_win / 4))
		cxgbit_rx_data_ack(csk);

	वापस ret;
पूर्ण

अटल पूर्णांक cxgbit_rx_skb(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff *skb)
अणु
	काष्ठा cxgb4_lld_info *lldi = &csk->com.cdev->lldi;
	पूर्णांक ret = -1;

	अगर (likely(cxgbit_skcb_flags(skb) & SKCBF_RX_LRO)) अणु
		अगर (is_t5(lldi->adapter_type))
			ret = cxgbit_rx_lro_skb(csk, skb);
		अन्यथा
			ret = cxgbit_process_lro_skb(csk, skb);
	पूर्ण

	__kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल bool cxgbit_rxq_len(काष्ठा cxgbit_sock *csk, काष्ठा sk_buff_head *rxq)
अणु
	spin_lock_bh(&csk->rxq.lock);
	अगर (skb_queue_len(&csk->rxq)) अणु
		skb_queue_splice_init(&csk->rxq, rxq);
		spin_unlock_bh(&csk->rxq.lock);
		वापस true;
	पूर्ण
	spin_unlock_bh(&csk->rxq.lock);
	वापस false;
पूर्ण

अटल पूर्णांक cxgbit_रुको_rxq(काष्ठा cxgbit_sock *csk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head rxq;

	skb_queue_head_init(&rxq);

	रुको_event_पूर्णांकerruptible(csk->रुकोq, cxgbit_rxq_len(csk, &rxq));

	अगर (संकेत_pending(current))
		जाओ out;

	जबतक ((skb = __skb_dequeue(&rxq))) अणु
		अगर (cxgbit_rx_skb(csk, skb))
			जाओ out;
	पूर्ण

	वापस 0;
out:
	__skb_queue_purge(&rxq);
	वापस -1;
पूर्ण

पूर्णांक cxgbit_get_login_rx(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	पूर्णांक ret = -1;

	जबतक (!test_and_clear_bit(CSK_LOGIN_PDU_DONE, &csk->com.flags)) अणु
		ret = cxgbit_रुको_rxq(csk);
		अगर (ret) अणु
			clear_bit(CSK_LOGIN_PDU_DONE, &csk->com.flags);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम cxgbit_get_rx_pdu(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;

	जबतक (!kthपढ़ो_should_stop()) अणु
		iscsit_thपढ़ो_check_cpumask(conn, current, 0);
		अगर (cxgbit_रुको_rxq(csk))
			वापस;
	पूर्ण
पूर्ण
