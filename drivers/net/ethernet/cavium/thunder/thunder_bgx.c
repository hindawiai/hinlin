<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>

#समावेश "nic_reg.h"
#समावेश "nic.h"
#समावेश "thunder_bgx.h"

#घोषणा DRV_NAME	"thunder_bgx"
#घोषणा DRV_VERSION	"1.0"

/* RX_DMAC_CTL configuration */
क्रमागत MCAST_MODE अणु
		MCAST_MODE_REJECT = 0x0,
		MCAST_MODE_ACCEPT = 0x1,
		MCAST_MODE_CAM_FILTER = 0x2,
		RSVD = 0x3
पूर्ण;

#घोषणा BCAST_ACCEPT      BIT(0)
#घोषणा CAM_ACCEPT        BIT(3)
#घोषणा MCAST_MODE_MASK   0x3
#घोषणा BGX_MCAST_MODE(x) (x << 1)

काष्ठा dmac_map अणु
	u64                     vf_map;
	u64                     dmac;
पूर्ण;

काष्ठा lmac अणु
	काष्ठा bgx		*bgx;
	/* actual number of DMACs configured */
	u8			dmacs_cfg;
	/* overal number of possible DMACs could be configured per LMAC */
	u8                      dmacs_count;
	काष्ठा dmac_map         *dmacs; /* DMAC:VFs tracking filter array */
	u8			mac[ETH_ALEN];
	u8                      lmac_type;
	u8                      lane_to_sds;
	bool                    use_training;
	bool                    स्वतःneg;
	bool			link_up;
	पूर्णांक			lmacid; /* ID within BGX */
	पूर्णांक			lmacid_bd; /* ID on board */
	काष्ठा net_device       netdev;
	काष्ठा phy_device       *phydev;
	अचिन्हित पूर्णांक            last_duplex;
	अचिन्हित पूर्णांक            last_link;
	अचिन्हित पूर्णांक            last_speed;
	bool			is_sgmii;
	काष्ठा delayed_work	dwork;
	काष्ठा workqueue_काष्ठा *check_link;
पूर्ण;

काष्ठा bgx अणु
	u8			bgx_id;
	काष्ठा	lmac		lmac[MAX_LMAC_PER_BGX];
	u8			lmac_count;
	u8			max_lmac;
	u8                      acpi_lmac_idx;
	व्योम __iomem		*reg_base;
	काष्ठा pci_dev		*pdev;
	bool                    is_dlm;
	bool                    is_rgx;
पूर्ण;

अटल काष्ठा bgx *bgx_vnic[MAX_BGX_THUNDER];
अटल पूर्णांक lmac_count; /* Total no of LMACs in प्रणाली */

अटल पूर्णांक bgx_xaui_check_link(काष्ठा lmac *lmac);

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id bgx_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_BGX) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_RGX) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_AUTHOR("Cavium Inc");
MODULE_DESCRIPTION("Cavium Thunder BGX/MAC Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, bgx_id_table);

/* The Cavium ThunderX network controller can *only* be found in SoCs
 * containing the ThunderX ARM64 CPU implementation.  All accesses to the device
 * रेजिस्टरs on this platक्रमm are implicitly strongly ordered with respect
 * to memory accesses. So ग_लिखोq_relaxed() and पढ़ोq_relaxed() are safe to use
 * with no memory barriers in this driver.  The पढ़ोq()/ग_लिखोq() functions add
 * explicit ordering operation which in this हाल are redundant, and only
 * add overhead.
 */

/* Register पढ़ो/ग_लिखो APIs */
अटल u64 bgx_reg_पढ़ो(काष्ठा bgx *bgx, u8 lmac, u64 offset)
अणु
	व्योम __iomem *addr = bgx->reg_base + ((u32)lmac << 20) + offset;

	वापस पढ़ोq_relaxed(addr);
पूर्ण

अटल व्योम bgx_reg_ग_लिखो(काष्ठा bgx *bgx, u8 lmac, u64 offset, u64 val)
अणु
	व्योम __iomem *addr = bgx->reg_base + ((u32)lmac << 20) + offset;

	ग_लिखोq_relaxed(val, addr);
पूर्ण

अटल व्योम bgx_reg_modअगरy(काष्ठा bgx *bgx, u8 lmac, u64 offset, u64 val)
अणु
	व्योम __iomem *addr = bgx->reg_base + ((u32)lmac << 20) + offset;

	ग_लिखोq_relaxed(val | पढ़ोq_relaxed(addr), addr);
पूर्ण

अटल पूर्णांक bgx_poll_reg(काष्ठा bgx *bgx, u8 lmac, u64 reg, u64 mask, bool zero)
अणु
	पूर्णांक समयout = 100;
	u64 reg_val;

	जबतक (समयout) अणु
		reg_val = bgx_reg_पढ़ो(bgx, lmac, reg);
		अगर (zero && !(reg_val & mask))
			वापस 0;
		अगर (!zero && (reg_val & mask))
			वापस 0;
		usleep_range(1000, 2000);
		समयout--;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक max_bgx_per_node;
अटल व्योम set_max_bgx_per_node(काष्ठा pci_dev *pdev)
अणु
	u16 sdevid;

	अगर (max_bgx_per_node)
		वापस;

	pci_पढ़ो_config_word(pdev, PCI_SUBSYSTEM_ID, &sdevid);
	चयन (sdevid) अणु
	हाल PCI_SUBSYS_DEVID_81XX_BGX:
	हाल PCI_SUBSYS_DEVID_81XX_RGX:
		max_bgx_per_node = MAX_BGX_PER_CN81XX;
		अवरोध;
	हाल PCI_SUBSYS_DEVID_83XX_BGX:
		max_bgx_per_node = MAX_BGX_PER_CN83XX;
		अवरोध;
	हाल PCI_SUBSYS_DEVID_88XX_BGX:
	शेष:
		max_bgx_per_node = MAX_BGX_PER_CN88XX;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा bgx *get_bgx(पूर्णांक node, पूर्णांक bgx_idx)
अणु
	पूर्णांक idx = (node * max_bgx_per_node) + bgx_idx;

	वापस bgx_vnic[idx];
पूर्ण

/* Return number of BGX present in HW */
अचिन्हित bgx_get_map(पूर्णांक node)
अणु
	पूर्णांक i;
	अचिन्हित map = 0;

	क्रम (i = 0; i < max_bgx_per_node; i++) अणु
		अगर (bgx_vnic[(node * max_bgx_per_node) + i])
			map |= (1 << i);
	पूर्ण

	वापस map;
पूर्ण
EXPORT_SYMBOL(bgx_get_map);

/* Return number of LMAC configured क्रम this BGX */
पूर्णांक bgx_get_lmac_count(पूर्णांक node, पूर्णांक bgx_idx)
अणु
	काष्ठा bgx *bgx;

	bgx = get_bgx(node, bgx_idx);
	अगर (bgx)
		वापस bgx->lmac_count;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(bgx_get_lmac_count);

/* Returns the current link status of LMAC */
व्योम bgx_get_lmac_link_state(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, व्योम *status)
अणु
	काष्ठा bgx_link_status *link = (काष्ठा bgx_link_status *)status;
	काष्ठा bgx *bgx;
	काष्ठा lmac *lmac;

	bgx = get_bgx(node, bgx_idx);
	अगर (!bgx)
		वापस;

	lmac = &bgx->lmac[lmacid];
	link->mac_type = lmac->lmac_type;
	link->link_up = lmac->link_up;
	link->duplex = lmac->last_duplex;
	link->speed = lmac->last_speed;
पूर्ण
EXPORT_SYMBOL(bgx_get_lmac_link_state);

स्थिर u8 *bgx_get_lmac_mac(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);

	अगर (bgx)
		वापस bgx->lmac[lmacid].mac;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(bgx_get_lmac_mac);

व्योम bgx_set_lmac_mac(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, स्थिर u8 *mac)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);

	अगर (!bgx)
		वापस;

	ether_addr_copy(bgx->lmac[lmacid].mac, mac);
पूर्ण
EXPORT_SYMBOL(bgx_set_lmac_mac);

अटल व्योम bgx_flush_dmac_cam_filter(काष्ठा bgx *bgx, पूर्णांक lmacid)
अणु
	काष्ठा lmac *lmac = शून्य;
	u8  idx = 0;

	lmac = &bgx->lmac[lmacid];
	/* reset CAM filters */
	क्रम (idx = 0; idx < lmac->dmacs_count; idx++)
		bgx_reg_ग_लिखो(bgx, 0, BGX_CMR_RX_DMACX_CAM +
			      ((lmacid * lmac->dmacs_count) + idx) *
			      माप(u64), 0);
