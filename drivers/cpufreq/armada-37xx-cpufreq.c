<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CPU frequency scaling support क्रम Armada 37xx platक्रमm.
 *
 * Copyright (C) 2017 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "cpufreq-dt.h"

/* Clk रेजिस्टर set */
#घोषणा ARMADA_37XX_CLK_TBG_SEL		0
#घोषणा ARMADA_37XX_CLK_TBG_SEL_CPU_OFF	22

/* Power management in North Bridge रेजिस्टर set */
#घोषणा ARMADA_37XX_NB_L0L1	0x18
#घोषणा ARMADA_37XX_NB_L2L3	0x1C
#घोषणा  ARMADA_37XX_NB_TBG_DIV_OFF	13
#घोषणा  ARMADA_37XX_NB_TBG_DIV_MASK	0x7
#घोषणा  ARMADA_37XX_NB_CLK_SEL_OFF	11
#घोषणा  ARMADA_37XX_NB_CLK_SEL_MASK	0x1
#घोषणा  ARMADA_37XX_NB_CLK_SEL_TBG	0x1
#घोषणा  ARMADA_37XX_NB_TBG_SEL_OFF	9
#घोषणा  ARMADA_37XX_NB_TBG_SEL_MASK	0x3
#घोषणा  ARMADA_37XX_NB_VDD_SEL_OFF	6
#घोषणा  ARMADA_37XX_NB_VDD_SEL_MASK	0x3
#घोषणा  ARMADA_37XX_NB_CONFIG_SHIFT	16
#घोषणा ARMADA_37XX_NB_DYN_MOD	0x24
#घोषणा  ARMADA_37XX_NB_CLK_SEL_EN	BIT(26)
#घोषणा  ARMADA_37XX_NB_TBG_EN		BIT(28)
#घोषणा  ARMADA_37XX_NB_DIV_EN		BIT(29)
#घोषणा  ARMADA_37XX_NB_VDD_EN		BIT(30)
#घोषणा  ARMADA_37XX_NB_DFS_EN		BIT(31)
#घोषणा ARMADA_37XX_NB_CPU_LOAD 0x30
#घोषणा  ARMADA_37XX_NB_CPU_LOAD_MASK	0x3
#घोषणा  ARMADA_37XX_DVFS_LOAD_0	0
#घोषणा  ARMADA_37XX_DVFS_LOAD_1	1
#घोषणा  ARMADA_37XX_DVFS_LOAD_2	2
#घोषणा  ARMADA_37XX_DVFS_LOAD_3	3

/* AVS रेजिस्टर set */
#घोषणा ARMADA_37XX_AVS_CTL0		0x0
#घोषणा	 ARMADA_37XX_AVS_ENABLE		BIT(30)
#घोषणा	 ARMADA_37XX_AVS_HIGH_VDD_LIMIT	16
#घोषणा	 ARMADA_37XX_AVS_LOW_VDD_LIMIT	22
#घोषणा	 ARMADA_37XX_AVS_VDD_MASK	0x3F
#घोषणा ARMADA_37XX_AVS_CTL2		0x8
#घोषणा	 ARMADA_37XX_AVS_LOW_VDD_EN	BIT(6)
#घोषणा ARMADA_37XX_AVS_VSET(x)	    (0x1C + 4 * (x))

/*
 * On Armada 37xx the Power management manages 4 level of CPU load,
 * each level can be associated with a CPU घड़ी source, a CPU
 * भागider, a VDD level, etc...
 */
#घोषणा LOAD_LEVEL_NR	4

#घोषणा MIN_VOLT_MV 1000
#घोषणा MIN_VOLT_MV_FOR_L1_1000MHZ 1108
#घोषणा MIN_VOLT_MV_FOR_L1_1200MHZ 1155

/*  AVS value क्रम the corresponding voltage (in mV) */
अटल पूर्णांक avs_map[] = अणु
	747, 758, 770, 782, 793, 805, 817, 828, 840, 852, 863, 875, 887, 898,
	910, 922, 933, 945, 957, 968, 980, 992, 1003, 1015, 1027, 1038, 1050,
	1062, 1073, 1085, 1097, 1108, 1120, 1132, 1143, 1155, 1167, 1178, 1190,
	1202, 1213, 1225, 1237, 1248, 1260, 1272, 1283, 1295, 1307, 1318, 1330,
	1342
