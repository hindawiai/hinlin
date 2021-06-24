<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _STREAM2MMMIO_DEFS_H
#घोषणा _STREAM2MMMIO_DEFS_H

#समावेश <mipi_backend_defs.h>

#घोषणा _STREAM2MMIO_REG_ALIGN                  4

#घोषणा _STREAM2MMIO_COMMAND_REG_ID             0
#घोषणा _STREAM2MMIO_ACKNOWLEDGE_REG_ID         1
#घोषणा _STREAM2MMIO_PIX_WIDTH_ID_REG_ID        2
#घोषणा _STREAM2MMIO_START_ADDR_REG_ID          3      /* master port address,NOT Byte */
#घोषणा _STREAM2MMIO_END_ADDR_REG_ID            4      /* master port address,NOT Byte */
#घोषणा _STREAM2MMIO_STRIDE_REG_ID              5      /* stride in master port words, increment is per packet क्रम दीर्घ sids, stride is not used क्रम लघु sid's*/
#घोषणा _STREAM2MMIO_NUM_ITEMS_REG_ID           6      /* number of packets क्रम store packets cmd, number of words क्रम store_words cmd */
#घोषणा _STREAM2MMIO_BLOCK_WHEN_NO_CMD_REG_ID   7      /* अगर this रेजिस्टर is 1, input will be stalled अगर there is no pending command क्रम this sid */
#घोषणा _STREAM2MMIO_REGS_PER_SID               8

#घोषणा _STREAM2MMIO_SID_REG_OFFSET             8
#घोषणा _STREAM2MMIO_MAX_NOF_SIDS              64      /* value used in hss model */

/* command token definition     */
#घोषणा _STREAM2MMIO_CMD_TOKEN_CMD_LSB          0      /* bits 1-0 is क्रम the command field */
#घोषणा _STREAM2MMIO_CMD_TOKEN_CMD_MSB          1

#घोषणा _STREAM2MMIO_CMD_TOKEN_WIDTH           (_STREAM2MMIO_CMD_TOKEN_CMD_MSB + 1 - _STREAM2MMIO_CMD_TOKEN_CMD_LSB)

#घोषणा _STREAM2MMIO_CMD_TOKEN_STORE_WORDS              0      /* command क्रम storing a number of output words indicated by reg _STREAM2MMIO_NUM_ITEMS */
#घोषणा _STREAM2MMIO_CMD_TOKEN_STORE_PACKETS            1      /* command क्रम storing a number of packets indicated by reg _STREAM2MMIO_NUM_ITEMS      */
#घोषणा _STREAM2MMIO_CMD_TOKEN_SYNC_FRAME               2      /* command क्रम रुकोing क्रम a frame start                                                */

/* acknowledges from packer module */
/* fields: eof   - indicates whether last (लघु) packet received was an eof packet */
/*         eop   - indicates whether command has ended due to packet end or due to no of words requested has been received */
/*         count - indicates number of words stored */
#घोषणा _STREAM2MMIO_PACK_NUM_ITEMS_BITS        16
#घोषणा _STREAM2MMIO_PACK_ACK_EOP_BIT           _STREAM2MMIO_PACK_NUM_ITEMS_BITS
#घोषणा _STREAM2MMIO_PACK_ACK_खातापूर्ण_BIT           (_STREAM2MMIO_PACK_ACK_EOP_BIT + 1)

/* acknowledge token definition */
#घोषणा _STREAM2MMIO_ACK_TOKEN_NUM_ITEMS_LSB    0      /* bits 3-0 is क्रम the command field */
#घोषणा _STREAM2MMIO_ACK_TOKEN_NUM_ITEMS_MSB   (_STREAM2MMIO_PACK_NUM_ITEMS_BITS - 1)
#घोषणा _STREAM2MMIO_ACK_TOKEN_EOP_BIT         _STREAM2MMIO_PACK_ACK_EOP_BIT
#घोषणा _STREAM2MMIO_ACK_TOKEN_खातापूर्ण_BIT         _STREAM2MMIO_PACK_ACK_खातापूर्ण_BIT
#घोषणा _STREAM2MMIO_ACK_TOKEN_VALID_BIT       (_STREAM2MMIO_ACK_TOKEN_खातापूर्ण_BIT + 1)      /* this bit indicates a valid ack    */
/* अगर there is no valid ack, a पढ़ो  */
/* on the ack रेजिस्टर वापसs 0     */
#घोषणा _STREAM2MMIO_ACK_TOKEN_WIDTH           (_STREAM2MMIO_ACK_TOKEN_VALID_BIT + 1)

/* commands क्रम packer module */
#घोषणा _STREAM2MMIO_PACK_CMD_STORE_WORDS        0
#घोषणा _STREAM2MMIO_PACK_CMD_STORE_LONG_PACKET  1
#घोषणा _STREAM2MMIO_PACK_CMD_STORE_SHORT_PACKET 2

#पूर्ण_अगर /* _STREAM2MMIO_DEFS_H */
