<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2020, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>

#समावेश <soc/tegra/mc.h>

#समावेश "tegra210-emc.h"
#समावेश "tegra210-mc.h"

/*
 * Enable flags क्रम specअगरying verbosity.
 */
#घोषणा INFO            (1 << 0)
#घोषणा STEPS           (1 << 1)
#घोषणा SUB_STEPS       (1 << 2)
#घोषणा PRELOCK         (1 << 3)
#घोषणा PRELOCK_STEPS   (1 << 4)
#घोषणा ACTIVE_EN       (1 << 5)
#घोषणा PRAMP_UP        (1 << 6)
#घोषणा PRAMP_DN        (1 << 7)
#घोषणा EMA_WRITES      (1 << 10)
#घोषणा EMA_UPDATES     (1 << 11)
#घोषणा PER_TRAIN       (1 << 16)
#घोषणा CC_PRINT        (1 << 17)
#घोषणा CCFIFO          (1 << 29)
#घोषणा REGS            (1 << 30)
#घोषणा REG_LISTS       (1 << 31)

#घोषणा emc_dbg(emc, flags, ...) dev_dbg(emc->dev, __VA_ARGS__)

#घोषणा DVFS_CLOCK_CHANGE_VERSION	21021
#घोषणा EMC_PRELOCK_VERSION		2101

क्रमागत अणु
	DVFS_SEQUENCE = 1,
	WRITE_TRAINING_SEQUENCE = 2,
	PERIODIC_TRAINING_SEQUENCE = 3,
	DVFS_PT1 = 10,
	DVFS_UPDATE = 11,
	TRAINING_PT1 = 12,
	TRAINING_UPDATE = 13,
	PERIODIC_TRAINING_UPDATE = 14
पूर्ण;

/*
 * PTFV defines - basically just indexes पूर्णांकo the per table PTFV array.
 */
#घोषणा PTFV_DQSOSC_MOVAVG_C0D0U0_INDEX		0
#घोषणा PTFV_DQSOSC_MOVAVG_C0D0U1_INDEX		1
#घोषणा PTFV_DQSOSC_MOVAVG_C0D1U0_INDEX		2
#घोषणा PTFV_DQSOSC_MOVAVG_C0D1U1_INDEX		3
#घोषणा PTFV_DQSOSC_MOVAVG_C1D0U0_INDEX		4
#घोषणा PTFV_DQSOSC_MOVAVG_C1D0U1_INDEX		5
#घोषणा PTFV_DQSOSC_MOVAVG_C1D1U0_INDEX		6
#घोषणा PTFV_DQSOSC_MOVAVG_C1D1U1_INDEX		7
#घोषणा PTFV_DVFS_SAMPLES_INDEX			9
#घोषणा PTFV_MOVAVG_WEIGHT_INDEX		10
#घोषणा PTFV_CONFIG_CTRL_INDEX			11

#घोषणा PTFV_CONFIG_CTRL_USE_PREVIOUS_EMA	(1 << 0)

/*
 * Do arithmetic in fixed poपूर्णांक.
 */
#घोषणा MOVAVG_PRECISION_FACTOR		100

/*
 * The भागision portion of the average operation.
 */
#घोषणा __AVERAGE_PTFV(dev)						\
	(अणु next->ptfv_list[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] =	\
	   next->ptfv_list[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] /	\
	   next->ptfv_list[PTFV_DVFS_SAMPLES_INDEX]; पूर्ण)

/*
 * Convert val to fixed poपूर्णांक and add it to the temporary average.
 */
#घोषणा __INCREMENT_PTFV(dev, val)					\
	(अणु next->ptfv_list[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] +=	\
	   ((val) * MOVAVG_PRECISION_FACTOR); पूर्ण)

/*
 * Convert a moving average back to पूर्णांकegral क्रमm and वापस the value.
 */
#घोषणा __MOVAVG_AC(timing, dev)					\
	((timing)->ptfv_list[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX] /	\
	 MOVAVG_PRECISION_FACTOR)

/* Weighted update. */
#घोषणा __WEIGHTED_UPDATE_PTFV(dev, nval)				\
	करो अणु								\
		पूर्णांक w = PTFV_MOVAVG_WEIGHT_INDEX;			\
		पूर्णांक dqs = PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX;		\
									\
		next->ptfv_list[dqs] =					\
			((nval * MOVAVG_PRECISION_FACTOR) +		\
			 (next->ptfv_list[dqs] *			\
			  next->ptfv_list[w])) /			\
			(next->ptfv_list[w] + 1);			\
									\
		emc_dbg(emc, EMA_UPDATES, "%s: (s=%lu) EMA: %u\n",	\
			__stringअगरy(dev), nval, next->ptfv_list[dqs]);	\
	पूर्ण जबतक (0)

/* Access a particular average. */
#घोषणा __MOVAVG(timing, dev)                      \
	((timing)->ptfv_list[PTFV_DQSOSC_MOVAVG_ ## dev ## _INDEX])

अटल u32 update_घड़ी_प्रकारree_delay(काष्ठा tegra210_emc *emc, पूर्णांक type)
अणु
	bool periodic_training_update = type == PERIODIC_TRAINING_UPDATE;
	काष्ठा tegra210_emc_timing *last = emc->last;
	काष्ठा tegra210_emc_timing *next = emc->next;
	u32 last_timing_rate_mhz = last->rate / 1000;
	u32 next_timing_rate_mhz = next->rate / 1000;
	bool dvfs_update = type == DVFS_UPDATE;
	s32 tdel = 0, पंचांगdel = 0, adel = 0;
	bool dvfs_pt1 = type == DVFS_PT1;
	अचिन्हित दीर्घ cval = 0;
	u32 temp[2][2], value;
	अचिन्हित पूर्णांक i;

	/*
	 * Dev0 MSB.
	 */
	अगर (dvfs_pt1 || periodic_training_update) अणु
		value = tegra210_emc_mrr_पढ़ो(emc, 2, 19);

		क्रम (i = 0; i < emc->num_channels; i++) अणु
			temp[i][0] = (value & 0x00ff) << 8;
			temp[i][1] = (value & 0xff00) << 0;
			value >>= 16;
		पूर्ण

		/*
		 * Dev0 LSB.
		 */
		value = tegra210_emc_mrr_पढ़ो(emc, 2, 18);

		क्रम (i = 0; i < emc->num_channels; i++) अणु
			temp[i][0] |= (value & 0x00ff) >> 0;
			temp[i][1] |= (value & 0xff00) >> 8;
			value >>= 16;
		पूर्ण
	पूर्ण

	अगर (dvfs_pt1 || periodic_training_update) अणु
		cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
		cval *= 1000000;
		cval /= last_timing_rate_mhz * 2 * temp[0][0];
	पूर्ण

	अगर (dvfs_pt1)
		__INCREMENT_PTFV(C0D0U0, cval);
	अन्यथा अगर (dvfs_update)
		__AVERAGE_PTFV(C0D0U0);
	अन्यथा अगर (periodic_training_update)
		__WEIGHTED_UPDATE_PTFV(C0D0U0, cval);

	अगर (dvfs_update || periodic_training_update) अणु
		tdel = next->current_dram_clktree[C0D0U0] -
				__MOVAVG_AC(next, C0D0U0);
		पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;
		adel = पंचांगdel;

		अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
		    next->tree_margin)
			next->current_dram_clktree[C0D0U0] =
				__MOVAVG_AC(next, C0D0U0);
	पूर्ण

	अगर (dvfs_pt1 || periodic_training_update) अणु
		cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
		cval *= 1000000;
		cval /= last_timing_rate_mhz * 2 * temp[0][1];
	पूर्ण

	अगर (dvfs_pt1)
		__INCREMENT_PTFV(C0D0U1, cval);
	अन्यथा अगर (dvfs_update)
		__AVERAGE_PTFV(C0D0U1);
	अन्यथा अगर (periodic_training_update)
		__WEIGHTED_UPDATE_PTFV(C0D0U1, cval);

	अगर (dvfs_update || periodic_training_update) अणु
		tdel = next->current_dram_clktree[C0D0U1] -
				__MOVAVG_AC(next, C0D0U1);
		पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

		अगर (पंचांगdel > adel)
			adel = पंचांगdel;

		अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
		    next->tree_margin)
			next->current_dram_clktree[C0D0U1] =
				__MOVAVG_AC(next, C0D0U1);
	पूर्ण

	अगर (emc->num_channels > 1) अणु
		अगर (dvfs_pt1 || periodic_training_update) अणु
			cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
			cval *= 1000000;
			cval /= last_timing_rate_mhz * 2 * temp[1][0];
		पूर्ण

		अगर (dvfs_pt1)
			__INCREMENT_PTFV(C1D0U0, cval);
		अन्यथा अगर (dvfs_update)
			__AVERAGE_PTFV(C1D0U0);
		अन्यथा अगर (periodic_training_update)
			__WEIGHTED_UPDATE_PTFV(C1D0U0, cval);

		अगर (dvfs_update || periodic_training_update) अणु
			tdel = next->current_dram_clktree[C1D0U0] -
					__MOVAVG_AC(next, C1D0U0);
			पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

			अगर (पंचांगdel > adel)
				adel = पंचांगdel;

			अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
			    next->tree_margin)
				next->current_dram_clktree[C1D0U0] =
					__MOVAVG_AC(next, C1D0U0);
		पूर्ण

		अगर (dvfs_pt1 || periodic_training_update) अणु
			cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
			cval *= 1000000;
			cval /= last_timing_rate_mhz * 2 * temp[1][1];
		पूर्ण

		अगर (dvfs_pt1)
			__INCREMENT_PTFV(C1D0U1, cval);
		अन्यथा अगर (dvfs_update)
			__AVERAGE_PTFV(C1D0U1);
		अन्यथा अगर (periodic_training_update)
			__WEIGHTED_UPDATE_PTFV(C1D0U1, cval);

		अगर (dvfs_update || periodic_training_update) अणु
			tdel = next->current_dram_clktree[C1D0U1] -
					__MOVAVG_AC(next, C1D0U1);
			पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

			अगर (पंचांगdel > adel)
				adel = पंचांगdel;

			अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
			    next->tree_margin)
				next->current_dram_clktree[C1D0U1] =
					__MOVAVG_AC(next, C1D0U1);
		पूर्ण
	पूर्ण

	अगर (emc->num_devices < 2)
		जाओ करोne;

	/*
	 * Dev1 MSB.
	 */
	अगर (dvfs_pt1 || periodic_training_update) अणु
		value = tegra210_emc_mrr_पढ़ो(emc, 1, 19);

		क्रम (i = 0; i < emc->num_channels; i++) अणु
			temp[i][0] = (value & 0x00ff) << 8;
			temp[i][1] = (value & 0xff00) << 0;
			value >>= 16;
		पूर्ण

		/*
		 * Dev1 LSB.
		 */
		value = tegra210_emc_mrr_पढ़ो(emc, 2, 18);

		क्रम (i = 0; i < emc->num_channels; i++) अणु
			temp[i][0] |= (value & 0x00ff) >> 0;
			temp[i][1] |= (value & 0xff00) >> 8;
			value >>= 16;
		पूर्ण
	पूर्ण

	अगर (dvfs_pt1 || periodic_training_update) अणु
		cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
		cval *= 1000000;
		cval /= last_timing_rate_mhz * 2 * temp[0][0];
	पूर्ण

	अगर (dvfs_pt1)
		__INCREMENT_PTFV(C0D1U0, cval);
	अन्यथा अगर (dvfs_update)
		__AVERAGE_PTFV(C0D1U0);
	अन्यथा अगर (periodic_training_update)
		__WEIGHTED_UPDATE_PTFV(C0D1U0, cval);

	अगर (dvfs_update || periodic_training_update) अणु
		tdel = next->current_dram_clktree[C0D1U0] -
				__MOVAVG_AC(next, C0D1U0);
		पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

		अगर (पंचांगdel > adel)
			adel = पंचांगdel;

		अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
		    next->tree_margin)
			next->current_dram_clktree[C0D1U0] =
				__MOVAVG_AC(next, C0D1U0);
	पूर्ण

	अगर (dvfs_pt1 || periodic_training_update) अणु
		cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
		cval *= 1000000;
		cval /= last_timing_rate_mhz * 2 * temp[0][1];
	पूर्ण

	अगर (dvfs_pt1)
		__INCREMENT_PTFV(C0D1U1, cval);
	अन्यथा अगर (dvfs_update)
		__AVERAGE_PTFV(C0D1U1);
	अन्यथा अगर (periodic_training_update)
		__WEIGHTED_UPDATE_PTFV(C0D1U1, cval);

	अगर (dvfs_update || periodic_training_update) अणु
		tdel = next->current_dram_clktree[C0D1U1] -
				__MOVAVG_AC(next, C0D1U1);
		पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

		अगर (पंचांगdel > adel)
			adel = पंचांगdel;

		अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
		    next->tree_margin)
			next->current_dram_clktree[C0D1U1] =
				__MOVAVG_AC(next, C0D1U1);
	पूर्ण

	अगर (emc->num_channels > 1) अणु
		अगर (dvfs_pt1 || periodic_training_update) अणु
			cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
			cval *= 1000000;
			cval /= last_timing_rate_mhz * 2 * temp[1][0];
		पूर्ण

		अगर (dvfs_pt1)
			__INCREMENT_PTFV(C1D1U0, cval);
		अन्यथा अगर (dvfs_update)
			__AVERAGE_PTFV(C1D1U0);
		अन्यथा अगर (periodic_training_update)
			__WEIGHTED_UPDATE_PTFV(C1D1U0, cval);

		अगर (dvfs_update || periodic_training_update) अणु
			tdel = next->current_dram_clktree[C1D1U0] -
					__MOVAVG_AC(next, C1D1U0);
			पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

			अगर (पंचांगdel > adel)
				adel = पंचांगdel;

			अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
			    next->tree_margin)
				next->current_dram_clktree[C1D1U0] =
					__MOVAVG_AC(next, C1D1U0);
		पूर्ण

		अगर (dvfs_pt1 || periodic_training_update) अणु
			cval = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
			cval *= 1000000;
			cval /= last_timing_rate_mhz * 2 * temp[1][1];
		पूर्ण

		अगर (dvfs_pt1)
			__INCREMENT_PTFV(C1D1U1, cval);
		अन्यथा अगर (dvfs_update)
			__AVERAGE_PTFV(C1D1U1);
		अन्यथा अगर (periodic_training_update)
			__WEIGHTED_UPDATE_PTFV(C1D1U1, cval);

		अगर (dvfs_update || periodic_training_update) अणु
			tdel = next->current_dram_clktree[C1D1U1] -
					__MOVAVG_AC(next, C1D1U1);
			पंचांगdel = (tdel < 0) ? -1 * tdel : tdel;

			अगर (पंचांगdel > adel)
				adel = पंचांगdel;

			अगर (पंचांगdel * 128 * next_timing_rate_mhz / 1000000 >
			    next->tree_margin)
				next->current_dram_clktree[C1D1U1] =
					__MOVAVG_AC(next, C1D1U1);
		पूर्ण
	पूर्ण

