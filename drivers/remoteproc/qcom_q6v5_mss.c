<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm self-authenticating modem subप्रणाली remoteproc driver
 *
 * Copyright (C) 2016 Linaro Ltd.
 * Copyright (C) 2014 Sony Mobile Communications AB
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>
#समावेश <linux/soc/qcom/mdt_loader.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>

#समावेश "remoteproc_internal.h"
#समावेश "qcom_common.h"
#समावेश "qcom_pil_info.h"
#समावेश "qcom_q6v5.h"

#समावेश <linux/qcom_scm.h>

#घोषणा MPSS_CRASH_REASON_SMEM		421

#घोषणा MBA_LOG_SIZE			SZ_4K

/* RMB Status Register Values */
#घोषणा RMB_PBL_SUCCESS			0x1

#घोषणा RMB_MBA_XPU_UNLOCKED		0x1
#घोषणा RMB_MBA_XPU_UNLOCKED_SCRIBBLED	0x2
#घोषणा RMB_MBA_META_DATA_AUTH_SUCCESS	0x3
#घोषणा RMB_MBA_AUTH_COMPLETE		0x4

/* PBL/MBA पूर्णांकerface रेजिस्टरs */
#घोषणा RMB_MBA_IMAGE_REG		0x00
#घोषणा RMB_PBL_STATUS_REG		0x04
#घोषणा RMB_MBA_COMMAND_REG		0x08
#घोषणा RMB_MBA_STATUS_REG		0x0C
#घोषणा RMB_PMI_META_DATA_REG		0x10
#घोषणा RMB_PMI_CODE_START_REG		0x14
#घोषणा RMB_PMI_CODE_LENGTH_REG		0x18
#घोषणा RMB_MBA_MSS_STATUS		0x40
#घोषणा RMB_MBA_ALT_RESET		0x44

#घोषणा RMB_CMD_META_DATA_READY		0x1
#घोषणा RMB_CMD_LOAD_READY		0x2

/* QDSP6SS Register Offsets */
#घोषणा QDSP6SS_RESET_REG		0x014
#घोषणा QDSP6SS_GFMUX_CTL_REG		0x020
#घोषणा QDSP6SS_PWR_CTL_REG		0x030
#घोषणा QDSP6SS_MEM_PWR_CTL		0x0B0
#घोषणा QDSP6V6SS_MEM_PWR_CTL		0x034
#घोषणा QDSP6SS_STRAP_ACC		0x110

/* AXI Halt Register Offsets */
#घोषणा AXI_HALTREQ_REG			0x0
#घोषणा AXI_HALTACK_REG			0x4
#घोषणा AXI_IDLE_REG			0x8
#घोषणा AXI_GATING_VALID_OVERRIDE	BIT(0)

#घोषणा HALT_ACK_TIMEOUT_US		100000

/* QDSP6SS_RESET */
#घोषणा Q6SS_STOP_CORE			BIT(0)
#घोषणा Q6SS_CORE_ARES			BIT(1)
#घोषणा Q6SS_BUS_ARES_ENABLE		BIT(2)

/* QDSP6SS CBCR */
#घोषणा Q6SS_CBCR_CLKEN			BIT(0)
#घोषणा Q6SS_CBCR_CLKOFF		BIT(31)
#घोषणा Q6SS_CBCR_TIMEOUT_US		200

/* QDSP6SS_GFMUX_CTL */
#घोषणा Q6SS_CLK_ENABLE			BIT(1)

/* QDSP6SS_PWR_CTL */
#घोषणा Q6SS_L2DATA_SLP_NRET_N_0	BIT(0)
#घोषणा Q6SS_L2DATA_SLP_NRET_N_1	BIT(1)
#घोषणा Q6SS_L2DATA_SLP_NRET_N_2	BIT(2)
#घोषणा Q6SS_L2TAG_SLP_NRET_N		BIT(16)
#घोषणा Q6SS_ETB_SLP_NRET_N		BIT(17)
#घोषणा Q6SS_L2DATA_STBY_N		BIT(18)
#घोषणा Q6SS_SLP_RET_N			BIT(19)
#घोषणा Q6SS_CLAMP_IO			BIT(20)
#घोषणा QDSS_BHS_ON			BIT(21)
#घोषणा QDSS_LDO_BYP			BIT(22)

/* QDSP6v56 parameters */
#घोषणा QDSP6v56_LDO_BYP		BIT(25)
#घोषणा QDSP6v56_BHS_ON		BIT(24)
#घोषणा QDSP6v56_CLAMP_WL		BIT(21)
#घोषणा QDSP6v56_CLAMP_QMC_MEM		BIT(22)
#घोषणा QDSP6SS_XO_CBCR		0x0038
#घोषणा QDSP6SS_ACC_OVERRIDE_VAL		0x20

/* QDSP6v65 parameters */
#घोषणा QDSP6SS_CORE_CBCR		0x20
#घोषणा QDSP6SS_SLEEP                   0x3C
#घोषणा QDSP6SS_BOOT_CORE_START         0x400
#घोषणा QDSP6SS_BOOT_CMD                0x404
#घोषणा BOOT_FSM_TIMEOUT                10000

काष्ठा reg_info अणु
	काष्ठा regulator *reg;
	पूर्णांक uV;
	पूर्णांक uA;
पूर्ण;

काष्ठा qcom_mss_reg_res अणु
	स्थिर अक्षर *supply;
	पूर्णांक uV;
	पूर्णांक uA;
पूर्ण;

काष्ठा rproc_hexagon_res अणु
	स्थिर अक्षर *hexagon_mba_image;
	काष्ठा qcom_mss_reg_res *proxy_supply;
	काष्ठा qcom_mss_reg_res *fallback_proxy_supply;
	काष्ठा qcom_mss_reg_res *active_supply;
	अक्षर **proxy_clk_names;
	अक्षर **reset_clk_names;
	अक्षर **active_clk_names;
	अक्षर **active_pd_names;
	अक्षर **proxy_pd_names;
	पूर्णांक version;
	bool need_mem_protection;
	bool has_alt_reset;
	bool has_mba_logs;
	bool has_spare_reg;
पूर्ण;

काष्ठा q6v5 अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;

	व्योम __iomem *reg_base;
	व्योम __iomem *rmb_base;

	काष्ठा regmap *halt_map;
	काष्ठा regmap *conn_map;

	u32 halt_q6;
	u32 halt_modem;
	u32 halt_nc;
	u32 conn_box;

	काष्ठा reset_control *mss_restart;
	काष्ठा reset_control *pdc_reset;

	काष्ठा qcom_q6v5 q6v5;

	काष्ठा clk *active_clks[8];
	काष्ठा clk *reset_clks[4];
	काष्ठा clk *proxy_clks[4];
	काष्ठा device *active_pds[1];
	काष्ठा device *proxy_pds[3];
	पूर्णांक active_clk_count;
	पूर्णांक reset_clk_count;
	पूर्णांक proxy_clk_count;
	पूर्णांक active_pd_count;
	पूर्णांक proxy_pd_count;

	काष्ठा reg_info active_regs[1];
	काष्ठा reg_info proxy_regs[1];
	काष्ठा reg_info fallback_proxy_regs[2];
	पूर्णांक active_reg_count;
	पूर्णांक proxy_reg_count;
	पूर्णांक fallback_proxy_reg_count;

	bool dump_mba_loaded;
	माप_प्रकार current_dump_size;
	माप_प्रकार total_dump_size;

	phys_addr_t mba_phys;
	माप_प्रकार mba_size;
	माप_प्रकार dp_size;

	phys_addr_t mpss_phys;
	phys_addr_t mpss_reloc;
	माप_प्रकार mpss_size;

	काष्ठा qcom_rproc_glink glink_subdev;
	काष्ठा qcom_rproc_subdev smd_subdev;
	काष्ठा qcom_rproc_ssr ssr_subdev;
	काष्ठा qcom_sysmon *sysmon;
	bool need_mem_protection;
	bool has_alt_reset;
	bool has_mba_logs;
	bool has_spare_reg;
	पूर्णांक mpss_perm;
	पूर्णांक mba_perm;
	स्थिर अक्षर *hexagon_mdt_image;
	पूर्णांक version;
पूर्ण;

क्रमागत अणु
	MSS_MSM8916,
	MSS_MSM8974,
	MSS_MSM8996,
	MSS_MSM8998,
	MSS_SC7180,
	MSS_SDM845,
पूर्ण;

अटल पूर्णांक q6v5_regulator_init(काष्ठा device *dev, काष्ठा reg_info *regs,
			       स्थिर काष्ठा qcom_mss_reg_res *reg_res)
