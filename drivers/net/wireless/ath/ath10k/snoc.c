<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of_address.h>
#समावेश <linux/iommu.h>

#समावेश "ce.h"
#समावेश "coredump.h"
#समावेश "debug.h"
#समावेश "hif.h"
#समावेश "htc.h"
#समावेश "snoc.h"

#घोषणा ATH10K_SNOC_RX_POST_RETRY_MS 50
#घोषणा CE_POLL_PIPE 4
#घोषणा ATH10K_SNOC_WAKE_IRQ 2

अटल अक्षर *स्थिर ce_name[] = अणु
	"WLAN_CE_0",
	"WLAN_CE_1",
	"WLAN_CE_2",
	"WLAN_CE_3",
	"WLAN_CE_4",
	"WLAN_CE_5",
	"WLAN_CE_6",
	"WLAN_CE_7",
	"WLAN_CE_8",
	"WLAN_CE_9",
	"WLAN_CE_10",
	"WLAN_CE_11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ath10k_regulators[] = अणु
	"vdd-0.8-cx-mx",
	"vdd-1.8-xo",
	"vdd-1.3-rfa",
	"vdd-3.3-ch0",
	"vdd-3.3-ch1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ath10k_घड़ीs[] = अणु
	"cxo_ref_clk_pin", "qdss",
पूर्ण;

अटल व्योम ath10k_snoc_htc_tx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_snoc_htt_tx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_snoc_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_snoc_htt_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_snoc_htt_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_snoc_pktlog_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);

अटल स्थिर काष्ठा ath10k_snoc_drv_priv drv_priv = अणु
	.hw_rev = ATH10K_HW_WCN3990,
	.dma_mask = DMA_BIT_MASK(35),
	.msa_size = 0x100000,
पूर्ण;

#घोषणा WCN3990_SRC_WR_IDX_OFFSET 0x3C
#घोषणा WCN3990_DST_WR_IDX_OFFSET 0x40

अटल काष्ठा ath10k_shaकरोw_reg_cfg target_shaकरोw_reg_cfg_map[] = अणु
		अणु
			.ce_id = __cpu_to_le16(0),
			.reg_offset = __cpu_to_le16(WCN3990_SRC_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(3),
			.reg_offset = __cpu_to_le16(WCN3990_SRC_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(4),
			.reg_offset = __cpu_to_le16(WCN3990_SRC_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(5),
			.reg_offset =  __cpu_to_le16(WCN3990_SRC_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(7),
			.reg_offset = __cpu_to_le16(WCN3990_SRC_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(1),
			.reg_offset = __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(2),
			.reg_offset =  __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(7),
			.reg_offset =  __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(8),
			.reg_offset =  __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(9),
			.reg_offset = __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(10),
			.reg_offset =  __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,

		अणु
			.ce_id = __cpu_to_le16(11),
			.reg_offset = __cpu_to_le16(WCN3990_DST_WR_IDX_OFFSET),
		पूर्ण,
पूर्ण;

अटल काष्ठा ce_attr host_ce_config_wlan[] = अणु
	/* CE0: host->target HTC control streams */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 16,
		.src_sz_max = 2048,
		.dest_nentries = 0,
		.send_cb = ath10k_snoc_htc_tx_cb,
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath10k_snoc_htt_htc_rx_cb,
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 64,
		.recv_cb = ath10k_snoc_htc_rx_cb,
	पूर्ण,

	/* CE3: host->target WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
		.send_cb = ath10k_snoc_htc_tx_cb,
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = 2048,
		.src_sz_max = 256,
		.dest_nentries = 0,
		.send_cb = ath10k_snoc_htt_tx_cb,
	पूर्ण,

	/* CE5: target->host HTT (ipa_uc->target ) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 512,
		.dest_nentries = 512,
		.recv_cb = ath10k_snoc_htt_rx_cb,
	पूर्ण,

	/* CE6: target स्वतःnomous hअगर_स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE7: ce_diag, the Diagnostic Winकरोw */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 2,
		.src_sz_max = 2048,
		.dest_nentries = 2,
	पूर्ण,

	/* CE8: Target to uMC */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 128,
	पूर्ण,

	/* CE9 target->host HTT */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath10k_snoc_htt_htc_rx_cb,
	पूर्ण,

	/* CE10: target->host HTT */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath10k_snoc_htt_htc_rx_cb,
	पूर्ण,

	/* CE11: target -> host PKTLOG */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath10k_snoc_pktlog_rx_cb,
	पूर्ण,
पूर्ण;

अटल काष्ठा ce_pipe_config target_ce_config_wlan[] = अणु
	/* CE0: host->target HTC control and raw streams */
	अणु
		.pipक्रमागत = __cpu_to_le32(0),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.pipक्रमागत = __cpu_to_le32(1),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.pipक्रमागत = __cpu_to_le32(2),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(64),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE3: host->target WMI */
	अणु
		.pipक्रमागत = __cpu_to_le32(3),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.pipक्रमागत = __cpu_to_le32(4),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(256),
		.nbytes_max = __cpu_to_le32(256),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE5: target->host HTT (HIF->HTT) */
	अणु
		.pipक्रमागत = __cpu_to_le32(5),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(1024),
		.nbytes_max = __cpu_to_le32(64),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE6: Reserved क्रम target स्वतःnomous hअगर_स_नकल */
	अणु
		.pipक्रमागत = __cpu_to_le32(6),
		.pipedir = __cpu_to_le32(PIPEसूची_INOUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(16384),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE7 used only by Host */
	अणु
		.pipक्रमागत = __cpu_to_le32(7),
		.pipedir = __cpu_to_le32(4),
		.nentries = __cpu_to_le32(0),
		.nbytes_max = __cpu_to_le32(0),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE8 Target to uMC */
	अणु
		.pipक्रमागत = __cpu_to_le32(8),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(0),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE9 target->host HTT */
	अणु
		.pipक्रमागत = __cpu_to_le32(9),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE10 target->host HTT */
	अणु
		.pipक्रमागत = __cpu_to_le32(10),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE11 target स्वतःnomous qcache स_नकल */
	अणु
		.pipक्रमागत = __cpu_to_le32(11),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,
पूर्ण;

अटल काष्ठा ce_service_to_pipe target_service_to_ce_map_wlan[] = अणु
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_CONTROL),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_CONTROL),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_RSVD_CTRL),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(0),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_RSVD_CTRL),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु /* not used */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(0),
	पूर्ण,
	अणु /* not used */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(4),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(1),
	पूर्ण,
	अणु /* not used */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS),
		__cpu_to_le32(PIPEसूची_OUT),
		__cpu_to_le32(5),
	पूर्ण,
	अणु /* in = DL = target -> host */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_DATA2_MSG),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(9),
	पूर्ण,
	अणु /* in = DL = target -> host */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_DATA3_MSG),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(10),
	पूर्ण,
	अणु /* in = DL = target -> host pktlog */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_LOG_MSG),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(11),
	पूर्ण,
	/* (Additions here) */

	अणु /* must be last */
		__cpu_to_le32(0),
		__cpu_to_le32(0),
		__cpu_to_le32(0),
	पूर्ण,
