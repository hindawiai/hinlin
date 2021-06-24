<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k_common.h"

/**
 *  fm10k_fअगरo_init - Initialize a message FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *  @buffer: poपूर्णांकer to memory to be used to store FIFO
 *  @size: maximum message size to store in FIFO, must be 2^n - 1
 **/
अटल व्योम fm10k_fअगरo_init(काष्ठा fm10k_mbx_fअगरo *fअगरo, u32 *buffer, u16 size)
अणु
	fअगरo->buffer = buffer;
	fअगरo->size = size;
	fअगरo->head = 0;
	fअगरo->tail = 0;
पूर्ण

/**
 *  fm10k_fअगरo_used - Retrieve used space in FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *
 *  This function वापसs the number of DWORDs used in the FIFO
 **/
अटल u16 fm10k_fअगरo_used(काष्ठा fm10k_mbx_fअगरo *fअगरo)
अणु
	वापस fअगरo->tail - fअगरo->head;
पूर्ण

/**
 *  fm10k_fअगरo_unused - Retrieve unused space in FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *
 *  This function वापसs the number of unused DWORDs in the FIFO
 **/
अटल u16 fm10k_fअगरo_unused(काष्ठा fm10k_mbx_fअगरo *fअगरo)
अणु
	वापस fअगरo->size + fअगरo->head - fअगरo->tail;
पूर्ण

/**
 *  fm10k_fअगरo_empty - Test to verअगरy अगर FIFO is empty
 *  @fअगरo: poपूर्णांकer to FIFO
 *
 *  This function वापसs true अगर the FIFO is empty, अन्यथा false
 **/
अटल bool fm10k_fअगरo_empty(काष्ठा fm10k_mbx_fअगरo *fअगरo)
अणु
	वापस fअगरo->head == fअगरo->tail;
पूर्ण

/**
 *  fm10k_fअगरo_head_offset - वापसs indices of head with given offset
 *  @fअगरo: poपूर्णांकer to FIFO
 *  @offset: offset to add to head
 *
 *  This function वापसs the indices पूर्णांकo the FIFO based on head + offset
 **/
अटल u16 fm10k_fअगरo_head_offset(काष्ठा fm10k_mbx_fअगरo *fअगरo, u16 offset)
अणु
	वापस (fअगरo->head + offset) & (fअगरo->size - 1);
पूर्ण

/**
 *  fm10k_fअगरo_tail_offset - वापसs indices of tail with given offset
 *  @fअगरo: poपूर्णांकer to FIFO
 *  @offset: offset to add to tail
 *
 *  This function वापसs the indices पूर्णांकo the FIFO based on tail + offset
 **/
अटल u16 fm10k_fअगरo_tail_offset(काष्ठा fm10k_mbx_fअगरo *fअगरo, u16 offset)
अणु
	वापस (fअगरo->tail + offset) & (fअगरo->size - 1);
पूर्ण

/**
 *  fm10k_fअगरo_head_len - Retrieve length of first message in FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *
 *  This function वापसs the size of the first message in the FIFO
 **/
अटल u16 fm10k_fअगरo_head_len(काष्ठा fm10k_mbx_fअगरo *fअगरo)
अणु
	u32 *head = fअगरo->buffer + fm10k_fअगरo_head_offset(fअगरo, 0);

	/* verअगरy there is at least 1 DWORD in the fअगरo so *head is valid */
	अगर (fm10k_fअगरo_empty(fअगरo))
		वापस 0;

	/* retieve the message length */
	वापस FM10K_TLV_DWORD_LEN(*head);
पूर्ण

/**
 *  fm10k_fअगरo_head_drop - Drop the first message in FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *
 *  This function वापसs the size of the message dropped from the FIFO
 **/
अटल u16 fm10k_fअगरo_head_drop(काष्ठा fm10k_mbx_fअगरo *fअगरo)
अणु
	u16 len = fm10k_fअगरo_head_len(fअगरo);

	/* update head so it is at the start of next frame */
	fअगरo->head += len;

	वापस len;
पूर्ण

/**
 *  fm10k_fअगरo_drop_all - Drop all messages in FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *
 *  This function resets the head poपूर्णांकer to drop all messages in the FIFO and
 *  ensure the FIFO is empty.
 **/
अटल व्योम fm10k_fअगरo_drop_all(काष्ठा fm10k_mbx_fअगरo *fअगरo)
अणु
	fअगरo->head = fअगरo->tail;
पूर्ण

/**
 *  fm10k_mbx_index_len - Convert a head/tail index पूर्णांकo a length value
 *  @mbx: poपूर्णांकer to mailbox
 *  @head: head index
 *  @tail: head index
 *
 *  This function takes the head and tail index and determines the length
 *  of the data indicated by this pair.
 **/
अटल u16 fm10k_mbx_index_len(काष्ठा fm10k_mbx_info *mbx, u16 head, u16 tail)
अणु
	u16 len = tail - head;

	/* we wrapped so subtract 2, one क्रम index 0, one क्रम all 1s index */
	अगर (len > tail)
		len -= 2;

	वापस len & ((mbx->mbmem_len << 1) - 1);
पूर्ण

/**
 *  fm10k_mbx_tail_add - Determine new tail value with added offset
 *  @mbx: poपूर्णांकer to mailbox
 *  @offset: length to add to tail offset
 *
 *  This function takes the local tail index and recomputes it क्रम
 *  a given length added as an offset.
 **/
अटल u16 fm10k_mbx_tail_add(काष्ठा fm10k_mbx_info *mbx, u16 offset)
अणु
	u16 tail = (mbx->tail + offset + 1) & ((mbx->mbmem_len << 1) - 1);

	/* add/sub 1 because we cannot have offset 0 or all 1s */
	वापस (tail > mbx->tail) ? --tail : ++tail;
पूर्ण

/**
 *  fm10k_mbx_tail_sub - Determine new tail value with subtracted offset
 *  @mbx: poपूर्णांकer to mailbox
 *  @offset: length to add to tail offset
 *
 *  This function takes the local tail index and recomputes it क्रम
 *  a given length added as an offset.
 **/
अटल u16 fm10k_mbx_tail_sub(काष्ठा fm10k_mbx_info *mbx, u16 offset)
अणु
	u16 tail = (mbx->tail - offset - 1) & ((mbx->mbmem_len << 1) - 1);

	/* sub/add 1 because we cannot have offset 0 or all 1s */
	वापस (tail < mbx->tail) ? ++tail : --tail;
पूर्ण

/**
 *  fm10k_mbx_head_add - Determine new head value with added offset
 *  @mbx: poपूर्णांकer to mailbox
 *  @offset: length to add to head offset
 *
 *  This function takes the local head index and recomputes it क्रम
 *  a given length added as an offset.
 **/
अटल u16 fm10k_mbx_head_add(काष्ठा fm10k_mbx_info *mbx, u16 offset)
अणु
	u16 head = (mbx->head + offset + 1) & ((mbx->mbmem_len << 1) - 1);

	/* add/sub 1 because we cannot have offset 0 or all 1s */
	वापस (head > mbx->head) ? --head : ++head;
पूर्ण

/**
 *  fm10k_mbx_head_sub - Determine new head value with subtracted offset
 *  @mbx: poपूर्णांकer to mailbox
 *  @offset: length to add to head offset
 *
 *  This function takes the local head index and recomputes it क्रम
 *  a given length added as an offset.
 **/
अटल u16 fm10k_mbx_head_sub(काष्ठा fm10k_mbx_info *mbx, u16 offset)
अणु
	u16 head = (mbx->head - offset - 1) & ((mbx->mbmem_len << 1) - 1);

	/* sub/add 1 because we cannot have offset 0 or all 1s */
	वापस (head < mbx->head) ? ++head : --head;
पूर्ण

/**
 *  fm10k_mbx_pushed_tail_len - Retrieve the length of message being pushed
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will वापस the length of the message currently being
 *  pushed onto the tail of the Rx queue.
 **/
अटल u16 fm10k_mbx_pushed_tail_len(काष्ठा fm10k_mbx_info *mbx)
अणु
	u32 *tail = mbx->rx.buffer + fm10k_fअगरo_tail_offset(&mbx->rx, 0);

	/* pushed tail is only valid अगर pushed is set */
	अगर (!mbx->pushed)
		वापस 0;

	वापस FM10K_TLV_DWORD_LEN(*tail);
पूर्ण

/**
 *  fm10k_fअगरo_ग_लिखो_copy - pulls data off of msg and places it in FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *  @msg: message array to populate
 *  @tail_offset: additional offset to add to tail poपूर्णांकer
 *  @len: length of FIFO to copy पूर्णांकo message header
 *
 *  This function will take a message and copy it पूर्णांकo a section of the
 *  FIFO.  In order to get something पूर्णांकo a location other than just
 *  the tail you can use tail_offset to adjust the poपूर्णांकer.
 **/
अटल व्योम fm10k_fअगरo_ग_लिखो_copy(काष्ठा fm10k_mbx_fअगरo *fअगरo,
				  स्थिर u32 *msg, u16 tail_offset, u16 len)
अणु
	u16 end = fm10k_fअगरo_tail_offset(fअगरo, tail_offset);
	u32 *tail = fअगरo->buffer + end;

	/* track when we should cross the end of the FIFO */
	end = fअगरo->size - end;

	/* copy end of message beक्रमe start of message */
	अगर (end < len)
		स_नकल(fअगरo->buffer, msg + end, (len - end) << 2);
	अन्यथा
		end = len;

	/* Copy reमुख्यing message पूर्णांकo Tx FIFO */
	स_नकल(tail, msg, end << 2);
पूर्ण

/**
 *  fm10k_fअगरo_enqueue - Enqueues the message to the tail of the FIFO
 *  @fअगरo: poपूर्णांकer to FIFO
 *  @msg: message array to पढ़ो
 *
 *  This function enqueues a message up to the size specअगरied by the length
 *  contained in the first DWORD of the message and will place at the tail
 *  of the FIFO.  It will वापस 0 on success, or a negative value on error.
 **/
