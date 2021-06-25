<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Intel Corporation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmi.h>
#समावेश "dwmac-intel.h"
#समावेश "dwmac4.h"
#समावेश "stmmac.h"
#समावेश "stmmac_ptp.h"

#घोषणा INTEL_MGBE_ADHOC_ADDR	0x15
#घोषणा INTEL_MGBE_XPCS_ADDR	0x16

/* Selection क्रम PTP Clock Freq beदीर्घs to PSE & PCH GbE */
#घोषणा PSE_PTP_CLK_FREQ_MASK		(GMAC_GPO0 | GMAC_GPO3)
#घोषणा PSE_PTP_CLK_FREQ_19_2MHZ	(GMAC_GPO0)
#घोषणा PSE_PTP_CLK_FREQ_200MHZ		(GMAC_GPO0 | GMAC_GPO3)
#घोषणा PSE_PTP_CLK_FREQ_256MHZ		(0)
#घोषणा PCH_PTP_CLK_FREQ_MASK		(GMAC_GPO0)
#घोषणा PCH_PTP_CLK_FREQ_19_2MHZ	(GMAC_GPO0)
#घोषणा PCH_PTP_CLK_FREQ_200MHZ		(0)

/* Cross-बारtamping defines */
#घोषणा ART_CPUID_LEAF		0x15
#घोषणा EHL_PSE_ART_MHZ		19200000

काष्ठा पूर्णांकel_priv_data अणु
	पूर्णांक mdio_adhoc_addr;	/* mdio address क्रम serdes & etc */
	अचिन्हित दीर्घ crossts_adj;
	bool is_pse;
पूर्ण;

/* This काष्ठा is used to associate PCI Function of MAC controller on a board,
 * discovered via DMI, with the address of PHY connected to the MAC. The
 * negative value of the address means that MAC controller is not connected
 * with PHY.
 */
काष्ठा sपंचांगmac_pci_func_data अणु
	अचिन्हित पूर्णांक func;
	पूर्णांक phy_addr;
पूर्ण;

काष्ठा sपंचांगmac_pci_dmi_data अणु
	स्थिर काष्ठा sपंचांगmac_pci_func_data *func;
	माप_प्रकार nfuncs;
पूर्ण;

काष्ठा sपंचांगmac_pci_info अणु
	पूर्णांक (*setup)(काष्ठा pci_dev *pdev, काष्ठा plat_sपंचांगmacenet_data *plat);
पूर्ण;

अटल पूर्णांक sपंचांगmac_pci_find_phy_addr(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा dmi_प्रणाली_id *dmi_list)
अणु
	स्थिर काष्ठा sपंचांगmac_pci_func_data *func_data;
	स्थिर काष्ठा sपंचांगmac_pci_dmi_data *dmi_data;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	पूर्णांक func = PCI_FUNC(pdev->devfn);
	माप_प्रकार n;

	dmi_id = dmi_first_match(dmi_list);
	अगर (!dmi_id)
		वापस -ENODEV;

	dmi_data = dmi_id->driver_data;
	func_data = dmi_data->func;

	क्रम (n = 0; n < dmi_data->nfuncs; n++, func_data++)
		अगर (func_data->func == func)
			वापस func_data->phy_addr;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक serdes_status_poll(काष्ठा sपंचांगmac_priv *priv, पूर्णांक phyaddr,
			      पूर्णांक phyreg, u32 mask, u32 val)
अणु
	अचिन्हित पूर्णांक retries = 10;
	पूर्णांक val_rd;

	करो अणु
		val_rd = mdiobus_पढ़ो(priv->mii, phyaddr, phyreg);
		अगर ((val_rd & mask) == (val & mask))
			वापस 0;
		udelay(POLL_DELAY_US);
	पूर्ण जबतक (--retries);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक पूर्णांकel_serdes_घातerup(काष्ठा net_device *ndev, व्योम *priv_data)
अणु
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv = priv_data;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	पूर्णांक serdes_phy_addr = 0;
	u32 data = 0;

	अगर (!पूर्णांकel_priv->mdio_adhoc_addr)
		वापस 0;

	serdes_phy_addr = पूर्णांकel_priv->mdio_adhoc_addr;

	/* निश्चित clk_req */
	data = mdiobus_पढ़ो(priv->mii, serdes_phy_addr, SERDES_GCR0);
	data |= SERDES_PLL_CLK;
	mdiobus_ग_लिखो(priv->mii, serdes_phy_addr, SERDES_GCR0, data);

	/* check क्रम clk_ack निश्चितion */
	data = serdes_status_poll(priv, serdes_phy_addr,
				  SERDES_GSR0,
				  SERDES_PLL_CLK,
				  SERDES_PLL_CLK);

	अगर (data) अणु
		dev_err(priv->device, "Serdes PLL clk request timeout\n");
		वापस data;
	पूर्ण

	/* निश्चित lane reset */
	data = mdiobus_पढ़ो(priv->mii, serdes_phy_addr, SERDES_GCR0);
	data |= SERDES_RST;
	mdiobus_ग_लिखो(priv->mii, serdes_phy_addr, SERDES_GCR0, data);

	/* check क्रम निश्चित lane reset reflection */
	data = serdes_status_poll(priv, serdes_phy_addr,
				  SERDES_GSR0,
				  SERDES_RST,
				  SERDES_RST);

	अगर (data) अणु
		dev_err(priv->device, "Serdes assert lane reset timeout\n");
		वापस data;
	पूर्ण

	/*  move घातer state to P0 */
	data = mdiobus_पढ़ो(priv->mii, serdes_phy_addr, SERDES_GCR0);

	data &= ~SERDES_PWR_ST_MASK;
	data |= SERDES_PWR_ST_P0 << SERDES_PWR_ST_SHIFT;

	mdiobus_ग_लिखो(priv->mii, serdes_phy_addr, SERDES_GCR0, data);

	/* Check क्रम P0 state */
	data = serdes_status_poll(priv, serdes_phy_addr,
				  SERDES_GSR0,
				  SERDES_PWR_ST_MASK,
				  SERDES_PWR_ST_P0 << SERDES_PWR_ST_SHIFT);

	अगर (data) अणु
		dev_err(priv->device, "Serdes power state P0 timeout.\n");
		वापस data;
	पूर्ण

	/* PSE only - ungate SGMII PHY Rx Clock */
	अगर (पूर्णांकel_priv->is_pse)
		mdiobus_modअगरy(priv->mii, serdes_phy_addr, SERDES_GCR0,
			       0, SERDES_PHY_RX_CLK);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_serdes_घातerकरोwn(काष्ठा net_device *ndev, व्योम *पूर्णांकel_data)
