<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_V2_ETHTOOL_H__
#घोषणा __XGENE_ENET_V2_ETHTOOL_H__

काष्ठा xge_gstrings_stats अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक offset;
पूर्ण;

काष्ठा xge_gstrings_extd_stats अणु
	अक्षर name[ETH_GSTRING_LEN];
	u32 addr;
	u32 value;
पूर्ण;

#घोषणा TR64			0xa080
#घोषणा TR127			0xa084
#घोषणा TR255			0xa088
#घोषणा TR511			0xa08c
#घोषणा TR1K			0xa090
#घोषणा TRMAX			0xa094
#घोषणा TRMGV			0xa098
#घोषणा RFCS			0xa0a4
#घोषणा RMCA			0xa0a8
#घोषणा RBCA			0xa0ac
#घोषणा RXCF			0xa0b0
#घोषणा RXPF			0xa0b4
#घोषणा RXUO			0xa0b8
#घोषणा RALN			0xa0bc
#घोषणा RFLR			0xa0c0
#घोषणा RCDE			0xa0c4
#घोषणा RCSE			0xa0c8
#घोषणा RUND			0xa0cc
#घोषणा ROVR			0xa0d0
#घोषणा RFRG			0xa0d4
#घोषणा RJBR			0xa0d8
#घोषणा RDRP			0xa0dc
#घोषणा TMCA			0xa0e8
#घोषणा TBCA			0xa0ec
#घोषणा TXPF			0xa0f0
#घोषणा TDFR			0xa0f4
#घोषणा TEDF			0xa0f8
#घोषणा TSCL			0xa0fc
#घोषणा TMCL			0xa100
#घोषणा TLCL			0xa104
#घोषणा TXCL			0xa108
#घोषणा TNCL			0xa10c
#घोषणा TPFH			0xa110
#घोषणा TDRP			0xa114
#घोषणा TJBR			0xa118
#घोषणा TFCS			0xa11c
#घोषणा TXCF			0xa120
#घोषणा TOVR			0xa124
#घोषणा TUND			0xa128
#घोषणा TFRG			0xa12c

व्योम xge_set_ethtool_ops(काष्ठा net_device *ndev);

#पूर्ण_अगर  /* __XGENE_ENET_V2_ETHTOOL_H__ */