पूर्ण;

काष्ठा armada37xx_cpufreq_state अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *cpu_dev;
	काष्ठा regmap *regmap;
	u32 nb_l0l1;
	u32 nb_l2l3;
	u32 nb_dyn_mod;
	u32 nb_cpu_load;
पूर्ण;

अटल काष्ठा armada37xx_cpufreq_state *armada37xx_cpufreq_state;

काष्ठा armada_37xx_dvfs अणु
	u32 cpu_freq_max;
	u8 भागider[LOAD_LEVEL_NR];
	u32 avs[LOAD_LEVEL_NR];
पूर्ण;

अटल काष्ठा armada_37xx_dvfs armada_37xx_dvfs[] = अणु
	अणु.cpu_freq_max = 1200*1000*1000, .भागider = अणु1, 2, 4, 6पूर्ण पूर्ण,
	अणु.cpu_freq_max = 1000*1000*1000, .भागider = अणु1, 2, 4, 5पूर्ण पूर्ण,
	अणु.cpu_freq_max = 800*1000*1000,  .भागider = अणु1, 2, 3, 4पूर्ण पूर्ण,
	अणु.cpu_freq_max = 600*1000*1000,  .भागider = अणु2, 4, 5, 6पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा armada_37xx_dvfs *armada_37xx_cpu_freq_info_get(u32 freq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(armada_37xx_dvfs); i++) अणु
		अगर (freq == armada_37xx_dvfs[i].cpu_freq_max)
			वापस &armada_37xx_dvfs[i];
	पूर्ण

	pr_err("Unsupported CPU frequency %d MHz\n", freq/1000000);
	वापस शून्य;
पूर्ण

/*
 * Setup the four level managed by the hardware. Once the four level
 * will be configured then the DVFS will be enabled.
 */
अटल व्योम __init armada37xx_cpufreq_dvfs_setup(काष्ठा regmap *base,
						 काष्ठा regmap *clk_base, u8 *भागider)
अणु
	u32 cpu_tbg_sel;
	पूर्णांक load_lvl;

	/* Determine to which TBG घड़ी is CPU connected */
	regmap_पढ़ो(clk_base, ARMADA_37XX_CLK_TBG_SEL, &cpu_tbg_sel);
	cpu_tbg_sel >>= ARMADA_37XX_CLK_TBG_SEL_CPU_OFF;
	cpu_tbg_sel &= ARMADA_37XX_NB_TBG_SEL_MASK;

	क्रम (load_lvl = 0; load_lvl < LOAD_LEVEL_NR; load_lvl++) अणु
		अचिन्हित पूर्णांक reg, mask, val, offset = 0;

		अगर (load_lvl <= ARMADA_37XX_DVFS_LOAD_1)
			reg = ARMADA_37XX_NB_L0L1;
		अन्यथा
			reg = ARMADA_37XX_NB_L2L3;

		अगर (load_lvl == ARMADA_37XX_DVFS_LOAD_0 ||
		    load_lvl == ARMADA_37XX_DVFS_LOAD_2)
			offset += ARMADA_37XX_NB_CONFIG_SHIFT;

		/* Set cpu घड़ी source, क्रम all the level we use TBG */
		val = ARMADA_37XX_NB_CLK_SEL_TBG << ARMADA_37XX_NB_CLK_SEL_OFF;
		mask = (ARMADA_37XX_NB_CLK_SEL_MASK
			<< ARMADA_37XX_NB_CLK_SEL_OFF);

		/* Set TBG index, क्रम all levels we use the same TBG */
		val = cpu_tbg_sel << ARMADA_37XX_NB_TBG_SEL_OFF;
		mask = (ARMADA_37XX_NB_TBG_SEL_MASK
			<< ARMADA_37XX_NB_TBG_SEL_OFF);

		/*
		 * Set cpu भागider based on the pre-computed array in
		 * order to have balanced step.
		 */
		val |= भागider[load_lvl] << ARMADA_37XX_NB_TBG_DIV_OFF;
		mask |= (ARMADA_37XX_NB_TBG_DIV_MASK
			<< ARMADA_37XX_NB_TBG_DIV_OFF);

		/* Set VDD भागider which is actually the load level. */
		val |= load_lvl << ARMADA_37XX_NB_VDD_SEL_OFF;
		mask |= (ARMADA_37XX_NB_VDD_SEL_MASK
			<< ARMADA_37XX_NB_VDD_SEL_OFF);

		val <<= offset;
		mask <<= offset;

		regmap_update_bits(base, reg, mask, val);
	पूर्ण
