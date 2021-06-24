<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Mobiveil PCIe Host controller
 *
 * Copyright (c) 2018 Mobiveil Inc.
 * Copyright 2019 NXP
 *
 * Author: Subrahmanya Lingappa <l.subrahmanya@mobiveil.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pcie-mobiveil.h"

/*
 * mobiveil_pcie_sel_page - routine to access paged रेजिस्टर
 *
 * Registers whose address greater than PAGED_ADDR_BNDRY (0xc00) are paged,
 * क्रम this scheme to work extracted higher 6 bits of the offset will be
 * written to pg_sel field of PAB_CTRL रेजिस्टर and rest of the lower 10
 * bits enabled with PAGED_ADDR_BNDRY are used as offset of the रेजिस्टर.
 */
अटल व्योम mobiveil_pcie_sel_page(काष्ठा mobiveil_pcie *pcie, u8 pg_idx)
अणु
	u32 val;

	val = पढ़ोl(pcie->csr_axi_slave_base + PAB_CTRL);
	val &= ~(PAGE_SEL_MASK << PAGE_SEL_SHIFT);
	val |= (pg_idx & PAGE_SEL_MASK) << PAGE_SEL_SHIFT;

	ग_लिखोl(val, pcie->csr_axi_slave_base + PAB_CTRL);
पूर्ण

अटल व्योम __iomem *mobiveil_pcie_comp_addr(काष्ठा mobiveil_pcie *pcie,
					     u32 off)
अणु
	अगर (off < PAGED_ADDR_BNDRY) अणु
		/* For directly accessed रेजिस्टरs, clear the pg_sel field */
		mobiveil_pcie_sel_page(pcie, 0);
		वापस pcie->csr_axi_slave_base + off;
	पूर्ण

	mobiveil_pcie_sel_page(pcie, OFFSET_TO_PAGE_IDX(off));
	वापस pcie->csr_axi_slave_base + OFFSET_TO_PAGE_ADDR(off);
पूर्ण