पूर्ण

अटल व्योम bgx_lmac_हटाओ_filters(काष्ठा lmac *lmac, u8 vf_id)
अणु
	पूर्णांक i = 0;

	अगर (!lmac)
		वापस;

	/* We've got reset filters request from some of attached VF, जबतक the
	 * others might want to keep their configuration. So in this हाल lets
	 * iterate over all of configured filters and decrease number of
	 * referencies. अगर some addresses get zero refs हटाओ them from list
	 */
	क्रम (i = lmac->dmacs_cfg - 1; i >= 0; i--) अणु
		lmac->dmacs[i].vf_map &= ~BIT_ULL(vf_id);
		अगर (!lmac->dmacs[i].vf_map) अणु
			lmac->dmacs_cfg--;
			lmac->dmacs[i].dmac = 0;
			lmac->dmacs[i].vf_map = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bgx_lmac_save_filter(काष्ठा lmac *lmac, u64 dmac, u8 vf_id)
अणु
	u8 i = 0;

	अगर (!lmac)
		वापस -1;

	/* At the same समय we could have several VFs 'attached' to some
	 * particular LMAC, and each VF is represented as network पूर्णांकerface
	 * क्रम kernel. So from user perspective it should be possible to
	 * manipulate with its' (VF) receive modes. However from PF
	 * driver perspective we need to keep track of filter configurations
	 * क्रम dअगरferent VFs to prevent filter values dupes
	 */
	क्रम (i = 0; i < lmac->dmacs_cfg; i++) अणु
		अगर (lmac->dmacs[i].dmac == dmac) अणु
			lmac->dmacs[i].vf_map |= BIT_ULL(vf_id);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (!(lmac->dmacs_cfg < lmac->dmacs_count))
		वापस -1;

	/* keep it क्रम further tracking */
	lmac->dmacs[lmac->dmacs_cfg].dmac = dmac;
	lmac->dmacs[lmac->dmacs_cfg].vf_map = BIT_ULL(vf_id);
	lmac->dmacs_cfg++;
	वापस 0;
पूर्ण

अटल पूर्णांक bgx_set_dmac_cam_filter_mac(काष्ठा bgx *bgx, पूर्णांक lmacid,
				       u64 cam_dmac, u8 idx)
अणु
	काष्ठा lmac *lmac = शून्य;
	u64 cfg = 0;

	/* skip zero addresses as meaningless */
	अगर (!cam_dmac || !bgx)
		वापस -1;

	lmac = &bgx->lmac[lmacid];

	/* configure DCAM filtering क्रम designated LMAC */
	cfg = RX_DMACX_CAM_LMACID(lmacid & LMAC_ID_MASK) |
		RX_DMACX_CAM_EN | cam_dmac;
	bgx_reg_ग_लिखो(bgx, 0, BGX_CMR_RX_DMACX_CAM +
		      ((lmacid * lmac->dmacs_count) + idx) * माप(u64), cfg);
	वापस 0;
पूर्ण

व्योम bgx_set_dmac_cam_filter(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid,
			     u64 cam_dmac, u8 vf_id)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);
	काष्ठा lmac *lmac = शून्य;

	अगर (!bgx)
		वापस;

	lmac = &bgx->lmac[lmacid];

	अगर (!cam_dmac)
		cam_dmac = ether_addr_to_u64(lmac->mac);

	/* since we might have several VFs attached to particular LMAC
	 * and kernel could call mcast config क्रम each of them with the
	 * same MAC, check अगर requested MAC is alपढ़ोy in filtering list and
	 * updare/prepare list of MACs to be applied later to HW filters
	 */
	bgx_lmac_save_filter(lmac, cam_dmac, vf_id);
पूर्ण
EXPORT_SYMBOL(bgx_set_dmac_cam_filter);

व्योम bgx_set_xcast_mode(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, u8 mode)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);
	काष्ठा lmac *lmac = शून्य;
	u64 cfg = 0;
	u8 i = 0;

	अगर (!bgx)
		वापस;

	lmac = &bgx->lmac[lmacid];

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_CMRX_RX_DMAC_CTL);
	अगर (mode & BGX_XCAST_BCAST_ACCEPT)
		cfg |= BCAST_ACCEPT;
	अन्यथा
		cfg &= ~BCAST_ACCEPT;

	/* disable all MCASTs and DMAC filtering */
	cfg &= ~(CAM_ACCEPT | BGX_MCAST_MODE(MCAST_MODE_MASK));

	/* check requested bits and set filtergin mode appropriately */
	अगर (mode & (BGX_XCAST_MCAST_ACCEPT)) अणु
		cfg |= (BGX_MCAST_MODE(MCAST_MODE_ACCEPT));
	पूर्ण अन्यथा अगर (mode & BGX_XCAST_MCAST_FILTER) अणु
		cfg |= (BGX_MCAST_MODE(MCAST_MODE_CAM_FILTER) | CAM_ACCEPT);
		क्रम (i = 0; i < lmac->dmacs_cfg; i++)
			bgx_set_dmac_cam_filter_mac(bgx, lmacid,
						    lmac->dmacs[i].dmac, i);
	पूर्ण
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_RX_DMAC_CTL, cfg);
पूर्ण
EXPORT_SYMBOL(bgx_set_xcast_mode);

व्योम bgx_reset_xcast_mode(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, u8 vf_id)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);

	अगर (!bgx)
		वापस;

	bgx_lmac_हटाओ_filters(&bgx->lmac[lmacid], vf_id);
	bgx_flush_dmac_cam_filter(bgx, lmacid);
	bgx_set_xcast_mode(node, bgx_idx, lmacid,
			   (BGX_XCAST_BCAST_ACCEPT | BGX_XCAST_MCAST_ACCEPT));
पूर्ण
EXPORT_SYMBOL(bgx_reset_xcast_mode);

व्योम bgx_lmac_rx_tx_enable(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, bool enable)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);
	काष्ठा lmac *lmac;
	u64 cfg;

	अगर (!bgx)
		वापस;
	lmac = &bgx->lmac[lmacid];

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_CMRX_CFG);
	अगर (enable) अणु
		cfg |= CMR_PKT_RX_EN | CMR_PKT_TX_EN;

		/* enable TX FIFO Underflow पूर्णांकerrupt */
		bgx_reg_modअगरy(bgx, lmacid, BGX_GMP_GMI_TXX_INT_ENA_W1S,
			       GMI_TXX_INT_UNDFLW);
	पूर्ण अन्यथा अणु
		cfg &= ~(CMR_PKT_RX_EN | CMR_PKT_TX_EN);

		/* Disable TX FIFO Underflow पूर्णांकerrupt */
		bgx_reg_modअगरy(bgx, lmacid, BGX_GMP_GMI_TXX_INT_ENA_W1C,
			       GMI_TXX_INT_UNDFLW);
	पूर्ण
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_CFG, cfg);

	अगर (bgx->is_rgx)
		xcv_setup_link(enable ? lmac->link_up : 0, lmac->last_speed);
पूर्ण
EXPORT_SYMBOL(bgx_lmac_rx_tx_enable);

/* Enables or disables बारtamp insertion by BGX क्रम Rx packets */
व्योम bgx_config_बारtamping(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, bool enable)
अणु
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);
	काष्ठा lmac *lmac;
	u64 csr_offset, cfg;

	अगर (!bgx)
		वापस;

	lmac = &bgx->lmac[lmacid];

	अगर (lmac->lmac_type == BGX_MODE_SGMII ||
	    lmac->lmac_type == BGX_MODE_QSGMII ||
	    lmac->lmac_type == BGX_MODE_RGMII)
		csr_offset = BGX_GMP_GMI_RXX_FRM_CTL;
	अन्यथा
		csr_offset = BGX_SMUX_RX_FRM_CTL;

	cfg = bgx_reg_पढ़ो(bgx, lmacid, csr_offset);

	अगर (enable)
		cfg |= BGX_PKT_RX_PTP_EN;
	अन्यथा
		cfg &= ~BGX_PKT_RX_PTP_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, csr_offset, cfg);
पूर्ण
EXPORT_SYMBOL(bgx_config_बारtamping);

व्योम bgx_lmac_get_pfc(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, व्योम *छोड़ो)
अणु
	काष्ठा pfc *pfc = (काष्ठा pfc *)छोड़ो;
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);
	काष्ठा lmac *lmac;
	u64 cfg;

	अगर (!bgx)
		वापस;
	lmac = &bgx->lmac[lmacid];
	अगर (lmac->is_sgmii)
		वापस;

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_CBFC_CTL);
	pfc->fc_rx = cfg & RX_EN;
	pfc->fc_tx = cfg & TX_EN;
	pfc->स्वतःneg = 0;
