<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * K3 NAVSS DMA glue पूर्णांकerface
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 *
 */

#समावेश <linux/atomic.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ti/k3-ringacc.h>
#समावेश <linux/dma/ti-cppi5.h>
#समावेश <linux/dma/k3-udma-glue.h>

#समावेश "k3-udma.h"
#समावेश "k3-psil-priv.h"

काष्ठा k3_udma_glue_common अणु
	काष्ठा device *dev;
	काष्ठा device chan_dev;
	काष्ठा udma_dev *udmax;
	स्थिर काष्ठा udma_tisci_rm *tisci_rm;
	काष्ठा k3_ringacc *ringacc;
	u32 src_thपढ़ो;
	u32 dst_thपढ़ो;

	u32  hdesc_size;
	bool epib;
	u32  psdata_size;
	u32  swdata_size;
	u32  atype_asel;
	काष्ठा psil_endpoपूर्णांक_config *ep_config;
पूर्ण;

काष्ठा k3_udma_glue_tx_channel अणु
	काष्ठा k3_udma_glue_common common;

	काष्ठा udma_tchan *udma_tchanx;
	पूर्णांक udma_tchan_id;

	काष्ठा k3_ring *ringtx;
	काष्ठा k3_ring *ringtxcq;

	bool psil_paired;

	पूर्णांक virq;

	atomic_t मुक्त_pkts;
	bool tx_छोड़ो_on_err;
	bool tx_filt_einfo;
	bool tx_filt_pswords;
	bool tx_supr_tdpkt;

	पूर्णांक udma_tflow_id;
पूर्ण;

काष्ठा k3_udma_glue_rx_flow अणु
	काष्ठा udma_rflow *udma_rflow;
	पूर्णांक udma_rflow_id;
	काष्ठा k3_ring *ringrx;
	काष्ठा k3_ring *ringrxfdq;

	पूर्णांक virq;
पूर्ण;

काष्ठा k3_udma_glue_rx_channel अणु
	काष्ठा k3_udma_glue_common common;

	काष्ठा udma_rchan *udma_rchanx;
	पूर्णांक udma_rchan_id;
	bool remote;

	bool psil_paired;

	u32  swdata_size;
	पूर्णांक  flow_id_base;

	काष्ठा k3_udma_glue_rx_flow *flows;
	u32 flow_num;
	u32 flows_पढ़ोy;
पूर्ण;

अटल व्योम k3_udma_chan_dev_release(काष्ठा device *dev)
अणु
	/* The काष्ठा containing the device is devm managed */
पूर्ण

अटल काष्ठा class k3_udma_glue_devclass = अणु
	.name		= "k3_udma_glue_chan",
	.dev_release	= k3_udma_chan_dev_release,
पूर्ण;

#घोषणा K3_UDMAX_TDOWN_TIMEOUT_US 1000

अटल पूर्णांक of_k3_udma_glue_parse(काष्ठा device_node *udmax_np,
				 काष्ठा k3_udma_glue_common *common)
अणु
	common->udmax = of_xudma_dev_get(udmax_np, शून्य);
	अगर (IS_ERR(common->udmax))
		वापस PTR_ERR(common->udmax);

	common->ringacc = xudma_get_ringacc(common->udmax);
	common->tisci_rm = xudma_dev_get_tisci_rm(common->udmax);

	वापस 0;
पूर्ण

अटल पूर्णांक of_k3_udma_glue_parse_chn(काष्ठा device_node *chn_np,
		स्थिर अक्षर *name, काष्ठा k3_udma_glue_common *common,
		bool tx_chn)
अणु
	काष्ठा of_phandle_args dma_spec;
	u32 thपढ़ो_id;
	पूर्णांक ret = 0;
	पूर्णांक index;

	अगर (unlikely(!name))
		वापस -EINVAL;

	index = of_property_match_string(chn_np, "dma-names", name);
	अगर (index < 0)
		वापस index;

	अगर (of_parse_phandle_with_args(chn_np, "dmas", "#dma-cells", index,
				       &dma_spec))
		वापस -ENOENT;

	ret = of_k3_udma_glue_parse(dma_spec.np, common);
	अगर (ret)
		जाओ out_put_spec;

	thपढ़ो_id = dma_spec.args[0];
	अगर (dma_spec.args_count == 2) अणु
		अगर (dma_spec.args[1] > 2 && !xudma_is_pktdma(common->udmax)) अणु
			dev_err(common->dev, "Invalid channel atype: %u\n",
				dma_spec.args[1]);
			ret = -EINVAL;
			जाओ out_put_spec;
		पूर्ण
		अगर (dma_spec.args[1] > 15 && xudma_is_pktdma(common->udmax)) अणु
			dev_err(common->dev, "Invalid channel asel: %u\n",
				dma_spec.args[1]);
			ret = -EINVAL;
			जाओ out_put_spec;
		पूर्ण

		common->atype_asel = dma_spec.args[1];
	पूर्ण

	अगर (tx_chn && !(thपढ़ो_id & K3_PSIL_DST_THREAD_ID_OFFSET)) अणु
		ret = -EINVAL;
		जाओ out_put_spec;
	पूर्ण

	अगर (!tx_chn && (thपढ़ो_id & K3_PSIL_DST_THREAD_ID_OFFSET)) अणु
		ret = -EINVAL;
		जाओ out_put_spec;
	पूर्ण

	/* get psil endpoपूर्णांक config */
	common->ep_config = psil_get_ep_config(thपढ़ो_id);
	अगर (IS_ERR(common->ep_config)) अणु
		dev_err(common->dev,
			"No configuration for psi-l thread 0x%04x\n",
			thपढ़ो_id);
		ret = PTR_ERR(common->ep_config);
		जाओ out_put_spec;
	पूर्ण

	common->epib = common->ep_config->needs_epib;
	common->psdata_size = common->ep_config->psd_size;

	अगर (tx_chn)
		common->dst_thपढ़ो = thपढ़ो_id;
	अन्यथा
		common->src_thपढ़ो = thपढ़ो_id;

out_put_spec:
	of_node_put(dma_spec.np);
	वापस ret;
पूर्ण;

अटल व्योम k3_udma_glue_dump_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	काष्ठा device *dev = tx_chn->common.dev;

	dev_dbg(dev, "dump_tx_chn:\n"
		"udma_tchan_id: %d\n"
		"src_thread: %08x\n"
		"dst_thread: %08x\n",
		tx_chn->udma_tchan_id,
		tx_chn->common.src_thपढ़ो,
		tx_chn->common.dst_thपढ़ो);
पूर्ण

अटल व्योम k3_udma_glue_dump_tx_rt_chn(काष्ठा k3_udma_glue_tx_channel *chn,
					अक्षर *mark)
