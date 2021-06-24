<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2020-2021 Intel Corporation
 */
#समावेश <net/tso.h>
#समावेश <linux/tcp.h>

#समावेश "iwl-debug.h"
#समावेश "iwl-io.h"
#समावेश "fw/api/tx.h"
#समावेश "queue/tx.h"
#समावेश "iwl-fh.h"
#समावेश "iwl-scd.h"
#समावेश <linux/dmapool.h>

/*
 * iwl_txq_update_byte_tbl - Set up entry in Tx byte-count array
 */
अटल व्योम iwl_pcie_gen2_update_byte_tbl(काष्ठा iwl_trans *trans,
					  काष्ठा iwl_txq *txq, u16 byte_cnt,
					  पूर्णांक num_tbs)
अणु
	पूर्णांक idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);
	u8 filled_tfd_size, num_fetch_chunks;
	u16 len = byte_cnt;
	__le16 bc_ent;

	अगर (WARN(idx >= txq->n_winकरोw, "%d >= %d\n", idx, txq->n_winकरोw))
		वापस;

	filled_tfd_size = दुरत्व(काष्ठा iwl_tfh_tfd, tbs) +
			  num_tbs * माप(काष्ठा iwl_tfh_tb);
	/*
	 * filled_tfd_size contains the number of filled bytes in the TFD.
	 * Dividing it by 64 will give the number of chunks to fetch
	 * to SRAM- 0 क्रम one chunk, 1 क्रम 2 and so on.
	 * If, क्रम example, TFD contains only 3 TBs then 32 bytes
	 * of the TFD are used, and only one chunk of 64 bytes should
	 * be fetched
	 */
	num_fetch_chunks = DIV_ROUND_UP(filled_tfd_size, 64) - 1;

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		काष्ठा iwl_gen3_bc_tbl *scd_bc_tbl_gen3 = txq->bc_tbl.addr;

		/* Starting from AX210, the HW expects bytes */
		WARN_ON(trans->txqs.bc_table_dword);
		WARN_ON(len > 0x3FFF);
		bc_ent = cpu_to_le16(len | (num_fetch_chunks << 14));
		scd_bc_tbl_gen3->tfd_offset[idx] = bc_ent;
	पूर्ण अन्यथा अणु
		काष्ठा iwlagn_scd_bc_tbl *scd_bc_tbl = txq->bc_tbl.addr;

		/* Beक्रमe AX210, the HW expects DW */
		WARN_ON(!trans->txqs.bc_table_dword);
		len = DIV_ROUND_UP(len, 4);
		WARN_ON(len > 0xFFF);
		bc_ent = cpu_to_le16(len | (num_fetch_chunks << 12));
		scd_bc_tbl->tfd_offset[idx] = bc_ent;
	पूर्ण
पूर्ण

/*
 * iwl_txq_inc_wr_ptr - Send new ग_लिखो index to hardware
 */
व्योम iwl_txq_inc_wr_ptr(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq)
अणु
	lockdep_निश्चित_held(&txq->lock);

	IWL_DEBUG_TX(trans, "Q:%d WR: 0x%x\n", txq->id, txq->ग_लिखो_ptr);

	/*
	 * अगर not in घातer-save mode, uCode will never sleep when we're
	 * trying to tx (during RFKILL, we're not trying to tx).
	 */
	iwl_ग_लिखो32(trans, HBUS_TARG_WRPTR, txq->ग_लिखो_ptr | (txq->id << 16));
पूर्ण

अटल u8 iwl_txq_gen2_get_num_tbs(काष्ठा iwl_trans *trans,
				   काष्ठा iwl_tfh_tfd *tfd)
अणु
	वापस le16_to_cpu(tfd->num_tbs) & 0x1f;
पूर्ण

व्योम iwl_txq_gen2_tfd_unmap(काष्ठा iwl_trans *trans, काष्ठा iwl_cmd_meta *meta,
			    काष्ठा iwl_tfh_tfd *tfd)
