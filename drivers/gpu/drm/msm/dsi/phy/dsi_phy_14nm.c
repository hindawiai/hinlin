<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>

#समावेश "dsi_phy.h"
#समावेश "dsi.xml.h"

#घोषणा PHY_14NM_CKLN_IDX	4

/*
 * DSI PLL 14nm - घड़ी diagram (eg: DSI0):
 *
 *         dsi0n1_postभाग_clk
 *                         |
 *                         |
 *                 +----+  |  +----+
 *  dsi0vco_clk ---| n1 |--o--| /8 |-- dsi0pllbyte
 *                 +----+  |  +----+
 *                         |           dsi0n1_postभागby2_clk
 *                         |   +----+  |
 *                         o---| /2 |--o--|\
 *                         |   +----+     | \   +----+
 *                         |              |  |--| n2 |-- dsi0pll
 *                         o--------------| /   +----+
 *                                        |/
 */

#घोषणा POLL_MAX_READS			15
#घोषणा POLL_TIMEOUT_US			1000

#घोषणा VCO_REF_CLK_RATE		19200000
#घोषणा VCO_MIN_RATE			1300000000UL
#घोषणा VCO_MAX_RATE			2600000000UL

काष्ठा dsi_pll_config अणु
	u64 vco_current_rate;

	u32 ssc_en;	/* SSC enable/disable */

	/* fixed params */
	u32 plllock_cnt;
	u32 ssc_center;
	u32 ssc_adj_period;
	u32 ssc_spपढ़ो;
	u32 ssc_freq;

	/* calculated */
	u32 dec_start;
	u32 भाग_frac_start;
	u32 ssc_period;
	u32 ssc_step_size;
	u32 plllock_cmp;
	u32 pll_vco_भाग_ref;
	u32 pll_vco_count;
	u32 pll_kvco_भाग_ref;
	u32 pll_kvco_count;
पूर्ण;

काष्ठा pll_14nm_cached_state अणु
	अचिन्हित दीर्घ vco_rate;
	u8 n2postभाग;
	u8 n1postभाग;
पूर्ण;

काष्ठा dsi_pll_14nm अणु
	काष्ठा clk_hw clk_hw;

	काष्ठा msm_dsi_phy *phy;

	/* protects REG_DSI_14nm_PHY_CMN_CLK_CFG0 रेजिस्टर */
	spinlock_t postभाग_lock;

	काष्ठा pll_14nm_cached_state cached_state;

	काष्ठा dsi_pll_14nm *slave;
पूर्ण;

#घोषणा to_pll_14nm(x)	container_of(x, काष्ठा dsi_pll_14nm, clk_hw)

/*
 * Private काष्ठा क्रम N1/N2 post-भागider घड़ीs. These घड़ीs are similar to
 * the generic clk_भागider class of घड़ीs. The only dअगरference is that it
 * also sets the slave DSI PLL's post-भागiders अगर in Dual DSI mode
 */
काष्ठा dsi_pll_14nm_postभाग अणु
	काष्ठा clk_hw hw;

	/* भागider params */
	u8 shअगरt;
	u8 width;
	u8 flags; /* same flags as used by clk_भागider काष्ठा */

	काष्ठा dsi_pll_14nm *pll;
पूर्ण;

#घोषणा to_pll_14nm_postभाग(_hw) container_of(_hw, काष्ठा dsi_pll_14nm_postभाग, hw)

/*
 * Global list of निजी DSI PLL काष्ठा poपूर्णांकers. We need this क्रम Dual DSI
 * mode, where the master PLL's clk_ops needs access the slave's निजी data
 */
अटल काष्ठा dsi_pll_14nm *pll_14nm_list[DSI_MAX];

अटल bool pll_14nm_poll_क्रम_पढ़ोy(काष्ठा dsi_pll_14nm *pll_14nm,
				    u32 nb_tries, u32 समयout_us)
अणु
	bool pll_locked = false;
	व्योम __iomem *base = pll_14nm->phy->pll_base;
	u32 tries, val;

	tries = nb_tries;
	जबतक (tries--) अणु
		val = dsi_phy_पढ़ो(base +
			       REG_DSI_14nm_PHY_PLL_RESET_SM_READY_STATUS);
		pll_locked = !!(val & BIT(5));

		अगर (pll_locked)
			अवरोध;

		udelay(समयout_us);
	पूर्ण

	अगर (!pll_locked) अणु
		tries = nb_tries;
		जबतक (tries--) अणु
			val = dsi_phy_पढ़ो(base +
				REG_DSI_14nm_PHY_PLL_RESET_SM_READY_STATUS);
			pll_locked = !!(val & BIT(0));

			अगर (pll_locked)
				अवरोध;

			udelay(समयout_us);
		पूर्ण
	पूर्ण

	DBG("DSI PLL is %slocked", pll_locked ? "" : "*not* ");

	वापस pll_locked;
पूर्ण

