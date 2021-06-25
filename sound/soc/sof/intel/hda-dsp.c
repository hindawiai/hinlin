<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//	    Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//	    Rander Wang <अक्रमer.wang@पूर्णांकel.com>
//          Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम generic Intel audio DSP HDA IP
 */

#समावेश <linux/module.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश "../sof-audio.h"
#समावेश "../ops.h"
#समावेश "hda.h"
#समावेश "hda-ipc.h"

अटल bool hda_enable_trace_D0I3_S0;
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG)
module_param_named(enable_trace_D0I3_S0, hda_enable_trace_D0I3_S0, bool, 0444);
MODULE_PARM_DESC(enable_trace_D0I3_S0,
		 "SOF HDA enable trace when the DSP is in D0I3 in S0");
#पूर्ण_अगर

/*
 * DSP Core control.
 */

पूर्णांक hda_dsp_core_reset_enter(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	u32 adspcs;
	u32 reset;
	पूर्णांक ret;

	/* set reset bits क्रम cores */
	reset = HDA_DSP_ADSPCS_CRST_MASK(core_mask);
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 reset, reset);

	/* poll with समयout to check अगर operation successful */
	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
					HDA_DSP_REG_ADSPCS, adspcs,
					((adspcs & reset) == reset),
					HDA_DSP_REG_POLL_INTERVAL_US,
					HDA_DSP_RESET_TIMEOUT_US);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: %s: timeout on HDA_DSP_REG_ADSPCS read\n",
			__func__);
		वापस ret;
	पूर्ण

	/* has core entered reset ? */
	adspcs = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
				  HDA_DSP_REG_ADSPCS);
	अगर ((adspcs & HDA_DSP_ADSPCS_CRST_MASK(core_mask)) !=
		HDA_DSP_ADSPCS_CRST_MASK(core_mask)) अणु
		dev_err(sdev->dev,
			"error: reset enter failed: core_mask %x adspcs 0x%x\n",
			core_mask, adspcs);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_core_reset_leave(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	अचिन्हित पूर्णांक crst;
	u32 adspcs;
	पूर्णांक ret;

	/* clear reset bits क्रम cores */
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 HDA_DSP_ADSPCS_CRST_MASK(core_mask),
					 0);

	/* poll with समयout to check अगर operation successful */
	crst = HDA_DSP_ADSPCS_CRST_MASK(core_mask);
	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
					    HDA_DSP_REG_ADSPCS, adspcs,
					    !(adspcs & crst),
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_RESET_TIMEOUT_US);

	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: %s: timeout on HDA_DSP_REG_ADSPCS read\n",
			__func__);
		वापस ret;
	पूर्ण

	/* has core left reset ? */
	adspcs = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
				  HDA_DSP_REG_ADSPCS);
	अगर ((adspcs & HDA_DSP_ADSPCS_CRST_MASK(core_mask)) != 0) अणु
		dev_err(sdev->dev,
			"error: reset leave failed: core_mask %x adspcs 0x%x\n",
			core_mask, adspcs);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_core_stall_reset(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	/* stall core */
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 HDA_DSP_ADSPCS_CSTALL_MASK(core_mask),
					 HDA_DSP_ADSPCS_CSTALL_MASK(core_mask));

	/* set reset state */
	वापस hda_dsp_core_reset_enter(sdev, core_mask);
पूर्ण

पूर्णांक hda_dsp_core_run(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret;

	/* leave reset state */
	ret = hda_dsp_core_reset_leave(sdev, core_mask);
	अगर (ret < 0)
		वापस ret;

	/* run core */
	dev_dbg(sdev->dev, "unstall/run core: core_mask = %x\n", core_mask);
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 HDA_DSP_ADSPCS_CSTALL_MASK(core_mask),
					 0);

	/* is core now running ? */
	अगर (!hda_dsp_core_is_enabled(sdev, core_mask)) अणु
		hda_dsp_core_stall_reset(sdev, core_mask);
		dev_err(sdev->dev, "error: DSP start core failed: core_mask %x\n",
			core_mask);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Power Management.
 */

