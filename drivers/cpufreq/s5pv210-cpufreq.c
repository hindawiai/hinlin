<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * CPU frequency scaling क्रम S5PC110/S5PV210
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regulator/consumer.h>

अटल व्योम __iomem *clk_base;
अटल व्योम __iomem *dmc_base[2];

#घोषणा S5P_CLKREG(x)		(clk_base + (x))

#घोषणा S5P_APLL_LOCK		S5P_CLKREG(0x00)
#घोषणा S5P_APLL_CON		S5P_CLKREG(0x100)
#घोषणा S5P_CLK_SRC0		S5P_CLKREG(0x200)
#घोषणा S5P_CLK_SRC2		S5P_CLKREG(0x208)
#घोषणा S5P_CLK_DIV0		S5P_CLKREG(0x300)
#घोषणा S5P_CLK_DIV2		S5P_CLKREG(0x308)
#घोषणा S5P_CLK_DIV6		S5P_CLKREG(0x318)
#घोषणा S5P_CLKDIV_STAT0	S5P_CLKREG(0x1000)
#घोषणा S5P_CLKDIV_STAT1	S5P_CLKREG(0x1004)
#घोषणा S5P_CLKMUX_STAT0	S5P_CLKREG(0x1100)
#घोषणा S5P_CLKMUX_STAT1	S5P_CLKREG(0x1104)

#घोषणा S5P_ARM_MCS_CON		S5P_CLKREG(0x6100)

/* CLKSRC0 */
#घोषणा S5P_CLKSRC0_MUX200_SHIFT	(16)
#घोषणा S5P_CLKSRC0_MUX200_MASK		(0x1 << S5P_CLKSRC0_MUX200_SHIFT)
#घोषणा S5P_CLKSRC0_MUX166_MASK		(0x1<<20)
#घोषणा S5P_CLKSRC0_MUX133_MASK		(0x1<<24)

/* CLKSRC2 */
#घोषणा S5P_CLKSRC2_G3D_SHIFT           (0)
#घोषणा S5P_CLKSRC2_G3D_MASK            (0x3 << S5P_CLKSRC2_G3D_SHIFT)
#घोषणा S5P_CLKSRC2_MFC_SHIFT           (4)
#घोषणा S5P_CLKSRC2_MFC_MASK            (0x3 << S5P_CLKSRC2_MFC_SHIFT)

/* CLKDIV0 */
#घोषणा S5P_CLKDIV0_APLL_SHIFT		(0)
#घोषणा S5P_CLKDIV0_APLL_MASK		(0x7 << S5P_CLKDIV0_APLL_SHIFT)
#घोषणा S5P_CLKDIV0_A2M_SHIFT		(4)
#घोषणा S5P_CLKDIV0_A2M_MASK		(0x7 << S5P_CLKDIV0_A2M_SHIFT)
#घोषणा S5P_CLKDIV0_HCLK200_SHIFT	(8)
#घोषणा S5P_CLKDIV0_HCLK200_MASK	(0x7 << S5P_CLKDIV0_HCLK200_SHIFT)
#घोषणा S5P_CLKDIV0_PCLK100_SHIFT	(12)
#घोषणा S5P_CLKDIV0_PCLK100_MASK	(0x7 << S5P_CLKDIV0_PCLK100_SHIFT)
#घोषणा S5P_CLKDIV0_HCLK166_SHIFT	(16)
#घोषणा S5P_CLKDIV0_HCLK166_MASK	(0xF << S5P_CLKDIV0_HCLK166_SHIFT)
#घोषणा S5P_CLKDIV0_PCLK83_SHIFT	(20)
#घोषणा S5P_CLKDIV0_PCLK83_MASK		(0x7 << S5P_CLKDIV0_PCLK83_SHIFT)
#घोषणा S5P_CLKDIV0_HCLK133_SHIFT	(24)
#घोषणा S5P_CLKDIV0_HCLK133_MASK	(0xF << S5P_CLKDIV0_HCLK133_SHIFT)
#घोषणा S5P_CLKDIV0_PCLK66_SHIFT	(28)
#घोषणा S5P_CLKDIV0_PCLK66_MASK		(0x7 << S5P_CLKDIV0_PCLK66_SHIFT)