अटल व्योम dsi_pll_14nm_config_init(काष्ठा dsi_pll_config *pconf)
अणु
	/* fixed input */
	pconf->plllock_cnt = 1;

	/*
	 * SSC is enabled by शेष. We might need DT props क्रम configuring
	 * some SSC params like PPM and center/करोwn spपढ़ो etc.
	 */
	pconf->ssc_en = 1;
	pconf->ssc_center = 0;		/* करोwn spपढ़ो by शेष */
	pconf->ssc_spपढ़ो = 5;		/* PPM / 1000 */
	pconf->ssc_freq = 31500;	/* शेष recommended */
	pconf->ssc_adj_period = 37;
पूर्ण

#घोषणा CEIL(x, y)		(((x) + ((y) - 1)) / (y))

अटल व्योम pll_14nm_ssc_calc(काष्ठा dsi_pll_14nm *pll, काष्ठा dsi_pll_config *pconf)
अणु
	u32 period, ssc_period;
	u32 ref, rem;
	u64 step_size;

	DBG("vco=%lld ref=%d", pconf->vco_current_rate, VCO_REF_CLK_RATE);

	ssc_period = pconf->ssc_freq / 500;
	period = (u32)VCO_REF_CLK_RATE / 1000;
	ssc_period  = CEIL(period, ssc_period);
	ssc_period -= 1;
	pconf->ssc_period = ssc_period;

	DBG("ssc freq=%d spread=%d period=%d", pconf->ssc_freq,
	    pconf->ssc_spपढ़ो, pconf->ssc_period);

	step_size = (u32)pconf->vco_current_rate;
	ref = VCO_REF_CLK_RATE;
	ref /= 1000;
	step_size = भाग_u64(step_size, ref);
	step_size <<= 20;
	step_size = भाग_u64(step_size, 1000);
	step_size *= pconf->ssc_spपढ़ो;
	step_size = भाग_u64(step_size, 1000);
	step_size *= (pconf->ssc_adj_period + 1);

	rem = 0;
	step_size = भाग_u64_rem(step_size, ssc_period + 1, &rem);
	अगर (rem)
		step_size++;

	DBG("step_size=%lld", step_size);

	step_size &= 0x0ffff;	/* take lower 16 bits */

	pconf->ssc_step_size = step_size;
पूर्ण

अटल व्योम pll_14nm_dec_frac_calc(काष्ठा dsi_pll_14nm *pll, काष्ठा dsi_pll_config *pconf)
अणु
	u64 multiplier = BIT(20);
	u64 dec_start_multiple, dec_start, pll_comp_val;
	u32 duration, भाग_frac_start;
	u64 vco_clk_rate = pconf->vco_current_rate;
	u64 fref = VCO_REF_CLK_RATE;

	DBG("vco_clk_rate=%lld ref_clk_rate=%lld", vco_clk_rate, fref);

	dec_start_multiple = भाग_u64(vco_clk_rate * multiplier, fref);
	भाग_u64_rem(dec_start_multiple, multiplier, &भाग_frac_start);

	dec_start = भाग_u64(dec_start_multiple, multiplier);

	pconf->dec_start = (u32)dec_start;
	pconf->भाग_frac_start = भाग_frac_start;

	अगर (pconf->plllock_cnt == 0)
		duration = 1024;
	अन्यथा अगर (pconf->plllock_cnt == 1)
		duration = 256;
	अन्यथा अगर (pconf->plllock_cnt == 2)
		duration = 128;
	अन्यथा
		duration = 32;

	pll_comp_val = duration * dec_start_multiple;
	pll_comp_val = भाग_u64(pll_comp_val, multiplier);
	करो_भाग(pll_comp_val, 10);

	pconf->plllock_cmp = (u32)pll_comp_val;
पूर्ण

अटल u32 pll_14nm_kvco_slop(u32 vrate)
अणु
	u32 slop = 0;

	अगर (vrate > VCO_MIN_RATE && vrate <= 1800000000UL)
		slop =  600;
	अन्यथा अगर (vrate > 1800000000UL && vrate < 2300000000UL)
		slop = 400;
	अन्यथा अगर (vrate > 2300000000UL && vrate < VCO_MAX_RATE)
		slop = 280;

	वापस slop;
पूर्ण

अटल व्योम pll_14nm_calc_vco_count(काष्ठा dsi_pll_14nm *pll, काष्ठा dsi_pll_config *pconf)
अणु
	u64 vco_clk_rate = pconf->vco_current_rate;
	u64 fref = VCO_REF_CLK_RATE;
	u32 vco_measure_समय = 5;
	u32 kvco_measure_समय = 5;
	u64 data;
	u32 cnt;

	data = fref * vco_measure_समय;
	करो_भाग(data, 1000000);
	data &= 0x03ff;	/* 10 bits */
	data -= 2;
	pconf->pll_vco_भाग_ref = data;

	data = भाग_u64(vco_clk_rate, 1000000);	/* unit is Mhz */
	data *= vco_measure_समय;
	करो_भाग(data, 10);
	pconf->pll_vco_count = data;

	data = fref * kvco_measure_समय;
	करो_भाग(data, 1000000);
	data &= 0x03ff;	/* 10 bits */
	data -= 1;
	pconf->pll_kvco_भाग_ref = data;

	cnt = pll_14nm_kvco_slop(vco_clk_rate);
	cnt *= 2;
	cnt /= 100;
	cnt *= kvco_measure_समय;
	pconf->pll_kvco_count = cnt;
