<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014-2015 Broadcom Corporation
 */

#अगर_अघोषित _PCIE_IPROC_H
#घोषणा _PCIE_IPROC_H

/**
 * iProc PCIe पूर्णांकerface type
 *
 * PAXB is the wrapper used in root complex that can be connected to an
 * बाह्यal endpoपूर्णांक device.
 *
 * PAXC is the wrapper used in root complex dedicated क्रम पूर्णांकernal emulated
 * endpoपूर्णांक devices.
 */
क्रमागत iproc_pcie_type अणु
	IPROC_PCIE_PAXB_BCMA = 0,
	IPROC_PCIE_PAXB,
	IPROC_PCIE_PAXB_V2,
	IPROC_PCIE_PAXC,
	IPROC_PCIE_PAXC_V2,
पूर्ण;

/**
 * iProc PCIe outbound mapping
 * @axi_offset: offset from the AXI address to the पूर्णांकernal address used by
 * the iProc PCIe core
 * @nr_winकरोws: total number of supported outbound mapping winकरोws
 */
काष्ठा iproc_pcie_ob अणु
	resource_माप_प्रकार axi_offset;
	अचिन्हित पूर्णांक nr_winकरोws;
पूर्ण;

/**
 * iProc PCIe inbound mapping
 * @nr_regions: total number of supported inbound mapping regions
 */
काष्ठा iproc_pcie_ib अणु
	अचिन्हित पूर्णांक nr_regions;
पूर्ण;

काष्ठा iproc_pcie_ob_map;
काष्ठा iproc_pcie_ib_map;
काष्ठा iproc_msi;

/**
 * iProc PCIe device
 *
 * @dev: poपूर्णांकer to device data काष्ठाure
 * @type: iProc PCIe पूर्णांकerface type
 * @reg_offsets: रेजिस्टर offsets
 * @base: PCIe host controller I/O रेजिस्टर base
 * @base_addr: PCIe host controller रेजिस्टर base physical address
 * @phy: optional PHY device that controls the Serdes
 * @map_irq: function callback to map पूर्णांकerrupts
 * @ep_is_पूर्णांकernal: indicates an पूर्णांकernal emulated endpoपूर्णांक device is connected
 * @iproc_cfg_पढ़ो: indicates the iProc config पढ़ो function should be used
 * @rej_unconfig_pf: indicates the root complex needs to detect and reject
 * क्रमागतeration against unconfigured physical functions emulated in the ASIC
 * @has_apb_err_disable: indicates the controller can be configured to prevent
 * unsupported request from being क्रमwarded as an APB bus error
 * @fix_paxc_cap: indicates the controller has corrupted capability list in its
 * config space रेजिस्टरs and requires SW based fixup
 *
 * @need_ob_cfg: indicates SW needs to configure the outbound mapping winकरोw
 * @ob: outbound mapping related parameters
 * @ob_map: outbound mapping related parameters specअगरic to the controller
 *
 * @need_ib_cfg: indicates SW needs to configure the inbound mapping winकरोw
 * @ib: inbound mapping related parameters
 * @ib_map: outbound mapping region related parameters
 *
 * @need_msi_steer: indicates additional configuration of the iProc PCIe
 * controller is required to steer MSI ग_लिखोs to बाह्यal पूर्णांकerrupt controller
 * @msi: MSI data
 */
काष्ठा iproc_pcie अणु
	काष्ठा device *dev;
	क्रमागत iproc_pcie_type type;
	u16 *reg_offsets;
	व्योम __iomem *base;
	phys_addr_t base_addr;
	काष्ठा resource mem;
	काष्ठा phy *phy;
	पूर्णांक (*map_irq)(स्थिर काष्ठा pci_dev *, u8, u8);
	bool ep_is_पूर्णांकernal;
	bool iproc_cfg_पढ़ो;
	bool rej_unconfig_pf;
	bool has_apb_err_disable;
	bool fix_paxc_cap;

	bool need_ob_cfg;
	काष्ठा iproc_pcie_ob ob;
	स्थिर काष्ठा iproc_pcie_ob_map *ob_map;

	bool need_ib_cfg;
	काष्ठा iproc_pcie_ib ib;
	स्थिर काष्ठा iproc_pcie_ib_map *ib_map;

	bool need_msi_steer;
	काष्ठा iproc_msi *msi;
पूर्ण;

पूर्णांक iproc_pcie_setup(काष्ठा iproc_pcie *pcie, काष्ठा list_head *res);
पूर्णांक iproc_pcie_हटाओ(काष्ठा iproc_pcie *pcie);
पूर्णांक iproc_pcie_shutकरोwn(काष्ठा iproc_pcie *pcie);

#अगर_घोषित CONFIG_PCIE_IPROC_MSI
पूर्णांक iproc_msi_init(काष्ठा iproc_pcie *pcie, काष्ठा device_node *node);
व्योम iproc_msi_निकास(काष्ठा iproc_pcie *pcie);
#अन्यथा
अटल अंतरभूत पूर्णांक iproc_msi_init(काष्ठा iproc_pcie *pcie,
				 काष्ठा device_node *node)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम iproc_msi_निकास(काष्ठा iproc_pcie *pcie)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _PCIE_IPROC_H */
