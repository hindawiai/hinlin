<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright Altera Corporation (C) 2013-2015. All rights reserved
 *
 * Author: Ley Foon Tan <lftan@altera.com>
 * Description: Altera PCIe host controller driver
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "../pci.h"

#घोषणा RP_TX_REG0			0x2000
#घोषणा RP_TX_REG1			0x2004
#घोषणा RP_TX_CNTRL			0x2008
#घोषणा RP_TX_EOP			0x2
#घोषणा RP_TX_SOP			0x1
#घोषणा RP_RXCPL_STATUS			0x2010
#घोषणा RP_RXCPL_EOP			0x2
#घोषणा RP_RXCPL_SOP			0x1
#घोषणा RP_RXCPL_REG0			0x2014
#घोषणा RP_RXCPL_REG1			0x2018
#घोषणा P2A_INT_STATUS			0x3060
#घोषणा P2A_INT_STS_ALL			0xf
#घोषणा P2A_INT_ENABLE			0x3070
#घोषणा P2A_INT_ENA_ALL			0xf
#घोषणा RP_LTSSM			0x3c64
#घोषणा RP_LTSSM_MASK			0x1f
#घोषणा LTSSM_L0			0xf

#घोषणा S10_RP_TX_CNTRL			0x2004
#घोषणा S10_RP_RXCPL_REG		0x2008
#घोषणा S10_RP_RXCPL_STATUS		0x200C
#घोषणा S10_RP_CFG_ADDR(pcie, reg)	\
	(((pcie)->hip_base) + (reg) + (1 << 20))
#घोषणा S10_RP_SECONDARY(pcie)		\
	पढ़ोb(S10_RP_CFG_ADDR(pcie, PCI_SECONDARY_BUS))

/* TLP configuration type 0 and 1 */
#घोषणा TLP_FMTTYPE_CFGRD0		0x04	/* Configuration Read Type 0 */
#घोषणा TLP_FMTTYPE_CFGWR0		0x44	/* Configuration Write Type 0 */
#घोषणा TLP_FMTTYPE_CFGRD1		0x05	/* Configuration Read Type 1 */
#घोषणा TLP_FMTTYPE_CFGWR1		0x45	/* Configuration Write Type 1 */
#घोषणा TLP_PAYLOAD_SIZE		0x01
#घोषणा TLP_READ_TAG			0x1d
#घोषणा TLP_WRITE_TAG			0x10
#घोषणा RP_DEVFN			0
#घोषणा TLP_REQ_ID(bus, devfn)		(((bus) << 8) | (devfn))
#घोषणा TLP_CFG_DW0(pcie, cfg)		\
		(((cfg) << 24) |	\
		  TLP_PAYLOAD_SIZE)
#घोषणा TLP_CFG_DW1(pcie, tag, be)	\
	(((TLP_REQ_ID(pcie->root_bus_nr,  RP_DEVFN)) << 16) | (tag << 8) | (be))
#घोषणा TLP_CFG_DW2(bus, devfn, offset)	\
				(((bus) << 24) | ((devfn) << 16) | (offset))
#घोषणा TLP_COMP_STATUS(s)		(((s) >> 13) & 7)
#घोषणा TLP_BYTE_COUNT(s)		(((s) >> 0) & 0xfff)
#घोषणा TLP_HDR_SIZE			3
#घोषणा TLP_LOOP			500

#घोषणा LINK_UP_TIMEOUT			HZ
#घोषणा LINK_RETRAIN_TIMEOUT		HZ

#घोषणा DWORD_MASK			3

#घोषणा S10_TLP_FMTTYPE_CFGRD0		0x05
#घोषणा S10_TLP_FMTTYPE_CFGRD1		0x04
#घोषणा S10_TLP_FMTTYPE_CFGWR0		0x45
#घोषणा S10_TLP_FMTTYPE_CFGWR1		0x44

क्रमागत altera_pcie_version अणु
	ALTERA_PCIE_V1 = 0,
	ALTERA_PCIE_V2,