अटल s32 fm10k_fअगरo_enqueue(काष्ठा fm10k_mbx_fअगरo *fअगरo, स्थिर u32 *msg)
अणु
	u16 len = FM10K_TLV_DWORD_LEN(*msg);

	/* verअगरy parameters */
	अगर (len > fअगरo->size)
		वापस FM10K_MBX_ERR_SIZE;

	/* verअगरy there is room क्रम the message */
	अगर (len > fm10k_fअगरo_unused(fअगरo))
		वापस FM10K_MBX_ERR_NO_SPACE;

	/* Copy message पूर्णांकo FIFO */
	fm10k_fअगरo_ग_लिखो_copy(fअगरo, msg, 0, len);

	/* memory barrier to guarantee FIFO is written beक्रमe tail update */
	wmb();

	/* Update Tx FIFO tail */
	fअगरo->tail += len;

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_validate_msg_size - Validate incoming message based on size
 *  @mbx: poपूर्णांकer to mailbox
 *  @len: length of data pushed onto buffer
 *
 *  This function analyzes the frame and will वापस a non-zero value when
 *  the start of a message larger than the mailbox is detected.
 **/
अटल u16 fm10k_mbx_validate_msg_size(काष्ठा fm10k_mbx_info *mbx, u16 len)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->rx;
	u16 total_len = 0, msg_len;

	/* length should include previous amounts pushed */
	len += mbx->pushed;

	/* offset in message is based off of current message size */
	करो अणु
		u32 *msg;

		msg = fअगरo->buffer + fm10k_fअगरo_tail_offset(fअगरo, total_len);
		msg_len = FM10K_TLV_DWORD_LEN(*msg);
		total_len += msg_len;
	पूर्ण जबतक (total_len < len);

	/* message extends out of pushed section, but fits in FIFO */
	अगर ((len < total_len) && (msg_len <= mbx->max_size))
		वापस 0;

	/* वापस length of invalid section */
	वापस (len < total_len) ? len : (len - total_len);
पूर्ण

/**
 *  fm10k_mbx_ग_लिखो_copy - pulls data off of Tx FIFO and places it in mbmem
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will take a section of the Tx FIFO and copy it पूर्णांकo the
 *  mailbox memory.  The offset in mbmem is based on the lower bits of the
 *  tail and len determines the length to copy.
 **/