पूर्ण
EXPORT_SYMBOL(bgx_lmac_get_pfc);

व्योम bgx_lmac_set_pfc(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, व्योम *छोड़ो)
अणु
	काष्ठा pfc *pfc = (काष्ठा pfc *)छोड़ो;
	काष्ठा bgx *bgx = get_bgx(node, bgx_idx);
	काष्ठा lmac *lmac;
	u64 cfg;

	अगर (!bgx)
		वापस;
	lmac = &bgx->lmac[lmacid];
	अगर (lmac->is_sgmii)
		वापस;

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_CBFC_CTL);
	cfg &= ~(RX_EN | TX_EN);
	cfg |= (pfc->fc_rx ? RX_EN : 0x00);
	cfg |= (pfc->fc_tx ? TX_EN : 0x00);
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_CBFC_CTL, cfg);
पूर्ण
EXPORT_SYMBOL(bgx_lmac_set_pfc);

अटल व्योम bgx_sgmii_change_link_state(काष्ठा lmac *lmac)
अणु
	काष्ठा bgx *bgx = lmac->bgx;
	u64 cmr_cfg;
	u64 port_cfg = 0;
	u64 misc_ctl = 0;
	bool tx_en, rx_en;

	cmr_cfg = bgx_reg_पढ़ो(bgx, lmac->lmacid, BGX_CMRX_CFG);
	tx_en = cmr_cfg & CMR_PKT_TX_EN;
	rx_en = cmr_cfg & CMR_PKT_RX_EN;
	cmr_cfg &= ~(CMR_PKT_RX_EN | CMR_PKT_TX_EN);
	bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_CMRX_CFG, cmr_cfg);

	/* Wait क्रम BGX RX to be idle */
	अगर (bgx_poll_reg(bgx, lmac->lmacid, BGX_GMP_GMI_PRTX_CFG,
			 GMI_PORT_CFG_RX_IDLE, false)) अणु
		dev_err(&bgx->pdev->dev, "BGX%d LMAC%d GMI RX not idle\n",
			bgx->bgx_id, lmac->lmacid);
		वापस;
	पूर्ण

	/* Wait क्रम BGX TX to be idle */
	अगर (bgx_poll_reg(bgx, lmac->lmacid, BGX_GMP_GMI_PRTX_CFG,
			 GMI_PORT_CFG_TX_IDLE, false)) अणु
		dev_err(&bgx->pdev->dev, "BGX%d LMAC%d GMI TX not idle\n",
			bgx->bgx_id, lmac->lmacid);
		वापस;
	पूर्ण

	port_cfg = bgx_reg_पढ़ो(bgx, lmac->lmacid, BGX_GMP_GMI_PRTX_CFG);
	misc_ctl = bgx_reg_पढ़ो(bgx, lmac->lmacid, BGX_GMP_PCS_MISCX_CTL);

	अगर (lmac->link_up) अणु
		misc_ctl &= ~PCS_MISC_CTL_GMX_ENO;
		port_cfg &= ~GMI_PORT_CFG_DUPLEX;
		port_cfg |=  (lmac->last_duplex << 2);
	पूर्ण अन्यथा अणु
		misc_ctl |= PCS_MISC_CTL_GMX_ENO;
	पूर्ण

	चयन (lmac->last_speed) अणु
	हाल 10:
		port_cfg &= ~GMI_PORT_CFG_SPEED; /* speed 0 */
		port_cfg |= GMI_PORT_CFG_SPEED_MSB;  /* speed_msb 1 */
		port_cfg &= ~GMI_PORT_CFG_SLOT_TIME; /* slotसमय 0 */
		misc_ctl &= ~PCS_MISC_CTL_SAMP_PT_MASK;
		misc_ctl |= 50; /* samp_pt */
		bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_GMI_TXX_SLOT, 64);
		bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_GMI_TXX_BURST, 0);
		अवरोध;
	हाल 100:
		port_cfg &= ~GMI_PORT_CFG_SPEED; /* speed 0 */
		port_cfg &= ~GMI_PORT_CFG_SPEED_MSB; /* speed_msb 0 */
		port_cfg &= ~GMI_PORT_CFG_SLOT_TIME; /* slotसमय 0 */
		misc_ctl &= ~PCS_MISC_CTL_SAMP_PT_MASK;
		misc_ctl |= 5; /* samp_pt */
		bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_GMI_TXX_SLOT, 64);
		bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_GMI_TXX_BURST, 0);
		अवरोध;
	हाल 1000:
		port_cfg |= GMI_PORT_CFG_SPEED; /* speed 1 */
		port_cfg &= ~GMI_PORT_CFG_SPEED_MSB; /* speed_msb 0 */
		port_cfg |= GMI_PORT_CFG_SLOT_TIME; /* slotसमय 1 */
		misc_ctl &= ~PCS_MISC_CTL_SAMP_PT_MASK;
		misc_ctl |= 1; /* samp_pt */
		bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_GMI_TXX_SLOT, 512);
		अगर (lmac->last_duplex)
			bgx_reg_ग_लिखो(bgx, lmac->lmacid,
				      BGX_GMP_GMI_TXX_BURST, 0);
		अन्यथा
			bgx_reg_ग_लिखो(bgx, lmac->lmacid,
				      BGX_GMP_GMI_TXX_BURST, 8192);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_PCS_MISCX_CTL, misc_ctl);
	bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_GMP_GMI_PRTX_CFG, port_cfg);

	/* Restore CMR config settings */
	cmr_cfg |= (rx_en ? CMR_PKT_RX_EN : 0) | (tx_en ? CMR_PKT_TX_EN : 0);
	bgx_reg_ग_लिखो(bgx, lmac->lmacid, BGX_CMRX_CFG, cmr_cfg);

	अगर (bgx->is_rgx && (cmr_cfg & (CMR_PKT_RX_EN | CMR_PKT_TX_EN)))
		xcv_setup_link(lmac->link_up, lmac->last_speed);
पूर्ण

अटल व्योम bgx_lmac_handler(काष्ठा net_device *netdev)
अणु
	काष्ठा lmac *lmac = container_of(netdev, काष्ठा lmac, netdev);
	काष्ठा phy_device *phydev;
	पूर्णांक link_changed = 0;

	अगर (!lmac)
		वापस;

	phydev = lmac->phydev;

	अगर (!phydev->link && lmac->last_link)
		link_changed = -1;

	अगर (phydev->link &&
	    (lmac->last_duplex != phydev->duplex ||
	     lmac->last_link != phydev->link ||
	     lmac->last_speed != phydev->speed)) अणु
			link_changed = 1;
	पूर्ण

	lmac->last_link = phydev->link;
	lmac->last_speed = phydev->speed;
	lmac->last_duplex = phydev->duplex;

	अगर (!link_changed)
		वापस;

	अगर (link_changed > 0)
		lmac->link_up = true;
	अन्यथा
		lmac->link_up = false;

	अगर (lmac->is_sgmii)
		bgx_sgmii_change_link_state(lmac);
	अन्यथा
		bgx_xaui_check_link(lmac);
पूर्ण

u64 bgx_get_rx_stats(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmac, पूर्णांक idx)
अणु
	काष्ठा bgx *bgx;

	bgx = get_bgx(node, bgx_idx);
	अगर (!bgx)
		वापस 0;

	अगर (idx > 8)
		lmac = 0;
	वापस bgx_reg_पढ़ो(bgx, lmac, BGX_CMRX_RX_STAT0 + (idx * 8));
पूर्ण
EXPORT_SYMBOL(bgx_get_rx_stats);

u64 bgx_get_tx_stats(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmac, पूर्णांक idx)
अणु
	काष्ठा bgx *bgx;

	bgx = get_bgx(node, bgx_idx);
	अगर (!bgx)
		वापस 0;

	वापस bgx_reg_पढ़ो(bgx, lmac, BGX_CMRX_TX_STAT0 + (idx * 8));
पूर्ण
EXPORT_SYMBOL(bgx_get_tx_stats);

/* Configure BGX LMAC in पूर्णांकernal loopback mode */
व्योम bgx_lmac_पूर्णांकernal_loopback(पूर्णांक node, पूर्णांक bgx_idx,
				पूर्णांक lmac_idx, bool enable)
