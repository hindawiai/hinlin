<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 CGX driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>

#समावेश "cgx.h"
#समावेश "rvu.h"
#समावेश "lmac_common.h"

#घोषणा DRV_NAME	"Marvell-CGX/RPM"
#घोषणा DRV_STRING      "Marvell CGX/RPM Driver"

अटल LIST_HEAD(cgx_list);

/* Convert firmware speed encoding to user क्रमmat(Mbps) */
अटल स्थिर u32 cgx_speed_mbps[CGX_LINK_SPEED_MAX] = अणु
	[CGX_LINK_NONE] = 0,
	[CGX_LINK_10M] = 10,
	[CGX_LINK_100M] = 100,
	[CGX_LINK_1G] = 1000,
	[CGX_LINK_2HG] = 2500,
	[CGX_LINK_5G] = 5000,
	[CGX_LINK_10G] = 10000,
	[CGX_LINK_20G] = 20000,
	[CGX_LINK_25G] = 25000,
	[CGX_LINK_40G] = 40000,
	[CGX_LINK_50G] = 50000,
	[CGX_LINK_80G] = 80000,
	[CGX_LINK_100G] = 100000,
पूर्ण;

/* Convert firmware lmac type encoding to string */
अटल स्थिर अक्षर *cgx_lmactype_string[LMAC_MODE_MAX] = अणु
	[LMAC_MODE_SGMII] = "SGMII",
	[LMAC_MODE_XAUI] = "XAUI",
	[LMAC_MODE_RXAUI] = "RXAUI",
	[LMAC_MODE_10G_R] = "10G_R",
	[LMAC_MODE_40G_R] = "40G_R",
	[LMAC_MODE_QSGMII] = "QSGMII",
	[LMAC_MODE_25G_R] = "25G_R",
	[LMAC_MODE_50G_R] = "50G_R",
	[LMAC_MODE_100G_R] = "100G_R",
	[LMAC_MODE_USXGMII] = "USXGMII",
पूर्ण;

/* CGX PHY management पूर्णांकernal APIs */
अटल पूर्णांक cgx_fwi_link_change(काष्ठा cgx *cgx, पूर्णांक lmac_id, bool en);

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id cgx_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_CGX) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_CN10K_RPM) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_DEVICE_TABLE(pci, cgx_id_table);

अटल bool is_dev_rpm(व्योम *cgxd)
अणु
	काष्ठा cgx *cgx = cgxd;

	वापस (cgx->pdev->device == PCI_DEVID_CN10K_RPM);
पूर्ण

bool is_lmac_valid(काष्ठा cgx *cgx, पूर्णांक lmac_id)
अणु
	अगर (!cgx || lmac_id < 0 || lmac_id >= MAX_LMAC_PER_CGX)
		वापस false;
	वापस test_bit(lmac_id, &cgx->lmac_bmap);
पूर्ण

काष्ठा mac_ops *get_mac_ops(व्योम *cgxd)
अणु
	अगर (!cgxd)
		वापस cgxd;

	वापस ((काष्ठा cgx *)cgxd)->mac_ops;
पूर्ण

व्योम cgx_ग_लिखो(काष्ठा cgx *cgx, u64 lmac, u64 offset, u64 val)
अणु
	ग_लिखोq(val, cgx->reg_base + (lmac << cgx->mac_ops->lmac_offset) +
	       offset);
पूर्ण

u64 cgx_पढ़ो(काष्ठा cgx *cgx, u64 lmac, u64 offset)
अणु
	वापस पढ़ोq(cgx->reg_base + (lmac << cgx->mac_ops->lmac_offset) +
		     offset);
पूर्ण

काष्ठा lmac *lmac_pdata(u8 lmac_id, काष्ठा cgx *cgx)
अणु
	अगर (!cgx || lmac_id >= MAX_LMAC_PER_CGX)
		वापस शून्य;

	वापस cgx->lmac_idmap[lmac_id];
पूर्ण

पूर्णांक cgx_get_cgxcnt_max(व्योम)
अणु
	काष्ठा cgx *cgx_dev;
	पूर्णांक idmax = -ENODEV;

	list_क्रम_each_entry(cgx_dev, &cgx_list, cgx_list)
		अगर (cgx_dev->cgx_id > idmax)
			idmax = cgx_dev->cgx_id;

	अगर (idmax < 0)
		वापस 0;

	वापस idmax + 1;
पूर्ण

पूर्णांक cgx_get_lmac_cnt(व्योम *cgxd)
अणु
	काष्ठा cgx *cgx = cgxd;

	अगर (!cgx)
		वापस -ENODEV;

	वापस cgx->lmac_count;
पूर्ण

व्योम *cgx_get_pdata(पूर्णांक cgx_id)
अणु
	काष्ठा cgx *cgx_dev;

	list_क्रम_each_entry(cgx_dev, &cgx_list, cgx_list) अणु
		अगर (cgx_dev->cgx_id == cgx_id)
			वापस cgx_dev;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम cgx_lmac_ग_लिखो(पूर्णांक cgx_id, पूर्णांक lmac_id, u64 offset, u64 val)
अणु
	काष्ठा cgx *cgx_dev = cgx_get_pdata(cgx_id);

	cgx_ग_लिखो(cgx_dev, lmac_id, offset, val);
पूर्ण

u64 cgx_lmac_पढ़ो(पूर्णांक cgx_id, पूर्णांक lmac_id, u64 offset)
अणु
	काष्ठा cgx *cgx_dev = cgx_get_pdata(cgx_id);

	वापस cgx_पढ़ो(cgx_dev, lmac_id, offset);
पूर्ण

पूर्णांक cgx_get_cgxid(व्योम *cgxd)
अणु
	काष्ठा cgx *cgx = cgxd;

	अगर (!cgx)
		वापस -EINVAL;

	वापस cgx->cgx_id;
पूर्ण

u8 cgx_lmac_get_p2x(पूर्णांक cgx_id, पूर्णांक lmac_id)
अणु
	काष्ठा cgx *cgx_dev = cgx_get_pdata(cgx_id);
	u64 cfg;

	cfg = cgx_पढ़ो(cgx_dev, lmac_id, CGXX_CMRX_CFG);

	वापस (cfg & CMR_P2X_SEL_MASK) >> CMR_P2X_SEL_SHIFT;
पूर्ण

/* Ensure the required lock क्रम event queue(where asynchronous events are
 * posted) is acquired beक्रमe calling this API. Else an asynchronous event(with
 * latest link status) can reach the destination beक्रमe this function वापसs
 * and could make the link status appear wrong.
 */
पूर्णांक cgx_get_link_info(व्योम *cgxd, पूर्णांक lmac_id,
		      काष्ठा cgx_link_user_info *linfo)
