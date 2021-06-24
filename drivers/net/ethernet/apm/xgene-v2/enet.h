<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_V2_ENET_H__
#घोषणा __XGENE_ENET_V2_ENET_H__

#घोषणा ENET_CLKEN		0xc008
#घोषणा ENET_SRST		0xc000
#घोषणा ENET_SHIM		0xc010
#घोषणा CFG_MEM_RAM_SHUTDOWN	0xd070
#घोषणा BLOCK_MEM_RDY		0xd074

#घोषणा MEM_RDY			0xffffffff
#घोषणा DEVM_ARAUX_COH		BIT(19)
#घोषणा DEVM_AWAUX_COH		BIT(3)

#घोषणा CFG_FORCE_LINK_STATUS_EN	0x229c
#घोषणा FORCE_LINK_STATUS		0x22a0
#घोषणा CFG_LINK_AGGR_RESUME		0x27c8
#घोषणा RX_DV_GATE_REG			0x2dfc

व्योम xge_wr_csr(काष्ठा xge_pdata *pdata, u32 offset, u32 val);
u32 xge_rd_csr(काष्ठा xge_pdata *pdata, u32 offset);
पूर्णांक xge_port_reset(काष्ठा net_device *ndev);
व्योम xge_port_init(काष्ठा net_device *ndev);

#पूर्ण_अगर  /* __XGENE_ENET_V2_ENET__H__ */