अणु
	पूर्णांक i, num_tbs;

	/* Sanity check on number of chunks */
	num_tbs = iwl_txq_gen2_get_num_tbs(trans, tfd);

	अगर (num_tbs > trans->txqs.tfd.max_tbs) अणु
		IWL_ERR(trans, "Too many chunks: %i\n", num_tbs);
		वापस;
	पूर्ण

	/* first TB is never मुक्तd - it's the bidirectional DMA data */
	क्रम (i = 1; i < num_tbs; i++) अणु
		अगर (meta->tbs & BIT(i))
			dma_unmap_page(trans->dev,
				       le64_to_cpu(tfd->tbs[i].addr),
				       le16_to_cpu(tfd->tbs[i].tb_len),
				       DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(trans->dev,
					 le64_to_cpu(tfd->tbs[i].addr),
					 le16_to_cpu(tfd->tbs[i].tb_len),
					 DMA_TO_DEVICE);
	पूर्ण

	tfd->num_tbs = 0;
पूर्ण

व्योम iwl_txq_gen2_मुक्त_tfd(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq)
अणु
	/* rd_ptr is bounded by TFD_QUEUE_SIZE_MAX and
	 * idx is bounded by n_winकरोw
	 */
	पूर्णांक idx = iwl_txq_get_cmd_index(txq, txq->पढ़ो_ptr);
	काष्ठा sk_buff *skb;

	lockdep_निश्चित_held(&txq->lock);

	अगर (!txq->entries)
		वापस;

	iwl_txq_gen2_tfd_unmap(trans, &txq->entries[idx].meta,
			       iwl_txq_get_tfd(trans, txq, idx));

	skb = txq->entries[idx].skb;

	/* Can be called from irqs-disabled context
	 * If skb is not शून्य, it means that the whole queue is being
	 * मुक्तd and that the queue is not empty - मुक्त the skb
	 */
	अगर (skb) अणु
		iwl_op_mode_मुक्त_skb(trans->op_mode, skb);
		txq->entries[idx].skb = शून्य;
	पूर्ण
पूर्ण

पूर्णांक iwl_txq_gen2_set_tb(काष्ठा iwl_trans *trans, काष्ठा iwl_tfh_tfd *tfd,
			dma_addr_t addr, u16 len)
अणु
	पूर्णांक idx = iwl_txq_gen2_get_num_tbs(trans, tfd);
	काष्ठा iwl_tfh_tb *tb;

	/*
	 * Only WARN here so we know about the issue, but we mess up our
	 * unmap path because not every place currently checks क्रम errors
	 * वापसed from this function - it can only वापस an error अगर
	 * there's no more space, and so when we know there is enough we
	 * करोn't always check ...
	 */
	WARN(iwl_txq_crosses_4g_boundary(addr, len),
	     "possible DMA problem with iova:0x%llx, len:%d\n",
	     (अचिन्हित दीर्घ दीर्घ)addr, len);

	अगर (WARN_ON(idx >= IWL_TFH_NUM_TBS))
		वापस -EINVAL;
	tb = &tfd->tbs[idx];

	/* Each TFD can poपूर्णांक to a maximum max_tbs Tx buffers */
	अगर (le16_to_cpu(tfd->num_tbs) >= trans->txqs.tfd.max_tbs) अणु
		IWL_ERR(trans, "Error can not send more than %d chunks\n",
			trans->txqs.tfd.max_tbs);
		वापस -EINVAL;
	पूर्ण

	put_unaligned_le64(addr, &tb->addr);
	tb->tb_len = cpu_to_le16(len);

	tfd->num_tbs = cpu_to_le16(idx + 1);

	वापस idx;
पूर्ण

अटल काष्ठा page *get_workaround_page(काष्ठा iwl_trans *trans,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा page **page_ptr;
	काष्ठा page *ret;

	page_ptr = (व्योम *)((u8 *)skb->cb + trans->txqs.page_offs);

	ret = alloc_page(GFP_ATOMIC);
	अगर (!ret)
		वापस शून्य;

	/* set the chaining poपूर्णांकer to the previous page अगर there */
	*(व्योम **)(page_address(ret) + PAGE_SIZE - माप(व्योम *)) = *page_ptr;
	*page_ptr = ret;

	वापस ret;
पूर्ण

/*
 * Add a TB and अगर needed apply the FH HW bug workaround;
 * meta != शून्य indicates that it's a page mapping and we
 * need to dma_unmap_page() and set the meta->tbs bit in
 * this हाल.
 */
अटल पूर्णांक iwl_txq_gen2_set_tb_with_wa(काष्ठा iwl_trans *trans,
				       काष्ठा sk_buff *skb,
				       काष्ठा iwl_tfh_tfd *tfd,
				       dma_addr_t phys, व्योम *virt,
				       u16 len, काष्ठा iwl_cmd_meta *meta)
अणु
	dma_addr_t oldphys = phys;
	काष्ठा page *page;
	पूर्णांक ret;

	अगर (unlikely(dma_mapping_error(trans->dev, phys)))
		वापस -ENOMEM;

	अगर (likely(!iwl_txq_crosses_4g_boundary(phys, len))) अणु
		ret = iwl_txq_gen2_set_tb(trans, tfd, phys, len);

		अगर (ret < 0)
			जाओ unmap;

		अगर (meta)
			meta->tbs |= BIT(ret);

		ret = 0;
		जाओ trace;
	पूर्ण

	/*
	 * Work around a hardware bug. If (as expressed in the
	 * condition above) the TB ends on a 32-bit boundary,
	 * then the next TB may be accessed with the wrong
	 * address.
	 * To work around it, copy the data अन्यथाwhere and make
	 * a new mapping क्रम it so the device will not fail.
	 */

	अगर (WARN_ON(len > PAGE_SIZE - माप(व्योम *))) अणु
		ret = -ENOBUFS;
		जाओ unmap;
	पूर्ण

	page = get_workaround_page(trans, skb);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण

	स_नकल(page_address(page), virt, len);

	phys = dma_map_single(trans->dev, page_address(page), len,
			      DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(trans->dev, phys)))
		वापस -ENOMEM;
	ret = iwl_txq_gen2_set_tb(trans, tfd, phys, len);
	अगर (ret < 0) अणु
		/* unmap the new allocation as single */
		oldphys = phys;
		meta = शून्य;
		जाओ unmap;
	पूर्ण
	IWL_WARN(trans,
		 "TB bug workaround: copied %d bytes from 0x%llx to 0x%llx\n",
		 len, (अचिन्हित दीर्घ दीर्घ)oldphys, (अचिन्हित दीर्घ दीर्घ)phys);

	ret = 0;
unmap:
	अगर (meta)
		dma_unmap_page(trans->dev, oldphys, len, DMA_TO_DEVICE);
	अन्यथा
		dma_unmap_single(trans->dev, oldphys, len, DMA_TO_DEVICE);
trace:
	trace_iwlwअगरi_dev_tx_tb(trans->dev, skb, virt, phys, len);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_INET
काष्ठा iwl_tso_hdr_page *get_page_hdr(काष्ठा iwl_trans *trans, माप_प्रकार len,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा iwl_tso_hdr_page *p = this_cpu_ptr(trans->txqs.tso_hdr_page);
	काष्ठा page **page_ptr;

	page_ptr = (व्योम *)((u8 *)skb->cb + trans->txqs.page_offs);

	अगर (WARN_ON(*page_ptr))
		वापस शून्य;

	अगर (!p->page)
		जाओ alloc;

	/*
	 * Check अगर there's enough room on this page
	 *
	 * Note that we put a page chaining poपूर्णांकer *last* in the
	 * page - we need it somewhere, and अगर it's there then we
	 * aव्योम DMA mapping the last bits of the page which may
	 * trigger the 32-bit boundary hardware bug.
	 *
	 * (see also get_workaround_page() in tx-gen2.c)
	 */
	अगर (p->pos + len < (u8 *)page_address(p->page) + PAGE_SIZE -
			   माप(व्योम *))
		जाओ out;

	/* We करोn't have enough room on this page, get a new one. */
	__मुक्त_page(p->page);

alloc:
	p->page = alloc_page(GFP_ATOMIC);
	अगर (!p->page)
		वापस शून्य;
	p->pos = page_address(p->page);
	/* set the chaining poपूर्णांकer to शून्य */
	*(व्योम **)(page_address(p->page) + PAGE_SIZE - माप(व्योम *)) = शून्य;
out:
	*page_ptr = p->page;
	get_page(p->page);
	वापस p;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक iwl_txq_gen2_build_amsdu(काष्ठा iwl_trans *trans,
				    काष्ठा sk_buff *skb,
				    काष्ठा iwl_tfh_tfd *tfd, पूर्णांक start_len,
				    u8 hdr_len,
				    काष्ठा iwl_device_tx_cmd *dev_cmd)
अणु
#अगर_घोषित CONFIG_INET
	काष्ठा iwl_tx_cmd_gen2 *tx_cmd = (व्योम *)dev_cmd->payload;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	अचिन्हित पूर्णांक snap_ip_tcp_hdrlen, ip_hdrlen, total_len, hdr_room;
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;
	u16 length, amsdu_pad;
	u8 *start_hdr;
	काष्ठा iwl_tso_hdr_page *hdr_page;
	काष्ठा tso_t tso;

	trace_iwlwअगरi_dev_tx(trans->dev, skb, tfd, माप(*tfd),
			     &dev_cmd->hdr, start_len, 0);

	ip_hdrlen = skb_transport_header(skb) - skb_network_header(skb);
	snap_ip_tcp_hdrlen = 8 + ip_hdrlen + tcp_hdrlen(skb);
	total_len = skb->len - snap_ip_tcp_hdrlen - hdr_len;
	amsdu_pad = 0;

	/* total amount of header we may need क्रम this A-MSDU */
	hdr_room = DIV_ROUND_UP(total_len, mss) *
		(3 + snap_ip_tcp_hdrlen + माप(काष्ठा ethhdr));

	/* Our device supports 9 segments at most, it will fit in 1 page */
	hdr_page = get_page_hdr(trans, hdr_room, skb);
	अगर (!hdr_page)
		वापस -ENOMEM;

	start_hdr = hdr_page->pos;

	/*
	 * Pull the ieee80211 header to be able to use TSO core,
	 * we will restore it क्रम the tx_status flow.
	 */
	skb_pull(skb, hdr_len);

	/*
	 * Remove the length of all the headers that we करोn't actually
	 * have in the MPDU by themselves, but that we duplicate पूर्णांकo
	 * all the dअगरferent MSDUs inside the A-MSDU.
	 */
	le16_add_cpu(&tx_cmd->len, -snap_ip_tcp_hdrlen);

	tso_start(skb, &tso);

	जबतक (total_len) अणु
		/* this is the data left क्रम this subframe */
		अचिन्हित पूर्णांक data_left = min_t(अचिन्हित पूर्णांक, mss, total_len);
		अचिन्हित पूर्णांक tb_len;
		dma_addr_t tb_phys;
		u8 *subf_hdrs_start = hdr_page->pos;

		total_len -= data_left;

		स_रखो(hdr_page->pos, 0, amsdu_pad);
		hdr_page->pos += amsdu_pad;
		amsdu_pad = (4 - (माप(काष्ठा ethhdr) + snap_ip_tcp_hdrlen +
				  data_left)) & 0x3;
		ether_addr_copy(hdr_page->pos, ieee80211_get_DA(hdr));
		hdr_page->pos += ETH_ALEN;
		ether_addr_copy(hdr_page->pos, ieee80211_get_SA(hdr));
		hdr_page->pos += ETH_ALEN;

		length = snap_ip_tcp_hdrlen + data_left;
		*((__be16 *)hdr_page->pos) = cpu_to_be16(length);
		hdr_page->pos += माप(length);

		/*
		 * This will copy the SNAP as well which will be considered
		 * as MAC header.
		 */
		tso_build_hdr(skb, hdr_page->pos, &tso, data_left, !total_len);

		hdr_page->pos += snap_ip_tcp_hdrlen;

		tb_len = hdr_page->pos - start_hdr;
		tb_phys = dma_map_single(trans->dev, start_hdr,
					 tb_len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(trans->dev, tb_phys)))
			जाओ out_err;
		/*
		 * No need क्रम _with_wa, this is from the TSO page and
		 * we leave some space at the end of it so can't hit
		 * the buggy scenario.
		 */
		iwl_txq_gen2_set_tb(trans, tfd, tb_phys, tb_len);
		trace_iwlwअगरi_dev_tx_tb(trans->dev, skb, start_hdr,
					tb_phys, tb_len);
		/* add this subframe's headers' length to the tx_cmd */
		le16_add_cpu(&tx_cmd->len, hdr_page->pos - subf_hdrs_start);

		/* prepare the start_hdr क्रम the next subframe */
		start_hdr = hdr_page->pos;

		/* put the payload */
		जबतक (data_left) अणु
			पूर्णांक ret;

			tb_len = min_t(अचिन्हित पूर्णांक, tso.size, data_left);
			tb_phys = dma_map_single(trans->dev, tso.data,
						 tb_len, DMA_TO_DEVICE);
			ret = iwl_txq_gen2_set_tb_with_wa(trans, skb, tfd,
							  tb_phys, tso.data,
							  tb_len, शून्य);
			अगर (ret)
				जाओ out_err;

			data_left -= tb_len;
			tso_build_data(skb, &tso, tb_len);
		पूर्ण
	पूर्ण

	/* re -add the WiFi header */
	skb_push(skb, hdr_len);

	वापस 0;

out_err:
#पूर्ण_अगर
	वापस -EINVAL;
पूर्ण

अटल काष्ठा
iwl_tfh_tfd *iwl_txq_gen2_build_tx_amsdu(काष्ठा iwl_trans *trans,
					 काष्ठा iwl_txq *txq,
					 काष्ठा iwl_device_tx_cmd *dev_cmd,
					 काष्ठा sk_buff *skb,
					 काष्ठा iwl_cmd_meta *out_meta,
					 पूर्णांक hdr_len,
					 पूर्णांक tx_cmd_len)
अणु
	पूर्णांक idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);
	काष्ठा iwl_tfh_tfd *tfd = iwl_txq_get_tfd(trans, txq, idx);
	dma_addr_t tb_phys;
	पूर्णांक len;
	व्योम *tb1_addr;

	tb_phys = iwl_txq_get_first_tb_dma(txq, idx);

	/*
	 * No need क्रम _with_wa, the first TB allocation is aligned up
	 * to a 64-byte boundary and thus can't be at the end or cross
	 * a page boundary (much less a 2^32 boundary).
	 */
	iwl_txq_gen2_set_tb(trans, tfd, tb_phys, IWL_FIRST_TB_SIZE);

	/*
	 * The second TB (tb1) poपूर्णांकs to the reमुख्यder of the TX command
	 * and the 802.11 header - dword aligned size
	 * (This calculation modअगरies the TX command, so करो it beक्रमe the
	 * setup of the first TB)
	 */
	len = tx_cmd_len + माप(काष्ठा iwl_cmd_header) + hdr_len -
	      IWL_FIRST_TB_SIZE;

	/* करो not align A-MSDU to dword as the subframe header aligns it */

	/* map the data क्रम TB1 */
	tb1_addr = ((u8 *)&dev_cmd->hdr) + IWL_FIRST_TB_SIZE;
	tb_phys = dma_map_single(trans->dev, tb1_addr, len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(trans->dev, tb_phys)))
		जाओ out_err;
	/*
	 * No need क्रम _with_wa(), we ensure (via alignment) that the data
	 * here can never cross or end at a page boundary.
	 */
	iwl_txq_gen2_set_tb(trans, tfd, tb_phys, len);

	अगर (iwl_txq_gen2_build_amsdu(trans, skb, tfd, len + IWL_FIRST_TB_SIZE,
				     hdr_len, dev_cmd))
		जाओ out_err;

	/* building the A-MSDU might have changed this data, स_नकल it now */
	स_नकल(&txq->first_tb_bufs[idx], dev_cmd, IWL_FIRST_TB_SIZE);
	वापस tfd;

