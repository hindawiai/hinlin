<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 */

#अगर_अघोषित EFX_NIC_COMMON_H
#घोषणा EFX_NIC_COMMON_H

#समावेश "net_driver.h"
#समावेश "efx_common.h"
#समावेश "mcdi.h"
#समावेश "ptp.h"

क्रमागत अणु
	/* Revisions 0-2 were Falcon A0, A1 and B0 respectively.
	 * They are not supported by this driver but these revision numbers
	 * क्रमm part of the ethtool API क्रम रेजिस्टर dumping.
	 */
	EFX_REV_SIENA_A0 = 3,
	EFX_REV_HUNT_A0 = 4,
	EFX_REV_EF100 = 5,
पूर्ण;

अटल अंतरभूत पूर्णांक efx_nic_rev(काष्ठा efx_nic *efx)
अणु
	वापस efx->type->revision;
पूर्ण

/* Read the current event from the event queue */
अटल अंतरभूत efx_qword_t *efx_event(काष्ठा efx_channel *channel,
				     अचिन्हित पूर्णांक index)
अणु
	वापस ((efx_qword_t *) (channel->eventq.buf.addr)) +
		(index & channel->eventq_mask);
पूर्ण

/* See अगर an event is present
 *
 * We check both the high and low dword of the event क्रम all ones.  We
 * wrote all ones when we cleared the event, and no valid event can
 * have all ones in either its high or low dwords.  This approach is
 * robust against reordering.
 *
 * Note that using a single 64-bit comparison is incorrect; even
 * though the CPU पढ़ो will be atomic, the DMA ग_लिखो may not be.
 */
अटल अंतरभूत पूर्णांक efx_event_present(efx_qword_t *event)
अणु
	वापस !(EFX_DWORD_IS_ALL_ONES(event->dword[0]) |
		  EFX_DWORD_IS_ALL_ONES(event->dword[1]));
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied transmit descriptor in the TX
 * descriptor queue beदीर्घing to the specअगरied channel.
 */
अटल अंतरभूत efx_qword_t *
efx_tx_desc(काष्ठा efx_tx_queue *tx_queue, अचिन्हित पूर्णांक index)
अणु
	वापस ((efx_qword_t *) (tx_queue->txd.buf.addr)) + index;
पूर्ण

/* Report whether this TX queue would be empty क्रम the given ग_लिखो_count.
 * May वापस false negative.
 */
अटल अंतरभूत bool efx_nic_tx_is_empty(काष्ठा efx_tx_queue *tx_queue, अचिन्हित पूर्णांक ग_लिखो_count)
अणु
	अचिन्हित पूर्णांक empty_पढ़ो_count = READ_ONCE(tx_queue->empty_पढ़ो_count);

	अगर (empty_पढ़ो_count == 0)
		वापस false;

	वापस ((empty_पढ़ो_count ^ ग_लिखो_count) & ~EFX_EMPTY_COUNT_VALID) == 0;
पूर्ण

पूर्णांक efx_enqueue_skb_tso(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb,
			bool *data_mapped);

/* Decide whether to push a TX descriptor to the NIC vs merely writing
 * the करोorbell.  This can reduce latency when we are adding a single
 * descriptor to an empty queue, but is otherwise poपूर्णांकless.  Further,
 * Falcon and Siena have hardware bugs (SF bug 33851) that may be
 * triggered अगर we करोn't check this.
 * We use the ग_लिखो_count used क्रम the last करोorbell push, to get the
 * NIC's view of the tx queue.
 */
अटल अंतरभूत bool efx_nic_may_push_tx_desc(काष्ठा efx_tx_queue *tx_queue,
					    अचिन्हित पूर्णांक ग_लिखो_count)
अणु
	bool was_empty = efx_nic_tx_is_empty(tx_queue, ग_लिखो_count);

	tx_queue->empty_पढ़ो_count = 0;
	वापस was_empty && tx_queue->ग_लिखो_count - ग_लिखो_count == 1;
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied descriptor in the RX descriptor queue */
अटल अंतरभूत efx_qword_t *
efx_rx_desc(काष्ठा efx_rx_queue *rx_queue, अचिन्हित पूर्णांक index)
अणु
	वापस ((efx_qword_t *) (rx_queue->rxd.buf.addr)) + index;
पूर्ण

/* Alignment of PCIe DMA boundaries (4KB) */
#घोषणा EFX_PAGE_SIZE	4096
/* Size and alignment of buffer table entries (same) */
#घोषणा EFX_BUF_SIZE	EFX_PAGE_SIZE

/* NIC-generic software stats */
क्रमागत अणु
	GENERIC_STAT_rx_noskb_drops,
	GENERIC_STAT_rx_nodesc_trunc,
	GENERIC_STAT_COUNT
पूर्ण;

