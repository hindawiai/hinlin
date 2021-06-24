<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2018 Linaro Ltd.
 * Copyright (C) 2014 Sony Mobile Communications AB
 * Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/soc/qcom/mdt_loader.h>
#समावेश "qcom_common.h"
#समावेश "qcom_pil_info.h"
#समावेश "qcom_q6v5.h"

#घोषणा WCSS_CRASH_REASON		421

/* Q6SS Register Offsets */
#घोषणा Q6SS_RESET_REG		0x014
#घोषणा Q6SS_GFMUX_CTL_REG		0x020
#घोषणा Q6SS_PWR_CTL_REG		0x030
#घोषणा Q6SS_MEM_PWR_CTL		0x0B0
#घोषणा Q6SS_STRAP_ACC			0x110
#घोषणा Q6SS_CGC_OVERRIDE		0x034
#घोषणा Q6SS_BCR_REG			0x6000

/* AXI Halt Register Offsets */
#घोषणा AXI_HALTREQ_REG			0x0
#घोषणा AXI_HALTACK_REG			0x4
#घोषणा AXI_IDLE_REG			0x8

#घोषणा HALT_ACK_TIMEOUT_MS		100

/* Q6SS_RESET */
#घोषणा Q6SS_STOP_CORE			BIT(0)
#घोषणा Q6SS_CORE_ARES			BIT(1)
#घोषणा Q6SS_BUS_ARES_ENABLE		BIT(2)

/* Q6SS_BRC_RESET */
#घोषणा Q6SS_BRC_BLK_ARES		BIT(0)

/* Q6SS_GFMUX_CTL */
#घोषणा Q6SS_CLK_ENABLE			BIT(1)
#घोषणा Q6SS_SWITCH_CLK_SRC		BIT(8)

/* Q6SS_PWR_CTL */
#घोषणा Q6SS_L2DATA_STBY_N		BIT(18)
#घोषणा Q6SS_SLP_RET_N			BIT(19)
#घोषणा Q6SS_CLAMP_IO			BIT(20)
#घोषणा QDSS_BHS_ON			BIT(21)
#घोषणा QDSS_Q6_MEMORIES		GENMASK(15, 0)

/* Q6SS parameters */
#घोषणा Q6SS_LDO_BYP		BIT(25)
#घोषणा Q6SS_BHS_ON		BIT(24)
#घोषणा Q6SS_CLAMP_WL		BIT(21)
#घोषणा Q6SS_CLAMP_QMC_MEM		BIT(22)
#घोषणा HALT_CHECK_MAX_LOOPS		200
#घोषणा Q6SS_XO_CBCR		GENMASK(5, 3)
#घोषणा Q6SS_SLEEP_CBCR		GENMASK(5, 2)

/* Q6SS config/status रेजिस्टरs */
#घोषणा TCSR_GLOBAL_CFG0	0x0
#घोषणा TCSR_GLOBAL_CFG1	0x4
#घोषणा SSCAON_CONFIG		0x8
#घोषणा SSCAON_STATUS		0xc
#घोषणा Q6SS_BHS_STATUS		0x78
#घोषणा Q6SS_RST_EVB		0x10

#घोषणा BHS_EN_REST_ACK		BIT(0)
#घोषणा SSCAON_ENABLE		BIT(13)
#घोषणा SSCAON_BUS_EN		BIT(15)
#घोषणा SSCAON_BUS_MUX_MASK	GENMASK(18, 16)

#घोषणा MEM_BANKS		19
#घोषणा TCSR_WCSS_CLK_MASK	0x1F
#घोषणा TCSR_WCSS_CLK_ENABLE	0x14

#घोषणा MAX_HALT_REG		3
क्रमागत अणु
	WCSS_IPQ8074,
	WCSS_QCS404,
पूर्ण;

काष्ठा wcss_data अणु
	स्थिर अक्षर *firmware_name;
	अचिन्हित पूर्णांक crash_reason_smem;
	u32 version;
	bool aon_reset_required;
	bool wcss_q6_reset_required;
	स्थिर अक्षर *ssr_name;
	स्थिर अक्षर *sysmon_name;
	पूर्णांक ssctl_id;
	स्थिर काष्ठा rproc_ops *ops;
	bool requires_क्रमce_stop;
पूर्ण;

काष्ठा q6v5_wcss अणु
	काष्ठा device *dev;

	व्योम __iomem *reg_base;
	व्योम __iomem *rmb_base;

	काष्ठा regmap *halt_map;
	u32 halt_q6;
	u32 halt_wcss;
	u32 halt_nc;

	काष्ठा clk *xo;
	काष्ठा clk *ahbfabric_cbcr_clk;
	काष्ठा clk *gcc_abhs_cbcr;
	काष्ठा clk *gcc_axim_cbcr;
	काष्ठा clk *lcc_csr_cbcr;
	काष्ठा clk *ahbs_cbcr;
	काष्ठा clk *tcm_slave_cbcr;
	काष्ठा clk *qdsp6ss_abhm_cbcr;
	काष्ठा clk *qdsp6ss_sleep_cbcr;
	काष्ठा clk *qdsp6ss_axim_cbcr;
	काष्ठा clk *qdsp6ss_xo_cbcr;
	काष्ठा clk *qdsp6ss_core_gfmux;
	काष्ठा clk *lcc_bcr_sleep;
	काष्ठा regulator *cx_supply;
	काष्ठा qcom_sysmon *sysmon;

	काष्ठा reset_control *wcss_aon_reset;
	काष्ठा reset_control *wcss_reset;
	काष्ठा reset_control *wcss_q6_reset;
	काष्ठा reset_control *wcss_q6_bcr_reset;

	काष्ठा qcom_q6v5 q6v5;

	phys_addr_t mem_phys;
	phys_addr_t mem_reloc;
	व्योम *mem_region;
	माप_प्रकार mem_size;

	अचिन्हित पूर्णांक crash_reason_smem;
	u32 version;
	bool requires_क्रमce_stop;

	काष्ठा qcom_rproc_glink glink_subdev;
	काष्ठा qcom_rproc_ssr ssr_subdev;