पूर्ण;

काष्ठा altera_pcie अणु
	काष्ठा platक्रमm_device	*pdev;
	व्योम __iomem		*cra_base;
	व्योम __iomem		*hip_base;
	पूर्णांक			irq;
	u8			root_bus_nr;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	काष्ठा resource		bus_range;
	स्थिर काष्ठा altera_pcie_data	*pcie_data;
पूर्ण;

काष्ठा altera_pcie_ops अणु
	पूर्णांक (*tlp_पढ़ो_pkt)(काष्ठा altera_pcie *pcie, u32 *value);
	व्योम (*tlp_ग_लिखो_pkt)(काष्ठा altera_pcie *pcie, u32 *headers,
			      u32 data, bool align);
	bool (*get_link_status)(काष्ठा altera_pcie *pcie);
	पूर्णांक (*rp_पढ़ो_cfg)(काष्ठा altera_pcie *pcie, पूर्णांक where,
			   पूर्णांक size, u32 *value);
	पूर्णांक (*rp_ग_लिखो_cfg)(काष्ठा altera_pcie *pcie, u8 busno,
			    पूर्णांक where, पूर्णांक size, u32 value);
पूर्ण;

काष्ठा altera_pcie_data अणु
	स्थिर काष्ठा altera_pcie_ops *ops;
	क्रमागत altera_pcie_version version;
	u32 cap_offset;		/* PCIe capability काष्ठाure रेजिस्टर offset */
	u32 cfgrd0;
	u32 cfgrd1;
	u32 cfgwr0;
	u32 cfgwr1;
पूर्ण;

काष्ठा tlp_rp_regpair_t अणु
	u32 ctrl;
	u32 reg0;
	u32 reg1;
पूर्ण;

अटल अंतरभूत व्योम cra_ग_लिखोl(काष्ठा altera_pcie *pcie, स्थिर u32 value,
			      स्थिर u32 reg)
अणु
	ग_लिखोl_relaxed(value, pcie->cra_base + reg);
पूर्ण

अटल अंतरभूत u32 cra_पढ़ोl(काष्ठा altera_pcie *pcie, स्थिर u32 reg)
अणु
	वापस पढ़ोl_relaxed(pcie->cra_base + reg);
पूर्ण

अटल bool altera_pcie_link_up(काष्ठा altera_pcie *pcie)
अणु
	वापस !!((cra_पढ़ोl(pcie, RP_LTSSM) & RP_LTSSM_MASK) == LTSSM_L0);
पूर्ण

अटल bool s10_altera_pcie_link_up(काष्ठा altera_pcie *pcie)
अणु
	व्योम __iomem *addr = S10_RP_CFG_ADDR(pcie,
				   pcie->pcie_data->cap_offset +
				   PCI_EXP_LNKSTA);

	वापस !!(पढ़ोw(addr) & PCI_EXP_LNKSTA_DLLLA);
पूर्ण

/*
 * Altera PCIe port uses BAR0 of RC's configuration space as the translation
 * from PCI bus to native BUS.  Entire DDR region is mapped पूर्णांकo PCIe space
 * using these रेजिस्टरs, so it can be reached by DMA from EP devices.
 * This BAR0 will also access to MSI vector when receiving MSI/MSIX पूर्णांकerrupt
 * from EP devices, eventually trigger पूर्णांकerrupt to GIC.  The BAR0 of bridge
 * should be hidden during क्रमागतeration to aव्योम the sizing and resource
 * allocation by PCIe core.
 */
अटल bool altera_pcie_hide_rc_bar(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक  devfn,
				    पूर्णांक offset)
अणु
	अगर (pci_is_root_bus(bus) && (devfn == 0) &&
	    (offset == PCI_BASE_ADDRESS_0))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम tlp_ग_लिखो_tx(काष्ठा altera_pcie *pcie,
			 काष्ठा tlp_rp_regpair_t *tlp_rp_regdata)
