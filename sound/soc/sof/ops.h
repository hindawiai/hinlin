<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 *
 * Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __SOUND_SOC_SOF_IO_H
#घोषणा __SOUND_SOC_SOF_IO_H

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <sound/pcm.h>
#समावेश "sof-priv.h"

#घोषणा sof_ops(sdev) \
	((sdev)->pdata->desc->ops)

/* Mandatory operations are verअगरied during probing */

/* init */
अटल अंतरभूत पूर्णांक snd_sof_probe(काष्ठा snd_sof_dev *sdev)
अणु
	वापस sof_ops(sdev)->probe(sdev);
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_हटाओ(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->हटाओ)
		वापस sof_ops(sdev)->हटाओ(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_shutकरोwn(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->shutकरोwn)
		वापस sof_ops(sdev)->shutकरोwn(sdev);

	वापस 0;
पूर्ण

/* control */

/*
 * snd_sof_dsp_run वापसs the core mask of the cores that are available
 * after successful fw boot
 */
अटल अंतरभूत पूर्णांक snd_sof_dsp_run(काष्ठा snd_sof_dev *sdev)
अणु
	वापस sof_ops(sdev)->run(sdev);
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_stall(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask)
अणु
	अगर (sof_ops(sdev)->stall)
		वापस sof_ops(sdev)->stall(sdev, core_mask);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_reset(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->reset)
		वापस sof_ops(sdev)->reset(sdev);

	वापस 0;
पूर्ण

/* dsp core घातer up/घातer करोwn */
अटल अंतरभूत पूर्णांक snd_sof_dsp_core_घातer_up(काष्ठा snd_sof_dev *sdev,
					    अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret = 0;

	core_mask &= ~sdev->enabled_cores_mask;
	अगर (sof_ops(sdev)->core_घातer_up && core_mask) अणु
		ret = sof_ops(sdev)->core_घातer_up(sdev, core_mask);
		अगर (!ret)
			sdev->enabled_cores_mask |= core_mask;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_core_घातer_करोwn(काष्ठा snd_sof_dev *sdev,
					      अचिन्हित पूर्णांक core_mask)
अणु
	पूर्णांक ret = 0;

	core_mask &= sdev->enabled_cores_mask;
	अगर (sof_ops(sdev)->core_घातer_करोwn && core_mask) अणु
		ret = sof_ops(sdev)->core_घातer_करोwn(sdev, core_mask);
		अगर (!ret)
			sdev->enabled_cores_mask &= ~core_mask;
	पूर्ण

	वापस ret;
पूर्ण

/* pre/post fw load */
अटल अंतरभूत पूर्णांक snd_sof_dsp_pre_fw_run(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->pre_fw_run)
		वापस sof_ops(sdev)->pre_fw_run(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_post_fw_run(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->post_fw_run)
		वापस sof_ops(sdev)->post_fw_run(sdev);

	वापस 0;
पूर्ण

/* parse platक्रमm specअगरic extended manअगरest */
अटल अंतरभूत पूर्णांक snd_sof_dsp_parse_platक्रमm_ext_manअगरest(काष्ठा snd_sof_dev *sdev,
							  स्थिर काष्ठा sof_ext_man_elem_header *hdr)
अणु
	अगर (sof_ops(sdev)->parse_platक्रमm_ext_manअगरest)
		वापस sof_ops(sdev)->parse_platक्रमm_ext_manअगरest(sdev, hdr);

	वापस 0;
पूर्ण

/* misc */

/**
 * snd_sof_dsp_get_bar_index - Maps a section type with a BAR index
 *
 * @sdev: sof device
 * @type: section type as described by snd_sof_fw_blk_type
 *
 * Returns the corresponding BAR index (a positive पूर्णांकeger) or -EINVAL
 * in हाल there is no mapping
 */
अटल अंतरभूत पूर्णांक snd_sof_dsp_get_bar_index(काष्ठा snd_sof_dev *sdev, u32 type)
अणु
	अगर (sof_ops(sdev)->get_bar_index)
		वापस sof_ops(sdev)->get_bar_index(sdev, type);

	वापस sdev->mmio_bar;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_get_mailbox_offset(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->get_mailbox_offset)
		वापस sof_ops(sdev)->get_mailbox_offset(sdev);

	dev_err(sdev->dev, "error: %s not defined\n", __func__);
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev,
						u32 id)
अणु
	अगर (sof_ops(sdev)->get_winकरोw_offset)
		वापस sof_ops(sdev)->get_winकरोw_offset(sdev, id);

	dev_err(sdev->dev, "error: %s not defined\n", __func__);
	वापस -ENOTSUPP;
पूर्ण
/* घातer management */
अटल अंतरभूत पूर्णांक snd_sof_dsp_resume(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->resume)
		वापस sof_ops(sdev)->resume(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_suspend(काष्ठा snd_sof_dev *sdev,
				      u32 target_state)
अणु
	अगर (sof_ops(sdev)->suspend)
		वापस sof_ops(sdev)->suspend(sdev, target_state);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_runसमय_resume(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->runसमय_resume)
		वापस sof_ops(sdev)->runसमय_resume(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_runसमय_suspend(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->runसमय_suspend)
		वापस sof_ops(sdev)->runसमय_suspend(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_runसमय_idle(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->runसमय_idle)
		वापस sof_ops(sdev)->runसमय_idle(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_hw_params_upon_resume(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->set_hw_params_upon_resume)
		वापस sof_ops(sdev)->set_hw_params_upon_resume(sdev);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dsp_set_clk(काष्ठा snd_sof_dev *sdev, u32 freq)
अणु
	अगर (sof_ops(sdev)->set_clk)
		वापस sof_ops(sdev)->set_clk(sdev, freq);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
snd_sof_dsp_set_घातer_state(काष्ठा snd_sof_dev *sdev,
			    स्थिर काष्ठा sof_dsp_घातer_state *target_state)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&sdev->घातer_state_access);

	अगर (sof_ops(sdev)->set_घातer_state)
		ret = sof_ops(sdev)->set_घातer_state(sdev, target_state);

	mutex_unlock(&sdev->घातer_state_access);

	वापस ret;
पूर्ण

/* debug */
अटल अंतरभूत व्योम snd_sof_dsp_dbg_dump(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	अगर (sof_ops(sdev)->dbg_dump)
		वापस sof_ops(sdev)->dbg_dump(sdev, flags);
पूर्ण

अटल अंतरभूत व्योम snd_sof_ipc_dump(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->ipc_dump)
		वापस sof_ops(sdev)->ipc_dump(sdev);
पूर्ण

/* रेजिस्टर IO */
अटल अंतरभूत व्योम snd_sof_dsp_ग_लिखो(काष्ठा snd_sof_dev *sdev, u32 bar,
				     u32 offset, u32 value)
अणु
	अगर (sof_ops(sdev)->ग_लिखो) अणु
		sof_ops(sdev)->ग_लिखो(sdev, sdev->bar[bar] + offset, value);
		वापस;
	पूर्ण

	dev_err_ratelimited(sdev->dev, "error: %s not defined\n", __func__);
पूर्ण

अटल अंतरभूत व्योम snd_sof_dsp_ग_लिखो64(काष्ठा snd_sof_dev *sdev, u32 bar,
				       u32 offset, u64 value)
अणु
	अगर (sof_ops(sdev)->ग_लिखो64) अणु
		sof_ops(sdev)->ग_लिखो64(sdev, sdev->bar[bar] + offset, value);
		वापस;
	पूर्ण

	dev_err_ratelimited(sdev->dev, "error: %s not defined\n", __func__);
पूर्ण

अटल अंतरभूत u32 snd_sof_dsp_पढ़ो(काष्ठा snd_sof_dev *sdev, u32 bar,
				   u32 offset)
अणु
	अगर (sof_ops(sdev)->पढ़ो)
		वापस sof_ops(sdev)->पढ़ो(sdev, sdev->bar[bar] + offset);

	dev_err(sdev->dev, "error: %s not defined\n", __func__);
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत u64 snd_sof_dsp_पढ़ो64(काष्ठा snd_sof_dev *sdev, u32 bar,
				     u32 offset)
अणु
	अगर (sof_ops(sdev)->पढ़ो64)
		वापस sof_ops(sdev)->पढ़ो64(sdev, sdev->bar[bar] + offset);

	dev_err(sdev->dev, "error: %s not defined\n", __func__);
	वापस -ENOTSUPP;
पूर्ण

/* block IO */
अटल अंतरभूत व्योम snd_sof_dsp_block_पढ़ो(काष्ठा snd_sof_dev *sdev, u32 bar,
					  u32 offset, व्योम *dest, माप_प्रकार bytes)
अणु
	sof_ops(sdev)->block_पढ़ो(sdev, bar, offset, dest, bytes);
पूर्ण

अटल अंतरभूत व्योम snd_sof_dsp_block_ग_लिखो(काष्ठा snd_sof_dev *sdev, u32 bar,
					   u32 offset, व्योम *src, माप_प्रकार bytes)
अणु
	sof_ops(sdev)->block_ग_लिखो(sdev, bar, offset, src, bytes);
पूर्ण

/* ipc */
अटल अंतरभूत पूर्णांक snd_sof_dsp_send_msg(काष्ठा snd_sof_dev *sdev,
				       काष्ठा snd_sof_ipc_msg *msg)
अणु
	वापस sof_ops(sdev)->send_msg(sdev, msg);
पूर्ण

/* host DMA trace */
अटल अंतरभूत पूर्णांक snd_sof_dma_trace_init(काष्ठा snd_sof_dev *sdev,
					 u32 *stream_tag)
अणु
	अगर (sof_ops(sdev)->trace_init)
		वापस sof_ops(sdev)->trace_init(sdev, stream_tag);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dma_trace_release(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev)->trace_release)
		वापस sof_ops(sdev)->trace_release(sdev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_sof_dma_trace_trigger(काष्ठा snd_sof_dev *sdev, पूर्णांक cmd)
अणु
	अगर (sof_ops(sdev)->trace_trigger)
		वापस sof_ops(sdev)->trace_trigger(sdev, cmd);

	वापस 0;
पूर्ण

/* host PCM ops */
अटल अंतरभूत पूर्णांक
snd_sof_pcm_platक्रमm_खोलो(काष्ठा snd_sof_dev *sdev,
			  काष्ठा snd_pcm_substream *substream)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->pcm_खोलो)
		वापस sof_ops(sdev)->pcm_खोलो(sdev, substream);

	वापस 0;
पूर्ण

/* disconnect pcm substream to a host stream */
अटल अंतरभूत पूर्णांक
snd_sof_pcm_platक्रमm_बंद(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_pcm_substream *substream)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->pcm_बंद)
		वापस sof_ops(sdev)->pcm_बंद(sdev, substream);

	वापस 0;
पूर्ण

/* host stream hw params */
अटल अंतरभूत पूर्णांक
snd_sof_pcm_platक्रमm_hw_params(काष्ठा snd_sof_dev *sdev,
			       काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा sof_ipc_stream_params *ipc_params)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->pcm_hw_params)
		वापस sof_ops(sdev)->pcm_hw_params(sdev, substream,
						    params, ipc_params);

	वापस 0;
पूर्ण

/* host stream hw मुक्त */
अटल अंतरभूत पूर्णांक
snd_sof_pcm_platक्रमm_hw_मुक्त(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_pcm_substream *substream)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->pcm_hw_मुक्त)
		वापस sof_ops(sdev)->pcm_hw_मुक्त(sdev, substream);

	वापस 0;
पूर्ण

/* host stream trigger */
अटल अंतरभूत पूर्णांक
snd_sof_pcm_platक्रमm_trigger(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->pcm_trigger)
		वापस sof_ops(sdev)->pcm_trigger(sdev, substream, cmd);

	वापस 0;
पूर्ण

/* host DSP message data */
अटल अंतरभूत व्योम snd_sof_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
					काष्ठा snd_pcm_substream *substream,
					व्योम *p, माप_प्रकार sz)
अणु
	sof_ops(sdev)->ipc_msg_data(sdev, substream, p, sz);
पूर्ण

/* host configure DSP HW parameters */
अटल अंतरभूत पूर्णांक
snd_sof_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
		       काष्ठा snd_pcm_substream *substream,
		       स्थिर काष्ठा sof_ipc_pcm_params_reply *reply)