पूर्णांक hda_dsp_core_घातer_up(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	अचिन्हित पूर्णांक cpa;
	u32 adspcs;
	पूर्णांक ret;

	/* update bits */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPCS,
				HDA_DSP_ADSPCS_SPA_MASK(core_mask),
				HDA_DSP_ADSPCS_SPA_MASK(core_mask));

	/* poll with समयout to check अगर operation successful */
	cpa = HDA_DSP_ADSPCS_CPA_MASK(core_mask);
	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
					    HDA_DSP_REG_ADSPCS, adspcs,
					    (adspcs & cpa) == cpa,
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_RESET_TIMEOUT_US);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: %s: timeout on HDA_DSP_REG_ADSPCS read\n",
			__func__);
		वापस ret;
	पूर्ण

	/* did core घातer up ? */
	adspcs = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR,
				  HDA_DSP_REG_ADSPCS);
	अगर ((adspcs & HDA_DSP_ADSPCS_CPA_MASK(core_mask)) !=
		HDA_DSP_ADSPCS_CPA_MASK(core_mask)) अणु
		dev_err(sdev->dev,
			"error: power up core failed core_mask %xadspcs 0x%x\n",
			core_mask, adspcs);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_core_घातer_करोwn(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	u32 adspcs;
	पूर्णांक ret;

	/* update bits */
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 HDA_DSP_ADSPCS_SPA_MASK(core_mask), 0);

	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_BAR,
				HDA_DSP_REG_ADSPCS, adspcs,
				!(adspcs & HDA_DSP_ADSPCS_CPA_MASK(core_mask)),
				HDA_DSP_REG_POLL_INTERVAL_US,
				HDA_DSP_PD_TIMEOUT * USEC_PER_MSEC);
	अगर (ret < 0)
		dev_err(sdev->dev,
			"error: %s: timeout on HDA_DSP_REG_ADSPCS read\n",
			__func__);

	वापस ret;
पूर्ण

bool hda_dsp_core_is_enabled(काष्ठा snd_sof_dev *sdev,
			     अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक val;
	bool is_enable;

	val = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPCS);

#घोषणा MASK_IS_EQUAL(v, m, field) (अणु	\
	u32 _m = field(m);		\
	((v) & _m) == _m;		\
पूर्ण)

	is_enable = MASK_IS_EQUAL(val, core_mask, HDA_DSP_ADSPCS_CPA_MASK) &&
		MASK_IS_EQUAL(val, core_mask, HDA_DSP_ADSPCS_SPA_MASK) &&
		!(val & HDA_DSP_ADSPCS_CRST_MASK(core_mask)) &&
		!(val & HDA_DSP_ADSPCS_CSTALL_MASK(core_mask));

#अघोषित MASK_IS_EQUAL

	dev_dbg(sdev->dev, "DSP core(s) enabled? %d : core_mask %x\n",
		is_enable, core_mask);

	वापस is_enable;
पूर्ण

पूर्णांक hda_dsp_enable_core(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;
	पूर्णांक ret;

	/* restrict core_mask to host managed cores mask */
	core_mask &= chip->host_managed_cores_mask;

	/* वापस अगर core_mask is not valid or cores are alपढ़ोy enabled */
	अगर (!core_mask || hda_dsp_core_is_enabled(sdev, core_mask))
		वापस 0;

	/* घातer up */
	ret = hda_dsp_core_घातer_up(sdev, core_mask);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: dsp core power up failed: core_mask %x\n",
			core_mask);
		वापस ret;
	पूर्ण

	वापस hda_dsp_core_run(sdev, core_mask);
पूर्ण