पूर्ण;

अटल पूर्णांक q6v5_wcss_reset(काष्ठा q6v5_wcss *wcss)
अणु
	पूर्णांक ret;
	u32 val;
	पूर्णांक i;

	/* Assert resets, stop core */
	val = पढ़ोl(wcss->reg_base + Q6SS_RESET_REG);
	val |= Q6SS_CORE_ARES | Q6SS_BUS_ARES_ENABLE | Q6SS_STOP_CORE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_RESET_REG);

	/* BHS require xo cbcr to be enabled */
	val = पढ़ोl(wcss->reg_base + Q6SS_XO_CBCR);
	val |= 0x1;
	ग_लिखोl(val, wcss->reg_base + Q6SS_XO_CBCR);

	/* Read CLKOFF bit to go low indicating CLK is enabled */
	ret = पढ़ोl_poll_समयout(wcss->reg_base + Q6SS_XO_CBCR,
				 val, !(val & BIT(31)), 1,
				 HALT_CHECK_MAX_LOOPS);
	अगर (ret) अणु
		dev_err(wcss->dev,
			"xo cbcr enabling timed out (rc:%d)\n", ret);
		वापस ret;
	पूर्ण
	/* Enable घातer block headचयन and रुको क्रम it to stabilize */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val |= Q6SS_BHS_ON;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);
	udelay(1);

	/* Put LDO in bypass mode */
	val |= Q6SS_LDO_BYP;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* Deनिश्चित Q6 compiler memory clamp */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val &= ~Q6SS_CLAMP_QMC_MEM;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* Deनिश्चित memory peripheral sleep and L2 memory standby */
	val |= Q6SS_L2DATA_STBY_N | Q6SS_SLP_RET_N;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* Turn on L1, L2, ETB and JU memories 1 at a समय */
	val = पढ़ोl(wcss->reg_base + Q6SS_MEM_PWR_CTL);
	क्रम (i = MEM_BANKS; i >= 0; i--) अणु
		val |= BIT(i);
		ग_लिखोl(val, wcss->reg_base + Q6SS_MEM_PWR_CTL);
		/*
		 * Read back value to ensure the ग_लिखो is करोne then
		 * रुको क्रम 1us क्रम both memory peripheral and data
		 * array to turn on.
		 */
		val |= पढ़ोl(wcss->reg_base + Q6SS_MEM_PWR_CTL);
		udelay(1);
	पूर्ण
	/* Remove word line clamp */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val &= ~Q6SS_CLAMP_WL;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* Remove IO clamp */
	val &= ~Q6SS_CLAMP_IO;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* Bring core out of reset */
	val = पढ़ोl(wcss->reg_base + Q6SS_RESET_REG);
	val &= ~Q6SS_CORE_ARES;
	ग_लिखोl(val, wcss->reg_base + Q6SS_RESET_REG);

	/* Turn on core घड़ी */
	val = पढ़ोl(wcss->reg_base + Q6SS_GFMUX_CTL_REG);
	val |= Q6SS_CLK_ENABLE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_GFMUX_CTL_REG);

	/* Start core execution */
	val = पढ़ोl(wcss->reg_base + Q6SS_RESET_REG);
	val &= ~Q6SS_STOP_CORE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_RESET_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_start(काष्ठा rproc *rproc)
अणु
	काष्ठा q6v5_wcss *wcss = rproc->priv;
	पूर्णांक ret;

	qcom_q6v5_prepare(&wcss->q6v5);

	/* Release Q6 and WCSS reset */
	ret = reset_control_deनिश्चित(wcss->wcss_reset);
	अगर (ret) अणु
		dev_err(wcss->dev, "wcss_reset failed\n");
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(wcss->wcss_q6_reset);
	अगर (ret) अणु
		dev_err(wcss->dev, "wcss_q6_reset failed\n");
		जाओ wcss_reset;
	पूर्ण

	/* Lithium configuration - घड़ी gating and bus arbitration */
	ret = regmap_update_bits(wcss->halt_map,
				 wcss->halt_nc + TCSR_GLOBAL_CFG0,
				 TCSR_WCSS_CLK_MASK,
				 TCSR_WCSS_CLK_ENABLE);
	अगर (ret)
		जाओ wcss_q6_reset;

	ret = regmap_update_bits(wcss->halt_map,
				 wcss->halt_nc + TCSR_GLOBAL_CFG1,
				 1, 0);
	अगर (ret)
		जाओ wcss_q6_reset;

	/* Write bootaddr to EVB so that Q6WCSS will jump there after reset */
	ग_लिखोl(rproc->bootaddr >> 4, wcss->reg_base + Q6SS_RST_EVB);

	ret = q6v5_wcss_reset(wcss);
	अगर (ret)
		जाओ wcss_q6_reset;

	ret = qcom_q6v5_रुको_क्रम_start(&wcss->q6v5, 5 * HZ);
	अगर (ret == -ETIMEDOUT)
		dev_err(wcss->dev, "start timed out\n");

	वापस ret;

