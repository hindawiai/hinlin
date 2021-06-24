<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright (C) 2020 NVIDIA CORPORATION.

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/spi/spi.h>

#घोषणा QSPI_COMMAND1				0x000
#घोषणा QSPI_BIT_LENGTH(x)			(((x) & 0x1f) << 0)
#घोषणा QSPI_PACKED				BIT(5)
#घोषणा QSPI_INTERFACE_WIDTH_MASK		(0x03 << 7)
#घोषणा QSPI_INTERFACE_WIDTH(x)			(((x) & 0x03) << 7)
#घोषणा QSPI_INTERFACE_WIDTH_SINGLE		QSPI_INTERFACE_WIDTH(0)
#घोषणा QSPI_INTERFACE_WIDTH_DUAL		QSPI_INTERFACE_WIDTH(1)
#घोषणा QSPI_INTERFACE_WIDTH_QUAD		QSPI_INTERFACE_WIDTH(2)
#घोषणा QSPI_SDR_DDR_SEL			BIT(9)
#घोषणा QSPI_TX_EN				BIT(11)
#घोषणा QSPI_RX_EN				BIT(12)
#घोषणा QSPI_CS_SW_VAL				BIT(20)
#घोषणा QSPI_CS_SW_HW				BIT(21)
#घोषणा QSPI_CONTROL_MODE_0			(0 << 28)
#घोषणा QSPI_CONTROL_MODE_3			(3 << 28)
#घोषणा QSPI_CONTROL_MODE_MASK			(3 << 28)
#घोषणा QSPI_M_S				BIT(30)
#घोषणा QSPI_PIO				BIT(31)

#घोषणा QSPI_COMMAND2				0x004
#घोषणा QSPI_TX_TAP_DELAY(x)			(((x) & 0x3f) << 10)
#घोषणा QSPI_RX_TAP_DELAY(x)			(((x) & 0xff) << 0)

#घोषणा QSPI_CS_TIMING1				0x008
#घोषणा QSPI_SETUP_HOLD(setup, hold)		(((setup) << 4) | (hold))

#घोषणा QSPI_CS_TIMING2				0x00c
#घोषणा CYCLES_BETWEEN_PACKETS_0(x)		(((x) & 0x1f) << 0)
#घोषणा CS_ACTIVE_BETWEEN_PACKETS_0		BIT(5)

#घोषणा QSPI_TRANS_STATUS			0x010
#घोषणा QSPI_BLK_CNT(val)			(((val) >> 0) & 0xffff)
#घोषणा QSPI_RDY				BIT(30)

#घोषणा QSPI_FIFO_STATUS			0x014
#घोषणा QSPI_RX_FIFO_EMPTY			BIT(0)
#घोषणा QSPI_RX_FIFO_FULL			BIT(1)
#घोषणा QSPI_TX_FIFO_EMPTY			BIT(2)
#घोषणा QSPI_TX_FIFO_FULL			BIT(3)
#घोषणा QSPI_RX_FIFO_UNF			BIT(4)
#घोषणा QSPI_RX_FIFO_OVF			BIT(5)
#घोषणा QSPI_TX_FIFO_UNF			BIT(6)
#घोषणा QSPI_TX_FIFO_OVF			BIT(7)
#घोषणा QSPI_ERR				BIT(8)
#घोषणा QSPI_TX_FIFO_FLUSH			BIT(14)
#घोषणा QSPI_RX_FIFO_FLUSH			BIT(15)
#घोषणा QSPI_TX_FIFO_EMPTY_COUNT(val)		(((val) >> 16) & 0x7f)
#घोषणा QSPI_RX_FIFO_FULL_COUNT(val)		(((val) >> 23) & 0x7f)

#घोषणा QSPI_FIFO_ERROR				(QSPI_RX_FIFO_UNF | \
						 QSPI_RX_FIFO_OVF | \
						 QSPI_TX_FIFO_UNF | \
						 QSPI_TX_FIFO_OVF)
#घोषणा QSPI_FIFO_EMPTY				(QSPI_RX_FIFO_EMPTY | \
						 QSPI_TX_FIFO_EMPTY)

#घोषणा QSPI_TX_DATA				0x018
#घोषणा QSPI_RX_DATA				0x01c

#घोषणा QSPI_DMA_CTL				0x020
#घोषणा QSPI_TX_TRIG(n)				(((n) & 0x3) << 15)
#घोषणा QSPI_TX_TRIG_1				QSPI_TX_TRIG(0)
#घोषणा QSPI_TX_TRIG_4				QSPI_TX_TRIG(1)
#घोषणा QSPI_TX_TRIG_8				QSPI_TX_TRIG(2)
#घोषणा QSPI_TX_TRIG_16				QSPI_TX_TRIG(3)

#घोषणा QSPI_RX_TRIG(n)				(((n) & 0x3) << 19)
#घोषणा QSPI_RX_TRIG_1				QSPI_RX_TRIG(0)
#घोषणा QSPI_RX_TRIG_4				QSPI_RX_TRIG(1)
#घोषणा QSPI_RX_TRIG_8				QSPI_RX_TRIG(2)
#घोषणा QSPI_RX_TRIG_16				QSPI_RX_TRIG(3)

#घोषणा QSPI_DMA_EN				BIT(31)

#घोषणा QSPI_DMA_BLK				0x024
#घोषणा QSPI_DMA_BLK_SET(x)			(((x) & 0xffff) << 0)

#घोषणा QSPI_TX_FIFO				0x108
#घोषणा QSPI_RX_FIFO				0x188

#घोषणा QSPI_FIFO_DEPTH				64

#घोषणा QSPI_INTR_MASK				0x18c
#घोषणा QSPI_INTR_RX_FIFO_UNF_MASK		BIT(25)
#घोषणा QSPI_INTR_RX_FIFO_OVF_MASK		BIT(26)
#घोषणा QSPI_INTR_TX_FIFO_UNF_MASK		BIT(27)
#घोषणा QSPI_INTR_TX_FIFO_OVF_MASK		BIT(28)
#घोषणा QSPI_INTR_RDY_MASK			BIT(29)
#घोषणा QSPI_INTR_RX_TX_FIFO_ERR		(QSPI_INTR_RX_FIFO_UNF_MASK | \
						 QSPI_INTR_RX_FIFO_OVF_MASK | \
						 QSPI_INTR_TX_FIFO_UNF_MASK | \
						 QSPI_INTR_TX_FIFO_OVF_MASK)

#घोषणा QSPI_MISC_REG                           0x194
#घोषणा QSPI_NUM_DUMMY_CYCLE(x)			(((x) & 0xff) << 0)
#घोषणा QSPI_DUMMY_CYCLES_MAX			0xff

#घोषणा DATA_सूची_TX				BIT(0)
#घोषणा DATA_सूची_RX				BIT(1)

#घोषणा QSPI_DMA_TIMEOUT			(msecs_to_jअगरfies(1000))
#घोषणा DEFAULT_QSPI_DMA_BUF_LEN		(64 * 1024)

काष्ठा tegra_qspi_client_data अणु
	पूर्णांक tx_clk_tap_delay;
	पूर्णांक rx_clk_tap_delay;
