<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i3c/master.h>
#समावेश <linux/पन.स>

#समावेश "hci.h"
#समावेश "cmd.h"
#समावेश "ibi.h"


/*
 * PIO Access Area
 */

#घोषणा pio_reg_पढ़ो(r)		पढ़ोl(hci->PIO_regs + (PIO_##r))
#घोषणा pio_reg_ग_लिखो(r, v)	ग_लिखोl(v, hci->PIO_regs + (PIO_##r))

#घोषणा PIO_COMMAND_QUEUE_PORT		0x00
#घोषणा PIO_RESPONSE_QUEUE_PORT		0x04
#घोषणा PIO_XFER_DATA_PORT		0x08
#घोषणा PIO_IBI_PORT			0x0c

#घोषणा PIO_QUEUE_THLD_CTRL		0x10
#घोषणा QUEUE_IBI_STATUS_THLD		GENMASK(31, 24)
#घोषणा QUEUE_IBI_DATA_THLD		GENMASK(23, 16)
#घोषणा QUEUE_RESP_BUF_THLD		GENMASK(15, 8)
#घोषणा QUEUE_CMD_EMPTY_BUF_THLD	GENMASK(7, 0)

#घोषणा PIO_DATA_BUFFER_THLD_CTRL	0x14
#घोषणा DATA_RX_START_THLD		GENMASK(26, 24)
#घोषणा DATA_TX_START_THLD		GENMASK(18, 16)
#घोषणा DATA_RX_BUF_THLD		GENMASK(10, 8)
#घोषणा DATA_TX_BUF_THLD		GENMASK(2, 0)

#घोषणा PIO_QUEUE_SIZE			0x18
#घोषणा TX_DATA_BUFFER_SIZE		GENMASK(31, 24)
#घोषणा RX_DATA_BUFFER_SIZE		GENMASK(23, 16)
#घोषणा IBI_STATUS_SIZE			GENMASK(15, 8)
#घोषणा CR_QUEUE_SIZE			GENMASK(7, 0)

#घोषणा PIO_INTR_STATUS			0x20
#घोषणा PIO_INTR_STATUS_ENABLE		0x24
#घोषणा PIO_INTR_SIGNAL_ENABLE		0x28
#घोषणा PIO_INTR_FORCE			0x2c
#घोषणा STAT_TRANSFER_BLOCKED		BIT(25)
#घोषणा STAT_PERR_RESP_UFLOW		BIT(24)
#घोषणा STAT_PERR_CMD_OFLOW		BIT(23)
#घोषणा STAT_PERR_IBI_UFLOW		BIT(22)
#घोषणा STAT_PERR_RX_UFLOW		BIT(21)
#घोषणा STAT_PERR_TX_OFLOW		BIT(20)
#घोषणा STAT_ERR_RESP_QUEUE_FULL	BIT(19)
#घोषणा STAT_WARN_RESP_QUEUE_FULL	BIT(18)
#घोषणा STAT_ERR_IBI_QUEUE_FULL		BIT(17)
#घोषणा STAT_WARN_IBI_QUEUE_FULL	BIT(16)
#घोषणा STAT_ERR_RX_DATA_FULL		BIT(15)
#घोषणा STAT_WARN_RX_DATA_FULL		BIT(14)
#घोषणा STAT_ERR_TX_DATA_EMPTY		BIT(13)
#घोषणा STAT_WARN_TX_DATA_EMPTY		BIT(12)
#घोषणा STAT_TRANSFER_ERR		BIT(9)
#घोषणा STAT_WARN_INS_STOP_MODE		BIT(7)
#घोषणा STAT_TRANSFER_ABORT		BIT(5)
#घोषणा STAT_RESP_READY			BIT(4)
#घोषणा STAT_CMD_QUEUE_READY		BIT(3)
#घोषणा STAT_IBI_STATUS_THLD		BIT(2)
#घोषणा STAT_RX_THLD			BIT(1)
#घोषणा STAT_TX_THLD			BIT(0)

#घोषणा PIO_QUEUE_CUR_STATUS		0x38
#घोषणा CUR_IBI_Q_LEVEL			GENMASK(28, 20)
#घोषणा CUR_RESP_Q_LEVEL		GENMASK(18, 10)
#घोषणा CUR_CMD_Q_EMPTY_LEVEL		GENMASK(8, 0)

#घोषणा PIO_DATA_BUFFER_CUR_STATUS	0x3c
#घोषणा CUR_RX_BUF_LVL			GENMASK(26, 16)
#घोषणा CUR_TX_BUF_LVL			GENMASK(10, 0)

/*
 * Handy status bit combinations
 */

#घोषणा STAT_LATENCY_WARNINGS		(STAT_WARN_RESP_QUEUE_FULL | \
					 STAT_WARN_IBI_QUEUE_FULL | \
					 STAT_WARN_RX_DATA_FULL | \
					 STAT_WARN_TX_DATA_EMPTY | \
					 STAT_WARN_INS_STOP_MODE)

#घोषणा STAT_LATENCY_ERRORS		(STAT_ERR_RESP_QUEUE_FULL | \
					 STAT_ERR_IBI_QUEUE_FULL | \
					 STAT_ERR_RX_DATA_FULL | \
					 STAT_ERR_TX_DATA_EMPTY)

#घोषणा STAT_PROG_ERRORS		(STAT_TRANSFER_BLOCKED | \
					 STAT_PERR_RESP_UFLOW | \
					 STAT_PERR_CMD_OFLOW | \
					 STAT_PERR_IBI_UFLOW | \
					 STAT_PERR_RX_UFLOW | \
					 STAT_PERR_TX_OFLOW)