अणु
	काष्ठा device *dev = chn->common.dev;

	dev_dbg(dev, "=== dump ===> %s\n", mark);
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_CTL_REG,
		xudma_tchanrt_पढ़ो(chn->udma_tchanx, UDMA_CHAN_RT_CTL_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_PEER_RT_EN_REG,
		xudma_tchanrt_पढ़ो(chn->udma_tchanx,
				   UDMA_CHAN_RT_PEER_RT_EN_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_PCNT_REG,
		xudma_tchanrt_पढ़ो(chn->udma_tchanx, UDMA_CHAN_RT_PCNT_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_BCNT_REG,
		xudma_tchanrt_पढ़ो(chn->udma_tchanx, UDMA_CHAN_RT_BCNT_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_SBCNT_REG,
		xudma_tchanrt_पढ़ो(chn->udma_tchanx, UDMA_CHAN_RT_SBCNT_REG));
पूर्ण

अटल पूर्णांक k3_udma_glue_cfg_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	स्थिर काष्ठा udma_tisci_rm *tisci_rm = tx_chn->common.tisci_rm;
	काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg req;

	स_रखो(&req, 0, माप(req));

	req.valid_params = TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_EINFO_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_PSWORDS_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_SUPR_TDPKT_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID;
	req.nav_id = tisci_rm->tisci_dev_id;
	req.index = tx_chn->udma_tchan_id;
	अगर (tx_chn->tx_छोड़ो_on_err)
		req.tx_छोड़ो_on_err = 1;
	अगर (tx_chn->tx_filt_einfo)
		req.tx_filt_einfo = 1;
	अगर (tx_chn->tx_filt_pswords)
		req.tx_filt_pswords = 1;
	req.tx_chan_type = TI_SCI_RM_UDMAP_CHAN_TYPE_PKT_PBRR;
	अगर (tx_chn->tx_supr_tdpkt)
		req.tx_supr_tdpkt = 1;
	req.tx_fetch_size = tx_chn->common.hdesc_size >> 2;
	req.txcq_qnum = k3_ringacc_get_ring_id(tx_chn->ringtxcq);
	req.tx_atype = tx_chn->common.atype_asel;

	वापस tisci_rm->tisci_udmap_ops->tx_ch_cfg(tisci_rm->tisci, &req);
पूर्ण

काष्ठा k3_udma_glue_tx_channel *k3_udma_glue_request_tx_chn(काष्ठा device *dev,
		स्थिर अक्षर *name, काष्ठा k3_udma_glue_tx_channel_cfg *cfg)
अणु
	काष्ठा k3_udma_glue_tx_channel *tx_chn;
	पूर्णांक ret;

	tx_chn = devm_kzalloc(dev, माप(*tx_chn), GFP_KERNEL);
	अगर (!tx_chn)
		वापस ERR_PTR(-ENOMEM);

	tx_chn->common.dev = dev;
	tx_chn->common.swdata_size = cfg->swdata_size;
	tx_chn->tx_छोड़ो_on_err = cfg->tx_छोड़ो_on_err;
	tx_chn->tx_filt_einfo = cfg->tx_filt_einfo;
	tx_chn->tx_filt_pswords = cfg->tx_filt_pswords;
	tx_chn->tx_supr_tdpkt = cfg->tx_supr_tdpkt;

	/* parse of udmap channel */
	ret = of_k3_udma_glue_parse_chn(dev->of_node, name,
					&tx_chn->common, true);
	अगर (ret)
		जाओ err;

	tx_chn->common.hdesc_size = cppi5_hdesc_calc_size(tx_chn->common.epib,
						tx_chn->common.psdata_size,
						tx_chn->common.swdata_size);

	अगर (xudma_is_pktdma(tx_chn->common.udmax))
		tx_chn->udma_tchan_id = tx_chn->common.ep_config->mapped_channel_id;
	अन्यथा
		tx_chn->udma_tchan_id = -1;

	/* request and cfg UDMAP TX channel */
	tx_chn->udma_tchanx = xudma_tchan_get(tx_chn->common.udmax,
					      tx_chn->udma_tchan_id);
	अगर (IS_ERR(tx_chn->udma_tchanx)) अणु
		ret = PTR_ERR(tx_chn->udma_tchanx);
		dev_err(dev, "UDMAX tchanx get err %d\n", ret);
		जाओ err;
	पूर्ण
	tx_chn->udma_tchan_id = xudma_tchan_get_id(tx_chn->udma_tchanx);

	tx_chn->common.chan_dev.class = &k3_udma_glue_devclass;
	tx_chn->common.chan_dev.parent = xudma_get_device(tx_chn->common.udmax);
	dev_set_name(&tx_chn->common.chan_dev, "tchan%d-0x%04x",
		     tx_chn->udma_tchan_id, tx_chn->common.dst_thपढ़ो);
	ret = device_रेजिस्टर(&tx_chn->common.chan_dev);
	अगर (ret) अणु
		dev_err(dev, "Channel Device registration failed %d\n", ret);
		tx_chn->common.chan_dev.parent = शून्य;
		जाओ err;
	पूर्ण

	अगर (xudma_is_pktdma(tx_chn->common.udmax)) अणु
		/* prepare the channel device as coherent */
		tx_chn->common.chan_dev.dma_coherent = true;
		dma_coerce_mask_and_coherent(&tx_chn->common.chan_dev,
					     DMA_BIT_MASK(48));
	पूर्ण

	atomic_set(&tx_chn->मुक्त_pkts, cfg->txcq_cfg.size);

	अगर (xudma_is_pktdma(tx_chn->common.udmax))
		tx_chn->udma_tflow_id = tx_chn->common.ep_config->शेष_flow_id;
	अन्यथा
		tx_chn->udma_tflow_id = tx_chn->udma_tchan_id;

	/* request and cfg rings */
	ret =  k3_ringacc_request_rings_pair(tx_chn->common.ringacc,
					     tx_chn->udma_tflow_id, -1,
					     &tx_chn->ringtx,
					     &tx_chn->ringtxcq);
	अगर (ret) अणु
		dev_err(dev, "Failed to get TX/TXCQ rings %d\n", ret);
		जाओ err;
	पूर्ण

	/* Set the dma_dev क्रम the rings to be configured */
	cfg->tx_cfg.dma_dev = k3_udma_glue_tx_get_dma_device(tx_chn);
	cfg->txcq_cfg.dma_dev = cfg->tx_cfg.dma_dev;

	/* Set the ASEL value क्रम DMA rings of PKTDMA */
	अगर (xudma_is_pktdma(tx_chn->common.udmax)) अणु
		cfg->tx_cfg.asel = tx_chn->common.atype_asel;
		cfg->txcq_cfg.asel = tx_chn->common.atype_asel;
	पूर्ण

	ret = k3_ringacc_ring_cfg(tx_chn->ringtx, &cfg->tx_cfg);
	अगर (ret) अणु
		dev_err(dev, "Failed to cfg ringtx %d\n", ret);
		जाओ err;
	पूर्ण

	ret = k3_ringacc_ring_cfg(tx_chn->ringtxcq, &cfg->txcq_cfg);
	अगर (ret) अणु
		dev_err(dev, "Failed to cfg ringtx %d\n", ret);
		जाओ err;
	पूर्ण

	/* request and cfg psi-l */
	tx_chn->common.src_thपढ़ो =
			xudma_dev_get_psil_base(tx_chn->common.udmax) +
			tx_chn->udma_tchan_id;

	ret = k3_udma_glue_cfg_tx_chn(tx_chn);
	अगर (ret) अणु
		dev_err(dev, "Failed to cfg tchan %d\n", ret);
		जाओ err;
	पूर्ण

	k3_udma_glue_dump_tx_chn(tx_chn);

	वापस tx_chn;

err:
	k3_udma_glue_release_tx_chn(tx_chn);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_request_tx_chn);

व्योम k3_udma_glue_release_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	अगर (tx_chn->psil_paired) अणु
		xudma_navss_psil_unpair(tx_chn->common.udmax,
					tx_chn->common.src_thपढ़ो,
					tx_chn->common.dst_thपढ़ो);
		tx_chn->psil_paired = false;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(tx_chn->udma_tchanx))
		xudma_tchan_put(tx_chn->common.udmax,
				tx_chn->udma_tchanx);

	अगर (tx_chn->ringtxcq)
		k3_ringacc_ring_मुक्त(tx_chn->ringtxcq);

	अगर (tx_chn->ringtx)
		k3_ringacc_ring_मुक्त(tx_chn->ringtx);

	अगर (tx_chn->common.chan_dev.parent) अणु
		device_unरेजिस्टर(&tx_chn->common.chan_dev);
		tx_chn->common.chan_dev.parent = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_release_tx_chn);

