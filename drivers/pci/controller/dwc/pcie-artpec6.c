<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Axis ARTPEC-6 SoC
 *
 * Author: Niklas Cassel <niklas.cassel@axis.com>
 *
 * Based on work करोne by Phil Edworthy <phil@edworthys.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pcie-designware.h"

#घोषणा to_artpec6_pcie(x)	dev_get_drvdata((x)->dev)

क्रमागत artpec_pcie_variants अणु
	ARTPEC6,
	ARTPEC7,
पूर्ण;

काष्ठा artpec6_pcie अणु
	काष्ठा dw_pcie		*pci;
	काष्ठा regmap		*regmap;	/* DT axis,syscon-pcie */
	व्योम __iomem		*phy_base;	/* DT phy */
	क्रमागत artpec_pcie_variants variant;
	क्रमागत dw_pcie_device_mode mode;
पूर्ण;

काष्ठा artpec_pcie_of_data अणु
	क्रमागत artpec_pcie_variants variant;
	क्रमागत dw_pcie_device_mode mode;
पूर्ण;

अटल स्थिर काष्ठा of_device_id artpec6_pcie_of_match[];

/* ARTPEC-6 specअगरic रेजिस्टरs */
#घोषणा PCIECFG				0x18
#घोषणा  PCIECFG_DBG_OEN		BIT(24)
#घोषणा  PCIECFG_CORE_RESET_REQ		BIT(21)
#घोषणा  PCIECFG_LTSSM_ENABLE		BIT(20)
#घोषणा  PCIECFG_DEVICE_TYPE_MASK	GENMASK(19, 16)
#घोषणा  PCIECFG_CLKREQ_B		BIT(11)
#घोषणा  PCIECFG_REFCLK_ENABLE		BIT(10)
#घोषणा  PCIECFG_PLL_ENABLE		BIT(9)
#घोषणा  PCIECFG_PCLK_ENABLE		BIT(8)
#घोषणा  PCIECFG_RISRCREN		BIT(4)
#घोषणा  PCIECFG_MODE_TX_DRV_EN		BIT(3)
#घोषणा  PCIECFG_CISRREN		BIT(2)
#घोषणा  PCIECFG_MACRO_ENABLE		BIT(0)
/* ARTPEC-7 specअगरic fields */
#घोषणा  PCIECFG_REFCLKSEL		BIT(23)
#घोषणा  PCIECFG_NOC_RESET		BIT(3)

#घोषणा PCIESTAT			0x1c
/* ARTPEC-7 specअगरic fields */
#घोषणा  PCIESTAT_EXTREFCLK		BIT(3)

#घोषणा NOCCFG				0x40
#घोषणा  NOCCFG_ENABLE_CLK_PCIE		BIT(4)
#घोषणा  NOCCFG_POWER_PCIE_IDLEACK	BIT(3)
#घोषणा  NOCCFG_POWER_PCIE_IDLE		BIT(2)
#घोषणा  NOCCFG_POWER_PCIE_IDLEREQ	BIT(1)

#घोषणा PHY_STATUS			0x118
#घोषणा  PHY_COSPLLLOCK			BIT(0)

#घोषणा PHY_TX_ASIC_OUT			0x4040
#घोषणा  PHY_TX_ASIC_OUT_TX_ACK		BIT(0)

#घोषणा PHY_RX_ASIC_OUT			0x405c
#घोषणा  PHY_RX_ASIC_OUT_ACK		BIT(0)

अटल u32 artpec6_pcie_पढ़ोl(काष्ठा artpec6_pcie *artpec6_pcie, u32 offset)
अणु
	u32 val;

	regmap_पढ़ो(artpec6_pcie->regmap, offset, &val);
	वापस val;
पूर्ण

अटल व्योम artpec6_pcie_ग_लिखोl(काष्ठा artpec6_pcie *artpec6_pcie, u32 offset, u32 val)
अणु
	regmap_ग_लिखो(artpec6_pcie->regmap, offset, val);
पूर्ण

