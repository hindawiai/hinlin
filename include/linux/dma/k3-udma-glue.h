<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 */

#अगर_अघोषित K3_UDMA_GLUE_H_
#घोषणा K3_UDMA_GLUE_H_

#समावेश <linux/types.h>
#समावेश <linux/soc/ti/k3-ringacc.h>
#समावेश <linux/dma/ti-cppi5.h>

काष्ठा k3_udma_glue_tx_channel_cfg अणु
	काष्ठा k3_ring_cfg tx_cfg;
	काष्ठा k3_ring_cfg txcq_cfg;

	bool tx_छोड़ो_on_err;
	bool tx_filt_einfo;
	bool tx_filt_pswords;
	bool tx_supr_tdpkt;
	u32  swdata_size;
पूर्ण;

काष्ठा k3_udma_glue_tx_channel;

काष्ठा k3_udma_glue_tx_channel *k3_udma_glue_request_tx_chn(काष्ठा device *dev,
		स्थिर अक्षर *name, काष्ठा k3_udma_glue_tx_channel_cfg *cfg);

व्योम k3_udma_glue_release_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn);
पूर्णांक k3_udma_glue_push_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			     काष्ठा cppi5_host_desc_t *desc_tx,
			     dma_addr_t desc_dma);
पूर्णांक k3_udma_glue_pop_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			    dma_addr_t *desc_dma);
पूर्णांक k3_udma_glue_enable_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn);
व्योम k3_udma_glue_disable_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn);
व्योम k3_udma_glue_tकरोwn_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
			       bool sync);
व्योम k3_udma_glue_reset_tx_chn(काष्ठा k3_udma_glue_tx_channel *tx_chn,
		व्योम *data, व्योम (*cleanup)(व्योम *data, dma_addr_t desc_dma));
u32 k3_udma_glue_tx_get_hdesc_size(काष्ठा k3_udma_glue_tx_channel *tx_chn);
u32 k3_udma_glue_tx_get_txcq_id(काष्ठा k3_udma_glue_tx_channel *tx_chn);
पूर्णांक k3_udma_glue_tx_get_irq(काष्ठा k3_udma_glue_tx_channel *tx_chn);
काष्ठा device *
	k3_udma_glue_tx_get_dma_device(काष्ठा k3_udma_glue_tx_channel *tx_chn);
व्योम k3_udma_glue_tx_dma_to_cppi5_addr(काष्ठा k3_udma_glue_tx_channel *tx_chn,
				       dma_addr_t *addr);
व्योम k3_udma_glue_tx_cppi5_to_dma_addr(काष्ठा k3_udma_glue_tx_channel *tx_chn,
				       dma_addr_t *addr);

क्रमागत अणु
	K3_UDMA_GLUE_SRC_TAG_LO_KEEP = 0,
	K3_UDMA_GLUE_SRC_TAG_LO_USE_FLOW_REG = 1,
	K3_UDMA_GLUE_SRC_TAG_LO_USE_REMOTE_FLOW_ID = 2,
	K3_UDMA_GLUE_SRC_TAG_LO_USE_REMOTE_SRC_TAG = 4,
पूर्ण;

/**
 * k3_udma_glue_rx_flow_cfg - UDMA RX flow cfg
 *
 * @rx_cfg:		RX ring configuration
 * @rxfdq_cfg:		RX मुक्त Host PD ring configuration
 * @ring_rxq_id:	RX ring id (or -1 क्रम any)
 * @ring_rxfdq0_id:	RX मुक्त Host PD ring (FDQ) अगर (or -1 क्रम any)
 * @rx_error_handling:	Rx Error Handling Mode (0 - drop, 1 - re-try)
 * @src_tag_lo_sel:	Rx Source Tag Low Byte Selector in Host PD
 */
काष्ठा k3_udma_glue_rx_flow_cfg अणु
	काष्ठा k3_ring_cfg rx_cfg;
	काष्ठा k3_ring_cfg rxfdq_cfg;
	पूर्णांक ring_rxq_id;
	पूर्णांक ring_rxfdq0_id;
	bool rx_error_handling;
	पूर्णांक src_tag_lo_sel;
