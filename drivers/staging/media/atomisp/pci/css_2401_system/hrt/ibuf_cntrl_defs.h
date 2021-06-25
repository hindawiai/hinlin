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

#अगर_अघोषित _ibuf_cntrl_defs_h_
#घोषणा _ibuf_cntrl_defs_h_

#समावेश <stream2mmio_defs.h>
#समावेश <dma_v2_defs.h>

#घोषणा _IBUF_CNTRL_REG_ALIGN 4
/* alignment of रेजिस्टर banks, first bank are shared configuration and status रेजिस्टरs: */
#घोषणा _IBUF_CNTRL_PROC_REG_ALIGN        32

/* the actual amount of configuration रेजिस्टरs per proc: */
#घोषणा _IBUF_CNTRL_CONFIG_REGS_PER_PROC 18
/* the actual amount of shared configuration रेजिस्टरs: */
#घोषणा _IBUF_CNTRL_CONFIG_REGS_NO_PROC  0

/* the actual amount of status रेजिस्टरs per proc */
#घोषणा _IBUF_CNTRL_STATUS_REGS_PER_PROC (_IBUF_CNTRL_CONFIG_REGS_PER_PROC + 10)
/* the actual amount shared status रेजिस्टरs */
#घोषणा _IBUF_CNTRL_STATUS_REGS_NO_PROC  (_IBUF_CNTRL_CONFIG_REGS_NO_PROC + 2)

/* समय out bits, maximum समय out value is 2^_IBUF_CNTRL_TIME_OUT_BITS - 1 */
#घोषणा _IBUF_CNTRL_TIME_OUT_BITS         5

/* command token definition */
#घोषणा _IBUF_CNTRL_CMD_TOKEN_LSB          0
#घोषणा _IBUF_CNTRL_CMD_TOKEN_MSB          1

/* Str2MMIO defines */
#घोषणा _IBUF_CNTRL_STREAM2MMIO_CMD_TOKEN_MSB        _STREAM2MMIO_CMD_TOKEN_CMD_MSB
#घोषणा _IBUF_CNTRL_STREAM2MMIO_CMD_TOKEN_LSB        _STREAM2MMIO_CMD_TOKEN_CMD_LSB
#घोषणा _IBUF_CNTRL_STREAM2MMIO_NUM_ITEMS_BITS       _STREAM2MMIO_PACK_NUM_ITEMS_BITS
#घोषणा _IBUF_CNTRL_STREAM2MMIO_ACK_खातापूर्ण_BIT          _STREAM2MMIO_PACK_ACK_खातापूर्ण_BIT
#घोषणा _IBUF_CNTRL_STREAM2MMIO_ACK_TOKEN_VALID_BIT  _STREAM2MMIO_ACK_TOKEN_VALID_BIT

/* acknowledge token definition */
#घोषणा _IBUF_CNTRL_ACK_TOKEN_STORES_IDX    0
#घोषणा _IBUF_CNTRL_ACK_TOKEN_STORES_BITS   15
#घोषणा _IBUF_CNTRL_ACK_TOKEN_ITEMS_IDX     (_IBUF_CNTRL_ACK_TOKEN_STORES_BITS + _IBUF_CNTRL_ACK_TOKEN_STORES_IDX)
#घोषणा _IBUF_CNTRL_ACK_TOKEN_ITEMS_BITS    _STREAM2MMIO_PACK_NUM_ITEMS_BITS
#घोषणा _IBUF_CNTRL_ACK_TOKEN_LSB          _IBUF_CNTRL_ACK_TOKEN_STORES_IDX
#घोषणा _IBUF_CNTRL_ACK_TOKEN_MSB          (_IBUF_CNTRL_ACK_TOKEN_ITEMS_BITS + _IBUF_CNTRL_ACK_TOKEN_ITEMS_IDX - 1)
/* bit 31 indicates a valid ack: */
#घोषणा _IBUF_CNTRL_ACK_TOKEN_VALID_BIT    (_IBUF_CNTRL_ACK_TOKEN_ITEMS_BITS + _IBUF_CNTRL_ACK_TOKEN_ITEMS_IDX)

/*shared रेजिस्टरs:*/
#घोषणा _IBUF_CNTRL_RECALC_WORDS_STATUS     0
#घोषणा _IBUF_CNTRL_ARBITERS_STATUS         1

