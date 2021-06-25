<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Parts of this file are based on Ralink's 2.6.21 BSP
 *
 * Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mach-ralink/ralink_regs.h>
#समावेश <यंत्र/mach-ralink/rt3883.h>
#समावेश <यंत्र/mach-ralink/pinmux.h>

#समावेश "common.h"

अटल काष्ठा rt2880_pmx_func i2c_func[] =  अणु FUNC("i2c", 0, 1, 2) पूर्ण;
अटल काष्ठा rt2880_pmx_func spi_func[] = अणु FUNC("spi", 0, 3, 4) पूर्ण;
अटल काष्ठा rt2880_pmx_func uartf_func[] = अणु
	FUNC("uartf", RT3883_GPIO_MODE_UARTF, 7, 8),
	FUNC("pcm uartf", RT3883_GPIO_MODE_PCM_UARTF, 7, 8),
	FUNC("pcm i2s", RT3883_GPIO_MODE_PCM_I2S, 7, 8),
	FUNC("i2s uartf", RT3883_GPIO_MODE_I2S_UARTF, 7, 8),
	FUNC("pcm gpio", RT3883_GPIO_MODE_PCM_GPIO, 11, 4),
	FUNC("gpio uartf", RT3883_GPIO_MODE_GPIO_UARTF, 7, 4),
	FUNC("gpio i2s", RT3883_GPIO_MODE_GPIO_I2S, 7, 4),
पूर्ण;
अटल काष्ठा rt2880_pmx_func uartlite_func[] = अणु FUNC("uartlite", 0, 15, 2) पूर्ण;
अटल काष्ठा rt2880_pmx_func jtag_func[] = अणु FUNC("jtag", 0, 17, 5) पूर्ण;
अटल काष्ठा rt2880_pmx_func mdio_func[] = अणु FUNC("mdio", 0, 22, 2) पूर्ण;
अटल काष्ठा rt2880_pmx_func lna_a_func[] = अणु FUNC("lna a", 0, 32, 3) पूर्ण;
अटल काष्ठा rt2880_pmx_func lna_g_func[] = अणु FUNC("lna g", 0, 35, 3) पूर्ण;
अटल काष्ठा rt2880_pmx_func pci_func[] = अणु
	FUNC("pci-dev", 0, 40, 32),
	FUNC("pci-host2", 1, 40, 32),
	FUNC("pci-host1", 2, 40, 32),
	FUNC("pci-fnc", 3, 40, 32)
पूर्ण;
अटल काष्ठा rt2880_pmx_func ge1_func[] = अणु FUNC("ge1", 0, 72, 12) पूर्ण;
अटल काष्ठा rt2880_pmx_func ge2_func[] = अणु FUNC("ge2", 0, 84, 12) पूर्ण;

अटल काष्ठा rt2880_pmx_group rt3883_pinmux_data[] = अणु
	GRP("i2c", i2c_func, 1, RT3883_GPIO_MODE_I2C),
	GRP("spi", spi_func, 1, RT3883_GPIO_MODE_SPI),
	GRP("uartf", uartf_func, RT3883_GPIO_MODE_UART0_MASK,
		RT3883_GPIO_MODE_UART0_SHIFT),
	GRP("uartlite", uartlite_func, 1, RT3883_GPIO_MODE_UART1),
	GRP("jtag", jtag_func, 1, RT3883_GPIO_MODE_JTAG),
	GRP("mdio", mdio_func, 1, RT3883_GPIO_MODE_MDIO),
	GRP("lna a", lna_a_func, 1, RT3883_GPIO_MODE_LNA_A),
	GRP("lna g", lna_g_func, 1, RT3883_GPIO_MODE_LNA_G),
	GRP("pci", pci_func, RT3883_GPIO_MODE_PCI_MASK,
		RT3883_GPIO_MODE_PCI_SHIFT),
	GRP("ge1", ge1_func, 1, RT3883_GPIO_MODE_GE1),
	GRP("ge2", ge2_func, 1, RT3883_GPIO_MODE_GE2),
	अणु 0 पूर्ण
पूर्ण;