पूर्ण;

/**
 * k3_udma_glue_rx_channel_cfg - UDMA RX channel cfg
 *
 * @psdata_size:	SW Data is present in Host PD of @swdata_size bytes
 * @flow_id_base:	first flow_id used by channel.
 *			अगर @flow_id_base = -1 - range of GP rflows will be
 *			allocated dynamically.
 * @flow_id_num:	number of RX flows used by channel
 * @flow_id_use_rxchan_id:	use RX channel id as flow id,
 *				used only अगर @flow_id_num = 1
 * @remote		indication that RX channel is remote - some remote CPU
 *			core owns and control the RX channel. Linux Host only
 *			allowed to attach and configure RX Flow within RX
 *			channel. अगर set - not RX channel operation will be
 *			perक्रमmed by K3 NAVSS DMA glue पूर्णांकerface.
 * @def_flow_cfg	शेष RX flow configuration,
 *			used only अगर @flow_id_num = 1
 */
काष्ठा k3_udma_glue_rx_channel_cfg अणु
	u32  swdata_size;
	पूर्णांक  flow_id_base;
	पूर्णांक  flow_id_num;
	bool flow_id_use_rxchan_id;
	bool remote;

	काष्ठा k3_udma_glue_rx_flow_cfg *def_flow_cfg;
पूर्ण;

काष्ठा k3_udma_glue_rx_channel;

काष्ठा k3_udma_glue_rx_channel *k3_udma_glue_request_rx_chn(
		काष्ठा device *dev,
		स्थिर अक्षर *name,
		काष्ठा k3_udma_glue_rx_channel_cfg *cfg);

व्योम k3_udma_glue_release_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn);
पूर्णांक k3_udma_glue_enable_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn);
व्योम k3_udma_glue_disable_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn);
व्योम k3_udma_glue_tकरोwn_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			       bool sync);
पूर्णांक k3_udma_glue_push_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
		u32 flow_num, काष्ठा cppi5_host_desc_t *desc_tx,
		dma_addr_t desc_dma);
पूर्णांक k3_udma_glue_pop_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
		u32 flow_num, dma_addr_t *desc_dma);
पूर्णांक k3_udma_glue_rx_flow_init(काष्ठा k3_udma_glue_rx_channel *rx_chn,
		u32 flow_idx, काष्ठा k3_udma_glue_rx_flow_cfg *flow_cfg);
u32 k3_udma_glue_rx_flow_get_fdq_id(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				    u32 flow_idx);
u32 k3_udma_glue_rx_get_flow_id_base(काष्ठा k3_udma_glue_rx_channel *rx_chn);
पूर्णांक k3_udma_glue_rx_get_irq(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			    u32 flow_num);
व्योम k3_udma_glue_rx_put_irq(काष्ठा k3_udma_glue_rx_channel *rx_chn,
			     u32 flow_num);
व्योम k3_udma_glue_reset_rx_chn(काष्ठा k3_udma_glue_rx_channel *rx_chn,
		u32 flow_num, व्योम *data,
		व्योम (*cleanup)(व्योम *data, dma_addr_t desc_dma),
		bool skip_fdq);
पूर्णांक k3_udma_glue_rx_flow_enable(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				u32 flow_idx);
पूर्णांक k3_udma_glue_rx_flow_disable(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				 u32 flow_idx);
काष्ठा device *
	k3_udma_glue_rx_get_dma_device(काष्ठा k3_udma_glue_rx_channel *rx_chn);
व्योम k3_udma_glue_rx_dma_to_cppi5_addr(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				       dma_addr_t *addr);
व्योम k3_udma_glue_rx_cppi5_to_dma_addr(काष्ठा k3_udma_glue_rx_channel *rx_chn,
				       dma_addr_t *addr);

#पूर्ण_अगर /* K3_UDMA_GLUE_H_ */