अणु
	cra_ग_लिखोl(pcie, tlp_rp_regdata->reg0, RP_TX_REG0);
	cra_ग_लिखोl(pcie, tlp_rp_regdata->reg1, RP_TX_REG1);
	cra_ग_लिखोl(pcie, tlp_rp_regdata->ctrl, RP_TX_CNTRL);
पूर्ण

अटल व्योम s10_tlp_ग_लिखो_tx(काष्ठा altera_pcie *pcie, u32 reg0, u32 ctrl)
अणु
	cra_ग_लिखोl(pcie, reg0, RP_TX_REG0);
	cra_ग_लिखोl(pcie, ctrl, S10_RP_TX_CNTRL);
पूर्ण

अटल bool altera_pcie_valid_device(काष्ठा altera_pcie *pcie,
				     काष्ठा pci_bus *bus, पूर्णांक dev)
अणु
	/* If there is no link, then there is no device */
	अगर (bus->number != pcie->root_bus_nr) अणु
		अगर (!pcie->pcie_data->ops->get_link_status(pcie))
			वापस false;
	पूर्ण

	/* access only one slot on each root port */
	अगर (bus->number == pcie->root_bus_nr && dev > 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक tlp_पढ़ो_packet(काष्ठा altera_pcie *pcie, u32 *value)
अणु
	पूर्णांक i;
	bool sop = false;
	u32 ctrl;
	u32 reg0, reg1;
	u32 comp_status = 1;

	/*
	 * Minimum 2 loops to पढ़ो TLP headers and 1 loop to पढ़ो data
	 * payload.
	 */
	क्रम (i = 0; i < TLP_LOOP; i++) अणु
		ctrl = cra_पढ़ोl(pcie, RP_RXCPL_STATUS);
		अगर ((ctrl & RP_RXCPL_SOP) || (ctrl & RP_RXCPL_EOP) || sop) अणु
			reg0 = cra_पढ़ोl(pcie, RP_RXCPL_REG0);
			reg1 = cra_पढ़ोl(pcie, RP_RXCPL_REG1);

			अगर (ctrl & RP_RXCPL_SOP) अणु
				sop = true;
				comp_status = TLP_COMP_STATUS(reg1);
			पूर्ण

			अगर (ctrl & RP_RXCPL_EOP) अणु
				अगर (comp_status)
					वापस PCIBIOS_DEVICE_NOT_FOUND;

				अगर (value)
					*value = reg0;

				वापस PCIBIOS_SUCCESSFUL;
			पूर्ण
		पूर्ण
		udelay(5);
	पूर्ण

	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

अटल पूर्णांक s10_tlp_पढ़ो_packet(काष्ठा altera_pcie *pcie, u32 *value)
अणु
	u32 ctrl;
	u32 comp_status;
	u32 dw[4];
	u32 count;
	काष्ठा device *dev = &pcie->pdev->dev;

	क्रम (count = 0; count < TLP_LOOP; count++) अणु
		ctrl = cra_पढ़ोl(pcie, S10_RP_RXCPL_STATUS);
		अगर (ctrl & RP_RXCPL_SOP) अणु
			/* Read first DW */
			dw[0] = cra_पढ़ोl(pcie, S10_RP_RXCPL_REG);
			अवरोध;
		पूर्ण

		udelay(5);
	पूर्ण

	/* SOP detection failed, वापस error */
	अगर (count == TLP_LOOP)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	count = 1;

	/* Poll क्रम EOP */
	जबतक (count < ARRAY_SIZE(dw)) अणु
		ctrl = cra_पढ़ोl(pcie, S10_RP_RXCPL_STATUS);
		dw[count++] = cra_पढ़ोl(pcie, S10_RP_RXCPL_REG);
		अगर (ctrl & RP_RXCPL_EOP) अणु
			comp_status = TLP_COMP_STATUS(dw[1]);
			अगर (comp_status)
				वापस PCIBIOS_DEVICE_NOT_FOUND;

			अगर (value && TLP_BYTE_COUNT(dw[1]) == माप(u32) &&
			    count == 4)
				*value = dw[3];

			वापस PCIBIOS_SUCCESSFUL;
		पूर्ण
	पूर्ण

	dev_warn(dev, "Malformed TLP packet\n");

	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

अटल व्योम tlp_ग_लिखो_packet(काष्ठा altera_pcie *pcie, u32 *headers,
			     u32 data, bool align)
अणु
	काष्ठा tlp_rp_regpair_t tlp_rp_regdata;

	tlp_rp_regdata.reg0 = headers[0];
	tlp_rp_regdata.reg1 = headers[1];
	tlp_rp_regdata.ctrl = RP_TX_SOP;
	tlp_ग_लिखो_tx(pcie, &tlp_rp_regdata);

	अगर (align) अणु
		tlp_rp_regdata.reg0 = headers[2];
		tlp_rp_regdata.reg1 = 0;
		tlp_rp_regdata.ctrl = 0;
		tlp_ग_लिखो_tx(pcie, &tlp_rp_regdata);

		tlp_rp_regdata.reg0 = data;
		tlp_rp_regdata.reg1 = 0;
	पूर्ण अन्यथा अणु
		tlp_rp_regdata.reg0 = headers[2];
		tlp_rp_regdata.reg1 = data;
	पूर्ण

	tlp_rp_regdata.ctrl = RP_TX_EOP;
	tlp_ग_लिखो_tx(pcie, &tlp_rp_regdata);
पूर्ण

अटल व्योम s10_tlp_ग_लिखो_packet(काष्ठा altera_pcie *pcie, u32 *headers,
				 u32 data, bool dummy)
अणु
	s10_tlp_ग_लिखो_tx(pcie, headers[0], RP_TX_SOP);
	s10_tlp_ग_लिखो_tx(pcie, headers[1], 0);
	s10_tlp_ग_लिखो_tx(pcie, headers[2], 0);
	s10_tlp_ग_लिखो_tx(pcie, data, RP_TX_EOP);
पूर्ण

अटल व्योम get_tlp_header(काष्ठा altera_pcie *pcie, u8 bus, u32 devfn,
			   पूर्णांक where, u8 byte_en, bool पढ़ो, u32 *headers)
अणु
	u8 cfg;
	u8 cfg0 = पढ़ो ? pcie->pcie_data->cfgrd0 : pcie->pcie_data->cfgwr0;
	u8 cfg1 = पढ़ो ? pcie->pcie_data->cfgrd1 : pcie->pcie_data->cfgwr1;
	u8 tag = पढ़ो ? TLP_READ_TAG : TLP_WRITE_TAG;

	अगर (pcie->pcie_data->version == ALTERA_PCIE_V1)
		cfg = (bus == pcie->root_bus_nr) ? cfg0 : cfg1;
	अन्यथा
		cfg = (bus > S10_RP_SECONDARY(pcie)) ? cfg0 : cfg1;

	headers[0] = TLP_CFG_DW0(pcie, cfg);
	headers[1] = TLP_CFG_DW1(pcie, tag, byte_en);
	headers[2] = TLP_CFG_DW2(bus, devfn, where);
पूर्ण

अटल पूर्णांक tlp_cfg_dword_पढ़ो(काष्ठा altera_pcie *pcie, u8 bus, u32 devfn,
			      पूर्णांक where, u8 byte_en, u32 *value)
अणु
	u32 headers[TLP_HDR_SIZE];

	get_tlp_header(pcie, bus, devfn, where, byte_en, true,
		       headers);

	pcie->pcie_data->ops->tlp_ग_लिखो_pkt(pcie, headers, 0, false);

	वापस pcie->pcie_data->ops->tlp_पढ़ो_pkt(pcie, value);
पूर्ण

अटल पूर्णांक tlp_cfg_dword_ग_लिखो(काष्ठा altera_pcie *pcie, u8 bus, u32 devfn,
			       पूर्णांक where, u8 byte_en, u32 value)
अणु
	u32 headers[TLP_HDR_SIZE];
	पूर्णांक ret;

	get_tlp_header(pcie, bus, devfn, where, byte_en, false,
		       headers);

	/* check alignment to Qword */
	अगर ((where & 0x7) == 0)
		pcie->pcie_data->ops->tlp_ग_लिखो_pkt(pcie, headers,
						    value, true);
	अन्यथा
		pcie->pcie_data->ops->tlp_ग_लिखो_pkt(pcie, headers,
						    value, false);

	ret = pcie->pcie_data->ops->tlp_पढ़ो_pkt(pcie, शून्य);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस ret;

	/*
	 * Monitor changes to PCI_PRIMARY_BUS रेजिस्टर on root port
	 * and update local copy of root bus number accordingly.
	 */
	अगर ((bus == pcie->root_bus_nr) && (where == PCI_PRIMARY_BUS))
		pcie->root_bus_nr = (u8)(value);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक s10_rp_पढ़ो_cfg(काष्ठा altera_pcie *pcie, पूर्णांक where,
			   पूर्णांक size, u32 *value)
अणु
	व्योम __iomem *addr = S10_RP_CFG_ADDR(pcie, where);

	चयन (size) अणु
	हाल 1:
		*value = पढ़ोb(addr);
		अवरोध;
	हाल 2:
		*value = पढ़ोw(addr);
		अवरोध;
	शेष:
		*value = पढ़ोl(addr);
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक s10_rp_ग_लिखो_cfg(काष्ठा altera_pcie *pcie, u8 busno,
			    पूर्णांक where, पूर्णांक size, u32 value)
अणु
	व्योम __iomem *addr = S10_RP_CFG_ADDR(pcie, where);

	चयन (size) अणु
	हाल 1:
		ग_लिखोb(value, addr);
		अवरोध;
	हाल 2:
		ग_लिखोw(value, addr);
		अवरोध;
	शेष:
		ग_लिखोl(value, addr);
		अवरोध;
	पूर्ण

	/*
	 * Monitor changes to PCI_PRIMARY_BUS रेजिस्टर on root port
	 * and update local copy of root bus number accordingly.
	 */
	अगर (busno == pcie->root_bus_nr && where == PCI_PRIMARY_BUS)
		pcie->root_bus_nr = value & 0xff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक _altera_pcie_cfg_पढ़ो(काष्ठा altera_pcie *pcie, u8 busno,
				 अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
				 u32 *value)
अणु
	पूर्णांक ret;
	u32 data;
	u8 byte_en;

	अगर (busno == pcie->root_bus_nr && pcie->pcie_data->ops->rp_पढ़ो_cfg)
		वापस pcie->pcie_data->ops->rp_पढ़ो_cfg(pcie, where,
							 size, value);

	चयन (size) अणु
	हाल 1:
		byte_en = 1 << (where & 3);
		अवरोध;
	हाल 2:
		byte_en = 3 << (where & 3);
		अवरोध;
	शेष:
		byte_en = 0xf;
		अवरोध;
	पूर्ण

	ret = tlp_cfg_dword_पढ़ो(pcie, busno, devfn,
				 (where & ~DWORD_MASK), byte_en, &data);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस ret;

	चयन (size) अणु
	हाल 1:
		*value = (data >> (8 * (where & 0x3))) & 0xff;
		अवरोध;
	हाल 2:
		*value = (data >> (8 * (where & 0x2))) & 0xffff;
		अवरोध;
	शेष:
		*value = data;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक _altera_pcie_cfg_ग_लिखो(काष्ठा altera_pcie *pcie, u8 busno,
				  अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
				  u32 value)
अणु
	u32 data32;
	u32 shअगरt = 8 * (where & 3);
	u8 byte_en;

	अगर (busno == pcie->root_bus_nr && pcie->pcie_data->ops->rp_ग_लिखो_cfg)
		वापस pcie->pcie_data->ops->rp_ग_लिखो_cfg(pcie, busno,
						     where, size, value);

	चयन (size) अणु
	हाल 1:
		data32 = (value & 0xff) << shअगरt;
		byte_en = 1 << (where & 3);
		अवरोध;
	हाल 2:
		data32 = (value & 0xffff) << shअगरt;
		byte_en = 3 << (where & 3);
		अवरोध;
	शेष:
		data32 = value;
		byte_en = 0xf;
		अवरोध;
	पूर्ण

	वापस tlp_cfg_dword_ग_लिखो(pcie, busno, devfn, (where & ~DWORD_MASK),
				   byte_en, data32);
पूर्ण

अटल पूर्णांक altera_pcie_cfg_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	काष्ठा altera_pcie *pcie = bus->sysdata;

	अगर (altera_pcie_hide_rc_bar(bus, devfn, where))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (!altera_pcie_valid_device(pcie, bus, PCI_SLOT(devfn))) अणु
		*value = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	वापस _altera_pcie_cfg_पढ़ो(pcie, bus->number, devfn, where, size,
				     value);
पूर्ण

अटल पूर्णांक altera_pcie_cfg_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 value)
अणु
	काष्ठा altera_pcie *pcie = bus->sysdata;

	अगर (altera_pcie_hide_rc_bar(bus, devfn, where))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (!altera_pcie_valid_device(pcie, bus, PCI_SLOT(devfn)))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस _altera_pcie_cfg_ग_लिखो(pcie, bus->number, devfn, where, size,
				     value);