#घोषणा STAT_ALL_ERRORS			(STAT_TRANSFER_ABORT | \
					 STAT_TRANSFER_ERR | \
					 STAT_LATENCY_ERRORS | \
					 STAT_PROG_ERRORS)

काष्ठा hci_pio_dev_ibi_data अणु
	काष्ठा i3c_generic_ibi_pool *pool;
	अचिन्हित पूर्णांक max_len;
पूर्ण;

काष्ठा hci_pio_ibi_data अणु
	काष्ठा i3c_ibi_slot *slot;
	व्योम *data_ptr;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक seg_len, seg_cnt;
	अचिन्हित पूर्णांक max_len;
	bool last_seg;
पूर्ण;

काष्ठा hci_pio_data अणु
	spinlock_t lock;
	काष्ठा hci_xfer *curr_xfer, *xfer_queue;
	काष्ठा hci_xfer *curr_rx, *rx_queue;
	काष्ठा hci_xfer *curr_tx, *tx_queue;
	काष्ठा hci_xfer *curr_resp, *resp_queue;
	काष्ठा hci_pio_ibi_data ibi;
	अचिन्हित पूर्णांक rx_thresh_size, tx_thresh_size;
	अचिन्हित पूर्णांक max_ibi_thresh;
	u32 reg_queue_thresh;
	u32 enabled_irqs;
पूर्ण;

अटल पूर्णांक hci_pio_init(काष्ठा i3c_hci *hci)
अणु
	काष्ठा hci_pio_data *pio;
	u32 val, size_val, rx_thresh, tx_thresh, ibi_val;

	pio = kzalloc(माप(*pio), GFP_KERNEL);
	अगर (!pio)
		वापस -ENOMEM;

	hci->io_data = pio;
	spin_lock_init(&pio->lock);

	size_val = pio_reg_पढ़ो(QUEUE_SIZE);
	dev_info(&hci->master.dev, "CMD/RESP FIFO = %ld entries\n",
		 FIELD_GET(CR_QUEUE_SIZE, size_val));
	dev_info(&hci->master.dev, "IBI FIFO = %ld bytes\n",
		 4 * FIELD_GET(IBI_STATUS_SIZE, size_val));
	dev_info(&hci->master.dev, "RX data FIFO = %d bytes\n",
		 4 * (2 << FIELD_GET(RX_DATA_BUFFER_SIZE, size_val)));
	dev_info(&hci->master.dev, "TX data FIFO = %d bytes\n",
		 4 * (2 << FIELD_GET(TX_DATA_BUFFER_SIZE, size_val)));

	/*
	 * Let's initialize data thresholds to half of the actual FIFO size.
	 * The start thresholds aren't used (set to 0) as the FIFO is always
	 * serviced beक्रमe the corresponding command is queued.
	 */
	rx_thresh = FIELD_GET(RX_DATA_BUFFER_SIZE, size_val);
	tx_thresh = FIELD_GET(TX_DATA_BUFFER_SIZE, size_val);
	अगर (hci->version_major == 1) अणु
		/* those are expressed as 2^[n+1), so just sub 1 अगर not 0 */
		अगर (rx_thresh)
			rx_thresh -= 1;
		अगर (tx_thresh)
			tx_thresh -= 1;
		pio->rx_thresh_size = 2 << rx_thresh;
		pio->tx_thresh_size = 2 << tx_thresh;
	पूर्ण अन्यथा अणु
		/* size is 2^(n+1) and threshold is 2^n i.e. alपढ़ोy halved */
		pio->rx_thresh_size = 1 << rx_thresh;
		pio->tx_thresh_size = 1 << tx_thresh;
	पूर्ण
	val = FIELD_PREP(DATA_RX_BUF_THLD,   rx_thresh) |
	      FIELD_PREP(DATA_TX_BUF_THLD,   tx_thresh);
	pio_reg_ग_लिखो(DATA_BUFFER_THLD_CTRL, val);

	/*
	 * Let's उठाओ an पूर्णांकerrupt as soon as there is one मुक्त cmd slot
	 * or one available response or IBI. For IBI data let's use half the
	 * IBI queue size within allowed bounds.
	 */
	ibi_val = FIELD_GET(IBI_STATUS_SIZE, size_val);
	pio->max_ibi_thresh = clamp_val(ibi_val/2, 1, 63);
	val = FIELD_PREP(QUEUE_IBI_STATUS_THLD, 1) |
	      FIELD_PREP(QUEUE_IBI_DATA_THLD, pio->max_ibi_thresh) |
	      FIELD_PREP(QUEUE_RESP_BUF_THLD, 1) |
	      FIELD_PREP(QUEUE_CMD_EMPTY_BUF_THLD, 1);
	pio_reg_ग_लिखो(QUEUE_THLD_CTRL, val);
	pio->reg_queue_thresh = val;

	/* Disable all IRQs but allow all status bits */
	pio_reg_ग_लिखो(INTR_SIGNAL_ENABLE, 0x0);
	pio_reg_ग_लिखो(INTR_STATUS_ENABLE, 0xffffffff);

	/* Always accept error पूर्णांकerrupts (will be activated on first xfer) */
	pio->enabled_irqs = STAT_ALL_ERRORS;

	वापस 0;
पूर्ण