पूर्णांक k3_udma_glue_push_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			     काष्ठा cppi5_host_desc_t *desc_tx,
			     dma_addr_t desc_dma)
अणु
	u32 ringtxcq_id;

	अगर (!atomic_add_unless(&tx_chn->मुक्त_pkts, -1, 0))
		वापस -ENOMEM;

	ringtxcq_id = k3_ringacc_get_ring_id(tx_chn->ringtxcq);
	cppi5_desc_set_retpolicy(&desc_tx->hdr, 0, ringtxcq_id);

	वापस k3_ringacc_ring_push(tx_chn->ringtx, &desc_dma);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_push_tx_chn);

पूर्णांक k3_udma_glue_pop_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			    dma_addr_t *desc_dma)
अणु
	पूर्णांक ret;

	ret = k3_ringacc_ring_pop(tx_chn->ringtxcq, desc_dma);
	अगर (!ret)
		atomic_inc(&tx_chn->मुक्त_pkts);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_pop_tx_chn);

पूर्णांक k3_udma_glue_enable_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	पूर्णांक ret;

	ret = xudma_navss_psil_pair(tx_chn->common.udmax,
				    tx_chn->common.src_thपढ़ो,
				    tx_chn->common.dst_thपढ़ो);
	अगर (ret) अणु
		dev_err(tx_chn->common.dev, "PSI-L request err %d\n", ret);
		वापस ret;
	पूर्ण

	tx_chn->psil_paired = true;

	xudma_tchanrt_ग_लिखो(tx_chn->udma_tchanx, UDMA_CHAN_RT_PEER_RT_EN_REG,
			    UDMA_PEER_RT_EN_ENABLE);

	xudma_tchanrt_ग_लिखो(tx_chn->udma_tchanx, UDMA_CHAN_RT_CTL_REG,
			    UDMA_CHAN_RT_CTL_EN);

	k3_udma_glue_dump_tx_rt_chn(tx_chn, "txchn en");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_enable_tx_chn);

व्योम k3_udma_glue_disable_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	k3_udma_glue_dump_tx_rt_chn(tx_chn, "txchn dis1");

	xudma_tchanrt_ग_लिखो(tx_chn->udma_tchanx, UDMA_CHAN_RT_CTL_REG, 0);

	xudma_tchanrt_ग_लिखो(tx_chn->udma_tchanx,
			    UDMA_CHAN_RT_PEER_RT_EN_REG, 0);
	k3_udma_glue_dump_tx_rt_chn(tx_chn, "txchn dis2");

	अगर (tx_chn->psil_paired) अणु
		xudma_navss_psil_unpair(tx_chn->common.udmax,
					tx_chn->common.src_thपढ़ो,
					tx_chn->common.dst_thपढ़ो);
		tx_chn->psil_paired = false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_disable_tx_chn);

व्योम k3_udma_glue_tकरोwn_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			       bool sync)
अणु
	पूर्णांक i = 0;
	u32 val;

	k3_udma_glue_dump_tx_rt_chn(tx_chn, "txchn tdown1");

	xudma_tchanrt_ग_लिखो(tx_chn->udma_tchanx, UDMA_CHAN_RT_CTL_REG,
			    UDMA_CHAN_RT_CTL_EN | UDMA_CHAN_RT_CTL_TDOWN);

	val = xudma_tchanrt_पढ़ो(tx_chn->udma_tchanx, UDMA_CHAN_RT_CTL_REG);

	जबतक (sync && (val & UDMA_CHAN_RT_CTL_EN)) अणु
		val = xudma_tchanrt_पढ़ो(tx_chn->udma_tchanx,
					 UDMA_CHAN_RT_CTL_REG);
		udelay(1);
		अगर (i > K3_UDMAX_TDOWN_TIMEOUT_US) अणु
			dev_err(tx_chn->common.dev, "TX tdown timeout\n");
			अवरोध;
		पूर्ण
		i++;
	पूर्ण

	val = xudma_tchanrt_पढ़ो(tx_chn->udma_tchanx,
				 UDMA_CHAN_RT_PEER_RT_EN_REG);
	अगर (sync && (val & UDMA_PEER_RT_EN_ENABLE))
		dev_err(tx_chn->common.dev, "TX tdown peer not stopped\n");
	k3_udma_glue_dump_tx_rt_chn(tx_chn, "txchn tdown2");
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tकरोwn_tx_chn);

व्योम k3_udma_glue_reset_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			       व्योम *data,
			       व्योम (*cleanup)(व्योम *data, dma_addr_t desc_dma))
अणु
	काष्ठा device *dev = tx_chn->common.dev;
	dma_addr_t desc_dma;
	पूर्णांक occ_tx, i, ret;

	/*
	 * TXQ reset need to be special way as it is input क्रम udma and its
	 * state cached by udma, so:
	 * 1) save TXQ occ
	 * 2) clean up TXQ and call callback .cleanup() क्रम each desc
	 * 3) reset TXQ in a special way
	 */
	occ_tx = k3_ringacc_ring_get_occ(tx_chn->ringtx);
	dev_dbg(dev, "TX reset occ_tx %u\n", occ_tx);

	क्रम (i = 0; i < occ_tx; i++) अणु
		ret = k3_ringacc_ring_pop(tx_chn->ringtx, &desc_dma);
		अगर (ret) अणु
			अगर (ret != -ENODATA)
				dev_err(dev, "TX reset pop %d\n", ret);
			अवरोध;
		पूर्ण
		cleanup(data, desc_dma);
	पूर्ण

	/* reset TXCQ as it is not input क्रम udma - expected to be empty */
	k3_ringacc_ring_reset(tx_chn->ringtxcq);
	k3_ringacc_ring_reset_dma(tx_chn->ringtx, occ_tx);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_reset_tx_chn);

u32 k3_udma_glue_tx_get_hdesc_size(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	वापस tx_chn->common.hdesc_size;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tx_get_hdesc_size);

u32 k3_udma_glue_tx_get_txcq_id(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	वापस k3_ringacc_get_ring_id(tx_chn->ringtxcq);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tx_get_txcq_id);

