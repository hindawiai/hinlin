<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI driver क्रम Nvidia's Tegra20/Tegra30 SLINK Controller.
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
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

#घोषणा SLINK_COMMAND			0x000
#घोषणा SLINK_BIT_LENGTH(x)		(((x) & 0x1f) << 0)
#घोषणा SLINK_WORD_SIZE(x)		(((x) & 0x1f) << 5)
#घोषणा SLINK_BOTH_EN			(1 << 10)
#घोषणा SLINK_CS_SW			(1 << 11)
#घोषणा SLINK_CS_VALUE			(1 << 12)
#घोषणा SLINK_CS_POLARITY		(1 << 13)
#घोषणा SLINK_IDLE_SDA_DRIVE_LOW	(0 << 16)
#घोषणा SLINK_IDLE_SDA_DRIVE_HIGH	(1 << 16)
#घोषणा SLINK_IDLE_SDA_PULL_LOW		(2 << 16)
#घोषणा SLINK_IDLE_SDA_PULL_HIGH	(3 << 16)
#घोषणा SLINK_IDLE_SDA_MASK		(3 << 16)
#घोषणा SLINK_CS_POLARITY1		(1 << 20)
#घोषणा SLINK_CK_SDA			(1 << 21)
#घोषणा SLINK_CS_POLARITY2		(1 << 22)
#घोषणा SLINK_CS_POLARITY3		(1 << 23)
#घोषणा SLINK_IDLE_SCLK_DRIVE_LOW	(0 << 24)
#घोषणा SLINK_IDLE_SCLK_DRIVE_HIGH	(1 << 24)
#घोषणा SLINK_IDLE_SCLK_PULL_LOW	(2 << 24)
#घोषणा SLINK_IDLE_SCLK_PULL_HIGH	(3 << 24)
#घोषणा SLINK_IDLE_SCLK_MASK		(3 << 24)
#घोषणा SLINK_M_S			(1 << 28)
#घोषणा SLINK_WAIT			(1 << 29)
#घोषणा SLINK_GO			(1 << 30)
#घोषणा SLINK_ENB			(1 << 31)

#घोषणा SLINK_MODES			(SLINK_IDLE_SCLK_MASK | SLINK_CK_SDA)

#घोषणा SLINK_COMMAND2			0x004
#घोषणा SLINK_LSBFE			(1 << 0)
#घोषणा SLINK_SSOE			(1 << 1)
#घोषणा SLINK_SPIE			(1 << 4)
#घोषणा SLINK_BIसूचीOE			(1 << 6)
#घोषणा SLINK_MODFEN			(1 << 7)
#घोषणा SLINK_INT_SIZE(x)		(((x) & 0x1f) << 8)
#घोषणा SLINK_CS_ACTIVE_BETWEEN		(1 << 17)
#घोषणा SLINK_SS_EN_CS(x)		(((x) & 0x3) << 18)
#घोषणा SLINK_SS_SETUP(x)		(((x) & 0x3) << 20)
#घोषणा SLINK_FIFO_REFILLS_0		(0 << 22)
#घोषणा SLINK_FIFO_REFILLS_1		(1 << 22)
#घोषणा SLINK_FIFO_REFILLS_2		(2 << 22)
#घोषणा SLINK_FIFO_REFILLS_3		(3 << 22)
#घोषणा SLINK_FIFO_REFILLS_MASK		(3 << 22)
#घोषणा SLINK_WAIT_PACK_INT(x)		(((x) & 0x7) << 26)
#घोषणा SLINK_SPC0			(1 << 29)
#घोषणा SLINK_TXEN			(1 << 30)
#घोषणा SLINK_RXEN			(1 << 31)

#घोषणा SLINK_STATUS			0x008
#घोषणा SLINK_COUNT(val)		(((val) >> 0) & 0x1f)
#घोषणा SLINK_WORD(val)			(((val) >> 5) & 0x1f)
#घोषणा SLINK_BLK_CNT(val)		(((val) >> 0) & 0xffff)
#घोषणा SLINK_MODF			(1 << 16)
#घोषणा SLINK_RX_UNF			(1 << 18)
#घोषणा SLINK_TX_OVF			(1 << 19)
#घोषणा SLINK_TX_FULL			(1 << 20)
#घोषणा SLINK_TX_EMPTY			(1 << 21)
#घोषणा SLINK_RX_FULL			(1 << 22)
#घोषणा SLINK_RX_EMPTY			(1 << 23)
#घोषणा SLINK_TX_UNF			(1 << 24)
#घोषणा SLINK_RX_OVF			(1 << 25)
#घोषणा SLINK_TX_FLUSH			(1 << 26)
#घोषणा SLINK_RX_FLUSH			(1 << 27)
#घोषणा SLINK_SCLK			(1 << 28)
#घोषणा SLINK_ERR			(1 << 29)
#घोषणा SLINK_RDY			(1 << 30)
#घोषणा SLINK_BSY			(1 << 31)
#घोषणा SLINK_FIFO_ERROR		(SLINK_TX_OVF | SLINK_RX_UNF |	\
					SLINK_TX_UNF | SLINK_RX_OVF)

#घोषणा SLINK_FIFO_EMPTY		(SLINK_TX_EMPTY | SLINK_RX_EMPTY)

#घोषणा SLINK_MAS_DATA			0x010
#घोषणा SLINK_SLAVE_DATA		0x014