wcss_q6_reset:
	reset_control_निश्चित(wcss->wcss_q6_reset);

wcss_reset:
	reset_control_निश्चित(wcss->wcss_reset);

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_wcss_qcs404_घातer_on(काष्ठा q6v5_wcss *wcss)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret, idx;

	/* Toggle the restart */
	reset_control_निश्चित(wcss->wcss_reset);
	usleep_range(200, 300);
	reset_control_deनिश्चित(wcss->wcss_reset);
	usleep_range(200, 300);

	/* Enable GCC_WDSP_Q6SS_AHBS_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->gcc_abhs_cbcr);
	अगर (ret)
		वापस ret;

	/* Remove reset to the WCNSS QDSP6SS */
	reset_control_deनिश्चित(wcss->wcss_q6_bcr_reset);

	/* Enable Q6SSTOP_AHBFABRIC_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->ahbfabric_cbcr_clk);
	अगर (ret)
		जाओ disable_gcc_abhs_cbcr_clk;

	/* Enable the LCCCSR CBC घड़ी, Q6SSTOP_Q6SSTOP_LCC_CSR_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->lcc_csr_cbcr);
	अगर (ret)
		जाओ disable_ahbfabric_cbcr_clk;

	/* Enable the Q6AHBS CBC, Q6SSTOP_Q6SS_AHBS_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->ahbs_cbcr);
	अगर (ret)
		जाओ disable_csr_cbcr_clk;

	/* Enable the TCM slave CBC, Q6SSTOP_Q6SS_TCM_SLAVE_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->tcm_slave_cbcr);
	अगर (ret)
		जाओ disable_ahbs_cbcr_clk;

	/* Enable the Q6SS AHB master CBC, Q6SSTOP_Q6SS_AHBM_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->qdsp6ss_abhm_cbcr);
	अगर (ret)
		जाओ disable_tcm_slave_cbcr_clk;

	/* Enable the Q6SS AXI master CBC, Q6SSTOP_Q6SS_AXIM_CBCR घड़ी */
	ret = clk_prepare_enable(wcss->qdsp6ss_axim_cbcr);
	अगर (ret)
		जाओ disable_abhm_cbcr_clk;

	/* Enable the Q6SS XO CBC */
	val = पढ़ोl(wcss->reg_base + Q6SS_XO_CBCR);
	val |= BIT(0);
	ग_लिखोl(val, wcss->reg_base + Q6SS_XO_CBCR);
	/* Read CLKOFF bit to go low indicating CLK is enabled */
	ret = पढ़ोl_poll_समयout(wcss->reg_base + Q6SS_XO_CBCR,
				 val, !(val & BIT(31)), 1,
				 HALT_CHECK_MAX_LOOPS);
	अगर (ret) अणु
		dev_err(wcss->dev,
			"xo cbcr enabling timed out (rc:%d)\n", ret);
		वापस ret;
	पूर्ण

	ग_लिखोl(0, wcss->reg_base + Q6SS_CGC_OVERRIDE);

	/* Enable QDSP6 sleep घड़ी घड़ी */
	val = पढ़ोl(wcss->reg_base + Q6SS_SLEEP_CBCR);
	val |= BIT(0);
	ग_लिखोl(val, wcss->reg_base + Q6SS_SLEEP_CBCR);

	/* Enable the Enable the Q6 AXI घड़ी, GCC_WDSP_Q6SS_AXIM_CBCR*/
	ret = clk_prepare_enable(wcss->gcc_axim_cbcr);
	अगर (ret)
		जाओ disable_sleep_cbcr_clk;

	/* Assert resets, stop core */
	val = पढ़ोl(wcss->reg_base + Q6SS_RESET_REG);
	val |= Q6SS_CORE_ARES | Q6SS_BUS_ARES_ENABLE | Q6SS_STOP_CORE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_RESET_REG);

	/* Program the QDSP6SS PWR_CTL रेजिस्टर */
	ग_लिखोl(0x01700000, wcss->reg_base + Q6SS_PWR_CTL_REG);

	ग_लिखोl(0x03700000, wcss->reg_base + Q6SS_PWR_CTL_REG);

	ग_लिखोl(0x03300000, wcss->reg_base + Q6SS_PWR_CTL_REG);

	ग_लिखोl(0x033C0000, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/*
	 * Enable memories by turning on the QDSP6 memory foot/head चयन, one
	 * bank at a समय to aव्योम in-rush current
	 */
	क्रम (idx = 28; idx >= 0; idx--) अणु
		ग_लिखोl((पढ़ोl(wcss->reg_base + Q6SS_MEM_PWR_CTL) |
			(1 << idx)), wcss->reg_base + Q6SS_MEM_PWR_CTL);
	पूर्ण

	ग_लिखोl(0x031C0000, wcss->reg_base + Q6SS_PWR_CTL_REG);
	ग_लिखोl(0x030C0000, wcss->reg_base + Q6SS_PWR_CTL_REG);

	val = पढ़ोl(wcss->reg_base + Q6SS_RESET_REG);
	val &= ~Q6SS_CORE_ARES;
	ग_लिखोl(val, wcss->reg_base + Q6SS_RESET_REG);

	/* Enable the Q6 core घड़ी at the GFM, Q6SSTOP_QDSP6SS_GFMUX_CTL */
	val = पढ़ोl(wcss->reg_base + Q6SS_GFMUX_CTL_REG);
	val |= Q6SS_CLK_ENABLE | Q6SS_SWITCH_CLK_SRC;
	ग_लिखोl(val, wcss->reg_base + Q6SS_GFMUX_CTL_REG);

	/* Enable sleep घड़ी branch needed क्रम BCR circuit */
	ret = clk_prepare_enable(wcss->lcc_bcr_sleep);
	अगर (ret)
		जाओ disable_core_gfmux_clk;

	वापस 0;

disable_core_gfmux_clk:
	val = पढ़ोl(wcss->reg_base + Q6SS_GFMUX_CTL_REG);
	val &= ~(Q6SS_CLK_ENABLE | Q6SS_SWITCH_CLK_SRC);
	ग_लिखोl(val, wcss->reg_base + Q6SS_GFMUX_CTL_REG);
	clk_disable_unprepare(wcss->gcc_axim_cbcr);
disable_sleep_cbcr_clk:
	val = पढ़ोl(wcss->reg_base + Q6SS_SLEEP_CBCR);
	val &= ~Q6SS_CLK_ENABLE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_SLEEP_CBCR);
	val = पढ़ोl(wcss->reg_base + Q6SS_XO_CBCR);
	val &= ~Q6SS_CLK_ENABLE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_XO_CBCR);
	clk_disable_unprepare(wcss->qdsp6ss_axim_cbcr);
