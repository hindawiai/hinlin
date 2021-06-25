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

/*   Atheros Ethernet framing. Every Ethernet frame is surrounded by an atheros
 *   frame जबतक transmitted over a serial channel.
 */

#अगर_अघोषित _QCA_FRAMING_H
#घोषणा _QCA_FRAMING_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/types.h>

/* Frame is currently being received */
#घोषणा QCAFRM_GATHER 0

/*  No header byte जबतक expecting it */
#घोषणा QCAFRM_NOHEAD (QCAFRM_ERR_BASE - 1)

/* No tailer byte जबतक expecting it */
#घोषणा QCAFRM_NOTAIL (QCAFRM_ERR_BASE - 2)

/* Frame length is invalid */
#घोषणा QCAFRM_INVLEN (QCAFRM_ERR_BASE - 3)

/* Frame length is invalid */
#घोषणा QCAFRM_INVFRAME (QCAFRM_ERR_BASE - 4)

/* Min/Max Ethernet MTU: 46/1500 */
#घोषणा QCAFRM_MIN_MTU (ETH_ZLEN - ETH_HLEN)
#घोषणा QCAFRM_MAX_MTU ETH_DATA_LEN

/* Min/Max frame lengths */
#घोषणा QCAFRM_MIN_LEN (QCAFRM_MIN_MTU + ETH_HLEN)
#घोषणा QCAFRM_MAX_LEN (QCAFRM_MAX_MTU + VLAN_ETH_HLEN)

/* QCA7K header len */
#घोषणा QCAFRM_HEADER_LEN 8

/* QCA7K footer len */
#घोषणा QCAFRM_FOOTER_LEN 2

/* QCA7K Framing. */
#घोषणा QCAFRM_ERR_BASE -1000

क्रमागत qcafrm_state अणु
	/* HW length is only available on SPI */
	QCAFRM_HW_LEN0 = 0x8000,
	QCAFRM_HW_LEN1 = QCAFRM_HW_LEN0 - 1,
	QCAFRM_HW_LEN2 = QCAFRM_HW_LEN1 - 1,
	QCAFRM_HW_LEN3 = QCAFRM_HW_LEN2 - 1,

	/*  Waiting first 0xAA of header */
	QCAFRM_WAIT_AA1 = QCAFRM_HW_LEN3 - 1,

	/*  Waiting second 0xAA of header */
	QCAFRM_WAIT_AA2 = QCAFRM_WAIT_AA1 - 1,

	/*  Waiting third 0xAA of header */
	QCAFRM_WAIT_AA3 = QCAFRM_WAIT_AA2 - 1,

	/*  Waiting fourth 0xAA of header */
	QCAFRM_WAIT_AA4 = QCAFRM_WAIT_AA3 - 1,

	/*  Waiting Byte 0-1 of length (litte endian) */
	QCAFRM_WAIT_LEN_BYTE0 = QCAFRM_WAIT_AA4 - 1,
	QCAFRM_WAIT_LEN_BYTE1 = QCAFRM_WAIT_AA4 - 2,

	/* Reserved bytes */
	QCAFRM_WAIT_RSVD_BYTE1 = QCAFRM_WAIT_AA4 - 3,
	QCAFRM_WAIT_RSVD_BYTE2 = QCAFRM_WAIT_AA4 - 4,

	/*  The frame length is used as the state until
	 *  the end of the Ethernet frame
	 *  Waiting क्रम first 0x55 of footer
	 */
	QCAFRM_WAIT_551 = 1,

	/*  Waiting क्रम second 0x55 of footer */
	QCAFRM_WAIT_552 = QCAFRM_WAIT_551 - 1
पूर्ण;

/*   Structure to मुख्यtain the frame decoding during reception. */

काष्ठा qcafrm_handle अणु
	/*  Current decoding state */
	क्रमागत qcafrm_state state;
	/* Initial state depends on connection type */
	क्रमागत qcafrm_state init;

	/* Offset in buffer (borrowed क्रम length too) */
	u16 offset;

	/* Frame length as kept by this module */
	u16 len;
पूर्ण;

u16 qcafrm_create_header(u8 *buf, u16 len);

u16 qcafrm_create_footer(u8 *buf);

अटल अंतरभूत व्योम qcafrm_fsm_init_spi(काष्ठा qcafrm_handle *handle)
अणु
	handle->init = QCAFRM_HW_LEN0;
	handle->state = handle->init;
पूर्ण

अटल अंतरभूत व्योम qcafrm_fsm_init_uart(काष्ठा qcafrm_handle *handle)
अणु
	handle->init = QCAFRM_WAIT_AA1;
	handle->state = handle->init;
पूर्ण

/*   Gather received bytes and try to extract a full Ethernet frame
 *   by following a simple state machine.
 *
 * Return:   QCAFRM_GATHER       No Ethernet frame fully received yet.
 *           QCAFRM_NOHEAD       Header expected but not found.
 *           QCAFRM_INVLEN       QCA7K frame length is invalid
 *           QCAFRM_NOTAIL       Footer expected but not found.
 *           > 0                 Number of byte in the fully received
 *                               Ethernet frame
 */

s32 qcafrm_fsm_decode(काष्ठा qcafrm_handle *handle, u8 *buf, u16 buf_len, u8 recv_byte);

#पूर्ण_अगर /* _QCA_FRAMING_H */
