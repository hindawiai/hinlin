<शैली गुरु>
/*
 *   Copyright (c) 2011, 2012, Atheros Communications Inc.
 *   Copyright (c) 2014, I2SE GmbH
 *
 *   Permission to use, copy, modअगरy, and/or distribute this software
 *   क्रम any purpose with or without fee is hereby granted, provided
 *   that the above copyright notice and this permission notice appear
 *   in all copies.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, सूचीECT, INसूचीECT, OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*   Atheros ethernet framing. Every Ethernet frame is surrounded
 *   by an atheros frame जबतक transmitted over a serial channel;
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "qca_7k_common.h"

u16
qcafrm_create_header(u8 *buf, u16 length)
अणु
	__le16 len;

	अगर (!buf)
		वापस 0;

	len = cpu_to_le16(length);

	buf[0] = 0xAA;
	buf[1] = 0xAA;
	buf[2] = 0xAA;
	buf[3] = 0xAA;
	buf[4] = len & 0xff;
	buf[5] = (len >> 8) & 0xff;
	buf[6] = 0;
	buf[7] = 0;

	वापस QCAFRM_HEADER_LEN;
पूर्ण
EXPORT_SYMBOL_GPL(qcafrm_create_header);

u16
qcafrm_create_footer(u8 *buf)
अणु
	अगर (!buf)
		वापस 0;

	buf[0] = 0x55;
	buf[1] = 0x55;
	वापस QCAFRM_FOOTER_LEN;
पूर्ण
EXPORT_SYMBOL_GPL(qcafrm_create_footer);

/*   Gather received bytes and try to extract a full ethernet frame by
 *   following a simple state machine.
 *
 * Return:   QCAFRM_GATHER       No ethernet frame fully received yet.
 *           QCAFRM_NOHEAD       Header expected but not found.
 *           QCAFRM_INVLEN       Atheros frame length is invalid
 *           QCAFRM_NOTAIL       Footer expected but not found.
 *           > 0                 Number of byte in the fully received
 *                               Ethernet frame
 */

s32
qcafrm_fsm_decode(काष्ठा qcafrm_handle *handle, u8 *buf, u16 buf_len, u8 recv_byte)
अणु
	s32 ret = QCAFRM_GATHER;
	u16 len;

	चयन (handle->state) अणु
	हाल QCAFRM_HW_LEN0:
	हाल QCAFRM_HW_LEN1:
		/* by शेष, just go to next state */
		handle->state--;

		अगर (recv_byte != 0x00) अणु
			/* first two bytes of length must be 0 */
			handle->state = handle->init;
		पूर्ण
		अवरोध;
	हाल QCAFRM_HW_LEN2:
	हाल QCAFRM_HW_LEN3:
		handle->state--;
		अवरोध;
	/* 4 bytes header pattern */
	हाल QCAFRM_WAIT_AA1:
	हाल QCAFRM_WAIT_AA2:
	हाल QCAFRM_WAIT_AA3:
	हाल QCAFRM_WAIT_AA4:
		अगर (recv_byte != 0xAA) अणु
			ret = QCAFRM_NOHEAD;
			handle->state = handle->init;
		पूर्ण अन्यथा अणु
			handle->state--;
		पूर्ण
		अवरोध;
		/* 2 bytes length. */
		/* Borrow offset field to hold length क्रम now. */
	हाल QCAFRM_WAIT_LEN_BYTE0:
		handle->offset = recv_byte;
		handle->state = QCAFRM_WAIT_LEN_BYTE1;
		अवरोध;
	हाल QCAFRM_WAIT_LEN_BYTE1:
		handle->offset = handle->offset | (recv_byte << 8);
		handle->state = QCAFRM_WAIT_RSVD_BYTE1;
		अवरोध;
	हाल QCAFRM_WAIT_RSVD_BYTE1:
		handle->state = QCAFRM_WAIT_RSVD_BYTE2;
		अवरोध;
	हाल QCAFRM_WAIT_RSVD_BYTE2:
		len = handle->offset;
		अगर (len > buf_len || len < QCAFRM_MIN_LEN) अणु
			ret = QCAFRM_INVLEN;
			handle->state = handle->init;
		पूर्ण अन्यथा अणु
			handle->state = (क्रमागत qcafrm_state)(len + 1);
			/* Reमुख्यing number of bytes. */
			handle->offset = 0;
		पूर्ण
		अवरोध;
	शेष:
		/* Receiving Ethernet frame itself. */
		buf[handle->offset] = recv_byte;
		handle->offset++;
		handle->state--;
		अवरोध;
	हाल QCAFRM_WAIT_551:
		अगर (recv_byte != 0x55) अणु
			ret = QCAFRM_NOTAIL;
			handle->state = handle->init;
		पूर्ण अन्यथा अणु
			handle->state = QCAFRM_WAIT_552;
		पूर्ण
		अवरोध;
	हाल QCAFRM_WAIT_552:
		अगर (recv_byte != 0x55) अणु
			ret = QCAFRM_NOTAIL;
			handle->state = handle->init;
		पूर्ण अन्यथा अणु
			ret = handle->offset;
			/* Frame is fully received. */
			handle->state = handle->init;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(qcafrm_fsm_decode);

MODULE_DESCRIPTION("Qualcomm Atheros QCA7000 common");
MODULE_AUTHOR("Qualcomm Atheros Communications");
MODULE_AUTHOR("Stefan Wahren <stefan.wahren@i2se.com>");
MODULE_LICENSE("Dual BSD/GPL");