पूर्ण

अटल व्योम pll_db_commit_ssc(काष्ठा dsi_pll_14nm *pll, काष्ठा dsi_pll_config *pconf)
अणु
	व्योम __iomem *base = pll->phy->pll_base;
	u8 data;

	data = pconf->ssc_adj_period;
	data &= 0x0ff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_ADJ_PER1, data);
	data = (pconf->ssc_adj_period >> 8);
	data &= 0x03;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_ADJ_PER2, data);

	data = pconf->ssc_period;
	data &= 0x0ff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_PER1, data);
	data = (pconf->ssc_period >> 8);
	data &= 0x0ff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_PER2, data);

	data = pconf->ssc_step_size;
	data &= 0x0ff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_STEP_SIZE1, data);
	data = (pconf->ssc_step_size >> 8);
	data &= 0x0ff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_STEP_SIZE2, data);

	data = (pconf->ssc_center & 0x01);
	data <<= 1;
	data |= 0x01; /* enable */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SSC_EN_CENTER, data);

	wmb();	/* make sure रेजिस्टर committed */
पूर्ण

अटल व्योम pll_db_commit_common(काष्ठा dsi_pll_14nm *pll,
				 काष्ठा dsi_pll_config *pconf)
अणु
	व्योम __iomem *base = pll->phy->pll_base;
	u8 data;

	/* confgiure the non frequency dependent pll रेजिस्टरs */
	data = 0;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_SYSCLK_EN_RESET, data);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_TXCLK_EN, 1);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_RESETSM_CNTRL, 48);
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_RESETSM_CNTRL2, 4 << 3); /* bandgap_समयr */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_RESETSM_CNTRL5, 5); /* pll_wakeup_समयr */

	data = pconf->pll_vco_भाग_ref & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_VCO_DIV_REF1, data);
	data = (pconf->pll_vco_भाग_ref >> 8) & 0x3;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_VCO_DIV_REF2, data);

	data = pconf->pll_kvco_भाग_ref & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_KVCO_DIV_REF1, data);
	data = (pconf->pll_kvco_भाग_ref >> 8) & 0x3;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_KVCO_DIV_REF2, data);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_MISC1, 16);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_IE_TRIM, 4);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_IP_TRIM, 4);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_CP_SET_CUR, 1 << 3 | 1);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_ICPCSET, 0 << 3 | 0);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_ICPMSET, 0 << 3 | 0);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_ICP_SET, 4 << 3 | 4);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_LPF1, 1 << 4 | 11);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_IPTAT_TRIM, 7);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_CRCTRL, 1 << 4 | 2);
पूर्ण

अटल व्योम pll_14nm_software_reset(काष्ठा dsi_pll_14nm *pll_14nm)
अणु
	व्योम __iomem *cmn_base = pll_14nm->phy->base;

	/* de निश्चित pll start and apply pll sw reset */

	/* stop pll */
	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_PLL_CNTRL, 0);

	/* pll sw reset */
	dsi_phy_ग_लिखो_udelay(cmn_base + REG_DSI_14nm_PHY_CMN_CTRL_1, 0x20, 10);
	wmb();	/* make sure रेजिस्टर committed */

	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_CTRL_1, 0);
	wmb();	/* make sure रेजिस्टर committed */
पूर्ण

अटल व्योम pll_db_commit_14nm(काष्ठा dsi_pll_14nm *pll,
			       काष्ठा dsi_pll_config *pconf)
