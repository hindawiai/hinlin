<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _SPRD_DMA_H_
#घोषणा _SPRD_DMA_H_

#घोषणा SPRD_DMA_REQ_SHIFT	8
#घोषणा SPRD_DMA_TRG_MODE_SHIFT	16
#घोषणा SPRD_DMA_CHN_MODE_SHIFT	24
#घोषणा SPRD_DMA_FLAGS(chn_mode, trg_mode, req_mode, पूर्णांक_type) \
	((chn_mode) << SPRD_DMA_CHN_MODE_SHIFT | \
	(trg_mode) << SPRD_DMA_TRG_MODE_SHIFT | \
	(req_mode) << SPRD_DMA_REQ_SHIFT | (पूर्णांक_type))

/*
 * The Spपढ़ोtrum DMA controller supports channel 2-stage tansfer, that means
 * we can request 2 dma channels, one क्रम source channel, and another one क्रम
 * destination channel. Each channel is independent, and has its own
 * configurations. Once the source channel's transaction is करोne, it will
 * trigger the destination channel's transaction स्वतःmatically by hardware
 * संकेत.
 *
 * To support 2-stage tansfer, we must configure the channel mode and trigger
 * mode as below definition.
 */

/*
 * क्रमागत sprd_dma_chn_mode: define the DMA channel mode क्रम 2-stage transfer
 * @SPRD_DMA_CHN_MODE_NONE: No channel mode setting which means channel करोesn't
 * support the 2-stage transfer.
 * @SPRD_DMA_SRC_CHN0: Channel used as source channel 0.
 * @SPRD_DMA_SRC_CHN1: Channel used as source channel 1.
 * @SPRD_DMA_DST_CHN0: Channel used as destination channel 0.
 * @SPRD_DMA_DST_CHN1: Channel used as destination channel 1.
 *
 * Now the DMA controller can supports 2 groups 2-stage transfer.
 */
क्रमागत sprd_dma_chn_mode अणु
	SPRD_DMA_CHN_MODE_NONE,
	SPRD_DMA_SRC_CHN0,
	SPRD_DMA_SRC_CHN1,
	SPRD_DMA_DST_CHN0,
	SPRD_DMA_DST_CHN1,
पूर्ण;

/*
 * क्रमागत sprd_dma_trg_mode: define the DMA channel trigger mode क्रम 2-stage
 * transfer
 * @SPRD_DMA_NO_TRG: No trigger setting.
 * @SPRD_DMA_FRAG_DONE_TRG: Trigger the transaction of destination channel
 * स्वतःmatically once the source channel's fragment request is करोne.
 * @SPRD_DMA_BLOCK_DONE_TRG: Trigger the transaction of destination channel
 * स्वतःmatically once the source channel's block request is करोne.
 * @SPRD_DMA_TRANS_DONE_TRG: Trigger the transaction of destination channel
 * स्वतःmatically once the source channel's transfer request is करोne.
 * @SPRD_DMA_LIST_DONE_TRG: Trigger the transaction of destination channel
 * स्वतःmatically once the source channel's link-list request is करोne.
 */
क्रमागत sprd_dma_trg_mode अणु
	SPRD_DMA_NO_TRG,
	SPRD_DMA_FRAG_DONE_TRG,
	SPRD_DMA_BLOCK_DONE_TRG,
	SPRD_DMA_TRANS_DONE_TRG,
	SPRD_DMA_LIST_DONE_TRG,
पूर्ण;

/*
 * क्रमागत sprd_dma_req_mode: define the DMA request mode
 * @SPRD_DMA_FRAG_REQ: fragment request mode
 * @SPRD_DMA_BLK_REQ: block request mode
 * @SPRD_DMA_TRANS_REQ: transaction request mode
 * @SPRD_DMA_LIST_REQ: link-list request mode
 *
 * We have 4 types request mode: fragment mode, block mode, transaction mode
 * and linklist mode. One transaction can contain several blocks, one block can
 * contain several fragments. Link-list mode means we can save several DMA
 * configuration पूर्णांकo one reserved memory, then DMA can fetch each DMA
 * configuration स्वतःmatically to start transfer.
 */
क्रमागत sprd_dma_req_mode अणु
	SPRD_DMA_FRAG_REQ,
	SPRD_DMA_BLK_REQ,
	SPRD_DMA_TRANS_REQ,
	SPRD_DMA_LIST_REQ,
पूर्ण;

