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

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/sof.h>
#समावेश "sof-priv.h"
#समावेश "ops.h"
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
#समावेश "probe.h"
#पूर्ण_अगर

/* see SOF_DBG_ flags */
पूर्णांक sof_core_debug;
module_param_named(sof_debug, sof_core_debug, पूर्णांक, 0444);
MODULE_PARM_DESC(sof_debug, "SOF core debug options (0x0 all off)");

/* SOF शेषs अगर not provided by the platक्रमm in ms */
#घोषणा TIMEOUT_DEFAULT_IPC_MS  500
#घोषणा TIMEOUT_DEFAULT_BOOT_MS 2000

/*
 * FW Panic/fault handling.
 */

काष्ठा sof_panic_msg अणु
	u32 id;
	स्थिर अक्षर *msg;
पूर्ण;

/* standard FW panic types */
अटल स्थिर काष्ठा sof_panic_msg panic_msg[] = अणु
	अणुSOF_IPC_PANIC_MEM, "out of memory"पूर्ण,
	अणुSOF_IPC_PANIC_WORK, "work subsystem init failed"पूर्ण,
	अणुSOF_IPC_PANIC_IPC, "IPC subsystem init failed"पूर्ण,
	अणुSOF_IPC_PANIC_ARCH, "arch init failed"पूर्ण,
	अणुSOF_IPC_PANIC_PLATFORM, "platform init failed"पूर्ण,
	अणुSOF_IPC_PANIC_TASK, "scheduler init failed"पूर्ण,
	अणुSOF_IPC_PANIC_EXCEPTION, "runtime exception"पूर्ण,
	अणुSOF_IPC_PANIC_DEADLOCK, "deadlock"पूर्ण,
	अणुSOF_IPC_PANIC_STACK, "stack overflow"पूर्ण,
	अणुSOF_IPC_PANIC_IDLE, "can't enter idle"पूर्ण,
	अणुSOF_IPC_PANIC_WFI, "invalid wait state"पूर्ण,
	अणुSOF_IPC_PANIC_ASSERT, "assertion failed"पूर्ण,
पूर्ण;

/*
 * helper to be called from .dbg_dump callbacks. No error code is
 * provided, it's left as an exercise क्रम the caller of .dbg_dump
 * (typically IPC or loader)
 */
व्योम snd_sof_get_status(काष्ठा snd_sof_dev *sdev, u32 panic_code,
			u32 tracep_code, व्योम *oops,
			काष्ठा sof_ipc_panic_info *panic_info,
			व्योम *stack, माप_प्रकार stack_words)
अणु
	u32 code;
	पूर्णांक i;

	/* is firmware dead ? */
	अगर ((panic_code & SOF_IPC_PANIC_MAGIC_MASK) != SOF_IPC_PANIC_MAGIC) अणु
		dev_err(sdev->dev, "error: unexpected fault 0x%8.8x trace 0x%8.8x\n",
			panic_code, tracep_code);
		वापस; /* no fault ? */
	पूर्ण

	code = panic_code & (SOF_IPC_PANIC_MAGIC_MASK | SOF_IPC_PANIC_CODE_MASK);

	क्रम (i = 0; i < ARRAY_SIZE(panic_msg); i++) अणु
		अगर (panic_msg[i].id == code) अणु
			dev_err(sdev->dev, "error: %s\n", panic_msg[i].msg);
			dev_err(sdev->dev, "error: trace point %8.8x\n",
				tracep_code);
			जाओ out;
		पूर्ण
	पूर्ण

	/* unknown error */
	dev_err(sdev->dev, "error: unknown reason %8.8x\n", panic_code);
	dev_err(sdev->dev, "error: trace point %8.8x\n", tracep_code);

out:
	dev_err(sdev->dev, "error: panic at %s:%d\n",
		panic_info->filename, panic_info->linक्रमागत);
	sof_oops(sdev, oops);
	sof_stack(sdev, oops, stack, stack_words);
पूर्ण
EXPORT_SYMBOL(snd_sof_get_status);

/*
 *			FW Boot State Transition Diagram
 *
 *    +-----------------------------------------------------------------------+
 *    |									      |
 * ------------------	     ------------------				      |
 * |		    |	     |		      |				      |
 * |   BOOT_FAILED  |	     |  READY_FAILED  |-------------------------+     |
 * |		    |	     |	              |				|     |
 * ------------------	     ------------------				|     |
 *	^			    ^					|     |
 *	|			    |					|     |
 * (FW Boot Timeout)		(FW_READY FAIL)				|     |
 *	|			    |					|     |
 *	|			    |					|     |
 * ------------------		    |		   ------------------	|     |
 * |		    |		    |		   |		    |	|     |
 * |   IN_PROGRESS  |---------------+------------->|    COMPLETE    |	|     |
 * |		    | (FW Boot OK)   (FW_READY OK) |		    |	|     |
 * ------------------				   ------------------	|     |
 *	^						|		|     |
 *	|						|		|     |
 * (FW Loading OK)			       (System Suspend/Runसमय Suspend)
 *	|						|		|     |
 *	|						|		|     |
 * ------------------		------------------	|		|     |
 * |		    |		|		 |<-----+		|     |
 * |   PREPARE	    |		|   NOT_STARTED  |<---------------------+     |
 * |		    |		|		 |<---------------------------+
 * ------------------		------------------
 *    |	    ^			    |	   ^
 *    |	    |			    |	   |
 *    |	    +-----------------------+	   |
 *    |		(DSP Probe OK)		   |
 *    |					   |
 *    |					   |
 *    +------------------------------------+
 *	(System Suspend/Runसमय Suspend)
 */

