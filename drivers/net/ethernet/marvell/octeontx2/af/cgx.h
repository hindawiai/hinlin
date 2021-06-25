<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 CGX driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित CGX_H
#घोषणा CGX_H

#समावेश "mbox.h"
#समावेश "cgx_fw_if.h"
#समावेश "rpm.h"

 /* PCI device IDs */
#घोषणा	PCI_DEVID_OCTEONTX2_CGX		0xA059

/* PCI BAR nos */
#घोषणा PCI_CFG_REG_BAR_NUM		0

#घोषणा CGX_ID_MASK			0x7
#घोषणा MAX_LMAC_PER_CGX		4
#घोषणा CGX_FIFO_LEN			65536 /* 64K क्रम both Rx & Tx */
#घोषणा CGX_OFFSET(x)			((x) * MAX_LMAC_PER_CGX)

/* Registers */
#घोषणा CGXX_CMRX_CFG			0x00
#घोषणा CMR_P2X_SEL_MASK		GENMASK_ULL(61, 59)
#घोषणा CMR_P2X_SEL_SHIFT		59ULL
#घोषणा CMR_P2X_SEL_NIX0		1ULL
#घोषणा CMR_P2X_SEL_NIX1		2ULL
#घोषणा CMR_EN				BIT_ULL(55)
#घोषणा DATA_PKT_TX_EN			BIT_ULL(53)
#घोषणा DATA_PKT_RX_EN			BIT_ULL(54)
#घोषणा CGX_LMAC_TYPE_SHIFT		40
#घोषणा CGX_LMAC_TYPE_MASK		0xF
#घोषणा CGXX_CMRX_INT			0x040
#घोषणा FW_CGX_INT			BIT_ULL(1)
#घोषणा CGXX_CMRX_INT_ENA_W1S		0x058
#घोषणा CGXX_CMRX_RX_ID_MAP		0x060
#घोषणा CGXX_CMRX_RX_STAT0		0x070
#घोषणा CGXX_CMRX_RX_LMACS		0x128
#घोषणा CGXX_CMRX_RX_DMAC_CTL0		(0x1F8 + mac_ops->csr_offset)
#घोषणा CGX_DMAC_CTL0_CAM_ENABLE	BIT_ULL(3)
#घोषणा CGX_DMAC_CAM_ACCEPT		BIT_ULL(3)
#घोषणा CGX_DMAC_MCAST_MODE		BIT_ULL(1)
#घोषणा CGX_DMAC_BCAST_MODE		BIT_ULL(0)
#घोषणा CGXX_CMRX_RX_DMAC_CAM0		(0x200 + mac_ops->csr_offset)
#घोषणा CGX_DMAC_CAM_ADDR_ENABLE	BIT_ULL(48)
#घोषणा CGXX_CMRX_RX_DMAC_CAM1		0x400
#घोषणा CGX_RX_DMAC_ADR_MASK		GENMASK_ULL(47, 0)
#घोषणा CGXX_CMRX_TX_STAT0		0x700
#घोषणा CGXX_SCRATCH0_REG		0x1050
#घोषणा CGXX_SCRATCH1_REG		0x1058
#घोषणा CGX_CONST			0x2000
#घोषणा CGX_CONST_RXFIFO_SIZE	        GENMASK_ULL(23, 0)
#घोषणा CGXX_SPUX_CONTROL1		0x10000
#घोषणा CGXX_SPUX_LNX_FEC_CORR_BLOCKS	0x10700
#घोषणा CGXX_SPUX_LNX_FEC_UNCORR_BLOCKS	0x10800
#घोषणा CGXX_SPUX_RSFEC_CORR		0x10088
#घोषणा CGXX_SPUX_RSFEC_UNCORR		0x10090

#घोषणा CGXX_SPUX_CONTROL1_LBK		BIT_ULL(14)
#घोषणा CGXX_GMP_PCS_MRX_CTL		0x30000
#घोषणा CGXX_GMP_PCS_MRX_CTL_LBK	BIT_ULL(14)

#घोषणा CGXX_SMUX_RX_FRM_CTL		0x20020
#घोषणा CGX_SMUX_RX_FRM_CTL_CTL_BCK	BIT_ULL(3)
#घोषणा CGX_SMUX_RX_FRM_CTL_PTP_MODE	BIT_ULL(12)
#घोषणा CGXX_GMP_GMI_RXX_FRM_CTL	0x38028
#घोषणा CGX_GMP_GMI_RXX_FRM_CTL_CTL_BCK	BIT_ULL(3)
#घोषणा CGX_GMP_GMI_RXX_FRM_CTL_PTP_MODE BIT_ULL(12)
#घोषणा CGXX_SMUX_TX_CTL		0x20178
#घोषणा CGXX_SMUX_TX_PAUSE_PKT_TIME	0x20110
#घोषणा CGXX_SMUX_TX_PAUSE_PKT_INTERVAL	0x20120
#घोषणा CGXX_GMP_GMI_TX_PAUSE_PKT_TIME	0x38230
#घोषणा CGXX_GMP_GMI_TX_PAUSE_PKT_INTERVAL	0x38248
#घोषणा CGX_SMUX_TX_CTL_L2P_BP_CONV	BIT_ULL(7)
#घोषणा CGXX_CMR_RX_OVR_BP		0x130
#घोषणा CGX_CMR_RX_OVR_BP_EN(X)		BIT_ULL(((X) + 8))
#घोषणा CGX_CMR_RX_OVR_BP_BP(X)		BIT_ULL(((X) + 4))

#घोषणा CGX_COMMAND_REG			CGXX_SCRATCH1_REG
#घोषणा CGX_EVENT_REG			CGXX_SCRATCH0_REG
#घोषणा CGX_CMD_TIMEOUT			2200 /* msecs */
#घोषणा DEFAULT_PAUSE_TIME		0x7FF

