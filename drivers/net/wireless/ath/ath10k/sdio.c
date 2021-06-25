<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2016-2017 Erik Stromdahl <erik.stromdahl@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/bitfield.h>
#समावेश "core.h"
#समावेश "bmi.h"
#समावेश "debug.h"
#समावेश "hif.h"
#समावेश "htc.h"
#समावेश "mac.h"
#समावेश "targaddrs.h"
#समावेश "trace.h"
#समावेश "sdio.h"
#समावेश "coredump.h"

व्योम ath10k_sdio_fw_crashed_dump(काष्ठा ath10k *ar);

#घोषणा ATH10K_SDIO_VSG_BUF_SIZE	(64 * 1024)

/* अंतरभूतd helper functions */

अटल अंतरभूत पूर्णांक ath10k_sdio_calc_txrx_padded_len(काष्ठा ath10k_sdio *ar_sdio,
						   माप_प्रकार len)
अणु
	वापस __ALIGN_MASK((len), ar_sdio->mbox_info.block_mask);
पूर्ण

अटल अंतरभूत क्रमागत ath10k_htc_ep_id pipe_id_to_eid(u8 pipe_id)
अणु
	वापस (क्रमागत ath10k_htc_ep_id)pipe_id;
पूर्ण

अटल अंतरभूत व्योम ath10k_sdio_mbox_मुक्त_rx_pkt(काष्ठा ath10k_sdio_rx_data *pkt)
अणु
	dev_kमुक्त_skb(pkt->skb);
	pkt->skb = शून्य;
	pkt->alloc_len = 0;
	pkt->act_len = 0;
	pkt->trailer_only = false;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_sdio_mbox_alloc_rx_pkt(काष्ठा ath10k_sdio_rx_data *pkt,
						माप_प्रकार act_len, माप_प्रकार full_len,
						bool part_of_bundle,
						bool last_in_bundle)
अणु
	pkt->skb = dev_alloc_skb(full_len);
	अगर (!pkt->skb)
		वापस -ENOMEM;

	pkt->act_len = act_len;
	pkt->alloc_len = full_len;
	pkt->part_of_bundle = part_of_bundle;
	pkt->last_in_bundle = last_in_bundle;
	pkt->trailer_only = false;

	वापस 0;
पूर्ण

अटल अंतरभूत bool is_trailer_only_msg(काष्ठा ath10k_sdio_rx_data *pkt)
अणु
	bool trailer_only = false;
	काष्ठा ath10k_htc_hdr *htc_hdr =
		(काष्ठा ath10k_htc_hdr *)pkt->skb->data;
	u16 len = __le16_to_cpu(htc_hdr->len);

	अगर (len == htc_hdr->trailer_len)
		trailer_only = true;

	वापस trailer_only;
पूर्ण

/* sdio/mmc functions */

अटल अंतरभूत व्योम ath10k_sdio_set_cmd52_arg(u32 *arg, u8 ग_लिखो, u8 raw,
					     अचिन्हित पूर्णांक address,
					     अचिन्हित अक्षर val)
अणु
	*arg = FIELD_PREP(BIT(31), ग_लिखो) |
	       FIELD_PREP(BIT(27), raw) |
	       FIELD_PREP(BIT(26), 1) |
	       FIELD_PREP(GENMASK(25, 9), address) |
	       FIELD_PREP(BIT(8), 1) |
	       FIELD_PREP(GENMASK(7, 0), val);
पूर्ण

अटल पूर्णांक ath10k_sdio_func0_cmd52_wr_byte(काष्ठा mmc_card *card,
					   अचिन्हित पूर्णांक address,
					   अचिन्हित अक्षर byte)
अणु
	काष्ठा mmc_command io_cmd;

	स_रखो(&io_cmd, 0, माप(io_cmd));
	ath10k_sdio_set_cmd52_arg(&io_cmd.arg, 1, 0, address, byte);
	io_cmd.opcode = SD_IO_RW_सूचीECT;
	io_cmd.flags = MMC_RSP_R5 | MMC_CMD_AC;

	वापस mmc_रुको_क्रम_cmd(card->host, &io_cmd, 0);
पूर्ण

अटल पूर्णांक ath10k_sdio_func0_cmd52_rd_byte(काष्ठा mmc_card *card,
					   अचिन्हित पूर्णांक address,
					   अचिन्हित अक्षर *byte)
अणु
	काष्ठा mmc_command io_cmd;
	पूर्णांक ret;

	स_रखो(&io_cmd, 0, माप(io_cmd));
	ath10k_sdio_set_cmd52_arg(&io_cmd.arg, 0, 0, address, 0);
	io_cmd.opcode = SD_IO_RW_सूचीECT;
	io_cmd.flags = MMC_RSP_R5 | MMC_CMD_AC;

	ret = mmc_रुको_क्रम_cmd(card->host, &io_cmd, 0);
	अगर (!ret)
		*byte = io_cmd.resp[0];

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_config(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	अचिन्हित अक्षर byte, asyncपूर्णांकdelay = 2;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio configuration\n");

	sdio_claim_host(func);

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(func->card,
					      SDIO_CCCR_DRIVE_STRENGTH,
					      &byte);

	byte &= ~ATH10K_SDIO_DRIVE_DTSX_MASK;
	byte |= FIELD_PREP(ATH10K_SDIO_DRIVE_DTSX_MASK,
			   ATH10K_SDIO_DRIVE_DTSX_TYPE_D);

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      SDIO_CCCR_DRIVE_STRENGTH,
					      byte);

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(
		func->card,
		CCCR_SDIO_DRIVER_STRENGTH_ENABLE_ADDR,
		&byte);

	byte |= (CCCR_SDIO_DRIVER_STRENGTH_ENABLE_A |
		 CCCR_SDIO_DRIVER_STRENGTH_ENABLE_C |
		 CCCR_SDIO_DRIVER_STRENGTH_ENABLE_D);

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      CCCR_SDIO_DRIVER_STRENGTH_ENABLE_ADDR,
					      byte);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable driver strength: %d\n", ret);
		जाओ out;
	पूर्ण

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(func->card,
					      CCCR_SDIO_IRQ_MODE_REG_SDIO3,
					      &byte);

	byte |= SDIO_IRQ_MODE_ASYNC_4BIT_IRQ_SDIO3;

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      CCCR_SDIO_IRQ_MODE_REG_SDIO3,
					      byte);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable 4-bit async irq mode: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	byte = 0;
	ret = ath10k_sdio_func0_cmd52_rd_byte(func->card,
					      CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS,
					      &byte);

	byte &= ~CCCR_SDIO_ASYNC_INT_DELAY_MASK;
	byte |= FIELD_PREP(CCCR_SDIO_ASYNC_INT_DELAY_MASK, asyncपूर्णांकdelay);

	ret = ath10k_sdio_func0_cmd52_wr_byte(func->card,
					      CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS,
					      byte);

	/* give us some समय to enable, in ms */
	func->enable_समयout = 100;

	ret = sdio_set_block_size(func, ar_sdio->mbox_info.block_size);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set sdio block size to %d: %d\n",
			    ar_sdio->mbox_info.block_size, ret);
		जाओ out;
	पूर्ण

out:
	sdio_release_host(func);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_ग_लिखो32(काष्ठा ath10k *ar, u32 addr, u32 val)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	sdio_claim_host(func);

	sdio_ग_लिखोl(func, val, addr, &ret);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to write 0x%x to address 0x%x: %d\n",
			    val, addr, ret);
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio write32 addr 0x%x val 0x%x\n",
		   addr, val);

out:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_ग_लिखोsb32(काष्ठा ath10k *ar, u32 addr, u32 val)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	__le32 *buf;
	पूर्णांक ret;

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	*buf = cpu_to_le32(val);

	sdio_claim_host(func);

	ret = sdio_ग_लिखोsb(func, addr, buf, माप(*buf));
	अगर (ret) अणु
		ath10k_warn(ar, "failed to write value 0x%x to fixed sb address 0x%x: %d\n",
			    val, addr, ret);
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio writesb32 addr 0x%x val 0x%x\n",
		   addr, val);

out:
	sdio_release_host(func);

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_पढ़ो32(काष्ठा ath10k *ar, u32 addr, u32 *val)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	sdio_claim_host(func);
	*val = sdio_पढ़ोl(func, addr, &ret);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read from address 0x%x: %d\n",
			    addr, ret);
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio read32 addr 0x%x val 0x%x\n",
		   addr, *val);

out:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_पढ़ो(काष्ठा ath10k *ar, u32 addr, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	sdio_claim_host(func);

	ret = sdio_स_नकल_fromio(func, buf, addr, len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read from address 0x%x: %d\n",
			    addr, ret);
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio read addr 0x%x buf 0x%p len %zu\n",
		   addr, buf, len);
	ath10k_dbg_dump(ar, ATH10K_DBG_SDIO_DUMP, शून्य, "sdio read ", buf, len);

out:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_ग_लिखो(काष्ठा ath10k *ar, u32 addr, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	sdio_claim_host(func);

	/* For some reason toio() करोesn't have स्थिर क्रम the buffer, need
	 * an ugly hack to workaround that.
	 */
	ret = sdio_स_नकल_toio(func, addr, (व्योम *)buf, len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to write to address 0x%x: %d\n",
			    addr, ret);
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio write addr 0x%x buf 0x%p len %zu\n",
		   addr, buf, len);
	ath10k_dbg_dump(ar, ATH10K_DBG_SDIO_DUMP, शून्य, "sdio write ", buf, len);

out:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_पढ़ोsb(काष्ठा ath10k *ar, u32 addr, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	sdio_claim_host(func);

	len = round_करोwn(len, ar_sdio->mbox_info.block_size);

	ret = sdio_पढ़ोsb(func, buf, addr, len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read from fixed (sb) address 0x%x: %d\n",
			    addr, ret);
		जाओ out;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio readsb addr 0x%x buf 0x%p len %zu\n",
		   addr, buf, len);
	ath10k_dbg_dump(ar, ATH10K_DBG_SDIO_DUMP, शून्य, "sdio readsb ", buf, len);

out:
	sdio_release_host(func);

	वापस ret;
पूर्ण

/* HIF mbox functions */

अटल पूर्णांक ath10k_sdio_mbox_rx_process_packet(काष्ठा ath10k *ar,
					      काष्ठा ath10k_sdio_rx_data *pkt,
					      u32 *lookaheads,
					      पूर्णांक *n_lookaheads)