disable_abhm_cbcr_clk:
	clk_disable_unprepare(wcss->qdsp6ss_abhm_cbcr);
disable_tcm_slave_cbcr_clk:
	clk_disable_unprepare(wcss->tcm_slave_cbcr);
disable_ahbs_cbcr_clk:
	clk_disable_unprepare(wcss->ahbs_cbcr);
disable_csr_cbcr_clk:
	clk_disable_unprepare(wcss->lcc_csr_cbcr);
disable_ahbfabric_cbcr_clk:
	clk_disable_unprepare(wcss->ahbfabric_cbcr_clk);
disable_gcc_abhs_cbcr_clk:
	clk_disable_unprepare(wcss->gcc_abhs_cbcr);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक q6v5_wcss_qcs404_reset(काष्ठा q6v5_wcss *wcss)
अणु
	अचिन्हित दीर्घ val;

	ग_लिखोl(0x80800000, wcss->reg_base + Q6SS_STRAP_ACC);

	/* Start core execution */
	val = पढ़ोl(wcss->reg_base + Q6SS_RESET_REG);
	val &= ~Q6SS_STOP_CORE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_RESET_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_qcs404_wcss_start(काष्ठा rproc *rproc)
अणु
	काष्ठा q6v5_wcss *wcss = rproc->priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(wcss->xo);
	अगर (ret)
		वापस ret;

	ret = regulator_enable(wcss->cx_supply);
	अगर (ret)
		जाओ disable_xo_clk;

	qcom_q6v5_prepare(&wcss->q6v5);

	ret = q6v5_wcss_qcs404_घातer_on(wcss);
	अगर (ret) अणु
		dev_err(wcss->dev, "wcss clk_enable failed\n");
		जाओ disable_cx_supply;
	पूर्ण

	ग_लिखोl(rproc->bootaddr >> 4, wcss->reg_base + Q6SS_RST_EVB);

	q6v5_wcss_qcs404_reset(wcss);

	ret = qcom_q6v5_रुको_क्रम_start(&wcss->q6v5, 5 * HZ);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(wcss->dev, "start timed out\n");
		जाओ disable_cx_supply;
	पूर्ण

	वापस 0;

disable_cx_supply:
	regulator_disable(wcss->cx_supply);
disable_xo_clk:
	clk_disable_unprepare(wcss->xo);

	वापस ret;
पूर्ण

अटल व्योम q6v5_wcss_halt_axi_port(काष्ठा q6v5_wcss *wcss,
				    काष्ठा regmap *halt_map,
				    u32 offset)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Check अगर we're alपढ़ोy idle */
	ret = regmap_पढ़ो(halt_map, offset + AXI_IDLE_REG, &val);
	अगर (!ret && val)
		वापस;

	/* Assert halt request */
	regmap_ग_लिखो(halt_map, offset + AXI_HALTREQ_REG, 1);

	/* Wait क्रम halt */
	समयout = jअगरfies + msecs_to_jअगरfies(HALT_ACK_TIMEOUT_MS);
	क्रम (;;) अणु
		ret = regmap_पढ़ो(halt_map, offset + AXI_HALTACK_REG, &val);
		अगर (ret || val || समय_after(jअगरfies, समयout))
			अवरोध;

		msleep(1);
	पूर्ण

	ret = regmap_पढ़ो(halt_map, offset + AXI_IDLE_REG, &val);
	अगर (ret || !val)
		dev_err(wcss->dev, "port failed halt\n");

	/* Clear halt request (port will reमुख्य halted until reset) */
	regmap_ग_लिखो(halt_map, offset + AXI_HALTREQ_REG, 0);
पूर्ण