पूर्णांक k3_udma_glue_tx_get_irq(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	अगर (xudma_is_pktdma(tx_chn->common.udmax)) अणु
		tx_chn->virq = xudma_pktdma_tflow_get_irq(tx_chn->common.udmax,
							  tx_chn->udma_tflow_id);
	पूर्ण अन्यथा अणु
		tx_chn->virq = k3_ringacc_get_ring_irq_num(tx_chn->ringtxcq);
	पूर्ण

	वापस tx_chn->virq;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tx_get_irq);

काष्ठा device *
	k3_udma_glue_tx_get_dma_device(काष्ठा k3_udma_glue_tx_channel *tx_chn)
अणु
	अगर (xudma_is_pktdma(tx_chn->common.udmax) &&
	    (tx_chn->common.atype_asel == 14 || tx_chn->common.atype_asel == 15))
		वापस &tx_chn->common.chan_dev;

	वापस xudma_get_device(tx_chn->common.udmax);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tx_get_dma_device);

व्योम k3_udma_glue_tx_dma_to_cppi5_addr(काष्ठा k3_udma_glue_tx_channel *tx_chn,
				       dma_addr_t *addr)
अणु
	अगर (!xudma_is_pktdma(tx_chn->common.udmax) ||
	    !tx_chn->common.atype_asel)
		वापस;

	*addr |= (u64)tx_chn->common.atype_asel << K3_ADDRESS_ASEL_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tx_dma_to_cppi5_addr);

व्योम k3_udma_glue_tx_cppi5_to_dma_addr(काष्ठा k3_udma_glue_tx_channel *tx_chn,
				       dma_addr_t *addr)
अणु
	अगर (!xudma_is_pktdma(tx_chn->common.udmax) ||
	    !tx_chn->common.atype_asel)
		वापस;

	*addr &= (u64)GENMASK(K3_ADDRESS_ASEL_SHIFT - 1, 0);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tx_cppi5_to_dma_addr);

अटल पूर्णांक k3_udma_glue_cfg_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn)
अणु
	स्थिर काष्ठा udma_tisci_rm *tisci_rm = rx_chn->common.tisci_rm;
	काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg req;
	पूर्णांक ret;

	स_रखो(&req, 0, माप(req));

	req.valid_params = TI_SCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID |
			   TI_SCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID |
			   TI_SCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID |
			   TI_SCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID;

	req.nav_id = tisci_rm->tisci_dev_id;
	req.index = rx_chn->udma_rchan_id;
	req.rx_fetch_size = rx_chn->common.hdesc_size >> 2;
	/*
	 * TODO: we can't support rxcq_qnum/RCHAN[a]_RCQ cfg with current sysfw
	 * and udmax impl, so just configure it to invalid value.
	 * req.rxcq_qnum = k3_ringacc_get_ring_id(rx_chn->flows[0].ringrx);
	 */
	req.rxcq_qnum = 0xFFFF;
	अगर (!xudma_is_pktdma(rx_chn->common.udmax) && rx_chn->flow_num &&
	    rx_chn->flow_id_base != rx_chn->udma_rchan_id) अणु
		/* Default flow + extra ones */
		req.valid_params |= TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_START_VALID |
				    TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_CNT_VALID;
		req.flowid_start = rx_chn->flow_id_base;
		req.flowid_cnt = rx_chn->flow_num;
	पूर्ण
	req.rx_chan_type = TI_SCI_RM_UDMAP_CHAN_TYPE_PKT_PBRR;
	req.rx_atype = rx_chn->common.atype_asel;

	ret = tisci_rm->tisci_udmap_ops->rx_ch_cfg(tisci_rm->tisci, &req);
	अगर (ret)
		dev_err(rx_chn->common.dev, "rchan%d cfg failed %d\n",
			rx_chn->udma_rchan_id, ret);

	वापस ret;
पूर्ण

अटल व्योम k3_udma_glue_release_rx_flow(काष्ठा k3_udma_glue_rx_channel *rx_chn,
					 u32 flow_num)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_num];

	अगर (IS_ERR_OR_शून्य(flow->udma_rflow))
		वापस;

	अगर (flow->ringrxfdq)
		k3_ringacc_ring_मुक्त(flow->ringrxfdq);

	अगर (flow->ringrx)
		k3_ringacc_ring_मुक्त(flow->ringrx);

	xudma_rflow_put(rx_chn->common.udmax, flow->udma_rflow);
	flow->udma_rflow = शून्य;
	rx_chn->flows_पढ़ोy--;
पूर्ण

