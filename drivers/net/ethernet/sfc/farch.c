<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/crc32.h>
#समावेश "net_driver.h"
#समावेश "bitfield.h"
#समावेश "efx.h"
#समावेश "rx_common.h"
#समावेश "nic.h"
#समावेश "farch_regs.h"
#समावेश "sriov.h"
#समावेश "siena_sriov.h"
#समावेश "io.h"
#समावेश "workarounds.h"

/* Falcon-architecture (SFC9000-family) support */

/**************************************************************************
 *
 * Configurable values
 *
 **************************************************************************
 */

/* This is set to 16 क्रम a good reason.  In summary, अगर larger than
 * 16, the descriptor cache holds more than a शेष socket
 * buffer's worth of packets (क्रम UDP we can only have at most one
 * socket buffer's worth outstanding).  This combined with the fact
 * that we only get 1 TX event per descriptor cache means the NIC
 * goes idle.
 */
#घोषणा TX_DC_ENTRIES 16
#घोषणा TX_DC_ENTRIES_ORDER 1

#घोषणा RX_DC_ENTRIES 64
#घोषणा RX_DC_ENTRIES_ORDER 3

/* If EFX_MAX_INT_ERRORS पूर्णांकernal errors occur within
 * EFX_INT_ERROR_EXPIRE seconds, we consider the NIC broken and
 * disable it.
 */
#घोषणा EFX_INT_ERROR_EXPIRE 3600
#घोषणा EFX_MAX_INT_ERRORS 5

/* Depth of RX flush request fअगरo */
#घोषणा EFX_RX_FLUSH_COUNT 4

/* Driver generated events */
#घोषणा _EFX_CHANNEL_MAGIC_TEST		0x000101
#घोषणा _EFX_CHANNEL_MAGIC_FILL		0x000102
#घोषणा _EFX_CHANNEL_MAGIC_RX_DRAIN	0x000103
#घोषणा _EFX_CHANNEL_MAGIC_TX_DRAIN	0x000104

#घोषणा _EFX_CHANNEL_MAGIC(_code, _data)	((_code) << 8 | (_data))
#घोषणा _EFX_CHANNEL_MAGIC_CODE(_magic)		((_magic) >> 8)

#घोषणा EFX_CHANNEL_MAGIC_TEST(_channel)				\
	_EFX_CHANNEL_MAGIC(_EFX_CHANNEL_MAGIC_TEST, (_channel)->channel)
#घोषणा EFX_CHANNEL_MAGIC_FILL(_rx_queue)				\
	_EFX_CHANNEL_MAGIC(_EFX_CHANNEL_MAGIC_FILL,			\
			   efx_rx_queue_index(_rx_queue))
#घोषणा EFX_CHANNEL_MAGIC_RX_DRAIN(_rx_queue)				\
	_EFX_CHANNEL_MAGIC(_EFX_CHANNEL_MAGIC_RX_DRAIN,			\
			   efx_rx_queue_index(_rx_queue))
#घोषणा EFX_CHANNEL_MAGIC_TX_DRAIN(_tx_queue)				\
	_EFX_CHANNEL_MAGIC(_EFX_CHANNEL_MAGIC_TX_DRAIN,			\
			   (_tx_queue)->queue)

अटल व्योम efx_farch_magic_event(काष्ठा efx_channel *channel, u32 magic);

/**************************************************************************
 *
 * Hardware access
 *
 **************************************************************************/

अटल अंतरभूत व्योम efx_ग_लिखो_buf_tbl(काष्ठा efx_nic *efx, efx_qword_t *value,
				     अचिन्हित पूर्णांक index)
अणु
	efx_sram_ग_लिखोq(efx, efx->membase + efx->type->buf_tbl_base,
			value, index);
पूर्ण

अटल bool efx_masked_compare_oword(स्थिर efx_oword_t *a, स्थिर efx_oword_t *b,
				     स्थिर efx_oword_t *mask)
अणु
	वापस ((a->u64[0] ^ b->u64[0]) & mask->u64[0]) ||
		((a->u64[1] ^ b->u64[1]) & mask->u64[1]);
पूर्ण

पूर्णांक efx_farch_test_रेजिस्टरs(काष्ठा efx_nic *efx,
			     स्थिर काष्ठा efx_farch_रेजिस्टर_test *regs,
			     माप_प्रकार n_regs)
अणु
	अचिन्हित address = 0;
	पूर्णांक i, j;
	efx_oword_t mask, imask, original, reg, buf;

	क्रम (i = 0; i < n_regs; ++i) अणु
		address = regs[i].address;
		mask = imask = regs[i].mask;
		EFX_INVERT_OWORD(imask);

		efx_पढ़ोo(efx, &original, address);

		/* bit sweep on and off */
		क्रम (j = 0; j < 128; j++) अणु
			अगर (!EFX_EXTRACT_OWORD32(mask, j, j))
				जारी;

			/* Test this testable bit can be set in isolation */
			EFX_AND_OWORD(reg, original, mask);
			EFX_SET_OWORD32(reg, j, j, 1);

			efx_ग_लिखोo(efx, &reg, address);
			efx_पढ़ोo(efx, &buf, address);

			अगर (efx_masked_compare_oword(&reg, &buf, &mask))
				जाओ fail;

			/* Test this testable bit can be cleared in isolation */
			EFX_OR_OWORD(reg, original, mask);
			EFX_SET_OWORD32(reg, j, j, 0);

			efx_ग_लिखोo(efx, &reg, address);
			efx_पढ़ोo(efx, &buf, address);

			अगर (efx_masked_compare_oword(&reg, &buf, &mask))
				जाओ fail;
		पूर्ण

		efx_ग_लिखोo(efx, &original, address);
	पूर्ण

	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev,
		  "wrote "EFX_OWORD_FMT" read "EFX_OWORD_FMT
		  " at address 0x%x mask "EFX_OWORD_FMT"\n", EFX_OWORD_VAL(reg),
		  EFX_OWORD_VAL(buf), address, EFX_OWORD_VAL(mask));
	वापस -EIO;
पूर्ण

/**************************************************************************
 *
 * Special buffer handling
 * Special buffers are used क्रम event queues and the TX and RX
 * descriptor rings.
 *
 *************************************************************************/

/*
 * Initialise a special buffer
 *
 * This will define a buffer (previously allocated via
 * efx_alloc_special_buffer()) in the buffer table, allowing
 * it to be used क्रम event queues, descriptor rings etc.
 */
अटल व्योम
efx_init_special_buffer(काष्ठा efx_nic *efx, काष्ठा efx_special_buffer *buffer)
अणु
	efx_qword_t buf_desc;
	अचिन्हित पूर्णांक index;
	dma_addr_t dma_addr;
	पूर्णांक i;

	EFX_WARN_ON_PARANOID(!buffer->buf.addr);

	/* Write buffer descriptors to NIC */
	क्रम (i = 0; i < buffer->entries; i++) अणु
		index = buffer->index + i;
		dma_addr = buffer->buf.dma_addr + (i * EFX_BUF_SIZE);
		netअगर_dbg(efx, probe, efx->net_dev,
			  "mapping special buffer %d at %llx\n",
			  index, (अचिन्हित दीर्घ दीर्घ)dma_addr);
		EFX_POPULATE_QWORD_3(buf_desc,
				     FRF_AZ_BUF_ADR_REGION, 0,
				     FRF_AZ_BUF_ADR_FBUF, dma_addr >> 12,
				     FRF_AZ_BUF_OWNER_ID_FBUF, 0);
		efx_ग_लिखो_buf_tbl(efx, &buf_desc, index);
	पूर्ण
पूर्ण

/* Unmaps a buffer and clears the buffer table entries */
अटल व्योम
efx_fini_special_buffer(काष्ठा efx_nic *efx, काष्ठा efx_special_buffer *buffer)
अणु
	efx_oword_t buf_tbl_upd;
	अचिन्हित पूर्णांक start = buffer->index;
	अचिन्हित पूर्णांक end = (buffer->index + buffer->entries - 1);

	अगर (!buffer->entries)
		वापस;

	netअगर_dbg(efx, hw, efx->net_dev, "unmapping special buffers %d-%d\n",
		  buffer->index, buffer->index + buffer->entries - 1);

	EFX_POPULATE_OWORD_4(buf_tbl_upd,
			     FRF_AZ_BUF_UPD_CMD, 0,
			     FRF_AZ_BUF_CLR_CMD, 1,
			     FRF_AZ_BUF_CLR_END_ID, end,
			     FRF_AZ_BUF_CLR_START_ID, start);
	efx_ग_लिखोo(efx, &buf_tbl_upd, FR_AZ_BUF_TBL_UPD);
पूर्ण

/*
 * Allocate a new special buffer
 *
 * This allocates memory क्रम a new buffer, clears it and allocates a
 * new buffer ID range.  It करोes not ग_लिखो पूर्णांकo the buffer table.
 *
 * This call will allocate 4KB buffers, since 8KB buffers can't be
 * used क्रम event queues and descriptor rings.
 */
अटल पूर्णांक efx_alloc_special_buffer(काष्ठा efx_nic *efx,
				    काष्ठा efx_special_buffer *buffer,
				    अचिन्हित पूर्णांक len)
अणु
#अगर_घोषित CONFIG_SFC_SRIOV
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
#पूर्ण_अगर
	len = ALIGN(len, EFX_BUF_SIZE);

	अगर (efx_nic_alloc_buffer(efx, &buffer->buf, len, GFP_KERNEL))
		वापस -ENOMEM;
	buffer->entries = len / EFX_BUF_SIZE;
	BUG_ON(buffer->buf.dma_addr & (EFX_BUF_SIZE - 1));

	/* Select new buffer ID */
	buffer->index = efx->next_buffer_table;
	efx->next_buffer_table += buffer->entries;
#अगर_घोषित CONFIG_SFC_SRIOV
	BUG_ON(efx_siena_sriov_enabled(efx) &&
	       nic_data->vf_buftbl_base < efx->next_buffer_table);
#पूर्ण_अगर

	netअगर_dbg(efx, probe, efx->net_dev,
		  "allocating special buffers %d-%d at %llx+%x "
		  "(virt %p phys %llx)\n", buffer->index,
		  buffer->index + buffer->entries - 1,
		  (u64)buffer->buf.dma_addr, len,
		  buffer->buf.addr, (u64)virt_to_phys(buffer->buf.addr));

	वापस 0;
पूर्ण

अटल व्योम
efx_मुक्त_special_buffer(काष्ठा efx_nic *efx, काष्ठा efx_special_buffer *buffer)
अणु
	अगर (!buffer->buf.addr)
		वापस;

	netअगर_dbg(efx, hw, efx->net_dev,
		  "deallocating special buffers %d-%d at %llx+%x "
		  "(virt %p phys %llx)\n", buffer->index,
		  buffer->index + buffer->entries - 1,
		  (u64)buffer->buf.dma_addr, buffer->buf.len,
		  buffer->buf.addr, (u64)virt_to_phys(buffer->buf.addr));

	efx_nic_मुक्त_buffer(efx, &buffer->buf);
	buffer->entries = 0;
पूर्ण

/**************************************************************************
 *
 * TX path
 *
 **************************************************************************/

/* This ग_लिखोs to the TX_DESC_WPTR; ग_लिखो poपूर्णांकer क्रम TX descriptor ring */
अटल अंतरभूत व्योम efx_farch_notअगरy_tx_desc(काष्ठा efx_tx_queue *tx_queue)
अणु
	अचिन्हित ग_लिखो_ptr;
	efx_dword_t reg;

	ग_लिखो_ptr = tx_queue->ग_लिखो_count & tx_queue->ptr_mask;
	EFX_POPULATE_DWORD_1(reg, FRF_AZ_TX_DESC_WPTR_DWORD, ग_लिखो_ptr);
	efx_ग_लिखोd_page(tx_queue->efx, &reg,
			FR_AZ_TX_DESC_UPD_DWORD_P0, tx_queue->queue);
पूर्ण

/* Write poपूर्णांकer and first descriptor क्रम TX descriptor ring */
अटल अंतरभूत व्योम efx_farch_push_tx_desc(काष्ठा efx_tx_queue *tx_queue,
					  स्थिर efx_qword_t *txd)
अणु
	अचिन्हित ग_लिखो_ptr;
	efx_oword_t reg;

	BUILD_BUG_ON(FRF_AZ_TX_DESC_LBN != 0);
	BUILD_BUG_ON(FR_AA_TX_DESC_UPD_KER != FR_BZ_TX_DESC_UPD_P0);

	ग_लिखो_ptr = tx_queue->ग_लिखो_count & tx_queue->ptr_mask;
	EFX_POPULATE_OWORD_2(reg, FRF_AZ_TX_DESC_PUSH_CMD, true,
			     FRF_AZ_TX_DESC_WPTR, ग_लिखो_ptr);
	reg.qword[0] = *txd;
	efx_ग_लिखोo_page(tx_queue->efx, &reg,
			FR_BZ_TX_DESC_UPD_P0, tx_queue->queue);
पूर्ण


/* For each entry inserted पूर्णांकo the software descriptor ring, create a
 * descriptor in the hardware TX descriptor ring (in host memory), and
 * ग_लिखो a करोorbell.
 */
