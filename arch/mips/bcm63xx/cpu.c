<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2009 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_irq.h>

स्थिर अचिन्हित दीर्घ *bcm63xx_regs_base;
EXPORT_SYMBOL(bcm63xx_regs_base);

स्थिर पूर्णांक *bcm63xx_irqs;
EXPORT_SYMBOL(bcm63xx_irqs);

u16 bcm63xx_cpu_id __पढ़ो_mostly;
EXPORT_SYMBOL(bcm63xx_cpu_id);

अटल u8 bcm63xx_cpu_rev;
अटल अचिन्हित पूर्णांक bcm63xx_cpu_freq;
अटल अचिन्हित पूर्णांक bcm63xx_memory_size;

अटल स्थिर अचिन्हित दीर्घ bcm3368_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(3368)
पूर्ण;

अटल स्थिर पूर्णांक bcm3368_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(3368)
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6328_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6328)
पूर्ण;

अटल स्थिर पूर्णांक bcm6328_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6328)
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6338_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6338)
पूर्ण;

अटल स्थिर पूर्णांक bcm6338_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6338)
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6345_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6345)
पूर्ण;

अटल स्थिर पूर्णांक bcm6345_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6345)
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6348_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6348)
पूर्ण;

अटल स्थिर पूर्णांक bcm6348_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6348)

पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6358_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6358)
पूर्ण;

अटल स्थिर पूर्णांक bcm6358_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6358)

पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6362_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6362)
पूर्ण;

अटल स्थिर पूर्णांक bcm6362_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6362)

पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6368_regs_base[] = अणु
	__GEN_CPU_REGS_TABLE(6368)
पूर्ण;

अटल स्थिर पूर्णांक bcm6368_irqs[] = अणु
	__GEN_CPU_IRQ_TABLE(6368)

पूर्ण;

u8 bcm63xx_get_cpu_rev(व्योम)
अणु
	वापस bcm63xx_cpu_rev;
पूर्ण

EXPORT_SYMBOL(bcm63xx_get_cpu_rev);

अचिन्हित पूर्णांक bcm63xx_get_cpu_freq(व्योम)
अणु
	वापस bcm63xx_cpu_freq;
पूर्ण

अचिन्हित पूर्णांक bcm63xx_get_memory_size(व्योम)
अणु
	वापस bcm63xx_memory_size;
पूर्ण