अटल पूर्णांक k3_udma_glue_cfg_rx_flow(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				    u32 flow_idx,
				    काष्ठा k3_udma_glue_rx_flow_cfg *flow_cfg)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_idx];
	स्थिर काष्ठा udma_tisci_rm *tisci_rm = rx_chn->common.tisci_rm;
	काष्ठा device *dev = rx_chn->common.dev;
	काष्ठा ti_sci_msg_rm_udmap_flow_cfg req;
	पूर्णांक rx_ring_id;
	पूर्णांक rx_ringfdq_id;
	पूर्णांक ret = 0;

	flow->udma_rflow = xudma_rflow_get(rx_chn->common.udmax,
					   flow->udma_rflow_id);
	अगर (IS_ERR(flow->udma_rflow)) अणु
		ret = PTR_ERR(flow->udma_rflow);
		dev_err(dev, "UDMAX rflow get err %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (flow->udma_rflow_id != xudma_rflow_get_id(flow->udma_rflow)) अणु
		ret = -ENODEV;
		जाओ err_rflow_put;
	पूर्ण

	अगर (xudma_is_pktdma(rx_chn->common.udmax)) अणु
		rx_ringfdq_id = flow->udma_rflow_id +
				xudma_get_rflow_ring_offset(rx_chn->common.udmax);
		rx_ring_id = 0;
	पूर्ण अन्यथा अणु
		rx_ring_id = flow_cfg->ring_rxq_id;
		rx_ringfdq_id = flow_cfg->ring_rxfdq0_id;
	पूर्ण

	/* request and cfg rings */
	ret =  k3_ringacc_request_rings_pair(rx_chn->common.ringacc,
					     rx_ringfdq_id, rx_ring_id,
					     &flow->ringrxfdq,
					     &flow->ringrx);
	अगर (ret) अणु
		dev_err(dev, "Failed to get RX/RXFDQ rings %d\n", ret);
		जाओ err_rflow_put;
	पूर्ण

	/* Set the dma_dev क्रम the rings to be configured */
	flow_cfg->rx_cfg.dma_dev = k3_udma_glue_rx_get_dma_device(rx_chn);
	flow_cfg->rxfdq_cfg.dma_dev = flow_cfg->rx_cfg.dma_dev;

	/* Set the ASEL value क्रम DMA rings of PKTDMA */
	अगर (xudma_is_pktdma(rx_chn->common.udmax)) अणु
		flow_cfg->rx_cfg.asel = rx_chn->common.atype_asel;
		flow_cfg->rxfdq_cfg.asel = rx_chn->common.atype_asel;
	पूर्ण

	ret = k3_ringacc_ring_cfg(flow->ringrx, &flow_cfg->rx_cfg);
	अगर (ret) अणु
		dev_err(dev, "Failed to cfg ringrx %d\n", ret);
		जाओ err_ringrxfdq_मुक्त;
	पूर्ण

	ret = k3_ringacc_ring_cfg(flow->ringrxfdq, &flow_cfg->rxfdq_cfg);
	अगर (ret) अणु
		dev_err(dev, "Failed to cfg ringrxfdq %d\n", ret);
		जाओ err_ringrxfdq_मुक्त;
	पूर्ण

	अगर (rx_chn->remote) अणु
		rx_ring_id = TI_SCI_RESOURCE_शून्य;
		rx_ringfdq_id = TI_SCI_RESOURCE_शून्य;
	पूर्ण अन्यथा अणु
		rx_ring_id = k3_ringacc_get_ring_id(flow->ringrx);
		rx_ringfdq_id = k3_ringacc_get_ring_id(flow->ringrxfdq);
	पूर्ण

	स_रखो(&req, 0, माप(req));

	req.valid_params =
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_EINFO_PRESENT_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_PSINFO_PRESENT_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_ERROR_HANDLING_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DESC_TYPE_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_SEL_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_SEL_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_SEL_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_SEL_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID;
	req.nav_id = tisci_rm->tisci_dev_id;
	req.flow_index = flow->udma_rflow_id;
	अगर (rx_chn->common.epib)
		req.rx_einfo_present = 1;
	अगर (rx_chn->common.psdata_size)
		req.rx_psinfo_present = 1;
	अगर (flow_cfg->rx_error_handling)
		req.rx_error_handling = 1;
	req.rx_desc_type = 0;
	req.rx_dest_qnum = rx_ring_id;
	req.rx_src_tag_hi_sel = 0;
	req.rx_src_tag_lo_sel = flow_cfg->src_tag_lo_sel;
	req.rx_dest_tag_hi_sel = 0;
	req.rx_dest_tag_lo_sel = 0;
	req.rx_fdq0_sz0_qnum = rx_ringfdq_id;
	req.rx_fdq1_qnum = rx_ringfdq_id;
	req.rx_fdq2_qnum = rx_ringfdq_id;
	req.rx_fdq3_qnum = rx_ringfdq_id;

	ret = tisci_rm->tisci_udmap_ops->rx_flow_cfg(tisci_rm->tisci, &req);
	अगर (ret) अणु
		dev_err(dev, "flow%d config failed: %d\n", flow->udma_rflow_id,
			ret);
		जाओ err_ringrxfdq_मुक्त;
	पूर्ण

	rx_chn->flows_पढ़ोy++;
	dev_dbg(dev, "flow%d config done. ready:%d\n",
		flow->udma_rflow_id, rx_chn->flows_पढ़ोy);

	वापस 0;

err_ringrxfdq_मुक्त:
	k3_ringacc_ring_मुक्त(flow->ringrxfdq);
	k3_ringacc_ring_मुक्त(flow->ringrx);

err_rflow_put:
	xudma_rflow_put(rx_chn->common.udmax, flow->udma_rflow);
	flow->udma_rflow = शून्य;

	वापस ret;
पूर्ण

अटल व्योम k3_udma_glue_dump_rx_chn(काष्ठा k3_udma_glue_rx_channel *chn)
अणु
	काष्ठा device *dev = chn->common.dev;

	dev_dbg(dev, "dump_rx_chn:\n"
		"udma_rchan_id: %d\n"
		"src_thread: %08x\n"
		"dst_thread: %08x\n"
		"epib: %d\n"
		"hdesc_size: %u\n"
		"psdata_size: %u\n"
		"swdata_size: %u\n"
		"flow_id_base: %d\n"
		"flow_num: %d\n",
		chn->udma_rchan_id,
		chn->common.src_thपढ़ो,
		chn->common.dst_thपढ़ो,
		chn->common.epib,
		chn->common.hdesc_size,
		chn->common.psdata_size,
		chn->common.swdata_size,
		chn->flow_id_base,
		chn->flow_num);
पूर्ण

अटल व्योम k3_udma_glue_dump_rx_rt_chn(काष्ठा k3_udma_glue_rx_channel *chn,
					अक्षर *mark)
अणु
	काष्ठा device *dev = chn->common.dev;

	dev_dbg(dev, "=== dump ===> %s\n", mark);

	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_CTL_REG,
		xudma_rchanrt_पढ़ो(chn->udma_rchanx, UDMA_CHAN_RT_CTL_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_PEER_RT_EN_REG,
		xudma_rchanrt_पढ़ो(chn->udma_rchanx,
				   UDMA_CHAN_RT_PEER_RT_EN_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_PCNT_REG,
		xudma_rchanrt_पढ़ो(chn->udma_rchanx, UDMA_CHAN_RT_PCNT_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_BCNT_REG,
		xudma_rchanrt_पढ़ो(chn->udma_rchanx, UDMA_CHAN_RT_BCNT_REG));
	dev_dbg(dev, "0x%08X: %08X\n", UDMA_CHAN_RT_SBCNT_REG,
		xudma_rchanrt_पढ़ो(chn->udma_rchanx, UDMA_CHAN_RT_SBCNT_REG));
पूर्ण

अटल पूर्णांक
k3_udma_glue_allocate_rx_flows(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			       काष्ठा k3_udma_glue_rx_channel_cfg *cfg)
अणु
	पूर्णांक ret;

	/* शेष rflow */
	अगर (cfg->flow_id_use_rxchan_id)
		वापस 0;

	/* not a GP rflows */
	अगर (rx_chn->flow_id_base != -1 &&
	    !xudma_rflow_is_gp(rx_chn->common.udmax, rx_chn->flow_id_base))
		वापस 0;

	/* Allocate range of GP rflows */
	ret = xudma_alloc_gp_rflow_range(rx_chn->common.udmax,
					 rx_chn->flow_id_base,
					 rx_chn->flow_num);
	अगर (ret < 0) अणु
		dev_err(rx_chn->common.dev, "UDMAX reserve_rflow %d cnt:%d err: %d\n",
			rx_chn->flow_id_base, rx_chn->flow_num, ret);
		वापस ret;
	पूर्ण
	rx_chn->flow_id_base = ret;

	वापस 0;
पूर्ण

अटल काष्ठा k3_udma_glue_rx_channel *
k3_udma_glue_request_rx_chn_priv(काष्ठा device *dev, स्थिर अक्षर *name,
				 काष्ठा k3_udma_glue_rx_channel_cfg *cfg)
अणु
	काष्ठा k3_udma_glue_rx_channel *rx_chn;
	काष्ठा psil_endpoपूर्णांक_config *ep_cfg;
	पूर्णांक ret, i;

	अगर (cfg->flow_id_num <= 0)
		वापस ERR_PTR(-EINVAL);

	अगर (cfg->flow_id_num != 1 &&
	    (cfg->def_flow_cfg || cfg->flow_id_use_rxchan_id))
		वापस ERR_PTR(-EINVAL);

	rx_chn = devm_kzalloc(dev, माप(*rx_chn), GFP_KERNEL);
	अगर (!rx_chn)
		वापस ERR_PTR(-ENOMEM);

	rx_chn->common.dev = dev;
	rx_chn->common.swdata_size = cfg->swdata_size;
	rx_chn->remote = false;

	/* parse of udmap channel */
	ret = of_k3_udma_glue_parse_chn(dev->of_node, name,
					&rx_chn->common, false);
	अगर (ret)
		जाओ err;

	rx_chn->common.hdesc_size = cppi5_hdesc_calc_size(rx_chn->common.epib,
						rx_chn->common.psdata_size,
						rx_chn->common.swdata_size);

	ep_cfg = rx_chn->common.ep_config;

	अगर (xudma_is_pktdma(rx_chn->common.udmax))
		rx_chn->udma_rchan_id = ep_cfg->mapped_channel_id;
	अन्यथा
		rx_chn->udma_rchan_id = -1;

	/* request and cfg UDMAP RX channel */
	rx_chn->udma_rchanx = xudma_rchan_get(rx_chn->common.udmax,
					      rx_chn->udma_rchan_id);
	अगर (IS_ERR(rx_chn->udma_rchanx)) अणु
		ret = PTR_ERR(rx_chn->udma_rchanx);
		dev_err(dev, "UDMAX rchanx get err %d\n", ret);
		जाओ err;
	पूर्ण
	rx_chn->udma_rchan_id = xudma_rchan_get_id(rx_chn->udma_rchanx);

	rx_chn->common.chan_dev.class = &k3_udma_glue_devclass;
	rx_chn->common.chan_dev.parent = xudma_get_device(rx_chn->common.udmax);
	dev_set_name(&rx_chn->common.chan_dev, "rchan%d-0x%04x",
		     rx_chn->udma_rchan_id, rx_chn->common.src_thपढ़ो);
	ret = device_रेजिस्टर(&rx_chn->common.chan_dev);
	अगर (ret) अणु
		dev_err(dev, "Channel Device registration failed %d\n", ret);
		rx_chn->common.chan_dev.parent = शून्य;
		जाओ err;
	पूर्ण

	अगर (xudma_is_pktdma(rx_chn->common.udmax)) अणु
		/* prepare the channel device as coherent */
		rx_chn->common.chan_dev.dma_coherent = true;
		dma_coerce_mask_and_coherent(&rx_chn->common.chan_dev,
					     DMA_BIT_MASK(48));
	पूर्ण

	अगर (xudma_is_pktdma(rx_chn->common.udmax)) अणु
		पूर्णांक flow_start = cfg->flow_id_base;
		पूर्णांक flow_end;

		अगर (flow_start == -1)
			flow_start = ep_cfg->flow_start;

		flow_end = flow_start + cfg->flow_id_num - 1;
		अगर (flow_start < ep_cfg->flow_start ||
		    flow_end > (ep_cfg->flow_start + ep_cfg->flow_num - 1)) अणु
			dev_err(dev, "Invalid flow range requested\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		rx_chn->flow_id_base = flow_start;
	पूर्ण अन्यथा अणु
		rx_chn->flow_id_base = cfg->flow_id_base;

		/* Use RX channel id as flow id: target dev can't generate flow_id */
		अगर (cfg->flow_id_use_rxchan_id)
			rx_chn->flow_id_base = rx_chn->udma_rchan_id;
	पूर्ण

	rx_chn->flow_num = cfg->flow_id_num;

	rx_chn->flows = devm_kसुस्मृति(dev, rx_chn->flow_num,
				     माप(*rx_chn->flows), GFP_KERNEL);
	अगर (!rx_chn->flows) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = k3_udma_glue_allocate_rx_flows(rx_chn, cfg);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < rx_chn->flow_num; i++)
		rx_chn->flows[i].udma_rflow_id = rx_chn->flow_id_base + i;

	/* request and cfg psi-l */
	rx_chn->common.dst_thपढ़ो =
			xudma_dev_get_psil_base(rx_chn->common.udmax) +
			rx_chn->udma_rchan_id;

	ret = k3_udma_glue_cfg_rx_chn(rx_chn);
	अगर (ret) अणु
		dev_err(dev, "Failed to cfg rchan %d\n", ret);
		जाओ err;
	पूर्ण

	/* init शेष RX flow only अगर flow_num = 1 */
	अगर (cfg->def_flow_cfg) अणु
		ret = k3_udma_glue_cfg_rx_flow(rx_chn, 0, cfg->def_flow_cfg);
		अगर (ret)
			जाओ err;
	पूर्ण

	k3_udma_glue_dump_rx_chn(rx_chn);

	वापस rx_chn;

err:
	k3_udma_glue_release_rx_chn(rx_chn);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा k3_udma_glue_rx_channel *
k3_udma_glue_request_remote_rx_chn(काष्ठा device *dev, स्थिर अक्षर *name,
				   काष्ठा k3_udma_glue_rx_channel_cfg *cfg)
अणु
	काष्ठा k3_udma_glue_rx_channel *rx_chn;
	पूर्णांक ret, i;

	अगर (cfg->flow_id_num <= 0 ||
	    cfg->flow_id_use_rxchan_id ||
	    cfg->def_flow_cfg ||
	    cfg->flow_id_base < 0)
		वापस ERR_PTR(-EINVAL);

	/*
	 * Remote RX channel is under control of Remote CPU core, so
	 * Linux can only request and manipulate by dedicated RX flows
	 */

	rx_chn = devm_kzalloc(dev, माप(*rx_chn), GFP_KERNEL);
	अगर (!rx_chn)
		वापस ERR_PTR(-ENOMEM);

	rx_chn->common.dev = dev;
	rx_chn->common.swdata_size = cfg->swdata_size;
	rx_chn->remote = true;
	rx_chn->udma_rchan_id = -1;
	rx_chn->flow_num = cfg->flow_id_num;
	rx_chn->flow_id_base = cfg->flow_id_base;
	rx_chn->psil_paired = false;

	/* parse of udmap channel */
	ret = of_k3_udma_glue_parse_chn(dev->of_node, name,
					&rx_chn->common, false);
	अगर (ret)
		जाओ err;

	rx_chn->common.hdesc_size = cppi5_hdesc_calc_size(rx_chn->common.epib,
						rx_chn->common.psdata_size,
						rx_chn->common.swdata_size);

	rx_chn->flows = devm_kसुस्मृति(dev, rx_chn->flow_num,
				     माप(*rx_chn->flows), GFP_KERNEL);
	अगर (!rx_chn->flows) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	rx_chn->common.chan_dev.class = &k3_udma_glue_devclass;
	rx_chn->common.chan_dev.parent = xudma_get_device(rx_chn->common.udmax);
	dev_set_name(&rx_chn->common.chan_dev, "rchan_remote-0x%04x",
		     rx_chn->common.src_thपढ़ो);
	ret = device_रेजिस्टर(&rx_chn->common.chan_dev);
	अगर (ret) अणु
		dev_err(dev, "Channel Device registration failed %d\n", ret);
		rx_chn->common.chan_dev.parent = शून्य;
		जाओ err;
	पूर्ण

	अगर (xudma_is_pktdma(rx_chn->common.udmax)) अणु
		/* prepare the channel device as coherent */
		rx_chn->common.chan_dev.dma_coherent = true;
		dma_coerce_mask_and_coherent(&rx_chn->common.chan_dev,
					     DMA_BIT_MASK(48));
	पूर्ण

	ret = k3_udma_glue_allocate_rx_flows(rx_chn, cfg);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < rx_chn->flow_num; i++)
		rx_chn->flows[i].udma_rflow_id = rx_chn->flow_id_base + i;

	k3_udma_glue_dump_rx_chn(rx_chn);

	वापस rx_chn;

err:
	k3_udma_glue_release_rx_chn(rx_chn);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा k3_udma_glue_rx_channel *
k3_udma_glue_request_rx_chn(काष्ठा device *dev, स्थिर अक्षर *name,
			    काष्ठा k3_udma_glue_rx_channel_cfg *cfg)
अणु
	अगर (cfg->remote)
		वापस k3_udma_glue_request_remote_rx_chn(dev, name, cfg);
	अन्यथा
		वापस k3_udma_glue_request_rx_chn_priv(dev, name, cfg);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_request_rx_chn);

व्योम k3_udma_glue_release_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn)
अणु
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(rx_chn->common.udmax))
		वापस;

	अगर (rx_chn->psil_paired) अणु
		xudma_navss_psil_unpair(rx_chn->common.udmax,
					rx_chn->common.src_thपढ़ो,
					rx_chn->common.dst_thपढ़ो);
		rx_chn->psil_paired = false;
	पूर्ण

	क्रम (i = 0; i < rx_chn->flow_num; i++)
		k3_udma_glue_release_rx_flow(rx_chn, i);

	अगर (xudma_rflow_is_gp(rx_chn->common.udmax, rx_chn->flow_id_base))
		xudma_मुक्त_gp_rflow_range(rx_chn->common.udmax,
					  rx_chn->flow_id_base,
					  rx_chn->flow_num);

	अगर (!IS_ERR_OR_शून्य(rx_chn->udma_rchanx))
		xudma_rchan_put(rx_chn->common.udmax,
				rx_chn->udma_rchanx);

	अगर (rx_chn->common.chan_dev.parent) अणु
		device_unरेजिस्टर(&rx_chn->common.chan_dev);
		rx_chn->common.chan_dev.parent = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_release_rx_chn);