व्योम efx_farch_tx_ग_लिखो(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_tx_buffer *buffer;
	efx_qword_t *txd;
	अचिन्हित ग_लिखो_ptr;
	अचिन्हित old_ग_लिखो_count = tx_queue->ग_लिखो_count;

	tx_queue->xmit_pending = false;
	अगर (unlikely(tx_queue->ग_लिखो_count == tx_queue->insert_count))
		वापस;

	करो अणु
		ग_लिखो_ptr = tx_queue->ग_लिखो_count & tx_queue->ptr_mask;
		buffer = &tx_queue->buffer[ग_लिखो_ptr];
		txd = efx_tx_desc(tx_queue, ग_लिखो_ptr);
		++tx_queue->ग_लिखो_count;

		EFX_WARN_ON_ONCE_PARANOID(buffer->flags & EFX_TX_BUF_OPTION);

		/* Create TX descriptor ring entry */
		BUILD_BUG_ON(EFX_TX_BUF_CONT != 1);
		EFX_POPULATE_QWORD_4(*txd,
				     FSF_AZ_TX_KER_CONT,
				     buffer->flags & EFX_TX_BUF_CONT,
				     FSF_AZ_TX_KER_BYTE_COUNT, buffer->len,
				     FSF_AZ_TX_KER_BUF_REGION, 0,
				     FSF_AZ_TX_KER_BUF_ADDR, buffer->dma_addr);
	पूर्ण जबतक (tx_queue->ग_लिखो_count != tx_queue->insert_count);

	wmb(); /* Ensure descriptors are written beक्रमe they are fetched */

	अगर (efx_nic_may_push_tx_desc(tx_queue, old_ग_लिखो_count)) अणु
		txd = efx_tx_desc(tx_queue,
				  old_ग_लिखो_count & tx_queue->ptr_mask);
		efx_farch_push_tx_desc(tx_queue, txd);
		++tx_queue->pushes;
	पूर्ण अन्यथा अणु
		efx_farch_notअगरy_tx_desc(tx_queue);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक efx_farch_tx_limit_len(काष्ठा efx_tx_queue *tx_queue,
				    dma_addr_t dma_addr, अचिन्हित पूर्णांक len)
अणु
	/* Don't cross 4K boundaries with descriptors. */
	अचिन्हित पूर्णांक limit = (~dma_addr & (EFX_PAGE_SIZE - 1)) + 1;

	len = min(limit, len);

	वापस len;
पूर्ण


/* Allocate hardware resources क्रम a TX queue */
पूर्णांक efx_farch_tx_probe(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	अचिन्हित entries;

	tx_queue->type = ((tx_queue->label & 1) ? EFX_TXQ_TYPE_OUTER_CSUM : 0) |
			 ((tx_queue->label & 2) ? EFX_TXQ_TYPE_HIGHPRI : 0);
	entries = tx_queue->ptr_mask + 1;
	वापस efx_alloc_special_buffer(efx, &tx_queue->txd,
					entries * माप(efx_qword_t));
पूर्ण

व्योम efx_farch_tx_init(काष्ठा efx_tx_queue *tx_queue)
अणु
	पूर्णांक csum = tx_queue->type & EFX_TXQ_TYPE_OUTER_CSUM;
	काष्ठा efx_nic *efx = tx_queue->efx;
	efx_oword_t reg;

	/* Pin TX descriptor ring */
	efx_init_special_buffer(efx, &tx_queue->txd);

	/* Push TX descriptor ring to card */
	EFX_POPULATE_OWORD_10(reg,
			      FRF_AZ_TX_DESCQ_EN, 1,
			      FRF_AZ_TX_ISCSI_DDIG_EN, 0,
			      FRF_AZ_TX_ISCSI_HDIG_EN, 0,
			      FRF_AZ_TX_DESCQ_BUF_BASE_ID, tx_queue->txd.index,
			      FRF_AZ_TX_DESCQ_EVQ_ID,
			      tx_queue->channel->channel,
			      FRF_AZ_TX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_TX_DESCQ_LABEL, tx_queue->label,
			      FRF_AZ_TX_DESCQ_SIZE,
			      __ffs(tx_queue->txd.entries),
			      FRF_AZ_TX_DESCQ_TYPE, 0,
			      FRF_BZ_TX_NON_IP_DROP_DIS, 1);

	EFX_SET_OWORD_FIELD(reg, FRF_BZ_TX_IP_CHKSM_DIS, !csum);
	EFX_SET_OWORD_FIELD(reg, FRF_BZ_TX_TCP_CHKSM_DIS, !csum);

	efx_ग_लिखोo_table(efx, &reg, efx->type->txd_ptr_tbl_base,
			 tx_queue->queue);

	EFX_POPULATE_OWORD_1(reg,
			     FRF_BZ_TX_PACE,
			     (tx_queue->type & EFX_TXQ_TYPE_HIGHPRI) ?
			     FFE_BZ_TX_PACE_OFF :
			     FFE_BZ_TX_PACE_RESERVED);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_TX_PACE_TBL, tx_queue->queue);

	tx_queue->tso_version = 1;
पूर्ण

अटल व्योम efx_farch_flush_tx_queue(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	efx_oword_t tx_flush_descq;

	WARN_ON(atomic_पढ़ो(&tx_queue->flush_outstanding));
	atomic_set(&tx_queue->flush_outstanding, 1);

	EFX_POPULATE_OWORD_2(tx_flush_descq,
			     FRF_AZ_TX_FLUSH_DESCQ_CMD, 1,
			     FRF_AZ_TX_FLUSH_DESCQ, tx_queue->queue);
	efx_ग_लिखोo(efx, &tx_flush_descq, FR_AZ_TX_FLUSH_DESCQ);
पूर्ण

व्योम efx_farch_tx_fini(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	efx_oword_t tx_desc_ptr;

	/* Remove TX descriptor ring from card */
	EFX_ZERO_OWORD(tx_desc_ptr);
	efx_ग_लिखोo_table(efx, &tx_desc_ptr, efx->type->txd_ptr_tbl_base,
			 tx_queue->queue);

	/* Unpin TX descriptor ring */
	efx_fini_special_buffer(efx, &tx_queue->txd);
पूर्ण

/* Free buffers backing TX queue */
व्योम efx_farch_tx_हटाओ(काष्ठा efx_tx_queue *tx_queue)
अणु
	efx_मुक्त_special_buffer(tx_queue->efx, &tx_queue->txd);
पूर्ण

/**************************************************************************
 *
 * RX path
 *
 **************************************************************************/

/* This creates an entry in the RX descriptor queue */
अटल अंतरभूत व्योम
efx_farch_build_rx_desc(काष्ठा efx_rx_queue *rx_queue, अचिन्हित index)
अणु
	काष्ठा efx_rx_buffer *rx_buf;
	efx_qword_t *rxd;

	rxd = efx_rx_desc(rx_queue, index);
	rx_buf = efx_rx_buffer(rx_queue, index);
	EFX_POPULATE_QWORD_3(*rxd,
			     FSF_AZ_RX_KER_BUF_SIZE,
			     rx_buf->len -
			     rx_queue->efx->type->rx_buffer_padding,
			     FSF_AZ_RX_KER_BUF_REGION, 0,
			     FSF_AZ_RX_KER_BUF_ADDR, rx_buf->dma_addr);
पूर्ण

/* This ग_लिखोs to the RX_DESC_WPTR रेजिस्टर क्रम the specअगरied receive
 * descriptor ring.
 */
व्योम efx_farch_rx_ग_लिखो(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	efx_dword_t reg;
	अचिन्हित ग_लिखो_ptr;

	जबतक (rx_queue->notअगरied_count != rx_queue->added_count) अणु
		efx_farch_build_rx_desc(
			rx_queue,
			rx_queue->notअगरied_count & rx_queue->ptr_mask);
		++rx_queue->notअगरied_count;
	पूर्ण

	wmb();
	ग_लिखो_ptr = rx_queue->added_count & rx_queue->ptr_mask;
	EFX_POPULATE_DWORD_1(reg, FRF_AZ_RX_DESC_WPTR_DWORD, ग_लिखो_ptr);
	efx_ग_लिखोd_page(efx, &reg, FR_AZ_RX_DESC_UPD_DWORD_P0,
			efx_rx_queue_index(rx_queue));
पूर्ण

पूर्णांक efx_farch_rx_probe(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित entries;

	entries = rx_queue->ptr_mask + 1;
	वापस efx_alloc_special_buffer(efx, &rx_queue->rxd,
					entries * माप(efx_qword_t));
पूर्ण

व्योम efx_farch_rx_init(काष्ठा efx_rx_queue *rx_queue)
अणु
	efx_oword_t rx_desc_ptr;
	काष्ठा efx_nic *efx = rx_queue->efx;
	bool jumbo_en;

	/* For kernel-mode queues in Siena, the JUMBO flag enables scatter. */
	jumbo_en = efx->rx_scatter;

	netअगर_dbg(efx, hw, efx->net_dev,
		  "RX queue %d ring in special buffers %d-%d\n",
		  efx_rx_queue_index(rx_queue), rx_queue->rxd.index,
		  rx_queue->rxd.index + rx_queue->rxd.entries - 1);

	rx_queue->scatter_n = 0;

	/* Pin RX descriptor ring */
	efx_init_special_buffer(efx, &rx_queue->rxd);

	/* Push RX descriptor ring to card */
	EFX_POPULATE_OWORD_10(rx_desc_ptr,
			      FRF_AZ_RX_ISCSI_DDIG_EN, true,
			      FRF_AZ_RX_ISCSI_HDIG_EN, true,
			      FRF_AZ_RX_DESCQ_BUF_BASE_ID, rx_queue->rxd.index,
			      FRF_AZ_RX_DESCQ_EVQ_ID,
			      efx_rx_queue_channel(rx_queue)->channel,
			      FRF_AZ_RX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_RX_DESCQ_LABEL,
			      efx_rx_queue_index(rx_queue),
			      FRF_AZ_RX_DESCQ_SIZE,
			      __ffs(rx_queue->rxd.entries),
			      FRF_AZ_RX_DESCQ_TYPE, 0 /* kernel queue */ ,
			      FRF_AZ_RX_DESCQ_JUMBO, jumbo_en,
			      FRF_AZ_RX_DESCQ_EN, 1);
	efx_ग_लिखोo_table(efx, &rx_desc_ptr, efx->type->rxd_ptr_tbl_base,
			 efx_rx_queue_index(rx_queue));
पूर्ण

अटल व्योम efx_farch_flush_rx_queue(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	efx_oword_t rx_flush_descq;

	EFX_POPULATE_OWORD_2(rx_flush_descq,
			     FRF_AZ_RX_FLUSH_DESCQ_CMD, 1,
			     FRF_AZ_RX_FLUSH_DESCQ,
			     efx_rx_queue_index(rx_queue));
	efx_ग_लिखोo(efx, &rx_flush_descq, FR_AZ_RX_FLUSH_DESCQ);
पूर्ण

व्योम efx_farch_rx_fini(काष्ठा efx_rx_queue *rx_queue)
अणु
	efx_oword_t rx_desc_ptr;
	काष्ठा efx_nic *efx = rx_queue->efx;

	/* Remove RX descriptor ring from card */
	EFX_ZERO_OWORD(rx_desc_ptr);
	efx_ग_लिखोo_table(efx, &rx_desc_ptr, efx->type->rxd_ptr_tbl_base,
			 efx_rx_queue_index(rx_queue));

	/* Unpin RX descriptor ring */
	efx_fini_special_buffer(efx, &rx_queue->rxd);
पूर्ण

/* Free buffers backing RX queue */
व्योम efx_farch_rx_हटाओ(काष्ठा efx_rx_queue *rx_queue)
अणु
	efx_मुक्त_special_buffer(rx_queue->efx, &rx_queue->rxd);
पूर्ण

/**************************************************************************
 *
 * Flush handling
 *
 **************************************************************************/

/* efx_farch_flush_queues() must be woken up when all flushes are completed,
 * or more RX flushes can be kicked off.
 */
अटल bool efx_farch_flush_wake(काष्ठा efx_nic *efx)
अणु
	/* Ensure that all updates are visible to efx_farch_flush_queues() */
	smp_mb();

	वापस (atomic_पढ़ो(&efx->active_queues) == 0 ||
		(atomic_पढ़ो(&efx->rxq_flush_outstanding) < EFX_RX_FLUSH_COUNT
		 && atomic_पढ़ो(&efx->rxq_flush_pending) > 0));
पूर्ण

अटल bool efx_check_tx_flush_complete(काष्ठा efx_nic *efx)
अणु
	bool i = true;
	efx_oword_t txd_ptr_tbl;
	काष्ठा efx_channel *channel;
	काष्ठा efx_tx_queue *tx_queue;

	efx_क्रम_each_channel(channel, efx) अणु
		efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
			efx_पढ़ोo_table(efx, &txd_ptr_tbl,
					FR_BZ_TX_DESC_PTR_TBL, tx_queue->queue);
			अगर (EFX_OWORD_FIELD(txd_ptr_tbl,
					    FRF_AZ_TX_DESCQ_FLUSH) ||
			    EFX_OWORD_FIELD(txd_ptr_tbl,
					    FRF_AZ_TX_DESCQ_EN)) अणु
				netअगर_dbg(efx, hw, efx->net_dev,
					  "flush did not complete on TXQ %d\n",
					  tx_queue->queue);
				i = false;
			पूर्ण अन्यथा अगर (atomic_cmpxchg(&tx_queue->flush_outstanding,
						  1, 0)) अणु
				/* The flush is complete, but we didn't
				 * receive a flush completion event
				 */
				netअगर_dbg(efx, hw, efx->net_dev,
					  "flush complete on TXQ %d, so drain "
					  "the queue\n", tx_queue->queue);
				/* Don't need to increment active_queues as it
				 * has alपढ़ोy been incremented क्रम the queues
				 * which did not drain
				 */
				efx_farch_magic_event(channel,
						      EFX_CHANNEL_MAGIC_TX_DRAIN(
							      tx_queue));
			पूर्ण
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

/* Flush all the transmit queues, and जारी flushing receive queues until
 * they're all flushed. Wait क्रम the DRAIN events to be received so that there
 * are no more RX and TX events left on any channel. */
अटल पूर्णांक efx_farch_करो_flush(काष्ठा efx_nic *efx)
अणु
	अचिन्हित समयout = msecs_to_jअगरfies(5000); /* 5s क्रम all flushes and drains */
	काष्ठा efx_channel *channel;
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_tx_queue *tx_queue;
	पूर्णांक rc = 0;

	efx_क्रम_each_channel(channel, efx) अणु
		efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
			efx_farch_flush_tx_queue(tx_queue);
		पूर्ण
		efx_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
			rx_queue->flush_pending = true;
			atomic_inc(&efx->rxq_flush_pending);
		पूर्ण
	पूर्ण

	जबतक (समयout && atomic_पढ़ो(&efx->active_queues) > 0) अणु
		/* If SRIOV is enabled, then offload receive queue flushing to
		 * the firmware (though we will still have to poll क्रम
		 * completion). If that fails, fall back to the old scheme.
		 */
		अगर (efx_siena_sriov_enabled(efx)) अणु
			rc = efx_mcdi_flush_rxqs(efx);
			अगर (!rc)
				जाओ रुको;
		पूर्ण

		/* The hardware supports four concurrent rx flushes, each of
		 * which may need to be retried अगर there is an outstanding
		 * descriptor fetch
		 */
		efx_क्रम_each_channel(channel, efx) अणु
			efx_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
				अगर (atomic_पढ़ो(&efx->rxq_flush_outstanding) >=
				    EFX_RX_FLUSH_COUNT)
					अवरोध;

				अगर (rx_queue->flush_pending) अणु
					rx_queue->flush_pending = false;
					atomic_dec(&efx->rxq_flush_pending);
					atomic_inc(&efx->rxq_flush_outstanding);
					efx_farch_flush_rx_queue(rx_queue);
				पूर्ण
			पूर्ण
		पूर्ण

	रुको:
		समयout = रुको_event_समयout(efx->flush_wq,
					     efx_farch_flush_wake(efx),
					     समयout);
	पूर्ण

	अगर (atomic_पढ़ो(&efx->active_queues) &&
	    !efx_check_tx_flush_complete(efx)) अणु
		netअगर_err(efx, hw, efx->net_dev, "failed to flush %d queues "
			  "(rx %d+%d)\n", atomic_पढ़ो(&efx->active_queues),
			  atomic_पढ़ो(&efx->rxq_flush_outstanding),
			  atomic_पढ़ो(&efx->rxq_flush_pending));
		rc = -ETIMEDOUT;

		atomic_set(&efx->active_queues, 0);
		atomic_set(&efx->rxq_flush_pending, 0);
		atomic_set(&efx->rxq_flush_outstanding, 0);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक efx_farch_fini_dmaq(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;
	पूर्णांक rc = 0;

	/* Do not attempt to ग_लिखो to the NIC during EEH recovery */
	अगर (efx->state != STATE_RECOVERY) अणु
		/* Only perक्रमm flush अगर DMA is enabled */
		अगर (efx->pci_dev->is_busmaster) अणु
			efx->type->prepare_flush(efx);
			rc = efx_farch_करो_flush(efx);
			efx->type->finish_flush(efx);
		पूर्ण

		efx_क्रम_each_channel(channel, efx) अणु
			efx_क्रम_each_channel_rx_queue(rx_queue, channel)
				efx_farch_rx_fini(rx_queue);
			efx_क्रम_each_channel_tx_queue(tx_queue, channel)
				efx_farch_tx_fini(tx_queue);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* Reset queue and flush accounting after FLR
 *
 * One possible cause of FLR recovery is that DMA may be failing (eg. अगर bus
 * mastering was disabled), in which हाल we करोn't receive (RXQ) flush
 * completion events.  This means that efx->rxq_flush_outstanding reमुख्यed at 4
 * after the FLR; also, efx->active_queues was non-zero (as no flush completion
 * events were received, and we didn't go through efx_check_tx_flush_complete())
 * If we करोn't fix this up, on the next call to efx_realloc_channels() we won't
 * flush any RX queues because efx->rxq_flush_outstanding is at the limit of 4
 * क्रम batched flush requests; and the efx->active_queues माला_लो messed up because
 * we keep incrementing क्रम the newly initialised queues, but it never went to
 * zero previously.  Then we get a समयout every समय we try to restart the
 * queues, as it करोesn't go back to zero when we should be flushing the queues.
 */
व्योम efx_farch_finish_flr(काष्ठा efx_nic *efx)
अणु
	atomic_set(&efx->rxq_flush_pending, 0);
	atomic_set(&efx->rxq_flush_outstanding, 0);
	atomic_set(&efx->active_queues, 0);
पूर्ण


/**************************************************************************
 *
 * Event queue processing
 * Event queues are processed by per-channel tasklets.
 *
 **************************************************************************/

/* Update a channel's event queue's पढ़ो poपूर्णांकer (RPTR) रेजिस्टर
 *
 * This ग_लिखोs the EVQ_RPTR_REG रेजिस्टर क्रम the specअगरied channel's
 * event queue.
 */
व्योम efx_farch_ev_पढ़ो_ack(काष्ठा efx_channel *channel)
अणु
	efx_dword_t reg;
	काष्ठा efx_nic *efx = channel->efx;

	EFX_POPULATE_DWORD_1(reg, FRF_AZ_EVQ_RPTR,
			     channel->eventq_पढ़ो_ptr & channel->eventq_mask);

	/* For Falcon A1, EVQ_RPTR_KER is करोcumented as having a step size
	 * of 4 bytes, but it is really 16 bytes just like later revisions.
	 */
	efx_ग_लिखोd(efx, &reg,
		   efx->type->evq_rptr_tbl_base +
		   FR_BZ_EVQ_RPTR_STEP * channel->channel);
पूर्ण

/* Use HW to insert a SW defined event */
व्योम efx_farch_generate_event(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक evq,
			      efx_qword_t *event)
अणु
	efx_oword_t drv_ev_reg;

	BUILD_BUG_ON(FRF_AZ_DRV_EV_DATA_LBN != 0 ||
		     FRF_AZ_DRV_EV_DATA_WIDTH != 64);
	drv_ev_reg.u32[0] = event->u32[0];
	drv_ev_reg.u32[1] = event->u32[1];
	drv_ev_reg.u32[2] = 0;
	drv_ev_reg.u32[3] = 0;
	EFX_SET_OWORD_FIELD(drv_ev_reg, FRF_AZ_DRV_EV_QID, evq);
	efx_ग_लिखोo(efx, &drv_ev_reg, FR_AZ_DRV_EV);
पूर्ण

अटल व्योम efx_farch_magic_event(काष्ठा efx_channel *channel, u32 magic)
अणु
	efx_qword_t event;

	EFX_POPULATE_QWORD_2(event, FSF_AZ_EV_CODE,
			     FSE_AZ_EV_CODE_DRV_GEN_EV,
			     FSF_AZ_DRV_GEN_EV_MAGIC, magic);
	efx_farch_generate_event(channel->efx, channel->channel, &event);
पूर्ण

/* Handle a transmit completion event
 *
 * The NIC batches TX completion events; the message we receive is of
 * the क्रमm "complete all TX events up to this index".
 */
अटल व्योम
efx_farch_handle_tx_event(काष्ठा efx_channel *channel, efx_qword_t *event)
अणु
	अचिन्हित पूर्णांक tx_ev_desc_ptr;
	अचिन्हित पूर्णांक tx_ev_q_label;
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_nic *efx = channel->efx;

	अगर (unlikely(READ_ONCE(efx->reset_pending)))
		वापस;

	अगर (likely(EFX_QWORD_FIELD(*event, FSF_AZ_TX_EV_COMP))) अणु
		/* Transmit completion */
		tx_ev_desc_ptr = EFX_QWORD_FIELD(*event, FSF_AZ_TX_EV_DESC_PTR);
		tx_ev_q_label = EFX_QWORD_FIELD(*event, FSF_AZ_TX_EV_Q_LABEL);
		tx_queue = channel->tx_queue +
				(tx_ev_q_label % EFX_MAX_TXQ_PER_CHANNEL);
		efx_xmit_करोne(tx_queue, tx_ev_desc_ptr);
	पूर्ण अन्यथा अगर (EFX_QWORD_FIELD(*event, FSF_AZ_TX_EV_WQ_FF_FULL)) अणु
		/* Reग_लिखो the FIFO ग_लिखो poपूर्णांकer */
		tx_ev_q_label = EFX_QWORD_FIELD(*event, FSF_AZ_TX_EV_Q_LABEL);
		tx_queue = channel->tx_queue +
				(tx_ev_q_label % EFX_MAX_TXQ_PER_CHANNEL);

		netअगर_tx_lock(efx->net_dev);
		efx_farch_notअगरy_tx_desc(tx_queue);
		netअगर_tx_unlock(efx->net_dev);
	पूर्ण अन्यथा अगर (EFX_QWORD_FIELD(*event, FSF_AZ_TX_EV_PKT_ERR)) अणु
		efx_schedule_reset(efx, RESET_TYPE_DMA_ERROR);
	पूर्ण अन्यथा अणु
		netअगर_err(efx, tx_err, efx->net_dev,
			  "channel %d unexpected TX event "
			  EFX_QWORD_FMT"\n", channel->channel,
			  EFX_QWORD_VAL(*event));
	पूर्ण
पूर्ण

/* Detect errors included in the rx_evt_pkt_ok bit. */
अटल u16 efx_farch_handle_rx_not_ok(काष्ठा efx_rx_queue *rx_queue,
				      स्थिर efx_qword_t *event)
अणु
	काष्ठा efx_channel *channel = efx_rx_queue_channel(rx_queue);
	काष्ठा efx_nic *efx = rx_queue->efx;
	bool rx_ev_buf_owner_id_err, rx_ev_ip_hdr_chksum_err;
	bool rx_ev_tcp_udp_chksum_err, rx_ev_eth_crc_err;
	bool rx_ev_frm_trunc, rx_ev_tobe_disc;
	bool rx_ev_other_err, rx_ev_छोड़ो_frm;

	rx_ev_tobe_disc = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_TOBE_DISC);
	rx_ev_buf_owner_id_err = EFX_QWORD_FIELD(*event,
						 FSF_AZ_RX_EV_BUF_OWNER_ID_ERR);
	rx_ev_ip_hdr_chksum_err = EFX_QWORD_FIELD(*event,
						  FSF_AZ_RX_EV_IP_HDR_CHKSUM_ERR);
	rx_ev_tcp_udp_chksum_err = EFX_QWORD_FIELD(*event,
						   FSF_AZ_RX_EV_TCP_UDP_CHKSUM_ERR);
	rx_ev_eth_crc_err = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_ETH_CRC_ERR);
	rx_ev_frm_trunc = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_FRM_TRUNC);
	rx_ev_छोड़ो_frm = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_PAUSE_FRM_ERR);

	/* Every error apart from tobe_disc and छोड़ो_frm */
	rx_ev_other_err = (rx_ev_tcp_udp_chksum_err |
			   rx_ev_buf_owner_id_err | rx_ev_eth_crc_err |
			   rx_ev_frm_trunc | rx_ev_ip_hdr_chksum_err);

	/* Count errors that are not in MAC stats.  Ignore expected
	 * checksum errors during self-test. */
	अगर (rx_ev_frm_trunc)
		++channel->n_rx_frm_trunc;
	अन्यथा अगर (rx_ev_tobe_disc)
		++channel->n_rx_tobe_disc;
	अन्यथा अगर (!efx->loopback_selftest) अणु
		अगर (rx_ev_ip_hdr_chksum_err)
			++channel->n_rx_ip_hdr_chksum_err;
		अन्यथा अगर (rx_ev_tcp_udp_chksum_err)
			++channel->n_rx_tcp_udp_chksum_err;
	पूर्ण

	/* TOBE_DISC is expected on unicast mismatches; करोn't prपूर्णांक out an
	 * error message.  FRM_TRUNC indicates RXDP dropped the packet due
	 * to a FIFO overflow.
	 */
#अगर_घोषित DEBUG
	अगर (rx_ev_other_err && net_ratelimit()) अणु
		netअगर_dbg(efx, rx_err, efx->net_dev,
			  " RX queue %d unexpected RX event "
			  EFX_QWORD_FMT "%s%s%s%s%s%s%s\n",
			  efx_rx_queue_index(rx_queue), EFX_QWORD_VAL(*event),
			  rx_ev_buf_owner_id_err ? " [OWNER_ID_ERR]" : "",
			  rx_ev_ip_hdr_chksum_err ?
			  " [IP_HDR_CHKSUM_ERR]" : "",
			  rx_ev_tcp_udp_chksum_err ?
			  " [TCP_UDP_CHKSUM_ERR]" : "",
			  rx_ev_eth_crc_err ? " [ETH_CRC_ERR]" : "",
			  rx_ev_frm_trunc ? " [FRM_TRUNC]" : "",
			  rx_ev_tobe_disc ? " [TOBE_DISC]" : "",
			  rx_ev_छोड़ो_frm ? " [PAUSE]" : "");
	पूर्ण
#अन्यथा
	(व्योम) rx_ev_other_err;
#पूर्ण_अगर

	अगर (efx->net_dev->features & NETIF_F_RXALL)
		/* करोn't discard frame क्रम CRC error */
		rx_ev_eth_crc_err = false;

	/* The frame must be discarded अगर any of these are true. */
	वापस (rx_ev_eth_crc_err | rx_ev_frm_trunc |
		rx_ev_tobe_disc | rx_ev_छोड़ो_frm) ?
		EFX_RX_PKT_DISCARD : 0;
पूर्ण

/* Handle receive events that are not in-order. Return true अगर this
 * can be handled as a partial packet discard, false अगर it's more
 * serious.
 */
अटल bool
efx_farch_handle_rx_bad_index(काष्ठा efx_rx_queue *rx_queue, अचिन्हित index)
अणु
	काष्ठा efx_channel *channel = efx_rx_queue_channel(rx_queue);
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित expected, dropped;

	अगर (rx_queue->scatter_n &&
	    index == ((rx_queue->हटाओd_count + rx_queue->scatter_n - 1) &
		      rx_queue->ptr_mask)) अणु
		++channel->n_rx_nodesc_trunc;
		वापस true;
	पूर्ण

	expected = rx_queue->हटाओd_count & rx_queue->ptr_mask;
	dropped = (index - expected) & rx_queue->ptr_mask;
	netअगर_info(efx, rx_err, efx->net_dev,
		   "dropped %d events (index=%d expected=%d)\n",
		   dropped, index, expected);

	efx_schedule_reset(efx, RESET_TYPE_DISABLE);
	वापस false;
पूर्ण

/* Handle a packet received event
 *
 * The NIC gives a "discard" flag अगर it's a unicast packet with the
 * wrong destination address
 * Also "is multicast" and "matches multicast filter" flags can be used to
 * discard non-matching multicast packets.
 */
अटल व्योम
efx_farch_handle_rx_event(काष्ठा efx_channel *channel, स्थिर efx_qword_t *event)
अणु
	अचिन्हित पूर्णांक rx_ev_desc_ptr, rx_ev_byte_cnt;
	अचिन्हित पूर्णांक rx_ev_hdr_type, rx_ev_mcast_pkt;
	अचिन्हित expected_ptr;
	bool rx_ev_pkt_ok, rx_ev_sop, rx_ev_cont;
	u16 flags;
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_nic *efx = channel->efx;

	अगर (unlikely(READ_ONCE(efx->reset_pending)))
		वापस;

	rx_ev_cont = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_JUMBO_CONT);
	rx_ev_sop = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_SOP);
	WARN_ON(EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_Q_LABEL) !=
		channel->channel);

	rx_queue = efx_channel_get_rx_queue(channel);

	rx_ev_desc_ptr = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_DESC_PTR);
	expected_ptr = ((rx_queue->हटाओd_count + rx_queue->scatter_n) &
			rx_queue->ptr_mask);

	/* Check क्रम partial drops and other errors */
	अगर (unlikely(rx_ev_desc_ptr != expected_ptr) ||
	    unlikely(rx_ev_sop != (rx_queue->scatter_n == 0))) अणु
		अगर (rx_ev_desc_ptr != expected_ptr &&
		    !efx_farch_handle_rx_bad_index(rx_queue, rx_ev_desc_ptr))
			वापस;

		/* Discard all pending fragments */
		अगर (rx_queue->scatter_n) अणु
			efx_rx_packet(
				rx_queue,
				rx_queue->हटाओd_count & rx_queue->ptr_mask,
				rx_queue->scatter_n, 0, EFX_RX_PKT_DISCARD);
			rx_queue->हटाओd_count += rx_queue->scatter_n;
			rx_queue->scatter_n = 0;
		पूर्ण

		/* Return अगर there is no new fragment */
		अगर (rx_ev_desc_ptr != expected_ptr)
			वापस;

		/* Discard new fragment अगर not SOP */
		अगर (!rx_ev_sop) अणु
			efx_rx_packet(
				rx_queue,
				rx_queue->हटाओd_count & rx_queue->ptr_mask,
				1, 0, EFX_RX_PKT_DISCARD);
			++rx_queue->हटाओd_count;
			वापस;
		पूर्ण
	पूर्ण

	++rx_queue->scatter_n;
	अगर (rx_ev_cont)
		वापस;

	rx_ev_byte_cnt = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_BYTE_CNT);
	rx_ev_pkt_ok = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_PKT_OK);
	rx_ev_hdr_type = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_HDR_TYPE);

	अगर (likely(rx_ev_pkt_ok)) अणु
		/* If packet is marked as OK then we can rely on the
		 * hardware checksum and classअगरication.
		 */
		flags = 0;
		चयन (rx_ev_hdr_type) अणु
		हाल FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_TCP:
			flags |= EFX_RX_PKT_TCP;
			fallthrough;
		हाल FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_UDP:
			flags |= EFX_RX_PKT_CSUMMED;
			fallthrough;
		हाल FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_OTHER:
		हाल FSE_AZ_RX_EV_HDR_TYPE_OTHER:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		flags = efx_farch_handle_rx_not_ok(rx_queue, event);
	पूर्ण

	/* Detect multicast packets that didn't match the filter */
	rx_ev_mcast_pkt = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_MCAST_PKT);
	अगर (rx_ev_mcast_pkt) अणु
		अचिन्हित पूर्णांक rx_ev_mcast_hash_match =
			EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_MCAST_HASH_MATCH);

		अगर (unlikely(!rx_ev_mcast_hash_match)) अणु
			++channel->n_rx_mcast_mismatch;
			flags |= EFX_RX_PKT_DISCARD;
		पूर्ण
	पूर्ण

	channel->irq_mod_score += 2;

	/* Handle received packet */
	efx_rx_packet(rx_queue,
		      rx_queue->हटाओd_count & rx_queue->ptr_mask,
		      rx_queue->scatter_n, rx_ev_byte_cnt, flags);
	rx_queue->हटाओd_count += rx_queue->scatter_n;
	rx_queue->scatter_n = 0;