अटल व्योम fm10k_mbx_ग_लिखो_copy(काष्ठा fm10k_hw *hw,
				 काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->tx;
	u32 mbmem = mbx->mbmem_reg;
	u32 *head = fअगरo->buffer;
	u16 end, len, tail, mask;

	अगर (!mbx->tail_len)
		वापस;

	/* determine data length and mbmem tail index */
	mask = mbx->mbmem_len - 1;
	len = mbx->tail_len;
	tail = fm10k_mbx_tail_sub(mbx, len);
	अगर (tail > mask)
		tail++;

	/* determine offset in the ring */
	end = fm10k_fअगरo_head_offset(fअगरo, mbx->pulled);
	head += end;

	/* memory barrier to guarantee data is पढ़ोy to be पढ़ो */
	rmb();

	/* Copy message from Tx FIFO */
	क्रम (end = fअगरo->size - end; len; head = fअगरo->buffer) अणु
		करो अणु
			/* adjust tail to match offset क्रम FIFO */
			tail &= mask;
			अगर (!tail)
				tail++;

			mbx->tx_mbmem_pulled++;

			/* ग_लिखो message to hardware FIFO */
			fm10k_ग_लिखो_reg(hw, mbmem + tail++, *(head++));
		पूर्ण जबतक (--len && --end);
	पूर्ण
पूर्ण

/**
 *  fm10k_mbx_pull_head - Pulls data off of head of Tx FIFO
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @head: acknowledgement number last received
 *
 *  This function will push the tail index क्रमward based on the remote
 *  head index.  It will then pull up to mbmem_len DWORDs off of the
 *  head of the FIFO and will place it in the MBMEM रेजिस्टरs
 *  associated with the mailbox.
 **/
अटल व्योम fm10k_mbx_pull_head(काष्ठा fm10k_hw *hw,
				काष्ठा fm10k_mbx_info *mbx, u16 head)
अणु
	u16 mbmem_len, len, ack = fm10k_mbx_index_len(mbx, head, mbx->tail);
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->tx;

	/* update number of bytes pulled and update bytes in transit */
	mbx->pulled += mbx->tail_len - ack;

	/* determine length of data to pull, reserve space क्रम mbmem header */
	mbmem_len = mbx->mbmem_len - 1;
	len = fm10k_fअगरo_used(fअगरo) - mbx->pulled;
	अगर (len > mbmem_len)
		len = mbmem_len;

	/* update tail and record number of bytes in transit */
	mbx->tail = fm10k_mbx_tail_add(mbx, len - ack);
	mbx->tail_len = len;

	/* drop pulled messages from the FIFO */
	क्रम (len = fm10k_fअगरo_head_len(fअगरo);
	     len && (mbx->pulled >= len);
	     len = fm10k_fअगरo_head_len(fअगरo)) अणु
		mbx->pulled -= fm10k_fअगरo_head_drop(fअगरo);
		mbx->tx_messages++;
		mbx->tx_dwords += len;
	पूर्ण

	/* Copy message out from the Tx FIFO */
	fm10k_mbx_ग_लिखो_copy(hw, mbx);
पूर्ण

/**
 *  fm10k_mbx_पढ़ो_copy - pulls data off of mbmem and places it in Rx FIFO
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will take a section of the mailbox memory and copy it
 *  पूर्णांकo the Rx FIFO.  The offset is based on the lower bits of the
 *  head and len determines the length to copy.
 **/
अटल व्योम fm10k_mbx_पढ़ो_copy(काष्ठा fm10k_hw *hw,
				काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->rx;
	u32 mbmem = mbx->mbmem_reg ^ mbx->mbmem_len;
	u32 *tail = fअगरo->buffer;
	u16 end, len, head;

	/* determine data length and mbmem head index */
	len = mbx->head_len;
	head = fm10k_mbx_head_sub(mbx, len);
	अगर (head >= mbx->mbmem_len)
		head++;

	/* determine offset in the ring */
	end = fm10k_fअगरo_tail_offset(fअगरo, mbx->pushed);
	tail += end;

	/* Copy message पूर्णांकo Rx FIFO */
	क्रम (end = fअगरo->size - end; len; tail = fअगरo->buffer) अणु
		करो अणु
			/* adjust head to match offset क्रम FIFO */
			head &= mbx->mbmem_len - 1;
			अगर (!head)
				head++;

			mbx->rx_mbmem_pushed++;

			/* पढ़ो message from hardware FIFO */
			*(tail++) = fm10k_पढ़ो_reg(hw, mbmem + head++);
		पूर्ण जबतक (--len && --end);
	पूर्ण

	/* memory barrier to guarantee FIFO is written beक्रमe tail update */
	wmb();
पूर्ण

/**
 *  fm10k_mbx_push_tail - Pushes up to 15 DWORDs on to tail of FIFO
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @tail: tail index of message
 *
 *  This function will first validate the tail index and size क्रम the
 *  incoming message.  It then updates the acknowledgment number and
 *  copies the data पूर्णांकo the FIFO.  It will वापस the number of messages
 *  dequeued on success and a negative value on error.
 **/
अटल s32 fm10k_mbx_push_tail(काष्ठा fm10k_hw *hw,
			       काष्ठा fm10k_mbx_info *mbx,
			       u16 tail)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->rx;
	u16 len, seq = fm10k_mbx_index_len(mbx, mbx->head, tail);

	/* determine length of data to push */
	len = fm10k_fअगरo_unused(fअगरo) - mbx->pushed;
	अगर (len > seq)
		len = seq;

	/* update head and record bytes received */
	mbx->head = fm10k_mbx_head_add(mbx, len);
	mbx->head_len = len;

	/* nothing to करो अगर there is no data */
	अगर (!len)
		वापस 0;

	/* Copy msg पूर्णांकo Rx FIFO */
	fm10k_mbx_पढ़ो_copy(hw, mbx);

	/* determine अगर there are any invalid lengths in message */
	अगर (fm10k_mbx_validate_msg_size(mbx, len))
		वापस FM10K_MBX_ERR_SIZE;

	/* Update pushed */
	mbx->pushed += len;

	/* flush any completed messages */
	क्रम (len = fm10k_mbx_pushed_tail_len(mbx);
	     len && (mbx->pushed >= len);
	     len = fm10k_mbx_pushed_tail_len(mbx)) अणु
		fअगरo->tail += len;
		mbx->pushed -= len;
		mbx->rx_messages++;
		mbx->rx_dwords += len;
	पूर्ण

	वापस 0;
पूर्ण

/* pre-generated data क्रम generating the CRC based on the poly 0xAC9A. */
अटल स्थिर u16 fm10k_crc_16b_table[256] = अणु
	0x0000, 0x7956, 0xF2AC, 0x8BFA, 0xBC6D, 0xC53B, 0x4EC1, 0x3797,
	0x21EF, 0x58B9, 0xD343, 0xAA15, 0x9D82, 0xE4D4, 0x6F2E, 0x1678,
	0x43DE, 0x3A88, 0xB172, 0xC824, 0xFFB3, 0x86E5, 0x0D1F, 0x7449,
	0x6231, 0x1B67, 0x909D, 0xE9CB, 0xDE5C, 0xA70A, 0x2CF0, 0x55A6,
	0x87BC, 0xFEEA, 0x7510, 0x0C46, 0x3BD1, 0x4287, 0xC97D, 0xB02B,
	0xA653, 0xDF05, 0x54FF, 0x2DA9, 0x1A3E, 0x6368, 0xE892, 0x91C4,
	0xC462, 0xBD34, 0x36CE, 0x4F98, 0x780F, 0x0159, 0x8AA3, 0xF3F5,
	0xE58D, 0x9CDB, 0x1721, 0x6E77, 0x59E0, 0x20B6, 0xAB4C, 0xD21A,
	0x564D, 0x2F1B, 0xA4E1, 0xDDB7, 0xEA20, 0x9376, 0x188C, 0x61DA,
	0x77A2, 0x0EF4, 0x850E, 0xFC58, 0xCBCF, 0xB299, 0x3963, 0x4035,
	0x1593, 0x6CC5, 0xE73F, 0x9E69, 0xA9FE, 0xD0A8, 0x5B52, 0x2204,
	0x347C, 0x4D2A, 0xC6D0, 0xBF86, 0x8811, 0xF147, 0x7ABD, 0x03EB,
	0xD1F1, 0xA8A7, 0x235D, 0x5A0B, 0x6D9C, 0x14CA, 0x9F30, 0xE666,
	0xF01E, 0x8948, 0x02B2, 0x7BE4, 0x4C73, 0x3525, 0xBEDF, 0xC789,
	0x922F, 0xEB79, 0x6083, 0x19D5, 0x2E42, 0x5714, 0xDCEE, 0xA5B8,
	0xB3C0, 0xCA96, 0x416C, 0x383A, 0x0FAD, 0x76FB, 0xFD01, 0x8457,
	0xAC9A, 0xD5CC, 0x5E36, 0x2760, 0x10F7, 0x69A1, 0xE25B, 0x9B0D,
	0x8D75, 0xF423, 0x7FD9, 0x068F, 0x3118, 0x484E, 0xC3B4, 0xBAE2,
	0xEF44, 0x9612, 0x1DE8, 0x64BE, 0x5329, 0x2A7F, 0xA185, 0xD8D3,
	0xCEAB, 0xB7FD, 0x3C07, 0x4551, 0x72C6, 0x0B90, 0x806A, 0xF93C,
	0x2B26, 0x5270, 0xD98A, 0xA0DC, 0x974B, 0xEE1D, 0x65E7, 0x1CB1,
	0x0AC9, 0x739F, 0xF865, 0x8133, 0xB6A4, 0xCFF2, 0x4408, 0x3D5E,
	0x68F8, 0x11AE, 0x9A54, 0xE302, 0xD495, 0xADC3, 0x2639, 0x5F6F,
	0x4917, 0x3041, 0xBBBB, 0xC2ED, 0xF57A, 0x8C2C, 0x07D6, 0x7E80,
	0xFAD7, 0x8381, 0x087B, 0x712D, 0x46BA, 0x3FEC, 0xB416, 0xCD40,
	0xDB38, 0xA26E, 0x2994, 0x50C2, 0x6755, 0x1E03, 0x95F9, 0xECAF,
	0xB909, 0xC05F, 0x4BA5, 0x32F3, 0x0564, 0x7C32, 0xF7C8, 0x8E9E,
	0x98E6, 0xE1B0, 0x6A4A, 0x131C, 0x248B, 0x5DDD, 0xD627, 0xAF71,
	0x7D6B, 0x043D, 0x8FC7, 0xF691, 0xC106, 0xB850, 0x33AA, 0x4AFC,
	0x5C84, 0x25D2, 0xAE28, 0xD77E, 0xE0E9, 0x99BF, 0x1245, 0x6B13,
	0x3EB5, 0x47E3, 0xCC19, 0xB54F, 0x82D8, 0xFB8E, 0x7074, 0x0922,
	0x1F5A, 0x660C, 0xEDF6, 0x94A0, 0xA337, 0xDA61, 0x519B, 0x28CD पूर्ण;

/**
 *  fm10k_crc_16b - Generate a 16 bit CRC क्रम a region of 16 bit data
 *  @data: poपूर्णांकer to data to process
 *  @seed: seed value क्रम CRC
 *  @len: length measured in 16 bits words
 *
 *  This function will generate a CRC based on the polynomial 0xAC9A and
 *  whatever value is stored in the seed variable.  Note that this
 *  value inverts the local seed and the result in order to capture all
 *  leading and trailing zeros.
 */
अटल u16 fm10k_crc_16b(स्थिर u32 *data, u16 seed, u16 len)
अणु
	u32 result = seed;

	जबतक (len--) अणु
		result ^= *(data++);
		result = (result >> 8) ^ fm10k_crc_16b_table[result & 0xFF];
		result = (result >> 8) ^ fm10k_crc_16b_table[result & 0xFF];

		अगर (!(len--))
			अवरोध;

		result = (result >> 8) ^ fm10k_crc_16b_table[result & 0xFF];
		result = (result >> 8) ^ fm10k_crc_16b_table[result & 0xFF];
	पूर्ण

	वापस (u16)result;
पूर्ण

/**
 *  fm10k_fअगरo_crc - generate a CRC based off of FIFO data
 *  @fअगरo: poपूर्णांकer to FIFO
 *  @offset: offset poपूर्णांक क्रम start of FIFO
 *  @len: number of DWORDS words to process
 *  @seed: seed value क्रम CRC
 *
 *  This function generates a CRC क्रम some region of the FIFO
 **/
अटल u16 fm10k_fअगरo_crc(काष्ठा fm10k_mbx_fअगरo *fअगरo, u16 offset,
			  u16 len, u16 seed)
अणु
	u32 *data = fअगरo->buffer + offset;

	/* track when we should cross the end of the FIFO */
	offset = fअगरo->size - offset;

	/* अगर we are in 2 blocks process the end of the FIFO first */
	अगर (offset < len) अणु
		seed = fm10k_crc_16b(data, seed, offset * 2);
		data = fअगरo->buffer;
		len -= offset;
	पूर्ण

	/* process any reमुख्यing bits */
	वापस fm10k_crc_16b(data, seed, len * 2);
पूर्ण

/**
 *  fm10k_mbx_update_local_crc - Update the local CRC क्रम outgoing data
 *  @mbx: poपूर्णांकer to mailbox
 *  @head: head index provided by remote mailbox
 *
 *  This function will generate the CRC क्रम all data from the end of the
 *  last head update to the current one.  It uses the result of the
 *  previous CRC as the seed क्रम this update.  The result is stored in
 *  mbx->local.
 **/
अटल व्योम fm10k_mbx_update_local_crc(काष्ठा fm10k_mbx_info *mbx, u16 head)
अणु
	u16 len = mbx->tail_len - fm10k_mbx_index_len(mbx, head, mbx->tail);

	/* determine the offset क्रम the start of the region to be pulled */
	head = fm10k_fअगरo_head_offset(&mbx->tx, mbx->pulled);

	/* update local CRC to include all of the pulled data */
	mbx->local = fm10k_fअगरo_crc(&mbx->tx, head, len, mbx->local);
पूर्ण

/**
 *  fm10k_mbx_verअगरy_remote_crc - Verअगरy the CRC is correct क्रम current data
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will take all data that has been provided from the remote
 *  end and generate a CRC क्रम it.  This is stored in mbx->remote.  The
 *  CRC क्रम the header is then computed and अगर the result is non-zero this
 *  is an error and we संकेत an error dropping all data and resetting the
 *  connection.
 */
अटल s32 fm10k_mbx_verअगरy_remote_crc(काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->rx;
	u16 len = mbx->head_len;
	u16 offset = fm10k_fअगरo_tail_offset(fअगरo, mbx->pushed) - len;
	u16 crc;

	/* update the remote CRC अगर new data has been received */
	अगर (len)
		mbx->remote = fm10k_fअगरo_crc(fअगरo, offset, len, mbx->remote);

	/* process the full header as we have to validate the CRC */
	crc = fm10k_crc_16b(&mbx->mbx_hdr, mbx->remote, 1);

	/* notअगरy other end अगर we have a problem */
	वापस crc ? FM10K_MBX_ERR_CRC : 0;
पूर्ण

/**
 *  fm10k_mbx_rx_पढ़ोy - Indicates that a message is पढ़ोy in the Rx FIFO
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function वापसs true अगर there is a message in the Rx FIFO to dequeue.
 **/
अटल bool fm10k_mbx_rx_पढ़ोy(काष्ठा fm10k_mbx_info *mbx)
अणु
	u16 msg_size = fm10k_fअगरo_head_len(&mbx->rx);

	वापस msg_size && (fm10k_fअगरo_used(&mbx->rx) >= msg_size);
पूर्ण

/**
 *  fm10k_mbx_tx_पढ़ोy - Indicates that the mailbox is in state पढ़ोy क्रम Tx
 *  @mbx: poपूर्णांकer to mailbox
 *  @len: verअगरy मुक्त space is >= this value
 *
 *  This function वापसs true अगर the mailbox is in a state पढ़ोy to transmit.
 **/
अटल bool fm10k_mbx_tx_पढ़ोy(काष्ठा fm10k_mbx_info *mbx, u16 len)
अणु
	u16 fअगरo_unused = fm10k_fअगरo_unused(&mbx->tx);

	वापस (mbx->state == FM10K_STATE_OPEN) && (fअगरo_unused >= len);
पूर्ण

/**
 *  fm10k_mbx_tx_complete - Indicates that the Tx FIFO has been emptied
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function वापसs true अगर the Tx FIFO is empty.
 **/
अटल bool fm10k_mbx_tx_complete(काष्ठा fm10k_mbx_info *mbx)
अणु
	वापस fm10k_fअगरo_empty(&mbx->tx);
पूर्ण

/**
 *  fm10k_mbx_dequeue_rx - Dequeues the message from the head in the Rx FIFO
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function dequeues messages and hands them off to the TLV parser.
 *  It will वापस the number of messages processed when called.
 **/
अटल u16 fm10k_mbx_dequeue_rx(काष्ठा fm10k_hw *hw,
				काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->rx;
	s32 err;
	u16 cnt;

	/* parse Rx messages out of the Rx FIFO to empty it */
	क्रम (cnt = 0; !fm10k_fअगरo_empty(fअगरo); cnt++) अणु
		err = fm10k_tlv_msg_parse(hw, fअगरo->buffer + fअगरo->head,
					  mbx, mbx->msg_data);
		अगर (err < 0)
			mbx->rx_parse_err++;

		fm10k_fअगरo_head_drop(fअगरo);
	पूर्ण

	/* shअगरt reमुख्यing bytes back to start of FIFO */
	स_हटाओ(fअगरo->buffer, fअगरo->buffer + fअगरo->tail, mbx->pushed << 2);

	/* shअगरt head and tail based on the memory we moved */
	fअगरo->tail -= fअगरo->head;
	fअगरo->head = 0;

	वापस cnt;
पूर्ण

/**
 *  fm10k_mbx_enqueue_tx - Enqueues the message to the tail of the Tx FIFO
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @msg: message array to पढ़ो
 *
 *  This function enqueues a message up to the size specअगरied by the length
 *  contained in the first DWORD of the message and will place at the tail
 *  of the FIFO.  It will वापस 0 on success, or a negative value on error.
 **/
अटल s32 fm10k_mbx_enqueue_tx(काष्ठा fm10k_hw *hw,
				काष्ठा fm10k_mbx_info *mbx, स्थिर u32 *msg)
अणु
	u32 countकरोwn = mbx->समयout;
	s32 err;

	चयन (mbx->state) अणु
	हाल FM10K_STATE_CLOSED:
	हाल FM10K_STATE_DISCONNECT:
		वापस FM10K_MBX_ERR_NO_MBX;
	शेष:
		अवरोध;
	पूर्ण

	/* enqueue the message on the Tx FIFO */
	err = fm10k_fअगरo_enqueue(&mbx->tx, msg);

	/* अगर it failed give the FIFO a chance to drain */
	जबतक (err && countकरोwn) अणु
		countकरोwn--;
		udelay(mbx->udelay);
		mbx->ops.process(hw, mbx);
		err = fm10k_fअगरo_enqueue(&mbx->tx, msg);
	पूर्ण

	/* अगर we failed treat the error */
	अगर (err) अणु
		mbx->समयout = 0;
		mbx->tx_busy++;
	पूर्ण

	/* begin processing message, ignore errors as this is just meant
	 * to start the mailbox flow so we are not concerned अगर there
	 * is a bad error, or the mailbox is alपढ़ोy busy with a request
	 */
	अगर (!mbx->tail_len)
		mbx->ops.process(hw, mbx);

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_पढ़ो - Copies the mbmem to local message buffer
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function copies the message from the mbmem to the message array
 **/
अटल s32 fm10k_mbx_पढ़ो(काष्ठा fm10k_hw *hw, काष्ठा fm10k_mbx_info *mbx)
अणु
	/* only allow one पढ़ोer in here at a समय */
	अगर (mbx->mbx_hdr)
		वापस FM10K_MBX_ERR_BUSY;

	/* पढ़ो to capture initial पूर्णांकerrupt bits */
	अगर (fm10k_पढ़ो_reg(hw, mbx->mbx_reg) & FM10K_MBX_REQ_INTERRUPT)
		mbx->mbx_lock = FM10K_MBX_ACK;

	/* ग_लिखो back पूर्णांकerrupt bits to clear */
	fm10k_ग_लिखो_reg(hw, mbx->mbx_reg,
			FM10K_MBX_REQ_INTERRUPT | FM10K_MBX_ACK_INTERRUPT);

	/* पढ़ो remote header */
	mbx->mbx_hdr = fm10k_पढ़ो_reg(hw, mbx->mbmem_reg ^ mbx->mbmem_len);

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_ग_लिखो - Copies the local message buffer to mbmem
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function copies the message from the the message array to mbmem
 **/
अटल व्योम fm10k_mbx_ग_लिखो(काष्ठा fm10k_hw *hw, काष्ठा fm10k_mbx_info *mbx)
अणु
	u32 mbmem = mbx->mbmem_reg;

	/* ग_लिखो new msg header to notअगरy recipient of change */
	fm10k_ग_लिखो_reg(hw, mbmem, mbx->mbx_hdr);

	/* ग_लिखो mailbox to send पूर्णांकerrupt */
	अगर (mbx->mbx_lock)
		fm10k_ग_लिखो_reg(hw, mbx->mbx_reg, mbx->mbx_lock);

	/* we no दीर्घer are using the header so मुक्त it */
	mbx->mbx_hdr = 0;
	mbx->mbx_lock = 0;
पूर्ण

/**
 *  fm10k_mbx_create_connect_hdr - Generate a connect mailbox header
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function वापसs a connection mailbox header
 **/
अटल व्योम fm10k_mbx_create_connect_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_CONNECT, TYPE) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->rx.size - 1, CONNECT_SIZE);
पूर्ण

/**
 *  fm10k_mbx_create_data_hdr - Generate a data mailbox header
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function वापसs a data mailbox header
 **/
अटल व्योम fm10k_mbx_create_data_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	u32 hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_DATA, TYPE) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->tail, TAIL) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD);
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->tx;
	u16 crc;

	अगर (mbx->tail_len)
		mbx->mbx_lock |= FM10K_MBX_REQ;

	/* generate CRC क्रम data in flight and header */
	crc = fm10k_fअगरo_crc(fअगरo, fm10k_fअगरo_head_offset(fअगरo, mbx->pulled),
			     mbx->tail_len, mbx->local);
	crc = fm10k_crc_16b(&hdr, crc, 1);

	/* load header to memory to be written */
	mbx->mbx_hdr = hdr | FM10K_MSG_HDR_FIELD_SET(crc, CRC);