पूर्णांक k3_udma_glue_rx_flow_init(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			      u32 flow_idx,
			      काष्ठा k3_udma_glue_rx_flow_cfg *flow_cfg)
अणु
	अगर (flow_idx >= rx_chn->flow_num)
		वापस -EINVAL;

	वापस k3_udma_glue_cfg_rx_flow(rx_chn, flow_idx, flow_cfg);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_flow_init);

u32 k3_udma_glue_rx_flow_get_fdq_id(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				    u32 flow_idx)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow;

	अगर (flow_idx >= rx_chn->flow_num)
		वापस -EINVAL;

	flow = &rx_chn->flows[flow_idx];

	वापस k3_ringacc_get_ring_id(flow->ringrxfdq);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_flow_get_fdq_id);

u32 k3_udma_glue_rx_get_flow_id_base(काष्ठा k3_udma_glue_rx_channel *rx_chn)
अणु
	वापस rx_chn->flow_id_base;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_get_flow_id_base);

पूर्णांक k3_udma_glue_rx_flow_enable(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				u32 flow_idx)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_idx];
	स्थिर काष्ठा udma_tisci_rm *tisci_rm = rx_chn->common.tisci_rm;
	काष्ठा device *dev = rx_chn->common.dev;
	काष्ठा ti_sci_msg_rm_udmap_flow_cfg req;
	पूर्णांक rx_ring_id;
	पूर्णांक rx_ringfdq_id;
	पूर्णांक ret = 0;

	अगर (!rx_chn->remote)
		वापस -EINVAL;

	rx_ring_id = k3_ringacc_get_ring_id(flow->ringrx);
	rx_ringfdq_id = k3_ringacc_get_ring_id(flow->ringrxfdq);

	स_रखो(&req, 0, माप(req));

	req.valid_params =
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID;
	req.nav_id = tisci_rm->tisci_dev_id;
	req.flow_index = flow->udma_rflow_id;
	req.rx_dest_qnum = rx_ring_id;
	req.rx_fdq0_sz0_qnum = rx_ringfdq_id;
	req.rx_fdq1_qnum = rx_ringfdq_id;
	req.rx_fdq2_qnum = rx_ringfdq_id;
	req.rx_fdq3_qnum = rx_ringfdq_id;

	ret = tisci_rm->tisci_udmap_ops->rx_flow_cfg(tisci_rm->tisci, &req);
	अगर (ret) अणु
		dev_err(dev, "flow%d enable failed: %d\n", flow->udma_rflow_id,
			ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_flow_enable);