पूर्ण

अटल काष्ठा pci_ops altera_pcie_ops = अणु
	.पढ़ो = altera_pcie_cfg_पढ़ो,
	.ग_लिखो = altera_pcie_cfg_ग_लिखो,
पूर्ण;

अटल पूर्णांक altera_पढ़ो_cap_word(काष्ठा altera_pcie *pcie, u8 busno,
				अचिन्हित पूर्णांक devfn, पूर्णांक offset, u16 *value)
अणु
	u32 data;
	पूर्णांक ret;

	ret = _altera_pcie_cfg_पढ़ो(pcie, busno, devfn,
				    pcie->pcie_data->cap_offset + offset,
				    माप(*value),
				    &data);
	*value = data;
	वापस ret;
पूर्ण

अटल पूर्णांक altera_ग_लिखो_cap_word(काष्ठा altera_pcie *pcie, u8 busno,
				 अचिन्हित पूर्णांक devfn, पूर्णांक offset, u16 value)
अणु
	वापस _altera_pcie_cfg_ग_लिखो(pcie, busno, devfn,
				      pcie->pcie_data->cap_offset + offset,
				      माप(value),
				      value);
पूर्ण

अटल व्योम altera_रुको_link_retrain(काष्ठा altera_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	u16 reg16;
	अचिन्हित दीर्घ start_jअगरfies;

	/* Wait क्रम link training end. */
	start_jअगरfies = jअगरfies;
	क्रम (;;) अणु
		altera_पढ़ो_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				     PCI_EXP_LNKSTA, &reg16);
		अगर (!(reg16 & PCI_EXP_LNKSTA_LT))
			अवरोध;

		अगर (समय_after(jअगरfies, start_jअगरfies + LINK_RETRAIN_TIMEOUT)) अणु
			dev_err(dev, "link retrain timeout\n");
			अवरोध;
		पूर्ण
		udelay(100);
	पूर्ण

	/* Wait क्रम link is up */
	start_jअगरfies = jअगरfies;
	क्रम (;;) अणु
		अगर (pcie->pcie_data->ops->get_link_status(pcie))
			अवरोध;

		अगर (समय_after(jअगरfies, start_jअगरfies + LINK_UP_TIMEOUT)) अणु
			dev_err(dev, "link up timeout\n");
			अवरोध;
		पूर्ण
		udelay(100);
	पूर्ण
