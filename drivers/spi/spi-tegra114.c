<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI driver क्रम NVIDIA's Tegra114 SPI Controller.
 *
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/spi/spi.h>

#घोषणा SPI_COMMAND1				0x000
#घोषणा SPI_BIT_LENGTH(x)			(((x) & 0x1f) << 0)
#घोषणा SPI_PACKED				(1 << 5)
#घोषणा SPI_TX_EN				(1 << 11)
#घोषणा SPI_RX_EN				(1 << 12)
#घोषणा SPI_BOTH_EN_BYTE			(1 << 13)
#घोषणा SPI_BOTH_EN_BIT				(1 << 14)
#घोषणा SPI_LSBYTE_FE				(1 << 15)
#घोषणा SPI_LSBIT_FE				(1 << 16)
#घोषणा SPI_BIसूचीOE				(1 << 17)
#घोषणा SPI_IDLE_SDA_DRIVE_LOW			(0 << 18)
#घोषणा SPI_IDLE_SDA_DRIVE_HIGH			(1 << 18)
#घोषणा SPI_IDLE_SDA_PULL_LOW			(2 << 18)
#घोषणा SPI_IDLE_SDA_PULL_HIGH			(3 << 18)
#घोषणा SPI_IDLE_SDA_MASK			(3 << 18)
#घोषणा SPI_CS_SW_VAL				(1 << 20)
#घोषणा SPI_CS_SW_HW				(1 << 21)
/* SPI_CS_POL_INACTIVE bits are शेष high */
						/* n from 0 to 3 */
#घोषणा SPI_CS_POL_INACTIVE(n)			(1 << (22 + (n)))
#घोषणा SPI_CS_POL_INACTIVE_MASK		(0xF << 22)

#घोषणा SPI_CS_SEL_0				(0 << 26)
#घोषणा SPI_CS_SEL_1				(1 << 26)
#घोषणा SPI_CS_SEL_2				(2 << 26)
#घोषणा SPI_CS_SEL_3				(3 << 26)
#घोषणा SPI_CS_SEL_MASK				(3 << 26)
#घोषणा SPI_CS_SEL(x)				(((x) & 0x3) << 26)
#घोषणा SPI_CONTROL_MODE_0			(0 << 28)
#घोषणा SPI_CONTROL_MODE_1			(1 << 28)
#घोषणा SPI_CONTROL_MODE_2			(2 << 28)
#घोषणा SPI_CONTROL_MODE_3			(3 << 28)
#घोषणा SPI_CONTROL_MODE_MASK			(3 << 28)
#घोषणा SPI_MODE_SEL(x)				(((x) & 0x3) << 28)
#घोषणा SPI_M_S					(1 << 30)
#घोषणा SPI_PIO					(1 << 31)

#घोषणा SPI_COMMAND2				0x004
#घोषणा SPI_TX_TAP_DELAY(x)			(((x) & 0x3F) << 6)
#घोषणा SPI_RX_TAP_DELAY(x)			(((x) & 0x3F) << 0)

#घोषणा SPI_CS_TIMING1				0x008
#घोषणा SPI_SETUP_HOLD(setup, hold)		(((setup) << 4) | (hold))
#घोषणा SPI_CS_SETUP_HOLD(reg, cs, val)			\
		((((val) & 0xFFu) << ((cs) * 8)) |	\
		((reg) & ~(0xFFu << ((cs) * 8))))

#घोषणा SPI_CS_TIMING2				0x00C
#घोषणा CYCLES_BETWEEN_PACKETS_0(x)		(((x) & 0x1F) << 0)
#घोषणा CS_ACTIVE_BETWEEN_PACKETS_0		(1 << 5)
#घोषणा CYCLES_BETWEEN_PACKETS_1(x)		(((x) & 0x1F) << 8)
#घोषणा CS_ACTIVE_BETWEEN_PACKETS_1		(1 << 13)
#घोषणा CYCLES_BETWEEN_PACKETS_2(x)		(((x) & 0x1F) << 16)
#घोषणा CS_ACTIVE_BETWEEN_PACKETS_2		(1 << 21)
#घोषणा CYCLES_BETWEEN_PACKETS_3(x)		(((x) & 0x1F) << 24)
#घोषणा CS_ACTIVE_BETWEEN_PACKETS_3		(1 << 29)
#घोषणा SPI_SET_CS_ACTIVE_BETWEEN_PACKETS(reg, cs, val)		\
		(reg = (((val) & 0x1) << ((cs) * 8 + 5)) |	\
			((reg) & ~(1 << ((cs) * 8 + 5))))
#घोषणा SPI_SET_CYCLES_BETWEEN_PACKETS(reg, cs, val)		\
		(reg = (((val) & 0x1F) << ((cs) * 8)) |		\
			((reg) & ~(0x1F << ((cs) * 8))))
#घोषणा MAX_SETUP_HOLD_CYCLES			16
#घोषणा MAX_INACTIVE_CYCLES			32

#घोषणा SPI_TRANS_STATUS			0x010
#घोषणा SPI_BLK_CNT(val)			(((val) >> 0) & 0xFFFF)
#घोषणा SPI_SLV_IDLE_COUNT(val)			(((val) >> 16) & 0xFF)
#घोषणा SPI_RDY					(1 << 30)

#घोषणा SPI_FIFO_STATUS				0x014
#घोषणा SPI_RX_FIFO_EMPTY			(1 << 0)
#घोषणा SPI_RX_FIFO_FULL			(1 << 1)
#घोषणा SPI_TX_FIFO_EMPTY			(1 << 2)
#घोषणा SPI_TX_FIFO_FULL			(1 << 3)
#घोषणा SPI_RX_FIFO_UNF				(1 << 4)
#घोषणा SPI_RX_FIFO_OVF				(1 << 5)
#घोषणा SPI_TX_FIFO_UNF				(1 << 6)
#घोषणा SPI_TX_FIFO_OVF				(1 << 7)
#घोषणा SPI_ERR					(1 << 8)
#घोषणा SPI_TX_FIFO_FLUSH			(1 << 14)
#घोषणा SPI_RX_FIFO_FLUSH			(1 << 15)
#घोषणा SPI_TX_FIFO_EMPTY_COUNT(val)		(((val) >> 16) & 0x7F)
#घोषणा SPI_RX_FIFO_FULL_COUNT(val)		(((val) >> 23) & 0x7F)
#घोषणा SPI_FRAME_END				(1 << 30)
#घोषणा SPI_CS_INACTIVE				(1 << 31)

#घोषणा SPI_FIFO_ERROR				(SPI_RX_FIFO_UNF | \
			SPI_RX_FIFO_OVF | SPI_TX_FIFO_UNF | SPI_TX_FIFO_OVF)
#घोषणा SPI_FIFO_EMPTY			(SPI_RX_FIFO_EMPTY | SPI_TX_FIFO_EMPTY)

#घोषणा SPI_TX_DATA				0x018
#घोषणा SPI_RX_DATA				0x01C

#घोषणा SPI_DMA_CTL				0x020
#घोषणा SPI_TX_TRIG_1				(0 << 15)
#घोषणा SPI_TX_TRIG_4				(1 << 15)
#घोषणा SPI_TX_TRIG_8				(2 << 15)
#घोषणा SPI_TX_TRIG_16				(3 << 15)
#घोषणा SPI_TX_TRIG_MASK			(3 << 15)
#घोषणा SPI_RX_TRIG_1				(0 << 19)
#घोषणा SPI_RX_TRIG_4				(1 << 19)
#घोषणा SPI_RX_TRIG_8				(2 << 19)
#घोषणा SPI_RX_TRIG_16				(3 << 19)
#घोषणा SPI_RX_TRIG_MASK			(3 << 19)
#घोषणा SPI_IE_TX				(1 << 28)
#घोषणा SPI_IE_RX				(1 << 29)
#घोषणा SPI_CONT				(1 << 30)
#घोषणा SPI_DMA					(1 << 31)
#घोषणा SPI_DMA_EN				SPI_DMA