/*
 * क्रमागत sprd_dma_पूर्णांक_type: define the DMA पूर्णांकerrupt type
 * @SPRD_DMA_NO_INT: करो not need generate DMA पूर्णांकerrupts.
 * @SPRD_DMA_FRAG_INT: fragment करोne पूर्णांकerrupt when one fragment request
 * is करोne.
 * @SPRD_DMA_BLK_INT: block करोne पूर्णांकerrupt when one block request is करोne.
 * @SPRD_DMA_BLK_FRAG_INT: block and fragment पूर्णांकerrupt when one fragment
 * or one block request is करोne.
 * @SPRD_DMA_TRANS_INT: tansaction करोne पूर्णांकerrupt when one transaction
 * request is करोne.
 * @SPRD_DMA_TRANS_FRAG_INT: transaction and fragment पूर्णांकerrupt when one
 * transaction request or fragment request is करोne.
 * @SPRD_DMA_TRANS_BLK_INT: transaction and block पूर्णांकerrupt when one
 * transaction request or block request is करोne.
 * @SPRD_DMA_LIST_INT: link-list करोne पूर्णांकerrupt when one link-list request
 * is करोne.
 * @SPRD_DMA_CFGERR_INT: configure error पूर्णांकerrupt when configuration is
 * incorrect.
 */
क्रमागत sprd_dma_पूर्णांक_type अणु
	SPRD_DMA_NO_INT,
	SPRD_DMA_FRAG_INT,
	SPRD_DMA_BLK_INT,
	SPRD_DMA_BLK_FRAG_INT,
	SPRD_DMA_TRANS_INT,
	SPRD_DMA_TRANS_FRAG_INT,
	SPRD_DMA_TRANS_BLK_INT,
	SPRD_DMA_LIST_INT,
	SPRD_DMA_CFGERR_INT,
पूर्ण;

/*
 * काष्ठा sprd_dma_linklist - DMA link-list address काष्ठाure
 * @virt_addr: link-list भव address to configure link-list node
 * @phy_addr: link-list physical address to link DMA transfer
 * @wrap_addr: the wrap address क्रम link-list mode, which means once the
 * transfer address reaches the wrap address, the next transfer address
 * will jump to the address specअगरied by wrap_to रेजिस्टर.
 *
 * The Spपढ़ोtrum DMA controller supports the link-list mode, that means slaves
 * can supply several groups configurations (each configuration represents one
 * DMA transfer) saved in memory, and DMA controller will link these groups
 * configurations by writing the physical address of each configuration पूर्णांकo the
 * link-list रेजिस्टर.
 *
 * Just as shown below, the link-list poपूर्णांकer रेजिस्टर will be poपूर्णांकed to the
 * physical address of 'configuration 1', and the 'configuration 1' link-list
 * poपूर्णांकer will be poपूर्णांकed to 'configuration 2', and so on.
 * Once trigger the DMA transfer, the DMA controller will load 'configuration
 * 1' to its registers automatically, after 'configuration 1' transaction is
 * करोne, DMA controller will load 'configuration 2' स्वतःmatically, until all
 * DMA transactions are करोne.
 *
 * Note: The last link-list poपूर्णांकer should poपूर्णांक to the physical address
 * of 'configuration 1', which can aव्योम DMA controller loads incorrect
 * configuration when the last configuration transaction is करोne.
 *
 *     DMA controller                    linklist memory
 * ======================             -----------------------
 *|                      |           |    configuration 1    |<---
 *|   DMA controller     |   ------->|                       |   |
 *|                      |   |       |                       |   |
 *|                      |   |       |                       |   |
 *|                      |   |       |                       |   |
 *| linklist poपूर्णांकer reg |----   ----|    linklist poपूर्णांकer   |   |
 * ======================        |    -----------------------    |
 *                               |                               |
 *                               |    -----------------------    |
 *                               |   |    configuration 2    |   |
 *                               --->|                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                               ----|    linklist poपूर्णांकer   |   |
 *                               |    -----------------------    |
 *                               |                               |
 *                               |    -----------------------    |
 *                               |   |    configuration 3    |   |
 *                               --->|                       |   |
 *                                   |                       |   |
 *                                   |           .           |   |
 *                                               .               |
 *                                               .               |
 *                                               .               |
 *                               |               .               |
 *                               |    -----------------------    |
 *                               |   |    configuration n    |   |
 *                               --->|                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                                   |    linklist poपूर्णांकer   |----
 *                                    -----------------------
 *
 * To support the link-list mode, DMA slaves should allocate one segment memory
 * from always-on IRAM or dma coherent memory to store these groups of DMA
 * configuration, and pass the भव and physical address to DMA controller.
 */
काष्ठा sprd_dma_linklist अणु
	अचिन्हित दीर्घ virt_addr;
	phys_addr_t phy_addr;
	phys_addr_t wrap_addr;
पूर्ण;

#पूर्ण_अगर