अणु
	काष्ठा bgx *bgx;
	काष्ठा lmac *lmac;
	u64    cfg;

	bgx = get_bgx(node, bgx_idx);
	अगर (!bgx)
		वापस;

	lmac = &bgx->lmac[lmac_idx];
	अगर (lmac->is_sgmii) अणु
		cfg = bgx_reg_पढ़ो(bgx, lmac_idx, BGX_GMP_PCS_MRX_CTL);
		अगर (enable)
			cfg |= PCS_MRX_CTL_LOOPBACK1;
		अन्यथा
			cfg &= ~PCS_MRX_CTL_LOOPBACK1;
		bgx_reg_ग_लिखो(bgx, lmac_idx, BGX_GMP_PCS_MRX_CTL, cfg);
	पूर्ण अन्यथा अणु
		cfg = bgx_reg_पढ़ो(bgx, lmac_idx, BGX_SPUX_CONTROL1);
		अगर (enable)
			cfg |= SPU_CTL_LOOPBACK;
		अन्यथा
			cfg &= ~SPU_CTL_LOOPBACK;
		bgx_reg_ग_लिखो(bgx, lmac_idx, BGX_SPUX_CONTROL1, cfg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(bgx_lmac_पूर्णांकernal_loopback);

अटल पूर्णांक bgx_lmac_sgmii_init(काष्ठा bgx *bgx, काष्ठा lmac *lmac)
अणु
	पूर्णांक lmacid = lmac->lmacid;
	u64 cfg;

	bgx_reg_modअगरy(bgx, lmacid, BGX_GMP_GMI_TXX_THRESH, 0x30);
	/* max packet size */
	bgx_reg_modअगरy(bgx, lmacid, BGX_GMP_GMI_RXX_JABBER, MAX_FRAME_SIZE);

	/* Disable frame alignment अगर using preamble */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_GMP_GMI_TXX_APPEND);
	अगर (cfg & 1)
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_GMP_GMI_TXX_SGMII_CTL, 0);

	/* Enable lmac */
	bgx_reg_modअगरy(bgx, lmacid, BGX_CMRX_CFG, CMR_EN);

	/* PCS reset */
	bgx_reg_modअगरy(bgx, lmacid, BGX_GMP_PCS_MRX_CTL, PCS_MRX_CTL_RESET);
	अगर (bgx_poll_reg(bgx, lmacid, BGX_GMP_PCS_MRX_CTL,
			 PCS_MRX_CTL_RESET, true)) अणु
		dev_err(&bgx->pdev->dev, "BGX PCS reset not completed\n");
		वापस -1;
	पूर्ण

	/* घातer करोwn, reset स्वतःneg, स्वतःneg enable */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_GMP_PCS_MRX_CTL);
	cfg &= ~PCS_MRX_CTL_PWR_DN;
	cfg |= PCS_MRX_CTL_RST_AN;
	अगर (lmac->phydev) अणु
		cfg |= PCS_MRX_CTL_AN_EN;
	पूर्ण अन्यथा अणु
		/* In scenarios where PHY driver is not present or it's a
		 * non-standard PHY, FW sets AN_EN to inक्रमm Linux driver
		 * to करो स्वतः-neg and link polling or not.
		 */
		अगर (cfg & PCS_MRX_CTL_AN_EN)
			lmac->स्वतःneg = true;
	पूर्ण
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_GMP_PCS_MRX_CTL, cfg);

	अगर (lmac->lmac_type == BGX_MODE_QSGMII) अणु
		/* Disable disparity check क्रम QSGMII */
		cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_GMP_PCS_MISCX_CTL);
		cfg &= ~PCS_MISC_CTL_DISP_EN;
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_GMP_PCS_MISCX_CTL, cfg);
		वापस 0;
	पूर्ण

	अगर ((lmac->lmac_type == BGX_MODE_SGMII) && lmac->phydev) अणु
		अगर (bgx_poll_reg(bgx, lmacid, BGX_GMP_PCS_MRX_STATUS,
				 PCS_MRX_STATUS_AN_CPT, false)) अणु
			dev_err(&bgx->pdev->dev, "BGX AN_CPT not completed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bgx_lmac_xaui_init(काष्ठा bgx *bgx, काष्ठा lmac *lmac)
अणु
	u64 cfg;
	पूर्णांक lmacid = lmac->lmacid;

	/* Reset SPU */
	bgx_reg_modअगरy(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_RESET);
	अगर (bgx_poll_reg(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_RESET, true)) अणु
		dev_err(&bgx->pdev->dev, "BGX SPU reset not completed\n");
		वापस -1;
	पूर्ण

	/* Disable LMAC */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_CFG, cfg);

	bgx_reg_modअगरy(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_LOW_POWER);
	/* Set पूर्णांकerleaved running disparity क्रम RXAUI */
	अगर (lmac->lmac_type == BGX_MODE_RXAUI)
		bgx_reg_modअगरy(bgx, lmacid, BGX_SPUX_MISC_CONTROL,
			       SPU_MISC_CTL_INTLV_RDISP);

	/* Clear receive packet disable */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_MISC_CONTROL);
	cfg &= ~SPU_MISC_CTL_RX_DIS;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_MISC_CONTROL, cfg);

	/* clear all पूर्णांकerrupts */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_RX_INT);
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_RX_INT, cfg);
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_TX_INT);
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_TX_INT, cfg);
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_INT);
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_INT, cfg);

	अगर (lmac->use_training) अणु
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_BR_PMD_LP_CUP, 0x00);
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_BR_PMD_LD_CUP, 0x00);
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_BR_PMD_LD_REP, 0x00);
		/* training enable */
		bgx_reg_modअगरy(bgx, lmacid,
			       BGX_SPUX_BR_PMD_CRTL, SPU_PMD_CRTL_TRAIN_EN);
	पूर्ण

	/* Append FCS to each packet */
	bgx_reg_modअगरy(bgx, lmacid, BGX_SMUX_TX_APPEND, SMU_TX_APPEND_FCS_D);

	/* Disable क्रमward error correction */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_FEC_CONTROL);
	cfg &= ~SPU_FEC_CTL_FEC_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_FEC_CONTROL, cfg);

	/* Disable स्वतःneg */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_AN_CONTROL);
	cfg = cfg & ~(SPU_AN_CTL_AN_EN | SPU_AN_CTL_XNP_EN);
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_AN_CONTROL, cfg);

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_AN_ADV);
	अगर (lmac->lmac_type == BGX_MODE_10G_KR)
		cfg |= (1 << 23);
	अन्यथा अगर (lmac->lmac_type == BGX_MODE_40G_KR)
		cfg |= (1 << 24);
	अन्यथा
		cfg &= ~((1 << 23) | (1 << 24));
	cfg = cfg & (~((1ULL << 25) | (1ULL << 22) | (1ULL << 12)));
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_AN_ADV, cfg);

	cfg = bgx_reg_पढ़ो(bgx, 0, BGX_SPU_DBG_CONTROL);
	cfg &= ~SPU_DBG_CTL_AN_ARB_LINK_CHK_EN;
	bgx_reg_ग_लिखो(bgx, 0, BGX_SPU_DBG_CONTROL, cfg);

	/* Enable lmac */
	bgx_reg_modअगरy(bgx, lmacid, BGX_CMRX_CFG, CMR_EN);

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_CONTROL1);
	cfg &= ~SPU_CTL_LOW_POWER;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_CONTROL1, cfg);

	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_TX_CTL);
	cfg &= ~SMU_TX_CTL_UNI_EN;
	cfg |= SMU_TX_CTL_DIC_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_TX_CTL, cfg);

	/* Enable receive and transmission of छोड़ो frames */
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_CBFC_CTL, ((0xffffULL << 32) |
		      BCK_EN | DRP_EN | TX_EN | RX_EN));
	/* Configure छोड़ो समय and पूर्णांकerval */
	bgx_reg_ग_लिखो(bgx, lmacid,
		      BGX_SMUX_TX_PAUSE_PKT_TIME, DEFAULT_PAUSE_TIME);
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_TX_PAUSE_PKT_INTERVAL);
	cfg &= ~0xFFFFull;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_TX_PAUSE_PKT_INTERVAL,
		      cfg | (DEFAULT_PAUSE_TIME - 0x1000));
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_TX_PAUSE_ZERO, 0x01);

	/* take lmac_count पूर्णांकo account */
	bgx_reg_modअगरy(bgx, lmacid, BGX_SMUX_TX_THRESH, (0x100 - 1));
	/* max packet size */
	bgx_reg_modअगरy(bgx, lmacid, BGX_SMUX_RX_JABBER, MAX_FRAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक bgx_xaui_check_link(काष्ठा lmac *lmac)
अणु
	काष्ठा bgx *bgx = lmac->bgx;
	पूर्णांक lmacid = lmac->lmacid;
	पूर्णांक lmac_type = lmac->lmac_type;
	u64 cfg;

	अगर (lmac->use_training) अणु
		cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_INT);
		अगर (!(cfg & (1ull << 13))) अणु
			cfg = (1ull << 13) | (1ull << 14);
			bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_INT, cfg);
			cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_BR_PMD_CRTL);
			cfg |= (1ull << 0);
			bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_BR_PMD_CRTL, cfg);
			वापस -1;
		पूर्ण
	पूर्ण

	/* रुको क्रम PCS to come out of reset */
	अगर (bgx_poll_reg(bgx, lmacid, BGX_SPUX_CONTROL1, SPU_CTL_RESET, true)) अणु
		dev_err(&bgx->pdev->dev, "BGX SPU reset not completed\n");
		वापस -1;
	पूर्ण

	अगर ((lmac_type == BGX_MODE_10G_KR) || (lmac_type == BGX_MODE_XFI) ||
	    (lmac_type == BGX_MODE_40G_KR) || (lmac_type == BGX_MODE_XLAUI)) अणु
		अगर (bgx_poll_reg(bgx, lmacid, BGX_SPUX_BR_STATUS1,
				 SPU_BR_STATUS_BLK_LOCK, false)) अणु
			dev_err(&bgx->pdev->dev,
				"SPU_BR_STATUS_BLK_LOCK not completed\n");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bgx_poll_reg(bgx, lmacid, BGX_SPUX_BX_STATUS,
				 SPU_BX_STATUS_RX_ALIGN, false)) अणु
			dev_err(&bgx->pdev->dev,
				"SPU_BX_STATUS_RX_ALIGN not completed\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* Clear rcvflt bit (latching high) and पढ़ो it back */
	अगर (bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_STATUS2) & SPU_STATUS2_RCVFLT)
		bgx_reg_modअगरy(bgx, lmacid,
			       BGX_SPUX_STATUS2, SPU_STATUS2_RCVFLT);
	अगर (bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_STATUS2) & SPU_STATUS2_RCVFLT) अणु
		dev_err(&bgx->pdev->dev, "Receive fault, retry training\n");
		अगर (lmac->use_training) अणु
			cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_INT);
			अगर (!(cfg & (1ull << 13))) अणु
				cfg = (1ull << 13) | (1ull << 14);
				bgx_reg_ग_लिखो(bgx, lmacid, BGX_SPUX_INT, cfg);
				cfg = bgx_reg_पढ़ो(bgx, lmacid,
						   BGX_SPUX_BR_PMD_CRTL);
				cfg |= (1ull << 0);
				bgx_reg_ग_लिखो(bgx, lmacid,
					      BGX_SPUX_BR_PMD_CRTL, cfg);
				वापस -1;
			पूर्ण
		पूर्ण
		वापस -1;
	पूर्ण

	/* Wait क्रम BGX RX to be idle */
	अगर (bgx_poll_reg(bgx, lmacid, BGX_SMUX_CTL, SMU_CTL_RX_IDLE, false)) अणु
		dev_err(&bgx->pdev->dev, "SMU RX not idle\n");
		वापस -1;
	पूर्ण

	/* Wait क्रम BGX TX to be idle */
	अगर (bgx_poll_reg(bgx, lmacid, BGX_SMUX_CTL, SMU_CTL_TX_IDLE, false)) अणु
		dev_err(&bgx->pdev->dev, "SMU TX not idle\n");
		वापस -1;
	पूर्ण

	/* Check क्रम MAC RX faults */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_RX_CTL);
	/* 0 - Link is okay, 1 - Local fault, 2 - Remote fault */
	cfg &= SMU_RX_CTL_STATUS;
	अगर (!cfg)
		वापस 0;

	/* Rx local/remote fault seen.
	 * Do lmac reinit to see अगर condition recovers
	 */
	bgx_lmac_xaui_init(bgx, lmac);

	वापस -1;