अटल पूर्णांक mobiveil_pcie_पढ़ो(व्योम __iomem *addr, पूर्णांक size, u32 *val)
अणु
	अगर ((uपूर्णांकptr_t)addr & (size - 1)) अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	चयन (size) अणु
	हाल 4:
		*val = पढ़ोl(addr);
		अवरोध;
	हाल 2:
		*val = पढ़ोw(addr);
		अवरोध;
	हाल 1:
		*val = पढ़ोb(addr);
		अवरोध;
	शेष:
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक mobiveil_pcie_ग_लिखो(व्योम __iomem *addr, पूर्णांक size, u32 val)
अणु
	अगर ((uपूर्णांकptr_t)addr & (size - 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	चयन (size) अणु
	हाल 4:
		ग_लिखोl(val, addr);
		अवरोध;
	हाल 2:
		ग_लिखोw(val, addr);
		अवरोध;
	हाल 1:
		ग_लिखोb(val, addr);
		अवरोध;
	शेष:
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

u32 mobiveil_csr_पढ़ो(काष्ठा mobiveil_pcie *pcie, u32 off, माप_प्रकार size)
अणु
	व्योम __iomem *addr;
	u32 val;
	पूर्णांक ret;

	addr = mobiveil_pcie_comp_addr(pcie, off);

	ret = mobiveil_pcie_पढ़ो(addr, size, &val);
	अगर (ret)
		dev_err(&pcie->pdev->dev, "read CSR address failed\n");

	वापस val;
पूर्ण

व्योम mobiveil_csr_ग_लिखो(काष्ठा mobiveil_pcie *pcie, u32 val, u32 off,
			       माप_प्रकार size)
अणु
	व्योम __iomem *addr;
	पूर्णांक ret;

	addr = mobiveil_pcie_comp_addr(pcie, off);

	ret = mobiveil_pcie_ग_लिखो(addr, size, val);
	अगर (ret)
		dev_err(&pcie->pdev->dev, "write CSR address failed\n");
पूर्ण

bool mobiveil_pcie_link_up(काष्ठा mobiveil_pcie *pcie)
अणु
	अगर (pcie->ops->link_up)
		वापस pcie->ops->link_up(pcie);

	वापस (mobiveil_csr_पढ़ोl(pcie, LTSSM_STATUS) &
		LTSSM_STATUS_L0_MASK) == LTSSM_STATUS_L0;
पूर्ण

व्योम program_ib_winकरोws(काष्ठा mobiveil_pcie *pcie, पूर्णांक win_num,
			u64 cpu_addr, u64 pci_addr, u32 type, u64 size)
अणु
	u32 value;
	u64 size64 = ~(size - 1);

	अगर (win_num >= pcie->ppio_wins) अणु
		dev_err(&pcie->pdev->dev,
			"ERROR: max inbound windows reached !\n");
		वापस;
	पूर्ण

	value = mobiveil_csr_पढ़ोl(pcie, PAB_PEX_AMAP_CTRL(win_num));
	value &= ~(AMAP_CTRL_TYPE_MASK << AMAP_CTRL_TYPE_SHIFT | WIN_SIZE_MASK);
	value |= type << AMAP_CTRL_TYPE_SHIFT | 1 << AMAP_CTRL_EN_SHIFT |
		 (lower_32_bits(size64) & WIN_SIZE_MASK);
	mobiveil_csr_ग_लिखोl(pcie, value, PAB_PEX_AMAP_CTRL(win_num));

	mobiveil_csr_ग_लिखोl(pcie, upper_32_bits(size64),
			    PAB_EXT_PEX_AMAP_SIZEN(win_num));

	mobiveil_csr_ग_लिखोl(pcie, lower_32_bits(cpu_addr),
			    PAB_PEX_AMAP_AXI_WIN(win_num));
	mobiveil_csr_ग_लिखोl(pcie, upper_32_bits(cpu_addr),
			    PAB_EXT_PEX_AMAP_AXI_WIN(win_num));

	mobiveil_csr_ग_लिखोl(pcie, lower_32_bits(pci_addr),
			    PAB_PEX_AMAP_PEX_WIN_L(win_num));
	mobiveil_csr_ग_लिखोl(pcie, upper_32_bits(pci_addr),
			    PAB_PEX_AMAP_PEX_WIN_H(win_num));

	pcie->ib_wins_configured++;
पूर्ण

/*
 * routine to program the outbound winकरोws
 */
व्योम program_ob_winकरोws(काष्ठा mobiveil_pcie *pcie, पूर्णांक win_num,
			u64 cpu_addr, u64 pci_addr, u32 type, u64 size)
अणु
	u32 value;
	u64 size64 = ~(size - 1);

	अगर (win_num >= pcie->apio_wins) अणु
		dev_err(&pcie->pdev->dev,
			"ERROR: max outbound windows reached !\n");
		वापस;
	पूर्ण

	/*
	 * program Enable Bit to 1, Type Bit to (00) base 2, AXI Winकरोw Size Bit
	 * to 4 KB in PAB_AXI_AMAP_CTRL रेजिस्टर
	 */
	value = mobiveil_csr_पढ़ोl(pcie, PAB_AXI_AMAP_CTRL(win_num));
	value &= ~(WIN_TYPE_MASK << WIN_TYPE_SHIFT | WIN_SIZE_MASK);
	value |= 1 << WIN_ENABLE_SHIFT | type << WIN_TYPE_SHIFT |
		 (lower_32_bits(size64) & WIN_SIZE_MASK);
	mobiveil_csr_ग_लिखोl(pcie, value, PAB_AXI_AMAP_CTRL(win_num));

	mobiveil_csr_ग_लिखोl(pcie, upper_32_bits(size64),
			    PAB_EXT_AXI_AMAP_SIZE(win_num));

	/*
	 * program AXI winकरोw base with appropriate value in
	 * PAB_AXI_AMAP_AXI_WIN0 रेजिस्टर
	 */
	mobiveil_csr_ग_लिखोl(pcie,
			    lower_32_bits(cpu_addr) & (~AXI_WINDOW_ALIGN_MASK),
			    PAB_AXI_AMAP_AXI_WIN(win_num));
	mobiveil_csr_ग_लिखोl(pcie, upper_32_bits(cpu_addr),
			    PAB_EXT_AXI_AMAP_AXI_WIN(win_num));

	mobiveil_csr_ग_लिखोl(pcie, lower_32_bits(pci_addr),
			    PAB_AXI_AMAP_PEX_WIN_L(win_num));
	mobiveil_csr_ग_लिखोl(pcie, upper_32_bits(pci_addr),
			    PAB_AXI_AMAP_PEX_WIN_H(win_num));

	pcie->ob_wins_configured++;
पूर्ण

पूर्णांक mobiveil_bringup_link(काष्ठा mobiveil_pcie *pcie)
अणु
	पूर्णांक retries;

	/* check अगर the link is up or not */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) अणु
		अगर (mobiveil_pcie_link_up(pcie))
			वापस 0;

		usleep_range(LINK_WAIT_MIN, LINK_WAIT_MAX);
	पूर्ण

	dev_err(&pcie->pdev->dev, "link never came up\n");

	वापस -ETIMEDOUT;
पूर्ण