#घोषणा SPI_DMA_BLK				0x024
#घोषणा SPI_DMA_BLK_SET(x)			(((x) & 0xFFFF) << 0)

#घोषणा SPI_TX_FIFO				0x108
#घोषणा SPI_RX_FIFO				0x188
#घोषणा SPI_INTR_MASK				0x18c
#घोषणा SPI_INTR_ALL_MASK			(0x1fUL << 25)
#घोषणा MAX_CHIP_SELECT				4
#घोषणा SPI_FIFO_DEPTH				64
#घोषणा DATA_सूची_TX				(1 << 0)
#घोषणा DATA_सूची_RX				(1 << 1)

#घोषणा SPI_DMA_TIMEOUT				(msecs_to_jअगरfies(1000))
#घोषणा DEFAULT_SPI_DMA_BUF_LEN			(16*1024)
#घोषणा TX_FIFO_EMPTY_COUNT_MAX			SPI_TX_FIFO_EMPTY_COUNT(0x40)
#घोषणा RX_FIFO_FULL_COUNT_ZERO			SPI_RX_FIFO_FULL_COUNT(0)
#घोषणा MAX_HOLD_CYCLES				16
#घोषणा SPI_DEFAULT_SPEED			25000000

काष्ठा tegra_spi_soc_data अणु
	bool has_पूर्णांकr_mask_reg;
पूर्ण;

काष्ठा tegra_spi_client_data अणु
	पूर्णांक tx_clk_tap_delay;
	पूर्णांक rx_clk_tap_delay;
पूर्ण;

काष्ठा tegra_spi_data अणु
	काष्ठा device				*dev;
	काष्ठा spi_master			*master;
	spinlock_t				lock;

	काष्ठा clk				*clk;
	काष्ठा reset_control			*rst;
	व्योम __iomem				*base;
	phys_addr_t				phys;
	अचिन्हित				irq;
	u32					cur_speed;

	काष्ठा spi_device			*cur_spi;
	काष्ठा spi_device			*cs_control;
	अचिन्हित				cur_pos;
	अचिन्हित				words_per_32bit;
	अचिन्हित				bytes_per_word;
	अचिन्हित				curr_dma_words;
	अचिन्हित				cur_direction;

	अचिन्हित				cur_rx_pos;
	अचिन्हित				cur_tx_pos;

	अचिन्हित				dma_buf_size;
	अचिन्हित				max_buf_size;
	bool					is_curr_dma_xfer;
	bool					use_hw_based_cs;

	काष्ठा completion			rx_dma_complete;
	काष्ठा completion			tx_dma_complete;

	u32					tx_status;
	u32					rx_status;
	u32					status_reg;
	bool					is_packed;

	u32					command1_reg;
	u32					dma_control_reg;
	u32					def_command1_reg;
	u32					def_command2_reg;
	u32					spi_cs_timing1;
	u32					spi_cs_timing2;
	u8					last_used_cs;

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
	स्थिर काष्ठा tegra_spi_soc_data		*soc_data;
पूर्ण;

अटल पूर्णांक tegra_spi_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक tegra_spi_runसमय_resume(काष्ठा device *dev);