अटल पूर्णांक sof_probe_जारी(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *plat_data = sdev->pdata;
	पूर्णांक ret;

	/* probe the DSP hardware */
	ret = snd_sof_probe(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to probe DSP %d\n", ret);
		वापस ret;
	पूर्ण

	sdev->fw_state = SOF_FW_BOOT_PREPARE;

	/* check machine info */
	ret = sof_machine_check(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to get machine info %d\n",
			ret);
		जाओ dsp_err;
	पूर्ण

	/* set up platक्रमm component driver */
	snd_sof_new_platक्रमm_drv(sdev);

	/* रेजिस्टर any debug/trace capabilities */
	ret = snd_sof_dbg_init(sdev);
	अगर (ret < 0) अणु
		/*
		 * debugfs issues are suppressed in snd_sof_dbg_init() since
		 * we cannot rely on debugfs
		 * here we trap errors due to memory allocation only.
		 */
		dev_err(sdev->dev, "error: failed to init DSP trace/debug %d\n",
			ret);
		जाओ dbg_err;
	पूर्ण

	/* init the IPC */
	sdev->ipc = snd_sof_ipc_init(sdev);
	अगर (!sdev->ipc) अणु
		ret = -ENOMEM;
		dev_err(sdev->dev, "error: failed to init DSP IPC %d\n", ret);
		जाओ ipc_err;
	पूर्ण

	/* load the firmware */
	ret = snd_sof_load_firmware(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to load DSP firmware %d\n",
			ret);
		जाओ fw_load_err;
	पूर्ण

	sdev->fw_state = SOF_FW_BOOT_IN_PROGRESS;

	/*
	 * Boot the firmware. The FW boot status will be modअगरied
	 * in snd_sof_run_firmware() depending on the outcome.
	 */
	ret = snd_sof_run_firmware(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to boot DSP firmware %d\n",
			ret);
		जाओ fw_run_err;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_ENABLE_FIRMWARE_TRACE) ||
	    (sof_core_debug & SOF_DBG_ENABLE_TRACE)) अणु
		sdev->dtrace_is_supported = true;

		/* init DMA trace */
		ret = snd_sof_init_trace(sdev);
		अगर (ret < 0) अणु
			/* non fatal */
			dev_warn(sdev->dev,
				 "warning: failed to initialize trace %d\n",
				 ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(sdev->dev, "SOF firmware trace disabled\n");
	पूर्ण

	/* hereafter all FW boot flows are क्रम PM reasons */
	sdev->first_boot = false;

	/* now रेजिस्टर audio DSP platक्रमm driver and dai */
	ret = devm_snd_soc_रेजिस्टर_component(sdev->dev, &sdev->plat_drv,
					      sof_ops(sdev)->drv,
					      sof_ops(sdev)->num_drv);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to register DSP DAI driver %d\n", ret);
		जाओ fw_trace_err;
	पूर्ण

	ret = snd_sof_machine_रेजिस्टर(sdev, plat_data);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to register machine driver %d\n", ret);
		जाओ fw_trace_err;
	पूर्ण

	/*
	 * Some platक्रमms in SOF, ex: BYT, may not have their platक्रमm PM
	 * callbacks set. Increment the usage count so as to
	 * prevent the device from entering runसमय suspend.
	 */
	अगर (!sof_ops(sdev)->runसमय_suspend || !sof_ops(sdev)->runसमय_resume)
		pm_runसमय_get_noresume(sdev->dev);

	अगर (plat_data->sof_probe_complete)
		plat_data->sof_probe_complete(sdev->dev);

	sdev->probe_completed = true;

	वापस 0;

fw_trace_err:
	snd_sof_मुक्त_trace(sdev);
fw_run_err:
	snd_sof_fw_unload(sdev);
fw_load_err:
	snd_sof_ipc_मुक्त(sdev);
ipc_err:
dbg_err:
	snd_sof_मुक्त_debug(sdev);
dsp_err:
	snd_sof_हटाओ(sdev);

	/* all resources मुक्तd, update state to match */
	sdev->fw_state = SOF_FW_BOOT_NOT_STARTED;
	sdev->first_boot = true;

	वापस ret;
पूर्ण

अटल व्योम sof_probe_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_sof_dev *sdev =
		container_of(work, काष्ठा snd_sof_dev, probe_work);
	पूर्णांक ret;

	ret = sof_probe_जारी(sdev);
	अगर (ret < 0) अणु
		/* errors cannot be propagated, log */
		dev_err(sdev->dev, "error: %s failed err: %d\n", __func__, ret);
	पूर्ण
पूर्ण

पूर्णांक snd_sof_device_probe(काष्ठा device *dev, काष्ठा snd_sof_pdata *plat_data)
अणु
	काष्ठा snd_sof_dev *sdev;

	sdev = devm_kzalloc(dev, माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	/* initialize sof device */
	sdev->dev = dev;

	/* initialize शेष DSP घातer state */
	sdev->dsp_घातer_state.state = SOF_DSP_PM_D0;

	sdev->pdata = plat_data;
	sdev->first_boot = true;
	sdev->fw_state = SOF_FW_BOOT_NOT_STARTED;
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
	sdev->extractor_stream_tag = SOF_PROBE_INVALID_NODE_ID;
#पूर्ण_अगर
	dev_set_drvdata(dev, sdev);

	/* check all mandatory ops */
	अगर (!sof_ops(sdev) || !sof_ops(sdev)->probe || !sof_ops(sdev)->run ||
	    !sof_ops(sdev)->block_पढ़ो || !sof_ops(sdev)->block_ग_लिखो ||
	    !sof_ops(sdev)->send_msg || !sof_ops(sdev)->load_firmware ||
	    !sof_ops(sdev)->ipc_msg_data || !sof_ops(sdev)->ipc_pcm_params ||
	    !sof_ops(sdev)->fw_पढ़ोy) अणु
		dev_err(dev, "error: missing mandatory ops\n");
		वापस -EINVAL;
	पूर्ण

	INIT_LIST_HEAD(&sdev->pcm_list);
	INIT_LIST_HEAD(&sdev->kcontrol_list);
	INIT_LIST_HEAD(&sdev->widget_list);
	INIT_LIST_HEAD(&sdev->dai_list);
	INIT_LIST_HEAD(&sdev->route_list);
	spin_lock_init(&sdev->ipc_lock);
	spin_lock_init(&sdev->hw_lock);
	mutex_init(&sdev->घातer_state_access);

	अगर (IS_ENABLED(CONFIG_SND_SOC_SOF_PROBE_WORK_QUEUE))
		INIT_WORK(&sdev->probe_work, sof_probe_work);

	/* set शेष समयouts अगर none provided */
	अगर (plat_data->desc->ipc_समयout == 0)
		sdev->ipc_समयout = TIMEOUT_DEFAULT_IPC_MS;
	अन्यथा
		sdev->ipc_समयout = plat_data->desc->ipc_समयout;
	अगर (plat_data->desc->boot_समयout == 0)
		sdev->boot_समयout = TIMEOUT_DEFAULT_BOOT_MS;
	अन्यथा
		sdev->boot_समयout = plat_data->desc->boot_समयout;

	अगर (IS_ENABLED(CONFIG_SND_SOC_SOF_PROBE_WORK_QUEUE)) अणु
		schedule_work(&sdev->probe_work);
		वापस 0;
	पूर्ण

	वापस sof_probe_जारी(sdev);
पूर्ण
EXPORT_SYMBOL(snd_sof_device_probe);

bool snd_sof_device_probe_completed(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);

	वापस sdev->probe_completed;
पूर्ण
EXPORT_SYMBOL(snd_sof_device_probe_completed);

पूर्णांक snd_sof_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_SND_SOC_SOF_PROBE_WORK_QUEUE))
		cancel_work_sync(&sdev->probe_work);

	अगर (sdev->fw_state > SOF_FW_BOOT_NOT_STARTED) अणु
		ret = snd_sof_dsp_घातer_करोwn_notअगरy(sdev);
		अगर (ret < 0)
			dev_warn(dev, "error: %d failed to prepare DSP for device removal",
				 ret);

		snd_sof_fw_unload(sdev);
		snd_sof_ipc_मुक्त(sdev);
		snd_sof_मुक्त_debug(sdev);
		snd_sof_मुक्त_trace(sdev);
	पूर्ण

	/*
	 * Unरेजिस्टर machine driver. This will unbind the snd_card which
	 * will हटाओ the component driver and unload the topology
	 * beक्रमe मुक्तing the snd_card.
	 */
	snd_sof_machine_unरेजिस्टर(sdev, pdata);

	/*
	 * Unरेजिस्टरing the machine driver results in unloading the topology.
	 * Some widमाला_लो, ex: scheduler, attempt to घातer करोwn the core they are
	 * scheduled on, when they are unloaded. Thereक्रमe, the DSP must be
	 * हटाओd only after the topology has been unloaded.
	 */
	अगर (sdev->fw_state > SOF_FW_BOOT_NOT_STARTED)
		snd_sof_हटाओ(sdev);

	/* release firmware */
	release_firmware(pdata->fw);
	pdata->fw = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_device_हटाओ);

पूर्णांक snd_sof_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);

	अगर (IS_ENABLED(CONFIG_SND_SOC_SOF_PROBE_WORK_QUEUE))
		cancel_work_sync(&sdev->probe_work);

	अगर (sdev->fw_state == SOF_FW_BOOT_COMPLETE)
		वापस snd_sof_shutकरोwn(sdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_device_shutकरोwn);

MODULE_AUTHOR("Liam Girdwood");
MODULE_DESCRIPTION("Sound Open Firmware (SOF) Core");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:sof-audio");