अणु
	वापस sof_ops(sdev)->ipc_pcm_params(sdev, substream, reply);
पूर्ण

/* host stream poपूर्णांकer */
अटल अंतरभूत snd_pcm_uframes_t
snd_sof_pcm_platक्रमm_poपूर्णांकer(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_pcm_substream *substream)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->pcm_poपूर्णांकer)
		वापस sof_ops(sdev)->pcm_poपूर्णांकer(sdev, substream);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
अटल अंतरभूत पूर्णांक
snd_sof_probe_compr_assign(काष्ठा snd_sof_dev *sdev,
		काष्ठा snd_compr_stream *cstream, काष्ठा snd_soc_dai *dai)
अणु
	वापस sof_ops(sdev)->probe_assign(sdev, cstream, dai);
पूर्ण

अटल अंतरभूत पूर्णांक
snd_sof_probe_compr_मुक्त(काष्ठा snd_sof_dev *sdev,
		काष्ठा snd_compr_stream *cstream, काष्ठा snd_soc_dai *dai)
अणु
	वापस sof_ops(sdev)->probe_मुक्त(sdev, cstream, dai);
पूर्ण

अटल अंतरभूत पूर्णांक
snd_sof_probe_compr_set_params(काष्ठा snd_sof_dev *sdev,
		काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_compr_params *params, काष्ठा snd_soc_dai *dai)