अटल अंतरभूत u32 tegra_spi_पढ़ोl(काष्ठा tegra_spi_data *tspi,
		अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(tspi->base + reg);
पूर्ण

अटल अंतरभूत व्योम tegra_spi_ग_लिखोl(काष्ठा tegra_spi_data *tspi,
		u32 val, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोl(val, tspi->base + reg);

	/* Read back रेजिस्टर to make sure that रेजिस्टर ग_लिखोs completed */
	अगर (reg != SPI_TX_FIFO)
		पढ़ोl(tspi->base + SPI_COMMAND1);
पूर्ण

अटल व्योम tegra_spi_clear_status(काष्ठा tegra_spi_data *tspi)
अणु
	u32 val;

	/* Write 1 to clear status रेजिस्टर */
	val = tegra_spi_पढ़ोl(tspi, SPI_TRANS_STATUS);
	tegra_spi_ग_लिखोl(tspi, val, SPI_TRANS_STATUS);

	/* Clear fअगरo status error अगर any */
	val = tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS);
	अगर (val & SPI_ERR)
		tegra_spi_ग_लिखोl(tspi, SPI_ERR | SPI_FIFO_ERROR,
				SPI_FIFO_STATUS);
पूर्ण

अटल अचिन्हित tegra_spi_calculate_curr_xfer_param(
	काष्ठा spi_device *spi, काष्ठा tegra_spi_data *tspi,
	काष्ठा spi_transfer *t)
अणु
	अचिन्हित reमुख्य_len = t->len - tspi->cur_pos;
	अचिन्हित max_word;
	अचिन्हित bits_per_word = t->bits_per_word;
	अचिन्हित max_len;
	अचिन्हित total_fअगरo_words;

	tspi->bytes_per_word = DIV_ROUND_UP(bits_per_word, 8);

	अगर ((bits_per_word == 8 || bits_per_word == 16 ||
	     bits_per_word == 32) && t->len > 3) अणु
		tspi->is_packed = true;
		tspi->words_per_32bit = 32/bits_per_word;
	पूर्ण अन्यथा अणु
		tspi->is_packed = false;
		tspi->words_per_32bit = 1;
	पूर्ण

	अगर (tspi->is_packed) अणु
		max_len = min(reमुख्य_len, tspi->max_buf_size);
		tspi->curr_dma_words = max_len/tspi->bytes_per_word;
		total_fअगरo_words = (max_len + 3) / 4;
	पूर्ण अन्यथा अणु
		max_word = (reमुख्य_len - 1) / tspi->bytes_per_word + 1;
		max_word = min(max_word, tspi->max_buf_size/4);
		tspi->curr_dma_words = max_word;
		total_fअगरo_words = max_word;
	पूर्ण
	वापस total_fअगरo_words;
पूर्ण

अटल अचिन्हित tegra_spi_fill_tx_fअगरo_from_client_txbuf(
	काष्ठा tegra_spi_data *tspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित nbytes;
	अचिन्हित tx_empty_count;
	u32 fअगरo_status;
	अचिन्हित max_n_32bit;
	अचिन्हित i, count;
	अचिन्हित पूर्णांक written_words;
	अचिन्हित fअगरo_words_left;
	u8 *tx_buf = (u8 *)t->tx_buf + tspi->cur_tx_pos;

	fअगरo_status = tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS);
	tx_empty_count = SPI_TX_FIFO_EMPTY_COUNT(fअगरo_status);

	अगर (tspi->is_packed) अणु
		fअगरo_words_left = tx_empty_count * tspi->words_per_32bit;
		written_words = min(fअगरo_words_left, tspi->curr_dma_words);
		nbytes = written_words * tspi->bytes_per_word;
		max_n_32bit = DIV_ROUND_UP(nbytes, 4);
		क्रम (count = 0; count < max_n_32bit; count++) अणु
			u32 x = 0;

			क्रम (i = 0; (i < 4) && nbytes; i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegra_spi_ग_लिखोl(tspi, x, SPI_TX_FIFO);
		पूर्ण

		tspi->cur_tx_pos += written_words * tspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक ग_लिखो_bytes;
		max_n_32bit = min(tspi->curr_dma_words,  tx_empty_count);
		written_words = max_n_32bit;
		nbytes = written_words * tspi->bytes_per_word;
		अगर (nbytes > t->len - tspi->cur_pos)
			nbytes = t->len - tspi->cur_pos;
		ग_लिखो_bytes = nbytes;
		क्रम (count = 0; count < max_n_32bit; count++) अणु
			u32 x = 0;

			क्रम (i = 0; nbytes && (i < tspi->bytes_per_word);
							i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegra_spi_ग_लिखोl(tspi, x, SPI_TX_FIFO);
		पूर्ण

		tspi->cur_tx_pos += ग_लिखो_bytes;
	पूर्ण

	वापस written_words;
पूर्ण

अटल अचिन्हित पूर्णांक tegra_spi_पढ़ो_rx_fअगरo_to_client_rxbuf(
		काष्ठा tegra_spi_data *tspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित rx_full_count;
	u32 fअगरo_status;
	अचिन्हित i, count;
	अचिन्हित पूर्णांक पढ़ो_words = 0;
	अचिन्हित len;
	u8 *rx_buf = (u8 *)t->rx_buf + tspi->cur_rx_pos;

	fअगरo_status = tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS);
	rx_full_count = SPI_RX_FIFO_FULL_COUNT(fअगरo_status);
	अगर (tspi->is_packed) अणु
		len = tspi->curr_dma_words * tspi->bytes_per_word;
		क्रम (count = 0; count < rx_full_count; count++) अणु
			u32 x = tegra_spi_पढ़ोl(tspi, SPI_RX_FIFO);

			क्रम (i = 0; len && (i < 4); i++, len--)
				*rx_buf++ = (x >> i*8) & 0xFF;
		पूर्ण
		पढ़ो_words += tspi->curr_dma_words;
		tspi->cur_rx_pos += tspi->curr_dma_words * tspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;
		u8 bytes_per_word = tspi->bytes_per_word;
		अचिन्हित पूर्णांक पढ़ो_bytes;

		len = rx_full_count * bytes_per_word;
		अगर (len > t->len - tspi->cur_pos)
			len = t->len - tspi->cur_pos;
		पढ़ो_bytes = len;
		क्रम (count = 0; count < rx_full_count; count++) अणु
			u32 x = tegra_spi_पढ़ोl(tspi, SPI_RX_FIFO) & rx_mask;

			क्रम (i = 0; len && (i < bytes_per_word); i++, len--)
				*rx_buf++ = (x >> (i*8)) & 0xFF;
		पूर्ण
		पढ़ो_words += rx_full_count;
		tspi->cur_rx_pos += पढ़ो_bytes;
	पूर्ण

	वापस पढ़ो_words;
पूर्ण

अटल व्योम tegra_spi_copy_client_txbuf_to_spi_txbuf(
		काष्ठा tegra_spi_data *tspi, काष्ठा spi_transfer *t)
अणु
	/* Make the dma buffer to पढ़ो by cpu */
	dma_sync_single_क्रम_cpu(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);

	अगर (tspi->is_packed) अणु
		अचिन्हित len = tspi->curr_dma_words * tspi->bytes_per_word;

		स_नकल(tspi->tx_dma_buf, t->tx_buf + tspi->cur_pos, len);
		tspi->cur_tx_pos += tspi->curr_dma_words * tspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक count;
		u8 *tx_buf = (u8 *)t->tx_buf + tspi->cur_tx_pos;
		अचिन्हित consume = tspi->curr_dma_words * tspi->bytes_per_word;
		अचिन्हित पूर्णांक ग_लिखो_bytes;

		अगर (consume > t->len - tspi->cur_pos)
			consume = t->len - tspi->cur_pos;
		ग_लिखो_bytes = consume;
		क्रम (count = 0; count < tspi->curr_dma_words; count++) अणु
			u32 x = 0;

			क्रम (i = 0; consume && (i < tspi->bytes_per_word);
							i++, consume--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tspi->tx_dma_buf[count] = x;
		पूर्ण

		tspi->cur_tx_pos += ग_लिखो_bytes;
	पूर्ण

	/* Make the dma buffer to पढ़ो by dma */
	dma_sync_single_क्रम_device(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);
पूर्ण

अटल व्योम tegra_spi_copy_spi_rxbuf_to_client_rxbuf(
		काष्ठा tegra_spi_data *tspi, काष्ठा spi_transfer *t)
अणु
	/* Make the dma buffer to पढ़ो by cpu */
	dma_sync_single_क्रम_cpu(tspi->dev, tspi->rx_dma_phys,
		tspi->dma_buf_size, DMA_FROM_DEVICE);

	अगर (tspi->is_packed) अणु
		अचिन्हित len = tspi->curr_dma_words * tspi->bytes_per_word;

		स_नकल(t->rx_buf + tspi->cur_rx_pos, tspi->rx_dma_buf, len);
		tspi->cur_rx_pos += tspi->curr_dma_words * tspi->bytes_per_word;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक count;
		अचिन्हित अक्षर *rx_buf = t->rx_buf + tspi->cur_rx_pos;
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;
		अचिन्हित consume = tspi->curr_dma_words * tspi->bytes_per_word;
		अचिन्हित पूर्णांक पढ़ो_bytes;

		अगर (consume > t->len - tspi->cur_pos)
			consume = t->len - tspi->cur_pos;
		पढ़ो_bytes = consume;
		क्रम (count = 0; count < tspi->curr_dma_words; count++) अणु
			u32 x = tspi->rx_dma_buf[count] & rx_mask;

			क्रम (i = 0; consume && (i < tspi->bytes_per_word);
							i++, consume--)
				*rx_buf++ = (x >> (i*8)) & 0xFF;
		पूर्ण

		tspi->cur_rx_pos += पढ़ो_bytes;
	पूर्ण

	/* Make the dma buffer to पढ़ो by dma */
	dma_sync_single_क्रम_device(tspi->dev, tspi->rx_dma_phys,
		tspi->dma_buf_size, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम tegra_spi_dma_complete(व्योम *args)
अणु
	काष्ठा completion *dma_complete = args;

	complete(dma_complete);
पूर्ण

अटल पूर्णांक tegra_spi_start_tx_dma(काष्ठा tegra_spi_data *tspi, पूर्णांक len)
अणु
	reinit_completion(&tspi->tx_dma_complete);
	tspi->tx_dma_desc = dmaengine_prep_slave_single(tspi->tx_dma_chan,
				tspi->tx_dma_phys, len, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);
	अगर (!tspi->tx_dma_desc) अणु
		dev_err(tspi->dev, "Not able to get desc for Tx\n");
		वापस -EIO;
	पूर्ण

	tspi->tx_dma_desc->callback = tegra_spi_dma_complete;
	tspi->tx_dma_desc->callback_param = &tspi->tx_dma_complete;

	dmaengine_submit(tspi->tx_dma_desc);
	dma_async_issue_pending(tspi->tx_dma_chan);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_spi_start_rx_dma(काष्ठा tegra_spi_data *tspi, पूर्णांक len)
अणु
	reinit_completion(&tspi->rx_dma_complete);
	tspi->rx_dma_desc = dmaengine_prep_slave_single(tspi->rx_dma_chan,
				tspi->rx_dma_phys, len, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);
	अगर (!tspi->rx_dma_desc) अणु
		dev_err(tspi->dev, "Not able to get desc for Rx\n");
		वापस -EIO;
	पूर्ण

	tspi->rx_dma_desc->callback = tegra_spi_dma_complete;
	tspi->rx_dma_desc->callback_param = &tspi->rx_dma_complete;

	dmaengine_submit(tspi->rx_dma_desc);
	dma_async_issue_pending(tspi->rx_dma_chan);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_spi_flush_fअगरos(काष्ठा tegra_spi_data *tspi)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	u32 status;

	status = tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS);
	अगर ((status & SPI_FIFO_EMPTY) != SPI_FIFO_EMPTY) अणु
		status |= SPI_RX_FIFO_FLUSH | SPI_TX_FIFO_FLUSH;
		tegra_spi_ग_लिखोl(tspi, status, SPI_FIFO_STATUS);
		जबतक ((status & SPI_FIFO_EMPTY) != SPI_FIFO_EMPTY) अणु
			status = tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS);
			अगर (समय_after(jअगरfies, समयout)) अणु
				dev_err(tspi->dev,
					"timeout waiting for fifo flush\n");
				वापस -EIO;
			पूर्ण

			udelay(1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_spi_start_dma_based_transfer(
		काष्ठा tegra_spi_data *tspi, काष्ठा spi_transfer *t)
अणु
	u32 val;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret = 0;
	u8 dma_burst;
	काष्ठा dma_slave_config dma_sconfig = अणु0पूर्ण;

	val = SPI_DMA_BLK_SET(tspi->curr_dma_words - 1);
	tegra_spi_ग_लिखोl(tspi, val, SPI_DMA_BLK);

	अगर (tspi->is_packed)
		len = DIV_ROUND_UP(tspi->curr_dma_words * tspi->bytes_per_word,
					4) * 4;
	अन्यथा
		len = tspi->curr_dma_words * 4;

	/* Set attention level based on length of transfer */
	अगर (len & 0xF) अणु
		val |= SPI_TX_TRIG_1 | SPI_RX_TRIG_1;
		dma_burst = 1;
	पूर्ण अन्यथा अगर (((len) >> 4) & 0x1) अणु
		val |= SPI_TX_TRIG_4 | SPI_RX_TRIG_4;
		dma_burst = 4;
	पूर्ण अन्यथा अणु
		val |= SPI_TX_TRIG_8 | SPI_RX_TRIG_8;
		dma_burst = 8;
	पूर्ण

	अगर (!tspi->soc_data->has_पूर्णांकr_mask_reg) अणु
		अगर (tspi->cur_direction & DATA_सूची_TX)
			val |= SPI_IE_TX;

		अगर (tspi->cur_direction & DATA_सूची_RX)
			val |= SPI_IE_RX;
	पूर्ण

	tegra_spi_ग_लिखोl(tspi, val, SPI_DMA_CTL);
	tspi->dma_control_reg = val;

	dma_sconfig.device_fc = true;
	अगर (tspi->cur_direction & DATA_सूची_TX) अणु
		dma_sconfig.dst_addr = tspi->phys + SPI_TX_FIFO;
		dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.dst_maxburst = dma_burst;
		ret = dmaengine_slave_config(tspi->tx_dma_chan, &dma_sconfig);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"DMA slave config failed: %d\n", ret);
			वापस ret;
		पूर्ण

		tegra_spi_copy_client_txbuf_to_spi_txbuf(tspi, t);
		ret = tegra_spi_start_tx_dma(tspi, len);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"Starting tx dma failed, err %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX) अणु
		dma_sconfig.src_addr = tspi->phys + SPI_RX_FIFO;
		dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.src_maxburst = dma_burst;
		ret = dmaengine_slave_config(tspi->rx_dma_chan, &dma_sconfig);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"DMA slave config failed: %d\n", ret);
			वापस ret;
		पूर्ण

		/* Make the dma buffer to पढ़ो by dma */
		dma_sync_single_क्रम_device(tspi->dev, tspi->rx_dma_phys,
				tspi->dma_buf_size, DMA_FROM_DEVICE);

		ret = tegra_spi_start_rx_dma(tspi, len);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"Starting rx dma failed, err %d\n", ret);
			अगर (tspi->cur_direction & DATA_सूची_TX)
				dmaengine_terminate_all(tspi->tx_dma_chan);
			वापस ret;
		पूर्ण
	पूर्ण
	tspi->is_curr_dma_xfer = true;
	tspi->dma_control_reg = val;

	val |= SPI_DMA_EN;
	tegra_spi_ग_लिखोl(tspi, val, SPI_DMA_CTL);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_spi_start_cpu_based_transfer(
		काष्ठा tegra_spi_data *tspi, काष्ठा spi_transfer *t)
अणु
	u32 val;
	अचिन्हित cur_words;

	अगर (tspi->cur_direction & DATA_सूची_TX)
		cur_words = tegra_spi_fill_tx_fअगरo_from_client_txbuf(tspi, t);
	अन्यथा
		cur_words = tspi->curr_dma_words;

	val = SPI_DMA_BLK_SET(cur_words - 1);
	tegra_spi_ग_लिखोl(tspi, val, SPI_DMA_BLK);

	val = 0;
	अगर (tspi->cur_direction & DATA_सूची_TX)
		val |= SPI_IE_TX;

	अगर (tspi->cur_direction & DATA_सूची_RX)
		val |= SPI_IE_RX;

	tegra_spi_ग_लिखोl(tspi, val, SPI_DMA_CTL);
	tspi->dma_control_reg = val;

	tspi->is_curr_dma_xfer = false;

	val = tspi->command1_reg;
	val |= SPI_PIO;
	tegra_spi_ग_लिखोl(tspi, val, SPI_COMMAND1);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_spi_init_dma_param(काष्ठा tegra_spi_data *tspi,
			bool dma_to_memory)
अणु
	काष्ठा dma_chan *dma_chan;
	u32 *dma_buf;
	dma_addr_t dma_phys;

	dma_chan = dma_request_chan(tspi->dev, dma_to_memory ? "rx" : "tx");
	अगर (IS_ERR(dma_chan))
		वापस dev_err_probe(tspi->dev, PTR_ERR(dma_chan),
				     "Dma channel is not available\n");

	dma_buf = dma_alloc_coherent(tspi->dev, tspi->dma_buf_size,
				&dma_phys, GFP_KERNEL);
	अगर (!dma_buf) अणु
		dev_err(tspi->dev, " Not able to allocate the dma buffer\n");
		dma_release_channel(dma_chan);
		वापस -ENOMEM;
	पूर्ण

	अगर (dma_to_memory) अणु
		tspi->rx_dma_chan = dma_chan;
		tspi->rx_dma_buf = dma_buf;
		tspi->rx_dma_phys = dma_phys;
	पूर्ण अन्यथा अणु
		tspi->tx_dma_chan = dma_chan;
		tspi->tx_dma_buf = dma_buf;
		tspi->tx_dma_phys = dma_phys;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tegra_spi_deinit_dma_param(काष्ठा tegra_spi_data *tspi,
	bool dma_to_memory)
अणु
	u32 *dma_buf;
	dma_addr_t dma_phys;
	काष्ठा dma_chan *dma_chan;

	अगर (dma_to_memory) अणु
		dma_buf = tspi->rx_dma_buf;
		dma_chan = tspi->rx_dma_chan;
		dma_phys = tspi->rx_dma_phys;
		tspi->rx_dma_chan = शून्य;
		tspi->rx_dma_buf = शून्य;
	पूर्ण अन्यथा अणु
		dma_buf = tspi->tx_dma_buf;
		dma_chan = tspi->tx_dma_chan;
		dma_phys = tspi->tx_dma_phys;
		tspi->tx_dma_buf = शून्य;
		tspi->tx_dma_chan = शून्य;
	पूर्ण
	अगर (!dma_chan)
		वापस;

	dma_मुक्त_coherent(tspi->dev, tspi->dma_buf_size, dma_buf, dma_phys);
	dma_release_channel(dma_chan);
पूर्ण

अटल पूर्णांक tegra_spi_set_hw_cs_timing(काष्ठा spi_device *spi,
				      काष्ठा spi_delay *setup,
				      काष्ठा spi_delay *hold,
				      काष्ठा spi_delay *inactive)
अणु
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	u8 setup_dly, hold_dly, inactive_dly;
	u32 setup_hold;
	u32 spi_cs_timing;
	u32 inactive_cycles;
	u8 cs_state;

	अगर ((setup && setup->unit != SPI_DELAY_UNIT_SCK) ||
	    (hold && hold->unit != SPI_DELAY_UNIT_SCK) ||
	    (inactive && inactive->unit != SPI_DELAY_UNIT_SCK)) अणु
		dev_err(&spi->dev,
			"Invalid delay unit %d, should be SPI_DELAY_UNIT_SCK\n",
			SPI_DELAY_UNIT_SCK);
		वापस -EINVAL;
	पूर्ण

	setup_dly = setup ? setup->value : 0;
	hold_dly = hold ? hold->value : 0;
	inactive_dly = inactive ? inactive->value : 0;

	setup_dly = min_t(u8, setup_dly, MAX_SETUP_HOLD_CYCLES);
	hold_dly = min_t(u8, hold_dly, MAX_SETUP_HOLD_CYCLES);
	अगर (setup_dly && hold_dly) अणु
		setup_hold = SPI_SETUP_HOLD(setup_dly - 1, hold_dly - 1);
		spi_cs_timing = SPI_CS_SETUP_HOLD(tspi->spi_cs_timing1,
						  spi->chip_select,
						  setup_hold);
		अगर (tspi->spi_cs_timing1 != spi_cs_timing) अणु
			tspi->spi_cs_timing1 = spi_cs_timing;
			tegra_spi_ग_लिखोl(tspi, spi_cs_timing, SPI_CS_TIMING1);
		पूर्ण
	पूर्ण

	inactive_cycles = min_t(u8, inactive_dly, MAX_INACTIVE_CYCLES);
	अगर (inactive_cycles)
		inactive_cycles--;
	cs_state = inactive_cycles ? 0 : 1;
	spi_cs_timing = tspi->spi_cs_timing2;
	SPI_SET_CS_ACTIVE_BETWEEN_PACKETS(spi_cs_timing, spi->chip_select,
					  cs_state);
	SPI_SET_CYCLES_BETWEEN_PACKETS(spi_cs_timing, spi->chip_select,
				       inactive_cycles);
	अगर (tspi->spi_cs_timing2 != spi_cs_timing) अणु
		tspi->spi_cs_timing2 = spi_cs_timing;
		tegra_spi_ग_लिखोl(tspi, spi_cs_timing, SPI_CS_TIMING2);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 tegra_spi_setup_transfer_one(काष्ठा spi_device *spi,
					काष्ठा spi_transfer *t,
					bool is_first_of_msg,
					bool is_single_xfer)
अणु
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	काष्ठा tegra_spi_client_data *cdata = spi->controller_data;
	u32 speed = t->speed_hz;
	u8 bits_per_word = t->bits_per_word;
	u32 command1, command2;
	पूर्णांक req_mode;
	u32 tx_tap = 0, rx_tap = 0;

	अगर (speed != tspi->cur_speed) अणु
		clk_set_rate(tspi->clk, speed);
		tspi->cur_speed = speed;
	पूर्ण

	tspi->cur_spi = spi;
	tspi->cur_pos = 0;
	tspi->cur_rx_pos = 0;
	tspi->cur_tx_pos = 0;
	tspi->curr_xfer = t;

	अगर (is_first_of_msg) अणु
		tegra_spi_clear_status(tspi);

		command1 = tspi->def_command1_reg;
		command1 |= SPI_BIT_LENGTH(bits_per_word - 1);

		command1 &= ~SPI_CONTROL_MODE_MASK;
		req_mode = spi->mode & 0x3;
		अगर (req_mode == SPI_MODE_0)
			command1 |= SPI_CONTROL_MODE_0;
		अन्यथा अगर (req_mode == SPI_MODE_1)
			command1 |= SPI_CONTROL_MODE_1;
		अन्यथा अगर (req_mode == SPI_MODE_2)
			command1 |= SPI_CONTROL_MODE_2;
		अन्यथा अगर (req_mode == SPI_MODE_3)
			command1 |= SPI_CONTROL_MODE_3;

		अगर (spi->mode & SPI_LSB_FIRST)
			command1 |= SPI_LSBIT_FE;
		अन्यथा
			command1 &= ~SPI_LSBIT_FE;

		अगर (spi->mode & SPI_3WIRE)
			command1 |= SPI_BIसूचीOE;
		अन्यथा
			command1 &= ~SPI_BIसूचीOE;

		अगर (tspi->cs_control) अणु
			अगर (tspi->cs_control != spi)
				tegra_spi_ग_लिखोl(tspi, command1, SPI_COMMAND1);
			tspi->cs_control = शून्य;
		पूर्ण अन्यथा
			tegra_spi_ग_लिखोl(tspi, command1, SPI_COMMAND1);

		/* GPIO based chip select control */
		अगर (spi->cs_gpiod)
			gpiod_set_value(spi->cs_gpiod, 1);

		अगर (is_single_xfer && !(t->cs_change)) अणु
			tspi->use_hw_based_cs = true;
			command1 &= ~(SPI_CS_SW_HW | SPI_CS_SW_VAL);
		पूर्ण अन्यथा अणु
			tspi->use_hw_based_cs = false;
			command1 |= SPI_CS_SW_HW;
			अगर (spi->mode & SPI_CS_HIGH)
				command1 |= SPI_CS_SW_VAL;
			अन्यथा
				command1 &= ~SPI_CS_SW_VAL;
		पूर्ण

		अगर (tspi->last_used_cs != spi->chip_select) अणु
			अगर (cdata && cdata->tx_clk_tap_delay)
				tx_tap = cdata->tx_clk_tap_delay;
			अगर (cdata && cdata->rx_clk_tap_delay)
				rx_tap = cdata->rx_clk_tap_delay;
			command2 = SPI_TX_TAP_DELAY(tx_tap) |
				   SPI_RX_TAP_DELAY(rx_tap);
			अगर (command2 != tspi->def_command2_reg)
				tegra_spi_ग_लिखोl(tspi, command2, SPI_COMMAND2);
			tspi->last_used_cs = spi->chip_select;
		पूर्ण

	पूर्ण अन्यथा अणु
		command1 = tspi->command1_reg;
		command1 &= ~SPI_BIT_LENGTH(~0);
		command1 |= SPI_BIT_LENGTH(bits_per_word - 1);
	पूर्ण

	वापस command1;
पूर्ण

अटल पूर्णांक tegra_spi_start_transfer_one(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t, u32 command1)
अणु
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	अचिन्हित total_fअगरo_words;
	पूर्णांक ret;

	total_fअगरo_words = tegra_spi_calculate_curr_xfer_param(spi, tspi, t);

	अगर (t->rx_nbits == SPI_NBITS_DUAL || t->tx_nbits == SPI_NBITS_DUAL)
		command1 |= SPI_BOTH_EN_BIT;
	अन्यथा
		command1 &= ~SPI_BOTH_EN_BIT;

	अगर (tspi->is_packed)
		command1 |= SPI_PACKED;
	अन्यथा
		command1 &= ~SPI_PACKED;

	command1 &= ~(SPI_CS_SEL_MASK | SPI_TX_EN | SPI_RX_EN);
	tspi->cur_direction = 0;
	अगर (t->rx_buf) अणु
		command1 |= SPI_RX_EN;
		tspi->cur_direction |= DATA_सूची_RX;
	पूर्ण
	अगर (t->tx_buf) अणु
		command1 |= SPI_TX_EN;
		tspi->cur_direction |= DATA_सूची_TX;
	पूर्ण
	command1 |= SPI_CS_SEL(spi->chip_select);
	tegra_spi_ग_लिखोl(tspi, command1, SPI_COMMAND1);
	tspi->command1_reg = command1;

	dev_dbg(tspi->dev, "The def 0x%x and written 0x%x\n",
		tspi->def_command1_reg, (अचिन्हित)command1);

	ret = tegra_spi_flush_fअगरos(tspi);
	अगर (ret < 0)
		वापस ret;
	अगर (total_fअगरo_words > SPI_FIFO_DEPTH)
		ret = tegra_spi_start_dma_based_transfer(tspi, t);
	अन्यथा
		ret = tegra_spi_start_cpu_based_transfer(tspi, t);
	वापस ret;
पूर्ण

अटल काष्ठा tegra_spi_client_data
	*tegra_spi_parse_cdata_dt(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_spi_client_data *cdata;
	काष्ठा device_node *slave_np;

	slave_np = spi->dev.of_node;
	अगर (!slave_np) अणु
		dev_dbg(&spi->dev, "device node not found\n");
		वापस शून्य;
	पूर्ण

	cdata = kzalloc(माप(*cdata), GFP_KERNEL);
	अगर (!cdata)
		वापस शून्य;

	of_property_पढ़ो_u32(slave_np, "nvidia,tx-clk-tap-delay",
			     &cdata->tx_clk_tap_delay);
	of_property_पढ़ो_u32(slave_np, "nvidia,rx-clk-tap-delay",
			     &cdata->rx_clk_tap_delay);
	वापस cdata;
पूर्ण

अटल व्योम tegra_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_spi_client_data *cdata = spi->controller_data;

	spi->controller_data = शून्य;
	अगर (spi->dev.of_node)
		kमुक्त(cdata);
पूर्ण

अटल पूर्णांक tegra_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	काष्ठा tegra_spi_client_data *cdata = spi->controller_data;
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(&spi->dev, "setup %d bpw, %scpol, %scpha, %dHz\n",
		spi->bits_per_word,
		spi->mode & SPI_CPOL ? "" : "~",
		spi->mode & SPI_CPHA ? "" : "~",
		spi->max_speed_hz);

	अगर (!cdata) अणु
		cdata = tegra_spi_parse_cdata_dt(spi);
		spi->controller_data = cdata;
	पूर्ण

	ret = pm_runसमय_get_sync(tspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(tspi->dev);
		dev_err(tspi->dev, "pm runtime failed, e = %d\n", ret);
		अगर (cdata)
			tegra_spi_cleanup(spi);
		वापस ret;
	पूर्ण

	अगर (tspi->soc_data->has_पूर्णांकr_mask_reg) अणु
		val = tegra_spi_पढ़ोl(tspi, SPI_INTR_MASK);
		val &= ~SPI_INTR_ALL_MASK;
		tegra_spi_ग_लिखोl(tspi, val, SPI_INTR_MASK);
	पूर्ण

	spin_lock_irqsave(&tspi->lock, flags);
	/* GPIO based chip select control */
	अगर (spi->cs_gpiod)
		gpiod_set_value(spi->cs_gpiod, 0);

	val = tspi->def_command1_reg;
	अगर (spi->mode & SPI_CS_HIGH)
		val &= ~SPI_CS_POL_INACTIVE(spi->chip_select);
	अन्यथा
		val |= SPI_CS_POL_INACTIVE(spi->chip_select);
	tspi->def_command1_reg = val;
	tegra_spi_ग_लिखोl(tspi, tspi->def_command1_reg, SPI_COMMAND1);
	spin_unlock_irqrestore(&tspi->lock, flags);

	pm_runसमय_put(tspi->dev);
	वापस 0;
पूर्ण

अटल व्योम tegra_spi_transfer_end(काष्ठा spi_device *spi)
अणु
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(spi->master);
	पूर्णांक cs_val = (spi->mode & SPI_CS_HIGH) ? 0 : 1;

	/* GPIO based chip select control */
	अगर (spi->cs_gpiod)
		gpiod_set_value(spi->cs_gpiod, 0);

	अगर (!tspi->use_hw_based_cs) अणु
		अगर (cs_val)
			tspi->command1_reg |= SPI_CS_SW_VAL;
		अन्यथा
			tspi->command1_reg &= ~SPI_CS_SW_VAL;
		tegra_spi_ग_लिखोl(tspi, tspi->command1_reg, SPI_COMMAND1);
	पूर्ण

	tegra_spi_ग_लिखोl(tspi, tspi->def_command1_reg, SPI_COMMAND1);
पूर्ण

अटल व्योम tegra_spi_dump_regs(काष्ठा tegra_spi_data *tspi)
अणु
	dev_dbg(tspi->dev, "============ SPI REGISTER DUMP ============\n");
	dev_dbg(tspi->dev, "Command1:    0x%08x | Command2:    0x%08x\n",
		tegra_spi_पढ़ोl(tspi, SPI_COMMAND1),
		tegra_spi_पढ़ोl(tspi, SPI_COMMAND2));
	dev_dbg(tspi->dev, "DMA_CTL:     0x%08x | DMA_BLK:     0x%08x\n",
		tegra_spi_पढ़ोl(tspi, SPI_DMA_CTL),
		tegra_spi_पढ़ोl(tspi, SPI_DMA_BLK));
	dev_dbg(tspi->dev, "TRANS_STAT:  0x%08x | FIFO_STATUS: 0x%08x\n",
		tegra_spi_पढ़ोl(tspi, SPI_TRANS_STATUS),
		tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS));
पूर्ण

अटल पूर्णांक tegra_spi_transfer_one_message(काष्ठा spi_master *master,
			काष्ठा spi_message *msg)
अणु
	bool is_first_msg = true;
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(master);
	काष्ठा spi_transfer *xfer;
	काष्ठा spi_device *spi = msg->spi;
	पूर्णांक ret;
	bool skip = false;
	पूर्णांक single_xfer;

	msg->status = 0;
	msg->actual_length = 0;

	single_xfer = list_is_singular(&msg->transfers);
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		u32 cmd1;

		reinit_completion(&tspi->xfer_completion);

		cmd1 = tegra_spi_setup_transfer_one(spi, xfer, is_first_msg,
						    single_xfer);

		अगर (!xfer->len) अणु
			ret = 0;
			skip = true;
			जाओ complete_xfer;
		पूर्ण

		ret = tegra_spi_start_transfer_one(spi, xfer, cmd1);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"spi can not start transfer, err %d\n", ret);
			जाओ complete_xfer;
		पूर्ण

		is_first_msg = false;
		ret = रुको_क्रम_completion_समयout(&tspi->xfer_completion,
						SPI_DMA_TIMEOUT);
		अगर (WARN_ON(ret == 0)) अणु
			dev_err(tspi->dev,
				"spi transfer timeout, err %d\n", ret);
			अगर (tspi->is_curr_dma_xfer &&
			    (tspi->cur_direction & DATA_सूची_TX))
				dmaengine_terminate_all(tspi->tx_dma_chan);
			अगर (tspi->is_curr_dma_xfer &&
			    (tspi->cur_direction & DATA_सूची_RX))
				dmaengine_terminate_all(tspi->rx_dma_chan);
			ret = -EIO;
			tegra_spi_dump_regs(tspi);
			tegra_spi_flush_fअगरos(tspi);
			reset_control_निश्चित(tspi->rst);
			udelay(2);
			reset_control_deनिश्चित(tspi->rst);
			tspi->last_used_cs = master->num_chipselect + 1;
			जाओ complete_xfer;
		पूर्ण

		अगर (tspi->tx_status ||  tspi->rx_status) अणु
			dev_err(tspi->dev, "Error in Transfer\n");
			ret = -EIO;
			tegra_spi_dump_regs(tspi);
			जाओ complete_xfer;
		पूर्ण
		msg->actual_length += xfer->len;

complete_xfer:
		अगर (ret < 0 || skip) अणु
			tegra_spi_transfer_end(spi);
			spi_transfer_delay_exec(xfer);
			जाओ निकास;
		पूर्ण अन्यथा अगर (list_is_last(&xfer->transfer_list,
					&msg->transfers)) अणु
			अगर (xfer->cs_change)
				tspi->cs_control = spi;
			अन्यथा अणु
				tegra_spi_transfer_end(spi);
				spi_transfer_delay_exec(xfer);
			पूर्ण
		पूर्ण अन्यथा अगर (xfer->cs_change) अणु
			tegra_spi_transfer_end(spi);
			spi_transfer_delay_exec(xfer);
		पूर्ण

	पूर्ण
	ret = 0;
निकास:
	msg->status = ret;
	spi_finalize_current_message(master);
	वापस ret;
पूर्ण

अटल irqवापस_t handle_cpu_based_xfer(काष्ठा tegra_spi_data *tspi)
अणु
	काष्ठा spi_transfer *t = tspi->curr_xfer;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tspi->lock, flags);
	अगर (tspi->tx_status ||  tspi->rx_status) अणु
		dev_err(tspi->dev, "CpuXfer ERROR bit set 0x%x\n",
			tspi->status_reg);
		dev_err(tspi->dev, "CpuXfer 0x%08x:0x%08x\n",
			tspi->command1_reg, tspi->dma_control_reg);
		tegra_spi_dump_regs(tspi);
		tegra_spi_flush_fअगरos(tspi);
		complete(&tspi->xfer_completion);
		spin_unlock_irqrestore(&tspi->lock, flags);
		reset_control_निश्चित(tspi->rst);
		udelay(2);
		reset_control_deनिश्चित(tspi->rst);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX)
		tegra_spi_पढ़ो_rx_fअगरo_to_client_rxbuf(tspi, t);

	अगर (tspi->cur_direction & DATA_सूची_TX)
		tspi->cur_pos = tspi->cur_tx_pos;
	अन्यथा
		tspi->cur_pos = tspi->cur_rx_pos;

	अगर (tspi->cur_pos == t->len) अणु
		complete(&tspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	tegra_spi_calculate_curr_xfer_param(tspi->cur_spi, tspi, t);
	tegra_spi_start_cpu_based_transfer(tspi, t);
निकास:
	spin_unlock_irqrestore(&tspi->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t handle_dma_based_xfer(काष्ठा tegra_spi_data *tspi)
अणु
	काष्ठा spi_transfer *t = tspi->curr_xfer;
	दीर्घ रुको_status;
	पूर्णांक err = 0;
	अचिन्हित total_fअगरo_words;
	अचिन्हित दीर्घ flags;

	/* Abort dmas अगर any error */
	अगर (tspi->cur_direction & DATA_सूची_TX) अणु
		अगर (tspi->tx_status) अणु
			dmaengine_terminate_all(tspi->tx_dma_chan);
			err += 1;
		पूर्ण अन्यथा अणु
			रुको_status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&tspi->tx_dma_complete, SPI_DMA_TIMEOUT);
			अगर (रुको_status <= 0) अणु
				dmaengine_terminate_all(tspi->tx_dma_chan);
				dev_err(tspi->dev, "TxDma Xfer failed\n");
				err += 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX) अणु
		अगर (tspi->rx_status) अणु
			dmaengine_terminate_all(tspi->rx_dma_chan);
			err += 2;
		पूर्ण अन्यथा अणु
			रुको_status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&tspi->rx_dma_complete, SPI_DMA_TIMEOUT);
			अगर (रुको_status <= 0) अणु
				dmaengine_terminate_all(tspi->rx_dma_chan);
				dev_err(tspi->dev, "RxDma Xfer failed\n");
				err += 2;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&tspi->lock, flags);
	अगर (err) अणु
		dev_err(tspi->dev, "DmaXfer: ERROR bit set 0x%x\n",
			tspi->status_reg);
		dev_err(tspi->dev, "DmaXfer 0x%08x:0x%08x\n",
			tspi->command1_reg, tspi->dma_control_reg);
		tegra_spi_dump_regs(tspi);
		tegra_spi_flush_fअगरos(tspi);
		complete(&tspi->xfer_completion);
		spin_unlock_irqrestore(&tspi->lock, flags);
		reset_control_निश्चित(tspi->rst);
		udelay(2);
		reset_control_deनिश्चित(tspi->rst);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX)
		tegra_spi_copy_spi_rxbuf_to_client_rxbuf(tspi, t);

	अगर (tspi->cur_direction & DATA_सूची_TX)
		tspi->cur_pos = tspi->cur_tx_pos;
	अन्यथा
		tspi->cur_pos = tspi->cur_rx_pos;

	अगर (tspi->cur_pos == t->len) अणु
		complete(&tspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	/* Continue transfer in current message */
	total_fअगरo_words = tegra_spi_calculate_curr_xfer_param(tspi->cur_spi,
							tspi, t);
	अगर (total_fअगरo_words > SPI_FIFO_DEPTH)
		err = tegra_spi_start_dma_based_transfer(tspi, t);
	अन्यथा
		err = tegra_spi_start_cpu_based_transfer(tspi, t);

निकास:
	spin_unlock_irqrestore(&tspi->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_spi_isr_thपढ़ो(पूर्णांक irq, व्योम *context_data)
अणु
	काष्ठा tegra_spi_data *tspi = context_data;

	अगर (!tspi->is_curr_dma_xfer)
		वापस handle_cpu_based_xfer(tspi);
	वापस handle_dma_based_xfer(tspi);
पूर्ण

अटल irqवापस_t tegra_spi_isr(पूर्णांक irq, व्योम *context_data)
अणु
	काष्ठा tegra_spi_data *tspi = context_data;

	tspi->status_reg = tegra_spi_पढ़ोl(tspi, SPI_FIFO_STATUS);
	अगर (tspi->cur_direction & DATA_सूची_TX)
		tspi->tx_status = tspi->status_reg &
					(SPI_TX_FIFO_UNF | SPI_TX_FIFO_OVF);

	अगर (tspi->cur_direction & DATA_सूची_RX)
		tspi->rx_status = tspi->status_reg &
					(SPI_RX_FIFO_OVF | SPI_RX_FIFO_UNF);
	tegra_spi_clear_status(tspi);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल काष्ठा tegra_spi_soc_data tegra114_spi_soc_data = अणु
	.has_पूर्णांकr_mask_reg = false,
पूर्ण;

अटल काष्ठा tegra_spi_soc_data tegra124_spi_soc_data = अणु
	.has_पूर्णांकr_mask_reg = false,
पूर्ण;

अटल काष्ठा tegra_spi_soc_data tegra210_spi_soc_data = अणु
	.has_पूर्णांकr_mask_reg = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_spi_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra114-spi",
		.data	    = &tegra114_spi_soc_data,
	पूर्ण, अणु
		.compatible = "nvidia,tegra124-spi",
		.data	    = &tegra124_spi_soc_data,
	पूर्ण, अणु
		.compatible = "nvidia,tegra210-spi",
		.data	    = &tegra210_spi_soc_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_spi_of_match);

अटल पूर्णांक tegra_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master;
	काष्ठा tegra_spi_data	*tspi;
	काष्ठा resource		*r;
	पूर्णांक ret, spi_irq;
	पूर्णांक bus_num;

	master = spi_alloc_master(&pdev->dev, माप(*tspi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, master);
	tspi = spi_master_get_devdata(master);

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "spi-max-frequency",
				 &master->max_speed_hz))
		master->max_speed_hz = 25000000; /* 25MHz */

	/* the spi->mode bits understood by this driver: */
	master->use_gpio_descriptors = true;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST |
			    SPI_TX_DUAL | SPI_RX_DUAL | SPI_3WIRE;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	master->setup = tegra_spi_setup;
	master->cleanup = tegra_spi_cleanup;
	master->transfer_one_message = tegra_spi_transfer_one_message;
	master->set_cs_timing = tegra_spi_set_hw_cs_timing;
	master->num_chipselect = MAX_CHIP_SELECT;
	master->स्वतः_runसमय_pm = true;
	bus_num = of_alias_get_id(pdev->dev.of_node, "spi");
	अगर (bus_num >= 0)
		master->bus_num = bus_num;

	tspi->master = master;
	tspi->dev = &pdev->dev;
	spin_lock_init(&tspi->lock);

	tspi->soc_data = of_device_get_match_data(&pdev->dev);
	अगर (!tspi->soc_data) अणु
		dev_err(&pdev->dev, "unsupported tegra\n");
		ret = -ENODEV;
		जाओ निकास_मुक्त_master;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tspi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(tspi->base)) अणु
		ret = PTR_ERR(tspi->base);
		जाओ निकास_मुक्त_master;
	पूर्ण
	tspi->phys = r->start;

	spi_irq = platक्रमm_get_irq(pdev, 0);
	tspi->irq = spi_irq;

	tspi->clk = devm_clk_get(&pdev->dev, "spi");
	अगर (IS_ERR(tspi->clk)) अणु
		dev_err(&pdev->dev, "can not get clock\n");
		ret = PTR_ERR(tspi->clk);
		जाओ निकास_मुक्त_master;
	पूर्ण

	tspi->rst = devm_reset_control_get_exclusive(&pdev->dev, "spi");
	अगर (IS_ERR(tspi->rst)) अणु
		dev_err(&pdev->dev, "can not get reset\n");
		ret = PTR_ERR(tspi->rst);
		जाओ निकास_मुक्त_master;
	पूर्ण

	tspi->max_buf_size = SPI_FIFO_DEPTH << 2;
	tspi->dma_buf_size = DEFAULT_SPI_DMA_BUF_LEN;

	ret = tegra_spi_init_dma_param(tspi, true);
	अगर (ret < 0)
		जाओ निकास_मुक्त_master;
	ret = tegra_spi_init_dma_param(tspi, false);
	अगर (ret < 0)
		जाओ निकास_rx_dma_मुक्त;
	tspi->max_buf_size = tspi->dma_buf_size;
	init_completion(&tspi->tx_dma_complete);
	init_completion(&tspi->rx_dma_complete);

	init_completion(&tspi->xfer_completion);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = tegra_spi_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ निकास_pm_disable;
	पूर्ण

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pm runtime get failed, e = %d\n", ret);
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ निकास_pm_disable;
	पूर्ण

	reset_control_निश्चित(tspi->rst);
	udelay(2);
	reset_control_deनिश्चित(tspi->rst);
	tspi->def_command1_reg  = SPI_M_S;
	tegra_spi_ग_लिखोl(tspi, tspi->def_command1_reg, SPI_COMMAND1);
	tspi->spi_cs_timing1 = tegra_spi_पढ़ोl(tspi, SPI_CS_TIMING1);
	tspi->spi_cs_timing2 = tegra_spi_पढ़ोl(tspi, SPI_CS_TIMING2);
	tspi->def_command2_reg = tegra_spi_पढ़ोl(tspi, SPI_COMMAND2);
	tspi->last_used_cs = master->num_chipselect + 1;
	pm_runसमय_put(&pdev->dev);
	ret = request_thपढ़ोed_irq(tspi->irq, tegra_spi_isr,
				   tegra_spi_isr_thपढ़ो, IRQF_ONESHOT,
				   dev_name(&pdev->dev), tspi);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register ISR for IRQ %d\n",
			tspi->irq);
		जाओ निकास_pm_disable;
	पूर्ण

	master->dev.of_node = pdev->dev.of_node;
	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can not register to master err %d\n", ret);
		जाओ निकास_मुक्त_irq;
	पूर्ण
	वापस ret;