पूर्णांक k3_udma_glue_rx_flow_disable(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				 u32 flow_idx)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_idx];
	स्थिर काष्ठा udma_tisci_rm *tisci_rm = rx_chn->common.tisci_rm;
	काष्ठा device *dev = rx_chn->common.dev;
	काष्ठा ti_sci_msg_rm_udmap_flow_cfg req;
	पूर्णांक ret = 0;

	अगर (!rx_chn->remote)
		वापस -EINVAL;

	स_रखो(&req, 0, माप(req));
	req.valid_params =
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID |
			TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID;
	req.nav_id = tisci_rm->tisci_dev_id;
	req.flow_index = flow->udma_rflow_id;
	req.rx_dest_qnum = TI_SCI_RESOURCE_शून्य;
	req.rx_fdq0_sz0_qnum = TI_SCI_RESOURCE_शून्य;
	req.rx_fdq1_qnum = TI_SCI_RESOURCE_शून्य;
	req.rx_fdq2_qnum = TI_SCI_RESOURCE_शून्य;
	req.rx_fdq3_qnum = TI_SCI_RESOURCE_शून्य;

	ret = tisci_rm->tisci_udmap_ops->rx_flow_cfg(tisci_rm->tisci, &req);
	अगर (ret) अणु
		dev_err(dev, "flow%d disable failed: %d\n", flow->udma_rflow_id,
			ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_flow_disable);

पूर्णांक k3_udma_glue_enable_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn)
अणु
	पूर्णांक ret;

	अगर (rx_chn->remote)
		वापस -EINVAL;

	अगर (rx_chn->flows_पढ़ोy < rx_chn->flow_num)
		वापस -EINVAL;

	ret = xudma_navss_psil_pair(rx_chn->common.udmax,
				    rx_chn->common.src_thपढ़ो,
				    rx_chn->common.dst_thपढ़ो);
	अगर (ret) अणु
		dev_err(rx_chn->common.dev, "PSI-L request err %d\n", ret);
		वापस ret;
	पूर्ण

	rx_chn->psil_paired = true;

	xudma_rchanrt_ग_लिखो(rx_chn->udma_rchanx, UDMA_CHAN_RT_CTL_REG,
			    UDMA_CHAN_RT_CTL_EN);

	xudma_rchanrt_ग_लिखो(rx_chn->udma_rchanx, UDMA_CHAN_RT_PEER_RT_EN_REG,
			    UDMA_PEER_RT_EN_ENABLE);

	k3_udma_glue_dump_rx_rt_chn(rx_chn, "rxrt en");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_enable_rx_chn);

