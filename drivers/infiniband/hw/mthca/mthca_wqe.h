<शैली गुरु>
/*
 * Copyright (c) 2005 Cisco Systems. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित MTHCA_WQE_H
#घोषणा MTHCA_WQE_H

#समावेश <linux/types.h>

क्रमागत अणु
	MTHCA_NEXT_DBD		= 1 << 7,
	MTHCA_NEXT_FENCE	= 1 << 6,
	MTHCA_NEXT_CQ_UPDATE	= 1 << 3,
	MTHCA_NEXT_EVENT_GEN	= 1 << 2,
	MTHCA_NEXT_SOLICIT	= 1 << 1,
	MTHCA_NEXT_IP_CSUM	= 1 << 4,
	MTHCA_NEXT_TCP_UDP_CSUM = 1 << 5,

	MTHCA_MLX_VL15		= 1 << 17,
	MTHCA_MLX_SLR		= 1 << 16
पूर्ण;

क्रमागत अणु
	MTHCA_INVAL_LKEY			= 0x100,
	MTHCA_TAVOR_MAX_WQES_PER_RECV_DB	= 256,
	MTHCA_ARBEL_MAX_WQES_PER_SEND_DB	= 255
पूर्ण;

काष्ठा mthca_next_seg अणु
	__be32 nda_op;		/* [31:6] next WQE [4:0] next opcode */
	__be32 ee_nds;		/* [31:8] next EE  [7] DBD [6] F [5:0] next WQE size */
	__be32 flags;		/* [3] CQ [2] Event [1] Solicit */
	__be32 imm;		/* immediate data */
पूर्ण;

काष्ठा mthca_tavor_ud_seg अणु
	u32    reserved1;
	__be32 lkey;
	__be64 av_addr;
	u32    reserved2[4];
	__be32 dqpn;
	__be32 qkey;
	u32    reserved3[2];
पूर्ण;

काष्ठा mthca_arbel_ud_seg अणु
	__be32 av[8];
	__be32 dqpn;
	__be32 qkey;
	u32    reserved[2];
पूर्ण;

काष्ठा mthca_bind_seg अणु
	__be32 flags;		/* [31] Atomic [30] rem ग_लिखो [29] rem पढ़ो */
	u32    reserved;
	__be32 new_rkey;
	__be32 lkey;
	__be64 addr;
	__be64 length;
पूर्ण;

काष्ठा mthca_raddr_seg अणु
	__be64 raddr;
	__be32 rkey;
	u32    reserved;
पूर्ण;

काष्ठा mthca_atomic_seg अणु
	__be64 swap_add;
	__be64 compare;
पूर्ण;

काष्ठा mthca_data_seg अणु
	__be32 byte_count;
	__be32 lkey;
	__be64 addr;
पूर्ण;

काष्ठा mthca_mlx_seg अणु
	__be32 nda_op;
	__be32 nds;
	__be32 flags;		/* [17] VL15 [16] SLR [14:12] अटल rate
				   [11:8] SL [3] C [2] E */
	__be16 rlid;
	__be16 vcrc;
पूर्ण;

अटल __always_अंतरभूत व्योम mthca_set_data_seg(काष्ठा mthca_data_seg *dseg,
					       काष्ठा ib_sge *sg)
अणु
	dseg->byte_count = cpu_to_be32(sg->length);
	dseg->lkey       = cpu_to_be32(sg->lkey);
	dseg->addr       = cpu_to_be64(sg->addr);
पूर्ण

अटल __always_अंतरभूत व्योम mthca_set_data_seg_inval(काष्ठा mthca_data_seg *dseg)
अणु
	dseg->byte_count = 0;
	dseg->lkey       = cpu_to_be32(MTHCA_INVAL_LKEY);
	dseg->addr       = 0;
पूर्ण

#पूर्ण_अगर /* MTHCA_WQE_H */
