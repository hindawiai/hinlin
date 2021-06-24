<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This contains the functions to handle the platक्रमm driver.

  Copyright (C) 2007-2011  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

#अगर_घोषित CONFIG_OF

/**
 * dwmac1000_validate_mcast_bins - validates the number of Multicast filter bins
 * @dev: काष्ठा device of the platक्रमm device
 * @mcast_bins: Multicast filtering bins
 * Description:
 * this function validates the number of Multicast filtering bins specअगरied
 * by the configuration through the device tree. The Synopsys GMAC supports
 * 64 bins, 128 bins, or 256 bins. "bins" refer to the भागision of CRC
 * number space. 64 bins correspond to 6 bits of the CRC, 128 corresponds
 * to 7 bits, and 256 refers to 8 bits of the CRC. Any other setting is
 * invalid and will cause the filtering algorithm to use Multicast
 * promiscuous mode.
 */
अटल पूर्णांक dwmac1000_validate_mcast_bins(काष्ठा device *dev, पूर्णांक mcast_bins)
अणु
	पूर्णांक x = mcast_bins;

	चयन (x) अणु
	हाल HASH_TABLE_SIZE:
	हाल 128:
	हाल 256:
		अवरोध;
	शेष:
		x = 0;
		dev_info(dev, "Hash table entries set to unexpected value %d\n",
			 mcast_bins);
		अवरोध;
	पूर्ण
	वापस x;
पूर्ण

/**
 * dwmac1000_validate_ucast_entries - validate the Unicast address entries
 * @dev: काष्ठा device of the platक्रमm device
 * @ucast_entries: number of Unicast address entries
 * Description:
 * This function validates the number of Unicast address entries supported
 * by a particular Synopsys 10/100/1000 controller. The Synopsys controller
 * supports 1..32, 64, or 128 Unicast filter entries क्रम it's Unicast filter
 * logic. This function validates a valid, supported configuration is
 * selected, and शेषs to 1 Unicast address अगर an unsupported
 * configuration is selected.
 */
अटल पूर्णांक dwmac1000_validate_ucast_entries(काष्ठा device *dev,
					    पूर्णांक ucast_entries)
अणु
	पूर्णांक x = ucast_entries;

	चयन (x) अणु
	हाल 1 ... 32:
	हाल 64:
	हाल 128:
		अवरोध;
	शेष:
		x = 1;
		dev_info(dev, "Unicast table entries set to unexpected value %d\n",
			 ucast_entries);
		अवरोध;
	पूर्ण
	वापस x;
पूर्ण

/**
 * sपंचांगmac_axi_setup - parse DT parameters क्रम programming the AXI रेजिस्टर
 * @pdev: platक्रमm device
 * Description:
 * अगर required, from device-tree the AXI पूर्णांकernal रेजिस्टर can be tuned
 * by using platक्रमm parameters.
 */
अटल काष्ठा sपंचांगmac_axi *sपंचांगmac_axi_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	काष्ठा sपंचांगmac_axi *axi;

	np = of_parse_phandle(pdev->dev.of_node, "snps,axi-config", 0);
	अगर (!np)
		वापस शून्य;

	axi = devm_kzalloc(&pdev->dev, माप(*axi), GFP_KERNEL);
	अगर (!axi) अणु
		of_node_put(np);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	axi->axi_lpi_en = of_property_पढ़ो_bool(np, "snps,lpi_en");
	axi->axi_xit_frm = of_property_पढ़ो_bool(np, "snps,xit_frm");
	axi->axi_kbbe = of_property_पढ़ो_bool(np, "snps,axi_kbbe");
	axi->axi_fb = of_property_पढ़ो_bool(np, "snps,axi_fb");
	axi->axi_mb = of_property_पढ़ो_bool(np, "snps,axi_mb");
	axi->axi_rb =  of_property_पढ़ो_bool(np, "snps,axi_rb");

	अगर (of_property_पढ़ो_u32(np, "snps,wr_osr_lmt", &axi->axi_wr_osr_lmt))
		axi->axi_wr_osr_lmt = 1;
	अगर (of_property_पढ़ो_u32(np, "snps,rd_osr_lmt", &axi->axi_rd_osr_lmt))
		axi->axi_rd_osr_lmt = 1;
	of_property_पढ़ो_u32_array(np, "snps,blen", axi->axi_blen, AXI_BLEN);
	of_node_put(np);

	वापस axi;