/* CLKDIV2 */
#घोषणा S5P_CLKDIV2_G3D_SHIFT           (0)
#घोषणा S5P_CLKDIV2_G3D_MASK            (0xF << S5P_CLKDIV2_G3D_SHIFT)
#घोषणा S5P_CLKDIV2_MFC_SHIFT           (4)
#घोषणा S5P_CLKDIV2_MFC_MASK            (0xF << S5P_CLKDIV2_MFC_SHIFT)

/* CLKDIV6 */
#घोषणा S5P_CLKDIV6_ONEDRAM_SHIFT       (28)
#घोषणा S5P_CLKDIV6_ONEDRAM_MASK        (0xF << S5P_CLKDIV6_ONEDRAM_SHIFT)

अटल काष्ठा clk *dmc0_clk;
अटल काष्ठा clk *dmc1_clk;
अटल DEFINE_MUTEX(set_freq_lock);

/* APLL M,P,S values क्रम 1G/800Mhz */
#घोषणा APLL_VAL_1000	((1 << 31) | (125 << 16) | (3 << 8) | 1)
#घोषणा APLL_VAL_800	((1 << 31) | (100 << 16) | (3 << 8) | 1)

/* Use 800MHz when entering sleep mode */
#घोषणा SLEEP_FREQ	(800 * 1000)

/* Tracks अगर CPU frequency can be updated anymore */
अटल bool no_cpufreq_access;

/*
 * DRAM configurations to calculate refresh counter क्रम changing
 * frequency of memory.
 */
काष्ठा dram_conf अणु
	अचिन्हित दीर्घ freq;	/* HZ */
	अचिन्हित दीर्घ refresh;	/* DRAM refresh counter * 1000 */
पूर्ण;

/* DRAM configuration (DMC0 and DMC1) */
अटल काष्ठा dram_conf s5pv210_dram_conf[2];

क्रमागत perf_level अणु
	L0, L1, L2, L3, L4,
पूर्ण;

क्रमागत s5pv210_mem_type अणु
	LPDDR	= 0x1,
	LPDDR2	= 0x2,
	DDR2	= 0x4,
पूर्ण;

क्रमागत s5pv210_dmc_port अणु
	DMC0 = 0,
	DMC1,
पूर्ण;

अटल काष्ठा cpufreq_frequency_table s5pv210_freq_table[] = अणु
	अणु0, L0, 1000*1000पूर्ण,
	अणु0, L1, 800*1000पूर्ण,
	अणु0, L2, 400*1000पूर्ण,
	अणु0, L3, 200*1000पूर्ण,
	अणु0, L4, 100*1000पूर्ण,
	अणु0, 0, CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

अटल काष्ठा regulator *arm_regulator;
अटल काष्ठा regulator *पूर्णांक_regulator;

काष्ठा s5pv210_dvs_conf अणु
	पूर्णांक arm_volt;	/* uV */
	पूर्णांक पूर्णांक_volt;	/* uV */
पूर्ण;

अटल स्थिर पूर्णांक arm_volt_max = 1350000;
अटल स्थिर पूर्णांक पूर्णांक_volt_max = 1250000;

अटल काष्ठा s5pv210_dvs_conf dvs_conf[] = अणु
	[L0] = अणु
		.arm_volt	= 1250000,
		.पूर्णांक_volt	= 1100000,
	पूर्ण,
	[L1] = अणु
		.arm_volt	= 1200000,
		.पूर्णांक_volt	= 1100000,
	पूर्ण,
	[L2] = अणु
		.arm_volt	= 1050000,
		.पूर्णांक_volt	= 1100000,
	पूर्ण,
	[L3] = अणु
		.arm_volt	= 950000,
		.पूर्णांक_volt	= 1100000,
	पूर्ण,
	[L4] = अणु
		.arm_volt	= 950000,
		.पूर्णांक_volt	= 1000000,
	पूर्ण,
पूर्ण;