अटल u64 artpec6_pcie_cpu_addr_fixup(काष्ठा dw_pcie *pci, u64 pci_addr)
अणु
	काष्ठा artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा dw_pcie_ep *ep = &pci->ep;

	चयन (artpec6_pcie->mode) अणु
	हाल DW_PCIE_RC_TYPE:
		वापस pci_addr - pp->cfg0_base;
	हाल DW_PCIE_EP_TYPE:
		वापस pci_addr - ep->phys_base;
	शेष:
		dev_err(pci->dev, "UNKNOWN device type\n");
	पूर्ण
	वापस pci_addr;
पूर्ण

अटल पूर्णांक artpec6_pcie_establish_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);
	u32 val;

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	val |= PCIECFG_LTSSM_ENABLE;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);

	वापस 0;
पूर्ण

अटल व्योम artpec6_pcie_stop_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);
	u32 val;

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	val &= ~PCIECFG_LTSSM_ENABLE;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.cpu_addr_fixup = artpec6_pcie_cpu_addr_fixup,
	.start_link = artpec6_pcie_establish_link,
	.stop_link = artpec6_pcie_stop_link,
पूर्ण;

अटल व्योम artpec6_pcie_रुको_क्रम_phy_a6(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	काष्ठा dw_pcie *pci = artpec6_pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 val;
	अचिन्हित पूर्णांक retries;

	retries = 50;
	करो अणु
		usleep_range(1000, 2000);
		val = artpec6_pcie_पढ़ोl(artpec6_pcie, NOCCFG);
		retries--;
	पूर्ण जबतक (retries &&
		(val & (NOCCFG_POWER_PCIE_IDLEACK | NOCCFG_POWER_PCIE_IDLE)));
	अगर (!retries)
		dev_err(dev, "PCIe clock manager did not leave idle state\n");

	retries = 50;
	करो अणु
		usleep_range(1000, 2000);
		val = पढ़ोl(artpec6_pcie->phy_base + PHY_STATUS);
		retries--;
	पूर्ण जबतक (retries && !(val & PHY_COSPLLLOCK));
	अगर (!retries)
		dev_err(dev, "PHY PLL did not lock\n");
पूर्ण

अटल व्योम artpec6_pcie_रुको_क्रम_phy_a7(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	काष्ठा dw_pcie *pci = artpec6_pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 val;
	u16 phy_status_tx, phy_status_rx;
	अचिन्हित पूर्णांक retries;

	retries = 50;
	करो अणु
		usleep_range(1000, 2000);
		val = artpec6_pcie_पढ़ोl(artpec6_pcie, NOCCFG);
		retries--;
	पूर्ण जबतक (retries &&
		(val & (NOCCFG_POWER_PCIE_IDLEACK | NOCCFG_POWER_PCIE_IDLE)));
	अगर (!retries)
		dev_err(dev, "PCIe clock manager did not leave idle state\n");

	retries = 50;
	करो अणु
		usleep_range(1000, 2000);
		phy_status_tx = पढ़ोw(artpec6_pcie->phy_base + PHY_TX_ASIC_OUT);
		phy_status_rx = पढ़ोw(artpec6_pcie->phy_base + PHY_RX_ASIC_OUT);
		retries--;
	पूर्ण जबतक (retries && ((phy_status_tx & PHY_TX_ASIC_OUT_TX_ACK) ||
				(phy_status_rx & PHY_RX_ASIC_OUT_ACK)));
	अगर (!retries)
		dev_err(dev, "PHY did not enter Pn state\n");
पूर्ण

अटल व्योम artpec6_pcie_रुको_क्रम_phy(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	चयन (artpec6_pcie->variant) अणु
	हाल ARTPEC6:
		artpec6_pcie_रुको_क्रम_phy_a6(artpec6_pcie);
		अवरोध;
	हाल ARTPEC7:
		artpec6_pcie_रुको_क्रम_phy_a7(artpec6_pcie);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम artpec6_pcie_init_phy_a6(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	u32 val;

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	val |=  PCIECFG_RISRCREN |	/* Receiver term. 50 Ohm */
		PCIECFG_MODE_TX_DRV_EN |
		PCIECFG_CISRREN |	/* Reference घड़ी term. 100 Ohm */
		PCIECFG_MACRO_ENABLE;
	val |= PCIECFG_REFCLK_ENABLE;
	val &= ~PCIECFG_DBG_OEN;
	val &= ~PCIECFG_CLKREQ_B;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);
	usleep_range(5000, 6000);

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, NOCCFG);
	val |= NOCCFG_ENABLE_CLK_PCIE;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, NOCCFG, val);
	usleep_range(20, 30);

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	val |= PCIECFG_PCLK_ENABLE | PCIECFG_PLL_ENABLE;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);
	usleep_range(6000, 7000);

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, NOCCFG);
	val &= ~NOCCFG_POWER_PCIE_IDLEREQ;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, NOCCFG, val);