करोne:
	वापस adel;
पूर्ण

अटल u32 periodic_compensation_handler(काष्ठा tegra210_emc *emc, u32 type,
					 काष्ठा tegra210_emc_timing *last,
					 काष्ठा tegra210_emc_timing *next)
अणु
#घोषणा __COPY_EMA(nt, lt, dev)						\
	(अणु __MOVAVG(nt, dev) = __MOVAVG(lt, dev) *			\
	   (nt)->ptfv_list[PTFV_DVFS_SAMPLES_INDEX]; पूर्ण)

	u32 i, adel = 0, samples = next->ptfv_list[PTFV_DVFS_SAMPLES_INDEX];
	u32 delay;

	delay = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
	delay *= 1000;
	delay = 2 + (delay / last->rate);

	अगर (!next->periodic_training)
		वापस 0;

	अगर (type == DVFS_SEQUENCE) अणु
		अगर (last->periodic_training &&
		    (next->ptfv_list[PTFV_CONFIG_CTRL_INDEX] &
		     PTFV_CONFIG_CTRL_USE_PREVIOUS_EMA)) अणु
			/*
			 * If the previous frequency was using periodic
			 * calibration then we can reuse the previous
			 * frequencies EMA data.
			 */
			__COPY_EMA(next, last, C0D0U0);
			__COPY_EMA(next, last, C0D0U1);
			__COPY_EMA(next, last, C1D0U0);
			__COPY_EMA(next, last, C1D0U1);
			__COPY_EMA(next, last, C0D1U0);
			__COPY_EMA(next, last, C0D1U1);
			__COPY_EMA(next, last, C1D1U0);
			__COPY_EMA(next, last, C1D1U1);
		पूर्ण अन्यथा अणु
			/* Reset the EMA.*/
			__MOVAVG(next, C0D0U0) = 0;
			__MOVAVG(next, C0D0U1) = 0;
			__MOVAVG(next, C1D0U0) = 0;
			__MOVAVG(next, C1D0U1) = 0;
			__MOVAVG(next, C0D1U0) = 0;
			__MOVAVG(next, C0D1U1) = 0;
			__MOVAVG(next, C1D1U0) = 0;
			__MOVAVG(next, C1D1U1) = 0;

			क्रम (i = 0; i < samples; i++) अणु
				tegra210_emc_start_periodic_compensation(emc);
				udelay(delay);

				/*
				 * Generate next sample of data.
				 */
				adel = update_घड़ी_प्रकारree_delay(emc, DVFS_PT1);
			पूर्ण
		पूर्ण

		/*
		 * Seems like it should be part of the
		 * 'if (last_timing->periodic_training)' conditional
		 * since is alपढ़ोy करोne क्रम the अन्यथा clause.
		 */
		adel = update_घड़ी_प्रकारree_delay(emc, DVFS_UPDATE);
	पूर्ण

	अगर (type == PERIODIC_TRAINING_SEQUENCE) अणु
		tegra210_emc_start_periodic_compensation(emc);
		udelay(delay);

		adel = update_घड़ी_प्रकारree_delay(emc, PERIODIC_TRAINING_UPDATE);
	पूर्ण

	वापस adel;
पूर्ण