अणु
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा sk_buff *skb = pkt->skb;
	काष्ठा ath10k_htc_hdr *htc_hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	bool trailer_present = htc_hdr->flags & ATH10K_HTC_FLAG_TRAILER_PRESENT;
	क्रमागत ath10k_htc_ep_id eid;
	u8 *trailer;
	पूर्णांक ret;

	अगर (trailer_present) अणु
		trailer = skb->data + skb->len - htc_hdr->trailer_len;

		eid = pipe_id_to_eid(htc_hdr->eid);

		ret = ath10k_htc_process_trailer(htc,
						 trailer,
						 htc_hdr->trailer_len,
						 eid,
						 lookaheads,
						 n_lookaheads);
		अगर (ret)
			वापस ret;

		अगर (is_trailer_only_msg(pkt))
			pkt->trailer_only = true;

		skb_trim(skb, skb->len - htc_hdr->trailer_len);
	पूर्ण

	skb_pull(skb, माप(*htc_hdr));

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_rx_process_packets(काष्ठा ath10k *ar,
					       u32 lookaheads[],
					       पूर्णांक *n_lookahead)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_htc *htc = &ar->htc;
	काष्ठा ath10k_sdio_rx_data *pkt;
	काष्ठा ath10k_htc_ep *ep;
	काष्ठा ath10k_skb_rxcb *cb;
	क्रमागत ath10k_htc_ep_id id;
	पूर्णांक ret, i, *n_lookahead_local;
	u32 *lookaheads_local;
	पूर्णांक lookahead_idx = 0;

	क्रम (i = 0; i < ar_sdio->n_rx_pkts; i++) अणु
		lookaheads_local = lookaheads;
		n_lookahead_local = n_lookahead;

		id = ((काष्ठा ath10k_htc_hdr *)
		      &lookaheads[lookahead_idx++])->eid;

		अगर (id >= ATH10K_HTC_EP_COUNT) अणु
			ath10k_warn(ar, "invalid endpoint in look-ahead: %d\n",
				    id);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		ep = &htc->endpoपूर्णांक[id];

		अगर (ep->service_id == 0) अणु
			ath10k_warn(ar, "ep %d is not connected\n", id);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		pkt = &ar_sdio->rx_pkts[i];

		अगर (pkt->part_of_bundle && !pkt->last_in_bundle) अणु
			/* Only पढ़ो lookahead's from RX trailers
			 * क्रम the last packet in a bundle.
			 */
			lookahead_idx--;
			lookaheads_local = शून्य;
			n_lookahead_local = शून्य;
		पूर्ण

		ret = ath10k_sdio_mbox_rx_process_packet(ar,
							 pkt,
							 lookaheads_local,
							 n_lookahead_local);
		अगर (ret)
			जाओ out;

		अगर (!pkt->trailer_only) अणु
			cb = ATH10K_SKB_RXCB(pkt->skb);
			cb->eid = id;

			skb_queue_tail(&ar_sdio->rx_head, pkt->skb);
			queue_work(ar->workqueue_aux,
				   &ar_sdio->async_work_rx);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(pkt->skb);
		पूर्ण

		/* The RX complete handler now owns the skb...*/
		pkt->skb = शून्य;
		pkt->alloc_len = 0;
	पूर्ण

	ret = 0;

out:
	/* Free all packets that was not passed on to the RX completion
	 * handler...
	 */
	क्रम (; i < ar_sdio->n_rx_pkts; i++)
		ath10k_sdio_mbox_मुक्त_rx_pkt(&ar_sdio->rx_pkts[i]);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_alloc_bundle(काष्ठा ath10k *ar,
					 काष्ठा ath10k_sdio_rx_data *rx_pkts,
					 काष्ठा ath10k_htc_hdr *htc_hdr,
					 माप_प्रकार full_len, माप_प्रकार act_len,
					 माप_प्रकार *bndl_cnt)
अणु
	पूर्णांक ret, i;
	u8 max_msgs = ar->htc.max_msgs_per_htc_bundle;

	*bndl_cnt = ath10k_htc_get_bundle_count(max_msgs, htc_hdr->flags);

	अगर (*bndl_cnt > max_msgs) अणु
		ath10k_warn(ar,
			    "HTC bundle length %u exceeds maximum %u\n",
			    le16_to_cpu(htc_hdr->len),
			    max_msgs);
		वापस -ENOMEM;
	पूर्ण

	/* Allocate bndl_cnt extra skb's क्रम the bundle.
	 * The package containing the
	 * ATH10K_HTC_FLAG_BUNDLE_MASK flag is not included
	 * in bndl_cnt. The skb क्रम that packet will be
	 * allocated separately.
	 */
	क्रम (i = 0; i < *bndl_cnt; i++) अणु
		ret = ath10k_sdio_mbox_alloc_rx_pkt(&rx_pkts[i],
						    act_len,
						    full_len,
						    true,
						    false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_rx_alloc(काष्ठा ath10k *ar,
				     u32 lookaheads[], पूर्णांक n_lookaheads)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_htc_hdr *htc_hdr;
	माप_प्रकार full_len, act_len;
	bool last_in_bundle;
	पूर्णांक ret, i;
	पूर्णांक pkt_cnt = 0;

	अगर (n_lookaheads > ATH10K_SDIO_MAX_RX_MSGS) अणु
		ath10k_warn(ar, "the total number of pkts to be fetched (%u) exceeds maximum %u\n",
			    n_lookaheads, ATH10K_SDIO_MAX_RX_MSGS);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < n_lookaheads; i++) अणु
		htc_hdr = (काष्ठा ath10k_htc_hdr *)&lookaheads[i];
		last_in_bundle = false;

		अगर (le16_to_cpu(htc_hdr->len) > ATH10K_HTC_MBOX_MAX_PAYLOAD_LENGTH) अणु
			ath10k_warn(ar, "payload length %d exceeds max htc length: %zu\n",
				    le16_to_cpu(htc_hdr->len),
				    ATH10K_HTC_MBOX_MAX_PAYLOAD_LENGTH);
			ret = -ENOMEM;

			ath10k_core_start_recovery(ar);
			ath10k_warn(ar, "exceeds length, start recovery\n");

			जाओ err;
		पूर्ण

		act_len = le16_to_cpu(htc_hdr->len) + माप(*htc_hdr);
		full_len = ath10k_sdio_calc_txrx_padded_len(ar_sdio, act_len);

		अगर (full_len > ATH10K_SDIO_MAX_BUFFER_SIZE) अणु
			ath10k_warn(ar, "rx buffer requested with invalid htc_hdr length (%d, 0x%x): %d\n",
				    htc_hdr->eid, htc_hdr->flags,
				    le16_to_cpu(htc_hdr->len));
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (ath10k_htc_get_bundle_count(
			ar->htc.max_msgs_per_htc_bundle, htc_hdr->flags)) अणु
			/* HTC header indicates that every packet to follow
			 * has the same padded length so that it can be
			 * optimally fetched as a full bundle.
			 */
			माप_प्रकार bndl_cnt;

			ret = ath10k_sdio_mbox_alloc_bundle(ar,
							    &ar_sdio->rx_pkts[pkt_cnt],
							    htc_hdr,
							    full_len,
							    act_len,
							    &bndl_cnt);

			अगर (ret) अणु
				ath10k_warn(ar, "failed to allocate a bundle: %d\n",
					    ret);
				जाओ err;
			पूर्ण

			pkt_cnt += bndl_cnt;

			/* next buffer will be the last in the bundle */
			last_in_bundle = true;
		पूर्ण

		/* Allocate skb क्रम packet. If the packet had the
		 * ATH10K_HTC_FLAG_BUNDLE_MASK flag set, all bundled
		 * packet skb's have been allocated in the previous step.
		 */
		अगर (htc_hdr->flags & ATH10K_HTC_FLAGS_RECV_1MORE_BLOCK)
			full_len += ATH10K_HIF_MBOX_BLOCK_SIZE;

		ret = ath10k_sdio_mbox_alloc_rx_pkt(&ar_sdio->rx_pkts[pkt_cnt],
						    act_len,
						    full_len,
						    last_in_bundle,
						    last_in_bundle);
		अगर (ret) अणु
			ath10k_warn(ar, "alloc_rx_pkt error %d\n", ret);
			जाओ err;
		पूर्ण

		pkt_cnt++;
	पूर्ण

	ar_sdio->n_rx_pkts = pkt_cnt;

	वापस 0;