पूर्ण;

अटल व्योम ath10k_snoc_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ioग_लिखो32(value, ar_snoc->mem + offset);
पूर्ण

अटल u32 ath10k_snoc_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	u32 val;

	val = ioपढ़ो32(ar_snoc->mem + offset);

	वापस val;
पूर्ण

अटल पूर्णांक __ath10k_snoc_rx_post_buf(काष्ठा ath10k_snoc_pipe *pipe)
अणु
	काष्ठा ath10k_ce_pipe *ce_pipe = pipe->ce_hdl;
	काष्ठा ath10k *ar = pipe->hअगर_ce_state;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक ret;

	skb = dev_alloc_skb(pipe->buf_sz);
	अगर (!skb)
		वापस -ENOMEM;

	WARN_ONCE((अचिन्हित दीर्घ)skb->data & 3, "unaligned skb");

	paddr = dma_map_single(ar->dev, skb->data,
			       skb->len + skb_tailroom(skb),
			       DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(ar->dev, paddr))) अणु
		ath10k_warn(ar, "failed to dma map snoc rx buf\n");
		dev_kमुक्त_skb_any(skb);
		वापस -EIO;
	पूर्ण

	ATH10K_SKB_RXCB(skb)->paddr = paddr;

	spin_lock_bh(&ce->ce_lock);
	ret = ce_pipe->ops->ce_rx_post_buf(ce_pipe, skb, paddr);
	spin_unlock_bh(&ce->ce_lock);
	अगर (ret) अणु
		dma_unmap_single(ar->dev, paddr, skb->len + skb_tailroom(skb),
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_snoc_rx_post_pipe(काष्ठा ath10k_snoc_pipe *pipe)
अणु
	काष्ठा ath10k *ar = pipe->hअगर_ce_state;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_pipe = pipe->ce_hdl;
	पूर्णांक ret, num;

	अगर (pipe->buf_sz == 0)
		वापस;

	अगर (!ce_pipe->dest_ring)
		वापस;

	spin_lock_bh(&ce->ce_lock);
	num = __ath10k_ce_rx_num_मुक्त_bufs(ce_pipe);
	spin_unlock_bh(&ce->ce_lock);
	जबतक (num--) अणु
		ret = __ath10k_snoc_rx_post_buf(pipe);
		अगर (ret) अणु
			अगर (ret == -ENOSPC)
				अवरोध;
			ath10k_warn(ar, "failed to post rx buf: %d\n", ret);
			mod_समयr(&ar_snoc->rx_post_retry, jअगरfies +
				  ATH10K_SNOC_RX_POST_RETRY_MS);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath10k_snoc_rx_post(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक i;

	क्रम (i = 0; i < CE_COUNT; i++)
		ath10k_snoc_rx_post_pipe(&ar_snoc->pipe_info[i]);
पूर्ण

अटल व्योम ath10k_snoc_process_rx_cb(काष्ठा ath10k_ce_pipe *ce_state,
				      व्योम (*callback)(काष्ठा ath10k *ar,
						       काष्ठा sk_buff *skb))
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_snoc_pipe *pipe_info =  &ar_snoc->pipe_info[ce_state->id];
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head list;
	व्योम *transfer_context;
	अचिन्हित पूर्णांक nbytes, max_nbytes;

	__skb_queue_head_init(&list);
	जबतक (ath10k_ce_completed_recv_next(ce_state, &transfer_context,
					     &nbytes) == 0) अणु
		skb = transfer_context;
		max_nbytes = skb->len + skb_tailroom(skb);
		dma_unmap_single(ar->dev, ATH10K_SKB_RXCB(skb)->paddr,
				 max_nbytes, DMA_FROM_DEVICE);

		अगर (unlikely(max_nbytes < nbytes)) अणु
			ath10k_warn(ar, "rxed more than expected (nbytes %d, max %d)\n",
				    nbytes, max_nbytes);
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		skb_put(skb, nbytes);
		__skb_queue_tail(&list, skb);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&list))) अणु
		ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc rx ce pipe %d len %d\n",
			   ce_state->id, skb->len);

		callback(ar, skb);
	पूर्ण

	ath10k_snoc_rx_post_pipe(pipe_info);
पूर्ण

अटल व्योम ath10k_snoc_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	ath10k_snoc_process_rx_cb(ce_state, ath10k_htc_rx_completion_handler);
पूर्ण

अटल व्योम ath10k_snoc_htt_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	/* CE4 polling needs to be करोne whenever CE pipe which transports
	 * HTT Rx (target->host) is processed.
	 */
	ath10k_ce_per_engine_service(ce_state->ar, CE_POLL_PIPE);

	ath10k_snoc_process_rx_cb(ce_state, ath10k_htc_rx_completion_handler);
पूर्ण

/* Called by lower (CE) layer when data is received from the Target.
 * WCN3990 firmware uses separate CE(CE11) to transfer pktlog data.
 */
अटल व्योम ath10k_snoc_pktlog_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	ath10k_snoc_process_rx_cb(ce_state, ath10k_htc_rx_completion_handler);
पूर्ण

अटल व्योम ath10k_snoc_htt_rx_deliver(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, माप(काष्ठा ath10k_htc_hdr));
	ath10k_htt_t2h_msg_handler(ar, skb);
पूर्ण

अटल व्योम ath10k_snoc_htt_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	ath10k_ce_per_engine_service(ce_state->ar, CE_POLL_PIPE);
	ath10k_snoc_process_rx_cb(ce_state, ath10k_snoc_htt_rx_deliver);
पूर्ण