अणु
	वापस sof_ops(sdev)->probe_set_params(sdev, cstream, params, dai);
पूर्ण

अटल अंतरभूत पूर्णांक
snd_sof_probe_compr_trigger(काष्ठा snd_sof_dev *sdev,
		काष्ठा snd_compr_stream *cstream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai)
अणु
	वापस sof_ops(sdev)->probe_trigger(sdev, cstream, cmd, dai);
पूर्ण

अटल अंतरभूत पूर्णांक
snd_sof_probe_compr_poपूर्णांकer(काष्ठा snd_sof_dev *sdev,
		काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_compr_tstamp *tstamp, काष्ठा snd_soc_dai *dai)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->probe_poपूर्णांकer)
		वापस sof_ops(sdev)->probe_poपूर्णांकer(sdev, cstream, tstamp, dai);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* machine driver */
अटल अंतरभूत पूर्णांक
snd_sof_machine_रेजिस्टर(काष्ठा snd_sof_dev *sdev, व्योम *pdata)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->machine_रेजिस्टर)
		वापस sof_ops(sdev)->machine_रेजिस्टर(sdev, pdata);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
snd_sof_machine_unरेजिस्टर(काष्ठा snd_sof_dev *sdev, व्योम *pdata)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->machine_unरेजिस्टर)
		sof_ops(sdev)->machine_unरेजिस्टर(sdev, pdata);