#घोषणा SLINK_DMA_CTL			0x018
#घोषणा SLINK_DMA_BLOCK_SIZE(x)		(((x) & 0xffff) << 0)
#घोषणा SLINK_TX_TRIG_1			(0 << 16)
#घोषणा SLINK_TX_TRIG_4			(1 << 16)
#घोषणा SLINK_TX_TRIG_8			(2 << 16)
#घोषणा SLINK_TX_TRIG_16		(3 << 16)
#घोषणा SLINK_TX_TRIG_MASK		(3 << 16)
#घोषणा SLINK_RX_TRIG_1			(0 << 18)
#घोषणा SLINK_RX_TRIG_4			(1 << 18)
#घोषणा SLINK_RX_TRIG_8			(2 << 18)
#घोषणा SLINK_RX_TRIG_16		(3 << 18)
#घोषणा SLINK_RX_TRIG_MASK		(3 << 18)
#घोषणा SLINK_PACKED			(1 << 20)
#घोषणा SLINK_PACK_SIZE_4		(0 << 21)
#घोषणा SLINK_PACK_SIZE_8		(1 << 21)
#घोषणा SLINK_PACK_SIZE_16		(2 << 21)
#घोषणा SLINK_PACK_SIZE_32		(3 << 21)
#घोषणा SLINK_PACK_SIZE_MASK		(3 << 21)
#घोषणा SLINK_IE_TXC			(1 << 26)
#घोषणा SLINK_IE_RXC			(1 << 27)
#घोषणा SLINK_DMA_EN			(1 << 31)

#घोषणा SLINK_STATUS2			0x01c
#घोषणा SLINK_TX_FIFO_EMPTY_COUNT(val)	(((val) & 0x3f) >> 0)
#घोषणा SLINK_RX_FIFO_FULL_COUNT(val)	(((val) & 0x3f0000) >> 16)
#घोषणा SLINK_SS_HOLD_TIME(val)		(((val) & 0xF) << 6)

#घोषणा SLINK_TX_FIFO			0x100
#घोषणा SLINK_RX_FIFO			0x180

#घोषणा DATA_सूची_TX			(1 << 0)
#घोषणा DATA_सूची_RX			(1 << 1)

#घोषणा SLINK_DMA_TIMEOUT		(msecs_to_jअगरfies(1000))

#घोषणा DEFAULT_SPI_DMA_BUF_LEN		(16*1024)
#घोषणा TX_FIFO_EMPTY_COUNT_MAX		SLINK_TX_FIFO_EMPTY_COUNT(0x20)
#घोषणा RX_FIFO_FULL_COUNT_ZERO		SLINK_RX_FIFO_FULL_COUNT(0)

#घोषणा SLINK_STATUS2_RESET \
	(TX_FIFO_EMPTY_COUNT_MAX | RX_FIFO_FULL_COUNT_ZERO << 16)

#घोषणा MAX_CHIP_SELECT			4
#घोषणा SLINK_FIFO_DEPTH		32

काष्ठा tegra_slink_chip_data अणु
	bool cs_hold_समय;
पूर्ण;

काष्ठा tegra_slink_data अणु
	काष्ठा device				*dev;
	काष्ठा spi_master			*master;
	स्थिर काष्ठा tegra_slink_chip_data	*chip_data;
	spinlock_t				lock;

	काष्ठा clk				*clk;
	काष्ठा reset_control			*rst;
	व्योम __iomem				*base;
	phys_addr_t				phys;
	अचिन्हित				irq;
	u32					cur_speed;

	काष्ठा spi_device			*cur_spi;
	अचिन्हित				cur_pos;
	अचिन्हित				cur_len;
	अचिन्हित				words_per_32bit;
	अचिन्हित				bytes_per_word;
	अचिन्हित				curr_dma_words;
	अचिन्हित				cur_direction;

	अचिन्हित				cur_rx_pos;
	अचिन्हित				cur_tx_pos;

	अचिन्हित				dma_buf_size;
	अचिन्हित				max_buf_size;
	bool					is_curr_dma_xfer;

	काष्ठा completion			rx_dma_complete;
	काष्ठा completion			tx_dma_complete;

	u32					tx_status;
	u32					rx_status;
	u32					status_reg;
	bool					is_packed;
	u32					packed_size;

	u32					command_reg;
	u32					command2_reg;
	u32					dma_control_reg;
	u32					def_command_reg;
	u32					def_command2_reg;

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

अटल पूर्णांक tegra_slink_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक tegra_slink_runसमय_resume(काष्ठा device *dev);