अटल व्योम ath10k_snoc_rx_replenish_retry(काष्ठा समयr_list *t)
अणु
	काष्ठा ath10k_snoc *ar_snoc = from_समयr(ar_snoc, t, rx_post_retry);
	काष्ठा ath10k *ar = ar_snoc->ar;

	ath10k_snoc_rx_post(ar);
पूर्ण

अटल व्योम ath10k_snoc_htc_tx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&list);
	जबतक (ath10k_ce_completed_send_next(ce_state, (व्योम **)&skb) == 0) अणु
		अगर (!skb)
			जारी;

		__skb_queue_tail(&list, skb);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&list)))
		ath10k_htc_tx_completion_handler(ar, skb);
पूर्ण

अटल व्योम ath10k_snoc_htt_tx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा sk_buff *skb;

	जबतक (ath10k_ce_completed_send_next(ce_state, (व्योम **)&skb) == 0) अणु
		अगर (!skb)
			जारी;

		dma_unmap_single(ar->dev, ATH10K_SKB_CB(skb)->paddr,
				 skb->len, DMA_TO_DEVICE);
		ath10k_htt_hअगर_tx_complete(ar, skb);
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_tx_sg(काष्ठा ath10k *ar, u8 pipe_id,
				 काष्ठा ath10k_hअगर_sg_item *items, पूर्णांक n_items)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_snoc_pipe *snoc_pipe;
	काष्ठा ath10k_ce_pipe *ce_pipe;
	पूर्णांक err, i = 0;

	snoc_pipe = &ar_snoc->pipe_info[pipe_id];
	ce_pipe = snoc_pipe->ce_hdl;
	spin_lock_bh(&ce->ce_lock);

	क्रम (i = 0; i < n_items - 1; i++) अणु
		ath10k_dbg(ar, ATH10K_DBG_SNOC,
			   "snoc tx item %d paddr %pad len %d n_items %d\n",
			   i, &items[i].paddr, items[i].len, n_items);

		err = ath10k_ce_send_nolock(ce_pipe,
					    items[i].transfer_context,
					    items[i].paddr,
					    items[i].len,
					    items[i].transfer_id,
					    CE_SEND_FLAG_GATHER);
		अगर (err)
			जाओ err;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SNOC,
		   "snoc tx item %d paddr %pad len %d n_items %d\n",
		   i, &items[i].paddr, items[i].len, n_items);

	err = ath10k_ce_send_nolock(ce_pipe,
				    items[i].transfer_context,
				    items[i].paddr,
				    items[i].len,
				    items[i].transfer_id,
				    0);
	अगर (err)
		जाओ err;

	spin_unlock_bh(&ce->ce_lock);

	वापस 0;

err:
	क्रम (; i > 0; i--)
		__ath10k_ce_send_revert(ce_pipe);

	spin_unlock_bh(&ce->ce_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_get_target_info(काष्ठा ath10k *ar,
					   काष्ठा bmi_target_info *target_info)
अणु
	target_info->version = ATH10K_HW_WCN3990;
	target_info->type = ATH10K_HW_WCN3990;

	वापस 0;
पूर्ण

अटल u16 ath10k_snoc_hअगर_get_मुक्त_queue_number(काष्ठा ath10k *ar, u8 pipe)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "hif get free queue number\n");

	वापस ath10k_ce_num_मुक्त_src_entries(ar_snoc->pipe_info[pipe].ce_hdl);
पूर्ण

अटल व्योम ath10k_snoc_hअगर_send_complete_check(काष्ठा ath10k *ar, u8 pipe,
						पूर्णांक क्रमce)
अणु
	पूर्णांक resources;

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc hif send complete check\n");

	अगर (!क्रमce) अणु
		resources = ath10k_snoc_hअगर_get_मुक्त_queue_number(ar, pipe);

		अगर (resources > (host_ce_config_wlan[pipe].src_nentries >> 1))
			वापस;
	पूर्ण
	ath10k_ce_per_engine_service(ar, pipe);
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_map_service_to_pipe(काष्ठा ath10k *ar,
					       u16 service_id,
					       u8 *ul_pipe, u8 *dl_pipe)
अणु
	स्थिर काष्ठा ce_service_to_pipe *entry;
	bool ul_set = false, dl_set = false;
	पूर्णांक i;

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc hif map service\n");

	क्रम (i = 0; i < ARRAY_SIZE(target_service_to_ce_map_wlan); i++) अणु
		entry = &target_service_to_ce_map_wlan[i];

		अगर (__le32_to_cpu(entry->service_id) != service_id)
			जारी;

		चयन (__le32_to_cpu(entry->pipedir)) अणु
		हाल PIPEसूची_NONE:
			अवरोध;
		हाल PIPEसूची_IN:
			WARN_ON(dl_set);
			*dl_pipe = __le32_to_cpu(entry->pipक्रमागत);
			dl_set = true;
			अवरोध;
		हाल PIPEसूची_OUT:
			WARN_ON(ul_set);
			*ul_pipe = __le32_to_cpu(entry->pipक्रमागत);
			ul_set = true;
			अवरोध;
		हाल PIPEसूची_INOUT:
			WARN_ON(dl_set);
			WARN_ON(ul_set);
			*dl_pipe = __le32_to_cpu(entry->pipक्रमागत);
			*ul_pipe = __le32_to_cpu(entry->pipक्रमागत);
			dl_set = true;
			ul_set = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ul_set || !dl_set)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल व्योम ath10k_snoc_hअगर_get_शेष_pipe(काष्ठा ath10k *ar,
					     u8 *ul_pipe, u8 *dl_pipe)
अणु
	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc hif get default pipe\n");

	(व्योम)ath10k_snoc_hअगर_map_service_to_pipe(ar,
						 ATH10K_HTC_SVC_ID_RSVD_CTRL,
						 ul_pipe, dl_pipe);
पूर्ण

अटल अंतरभूत व्योम ath10k_snoc_irq_disable(काष्ठा ath10k *ar)
अणु
	ath10k_ce_disable_पूर्णांकerrupts(ar);
पूर्ण

अटल अंतरभूत व्योम ath10k_snoc_irq_enable(काष्ठा ath10k *ar)
अणु
	ath10k_ce_enable_पूर्णांकerrupts(ar);
पूर्ण

