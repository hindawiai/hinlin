<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश "ccu_sdm.h"

bool ccu_sdm_helper_is_enabled(काष्ठा ccu_common *common,
			       काष्ठा ccu_sdm_पूर्णांकernal *sdm)
अणु
	अगर (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		वापस false;

	अगर (sdm->enable && !(पढ़ोl(common->base + common->reg) & sdm->enable))
		वापस false;

	वापस !!(पढ़ोl(common->base + sdm->tuning_reg) & sdm->tuning_enable);
पूर्ण

व्योम ccu_sdm_helper_enable(काष्ठा ccu_common *common,
			   काष्ठा ccu_sdm_पूर्णांकernal *sdm,
			   अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 reg;

	अगर (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		वापस;

	/* Set the pattern */
	क्रम (i = 0; i < sdm->table_size; i++)
		अगर (sdm->table[i].rate == rate)
			ग_लिखोl(sdm->table[i].pattern,
			       common->base + sdm->tuning_reg);

	/* Make sure SDM is enabled */
	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + sdm->tuning_reg);
	ग_लिखोl(reg | sdm->tuning_enable, common->base + sdm->tuning_reg);
	spin_unlock_irqrestore(common->lock, flags);

	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + common->reg);
	ग_लिखोl(reg | sdm->enable, common->base + common->reg);
	spin_unlock_irqrestore(common->lock, flags);
पूर्ण

व्योम ccu_sdm_helper_disable(काष्ठा ccu_common *common,
			    काष्ठा ccu_sdm_पूर्णांकernal *sdm)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		वापस;

	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + common->reg);
	ग_लिखोl(reg & ~sdm->enable, common->base + common->reg);
	spin_unlock_irqrestore(common->lock, flags);

	spin_lock_irqsave(common->lock, flags);
	reg = पढ़ोl(common->base + sdm->tuning_reg);
	ग_लिखोl(reg & ~sdm->tuning_enable, common->base + sdm->tuning_reg);
	spin_unlock_irqrestore(common->lock, flags);
पूर्ण

/*
 * Sigma delta modulation provides a way to करो fractional-N frequency
 * synthesis, in essence allowing the PLL to output any frequency
 * within its operational range. On earlier SoCs such as the A10/A20,
 * some PLLs support this. On later SoCs, all PLLs support this.
 *
 * The datasheets करो not explain what the "wave top" and "wave bottom"
 * parameters mean or करो, nor how to calculate the effective output
 * frequency. The only examples (and real world usage) are क्रम the audio
 * PLL to generate 24.576 and 22.5792 MHz घड़ी rates used by the audio
 * peripherals. The author lacks the underlying करोमुख्य knowledge to
 * pursue this.
 *
 * The goal and function of the following code is to support the two
 * घड़ी rates used by the audio subप्रणाली, allowing क्रम proper audio
 * playback and capture without any pitch or speed changes.
 */
bool ccu_sdm_helper_has_rate(काष्ठा ccu_common *common,
			     काष्ठा ccu_sdm_पूर्णांकernal *sdm,
			     अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		वापस false;

	क्रम (i = 0; i < sdm->table_size; i++)
		अगर (sdm->table[i].rate == rate)
			वापस true;

	वापस false;
पूर्ण

अचिन्हित दीर्घ ccu_sdm_helper_पढ़ो_rate(काष्ठा ccu_common *common,
				       काष्ठा ccu_sdm_पूर्णांकernal *sdm,
				       u32 m, u32 n)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;

	pr_debug("%s: Read sigma-delta modulation setting\n",
		 clk_hw_get_name(&common->hw));

	अगर (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		वापस 0;

	pr_debug("%s: clock is sigma-delta modulated\n",
		 clk_hw_get_name(&common->hw));

	reg = पढ़ोl(common->base + sdm->tuning_reg);

	pr_debug("%s: pattern reg is 0x%x",
		 clk_hw_get_name(&common->hw), reg);

	क्रम (i = 0; i < sdm->table_size; i++)
		अगर (sdm->table[i].pattern == reg &&
		    sdm->table[i].m == m && sdm->table[i].n == n)
			वापस sdm->table[i].rate;

	/* We can't calculate the effective घड़ी rate, so just fail. */
	वापस 0;
पूर्ण

पूर्णांक ccu_sdm_helper_get_factors(काष्ठा ccu_common *common,
			       काष्ठा ccu_sdm_पूर्णांकernal *sdm,
			       अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *m, अचिन्हित दीर्घ *n)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		वापस -EINVAL;

	क्रम (i = 0; i < sdm->table_size; i++)
		अगर (sdm->table[i].rate == rate) अणु
			*m = sdm->table[i].m;
			*n = sdm->table[i].n;
			वापस 0;
		पूर्ण

	/* nothing found */
	वापस -EINVAL;
पूर्ण