व्योम k3_udma_glue_disable_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn)
अणु
	k3_udma_glue_dump_rx_rt_chn(rx_chn, "rxrt dis1");

	xudma_rchanrt_ग_लिखो(rx_chn->udma_rchanx,
			    UDMA_CHAN_RT_PEER_RT_EN_REG, 0);
	xudma_rchanrt_ग_लिखो(rx_chn->udma_rchanx, UDMA_CHAN_RT_CTL_REG, 0);

	k3_udma_glue_dump_rx_rt_chn(rx_chn, "rxrt dis2");

	अगर (rx_chn->psil_paired) अणु
		xudma_navss_psil_unpair(rx_chn->common.udmax,
					rx_chn->common.src_thपढ़ो,
					rx_chn->common.dst_thपढ़ो);
		rx_chn->psil_paired = false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_disable_rx_chn);

व्योम k3_udma_glue_tकरोwn_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			       bool sync)
अणु
	पूर्णांक i = 0;
	u32 val;

	अगर (rx_chn->remote)
		वापस;

	k3_udma_glue_dump_rx_rt_chn(rx_chn, "rxrt tdown1");

	xudma_rchanrt_ग_लिखो(rx_chn->udma_rchanx, UDMA_CHAN_RT_PEER_RT_EN_REG,
			    UDMA_PEER_RT_EN_ENABLE | UDMA_PEER_RT_EN_TEARDOWN);

	val = xudma_rchanrt_पढ़ो(rx_chn->udma_rchanx, UDMA_CHAN_RT_CTL_REG);

	जबतक (sync && (val & UDMA_CHAN_RT_CTL_EN)) अणु
		val = xudma_rchanrt_पढ़ो(rx_chn->udma_rchanx,
					 UDMA_CHAN_RT_CTL_REG);
		udelay(1);
		अगर (i > K3_UDMAX_TDOWN_TIMEOUT_US) अणु
			dev_err(rx_chn->common.dev, "RX tdown timeout\n");
			अवरोध;
		पूर्ण
		i++;
	पूर्ण

	val = xudma_rchanrt_पढ़ो(rx_chn->udma_rchanx,
				 UDMA_CHAN_RT_PEER_RT_EN_REG);
	अगर (sync && (val & UDMA_PEER_RT_EN_ENABLE))
		dev_err(rx_chn->common.dev, "TX tdown peer not stopped\n");
	k3_udma_glue_dump_rx_rt_chn(rx_chn, "rxrt tdown2");
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_tकरोwn_rx_chn);

व्योम k3_udma_glue_reset_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
		u32 flow_num, व्योम *data,
		व्योम (*cleanup)(व्योम *data, dma_addr_t desc_dma), bool skip_fdq)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_num];
	काष्ठा device *dev = rx_chn->common.dev;
	dma_addr_t desc_dma;
	पूर्णांक occ_rx, i, ret;

	/* reset RXCQ as it is not input क्रम udma - expected to be empty */
	occ_rx = k3_ringacc_ring_get_occ(flow->ringrx);
	dev_dbg(dev, "RX reset flow %u occ_rx %u\n", flow_num, occ_rx);

	/* Skip RX FDQ in हाल one FDQ is used क्रम the set of flows */
	अगर (skip_fdq)
		जाओ करो_reset;

	/*
	 * RX FDQ reset need to be special way as it is input क्रम udma and its
	 * state cached by udma, so:
	 * 1) save RX FDQ occ
	 * 2) clean up RX FDQ and call callback .cleanup() क्रम each desc
	 * 3) reset RX FDQ in a special way
	 */
	occ_rx = k3_ringacc_ring_get_occ(flow->ringrxfdq);
	dev_dbg(dev, "RX reset flow %u occ_rx_fdq %u\n", flow_num, occ_rx);

	क्रम (i = 0; i < occ_rx; i++) अणु
		ret = k3_ringacc_ring_pop(flow->ringrxfdq, &desc_dma);
		अगर (ret) अणु
			अगर (ret != -ENODATA)
				dev_err(dev, "RX reset pop %d\n", ret);
			अवरोध;
		पूर्ण
		cleanup(data, desc_dma);
	पूर्ण

	k3_ringacc_ring_reset_dma(flow->ringrxfdq, occ_rx);

करो_reset:
	k3_ringacc_ring_reset(flow->ringrx);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_reset_rx_chn);

पूर्णांक k3_udma_glue_push_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			     u32 flow_num, काष्ठा cppi5_host_desc_t *desc_rx,
			     dma_addr_t desc_dma)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_num];

	वापस k3_ringacc_ring_push(flow->ringrxfdq, &desc_dma);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_push_rx_chn);

पूर्णांक k3_udma_glue_pop_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			    u32 flow_num, dma_addr_t *desc_dma)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow = &rx_chn->flows[flow_num];

	वापस k3_ringacc_ring_pop(flow->ringrx, desc_dma);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_pop_rx_chn);

पूर्णांक k3_udma_glue_rx_get_irq(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			    u32 flow_num)
अणु
	काष्ठा k3_udma_glue_rx_flow *flow;

	flow = &rx_chn->flows[flow_num];

	अगर (xudma_is_pktdma(rx_chn->common.udmax)) अणु
		flow->virq = xudma_pktdma_rflow_get_irq(rx_chn->common.udmax,
							flow->udma_rflow_id);
	पूर्ण अन्यथा अणु
		flow->virq = k3_ringacc_get_ring_irq_num(flow->ringrx);
	पूर्ण

	वापस flow->virq;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_get_irq);

काष्ठा device *
	k3_udma_glue_rx_get_dma_device(काष्ठा k3_udma_glue_rx_channel *rx_chn)
अणु
	अगर (xudma_is_pktdma(rx_chn->common.udmax) &&
	    (rx_chn->common.atype_asel == 14 || rx_chn->common.atype_asel == 15))
		वापस &rx_chn->common.chan_dev;

	वापस xudma_get_device(rx_chn->common.udmax);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_get_dma_device);

व्योम k3_udma_glue_rx_dma_to_cppi5_addr(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				       dma_addr_t *addr)
अणु
	अगर (!xudma_is_pktdma(rx_chn->common.udmax) ||
	    !rx_chn->common.atype_asel)
		वापस;

	*addr |= (u64)rx_chn->common.atype_asel << K3_ADDRESS_ASEL_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_dma_to_cppi5_addr);

व्योम k3_udma_glue_rx_cppi5_to_dma_addr(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				       dma_addr_t *addr)
अणु
	अगर (!xudma_is_pktdma(rx_chn->common.udmax) ||
	    !rx_chn->common.atype_asel)
		वापस;

	*addr &= (u64)GENMASK(K3_ADDRESS_ASEL_SHIFT - 1, 0);
पूर्ण
EXPORT_SYMBOL_GPL(k3_udma_glue_rx_cppi5_to_dma_addr);

अटल पूर्णांक __init k3_udma_glue_class_init(व्योम)
अणु
	वापस class_रेजिस्टर(&k3_udma_glue_devclass);
पूर्ण
arch_initcall(k3_udma_glue_class_init);