अटल u32 clkभाग_val[5][11] = अणु
	/*
	 * Clock भागider value क्रम following
	 * अणु APLL, A2M, HCLK_MSYS, PCLK_MSYS,
	 *   HCLK_DSYS, PCLK_DSYS, HCLK_PSYS, PCLK_PSYS,
	 *   ONEDRAM, MFC, G3D पूर्ण
	 */

	/* L0 : [1000/200/100][166/83][133/66][200/200] */
	अणु0, 4, 4, 1, 3, 1, 4, 1, 3, 0, 0पूर्ण,

	/* L1 : [800/200/100][166/83][133/66][200/200] */
	अणु0, 3, 3, 1, 3, 1, 4, 1, 3, 0, 0पूर्ण,

	/* L2 : [400/200/100][166/83][133/66][200/200] */
	अणु1, 3, 1, 1, 3, 1, 4, 1, 3, 0, 0पूर्ण,

	/* L3 : [200/200/100][166/83][133/66][200/200] */
	अणु3, 3, 1, 1, 3, 1, 4, 1, 3, 0, 0पूर्ण,

	/* L4 : [100/100/100][83/83][66/66][100/100] */
	अणु7, 7, 0, 0, 7, 0, 9, 0, 7, 0, 0पूर्ण,
पूर्ण;

/*
 * This function set DRAM refresh counter
 * according to operating frequency of DRAM
 * ch: DMC port number 0 or 1
 * freq: Operating frequency of DRAM(KHz)
 */
अटल व्योम s5pv210_set_refresh(क्रमागत s5pv210_dmc_port ch, अचिन्हित दीर्घ freq)
अणु
	अचिन्हित दीर्घ पंचांगp, पंचांगp1;
	व्योम __iomem *reg = शून्य;

	अगर (ch == DMC0) अणु
		reg = (dmc_base[0] + 0x30);
	पूर्ण अन्यथा अगर (ch == DMC1) अणु
		reg = (dmc_base[1] + 0x30);
	पूर्ण अन्यथा अणु
		pr_err("Cannot find DMC port\n");
		वापस;
	पूर्ण

	/* Find current DRAM frequency */
	पंचांगp = s5pv210_dram_conf[ch].freq;

	पंचांगp /= freq;

	पंचांगp1 = s5pv210_dram_conf[ch].refresh;

	पंचांगp1 /= पंचांगp;

	ग_लिखोl_relaxed(पंचांगp1, reg);
पूर्ण

