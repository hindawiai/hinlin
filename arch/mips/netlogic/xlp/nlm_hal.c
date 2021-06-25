<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/समय.स>

#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/bridge.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#समावेश <यंत्र/netlogic/xlp-hal/sys.h>

/* Main initialization */
व्योम nlm_node_init(पूर्णांक node)
अणु
	काष्ठा nlm_soc_info *nodep;

	nodep = nlm_get_node(node);
	अगर (node == 0)
		nodep->coremask = 1;	/* node 0, boot cpu */
	nodep->sysbase = nlm_get_sys_regbase(node);
	nodep->picbase = nlm_get_pic_regbase(node);
	nodep->ebase = पढ़ो_c0_ebase() & MIPS_EBASE_BASE;
	अगर (cpu_is_xlp9xx())
		nodep->socbus = xlp9xx_get_socbus(node);
	अन्यथा
		nodep->socbus = 0;
	spin_lock_init(&nodep->piघड़ी);
पूर्ण

अटल पूर्णांक xlp9xx_irq_to_irt(पूर्णांक irq)
अणु
	चयन (irq) अणु
	हाल PIC_GPIO_IRQ:
		वापस 12;
	हाल PIC_I2C_0_IRQ:
		वापस 125;
	हाल PIC_I2C_1_IRQ:
		वापस 126;
	हाल PIC_I2C_2_IRQ:
		वापस 127;
	हाल PIC_I2C_3_IRQ:
		वापस 128;
	हाल PIC_9XX_XHCI_0_IRQ:
		वापस 114;
	हाल PIC_9XX_XHCI_1_IRQ:
		वापस 115;
	हाल PIC_9XX_XHCI_2_IRQ:
		वापस 116;
	हाल PIC_UART_0_IRQ:
		वापस 133;
	हाल PIC_UART_1_IRQ:
		वापस 134;
	हाल PIC_SATA_IRQ:
		वापस 143;
	हाल PIC_न_अंकD_IRQ:
		वापस 151;
	हाल PIC_SPI_IRQ:
		वापस 152;
	हाल PIC_MMC_IRQ:
		वापस 153;
	हाल PIC_PCIE_LINK_LEGACY_IRQ(0):
	हाल PIC_PCIE_LINK_LEGACY_IRQ(1):
	हाल PIC_PCIE_LINK_LEGACY_IRQ(2):
	हाल PIC_PCIE_LINK_LEGACY_IRQ(3):
		वापस 191 + irq - PIC_PCIE_LINK_LEGACY_IRQ_BASE;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक xlp_irq_to_irt(पूर्णांक irq)
अणु
	uपूर्णांक64_t pcibase;
	पूर्णांक devoff, irt;

	devoff = 0;
	चयन (irq) अणु
	हाल PIC_UART_0_IRQ:
		devoff = XLP_IO_UART0_OFFSET(0);
		अवरोध;
	हाल PIC_UART_1_IRQ:
		devoff = XLP_IO_UART1_OFFSET(0);
		अवरोध;
	हाल PIC_MMC_IRQ:
		devoff = XLP_IO_MMC_OFFSET(0);
		अवरोध;
	हाल PIC_I2C_0_IRQ:	/* I2C will be fixed up */
	हाल PIC_I2C_1_IRQ:
	हाल PIC_I2C_2_IRQ:
	हाल PIC_I2C_3_IRQ:
		अगर (cpu_is_xlpii())
			devoff = XLP2XX_IO_I2C_OFFSET(0);
		अन्यथा
			devoff = XLP_IO_I2C0_OFFSET(0);
		अवरोध;
	हाल PIC_SATA_IRQ:
		devoff = XLP_IO_SATA_OFFSET(0);
		अवरोध;
	हाल PIC_GPIO_IRQ:
		devoff = XLP_IO_GPIO_OFFSET(0);
		अवरोध;
	हाल PIC_न_अंकD_IRQ:
		devoff = XLP_IO_न_अंकD_OFFSET(0);
		अवरोध;
	हाल PIC_SPI_IRQ:
		devoff = XLP_IO_SPI_OFFSET(0);
		अवरोध;
	शेष:
		अगर (cpu_is_xlpii()) अणु
			चयन (irq) अणु
				/* XLP2XX has three XHCI USB controller */
			हाल PIC_2XX_XHCI_0_IRQ:
				devoff = XLP2XX_IO_USB_XHCI0_OFFSET(0);
				अवरोध;
			हाल PIC_2XX_XHCI_1_IRQ:
				devoff = XLP2XX_IO_USB_XHCI1_OFFSET(0);
				अवरोध;
			हाल PIC_2XX_XHCI_2_IRQ:
				devoff = XLP2XX_IO_USB_XHCI2_OFFSET(0);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (irq) अणु
			हाल PIC_EHCI_0_IRQ:
				devoff = XLP_IO_USB_EHCI0_OFFSET(0);
				अवरोध;
			हाल PIC_EHCI_1_IRQ:
				devoff = XLP_IO_USB_EHCI1_OFFSET(0);
				अवरोध;
			हाल PIC_OHCI_0_IRQ:
				devoff = XLP_IO_USB_OHCI0_OFFSET(0);
				अवरोध;
			हाल PIC_OHCI_1_IRQ:
				devoff = XLP_IO_USB_OHCI1_OFFSET(0);
				अवरोध;
			हाल PIC_OHCI_2_IRQ:
				devoff = XLP_IO_USB_OHCI2_OFFSET(0);
				अवरोध;
			हाल PIC_OHCI_3_IRQ:
				devoff = XLP_IO_USB_OHCI3_OFFSET(0);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (devoff != 0) अणु
		uपूर्णांक32_t val;

		pcibase = nlm_pcicfg_base(devoff);
		val = nlm_पढ़ो_reg(pcibase, XLP_PCI_IRTINFO_REG);
		अगर (val == 0xffffffff) अणु
			irt = -1;
		पूर्ण अन्यथा अणु
			irt = val & 0xffff;
			/* HW weirdness, I2C IRT entry has to be fixed up */
			चयन (irq) अणु
			हाल PIC_I2C_1_IRQ:
				irt = irt + 1; अवरोध;
			हाल PIC_I2C_2_IRQ:
				irt = irt + 2; अवरोध;
			हाल PIC_I2C_3_IRQ:
				irt = irt + 3; अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (irq >= PIC_PCIE_LINK_LEGACY_IRQ(0) &&
			irq <= PIC_PCIE_LINK_LEGACY_IRQ(3)) अणु
		/* HW bug, PCI IRT entries are bad on early silicon, fix */
		irt = PIC_IRT_PCIE_LINK_INDEX(irq -
					PIC_PCIE_LINK_LEGACY_IRQ_BASE);
	पूर्ण अन्यथा अणु
		irt = -1;
	पूर्ण
	वापस irt;