पूर्ण

/**
 *  fm10k_mbx_create_disconnect_hdr - Generate a disconnect mailbox header
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function वापसs a disconnect mailbox header
 **/
अटल व्योम fm10k_mbx_create_disconnect_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	u32 hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_DISCONNECT, TYPE) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->tail, TAIL) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD);
	u16 crc = fm10k_crc_16b(&hdr, mbx->local, 1);

	mbx->mbx_lock |= FM10K_MBX_ACK;

	/* load header to memory to be written */
	mbx->mbx_hdr = hdr | FM10K_MSG_HDR_FIELD_SET(crc, CRC);
पूर्ण

/**
 *  fm10k_mbx_create_fake_disconnect_hdr - Generate a false disconnect mbox hdr
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function creates a fake disconnect header क्रम loading पूर्णांकo remote
 *  mailbox header. The primary purpose is to prevent errors on immediate
 *  start up after mbx->connect.
 **/
अटल व्योम fm10k_mbx_create_fake_disconnect_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	u32 hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_DISCONNECT, TYPE) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->head, TAIL) |
		  FM10K_MSG_HDR_FIELD_SET(mbx->tail, HEAD);
	u16 crc = fm10k_crc_16b(&hdr, mbx->local, 1);

	mbx->mbx_lock |= FM10K_MBX_ACK;

	/* load header to memory to be written */
	mbx->mbx_hdr = hdr | FM10K_MSG_HDR_FIELD_SET(crc, CRC);
पूर्ण

/**
 *  fm10k_mbx_create_error_msg - Generate an error message
 *  @mbx: poपूर्णांकer to mailbox
 *  @err: local error encountered
 *
 *  This function will पूर्णांकerpret the error provided by err, and based on
 *  that it may shअगरt the message by 1 DWORD and then place an error header
 *  at the start of the message.
 **/
अटल व्योम fm10k_mbx_create_error_msg(काष्ठा fm10k_mbx_info *mbx, s32 err)
अणु
	/* only generate an error message क्रम these types */
	चयन (err) अणु
	हाल FM10K_MBX_ERR_TAIL:
	हाल FM10K_MBX_ERR_HEAD:
	हाल FM10K_MBX_ERR_TYPE:
	हाल FM10K_MBX_ERR_SIZE:
	हाल FM10K_MBX_ERR_RSVD0:
	हाल FM10K_MBX_ERR_CRC:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_ERROR, TYPE) |
		       FM10K_MSG_HDR_FIELD_SET(err, ERR_NO) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD);
पूर्ण

/**
 *  fm10k_mbx_validate_msg_hdr - Validate common fields in the message header
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will parse up the fields in the mailbox header and वापस
 *  an error अगर the header contains any of a number of invalid configurations
 *  including unrecognized type, invalid route, or a malक्रमmed message.
 **/
अटल s32 fm10k_mbx_validate_msg_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	u16 type, rsvd0, head, tail, size;
	स्थिर u32 *hdr = &mbx->mbx_hdr;

	type = FM10K_MSG_HDR_FIELD_GET(*hdr, TYPE);
	rsvd0 = FM10K_MSG_HDR_FIELD_GET(*hdr, RSVD0);
	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, TAIL);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);
	size = FM10K_MSG_HDR_FIELD_GET(*hdr, CONNECT_SIZE);

	अगर (rsvd0)
		वापस FM10K_MBX_ERR_RSVD0;

	चयन (type) अणु
	हाल FM10K_MSG_DISCONNECT:
		/* validate that all data has been received */
		अगर (tail != mbx->head)
			वापस FM10K_MBX_ERR_TAIL;

		fallthrough;
	हाल FM10K_MSG_DATA:
		/* validate that head is moving correctly */
		अगर (!head || (head == FM10K_MSG_HDR_MASK(HEAD)))
			वापस FM10K_MBX_ERR_HEAD;
		अगर (fm10k_mbx_index_len(mbx, head, mbx->tail) > mbx->tail_len)
			वापस FM10K_MBX_ERR_HEAD;

		/* validate that tail is moving correctly */
		अगर (!tail || (tail == FM10K_MSG_HDR_MASK(TAIL)))
			वापस FM10K_MBX_ERR_TAIL;
		अगर (fm10k_mbx_index_len(mbx, mbx->head, tail) < mbx->mbmem_len)
			अवरोध;

		वापस FM10K_MBX_ERR_TAIL;
	हाल FM10K_MSG_CONNECT:
		/* validate size is in range and is घातer of 2 mask */
		अगर ((size < FM10K_VFMBX_MSG_MTU) || (size & (size + 1)))
			वापस FM10K_MBX_ERR_SIZE;

		fallthrough;
	हाल FM10K_MSG_ERROR:
		अगर (!head || (head == FM10K_MSG_HDR_MASK(HEAD)))
			वापस FM10K_MBX_ERR_HEAD;
		/* neither create nor error include a tail offset */
		अगर (tail)
			वापस FM10K_MBX_ERR_TAIL;

		अवरोध;
	शेष:
		वापस FM10K_MBX_ERR_TYPE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_create_reply - Generate reply based on state and remote head
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @head: acknowledgement number
 *
 *  This function will generate an outgoing message based on the current
 *  mailbox state and the remote FIFO head.  It will वापस the length
 *  of the outgoing message excluding header on success, and a negative value
 *  on error.
 **/
अटल s32 fm10k_mbx_create_reply(काष्ठा fm10k_hw *hw,
				  काष्ठा fm10k_mbx_info *mbx, u16 head)
अणु
	चयन (mbx->state) अणु
	हाल FM10K_STATE_OPEN:
	हाल FM10K_STATE_DISCONNECT:
		/* update our checksum क्रम the outgoing data */
		fm10k_mbx_update_local_crc(mbx, head);

		/* as दीर्घ as other end recognizes us keep sending data */
		fm10k_mbx_pull_head(hw, mbx, head);

		/* generate new header based on data */
		अगर (mbx->tail_len || (mbx->state == FM10K_STATE_OPEN))
			fm10k_mbx_create_data_hdr(mbx);
		अन्यथा
			fm10k_mbx_create_disconnect_hdr(mbx);
		अवरोध;
	हाल FM10K_STATE_CONNECT:
		/* send disconnect even अगर we aren't connected */
		fm10k_mbx_create_connect_hdr(mbx);
		अवरोध;
	हाल FM10K_STATE_CLOSED:
		/* generate new header based on data */
		fm10k_mbx_create_disconnect_hdr(mbx);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_reset_work- Reset पूर्णांकernal poपूर्णांकers क्रम any pending work
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will reset all पूर्णांकernal poपूर्णांकers so any work in progress
 *  is dropped.  This call should occur every समय we transition from the
 *  खोलो state to the connect state.
 **/