पूर्ण

अटल अंतरभूत व्योम
snd_sof_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->machine_select)
		sof_ops(sdev)->machine_select(sdev);
पूर्ण

अटल अंतरभूत व्योम
snd_sof_set_mach_params(स्थिर काष्ठा snd_soc_acpi_mach *mach,
			काष्ठा snd_sof_dev *sdev)
अणु
	अगर (sof_ops(sdev) && sof_ops(sdev)->set_mach_params)
		sof_ops(sdev)->set_mach_params(mach, sdev);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा snd_sof_dsp_ops
*sof_get_ops(स्थिर काष्ठा sof_dev_desc *d,
	     स्थिर काष्ठा sof_ops_table mach_ops[], पूर्णांक asize)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < asize; i++) अणु
		अगर (d == mach_ops[i].desc)
			वापस mach_ops[i].ops;
	पूर्ण

	/* not found */
	वापस शून्य;
पूर्ण

/**
 * snd_sof_dsp_रेजिस्टर_poll_समयout - Periodically poll an address
 * until a condition is met or a समयout occurs
 * @op: accessor function (takes @addr as its only argument)
 * @addr: Address to poll
 * @val: Variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @sleep_us: Maximum समय to sleep between पढ़ोs in us (0
 *            tight-loops).  Should be less than ~20ms since usleep_range
 *            is used (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout. In either
 * हाल, the last पढ़ो value at @addr is stored in @val. Must not
 * be called from atomic context अगर sleep_us or समयout_us are used.
 *
 * This is modelled after the पढ़ोx_poll_समयout macros in linux/iopoll.h.
 */