अटल व्योम hci_pio_cleanup(काष्ठा i3c_hci *hci)
अणु
	काष्ठा hci_pio_data *pio = hci->io_data;

	pio_reg_ग_लिखो(INTR_SIGNAL_ENABLE, 0x0);

	अगर (pio) अणु
		DBG("status = %#x/%#x",
		    pio_reg_पढ़ो(INTR_STATUS), pio_reg_पढ़ो(INTR_SIGNAL_ENABLE));
		BUG_ON(pio->curr_xfer);
		BUG_ON(pio->curr_rx);
		BUG_ON(pio->curr_tx);
		BUG_ON(pio->curr_resp);
		kमुक्त(pio);
		hci->io_data = शून्य;
	पूर्ण
पूर्ण

अटल व्योम hci_pio_ग_लिखो_cmd(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer)
अणु
	DBG("cmd_desc[%d] = 0x%08x", 0, xfer->cmd_desc[0]);
	DBG("cmd_desc[%d] = 0x%08x", 1, xfer->cmd_desc[1]);
	pio_reg_ग_लिखो(COMMAND_QUEUE_PORT, xfer->cmd_desc[0]);
	pio_reg_ग_लिखो(COMMAND_QUEUE_PORT, xfer->cmd_desc[1]);
	अगर (hci->cmd == &mipi_i3c_hci_cmd_v2) अणु
		DBG("cmd_desc[%d] = 0x%08x", 2, xfer->cmd_desc[2]);
		DBG("cmd_desc[%d] = 0x%08x", 3, xfer->cmd_desc[3]);
		pio_reg_ग_लिखो(COMMAND_QUEUE_PORT, xfer->cmd_desc[2]);
		pio_reg_ग_लिखो(COMMAND_QUEUE_PORT, xfer->cmd_desc[3]);
	पूर्ण
पूर्ण

अटल bool hci_pio_करो_rx(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_xfer *xfer = pio->curr_rx;
	अचिन्हित पूर्णांक nr_words;
	u32 *p;

	p = xfer->data;
	p += (xfer->data_len - xfer->data_left) / 4;

	जबतक (xfer->data_left >= 4) अणु
		/* bail out अगर FIFO hasn't reached the threshold value yet */
		अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_RX_THLD))
			वापस false;
		nr_words = min(xfer->data_left / 4, pio->rx_thresh_size);
		/* extract data from FIFO */
		xfer->data_left -= nr_words * 4;
		DBG("now %d left %d", nr_words * 4, xfer->data_left);
		जबतक (nr_words--)
			*p++ = pio_reg_पढ़ो(XFER_DATA_PORT);
	पूर्ण

	/* trailing data is retrieved upon response reception */
	वापस !xfer->data_left;
पूर्ण

अटल व्योम hci_pio_करो_trailing_rx(काष्ठा i3c_hci *hci,
				   काष्ठा hci_pio_data *pio, अचिन्हित पूर्णांक count)
अणु
	काष्ठा hci_xfer *xfer = pio->curr_rx;
	u32 *p;

	DBG("%d remaining", count);

	p = xfer->data;
	p += (xfer->data_len - xfer->data_left) / 4;

	अगर (count >= 4) अणु
		अचिन्हित पूर्णांक nr_words = count / 4;
		/* extract data from FIFO */
		xfer->data_left -= nr_words * 4;
		DBG("now %d left %d", nr_words * 4, xfer->data_left);
		जबतक (nr_words--)
			*p++ = pio_reg_पढ़ो(XFER_DATA_PORT);
	पूर्ण

	count &= 3;
	अगर (count) अणु
		/*
		 * There are trailing bytes in the last word.
		 * Fetch it and extract bytes in an endian independent way.
		 * Unlike the TX हाल, we must not ग_लिखो memory past the
		 * end of the destination buffer.
		 */
		u8 *p_byte = (u8 *)p;
		u32 data = pio_reg_पढ़ो(XFER_DATA_PORT);

		xfer->data_word_beक्रमe_partial = data;
		xfer->data_left -= count;
		data = (__क्रमce u32) cpu_to_le32(data);
		जबतक (count--) अणु
			*p_byte++ = data;
			data >>= 8;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool hci_pio_करो_tx(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_xfer *xfer = pio->curr_tx;
	अचिन्हित पूर्णांक nr_words;
	u32 *p;

	p = xfer->data;
	p += (xfer->data_len - xfer->data_left) / 4;

	जबतक (xfer->data_left >= 4) अणु
		/* bail out अगर FIFO मुक्त space is below set threshold */
		अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_TX_THLD))
			वापस false;
		/* we can fill up to that TX threshold */
		nr_words = min(xfer->data_left / 4, pio->tx_thresh_size);
		/* push data पूर्णांकo the FIFO */
		xfer->data_left -= nr_words * 4;
		DBG("now %d left %d", nr_words * 4, xfer->data_left);
		जबतक (nr_words--)
			pio_reg_ग_लिखो(XFER_DATA_PORT, *p++);
	पूर्ण

	अगर (xfer->data_left) अणु
		/*
		 * There are trailing bytes to send. We can simply load
		 * them from memory as a word which will keep those bytes
		 * in their proper place even on a BE प्रणाली. This will
		 * also get some bytes past the actual buffer but no one
		 * should care as they won't be sent out.
		 */
		अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_TX_THLD))
			वापस false;
		DBG("trailing %d", xfer->data_left);
		pio_reg_ग_लिखो(XFER_DATA_PORT, *p);
		xfer->data_left = 0;
	पूर्ण

	वापस true;
पूर्ण

