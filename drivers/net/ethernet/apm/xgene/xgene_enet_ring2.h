<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2015, Applied Micro Circuits Corporation
 * Author: Iyappan Subramanian <isubramanian@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_RING2_H__
#घोषणा __XGENE_ENET_RING2_H__

#समावेश "xgene_enet_main.h"

#घोषणा X2_NUM_RING_CONFIG	6

#घोषणा INTR_MBOX_SIZE		1024
#घोषणा CSR_VMID0_INTR_MBOX	0x0270
#घोषणा INTR_CLEAR		BIT(23)

#घोषणा X2_MSG_AM_POS		10
#घोषणा X2_QBASE_AM_POS		11
#घोषणा X2_INTLINE_POS		24
#घोषणा X2_INTLINE_LEN		5
#घोषणा X2_CFGCRID_POS		29
#घोषणा X2_CFGCRID_LEN		3
#घोषणा X2_SELTHRSH_POS		7
#घोषणा X2_SELTHRSH_LEN		3
#घोषणा X2_RINGTYPE_POS		23
#घोषणा X2_RINGTYPE_LEN		2
#घोषणा X2_DEQINTEN_POS		29
#घोषणा X2_RECOMTIMEOUT_POS	0
#घोषणा X2_RECOMTIMEOUT_LEN	7
#घोषणा X2_NUMMSGSINQ_POS	0
#घोषणा X2_NUMMSGSINQ_LEN	17

बाह्य काष्ठा xgene_ring_ops xgene_ring2_ops;

#पूर्ण_अगर /* __XGENE_ENET_RING2_H__ */