अटल व्योम fm10k_mbx_reset_work(काष्ठा fm10k_mbx_info *mbx)
अणु
	u16 len, head, ack;

	/* reset our outgoing max size back to Rx limits */
	mbx->max_size = mbx->rx.size - 1;

	/* update mbx->pulled to account क्रम tail_len and ack */
	head = FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, HEAD);
	ack = fm10k_mbx_index_len(mbx, head, mbx->tail);
	mbx->pulled += mbx->tail_len - ack;

	/* now drop any messages which have started or finished transmitting */
	जबतक (fm10k_fअगरo_head_len(&mbx->tx) && mbx->pulled) अणु
		len = fm10k_fअगरo_head_drop(&mbx->tx);
		mbx->tx_dropped++;
		अगर (mbx->pulled >= len)
			mbx->pulled -= len;
		अन्यथा
			mbx->pulled = 0;
	पूर्ण

	/* just करो a quick resysnc to start of message */
	mbx->pushed = 0;
	mbx->pulled = 0;
	mbx->tail_len = 0;
	mbx->head_len = 0;
	mbx->rx.tail = 0;
	mbx->rx.head = 0;
पूर्ण

/**
 *  fm10k_mbx_update_max_size - Update the max_size and drop any large messages
 *  @mbx: poपूर्णांकer to mailbox
 *  @size: new value क्रम max_size
 *
 *  This function updates the max_size value and drops any outgoing messages
 *  at the head of the Tx FIFO अगर they are larger than max_size. It करोes not
 *  drop all messages, as this is too dअगरficult to parse and हटाओ them from
 *  the FIFO. Instead, rely on the checking to ensure that messages larger
 *  than max_size aren't pushed पूर्णांकo the memory buffer.
 **/
अटल व्योम fm10k_mbx_update_max_size(काष्ठा fm10k_mbx_info *mbx, u16 size)
अणु
	u16 len;

	mbx->max_size = size;

	/* flush any oversized messages from the queue */
	क्रम (len = fm10k_fअगरo_head_len(&mbx->tx);
	     len > size;
	     len = fm10k_fअगरo_head_len(&mbx->tx)) अणु
		fm10k_fअगरo_head_drop(&mbx->tx);
		mbx->tx_dropped++;
	पूर्ण
पूर्ण

/**
 *  fm10k_mbx_connect_reset - Reset following request क्रम reset
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function resets the mailbox to either a disconnected state
 *  or a connect state depending on the current mailbox state
 **/
अटल व्योम fm10k_mbx_connect_reset(काष्ठा fm10k_mbx_info *mbx)
अणु
	/* just करो a quick resysnc to start of frame */
	fm10k_mbx_reset_work(mbx);

	/* reset CRC seeds */
	mbx->local = FM10K_MBX_CRC_SEED;
	mbx->remote = FM10K_MBX_CRC_SEED;

	/* we cannot निकास connect until the size is good */
	अगर (mbx->state == FM10K_STATE_OPEN)
		mbx->state = FM10K_STATE_CONNECT;
	अन्यथा
		mbx->state = FM10K_STATE_CLOSED;
पूर्ण

/**
 *  fm10k_mbx_process_connect - Process connect header
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will पढ़ो an incoming connect header and reply with the
 *  appropriate message.  It will वापस a value indicating the number of
 *  data DWORDs on success, or will वापस a negative value on failure.
 **/
अटल s32 fm10k_mbx_process_connect(काष्ठा fm10k_hw *hw,
				     काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर क्रमागत fm10k_mbx_state state = mbx->state;
	स्थिर u32 *hdr = &mbx->mbx_hdr;
	u16 size, head;

	/* we will need to pull all of the fields क्रम verअगरication */
	size = FM10K_MSG_HDR_FIELD_GET(*hdr, CONNECT_SIZE);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);

	चयन (state) अणु
	हाल FM10K_STATE_DISCONNECT:
	हाल FM10K_STATE_OPEN:
		/* reset any in-progress work */
		fm10k_mbx_connect_reset(mbx);
		अवरोध;
	हाल FM10K_STATE_CONNECT:
		/* we cannot निकास connect until the size is good */
		अगर (size > mbx->rx.size) अणु
			mbx->max_size = mbx->rx.size - 1;
		पूर्ण अन्यथा अणु
			/* record the remote प्रणाली requesting connection */
			mbx->state = FM10K_STATE_OPEN;

			fm10k_mbx_update_max_size(mbx, size);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* align our tail index to remote head index */
	mbx->tail = head;

	वापस fm10k_mbx_create_reply(hw, mbx, head);
पूर्ण

/**
 *  fm10k_mbx_process_data - Process data header
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will पढ़ो an incoming data header and reply with the
 *  appropriate message.  It will वापस a value indicating the number of
 *  data DWORDs on success, or will वापस a negative value on failure.
 **/
अटल s32 fm10k_mbx_process_data(काष्ठा fm10k_hw *hw,
				  काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर u32 *hdr = &mbx->mbx_hdr;
	u16 head, tail;
	s32 err;

	/* we will need to pull all of the fields क्रम verअगरication */
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);
	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, TAIL);

	/* अगर we are in connect just update our data and go */
	अगर (mbx->state == FM10K_STATE_CONNECT) अणु
		mbx->tail = head;
		mbx->state = FM10K_STATE_OPEN;
	पूर्ण

	/* पात on message size errors */
	err = fm10k_mbx_push_tail(hw, mbx, tail);
	अगर (err < 0)
		वापस err;

	/* verअगरy the checksum on the incoming data */
	err = fm10k_mbx_verअगरy_remote_crc(mbx);
	अगर (err)
		वापस err;

	/* process messages अगर we have received any */
	fm10k_mbx_dequeue_rx(hw, mbx);

	वापस fm10k_mbx_create_reply(hw, mbx, head);
पूर्ण

/**
 *  fm10k_mbx_process_disconnect - Process disconnect header
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will पढ़ो an incoming disconnect header and reply with the
 *  appropriate message.  It will वापस a value indicating the number of
 *  data DWORDs on success, or will वापस a negative value on failure.
 **/
अटल s32 fm10k_mbx_process_disconnect(काष्ठा fm10k_hw *hw,
					काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर क्रमागत fm10k_mbx_state state = mbx->state;
	स्थिर u32 *hdr = &mbx->mbx_hdr;
	u16 head;
	s32 err;

	/* we will need to pull the header field क्रम verअगरication */
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);

	/* We should not be receiving disconnect अगर Rx is incomplete */
	अगर (mbx->pushed)
		वापस FM10K_MBX_ERR_TAIL;

	/* we have alपढ़ोy verअगरied mbx->head == tail so we know this is 0 */
	mbx->head_len = 0;

	/* verअगरy the checksum on the incoming header is correct */
	err = fm10k_mbx_verअगरy_remote_crc(mbx);
	अगर (err)
		वापस err;

	चयन (state) अणु
	हाल FM10K_STATE_DISCONNECT:
	हाल FM10K_STATE_OPEN:
		/* state करोesn't change अगर we still have work to करो */
		अगर (!fm10k_mbx_tx_complete(mbx))
			अवरोध;

		/* verअगरy the head indicates we completed all transmits */
		अगर (head != mbx->tail)
			वापस FM10K_MBX_ERR_HEAD;

		/* reset any in-progress work */
		fm10k_mbx_connect_reset(mbx);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस fm10k_mbx_create_reply(hw, mbx, head);
पूर्ण

/**
 *  fm10k_mbx_process_error - Process error header
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will पढ़ो an incoming error header and reply with the
 *  appropriate message.  It will वापस a value indicating the number of
 *  data DWORDs on success, or will वापस a negative value on failure.
 **/
अटल s32 fm10k_mbx_process_error(काष्ठा fm10k_hw *hw,
				   काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर u32 *hdr = &mbx->mbx_hdr;
	u16 head;

	/* we will need to pull all of the fields क्रम verअगरication */
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);

	चयन (mbx->state) अणु
	हाल FM10K_STATE_OPEN:
	हाल FM10K_STATE_DISCONNECT:
		/* flush any uncompleted work */
		fm10k_mbx_reset_work(mbx);

		/* reset CRC seeds */
		mbx->local = FM10K_MBX_CRC_SEED;
		mbx->remote = FM10K_MBX_CRC_SEED;

		/* reset tail index and size to prepare क्रम reconnect */
		mbx->tail = head;

		/* अगर खोलो then reset max_size and go back to connect */
		अगर (mbx->state == FM10K_STATE_OPEN) अणु
			mbx->state = FM10K_STATE_CONNECT;
			अवरोध;
		पूर्ण

		/* send a connect message to get data flowing again */
		fm10k_mbx_create_connect_hdr(mbx);
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस fm10k_mbx_create_reply(hw, mbx, mbx->tail);
पूर्ण

/**
 *  fm10k_mbx_process - Process mailbox पूर्णांकerrupt
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will process incoming mailbox events and generate mailbox
 *  replies.  It will वापस a value indicating the number of DWORDs
 *  transmitted excluding header on success or a negative value on error.
 **/
अटल s32 fm10k_mbx_process(काष्ठा fm10k_hw *hw,
			     काष्ठा fm10k_mbx_info *mbx)