पूर्ण

/* If this flush करोne event corresponds to a &काष्ठा efx_tx_queue, then
 * send an %EFX_CHANNEL_MAGIC_TX_DRAIN event to drain the event queue
 * of all transmit completions.
 */
अटल व्योम
efx_farch_handle_tx_flush_करोne(काष्ठा efx_nic *efx, efx_qword_t *event)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_channel *channel;
	पूर्णांक qid;

	qid = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBDATA);
	अगर (qid < EFX_MAX_TXQ_PER_CHANNEL * (efx->n_tx_channels + efx->n_extra_tx_channels)) अणु
		channel = efx_get_tx_channel(efx, qid / EFX_MAX_TXQ_PER_CHANNEL);
		tx_queue = channel->tx_queue + (qid % EFX_MAX_TXQ_PER_CHANNEL);
		अगर (atomic_cmpxchg(&tx_queue->flush_outstanding, 1, 0))
			efx_farch_magic_event(tx_queue->channel,
					      EFX_CHANNEL_MAGIC_TX_DRAIN(tx_queue));
	पूर्ण
पूर्ण

/* If this flush करोne event corresponds to a &काष्ठा efx_rx_queue: If the flush
 * was successful then send an %EFX_CHANNEL_MAGIC_RX_DRAIN, otherwise add
 * the RX queue back to the mask of RX queues in need of flushing.
 */