पूर्ण

/**
 * sपंचांगmac_mtl_setup - parse DT parameters क्रम multiple queues configuration
 * @pdev: platक्रमm device
 * @plat: enet data
 */
अटल पूर्णांक sपंचांगmac_mtl_setup(काष्ठा platक्रमm_device *pdev,
			    काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	काष्ठा device_node *q_node;
	काष्ठा device_node *rx_node;
	काष्ठा device_node *tx_node;
	u8 queue = 0;
	पूर्णांक ret = 0;

	/* For backwards-compatibility with device trees that करोn't have any
	 * snps,mtl-rx-config or snps,mtl-tx-config properties, we fall back
	 * to one RX and TX queues each.
	 */
	plat->rx_queues_to_use = 1;
	plat->tx_queues_to_use = 1;

	/* First Queue must always be in DCB mode. As MTL_QUEUE_DCB = 1 we need
	 * to always set this, otherwise Queue will be classअगरied as AVB
	 * (because MTL_QUEUE_AVB = 0).
	 */
	plat->rx_queues_cfg[0].mode_to_use = MTL_QUEUE_DCB;
	plat->tx_queues_cfg[0].mode_to_use = MTL_QUEUE_DCB;

	rx_node = of_parse_phandle(pdev->dev.of_node, "snps,mtl-rx-config", 0);
	अगर (!rx_node)
		वापस ret;

	tx_node = of_parse_phandle(pdev->dev.of_node, "snps,mtl-tx-config", 0);
	अगर (!tx_node) अणु
		of_node_put(rx_node);
		वापस ret;
	पूर्ण

	/* Processing RX queues common config */
	अगर (of_property_पढ़ो_u32(rx_node, "snps,rx-queues-to-use",
				 &plat->rx_queues_to_use))
		plat->rx_queues_to_use = 1;

	अगर (of_property_पढ़ो_bool(rx_node, "snps,rx-sched-sp"))
		plat->rx_sched_algorithm = MTL_RX_ALGORITHM_SP;
	अन्यथा अगर (of_property_पढ़ो_bool(rx_node, "snps,rx-sched-wsp"))
		plat->rx_sched_algorithm = MTL_RX_ALGORITHM_WSP;
	अन्यथा
		plat->rx_sched_algorithm = MTL_RX_ALGORITHM_SP;

	/* Processing inभागidual RX queue config */
	क्रम_each_child_of_node(rx_node, q_node) अणु
		अगर (queue >= plat->rx_queues_to_use)
			अवरोध;

		अगर (of_property_पढ़ो_bool(q_node, "snps,dcb-algorithm"))
			plat->rx_queues_cfg[queue].mode_to_use = MTL_QUEUE_DCB;
		अन्यथा अगर (of_property_पढ़ो_bool(q_node, "snps,avb-algorithm"))
			plat->rx_queues_cfg[queue].mode_to_use = MTL_QUEUE_AVB;
		अन्यथा
			plat->rx_queues_cfg[queue].mode_to_use = MTL_QUEUE_DCB;

		अगर (of_property_पढ़ो_u32(q_node, "snps,map-to-dma-channel",
					 &plat->rx_queues_cfg[queue].chan))
			plat->rx_queues_cfg[queue].chan = queue;
		/* TODO: Dynamic mapping to be included in the future */

		अगर (of_property_पढ़ो_u32(q_node, "snps,priority",
					&plat->rx_queues_cfg[queue].prio)) अणु
			plat->rx_queues_cfg[queue].prio = 0;
			plat->rx_queues_cfg[queue].use_prio = false;
		पूर्ण अन्यथा अणु
			plat->rx_queues_cfg[queue].use_prio = true;
		पूर्ण

		/* RX queue specअगरic packet type routing */
		अगर (of_property_पढ़ो_bool(q_node, "snps,route-avcp"))
			plat->rx_queues_cfg[queue].pkt_route = PACKET_AVCPQ;
		अन्यथा अगर (of_property_पढ़ो_bool(q_node, "snps,route-ptp"))
			plat->rx_queues_cfg[queue].pkt_route = PACKET_PTPQ;
		अन्यथा अगर (of_property_पढ़ो_bool(q_node, "snps,route-dcbcp"))
			plat->rx_queues_cfg[queue].pkt_route = PACKET_DCBCPQ;
		अन्यथा अगर (of_property_पढ़ो_bool(q_node, "snps,route-up"))
			plat->rx_queues_cfg[queue].pkt_route = PACKET_UPQ;
		अन्यथा अगर (of_property_पढ़ो_bool(q_node, "snps,route-multi-broad"))
			plat->rx_queues_cfg[queue].pkt_route = PACKET_MCBCQ;
		अन्यथा
			plat->rx_queues_cfg[queue].pkt_route = 0x0;

		queue++;
	पूर्ण
	अगर (queue != plat->rx_queues_to_use) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "Not all RX queues were configured\n");
		जाओ out;
	पूर्ण

	/* Processing TX queues common config */
	अगर (of_property_पढ़ो_u32(tx_node, "snps,tx-queues-to-use",
				 &plat->tx_queues_to_use))
		plat->tx_queues_to_use = 1;

	अगर (of_property_पढ़ो_bool(tx_node, "snps,tx-sched-wrr"))
		plat->tx_sched_algorithm = MTL_TX_ALGORITHM_WRR;
	अन्यथा अगर (of_property_पढ़ो_bool(tx_node, "snps,tx-sched-wfq"))
		plat->tx_sched_algorithm = MTL_TX_ALGORITHM_WFQ;
	अन्यथा अगर (of_property_पढ़ो_bool(tx_node, "snps,tx-sched-dwrr"))
		plat->tx_sched_algorithm = MTL_TX_ALGORITHM_DWRR;
	अन्यथा अगर (of_property_पढ़ो_bool(tx_node, "snps,tx-sched-sp"))
		plat->tx_sched_algorithm = MTL_TX_ALGORITHM_SP;
	अन्यथा
		plat->tx_sched_algorithm = MTL_TX_ALGORITHM_SP;

	queue = 0;

	/* Processing inभागidual TX queue config */
	क्रम_each_child_of_node(tx_node, q_node) अणु
		अगर (queue >= plat->tx_queues_to_use)
			अवरोध;

		अगर (of_property_पढ़ो_u32(q_node, "snps,weight",
					 &plat->tx_queues_cfg[queue].weight))
			plat->tx_queues_cfg[queue].weight = 0x10 + queue;

		अगर (of_property_पढ़ो_bool(q_node, "snps,dcb-algorithm")) अणु
			plat->tx_queues_cfg[queue].mode_to_use = MTL_QUEUE_DCB;
		पूर्ण अन्यथा अगर (of_property_पढ़ो_bool(q_node,
						 "snps,avb-algorithm")) अणु
			plat->tx_queues_cfg[queue].mode_to_use = MTL_QUEUE_AVB;

			/* Credit Base Shaper parameters used by AVB */
			अगर (of_property_पढ़ो_u32(q_node, "snps,send_slope",
				&plat->tx_queues_cfg[queue].send_slope))
				plat->tx_queues_cfg[queue].send_slope = 0x0;
			अगर (of_property_पढ़ो_u32(q_node, "snps,idle_slope",
				&plat->tx_queues_cfg[queue].idle_slope))
				plat->tx_queues_cfg[queue].idle_slope = 0x0;
			अगर (of_property_पढ़ो_u32(q_node, "snps,high_credit",
				&plat->tx_queues_cfg[queue].high_credit))
				plat->tx_queues_cfg[queue].high_credit = 0x0;
			अगर (of_property_पढ़ो_u32(q_node, "snps,low_credit",
				&plat->tx_queues_cfg[queue].low_credit))
				plat->tx_queues_cfg[queue].low_credit = 0x0;
		पूर्ण अन्यथा अणु
			plat->tx_queues_cfg[queue].mode_to_use = MTL_QUEUE_DCB;
		पूर्ण

		अगर (of_property_पढ़ो_u32(q_node, "snps,priority",
					&plat->tx_queues_cfg[queue].prio)) अणु
			plat->tx_queues_cfg[queue].prio = 0;
			plat->tx_queues_cfg[queue].use_prio = false;
		पूर्ण अन्यथा अणु
			plat->tx_queues_cfg[queue].use_prio = true;
		पूर्ण

		queue++;
	पूर्ण
	अगर (queue != plat->tx_queues_to_use) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "Not all TX queues were configured\n");
		जाओ out;
	पूर्ण