#घोषणा EFX_GENERIC_SW_STAT(ext_name)				\
	[GENERIC_STAT_ ## ext_name] = अणु #ext_name, 0, 0 पूर्ण

/* TX data path */
अटल अंतरभूत पूर्णांक efx_nic_probe_tx(काष्ठा efx_tx_queue *tx_queue)
अणु
	वापस tx_queue->efx->type->tx_probe(tx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_init_tx(काष्ठा efx_tx_queue *tx_queue)
अणु
	tx_queue->efx->type->tx_init(tx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_हटाओ_tx(काष्ठा efx_tx_queue *tx_queue)
अणु
	अगर (tx_queue->efx->type->tx_हटाओ)
		tx_queue->efx->type->tx_हटाओ(tx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_push_buffers(काष्ठा efx_tx_queue *tx_queue)
अणु
	tx_queue->efx->type->tx_ग_लिखो(tx_queue);
पूर्ण

/* RX data path */
अटल अंतरभूत पूर्णांक efx_nic_probe_rx(काष्ठा efx_rx_queue *rx_queue)
अणु
	वापस rx_queue->efx->type->rx_probe(rx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_init_rx(काष्ठा efx_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_init(rx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_हटाओ_rx(काष्ठा efx_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_हटाओ(rx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_notअगरy_rx_desc(काष्ठा efx_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_ग_लिखो(rx_queue);
पूर्ण
अटल अंतरभूत व्योम efx_nic_generate_fill_event(काष्ठा efx_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_defer_refill(rx_queue);
पूर्ण

/* Event data path */
अटल अंतरभूत पूर्णांक efx_nic_probe_eventq(काष्ठा efx_channel *channel)
अणु
	वापस channel->efx->type->ev_probe(channel);
पूर्ण
अटल अंतरभूत पूर्णांक efx_nic_init_eventq(काष्ठा efx_channel *channel)
अणु
	वापस channel->efx->type->ev_init(channel);
पूर्ण
अटल अंतरभूत व्योम efx_nic_fini_eventq(काष्ठा efx_channel *channel)
अणु
	channel->efx->type->ev_fini(channel);
पूर्ण
अटल अंतरभूत व्योम efx_nic_हटाओ_eventq(काष्ठा efx_channel *channel)
अणु
	channel->efx->type->ev_हटाओ(channel);
पूर्ण
अटल अंतरभूत पूर्णांक
efx_nic_process_eventq(काष्ठा efx_channel *channel, पूर्णांक quota)
अणु
	वापस channel->efx->type->ev_process(channel, quota);
पूर्ण
अटल अंतरभूत व्योम efx_nic_eventq_पढ़ो_ack(काष्ठा efx_channel *channel)
अणु
	channel->efx->type->ev_पढ़ो_ack(channel);
पूर्ण

व्योम efx_nic_event_test_start(काष्ठा efx_channel *channel);

bool efx_nic_event_present(काष्ठा efx_channel *channel);

अटल अंतरभूत व्योम efx_sensor_event(काष्ठा efx_nic *efx, efx_qword_t *ev)
अणु
	अगर (efx->type->sensor_event)
		efx->type->sensor_event(efx, ev);
पूर्ण

/* Some statistics are computed as A - B where A and B each increase
 * linearly with some hardware counter(s) and the counters are पढ़ो
 * asynchronously.  If the counters contributing to B are always पढ़ो
 * after those contributing to A, the computed value may be lower than
 * the true value by some variable amount, and may decrease between
 * subsequent computations.
 *
 * We should never allow statistics to decrease or to exceed the true
 * value.  Since the computed value will never be greater than the
 * true value, we can achieve this by only storing the computed value
 * when it increases.
 */
अटल अंतरभूत व्योम efx_update_dअगरf_stat(u64 *stat, u64 dअगरf)
अणु
	अगर ((s64)(dअगरf - *stat) > 0)
		*stat = dअगरf;
पूर्ण

/* Interrupts */
पूर्णांक efx_nic_init_पूर्णांकerrupt(काष्ठा efx_nic *efx);
पूर्णांक efx_nic_irq_test_start(काष्ठा efx_nic *efx);
व्योम efx_nic_fini_पूर्णांकerrupt(काष्ठा efx_nic *efx);

अटल अंतरभूत पूर्णांक efx_nic_event_test_irq_cpu(काष्ठा efx_channel *channel)
अणु
	वापस READ_ONCE(channel->event_test_cpu);
पूर्ण
अटल अंतरभूत पूर्णांक efx_nic_irq_test_irq_cpu(काष्ठा efx_nic *efx)
अणु
	वापस READ_ONCE(efx->last_irq_cpu);
पूर्ण

/* Global Resources */
पूर्णांक efx_nic_alloc_buffer(काष्ठा efx_nic *efx, काष्ठा efx_buffer *buffer,
			 अचिन्हित पूर्णांक len, gfp_t gfp_flags);
व्योम efx_nic_मुक्त_buffer(काष्ठा efx_nic *efx, काष्ठा efx_buffer *buffer);

माप_प्रकार efx_nic_get_regs_len(काष्ठा efx_nic *efx);
व्योम efx_nic_get_regs(काष्ठा efx_nic *efx, व्योम *buf);

#घोषणा EFX_MC_STATS_GENERATION_INVALID ((__क्रमce __le64)(-1))

माप_प्रकार efx_nic_describe_stats(स्थिर काष्ठा efx_hw_stat_desc *desc, माप_प्रकार count,
			      स्थिर अचिन्हित दीर्घ *mask, u8 *names);
पूर्णांक efx_nic_copy_stats(काष्ठा efx_nic *efx, __le64 *dest);
व्योम efx_nic_update_stats(स्थिर काष्ठा efx_hw_stat_desc *desc, माप_प्रकार count,
			  स्थिर अचिन्हित दीर्घ *mask, u64 *stats,
			  स्थिर व्योम *dma_buf, bool accumulate);
व्योम efx_nic_fix_nodesc_drop_stat(काष्ठा efx_nic *efx, u64 *stat);
अटल अंतरभूत माप_प्रकार efx_nic_update_stats_atomic(काष्ठा efx_nic *efx, u64 *full_stats,
						 काष्ठा rtnl_link_stats64 *core_stats)
अणु
	अगर (efx->type->update_stats_atomic)
		वापस efx->type->update_stats_atomic(efx, full_stats, core_stats);
	वापस efx->type->update_stats(efx, full_stats, core_stats);
पूर्ण

#घोषणा EFX_MAX_FLUSH_TIME 5000

#पूर्ण_अगर /* EFX_NIC_COMMON_H */