पूर्णांक hda_dsp_core_reset_घातer_करोwn(काष्ठा snd_sof_dev *sdev,
				  अचिन्हित पूर्णांक core_mask)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;
	पूर्णांक ret;

	/* restrict core_mask to host managed cores mask */
	core_mask &= chip->host_managed_cores_mask;

	/* वापस अगर core_mask is not valid */
	अगर (!core_mask)
		वापस 0;

	/* place core in reset prior to घातer करोwn */
	ret = hda_dsp_core_stall_reset(sdev, core_mask);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: dsp core reset failed: core_mask %x\n",
			core_mask);
		वापस ret;
	पूर्ण

	/* घातer करोwn core */
	ret = hda_dsp_core_घातer_करोwn(sdev, core_mask);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: dsp core power down fail mask %x: %d\n",
			core_mask, ret);
		वापस ret;
	पूर्ण

	/* make sure we are in OFF state */
	अगर (hda_dsp_core_is_enabled(sdev, core_mask)) अणु
		dev_err(sdev->dev, "error: dsp core disable fail mask %x: %d\n",
			core_mask, ret);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

व्योम hda_dsp_ipc_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;

	/* enable IPC DONE and BUSY पूर्णांकerrupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, chip->ipc_ctl,
			HDA_DSP_REG_HIPCCTL_DONE | HDA_DSP_REG_HIPCCTL_BUSY,
			HDA_DSP_REG_HIPCCTL_DONE | HDA_DSP_REG_HIPCCTL_BUSY);

	/* enable IPC पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIC,
				HDA_DSP_ADSPIC_IPC, HDA_DSP_ADSPIC_IPC);
पूर्ण

व्योम hda_dsp_ipc_पूर्णांक_disable(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;

	/* disable IPC पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIC,
				HDA_DSP_ADSPIC_IPC, 0);

	/* disable IPC BUSY and DONE पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, chip->ipc_ctl,
			HDA_DSP_REG_HIPCCTL_BUSY | HDA_DSP_REG_HIPCCTL_DONE, 0);
पूर्ण

अटल पूर्णांक hda_dsp_रुको_d0i3c_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	पूर्णांक retry = HDA_DSP_REG_POLL_RETRY_COUNT;

	जबतक (snd_hdac_chip_पढ़ोb(bus, VS_D0I3C) & SOF_HDA_VS_D0I3C_CIP) अणु
		अगर (!retry--)
			वापस -ETIMEDOUT;
		usleep_range(10, 15);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hda_dsp_send_pm_gate_ipc(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	काष्ठा sof_ipc_pm_gate pm_gate;
	काष्ठा sof_ipc_reply reply;

	स_रखो(&pm_gate, 0, माप(pm_gate));

	/* configure pm_gate ipc message */
	pm_gate.hdr.size = माप(pm_gate);
	pm_gate.hdr.cmd = SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_GATE;
	pm_gate.flags = flags;

	/* send pm_gate ipc to dsp */
	वापस sof_ipc_tx_message_no_pm(sdev->ipc, pm_gate.hdr.cmd,
					&pm_gate, माप(pm_gate), &reply,
					माप(reply));
पूर्ण

अटल पूर्णांक hda_dsp_update_d0i3c_रेजिस्टर(काष्ठा snd_sof_dev *sdev, u8 value)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	पूर्णांक ret;

	/* Write to D0I3C after Command-In-Progress bit is cleared */
	ret = hda_dsp_रुको_d0i3c_करोne(sdev);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "CIP timeout before D0I3C update!\n");
		वापस ret;
	पूर्ण

	/* Update D0I3C रेजिस्टर */
	snd_hdac_chip_updateb(bus, VS_D0I3C, SOF_HDA_VS_D0I3C_I3, value);

	/* Wait क्रम cmd in progress to be cleared beक्रमe निकासing the function */
	ret = hda_dsp_रुको_d0i3c_करोne(sdev);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "CIP timeout after D0I3C update!\n");
		वापस ret;
	पूर्ण

	dev_vdbg(bus->dev, "D0I3C updated, register = 0x%x\n",
		 snd_hdac_chip_पढ़ोb(bus, VS_D0I3C));

	वापस 0;
पूर्ण