अणु
	काष्ठा lmac *lmac = lmac_pdata(lmac_id, cgxd);

	अगर (!lmac)
		वापस -ENODEV;

	*linfo = lmac->link_info;
	वापस 0;
पूर्ण

अटल u64 mac2u64 (u8 *mac_addr)
अणु
	u64 mac = 0;
	पूर्णांक index;

	क्रम (index = ETH_ALEN - 1; index >= 0; index--)
		mac |= ((u64)*mac_addr++) << (8 * index);
	वापस mac;
पूर्ण

पूर्णांक cgx_lmac_addr_set(u8 cgx_id, u8 lmac_id, u8 *mac_addr)
अणु
	काष्ठा cgx *cgx_dev = cgx_get_pdata(cgx_id);
	काष्ठा mac_ops *mac_ops;
	u64 cfg;

	mac_ops = cgx_dev->mac_ops;
	/* copy 6bytes from macaddr */
	/* स_नकल(&cfg, mac_addr, 6); */

	cfg = mac2u64 (mac_addr);

	cgx_ग_लिखो(cgx_dev, 0, (CGXX_CMRX_RX_DMAC_CAM0 + (lmac_id * 0x8)),
		  cfg | CGX_DMAC_CAM_ADDR_ENABLE | ((u64)lmac_id << 49));

	cfg = cgx_पढ़ो(cgx_dev, lmac_id, CGXX_CMRX_RX_DMAC_CTL0);
	cfg |= CGX_DMAC_CTL0_CAM_ENABLE;
	cgx_ग_लिखो(cgx_dev, lmac_id, CGXX_CMRX_RX_DMAC_CTL0, cfg);

	वापस 0;
पूर्ण

u64 cgx_lmac_addr_get(u8 cgx_id, u8 lmac_id)
अणु
	काष्ठा cgx *cgx_dev = cgx_get_pdata(cgx_id);
	काष्ठा mac_ops *mac_ops;
	u64 cfg;

	mac_ops = cgx_dev->mac_ops;

	cfg = cgx_पढ़ो(cgx_dev, 0, CGXX_CMRX_RX_DMAC_CAM0 + lmac_id * 0x8);
	वापस cfg & CGX_RX_DMAC_ADR_MASK;
पूर्ण

पूर्णांक cgx_set_pkind(व्योम *cgxd, u8 lmac_id, पूर्णांक pkind)
अणु
	काष्ठा cgx *cgx = cgxd;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;

	cgx_ग_लिखो(cgx, lmac_id, CGXX_CMRX_RX_ID_MAP, (pkind & 0x3F));
	वापस 0;
पूर्ण

अटल u8 cgx_get_lmac_type(व्योम *cgxd, पूर्णांक lmac_id)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_CFG);
	वापस (cfg >> CGX_LMAC_TYPE_SHIFT) & CGX_LMAC_TYPE_MASK;
पूर्ण

/* Configure CGX LMAC in पूर्णांकernal loopback mode */
पूर्णांक cgx_lmac_पूर्णांकernal_loopback(व्योम *cgxd, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgxd;
	u8 lmac_type;
	u64 cfg;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;

	lmac_type = cgx->mac_ops->get_lmac_type(cgx, lmac_id);
	अगर (lmac_type == LMAC_MODE_SGMII || lmac_type == LMAC_MODE_QSGMII) अणु
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_PCS_MRX_CTL);
		अगर (enable)
			cfg |= CGXX_GMP_PCS_MRX_CTL_LBK;
		अन्यथा
			cfg &= ~CGXX_GMP_PCS_MRX_CTL_LBK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_PCS_MRX_CTL, cfg);
	पूर्ण अन्यथा अणु
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SPUX_CONTROL1);
		अगर (enable)
			cfg |= CGXX_SPUX_CONTROL1_LBK;
		अन्यथा
			cfg &= ~CGXX_SPUX_CONTROL1_LBK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SPUX_CONTROL1, cfg);
	पूर्ण
	वापस 0;
पूर्ण

व्योम cgx_lmac_promisc_config(पूर्णांक cgx_id, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgx_get_pdata(cgx_id);
	काष्ठा mac_ops *mac_ops;
	u64 cfg = 0;

	अगर (!cgx)
		वापस;

	mac_ops = cgx->mac_ops;
	अगर (enable) अणु
		/* Enable promiscuous mode on LMAC */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_RX_DMAC_CTL0);
		cfg &= ~(CGX_DMAC_CAM_ACCEPT | CGX_DMAC_MCAST_MODE);
		cfg |= CGX_DMAC_BCAST_MODE;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_CMRX_RX_DMAC_CTL0, cfg);

		cfg = cgx_पढ़ो(cgx, 0,
			       (CGXX_CMRX_RX_DMAC_CAM0 + lmac_id * 0x8));
		cfg &= ~CGX_DMAC_CAM_ADDR_ENABLE;
		cgx_ग_लिखो(cgx, 0,
			  (CGXX_CMRX_RX_DMAC_CAM0 + lmac_id * 0x8), cfg);
	पूर्ण अन्यथा अणु
		/* Disable promiscuous mode */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_RX_DMAC_CTL0);
		cfg |= CGX_DMAC_CAM_ACCEPT | CGX_DMAC_MCAST_MODE;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_CMRX_RX_DMAC_CTL0, cfg);
		cfg = cgx_पढ़ो(cgx, 0,
			       (CGXX_CMRX_RX_DMAC_CAM0 + lmac_id * 0x8));
		cfg |= CGX_DMAC_CAM_ADDR_ENABLE;
		cgx_ग_लिखो(cgx, 0,
			  (CGXX_CMRX_RX_DMAC_CAM0 + lmac_id * 0x8), cfg);
	पूर्ण
पूर्ण

/* Enable or disable क्रमwarding received छोड़ो frames to Tx block */
व्योम cgx_lmac_enadis_rx_छोड़ो_fwding(व्योम *cgxd, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	अगर (!cgx)
		वापस;

	अगर (enable) अणु
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL);
		cfg |= CGX_GMP_GMI_RXX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL, cfg);

		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
		cfg |= CGX_SMUX_RX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id,	CGXX_SMUX_RX_FRM_CTL, cfg);
	पूर्ण अन्यथा अणु
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL);
		cfg &= ~CGX_GMP_GMI_RXX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL, cfg);

		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
		cfg &= ~CGX_SMUX_RX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id,	CGXX_SMUX_RX_FRM_CTL, cfg);
	पूर्ण
पूर्ण

पूर्णांक cgx_get_rx_stats(व्योम *cgxd, पूर्णांक lmac_id, पूर्णांक idx, u64 *rx_stat)
अणु
	काष्ठा cgx *cgx = cgxd;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;
	*rx_stat =  cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_RX_STAT0 + (idx * 8));
	वापस 0;