अटल अंतरभूत u32 tegra_slink_पढ़ोl(काष्ठा tegra_slink_data *tspi,
		अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(tspi->base + reg);
पूर्ण

अटल अंतरभूत व्योम tegra_slink_ग_लिखोl(काष्ठा tegra_slink_data *tspi,
		u32 val, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोl(val, tspi->base + reg);

	/* Read back रेजिस्टर to make sure that रेजिस्टर ग_लिखोs completed */
	अगर (reg != SLINK_TX_FIFO)
		पढ़ोl(tspi->base + SLINK_MAS_DATA);
पूर्ण

अटल व्योम tegra_slink_clear_status(काष्ठा tegra_slink_data *tspi)
अणु
	u32 val_ग_लिखो;

	tegra_slink_पढ़ोl(tspi, SLINK_STATUS);

	/* Write 1 to clear status रेजिस्टर */
	val_ग_लिखो = SLINK_RDY | SLINK_FIFO_ERROR;
	tegra_slink_ग_लिखोl(tspi, val_ग_लिखो, SLINK_STATUS);
पूर्ण

अटल u32 tegra_slink_get_packed_size(काष्ठा tegra_slink_data *tspi,
				  काष्ठा spi_transfer *t)
अणु
	चयन (tspi->bytes_per_word) अणु
	हाल 0:
		वापस SLINK_PACK_SIZE_4;
	हाल 1:
		वापस SLINK_PACK_SIZE_8;
	हाल 2:
		वापस SLINK_PACK_SIZE_16;
	हाल 4:
		वापस SLINK_PACK_SIZE_32;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अचिन्हित tegra_slink_calculate_curr_xfer_param(
	काष्ठा spi_device *spi, काष्ठा tegra_slink_data *tspi,
	काष्ठा spi_transfer *t)
अणु
	अचिन्हित reमुख्य_len = t->len - tspi->cur_pos;
	अचिन्हित max_word;
	अचिन्हित bits_per_word;
	अचिन्हित max_len;
	अचिन्हित total_fअगरo_words;

	bits_per_word = t->bits_per_word;
	tspi->bytes_per_word = DIV_ROUND_UP(bits_per_word, 8);

	अगर (bits_per_word == 8 || bits_per_word == 16) अणु
		tspi->is_packed = true;
		tspi->words_per_32bit = 32/bits_per_word;
	पूर्ण अन्यथा अणु
		tspi->is_packed = false;
		tspi->words_per_32bit = 1;
	पूर्ण
	tspi->packed_size = tegra_slink_get_packed_size(tspi, t);

	अगर (tspi->is_packed) अणु
		max_len = min(reमुख्य_len, tspi->max_buf_size);
		tspi->curr_dma_words = max_len/tspi->bytes_per_word;
		total_fअगरo_words = max_len/4;
	पूर्ण अन्यथा अणु
		max_word = (reमुख्य_len - 1) / tspi->bytes_per_word + 1;
		max_word = min(max_word, tspi->max_buf_size/4);
		tspi->curr_dma_words = max_word;
		total_fअगरo_words = max_word;
	पूर्ण
	वापस total_fअगरo_words;
पूर्ण

अटल अचिन्हित tegra_slink_fill_tx_fअगरo_from_client_txbuf(
	काष्ठा tegra_slink_data *tspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित nbytes;
	अचिन्हित tx_empty_count;
	u32 fअगरo_status;
	अचिन्हित max_n_32bit;
	अचिन्हित i, count;
	अचिन्हित पूर्णांक written_words;
	अचिन्हित fअगरo_words_left;
	u8 *tx_buf = (u8 *)t->tx_buf + tspi->cur_tx_pos;

	fअगरo_status = tegra_slink_पढ़ोl(tspi, SLINK_STATUS2);
	tx_empty_count = SLINK_TX_FIFO_EMPTY_COUNT(fअगरo_status);

	अगर (tspi->is_packed) अणु
		fअगरo_words_left = tx_empty_count * tspi->words_per_32bit;
		written_words = min(fअगरo_words_left, tspi->curr_dma_words);
		nbytes = written_words * tspi->bytes_per_word;
		max_n_32bit = DIV_ROUND_UP(nbytes, 4);
		क्रम (count = 0; count < max_n_32bit; count++) अणु
			u32 x = 0;
			क्रम (i = 0; (i < 4) && nbytes; i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegra_slink_ग_लिखोl(tspi, x, SLINK_TX_FIFO);
		पूर्ण
	पूर्ण अन्यथा अणु
		max_n_32bit = min(tspi->curr_dma_words,  tx_empty_count);
		written_words = max_n_32bit;
		nbytes = written_words * tspi->bytes_per_word;
		क्रम (count = 0; count < max_n_32bit; count++) अणु
			u32 x = 0;
			क्रम (i = 0; nbytes && (i < tspi->bytes_per_word);
							i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegra_slink_ग_लिखोl(tspi, x, SLINK_TX_FIFO);
		पूर्ण
	पूर्ण
	tspi->cur_tx_pos += written_words * tspi->bytes_per_word;
	वापस written_words;
पूर्ण

अटल अचिन्हित पूर्णांक tegra_slink_पढ़ो_rx_fअगरo_to_client_rxbuf(
		काष्ठा tegra_slink_data *tspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित rx_full_count;
	u32 fअगरo_status;
	अचिन्हित i, count;
	अचिन्हित पूर्णांक पढ़ो_words = 0;
	अचिन्हित len;
	u8 *rx_buf = (u8 *)t->rx_buf + tspi->cur_rx_pos;

	fअगरo_status = tegra_slink_पढ़ोl(tspi, SLINK_STATUS2);
	rx_full_count = SLINK_RX_FIFO_FULL_COUNT(fअगरo_status);
	अगर (tspi->is_packed) अणु
		len = tspi->curr_dma_words * tspi->bytes_per_word;
		क्रम (count = 0; count < rx_full_count; count++) अणु
			u32 x = tegra_slink_पढ़ोl(tspi, SLINK_RX_FIFO);
			क्रम (i = 0; len && (i < 4); i++, len--)
				*rx_buf++ = (x >> i*8) & 0xFF;
		पूर्ण
		tspi->cur_rx_pos += tspi->curr_dma_words * tspi->bytes_per_word;
		पढ़ो_words += tspi->curr_dma_words;
	पूर्ण अन्यथा अणु
		क्रम (count = 0; count < rx_full_count; count++) अणु
			u32 x = tegra_slink_पढ़ोl(tspi, SLINK_RX_FIFO);
			क्रम (i = 0; (i < tspi->bytes_per_word); i++)
				*rx_buf++ = (x >> (i*8)) & 0xFF;
		पूर्ण
		tspi->cur_rx_pos += rx_full_count * tspi->bytes_per_word;
		पढ़ो_words += rx_full_count;
	पूर्ण
	वापस पढ़ो_words;
पूर्ण

अटल व्योम tegra_slink_copy_client_txbuf_to_spi_txbuf(
		काष्ठा tegra_slink_data *tspi, काष्ठा spi_transfer *t)
अणु
	/* Make the dma buffer to पढ़ो by cpu */
	dma_sync_single_क्रम_cpu(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);

	अगर (tspi->is_packed) अणु
		अचिन्हित len = tspi->curr_dma_words * tspi->bytes_per_word;
		स_नकल(tspi->tx_dma_buf, t->tx_buf + tspi->cur_pos, len);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक count;
		u8 *tx_buf = (u8 *)t->tx_buf + tspi->cur_tx_pos;
		अचिन्हित consume = tspi->curr_dma_words * tspi->bytes_per_word;

		क्रम (count = 0; count < tspi->curr_dma_words; count++) अणु
			u32 x = 0;
			क्रम (i = 0; consume && (i < tspi->bytes_per_word);
							i++, consume--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tspi->tx_dma_buf[count] = x;
		पूर्ण
	पूर्ण
	tspi->cur_tx_pos += tspi->curr_dma_words * tspi->bytes_per_word;

	/* Make the dma buffer to पढ़ो by dma */
	dma_sync_single_क्रम_device(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);
पूर्ण

अटल व्योम tegra_slink_copy_spi_rxbuf_to_client_rxbuf(
		काष्ठा tegra_slink_data *tspi, काष्ठा spi_transfer *t)
अणु
	अचिन्हित len;

	/* Make the dma buffer to पढ़ो by cpu */
	dma_sync_single_क्रम_cpu(tspi->dev, tspi->rx_dma_phys,
		tspi->dma_buf_size, DMA_FROM_DEVICE);

	अगर (tspi->is_packed) अणु
		len = tspi->curr_dma_words * tspi->bytes_per_word;
		स_नकल(t->rx_buf + tspi->cur_rx_pos, tspi->rx_dma_buf, len);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक count;
		अचिन्हित अक्षर *rx_buf = t->rx_buf + tspi->cur_rx_pos;
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;

		क्रम (count = 0; count < tspi->curr_dma_words; count++) अणु
			u32 x = tspi->rx_dma_buf[count] & rx_mask;
			क्रम (i = 0; (i < tspi->bytes_per_word); i++)
				*rx_buf++ = (x >> (i*8)) & 0xFF;
		पूर्ण
	पूर्ण
	tspi->cur_rx_pos += tspi->curr_dma_words * tspi->bytes_per_word;

	/* Make the dma buffer to पढ़ो by dma */
	dma_sync_single_क्रम_device(tspi->dev, tspi->rx_dma_phys,
		tspi->dma_buf_size, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम tegra_slink_dma_complete(व्योम *args)
अणु
	काष्ठा completion *dma_complete = args;

	complete(dma_complete);
पूर्ण

अटल पूर्णांक tegra_slink_start_tx_dma(काष्ठा tegra_slink_data *tspi, पूर्णांक len)
अणु
	reinit_completion(&tspi->tx_dma_complete);
	tspi->tx_dma_desc = dmaengine_prep_slave_single(tspi->tx_dma_chan,
				tspi->tx_dma_phys, len, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);
	अगर (!tspi->tx_dma_desc) अणु
		dev_err(tspi->dev, "Not able to get desc for Tx\n");
		वापस -EIO;
	पूर्ण

	tspi->tx_dma_desc->callback = tegra_slink_dma_complete;
	tspi->tx_dma_desc->callback_param = &tspi->tx_dma_complete;

	dmaengine_submit(tspi->tx_dma_desc);
	dma_async_issue_pending(tspi->tx_dma_chan);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_start_rx_dma(काष्ठा tegra_slink_data *tspi, पूर्णांक len)
अणु
	reinit_completion(&tspi->rx_dma_complete);
	tspi->rx_dma_desc = dmaengine_prep_slave_single(tspi->rx_dma_chan,
				tspi->rx_dma_phys, len, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT |  DMA_CTRL_ACK);
	अगर (!tspi->rx_dma_desc) अणु
		dev_err(tspi->dev, "Not able to get desc for Rx\n");
		वापस -EIO;
	पूर्ण

	tspi->rx_dma_desc->callback = tegra_slink_dma_complete;
	tspi->rx_dma_desc->callback_param = &tspi->rx_dma_complete;

	dmaengine_submit(tspi->rx_dma_desc);
	dma_async_issue_pending(tspi->rx_dma_chan);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_start_dma_based_transfer(
		काष्ठा tegra_slink_data *tspi, काष्ठा spi_transfer *t)
अणु
	u32 val;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret = 0;
	u32 status;

	/* Make sure that Rx and Tx fअगरo are empty */
	status = tegra_slink_पढ़ोl(tspi, SLINK_STATUS);
	अगर ((status & SLINK_FIFO_EMPTY) != SLINK_FIFO_EMPTY) अणु
		dev_err(tspi->dev, "Rx/Tx fifo are not empty status 0x%08x\n",
			(अचिन्हित)status);
		वापस -EIO;
	पूर्ण

	val = SLINK_DMA_BLOCK_SIZE(tspi->curr_dma_words - 1);
	val |= tspi->packed_size;
	अगर (tspi->is_packed)
		len = DIV_ROUND_UP(tspi->curr_dma_words * tspi->bytes_per_word,
					4) * 4;
	अन्यथा
		len = tspi->curr_dma_words * 4;

	/* Set attention level based on length of transfer */
	अगर (len & 0xF)
		val |= SLINK_TX_TRIG_1 | SLINK_RX_TRIG_1;
	अन्यथा अगर (((len) >> 4) & 0x1)
		val |= SLINK_TX_TRIG_4 | SLINK_RX_TRIG_4;
	अन्यथा
		val |= SLINK_TX_TRIG_8 | SLINK_RX_TRIG_8;

	अगर (tspi->cur_direction & DATA_सूची_TX)
		val |= SLINK_IE_TXC;

	अगर (tspi->cur_direction & DATA_सूची_RX)
		val |= SLINK_IE_RXC;

	tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
	tspi->dma_control_reg = val;

	अगर (tspi->cur_direction & DATA_सूची_TX) अणु
		tegra_slink_copy_client_txbuf_to_spi_txbuf(tspi, t);
		wmb();
		ret = tegra_slink_start_tx_dma(tspi, len);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"Starting tx dma failed, err %d\n", ret);
			वापस ret;
		पूर्ण

		/* Wait क्रम tx fअगरo to be fill beक्रमe starting slink */
		status = tegra_slink_पढ़ोl(tspi, SLINK_STATUS);
		जबतक (!(status & SLINK_TX_FULL))
			status = tegra_slink_पढ़ोl(tspi, SLINK_STATUS);
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX) अणु
		/* Make the dma buffer to पढ़ो by dma */
		dma_sync_single_क्रम_device(tspi->dev, tspi->rx_dma_phys,
				tspi->dma_buf_size, DMA_FROM_DEVICE);

		ret = tegra_slink_start_rx_dma(tspi, len);
		अगर (ret < 0) अणु
			dev_err(tspi->dev,
				"Starting rx dma failed, err %d\n", ret);
			अगर (tspi->cur_direction & DATA_सूची_TX)
				dmaengine_terminate_all(tspi->tx_dma_chan);
			वापस ret;
		पूर्ण
	पूर्ण
	tspi->is_curr_dma_xfer = true;
	अगर (tspi->is_packed) अणु
		val |= SLINK_PACKED;
		tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
		/* HW need small delay after settign Packed mode */
		udelay(1);
	पूर्ण
	tspi->dma_control_reg = val;

	val |= SLINK_DMA_EN;
	tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_slink_start_cpu_based_transfer(
		काष्ठा tegra_slink_data *tspi, काष्ठा spi_transfer *t)
अणु
	u32 val;
	अचिन्हित cur_words;

	val = tspi->packed_size;
	अगर (tspi->cur_direction & DATA_सूची_TX)
		val |= SLINK_IE_TXC;

	अगर (tspi->cur_direction & DATA_सूची_RX)
		val |= SLINK_IE_RXC;

	tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
	tspi->dma_control_reg = val;

	अगर (tspi->cur_direction & DATA_सूची_TX)
		cur_words = tegra_slink_fill_tx_fअगरo_from_client_txbuf(tspi, t);
	अन्यथा
		cur_words = tspi->curr_dma_words;
	val |= SLINK_DMA_BLOCK_SIZE(cur_words - 1);
	tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
	tspi->dma_control_reg = val;

	tspi->is_curr_dma_xfer = false;
	अगर (tspi->is_packed) अणु
		val |= SLINK_PACKED;
		tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
		udelay(1);
		wmb();
	पूर्ण
	tspi->dma_control_reg = val;
	val |= SLINK_DMA_EN;
	tegra_slink_ग_लिखोl(tspi, val, SLINK_DMA_CTL);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_init_dma_param(काष्ठा tegra_slink_data *tspi,
			bool dma_to_memory)
अणु
	काष्ठा dma_chan *dma_chan;
	u32 *dma_buf;
	dma_addr_t dma_phys;
	पूर्णांक ret;
	काष्ठा dma_slave_config dma_sconfig;

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
		dma_sconfig.src_addr = tspi->phys + SLINK_RX_FIFO;
		dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.src_maxburst = 0;
	पूर्ण अन्यथा अणु
		dma_sconfig.dst_addr = tspi->phys + SLINK_TX_FIFO;
		dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.dst_maxburst = 0;
	पूर्ण

	ret = dmaengine_slave_config(dma_chan, &dma_sconfig);
	अगर (ret)
		जाओ scrub;
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

scrub:
	dma_मुक्त_coherent(tspi->dev, tspi->dma_buf_size, dma_buf, dma_phys);
	dma_release_channel(dma_chan);
	वापस ret;
पूर्ण

अटल व्योम tegra_slink_deinit_dma_param(काष्ठा tegra_slink_data *tspi,
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

अटल पूर्णांक tegra_slink_start_transfer_one(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t)
अणु
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(spi->master);
	u32 speed;
	u8 bits_per_word;
	अचिन्हित total_fअगरo_words;
	पूर्णांक ret;
	u32 command;
	u32 command2;

	bits_per_word = t->bits_per_word;
	speed = t->speed_hz;
	अगर (speed != tspi->cur_speed) अणु
		clk_set_rate(tspi->clk, speed * 4);
		tspi->cur_speed = speed;
	पूर्ण

	tspi->cur_spi = spi;
	tspi->cur_pos = 0;
	tspi->cur_rx_pos = 0;
	tspi->cur_tx_pos = 0;
	tspi->curr_xfer = t;
	total_fअगरo_words = tegra_slink_calculate_curr_xfer_param(spi, tspi, t);

	command = tspi->command_reg;
	command &= ~SLINK_BIT_LENGTH(~0);
	command |= SLINK_BIT_LENGTH(bits_per_word - 1);

	command2 = tspi->command2_reg;
	command2 &= ~(SLINK_RXEN | SLINK_TXEN);

	tspi->cur_direction = 0;
	अगर (t->rx_buf) अणु
		command2 |= SLINK_RXEN;
		tspi->cur_direction |= DATA_सूची_RX;
	पूर्ण
	अगर (t->tx_buf) अणु
		command2 |= SLINK_TXEN;
		tspi->cur_direction |= DATA_सूची_TX;
	पूर्ण

	/*
	 * Writing to the command2 रेजिस्टर bevore the command रेजिस्टर prevents
	 * a spike in chip_select line 0. This selects the chip_select line
	 * beक्रमe changing the chip_select value.
	 */
	tegra_slink_ग_लिखोl(tspi, command2, SLINK_COMMAND2);
	tspi->command2_reg = command2;

	tegra_slink_ग_लिखोl(tspi, command, SLINK_COMMAND);
	tspi->command_reg = command;

	अगर (total_fअगरo_words > SLINK_FIFO_DEPTH)
		ret = tegra_slink_start_dma_based_transfer(tspi, t);
	अन्यथा
		ret = tegra_slink_start_cpu_based_transfer(tspi, t);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_slink_setup(काष्ठा spi_device *spi)
अणु
	अटल स्थिर u32 cs_pol_bit[MAX_CHIP_SELECT] = अणु
			SLINK_CS_POLARITY,
			SLINK_CS_POLARITY1,
			SLINK_CS_POLARITY2,
			SLINK_CS_POLARITY3,
	पूर्ण;

	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(spi->master);
	u32 val;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(&spi->dev, "setup %d bpw, %scpol, %scpha, %dHz\n",
		spi->bits_per_word,
		spi->mode & SPI_CPOL ? "" : "~",
		spi->mode & SPI_CPHA ? "" : "~",
		spi->max_speed_hz);

	ret = pm_runसमय_get_sync(tspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(tspi->dev);
		dev_err(tspi->dev, "pm runtime failed, e = %d\n", ret);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&tspi->lock, flags);
	val = tspi->def_command_reg;
	अगर (spi->mode & SPI_CS_HIGH)
		val |= cs_pol_bit[spi->chip_select];
	अन्यथा
		val &= ~cs_pol_bit[spi->chip_select];
	tspi->def_command_reg = val;
	tegra_slink_ग_लिखोl(tspi, tspi->def_command_reg, SLINK_COMMAND);
	spin_unlock_irqrestore(&tspi->lock, flags);

	pm_runसमय_put(tspi->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_prepare_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *msg)
अणु
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = msg->spi;

	tegra_slink_clear_status(tspi);

	tspi->command_reg = tspi->def_command_reg;
	tspi->command_reg |= SLINK_CS_SW | SLINK_CS_VALUE;

	tspi->command2_reg = tspi->def_command2_reg;
	tspi->command2_reg |= SLINK_SS_EN_CS(spi->chip_select);

	tspi->command_reg &= ~SLINK_MODES;
	अगर (spi->mode & SPI_CPHA)
		tspi->command_reg |= SLINK_CK_SDA;

	अगर (spi->mode & SPI_CPOL)
		tspi->command_reg |= SLINK_IDLE_SCLK_DRIVE_HIGH;
	अन्यथा
		tspi->command_reg |= SLINK_IDLE_SCLK_DRIVE_LOW;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_transfer_one(काष्ठा spi_master *master,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	reinit_completion(&tspi->xfer_completion);
	ret = tegra_slink_start_transfer_one(spi, xfer);
	अगर (ret < 0) अणु
		dev_err(tspi->dev,
			"spi can not start transfer, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&tspi->xfer_completion,
					  SLINK_DMA_TIMEOUT);
	अगर (WARN_ON(ret == 0)) अणु
		dev_err(tspi->dev,
			"spi transfer timeout, err %d\n", ret);
		वापस -EIO;
	पूर्ण

	अगर (tspi->tx_status)
		वापस tspi->tx_status;
	अगर (tspi->rx_status)
		वापस tspi->rx_status;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_unprepare_message(काष्ठा spi_master *master,
					 काष्ठा spi_message *msg)
अणु
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(master);

	tegra_slink_ग_लिखोl(tspi, tspi->def_command_reg, SLINK_COMMAND);
	tegra_slink_ग_लिखोl(tspi, tspi->def_command2_reg, SLINK_COMMAND2);

	वापस 0;
पूर्ण

अटल irqवापस_t handle_cpu_based_xfer(काष्ठा tegra_slink_data *tspi)
अणु
	काष्ठा spi_transfer *t = tspi->curr_xfer;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tspi->lock, flags);
	अगर (tspi->tx_status ||  tspi->rx_status ||
				(tspi->status_reg & SLINK_BSY)) अणु
		dev_err(tspi->dev,
			"CpuXfer ERROR bit set 0x%x\n", tspi->status_reg);
		dev_err(tspi->dev,
			"CpuXfer 0x%08x:0x%08x:0x%08x\n", tspi->command_reg,
				tspi->command2_reg, tspi->dma_control_reg);
		reset_control_निश्चित(tspi->rst);
		udelay(2);
		reset_control_deनिश्चित(tspi->rst);
		complete(&tspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX)
		tegra_slink_पढ़ो_rx_fअगरo_to_client_rxbuf(tspi, t);

	अगर (tspi->cur_direction & DATA_सूची_TX)
		tspi->cur_pos = tspi->cur_tx_pos;
	अन्यथा
		tspi->cur_pos = tspi->cur_rx_pos;

	अगर (tspi->cur_pos == t->len) अणु
		complete(&tspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	tegra_slink_calculate_curr_xfer_param(tspi->cur_spi, tspi, t);
	tegra_slink_start_cpu_based_transfer(tspi, t);
निकास:
	spin_unlock_irqrestore(&tspi->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t handle_dma_based_xfer(काष्ठा tegra_slink_data *tspi)
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
				&tspi->tx_dma_complete, SLINK_DMA_TIMEOUT);
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
				&tspi->rx_dma_complete, SLINK_DMA_TIMEOUT);
			अगर (रुको_status <= 0) अणु
				dmaengine_terminate_all(tspi->rx_dma_chan);
				dev_err(tspi->dev, "RxDma Xfer failed\n");
				err += 2;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&tspi->lock, flags);
	अगर (err) अणु
		dev_err(tspi->dev,
			"DmaXfer: ERROR bit set 0x%x\n", tspi->status_reg);
		dev_err(tspi->dev,
			"DmaXfer 0x%08x:0x%08x:0x%08x\n", tspi->command_reg,
				tspi->command2_reg, tspi->dma_control_reg);
		reset_control_निश्चित(tspi->rst);
		udelay(2);
		reset_control_निश्चित(tspi->rst);
		complete(&tspi->xfer_completion);
		spin_unlock_irqrestore(&tspi->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (tspi->cur_direction & DATA_सूची_RX)
		tegra_slink_copy_spi_rxbuf_to_client_rxbuf(tspi, t);

	अगर (tspi->cur_direction & DATA_सूची_TX)
		tspi->cur_pos = tspi->cur_tx_pos;
	अन्यथा
		tspi->cur_pos = tspi->cur_rx_pos;

	अगर (tspi->cur_pos == t->len) अणु
		complete(&tspi->xfer_completion);
		जाओ निकास;
	पूर्ण

	/* Continue transfer in current message */
	total_fअगरo_words = tegra_slink_calculate_curr_xfer_param(tspi->cur_spi,
							tspi, t);
	अगर (total_fअगरo_words > SLINK_FIFO_DEPTH)
		err = tegra_slink_start_dma_based_transfer(tspi, t);
	अन्यथा
		err = tegra_slink_start_cpu_based_transfer(tspi, t);

निकास:
	spin_unlock_irqrestore(&tspi->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_slink_isr_thपढ़ो(पूर्णांक irq, व्योम *context_data)
अणु
	काष्ठा tegra_slink_data *tspi = context_data;

	अगर (!tspi->is_curr_dma_xfer)
		वापस handle_cpu_based_xfer(tspi);
	वापस handle_dma_based_xfer(tspi);
पूर्ण

अटल irqवापस_t tegra_slink_isr(पूर्णांक irq, व्योम *context_data)
अणु
	काष्ठा tegra_slink_data *tspi = context_data;

	tspi->status_reg = tegra_slink_पढ़ोl(tspi, SLINK_STATUS);
	अगर (tspi->cur_direction & DATA_सूची_TX)
		tspi->tx_status = tspi->status_reg &
					(SLINK_TX_OVF | SLINK_TX_UNF);

	अगर (tspi->cur_direction & DATA_सूची_RX)
		tspi->rx_status = tspi->status_reg &
					(SLINK_RX_OVF | SLINK_RX_UNF);
	tegra_slink_clear_status(tspi);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल स्थिर काष्ठा tegra_slink_chip_data tegra30_spi_cdata = अणु
	.cs_hold_समय = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_slink_chip_data tegra20_spi_cdata = अणु
	.cs_hold_समय = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_slink_of_match[] = अणु
	अणु .compatible = "nvidia,tegra30-slink", .data = &tegra30_spi_cdata, पूर्ण,
	अणु .compatible = "nvidia,tegra20-slink", .data = &tegra20_spi_cdata, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_slink_of_match);

अटल पूर्णांक tegra_slink_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master;
	काष्ठा tegra_slink_data	*tspi;
	काष्ठा resource		*r;
	पूर्णांक ret, spi_irq;
	स्थिर काष्ठा tegra_slink_chip_data *cdata = शून्य;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(tegra_slink_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण
	cdata = match->data;

	master = spi_alloc_master(&pdev->dev, माप(*tspi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->setup = tegra_slink_setup;
	master->prepare_message = tegra_slink_prepare_message;
	master->transfer_one = tegra_slink_transfer_one;
	master->unprepare_message = tegra_slink_unprepare_message;
	master->स्वतः_runसमय_pm = true;
	master->num_chipselect = MAX_CHIP_SELECT;

	platक्रमm_set_drvdata(pdev, master);
	tspi = spi_master_get_devdata(master);
	tspi->master = master;
	tspi->dev = &pdev->dev;
	tspi->chip_data = cdata;
	spin_lock_init(&tspi->lock);

	अगर (of_property_पढ़ो_u32(tspi->dev->of_node, "spi-max-frequency",
				 &master->max_speed_hz))
		master->max_speed_hz = 25000000; /* 25MHz */

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "No IO memory resource\n");
		ret = -ENODEV;
		जाओ निकास_मुक्त_master;
	पूर्ण
	tspi->phys = r->start;
	tspi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(tspi->base)) अणु
		ret = PTR_ERR(tspi->base);
		जाओ निकास_मुक्त_master;
	पूर्ण

	/* disabled घड़ी may cause पूर्णांकerrupt storm upon request */
	tspi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tspi->clk)) अणु
		ret = PTR_ERR(tspi->clk);
		dev_err(&pdev->dev, "Can not get clock %d\n", ret);
		जाओ निकास_मुक्त_master;
	पूर्ण
	ret = clk_prepare(tspi->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Clock prepare failed %d\n", ret);
		जाओ निकास_मुक्त_master;
	पूर्ण
	ret = clk_enable(tspi->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Clock enable failed %d\n", ret);
		जाओ निकास_clk_unprepare;
	पूर्ण

	spi_irq = platक्रमm_get_irq(pdev, 0);
	tspi->irq = spi_irq;
	ret = request_thपढ़ोed_irq(tspi->irq, tegra_slink_isr,
			tegra_slink_isr_thपढ़ो, IRQF_ONESHOT,
			dev_name(&pdev->dev), tspi);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register ISR for IRQ %d\n",
					tspi->irq);
		जाओ निकास_clk_disable;
	पूर्ण

	tspi->rst = devm_reset_control_get_exclusive(&pdev->dev, "spi");
	अगर (IS_ERR(tspi->rst)) अणु
		dev_err(&pdev->dev, "can not get reset\n");
		ret = PTR_ERR(tspi->rst);
		जाओ निकास_मुक्त_irq;
	पूर्ण

	tspi->max_buf_size = SLINK_FIFO_DEPTH << 2;
	tspi->dma_buf_size = DEFAULT_SPI_DMA_BUF_LEN;

	ret = tegra_slink_init_dma_param(tspi, true);
	अगर (ret < 0)
		जाओ निकास_मुक्त_irq;
	ret = tegra_slink_init_dma_param(tspi, false);
	अगर (ret < 0)
		जाओ निकास_rx_dma_मुक्त;
	tspi->max_buf_size = tspi->dma_buf_size;
	init_completion(&tspi->tx_dma_complete);
	init_completion(&tspi->rx_dma_complete);

	init_completion(&tspi->xfer_completion);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = tegra_slink_runसमय_resume(&pdev->dev);
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

	tspi->def_command_reg  = SLINK_M_S;
	tspi->def_command2_reg = SLINK_CS_ACTIVE_BETWEEN;
	tegra_slink_ग_लिखोl(tspi, tspi->def_command_reg, SLINK_COMMAND);
	tegra_slink_ग_लिखोl(tspi, tspi->def_command2_reg, SLINK_COMMAND2);
	pm_runसमय_put(&pdev->dev);

	master->dev.of_node = pdev->dev.of_node;
	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can not register to master err %d\n", ret);
		जाओ निकास_pm_disable;
	पूर्ण
	वापस ret;

निकास_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_slink_runसमय_suspend(&pdev->dev);
	tegra_slink_deinit_dma_param(tspi, false);
निकास_rx_dma_मुक्त:
	tegra_slink_deinit_dma_param(tspi, true);
निकास_मुक्त_irq:
	मुक्त_irq(spi_irq, tspi);
निकास_clk_disable:
	clk_disable(tspi->clk);
निकास_clk_unprepare:
	clk_unprepare(tspi->clk);
निकास_मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_slink_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा tegra_slink_data	*tspi = spi_master_get_devdata(master);

	मुक्त_irq(tspi->irq, tspi);

	clk_disable(tspi->clk);
	clk_unprepare(tspi->clk);

	अगर (tspi->tx_dma_chan)
		tegra_slink_deinit_dma_param(tspi, false);

	अगर (tspi->rx_dma_chan)
		tegra_slink_deinit_dma_param(tspi, true);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		tegra_slink_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_slink_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);

	वापस spi_master_suspend(master);
पूर्ण

अटल पूर्णांक tegra_slink_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		dev_err(dev, "pm runtime failed, e = %d\n", ret);
		वापस ret;
	पूर्ण
	tegra_slink_ग_लिखोl(tspi, tspi->command_reg, SLINK_COMMAND);
	tegra_slink_ग_लिखोl(tspi, tspi->command2_reg, SLINK_COMMAND2);
	pm_runसमय_put(dev);

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tegra_slink_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(master);

	/* Flush all ग_लिखो which are in PPSB queue by पढ़ोing back */
	tegra_slink_पढ़ोl(tspi, SLINK_MAS_DATA);

	clk_disable_unprepare(tspi->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_slink_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा tegra_slink_data *tspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(tspi->clk);
	अगर (ret < 0) अणु
		dev_err(tspi->dev, "clk_prepare failed: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops slink_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_slink_runसमय_suspend,
		tegra_slink_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_slink_suspend, tegra_slink_resume)
पूर्ण;
अटल काष्ठा platक्रमm_driver tegra_slink_driver = अणु
	.driver = अणु
		.name		= "spi-tegra-slink",
		.pm		= &slink_pm_ops,
		.of_match_table	= tegra_slink_of_match,
	पूर्ण,
	.probe =	tegra_slink_probe,
	.हटाओ =	tegra_slink_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_slink_driver);

MODULE_ALIAS("platform:spi-tegra-slink");
MODULE_DESCRIPTION("NVIDIA Tegra20/Tegra30 SLINK Controller Driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
