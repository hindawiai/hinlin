<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (c) 2019, Linaro Limited
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/clk.h>
#समावेश <linux/nvmem-consumer.h>

/* Register Offsets क्रम RB-CPR and Bit Definitions */

/* RBCPR Version Register */
#घोषणा REG_RBCPR_VERSION		0
#घोषणा RBCPR_VER_2			0x02
#घोषणा FLAGS_IGNORE_1ST_IRQ_STATUS	BIT(0)

/* RBCPR Gate Count and Target Registers */
#घोषणा REG_RBCPR_GCNT_TARGET(n)	(0x60 + 4 * (n))

#घोषणा RBCPR_GCNT_TARGET_TARGET_SHIFT	0
#घोषणा RBCPR_GCNT_TARGET_TARGET_MASK	GENMASK(11, 0)
#घोषणा RBCPR_GCNT_TARGET_GCNT_SHIFT	12
#घोषणा RBCPR_GCNT_TARGET_GCNT_MASK	GENMASK(9, 0)

/* RBCPR Timer Control */
#घोषणा REG_RBCPR_TIMER_INTERVAL	0x44
#घोषणा REG_RBIF_TIMER_ADJUST		0x4c

#घोषणा RBIF_TIMER_ADJ_CONS_UP_MASK	GENMASK(3, 0)
#घोषणा RBIF_TIMER_ADJ_CONS_UP_SHIFT	0
#घोषणा RBIF_TIMER_ADJ_CONS_DOWN_MASK	GENMASK(3, 0)
#घोषणा RBIF_TIMER_ADJ_CONS_DOWN_SHIFT	4
#घोषणा RBIF_TIMER_ADJ_CLAMP_INT_MASK	GENMASK(7, 0)
#घोषणा RBIF_TIMER_ADJ_CLAMP_INT_SHIFT	8

/* RBCPR Config Register */
#घोषणा REG_RBIF_LIMIT			0x48
#घोषणा RBIF_LIMIT_CEILING_MASK		GENMASK(5, 0)
#घोषणा RBIF_LIMIT_CEILING_SHIFT	6
#घोषणा RBIF_LIMIT_FLOOR_BITS		6
#घोषणा RBIF_LIMIT_FLOOR_MASK		GENMASK(5, 0)

#घोषणा RBIF_LIMIT_CEILING_DEFAULT	RBIF_LIMIT_CEILING_MASK
#घोषणा RBIF_LIMIT_FLOOR_DEFAULT	0

#घोषणा REG_RBIF_SW_VLEVEL		0x94
#घोषणा RBIF_SW_VLEVEL_DEFAULT		0x20

#घोषणा REG_RBCPR_STEP_QUOT		0x80
#घोषणा RBCPR_STEP_QUOT_STEPQUOT_MASK	GENMASK(7, 0)
#घोषणा RBCPR_STEP_QUOT_IDLE_CLK_MASK	GENMASK(3, 0)
#घोषणा RBCPR_STEP_QUOT_IDLE_CLK_SHIFT	8

/* RBCPR Control Register */
#घोषणा REG_RBCPR_CTL			0x90

#घोषणा RBCPR_CTL_LOOP_EN			BIT(0)
#घोषणा RBCPR_CTL_TIMER_EN			BIT(3)
#घोषणा RBCPR_CTL_SW_AUTO_CONT_ACK_EN		BIT(5)
#घोषणा RBCPR_CTL_SW_AUTO_CONT_NACK_DN_EN	BIT(6)
#घोषणा RBCPR_CTL_COUNT_MODE			BIT(10)
#घोषणा RBCPR_CTL_UP_THRESHOLD_MASK	GENMASK(3, 0)
#घोषणा RBCPR_CTL_UP_THRESHOLD_SHIFT	24
#घोषणा RBCPR_CTL_DN_THRESHOLD_MASK	GENMASK(3, 0)
#घोषणा RBCPR_CTL_DN_THRESHOLD_SHIFT	28

/* RBCPR Ack/Nack Response */
#घोषणा REG_RBIF_CONT_ACK_CMD		0x98
#घोषणा REG_RBIF_CONT_NACK_CMD		0x9c

/* RBCPR Result status Register */
#घोषणा REG_RBCPR_RESULT_0		0xa0

#घोषणा RBCPR_RESULT0_BUSY_SHIFT	19
#घोषणा RBCPR_RESULT0_BUSY_MASK		BIT(RBCPR_RESULT0_BUSY_SHIFT)
#घोषणा RBCPR_RESULT0_ERROR_LT0_SHIFT	18
#घोषणा RBCPR_RESULT0_ERROR_SHIFT	6
#घोषणा RBCPR_RESULT0_ERROR_MASK	GENMASK(11, 0)
#घोषणा RBCPR_RESULT0_ERROR_STEPS_SHIFT	2
#घोषणा RBCPR_RESULT0_ERROR_STEPS_MASK	GENMASK(3, 0)
#घोषणा RBCPR_RESULT0_STEP_UP_SHIFT	1

/* RBCPR Interrupt Control Register */
#घोषणा REG_RBIF_IRQ_EN(n)		(0x100 + 4 * (n))
#घोषणा REG_RBIF_IRQ_CLEAR		0x110
#घोषणा REG_RBIF_IRQ_STATUS		0x114

#घोषणा CPR_INT_DONE		BIT(0)
#घोषणा CPR_पूर्णांक_न्यून		BIT(1)
#घोषणा CPR_INT_DOWN		BIT(2)
#घोषणा CPR_INT_MID		BIT(3)
#घोषणा CPR_INT_UP		BIT(4)
#घोषणा CPR_पूर्णांक_उच्च		BIT(5)
#घोषणा CPR_INT_CLAMP		BIT(6)
#घोषणा CPR_INT_ALL	(CPR_INT_DONE | CPR_पूर्णांक_न्यून | CPR_INT_DOWN | \
			CPR_INT_MID | CPR_INT_UP | CPR_पूर्णांक_उच्च | CPR_INT_CLAMP)
#घोषणा CPR_INT_DEFAULT	(CPR_INT_UP | CPR_INT_DOWN)

#घोषणा CPR_NUM_RING_OSC	8

/* CPR eFuse parameters */
#घोषणा CPR_FUSE_TARGET_QUOT_BITS_MASK	GENMASK(11, 0)

#घोषणा CPR_FUSE_MIN_QUOT_DIFF		50

#घोषणा FUSE_REVISION_UNKNOWN		(-1)

क्रमागत voltage_change_dir अणु
	NO_CHANGE,
	DOWN,
	UP,
पूर्ण;

काष्ठा cpr_fuse अणु
	अक्षर *ring_osc;
	अक्षर *init_voltage;
	अक्षर *quotient;
	अक्षर *quotient_offset;
पूर्ण;

काष्ठा fuse_corner_data अणु
	पूर्णांक ref_uV;
	पूर्णांक max_uV;
	पूर्णांक min_uV;
	पूर्णांक max_volt_scale;
	पूर्णांक max_quot_scale;
	/* fuse quot */
	पूर्णांक quot_offset;
	पूर्णांक quot_scale;
	पूर्णांक quot_adjust;
	/* fuse quot_offset */
	पूर्णांक quot_offset_scale;
	पूर्णांक quot_offset_adjust;
पूर्ण;

काष्ठा cpr_fuses अणु
	पूर्णांक init_voltage_step;
	पूर्णांक init_voltage_width;
	काष्ठा fuse_corner_data *fuse_corner_data;
पूर्ण;

काष्ठा corner_data अणु
	अचिन्हित पूर्णांक fuse_corner;
	अचिन्हित दीर्घ freq;
पूर्ण;

काष्ठा cpr_desc अणु
	अचिन्हित पूर्णांक num_fuse_corners;
	पूर्णांक min_dअगरf_quot;
	पूर्णांक *step_quot;

	अचिन्हित पूर्णांक		समयr_delay_us;
	अचिन्हित पूर्णांक		समयr_cons_up;
	अचिन्हित पूर्णांक		समयr_cons_करोwn;
	अचिन्हित पूर्णांक		up_threshold;
	अचिन्हित पूर्णांक		करोwn_threshold;
	अचिन्हित पूर्णांक		idle_घड़ीs;
	अचिन्हित पूर्णांक		gcnt_us;
	अचिन्हित पूर्णांक		vdd_apc_step_up_limit;
	अचिन्हित पूर्णांक		vdd_apc_step_करोwn_limit;
	अचिन्हित पूर्णांक		clamp_समयr_पूर्णांकerval;

	काष्ठा cpr_fuses cpr_fuses;
	bool reduce_to_fuse_uV;
	bool reduce_to_corner_uV;
पूर्ण;

काष्ठा acc_desc अणु
	अचिन्हित पूर्णांक	enable_reg;
	u32		enable_mask;

	काष्ठा reg_sequence	*config;
	काष्ठा reg_sequence	*settings;
	पूर्णांक			num_regs_per_fuse;