अणु
	पूर्णांक rc;
	पूर्णांक i;

	अगर (!reg_res)
		वापस 0;

	क्रम (i = 0; reg_res[i].supply; i++) अणु
		regs[i].reg = devm_regulator_get(dev, reg_res[i].supply);
		अगर (IS_ERR(regs[i].reg)) अणु
			rc = PTR_ERR(regs[i].reg);
			अगर (rc != -EPROBE_DEFER)
				dev_err(dev, "Failed to get %s\n regulator",
					reg_res[i].supply);
			वापस rc;
		पूर्ण

		regs[i].uV = reg_res[i].uV;
		regs[i].uA = reg_res[i].uA;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक q6v5_regulator_enable(काष्ठा q6v5 *qproc,
				 काष्ठा reg_info *regs, पूर्णांक count)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (regs[i].uV > 0) अणु
			ret = regulator_set_voltage(regs[i].reg,
					regs[i].uV, पूर्णांक_उच्च);
			अगर (ret) अणु
				dev_err(qproc->dev,
					"Failed to request voltage for %d.\n",
						i);
				जाओ err;
			पूर्ण
		पूर्ण

		अगर (regs[i].uA > 0) अणु
			ret = regulator_set_load(regs[i].reg,
						 regs[i].uA);
			अगर (ret < 0) अणु
				dev_err(qproc->dev,
					"Failed to set regulator mode\n");
				जाओ err;
			पूर्ण
		पूर्ण

		ret = regulator_enable(regs[i].reg);
		अगर (ret) अणु
			dev_err(qproc->dev, "Regulator enable failed\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	क्रम (; i >= 0; i--) अणु
		अगर (regs[i].uV > 0)
			regulator_set_voltage(regs[i].reg, 0, पूर्णांक_उच्च);

		अगर (regs[i].uA > 0)
			regulator_set_load(regs[i].reg, 0);

		regulator_disable(regs[i].reg);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम q6v5_regulator_disable(काष्ठा q6v5 *qproc,
				   काष्ठा reg_info *regs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (regs[i].uV > 0)
			regulator_set_voltage(regs[i].reg, 0, पूर्णांक_उच्च);

		अगर (regs[i].uA > 0)
			regulator_set_load(regs[i].reg, 0);

		regulator_disable(regs[i].reg);
	पूर्ण
पूर्ण

अटल पूर्णांक q6v5_clk_enable(काष्ठा device *dev,
			   काष्ठा clk **clks, पूर्णांक count)
अणु
	पूर्णांक rc;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		rc = clk_prepare_enable(clks[i]);
		अगर (rc) अणु
			dev_err(dev, "Clock enable failed\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	क्रम (i--; i >= 0; i--)
		clk_disable_unprepare(clks[i]);

	वापस rc;
पूर्ण

अटल व्योम q6v5_clk_disable(काष्ठा device *dev,
			     काष्ठा clk **clks, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		clk_disable_unprepare(clks[i]);
पूर्ण

अटल पूर्णांक q6v5_pds_enable(काष्ठा q6v5 *qproc, काष्ठा device **pds,
			   माप_प्रकार pd_count)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < pd_count; i++) अणु
		dev_pm_genpd_set_perक्रमmance_state(pds[i], पूर्णांक_उच्च);
		ret = pm_runसमय_get_sync(pds[i]);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(pds[i]);
			dev_pm_genpd_set_perक्रमmance_state(pds[i], 0);
			जाओ unroll_pd_votes;
		पूर्ण
	पूर्ण

	वापस 0;

unroll_pd_votes:
	क्रम (i--; i >= 0; i--) अणु
		dev_pm_genpd_set_perक्रमmance_state(pds[i], 0);
		pm_runसमय_put(pds[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम q6v5_pds_disable(काष्ठा q6v5 *qproc, काष्ठा device **pds,
			     माप_प्रकार pd_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pd_count; i++) अणु
		dev_pm_genpd_set_perक्रमmance_state(pds[i], 0);
		pm_runसमय_put(pds[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक q6v5_xfer_mem_ownership(काष्ठा q6v5 *qproc, पूर्णांक *current_perm,
				   bool local, bool remote, phys_addr_t addr,
				   माप_प्रकार size)
अणु
	काष्ठा qcom_scm_vmperm next[2];
	पूर्णांक perms = 0;

	अगर (!qproc->need_mem_protection)
		वापस 0;

	अगर (local == !!(*current_perm & BIT(QCOM_SCM_VMID_HLOS)) &&
	    remote == !!(*current_perm & BIT(QCOM_SCM_VMID_MSS_MSA)))
		वापस 0;

	अगर (local) अणु
		next[perms].vmid = QCOM_SCM_VMID_HLOS;
		next[perms].perm = QCOM_SCM_PERM_RWX;
		perms++;
	पूर्ण

	अगर (remote) अणु
		next[perms].vmid = QCOM_SCM_VMID_MSS_MSA;
		next[perms].perm = QCOM_SCM_PERM_RW;
		perms++;
	पूर्ण

	वापस qcom_scm_assign_mem(addr, ALIGN(size, SZ_4K),
				   current_perm, next, perms);
पूर्ण

अटल व्योम q6v5_debug_policy_load(काष्ठा q6v5 *qproc, व्योम *mba_region)
अणु
	स्थिर काष्ठा firmware *dp_fw;

	अगर (request_firmware_direct(&dp_fw, "msadp", qproc->dev))
		वापस;

	अगर (SZ_1M + dp_fw->size <= qproc->mba_size) अणु
		स_नकल(mba_region + SZ_1M, dp_fw->data, dp_fw->size);
		qproc->dp_size = dp_fw->size;
	पूर्ण

	release_firmware(dp_fw);
पूर्ण

अटल पूर्णांक q6v5_load(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा q6v5 *qproc = rproc->priv;
	व्योम *mba_region;

	/* MBA is restricted to a maximum size of 1M */
	अगर (fw->size > qproc->mba_size || fw->size > SZ_1M) अणु
		dev_err(qproc->dev, "MBA firmware load failed\n");
		वापस -EINVAL;
	पूर्ण

	mba_region = memremap(qproc->mba_phys, qproc->mba_size, MEMREMAP_WC);
	अगर (!mba_region) अणु
		dev_err(qproc->dev, "unable to map memory region: %pa+%zx\n",
			&qproc->mba_phys, qproc->mba_size);
		वापस -EBUSY;
	पूर्ण

	स_नकल(mba_region, fw->data, fw->size);
	q6v5_debug_policy_load(qproc, mba_region);
	memunmap(mba_region);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_reset_निश्चित(काष्ठा q6v5 *qproc)
अणु
	पूर्णांक ret;

	अगर (qproc->has_alt_reset) अणु
		reset_control_निश्चित(qproc->pdc_reset);
		ret = reset_control_reset(qproc->mss_restart);
		reset_control_deनिश्चित(qproc->pdc_reset);
	पूर्ण अन्यथा अगर (qproc->has_spare_reg) अणु
		/*
		 * When the AXI pipeline is being reset with the Q6 modem partly
		 * operational there is possibility of AXI valid संकेत to
		 * glitch, leading to spurious transactions and Q6 hangs. A work
		 * around is employed by निश्चितing the AXI_GATING_VALID_OVERRIDE
		 * BIT beक्रमe triggering Q6 MSS reset. AXI_GATING_VALID_OVERRIDE
		 * is withdrawn post MSS निश्चित followed by a MSS deनिश्चित,
		 * जबतक holding the PDC reset.
		 */
		reset_control_निश्चित(qproc->pdc_reset);
		regmap_update_bits(qproc->conn_map, qproc->conn_box,
				   AXI_GATING_VALID_OVERRIDE, 1);
		reset_control_निश्चित(qproc->mss_restart);
		reset_control_deनिश्चित(qproc->pdc_reset);
		regmap_update_bits(qproc->conn_map, qproc->conn_box,
				   AXI_GATING_VALID_OVERRIDE, 0);
		ret = reset_control_deनिश्चित(qproc->mss_restart);
	पूर्ण अन्यथा अणु
		ret = reset_control_निश्चित(qproc->mss_restart);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_reset_deनिश्चित(काष्ठा q6v5 *qproc)
अणु
	पूर्णांक ret;

	अगर (qproc->has_alt_reset) अणु
		reset_control_निश्चित(qproc->pdc_reset);
		ग_लिखोl(1, qproc->rmb_base + RMB_MBA_ALT_RESET);
		ret = reset_control_reset(qproc->mss_restart);
		ग_लिखोl(0, qproc->rmb_base + RMB_MBA_ALT_RESET);
		reset_control_deनिश्चित(qproc->pdc_reset);
	पूर्ण अन्यथा अगर (qproc->has_spare_reg) अणु
		ret = reset_control_reset(qproc->mss_restart);
	पूर्ण अन्यथा अणु
		ret = reset_control_deनिश्चित(qproc->mss_restart);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_rmb_pbl_रुको(काष्ठा q6v5 *qproc, पूर्णांक ms)
अणु
	अचिन्हित दीर्घ समयout;
	s32 val;

	समयout = jअगरfies + msecs_to_jअगरfies(ms);
	क्रम (;;) अणु
		val = पढ़ोl(qproc->rmb_base + RMB_PBL_STATUS_REG);
		अगर (val)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

		msleep(1);
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक q6v5_rmb_mba_रुको(काष्ठा q6v5 *qproc, u32 status, पूर्णांक ms)
अणु

	अचिन्हित दीर्घ समयout;
	s32 val;

	समयout = jअगरfies + msecs_to_jअगरfies(ms);
	क्रम (;;) अणु
		val = पढ़ोl(qproc->rmb_base + RMB_MBA_STATUS_REG);
		अगर (val < 0)
			अवरोध;

		अगर (!status && val)
			अवरोध;
		अन्यथा अगर (status && val == status)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

		msleep(1);
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम q6v5_dump_mba_logs(काष्ठा q6v5 *qproc)
अणु
	काष्ठा rproc *rproc = qproc->rproc;
	व्योम *data;
	व्योम *mba_region;

	अगर (!qproc->has_mba_logs)
		वापस;

	अगर (q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, true, false, qproc->mba_phys,
				    qproc->mba_size))
		वापस;

	mba_region = memremap(qproc->mba_phys, qproc->mba_size, MEMREMAP_WC);
	अगर (!mba_region)
		वापस;

	data = vदो_स्मृति(MBA_LOG_SIZE);
	अगर (data) अणु
		स_नकल(data, mba_region, MBA_LOG_SIZE);
		dev_coredumpv(&rproc->dev, data, MBA_LOG_SIZE, GFP_KERNEL);
	पूर्ण
	memunmap(mba_region);
पूर्ण

अटल पूर्णांक q6v5proc_reset(काष्ठा q6v5 *qproc)
अणु
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (qproc->version == MSS_SDM845) अणु
		val = पढ़ोl(qproc->reg_base + QDSP6SS_SLEEP);
		val |= Q6SS_CBCR_CLKEN;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_SLEEP);

		ret = पढ़ोl_poll_समयout(qproc->reg_base + QDSP6SS_SLEEP,
					 val, !(val & Q6SS_CBCR_CLKOFF), 1,
					 Q6SS_CBCR_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(qproc->dev, "QDSP6SS Sleep clock timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		/* De-निश्चित QDSP6 stop core */
		ग_लिखोl(1, qproc->reg_base + QDSP6SS_BOOT_CORE_START);
		/* Trigger boot FSM */
		ग_लिखोl(1, qproc->reg_base + QDSP6SS_BOOT_CMD);

		ret = पढ़ोl_poll_समयout(qproc->rmb_base + RMB_MBA_MSS_STATUS,
				val, (val & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
		अगर (ret) अणु
			dev_err(qproc->dev, "Boot FSM failed to complete.\n");
			/* Reset the modem so that boot FSM is in reset state */
			q6v5_reset_deनिश्चित(qproc);
			वापस ret;
		पूर्ण

		जाओ pbl_रुको;
	पूर्ण अन्यथा अगर (qproc->version == MSS_SC7180) अणु
		val = पढ़ोl(qproc->reg_base + QDSP6SS_SLEEP);
		val |= Q6SS_CBCR_CLKEN;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_SLEEP);

		ret = पढ़ोl_poll_समयout(qproc->reg_base + QDSP6SS_SLEEP,
					 val, !(val & Q6SS_CBCR_CLKOFF), 1,
					 Q6SS_CBCR_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(qproc->dev, "QDSP6SS Sleep clock timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		/* Turn on the XO घड़ी needed क्रम PLL setup */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_XO_CBCR);
		val |= Q6SS_CBCR_CLKEN;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_XO_CBCR);

		ret = पढ़ोl_poll_समयout(qproc->reg_base + QDSP6SS_XO_CBCR,
					 val, !(val & Q6SS_CBCR_CLKOFF), 1,
					 Q6SS_CBCR_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(qproc->dev, "QDSP6SS XO clock timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		/* Configure Q6 core CBCR to स्वतः-enable after reset sequence */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_CORE_CBCR);
		val |= Q6SS_CBCR_CLKEN;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_CORE_CBCR);

		/* De-निश्चित the Q6 stop core संकेत */
		ग_लिखोl(1, qproc->reg_base + QDSP6SS_BOOT_CORE_START);

		/* Wait क्रम 10 us क्रम any staggering logic to settle */
		usleep_range(10, 20);

		/* Trigger the boot FSM to start the Q6 out-of-reset sequence */
		ग_लिखोl(1, qproc->reg_base + QDSP6SS_BOOT_CMD);

		/* Poll the MSS_STATUS क्रम FSM completion */
		ret = पढ़ोl_poll_समयout(qproc->rmb_base + RMB_MBA_MSS_STATUS,
					 val, (val & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
		अगर (ret) अणु
			dev_err(qproc->dev, "Boot FSM failed to complete.\n");
			/* Reset the modem so that boot FSM is in reset state */
			q6v5_reset_deनिश्चित(qproc);
			वापस ret;
		पूर्ण
		जाओ pbl_रुको;
	पूर्ण अन्यथा अगर (qproc->version == MSS_MSM8996 ||
		   qproc->version == MSS_MSM8998) अणु
		पूर्णांक mem_pwr_ctl;

		/* Override the ACC value अगर required */
		ग_लिखोl(QDSP6SS_ACC_OVERRIDE_VAL,
		       qproc->reg_base + QDSP6SS_STRAP_ACC);

		/* Assert resets, stop core */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_RESET_REG);
		val |= Q6SS_CORE_ARES | Q6SS_BUS_ARES_ENABLE | Q6SS_STOP_CORE;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_RESET_REG);

		/* BHS require xo cbcr to be enabled */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_XO_CBCR);
		val |= Q6SS_CBCR_CLKEN;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_XO_CBCR);

		/* Read CLKOFF bit to go low indicating CLK is enabled */
		ret = पढ़ोl_poll_समयout(qproc->reg_base + QDSP6SS_XO_CBCR,
					 val, !(val & Q6SS_CBCR_CLKOFF), 1,
					 Q6SS_CBCR_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(qproc->dev,
				"xo cbcr enabling timed out (rc:%d)\n", ret);
			वापस ret;
		पूर्ण
		/* Enable घातer block headचयन and रुको क्रम it to stabilize */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= QDSP6v56_BHS_ON;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		udelay(1);

		/* Put LDO in bypass mode */
		val |= QDSP6v56_LDO_BYP;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

		/* Deनिश्चित QDSP6 compiler memory clamp */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val &= ~QDSP6v56_CLAMP_QMC_MEM;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

		/* Deनिश्चित memory peripheral sleep and L2 memory standby */
		val |= Q6SS_L2DATA_STBY_N | Q6SS_SLP_RET_N;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

		/* Turn on L1, L2, ETB and JU memories 1 at a समय */
		अगर (qproc->version == MSS_MSM8996) अणु
			mem_pwr_ctl = QDSP6SS_MEM_PWR_CTL;
			i = 19;
		पूर्ण अन्यथा अणु
			/* MSS_MSM8998 */
			mem_pwr_ctl = QDSP6V6SS_MEM_PWR_CTL;
			i = 28;
		पूर्ण
		val = पढ़ोl(qproc->reg_base + mem_pwr_ctl);
		क्रम (; i >= 0; i--) अणु
			val |= BIT(i);
			ग_लिखोl(val, qproc->reg_base + mem_pwr_ctl);
			/*
			 * Read back value to ensure the ग_लिखो is करोne then
			 * रुको क्रम 1us क्रम both memory peripheral and data
			 * array to turn on.
			 */
			val |= पढ़ोl(qproc->reg_base + mem_pwr_ctl);
			udelay(1);
		पूर्ण
		/* Remove word line clamp */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val &= ~QDSP6v56_CLAMP_WL;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	पूर्ण अन्यथा अणु
		/* Assert resets, stop core */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_RESET_REG);
		val |= Q6SS_CORE_ARES | Q6SS_BUS_ARES_ENABLE | Q6SS_STOP_CORE;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_RESET_REG);

		/* Enable घातer block headचयन and रुको क्रम it to stabilize */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= QDSS_BHS_ON | QDSS_LDO_BYP;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		udelay(1);
		/*
		 * Turn on memories. L2 banks should be करोne inभागidually
		 * to minimize inrush current.
		 */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_SLP_RET_N | Q6SS_L2TAG_SLP_NRET_N |
			Q6SS_ETB_SLP_NRET_N | Q6SS_L2DATA_STBY_N;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_L2DATA_SLP_NRET_N_2;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_L2DATA_SLP_NRET_N_1;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_L2DATA_SLP_NRET_N_0;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	पूर्ण
	/* Remove IO clamp */
	val &= ~Q6SS_CLAMP_IO;
	ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);

	/* Bring core out of reset */
	val = पढ़ोl(qproc->reg_base + QDSP6SS_RESET_REG);
	val &= ~Q6SS_CORE_ARES;
	ग_लिखोl(val, qproc->reg_base + QDSP6SS_RESET_REG);

	/* Turn on core घड़ी */
	val = पढ़ोl(qproc->reg_base + QDSP6SS_GFMUX_CTL_REG);
	val |= Q6SS_CLK_ENABLE;
	ग_लिखोl(val, qproc->reg_base + QDSP6SS_GFMUX_CTL_REG);

	/* Start core execution */
	val = पढ़ोl(qproc->reg_base + QDSP6SS_RESET_REG);
	val &= ~Q6SS_STOP_CORE;
	ग_लिखोl(val, qproc->reg_base + QDSP6SS_RESET_REG);

pbl_रुको:
	/* Wait क्रम PBL status */
	ret = q6v5_rmb_pbl_रुको(qproc, 1000);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(qproc->dev, "PBL boot timed out\n");
	पूर्ण अन्यथा अगर (ret != RMB_PBL_SUCCESS) अणु
		dev_err(qproc->dev, "PBL returned unexpected status %d\n", ret);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम q6v5proc_halt_axi_port(काष्ठा q6v5 *qproc,
				   काष्ठा regmap *halt_map,
				   u32 offset)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Check अगर we're alपढ़ोy idle */
	ret = regmap_पढ़ो(halt_map, offset + AXI_IDLE_REG, &val);
	अगर (!ret && val)
		वापस;

	/* Assert halt request */
	regmap_ग_लिखो(halt_map, offset + AXI_HALTREQ_REG, 1);

	/* Wait क्रम halt */
	regmap_पढ़ो_poll_समयout(halt_map, offset + AXI_HALTACK_REG, val,
				 val, 1000, HALT_ACK_TIMEOUT_US);

	ret = regmap_पढ़ो(halt_map, offset + AXI_IDLE_REG, &val);
	अगर (ret || !val)
		dev_err(qproc->dev, "port failed halt\n");

	/* Clear halt request (port will reमुख्य halted until reset) */
	regmap_ग_लिखो(halt_map, offset + AXI_HALTREQ_REG, 0);
पूर्ण

अटल पूर्णांक q6v5_mpss_init_image(काष्ठा q6v5 *qproc, स्थिर काष्ठा firmware *fw)
अणु
	अचिन्हित दीर्घ dma_attrs = DMA_ATTR_FORCE_CONTIGUOUS;
	dma_addr_t phys;
	व्योम *metadata;
	पूर्णांक mdata_perm;
	पूर्णांक xferop_ret;
	माप_प्रकार size;
	व्योम *ptr;
	पूर्णांक ret;

	metadata = qcom_mdt_पढ़ो_metadata(fw, &size);
	अगर (IS_ERR(metadata))
		वापस PTR_ERR(metadata);

	ptr = dma_alloc_attrs(qproc->dev, size, &phys, GFP_KERNEL, dma_attrs);
	अगर (!ptr) अणु
		kमुक्त(metadata);
		dev_err(qproc->dev, "failed to allocate mdt buffer\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(ptr, metadata, size);

	/* Hypervisor mapping to access metadata by modem */
	mdata_perm = BIT(QCOM_SCM_VMID_HLOS);
	ret = q6v5_xfer_mem_ownership(qproc, &mdata_perm, false, true,
				      phys, size);
	अगर (ret) अणु
		dev_err(qproc->dev,
			"assigning Q6 access to metadata failed: %d\n", ret);
		ret = -EAGAIN;
		जाओ मुक्त_dma_attrs;
	पूर्ण

	ग_लिखोl(phys, qproc->rmb_base + RMB_PMI_META_DATA_REG);
	ग_लिखोl(RMB_CMD_META_DATA_READY, qproc->rmb_base + RMB_MBA_COMMAND_REG);

	ret = q6v5_rmb_mba_रुको(qproc, RMB_MBA_META_DATA_AUTH_SUCCESS, 1000);
	अगर (ret == -ETIMEDOUT)
		dev_err(qproc->dev, "MPSS header authentication timed out\n");
	अन्यथा अगर (ret < 0)
		dev_err(qproc->dev, "MPSS header authentication failed: %d\n", ret);

	/* Metadata authentication करोne, हटाओ modem access */
	xferop_ret = q6v5_xfer_mem_ownership(qproc, &mdata_perm, true, false,
					     phys, size);
	अगर (xferop_ret)
		dev_warn(qproc->dev,
			 "mdt buffer not reclaimed system may become unstable\n");

मुक्त_dma_attrs:
	dma_मुक्त_attrs(qproc->dev, size, ptr, phys, dma_attrs);
	kमुक्त(metadata);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल bool q6v5_phdr_valid(स्थिर काष्ठा elf32_phdr *phdr)
अणु
	अगर (phdr->p_type != PT_LOAD)
		वापस false;

	अगर ((phdr->p_flags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
		वापस false;

	अगर (!phdr->p_memsz)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक q6v5_mba_load(काष्ठा q6v5 *qproc)
अणु
	पूर्णांक ret;
	पूर्णांक xfermemop_ret;
	bool mba_load_err = false;

	qcom_q6v5_prepare(&qproc->q6v5);

	ret = q6v5_pds_enable(qproc, qproc->active_pds, qproc->active_pd_count);
	अगर (ret < 0) अणु
		dev_err(qproc->dev, "failed to enable active power domains\n");
		जाओ disable_irqs;
	पूर्ण

	ret = q6v5_pds_enable(qproc, qproc->proxy_pds, qproc->proxy_pd_count);
	अगर (ret < 0) अणु
		dev_err(qproc->dev, "failed to enable proxy power domains\n");
		जाओ disable_active_pds;
	पूर्ण

	ret = q6v5_regulator_enable(qproc, qproc->fallback_proxy_regs,
				    qproc->fallback_proxy_reg_count);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to enable fallback proxy supplies\n");
		जाओ disable_proxy_pds;
	पूर्ण

	ret = q6v5_regulator_enable(qproc, qproc->proxy_regs,
				    qproc->proxy_reg_count);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to enable proxy supplies\n");
		जाओ disable_fallback_proxy_reg;
	पूर्ण

	ret = q6v5_clk_enable(qproc->dev, qproc->proxy_clks,
			      qproc->proxy_clk_count);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to enable proxy clocks\n");
		जाओ disable_proxy_reg;
	पूर्ण

	ret = q6v5_regulator_enable(qproc, qproc->active_regs,
				    qproc->active_reg_count);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to enable supplies\n");
		जाओ disable_proxy_clk;
	पूर्ण

	ret = q6v5_clk_enable(qproc->dev, qproc->reset_clks,
			      qproc->reset_clk_count);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to enable reset clocks\n");
		जाओ disable_vdd;
	पूर्ण

	ret = q6v5_reset_deनिश्चित(qproc);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to deassert mss restart\n");
		जाओ disable_reset_clks;
	पूर्ण

	ret = q6v5_clk_enable(qproc->dev, qproc->active_clks,
			      qproc->active_clk_count);
	अगर (ret) अणु
		dev_err(qproc->dev, "failed to enable clocks\n");
		जाओ निश्चित_reset;
	पूर्ण

	/*
	 * Some versions of the MBA firmware will upon boot wipe the MPSS region as well, so provide
	 * the Q6 access to this region.
	 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm, false, true,
				      qproc->mpss_phys, qproc->mpss_size);
	अगर (ret) अणु
		dev_err(qproc->dev, "assigning Q6 access to mpss memory failed: %d\n", ret);
		जाओ disable_active_clks;
	पूर्ण

	/* Assign MBA image access in DDR to q6 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, false, true,
				      qproc->mba_phys, qproc->mba_size);
	अगर (ret) अणु
		dev_err(qproc->dev,
			"assigning Q6 access to mba memory failed: %d\n", ret);
		जाओ disable_active_clks;
	पूर्ण

	ग_लिखोl(qproc->mba_phys, qproc->rmb_base + RMB_MBA_IMAGE_REG);
	अगर (qproc->dp_size) अणु
		ग_लिखोl(qproc->mba_phys + SZ_1M, qproc->rmb_base + RMB_PMI_CODE_START_REG);
		ग_लिखोl(qproc->dp_size, qproc->rmb_base + RMB_PMI_CODE_LENGTH_REG);
	पूर्ण

	ret = q6v5proc_reset(qproc);
	अगर (ret)
		जाओ reclaim_mba;

	ret = q6v5_rmb_mba_रुको(qproc, 0, 5000);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(qproc->dev, "MBA boot timed out\n");
		जाओ halt_axi_ports;
	पूर्ण अन्यथा अगर (ret != RMB_MBA_XPU_UNLOCKED &&
		   ret != RMB_MBA_XPU_UNLOCKED_SCRIBBLED) अणु
		dev_err(qproc->dev, "MBA returned unexpected status %d\n", ret);
		ret = -EINVAL;
		जाओ halt_axi_ports;
	पूर्ण

	qproc->dump_mba_loaded = true;
	वापस 0;

halt_axi_ports:
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_q6);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_modem);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_nc);
	mba_load_err = true;
reclaim_mba:
	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, true,
						false, qproc->mba_phys,
						qproc->mba_size);
	अगर (xfermemop_ret) अणु
		dev_err(qproc->dev,
			"Failed to reclaim mba buffer, system may become unstable\n");
	पूर्ण अन्यथा अगर (mba_load_err) अणु
		q6v5_dump_mba_logs(qproc);
	पूर्ण

disable_active_clks:
	q6v5_clk_disable(qproc->dev, qproc->active_clks,
			 qproc->active_clk_count);
निश्चित_reset:
	q6v5_reset_निश्चित(qproc);
disable_reset_clks:
	q6v5_clk_disable(qproc->dev, qproc->reset_clks,
			 qproc->reset_clk_count);
disable_vdd:
	q6v5_regulator_disable(qproc, qproc->active_regs,
			       qproc->active_reg_count);
disable_proxy_clk:
	q6v5_clk_disable(qproc->dev, qproc->proxy_clks,
			 qproc->proxy_clk_count);
disable_proxy_reg:
	q6v5_regulator_disable(qproc, qproc->proxy_regs,
			       qproc->proxy_reg_count);
disable_fallback_proxy_reg:
	q6v5_regulator_disable(qproc, qproc->fallback_proxy_regs,
			       qproc->fallback_proxy_reg_count);
disable_proxy_pds:
	q6v5_pds_disable(qproc, qproc->proxy_pds, qproc->proxy_pd_count);
disable_active_pds:
	q6v5_pds_disable(qproc, qproc->active_pds, qproc->active_pd_count);
disable_irqs:
	qcom_q6v5_unprepare(&qproc->q6v5);

	वापस ret;
पूर्ण

अटल व्योम q6v5_mba_reclaim(काष्ठा q6v5 *qproc)
अणु
	पूर्णांक ret;
	u32 val;

	qproc->dump_mba_loaded = false;
	qproc->dp_size = 0;

	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_q6);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_modem);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_nc);
	अगर (qproc->version == MSS_MSM8996) अणु
		/*
		 * To aव्योम high MX current during LPASS/MSS restart.
		 */
		val = पढ़ोl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_CLAMP_IO | QDSP6v56_CLAMP_WL |
			QDSP6v56_CLAMP_QMC_MEM;
		ग_लिखोl(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	पूर्ण

	q6v5_reset_निश्चित(qproc);

	q6v5_clk_disable(qproc->dev, qproc->reset_clks,
			 qproc->reset_clk_count);
	q6v5_clk_disable(qproc->dev, qproc->active_clks,
			 qproc->active_clk_count);
	q6v5_regulator_disable(qproc, qproc->active_regs,
			       qproc->active_reg_count);
	q6v5_pds_disable(qproc, qproc->active_pds, qproc->active_pd_count);

	/* In हाल of failure or coredump scenario where reclaiming MBA memory
	 * could not happen reclaim it here.
	 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, true, false,
				      qproc->mba_phys,
				      qproc->mba_size);
	WARN_ON(ret);

	ret = qcom_q6v5_unprepare(&qproc->q6v5);
	अगर (ret) अणु
		q6v5_pds_disable(qproc, qproc->proxy_pds,
				 qproc->proxy_pd_count);
		q6v5_clk_disable(qproc->dev, qproc->proxy_clks,
				 qproc->proxy_clk_count);
		q6v5_regulator_disable(qproc, qproc->fallback_proxy_regs,
				       qproc->fallback_proxy_reg_count);
		q6v5_regulator_disable(qproc, qproc->proxy_regs,
				       qproc->proxy_reg_count);
	पूर्ण
पूर्ण

अटल पूर्णांक q6v5_reload_mba(काष्ठा rproc *rproc)
अणु
	काष्ठा q6v5 *qproc = rproc->priv;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, rproc->firmware, qproc->dev);
	अगर (ret < 0)
		वापस ret;

	q6v5_load(rproc, fw);
	ret = q6v5_mba_load(qproc);
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_mpss_load(काष्ठा q6v5 *qproc)
अणु
	स्थिर काष्ठा elf32_phdr *phdrs;
	स्थिर काष्ठा elf32_phdr *phdr;
	स्थिर काष्ठा firmware *seg_fw;
	स्थिर काष्ठा firmware *fw;
	काष्ठा elf32_hdr *ehdr;
	phys_addr_t mpss_reloc;
	phys_addr_t boot_addr;
	phys_addr_t min_addr = PHYS_ADDR_MAX;
	phys_addr_t max_addr = 0;
	u32 code_length;
	bool relocate = false;
	अक्षर *fw_name;
	माप_प्रकार fw_name_len;
	sमाप_प्रकार offset;
	माप_प्रकार size = 0;
	व्योम *ptr;
	पूर्णांक ret;
	पूर्णांक i;

	fw_name_len = म_माप(qproc->hexagon_mdt_image);
	अगर (fw_name_len <= 4)
		वापस -EINVAL;

	fw_name = kstrdup(qproc->hexagon_mdt_image, GFP_KERNEL);
	अगर (!fw_name)
		वापस -ENOMEM;

	ret = request_firmware(&fw, fw_name, qproc->dev);
	अगर (ret < 0) अणु
		dev_err(qproc->dev, "unable to load %s\n", fw_name);
		जाओ out;
	पूर्ण

	/* Initialize the RMB validator */
	ग_लिखोl(0, qproc->rmb_base + RMB_PMI_CODE_LENGTH_REG);

	ret = q6v5_mpss_init_image(qproc, fw);
	अगर (ret)
		जाओ release_firmware;

	ehdr = (काष्ठा elf32_hdr *)fw->data;
	phdrs = (काष्ठा elf32_phdr *)(ehdr + 1);

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (!q6v5_phdr_valid(phdr))
			जारी;

		अगर (phdr->p_flags & QCOM_MDT_RELOCATABLE)
			relocate = true;

		अगर (phdr->p_paddr < min_addr)
			min_addr = phdr->p_paddr;

		अगर (phdr->p_paddr + phdr->p_memsz > max_addr)
			max_addr = ALIGN(phdr->p_paddr + phdr->p_memsz, SZ_4K);
	पूर्ण

	/*
	 * In हाल of a modem subप्रणाली restart on secure devices, the modem
	 * memory can be reclaimed only after MBA is loaded.
	 */
	q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm, true, false,
				qproc->mpss_phys, qproc->mpss_size);

	/* Share ownership between Linux and MSS, during segment loading */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm, true, true,
				      qproc->mpss_phys, qproc->mpss_size);
	अगर (ret) अणु
		dev_err(qproc->dev,
			"assigning Q6 access to mpss memory failed: %d\n", ret);
		ret = -EAGAIN;
		जाओ release_firmware;
	पूर्ण

	mpss_reloc = relocate ? min_addr : qproc->mpss_phys;
	qproc->mpss_reloc = mpss_reloc;
	/* Load firmware segments */
	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (!q6v5_phdr_valid(phdr))
			जारी;

		offset = phdr->p_paddr - mpss_reloc;
		अगर (offset < 0 || offset + phdr->p_memsz > qproc->mpss_size) अणु
			dev_err(qproc->dev, "segment outside memory range\n");
			ret = -EINVAL;
			जाओ release_firmware;
		पूर्ण

		अगर (phdr->p_filesz > phdr->p_memsz) अणु
			dev_err(qproc->dev,
				"refusing to load segment %d with p_filesz > p_memsz\n",
				i);
			ret = -EINVAL;
			जाओ release_firmware;
		पूर्ण

		ptr = memremap(qproc->mpss_phys + offset, phdr->p_memsz, MEMREMAP_WC);
		अगर (!ptr) अणु
			dev_err(qproc->dev,
				"unable to map memory region: %pa+%zx-%x\n",
				&qproc->mpss_phys, offset, phdr->p_memsz);
			जाओ release_firmware;
		पूर्ण

		अगर (phdr->p_filesz && phdr->p_offset < fw->size) अणु
			/* Firmware is large enough to be non-split */
			अगर (phdr->p_offset + phdr->p_filesz > fw->size) अणु
				dev_err(qproc->dev,
					"failed to load segment %d from truncated file %s\n",
					i, fw_name);
				ret = -EINVAL;
				memunmap(ptr);
				जाओ release_firmware;
			पूर्ण

			स_नकल(ptr, fw->data + phdr->p_offset, phdr->p_filesz);
		पूर्ण अन्यथा अगर (phdr->p_filesz) अणु
			/* Replace "xxx.xxx" with "xxx.bxx" */
			प्र_लिखो(fw_name + fw_name_len - 3, "b%02d", i);
			ret = request_firmware_पूर्णांकo_buf(&seg_fw, fw_name, qproc->dev,
							ptr, phdr->p_filesz);
			अगर (ret) अणु
				dev_err(qproc->dev, "failed to load %s\n", fw_name);
				memunmap(ptr);
				जाओ release_firmware;
			पूर्ण

			अगर (seg_fw->size != phdr->p_filesz) अणु
				dev_err(qproc->dev,
					"failed to load segment %d from truncated file %s\n",
					i, fw_name);
				ret = -EINVAL;
				release_firmware(seg_fw);
				memunmap(ptr);
				जाओ release_firmware;
			पूर्ण

			release_firmware(seg_fw);
		पूर्ण

		अगर (phdr->p_memsz > phdr->p_filesz) अणु
			स_रखो(ptr + phdr->p_filesz, 0,
			       phdr->p_memsz - phdr->p_filesz);
		पूर्ण
		memunmap(ptr);
		size += phdr->p_memsz;

		code_length = पढ़ोl(qproc->rmb_base + RMB_PMI_CODE_LENGTH_REG);
		अगर (!code_length) अणु
			boot_addr = relocate ? qproc->mpss_phys : min_addr;
			ग_लिखोl(boot_addr, qproc->rmb_base + RMB_PMI_CODE_START_REG);
			ग_लिखोl(RMB_CMD_LOAD_READY, qproc->rmb_base + RMB_MBA_COMMAND_REG);
		पूर्ण
		ग_लिखोl(size, qproc->rmb_base + RMB_PMI_CODE_LENGTH_REG);

		ret = पढ़ोl(qproc->rmb_base + RMB_MBA_STATUS_REG);
		अगर (ret < 0) अणु
			dev_err(qproc->dev, "MPSS authentication failed: %d\n",
				ret);
			जाओ release_firmware;
		पूर्ण
	पूर्ण

	/* Transfer ownership of modem ddr region to q6 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm, false, true,
				      qproc->mpss_phys, qproc->mpss_size);
	अगर (ret) अणु
		dev_err(qproc->dev,
			"assigning Q6 access to mpss memory failed: %d\n", ret);
		ret = -EAGAIN;
		जाओ release_firmware;
	पूर्ण

	ret = q6v5_rmb_mba_रुको(qproc, RMB_MBA_AUTH_COMPLETE, 10000);
	अगर (ret == -ETIMEDOUT)
		dev_err(qproc->dev, "MPSS authentication timed out\n");
	अन्यथा अगर (ret < 0)
		dev_err(qproc->dev, "MPSS authentication failed: %d\n", ret);

	qcom_pil_info_store("modem", qproc->mpss_phys, qproc->mpss_size);

release_firmware:
	release_firmware(fw);
out:
	kमुक्त(fw_name);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम qcom_q6v5_dump_segment(काष्ठा rproc *rproc,
				   काष्ठा rproc_dump_segment *segment,
				   व्योम *dest, माप_प्रकार cp_offset, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	काष्ठा q6v5 *qproc = rproc->priv;
	पूर्णांक offset = segment->da - qproc->mpss_reloc;
	व्योम *ptr = शून्य;

	/* Unlock mba beक्रमe copying segments */
	अगर (!qproc->dump_mba_loaded) अणु
		ret = q6v5_reload_mba(rproc);
		अगर (!ret) अणु
			/* Reset ownership back to Linux to copy segments */
			ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm,
						      true, false,
						      qproc->mpss_phys,
						      qproc->mpss_size);
		पूर्ण
	पूर्ण

	अगर (!ret)
		ptr = memremap(qproc->mpss_phys + offset + cp_offset, size, MEMREMAP_WC);

	अगर (ptr) अणु
		स_नकल(dest, ptr, size);
		memunmap(ptr);
	पूर्ण अन्यथा अणु
		स_रखो(dest, 0xff, size);
	पूर्ण

	qproc->current_dump_size += size;

	/* Reclaim mba after copying segments */
	अगर (qproc->current_dump_size == qproc->total_dump_size) अणु
		अगर (qproc->dump_mba_loaded) अणु
			/* Try to reset ownership back to Q6 */
			q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm,
						false, true,
						qproc->mpss_phys,
						qproc->mpss_size);
			q6v5_mba_reclaim(qproc);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक q6v5_start(काष्ठा rproc *rproc)
अणु
	काष्ठा q6v5 *qproc = (काष्ठा q6v5 *)rproc->priv;
	पूर्णांक xfermemop_ret;
	पूर्णांक ret;

	ret = q6v5_mba_load(qproc);
	अगर (ret)
		वापस ret;

	dev_info(qproc->dev, "MBA booted with%s debug policy, loading mpss\n",
		 qproc->dp_size ? "" : "out");

	ret = q6v5_mpss_load(qproc);
	अगर (ret)
		जाओ reclaim_mpss;

	ret = qcom_q6v5_रुको_क्रम_start(&qproc->q6v5, msecs_to_jअगरfies(5000));
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(qproc->dev, "start timed out\n");
		जाओ reclaim_mpss;
	पूर्ण

	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, true,
						false, qproc->mba_phys,
						qproc->mba_size);
	अगर (xfermemop_ret)
		dev_err(qproc->dev,
			"Failed to reclaim mba buffer system may become unstable\n");

	/* Reset Dump Segment Mask */
	qproc->current_dump_size = 0;

	वापस 0;

reclaim_mpss:
	q6v5_mba_reclaim(qproc);
	q6v5_dump_mba_logs(qproc);

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा q6v5 *qproc = (काष्ठा q6v5 *)rproc->priv;
	पूर्णांक ret;

	ret = qcom_q6v5_request_stop(&qproc->q6v5, qproc->sysmon);
	अगर (ret == -ETIMEDOUT)
		dev_err(qproc->dev, "timed out on wait\n");

	q6v5_mba_reclaim(qproc);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_q6v5_रेजिस्टर_dump_segments(काष्ठा rproc *rproc,
					    स्थिर काष्ठा firmware *mba_fw)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा elf32_phdr *phdrs;
	स्थिर काष्ठा elf32_phdr *phdr;
	स्थिर काष्ठा elf32_hdr *ehdr;
	काष्ठा q6v5 *qproc = rproc->priv;
	अचिन्हित दीर्घ i;
	पूर्णांक ret;

	ret = request_firmware(&fw, qproc->hexagon_mdt_image, qproc->dev);
	अगर (ret < 0) अणु
		dev_err(qproc->dev, "unable to load %s\n",
			qproc->hexagon_mdt_image);
		वापस ret;
	पूर्ण

	rproc_coredump_set_elf_info(rproc, ELFCLASS32, EM_NONE);

	ehdr = (काष्ठा elf32_hdr *)fw->data;
	phdrs = (काष्ठा elf32_phdr *)(ehdr + 1);
	qproc->total_dump_size = 0;

	क्रम (i = 0; i < ehdr->e_phnum; i++) अणु
		phdr = &phdrs[i];

		अगर (!q6v5_phdr_valid(phdr))
			जारी;

		ret = rproc_coredump_add_custom_segment(rproc, phdr->p_paddr,
							phdr->p_memsz,
							qcom_q6v5_dump_segment,
							शून्य);
		अगर (ret)
			अवरोध;

		qproc->total_dump_size += phdr->p_memsz;
	पूर्ण

	release_firmware(fw);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rproc_ops q6v5_ops = अणु
	.start = q6v5_start,
	.stop = q6v5_stop,
	.parse_fw = qcom_q6v5_रेजिस्टर_dump_segments,
	.load = q6v5_load,
पूर्ण;

अटल व्योम qcom_msa_hanकरोver(काष्ठा qcom_q6v5 *q6v5)
अणु
	काष्ठा q6v5 *qproc = container_of(q6v5, काष्ठा q6v5, q6v5);

	q6v5_clk_disable(qproc->dev, qproc->proxy_clks,
			 qproc->proxy_clk_count);
	q6v5_regulator_disable(qproc, qproc->proxy_regs,
			       qproc->proxy_reg_count);
	q6v5_regulator_disable(qproc, qproc->fallback_proxy_regs,
			       qproc->fallback_proxy_reg_count);
	q6v5_pds_disable(qproc, qproc->proxy_pds, qproc->proxy_pd_count);
पूर्ण

अटल पूर्णांक q6v5_init_mem(काष्ठा q6v5 *qproc, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा of_phandle_args args;
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qdsp6");
	qproc->reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(qproc->reg_base))
		वापस PTR_ERR(qproc->reg_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rmb");
	qproc->rmb_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(qproc->rmb_base))
		वापस PTR_ERR(qproc->rmb_base);

	ret = of_parse_phandle_with_fixed_args(pdev->dev.of_node,
					       "qcom,halt-regs", 3, 0, &args);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to parse qcom,halt-regs\n");
		वापस -EINVAL;
	पूर्ण

	qproc->halt_map = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	अगर (IS_ERR(qproc->halt_map))
		वापस PTR_ERR(qproc->halt_map);

	qproc->halt_q6 = args.args[0];
	qproc->halt_modem = args.args[1];
	qproc->halt_nc = args.args[2];

	अगर (qproc->has_spare_reg) अणु
		ret = of_parse_phandle_with_fixed_args(pdev->dev.of_node,
						       "qcom,spare-regs",
						       1, 0, &args);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to parse spare-regs\n");
			वापस -EINVAL;
		पूर्ण

		qproc->conn_map = syscon_node_to_regmap(args.np);
		of_node_put(args.np);
		अगर (IS_ERR(qproc->conn_map))
			वापस PTR_ERR(qproc->conn_map);

		qproc->conn_box = args.args[0];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_init_घड़ीs(काष्ठा device *dev, काष्ठा clk **clks,
		अक्षर **clk_names)
अणु
	पूर्णांक i;

	अगर (!clk_names)
		वापस 0;

	क्रम (i = 0; clk_names[i]; i++) अणु
		clks[i] = devm_clk_get(dev, clk_names[i]);
		अगर (IS_ERR(clks[i])) अणु
			पूर्णांक rc = PTR_ERR(clks[i]);

			अगर (rc != -EPROBE_DEFER)
				dev_err(dev, "Failed to get %s clock\n",
					clk_names[i]);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक q6v5_pds_attach(काष्ठा device *dev, काष्ठा device **devs,
			   अक्षर **pd_names)
अणु
	माप_प्रकार num_pds = 0;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!pd_names)
		वापस 0;

	जबतक (pd_names[num_pds])
		num_pds++;

	क्रम (i = 0; i < num_pds; i++) अणु
		devs[i] = dev_pm_करोमुख्य_attach_by_name(dev, pd_names[i]);
		अगर (IS_ERR_OR_शून्य(devs[i])) अणु
			ret = PTR_ERR(devs[i]) ? : -ENODATA;
			जाओ unroll_attach;
		पूर्ण
	पूर्ण

	वापस num_pds;

unroll_attach:
	क्रम (i--; i >= 0; i--)
		dev_pm_करोमुख्य_detach(devs[i], false);

	वापस ret;
पूर्ण

अटल व्योम q6v5_pds_detach(काष्ठा q6v5 *qproc, काष्ठा device **pds,
			    माप_प्रकार pd_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pd_count; i++)
		dev_pm_करोमुख्य_detach(pds[i], false);
पूर्ण

अटल पूर्णांक q6v5_init_reset(काष्ठा q6v5 *qproc)
अणु
	qproc->mss_restart = devm_reset_control_get_exclusive(qproc->dev,
							      "mss_restart");
	अगर (IS_ERR(qproc->mss_restart)) अणु
		dev_err(qproc->dev, "failed to acquire mss restart\n");
		वापस PTR_ERR(qproc->mss_restart);
	पूर्ण

	अगर (qproc->has_alt_reset || qproc->has_spare_reg) अणु
		qproc->pdc_reset = devm_reset_control_get_exclusive(qproc->dev,
								    "pdc_reset");
		अगर (IS_ERR(qproc->pdc_reset)) अणु
			dev_err(qproc->dev, "failed to acquire pdc reset\n");
			वापस PTR_ERR(qproc->pdc_reset);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_alloc_memory_region(काष्ठा q6v5 *qproc)
अणु
	काष्ठा device_node *child;
	काष्ठा device_node *node;
	काष्ठा resource r;
	पूर्णांक ret;

	/*
	 * In the असलence of mba/mpss sub-child, extract the mba and mpss
	 * reserved memory regions from device's memory-region property.
	 */
	child = of_get_child_by_name(qproc->dev->of_node, "mba");
	अगर (!child)
		node = of_parse_phandle(qproc->dev->of_node,
					"memory-region", 0);
	अन्यथा
		node = of_parse_phandle(child, "memory-region", 0);

	ret = of_address_to_resource(node, 0, &r);
	अगर (ret) अणु
		dev_err(qproc->dev, "unable to resolve mba region\n");
		वापस ret;
	पूर्ण
	of_node_put(node);

	qproc->mba_phys = r.start;
	qproc->mba_size = resource_size(&r);

	अगर (!child) अणु
		node = of_parse_phandle(qproc->dev->of_node,
					"memory-region", 1);
	पूर्ण अन्यथा अणु
		child = of_get_child_by_name(qproc->dev->of_node, "mpss");
		node = of_parse_phandle(child, "memory-region", 0);
	पूर्ण

	ret = of_address_to_resource(node, 0, &r);
	अगर (ret) अणु
		dev_err(qproc->dev, "unable to resolve mpss region\n");
		वापस ret;
	पूर्ण
	of_node_put(node);

	qproc->mpss_phys = qproc->mpss_reloc = r.start;
	qproc->mpss_size = resource_size(&r);

	वापस 0;
पूर्ण

अटल पूर्णांक q6v5_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा rproc_hexagon_res *desc;
	काष्ठा q6v5 *qproc;
	काष्ठा rproc *rproc;
	स्थिर अक्षर *mba_image;
	पूर्णांक ret;

	desc = of_device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	अगर (desc->need_mem_protection && !qcom_scm_is_available())
		वापस -EPROBE_DEFER;

	mba_image = desc->hexagon_mba_image;
	ret = of_property_पढ़ो_string_index(pdev->dev.of_node, "firmware-name",
					    0, &mba_image);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(&pdev->dev, "unable to read mba firmware-name\n");
		वापस ret;
	पूर्ण

	rproc = rproc_alloc(&pdev->dev, pdev->name, &q6v5_ops,
			    mba_image, माप(*qproc));
	अगर (!rproc) अणु
		dev_err(&pdev->dev, "failed to allocate rproc\n");
		वापस -ENOMEM;
	पूर्ण

	rproc->स्वतः_boot = false;
	rproc_coredump_set_elf_info(rproc, ELFCLASS32, EM_NONE);

	qproc = (काष्ठा q6v5 *)rproc->priv;
	qproc->dev = &pdev->dev;
	qproc->rproc = rproc;
	qproc->hexagon_mdt_image = "modem.mdt";
	ret = of_property_पढ़ो_string_index(pdev->dev.of_node, "firmware-name",
					    1, &qproc->hexagon_mdt_image);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(&pdev->dev, "unable to read mpss firmware-name\n");
		जाओ मुक्त_rproc;
	पूर्ण

	platक्रमm_set_drvdata(pdev, qproc);

	qproc->has_spare_reg = desc->has_spare_reg;
	ret = q6v5_init_mem(qproc, pdev);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = q6v5_alloc_memory_region(qproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = q6v5_init_घड़ीs(&pdev->dev, qproc->proxy_clks,
			       desc->proxy_clk_names);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get proxy clocks.\n");
		जाओ मुक्त_rproc;
	पूर्ण
	qproc->proxy_clk_count = ret;

	ret = q6v5_init_घड़ीs(&pdev->dev, qproc->reset_clks,
			       desc->reset_clk_names);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get reset clocks.\n");
		जाओ मुक्त_rproc;
	पूर्ण
	qproc->reset_clk_count = ret;

	ret = q6v5_init_घड़ीs(&pdev->dev, qproc->active_clks,
			       desc->active_clk_names);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get active clocks.\n");
		जाओ मुक्त_rproc;
	पूर्ण
	qproc->active_clk_count = ret;

	ret = q6v5_regulator_init(&pdev->dev, qproc->proxy_regs,
				  desc->proxy_supply);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get proxy regulators.\n");
		जाओ मुक्त_rproc;
	पूर्ण
	qproc->proxy_reg_count = ret;

	ret = q6v5_regulator_init(&pdev->dev,  qproc->active_regs,
				  desc->active_supply);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get active regulators.\n");
		जाओ मुक्त_rproc;
	पूर्ण
	qproc->active_reg_count = ret;

	ret = q6v5_pds_attach(&pdev->dev, qproc->active_pds,
			      desc->active_pd_names);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to attach active power domains\n");
		जाओ मुक्त_rproc;
	पूर्ण
	qproc->active_pd_count = ret;

	ret = q6v5_pds_attach(&pdev->dev, qproc->proxy_pds,
			      desc->proxy_pd_names);
	/* Fallback to regulators क्रम old device trees */
	अगर (ret == -ENODATA && desc->fallback_proxy_supply) अणु
		ret = q6v5_regulator_init(&pdev->dev,
					  qproc->fallback_proxy_regs,
					  desc->fallback_proxy_supply);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Failed to get fallback proxy regulators.\n");
			जाओ detach_active_pds;
		पूर्ण
		qproc->fallback_proxy_reg_count = ret;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to init power domains\n");
		जाओ detach_active_pds;
	पूर्ण अन्यथा अणु
		qproc->proxy_pd_count = ret;
	पूर्ण

	qproc->has_alt_reset = desc->has_alt_reset;
	ret = q6v5_init_reset(qproc);
	अगर (ret)
		जाओ detach_proxy_pds;

	qproc->version = desc->version;
	qproc->need_mem_protection = desc->need_mem_protection;
	qproc->has_mba_logs = desc->has_mba_logs;

	ret = qcom_q6v5_init(&qproc->q6v5, pdev, rproc, MPSS_CRASH_REASON_SMEM,
			     qcom_msa_hanकरोver);
	अगर (ret)
		जाओ detach_proxy_pds;

	qproc->mpss_perm = BIT(QCOM_SCM_VMID_HLOS);
	qproc->mba_perm = BIT(QCOM_SCM_VMID_HLOS);
	qcom_add_glink_subdev(rproc, &qproc->glink_subdev, "mpss");
	qcom_add_smd_subdev(rproc, &qproc->smd_subdev);
	qcom_add_ssr_subdev(rproc, &qproc->ssr_subdev, "mpss");
	qproc->sysmon = qcom_add_sysmon_subdev(rproc, "modem", 0x12);
	अगर (IS_ERR(qproc->sysmon)) अणु
		ret = PTR_ERR(qproc->sysmon);
		जाओ हटाओ_subdevs;
	पूर्ण

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ हटाओ_sysmon_subdev;

	वापस 0;

हटाओ_sysmon_subdev:
	qcom_हटाओ_sysmon_subdev(qproc->sysmon);
हटाओ_subdevs:
	qcom_हटाओ_ssr_subdev(rproc, &qproc->ssr_subdev);
	qcom_हटाओ_smd_subdev(rproc, &qproc->smd_subdev);
	qcom_हटाओ_glink_subdev(rproc, &qproc->glink_subdev);
detach_proxy_pds:
	q6v5_pds_detach(qproc, qproc->proxy_pds, qproc->proxy_pd_count);
detach_active_pds:
	q6v5_pds_detach(qproc, qproc->active_pds, qproc->active_pd_count);
मुक्त_rproc:
	rproc_मुक्त(rproc);

	वापस ret;
पूर्ण

अटल पूर्णांक q6v5_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा q6v5 *qproc = platक्रमm_get_drvdata(pdev);
	काष्ठा rproc *rproc = qproc->rproc;

	rproc_del(rproc);

	qcom_हटाओ_sysmon_subdev(qproc->sysmon);
	qcom_हटाओ_ssr_subdev(rproc, &qproc->ssr_subdev);
	qcom_हटाओ_smd_subdev(rproc, &qproc->smd_subdev);
	qcom_हटाओ_glink_subdev(rproc, &qproc->glink_subdev);

	q6v5_pds_detach(qproc, qproc->proxy_pds, qproc->proxy_pd_count);
	q6v5_pds_detach(qproc, qproc->active_pds, qproc->active_pd_count);

	rproc_मुक्त(rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rproc_hexagon_res sc7180_mss = अणु
	.hexagon_mba_image = "mba.mbn",
	.proxy_clk_names = (अक्षर*[])अणु
		"xo",
		शून्य
	पूर्ण,
	.reset_clk_names = (अक्षर*[])अणु
		"iface",
		"bus",
		"snoc_axi",
		शून्य
	पूर्ण,
	.active_clk_names = (अक्षर*[])अणु
		"mnoc_axi",
		"nav",
		शून्य
	पूर्ण,
	.active_pd_names = (अक्षर*[])अणु
		"load_state",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"cx",
		"mx",
		"mss",
		शून्य
	पूर्ण,
	.need_mem_protection = true,
	.has_alt_reset = false,
	.has_mba_logs = true,
	.has_spare_reg = true,
	.version = MSS_SC7180,
पूर्ण;

अटल स्थिर काष्ठा rproc_hexagon_res sdm845_mss = अणु
	.hexagon_mba_image = "mba.mbn",
	.proxy_clk_names = (अक्षर*[])अणु
			"xo",
			"prng",
			शून्य
	पूर्ण,
	.reset_clk_names = (अक्षर*[])अणु
			"iface",
			"snoc_axi",
			शून्य
	पूर्ण,
	.active_clk_names = (अक्षर*[])अणु
			"bus",
			"mem",
			"gpll0_mss",
			"mnoc_axi",
			शून्य
	पूर्ण,
	.active_pd_names = (अक्षर*[])अणु
			"load_state",
			शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
			"cx",
			"mx",
			"mss",
			शून्य
	पूर्ण,
	.need_mem_protection = true,
	.has_alt_reset = true,
	.has_mba_logs = false,
	.has_spare_reg = false,
	.version = MSS_SDM845,
पूर्ण;

अटल स्थिर काष्ठा rproc_hexagon_res msm8998_mss = अणु
	.hexagon_mba_image = "mba.mbn",
	.proxy_clk_names = (अक्षर*[])अणु
			"xo",
			"qdss",
			"mem",
			शून्य
	पूर्ण,
	.active_clk_names = (अक्षर*[])अणु
			"iface",
			"bus",
			"gpll0_mss",
			"mnoc_axi",
			"snoc_axi",
			शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
			"cx",
			"mx",
			शून्य
	पूर्ण,
	.need_mem_protection = true,
	.has_alt_reset = false,
	.has_mba_logs = false,
	.has_spare_reg = false,
	.version = MSS_MSM8998,
पूर्ण;

अटल स्थिर काष्ठा rproc_hexagon_res msm8996_mss = अणु
	.hexagon_mba_image = "mba.mbn",
	.proxy_supply = (काष्ठा qcom_mss_reg_res[]) अणु
		अणु
			.supply = "pll",
			.uA = 100000,
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	.proxy_clk_names = (अक्षर*[])अणु
			"xo",
			"pnoc",
			"qdss",
			शून्य
	पूर्ण,
	.active_clk_names = (अक्षर*[])अणु
			"iface",
			"bus",
			"mem",
			"gpll0_mss",
			"snoc_axi",
			"mnoc_axi",
			शून्य
	पूर्ण,
	.need_mem_protection = true,
	.has_alt_reset = false,
	.has_mba_logs = false,
	.has_spare_reg = false,
	.version = MSS_MSM8996,
पूर्ण;

अटल स्थिर काष्ठा rproc_hexagon_res msm8916_mss = अणु
	.hexagon_mba_image = "mba.mbn",
	.proxy_supply = (काष्ठा qcom_mss_reg_res[]) अणु
		अणु
			.supply = "pll",
			.uA = 100000,
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	.fallback_proxy_supply = (काष्ठा qcom_mss_reg_res[]) अणु
		अणु
			.supply = "mx",
			.uV = 1050000,
		पूर्ण,
		अणु
			.supply = "cx",
			.uA = 100000,
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	.proxy_clk_names = (अक्षर*[])अणु
		"xo",
		शून्य
	पूर्ण,
	.active_clk_names = (अक्षर*[])अणु
		"iface",
		"bus",
		"mem",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"mx",
		"cx",
		शून्य
	पूर्ण,
	.need_mem_protection = false,
	.has_alt_reset = false,
	.has_mba_logs = false,
	.has_spare_reg = false,
	.version = MSS_MSM8916,
पूर्ण;

अटल स्थिर काष्ठा rproc_hexagon_res msm8974_mss = अणु
	.hexagon_mba_image = "mba.b00",
	.proxy_supply = (काष्ठा qcom_mss_reg_res[]) अणु
		अणु
			.supply = "pll",
			.uA = 100000,
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	.fallback_proxy_supply = (काष्ठा qcom_mss_reg_res[]) अणु
		अणु
			.supply = "mx",
			.uV = 1050000,
		पूर्ण,
		अणु
			.supply = "cx",
			.uA = 100000,
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	.active_supply = (काष्ठा qcom_mss_reg_res[]) अणु
		अणु
			.supply = "mss",
			.uV = 1050000,
			.uA = 100000,
		पूर्ण,
		अणुपूर्ण
	पूर्ण,
	.proxy_clk_names = (अक्षर*[])अणु
		"xo",
		शून्य
	पूर्ण,
	.active_clk_names = (अक्षर*[])अणु
		"iface",
		"bus",
		"mem",
		शून्य
	पूर्ण,
	.proxy_pd_names = (अक्षर*[])अणु
		"mx",
		"cx",
		शून्य
	पूर्ण,
	.need_mem_protection = false,
	.has_alt_reset = false,
	.has_mba_logs = false,
	.has_spare_reg = false,
	.version = MSS_MSM8974,
पूर्ण;

अटल स्थिर काष्ठा of_device_id q6v5_of_match[] = अणु
	अणु .compatible = "qcom,q6v5-pil", .data = &msm8916_mssपूर्ण,
	अणु .compatible = "qcom,msm8916-mss-pil", .data = &msm8916_mssपूर्ण,
	अणु .compatible = "qcom,msm8974-mss-pil", .data = &msm8974_mssपूर्ण,
	अणु .compatible = "qcom,msm8996-mss-pil", .data = &msm8996_mssपूर्ण,
	अणु .compatible = "qcom,msm8998-mss-pil", .data = &msm8998_mssपूर्ण,
	अणु .compatible = "qcom,sc7180-mss-pil", .data = &sc7180_mssपूर्ण,
	अणु .compatible = "qcom,sdm845-mss-pil", .data = &sdm845_mssपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6v5_of_match);

अटल काष्ठा platक्रमm_driver q6v5_driver = अणु
	.probe = q6v5_probe,
	.हटाओ = q6v5_हटाओ,
	.driver = अणु
		.name = "qcom-q6v5-mss",
		.of_match_table = q6v5_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(q6v5_driver);

MODULE_DESCRIPTION("Qualcomm Self-authenticating modem remoteproc driver");
MODULE_LICENSE("GPL v2");