पूर्ण

अटल व्योम bgx_poll_क्रम_sgmii_link(काष्ठा lmac *lmac)
अणु
	u64 pcs_link, an_result;
	u8 speed;

	pcs_link = bgx_reg_पढ़ो(lmac->bgx, lmac->lmacid,
				BGX_GMP_PCS_MRX_STATUS);

	/*Link state bit is sticky, पढ़ो it again*/
	अगर (!(pcs_link & PCS_MRX_STATUS_LINK))
		pcs_link = bgx_reg_पढ़ो(lmac->bgx, lmac->lmacid,
					BGX_GMP_PCS_MRX_STATUS);

	अगर (bgx_poll_reg(lmac->bgx, lmac->lmacid, BGX_GMP_PCS_MRX_STATUS,
			 PCS_MRX_STATUS_AN_CPT, false)) अणु
		lmac->link_up = false;
		lmac->last_speed = SPEED_UNKNOWN;
		lmac->last_duplex = DUPLEX_UNKNOWN;
		जाओ next_poll;
	पूर्ण

	lmac->link_up = ((pcs_link & PCS_MRX_STATUS_LINK) != 0) ? true : false;
	an_result = bgx_reg_पढ़ो(lmac->bgx, lmac->lmacid,
				 BGX_GMP_PCS_ANX_AN_RESULTS);

	speed = (an_result >> 3) & 0x3;
	lmac->last_duplex = (an_result >> 1) & 0x1;
	चयन (speed) अणु
	हाल 0:
		lmac->last_speed = SPEED_10;
		अवरोध;
	हाल 1:
		lmac->last_speed = SPEED_100;
		अवरोध;
	हाल 2:
		lmac->last_speed = SPEED_1000;
		अवरोध;
	शेष:
		lmac->link_up = false;
		lmac->last_speed = SPEED_UNKNOWN;
		lmac->last_duplex = DUPLEX_UNKNOWN;
		अवरोध;
	पूर्ण

next_poll:

	अगर (lmac->last_link != lmac->link_up) अणु
		अगर (lmac->link_up)
			bgx_sgmii_change_link_state(lmac);
		lmac->last_link = lmac->link_up;
	पूर्ण

	queue_delayed_work(lmac->check_link, &lmac->dwork, HZ * 3);
पूर्ण