पूर्ण;

काष्ठा tegra_qspi अणु
	काष्ठा device				*dev;
	काष्ठा spi_master			*master;
	/* lock to protect data accessed by irq */
	spinlock_t				lock;

	काष्ठा clk				*clk;
	काष्ठा reset_control			*rst;
	व्योम __iomem				*base;
	phys_addr_t				phys;
	अचिन्हित पूर्णांक				irq;

	u32					cur_speed;
	अचिन्हित पूर्णांक				cur_pos;
	अचिन्हित पूर्णांक				words_per_32bit;
	अचिन्हित पूर्णांक				bytes_per_word;
	अचिन्हित पूर्णांक				curr_dma_words;
	अचिन्हित पूर्णांक				cur_direction;

	अचिन्हित पूर्णांक				cur_rx_pos;
	अचिन्हित पूर्णांक				cur_tx_pos;

	अचिन्हित पूर्णांक				dma_buf_size;
	अचिन्हित पूर्णांक				max_buf_size;
	bool					is_curr_dma_xfer;

	काष्ठा completion			rx_dma_complete;
	काष्ठा completion			tx_dma_complete;

	u32					tx_status;
	u32					rx_status;
	u32					status_reg;
	bool					is_packed;
	bool					use_dma;

	u32					command1_reg;
	u32					dma_control_reg;
	u32					def_command1_reg;
	u32					def_command2_reg;
	u32					spi_cs_timing1;
	u32					spi_cs_timing2;
	u8					dummy_cycles;

	काष्ठा completion			xfer_completion;
	काष्ठा spi_transfer			*curr_xfer;

	काष्ठा dma_chan				*rx_dma_chan;
	u32					*rx_dma_buf;
	dma_addr_t				rx_dma_phys;
	काष्ठा dma_async_tx_descriptor		*rx_dma_desc;

	काष्ठा dma_chan				*tx_dma_chan;
	u32					*tx_dma_buf;
	dma_addr_t				tx_dma_phys;
	काष्ठा dma_async_tx_descriptor		*tx_dma_desc;
पूर्ण;