अटल पूर्णांक q6v5_qcs404_wcss_shutकरोwn(काष्ठा q6v5_wcss *wcss)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	q6v5_wcss_halt_axi_port(wcss, wcss->halt_map, wcss->halt_wcss);

	/* निश्चित clamps to aव्योम MX current inrush */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val |= (Q6SS_CLAMP_IO | Q6SS_CLAMP_WL | Q6SS_CLAMP_QMC_MEM);
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* Disable memories by turning off memory foot/headचयन */
	ग_लिखोl((पढ़ोl(wcss->reg_base + Q6SS_MEM_PWR_CTL) &
		~QDSS_Q6_MEMORIES),
		wcss->reg_base + Q6SS_MEM_PWR_CTL);

	/* Clear the BHS_ON bit */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val &= ~Q6SS_BHS_ON;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	clk_disable_unprepare(wcss->ahbfabric_cbcr_clk);
	clk_disable_unprepare(wcss->lcc_csr_cbcr);
	clk_disable_unprepare(wcss->tcm_slave_cbcr);
	clk_disable_unprepare(wcss->qdsp6ss_abhm_cbcr);
	clk_disable_unprepare(wcss->qdsp6ss_axim_cbcr);

	val = पढ़ोl(wcss->reg_base + Q6SS_SLEEP_CBCR);
	val &= ~BIT(0);
	ग_लिखोl(val, wcss->reg_base + Q6SS_SLEEP_CBCR);

	val = पढ़ोl(wcss->reg_base + Q6SS_XO_CBCR);
	val &= ~BIT(0);
	ग_लिखोl(val, wcss->reg_base + Q6SS_XO_CBCR);

	clk_disable_unprepare(wcss->ahbs_cbcr);
	clk_disable_unprepare(wcss->lcc_bcr_sleep);

	val = पढ़ोl(wcss->reg_base + Q6SS_GFMUX_CTL_REG);
	val &= ~(Q6SS_CLK_ENABLE | Q6SS_SWITCH_CLK_SRC);
	ग_लिखोl(val, wcss->reg_base + Q6SS_GFMUX_CTL_REG);

	clk_disable_unprepare(wcss->gcc_abhs_cbcr);

	ret = reset_control_निश्चित(wcss->wcss_reset);
	अगर (ret) अणु
		dev_err(wcss->dev, "wcss_reset failed\n");
		वापस ret;
	पूर्ण
	usleep_range(200, 300);

	ret = reset_control_deनिश्चित(wcss->wcss_reset);
	अगर (ret) अणु
		dev_err(wcss->dev, "wcss_reset failed\n");
		वापस ret;
	पूर्ण
	usleep_range(200, 300);

	clk_disable_unprepare(wcss->gcc_axim_cbcr);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_घातerकरोwn(काष्ठा q6v5_wcss *wcss)
अणु
	पूर्णांक ret;
	u32 val;

	/* 1 - Assert WCSS/Q6 HALTREQ */
	q6v5_wcss_halt_axi_port(wcss, wcss->halt_map, wcss->halt_wcss);

	/* 2 - Enable WCSSAON_CONFIG */
	val = पढ़ोl(wcss->rmb_base + SSCAON_CONFIG);
	val |= SSCAON_ENABLE;
	ग_लिखोl(val, wcss->rmb_base + SSCAON_CONFIG);

	/* 3 - Set SSCAON_CONFIG */
	val |= SSCAON_BUS_EN;
	val &= ~SSCAON_BUS_MUX_MASK;
	ग_लिखोl(val, wcss->rmb_base + SSCAON_CONFIG);

	/* 4 - SSCAON_CONFIG 1 */
	val |= BIT(1);
	ग_लिखोl(val, wcss->rmb_base + SSCAON_CONFIG);

	/* 5 - रुको क्रम SSCAON_STATUS */
	ret = पढ़ोl_poll_समयout(wcss->rmb_base + SSCAON_STATUS,
				 val, (val & 0xffff) == 0x400, 1000,
				 HALT_CHECK_MAX_LOOPS);
	अगर (ret) अणु
		dev_err(wcss->dev,
			"can't get SSCAON_STATUS rc:%d)\n", ret);
		वापस ret;
	पूर्ण

	/* 6 - De-निश्चित WCSS_AON reset */
	reset_control_निश्चित(wcss->wcss_aon_reset);

	/* 7 - Disable WCSSAON_CONFIG 13 */
	val = पढ़ोl(wcss->rmb_base + SSCAON_CONFIG);
	val &= ~SSCAON_ENABLE;
	ग_लिखोl(val, wcss->rmb_base + SSCAON_CONFIG);

	/* 8 - De-निश्चित WCSS/Q6 HALTREQ */
	reset_control_निश्चित(wcss->wcss_reset);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_q6_घातerकरोwn(काष्ठा q6v5_wcss *wcss)