अणु
	s32 err;

	/* we करो not पढ़ो mailbox अगर बंदd */
	अगर (mbx->state == FM10K_STATE_CLOSED)
		वापस 0;

	/* copy data from mailbox */
	err = fm10k_mbx_पढ़ो(hw, mbx);
	अगर (err)
		वापस err;

	/* validate type, source, and destination */
	err = fm10k_mbx_validate_msg_hdr(mbx);
	अगर (err < 0)
		जाओ msg_err;

	चयन (FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, TYPE)) अणु
	हाल FM10K_MSG_CONNECT:
		err = fm10k_mbx_process_connect(hw, mbx);
		अवरोध;
	हाल FM10K_MSG_DATA:
		err = fm10k_mbx_process_data(hw, mbx);
		अवरोध;
	हाल FM10K_MSG_DISCONNECT:
		err = fm10k_mbx_process_disconnect(hw, mbx);
		अवरोध;
	हाल FM10K_MSG_ERROR:
		err = fm10k_mbx_process_error(hw, mbx);
		अवरोध;
	शेष:
		err = FM10K_MBX_ERR_TYPE;
		अवरोध;
	पूर्ण

msg_err:
	/* notअगरy partner of errors on our end */
	अगर (err < 0)
		fm10k_mbx_create_error_msg(mbx, err);

	/* copy data from mailbox */
	fm10k_mbx_ग_लिखो(hw, mbx);

	वापस err;
पूर्ण

/**
 *  fm10k_mbx_disconnect - Shutकरोwn mailbox connection
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will shut करोwn the mailbox.  It places the mailbox first
 *  in the disconnect state, it then allows up to a predefined समयout क्रम
 *  the mailbox to transition to बंद on its own.  If this करोes not occur
 *  then the mailbox will be क्रमced पूर्णांकo the बंदd state.
 *
 *  Any mailbox transactions not completed beक्रमe calling this function
 *  are not guaranteed to complete and may be dropped.
 **/
अटल व्योम fm10k_mbx_disconnect(काष्ठा fm10k_hw *hw,
				 काष्ठा fm10k_mbx_info *mbx)
अणु
	पूर्णांक समयout = mbx->समयout ? FM10K_MBX_DISCONNECT_TIMEOUT : 0;

	/* Place mbx in पढ़ोy to disconnect state */
	mbx->state = FM10K_STATE_DISCONNECT;

	/* trigger पूर्णांकerrupt to start shutकरोwn process */
	fm10k_ग_लिखो_reg(hw, mbx->mbx_reg, FM10K_MBX_REQ |
					  FM10K_MBX_INTERRUPT_DISABLE);
	करो अणु
		udelay(FM10K_MBX_POLL_DELAY);
		mbx->ops.process(hw, mbx);
		समयout -= FM10K_MBX_POLL_DELAY;
	पूर्ण जबतक ((समयout > 0) && (mbx->state != FM10K_STATE_CLOSED));

	/* in हाल we didn't बंद, just क्रमce the mailbox पूर्णांकo shutकरोwn and
	 * drop all left over messages in the FIFO.
	 */
	fm10k_mbx_connect_reset(mbx);
	fm10k_fअगरo_drop_all(&mbx->tx);

	fm10k_ग_लिखो_reg(hw, mbx->mbmem_reg, 0);
पूर्ण

/**
 *  fm10k_mbx_connect - Start mailbox connection
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will initiate a mailbox connection.  It will populate the
 *  mailbox with a broadcast connect message and then initialize the lock.
 *  This is safe since the connect message is a single DWORD so the mailbox
 *  transaction is guaranteed to be atomic.
 *
 *  This function will वापस an error अगर the mailbox has not been initiated
 *  or is currently in use.
 **/
अटल s32 fm10k_mbx_connect(काष्ठा fm10k_hw *hw, काष्ठा fm10k_mbx_info *mbx)
अणु
	/* we cannot connect an uninitialized mailbox */
	अगर (!mbx->rx.buffer)
		वापस FM10K_MBX_ERR_NO_SPACE;

	/* we cannot connect an alपढ़ोy connected mailbox */
	अगर (mbx->state != FM10K_STATE_CLOSED)
		वापस FM10K_MBX_ERR_BUSY;

	/* mailbox समयout can now become active */
	mbx->समयout = FM10K_MBX_INIT_TIMEOUT;

	/* Place mbx in पढ़ोy to connect state */
	mbx->state = FM10K_STATE_CONNECT;

	fm10k_mbx_reset_work(mbx);

	/* initialize header of remote mailbox */
	fm10k_mbx_create_fake_disconnect_hdr(mbx);
	fm10k_ग_लिखो_reg(hw, mbx->mbmem_reg ^ mbx->mbmem_len, mbx->mbx_hdr);

	/* enable पूर्णांकerrupt and notअगरy other party of new message */
	mbx->mbx_lock = FM10K_MBX_REQ_INTERRUPT | FM10K_MBX_ACK_INTERRUPT |
			FM10K_MBX_INTERRUPT_ENABLE;

	/* generate and load connect header पूर्णांकo mailbox */
	fm10k_mbx_create_connect_hdr(mbx);
	fm10k_mbx_ग_लिखो(hw, mbx);

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_validate_handlers - Validate layout of message parsing data
 *  @msg_data: handlers क्रम mailbox events
 *
 *  This function validates the layout of the message parsing data.  This
 *  should be mostly अटल, but it is important to catch any errors that
 *  are made when स्थिरructing the parsers.
 **/
अटल s32 fm10k_mbx_validate_handlers(स्थिर काष्ठा fm10k_msg_data *msg_data)
अणु
	स्थिर काष्ठा fm10k_tlv_attr *attr;
	अचिन्हित पूर्णांक id;

	/* Allow शून्य mailboxes that transmit but करोn't receive */
	अगर (!msg_data)
		वापस 0;

	जबतक (msg_data->id != FM10K_TLV_ERROR) अणु
		/* all messages should have a function handler */
		अगर (!msg_data->func)
			वापस FM10K_ERR_PARAM;

		/* parser is optional */
		attr = msg_data->attr;
		अगर (attr) अणु
			जबतक (attr->id != FM10K_TLV_ERROR) अणु
				id = attr->id;
				attr++;
				/* ID should always be increasing */
				अगर (id >= attr->id)
					वापस FM10K_ERR_PARAM;
				/* ID should fit in results array */
				अगर (id >= FM10K_TLV_RESULTS_MAX)
					वापस FM10K_ERR_PARAM;
			पूर्ण

			/* verअगरy terminator is in the list */
			अगर (attr->id != FM10K_TLV_ERROR)
				वापस FM10K_ERR_PARAM;
		पूर्ण

		id = msg_data->id;
		msg_data++;
		/* ID should always be increasing */
		अगर (id >= msg_data->id)
			वापस FM10K_ERR_PARAM;
	पूर्ण

	/* verअगरy terminator is in the list */
	अगर ((msg_data->id != FM10K_TLV_ERROR) || !msg_data->func)
		वापस FM10K_ERR_PARAM;

	वापस 0;
पूर्ण

/**
 *  fm10k_mbx_रेजिस्टर_handlers - Register a set of handler ops क्रम mailbox
 *  @mbx: poपूर्णांकer to mailbox
 *  @msg_data: handlers क्रम mailbox events
 *
 *  This function associates a set of message handling ops with a mailbox.
 **/
अटल s32 fm10k_mbx_रेजिस्टर_handlers(काष्ठा fm10k_mbx_info *mbx,
				       स्थिर काष्ठा fm10k_msg_data *msg_data)
अणु
	/* validate layout of handlers beक्रमe assigning them */
	अगर (fm10k_mbx_validate_handlers(msg_data))
		वापस FM10K_ERR_PARAM;

	/* initialize the message handlers */
	mbx->msg_data = msg_data;

	वापस 0;
पूर्ण

/**
 *  fm10k_pfvf_mbx_init - Initialize mailbox memory क्रम PF/VF mailbox
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @msg_data: handlers क्रम mailbox events
 *  @id: ID reference क्रम PF as it supports up to 64 PF/VF mailboxes
 *
 *  This function initializes the mailbox क्रम use.  It will split the
 *  buffer provided and use that to populate both the Tx and Rx FIFO by
 *  evenly splitting it.  In order to allow क्रम easy masking of head/tail
 *  the value reported in size must be a घातer of 2 and is reported in
 *  DWORDs, not bytes.  Any invalid values will cause the mailbox to वापस
 *  error.
 **/
s32 fm10k_pfvf_mbx_init(काष्ठा fm10k_hw *hw, काष्ठा fm10k_mbx_info *mbx,
			स्थिर काष्ठा fm10k_msg_data *msg_data, u8 id)
अणु
	/* initialize रेजिस्टरs */
	चयन (hw->mac.type) अणु
	हाल fm10k_mac_vf:
		mbx->mbx_reg = FM10K_VFMBX;
		mbx->mbmem_reg = FM10K_VFMBMEM(FM10K_VFMBMEM_VF_XOR);
		अवरोध;
	हाल fm10k_mac_pf:
		/* there are only 64 VF <-> PF mailboxes */
		अगर (id < 64) अणु
			mbx->mbx_reg = FM10K_MBX(id);
			mbx->mbmem_reg = FM10K_MBMEM_VF(id, 0);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		वापस FM10K_MBX_ERR_NO_MBX;
	पूर्ण

	/* start out in बंदd state */
	mbx->state = FM10K_STATE_CLOSED;

	/* validate layout of handlers beक्रमe assigning them */
	अगर (fm10k_mbx_validate_handlers(msg_data))
		वापस FM10K_ERR_PARAM;

	/* initialize the message handlers */
	mbx->msg_data = msg_data;

	/* start mailbox as समयd out and let the reset_hw call
	 * set the समयout value to begin communications
	 */
	mbx->समयout = 0;
	mbx->udelay = FM10K_MBX_INIT_DELAY;

	/* initialize tail and head */
	mbx->tail = 1;
	mbx->head = 1;

	/* initialize CRC seeds */
	mbx->local = FM10K_MBX_CRC_SEED;
	mbx->remote = FM10K_MBX_CRC_SEED;

	/* Split buffer क्रम use by Tx/Rx FIFOs */
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;
	mbx->mbmem_len = FM10K_VFMBMEM_VF_XOR;

	/* initialize the FIFOs, sizes are in 4 byte increments */
	fm10k_fअगरo_init(&mbx->tx, mbx->buffer, FM10K_MBX_TX_BUFFER_SIZE);
	fm10k_fअगरo_init(&mbx->rx, &mbx->buffer[FM10K_MBX_TX_BUFFER_SIZE],
			FM10K_MBX_RX_BUFFER_SIZE);

	/* initialize function poपूर्णांकers */
	mbx->ops.connect = fm10k_mbx_connect;
	mbx->ops.disconnect = fm10k_mbx_disconnect;
	mbx->ops.rx_पढ़ोy = fm10k_mbx_rx_पढ़ोy;
	mbx->ops.tx_पढ़ोy = fm10k_mbx_tx_पढ़ोy;
	mbx->ops.tx_complete = fm10k_mbx_tx_complete;
	mbx->ops.enqueue_tx = fm10k_mbx_enqueue_tx;
	mbx->ops.process = fm10k_mbx_process;
	mbx->ops.रेजिस्टर_handlers = fm10k_mbx_रेजिस्टर_handlers;

	वापस 0;