अटल पूर्णांक hda_dsp_set_D0_state(काष्ठा snd_sof_dev *sdev,
				स्थिर काष्ठा sof_dsp_घातer_state *target_state)
अणु
	u32 flags = 0;
	पूर्णांक ret;
	u8 value = 0;

	/*
	 * Sanity check क्रम illegal state transitions
	 * The only allowed transitions are:
	 * 1. D3 -> D0I0
	 * 2. D0I0 -> D0I3
	 * 3. D0I3 -> D0I0
	 */
	चयन (sdev->dsp_घातer_state.state) अणु
	हाल SOF_DSP_PM_D0:
		/* Follow the sequence below क्रम D0 substate transitions */
		अवरोध;
	हाल SOF_DSP_PM_D3:
		/* Follow regular flow क्रम D3 -> D0 transition */
		वापस 0;
	शेष:
		dev_err(sdev->dev, "error: transition from %d to %d not allowed\n",
			sdev->dsp_घातer_state.state, target_state->state);
		वापस -EINVAL;
	पूर्ण

	/* Set flags and रेजिस्टर value क्रम D0 target substate */
	अगर (target_state->substate == SOF_HDA_DSP_PM_D0I3) अणु
		value = SOF_HDA_VS_D0I3C_I3;

		/*
		 * Trace DMA need to be disabled when the DSP enters
		 * D0I3 क्रम S0Ix suspend, but it can be kept enabled
		 * when the DSP enters D0I3 जबतक the प्रणाली is in S0
		 * क्रम debug purpose.
		 */
		अगर (!sdev->dtrace_is_supported ||
		    !hda_enable_trace_D0I3_S0 ||
		    sdev->प्रणाली_suspend_target != SOF_SUSPEND_NONE)
			flags = HDA_PM_NO_DMA_TRACE;
	पूर्ण अन्यथा अणु
		/* prevent घातer gating in D0I0 */
		flags = HDA_PM_PPG;
	पूर्ण

	/* update D0I3C रेजिस्टर */
	ret = hda_dsp_update_d0i3c_रेजिस्टर(sdev, value);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Notअगरy the DSP of the state change.
	 * If this IPC fails, revert the D0I3C रेजिस्टर update in order
	 * to prevent partial state change.
	 */
	ret = hda_dsp_send_pm_gate_ipc(sdev, flags);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: PM_GATE ipc error %d\n", ret);
		जाओ revert;
	पूर्ण

	वापस ret;

revert:
	/* fallback to the previous रेजिस्टर value */
	value = value ? 0 : SOF_HDA_VS_D0I3C_I3;

	/*
	 * This can fail but वापस the IPC error to संकेत that
	 * the state change failed.
	 */
	hda_dsp_update_d0i3c_रेजिस्टर(sdev, value);

	वापस ret;
पूर्ण

/* helper to log DSP state */
अटल व्योम hda_dsp_state_log(काष्ठा snd_sof_dev *sdev)
अणु
	चयन (sdev->dsp_घातer_state.state) अणु
	हाल SOF_DSP_PM_D0:
		चयन (sdev->dsp_घातer_state.substate) अणु
		हाल SOF_HDA_DSP_PM_D0I0:
			dev_dbg(sdev->dev, "Current DSP power state: D0I0\n");
			अवरोध;
		हाल SOF_HDA_DSP_PM_D0I3:
			dev_dbg(sdev->dev, "Current DSP power state: D0I3\n");
			अवरोध;
		शेष:
			dev_dbg(sdev->dev, "Unknown DSP D0 substate: %d\n",
				sdev->dsp_घातer_state.substate);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_DSP_PM_D1:
		dev_dbg(sdev->dev, "Current DSP power state: D1\n");
		अवरोध;
	हाल SOF_DSP_PM_D2:
		dev_dbg(sdev->dev, "Current DSP power state: D2\n");
		अवरोध;
	हाल SOF_DSP_PM_D3_HOT:
		dev_dbg(sdev->dev, "Current DSP power state: D3_HOT\n");
		अवरोध;
	हाल SOF_DSP_PM_D3:
		dev_dbg(sdev->dev, "Current DSP power state: D3\n");
		अवरोध;
	हाल SOF_DSP_PM_D3_COLD:
		dev_dbg(sdev->dev, "Current DSP power state: D3_COLD\n");
		अवरोध;
	शेष:
		dev_dbg(sdev->dev, "Unknown DSP power state: %d\n",
			sdev->dsp_घातer_state.state);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * All DSP घातer state transitions are initiated by the driver.
 * If the requested state change fails, the error is simply वापसed.
 * Further state transitions are attempted only when the set_घातer_save() op
 * is called again either because of a new IPC sent to the DSP or
 * during प्रणाली suspend/resume.
 */