पूर्ण;

काष्ठा cpr_acc_desc अणु
	स्थिर काष्ठा cpr_desc *cpr_desc;
	स्थिर काष्ठा acc_desc *acc_desc;
पूर्ण;

काष्ठा fuse_corner अणु
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	पूर्णांक uV;
	पूर्णांक quot;
	पूर्णांक step_quot;
	स्थिर काष्ठा reg_sequence *accs;
	पूर्णांक num_accs;
	अचिन्हित दीर्घ max_freq;
	u8 ring_osc_idx;
पूर्ण;

काष्ठा corner अणु
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	पूर्णांक uV;
	पूर्णांक last_uV;
	पूर्णांक quot_adjust;
	u32 save_ctl;
	u32 save_irq;
	अचिन्हित दीर्घ freq;
	काष्ठा fuse_corner *fuse_corner;
पूर्ण;

काष्ठा cpr_drv अणु
	अचिन्हित पूर्णांक		num_corners;
	अचिन्हित पूर्णांक		ref_clk_khz;

	काष्ठा generic_pm_करोमुख्य pd;
	काष्ठा device		*dev;
	काष्ठा device		*attached_cpu_dev;
	काष्ठा mutex		lock;
	व्योम __iomem		*base;
	काष्ठा corner		*corner;
	काष्ठा regulator	*vdd_apc;
	काष्ठा clk		*cpu_clk;
	काष्ठा regmap		*tcsr;
	bool			loop_disabled;
	u32			gcnt;
	अचिन्हित दीर्घ		flags;

	काष्ठा fuse_corner	*fuse_corners;
	काष्ठा corner		*corners;

	स्थिर काष्ठा cpr_desc *desc;
	स्थिर काष्ठा acc_desc *acc_desc;
	स्थिर काष्ठा cpr_fuse *cpr_fuses;

	काष्ठा dentry *debugfs;
पूर्ण;

अटल bool cpr_is_allowed(काष्ठा cpr_drv *drv)
अणु
	वापस !drv->loop_disabled;
पूर्ण

अटल व्योम cpr_ग_लिखो(काष्ठा cpr_drv *drv, u32 offset, u32 value)
अणु
	ग_लिखोl_relaxed(value, drv->base + offset);
पूर्ण

अटल u32 cpr_पढ़ो(काष्ठा cpr_drv *drv, u32 offset)
अणु
	वापस पढ़ोl_relaxed(drv->base + offset);
पूर्ण

अटल व्योम
cpr_masked_ग_लिखो(काष्ठा cpr_drv *drv, u32 offset, u32 mask, u32 value)
अणु
	u32 val;

	val = पढ़ोl_relaxed(drv->base + offset);
	val &= ~mask;
	val |= value & mask;
	ग_लिखोl_relaxed(val, drv->base + offset);
पूर्ण

अटल व्योम cpr_irq_clr(काष्ठा cpr_drv *drv)
अणु
	cpr_ग_लिखो(drv, REG_RBIF_IRQ_CLEAR, CPR_INT_ALL);
पूर्ण

अटल व्योम cpr_irq_clr_nack(काष्ठा cpr_drv *drv)
अणु
	cpr_irq_clr(drv);
	cpr_ग_लिखो(drv, REG_RBIF_CONT_NACK_CMD, 1);
पूर्ण

अटल व्योम cpr_irq_clr_ack(काष्ठा cpr_drv *drv)
अणु
	cpr_irq_clr(drv);
	cpr_ग_लिखो(drv, REG_RBIF_CONT_ACK_CMD, 1);
पूर्ण

अटल व्योम cpr_irq_set(काष्ठा cpr_drv *drv, u32 पूर्णांक_bits)
अणु
	cpr_ग_लिखो(drv, REG_RBIF_IRQ_EN(0), पूर्णांक_bits);
पूर्ण

अटल व्योम cpr_ctl_modअगरy(काष्ठा cpr_drv *drv, u32 mask, u32 value)
अणु
	cpr_masked_ग_लिखो(drv, REG_RBCPR_CTL, mask, value);
पूर्ण

अटल व्योम cpr_ctl_enable(काष्ठा cpr_drv *drv, काष्ठा corner *corner)
अणु
	u32 val, mask;
	स्थिर काष्ठा cpr_desc *desc = drv->desc;

	/* Program Consecutive Up & Down */
	val = desc->समयr_cons_करोwn << RBIF_TIMER_ADJ_CONS_DOWN_SHIFT;
	val |= desc->समयr_cons_up << RBIF_TIMER_ADJ_CONS_UP_SHIFT;
	mask = RBIF_TIMER_ADJ_CONS_UP_MASK | RBIF_TIMER_ADJ_CONS_DOWN_MASK;
	cpr_masked_ग_लिखो(drv, REG_RBIF_TIMER_ADJUST, mask, val);
	cpr_masked_ग_लिखो(drv, REG_RBCPR_CTL,
			 RBCPR_CTL_SW_AUTO_CONT_NACK_DN_EN |
			 RBCPR_CTL_SW_AUTO_CONT_ACK_EN,
			 corner->save_ctl);
	cpr_irq_set(drv, corner->save_irq);

	अगर (cpr_is_allowed(drv) && corner->max_uV > corner->min_uV)
		val = RBCPR_CTL_LOOP_EN;
	अन्यथा
		val = 0;
	cpr_ctl_modअगरy(drv, RBCPR_CTL_LOOP_EN, val);
पूर्ण

अटल व्योम cpr_ctl_disable(काष्ठा cpr_drv *drv)
अणु
	cpr_irq_set(drv, 0);
	cpr_ctl_modअगरy(drv, RBCPR_CTL_SW_AUTO_CONT_NACK_DN_EN |
		       RBCPR_CTL_SW_AUTO_CONT_ACK_EN, 0);
	cpr_masked_ग_लिखो(drv, REG_RBIF_TIMER_ADJUST,
			 RBIF_TIMER_ADJ_CONS_UP_MASK |
			 RBIF_TIMER_ADJ_CONS_DOWN_MASK, 0);
	cpr_irq_clr(drv);
	cpr_ग_लिखो(drv, REG_RBIF_CONT_ACK_CMD, 1);
	cpr_ग_लिखो(drv, REG_RBIF_CONT_NACK_CMD, 1);
	cpr_ctl_modअगरy(drv, RBCPR_CTL_LOOP_EN, 0);
पूर्ण

अटल bool cpr_ctl_is_enabled(काष्ठा cpr_drv *drv)
अणु
	u32 reg_val;

	reg_val = cpr_पढ़ो(drv, REG_RBCPR_CTL);
	वापस reg_val & RBCPR_CTL_LOOP_EN;
पूर्ण

अटल bool cpr_ctl_is_busy(काष्ठा cpr_drv *drv)
अणु
	u32 reg_val;

	reg_val = cpr_पढ़ो(drv, REG_RBCPR_RESULT_0);
	वापस reg_val & RBCPR_RESULT0_BUSY_MASK;
पूर्ण

अटल व्योम cpr_corner_save(काष्ठा cpr_drv *drv, काष्ठा corner *corner)
अणु
	corner->save_ctl = cpr_पढ़ो(drv, REG_RBCPR_CTL);
	corner->save_irq = cpr_पढ़ो(drv, REG_RBIF_IRQ_EN(0));
पूर्ण

अटल व्योम cpr_corner_restore(काष्ठा cpr_drv *drv, काष्ठा corner *corner)
अणु
	u32 gcnt, ctl, irq, ro_sel, step_quot;
	काष्ठा fuse_corner *fuse = corner->fuse_corner;
	स्थिर काष्ठा cpr_desc *desc = drv->desc;
	पूर्णांक i;

	ro_sel = fuse->ring_osc_idx;
	gcnt = drv->gcnt;
	gcnt |= fuse->quot - corner->quot_adjust;

	/* Program the step quotient and idle घड़ीs */
	step_quot = desc->idle_घड़ीs << RBCPR_STEP_QUOT_IDLE_CLK_SHIFT;
	step_quot |= fuse->step_quot & RBCPR_STEP_QUOT_STEPQUOT_MASK;
	cpr_ग_लिखो(drv, REG_RBCPR_STEP_QUOT, step_quot);

	/* Clear the target quotient value and gate count of all ROs */
	क्रम (i = 0; i < CPR_NUM_RING_OSC; i++)
		cpr_ग_लिखो(drv, REG_RBCPR_GCNT_TARGET(i), 0);

	cpr_ग_लिखो(drv, REG_RBCPR_GCNT_TARGET(ro_sel), gcnt);
	ctl = corner->save_ctl;
	cpr_ग_लिखो(drv, REG_RBCPR_CTL, ctl);
	irq = corner->save_irq;
	cpr_irq_set(drv, irq);
	dev_dbg(drv->dev, "gcnt = %#08x, ctl = %#08x, irq = %#08x\n", gcnt,
		ctl, irq);