out:
	of_node_put(rx_node);
	of_node_put(tx_node);
	of_node_put(q_node);

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_dt_phy - parse device-tree driver parameters to allocate PHY resources
 * @plat: driver data platक्रमm काष्ठाure
 * @np: device tree node
 * @dev: device poपूर्णांकer
 * Description:
 * The mdio bus will be allocated in हाल of a phy transceiver is on board;
 * it will be शून्य अगर the fixed-link is configured.
 * If there is the "snps,dwmac-mdio" sub-node the mdio will be allocated
 * in any हाल (क्रम DSA, mdio must be रेजिस्टरed even अगर fixed-link).
 * The table below sums the supported configurations:
 *	-------------------------------
 *	snps,phy-addr	|     Y
 *	-------------------------------
 *	phy-handle	|     Y
 *	-------------------------------
 *	fixed-link	|     N
 *	-------------------------------
 *	snps,dwmac-mdio	|
 *	  even अगर	|     Y
 *	fixed-link	|
 *	-------------------------------
 *
 * It वापसs 0 in हाल of success otherwise -ENODEV.
 */
अटल पूर्णांक sपंचांगmac_dt_phy(काष्ठा plat_sपंचांगmacenet_data *plat,
			 काष्ठा device_node *np, काष्ठा device *dev)