out_err:
	iwl_txq_gen2_tfd_unmap(trans, out_meta, tfd);
	वापस शून्य;
पूर्ण

अटल पूर्णांक iwl_txq_gen2_tx_add_frags(काष्ठा iwl_trans *trans,
				     काष्ठा sk_buff *skb,
				     काष्ठा iwl_tfh_tfd *tfd,
				     काष्ठा iwl_cmd_meta *out_meta)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		dma_addr_t tb_phys;
		अचिन्हित पूर्णांक fragsz = skb_frag_size(frag);
		पूर्णांक ret;

		अगर (!fragsz)
			जारी;

		tb_phys = skb_frag_dma_map(trans->dev, frag, 0,
					   fragsz, DMA_TO_DEVICE);
		ret = iwl_txq_gen2_set_tb_with_wa(trans, skb, tfd, tb_phys,
						  skb_frag_address(frag),
						  fragsz, out_meta);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा
iwl_tfh_tfd *iwl_txq_gen2_build_tx(काष्ठा iwl_trans *trans,
				   काष्ठा iwl_txq *txq,
				   काष्ठा iwl_device_tx_cmd *dev_cmd,
				   काष्ठा sk_buff *skb,
				   काष्ठा iwl_cmd_meta *out_meta,
				   पूर्णांक hdr_len,
				   पूर्णांक tx_cmd_len,
				   bool pad)
अणु
	पूर्णांक idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);
	काष्ठा iwl_tfh_tfd *tfd = iwl_txq_get_tfd(trans, txq, idx);
	dma_addr_t tb_phys;
	पूर्णांक len, tb1_len, tb2_len;
	व्योम *tb1_addr;
	काष्ठा sk_buff *frag;

	tb_phys = iwl_txq_get_first_tb_dma(txq, idx);

	/* The first TB poपूर्णांकs to bi-directional DMA data */
	स_नकल(&txq->first_tb_bufs[idx], dev_cmd, IWL_FIRST_TB_SIZE);

	/*
	 * No need क्रम _with_wa, the first TB allocation is aligned up
	 * to a 64-byte boundary and thus can't be at the end or cross
	 * a page boundary (much less a 2^32 boundary).
	 */
	iwl_txq_gen2_set_tb(trans, tfd, tb_phys, IWL_FIRST_TB_SIZE);

	/*
	 * The second TB (tb1) poपूर्णांकs to the reमुख्यder of the TX command
	 * and the 802.11 header - dword aligned size
	 * (This calculation modअगरies the TX command, so करो it beक्रमe the
	 * setup of the first TB)
	 */
	len = tx_cmd_len + माप(काष्ठा iwl_cmd_header) + hdr_len -
	      IWL_FIRST_TB_SIZE;

	अगर (pad)
		tb1_len = ALIGN(len, 4);
	अन्यथा
		tb1_len = len;

	/* map the data क्रम TB1 */
	tb1_addr = ((u8 *)&dev_cmd->hdr) + IWL_FIRST_TB_SIZE;
	tb_phys = dma_map_single(trans->dev, tb1_addr, tb1_len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(trans->dev, tb_phys)))
		जाओ out_err;
	/*
	 * No need क्रम _with_wa(), we ensure (via alignment) that the data
	 * here can never cross or end at a page boundary.
	 */
	iwl_txq_gen2_set_tb(trans, tfd, tb_phys, tb1_len);
	trace_iwlwअगरi_dev_tx(trans->dev, skb, tfd, माप(*tfd), &dev_cmd->hdr,
			     IWL_FIRST_TB_SIZE + tb1_len, hdr_len);

	/* set up TFD's third entry to point to remainder of skb's head */
	tb2_len = skb_headlen(skb) - hdr_len;

	अगर (tb2_len > 0) अणु
		पूर्णांक ret;

		tb_phys = dma_map_single(trans->dev, skb->data + hdr_len,
					 tb2_len, DMA_TO_DEVICE);
		ret = iwl_txq_gen2_set_tb_with_wa(trans, skb, tfd, tb_phys,
						  skb->data + hdr_len, tb2_len,
						  शून्य);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (iwl_txq_gen2_tx_add_frags(trans, skb, tfd, out_meta))
		जाओ out_err;

	skb_walk_frags(skb, frag) अणु
		पूर्णांक ret;

		tb_phys = dma_map_single(trans->dev, frag->data,
					 skb_headlen(frag), DMA_TO_DEVICE);
		ret = iwl_txq_gen2_set_tb_with_wa(trans, skb, tfd, tb_phys,
						  frag->data,
						  skb_headlen(frag), शून्य);
		अगर (ret)
			जाओ out_err;
		अगर (iwl_txq_gen2_tx_add_frags(trans, frag, tfd, out_meta))
			जाओ out_err;
	पूर्ण

	वापस tfd;

out_err:
	iwl_txq_gen2_tfd_unmap(trans, out_meta, tfd);
	वापस शून्य;
पूर्ण

अटल
काष्ठा iwl_tfh_tfd *iwl_txq_gen2_build_tfd(काष्ठा iwl_trans *trans,
					   काष्ठा iwl_txq *txq,
					   काष्ठा iwl_device_tx_cmd *dev_cmd,
					   काष्ठा sk_buff *skb,
					   काष्ठा iwl_cmd_meta *out_meta)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	पूर्णांक idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);
	काष्ठा iwl_tfh_tfd *tfd = iwl_txq_get_tfd(trans, txq, idx);
	पूर्णांक len, hdr_len;
	bool amsdu;

	/* There must be data left over क्रम TB1 or this code must be changed */
	BUILD_BUG_ON(माप(काष्ठा iwl_tx_cmd_gen2) < IWL_FIRST_TB_SIZE);

	स_रखो(tfd, 0, माप(*tfd));

	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		len = माप(काष्ठा iwl_tx_cmd_gen2);
	अन्यथा
		len = माप(काष्ठा iwl_tx_cmd_gen3);

	amsdu = ieee80211_is_data_qos(hdr->frame_control) &&
			(*ieee80211_get_qos_ctl(hdr) &
			 IEEE80211_QOS_CTL_A_MSDU_PRESENT);

	hdr_len = ieee80211_hdrlen(hdr->frame_control);

	/*
	 * Only build A-MSDUs here अगर करोing so by GSO, otherwise it may be
	 * an A-MSDU क्रम other reasons, e.g. न_अंक or an A-MSDU having been
	 * built in the higher layers alपढ़ोy.
	 */
	अगर (amsdu && skb_shinfo(skb)->gso_size)
		वापस iwl_txq_gen2_build_tx_amsdu(trans, txq, dev_cmd, skb,
						    out_meta, hdr_len, len);
	वापस iwl_txq_gen2_build_tx(trans, txq, dev_cmd, skb, out_meta,
				      hdr_len, len, !amsdu);
पूर्ण