अटल व्योम
efx_farch_handle_rx_flush_करोne(काष्ठा efx_nic *efx, efx_qword_t *event)
अणु
	काष्ठा efx_channel *channel;
	काष्ठा efx_rx_queue *rx_queue;
	पूर्णांक qid;
	bool failed;

	qid = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_RX_DESCQ_ID);
	failed = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_RX_FLUSH_FAIL);
	अगर (qid >= efx->n_channels)
		वापस;
	channel = efx_get_channel(efx, qid);
	अगर (!efx_channel_has_rx_queue(channel))
		वापस;
	rx_queue = efx_channel_get_rx_queue(channel);

	अगर (failed) अणु
		netअगर_info(efx, hw, efx->net_dev,
			   "RXQ %d flush retry\n", qid);
		rx_queue->flush_pending = true;
		atomic_inc(&efx->rxq_flush_pending);
	पूर्ण अन्यथा अणु
		efx_farch_magic_event(efx_rx_queue_channel(rx_queue),
				      EFX_CHANNEL_MAGIC_RX_DRAIN(rx_queue));
	पूर्ण
	atomic_dec(&efx->rxq_flush_outstanding);
	अगर (efx_farch_flush_wake(efx))
		wake_up(&efx->flush_wq);
पूर्ण

अटल व्योम
efx_farch_handle_drain_event(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;

	WARN_ON(atomic_पढ़ो(&efx->active_queues) == 0);
	atomic_dec(&efx->active_queues);
	अगर (efx_farch_flush_wake(efx))
		wake_up(&efx->flush_wq);
पूर्ण

अटल व्योम efx_farch_handle_generated_event(काष्ठा efx_channel *channel,
					     efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_rx_queue *rx_queue =
		efx_channel_has_rx_queue(channel) ?
		efx_channel_get_rx_queue(channel) : शून्य;
	अचिन्हित magic, code;

	magic = EFX_QWORD_FIELD(*event, FSF_AZ_DRV_GEN_EV_MAGIC);
	code = _EFX_CHANNEL_MAGIC_CODE(magic);

	अगर (magic == EFX_CHANNEL_MAGIC_TEST(channel)) अणु
		channel->event_test_cpu = raw_smp_processor_id();
	पूर्ण अन्यथा अगर (rx_queue && magic == EFX_CHANNEL_MAGIC_FILL(rx_queue)) अणु
		/* The queue must be empty, so we won't receive any rx
		 * events, so efx_process_channel() won't refill the
		 * queue. Refill it here */
		efx_fast_push_rx_descriptors(rx_queue, true);
	पूर्ण अन्यथा अगर (rx_queue && magic == EFX_CHANNEL_MAGIC_RX_DRAIN(rx_queue)) अणु
		efx_farch_handle_drain_event(channel);
	पूर्ण अन्यथा अगर (code == _EFX_CHANNEL_MAGIC_TX_DRAIN) अणु
		efx_farch_handle_drain_event(channel);
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, hw, efx->net_dev, "channel %d received "
			  "generated event "EFX_QWORD_FMT"\n",
			  channel->channel, EFX_QWORD_VAL(*event));
	पूर्ण
पूर्ण

अटल व्योम
efx_farch_handle_driver_event(काष्ठा efx_channel *channel, efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	अचिन्हित पूर्णांक ev_sub_code;
	अचिन्हित पूर्णांक ev_sub_data;

	ev_sub_code = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBCODE);
	ev_sub_data = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBDATA);

	चयन (ev_sub_code) अणु
	हाल FSE_AZ_TX_DESCQ_FLS_DONE_EV:
		netअगर_vdbg(efx, hw, efx->net_dev, "channel %d TXQ %d flushed\n",
			   channel->channel, ev_sub_data);
		efx_farch_handle_tx_flush_करोne(efx, event);
#अगर_घोषित CONFIG_SFC_SRIOV
		efx_siena_sriov_tx_flush_करोne(efx, event);
#पूर्ण_अगर
		अवरोध;
	हाल FSE_AZ_RX_DESCQ_FLS_DONE_EV:
		netअगर_vdbg(efx, hw, efx->net_dev, "channel %d RXQ %d flushed\n",
			   channel->channel, ev_sub_data);
		efx_farch_handle_rx_flush_करोne(efx, event);
#अगर_घोषित CONFIG_SFC_SRIOV
		efx_siena_sriov_rx_flush_करोne(efx, event);
#पूर्ण_अगर
		अवरोध;
	हाल FSE_AZ_EVQ_INIT_DONE_EV:
		netअगर_dbg(efx, hw, efx->net_dev,
			  "channel %d EVQ %d initialised\n",
			  channel->channel, ev_sub_data);
		अवरोध;
	हाल FSE_AZ_SRM_UPD_DONE_EV:
		netअगर_vdbg(efx, hw, efx->net_dev,
			   "channel %d SRAM update done\n", channel->channel);
		अवरोध;
	हाल FSE_AZ_WAKE_UP_EV:
		netअगर_vdbg(efx, hw, efx->net_dev,
			   "channel %d RXQ %d wakeup event\n",
			   channel->channel, ev_sub_data);
		अवरोध;
	हाल FSE_AZ_TIMER_EV:
		netअगर_vdbg(efx, hw, efx->net_dev,
			   "channel %d RX queue %d timer expired\n",
			   channel->channel, ev_sub_data);
		अवरोध;
	हाल FSE_AA_RX_RECOVER_EV:
		netअगर_err(efx, rx_err, efx->net_dev,
			  "channel %d seen DRIVER RX_RESET event. "
			"Resetting.\n", channel->channel);
		atomic_inc(&efx->rx_reset);
		efx_schedule_reset(efx, RESET_TYPE_DISABLE);
		अवरोध;
	हाल FSE_BZ_RX_DSC_ERROR_EV:
		अगर (ev_sub_data < EFX_VI_BASE) अणु
			netअगर_err(efx, rx_err, efx->net_dev,
				  "RX DMA Q %d reports descriptor fetch error."
				  " RX Q %d is disabled.\n", ev_sub_data,
				  ev_sub_data);
			efx_schedule_reset(efx, RESET_TYPE_DMA_ERROR);
		पूर्ण
#अगर_घोषित CONFIG_SFC_SRIOV
		अन्यथा
			efx_siena_sriov_desc_fetch_err(efx, ev_sub_data);
#पूर्ण_अगर
		अवरोध;
	हाल FSE_BZ_TX_DSC_ERROR_EV:
		अगर (ev_sub_data < EFX_VI_BASE) अणु
			netअगर_err(efx, tx_err, efx->net_dev,
				  "TX DMA Q %d reports descriptor fetch error."
				  " TX Q %d is disabled.\n", ev_sub_data,
				  ev_sub_data);
			efx_schedule_reset(efx, RESET_TYPE_DMA_ERROR);
		पूर्ण
#अगर_घोषित CONFIG_SFC_SRIOV
		अन्यथा
			efx_siena_sriov_desc_fetch_err(efx, ev_sub_data);
#पूर्ण_अगर
		अवरोध;
	शेष:
		netअगर_vdbg(efx, hw, efx->net_dev,
			   "channel %d unknown driver event code %d "
			   "data %04x\n", channel->channel, ev_sub_code,
			   ev_sub_data);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक efx_farch_ev_process(काष्ठा efx_channel *channel, पूर्णांक budget)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	अचिन्हित पूर्णांक पढ़ो_ptr;
	efx_qword_t event, *p_event;
	पूर्णांक ev_code;
	पूर्णांक spent = 0;

	अगर (budget <= 0)
		वापस spent;

	पढ़ो_ptr = channel->eventq_पढ़ो_ptr;

	क्रम (;;) अणु
		p_event = efx_event(channel, पढ़ो_ptr);
		event = *p_event;

		अगर (!efx_event_present(&event))
			/* End of events */
			अवरोध;

		netअगर_vdbg(channel->efx, पूर्णांकr, channel->efx->net_dev,
			   "channel %d event is "EFX_QWORD_FMT"\n",
			   channel->channel, EFX_QWORD_VAL(event));

		/* Clear this event by marking it all ones */
		EFX_SET_QWORD(*p_event);

		++पढ़ो_ptr;

		ev_code = EFX_QWORD_FIELD(event, FSF_AZ_EV_CODE);

		चयन (ev_code) अणु
		हाल FSE_AZ_EV_CODE_RX_EV:
			efx_farch_handle_rx_event(channel, &event);
			अगर (++spent == budget)
				जाओ out;
			अवरोध;
		हाल FSE_AZ_EV_CODE_TX_EV:
			efx_farch_handle_tx_event(channel, &event);
			अवरोध;
		हाल FSE_AZ_EV_CODE_DRV_GEN_EV:
			efx_farch_handle_generated_event(channel, &event);
			अवरोध;
		हाल FSE_AZ_EV_CODE_DRIVER_EV:
			efx_farch_handle_driver_event(channel, &event);
			अवरोध;
#अगर_घोषित CONFIG_SFC_SRIOV
		हाल FSE_CZ_EV_CODE_USER_EV:
			efx_siena_sriov_event(channel, &event);
			अवरोध;
#पूर्ण_अगर
		हाल FSE_CZ_EV_CODE_MCDI_EV:
			efx_mcdi_process_event(channel, &event);
			अवरोध;
		हाल FSE_AZ_EV_CODE_GLOBAL_EV:
			अगर (efx->type->handle_global_event &&
			    efx->type->handle_global_event(channel, &event))
				अवरोध;
			fallthrough;
		शेष:
			netअगर_err(channel->efx, hw, channel->efx->net_dev,
				  "channel %d unknown event type %d (data "
				  EFX_QWORD_FMT ")\n", channel->channel,
				  ev_code, EFX_QWORD_VAL(event));
		पूर्ण
	पूर्ण

out:
	channel->eventq_पढ़ो_ptr = पढ़ो_ptr;
	वापस spent;
पूर्ण

/* Allocate buffer table entries क्रम event queue */
पूर्णांक efx_farch_ev_probe(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	अचिन्हित entries;

	entries = channel->eventq_mask + 1;
	वापस efx_alloc_special_buffer(efx, &channel->eventq,
					entries * माप(efx_qword_t));
पूर्ण

पूर्णांक efx_farch_ev_init(काष्ठा efx_channel *channel)
अणु
	efx_oword_t reg;
	काष्ठा efx_nic *efx = channel->efx;

	netअगर_dbg(efx, hw, efx->net_dev,
		  "channel %d event queue in special buffers %d-%d\n",
		  channel->channel, channel->eventq.index,
		  channel->eventq.index + channel->eventq.entries - 1);

	EFX_POPULATE_OWORD_3(reg,
			     FRF_CZ_TIMER_Q_EN, 1,
			     FRF_CZ_HOST_NOTIFY_MODE, 0,
			     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_TIMER_TBL, channel->channel);

	/* Pin event queue buffer */
	efx_init_special_buffer(efx, &channel->eventq);

	/* Fill event queue with all ones (i.e. empty events) */
	स_रखो(channel->eventq.buf.addr, 0xff, channel->eventq.buf.len);

	/* Push event queue to card */
	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(channel->eventq.entries),
			     FRF_AZ_EVQ_BUF_BASE_ID, channel->eventq.index);
	efx_ग_लिखोo_table(efx, &reg, efx->type->evq_ptr_tbl_base,
			 channel->channel);

	वापस 0;
पूर्ण

व्योम efx_farch_ev_fini(काष्ठा efx_channel *channel)
अणु
	efx_oword_t reg;
	काष्ठा efx_nic *efx = channel->efx;

	/* Remove event queue from card */
	EFX_ZERO_OWORD(reg);
	efx_ग_लिखोo_table(efx, &reg, efx->type->evq_ptr_tbl_base,
			 channel->channel);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_TIMER_TBL, channel->channel);

	/* Unpin event queue */
	efx_fini_special_buffer(efx, &channel->eventq);
पूर्ण

/* Free buffers backing event queue */
व्योम efx_farch_ev_हटाओ(काष्ठा efx_channel *channel)
अणु
	efx_मुक्त_special_buffer(channel->efx, &channel->eventq);
पूर्ण


व्योम efx_farch_ev_test_generate(काष्ठा efx_channel *channel)
अणु
	efx_farch_magic_event(channel, EFX_CHANNEL_MAGIC_TEST(channel));
पूर्ण

व्योम efx_farch_rx_defer_refill(काष्ठा efx_rx_queue *rx_queue)
अणु
	efx_farch_magic_event(efx_rx_queue_channel(rx_queue),
			      EFX_CHANNEL_MAGIC_FILL(rx_queue));
पूर्ण

/**************************************************************************
 *
 * Hardware पूर्णांकerrupts
 * The hardware पूर्णांकerrupt handler करोes very little work; all the event
 * queue processing is carried out by per-channel tasklets.
 *
 **************************************************************************/

/* Enable/disable/generate पूर्णांकerrupts */
अटल अंतरभूत व्योम efx_farch_पूर्णांकerrupts(काष्ठा efx_nic *efx,
				      bool enabled, bool क्रमce)
अणु
	efx_oword_t पूर्णांक_en_reg_ker;

	EFX_POPULATE_OWORD_3(पूर्णांक_en_reg_ker,
			     FRF_AZ_KER_INT_LEVE_SEL, efx->irq_level,
			     FRF_AZ_KER_INT_KER, क्रमce,
			     FRF_AZ_DRV_INT_EN_KER, enabled);
	efx_ग_लिखोo(efx, &पूर्णांक_en_reg_ker, FR_AZ_INT_EN_KER);
पूर्ण

व्योम efx_farch_irq_enable_master(काष्ठा efx_nic *efx)
अणु
	EFX_ZERO_OWORD(*((efx_oword_t *) efx->irq_status.addr));
	wmb(); /* Ensure पूर्णांकerrupt vector is clear beक्रमe पूर्णांकerrupts enabled */

	efx_farch_पूर्णांकerrupts(efx, true, false);
पूर्ण

व्योम efx_farch_irq_disable_master(काष्ठा efx_nic *efx)
अणु
	/* Disable पूर्णांकerrupts */
	efx_farch_पूर्णांकerrupts(efx, false, false);
पूर्ण

/* Generate a test पूर्णांकerrupt
 * Interrupt must alपढ़ोy have been enabled, otherwise nasty things
 * may happen.
 */
पूर्णांक efx_farch_irq_test_generate(काष्ठा efx_nic *efx)
अणु
	efx_farch_पूर्णांकerrupts(efx, true, true);
	वापस 0;
पूर्ण

/* Process a fatal पूर्णांकerrupt
 * Disable bus mastering ASAP and schedule a reset
 */