अणु
	bool mdio = !of_phy_is_fixed_link(np);
	अटल स्थिर काष्ठा of_device_id need_mdio_ids[] = अणु
		अणु .compatible = "snps,dwc-qos-ethernet-4.10" पूर्ण,
		अणुपूर्ण,
	पूर्ण;

	अगर (of_match_node(need_mdio_ids, np)) अणु
		plat->mdio_node = of_get_child_by_name(np, "mdio");
	पूर्ण अन्यथा अणु
		/**
		 * If snps,dwmac-mdio is passed from DT, always रेजिस्टर
		 * the MDIO
		 */
		क्रम_each_child_of_node(np, plat->mdio_node) अणु
			अगर (of_device_is_compatible(plat->mdio_node,
						    "snps,dwmac-mdio"))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (plat->mdio_node) अणु
		dev_dbg(dev, "Found MDIO subnode\n");
		mdio = true;
	पूर्ण

	अगर (mdio) अणु
		plat->mdio_bus_data =
			devm_kzalloc(dev, माप(काष्ठा sपंचांगmac_mdio_bus_data),
				     GFP_KERNEL);
		अगर (!plat->mdio_bus_data)
			वापस -ENOMEM;

		plat->mdio_bus_data->needs_reset = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sपंचांगmac_of_get_mac_mode - retrieves the पूर्णांकerface of the MAC
 * @np: - device-tree node
 * Description:
 * Similar to `of_get_phy_mode()`, this function will retrieve (from
 * the device-tree) the पूर्णांकerface mode on the MAC side. This assumes
 * that there is mode converter in-between the MAC & PHY
 * (e.g. GMII-to-RGMII).
 */
