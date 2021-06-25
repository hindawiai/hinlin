<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tegra20 External Memory Controller driver
 *
 * Author: Dmitry Osipenko <digetx@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/types.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/fuse.h>

#समावेश "mc.h"

#घोषणा EMC_INTSTATUS				0x000
#घोषणा EMC_INTMASK				0x004
#घोषणा EMC_DBG					0x008
#घोषणा EMC_TIMING_CONTROL			0x028
#घोषणा EMC_RC					0x02c
#घोषणा EMC_RFC					0x030
#घोषणा EMC_RAS					0x034
#घोषणा EMC_RP					0x038
#घोषणा EMC_R2W					0x03c
#घोषणा EMC_W2R					0x040
#घोषणा EMC_R2P					0x044
#घोषणा EMC_W2P					0x048
#घोषणा EMC_RD_RCD				0x04c
#घोषणा EMC_WR_RCD				0x050
#घोषणा EMC_RRD					0x054
#घोषणा EMC_REXT				0x058
#घोषणा EMC_WDV					0x05c
#घोषणा EMC_QUSE				0x060
#घोषणा EMC_QRST				0x064
#घोषणा EMC_QSAFE				0x068
#घोषणा EMC_RDV					0x06c
#घोषणा EMC_REFRESH				0x070
#घोषणा EMC_BURST_REFRESH_NUM			0x074
#घोषणा EMC_PDEX2WR				0x078
#घोषणा EMC_PDEX2RD				0x07c
#घोषणा EMC_PCHG2PDEN				0x080
#घोषणा EMC_ACT2PDEN				0x084
#घोषणा EMC_AR2PDEN				0x088
#घोषणा EMC_RW2PDEN				0x08c
#घोषणा EMC_TXSR				0x090
#घोषणा EMC_TCKE				0x094
#घोषणा EMC_TFAW				0x098
#घोषणा EMC_TRPAB				0x09c
#घोषणा EMC_TCLKSTABLE				0x0a0
#घोषणा EMC_TCLKSTOP				0x0a4
#घोषणा EMC_TREFBW				0x0a8
#घोषणा EMC_QUSE_EXTRA				0x0ac
#घोषणा EMC_ODT_WRITE				0x0b0
#घोषणा EMC_ODT_READ				0x0b4
#घोषणा EMC_FBIO_CFG5				0x104
#घोषणा EMC_FBIO_CFG6				0x114
#घोषणा EMC_STAT_CONTROL			0x160
#घोषणा EMC_STAT_LLMC_CONTROL			0x178
#घोषणा EMC_STAT_PWR_CLOCK_LIMIT		0x198
#घोषणा EMC_STAT_PWR_CLOCKS			0x19c
#घोषणा EMC_STAT_PWR_COUNT			0x1a0
#घोषणा EMC_AUTO_CAL_INTERVAL			0x2a8
#घोषणा EMC_CFG_2				0x2b8
#घोषणा EMC_CFG_DIG_DLL				0x2bc
#घोषणा EMC_DLL_XFORM_DQS			0x2c0
#घोषणा EMC_DLL_XFORM_QUSE			0x2c4
#घोषणा EMC_ZCAL_REF_CNT			0x2e0
#घोषणा EMC_ZCAL_WAIT_CNT			0x2e4
#घोषणा EMC_CFG_CLKTRIM_0			0x2d0
#घोषणा EMC_CFG_CLKTRIM_1			0x2d4
#घोषणा EMC_CFG_CLKTRIM_2			0x2d8

#घोषणा EMC_CLKCHANGE_REQ_ENABLE		BIT(0)
#घोषणा EMC_CLKCHANGE_PD_ENABLE			BIT(1)
#घोषणा EMC_CLKCHANGE_SR_ENABLE			BIT(2)

#घोषणा EMC_TIMING_UPDATE			BIT(0)

#घोषणा EMC_REFRESH_OVERFLOW_INT		BIT(3)
#घोषणा EMC_CLKCHANGE_COMPLETE_INT		BIT(4)

#घोषणा EMC_DBG_READ_MUX_ASSEMBLY		BIT(0)
#घोषणा EMC_DBG_WRITE_MUX_ACTIVE		BIT(1)
#घोषणा EMC_DBG_FORCE_UPDATE			BIT(2)
#घोषणा EMC_DBG_READ_DQM_CTRL			BIT(9)
#घोषणा EMC_DBG_CFG_PRIORITY			BIT(24)

#घोषणा EMC_FBIO_CFG5_DRAM_WIDTH_X16		BIT(4)

#घोषणा EMC_PWR_GATHER_CLEAR			(1 << 8)
#घोषणा EMC_PWR_GATHER_DISABLE			(2 << 8)
#घोषणा EMC_PWR_GATHER_ENABLE			(3 << 8)