irqवापस_t efx_farch_fatal_पूर्णांकerrupt(काष्ठा efx_nic *efx)
अणु
	efx_oword_t *पूर्णांक_ker = efx->irq_status.addr;
	efx_oword_t fatal_पूर्णांकr;
	पूर्णांक error, mem_perr;

	efx_पढ़ोo(efx, &fatal_पूर्णांकr, FR_AZ_FATAL_INTR_KER);
	error = EFX_OWORD_FIELD(fatal_पूर्णांकr, FRF_AZ_FATAL_INTR);

	netअगर_err(efx, hw, efx->net_dev, "SYSTEM ERROR "EFX_OWORD_FMT" status "
		  EFX_OWORD_FMT ": %s\n", EFX_OWORD_VAL(*पूर्णांक_ker),
		  EFX_OWORD_VAL(fatal_पूर्णांकr),
		  error ? "disabling bus mastering" : "no recognised error");

	/* If this is a memory parity error dump which blocks are offending */
	mem_perr = (EFX_OWORD_FIELD(fatal_पूर्णांकr, FRF_AZ_MEM_PERR_INT_KER) ||
		    EFX_OWORD_FIELD(fatal_पूर्णांकr, FRF_AZ_SRM_PERR_INT_KER));
	अगर (mem_perr) अणु
		efx_oword_t reg;
		efx_पढ़ोo(efx, &reg, FR_AZ_MEM_STAT);
		netअगर_err(efx, hw, efx->net_dev,
			  "SYSTEM ERROR: memory parity error "EFX_OWORD_FMT"\n",
			  EFX_OWORD_VAL(reg));
	पूर्ण

	/* Disable both devices */
	pci_clear_master(efx->pci_dev);
	efx_farch_irq_disable_master(efx);

	/* Count errors and reset or disable the NIC accordingly */
	अगर (efx->पूर्णांक_error_count == 0 ||
	    समय_after(jअगरfies, efx->पूर्णांक_error_expire)) अणु
		efx->पूर्णांक_error_count = 0;
		efx->पूर्णांक_error_expire =
			jअगरfies + EFX_INT_ERROR_EXPIRE * HZ;
	पूर्ण
	अगर (++efx->पूर्णांक_error_count < EFX_MAX_INT_ERRORS) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "SYSTEM ERROR - reset scheduled\n");
		efx_schedule_reset(efx, RESET_TYPE_INT_ERROR);
	पूर्ण अन्यथा अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "SYSTEM ERROR - max number of errors seen."
			  "NIC will be disabled\n");
		efx_schedule_reset(efx, RESET_TYPE_DISABLE);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Handle a legacy पूर्णांकerrupt
 * Acknowledges the पूर्णांकerrupt and schedule event queue processing.
 */
irqवापस_t efx_farch_legacy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा efx_nic *efx = dev_id;
	bool soft_enabled = READ_ONCE(efx->irq_soft_enabled);
	efx_oword_t *पूर्णांक_ker = efx->irq_status.addr;
	irqवापस_t result = IRQ_NONE;
	काष्ठा efx_channel *channel;
	efx_dword_t reg;
	u32 queues;
	पूर्णांक syserr;

	/* Read the ISR which also ACKs the पूर्णांकerrupts */
	efx_पढ़ोd(efx, &reg, FR_BZ_INT_ISR0);
	queues = EFX_EXTRACT_DWORD(reg, 0, 31);

	/* Legacy पूर्णांकerrupts are disabled too late by the EEH kernel
	 * code. Disable them earlier.
	 * If an EEH error occurred, the पढ़ो will have वापसed all ones.
	 */
	अगर (EFX_DWORD_IS_ALL_ONES(reg) && efx_try_recovery(efx) &&
	    !efx->eeh_disabled_legacy_irq) अणु
		disable_irq_nosync(efx->legacy_irq);
		efx->eeh_disabled_legacy_irq = true;
	पूर्ण

	/* Handle non-event-queue sources */
	अगर (queues & (1U << efx->irq_level) && soft_enabled) अणु
		syserr = EFX_OWORD_FIELD(*पूर्णांक_ker, FSF_AZ_NET_IVEC_FATAL_INT);
		अगर (unlikely(syserr))
			वापस efx_farch_fatal_पूर्णांकerrupt(efx);
		efx->last_irq_cpu = raw_smp_processor_id();
	पूर्ण

	अगर (queues != 0) अणु
		efx->irq_zero_count = 0;

		/* Schedule processing of any पूर्णांकerrupting queues */
		अगर (likely(soft_enabled)) अणु
			efx_क्रम_each_channel(channel, efx) अणु
				अगर (queues & 1)
					efx_schedule_channel_irq(channel);
				queues >>= 1;
			पूर्ण
		पूर्ण
		result = IRQ_HANDLED;

	पूर्ण अन्यथा अणु
		efx_qword_t *event;

		/* Legacy ISR पढ़ो can वापस zero once (SF bug 15783) */

		/* We can't वापस IRQ_HANDLED more than once on seeing ISR=0
		 * because this might be a shared पूर्णांकerrupt. */
		अगर (efx->irq_zero_count++ == 0)
			result = IRQ_HANDLED;

		/* Ensure we schedule or rearm all event queues */
		अगर (likely(soft_enabled)) अणु
			efx_क्रम_each_channel(channel, efx) अणु
				event = efx_event(channel,
						  channel->eventq_पढ़ो_ptr);
				अगर (efx_event_present(event))
					efx_schedule_channel_irq(channel);
				अन्यथा
					efx_farch_ev_पढ़ो_ack(channel);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (result == IRQ_HANDLED)
		netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
			   "IRQ %d on CPU %d status " EFX_DWORD_FMT "\n",
			   irq, raw_smp_processor_id(), EFX_DWORD_VAL(reg));

	वापस result;
पूर्ण

/* Handle an MSI पूर्णांकerrupt
 *
 * Handle an MSI hardware पूर्णांकerrupt.  This routine schedules event
 * queue processing.  No पूर्णांकerrupt acknowledgement cycle is necessary.
 * Also, we never need to check that the पूर्णांकerrupt is क्रम us, since
 * MSI पूर्णांकerrupts cannot be shared.
 */
irqवापस_t efx_farch_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा efx_msi_context *context = dev_id;
	काष्ठा efx_nic *efx = context->efx;
	efx_oword_t *पूर्णांक_ker = efx->irq_status.addr;
	पूर्णांक syserr;

	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "IRQ %d on CPU %d status " EFX_OWORD_FMT "\n",
		   irq, raw_smp_processor_id(), EFX_OWORD_VAL(*पूर्णांक_ker));

	अगर (!likely(READ_ONCE(efx->irq_soft_enabled)))
		वापस IRQ_HANDLED;

	/* Handle non-event-queue sources */
	अगर (context->index == efx->irq_level) अणु
		syserr = EFX_OWORD_FIELD(*पूर्णांक_ker, FSF_AZ_NET_IVEC_FATAL_INT);
		अगर (unlikely(syserr))
			वापस efx_farch_fatal_पूर्णांकerrupt(efx);
		efx->last_irq_cpu = raw_smp_processor_id();
	पूर्ण

	/* Schedule processing of the channel */
	efx_schedule_channel_irq(efx->channel[context->index]);

	वापस IRQ_HANDLED;
पूर्ण

/* Setup RSS indirection table.
 * This maps from the hash value of the packet to RXQ
 */
व्योम efx_farch_rx_push_indir_table(काष्ठा efx_nic *efx)
अणु
	माप_प्रकार i = 0;
	efx_dword_t dword;

	BUILD_BUG_ON(ARRAY_SIZE(efx->rss_context.rx_indir_table) !=
		     FR_BZ_RX_INसूचीECTION_TBL_ROWS);

	क्रम (i = 0; i < FR_BZ_RX_INसूचीECTION_TBL_ROWS; i++) अणु
		EFX_POPULATE_DWORD_1(dword, FRF_BZ_IT_QUEUE,
				     efx->rss_context.rx_indir_table[i]);
		efx_ग_लिखोd(efx, &dword,
			   FR_BZ_RX_INसूचीECTION_TBL +
			   FR_BZ_RX_INसूचीECTION_TBL_STEP * i);
	पूर्ण
पूर्ण

व्योम efx_farch_rx_pull_indir_table(काष्ठा efx_nic *efx)
अणु
	माप_प्रकार i = 0;
	efx_dword_t dword;

	BUILD_BUG_ON(ARRAY_SIZE(efx->rss_context.rx_indir_table) !=
		     FR_BZ_RX_INसूचीECTION_TBL_ROWS);

	क्रम (i = 0; i < FR_BZ_RX_INसूचीECTION_TBL_ROWS; i++) अणु
		efx_पढ़ोd(efx, &dword,
			   FR_BZ_RX_INसूचीECTION_TBL +
			   FR_BZ_RX_INसूचीECTION_TBL_STEP * i);
		efx->rss_context.rx_indir_table[i] = EFX_DWORD_FIELD(dword, FRF_BZ_IT_QUEUE);
	पूर्ण
पूर्ण

/* Looks at available SRAM resources and works out how many queues we
 * can support, and where things like descriptor caches should live.
 *
 * SRAM is split up as follows:
 * 0                          buftbl entries क्रम channels
 * efx->vf_buftbl_base        buftbl entries क्रम SR-IOV
 * efx->rx_dc_base            RX descriptor caches
 * efx->tx_dc_base            TX descriptor caches
 */
व्योम efx_farch_dimension_resources(काष्ठा efx_nic *efx, अचिन्हित sram_lim_qw)
अणु
	अचिन्हित vi_count, buftbl_min, total_tx_channels;

#अगर_घोषित CONFIG_SFC_SRIOV
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
#पूर्ण_अगर

	total_tx_channels = efx->n_tx_channels + efx->n_extra_tx_channels;
	/* Account क्रम the buffer table entries backing the datapath channels
	 * and the descriptor caches क्रम those channels.
	 */
	buftbl_min = ((efx->n_rx_channels * EFX_MAX_DMAQ_SIZE +
		       total_tx_channels * EFX_MAX_TXQ_PER_CHANNEL * EFX_MAX_DMAQ_SIZE +
		       efx->n_channels * EFX_MAX_EVQ_SIZE)
		      * माप(efx_qword_t) / EFX_BUF_SIZE);
	vi_count = max(efx->n_channels, total_tx_channels * EFX_MAX_TXQ_PER_CHANNEL);

#अगर_घोषित CONFIG_SFC_SRIOV
	अगर (efx->type->sriov_wanted) अणु
		अगर (efx->type->sriov_wanted(efx)) अणु
			अचिन्हित vi_dc_entries, buftbl_मुक्त;
			अचिन्हित entries_per_vf, vf_limit;

			nic_data->vf_buftbl_base = buftbl_min;

			vi_dc_entries = RX_DC_ENTRIES + TX_DC_ENTRIES;
			vi_count = max(vi_count, EFX_VI_BASE);
			buftbl_मुक्त = (sram_lim_qw - buftbl_min -
				       vi_count * vi_dc_entries);

			entries_per_vf = ((vi_dc_entries +
					   EFX_VF_BUFTBL_PER_VI) *
					  efx_vf_size(efx));
			vf_limit = min(buftbl_मुक्त / entries_per_vf,
				       (1024U - EFX_VI_BASE) >> efx->vi_scale);

			अगर (efx->vf_count > vf_limit) अणु
				netअगर_err(efx, probe, efx->net_dev,
					  "Reducing VF count from from %d to %d\n",
					  efx->vf_count, vf_limit);
				efx->vf_count = vf_limit;
			पूर्ण
			vi_count += efx->vf_count * efx_vf_size(efx);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	efx->tx_dc_base = sram_lim_qw - vi_count * TX_DC_ENTRIES;
	efx->rx_dc_base = efx->tx_dc_base - vi_count * RX_DC_ENTRIES;
पूर्ण

u32 efx_farch_fpga_ver(काष्ठा efx_nic *efx)
अणु
	efx_oword_t altera_build;
	efx_पढ़ोo(efx, &altera_build, FR_AZ_ALTERA_BUILD);
	वापस EFX_OWORD_FIELD(altera_build, FRF_AZ_ALTERA_BUILD_VER);
पूर्ण

व्योम efx_farch_init_common(काष्ठा efx_nic *efx)
अणु
	efx_oword_t temp;

	/* Set positions of descriptor caches in SRAM. */
	EFX_POPULATE_OWORD_1(temp, FRF_AZ_SRM_TX_DC_BASE_ADR, efx->tx_dc_base);
	efx_ग_लिखोo(efx, &temp, FR_AZ_SRM_TX_DC_CFG);
	EFX_POPULATE_OWORD_1(temp, FRF_AZ_SRM_RX_DC_BASE_ADR, efx->rx_dc_base);
	efx_ग_लिखोo(efx, &temp, FR_AZ_SRM_RX_DC_CFG);

	/* Set TX descriptor cache size. */
	BUILD_BUG_ON(TX_DC_ENTRIES != (8 << TX_DC_ENTRIES_ORDER));
	EFX_POPULATE_OWORD_1(temp, FRF_AZ_TX_DC_SIZE, TX_DC_ENTRIES_ORDER);
	efx_ग_लिखोo(efx, &temp, FR_AZ_TX_DC_CFG);

	/* Set RX descriptor cache size.  Set low watermark to size-8, as
	 * this allows most efficient prefetching.
	 */
	BUILD_BUG_ON(RX_DC_ENTRIES != (8 << RX_DC_ENTRIES_ORDER));
	EFX_POPULATE_OWORD_1(temp, FRF_AZ_RX_DC_SIZE, RX_DC_ENTRIES_ORDER);
	efx_ग_लिखोo(efx, &temp, FR_AZ_RX_DC_CFG);
	EFX_POPULATE_OWORD_1(temp, FRF_AZ_RX_DC_PF_LWM, RX_DC_ENTRIES - 8);
	efx_ग_लिखोo(efx, &temp, FR_AZ_RX_DC_PF_WM);

	/* Program INT_KER address */
	EFX_POPULATE_OWORD_2(temp,
			     FRF_AZ_NORM_INT_VEC_DIS_KER,
			     EFX_INT_MODE_USE_MSI(efx),
			     FRF_AZ_INT_ADR_KER, efx->irq_status.dma_addr);
	efx_ग_लिखोo(efx, &temp, FR_AZ_INT_ADR_KER);

	अगर (EFX_WORKAROUND_17213(efx) && !EFX_INT_MODE_USE_MSI(efx))
		/* Use an पूर्णांकerrupt level unused by event queues */
		efx->irq_level = 0x1f;
	अन्यथा
		/* Use a valid MSI-X vector */
		efx->irq_level = 0;

	/* Enable all the genuinely fatal पूर्णांकerrupts.  (They are still
	 * masked by the overall पूर्णांकerrupt mask, controlled by
	 * falcon_पूर्णांकerrupts()).
	 *
	 * Note: All other fatal पूर्णांकerrupts are enabled
	 */
	EFX_POPULATE_OWORD_3(temp,
			     FRF_AZ_ILL_ADR_INT_KER_EN, 1,
			     FRF_AZ_RBUF_OWN_INT_KER_EN, 1,
			     FRF_AZ_TBUF_OWN_INT_KER_EN, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_CZ_SRAM_PERR_INT_P_KER_EN, 1);
	EFX_INVERT_OWORD(temp);
	efx_ग_लिखोo(efx, &temp, FR_AZ_FATAL_INTR_KER);

	/* Disable the ugly समयr-based TX DMA backoff and allow TX DMA to be
	 * controlled by the RX FIFO fill level. Set arbitration to one pkt/Q.
	 */
	efx_पढ़ोo(efx, &temp, FR_AZ_TX_RESERVED);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_RX_SPACER, 0xfe);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_RX_SPACER_EN, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_ONE_PKT_PER_Q, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_PUSH_EN, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_DIS_NON_IP_EV, 1);
	/* Enable SW_EV to inherit in अक्षर driver - assume harmless here */
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_SOFT_EVT_EN, 1);
	/* Prefetch threshold 2 => fetch when descriptor cache half empty */
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_PREF_THRESHOLD, 2);
	/* Disable hardware watchकरोg which can misfire */
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_PREF_WD_TMR, 0x3fffff);
	/* Squash TX of packets of 16 bytes or less */
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_TX_FLUSH_MIN_LEN_EN, 1);
	efx_ग_लिखोo(efx, &temp, FR_AZ_TX_RESERVED);

	EFX_POPULATE_OWORD_4(temp,
			     /* Default values */
			     FRF_BZ_TX_PACE_SB_NOT_AF, 0x15,
			     FRF_BZ_TX_PACE_SB_AF, 0xb,
			     FRF_BZ_TX_PACE_FB_BASE, 0,
			     /* Allow large pace values in the fast bin. */
			     FRF_BZ_TX_PACE_BIN_TH,
			     FFE_BZ_TX_PACE_RESERVED);
	efx_ग_लिखोo(efx, &temp, FR_BZ_TX_PACE);
पूर्ण

