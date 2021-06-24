<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित _HNS_GMAC_H
#घोषणा _HNS_GMAC_H

#समावेश "hns_dsaf_mac.h"

क्रमागत hns_port_mode अणु
	GMAC_10M_MII = 0,
	GMAC_100M_MII,
	GMAC_1000M_GMII,
	GMAC_10M_RGMII,
	GMAC_100M_RGMII,
	GMAC_1000M_RGMII,
	GMAC_10M_SGMII,
	GMAC_100M_SGMII,
	GMAC_1000M_SGMII,
	GMAC_10000M_SGMII	/* 10GE */
पूर्ण;

क्रमागत hns_gmac_duplex_mकरोe अणु
	GMAC_HALF_DUPLEX_MODE = 0,
	GMAC_FULL_DUPLEX_MODE
पूर्ण;

काष्ठा hns_gmac_port_mode_cfg अणु
	क्रमागत hns_port_mode port_mode;
	u32 max_frm_size;
	u32 लघु_runts_thr;
	u32 pad_enable;
	u32 crc_add;
	u32 an_enable;	/*स्वतः-nego enable  */
	u32 runt_pkt_en;
	u32 strip_pad_en;
पूर्ण;

#घोषणा ETH_GMAC_DUMP_NUM		96
#पूर्ण_अगर				/* __HNS_GMAC_H__ */