पूर्ण

अटल व्योम artpec6_pcie_init_phy_a7(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	काष्ठा dw_pcie *pci = artpec6_pcie->pci;
	u32 val;
	bool extrefclk;

	/* Check अगर बाह्यal reference घड़ी is connected */
	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIESTAT);
	extrefclk = !!(val & PCIESTAT_EXTREFCLK);
	dev_dbg(pci->dev, "Using reference clock: %s\n",
		extrefclk ? "external" : "internal");

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	val |=  PCIECFG_RISRCREN |	/* Receiver term. 50 Ohm */
		PCIECFG_PCLK_ENABLE;
	अगर (extrefclk)
		val |= PCIECFG_REFCLKSEL;
	अन्यथा
		val &= ~PCIECFG_REFCLKSEL;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);
	usleep_range(10, 20);

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, NOCCFG);
	val |= NOCCFG_ENABLE_CLK_PCIE;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, NOCCFG, val);
	usleep_range(20, 30);

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, NOCCFG);
	val &= ~NOCCFG_POWER_PCIE_IDLEREQ;
	artpec6_pcie_ग_लिखोl(artpec6_pcie, NOCCFG, val);
पूर्ण

अटल व्योम artpec6_pcie_init_phy(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	चयन (artpec6_pcie->variant) अणु
	हाल ARTPEC6:
		artpec6_pcie_init_phy_a6(artpec6_pcie);
		अवरोध;
	हाल ARTPEC7:
		artpec6_pcie_init_phy_a7(artpec6_pcie);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम artpec6_pcie_निश्चित_core_reset(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	u32 val;

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	चयन (artpec6_pcie->variant) अणु
	हाल ARTPEC6:
		val |= PCIECFG_CORE_RESET_REQ;
		अवरोध;
	हाल ARTPEC7:
		val &= ~PCIECFG_NOC_RESET;
		अवरोध;
	पूर्ण
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);
पूर्ण

अटल व्योम artpec6_pcie_deनिश्चित_core_reset(काष्ठा artpec6_pcie *artpec6_pcie)
अणु
	u32 val;

	val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
	चयन (artpec6_pcie->variant) अणु
	हाल ARTPEC6:
		val &= ~PCIECFG_CORE_RESET_REQ;
		अवरोध;
	हाल ARTPEC7:
		val |= PCIECFG_NOC_RESET;
		अवरोध;
	पूर्ण
	artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);
	usleep_range(100, 200);
पूर्ण

अटल पूर्णांक artpec6_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);

	अगर (artpec6_pcie->variant == ARTPEC7) अणु
		pci->n_fts[0] = 180;
		pci->n_fts[1] = 180;
	पूर्ण
	artpec6_pcie_निश्चित_core_reset(artpec6_pcie);
	artpec6_pcie_init_phy(artpec6_pcie);
	artpec6_pcie_deनिश्चित_core_reset(artpec6_pcie);
	artpec6_pcie_रुको_क्रम_phy(artpec6_pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops artpec6_pcie_host_ops = अणु
	.host_init = artpec6_pcie_host_init,
पूर्ण;

अटल व्योम artpec6_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा artpec6_pcie *artpec6_pcie = to_artpec6_pcie(pci);
	क्रमागत pci_barno bar;

	artpec6_pcie_निश्चित_core_reset(artpec6_pcie);
	artpec6_pcie_init_phy(artpec6_pcie);
	artpec6_pcie_deनिश्चित_core_reset(artpec6_pcie);
	artpec6_pcie_रुको_क्रम_phy(artpec6_pcie);

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++)
		dw_pcie_ep_reset_bar(pci, bar);