पूर्णांक hda_dsp_set_घातer_state(काष्ठा snd_sof_dev *sdev,
			    स्थिर काष्ठा sof_dsp_घातer_state *target_state)
अणु
	पूर्णांक ret = 0;

	/*
	 * When the DSP is alपढ़ोy in D0I3 and the target state is D0I3,
	 * it could be the हाल that the DSP is in D0I3 during S0
	 * and the प्रणाली is suspending to S0Ix. Thereक्रमe,
	 * hda_dsp_set_D0_state() must be called to disable trace DMA
	 * by sending the PM_GATE IPC to the FW.
	 */
	अगर (target_state->substate == SOF_HDA_DSP_PM_D0I3 &&
	    sdev->प्रणाली_suspend_target == SOF_SUSPEND_S0IX)
		जाओ set_state;

	/*
	 * For all other हालs, वापस without करोing anything अगर
	 * the DSP is alपढ़ोy in the target state.
	 */
	अगर (target_state->state == sdev->dsp_घातer_state.state &&
	    target_state->substate == sdev->dsp_घातer_state.substate)
		वापस 0;

set_state:
	चयन (target_state->state) अणु
	हाल SOF_DSP_PM_D0:
		ret = hda_dsp_set_D0_state(sdev, target_state);
		अवरोध;
	हाल SOF_DSP_PM_D3:
		/* The only allowed transition is: D0I0 -> D3 */
		अगर (sdev->dsp_घातer_state.state == SOF_DSP_PM_D0 &&
		    sdev->dsp_घातer_state.substate == SOF_HDA_DSP_PM_D0I0)
			अवरोध;

		dev_err(sdev->dev,
			"error: transition from %d to %d not allowed\n",
			sdev->dsp_घातer_state.state, target_state->state);
		वापस -EINVAL;
	शेष:
		dev_err(sdev->dev, "error: target state unsupported %d\n",
			target_state->state);
		वापस -EINVAL;
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"failed to set requested target DSP state %d substate %d\n",
			target_state->state, target_state->substate);
		वापस ret;
	पूर्ण

	sdev->dsp_घातer_state = *target_state;
	hda_dsp_state_log(sdev);
	वापस ret;
पूर्ण

/*
 * Audio DSP states may transक्रमm as below:-
 *
 *                                         Opportunistic D0I3 in S0
 *     Runसमय    +---------------------+  Delayed D0i3 work समयout
 *     suspend    |                     +--------------------+
 *   +------------+       D0I0(active)  |                    |
 *   |            |                     <---------------+    |
 *   |   +-------->                     |    New IPC	|    |
 *   |   |Runसमय +--^--+---------^--+--+ (via mailbox)	|    |
 *   |   |resume     |  |         |  |			|    |
 *   |   |           |  |         |  |			|    |
 *   |   |     System|  |         |  |			|    |
 *   |   |     resume|  | S3/S0IX |  |                  |    |
 *   |   |	     |  | suspend |  | S0IX             |    |
 *   |   |           |  |         |  |suspend           |    |
 *   |   |           |  |         |  |                  |    |
 *   |   |           |  |         |  |                  |    |
 * +-v---+-----------+--v-------+ |  |           +------+----v----+
 * |                            | |  +----------->                |
 * |       D3 (suspended)       | |              |      D0I3      |
 * |                            | +--------------+                |
 * |                            |  System resume |                |
 * +----------------------------+		 +----------------+
 *
 * S0IX suspend: The DSP is in D0I3 अगर any D0I3-compatible streams
 *		 ignored the suspend trigger. Otherwise the DSP
 *		 is in D3.
 */