अटल स्थिर u16 emc_timing_रेजिस्टरs[] = अणु
	EMC_RC,
	EMC_RFC,
	EMC_RAS,
	EMC_RP,
	EMC_R2W,
	EMC_W2R,
	EMC_R2P,
	EMC_W2P,
	EMC_RD_RCD,
	EMC_WR_RCD,
	EMC_RRD,
	EMC_REXT,
	EMC_WDV,
	EMC_QUSE,
	EMC_QRST,
	EMC_QSAFE,
	EMC_RDV,
	EMC_REFRESH,
	EMC_BURST_REFRESH_NUM,
	EMC_PDEX2WR,
	EMC_PDEX2RD,
	EMC_PCHG2PDEN,
	EMC_ACT2PDEN,
	EMC_AR2PDEN,
	EMC_RW2PDEN,
	EMC_TXSR,
	EMC_TCKE,
	EMC_TFAW,
	EMC_TRPAB,
	EMC_TCLKSTABLE,
	EMC_TCLKSTOP,
	EMC_TREFBW,
	EMC_QUSE_EXTRA,
	EMC_FBIO_CFG6,
	EMC_ODT_WRITE,
	EMC_ODT_READ,
	EMC_FBIO_CFG5,
	EMC_CFG_DIG_DLL,
	EMC_DLL_XFORM_DQS,
	EMC_DLL_XFORM_QUSE,
	EMC_ZCAL_REF_CNT,
	EMC_ZCAL_WAIT_CNT,
	EMC_AUTO_CAL_INTERVAL,
	EMC_CFG_CLKTRIM_0,
	EMC_CFG_CLKTRIM_1,
	EMC_CFG_CLKTRIM_2,
पूर्ण;

काष्ठा emc_timing अणु
	अचिन्हित दीर्घ rate;
	u32 data[ARRAY_SIZE(emc_timing_रेजिस्टरs)];
पूर्ण;

क्रमागत emc_rate_request_type अणु
	EMC_RATE_DEVFREQ,
	EMC_RATE_DEBUG,
	EMC_RATE_ICC,
	EMC_RATE_TYPE_MAX,
पूर्ण;

काष्ठा emc_rate_request अणु
	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
पूर्ण;

काष्ठा tegra_emc अणु
	काष्ठा device *dev;
	काष्ठा tegra_mc *mc;
	काष्ठा icc_provider provider;
	काष्ठा notअगरier_block clk_nb;
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक dram_bus_width;

	काष्ठा emc_timing *timings;
	अचिन्हित पूर्णांक num_timings;

	काष्ठा अणु
		काष्ठा dentry *root;
		अचिन्हित दीर्घ min_rate;
		अचिन्हित दीर्घ max_rate;
	पूर्ण debugfs;

	/*
	 * There are multiple sources in the EMC driver which could request
	 * a min/max घड़ी rate, these rates are contained in this array.
	 */
	काष्ठा emc_rate_request requested_rate[EMC_RATE_TYPE_MAX];

	/* protect shared rate-change code path */
	काष्ठा mutex rate_lock;

	काष्ठा devfreq_simple_ondemand_data ondemand_data;
पूर्ण;