पूर्ण

अटल व्योम cpr_set_acc(काष्ठा regmap *tcsr, काष्ठा fuse_corner *f,
			काष्ठा fuse_corner *end)
अणु
	अगर (f == end)
		वापस;

	अगर (f < end) अणु
		क्रम (f += 1; f <= end; f++)
			regmap_multi_reg_ग_लिखो(tcsr, f->accs, f->num_accs);
	पूर्ण अन्यथा अणु
		क्रम (f -= 1; f >= end; f--)
			regmap_multi_reg_ग_लिखो(tcsr, f->accs, f->num_accs);
	पूर्ण
पूर्ण

अटल पूर्णांक cpr_pre_voltage(काष्ठा cpr_drv *drv,
			   काष्ठा fuse_corner *fuse_corner,
			   क्रमागत voltage_change_dir dir)
अणु
	काष्ठा fuse_corner *prev_fuse_corner = drv->corner->fuse_corner;

	अगर (drv->tcsr && dir == DOWN)
		cpr_set_acc(drv->tcsr, prev_fuse_corner, fuse_corner);

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_post_voltage(काष्ठा cpr_drv *drv,
			    काष्ठा fuse_corner *fuse_corner,
			    क्रमागत voltage_change_dir dir)
अणु
	काष्ठा fuse_corner *prev_fuse_corner = drv->corner->fuse_corner;

	अगर (drv->tcsr && dir == UP)
		cpr_set_acc(drv->tcsr, prev_fuse_corner, fuse_corner);

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_scale_voltage(काष्ठा cpr_drv *drv, काष्ठा corner *corner,
			     पूर्णांक new_uV, क्रमागत voltage_change_dir dir)
अणु
	पूर्णांक ret;
	काष्ठा fuse_corner *fuse_corner = corner->fuse_corner;

	ret = cpr_pre_voltage(drv, fuse_corner, dir);
	अगर (ret)
		वापस ret;

	ret = regulator_set_voltage(drv->vdd_apc, new_uV, new_uV);
	अगर (ret) अणु
		dev_err_ratelimited(drv->dev, "failed to set apc voltage %d\n",
				    new_uV);
		वापस ret;
	पूर्ण

	ret = cpr_post_voltage(drv, fuse_corner, dir);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक cpr_get_cur_perf_state(काष्ठा cpr_drv *drv)
अणु
	वापस drv->corner ? drv->corner - drv->corners + 1 : 0;
पूर्ण

अटल पूर्णांक cpr_scale(काष्ठा cpr_drv *drv, क्रमागत voltage_change_dir dir)
अणु
	u32 val, error_steps, reg_mask;
	पूर्णांक last_uV, new_uV, step_uV, ret;
	काष्ठा corner *corner;
	स्थिर काष्ठा cpr_desc *desc = drv->desc;

	अगर (dir != UP && dir != DOWN)
		वापस 0;

	step_uV = regulator_get_linear_step(drv->vdd_apc);
	अगर (!step_uV)
		वापस -EINVAL;

	corner = drv->corner;

	val = cpr_पढ़ो(drv, REG_RBCPR_RESULT_0);

	error_steps = val >> RBCPR_RESULT0_ERROR_STEPS_SHIFT;
	error_steps &= RBCPR_RESULT0_ERROR_STEPS_MASK;
	last_uV = corner->last_uV;

	अगर (dir == UP) अणु
		अगर (desc->clamp_समयr_पूर्णांकerval &&
		    error_steps < desc->up_threshold) अणु
			/*
			 * Handle the हाल where another measurement started
			 * after the पूर्णांकerrupt was triggered due to a core
			 * निकासing from घातer collapse.
			 */
			error_steps = max(desc->up_threshold,
					  desc->vdd_apc_step_up_limit);
		पूर्ण

		अगर (last_uV >= corner->max_uV) अणु
			cpr_irq_clr_nack(drv);

			/* Maximize the UP threshold */
			reg_mask = RBCPR_CTL_UP_THRESHOLD_MASK;
			reg_mask <<= RBCPR_CTL_UP_THRESHOLD_SHIFT;
			val = reg_mask;
			cpr_ctl_modअगरy(drv, reg_mask, val);

			/* Disable UP पूर्णांकerrupt */
			cpr_irq_set(drv, CPR_INT_DEFAULT & ~CPR_INT_UP);

			वापस 0;
		पूर्ण

		अगर (error_steps > desc->vdd_apc_step_up_limit)
			error_steps = desc->vdd_apc_step_up_limit;

		/* Calculate new voltage */
		new_uV = last_uV + error_steps * step_uV;
		new_uV = min(new_uV, corner->max_uV);

		dev_dbg(drv->dev,
			"UP: -> new_uV: %d last_uV: %d perf state: %u\n",
			new_uV, last_uV, cpr_get_cur_perf_state(drv));
	पूर्ण अन्यथा अणु
		अगर (desc->clamp_समयr_पूर्णांकerval &&
		    error_steps < desc->करोwn_threshold) अणु
			/*
			 * Handle the हाल where another measurement started
			 * after the पूर्णांकerrupt was triggered due to a core
			 * निकासing from घातer collapse.
			 */
			error_steps = max(desc->करोwn_threshold,
					  desc->vdd_apc_step_करोwn_limit);
		पूर्ण

		अगर (last_uV <= corner->min_uV) अणु
			cpr_irq_clr_nack(drv);

			/* Enable स्वतः nack करोwn */
			reg_mask = RBCPR_CTL_SW_AUTO_CONT_NACK_DN_EN;
			val = RBCPR_CTL_SW_AUTO_CONT_NACK_DN_EN;

			cpr_ctl_modअगरy(drv, reg_mask, val);

			/* Disable DOWN पूर्णांकerrupt */
			cpr_irq_set(drv, CPR_INT_DEFAULT & ~CPR_INT_DOWN);

			वापस 0;
		पूर्ण

		अगर (error_steps > desc->vdd_apc_step_करोwn_limit)
			error_steps = desc->vdd_apc_step_करोwn_limit;

		/* Calculate new voltage */
		new_uV = last_uV - error_steps * step_uV;
		new_uV = max(new_uV, corner->min_uV);

		dev_dbg(drv->dev,
			"DOWN: -> new_uV: %d last_uV: %d perf state: %u\n",
			new_uV, last_uV, cpr_get_cur_perf_state(drv));
	पूर्ण

	ret = cpr_scale_voltage(drv, corner, new_uV, dir);
	अगर (ret) अणु
		cpr_irq_clr_nack(drv);
		वापस ret;
	पूर्ण
	drv->corner->last_uV = new_uV;

	अगर (dir == UP) अणु
		/* Disable स्वतः nack करोwn */
		reg_mask = RBCPR_CTL_SW_AUTO_CONT_NACK_DN_EN;
		val = 0;
	पूर्ण अन्यथा अणु
		/* Restore शेष threshold क्रम UP */
		reg_mask = RBCPR_CTL_UP_THRESHOLD_MASK;
		reg_mask <<= RBCPR_CTL_UP_THRESHOLD_SHIFT;
		val = desc->up_threshold;
		val <<= RBCPR_CTL_UP_THRESHOLD_SHIFT;
	पूर्ण

	cpr_ctl_modअगरy(drv, reg_mask, val);

	/* Re-enable शेष पूर्णांकerrupts */
	cpr_irq_set(drv, CPR_INT_DEFAULT);

	/* Ack */
	cpr_irq_clr_ack(drv);

	वापस 0;
पूर्ण