/**************************************************************************
 *
 * Filter tables
 *
 **************************************************************************
 */

/* "Fudge factors" - dअगरference between programmed value and actual depth.
 * Due to pipelined implementation we need to program H/W with a value that
 * is larger than the hop limit we want.
 */
#घोषणा EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD 3
#घोषणा EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL 1

/* Hard maximum search limit.  Hardware will समय-out beyond 200-something.
 * We also need to aव्योम infinite loops in efx_farch_filter_search() when the
 * table is full.
 */
#घोषणा EFX_FARCH_FILTER_CTL_SRCH_MAX 200

/* Don't try very hard to find space क्रम perक्रमmance hपूर्णांकs, as this is
 * counter-productive. */
#घोषणा EFX_FARCH_FILTER_CTL_SRCH_Hपूर्णांक_उच्च 5

क्रमागत efx_farch_filter_type अणु
	EFX_FARCH_FILTER_TCP_FULL = 0,
	EFX_FARCH_FILTER_TCP_WILD,
	EFX_FARCH_FILTER_UDP_FULL,
	EFX_FARCH_FILTER_UDP_WILD,
	EFX_FARCH_FILTER_MAC_FULL = 4,
	EFX_FARCH_FILTER_MAC_WILD,
	EFX_FARCH_FILTER_UC_DEF = 8,
	EFX_FARCH_FILTER_MC_DEF,
	EFX_FARCH_FILTER_TYPE_COUNT,		/* number of specअगरic types */
पूर्ण;

क्रमागत efx_farch_filter_table_id अणु
	EFX_FARCH_FILTER_TABLE_RX_IP = 0,
	EFX_FARCH_FILTER_TABLE_RX_MAC,
	EFX_FARCH_FILTER_TABLE_RX_DEF,
	EFX_FARCH_FILTER_TABLE_TX_MAC,
	EFX_FARCH_FILTER_TABLE_COUNT,
पूर्ण;

क्रमागत efx_farch_filter_index अणु
	EFX_FARCH_FILTER_INDEX_UC_DEF,
	EFX_FARCH_FILTER_INDEX_MC_DEF,
	EFX_FARCH_FILTER_SIZE_RX_DEF,
पूर्ण;

काष्ठा efx_farch_filter_spec अणु
	u8	type:4;
	u8	priority:4;
	u8	flags;
	u16	dmaq_id;
	u32	data[3];
पूर्ण;

काष्ठा efx_farch_filter_table अणु
	क्रमागत efx_farch_filter_table_id id;
	u32		offset;		/* address of table relative to BAR */
	अचिन्हित	size;		/* number of entries */
	अचिन्हित	step;		/* step between entries */
	अचिन्हित	used;		/* number currently used */
	अचिन्हित दीर्घ	*used_biपंचांगap;
	काष्ठा efx_farch_filter_spec *spec;
	अचिन्हित	search_limit[EFX_FARCH_FILTER_TYPE_COUNT];
पूर्ण;

काष्ठा efx_farch_filter_state अणु
	काष्ठा rw_semaphore lock; /* Protects table contents */
	काष्ठा efx_farch_filter_table table[EFX_FARCH_FILTER_TABLE_COUNT];
पूर्ण;

अटल व्योम
efx_farch_filter_table_clear_entry(काष्ठा efx_nic *efx,
				   काष्ठा efx_farch_filter_table *table,
				   अचिन्हित पूर्णांक filter_idx);

/* The filter hash function is LFSR polynomial x^16 + x^3 + 1 of a 32-bit
 * key derived from the n-tuple.  The initial LFSR state is 0xffff. */
अटल u16 efx_farch_filter_hash(u32 key)
अणु
	u16 पंचांगp;

	/* First 16 rounds */
	पंचांगp = 0x1fff ^ key >> 16;
	पंचांगp = पंचांगp ^ पंचांगp >> 3 ^ पंचांगp >> 6;
	पंचांगp = पंचांगp ^ पंचांगp >> 9;
	/* Last 16 rounds */
	पंचांगp = पंचांगp ^ पंचांगp << 13 ^ key;
	पंचांगp = पंचांगp ^ पंचांगp >> 3 ^ पंचांगp >> 6;
	वापस पंचांगp ^ पंचांगp >> 9;
पूर्ण

/* To allow क्रम hash collisions, filter search जारीs at these
 * increments from the first possible entry selected by the hash. */
अटल u16 efx_farch_filter_increment(u32 key)
अणु
	वापस key * 2 - 1;
पूर्ण

अटल क्रमागत efx_farch_filter_table_id
efx_farch_filter_spec_table_id(स्थिर काष्ठा efx_farch_filter_spec *spec)
अणु
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_RX_IP !=
		     (EFX_FARCH_FILTER_TCP_FULL >> 2));
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_RX_IP !=
		     (EFX_FARCH_FILTER_TCP_WILD >> 2));
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_RX_IP !=
		     (EFX_FARCH_FILTER_UDP_FULL >> 2));
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_RX_IP !=
		     (EFX_FARCH_FILTER_UDP_WILD >> 2));
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_RX_MAC !=
		     (EFX_FARCH_FILTER_MAC_FULL >> 2));
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_RX_MAC !=
		     (EFX_FARCH_FILTER_MAC_WILD >> 2));
	BUILD_BUG_ON(EFX_FARCH_FILTER_TABLE_TX_MAC !=
		     EFX_FARCH_FILTER_TABLE_RX_MAC + 2);
	वापस (spec->type >> 2) + ((spec->flags & EFX_FILTER_FLAG_TX) ? 2 : 0);
पूर्ण

अटल व्योम efx_farch_filter_push_rx_config(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	काष्ठा efx_farch_filter_table *table;
	efx_oword_t filter_ctl;

	efx_पढ़ोo(efx, &filter_ctl, FR_BZ_RX_FILTER_CTL);

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_IP];
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_TCP_FULL_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_TCP_FULL] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_TCP_WILD_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_TCP_WILD] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_UDP_FULL_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_UDP_FULL] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
	EFX_SET_OWORD_FIELD(filter_ctl, FRF_BZ_UDP_WILD_SRCH_LIMIT,
			    table->search_limit[EFX_FARCH_FILTER_UDP_WILD] +
			    EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_MAC];
	अगर (table->size) अणु
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_ETHERNET_FULL_SEARCH_LIMIT,
			table->search_limit[EFX_FARCH_FILTER_MAC_FULL] +
			EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_ETHERNET_WILDCARD_SEARCH_LIMIT,
			table->search_limit[EFX_FARCH_FILTER_MAC_WILD] +
			EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);
	पूर्ण

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_DEF];
	अगर (table->size) अणु
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_UNICAST_NOMATCH_Q_ID,
			table->spec[EFX_FARCH_FILTER_INDEX_UC_DEF].dmaq_id);
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_UNICAST_NOMATCH_RSS_ENABLED,
			!!(table->spec[EFX_FARCH_FILTER_INDEX_UC_DEF].flags &
			   EFX_FILTER_FLAG_RX_RSS));
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_MULTICAST_NOMATCH_Q_ID,
			table->spec[EFX_FARCH_FILTER_INDEX_MC_DEF].dmaq_id);
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_CZ_MULTICAST_NOMATCH_RSS_ENABLED,
			!!(table->spec[EFX_FARCH_FILTER_INDEX_MC_DEF].flags &
			   EFX_FILTER_FLAG_RX_RSS));

		/* There is a single bit to enable RX scatter क्रम all
		 * unmatched packets.  Only set it अगर scatter is
		 * enabled in both filter specs.
		 */
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_BZ_SCATTER_ENBL_NO_MATCH_Q,
			!!(table->spec[EFX_FARCH_FILTER_INDEX_UC_DEF].flags &
			   table->spec[EFX_FARCH_FILTER_INDEX_MC_DEF].flags &
			   EFX_FILTER_FLAG_RX_SCATTER));
	पूर्ण अन्यथा अणु
		/* We करोn't expose 'default' filters because unmatched
		 * packets always go to the queue number found in the
		 * RSS table.  But we still need to set the RX scatter
		 * bit here.
		 */
		EFX_SET_OWORD_FIELD(
			filter_ctl, FRF_BZ_SCATTER_ENBL_NO_MATCH_Q,
			efx->rx_scatter);
	पूर्ण

	efx_ग_लिखोo(efx, &filter_ctl, FR_BZ_RX_FILTER_CTL);
पूर्ण

अटल व्योम efx_farch_filter_push_tx_limits(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	काष्ठा efx_farch_filter_table *table;
	efx_oword_t tx_cfg;

	efx_पढ़ोo(efx, &tx_cfg, FR_AZ_TX_CFG);

	table = &state->table[EFX_FARCH_FILTER_TABLE_TX_MAC];
	अगर (table->size) अणु
		EFX_SET_OWORD_FIELD(
			tx_cfg, FRF_CZ_TX_ETH_FILTER_FULL_SEARCH_RANGE,
			table->search_limit[EFX_FARCH_FILTER_MAC_FULL] +
			EFX_FARCH_FILTER_CTL_SRCH_FUDGE_FULL);
		EFX_SET_OWORD_FIELD(
			tx_cfg, FRF_CZ_TX_ETH_FILTER_WILD_SEARCH_RANGE,
			table->search_limit[EFX_FARCH_FILTER_MAC_WILD] +
			EFX_FARCH_FILTER_CTL_SRCH_FUDGE_WILD);
	पूर्ण

	efx_ग_लिखोo(efx, &tx_cfg, FR_AZ_TX_CFG);
पूर्ण

अटल पूर्णांक
efx_farch_filter_from_gen_spec(काष्ठा efx_farch_filter_spec *spec,
			       स्थिर काष्ठा efx_filter_spec *gen_spec)
अणु
	bool is_full = false;

	अगर ((gen_spec->flags & EFX_FILTER_FLAG_RX_RSS) && gen_spec->rss_context)
		वापस -EINVAL;

	spec->priority = gen_spec->priority;
	spec->flags = gen_spec->flags;
	spec->dmaq_id = gen_spec->dmaq_id;

	चयन (gen_spec->match_flags) अणु
	हाल (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_IP_PROTO |
	      EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_LOC_PORT |
	      EFX_FILTER_MATCH_REM_HOST | EFX_FILTER_MATCH_REM_PORT):
		is_full = true;
		fallthrough;
	हाल (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_IP_PROTO |
	      EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_LOC_PORT): अणु
		__be32 rhost, host1, host2;
		__be16 rport, port1, port2;

		EFX_WARN_ON_PARANOID(!(gen_spec->flags & EFX_FILTER_FLAG_RX));

		अगर (gen_spec->ether_type != htons(ETH_P_IP))
			वापस -EPROTONOSUPPORT;
		अगर (gen_spec->loc_port == 0 ||
		    (is_full && gen_spec->rem_port == 0))
			वापस -EADDRNOTAVAIL;
		चयन (gen_spec->ip_proto) अणु
		हाल IPPROTO_TCP:
			spec->type = (is_full ? EFX_FARCH_FILTER_TCP_FULL :
				      EFX_FARCH_FILTER_TCP_WILD);
			अवरोध;
		हाल IPPROTO_UDP:
			spec->type = (is_full ? EFX_FARCH_FILTER_UDP_FULL :
				      EFX_FARCH_FILTER_UDP_WILD);
			अवरोध;
		शेष:
			वापस -EPROTONOSUPPORT;
		पूर्ण

		/* Filter is स्थिरructed in terms of source and destination,
		 * with the odd wrinkle that the ports are swapped in a UDP
		 * wildcard filter.  We need to convert from local and remote
		 * (= zero क्रम wildcard) addresses.
		 */
		rhost = is_full ? gen_spec->rem_host[0] : 0;
		rport = is_full ? gen_spec->rem_port : 0;
		host1 = rhost;
		host2 = gen_spec->loc_host[0];
		अगर (!is_full && gen_spec->ip_proto == IPPROTO_UDP) अणु
			port1 = gen_spec->loc_port;
			port2 = rport;
		पूर्ण अन्यथा अणु
			port1 = rport;
			port2 = gen_spec->loc_port;
		पूर्ण
		spec->data[0] = ntohl(host1) << 16 | ntohs(port1);
		spec->data[1] = ntohs(port2) << 16 | ntohl(host1) >> 16;
		spec->data[2] = ntohl(host2);

		अवरोध;
	पूर्ण

	हाल EFX_FILTER_MATCH_LOC_MAC | EFX_FILTER_MATCH_OUTER_VID:
		is_full = true;
		fallthrough;
	हाल EFX_FILTER_MATCH_LOC_MAC:
		spec->type = (is_full ? EFX_FARCH_FILTER_MAC_FULL :
			      EFX_FARCH_FILTER_MAC_WILD);
		spec->data[0] = is_full ? ntohs(gen_spec->outer_vid) : 0;
		spec->data[1] = (gen_spec->loc_mac[2] << 24 |
				 gen_spec->loc_mac[3] << 16 |
				 gen_spec->loc_mac[4] << 8 |
				 gen_spec->loc_mac[5]);
		spec->data[2] = (gen_spec->loc_mac[0] << 8 |
				 gen_spec->loc_mac[1]);
		अवरोध;

	हाल EFX_FILTER_MATCH_LOC_MAC_IG:
		spec->type = (is_multicast_ether_addr(gen_spec->loc_mac) ?
			      EFX_FARCH_FILTER_MC_DEF :
			      EFX_FARCH_FILTER_UC_DEF);
		स_रखो(spec->data, 0, माप(spec->data)); /* ensure equality */
		अवरोध;

	शेष:
		वापस -EPROTONOSUPPORT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
efx_farch_filter_to_gen_spec(काष्ठा efx_filter_spec *gen_spec,
			     स्थिर काष्ठा efx_farch_filter_spec *spec)
अणु
	bool is_full = false;

	/* *gen_spec should be completely initialised, to be consistent
	 * with efx_filter_init_अणुrx,txपूर्ण() and in हाल we want to copy
	 * it back to userland.
	 */
	स_रखो(gen_spec, 0, माप(*gen_spec));

	gen_spec->priority = spec->priority;
	gen_spec->flags = spec->flags;
	gen_spec->dmaq_id = spec->dmaq_id;

	चयन (spec->type) अणु
	हाल EFX_FARCH_FILTER_TCP_FULL:
	हाल EFX_FARCH_FILTER_UDP_FULL:
		is_full = true;
		fallthrough;
	हाल EFX_FARCH_FILTER_TCP_WILD:
	हाल EFX_FARCH_FILTER_UDP_WILD: अणु
		__be32 host1, host2;
		__be16 port1, port2;

		gen_spec->match_flags =
			EFX_FILTER_MATCH_ETHER_TYPE |
			EFX_FILTER_MATCH_IP_PROTO |
			EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_LOC_PORT;
		अगर (is_full)
			gen_spec->match_flags |= (EFX_FILTER_MATCH_REM_HOST |
						  EFX_FILTER_MATCH_REM_PORT);
		gen_spec->ether_type = htons(ETH_P_IP);
		gen_spec->ip_proto =
			(spec->type == EFX_FARCH_FILTER_TCP_FULL ||
			 spec->type == EFX_FARCH_FILTER_TCP_WILD) ?
			IPPROTO_TCP : IPPROTO_UDP;

		host1 = htonl(spec->data[0] >> 16 | spec->data[1] << 16);
		port1 = htons(spec->data[0]);
		host2 = htonl(spec->data[2]);
		port2 = htons(spec->data[1] >> 16);
		अगर (spec->flags & EFX_FILTER_FLAG_TX) अणु
			gen_spec->loc_host[0] = host1;
			gen_spec->rem_host[0] = host2;
		पूर्ण अन्यथा अणु
			gen_spec->loc_host[0] = host2;
			gen_spec->rem_host[0] = host1;
		पूर्ण
		अगर (!!(gen_spec->flags & EFX_FILTER_FLAG_TX) ^
		    (!is_full && gen_spec->ip_proto == IPPROTO_UDP)) अणु
			gen_spec->loc_port = port1;
			gen_spec->rem_port = port2;
		पूर्ण अन्यथा अणु
			gen_spec->loc_port = port2;
			gen_spec->rem_port = port1;
		पूर्ण

		अवरोध;
	पूर्ण

	हाल EFX_FARCH_FILTER_MAC_FULL:
		is_full = true;
		fallthrough;
	हाल EFX_FARCH_FILTER_MAC_WILD:
		gen_spec->match_flags = EFX_FILTER_MATCH_LOC_MAC;
		अगर (is_full)
			gen_spec->match_flags |= EFX_FILTER_MATCH_OUTER_VID;
		gen_spec->loc_mac[0] = spec->data[2] >> 8;
		gen_spec->loc_mac[1] = spec->data[2];
		gen_spec->loc_mac[2] = spec->data[1] >> 24;
		gen_spec->loc_mac[3] = spec->data[1] >> 16;
		gen_spec->loc_mac[4] = spec->data[1] >> 8;
		gen_spec->loc_mac[5] = spec->data[1];
		gen_spec->outer_vid = htons(spec->data[0]);
		अवरोध;

	हाल EFX_FARCH_FILTER_UC_DEF:
	हाल EFX_FARCH_FILTER_MC_DEF:
		gen_spec->match_flags = EFX_FILTER_MATCH_LOC_MAC_IG;
		gen_spec->loc_mac[0] = spec->type == EFX_FARCH_FILTER_MC_DEF;
		अवरोध;

	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
efx_farch_filter_init_rx_स्वतः(काष्ठा efx_nic *efx,
			      काष्ठा efx_farch_filter_spec *spec)
अणु
	/* If there's only one channel then disable RSS क्रम non VF
	 * traffic, thereby allowing VFs to use RSS when the PF can't.
	 */
	spec->priority = EFX_FILTER_PRI_AUTO;
	spec->flags = (EFX_FILTER_FLAG_RX |
		       (efx_rss_enabled(efx) ? EFX_FILTER_FLAG_RX_RSS : 0) |
		       (efx->rx_scatter ? EFX_FILTER_FLAG_RX_SCATTER : 0));
	spec->dmaq_id = 0;
पूर्ण

/* Build a filter entry and वापस its n-tuple key. */
अटल u32 efx_farch_filter_build(efx_oword_t *filter,
				  काष्ठा efx_farch_filter_spec *spec)
अणु
	u32 data3;

	चयन (efx_farch_filter_spec_table_id(spec)) अणु
	हाल EFX_FARCH_FILTER_TABLE_RX_IP: अणु
		bool is_udp = (spec->type == EFX_FARCH_FILTER_UDP_FULL ||
			       spec->type == EFX_FARCH_FILTER_UDP_WILD);
		EFX_POPULATE_OWORD_7(
			*filter,
			FRF_BZ_RSS_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_RSS),
			FRF_BZ_SCATTER_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_SCATTER),
			FRF_BZ_TCP_UDP, is_udp,
			FRF_BZ_RXQ_ID, spec->dmaq_id,
			EFX_DWORD_2, spec->data[2],
			EFX_DWORD_1, spec->data[1],
			EFX_DWORD_0, spec->data[0]);
		data3 = is_udp;
		अवरोध;
	पूर्ण

	हाल EFX_FARCH_FILTER_TABLE_RX_MAC: अणु
		bool is_wild = spec->type == EFX_FARCH_FILTER_MAC_WILD;
		EFX_POPULATE_OWORD_7(
			*filter,
			FRF_CZ_RMFT_RSS_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_RSS),
			FRF_CZ_RMFT_SCATTER_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_SCATTER),
			FRF_CZ_RMFT_RXQ_ID, spec->dmaq_id,
			FRF_CZ_RMFT_WILDCARD_MATCH, is_wild,
			FRF_CZ_RMFT_DEST_MAC_HI, spec->data[2],
			FRF_CZ_RMFT_DEST_MAC_LO, spec->data[1],
			FRF_CZ_RMFT_VLAN_ID, spec->data[0]);
		data3 = is_wild;
		अवरोध;
	पूर्ण

	हाल EFX_FARCH_FILTER_TABLE_TX_MAC: अणु
		bool is_wild = spec->type == EFX_FARCH_FILTER_MAC_WILD;
		EFX_POPULATE_OWORD_5(*filter,
				     FRF_CZ_TMFT_TXQ_ID, spec->dmaq_id,
				     FRF_CZ_TMFT_WILDCARD_MATCH, is_wild,
				     FRF_CZ_TMFT_SRC_MAC_HI, spec->data[2],
				     FRF_CZ_TMFT_SRC_MAC_LO, spec->data[1],
				     FRF_CZ_TMFT_VLAN_ID, spec->data[0]);
		data3 = is_wild | spec->dmaq_id << 1;
		अवरोध;
	पूर्ण

	शेष:
		BUG();
	पूर्ण

	वापस spec->data[0] ^ spec->data[1] ^ spec->data[2] ^ data3;