अटल अचिन्हित पूर्णांक detect_cpu_घड़ी(व्योम)
अणु
	u16 cpu_id = bcm63xx_get_cpu_id();

	चयन (cpu_id) अणु
	हाल BCM3368_CPU_ID:
		वापस 300000000;

	हाल BCM6328_CPU_ID:
	अणु
		अचिन्हित पूर्णांक पंचांगp, mips_pll_fcvo;

		पंचांगp = bcm_misc_पढ़ोl(MISC_STRAPBUS_6328_REG);
		mips_pll_fcvo = (पंचांगp & STRAPBUS_6328_FCVO_MASK)
				>> STRAPBUS_6328_FCVO_SHIFT;

		चयन (mips_pll_fcvo) अणु
		हाल 0x12:
		हाल 0x14:
		हाल 0x19:
			वापस 160000000;
		हाल 0x1c:
			वापस 192000000;
		हाल 0x13:
		हाल 0x15:
			वापस 200000000;
		हाल 0x1a:
			वापस 384000000;
		हाल 0x16:
			वापस 400000000;
		शेष:
			वापस 320000000;
		पूर्ण

	पूर्ण
	हाल BCM6338_CPU_ID:
		/* BCM6338 has a fixed 240 Mhz frequency */
		वापस 240000000;

	हाल BCM6345_CPU_ID:
		/* BCM6345 has a fixed 140Mhz frequency */
		वापस 140000000;

	हाल BCM6348_CPU_ID:
	अणु
		अचिन्हित पूर्णांक पंचांगp, n1, n2, m1;

		/* 16MHz * (N1 + 1) * (N2 + 2) / (M1_CPU + 1) */
		पंचांगp = bcm_perf_पढ़ोl(PERF_MIPSPLLCTL_REG);
		n1 = (पंचांगp & MIPSPLLCTL_N1_MASK) >> MIPSPLLCTL_N1_SHIFT;
		n2 = (पंचांगp & MIPSPLLCTL_N2_MASK) >> MIPSPLLCTL_N2_SHIFT;
		m1 = (पंचांगp & MIPSPLLCTL_M1CPU_MASK) >> MIPSPLLCTL_M1CPU_SHIFT;
		n1 += 1;
		n2 += 2;
		m1 += 1;
		वापस (16 * 1000000 * n1 * n2) / m1;
	पूर्ण

	हाल BCM6358_CPU_ID:
	अणु
		अचिन्हित पूर्णांक पंचांगp, n1, n2, m1;

		/* 16MHz * N1 * N2 / M1_CPU */
		पंचांगp = bcm_ddr_पढ़ोl(DDR_DMIPSPLLCFG_REG);
		n1 = (पंचांगp & DMIPSPLLCFG_N1_MASK) >> DMIPSPLLCFG_N1_SHIFT;
		n2 = (पंचांगp & DMIPSPLLCFG_N2_MASK) >> DMIPSPLLCFG_N2_SHIFT;
		m1 = (पंचांगp & DMIPSPLLCFG_M1_MASK) >> DMIPSPLLCFG_M1_SHIFT;
		वापस (16 * 1000000 * n1 * n2) / m1;
	पूर्ण

	हाल BCM6362_CPU_ID:
	अणु
		अचिन्हित पूर्णांक पंचांगp, mips_pll_fcvo;

		पंचांगp = bcm_misc_पढ़ोl(MISC_STRAPBUS_6362_REG);
		mips_pll_fcvo = (पंचांगp & STRAPBUS_6362_FCVO_MASK)
				>> STRAPBUS_6362_FCVO_SHIFT;
		चयन (mips_pll_fcvo) अणु
		हाल 0x03:
		हाल 0x0b:
		हाल 0x13:
		हाल 0x1b:
			वापस 240000000;
		हाल 0x04:
		हाल 0x0c:
		हाल 0x14:
		हाल 0x1c:
			वापस 160000000;
		हाल 0x05:
		हाल 0x0e:
		हाल 0x16:
		हाल 0x1e:
		हाल 0x1f:
			वापस 400000000;
		हाल 0x06:
			वापस 440000000;
		हाल 0x07:
		हाल 0x17:
			वापस 384000000;
		हाल 0x15:
		हाल 0x1d:
			वापस 200000000;
		शेष:
			वापस 320000000;
		पूर्ण
	पूर्ण
	हाल BCM6368_CPU_ID:
	अणु
		अचिन्हित पूर्णांक पंचांगp, p1, p2, nभाग, m1;

		/* (64MHz / P1) * P2 * NDIV / M1_CPU */
		पंचांगp = bcm_ddr_पढ़ोl(DDR_DMIPSPLLCFG_6368_REG);

		p1 = (पंचांगp & DMIPSPLLCFG_6368_P1_MASK) >>
			DMIPSPLLCFG_6368_P1_SHIFT;

		p2 = (पंचांगp & DMIPSPLLCFG_6368_P2_MASK) >>
			DMIPSPLLCFG_6368_P2_SHIFT;

		nभाग = (पंचांगp & DMIPSPLLCFG_6368_NDIV_MASK) >>
			DMIPSPLLCFG_6368_NDIV_SHIFT;

		पंचांगp = bcm_ddr_पढ़ोl(DDR_DMIPSPLLDIV_6368_REG);
		m1 = (पंचांगp & DMIPSPLLDIV_6368_MDIV_MASK) >>
			DMIPSPLLDIV_6368_MDIV_SHIFT;

		वापस (((64 * 1000000) / p1) * p2 * nभाग) / m1;
	पूर्ण

	शेष:
		panic("Failed to detect clock for CPU with id=%04X\n", cpu_id);
	पूर्ण
पूर्ण

/*
 * attempt to detect the amount of memory installed
 */
अटल अचिन्हित पूर्णांक detect_memory_size(व्योम)
अणु
	अचिन्हित पूर्णांक cols = 0, rows = 0, is_32bits = 0, banks = 0;
	u32 val;

	अगर (BCMCPU_IS_6328() || BCMCPU_IS_6362())
		वापस bcm_ddr_पढ़ोl(DDR_CSEND_REG) << 24;

	अगर (BCMCPU_IS_6345()) अणु
		val = bcm_sdram_पढ़ोl(SDRAM_MBASE_REG);
		वापस val * 8 * 1024 * 1024;
	पूर्ण

	अगर (BCMCPU_IS_6338() || BCMCPU_IS_6348()) अणु
		val = bcm_sdram_पढ़ोl(SDRAM_CFG_REG);
		rows = (val & SDRAM_CFG_ROW_MASK) >> SDRAM_CFG_ROW_SHIFT;
		cols = (val & SDRAM_CFG_COL_MASK) >> SDRAM_CFG_COL_SHIFT;
		is_32bits = (val & SDRAM_CFG_32B_MASK) ? 1 : 0;
		banks = (val & SDRAM_CFG_BANK_MASK) ? 2 : 1;
	पूर्ण

	अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358() || BCMCPU_IS_6368()) अणु
		val = bcm_memc_पढ़ोl(MEMC_CFG_REG);
		rows = (val & MEMC_CFG_ROW_MASK) >> MEMC_CFG_ROW_SHIFT;
		cols = (val & MEMC_CFG_COL_MASK) >> MEMC_CFG_COL_SHIFT;
		is_32bits = (val & MEMC_CFG_32B_MASK) ? 0 : 1;
		banks = 2;
	पूर्ण

	/* 0 => 11 address bits ... 2 => 13 address bits */
	rows += 11;

	/* 0 => 8 address bits ... 2 => 10 address bits */
	cols += 8;

	वापस 1 << (cols + rows + (is_32bits + 1) + banks);