अणु
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv = पूर्णांकel_data;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	पूर्णांक serdes_phy_addr = 0;
	u32 data = 0;

	अगर (!पूर्णांकel_priv->mdio_adhoc_addr)
		वापस;

	serdes_phy_addr = पूर्णांकel_priv->mdio_adhoc_addr;

	/* PSE only - gate SGMII PHY Rx Clock */
	अगर (पूर्णांकel_priv->is_pse)
		mdiobus_modअगरy(priv->mii, serdes_phy_addr, SERDES_GCR0,
			       SERDES_PHY_RX_CLK, 0);

	/*  move घातer state to P3 */
	data = mdiobus_पढ़ो(priv->mii, serdes_phy_addr, SERDES_GCR0);

	data &= ~SERDES_PWR_ST_MASK;
	data |= SERDES_PWR_ST_P3 << SERDES_PWR_ST_SHIFT;

	mdiobus_ग_लिखो(priv->mii, serdes_phy_addr, SERDES_GCR0, data);

	/* Check क्रम P3 state */
	data = serdes_status_poll(priv, serdes_phy_addr,
				  SERDES_GSR0,
				  SERDES_PWR_ST_MASK,
				  SERDES_PWR_ST_P3 << SERDES_PWR_ST_SHIFT);

	अगर (data) अणु
		dev_err(priv->device, "Serdes power state P3 timeout\n");
		वापस;
	पूर्ण

	/* de-निश्चित clk_req */
	data = mdiobus_पढ़ो(priv->mii, serdes_phy_addr, SERDES_GCR0);
	data &= ~SERDES_PLL_CLK;
	mdiobus_ग_लिखो(priv->mii, serdes_phy_addr, SERDES_GCR0, data);

	/* check क्रम clk_ack de-निश्चित */
	data = serdes_status_poll(priv, serdes_phy_addr,
				  SERDES_GSR0,
				  SERDES_PLL_CLK,
				  (u32)~SERDES_PLL_CLK);

	अगर (data) अणु
		dev_err(priv->device, "Serdes PLL clk de-assert timeout\n");
		वापस;
	पूर्ण

	/* de-निश्चित lane reset */
	data = mdiobus_पढ़ो(priv->mii, serdes_phy_addr, SERDES_GCR0);
	data &= ~SERDES_RST;
	mdiobus_ग_लिखो(priv->mii, serdes_phy_addr, SERDES_GCR0, data);

	/* check क्रम de-निश्चित lane reset reflection */
	data = serdes_status_poll(priv, serdes_phy_addr,
				  SERDES_GSR0,
				  SERDES_RST,
				  (u32)~SERDES_RST);

	अगर (data) अणु
		dev_err(priv->device, "Serdes de-assert lane reset timeout\n");
		वापस;
	पूर्ण
पूर्ण

/* Program PTP Clock Frequency क्रम dअगरferent variant of
 * Intel mGBE that has slightly dअगरferent GPO mapping
 */
अटल व्योम पूर्णांकel_mgbe_ptp_clk_freq_config(व्योम *npriv)
अणु
	काष्ठा sपंचांगmac_priv *priv = (काष्ठा sपंचांगmac_priv *)npriv;
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv;
	u32 gpio_value;

	पूर्णांकel_priv = (काष्ठा पूर्णांकel_priv_data *)priv->plat->bsp_priv;

	gpio_value = पढ़ोl(priv->ioaddr + GMAC_GPIO_STATUS);

	अगर (पूर्णांकel_priv->is_pse) अणु
		/* For PSE GbE, use 200MHz */
		gpio_value &= ~PSE_PTP_CLK_FREQ_MASK;
		gpio_value |= PSE_PTP_CLK_FREQ_200MHZ;
	पूर्ण अन्यथा अणु
		/* For PCH GbE, use 200MHz */
		gpio_value &= ~PCH_PTP_CLK_FREQ_MASK;
		gpio_value |= PCH_PTP_CLK_FREQ_200MHZ;
	पूर्ण

	ग_लिखोl(gpio_value, priv->ioaddr + GMAC_GPIO_STATUS);
पूर्ण

अटल व्योम get_artसमय(काष्ठा mii_bus *mii, पूर्णांक पूर्णांकel_adhoc_addr,
			u64 *art_समय)