पूर्ण

पूर्णांक cgx_get_tx_stats(व्योम *cgxd, पूर्णांक lmac_id, पूर्णांक idx, u64 *tx_stat)
अणु
	काष्ठा cgx *cgx = cgxd;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;
	*tx_stat = cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_TX_STAT0 + (idx * 8));
	वापस 0;
पूर्ण

u64 cgx_features_get(व्योम *cgxd)
अणु
	वापस ((काष्ठा cgx *)cgxd)->hw_features;
पूर्ण

अटल पूर्णांक cgx_set_fec_stats_count(काष्ठा cgx_link_user_info *linfo)
अणु
	अगर (!linfo->fec)
		वापस 0;

	चयन (linfo->lmac_type_id) अणु
	हाल LMAC_MODE_SGMII:
	हाल LMAC_MODE_XAUI:
	हाल LMAC_MODE_RXAUI:
	हाल LMAC_MODE_QSGMII:
		वापस 0;
	हाल LMAC_MODE_10G_R:
	हाल LMAC_MODE_25G_R:
	हाल LMAC_MODE_100G_R:
	हाल LMAC_MODE_USXGMII:
		वापस 1;
	हाल LMAC_MODE_40G_R:
		वापस 4;
	हाल LMAC_MODE_50G_R:
		अगर (linfo->fec == OTX2_FEC_BASER)
			वापस 2;
		अन्यथा
			वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक cgx_get_fec_stats(व्योम *cgxd, पूर्णांक lmac_id, काष्ठा cgx_fec_stats_rsp *rsp)
अणु
	पूर्णांक stats, fec_stats_count = 0;
	पूर्णांक corr_reg, uncorr_reg;
	काष्ठा cgx *cgx = cgxd;

	अगर (!cgx || lmac_id >= cgx->lmac_count)
		वापस -ENODEV;
	fec_stats_count =
		cgx_set_fec_stats_count(&cgx->lmac_idmap[lmac_id]->link_info);
	अगर (cgx->lmac_idmap[lmac_id]->link_info.fec == OTX2_FEC_BASER) अणु
		corr_reg = CGXX_SPUX_LNX_FEC_CORR_BLOCKS;
		uncorr_reg = CGXX_SPUX_LNX_FEC_UNCORR_BLOCKS;
	पूर्ण अन्यथा अणु
		corr_reg = CGXX_SPUX_RSFEC_CORR;
		uncorr_reg = CGXX_SPUX_RSFEC_UNCORR;
	पूर्ण
	क्रम (stats = 0; stats < fec_stats_count; stats++) अणु
		rsp->fec_corr_blks +=
			cgx_पढ़ो(cgx, lmac_id, corr_reg + (stats * 8));
		rsp->fec_uncorr_blks +=
			cgx_पढ़ो(cgx, lmac_id, uncorr_reg + (stats * 8));
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cgx_lmac_rx_tx_enable(व्योम *cgxd, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_CFG);
	अगर (enable)
		cfg |= CMR_EN | DATA_PKT_RX_EN | DATA_PKT_TX_EN;
	अन्यथा
		cfg &= ~(CMR_EN | DATA_PKT_RX_EN | DATA_PKT_TX_EN);
	cgx_ग_लिखो(cgx, lmac_id, CGXX_CMRX_CFG, cfg);
	वापस 0;
पूर्ण

पूर्णांक cgx_lmac_tx_enable(व्योम *cgxd, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg, last;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_CMRX_CFG);
	last = cfg;
	अगर (enable)
		cfg |= DATA_PKT_TX_EN;
	अन्यथा
		cfg &= ~DATA_PKT_TX_EN;

	अगर (cfg != last)
		cgx_ग_लिखो(cgx, lmac_id, CGXX_CMRX_CFG, cfg);
	वापस !!(last & DATA_PKT_TX_EN);
पूर्ण

अटल पूर्णांक cgx_lmac_get_छोड़ो_frm_status(व्योम *cgxd, पूर्णांक lmac_id,
					 u8 *tx_छोड़ो, u8 *rx_छोड़ो)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	अगर (is_dev_rpm(cgx))
		वापस 0;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
	*rx_छोड़ो = !!(cfg & CGX_SMUX_RX_FRM_CTL_CTL_BCK);

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_TX_CTL);
	*tx_छोड़ो = !!(cfg & CGX_SMUX_TX_CTL_L2P_BP_CONV);
	वापस 0;
पूर्ण

अटल पूर्णांक cgx_lmac_enadis_छोड़ो_frm(व्योम *cgxd, पूर्णांक lmac_id,
				     u8 tx_छोड़ो, u8 rx_छोड़ो)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	अगर (is_dev_rpm(cgx))
		वापस 0;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस -ENODEV;

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
	cfg &= ~CGX_SMUX_RX_FRM_CTL_CTL_BCK;
	cfg |= rx_छोड़ो ? CGX_SMUX_RX_FRM_CTL_CTL_BCK : 0x0;
	cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL, cfg);

	cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_TX_CTL);
	cfg &= ~CGX_SMUX_TX_CTL_L2P_BP_CONV;
	cfg |= tx_छोड़ो ? CGX_SMUX_TX_CTL_L2P_BP_CONV : 0x0;
	cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_TX_CTL, cfg);

	cfg = cgx_पढ़ो(cgx, 0, CGXX_CMR_RX_OVR_BP);
	अगर (tx_छोड़ो) अणु
		cfg &= ~CGX_CMR_RX_OVR_BP_EN(lmac_id);
	पूर्ण अन्यथा अणु
		cfg |= CGX_CMR_RX_OVR_BP_EN(lmac_id);
		cfg &= ~CGX_CMR_RX_OVR_BP_BP(lmac_id);
	पूर्ण
	cgx_ग_लिखो(cgx, 0, CGXX_CMR_RX_OVR_BP, cfg);
	वापस 0;
पूर्ण