अटल पूर्णांक sपंचांगmac_of_get_mac_mode(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *pm;
	पूर्णांक err, i;

	err = of_property_पढ़ो_string(np, "mac-mode", &pm);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < PHY_INTERFACE_MODE_MAX; i++) अणु
		अगर (!strहालcmp(pm, phy_modes(i)))
			वापस i;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * sपंचांगmac_probe_config_dt - parse device-tree driver parameters
 * @pdev: platक्रमm_device काष्ठाure
 * @mac: MAC address to use
 * Description:
 * this function is to पढ़ो the driver parameters from device-tree and
 * set some निजी fields that will be used by the मुख्य at runसमय.
 */
काष्ठा plat_sपंचांगmacenet_data *
sपंचांगmac_probe_config_dt(काष्ठा platक्रमm_device *pdev, u8 *mac)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा plat_sपंचांगmacenet_data *plat;
	काष्ठा sपंचांगmac_dma_cfg *dma_cfg;
	व्योम *ret;
	पूर्णांक rc;

	plat = devm_kzalloc(&pdev->dev, माप(*plat), GFP_KERNEL);
	अगर (!plat)
		वापस ERR_PTR(-ENOMEM);

	rc = of_get_mac_address(np, mac);
	अगर (rc) अणु
		अगर (rc == -EPROBE_DEFER)
			वापस ERR_PTR(rc);

		eth_zero_addr(mac);
	पूर्ण

	plat->phy_पूर्णांकerface = device_get_phy_mode(&pdev->dev);
	अगर (plat->phy_पूर्णांकerface < 0)
		वापस ERR_PTR(plat->phy_पूर्णांकerface);

	plat->पूर्णांकerface = sपंचांगmac_of_get_mac_mode(np);
	अगर (plat->पूर्णांकerface < 0)
		plat->पूर्णांकerface = plat->phy_पूर्णांकerface;

	/* Some wrapper drivers still rely on phy_node. Let's save it जबतक
	 * they are not converted to phylink. */
	plat->phy_node = of_parse_phandle(np, "phy-handle", 0);

	/* PHYLINK स्वतःmatically parses the phy-handle property */
	plat->phylink_node = np;

	/* Get max speed of operation from device tree */
	अगर (of_property_पढ़ो_u32(np, "max-speed", &plat->max_speed))
		plat->max_speed = -1;

	plat->bus_id = of_alias_get_id(np, "ethernet");
	अगर (plat->bus_id < 0)
		plat->bus_id = 0;

	/* Default to phy स्वतः-detection */
	plat->phy_addr = -1;

	/* Default to get clk_csr from sपंचांगmac_clk_crs_set(),
	 * or get clk_csr from device tree.
	 */
	plat->clk_csr = -1;
	of_property_पढ़ो_u32(np, "clk_csr", &plat->clk_csr);

	/* "snps,phy-addr" is not a standard property. Mark it as deprecated
	 * and warn of its use. Remove this when phy node support is added.
	 */
	अगर (of_property_पढ़ो_u32(np, "snps,phy-addr", &plat->phy_addr) == 0)
		dev_warn(&pdev->dev, "snps,phy-addr property is deprecated\n");

	/* To Configure PHY by using all device-tree supported properties */
	rc = sपंचांगmac_dt_phy(plat, np, &pdev->dev);
	अगर (rc)
		वापस ERR_PTR(rc);

	of_property_पढ़ो_u32(np, "tx-fifo-depth", &plat->tx_fअगरo_size);

	of_property_पढ़ो_u32(np, "rx-fifo-depth", &plat->rx_fअगरo_size);

	plat->क्रमce_sf_dma_mode =
		of_property_पढ़ो_bool(np, "snps,force_sf_dma_mode");

	plat->en_tx_lpi_घड़ीgating =
		of_property_पढ़ो_bool(np, "snps,en-tx-lpi-clockgating");

	/* Set the maxmtu to a शेष of JUMBO_LEN in हाल the
	 * parameter is not present in the device tree.
	 */
	plat->maxmtu = JUMBO_LEN;

	/* Set शेष value क्रम multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set शेष value क्रम unicast filter entries */
	plat->unicast_filter_entries = 1;

	/*
	 * Currently only the properties needed on SPEAr600
	 * are provided. All other properties should be added
	 * once needed on other platक्रमms.
	 */
	अगर (of_device_is_compatible(np, "st,spear600-gmac") ||
		of_device_is_compatible(np, "snps,dwmac-3.50a") ||
		of_device_is_compatible(np, "snps,dwmac-3.70a") ||
		of_device_is_compatible(np, "snps,dwmac")) अणु
		/* Note that the max-frame-size parameter as defined in the
		 * ePAPR v1.1 spec is defined as max-frame-size, it's
		 * actually used as the IEEE definition of MAC Client
		 * data, or MTU. The ePAPR specअगरication is confusing as
		 * the definition is max-frame-size, but usage examples
		 * are clearly MTUs
		 */
		of_property_पढ़ो_u32(np, "max-frame-size", &plat->maxmtu);
		of_property_पढ़ो_u32(np, "snps,multicast-filter-bins",
				     &plat->multicast_filter_bins);
		of_property_पढ़ो_u32(np, "snps,perfect-filter-entries",
				     &plat->unicast_filter_entries);
		plat->unicast_filter_entries = dwmac1000_validate_ucast_entries(
				&pdev->dev, plat->unicast_filter_entries);
		plat->multicast_filter_bins = dwmac1000_validate_mcast_bins(
				&pdev->dev, plat->multicast_filter_bins);
		plat->has_gmac = 1;
		plat->pmt = 1;
	पूर्ण

	अगर (of_device_is_compatible(np, "snps,dwmac-4.00") ||
	    of_device_is_compatible(np, "snps,dwmac-4.10a") ||
	    of_device_is_compatible(np, "snps,dwmac-4.20a") ||
	    of_device_is_compatible(np, "snps,dwmac-5.10a")) अणु
		plat->has_gmac4 = 1;
		plat->has_gmac = 0;
		plat->pmt = 1;
		plat->tso_en = of_property_पढ़ो_bool(np, "snps,tso");
	पूर्ण

	अगर (of_device_is_compatible(np, "snps,dwmac-3.610") ||
		of_device_is_compatible(np, "snps,dwmac-3.710")) अणु
		plat->enh_desc = 1;
		plat->bugged_jumbo = 1;
		plat->क्रमce_sf_dma_mode = 1;
	पूर्ण

	अगर (of_device_is_compatible(np, "snps,dwxgmac")) अणु
		plat->has_xgmac = 1;
		plat->pmt = 1;
		plat->tso_en = of_property_पढ़ो_bool(np, "snps,tso");
	पूर्ण

	dma_cfg = devm_kzalloc(&pdev->dev, माप(*dma_cfg),
			       GFP_KERNEL);
	अगर (!dma_cfg) अणु
		sपंचांगmac_हटाओ_config_dt(pdev, plat);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	plat->dma_cfg = dma_cfg;

	of_property_पढ़ो_u32(np, "snps,pbl", &dma_cfg->pbl);
	अगर (!dma_cfg->pbl)
		dma_cfg->pbl = DEFAULT_DMA_PBL;
	of_property_पढ़ो_u32(np, "snps,txpbl", &dma_cfg->txpbl);
	of_property_पढ़ो_u32(np, "snps,rxpbl", &dma_cfg->rxpbl);
	dma_cfg->pblx8 = !of_property_पढ़ो_bool(np, "snps,no-pbl-x8");

	dma_cfg->aal = of_property_पढ़ो_bool(np, "snps,aal");
	dma_cfg->fixed_burst = of_property_पढ़ो_bool(np, "snps,fixed-burst");
	dma_cfg->mixed_burst = of_property_पढ़ो_bool(np, "snps,mixed-burst");

	plat->क्रमce_thresh_dma_mode = of_property_पढ़ो_bool(np, "snps,force_thresh_dma_mode");
	अगर (plat->क्रमce_thresh_dma_mode) अणु
		plat->क्रमce_sf_dma_mode = 0;
		dev_warn(&pdev->dev,
			 "force_sf_dma_mode is ignored if force_thresh_dma_mode is set.\n");
	पूर्ण

	of_property_पढ़ो_u32(np, "snps,ps-speed", &plat->mac_port_sel_speed);

	plat->axi = sपंचांगmac_axi_setup(pdev);

	rc = sपंचांगmac_mtl_setup(pdev, plat);
	अगर (rc) अणु
		sपंचांगmac_हटाओ_config_dt(pdev, plat);
		वापस ERR_PTR(rc);
	पूर्ण

	/* घड़ी setup */
	अगर (!of_device_is_compatible(np, "snps,dwc-qos-ethernet-4.10")) अणु
		plat->sपंचांगmac_clk = devm_clk_get(&pdev->dev,
						STMMAC_RESOURCE_NAME);
		अगर (IS_ERR(plat->sपंचांगmac_clk)) अणु
			dev_warn(&pdev->dev, "Cannot get CSR clock\n");
			plat->sपंचांगmac_clk = शून्य;
		पूर्ण
		clk_prepare_enable(plat->sपंचांगmac_clk);
	पूर्ण

	plat->pclk = devm_clk_get_optional(&pdev->dev, "pclk");
	अगर (IS_ERR(plat->pclk)) अणु
		ret = plat->pclk;
		जाओ error_pclk_get;
	पूर्ण
	clk_prepare_enable(plat->pclk);

	/* Fall-back to मुख्य घड़ी in हाल of no PTP ref is passed */
	plat->clk_ptp_ref = devm_clk_get(&pdev->dev, "ptp_ref");
	अगर (IS_ERR(plat->clk_ptp_ref)) अणु
		plat->clk_ptp_rate = clk_get_rate(plat->sपंचांगmac_clk);
		plat->clk_ptp_ref = शून्य;
		dev_info(&pdev->dev, "PTP uses main clock\n");
	पूर्ण अन्यथा अणु
		plat->clk_ptp_rate = clk_get_rate(plat->clk_ptp_ref);
		dev_dbg(&pdev->dev, "PTP rate %d\n", plat->clk_ptp_rate);
	पूर्ण

	plat->sपंचांगmac_rst = devm_reset_control_get_optional(&pdev->dev,
							   STMMAC_RESOURCE_NAME);
	अगर (IS_ERR(plat->sपंचांगmac_rst)) अणु
		ret = plat->sपंचांगmac_rst;
		जाओ error_hw_init;
	पूर्ण

	वापस plat;