अटल पूर्णांक hda_suspend(काष्ठा snd_sof_dev *sdev, bool runसमय_suspend)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *chip = hda->desc;
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
#पूर्ण_अगर
	पूर्णांक ret;

	hda_sdw_पूर्णांक_enable(sdev, false);

	/* disable IPC पूर्णांकerrupts */
	hda_dsp_ipc_पूर्णांक_disable(sdev);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	अगर (runसमय_suspend)
		hda_codec_jack_wake_enable(sdev, true);

	/* घातer करोwn all hda link */
	snd_hdac_ext_bus_link_घातer_करोwn_all(bus);
#पूर्ण_अगर

	/* घातer करोwn DSP */
	ret = snd_sof_dsp_core_घातer_करोwn(sdev, chip->host_managed_cores_mask);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to power down core during suspend\n");
		वापस ret;
	पूर्ण

	/* disable ppcap पूर्णांकerrupt */
	hda_dsp_ctrl_ppcap_enable(sdev, false);
	hda_dsp_ctrl_ppcap_पूर्णांक_enable(sdev, false);

	/* disable hda bus irq and streams */
	hda_dsp_ctrl_stop_chip(sdev);

	/* disable LP retention mode */
	snd_sof_pci_update_bits(sdev, PCI_PGCTL,
				PCI_PGCTL_LSRMD_MASK, PCI_PGCTL_LSRMD_MASK);

	/* reset controller */
	ret = hda_dsp_ctrl_link_reset(sdev, true);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to reset controller during suspend\n");
		वापस ret;
	पूर्ण

	/* display codec can घातered off after link reset */
	hda_codec_i915_display_घातer(sdev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक hda_resume(काष्ठा snd_sof_dev *sdev, bool runसमय_resume)
अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_ext_link *hlink = शून्य;
#पूर्ण_अगर
	पूर्णांक ret;

	/* display codec must be घातered beक्रमe link reset */
	hda_codec_i915_display_घातer(sdev, true);

	/*
	 * clear TCSEL to clear playback on some HD Audio
	 * codecs. PCI TCSEL is defined in the Intel manuals.
	 */
	snd_sof_pci_update_bits(sdev, PCI_TCSEL, 0x07, 0);

	/* reset and start hda controller */
	ret = hda_dsp_ctrl_init_chip(sdev, true);
	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: failed to start controller after resume\n");
		जाओ cleanup;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* check jack status */
	अगर (runसमय_resume) अणु
		hda_codec_jack_wake_enable(sdev, false);
		अगर (sdev->प्रणाली_suspend_target == SOF_SUSPEND_NONE)
			hda_codec_jack_check(sdev);
	पूर्ण

	/* turn off the links that were off beक्रमe suspend */
	list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
		अगर (!hlink->ref_count)
			snd_hdac_ext_bus_link_घातer_करोwn(hlink);
	पूर्ण

	/* check dma status and clean up CORB/RIRB buffers */
	अगर (!bus->cmd_dma_state)
		snd_hdac_bus_stop_cmd_io(bus);
#पूर्ण_अगर

	/* enable ppcap पूर्णांकerrupt */
	hda_dsp_ctrl_ppcap_enable(sdev, true);
	hda_dsp_ctrl_ppcap_पूर्णांक_enable(sdev, true);

cleanup:
	/* display codec can घातered off after controller init */
	hda_codec_i915_display_घातer(sdev, false);

	वापस 0;
पूर्ण

पूर्णांक hda_dsp_resume(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	स्थिर काष्ठा sof_dsp_घातer_state target_state = अणु
		.state = SOF_DSP_PM_D0,
		.substate = SOF_HDA_DSP_PM_D0I0,
	पूर्ण;
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_ext_link *hlink = शून्य;
#पूर्ण_अगर
	पूर्णांक ret;

	/* resume from D0I3 */
	अगर (sdev->dsp_घातer_state.state == SOF_DSP_PM_D0) अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
		/* घातer up links that were active beक्रमe suspend */
		list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
			अगर (hlink->ref_count) अणु
				ret = snd_hdac_ext_bus_link_घातer_up(hlink);
				अगर (ret < 0) अणु
					dev_dbg(sdev->dev,
						"error %d in %s: failed to power up links",
						ret, __func__);
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण

		/* set up CORB/RIRB buffers अगर was on beक्रमe suspend */
		अगर (bus->cmd_dma_state)
			snd_hdac_bus_init_cmd_io(bus);
#पूर्ण_अगर

		/* Set DSP घातer state */
		ret = snd_sof_dsp_set_घातer_state(sdev, &target_state);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: setting dsp state %d substate %d\n",
				target_state.state, target_state.substate);
			वापस ret;
		पूर्ण

		/* restore L1SEN bit */
		अगर (hda->l1_support_changed)
			snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
						HDA_VS_INTEL_EM2,
						HDA_VS_INTEL_EM2_L1SEN, 0);

		/* restore and disable the प्रणाली wakeup */
		pci_restore_state(pci);
		disable_irq_wake(pci->irq);
		वापस 0;
	पूर्ण

	/* init hda controller. DSP cores will be घातered up during fw boot */
	ret = hda_resume(sdev, false);
	अगर (ret < 0)
		वापस ret;

	वापस snd_sof_dsp_set_घातer_state(sdev, &target_state);