पूर्ण

अटल पूर्णांक artpec6_pcie_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				  क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		dev_err(pci->dev, "EP cannot trigger legacy IRQs\n");
		वापस -EINVAL;
	हाल PCI_EPC_IRQ_MSI:
		वापस dw_pcie_ep_उठाओ_msi_irq(ep, func_no, पूर्णांकerrupt_num);
	शेष:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops pcie_ep_ops = अणु
	.ep_init = artpec6_pcie_ep_init,
	.उठाओ_irq = artpec6_pcie_उठाओ_irq,
पूर्ण;

अटल पूर्णांक artpec6_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा artpec6_pcie *artpec6_pcie;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा artpec_pcie_of_data *data;
	क्रमागत artpec_pcie_variants variant;
	क्रमागत dw_pcie_device_mode mode;

	match = of_match_device(artpec6_pcie_of_match, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा artpec_pcie_of_data *)match->data;
	variant = (क्रमागत artpec_pcie_variants)data->variant;
	mode = (क्रमागत dw_pcie_device_mode)data->mode;

	artpec6_pcie = devm_kzalloc(dev, माप(*artpec6_pcie), GFP_KERNEL);
	अगर (!artpec6_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	artpec6_pcie->pci = pci;
	artpec6_pcie->variant = variant;
	artpec6_pcie->mode = mode;

	artpec6_pcie->phy_base =
		devm_platक्रमm_ioremap_resource_byname(pdev, "phy");
	अगर (IS_ERR(artpec6_pcie->phy_base))
		वापस PTR_ERR(artpec6_pcie->phy_base);

	artpec6_pcie->regmap =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"axis,syscon-pcie");
	अगर (IS_ERR(artpec6_pcie->regmap))
		वापस PTR_ERR(artpec6_pcie->regmap);

	platक्रमm_set_drvdata(pdev, artpec6_pcie);

	चयन (artpec6_pcie->mode) अणु
	हाल DW_PCIE_RC_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCIE_ARTPEC6_HOST))
			वापस -ENODEV;

		pci->pp.ops = &artpec6_pcie_host_ops;

		ret = dw_pcie_host_init(&pci->pp);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल DW_PCIE_EP_TYPE: अणु
		u32 val;

		अगर (!IS_ENABLED(CONFIG_PCIE_ARTPEC6_EP))
			वापस -ENODEV;

		val = artpec6_pcie_पढ़ोl(artpec6_pcie, PCIECFG);
		val &= ~PCIECFG_DEVICE_TYPE_MASK;
		artpec6_pcie_ग_लिखोl(artpec6_pcie, PCIECFG, val);

		pci->ep.ops = &pcie_ep_ops;

		वापस dw_pcie_ep_init(&pci->ep);
		अवरोध;
	पूर्ण
	शेष:
		dev_err(dev, "INVALID device type %d\n", artpec6_pcie->mode);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा artpec_pcie_of_data artpec6_pcie_rc_of_data = अणु
	.variant = ARTPEC6,
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा artpec_pcie_of_data artpec6_pcie_ep_of_data = अणु
	.variant = ARTPEC6,
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा artpec_pcie_of_data artpec7_pcie_rc_of_data = अणु
	.variant = ARTPEC7,
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा artpec_pcie_of_data artpec7_pcie_ep_of_data = अणु
	.variant = ARTPEC7,
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id artpec6_pcie_of_match[] = अणु
	अणु
		.compatible = "axis,artpec6-pcie",
		.data = &artpec6_pcie_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "axis,artpec6-pcie-ep",
		.data = &artpec6_pcie_ep_of_data,
	पूर्ण,
	अणु
		.compatible = "axis,artpec7-pcie",
		.data = &artpec7_pcie_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "axis,artpec7-pcie-ep",
		.data = &artpec7_pcie_ep_of_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver artpec6_pcie_driver = अणु
	.probe = artpec6_pcie_probe,
	.driver = अणु
		.name	= "artpec6-pcie",
		.of_match_table = artpec6_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(artpec6_pcie_driver);
