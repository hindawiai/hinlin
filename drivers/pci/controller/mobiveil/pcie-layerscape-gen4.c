<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe Gen4 host controller driver क्रम NXP Layerscape SoCs
 *
 * Copyright 2019-2020 NXP
 *
 * Author: Zhiqiang Hou <Zhiqiang.Hou@nxp.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pcie-mobiveil.h"

/* LUT and PF control रेजिस्टरs */
#घोषणा PCIE_LUT_OFF			0x80000
#घोषणा PCIE_PF_OFF			0xc0000
#घोषणा PCIE_PF_INT_STAT		0x18
#घोषणा PF_INT_STAT_PABRST		BIT(31)

#घोषणा PCIE_PF_DBG			0x7fc
#घोषणा PF_DBG_LTSSM_MASK		0x3f
#घोषणा PF_DBG_LTSSM_L0			0x2d /* L0 state */
#घोषणा PF_DBG_WE			BIT(31)
#घोषणा PF_DBG_PABR			BIT(27)

#घोषणा to_ls_pcie_g4(x)		platक्रमm_get_drvdata((x)->pdev)

काष्ठा ls_pcie_g4 अणु
	काष्ठा mobiveil_pcie pci;
	काष्ठा delayed_work dwork;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत u32 ls_pcie_g4_lut_पढ़ोl(काष्ठा ls_pcie_g4 *pcie, u32 off)
अणु
	वापस ioपढ़ो32(pcie->pci.csr_axi_slave_base + PCIE_LUT_OFF + off);
पूर्ण

अटल अंतरभूत व्योम ls_pcie_g4_lut_ग_लिखोl(काष्ठा ls_pcie_g4 *pcie,
					 u32 off, u32 val)
अणु
	ioग_लिखो32(val, pcie->pci.csr_axi_slave_base + PCIE_LUT_OFF + off);
पूर्ण

अटल अंतरभूत u32 ls_pcie_g4_pf_पढ़ोl(काष्ठा ls_pcie_g4 *pcie, u32 off)
अणु
	वापस ioपढ़ो32(pcie->pci.csr_axi_slave_base + PCIE_PF_OFF + off);
पूर्ण

अटल अंतरभूत व्योम ls_pcie_g4_pf_ग_लिखोl(काष्ठा ls_pcie_g4 *pcie,
					u32 off, u32 val)
अणु
	ioग_लिखो32(val, pcie->pci.csr_axi_slave_base + PCIE_PF_OFF + off);
पूर्ण

अटल पूर्णांक ls_pcie_g4_link_up(काष्ठा mobiveil_pcie *pci)
अणु
	काष्ठा ls_pcie_g4 *pcie = to_ls_pcie_g4(pci);
	u32 state;

	state = ls_pcie_g4_pf_पढ़ोl(pcie, PCIE_PF_DBG);
	state =	state & PF_DBG_LTSSM_MASK;

	अगर (state == PF_DBG_LTSSM_L0)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम ls_pcie_g4_disable_पूर्णांकerrupt(काष्ठा ls_pcie_g4 *pcie)
अणु
	काष्ठा mobiveil_pcie *mv_pci = &pcie->pci;

	mobiveil_csr_ग_लिखोl(mv_pci, 0, PAB_INTP_AMBA_MISC_ENB);
पूर्ण

अटल व्योम ls_pcie_g4_enable_पूर्णांकerrupt(काष्ठा ls_pcie_g4 *pcie)
अणु
	काष्ठा mobiveil_pcie *mv_pci = &pcie->pci;
	u32 val;

	/* Clear the पूर्णांकerrupt status */
	mobiveil_csr_ग_लिखोl(mv_pci, 0xffffffff, PAB_INTP_AMBA_MISC_STAT);

	val = PAB_INTP_INTX_MASK | PAB_INTP_MSI | PAB_INTP_RESET |
	      PAB_INTP_PCIE_UE | PAB_INTP_IE_PMREDI | PAB_INTP_IE_EC;
	mobiveil_csr_ग_लिखोl(mv_pci, val, PAB_INTP_AMBA_MISC_ENB);
पूर्ण