err:
	क्रम (i = 0; i < ATH10K_SDIO_MAX_RX_MSGS; i++) अणु
		अगर (!ar_sdio->rx_pkts[i].alloc_len)
			अवरोध;
		ath10k_sdio_mbox_मुक्त_rx_pkt(&ar_sdio->rx_pkts[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_rx_fetch(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_rx_data *pkt = &ar_sdio->rx_pkts[0];
	काष्ठा sk_buff *skb = pkt->skb;
	काष्ठा ath10k_htc_hdr *htc_hdr;
	पूर्णांक ret;

	ret = ath10k_sdio_पढ़ोsb(ar, ar_sdio->mbox_info.htc_addr,
				 skb->data, pkt->alloc_len);
	अगर (ret)
		जाओ err;

	htc_hdr = (काष्ठा ath10k_htc_hdr *)skb->data;
	pkt->act_len = le16_to_cpu(htc_hdr->len) + माप(*htc_hdr);

	अगर (pkt->act_len > pkt->alloc_len) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	skb_put(skb, pkt->act_len);
	वापस 0;

err:
	ar_sdio->n_rx_pkts = 0;
	ath10k_sdio_mbox_मुक्त_rx_pkt(pkt);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_rx_fetch_bundle(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_rx_data *pkt;
	काष्ठा ath10k_htc_hdr *htc_hdr;
	पूर्णांक ret, i;
	u32 pkt_offset, virt_pkt_len;

	virt_pkt_len = 0;
	क्रम (i = 0; i < ar_sdio->n_rx_pkts; i++)
		virt_pkt_len += ar_sdio->rx_pkts[i].alloc_len;

	अगर (virt_pkt_len > ATH10K_SDIO_VSG_BUF_SIZE) अणु
		ath10k_warn(ar, "sdio vsg buffer size limit: %d\n", virt_pkt_len);
		ret = -E2BIG;
		जाओ err;
	पूर्ण

	ret = ath10k_sdio_पढ़ोsb(ar, ar_sdio->mbox_info.htc_addr,
				 ar_sdio->vsg_buffer, virt_pkt_len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read bundle packets: %d", ret);
		जाओ err;
	पूर्ण

	pkt_offset = 0;
	क्रम (i = 0; i < ar_sdio->n_rx_pkts; i++) अणु
		pkt = &ar_sdio->rx_pkts[i];
		htc_hdr = (काष्ठा ath10k_htc_hdr *)(ar_sdio->vsg_buffer + pkt_offset);
		pkt->act_len = le16_to_cpu(htc_hdr->len) + माप(*htc_hdr);

		अगर (pkt->act_len > pkt->alloc_len) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		skb_put_data(pkt->skb, htc_hdr, pkt->act_len);
		pkt_offset += pkt->alloc_len;
	पूर्ण

	वापस 0;

err:
	/* Free all packets that was not successfully fetched. */
	क्रम (i = 0; i < ar_sdio->n_rx_pkts; i++)
		ath10k_sdio_mbox_मुक्त_rx_pkt(&ar_sdio->rx_pkts[i]);

	ar_sdio->n_rx_pkts = 0;

	वापस ret;
पूर्ण

/* This is the समयout क्रम mailbox processing करोne in the sdio irq
 * handler. The समयout is deliberately set quite high since SDIO dump logs
 * over serial port can/will add a substantial overhead to the processing
 * (अगर enabled).
 */
#घोषणा SDIO_MBOX_PROCESSING_TIMEOUT_HZ (20 * HZ)

अटल पूर्णांक ath10k_sdio_mbox_rxmsg_pending_handler(काष्ठा ath10k *ar,
						  u32 msg_lookahead, bool *करोne)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 lookaheads[ATH10K_SDIO_MAX_RX_MSGS];
	पूर्णांक n_lookaheads = 1;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	*करोne = true;

	/* Copy the lookahead obtained from the HTC रेजिस्टर table पूर्णांकo our
	 * temp array as a start value.
	 */
	lookaheads[0] = msg_lookahead;

	समयout = jअगरfies + SDIO_MBOX_PROCESSING_TIMEOUT_HZ;
	करो अणु
		/* Try to allocate as many HTC RX packets indicated by
		 * n_lookaheads.
		 */
		ret = ath10k_sdio_mbox_rx_alloc(ar, lookaheads,
						n_lookaheads);
		अगर (ret)
			अवरोध;

		अगर (ar_sdio->n_rx_pkts >= 2)
			/* A recv bundle was detected, क्रमce IRQ status
			 * re-check again.
			 */
			*करोne = false;

		अगर (ar_sdio->n_rx_pkts > 1)
			ret = ath10k_sdio_mbox_rx_fetch_bundle(ar);
		अन्यथा
			ret = ath10k_sdio_mbox_rx_fetch(ar);

		/* Process fetched packets. This will potentially update
		 * n_lookaheads depending on अगर the packets contain lookahead
		 * reports.
		 */
		n_lookaheads = 0;
		ret = ath10k_sdio_mbox_rx_process_packets(ar,
							  lookaheads,
							  &n_lookaheads);

		अगर (!n_lookaheads || ret)
			अवरोध;

		/* For SYNCH processing, अगर we get here, we are running
		 * through the loop again due to updated lookaheads. Set
		 * flag that we should re-check IRQ status रेजिस्टरs again
		 * beक्रमe leaving IRQ processing, this can net better
		 * perक्रमmance in high throughput situations.
		 */
		*करोne = false;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	अगर (ret && (ret != -ECANCELED))
		ath10k_warn(ar, "failed to get pending recv messages: %d\n",
			    ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_proc_dbg_पूर्णांकr(काष्ठा ath10k *ar)
अणु
	u32 val;
	पूर्णांक ret;

	/* TODO: Add firmware crash handling */
	ath10k_warn(ar, "firmware crashed\n");

	/* पढ़ो counter to clear the पूर्णांकerrupt, the debug error पूर्णांकerrupt is
	 * counter 0.
	 */
	ret = ath10k_sdio_पढ़ो32(ar, MBOX_COUNT_DEC_ADDRESS, &val);
	अगर (ret)
		ath10k_warn(ar, "failed to clear debug interrupt: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_proc_counter_पूर्णांकr(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	u8 counter_पूर्णांक_status;
	पूर्णांक ret;

	mutex_lock(&irq_data->mtx);
	counter_पूर्णांक_status = irq_data->irq_proc_reg->counter_पूर्णांक_status &
			     irq_data->irq_en_reg->cntr_पूर्णांक_status_en;

	/* NOTE: other modules like GMBOX may use the counter पूर्णांकerrupt क्रम
	 * credit flow control on other counters, we only need to check क्रम
	 * the debug निश्चितion counter पूर्णांकerrupt.
	 */
	अगर (counter_पूर्णांक_status & ATH10K_SDIO_TARGET_DEBUG_INTR_MASK)
		ret = ath10k_sdio_mbox_proc_dbg_पूर्णांकr(ar);
	अन्यथा
		ret = 0;

	mutex_unlock(&irq_data->mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_proc_err_पूर्णांकr(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	u8 error_पूर्णांक_status;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio error interrupt\n");

	error_पूर्णांक_status = irq_data->irq_proc_reg->error_पूर्णांक_status & 0x0F;
	अगर (!error_पूर्णांक_status) अणु
		ath10k_warn(ar, "invalid error interrupt status: 0x%x\n",
			    error_पूर्णांक_status);
		वापस -EIO;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SDIO,
		   "sdio error_int_status 0x%x\n", error_पूर्णांक_status);

	अगर (FIELD_GET(MBOX_ERROR_INT_STATUS_WAKEUP_MASK,
		      error_पूर्णांक_status))
		ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio interrupt error wakeup\n");

	अगर (FIELD_GET(MBOX_ERROR_INT_STATUS_RX_UNDERFLOW_MASK,
		      error_पूर्णांक_status))
		ath10k_warn(ar, "rx underflow interrupt error\n");

	अगर (FIELD_GET(MBOX_ERROR_INT_STATUS_TX_OVERFLOW_MASK,
		      error_पूर्णांक_status))
		ath10k_warn(ar, "tx overflow interrupt error\n");

	/* Clear the पूर्णांकerrupt */
	irq_data->irq_proc_reg->error_पूर्णांक_status &= ~error_पूर्णांक_status;

	/* set W1C value to clear the पूर्णांकerrupt, this hits the रेजिस्टर first */
	ret = ath10k_sdio_ग_लिखोsb32(ar, MBOX_ERROR_INT_STATUS_ADDRESS,
				    error_पूर्णांक_status);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to write to error int status address: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_proc_cpu_पूर्णांकr(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	u8 cpu_पूर्णांक_status;
	पूर्णांक ret;

	mutex_lock(&irq_data->mtx);
	cpu_पूर्णांक_status = irq_data->irq_proc_reg->cpu_पूर्णांक_status &
			 irq_data->irq_en_reg->cpu_पूर्णांक_status_en;
	अगर (!cpu_पूर्णांक_status) अणु
		ath10k_warn(ar, "CPU interrupt status is zero\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Clear the पूर्णांकerrupt */
	irq_data->irq_proc_reg->cpu_पूर्णांक_status &= ~cpu_पूर्णांक_status;

	/* Set up the रेजिस्टर transfer buffer to hit the रेजिस्टर 4 बार,
	 * this is करोne to make the access 4-byte aligned to mitigate issues
	 * with host bus पूर्णांकerconnects that restrict bus transfer lengths to
	 * be a multiple of 4-bytes.
	 *
	 * Set W1C value to clear the पूर्णांकerrupt, this hits the रेजिस्टर first.
	 */
	ret = ath10k_sdio_ग_लिखोsb32(ar, MBOX_CPU_INT_STATUS_ADDRESS,
				    cpu_पूर्णांक_status);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to write to cpu interrupt status address: %d\n",
			    ret);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&irq_data->mtx);
	अगर (cpu_पूर्णांक_status & MBOX_CPU_STATUS_ENABLE_ASSERT_MASK)
		ath10k_sdio_fw_crashed_dump(ar);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_पढ़ो_पूर्णांक_status(काष्ठा ath10k *ar,
					    u8 *host_पूर्णांक_status,
					    u32 *lookahead)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	काष्ठा ath10k_sdio_irq_proc_regs *irq_proc_reg = irq_data->irq_proc_reg;
	काष्ठा ath10k_sdio_irq_enable_regs *irq_en_reg = irq_data->irq_en_reg;
	u8 htc_mbox = FIELD_PREP(ATH10K_HTC_MAILBOX_MASK, 1);
	पूर्णांक ret;

	mutex_lock(&irq_data->mtx);

	*lookahead = 0;
	*host_पूर्णांक_status = 0;

	/* पूर्णांक_status_en is supposed to be non zero, otherwise पूर्णांकerrupts
	 * shouldn't be enabled. There is however a लघु समय frame during
	 * initialization between the irq रेजिस्टर and पूर्णांक_status_en init
	 * where this can happen.
	 * We silently ignore this condition.
	 */
	अगर (!irq_en_reg->पूर्णांक_status_en) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* Read the first माप(काष्ठा ath10k_irq_proc_रेजिस्टरs)
	 * bytes of the HTC रेजिस्टर table. This
	 * will yield us the value of dअगरferent पूर्णांक status
	 * रेजिस्टरs and the lookahead रेजिस्टरs.
	 */
	ret = ath10k_sdio_पढ़ो(ar, MBOX_HOST_INT_STATUS_ADDRESS,
			       irq_proc_reg, माप(*irq_proc_reg));
	अगर (ret) अणु
		ath10k_core_start_recovery(ar);
		ath10k_warn(ar, "read int status fail, start recovery\n");
		जाओ out;
	पूर्ण

	/* Update only those रेजिस्टरs that are enabled */
	*host_पूर्णांक_status = irq_proc_reg->host_पूर्णांक_status &
			   irq_en_reg->पूर्णांक_status_en;

	/* Look at mbox status */
	अगर (!(*host_पूर्णांक_status & htc_mbox)) अणु
		*lookahead = 0;
		ret = 0;
		जाओ out;
	पूर्ण

	/* Mask out pending mbox value, we use look ahead as
	 * the real flag क्रम mbox processing.
	 */
	*host_पूर्णांक_status &= ~htc_mbox;
	अगर (irq_proc_reg->rx_lookahead_valid & htc_mbox) अणु
		*lookahead = le32_to_cpu(
			irq_proc_reg->rx_lookahead[ATH10K_HTC_MAILBOX]);
		अगर (!*lookahead)
			ath10k_warn(ar, "sdio mbox lookahead is zero\n");
	पूर्ण

out:
	mutex_unlock(&irq_data->mtx);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_mbox_proc_pending_irqs(काष्ठा ath10k *ar,
					      bool *करोne)
अणु
	u8 host_पूर्णांक_status;
	u32 lookahead;
	पूर्णांक ret;

	/* NOTE: HIF implementation guarantees that the context of this
	 * call allows us to perक्रमm SYNCHRONOUS I/O, that is we can block,
	 * sleep or call any API that can block or चयन thपढ़ो/task
	 * contexts. This is a fully schedulable context.
	 */

	ret = ath10k_sdio_mbox_पढ़ो_पूर्णांक_status(ar,
					       &host_पूर्णांक_status,
					       &lookahead);
	अगर (ret) अणु
		*करोne = true;
		जाओ out;
	पूर्ण

	अगर (!host_पूर्णांक_status && !lookahead) अणु
		ret = 0;
		*करोne = true;
		जाओ out;
	पूर्ण

	अगर (lookahead) अणु
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio pending mailbox msg lookahead 0x%08x\n",
			   lookahead);

		ret = ath10k_sdio_mbox_rxmsg_pending_handler(ar,
							     lookahead,
							     करोne);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* now, handle the rest of the पूर्णांकerrupts */
	ath10k_dbg(ar, ATH10K_DBG_SDIO,
		   "sdio host_int_status 0x%x\n", host_पूर्णांक_status);

	अगर (FIELD_GET(MBOX_HOST_INT_STATUS_CPU_MASK, host_पूर्णांक_status)) अणु
		/* CPU Interrupt */
		ret = ath10k_sdio_mbox_proc_cpu_पूर्णांकr(ar);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (FIELD_GET(MBOX_HOST_INT_STATUS_ERROR_MASK, host_पूर्णांक_status)) अणु
		/* Error Interrupt */
		ret = ath10k_sdio_mbox_proc_err_पूर्णांकr(ar);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (FIELD_GET(MBOX_HOST_INT_STATUS_COUNTER_MASK, host_पूर्णांक_status))
		/* Counter Interrupt */
		ret = ath10k_sdio_mbox_proc_counter_पूर्णांकr(ar);

	ret = 0;

out:
	/* An optimization to bypass पढ़ोing the IRQ status रेजिस्टरs
	 * unecessarily which can re-wake the target, अगर upper layers
	 * determine that we are in a low-throughput mode, we can rely on
	 * taking another पूर्णांकerrupt rather than re-checking the status
	 * रेजिस्टरs which can re-wake the target.
	 *
	 * NOTE : क्रम host पूर्णांकerfaces that makes use of detecting pending
	 * mbox messages at hअगर can not use this optimization due to
	 * possible side effects, SPI requires the host to drain all
	 * messages from the mailbox beक्रमe निकासing the ISR routine.
	 */

	ath10k_dbg(ar, ATH10K_DBG_SDIO,
		   "sdio pending irqs done %d status %d",
		   *करोne, ret);

	वापस ret;
पूर्ण

अटल व्योम ath10k_sdio_set_mbox_info(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_mbox_info *mbox_info = &ar_sdio->mbox_info;
	u16 device = ar_sdio->func->device, dev_id_base, dev_id_chiprev;

	mbox_info->htc_addr = ATH10K_HIF_MBOX_BASE_ADDR;
	mbox_info->block_size = ATH10K_HIF_MBOX_BLOCK_SIZE;
	mbox_info->block_mask = ATH10K_HIF_MBOX_BLOCK_SIZE - 1;
	mbox_info->gmbox_addr = ATH10K_HIF_GMBOX_BASE_ADDR;
	mbox_info->gmbox_sz = ATH10K_HIF_GMBOX_WIDTH;

	mbox_info->ext_info[0].htc_ext_addr = ATH10K_HIF_MBOX0_EXT_BASE_ADDR;

	dev_id_base = (device & 0x0F00);
	dev_id_chiprev = (device & 0x00FF);
	चयन (dev_id_base) अणु
	हाल (SDIO_DEVICE_ID_ATHEROS_AR6005 & 0x0F00):
		अगर (dev_id_chiprev < 4)
			mbox_info->ext_info[0].htc_ext_sz =
				ATH10K_HIF_MBOX0_EXT_WIDTH;
		अन्यथा
			/* from QCA6174 2.0(0x504), the width has been extended
			 * to 56K
			 */
			mbox_info->ext_info[0].htc_ext_sz =
				ATH10K_HIF_MBOX0_EXT_WIDTH_ROME_2_0;
		अवरोध;
	हाल (SDIO_DEVICE_ID_ATHEROS_QCA9377 & 0x0F00):
		mbox_info->ext_info[0].htc_ext_sz =
			ATH10K_HIF_MBOX0_EXT_WIDTH_ROME_2_0;
		अवरोध;
	शेष:
		mbox_info->ext_info[0].htc_ext_sz =
				ATH10K_HIF_MBOX0_EXT_WIDTH;
	पूर्ण

	mbox_info->ext_info[1].htc_ext_addr =
		mbox_info->ext_info[0].htc_ext_addr +
		mbox_info->ext_info[0].htc_ext_sz +
		ATH10K_HIF_MBOX_DUMMY_SPACE_SIZE;
	mbox_info->ext_info[1].htc_ext_sz = ATH10K_HIF_MBOX1_EXT_WIDTH;
पूर्ण

/* BMI functions */

अटल पूर्णांक ath10k_sdio_bmi_credits(काष्ठा ath10k *ar)
अणु
	u32 addr, cmd_credits;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	/* Read the counter रेजिस्टर to get the command credits */
	addr = MBOX_COUNT_DEC_ADDRESS + ATH10K_HIF_MBOX_NUM_MAX * 4;
	समयout = jअगरfies + BMI_COMMUNICATION_TIMEOUT_HZ;
	cmd_credits = 0;

	जबतक (समय_beक्रमe(jअगरfies, समयout) && !cmd_credits) अणु
		/* Hit the credit counter with a 4-byte access, the first byte
		 * पढ़ो will hit the counter and cause a decrement, जबतक the
		 * reमुख्यing 3 bytes has no effect. The rationale behind this
		 * is to make all HIF accesses 4-byte aligned.
		 */
		ret = ath10k_sdio_पढ़ो32(ar, addr, &cmd_credits);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "unable to decrement the command credit count register: %d\n",
				    ret);
			वापस ret;
		पूर्ण

		/* The counter is only 8 bits.
		 * Ignore anything in the upper 3 bytes
		 */
		cmd_credits &= 0xFF;
	पूर्ण

	अगर (!cmd_credits) अणु
		ath10k_warn(ar, "bmi communication timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_bmi_get_rx_lookahead(काष्ठा ath10k *ar)
अणु
	अचिन्हित दीर्घ समयout;
	u32 rx_word;
	पूर्णांक ret;

	समयout = jअगरfies + BMI_COMMUNICATION_TIMEOUT_HZ;
	rx_word = 0;

	जबतक ((समय_beक्रमe(jअगरfies, समयout)) && !rx_word) अणु
		ret = ath10k_sdio_पढ़ो32(ar,
					 MBOX_HOST_INT_STATUS_ADDRESS,
					 &rx_word);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to read RX_LOOKAHEAD_VALID: %d\n", ret);
			वापस ret;
		पूर्ण

		 /* all we really want is one bit */
		rx_word &= 1;
	पूर्ण

	अगर (!rx_word) अणु
		ath10k_warn(ar, "bmi_recv_buf FIFO empty\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_bmi_exchange_msg(काष्ठा ath10k *ar,
					व्योम *req, u32 req_len,
					व्योम *resp, u32 *resp_len)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 addr;
	पूर्णांक ret;

	अगर (req) अणु
		ret = ath10k_sdio_bmi_credits(ar);
		अगर (ret)
			वापस ret;

		addr = ar_sdio->mbox_info.htc_addr;

		स_नकल(ar_sdio->bmi_buf, req, req_len);
		ret = ath10k_sdio_ग_लिखो(ar, addr, ar_sdio->bmi_buf, req_len);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "unable to send the bmi data to the device: %d\n",
				    ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!resp || !resp_len)
		/* No response expected */
		वापस 0;

	/* During normal bootup, small पढ़ोs may be required.
	 * Rather than issue an HIF Read and then रुको as the Target
	 * adds successive bytes to the FIFO, we रुको here until
	 * we know that response data is available.
	 *
	 * This allows us to cleanly समयout on an unexpected
	 * Target failure rather than risk problems at the HIF level.
	 * In particular, this aव्योमs SDIO समयouts and possibly garbage
	 * data on some host controllers.  And on an पूर्णांकerconnect
	 * such as Compact Flash (as well as some SDIO masters) which
	 * करोes not provide any indication on data समयout, it aव्योमs
	 * a potential hang or garbage response.
	 *
	 * Synchronization is more dअगरficult क्रम पढ़ोs larger than the
	 * size of the MBOX FIFO (128B), because the Target is unable
	 * to push the 129th byte of data until AFTER the Host posts an
	 * HIF Read and हटाओs some FIFO data.  So क्रम large पढ़ोs the
	 * Host proceeds to post an HIF Read BEFORE all the data is
	 * actually available to पढ़ो.  Fortunately, large BMI पढ़ोs करो
	 * not occur in practice -- they're supported क्रम debug/development.
	 *
	 * So Host/Target BMI synchronization is भागided पूर्णांकo these हालs:
	 *  CASE 1: length < 4
	 *        Should not happen
	 *
	 *  CASE 2: 4 <= length <= 128
	 *        Wait क्रम first 4 bytes to be in FIFO
	 *        If CONSERVATIVE_BMI_READ is enabled, also रुको क्रम
	 *        a BMI command credit, which indicates that the ENTIRE
	 *        response is available in the FIFO
	 *
	 *  CASE 3: length > 128
	 *        Wait क्रम the first 4 bytes to be in FIFO
	 *
	 * For most uses, a small समयout should be sufficient and we will
	 * usually see a response quickly; but there may be some unusual
	 * (debug) हालs of BMI_EXECUTE where we want an larger समयout.
	 * For now, we use an unbounded busy loop जबतक रुकोing क्रम
	 * BMI_EXECUTE.
	 *
	 * If BMI_EXECUTE ever needs to support दीर्घer-latency execution,
	 * especially in production, this code needs to be enhanced to sleep
	 * and yield.  Also note that BMI_COMMUNICATION_TIMEOUT is currently
	 * a function of Host processor speed.
	 */
	ret = ath10k_sdio_bmi_get_rx_lookahead(ar);
	अगर (ret)
		वापस ret;

	/* We always पढ़ो from the start of the mbox address */
	addr = ar_sdio->mbox_info.htc_addr;
	ret = ath10k_sdio_पढ़ो(ar, addr, ar_sdio->bmi_buf, *resp_len);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "unable to read the bmi data from the device: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	स_नकल(resp, ar_sdio->bmi_buf, *resp_len);

	वापस 0;
पूर्ण

/* sdio async handling functions */

अटल काष्ठा ath10k_sdio_bus_request
*ath10k_sdio_alloc_busreq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_bus_request *bus_req;

	spin_lock_bh(&ar_sdio->lock);

	अगर (list_empty(&ar_sdio->bus_req_मुक्तq)) अणु
		bus_req = शून्य;
		जाओ out;
	पूर्ण

	bus_req = list_first_entry(&ar_sdio->bus_req_मुक्तq,
				   काष्ठा ath10k_sdio_bus_request, list);
	list_del(&bus_req->list);

out:
	spin_unlock_bh(&ar_sdio->lock);
	वापस bus_req;
पूर्ण

अटल व्योम ath10k_sdio_मुक्त_bus_req(काष्ठा ath10k *ar,
				     काष्ठा ath10k_sdio_bus_request *bus_req)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);

	स_रखो(bus_req, 0, माप(*bus_req));

	spin_lock_bh(&ar_sdio->lock);
	list_add_tail(&bus_req->list, &ar_sdio->bus_req_मुक्तq);
	spin_unlock_bh(&ar_sdio->lock);
पूर्ण

अटल व्योम __ath10k_sdio_ग_लिखो_async(काष्ठा ath10k *ar,
				      काष्ठा ath10k_sdio_bus_request *req)
अणु
	काष्ठा ath10k_htc_ep *ep;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = req->skb;
	ret = ath10k_sdio_ग_लिखो(ar, req->address, skb->data, skb->len);
	अगर (ret)
		ath10k_warn(ar, "failed to write skb to 0x%x asynchronously: %d",
			    req->address, ret);

	अगर (req->htc_msg) अणु
		ep = &ar->htc.endpoपूर्णांक[req->eid];
		ath10k_htc_notअगरy_tx_completion(ep, skb);
	पूर्ण अन्यथा अगर (req->comp) अणु
		complete(req->comp);
	पूर्ण

	ath10k_sdio_मुक्त_bus_req(ar, req);
पूर्ण

/* To improve throughput use workqueue to deliver packets to HTC layer,
 * this way SDIO bus is utilised much better.
 */
अटल व्योम ath10k_rx_indication_async_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_sdio *ar_sdio = container_of(work, काष्ठा ath10k_sdio,
						   async_work_rx);
	काष्ठा ath10k *ar = ar_sdio->ar;
	काष्ठा ath10k_htc_ep *ep;
	काष्ठा ath10k_skb_rxcb *cb;
	काष्ठा sk_buff *skb;

	जबतक (true) अणु
		skb = skb_dequeue(&ar_sdio->rx_head);
		अगर (!skb)
			अवरोध;
		cb = ATH10K_SKB_RXCB(skb);
		ep = &ar->htc.endpoपूर्णांक[cb->eid];
		ep->ep_ops.ep_rx_complete(ar, skb);
	पूर्ण

	अगर (test_bit(ATH10K_FLAG_CORE_REGISTERED, &ar->dev_flags))
		napi_schedule(&ar->napi);
पूर्ण

अटल पूर्णांक ath10k_sdio_पढ़ो_rtc_state(काष्ठा ath10k_sdio *ar_sdio, अचिन्हित अक्षर *state)
अणु
	काष्ठा ath10k *ar = ar_sdio->ar;
	अचिन्हित अक्षर rtc_state = 0;
	पूर्णांक ret = 0;

	rtc_state = sdio_f0_पढ़ोb(ar_sdio->func, ATH10K_CIS_RTC_STATE_ADDR, &ret);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read rtc state: %d\n", ret);
		वापस ret;
	पूर्ण

	*state = rtc_state & 0x3;

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_set_mbox_sleep(काष्ठा ath10k *ar, bool enable_sleep)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 val;
	पूर्णांक retry = ATH10K_CIS_READ_RETRY, ret = 0;
	अचिन्हित अक्षर rtc_state = 0;

	sdio_claim_host(ar_sdio->func);

	ret = ath10k_sdio_पढ़ो32(ar, ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL, &val);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read fifo/chip control register: %d\n",
			    ret);
		जाओ release;
	पूर्ण

	अगर (enable_sleep) अणु
		val &= ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL_DISABLE_SLEEP_OFF;
		ar_sdio->mbox_state = SDIO_MBOX_SLEEP_STATE;
	पूर्ण अन्यथा अणु
		val |= ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL_DISABLE_SLEEP_ON;
		ar_sdio->mbox_state = SDIO_MBOX_AWAKE_STATE;
	पूर्ण

	ret = ath10k_sdio_ग_लिखो32(ar, ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL, val);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to write to FIFO_TIMEOUT_AND_CHIP_CONTROL: %d",
			    ret);
	पूर्ण

	अगर (!enable_sleep) अणु
		करो अणु
			udelay(ATH10K_CIS_READ_WAIT_4_RTC_CYCLE_IN_US);
			ret = ath10k_sdio_पढ़ो_rtc_state(ar_sdio, &rtc_state);

			अगर (ret) अणु
				ath10k_warn(ar, "failed to disable mbox sleep: %d", ret);
				अवरोध;
			पूर्ण

			ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio read rtc state: %d\n",
				   rtc_state);

			अगर (rtc_state == ATH10K_CIS_RTC_STATE_ON)
				अवरोध;

			udelay(ATH10K_CIS_XTAL_SETTLE_DURATION_IN_US);
			retry--;
		पूर्ण जबतक (retry > 0);
	पूर्ण

release:
	sdio_release_host(ar_sdio->func);

	वापस ret;
पूर्ण

अटल व्योम ath10k_sdio_sleep_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा ath10k_sdio *ar_sdio = from_समयr(ar_sdio, t, sleep_समयr);

	ar_sdio->mbox_state = SDIO_MBOX_REQUEST_TO_SLEEP_STATE;
	queue_work(ar_sdio->workqueue, &ar_sdio->wr_async_work);
पूर्ण

अटल व्योम ath10k_sdio_ग_लिखो_async_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_sdio *ar_sdio = container_of(work, काष्ठा ath10k_sdio,
						   wr_async_work);
	काष्ठा ath10k *ar = ar_sdio->ar;
	काष्ठा ath10k_sdio_bus_request *req, *पंचांगp_req;
	काष्ठा ath10k_mbox_info *mbox_info = &ar_sdio->mbox_info;

	spin_lock_bh(&ar_sdio->wr_async_lock);

	list_क्रम_each_entry_safe(req, पंचांगp_req, &ar_sdio->wr_asyncq, list) अणु
		list_del(&req->list);
		spin_unlock_bh(&ar_sdio->wr_async_lock);

		अगर (req->address >= mbox_info->htc_addr &&
		    ar_sdio->mbox_state == SDIO_MBOX_SLEEP_STATE) अणु
			ath10k_sdio_set_mbox_sleep(ar, false);
			mod_समयr(&ar_sdio->sleep_समयr, jअगरfies +
				  msecs_to_jअगरfies(ATH10K_MIN_SLEEP_INACTIVITY_TIME_MS));
		पूर्ण

		__ath10k_sdio_ग_लिखो_async(ar, req);
		spin_lock_bh(&ar_sdio->wr_async_lock);
	पूर्ण

	spin_unlock_bh(&ar_sdio->wr_async_lock);

	अगर (ar_sdio->mbox_state == SDIO_MBOX_REQUEST_TO_SLEEP_STATE)
		ath10k_sdio_set_mbox_sleep(ar, true);
पूर्ण

अटल पूर्णांक ath10k_sdio_prep_async_req(काष्ठा ath10k *ar, u32 addr,
				      काष्ठा sk_buff *skb,
				      काष्ठा completion *comp,
				      bool htc_msg, क्रमागत ath10k_htc_ep_id eid)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_bus_request *bus_req;

	/* Allocate a bus request क्रम the message and queue it on the
	 * SDIO workqueue.
	 */
	bus_req = ath10k_sdio_alloc_busreq(ar);
	अगर (!bus_req) अणु
		ath10k_warn(ar,
			    "unable to allocate bus request for async request\n");
		वापस -ENOMEM;
	पूर्ण

	bus_req->skb = skb;
	bus_req->eid = eid;
	bus_req->address = addr;
	bus_req->htc_msg = htc_msg;
	bus_req->comp = comp;

	spin_lock_bh(&ar_sdio->wr_async_lock);
	list_add_tail(&bus_req->list, &ar_sdio->wr_asyncq);
	spin_unlock_bh(&ar_sdio->wr_async_lock);

	वापस 0;
पूर्ण

/* IRQ handler */

अटल व्योम ath10k_sdio_irq_handler(काष्ठा sdio_func *func)
अणु
	काष्ठा ath10k_sdio *ar_sdio = sdio_get_drvdata(func);
	काष्ठा ath10k *ar = ar_sdio->ar;
	अचिन्हित दीर्घ समयout;
	bool करोne = false;
	पूर्णांक ret;

	/* Release the host during पूर्णांकerrupts so we can pick it back up when
	 * we process commands.
	 */
	sdio_release_host(ar_sdio->func);

	समयout = jअगरfies + ATH10K_SDIO_HIF_COMMUNICATION_TIMEOUT_HZ;
	करो अणु
		ret = ath10k_sdio_mbox_proc_pending_irqs(ar, &करोne);
		अगर (ret)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout) && !करोne);

	ath10k_mac_tx_push_pending(ar);

	sdio_claim_host(ar_sdio->func);

	अगर (ret && ret != -ECANCELED)
		ath10k_warn(ar, "failed to process pending SDIO interrupts: %d\n",
			    ret);
पूर्ण

/* sdio HIF functions */

अटल पूर्णांक ath10k_sdio_disable_पूर्णांकrs(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	काष्ठा ath10k_sdio_irq_enable_regs *regs = irq_data->irq_en_reg;
	पूर्णांक ret;

	mutex_lock(&irq_data->mtx);

	स_रखो(regs, 0, माप(*regs));
	ret = ath10k_sdio_ग_लिखो(ar, MBOX_INT_STATUS_ENABLE_ADDRESS,
				&regs->पूर्णांक_status_en, माप(*regs));
	अगर (ret)
		ath10k_warn(ar, "unable to disable sdio interrupts: %d\n", ret);

	mutex_unlock(&irq_data->mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_hअगर_घातer_up(काष्ठा ath10k *ar,
				    क्रमागत ath10k_firmware_mode fw_mode)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sdio_func *func = ar_sdio->func;
	पूर्णांक ret;

	अगर (!ar_sdio->is_disabled)
		वापस 0;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio power on\n");

	ret = ath10k_sdio_config(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to config sdio: %d\n", ret);
		वापस ret;
	पूर्ण

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to enable sdio function: %d)\n", ret);
		sdio_release_host(func);
		वापस ret;
	पूर्ण

	sdio_release_host(func);

	/* Wait क्रम hardware to initialise. It should take a lot less than
	 * 20 ms but let's be conservative here.
	 */
	msleep(20);

	ar_sdio->is_disabled = false;

	ret = ath10k_sdio_disable_पूर्णांकrs(ar);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम ath10k_sdio_hअगर_घातer_करोwn(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	पूर्णांक ret;

	अगर (ar_sdio->is_disabled)
		वापस;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio power off\n");

	del_समयr_sync(&ar_sdio->sleep_समयr);
	ath10k_sdio_set_mbox_sleep(ar, true);

	/* Disable the card */
	sdio_claim_host(ar_sdio->func);

	ret = sdio_disable_func(ar_sdio->func);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to disable sdio function: %d\n", ret);
		sdio_release_host(ar_sdio->func);
		वापस;
	पूर्ण

	ret = mmc_hw_reset(ar_sdio->func->card->host);
	अगर (ret)
		ath10k_warn(ar, "unable to reset sdio: %d\n", ret);

	sdio_release_host(ar_sdio->func);

	ar_sdio->is_disabled = true;
पूर्ण

अटल पूर्णांक ath10k_sdio_hअगर_tx_sg(काष्ठा ath10k *ar, u8 pipe_id,
				 काष्ठा ath10k_hअगर_sg_item *items, पूर्णांक n_items)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	क्रमागत ath10k_htc_ep_id eid;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, i;

	eid = pipe_id_to_eid(pipe_id);

	क्रम (i = 0; i < n_items; i++) अणु
		माप_प्रकार padded_len;
		u32 address;

		skb = items[i].transfer_context;
		padded_len = ath10k_sdio_calc_txrx_padded_len(ar_sdio,
							      skb->len);
		skb_trim(skb, padded_len);

		/* Write TX data to the end of the mbox address space */
		address = ar_sdio->mbox_addr[eid] + ar_sdio->mbox_size[eid] -
			  skb->len;
		ret = ath10k_sdio_prep_async_req(ar, address, skb,
						 शून्य, true, eid);
		अगर (ret)
			वापस ret;
	पूर्ण

	queue_work(ar_sdio->workqueue, &ar_sdio->wr_async_work);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_enable_पूर्णांकrs(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	काष्ठा ath10k_sdio_irq_enable_regs *regs = irq_data->irq_en_reg;
	पूर्णांक ret;

	mutex_lock(&irq_data->mtx);

	/* Enable all but CPU पूर्णांकerrupts */
	regs->पूर्णांक_status_en = FIELD_PREP(MBOX_INT_STATUS_ENABLE_ERROR_MASK, 1) |
			      FIELD_PREP(MBOX_INT_STATUS_ENABLE_CPU_MASK, 1) |
			      FIELD_PREP(MBOX_INT_STATUS_ENABLE_COUNTER_MASK, 1);

	/* NOTE: There are some हालs where HIF can करो detection of
	 * pending mbox messages which is disabled now.
	 */
	regs->पूर्णांक_status_en |=
		FIELD_PREP(MBOX_INT_STATUS_ENABLE_MBOX_DATA_MASK, 1);

	/* Set up the CPU Interrupt Status Register, enable CPU sourced पूर्णांकerrupt #0
	 * #0 is used क्रम report निश्चितion from target
	 */
	regs->cpu_पूर्णांक_status_en = FIELD_PREP(MBOX_CPU_STATUS_ENABLE_ASSERT_MASK, 1);

	/* Set up the Error Interrupt status Register */
	regs->err_पूर्णांक_status_en =
		FIELD_PREP(MBOX_ERROR_STATUS_ENABLE_RX_UNDERFLOW_MASK, 1) |
		FIELD_PREP(MBOX_ERROR_STATUS_ENABLE_TX_OVERFLOW_MASK, 1);

	/* Enable Counter पूर्णांकerrupt status रेजिस्टर to get fatal errors क्रम
	 * debugging.
	 */
	regs->cntr_पूर्णांक_status_en =
		FIELD_PREP(MBOX_COUNTER_INT_STATUS_ENABLE_BIT_MASK,
			   ATH10K_SDIO_TARGET_DEBUG_INTR_MASK);

	ret = ath10k_sdio_ग_लिखो(ar, MBOX_INT_STATUS_ENABLE_ADDRESS,
				&regs->पूर्णांक_status_en, माप(*regs));
	अगर (ret)
		ath10k_warn(ar,
			    "failed to update mbox interrupt status register : %d\n",
			    ret);

	mutex_unlock(&irq_data->mtx);
	वापस ret;
पूर्ण

/* HIF diagnostics */

अटल पूर्णांक ath10k_sdio_hअगर_diag_पढ़ो(काष्ठा ath10k *ar, u32 address, व्योम *buf,
				     माप_प्रकार buf_len)
अणु
	पूर्णांक ret;
	व्योम *mem;

	mem = kzalloc(buf_len, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	/* set winकरोw रेजिस्टर to start पढ़ो cycle */
	ret = ath10k_sdio_ग_लिखो32(ar, MBOX_WINDOW_READ_ADDR_ADDRESS, address);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set mbox window read address: %d", ret);
		जाओ out;
	पूर्ण

	/* पढ़ो the data */
	ret = ath10k_sdio_पढ़ो(ar, MBOX_WINDOW_DATA_ADDRESS, mem, buf_len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read from mbox window data address: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	स_नकल(buf, mem, buf_len);

out:
	kमुक्त(mem);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_diag_पढ़ो32(काष्ठा ath10k *ar, u32 address,
				   u32 *value)
अणु
	__le32 *val;
	पूर्णांक ret;

	val = kzalloc(माप(*val), GFP_KERNEL);
	अगर (!val)
		वापस -ENOMEM;

	ret = ath10k_sdio_hअगर_diag_पढ़ो(ar, address, val, माप(*val));
	अगर (ret)
		जाओ out;

	*value = __le32_to_cpu(*val);

out:
	kमुक्त(val);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_hअगर_diag_ग_लिखो_mem(काष्ठा ath10k *ar, u32 address,
					  स्थिर व्योम *data, पूर्णांक nbytes)
अणु
	पूर्णांक ret;

	/* set ग_लिखो data */
	ret = ath10k_sdio_ग_लिखो(ar, MBOX_WINDOW_DATA_ADDRESS, data, nbytes);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "failed to write 0x%p to mbox window data address: %d\n",
			    data, ret);
		वापस ret;
	पूर्ण

	/* set winकरोw रेजिस्टर, which starts the ग_लिखो cycle */
	ret = ath10k_sdio_ग_लिखो32(ar, MBOX_WINDOW_WRITE_ADDR_ADDRESS, address);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set mbox window write address: %d", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_hअगर_start_post(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 addr, val;
	पूर्णांक ret = 0;

	addr = host_पूर्णांकerest_item_address(HI_ITEM(hi_acs_flags));

	ret = ath10k_sdio_diag_पढ़ो32(ar, addr, &val);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to read hi_acs_flags : %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (val & HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_FW_ACK) अणु
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio mailbox swap service enabled\n");
		ar_sdio->swap_mbox = true;
	पूर्ण अन्यथा अणु
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio mailbox swap service disabled\n");
		ar_sdio->swap_mbox = false;
	पूर्ण

	ath10k_sdio_set_mbox_sleep(ar, true);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_get_htt_tx_complete(काष्ठा ath10k *ar)
अणु
	u32 addr, val;
	पूर्णांक ret;

	addr = host_पूर्णांकerest_item_address(HI_ITEM(hi_acs_flags));

	ret = ath10k_sdio_diag_पढ़ो32(ar, addr, &val);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "unable to read hi_acs_flags for htt tx comple : %d\n", ret);
		वापस ret;
	पूर्ण

	ret = (val & HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_FW_ACK);

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio reduce tx complete fw%sack\n",
		   ret ? " " : " not ");

	वापस ret;
पूर्ण

/* HIF start/stop */

अटल पूर्णांक ath10k_sdio_hअगर_start(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	पूर्णांक ret;

	ath10k_core_napi_enable(ar);

	/* Sleep 20 ms beक्रमe HIF पूर्णांकerrupts are disabled.
	 * This will give target plenty of समय to process the BMI करोne
	 * request beक्रमe पूर्णांकerrupts are disabled.
	 */
	msleep(20);
	ret = ath10k_sdio_disable_पूर्णांकrs(ar);
	अगर (ret)
		वापस ret;

	/* eid 0 always uses the lower part of the extended mailbox address
	 * space (ext_info[0].htc_ext_addr).
	 */
	ar_sdio->mbox_addr[0] = ar_sdio->mbox_info.ext_info[0].htc_ext_addr;
	ar_sdio->mbox_size[0] = ar_sdio->mbox_info.ext_info[0].htc_ext_sz;

	sdio_claim_host(ar_sdio->func);

	/* Register the isr */
	ret =  sdio_claim_irq(ar_sdio->func, ath10k_sdio_irq_handler);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to claim sdio interrupt: %d\n", ret);
		sdio_release_host(ar_sdio->func);
		वापस ret;
	पूर्ण

	sdio_release_host(ar_sdio->func);

	ret = ath10k_sdio_enable_पूर्णांकrs(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to enable sdio interrupts: %d\n", ret);

	/* Enable sleep and then disable it again */
	ret = ath10k_sdio_set_mbox_sleep(ar, true);
	अगर (ret)
		वापस ret;

	/* Wait क्रम 20ms क्रम the written value to take effect */
	msleep(20);

	ret = ath10k_sdio_set_mbox_sleep(ar, false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा SDIO_IRQ_DISABLE_TIMEOUT_HZ (3 * HZ)

अटल व्योम ath10k_sdio_irq_disable(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	काष्ठा ath10k_sdio_irq_enable_regs *regs = irq_data->irq_en_reg;
	काष्ठा sk_buff *skb;
	काष्ठा completion irqs_disabled_comp;
	पूर्णांक ret;

	skb = dev_alloc_skb(माप(*regs));
	अगर (!skb)
		वापस;

	mutex_lock(&irq_data->mtx);

	स_रखो(regs, 0, माप(*regs)); /* disable all पूर्णांकerrupts */
	स_नकल(skb->data, regs, माप(*regs));
	skb_put(skb, माप(*regs));

	mutex_unlock(&irq_data->mtx);

	init_completion(&irqs_disabled_comp);
	ret = ath10k_sdio_prep_async_req(ar, MBOX_INT_STATUS_ENABLE_ADDRESS,
					 skb, &irqs_disabled_comp, false, 0);
	अगर (ret)
		जाओ out;

	queue_work(ar_sdio->workqueue, &ar_sdio->wr_async_work);

	/* Wait क्रम the completion of the IRQ disable request.
	 * If there is a समयout we will try to disable irq's anyway.
	 */
	ret = रुको_क्रम_completion_समयout(&irqs_disabled_comp,
					  SDIO_IRQ_DISABLE_TIMEOUT_HZ);
	अगर (!ret)
		ath10k_warn(ar, "sdio irq disable request timed out\n");

	sdio_claim_host(ar_sdio->func);

	ret = sdio_release_irq(ar_sdio->func);
	अगर (ret)
		ath10k_warn(ar, "failed to release sdio interrupt: %d\n", ret);

	sdio_release_host(ar_sdio->func);

out:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम ath10k_sdio_hअगर_stop(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_sdio_bus_request *req, *पंचांगp_req;
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा sk_buff *skb;

	ath10k_sdio_irq_disable(ar);

	cancel_work_sync(&ar_sdio->async_work_rx);

	जबतक ((skb = skb_dequeue(&ar_sdio->rx_head)))
		dev_kमुक्त_skb_any(skb);

	cancel_work_sync(&ar_sdio->wr_async_work);

	spin_lock_bh(&ar_sdio->wr_async_lock);

	/* Free all bus requests that have not been handled */
	list_क्रम_each_entry_safe(req, पंचांगp_req, &ar_sdio->wr_asyncq, list) अणु
		काष्ठा ath10k_htc_ep *ep;

		list_del(&req->list);

		अगर (req->htc_msg) अणु
			ep = &ar->htc.endpoपूर्णांक[req->eid];
			ath10k_htc_notअगरy_tx_completion(ep, req->skb);
		पूर्ण अन्यथा अगर (req->skb) अणु
			kमुक्त_skb(req->skb);
		पूर्ण
		ath10k_sdio_मुक्त_bus_req(ar, req);
	पूर्ण

	spin_unlock_bh(&ar_sdio->wr_async_lock);

	ath10k_core_napi_sync_disable(ar);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक ath10k_sdio_hअगर_suspend(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_sdio_hअगर_resume(काष्ठा ath10k *ar)
अणु
	चयन (ar->state) अणु
	हाल ATH10K_STATE_OFF:
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio resume configuring sdio\n");

		/* need to set sdio settings after घातer is cut from sdio */
		ath10k_sdio_config(ar);
		अवरोध;

	हाल ATH10K_STATE_ON:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ath10k_sdio_hअगर_map_service_to_pipe(काष्ठा ath10k *ar,
					       u16 service_id,
					       u8 *ul_pipe, u8 *dl_pipe)
अणु
	काष्ठा ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	काष्ठा ath10k_htc *htc = &ar->htc;
	u32 htt_addr, wmi_addr, htt_mbox_size, wmi_mbox_size;
	क्रमागत ath10k_htc_ep_id eid;
	bool ep_found = false;
	पूर्णांक i;

	/* For sdio, we are पूर्णांकerested in the mapping between eid
	 * and pipeid rather than service_id to pipe_id.
	 * First we find out which eid has been allocated to the
	 * service...
	 */
	क्रम (i = 0; i < ATH10K_HTC_EP_COUNT; i++) अणु
		अगर (htc->endpoपूर्णांक[i].service_id == service_id) अणु
			eid = htc->endpoपूर्णांक[i].eid;
			ep_found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ep_found)
		वापस -EINVAL;

	/* Then we create the simplest mapping possible between pipeid
	 * and eid
	 */
	*ul_pipe = *dl_pipe = (u8)eid;

	/* Normally, HTT will use the upper part of the extended
	 * mailbox address space (ext_info[1].htc_ext_addr) and WMI ctrl
	 * the lower part (ext_info[0].htc_ext_addr).
	 * If fw wants swapping of mailbox addresses, the opposite is true.
	 */
	अगर (ar_sdio->swap_mbox) अणु
		htt_addr = ar_sdio->mbox_info.ext_info[0].htc_ext_addr;
		wmi_addr = ar_sdio->mbox_info.ext_info[1].htc_ext_addr;
		htt_mbox_size = ar_sdio->mbox_info.ext_info[0].htc_ext_sz;
		wmi_mbox_size = ar_sdio->mbox_info.ext_info[1].htc_ext_sz;
	पूर्ण अन्यथा अणु
		htt_addr = ar_sdio->mbox_info.ext_info[1].htc_ext_addr;
		wmi_addr = ar_sdio->mbox_info.ext_info[0].htc_ext_addr;
		htt_mbox_size = ar_sdio->mbox_info.ext_info[1].htc_ext_sz;
		wmi_mbox_size = ar_sdio->mbox_info.ext_info[0].htc_ext_sz;
	पूर्ण

	चयन (service_id) अणु
	हाल ATH10K_HTC_SVC_ID_RSVD_CTRL:
		/* HTC ctrl ep mbox address has alपढ़ोy been setup in
		 * ath10k_sdio_hअगर_start
		 */
		अवरोध;
	हाल ATH10K_HTC_SVC_ID_WMI_CONTROL:
		ar_sdio->mbox_addr[eid] = wmi_addr;
		ar_sdio->mbox_size[eid] = wmi_mbox_size;
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio wmi ctrl mbox_addr 0x%x mbox_size %d\n",
			   ar_sdio->mbox_addr[eid], ar_sdio->mbox_size[eid]);
		अवरोध;
	हाल ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		ar_sdio->mbox_addr[eid] = htt_addr;
		ar_sdio->mbox_size[eid] = htt_mbox_size;
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio htt data mbox_addr 0x%x mbox_size %d\n",
			   ar_sdio->mbox_addr[eid], ar_sdio->mbox_size[eid]);
		अवरोध;
	शेष:
		ath10k_warn(ar, "unsupported HTC service id: %d\n",
			    service_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_sdio_hअगर_get_शेष_pipe(काष्ठा ath10k *ar,
					     u8 *ul_pipe, u8 *dl_pipe)
अणु
	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio hif get default pipe\n");

	/* HTC ctrl ep (SVC id 1) always has eid (and pipe_id in our
	 * हाल) == 0
	 */
	*ul_pipe = 0;
	*dl_pipe = 0;
पूर्ण

अटल स्थिर काष्ठा ath10k_hअगर_ops ath10k_sdio_hअगर_ops = अणु
	.tx_sg			= ath10k_sdio_hअगर_tx_sg,
	.diag_पढ़ो		= ath10k_sdio_hअगर_diag_पढ़ो,
	.diag_ग_लिखो		= ath10k_sdio_hअगर_diag_ग_लिखो_mem,
	.exchange_bmi_msg	= ath10k_sdio_bmi_exchange_msg,
	.start			= ath10k_sdio_hअगर_start,
	.stop			= ath10k_sdio_hअगर_stop,
	.start_post		= ath10k_sdio_hअगर_start_post,
	.get_htt_tx_complete	= ath10k_sdio_get_htt_tx_complete,
	.map_service_to_pipe	= ath10k_sdio_hअगर_map_service_to_pipe,
	.get_शेष_pipe	= ath10k_sdio_hअगर_get_शेष_pipe,
	.घातer_up		= ath10k_sdio_hअगर_घातer_up,
	.घातer_करोwn		= ath10k_sdio_hअगर_घातer_करोwn,
#अगर_घोषित CONFIG_PM
	.suspend		= ath10k_sdio_hअगर_suspend,
	.resume			= ath10k_sdio_hअगर_resume,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP

/* Empty handlers so that mmc subप्रणाली करोesn't हटाओ us entirely during
 * suspend. We instead follow cfg80211 suspend/resume handlers.
 */
अटल पूर्णांक ath10k_sdio_pm_suspend(काष्ठा device *device)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(device);
	काष्ठा ath10k_sdio *ar_sdio = sdio_get_drvdata(func);
	काष्ठा ath10k *ar = ar_sdio->ar;
	mmc_pm_flag_t pm_flag, pm_caps;
	पूर्णांक ret;

	अगर (!device_may_wakeup(ar->dev))
		वापस 0;

	ath10k_sdio_set_mbox_sleep(ar, true);

	pm_flag = MMC_PM_KEEP_POWER;

	ret = sdio_set_host_pm_flags(func, pm_flag);
	अगर (ret) अणु
		pm_caps = sdio_get_host_pm_caps(func);
		ath10k_warn(ar, "failed to set sdio host pm flags (0x%x, 0x%x): %d\n",
			    pm_flag, pm_caps, ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_pm_resume(काष्ठा device *device)
अणु
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ath10k_sdio_pm_ops, ath10k_sdio_pm_suspend,
			 ath10k_sdio_pm_resume);

#घोषणा ATH10K_SDIO_PM_OPS (&ath10k_sdio_pm_ops)

#अन्यथा

#घोषणा ATH10K_SDIO_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक ath10k_sdio_napi_poll(काष्ठा napi_काष्ठा *ctx, पूर्णांक budget)
अणु
	काष्ठा ath10k *ar = container_of(ctx, काष्ठा ath10k, napi);
	पूर्णांक करोne;

	करोne = ath10k_htt_rx_hl_indication(ar, budget);
	ath10k_dbg(ar, ATH10K_DBG_SDIO, "napi poll: done: %d, budget:%d\n", करोne, budget);

	अगर (करोne < budget)
		napi_complete_करोne(ctx, करोne);

	वापस करोne;
पूर्ण

अटल पूर्णांक ath10k_sdio_पढ़ो_host_पूर्णांकerest_value(काष्ठा ath10k *ar,
						u32 item_offset,
						u32 *val)
अणु
	u32 addr;
	पूर्णांक ret;

	addr = host_पूर्णांकerest_item_address(item_offset);

	ret = ath10k_sdio_diag_पढ़ो32(ar, addr, val);

	अगर (ret)
		ath10k_warn(ar, "unable to read host interest offset %d value\n",
			    item_offset);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_sdio_पढ़ो_mem(काष्ठा ath10k *ar, u32 address, व्योम *buf,
				u32 buf_len)
अणु
	u32 val;
	पूर्णांक i, ret;

	क्रम (i = 0; i < buf_len; i += 4) अणु
		ret = ath10k_sdio_diag_पढ़ो32(ar, address + i, &val);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to read mem %d value\n", address + i);
			अवरोध;
		पूर्ण
		स_नकल(buf + i, &val, 4);
	पूर्ण

	वापस ret;
पूर्ण

अटल bool ath10k_sdio_is_fast_dump_supported(काष्ठा ath10k *ar)
अणु
	u32 param;

	ath10k_sdio_पढ़ो_host_पूर्णांकerest_value(ar, HI_ITEM(hi_option_flag2), &param);

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio hi_option_flag2 %x\n", param);

	वापस !!(param & HI_OPTION_SDIO_CRASH_DUMP_ENHANCEMENT_FW);
पूर्ण

अटल व्योम ath10k_sdio_dump_रेजिस्टरs(काष्ठा ath10k *ar,
				       काष्ठा ath10k_fw_crash_data *crash_data,
				       bool fast_dump)
अणु
	u32 reg_dump_values[REG_DUMP_COUNT_QCA988X] = अणुपूर्ण;
	पूर्णांक i, ret;
	u32 reg_dump_area;

	ret = ath10k_sdio_पढ़ो_host_पूर्णांकerest_value(ar, HI_ITEM(hi_failure_state),
						   &reg_dump_area);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read firmware dump area: %d\n", ret);
		वापस;
	पूर्ण

	अगर (fast_dump)
		ret = ath10k_bmi_पढ़ो_memory(ar, reg_dump_area, reg_dump_values,
					     माप(reg_dump_values));
	अन्यथा
		ret = ath10k_sdio_पढ़ो_mem(ar, reg_dump_area, reg_dump_values,
					   माप(reg_dump_values));

	अगर (ret) अणु
		ath10k_warn(ar, "failed to read firmware dump value: %d\n", ret);
		वापस;
	पूर्ण

	ath10k_err(ar, "firmware register dump:\n");
	क्रम (i = 0; i < ARRAY_SIZE(reg_dump_values); i += 4)
		ath10k_err(ar, "[%02d]: 0x%08X 0x%08X 0x%08X 0x%08X\n",
			   i,
			   reg_dump_values[i],
			   reg_dump_values[i + 1],
			   reg_dump_values[i + 2],
			   reg_dump_values[i + 3]);

	अगर (!crash_data)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(reg_dump_values); i++)
		crash_data->रेजिस्टरs[i] = __cpu_to_le32(reg_dump_values[i]);
पूर्ण

अटल पूर्णांक ath10k_sdio_dump_memory_section(काष्ठा ath10k *ar,
					   स्थिर काष्ठा ath10k_mem_region *mem_region,
					   u8 *buf, माप_प्रकार buf_len)
अणु
	स्थिर काष्ठा ath10k_mem_section *cur_section, *next_section;
	अचिन्हित पूर्णांक count, section_size, skip_size;
	पूर्णांक ret, i, j;

	अगर (!mem_region || !buf)
		वापस 0;

	cur_section = &mem_region->section_table.sections[0];

	अगर (mem_region->start > cur_section->start) अणु
		ath10k_warn(ar, "incorrect memdump region 0x%x with section start address 0x%x.\n",
			    mem_region->start, cur_section->start);
		वापस 0;
	पूर्ण

	skip_size = cur_section->start - mem_region->start;

	/* fill the gap between the first रेजिस्टर section and रेजिस्टर
	 * start address
	 */
	क्रम (i = 0; i < skip_size; i++) अणु
		*buf = ATH10K_MAGIC_NOT_COPIED;
		buf++;
	पूर्ण

	count = 0;
	i = 0;
	क्रम (; cur_section; cur_section = next_section) अणु
		section_size = cur_section->end - cur_section->start;

		अगर (section_size <= 0) अणु
			ath10k_warn(ar, "incorrect ramdump format with start address 0x%x and stop address 0x%x\n",
				    cur_section->start,
				    cur_section->end);
			अवरोध;
		पूर्ण

		अगर (++i == mem_region->section_table.size) अणु
			/* last section */
			next_section = शून्य;
			skip_size = 0;
		पूर्ण अन्यथा अणु
			next_section = cur_section + 1;

			अगर (cur_section->end > next_section->start) अणु
				ath10k_warn(ar, "next ramdump section 0x%x is smaller than current end address 0x%x\n",
					    next_section->start,
					    cur_section->end);
				अवरोध;
			पूर्ण

			skip_size = next_section->start - cur_section->end;
		पूर्ण

		अगर (buf_len < (skip_size + section_size)) अणु
			ath10k_warn(ar, "ramdump buffer is too small: %zu\n", buf_len);
			अवरोध;
		पूर्ण

		buf_len -= skip_size + section_size;

		/* पढ़ो section to dest memory */
		ret = ath10k_sdio_पढ़ो_mem(ar, cur_section->start,
					   buf, section_size);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to read ramdump from section 0x%x: %d\n",
				    cur_section->start, ret);
			अवरोध;
		पूर्ण

		buf += section_size;
		count += section_size;

		/* fill in the gap between this section and the next */
		क्रम (j = 0; j < skip_size; j++) अणु
			*buf = ATH10K_MAGIC_NOT_COPIED;
			buf++;
		पूर्ण

		count += skip_size;
	पूर्ण

	वापस count;
पूर्ण

/* अगर an error happened वापसs < 0, otherwise the length */
अटल पूर्णांक ath10k_sdio_dump_memory_generic(काष्ठा ath10k *ar,
					   स्थिर काष्ठा ath10k_mem_region *current_region,
					   u8 *buf,
					   bool fast_dump)
अणु
	पूर्णांक ret;

	अगर (current_region->section_table.size > 0)
		/* Copy each section inभागidually. */
		वापस ath10k_sdio_dump_memory_section(ar,
						      current_region,
						      buf,
						      current_region->len);

	/* No inभागidiual memory sections defined so we can
	 * copy the entire memory region.
	 */
	अगर (fast_dump)
		ret = ath10k_bmi_पढ़ो_memory(ar,
					     current_region->start,
					     buf,
					     current_region->len);
	अन्यथा
		ret = ath10k_sdio_पढ़ो_mem(ar,
					   current_region->start,
					   buf,
					   current_region->len);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to copy ramdump region %s: %d\n",
			    current_region->name, ret);
		वापस ret;
	पूर्ण

	वापस current_region->len;
पूर्ण

अटल व्योम ath10k_sdio_dump_memory(काष्ठा ath10k *ar,
				    काष्ठा ath10k_fw_crash_data *crash_data,
				    bool fast_dump)
अणु
	स्थिर काष्ठा ath10k_hw_mem_layout *mem_layout;
	स्थिर काष्ठा ath10k_mem_region *current_region;
	काष्ठा ath10k_dump_ram_data_hdr *hdr;
	u32 count;
	माप_प्रकार buf_len;
	पूर्णांक ret, i;
	u8 *buf;

	अगर (!crash_data)
		वापस;

	mem_layout = ath10k_coredump_get_mem_layout(ar);
	अगर (!mem_layout)
		वापस;

	current_region = &mem_layout->region_table.regions[0];

	buf = crash_data->ramdump_buf;
	buf_len = crash_data->ramdump_buf_len;

	स_रखो(buf, 0, buf_len);

	क्रम (i = 0; i < mem_layout->region_table.size; i++) अणु
		count = 0;

		अगर (current_region->len > buf_len) अणु
			ath10k_warn(ar, "memory region %s size %d is larger that remaining ramdump buffer size %zu\n",
				    current_region->name,
				    current_region->len,
				    buf_len);
			अवरोध;
		पूर्ण

		/* Reserve space क्रम the header. */
		hdr = (व्योम *)buf;
		buf += माप(*hdr);
		buf_len -= माप(*hdr);

		ret = ath10k_sdio_dump_memory_generic(ar, current_region, buf,
						      fast_dump);
		अगर (ret >= 0)
			count = ret;

		hdr->region_type = cpu_to_le32(current_region->type);
		hdr->start = cpu_to_le32(current_region->start);
		hdr->length = cpu_to_le32(count);

		अगर (count == 0)
			/* Note: the header reमुख्यs, just with zero length. */
			अवरोध;

		buf += count;
		buf_len -= count;

		current_region++;
	पूर्ण
पूर्ण

व्योम ath10k_sdio_fw_crashed_dump(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_fw_crash_data *crash_data;
	अक्षर guid[UUID_STRING_LEN + 1];
	bool fast_dump;

	fast_dump = ath10k_sdio_is_fast_dump_supported(ar);

	अगर (fast_dump)
		ath10k_bmi_start(ar);

	ar->stats.fw_crash_counter++;

	ath10k_sdio_disable_पूर्णांकrs(ar);

	crash_data = ath10k_coredump_new(ar);

	अगर (crash_data)
		scnम_लिखो(guid, माप(guid), "%pUl", &crash_data->guid);
	अन्यथा
		scnम_लिखो(guid, माप(guid), "n/a");

	ath10k_err(ar, "firmware crashed! (guid %s)\n", guid);
	ath10k_prपूर्णांक_driver_info(ar);
	ath10k_sdio_dump_रेजिस्टरs(ar, crash_data, fast_dump);
	ath10k_sdio_dump_memory(ar, crash_data, fast_dump);

	ath10k_sdio_enable_पूर्णांकrs(ar);

	ath10k_core_start_recovery(ar);
पूर्ण

अटल पूर्णांक ath10k_sdio_probe(काष्ठा sdio_func *func,
			     स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा ath10k_sdio *ar_sdio;
	काष्ठा ath10k *ar;
	क्रमागत ath10k_hw_rev hw_rev;
	u32 dev_id_base;
	काष्ठा ath10k_bus_params bus_params = अणुपूर्ण;
	पूर्णांक ret, i;

	/* Assumption: All SDIO based chipsets (so far) are QCA6174 based.
	 * If there will be newer chipsets that करोes not use the hw reg
	 * setup as defined in qca6174_regs and qca6174_values, this
	 * assumption is no दीर्घer valid and hw_rev must be setup dअगरferently
	 * depending on chipset.
	 */
	hw_rev = ATH10K_HW_QCA6174;

	ar = ath10k_core_create(माप(*ar_sdio), &func->dev, ATH10K_BUS_SDIO,
				hw_rev, &ath10k_sdio_hअगर_ops);
	अगर (!ar) अणु
		dev_err(&func->dev, "failed to allocate core\n");
		वापस -ENOMEM;
	पूर्ण

	netअगर_napi_add(&ar->napi_dev, &ar->napi, ath10k_sdio_napi_poll,
		       ATH10K_NAPI_BUDGET);

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "sdio new func %d vendor 0x%x device 0x%x block 0x%x/0x%x\n",
		   func->num, func->venकरोr, func->device,
		   func->max_blksize, func->cur_blksize);

	ar_sdio = ath10k_sdio_priv(ar);

	ar_sdio->irq_data.irq_proc_reg =
		devm_kzalloc(ar->dev, माप(काष्ठा ath10k_sdio_irq_proc_regs),
			     GFP_KERNEL);
	अगर (!ar_sdio->irq_data.irq_proc_reg) अणु
		ret = -ENOMEM;
		जाओ err_core_destroy;
	पूर्ण

	ar_sdio->vsg_buffer = devm_kदो_स्मृति(ar->dev, ATH10K_SDIO_VSG_BUF_SIZE, GFP_KERNEL);
	अगर (!ar_sdio->vsg_buffer) अणु
		ret = -ENOMEM;
		जाओ err_core_destroy;
	पूर्ण

	ar_sdio->irq_data.irq_en_reg =
		devm_kzalloc(ar->dev, माप(काष्ठा ath10k_sdio_irq_enable_regs),
			     GFP_KERNEL);
	अगर (!ar_sdio->irq_data.irq_en_reg) अणु
		ret = -ENOMEM;
		जाओ err_core_destroy;
	पूर्ण

	ar_sdio->bmi_buf = devm_kzalloc(ar->dev, BMI_MAX_LARGE_CMDBUF_SIZE, GFP_KERNEL);
	अगर (!ar_sdio->bmi_buf) अणु
		ret = -ENOMEM;
		जाओ err_core_destroy;
	पूर्ण

	ar_sdio->func = func;
	sdio_set_drvdata(func, ar_sdio);

	ar_sdio->is_disabled = true;
	ar_sdio->ar = ar;

	spin_lock_init(&ar_sdio->lock);
	spin_lock_init(&ar_sdio->wr_async_lock);
	mutex_init(&ar_sdio->irq_data.mtx);

	INIT_LIST_HEAD(&ar_sdio->bus_req_मुक्तq);
	INIT_LIST_HEAD(&ar_sdio->wr_asyncq);

	INIT_WORK(&ar_sdio->wr_async_work, ath10k_sdio_ग_लिखो_async_work);
	ar_sdio->workqueue = create_singlethपढ़ो_workqueue("ath10k_sdio_wq");
	अगर (!ar_sdio->workqueue) अणु
		ret = -ENOMEM;
		जाओ err_core_destroy;
	पूर्ण

	क्रम (i = 0; i < ATH10K_SDIO_BUS_REQUEST_MAX_NUM; i++)
		ath10k_sdio_मुक्त_bus_req(ar, &ar_sdio->bus_req[i]);

	skb_queue_head_init(&ar_sdio->rx_head);
	INIT_WORK(&ar_sdio->async_work_rx, ath10k_rx_indication_async_work);

	dev_id_base = (id->device & 0x0F00);
	अगर (dev_id_base != (SDIO_DEVICE_ID_ATHEROS_AR6005 & 0x0F00) &&
	    dev_id_base != (SDIO_DEVICE_ID_ATHEROS_QCA9377 & 0x0F00)) अणु
		ret = -ENODEV;
		ath10k_err(ar, "unsupported device id %u (0x%x)\n",
			   dev_id_base, id->device);
		जाओ err_मुक्त_wq;
	पूर्ण

	ar->dev_id = QCA9377_1_0_DEVICE_ID;
	ar->id.venकरोr = id->venकरोr;
	ar->id.device = id->device;

	ath10k_sdio_set_mbox_info(ar);

	bus_params.dev_type = ATH10K_DEV_TYPE_HL;
	/* TODO: करोn't know yet how to get chip_id with SDIO */
	bus_params.chip_id = 0;
	bus_params.hl_msdu_ids = true;

	ar->hw->max_mtu = ETH_DATA_LEN;

	ret = ath10k_core_रेजिस्टर(ar, &bus_params);
	अगर (ret) अणु
		ath10k_err(ar, "failed to register driver core: %d\n", ret);
		जाओ err_मुक्त_wq;
	पूर्ण

	समयr_setup(&ar_sdio->sleep_समयr, ath10k_sdio_sleep_समयr_handler, 0);

	वापस 0;

err_मुक्त_wq:
	destroy_workqueue(ar_sdio->workqueue);
err_core_destroy:
	ath10k_core_destroy(ar);

	वापस ret;
पूर्ण

अटल व्योम ath10k_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा ath10k_sdio *ar_sdio = sdio_get_drvdata(func);
	काष्ठा ath10k *ar = ar_sdio->ar;

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "sdio removed func %d vendor 0x%x device 0x%x\n",
		   func->num, func->venकरोr, func->device);

	ath10k_core_unरेजिस्टर(ar);

	netअगर_napi_del(&ar->napi);

	ath10k_core_destroy(ar);

	flush_workqueue(ar_sdio->workqueue);
	destroy_workqueue(ar_sdio->workqueue);
पूर्ण

अटल स्थिर काष्ठा sdio_device_id ath10k_sdio_devices[] = अणु
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_AR6005)पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_ATHEROS, SDIO_DEVICE_ID_ATHEROS_QCA9377)पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(sdio, ath10k_sdio_devices);

अटल काष्ठा sdio_driver ath10k_sdio_driver = अणु
	.name = "ath10k_sdio",
	.id_table = ath10k_sdio_devices,
	.probe = ath10k_sdio_probe,
	.हटाओ = ath10k_sdio_हटाओ,
	.drv = अणु
		.owner = THIS_MODULE,
		.pm = ATH10K_SDIO_PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ath10k_sdio_init(व्योम)
अणु
	पूर्णांक ret;

	ret = sdio_रेजिस्टर_driver(&ath10k_sdio_driver);
	अगर (ret)
		pr_err("sdio driver registration failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम __निकास ath10k_sdio_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&ath10k_sdio_driver);
पूर्ण

module_init(ath10k_sdio_init);
module_निकास(ath10k_sdio_निकास);

MODULE_AUTHOR("Qualcomm Atheros");
MODULE_DESCRIPTION("Driver support for Qualcomm Atheros 802.11ac WLAN SDIO devices");
MODULE_LICENSE("Dual BSD/GPL");