पूर्णांक iwl_txq_space(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_txq *q)
अणु
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक used;

	/*
	 * To aव्योम ambiguity between empty and completely full queues, there
	 * should always be less than max_tfd_queue_size elements in the queue.
	 * If q->n_winकरोw is smaller than max_tfd_queue_size, there is no need
	 * to reserve any queue entries क्रम this purpose.
	 */
	अगर (q->n_winकरोw < trans->trans_cfg->base_params->max_tfd_queue_size)
		max = q->n_winकरोw;
	अन्यथा
		max = trans->trans_cfg->base_params->max_tfd_queue_size - 1;

	/*
	 * max_tfd_queue_size is a घातer of 2, so the following is equivalent to
	 * modulo by max_tfd_queue_size and is well defined.
	 */
	used = (q->ग_लिखो_ptr - q->पढ़ो_ptr) &
		(trans->trans_cfg->base_params->max_tfd_queue_size - 1);

	अगर (WARN_ON(used > max))
		वापस 0;

	वापस max - used;
पूर्ण

पूर्णांक iwl_txq_gen2_tx(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
		    काष्ठा iwl_device_tx_cmd *dev_cmd, पूर्णांक txq_id)
अणु
	काष्ठा iwl_cmd_meta *out_meta;
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];
	u16 cmd_len;
	पूर्णांक idx;
	व्योम *tfd;

	अगर (WARN_ONCE(txq_id >= IWL_MAX_TVQM_QUEUES,
		      "queue %d out of range", txq_id))
		वापस -EINVAL;

	अगर (WARN_ONCE(!test_bit(txq_id, trans->txqs.queue_used),
		      "TX on unused queue %d\n", txq_id))
		वापस -EINVAL;

	अगर (skb_is_nonlinear(skb) &&
	    skb_shinfo(skb)->nr_frags > IWL_TRANS_MAX_FRAGS(trans) &&
	    __skb_linearize(skb))
		वापस -ENOMEM;

	spin_lock(&txq->lock);

	अगर (iwl_txq_space(trans, txq) < txq->high_mark) अणु
		iwl_txq_stop(trans, txq);

		/* करोn't put the packet on the ring, अगर there is no room */
		अगर (unlikely(iwl_txq_space(trans, txq) < 3)) अणु
			काष्ठा iwl_device_tx_cmd **dev_cmd_ptr;

			dev_cmd_ptr = (व्योम *)((u8 *)skb->cb +
					       trans->txqs.dev_cmd_offs);

			*dev_cmd_ptr = dev_cmd;
			__skb_queue_tail(&txq->overflow_q, skb);
			spin_unlock(&txq->lock);
			वापस 0;
		पूर्ण
	पूर्ण

	idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);

	/* Set up driver data क्रम this TFD */
	txq->entries[idx].skb = skb;
	txq->entries[idx].cmd = dev_cmd;

	dev_cmd->hdr.sequence =
		cpu_to_le16((u16)(QUEUE_TO_SEQ(txq_id) |
			    INDEX_TO_SEQ(idx)));

	/* Set up first empty entry in queue's array of Tx/cmd buffers */
	out_meta = &txq->entries[idx].meta;
	out_meta->flags = 0;

	tfd = iwl_txq_gen2_build_tfd(trans, txq, dev_cmd, skb, out_meta);
	अगर (!tfd) अणु
		spin_unlock(&txq->lock);
		वापस -1;
	पूर्ण

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		काष्ठा iwl_tx_cmd_gen3 *tx_cmd_gen3 =
			(व्योम *)dev_cmd->payload;

		cmd_len = le16_to_cpu(tx_cmd_gen3->len);
	पूर्ण अन्यथा अणु
		काष्ठा iwl_tx_cmd_gen2 *tx_cmd_gen2 =
			(व्योम *)dev_cmd->payload;

		cmd_len = le16_to_cpu(tx_cmd_gen2->len);
	पूर्ण

	/* Set up entry क्रम this TFD in Tx byte-count array */
	iwl_pcie_gen2_update_byte_tbl(trans, txq, cmd_len,
				      iwl_txq_gen2_get_num_tbs(trans, tfd));

	/* start समयr अगर queue currently empty */
	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr && txq->wd_समयout)
		mod_समयr(&txq->stuck_समयr, jअगरfies + txq->wd_समयout);

	/* Tell device the ग_लिखो index *just past* this latest filled TFD */
	txq->ग_लिखो_ptr = iwl_txq_inc_wrap(trans, txq->ग_लिखो_ptr);
	iwl_txq_inc_wr_ptr(trans, txq);
	/*
	 * At this poपूर्णांक the frame is "transmitted" successfully
	 * and we will get a TX status notअगरication eventually.
	 */
	spin_unlock(&txq->lock);
	वापस 0;
पूर्ण

/*************** HOST COMMAND QUEUE FUNCTIONS   *****/

/*
 * iwl_txq_gen2_unmap -  Unmap any reमुख्यing DMA mappings and मुक्त skb's
 */
व्योम iwl_txq_gen2_unmap(काष्ठा iwl_trans *trans, पूर्णांक txq_id)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];

	spin_lock_bh(&txq->lock);
	जबतक (txq->ग_लिखो_ptr != txq->पढ़ो_ptr) अणु
		IWL_DEBUG_TX_REPLY(trans, "Q %d Free %d\n",
				   txq_id, txq->पढ़ो_ptr);

		अगर (txq_id != trans->txqs.cmd.q_id) अणु
			पूर्णांक idx = iwl_txq_get_cmd_index(txq, txq->पढ़ो_ptr);
			काष्ठा sk_buff *skb = txq->entries[idx].skb;

			अगर (!WARN_ON_ONCE(!skb))
				iwl_txq_मुक्त_tso_page(trans, skb);
		पूर्ण
		iwl_txq_gen2_मुक्त_tfd(trans, txq);
		txq->पढ़ो_ptr = iwl_txq_inc_wrap(trans, txq->पढ़ो_ptr);
	पूर्ण

	जबतक (!skb_queue_empty(&txq->overflow_q)) अणु
		काष्ठा sk_buff *skb = __skb_dequeue(&txq->overflow_q);

		iwl_op_mode_मुक्त_skb(trans->op_mode, skb);
	पूर्ण

	spin_unlock_bh(&txq->lock);

	/* just in हाल - this queue may have been stopped */
	iwl_wake_queue(trans, txq);
पूर्ण

अटल व्योम iwl_txq_gen2_मुक्त_memory(काष्ठा iwl_trans *trans,
				     काष्ठा iwl_txq *txq)
अणु
	काष्ठा device *dev = trans->dev;

	/* De-alloc circular buffer of TFDs */
	अगर (txq->tfds) अणु
		dma_मुक्त_coherent(dev,
				  trans->txqs.tfd.size * txq->n_winकरोw,
				  txq->tfds, txq->dma_addr);
		dma_मुक्त_coherent(dev,
				  माप(*txq->first_tb_bufs) * txq->n_winकरोw,
				  txq->first_tb_bufs, txq->first_tb_dma);
	पूर्ण

	kमुक्त(txq->entries);
	अगर (txq->bc_tbl.addr)
		dma_pool_मुक्त(trans->txqs.bc_pool,
			      txq->bc_tbl.addr, txq->bc_tbl.dma);
	kमुक्त(txq);
पूर्ण

/*
 * iwl_pcie_txq_मुक्त - Deallocate DMA queue.
 * @txq: Transmit queue to deallocate.
 *
 * Empty queue by removing and destroying all BD's.
 * Free all buffers.
 * 0-fill, but करो not मुक्त "txq" descriptor काष्ठाure.
 */
अटल व्योम iwl_txq_gen2_मुक्त(काष्ठा iwl_trans *trans, पूर्णांक txq_id)
अणु
	काष्ठा iwl_txq *txq;
	पूर्णांक i;

	अगर (WARN_ONCE(txq_id >= IWL_MAX_TVQM_QUEUES,
		      "queue %d out of range", txq_id))
		वापस;

	txq = trans->txqs.txq[txq_id];

	अगर (WARN_ON(!txq))
		वापस;

	iwl_txq_gen2_unmap(trans, txq_id);

	/* De-alloc array of command/tx buffers */
	अगर (txq_id == trans->txqs.cmd.q_id)
		क्रम (i = 0; i < txq->n_winकरोw; i++) अणु
			kमुक्त_sensitive(txq->entries[i].cmd);
			kमुक्त_sensitive(txq->entries[i].मुक्त_buf);
		पूर्ण
	del_समयr_sync(&txq->stuck_समयr);

	iwl_txq_gen2_मुक्त_memory(trans, txq);

	trans->txqs.txq[txq_id] = शून्य;

	clear_bit(txq_id, trans->txqs.queue_used);
पूर्ण

/*
 * iwl_queue_init - Initialize queue's high/low-water and पढ़ो/ग_लिखो indexes
 */