अणु
	व्योम __iomem *base = pll->phy->pll_base;
	व्योम __iomem *cmn_base = pll->phy->base;
	u8 data;

	DBG("DSI%d PLL", pll->phy->id);

	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_LDO_CNTRL, 0x3c);

	pll_db_commit_common(pll, pconf);

	pll_14nm_software_reset(pll);

	/* Use the /2 path in Mux */
	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_CLK_CFG1, 1);

	data = 0xff; /* data, clk, pll normal operation */
	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_CTRL_0, data);

	/* configure the frequency dependent pll रेजिस्टरs */
	data = pconf->dec_start;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_DEC_START, data);

	data = pconf->भाग_frac_start & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_DIV_FRAC_START1, data);
	data = (pconf->भाग_frac_start >> 8) & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_DIV_FRAC_START2, data);
	data = (pconf->भाग_frac_start >> 16) & 0xf;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_DIV_FRAC_START3, data);

	data = pconf->plllock_cmp & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLLLOCK_CMP1, data);

	data = (pconf->plllock_cmp >> 8) & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLLLOCK_CMP2, data);

	data = (pconf->plllock_cmp >> 16) & 0x3;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLLLOCK_CMP3, data);

	data = pconf->plllock_cnt << 1 | 0 << 3; /* plllock_rng */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLLLOCK_CMP_EN, data);

	data = pconf->pll_vco_count & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_VCO_COUNT1, data);
	data = (pconf->pll_vco_count >> 8) & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_VCO_COUNT2, data);

	data = pconf->pll_kvco_count & 0xff;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_KVCO_COUNT1, data);
	data = (pconf->pll_kvco_count >> 8) & 0x3;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_KVCO_COUNT2, data);

	/*
	 * High nibble configures the post भागider पूर्णांकernal to the VCO. It's
	 * fixed to भागide by 1 क्रम now.
	 *
	 * 0: भागided by 1
	 * 1: भागided by 2
	 * 2: भागided by 4
	 * 3: भागided by 8
	 */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_LPF2_POSTDIV, 0 << 4 | 3);

	अगर (pconf->ssc_en)
		pll_db_commit_ssc(pll, pconf);

	wmb();	/* make sure रेजिस्टर committed */
पूर्ण

/*
 * VCO घड़ी Callbacks
 */
अटल पूर्णांक dsi_pll_14nm_vco_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(hw);
	काष्ठा dsi_pll_config conf;

	DBG("DSI PLL%d rate=%lu, parent's=%lu", pll_14nm->phy->id, rate,
	    parent_rate);

	dsi_pll_14nm_config_init(&conf);
	conf.vco_current_rate = rate;

	pll_14nm_dec_frac_calc(pll_14nm, &conf);

	अगर (conf.ssc_en)
		pll_14nm_ssc_calc(pll_14nm, &conf);

	pll_14nm_calc_vco_count(pll_14nm, &conf);

	/* commit the slave DSI PLL रेजिस्टरs अगर we're master. Note that we
	 * करोn't lock the slave PLL. We just ensure that the PLL/PHY रेजिस्टरs
	 * of the master and slave are identical
	 */
	अगर (pll_14nm->phy->useहाल == MSM_DSI_PHY_MASTER) अणु
		काष्ठा dsi_pll_14nm *pll_14nm_slave = pll_14nm->slave;

		pll_db_commit_14nm(pll_14nm_slave, &conf);
	पूर्ण

	pll_db_commit_14nm(pll_14nm, &conf);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ dsi_pll_14nm_vco_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(hw);
	व्योम __iomem *base = pll_14nm->phy->pll_base;
	u64 vco_rate, multiplier = BIT(20);
	u32 भाग_frac_start;
	u32 dec_start;
	u64 ref_clk = parent_rate;

	dec_start = dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_PLL_DEC_START);
	dec_start &= 0x0ff;

	DBG("dec_start = %x", dec_start);

	भाग_frac_start = (dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_PLL_DIV_FRAC_START3)
				& 0xf) << 16;
	भाग_frac_start |= (dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_PLL_DIV_FRAC_START2)
				& 0xff) << 8;
	भाग_frac_start |= dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_PLL_DIV_FRAC_START1)
				& 0xff;

	DBG("div_frac_start = %x", भाग_frac_start);

	vco_rate = ref_clk * dec_start;

	vco_rate += ((ref_clk * भाग_frac_start) / multiplier);

	/*
	 * Recalculating the rate from dec_start and frac_start करोesn't end up
	 * the rate we originally set. Convert the freq to KHz, round it up and
	 * convert it back to MHz.
	 */
	vco_rate = DIV_ROUND_UP_ULL(vco_rate, 1000) * 1000;

	DBG("returning vco rate = %lu", (अचिन्हित दीर्घ)vco_rate);

	वापस (अचिन्हित दीर्घ)vco_rate;
पूर्ण

अटल पूर्णांक dsi_pll_14nm_vco_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(hw);
	व्योम __iomem *base = pll_14nm->phy->pll_base;
	व्योम __iomem *cmn_base = pll_14nm->phy->base;
	bool locked;

	DBG("");

	अगर (unlikely(pll_14nm->phy->pll_on))
		वापस 0;

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_VREF_CFG1, 0x10);
	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_PLL_CNTRL, 1);

	locked = pll_14nm_poll_क्रम_पढ़ोy(pll_14nm, POLL_MAX_READS,
					 POLL_TIMEOUT_US);

	अगर (unlikely(!locked)) अणु
		DRM_DEV_ERROR(&pll_14nm->phy->pdev->dev, "DSI PLL lock failed\n");
		वापस -EINVAL;
	पूर्ण

	DBG("DSI PLL lock success");
	pll_14nm->phy->pll_on = true;

	वापस 0;
पूर्ण

अटल व्योम dsi_pll_14nm_vco_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(hw);
	व्योम __iomem *cmn_base = pll_14nm->phy->base;

	DBG("");

	अगर (unlikely(!pll_14nm->phy->pll_on))
		वापस;

	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_PLL_CNTRL, 0);

	pll_14nm->phy->pll_on = false;