पूर्ण

/**
 *  fm10k_sm_mbx_create_data_hdr - Generate a mailbox header क्रम local FIFO
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function वापसs a data mailbox header
 **/
अटल व्योम fm10k_sm_mbx_create_data_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	अगर (mbx->tail_len)
		mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(mbx->tail, SM_TAIL) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->remote, SM_VER) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, SM_HEAD);
पूर्ण

/**
 *  fm10k_sm_mbx_create_connect_hdr - Generate a mailbox header क्रम local FIFO
 *  @mbx: poपूर्णांकer to mailbox
 *  @err: error flags to report अगर any
 *
 *  This function वापसs a connection mailbox header
 **/
अटल व्योम fm10k_sm_mbx_create_connect_hdr(काष्ठा fm10k_mbx_info *mbx, u8 err)
अणु
	अगर (mbx->local)
		mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(mbx->tail, SM_TAIL) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->remote, SM_VER) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, SM_HEAD) |
		       FM10K_MSG_HDR_FIELD_SET(err, SM_ERR);
पूर्ण

/**
 *  fm10k_sm_mbx_connect_reset - Reset following request क्रम reset
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function resets the mailbox to a just connected state
 **/
अटल व्योम fm10k_sm_mbx_connect_reset(काष्ठा fm10k_mbx_info *mbx)
अणु
	/* flush any uncompleted work */
	fm10k_mbx_reset_work(mbx);

	/* set local version to max and remote version to 0 */
	mbx->local = FM10K_SM_MBX_VERSION;
	mbx->remote = 0;

	/* initialize tail and head */
	mbx->tail = 1;
	mbx->head = 1;

	/* reset state back to connect */
	mbx->state = FM10K_STATE_CONNECT;
पूर्ण

/**
 *  fm10k_sm_mbx_connect - Start चयन manager mailbox connection
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will initiate a mailbox connection with the चयन
 *  manager.  To करो this it will first disconnect the mailbox, and then
 *  reconnect it in order to complete a reset of the mailbox.
 *
 *  This function will वापस an error अगर the mailbox has not been initiated
 *  or is currently in use.
 **/
अटल s32 fm10k_sm_mbx_connect(काष्ठा fm10k_hw *hw, काष्ठा fm10k_mbx_info *mbx)
अणु
	/* we cannot connect an uninitialized mailbox */
	अगर (!mbx->rx.buffer)
		वापस FM10K_MBX_ERR_NO_SPACE;

	/* we cannot connect an alपढ़ोy connected mailbox */
	अगर (mbx->state != FM10K_STATE_CLOSED)
		वापस FM10K_MBX_ERR_BUSY;

	/* mailbox समयout can now become active */
	mbx->समयout = FM10K_MBX_INIT_TIMEOUT;

	/* Place mbx in पढ़ोy to connect state */
	mbx->state = FM10K_STATE_CONNECT;
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;

	/* reset पूर्णांकerface back to connect */
	fm10k_sm_mbx_connect_reset(mbx);

	/* enable पूर्णांकerrupt and notअगरy other party of new message */
	mbx->mbx_lock = FM10K_MBX_REQ_INTERRUPT | FM10K_MBX_ACK_INTERRUPT |
			FM10K_MBX_INTERRUPT_ENABLE;

	/* generate and load connect header पूर्णांकo mailbox */
	fm10k_sm_mbx_create_connect_hdr(mbx, 0);
	fm10k_mbx_ग_लिखो(hw, mbx);

	वापस 0;
पूर्ण

/**
 *  fm10k_sm_mbx_disconnect - Shutकरोwn mailbox connection
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will shut करोwn the mailbox.  It places the mailbox first
 *  in the disconnect state, it then allows up to a predefined समयout क्रम
 *  the mailbox to transition to बंद on its own.  If this करोes not occur
 *  then the mailbox will be क्रमced पूर्णांकo the बंदd state.
 *
 *  Any mailbox transactions not completed beक्रमe calling this function
 *  are not guaranteed to complete and may be dropped.
 **/
अटल व्योम fm10k_sm_mbx_disconnect(काष्ठा fm10k_hw *hw,
				    काष्ठा fm10k_mbx_info *mbx)
अणु
	पूर्णांक समयout = mbx->समयout ? FM10K_MBX_DISCONNECT_TIMEOUT : 0;

	/* Place mbx in पढ़ोy to disconnect state */
	mbx->state = FM10K_STATE_DISCONNECT;

	/* trigger पूर्णांकerrupt to start shutकरोwn process */
	fm10k_ग_लिखो_reg(hw, mbx->mbx_reg, FM10K_MBX_REQ |
					  FM10K_MBX_INTERRUPT_DISABLE);
	करो अणु
		udelay(FM10K_MBX_POLL_DELAY);
		mbx->ops.process(hw, mbx);
		समयout -= FM10K_MBX_POLL_DELAY;
	पूर्ण जबतक ((समयout > 0) && (mbx->state != FM10K_STATE_CLOSED));

	/* in हाल we didn't बंद just क्रमce the mailbox पूर्णांकo shutकरोwn */
	mbx->state = FM10K_STATE_CLOSED;
	mbx->remote = 0;
	fm10k_mbx_reset_work(mbx);
	fm10k_fअगरo_drop_all(&mbx->tx);

	fm10k_ग_लिखो_reg(hw, mbx->mbmem_reg, 0);
पूर्ण

/**
 *  fm10k_sm_mbx_validate_fअगरo_hdr - Validate fields in the remote FIFO header
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will parse up the fields in the mailbox header and वापस
 *  an error अगर the header contains any of a number of invalid configurations
 *  including unrecognized offsets or version numbers.
 **/
अटल s32 fm10k_sm_mbx_validate_fअगरo_hdr(काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर u32 *hdr = &mbx->mbx_hdr;
	u16 tail, head, ver;

	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_TAIL);
	ver = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_VER);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_HEAD);

	चयन (ver) अणु
	हाल 0:
		अवरोध;
	हाल FM10K_SM_MBX_VERSION:
		अगर (!head || head > FM10K_SM_MBX_FIFO_LEN)
			वापस FM10K_MBX_ERR_HEAD;
		अगर (!tail || tail > FM10K_SM_MBX_FIFO_LEN)
			वापस FM10K_MBX_ERR_TAIL;
		अगर (mbx->tail < head)
			head += mbx->mbmem_len - 1;
		अगर (tail < mbx->head)
			tail += mbx->mbmem_len - 1;
		अगर (fm10k_mbx_index_len(mbx, head, mbx->tail) > mbx->tail_len)
			वापस FM10K_MBX_ERR_HEAD;
		अगर (fm10k_mbx_index_len(mbx, mbx->head, tail) < mbx->mbmem_len)
			अवरोध;
		वापस FM10K_MBX_ERR_TAIL;
	शेष:
		वापस FM10K_MBX_ERR_SRC;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_sm_mbx_process_error - Process header with error flag set
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function is meant to respond to a request where the error flag
 *  is set.  As a result we will terminate a connection अगर one is present
 *  and fall back पूर्णांकo the reset state with a connection header of version
 *  0 (RESET).
 **/