अटल पूर्णांक iwl_queue_init(काष्ठा iwl_txq *q, पूर्णांक slots_num)
अणु
	q->n_winकरोw = slots_num;

	/* slots_num must be घातer-of-two size, otherwise
	 * iwl_txq_get_cmd_index is broken. */
	अगर (WARN_ON(!is_घातer_of_2(slots_num)))
		वापस -EINVAL;

	q->low_mark = q->n_winकरोw / 4;
	अगर (q->low_mark < 4)
		q->low_mark = 4;

	q->high_mark = q->n_winकरोw / 8;
	अगर (q->high_mark < 2)
		q->high_mark = 2;

	q->ग_लिखो_ptr = 0;
	q->पढ़ो_ptr = 0;

	वापस 0;
पूर्ण

पूर्णांक iwl_txq_init(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq, पूर्णांक slots_num,
		 bool cmd_queue)
अणु
	पूर्णांक ret;
	u32 tfd_queue_max_size =
		trans->trans_cfg->base_params->max_tfd_queue_size;

	txq->need_update = false;

	/* max_tfd_queue_size must be घातer-of-two size, otherwise
	 * iwl_txq_inc_wrap and iwl_txq_dec_wrap are broken. */
	अगर (WARN_ONCE(tfd_queue_max_size & (tfd_queue_max_size - 1),
		      "Max tfd queue size must be a power of two, but is %d",
		      tfd_queue_max_size))
		वापस -EINVAL;

	/* Initialize queue's high/low-water marks, and head/tail indexes */
	ret = iwl_queue_init(txq, slots_num);
	अगर (ret)
		वापस ret;

	spin_lock_init(&txq->lock);

	अगर (cmd_queue) अणु
		अटल काष्ठा lock_class_key iwl_txq_cmd_queue_lock_class;

		lockdep_set_class(&txq->lock, &iwl_txq_cmd_queue_lock_class);
	पूर्ण

	__skb_queue_head_init(&txq->overflow_q);

	वापस 0;
पूर्ण

व्योम iwl_txq_मुक्त_tso_page(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb)
अणु
	काष्ठा page **page_ptr;
	काष्ठा page *next;

	page_ptr = (व्योम *)((u8 *)skb->cb + trans->txqs.page_offs);
	next = *page_ptr;
	*page_ptr = शून्य;

	जबतक (next) अणु
		काष्ठा page *पंचांगp = next;

		next = *(व्योम **)(page_address(next) + PAGE_SIZE -
				  माप(व्योम *));
		__मुक्त_page(पंचांगp);
	पूर्ण
पूर्ण

व्योम iwl_txq_log_scd_error(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq)
अणु
	u32 txq_id = txq->id;
	u32 status;
	bool active;
	u8 fअगरo;

	अगर (trans->trans_cfg->use_tfh) अणु
		IWL_ERR(trans, "Queue %d is stuck %d %d\n", txq_id,
			txq->पढ़ो_ptr, txq->ग_लिखो_ptr);
		/* TODO: access new SCD रेजिस्टरs and dump them */
		वापस;
	पूर्ण

	status = iwl_पढ़ो_prph(trans, SCD_QUEUE_STATUS_BITS(txq_id));
	fअगरo = (status >> SCD_QUEUE_STTS_REG_POS_TXF) & 0x7;
	active = !!(status & BIT(SCD_QUEUE_STTS_REG_POS_ACTIVE));

	IWL_ERR(trans,
		"Queue %d is %sactive on fifo %d and stuck for %u ms. SW [%d, %d] HW [%d, %d] FH TRB=0x0%x\n",
		txq_id, active ? "" : "in", fअगरo,
		jअगरfies_to_msecs(txq->wd_समयout),
		txq->पढ़ो_ptr, txq->ग_लिखो_ptr,
		iwl_पढ़ो_prph(trans, SCD_QUEUE_RDPTR(txq_id)) &
			(trans->trans_cfg->base_params->max_tfd_queue_size - 1),
			iwl_पढ़ो_prph(trans, SCD_QUEUE_WRPTR(txq_id)) &
			(trans->trans_cfg->base_params->max_tfd_queue_size - 1),
			iwl_पढ़ो_direct32(trans, FH_TX_TRB_REG(fअगरo)));
पूर्ण

अटल व्योम iwl_txq_stuck_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_txq *txq = from_समयr(txq, t, stuck_समयr);
	काष्ठा iwl_trans *trans = txq->trans;

	spin_lock(&txq->lock);
	/* check अगर triggered erroneously */
	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr) अणु
		spin_unlock(&txq->lock);
		वापस;
	पूर्ण
	spin_unlock(&txq->lock);

	iwl_txq_log_scd_error(trans, txq);

	iwl_क्रमce_nmi(trans);
पूर्ण

पूर्णांक iwl_txq_alloc(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq, पूर्णांक slots_num,
		  bool cmd_queue)
अणु
	माप_प्रकार tfd_sz = trans->txqs.tfd.size *
		trans->trans_cfg->base_params->max_tfd_queue_size;
	माप_प्रकार tb0_buf_sz;
	पूर्णांक i;

	अगर (WARN_ON(txq->entries || txq->tfds))
		वापस -EINVAL;

	अगर (trans->trans_cfg->use_tfh)
		tfd_sz = trans->txqs.tfd.size * slots_num;

	समयr_setup(&txq->stuck_समयr, iwl_txq_stuck_समयr, 0);
	txq->trans = trans;

	txq->n_winकरोw = slots_num;

	txq->entries = kसुस्मृति(slots_num,
			       माप(काष्ठा iwl_pcie_txq_entry),
			       GFP_KERNEL);

	अगर (!txq->entries)
		जाओ error;

	अगर (cmd_queue)
		क्रम (i = 0; i < slots_num; i++) अणु
			txq->entries[i].cmd =
				kदो_स्मृति(माप(काष्ठा iwl_device_cmd),
					GFP_KERNEL);
			अगर (!txq->entries[i].cmd)
				जाओ error;
		पूर्ण

	/* Circular buffer of transmit frame descriptors (TFDs),
	 * shared with device */
	txq->tfds = dma_alloc_coherent(trans->dev, tfd_sz,
				       &txq->dma_addr, GFP_KERNEL);
	अगर (!txq->tfds)
		जाओ error;

	BUILD_BUG_ON(माप(*txq->first_tb_bufs) != IWL_FIRST_TB_SIZE_ALIGN);

	tb0_buf_sz = माप(*txq->first_tb_bufs) * slots_num;

	txq->first_tb_bufs = dma_alloc_coherent(trans->dev, tb0_buf_sz,
						&txq->first_tb_dma,
						GFP_KERNEL);
	अगर (!txq->first_tb_bufs)
		जाओ err_मुक्त_tfds;

	वापस 0;
err_मुक्त_tfds:
	dma_मुक्त_coherent(trans->dev, tfd_sz, txq->tfds, txq->dma_addr);
error:
	अगर (txq->entries && cmd_queue)
		क्रम (i = 0; i < slots_num; i++)
			kमुक्त(txq->entries[i].cmd);
	kमुक्त(txq->entries);
	txq->entries = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक iwl_txq_dyn_alloc_dma(काष्ठा iwl_trans *trans,
				 काष्ठा iwl_txq **पूर्णांकxq, पूर्णांक size,
				 अचिन्हित पूर्णांक समयout)
अणु
	माप_प्रकार bc_tbl_size, bc_tbl_entries;
	काष्ठा iwl_txq *txq;
	पूर्णांक ret;

	WARN_ON(!trans->txqs.bc_tbl_size);

	bc_tbl_size = trans->txqs.bc_tbl_size;
	bc_tbl_entries = bc_tbl_size / माप(u16);

	अगर (WARN_ON(size > bc_tbl_entries))
		वापस -EINVAL;

	txq = kzalloc(माप(*txq), GFP_KERNEL);
	अगर (!txq)
		वापस -ENOMEM;

	txq->bc_tbl.addr = dma_pool_alloc(trans->txqs.bc_pool, GFP_KERNEL,
					  &txq->bc_tbl.dma);
	अगर (!txq->bc_tbl.addr) अणु
		IWL_ERR(trans, "Scheduler BC Table allocation failed\n");
		kमुक्त(txq);
		वापस -ENOMEM;
	पूर्ण

	ret = iwl_txq_alloc(trans, txq, size, false);
	अगर (ret) अणु
		IWL_ERR(trans, "Tx queue alloc failed\n");
		जाओ error;
	पूर्ण
	ret = iwl_txq_init(trans, txq, size, false);
	अगर (ret) अणु
		IWL_ERR(trans, "Tx queue init failed\n");
		जाओ error;
	पूर्ण

	txq->wd_समयout = msecs_to_jअगरfies(समयout);

	*पूर्णांकxq = txq;
	वापस 0;

error:
	iwl_txq_gen2_मुक्त_memory(trans, txq);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_txq_alloc_response(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq,
				  काष्ठा iwl_host_cmd *hcmd)
