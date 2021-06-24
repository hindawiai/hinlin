<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * skl-sst-dsp.c - SKL SST library generic function
 *
 * Copyright (C) 2014-15, Intel Corporation.
 * Author:Rafal Redzimski <rafal.f.redzimski@पूर्णांकel.com>
 *	Jeeja KP <jeeja.kp@पूर्णांकel.com>
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <sound/pcm.h>

#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-ipc.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "skl.h"

/* various समयout values */
#घोषणा SKL_DSP_PU_TO		50
#घोषणा SKL_DSP_PD_TO		50
#घोषणा SKL_DSP_RESET_TO	50

व्योम skl_dsp_set_state_locked(काष्ठा sst_dsp *ctx, पूर्णांक state)
अणु
	mutex_lock(&ctx->mutex);
	ctx->sst_state = state;
	mutex_unlock(&ctx->mutex);
पूर्ण

/*
 * Initialize core घातer state and usage count. To be called after
 * successful first boot. Hence core 0 will be running and other cores
 * will be reset
 */
व्योम skl_dsp_init_core_state(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	पूर्णांक i;

	skl->cores.state[SKL_DSP_CORE0_ID] = SKL_DSP_RUNNING;
	skl->cores.usage_count[SKL_DSP_CORE0_ID] = 1;

	क्रम (i = SKL_DSP_CORE0_ID + 1; i < skl->cores.count; i++) अणु
		skl->cores.state[i] = SKL_DSP_RESET;
		skl->cores.usage_count[i] = 0;
	पूर्ण
पूर्ण

/* Get the mask क्रम all enabled cores */
अचिन्हित पूर्णांक skl_dsp_get_enabled_cores(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	अचिन्हित पूर्णांक core_mask, en_cores_mask;
	u32 val;

	core_mask = SKL_DSP_CORES_MASK(skl->cores.count);

	val = sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_ADSPCS);

	/* Cores having CPA bit set */
	en_cores_mask = (val & SKL_ADSPCS_CPA_MASK(core_mask)) >>
			SKL_ADSPCS_CPA_SHIFT;

	/* And cores having CRST bit cleared */
	en_cores_mask &= (~val & SKL_ADSPCS_CRST_MASK(core_mask)) >>
			SKL_ADSPCS_CRST_SHIFT;

	/* And cores having CSTALL bit cleared */
	en_cores_mask &= (~val & SKL_ADSPCS_CSTALL_MASK(core_mask)) >>
			SKL_ADSPCS_CSTALL_SHIFT;
	en_cores_mask &= core_mask;

	dev_dbg(ctx->dev, "DSP enabled cores mask = %x\n", en_cores_mask);

	वापस en_cores_mask;
पूर्ण

अटल पूर्णांक
skl_dsp_core_set_reset_state(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx,
			SKL_ADSP_REG_ADSPCS, SKL_ADSPCS_CRST_MASK(core_mask),
			SKL_ADSPCS_CRST_MASK(core_mask));

	/* poll with समयout to check अगर operation successful */
	ret = sst_dsp_रेजिस्टर_poll(ctx,
			SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CRST_MASK(core_mask),
			SKL_ADSPCS_CRST_MASK(core_mask),
			SKL_DSP_RESET_TO,
			"Set reset");
	अगर ((sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_ADSPCS) &
				SKL_ADSPCS_CRST_MASK(core_mask)) !=
				SKL_ADSPCS_CRST_MASK(core_mask)) अणु
		dev_err(ctx->dev, "Set reset state failed: core_mask %x\n",
							core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक skl_dsp_core_unset_reset_state(
		काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	dev_dbg(ctx->dev, "In %s\n", __func__);

	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
				SKL_ADSPCS_CRST_MASK(core_mask), 0);

	/* poll with समयout to check अगर operation successful */
	ret = sst_dsp_रेजिस्टर_poll(ctx,
			SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CRST_MASK(core_mask),
			0,
			SKL_DSP_RESET_TO,
			"Unset reset");

	अगर ((sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_ADSPCS) &
				SKL_ADSPCS_CRST_MASK(core_mask)) != 0) अणु
		dev_err(ctx->dev, "Unset reset state failed: core_mask %x\n",
				core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool
is_skl_dsp_core_enable(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक val;
	bool is_enable;

	val = sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_ADSPCS);

	is_enable = ((val & SKL_ADSPCS_CPA_MASK(core_mask)) &&
			(val & SKL_ADSPCS_SPA_MASK(core_mask)) &&
			!(val & SKL_ADSPCS_CRST_MASK(core_mask)) &&
			!(val & SKL_ADSPCS_CSTALL_MASK(core_mask)));

	dev_dbg(ctx->dev, "DSP core(s) enabled? %d : core_mask %x\n",
						is_enable, core_mask);

	वापस is_enable;
पूर्ण

अटल पूर्णांक skl_dsp_reset_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* stall core */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CSTALL_MASK(core_mask),
			SKL_ADSPCS_CSTALL_MASK(core_mask));

	/* set reset state */
	वापस skl_dsp_core_set_reset_state(ctx, core_mask);