अटल पूर्णांक ls_pcie_g4_reinit_hw(काष्ठा ls_pcie_g4 *pcie)
अणु
	काष्ठा mobiveil_pcie *mv_pci = &pcie->pci;
	काष्ठा device *dev = &mv_pci->pdev->dev;
	u32 val, act_stat;
	पूर्णांक to = 100;

	/* Poll क्रम pab_csb_reset to set and PAB activity to clear */
	करो अणु
		usleep_range(10, 15);
		val = ls_pcie_g4_pf_पढ़ोl(pcie, PCIE_PF_INT_STAT);
		act_stat = mobiveil_csr_पढ़ोl(mv_pci, PAB_ACTIVITY_STAT);
	पूर्ण जबतक (((val & PF_INT_STAT_PABRST) == 0 || act_stat) && to--);
	अगर (to < 0) अणु
		dev_err(dev, "Poll PABRST&PABACT timeout\n");
		वापस -EIO;
	पूर्ण

	/* clear PEX_RESET bit in PEX_PF0_DBG रेजिस्टर */
	val = ls_pcie_g4_pf_पढ़ोl(pcie, PCIE_PF_DBG);
	val |= PF_DBG_WE;
	ls_pcie_g4_pf_ग_लिखोl(pcie, PCIE_PF_DBG, val);

	val = ls_pcie_g4_pf_पढ़ोl(pcie, PCIE_PF_DBG);
	val |= PF_DBG_PABR;
	ls_pcie_g4_pf_ग_लिखोl(pcie, PCIE_PF_DBG, val);

	val = ls_pcie_g4_pf_पढ़ोl(pcie, PCIE_PF_DBG);
	val &= ~PF_DBG_WE;
	ls_pcie_g4_pf_ग_लिखोl(pcie, PCIE_PF_DBG, val);

	mobiveil_host_init(mv_pci, true);

	to = 100;
	जबतक (!ls_pcie_g4_link_up(mv_pci) && to--)
		usleep_range(200, 250);
	अगर (to < 0) अणु
		dev_err(dev, "PCIe link training timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t ls_pcie_g4_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ls_pcie_g4 *pcie = (काष्ठा ls_pcie_g4 *)dev_id;
	काष्ठा mobiveil_pcie *mv_pci = &pcie->pci;
	u32 val;

	val = mobiveil_csr_पढ़ोl(mv_pci, PAB_INTP_AMBA_MISC_STAT);
	अगर (!val)
		वापस IRQ_NONE;

	अगर (val & PAB_INTP_RESET) अणु
		ls_pcie_g4_disable_पूर्णांकerrupt(pcie);
		schedule_delayed_work(&pcie->dwork, msecs_to_jअगरfies(1));
	पूर्ण

	mobiveil_csr_ग_लिखोl(mv_pci, val, PAB_INTP_AMBA_MISC_STAT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ls_pcie_g4_पूर्णांकerrupt_init(काष्ठा mobiveil_pcie *mv_pci)
अणु
	काष्ठा ls_pcie_g4 *pcie = to_ls_pcie_g4(mv_pci);
	काष्ठा platक्रमm_device *pdev = mv_pci->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pcie->irq = platक्रमm_get_irq_byname(pdev, "intr");
	अगर (pcie->irq < 0)
		वापस pcie->irq;

	ret = devm_request_irq(dev, pcie->irq, ls_pcie_g4_isr,
			       IRQF_SHARED, pdev->name, pcie);
	अगर (ret) अणु
		dev_err(dev, "Can't register PCIe IRQ, errno = %d\n", ret);
		वापस  ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ls_pcie_g4_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = container_of(work, काष्ठा delayed_work,
						  work);
	काष्ठा ls_pcie_g4 *pcie = container_of(dwork, काष्ठा ls_pcie_g4, dwork);
	काष्ठा mobiveil_pcie *mv_pci = &pcie->pci;
	u16 ctrl;

	ctrl = mobiveil_csr_पढ़ोw(mv_pci, PCI_BRIDGE_CONTROL);
	ctrl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	mobiveil_csr_ग_लिखोw(mv_pci, ctrl, PCI_BRIDGE_CONTROL);

	अगर (!ls_pcie_g4_reinit_hw(pcie))
		वापस;

	ls_pcie_g4_enable_पूर्णांकerrupt(pcie);
पूर्ण

अटल काष्ठा mobiveil_rp_ops ls_pcie_g4_rp_ops = अणु
	.पूर्णांकerrupt_init = ls_pcie_g4_पूर्णांकerrupt_init,
पूर्ण;

अटल स्थिर काष्ठा mobiveil_pab_ops ls_pcie_g4_pab_ops = अणु
	.link_up = ls_pcie_g4_link_up,
पूर्ण;

अटल पूर्णांक __init ls_pcie_g4_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा mobiveil_pcie *mv_pci;
	काष्ठा ls_pcie_g4 *pcie;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	अगर (!of_parse_phandle(np, "msi-parent", 0)) अणु
		dev_err(dev, "Failed to find msi-parent\n");
		वापस -EINVAL;
	पूर्ण

	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	mv_pci = &pcie->pci;

	mv_pci->pdev = pdev;
	mv_pci->ops = &ls_pcie_g4_pab_ops;
	mv_pci->rp.ops = &ls_pcie_g4_rp_ops;
	mv_pci->rp.bridge = bridge;

	platक्रमm_set_drvdata(pdev, pcie);

	INIT_DELAYED_WORK(&pcie->dwork, ls_pcie_g4_reset);

	ret = mobiveil_pcie_host_probe(mv_pci);
	अगर (ret) अणु
		dev_err(dev, "Fail to probe\n");
		वापस  ret;
	पूर्ण

	ls_pcie_g4_enable_पूर्णांकerrupt(pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ls_pcie_g4_of_match[] = अणु
	अणु .compatible = "fsl,lx2160a-pcie", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ls_pcie_g4_driver = अणु
	.driver = अणु
		.name = "layerscape-pcie-gen4",
		.of_match_table = ls_pcie_g4_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver_probe(ls_pcie_g4_driver, ls_pcie_g4_probe);