पूर्ण

पूर्णांक hda_dsp_runसमय_resume(काष्ठा snd_sof_dev *sdev)
अणु
	स्थिर काष्ठा sof_dsp_घातer_state target_state = अणु
		.state = SOF_DSP_PM_D0,
	पूर्ण;
	पूर्णांक ret;

	/* init hda controller. DSP cores will be घातered up during fw boot */
	ret = hda_resume(sdev, true);
	अगर (ret < 0)
		वापस ret;

	वापस snd_sof_dsp_set_घातer_state(sdev, &target_state);
पूर्ण

पूर्णांक hda_dsp_runसमय_idle(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *hbus = sof_to_bus(sdev);

	अगर (hbus->codec_घातered) अणु
		dev_dbg(sdev->dev, "some codecs still powered (%08X), not idle\n",
			(अचिन्हित पूर्णांक)hbus->codec_घातered);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hda_dsp_runसमय_suspend(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	स्थिर काष्ठा sof_dsp_घातer_state target_state = अणु
		.state = SOF_DSP_PM_D3,
	पूर्ण;
	पूर्णांक ret;

	/* cancel any attempt क्रम DSP D0I3 */
	cancel_delayed_work_sync(&hda->d0i3_work);

	/* stop hda controller and घातer dsp off */
	ret = hda_suspend(sdev, true);
	अगर (ret < 0)
		वापस ret;

	वापस snd_sof_dsp_set_घातer_state(sdev, &target_state);
पूर्ण

पूर्णांक hda_dsp_suspend(काष्ठा snd_sof_dev *sdev, u32 target_state)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	स्थिर काष्ठा sof_dsp_घातer_state target_dsp_state = अणु
		.state = target_state,
		.substate = target_state == SOF_DSP_PM_D0 ?
				SOF_HDA_DSP_PM_D0I3 : 0,
	पूर्ण;
	पूर्णांक ret;

	/* cancel any attempt क्रम DSP D0I3 */
	cancel_delayed_work_sync(&hda->d0i3_work);

	अगर (target_state == SOF_DSP_PM_D0) अणु
		/* Set DSP घातer state */
		ret = snd_sof_dsp_set_घातer_state(sdev, &target_dsp_state);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: setting dsp state %d substate %d\n",
				target_dsp_state.state,
				target_dsp_state.substate);
			वापस ret;
		पूर्ण

		/* enable L1SEN to make sure the प्रणाली can enter S0Ix */
		hda->l1_support_changed =
			snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
						HDA_VS_INTEL_EM2,
						HDA_VS_INTEL_EM2_L1SEN,
						HDA_VS_INTEL_EM2_L1SEN);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
		/* stop the CORB/RIRB DMA अगर it is On */
		अगर (bus->cmd_dma_state)
			snd_hdac_bus_stop_cmd_io(bus);

		/* no link can be घातered in s0ix state */
		ret = snd_hdac_ext_bus_link_घातer_करोwn_all(bus);
		अगर (ret < 0) अणु
			dev_dbg(sdev->dev,
				"error %d in %s: failed to power down links",
				ret, __func__);
			वापस ret;
		पूर्ण