पूर्ण

पूर्णांक nlm_irq_to_irt(पूर्णांक irq)
अणु
	/* वापस -2 क्रम irqs without 1-1 mapping */
	अगर (irq >= PIC_PCIE_LINK_MSI_IRQ(0) && irq <= PIC_PCIE_LINK_MSI_IRQ(3))
		वापस -2;
	अगर (irq >= PIC_PCIE_MSIX_IRQ(0) && irq <= PIC_PCIE_MSIX_IRQ(3))
		वापस -2;

	अगर (cpu_is_xlp9xx())
		वापस xlp9xx_irq_to_irt(irq);
	अन्यथा
		वापस xlp_irq_to_irt(irq);
पूर्ण

अटल अचिन्हित पूर्णांक nlm_xlp2_get_core_frequency(पूर्णांक node, पूर्णांक core)
अणु
	अचिन्हित पूर्णांक pll_post_भाग, ctrl_val0, ctrl_val1, denom;
	uपूर्णांक64_t num, sysbase, घड़ीbase;

	अगर (cpu_is_xlp9xx()) अणु
		घड़ीbase = nlm_get_घड़ी_regbase(node);
		ctrl_val0 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_CPU_PLL_CTRL0(core));
		ctrl_val1 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_CPU_PLL_CTRL1(core));
	पूर्ण अन्यथा अणु
		sysbase = nlm_get_node(node)->sysbase;
		ctrl_val0 = nlm_पढ़ो_sys_reg(sysbase,
						SYS_CPU_PLL_CTRL0(core));
		ctrl_val1 = nlm_पढ़ो_sys_reg(sysbase,
						SYS_CPU_PLL_CTRL1(core));
	पूर्ण

	/* Find PLL post भागider value */
	चयन ((ctrl_val0 >> 24) & 0x7) अणु
	हाल 1:
		pll_post_भाग = 2;
		अवरोध;
	हाल 3:
		pll_post_भाग = 4;
		अवरोध;
	हाल 7:
		pll_post_भाग = 8;
		अवरोध;
	हाल 6:
		pll_post_भाग = 16;
		अवरोध;
	हाल 0:
	शेष:
		pll_post_भाग = 1;
		अवरोध;
	पूर्ण

	num = 1000000ULL * (400 * 3 + 100 * (ctrl_val1 & 0x3f));
	denom = 3 * pll_post_भाग;
	करो_भाग(num, denom);

	वापस (अचिन्हित पूर्णांक)num;
पूर्ण