अणु
	काष्ठा iwl_tx_queue_cfg_rsp *rsp;
	पूर्णांक ret, qid;
	u32 wr_ptr;

	अगर (WARN_ON(iwl_rx_packet_payload_len(hcmd->resp_pkt) !=
		    माप(*rsp))) अणु
		ret = -EINVAL;
		जाओ error_मुक्त_resp;
	पूर्ण

	rsp = (व्योम *)hcmd->resp_pkt->data;
	qid = le16_to_cpu(rsp->queue_number);
	wr_ptr = le16_to_cpu(rsp->ग_लिखो_poपूर्णांकer);

	अगर (qid >= ARRAY_SIZE(trans->txqs.txq)) अणु
		WARN_ONCE(1, "queue index %d unsupported", qid);
		ret = -EIO;
		जाओ error_मुक्त_resp;
	पूर्ण

	अगर (test_and_set_bit(qid, trans->txqs.queue_used)) अणु
		WARN_ONCE(1, "queue %d already used", qid);
		ret = -EIO;
		जाओ error_मुक्त_resp;
	पूर्ण

	अगर (WARN_ONCE(trans->txqs.txq[qid],
		      "queue %d already allocated\n", qid)) अणु
		ret = -EIO;
		जाओ error_मुक्त_resp;
	पूर्ण

	txq->id = qid;
	trans->txqs.txq[qid] = txq;
	wr_ptr &= (trans->trans_cfg->base_params->max_tfd_queue_size - 1);

	/* Place first TFD at index corresponding to start sequence number */
	txq->पढ़ो_ptr = wr_ptr;
	txq->ग_लिखो_ptr = wr_ptr;

	IWL_DEBUG_TX_QUEUES(trans, "Activate queue %d\n", qid);

	iwl_मुक्त_resp(hcmd);
	वापस qid;

error_मुक्त_resp:
	iwl_मुक्त_resp(hcmd);
	iwl_txq_gen2_मुक्त_memory(trans, txq);
	वापस ret;
पूर्ण

