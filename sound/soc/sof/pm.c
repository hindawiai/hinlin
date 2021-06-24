<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश "ops.h"
#समावेश "sof-priv.h"
#समावेश "sof-audio.h"

/*
 * Helper function to determine the target DSP state during
 * प्रणाली suspend. This function only cares about the device
 * D-states. Platक्रमm-specअगरic substates, अगर any, should be
 * handled by the platक्रमm-specअगरic parts.
 */
अटल u32 snd_sof_dsp_घातer_target(काष्ठा snd_sof_dev *sdev)
अणु
	u32 target_dsp_state;

	चयन (sdev->प्रणाली_suspend_target) अणु
	हाल SOF_SUSPEND_S3:
		/* DSP should be in D3 अगर the प्रणाली is suspending to S3 */
		target_dsp_state = SOF_DSP_PM_D3;
		अवरोध;
	हाल SOF_SUSPEND_S0IX:
		/*
		 * Currently, the only criterion क्रम retaining the DSP in D0
		 * is that there are streams that ignored the suspend trigger.
		 * Additional criteria such Soundwire घड़ी-stop mode and
		 * device suspend latency considerations will be added later.
		 */
		अगर (snd_sof_stream_suspend_ignored(sdev))
			target_dsp_state = SOF_DSP_PM_D0;
		अन्यथा
			target_dsp_state = SOF_DSP_PM_D3;
		अवरोध;
	शेष:
		/* This हाल would be during runसमय suspend */
		target_dsp_state = SOF_DSP_PM_D3;
		अवरोध;
	पूर्ण

	वापस target_dsp_state;
पूर्ण