#घोषणा CGX_LMAC_FWI			0

क्रमागत  cgx_nix_stat_type अणु
	NIX_STATS_RX,
	NIX_STATS_TX,
पूर्ण;

क्रमागत LMAC_TYPE अणु
	LMAC_MODE_SGMII		= 0,
	LMAC_MODE_XAUI		= 1,
	LMAC_MODE_RXAUI		= 2,
	LMAC_MODE_10G_R		= 3,
	LMAC_MODE_40G_R		= 4,
	LMAC_MODE_QSGMII	= 6,
	LMAC_MODE_25G_R		= 7,
	LMAC_MODE_50G_R		= 8,
	LMAC_MODE_100G_R	= 9,
	LMAC_MODE_USXGMII	= 10,
	LMAC_MODE_MAX,
पूर्ण;

काष्ठा cgx_link_event अणु
	काष्ठा cgx_link_user_info link_uinfo;
	u8 cgx_id;
	u8 lmac_id;
पूर्ण;

/**
 * काष्ठा cgx_event_cb
 * @notअगरy_link_chg:	callback क्रम link change notअगरication
 * @data:	data passed to callback function
 */
काष्ठा cgx_event_cb अणु
	पूर्णांक (*notअगरy_link_chg)(काष्ठा cgx_link_event *event, व्योम *data);
	व्योम *data;
पूर्ण;

बाह्य काष्ठा pci_driver cgx_driver;

पूर्णांक cgx_get_cgxcnt_max(व्योम);
पूर्णांक cgx_get_cgxid(व्योम *cgxd);
पूर्णांक cgx_get_lmac_cnt(व्योम *cgxd);
व्योम *cgx_get_pdata(पूर्णांक cgx_id);
पूर्णांक cgx_set_pkind(व्योम *cgxd, u8 lmac_id, पूर्णांक pkind);
पूर्णांक cgx_lmac_evh_रेजिस्टर(काष्ठा cgx_event_cb *cb, व्योम *cgxd, पूर्णांक lmac_id);
पूर्णांक cgx_lmac_evh_unरेजिस्टर(व्योम *cgxd, पूर्णांक lmac_id);
पूर्णांक cgx_get_tx_stats(व्योम *cgxd, पूर्णांक lmac_id, पूर्णांक idx, u64 *tx_stat);
पूर्णांक cgx_get_rx_stats(व्योम *cgxd, पूर्णांक lmac_id, पूर्णांक idx, u64 *rx_stat);
पूर्णांक cgx_lmac_rx_tx_enable(व्योम *cgxd, पूर्णांक lmac_id, bool enable);
पूर्णांक cgx_lmac_tx_enable(व्योम *cgxd, पूर्णांक lmac_id, bool enable);
पूर्णांक cgx_lmac_addr_set(u8 cgx_id, u8 lmac_id, u8 *mac_addr);
u64 cgx_lmac_addr_get(u8 cgx_id, u8 lmac_id);
व्योम cgx_lmac_promisc_config(पूर्णांक cgx_id, पूर्णांक lmac_id, bool enable);
व्योम cgx_lmac_enadis_rx_छोड़ो_fwding(व्योम *cgxd, पूर्णांक lmac_id, bool enable);
पूर्णांक cgx_lmac_पूर्णांकernal_loopback(व्योम *cgxd, पूर्णांक lmac_id, bool enable);
पूर्णांक cgx_get_link_info(व्योम *cgxd, पूर्णांक lmac_id,
		      काष्ठा cgx_link_user_info *linfo);
पूर्णांक cgx_lmac_linkup_start(व्योम *cgxd);
पूर्णांक cgx_get_fwdata_base(u64 *base);
पूर्णांक cgx_lmac_get_छोड़ो_frm(व्योम *cgxd, पूर्णांक lmac_id,
			   u8 *tx_छोड़ो, u8 *rx_छोड़ो);
पूर्णांक cgx_lmac_set_छोड़ो_frm(व्योम *cgxd, पूर्णांक lmac_id,
			   u8 tx_छोड़ो, u8 rx_छोड़ो);
व्योम cgx_lmac_ptp_config(व्योम *cgxd, पूर्णांक lmac_id, bool enable);
u8 cgx_lmac_get_p2x(पूर्णांक cgx_id, पूर्णांक lmac_id);
पूर्णांक cgx_set_fec(u64 fec, पूर्णांक cgx_id, पूर्णांक lmac_id);
पूर्णांक cgx_get_fec_stats(व्योम *cgxd, पूर्णांक lmac_id, काष्ठा cgx_fec_stats_rsp *rsp);
पूर्णांक cgx_get_phy_fec_stats(व्योम *cgxd, पूर्णांक lmac_id);
पूर्णांक cgx_set_link_mode(व्योम *cgxd, काष्ठा cgx_set_link_mode_args args,
		      पूर्णांक cgx_id, पूर्णांक lmac_id);
u64 cgx_features_get(व्योम *cgxd);
काष्ठा mac_ops *get_mac_ops(व्योम *cgxd);
पूर्णांक cgx_get_nr_lmacs(व्योम *cgxd);
u8 cgx_get_lmacid(व्योम *cgxd, u8 lmac_index);
अचिन्हित दीर्घ cgx_get_lmac_bmap(व्योम *cgxd);
व्योम cgx_lmac_ग_लिखो(पूर्णांक cgx_id, पूर्णांक lmac_id, u64 offset, u64 val);
u64 cgx_lmac_पढ़ो(पूर्णांक cgx_id, पूर्णांक lmac_id, u64 offset);
#पूर्ण_अगर /* CGX_H */