#घोषणा snd_sof_dsp_पढ़ो_poll_समयout(sdev, bar, offset, val, cond, sleep_us, समयout_us) \
(अणु \
	u64 __समयout_us = (समयout_us); \
	अचिन्हित दीर्घ __sleep_us = (sleep_us); \
	kसमय_प्रकार __समयout = kसमय_add_us(kसमय_get(), __समयout_us); \
	might_sleep_अगर((__sleep_us) != 0); \
	क्रम (;;) अणु							\
		(val) = snd_sof_dsp_पढ़ो(sdev, bar, offset);		\
		अगर (cond) अणु \
			dev_dbg(sdev->dev, \
				"FW Poll Status: reg=%#x successful\n", (val)); \
			अवरोध; \
		पूर्ण \
		अगर (__समयout_us && \
		    kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			(val) = snd_sof_dsp_पढ़ो(sdev, bar, offset); \
			dev_dbg(sdev->dev, \
				"FW Poll Status: reg=%#x timedout\n", (val)); \
			अवरोध; \
		पूर्ण \
		अगर (__sleep_us) \
			usleep_range((__sleep_us >> 2) + 1, __sleep_us); \
	पूर्ण \
	(cond) ? 0 : -ETIMEDOUT; \
पूर्ण)

/* This is क्रम रेजिस्टरs bits with attribute RWC */
bool snd_sof_pci_update_bits(काष्ठा snd_sof_dev *sdev, u32 offset,
			     u32 mask, u32 value);

bool snd_sof_dsp_update_bits_unlocked(काष्ठा snd_sof_dev *sdev, u32 bar,
				      u32 offset, u32 mask, u32 value);

bool snd_sof_dsp_update_bits64_unlocked(काष्ठा snd_sof_dev *sdev, u32 bar,
					u32 offset, u64 mask, u64 value);

bool snd_sof_dsp_update_bits(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset,
			     u32 mask, u32 value);

bool snd_sof_dsp_update_bits64(काष्ठा snd_sof_dev *sdev, u32 bar,
			       u32 offset, u64 mask, u64 value);

व्योम snd_sof_dsp_update_bits_क्रमced(काष्ठा snd_sof_dev *sdev, u32 bar,
				    u32 offset, u32 mask, u32 value);

पूर्णांक snd_sof_dsp_रेजिस्टर_poll(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset,
			      u32 mask, u32 target, u32 समयout_ms,
			      u32 पूर्णांकerval_us);

व्योम snd_sof_dsp_panic(काष्ठा snd_sof_dev *sdev, u32 offset);
#पूर्ण_अगर