पूर्ण

अटल bool efx_farch_filter_equal(स्थिर काष्ठा efx_farch_filter_spec *left,
				   स्थिर काष्ठा efx_farch_filter_spec *right)
अणु
	अगर (left->type != right->type ||
	    स_भेद(left->data, right->data, माप(left->data)))
		वापस false;

	अगर (left->flags & EFX_FILTER_FLAG_TX &&
	    left->dmaq_id != right->dmaq_id)
		वापस false;

	वापस true;
पूर्ण

/*
 * Conकाष्ठा/deस्थिरruct बाह्यal filter IDs.  At least the RX filter
 * IDs must be ordered by matching priority, क्रम RX NFC semantics.
 *
 * Deस्थिरruction needs to be robust against invalid IDs so that
 * efx_filter_हटाओ_id_safe() and efx_filter_get_filter_safe() can
 * accept user-provided IDs.
 */

#घोषणा EFX_FARCH_FILTER_MATCH_PRI_COUNT	5

अटल स्थिर u8 efx_farch_filter_type_match_pri[EFX_FARCH_FILTER_TYPE_COUNT] = अणु
	[EFX_FARCH_FILTER_TCP_FULL]	= 0,
	[EFX_FARCH_FILTER_UDP_FULL]	= 0,
	[EFX_FARCH_FILTER_TCP_WILD]	= 1,
	[EFX_FARCH_FILTER_UDP_WILD]	= 1,
	[EFX_FARCH_FILTER_MAC_FULL]	= 2,
	[EFX_FARCH_FILTER_MAC_WILD]	= 3,
	[EFX_FARCH_FILTER_UC_DEF]	= 4,
	[EFX_FARCH_FILTER_MC_DEF]	= 4,
पूर्ण;

अटल स्थिर क्रमागत efx_farch_filter_table_id efx_farch_filter_range_table[] = अणु
	EFX_FARCH_FILTER_TABLE_RX_IP,	/* RX match pri 0 */
	EFX_FARCH_FILTER_TABLE_RX_IP,
	EFX_FARCH_FILTER_TABLE_RX_MAC,
	EFX_FARCH_FILTER_TABLE_RX_MAC,
	EFX_FARCH_FILTER_TABLE_RX_DEF,	/* RX match pri 4 */
	EFX_FARCH_FILTER_TABLE_TX_MAC,	/* TX match pri 0 */
	EFX_FARCH_FILTER_TABLE_TX_MAC,	/* TX match pri 1 */
पूर्ण;

#घोषणा EFX_FARCH_FILTER_INDEX_WIDTH 13
#घोषणा EFX_FARCH_FILTER_INDEX_MASK ((1 << EFX_FARCH_FILTER_INDEX_WIDTH) - 1)

अटल अंतरभूत u32
efx_farch_filter_make_id(स्थिर काष्ठा efx_farch_filter_spec *spec,
			 अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक range;

	range = efx_farch_filter_type_match_pri[spec->type];
	अगर (!(spec->flags & EFX_FILTER_FLAG_RX))
		range += EFX_FARCH_FILTER_MATCH_PRI_COUNT;

	वापस range << EFX_FARCH_FILTER_INDEX_WIDTH | index;
पूर्ण

अटल अंतरभूत क्रमागत efx_farch_filter_table_id
efx_farch_filter_id_table_id(u32 id)
अणु
	अचिन्हित पूर्णांक range = id >> EFX_FARCH_FILTER_INDEX_WIDTH;

	अगर (range < ARRAY_SIZE(efx_farch_filter_range_table))
		वापस efx_farch_filter_range_table[range];
	अन्यथा
		वापस EFX_FARCH_FILTER_TABLE_COUNT; /* invalid */
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक efx_farch_filter_id_index(u32 id)
अणु
	वापस id & EFX_FARCH_FILTER_INDEX_MASK;
पूर्ण

u32 efx_farch_filter_get_rx_id_limit(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	अचिन्हित पूर्णांक range = EFX_FARCH_FILTER_MATCH_PRI_COUNT - 1;
	क्रमागत efx_farch_filter_table_id table_id;

	करो अणु
		table_id = efx_farch_filter_range_table[range];
		अगर (state->table[table_id].size != 0)
			वापस range << EFX_FARCH_FILTER_INDEX_WIDTH |
				state->table[table_id].size;
	पूर्ण जबतक (range--);

	वापस 0;
पूर्ण

s32 efx_farch_filter_insert(काष्ठा efx_nic *efx,
			    काष्ठा efx_filter_spec *gen_spec,
			    bool replace_equal)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	काष्ठा efx_farch_filter_table *table;
	काष्ठा efx_farch_filter_spec spec;
	efx_oword_t filter;
	पूर्णांक rep_index, ins_index;
	अचिन्हित पूर्णांक depth = 0;
	पूर्णांक rc;

	rc = efx_farch_filter_from_gen_spec(&spec, gen_spec);
	अगर (rc)
		वापस rc;

	करोwn_ग_लिखो(&state->lock);

	table = &state->table[efx_farch_filter_spec_table_id(&spec)];
	अगर (table->size == 0) अणु
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "%s: type %d search_limit=%d", __func__, spec.type,
		   table->search_limit[spec.type]);

	अगर (table->id == EFX_FARCH_FILTER_TABLE_RX_DEF) अणु
		/* One filter spec per type */
		BUILD_BUG_ON(EFX_FARCH_FILTER_INDEX_UC_DEF != 0);
		BUILD_BUG_ON(EFX_FARCH_FILTER_INDEX_MC_DEF !=
			     EFX_FARCH_FILTER_MC_DEF - EFX_FARCH_FILTER_UC_DEF);
		rep_index = spec.type - EFX_FARCH_FILTER_UC_DEF;
		ins_index = rep_index;
	पूर्ण अन्यथा अणु
		/* Search concurrently क्रम
		 * (1) a filter to be replaced (rep_index): any filter
		 *     with the same match values, up to the current
		 *     search depth क्रम this type, and
		 * (2) the insertion poपूर्णांक (ins_index): (1) or any
		 *     मुक्त slot beक्रमe it or up to the maximum search
		 *     depth क्रम this priority
		 * We fail अगर we cannot find (2).
		 *
		 * We can stop once either
		 * (a) we find (1), in which हाल we have definitely
		 *     found (2) as well; or
		 * (b) we have searched exhaustively क्रम (1), and have
		 *     either found (2) or searched exhaustively क्रम it
		 */
		u32 key = efx_farch_filter_build(&filter, &spec);
		अचिन्हित पूर्णांक hash = efx_farch_filter_hash(key);
		अचिन्हित पूर्णांक incr = efx_farch_filter_increment(key);
		अचिन्हित पूर्णांक max_rep_depth = table->search_limit[spec.type];
		अचिन्हित पूर्णांक max_ins_depth =
			spec.priority <= EFX_FILTER_PRI_HINT ?
			EFX_FARCH_FILTER_CTL_SRCH_Hपूर्णांक_उच्च :
			EFX_FARCH_FILTER_CTL_SRCH_MAX;
		अचिन्हित पूर्णांक i = hash & (table->size - 1);

		ins_index = -1;
		depth = 1;

		क्रम (;;) अणु
			अगर (!test_bit(i, table->used_biपंचांगap)) अणु
				अगर (ins_index < 0)
					ins_index = i;
			पूर्ण अन्यथा अगर (efx_farch_filter_equal(&spec,
							  &table->spec[i])) अणु
				/* Case (a) */
				अगर (ins_index < 0)
					ins_index = i;
				rep_index = i;
				अवरोध;
			पूर्ण

			अगर (depth >= max_rep_depth &&
			    (ins_index >= 0 || depth >= max_ins_depth)) अणु
				/* Case (b) */
				अगर (ins_index < 0) अणु
					rc = -EBUSY;
					जाओ out_unlock;
				पूर्ण
				rep_index = -1;
				अवरोध;
			पूर्ण

			i = (i + incr) & (table->size - 1);
			++depth;
		पूर्ण
	पूर्ण

	/* If we found a filter to be replaced, check whether we
	 * should करो so
	 */
	अगर (rep_index >= 0) अणु
		काष्ठा efx_farch_filter_spec *saved_spec =
			&table->spec[rep_index];

		अगर (spec.priority == saved_spec->priority && !replace_equal) अणु
			rc = -EEXIST;
			जाओ out_unlock;
		पूर्ण
		अगर (spec.priority < saved_spec->priority) अणु
			rc = -EPERM;
			जाओ out_unlock;
		पूर्ण
		अगर (saved_spec->priority == EFX_FILTER_PRI_AUTO ||
		    saved_spec->flags & EFX_FILTER_FLAG_RX_OVER_AUTO)
			spec.flags |= EFX_FILTER_FLAG_RX_OVER_AUTO;
	पूर्ण

	/* Insert the filter */
	अगर (ins_index != rep_index) अणु
		__set_bit(ins_index, table->used_biपंचांगap);
		++table->used;
	पूर्ण
	table->spec[ins_index] = spec;

	अगर (table->id == EFX_FARCH_FILTER_TABLE_RX_DEF) अणु
		efx_farch_filter_push_rx_config(efx);
	पूर्ण अन्यथा अणु
		अगर (table->search_limit[spec.type] < depth) अणु
			table->search_limit[spec.type] = depth;
			अगर (spec.flags & EFX_FILTER_FLAG_TX)
				efx_farch_filter_push_tx_limits(efx);
			अन्यथा
				efx_farch_filter_push_rx_config(efx);
		पूर्ण

		efx_ग_लिखोo(efx, &filter,
			   table->offset + table->step * ins_index);

		/* If we were able to replace a filter by inserting
		 * at a lower depth, clear the replaced filter
		 */
		अगर (ins_index != rep_index && rep_index >= 0)
			efx_farch_filter_table_clear_entry(efx, table,
							   rep_index);
	पूर्ण

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "%s: filter type %d index %d rxq %u set",
		   __func__, spec.type, ins_index, spec.dmaq_id);
	rc = efx_farch_filter_make_id(&spec, ins_index);

out_unlock:
	up_ग_लिखो(&state->lock);
	वापस rc;
पूर्ण

अटल व्योम
efx_farch_filter_table_clear_entry(काष्ठा efx_nic *efx,
				   काष्ठा efx_farch_filter_table *table,
				   अचिन्हित पूर्णांक filter_idx)
अणु
	अटल efx_oword_t filter;

	EFX_WARN_ON_PARANOID(!test_bit(filter_idx, table->used_biपंचांगap));
	BUG_ON(table->offset == 0); /* can't clear MAC शेष filters */

	__clear_bit(filter_idx, table->used_biपंचांगap);
	--table->used;
	स_रखो(&table->spec[filter_idx], 0, माप(table->spec[0]));

	efx_ग_लिखोo(efx, &filter, table->offset + table->step * filter_idx);

	/* If this filter required a greater search depth than
	 * any other, the search limit क्रम its type can now be
	 * decreased.  However, it is hard to determine that
	 * unless the table has become completely empty - in
	 * which हाल, all its search limits can be set to 0.
	 */
	अगर (unlikely(table->used == 0)) अणु
		स_रखो(table->search_limit, 0, माप(table->search_limit));
		अगर (table->id == EFX_FARCH_FILTER_TABLE_TX_MAC)
			efx_farch_filter_push_tx_limits(efx);
		अन्यथा
			efx_farch_filter_push_rx_config(efx);
	पूर्ण