अटल पूर्णांक s5pv210_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित दीर्घ reg;
	अचिन्हित पूर्णांक priv_index;
	अचिन्हित पूर्णांक pll_changing = 0;
	अचिन्हित पूर्णांक bus_speed_changing = 0;
	अचिन्हित पूर्णांक old_freq, new_freq;
	पूर्णांक arm_volt, पूर्णांक_volt;
	पूर्णांक ret = 0;

	mutex_lock(&set_freq_lock);

	अगर (no_cpufreq_access) अणु
		pr_err("Denied access to %s as it is disabled temporarily\n",
		       __func__);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	old_freq = policy->cur;
	new_freq = s5pv210_freq_table[index].frequency;

	/* Finding current running level index */
	priv_index = cpufreq_table_find_index_h(policy, old_freq);

	arm_volt = dvs_conf[index].arm_volt;
	पूर्णांक_volt = dvs_conf[index].पूर्णांक_volt;

	अगर (new_freq > old_freq) अणु
		ret = regulator_set_voltage(arm_regulator,
				arm_volt, arm_volt_max);
		अगर (ret)
			जाओ निकास;

		ret = regulator_set_voltage(पूर्णांक_regulator,
				पूर्णांक_volt, पूर्णांक_volt_max);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	/* Check अगर there need to change PLL */
	अगर ((index == L0) || (priv_index == L0))
		pll_changing = 1;

	/* Check अगर there need to change System bus घड़ी */
	अगर ((index == L4) || (priv_index == L4))
		bus_speed_changing = 1;

	अगर (bus_speed_changing) अणु
		/*
		 * Reconfigure DRAM refresh counter value क्रम minimum
		 * temporary घड़ी जबतक changing भागider.
		 * expected घड़ी is 83Mhz : 7.8usec/(1/83Mhz) = 0x287
		 */
		अगर (pll_changing)
			s5pv210_set_refresh(DMC1, 83000);
		अन्यथा
			s5pv210_set_refresh(DMC1, 100000);

		s5pv210_set_refresh(DMC0, 83000);
	पूर्ण

	/*
	 * APLL should be changed in this level
	 * APLL -> MPLL(क्रम stable transition) -> APLL
	 * Some घड़ी source's घड़ी API are not prepared.
	 * Do not use घड़ी API in below code.
	 */
	अगर (pll_changing) अणु
		/*
		 * 1. Temporary Change भागider क्रम MFC and G3D
		 * SCLKA2M(200/1=200)->(200/4=50)Mhz
		 */
		reg = पढ़ोl_relaxed(S5P_CLK_DIV2);
		reg &= ~(S5P_CLKDIV2_G3D_MASK | S5P_CLKDIV2_MFC_MASK);
		reg |= (3 << S5P_CLKDIV2_G3D_SHIFT) |
			(3 << S5P_CLKDIV2_MFC_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_DIV2);

		/* For MFC, G3D भागiding */
		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKDIV_STAT0);
		पूर्ण जबतक (reg & ((1 << 16) | (1 << 17)));

		/*
		 * 2. Change SCLKA2M(200Mhz)to SCLKMPLL in MFC_MUX, G3D MUX
		 * (200/4=50)->(667/4=166)Mhz
		 */
		reg = पढ़ोl_relaxed(S5P_CLK_SRC2);
		reg &= ~(S5P_CLKSRC2_G3D_MASK | S5P_CLKSRC2_MFC_MASK);
		reg |= (1 << S5P_CLKSRC2_G3D_SHIFT) |
			(1 << S5P_CLKSRC2_MFC_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_SRC2);

		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKMUX_STAT1);
		पूर्ण जबतक (reg & ((1 << 7) | (1 << 3)));

		/*
		 * 3. DMC1 refresh count क्रम 133Mhz अगर (index == L4) is
		 * true refresh counter is alपढ़ोy programmed in upper
		 * code. 0x287@83Mhz
		 */
		अगर (!bus_speed_changing)
			s5pv210_set_refresh(DMC1, 133000);

		/* 4. SCLKAPLL -> SCLKMPLL */
		reg = पढ़ोl_relaxed(S5P_CLK_SRC0);
		reg &= ~(S5P_CLKSRC0_MUX200_MASK);
		reg |= (0x1 << S5P_CLKSRC0_MUX200_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_SRC0);

		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKMUX_STAT0);
		पूर्ण जबतक (reg & (0x1 << 18));

	पूर्ण

	/* Change भागider */
	reg = पढ़ोl_relaxed(S5P_CLK_DIV0);

	reg &= ~(S5P_CLKDIV0_APLL_MASK | S5P_CLKDIV0_A2M_MASK |
		S5P_CLKDIV0_HCLK200_MASK | S5P_CLKDIV0_PCLK100_MASK |
		S5P_CLKDIV0_HCLK166_MASK | S5P_CLKDIV0_PCLK83_MASK |
		S5P_CLKDIV0_HCLK133_MASK | S5P_CLKDIV0_PCLK66_MASK);

	reg |= ((clkभाग_val[index][0] << S5P_CLKDIV0_APLL_SHIFT) |
		(clkभाग_val[index][1] << S5P_CLKDIV0_A2M_SHIFT) |
		(clkभाग_val[index][2] << S5P_CLKDIV0_HCLK200_SHIFT) |
		(clkभाग_val[index][3] << S5P_CLKDIV0_PCLK100_SHIFT) |
		(clkभाग_val[index][4] << S5P_CLKDIV0_HCLK166_SHIFT) |
		(clkभाग_val[index][5] << S5P_CLKDIV0_PCLK83_SHIFT) |
		(clkभाग_val[index][6] << S5P_CLKDIV0_HCLK133_SHIFT) |
		(clkभाग_val[index][7] << S5P_CLKDIV0_PCLK66_SHIFT));

	ग_लिखोl_relaxed(reg, S5P_CLK_DIV0);

	करो अणु
		reg = पढ़ोl_relaxed(S5P_CLKDIV_STAT0);
	पूर्ण जबतक (reg & 0xff);

	/* ARM MCS value changed */
	reg = पढ़ोl_relaxed(S5P_ARM_MCS_CON);
	reg &= ~0x3;
	अगर (index >= L3)
		reg |= 0x3;
	अन्यथा
		reg |= 0x1;

	ग_लिखोl_relaxed(reg, S5P_ARM_MCS_CON);

	अगर (pll_changing) अणु
		/* 5. Set Lock समय = 30us*24Mhz = 0x2cf */
		ग_लिखोl_relaxed(0x2cf, S5P_APLL_LOCK);

		/*
		 * 6. Turn on APLL
		 * 6-1. Set PMS values
		 * 6-2. Wait until the PLL is locked
		 */
		अगर (index == L0)
			ग_लिखोl_relaxed(APLL_VAL_1000, S5P_APLL_CON);
		अन्यथा
			ग_लिखोl_relaxed(APLL_VAL_800, S5P_APLL_CON);

		करो अणु
			reg = पढ़ोl_relaxed(S5P_APLL_CON);
		पूर्ण जबतक (!(reg & (0x1 << 29)));

		/*
		 * 7. Change source घड़ी from SCLKMPLL(667Mhz)
		 * to SCLKA2M(200Mhz) in MFC_MUX and G3D MUX
		 * (667/4=166)->(200/4=50)Mhz
		 */
		reg = पढ़ोl_relaxed(S5P_CLK_SRC2);
		reg &= ~(S5P_CLKSRC2_G3D_MASK | S5P_CLKSRC2_MFC_MASK);
		reg |= (0 << S5P_CLKSRC2_G3D_SHIFT) |
			(0 << S5P_CLKSRC2_MFC_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_SRC2);

		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKMUX_STAT1);
		पूर्ण जबतक (reg & ((1 << 7) | (1 << 3)));

		/*
		 * 8. Change भागider क्रम MFC and G3D
		 * (200/4=50)->(200/1=200)Mhz
		 */
		reg = पढ़ोl_relaxed(S5P_CLK_DIV2);
		reg &= ~(S5P_CLKDIV2_G3D_MASK | S5P_CLKDIV2_MFC_MASK);
		reg |= (clkभाग_val[index][10] << S5P_CLKDIV2_G3D_SHIFT) |
			(clkभाग_val[index][9] << S5P_CLKDIV2_MFC_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_DIV2);

		/* For MFC, G3D भागiding */
		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKDIV_STAT0);
		पूर्ण जबतक (reg & ((1 << 16) | (1 << 17)));

		/* 9. Change MPLL to APLL in MSYS_MUX */
		reg = पढ़ोl_relaxed(S5P_CLK_SRC0);
		reg &= ~(S5P_CLKSRC0_MUX200_MASK);
		reg |= (0x0 << S5P_CLKSRC0_MUX200_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_SRC0);

		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKMUX_STAT0);
		पूर्ण जबतक (reg & (0x1 << 18));

		/*
		 * 10. DMC1 refresh counter
		 * L4 : DMC1 = 100Mhz 7.8us/(1/100) = 0x30c
		 * Others : DMC1 = 200Mhz 7.8us/(1/200) = 0x618
		 */
		अगर (!bus_speed_changing)
			s5pv210_set_refresh(DMC1, 200000);
	पूर्ण

	/*
	 * L4 level needs to change memory bus speed, hence ONEDRAM घड़ी
	 * भागider and memory refresh parameter should be changed
	 */
	अगर (bus_speed_changing) अणु
		reg = पढ़ोl_relaxed(S5P_CLK_DIV6);
		reg &= ~S5P_CLKDIV6_ONEDRAM_MASK;
		reg |= (clkभाग_val[index][8] << S5P_CLKDIV6_ONEDRAM_SHIFT);
		ग_लिखोl_relaxed(reg, S5P_CLK_DIV6);

		करो अणु
			reg = पढ़ोl_relaxed(S5P_CLKDIV_STAT1);
		पूर्ण जबतक (reg & (1 << 15));

		/* Reconfigure DRAM refresh counter value */
		अगर (index != L4) अणु
			/*
			 * DMC0 : 166Mhz
			 * DMC1 : 200Mhz
			 */
			s5pv210_set_refresh(DMC0, 166000);
			s5pv210_set_refresh(DMC1, 200000);
		पूर्ण अन्यथा अणु
			/*
			 * DMC0 : 83Mhz
			 * DMC1 : 100Mhz
			 */
			s5pv210_set_refresh(DMC0, 83000);
			s5pv210_set_refresh(DMC1, 100000);
		पूर्ण
	पूर्ण

	अगर (new_freq < old_freq) अणु
		regulator_set_voltage(पूर्णांक_regulator,
				पूर्णांक_volt, पूर्णांक_volt_max);

		regulator_set_voltage(arm_regulator,
				arm_volt, arm_volt_max);
	पूर्ण

	pr_debug("Perf changed[L%d]\n", index);