पूर्णांक iwl_txq_dyn_alloc(काष्ठा iwl_trans *trans, __le16 flags, u8 sta_id, u8 tid,
		      पूर्णांक cmd_id, पूर्णांक size, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा iwl_txq *txq = शून्य;
	काष्ठा iwl_tx_queue_cfg_cmd cmd = अणु
		.flags = flags,
		.sta_id = sta_id,
		.tid = tid,
	पूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = cmd_id,
		.len = अणु माप(cmd) पूर्ण,
		.data = अणु &cmd, पूर्ण,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_txq_dyn_alloc_dma(trans, &txq, size, समयout);
	अगर (ret)
		वापस ret;

	cmd.tfdq_addr = cpu_to_le64(txq->dma_addr);
	cmd.byte_cnt_addr = cpu_to_le64(txq->bc_tbl.dma);
	cmd.cb_size = cpu_to_le32(TFD_QUEUE_CB_SIZE(size));

	ret = iwl_trans_send_cmd(trans, &hcmd);
	अगर (ret)
		जाओ error;

	वापस iwl_txq_alloc_response(trans, txq, &hcmd);

error:
	iwl_txq_gen2_मुक्त_memory(trans, txq);
	वापस ret;
पूर्ण

व्योम iwl_txq_dyn_मुक्त(काष्ठा iwl_trans *trans, पूर्णांक queue)
अणु
	अगर (WARN(queue >= IWL_MAX_TVQM_QUEUES,
		 "queue %d out of range", queue))
		वापस;

	/*
	 * Upon HW Rfसमाप्त - we stop the device, and then stop the queues
	 * in the op_mode. Just क्रम the sake of the simplicity of the op_mode,
	 * allow the op_mode to call txq_disable after it alपढ़ोy called
	 * stop_device.
	 */
	अगर (!test_and_clear_bit(queue, trans->txqs.queue_used)) अणु
		WARN_ONCE(test_bit(STATUS_DEVICE_ENABLED, &trans->status),
			  "queue %d not used", queue);
		वापस;
	पूर्ण

	iwl_txq_gen2_मुक्त(trans, queue);

	IWL_DEBUG_TX_QUEUES(trans, "Deactivate queue %d\n", queue);
पूर्ण

व्योम iwl_txq_gen2_tx_मुक्त(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक i;

	स_रखो(trans->txqs.queue_used, 0, माप(trans->txqs.queue_used));

	/* Free all TX queues */
	क्रम (i = 0; i < ARRAY_SIZE(trans->txqs.txq); i++) अणु
		अगर (!trans->txqs.txq[i])
			जारी;

		iwl_txq_gen2_मुक्त(trans, i);
	पूर्ण
पूर्ण

पूर्णांक iwl_txq_gen2_init(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक queue_size)
अणु
	काष्ठा iwl_txq *queue;
	पूर्णांक ret;

	/* alloc and init the tx queue */
	अगर (!trans->txqs.txq[txq_id]) अणु
		queue = kzalloc(माप(*queue), GFP_KERNEL);
		अगर (!queue) अणु
			IWL_ERR(trans, "Not enough memory for tx queue\n");
			वापस -ENOMEM;
		पूर्ण
		trans->txqs.txq[txq_id] = queue;
		ret = iwl_txq_alloc(trans, queue, queue_size, true);
		अगर (ret) अणु
			IWL_ERR(trans, "Tx %d queue init failed\n", txq_id);
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		queue = trans->txqs.txq[txq_id];
	पूर्ण

	ret = iwl_txq_init(trans, queue, queue_size,
			   (txq_id == trans->txqs.cmd.q_id));
	अगर (ret) अणु
		IWL_ERR(trans, "Tx %d queue alloc failed\n", txq_id);
		जाओ error;
	पूर्ण
	trans->txqs.txq[txq_id]->id = txq_id;
	set_bit(txq_id, trans->txqs.queue_used);

	वापस 0;

error:
	iwl_txq_gen2_tx_मुक्त(trans);
	वापस ret;
पूर्ण

अटल अंतरभूत dma_addr_t iwl_txq_gen1_tfd_tb_get_addr(काष्ठा iwl_trans *trans,
						      व्योम *_tfd, u8 idx)
अणु
	काष्ठा iwl_tfd *tfd;
	काष्ठा iwl_tfd_tb *tb;
	dma_addr_t addr;
	dma_addr_t hi_len;

	अगर (trans->trans_cfg->use_tfh) अणु
		काष्ठा iwl_tfh_tfd *tfd = _tfd;
		काष्ठा iwl_tfh_tb *tb = &tfd->tbs[idx];

		वापस (dma_addr_t)(le64_to_cpu(tb->addr));
	पूर्ण

	tfd = _tfd;
	tb = &tfd->tbs[idx];
	addr = get_unaligned_le32(&tb->lo);

	अगर (माप(dma_addr_t) <= माप(u32))
		वापस addr;

	hi_len = le16_to_cpu(tb->hi_n_len) & 0xF;

	/*
	 * shअगरt by 16 twice to aव्योम warnings on 32-bit
	 * (where this code never runs anyway due to the
	 * अगर statement above)
	 */
	वापस addr | ((hi_len << 16) << 16);
पूर्ण

व्योम iwl_txq_gen1_tfd_unmap(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_cmd_meta *meta,
			    काष्ठा iwl_txq *txq, पूर्णांक index)
अणु
	पूर्णांक i, num_tbs;
	व्योम *tfd = iwl_txq_get_tfd(trans, txq, index);

	/* Sanity check on number of chunks */
	num_tbs = iwl_txq_gen1_tfd_get_num_tbs(trans, tfd);

	अगर (num_tbs > trans->txqs.tfd.max_tbs) अणु
		IWL_ERR(trans, "Too many chunks: %i\n", num_tbs);
		/* @toकरो issue fatal error, it is quite serious situation */
		वापस;
	पूर्ण

	/* first TB is never मुक्तd - it's the bidirectional DMA data */

	क्रम (i = 1; i < num_tbs; i++) अणु
		अगर (meta->tbs & BIT(i))
			dma_unmap_page(trans->dev,
				       iwl_txq_gen1_tfd_tb_get_addr(trans,
								    tfd, i),
				       iwl_txq_gen1_tfd_tb_get_len(trans,
								   tfd, i),
				       DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(trans->dev,
					 iwl_txq_gen1_tfd_tb_get_addr(trans,
								      tfd, i),
					 iwl_txq_gen1_tfd_tb_get_len(trans,
								     tfd, i),
					 DMA_TO_DEVICE);
	पूर्ण

	meta->tbs = 0;

	अगर (trans->trans_cfg->use_tfh) अणु
		काष्ठा iwl_tfh_tfd *tfd_fh = (व्योम *)tfd;

		tfd_fh->num_tbs = 0;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_tfd *tfd_fh = (व्योम *)tfd;

		tfd_fh->num_tbs = 0;
	पूर्ण
पूर्ण

#घोषणा IWL_TX_CRC_SIZE 4
#घोषणा IWL_TX_DELIMITER_SIZE 4

/*
 * iwl_txq_gen1_update_byte_cnt_tbl - Set up entry in Tx byte-count array
 */
व्योम iwl_txq_gen1_update_byte_cnt_tbl(काष्ठा iwl_trans *trans,
				      काष्ठा iwl_txq *txq, u16 byte_cnt,
				      पूर्णांक num_tbs)
अणु
	काष्ठा iwlagn_scd_bc_tbl *scd_bc_tbl;
	पूर्णांक ग_लिखो_ptr = txq->ग_लिखो_ptr;
	पूर्णांक txq_id = txq->id;
	u8 sec_ctl = 0;
	u16 len = byte_cnt + IWL_TX_CRC_SIZE + IWL_TX_DELIMITER_SIZE;
	__le16 bc_ent;
	काष्ठा iwl_device_tx_cmd *dev_cmd = txq->entries[txq->ग_लिखो_ptr].cmd;
	काष्ठा iwl_tx_cmd *tx_cmd = (व्योम *)dev_cmd->payload;
	u8 sta_id = tx_cmd->sta_id;

	scd_bc_tbl = trans->txqs.scd_bc_tbls.addr;

	sec_ctl = tx_cmd->sec_ctl;

	चयन (sec_ctl & TX_CMD_SEC_MSK) अणु
	हाल TX_CMD_SEC_CCM:
		len += IEEE80211_CCMP_MIC_LEN;
		अवरोध;
	हाल TX_CMD_SEC_TKIP:
		len += IEEE80211_TKIP_ICV_LEN;
		अवरोध;
	हाल TX_CMD_SEC_WEP:
		len += IEEE80211_WEP_IV_LEN + IEEE80211_WEP_ICV_LEN;
		अवरोध;
	पूर्ण
	अगर (trans->txqs.bc_table_dword)
		len = DIV_ROUND_UP(len, 4);

	अगर (WARN_ON(len > 0xFFF || ग_लिखो_ptr >= TFD_QUEUE_SIZE_MAX))
		वापस;

	bc_ent = cpu_to_le16(len | (sta_id << 12));

	scd_bc_tbl[txq_id].tfd_offset[ग_लिखो_ptr] = bc_ent;

	अगर (ग_लिखो_ptr < TFD_QUEUE_SIZE_BC_DUP)
		scd_bc_tbl[txq_id].tfd_offset[TFD_QUEUE_SIZE_MAX + ग_लिखो_ptr] =
			bc_ent;
पूर्ण

व्योम iwl_txq_gen1_inval_byte_cnt_tbl(काष्ठा iwl_trans *trans,
				     काष्ठा iwl_txq *txq)
अणु
	काष्ठा iwlagn_scd_bc_tbl *scd_bc_tbl = trans->txqs.scd_bc_tbls.addr;
	पूर्णांक txq_id = txq->id;
	पूर्णांक पढ़ो_ptr = txq->पढ़ो_ptr;
	u8 sta_id = 0;
	__le16 bc_ent;
	काष्ठा iwl_device_tx_cmd *dev_cmd = txq->entries[पढ़ो_ptr].cmd;
	काष्ठा iwl_tx_cmd *tx_cmd = (व्योम *)dev_cmd->payload;

	WARN_ON(पढ़ो_ptr >= TFD_QUEUE_SIZE_MAX);

	अगर (txq_id != trans->txqs.cmd.q_id)
		sta_id = tx_cmd->sta_id;

	bc_ent = cpu_to_le16(1 | (sta_id << 12));

	scd_bc_tbl[txq_id].tfd_offset[पढ़ो_ptr] = bc_ent;

	अगर (पढ़ो_ptr < TFD_QUEUE_SIZE_BC_DUP)
		scd_bc_tbl[txq_id].tfd_offset[TFD_QUEUE_SIZE_MAX + पढ़ो_ptr] =
			bc_ent;
पूर्ण

/*
 * iwl_txq_मुक्त_tfd - Free all chunks referenced by TFD [txq->q.पढ़ो_ptr]
 * @trans - transport निजी data
 * @txq - tx queue
 * @dma_dir - the direction of the DMA mapping
 *
 * Does NOT advance any TFD circular buffer पढ़ो/ग_लिखो indexes
 * Does NOT मुक्त the TFD itself (which is within circular buffer)
 */
व्योम iwl_txq_मुक्त_tfd(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq)
अणु
	/* rd_ptr is bounded by TFD_QUEUE_SIZE_MAX and
	 * idx is bounded by n_winकरोw
	 */
	पूर्णांक rd_ptr = txq->पढ़ो_ptr;
	पूर्णांक idx = iwl_txq_get_cmd_index(txq, rd_ptr);
	काष्ठा sk_buff *skb;

	lockdep_निश्चित_held(&txq->lock);

	अगर (!txq->entries)
		वापस;

	/* We have only q->n_winकरोw txq->entries, but we use
	 * TFD_QUEUE_SIZE_MAX tfds
	 */
	iwl_txq_gen1_tfd_unmap(trans, &txq->entries[idx].meta, txq, rd_ptr);

	/* मुक्त SKB */
	skb = txq->entries[idx].skb;

	/* Can be called from irqs-disabled context
	 * If skb is not शून्य, it means that the whole queue is being
	 * मुक्तd and that the queue is not empty - मुक्त the skb
	 */
	अगर (skb) अणु
		iwl_op_mode_मुक्त_skb(trans->op_mode, skb);
		txq->entries[idx].skb = शून्य;
	पूर्ण
पूर्ण

व्योम iwl_txq_progress(काष्ठा iwl_txq *txq)
अणु
	lockdep_निश्चित_held(&txq->lock);

	अगर (!txq->wd_समयout)
		वापस;

	/*
	 * station is asleep and we send data - that must
	 * be uAPSD or PS-Poll. Don't rearm the समयr.
	 */
	अगर (txq->frozen)
		वापस;

	/*
	 * अगर empty delete समयr, otherwise move समयr क्रमward
	 * since we're making progress on this queue
	 */
	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr)
		del_समयr(&txq->stuck_समयr);
	अन्यथा
		mod_समयr(&txq->stuck_समयr, jअगरfies + txq->wd_समयout);
पूर्ण

/* Frees buffers until index _not_ inclusive */
व्योम iwl_txq_reclaim(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक ssn,
		     काष्ठा sk_buff_head *skbs)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];
	पूर्णांक tfd_num = iwl_txq_get_cmd_index(txq, ssn);
	पूर्णांक पढ़ो_ptr = iwl_txq_get_cmd_index(txq, txq->पढ़ो_ptr);
	पूर्णांक last_to_मुक्त;

	/* This function is not meant to release cmd queue*/
	अगर (WARN_ON(txq_id == trans->txqs.cmd.q_id))
		वापस;

	spin_lock_bh(&txq->lock);

	अगर (!test_bit(txq_id, trans->txqs.queue_used)) अणु
		IWL_DEBUG_TX_QUEUES(trans, "Q %d inactive - ignoring idx %d\n",
				    txq_id, ssn);
		जाओ out;
	पूर्ण

	अगर (पढ़ो_ptr == tfd_num)
		जाओ out;

	IWL_DEBUG_TX_REPLY(trans, "[Q %d] %d -> %d (%d)\n",
			   txq_id, txq->पढ़ो_ptr, tfd_num, ssn);

	/*Since we मुक्त until index _not_ inclusive, the one beक्रमe index is
	 * the last we will मुक्त. This one must be used */
	last_to_मुक्त = iwl_txq_dec_wrap(trans, tfd_num);

	अगर (!iwl_txq_used(txq, last_to_मुक्त)) अणु
		IWL_ERR(trans,
			"%s: Read index for txq id (%d), last_to_free %d is out of range [0-%d] %d %d.\n",
			__func__, txq_id, last_to_मुक्त,
			trans->trans_cfg->base_params->max_tfd_queue_size,
			txq->ग_लिखो_ptr, txq->पढ़ो_ptr);

		iwl_op_mode_समय_poपूर्णांक(trans->op_mode,
				       IWL_FW_INI_TIME_POINT_FAKE_TX,
				       शून्य);
		जाओ out;
	पूर्ण

	अगर (WARN_ON(!skb_queue_empty(skbs)))
		जाओ out;

	क्रम (;
	     पढ़ो_ptr != tfd_num;
	     txq->पढ़ो_ptr = iwl_txq_inc_wrap(trans, txq->पढ़ो_ptr),
	     पढ़ो_ptr = iwl_txq_get_cmd_index(txq, txq->पढ़ो_ptr)) अणु
		काष्ठा sk_buff *skb = txq->entries[पढ़ो_ptr].skb;

		अगर (WARN_ON_ONCE(!skb))
			जारी;

		iwl_txq_मुक्त_tso_page(trans, skb);

		__skb_queue_tail(skbs, skb);

		txq->entries[पढ़ो_ptr].skb = शून्य;

		अगर (!trans->trans_cfg->use_tfh)
			iwl_txq_gen1_inval_byte_cnt_tbl(trans, txq);

		iwl_txq_मुक्त_tfd(trans, txq);
	पूर्ण

	iwl_txq_progress(txq);

	अगर (iwl_txq_space(trans, txq) > txq->low_mark &&
	    test_bit(txq_id, trans->txqs.queue_stopped)) अणु
		काष्ठा sk_buff_head overflow_skbs;

		__skb_queue_head_init(&overflow_skbs);
		skb_queue_splice_init(&txq->overflow_q, &overflow_skbs);

		/*
		 * We are going to transmit from the overflow queue.
		 * Remember this state so that रुको_क्रम_txq_empty will know we
		 * are adding more packets to the TFD queue. It cannot rely on
		 * the state of &txq->overflow_q, as we just emptied it, but
		 * haven't TXed the content yet.
		 */
		txq->overflow_tx = true;

		/*
		 * This is tricky: we are in reclaim path which is non
		 * re-entrant, so noone will try to take the access the
		 * txq data from that path. We stopped tx, so we can't
		 * have tx as well. Bottom line, we can unlock and re-lock
		 * later.
		 */
		spin_unlock_bh(&txq->lock);

		जबतक (!skb_queue_empty(&overflow_skbs)) अणु
			काष्ठा sk_buff *skb = __skb_dequeue(&overflow_skbs);
			काष्ठा iwl_device_tx_cmd *dev_cmd_ptr;

			dev_cmd_ptr = *(व्योम **)((u8 *)skb->cb +
						 trans->txqs.dev_cmd_offs);

			/*
			 * Note that we can very well be overflowing again.
			 * In that हाल, iwl_txq_space will be small again
			 * and we won't wake mac80211's queue.
			 */
			iwl_trans_tx(trans, skb, dev_cmd_ptr, txq_id);
		पूर्ण

		अगर (iwl_txq_space(trans, txq) > txq->low_mark)
			iwl_wake_queue(trans, txq);

		spin_lock_bh(&txq->lock);
		txq->overflow_tx = false;
	पूर्ण

out:
	spin_unlock_bh(&txq->lock);
पूर्ण

/* Set wr_ptr of specअगरic device and txq  */
व्योम iwl_txq_set_q_ptrs(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक ptr)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];

	spin_lock_bh(&txq->lock);

	txq->ग_लिखो_ptr = ptr;
	txq->पढ़ो_ptr = txq->ग_लिखो_ptr;

	spin_unlock_bh(&txq->lock);