अटल अचिन्हित पूर्णांक nlm_xlp_get_core_frequency(पूर्णांक node, पूर्णांक core)
अणु
	अचिन्हित पूर्णांक pll_भागf, pll_भागr, dfs_भाग, ext_भाग;
	अचिन्हित पूर्णांक rstval, dfsval, denom;
	uपूर्णांक64_t num, sysbase;

	sysbase = nlm_get_node(node)->sysbase;
	rstval = nlm_पढ़ो_sys_reg(sysbase, SYS_POWER_ON_RESET_CFG);
	dfsval = nlm_पढ़ो_sys_reg(sysbase, SYS_CORE_DFS_DIV_VALUE);
	pll_भागf = ((rstval >> 10) & 0x7f) + 1;
	pll_भागr = ((rstval >> 8)  & 0x3) + 1;
	ext_भाग  = ((rstval >> 30) & 0x3) + 1;
	dfs_भाग  = ((dfsval >> (core * 4)) & 0xf) + 1;

	num = 800000000ULL * pll_भागf;
	denom = 3 * pll_भागr * ext_भाग * dfs_भाग;
	करो_भाग(num, denom);

	वापस (अचिन्हित पूर्णांक)num;
पूर्ण

अचिन्हित पूर्णांक nlm_get_core_frequency(पूर्णांक node, पूर्णांक core)
अणु
	अगर (cpu_is_xlpii())
		वापस nlm_xlp2_get_core_frequency(node, core);
	अन्यथा
		वापस nlm_xlp_get_core_frequency(node, core);
पूर्ण

/*
 * Calculate PIC frequency from PLL रेजिस्टरs.
 * freq_out = (ref_freq/2 * (6 + ctrl2[7:0]) + ctrl2[20:8]/2^13) /
 * 		((2^ctrl0[7:5]) * Table(ctrl0[26:24]))
 */
अटल अचिन्हित पूर्णांक nlm_xlp2_get_pic_frequency(पूर्णांक node)
अणु
	u32 ctrl_val0, ctrl_val2, vco_post_भाग, pll_post_भाग, cpu_xlp9xx;
	u32 mभाग, fभाग, pll_out_freq_den, reg_select, ref_भाग, pic_भाग;
	u64 sysbase, pll_out_freq_num, ref_clk_select, घड़ीbase, ref_clk;

	sysbase = nlm_get_node(node)->sysbase;
	घड़ीbase = nlm_get_घड़ी_regbase(node);
	cpu_xlp9xx = cpu_is_xlp9xx();

	/* Find ref_clk_base */
	अगर (cpu_xlp9xx)
		ref_clk_select = (nlm_पढ़ो_sys_reg(sysbase,
				SYS_9XX_POWER_ON_RESET_CFG) >> 18) & 0x3;
	अन्यथा
		ref_clk_select = (nlm_पढ़ो_sys_reg(sysbase,
					SYS_POWER_ON_RESET_CFG) >> 18) & 0x3;
	चयन (ref_clk_select) अणु
	हाल 0:
		ref_clk = 200000000ULL;
		ref_भाग = 3;
		अवरोध;
	हाल 1:
		ref_clk = 100000000ULL;
		ref_भाग = 1;
		अवरोध;
	हाल 2:
		ref_clk = 125000000ULL;
		ref_भाग = 1;
		अवरोध;
	हाल 3:
		ref_clk = 400000000ULL;
		ref_भाग = 3;
		अवरोध;
	पूर्ण

	/* Find the घड़ी source PLL device क्रम PIC */
	अगर (cpu_xlp9xx) अणु
		reg_select = nlm_पढ़ो_sys_reg(घड़ीbase,
				SYS_9XX_CLK_DEV_SEL_REG) & 0x3;
		चयन (reg_select) अणु
		हाल 0:
			ctrl_val0 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL0);
			ctrl_val2 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL2);
			अवरोध;
		हाल 1:
			ctrl_val0 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL0_DEVX(0));
			ctrl_val2 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL2_DEVX(0));
			अवरोध;
		हाल 2:
			ctrl_val0 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL0_DEVX(1));
			ctrl_val2 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL2_DEVX(1));
			अवरोध;
		हाल 3:
			ctrl_val0 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL0_DEVX(2));
			ctrl_val2 = nlm_पढ़ो_sys_reg(घड़ीbase,
					SYS_9XX_PLL_CTRL2_DEVX(2));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		reg_select = (nlm_पढ़ो_sys_reg(sysbase,
					SYS_CLK_DEV_SEL_REG) >> 22) & 0x3;
		चयन (reg_select) अणु
		हाल 0:
			ctrl_val0 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL0);
			ctrl_val2 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL2);
			अवरोध;
		हाल 1:
			ctrl_val0 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL0_DEVX(0));
			ctrl_val2 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL2_DEVX(0));
			अवरोध;
		हाल 2:
			ctrl_val0 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL0_DEVX(1));
			ctrl_val2 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL2_DEVX(1));
			अवरोध;
		हाल 3:
			ctrl_val0 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL0_DEVX(2));
			ctrl_val2 = nlm_पढ़ो_sys_reg(sysbase,
					SYS_PLL_CTRL2_DEVX(2));
			अवरोध;
		पूर्ण
	पूर्ण

	vco_post_भाग = (ctrl_val0 >> 5) & 0x7;
	pll_post_भाग = (ctrl_val0 >> 24) & 0x7;
	mभाग = ctrl_val2 & 0xff;
	fभाग = (ctrl_val2 >> 8) & 0x1fff;

	/* Find PLL post भागider value */
	चयन (pll_post_भाग) अणु
	हाल 1:
		pll_post_भाग = 2;
		अवरोध;
	हाल 3:
		pll_post_भाग = 4;
		अवरोध;
	हाल 7:
		pll_post_भाग = 8;
		अवरोध;
	हाल 6:
		pll_post_भाग = 16;
		अवरोध;
	हाल 0:
	शेष:
		pll_post_भाग = 1;
		अवरोध;
	पूर्ण

	fभाग = fभाग/(1 << 13);
	pll_out_freq_num = ((ref_clk >> 1) * (6 + mभाग)) + fभाग;
	pll_out_freq_den = (1 << vco_post_भाग) * pll_post_भाग * ref_भाग;

	अगर (pll_out_freq_den > 0)
		करो_भाग(pll_out_freq_num, pll_out_freq_den);

	/* PIC post भागider, which happens after PLL */
	अगर (cpu_xlp9xx)
		pic_भाग = nlm_पढ़ो_sys_reg(घड़ीbase,
				SYS_9XX_CLK_DEV_DIV_REG) & 0x3;
	अन्यथा
		pic_भाग = (nlm_पढ़ो_sys_reg(sysbase,
					SYS_CLK_DEV_DIV_REG) >> 22) & 0x3;
	करो_भाग(pll_out_freq_num, 1 << pic_भाग);

	वापस pll_out_freq_num;