पूर्ण

/*
 * Find out the armada 37x supported AVS value whose voltage value is
 * the round-up बंदst to the target voltage value.
 */
अटल u32 armada_37xx_avs_val_match(पूर्णांक target_vm)
अणु
	u32 avs;

	/* Find out the round-up बंदst supported voltage value */
	क्रम (avs = 0; avs < ARRAY_SIZE(avs_map); avs++)
		अगर (avs_map[avs] >= target_vm)
			अवरोध;

	/*
	 * If all supported voltages are smaller than target one,
	 * choose the largest supported voltage
	 */
	अगर (avs == ARRAY_SIZE(avs_map))
		avs = ARRAY_SIZE(avs_map) - 1;

	वापस avs;
पूर्ण

/*
 * For Armada 37xx soc, L0(VSET0) VDD AVS value is set to SVC revision
 * value or a शेष value when SVC is not supported.
 * - L0 can be पढ़ो out from the रेजिस्टर of AVS_CTRL_0 and L0 voltage
 *   can be got from the mapping table of avs_map.
 * - L1 voltage should be about 100mv smaller than L0 voltage
 * - L2 & L3 voltage should be about 150mv smaller than L0 voltage.
 * This function calculates L1 & L2 & L3 AVS values dynamically based
 * on L0 voltage and fill all AVS values to the AVS value table.
 * When base CPU frequency is 1000 or 1200 MHz then there is additional
 * minimal avs value क्रम load L1.
 */
अटल व्योम __init armada37xx_cpufreq_avs_configure(काष्ठा regmap *base,
						काष्ठा armada_37xx_dvfs *dvfs)
अणु
	अचिन्हित पूर्णांक target_vm;
	पूर्णांक load_level = 0;
	u32 l0_vdd_min;

	अगर (base == शून्य)
		वापस;

	/* Get L0 VDD min value */
	regmap_पढ़ो(base, ARMADA_37XX_AVS_CTL0, &l0_vdd_min);
	l0_vdd_min = (l0_vdd_min >> ARMADA_37XX_AVS_LOW_VDD_LIMIT) &
		ARMADA_37XX_AVS_VDD_MASK;
	अगर (l0_vdd_min >= ARRAY_SIZE(avs_map))  अणु
		pr_err("L0 VDD MIN %d is not correct.\n", l0_vdd_min);
		वापस;
	पूर्ण
	dvfs->avs[0] = l0_vdd_min;

	अगर (avs_map[l0_vdd_min] <= MIN_VOLT_MV) अणु
		/*
		 * If L0 voltage is smaller than 1000mv, then all VDD sets
		 * use L0 voltage;
		 */
		u32 avs_min = armada_37xx_avs_val_match(MIN_VOLT_MV);

		क्रम (load_level = 1; load_level < LOAD_LEVEL_NR; load_level++)
			dvfs->avs[load_level] = avs_min;

		/*
		 * Set the avs values क्रम load L0 and L1 when base CPU frequency
		 * is 1000/1200 MHz to its typical initial values according to
		 * the Armada 3700 Hardware Specअगरications.
		 */
		अगर (dvfs->cpu_freq_max >= 1000*1000*1000) अणु
			अगर (dvfs->cpu_freq_max >= 1200*1000*1000)
				avs_min = armada_37xx_avs_val_match(MIN_VOLT_MV_FOR_L1_1200MHZ);
			अन्यथा
				avs_min = armada_37xx_avs_val_match(MIN_VOLT_MV_FOR_L1_1000MHZ);
			dvfs->avs[0] = dvfs->avs[1] = avs_min;
		पूर्ण

		वापस;
	पूर्ण

	/*
	 * L1 voltage is equal to L0 voltage - 100mv and it must be
	 * larger than 1000mv
	 */

	target_vm = avs_map[l0_vdd_min] - 100;
	target_vm = target_vm > MIN_VOLT_MV ? target_vm : MIN_VOLT_MV;
	dvfs->avs[1] = armada_37xx_avs_val_match(target_vm);

	/*
	 * L2 & L3 voltage is equal to L0 voltage - 150mv and it must
	 * be larger than 1000mv
	 */
	target_vm = avs_map[l0_vdd_min] - 150;
	target_vm = target_vm > MIN_VOLT_MV ? target_vm : MIN_VOLT_MV;
	dvfs->avs[2] = dvfs->avs[3] = armada_37xx_avs_val_match(target_vm);

	/*
	 * Fix the avs value क्रम load L1 when base CPU frequency is 1000/1200 MHz,
	 * otherwise the CPU माला_लो stuck when चयनing from load L1 to load L0.
	 * Also ensure that avs value क्रम load L1 is not higher than क्रम L0.
	 */
	अगर (dvfs->cpu_freq_max >= 1000*1000*1000) अणु
		u32 avs_min_l1;

		अगर (dvfs->cpu_freq_max >= 1200*1000*1000)
			avs_min_l1 = armada_37xx_avs_val_match(MIN_VOLT_MV_FOR_L1_1200MHZ);
		अन्यथा
			avs_min_l1 = armada_37xx_avs_val_match(MIN_VOLT_MV_FOR_L1_1000MHZ);

		अगर (avs_min_l1 > dvfs->avs[0])
			avs_min_l1 = dvfs->avs[0];

		अगर (dvfs->avs[1] < avs_min_l1)
			dvfs->avs[1] = avs_min_l1;
	पूर्ण