#घोषणा _IBUF_CNTRL_SET_CRUN                2 /* NO PHYSICAL REGISTER!! Only used in HSS model */

/*रेजिस्टर addresses क्रम each proc: */
#घोषणा _IBUF_CNTRL_CMD                   0
#घोषणा _IBUF_CNTRL_ACK                   1

/* number of items (packets or words) per frame: */
#घोषणा _IBUF_CNTRL_NUM_ITEMS_PER_STORE   2

/* number of stores (packets or words) per store/buffer: */
#घोषणा _IBUF_CNTRL_NUM_STORES_PER_FRAME  3

/* the channel and command in the DMA */
#घोषणा _IBUF_CNTRL_DMA_CHANNEL           4
#घोषणा _IBUF_CNTRL_DMA_CMD               5

/* the start address and stride of the buffers */
#घोषणा _IBUF_CNTRL_BUFFER_START_ADDRESS  6
#घोषणा _IBUF_CNTRL_BUFFER_STRIDE         7
#घोषणा _IBUF_CNTRL_BUFFER_END_ADDRESS    8

/* destination start address, stride and end address; should be the same as in the DMA */
#घोषणा _IBUF_CNTRL_DEST_START_ADDRESS    9
#घोषणा _IBUF_CNTRL_DEST_STRIDE           10
#घोषणा _IBUF_CNTRL_DEST_END_ADDRESS      11

/* send a frame sync or not, शेष 1 */
#घोषणा _IBUF_CNTRL_SYNC_FRAME            12

/* str2mmio cmds */
#घोषणा _IBUF_CNTRL_STR2MMIO_SYNC_CMD     13
#घोषणा _IBUF_CNTRL_STR2MMIO_STORE_CMD    14

/* num elems p word*/
#घोषणा _IBUF_CNTRL_SHIFT_ITEMS           15
#घोषणा _IBUF_CNTRL_ELEMS_P_WORD_IBUF     16
#घोषणा _IBUF_CNTRL_ELEMS_P_WORD_DEST     17

/* STATUS */
/* current frame and stores in buffer */
#घोषणा _IBUF_CNTRL_CUR_STORES            18
#घोषणा _IBUF_CNTRL_CUR_ACKS              19

/* current buffer and destination address क्रम DMA cmd's */
#घोषणा _IBUF_CNTRL_CUR_S2M_IBUF_ADDR     20
#घोषणा _IBUF_CNTRL_CUR_DMA_IBUF_ADDR     21
#घोषणा _IBUF_CNTRL_CUR_DMA_DEST_ADDR     22
#घोषणा _IBUF_CNTRL_CUR_ISP_DEST_ADDR     23

#घोषणा _IBUF_CNTRL_CUR_NR_DMA_CMDS_SEND  24

#घोषणा _IBUF_CNTRL_MAIN_CNTRL_STATE      25
#घोषणा _IBUF_CNTRL_DMA_SYNC_STATE        26
#घोषणा _IBUF_CNTRL_ISP_SYNC_STATE        27

/*Commands: */
#घोषणा _IBUF_CNTRL_CMD_STORE_FRAME_IDX     0
#घोषणा _IBUF_CNTRL_CMD_ONLINE_IDX          1

/* initialize, copy st_addr to cur_addr etc */
#घोषणा _IBUF_CNTRL_CMD_INITIALIZE          0

/* store an online frame (sync with ISP, use end cfg start, stride and end address: */
#घोषणा _IBUF_CNTRL_CMD_STORE_ONLINE_FRAME  ((1 << _IBUF_CNTRL_CMD_STORE_FRAME_IDX) | (1 << _IBUF_CNTRL_CMD_ONLINE_IDX))

/* store an offline frame (करोn't sync with ISP, requires start address as 2nd token, no end address: */
#घोषणा _IBUF_CNTRL_CMD_STORE_OFFLINE_FRAME  BIT(_IBUF_CNTRL_CMD_STORE_FRAME_IDX)

/* false command token, should be dअगरferent then commands. Use online bit, not store frame: */
#घोषणा _IBUF_CNTRL_FALSE_ACK               2

#पूर्ण_अगर