अटल व्योम bgx_poll_क्रम_link(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lmac *lmac;
	u64 spu_link, smu_link;

	lmac = container_of(work, काष्ठा lmac, dwork.work);
	अगर (lmac->is_sgmii) अणु
		bgx_poll_क्रम_sgmii_link(lmac);
		वापस;
	पूर्ण

	/* Receive link is latching low. Force it high and verअगरy it */
	bgx_reg_modअगरy(lmac->bgx, lmac->lmacid,
		       BGX_SPUX_STATUS1, SPU_STATUS1_RCV_LNK);
	bgx_poll_reg(lmac->bgx, lmac->lmacid, BGX_SPUX_STATUS1,
		     SPU_STATUS1_RCV_LNK, false);

	spu_link = bgx_reg_पढ़ो(lmac->bgx, lmac->lmacid, BGX_SPUX_STATUS1);
	smu_link = bgx_reg_पढ़ो(lmac->bgx, lmac->lmacid, BGX_SMUX_RX_CTL);

	अगर ((spu_link & SPU_STATUS1_RCV_LNK) &&
	    !(smu_link & SMU_RX_CTL_STATUS)) अणु
		lmac->link_up = true;
		अगर (lmac->lmac_type == BGX_MODE_XLAUI)
			lmac->last_speed = SPEED_40000;
		अन्यथा
			lmac->last_speed = SPEED_10000;
		lmac->last_duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		lmac->link_up = false;
		lmac->last_speed = SPEED_UNKNOWN;
		lmac->last_duplex = DUPLEX_UNKNOWN;
	पूर्ण

	अगर (lmac->last_link != lmac->link_up) अणु
		अगर (lmac->link_up) अणु
			अगर (bgx_xaui_check_link(lmac)) अणु
				/* Errors, clear link_up state */
				lmac->link_up = false;
				lmac->last_speed = SPEED_UNKNOWN;
				lmac->last_duplex = DUPLEX_UNKNOWN;
			पूर्ण
		पूर्ण
		lmac->last_link = lmac->link_up;
	पूर्ण

	queue_delayed_work(lmac->check_link, &lmac->dwork, HZ * 2);
पूर्ण

अटल पूर्णांक phy_पूर्णांकerface_mode(u8 lmac_type)
अणु
	अगर (lmac_type == BGX_MODE_QSGMII)
		वापस PHY_INTERFACE_MODE_QSGMII;
	अगर (lmac_type == BGX_MODE_RGMII)
		वापस PHY_INTERFACE_MODE_RGMII_RXID;

	वापस PHY_INTERFACE_MODE_SGMII;
पूर्ण

अटल पूर्णांक bgx_lmac_enable(काष्ठा bgx *bgx, u8 lmacid)
अणु
	काष्ठा lmac *lmac;
	u64 cfg;

	lmac = &bgx->lmac[lmacid];
	lmac->bgx = bgx;

	अगर ((lmac->lmac_type == BGX_MODE_SGMII) ||
	    (lmac->lmac_type == BGX_MODE_QSGMII) ||
	    (lmac->lmac_type == BGX_MODE_RGMII)) अणु
		lmac->is_sgmii = true;
		अगर (bgx_lmac_sgmii_init(bgx, lmac))
			वापस -1;
	पूर्ण अन्यथा अणु
		lmac->is_sgmii = false;
		अगर (bgx_lmac_xaui_init(bgx, lmac))
			वापस -1;
	पूर्ण

	अगर (lmac->is_sgmii) अणु
		cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_GMP_GMI_TXX_APPEND);
		cfg |= ((1ull << 2) | (1ull << 1)); /* FCS and PAD */
		bgx_reg_modअगरy(bgx, lmacid, BGX_GMP_GMI_TXX_APPEND, cfg);
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_GMP_GMI_TXX_MIN_PKT, 60 - 1);
	पूर्ण अन्यथा अणु
		cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_SMUX_TX_APPEND);
		cfg |= ((1ull << 2) | (1ull << 1)); /* FCS and PAD */
		bgx_reg_modअगरy(bgx, lmacid, BGX_SMUX_TX_APPEND, cfg);
		bgx_reg_ग_लिखो(bgx, lmacid, BGX_SMUX_TX_MIN_PKT, 60 + 4);
	पूर्ण

	/* actual number of filters available to exact LMAC */
	lmac->dmacs_count = (RX_DMAC_COUNT / bgx->lmac_count);
	lmac->dmacs = kसुस्मृति(lmac->dmacs_count, माप(*lmac->dmacs),
			      GFP_KERNEL);
	अगर (!lmac->dmacs)
		वापस -ENOMEM;

	/* Enable lmac */
	bgx_reg_modअगरy(bgx, lmacid, BGX_CMRX_CFG, CMR_EN);

	/* Restore शेष cfg, inहाल low level firmware changed it */
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_RX_DMAC_CTL, 0x03);

	अगर ((lmac->lmac_type != BGX_MODE_XFI) &&
	    (lmac->lmac_type != BGX_MODE_XLAUI) &&
	    (lmac->lmac_type != BGX_MODE_40G_KR) &&
	    (lmac->lmac_type != BGX_MODE_10G_KR)) अणु
		अगर (!lmac->phydev) अणु
			अगर (lmac->स्वतःneg) अणु
				bgx_reg_ग_लिखो(bgx, lmacid,
					      BGX_GMP_PCS_LINKX_TIMER,
					      PCS_LINKX_TIMER_COUNT);
				जाओ poll;
			पूर्ण अन्यथा अणु
				/* Default to below link speed and duplex */
				lmac->link_up = true;
				lmac->last_speed = SPEED_1000;
				lmac->last_duplex = DUPLEX_FULL;
				bgx_sgmii_change_link_state(lmac);
				वापस 0;
			पूर्ण
		पूर्ण
		lmac->phydev->dev_flags = 0;

		अगर (phy_connect_direct(&lmac->netdev, lmac->phydev,
				       bgx_lmac_handler,
				       phy_पूर्णांकerface_mode(lmac->lmac_type)))
			वापस -ENODEV;

		phy_start(lmac->phydev);
		वापस 0;
	पूर्ण

poll:
	lmac->check_link = alloc_workqueue("check_link", WQ_UNBOUND |
					   WQ_MEM_RECLAIM, 1);
	अगर (!lmac->check_link)
		वापस -ENOMEM;
	INIT_DELAYED_WORK(&lmac->dwork, bgx_poll_क्रम_link);
	queue_delayed_work(lmac->check_link, &lmac->dwork, 0);

	वापस 0;
पूर्ण

अटल व्योम bgx_lmac_disable(काष्ठा bgx *bgx, u8 lmacid)
अणु
	काष्ठा lmac *lmac;
	u64 cfg;

	lmac = &bgx->lmac[lmacid];
	अगर (lmac->check_link) अणु
		/* Destroy work queue */
		cancel_delayed_work_sync(&lmac->dwork);
		destroy_workqueue(lmac->check_link);
	पूर्ण

	/* Disable packet reception */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_PKT_RX_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_CFG, cfg);

	/* Give chance क्रम Rx/Tx FIFO to get drained */
	bgx_poll_reg(bgx, lmacid, BGX_CMRX_RX_FIFO_LEN, (u64)0x1FFF, true);
	bgx_poll_reg(bgx, lmacid, BGX_CMRX_TX_FIFO_LEN, (u64)0x3FFF, true);

	/* Disable packet transmission */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_PKT_TX_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_CFG, cfg);

	/* Disable serdes lanes */
        अगर (!lmac->is_sgmii)
                bgx_reg_modअगरy(bgx, lmacid,
                               BGX_SPUX_CONTROL1, SPU_CTL_LOW_POWER);
        अन्यथा
                bgx_reg_modअगरy(bgx, lmacid,
                               BGX_GMP_PCS_MRX_CTL, PCS_MRX_CTL_PWR_DN);

	/* Disable LMAC */
	cfg = bgx_reg_पढ़ो(bgx, lmacid, BGX_CMRX_CFG);
	cfg &= ~CMR_EN;
	bgx_reg_ग_लिखो(bgx, lmacid, BGX_CMRX_CFG, cfg);

	bgx_flush_dmac_cam_filter(bgx, lmacid);
	kमुक्त(lmac->dmacs);

	अगर ((lmac->lmac_type != BGX_MODE_XFI) &&
	    (lmac->lmac_type != BGX_MODE_XLAUI) &&
	    (lmac->lmac_type != BGX_MODE_40G_KR) &&
	    (lmac->lmac_type != BGX_MODE_10G_KR) && lmac->phydev)
		phy_disconnect(lmac->phydev);

	lmac->phydev = शून्य;
पूर्ण

अटल व्योम bgx_init_hw(काष्ठा bgx *bgx)
अणु
	पूर्णांक i;
	काष्ठा lmac *lmac;

	bgx_reg_modअगरy(bgx, 0, BGX_CMR_GLOBAL_CFG, CMR_GLOBAL_CFG_FCS_STRIP);
	अगर (bgx_reg_पढ़ो(bgx, 0, BGX_CMR_BIST_STATUS))
		dev_err(&bgx->pdev->dev, "BGX%d BIST failed\n", bgx->bgx_id);

	/* Set lmac type and lane2serdes mapping */
	क्रम (i = 0; i < bgx->lmac_count; i++) अणु
		lmac = &bgx->lmac[i];
		bgx_reg_ग_लिखो(bgx, i, BGX_CMRX_CFG,
			      (lmac->lmac_type << 8) | lmac->lane_to_sds);
		bgx->lmac[i].lmacid_bd = lmac_count;
		lmac_count++;
	पूर्ण

	bgx_reg_ग_लिखो(bgx, 0, BGX_CMR_TX_LMACS, bgx->lmac_count);
	bgx_reg_ग_लिखो(bgx, 0, BGX_CMR_RX_LMACS, bgx->lmac_count);

	/* Set the backpressure AND mask */
	क्रम (i = 0; i < bgx->lmac_count; i++)
		bgx_reg_modअगरy(bgx, 0, BGX_CMR_CHAN_MSK_AND,
			       ((1ULL << MAX_BGX_CHANS_PER_LMAC) - 1) <<
			       (i * MAX_BGX_CHANS_PER_LMAC));

	/* Disable all MAC filtering */
	क्रम (i = 0; i < RX_DMAC_COUNT; i++)
		bgx_reg_ग_लिखो(bgx, 0, BGX_CMR_RX_DMACX_CAM + (i * 8), 0x00);

	/* Disable MAC steering (NCSI traffic) */
	क्रम (i = 0; i < RX_TRAFFIC_STEER_RULE_COUNT; i++)
		bgx_reg_ग_लिखो(bgx, 0, BGX_CMR_RX_STEERING + (i * 8), 0x00);
पूर्ण