पूर्ण

अटल व्योम __init armada37xx_cpufreq_avs_setup(काष्ठा regmap *base,
						काष्ठा armada_37xx_dvfs *dvfs)
अणु
	अचिन्हित पूर्णांक avs_val = 0;
	पूर्णांक load_level = 0;

	अगर (base == शून्य)
		वापस;

	/* Disable AVS beक्रमe the configuration */
	regmap_update_bits(base, ARMADA_37XX_AVS_CTL0,
			   ARMADA_37XX_AVS_ENABLE, 0);


	/* Enable low voltage mode */
	regmap_update_bits(base, ARMADA_37XX_AVS_CTL2,
			   ARMADA_37XX_AVS_LOW_VDD_EN,
			   ARMADA_37XX_AVS_LOW_VDD_EN);


	क्रम (load_level = 1; load_level < LOAD_LEVEL_NR; load_level++) अणु
		avs_val = dvfs->avs[load_level];
		regmap_update_bits(base, ARMADA_37XX_AVS_VSET(load_level-1),
		    ARMADA_37XX_AVS_VDD_MASK << ARMADA_37XX_AVS_HIGH_VDD_LIMIT |
		    ARMADA_37XX_AVS_VDD_MASK << ARMADA_37XX_AVS_LOW_VDD_LIMIT,
		    avs_val << ARMADA_37XX_AVS_HIGH_VDD_LIMIT |
		    avs_val << ARMADA_37XX_AVS_LOW_VDD_LIMIT);
	पूर्ण

	/* Enable AVS after the configuration */
	regmap_update_bits(base, ARMADA_37XX_AVS_CTL0,
			   ARMADA_37XX_AVS_ENABLE,
			   ARMADA_37XX_AVS_ENABLE);

पूर्ण

अटल व्योम armada37xx_cpufreq_disable_dvfs(काष्ठा regmap *base)
अणु
	अचिन्हित पूर्णांक reg = ARMADA_37XX_NB_DYN_MOD,
		mask = ARMADA_37XX_NB_DFS_EN;

	regmap_update_bits(base, reg, mask, 0);
पूर्ण

अटल व्योम __init armada37xx_cpufreq_enable_dvfs(काष्ठा regmap *base)
अणु
	अचिन्हित पूर्णांक val, reg = ARMADA_37XX_NB_CPU_LOAD,
		mask = ARMADA_37XX_NB_CPU_LOAD_MASK;

	/* Start with the highest load (0) */
	val = ARMADA_37XX_DVFS_LOAD_0;
	regmap_update_bits(base, reg, mask, val);

	/* Now enable DVFS क्रम the CPUs */
	reg = ARMADA_37XX_NB_DYN_MOD;
	mask =	ARMADA_37XX_NB_CLK_SEL_EN | ARMADA_37XX_NB_TBG_EN |
		ARMADA_37XX_NB_DIV_EN | ARMADA_37XX_NB_VDD_EN |
		ARMADA_37XX_NB_DFS_EN;

	regmap_update_bits(base, reg, mask, mask);