error_hw_init:
	clk_disable_unprepare(plat->pclk);
error_pclk_get:
	clk_disable_unprepare(plat->sपंचांगmac_clk);

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_हटाओ_config_dt - unकरो the effects of sपंचांगmac_probe_config_dt()
 * @pdev: platक्रमm_device काष्ठाure
 * @plat: driver data platक्रमm काष्ठाure
 *
 * Release resources claimed by sपंचांगmac_probe_config_dt().
 */
व्योम sपंचांगmac_हटाओ_config_dt(काष्ठा platक्रमm_device *pdev,
			     काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	clk_disable_unprepare(plat->sपंचांगmac_clk);
	clk_disable_unprepare(plat->pclk);
	of_node_put(plat->phy_node);
	of_node_put(plat->mdio_node);
पूर्ण
#अन्यथा
काष्ठा plat_sपंचांगmacenet_data *
sपंचांगmac_probe_config_dt(काष्ठा platक्रमm_device *pdev, u8 *mac)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

व्योम sपंचांगmac_हटाओ_config_dt(काष्ठा platक्रमm_device *pdev,
			     काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */
EXPORT_SYMBOL_GPL(sपंचांगmac_probe_config_dt);
EXPORT_SYMBOL_GPL(sपंचांगmac_हटाओ_config_dt);

पूर्णांक sपंचांगmac_get_platक्रमm_resources(काष्ठा platक्रमm_device *pdev,
				  काष्ठा sपंचांगmac_resources *sपंचांगmac_res)
अणु
	स_रखो(sपंचांगmac_res, 0, माप(*sपंचांगmac_res));

	/* Get IRQ inक्रमmation early to have an ability to ask क्रम deferred
	 * probe अगर needed beक्रमe we went too far with resource allocation.
	 */
	sपंचांगmac_res->irq = platक्रमm_get_irq_byname(pdev, "macirq");
	अगर (sपंचांगmac_res->irq < 0)
		वापस sपंचांगmac_res->irq;

	/* On some platक्रमms e.g. SPEAr the wake up irq dअगरfers from the mac irq
	 * The बाह्यal wake up irq can be passed through the platक्रमm code
	 * named as "eth_wake_irq"
	 *
	 * In हाल the wake up पूर्णांकerrupt is not passed from the platक्रमm
	 * so the driver will जारी to use the mac irq (ndev->irq)
	 */
	sपंचांगmac_res->wol_irq =
		platक्रमm_get_irq_byname_optional(pdev, "eth_wake_irq");
	अगर (sपंचांगmac_res->wol_irq < 0) अणु
		अगर (sपंचांगmac_res->wol_irq == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(&pdev->dev, "IRQ eth_wake_irq not found\n");
		sपंचांगmac_res->wol_irq = sपंचांगmac_res->irq;
	पूर्ण

	sपंचांगmac_res->lpi_irq =
		platक्रमm_get_irq_byname_optional(pdev, "eth_lpi");
	अगर (sपंचांगmac_res->lpi_irq < 0) अणु
		अगर (sपंचांगmac_res->lpi_irq == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(&pdev->dev, "IRQ eth_lpi not found\n");
	पूर्ण

	sपंचांगmac_res->addr = devm_platक्रमm_ioremap_resource(pdev, 0);

	वापस PTR_ERR_OR_ZERO(sपंचांगmac_res->addr);
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_get_platक्रमm_resources);

/**
 * sपंचांगmac_pltfr_हटाओ
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: this function calls the मुख्य to मुक्त the net resources
 * and calls the platक्रमms hook and release the resources (e.g. mem).
 */
पूर्णांक sपंचांगmac_pltfr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा plat_sपंचांगmacenet_data *plat = priv->plat;
	पूर्णांक ret = sपंचांगmac_dvr_हटाओ(&pdev->dev);

	अगर (plat->निकास)
		plat->निकास(pdev, plat->bsp_priv);

	sपंचांगmac_हटाओ_config_dt(pdev, plat);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_pltfr_हटाओ);

/**
 * sपंचांगmac_pltfr_suspend
 * @dev: device poपूर्णांकer
 * Description: this function is invoked when suspend the driver and it direcly
 * call the मुख्य suspend function and then, अगर required, on some platक्रमm, it
 * can call an निकास helper.
 */
अटल पूर्णांक __maybe_unused sपंचांगmac_pltfr_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	ret = sपंचांगmac_suspend(dev);
	अगर (priv->plat->निकास)
		priv->plat->निकास(pdev, priv->plat->bsp_priv);

	वापस ret;
पूर्ण

/**
 * sपंचांगmac_pltfr_resume
 * @dev: device poपूर्णांकer
 * Description: this function is invoked when resume the driver beक्रमe calling
 * the मुख्य resume function, on some platक्रमms, it can call own init helper
 * अगर required.
 */
अटल पूर्णांक __maybe_unused sपंचांगmac_pltfr_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (priv->plat->init)
		priv->plat->init(pdev, priv->plat->bsp_priv);

	वापस sपंचांगmac_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगmac_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	sपंचांगmac_bus_clks_config(priv, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगmac_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	वापस sपंचांगmac_bus_clks_config(priv, true);
पूर्ण

स्थिर काष्ठा dev_pm_ops sपंचांगmac_pltfr_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांगmac_pltfr_suspend, sपंचांगmac_pltfr_resume)
	SET_RUNTIME_PM_OPS(sपंचांगmac_runसमय_suspend, sपंचांगmac_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(sपंचांगmac_pltfr_pm_ops);

MODULE_DESCRIPTION("STMMAC 10/100/1000 Ethernet platform support");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL");