पूर्ण

अटल पूर्णांक efx_farch_filter_हटाओ(काष्ठा efx_nic *efx,
				   काष्ठा efx_farch_filter_table *table,
				   अचिन्हित पूर्णांक filter_idx,
				   क्रमागत efx_filter_priority priority)
अणु
	काष्ठा efx_farch_filter_spec *spec = &table->spec[filter_idx];

	अगर (!test_bit(filter_idx, table->used_biपंचांगap) ||
	    spec->priority != priority)
		वापस -ENOENT;

	अगर (spec->flags & EFX_FILTER_FLAG_RX_OVER_AUTO) अणु
		efx_farch_filter_init_rx_स्वतः(efx, spec);
		efx_farch_filter_push_rx_config(efx);
	पूर्ण अन्यथा अणु
		efx_farch_filter_table_clear_entry(efx, table, filter_idx);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efx_farch_filter_हटाओ_safe(काष्ठा efx_nic *efx,
				 क्रमागत efx_filter_priority priority,
				 u32 filter_id)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;
	काष्ठा efx_farch_filter_table *table;
	अचिन्हित पूर्णांक filter_idx;
	पूर्णांक rc;

	table_id = efx_farch_filter_id_table_id(filter_id);
	अगर ((अचिन्हित पूर्णांक)table_id >= EFX_FARCH_FILTER_TABLE_COUNT)
		वापस -ENOENT;
	table = &state->table[table_id];

	filter_idx = efx_farch_filter_id_index(filter_id);
	अगर (filter_idx >= table->size)
		वापस -ENOENT;
	करोwn_ग_लिखो(&state->lock);

	rc = efx_farch_filter_हटाओ(efx, table, filter_idx, priority);
	up_ग_लिखो(&state->lock);

	वापस rc;
पूर्ण

पूर्णांक efx_farch_filter_get_safe(काष्ठा efx_nic *efx,
			      क्रमागत efx_filter_priority priority,
			      u32 filter_id, काष्ठा efx_filter_spec *spec_buf)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;
	काष्ठा efx_farch_filter_table *table;
	काष्ठा efx_farch_filter_spec *spec;
	अचिन्हित पूर्णांक filter_idx;
	पूर्णांक rc = -ENOENT;

	करोwn_पढ़ो(&state->lock);

	table_id = efx_farch_filter_id_table_id(filter_id);
	अगर ((अचिन्हित पूर्णांक)table_id >= EFX_FARCH_FILTER_TABLE_COUNT)
		जाओ out_unlock;
	table = &state->table[table_id];

	filter_idx = efx_farch_filter_id_index(filter_id);
	अगर (filter_idx >= table->size)
		जाओ out_unlock;
	spec = &table->spec[filter_idx];

	अगर (test_bit(filter_idx, table->used_biपंचांगap) &&
	    spec->priority == priority) अणु
		efx_farch_filter_to_gen_spec(spec_buf, spec);
		rc = 0;
	पूर्ण

out_unlock:
	up_पढ़ो(&state->lock);
	वापस rc;
पूर्ण

अटल व्योम
efx_farch_filter_table_clear(काष्ठा efx_nic *efx,
			     क्रमागत efx_farch_filter_table_id table_id,
			     क्रमागत efx_filter_priority priority)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	काष्ठा efx_farch_filter_table *table = &state->table[table_id];
	अचिन्हित पूर्णांक filter_idx;

	करोwn_ग_लिखो(&state->lock);
	क्रम (filter_idx = 0; filter_idx < table->size; ++filter_idx) अणु
		अगर (table->spec[filter_idx].priority != EFX_FILTER_PRI_AUTO)
			efx_farch_filter_हटाओ(efx, table,
						filter_idx, priority);
	पूर्ण
	up_ग_लिखो(&state->lock);
पूर्ण

पूर्णांक efx_farch_filter_clear_rx(काष्ठा efx_nic *efx,
			       क्रमागत efx_filter_priority priority)
अणु
	efx_farch_filter_table_clear(efx, EFX_FARCH_FILTER_TABLE_RX_IP,
				     priority);
	efx_farch_filter_table_clear(efx, EFX_FARCH_FILTER_TABLE_RX_MAC,
				     priority);
	efx_farch_filter_table_clear(efx, EFX_FARCH_FILTER_TABLE_RX_DEF,
				     priority);
	वापस 0;
पूर्ण

u32 efx_farch_filter_count_rx_used(काष्ठा efx_nic *efx,
				   क्रमागत efx_filter_priority priority)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;
	काष्ठा efx_farch_filter_table *table;
	अचिन्हित पूर्णांक filter_idx;
	u32 count = 0;

	करोwn_पढ़ो(&state->lock);

	क्रम (table_id = EFX_FARCH_FILTER_TABLE_RX_IP;
	     table_id <= EFX_FARCH_FILTER_TABLE_RX_DEF;
	     table_id++) अणु
		table = &state->table[table_id];
		क्रम (filter_idx = 0; filter_idx < table->size; filter_idx++) अणु
			अगर (test_bit(filter_idx, table->used_biपंचांगap) &&
			    table->spec[filter_idx].priority == priority)
				++count;
		पूर्ण
	पूर्ण

	up_पढ़ो(&state->lock);

	वापस count;
पूर्ण

s32 efx_farch_filter_get_rx_ids(काष्ठा efx_nic *efx,
				क्रमागत efx_filter_priority priority,
				u32 *buf, u32 size)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;
	काष्ठा efx_farch_filter_table *table;
	अचिन्हित पूर्णांक filter_idx;
	s32 count = 0;

	करोwn_पढ़ो(&state->lock);

	क्रम (table_id = EFX_FARCH_FILTER_TABLE_RX_IP;
	     table_id <= EFX_FARCH_FILTER_TABLE_RX_DEF;
	     table_id++) अणु
		table = &state->table[table_id];
		क्रम (filter_idx = 0; filter_idx < table->size; filter_idx++) अणु
			अगर (test_bit(filter_idx, table->used_biपंचांगap) &&
			    table->spec[filter_idx].priority == priority) अणु
				अगर (count == size) अणु
					count = -EMSGSIZE;
					जाओ out;
				पूर्ण
				buf[count++] = efx_farch_filter_make_id(
					&table->spec[filter_idx], filter_idx);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	up_पढ़ो(&state->lock);

	वापस count;
पूर्ण

/* Restore filter stater after reset */
व्योम efx_farch_filter_table_restore(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;
	काष्ठा efx_farch_filter_table *table;
	efx_oword_t filter;
	अचिन्हित पूर्णांक filter_idx;

	करोwn_ग_लिखो(&state->lock);

	क्रम (table_id = 0; table_id < EFX_FARCH_FILTER_TABLE_COUNT; table_id++) अणु
		table = &state->table[table_id];

		/* Check whether this is a regular रेजिस्टर table */
		अगर (table->step == 0)
			जारी;

		क्रम (filter_idx = 0; filter_idx < table->size; filter_idx++) अणु
			अगर (!test_bit(filter_idx, table->used_biपंचांगap))
				जारी;
			efx_farch_filter_build(&filter, &table->spec[filter_idx]);
			efx_ग_लिखोo(efx, &filter,
				   table->offset + table->step * filter_idx);
		पूर्ण
	पूर्ण

	efx_farch_filter_push_rx_config(efx);
	efx_farch_filter_push_tx_limits(efx);

	up_ग_लिखो(&state->lock);
पूर्ण

व्योम efx_farch_filter_table_हटाओ(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;

	क्रम (table_id = 0; table_id < EFX_FARCH_FILTER_TABLE_COUNT; table_id++) अणु
		kमुक्त(state->table[table_id].used_biपंचांगap);
		vमुक्त(state->table[table_id].spec);
	पूर्ण
	kमुक्त(state);
पूर्ण

पूर्णांक efx_farch_filter_table_probe(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state;
	काष्ठा efx_farch_filter_table *table;
	अचिन्हित table_id;

	state = kzalloc(माप(काष्ठा efx_farch_filter_state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;
	efx->filter_state = state;
	init_rwsem(&state->lock);

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_IP];
	table->id = EFX_FARCH_FILTER_TABLE_RX_IP;
	table->offset = FR_BZ_RX_FILTER_TBL0;
	table->size = FR_BZ_RX_FILTER_TBL0_ROWS;
	table->step = FR_BZ_RX_FILTER_TBL0_STEP;

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_MAC];
	table->id = EFX_FARCH_FILTER_TABLE_RX_MAC;
	table->offset = FR_CZ_RX_MAC_FILTER_TBL0;
	table->size = FR_CZ_RX_MAC_FILTER_TBL0_ROWS;
	table->step = FR_CZ_RX_MAC_FILTER_TBL0_STEP;

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_DEF];
	table->id = EFX_FARCH_FILTER_TABLE_RX_DEF;
	table->size = EFX_FARCH_FILTER_SIZE_RX_DEF;

	table = &state->table[EFX_FARCH_FILTER_TABLE_TX_MAC];
	table->id = EFX_FARCH_FILTER_TABLE_TX_MAC;
	table->offset = FR_CZ_TX_MAC_FILTER_TBL0;
	table->size = FR_CZ_TX_MAC_FILTER_TBL0_ROWS;
	table->step = FR_CZ_TX_MAC_FILTER_TBL0_STEP;

	क्रम (table_id = 0; table_id < EFX_FARCH_FILTER_TABLE_COUNT; table_id++) अणु
		table = &state->table[table_id];
		अगर (table->size == 0)
			जारी;
		table->used_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(table->size),
					     माप(अचिन्हित दीर्घ),
					     GFP_KERNEL);
		अगर (!table->used_biपंचांगap)
			जाओ fail;
		table->spec = vzalloc(array_size(माप(*table->spec),
						 table->size));
		अगर (!table->spec)
			जाओ fail;
	पूर्ण

	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_DEF];
	अगर (table->size) अणु
		/* RX शेष filters must always exist */
		काष्ठा efx_farch_filter_spec *spec;
		अचिन्हित i;

		क्रम (i = 0; i < EFX_FARCH_FILTER_SIZE_RX_DEF; i++) अणु
			spec = &table->spec[i];
			spec->type = EFX_FARCH_FILTER_UC_DEF + i;
			efx_farch_filter_init_rx_स्वतः(efx, spec);
			__set_bit(i, table->used_biपंचांगap);
		पूर्ण
	पूर्ण

	efx_farch_filter_push_rx_config(efx);

	वापस 0;

fail:
	efx_farch_filter_table_हटाओ(efx);
	वापस -ENOMEM;
पूर्ण

/* Update scatter enable flags क्रम filters poपूर्णांकing to our own RX queues */
व्योम efx_farch_filter_update_rx_scatter(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	क्रमागत efx_farch_filter_table_id table_id;
	काष्ठा efx_farch_filter_table *table;
	efx_oword_t filter;
	अचिन्हित पूर्णांक filter_idx;

	करोwn_ग_लिखो(&state->lock);

	क्रम (table_id = EFX_FARCH_FILTER_TABLE_RX_IP;
	     table_id <= EFX_FARCH_FILTER_TABLE_RX_DEF;
	     table_id++) अणु
		table = &state->table[table_id];

		क्रम (filter_idx = 0; filter_idx < table->size; filter_idx++) अणु
			अगर (!test_bit(filter_idx, table->used_biपंचांगap) ||
			    table->spec[filter_idx].dmaq_id >=
			    efx->n_rx_channels)
				जारी;

			अगर (efx->rx_scatter)
				table->spec[filter_idx].flags |=
					EFX_FILTER_FLAG_RX_SCATTER;
			अन्यथा
				table->spec[filter_idx].flags &=
					~EFX_FILTER_FLAG_RX_SCATTER;

			अगर (table_id == EFX_FARCH_FILTER_TABLE_RX_DEF)
				/* Pushed by efx_farch_filter_push_rx_config() */
				जारी;

			efx_farch_filter_build(&filter, &table->spec[filter_idx]);
			efx_ग_लिखोo(efx, &filter,
				   table->offset + table->step * filter_idx);
		पूर्ण
	पूर्ण

	efx_farch_filter_push_rx_config(efx);

	up_ग_लिखो(&state->lock);
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL

bool efx_farch_filter_rfs_expire_one(काष्ठा efx_nic *efx, u32 flow_id,
				     अचिन्हित पूर्णांक index)
अणु
	काष्ठा efx_farch_filter_state *state = efx->filter_state;
	काष्ठा efx_farch_filter_table *table;
	bool ret = false, क्रमce = false;
	u16 arfs_id;

	करोwn_ग_लिखो(&state->lock);
	spin_lock_bh(&efx->rps_hash_lock);
	table = &state->table[EFX_FARCH_FILTER_TABLE_RX_IP];
	अगर (test_bit(index, table->used_biपंचांगap) &&
	    table->spec[index].priority == EFX_FILTER_PRI_HINT) अणु
		काष्ठा efx_arfs_rule *rule = शून्य;
		काष्ठा efx_filter_spec spec;

		efx_farch_filter_to_gen_spec(&spec, &table->spec[index]);
		अगर (!efx->rps_hash_table) अणु
			/* In the असलence of the table, we always वापसed 0 to
			 * ARFS, so use the same to query it.
			 */
			arfs_id = 0;
		पूर्ण अन्यथा अणु
			rule = efx_rps_hash_find(efx, &spec);
			अगर (!rule) अणु
				/* ARFS table करोesn't know of this filter, हटाओ it */
				क्रमce = true;
			पूर्ण अन्यथा अणु
				arfs_id = rule->arfs_id;
				अगर (!efx_rps_check_rule(rule, index, &क्रमce))
					जाओ out_unlock;
			पूर्ण
		पूर्ण
		अगर (क्रमce || rps_may_expire_flow(efx->net_dev, spec.dmaq_id,
						 flow_id, arfs_id)) अणु
			अगर (rule)
				rule->filter_id = EFX_ARFS_FILTER_ID_REMOVING;
			efx_rps_hash_del(efx, &spec);
			efx_farch_filter_table_clear_entry(efx, table, index);
			ret = true;
		पूर्ण
	पूर्ण
out_unlock:
	spin_unlock_bh(&efx->rps_hash_lock);
	up_ग_लिखो(&state->lock);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

व्योम efx_farch_filter_sync_rx_mode(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा netdev_hw_addr *ha;
	जोड़ efx_multicast_hash *mc_hash = &efx->multicast_hash;
	u32 crc;
	पूर्णांक bit;

	अगर (!efx_dev_रेजिस्टरed(efx))
		वापस;

	netअगर_addr_lock_bh(net_dev);

	efx->unicast_filter = !(net_dev->flags & IFF_PROMISC);

	/* Build multicast hash table */
	अगर (net_dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) अणु
		स_रखो(mc_hash, 0xff, माप(*mc_hash));
	पूर्ण अन्यथा अणु
		स_रखो(mc_hash, 0x00, माप(*mc_hash));
		netdev_क्रम_each_mc_addr(ha, net_dev) अणु
			crc = ether_crc_le(ETH_ALEN, ha->addr);
			bit = crc & (EFX_MCAST_HASH_ENTRIES - 1);
			__set_bit_le(bit, mc_hash);
		पूर्ण

		/* Broadcast packets go through the multicast hash filter.
		 * ether_crc_le() of the broadcast address is 0xbe2612ff
		 * so we always add bit 0xff to the mask.
		 */
		__set_bit_le(0xff, mc_hash);
	पूर्ण

	netअगर_addr_unlock_bh(net_dev);
पूर्ण