अणु
	u64 ns;

	ns = mdiobus_पढ़ो(mii, पूर्णांकel_adhoc_addr, PMC_ART_VALUE3);
	ns <<= GMAC4_ART_TIME_SHIFT;
	ns |= mdiobus_पढ़ो(mii, पूर्णांकel_adhoc_addr, PMC_ART_VALUE2);
	ns <<= GMAC4_ART_TIME_SHIFT;
	ns |= mdiobus_पढ़ो(mii, पूर्णांकel_adhoc_addr, PMC_ART_VALUE1);
	ns <<= GMAC4_ART_TIME_SHIFT;
	ns |= mdiobus_पढ़ो(mii, पूर्णांकel_adhoc_addr, PMC_ART_VALUE0);

	*art_समय = ns;
पूर्ण

अटल पूर्णांक पूर्णांकel_crosststamp(kसमय_प्रकार *device,
			     काष्ठा प्रणाली_counterval_t *प्रणाली,
			     व्योम *ctx)
अणु
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv;

	काष्ठा sपंचांगmac_priv *priv = (काष्ठा sपंचांगmac_priv *)ctx;
	व्योम __iomem *ptpaddr = priv->ptpaddr;
	व्योम __iomem *ioaddr = priv->hw->pcsr;
	अचिन्हित दीर्घ flags;
	u64 art_समय = 0;
	u64 ptp_समय = 0;
	u32 num_snapshot;
	u32 gpio_value;
	u32 acr_value;
	पूर्णांक ret;
	u32 v;
	पूर्णांक i;

	अगर (!boot_cpu_has(X86_FEATURE_ART))
		वापस -EOPNOTSUPP;

	पूर्णांकel_priv = priv->plat->bsp_priv;

	/* Both पूर्णांकernal crossबारtamping and बाह्यal triggered event
	 * बारtamping cannot be run concurrently.
	 */
	अगर (priv->plat->ext_snapshot_en)
		वापस -EBUSY;

	mutex_lock(&priv->aux_ts_lock);
	/* Enable Internal snapshot trigger */
	acr_value = पढ़ोl(ptpaddr + PTP_ACR);
	acr_value &= ~PTP_ACR_MASK;
	चयन (priv->plat->पूर्णांक_snapshot_num) अणु
	हाल AUX_SNAPSHOT0:
		acr_value |= PTP_ACR_ATSEN0;
		अवरोध;
	हाल AUX_SNAPSHOT1:
		acr_value |= PTP_ACR_ATSEN1;
		अवरोध;
	हाल AUX_SNAPSHOT2:
		acr_value |= PTP_ACR_ATSEN2;
		अवरोध;
	हाल AUX_SNAPSHOT3:
		acr_value |= PTP_ACR_ATSEN3;
		अवरोध;
	शेष:
		mutex_unlock(&priv->aux_ts_lock);
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(acr_value, ptpaddr + PTP_ACR);

	/* Clear FIFO */
	acr_value = पढ़ोl(ptpaddr + PTP_ACR);
	acr_value |= PTP_ACR_ATSFC;
	ग_लिखोl(acr_value, ptpaddr + PTP_ACR);
	/* Release the mutex */
	mutex_unlock(&priv->aux_ts_lock);

	/* Trigger Internal snapshot संकेत
	 * Create a rising edge by just toggle the GPO1 to low
	 * and back to high.
	 */
	gpio_value = पढ़ोl(ioaddr + GMAC_GPIO_STATUS);
	gpio_value &= ~GMAC_GPO1;
	ग_लिखोl(gpio_value, ioaddr + GMAC_GPIO_STATUS);
	gpio_value |= GMAC_GPO1;
	ग_लिखोl(gpio_value, ioaddr + GMAC_GPIO_STATUS);

	/* Poll क्रम समय sync operation करोne */
	ret = पढ़ोl_poll_समयout(priv->ioaddr + GMAC_INT_STATUS, v,
				 (v & GMAC_INT_TSIE), 100, 10000);

	अगर (ret == -ETIMEDOUT) अणु
		pr_err("%s: Wait for time sync operation timeout\n", __func__);
		वापस ret;
	पूर्ण

	num_snapshot = (पढ़ोl(ioaddr + GMAC_TIMESTAMP_STATUS) &
			GMAC_TIMESTAMP_ATSNS_MASK) >>
			GMAC_TIMESTAMP_ATSNS_SHIFT;

	/* Repeat until the बारtamps are from the FIFO last segment */
	क्रम (i = 0; i < num_snapshot; i++) अणु
		spin_lock_irqsave(&priv->ptp_lock, flags);
		sपंचांगmac_get_ptpसमय(priv, ptpaddr, &ptp_समय);
		*device = ns_to_kसमय(ptp_समय);
		spin_unlock_irqrestore(&priv->ptp_lock, flags);
		get_artसमय(priv->mii, पूर्णांकel_priv->mdio_adhoc_addr, &art_समय);
		*प्रणाली = convert_art_to_tsc(art_समय);
	पूर्ण

	प्रणाली->cycles *= पूर्णांकel_priv->crossts_adj;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_mgbe_pse_crossts_adj(काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv,
				       पूर्णांक base)
अणु
	अगर (boot_cpu_has(X86_FEATURE_ART)) अणु
		अचिन्हित पूर्णांक art_freq;

		/* On प्रणालीs that support ART, ART frequency can be obtained
		 * from ECX रेजिस्टर of CPUID leaf (0x15).
		 */
		art_freq = cpuid_ecx(ART_CPUID_LEAF);
		करो_भाग(art_freq, base);
		पूर्णांकel_priv->crossts_adj = art_freq;
	पूर्ण