पूर्ण

अटल दीर्घ dsi_pll_14nm_clk_round_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(hw);

	अगर      (rate < pll_14nm->phy->cfg->min_pll_rate)
		वापस  pll_14nm->phy->cfg->min_pll_rate;
	अन्यथा अगर (rate > pll_14nm->phy->cfg->max_pll_rate)
		वापस  pll_14nm->phy->cfg->max_pll_rate;
	अन्यथा
		वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ops_dsi_pll_14nm_vco = अणु
	.round_rate = dsi_pll_14nm_clk_round_rate,
	.set_rate = dsi_pll_14nm_vco_set_rate,
	.recalc_rate = dsi_pll_14nm_vco_recalc_rate,
	.prepare = dsi_pll_14nm_vco_prepare,
	.unprepare = dsi_pll_14nm_vco_unprepare,
पूर्ण;

/*
 * N1 and N2 post-भागider घड़ी callbacks
 */
#घोषणा भाग_mask(width)	((1 << (width)) - 1)
अटल अचिन्हित दीर्घ dsi_pll_14nm_postभाग_recalc_rate(काष्ठा clk_hw *hw,
						      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_14nm_postभाग *postभाग = to_pll_14nm_postभाग(hw);
	काष्ठा dsi_pll_14nm *pll_14nm = postभाग->pll;
	व्योम __iomem *base = pll_14nm->phy->base;
	u8 shअगरt = postभाग->shअगरt;
	u8 width = postभाग->width;
	u32 val;

	DBG("DSI%d PLL parent rate=%lu", pll_14nm->phy->id, parent_rate);

	val = dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_CMN_CLK_CFG0) >> shअगरt;
	val &= भाग_mask(width);

	वापस भागider_recalc_rate(hw, parent_rate, val, शून्य,
				   postभाग->flags, width);
पूर्ण

अटल दीर्घ dsi_pll_14nm_postभाग_round_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ *prate)
अणु
	काष्ठा dsi_pll_14nm_postभाग *postभाग = to_pll_14nm_postभाग(hw);
	काष्ठा dsi_pll_14nm *pll_14nm = postभाग->pll;

	DBG("DSI%d PLL parent rate=%lu", pll_14nm->phy->id, rate);

	वापस भागider_round_rate(hw, rate, prate, शून्य,
				  postभाग->width,
				  postभाग->flags);
पूर्ण