पूर्ण

अटल पूर्णांक armada37xx_cpufreq_suspend(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा armada37xx_cpufreq_state *state = armada37xx_cpufreq_state;

	regmap_पढ़ो(state->regmap, ARMADA_37XX_NB_L0L1, &state->nb_l0l1);
	regmap_पढ़ो(state->regmap, ARMADA_37XX_NB_L2L3, &state->nb_l2l3);
	regmap_पढ़ो(state->regmap, ARMADA_37XX_NB_CPU_LOAD,
		    &state->nb_cpu_load);
	regmap_पढ़ो(state->regmap, ARMADA_37XX_NB_DYN_MOD, &state->nb_dyn_mod);

	वापस 0;
पूर्ण

अटल पूर्णांक armada37xx_cpufreq_resume(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा armada37xx_cpufreq_state *state = armada37xx_cpufreq_state;

	/* Ensure DVFS is disabled otherwise the following रेजिस्टरs are RO */
	armada37xx_cpufreq_disable_dvfs(state->regmap);

	regmap_ग_लिखो(state->regmap, ARMADA_37XX_NB_L0L1, state->nb_l0l1);
	regmap_ग_लिखो(state->regmap, ARMADA_37XX_NB_L2L3, state->nb_l2l3);
	regmap_ग_लिखो(state->regmap, ARMADA_37XX_NB_CPU_LOAD,
		     state->nb_cpu_load);

	/*
	 * NB_DYN_MOD रेजिस्टर is the one that actually enable back DVFS अगर it
	 * was enabled beक्रमe the suspend operation. This must be करोne last
	 * otherwise other रेजिस्टरs are not writable.
	 */
	regmap_ग_लिखो(state->regmap, ARMADA_37XX_NB_DYN_MOD, state->nb_dyn_mod);

	वापस 0;
पूर्ण

अटल पूर्णांक __init armada37xx_cpufreq_driver_init(व्योम)
अणु
	काष्ठा cpufreq_dt_platक्रमm_data pdata;
	काष्ठा armada_37xx_dvfs *dvfs;
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित दीर्घ freq;
	अचिन्हित पूर्णांक base_frequency;
	काष्ठा regmap *nb_clk_base, *nb_pm_base, *avs_base;
	काष्ठा device *cpu_dev;
	पूर्णांक load_lvl, ret;
	काष्ठा clk *clk, *parent;

	nb_clk_base =
		syscon_regmap_lookup_by_compatible("marvell,armada-3700-periph-clock-nb");
	अगर (IS_ERR(nb_clk_base))
		वापस -ENODEV;

	nb_pm_base =
		syscon_regmap_lookup_by_compatible("marvell,armada-3700-nb-pm");

	अगर (IS_ERR(nb_pm_base))
		वापस -ENODEV;

	avs_base =
		syscon_regmap_lookup_by_compatible("marvell,armada-3700-avs");

	/* अगर AVS is not present करोn't use it but still try to setup dvfs */
	अगर (IS_ERR(avs_base)) अणु
		pr_info("Syscon failed for Adapting Voltage Scaling: skip it\n");
		avs_base = शून्य;
	पूर्ण
	/* Beक्रमe करोing any configuration on the DVFS first, disable it */
	armada37xx_cpufreq_disable_dvfs(nb_pm_base);

	/*
	 * On CPU 0 रेजिस्टर the operating poपूर्णांकs supported (which are
	 * the nominal CPU frequency and full पूर्णांकeger भागisions of
	 * it).
	 */
	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev) अणु
		dev_err(cpu_dev, "Cannot get CPU\n");
		वापस -ENODEV;
	पूर्ण

	clk = clk_get(cpu_dev, 0);
	अगर (IS_ERR(clk)) अणु
		dev_err(cpu_dev, "Cannot get clock for CPU0\n");
		वापस PTR_ERR(clk);
	पूर्ण

	parent = clk_get_parent(clk);
	अगर (IS_ERR(parent)) अणु
		dev_err(cpu_dev, "Cannot get parent clock for CPU0\n");
		clk_put(clk);
		वापस PTR_ERR(parent);
	पूर्ण

	/* Get parent CPU frequency */
	base_frequency =  clk_get_rate(parent);

	अगर (!base_frequency) अणु
		dev_err(cpu_dev, "Failed to get parent clock rate for CPU\n");
		clk_put(clk);
		वापस -EINVAL;
	पूर्ण

	dvfs = armada_37xx_cpu_freq_info_get(base_frequency);
	अगर (!dvfs) अणु
		clk_put(clk);
		वापस -EINVAL;
	पूर्ण

	armada37xx_cpufreq_state = kदो_स्मृति(माप(*armada37xx_cpufreq_state),
					   GFP_KERNEL);
	अगर (!armada37xx_cpufreq_state) अणु
		clk_put(clk);
		वापस -ENOMEM;
	पूर्ण

	armada37xx_cpufreq_state->regmap = nb_pm_base;

	armada37xx_cpufreq_avs_configure(avs_base, dvfs);
	armada37xx_cpufreq_avs_setup(avs_base, dvfs);

	armada37xx_cpufreq_dvfs_setup(nb_pm_base, nb_clk_base, dvfs->भागider);
	clk_put(clk);

	क्रम (load_lvl = ARMADA_37XX_DVFS_LOAD_0; load_lvl < LOAD_LEVEL_NR;
	     load_lvl++) अणु
		अचिन्हित दीर्घ u_volt = avs_map[dvfs->avs[load_lvl]] * 1000;
		freq = base_frequency / dvfs->भागider[load_lvl];
		ret = dev_pm_opp_add(cpu_dev, freq, u_volt);
		अगर (ret)
			जाओ हटाओ_opp;


	पूर्ण

	/* Now that everything is setup, enable the DVFS at hardware level */
	armada37xx_cpufreq_enable_dvfs(nb_pm_base);

	स_रखो(&pdata, 0, माप(pdata));
	pdata.suspend = armada37xx_cpufreq_suspend;
	pdata.resume = armada37xx_cpufreq_resume;

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "cpufreq-dt", -1, &pdata,
					     माप(pdata));
	ret = PTR_ERR_OR_ZERO(pdev);
	अगर (ret)
		जाओ disable_dvfs;

	armada37xx_cpufreq_state->cpu_dev = cpu_dev;
	armada37xx_cpufreq_state->pdev = pdev;
	platक्रमm_set_drvdata(pdev, dvfs);
	वापस 0;