पूर्ण

पूर्णांक skl_dsp_start_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* unset reset state */
	ret = skl_dsp_core_unset_reset_state(ctx, core_mask);
	अगर (ret < 0)
		वापस ret;

	/* run core */
	dev_dbg(ctx->dev, "unstall/run core: core_mask = %x\n", core_mask);
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CSTALL_MASK(core_mask), 0);

	अगर (!is_skl_dsp_core_enable(ctx, core_mask)) अणु
		skl_dsp_reset_core(ctx, core_mask);
		dev_err(ctx->dev, "DSP start core failed: core_mask %x\n",
							core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक skl_dsp_core_घातer_up(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_SPA_MASK(core_mask),
			SKL_ADSPCS_SPA_MASK(core_mask));

	/* poll with समयout to check अगर operation successful */
	ret = sst_dsp_रेजिस्टर_poll(ctx,
			SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CPA_MASK(core_mask),
			SKL_ADSPCS_CPA_MASK(core_mask),
			SKL_DSP_PU_TO,
			"Power up");

	अगर ((sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_ADSPCS) &
			SKL_ADSPCS_CPA_MASK(core_mask)) !=
			SKL_ADSPCS_CPA_MASK(core_mask)) अणु
		dev_err(ctx->dev, "DSP core power up failed: core_mask %x\n",
				core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक skl_dsp_core_घातer_करोwn(काष्ठा sst_dsp  *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	/* update bits */
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPCS,
				SKL_ADSPCS_SPA_MASK(core_mask), 0);

	/* poll with समयout to check अगर operation successful */
	वापस sst_dsp_रेजिस्टर_poll(ctx,
			SKL_ADSP_REG_ADSPCS,
			SKL_ADSPCS_CPA_MASK(core_mask),
			0,
			SKL_DSP_PD_TO,
			"Power down");
पूर्ण

पूर्णांक skl_dsp_enable_core(काष्ठा sst_dsp  *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* घातer up */
	ret = skl_dsp_core_घातer_up(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "dsp core power up failed: core_mask %x\n",
							core_mask);
		वापस ret;
	पूर्ण

	वापस skl_dsp_start_core(ctx, core_mask);
पूर्ण

पूर्णांक skl_dsp_disable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	ret = skl_dsp_reset_core(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "dsp core reset failed: core_mask %x\n",
							core_mask);
		वापस ret;
	पूर्ण

	/* घातer करोwn core*/
	ret = skl_dsp_core_घातer_करोwn(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "dsp core power down fail mask %x: %d\n",
							core_mask, ret);
		वापस ret;
	पूर्ण

	अगर (is_skl_dsp_core_enable(ctx, core_mask)) अणु
		dev_err(ctx->dev, "dsp core disable fail mask %x: %d\n",
							core_mask, ret);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक skl_dsp_boot(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret;

	अगर (is_skl_dsp_core_enable(ctx, SKL_DSP_CORE0_MASK)) अणु
		ret = skl_dsp_reset_core(ctx, SKL_DSP_CORE0_MASK);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "dsp core0 reset fail: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = skl_dsp_start_core(ctx, SKL_DSP_CORE0_MASK);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "dsp core0 start fail: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "dsp core0 disable fail: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = skl_dsp_enable_core(ctx, SKL_DSP_CORE0_MASK);
	पूर्ण

	वापस ret;
पूर्ण

irqवापस_t skl_dsp_sst_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sst_dsp *ctx = dev_id;
	u32 val;
	irqवापस_t result = IRQ_NONE;

	spin_lock(&ctx->spinlock);

	val = sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_ADSPIS);
	ctx->पूर्णांकr_status = val;

	अगर (val == 0xffffffff) अणु
		spin_unlock(&ctx->spinlock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (val & SKL_ADSPIS_IPC) अणु
		skl_ipc_पूर्णांक_disable(ctx);
		result = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (val & SKL_ADSPIS_CL_DMA) अणु
		skl_cldma_पूर्णांक_disable(ctx);
		result = IRQ_WAKE_THREAD;
	पूर्ण

	spin_unlock(&ctx->spinlock);

	वापस result;
पूर्ण
/*
 * skl_dsp_get_core/skl_dsp_put_core will be called inside DAPM context
 * within the dapm mutex. Hence no separate lock is used.
 */
पूर्णांक skl_dsp_get_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	पूर्णांक ret = 0;

	अगर (core_id >= skl->cores.count) अणु
		dev_err(ctx->dev, "invalid core id: %d\n", core_id);
		वापस -EINVAL;
	पूर्ण

	skl->cores.usage_count[core_id]++;

	अगर (skl->cores.state[core_id] == SKL_DSP_RESET) अणु
		ret = ctx->fw_ops.set_state_D0(ctx, core_id);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "unable to get core%d\n", core_id);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	dev_dbg(ctx->dev, "core id %d state %d usage_count %d\n",
			core_id, skl->cores.state[core_id],
			skl->cores.usage_count[core_id]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_dsp_get_core);

पूर्णांक skl_dsp_put_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	पूर्णांक ret = 0;

	अगर (core_id >= skl->cores.count) अणु
		dev_err(ctx->dev, "invalid core id: %d\n", core_id);
		वापस -EINVAL;
	पूर्ण

	अगर ((--skl->cores.usage_count[core_id] == 0) &&
		(skl->cores.state[core_id] != SKL_DSP_RESET)) अणु
		ret = ctx->fw_ops.set_state_D3(ctx, core_id);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "unable to put core %d: %d\n",
					core_id, ret);
			skl->cores.usage_count[core_id]++;
		पूर्ण
	पूर्ण

	dev_dbg(ctx->dev, "core id %d state %d usage_count %d\n",
			core_id, skl->cores.state[core_id],
			skl->cores.usage_count[core_id]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(skl_dsp_put_core);

पूर्णांक skl_dsp_wake(काष्ठा sst_dsp *ctx)
अणु
	वापस skl_dsp_get_core(ctx, SKL_DSP_CORE0_ID);
पूर्ण
EXPORT_SYMBOL_GPL(skl_dsp_wake);

पूर्णांक skl_dsp_sleep(काष्ठा sst_dsp *ctx)
अणु
	वापस skl_dsp_put_core(ctx, SKL_DSP_CORE0_ID);
पूर्ण
EXPORT_SYMBOL_GPL(skl_dsp_sleep);

काष्ठा sst_dsp *skl_dsp_ctx_init(काष्ठा device *dev,
		काष्ठा sst_dsp_device *sst_dev, पूर्णांक irq)
अणु
	पूर्णांक ret;
	काष्ठा sst_dsp *sst;

	sst = devm_kzalloc(dev, माप(*sst), GFP_KERNEL);
	अगर (sst == शून्य)
		वापस शून्य;

	spin_lock_init(&sst->spinlock);
	mutex_init(&sst->mutex);
	sst->dev = dev;
	sst->sst_dev = sst_dev;
	sst->irq = irq;
	sst->ops = sst_dev->ops;
	sst->thपढ़ो_context = sst_dev->thपढ़ो_context;

	/* Initialise SST Audio DSP */
	अगर (sst->ops->init) अणु
		ret = sst->ops->init(sst);
		अगर (ret < 0)
			वापस शून्य;
	पूर्ण

	वापस sst;
पूर्ण

पूर्णांक skl_dsp_acquire_irq(काष्ठा sst_dsp *sst)
अणु
	काष्ठा sst_dsp_device *sst_dev = sst->sst_dev;
	पूर्णांक ret;

	/* Register the ISR */
	ret = request_thपढ़ोed_irq(sst->irq, sst->ops->irq_handler,
		sst_dev->thपढ़ो, IRQF_SHARED, "AudioDSP", sst);
	अगर (ret)
		dev_err(sst->dev, "unable to grab threaded IRQ %d, disabling device\n",
			       sst->irq);

	वापस ret;
पूर्ण

व्योम skl_dsp_मुक्त(काष्ठा sst_dsp *dsp)
अणु
	skl_ipc_पूर्णांक_disable(dsp);

	मुक्त_irq(dsp->irq, dsp);
	skl_ipc_op_पूर्णांक_disable(dsp);
	skl_dsp_disable_core(dsp, SKL_DSP_CORE0_MASK);
पूर्ण
EXPORT_SYMBOL_GPL(skl_dsp_मुक्त);

bool is_skl_dsp_running(काष्ठा sst_dsp *ctx)
अणु
	वापस (ctx->sst_state == SKL_DSP_RUNNING);
पूर्ण
EXPORT_SYMBOL_GPL(is_skl_dsp_running);
