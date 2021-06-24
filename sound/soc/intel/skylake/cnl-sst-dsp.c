<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cnl-sst-dsp.c - CNL SST library generic function
 *
 * Copyright (C) 2016-17, Intel Corporation.
 * Author: Guneshwor Singh <guneshwor.o.singh@पूर्णांकel.com>
 *
 * Modअगरied from:
 *	SKL SST library generic function
 *	Copyright (C) 2014-15, Intel Corporation.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/device.h>
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-ipc.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "cnl-sst-dsp.h"

/* various समयout values */
#घोषणा CNL_DSP_PU_TO		50
#घोषणा CNL_DSP_PD_TO		50
#घोषणा CNL_DSP_RESET_TO	50

अटल पूर्णांक
cnl_dsp_core_set_reset_state(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx,
			CNL_ADSP_REG_ADSPCS, CNL_ADSPCS_CRST(core_mask),
			CNL_ADSPCS_CRST(core_mask));

	/* poll with समयout to check अगर operation successful */
	वापस sst_dsp_रेजिस्टर_poll(ctx,
			CNL_ADSP_REG_ADSPCS,
			CNL_ADSPCS_CRST(core_mask),
			CNL_ADSPCS_CRST(core_mask),
			CNL_DSP_RESET_TO,
			"Set reset");
पूर्ण

अटल पूर्णांक
cnl_dsp_core_unset_reset_state(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
					CNL_ADSPCS_CRST(core_mask), 0);

	/* poll with समयout to check अगर operation successful */
	वापस sst_dsp_रेजिस्टर_poll(ctx,
			CNL_ADSP_REG_ADSPCS,
			CNL_ADSPCS_CRST(core_mask),
			0,
			CNL_DSP_RESET_TO,
			"Unset reset");
पूर्ण

अटल bool is_cnl_dsp_core_enable(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक val;
	bool is_enable;

	val = sst_dsp_shim_पढ़ो_unlocked(ctx, CNL_ADSP_REG_ADSPCS);

	is_enable = (val & CNL_ADSPCS_CPA(core_mask)) &&
			(val & CNL_ADSPCS_SPA(core_mask)) &&
			!(val & CNL_ADSPCS_CRST(core_mask)) &&
			!(val & CNL_ADSPCS_CSTALL(core_mask));

	dev_dbg(ctx->dev, "DSP core(s) enabled? %d: core_mask %#x\n",
		is_enable, core_mask);

	वापस is_enable;
पूर्ण

अटल पूर्णांक cnl_dsp_reset_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* stall core */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
			CNL_ADSPCS_CSTALL(core_mask),
			CNL_ADSPCS_CSTALL(core_mask));

	/* set reset state */
	वापस cnl_dsp_core_set_reset_state(ctx, core_mask);
पूर्ण

