<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Texas Instruments CPDMA Driver
 *
 * Copyright (C) 2010 Texas Instruments
 *
 */
#अगर_अघोषित __DAVINCI_CPDMA_H__
#घोषणा __DAVINCI_CPDMA_H__

#घोषणा CPDMA_MAX_CHANNELS	BITS_PER_LONG

#घोषणा CPDMA_RX_SOURCE_PORT(__status__)	((__status__ >> 16) & 0x7)

#घोषणा CPDMA_RX_VLAN_ENCAP BIT(19)

#घोषणा CPDMA_EOI_RX_THRESH	0x0
#घोषणा CPDMA_EOI_RX		0x1
#घोषणा CPDMA_EOI_TX		0x2
#घोषणा CPDMA_EOI_MISC		0x3

काष्ठा cpdma_params अणु
	काष्ठा device		*dev;
	व्योम __iomem		*dmaregs;
	व्योम __iomem		*txhdp, *rxhdp, *txcp, *rxcp;
	व्योम __iomem		*rxthresh, *rxमुक्त;
	पूर्णांक			num_chan;
	bool			has_soft_reset;
	पूर्णांक			min_packet_size;
	dma_addr_t		desc_mem_phys;
	dma_addr_t		desc_hw_addr;
	पूर्णांक			desc_mem_size;
	पूर्णांक			desc_align;
	u32			bus_freq_mhz;
	u32			descs_pool_size;

	/*
	 * Some instances of embedded cpdma controllers have extra control and
	 * status रेजिस्टरs.  The following flag enables access to these
	 * "extended" रेजिस्टरs.
	 */
	bool			has_ext_regs;
पूर्ण;

काष्ठा cpdma_chan_stats अणु
	u32			head_enqueue;
	u32			tail_enqueue;
	u32			pad_enqueue;
	u32			misqueued;
	u32			desc_alloc_fail;
	u32			pad_alloc_fail;
	u32			runt_receive_buff;
	u32			runt_transmit_buff;
	u32			empty_dequeue;
	u32			busy_dequeue;
	u32			good_dequeue;
	u32			requeue;
	u32			tearकरोwn_dequeue;
पूर्ण;

काष्ठा cpdma_ctlr;
काष्ठा cpdma_chan;

प्रकार व्योम (*cpdma_handler_fn)(व्योम *token, पूर्णांक len, पूर्णांक status);

काष्ठा cpdma_ctlr *cpdma_ctlr_create(काष्ठा cpdma_params *params);
पूर्णांक cpdma_ctlr_destroy(काष्ठा cpdma_ctlr *ctlr);
पूर्णांक cpdma_ctlr_start(काष्ठा cpdma_ctlr *ctlr);
पूर्णांक cpdma_ctlr_stop(काष्ठा cpdma_ctlr *ctlr);

काष्ठा cpdma_chan *cpdma_chan_create(काष्ठा cpdma_ctlr *ctlr, पूर्णांक chan_num,
				     cpdma_handler_fn handler, पूर्णांक rx_type);
पूर्णांक cpdma_chan_get_rx_buf_num(काष्ठा cpdma_chan *chan);
पूर्णांक cpdma_chan_destroy(काष्ठा cpdma_chan *chan);
पूर्णांक cpdma_chan_start(काष्ठा cpdma_chan *chan);
पूर्णांक cpdma_chan_stop(काष्ठा cpdma_chan *chan);

पूर्णांक cpdma_chan_get_stats(काष्ठा cpdma_chan *chan,
			 काष्ठा cpdma_chan_stats *stats);
पूर्णांक cpdma_chan_submit_mapped(काष्ठा cpdma_chan *chan, व्योम *token,
			     dma_addr_t data, पूर्णांक len, पूर्णांक directed);
पूर्णांक cpdma_chan_submit(काष्ठा cpdma_chan *chan, व्योम *token, व्योम *data,
		      पूर्णांक len, पूर्णांक directed);
पूर्णांक cpdma_chan_idle_submit_mapped(काष्ठा cpdma_chan *chan, व्योम *token,
				  dma_addr_t data, पूर्णांक len, पूर्णांक directed);
पूर्णांक cpdma_chan_idle_submit(काष्ठा cpdma_chan *chan, व्योम *token, व्योम *data,
			   पूर्णांक len, पूर्णांक directed);
पूर्णांक cpdma_chan_process(काष्ठा cpdma_chan *chan, पूर्णांक quota);

पूर्णांक cpdma_ctlr_पूर्णांक_ctrl(काष्ठा cpdma_ctlr *ctlr, bool enable);
व्योम cpdma_ctlr_eoi(काष्ठा cpdma_ctlr *ctlr, u32 value);
पूर्णांक cpdma_chan_पूर्णांक_ctrl(काष्ठा cpdma_chan *chan, bool enable);
u32 cpdma_ctrl_rxchs_state(काष्ठा cpdma_ctlr *ctlr);
u32 cpdma_ctrl_txchs_state(काष्ठा cpdma_ctlr *ctlr);
bool cpdma_check_मुक्त_tx_desc(काष्ठा cpdma_chan *chan);
पूर्णांक cpdma_chan_set_weight(काष्ठा cpdma_chan *ch, पूर्णांक weight);
पूर्णांक cpdma_chan_set_rate(काष्ठा cpdma_chan *ch, u32 rate);
u32 cpdma_chan_get_rate(काष्ठा cpdma_chan *ch);
u32 cpdma_chan_get_min_rate(काष्ठा cpdma_ctlr *ctlr);

क्रमागत cpdma_control अणु
	CPDMA_TX_RLIM,			/* पढ़ो-ग_लिखो */
	CPDMA_CMD_IDLE,			/* ग_लिखो-only */
	CPDMA_COPY_ERROR_FRAMES,	/* पढ़ो-ग_लिखो */
	CPDMA_RX_OFF_LEN_UPDATE,	/* पढ़ो-ग_लिखो */
	CPDMA_RX_OWNERSHIP_FLIP,	/* पढ़ो-ग_लिखो */
	CPDMA_TX_PRIO_FIXED,		/* पढ़ो-ग_लिखो */
	CPDMA_STAT_IDLE,		/* पढ़ो-only */
	CPDMA_STAT_TX_ERR_CHAN,		/* पढ़ो-only */
	CPDMA_STAT_TX_ERR_CODE,		/* पढ़ो-only */
	CPDMA_STAT_RX_ERR_CHAN,		/* पढ़ो-only */
	CPDMA_STAT_RX_ERR_CODE,		/* पढ़ो-only */
	CPDMA_RX_BUFFER_OFFSET,		/* पढ़ो-ग_लिखो */
पूर्ण;

पूर्णांक cpdma_control_get(काष्ठा cpdma_ctlr *ctlr, पूर्णांक control);
पूर्णांक cpdma_control_set(काष्ठा cpdma_ctlr *ctlr, पूर्णांक control, पूर्णांक value);
पूर्णांक cpdma_get_num_rx_descs(काष्ठा cpdma_ctlr *ctlr);
पूर्णांक cpdma_set_num_rx_descs(काष्ठा cpdma_ctlr *ctlr, पूर्णांक num_rx_desc);
पूर्णांक cpdma_get_num_tx_descs(काष्ठा cpdma_ctlr *ctlr);

#पूर्ण_अगर