पूर्ण

अटल व्योम altera_pcie_retrain(काष्ठा altera_pcie *pcie)
अणु
	u16 linkcap, linkstat, linkctl;

	अगर (!pcie->pcie_data->ops->get_link_status(pcie))
		वापस;

	/*
	 * Set the retrain bit अगर the PCIe rootport support > 2.5GB/s, but
	 * current speed is 2.5 GB/s.
	 */
	altera_पढ़ो_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN, PCI_EXP_LNKCAP,
			     &linkcap);
	अगर ((linkcap & PCI_EXP_LNKCAP_SLS) <= PCI_EXP_LNKCAP_SLS_2_5GB)
		वापस;

	altera_पढ़ो_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN, PCI_EXP_LNKSTA,
			     &linkstat);
	अगर ((linkstat & PCI_EXP_LNKSTA_CLS) == PCI_EXP_LNKSTA_CLS_2_5GB) अणु
		altera_पढ़ो_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				     PCI_EXP_LNKCTL, &linkctl);
		linkctl |= PCI_EXP_LNKCTL_RL;
		altera_ग_लिखो_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				      PCI_EXP_LNKCTL, linkctl);

		altera_रुको_link_retrain(pcie);
	पूर्ण
पूर्ण

अटल पूर्णांक altera_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = altera_pcie_पूर्णांकx_map,
	.xlate = pci_irqd_पूर्णांकx_xlate,