अटल u32 tegra210_emc_r21021_periodic_compensation(काष्ठा tegra210_emc *emc)
अणु
	u32 emc_cfg, emc_cfg_o, emc_cfg_update, del, value;
	u32 list[] = अणु
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2,
		EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3,
		EMC_DATA_BRLSHFT_0,
		EMC_DATA_BRLSHFT_1
	पूर्ण;
	काष्ठा tegra210_emc_timing *last = emc->last;
	अचिन्हित पूर्णांक items = ARRAY_SIZE(list), i;
	अचिन्हित दीर्घ delay;

	अगर (last->periodic_training) अणु
		emc_dbg(emc, PER_TRAIN, "Periodic training starting\n");

		value = emc_पढ़ोl(emc, EMC_DBG);
		emc_cfg_o = emc_पढ़ोl(emc, EMC_CFG);
		emc_cfg = emc_cfg_o & ~(EMC_CFG_DYN_SELF_REF |
					EMC_CFG_DRAM_ACPD |
					EMC_CFG_DRAM_CLKSTOP_PD);


		/*
		 * 1. Power optimizations should be off.
		 */
		emc_ग_लिखोl(emc, emc_cfg, EMC_CFG);

		/* Does emc_timing_update() क्रम above changes. */
		tegra210_emc_dll_disable(emc);

		क्रम (i = 0; i < emc->num_channels; i++)
			tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DRAM_IN_POWERDOWN_MASK,
						     0);

		क्रम (i = 0; i < emc->num_channels; i++)
			tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DRAM_IN_SELF_REFRESH_MASK,
						     0);

		emc_cfg_update = value = emc_पढ़ोl(emc, EMC_CFG_UPDATE);
		value &= ~EMC_CFG_UPDATE_UPDATE_DLL_IN_UPDATE_MASK;
		value |= (2 << EMC_CFG_UPDATE_UPDATE_DLL_IN_UPDATE_SHIFT);
		emc_ग_लिखोl(emc, value, EMC_CFG_UPDATE);

		/*
		 * 2. osc kick off - this assumes training and dvfs have set
		 *    correct MR23.
		 */
		tegra210_emc_start_periodic_compensation(emc);

		/*
		 * 3. Let dram capture its घड़ी tree delays.
		 */
		delay = tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
		delay *= 1000;
		delay /= last->rate + 1;
		udelay(delay);

		/*
		 * 4. Check delta wrt previous values (save value अगर margin
		 *    exceeds what is set in table).
		 */
		del = periodic_compensation_handler(emc,
						    PERIODIC_TRAINING_SEQUENCE,
						    last, last);

		/*
		 * 5. Apply compensation w.r.t. trained values (अगर घड़ी tree
		 *    has drअगरted more than the set margin).
		 */
		अगर (last->tree_margin < ((del * 128 * (last->rate / 1000)) / 1000000)) अणु
			क्रम (i = 0; i < items; i++) अणु
				value = tegra210_emc_compensate(last, list[i]);
				emc_dbg(emc, EMA_WRITES, "0x%08x <= 0x%08x\n",
					list[i], value);
				emc_ग_लिखोl(emc, value, list[i]);
			पूर्ण
		पूर्ण

		emc_ग_लिखोl(emc, emc_cfg_o, EMC_CFG);

		/*
		 * 6. Timing update actally applies the new trimmers.
		 */
		tegra210_emc_timing_update(emc);

		/* 6.1. Restore the UPDATE_DLL_IN_UPDATE field. */
		emc_ग_लिखोl(emc, emc_cfg_update, EMC_CFG_UPDATE);

		/* 6.2. Restore the DLL. */
		tegra210_emc_dll_enable(emc);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Do the घड़ी change sequence.
 */