अटल bool hci_pio_process_rx(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	जबतक (pio->curr_rx && hci_pio_करो_rx(hci, pio))
		pio->curr_rx = pio->curr_rx->next_data;
	वापस !pio->curr_rx;
पूर्ण

अटल bool hci_pio_process_tx(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	जबतक (pio->curr_tx && hci_pio_करो_tx(hci, pio))
		pio->curr_tx = pio->curr_tx->next_data;
	वापस !pio->curr_tx;
पूर्ण

अटल व्योम hci_pio_queue_data(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_xfer *xfer = pio->curr_xfer;
	काष्ठा hci_xfer *prev_queue_tail;

	अगर (!xfer->data) अणु
		xfer->data_len = xfer->data_left = 0;
		वापस;
	पूर्ण

	अगर (xfer->rnw) अणु
		prev_queue_tail = pio->rx_queue;
		pio->rx_queue = xfer;
		अगर (pio->curr_rx) अणु
			prev_queue_tail->next_data = xfer;
		पूर्ण अन्यथा अणु
			pio->curr_rx = xfer;
			अगर (!hci_pio_process_rx(hci, pio))
				pio->enabled_irqs |= STAT_RX_THLD;
		पूर्ण
	पूर्ण अन्यथा अणु
		prev_queue_tail = pio->tx_queue;
		pio->tx_queue = xfer;
		अगर (pio->curr_tx) अणु
			prev_queue_tail->next_data = xfer;
		पूर्ण अन्यथा अणु
			pio->curr_tx = xfer;
			अगर (!hci_pio_process_tx(hci, pio))
				pio->enabled_irqs |= STAT_TX_THLD;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hci_pio_push_to_next_rx(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer,
				    अचिन्हित पूर्णांक words_to_keep)
अणु
	u32 *from = xfer->data;
	u32 from_last;
	अचिन्हित पूर्णांक received, count;

	received = (xfer->data_len - xfer->data_left) / 4;
	अगर ((xfer->data_len - xfer->data_left) & 3) अणु
		from_last = xfer->data_word_beक्रमe_partial;
		received += 1;
	पूर्ण अन्यथा अणु
		from_last = from[received];
	पूर्ण
	from += words_to_keep;
	count = received - words_to_keep;

	जबतक (count) अणु
		अचिन्हित पूर्णांक room, left, chunk, bytes_to_move;
		u32 last_word;

		xfer = xfer->next_data;
		अगर (!xfer) अणु
			dev_err(&hci->master.dev, "pushing RX data to unexistent xfer\n");
			वापस;
		पूर्ण

		room = DIV_ROUND_UP(xfer->data_len, 4);
		left = DIV_ROUND_UP(xfer->data_left, 4);
		chunk = min(count, room);
		अगर (chunk > left) अणु
			hci_pio_push_to_next_rx(hci, xfer, chunk - left);
			left = chunk;
			xfer->data_left = left * 4;
		पूर्ण

		bytes_to_move = xfer->data_len - xfer->data_left;
		अगर (bytes_to_move & 3) अणु
			/* preserve word  to become partial */
			u32 *p = xfer->data;

			xfer->data_word_beक्रमe_partial = p[bytes_to_move / 4];
		पूर्ण
		स_हटाओ(xfer->data + chunk, xfer->data, bytes_to_move);

		/* treat last word specially because of partial word issues */
		chunk -= 1;

		स_नकल(xfer->data, from, chunk * 4);
		xfer->data_left -= chunk * 4;
		from += chunk;
		count -= chunk;

		last_word = (count == 1) ? from_last : *from++;
		अगर (xfer->data_left < 4) अणु
			/*
			 * Like in hci_pio_करो_trailing_rx(), preserve original
			 * word to be stored partially then store bytes it
			 * in an endian independent way.
			 */
			u8 *p_byte = xfer->data;

			p_byte += chunk * 4;
			xfer->data_word_beक्रमe_partial = last_word;
			last_word = (__क्रमce u32) cpu_to_le32(last_word);
			जबतक (xfer->data_left--) अणु
				*p_byte++ = last_word;
				last_word >>= 8;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 *p = xfer->data;

			p[chunk] = last_word;
			xfer->data_left -= 4;
		पूर्ण
		count--;
	पूर्ण
पूर्ण

अटल व्योम hci_pio_err(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio,
			u32 status);

अटल bool hci_pio_process_resp(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	जबतक (pio->curr_resp &&
	       (pio_reg_पढ़ो(INTR_STATUS) & STAT_RESP_READY)) अणु
		काष्ठा hci_xfer *xfer = pio->curr_resp;
		u32 resp = pio_reg_पढ़ो(RESPONSE_QUEUE_PORT);
		अचिन्हित पूर्णांक tid = RESP_TID(resp);

		DBG("resp = 0x%08x", resp);
		अगर (tid != xfer->cmd_tid) अणु
			dev_err(&hci->master.dev,
				"response tid=%d when expecting %d\n",
				tid, xfer->cmd_tid);
			/* let's pretend it is a prog error... any of them  */
			hci_pio_err(hci, pio, STAT_PROG_ERRORS);
			वापस false;
		पूर्ण
		xfer->response = resp;

		अगर (pio->curr_rx == xfer) अणु
			/*
			 * Response availability implies RX completion.
			 * Retrieve trailing RX data अगर any.
			 * Note that लघु पढ़ोs are possible.
			 */
			अचिन्हित पूर्णांक received, expected, to_keep;

			received = xfer->data_len - xfer->data_left;
			expected = RESP_DATA_LENGTH(xfer->response);
			अगर (expected > received) अणु
				hci_pio_करो_trailing_rx(hci, pio,
						       expected - received);
			पूर्ण अन्यथा अगर (received > expected) अणु
				/* we consumed data meant क्रम next xfer */
				to_keep = DIV_ROUND_UP(expected, 4);
				hci_pio_push_to_next_rx(hci, xfer, to_keep);
			पूर्ण

			/* then process the RX list poपूर्णांकer */
			अगर (hci_pio_process_rx(hci, pio))
				pio->enabled_irqs &= ~STAT_RX_THLD;
		पूर्ण

		/*
		 * We're about to give back ownership of the xfer काष्ठाure
		 * to the रुकोing instance. Make sure no reference to it
		 * still exists.
		 */
		अगर (pio->curr_rx == xfer) अणु
			DBG("short RX ?");
			pio->curr_rx = pio->curr_rx->next_data;
		पूर्ण अन्यथा अगर (pio->curr_tx == xfer) अणु
			DBG("short TX ?");
			pio->curr_tx = pio->curr_tx->next_data;
		पूर्ण अन्यथा अगर (xfer->data_left) अणु
			DBG("PIO xfer count = %d after response",
			    xfer->data_left);
		पूर्ण

		pio->curr_resp = xfer->next_resp;
		अगर (xfer->completion)
			complete(xfer->completion);
	पूर्ण
	वापस !pio->curr_resp;
पूर्ण

अटल व्योम hci_pio_queue_resp(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_xfer *xfer = pio->curr_xfer;
	काष्ठा hci_xfer *prev_queue_tail;

	अगर (!(xfer->cmd_desc[0] & CMD_0_ROC))
		वापस;

	prev_queue_tail = pio->resp_queue;
	pio->resp_queue = xfer;
	अगर (pio->curr_resp) अणु
		prev_queue_tail->next_resp = xfer;
	पूर्ण अन्यथा अणु
		pio->curr_resp = xfer;
		अगर (!hci_pio_process_resp(hci, pio))
			pio->enabled_irqs |= STAT_RESP_READY;
	पूर्ण
पूर्ण

अटल bool hci_pio_process_cmd(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	जबतक (pio->curr_xfer &&
	       (pio_reg_पढ़ो(INTR_STATUS) & STAT_CMD_QUEUE_READY)) अणु
		/*
		 * Always process the data FIFO beक्रमe sending the command
		 * so needed TX data or RX space is available upfront.
		 */
		hci_pio_queue_data(hci, pio);
		/*
		 * Then queue our response request. This will also process
		 * the response FIFO in हाल it got suddenly filled up
		 * with results from previous commands.
		 */
		hci_pio_queue_resp(hci, pio);
		/*
		 * Finally send the command.
		 */
		hci_pio_ग_लिखो_cmd(hci, pio->curr_xfer);
		/*
		 * And move on.
		 */
		pio->curr_xfer = pio->curr_xfer->next_xfer;
	पूर्ण
	वापस !pio->curr_xfer;
पूर्ण

अटल पूर्णांक hci_pio_queue_xfer(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer, पूर्णांक n)
अणु
	काष्ठा hci_pio_data *pio = hci->io_data;
	काष्ठा hci_xfer *prev_queue_tail;
	पूर्णांक i;

	DBG("n = %d", n);

	/* link xfer instances together and initialize data count */
	क्रम (i = 0; i < n; i++) अणु
		xfer[i].next_xfer = (i + 1 < n) ? &xfer[i + 1] : शून्य;
		xfer[i].next_data = शून्य;
		xfer[i].next_resp = शून्य;
		xfer[i].data_left = xfer[i].data_len;
	पूर्ण

	spin_lock_irq(&pio->lock);
	prev_queue_tail = pio->xfer_queue;
	pio->xfer_queue = &xfer[n - 1];
	अगर (pio->curr_xfer) अणु
		prev_queue_tail->next_xfer = xfer;
	पूर्ण अन्यथा अणु
		pio->curr_xfer = xfer;
		अगर (!hci_pio_process_cmd(hci, pio))
			pio->enabled_irqs |= STAT_CMD_QUEUE_READY;
		pio_reg_ग_लिखो(INTR_SIGNAL_ENABLE, pio->enabled_irqs);
		DBG("status = %#x/%#x",
		    pio_reg_पढ़ो(INTR_STATUS), pio_reg_पढ़ो(INTR_SIGNAL_ENABLE));
	पूर्ण
	spin_unlock_irq(&pio->lock);
	वापस 0;
पूर्ण

अटल bool hci_pio_dequeue_xfer_common(काष्ठा i3c_hci *hci,
					काष्ठा hci_pio_data *pio,
					काष्ठा hci_xfer *xfer, पूर्णांक n)
अणु
	काष्ठा hci_xfer *p, **p_prev_next;
	पूर्णांक i;

	/*
	 * To safely dequeue a transfer request, it must be either entirely
	 * processed, or not yet processed at all. If our request tail is
	 * reachable from either the data or resp list that means the command
	 * was submitted and not yet completed.
	 */
	क्रम (p = pio->curr_resp; p; p = p->next_resp)
		क्रम (i = 0; i < n; i++)
			अगर (p == &xfer[i])
				जाओ pio_screwed;
	क्रम (p = pio->curr_rx; p; p = p->next_data)
		क्रम (i = 0; i < n; i++)
			अगर (p == &xfer[i])
				जाओ pio_screwed;
	क्रम (p = pio->curr_tx; p; p = p->next_data)
		क्रम (i = 0; i < n; i++)
			अगर (p == &xfer[i])
				जाओ pio_screwed;

	/*
	 * The command was completed, or wasn't yet submitted.
	 * Unlink it from the que अगर the later.
	 */
	p_prev_next = &pio->curr_xfer;
	क्रम (p = pio->curr_xfer; p; p = p->next_xfer) अणु
		अगर (p == &xfer[0]) अणु
			*p_prev_next = xfer[n - 1].next_xfer;
			अवरोध;
		पूर्ण
		p_prev_next = &p->next_xfer;
	पूर्ण

	/* वापस true अगर we actually unqueued something */
	वापस !!p;

pio_screwed:
	/*
	 * Lअगरe is tough. We must invalidate the hardware state and
	 * discard everything that is still queued.
	 */
	क्रम (p = pio->curr_resp; p; p = p->next_resp) अणु
		p->response = FIELD_PREP(RESP_ERR_FIELD, RESP_ERR_HC_TERMINATED);
		अगर (p->completion)
			complete(p->completion);
	पूर्ण
	क्रम (p = pio->curr_xfer; p; p = p->next_xfer) अणु
		p->response = FIELD_PREP(RESP_ERR_FIELD, RESP_ERR_HC_TERMINATED);
		अगर (p->completion)
			complete(p->completion);
	पूर्ण
	pio->curr_xfer = pio->curr_rx = pio->curr_tx = pio->curr_resp = शून्य;

	वापस true;
पूर्ण

अटल bool hci_pio_dequeue_xfer(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer, पूर्णांक n)
अणु
	काष्ठा hci_pio_data *pio = hci->io_data;
	पूर्णांक ret;

	spin_lock_irq(&pio->lock);
	DBG("n=%d status=%#x/%#x", n,
	    pio_reg_पढ़ो(INTR_STATUS), pio_reg_पढ़ो(INTR_SIGNAL_ENABLE));
	DBG("main_status = %#x/%#x",
	    पढ़ोl(hci->base_regs + 0x20), पढ़ोl(hci->base_regs + 0x28));

	ret = hci_pio_dequeue_xfer_common(hci, pio, xfer, n);
	spin_unlock_irq(&pio->lock);
	वापस ret;
पूर्ण

अटल व्योम hci_pio_err(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio,
			u32 status)
अणु
	/* TODO: this ought to be more sophisticated eventually */

	अगर (pio_reg_पढ़ो(INTR_STATUS) & STAT_RESP_READY) अणु
		/* this may happen when an error is संकेतed with ROC unset */
		u32 resp = pio_reg_पढ़ो(RESPONSE_QUEUE_PORT);

		dev_err(&hci->master.dev,
			"orphan response (%#x) on error\n", resp);
	पूर्ण

	/* dump states on programming errors */
	अगर (status & STAT_PROG_ERRORS) अणु
		u32 queue = pio_reg_पढ़ो(QUEUE_CUR_STATUS);
		u32 data = pio_reg_पढ़ो(DATA_BUFFER_CUR_STATUS);

		dev_err(&hci->master.dev,
			"prog error %#lx (C/R/I = %ld/%ld/%ld, TX/RX = %ld/%ld)\n",
			status & STAT_PROG_ERRORS,
			FIELD_GET(CUR_CMD_Q_EMPTY_LEVEL, queue),
			FIELD_GET(CUR_RESP_Q_LEVEL, queue),
			FIELD_GET(CUR_IBI_Q_LEVEL, queue),
			FIELD_GET(CUR_TX_BUF_LVL, data),
			FIELD_GET(CUR_RX_BUF_LVL, data));
	पूर्ण

	/* just bust out everything with pending responses क्रम now */
	hci_pio_dequeue_xfer_common(hci, pio, pio->curr_resp, 1);
	/* ... and half-way TX transfers अगर any */
	अगर (pio->curr_tx && pio->curr_tx->data_left != pio->curr_tx->data_len)
		hci_pio_dequeue_xfer_common(hci, pio, pio->curr_tx, 1);
	/* then reset the hardware */
	mipi_i3c_hci_pio_reset(hci);
	mipi_i3c_hci_resume(hci);

	DBG("status=%#x/%#x",
	    pio_reg_पढ़ो(INTR_STATUS), pio_reg_पढ़ो(INTR_SIGNAL_ENABLE));
पूर्ण

अटल व्योम hci_pio_set_ibi_thresh(काष्ठा i3c_hci *hci,
				   काष्ठा hci_pio_data *pio,
				   अचिन्हित पूर्णांक thresh_val)
अणु
	u32 regval = pio->reg_queue_thresh;

	regval &= ~QUEUE_IBI_STATUS_THLD;
	regval |= FIELD_PREP(QUEUE_IBI_STATUS_THLD, thresh_val);
	/* ग_लिखो the threshold reg only अगर it changes */
	अगर (regval != pio->reg_queue_thresh) अणु
		pio_reg_ग_लिखो(QUEUE_THLD_CTRL, regval);
		pio->reg_queue_thresh = regval;
		DBG("%d", thresh_val);
	पूर्ण
पूर्ण

अटल bool hci_pio_get_ibi_segment(काष्ठा i3c_hci *hci,
				    काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_pio_ibi_data *ibi = &pio->ibi;
	अचिन्हित पूर्णांक nr_words, thresh_val;
	u32 *p;

	p = ibi->data_ptr;
	p += (ibi->seg_len - ibi->seg_cnt) / 4;

	जबतक ((nr_words = ibi->seg_cnt/4)) अणु
		/* determine our IBI queue threshold value */
		thresh_val = min(nr_words, pio->max_ibi_thresh);
		hci_pio_set_ibi_thresh(hci, pio, thresh_val);
		/* bail out अगर we करोn't have that amount of data पढ़ोy */
		अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_IBI_STATUS_THLD))
			वापस false;
		/* extract the data from the IBI port */
		nr_words = thresh_val;
		ibi->seg_cnt -= nr_words * 4;
		DBG("now %d left %d", nr_words * 4, ibi->seg_cnt);
		जबतक (nr_words--)
			*p++ = pio_reg_पढ़ो(IBI_PORT);
	पूर्ण

	अगर (ibi->seg_cnt) अणु
		/*
		 * There are trailing bytes in the last word.
		 * Fetch it and extract bytes in an endian independent way.
		 * Unlike the TX हाल, we must not ग_लिखो past the end of
		 * the destination buffer.
		 */
		u32 data;
		u8 *p_byte = (u8 *)p;

		hci_pio_set_ibi_thresh(hci, pio, 1);
		अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_IBI_STATUS_THLD))
			वापस false;
		DBG("trailing %d", ibi->seg_cnt);
		data = pio_reg_पढ़ो(IBI_PORT);
		data = (__क्रमce u32) cpu_to_le32(data);
		जबतक (ibi->seg_cnt--) अणु
			*p_byte++ = data;
			data >>= 8;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool hci_pio_prep_new_ibi(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_pio_ibi_data *ibi = &pio->ibi;
	काष्ठा i3c_dev_desc *dev;
	काष्ठा i3c_hci_dev_data *dev_data;
	काष्ठा hci_pio_dev_ibi_data *dev_ibi;
	u32 ibi_status;

	/*
	 * We have a new IBI. Try to set up its payload retrieval.
	 * When वापसing true, the IBI data has to be consumed whether
	 * or not we are set up to capture it. If we वापस true with
	 * ibi->slot == शून्य that means the data payload has to be
	 * drained out of the IBI port and dropped.
	 */

	ibi_status = pio_reg_पढ़ो(IBI_PORT);
	DBG("status = %#x", ibi_status);
	ibi->addr = FIELD_GET(IBI_TARGET_ADDR, ibi_status);
	अगर (ibi_status & IBI_ERROR) अणु
		dev_err(&hci->master.dev, "IBI error from %#x\n", ibi->addr);
		वापस false;
	पूर्ण

	ibi->last_seg = ibi_status & IBI_LAST_STATUS;
	ibi->seg_len = FIELD_GET(IBI_DATA_LENGTH, ibi_status);
	ibi->seg_cnt = ibi->seg_len;

	dev = i3c_hci_addr_to_dev(hci, ibi->addr);
	अगर (!dev) अणु
		dev_err(&hci->master.dev,
			"IBI for unknown device %#x\n", ibi->addr);
		वापस true;
	पूर्ण

	dev_data = i3c_dev_get_master_data(dev);
	dev_ibi = dev_data->ibi_data;
	ibi->max_len = dev_ibi->max_len;

	अगर (ibi->seg_len > ibi->max_len) अणु
		dev_err(&hci->master.dev, "IBI payload too big (%d > %d)\n",
			ibi->seg_len, ibi->max_len);
		वापस true;
	पूर्ण

	ibi->slot = i3c_generic_ibi_get_मुक्त_slot(dev_ibi->pool);
	अगर (!ibi->slot) अणु
		dev_err(&hci->master.dev, "no free slot for IBI\n");
	पूर्ण अन्यथा अणु
		ibi->slot->len = 0;
		ibi->data_ptr = ibi->slot->data;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम hci_pio_मुक्त_ibi_slot(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_pio_ibi_data *ibi = &pio->ibi;
	काष्ठा hci_pio_dev_ibi_data *dev_ibi;

	अगर (ibi->slot) अणु
		dev_ibi = ibi->slot->dev->common.master_priv;
		i3c_generic_ibi_recycle_slot(dev_ibi->pool, ibi->slot);
		ibi->slot = शून्य;
	पूर्ण
पूर्ण

अटल bool hci_pio_process_ibi(काष्ठा i3c_hci *hci, काष्ठा hci_pio_data *pio)
अणु
	काष्ठा hci_pio_ibi_data *ibi = &pio->ibi;

	अगर (!ibi->slot && !ibi->seg_cnt && ibi->last_seg)
		अगर (!hci_pio_prep_new_ibi(hci, pio))
			वापस false;

	क्रम (;;) अणु
		u32 ibi_status;
		अचिन्हित पूर्णांक ibi_addr;

		अगर (ibi->slot) अणु
			अगर (!hci_pio_get_ibi_segment(hci, pio))
				वापस false;
			ibi->slot->len += ibi->seg_len;
			ibi->data_ptr += ibi->seg_len;
			अगर (ibi->last_seg) अणु
				/* was the last segment: submit it and leave */
				i3c_master_queue_ibi(ibi->slot->dev, ibi->slot);
				ibi->slot = शून्य;
				hci_pio_set_ibi_thresh(hci, pio, 1);
				वापस true;
			पूर्ण
		पूर्ण अन्यथा अगर (ibi->seg_cnt) अणु
			/*
			 * No slot but a non-zero count. This is the result
			 * of some error and the payload must be drained.
			 * This normally करोes not happen thereक्रमe no need
			 * to be extra optimized here.
			 */
			hci_pio_set_ibi_thresh(hci, pio, 1);
			करो अणु
				अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_IBI_STATUS_THLD))
					वापस false;
				pio_reg_पढ़ो(IBI_PORT);
			पूर्ण जबतक (--ibi->seg_cnt);
			अगर (ibi->last_seg)
				वापस true;
		पूर्ण

		/* try to move to the next segment right away */
		hci_pio_set_ibi_thresh(hci, pio, 1);
		अगर (!(pio_reg_पढ़ो(INTR_STATUS) & STAT_IBI_STATUS_THLD))
			वापस false;
		ibi_status = pio_reg_पढ़ो(IBI_PORT);
		ibi_addr = FIELD_GET(IBI_TARGET_ADDR, ibi_status);
		अगर (ibi->addr != ibi_addr) अणु
			/* target address changed beक्रमe last segment */
			dev_err(&hci->master.dev,
				"unexp IBI address changed from %d to %d\n",
				ibi->addr, ibi_addr);
			hci_pio_मुक्त_ibi_slot(hci, pio);
		पूर्ण
		ibi->last_seg = ibi_status & IBI_LAST_STATUS;
		ibi->seg_len = FIELD_GET(IBI_DATA_LENGTH, ibi_status);
		ibi->seg_cnt = ibi->seg_len;
		अगर (ibi->slot && ibi->slot->len + ibi->seg_len > ibi->max_len) अणु
			dev_err(&hci->master.dev,
				"IBI payload too big (%d > %d)\n",
				ibi->slot->len + ibi->seg_len, ibi->max_len);
			hci_pio_मुक्त_ibi_slot(hci, pio);
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक hci_pio_request_ibi(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev,
			       स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	काष्ठा i3c_generic_ibi_pool *pool;
	काष्ठा hci_pio_dev_ibi_data *dev_ibi;

	dev_ibi = kदो_स्मृति(माप(*dev_ibi), GFP_KERNEL);
	अगर (!dev_ibi)
		वापस -ENOMEM;
	pool = i3c_generic_ibi_alloc_pool(dev, req);
	अगर (IS_ERR(pool)) अणु
		kमुक्त(dev_ibi);
		वापस PTR_ERR(pool);
	पूर्ण
	dev_ibi->pool = pool;
	dev_ibi->max_len = req->max_payload_len;
	dev_data->ibi_data = dev_ibi;
	वापस 0;
पूर्ण

अटल व्योम hci_pio_मुक्त_ibi(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	काष्ठा hci_pio_dev_ibi_data *dev_ibi = dev_data->ibi_data;

	dev_data->ibi_data = शून्य;
	i3c_generic_ibi_मुक्त_pool(dev_ibi->pool);
	kमुक्त(dev_ibi);
पूर्ण

अटल व्योम hci_pio_recycle_ibi_slot(काष्ठा i3c_hci *hci,
				    काष्ठा i3c_dev_desc *dev,
				    काष्ठा i3c_ibi_slot *slot)
अणु
	काष्ठा i3c_hci_dev_data *dev_data = i3c_dev_get_master_data(dev);
	काष्ठा hci_pio_dev_ibi_data *dev_ibi = dev_data->ibi_data;

	i3c_generic_ibi_recycle_slot(dev_ibi->pool, slot);
पूर्ण

अटल bool hci_pio_irq_handler(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक unused)
अणु
	काष्ठा hci_pio_data *pio = hci->io_data;
	u32 status;

	spin_lock(&pio->lock);
	status = pio_reg_पढ़ो(INTR_STATUS);
	DBG("(in) status: %#x/%#x", status, pio->enabled_irqs);
	status &= pio->enabled_irqs | STAT_LATENCY_WARNINGS;
	अगर (!status) अणु
		spin_unlock(&pio->lock);
		वापस false;
	पूर्ण

	अगर (status & STAT_IBI_STATUS_THLD)
		hci_pio_process_ibi(hci, pio);

	अगर (status & STAT_RX_THLD)
		अगर (hci_pio_process_rx(hci, pio))
			pio->enabled_irqs &= ~STAT_RX_THLD;
	अगर (status & STAT_TX_THLD)
		अगर (hci_pio_process_tx(hci, pio))
			pio->enabled_irqs &= ~STAT_TX_THLD;
	अगर (status & STAT_RESP_READY)
		अगर (hci_pio_process_resp(hci, pio))
			pio->enabled_irqs &= ~STAT_RESP_READY;

	अगर (unlikely(status & STAT_LATENCY_WARNINGS)) अणु
		pio_reg_ग_लिखो(INTR_STATUS, status & STAT_LATENCY_WARNINGS);
		dev_warn_ratelimited(&hci->master.dev,
				     "encountered warning condition %#lx\n",
				     status & STAT_LATENCY_WARNINGS);
	पूर्ण

	अगर (unlikely(status & STAT_ALL_ERRORS)) अणु
		pio_reg_ग_लिखो(INTR_STATUS, status & STAT_ALL_ERRORS);
		hci_pio_err(hci, pio, status & STAT_ALL_ERRORS);
	पूर्ण

	अगर (status & STAT_CMD_QUEUE_READY)
		अगर (hci_pio_process_cmd(hci, pio))
			pio->enabled_irqs &= ~STAT_CMD_QUEUE_READY;

	pio_reg_ग_लिखो(INTR_SIGNAL_ENABLE, pio->enabled_irqs);
	DBG("(out) status: %#x/%#x",
	    pio_reg_पढ़ो(INTR_STATUS), pio_reg_पढ़ो(INTR_SIGNAL_ENABLE));
	spin_unlock(&pio->lock);
	वापस true;
पूर्ण

स्थिर काष्ठा hci_io_ops mipi_i3c_hci_pio = अणु
	.init			= hci_pio_init,
	.cleanup		= hci_pio_cleanup,
	.queue_xfer		= hci_pio_queue_xfer,
	.dequeue_xfer		= hci_pio_dequeue_xfer,
	.irq_handler		= hci_pio_irq_handler,
	.request_ibi		= hci_pio_request_ibi,
	.मुक्त_ibi		= hci_pio_मुक्त_ibi,
	.recycle_ibi_slot	= hci_pio_recycle_ibi_slot,
पूर्ण;
