<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_NIC_H
#घोषणा EF4_NIC_H

#समावेश <linux/net_tstamp.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश "net_driver.h"
#समावेश "efx.h"

क्रमागत अणु
	EF4_REV_FALCON_A0 = 0,
	EF4_REV_FALCON_A1 = 1,
	EF4_REV_FALCON_B0 = 2,
पूर्ण;

अटल अंतरभूत पूर्णांक ef4_nic_rev(काष्ठा ef4_nic *efx)
अणु
	वापस efx->type->revision;
पूर्ण

u32 ef4_farch_fpga_ver(काष्ठा ef4_nic *efx);

/* NIC has two पूर्णांकerlinked PCI functions क्रम the same port. */
अटल अंतरभूत bool ef4_nic_is_dual_func(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_nic_rev(efx) < EF4_REV_FALCON_B0;
पूर्ण

/* Read the current event from the event queue */
अटल अंतरभूत ef4_qword_t *ef4_event(काष्ठा ef4_channel *channel,
				     अचिन्हित पूर्णांक index)
अणु
	वापस ((ef4_qword_t *) (channel->eventq.buf.addr)) +
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
अटल अंतरभूत पूर्णांक ef4_event_present(ef4_qword_t *event)
अणु
	वापस !(EF4_DWORD_IS_ALL_ONES(event->dword[0]) |
		  EF4_DWORD_IS_ALL_ONES(event->dword[1]));
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied transmit descriptor in the TX
 * descriptor queue beदीर्घing to the specअगरied channel.
 */
अटल अंतरभूत ef4_qword_t *
ef4_tx_desc(काष्ठा ef4_tx_queue *tx_queue, अचिन्हित पूर्णांक index)
अणु
	वापस ((ef4_qword_t *) (tx_queue->txd.buf.addr)) + index;
पूर्ण

/* Get partner of a TX queue, seen as part of the same net core queue */
अटल अंतरभूत काष्ठा ef4_tx_queue *ef4_tx_queue_partner(काष्ठा ef4_tx_queue *tx_queue)
अणु
	अगर (tx_queue->queue & EF4_TXQ_TYPE_OFFLOAD)
		वापस tx_queue - EF4_TXQ_TYPE_OFFLOAD;
	अन्यथा
		वापस tx_queue + EF4_TXQ_TYPE_OFFLOAD;
पूर्ण

/* Report whether this TX queue would be empty क्रम the given ग_लिखो_count.
 * May वापस false negative.
 */
अटल अंतरभूत bool __ef4_nic_tx_is_empty(काष्ठा ef4_tx_queue *tx_queue,
					 अचिन्हित पूर्णांक ग_लिखो_count)
अणु
	अचिन्हित पूर्णांक empty_पढ़ो_count = READ_ONCE(tx_queue->empty_पढ़ो_count);

	अगर (empty_पढ़ो_count == 0)
		वापस false;

	वापस ((empty_पढ़ो_count ^ ग_लिखो_count) & ~EF4_EMPTY_COUNT_VALID) == 0;
पूर्ण

/* Decide whether to push a TX descriptor to the NIC vs merely writing
 * the करोorbell.  This can reduce latency when we are adding a single
 * descriptor to an empty queue, but is otherwise poपूर्णांकless.  Further,
 * Falcon and Siena have hardware bugs (SF bug 33851) that may be
 * triggered अगर we करोn't check this.
 * We use the ग_लिखो_count used क्रम the last करोorbell push, to get the
 * NIC's view of the tx queue.
 */
अटल अंतरभूत bool ef4_nic_may_push_tx_desc(काष्ठा ef4_tx_queue *tx_queue,
					    अचिन्हित पूर्णांक ग_लिखो_count)
अणु
	bool was_empty = __ef4_nic_tx_is_empty(tx_queue, ग_लिखो_count);

	tx_queue->empty_पढ़ो_count = 0;
	वापस was_empty && tx_queue->ग_लिखो_count - ग_लिखो_count == 1;
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied descriptor in the RX descriptor queue */
अटल अंतरभूत ef4_qword_t *
ef4_rx_desc(काष्ठा ef4_rx_queue *rx_queue, अचिन्हित पूर्णांक index)
अणु
	वापस ((ef4_qword_t *) (rx_queue->rxd.buf.addr)) + index;
पूर्ण

क्रमागत अणु
	PHY_TYPE_NONE = 0,
	PHY_TYPE_TXC43128 = 1,
	PHY_TYPE_88E1111 = 2,
	PHY_TYPE_SFX7101 = 3,
	PHY_TYPE_QT2022C2 = 4,
	PHY_TYPE_PM8358 = 6,
	PHY_TYPE_SFT9001A = 8,
	PHY_TYPE_QT2025C = 9,
	PHY_TYPE_SFT9001B = 10,
पूर्ण;

#घोषणा FALCON_XMAC_LOOPBACKS			\
	((1 << LOOPBACK_XGMII) |		\
	 (1 << LOOPBACK_XGXS) |			\
	 (1 << LOOPBACK_XAUI))

/* Alignment of PCIe DMA boundaries (4KB) */
#घोषणा EF4_PAGE_SIZE	4096
/* Size and alignment of buffer table entries (same) */
#घोषणा EF4_BUF_SIZE	EF4_PAGE_SIZE

/* NIC-generic software stats */
क्रमागत अणु
	GENERIC_STAT_rx_noskb_drops,
	GENERIC_STAT_rx_nodesc_trunc,
	GENERIC_STAT_COUNT
पूर्ण;

/**
 * काष्ठा falcon_board_type - board operations and type inक्रमmation
 * @id: Board type id, as found in NVRAM
 * @init: Allocate resources and initialise peripheral hardware
 * @init_phy: Do board-specअगरic PHY initialisation
 * @fini: Shut करोwn hardware and मुक्त resources
 * @set_id_led: Set state of identअगरying LED or revert to स्वतःmatic function
 * @monitor: Board-specअगरic health check function
 */
काष्ठा falcon_board_type अणु
	u8 id;
	पूर्णांक (*init) (काष्ठा ef4_nic *nic);
	व्योम (*init_phy) (काष्ठा ef4_nic *efx);
	व्योम (*fini) (काष्ठा ef4_nic *nic);
	व्योम (*set_id_led) (काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode);
	पूर्णांक (*monitor) (काष्ठा ef4_nic *nic);
पूर्ण;

/**
 * काष्ठा falcon_board - board inक्रमmation
 * @type: Type of board
 * @major: Major rev. ('A', 'B' ...)
 * @minor: Minor rev. (0, 1, ...)
 * @i2c_adap: I2C adapter क्रम on-board peripherals
 * @i2c_data: Data क्रम bit-banging algorithm
 * @hwmon_client: I2C client क्रम hardware monitor
 * @ioexp_client: I2C client क्रम घातer/port control
 */
काष्ठा falcon_board अणु
	स्थिर काष्ठा falcon_board_type *type;
	पूर्णांक major;
	पूर्णांक minor;
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_algo_bit_data i2c_data;
	काष्ठा i2c_client *hwmon_client, *ioexp_client;
पूर्ण;

/**
 * काष्ठा falcon_spi_device - a Falcon SPI (Serial Peripheral Interface) device
 * @device_id:		Controller's id क्रम the device
 * @size:		Size (in bytes)
 * @addr_len:		Number of address bytes in पढ़ो/ग_लिखो commands
 * @munge_address:	Flag whether addresses should be munged.
 *	Some devices with 9-bit addresses (e.g. AT25040A EEPROM)
 *	use bit 3 of the command byte as address bit A8, rather
 *	than having a two-byte address.  If this flag is set, then
 *	commands should be munged in this way.
 * @erase_command:	Erase command (or 0 अगर sector erase not needed).
 * @erase_size:		Erase sector size (in bytes)
 *	Erase commands affect sectors with this size and alignment.
 *	This must be a घातer of two.
 * @block_size:		Write block size (in bytes).
 *	Write commands are limited to blocks with this size and alignment.
 */
काष्ठा falcon_spi_device अणु
	पूर्णांक device_id;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक addr_len;
	अचिन्हित पूर्णांक munge_address:1;
	u8 erase_command;
	अचिन्हित पूर्णांक erase_size;
	अचिन्हित पूर्णांक block_size;
पूर्ण;

अटल अंतरभूत bool falcon_spi_present(स्थिर काष्ठा falcon_spi_device *spi)
अणु
	वापस spi->size != 0;
पूर्ण

क्रमागत अणु
	FALCON_STAT_tx_bytes = GENERIC_STAT_COUNT,
	FALCON_STAT_tx_packets,
	FALCON_STAT_tx_छोड़ो,
	FALCON_STAT_tx_control,
	FALCON_STAT_tx_unicast,
	FALCON_STAT_tx_multicast,
	FALCON_STAT_tx_broadcast,
	FALCON_STAT_tx_lt64,
	FALCON_STAT_tx_64,
	FALCON_STAT_tx_65_to_127,
	FALCON_STAT_tx_128_to_255,
	FALCON_STAT_tx_256_to_511,
	FALCON_STAT_tx_512_to_1023,
	FALCON_STAT_tx_1024_to_15xx,
	FALCON_STAT_tx_15xx_to_jumbo,
	FALCON_STAT_tx_gtjumbo,
	FALCON_STAT_tx_non_tcpudp,
	FALCON_STAT_tx_mac_src_error,
	FALCON_STAT_tx_ip_src_error,
	FALCON_STAT_rx_bytes,
	FALCON_STAT_rx_good_bytes,
	FALCON_STAT_rx_bad_bytes,
	FALCON_STAT_rx_packets,
	FALCON_STAT_rx_good,
	FALCON_STAT_rx_bad,
	FALCON_STAT_rx_छोड़ो,
	FALCON_STAT_rx_control,
	FALCON_STAT_rx_unicast,
	FALCON_STAT_rx_multicast,
	FALCON_STAT_rx_broadcast,
	FALCON_STAT_rx_lt64,
	FALCON_STAT_rx_64,
	FALCON_STAT_rx_65_to_127,
	FALCON_STAT_rx_128_to_255,
	FALCON_STAT_rx_256_to_511,
	FALCON_STAT_rx_512_to_1023,
	FALCON_STAT_rx_1024_to_15xx,
	FALCON_STAT_rx_15xx_to_jumbo,
	FALCON_STAT_rx_gtjumbo,
	FALCON_STAT_rx_bad_lt64,
	FALCON_STAT_rx_bad_gtjumbo,
	FALCON_STAT_rx_overflow,
	FALCON_STAT_rx_symbol_error,
	FALCON_STAT_rx_align_error,
	FALCON_STAT_rx_length_error,
	FALCON_STAT_rx_पूर्णांकernal_error,
	FALCON_STAT_rx_nodesc_drop_cnt,
	FALCON_STAT_COUNT
पूर्ण;

/**
 * काष्ठा falcon_nic_data - Falcon NIC state
 * @pci_dev2: Secondary function of Falcon A
 * @efx: ef4_nic poपूर्णांकer
 * @board: Board state and functions
 * @stats: Hardware statistics
 * @stats_disable_count: Nest count क्रम disabling statistics fetches
 * @stats_pending: Is there a pending DMA of MAC statistics.
 * @stats_समयr: A समयr क्रम regularly fetching MAC statistics.
 * @spi_flash: SPI flash device
 * @spi_eeprom: SPI EEPROM device
 * @spi_lock: SPI bus lock
 * @mdio_lock: MDIO bus lock
 * @xmac_poll_required: XMAC link state needs polling
 */
काष्ठा falcon_nic_data अणु
	काष्ठा pci_dev *pci_dev2;
	काष्ठा ef4_nic *efx;
	काष्ठा falcon_board board;
	u64 stats[FALCON_STAT_COUNT];
	अचिन्हित पूर्णांक stats_disable_count;
	bool stats_pending;
	काष्ठा समयr_list stats_समयr;
	काष्ठा falcon_spi_device spi_flash;
	काष्ठा falcon_spi_device spi_eeprom;
	काष्ठा mutex spi_lock;
	काष्ठा mutex mdio_lock;
	bool xmac_poll_required;
पूर्ण;

अटल अंतरभूत काष्ठा falcon_board *falcon_board(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *data = efx->nic_data;
	वापस &data->board;
पूर्ण

काष्ठा ethtool_ts_info;

बाह्य स्थिर काष्ठा ef4_nic_type falcon_a1_nic_type;
बाह्य स्थिर काष्ठा ef4_nic_type falcon_b0_nic_type;

/**************************************************************************
 *
 * Externs
 *
 **************************************************************************
 */

पूर्णांक falcon_probe_board(काष्ठा ef4_nic *efx, u16 revision_info);

/* TX data path */
अटल अंतरभूत पूर्णांक ef4_nic_probe_tx(काष्ठा ef4_tx_queue *tx_queue)
अणु
	वापस tx_queue->efx->type->tx_probe(tx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_init_tx(काष्ठा ef4_tx_queue *tx_queue)
अणु
	tx_queue->efx->type->tx_init(tx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_हटाओ_tx(काष्ठा ef4_tx_queue *tx_queue)
अणु
	tx_queue->efx->type->tx_हटाओ(tx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_push_buffers(काष्ठा ef4_tx_queue *tx_queue)
अणु
	tx_queue->efx->type->tx_ग_लिखो(tx_queue);
पूर्ण

/* RX data path */
अटल अंतरभूत पूर्णांक ef4_nic_probe_rx(काष्ठा ef4_rx_queue *rx_queue)
अणु
	वापस rx_queue->efx->type->rx_probe(rx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_init_rx(काष्ठा ef4_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_init(rx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_हटाओ_rx(काष्ठा ef4_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_हटाओ(rx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_notअगरy_rx_desc(काष्ठा ef4_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_ग_लिखो(rx_queue);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_generate_fill_event(काष्ठा ef4_rx_queue *rx_queue)
अणु
	rx_queue->efx->type->rx_defer_refill(rx_queue);
पूर्ण

/* Event data path */
अटल अंतरभूत पूर्णांक ef4_nic_probe_eventq(काष्ठा ef4_channel *channel)
अणु
	वापस channel->efx->type->ev_probe(channel);
पूर्ण
अटल अंतरभूत पूर्णांक ef4_nic_init_eventq(काष्ठा ef4_channel *channel)
अणु
	वापस channel->efx->type->ev_init(channel);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_fini_eventq(काष्ठा ef4_channel *channel)
अणु
	channel->efx->type->ev_fini(channel);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_हटाओ_eventq(काष्ठा ef4_channel *channel)
अणु
	channel->efx->type->ev_हटाओ(channel);
पूर्ण
अटल अंतरभूत पूर्णांक
ef4_nic_process_eventq(काष्ठा ef4_channel *channel, पूर्णांक quota)
अणु
	वापस channel->efx->type->ev_process(channel, quota);
पूर्ण
अटल अंतरभूत व्योम ef4_nic_eventq_पढ़ो_ack(काष्ठा ef4_channel *channel)
अणु
	channel->efx->type->ev_पढ़ो_ack(channel);
पूर्ण
व्योम ef4_nic_event_test_start(काष्ठा ef4_channel *channel);

/* queue operations */
पूर्णांक ef4_farch_tx_probe(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_farch_tx_init(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_farch_tx_fini(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_farch_tx_हटाओ(काष्ठा ef4_tx_queue *tx_queue);
व्योम ef4_farch_tx_ग_लिखो(काष्ठा ef4_tx_queue *tx_queue);
अचिन्हित पूर्णांक ef4_farch_tx_limit_len(काष्ठा ef4_tx_queue *tx_queue,
				    dma_addr_t dma_addr, अचिन्हित पूर्णांक len);
पूर्णांक ef4_farch_rx_probe(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_farch_rx_init(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_farch_rx_fini(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_farch_rx_हटाओ(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_farch_rx_ग_लिखो(काष्ठा ef4_rx_queue *rx_queue);
व्योम ef4_farch_rx_defer_refill(काष्ठा ef4_rx_queue *rx_queue);
पूर्णांक ef4_farch_ev_probe(काष्ठा ef4_channel *channel);
पूर्णांक ef4_farch_ev_init(काष्ठा ef4_channel *channel);
व्योम ef4_farch_ev_fini(काष्ठा ef4_channel *channel);
व्योम ef4_farch_ev_हटाओ(काष्ठा ef4_channel *channel);
पूर्णांक ef4_farch_ev_process(काष्ठा ef4_channel *channel, पूर्णांक quota);
व्योम ef4_farch_ev_पढ़ो_ack(काष्ठा ef4_channel *channel);
व्योम ef4_farch_ev_test_generate(काष्ठा ef4_channel *channel);

/* filter operations */
पूर्णांक ef4_farch_filter_table_probe(काष्ठा ef4_nic *efx);
व्योम ef4_farch_filter_table_restore(काष्ठा ef4_nic *efx);
व्योम ef4_farch_filter_table_हटाओ(काष्ठा ef4_nic *efx);
व्योम ef4_farch_filter_update_rx_scatter(काष्ठा ef4_nic *efx);
s32 ef4_farch_filter_insert(काष्ठा ef4_nic *efx, काष्ठा ef4_filter_spec *spec,
			    bool replace);
पूर्णांक ef4_farch_filter_हटाओ_safe(काष्ठा ef4_nic *efx,
				 क्रमागत ef4_filter_priority priority,
				 u32 filter_id);
पूर्णांक ef4_farch_filter_get_safe(काष्ठा ef4_nic *efx,
			      क्रमागत ef4_filter_priority priority, u32 filter_id,
			      काष्ठा ef4_filter_spec *);
पूर्णांक ef4_farch_filter_clear_rx(काष्ठा ef4_nic *efx,
			      क्रमागत ef4_filter_priority priority);
u32 ef4_farch_filter_count_rx_used(काष्ठा ef4_nic *efx,
				   क्रमागत ef4_filter_priority priority);
u32 ef4_farch_filter_get_rx_id_limit(काष्ठा ef4_nic *efx);
s32 ef4_farch_filter_get_rx_ids(काष्ठा ef4_nic *efx,
				क्रमागत ef4_filter_priority priority, u32 *buf,
				u32 size);
#अगर_घोषित CONFIG_RFS_ACCEL
s32 ef4_farch_filter_rfs_insert(काष्ठा ef4_nic *efx,
				काष्ठा ef4_filter_spec *spec);
bool ef4_farch_filter_rfs_expire_one(काष्ठा ef4_nic *efx, u32 flow_id,
				     अचिन्हित पूर्णांक index);
#पूर्ण_अगर
व्योम ef4_farch_filter_sync_rx_mode(काष्ठा ef4_nic *efx);

bool ef4_nic_event_present(काष्ठा ef4_channel *channel);

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
अटल अंतरभूत व्योम ef4_update_dअगरf_stat(u64 *stat, u64 dअगरf)
अणु
	अगर ((s64)(dअगरf - *stat) > 0)
		*stat = dअगरf;
पूर्ण

/* Interrupts */
पूर्णांक ef4_nic_init_पूर्णांकerrupt(काष्ठा ef4_nic *efx);
पूर्णांक ef4_nic_irq_test_start(काष्ठा ef4_nic *efx);
व्योम ef4_nic_fini_पूर्णांकerrupt(काष्ठा ef4_nic *efx);
व्योम ef4_farch_irq_enable_master(काष्ठा ef4_nic *efx);
पूर्णांक ef4_farch_irq_test_generate(काष्ठा ef4_nic *efx);
व्योम ef4_farch_irq_disable_master(काष्ठा ef4_nic *efx);
irqवापस_t ef4_farch_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t ef4_farch_legacy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t ef4_farch_fatal_पूर्णांकerrupt(काष्ठा ef4_nic *efx);

अटल अंतरभूत पूर्णांक ef4_nic_event_test_irq_cpu(काष्ठा ef4_channel *channel)
अणु
	वापस READ_ONCE(channel->event_test_cpu);
पूर्ण
अटल अंतरभूत पूर्णांक ef4_nic_irq_test_irq_cpu(काष्ठा ef4_nic *efx)
अणु
	वापस READ_ONCE(efx->last_irq_cpu);
पूर्ण

/* Global Resources */
पूर्णांक ef4_nic_flush_queues(काष्ठा ef4_nic *efx);
पूर्णांक ef4_farch_fini_dmaq(काष्ठा ef4_nic *efx);
व्योम ef4_farch_finish_flr(काष्ठा ef4_nic *efx);
व्योम falcon_start_nic_stats(काष्ठा ef4_nic *efx);
व्योम falcon_stop_nic_stats(काष्ठा ef4_nic *efx);
पूर्णांक falcon_reset_xaui(काष्ठा ef4_nic *efx);
व्योम ef4_farch_dimension_resources(काष्ठा ef4_nic *efx, अचिन्हित sram_lim_qw);
व्योम ef4_farch_init_common(काष्ठा ef4_nic *efx);
व्योम ef4_farch_rx_push_indir_table(काष्ठा ef4_nic *efx);

पूर्णांक ef4_nic_alloc_buffer(काष्ठा ef4_nic *efx, काष्ठा ef4_buffer *buffer,
			 अचिन्हित पूर्णांक len, gfp_t gfp_flags);
व्योम ef4_nic_मुक्त_buffer(काष्ठा ef4_nic *efx, काष्ठा ef4_buffer *buffer);

/* Tests */
काष्ठा ef4_farch_रेजिस्टर_test अणु
	अचिन्हित address;
	ef4_oword_t mask;
पूर्ण;
पूर्णांक ef4_farch_test_रेजिस्टरs(काष्ठा ef4_nic *efx,
			     स्थिर काष्ठा ef4_farch_रेजिस्टर_test *regs,
			     माप_प्रकार n_regs);

माप_प्रकार ef4_nic_get_regs_len(काष्ठा ef4_nic *efx);
व्योम ef4_nic_get_regs(काष्ठा ef4_nic *efx, व्योम *buf);

माप_प्रकार ef4_nic_describe_stats(स्थिर काष्ठा ef4_hw_stat_desc *desc, माप_प्रकार count,
			      स्थिर अचिन्हित दीर्घ *mask, u8 *names);
व्योम ef4_nic_update_stats(स्थिर काष्ठा ef4_hw_stat_desc *desc, माप_प्रकार count,
			  स्थिर अचिन्हित दीर्घ *mask, u64 *stats,
			  स्थिर व्योम *dma_buf, bool accumulate);
व्योम ef4_nic_fix_nodesc_drop_stat(काष्ठा ef4_nic *efx, u64 *stat);

#घोषणा EF4_MAX_FLUSH_TIME 5000

व्योम ef4_farch_generate_event(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक evq,
			      ef4_qword_t *event);

#पूर्ण_अगर /* EF4_NIC_H */