अटल व्योम ath10k_snoc_rx_pipe_cleanup(काष्ठा ath10k_snoc_pipe *snoc_pipe)
अणु
	काष्ठा ath10k_ce_pipe *ce_pipe;
	काष्ठा ath10k_ce_ring *ce_ring;
	काष्ठा sk_buff *skb;
	काष्ठा ath10k *ar;
	पूर्णांक i;

	ar = snoc_pipe->hअगर_ce_state;
	ce_pipe = snoc_pipe->ce_hdl;
	ce_ring = ce_pipe->dest_ring;

	अगर (!ce_ring)
		वापस;

	अगर (!snoc_pipe->buf_sz)
		वापस;

	क्रम (i = 0; i < ce_ring->nentries; i++) अणु
		skb = ce_ring->per_transfer_context[i];
		अगर (!skb)
			जारी;

		ce_ring->per_transfer_context[i] = शून्य;

		dma_unmap_single(ar->dev, ATH10K_SKB_RXCB(skb)->paddr,
				 skb->len + skb_tailroom(skb),
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम ath10k_snoc_tx_pipe_cleanup(काष्ठा ath10k_snoc_pipe *snoc_pipe)
अणु
	काष्ठा ath10k_ce_pipe *ce_pipe;
	काष्ठा ath10k_ce_ring *ce_ring;
	काष्ठा sk_buff *skb;
	काष्ठा ath10k *ar;
	पूर्णांक i;

	ar = snoc_pipe->hअगर_ce_state;
	ce_pipe = snoc_pipe->ce_hdl;
	ce_ring = ce_pipe->src_ring;

	अगर (!ce_ring)
		वापस;

	अगर (!snoc_pipe->buf_sz)
		वापस;

	क्रम (i = 0; i < ce_ring->nentries; i++) अणु
		skb = ce_ring->per_transfer_context[i];
		अगर (!skb)
			जारी;

		ce_ring->per_transfer_context[i] = शून्य;

		ath10k_htc_tx_completion_handler(ar, skb);
	पूर्ण
पूर्ण

अटल व्योम ath10k_snoc_buffer_cleanup(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_snoc_pipe *pipe_info;
	पूर्णांक pipe_num;

	del_समयr_sync(&ar_snoc->rx_post_retry);
	क्रम (pipe_num = 0; pipe_num < CE_COUNT; pipe_num++) अणु
		pipe_info = &ar_snoc->pipe_info[pipe_num];
		ath10k_snoc_rx_pipe_cleanup(pipe_info);
		ath10k_snoc_tx_pipe_cleanup(pipe_info);
	पूर्ण
पूर्ण

अटल व्योम ath10k_snoc_hअगर_stop(काष्ठा ath10k *ar)
अणु
	अगर (!test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
		ath10k_snoc_irq_disable(ar);

	ath10k_core_napi_sync_disable(ar);
	ath10k_snoc_buffer_cleanup(ar);
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif stop\n");
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_start(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	biपंचांगap_clear(ar_snoc->pending_ce_irqs, 0, CE_COUNT_MAX);

	ath10k_core_napi_enable(ar);
	ath10k_snoc_irq_enable(ar);
	ath10k_snoc_rx_post(ar);

	clear_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif start\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_snoc_init_pipes(काष्ठा ath10k *ar)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < CE_COUNT; i++) अणु
		ret = ath10k_ce_init_pipe(ar, i, &host_ce_config_wlan[i]);
		अगर (ret) अणु
			ath10k_err(ar, "failed to initialize copy engine pipe %d: %d\n",
				   i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_snoc_wlan_enable(काष्ठा ath10k *ar,
				   क्रमागत ath10k_firmware_mode fw_mode)
अणु
	काष्ठा ath10k_tgt_pipe_cfg tgt_cfg[CE_COUNT_MAX];
	काष्ठा ath10k_qmi_wlan_enable_cfg cfg;
	क्रमागत wlfw_driver_mode_क्रमागत_v01 mode;
	पूर्णांक pipe_num;

	क्रम (pipe_num = 0; pipe_num < CE_COUNT_MAX; pipe_num++) अणु
		tgt_cfg[pipe_num].pipe_num =
				target_ce_config_wlan[pipe_num].pipक्रमागत;
		tgt_cfg[pipe_num].pipe_dir =
				target_ce_config_wlan[pipe_num].pipedir;
		tgt_cfg[pipe_num].nentries =
				target_ce_config_wlan[pipe_num].nentries;
		tgt_cfg[pipe_num].nbytes_max =
				target_ce_config_wlan[pipe_num].nbytes_max;
		tgt_cfg[pipe_num].flags =
				target_ce_config_wlan[pipe_num].flags;
		tgt_cfg[pipe_num].reserved = 0;
	पूर्ण

	cfg.num_ce_tgt_cfg = माप(target_ce_config_wlan) /
				माप(काष्ठा ath10k_tgt_pipe_cfg);
	cfg.ce_tgt_cfg = (काष्ठा ath10k_tgt_pipe_cfg *)
		&tgt_cfg;
	cfg.num_ce_svc_pipe_cfg = माप(target_service_to_ce_map_wlan) /
				  माप(काष्ठा ath10k_svc_pipe_cfg);
	cfg.ce_svc_cfg = (काष्ठा ath10k_svc_pipe_cfg *)
		&target_service_to_ce_map_wlan;
	cfg.num_shaकरोw_reg_cfg = ARRAY_SIZE(target_shaकरोw_reg_cfg_map);
	cfg.shaकरोw_reg_cfg = (काष्ठा ath10k_shaकरोw_reg_cfg *)
		&target_shaकरोw_reg_cfg_map;

	चयन (fw_mode) अणु
	हाल ATH10K_FIRMWARE_MODE_NORMAL:
		mode = QMI_WLFW_MISSION_V01;
		अवरोध;
	हाल ATH10K_FIRMWARE_MODE_UTF:
		mode = QMI_WLFW_FTM_V01;
		अवरोध;
	शेष:
		ath10k_err(ar, "invalid firmware mode %d\n", fw_mode);
		वापस -EINVAL;
	पूर्ण

	वापस ath10k_qmi_wlan_enable(ar, &cfg, mode,
				       शून्य);
पूर्ण

अटल पूर्णांक ath10k_hw_घातer_on(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "soc power on\n");

	ret = regulator_bulk_enable(ar_snoc->num_vregs, ar_snoc->vregs);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(ar_snoc->num_clks, ar_snoc->clks);
	अगर (ret)
		जाओ vreg_off;

	वापस ret;

vreg_off:
	regulator_bulk_disable(ar_snoc->num_vregs, ar_snoc->vregs);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_hw_घातer_off(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "soc power off\n");

	clk_bulk_disable_unprepare(ar_snoc->num_clks, ar_snoc->clks);

	वापस regulator_bulk_disable(ar_snoc->num_vregs, ar_snoc->vregs);
पूर्ण

अटल व्योम ath10k_snoc_wlan_disable(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	/* If both ATH10K_FLAG_CRASH_FLUSH and ATH10K_SNOC_FLAG_RECOVERY
	 * flags are not set, it means that the driver has restarted
	 * due to a crash inject via debugfs. In this हाल, the driver
	 * needs to restart the firmware and hence send qmi wlan disable,
	 * during the driver restart sequence.
	 */
	अगर (!test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags) ||
	    !test_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags))
		ath10k_qmi_wlan_disable(ar);
पूर्ण

अटल व्योम ath10k_snoc_hअगर_घातer_करोwn(काष्ठा ath10k *ar)
अणु
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif power down\n");

	ath10k_snoc_wlan_disable(ar);
	ath10k_ce_मुक्त_rri(ar);
	ath10k_hw_घातer_off(ar);
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_घातer_up(काष्ठा ath10k *ar,
				    क्रमागत ath10k_firmware_mode fw_mode)
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "%s:WCN3990 driver state = %d\n",
		   __func__, ar->state);

	ret = ath10k_hw_घातer_on(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to power on device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_snoc_wlan_enable(ar, fw_mode);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable wcn3990: %d\n", ret);
		जाओ err_hw_घातer_off;
	पूर्ण

	ath10k_ce_alloc_rri(ar);

	ret = ath10k_snoc_init_pipes(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to initialize CE: %d\n", ret);
		जाओ err_मुक्त_rri;
	पूर्ण

	वापस 0;

err_मुक्त_rri:
	ath10k_ce_मुक्त_rri(ar);
	ath10k_snoc_wlan_disable(ar);

err_hw_घातer_off:
	ath10k_hw_घातer_off(ar);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_set_target_log_mode(काष्ठा ath10k *ar,
					       u8 fw_log_mode)
अणु
	u8 fw_dbg_mode;

	अगर (fw_log_mode)
		fw_dbg_mode = ATH10K_ENABLE_FW_LOG_CE;
	अन्यथा
		fw_dbg_mode = ATH10K_ENABLE_FW_LOG_DIAG;

	वापस ath10k_qmi_set_fw_log_mode(ar, fw_dbg_mode);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ath10k_snoc_hअगर_suspend(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक ret;

	अगर (!device_may_wakeup(ar->dev))
		वापस -EPERM;

	ret = enable_irq_wake(ar_snoc->ce_irqs[ATH10K_SNOC_WAKE_IRQ].irq_line);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable wakeup irq :%d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc device suspended\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_snoc_hअगर_resume(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक ret;

	अगर (!device_may_wakeup(ar->dev))
		वापस -EPERM;

	ret = disable_irq_wake(ar_snoc->ce_irqs[ATH10K_SNOC_WAKE_IRQ].irq_line);
	अगर (ret) अणु
		ath10k_err(ar, "failed to disable wakeup irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc device resumed\n");

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा ath10k_hअगर_ops ath10k_snoc_hअगर_ops = अणु
	.पढ़ो32		= ath10k_snoc_पढ़ो32,
	.ग_लिखो32	= ath10k_snoc_ग_लिखो32,
	.start		= ath10k_snoc_hअगर_start,
	.stop		= ath10k_snoc_hअगर_stop,
	.map_service_to_pipe	= ath10k_snoc_hअगर_map_service_to_pipe,
	.get_शेष_pipe	= ath10k_snoc_hअगर_get_शेष_pipe,
	.घातer_up		= ath10k_snoc_hअगर_घातer_up,
	.घातer_करोwn		= ath10k_snoc_hअगर_घातer_करोwn,
	.tx_sg			= ath10k_snoc_hअगर_tx_sg,
	.send_complete_check	= ath10k_snoc_hअगर_send_complete_check,
	.get_मुक्त_queue_number	= ath10k_snoc_hअगर_get_मुक्त_queue_number,
	.get_target_info	= ath10k_snoc_hअगर_get_target_info,
	.set_target_log_mode    = ath10k_snoc_hअगर_set_target_log_mode,

#अगर_घोषित CONFIG_PM
	.suspend                = ath10k_snoc_hअगर_suspend,
	.resume                 = ath10k_snoc_hअगर_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा ath10k_bus_ops ath10k_snoc_bus_ops = अणु
	.पढ़ो32		= ath10k_snoc_पढ़ो32,
	.ग_लिखो32	= ath10k_snoc_ग_लिखो32,
पूर्ण;

अटल पूर्णांक ath10k_snoc_get_ce_id_from_irq(काष्ठा ath10k *ar, पूर्णांक irq)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक i;

	क्रम (i = 0; i < CE_COUNT_MAX; i++) अणु
		अगर (ar_snoc->ce_irqs[i].irq_line == irq)
			वापस i;
	पूर्ण
	ath10k_err(ar, "No matching CE id for irq %d\n", irq);

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t ath10k_snoc_per_engine_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath10k *ar = arg;
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक ce_id = ath10k_snoc_get_ce_id_from_irq(ar, irq);

	अगर (ce_id < 0 || ce_id >= ARRAY_SIZE(ar_snoc->pipe_info)) अणु
		ath10k_warn(ar, "unexpected/invalid irq %d ce_id %d\n", irq,
			    ce_id);
		वापस IRQ_HANDLED;
	पूर्ण

	ath10k_ce_disable_पूर्णांकerrupt(ar, ce_id);
	set_bit(ce_id, ar_snoc->pending_ce_irqs);

	napi_schedule(&ar->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ath10k_snoc_napi_poll(काष्ठा napi_काष्ठा *ctx, पूर्णांक budget)
अणु
	काष्ठा ath10k *ar = container_of(ctx, काष्ठा ath10k, napi);
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक करोne = 0;
	पूर्णांक ce_id;

	अगर (test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags)) अणु
		napi_complete(ctx);
		वापस करोne;
	पूर्ण

	क्रम (ce_id = 0; ce_id < CE_COUNT; ce_id++)
		अगर (test_and_clear_bit(ce_id, ar_snoc->pending_ce_irqs)) अणु
			ath10k_ce_per_engine_service(ar, ce_id);
			ath10k_ce_enable_पूर्णांकerrupt(ar, ce_id);
		पूर्ण

	करोne = ath10k_htt_txrx_compl_task(ar, budget);

	अगर (करोne < budget)
		napi_complete(ctx);

	वापस करोne;
पूर्ण

अटल व्योम ath10k_snoc_init_napi(काष्ठा ath10k *ar)
अणु
	netअगर_napi_add(&ar->napi_dev, &ar->napi, ath10k_snoc_napi_poll,
		       ATH10K_NAPI_BUDGET);
पूर्ण

अटल पूर्णांक ath10k_snoc_request_irq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक irqflags = IRQF_TRIGGER_RISING;
	पूर्णांक ret, id;

	क्रम (id = 0; id < CE_COUNT_MAX; id++) अणु
		ret = request_irq(ar_snoc->ce_irqs[id].irq_line,
				  ath10k_snoc_per_engine_handler,
				  irqflags, ce_name[id], ar);
		अगर (ret) अणु
			ath10k_err(ar,
				   "failed to register IRQ handler for CE %d: %d\n",
				   id, ret);
			जाओ err_irq;
		पूर्ण
	पूर्ण

	वापस 0;

err_irq:
	क्रम (id -= 1; id >= 0; id--)
		मुक्त_irq(ar_snoc->ce_irqs[id].irq_line, ar);

	वापस ret;
पूर्ण

अटल व्योम ath10k_snoc_मुक्त_irq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	पूर्णांक id;

	क्रम (id = 0; id < CE_COUNT_MAX; id++)
		मुक्त_irq(ar_snoc->ce_irqs[id].irq_line, ar);
पूर्ण

अटल पूर्णांक ath10k_snoc_resource_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *res;
	पूर्णांक i, ret = 0;

	pdev = ar_snoc->dev;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "membase");
	अगर (!res) अणु
		ath10k_err(ar, "Memory base not found in DT\n");
		वापस -EINVAL;
	पूर्ण

	ar_snoc->mem_pa = res->start;
	ar_snoc->mem = devm_ioremap(&pdev->dev, ar_snoc->mem_pa,
				    resource_size(res));
	अगर (!ar_snoc->mem) अणु
		ath10k_err(ar, "Memory base ioremap failed with physical address %pa\n",
			   &ar_snoc->mem_pa);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < CE_COUNT; i++) अणु
		res = platक्रमm_get_resource(ar_snoc->dev, IORESOURCE_IRQ, i);
		अगर (!res) अणु
			ath10k_err(ar, "failed to get IRQ%d\n", i);
			ret = -ENODEV;
			जाओ out;
		पूर्ण
		ar_snoc->ce_irqs[i].irq_line = res->start;
	पूर्ण

	ret = device_property_पढ़ो_u32(&pdev->dev, "qcom,xo-cal-data",
				       &ar_snoc->xo_cal_data);
	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc xo-cal-data return %d\n", ret);
	अगर (ret == 0) अणु
		ar_snoc->xo_cal_supported = true;
		ath10k_dbg(ar, ATH10K_DBG_SNOC, "xo cal data %x\n",
			   ar_snoc->xo_cal_data);
	पूर्ण
	ret = 0;

out:
	वापस ret;
पूर्ण

अटल व्योम ath10k_snoc_quirks_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा device *dev = &ar_snoc->dev->dev;

	अगर (of_property_पढ़ो_bool(dev->of_node, "qcom,snoc-host-cap-8bit-quirk"))
		set_bit(ATH10K_SNOC_FLAG_8BIT_HOST_CAP_QUIRK, &ar_snoc->flags);
पूर्ण

पूर्णांक ath10k_snoc_fw_indication(काष्ठा ath10k *ar, u64 type)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_bus_params bus_params = अणुपूर्ण;
	पूर्णांक ret;

	अगर (test_bit(ATH10K_SNOC_FLAG_UNREGISTERING, &ar_snoc->flags))
		वापस 0;

	चयन (type) अणु
	हाल ATH10K_QMI_EVENT_FW_READY_IND:
		अगर (test_bit(ATH10K_SNOC_FLAG_REGISTERED, &ar_snoc->flags)) अणु
			ath10k_core_start_recovery(ar);
			अवरोध;
		पूर्ण

		bus_params.dev_type = ATH10K_DEV_TYPE_LL;
		bus_params.chip_id = ar_snoc->target_info.soc_version;
		ret = ath10k_core_रेजिस्टर(ar, &bus_params);
		अगर (ret) अणु
			ath10k_err(ar, "Failed to register driver core: %d\n",
				   ret);
			वापस ret;
		पूर्ण
		set_bit(ATH10K_SNOC_FLAG_REGISTERED, &ar_snoc->flags);
		अवरोध;
	हाल ATH10K_QMI_EVENT_FW_DOWN_IND:
		set_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags);
		set_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags);
		अवरोध;
	शेष:
		ath10k_err(ar, "invalid fw indication: %llx\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_snoc_setup_resource(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_snoc_pipe *pipe;
	पूर्णांक i, ret;

	समयr_setup(&ar_snoc->rx_post_retry, ath10k_snoc_rx_replenish_retry, 0);
	spin_lock_init(&ce->ce_lock);
	क्रम (i = 0; i < CE_COUNT; i++) अणु
		pipe = &ar_snoc->pipe_info[i];
		pipe->ce_hdl = &ce->ce_states[i];
		pipe->pipe_num = i;
		pipe->hअगर_ce_state = ar;

		ret = ath10k_ce_alloc_pipe(ar, i, &host_ce_config_wlan[i]);
		अगर (ret) अणु
			ath10k_err(ar, "failed to allocate copy engine pipe %d: %d\n",
				   i, ret);
			वापस ret;
		पूर्ण

		pipe->buf_sz = host_ce_config_wlan[i].src_sz_max;
	पूर्ण
	ath10k_snoc_init_napi(ar);

	वापस 0;
पूर्ण

अटल व्योम ath10k_snoc_release_resource(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;

	netअगर_napi_del(&ar->napi);
	क्रम (i = 0; i < CE_COUNT; i++)
		ath10k_ce_मुक्त_pipe(ar, i);
पूर्ण

अटल व्योम ath10k_msa_dump_memory(काष्ठा ath10k *ar,
				   काष्ठा ath10k_fw_crash_data *crash_data)
अणु
	स्थिर काष्ठा ath10k_hw_mem_layout *mem_layout;
	स्थिर काष्ठा ath10k_mem_region *current_region;
	काष्ठा ath10k_dump_ram_data_hdr *hdr;
	माप_प्रकार buf_len;
	u8 *buf;

	अगर (!crash_data || !crash_data->ramdump_buf)
		वापस;

	mem_layout = ath10k_coredump_get_mem_layout(ar);
	अगर (!mem_layout)
		वापस;

	current_region = &mem_layout->region_table.regions[0];

	buf = crash_data->ramdump_buf;
	buf_len = crash_data->ramdump_buf_len;
	स_रखो(buf, 0, buf_len);

	/* Reserve space क्रम the header. */
	hdr = (व्योम *)buf;
	buf += माप(*hdr);
	buf_len -= माप(*hdr);

	hdr->region_type = cpu_to_le32(current_region->type);
	hdr->start = cpu_to_le32((अचिन्हित दीर्घ)ar->msa.vaddr);
	hdr->length = cpu_to_le32(ar->msa.mem_size);

	अगर (current_region->len < ar->msa.mem_size) अणु
		स_नकल(buf, ar->msa.vaddr, current_region->len);
		ath10k_warn(ar, "msa dump length is less than msa size %x, %x\n",
			    current_region->len, ar->msa.mem_size);
	पूर्ण अन्यथा अणु
		स_नकल(buf, ar->msa.vaddr, ar->msa.mem_size);
	पूर्ण
पूर्ण

व्योम ath10k_snoc_fw_crashed_dump(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_fw_crash_data *crash_data;
	अक्षर guid[UUID_STRING_LEN + 1];

	mutex_lock(&ar->dump_mutex);

	spin_lock_bh(&ar->data_lock);
	ar->stats.fw_crash_counter++;
	spin_unlock_bh(&ar->data_lock);

	crash_data = ath10k_coredump_new(ar);

	अगर (crash_data)
		scnम_लिखो(guid, माप(guid), "%pUl", &crash_data->guid);
	अन्यथा
		scnम_लिखो(guid, माप(guid), "n/a");

	ath10k_err(ar, "firmware crashed! (guid %s)\n", guid);
	ath10k_prपूर्णांक_driver_info(ar);
	ath10k_msa_dump_memory(ar, crash_data);
	mutex_unlock(&ar->dump_mutex);
पूर्ण

अटल पूर्णांक ath10k_setup_msa_resources(काष्ठा ath10k *ar, u32 msa_size)
अणु
	काष्ठा device *dev = ar->dev;
	काष्ठा device_node *node;
	काष्ठा resource r;
	पूर्णांक ret;

	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (node) अणु
		ret = of_address_to_resource(node, 0, &r);
		अगर (ret) अणु
			dev_err(dev, "failed to resolve msa fixed region\n");
			वापस ret;
		पूर्ण
		of_node_put(node);

		ar->msa.paddr = r.start;
		ar->msa.mem_size = resource_size(&r);
		ar->msa.vaddr = devm_memremap(dev, ar->msa.paddr,
					      ar->msa.mem_size,
					      MEMREMAP_WT);
		अगर (IS_ERR(ar->msa.vaddr)) अणु
			dev_err(dev, "failed to map memory region: %pa\n",
				&r.start);
			वापस PTR_ERR(ar->msa.vaddr);
		पूर्ण
	पूर्ण अन्यथा अणु
		ar->msa.vaddr = dmam_alloc_coherent(dev, msa_size,
						    &ar->msa.paddr,
						    GFP_KERNEL);
		अगर (!ar->msa.vaddr) अणु
			ath10k_err(ar, "failed to allocate dma memory for msa region\n");
			वापस -ENOMEM;
		पूर्ण
		ar->msa.mem_size = msa_size;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_QMI, "qmi msa.paddr: %pad , msa.vaddr: 0x%p\n",
		   &ar->msa.paddr,
		   ar->msa.vaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_fw_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	काष्ठा device *host_dev = &ar_snoc->dev->dev;
	काष्ठा platक्रमm_device_info info;
	काष्ठा iommu_करोमुख्य *iommu_करोm;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *node;
	पूर्णांक ret;

	node = of_get_child_by_name(host_dev->of_node, "wifi-firmware");
	अगर (!node) अणु
		ar_snoc->use_tz = true;
		वापस 0;
	पूर्ण

	स_रखो(&info, 0, माप(info));
	info.fwnode = &node->fwnode;
	info.parent = host_dev;
	info.name = node->name;
	info.dma_mask = DMA_BIT_MASK(32);

	pdev = platक्रमm_device_रेजिस्टर_full(&info);
	अगर (IS_ERR(pdev)) अणु
		of_node_put(node);
		वापस PTR_ERR(pdev);
	पूर्ण

	pdev->dev.of_node = node;

	ret = of_dma_configure(&pdev->dev, node, true);
	अगर (ret) अणु
		ath10k_err(ar, "dma configure fail: %d\n", ret);
		जाओ err_unरेजिस्टर;
	पूर्ण

	ar_snoc->fw.dev = &pdev->dev;

	iommu_करोm = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!iommu_करोm) अणु
		ath10k_err(ar, "failed to allocate iommu domain\n");
		ret = -ENOMEM;
		जाओ err_unरेजिस्टर;
	पूर्ण

	ret = iommu_attach_device(iommu_करोm, ar_snoc->fw.dev);
	अगर (ret) अणु
		ath10k_err(ar, "could not attach device: %d\n", ret);
		जाओ err_iommu_मुक्त;
	पूर्ण

	ar_snoc->fw.iommu_करोमुख्य = iommu_करोm;
	ar_snoc->fw.fw_start_addr = ar->msa.paddr;

	ret = iommu_map(iommu_करोm, ar_snoc->fw.fw_start_addr,
			ar->msa.paddr, ar->msa.mem_size,
			IOMMU_READ | IOMMU_WRITE);
	अगर (ret) अणु
		ath10k_err(ar, "failed to map firmware region: %d\n", ret);
		जाओ err_iommu_detach;
	पूर्ण

	of_node_put(node);

	वापस 0;

err_iommu_detach:
	iommu_detach_device(iommu_करोm, ar_snoc->fw.dev);

err_iommu_मुक्त:
	iommu_करोमुख्य_मुक्त(iommu_करोm);

err_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(pdev);
	of_node_put(node);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_fw_deinit(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	स्थिर माप_प्रकार mapped_size = ar_snoc->fw.mapped_mem_size;
	काष्ठा iommu_करोमुख्य *iommu;
	माप_प्रकार unmapped_size;

	अगर (ar_snoc->use_tz)
		वापस 0;

	iommu = ar_snoc->fw.iommu_करोमुख्य;

	unmapped_size = iommu_unmap(iommu, ar_snoc->fw.fw_start_addr,
				    mapped_size);
	अगर (unmapped_size != mapped_size)
		ath10k_err(ar, "failed to unmap firmware: %zu\n",
			   unmapped_size);

	iommu_detach_device(iommu, ar_snoc->fw.dev);
	iommu_करोमुख्य_मुक्त(iommu);

	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(ar_snoc->fw.dev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ath10k_snoc_dt_match[] = अणु
	अणु .compatible = "qcom,wcn3990-wifi",
	 .data = &drv_priv,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ath10k_snoc_dt_match);

अटल पूर्णांक ath10k_snoc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ath10k_snoc_drv_priv *drv_data;
	काष्ठा ath10k_snoc *ar_snoc;
	काष्ठा device *dev;
	काष्ठा ath10k *ar;
	u32 msa_size;
	पूर्णांक ret;
	u32 i;

	dev = &pdev->dev;
	drv_data = device_get_match_data(dev);
	अगर (!drv_data) अणु
		dev_err(dev, "failed to find matching device tree id\n");
		वापस -EINVAL;
	पूर्ण

	ret = dma_set_mask_and_coherent(dev, drv_data->dma_mask);
	अगर (ret) अणु
		dev_err(dev, "failed to set dma mask: %d\n", ret);
		वापस ret;
	पूर्ण

	ar = ath10k_core_create(माप(*ar_snoc), dev, ATH10K_BUS_SNOC,
				drv_data->hw_rev, &ath10k_snoc_hअगर_ops);
	अगर (!ar) अणु
		dev_err(dev, "failed to allocate core\n");
		वापस -ENOMEM;
	पूर्ण

	ar_snoc = ath10k_snoc_priv(ar);
	ar_snoc->dev = pdev;
	platक्रमm_set_drvdata(pdev, ar);
	ar_snoc->ar = ar;
	ar_snoc->ce.bus_ops = &ath10k_snoc_bus_ops;
	ar->ce_priv = &ar_snoc->ce;
	msa_size = drv_data->msa_size;

	ath10k_snoc_quirks_init(ar);

	ret = ath10k_snoc_resource_init(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to initialize resource: %d\n", ret);
		जाओ err_core_destroy;
	पूर्ण

	ret = ath10k_snoc_setup_resource(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to setup resource: %d\n", ret);
		जाओ err_core_destroy;
	पूर्ण
	ret = ath10k_snoc_request_irq(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request irqs: %d\n", ret);
		जाओ err_release_resource;
	पूर्ण

	ar_snoc->num_vregs = ARRAY_SIZE(ath10k_regulators);
	ar_snoc->vregs = devm_kसुस्मृति(&pdev->dev, ar_snoc->num_vregs,
				      माप(*ar_snoc->vregs), GFP_KERNEL);
	अगर (!ar_snoc->vregs) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण
	क्रम (i = 0; i < ar_snoc->num_vregs; i++)
		ar_snoc->vregs[i].supply = ath10k_regulators[i];

	ret = devm_regulator_bulk_get(&pdev->dev, ar_snoc->num_vregs,
				      ar_snoc->vregs);
	अगर (ret < 0)
		जाओ err_मुक्त_irq;

	ar_snoc->num_clks = ARRAY_SIZE(ath10k_घड़ीs);
	ar_snoc->clks = devm_kसुस्मृति(&pdev->dev, ar_snoc->num_clks,
				     माप(*ar_snoc->clks), GFP_KERNEL);
	अगर (!ar_snoc->clks) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण

	क्रम (i = 0; i < ar_snoc->num_clks; i++)
		ar_snoc->clks[i].id = ath10k_घड़ीs[i];

	ret = devm_clk_bulk_get_optional(&pdev->dev, ar_snoc->num_clks,
					 ar_snoc->clks);
	अगर (ret)
		जाओ err_मुक्त_irq;

	ret = ath10k_setup_msa_resources(ar, msa_size);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to setup msa resources: %d\n", ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	ret = ath10k_fw_init(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to initialize firmware: %d\n", ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	ret = ath10k_qmi_init(ar, msa_size);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to register wlfw qmi client: %d\n", ret);
		जाओ err_fw_deinit;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc probe\n");

	वापस 0;

err_fw_deinit:
	ath10k_fw_deinit(ar);

err_मुक्त_irq:
	ath10k_snoc_मुक्त_irq(ar);

err_release_resource:
	ath10k_snoc_release_resource(ar);

err_core_destroy:
	ath10k_core_destroy(ar);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_snoc_मुक्त_resources(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc free resources\n");

	set_bit(ATH10K_SNOC_FLAG_UNREGISTERING, &ar_snoc->flags);

	ath10k_core_unरेजिस्टर(ar);
	ath10k_fw_deinit(ar);
	ath10k_snoc_मुक्त_irq(ar);
	ath10k_snoc_release_resource(ar);
	ath10k_qmi_deinit(ar);
	ath10k_core_destroy(ar);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_snoc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath10k *ar = platक्रमm_get_drvdata(pdev);
	काष्ठा ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc remove\n");

	reinit_completion(&ar->driver_recovery);

	अगर (test_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags))
		रुको_क्रम_completion_समयout(&ar->driver_recovery, 3 * HZ);

	ath10k_snoc_मुक्त_resources(ar);

	वापस 0;
पूर्ण

अटल व्योम ath10k_snoc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath10k *ar = platक्रमm_get_drvdata(pdev);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc shutdown\n");
	ath10k_snoc_मुक्त_resources(ar);
पूर्ण

अटल काष्ठा platक्रमm_driver ath10k_snoc_driver = अणु
	.probe  = ath10k_snoc_probe,
	.हटाओ = ath10k_snoc_हटाओ,
	.shutकरोwn =  ath10k_snoc_shutकरोwn,
	.driver = अणु
		.name   = "ath10k_snoc",
		.of_match_table = ath10k_snoc_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ath10k_snoc_driver);

MODULE_AUTHOR("Qualcomm");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Driver support for Atheros WCN3990 SNOC devices");