अटल व्योम tegra210_emc_r21021_set_घड़ी(काष्ठा tegra210_emc *emc, u32 clksrc)
अणु
	/* state variables */
	अटल bool fsp_क्रम_next_freq;
	/* स्थिरant configuration parameters */
	स्थिर bool save_restore_clkstop_pd = true;
	स्थिर u32 zqcal_beक्रमe_cc_cutoff = 2400;
	स्थिर bool cya_allow_ref_cc = false;
	स्थिर bool cya_issue_pc_ref = false;
	स्थिर bool opt_cc_लघु_zcal = true;
	स्थिर bool ref_b4_sref_en = false;
	स्थिर u32 tZQCAL_lpddr4 = 1000000;
	स्थिर bool opt_लघु_zcal = true;
	स्थिर bool opt_करो_sw_qrst = true;
	स्थिर u32 opt_dvfs_mode = MAN_SR;
	/*
	 * This is the timing table क्रम the source frequency. It करोes _not_
	 * necessarily correspond to the actual timing values in the EMC at the
	 * moment. If the boot BCT dअगरfers from the table then this can happen.
	 * However, we need it क्रम accessing the dram_timings (which are not
	 * really रेजिस्टरs) array क्रम the current frequency.
	 */
	काष्ठा tegra210_emc_timing *fake, *last = emc->last, *next = emc->next;
	u32 tRTM, RP_war, R2P_war, TRPab_war, deltaTWATM, W2P_war, tRPST;
	u32 mr13_flip_fspwr, mr13_flip_fspop, ramp_up_रुको, ramp_करोwn_रुको;
	u32 zq_रुको_दीर्घ, zq_latch_dvfs_रुको_समय, tZQCAL_lpddr4_fc_adj;
	u32 emc_स्वतः_cal_config, स्वतः_cal_en, emc_cfg, emc_sel_dpd_ctrl;
	u32 tFC_lpddr4 = 1000 * next->dram_timings[T_FC_LPDDR4];
	u32 bg_reg_mode_change, enable_bglp_reg, enable_bg_reg;
	bool opt_zcal_en_cc = false, is_lpddr3 = false;
	bool compensate_trimmer_applicable = false;
	u32 emc_dbg, emc_cfg_pipe_clk, emc_pin;
	u32 src_clk_period, dst_clk_period; /* in picoseconds */
	bool shared_zq_resistor = false;
	u32 value, dram_type;
	u32 opt_dll_mode = 0;
	अचिन्हित दीर्घ delay;
	अचिन्हित पूर्णांक i;

	emc_dbg(emc, INFO, "Running clock change.\n");

	/* XXX fake == last */
	fake = tegra210_emc_find_timing(emc, last->rate * 1000UL);
	fsp_क्रम_next_freq = !fsp_क्रम_next_freq;

	value = emc_पढ़ोl(emc, EMC_FBIO_CFG5) & EMC_FBIO_CFG5_DRAM_TYPE_MASK;
	dram_type = value >> EMC_FBIO_CFG5_DRAM_TYPE_SHIFT;

	अगर (last->burst_regs[EMC_ZCAL_WAIT_CNT_INDEX] & BIT(31))
		shared_zq_resistor = true;

	अगर ((next->burst_regs[EMC_ZCAL_INTERVAL_INDEX] != 0 &&
	     last->burst_regs[EMC_ZCAL_INTERVAL_INDEX] == 0) ||
	    dram_type == DRAM_TYPE_LPDDR4)
		opt_zcal_en_cc = true;

	अगर (dram_type == DRAM_TYPE_DDR3)
		opt_dll_mode = tegra210_emc_get_dll_state(next);

	अगर ((next->burst_regs[EMC_FBIO_CFG5_INDEX] & BIT(25)) &&
	    (dram_type == DRAM_TYPE_LPDDR2))
		is_lpddr3 = true;

	emc_पढ़ोl(emc, EMC_CFG);
	emc_पढ़ोl(emc, EMC_AUTO_CAL_CONFIG);

	src_clk_period = 1000000000 / last->rate;
	dst_clk_period = 1000000000 / next->rate;

	अगर (dst_clk_period <= zqcal_beक्रमe_cc_cutoff)
		tZQCAL_lpddr4_fc_adj = tZQCAL_lpddr4 - tFC_lpddr4;
	अन्यथा
		tZQCAL_lpddr4_fc_adj = tZQCAL_lpddr4;

	tZQCAL_lpddr4_fc_adj /= dst_clk_period;

	emc_dbg = emc_पढ़ोl(emc, EMC_DBG);
	emc_pin = emc_पढ़ोl(emc, EMC_PIN);
	emc_cfg_pipe_clk = emc_पढ़ोl(emc, EMC_CFG_PIPE_CLK);

	emc_cfg = next->burst_regs[EMC_CFG_INDEX];
	emc_cfg &= ~(EMC_CFG_DYN_SELF_REF | EMC_CFG_DRAM_ACPD |
		     EMC_CFG_DRAM_CLKSTOP_SR | EMC_CFG_DRAM_CLKSTOP_PD);
	emc_sel_dpd_ctrl = next->emc_sel_dpd_ctrl;
	emc_sel_dpd_ctrl &= ~(EMC_SEL_DPD_CTRL_CLK_SEL_DPD_EN |
			      EMC_SEL_DPD_CTRL_CA_SEL_DPD_EN |
			      EMC_SEL_DPD_CTRL_RESET_SEL_DPD_EN |
			      EMC_SEL_DPD_CTRL_ODT_SEL_DPD_EN |
			      EMC_SEL_DPD_CTRL_DATA_SEL_DPD_EN);

	emc_dbg(emc, INFO, "Clock change version: %d\n",
		DVFS_CLOCK_CHANGE_VERSION);
	emc_dbg(emc, INFO, "DRAM type = %d\n", dram_type);
	emc_dbg(emc, INFO, "DRAM dev #: %u\n", emc->num_devices);
	emc_dbg(emc, INFO, "Next EMC clksrc: 0x%08x\n", clksrc);
	emc_dbg(emc, INFO, "DLL clksrc:      0x%08x\n", next->dll_clk_src);
	emc_dbg(emc, INFO, "last rate: %u, next rate %u\n", last->rate,
		next->rate);
	emc_dbg(emc, INFO, "last period: %u, next period: %u\n",
		src_clk_period, dst_clk_period);
	emc_dbg(emc, INFO, "  shared_zq_resistor: %d\n", !!shared_zq_resistor);
	emc_dbg(emc, INFO, "  num_channels: %u\n", emc->num_channels);
	emc_dbg(emc, INFO, "  opt_dll_mode: %d\n", opt_dll_mode);

	/*
	 * Step 1:
	 *   Pre DVFS SW sequence.
	 */
	emc_dbg(emc, STEPS, "Step 1\n");
	emc_dbg(emc, STEPS, "Step 1.1: Disable DLL temporarily.\n");

	value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_EN;
	emc_ग_लिखोl(emc, value, EMC_CFG_DIG_DLL);

	tegra210_emc_timing_update(emc);

	क्रम (i = 0; i < emc->num_channels; i++)
		tegra210_emc_रुको_क्रम_update(emc, i, EMC_CFG_DIG_DLL,
					     EMC_CFG_DIG_DLL_CFG_DLL_EN, 0);

	emc_dbg(emc, STEPS, "Step 1.2: Disable AUTOCAL temporarily.\n");

	emc_स्वतः_cal_config = next->emc_स्वतः_cal_config;
	स्वतः_cal_en = emc_स्वतः_cal_config & EMC_AUTO_CAL_CONFIG_AUTO_CAL_ENABLE;
	emc_स्वतः_cal_config &= ~EMC_AUTO_CAL_CONFIG_AUTO_CAL_START;
	emc_स्वतः_cal_config |= EMC_AUTO_CAL_CONFIG_AUTO_CAL_MEASURE_STALL;
	emc_स्वतः_cal_config |= EMC_AUTO_CAL_CONFIG_AUTO_CAL_UPDATE_STALL;
	emc_स्वतः_cal_config |= स्वतः_cal_en;
	emc_ग_लिखोl(emc, emc_स्वतः_cal_config, EMC_AUTO_CAL_CONFIG);
	emc_पढ़ोl(emc, EMC_AUTO_CAL_CONFIG); /* Flush ग_लिखो. */

	emc_dbg(emc, STEPS, "Step 1.3: Disable other power features.\n");

	tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
	emc_ग_लिखोl(emc, emc_cfg, EMC_CFG);
	emc_ग_लिखोl(emc, emc_sel_dpd_ctrl, EMC_SEL_DPD_CTRL);
	tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);

	अगर (next->periodic_training) अणु
		tegra210_emc_reset_dram_clktree_values(next);

		क्रम (i = 0; i < emc->num_channels; i++)
			tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DRAM_IN_POWERDOWN_MASK,
						     0);

		क्रम (i = 0; i < emc->num_channels; i++)
			tegra210_emc_रुको_क्रम_update(emc, i, EMC_EMC_STATUS,
						     EMC_EMC_STATUS_DRAM_IN_SELF_REFRESH_MASK,
						     0);

		tegra210_emc_start_periodic_compensation(emc);

		delay = 1000 * tegra210_emc_actual_osc_घड़ीs(last->run_घड़ीs);
		udelay((delay / last->rate) + 2);

		value = periodic_compensation_handler(emc, DVFS_SEQUENCE, fake,
						      next);
		value = (value * 128 * next->rate / 1000) / 1000000;

		अगर (next->periodic_training && value > next->tree_margin)
			compensate_trimmer_applicable = true;
	पूर्ण

	emc_ग_लिखोl(emc, EMC_INTSTATUS_CLKCHANGE_COMPLETE, EMC_INTSTATUS);
	tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
	emc_ग_लिखोl(emc, emc_cfg, EMC_CFG);
	emc_ग_लिखोl(emc, emc_sel_dpd_ctrl, EMC_SEL_DPD_CTRL);
	emc_ग_लिखोl(emc, emc_cfg_pipe_clk | EMC_CFG_PIPE_CLK_CLK_ALWAYS_ON,
		   EMC_CFG_PIPE_CLK);
	emc_ग_लिखोl(emc, next->emc_fdpd_ctrl_cmd_no_ramp &
			~EMC_FDPD_CTRL_CMD_NO_RAMP_CMD_DPD_NO_RAMP_ENABLE,
		   EMC_FDPD_CTRL_CMD_NO_RAMP);

	bg_reg_mode_change =
		((next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
		  EMC_PMACRO_BG_BIAS_CTRL_0_BGLP_E_PWRD) ^
		 (last->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
		  EMC_PMACRO_BG_BIAS_CTRL_0_BGLP_E_PWRD)) ||
		((next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
		  EMC_PMACRO_BG_BIAS_CTRL_0_BG_E_PWRD) ^
		 (last->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
		  EMC_PMACRO_BG_BIAS_CTRL_0_BG_E_PWRD));
	enable_bglp_reg =
		(next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
		 EMC_PMACRO_BG_BIAS_CTRL_0_BGLP_E_PWRD) == 0;
	enable_bg_reg =
		(next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
		 EMC_PMACRO_BG_BIAS_CTRL_0_BG_E_PWRD) == 0;

	अगर (bg_reg_mode_change) अणु
		अगर (enable_bg_reg)
			emc_ग_लिखोl(emc, last->burst_regs
				   [EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
				   ~EMC_PMACRO_BG_BIAS_CTRL_0_BG_E_PWRD,
				   EMC_PMACRO_BG_BIAS_CTRL_0);

		अगर (enable_bglp_reg)
			emc_ग_लिखोl(emc, last->burst_regs
				   [EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
				   ~EMC_PMACRO_BG_BIAS_CTRL_0_BGLP_E_PWRD,
				   EMC_PMACRO_BG_BIAS_CTRL_0);
	पूर्ण

	/* Check अगर we need to turn on VREF generator. */
	अगर ((((last->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX] &
	       EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_E_IVREF) == 0) &&
	     ((next->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX] &
	       EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_E_IVREF) == 1)) ||
	    (((last->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX] &
	       EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQS_E_IVREF) == 0) &&
	     ((next->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX] &
	       EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQS_E_IVREF) != 0))) अणु
		u32 pad_tx_ctrl =
		    next->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX];
		u32 last_pad_tx_ctrl =
		    last->burst_regs[EMC_PMACRO_DATA_PAD_TX_CTRL_INDEX];
		u32 next_dq_e_ivref, next_dqs_e_ivref;

		next_dqs_e_ivref = pad_tx_ctrl &
				   EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQS_E_IVREF;
		next_dq_e_ivref = pad_tx_ctrl &
				  EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_E_IVREF;
		value = (last_pad_tx_ctrl &
				~EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_E_IVREF &
				~EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQS_E_IVREF) |
			next_dq_e_ivref | next_dqs_e_ivref;
		emc_ग_लिखोl(emc, value, EMC_PMACRO_DATA_PAD_TX_CTRL);
		udelay(1);
	पूर्ण अन्यथा अगर (bg_reg_mode_change) अणु
		udelay(1);
	पूर्ण

	tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);

	/*
	 * Step 2:
	 *   Prelock the DLL.
	 */
	emc_dbg(emc, STEPS, "Step 2\n");

	अगर (next->burst_regs[EMC_CFG_DIG_DLL_INDEX] &
	    EMC_CFG_DIG_DLL_CFG_DLL_EN) अणु
		emc_dbg(emc, INFO, "Prelock enabled for target frequency.\n");
		value = tegra210_emc_dll_prelock(emc, clksrc);
		emc_dbg(emc, INFO, "DLL out: 0x%03x\n", value);
	पूर्ण अन्यथा अणु
		emc_dbg(emc, INFO, "Disabling DLL for target frequency.\n");
		tegra210_emc_dll_disable(emc);
	पूर्ण

	/*
	 * Step 3:
	 *   Prepare स्वतःcal क्रम the घड़ी change.
	 */
	emc_dbg(emc, STEPS, "Step 3\n");

	tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config2, EMC_AUTO_CAL_CONFIG2);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config3, EMC_AUTO_CAL_CONFIG3);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config4, EMC_AUTO_CAL_CONFIG4);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config5, EMC_AUTO_CAL_CONFIG5);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config6, EMC_AUTO_CAL_CONFIG6);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config7, EMC_AUTO_CAL_CONFIG7);
	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config8, EMC_AUTO_CAL_CONFIG8);
	tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);

	emc_स्वतः_cal_config |= (EMC_AUTO_CAL_CONFIG_AUTO_CAL_COMPUTE_START |
				स्वतः_cal_en);
	emc_ग_लिखोl(emc, emc_स्वतः_cal_config, EMC_AUTO_CAL_CONFIG);

	/*
	 * Step 4:
	 *   Update EMC_CFG. (??)
	 */
	emc_dbg(emc, STEPS, "Step 4\n");

	अगर (src_clk_period > 50000 && dram_type == DRAM_TYPE_LPDDR4)
		ccfअगरo_ग_लिखोl(emc, 1, EMC_SELF_REF, 0);
	अन्यथा
		emc_ग_लिखोl(emc, next->emc_cfg_2, EMC_CFG_2);

	/*
	 * Step 5:
	 *   Prepare reference variables क्रम ZQCAL regs.
	 */
	emc_dbg(emc, STEPS, "Step 5\n");

	अगर (dram_type == DRAM_TYPE_LPDDR4)
		zq_रुको_दीर्घ = max((u32)1, भाग_o3(1000000, dst_clk_period));
	अन्यथा अगर (dram_type == DRAM_TYPE_LPDDR2 || is_lpddr3)
		zq_रुको_दीर्घ = max(next->min_mrs_रुको,
				   भाग_o3(360000, dst_clk_period)) + 4;
	अन्यथा अगर (dram_type == DRAM_TYPE_DDR3)
		zq_रुको_दीर्घ = max((u32)256,
				   भाग_o3(320000, dst_clk_period) + 2);
	अन्यथा
		zq_रुको_दीर्घ = 0;

	/*
	 * Step 6:
	 *   Training code - हटाओd.
	 */
	emc_dbg(emc, STEPS, "Step 6\n");

	/*
	 * Step 7:
	 *   Program FSP reference रेजिस्टरs and send MRWs to new FSPWR.
	 */
	emc_dbg(emc, STEPS, "Step 7\n");
	emc_dbg(emc, SUB_STEPS, "Step 7.1: Bug 200024907 - Patch RP R2P");

	/* WAR 200024907 */
	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		u32 nRTP = 16;

		अगर (src_clk_period >= 1000000 / 1866) /* 535.91 ps */
			nRTP = 14;

		अगर (src_clk_period >= 1000000 / 1600) /* 625.00 ps */
			nRTP = 12;

		अगर (src_clk_period >= 1000000 / 1333) /* 750.19 ps */
			nRTP = 10;

		अगर (src_clk_period >= 1000000 / 1066) /* 938.09 ps */
			nRTP = 8;

		deltaTWATM = max_t(u32, भाग_o3(7500, src_clk_period), 8);

		/*
		 * Originally there was a + .5 in the tRPST calculation.
		 * However since we can't करो FP in the kernel and the tRTM
		 * computation was in a भग्नing poपूर्णांक उच्चमानing function, adding
		 * one to tRTP should be ok. There is no other source of non
		 * पूर्णांकeger values, so the result was always going to be
		 * something क्रम the क्रमm: f_उच्चमान(N + .5) = N + 1;
		 */
		tRPST = (last->emc_mrw & 0x80) >> 7;
		tRTM = fake->dram_timings[RL] + भाग_o3(3600, src_clk_period) +
			max_t(u32, भाग_o3(7500, src_clk_period), 8) + tRPST +
			1 + nRTP;

		emc_dbg(emc, INFO, "tRTM = %u, EMC_RP = %u\n", tRTM,
			next->burst_regs[EMC_RP_INDEX]);

		अगर (last->burst_regs[EMC_RP_INDEX] < tRTM) अणु
			अगर (tRTM > (last->burst_regs[EMC_R2P_INDEX] +
				    last->burst_regs[EMC_RP_INDEX])) अणु
				R2P_war = tRTM - last->burst_regs[EMC_RP_INDEX];
				RP_war = last->burst_regs[EMC_RP_INDEX];
				TRPab_war = last->burst_regs[EMC_TRPAB_INDEX];

				अगर (R2P_war > 63) अणु
					RP_war = R2P_war +
						 last->burst_regs[EMC_RP_INDEX] - 63;

					अगर (TRPab_war < RP_war)
						TRPab_war = RP_war;

					R2P_war = 63;
				पूर्ण
			पूर्ण अन्यथा अणु
				R2P_war = last->burst_regs[EMC_R2P_INDEX];
				RP_war = last->burst_regs[EMC_RP_INDEX];
				TRPab_war = last->burst_regs[EMC_TRPAB_INDEX];
			पूर्ण

			अगर (RP_war < deltaTWATM) अणु
				W2P_war = last->burst_regs[EMC_W2P_INDEX]
					  + deltaTWATM - RP_war;
				अगर (W2P_war > 63) अणु
					RP_war = RP_war + W2P_war - 63;
					अगर (TRPab_war < RP_war)
						TRPab_war = RP_war;
					W2P_war = 63;
				पूर्ण
			पूर्ण अन्यथा अणु
				W2P_war = last->burst_regs[
					  EMC_W2P_INDEX];
			पूर्ण

			अगर ((last->burst_regs[EMC_W2P_INDEX] ^ W2P_war) ||
			    (last->burst_regs[EMC_R2P_INDEX] ^ R2P_war) ||
			    (last->burst_regs[EMC_RP_INDEX] ^ RP_war) ||
			    (last->burst_regs[EMC_TRPAB_INDEX] ^ TRPab_war)) अणु
				emc_ग_लिखोl(emc, RP_war, EMC_RP);
				emc_ग_लिखोl(emc, R2P_war, EMC_R2P);
				emc_ग_लिखोl(emc, W2P_war, EMC_W2P);
				emc_ग_लिखोl(emc, TRPab_war, EMC_TRPAB);
			पूर्ण

			tegra210_emc_timing_update(emc);
		पूर्ण अन्यथा अणु
			emc_dbg(emc, INFO, "Skipped WAR\n");
		पूर्ण
	पूर्ण

	अगर (!fsp_क्रम_next_freq) अणु
		mr13_flip_fspwr = (next->emc_mrw3 & 0xffffff3f) | 0x80;
		mr13_flip_fspop = (next->emc_mrw3 & 0xffffff3f) | 0x00;
	पूर्ण अन्यथा अणु
		mr13_flip_fspwr = (next->emc_mrw3 & 0xffffff3f) | 0x40;
		mr13_flip_fspop = (next->emc_mrw3 & 0xffffff3f) | 0xc0;
	पूर्ण

	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		emc_ग_लिखोl(emc, mr13_flip_fspwr, EMC_MRW3);
		emc_ग_लिखोl(emc, next->emc_mrw, EMC_MRW);
		emc_ग_लिखोl(emc, next->emc_mrw2, EMC_MRW2);
	पूर्ण

	/*
	 * Step 8:
	 *   Program the shaकरोw रेजिस्टरs.
	 */
	emc_dbg(emc, STEPS, "Step 8\n");
	emc_dbg(emc, SUB_STEPS, "Writing burst_regs\n");

	क्रम (i = 0; i < next->num_burst; i++) अणु
		स्थिर u16 *offsets = emc->offsets->burst;
		u16 offset;

		अगर (!offsets[i])
			जारी;

		value = next->burst_regs[i];
		offset = offsets[i];

		अगर (dram_type != DRAM_TYPE_LPDDR4 &&
		    (offset == EMC_MRW6 || offset == EMC_MRW7 ||
		     offset == EMC_MRW8 || offset == EMC_MRW9 ||
		     offset == EMC_MRW10 || offset == EMC_MRW11 ||
		     offset == EMC_MRW12 || offset == EMC_MRW13 ||
		     offset == EMC_MRW14 || offset == EMC_MRW15 ||
		     offset == EMC_TRAINING_CTRL))
			जारी;

		/* Pain... And suffering. */
		अगर (offset == EMC_CFG) अणु
			value &= ~EMC_CFG_DRAM_ACPD;
			value &= ~EMC_CFG_DYN_SELF_REF;

			अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
				value &= ~EMC_CFG_DRAM_CLKSTOP_SR;
				value &= ~EMC_CFG_DRAM_CLKSTOP_PD;
			पूर्ण
		पूर्ण अन्यथा अगर (offset == EMC_MRS_WAIT_CNT &&
			   dram_type == DRAM_TYPE_LPDDR2 &&
			   opt_zcal_en_cc && !opt_cc_लघु_zcal &&
			   opt_लघु_zcal) अणु
			value = (value & ~(EMC_MRS_WAIT_CNT_SHORT_WAIT_MASK <<
					   EMC_MRS_WAIT_CNT_SHORT_WAIT_SHIFT)) |
				((zq_रुको_दीर्घ & EMC_MRS_WAIT_CNT_SHORT_WAIT_MASK) <<
						 EMC_MRS_WAIT_CNT_SHORT_WAIT_SHIFT);
		पूर्ण अन्यथा अगर (offset == EMC_ZCAL_WAIT_CNT &&
			   dram_type == DRAM_TYPE_DDR3 && opt_zcal_en_cc &&
			   !opt_cc_लघु_zcal && opt_लघु_zcal) अणु
			value = (value & ~(EMC_ZCAL_WAIT_CNT_ZCAL_WAIT_CNT_MASK <<
					   EMC_ZCAL_WAIT_CNT_ZCAL_WAIT_CNT_SHIFT)) |
				((zq_रुको_दीर्घ & EMC_ZCAL_WAIT_CNT_ZCAL_WAIT_CNT_MASK) <<
						 EMC_MRS_WAIT_CNT_SHORT_WAIT_SHIFT);
		पूर्ण अन्यथा अगर (offset == EMC_ZCAL_INTERVAL && opt_zcal_en_cc) अणु
			value = 0; /* EMC_ZCAL_INTERVAL reset value. */
		पूर्ण अन्यथा अगर (offset == EMC_PMACRO_AUTOCAL_CFG_COMMON) अणु
			value |= EMC_PMACRO_AUTOCAL_CFG_COMMON_E_CAL_BYPASS_DVFS;
		पूर्ण अन्यथा अगर (offset == EMC_PMACRO_DATA_PAD_TX_CTRL) अणु
			value &= ~(EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSP_TX_E_DCC |
				   EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQSN_TX_E_DCC |
				   EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_DQ_TX_E_DCC |
				   EMC_PMACRO_DATA_PAD_TX_CTRL_DATA_CMD_TX_E_DCC);
		पूर्ण अन्यथा अगर (offset == EMC_PMACRO_CMD_PAD_TX_CTRL) अणु
			value |= EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_DRVFORCEON;
			value &= ~(EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSP_TX_E_DCC |
				   EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQSN_TX_E_DCC |
				   EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_DQ_TX_E_DCC |
				   EMC_PMACRO_CMD_PAD_TX_CTRL_CMD_CMD_TX_E_DCC);
		पूर्ण अन्यथा अगर (offset == EMC_PMACRO_BRICK_CTRL_RFU1) अणु
			value &= 0xf800f800;
		पूर्ण अन्यथा अगर (offset == EMC_PMACRO_COMMON_PAD_TX_CTRL) अणु
			value &= 0xfffffff0;
		पूर्ण

		emc_ग_लिखोl(emc, value, offset);
	पूर्ण

	/* SW addition: करो EMC refresh adjusपंचांगent here. */
	tegra210_emc_adjust_timing(emc, next);

	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		value = (23 << EMC_MRW_MRW_MA_SHIFT) |
			(next->run_घड़ीs & EMC_MRW_MRW_OP_MASK);
		emc_ग_लिखोl(emc, value, EMC_MRW);
	पूर्ण

	/* Per channel burst रेजिस्टरs. */
	emc_dbg(emc, SUB_STEPS, "Writing burst_regs_per_ch\n");

	क्रम (i = 0; i < next->num_burst_per_ch; i++) अणु
		स्थिर काष्ठा tegra210_emc_per_channel_regs *burst =
				emc->offsets->burst_per_channel;

		अगर (!burst[i].offset)
			जारी;

		अगर (dram_type != DRAM_TYPE_LPDDR4 &&
		    (burst[i].offset == EMC_MRW6 ||
		     burst[i].offset == EMC_MRW7 ||
		     burst[i].offset == EMC_MRW8 ||
		     burst[i].offset == EMC_MRW9 ||
		     burst[i].offset == EMC_MRW10 ||
		     burst[i].offset == EMC_MRW11 ||
		     burst[i].offset == EMC_MRW12 ||
		     burst[i].offset == EMC_MRW13 ||
		     burst[i].offset == EMC_MRW14 ||
		     burst[i].offset == EMC_MRW15))
			जारी;

		/* Filter out second channel अगर not in DUAL_CHANNEL mode. */
		अगर (emc->num_channels < 2 && burst[i].bank >= 1)
			जारी;

		emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
			next->burst_reg_per_ch[i], burst[i].offset);
		emc_channel_ग_लिखोl(emc, burst[i].bank,
				   next->burst_reg_per_ch[i],
				   burst[i].offset);
	पूर्ण

	/* Vref regs. */
	emc_dbg(emc, SUB_STEPS, "Writing vref_regs\n");

	क्रम (i = 0; i < next->vref_num; i++) अणु
		स्थिर काष्ठा tegra210_emc_per_channel_regs *vref =
					emc->offsets->vref_per_channel;

		अगर (!vref[i].offset)
			जारी;

		अगर (emc->num_channels < 2 && vref[i].bank >= 1)
			जारी;

		emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
			next->vref_perch_regs[i], vref[i].offset);
		emc_channel_ग_लिखोl(emc, vref[i].bank, next->vref_perch_regs[i],
				   vref[i].offset);
	पूर्ण

	/* Trimmers. */
	emc_dbg(emc, SUB_STEPS, "Writing trim_regs\n");

	क्रम (i = 0; i < next->num_trim; i++) अणु
		स्थिर u16 *offsets = emc->offsets->trim;

		अगर (!offsets[i])
			जारी;

		अगर (compensate_trimmer_applicable &&
		    (offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2 ||
		     offsets[i] == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3 ||
		     offsets[i] == EMC_DATA_BRLSHFT_0 ||
		     offsets[i] == EMC_DATA_BRLSHFT_1)) अणु
			value = tegra210_emc_compensate(next, offsets[i]);
			emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
				value, offsets[i]);
			emc_dbg(emc, EMA_WRITES, "0x%08x <= 0x%08x\n",
				(u32)(u64)offsets[i], value);
			emc_ग_लिखोl(emc, value, offsets[i]);
		पूर्ण अन्यथा अणु
			emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
				next->trim_regs[i], offsets[i]);
			emc_ग_लिखोl(emc, next->trim_regs[i], offsets[i]);
		पूर्ण
	पूर्ण

	/* Per channel trimmers. */
	emc_dbg(emc, SUB_STEPS, "Writing trim_regs_per_ch\n");

	क्रम (i = 0; i < next->num_trim_per_ch; i++) अणु
		स्थिर काष्ठा tegra210_emc_per_channel_regs *trim =
				&emc->offsets->trim_per_channel[0];
		अचिन्हित पूर्णांक offset;

		अगर (!trim[i].offset)
			जारी;

		अगर (emc->num_channels < 2 && trim[i].bank >= 1)
			जारी;

		offset = trim[i].offset;

		अगर (compensate_trimmer_applicable &&
		    (offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2 ||
		     offset == EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3 ||
		     offset == EMC_DATA_BRLSHFT_0 ||
		     offset == EMC_DATA_BRLSHFT_1)) अणु
			value = tegra210_emc_compensate(next, offset);
			emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
				value, offset);
			emc_dbg(emc, EMA_WRITES, "0x%08x <= 0x%08x\n", offset,
				value);
			emc_channel_ग_लिखोl(emc, trim[i].bank, value, offset);
		पूर्ण अन्यथा अणु
			emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
				next->trim_perch_regs[i], offset);
			emc_channel_ग_लिखोl(emc, trim[i].bank,
					   next->trim_perch_regs[i], offset);
		पूर्ण
	पूर्ण

	emc_dbg(emc, SUB_STEPS, "Writing burst_mc_regs\n");

	क्रम (i = 0; i < next->num_mc_regs; i++) अणु
		स्थिर u16 *offsets = emc->offsets->burst_mc;
		u32 *values = next->burst_mc_regs;

		emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
			values[i], offsets[i]);
		mc_ग_लिखोl(emc->mc, values[i], offsets[i]);
	पूर्ण

	/* Registers to be programmed on the faster घड़ी. */
	अगर (next->rate < last->rate) अणु
		स्थिर u16 *la = emc->offsets->la_scale;

		emc_dbg(emc, SUB_STEPS, "Writing la_scale_regs\n");

		क्रम (i = 0; i < next->num_up_करोwn; i++) अणु
			emc_dbg(emc, REG_LISTS, "(%u) 0x%08x => 0x%08x\n", i,
				next->la_scale_regs[i], la[i]);
			mc_ग_लिखोl(emc->mc, next->la_scale_regs[i], la[i]);
		पूर्ण
	पूर्ण

	/* Flush all the burst रेजिस्टर ग_लिखोs. */
	mc_पढ़ोl(emc->mc, MC_EMEM_ADR_CFG);

	/*
	 * Step 9:
	 *   LPDDR4 section A.
	 */
	emc_dbg(emc, STEPS, "Step 9\n");

	value = next->burst_regs[EMC_ZCAL_WAIT_CNT_INDEX];
	value &= ~EMC_ZCAL_WAIT_CNT_ZCAL_WAIT_CNT_MASK;

	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		emc_ग_लिखोl(emc, 0, EMC_ZCAL_INTERVAL);
		emc_ग_लिखोl(emc, value, EMC_ZCAL_WAIT_CNT);

		value = emc_dbg | (EMC_DBG_WRITE_MUX_ACTIVE |
				   EMC_DBG_WRITE_ACTIVE_ONLY);

		emc_ग_लिखोl(emc, value, EMC_DBG);
		emc_ग_लिखोl(emc, 0, EMC_ZCAL_INTERVAL);
		emc_ग_लिखोl(emc, emc_dbg, EMC_DBG);
	पूर्ण

	/*
	 * Step 10:
	 *   LPDDR4 and DDR3 common section.
	 */
	emc_dbg(emc, STEPS, "Step 10\n");

	अगर (opt_dvfs_mode == MAN_SR || dram_type == DRAM_TYPE_LPDDR4) अणु
		अगर (dram_type == DRAM_TYPE_LPDDR4)
			ccfअगरo_ग_लिखोl(emc, 0x101, EMC_SELF_REF, 0);
		अन्यथा
			ccfअगरo_ग_लिखोl(emc, 0x1, EMC_SELF_REF, 0);

		अगर (dram_type == DRAM_TYPE_LPDDR4 &&
		    dst_clk_period <= zqcal_beक्रमe_cc_cutoff) अणु
			ccfअगरo_ग_लिखोl(emc, mr13_flip_fspwr ^ 0x40, EMC_MRW3, 0);
			ccfअगरo_ग_लिखोl(emc, (next->burst_regs[EMC_MRW6_INDEX] &
						0xFFFF3F3F) |
					   (last->burst_regs[EMC_MRW6_INDEX] &
						0x0000C0C0), EMC_MRW6, 0);
			ccfअगरo_ग_लिखोl(emc, (next->burst_regs[EMC_MRW14_INDEX] &
						0xFFFF0707) |
					   (last->burst_regs[EMC_MRW14_INDEX] &
						0x00003838), EMC_MRW14, 0);

			अगर (emc->num_devices > 1) अणु
				ccfअगरo_ग_लिखोl(emc,
				      (next->burst_regs[EMC_MRW7_INDEX] &
				       0xFFFF3F3F) |
				      (last->burst_regs[EMC_MRW7_INDEX] &
				       0x0000C0C0), EMC_MRW7, 0);
				ccfअगरo_ग_लिखोl(emc,
				     (next->burst_regs[EMC_MRW15_INDEX] &
				      0xFFFF0707) |
				     (last->burst_regs[EMC_MRW15_INDEX] &
				      0x00003838), EMC_MRW15, 0);
			पूर्ण

			अगर (opt_zcal_en_cc) अणु
				अगर (emc->num_devices < 2)
					ccfअगरo_ग_लिखोl(emc,
						2UL << EMC_ZQ_CAL_DEV_SEL_SHIFT
						| EMC_ZQ_CAL_ZQ_CAL_CMD,
						EMC_ZQ_CAL, 0);
				अन्यथा अगर (shared_zq_resistor)
					ccfअगरo_ग_लिखोl(emc,
						2UL << EMC_ZQ_CAL_DEV_SEL_SHIFT
						| EMC_ZQ_CAL_ZQ_CAL_CMD,
						EMC_ZQ_CAL, 0);
				अन्यथा
					ccfअगरo_ग_लिखोl(emc,
						      EMC_ZQ_CAL_ZQ_CAL_CMD,
						      EMC_ZQ_CAL, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		value = (1000 * fake->dram_timings[T_RP]) / src_clk_period;
		ccfअगरo_ग_लिखोl(emc, mr13_flip_fspop | 0x8, EMC_MRW3, value);
		ccfअगरo_ग_लिखोl(emc, 0, 0, tFC_lpddr4 / src_clk_period);
	पूर्ण

	अगर (dram_type == DRAM_TYPE_LPDDR4 || opt_dvfs_mode != MAN_SR) अणु
		delay = 30;

		अगर (cya_allow_ref_cc) अणु
			delay += (1000 * fake->dram_timings[T_RP]) /
					src_clk_period;
			delay += 4000 * fake->dram_timings[T_RFC];
		पूर्ण

		ccfअगरo_ग_लिखोl(emc, emc_pin & ~(EMC_PIN_PIN_CKE_PER_DEV |
					       EMC_PIN_PIN_CKEB |
					       EMC_PIN_PIN_CKE),
			      EMC_PIN, delay);
	पूर्ण

	/* calculate reference delay multiplier */
	value = 1;

	अगर (ref_b4_sref_en)
		value++;

	अगर (cya_allow_ref_cc)
		value++;

	अगर (cya_issue_pc_ref)
		value++;

	अगर (dram_type != DRAM_TYPE_LPDDR4) अणु
		delay = ((1000 * fake->dram_timings[T_RP] / src_clk_period) +
			 (1000 * fake->dram_timings[T_RFC] / src_clk_period));
		delay = value * delay + 20;
	पूर्ण अन्यथा अणु
		delay = 0;
	पूर्ण

	/*
	 * Step 11:
	 *   Ramp करोwn.
	 */
	emc_dbg(emc, STEPS, "Step 11\n");

	ccfअगरo_ग_लिखोl(emc, 0x0, EMC_CFG_SYNC, delay);

	value = emc_dbg | EMC_DBG_WRITE_MUX_ACTIVE | EMC_DBG_WRITE_ACTIVE_ONLY;
	ccfअगरo_ग_लिखोl(emc, value, EMC_DBG, 0);

	ramp_करोwn_रुको = tegra210_emc_dvfs_घातer_ramp_करोwn(emc, src_clk_period,
							   0);

	/*
	 * Step 12:
	 *   And finally - trigger the घड़ी change.
	 */
	emc_dbg(emc, STEPS, "Step 12\n");

	ccfअगरo_ग_लिखोl(emc, 1, EMC_STALL_THEN_EXE_AFTER_CLKCHANGE, 0);
	value &= ~EMC_DBG_WRITE_ACTIVE_ONLY;
	ccfअगरo_ग_लिखोl(emc, value, EMC_DBG, 0);

	/*
	 * Step 13:
	 *   Ramp up.
	 */
	emc_dbg(emc, STEPS, "Step 13\n");

	ramp_up_रुको = tegra210_emc_dvfs_घातer_ramp_up(emc, dst_clk_period, 0);
	ccfअगरo_ग_लिखोl(emc, emc_dbg, EMC_DBG, 0);

	/*
	 * Step 14:
	 *   Bringup CKE pins.
	 */
	emc_dbg(emc, STEPS, "Step 14\n");

	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		value = emc_pin | EMC_PIN_PIN_CKE;

		अगर (emc->num_devices <= 1)
			value &= ~(EMC_PIN_PIN_CKEB | EMC_PIN_PIN_CKE_PER_DEV);
		अन्यथा
			value |= EMC_PIN_PIN_CKEB | EMC_PIN_PIN_CKE_PER_DEV;

		ccfअगरo_ग_लिखोl(emc, value, EMC_PIN, 0);
	पूर्ण

	/*
	 * Step 15: (two step 15s ??)
	 *   Calculate zqlatch रुको समय; has dependency on ramping बार.
	 */
	emc_dbg(emc, STEPS, "Step 15\n");

	अगर (dst_clk_period <= zqcal_beक्रमe_cc_cutoff) अणु
		s32 t = (s32)(ramp_up_रुको + ramp_करोwn_रुको) /
			(s32)dst_clk_period;
		zq_latch_dvfs_रुको_समय = (s32)tZQCAL_lpddr4_fc_adj - t;
	पूर्ण अन्यथा अणु
		zq_latch_dvfs_रुको_समय = tZQCAL_lpddr4_fc_adj -
			भाग_o3(1000 * next->dram_timings[T_PDEX],
			       dst_clk_period);
	पूर्ण

	emc_dbg(emc, INFO, "tZQCAL_lpddr4_fc_adj = %u\n", tZQCAL_lpddr4_fc_adj);
	emc_dbg(emc, INFO, "dst_clk_period = %u\n",
		dst_clk_period);
	emc_dbg(emc, INFO, "next->dram_timings[T_PDEX] = %u\n",
		next->dram_timings[T_PDEX]);
	emc_dbg(emc, INFO, "zq_latch_dvfs_wait_time = %d\n",
		max_t(s32, 0, zq_latch_dvfs_रुको_समय));

	अगर (dram_type == DRAM_TYPE_LPDDR4 && opt_zcal_en_cc) अणु
		delay = भाग_o3(1000 * next->dram_timings[T_PDEX],
			       dst_clk_period);

		अगर (emc->num_devices < 2) अणु
			अगर (dst_clk_period > zqcal_beक्रमe_cc_cutoff)
				ccfअगरo_ग_लिखोl(emc,
					      2UL << EMC_ZQ_CAL_DEV_SEL_SHIFT |
					      EMC_ZQ_CAL_ZQ_CAL_CMD, EMC_ZQ_CAL,
					      delay);

			value = (mr13_flip_fspop & 0xfffffff7) | 0x0c000000;
			ccfअगरo_ग_लिखोl(emc, value, EMC_MRW3, delay);
			ccfअगरo_ग_लिखोl(emc, 0, EMC_SELF_REF, 0);
			ccfअगरo_ग_लिखोl(emc, 0, EMC_REF, 0);
			ccfअगरo_ग_लिखोl(emc, 2UL << EMC_ZQ_CAL_DEV_SEL_SHIFT |
				      EMC_ZQ_CAL_ZQ_LATCH_CMD,
				      EMC_ZQ_CAL,
				      max_t(s32, 0, zq_latch_dvfs_रुको_समय));
		पूर्ण अन्यथा अगर (shared_zq_resistor) अणु
			अगर (dst_clk_period > zqcal_beक्रमe_cc_cutoff)
				ccfअगरo_ग_लिखोl(emc,
					      2UL << EMC_ZQ_CAL_DEV_SEL_SHIFT |
					      EMC_ZQ_CAL_ZQ_CAL_CMD, EMC_ZQ_CAL,
					      delay);

			ccfअगरo_ग_लिखोl(emc, 2UL << EMC_ZQ_CAL_DEV_SEL_SHIFT |
				      EMC_ZQ_CAL_ZQ_LATCH_CMD, EMC_ZQ_CAL,
				      max_t(s32, 0, zq_latch_dvfs_रुको_समय) +
					delay);
			ccfअगरo_ग_लिखोl(emc, 1UL << EMC_ZQ_CAL_DEV_SEL_SHIFT |
				      EMC_ZQ_CAL_ZQ_LATCH_CMD,
				      EMC_ZQ_CAL, 0);

			value = (mr13_flip_fspop & 0xfffffff7) | 0x0c000000;
			ccfअगरo_ग_लिखोl(emc, value, EMC_MRW3, 0);
			ccfअगरo_ग_लिखोl(emc, 0, EMC_SELF_REF, 0);
			ccfअगरo_ग_लिखोl(emc, 0, EMC_REF, 0);

			ccfअगरo_ग_लिखोl(emc, 1UL << EMC_ZQ_CAL_DEV_SEL_SHIFT |
				      EMC_ZQ_CAL_ZQ_LATCH_CMD, EMC_ZQ_CAL,
				      tZQCAL_lpddr4 / dst_clk_period);
		पूर्ण अन्यथा अणु
			अगर (dst_clk_period > zqcal_beक्रमe_cc_cutoff)
				ccfअगरo_ग_लिखोl(emc, EMC_ZQ_CAL_ZQ_CAL_CMD,
					      EMC_ZQ_CAL, delay);

			value = (mr13_flip_fspop & 0xfffffff7) | 0x0c000000;
			ccfअगरo_ग_लिखोl(emc, value, EMC_MRW3, delay);
			ccfअगरo_ग_लिखोl(emc, 0, EMC_SELF_REF, 0);
			ccfअगरo_ग_लिखोl(emc, 0, EMC_REF, 0);

			ccfअगरo_ग_लिखोl(emc, EMC_ZQ_CAL_ZQ_LATCH_CMD, EMC_ZQ_CAL,
				      max_t(s32, 0, zq_latch_dvfs_रुको_समय));
		पूर्ण
	पूर्ण

	/* WAR: delay क्रम zqlatch */
	ccfअगरo_ग_लिखोl(emc, 0, 0, 10);

	/*
	 * Step 16:
	 *   LPDDR4 Conditional Training Kickoff. Removed.
	 */

	/*
	 * Step 17:
	 *   MANSR निकास self refresh.
	 */
	emc_dbg(emc, STEPS, "Step 17\n");

	अगर (opt_dvfs_mode == MAN_SR && dram_type != DRAM_TYPE_LPDDR4)
		ccfअगरo_ग_लिखोl(emc, 0, EMC_SELF_REF, 0);

	/*
	 * Step 18:
	 *   Send MRWs to LPDDR3/DDR3.
	 */
	emc_dbg(emc, STEPS, "Step 18\n");

	अगर (dram_type == DRAM_TYPE_LPDDR2) अणु
		ccfअगरo_ग_लिखोl(emc, next->emc_mrw2, EMC_MRW2, 0);
		ccfअगरo_ग_लिखोl(emc, next->emc_mrw,  EMC_MRW,  0);
		अगर (is_lpddr3)
			ccfअगरo_ग_लिखोl(emc, next->emc_mrw4, EMC_MRW4, 0);
	पूर्ण अन्यथा अगर (dram_type == DRAM_TYPE_DDR3) अणु
		अगर (opt_dll_mode)
			ccfअगरo_ग_लिखोl(emc, next->emc_emrs &
				      ~EMC_EMRS_USE_EMRS_LONG_CNT, EMC_EMRS, 0);
		ccfअगरo_ग_लिखोl(emc, next->emc_emrs2 &
			      ~EMC_EMRS2_USE_EMRS2_LONG_CNT, EMC_EMRS2, 0);
		ccfअगरo_ग_लिखोl(emc, next->emc_mrs |
			      EMC_EMRS_USE_EMRS_LONG_CNT, EMC_MRS, 0);
	पूर्ण

	/*
	 * Step 19:
	 *   ZQCAL क्रम LPDDR3/DDR3
	 */
	emc_dbg(emc, STEPS, "Step 19\n");

	अगर (opt_zcal_en_cc) अणु
		अगर (dram_type == DRAM_TYPE_LPDDR2) अणु
			value = opt_cc_लघु_zcal ? 90000 : 360000;
			value = भाग_o3(value, dst_clk_period);
			value = value <<
				EMC_MRS_WAIT_CNT2_MRS_EXT2_WAIT_CNT_SHIFT |
				value <<
				EMC_MRS_WAIT_CNT2_MRS_EXT1_WAIT_CNT_SHIFT;
			ccfअगरo_ग_लिखोl(emc, value, EMC_MRS_WAIT_CNT2, 0);

			value = opt_cc_लघु_zcal ? 0x56 : 0xab;
			ccfअगरo_ग_लिखोl(emc, 2 << EMC_MRW_MRW_DEV_SELECTN_SHIFT |
					   EMC_MRW_USE_MRW_EXT_CNT |
					   10 << EMC_MRW_MRW_MA_SHIFT |
					   value << EMC_MRW_MRW_OP_SHIFT,
				      EMC_MRW, 0);

			अगर (emc->num_devices > 1) अणु
				value = 1 << EMC_MRW_MRW_DEV_SELECTN_SHIFT |
					EMC_MRW_USE_MRW_EXT_CNT |
					10 << EMC_MRW_MRW_MA_SHIFT |
					value << EMC_MRW_MRW_OP_SHIFT;
				ccfअगरo_ग_लिखोl(emc, value, EMC_MRW, 0);
			पूर्ण
		पूर्ण अन्यथा अगर (dram_type == DRAM_TYPE_DDR3) अणु
			value = opt_cc_लघु_zcal ? 0 : EMC_ZQ_CAL_LONG;

			ccfअगरo_ग_लिखोl(emc, value |
					   2 << EMC_ZQ_CAL_DEV_SEL_SHIFT |
					   EMC_ZQ_CAL_ZQ_CAL_CMD, EMC_ZQ_CAL,
					   0);

			अगर (emc->num_devices > 1) अणु
				value = value | 1 << EMC_ZQ_CAL_DEV_SEL_SHIFT |
						EMC_ZQ_CAL_ZQ_CAL_CMD;
				ccfअगरo_ग_लिखोl(emc, value, EMC_ZQ_CAL, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bg_reg_mode_change) अणु
		tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);

		अगर (ramp_up_रुको <= 1250000)
			delay = (1250000 - ramp_up_रुको) / dst_clk_period;
		अन्यथा
			delay = 0;

		ccfअगरo_ग_लिखोl(emc,
			      next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX],
			      EMC_PMACRO_BG_BIAS_CTRL_0, delay);
		tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);
	पूर्ण

	/*
	 * Step 20:
	 *   Issue ref and optional QRST.
	 */
	emc_dbg(emc, STEPS, "Step 20\n");

	अगर (dram_type != DRAM_TYPE_LPDDR4)
		ccfअगरo_ग_लिखोl(emc, 0, EMC_REF, 0);

	अगर (opt_करो_sw_qrst) अणु
		ccfअगरo_ग_लिखोl(emc, 1, EMC_ISSUE_QRST, 0);
		ccfअगरo_ग_लिखोl(emc, 0, EMC_ISSUE_QRST, 2);
	पूर्ण

	/*
	 * Step 21:
	 *   Restore ZCAL and ZCAL पूर्णांकerval.
	 */
	emc_dbg(emc, STEPS, "Step 21\n");

	अगर (save_restore_clkstop_pd || opt_zcal_en_cc) अणु
		ccfअगरo_ग_लिखोl(emc, emc_dbg | EMC_DBG_WRITE_MUX_ACTIVE,
			      EMC_DBG, 0);
		अगर (opt_zcal_en_cc && dram_type != DRAM_TYPE_LPDDR4)
			ccfअगरo_ग_लिखोl(emc, next->burst_regs[EMC_ZCAL_INTERVAL_INDEX],
				      EMC_ZCAL_INTERVAL, 0);

		अगर (save_restore_clkstop_pd)
			ccfअगरo_ग_लिखोl(emc, next->burst_regs[EMC_CFG_INDEX] &
						~EMC_CFG_DYN_SELF_REF,
				      EMC_CFG, 0);
		ccfअगरo_ग_लिखोl(emc, emc_dbg, EMC_DBG, 0);
	पूर्ण

	/*
	 * Step 22:
	 *   Restore EMC_CFG_PIPE_CLK.
	 */
	emc_dbg(emc, STEPS, "Step 22\n");

	ccfअगरo_ग_लिखोl(emc, emc_cfg_pipe_clk, EMC_CFG_PIPE_CLK, 0);

	अगर (bg_reg_mode_change) अणु
		अगर (enable_bg_reg)
			emc_ग_लिखोl(emc,
				   next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
					~EMC_PMACRO_BG_BIAS_CTRL_0_BGLP_E_PWRD,
				   EMC_PMACRO_BG_BIAS_CTRL_0);
		अन्यथा
			emc_ग_लिखोl(emc,
				   next->burst_regs[EMC_PMACRO_BG_BIAS_CTRL_0_INDEX] &
					~EMC_PMACRO_BG_BIAS_CTRL_0_BG_E_PWRD,
				   EMC_PMACRO_BG_BIAS_CTRL_0);
	पूर्ण

	/*
	 * Step 23:
	 */
	emc_dbg(emc, STEPS, "Step 23\n");

	value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
	value |= EMC_CFG_DIG_DLL_CFG_DLL_STALL_ALL_TRAFFIC;
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_STALL_RW_UNTIL_LOCK;
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_STALL_ALL_UNTIL_LOCK;
	value &= ~EMC_CFG_DIG_DLL_CFG_DLL_EN;
	value = (value & ~EMC_CFG_DIG_DLL_CFG_DLL_MODE_MASK) |
		(2 << EMC_CFG_DIG_DLL_CFG_DLL_MODE_SHIFT);
	emc_ग_लिखोl(emc, value, EMC_CFG_DIG_DLL);

	tegra210_emc_करो_घड़ी_change(emc, clksrc);

	/*
	 * Step 24:
	 *   Save training results. Removed.
	 */

	/*
	 * Step 25:
	 *   Program MC upकरोwn रेजिस्टरs.
	 */
	emc_dbg(emc, STEPS, "Step 25\n");

	अगर (next->rate > last->rate) अणु
		क्रम (i = 0; i < next->num_up_करोwn; i++)
			mc_ग_लिखोl(emc->mc, next->la_scale_regs[i],
				  emc->offsets->la_scale[i]);

		tegra210_emc_timing_update(emc);
	पूर्ण

	/*
	 * Step 26:
	 *   Restore ZCAL रेजिस्टरs.
	 */
	emc_dbg(emc, STEPS, "Step 26\n");

	अगर (dram_type == DRAM_TYPE_LPDDR4) अणु
		tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
		emc_ग_लिखोl(emc, next->burst_regs[EMC_ZCAL_WAIT_CNT_INDEX],
			   EMC_ZCAL_WAIT_CNT);
		emc_ग_लिखोl(emc, next->burst_regs[EMC_ZCAL_INTERVAL_INDEX],
			   EMC_ZCAL_INTERVAL);
		tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);
	पूर्ण

	अगर (dram_type != DRAM_TYPE_LPDDR4 && opt_zcal_en_cc &&
	    !opt_लघु_zcal && opt_cc_लघु_zcal) अणु
		udelay(2);

		tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
		अगर (dram_type == DRAM_TYPE_LPDDR2)
			emc_ग_लिखोl(emc, next->burst_regs[EMC_MRS_WAIT_CNT_INDEX],
				   EMC_MRS_WAIT_CNT);
		अन्यथा अगर (dram_type == DRAM_TYPE_DDR3)
			emc_ग_लिखोl(emc, next->burst_regs[EMC_ZCAL_WAIT_CNT_INDEX],
				   EMC_ZCAL_WAIT_CNT);
		tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);
	पूर्ण

	/*
	 * Step 27:
	 *   Restore EMC_CFG, FDPD रेजिस्टरs.
	 */
	emc_dbg(emc, STEPS, "Step 27\n");

	tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
	emc_ग_लिखोl(emc, next->burst_regs[EMC_CFG_INDEX], EMC_CFG);
	tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);
	emc_ग_लिखोl(emc, next->emc_fdpd_ctrl_cmd_no_ramp,
		   EMC_FDPD_CTRL_CMD_NO_RAMP);
	emc_ग_लिखोl(emc, next->emc_sel_dpd_ctrl, EMC_SEL_DPD_CTRL);

	/*
	 * Step 28:
	 *   Training recover. Removed.
	 */
	emc_dbg(emc, STEPS, "Step 28\n");

	tegra210_emc_set_shaकरोw_bypass(emc, ACTIVE);
	emc_ग_लिखोl(emc,
		   next->burst_regs[EMC_PMACRO_AUTOCAL_CFG_COMMON_INDEX],
		   EMC_PMACRO_AUTOCAL_CFG_COMMON);
	tegra210_emc_set_shaकरोw_bypass(emc, ASSEMBLY);

	/*
	 * Step 29:
	 *   Power fix WAR.
	 */
	emc_dbg(emc, STEPS, "Step 29\n");

	emc_ग_लिखोl(emc, EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE0 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE1 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE2 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE3 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE4 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE5 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE6 |
		   EMC_PMACRO_CFG_PM_GLOBAL_0_DISABLE_CFG_BYTE7,
		   EMC_PMACRO_CFG_PM_GLOBAL_0);
	emc_ग_लिखोl(emc, EMC_PMACRO_TRAINING_CTRL_0_CH0_TRAINING_E_WRPTR,
		   EMC_PMACRO_TRAINING_CTRL_0);
	emc_ग_लिखोl(emc, EMC_PMACRO_TRAINING_CTRL_1_CH1_TRAINING_E_WRPTR,
		   EMC_PMACRO_TRAINING_CTRL_1);
	emc_ग_लिखोl(emc, 0, EMC_PMACRO_CFG_PM_GLOBAL_0);

	/*
	 * Step 30:
	 *   Re-enable स्वतःcal.
	 */
	emc_dbg(emc, STEPS, "Step 30: Re-enable DLL and AUTOCAL\n");

	अगर (next->burst_regs[EMC_CFG_DIG_DLL_INDEX] & EMC_CFG_DIG_DLL_CFG_DLL_EN) अणु
		value = emc_पढ़ोl(emc, EMC_CFG_DIG_DLL);
		value |=  EMC_CFG_DIG_DLL_CFG_DLL_STALL_ALL_TRAFFIC;
		value |=  EMC_CFG_DIG_DLL_CFG_DLL_EN;
		value &= ~EMC_CFG_DIG_DLL_CFG_DLL_STALL_RW_UNTIL_LOCK;
		value &= ~EMC_CFG_DIG_DLL_CFG_DLL_STALL_ALL_UNTIL_LOCK;
		value = (value & ~EMC_CFG_DIG_DLL_CFG_DLL_MODE_MASK) |
			(2 << EMC_CFG_DIG_DLL_CFG_DLL_MODE_SHIFT);
		emc_ग_लिखोl(emc, value, EMC_CFG_DIG_DLL);
		tegra210_emc_timing_update(emc);
	पूर्ण

	emc_ग_लिखोl(emc, next->emc_स्वतः_cal_config, EMC_AUTO_CAL_CONFIG);

	/* Done! Yay. */
पूर्ण

स्थिर काष्ठा tegra210_emc_sequence tegra210_emc_r21021 = अणु
	.revision = 0x7,
	.set_घड़ी = tegra210_emc_r21021_set_घड़ी,
	.periodic_compensation = tegra210_emc_r21021_periodic_compensation,
पूर्ण;