अटल अंतरभूत u32 tegra_qspi_पढ़ोl(काष्ठा tegra_qspi *tqspi, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(tqspi->base + offset);
पूर्ण

अटल अंतरभूत व्योम tegra_qspi_ग_लिखोl(काष्ठा tegra_qspi *tqspi, u32 value, अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, tqspi->base + offset);

	/* पढ़ो back रेजिस्टर to make sure that रेजिस्टर ग_लिखोs completed */
	अगर (offset != QSPI_TX_FIFO)
		पढ़ोl(tqspi->base + QSPI_COMMAND1);
पूर्ण

अटल व्योम tegra_qspi_mask_clear_irq(काष्ठा tegra_qspi *tqspi)
अणु
	u32 value;

	/* ग_लिखो 1 to clear status रेजिस्टर */
	value = tegra_qspi_पढ़ोl(tqspi, QSPI_TRANS_STATUS);
	tegra_qspi_ग_लिखोl(tqspi, value, QSPI_TRANS_STATUS);

	value = tegra_qspi_पढ़ोl(tqspi, QSPI_INTR_MASK);
	अगर (!(value & QSPI_INTR_RDY_MASK)) अणु
		value |= (QSPI_INTR_RDY_MASK | QSPI_INTR_RX_TX_FIFO_ERR);
		tegra_qspi_ग_लिखोl(tqspi, value, QSPI_INTR_MASK);
	पूर्ण

	/* clear fअगरo status error अगर any */
	value = tegra_qspi_पढ़ोl(tqspi, QSPI_FIFO_STATUS);
	अगर (value & QSPI_ERR)
		tegra_qspi_ग_लिखोl(tqspi, QSPI_ERR | QSPI_FIFO_ERROR, QSPI_FIFO_STATUS);
पूर्ण

अटल अचिन्हित पूर्णांक
tegra_qspi_calculate_curr_xfer_param(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित पूर्णांक max_word, max_len, total_fअगरo_words;
	अचिन्हित पूर्णांक reमुख्य_len = t->len - tqspi->cur_pos;
	अचिन्हित पूर्णांक bits_per_word = t->bits_per_word;

	tqspi->bytes_per_word = DIV_ROUND_UP(bits_per_word, 8);

	/*
	 * Tegra QSPI controller supports packed or unpacked mode transfers.
	 * Packed mode is used क्रम data transfers using 8, 16, or 32 bits per
	 * word with a minimum transfer of 1 word and क्रम all other transfers
	 * unpacked mode will be used.
	 */

	अगर ((bits_per_word == 8 || bits_per_word == 16 ||
	     bits_per_word == 32) && t->len > 3) अणु
		tqspi->is_packed = true;
		tqspi->words_per_32bit = 32 / bits_per_word;
	पूर्ण अन्यथा अणु
		tqspi->is_packed = false;
		tqspi->words_per_32bit = 1;
	पूर्ण

	अगर (tqspi->is_packed) अणु
		max_len = min(reमुख्य_len, tqspi->max_buf_size);
		tqspi->curr_dma_words = max_len / tqspi->bytes_per_word;
		total_fअगरo_words = (max_len + 3) / 4;
	पूर्ण अन्यथा अणु
		max_word = (reमुख्य_len - 1) / tqspi->bytes_per_word + 1;
		max_word = min(max_word, tqspi->max_buf_size / 4);
		tqspi->curr_dma_words = max_word;
		total_fअगरo_words = max_word;
	पूर्ण

	वापस total_fअगरo_words;
पूर्ण

अटल अचिन्हित पूर्णांक
tegra_qspi_fill_tx_fअगरo_from_client_txbuf(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित पूर्णांक written_words, fअगरo_words_left, count;
	अचिन्हित पूर्णांक len, tx_empty_count, max_n_32bit, i;
	u8 *tx_buf = (u8 *)t->tx_buf + tqspi->cur_tx_pos;
	u32 fअगरo_status;

	fअगरo_status = tegra_qspi_पढ़ोl(tqspi, QSPI_FIFO_STATUS);
	tx_empty_count = QSPI_TX_FIFO_EMPTY_COUNT(fअगरo_status);

	अगर (tqspi->is_packed) अणु
		fअगरo_words_left = tx_empty_count * tqspi->words_per_32bit;
		written_words = min(fअगरo_words_left, tqspi->curr_dma_words);
		len = written_words * tqspi->bytes_per_word;
		max_n_32bit = DIV_ROUND_UP(len, 4);
		क्रम (count = 0; count < max_n_32bit; count++) अणु
			u32 x = 0;

			क्रम (i = 0; (i < 4) && len; i++, len--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegra_qspi_ग_लिखोl(tqspi, x, QSPI_TX_FIFO);
		पूर्ण

		tqspi->cur_tx_pos += written_words * tqspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक ग_लिखो_bytes;
		u8 bytes_per_word = tqspi->bytes_per_word;

		max_n_32bit = min(tqspi->curr_dma_words, tx_empty_count);
		written_words = max_n_32bit;
		len = written_words * tqspi->bytes_per_word;
		अगर (len > t->len - tqspi->cur_pos)
			len = t->len - tqspi->cur_pos;
		ग_लिखो_bytes = len;
		क्रम (count = 0; count < max_n_32bit; count++) अणु
			u32 x = 0;

			क्रम (i = 0; len && (i < bytes_per_word); i++, len--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegra_qspi_ग_लिखोl(tqspi, x, QSPI_TX_FIFO);
		पूर्ण

		tqspi->cur_tx_pos += ग_लिखो_bytes;
	पूर्ण

	वापस written_words;
पूर्ण

अटल अचिन्हित पूर्णांक
tegra_qspi_पढ़ो_rx_fअगरo_to_client_rxbuf(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	u8 *rx_buf = (u8 *)t->rx_buf + tqspi->cur_rx_pos;
	अचिन्हित पूर्णांक len, rx_full_count, count, i;
	अचिन्हित पूर्णांक पढ़ो_words = 0;
	u32 fअगरo_status, x;

	fअगरo_status = tegra_qspi_पढ़ोl(tqspi, QSPI_FIFO_STATUS);
	rx_full_count = QSPI_RX_FIFO_FULL_COUNT(fअगरo_status);
	अगर (tqspi->is_packed) अणु
		len = tqspi->curr_dma_words * tqspi->bytes_per_word;
		क्रम (count = 0; count < rx_full_count; count++) अणु
			x = tegra_qspi_पढ़ोl(tqspi, QSPI_RX_FIFO);

			क्रम (i = 0; len && (i < 4); i++, len--)
				*rx_buf++ = (x >> i * 8) & 0xff;
		पूर्ण

		पढ़ो_words += tqspi->curr_dma_words;
		tqspi->cur_rx_pos += tqspi->curr_dma_words * tqspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;
		u8 bytes_per_word = tqspi->bytes_per_word;
		अचिन्हित पूर्णांक पढ़ो_bytes;

		len = rx_full_count * bytes_per_word;
		अगर (len > t->len - tqspi->cur_pos)
			len = t->len - tqspi->cur_pos;
		पढ़ो_bytes = len;
		क्रम (count = 0; count < rx_full_count; count++) अणु
			x = tegra_qspi_पढ़ोl(tqspi, QSPI_RX_FIFO) & rx_mask;

			क्रम (i = 0; len && (i < bytes_per_word); i++, len--)
				*rx_buf++ = (x >> (i * 8)) & 0xff;
		पूर्ण

		पढ़ो_words += rx_full_count;
		tqspi->cur_rx_pos += पढ़ो_bytes;
	पूर्ण

	वापस पढ़ो_words;
पूर्ण

अटल व्योम
tegra_qspi_copy_client_txbuf_to_qspi_txbuf(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	dma_sync_single_क्रम_cpu(tqspi->dev, tqspi->tx_dma_phys,
				tqspi->dma_buf_size, DMA_TO_DEVICE);

	/*
	 * In packed mode, each word in FIFO may contain multiple packets
	 * based on bits per word. So all bytes in each FIFO word are valid.
	 *
	 * In unpacked mode, each word in FIFO contains single packet and
	 * based on bits per word any reमुख्यing bits in FIFO word will be
	 * ignored by the hardware and are invalid bits.
	 */
	अगर (tqspi->is_packed) अणु
		tqspi->cur_tx_pos += tqspi->curr_dma_words * tqspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		u8 *tx_buf = (u8 *)t->tx_buf + tqspi->cur_tx_pos;
		अचिन्हित पूर्णांक i, count, consume, ग_लिखो_bytes;

		/*
		 * Fill tx_dma_buf to contain single packet in each word based
		 * on bits per word from SPI core tx_buf.
		 */
		consume = tqspi->curr_dma_words * tqspi->bytes_per_word;
		अगर (consume > t->len - tqspi->cur_pos)
			consume = t->len - tqspi->cur_pos;
		ग_लिखो_bytes = consume;
		क्रम (count = 0; count < tqspi->curr_dma_words; count++) अणु
			u32 x = 0;

			क्रम (i = 0; consume && (i < tqspi->bytes_per_word); i++, consume--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tqspi->tx_dma_buf[count] = x;
		पूर्ण

		tqspi->cur_tx_pos += ग_लिखो_bytes;
	पूर्ण

	dma_sync_single_क्रम_device(tqspi->dev, tqspi->tx_dma_phys,
				   tqspi->dma_buf_size, DMA_TO_DEVICE);
पूर्ण

अटल व्योम
tegra_qspi_copy_qspi_rxbuf_to_client_rxbuf(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	dma_sync_single_क्रम_cpu(tqspi->dev, tqspi->rx_dma_phys,
				tqspi->dma_buf_size, DMA_FROM_DEVICE);

	अगर (tqspi->is_packed) अणु
		tqspi->cur_rx_pos += tqspi->curr_dma_words * tqspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर *rx_buf = t->rx_buf + tqspi->cur_rx_pos;
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;
		अचिन्हित पूर्णांक i, count, consume, पढ़ो_bytes;

		/*
		 * Each FIFO word contains single data packet.
		 * Skip invalid bits in each FIFO word based on bits per word
		 * and align bytes जबतक filling in SPI core rx_buf.
		 */
		consume = tqspi->curr_dma_words * tqspi->bytes_per_word;
		अगर (consume > t->len - tqspi->cur_pos)
			consume = t->len - tqspi->cur_pos;
		पढ़ो_bytes = consume;
		क्रम (count = 0; count < tqspi->curr_dma_words; count++) अणु
			u32 x = tqspi->rx_dma_buf[count] & rx_mask;

			क्रम (i = 0; consume && (i < tqspi->bytes_per_word); i++, consume--)
				*rx_buf++ = (x >> (i * 8)) & 0xff;
		पूर्ण

		tqspi->cur_rx_pos += पढ़ो_bytes;
	पूर्ण

	dma_sync_single_क्रम_device(tqspi->dev, tqspi->rx_dma_phys,
				   tqspi->dma_buf_size, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम tegra_qspi_dma_complete(व्योम *args)
अणु
	काष्ठा completion *dma_complete = args;

	complete(dma_complete);
पूर्ण

अटल पूर्णांक tegra_qspi_start_tx_dma(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t, पूर्णांक len)
अणु
	dma_addr_t tx_dma_phys;

	reinit_completion(&tqspi->tx_dma_complete);

	अगर (tqspi->is_packed)
		tx_dma_phys = t->tx_dma;
	अन्यथा
		tx_dma_phys = tqspi->tx_dma_phys;

	tqspi->tx_dma_desc = dmaengine_prep_slave_single(tqspi->tx_dma_chan, tx_dma_phys,
							 len, DMA_MEM_TO_DEV,
							 DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);

	अगर (!tqspi->tx_dma_desc) अणु
		dev_err(tqspi->dev, "Unable to get TX descriptor\n");
		वापस -EIO;
	पूर्ण

	tqspi->tx_dma_desc->callback = tegra_qspi_dma_complete;
	tqspi->tx_dma_desc->callback_param = &tqspi->tx_dma_complete;
	dmaengine_submit(tqspi->tx_dma_desc);
	dma_async_issue_pending(tqspi->tx_dma_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_qspi_start_rx_dma(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t, पूर्णांक len)
अणु
	dma_addr_t rx_dma_phys;

	reinit_completion(&tqspi->rx_dma_complete);

	अगर (tqspi->is_packed)
		rx_dma_phys = t->rx_dma;
	अन्यथा
		rx_dma_phys = tqspi->rx_dma_phys;

	tqspi->rx_dma_desc = dmaengine_prep_slave_single(tqspi->rx_dma_chan, rx_dma_phys,
							 len, DMA_DEV_TO_MEM,
							 DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);

	अगर (!tqspi->rx_dma_desc) अणु
		dev_err(tqspi->dev, "Unable to get RX descriptor\n");
		वापस -EIO;
	पूर्ण

	tqspi->rx_dma_desc->callback = tegra_qspi_dma_complete;
	tqspi->rx_dma_desc->callback_param = &tqspi->rx_dma_complete;
	dmaengine_submit(tqspi->rx_dma_desc);
	dma_async_issue_pending(tqspi->rx_dma_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_qspi_flush_fअगरos(काष्ठा tegra_qspi *tqspi, bool atomic)
अणु
	व्योम __iomem *addr = tqspi->base + QSPI_FIFO_STATUS;
	u32 val;

	val = tegra_qspi_पढ़ोl(tqspi, QSPI_FIFO_STATUS);
	अगर ((val & QSPI_FIFO_EMPTY) == QSPI_FIFO_EMPTY)
		वापस 0;

	val |= QSPI_RX_FIFO_FLUSH | QSPI_TX_FIFO_FLUSH;
	tegra_qspi_ग_लिखोl(tqspi, val, QSPI_FIFO_STATUS);

	अगर (!atomic)
		वापस पढ़ोl_relaxed_poll_समयout(addr, val,
						  (val & QSPI_FIFO_EMPTY) == QSPI_FIFO_EMPTY,
						  1000, 1000000);

	वापस पढ़ोl_relaxed_poll_समयout_atomic(addr, val,
						 (val & QSPI_FIFO_EMPTY) == QSPI_FIFO_EMPTY,
						 1000, 1000000);
पूर्ण

अटल व्योम tegra_qspi_unmask_irq(काष्ठा tegra_qspi *tqspi)
अणु
	u32 पूर्णांकr_mask;

	पूर्णांकr_mask = tegra_qspi_पढ़ोl(tqspi, QSPI_INTR_MASK);
	पूर्णांकr_mask &= ~(QSPI_INTR_RDY_MASK | QSPI_INTR_RX_TX_FIFO_ERR);
	tegra_qspi_ग_लिखोl(tqspi, पूर्णांकr_mask, QSPI_INTR_MASK);
पूर्ण

अटल पूर्णांक tegra_qspi_dma_map_xfer(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	u8 *tx_buf = (u8 *)t->tx_buf + tqspi->cur_tx_pos;
	u8 *rx_buf = (u8 *)t->rx_buf + tqspi->cur_rx_pos;
	अचिन्हित पूर्णांक len;

	len = DIV_ROUND_UP(tqspi->curr_dma_words * tqspi->bytes_per_word, 4) * 4;

	अगर (t->tx_buf) अणु
		t->tx_dma = dma_map_single(tqspi->dev, (व्योम *)tx_buf, len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(tqspi->dev, t->tx_dma))
			वापस -ENOMEM;
	पूर्ण

	अगर (t->rx_buf) अणु
		t->rx_dma = dma_map_single(tqspi->dev, (व्योम *)rx_buf, len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(tqspi->dev, t->rx_dma)) अणु
			dma_unmap_single(tqspi->dev, t->tx_dma, len, DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_qspi_dma_unmap_xfer(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित पूर्णांक len;

	len = DIV_ROUND_UP(tqspi->curr_dma_words * tqspi->bytes_per_word, 4) * 4;

	dma_unmap_single(tqspi->dev, t->tx_dma, len, DMA_TO_DEVICE);
	dma_unmap_single(tqspi->dev, t->rx_dma, len, DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक tegra_qspi_start_dma_based_transfer(काष्ठा tegra_qspi *tqspi, काष्ठा spi_transfer *t)
अणु
	काष्ठा dma_slave_config dma_sconfig = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक len;
	u8 dma_burst;
	पूर्णांक ret = 0;
	u32 val;

	अगर (tqspi->is_packed) अणु
		ret = tegra_qspi_dma_map_xfer(tqspi, t);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	val = QSPI_DMA_BLK_SET(tqspi->curr_dma_words - 1);
	tegra_qspi_ग_लिखोl(tqspi, val, QSPI_DMA_BLK);

	tegra_qspi_unmask_irq(tqspi);

	अगर (tqspi->is_packed)
		len = DIV_ROUND_UP(tqspi->curr_dma_words * tqspi->bytes_per_word, 4) * 4;
	अन्यथा
		len = tqspi->curr_dma_words * 4;

	/* set attention level based on length of transfer */
	val = 0;
	अगर (len & 0xf) अणु
		val |= QSPI_TX_TRIG_1 | QSPI_RX_TRIG_1;
		dma_burst = 1;
	पूर्ण अन्यथा अगर (((len) >> 4) & 0x1) अणु
		val |= QSPI_TX_TRIG_4 | QSPI_RX_TRIG_4;
		dma_burst = 4;
	पूर्ण अन्यथा अणु
		val |= QSPI_TX_TRIG_8 | QSPI_RX_TRIG_8;
		dma_burst = 8;
	पूर्ण

	tegra_qspi_ग_लिखोl(tqspi, val, QSPI_DMA_CTL);
	tqspi->dma_control_reg = val;

	dma_sconfig.device_fc = true;
	अगर (tqspi->cur_direction & DATA_सूची_TX) अणु
		dma_sconfig.dst_addr = tqspi->phys + QSPI_TX_FIFO;
		dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.dst_maxburst = dma_burst;
		ret = dmaengine_slave_config(tqspi->tx_dma_chan, &dma_sconfig);
		अगर (ret < 0) अणु
			dev_err(tqspi->dev, "failed DMA slave config: %d\n", ret);
			वापस ret;
		पूर्ण

		tegra_qspi_copy_client_txbuf_to_qspi_txbuf(tqspi, t);
		ret = tegra_qspi_start_tx_dma(tqspi, t, len);
		अगर (ret < 0) अणु
			dev_err(tqspi->dev, "failed to starting TX DMA: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (tqspi->cur_direction & DATA_सूची_RX) अणु
		dma_sconfig.src_addr = tqspi->phys + QSPI_RX_FIFO;
		dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.src_maxburst = dma_burst;
		ret = dmaengine_slave_config(tqspi->rx_dma_chan, &dma_sconfig);
		अगर (ret < 0) अणु
			dev_err(tqspi->dev, "failed DMA slave config: %d\n", ret);
			वापस ret;
		पूर्ण

		dma_sync_single_क्रम_device(tqspi->dev, tqspi->rx_dma_phys,
					   tqspi->dma_buf_size,
					   DMA_FROM_DEVICE);

		ret = tegra_qspi_start_rx_dma(tqspi, t, len);
		अगर (ret < 0) अणु
			dev_err(tqspi->dev, "failed to start RX DMA: %d\n", ret);
			अगर (tqspi->cur_direction & DATA_सूची_TX)
				dmaengine_terminate_all(tqspi->tx_dma_chan);
			वापस ret;
		पूर्ण
	पूर्ण

	tegra_qspi_ग_लिखोl(tqspi, tqspi->command1_reg, QSPI_COMMAND1);

	tqspi->is_curr_dma_xfer = true;
	tqspi->dma_control_reg = val;
	val |= QSPI_DMA_EN;
	tegra_qspi_ग_लिखोl(tqspi, val, QSPI_DMA_CTL);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_qspi_start_cpu_based_transfer(काष्ठा tegra_qspi *qspi, काष्ठा spi_transfer *t)
अणु
	u32 val;
	अचिन्हित पूर्णांक cur_words;

	अगर (qspi->cur_direction & DATA_सूची_TX)
		cur_words = tegra_qspi_fill_tx_fअगरo_from_client_txbuf(qspi, t);
	अन्यथा
		cur_words = qspi->curr_dma_words;

	val = QSPI_DMA_BLK_SET(cur_words - 1);
	tegra_qspi_ग_लिखोl(qspi, val, QSPI_DMA_BLK);

	tegra_qspi_unmask_irq(qspi);

	qspi->is_curr_dma_xfer = false;
	val = qspi->command1_reg;
	val |= QSPI_PIO;
	tegra_qspi_ग_लिखोl(qspi, val, QSPI_COMMAND1);

	वापस 0;
पूर्ण

अटल व्योम tegra_qspi_deinit_dma(काष्ठा tegra_qspi *tqspi)
अणु
	अगर (tqspi->tx_dma_buf) अणु
		dma_मुक्त_coherent(tqspi->dev, tqspi->dma_buf_size,
				  tqspi->tx_dma_buf, tqspi->tx_dma_phys);
		tqspi->tx_dma_buf = शून्य;
	पूर्ण

	अगर (tqspi->tx_dma_chan) अणु
		dma_release_channel(tqspi->tx_dma_chan);
		tqspi->tx_dma_chan = शून्य;
	पूर्ण

	अगर (tqspi->rx_dma_buf) अणु
		dma_मुक्त_coherent(tqspi->dev, tqspi->dma_buf_size,
				  tqspi->rx_dma_buf, tqspi->rx_dma_phys);
		tqspi->rx_dma_buf = शून्य;
	पूर्ण

	अगर (tqspi->rx_dma_chan) अणु
		dma_release_channel(tqspi->rx_dma_chan);
		tqspi->rx_dma_chan = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_qspi_init_dma(काष्ठा tegra_qspi *tqspi)
अणु
	काष्ठा dma_chan *dma_chan;
	dma_addr_t dma_phys;
	u32 *dma_buf;
	पूर्णांक err;

	dma_chan = dma_request_chan(tqspi->dev, "rx");
	अगर (IS_ERR(dma_chan)) अणु
		err = PTR_ERR(dma_chan);
		जाओ err_out;
	पूर्ण

	tqspi->rx_dma_chan = dma_chan;

	dma_buf = dma_alloc_coherent(tqspi->dev, tqspi->dma_buf_size, &dma_phys, GFP_KERNEL);
	अगर (!dma_buf) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	tqspi->rx_dma_buf = dma_buf;
	tqspi->rx_dma_phys = dma_phys;

	dma_chan = dma_request_chan(tqspi->dev, "tx");
	अगर (IS_ERR(dma_chan)) अणु
		err = PTR_ERR(dma_chan);
		जाओ err_out;
	पूर्ण

	tqspi->tx_dma_chan = dma_chan;

	dma_buf = dma_alloc_coherent(tqspi->dev, tqspi->dma_buf_size, &dma_phys, GFP_KERNEL);
	अगर (!dma_buf) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	tqspi->tx_dma_buf = dma_buf;
	tqspi->tx_dma_phys = dma_phys;
	tqspi->use_dma = true;

	वापस 0;

err_out:
	tegra_qspi_deinit_dma(tqspi);

	अगर (err != -EPROBE_DEFER) अणु
		dev_err(tqspi->dev, "cannot use DMA: %d\n", err);
		dev_err(tqspi->dev, "falling back to PIO\n");
		वापस 0;
	पूर्ण

	वापस err;
पूर्ण

अटल u32 tegra_qspi_setup_transfer_one(काष्ठा spi_device *spi, काष्ठा spi_transfer *t,
					 bool is_first_of_msg)
अणु
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(spi->master);
	काष्ठा tegra_qspi_client_data *cdata = spi->controller_data;
	u32 command1, command2, speed = t->speed_hz;
	u8 bits_per_word = t->bits_per_word;
	u32 tx_tap = 0, rx_tap = 0;
	पूर्णांक req_mode;

	अगर (speed != tqspi->cur_speed) अणु
		clk_set_rate(tqspi->clk, speed);
		tqspi->cur_speed = speed;
	पूर्ण

	tqspi->cur_pos = 0;
	tqspi->cur_rx_pos = 0;
	tqspi->cur_tx_pos = 0;
	tqspi->curr_xfer = t;

	अगर (is_first_of_msg) अणु
		tegra_qspi_mask_clear_irq(tqspi);

		command1 = tqspi->def_command1_reg;
		command1 |= QSPI_BIT_LENGTH(bits_per_word - 1);

		command1 &= ~QSPI_CONTROL_MODE_MASK;
		req_mode = spi->mode & 0x3;
		अगर (req_mode == SPI_MODE_3)
			command1 |= QSPI_CONTROL_MODE_3;
		अन्यथा
			command1 |= QSPI_CONTROL_MODE_0;

		अगर (spi->mode & SPI_CS_HIGH)
			command1 |= QSPI_CS_SW_VAL;
		अन्यथा
			command1 &= ~QSPI_CS_SW_VAL;
		tegra_qspi_ग_लिखोl(tqspi, command1, QSPI_COMMAND1);

		अगर (cdata && cdata->tx_clk_tap_delay)
			tx_tap = cdata->tx_clk_tap_delay;

		अगर (cdata && cdata->rx_clk_tap_delay)
			rx_tap = cdata->rx_clk_tap_delay;

		command2 = QSPI_TX_TAP_DELAY(tx_tap) | QSPI_RX_TAP_DELAY(rx_tap);
		अगर (command2 != tqspi->def_command2_reg)
			tegra_qspi_ग_लिखोl(tqspi, command2, QSPI_COMMAND2);

	पूर्ण अन्यथा अणु
		command1 = tqspi->command1_reg;
		command1 &= ~QSPI_BIT_LENGTH(~0);
		command1 |= QSPI_BIT_LENGTH(bits_per_word - 1);
	पूर्ण

	command1 &= ~QSPI_SDR_DDR_SEL;

	वापस command1;
पूर्ण

अटल पूर्णांक tegra_qspi_start_transfer_one(काष्ठा spi_device *spi,
					 काष्ठा spi_transfer *t, u32 command1)
अणु
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक total_fअगरo_words;
	u8 bus_width = 0;
	पूर्णांक ret;

	total_fअगरo_words = tegra_qspi_calculate_curr_xfer_param(tqspi, t);

	command1 &= ~QSPI_PACKED;
	अगर (tqspi->is_packed)
		command1 |= QSPI_PACKED;
	tegra_qspi_ग_लिखोl(tqspi, command1, QSPI_COMMAND1);

	tqspi->cur_direction = 0;

	command1 &= ~(QSPI_TX_EN | QSPI_RX_EN);
	अगर (t->rx_buf) अणु
		command1 |= QSPI_RX_EN;
		tqspi->cur_direction |= DATA_सूची_RX;
		bus_width = t->rx_nbits;
	पूर्ण

	अगर (t->tx_buf) अणु
		command1 |= QSPI_TX_EN;
		tqspi->cur_direction |= DATA_सूची_TX;
		bus_width = t->tx_nbits;
	पूर्ण

	command1 &= ~QSPI_INTERFACE_WIDTH_MASK;

	अगर (bus_width == SPI_NBITS_QUAD)
		command1 |= QSPI_INTERFACE_WIDTH_QUAD;
	अन्यथा अगर (bus_width == SPI_NBITS_DUAL)
		command1 |= QSPI_INTERFACE_WIDTH_DUAL;
	अन्यथा
		command1 |= QSPI_INTERFACE_WIDTH_SINGLE;

	tqspi->command1_reg = command1;

	tegra_qspi_ग_लिखोl(tqspi, QSPI_NUM_DUMMY_CYCLE(tqspi->dummy_cycles), QSPI_MISC_REG);

	ret = tegra_qspi_flush_fअगरos(tqspi, false);
	अगर (ret < 0)
		वापस ret;

	अगर (tqspi->use_dma && total_fअगरo_words > QSPI_FIFO_DEPTH)
		ret = tegra_qspi_start_dma_based_transfer(tqspi, t);
	अन्यथा
		ret = tegra_qspi_start_cpu_based_transfer(tqspi, t);

	वापस ret;
पूर्ण

अटल काष्ठा tegra_qspi_client_data *tegra_qspi_parse_cdata_dt(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_qspi_client_data *cdata;
	काष्ठा device_node *slave_np = spi->dev.of_node;

	cdata = kzalloc(माप(*cdata), GFP_KERNEL);
	अगर (!cdata)
		वापस शून्य;

	of_property_पढ़ो_u32(slave_np, "nvidia,tx-clk-tap-delay",
			     &cdata->tx_clk_tap_delay);
	of_property_पढ़ो_u32(slave_np, "nvidia,rx-clk-tap-delay",
			     &cdata->rx_clk_tap_delay);
	वापस cdata;
पूर्ण

अटल व्योम tegra_qspi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_qspi_client_data *cdata = spi->controller_data;

	spi->controller_data = शून्य;
	kमुक्त(cdata);
पूर्ण

अटल पूर्णांक tegra_qspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(spi->master);
	काष्ठा tegra_qspi_client_data *cdata = spi->controller_data;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(tqspi->dev);
	अगर (ret < 0) अणु
		dev_err(tqspi->dev, "failed to get runtime PM: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!cdata) अणु
		cdata = tegra_qspi_parse_cdata_dt(spi);
		spi->controller_data = cdata;
	पूर्ण

	spin_lock_irqsave(&tqspi->lock, flags);

	/* keep शेष cs state to inactive */
	val = tqspi->def_command1_reg;
	अगर (spi->mode & SPI_CS_HIGH)
		val &= ~QSPI_CS_SW_VAL;
	अन्यथा
		val |= QSPI_CS_SW_VAL;

	tqspi->def_command1_reg = val;
	tegra_qspi_ग_लिखोl(tqspi, tqspi->def_command1_reg, QSPI_COMMAND1);

	spin_unlock_irqrestore(&tqspi->lock, flags);

	pm_runसमय_put(tqspi->dev);

	वापस 0;
पूर्ण

अटल व्योम tegra_qspi_dump_regs(काष्ठा tegra_qspi *tqspi)
अणु
	dev_dbg(tqspi->dev, "============ QSPI REGISTER DUMP ============\n");
	dev_dbg(tqspi->dev, "Command1:    0x%08x | Command2:    0x%08x\n",
		tegra_qspi_पढ़ोl(tqspi, QSPI_COMMAND1),
		tegra_qspi_पढ़ोl(tqspi, QSPI_COMMAND2));
	dev_dbg(tqspi->dev, "DMA_CTL:     0x%08x | DMA_BLK:     0x%08x\n",
		tegra_qspi_पढ़ोl(tqspi, QSPI_DMA_CTL),
		tegra_qspi_पढ़ोl(tqspi, QSPI_DMA_BLK));
	dev_dbg(tqspi->dev, "INTR_MASK:  0x%08x | MISC: 0x%08x\n",
		tegra_qspi_पढ़ोl(tqspi, QSPI_INTR_MASK),
		tegra_qspi_पढ़ोl(tqspi, QSPI_MISC_REG));
	dev_dbg(tqspi->dev, "TRANS_STAT:  0x%08x | FIFO_STATUS: 0x%08x\n",
		tegra_qspi_पढ़ोl(tqspi, QSPI_TRANS_STATUS),
		tegra_qspi_पढ़ोl(tqspi, QSPI_FIFO_STATUS));
पूर्ण

अटल व्योम tegra_qspi_handle_error(काष्ठा tegra_qspi *tqspi)
अणु
	dev_err(tqspi->dev, "error in transfer, fifo status 0x%08x\n", tqspi->status_reg);
	tegra_qspi_dump_regs(tqspi);
	tegra_qspi_flush_fअगरos(tqspi, true);
	reset_control_निश्चित(tqspi->rst);
	udelay(2);
	reset_control_deनिश्चित(tqspi->rst);
पूर्ण

अटल व्योम tegra_qspi_transfer_end(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(spi->master);
	पूर्णांक cs_val = (spi->mode & SPI_CS_HIGH) ? 0 : 1;

	अगर (cs_val)
		tqspi->command1_reg |= QSPI_CS_SW_VAL;
	अन्यथा
		tqspi->command1_reg &= ~QSPI_CS_SW_VAL;
	tegra_qspi_ग_लिखोl(tqspi, tqspi->command1_reg, QSPI_COMMAND1);
	tegra_qspi_ग_लिखोl(tqspi, tqspi->def_command1_reg, QSPI_COMMAND1);
पूर्ण

अटल पूर्णांक tegra_qspi_transfer_one_message(काष्ठा spi_master *master, काष्ठा spi_message *msg)
अणु
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा spi_transfer *transfer;
	bool is_first_msg = true;
	पूर्णांक ret;

	msg->status = 0;
	msg->actual_length = 0;
	tqspi->tx_status = 0;
	tqspi->rx_status = 0;

	list_क्रम_each_entry(transfer, &msg->transfers, transfer_list) अणु
		काष्ठा spi_transfer *xfer = transfer;
		u8 dummy_bytes = 0;
		u32 cmd1;

		tqspi->dummy_cycles = 0;
		/*
		 * Tegra QSPI hardware supports dummy bytes transfer after actual transfer
		 * bytes based on programmed dummy घड़ी cycles in the QSPI_MISC रेजिस्टर.
		 * So, check अगर the next transfer is dummy data transfer and program dummy
		 * घड़ी cycles aदीर्घ with the current transfer and skip next transfer.
		 */
		अगर (!list_is_last(&xfer->transfer_list, &msg->transfers)) अणु
			काष्ठा spi_transfer *next_xfer;

			next_xfer = list_next_entry(xfer, transfer_list);
			अगर (next_xfer->dummy_data) अणु
				u32 dummy_cycles = next_xfer->len * 8 / next_xfer->tx_nbits;

				अगर (dummy_cycles <= QSPI_DUMMY_CYCLES_MAX) अणु
					tqspi->dummy_cycles = dummy_cycles;
					dummy_bytes = next_xfer->len;
					transfer = next_xfer;
				पूर्ण
			पूर्ण
		पूर्ण

		reinit_completion(&tqspi->xfer_completion);

		cmd1 = tegra_qspi_setup_transfer_one(spi, xfer, is_first_msg);

		ret = tegra_qspi_start_transfer_one(spi, xfer, cmd1);
		अगर (ret < 0) अणु
			dev_err(tqspi->dev, "failed to start transfer: %d\n", ret);
			जाओ complete_xfer;
		पूर्ण

		is_first_msg = false;
		ret = रुको_क्रम_completion_समयout(&tqspi->xfer_completion,
						  QSPI_DMA_TIMEOUT);
		अगर (WARN_ON(ret == 0)) अणु
			dev_err(tqspi->dev, "transfer timeout: %d\n", ret);
			अगर (tqspi->is_curr_dma_xfer && (tqspi->cur_direction & DATA_सूची_TX))
				dmaengine_terminate_all(tqspi->tx_dma_chan);
			अगर (tqspi->is_curr_dma_xfer && (tqspi->cur_direction & DATA_सूची_RX))
				dmaengine_terminate_all(tqspi->rx_dma_chan);
			tegra_qspi_handle_error(tqspi);
			ret = -EIO;
			जाओ complete_xfer;
		पूर्ण

		अगर (tqspi->tx_status ||  tqspi->rx_status) अणु
			tegra_qspi_handle_error(tqspi);
			ret = -EIO;
			जाओ complete_xfer;
		पूर्ण

		msg->actual_length += xfer->len + dummy_bytes;

complete_xfer:
		अगर (ret < 0) अणु
			tegra_qspi_transfer_end(spi);
			spi_transfer_delay_exec(xfer);
			जाओ निकास;
		पूर्ण

		अगर (list_is_last(&xfer->transfer_list, &msg->transfers)) अणु
			/* de-activate CS after last transfer only when cs_change is not set */
			अगर (!xfer->cs_change) अणु
				tegra_qspi_transfer_end(spi);
				spi_transfer_delay_exec(xfer);
			पूर्ण
		पूर्ण अन्यथा अगर (xfer->cs_change) अणु
			 /* de-activated CS between the transfers only when cs_change is set */
			tegra_qspi_transfer_end(spi);
			spi_transfer_delay_exec(xfer);
		पूर्ण
	पूर्ण

	ret = 0;
निकास:
	msg->status = ret;
	spi_finalize_current_message(master);
	वापस ret;
पूर्ण

अटल irqवापस_t handle_cpu_based_xfer(काष्ठा tegra_qspi *tqspi)
अणु
	काष्ठा spi_transfer *t = tqspi->curr_xfer;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tqspi->lock, flags);

	अगर (tqspi->tx_status ||  tqspi->rx_status) अणु
		tegra_qspi_handle_error(tqspi);
		complete(&tqspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	अगर (tqspi->cur_direction & DATA_सूची_RX)
		tegra_qspi_पढ़ो_rx_fअगरo_to_client_rxbuf(tqspi, t);

	अगर (tqspi->cur_direction & DATA_सूची_TX)
		tqspi->cur_pos = tqspi->cur_tx_pos;
	अन्यथा
		tqspi->cur_pos = tqspi->cur_rx_pos;

	अगर (tqspi->cur_pos == t->len) अणु
		complete(&tqspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	tegra_qspi_calculate_curr_xfer_param(tqspi, t);
	tegra_qspi_start_cpu_based_transfer(tqspi, t);
निकास:
	spin_unlock_irqrestore(&tqspi->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t handle_dma_based_xfer(काष्ठा tegra_qspi *tqspi)
अणु
	काष्ठा spi_transfer *t = tqspi->curr_xfer;
	अचिन्हित पूर्णांक total_fअगरo_words;
	अचिन्हित दीर्घ flags;
	दीर्घ रुको_status;
	पूर्णांक err = 0;

	अगर (tqspi->cur_direction & DATA_सूची_TX) अणु
		अगर (tqspi->tx_status) अणु
			dmaengine_terminate_all(tqspi->tx_dma_chan);
			err += 1;
		पूर्ण अन्यथा अणु
			रुको_status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&tqspi->tx_dma_complete, QSPI_DMA_TIMEOUT);
			अगर (रुको_status <= 0) अणु
				dmaengine_terminate_all(tqspi->tx_dma_chan);
				dev_err(tqspi->dev, "failed TX DMA transfer\n");
				err += 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tqspi->cur_direction & DATA_सूची_RX) अणु
		अगर (tqspi->rx_status) अणु
			dmaengine_terminate_all(tqspi->rx_dma_chan);
			err += 2;
		पूर्ण अन्यथा अणु
			रुको_status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&tqspi->rx_dma_complete, QSPI_DMA_TIMEOUT);
			अगर (रुको_status <= 0) अणु
				dmaengine_terminate_all(tqspi->rx_dma_chan);
				dev_err(tqspi->dev, "failed RX DMA transfer\n");
				err += 2;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&tqspi->lock, flags);

	अगर (err) अणु
		tegra_qspi_dma_unmap_xfer(tqspi, t);
		tegra_qspi_handle_error(tqspi);
		complete(&tqspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	अगर (tqspi->cur_direction & DATA_सूची_RX)
		tegra_qspi_copy_qspi_rxbuf_to_client_rxbuf(tqspi, t);

	अगर (tqspi->cur_direction & DATA_सूची_TX)
		tqspi->cur_pos = tqspi->cur_tx_pos;
	अन्यथा
		tqspi->cur_pos = tqspi->cur_rx_pos;

	अगर (tqspi->cur_pos == t->len) अणु
		tegra_qspi_dma_unmap_xfer(tqspi, t);
		complete(&tqspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	tegra_qspi_dma_unmap_xfer(tqspi, t);

	/* जारी transfer in current message */
	total_fअगरo_words = tegra_qspi_calculate_curr_xfer_param(tqspi, t);
	अगर (total_fअगरo_words > QSPI_FIFO_DEPTH)
		err = tegra_qspi_start_dma_based_transfer(tqspi, t);
	अन्यथा
		err = tegra_qspi_start_cpu_based_transfer(tqspi, t);

निकास:
	spin_unlock_irqrestore(&tqspi->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_qspi_isr_thपढ़ो(पूर्णांक irq, व्योम *context_data)
अणु
	काष्ठा tegra_qspi *tqspi = context_data;

	tqspi->status_reg = tegra_qspi_पढ़ोl(tqspi, QSPI_FIFO_STATUS);

	अगर (tqspi->cur_direction & DATA_सूची_TX)
		tqspi->tx_status = tqspi->status_reg & (QSPI_TX_FIFO_UNF | QSPI_TX_FIFO_OVF);

	अगर (tqspi->cur_direction & DATA_सूची_RX)
		tqspi->rx_status = tqspi->status_reg & (QSPI_RX_FIFO_OVF | QSPI_RX_FIFO_UNF);

	tegra_qspi_mask_clear_irq(tqspi);

	अगर (!tqspi->is_curr_dma_xfer)
		वापस handle_cpu_based_xfer(tqspi);

	वापस handle_dma_based_xfer(tqspi);
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_qspi_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-qspi", पूर्ण,
	अणु .compatible = "nvidia,tegra186-qspi", पूर्ण,
	अणु .compatible = "nvidia,tegra194-qspi", पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, tegra_qspi_of_match);

अटल पूर्णांक tegra_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master;
	काष्ठा tegra_qspi	*tqspi;
	काष्ठा resource		*r;
	पूर्णांक ret, qspi_irq;
	पूर्णांक bus_num;

	master = devm_spi_alloc_master(&pdev->dev, माप(*tqspi));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);
	tqspi = spi_master_get_devdata(master);

	master->mode_bits = SPI_MODE_0 | SPI_MODE_3 | SPI_CS_HIGH |
			    SPI_TX_DUAL | SPI_RX_DUAL | SPI_TX_QUAD | SPI_RX_QUAD;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(16) | SPI_BPW_MASK(8);
	master->setup = tegra_qspi_setup;
	master->cleanup = tegra_qspi_cleanup;
	master->transfer_one_message = tegra_qspi_transfer_one_message;
	master->num_chipselect = 1;
	master->स्वतः_runसमय_pm = true;

	bus_num = of_alias_get_id(pdev->dev.of_node, "spi");
	अगर (bus_num >= 0)
		master->bus_num = bus_num;

	tqspi->master = master;
	tqspi->dev = &pdev->dev;
	spin_lock_init(&tqspi->lock);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tqspi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(tqspi->base))
		वापस PTR_ERR(tqspi->base);

	tqspi->phys = r->start;
	qspi_irq = platक्रमm_get_irq(pdev, 0);
	tqspi->irq = qspi_irq;

	tqspi->clk = devm_clk_get(&pdev->dev, "qspi");
	अगर (IS_ERR(tqspi->clk)) अणु
		ret = PTR_ERR(tqspi->clk);
		dev_err(&pdev->dev, "failed to get clock: %d\n", ret);
		वापस ret;
	पूर्ण

	tqspi->rst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(tqspi->rst)) अणु
		ret = PTR_ERR(tqspi->rst);
		dev_err(&pdev->dev, "failed to get reset control: %d\n", ret);
		वापस ret;
	पूर्ण

	tqspi->max_buf_size = QSPI_FIFO_DEPTH << 2;
	tqspi->dma_buf_size = DEFAULT_QSPI_DMA_BUF_LEN;

	ret = tegra_qspi_init_dma(tqspi);
	अगर (ret < 0)
		वापस ret;

	अगर (tqspi->use_dma)
		tqspi->max_buf_size = tqspi->dma_buf_size;

	init_completion(&tqspi->tx_dma_complete);
	init_completion(&tqspi->rx_dma_complete);
	init_completion(&tqspi->xfer_completion);

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get runtime PM: %d\n", ret);
		जाओ निकास_pm_disable;
	पूर्ण

	reset_control_निश्चित(tqspi->rst);
	udelay(2);
	reset_control_deनिश्चित(tqspi->rst);

	tqspi->def_command1_reg = QSPI_M_S | QSPI_CS_SW_HW |  QSPI_CS_SW_VAL;
	tegra_qspi_ग_लिखोl(tqspi, tqspi->def_command1_reg, QSPI_COMMAND1);
	tqspi->spi_cs_timing1 = tegra_qspi_पढ़ोl(tqspi, QSPI_CS_TIMING1);
	tqspi->spi_cs_timing2 = tegra_qspi_पढ़ोl(tqspi, QSPI_CS_TIMING2);
	tqspi->def_command2_reg = tegra_qspi_पढ़ोl(tqspi, QSPI_COMMAND2);

	pm_runसमय_put(&pdev->dev);

	ret = request_thपढ़ोed_irq(tqspi->irq, शून्य,
				   tegra_qspi_isr_thपढ़ो, IRQF_ONESHOT,
				   dev_name(&pdev->dev), tqspi);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ#%u: %d\n", tqspi->irq, ret);
		जाओ निकास_pm_disable;
	पूर्ण

	master->dev.of_node = pdev->dev.of_node;
	ret = spi_रेजिस्टर_master(master);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register master: %d\n", ret);
		जाओ निकास_मुक्त_irq;
	पूर्ण

	वापस 0;

निकास_मुक्त_irq:
	मुक्त_irq(qspi_irq, tqspi);
निकास_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	tegra_qspi_deinit_dma(tqspi);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(master);

	spi_unरेजिस्टर_master(master);
	मुक्त_irq(tqspi->irq, tqspi);
	pm_runसमय_disable(&pdev->dev);
	tegra_qspi_deinit_dma(tqspi);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_qspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);

	वापस spi_master_suspend(master);
पूर्ण

अटल पूर्णांक __maybe_unused tegra_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get runtime PM: %d\n", ret);
		वापस ret;
	पूर्ण

	tegra_qspi_ग_लिखोl(tqspi, tqspi->command1_reg, QSPI_COMMAND1);
	tegra_qspi_ग_लिखोl(tqspi, tqspi->def_command2_reg, QSPI_COMMAND2);
	pm_runसमय_put(dev);

	वापस spi_master_resume(master);
पूर्ण

अटल पूर्णांक __maybe_unused tegra_qspi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(master);

	/* flush all ग_लिखो which are in PPSB queue by पढ़ोing back */
	tegra_qspi_पढ़ोl(tqspi, QSPI_COMMAND1);

	clk_disable_unprepare(tqspi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_qspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_qspi *tqspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(tqspi->clk);
	अगर (ret < 0)
		dev_err(tqspi->dev, "failed to enable clock: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_qspi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_qspi_runसमय_suspend, tegra_qspi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_qspi_suspend, tegra_qspi_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_qspi_driver = अणु
	.driver = अणु
		.name		= "tegra-qspi",
		.pm		= &tegra_qspi_pm_ops,
		.of_match_table	= tegra_qspi_of_match,
	पूर्ण,
	.probe =	tegra_qspi_probe,
	.हटाओ =	tegra_qspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_qspi_driver);

MODULE_ALIAS("platform:qspi-tegra");
MODULE_DESCRIPTION("NVIDIA Tegra QSPI Controller Driver");
MODULE_AUTHOR("Sowjanya Komatineni <skomatineni@nvidia.com>");
MODULE_LICENSE("GPL v2");