अटल पूर्णांक dsi_pll_14nm_postभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_14nm_postभाग *postभाग = to_pll_14nm_postभाग(hw);
	काष्ठा dsi_pll_14nm *pll_14nm = postभाग->pll;
	व्योम __iomem *base = pll_14nm->phy->base;
	spinlock_t *lock = &pll_14nm->postभाग_lock;
	u8 shअगरt = postभाग->shअगरt;
	u8 width = postभाग->width;
	अचिन्हित पूर्णांक value;
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	DBG("DSI%d PLL parent rate=%lu parent rate %lu", pll_14nm->phy->id, rate,
	    parent_rate);

	value = भागider_get_val(rate, parent_rate, शून्य, postभाग->width,
				postभाग->flags);

	spin_lock_irqsave(lock, flags);

	val = dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_CMN_CLK_CFG0);
	val &= ~(भाग_mask(width) << shअगरt);

	val |= value << shअगरt;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_CLK_CFG0, val);

	/* If we're master in dual DSI mode, then the slave PLL's post-भागiders
	 * follow the master's post भागiders
	 */
	अगर (pll_14nm->phy->useहाल == MSM_DSI_PHY_MASTER) अणु
		काष्ठा dsi_pll_14nm *pll_14nm_slave = pll_14nm->slave;
		व्योम __iomem *slave_base = pll_14nm_slave->phy->base;

		dsi_phy_ग_लिखो(slave_base + REG_DSI_14nm_PHY_CMN_CLK_CFG0, val);
	पूर्ण

	spin_unlock_irqrestore(lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ops_dsi_pll_14nm_postभाग = अणु
	.recalc_rate = dsi_pll_14nm_postभाग_recalc_rate,
	.round_rate = dsi_pll_14nm_postभाग_round_rate,
	.set_rate = dsi_pll_14nm_postभाग_set_rate,
पूर्ण;

/*
 * PLL Callbacks
 */

अटल व्योम dsi_14nm_pll_save_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(phy->vco_hw);
	काष्ठा pll_14nm_cached_state *cached_state = &pll_14nm->cached_state;
	व्योम __iomem *cmn_base = pll_14nm->phy->base;
	u32 data;

	data = dsi_phy_पढ़ो(cmn_base + REG_DSI_14nm_PHY_CMN_CLK_CFG0);

	cached_state->n1postभाग = data & 0xf;
	cached_state->n2postभाग = (data >> 4) & 0xf;

	DBG("DSI%d PLL save state %x %x", pll_14nm->phy->id,
	    cached_state->n1postभाग, cached_state->n2postभाग);

	cached_state->vco_rate = clk_hw_get_rate(phy->vco_hw);
पूर्ण

अटल पूर्णांक dsi_14nm_pll_restore_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(phy->vco_hw);
	काष्ठा pll_14nm_cached_state *cached_state = &pll_14nm->cached_state;
	व्योम __iomem *cmn_base = pll_14nm->phy->base;
	u32 data;
	पूर्णांक ret;

	ret = dsi_pll_14nm_vco_set_rate(phy->vco_hw,
					cached_state->vco_rate, 0);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pll_14nm->phy->pdev->dev,
			"restore vco rate failed. ret=%d\n", ret);
		वापस ret;
	पूर्ण

	data = cached_state->n1postभाग | (cached_state->n2postभाग << 4);

	DBG("DSI%d PLL restore state %x %x", pll_14nm->phy->id,
	    cached_state->n1postभाग, cached_state->n2postभाग);

	dsi_phy_ग_लिखो(cmn_base + REG_DSI_14nm_PHY_CMN_CLK_CFG0, data);

	/* also restore post-भागiders क्रम slave DSI PLL */
	अगर (phy->useहाल == MSM_DSI_PHY_MASTER) अणु
		काष्ठा dsi_pll_14nm *pll_14nm_slave = pll_14nm->slave;
		व्योम __iomem *slave_base = pll_14nm_slave->phy->base;

		dsi_phy_ग_लिखो(slave_base + REG_DSI_14nm_PHY_CMN_CLK_CFG0, data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_14nm_set_useहाल(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_14nm *pll_14nm = to_pll_14nm(phy->vco_hw);
	व्योम __iomem *base = phy->pll_base;
	u32 clkbuflr_en, bandgap = 0;

	चयन (phy->useहाल) अणु
	हाल MSM_DSI_PHY_STANDALONE:
		clkbuflr_en = 0x1;
		अवरोध;
	हाल MSM_DSI_PHY_MASTER:
		clkbuflr_en = 0x3;
		pll_14nm->slave = pll_14nm_list[(pll_14nm->phy->id + 1) % DSI_MAX];
		अवरोध;
	हाल MSM_DSI_PHY_SLAVE:
		clkbuflr_en = 0x0;
		bandgap = 0x3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_CLKBUFLR_EN, clkbuflr_en);
	अगर (bandgap)
		dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_PLL_PLL_BANDGAP, bandgap);

	वापस 0;
पूर्ण

अटल काष्ठा clk_hw *pll_14nm_postभाग_रेजिस्टर(काष्ठा dsi_pll_14nm *pll_14nm,
						स्थिर अक्षर *name,
						स्थिर अक्षर *parent_name,
						अचिन्हित दीर्घ flags,
						u8 shअगरt)