अटल u8 bgx_get_lane2sds_cfg(काष्ठा bgx *bgx, काष्ठा lmac *lmac)
अणु
	वापस (u8)(bgx_reg_पढ़ो(bgx, lmac->lmacid, BGX_CMRX_CFG) & 0xFF);
पूर्ण

अटल व्योम bgx_prपूर्णांक_qlm_mode(काष्ठा bgx *bgx, u8 lmacid)
अणु
	काष्ठा device *dev = &bgx->pdev->dev;
	काष्ठा lmac *lmac;
	अक्षर str[27];

	अगर (!bgx->is_dlm && lmacid)
		वापस;

	lmac = &bgx->lmac[lmacid];
	अगर (!bgx->is_dlm)
		प्र_लिखो(str, "BGX%d QLM mode", bgx->bgx_id);
	अन्यथा
		प्र_लिखो(str, "BGX%d LMAC%d mode", bgx->bgx_id, lmacid);

	चयन (lmac->lmac_type) अणु
	हाल BGX_MODE_SGMII:
		dev_info(dev, "%s: SGMII\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_XAUI:
		dev_info(dev, "%s: XAUI\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_RXAUI:
		dev_info(dev, "%s: RXAUI\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_XFI:
		अगर (!lmac->use_training)
			dev_info(dev, "%s: XFI\n", (अक्षर *)str);
		अन्यथा
			dev_info(dev, "%s: 10G_KR\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_XLAUI:
		अगर (!lmac->use_training)
			dev_info(dev, "%s: XLAUI\n", (अक्षर *)str);
		अन्यथा
			dev_info(dev, "%s: 40G_KR4\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_QSGMII:
		dev_info(dev, "%s: QSGMII\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_RGMII:
		dev_info(dev, "%s: RGMII\n", (अक्षर *)str);
		अवरोध;
	हाल BGX_MODE_INVALID:
		/* Nothing to करो */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lmac_set_lane2sds(काष्ठा bgx *bgx, काष्ठा lmac *lmac)
अणु
	चयन (lmac->lmac_type) अणु
	हाल BGX_MODE_SGMII:
	हाल BGX_MODE_XFI:
		lmac->lane_to_sds = lmac->lmacid;
		अवरोध;
	हाल BGX_MODE_XAUI:
	हाल BGX_MODE_XLAUI:
	हाल BGX_MODE_RGMII:
		lmac->lane_to_sds = 0xE4;
		अवरोध;
	हाल BGX_MODE_RXAUI:
		lmac->lane_to_sds = (lmac->lmacid) ? 0xE : 0x4;
		अवरोध;
	हाल BGX_MODE_QSGMII:
		/* There is no way to determine अगर DLM0/2 is QSGMII or
		 * DLM1/3 is configured to QSGMII as bootloader will
		 * configure all LMACs, so take whatever is configured
		 * by low level firmware.
		 */
		lmac->lane_to_sds = bgx_get_lane2sds_cfg(bgx, lmac);
		अवरोध;
	शेष:
		lmac->lane_to_sds = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lmac_set_training(काष्ठा bgx *bgx, काष्ठा lmac *lmac, पूर्णांक lmacid)
अणु
	अगर ((lmac->lmac_type != BGX_MODE_10G_KR) &&
	    (lmac->lmac_type != BGX_MODE_40G_KR)) अणु
		lmac->use_training = false;
		वापस;
	पूर्ण

	lmac->use_training = bgx_reg_पढ़ो(bgx, lmacid, BGX_SPUX_BR_PMD_CRTL) &
							SPU_PMD_CRTL_TRAIN_EN;
पूर्ण

अटल व्योम bgx_set_lmac_config(काष्ठा bgx *bgx, u8 idx)
अणु
	काष्ठा lmac *lmac;
	u64 cmr_cfg;
	u8 lmac_type;
	u8 lane_to_sds;

	lmac = &bgx->lmac[idx];

	अगर (!bgx->is_dlm || bgx->is_rgx) अणु
		/* Read LMAC0 type to figure out QLM mode
		 * This is configured by low level firmware
		 */
		cmr_cfg = bgx_reg_पढ़ो(bgx, 0, BGX_CMRX_CFG);
		lmac->lmac_type = (cmr_cfg >> 8) & 0x07;
		अगर (bgx->is_rgx)
			lmac->lmac_type = BGX_MODE_RGMII;
		lmac_set_training(bgx, lmac, 0);
		lmac_set_lane2sds(bgx, lmac);
		वापस;
	पूर्ण

	/* For DLMs or SLMs on 80/81/83xx so many lane configurations
	 * are possible and vary across boards. Also Kernel करोesn't have
	 * any way to identअगरy board type/info and since firmware करोes,
	 * just take lmac type and serdes lane config as is.
	 */
	cmr_cfg = bgx_reg_पढ़ो(bgx, idx, BGX_CMRX_CFG);
	lmac_type = (u8)((cmr_cfg >> 8) & 0x07);
	lane_to_sds = (u8)(cmr_cfg & 0xFF);
	/* Check अगर config is reset value */
	अगर ((lmac_type == 0) && (lane_to_sds == 0xE4))
		lmac->lmac_type = BGX_MODE_INVALID;
	अन्यथा
		lmac->lmac_type = lmac_type;
	lmac->lane_to_sds = lane_to_sds;
	lmac_set_training(bgx, lmac, lmac->lmacid);
पूर्ण

अटल व्योम bgx_get_qlm_mode(काष्ठा bgx *bgx)
अणु
	काष्ठा lmac *lmac;
	u8  idx;

	/* Init all LMAC's type to invalid */
	क्रम (idx = 0; idx < bgx->max_lmac; idx++) अणु
		lmac = &bgx->lmac[idx];
		lmac->lmacid = idx;
		lmac->lmac_type = BGX_MODE_INVALID;
		lmac->use_training = false;
	पूर्ण

	/* It is assumed that low level firmware sets this value */
	bgx->lmac_count = bgx_reg_पढ़ो(bgx, 0, BGX_CMR_RX_LMACS) & 0x7;
	अगर (bgx->lmac_count > bgx->max_lmac)
		bgx->lmac_count = bgx->max_lmac;

	क्रम (idx = 0; idx < bgx->lmac_count; idx++) अणु
		bgx_set_lmac_config(bgx, idx);
		bgx_prपूर्णांक_qlm_mode(bgx, idx);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI

अटल पूर्णांक acpi_get_mac_address(काष्ठा device *dev, काष्ठा acpi_device *adev,
				u8 *dst)
अणु
	u8 mac[ETH_ALEN];
	u8 *addr;

	addr = fwnode_get_mac_address(acpi_fwnode_handle(adev), mac, ETH_ALEN);
	अगर (!addr) अणु
		dev_err(dev, "MAC address invalid: %pM\n", mac);
		वापस -EINVAL;
	पूर्ण

	dev_info(dev, "MAC address set to: %pM\n", mac);

	ether_addr_copy(dst, mac);
	वापस 0;
पूर्ण

/* Currently only sets the MAC address. */
अटल acpi_status bgx_acpi_रेजिस्टर_phy(acpi_handle handle,
					 u32 lvl, व्योम *context, व्योम **rv)
अणु
	काष्ठा bgx *bgx = context;
	काष्ठा device *dev = &bgx->pdev->dev;
	काष्ठा acpi_device *adev;

	अगर (acpi_bus_get_device(handle, &adev))
		जाओ out;

	acpi_get_mac_address(dev, adev, bgx->lmac[bgx->acpi_lmac_idx].mac);

	SET_NETDEV_DEV(&bgx->lmac[bgx->acpi_lmac_idx].netdev, dev);

	bgx->lmac[bgx->acpi_lmac_idx].lmacid = bgx->acpi_lmac_idx;
	bgx->acpi_lmac_idx++; /* move to next LMAC */
out:
	वापस AE_OK;
पूर्ण

अटल acpi_status bgx_acpi_match_id(acpi_handle handle, u32 lvl,
				     व्योम *context, व्योम **ret_val)
अणु
	काष्ठा acpi_buffer string = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा bgx *bgx = context;
	अक्षर bgx_sel[5];

	snम_लिखो(bgx_sel, 5, "BGX%d", bgx->bgx_id);
	अगर (ACPI_FAILURE(acpi_get_name(handle, ACPI_SINGLE_NAME, &string))) अणु
		pr_warn("Invalid link device\n");
		वापस AE_OK;
	पूर्ण

	अगर (म_भेदन(string.poपूर्णांकer, bgx_sel, 4))
		वापस AE_OK;

	acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
			    bgx_acpi_रेजिस्टर_phy, शून्य, bgx, शून्य);

	kमुक्त(string.poपूर्णांकer);
	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल पूर्णांक bgx_init_acpi_phy(काष्ठा bgx *bgx)
अणु
	acpi_get_devices(शून्य, bgx_acpi_match_id, bgx, (व्योम **)शून्य);
	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक bgx_init_acpi_phy(काष्ठा bgx *bgx)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI */

#अगर IS_ENABLED(CONFIG_OF_MDIO)

अटल पूर्णांक bgx_init_of_phy(काष्ठा bgx *bgx)
अणु
	काष्ठा fwnode_handle *fwn;
	काष्ठा device_node *node = शून्य;
	u8 lmac = 0;

	device_क्रम_each_child_node(&bgx->pdev->dev, fwn) अणु
		काष्ठा phy_device *pd;
		काष्ठा device_node *phy_np;

		/* Should always be an OF node.  But अगर it is not, we
		 * cannot handle it, so निकास the loop.
		 */
		node = to_of_node(fwn);
		अगर (!node)
			अवरोध;

		of_get_mac_address(node, bgx->lmac[lmac].mac);

		SET_NETDEV_DEV(&bgx->lmac[lmac].netdev, &bgx->pdev->dev);
		bgx->lmac[lmac].lmacid = lmac;

		phy_np = of_parse_phandle(node, "phy-handle", 0);
		/* If there is no phy or defective firmware presents
		 * this cortina phy, क्रम which there is no driver
		 * support, ignore it.
		 */
		अगर (phy_np &&
		    !of_device_is_compatible(phy_np, "cortina,cs4223-slice")) अणु
			/* Wait until the phy drivers are available */
			pd = of_phy_find_device(phy_np);
			अगर (!pd)
				जाओ defer;
			bgx->lmac[lmac].phydev = pd;
		पूर्ण

		lmac++;
		अगर (lmac == bgx->max_lmac) अणु
			of_node_put(node);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;

defer:
	/* We are bailing out, try not to leak device reference counts
	 * क्रम phy devices we may have alपढ़ोy found.
	 */
	जबतक (lmac) अणु
		अगर (bgx->lmac[lmac].phydev) अणु
			put_device(&bgx->lmac[lmac].phydev->mdio.dev);
			bgx->lmac[lmac].phydev = शून्य;
		पूर्ण
		lmac--;
	पूर्ण
	of_node_put(node);
	वापस -EPROBE_DEFER;
पूर्ण

#अन्यथा

अटल पूर्णांक bgx_init_of_phy(काष्ठा bgx *bgx)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक bgx_init_phy(काष्ठा bgx *bgx)
अणु
	अगर (!acpi_disabled)
		वापस bgx_init_acpi_phy(bgx);

	वापस bgx_init_of_phy(bgx);
पूर्ण

अटल irqवापस_t bgx_पूर्णांकr_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bgx *bgx = (काष्ठा bgx *)data;
	u64 status, val;
	पूर्णांक lmac;

	क्रम (lmac = 0; lmac < bgx->lmac_count; lmac++) अणु
		status = bgx_reg_पढ़ो(bgx, lmac, BGX_GMP_GMI_TXX_INT);
		अगर (status & GMI_TXX_INT_UNDFLW) अणु
			pci_err(bgx->pdev, "BGX%d lmac%d UNDFLW\n",
				bgx->bgx_id, lmac);
			val = bgx_reg_पढ़ो(bgx, lmac, BGX_CMRX_CFG);
			val &= ~CMR_EN;
			bgx_reg_ग_लिखो(bgx, lmac, BGX_CMRX_CFG, val);
			val |= CMR_EN;
			bgx_reg_ग_लिखो(bgx, lmac, BGX_CMRX_CFG, val);
		पूर्ण
		/* clear पूर्णांकerrupts */
		bgx_reg_ग_लिखो(bgx, lmac, BGX_GMP_GMI_TXX_INT, status);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bgx_रेजिस्टर_पूर्णांकr(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bgx *bgx = pci_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pci_alloc_irq_vectors(pdev, BGX_LMAC_VEC_OFFSET,
				    BGX_LMAC_VEC_OFFSET, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0) अणु
		pci_err(pdev, "Req for #%d msix vectors failed\n",
			BGX_LMAC_VEC_OFFSET);
		वापस;
	पूर्ण
	ret = pci_request_irq(pdev, GMPX_GMI_TX_INT, bgx_पूर्णांकr_handler, शून्य,
			      bgx, "BGX%d", bgx->bgx_id);
	अगर (ret)
		pci_मुक्त_irq(pdev, GMPX_GMI_TX_INT, bgx);
पूर्ण

अटल पूर्णांक bgx_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bgx *bgx = शून्य;
	u8 lmac;
	u16 sdevid;

	bgx = devm_kzalloc(dev, माप(*bgx), GFP_KERNEL);
	अगर (!bgx)
		वापस -ENOMEM;
	bgx->pdev = pdev;

	pci_set_drvdata(pdev, bgx);

	err = pcim_enable_device(pdev);
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
	bgx->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!bgx->reg_base) अणु
		dev_err(dev, "BGX: Cannot map CSR memory space, aborting\n");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	set_max_bgx_per_node(pdev);

	pci_पढ़ो_config_word(pdev, PCI_DEVICE_ID, &sdevid);
	अगर (sdevid != PCI_DEVICE_ID_THUNDER_RGX) अणु
		bgx->bgx_id = (pci_resource_start(pdev,
			PCI_CFG_REG_BAR_NUM) >> 24) & BGX_ID_MASK;
		bgx->bgx_id += nic_get_node_id(pdev) * max_bgx_per_node;
		bgx->max_lmac = MAX_LMAC_PER_BGX;
		bgx_vnic[bgx->bgx_id] = bgx;
	पूर्ण अन्यथा अणु
		bgx->is_rgx = true;
		bgx->max_lmac = 1;
		bgx->bgx_id = MAX_BGX_PER_CN81XX - 1;
		bgx_vnic[bgx->bgx_id] = bgx;
		xcv_init_hw();
	पूर्ण

	/* On 81xx all are DLMs and on 83xx there are 3 BGX QLMs and one
	 * BGX i.e BGX2 can be split across 2 DLMs.
	 */
	pci_पढ़ो_config_word(pdev, PCI_SUBSYSTEM_ID, &sdevid);
	अगर ((sdevid == PCI_SUBSYS_DEVID_81XX_BGX) ||
	    ((sdevid == PCI_SUBSYS_DEVID_83XX_BGX) && (bgx->bgx_id == 2)))
		bgx->is_dlm = true;

	bgx_get_qlm_mode(bgx);

	err = bgx_init_phy(bgx);
	अगर (err)
		जाओ err_enable;

	bgx_init_hw(bgx);

	bgx_रेजिस्टर_पूर्णांकr(pdev);

	/* Enable all LMACs */
	क्रम (lmac = 0; lmac < bgx->lmac_count; lmac++) अणु
		err = bgx_lmac_enable(bgx, lmac);
		अगर (err) अणु
			dev_err(dev, "BGX%d failed to enable lmac%d\n",
				bgx->bgx_id, lmac);
			जबतक (lmac)
				bgx_lmac_disable(bgx, --lmac);
			जाओ err_enable;
		पूर्ण
	पूर्ण

	वापस 0;

err_enable:
	bgx_vnic[bgx->bgx_id] = शून्य;
	pci_मुक्त_irq(pdev, GMPX_GMI_TX_INT, bgx);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम bgx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bgx *bgx = pci_get_drvdata(pdev);
	u8 lmac;

	/* Disable all LMACs */
	क्रम (lmac = 0; lmac < bgx->lmac_count; lmac++)
		bgx_lmac_disable(bgx, lmac);

	pci_मुक्त_irq(pdev, GMPX_GMI_TX_INT, bgx);

	bgx_vnic[bgx->bgx_id] = शून्य;
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा pci_driver bgx_driver = अणु
	.name = DRV_NAME,
	.id_table = bgx_id_table,
	.probe = bgx_probe,
	.हटाओ = bgx_हटाओ,
पूर्ण;

अटल पूर्णांक __init bgx_init_module(व्योम)
अणु
	pr_info("%s, ver %s\n", DRV_NAME, DRV_VERSION);

	वापस pci_रेजिस्टर_driver(&bgx_driver);
पूर्ण

अटल व्योम __निकास bgx_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bgx_driver);
पूर्ण

module_init(bgx_init_module);
module_निकास(bgx_cleanup_module);