अटल irqवापस_t cpr_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा cpr_drv *drv = dev;
	स्थिर काष्ठा cpr_desc *desc = drv->desc;
	irqवापस_t ret = IRQ_HANDLED;
	u32 val;

	mutex_lock(&drv->lock);

	val = cpr_पढ़ो(drv, REG_RBIF_IRQ_STATUS);
	अगर (drv->flags & FLAGS_IGNORE_1ST_IRQ_STATUS)
		val = cpr_पढ़ो(drv, REG_RBIF_IRQ_STATUS);

	dev_dbg(drv->dev, "IRQ_STATUS = %#02x\n", val);

	अगर (!cpr_ctl_is_enabled(drv)) अणु
		dev_dbg(drv->dev, "CPR is disabled\n");
		ret = IRQ_NONE;
	पूर्ण अन्यथा अगर (cpr_ctl_is_busy(drv) && !desc->clamp_समयr_पूर्णांकerval) अणु
		dev_dbg(drv->dev, "CPR measurement is not ready\n");
	पूर्ण अन्यथा अगर (!cpr_is_allowed(drv)) अणु
		val = cpr_पढ़ो(drv, REG_RBCPR_CTL);
		dev_err_ratelimited(drv->dev,
				    "Interrupt broken? RBCPR_CTL = %#02x\n",
				    val);
		ret = IRQ_NONE;
	पूर्ण अन्यथा अणु
		/*
		 * Following sequence of handling is as per each IRQ's
		 * priority
		 */
		अगर (val & CPR_INT_UP) अणु
			cpr_scale(drv, UP);
		पूर्ण अन्यथा अगर (val & CPR_INT_DOWN) अणु
			cpr_scale(drv, DOWN);
		पूर्ण अन्यथा अगर (val & CPR_पूर्णांक_न्यून) अणु
			cpr_irq_clr_nack(drv);
		पूर्ण अन्यथा अगर (val & CPR_पूर्णांक_उच्च) अणु
			cpr_irq_clr_nack(drv);
		पूर्ण अन्यथा अगर (val & CPR_INT_MID) अणु
			/* RBCPR_CTL_SW_AUTO_CONT_ACK_EN is enabled */
			dev_dbg(drv->dev, "IRQ occurred for Mid Flag\n");
		पूर्ण अन्यथा अणु
			dev_dbg(drv->dev,
				"IRQ occurred for unknown flag (%#08x)\n", val);
		पूर्ण

		/* Save रेजिस्टर values क्रम the corner */
		cpr_corner_save(drv, drv->corner);
	पूर्ण

	mutex_unlock(&drv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cpr_enable(काष्ठा cpr_drv *drv)
अणु
	पूर्णांक ret;

	ret = regulator_enable(drv->vdd_apc);
	अगर (ret)
		वापस ret;

	mutex_lock(&drv->lock);

	अगर (cpr_is_allowed(drv) && drv->corner) अणु
		cpr_irq_clr(drv);
		cpr_corner_restore(drv, drv->corner);
		cpr_ctl_enable(drv, drv->corner);
	पूर्ण

	mutex_unlock(&drv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_disable(काष्ठा cpr_drv *drv)
अणु
	mutex_lock(&drv->lock);

	अगर (cpr_is_allowed(drv)) अणु
		cpr_ctl_disable(drv);
		cpr_irq_clr(drv);
	पूर्ण

	mutex_unlock(&drv->lock);

	वापस regulator_disable(drv->vdd_apc);
पूर्ण

अटल पूर्णांक cpr_config(काष्ठा cpr_drv *drv)
अणु
	पूर्णांक i;
	u32 val, gcnt;
	काष्ठा corner *corner;
	स्थिर काष्ठा cpr_desc *desc = drv->desc;

	/* Disable पूर्णांकerrupt and CPR */
	cpr_ग_लिखो(drv, REG_RBIF_IRQ_EN(0), 0);
	cpr_ग_लिखो(drv, REG_RBCPR_CTL, 0);

	/* Program the शेष HW उच्चमानing, न्यूनमान and vlevel */
	val = (RBIF_LIMIT_CEILING_DEFAULT & RBIF_LIMIT_CEILING_MASK)
		<< RBIF_LIMIT_CEILING_SHIFT;
	val |= RBIF_LIMIT_FLOOR_DEFAULT & RBIF_LIMIT_FLOOR_MASK;
	cpr_ग_लिखो(drv, REG_RBIF_LIMIT, val);
	cpr_ग_लिखो(drv, REG_RBIF_SW_VLEVEL, RBIF_SW_VLEVEL_DEFAULT);

	/*
	 * Clear the target quotient value and gate count of all
	 * ring oscillators
	 */
	क्रम (i = 0; i < CPR_NUM_RING_OSC; i++)
		cpr_ग_लिखो(drv, REG_RBCPR_GCNT_TARGET(i), 0);

	/* Init and save gcnt */
	gcnt = (drv->ref_clk_khz * desc->gcnt_us) / 1000;
	gcnt = gcnt & RBCPR_GCNT_TARGET_GCNT_MASK;
	gcnt <<= RBCPR_GCNT_TARGET_GCNT_SHIFT;
	drv->gcnt = gcnt;

	/* Program the delay count क्रम the समयr */
	val = (drv->ref_clk_khz * desc->समयr_delay_us) / 1000;
	cpr_ग_लिखो(drv, REG_RBCPR_TIMER_INTERVAL, val);
	dev_dbg(drv->dev, "Timer count: %#0x (for %d us)\n", val,
		desc->समयr_delay_us);

	/* Program Consecutive Up & Down */
	val = desc->समयr_cons_करोwn << RBIF_TIMER_ADJ_CONS_DOWN_SHIFT;
	val |= desc->समयr_cons_up << RBIF_TIMER_ADJ_CONS_UP_SHIFT;
	val |= desc->clamp_समयr_पूर्णांकerval << RBIF_TIMER_ADJ_CLAMP_INT_SHIFT;
	cpr_ग_लिखो(drv, REG_RBIF_TIMER_ADJUST, val);

	/* Program the control रेजिस्टर */
	val = desc->up_threshold << RBCPR_CTL_UP_THRESHOLD_SHIFT;
	val |= desc->करोwn_threshold << RBCPR_CTL_DN_THRESHOLD_SHIFT;
	val |= RBCPR_CTL_TIMER_EN | RBCPR_CTL_COUNT_MODE;
	val |= RBCPR_CTL_SW_AUTO_CONT_ACK_EN;
	cpr_ग_लिखो(drv, REG_RBCPR_CTL, val);

	क्रम (i = 0; i < drv->num_corners; i++) अणु
		corner = &drv->corners[i];
		corner->save_ctl = val;
		corner->save_irq = CPR_INT_DEFAULT;
	पूर्ण

	cpr_irq_set(drv, CPR_INT_DEFAULT);

	val = cpr_पढ़ो(drv, REG_RBCPR_VERSION);
	अगर (val <= RBCPR_VER_2)
		drv->flags |= FLAGS_IGNORE_1ST_IRQ_STATUS;

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_set_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक state)
अणु
	काष्ठा cpr_drv *drv = container_of(करोमुख्य, काष्ठा cpr_drv, pd);
	काष्ठा corner *corner, *end;
	क्रमागत voltage_change_dir dir;
	पूर्णांक ret = 0, new_uV;

	mutex_lock(&drv->lock);

	dev_dbg(drv->dev, "%s: setting perf state: %u (prev state: %u)\n",
		__func__, state, cpr_get_cur_perf_state(drv));

	/*
	 * Determine new corner we're going to.
	 * Remove one since lowest perक्रमmance state is 1.
	 */
	corner = drv->corners + state - 1;
	end = &drv->corners[drv->num_corners - 1];
	अगर (corner > end || corner < drv->corners) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	/* Determine direction */
	अगर (drv->corner > corner)
		dir = DOWN;
	अन्यथा अगर (drv->corner < corner)
		dir = UP;
	अन्यथा
		dir = NO_CHANGE;

	अगर (cpr_is_allowed(drv))
		new_uV = corner->last_uV;
	अन्यथा
		new_uV = corner->uV;

	अगर (cpr_is_allowed(drv))
		cpr_ctl_disable(drv);

	ret = cpr_scale_voltage(drv, corner, new_uV, dir);
	अगर (ret)
		जाओ unlock;

	अगर (cpr_is_allowed(drv)) अणु
		cpr_irq_clr(drv);
		अगर (drv->corner != corner)
			cpr_corner_restore(drv, corner);
		cpr_ctl_enable(drv, corner);
	पूर्ण

	drv->corner = corner;

unlock:
	mutex_unlock(&drv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cpr_पढ़ो_efuse(काष्ठा device *dev, स्थिर अक्षर *cname, u32 *data)
अणु
	काष्ठा nvmem_cell *cell;
	sमाप_प्रकार len;
	अक्षर *ret;
	पूर्णांक i;

	*data = 0;

	cell = nvmem_cell_get(dev, cname);
	अगर (IS_ERR(cell)) अणु
		अगर (PTR_ERR(cell) != -EPROBE_DEFER)
			dev_err(dev, "undefined cell %s\n", cname);
		वापस PTR_ERR(cell);
	पूर्ण

	ret = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);
	अगर (IS_ERR(ret)) अणु
		dev_err(dev, "can't read cell %s\n", cname);
		वापस PTR_ERR(ret);
	पूर्ण

	क्रम (i = 0; i < len; i++)
		*data |= ret[i] << (8 * i);

	kमुक्त(ret);
	dev_dbg(dev, "efuse read(%s) = %x, bytes %zd\n", cname, *data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक
cpr_populate_ring_osc_idx(काष्ठा cpr_drv *drv)
अणु
	काष्ठा fuse_corner *fuse = drv->fuse_corners;
	काष्ठा fuse_corner *end = fuse + drv->desc->num_fuse_corners;
	स्थिर काष्ठा cpr_fuse *fuses = drv->cpr_fuses;
	u32 data;
	पूर्णांक ret;

	क्रम (; fuse < end; fuse++, fuses++) अणु
		ret = cpr_पढ़ो_efuse(drv->dev, fuses->ring_osc,
				     &data);
		अगर (ret)
			वापस ret;
		fuse->ring_osc_idx = data;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_पढ़ो_fuse_uV(स्थिर काष्ठा cpr_desc *desc,
			    स्थिर काष्ठा fuse_corner_data *fdata,
			    स्थिर अक्षर *init_v_efuse,
			    पूर्णांक step_volt,
			    काष्ठा cpr_drv *drv)
अणु
	पूर्णांक step_size_uV, steps, uV;
	u32 bits = 0;
	पूर्णांक ret;

	ret = cpr_पढ़ो_efuse(drv->dev, init_v_efuse, &bits);
	अगर (ret)
		वापस ret;

	steps = bits & ~BIT(desc->cpr_fuses.init_voltage_width - 1);
	/* Not two's complement.. instead highest bit is sign bit */
	अगर (bits & BIT(desc->cpr_fuses.init_voltage_width - 1))
		steps = -steps;

	step_size_uV = desc->cpr_fuses.init_voltage_step;

	uV = fdata->ref_uV + steps * step_size_uV;
	वापस DIV_ROUND_UP(uV, step_volt) * step_volt;
पूर्ण

अटल पूर्णांक cpr_fuse_corner_init(काष्ठा cpr_drv *drv)
अणु
	स्थिर काष्ठा cpr_desc *desc = drv->desc;
	स्थिर काष्ठा cpr_fuse *fuses = drv->cpr_fuses;
	स्थिर काष्ठा acc_desc *acc_desc = drv->acc_desc;
	पूर्णांक i;
	अचिन्हित पूर्णांक step_volt;
	काष्ठा fuse_corner_data *fdata;
	काष्ठा fuse_corner *fuse, *end;
	पूर्णांक uV;
	स्थिर काष्ठा reg_sequence *accs;
	पूर्णांक ret;

	accs = acc_desc->settings;

	step_volt = regulator_get_linear_step(drv->vdd_apc);
	अगर (!step_volt)
		वापस -EINVAL;

	/* Populate fuse_corner members */
	fuse = drv->fuse_corners;
	end = &fuse[desc->num_fuse_corners - 1];
	fdata = desc->cpr_fuses.fuse_corner_data;

	क्रम (i = 0; fuse <= end; fuse++, fuses++, i++, fdata++) अणु
		/*
		 * Update SoC voltages: platक्रमms might choose a dअगरferent
		 * regulators than the one used to अक्षरacterize the algorithms
		 * (ie, init_voltage_step).
		 */
		fdata->min_uV = roundup(fdata->min_uV, step_volt);
		fdata->max_uV = roundup(fdata->max_uV, step_volt);

		/* Populate uV */
		uV = cpr_पढ़ो_fuse_uV(desc, fdata, fuses->init_voltage,
				      step_volt, drv);
		अगर (uV < 0)
			वापस uV;

		fuse->min_uV = fdata->min_uV;
		fuse->max_uV = fdata->max_uV;
		fuse->uV = clamp(uV, fuse->min_uV, fuse->max_uV);

		अगर (fuse == end) अणु
			/*
			 * Allow the highest fuse corner's PVS voltage to
			 * define the उच्चमानing voltage क्रम that corner in order
			 * to support SoC's in which variable उच्चमानing values
			 * are required.
			 */
			end->max_uV = max(end->max_uV, end->uV);
		पूर्ण

		/* Populate target quotient by scaling */
		ret = cpr_पढ़ो_efuse(drv->dev, fuses->quotient, &fuse->quot);
		अगर (ret)
			वापस ret;

		fuse->quot *= fdata->quot_scale;
		fuse->quot += fdata->quot_offset;
		fuse->quot += fdata->quot_adjust;
		fuse->step_quot = desc->step_quot[fuse->ring_osc_idx];

		/* Populate acc settings */
		fuse->accs = accs;
		fuse->num_accs = acc_desc->num_regs_per_fuse;
		accs += acc_desc->num_regs_per_fuse;
	पूर्ण

	/*
	 * Restrict all fuse corner PVS voltages based upon per corner
	 * उच्चमानing and न्यूनमान voltages.
	 */
	क्रम (fuse = drv->fuse_corners, i = 0; fuse <= end; fuse++, i++) अणु
		अगर (fuse->uV > fuse->max_uV)
			fuse->uV = fuse->max_uV;
		अन्यथा अगर (fuse->uV < fuse->min_uV)
			fuse->uV = fuse->min_uV;

		ret = regulator_is_supported_voltage(drv->vdd_apc,
						     fuse->min_uV,
						     fuse->min_uV);
		अगर (!ret) अणु
			dev_err(drv->dev,
				"min uV: %d (fuse corner: %d) not supported by regulator\n",
				fuse->min_uV, i);
			वापस -EINVAL;
		पूर्ण

		ret = regulator_is_supported_voltage(drv->vdd_apc,
						     fuse->max_uV,
						     fuse->max_uV);
		अगर (!ret) अणु
			dev_err(drv->dev,
				"max uV: %d (fuse corner: %d) not supported by regulator\n",
				fuse->max_uV, i);
			वापस -EINVAL;
		पूर्ण

		dev_dbg(drv->dev,
			"fuse corner %d: [%d %d %d] RO%hhu quot %d squot %d\n",
			i, fuse->min_uV, fuse->uV, fuse->max_uV,
			fuse->ring_osc_idx, fuse->quot, fuse->step_quot);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_calculate_scaling(स्थिर अक्षर *quot_offset,
				 काष्ठा cpr_drv *drv,
				 स्थिर काष्ठा fuse_corner_data *fdata,
				 स्थिर काष्ठा corner *corner)
अणु
	u32 quot_dअगरf = 0;
	अचिन्हित दीर्घ freq_dअगरf;
	पूर्णांक scaling;
	स्थिर काष्ठा fuse_corner *fuse, *prev_fuse;
	पूर्णांक ret;

	fuse = corner->fuse_corner;
	prev_fuse = fuse - 1;

	अगर (quot_offset) अणु
		ret = cpr_पढ़ो_efuse(drv->dev, quot_offset, &quot_dअगरf);
		अगर (ret)
			वापस ret;

		quot_dअगरf *= fdata->quot_offset_scale;
		quot_dअगरf += fdata->quot_offset_adjust;
	पूर्ण अन्यथा अणु
		quot_dअगरf = fuse->quot - prev_fuse->quot;
	पूर्ण

	freq_dअगरf = fuse->max_freq - prev_fuse->max_freq;
	freq_dअगरf /= 1000000; /* Convert to MHz */
	scaling = 1000 * quot_dअगरf / freq_dअगरf;
	वापस min(scaling, fdata->max_quot_scale);
पूर्ण

अटल पूर्णांक cpr_पूर्णांकerpolate(स्थिर काष्ठा corner *corner, पूर्णांक step_volt,
			   स्थिर काष्ठा fuse_corner_data *fdata)
अणु
	अचिन्हित दीर्घ f_high, f_low, f_dअगरf;
	पूर्णांक uV_high, uV_low, uV;
	u64 temp, temp_limit;
	स्थिर काष्ठा fuse_corner *fuse, *prev_fuse;

	fuse = corner->fuse_corner;
	prev_fuse = fuse - 1;

	f_high = fuse->max_freq;
	f_low = prev_fuse->max_freq;
	uV_high = fuse->uV;
	uV_low = prev_fuse->uV;
	f_dअगरf = fuse->max_freq - corner->freq;

	/*
	 * Don't पूर्णांकerpolate in the wrong direction. This could happen
	 * अगर the adjusted fuse voltage overlaps with the previous fuse's
	 * adjusted voltage.
	 */
	अगर (f_high <= f_low || uV_high <= uV_low || f_high <= corner->freq)
		वापस corner->uV;

	temp = f_dअगरf * (uV_high - uV_low);
	करो_भाग(temp, f_high - f_low);

	/*
	 * max_volt_scale has units of uV/MHz जबतक freq values
	 * have units of Hz.  Divide by 1000000 to convert to.
	 */
	temp_limit = f_dअगरf * fdata->max_volt_scale;
	करो_भाग(temp_limit, 1000000);

	uV = uV_high - min(temp, temp_limit);
	वापस roundup(uV, step_volt);
पूर्ण

अटल अचिन्हित पूर्णांक cpr_get_fuse_corner(काष्ठा dev_pm_opp *opp)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक fuse_corner = 0;

	np = dev_pm_opp_get_of_node(opp);
	अगर (of_property_पढ़ो_u32(np, "qcom,opp-fuse-level", &fuse_corner))
		pr_err("%s: missing 'qcom,opp-fuse-level' property\n",
		       __func__);

	of_node_put(np);

	वापस fuse_corner;
पूर्ण

अटल अचिन्हित दीर्घ cpr_get_opp_hz_क्रम_req(काष्ठा dev_pm_opp *ref,
					    काष्ठा device *cpu_dev)
अणु
	u64 rate = 0;
	काष्ठा device_node *ref_np;
	काष्ठा device_node *desc_np;
	काष्ठा device_node *child_np = शून्य;
	काष्ठा device_node *child_req_np = शून्य;

	desc_np = dev_pm_opp_of_get_opp_desc_node(cpu_dev);
	अगर (!desc_np)
		वापस 0;

	ref_np = dev_pm_opp_get_of_node(ref);
	अगर (!ref_np)
		जाओ out_ref;

	करो अणु
		of_node_put(child_req_np);
		child_np = of_get_next_available_child(desc_np, child_np);
		child_req_np = of_parse_phandle(child_np, "required-opps", 0);
	पूर्ण जबतक (child_np && child_req_np != ref_np);

	अगर (child_np && child_req_np == ref_np)
		of_property_पढ़ो_u64(child_np, "opp-hz", &rate);

	of_node_put(child_req_np);
	of_node_put(child_np);
	of_node_put(ref_np);
out_ref:
	of_node_put(desc_np);

	वापस (अचिन्हित दीर्घ) rate;
पूर्ण

अटल पूर्णांक cpr_corner_init(काष्ठा cpr_drv *drv)
अणु
	स्थिर काष्ठा cpr_desc *desc = drv->desc;
	स्थिर काष्ठा cpr_fuse *fuses = drv->cpr_fuses;
	पूर्णांक i, level, scaling = 0;
	अचिन्हित पूर्णांक fnum, fc;
	स्थिर अक्षर *quot_offset;
	काष्ठा fuse_corner *fuse, *prev_fuse;
	काष्ठा corner *corner, *end;
	काष्ठा corner_data *cdata;
	स्थिर काष्ठा fuse_corner_data *fdata;
	bool apply_scaling;
	अचिन्हित दीर्घ freq_dअगरf, freq_dअगरf_mhz;
	अचिन्हित दीर्घ freq;
	पूर्णांक step_volt = regulator_get_linear_step(drv->vdd_apc);
	काष्ठा dev_pm_opp *opp;

	अगर (!step_volt)
		वापस -EINVAL;

	corner = drv->corners;
	end = &corner[drv->num_corners - 1];

	cdata = devm_kसुस्मृति(drv->dev, drv->num_corners,
			     माप(काष्ठा corner_data),
			     GFP_KERNEL);
	अगर (!cdata)
		वापस -ENOMEM;

	/*
	 * Store maximum frequency क्रम each fuse corner based on the frequency
	 * plan
	 */
	क्रम (level = 1; level <= drv->num_corners; level++) अणु
		opp = dev_pm_opp_find_level_exact(&drv->pd.dev, level);
		अगर (IS_ERR(opp))
			वापस -EINVAL;
		fc = cpr_get_fuse_corner(opp);
		अगर (!fc) अणु
			dev_pm_opp_put(opp);
			वापस -EINVAL;
		पूर्ण
		fnum = fc - 1;
		freq = cpr_get_opp_hz_क्रम_req(opp, drv->attached_cpu_dev);
		अगर (!freq) अणु
			dev_pm_opp_put(opp);
			वापस -EINVAL;
		पूर्ण
		cdata[level - 1].fuse_corner = fnum;
		cdata[level - 1].freq = freq;

		fuse = &drv->fuse_corners[fnum];
		dev_dbg(drv->dev, "freq: %lu level: %u fuse level: %u\n",
			freq, dev_pm_opp_get_level(opp) - 1, fnum);
		अगर (freq > fuse->max_freq)
			fuse->max_freq = freq;
		dev_pm_opp_put(opp);
	पूर्ण

	/*
	 * Get the quotient adjusपंचांगent scaling factor, according to:
	 *
	 * scaling = min(1000 * (QUOT(corner_N) - QUOT(corner_N-1))
	 *		/ (freq(corner_N) - freq(corner_N-1)), max_factor)
	 *
	 * QUOT(corner_N):	quotient पढ़ो from fuse क्रम fuse corner N
	 * QUOT(corner_N-1):	quotient पढ़ो from fuse क्रम fuse corner (N - 1)
	 * freq(corner_N):	max frequency in MHz supported by fuse corner N
	 * freq(corner_N-1):	max frequency in MHz supported by fuse corner
	 *			 (N - 1)
	 *
	 * Then walk through the corners mapped to each fuse corner
	 * and calculate the quotient adjusपंचांगent क्रम each one using the
	 * following क्रमmula:
	 *
	 * quot_adjust = (freq_max - freq_corner) * scaling / 1000
	 *
	 * freq_max: max frequency in MHz supported by the fuse corner
	 * freq_corner: frequency in MHz corresponding to the corner
	 * scaling: calculated from above equation
	 *
	 *
	 *     +                           +
	 *     |                         v |
	 *   q |           f c           o |           f c
	 *   u |         c               l |         c
	 *   o |       f                 t |       f
	 *   t |     c                   a |     c
	 *     | c f                     g | c f
	 *     |                         e |
	 *     +---------------            +----------------
	 *       0 1 2 3 4 5 6               0 1 2 3 4 5 6
	 *          corner                      corner
	 *
	 *    c = corner
	 *    f = fuse corner
	 *
	 */
	क्रम (apply_scaling = false, i = 0; corner <= end; corner++, i++) अणु
		fnum = cdata[i].fuse_corner;
		fdata = &desc->cpr_fuses.fuse_corner_data[fnum];
		quot_offset = fuses[fnum].quotient_offset;
		fuse = &drv->fuse_corners[fnum];
		अगर (fnum)
			prev_fuse = &drv->fuse_corners[fnum - 1];
		अन्यथा
			prev_fuse = शून्य;

		corner->fuse_corner = fuse;
		corner->freq = cdata[i].freq;
		corner->uV = fuse->uV;

		अगर (prev_fuse && cdata[i - 1].freq == prev_fuse->max_freq) अणु
			scaling = cpr_calculate_scaling(quot_offset, drv,
							fdata, corner);
			अगर (scaling < 0)
				वापस scaling;

			apply_scaling = true;
		पूर्ण अन्यथा अगर (corner->freq == fuse->max_freq) अणु
			/* This is a fuse corner; करोn't scale anything */
			apply_scaling = false;
		पूर्ण

		अगर (apply_scaling) अणु
			freq_dअगरf = fuse->max_freq - corner->freq;
			freq_dअगरf_mhz = freq_dअगरf / 1000000;
			corner->quot_adjust = scaling * freq_dअगरf_mhz / 1000;

			corner->uV = cpr_पूर्णांकerpolate(corner, step_volt, fdata);
		पूर्ण

		corner->max_uV = fuse->max_uV;
		corner->min_uV = fuse->min_uV;
		corner->uV = clamp(corner->uV, corner->min_uV, corner->max_uV);
		corner->last_uV = corner->uV;

		/* Reduce the उच्चमानing voltage अगर needed */
		अगर (desc->reduce_to_corner_uV && corner->uV < corner->max_uV)
			corner->max_uV = corner->uV;
		अन्यथा अगर (desc->reduce_to_fuse_uV && fuse->uV < corner->max_uV)
			corner->max_uV = max(corner->min_uV, fuse->uV);

		dev_dbg(drv->dev, "corner %d: [%d %d %d] quot %d\n", i,
			corner->min_uV, corner->uV, corner->max_uV,
			fuse->quot - corner->quot_adjust);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cpr_fuse *cpr_get_fuses(काष्ठा cpr_drv *drv)
अणु
	स्थिर काष्ठा cpr_desc *desc = drv->desc;
	काष्ठा cpr_fuse *fuses;
	पूर्णांक i;

	fuses = devm_kसुस्मृति(drv->dev, desc->num_fuse_corners,
			     माप(काष्ठा cpr_fuse),
			     GFP_KERNEL);
	अगर (!fuses)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < desc->num_fuse_corners; i++) अणु
		अक्षर tbuf[32];

		snम_लिखो(tbuf, 32, "cpr_ring_osc%d", i + 1);
		fuses[i].ring_osc = devm_kstrdup(drv->dev, tbuf, GFP_KERNEL);
		अगर (!fuses[i].ring_osc)
			वापस ERR_PTR(-ENOMEM);

		snम_लिखो(tbuf, 32, "cpr_init_voltage%d", i + 1);
		fuses[i].init_voltage = devm_kstrdup(drv->dev, tbuf,
						     GFP_KERNEL);
		अगर (!fuses[i].init_voltage)
			वापस ERR_PTR(-ENOMEM);

		snम_लिखो(tbuf, 32, "cpr_quotient%d", i + 1);
		fuses[i].quotient = devm_kstrdup(drv->dev, tbuf, GFP_KERNEL);
		अगर (!fuses[i].quotient)
			वापस ERR_PTR(-ENOMEM);

		snम_लिखो(tbuf, 32, "cpr_quotient_offset%d", i + 1);
		fuses[i].quotient_offset = devm_kstrdup(drv->dev, tbuf,
							GFP_KERNEL);
		अगर (!fuses[i].quotient_offset)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस fuses;
पूर्ण

अटल व्योम cpr_set_loop_allowed(काष्ठा cpr_drv *drv)
अणु
	drv->loop_disabled = false;
पूर्ण

अटल पूर्णांक cpr_init_parameters(काष्ठा cpr_drv *drv)
अणु
	स्थिर काष्ठा cpr_desc *desc = drv->desc;
	काष्ठा clk *clk;

	clk = clk_get(drv->dev, "ref");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	drv->ref_clk_khz = clk_get_rate(clk) / 1000;
	clk_put(clk);

	अगर (desc->समयr_cons_up > RBIF_TIMER_ADJ_CONS_UP_MASK ||
	    desc->समयr_cons_करोwn > RBIF_TIMER_ADJ_CONS_DOWN_MASK ||
	    desc->up_threshold > RBCPR_CTL_UP_THRESHOLD_MASK ||
	    desc->करोwn_threshold > RBCPR_CTL_DN_THRESHOLD_MASK ||
	    desc->idle_घड़ीs > RBCPR_STEP_QUOT_IDLE_CLK_MASK ||
	    desc->clamp_समयr_पूर्णांकerval > RBIF_TIMER_ADJ_CLAMP_INT_MASK)
		वापस -EINVAL;

	dev_dbg(drv->dev, "up threshold = %u, down threshold = %u\n",
		desc->up_threshold, desc->करोwn_threshold);

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_find_initial_corner(काष्ठा cpr_drv *drv)
अणु
	अचिन्हित दीर्घ rate;
	स्थिर काष्ठा corner *end;
	काष्ठा corner *iter;
	अचिन्हित पूर्णांक i = 0;

	अगर (!drv->cpu_clk) अणु
		dev_err(drv->dev, "cannot get rate from NULL clk\n");
		वापस -EINVAL;
	पूर्ण

	end = &drv->corners[drv->num_corners - 1];
	rate = clk_get_rate(drv->cpu_clk);

	/*
	 * Some bootloaders set a CPU घड़ी frequency that is not defined
	 * in the OPP table. When running at an unlisted frequency,
	 * cpufreq_online() will change to the OPP which has the lowest
	 * frequency, at or above the unlisted frequency.
	 * Since cpufreq_online() always "rounds up" in the हाल of an
	 * unlisted frequency, this function always "rounds down" in हाल
	 * of an unlisted frequency. That way, when cpufreq_online()
	 * triggers the first ever call to cpr_set_perक्रमmance_state(),
	 * it will correctly determine the direction as UP.
	 */
	क्रम (iter = drv->corners; iter <= end; iter++) अणु
		अगर (iter->freq > rate)
			अवरोध;
		i++;
		अगर (iter->freq == rate) अणु
			drv->corner = iter;
			अवरोध;
		पूर्ण
		अगर (iter->freq < rate)
			drv->corner = iter;
	पूर्ण

	अगर (!drv->corner) अणु
		dev_err(drv->dev, "boot up corner not found\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(drv->dev, "boot up perf state: %u\n", i);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cpr_desc qcs404_cpr_desc = अणु
	.num_fuse_corners = 3,
	.min_dअगरf_quot = CPR_FUSE_MIN_QUOT_DIFF,
	.step_quot = (पूर्णांक [])अणु 25, 25, 25, पूर्ण,
	.समयr_delay_us = 5000,
	.समयr_cons_up = 0,
	.समयr_cons_करोwn = 2,
	.up_threshold = 1,
	.करोwn_threshold = 3,
	.idle_घड़ीs = 15,
	.gcnt_us = 1,
	.vdd_apc_step_up_limit = 1,
	.vdd_apc_step_करोwn_limit = 1,
	.cpr_fuses = अणु
		.init_voltage_step = 8000,
		.init_voltage_width = 6,
		.fuse_corner_data = (काष्ठा fuse_corner_data[])अणु
			/* fuse corner 0 */
			अणु
				.ref_uV = 1224000,
				.max_uV = 1224000,
				.min_uV = 1048000,
				.max_volt_scale = 0,
				.max_quot_scale = 0,
				.quot_offset = 0,
				.quot_scale = 1,
				.quot_adjust = 0,
				.quot_offset_scale = 5,
				.quot_offset_adjust = 0,
			पूर्ण,
			/* fuse corner 1 */
			अणु
				.ref_uV = 1288000,
				.max_uV = 1288000,
				.min_uV = 1048000,
				.max_volt_scale = 2000,
				.max_quot_scale = 1400,
				.quot_offset = 0,
				.quot_scale = 1,
				.quot_adjust = -20,
				.quot_offset_scale = 5,
				.quot_offset_adjust = 0,
			पूर्ण,
			/* fuse corner 2 */
			अणु
				.ref_uV = 1352000,
				.max_uV = 1384000,
				.min_uV = 1088000,
				.max_volt_scale = 2000,
				.max_quot_scale = 1400,
				.quot_offset = 0,
				.quot_scale = 1,
				.quot_adjust = 0,
				.quot_offset_scale = 5,
				.quot_offset_adjust = 0,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acc_desc qcs404_acc_desc = अणु
	.settings = (काष्ठा reg_sequence[])अणु
		अणु 0xb120, 0x1041040 पूर्ण,
		अणु 0xb124, 0x41 पूर्ण,
		अणु 0xb120, 0x0 पूर्ण,
		अणु 0xb124, 0x0 पूर्ण,
		अणु 0xb120, 0x0 पूर्ण,
		अणु 0xb124, 0x0 पूर्ण,
	पूर्ण,
	.config = (काष्ठा reg_sequence[])अणु
		अणु 0xb138, 0xff पूर्ण,
		अणु 0xb130, 0x5555 पूर्ण,
	पूर्ण,
	.num_regs_per_fuse = 2,
पूर्ण;

अटल स्थिर काष्ठा cpr_acc_desc qcs404_cpr_acc_desc = अणु
	.cpr_desc = &qcs404_cpr_desc,
	.acc_desc = &qcs404_acc_desc,
पूर्ण;

अटल अचिन्हित पूर्णांक cpr_get_perक्रमmance_state(काष्ठा generic_pm_करोमुख्य *genpd,
					      काष्ठा dev_pm_opp *opp)
अणु
	वापस dev_pm_opp_get_level(opp);
पूर्ण

अटल पूर्णांक cpr_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा cpr_drv *drv = container_of(करोमुख्य, काष्ठा cpr_drv, pd);

	वापस cpr_disable(drv);
पूर्ण

अटल पूर्णांक cpr_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा cpr_drv *drv = container_of(करोमुख्य, काष्ठा cpr_drv, pd);

	वापस cpr_enable(drv);
पूर्ण

अटल पूर्णांक cpr_pd_attach_dev(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
			     काष्ठा device *dev)
अणु
	काष्ठा cpr_drv *drv = container_of(करोमुख्य, काष्ठा cpr_drv, pd);
	स्थिर काष्ठा acc_desc *acc_desc = drv->acc_desc;
	पूर्णांक ret = 0;

	mutex_lock(&drv->lock);

	dev_dbg(drv->dev, "attach callback for: %s\n", dev_name(dev));

	/*
	 * This driver only supports scaling voltage क्रम a CPU cluster
	 * where all CPUs in the cluster share a single regulator.
	 * Thereक्रमe, save the काष्ठा device poपूर्णांकer only क्रम the first
	 * CPU device that माला_लो attached. There is no need to करो any
	 * additional initialization when further CPUs get attached.
	 */
	अगर (drv->attached_cpu_dev)
		जाओ unlock;

	/*
	 * cpr_scale_voltage() requires the direction (अगर we are changing
	 * to a higher or lower OPP). The first समय
	 * cpr_set_perक्रमmance_state() is called, there is no previous
	 * perक्रमmance state defined. Thereक्रमe, we call
	 * cpr_find_initial_corner() that माला_लो the CPU घड़ी frequency
	 * set by the bootloader, so that we can determine the direction
	 * the first समय cpr_set_perक्रमmance_state() is called.
	 */
	drv->cpu_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(drv->cpu_clk)) अणु
		ret = PTR_ERR(drv->cpu_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(drv->dev, "could not get cpu clk: %d\n", ret);
		जाओ unlock;
	पूर्ण
	drv->attached_cpu_dev = dev;

	dev_dbg(drv->dev, "using cpu clk from: %s\n",
		dev_name(drv->attached_cpu_dev));

	/*
	 * Everything related to (भव) corners has to be initialized
	 * here, when attaching to the घातer करोमुख्य, since we need to know
	 * the maximum frequency क्रम each fuse corner, and this is only
	 * available after the cpufreq driver has attached to us.
	 * The reason क्रम this is that we need to know the highest
	 * frequency associated with each fuse corner.
	 */
	ret = dev_pm_opp_get_opp_count(&drv->pd.dev);
	अगर (ret < 0) अणु
		dev_err(drv->dev, "could not get OPP count\n");
		जाओ unlock;
	पूर्ण
	drv->num_corners = ret;

	अगर (drv->num_corners < 2) अणु
		dev_err(drv->dev, "need at least 2 OPPs to use CPR\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	drv->corners = devm_kसुस्मृति(drv->dev, drv->num_corners,
				    माप(*drv->corners),
				    GFP_KERNEL);
	अगर (!drv->corners) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	ret = cpr_corner_init(drv);
	अगर (ret)
		जाओ unlock;

	cpr_set_loop_allowed(drv);

	ret = cpr_init_parameters(drv);
	अगर (ret)
		जाओ unlock;

	/* Configure CPR HW but keep it disabled */
	ret = cpr_config(drv);
	अगर (ret)
		जाओ unlock;

	ret = cpr_find_initial_corner(drv);
	अगर (ret)
		जाओ unlock;

	अगर (acc_desc->config)
		regmap_multi_reg_ग_लिखो(drv->tcsr, acc_desc->config,
				       acc_desc->num_regs_per_fuse);

	/* Enable ACC अगर required */
	अगर (acc_desc->enable_mask)
		regmap_update_bits(drv->tcsr, acc_desc->enable_reg,
				   acc_desc->enable_mask,
				   acc_desc->enable_mask);

	dev_info(drv->dev, "driver initialized with %u OPPs\n",
		 drv->num_corners);

unlock:
	mutex_unlock(&drv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cpr_debug_info_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	u32 gcnt, ro_sel, ctl, irq_status, reg, error_steps;
	u32 step_dn, step_up, error, error_lt0, busy;
	काष्ठा cpr_drv *drv = s->निजी;
	काष्ठा fuse_corner *fuse_corner;
	काष्ठा corner *corner;

	corner = drv->corner;
	fuse_corner = corner->fuse_corner;

	seq_म_लिखो(s, "corner, current_volt = %d uV\n",
		       corner->last_uV);

	ro_sel = fuse_corner->ring_osc_idx;
	gcnt = cpr_पढ़ो(drv, REG_RBCPR_GCNT_TARGET(ro_sel));
	seq_म_लिखो(s, "rbcpr_gcnt_target (%u) = %#02X\n", ro_sel, gcnt);

	ctl = cpr_पढ़ो(drv, REG_RBCPR_CTL);
	seq_म_लिखो(s, "rbcpr_ctl = %#02X\n", ctl);

	irq_status = cpr_पढ़ो(drv, REG_RBIF_IRQ_STATUS);
	seq_म_लिखो(s, "rbcpr_irq_status = %#02X\n", irq_status);

	reg = cpr_पढ़ो(drv, REG_RBCPR_RESULT_0);
	seq_म_लिखो(s, "rbcpr_result_0 = %#02X\n", reg);

	step_dn = reg & 0x01;
	step_up = (reg >> RBCPR_RESULT0_STEP_UP_SHIFT) & 0x01;
	seq_म_लिखो(s, "  [step_dn = %u", step_dn);

	seq_म_लिखो(s, ", step_up = %u", step_up);

	error_steps = (reg >> RBCPR_RESULT0_ERROR_STEPS_SHIFT)
				& RBCPR_RESULT0_ERROR_STEPS_MASK;
	seq_म_लिखो(s, ", error_steps = %u", error_steps);

	error = (reg >> RBCPR_RESULT0_ERROR_SHIFT) & RBCPR_RESULT0_ERROR_MASK;
	seq_म_लिखो(s, ", error = %u", error);

	error_lt0 = (reg >> RBCPR_RESULT0_ERROR_LT0_SHIFT) & 0x01;
	seq_म_लिखो(s, ", error_lt_0 = %u", error_lt0);

	busy = (reg >> RBCPR_RESULT0_BUSY_SHIFT) & 0x01;
	seq_म_लिखो(s, ", busy = %u]\n", busy);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cpr_debug_info);

अटल व्योम cpr_debugfs_init(काष्ठा cpr_drv *drv)
अणु
	drv->debugfs = debugfs_create_dir("qcom_cpr", शून्य);

	debugfs_create_file("debug_info", 0444, drv->debugfs,
			    drv, &cpr_debug_info_fops);
पूर्ण

अटल पूर्णांक cpr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cpr_drv *drv;
	पूर्णांक irq, ret;
	स्थिर काष्ठा cpr_acc_desc *data;
	काष्ठा device_node *np;
	u32 cpr_rev = FUSE_REVISION_UNKNOWN;

	data = of_device_get_match_data(dev);
	अगर (!data || !data->cpr_desc || !data->acc_desc)
		वापस -EINVAL;

	drv = devm_kzalloc(dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;
	drv->dev = dev;
	drv->desc = data->cpr_desc;
	drv->acc_desc = data->acc_desc;

	drv->fuse_corners = devm_kसुस्मृति(dev, drv->desc->num_fuse_corners,
					 माप(*drv->fuse_corners),
					 GFP_KERNEL);
	अगर (!drv->fuse_corners)
		वापस -ENOMEM;

	np = of_parse_phandle(dev->of_node, "acc-syscon", 0);
	अगर (!np)
		वापस -ENODEV;

	drv->tcsr = syscon_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(drv->tcsr))
		वापस PTR_ERR(drv->tcsr);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	drv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(drv->base))
		वापस PTR_ERR(drv->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	drv->vdd_apc = devm_regulator_get(dev, "vdd-apc");
	अगर (IS_ERR(drv->vdd_apc))
		वापस PTR_ERR(drv->vdd_apc);

	/*
	 * Initialize fuse corners, since it simply depends
	 * on data in efuses.
	 * Everything related to (भव) corners has to be
	 * initialized after attaching to the घातer करोमुख्य,
	 * since it depends on the CPU's OPP table.
	 */
	ret = cpr_पढ़ो_efuse(dev, "cpr_fuse_revision", &cpr_rev);
	अगर (ret)
		वापस ret;

	drv->cpr_fuses = cpr_get_fuses(drv);
	अगर (IS_ERR(drv->cpr_fuses))
		वापस PTR_ERR(drv->cpr_fuses);

	ret = cpr_populate_ring_osc_idx(drv);
	अगर (ret)
		वापस ret;

	ret = cpr_fuse_corner_init(drv);
	अगर (ret)
		वापस ret;

	mutex_init(&drv->lock);

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					cpr_irq_handler,
					IRQF_ONESHOT | IRQF_TRIGGER_RISING,
					"cpr", drv);
	अगर (ret)
		वापस ret;

	drv->pd.name = devm_kstrdup_स्थिर(dev, dev->of_node->full_name,
					  GFP_KERNEL);
	अगर (!drv->pd.name)
		वापस -EINVAL;

	drv->pd.घातer_off = cpr_घातer_off;
	drv->pd.घातer_on = cpr_घातer_on;
	drv->pd.set_perक्रमmance_state = cpr_set_perक्रमmance_state;
	drv->pd.opp_to_perक्रमmance_state = cpr_get_perक्रमmance_state;
	drv->pd.attach_dev = cpr_pd_attach_dev;

	ret = pm_genpd_init(&drv->pd, शून्य, true);
	अगर (ret)
		वापस ret;

	ret = of_genpd_add_provider_simple(dev->of_node, &drv->pd);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, drv);
	cpr_debugfs_init(drv);

	वापस 0;
पूर्ण

अटल पूर्णांक cpr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpr_drv *drv = platक्रमm_get_drvdata(pdev);

	अगर (cpr_is_allowed(drv)) अणु
		cpr_ctl_disable(drv);
		cpr_irq_set(drv, 0);
	पूर्ण

	of_genpd_del_provider(pdev->dev.of_node);
	pm_genpd_हटाओ(&drv->pd);

	debugfs_हटाओ_recursive(drv->debugfs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cpr_match_table[] = अणु
	अणु .compatible = "qcom,qcs404-cpr", .data = &qcs404_cpr_acc_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cpr_match_table);

अटल काष्ठा platक्रमm_driver cpr_driver = अणु
	.probe		= cpr_probe,
	.हटाओ		= cpr_हटाओ,
	.driver		= अणु
		.name	= "qcom-cpr",
		.of_match_table = cpr_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cpr_driver);

MODULE_DESCRIPTION("Core Power Reduction (CPR) driver");
MODULE_LICENSE("GPL v2");