अटल व्योम cgx_lmac_छोड़ो_frm_config(व्योम *cgxd, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	अगर (!is_lmac_valid(cgx, lmac_id))
		वापस;
	अगर (enable) अणु
		/* Enable receive छोड़ो frames */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
		cfg |= CGX_SMUX_RX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL, cfg);

		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL);
		cfg |= CGX_GMP_GMI_RXX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL, cfg);

		/* Enable छोड़ो frames transmission */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_TX_CTL);
		cfg |= CGX_SMUX_TX_CTL_L2P_BP_CONV;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_TX_CTL, cfg);

		/* Set छोड़ो समय and पूर्णांकerval */
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_TX_PAUSE_PKT_TIME,
			  DEFAULT_PAUSE_TIME);
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_TX_PAUSE_PKT_INTERVAL);
		cfg &= ~0xFFFFULL;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_TX_PAUSE_PKT_INTERVAL,
			  cfg | (DEFAULT_PAUSE_TIME / 2));

		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_TX_PAUSE_PKT_TIME,
			  DEFAULT_PAUSE_TIME);

		cfg = cgx_पढ़ो(cgx, lmac_id,
			       CGXX_GMP_GMI_TX_PAUSE_PKT_INTERVAL);
		cfg &= ~0xFFFFULL;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_TX_PAUSE_PKT_INTERVAL,
			  cfg | (DEFAULT_PAUSE_TIME / 2));
	पूर्ण अन्यथा अणु
		/* ALL छोड़ो frames received are completely ignored */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
		cfg &= ~CGX_SMUX_RX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL, cfg);

		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL);
		cfg &= ~CGX_GMP_GMI_RXX_FRM_CTL_CTL_BCK;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL, cfg);

		/* Disable छोड़ो frames transmission */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_TX_CTL);
		cfg &= ~CGX_SMUX_TX_CTL_L2P_BP_CONV;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_TX_CTL, cfg);
	पूर्ण
पूर्ण

व्योम cgx_lmac_ptp_config(व्योम *cgxd, पूर्णांक lmac_id, bool enable)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 cfg;

	अगर (!cgx)
		वापस;

	अगर (is_dev_rpm(cgx))
		वापस;

	अगर (enable) अणु
		/* Enable inbound PTP बारtamping */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL);
		cfg |= CGX_GMP_GMI_RXX_FRM_CTL_PTP_MODE;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL, cfg);

		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
		cfg |= CGX_SMUX_RX_FRM_CTL_PTP_MODE;
		cgx_ग_लिखो(cgx, lmac_id,	CGXX_SMUX_RX_FRM_CTL, cfg);
	पूर्ण अन्यथा अणु
		/* Disable inbound PTP stamping */
		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL);
		cfg &= ~CGX_GMP_GMI_RXX_FRM_CTL_PTP_MODE;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_GMP_GMI_RXX_FRM_CTL, cfg);

		cfg = cgx_पढ़ो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL);
		cfg &= ~CGX_SMUX_RX_FRM_CTL_PTP_MODE;
		cgx_ग_लिखो(cgx, lmac_id, CGXX_SMUX_RX_FRM_CTL, cfg);
	पूर्ण
पूर्ण

/* CGX Firmware पूर्णांकerface low level support */
पूर्णांक cgx_fwi_cmd_send(u64 req, u64 *resp, काष्ठा lmac *lmac)
अणु
	काष्ठा cgx *cgx = lmac->cgx;
	काष्ठा device *dev;
	पूर्णांक err = 0;
	u64 cmd;

	/* Ensure no other command is in progress */
	err = mutex_lock_पूर्णांकerruptible(&lmac->cmd_lock);
	अगर (err)
		वापस err;

	/* Ensure command रेजिस्टर is मुक्त */
	cmd = cgx_पढ़ो(cgx, lmac->lmac_id,  CGX_COMMAND_REG);
	अगर (FIELD_GET(CMDREG_OWN, cmd) != CGX_CMD_OWN_NS) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	/* Update ownership in command request */
	req = FIELD_SET(CMDREG_OWN, CGX_CMD_OWN_FIRMWARE, req);

	/* Mark this lmac as pending, beक्रमe we start */
	lmac->cmd_pend = true;

	/* Start command in hardware */
	cgx_ग_लिखो(cgx, lmac->lmac_id, CGX_COMMAND_REG, req);

	/* Ensure command is completed without errors */
	अगर (!रुको_event_समयout(lmac->wq_cmd_cmplt, !lmac->cmd_pend,
				msecs_to_jअगरfies(CGX_CMD_TIMEOUT))) अणु
		dev = &cgx->pdev->dev;
		dev_err(dev, "cgx port %d:%d cmd timeout\n",
			cgx->cgx_id, lmac->lmac_id);
		err = -EIO;
		जाओ unlock;
	पूर्ण

	/* we have a valid command response */
	smp_rmb(); /* Ensure the latest updates are visible */
	*resp = lmac->resp;

unlock:
	mutex_unlock(&lmac->cmd_lock);

	वापस err;
पूर्ण