अणु
	काष्ठा dsi_pll_14nm_postभाग *pll_postभाग;
	काष्ठा device *dev = &pll_14nm->phy->pdev->dev;
	काष्ठा clk_init_data postभाग_init = अणु
		.parent_names = (स्थिर अक्षर *[]) अणु parent_name पूर्ण,
		.num_parents = 1,
		.name = name,
		.flags = flags,
		.ops = &clk_ops_dsi_pll_14nm_postभाग,
	पूर्ण;
	पूर्णांक ret;

	pll_postभाग = devm_kzalloc(dev, माप(*pll_postभाग), GFP_KERNEL);
	अगर (!pll_postभाग)
		वापस ERR_PTR(-ENOMEM);

	pll_postभाग->pll = pll_14nm;
	pll_postभाग->shअगरt = shअगरt;
	/* both N1 and N2 postभागiders are 4 bits wide */
	pll_postभाग->width = 4;
	/* range of each भागider is from 1 to 15 */
	pll_postभाग->flags = CLK_DIVIDER_ONE_BASED;
	pll_postभाग->hw.init = &postभाग_init;

	ret = devm_clk_hw_रेजिस्टर(dev, &pll_postभाग->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &pll_postभाग->hw;
पूर्ण

अटल पूर्णांक pll_14nm_रेजिस्टर(काष्ठा dsi_pll_14nm *pll_14nm, काष्ठा clk_hw **provided_घड़ीs)
अणु
	अक्षर clk_name[32], parent[32], vco_name[32];
	काष्ठा clk_init_data vco_init = अणु
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.name = vco_name,
		.flags = CLK_IGNORE_UNUSED,
		.ops = &clk_ops_dsi_pll_14nm_vco,
	पूर्ण;
	काष्ठा device *dev = &pll_14nm->phy->pdev->dev;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	DBG("DSI%d", pll_14nm->phy->id);

	snम_लिखो(vco_name, 32, "dsi%dvco_clk", pll_14nm->phy->id);
	pll_14nm->clk_hw.init = &vco_init;

	ret = devm_clk_hw_रेजिस्टर(dev, &pll_14nm->clk_hw);
	अगर (ret)
		वापस ret;

	snम_लिखो(clk_name, 32, "dsi%dn1_postdiv_clk", pll_14nm->phy->id);
	snम_लिखो(parent, 32, "dsi%dvco_clk", pll_14nm->phy->id);

	/* N1 postभाग, bits 0-3 in REG_DSI_14nm_PHY_CMN_CLK_CFG0 */
	hw = pll_14nm_postभाग_रेजिस्टर(pll_14nm, clk_name, parent,
				       CLK_SET_RATE_PARENT, 0);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	snम_लिखो(clk_name, 32, "dsi%dpllbyte", pll_14nm->phy->id);
	snम_लिखो(parent, 32, "dsi%dn1_postdiv_clk", pll_14nm->phy->id);

	/* DSI Byte घड़ी = VCO_CLK / N1 / 8 */
	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name, parent,
					  CLK_SET_RATE_PARENT, 1, 8);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	provided_घड़ीs[DSI_BYTE_PLL_CLK] = hw;

	snम_लिखो(clk_name, 32, "dsi%dn1_postdivby2_clk", pll_14nm->phy->id);
	snम_लिखो(parent, 32, "dsi%dn1_postdiv_clk", pll_14nm->phy->id);

	/*
	 * Skip the mux क्रम now, क्रमce DSICLK_SEL to 1, Add a /2 भागider
	 * on the way. Don't let it set parent.
	 */
	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name, parent, 0, 1, 2);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	snम_लिखो(clk_name, 32, "dsi%dpll", pll_14nm->phy->id);
	snम_लिखो(parent, 32, "dsi%dn1_postdivby2_clk", pll_14nm->phy->id);

	/* DSI pixel घड़ी = VCO_CLK / N1 / 2 / N2
	 * This is the output of N2 post-भागider, bits 4-7 in
	 * REG_DSI_14nm_PHY_CMN_CLK_CFG0. Don't let it set parent.
	 */
	hw = pll_14nm_postभाग_रेजिस्टर(pll_14nm, clk_name, parent, 0, 4);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	provided_घड़ीs[DSI_PIXEL_PLL_CLK]	= hw;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_pll_14nm_init(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा platक्रमm_device *pdev = phy->pdev;
	काष्ठा dsi_pll_14nm *pll_14nm;
	पूर्णांक ret;

	अगर (!pdev)
		वापस -ENODEV;

	pll_14nm = devm_kzalloc(&pdev->dev, माप(*pll_14nm), GFP_KERNEL);
	अगर (!pll_14nm)
		वापस -ENOMEM;

	DBG("PLL%d", phy->id);

	pll_14nm_list[phy->id] = pll_14nm;

	spin_lock_init(&pll_14nm->postभाग_lock);

	pll_14nm->phy = phy;

	ret = pll_14nm_रेजिस्टर(pll_14nm, phy->provided_घड़ीs->hws);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to register PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	phy->vco_hw = &pll_14nm->clk_hw;

	वापस 0;
पूर्ण

अटल व्योम dsi_14nm_dphy_set_timing(काष्ठा msm_dsi_phy *phy,
				     काष्ठा msm_dsi_dphy_timing *timing,
				     पूर्णांक lane_idx)
अणु
	व्योम __iomem *base = phy->lane_base;
	bool clk_ln = (lane_idx == PHY_14NM_CKLN_IDX);
	u32 zero = clk_ln ? timing->clk_zero : timing->hs_zero;
	u32 prepare = clk_ln ? timing->clk_prepare : timing->hs_prepare;
	u32 trail = clk_ln ? timing->clk_trail : timing->hs_trail;
	u32 rqst = clk_ln ? timing->hs_rqst_ckln : timing->hs_rqst;
	u32 prep_dly = clk_ln ? timing->hs_prep_dly_ckln : timing->hs_prep_dly;
	u32 halfbyte_en = clk_ln ? timing->hs_halfbyte_en_ckln :
				   timing->hs_halfbyte_en;

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_4(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_4_HS_EXIT(timing->hs_निकास));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_5(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_5_HS_ZERO(zero));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_6(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_6_HS_PREPARE(prepare));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_7(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_7_HS_TRAIL(trail));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_8(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_8_HS_RQST(rqst));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_CFG0(lane_idx),
		      DSI_14nm_PHY_LN_CFG0_PREPARE_DLY(prep_dly));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_CFG1(lane_idx),
		      halfbyte_en ? DSI_14nm_PHY_LN_CFG1_HALFBYTECLK_EN : 0);
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_9(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_9_TA_GO(timing->ta_go) |
		      DSI_14nm_PHY_LN_TIMING_CTRL_9_TA_SURE(timing->ta_sure));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_10(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_10_TA_GET(timing->ta_get));
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_LN_TIMING_CTRL_11(lane_idx),
		      DSI_14nm_PHY_LN_TIMING_CTRL_11_TRIG3_CMD(0xa0));
पूर्ण