disable_dvfs:
	armada37xx_cpufreq_disable_dvfs(nb_pm_base);
हटाओ_opp:
	/* clean-up the alपढ़ोy added opp beक्रमe leaving */
	जबतक (load_lvl-- > ARMADA_37XX_DVFS_LOAD_0) अणु
		freq = base_frequency / dvfs->भागider[load_lvl];
		dev_pm_opp_हटाओ(cpu_dev, freq);
	पूर्ण

	kमुक्त(armada37xx_cpufreq_state);

	वापस ret;
पूर्ण
/* late_initcall, to guarantee the driver is loaded after A37xx घड़ी driver */
late_initcall(armada37xx_cpufreq_driver_init);

अटल व्योम __निकास armada37xx_cpufreq_driver_निकास(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev = armada37xx_cpufreq_state->pdev;
	काष्ठा armada_37xx_dvfs *dvfs = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ freq;
	पूर्णांक load_lvl;

	platक्रमm_device_unरेजिस्टर(pdev);

	armada37xx_cpufreq_disable_dvfs(armada37xx_cpufreq_state->regmap);

	क्रम (load_lvl = ARMADA_37XX_DVFS_LOAD_0; load_lvl < LOAD_LEVEL_NR; load_lvl++) अणु
		freq = dvfs->cpu_freq_max / dvfs->भागider[load_lvl];
		dev_pm_opp_हटाओ(armada37xx_cpufreq_state->cpu_dev, freq);
	पूर्ण

	kमुक्त(armada37xx_cpufreq_state);
पूर्ण
module_निकास(armada37xx_cpufreq_driver_निकास);

अटल स्थिर काष्ठा of_device_id __maybe_unused armada37xx_cpufreq_of_match[] = अणु
	अणु .compatible = "marvell,armada-3700-nb-pm" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, armada37xx_cpufreq_of_match);

MODULE_AUTHOR("Gregory CLEMENT <gregory.clement@free-electrons.com>");
MODULE_DESCRIPTION("Armada 37xx cpufreq driver");
MODULE_LICENSE("GPL");