पूर्णांक cgx_fwi_cmd_generic(u64 req, u64 *resp, काष्ठा cgx *cgx, पूर्णांक lmac_id)
अणु
	काष्ठा lmac *lmac;
	पूर्णांक err;

	lmac = lmac_pdata(lmac_id, cgx);
	अगर (!lmac)
		वापस -ENODEV;

	err = cgx_fwi_cmd_send(req, resp, lmac);

	/* Check क्रम valid response */
	अगर (!err) अणु
		अगर (FIELD_GET(EVTREG_STAT, *resp) == CGX_STAT_FAIL)
			वापस -EIO;
		अन्यथा
			वापस 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cgx_link_usertable_index_map(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_10:
		वापस CGX_LINK_10M;
	हाल SPEED_100:
		वापस CGX_LINK_100M;
	हाल SPEED_1000:
		वापस CGX_LINK_1G;
	हाल SPEED_2500:
		वापस CGX_LINK_2HG;
	हाल SPEED_5000:
		वापस CGX_LINK_5G;
	हाल SPEED_10000:
		वापस CGX_LINK_10G;
	हाल SPEED_20000:
		वापस CGX_LINK_20G;
	हाल SPEED_25000:
		वापस CGX_LINK_25G;
	हाल SPEED_40000:
		वापस CGX_LINK_40G;
	हाल SPEED_50000:
		वापस CGX_LINK_50G;
	हाल 80000:
		वापस CGX_LINK_80G;
	हाल SPEED_100000:
		वापस CGX_LINK_100G;
	हाल SPEED_UNKNOWN:
		वापस CGX_LINK_NONE;
	पूर्ण
	वापस CGX_LINK_NONE;
पूर्ण

अटल व्योम set_mod_args(काष्ठा cgx_set_link_mode_args *args,
			 u32 speed, u8 duplex, u8 स्वतःneg, u64 mode)
अणु
	/* Fill शेष values inहाल of user did not pass
	 * valid parameters
	 */
	अगर (args->duplex == DUPLEX_UNKNOWN)
		args->duplex = duplex;
	अगर (args->speed == SPEED_UNKNOWN)
		args->speed = speed;
	अगर (args->an == AUTONEG_UNKNOWN)
		args->an = स्वतःneg;
	args->mode = mode;
	args->ports = 0;
पूर्ण

अटल व्योम otx2_map_ethtool_link_modes(u64 biपंचांगask,
					काष्ठा cgx_set_link_mode_args *args)
अणु
	चयन (biपंचांगask) अणु
	हाल ETHTOOL_LINK_MODE_10baseT_Half_BIT:
		set_mod_args(args, 10, 1, 1, BIT_ULL(CGX_MODE_SGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_10baseT_Full_BIT:
		set_mod_args(args, 10, 0, 1, BIT_ULL(CGX_MODE_SGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_100baseT_Half_BIT:
		set_mod_args(args, 100, 1, 1, BIT_ULL(CGX_MODE_SGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_100baseT_Full_BIT:
		set_mod_args(args, 100, 0, 1, BIT_ULL(CGX_MODE_SGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_1000baseT_Half_BIT:
		set_mod_args(args, 1000, 1, 1, BIT_ULL(CGX_MODE_SGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_1000baseT_Full_BIT:
		set_mod_args(args, 1000, 0, 1, BIT_ULL(CGX_MODE_SGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_1000baseX_Full_BIT:
		set_mod_args(args, 1000, 0, 0, BIT_ULL(CGX_MODE_1000_BASEX));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_10000baseT_Full_BIT:
		set_mod_args(args, 1000, 0, 1, BIT_ULL(CGX_MODE_QSGMII));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_10000baseSR_Full_BIT:
		set_mod_args(args, 10000, 0, 0, BIT_ULL(CGX_MODE_10G_C2C));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_10000baseLR_Full_BIT:
		set_mod_args(args, 10000, 0, 0, BIT_ULL(CGX_MODE_10G_C2M));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_10000baseKR_Full_BIT:
		set_mod_args(args, 10000, 0, 1, BIT_ULL(CGX_MODE_10G_KR));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_25000baseSR_Full_BIT:
		set_mod_args(args, 25000, 0, 0, BIT_ULL(CGX_MODE_25G_C2C));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_25000baseCR_Full_BIT:
		set_mod_args(args, 25000, 0, 1, BIT_ULL(CGX_MODE_25G_CR));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_25000baseKR_Full_BIT:
		set_mod_args(args, 25000, 0, 1, BIT_ULL(CGX_MODE_25G_KR));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT:
		set_mod_args(args, 40000, 0, 0, BIT_ULL(CGX_MODE_40G_C2C));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT:
		set_mod_args(args, 40000, 0, 0, BIT_ULL(CGX_MODE_40G_C2M));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT:
		set_mod_args(args, 40000, 0, 1, BIT_ULL(CGX_MODE_40G_CR4));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT:
		set_mod_args(args, 40000, 0, 1, BIT_ULL(CGX_MODE_40G_KR4));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_50000baseSR_Full_BIT:
		set_mod_args(args, 50000, 0, 0, BIT_ULL(CGX_MODE_50G_C2C));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT:
		set_mod_args(args, 50000, 0, 0, BIT_ULL(CGX_MODE_50G_C2M));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_50000baseCR_Full_BIT:
		set_mod_args(args, 50000, 0, 1, BIT_ULL(CGX_MODE_50G_CR));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_50000baseKR_Full_BIT:
		set_mod_args(args, 50000, 0, 1, BIT_ULL(CGX_MODE_50G_KR));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT:
		set_mod_args(args, 100000, 0, 0, BIT_ULL(CGX_MODE_100G_C2C));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT:
		set_mod_args(args, 100000, 0, 0, BIT_ULL(CGX_MODE_100G_C2M));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT:
		set_mod_args(args, 100000, 0, 1, BIT_ULL(CGX_MODE_100G_CR4));
		अवरोध;
	हाल  ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT:
		set_mod_args(args, 100000, 0, 1, BIT_ULL(CGX_MODE_100G_KR4));
		अवरोध;
	शेष:
		set_mod_args(args, 0, 1, 0, BIT_ULL(CGX_MODE_MAX));
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम link_status_user_क्रमmat(u64 lstat,
					   काष्ठा cgx_link_user_info *linfo,
					   काष्ठा cgx *cgx, u8 lmac_id)
अणु
	स्थिर अक्षर *lmac_string;

	linfo->link_up = FIELD_GET(RESP_LINKSTAT_UP, lstat);
	linfo->full_duplex = FIELD_GET(RESP_LINKSTAT_FDUPLEX, lstat);
	linfo->speed = cgx_speed_mbps[FIELD_GET(RESP_LINKSTAT_SPEED, lstat)];
	linfo->an = FIELD_GET(RESP_LINKSTAT_AN, lstat);
	linfo->fec = FIELD_GET(RESP_LINKSTAT_FEC, lstat);
	linfo->lmac_type_id = cgx_get_lmac_type(cgx, lmac_id);
	lmac_string = cgx_lmactype_string[linfo->lmac_type_id];
	म_नकलन(linfo->lmac_type, lmac_string, LMACTYPE_STR_LEN - 1);
पूर्ण

/* Hardware event handlers */
अटल अंतरभूत व्योम cgx_link_change_handler(u64 lstat,
					   काष्ठा lmac *lmac)
अणु
	काष्ठा cgx_link_user_info *linfo;
	काष्ठा cgx *cgx = lmac->cgx;
	काष्ठा cgx_link_event event;
	काष्ठा device *dev;
	पूर्णांक err_type;

	dev = &cgx->pdev->dev;

	link_status_user_क्रमmat(lstat, &event.link_uinfo, cgx, lmac->lmac_id);
	err_type = FIELD_GET(RESP_LINKSTAT_ERRTYPE, lstat);

	event.cgx_id = cgx->cgx_id;
	event.lmac_id = lmac->lmac_id;

	/* update the local copy of link status */
	lmac->link_info = event.link_uinfo;
	linfo = &lmac->link_info;

	अगर (err_type == CGX_ERR_SPEED_CHANGE_INVALID)
		वापस;

	/* Ensure callback करोesn't get unरेजिस्टरed until we finish it */
	spin_lock(&lmac->event_cb_lock);

	अगर (!lmac->event_cb.notअगरy_link_chg) अणु
		dev_dbg(dev, "cgx port %d:%d Link change handler null",
			cgx->cgx_id, lmac->lmac_id);
		अगर (err_type != CGX_ERR_NONE) अणु
			dev_err(dev, "cgx port %d:%d Link error %d\n",
				cgx->cgx_id, lmac->lmac_id, err_type);
		पूर्ण
		dev_info(dev, "cgx port %d:%d Link is %s %d Mbps\n",
			 cgx->cgx_id, lmac->lmac_id,
			 linfo->link_up ? "UP" : "DOWN", linfo->speed);
		जाओ err;
	पूर्ण

	अगर (lmac->event_cb.notअगरy_link_chg(&event, lmac->event_cb.data))
		dev_err(dev, "event notification failure\n");
err:
	spin_unlock(&lmac->event_cb_lock);
पूर्ण

अटल अंतरभूत bool cgx_cmdresp_is_linkevent(u64 event)
अणु
	u8 id;

	id = FIELD_GET(EVTREG_ID, event);
	अगर (id == CGX_CMD_LINK_BRING_UP ||
	    id == CGX_CMD_LINK_BRING_DOWN ||
	    id == CGX_CMD_MODE_CHANGE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत bool cgx_event_is_linkevent(u64 event)
अणु
	अगर (FIELD_GET(EVTREG_ID, event) == CGX_EVT_LINK_CHANGE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल irqवापस_t cgx_fwi_event_handler(पूर्णांक irq, व्योम *data)
अणु
	u64 event, offset, clear_bit;
	काष्ठा lmac *lmac = data;
	काष्ठा cgx *cgx;

	cgx = lmac->cgx;

	/* Clear SW_INT क्रम RPM and CMR_INT क्रम CGX */
	offset     = cgx->mac_ops->पूर्णांक_रेजिस्टर;
	clear_bit  = cgx->mac_ops->पूर्णांक_ena_bit;

	event = cgx_पढ़ो(cgx, lmac->lmac_id, CGX_EVENT_REG);

	अगर (!FIELD_GET(EVTREG_ACK, event))
		वापस IRQ_NONE;

	चयन (FIELD_GET(EVTREG_EVT_TYPE, event)) अणु
	हाल CGX_EVT_CMD_RESP:
		/* Copy the response. Since only one command is active at a
		 * समय, there is no way a response can get overwritten
		 */
		lmac->resp = event;
		/* Ensure response is updated beक्रमe thपढ़ो context starts */
		smp_wmb();

		/* There wont be separate events क्रम link change initiated from
		 * software; Hence report the command responses as events
		 */
		अगर (cgx_cmdresp_is_linkevent(event))
			cgx_link_change_handler(event, lmac);

		/* Release thपढ़ो रुकोing क्रम completion  */
		lmac->cmd_pend = false;
		wake_up_पूर्णांकerruptible(&lmac->wq_cmd_cmplt);
		अवरोध;
	हाल CGX_EVT_ASYNC:
		अगर (cgx_event_is_linkevent(event))
			cgx_link_change_handler(event, lmac);
		अवरोध;
	पूर्ण

	/* Any new event or command response will be posted by firmware
	 * only after the current status is acked.
	 * Ack the पूर्णांकerrupt रेजिस्टर as well.
	 */
	cgx_ग_लिखो(lmac->cgx, lmac->lmac_id, CGX_EVENT_REG, 0);
	cgx_ग_लिखो(lmac->cgx, lmac->lmac_id, offset, clear_bit);

	वापस IRQ_HANDLED;
पूर्ण

/* APIs क्रम PHY management using CGX firmware पूर्णांकerface */

/* callback registration क्रम hardware events like link change */
पूर्णांक cgx_lmac_evh_रेजिस्टर(काष्ठा cgx_event_cb *cb, व्योम *cgxd, पूर्णांक lmac_id)
अणु
	काष्ठा cgx *cgx = cgxd;
	काष्ठा lmac *lmac;

	lmac = lmac_pdata(lmac_id, cgx);
	अगर (!lmac)
		वापस -ENODEV;

	lmac->event_cb = *cb;

	वापस 0;
पूर्ण

पूर्णांक cgx_lmac_evh_unरेजिस्टर(व्योम *cgxd, पूर्णांक lmac_id)
अणु
	काष्ठा lmac *lmac;
	अचिन्हित दीर्घ flags;
	काष्ठा cgx *cgx = cgxd;

	lmac = lmac_pdata(lmac_id, cgx);
	अगर (!lmac)
		वापस -ENODEV;

	spin_lock_irqsave(&lmac->event_cb_lock, flags);
	lmac->event_cb.notअगरy_link_chg = शून्य;
	lmac->event_cb.data = शून्य;
	spin_unlock_irqrestore(&lmac->event_cb_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cgx_get_fwdata_base(u64 *base)
अणु
	u64 req = 0, resp;
	काष्ठा cgx *cgx;
	पूर्णांक first_lmac;
	पूर्णांक err;

	cgx = list_first_entry_or_null(&cgx_list, काष्ठा cgx, cgx_list);
	अगर (!cgx)
		वापस -ENXIO;

	first_lmac = find_first_bit(&cgx->lmac_bmap, MAX_LMAC_PER_CGX);
	req = FIELD_SET(CMDREG_ID, CGX_CMD_GET_FWD_BASE, req);
	err = cgx_fwi_cmd_generic(req, &resp, cgx, first_lmac);
	अगर (!err)
		*base = FIELD_GET(RESP_FWD_BASE, resp);

	वापस err;
पूर्ण

पूर्णांक cgx_set_link_mode(व्योम *cgxd, काष्ठा cgx_set_link_mode_args args,
		      पूर्णांक cgx_id, पूर्णांक lmac_id)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 req = 0, resp;

	अगर (!cgx)
		वापस -ENODEV;

	अगर (args.mode)
		otx2_map_ethtool_link_modes(args.mode, &args);
	अगर (!args.speed && args.duplex && !args.an)
		वापस -EINVAL;

	req = FIELD_SET(CMDREG_ID, CGX_CMD_MODE_CHANGE, req);
	req = FIELD_SET(CMDMODECHANGE_SPEED,
			cgx_link_usertable_index_map(args.speed), req);
	req = FIELD_SET(CMDMODECHANGE_DUPLEX, args.duplex, req);
	req = FIELD_SET(CMDMODECHANGE_AN, args.an, req);
	req = FIELD_SET(CMDMODECHANGE_PORT, args.ports, req);
	req = FIELD_SET(CMDMODECHANGE_FLAGS, args.mode, req);

	वापस cgx_fwi_cmd_generic(req, &resp, cgx, lmac_id);
पूर्ण
पूर्णांक cgx_set_fec(u64 fec, पूर्णांक cgx_id, पूर्णांक lmac_id)
अणु
	u64 req = 0, resp;
	काष्ठा cgx *cgx;
	पूर्णांक err = 0;

	cgx = cgx_get_pdata(cgx_id);
	अगर (!cgx)
		वापस -ENXIO;

	req = FIELD_SET(CMDREG_ID, CGX_CMD_SET_FEC, req);
	req = FIELD_SET(CMDSETFEC, fec, req);
	err = cgx_fwi_cmd_generic(req, &resp, cgx, lmac_id);
	अगर (err)
		वापस err;

	cgx->lmac_idmap[lmac_id]->link_info.fec =
			FIELD_GET(RESP_LINKSTAT_FEC, resp);
	वापस cgx->lmac_idmap[lmac_id]->link_info.fec;
पूर्ण

पूर्णांक cgx_get_phy_fec_stats(व्योम *cgxd, पूर्णांक lmac_id)
अणु
	काष्ठा cgx *cgx = cgxd;
	u64 req = 0, resp;

	अगर (!cgx)
		वापस -ENODEV;

	req = FIELD_SET(CMDREG_ID, CGX_CMD_GET_PHY_FEC_STATS, req);
	वापस cgx_fwi_cmd_generic(req, &resp, cgx, lmac_id);
पूर्ण

अटल पूर्णांक cgx_fwi_link_change(काष्ठा cgx *cgx, पूर्णांक lmac_id, bool enable)
अणु
	u64 req = 0;
	u64 resp;

	अगर (enable)
		req = FIELD_SET(CMDREG_ID, CGX_CMD_LINK_BRING_UP, req);
	अन्यथा
		req = FIELD_SET(CMDREG_ID, CGX_CMD_LINK_BRING_DOWN, req);

	वापस cgx_fwi_cmd_generic(req, &resp, cgx, lmac_id);
पूर्ण

अटल अंतरभूत पूर्णांक cgx_fwi_पढ़ो_version(u64 *resp, काष्ठा cgx *cgx)
अणु
	पूर्णांक first_lmac = find_first_bit(&cgx->lmac_bmap, MAX_LMAC_PER_CGX);
	u64 req = 0;

	req = FIELD_SET(CMDREG_ID, CGX_CMD_GET_FW_VER, req);
	वापस cgx_fwi_cmd_generic(req, resp, cgx, first_lmac);
पूर्ण

अटल पूर्णांक cgx_lmac_verअगरy_fwi_version(काष्ठा cgx *cgx)
अणु
	काष्ठा device *dev = &cgx->pdev->dev;
	पूर्णांक major_ver, minor_ver;
	u64 resp;
	पूर्णांक err;

	अगर (!cgx->lmac_count)
		वापस 0;

	err = cgx_fwi_पढ़ो_version(&resp, cgx);
	अगर (err)
		वापस err;

	major_ver = FIELD_GET(RESP_MAJOR_VER, resp);
	minor_ver = FIELD_GET(RESP_MINOR_VER, resp);
	dev_dbg(dev, "Firmware command interface version = %d.%d\n",
		major_ver, minor_ver);
	अगर (major_ver != CGX_FIRMWARE_MAJOR_VER)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम cgx_lmac_linkup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cgx *cgx = container_of(work, काष्ठा cgx, cgx_cmd_work);
	काष्ठा device *dev = &cgx->pdev->dev;
	पूर्णांक i, err;

	/* Do Link up क्रम all the enabled lmacs */
	क्रम_each_set_bit(i, &cgx->lmac_bmap, MAX_LMAC_PER_CGX) अणु
		err = cgx_fwi_link_change(cgx, i, true);
		अगर (err)
			dev_info(dev, "cgx port %d:%d Link up command failed\n",
				 cgx->cgx_id, i);
	पूर्ण
पूर्ण

पूर्णांक cgx_lmac_linkup_start(व्योम *cgxd)
अणु
	काष्ठा cgx *cgx = cgxd;

	अगर (!cgx)
		वापस -ENODEV;

	queue_work(cgx->cgx_cmd_workq, &cgx->cgx_cmd_work);

	वापस 0;
पूर्ण

अटल व्योम cgx_lmac_get_fअगरolen(काष्ठा cgx *cgx)
अणु
	u64 cfg;

	cfg = cgx_पढ़ो(cgx, 0, CGX_CONST);
	cgx->mac_ops->fअगरo_len = FIELD_GET(CGX_CONST_RXFIFO_SIZE, cfg);
पूर्ण

अटल पूर्णांक cgx_configure_पूर्णांकerrupt(काष्ठा cgx *cgx, काष्ठा lmac *lmac,
				   पूर्णांक cnt, bool req_मुक्त)
अणु
	काष्ठा mac_ops *mac_ops = cgx->mac_ops;
	u64 offset, ena_bit;
	अचिन्हित पूर्णांक irq;
	पूर्णांक err;

	irq      = pci_irq_vector(cgx->pdev, mac_ops->lmac_fwi +
				  cnt * mac_ops->irq_offset);
	offset   = mac_ops->पूर्णांक_set_reg;
	ena_bit  = mac_ops->पूर्णांक_ena_bit;

	अगर (req_मुक्त) अणु
		मुक्त_irq(irq, lmac);
		वापस 0;
	पूर्ण

	err = request_irq(irq, cgx_fwi_event_handler, 0, lmac->name, lmac);
	अगर (err)
		वापस err;

	/* Enable पूर्णांकerrupt */
	cgx_ग_लिखो(cgx, lmac->lmac_id, offset, ena_bit);
	वापस 0;
पूर्ण

पूर्णांक cgx_get_nr_lmacs(व्योम *cgxd)
अणु
	काष्ठा cgx *cgx = cgxd;

	वापस cgx_पढ़ो(cgx, 0, CGXX_CMRX_RX_LMACS) & 0x7ULL;
पूर्ण

u8 cgx_get_lmacid(व्योम *cgxd, u8 lmac_index)
अणु
	काष्ठा cgx *cgx = cgxd;

	वापस cgx->lmac_idmap[lmac_index]->lmac_id;
पूर्ण

अचिन्हित दीर्घ cgx_get_lmac_bmap(व्योम *cgxd)
अणु
	काष्ठा cgx *cgx = cgxd;

	वापस cgx->lmac_bmap;
पूर्ण

अटल पूर्णांक cgx_lmac_init(काष्ठा cgx *cgx)
अणु
	काष्ठा lmac *lmac;
	u64 lmac_list;
	पूर्णांक i, err;

	cgx_lmac_get_fअगरolen(cgx);

	cgx->lmac_count = cgx->mac_ops->get_nr_lmacs(cgx);
	/* lmac_list specअगरies which lmacs are enabled
	 * when bit n is set to 1, LMAC[n] is enabled
	 */
	अगर (cgx->mac_ops->non_contiguous_serdes_lane)
		lmac_list = cgx_पढ़ो(cgx, 0, CGXX_CMRX_RX_LMACS) & 0xFULL;

	अगर (cgx->lmac_count > MAX_LMAC_PER_CGX)
		cgx->lmac_count = MAX_LMAC_PER_CGX;

	क्रम (i = 0; i < cgx->lmac_count; i++) अणु
		lmac = kzalloc(माप(काष्ठा lmac), GFP_KERNEL);
		अगर (!lmac)
			वापस -ENOMEM;
		lmac->name = kसुस्मृति(1, माप("cgx_fwi_xxx_yyy"), GFP_KERNEL);
		अगर (!lmac->name) अणु
			err = -ENOMEM;
			जाओ err_lmac_मुक्त;
		पूर्ण
		प्र_लिखो(lmac->name, "cgx_fwi_%d_%d", cgx->cgx_id, i);
		अगर (cgx->mac_ops->non_contiguous_serdes_lane) अणु
			lmac->lmac_id = __ffs64(lmac_list);
			lmac_list   &= ~BIT_ULL(lmac->lmac_id);
		पूर्ण अन्यथा अणु
			lmac->lmac_id = i;
		पूर्ण

		lmac->cgx = cgx;
		init_रुकोqueue_head(&lmac->wq_cmd_cmplt);
		mutex_init(&lmac->cmd_lock);
		spin_lock_init(&lmac->event_cb_lock);
		err = cgx_configure_पूर्णांकerrupt(cgx, lmac, lmac->lmac_id, false);
		अगर (err)
			जाओ err_irq;

		/* Add reference */
		cgx->lmac_idmap[lmac->lmac_id] = lmac;
		cgx->mac_ops->mac_छोड़ो_frm_config(cgx, lmac->lmac_id, true);
		set_bit(lmac->lmac_id, &cgx->lmac_bmap);
	पूर्ण

	वापस cgx_lmac_verअगरy_fwi_version(cgx);

err_irq:
	kमुक्त(lmac->name);
err_lmac_मुक्त:
	kमुक्त(lmac);
	वापस err;
पूर्ण

अटल पूर्णांक cgx_lmac_निकास(काष्ठा cgx *cgx)
अणु
	काष्ठा lmac *lmac;
	पूर्णांक i;

	अगर (cgx->cgx_cmd_workq) अणु
		flush_workqueue(cgx->cgx_cmd_workq);
		destroy_workqueue(cgx->cgx_cmd_workq);
		cgx->cgx_cmd_workq = शून्य;
	पूर्ण

	/* Free all lmac related resources */
	क्रम_each_set_bit(i, &cgx->lmac_bmap, MAX_LMAC_PER_CGX) अणु
		lmac = cgx->lmac_idmap[i];
		अगर (!lmac)
			जारी;
		cgx->mac_ops->mac_छोड़ो_frm_config(cgx, lmac->lmac_id, false);
		cgx_configure_पूर्णांकerrupt(cgx, lmac, lmac->lmac_id, true);
		kमुक्त(lmac->name);
		kमुक्त(lmac);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cgx_populate_features(काष्ठा cgx *cgx)
अणु
	अगर (is_dev_rpm(cgx))
		cgx->hw_features =  (RVU_MAC_RPM | RVU_LMAC_FEAT_FC);
	अन्यथा
		cgx->hw_features = (RVU_LMAC_FEAT_FC | RVU_LMAC_FEAT_PTP);
पूर्ण

अटल काष्ठा mac_ops	cgx_mac_ops    = अणु
	.name		=       "cgx",
	.csr_offset	=       0,
	.lmac_offset    =       18,
	.पूर्णांक_रेजिस्टर	=       CGXX_CMRX_INT,
	.पूर्णांक_set_reg	=       CGXX_CMRX_INT_ENA_W1S,
	.irq_offset	=       9,
	.पूर्णांक_ena_bit    =       FW_CGX_INT,
	.lmac_fwi	=	CGX_LMAC_FWI,
	.non_contiguous_serdes_lane = false,
	.rx_stats_cnt   =       9,
	.tx_stats_cnt   =       18,
	.get_nr_lmacs	=	cgx_get_nr_lmacs,
	.get_lmac_type  =       cgx_get_lmac_type,
	.mac_lmac_पूर्णांकl_lbk =    cgx_lmac_पूर्णांकernal_loopback,
	.mac_get_rx_stats  =	cgx_get_rx_stats,
	.mac_get_tx_stats  =	cgx_get_tx_stats,
	.mac_enadis_rx_छोड़ो_fwding =	cgx_lmac_enadis_rx_छोड़ो_fwding,
	.mac_get_छोड़ो_frm_status =	cgx_lmac_get_छोड़ो_frm_status,
	.mac_enadis_छोड़ो_frm =		cgx_lmac_enadis_छोड़ो_frm,
	.mac_छोड़ो_frm_config =		cgx_lmac_छोड़ो_frm_config,
पूर्ण;

अटल पूर्णांक cgx_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cgx *cgx;
	पूर्णांक err, nvec;

	cgx = devm_kzalloc(dev, माप(*cgx), GFP_KERNEL);
	अगर (!cgx)
		वापस -ENOMEM;
	cgx->pdev = pdev;

	pci_set_drvdata(pdev, cgx);

	/* Use mac_ops to get MAC specअगरic features */
	अगर (pdev->device == PCI_DEVID_CN10K_RPM)
		cgx->mac_ops = rpm_get_mac_ops();
	अन्यथा
		cgx->mac_ops = &cgx_mac_ops;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, शून्य);
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ err_disable_device;
	पूर्ण

	/* MAP configuration रेजिस्टरs */
	cgx->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!cgx->reg_base) अणु
		dev_err(dev, "CGX: Cannot map CSR memory space, aborting\n");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	nvec = pci_msix_vec_count(cgx->pdev);
	err = pci_alloc_irq_vectors(pdev, nvec, nvec, PCI_IRQ_MSIX);
	अगर (err < 0 || err != nvec) अणु
		dev_err(dev, "Request for %d msix vectors failed, err %d\n",
			nvec, err);
		जाओ err_release_regions;
	पूर्ण

	cgx->cgx_id = (pci_resource_start(pdev, PCI_CFG_REG_BAR_NUM) >> 24)
		& CGX_ID_MASK;

	/* init wq क्रम processing linkup requests */
	INIT_WORK(&cgx->cgx_cmd_work, cgx_lmac_linkup_work);
	cgx->cgx_cmd_workq = alloc_workqueue("cgx_cmd_workq", 0, 0);
	अगर (!cgx->cgx_cmd_workq) अणु
		dev_err(dev, "alloc workqueue failed for cgx cmd");
		err = -ENOMEM;
		जाओ err_मुक्त_irq_vectors;
	पूर्ण

	list_add(&cgx->cgx_list, &cgx_list);


	cgx_populate_features(cgx);

	mutex_init(&cgx->lock);

	err = cgx_lmac_init(cgx);
	अगर (err)
		जाओ err_release_lmac;

	वापस 0;

err_release_lmac:
	cgx_lmac_निकास(cgx);
	list_del(&cgx->cgx_list);
err_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम cgx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cgx *cgx = pci_get_drvdata(pdev);

	अगर (cgx) अणु
		cgx_lmac_निकास(cgx);
		list_del(&cgx->cgx_list);
	पूर्ण
	pci_मुक्त_irq_vectors(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

काष्ठा pci_driver cgx_driver = अणु
	.name = DRV_NAME,
	.id_table = cgx_id_table,
	.probe = cgx_probe,
	.हटाओ = cgx_हटाओ,
पूर्ण;