पूर्ण

व्योम __init bcm63xx_cpu_init(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u32 chipid_reg;

	/* soc रेजिस्टरs location depends on cpu type */
	chipid_reg = 0;

	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS3300:
		अगर ((पढ़ो_c0_prid() & PRID_IMP_MASK) != PRID_IMP_BMIPS3300_ALT)
			__cpu_name[cpu] = "Broadcom BCM6338";
		fallthrough;
	हाल CPU_BMIPS32:
		chipid_reg = BCM_6345_PERF_BASE;
		अवरोध;
	हाल CPU_BMIPS4350:
		चयन ((पढ़ो_c0_prid() & PRID_REV_MASK)) अणु
		हाल 0x04:
			chipid_reg = BCM_3368_PERF_BASE;
			अवरोध;
		हाल 0x10:
			chipid_reg = BCM_6345_PERF_BASE;
			अवरोध;
		शेष:
			chipid_reg = BCM_6368_PERF_BASE;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * really early to panic, but delaying panic would not help since we
	 * will never get any working console
	 */
	अगर (!chipid_reg)
		panic("unsupported Broadcom CPU");

	/* पढ़ो out CPU type */
	पंचांगp = bcm_पढ़ोl(chipid_reg);
	bcm63xx_cpu_id = (पंचांगp & REV_CHIPID_MASK) >> REV_CHIPID_SHIFT;
	bcm63xx_cpu_rev = (पंचांगp & REV_REVID_MASK) >> REV_REVID_SHIFT;

	चयन (bcm63xx_cpu_id) अणु
	हाल BCM3368_CPU_ID:
		bcm63xx_regs_base = bcm3368_regs_base;
		bcm63xx_irqs = bcm3368_irqs;
		अवरोध;
	हाल BCM6328_CPU_ID:
		bcm63xx_regs_base = bcm6328_regs_base;
		bcm63xx_irqs = bcm6328_irqs;
		अवरोध;
	हाल BCM6338_CPU_ID:
		bcm63xx_regs_base = bcm6338_regs_base;
		bcm63xx_irqs = bcm6338_irqs;
		अवरोध;
	हाल BCM6345_CPU_ID:
		bcm63xx_regs_base = bcm6345_regs_base;
		bcm63xx_irqs = bcm6345_irqs;
		अवरोध;
	हाल BCM6348_CPU_ID:
		bcm63xx_regs_base = bcm6348_regs_base;
		bcm63xx_irqs = bcm6348_irqs;
		अवरोध;
	हाल BCM6358_CPU_ID:
		bcm63xx_regs_base = bcm6358_regs_base;
		bcm63xx_irqs = bcm6358_irqs;
		अवरोध;
	हाल BCM6362_CPU_ID:
		bcm63xx_regs_base = bcm6362_regs_base;
		bcm63xx_irqs = bcm6362_irqs;
		अवरोध;
	हाल BCM6368_CPU_ID:
		bcm63xx_regs_base = bcm6368_regs_base;
		bcm63xx_irqs = bcm6368_irqs;
		अवरोध;
	शेष:
		panic("unsupported broadcom CPU %x", bcm63xx_cpu_id);
		अवरोध;
	पूर्ण

	bcm63xx_cpu_freq = detect_cpu_घड़ी();
	bcm63xx_memory_size = detect_memory_size();

	pr_info("Detected Broadcom 0x%04x CPU revision %02x\n",
		bcm63xx_cpu_id, bcm63xx_cpu_rev);
	pr_info("CPU frequency is %u MHz\n",
		bcm63xx_cpu_freq / 1000000);
	pr_info("%uMB of RAM installed\n",
		bcm63xx_memory_size >> 20);
पूर्ण