अटल पूर्णांक dsi_14nm_phy_enable(काष्ठा msm_dsi_phy *phy,
			       काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	काष्ठा msm_dsi_dphy_timing *timing = &phy->timing;
	u32 data;
	पूर्णांक i;
	पूर्णांक ret;
	व्योम __iomem *base = phy->base;
	व्योम __iomem *lane_base = phy->lane_base;
	u32 glbl_test_ctrl;

	अगर (msm_dsi_dphy_timing_calc_v2(timing, clk_req)) अणु
		DRM_DEV_ERROR(&phy->pdev->dev,
			"%s: D-PHY timing calculation failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	data = 0x1c;
	अगर (phy->useहाल != MSM_DSI_PHY_STANDALONE)
		data |= DSI_14nm_PHY_CMN_LDO_CNTRL_VREG_CTRL(32);
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_LDO_CNTRL, data);

	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_GLBL_TEST_CTRL, 0x1);

	/* 4 data lanes + 1 clk lane configuration */
	क्रम (i = 0; i < 5; i++) अणु
		dsi_phy_ग_लिखो(lane_base + REG_DSI_14nm_PHY_LN_VREG_CNTRL(i),
			      0x1d);

		dsi_phy_ग_लिखो(lane_base +
			      REG_DSI_14nm_PHY_LN_STRENGTH_CTRL_0(i), 0xff);
		dsi_phy_ग_लिखो(lane_base +
			      REG_DSI_14nm_PHY_LN_STRENGTH_CTRL_1(i),
			      (i == PHY_14NM_CKLN_IDX) ? 0x00 : 0x06);

		dsi_phy_ग_लिखो(lane_base + REG_DSI_14nm_PHY_LN_CFG3(i),
			      (i == PHY_14NM_CKLN_IDX) ? 0x8f : 0x0f);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_14nm_PHY_LN_CFG2(i), 0x10);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_14nm_PHY_LN_TEST_DATAPATH(i),
			      0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_14nm_PHY_LN_TEST_STR(i),
			      0x88);

		dsi_14nm_dphy_set_timing(phy, timing, i);
	पूर्ण

	/* Make sure PLL is not start */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_PLL_CNTRL, 0x00);

	wmb(); /* make sure everything is written beक्रमe reset and enable */

	/* reset digital block */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_CTRL_1, 0x80);
	wmb(); /* ensure reset is निश्चितed */
	udelay(100);
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_CTRL_1, 0x00);

	glbl_test_ctrl = dsi_phy_पढ़ो(base + REG_DSI_14nm_PHY_CMN_GLBL_TEST_CTRL);
	अगर (phy->id == DSI_1 && phy->useहाल == MSM_DSI_PHY_SLAVE)
		glbl_test_ctrl |= DSI_14nm_PHY_CMN_GLBL_TEST_CTRL_BITCLK_HS_SEL;
	अन्यथा
		glbl_test_ctrl &= ~DSI_14nm_PHY_CMN_GLBL_TEST_CTRL_BITCLK_HS_SEL;
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_GLBL_TEST_CTRL, glbl_test_ctrl);
	ret = dsi_14nm_set_useहाल(phy);
	अगर (ret) अणु
		DRM_DEV_ERROR(&phy->pdev->dev, "%s: set pll usecase failed, %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Remove घातer करोwn from PLL and all lanes */
	dsi_phy_ग_लिखो(base + REG_DSI_14nm_PHY_CMN_CTRL_0, 0xff);

	वापस 0;
पूर्ण

अटल व्योम dsi_14nm_phy_disable(काष्ठा msm_dsi_phy *phy)
अणु
	dsi_phy_ग_लिखो(phy->base + REG_DSI_14nm_PHY_CMN_GLBL_TEST_CTRL, 0);
	dsi_phy_ग_लिखो(phy->base + REG_DSI_14nm_PHY_CMN_CTRL_0, 0);

	/* ensure that the phy is completely disabled */
	wmb();
पूर्ण

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_14nm_cfgs = अणु
	.has_phy_lane = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vcca", 17000, 32पूर्ण,
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_14nm_phy_enable,
		.disable = dsi_14nm_phy_disable,
		.pll_init = dsi_pll_14nm_init,
		.save_pll_state = dsi_14nm_pll_save_state,
		.restore_pll_state = dsi_14nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = VCO_MIN_RATE,
	.max_pll_rate = VCO_MAX_RATE,
	.io_start = अणु 0x994400, 0x996400 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_14nm_660_cfgs = अणु
	.has_phy_lane = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vcca", 17000, 32पूर्ण,
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_14nm_phy_enable,
		.disable = dsi_14nm_phy_disable,
		.pll_init = dsi_pll_14nm_init,
		.save_pll_state = dsi_14nm_pll_save_state,
		.restore_pll_state = dsi_14nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = VCO_MIN_RATE,
	.max_pll_rate = VCO_MAX_RATE,
	.io_start = अणु 0xc994400, 0xc996000 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;