#पूर्ण_अगर

		/* enable the प्रणाली waking up via IPC IRQ */
		enable_irq_wake(pci->irq);
		pci_save_state(pci);
		वापस 0;
	पूर्ण

	/* stop hda controller and घातer dsp off */
	ret = hda_suspend(sdev, false);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "error: suspending dsp\n");
		वापस ret;
	पूर्ण

	वापस snd_sof_dsp_set_घातer_state(sdev, &target_dsp_state);
पूर्ण

पूर्णांक hda_dsp_shutकरोwn(काष्ठा snd_sof_dev *sdev)
अणु
	sdev->प्रणाली_suspend_target = SOF_SUSPEND_S3;
	वापस snd_sof_suspend(sdev->dev);
पूर्ण

पूर्णांक hda_dsp_set_hw_params_upon_resume(काष्ठा snd_sof_dev *sdev)
अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा hdac_ext_stream *stream;
	काष्ठा hdac_ext_link *link;
	काष्ठा hdac_stream *s;
	स्थिर अक्षर *name;
	पूर्णांक stream_tag;

	/* set पूर्णांकernal flag क्रम BE */
	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		stream = stream_to_hdac_ext_stream(s);

		/*
		 * clear stream. This should alपढ़ोy be taken care क्रम running
		 * streams when the SUSPEND trigger is called. But छोड़ोd
		 * streams करो not get suspended, so this needs to be करोne
		 * explicitly during suspend.
		 */
		अगर (stream->link_substream) अणु
			rtd = asoc_substream_to_rtd(stream->link_substream);
			name = asoc_rtd_to_codec(rtd, 0)->component->name;
			link = snd_hdac_ext_bus_get_link(bus, name);
			अगर (!link)
				वापस -EINVAL;

			stream->link_prepared = 0;

			अगर (hdac_stream(stream)->direction ==
				SNDRV_PCM_STREAM_CAPTURE)
				जारी;

			stream_tag = hdac_stream(stream)->stream_tag;
			snd_hdac_ext_link_clear_stream_id(link, stream_tag);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम hda_dsp_d0i3_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev = container_of(work,
						      काष्ठा sof_पूर्णांकel_hda_dev,
						      d0i3_work.work);
	काष्ठा hdac_bus *bus = &hdev->hbus.core;
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(bus->dev);
	काष्ठा sof_dsp_घातer_state target_state = अणु
		.state = SOF_DSP_PM_D0,
		.substate = SOF_HDA_DSP_PM_D0I3,
	पूर्ण;
	पूर्णांक ret;

	/* DSP can enter D0I3 अगरf only D0I3-compatible streams are active */
	अगर (!snd_sof_dsp_only_d0i3_compatible_stream_active(sdev))
		/* reमुख्य in D0I0 */
		वापस;

	/* This can fail but error cannot be propagated */
	ret = snd_sof_dsp_set_घातer_state(sdev, &target_state);
	अगर (ret < 0)
		dev_err_ratelimited(sdev->dev,
				    "error: failed to set DSP state %d substate %d\n",
				    target_state.state, target_state.substate);
पूर्ण