पूर्ण

अचिन्हित पूर्णांक nlm_get_pic_frequency(पूर्णांक node)
अणु
	अगर (cpu_is_xlpii())
		वापस nlm_xlp2_get_pic_frequency(node);
	अन्यथा
		वापस 133333333;
पूर्ण

अचिन्हित पूर्णांक nlm_get_cpu_frequency(व्योम)
अणु
	वापस nlm_get_core_frequency(0, 0);
पूर्ण

/*
 * Fills upto 8 pairs of entries containing the DRAM map of a node
 * अगर node < 0, get dram map क्रम all nodes
 */
पूर्णांक nlm_get_dram_map(पूर्णांक node, uपूर्णांक64_t *dram_map, पूर्णांक nentries)
अणु
	uपूर्णांक64_t bridgebase, base, lim;
	uपूर्णांक32_t val;
	अचिन्हित पूर्णांक barreg, limreg, xlatreg;
	पूर्णांक i, n, rv;

	/* Look only at mapping on Node 0, we करोn't handle crazy configs */
	bridgebase = nlm_get_bridge_regbase(0);
	rv = 0;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (rv + 1 >= nentries)
			अवरोध;
		अगर (cpu_is_xlp9xx()) अणु
			barreg = BRIDGE_9XX_DRAM_BAR(i);
			limreg = BRIDGE_9XX_DRAM_LIMIT(i);
			xlatreg = BRIDGE_9XX_DRAM_NODE_TRANSLN(i);
		पूर्ण अन्यथा अणु
			barreg = BRIDGE_DRAM_BAR(i);
			limreg = BRIDGE_DRAM_LIMIT(i);
			xlatreg = BRIDGE_DRAM_NODE_TRANSLN(i);
		पूर्ण
		अगर (node >= 0) अणु
			/* node specअगरied, get node mapping of BAR */
			val = nlm_पढ़ो_bridge_reg(bridgebase, xlatreg);
			n = (val >> 1) & 0x3;
			अगर (n != node)
				जारी;
		पूर्ण
		val = nlm_पढ़ो_bridge_reg(bridgebase, barreg);
		val = (val >>  12) & 0xfffff;
		base = (uपूर्णांक64_t) val << 20;
		val = nlm_पढ़ो_bridge_reg(bridgebase, limreg);
		val = (val >>  12) & 0xfffff;
		अगर (val == 0)   /* BAR not used */
			जारी;
		lim = ((uपूर्णांक64_t)val + 1) << 20;
		dram_map[rv] = base;
		dram_map[rv + 1] = lim;
		rv += 2;
	पूर्ण
	वापस rv;
पूर्ण