अटल पूर्णांक cnl_dsp_start_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* unset reset state */
	ret = cnl_dsp_core_unset_reset_state(ctx, core_mask);
	अगर (ret < 0)
		वापस ret;

	/* run core */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
				CNL_ADSPCS_CSTALL(core_mask), 0);

	अगर (!is_cnl_dsp_core_enable(ctx, core_mask)) अणु
		cnl_dsp_reset_core(ctx, core_mask);
		dev_err(ctx->dev, "DSP core mask %#x enable failed\n",
			core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cnl_dsp_core_घातer_up(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
					  CNL_ADSPCS_SPA(core_mask),
					  CNL_ADSPCS_SPA(core_mask));

	/* poll with समयout to check अगर operation successful */
	वापस sst_dsp_रेजिस्टर_poll(ctx, CNL_ADSP_REG_ADSPCS,
				    CNL_ADSPCS_CPA(core_mask),
				    CNL_ADSPCS_CPA(core_mask),
				    CNL_DSP_PU_TO,
				    "Power up");
पूर्ण

अटल पूर्णांक cnl_dsp_core_घातer_करोwn(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPCS,
					CNL_ADSPCS_SPA(core_mask), 0);

	/* poll with समयout to check अगर operation successful */
	वापस sst_dsp_रेजिस्टर_poll(ctx,
			CNL_ADSP_REG_ADSPCS,
			CNL_ADSPCS_CPA(core_mask),
			0,
			CNL_DSP_PD_TO,
			"Power down");
पूर्ण

पूर्णांक cnl_dsp_enable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* घातer up */
	ret = cnl_dsp_core_घातer_up(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_dbg(ctx->dev, "DSP core mask %#x power up failed",
			core_mask);
		वापस ret;
	पूर्ण

	वापस cnl_dsp_start_core(ctx, core_mask);
पूर्ण

पूर्णांक cnl_dsp_disable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	ret = cnl_dsp_reset_core(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "DSP core mask %#x reset failed\n",
			core_mask);
		वापस ret;
	पूर्ण

	/* घातer करोwn core*/
	ret = cnl_dsp_core_घातer_करोwn(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "DSP core mask %#x power down failed\n",
			core_mask);
		वापस ret;
	पूर्ण

	अगर (is_cnl_dsp_core_enable(ctx, core_mask)) अणु
		dev_err(ctx->dev, "DSP core mask %#x disable failed\n",
			core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

irqवापस_t cnl_dsp_sst_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sst_dsp *ctx = dev_id;
	u32 val;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&ctx->spinlock);

	val = sst_dsp_shim_पढ़ो_unlocked(ctx, CNL_ADSP_REG_ADSPIS);
	ctx->पूर्णांकr_status = val;

	अगर (val == 0xffffffff) अणु
		spin_unlock(&ctx->spinlock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (val & CNL_ADSPIS_IPC) अणु
		cnl_ipc_पूर्णांक_disable(ctx);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	spin_unlock(&ctx->spinlock);

	वापस ret;
पूर्ण

व्योम cnl_dsp_मुक्त(काष्ठा sst_dsp *dsp)
अणु
	cnl_ipc_पूर्णांक_disable(dsp);

	मुक्त_irq(dsp->irq, dsp);
	cnl_ipc_op_पूर्णांक_disable(dsp);
	cnl_dsp_disable_core(dsp, SKL_DSP_CORE0_MASK);
पूर्ण
EXPORT_SYMBOL_GPL(cnl_dsp_मुक्त);

व्योम cnl_ipc_पूर्णांक_enable(काष्ठा sst_dsp *ctx)
अणु
	sst_dsp_shim_update_bits(ctx, CNL_ADSP_REG_ADSPIC,
				 CNL_ADSPIC_IPC, CNL_ADSPIC_IPC);
पूर्ण

व्योम cnl_ipc_पूर्णांक_disable(काष्ठा sst_dsp *ctx)
अणु
	sst_dsp_shim_update_bits_unlocked(ctx, CNL_ADSP_REG_ADSPIC,
					  CNL_ADSPIC_IPC, 0);
पूर्ण

व्योम cnl_ipc_op_पूर्णांक_enable(काष्ठा sst_dsp *ctx)
अणु
	/* enable IPC DONE पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ctx, CNL_ADSP_REG_HIPCCTL,
				 CNL_ADSP_REG_HIPCCTL_DONE,
				 CNL_ADSP_REG_HIPCCTL_DONE);

	/* enable IPC BUSY पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ctx, CNL_ADSP_REG_HIPCCTL,
				 CNL_ADSP_REG_HIPCCTL_BUSY,
				 CNL_ADSP_REG_HIPCCTL_BUSY);
पूर्ण

व्योम cnl_ipc_op_पूर्णांक_disable(काष्ठा sst_dsp *ctx)
अणु
	/* disable IPC DONE पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ctx, CNL_ADSP_REG_HIPCCTL,
				 CNL_ADSP_REG_HIPCCTL_DONE, 0);

	/* disable IPC BUSY पूर्णांकerrupt */
	sst_dsp_shim_update_bits(ctx, CNL_ADSP_REG_HIPCCTL,
				 CNL_ADSP_REG_HIPCCTL_BUSY, 0);
पूर्ण

bool cnl_ipc_पूर्णांक_status(काष्ठा sst_dsp *ctx)
अणु
	वापस sst_dsp_shim_पढ़ो_unlocked(ctx, CNL_ADSP_REG_ADSPIS) &
							CNL_ADSPIS_IPC;
पूर्ण

व्योम cnl_ipc_मुक्त(काष्ठा sst_generic_ipc *ipc)
अणु
	cnl_ipc_op_पूर्णांक_disable(ipc->dsp);
	sst_ipc_fini(ipc);
पूर्ण