अणु
	पूर्णांक ret;
	u32 val;
	पूर्णांक i;

	/* 1 - Halt Q6 bus पूर्णांकerface */
	q6v5_wcss_halt_axi_port(wcss, wcss->halt_map, wcss->halt_q6);

	/* 2 - Disable Q6 Core घड़ी */
	val = पढ़ोl(wcss->reg_base + Q6SS_GFMUX_CTL_REG);
	val &= ~Q6SS_CLK_ENABLE;
	ग_लिखोl(val, wcss->reg_base + Q6SS_GFMUX_CTL_REG);

	/* 3 - Clamp I/O */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val |= Q6SS_CLAMP_IO;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* 4 - Clamp WL */
	val |= QDSS_BHS_ON;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* 5 - Clear Erase standby */
	val &= ~Q6SS_L2DATA_STBY_N;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* 6 - Clear Sleep RTN */
	val &= ~Q6SS_SLP_RET_N;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* 7 - turn off Q6 memory foot/head चयन one bank at a समय */
	क्रम (i = 0; i < 20; i++) अणु
		val = पढ़ोl(wcss->reg_base + Q6SS_MEM_PWR_CTL);
		val &= ~BIT(i);
		ग_लिखोl(val, wcss->reg_base + Q6SS_MEM_PWR_CTL);
		mdelay(1);
	पूर्ण

	/* 8 - Assert QMC memory RTN */
	val = पढ़ोl(wcss->reg_base + Q6SS_PWR_CTL_REG);
	val |= Q6SS_CLAMP_QMC_MEM;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);

	/* 9 - Turn off BHS */
	val &= ~Q6SS_BHS_ON;
	ग_लिखोl(val, wcss->reg_base + Q6SS_PWR_CTL_REG);
	udelay(1);

	/* 10 - Wait till BHS Reset is करोne */
	ret = पढ़ोl_poll_समयout(wcss->reg_base + Q6SS_BHS_STATUS,
				 val, !(val & BHS_EN_REST_ACK), 1000,
				 HALT_CHECK_MAX_LOOPS);
	अगर (ret) अणु
		dev_err(wcss->dev, "BHS_STATUS not OFF (rc:%d)\n", ret);
		वापस ret;
	पूर्ण

	/* 11 -  Assert WCSS reset */
	reset_control_निश्चित(wcss->wcss_reset);

	/* 12 - Assert Q6 reset */
	reset_control_निश्चित(wcss->wcss_q6_reset);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा q6v5_wcss *wcss = rproc->priv;
	पूर्णांक ret;

	/* WCSS घातerकरोwn */
	अगर (wcss->requires_क्रमce_stop) अणु
		ret = qcom_q6v5_request_stop(&wcss->q6v5, शून्य);
		अगर (ret == -ETIMEDOUT) अणु
			dev_err(wcss->dev, "timed out on wait\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (wcss->version == WCSS_QCS404) अणु
		ret = q6v5_qcs404_wcss_shutकरोwn(wcss);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = q6v5_wcss_घातerकरोwn(wcss);
		अगर (ret)
			वापस ret;

		/* Q6 Power करोwn */
		ret = q6v5_q6_घातerकरोwn(wcss);
		अगर (ret)
			वापस ret;
	पूर्ण

	qcom_q6v5_unprepare(&wcss->q6v5);

	वापस 0;
पूर्ण

अटल व्योम *q6v5_wcss_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा q6v5_wcss *wcss = rproc->priv;
	पूर्णांक offset;

	offset = da - wcss->mem_reloc;
	अगर (offset < 0 || offset + len > wcss->mem_size)
		वापस शून्य;

	वापस wcss->mem_region + offset;
पूर्ण

अटल पूर्णांक q6v5_wcss_load(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा q6v5_wcss *wcss = rproc->priv;
	पूर्णांक ret;

	ret = qcom_mdt_load_no_init(wcss->dev, fw, rproc->firmware,
				    0, wcss->mem_region, wcss->mem_phys,
				    wcss->mem_size, &wcss->mem_reloc);
	अगर (ret)
		वापस ret;

	qcom_pil_info_store("wcnss", wcss->mem_phys, wcss->mem_size);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rproc_ops q6v5_wcss_ipq8074_ops = अणु
	.start = q6v5_wcss_start,
	.stop = q6v5_wcss_stop,
	.da_to_va = q6v5_wcss_da_to_va,
	.load = q6v5_wcss_load,
	.get_boot_addr = rproc_elf_get_boot_addr,
पूर्ण;

अटल स्थिर काष्ठा rproc_ops q6v5_wcss_qcs404_ops = अणु
	.start = q6v5_qcs404_wcss_start,
	.stop = q6v5_wcss_stop,
	.da_to_va = q6v5_wcss_da_to_va,
	.load = q6v5_wcss_load,
	.get_boot_addr = rproc_elf_get_boot_addr,
	.parse_fw = qcom_रेजिस्टर_dump_segments,
पूर्ण;

अटल पूर्णांक q6v5_wcss_init_reset(काष्ठा q6v5_wcss *wcss,
				स्थिर काष्ठा wcss_data *desc)
अणु
	काष्ठा device *dev = wcss->dev;

	अगर (desc->aon_reset_required) अणु
		wcss->wcss_aon_reset = devm_reset_control_get_exclusive(dev, "wcss_aon_reset");
		अगर (IS_ERR(wcss->wcss_aon_reset)) अणु
			dev_err(wcss->dev, "fail to acquire wcss_aon_reset\n");
			वापस PTR_ERR(wcss->wcss_aon_reset);
		पूर्ण
	पूर्ण

	wcss->wcss_reset = devm_reset_control_get_exclusive(dev, "wcss_reset");
	अगर (IS_ERR(wcss->wcss_reset)) अणु
		dev_err(wcss->dev, "unable to acquire wcss_reset\n");
		वापस PTR_ERR(wcss->wcss_reset);
	पूर्ण

	अगर (desc->wcss_q6_reset_required) अणु
		wcss->wcss_q6_reset = devm_reset_control_get_exclusive(dev, "wcss_q6_reset");
		अगर (IS_ERR(wcss->wcss_q6_reset)) अणु
			dev_err(wcss->dev, "unable to acquire wcss_q6_reset\n");
			वापस PTR_ERR(wcss->wcss_q6_reset);
		पूर्ण
	पूर्ण

	wcss->wcss_q6_bcr_reset = devm_reset_control_get_exclusive(dev, "wcss_q6_bcr_reset");
	अगर (IS_ERR(wcss->wcss_q6_bcr_reset)) अणु
		dev_err(wcss->dev, "unable to acquire wcss_q6_bcr_reset\n");
		वापस PTR_ERR(wcss->wcss_q6_bcr_reset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_init_mmio(काष्ठा q6v5_wcss *wcss,
			       काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक halt_reg[MAX_HALT_REG] = अणु0पूर्ण;
	काष्ठा device_node *syscon;
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qdsp6");
	wcss->reg_base = devm_ioremap(&pdev->dev, res->start,
				      resource_size(res));
	अगर (!wcss->reg_base)
		वापस -ENOMEM;

	अगर (wcss->version == WCSS_IPQ8074) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rmb");
		wcss->rmb_base = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(wcss->rmb_base))
			वापस PTR_ERR(wcss->rmb_base);
	पूर्ण

	syscon = of_parse_phandle(pdev->dev.of_node,
				  "qcom,halt-regs", 0);
	अगर (!syscon) अणु
		dev_err(&pdev->dev, "failed to parse qcom,halt-regs\n");
		वापस -EINVAL;
	पूर्ण

	wcss->halt_map = syscon_node_to_regmap(syscon);
	of_node_put(syscon);
	अगर (IS_ERR(wcss->halt_map))
		वापस PTR_ERR(wcss->halt_map);

	ret = of_property_पढ़ो_variable_u32_array(pdev->dev.of_node,
						  "qcom,halt-regs",
						  halt_reg, 0,
						  MAX_HALT_REG);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to parse qcom,halt-regs\n");
		वापस -EINVAL;
	पूर्ण

	wcss->halt_q6 = halt_reg[0];
	wcss->halt_wcss = halt_reg[1];
	wcss->halt_nc = halt_reg[2];

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_alloc_memory_region(काष्ठा q6v5_wcss *wcss)
अणु
	काष्ठा reserved_mem *rmem = शून्य;
	काष्ठा device_node *node;
	काष्ठा device *dev = wcss->dev;

	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (node)
		rmem = of_reserved_mem_lookup(node);
	of_node_put(node);

	अगर (!rmem) अणु
		dev_err(dev, "unable to acquire memory-region\n");
		वापस -EINVAL;
	पूर्ण

	wcss->mem_phys = rmem->base;
	wcss->mem_reloc = rmem->base;
	wcss->mem_size = rmem->size;
	wcss->mem_region = devm_ioremap_wc(dev, wcss->mem_phys, wcss->mem_size);
	अगर (!wcss->mem_region) अणु
		dev_err(dev, "unable to map memory region: %pa+%pa\n",
			&rmem->base, &rmem->size);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_init_घड़ी(काष्ठा q6v5_wcss *wcss)
अणु
	पूर्णांक ret;

	wcss->xo = devm_clk_get(wcss->dev, "xo");
	अगर (IS_ERR(wcss->xo)) अणु
		ret = PTR_ERR(wcss->xo);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get xo clock");
		वापस ret;
	पूर्ण

	wcss->gcc_abhs_cbcr = devm_clk_get(wcss->dev, "gcc_abhs_cbcr");
	अगर (IS_ERR(wcss->gcc_abhs_cbcr)) अणु
		ret = PTR_ERR(wcss->gcc_abhs_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get gcc abhs clock");
		वापस ret;
	पूर्ण

	wcss->gcc_axim_cbcr = devm_clk_get(wcss->dev, "gcc_axim_cbcr");
	अगर (IS_ERR(wcss->gcc_axim_cbcr)) अणु
		ret = PTR_ERR(wcss->gcc_axim_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get gcc axim clock\n");
		वापस ret;
	पूर्ण

	wcss->ahbfabric_cbcr_clk = devm_clk_get(wcss->dev,
						"lcc_ahbfabric_cbc");
	अगर (IS_ERR(wcss->ahbfabric_cbcr_clk)) अणु
		ret = PTR_ERR(wcss->ahbfabric_cbcr_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get ahbfabric clock\n");
		वापस ret;
	पूर्ण

	wcss->lcc_csr_cbcr = devm_clk_get(wcss->dev, "tcsr_lcc_cbc");
	अगर (IS_ERR(wcss->lcc_csr_cbcr)) अणु
		ret = PTR_ERR(wcss->lcc_csr_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get csr cbcr clk\n");
		वापस ret;
	पूर्ण

	wcss->ahbs_cbcr = devm_clk_get(wcss->dev,
				       "lcc_abhs_cbc");
	अगर (IS_ERR(wcss->ahbs_cbcr)) अणु
		ret = PTR_ERR(wcss->ahbs_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get ahbs_cbcr clk\n");
		वापस ret;
	पूर्ण

	wcss->tcm_slave_cbcr = devm_clk_get(wcss->dev,
					    "lcc_tcm_slave_cbc");
	अगर (IS_ERR(wcss->tcm_slave_cbcr)) अणु
		ret = PTR_ERR(wcss->tcm_slave_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get tcm cbcr clk\n");
		वापस ret;
	पूर्ण

	wcss->qdsp6ss_abhm_cbcr = devm_clk_get(wcss->dev, "lcc_abhm_cbc");
	अगर (IS_ERR(wcss->qdsp6ss_abhm_cbcr)) अणु
		ret = PTR_ERR(wcss->qdsp6ss_abhm_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get abhm cbcr clk\n");
		वापस ret;
	पूर्ण

	wcss->qdsp6ss_axim_cbcr = devm_clk_get(wcss->dev, "lcc_axim_cbc");
	अगर (IS_ERR(wcss->qdsp6ss_axim_cbcr)) अणु
		ret = PTR_ERR(wcss->qdsp6ss_axim_cbcr);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get axim cbcr clk\n");
		वापस ret;
	पूर्ण

	wcss->lcc_bcr_sleep = devm_clk_get(wcss->dev, "lcc_bcr_sleep");
	अगर (IS_ERR(wcss->lcc_bcr_sleep)) अणु
		ret = PTR_ERR(wcss->lcc_bcr_sleep);
		अगर (ret != -EPROBE_DEFER)
			dev_err(wcss->dev, "failed to get bcr cbcr clk\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_init_regulator(काष्ठा q6v5_wcss *wcss)
अणु
	wcss->cx_supply = devm_regulator_get(wcss->dev, "cx");
	अगर (IS_ERR(wcss->cx_supply))
		वापस PTR_ERR(wcss->cx_supply);

	regulator_set_load(wcss->cx_supply, 100000);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_wcss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा wcss_data *desc;
	काष्ठा q6v5_wcss *wcss;
	काष्ठा rproc *rproc;
	पूर्णांक ret;

	desc = device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	rproc = rproc_alloc(&pdev->dev, pdev->name, desc->ops,
			    desc->firmware_name, माप(*wcss));
	अगर (!rproc) अणु
		dev_err(&pdev->dev, "failed to allocate rproc\n");
		वापस -ENOMEM;
	पूर्ण

	wcss = rproc->priv;
	wcss->dev = &pdev->dev;
	wcss->version = desc->version;

	wcss->version = desc->version;
	wcss->requires_क्रमce_stop = desc->requires_क्रमce_stop;

	ret = q6v5_wcss_init_mmio(wcss, pdev);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = q6v5_alloc_memory_region(wcss);
	अगर (ret)
		जाओ मुक्त_rproc;

	अगर (wcss->version == WCSS_QCS404) अणु
		ret = q6v5_wcss_init_घड़ी(wcss);
		अगर (ret)
			जाओ मुक्त_rproc;

		ret = q6v5_wcss_init_regulator(wcss);
		अगर (ret)
			जाओ मुक्त_rproc;
	पूर्ण

	ret = q6v5_wcss_init_reset(wcss, desc);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = qcom_q6v5_init(&wcss->q6v5, pdev, rproc, desc->crash_reason_smem,
			     शून्य);
	अगर (ret)
		जाओ मुक्त_rproc;

	qcom_add_glink_subdev(rproc, &wcss->glink_subdev, "q6wcss");
	qcom_add_ssr_subdev(rproc, &wcss->ssr_subdev, "q6wcss");

	अगर (desc->ssctl_id)
		wcss->sysmon = qcom_add_sysmon_subdev(rproc,
						      desc->sysmon_name,
						      desc->ssctl_id);

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	platक्रमm_set_drvdata(pdev, rproc);

	वापस 0;

मुक्त_rproc:
	rproc_मुक्त(rproc);

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_wcss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);

	rproc_del(rproc);
	rproc_मुक्त(rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wcss_data wcss_ipq8074_res_init = अणु
	.firmware_name = "IPQ8074/q6_fw.mdt",
	.crash_reason_smem = WCSS_CRASH_REASON,
	.aon_reset_required = true,
	.wcss_q6_reset_required = true,
	.ops = &q6v5_wcss_ipq8074_ops,
	.requires_क्रमce_stop = true,
पूर्ण;

अटल स्थिर काष्ठा wcss_data wcss_qcs404_res_init = अणु
	.crash_reason_smem = WCSS_CRASH_REASON,
	.firmware_name = "wcnss.mdt",
	.version = WCSS_QCS404,
	.aon_reset_required = false,
	.wcss_q6_reset_required = false,
	.ssr_name = "mpss",
	.sysmon_name = "wcnss",
	.ssctl_id = 0x12,
	.ops = &q6v5_wcss_qcs404_ops,
	.requires_क्रमce_stop = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id q6v5_wcss_of_match[] = अणु
	अणु .compatible = "qcom,ipq8074-wcss-pil", .data = &wcss_ipq8074_res_init पूर्ण,
	अणु .compatible = "qcom,qcs404-wcss-pil", .data = &wcss_qcs404_res_init पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6v5_wcss_of_match);

अटल काष्ठा platक्रमm_driver q6v5_wcss_driver = अणु
	.probe = q6v5_wcss_probe,
	.हटाओ = q6v5_wcss_हटाओ,
	.driver = अणु
		.name = "qcom-q6v5-wcss-pil",
		.of_match_table = q6v5_wcss_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(q6v5_wcss_driver);

MODULE_DESCRIPTION("Hexagon WCSS Peripheral Image Loader");
MODULE_LICENSE("GPL v2");