पूर्ण

व्योम iwl_trans_txq_मुक्तze_समयr(काष्ठा iwl_trans *trans, अचिन्हित दीर्घ txqs,
				bool मुक्तze)
अणु
	पूर्णांक queue;

	क्रम_each_set_bit(queue, &txqs, BITS_PER_LONG) अणु
		काष्ठा iwl_txq *txq = trans->txqs.txq[queue];
		अचिन्हित दीर्घ now;

		spin_lock_bh(&txq->lock);

		now = jअगरfies;

		अगर (txq->frozen == मुक्तze)
			जाओ next_queue;

		IWL_DEBUG_TX_QUEUES(trans, "%s TXQ %d\n",
				    मुक्तze ? "Freezing" : "Waking", queue);

		txq->frozen = मुक्तze;

		अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr)
			जाओ next_queue;

		अगर (मुक्तze) अणु
			अगर (unlikely(समय_after(now,
						txq->stuck_समयr.expires))) अणु
				/*
				 * The समयr should have fired, maybe it is
				 * spinning right now on the lock.
				 */
				जाओ next_queue;
			पूर्ण
			/* remember how दीर्घ until the समयr fires */
			txq->frozen_expiry_reमुख्यder =
				txq->stuck_समयr.expires - now;
			del_समयr(&txq->stuck_समयr);
			जाओ next_queue;
		पूर्ण

		/*
		 * Wake a non-empty queue -> arm समयr with the
		 * reमुख्यder beक्रमe it froze
		 */
		mod_समयr(&txq->stuck_समयr,
			  now + txq->frozen_expiry_reमुख्यder);

next_queue:
		spin_unlock_bh(&txq->lock);
	पूर्ण
पूर्ण

#घोषणा HOST_COMPLETE_TIMEOUT	(2 * HZ)

अटल पूर्णांक iwl_trans_txq_send_hcmd_sync(काष्ठा iwl_trans *trans,
					काष्ठा iwl_host_cmd *cmd)
अणु
	स्थिर अक्षर *cmd_str = iwl_get_cmd_string(trans, cmd->id);
	काष्ठा iwl_txq *txq = trans->txqs.txq[trans->txqs.cmd.q_id];
	पूर्णांक cmd_idx;
	पूर्णांक ret;

	IWL_DEBUG_INFO(trans, "Attempting to send sync command %s\n", cmd_str);

	अगर (WARN(test_and_set_bit(STATUS_SYNC_HCMD_ACTIVE,
				  &trans->status),
		 "Command %s: a command is already active!\n", cmd_str))
		वापस -EIO;

	IWL_DEBUG_INFO(trans, "Setting HCMD_ACTIVE for command %s\n", cmd_str);

	cmd_idx = trans->ops->send_cmd(trans, cmd);
	अगर (cmd_idx < 0) अणु
		ret = cmd_idx;
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_ERR(trans, "Error sending %s: enqueue_hcmd failed: %d\n",
			cmd_str, ret);
		वापस ret;
	पूर्ण

	ret = रुको_event_समयout(trans->रुको_command_queue,
				 !test_bit(STATUS_SYNC_HCMD_ACTIVE,
					   &trans->status),
				 HOST_COMPLETE_TIMEOUT);
	अगर (!ret) अणु
		IWL_ERR(trans, "Error sending %s: time out after %dms.\n",
			cmd_str, jअगरfies_to_msecs(HOST_COMPLETE_TIMEOUT));

		IWL_ERR(trans, "Current CMD queue read_ptr %d write_ptr %d\n",
			txq->पढ़ो_ptr, txq->ग_लिखो_ptr);

		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_DEBUG_INFO(trans, "Clearing HCMD_ACTIVE for command %s\n",
			       cmd_str);
		ret = -ETIMEDOUT;

		iwl_trans_sync_nmi(trans);
		जाओ cancel;
	पूर्ण

	अगर (test_bit(STATUS_FW_ERROR, &trans->status)) अणु
		IWL_ERR(trans, "FW error in SYNC CMD %s\n", cmd_str);
		dump_stack();
		ret = -EIO;
		जाओ cancel;
	पूर्ण

	अगर (!(cmd->flags & CMD_SEND_IN_RFKILL) &&
	    test_bit(STATUS_RFKILL_OPMODE, &trans->status)) अणु
		IWL_DEBUG_RF_KILL(trans, "RFKILL in SYNC CMD... no rsp\n");
		ret = -ERFKILL;
		जाओ cancel;
	पूर्ण

	अगर ((cmd->flags & CMD_WANT_SKB) && !cmd->resp_pkt) अणु
		IWL_ERR(trans, "Error: Response NULL in '%s'\n", cmd_str);
		ret = -EIO;
		जाओ cancel;
	पूर्ण

	वापस 0;

cancel:
	अगर (cmd->flags & CMD_WANT_SKB) अणु
		/*
		 * Cancel the CMD_WANT_SKB flag क्रम the cmd in the
		 * TX cmd queue. Otherwise in हाल the cmd comes
		 * in later, it will possibly set an invalid
		 * address (cmd->meta.source).
		 */
		txq->entries[cmd_idx].meta.flags &= ~CMD_WANT_SKB;
	पूर्ण

	अगर (cmd->resp_pkt) अणु
		iwl_मुक्त_resp(cmd);
		cmd->resp_pkt = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक iwl_trans_txq_send_hcmd(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_host_cmd *cmd)
अणु
	/* Make sure the NIC is still alive in the bus */
	अगर (test_bit(STATUS_TRANS_DEAD, &trans->status))
		वापस -ENODEV;

	अगर (!(cmd->flags & CMD_SEND_IN_RFKILL) &&
	    test_bit(STATUS_RFKILL_OPMODE, &trans->status)) अणु
		IWL_DEBUG_RF_KILL(trans, "Dropping CMD 0x%x: RF KILL\n",
				  cmd->id);
		वापस -ERFKILL;
	पूर्ण

	अगर (unlikely(trans->प्रणाली_pm_mode == IWL_PLAT_PM_MODE_D3 &&
		     !(cmd->flags & CMD_SEND_IN_D3))) अणु
		IWL_DEBUG_WOWLAN(trans, "Dropping CMD 0x%x: D3\n", cmd->id);
		वापस -EHOSTDOWN;
	पूर्ण

	अगर (cmd->flags & CMD_ASYNC) अणु
		पूर्णांक ret;

		/* An asynchronous command can not expect an SKB to be set. */
		अगर (WARN_ON(cmd->flags & CMD_WANT_SKB))
			वापस -EINVAL;

		ret = trans->ops->send_cmd(trans, cmd);
		अगर (ret < 0) अणु
			IWL_ERR(trans,
				"Error sending %s: enqueue_hcmd failed: %d\n",
				iwl_get_cmd_string(trans, cmd->id), ret);
			वापस ret;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस iwl_trans_txq_send_hcmd_sync(trans, cmd);
पूर्ण