पूर्ण

अटल व्योम common_शेष_data(काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->clk_csr = 2;	/* clk_csr_i = 20-35MHz & MDC = clk_csr_i/16 */
	plat->has_gmac = 1;
	plat->क्रमce_sf_dma_mode = 1;

	plat->mdio_bus_data->needs_reset = true;

	/* Set शेष value क्रम multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set शेष value क्रम unicast filter entries */
	plat->unicast_filter_entries = 1;

	/* Set the maxmtu to a शेष of JUMBO_LEN */
	plat->maxmtu = JUMBO_LEN;

	/* Set शेष number of RX and TX queues to use */
	plat->tx_queues_to_use = 1;
	plat->rx_queues_to_use = 1;

	/* Disable Priority config by शेष */
	plat->tx_queues_cfg[0].use_prio = false;
	plat->rx_queues_cfg[0].use_prio = false;

	/* Disable RX queues routing by शेष */
	plat->rx_queues_cfg[0].pkt_route = 0x0;
पूर्ण

अटल पूर्णांक पूर्णांकel_mgbe_common_data(काष्ठा pci_dev *pdev,
				  काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	अक्षर clk_name[20];
	पूर्णांक ret;
	पूर्णांक i;

	plat->pdev = pdev;
	plat->phy_addr = -1;
	plat->clk_csr = 5;
	plat->has_gmac = 0;
	plat->has_gmac4 = 1;
	plat->क्रमce_sf_dma_mode = 0;
	plat->tso_en = 1;

	plat->rx_sched_algorithm = MTL_RX_ALGORITHM_SP;

	क्रम (i = 0; i < plat->rx_queues_to_use; i++) अणु
		plat->rx_queues_cfg[i].mode_to_use = MTL_QUEUE_DCB;
		plat->rx_queues_cfg[i].chan = i;

		/* Disable Priority config by शेष */
		plat->rx_queues_cfg[i].use_prio = false;

		/* Disable RX queues routing by शेष */
		plat->rx_queues_cfg[i].pkt_route = 0x0;
	पूर्ण

	क्रम (i = 0; i < plat->tx_queues_to_use; i++) अणु
		plat->tx_queues_cfg[i].mode_to_use = MTL_QUEUE_DCB;

		/* Disable Priority config by शेष */
		plat->tx_queues_cfg[i].use_prio = false;
		/* Default TX Q0 to use TSO and rest TXQ क्रम TBS */
		अगर (i > 0)
			plat->tx_queues_cfg[i].tbs_en = 1;
	पूर्ण

	/* FIFO size is 4096 bytes क्रम 1 tx/rx queue */
	plat->tx_fअगरo_size = plat->tx_queues_to_use * 4096;
	plat->rx_fअगरo_size = plat->rx_queues_to_use * 4096;

	plat->tx_sched_algorithm = MTL_TX_ALGORITHM_WRR;
	plat->tx_queues_cfg[0].weight = 0x09;
	plat->tx_queues_cfg[1].weight = 0x0A;
	plat->tx_queues_cfg[2].weight = 0x0B;
	plat->tx_queues_cfg[3].weight = 0x0C;
	plat->tx_queues_cfg[4].weight = 0x0D;
	plat->tx_queues_cfg[5].weight = 0x0E;
	plat->tx_queues_cfg[6].weight = 0x0F;
	plat->tx_queues_cfg[7].weight = 0x10;

	plat->dma_cfg->pbl = 32;
	plat->dma_cfg->pblx8 = true;
	plat->dma_cfg->fixed_burst = 0;
	plat->dma_cfg->mixed_burst = 0;
	plat->dma_cfg->aal = 0;
	plat->dma_cfg->dche = true;

	plat->axi = devm_kzalloc(&pdev->dev, माप(*plat->axi),
				 GFP_KERNEL);
	अगर (!plat->axi)
		वापस -ENOMEM;

	plat->axi->axi_lpi_en = 0;
	plat->axi->axi_xit_frm = 0;
	plat->axi->axi_wr_osr_lmt = 1;
	plat->axi->axi_rd_osr_lmt = 1;
	plat->axi->axi_blen[0] = 4;
	plat->axi->axi_blen[1] = 8;
	plat->axi->axi_blen[2] = 16;

	plat->ptp_max_adj = plat->clk_ptp_rate;
	plat->eee_usecs_rate = plat->clk_ptp_rate;

	/* Set प्रणाली घड़ी */
	प्र_लिखो(clk_name, "%s-%s", "stmmac", pci_name(pdev));

	plat->sपंचांगmac_clk = clk_रेजिस्टर_fixed_rate(&pdev->dev,
						   clk_name, शून्य, 0,
						   plat->clk_ptp_rate);

	अगर (IS_ERR(plat->sपंचांगmac_clk)) अणु
		dev_warn(&pdev->dev, "Fail to register stmmac-clk\n");
		plat->sपंचांगmac_clk = शून्य;
	पूर्ण

	ret = clk_prepare_enable(plat->sपंचांगmac_clk);
	अगर (ret) अणु
		clk_unरेजिस्टर_fixed_rate(plat->sपंचांगmac_clk);
		वापस ret;
	पूर्ण

	plat->ptp_clk_freq_config = पूर्णांकel_mgbe_ptp_clk_freq_config;

	/* Set शेष value क्रम multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set शेष value क्रम unicast filter entries */
	plat->unicast_filter_entries = 1;

	/* Set the maxmtu to a शेष of JUMBO_LEN */
	plat->maxmtu = JUMBO_LEN;

	plat->vlan_fail_q_en = true;

	/* Use the last Rx queue */
	plat->vlan_fail_q = plat->rx_queues_to_use - 1;

	/* Intel mgbe SGMII पूर्णांकerface uses pcs-xcps */
	अगर (plat->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		plat->mdio_bus_data->has_xpcs = true;
		plat->mdio_bus_data->xpcs_an_inband = true;
	पूर्ण

	/* Ensure mdio bus scan skips पूर्णांकel serdes and pcs-xpcs */
	plat->mdio_bus_data->phy_mask = 1 << INTEL_MGBE_ADHOC_ADDR;
	plat->mdio_bus_data->phy_mask |= 1 << INTEL_MGBE_XPCS_ADDR;

	plat->पूर्णांक_snapshot_num = AUX_SNAPSHOT1;
	plat->ext_snapshot_num = AUX_SNAPSHOT0;

	plat->has_crossts = true;
	plat->crosststamp = पूर्णांकel_crosststamp;

	/* Setup MSI vector offset specअगरic to Intel mGbE controller */
	plat->msi_mac_vec = 29;
	plat->msi_lpi_vec = 28;
	plat->msi_sfty_ce_vec = 27;
	plat->msi_sfty_ue_vec = 26;
	plat->msi_rx_base_vec = 0;
	plat->msi_tx_base_vec = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ehl_common_data(काष्ठा pci_dev *pdev,
			   काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->rx_queues_to_use = 8;
	plat->tx_queues_to_use = 8;
	plat->clk_ptp_rate = 200000000;

	वापस पूर्णांकel_mgbe_common_data(pdev, plat);
पूर्ण

अटल पूर्णांक ehl_sgmii_data(काष्ठा pci_dev *pdev,
			  काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->bus_id = 1;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;

	plat->serdes_घातerup = पूर्णांकel_serdes_घातerup;
	plat->serdes_घातerकरोwn = पूर्णांकel_serdes_घातerकरोwn;

	वापस ehl_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info ehl_sgmii1g_info = अणु
	.setup = ehl_sgmii_data,
पूर्ण;

अटल पूर्णांक ehl_rgmii_data(काष्ठा pci_dev *pdev,
			  काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->bus_id = 1;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;

	वापस ehl_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info ehl_rgmii1g_info = अणु
	.setup = ehl_rgmii_data,
पूर्ण;

अटल पूर्णांक ehl_pse0_common_data(काष्ठा pci_dev *pdev,
				काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv = plat->bsp_priv;

	पूर्णांकel_priv->is_pse = true;
	plat->bus_id = 2;
	plat->addr64 = 32;

	पूर्णांकel_mgbe_pse_crossts_adj(पूर्णांकel_priv, EHL_PSE_ART_MHZ);

	वापस ehl_common_data(pdev, plat);
पूर्ण

अटल पूर्णांक ehl_pse0_rgmii1g_data(काष्ठा pci_dev *pdev,
				 काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_ID;
	वापस ehl_pse0_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info ehl_pse0_rgmii1g_info = अणु
	.setup = ehl_pse0_rgmii1g_data,
पूर्ण;

अटल पूर्णांक ehl_pse0_sgmii1g_data(काष्ठा pci_dev *pdev,
				 काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
	plat->serdes_घातerup = पूर्णांकel_serdes_घातerup;
	plat->serdes_घातerकरोwn = पूर्णांकel_serdes_घातerकरोwn;
	वापस ehl_pse0_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info ehl_pse0_sgmii1g_info = अणु
	.setup = ehl_pse0_sgmii1g_data,
पूर्ण;

अटल पूर्णांक ehl_pse1_common_data(काष्ठा pci_dev *pdev,
				काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv = plat->bsp_priv;

	पूर्णांकel_priv->is_pse = true;
	plat->bus_id = 3;
	plat->addr64 = 32;

	पूर्णांकel_mgbe_pse_crossts_adj(पूर्णांकel_priv, EHL_PSE_ART_MHZ);

	वापस ehl_common_data(pdev, plat);
पूर्ण

अटल पूर्णांक ehl_pse1_rgmii1g_data(काष्ठा pci_dev *pdev,
				 काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_ID;
	वापस ehl_pse1_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info ehl_pse1_rgmii1g_info = अणु
	.setup = ehl_pse1_rgmii1g_data,
पूर्ण;

अटल पूर्णांक ehl_pse1_sgmii1g_data(काष्ठा pci_dev *pdev,
				 काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
	plat->serdes_घातerup = पूर्णांकel_serdes_घातerup;
	plat->serdes_घातerकरोwn = पूर्णांकel_serdes_घातerकरोwn;
	वापस ehl_pse1_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info ehl_pse1_sgmii1g_info = अणु
	.setup = ehl_pse1_sgmii1g_data,
पूर्ण;

अटल पूर्णांक tgl_common_data(काष्ठा pci_dev *pdev,
			   काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->rx_queues_to_use = 6;
	plat->tx_queues_to_use = 4;
	plat->clk_ptp_rate = 200000000;

	वापस पूर्णांकel_mgbe_common_data(pdev, plat);
पूर्ण

अटल पूर्णांक tgl_sgmii_phy0_data(काष्ठा pci_dev *pdev,
			       काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->bus_id = 1;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
	plat->serdes_घातerup = पूर्णांकel_serdes_घातerup;
	plat->serdes_घातerकरोwn = पूर्णांकel_serdes_घातerकरोwn;
	वापस tgl_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info tgl_sgmii1g_phy0_info = अणु
	.setup = tgl_sgmii_phy0_data,
पूर्ण;

अटल पूर्णांक tgl_sgmii_phy1_data(काष्ठा pci_dev *pdev,
			       काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->bus_id = 2;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
	plat->serdes_घातerup = पूर्णांकel_serdes_घातerup;
	plat->serdes_घातerकरोwn = पूर्णांकel_serdes_घातerकरोwn;
	वापस tgl_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info tgl_sgmii1g_phy1_info = अणु
	.setup = tgl_sgmii_phy1_data,
पूर्ण;

अटल पूर्णांक adls_sgmii_phy0_data(काष्ठा pci_dev *pdev,
				काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->bus_id = 1;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;

	/* SerDes घातer up and घातer करोwn are करोne in BIOS क्रम ADL */

	वापस tgl_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info adls_sgmii1g_phy0_info = अणु
	.setup = adls_sgmii_phy0_data,
पूर्ण;

अटल पूर्णांक adls_sgmii_phy1_data(काष्ठा pci_dev *pdev,
				काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->bus_id = 2;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;

	/* SerDes घातer up and घातer करोwn are करोne in BIOS क्रम ADL */

	वापस tgl_common_data(pdev, plat);
पूर्ण

अटल काष्ठा sपंचांगmac_pci_info adls_sgmii1g_phy1_info = अणु
	.setup = adls_sgmii_phy1_data,
पूर्ण;
अटल स्थिर काष्ठा sपंचांगmac_pci_func_data galileo_sपंचांगmac_func_data[] = अणु
	अणु
		.func = 6,
		.phy_addr = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांगmac_pci_dmi_data galileo_sपंचांगmac_dmi_data = अणु
	.func = galileo_sपंचांगmac_func_data,
	.nfuncs = ARRAY_SIZE(galileo_sपंचांगmac_func_data),
पूर्ण;

अटल स्थिर काष्ठा sपंचांगmac_pci_func_data iot2040_sपंचांगmac_func_data[] = अणु
	अणु
		.func = 6,
		.phy_addr = 1,
	पूर्ण,
	अणु
		.func = 7,
		.phy_addr = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांगmac_pci_dmi_data iot2040_sपंचांगmac_dmi_data = अणु
	.func = iot2040_sपंचांगmac_func_data,
	.nfuncs = ARRAY_SIZE(iot2040_sपंचांगmac_func_data),
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id quark_pci_dmi[] = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Galileo"),
		पूर्ण,
		.driver_data = (व्योम *)&galileo_sपंचांगmac_dmi_data,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "GalileoGen2"),
		पूर्ण,
		.driver_data = (व्योम *)&galileo_sपंचांगmac_dmi_data,
	पूर्ण,
	/* There are 2 types of SIMATIC IOT2000: IOT2020 and IOT2040.
	 * The asset tag "6ES7647-0AA00-0YA2" is only क्रम IOT2020 which
	 * has only one pci network device जबतक other asset tags are
	 * क्रम IOT2040 which has two.
	 */
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "SIMATIC IOT2000"),
			DMI_EXACT_MATCH(DMI_BOARD_ASSET_TAG,
					"6ES7647-0AA00-0YA2"),
		पूर्ण,
		.driver_data = (व्योम *)&galileo_sपंचांगmac_dmi_data,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "SIMATIC IOT2000"),
		पूर्ण,
		.driver_data = (व्योम *)&iot2040_sपंचांगmac_dmi_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक quark_शेष_data(काष्ठा pci_dev *pdev,
			      काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	पूर्णांक ret;

	/* Set common शेष data first */
	common_शेष_data(plat);

	/* Refuse to load the driver and रेजिस्टर net device अगर MAC controller
	 * करोes not connect to any PHY पूर्णांकerface.
	 */
	ret = sपंचांगmac_pci_find_phy_addr(pdev, quark_pci_dmi);
	अगर (ret < 0) अणु
		/* Return error to the caller on DMI enabled boards. */
		अगर (dmi_get_प्रणाली_info(DMI_BOARD_NAME))
			वापस ret;

		/* Galileo boards with old firmware करोn't support DMI. We always
		 * use 1 here as PHY address, so at least the first found MAC
		 * controller would be probed.
		 */
		ret = 1;
	पूर्ण

	plat->bus_id = pci_dev_id(pdev);
	plat->phy_addr = ret;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_RMII;

	plat->dma_cfg->pbl = 16;
	plat->dma_cfg->pblx8 = true;
	plat->dma_cfg->fixed_burst = 1;
	/* AXI (TODO) */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_pci_info quark_info = अणु
	.setup = quark_शेष_data,
पूर्ण;

अटल पूर्णांक sपंचांगmac_config_single_msi(काष्ठा pci_dev *pdev,
				    काष्ठा plat_sपंचांगmacenet_data *plat,
				    काष्ठा sपंचांगmac_resources *res)
अणु
	पूर्णांक ret;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0) अणु
		dev_info(&pdev->dev, "%s: Single IRQ enablement failed\n",
			 __func__);
		वापस ret;
	पूर्ण

	res->irq = pci_irq_vector(pdev, 0);
	res->wol_irq = res->irq;
	plat->multi_msi_en = 0;
	dev_info(&pdev->dev, "%s: Single IRQ enablement successful\n",
		 __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_config_multi_msi(काष्ठा pci_dev *pdev,
				   काष्ठा plat_sपंचांगmacenet_data *plat,
				   काष्ठा sपंचांगmac_resources *res)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	अगर (plat->msi_rx_base_vec >= STMMAC_MSI_VEC_MAX ||
	    plat->msi_tx_base_vec >= STMMAC_MSI_VEC_MAX) अणु
		dev_info(&pdev->dev, "%s: Invalid RX & TX vector defined\n",
			 __func__);
		वापस -1;
	पूर्ण

	ret = pci_alloc_irq_vectors(pdev, 2, STMMAC_MSI_VEC_MAX,
				    PCI_IRQ_MSI | PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_info(&pdev->dev, "%s: multi MSI enablement failed\n",
			 __func__);
		वापस ret;
	पूर्ण

	/* For RX MSI */
	क्रम (i = 0; i < plat->rx_queues_to_use; i++) अणु
		res->rx_irq[i] = pci_irq_vector(pdev,
						plat->msi_rx_base_vec + i * 2);
	पूर्ण

	/* For TX MSI */
	क्रम (i = 0; i < plat->tx_queues_to_use; i++) अणु
		res->tx_irq[i] = pci_irq_vector(pdev,
						plat->msi_tx_base_vec + i * 2);
	पूर्ण

	अगर (plat->msi_mac_vec < STMMAC_MSI_VEC_MAX)
		res->irq = pci_irq_vector(pdev, plat->msi_mac_vec);
	अगर (plat->msi_wol_vec < STMMAC_MSI_VEC_MAX)
		res->wol_irq = pci_irq_vector(pdev, plat->msi_wol_vec);
	अगर (plat->msi_lpi_vec < STMMAC_MSI_VEC_MAX)
		res->lpi_irq = pci_irq_vector(pdev, plat->msi_lpi_vec);
	अगर (plat->msi_sfty_ce_vec < STMMAC_MSI_VEC_MAX)
		res->sfty_ce_irq = pci_irq_vector(pdev, plat->msi_sfty_ce_vec);
	अगर (plat->msi_sfty_ue_vec < STMMAC_MSI_VEC_MAX)
		res->sfty_ue_irq = pci_irq_vector(pdev, plat->msi_sfty_ue_vec);

	plat->multi_msi_en = 1;
	dev_info(&pdev->dev, "%s: multi MSI enablement successful\n", __func__);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_eth_pci_probe
 *
 * @pdev: pci device poपूर्णांकer
 * @id: poपूर्णांकer to table of device id/id's.
 *
 * Description: This probing function माला_लो called क्रम all PCI devices which
 * match the ID table and are not "owned" by other driver yet. This function
 * माला_लो passed a "struct pci_dev *" क्रम each device whose entry in the ID table
 * matches the device. The probe functions वापसs zero when the driver choose
 * to take "ownership" of the device or an error code(-ve no) otherwise.
 */
अटल पूर्णांक पूर्णांकel_eth_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा sपंचांगmac_pci_info *info = (काष्ठा sपंचांगmac_pci_info *)id->driver_data;
	काष्ठा पूर्णांकel_priv_data *पूर्णांकel_priv;
	काष्ठा plat_sपंचांगmacenet_data *plat;
	काष्ठा sपंचांगmac_resources res;
	पूर्णांक ret;

	पूर्णांकel_priv = devm_kzalloc(&pdev->dev, माप(*पूर्णांकel_priv), GFP_KERNEL);
	अगर (!पूर्णांकel_priv)
		वापस -ENOMEM;

	plat = devm_kzalloc(&pdev->dev, माप(*plat), GFP_KERNEL);
	अगर (!plat)
		वापस -ENOMEM;

	plat->mdio_bus_data = devm_kzalloc(&pdev->dev,
					   माप(*plat->mdio_bus_data),
					   GFP_KERNEL);
	अगर (!plat->mdio_bus_data)
		वापस -ENOMEM;

	plat->dma_cfg = devm_kzalloc(&pdev->dev, माप(*plat->dma_cfg),
				     GFP_KERNEL);
	अगर (!plat->dma_cfg)
		वापस -ENOMEM;

	/* Enable pci device */
	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: ERROR: failed to enable device\n",
			__func__);
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, BIT(0), pci_name(pdev));
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	plat->bsp_priv = पूर्णांकel_priv;
	पूर्णांकel_priv->mdio_adhoc_addr = INTEL_MGBE_ADHOC_ADDR;
	पूर्णांकel_priv->crossts_adj = 1;

	/* Initialize all MSI vectors to invalid so that it can be set
	 * according to platक्रमm data settings below.
	 * Note: MSI vector takes value from 0 upto 31 (STMMAC_MSI_VEC_MAX)
	 */
	plat->msi_mac_vec = STMMAC_MSI_VEC_MAX;
	plat->msi_wol_vec = STMMAC_MSI_VEC_MAX;
	plat->msi_lpi_vec = STMMAC_MSI_VEC_MAX;
	plat->msi_sfty_ce_vec = STMMAC_MSI_VEC_MAX;
	plat->msi_sfty_ue_vec = STMMAC_MSI_VEC_MAX;
	plat->msi_rx_base_vec = STMMAC_MSI_VEC_MAX;
	plat->msi_tx_base_vec = STMMAC_MSI_VEC_MAX;

	ret = info->setup(pdev, plat);
	अगर (ret)
		वापस ret;

	स_रखो(&res, 0, माप(res));
	res.addr = pcim_iomap_table(pdev)[0];

	अगर (plat->eee_usecs_rate > 0) अणु
		u32 tx_lpi_usec;

		tx_lpi_usec = (plat->eee_usecs_rate / 1000000) - 1;
		ग_लिखोl(tx_lpi_usec, res.addr + GMAC_1US_TIC_COUNTER);
	पूर्ण

	ret = sपंचांगmac_config_multi_msi(pdev, plat, &res);
	अगर (ret) अणु
		ret = sपंचांगmac_config_single_msi(pdev, plat, &res);
		अगर (ret) अणु
			dev_err(&pdev->dev, "%s: ERROR: failed to enable IRQ\n",
				__func__);
			जाओ err_alloc_irq;
		पूर्ण
	पूर्ण

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat, &res);
	अगर (ret) अणु
		जाओ err_dvr_probe;
	पूर्ण

	वापस 0;

err_dvr_probe:
	pci_मुक्त_irq_vectors(pdev);
err_alloc_irq:
	clk_disable_unprepare(plat->sपंचांगmac_clk);
	clk_unरेजिस्टर_fixed_rate(plat->sपंचांगmac_clk);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_eth_pci_हटाओ
 *
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: this function calls the मुख्य to मुक्त the net resources
 * and releases the PCI resources.
 */
अटल व्योम पूर्णांकel_eth_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(&pdev->dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	sपंचांगmac_dvr_हटाओ(&pdev->dev);

	clk_unरेजिस्टर_fixed_rate(priv->plat->sपंचांगmac_clk);

	pcim_iounmap_regions(pdev, BIT(0));
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_eth_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;

	ret = sपंचांगmac_suspend(dev);
	अगर (ret)
		वापस ret;

	ret = pci_save_state(pdev);
	अगर (ret)
		वापस ret;

	pci_wake_from_d3(pdev, true);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_eth_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;

	pci_restore_state(pdev);
	pci_set_घातer_state(pdev, PCI_D0);

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	वापस sपंचांगmac_resume(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पूर्णांकel_eth_pm_ops, पूर्णांकel_eth_pci_suspend,
			 पूर्णांकel_eth_pci_resume);

#घोषणा PCI_DEVICE_ID_INTEL_QUARK		0x0937
#घोषणा PCI_DEVICE_ID_INTEL_EHL_RGMII1G		0x4b30
#घोषणा PCI_DEVICE_ID_INTEL_EHL_SGMII1G		0x4b31
#घोषणा PCI_DEVICE_ID_INTEL_EHL_SGMII2G5	0x4b32
/* Intel(R) Programmable Services Engine (Intel(R) PSE) consist of 2 MAC
 * which are named PSE0 and PSE1
 */
#घोषणा PCI_DEVICE_ID_INTEL_EHL_PSE0_RGMII1G	0x4ba0
#घोषणा PCI_DEVICE_ID_INTEL_EHL_PSE0_SGMII1G	0x4ba1
#घोषणा PCI_DEVICE_ID_INTEL_EHL_PSE0_SGMII2G5	0x4ba2
#घोषणा PCI_DEVICE_ID_INTEL_EHL_PSE1_RGMII1G	0x4bb0
#घोषणा PCI_DEVICE_ID_INTEL_EHL_PSE1_SGMII1G	0x4bb1
#घोषणा PCI_DEVICE_ID_INTEL_EHL_PSE1_SGMII2G5	0x4bb2
#घोषणा PCI_DEVICE_ID_INTEL_TGLH_SGMII1G_0	0x43ac
#घोषणा PCI_DEVICE_ID_INTEL_TGLH_SGMII1G_1	0x43a2
#घोषणा PCI_DEVICE_ID_INTEL_TGL_SGMII1G		0xa0ac
#घोषणा PCI_DEVICE_ID_INTEL_ADLS_SGMII1G_0	0x7aac
#घोषणा PCI_DEVICE_ID_INTEL_ADLS_SGMII1G_1	0x7aad

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_eth_pci_id_table[] = अणु
	अणु PCI_DEVICE_DATA(INTEL, QUARK, &quark_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_RGMII1G, &ehl_rgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_SGMII1G, &ehl_sgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_SGMII2G5, &ehl_sgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_PSE0_RGMII1G, &ehl_pse0_rgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_PSE0_SGMII1G, &ehl_pse0_sgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_PSE0_SGMII2G5, &ehl_pse0_sgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_PSE1_RGMII1G, &ehl_pse1_rgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_PSE1_SGMII1G, &ehl_pse1_sgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_PSE1_SGMII2G5, &ehl_pse1_sgmii1g_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, TGL_SGMII1G, &tgl_sgmii1g_phy0_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, TGLH_SGMII1G_0, &tgl_sgmii1g_phy0_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, TGLH_SGMII1G_1, &tgl_sgmii1g_phy1_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, ADLS_SGMII1G_0, &adls_sgmii1g_phy0_info) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, ADLS_SGMII1G_1, &adls_sgmii1g_phy1_info) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, पूर्णांकel_eth_pci_id_table);

अटल काष्ठा pci_driver पूर्णांकel_eth_pci_driver = अणु
	.name = "intel-eth-pci",
	.id_table = पूर्णांकel_eth_pci_id_table,
	.probe = पूर्णांकel_eth_pci_probe,
	.हटाओ = पूर्णांकel_eth_pci_हटाओ,
	.driver         = अणु
		.pm     = &पूर्णांकel_eth_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(पूर्णांकel_eth_pci_driver);

MODULE_DESCRIPTION("INTEL 10/100/1000 Ethernet PCI driver");
MODULE_AUTHOR("Voon Weifeng <weifeng.voon@intel.com>");
MODULE_LICENSE("GPL v2");