निकास:
	mutex_unlock(&set_freq_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक check_mem_type(व्योम __iomem *dmc_reg)
अणु
	अचिन्हित दीर्घ val;

	val = पढ़ोl_relaxed(dmc_reg + 0x4);
	val = (val & (0xf << 8));

	वापस val >> 8;
पूर्ण

अटल पूर्णांक s5pv210_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित दीर्घ mem_type;
	पूर्णांक ret;

	policy->clk = clk_get(शून्य, "armclk");
	अगर (IS_ERR(policy->clk))
		वापस PTR_ERR(policy->clk);

	dmc0_clk = clk_get(शून्य, "sclk_dmc0");
	अगर (IS_ERR(dmc0_clk)) अणु
		ret = PTR_ERR(dmc0_clk);
		जाओ out_dmc0;
	पूर्ण

	dmc1_clk = clk_get(शून्य, "hclk_msys");
	अगर (IS_ERR(dmc1_clk)) अणु
		ret = PTR_ERR(dmc1_clk);
		जाओ out_dmc1;
	पूर्ण

	अगर (policy->cpu != 0) अणु
		ret = -EINVAL;
		जाओ out_dmc1;
	पूर्ण

	/*
	 * check_mem_type : This driver only support LPDDR & LPDDR2.
	 * other memory type is not supported.
	 */
	mem_type = check_mem_type(dmc_base[0]);

	अगर ((mem_type != LPDDR) && (mem_type != LPDDR2)) अणु
		pr_err("CPUFreq doesn't support this memory type\n");
		ret = -EINVAL;
		जाओ out_dmc1;
	पूर्ण

	/* Find current refresh counter and frequency each DMC */
	s5pv210_dram_conf[0].refresh = (पढ़ोl_relaxed(dmc_base[0] + 0x30) * 1000);
	s5pv210_dram_conf[0].freq = clk_get_rate(dmc0_clk);

	s5pv210_dram_conf[1].refresh = (पढ़ोl_relaxed(dmc_base[1] + 0x30) * 1000);
	s5pv210_dram_conf[1].freq = clk_get_rate(dmc1_clk);

	policy->suspend_freq = SLEEP_FREQ;
	cpufreq_generic_init(policy, s5pv210_freq_table, 40000);
	वापस 0;

out_dmc1:
	clk_put(dmc0_clk);
out_dmc0:
	clk_put(policy->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक s5pv210_cpufreq_reboot_notअगरier_event(काष्ठा notअगरier_block *this,
						 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	पूर्णांक ret;
	काष्ठा cpufreq_policy *policy;

	policy = cpufreq_cpu_get(0);
	अगर (!policy) अणु
		pr_debug("cpufreq: get no policy for cpu0\n");
		वापस NOTIFY_BAD;
	पूर्ण

	ret = cpufreq_driver_target(policy, SLEEP_FREQ, 0);
	cpufreq_cpu_put(policy);

	अगर (ret < 0)
		वापस NOTIFY_BAD;

	no_cpufreq_access = true;
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा cpufreq_driver s5pv210_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= s5pv210_target,
	.get		= cpufreq_generic_get,
	.init		= s5pv210_cpu_init,
	.name		= "s5pv210",
	.suspend	= cpufreq_generic_suspend,
	.resume		= cpufreq_generic_suspend, /* We need to set SLEEP FREQ again */
पूर्ण;

अटल काष्ठा notअगरier_block s5pv210_cpufreq_reboot_notअगरier = अणु
	.notअगरier_call = s5pv210_cpufreq_reboot_notअगरier_event,
पूर्ण;

अटल पूर्णांक s5pv210_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np;
	पूर्णांक id, result = 0;

	/*
	 * HACK: This is a temporary workaround to get access to घड़ी
	 * and DMC controller रेजिस्टरs directly and हटाओ अटल mappings
	 * and dependencies on platक्रमm headers. It is necessary to enable
	 * S5PV210 multi-platक्रमm support and will be हटाओd together with
	 * this whole driver as soon as S5PV210 माला_लो migrated to use
	 * cpufreq-dt driver.
	 */
	arm_regulator = regulator_get(शून्य, "vddarm");
	अगर (IS_ERR(arm_regulator))
		वापस dev_err_probe(dev, PTR_ERR(arm_regulator),
				     "failed to get regulator vddarm\n");

	पूर्णांक_regulator = regulator_get(शून्य, "vddint");
	अगर (IS_ERR(पूर्णांक_regulator)) अणु
		result = dev_err_probe(dev, PTR_ERR(पूर्णांक_regulator),
				       "failed to get regulator vddint\n");
		जाओ err_पूर्णांक_regulator;
	पूर्ण

	np = of_find_compatible_node(शून्य, शून्य, "samsung,s5pv210-clock");
	अगर (!np) अणु
		dev_err(dev, "failed to find clock controller DT node\n");
		result = -ENODEV;
		जाओ err_घड़ी;
	पूर्ण

	clk_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!clk_base) अणु
		dev_err(dev, "failed to map clock registers\n");
		result = -EFAULT;
		जाओ err_घड़ी;
	पूर्ण

	क्रम_each_compatible_node(np, शून्य, "samsung,s5pv210-dmc") अणु
		id = of_alias_get_id(np, "dmc");
		अगर (id < 0 || id >= ARRAY_SIZE(dmc_base)) अणु
			dev_err(dev, "failed to get alias of dmc node '%pOFn'\n", np);
			of_node_put(np);
			result = id;
			जाओ err_clk_base;
		पूर्ण

		dmc_base[id] = of_iomap(np, 0);
		अगर (!dmc_base[id]) अणु
			dev_err(dev, "failed to map dmc%d registers\n", id);
			of_node_put(np);
			result = -EFAULT;
			जाओ err_dmc;
		पूर्ण
	पूर्ण

	क्रम (id = 0; id < ARRAY_SIZE(dmc_base); ++id) अणु
		अगर (!dmc_base[id]) अणु
			dev_err(dev, "failed to find dmc%d node\n", id);
			result = -ENODEV;
			जाओ err_dmc;
		पूर्ण
	पूर्ण

	रेजिस्टर_reboot_notअगरier(&s5pv210_cpufreq_reboot_notअगरier);

	वापस cpufreq_रेजिस्टर_driver(&s5pv210_driver);

err_dmc:
	क्रम (id = 0; id < ARRAY_SIZE(dmc_base); ++id)
		अगर (dmc_base[id]) अणु
			iounmap(dmc_base[id]);
			dmc_base[id] = शून्य;
		पूर्ण

err_clk_base:
	iounmap(clk_base);

err_घड़ी:
	regulator_put(पूर्णांक_regulator);

err_पूर्णांक_regulator:
	regulator_put(arm_regulator);

	वापस result;
पूर्ण

अटल काष्ठा platक्रमm_driver s5pv210_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "s5pv210-cpufreq",
	पूर्ण,
	.probe = s5pv210_cpufreq_probe,
पूर्ण;
builtin_platक्रमm_driver(s5pv210_cpufreq_platdrv);