व्योम __init ralink_clk_init(व्योम)
अणु
	अचिन्हित दीर्घ cpu_rate, sys_rate;
	u32 syscfg0;
	u32 clksel;
	u32 ddr2;

	syscfg0 = rt_sysc_r32(RT3883_SYSC_REG_SYSCFG0);
	clksel = ((syscfg0 >> RT3883_SYSCFG0_CPUCLK_SHIFT) &
		RT3883_SYSCFG0_CPUCLK_MASK);
	ddr2 = syscfg0 & RT3883_SYSCFG0_DRAM_TYPE_DDR2;

	चयन (clksel) अणु
	हाल RT3883_SYSCFG0_CPUCLK_250:
		cpu_rate = 250000000;
		sys_rate = (ddr2) ? 125000000 : 83000000;
		अवरोध;
	हाल RT3883_SYSCFG0_CPUCLK_384:
		cpu_rate = 384000000;
		sys_rate = (ddr2) ? 128000000 : 96000000;
		अवरोध;
	हाल RT3883_SYSCFG0_CPUCLK_480:
		cpu_rate = 480000000;
		sys_rate = (ddr2) ? 160000000 : 120000000;
		अवरोध;
	हाल RT3883_SYSCFG0_CPUCLK_500:
		cpu_rate = 500000000;
		sys_rate = (ddr2) ? 166000000 : 125000000;
		अवरोध;
	पूर्ण

	ralink_clk_add("cpu", cpu_rate);
	ralink_clk_add("10000100.timer", sys_rate);
	ralink_clk_add("10000120.watchdog", sys_rate);
	ralink_clk_add("10000500.uart", 40000000);
	ralink_clk_add("10000900.i2c", 40000000);
	ralink_clk_add("10000a00.i2s", 40000000);
	ralink_clk_add("10000b00.spi", sys_rate);
	ralink_clk_add("10000b40.spi", sys_rate);
	ralink_clk_add("10000c00.uartlite", 40000000);
	ralink_clk_add("10100000.ethernet", sys_rate);
	ralink_clk_add("10180000.wmac", 40000000);
पूर्ण

व्योम __init ralink_of_remap(व्योम)
अणु
	rt_sysc_membase = plat_of_remap_node("ralink,rt3883-sysc");
	rt_memc_membase = plat_of_remap_node("ralink,rt3883-memc");

	अगर (!rt_sysc_membase || !rt_memc_membase)
		panic("Failed to remap core resources");
पूर्ण

व्योम __init prom_soc_init(काष्ठा ralink_soc_info *soc_info)
अणु
	व्योम __iomem *sysc = (व्योम __iomem *) KSEG1ADDR(RT3883_SYSC_BASE);
	स्थिर अक्षर *name;
	u32 n0;
	u32 n1;
	u32 id;

	n0 = __raw_पढ़ोl(sysc + RT3883_SYSC_REG_CHIPID0_3);
	n1 = __raw_पढ़ोl(sysc + RT3883_SYSC_REG_CHIPID4_7);
	id = __raw_पढ़ोl(sysc + RT3883_SYSC_REG_REVID);

	अगर (n0 == RT3883_CHIP_NAME0 && n1 == RT3883_CHIP_NAME1) अणु
		soc_info->compatible = "ralink,rt3883-soc";
		name = "RT3883";
	पूर्ण अन्यथा अणु
		panic("rt3883: unknown SoC, n0:%08x n1:%08x", n0, n1);
	पूर्ण

	snम_लिखो(soc_info->sys_type, RAMIPS_SYS_TYPE_LEN,
		"Ralink %s ver:%u eco:%u",
		name,
		(id >> RT3883_REVID_VER_ID_SHIFT) & RT3883_REVID_VER_ID_MASK,
		(id & RT3883_REVID_ECO_ID_MASK));

	soc_info->mem_base = RT3883_SDRAM_BASE;
	soc_info->mem_size_min = RT3883_MEM_SIZE_MIN;
	soc_info->mem_size_max = RT3883_MEM_SIZE_MAX;

	rt2880_pinmux_data = rt3883_pinmux_data;

	ralink_soc = RT3883_SOC;
पूर्ण