अटल पूर्णांक sof_send_pm_ctx_ipc(काष्ठा snd_sof_dev *sdev, पूर्णांक cmd)
अणु
	काष्ठा sof_ipc_pm_ctx pm_ctx;
	काष्ठा sof_ipc_reply reply;

	स_रखो(&pm_ctx, 0, माप(pm_ctx));

	/* configure ctx save ipc message */
	pm_ctx.hdr.size = माप(pm_ctx);
	pm_ctx.hdr.cmd = SOF_IPC_GLB_PM_MSG | cmd;

	/* send ctx save ipc to dsp */
	वापस sof_ipc_tx_message(sdev->ipc, pm_ctx.hdr.cmd, &pm_ctx,
				 माप(pm_ctx), &reply, माप(reply));
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_ENABLE_DEBUGFS_CACHE)
अटल व्योम sof_cache_debugfs(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_dfsentry *dfse;

	list_क्रम_each_entry(dfse, &sdev->dfsentry_list, list) अणु

		/* nothing to करो अगर debugfs buffer is not IO mem */
		अगर (dfse->type == SOF_DFSENTRY_TYPE_BUF)
			जारी;

		/* cache memory that is only accessible in D0 */
		अगर (dfse->access_type == SOF_DEBUGFS_ACCESS_D0_ONLY)
			स_नकल_fromio(dfse->cache_buf, dfse->io_mem,
				      dfse->size);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sof_resume(काष्ठा device *dev, bool runसमय_resume)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	u32 old_state = sdev->dsp_घातer_state.state;
	पूर्णांक ret;

	/* करो nothing अगर dsp resume callbacks are not set */
	अगर (!runसमय_resume && !sof_ops(sdev)->resume)
		वापस 0;

	अगर (runसमय_resume && !sof_ops(sdev)->runसमय_resume)
		वापस 0;

	/* DSP was never successfully started, nothing to resume */
	अगर (sdev->first_boot)
		वापस 0;

	/*
	 * अगर the runसमय_resume flag is set, call the runसमय_resume routine
	 * or अन्यथा call the प्रणाली resume routine
	 */
	अगर (runसमय_resume)
		ret = snd_sof_dsp_runसमय_resume(sdev);
	अन्यथा
		ret = snd_sof_dsp_resume(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to power up DSP after resume\n");
		वापस ret;
	पूर्ण

	/*
	 * Nothing further to be करोne क्रम platक्रमms that support the low घातer
	 * D0 substate.
	 */
	अगर (!runसमय_resume && sof_ops(sdev)->set_घातer_state &&
	    old_state == SOF_DSP_PM_D0)
		वापस 0;

	sdev->fw_state = SOF_FW_BOOT_PREPARE;

	/* load the firmware */
	ret = snd_sof_load_firmware(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to load DSP firmware after resume %d\n",
			ret);
		वापस ret;
	पूर्ण

	sdev->fw_state = SOF_FW_BOOT_IN_PROGRESS;

	/*
	 * Boot the firmware. The FW boot status will be modअगरied
	 * in snd_sof_run_firmware() depending on the outcome.
	 */
	ret = snd_sof_run_firmware(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to boot DSP firmware after resume %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* resume DMA trace, only need send ipc */
	ret = snd_sof_init_trace_ipc(sdev);
	अगर (ret < 0) अणु
		/* non fatal */
		dev_warn(sdev->dev,
			 "warning: failed to init trace after resume %d\n",
			 ret);
	पूर्ण

	/* restore pipelines */
	ret = sof_restore_pipelines(sdev->dev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to restore pipeline after resume %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* notअगरy DSP of प्रणाली resume */
	ret = sof_send_pm_ctx_ipc(sdev, SOF_IPC_PM_CTX_RESTORE);
	अगर (ret < 0)
		dev_err(sdev->dev,
			"error: ctx_restore ipc error during resume %d\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_suspend(काष्ठा device *dev, bool runसमय_suspend)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	u32 target_state = 0;
	पूर्णांक ret;

	/* करो nothing अगर dsp suspend callback is not set */
	अगर (!runसमय_suspend && !sof_ops(sdev)->suspend)
		वापस 0;

	अगर (runसमय_suspend && !sof_ops(sdev)->runसमय_suspend)
		वापस 0;

	अगर (sdev->fw_state != SOF_FW_BOOT_COMPLETE)
		जाओ suspend;

	/* set restore_stream क्रम all streams during प्रणाली suspend */
	अगर (!runसमय_suspend) अणु
		ret = sof_set_hw_params_upon_resume(sdev->dev);
		अगर (ret < 0) अणु
			dev_err(sdev->dev,
				"error: setting hw_params flag during suspend %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	target_state = snd_sof_dsp_घातer_target(sdev);

	/* Skip to platक्रमm-specअगरic suspend अगर DSP is entering D0 */
	अगर (target_state == SOF_DSP_PM_D0)
		जाओ suspend;

	/* release trace */
	snd_sof_release_trace(sdev);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_ENABLE_DEBUGFS_CACHE)
	/* cache debugfs contents during runसमय suspend */
	अगर (runसमय_suspend)
		sof_cache_debugfs(sdev);
#पूर्ण_अगर
	/* notअगरy DSP of upcoming घातer करोwn */
	ret = sof_send_pm_ctx_ipc(sdev, SOF_IPC_PM_CTX_SAVE);
	अगर (ret == -EBUSY || ret == -EAGAIN) अणु
		/*
		 * runसमय PM has logic to handle -EBUSY/-EAGAIN so
		 * pass these errors up
		 */
		dev_err(sdev->dev,
			"error: ctx_save ipc error during suspend %d\n",
			ret);
		वापस ret;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		/* FW in unexpected state, जारी to घातer करोwn */
		dev_warn(sdev->dev,
			 "ctx_save ipc error %d, proceeding with suspend\n",
			 ret);
	पूर्ण

suspend:

	/* वापस अगर the DSP was not probed successfully */
	अगर (sdev->fw_state == SOF_FW_BOOT_NOT_STARTED)
		वापस 0;

	/* platक्रमm-specअगरic suspend */
	अगर (runसमय_suspend)
		ret = snd_sof_dsp_runसमय_suspend(sdev);
	अन्यथा
		ret = snd_sof_dsp_suspend(sdev, target_state);
	अगर (ret < 0)
		dev_err(sdev->dev,
			"error: failed to power down DSP during suspend %d\n",
			ret);

	/* Do not reset FW state अगर DSP is in D0 */
	अगर (target_state == SOF_DSP_PM_D0)
		वापस ret;

	/* reset FW state */
	sdev->fw_state = SOF_FW_BOOT_NOT_STARTED;
	sdev->enabled_cores_mask = 0;

	वापस ret;
पूर्ण

पूर्णांक snd_sof_dsp_घातer_करोwn_notअगरy(काष्ठा snd_sof_dev *sdev)
अणु
	/* Notअगरy DSP of upcoming घातer करोwn */
	अगर (sof_ops(sdev)->हटाओ)
		वापस sof_send_pm_ctx_ipc(sdev, SOF_IPC_PM_CTX_SAVE);

	वापस 0;
पूर्ण

पूर्णांक snd_sof_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस sof_suspend(dev, true);
पूर्ण
EXPORT_SYMBOL(snd_sof_runसमय_suspend);

पूर्णांक snd_sof_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);

	वापस snd_sof_dsp_runसमय_idle(sdev);
पूर्ण
EXPORT_SYMBOL(snd_sof_runसमय_idle);

पूर्णांक snd_sof_runसमय_resume(काष्ठा device *dev)
अणु
	वापस sof_resume(dev, true);
पूर्ण
EXPORT_SYMBOL(snd_sof_runसमय_resume);

पूर्णांक snd_sof_resume(काष्ठा device *dev)
अणु
	वापस sof_resume(dev, false);
पूर्ण
EXPORT_SYMBOL(snd_sof_resume);

पूर्णांक snd_sof_suspend(काष्ठा device *dev)
अणु
	वापस sof_suspend(dev, false);
पूर्ण
EXPORT_SYMBOL(snd_sof_suspend);

पूर्णांक snd_sof_prepare(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	स्थिर काष्ठा sof_dev_desc *desc = sdev->pdata->desc;

	/* will suspend to S3 by शेष */
	sdev->प्रणाली_suspend_target = SOF_SUSPEND_S3;

	अगर (!desc->use_acpi_target_states)
		वापस 0;

#अगर defined(CONFIG_ACPI)
	अगर (acpi_target_प्रणाली_state() == ACPI_STATE_S0)
		sdev->प्रणाली_suspend_target = SOF_SUSPEND_S0IX;
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_prepare);

व्योम snd_sof_complete(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);

	sdev->प्रणाली_suspend_target = SOF_SUSPEND_NONE;
पूर्ण
EXPORT_SYMBOL(snd_sof_complete);