अटल irqवापस_t tegra_emc_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_emc *emc = data;
	u32 पूर्णांकmask = EMC_REFRESH_OVERFLOW_INT;
	u32 status;

	status = पढ़ोl_relaxed(emc->regs + EMC_INTSTATUS) & पूर्णांकmask;
	अगर (!status)
		वापस IRQ_NONE;

	/* notअगरy about HW problem */
	अगर (status & EMC_REFRESH_OVERFLOW_INT)
		dev_err_ratelimited(emc->dev,
				    "refresh request overflow timeout\n");

	/* clear पूर्णांकerrupts */
	ग_लिखोl_relaxed(status, emc->regs + EMC_INTSTATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा emc_timing *tegra_emc_find_timing(काष्ठा tegra_emc *emc,
						अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate >= rate) अणु
			timing = &emc->timings[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!timing) अणु
		dev_err(emc->dev, "no timing for rate %lu\n", rate);
		वापस शून्य;
	पूर्ण

	वापस timing;
पूर्ण

अटल पूर्णांक emc_prepare_timing_change(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate)
अणु
	काष्ठा emc_timing *timing = tegra_emc_find_timing(emc, rate);
	अचिन्हित पूर्णांक i;

	अगर (!timing)
		वापस -EINVAL;

	dev_dbg(emc->dev, "%s: using timing rate %lu for requested rate %lu\n",
		__func__, timing->rate, rate);

	/* program shaकरोw रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(timing->data); i++)
		ग_लिखोl_relaxed(timing->data[i],
			       emc->regs + emc_timing_रेजिस्टरs[i]);

	/* रुको until programming has settled */
	पढ़ोl_relaxed(emc->regs + emc_timing_रेजिस्टरs[i - 1]);

	वापस 0;
पूर्ण

अटल पूर्णांक emc_complete_timing_change(काष्ठा tegra_emc *emc, bool flush)
अणु
	पूर्णांक err;
	u32 v;

	dev_dbg(emc->dev, "%s: flush %d\n", __func__, flush);

	अगर (flush) अणु
		/* manually initiate memory timing update */
		ग_लिखोl_relaxed(EMC_TIMING_UPDATE,
			       emc->regs + EMC_TIMING_CONTROL);
		वापस 0;
	पूर्ण

	err = पढ़ोl_relaxed_poll_समयout_atomic(emc->regs + EMC_INTSTATUS, v,
						v & EMC_CLKCHANGE_COMPLETE_INT,
						1, 100);
	अगर (err) अणु
		dev_err(emc->dev, "emc-car handshake timeout: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_clk_change_notअगरy(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ msg, व्योम *data)
अणु
	काष्ठा tegra_emc *emc = container_of(nb, काष्ठा tegra_emc, clk_nb);
	काष्ठा clk_notअगरier_data *cnd = data;
	पूर्णांक err;

	चयन (msg) अणु
	हाल PRE_RATE_CHANGE:
		err = emc_prepare_timing_change(emc, cnd->new_rate);
		अवरोध;

	हाल ABORT_RATE_CHANGE:
		err = emc_prepare_timing_change(emc, cnd->old_rate);
		अगर (err)
			अवरोध;

		err = emc_complete_timing_change(emc, true);
		अवरोध;

	हाल POST_RATE_CHANGE:
		err = emc_complete_timing_change(emc, false);
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक load_one_timing_from_dt(काष्ठा tegra_emc *emc,
				   काष्ठा emc_timing *timing,
				   काष्ठा device_node *node)
अणु
	u32 rate;
	पूर्णांक err;

	अगर (!of_device_is_compatible(node, "nvidia,tegra20-emc-table")) अणु
		dev_err(emc->dev, "incompatible DT node: %pOF\n", node);
		वापस -EINVAL;
	पूर्ण

	err = of_property_पढ़ो_u32(node, "clock-frequency", &rate);
	अगर (err) अणु
		dev_err(emc->dev, "timing %pOF: failed to read rate: %d\n",
			node, err);
		वापस err;
	पूर्ण

	err = of_property_पढ़ो_u32_array(node, "nvidia,emc-registers",
					 timing->data,
					 ARRAY_SIZE(emc_timing_रेजिस्टरs));
	अगर (err) अणु
		dev_err(emc->dev,
			"timing %pOF: failed to read emc timing data: %d\n",
			node, err);
		वापस err;
	पूर्ण

	/*
	 * The EMC घड़ी rate is twice the bus rate, and the bus rate is
	 * measured in kHz.
	 */
	timing->rate = rate * 2 * 1000;

	dev_dbg(emc->dev, "%s: %pOF: EMC rate %lu\n",
		__func__, node, timing->rate);

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_timings(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा emc_timing *a = _a;
	स्थिर काष्ठा emc_timing *b = _b;

	अगर (a->rate < b->rate)
		वापस -1;

	अगर (a->rate > b->rate)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_load_timings_from_dt(काष्ठा tegra_emc *emc,
					  काष्ठा device_node *node)
अणु
	काष्ठा device_node *child;
	काष्ठा emc_timing *timing;
	पूर्णांक child_count;
	पूर्णांक err;

	child_count = of_get_child_count(node);
	अगर (!child_count) अणु
		dev_err(emc->dev, "no memory timings in DT node: %pOF\n", node);
		वापस -EINVAL;
	पूर्ण

	emc->timings = devm_kसुस्मृति(emc->dev, child_count, माप(*timing),
				    GFP_KERNEL);
	अगर (!emc->timings)
		वापस -ENOMEM;

	emc->num_timings = child_count;
	timing = emc->timings;

	क्रम_each_child_of_node(node, child) अणु
		err = load_one_timing_from_dt(emc, timing++, child);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	sort(emc->timings, emc->num_timings, माप(*timing), cmp_timings,
	     शून्य);

	dev_info_once(emc->dev,
		      "got %u timings for RAM code %u (min %luMHz max %luMHz)\n",
		      emc->num_timings,
		      tegra_पढ़ो_ram_code(),
		      emc->timings[0].rate / 1000000,
		      emc->timings[emc->num_timings - 1].rate / 1000000);

	वापस 0;
पूर्ण

अटल काष्ठा device_node *
tegra_emc_find_node_by_ram_code(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	u32 value, ram_code;
	पूर्णांक err;

	अगर (of_get_child_count(dev->of_node) == 0) अणु
		dev_info_once(dev, "device-tree doesn't have memory timings\n");
		वापस शून्य;
	पूर्ण

	अगर (!of_property_पढ़ो_bool(dev->of_node, "nvidia,use-ram-code"))
		वापस of_node_get(dev->of_node);

	ram_code = tegra_पढ़ो_ram_code();

	क्रम (np = of_find_node_by_name(dev->of_node, "emc-tables"); np;
	     np = of_find_node_by_name(np, "emc-tables")) अणु
		err = of_property_पढ़ो_u32(np, "nvidia,ram-code", &value);
		अगर (err || value != ram_code) अणु
			of_node_put(np);
			जारी;
		पूर्ण

		वापस np;
	पूर्ण

	dev_err(dev, "no memory timings for RAM code %u found in device tree\n",
		ram_code);

	वापस शून्य;
पूर्ण

अटल पूर्णांक emc_setup_hw(काष्ठा tegra_emc *emc)
अणु
	u32 पूर्णांकmask = EMC_REFRESH_OVERFLOW_INT;
	u32 emc_cfg, emc_dbg, emc_fbio;

	emc_cfg = पढ़ोl_relaxed(emc->regs + EMC_CFG_2);

	/*
	 * Depending on a memory type, DRAM should enter either self-refresh
	 * or घातer-करोwn state on EMC घड़ी change.
	 */
	अगर (!(emc_cfg & EMC_CLKCHANGE_PD_ENABLE) &&
	    !(emc_cfg & EMC_CLKCHANGE_SR_ENABLE)) अणु
		dev_err(emc->dev,
			"bootloader didn't specify DRAM auto-suspend mode\n");
		वापस -EINVAL;
	पूर्ण

	/* enable EMC and CAR to handshake on PLL भागider/source changes */
	emc_cfg |= EMC_CLKCHANGE_REQ_ENABLE;
	ग_लिखोl_relaxed(emc_cfg, emc->regs + EMC_CFG_2);

	/* initialize पूर्णांकerrupt */
	ग_लिखोl_relaxed(पूर्णांकmask, emc->regs + EMC_INTMASK);
	ग_लिखोl_relaxed(पूर्णांकmask, emc->regs + EMC_INTSTATUS);

	/* ensure that unwanted debug features are disabled */
	emc_dbg = पढ़ोl_relaxed(emc->regs + EMC_DBG);
	emc_dbg |= EMC_DBG_CFG_PRIORITY;
	emc_dbg &= ~EMC_DBG_READ_MUX_ASSEMBLY;
	emc_dbg &= ~EMC_DBG_WRITE_MUX_ACTIVE;
	emc_dbg &= ~EMC_DBG_FORCE_UPDATE;
	ग_लिखोl_relaxed(emc_dbg, emc->regs + EMC_DBG);

	emc_fbio = पढ़ोl_relaxed(emc->regs + EMC_FBIO_CFG5);

	अगर (emc_fbio & EMC_FBIO_CFG5_DRAM_WIDTH_X16)
		emc->dram_bus_width = 16;
	अन्यथा
		emc->dram_bus_width = 32;

	dev_info_once(emc->dev, "%ubit DRAM bus\n", emc->dram_bus_width);

	वापस 0;
पूर्ण

अटल दीर्घ emc_round_rate(अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ min_rate,
			   अचिन्हित दीर्घ max_rate,
			   व्योम *arg)
अणु
	काष्ठा emc_timing *timing = शून्य;
	काष्ठा tegra_emc *emc = arg;
	अचिन्हित पूर्णांक i;

	अगर (!emc->num_timings)
		वापस clk_get_rate(emc->clk);

	min_rate = min(min_rate, emc->timings[emc->num_timings - 1].rate);

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate < rate && i != emc->num_timings - 1)
			जारी;

		अगर (emc->timings[i].rate > max_rate) अणु
			i = max(i, 1u) - 1;

			अगर (emc->timings[i].rate < min_rate)
				अवरोध;
		पूर्ण

		अगर (emc->timings[i].rate < min_rate)
			जारी;

		timing = &emc->timings[i];
		अवरोध;
	पूर्ण

	अगर (!timing) अणु
		dev_err(emc->dev, "no timing for rate %lu min %lu max %lu\n",
			rate, min_rate, max_rate);
		वापस -EINVAL;
	पूर्ण

	वापस timing->rate;
पूर्ण

अटल व्योम tegra_emc_rate_requests_init(काष्ठा tegra_emc *emc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EMC_RATE_TYPE_MAX; i++) अणु
		emc->requested_rate[i].min_rate = 0;
		emc->requested_rate[i].max_rate = अच_दीर्घ_उच्च;
	पूर्ण
पूर्ण

अटल पूर्णांक emc_request_rate(काष्ठा tegra_emc *emc,
			    अचिन्हित दीर्घ new_min_rate,
			    अचिन्हित दीर्घ new_max_rate,
			    क्रमागत emc_rate_request_type type)
अणु
	काष्ठा emc_rate_request *req = emc->requested_rate;
	अचिन्हित दीर्घ min_rate = 0, max_rate = अच_दीर्घ_उच्च;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* select minimum and maximum rates among the requested rates */
	क्रम (i = 0; i < EMC_RATE_TYPE_MAX; i++, req++) अणु
		अगर (i == type) अणु
			min_rate = max(new_min_rate, min_rate);
			max_rate = min(new_max_rate, max_rate);
		पूर्ण अन्यथा अणु
			min_rate = max(req->min_rate, min_rate);
			max_rate = min(req->max_rate, max_rate);
		पूर्ण
	पूर्ण

	अगर (min_rate > max_rate) अणु
		dev_err_ratelimited(emc->dev, "%s: type %u: out of range: %lu %lu\n",
				    __func__, type, min_rate, max_rate);
		वापस -दुस्फल;
	पूर्ण

	/*
	 * EMC rate-changes should go via OPP API because it manages voltage
	 * changes.
	 */
	err = dev_pm_opp_set_rate(emc->dev, min_rate);
	अगर (err)
		वापस err;

	emc->requested_rate[type].min_rate = new_min_rate;
	emc->requested_rate[type].max_rate = new_max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक emc_set_min_rate(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate,
			    क्रमागत emc_rate_request_type type)
अणु
	काष्ठा emc_rate_request *req = &emc->requested_rate[type];
	पूर्णांक ret;

	mutex_lock(&emc->rate_lock);
	ret = emc_request_rate(emc, rate, req->max_rate, type);
	mutex_unlock(&emc->rate_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक emc_set_max_rate(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate,
			    क्रमागत emc_rate_request_type type)
अणु
	काष्ठा emc_rate_request *req = &emc->requested_rate[type];
	पूर्णांक ret;

	mutex_lock(&emc->rate_lock);
	ret = emc_request_rate(emc, req->min_rate, rate, type);
	mutex_unlock(&emc->rate_lock);

	वापस ret;
पूर्ण

/*
 * debugfs पूर्णांकerface
 *
 * The memory controller driver exposes some files in debugfs that can be used
 * to control the EMC frequency. The top-level directory can be found here:
 *
 *   /sys/kernel/debug/emc
 *
 * It contains the following files:
 *
 *   - available_rates: This file contains a list of valid, space-separated
 *     EMC frequencies.
 *
 *   - min_rate: Writing a value to this file sets the given frequency as the
 *       न्यूनमान of the permitted range. If this is higher than the currently
 *       configured EMC frequency, this will cause the frequency to be
 *       increased so that it stays within the valid range.
 *
 *   - max_rate: Similarily to the min_rate file, writing a value to this file
 *       sets the given frequency as the उच्चमानing of the permitted range. If
 *       the value is lower than the currently configured EMC frequency, this
 *       will cause the frequency to be decreased so that it stays within the
 *       valid range.
 */

अटल bool tegra_emc_validate_rate(काष्ठा tegra_emc *emc, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++)
		अगर (rate == emc->timings[i].rate)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tegra_emc_debug_available_rates_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा tegra_emc *emc = s->निजी;
	स्थिर अक्षर *prefix = "";
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		seq_म_लिखो(s, "%s%lu", prefix, emc->timings[i].rate);
		prefix = " ";
	पूर्ण

	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_debug_available_rates_खोलो(काष्ठा inode *inode,
						काष्ठा file *file)
अणु
	वापस single_खोलो(file, tegra_emc_debug_available_rates_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations tegra_emc_debug_available_rates_fops = अणु
	.खोलो = tegra_emc_debug_available_rates_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक tegra_emc_debug_min_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra_emc *emc = data;

	*rate = emc->debugfs.min_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_debug_min_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = emc_set_min_rate(emc, rate, EMC_RATE_DEBUG);
	अगर (err < 0)
		वापस err;

	emc->debugfs.min_rate = rate;

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(tegra_emc_debug_min_rate_fops,
			tegra_emc_debug_min_rate_get,
			tegra_emc_debug_min_rate_set, "%llu\n");

अटल पूर्णांक tegra_emc_debug_max_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra_emc *emc = data;

	*rate = emc->debugfs.max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_debug_max_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = emc_set_max_rate(emc, rate, EMC_RATE_DEBUG);
	अगर (err < 0)
		वापस err;

	emc->debugfs.max_rate = rate;

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(tegra_emc_debug_max_rate_fops,
			tegra_emc_debug_max_rate_get,
			tegra_emc_debug_max_rate_set, "%llu\n");

अटल व्योम tegra_emc_debugfs_init(काष्ठा tegra_emc *emc)
अणु
	काष्ठा device *dev = emc->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	emc->debugfs.min_rate = अच_दीर्घ_उच्च;
	emc->debugfs.max_rate = 0;

	क्रम (i = 0; i < emc->num_timings; i++) अणु
		अगर (emc->timings[i].rate < emc->debugfs.min_rate)
			emc->debugfs.min_rate = emc->timings[i].rate;

		अगर (emc->timings[i].rate > emc->debugfs.max_rate)
			emc->debugfs.max_rate = emc->timings[i].rate;
	पूर्ण

	अगर (!emc->num_timings) अणु
		emc->debugfs.min_rate = clk_get_rate(emc->clk);
		emc->debugfs.max_rate = emc->debugfs.min_rate;
	पूर्ण

	err = clk_set_rate_range(emc->clk, emc->debugfs.min_rate,
				 emc->debugfs.max_rate);
	अगर (err < 0) अणु
		dev_err(dev, "failed to set rate range [%lu-%lu] for %pC\n",
			emc->debugfs.min_rate, emc->debugfs.max_rate,
			emc->clk);
	पूर्ण

	emc->debugfs.root = debugfs_create_dir("emc", शून्य);
	अगर (!emc->debugfs.root) अणु
		dev_err(emc->dev, "failed to create debugfs directory\n");
		वापस;
	पूर्ण

	debugfs_create_file("available_rates", 0444, emc->debugfs.root,
			    emc, &tegra_emc_debug_available_rates_fops);
	debugfs_create_file("min_rate", 0644, emc->debugfs.root,
			    emc, &tegra_emc_debug_min_rate_fops);
	debugfs_create_file("max_rate", 0644, emc->debugfs.root,
			    emc, &tegra_emc_debug_max_rate_fops);
पूर्ण

अटल अंतरभूत काष्ठा tegra_emc *
to_tegra_emc_provider(काष्ठा icc_provider *provider)
अणु
	वापस container_of(provider, काष्ठा tegra_emc, provider);
पूर्ण

अटल काष्ठा icc_node_data *
emc_of_icc_xlate_extended(काष्ठा of_phandle_args *spec, व्योम *data)
अणु
	काष्ठा icc_provider *provider = data;
	काष्ठा icc_node_data *ndata;
	काष्ठा icc_node *node;

	/* External Memory is the only possible ICC route */
	list_क्रम_each_entry(node, &provider->nodes, node_list) अणु
		अगर (node->id != TEGRA_ICC_EMEM)
			जारी;

		ndata = kzalloc(माप(*ndata), GFP_KERNEL);
		अगर (!ndata)
			वापस ERR_PTR(-ENOMEM);

		/*
		 * SRC and DST nodes should have matching TAG in order to have
		 * it set by शेष क्रम a requested path.
		 */
		ndata->tag = TEGRA_MC_ICC_TAG_ISO;
		ndata->node = node;

		वापस ndata;
	पूर्ण

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण

अटल पूर्णांक emc_icc_set(काष्ठा icc_node *src, काष्ठा icc_node *dst)
अणु
	काष्ठा tegra_emc *emc = to_tegra_emc_provider(dst->provider);
	अचिन्हित दीर्घ दीर्घ peak_bw = icc_units_to_bps(dst->peak_bw);
	अचिन्हित दीर्घ दीर्घ avg_bw = icc_units_to_bps(dst->avg_bw);
	अचिन्हित दीर्घ दीर्घ rate = max(avg_bw, peak_bw);
	अचिन्हित पूर्णांक dram_data_bus_width_bytes;
	पूर्णांक err;

	/*
	 * Tegra20 EMC runs on x2 घड़ी rate of SDRAM bus because DDR data
	 * is sampled on both घड़ी edges.  This means that EMC घड़ी rate
	 * equals to the peak data-rate.
	 */
	dram_data_bus_width_bytes = emc->dram_bus_width / 8;
	करो_भाग(rate, dram_data_bus_width_bytes);
	rate = min_t(u64, rate, U32_MAX);

	err = emc_set_min_rate(emc, rate, EMC_RATE_ICC);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_पूर्णांकerconnect_init(काष्ठा tegra_emc *emc)
अणु
	स्थिर काष्ठा tegra_mc_soc *soc;
	काष्ठा icc_node *node;
	पूर्णांक err;

	emc->mc = devm_tegra_memory_controller_get(emc->dev);
	अगर (IS_ERR(emc->mc))
		वापस PTR_ERR(emc->mc);

	soc = emc->mc->soc;

	emc->provider.dev = emc->dev;
	emc->provider.set = emc_icc_set;
	emc->provider.data = &emc->provider;
	emc->provider.aggregate = soc->icc_ops->aggregate;
	emc->provider.xlate_extended = emc_of_icc_xlate_extended;

	err = icc_provider_add(&emc->provider);
	अगर (err)
		जाओ err_msg;

	/* create External Memory Controller node */
	node = icc_node_create(TEGRA_ICC_EMC);
	अगर (IS_ERR(node)) अणु
		err = PTR_ERR(node);
		जाओ del_provider;
	पूर्ण

	node->name = "External Memory Controller";
	icc_node_add(node, &emc->provider);

	/* link External Memory Controller to External Memory (DRAM) */
	err = icc_link_create(node, TEGRA_ICC_EMEM);
	अगर (err)
		जाओ हटाओ_nodes;

	/* create External Memory node */
	node = icc_node_create(TEGRA_ICC_EMEM);
	अगर (IS_ERR(node)) अणु
		err = PTR_ERR(node);
		जाओ हटाओ_nodes;
	पूर्ण

	node->name = "External Memory (DRAM)";
	icc_node_add(node, &emc->provider);

	वापस 0;

हटाओ_nodes:
	icc_nodes_हटाओ(&emc->provider);
del_provider:
	icc_provider_del(&emc->provider);
err_msg:
	dev_err(emc->dev, "failed to initialize ICC: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_emc_opp_table_init(काष्ठा tegra_emc *emc)
अणु
	u32 hw_version = BIT(tegra_sku_info.soc_process_id);
	काष्ठा opp_table *hw_opp_table;
	पूर्णांक err;

	hw_opp_table = dev_pm_opp_set_supported_hw(emc->dev, &hw_version, 1);
	err = PTR_ERR_OR_ZERO(hw_opp_table);
	अगर (err) अणु
		dev_err(emc->dev, "failed to set OPP supported HW: %d\n", err);
		वापस err;
	पूर्ण

	err = dev_pm_opp_of_add_table(emc->dev);
	अगर (err) अणु
		अगर (err == -ENODEV)
			dev_err(emc->dev, "OPP table not found, please update your device tree\n");
		अन्यथा
			dev_err(emc->dev, "failed to add OPP table: %d\n", err);

		जाओ put_hw_table;
	पूर्ण

	dev_info_once(emc->dev, "OPP HW ver. 0x%x, current clock rate %lu MHz\n",
		      hw_version, clk_get_rate(emc->clk) / 1000000);

	/* first dummy rate-set initializes voltage state */
	err = dev_pm_opp_set_rate(emc->dev, clk_get_rate(emc->clk));
	अगर (err) अणु
		dev_err(emc->dev, "failed to initialize OPP clock: %d\n", err);
		जाओ हटाओ_table;
	पूर्ण

	वापस 0;

हटाओ_table:
	dev_pm_opp_of_हटाओ_table(emc->dev);
put_hw_table:
	dev_pm_opp_put_supported_hw(hw_opp_table);

	वापस err;
पूर्ण

अटल व्योम devm_tegra_emc_unset_callback(व्योम *data)
अणु
	tegra20_clk_set_emc_round_callback(शून्य, शून्य);
पूर्ण

अटल व्योम devm_tegra_emc_unreg_clk_notअगरier(व्योम *data)
अणु
	काष्ठा tegra_emc *emc = data;

	clk_notअगरier_unरेजिस्टर(emc->clk, &emc->clk_nb);
पूर्ण

अटल पूर्णांक tegra_emc_init_clk(काष्ठा tegra_emc *emc)
अणु
	पूर्णांक err;

	tegra20_clk_set_emc_round_callback(emc_round_rate, emc);

	err = devm_add_action_or_reset(emc->dev, devm_tegra_emc_unset_callback,
				       शून्य);
	अगर (err)
		वापस err;

	emc->clk = devm_clk_get(emc->dev, शून्य);
	अगर (IS_ERR(emc->clk)) अणु
		dev_err(emc->dev, "failed to get EMC clock: %pe\n", emc->clk);
		वापस PTR_ERR(emc->clk);
	पूर्ण

	err = clk_notअगरier_रेजिस्टर(emc->clk, &emc->clk_nb);
	अगर (err) अणु
		dev_err(emc->dev, "failed to register clk notifier: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(emc->dev,
				       devm_tegra_emc_unreg_clk_notअगरier, emc);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_devfreq_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
				    u32 flags)
अणु
	काष्ठा tegra_emc *emc = dev_get_drvdata(dev);
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ rate;

	opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(opp)) अणु
		dev_err(dev, "failed to find opp for %lu Hz\n", *freq);
		वापस PTR_ERR(opp);
	पूर्ण

	rate = dev_pm_opp_get_freq(opp);
	dev_pm_opp_put(opp);

	वापस emc_set_min_rate(emc, rate, EMC_RATE_DEVFREQ);
पूर्ण

अटल पूर्णांक tegra_emc_devfreq_get_dev_status(काष्ठा device *dev,
					    काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा tegra_emc *emc = dev_get_drvdata(dev);

	/* मुक्तze counters */
	ग_लिखोl_relaxed(EMC_PWR_GATHER_DISABLE, emc->regs + EMC_STAT_CONTROL);

	/*
	 *  busy_समय: number of घड़ीs EMC request was accepted
	 * total_समय: number of घड़ीs PWR_GATHER control was set to ENABLE
	 */
	stat->busy_समय = पढ़ोl_relaxed(emc->regs + EMC_STAT_PWR_COUNT);
	stat->total_समय = पढ़ोl_relaxed(emc->regs + EMC_STAT_PWR_CLOCKS);
	stat->current_frequency = clk_get_rate(emc->clk);

	/* clear counters and restart */
	ग_लिखोl_relaxed(EMC_PWR_GATHER_CLEAR, emc->regs + EMC_STAT_CONTROL);
	ग_लिखोl_relaxed(EMC_PWR_GATHER_ENABLE, emc->regs + EMC_STAT_CONTROL);

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_dev_profile tegra_emc_devfreq_profile = अणु
	.polling_ms = 30,
	.target = tegra_emc_devfreq_target,
	.get_dev_status = tegra_emc_devfreq_get_dev_status,
पूर्ण;

अटल पूर्णांक tegra_emc_devfreq_init(काष्ठा tegra_emc *emc)
अणु
	काष्ठा devfreq *devfreq;

	/*
	 * PWR_COUNT is 1/2 of PWR_CLOCKS at max, and thus, the up-threshold
	 * should be less than 50.  Secondly, multiple active memory clients
	 * may cause over 20% of lost घड़ी cycles due to stalls caused by
	 * competing memory accesses.  This means that threshold should be
	 * set to a less than 30 in order to have a properly working governor.
	 */
	emc->ondemand_data.upthreshold = 20;

	/*
	 * Reset statistic gathers state, select global bandwidth क्रम the
	 * statistics collection mode and set घड़ीs counter saturation
	 * limit to maximum.
	 */
	ग_लिखोl_relaxed(0x00000000, emc->regs + EMC_STAT_CONTROL);
	ग_लिखोl_relaxed(0x00000000, emc->regs + EMC_STAT_LLMC_CONTROL);
	ग_लिखोl_relaxed(0xffffffff, emc->regs + EMC_STAT_PWR_CLOCK_LIMIT);

	devfreq = devm_devfreq_add_device(emc->dev, &tegra_emc_devfreq_profile,
					  DEVFREQ_GOV_SIMPLE_ONDEMAND,
					  &emc->ondemand_data);
	अगर (IS_ERR(devfreq)) अणु
		dev_err(emc->dev, "failed to initialize devfreq: %pe", devfreq);
		वापस PTR_ERR(devfreq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_emc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	काष्ठा tegra_emc *emc;
	पूर्णांक irq, err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(&pdev->dev, "please update your device tree\n");
		वापस irq;
	पूर्ण

	emc = devm_kzalloc(&pdev->dev, माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस -ENOMEM;

	mutex_init(&emc->rate_lock);
	emc->clk_nb.notअगरier_call = tegra_emc_clk_change_notअगरy;
	emc->dev = &pdev->dev;

	np = tegra_emc_find_node_by_ram_code(&pdev->dev);
	अगर (np) अणु
		err = tegra_emc_load_timings_from_dt(emc, np);
		of_node_put(np);
		अगर (err)
			वापस err;
	पूर्ण

	emc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(emc->regs))
		वापस PTR_ERR(emc->regs);

	err = emc_setup_hw(emc);
	अगर (err)
		वापस err;

	err = devm_request_irq(&pdev->dev, irq, tegra_emc_isr, 0,
			       dev_name(&pdev->dev), emc);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_emc_init_clk(emc);
	अगर (err)
		वापस err;

	err = tegra_emc_opp_table_init(emc);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, emc);
	tegra_emc_rate_requests_init(emc);
	tegra_emc_debugfs_init(emc);
	tegra_emc_पूर्णांकerconnect_init(emc);
	tegra_emc_devfreq_init(emc);

	/*
	 * Don't allow the kernel module to be unloaded. Unloading adds some
	 * extra complनिकासy which करोesn't really worth the efक्रमt in a हाल of
	 * this driver.
	 */
	try_module_get(THIS_MODULE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_emc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-emc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_emc_of_match);

अटल काष्ठा platक्रमm_driver tegra_emc_driver = अणु
	.probe = tegra_emc_probe,
	.driver = अणु
		.name = "tegra20-emc",
		.of_match_table = tegra_emc_of_match,
		.suppress_bind_attrs = true,
		.sync_state = icc_sync_state,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_emc_driver);

MODULE_AUTHOR("Dmitry Osipenko <digetx@gmail.com>");
MODULE_DESCRIPTION("NVIDIA Tegra20 EMC driver");
MODULE_LICENSE("GPL v2");