अटल व्योम fm10k_sm_mbx_process_error(काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर क्रमागत fm10k_mbx_state state = mbx->state;

	चयन (state) अणु
	हाल FM10K_STATE_DISCONNECT:
		/* अगर there is an error just disconnect */
		mbx->remote = 0;
		अवरोध;
	हाल FM10K_STATE_OPEN:
		/* flush any uncompleted work */
		fm10k_sm_mbx_connect_reset(mbx);
		अवरोध;
	हाल FM10K_STATE_CONNECT:
		/* try connnecting at lower version */
		अगर (mbx->remote) अणु
			जबतक (mbx->local > 1)
				mbx->local--;
			mbx->remote = 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	fm10k_sm_mbx_create_connect_hdr(mbx, 0);
पूर्ण

/**
 *  fm10k_sm_mbx_create_error_msg - Process an error in FIFO header
 *  @mbx: poपूर्णांकer to mailbox
 *  @err: local error encountered
 *
 *  This function will पूर्णांकerpret the error provided by err, and based on
 *  that it may set the error bit in the local message header
 **/
अटल व्योम fm10k_sm_mbx_create_error_msg(काष्ठा fm10k_mbx_info *mbx, s32 err)
अणु
	/* only generate an error message क्रम these types */
	चयन (err) अणु
	हाल FM10K_MBX_ERR_TAIL:
	हाल FM10K_MBX_ERR_HEAD:
	हाल FM10K_MBX_ERR_SRC:
	हाल FM10K_MBX_ERR_SIZE:
	हाल FM10K_MBX_ERR_RSVD0:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* process it as though we received an error, and send error reply */
	fm10k_sm_mbx_process_error(mbx);
	fm10k_sm_mbx_create_connect_hdr(mbx, 1);
पूर्ण

/**
 *  fm10k_sm_mbx_receive - Take message from Rx mailbox FIFO and put it in Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @tail: tail index of message
 *
 *  This function will dequeue one message from the Rx चयन manager mailbox
 *  FIFO and place it in the Rx mailbox FIFO क्रम processing by software.
 **/
अटल s32 fm10k_sm_mbx_receive(काष्ठा fm10k_hw *hw,
				काष्ठा fm10k_mbx_info *mbx,
				u16 tail)
अणु
	/* reduce length by 1 to convert to a mask */
	u16 mbmem_len = mbx->mbmem_len - 1;
	s32 err;

	/* push tail in front of head */
	अगर (tail < mbx->head)
		tail += mbmem_len;

	/* copy data to the Rx FIFO */
	err = fm10k_mbx_push_tail(hw, mbx, tail);
	अगर (err < 0)
		वापस err;

	/* process messages अगर we have received any */
	fm10k_mbx_dequeue_rx(hw, mbx);

	/* guarantee head aligns with the end of the last message */
	mbx->head = fm10k_mbx_head_sub(mbx, mbx->pushed);
	mbx->pushed = 0;

	/* clear any extra bits left over since index adds 1 extra bit */
	अगर (mbx->head > mbmem_len)
		mbx->head -= mbmem_len;

	वापस err;
पूर्ण

/**
 *  fm10k_sm_mbx_transmit - Take message from Tx and put it in Tx mailbox FIFO
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @head: head index of message
 *
 *  This function will dequeue one message from the Tx mailbox FIFO and place
 *  it in the Tx चयन manager mailbox FIFO क्रम processing by hardware.
 **/
अटल व्योम fm10k_sm_mbx_transmit(काष्ठा fm10k_hw *hw,
				  काष्ठा fm10k_mbx_info *mbx, u16 head)
अणु
	काष्ठा fm10k_mbx_fअगरo *fअगरo = &mbx->tx;
	/* reduce length by 1 to convert to a mask */
	u16 mbmem_len = mbx->mbmem_len - 1;
	u16 tail_len, len = 0;

	/* push head behind tail */
	अगर (mbx->tail < head)
		head += mbmem_len;

	fm10k_mbx_pull_head(hw, mbx, head);

	/* determine msg aligned offset क्रम end of buffer */
	करो अणु
		u32 *msg;

		msg = fअगरo->buffer + fm10k_fअगरo_head_offset(fअगरo, len);
		tail_len = len;
		len += FM10K_TLV_DWORD_LEN(*msg);
	पूर्ण जबतक ((len <= mbx->tail_len) && (len < mbmem_len));

	/* guarantee we stop on a message boundary */
	अगर (mbx->tail_len > tail_len) अणु
		mbx->tail = fm10k_mbx_tail_sub(mbx, mbx->tail_len - tail_len);
		mbx->tail_len = tail_len;
	पूर्ण

	/* clear any extra bits left over since index adds 1 extra bit */
	अगर (mbx->tail > mbmem_len)
		mbx->tail -= mbmem_len;
पूर्ण

/**
 *  fm10k_sm_mbx_create_reply - Generate reply based on state and remote head
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @head: acknowledgement number
 *
 *  This function will generate an outgoing message based on the current
 *  mailbox state and the remote FIFO head.  It will वापस the length
 *  of the outgoing message excluding header on success, and a negative value
 *  on error.
 **/
अटल व्योम fm10k_sm_mbx_create_reply(काष्ठा fm10k_hw *hw,
				      काष्ठा fm10k_mbx_info *mbx, u16 head)
अणु
	चयन (mbx->state) अणु
	हाल FM10K_STATE_OPEN:
	हाल FM10K_STATE_DISCONNECT:
		/* flush out Tx data */
		fm10k_sm_mbx_transmit(hw, mbx, head);

		/* generate new header based on data */
		अगर (mbx->tail_len || (mbx->state == FM10K_STATE_OPEN)) अणु
			fm10k_sm_mbx_create_data_hdr(mbx);
		पूर्ण अन्यथा अणु
			mbx->remote = 0;
			fm10k_sm_mbx_create_connect_hdr(mbx, 0);
		पूर्ण
		अवरोध;
	हाल FM10K_STATE_CONNECT:
	हाल FM10K_STATE_CLOSED:
		fm10k_sm_mbx_create_connect_hdr(mbx, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 *  fm10k_sm_mbx_process_reset - Process header with version == 0 (RESET)
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function is meant to respond to a request where the version data
 *  is set to 0.  As such we will either terminate the connection or go
 *  पूर्णांकo the connect state in order to re-establish the connection.  This
 *  function can also be used to respond to an error as the connection
 *  resetting would also be a means of dealing with errors.
 **/
अटल s32 fm10k_sm_mbx_process_reset(काष्ठा fm10k_hw *hw,
				      काष्ठा fm10k_mbx_info *mbx)
अणु
	s32 err = 0;
	स्थिर क्रमागत fm10k_mbx_state state = mbx->state;

	चयन (state) अणु
	हाल FM10K_STATE_DISCONNECT:
		/* drop remote connections and disconnect */
		mbx->state = FM10K_STATE_CLOSED;
		mbx->remote = 0;
		mbx->local = 0;
		अवरोध;
	हाल FM10K_STATE_OPEN:
		/* flush any incomplete work */
		fm10k_sm_mbx_connect_reset(mbx);
		err = FM10K_ERR_RESET_REQUESTED;
		अवरोध;
	हाल FM10K_STATE_CONNECT:
		/* Update remote value to match local value */
		mbx->remote = mbx->local;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	fm10k_sm_mbx_create_reply(hw, mbx, mbx->tail);

	वापस err;
पूर्ण

/**
 *  fm10k_sm_mbx_process_version_1 - Process header with version == 1
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function is meant to process messages received when the remote
 *  mailbox is active.
 **/
अटल s32 fm10k_sm_mbx_process_version_1(काष्ठा fm10k_hw *hw,
					  काष्ठा fm10k_mbx_info *mbx)
अणु
	स्थिर u32 *hdr = &mbx->mbx_hdr;
	u16 head, tail;
	s32 len;

	/* pull all fields needed क्रम verअगरication */
	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_TAIL);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, SM_HEAD);

	/* अगर we are in connect and wanting version 1 then start up and go */
	अगर (mbx->state == FM10K_STATE_CONNECT) अणु
		अगर (!mbx->remote)
			जाओ send_reply;
		अगर (mbx->remote != 1)
			वापस FM10K_MBX_ERR_SRC;

		mbx->state = FM10K_STATE_OPEN;
	पूर्ण

	करो अणु
		/* पात on message size errors */
		len = fm10k_sm_mbx_receive(hw, mbx, tail);
		अगर (len < 0)
			वापस len;

		/* जारी until we have flushed the Rx FIFO */
	पूर्ण जबतक (len);

send_reply:
	fm10k_sm_mbx_create_reply(hw, mbx, head);

	वापस 0;
पूर्ण

/**
 *  fm10k_sm_mbx_process - Process चयन manager mailbox पूर्णांकerrupt
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *
 *  This function will process incoming mailbox events and generate mailbox
 *  replies.  It will वापस a value indicating the number of DWORDs
 *  transmitted excluding header on success or a negative value on error.
 **/
अटल s32 fm10k_sm_mbx_process(काष्ठा fm10k_hw *hw,
				काष्ठा fm10k_mbx_info *mbx)
अणु
	s32 err;

	/* we करो not पढ़ो mailbox अगर बंदd */
	अगर (mbx->state == FM10K_STATE_CLOSED)
		वापस 0;

	/* retrieve data from चयन manager */
	err = fm10k_mbx_पढ़ो(hw, mbx);
	अगर (err)
		वापस err;

	err = fm10k_sm_mbx_validate_fअगरo_hdr(mbx);
	अगर (err < 0)
		जाओ fअगरo_err;

	अगर (FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, SM_ERR)) अणु
		fm10k_sm_mbx_process_error(mbx);
		जाओ fअगरo_err;
	पूर्ण

	चयन (FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, SM_VER)) अणु
	हाल 0:
		err = fm10k_sm_mbx_process_reset(hw, mbx);
		अवरोध;
	हाल FM10K_SM_MBX_VERSION:
		err = fm10k_sm_mbx_process_version_1(hw, mbx);
		अवरोध;
	पूर्ण

fअगरo_err:
	अगर (err < 0)
		fm10k_sm_mbx_create_error_msg(mbx, err);

	/* report data to चयन manager */
	fm10k_mbx_ग_लिखो(hw, mbx);

	वापस err;
पूर्ण

/**
 *  fm10k_sm_mbx_init - Initialize mailbox memory क्रम PF/SM mailbox
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mbx: poपूर्णांकer to mailbox
 *  @msg_data: handlers क्रम mailbox events
 *
 *  This function initializes the PF/SM mailbox क्रम use.  It will split the
 *  buffer provided and use that to populate both the Tx and Rx FIFO by
 *  evenly splitting it.  In order to allow क्रम easy masking of head/tail
 *  the value reported in size must be a घातer of 2 and is reported in
 *  DWORDs, not bytes.  Any invalid values will cause the mailbox to वापस
 *  error.
 **/
s32 fm10k_sm_mbx_init(काष्ठा fm10k_hw __always_unused *hw,
		      काष्ठा fm10k_mbx_info *mbx,
		      स्थिर काष्ठा fm10k_msg_data *msg_data)
अणु
	mbx->mbx_reg = FM10K_GMBX;
	mbx->mbmem_reg = FM10K_MBMEM_PF(0);

	/* start out in बंदd state */
	mbx->state = FM10K_STATE_CLOSED;

	/* validate layout of handlers beक्रमe assigning them */
	अगर (fm10k_mbx_validate_handlers(msg_data))
		वापस FM10K_ERR_PARAM;

	/* initialize the message handlers */
	mbx->msg_data = msg_data;

	/* start mailbox as समयd out and let the reset_hw call
	 * set the समयout value to begin communications
	 */
	mbx->समयout = 0;
	mbx->udelay = FM10K_MBX_INIT_DELAY;

	/* Split buffer क्रम use by Tx/Rx FIFOs */
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;
	mbx->mbmem_len = FM10K_MBMEM_PF_XOR;

	/* initialize the FIFOs, sizes are in 4 byte increments */
	fm10k_fअगरo_init(&mbx->tx, mbx->buffer, FM10K_MBX_TX_BUFFER_SIZE);
	fm10k_fअगरo_init(&mbx->rx, &mbx->buffer[FM10K_MBX_TX_BUFFER_SIZE],
			FM10K_MBX_RX_BUFFER_SIZE);

	/* initialize function poपूर्णांकers */
	mbx->ops.connect = fm10k_sm_mbx_connect;
	mbx->ops.disconnect = fm10k_sm_mbx_disconnect;
	mbx->ops.rx_पढ़ोy = fm10k_mbx_rx_पढ़ोy;
	mbx->ops.tx_पढ़ोy = fm10k_mbx_tx_पढ़ोy;
	mbx->ops.tx_complete = fm10k_mbx_tx_complete;
	mbx->ops.enqueue_tx = fm10k_mbx_enqueue_tx;
	mbx->ops.process = fm10k_sm_mbx_process;
	mbx->ops.रेजिस्टर_handlers = fm10k_mbx_रेजिस्टर_handlers;

	वापस 0;
पूर्ण