निकास_मुक्त_irq:
	मुक्त_irq(spi_irq, tspi);
निकास_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_spi_runसमय_suspend(&pdev->dev);
	tegra_spi_deinit_dma_param(tspi, false);
निकास_rx_dma_मुक्त:
	tegra_spi_deinit_dma_param(tspi, true);
निकास_मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा tegra_spi_data	*tspi = spi_master_get_devdata(master);

	मुक्त_irq(tspi->irq, tspi);

	अगर (tspi->tx_dma_chan)
		tegra_spi_deinit_dma_param(tspi, false);

	अगर (tspi->rx_dma_chan)
		tegra_spi_deinit_dma_param(tspi, true);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_spi_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);

	वापस spi_master_suspend(master);
पूर्ण

अटल पूर्णांक tegra_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		dev_err(dev, "pm runtime failed, e = %d\n", ret);
		वापस ret;
	पूर्ण
	tegra_spi_ग_लिखोl(tspi, tspi->command1_reg, SPI_COMMAND1);
	tegra_spi_ग_लिखोl(tspi, tspi->def_command2_reg, SPI_COMMAND2);
	tspi->last_used_cs = master->num_chipselect + 1;
	pm_runसमय_put(dev);

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tegra_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(master);

	/* Flush all ग_लिखो which are in PPSB queue by पढ़ोing back */
	tegra_spi_पढ़ोl(tspi, SPI_COMMAND1);

	clk_disable_unprepare(tspi->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_spi_data *tspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(tspi->clk);
	अगर (ret < 0) अणु
		dev_err(tspi->dev, "clk_prepare failed: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_spi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_spi_runसमय_suspend,
		tegra_spi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_spi_suspend, tegra_spi_resume)
पूर्ण;
अटल काष्ठा platक्रमm_driver tegra_spi_driver = अणु
	.driver = अणु
		.name		= "spi-tegra114",
		.pm		= &tegra_spi_pm_ops,
		.of_match_table	= tegra_spi_of_match,
	पूर्ण,
	.probe =	tegra_spi_probe,
	.हटाओ =	tegra_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_spi_driver);

MODULE_ALIAS("platform:spi-tegra114");
MODULE_DESCRIPTION("NVIDIA Tegra114 SPI Controller Driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