पूर्ण;

अटल व्योम altera_pcie_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा altera_pcie *pcie;
	काष्ठा device *dev;
	अचिन्हित दीर्घ status;
	u32 bit;
	u32 virq;

	chained_irq_enter(chip, desc);
	pcie = irq_desc_get_handler_data(desc);
	dev = &pcie->pdev->dev;

	जबतक ((status = cra_पढ़ोl(pcie, P2A_INT_STATUS)
		& P2A_INT_STS_ALL) != 0) अणु
		क्रम_each_set_bit(bit, &status, PCI_NUM_INTX) अणु
			/* clear पूर्णांकerrupts */
			cra_ग_लिखोl(pcie, 1 << bit, P2A_INT_STATUS);

			virq = irq_find_mapping(pcie->irq_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
			अन्यथा
				dev_err(dev, "unexpected IRQ, INT%d\n", bit);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक altera_pcie_init_irq_करोमुख्य(काष्ठा altera_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा device_node *node = dev->of_node;

	/* Setup INTx */
	pcie->irq_करोमुख्य = irq_करोमुख्य_add_linear(node, PCI_NUM_INTX,
					&पूर्णांकx_करोमुख्य_ops, pcie);
	अगर (!pcie->irq_करोमुख्य) अणु
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम altera_pcie_irq_tearकरोwn(काष्ठा altera_pcie *pcie)
अणु
	irq_set_chained_handler_and_data(pcie->irq, शून्य, शून्य);
	irq_करोमुख्य_हटाओ(pcie->irq_करोमुख्य);
	irq_dispose_mapping(pcie->irq);
पूर्ण

अटल पूर्णांक altera_pcie_parse_dt(काष्ठा altera_pcie *pcie)
अणु
	काष्ठा platक्रमm_device *pdev = pcie->pdev;

	pcie->cra_base = devm_platक्रमm_ioremap_resource_byname(pdev, "Cra");
	अगर (IS_ERR(pcie->cra_base))
		वापस PTR_ERR(pcie->cra_base);

	अगर (pcie->pcie_data->version == ALTERA_PCIE_V2) अणु
		pcie->hip_base =
			devm_platक्रमm_ioremap_resource_byname(pdev, "Hip");
		अगर (IS_ERR(pcie->hip_base))
			वापस PTR_ERR(pcie->hip_base);
	पूर्ण

	/* setup IRQ */
	pcie->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pcie->irq < 0)
		वापस pcie->irq;

	irq_set_chained_handler_and_data(pcie->irq, altera_pcie_isr, pcie);
	वापस 0;
पूर्ण

अटल व्योम altera_pcie_host_init(काष्ठा altera_pcie *pcie)
अणु
	altera_pcie_retrain(pcie);
पूर्ण

अटल स्थिर काष्ठा altera_pcie_ops altera_pcie_ops_1_0 = अणु
	.tlp_पढ़ो_pkt = tlp_पढ़ो_packet,
	.tlp_ग_लिखो_pkt = tlp_ग_लिखो_packet,
	.get_link_status = altera_pcie_link_up,
पूर्ण;

अटल स्थिर काष्ठा altera_pcie_ops altera_pcie_ops_2_0 = अणु
	.tlp_पढ़ो_pkt = s10_tlp_पढ़ो_packet,
	.tlp_ग_लिखो_pkt = s10_tlp_ग_लिखो_packet,
	.get_link_status = s10_altera_pcie_link_up,
	.rp_पढ़ो_cfg = s10_rp_पढ़ो_cfg,
	.rp_ग_लिखो_cfg = s10_rp_ग_लिखो_cfg,
पूर्ण;

अटल स्थिर काष्ठा altera_pcie_data altera_pcie_1_0_data = अणु
	.ops = &altera_pcie_ops_1_0,
	.cap_offset = 0x80,
	.version = ALTERA_PCIE_V1,
	.cfgrd0 = TLP_FMTTYPE_CFGRD0,
	.cfgrd1 = TLP_FMTTYPE_CFGRD1,
	.cfgwr0 = TLP_FMTTYPE_CFGWR0,
	.cfgwr1 = TLP_FMTTYPE_CFGWR1,
पूर्ण;

अटल स्थिर काष्ठा altera_pcie_data altera_pcie_2_0_data = अणु
	.ops = &altera_pcie_ops_2_0,
	.version = ALTERA_PCIE_V2,
	.cap_offset = 0x70,
	.cfgrd0 = S10_TLP_FMTTYPE_CFGRD0,
	.cfgrd1 = S10_TLP_FMTTYPE_CFGRD1,
	.cfgwr0 = S10_TLP_FMTTYPE_CFGWR0,
	.cfgwr1 = S10_TLP_FMTTYPE_CFGWR1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id altera_pcie_of_match[] = अणु
	अणु.compatible = "altr,pcie-root-port-1.0",
	 .data = &altera_pcie_1_0_data पूर्ण,
	अणु.compatible = "altr,pcie-root-port-2.0",
	 .data = &altera_pcie_2_0_data पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक altera_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा altera_pcie *pcie;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	pcie->pdev = pdev;
	platक्रमm_set_drvdata(pdev, pcie);

	match = of_match_device(altera_pcie_of_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	pcie->pcie_data = match->data;

	ret = altera_pcie_parse_dt(pcie);
	अगर (ret) अणु
		dev_err(dev, "Parsing DT failed\n");
		वापस ret;
	पूर्ण

	ret = altera_pcie_init_irq_करोमुख्य(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed creating IRQ Domain\n");
		वापस ret;
	पूर्ण

	/* clear all पूर्णांकerrupts */
	cra_ग_लिखोl(pcie, P2A_INT_STS_ALL, P2A_INT_STATUS);
	/* enable all पूर्णांकerrupts */
	cra_ग_लिखोl(pcie, P2A_INT_ENA_ALL, P2A_INT_ENABLE);
	altera_pcie_host_init(pcie);

	bridge->sysdata = pcie;
	bridge->busnr = pcie->root_bus_nr;
	bridge->ops = &altera_pcie_ops;

	वापस pci_host_probe(bridge);
पूर्ण

अटल पूर्णांक altera_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_pcie *pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);

	pci_stop_root_bus(bridge->bus);
	pci_हटाओ_root_bus(bridge->bus);
	altera_pcie_irq_tearकरोwn(pcie);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver altera_pcie_driver = अणु
	.probe		= altera_pcie_probe,
	.हटाओ		= altera_pcie_हटाओ,
	.driver = अणु
		.name	= "altera-pcie",
		.of_match_table = altera_pcie_of_match,
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, altera_pcie_of_match);
module_platक्रमm_driver(altera_pcie_driver);
MODULE_LICENSE("GPL v2");
