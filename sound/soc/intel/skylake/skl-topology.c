<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl-topology.c - Implements Platक्रमm component ALSA controls/widget
 *  handlers.
 *
 *  Copyright (C) 2014-2015 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/firmware.h>
#समावेश <linux/uuid.h>
#समावेश <sound/पूर्णांकel-nhlt.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-topology.h>
#समावेश <uapi/sound/snd_sst_tokens.h>
#समावेश <uapi/sound/skl-tplg-पूर्णांकerface.h>
#समावेश "skl-sst-dsp.h"
#समावेश "skl-sst-ipc.h"
#समावेश "skl-topology.h"
#समावेश "skl.h"
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"

#घोषणा SKL_CH_FIXUP_MASK		(1 << 0)
#घोषणा SKL_RATE_FIXUP_MASK		(1 << 1)
#घोषणा SKL_FMT_FIXUP_MASK		(1 << 2)
#घोषणा SKL_IN_सूची_BIT_MASK		BIT(0)
#घोषणा SKL_PIN_COUNT_MASK		GENMASK(7, 4)

अटल स्थिर पूर्णांक mic_mono_list[] = अणु
0, 1, 2, 3,
पूर्ण;
अटल स्थिर पूर्णांक mic_stereo_list[][SKL_CH_STEREO] = अणु
अणु0, 1पूर्ण, अणु0, 2पूर्ण, अणु0, 3पूर्ण, अणु1, 2पूर्ण, अणु1, 3पूर्ण, अणु2, 3पूर्ण,
पूर्ण;
अटल स्थिर पूर्णांक mic_trio_list[][SKL_CH_TRIO] = अणु
अणु0, 1, 2पूर्ण, अणु0, 1, 3पूर्ण, अणु0, 2, 3पूर्ण, अणु1, 2, 3पूर्ण,
पूर्ण;
अटल स्थिर पूर्णांक mic_quatro_list[][SKL_CH_QUATRO] = अणु
अणु0, 1, 2, 3पूर्ण,
पूर्ण;

#घोषणा CHECK_HW_PARAMS(ch, freq, bps, prm_ch, prm_freq, prm_bps) \
	((ch == prm_ch) && (bps == prm_bps) && (freq == prm_freq))

व्योम skl_tplg_d0i3_get(काष्ठा skl_dev *skl, क्रमागत d0i3_capability caps)
अणु
	काष्ठा skl_d0i3_data *d0i3 =  &skl->d0i3;

	चयन (caps) अणु
	हाल SKL_D0I3_NONE:
		d0i3->non_d0i3++;
		अवरोध;

	हाल SKL_D0I3_STREAMING:
		d0i3->streaming++;
		अवरोध;

	हाल SKL_D0I3_NON_STREAMING:
		d0i3->non_streaming++;
		अवरोध;
	पूर्ण
पूर्ण

व्योम skl_tplg_d0i3_put(काष्ठा skl_dev *skl, क्रमागत d0i3_capability caps)
अणु
	काष्ठा skl_d0i3_data *d0i3 =  &skl->d0i3;

	चयन (caps) अणु
	हाल SKL_D0I3_NONE:
		d0i3->non_d0i3--;
		अवरोध;

	हाल SKL_D0I3_STREAMING:
		d0i3->streaming--;
		अवरोध;

	हाल SKL_D0I3_NON_STREAMING:
		d0i3->non_streaming--;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * SKL DSP driver modelling uses only few DAPM widमाला_लो so क्रम rest we will
 * ignore. This helpers checks अगर the SKL driver handles this widget type
 */
अटल पूर्णांक is_skl_dsp_widget_type(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा device *dev)
अणु
	अगर (w->dapm->dev != dev)
		वापस false;

	चयन (w->id) अणु
	हाल snd_soc_dapm_dai_link:
	हाल snd_soc_dapm_dai_in:
	हाल snd_soc_dapm_aअगर_in:
	हाल snd_soc_dapm_aअगर_out:
	हाल snd_soc_dapm_dai_out:
	हाल snd_soc_dapm_चयन:
	हाल snd_soc_dapm_output:
	हाल snd_soc_dapm_mux:

		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम skl_dump_mconfig(काष्ठा skl_dev *skl, काष्ठा skl_module_cfg *mcfg)
अणु
	काष्ठा skl_module_अगरace *अगरace = &mcfg->module->क्रमmats[0];

	dev_dbg(skl->dev, "Dumping config\n");
	dev_dbg(skl->dev, "Input Format:\n");
	dev_dbg(skl->dev, "channels = %d\n", अगरace->inमाला_दो[0].fmt.channels);
	dev_dbg(skl->dev, "s_freq = %d\n", अगरace->inमाला_दो[0].fmt.s_freq);
	dev_dbg(skl->dev, "ch_cfg = %d\n", अगरace->inमाला_दो[0].fmt.ch_cfg);
	dev_dbg(skl->dev, "valid bit depth = %d\n",
				अगरace->inमाला_दो[0].fmt.valid_bit_depth);
	dev_dbg(skl->dev, "Output Format:\n");
	dev_dbg(skl->dev, "channels = %d\n", अगरace->outमाला_दो[0].fmt.channels);
	dev_dbg(skl->dev, "s_freq = %d\n", अगरace->outमाला_दो[0].fmt.s_freq);
	dev_dbg(skl->dev, "valid bit depth = %d\n",
				अगरace->outमाला_दो[0].fmt.valid_bit_depth);
	dev_dbg(skl->dev, "ch_cfg = %d\n", अगरace->outमाला_दो[0].fmt.ch_cfg);
पूर्ण

अटल व्योम skl_tplg_update_chmap(काष्ठा skl_module_fmt *fmt, पूर्णांक chs)
अणु
	पूर्णांक slot_map = 0xFFFFFFFF;
	पूर्णांक start_slot = 0;
	पूर्णांक i;

	क्रम (i = 0; i < chs; i++) अणु
		/*
		 * For 2 channels with starting slot as 0, slot map will
		 * look like 0xFFFFFF10.
		 */
		slot_map &= (~(0xF << (4 * i)) | (start_slot << (4 * i)));
		start_slot++;
	पूर्ण
	fmt->ch_map = slot_map;
पूर्ण

अटल व्योम skl_tplg_update_params(काष्ठा skl_module_fmt *fmt,
			काष्ठा skl_pipe_params *params, पूर्णांक fixup)
अणु
	अगर (fixup & SKL_RATE_FIXUP_MASK)
		fmt->s_freq = params->s_freq;
	अगर (fixup & SKL_CH_FIXUP_MASK) अणु
		fmt->channels = params->ch;
		skl_tplg_update_chmap(fmt, fmt->channels);
	पूर्ण
	अगर (fixup & SKL_FMT_FIXUP_MASK) अणु
		fmt->valid_bit_depth = skl_get_bit_depth(params->s_fmt);

		/*
		 * 16 bit is 16 bit container whereas 24 bit is in 32 bit
		 * container so update bit depth accordingly
		 */
		चयन (fmt->valid_bit_depth) अणु
		हाल SKL_DEPTH_16BIT:
			fmt->bit_depth = fmt->valid_bit_depth;
			अवरोध;

		शेष:
			fmt->bit_depth = SKL_DEPTH_32BIT;
			अवरोध;
		पूर्ण
	पूर्ण

पूर्ण

/*
 * A pipeline may have modules which impact the pcm parameters, like SRC,
 * channel converter, क्रमmat converter.
 * We need to calculate the output params by applying the 'fixup'
 * Topology will tell driver which type of fixup is to be applied by
 * supplying the fixup mask, so based on that we calculate the output
 *
 * Now In FE the pcm hw_params is source/target क्रमmat. Same is applicable
 * क्रम BE with its hw_params invoked.
 * here based on FE, BE pipeline and direction we calculate the input and
 * outfix and then apply that क्रम a module
 */
अटल व्योम skl_tplg_update_params_fixup(काष्ठा skl_module_cfg *m_cfg,
		काष्ठा skl_pipe_params *params, bool is_fe)
अणु
	पूर्णांक in_fixup, out_fixup;
	काष्ठा skl_module_fmt *in_fmt, *out_fmt;

	/* Fixups will be applied to pin 0 only */
	in_fmt = &m_cfg->module->क्रमmats[0].inमाला_दो[0].fmt;
	out_fmt = &m_cfg->module->क्रमmats[0].outमाला_दो[0].fmt;

	अगर (params->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (is_fe) अणु
			in_fixup = m_cfg->params_fixup;
			out_fixup = (~m_cfg->converter) &
					m_cfg->params_fixup;
		पूर्ण अन्यथा अणु
			out_fixup = m_cfg->params_fixup;
			in_fixup = (~m_cfg->converter) &
					m_cfg->params_fixup;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (is_fe) अणु
			out_fixup = m_cfg->params_fixup;
			in_fixup = (~m_cfg->converter) &
					m_cfg->params_fixup;
		पूर्ण अन्यथा अणु
			in_fixup = m_cfg->params_fixup;
			out_fixup = (~m_cfg->converter) &
					m_cfg->params_fixup;
		पूर्ण
	पूर्ण

	skl_tplg_update_params(in_fmt, params, in_fixup);
	skl_tplg_update_params(out_fmt, params, out_fixup);
पूर्ण

/*
 * A module needs input and output buffers, which are dependent upon pcm
 * params, so once we have calculate params, we need buffer calculation as
 * well.
 */
अटल व्योम skl_tplg_update_buffer_size(काष्ठा skl_dev *skl,
				काष्ठा skl_module_cfg *mcfg)
अणु
	पूर्णांक multiplier = 1;
	काष्ठा skl_module_fmt *in_fmt, *out_fmt;
	काष्ठा skl_module_res *res;

	/* Since fixups is applied to pin 0 only, ibs, obs needs
	 * change क्रम pin 0 only
	 */
	res = &mcfg->module->resources[0];
	in_fmt = &mcfg->module->क्रमmats[0].inमाला_दो[0].fmt;
	out_fmt = &mcfg->module->क्रमmats[0].outमाला_दो[0].fmt;

	अगर (mcfg->m_type == SKL_MODULE_TYPE_SRCINT)
		multiplier = 5;

	res->ibs = DIV_ROUND_UP(in_fmt->s_freq, 1000) *
			in_fmt->channels * (in_fmt->bit_depth >> 3) *
			multiplier;

	res->obs = DIV_ROUND_UP(out_fmt->s_freq, 1000) *
			out_fmt->channels * (out_fmt->bit_depth >> 3) *
			multiplier;
पूर्ण

अटल u8 skl_tplg_be_dev_type(पूर्णांक dev_type)
अणु
	पूर्णांक ret;

	चयन (dev_type) अणु
	हाल SKL_DEVICE_BT:
		ret = NHLT_DEVICE_BT;
		अवरोध;

	हाल SKL_DEVICE_DMIC:
		ret = NHLT_DEVICE_DMIC;
		अवरोध;

	हाल SKL_DEVICE_I2S:
		ret = NHLT_DEVICE_I2S;
		अवरोध;

	शेष:
		ret = NHLT_DEVICE_INVALID;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक skl_tplg_update_be_blob(काष्ठा snd_soc_dapm_widget *w,
						काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_module_cfg *m_cfg = w->priv;
	पूर्णांक link_type, dir;
	u32 ch, s_freq, s_fmt;
	काष्ठा nhlt_specअगरic_cfg *cfg;
	u8 dev_type = skl_tplg_be_dev_type(m_cfg->dev_type);
	पूर्णांक fmt_idx = m_cfg->fmt_idx;
	काष्ठा skl_module_अगरace *m_अगरace = &m_cfg->module->क्रमmats[fmt_idx];

	/* check अगर we alपढ़ोy have blob */
	अगर (m_cfg->क्रमmats_config.caps_size > 0)
		वापस 0;

	dev_dbg(skl->dev, "Applying default cfg blob\n");
	चयन (m_cfg->dev_type) अणु
	हाल SKL_DEVICE_DMIC:
		link_type = NHLT_LINK_DMIC;
		dir = SNDRV_PCM_STREAM_CAPTURE;
		s_freq = m_अगरace->inमाला_दो[0].fmt.s_freq;
		s_fmt = m_अगरace->inमाला_दो[0].fmt.bit_depth;
		ch = m_अगरace->inमाला_दो[0].fmt.channels;
		अवरोध;

	हाल SKL_DEVICE_I2S:
		link_type = NHLT_LINK_SSP;
		अगर (m_cfg->hw_conn_type == SKL_CONN_SOURCE) अणु
			dir = SNDRV_PCM_STREAM_PLAYBACK;
			s_freq = m_अगरace->outमाला_दो[0].fmt.s_freq;
			s_fmt = m_अगरace->outमाला_दो[0].fmt.bit_depth;
			ch = m_अगरace->outमाला_दो[0].fmt.channels;
		पूर्ण अन्यथा अणु
			dir = SNDRV_PCM_STREAM_CAPTURE;
			s_freq = m_अगरace->inमाला_दो[0].fmt.s_freq;
			s_fmt = m_अगरace->inमाला_दो[0].fmt.bit_depth;
			ch = m_अगरace->inमाला_दो[0].fmt.channels;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* update the blob based on भव bus_id and शेष params */
	cfg = skl_get_ep_blob(skl, m_cfg->vbus_id, link_type,
					s_fmt, ch, s_freq, dir, dev_type);
	अगर (cfg) अणु
		m_cfg->क्रमmats_config.caps_size = cfg->size;
		m_cfg->क्रमmats_config.caps = (u32 *) &cfg->caps;
	पूर्ण अन्यथा अणु
		dev_err(skl->dev, "Blob NULL for id %x type %d dirn %d\n",
					m_cfg->vbus_id, link_type, dir);
		dev_err(skl->dev, "PCM: ch %d, freq %d, fmt %d\n",
					ch, s_freq, s_fmt);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम skl_tplg_update_module_params(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_module_cfg *m_cfg = w->priv;
	काष्ठा skl_pipe_params *params = m_cfg->pipe->p_params;
	पूर्णांक p_conn_type = m_cfg->pipe->conn_type;
	bool is_fe;

	अगर (!m_cfg->params_fixup)
		वापस;

	dev_dbg(skl->dev, "Mconfig for widget=%s BEFORE updation\n",
				w->name);

	skl_dump_mconfig(skl, m_cfg);

	अगर (p_conn_type == SKL_PIPE_CONN_TYPE_FE)
		is_fe = true;
	अन्यथा
		is_fe = false;

	skl_tplg_update_params_fixup(m_cfg, params, is_fe);
	skl_tplg_update_buffer_size(skl, m_cfg);

	dev_dbg(skl->dev, "Mconfig for widget=%s AFTER updation\n",
				w->name);

	skl_dump_mconfig(skl, m_cfg);
पूर्ण

/*
 * some modules can have multiple params set from user control and
 * need to be set after module is initialized. If set_param flag is
 * set module params will be करोne after module is initialised.
 */
अटल पूर्णांक skl_tplg_set_module_params(काष्ठा snd_soc_dapm_widget *w,
						काष्ठा skl_dev *skl)
अणु
	पूर्णांक i, ret;
	काष्ठा skl_module_cfg *mconfig = w->priv;
	स्थिर काष्ठा snd_kcontrol_new *k;
	काष्ठा soc_bytes_ext *sb;
	काष्ठा skl_algo_data *bc;
	काष्ठा skl_specअगरic_cfg *sp_cfg;

	अगर (mconfig->क्रमmats_config.caps_size > 0 &&
		mconfig->क्रमmats_config.set_params == SKL_PARAM_SET) अणु
		sp_cfg = &mconfig->क्रमmats_config;
		ret = skl_set_module_params(skl, sp_cfg->caps,
					sp_cfg->caps_size,
					sp_cfg->param_id, mconfig);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		k = &w->kcontrol_news[i];
		अगर (k->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
			sb = (व्योम *) k->निजी_value;
			bc = (काष्ठा skl_algo_data *)sb->करोbj.निजी;

			अगर (bc->set_params == SKL_PARAM_SET) अणु
				ret = skl_set_module_params(skl,
						(u32 *)bc->params, bc->size,
						bc->param_id, mconfig);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * some module param can set from user control and this is required as
 * when module is initailzed. अगर module param is required in init it is
 * identअगरed by set_param flag. अगर set_param flag is not set, then this
 * parameter needs to set as part of module init.
 */
अटल पूर्णांक skl_tplg_set_module_init_data(काष्ठा snd_soc_dapm_widget *w)
अणु
	स्थिर काष्ठा snd_kcontrol_new *k;
	काष्ठा soc_bytes_ext *sb;
	काष्ठा skl_algo_data *bc;
	काष्ठा skl_module_cfg *mconfig = w->priv;
	पूर्णांक i;

	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		k = &w->kcontrol_news[i];
		अगर (k->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
			sb = (काष्ठा soc_bytes_ext *)k->निजी_value;
			bc = (काष्ठा skl_algo_data *)sb->करोbj.निजी;

			अगर (bc->set_params != SKL_PARAM_INIT)
				जारी;

			mconfig->क्रमmats_config.caps = (u32 *)bc->params;
			mconfig->क्रमmats_config.caps_size = bc->size;

			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_module_prepare(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe,
		काष्ठा snd_soc_dapm_widget *w, काष्ठा skl_module_cfg *mcfg)
अणु
	चयन (mcfg->dev_type) अणु
	हाल SKL_DEVICE_HDAHOST:
		वापस skl_pcm_host_dma_prepare(skl->dev, pipe->p_params);

	हाल SKL_DEVICE_HDALINK:
		वापस skl_pcm_link_dma_prepare(skl->dev, pipe->p_params);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Inside a pipe instance, we can have various modules. These modules need
 * to instantiated in DSP by invoking INIT_MODULE IPC, which is achieved by
 * skl_init_module() routine, so invoke that क्रम all modules in a pipeline
 */
अटल पूर्णांक
skl_tplg_init_pipe_modules(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	काष्ठा skl_pipe_module *w_module;
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा skl_module_cfg *mconfig;
	u8 cfg_idx;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(w_module, &pipe->w_list, node) अणु
		guid_t *uuid_mod;
		w = w_module->w;
		mconfig = w->priv;

		/* check अगर module ids are populated */
		अगर (mconfig->id.module_id < 0) अणु
			dev_err(skl->dev,
					"module %pUL id not populated\n",
					(guid_t *)mconfig->guid);
			वापस -EIO;
		पूर्ण

		cfg_idx = mconfig->pipe->cur_config_idx;
		mconfig->fmt_idx = mconfig->mod_cfg[cfg_idx].fmt_idx;
		mconfig->res_idx = mconfig->mod_cfg[cfg_idx].res_idx;

		अगर (mconfig->module->loadable && skl->dsp->fw_ops.load_mod) अणु
			ret = skl->dsp->fw_ops.load_mod(skl->dsp,
				mconfig->id.module_id, mconfig->guid);
			अगर (ret < 0)
				वापस ret;

			mconfig->m_state = SKL_MODULE_LOADED;
		पूर्ण

		/* prepare the DMA अगर the module is gateway cpr */
		ret = skl_tplg_module_prepare(skl, pipe, w, mconfig);
		अगर (ret < 0)
			वापस ret;

		/* update blob अगर blob is null क्रम be with शेष value */
		skl_tplg_update_be_blob(w, skl);

		/*
		 * apply fix/conversion to module params based on
		 * FE/BE params
		 */
		skl_tplg_update_module_params(w, skl);
		uuid_mod = (guid_t *)mconfig->guid;
		mconfig->id.pvt_id = skl_get_pvt_id(skl, uuid_mod,
						mconfig->id.instance_id);
		अगर (mconfig->id.pvt_id < 0)
			वापस ret;
		skl_tplg_set_module_init_data(w);

		ret = skl_dsp_get_core(skl->dsp, mconfig->core_id);
		अगर (ret < 0) अणु
			dev_err(skl->dev, "Failed to wake up core %d ret=%d\n",
						mconfig->core_id, ret);
			वापस ret;
		पूर्ण

		ret = skl_init_module(skl, mconfig);
		अगर (ret < 0) अणु
			skl_put_pvt_id(skl, uuid_mod, &mconfig->id.pvt_id);
			जाओ err;
		पूर्ण

		ret = skl_tplg_set_module_params(w, skl);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	skl_dsp_put_core(skl->dsp, mconfig->core_id);
	वापस ret;
पूर्ण

अटल पूर्णांक skl_tplg_unload_pipe_modules(काष्ठा skl_dev *skl,
	 काष्ठा skl_pipe *pipe)
अणु
	पूर्णांक ret = 0;
	काष्ठा skl_pipe_module *w_module;
	काष्ठा skl_module_cfg *mconfig;

	list_क्रम_each_entry(w_module, &pipe->w_list, node) अणु
		guid_t *uuid_mod;
		mconfig  = w_module->w->priv;
		uuid_mod = (guid_t *)mconfig->guid;

		अगर (mconfig->module->loadable && skl->dsp->fw_ops.unload_mod &&
			mconfig->m_state > SKL_MODULE_UNINIT) अणु
			ret = skl->dsp->fw_ops.unload_mod(skl->dsp,
						mconfig->id.module_id);
			अगर (ret < 0)
				वापस -EIO;
		पूर्ण
		skl_put_pvt_id(skl, uuid_mod, &mconfig->id.pvt_id);

		ret = skl_dsp_put_core(skl->dsp, mconfig->core_id);
		अगर (ret < 0) अणु
			/* करोn't वापस; जारी with other modules */
			dev_err(skl->dev, "Failed to sleep core %d ret=%d\n",
				mconfig->core_id, ret);
		पूर्ण
	पूर्ण

	/* no modules to unload in this path, so वापस */
	वापस ret;
पूर्ण

अटल bool skl_tplg_is_multi_fmt(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	काष्ठा skl_pipe_fmt *cur_fmt;
	काष्ठा skl_pipe_fmt *next_fmt;
	पूर्णांक i;

	अगर (pipe->nr_cfgs <= 1)
		वापस false;

	अगर (pipe->conn_type != SKL_PIPE_CONN_TYPE_FE)
		वापस true;

	क्रम (i = 0; i < pipe->nr_cfgs - 1; i++) अणु
		अगर (pipe->direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
			cur_fmt = &pipe->configs[i].out_fmt;
			next_fmt = &pipe->configs[i + 1].out_fmt;
		पूर्ण अन्यथा अणु
			cur_fmt = &pipe->configs[i].in_fmt;
			next_fmt = &pipe->configs[i + 1].in_fmt;
		पूर्ण

		अगर (!CHECK_HW_PARAMS(cur_fmt->channels, cur_fmt->freq,
				     cur_fmt->bps,
				     next_fmt->channels,
				     next_fmt->freq,
				     next_fmt->bps))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Here, we select pipe क्रमmat based on the pipe type and pipe
 * direction to determine the current config index क्रम the pipeline.
 * The config index is then used to select proper module resources.
 * Intermediate pipes currently have a fixed क्रमmat hence we select the
 * 0th configuratation by शेष क्रम such pipes.
 */
अटल पूर्णांक
skl_tplg_get_pipe_config(काष्ठा skl_dev *skl, काष्ठा skl_module_cfg *mconfig)
अणु
	काष्ठा skl_pipe *pipe = mconfig->pipe;
	काष्ठा skl_pipe_params *params = pipe->p_params;
	काष्ठा skl_path_config *pconfig = &pipe->configs[0];
	काष्ठा skl_pipe_fmt *fmt = शून्य;
	bool in_fmt = false;
	पूर्णांक i;

	अगर (pipe->nr_cfgs == 0) अणु
		pipe->cur_config_idx = 0;
		वापस 0;
	पूर्ण

	अगर (skl_tplg_is_multi_fmt(skl, pipe)) अणु
		pipe->cur_config_idx = pipe->pipe_config_idx;
		pipe->memory_pages = pconfig->mem_pages;
		dev_dbg(skl->dev, "found pipe config idx:%d\n",
			pipe->cur_config_idx);
		वापस 0;
	पूर्ण

	अगर (pipe->conn_type == SKL_PIPE_CONN_TYPE_NONE) अणु
		dev_dbg(skl->dev, "No conn_type detected, take 0th config\n");
		pipe->cur_config_idx = 0;
		pipe->memory_pages = pconfig->mem_pages;

		वापस 0;
	पूर्ण

	अगर ((pipe->conn_type == SKL_PIPE_CONN_TYPE_FE &&
	     pipe->direction == SNDRV_PCM_STREAM_PLAYBACK) ||
	     (pipe->conn_type == SKL_PIPE_CONN_TYPE_BE &&
	     pipe->direction == SNDRV_PCM_STREAM_CAPTURE))
		in_fmt = true;

	क्रम (i = 0; i < pipe->nr_cfgs; i++) अणु
		pconfig = &pipe->configs[i];
		अगर (in_fmt)
			fmt = &pconfig->in_fmt;
		अन्यथा
			fmt = &pconfig->out_fmt;

		अगर (CHECK_HW_PARAMS(params->ch, params->s_freq, params->s_fmt,
				    fmt->channels, fmt->freq, fmt->bps)) अणु
			pipe->cur_config_idx = i;
			pipe->memory_pages = pconfig->mem_pages;
			dev_dbg(skl->dev, "Using pipe config: %d\n", i);

			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(skl->dev, "Invalid pipe config: %d %d %d for pipe: %d\n",
		params->ch, params->s_freq, params->s_fmt, pipe->ppl_id);
	वापस -EINVAL;
पूर्ण

/*
 * Mixer module represents a pipeline. So in the Pre-PMU event of mixer we
 * need create the pipeline. So we करो following:
 *   - Create the pipeline
 *   - Initialize the modules in pipeline
 *   - finally bind all modules together
 */
अटल पूर्णांक skl_tplg_mixer_dapm_pre_pmu_event(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	पूर्णांक ret;
	काष्ठा skl_module_cfg *mconfig = w->priv;
	काष्ठा skl_pipe_module *w_module;
	काष्ठा skl_pipe *s_pipe = mconfig->pipe;
	काष्ठा skl_module_cfg *src_module = शून्य, *dst_module, *module;
	काष्ठा skl_module_deferred_bind *modules;

	ret = skl_tplg_get_pipe_config(skl, mconfig);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Create a list of modules क्रम pipe.
	 * This list contains modules from source to sink
	 */
	ret = skl_create_pipeline(skl, mconfig->pipe);
	अगर (ret < 0)
		वापस ret;

	/* Init all pipe modules from source to sink */
	ret = skl_tplg_init_pipe_modules(skl, s_pipe);
	अगर (ret < 0)
		वापस ret;

	/* Bind modules from source to sink */
	list_क्रम_each_entry(w_module, &s_pipe->w_list, node) अणु
		dst_module = w_module->w->priv;

		अगर (src_module == शून्य) अणु
			src_module = dst_module;
			जारी;
		पूर्ण

		ret = skl_bind_modules(skl, src_module, dst_module);
		अगर (ret < 0)
			वापस ret;

		src_module = dst_module;
	पूर्ण

	/*
	 * When the destination module is initialized, check क्रम these modules
	 * in deferred bind list. If found, bind them.
	 */
	list_क्रम_each_entry(w_module, &s_pipe->w_list, node) अणु
		अगर (list_empty(&skl->bind_list))
			अवरोध;

		list_क्रम_each_entry(modules, &skl->bind_list, node) अणु
			module = w_module->w->priv;
			अगर (modules->dst == module)
				skl_bind_modules(skl, modules->src,
							modules->dst);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_fill_sink_instance_id(काष्ठा skl_dev *skl, u32 *params,
				पूर्णांक size, काष्ठा skl_module_cfg *mcfg)
अणु
	पूर्णांक i, pvt_id;

	अगर (mcfg->m_type == SKL_MODULE_TYPE_KPB) अणु
		काष्ठा skl_kpb_params *kpb_params =
				(काष्ठा skl_kpb_params *)params;
		काष्ठा skl_mod_inst_map *inst = kpb_params->u.map;

		क्रम (i = 0; i < kpb_params->num_modules; i++) अणु
			pvt_id = skl_get_pvt_instance_id_map(skl, inst->mod_id,
								inst->inst_id);
			अगर (pvt_id < 0)
				वापस -EINVAL;

			inst->inst_id = pvt_id;
			inst++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
/*
 * Some modules require params to be set after the module is bound to
 * all pins connected.
 *
 * The module provider initializes set_param flag क्रम such modules and we
 * send params after binding
 */
अटल पूर्णांक skl_tplg_set_module_bind_params(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा skl_module_cfg *mcfg, काष्ठा skl_dev *skl)
अणु
	पूर्णांक i, ret;
	काष्ठा skl_module_cfg *mconfig = w->priv;
	स्थिर काष्ठा snd_kcontrol_new *k;
	काष्ठा soc_bytes_ext *sb;
	काष्ठा skl_algo_data *bc;
	काष्ठा skl_specअगरic_cfg *sp_cfg;
	u32 *params;

	/*
	 * check all out/in pins are in bind state.
	 * अगर so set the module param
	 */
	क्रम (i = 0; i < mcfg->module->max_output_pins; i++) अणु
		अगर (mcfg->m_out_pin[i].pin_state != SKL_PIN_BIND_DONE)
			वापस 0;
	पूर्ण

	क्रम (i = 0; i < mcfg->module->max_input_pins; i++) अणु
		अगर (mcfg->m_in_pin[i].pin_state != SKL_PIN_BIND_DONE)
			वापस 0;
	पूर्ण

	अगर (mconfig->क्रमmats_config.caps_size > 0 &&
		mconfig->क्रमmats_config.set_params == SKL_PARAM_BIND) अणु
		sp_cfg = &mconfig->क्रमmats_config;
		ret = skl_set_module_params(skl, sp_cfg->caps,
					sp_cfg->caps_size,
					sp_cfg->param_id, mconfig);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		k = &w->kcontrol_news[i];
		अगर (k->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
			sb = (व्योम *) k->निजी_value;
			bc = (काष्ठा skl_algo_data *)sb->करोbj.निजी;

			अगर (bc->set_params == SKL_PARAM_BIND) अणु
				params = kmemdup(bc->params, bc->max, GFP_KERNEL);
				अगर (!params)
					वापस -ENOMEM;

				skl_fill_sink_instance_id(skl, params, bc->max,
								mconfig);

				ret = skl_set_module_params(skl, params,
						bc->max, bc->param_id, mconfig);
				kमुक्त(params);

				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_get_module_id(काष्ठा skl_dev *skl, guid_t *uuid)
अणु
	काष्ठा uuid_module *module;

	list_क्रम_each_entry(module, &skl->uuid_list, list) अणु
		अगर (guid_equal(uuid, &module->uuid))
			वापस module->id;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक skl_tplg_find_moduleid_from_uuid(काष्ठा skl_dev *skl,
					स्थिर काष्ठा snd_kcontrol_new *k)
अणु
	काष्ठा soc_bytes_ext *sb = (व्योम *) k->निजी_value;
	काष्ठा skl_algo_data *bc = (काष्ठा skl_algo_data *)sb->करोbj.निजी;
	काष्ठा skl_kpb_params *uuid_params, *params;
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	पूर्णांक i, size, module_id;

	अगर (bc->set_params == SKL_PARAM_BIND && bc->max) अणु
		uuid_params = (काष्ठा skl_kpb_params *)bc->params;
		size = काष्ठा_size(params, u.map, uuid_params->num_modules);

		params = devm_kzalloc(bus->dev, size, GFP_KERNEL);
		अगर (!params)
			वापस -ENOMEM;

		params->num_modules = uuid_params->num_modules;

		क्रम (i = 0; i < uuid_params->num_modules; i++) अणु
			module_id = skl_get_module_id(skl,
				&uuid_params->u.map_uuid[i].mod_uuid);
			अगर (module_id < 0) अणु
				devm_kमुक्त(bus->dev, params);
				वापस -EINVAL;
			पूर्ण

			params->u.map[i].mod_id = module_id;
			params->u.map[i].inst_id =
				uuid_params->u.map_uuid[i].inst_id;
		पूर्ण

		devm_kमुक्त(bus->dev, bc->params);
		bc->params = (अक्षर *)params;
		bc->max = size;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Retrieve the module id from UUID mentioned in the
 * post bind params
 */
व्योम skl_tplg_add_moduleid_in_bind_params(काष्ठा skl_dev *skl,
				काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा skl_module_cfg *mconfig = w->priv;
	पूर्णांक i;

	/*
	 * Post bind params are used क्रम only क्रम KPB
	 * to set copier instances to drain the data
	 * in fast mode
	 */
	अगर (mconfig->m_type != SKL_MODULE_TYPE_KPB)
		वापस;

	क्रम (i = 0; i < w->num_kcontrols; i++)
		अगर ((w->kcontrol_news[i].access &
			SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) &&
			(skl_tplg_find_moduleid_from_uuid(skl,
			&w->kcontrol_news[i]) < 0))
			dev_err(skl->dev,
				"%s: invalid kpb post bind params\n",
				__func__);
पूर्ण

अटल पूर्णांक skl_tplg_module_add_deferred_bind(काष्ठा skl_dev *skl,
	काष्ठा skl_module_cfg *src, काष्ठा skl_module_cfg *dst)
अणु
	काष्ठा skl_module_deferred_bind *m_list, *modules;
	पूर्णांक i;

	/* only supported क्रम module with अटल pin connection */
	क्रम (i = 0; i < dst->module->max_input_pins; i++) अणु
		काष्ठा skl_module_pin *pin = &dst->m_in_pin[i];

		अगर (pin->is_dynamic)
			जारी;

		अगर ((pin->id.module_id  == src->id.module_id) &&
			(pin->id.instance_id  == src->id.instance_id)) अणु

			अगर (!list_empty(&skl->bind_list)) अणु
				list_क्रम_each_entry(modules, &skl->bind_list, node) अणु
					अगर (modules->src == src && modules->dst == dst)
						वापस 0;
				पूर्ण
			पूर्ण

			m_list = kzalloc(माप(*m_list), GFP_KERNEL);
			अगर (!m_list)
				वापस -ENOMEM;

			m_list->src = src;
			m_list->dst = dst;

			list_add(&m_list->node, &skl->bind_list);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_bind_sinks(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा skl_dev *skl,
				काष्ठा snd_soc_dapm_widget *src_w,
				काष्ठा skl_module_cfg *src_mconfig)
अणु
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा snd_soc_dapm_widget *sink = शून्य, *next_sink = शून्य;
	काष्ठा skl_module_cfg *sink_mconfig;
	पूर्णांक ret;

	snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
		अगर (!p->connect)
			जारी;

		dev_dbg(skl->dev,
			"%s: src widget=%s\n", __func__, w->name);
		dev_dbg(skl->dev,
			"%s: sink widget=%s\n", __func__, p->sink->name);

		next_sink = p->sink;

		अगर (!is_skl_dsp_widget_type(p->sink, skl->dev))
			वापस skl_tplg_bind_sinks(p->sink, skl, src_w, src_mconfig);

		/*
		 * here we will check widमाला_लो in sink pipelines, so that
		 * can be any widमाला_लो type and we are only पूर्णांकerested अगर
		 * they are ones used क्रम SKL so check that first
		 */
		अगर ((p->sink->priv != शून्य) &&
				is_skl_dsp_widget_type(p->sink, skl->dev)) अणु

			sink = p->sink;
			sink_mconfig = sink->priv;

			/*
			 * Modules other than PGA leaf can be connected
			 * directly or via चयन to a module in another
			 * pipeline. EX: reference path
			 * when the path is enabled, the dst module that needs
			 * to be bound may not be initialized. अगर the module is
			 * not initialized, add these modules in the deferred
			 * bind list and when the dst module is initialised,
			 * bind this module to the dst_module in deferred list.
			 */
			अगर (((src_mconfig->m_state == SKL_MODULE_INIT_DONE)
				&& (sink_mconfig->m_state == SKL_MODULE_UNINIT))) अणु

				ret = skl_tplg_module_add_deferred_bind(skl,
						src_mconfig, sink_mconfig);

				अगर (ret < 0)
					वापस ret;

			पूर्ण


			अगर (src_mconfig->m_state == SKL_MODULE_UNINIT ||
				sink_mconfig->m_state == SKL_MODULE_UNINIT)
				जारी;

			/* Bind source to sink, mixin is always source */
			ret = skl_bind_modules(skl, src_mconfig, sink_mconfig);
			अगर (ret)
				वापस ret;

			/* set module params after bind */
			skl_tplg_set_module_bind_params(src_w,
					src_mconfig, skl);
			skl_tplg_set_module_bind_params(sink,
					sink_mconfig, skl);

			/* Start sinks pipe first */
			अगर (sink_mconfig->pipe->state != SKL_PIPE_STARTED) अणु
				अगर (sink_mconfig->pipe->conn_type !=
							SKL_PIPE_CONN_TYPE_FE)
					ret = skl_run_pipe(skl,
							sink_mconfig->pipe);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!sink && next_sink)
		वापस skl_tplg_bind_sinks(next_sink, skl, src_w, src_mconfig);

	वापस 0;
पूर्ण

/*
 * A PGA represents a module in a pipeline. So in the Pre-PMU event of PGA
 * we need to करो following:
 *   - Bind to sink pipeline
 *      Since the sink pipes can be running and we करोn't get mixer event on
 *      connect क्रम alपढ़ोy running mixer, we need to find the sink pipes
 *      here and bind to them. This way dynamic connect works.
 *   - Start sink pipeline, अगर not running
 *   - Then run current pipe
 */
अटल पूर्णांक skl_tplg_pga_dapm_pre_pmu_event(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_module_cfg *src_mconfig;
	पूर्णांक ret = 0;

	src_mconfig = w->priv;

	/*
	 * find which sink it is connected to, bind with the sink,
	 * अगर sink is not started, start sink pipe first, then start
	 * this pipe
	 */
	ret = skl_tplg_bind_sinks(w, skl, w, src_mconfig);
	अगर (ret)
		वापस ret;

	/* Start source pipe last after starting all sinks */
	अगर (src_mconfig->pipe->conn_type != SKL_PIPE_CONN_TYPE_FE)
		वापस skl_run_pipe(skl, src_mconfig->pipe);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dapm_widget *skl_get_src_dsp_widget(
		काष्ठा snd_soc_dapm_widget *w, काष्ठा skl_dev *skl)
अणु
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा snd_soc_dapm_widget *src_w = शून्य;

	snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
		src_w = p->source;
		अगर (!p->connect)
			जारी;

		dev_dbg(skl->dev, "sink widget=%s\n", w->name);
		dev_dbg(skl->dev, "src widget=%s\n", p->source->name);

		/*
		 * here we will check widमाला_लो in sink pipelines, so that can
		 * be any widमाला_लो type and we are only पूर्णांकerested अगर they are
		 * ones used क्रम SKL so check that first
		 */
		अगर ((p->source->priv != शून्य) &&
				is_skl_dsp_widget_type(p->source, skl->dev)) अणु
			वापस p->source;
		पूर्ण
	पूर्ण

	अगर (src_w != शून्य)
		वापस skl_get_src_dsp_widget(src_w, skl);

	वापस शून्य;
पूर्ण

/*
 * in the Post-PMU event of mixer we need to करो following:
 *   - Check अगर this pipe is running
 *   - अगर not, then
 *	- bind this pipeline to its source pipeline
 *	  अगर source pipe is alपढ़ोy running, this means it is a dynamic
 *	  connection and we need to bind only to that pipe
 *	- start this pipeline
 */
अटल पूर्णांक skl_tplg_mixer_dapm_post_pmu_event(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_dapm_widget *source, *sink;
	काष्ठा skl_module_cfg *src_mconfig, *sink_mconfig;
	पूर्णांक src_pipe_started = 0;

	sink = w;
	sink_mconfig = sink->priv;

	/*
	 * If source pipe is alपढ़ोy started, that means source is driving
	 * one more sink beक्रमe this sink got connected, Since source is
	 * started, bind this sink to source and start this pipe.
	 */
	source = skl_get_src_dsp_widget(w, skl);
	अगर (source != शून्य) अणु
		src_mconfig = source->priv;
		sink_mconfig = sink->priv;
		src_pipe_started = 1;

		/*
		 * check pipe state, then no need to bind or start the
		 * pipe
		 */
		अगर (src_mconfig->pipe->state != SKL_PIPE_STARTED)
			src_pipe_started = 0;
	पूर्ण

	अगर (src_pipe_started) अणु
		ret = skl_bind_modules(skl, src_mconfig, sink_mconfig);
		अगर (ret)
			वापस ret;

		/* set module params after bind */
		skl_tplg_set_module_bind_params(source, src_mconfig, skl);
		skl_tplg_set_module_bind_params(sink, sink_mconfig, skl);

		अगर (sink_mconfig->pipe->conn_type != SKL_PIPE_CONN_TYPE_FE)
			ret = skl_run_pipe(skl, sink_mconfig->pipe);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * in the Pre-PMD event of mixer we need to करो following:
 *   - Stop the pipe
 *   - find the source connections and हटाओ that from dapm_path_list
 *   - unbind with source pipelines अगर still connected
 */
अटल पूर्णांक skl_tplg_mixer_dapm_pre_pmd_event(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_module_cfg *src_mconfig, *sink_mconfig;
	पूर्णांक ret = 0, i;

	sink_mconfig = w->priv;

	/* Stop the pipe */
	ret = skl_stop_pipe(skl, sink_mconfig->pipe);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < sink_mconfig->module->max_input_pins; i++) अणु
		अगर (sink_mconfig->m_in_pin[i].pin_state == SKL_PIN_BIND_DONE) अणु
			src_mconfig = sink_mconfig->m_in_pin[i].tgt_mcfg;
			अगर (!src_mconfig)
				जारी;

			ret = skl_unbind_modules(skl,
						src_mconfig, sink_mconfig);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * in the Post-PMD event of mixer we need to करो following:
 *   - Unbind the modules within the pipeline
 *   - Delete the pipeline (modules are not required to be explicitly
 *     deleted, pipeline delete is enough here
 */
अटल पूर्णांक skl_tplg_mixer_dapm_post_pmd_event(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_module_cfg *mconfig = w->priv;
	काष्ठा skl_pipe_module *w_module;
	काष्ठा skl_module_cfg *src_module = शून्य, *dst_module;
	काष्ठा skl_pipe *s_pipe = mconfig->pipe;
	काष्ठा skl_module_deferred_bind *modules, *पंचांगp;

	अगर (s_pipe->state == SKL_PIPE_INVALID)
		वापस -EINVAL;

	list_क्रम_each_entry(w_module, &s_pipe->w_list, node) अणु
		अगर (list_empty(&skl->bind_list))
			अवरोध;

		src_module = w_module->w->priv;

		list_क्रम_each_entry_safe(modules, पंचांगp, &skl->bind_list, node) अणु
			/*
			 * When the destination module is deleted, Unbind the
			 * modules from deferred bind list.
			 */
			अगर (modules->dst == src_module) अणु
				skl_unbind_modules(skl, modules->src,
						modules->dst);
			पूर्ण

			/*
			 * When the source module is deleted, हटाओ this entry
			 * from the deferred bind list.
			 */
			अगर (modules->src == src_module) अणु
				list_del(&modules->node);
				modules->src = शून्य;
				modules->dst = शून्य;
				kमुक्त(modules);
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(w_module, &s_pipe->w_list, node) अणु
		dst_module = w_module->w->priv;

		अगर (src_module == शून्य) अणु
			src_module = dst_module;
			जारी;
		पूर्ण

		skl_unbind_modules(skl, src_module, dst_module);
		src_module = dst_module;
	पूर्ण

	skl_delete_pipe(skl, mconfig->pipe);

	list_क्रम_each_entry(w_module, &s_pipe->w_list, node) अणु
		src_module = w_module->w->priv;
		src_module->m_state = SKL_MODULE_UNINIT;
	पूर्ण

	वापस skl_tplg_unload_pipe_modules(skl, s_pipe);
पूर्ण

/*
 * in the Post-PMD event of PGA we need to करो following:
 *   - Stop the pipeline
 *   - In source pipe is connected, unbind with source pipelines
 */
अटल पूर्णांक skl_tplg_pga_dapm_post_pmd_event(काष्ठा snd_soc_dapm_widget *w,
							काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_module_cfg *src_mconfig, *sink_mconfig;
	पूर्णांक ret = 0, i;

	src_mconfig = w->priv;

	/* Stop the pipe since this is a mixin module */
	ret = skl_stop_pipe(skl, src_mconfig->pipe);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < src_mconfig->module->max_output_pins; i++) अणु
		अगर (src_mconfig->m_out_pin[i].pin_state == SKL_PIN_BIND_DONE) अणु
			sink_mconfig = src_mconfig->m_out_pin[i].tgt_mcfg;
			अगर (!sink_mconfig)
				जारी;
			/*
			 * This is a connecter and अगर path is found that means
			 * unbind between source and sink has not happened yet
			 */
			ret = skl_unbind_modules(skl, src_mconfig,
							sink_mconfig);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * In modelling, we assume there will be ONLY one mixer in a pipeline. If a
 * second one is required that is created as another pipe entity.
 * The mixer is responsible क्रम pipe management and represent a pipeline
 * instance
 */
अटल पूर्णांक skl_tplg_mixer_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा skl_dev *skl = get_skl_ctx(dapm->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस skl_tplg_mixer_dapm_pre_pmu_event(w, skl);

	हाल SND_SOC_DAPM_POST_PMU:
		वापस skl_tplg_mixer_dapm_post_pmu_event(w, skl);

	हाल SND_SOC_DAPM_PRE_PMD:
		वापस skl_tplg_mixer_dapm_pre_pmd_event(w, skl);

	हाल SND_SOC_DAPM_POST_PMD:
		वापस skl_tplg_mixer_dapm_post_pmd_event(w, skl);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * In modelling, we assumed rest of the modules in pipeline are PGA. But we
 * are पूर्णांकerested in last PGA (leaf PGA) in a pipeline to disconnect with
 * the sink when it is running (two FE to one BE or one FE to two BE)
 * scenarios
 */
अटल पूर्णांक skl_tplg_pga_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)

अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा skl_dev *skl = get_skl_ctx(dapm->dev);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस skl_tplg_pga_dapm_pre_pmu_event(w, skl);

	हाल SND_SOC_DAPM_POST_PMD:
		वापस skl_tplg_pga_dapm_post_pmd_event(w, skl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_multi_config_set_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol,
					 bool is_set)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा hdac_bus *bus = snd_soc_component_get_drvdata(component);
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा skl_pipeline *ppl;
	काष्ठा skl_pipe *pipe = शून्य;
	काष्ठा soc_क्रमागत *ec = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	u32 *pipe_id;

	अगर (!ec)
		वापस -EINVAL;

	अगर (is_set && ucontrol->value.क्रमागतerated.item[0] > ec->items)
		वापस -EINVAL;

	pipe_id = ec->करोbj.निजी;

	list_क्रम_each_entry(ppl, &skl->ppl_list, node) अणु
		अगर (ppl->pipe->ppl_id == *pipe_id) अणु
			pipe = ppl->pipe;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!pipe)
		वापस -EIO;

	अगर (is_set)
		pipe->pipe_config_idx = ucontrol->value.क्रमागतerated.item[0];
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0]  =  pipe->pipe_config_idx;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_multi_config_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस skl_tplg_multi_config_set_get(kcontrol, ucontrol, false);
पूर्ण

अटल पूर्णांक skl_tplg_multi_config_set(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस skl_tplg_multi_config_set_get(kcontrol, ucontrol, true);
पूर्ण

अटल पूर्णांक skl_tplg_multi_config_get_dmic(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस skl_tplg_multi_config_set_get(kcontrol, ucontrol, false);
पूर्ण

अटल पूर्णांक skl_tplg_multi_config_set_dmic(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस skl_tplg_multi_config_set_get(kcontrol, ucontrol, true);
पूर्ण

अटल पूर्णांक skl_tplg_tlv_control_get(काष्ठा snd_kcontrol *kcontrol,
			अचिन्हित पूर्णांक __user *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा soc_bytes_ext *sb =
			(काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा skl_algo_data *bc = (काष्ठा skl_algo_data *)sb->करोbj.निजी;
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा skl_module_cfg *mconfig = w->priv;
	काष्ठा skl_dev *skl = get_skl_ctx(w->dapm->dev);

	अगर (w->घातer)
		skl_get_module_params(skl, (u32 *)bc->params,
				      bc->size, bc->param_id, mconfig);

	/* decrement size क्रम TLV header */
	size -= 2 * माप(u32);

	/* check size as we करोn't want to send kernel data */
	अगर (size > bc->max)
		size = bc->max;

	अगर (bc->params) अणु
		अगर (copy_to_user(data, &bc->param_id, माप(u32)))
			वापस -EFAULT;
		अगर (copy_to_user(data + 1, &size, माप(u32)))
			वापस -EFAULT;
		अगर (copy_to_user(data + 2, bc->params, size))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SKL_PARAM_VENDOR_ID 0xff

अटल पूर्णांक skl_tplg_tlv_control_set(काष्ठा snd_kcontrol *kcontrol,
			स्थिर अचिन्हित पूर्णांक __user *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा skl_module_cfg *mconfig = w->priv;
	काष्ठा soc_bytes_ext *sb =
			(काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा skl_algo_data *ac = (काष्ठा skl_algo_data *)sb->करोbj.निजी;
	काष्ठा skl_dev *skl = get_skl_ctx(w->dapm->dev);

	अगर (ac->params) अणु
		/*
		 * Widget data is expected to be stripped of T and L
		 */
		size -= 2 * माप(अचिन्हित पूर्णांक);
		data += 2;

		अगर (size > ac->max)
			वापस -EINVAL;
		ac->size = size;

		अगर (copy_from_user(ac->params, data, size))
			वापस -EFAULT;

		अगर (w->घातer)
			वापस skl_set_module_params(skl,
						(u32 *)ac->params, ac->size,
						ac->param_id, mconfig);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_mic_control_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा skl_module_cfg *mconfig = w->priv;
	काष्ठा soc_क्रमागत *ec = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	u32 ch_type = *((u32 *)ec->करोbj.निजी);

	अगर (mconfig->dmic_ch_type == ch_type)
		ucontrol->value.क्रमागतerated.item[0] =
					mconfig->dmic_ch_combo_index;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_fill_mic_sel_params(काष्ठा skl_module_cfg *mconfig,
	काष्ठा skl_mic_sel_config *mic_cfg, काष्ठा device *dev)
अणु
	काष्ठा skl_specअगरic_cfg *sp_cfg = &mconfig->क्रमmats_config;

	sp_cfg->caps_size = माप(काष्ठा skl_mic_sel_config);
	sp_cfg->set_params = SKL_PARAM_SET;
	sp_cfg->param_id = 0x00;
	अगर (!sp_cfg->caps) अणु
		sp_cfg->caps = devm_kzalloc(dev, sp_cfg->caps_size, GFP_KERNEL);
		अगर (!sp_cfg->caps)
			वापस -ENOMEM;
	पूर्ण

	mic_cfg->mic_चयन = SKL_MIC_SEL_SWITCH;
	mic_cfg->flags = 0;
	स_नकल(sp_cfg->caps, mic_cfg, sp_cfg->caps_size);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_mic_control_set(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_soc_dapm_kcontrol_widget(kcontrol);
	काष्ठा skl_module_cfg *mconfig = w->priv;
	काष्ठा skl_mic_sel_config mic_cfg = अणु0पूर्ण;
	काष्ठा soc_क्रमागत *ec = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	u32 ch_type = *((u32 *)ec->करोbj.निजी);
	स्थिर पूर्णांक *list;
	u8 in_ch, out_ch, index;

	mconfig->dmic_ch_type = ch_type;
	mconfig->dmic_ch_combo_index = ucontrol->value.क्रमागतerated.item[0];

	/* क्रमागत control index 0 is INVALID, so no channels to be set */
	अगर (mconfig->dmic_ch_combo_index == 0)
		वापस 0;

	/* No valid channel selection map क्रम index 0, so offset by 1 */
	index = mconfig->dmic_ch_combo_index - 1;

	चयन (ch_type) अणु
	हाल SKL_CH_MONO:
		अगर (mconfig->dmic_ch_combo_index > ARRAY_SIZE(mic_mono_list))
			वापस -EINVAL;

		list = &mic_mono_list[index];
		अवरोध;

	हाल SKL_CH_STEREO:
		अगर (mconfig->dmic_ch_combo_index > ARRAY_SIZE(mic_stereo_list))
			वापस -EINVAL;

		list = mic_stereo_list[index];
		अवरोध;

	हाल SKL_CH_TRIO:
		अगर (mconfig->dmic_ch_combo_index > ARRAY_SIZE(mic_trio_list))
			वापस -EINVAL;

		list = mic_trio_list[index];
		अवरोध;

	हाल SKL_CH_QUATRO:
		अगर (mconfig->dmic_ch_combo_index > ARRAY_SIZE(mic_quatro_list))
			वापस -EINVAL;

		list = mic_quatro_list[index];
		अवरोध;

	शेष:
		dev_err(w->dapm->dev,
				"Invalid channel %d for mic_select module\n",
				ch_type);
		वापस -EINVAL;

	पूर्ण

	/* channel type क्रमागत map to number of chanels क्रम that type */
	क्रम (out_ch = 0; out_ch < ch_type; out_ch++) अणु
		in_ch = list[out_ch];
		mic_cfg.blob[out_ch][in_ch] = SKL_DEFAULT_MIC_SEL_GAIN;
	पूर्ण

	वापस skl_fill_mic_sel_params(mconfig, &mic_cfg, w->dapm->dev);
पूर्ण

/*
 * Fill the dma id क्रम host and link. In हाल of passthrough
 * pipeline, this will both host and link in the same
 * pipeline, so need to copy the link and host based on dev_type
 */
अटल व्योम skl_tplg_fill_dma_id(काष्ठा skl_module_cfg *mcfg,
				काष्ठा skl_pipe_params *params)
अणु
	काष्ठा skl_pipe *pipe = mcfg->pipe;

	अगर (pipe->passthru) अणु
		चयन (mcfg->dev_type) अणु
		हाल SKL_DEVICE_HDALINK:
			pipe->p_params->link_dma_id = params->link_dma_id;
			pipe->p_params->link_index = params->link_index;
			pipe->p_params->link_bps = params->link_bps;
			अवरोध;

		हाल SKL_DEVICE_HDAHOST:
			pipe->p_params->host_dma_id = params->host_dma_id;
			pipe->p_params->host_bps = params->host_bps;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		pipe->p_params->s_fmt = params->s_fmt;
		pipe->p_params->ch = params->ch;
		pipe->p_params->s_freq = params->s_freq;
		pipe->p_params->stream = params->stream;
		pipe->p_params->क्रमmat = params->क्रमmat;

	पूर्ण अन्यथा अणु
		स_नकल(pipe->p_params, params, माप(*params));
	पूर्ण
पूर्ण

/*
 * The FE params are passed by hw_params of the DAI.
 * On hw_params, the params are stored in Gateway module of the FE and we
 * need to calculate the क्रमmat in DSP module configuration, that
 * conversion is करोne here
 */
पूर्णांक skl_tplg_update_pipe_params(काष्ठा device *dev,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_pipe_params *params)
अणु
	काष्ठा skl_module_res *res = &mconfig->module->resources[0];
	काष्ठा skl_dev *skl = get_skl_ctx(dev);
	काष्ठा skl_module_fmt *क्रमmat = शून्य;
	u8 cfg_idx = mconfig->pipe->cur_config_idx;

	skl_tplg_fill_dma_id(mconfig, params);
	mconfig->fmt_idx = mconfig->mod_cfg[cfg_idx].fmt_idx;
	mconfig->res_idx = mconfig->mod_cfg[cfg_idx].res_idx;

	अगर (skl->nr_modules)
		वापस 0;

	अगर (params->stream == SNDRV_PCM_STREAM_PLAYBACK)
		क्रमmat = &mconfig->module->क्रमmats[0].inमाला_दो[0].fmt;
	अन्यथा
		क्रमmat = &mconfig->module->क्रमmats[0].outमाला_दो[0].fmt;

	/* set the hw_params */
	क्रमmat->s_freq = params->s_freq;
	क्रमmat->channels = params->ch;
	क्रमmat->valid_bit_depth = skl_get_bit_depth(params->s_fmt);

	/*
	 * 16 bit is 16 bit container whereas 24 bit is in 32 bit
	 * container so update bit depth accordingly
	 */
	चयन (क्रमmat->valid_bit_depth) अणु
	हाल SKL_DEPTH_16BIT:
		क्रमmat->bit_depth = क्रमmat->valid_bit_depth;
		अवरोध;

	हाल SKL_DEPTH_24BIT:
	हाल SKL_DEPTH_32BIT:
		क्रमmat->bit_depth = SKL_DEPTH_32BIT;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid bit depth %x for pipe\n",
				क्रमmat->valid_bit_depth);
		वापस -EINVAL;
	पूर्ण

	अगर (params->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		res->ibs = (क्रमmat->s_freq / 1000) *
				(क्रमmat->channels) *
				(क्रमmat->bit_depth >> 3);
	पूर्ण अन्यथा अणु
		res->obs = (क्रमmat->s_freq / 1000) *
				(क्रमmat->channels) *
				(क्रमmat->bit_depth >> 3);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Query the module config क्रम the FE DAI
 * This is used to find the hw_params set क्रम that DAI and apply to FE
 * pipeline
 */
काष्ठा skl_module_cfg *
skl_tplg_fe_get_cpr_module(काष्ठा snd_soc_dai *dai, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_dapm_path *p = शून्य;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		w = dai->playback_widget;
		snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
			अगर (p->connect && p->sink->घातer &&
				!is_skl_dsp_widget_type(p->sink, dai->dev))
				जारी;

			अगर (p->sink->priv) अणु
				dev_dbg(dai->dev, "set params for %s\n",
						p->sink->name);
				वापस p->sink->priv;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		w = dai->capture_widget;
		snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
			अगर (p->connect && p->source->घातer &&
				!is_skl_dsp_widget_type(p->source, dai->dev))
				जारी;

			अगर (p->source->priv) अणु
				dev_dbg(dai->dev, "set params for %s\n",
						p->source->name);
				वापस p->source->priv;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा skl_module_cfg *skl_get_mconfig_pb_cpr(
		काष्ठा snd_soc_dai *dai, काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा skl_module_cfg *mconfig = शून्य;

	snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
		अगर (w->endpoपूर्णांकs[SND_SOC_DAPM_सूची_OUT] > 0) अणु
			अगर (p->connect &&
				    (p->sink->id == snd_soc_dapm_aअगर_out) &&
				    p->source->priv) अणु
				mconfig = p->source->priv;
				वापस mconfig;
			पूर्ण
			mconfig = skl_get_mconfig_pb_cpr(dai, p->source);
			अगर (mconfig)
				वापस mconfig;
		पूर्ण
	पूर्ण
	वापस mconfig;
पूर्ण

अटल काष्ठा skl_module_cfg *skl_get_mconfig_cap_cpr(
		काष्ठा snd_soc_dai *dai, काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा skl_module_cfg *mconfig = शून्य;

	snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
		अगर (w->endpoपूर्णांकs[SND_SOC_DAPM_सूची_IN] > 0) अणु
			अगर (p->connect &&
				    (p->source->id == snd_soc_dapm_aअगर_in) &&
				    p->sink->priv) अणु
				mconfig = p->sink->priv;
				वापस mconfig;
			पूर्ण
			mconfig = skl_get_mconfig_cap_cpr(dai, p->sink);
			अगर (mconfig)
				वापस mconfig;
		पूर्ण
	पूर्ण
	वापस mconfig;
पूर्ण

काष्ठा skl_module_cfg *
skl_tplg_be_get_cpr_module(काष्ठा snd_soc_dai *dai, पूर्णांक stream)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा skl_module_cfg *mconfig;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		w = dai->playback_widget;
		mconfig = skl_get_mconfig_pb_cpr(dai, w);
	पूर्ण अन्यथा अणु
		w = dai->capture_widget;
		mconfig = skl_get_mconfig_cap_cpr(dai, w);
	पूर्ण
	वापस mconfig;
पूर्ण

अटल u8 skl_tplg_be_link_type(पूर्णांक dev_type)
अणु
	पूर्णांक ret;

	चयन (dev_type) अणु
	हाल SKL_DEVICE_BT:
		ret = NHLT_LINK_SSP;
		अवरोध;

	हाल SKL_DEVICE_DMIC:
		ret = NHLT_LINK_DMIC;
		अवरोध;

	हाल SKL_DEVICE_I2S:
		ret = NHLT_LINK_SSP;
		अवरोध;

	हाल SKL_DEVICE_HDALINK:
		ret = NHLT_LINK_HDA;
		अवरोध;

	शेष:
		ret = NHLT_LINK_INVALID;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Fill the BE gateway parameters
 * The BE gateway expects a blob of parameters which are kept in the ACPI
 * NHLT blob, so query the blob क्रम पूर्णांकerface type (i2s/pdm) and instance.
 * The port can have multiple settings so pick based on the PCM
 * parameters
 */
अटल पूर्णांक skl_tplg_be_fill_pipe_params(काष्ठा snd_soc_dai *dai,
				काष्ठा skl_module_cfg *mconfig,
				काष्ठा skl_pipe_params *params)
अणु
	काष्ठा nhlt_specअगरic_cfg *cfg;
	काष्ठा skl_dev *skl = get_skl_ctx(dai->dev);
	पूर्णांक link_type = skl_tplg_be_link_type(mconfig->dev_type);
	u8 dev_type = skl_tplg_be_dev_type(mconfig->dev_type);

	skl_tplg_fill_dma_id(mconfig, params);

	अगर (link_type == NHLT_LINK_HDA)
		वापस 0;

	/* update the blob based on भव bus_id*/
	cfg = skl_get_ep_blob(skl, mconfig->vbus_id, link_type,
					params->s_fmt, params->ch,
					params->s_freq, params->stream,
					dev_type);
	अगर (cfg) अणु
		mconfig->क्रमmats_config.caps_size = cfg->size;
		mconfig->क्रमmats_config.caps = (u32 *) &cfg->caps;
	पूर्ण अन्यथा अणु
		dev_err(dai->dev, "Blob NULL for id %x type %d dirn %d\n",
					mconfig->vbus_id, link_type,
					params->stream);
		dev_err(dai->dev, "PCM: ch %d, freq %d, fmt %d\n",
				 params->ch, params->s_freq, params->s_fmt);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_be_set_src_pipe_params(काष्ठा snd_soc_dai *dai,
				काष्ठा snd_soc_dapm_widget *w,
				काष्ठा skl_pipe_params *params)
अणु
	काष्ठा snd_soc_dapm_path *p;
	पूर्णांक ret = -EIO;

	snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
		अगर (p->connect && is_skl_dsp_widget_type(p->source, dai->dev) &&
						p->source->priv) अणु

			ret = skl_tplg_be_fill_pipe_params(dai,
						p->source->priv, params);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			ret = skl_tplg_be_set_src_pipe_params(dai,
						p->source, params);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक skl_tplg_be_set_sink_pipe_params(काष्ठा snd_soc_dai *dai,
	काष्ठा snd_soc_dapm_widget *w, काष्ठा skl_pipe_params *params)
अणु
	काष्ठा snd_soc_dapm_path *p;
	पूर्णांक ret = -EIO;

	snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
		अगर (p->connect && is_skl_dsp_widget_type(p->sink, dai->dev) &&
						p->sink->priv) अणु

			ret = skl_tplg_be_fill_pipe_params(dai,
						p->sink->priv, params);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			ret = skl_tplg_be_set_sink_pipe_params(
						dai, p->sink, params);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * BE hw_params can be a source parameters (capture) or sink parameters
 * (playback). Based on sink and source we need to either find the source
 * list or the sink list and set the pipeline parameters
 */
पूर्णांक skl_tplg_be_update_params(काष्ठा snd_soc_dai *dai,
				काष्ठा skl_pipe_params *params)
अणु
	काष्ठा snd_soc_dapm_widget *w;

	अगर (params->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		w = dai->playback_widget;

		वापस skl_tplg_be_set_src_pipe_params(dai, w, params);

	पूर्ण अन्यथा अणु
		w = dai->capture_widget;

		वापस skl_tplg_be_set_sink_pipe_params(dai, w, params);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_tplg_widget_events skl_tplg_widget_ops[] = अणु
	अणुSKL_MIXER_EVENT, skl_tplg_mixer_eventपूर्ण,
	अणुSKL_VMIXER_EVENT, skl_tplg_mixer_eventपूर्ण,
	अणुSKL_PGA_EVENT, skl_tplg_pga_eventपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_tplg_bytes_ext_ops skl_tlv_ops[] = अणु
	अणुSKL_CONTROL_TYPE_BYTE_TLV, skl_tplg_tlv_control_get,
					skl_tplg_tlv_control_setपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_tplg_kcontrol_ops skl_tplg_kcontrol_ops[] = अणु
	अणु
		.id = SKL_CONTROL_TYPE_MIC_SELECT,
		.get = skl_tplg_mic_control_get,
		.put = skl_tplg_mic_control_set,
	पूर्ण,
	अणु
		.id = SKL_CONTROL_TYPE_MULTI_IO_SELECT,
		.get = skl_tplg_multi_config_get,
		.put = skl_tplg_multi_config_set,
	पूर्ण,
	अणु
		.id = SKL_CONTROL_TYPE_MULTI_IO_SELECT_DMIC,
		.get = skl_tplg_multi_config_get_dmic,
		.put = skl_tplg_multi_config_set_dmic,
	पूर्ण
पूर्ण;

अटल पूर्णांक skl_tplg_fill_pipe_cfg(काष्ठा device *dev,
			काष्ठा skl_pipe *pipe, u32 tkn,
			u32 tkn_val, पूर्णांक conf_idx, पूर्णांक dir)
अणु
	काष्ठा skl_pipe_fmt *fmt;
	काष्ठा skl_path_config *config;

	चयन (dir) अणु
	हाल SKL_सूची_IN:
		fmt = &pipe->configs[conf_idx].in_fmt;
		अवरोध;

	हाल SKL_सूची_OUT:
		fmt = &pipe->configs[conf_idx].out_fmt;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid direction: %d\n", dir);
		वापस -EINVAL;
	पूर्ण

	config = &pipe->configs[conf_idx];

	चयन (tkn) अणु
	हाल SKL_TKN_U32_CFG_FREQ:
		fmt->freq = tkn_val;
		अवरोध;

	हाल SKL_TKN_U8_CFG_CHAN:
		fmt->channels = tkn_val;
		अवरोध;

	हाल SKL_TKN_U8_CFG_BPS:
		fmt->bps = tkn_val;
		अवरोध;

	हाल SKL_TKN_U32_PATH_MEM_PGS:
		config->mem_pages = tkn_val;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid token config: %d\n", tkn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_fill_pipe_tkn(काष्ठा device *dev,
			काष्ठा skl_pipe *pipe, u32 tkn,
			u32 tkn_val)
अणु

	चयन (tkn) अणु
	हाल SKL_TKN_U32_PIPE_CONN_TYPE:
		pipe->conn_type = tkn_val;
		अवरोध;

	हाल SKL_TKN_U32_PIPE_PRIORITY:
		pipe->pipe_priority = tkn_val;
		अवरोध;

	हाल SKL_TKN_U32_PIPE_MEM_PGS:
		pipe->memory_pages = tkn_val;
		अवरोध;

	हाल SKL_TKN_U32_PMODE:
		pipe->lp_mode = tkn_val;
		अवरोध;

	हाल SKL_TKN_U32_PIPE_सूचीECTION:
		pipe->direction = tkn_val;
		अवरोध;

	हाल SKL_TKN_U32_NUM_CONFIGS:
		pipe->nr_cfgs = tkn_val;
		अवरोध;

	शेष:
		dev_err(dev, "Token not handled %d\n", tkn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add pipeline by parsing the relevant tokens
 * Return an existing pipe अगर the pipe alपढ़ोy exists.
 */
अटल पूर्णांक skl_tplg_add_pipe(काष्ठा device *dev,
		काष्ठा skl_module_cfg *mconfig, काष्ठा skl_dev *skl,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem)
अणु
	काष्ठा skl_pipeline *ppl;
	काष्ठा skl_pipe *pipe;
	काष्ठा skl_pipe_params *params;

	list_क्रम_each_entry(ppl, &skl->ppl_list, node) अणु
		अगर (ppl->pipe->ppl_id == tkn_elem->value) अणु
			mconfig->pipe = ppl->pipe;
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	ppl = devm_kzalloc(dev, माप(*ppl), GFP_KERNEL);
	अगर (!ppl)
		वापस -ENOMEM;

	pipe = devm_kzalloc(dev, माप(*pipe), GFP_KERNEL);
	अगर (!pipe)
		वापस -ENOMEM;

	params = devm_kzalloc(dev, माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	pipe->p_params = params;
	pipe->ppl_id = tkn_elem->value;
	INIT_LIST_HEAD(&pipe->w_list);

	ppl->pipe = pipe;
	list_add(&ppl->node, &skl->ppl_list);

	mconfig->pipe = pipe;
	mconfig->pipe->state = SKL_PIPE_INVALID;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_get_uuid(काष्ठा device *dev, guid_t *guid,
	      काष्ठा snd_soc_tplg_venकरोr_uuid_elem *uuid_tkn)
अणु
	अगर (uuid_tkn->token == SKL_TKN_UUID) अणु
		import_guid(guid, uuid_tkn->uuid);
		वापस 0;
	पूर्ण

	dev_err(dev, "Not an UUID token %d\n", uuid_tkn->token);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक skl_tplg_fill_pin(काष्ठा device *dev,
			काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
			काष्ठा skl_module_pin *m_pin,
			पूर्णांक pin_index)
अणु
	पूर्णांक ret;

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_U32_PIN_MOD_ID:
		m_pin[pin_index].id.module_id = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_PIN_INST_ID:
		m_pin[pin_index].id.instance_id = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_UUID:
		ret = skl_tplg_get_uuid(dev, &m_pin[pin_index].id.mod_uuid,
			(काष्ठा snd_soc_tplg_venकरोr_uuid_elem *)tkn_elem);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	शेष:
		dev_err(dev, "%d Not a pin token\n", tkn_elem->token);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Parse क्रम pin config specअगरic tokens to fill up the
 * module निजी data
 */
अटल पूर्णांक skl_tplg_fill_pins_info(काष्ठा device *dev,
		काष्ठा skl_module_cfg *mconfig,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		पूर्णांक dir, पूर्णांक pin_count)
अणु
	पूर्णांक ret;
	काष्ठा skl_module_pin *m_pin;

	चयन (dir) अणु
	हाल SKL_सूची_IN:
		m_pin = mconfig->m_in_pin;
		अवरोध;

	हाल SKL_सूची_OUT:
		m_pin = mconfig->m_out_pin;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid direction value\n");
		वापस -EINVAL;
	पूर्ण

	ret = skl_tplg_fill_pin(dev, tkn_elem, m_pin, pin_count);
	अगर (ret < 0)
		वापस ret;

	m_pin[pin_count].in_use = false;
	m_pin[pin_count].pin_state = SKL_PIN_UNBIND;

	वापस 0;
पूर्ण

/*
 * Fill up input/output module config क्रमmat based
 * on the direction
 */
अटल पूर्णांक skl_tplg_fill_fmt(काष्ठा device *dev,
		काष्ठा skl_module_fmt *dst_fmt,
		u32 tkn, u32 value)
अणु
	चयन (tkn) अणु
	हाल SKL_TKN_U32_FMT_CH:
		dst_fmt->channels  = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_FREQ:
		dst_fmt->s_freq = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_BIT_DEPTH:
		dst_fmt->bit_depth = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_SAMPLE_SIZE:
		dst_fmt->valid_bit_depth = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_CH_CONFIG:
		dst_fmt->ch_cfg = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_INTERLEAVE:
		dst_fmt->पूर्णांकerleaving_style = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_SAMPLE_TYPE:
		dst_fmt->sample_type = value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_CH_MAP:
		dst_fmt->ch_map = value;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid token %d\n", tkn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_widget_fill_fmt(काष्ठा device *dev,
		काष्ठा skl_module_अगरace *fmt,
		u32 tkn, u32 val, u32 dir, पूर्णांक fmt_idx)
अणु
	काष्ठा skl_module_fmt *dst_fmt;

	अगर (!fmt)
		वापस -EINVAL;

	चयन (dir) अणु
	हाल SKL_सूची_IN:
		dst_fmt = &fmt->inमाला_दो[fmt_idx].fmt;
		अवरोध;

	हाल SKL_सूची_OUT:
		dst_fmt = &fmt->outमाला_दो[fmt_idx].fmt;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid direction: %d\n", dir);
		वापस -EINVAL;
	पूर्ण

	वापस skl_tplg_fill_fmt(dev, dst_fmt, tkn, val);
पूर्ण

अटल व्योम skl_tplg_fill_pin_dynamic_val(
		काष्ठा skl_module_pin *mpin, u32 pin_count, u32 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pin_count; i++)
		mpin[i].is_dynamic = value;
पूर्ण

/*
 * Resource table in the manअगरest has pin specअगरic resources
 * like pin and pin buffer size
 */
अटल पूर्णांक skl_tplg_manअगरest_pin_res_tkn(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		काष्ठा skl_module_res *res, पूर्णांक pin_idx, पूर्णांक dir)
अणु
	काष्ठा skl_module_pin_resources *m_pin;

	चयन (dir) अणु
	हाल SKL_सूची_IN:
		m_pin = &res->input[pin_idx];
		अवरोध;

	हाल SKL_सूची_OUT:
		m_pin = &res->output[pin_idx];
		अवरोध;

	शेष:
		dev_err(dev, "Invalid pin direction: %d\n", dir);
		वापस -EINVAL;
	पूर्ण

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_MM_U32_RES_PIN_ID:
		m_pin->pin_index = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U32_PIN_BUF:
		m_pin->buf_size = tkn_elem->value;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid token: %d\n", tkn_elem->token);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Fill module specअगरic resources from the manअगरest's resource
 * table like CPS, DMA size, mem_pages.
 */
अटल पूर्णांक skl_tplg_fill_res_tkn(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		काष्ठा skl_module_res *res,
		पूर्णांक pin_idx, पूर्णांक dir)
अणु
	पूर्णांक ret, tkn_count = 0;

	अगर (!res)
		वापस -EINVAL;

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_MM_U32_DMA_SIZE:
		res->dma_buffer_size = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U32_CPC:
		res->cpc = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_MEM_PAGES:
		res->is_pages = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_OBS:
		res->obs = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_IBS:
		res->ibs = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U32_RES_PIN_ID:
	हाल SKL_TKN_MM_U32_PIN_BUF:
		ret = skl_tplg_manअगरest_pin_res_tkn(dev, tkn_elem, res,
						    pin_idx, dir);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	हाल SKL_TKN_MM_U32_CPS:
	हाल SKL_TKN_U32_MAX_MCPS:
		/* ignore unused tokens */
		अवरोध;

	शेष:
		dev_err(dev, "Not a res type token: %d", tkn_elem->token);
		वापस -EINVAL;

	पूर्ण
	tkn_count++;

	वापस tkn_count;
पूर्ण

/*
 * Parse tokens to fill up the module निजी data
 */
अटल पूर्णांक skl_tplg_get_token(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		काष्ठा skl_dev *skl, काष्ठा skl_module_cfg *mconfig)
अणु
	पूर्णांक tkn_count = 0;
	पूर्णांक ret;
	अटल पूर्णांक is_pipe_exists;
	अटल पूर्णांक pin_index, dir, conf_idx;
	काष्ठा skl_module_अगरace *अगरace = शून्य;
	काष्ठा skl_module_res *res = शून्य;
	पूर्णांक res_idx = mconfig->res_idx;
	पूर्णांक fmt_idx = mconfig->fmt_idx;

	/*
	 * If the manअगरest काष्ठाure contains no modules, fill all
	 * the module data to 0th index.
	 * res_idx and fmt_idx are शेष set to 0.
	 */
	अगर (skl->nr_modules == 0) अणु
		res = &mconfig->module->resources[res_idx];
		अगरace = &mconfig->module->क्रमmats[fmt_idx];
	पूर्ण

	अगर (tkn_elem->token > SKL_TKN_MAX)
		वापस -EINVAL;

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_U8_IN_QUEUE_COUNT:
		mconfig->module->max_input_pins = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_OUT_QUEUE_COUNT:
		mconfig->module->max_output_pins = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_DYN_IN_PIN:
		अगर (!mconfig->m_in_pin)
			mconfig->m_in_pin =
				devm_kसुस्मृति(dev, MAX_IN_QUEUE,
					     माप(*mconfig->m_in_pin),
					     GFP_KERNEL);
		अगर (!mconfig->m_in_pin)
			वापस -ENOMEM;

		skl_tplg_fill_pin_dynamic_val(mconfig->m_in_pin, MAX_IN_QUEUE,
					      tkn_elem->value);
		अवरोध;

	हाल SKL_TKN_U8_DYN_OUT_PIN:
		अगर (!mconfig->m_out_pin)
			mconfig->m_out_pin =
				devm_kसुस्मृति(dev, MAX_IN_QUEUE,
					     माप(*mconfig->m_in_pin),
					     GFP_KERNEL);
		अगर (!mconfig->m_out_pin)
			वापस -ENOMEM;

		skl_tplg_fill_pin_dynamic_val(mconfig->m_out_pin, MAX_OUT_QUEUE,
					      tkn_elem->value);
		अवरोध;

	हाल SKL_TKN_U8_TIME_SLOT:
		mconfig->समय_slot = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_CORE_ID:
		mconfig->core_id = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_MOD_TYPE:
		mconfig->m_type = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_DEV_TYPE:
		mconfig->dev_type = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_HW_CONN_TYPE:
		mconfig->hw_conn_type = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U16_MOD_INST_ID:
		mconfig->id.instance_id =
		tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_MEM_PAGES:
	हाल SKL_TKN_U32_MAX_MCPS:
	हाल SKL_TKN_U32_OBS:
	हाल SKL_TKN_U32_IBS:
		ret = skl_tplg_fill_res_tkn(dev, tkn_elem, res, pin_index, dir);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	हाल SKL_TKN_U32_VBUS_ID:
		mconfig->vbus_id = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_PARAMS_FIXUP:
		mconfig->params_fixup = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_CONVERTER:
		mconfig->converter = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_D0I3_CAPS:
		mconfig->d0i3_caps = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_PIPE_ID:
		ret = skl_tplg_add_pipe(dev,
				mconfig, skl, tkn_elem);

		अगर (ret < 0) अणु
			अगर (ret == -EEXIST) अणु
				is_pipe_exists = 1;
				अवरोध;
			पूर्ण
			वापस is_pipe_exists;
		पूर्ण

		अवरोध;

	हाल SKL_TKN_U32_PIPE_CONFIG_ID:
		conf_idx = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_PIPE_CONN_TYPE:
	हाल SKL_TKN_U32_PIPE_PRIORITY:
	हाल SKL_TKN_U32_PIPE_MEM_PGS:
	हाल SKL_TKN_U32_PMODE:
	हाल SKL_TKN_U32_PIPE_सूचीECTION:
	हाल SKL_TKN_U32_NUM_CONFIGS:
		अगर (is_pipe_exists) अणु
			ret = skl_tplg_fill_pipe_tkn(dev, mconfig->pipe,
					tkn_elem->token, tkn_elem->value);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		अवरोध;

	हाल SKL_TKN_U32_PATH_MEM_PGS:
	हाल SKL_TKN_U32_CFG_FREQ:
	हाल SKL_TKN_U8_CFG_CHAN:
	हाल SKL_TKN_U8_CFG_BPS:
		अगर (mconfig->pipe->nr_cfgs) अणु
			ret = skl_tplg_fill_pipe_cfg(dev, mconfig->pipe,
					tkn_elem->token, tkn_elem->value,
					conf_idx, dir);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SKL_TKN_CFG_MOD_RES_ID:
		mconfig->mod_cfg[conf_idx].res_idx = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_CFG_MOD_FMT_ID:
		mconfig->mod_cfg[conf_idx].fmt_idx = tkn_elem->value;
		अवरोध;

	/*
	 * SKL_TKN_U32_सूची_PIN_COUNT token has the value क्रम both
	 * direction and the pin count. The first four bits represent
	 * direction and next four the pin count.
	 */
	हाल SKL_TKN_U32_सूची_PIN_COUNT:
		dir = tkn_elem->value & SKL_IN_सूची_BIT_MASK;
		pin_index = (tkn_elem->value &
			SKL_PIN_COUNT_MASK) >> 4;

		अवरोध;

	हाल SKL_TKN_U32_FMT_CH:
	हाल SKL_TKN_U32_FMT_FREQ:
	हाल SKL_TKN_U32_FMT_BIT_DEPTH:
	हाल SKL_TKN_U32_FMT_SAMPLE_SIZE:
	हाल SKL_TKN_U32_FMT_CH_CONFIG:
	हाल SKL_TKN_U32_FMT_INTERLEAVE:
	हाल SKL_TKN_U32_FMT_SAMPLE_TYPE:
	हाल SKL_TKN_U32_FMT_CH_MAP:
		ret = skl_tplg_widget_fill_fmt(dev, अगरace, tkn_elem->token,
				tkn_elem->value, dir, pin_index);

		अगर (ret < 0)
			वापस ret;

		अवरोध;

	हाल SKL_TKN_U32_PIN_MOD_ID:
	हाल SKL_TKN_U32_PIN_INST_ID:
	हाल SKL_TKN_UUID:
		ret = skl_tplg_fill_pins_info(dev,
				mconfig, tkn_elem, dir,
				pin_index);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	हाल SKL_TKN_U32_CAPS_SIZE:
		mconfig->क्रमmats_config.caps_size =
			tkn_elem->value;

		अवरोध;

	हाल SKL_TKN_U32_CAPS_SET_PARAMS:
		mconfig->क्रमmats_config.set_params =
				tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_CAPS_PARAMS_ID:
		mconfig->क्रमmats_config.param_id =
				tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_PROC_DOMAIN:
		mconfig->करोमुख्य =
			tkn_elem->value;

		अवरोध;

	हाल SKL_TKN_U32_DMA_BUF_SIZE:
		mconfig->dma_buffer_size = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_IN_PIN_TYPE:
	हाल SKL_TKN_U8_OUT_PIN_TYPE:
	हाल SKL_TKN_U8_CONN_TYPE:
		अवरोध;

	शेष:
		dev_err(dev, "Token %d not handled\n",
				tkn_elem->token);
		वापस -EINVAL;
	पूर्ण

	tkn_count++;

	वापस tkn_count;
पूर्ण

/*
 * Parse the venकरोr array क्रम specअगरic tokens to स्थिरruct
 * module निजी data
 */
अटल पूर्णांक skl_tplg_get_tokens(काष्ठा device *dev,
		अक्षर *pvt_data,	काष्ठा skl_dev *skl,
		काष्ठा skl_module_cfg *mconfig, पूर्णांक block_size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_array *array;
	काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem;
	पूर्णांक tkn_count = 0, ret;
	पूर्णांक off = 0, tuple_size = 0;
	bool is_module_guid = true;

	अगर (block_size <= 0)
		वापस -EINVAL;

	जबतक (tuple_size < block_size) अणु
		array = (काष्ठा snd_soc_tplg_venकरोr_array *)(pvt_data + off);

		off += array->size;

		चयन (array->type) अणु
		हाल SND_SOC_TPLG_TUPLE_TYPE_STRING:
			dev_warn(dev, "no string tokens expected for skl tplg\n");
			जारी;

		हाल SND_SOC_TPLG_TUPLE_TYPE_UUID:
			अगर (is_module_guid) अणु
				ret = skl_tplg_get_uuid(dev, (guid_t *)mconfig->guid,
							array->uuid);
				is_module_guid = false;
			पूर्ण अन्यथा अणु
				ret = skl_tplg_get_token(dev, array->value, skl,
							 mconfig);
			पूर्ण

			अगर (ret < 0)
				वापस ret;

			tuple_size += माप(*array->uuid);

			जारी;

		शेष:
			tkn_elem = array->value;
			tkn_count = 0;
			अवरोध;
		पूर्ण

		जबतक (tkn_count <= (array->num_elems - 1)) अणु
			ret = skl_tplg_get_token(dev, tkn_elem,
					skl, mconfig);

			अगर (ret < 0)
				वापस ret;

			tkn_count = tkn_count + ret;
			tkn_elem++;
		पूर्ण

		tuple_size += tkn_count * माप(*tkn_elem);
	पूर्ण

	वापस off;
पूर्ण

/*
 * Every data block is preceded by a descriptor to पढ़ो the number
 * of data blocks, they type of the block and it's size
 */
अटल पूर्णांक skl_tplg_get_desc_blocks(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_array *array)
अणु
	काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem;

	tkn_elem = array->value;

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_U8_NUM_BLOCKS:
	हाल SKL_TKN_U8_BLOCK_TYPE:
	हाल SKL_TKN_U16_BLOCK_SIZE:
		वापस tkn_elem->value;

	शेष:
		dev_err(dev, "Invalid descriptor token %d\n", tkn_elem->token);
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Functions to parse निजी data from configuration file क्रमmat v4 */

/*
 * Add pipeline from topology binary पूर्णांकo driver pipeline list
 *
 * If alपढ़ोy added we वापस that instance
 * Otherwise we create a new instance and add पूर्णांकo driver list
 */
अटल पूर्णांक skl_tplg_add_pipe_v4(काष्ठा device *dev,
			काष्ठा skl_module_cfg *mconfig, काष्ठा skl_dev *skl,
			काष्ठा skl_dfw_v4_pipe *dfw_pipe)
अणु
	काष्ठा skl_pipeline *ppl;
	काष्ठा skl_pipe *pipe;
	काष्ठा skl_pipe_params *params;

	list_क्रम_each_entry(ppl, &skl->ppl_list, node) अणु
		अगर (ppl->pipe->ppl_id == dfw_pipe->pipe_id) अणु
			mconfig->pipe = ppl->pipe;
			वापस 0;
		पूर्ण
	पूर्ण

	ppl = devm_kzalloc(dev, माप(*ppl), GFP_KERNEL);
	अगर (!ppl)
		वापस -ENOMEM;

	pipe = devm_kzalloc(dev, माप(*pipe), GFP_KERNEL);
	अगर (!pipe)
		वापस -ENOMEM;

	params = devm_kzalloc(dev, माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	pipe->ppl_id = dfw_pipe->pipe_id;
	pipe->memory_pages = dfw_pipe->memory_pages;
	pipe->pipe_priority = dfw_pipe->pipe_priority;
	pipe->conn_type = dfw_pipe->conn_type;
	pipe->state = SKL_PIPE_INVALID;
	pipe->p_params = params;
	INIT_LIST_HEAD(&pipe->w_list);

	ppl->pipe = pipe;
	list_add(&ppl->node, &skl->ppl_list);

	mconfig->pipe = pipe;

	वापस 0;
पूर्ण

अटल व्योम skl_fill_module_pin_info_v4(काष्ठा skl_dfw_v4_module_pin *dfw_pin,
					काष्ठा skl_module_pin *m_pin,
					bool is_dynamic, पूर्णांक max_pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < max_pin; i++) अणु
		m_pin[i].id.module_id = dfw_pin[i].module_id;
		m_pin[i].id.instance_id = dfw_pin[i].instance_id;
		m_pin[i].in_use = false;
		m_pin[i].is_dynamic = is_dynamic;
		m_pin[i].pin_state = SKL_PIN_UNBIND;
	पूर्ण
पूर्ण

अटल व्योम skl_tplg_fill_fmt_v4(काष्ठा skl_module_pin_fmt *dst_fmt,
				 काष्ठा skl_dfw_v4_module_fmt *src_fmt,
				 पूर्णांक pins)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pins; i++) अणु
		dst_fmt[i].fmt.channels  = src_fmt[i].channels;
		dst_fmt[i].fmt.s_freq = src_fmt[i].freq;
		dst_fmt[i].fmt.bit_depth = src_fmt[i].bit_depth;
		dst_fmt[i].fmt.valid_bit_depth = src_fmt[i].valid_bit_depth;
		dst_fmt[i].fmt.ch_cfg = src_fmt[i].ch_cfg;
		dst_fmt[i].fmt.ch_map = src_fmt[i].ch_map;
		dst_fmt[i].fmt.पूर्णांकerleaving_style =
						src_fmt[i].पूर्णांकerleaving_style;
		dst_fmt[i].fmt.sample_type = src_fmt[i].sample_type;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_tplg_get_pvt_data_v4(काष्ठा snd_soc_tplg_dapm_widget *tplg_w,
				    काष्ठा skl_dev *skl, काष्ठा device *dev,
				    काष्ठा skl_module_cfg *mconfig)
अणु
	काष्ठा skl_dfw_v4_module *dfw =
				(काष्ठा skl_dfw_v4_module *)tplg_w->priv.data;
	पूर्णांक ret;

	dev_dbg(dev, "Parsing Skylake v4 widget topology data\n");

	ret = guid_parse(dfw->uuid, (guid_t *)mconfig->guid);
	अगर (ret)
		वापस ret;
	mconfig->id.module_id = -1;
	mconfig->id.instance_id = dfw->instance_id;
	mconfig->module->resources[0].cpc = dfw->max_mcps / 1000;
	mconfig->module->resources[0].ibs = dfw->ibs;
	mconfig->module->resources[0].obs = dfw->obs;
	mconfig->core_id = dfw->core_id;
	mconfig->module->max_input_pins = dfw->max_in_queue;
	mconfig->module->max_output_pins = dfw->max_out_queue;
	mconfig->module->loadable = dfw->is_loadable;
	skl_tplg_fill_fmt_v4(mconfig->module->क्रमmats[0].inमाला_दो, dfw->in_fmt,
			     MAX_IN_QUEUE);
	skl_tplg_fill_fmt_v4(mconfig->module->क्रमmats[0].outमाला_दो, dfw->out_fmt,
			     MAX_OUT_QUEUE);

	mconfig->params_fixup = dfw->params_fixup;
	mconfig->converter = dfw->converter;
	mconfig->m_type = dfw->module_type;
	mconfig->vbus_id = dfw->vbus_id;
	mconfig->module->resources[0].is_pages = dfw->mem_pages;

	ret = skl_tplg_add_pipe_v4(dev, mconfig, skl, &dfw->pipe);
	अगर (ret)
		वापस ret;

	mconfig->dev_type = dfw->dev_type;
	mconfig->hw_conn_type = dfw->hw_conn_type;
	mconfig->समय_slot = dfw->समय_slot;
	mconfig->क्रमmats_config.caps_size = dfw->caps.caps_size;

	mconfig->m_in_pin = devm_kसुस्मृति(dev,
				MAX_IN_QUEUE, माप(*mconfig->m_in_pin),
				GFP_KERNEL);
	अगर (!mconfig->m_in_pin)
		वापस -ENOMEM;

	mconfig->m_out_pin = devm_kसुस्मृति(dev,
				MAX_OUT_QUEUE, माप(*mconfig->m_out_pin),
				GFP_KERNEL);
	अगर (!mconfig->m_out_pin)
		वापस -ENOMEM;

	skl_fill_module_pin_info_v4(dfw->in_pin, mconfig->m_in_pin,
				    dfw->is_dynamic_in_pin,
				    mconfig->module->max_input_pins);
	skl_fill_module_pin_info_v4(dfw->out_pin, mconfig->m_out_pin,
				    dfw->is_dynamic_out_pin,
				    mconfig->module->max_output_pins);

	अगर (mconfig->क्रमmats_config.caps_size) अणु
		mconfig->क्रमmats_config.set_params = dfw->caps.set_params;
		mconfig->क्रमmats_config.param_id = dfw->caps.param_id;
		mconfig->क्रमmats_config.caps =
		devm_kzalloc(dev, mconfig->क्रमmats_config.caps_size,
			     GFP_KERNEL);
		अगर (!mconfig->क्रमmats_config.caps)
			वापस -ENOMEM;
		स_नकल(mconfig->क्रमmats_config.caps, dfw->caps.caps,
		       dfw->caps.caps_size);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Parse the निजी data क्रम the token and corresponding value.
 * The निजी data can have multiple data blocks. So, a data block
 * is preceded by a descriptor क्रम number of blocks and a descriptor
 * क्रम the type and size of the suceeding data block.
 */
अटल पूर्णांक skl_tplg_get_pvt_data(काष्ठा snd_soc_tplg_dapm_widget *tplg_w,
				काष्ठा skl_dev *skl, काष्ठा device *dev,
				काष्ठा skl_module_cfg *mconfig)
अणु
	काष्ठा snd_soc_tplg_venकरोr_array *array;
	पूर्णांक num_blocks, block_size, block_type, off = 0;
	अक्षर *data;
	पूर्णांक ret;

	/*
	 * v4 configuration files have a valid UUID at the start of
	 * the widget's निजी data.
	 */
	अगर (uuid_is_valid((अक्षर *)tplg_w->priv.data))
		वापस skl_tplg_get_pvt_data_v4(tplg_w, skl, dev, mconfig);

	/* Read the NUM_DATA_BLOCKS descriptor */
	array = (काष्ठा snd_soc_tplg_venकरोr_array *)tplg_w->priv.data;
	ret = skl_tplg_get_desc_blocks(dev, array);
	अगर (ret < 0)
		वापस ret;
	num_blocks = ret;

	off += array->size;
	/* Read the BLOCK_TYPE and BLOCK_SIZE descriptor */
	जबतक (num_blocks > 0) अणु
		array = (काष्ठा snd_soc_tplg_venकरोr_array *)
				(tplg_w->priv.data + off);

		ret = skl_tplg_get_desc_blocks(dev, array);

		अगर (ret < 0)
			वापस ret;
		block_type = ret;
		off += array->size;

		array = (काष्ठा snd_soc_tplg_venकरोr_array *)
			(tplg_w->priv.data + off);

		ret = skl_tplg_get_desc_blocks(dev, array);

		अगर (ret < 0)
			वापस ret;
		block_size = ret;
		off += array->size;

		array = (काष्ठा snd_soc_tplg_venकरोr_array *)
			(tplg_w->priv.data + off);

		data = (tplg_w->priv.data + off);

		अगर (block_type == SKL_TYPE_TUPLE) अणु
			ret = skl_tplg_get_tokens(dev, data,
					skl, mconfig, block_size);

			अगर (ret < 0)
				वापस ret;

			--num_blocks;
		पूर्ण अन्यथा अणु
			अगर (mconfig->क्रमmats_config.caps_size > 0)
				स_नकल(mconfig->क्रमmats_config.caps, data,
					mconfig->क्रमmats_config.caps_size);
			--num_blocks;
			ret = mconfig->क्रमmats_config.caps_size;
		पूर्ण
		off += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम skl_clear_pin_config(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_dapm_widget *w)
अणु
	पूर्णांक i;
	काष्ठा skl_module_cfg *mconfig;
	काष्ठा skl_pipe *pipe;

	अगर (!म_भेदन(w->dapm->component->name, component->name,
					म_माप(component->name))) अणु
		mconfig = w->priv;
		pipe = mconfig->pipe;
		क्रम (i = 0; i < mconfig->module->max_input_pins; i++) अणु
			mconfig->m_in_pin[i].in_use = false;
			mconfig->m_in_pin[i].pin_state = SKL_PIN_UNBIND;
		पूर्ण
		क्रम (i = 0; i < mconfig->module->max_output_pins; i++) अणु
			mconfig->m_out_pin[i].in_use = false;
			mconfig->m_out_pin[i].pin_state = SKL_PIN_UNBIND;
		पूर्ण
		pipe->state = SKL_PIPE_INVALID;
		mconfig->m_state = SKL_MODULE_UNINIT;
	पूर्ण
पूर्ण

व्योम skl_cleanup_resources(काष्ठा skl_dev *skl)
अणु
	काष्ठा snd_soc_component *soc_component = skl->component;
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_card *card;

	अगर (soc_component == शून्य)
		वापस;

	card = soc_component->card;
	अगर (!card || !card->instantiated)
		वापस;

	list_क्रम_each_entry(w, &card->widमाला_लो, list) अणु
		अगर (is_skl_dsp_widget_type(w, skl->dev) && w->priv != शून्य)
			skl_clear_pin_config(soc_component, w);
	पूर्ण

	skl_clear_module_cnt(skl->dsp);
पूर्ण

/*
 * Topology core widget load callback
 *
 * This is used to save the निजी data क्रम each widget which gives
 * inक्रमmation to the driver about module and pipeline parameters which DSP
 * FW expects like ids, resource values, क्रमmats etc
 */
अटल पूर्णांक skl_tplg_widget_load(काष्ठा snd_soc_component *cmpnt, पूर्णांक index,
				काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_soc_tplg_dapm_widget *tplg_w)
अणु
	पूर्णांक ret;
	काष्ठा hdac_bus *bus = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा skl_module_cfg *mconfig;

	अगर (!tplg_w->priv.size)
		जाओ bind_event;

	mconfig = devm_kzalloc(bus->dev, माप(*mconfig), GFP_KERNEL);

	अगर (!mconfig)
		वापस -ENOMEM;

	अगर (skl->nr_modules == 0) अणु
		mconfig->module = devm_kzalloc(bus->dev,
				माप(*mconfig->module), GFP_KERNEL);
		अगर (!mconfig->module)
			वापस -ENOMEM;
	पूर्ण

	w->priv = mconfig;

	/*
	 * module binary can be loaded later, so set it to query when
	 * module is load क्रम a use हाल
	 */
	mconfig->id.module_id = -1;

	/* Parse निजी data क्रम tuples */
	ret = skl_tplg_get_pvt_data(tplg_w, skl, bus->dev, mconfig);
	अगर (ret < 0)
		वापस ret;

	skl_debug_init_module(skl->debugfs, w, mconfig);

bind_event:
	अगर (tplg_w->event_type == 0) अणु
		dev_dbg(bus->dev, "ASoC: No event handler required\n");
		वापस 0;
	पूर्ण

	ret = snd_soc_tplg_widget_bind_event(w, skl_tplg_widget_ops,
					ARRAY_SIZE(skl_tplg_widget_ops),
					tplg_w->event_type);

	अगर (ret) अणु
		dev_err(bus->dev, "%s: No matching event handlers found for %d\n",
					__func__, tplg_w->event_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_init_algo_data(काष्ठा device *dev, काष्ठा soc_bytes_ext *be,
					काष्ठा snd_soc_tplg_bytes_control *bc)
अणु
	काष्ठा skl_algo_data *ac;
	काष्ठा skl_dfw_algo_data *dfw_ac =
				(काष्ठा skl_dfw_algo_data *)bc->priv.data;

	ac = devm_kzalloc(dev, माप(*ac), GFP_KERNEL);
	अगर (!ac)
		वापस -ENOMEM;

	/* Fill निजी data */
	ac->max = dfw_ac->max;
	ac->param_id = dfw_ac->param_id;
	ac->set_params = dfw_ac->set_params;
	ac->size = dfw_ac->max;

	अगर (ac->max) अणु
		ac->params = devm_kzalloc(dev, ac->max, GFP_KERNEL);
		अगर (!ac->params)
			वापस -ENOMEM;

		स_नकल(ac->params, dfw_ac->params, ac->max);
	पूर्ण

	be->करोbj.निजी  = ac;
	वापस 0;
पूर्ण

अटल पूर्णांक skl_init_क्रमागत_data(काष्ठा device *dev, काष्ठा soc_क्रमागत *se,
				काष्ठा snd_soc_tplg_क्रमागत_control *ec)
अणु

	व्योम *data;

	अगर (ec->priv.size) अणु
		data = devm_kzalloc(dev, माप(ec->priv.size), GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;
		स_नकल(data, ec->priv.data, ec->priv.size);
		se->करोbj.निजी = data;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक skl_tplg_control_load(काष्ठा snd_soc_component *cmpnt,
				पूर्णांक index,
				काष्ठा snd_kcontrol_new *kctl,
				काष्ठा snd_soc_tplg_ctl_hdr *hdr)
अणु
	काष्ठा soc_bytes_ext *sb;
	काष्ठा snd_soc_tplg_bytes_control *tplg_bc;
	काष्ठा snd_soc_tplg_क्रमागत_control *tplg_ec;
	काष्ठा hdac_bus *bus  = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा soc_क्रमागत *se;

	चयन (hdr->ops.info) अणु
	हाल SND_SOC_TPLG_CTL_BYTES:
		tplg_bc = container_of(hdr,
				काष्ठा snd_soc_tplg_bytes_control, hdr);
		अगर (kctl->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) अणु
			sb = (काष्ठा soc_bytes_ext *)kctl->निजी_value;
			अगर (tplg_bc->priv.size)
				वापस skl_init_algo_data(
						bus->dev, sb, tplg_bc);
		पूर्ण
		अवरोध;

	हाल SND_SOC_TPLG_CTL_ENUM:
		tplg_ec = container_of(hdr,
				काष्ठा snd_soc_tplg_क्रमागत_control, hdr);
		अगर (kctl->access & SNDRV_CTL_ELEM_ACCESS_READ) अणु
			se = (काष्ठा soc_क्रमागत *)kctl->निजी_value;
			अगर (tplg_ec->priv.size)
				skl_init_क्रमागत_data(bus->dev, se, tplg_ec);
		पूर्ण

		/*
		 * now that the control initializations are करोne, हटाओ
		 * ग_लिखो permission क्रम the DMIC configuration क्रमागतs to
		 * aव्योम conflicts between NHLT settings and user पूर्णांकeraction
		 */

		अगर (hdr->ops.get == SKL_CONTROL_TYPE_MULTI_IO_SELECT_DMIC)
			kctl->access = SNDRV_CTL_ELEM_ACCESS_READ;

		अवरोध;

	शेष:
		dev_dbg(bus->dev, "Control load not supported %d:%d:%d\n",
			hdr->ops.get, hdr->ops.put, hdr->ops.info);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_fill_str_mfest_tkn(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_string_elem *str_elem,
		काष्ठा skl_dev *skl)
अणु
	पूर्णांक tkn_count = 0;
	अटल पूर्णांक ref_count;

	चयन (str_elem->token) अणु
	हाल SKL_TKN_STR_LIB_NAME:
		अगर (ref_count > skl->lib_count - 1) अणु
			ref_count = 0;
			वापस -EINVAL;
		पूर्ण

		म_नकलन(skl->lib_info[ref_count].name,
			str_elem->string,
			ARRAY_SIZE(skl->lib_info[ref_count].name));
		ref_count++;
		अवरोध;

	शेष:
		dev_err(dev, "Not a string token %d\n", str_elem->token);
		अवरोध;
	पूर्ण
	tkn_count++;

	वापस tkn_count;
पूर्ण

अटल पूर्णांक skl_tplg_get_str_tkn(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_array *array,
		काष्ठा skl_dev *skl)
अणु
	पूर्णांक tkn_count = 0, ret;
	काष्ठा snd_soc_tplg_venकरोr_string_elem *str_elem;

	str_elem = (काष्ठा snd_soc_tplg_venकरोr_string_elem *)array->value;
	जबतक (tkn_count < array->num_elems) अणु
		ret = skl_tplg_fill_str_mfest_tkn(dev, str_elem, skl);
		str_elem++;

		अगर (ret < 0)
			वापस ret;

		tkn_count = tkn_count + ret;
	पूर्ण

	वापस tkn_count;
पूर्ण

अटल पूर्णांक skl_tplg_manअगरest_fill_fmt(काष्ठा device *dev,
		काष्ठा skl_module_अगरace *fmt,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		u32 dir, पूर्णांक fmt_idx)
अणु
	काष्ठा skl_module_pin_fmt *dst_fmt;
	काष्ठा skl_module_fmt *mod_fmt;
	पूर्णांक ret;

	अगर (!fmt)
		वापस -EINVAL;

	चयन (dir) अणु
	हाल SKL_सूची_IN:
		dst_fmt = &fmt->inमाला_दो[fmt_idx];
		अवरोध;

	हाल SKL_सूची_OUT:
		dst_fmt = &fmt->outमाला_दो[fmt_idx];
		अवरोध;

	शेष:
		dev_err(dev, "Invalid direction: %d\n", dir);
		वापस -EINVAL;
	पूर्ण

	mod_fmt = &dst_fmt->fmt;

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_MM_U32_INTF_PIN_ID:
		dst_fmt->id = tkn_elem->value;
		अवरोध;

	शेष:
		ret = skl_tplg_fill_fmt(dev, mod_fmt, tkn_elem->token,
					tkn_elem->value);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_tplg_fill_mod_info(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		काष्ठा skl_module *mod)
अणु

	अगर (!mod)
		वापस -EINVAL;

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_U8_IN_PIN_TYPE:
		mod->input_pin_type = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_OUT_PIN_TYPE:
		mod->output_pin_type = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_IN_QUEUE_COUNT:
		mod->max_input_pins = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_OUT_QUEUE_COUNT:
		mod->max_output_pins = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U8_NUM_RES:
		mod->nr_resources = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U8_NUM_INTF:
		mod->nr_पूर्णांकerfaces = tkn_elem->value;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid mod info token %d", tkn_elem->token);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक skl_tplg_get_पूर्णांक_tkn(काष्ठा device *dev,
		काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem,
		काष्ठा skl_dev *skl)
अणु
	पूर्णांक tkn_count = 0, ret;
	अटल पूर्णांक mod_idx, res_val_idx, पूर्णांकf_val_idx, dir, pin_idx;
	काष्ठा skl_module_res *res = शून्य;
	काष्ठा skl_module_अगरace *fmt = शून्य;
	काष्ठा skl_module *mod = शून्य;
	अटल काष्ठा skl_astate_param *astate_table;
	अटल पूर्णांक astate_cfg_idx, count;
	पूर्णांक i;
	माप_प्रकार size;

	अगर (skl->modules) अणु
		mod = skl->modules[mod_idx];
		res = &mod->resources[res_val_idx];
		fmt = &mod->क्रमmats[पूर्णांकf_val_idx];
	पूर्ण

	चयन (tkn_elem->token) अणु
	हाल SKL_TKN_U32_LIB_COUNT:
		skl->lib_count = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_NUM_MOD:
		skl->nr_modules = tkn_elem->value;
		skl->modules = devm_kसुस्मृति(dev, skl->nr_modules,
				माप(*skl->modules), GFP_KERNEL);
		अगर (!skl->modules)
			वापस -ENOMEM;

		क्रम (i = 0; i < skl->nr_modules; i++) अणु
			skl->modules[i] = devm_kzalloc(dev,
					माप(काष्ठा skl_module), GFP_KERNEL);
			अगर (!skl->modules[i])
				वापस -ENOMEM;
		पूर्ण
		अवरोध;

	हाल SKL_TKN_MM_U8_MOD_IDX:
		mod_idx = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_ASTATE_COUNT:
		अगर (astate_table != शून्य) अणु
			dev_err(dev, "More than one entry for A-State count");
			वापस -EINVAL;
		पूर्ण

		अगर (tkn_elem->value > SKL_MAX_ASTATE_CFG) अणु
			dev_err(dev, "Invalid A-State count %d\n",
				tkn_elem->value);
			वापस -EINVAL;
		पूर्ण

		size = काष्ठा_size(skl->cfg.astate_cfg, astate_table,
				   tkn_elem->value);
		skl->cfg.astate_cfg = devm_kzalloc(dev, size, GFP_KERNEL);
		अगर (!skl->cfg.astate_cfg)
			वापस -ENOMEM;

		astate_table = skl->cfg.astate_cfg->astate_table;
		count = skl->cfg.astate_cfg->count = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_ASTATE_IDX:
		अगर (tkn_elem->value >= count) अणु
			dev_err(dev, "Invalid A-State index %d\n",
				tkn_elem->value);
			वापस -EINVAL;
		पूर्ण

		astate_cfg_idx = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_ASTATE_KCPS:
		astate_table[astate_cfg_idx].kcps = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_ASTATE_CLK_SRC:
		astate_table[astate_cfg_idx].clk_src = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U8_IN_PIN_TYPE:
	हाल SKL_TKN_U8_OUT_PIN_TYPE:
	हाल SKL_TKN_U8_IN_QUEUE_COUNT:
	हाल SKL_TKN_U8_OUT_QUEUE_COUNT:
	हाल SKL_TKN_MM_U8_NUM_RES:
	हाल SKL_TKN_MM_U8_NUM_INTF:
		ret = skl_tplg_fill_mod_info(dev, tkn_elem, mod);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	हाल SKL_TKN_U32_सूची_PIN_COUNT:
		dir = tkn_elem->value & SKL_IN_सूची_BIT_MASK;
		pin_idx = (tkn_elem->value & SKL_PIN_COUNT_MASK) >> 4;
		अवरोध;

	हाल SKL_TKN_MM_U32_RES_ID:
		अगर (!res)
			वापस -EINVAL;

		res->id = tkn_elem->value;
		res_val_idx = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U32_FMT_ID:
		अगर (!fmt)
			वापस -EINVAL;

		fmt->fmt_idx = tkn_elem->value;
		पूर्णांकf_val_idx = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U32_CPS:
	हाल SKL_TKN_MM_U32_DMA_SIZE:
	हाल SKL_TKN_MM_U32_CPC:
	हाल SKL_TKN_U32_MEM_PAGES:
	हाल SKL_TKN_U32_OBS:
	हाल SKL_TKN_U32_IBS:
	हाल SKL_TKN_MM_U32_RES_PIN_ID:
	हाल SKL_TKN_MM_U32_PIN_BUF:
		ret = skl_tplg_fill_res_tkn(dev, tkn_elem, res, pin_idx, dir);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	हाल SKL_TKN_MM_U32_NUM_IN_FMT:
		अगर (!fmt)
			वापस -EINVAL;

		res->nr_input_pins = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_MM_U32_NUM_OUT_FMT:
		अगर (!fmt)
			वापस -EINVAL;

		res->nr_output_pins = tkn_elem->value;
		अवरोध;

	हाल SKL_TKN_U32_FMT_CH:
	हाल SKL_TKN_U32_FMT_FREQ:
	हाल SKL_TKN_U32_FMT_BIT_DEPTH:
	हाल SKL_TKN_U32_FMT_SAMPLE_SIZE:
	हाल SKL_TKN_U32_FMT_CH_CONFIG:
	हाल SKL_TKN_U32_FMT_INTERLEAVE:
	हाल SKL_TKN_U32_FMT_SAMPLE_TYPE:
	हाल SKL_TKN_U32_FMT_CH_MAP:
	हाल SKL_TKN_MM_U32_INTF_PIN_ID:
		ret = skl_tplg_manअगरest_fill_fmt(dev, fmt, tkn_elem,
						 dir, pin_idx);
		अगर (ret < 0)
			वापस ret;
		अवरोध;

	शेष:
		dev_err(dev, "Not a manifest token %d\n", tkn_elem->token);
		वापस -EINVAL;
	पूर्ण
	tkn_count++;

	वापस tkn_count;
पूर्ण

/*
 * Fill the manअगरest काष्ठाure by parsing the tokens based on the
 * type.
 */
अटल पूर्णांक skl_tplg_get_manअगरest_tkn(काष्ठा device *dev,
		अक्षर *pvt_data, काष्ठा skl_dev *skl,
		पूर्णांक block_size)
अणु
	पूर्णांक tkn_count = 0, ret;
	पूर्णांक off = 0, tuple_size = 0;
	u8 uuid_index = 0;
	काष्ठा snd_soc_tplg_venकरोr_array *array;
	काष्ठा snd_soc_tplg_venकरोr_value_elem *tkn_elem;

	अगर (block_size <= 0)
		वापस -EINVAL;

	जबतक (tuple_size < block_size) अणु
		array = (काष्ठा snd_soc_tplg_venकरोr_array *)(pvt_data + off);
		off += array->size;
		चयन (array->type) अणु
		हाल SND_SOC_TPLG_TUPLE_TYPE_STRING:
			ret = skl_tplg_get_str_tkn(dev, array, skl);

			अगर (ret < 0)
				वापस ret;
			tkn_count = ret;

			tuple_size += tkn_count *
				माप(काष्ठा snd_soc_tplg_venकरोr_string_elem);
			जारी;

		हाल SND_SOC_TPLG_TUPLE_TYPE_UUID:
			अगर (array->uuid->token != SKL_TKN_UUID) अणु
				dev_err(dev, "Not an UUID token: %d\n",
					array->uuid->token);
				वापस -EINVAL;
			पूर्ण
			अगर (uuid_index >= skl->nr_modules) अणु
				dev_err(dev, "Too many UUID tokens\n");
				वापस -EINVAL;
			पूर्ण
			import_guid(&skl->modules[uuid_index++]->uuid,
				    array->uuid->uuid);

			tuple_size += माप(*array->uuid);
			जारी;

		शेष:
			tkn_elem = array->value;
			tkn_count = 0;
			अवरोध;
		पूर्ण

		जबतक (tkn_count <= array->num_elems - 1) अणु
			ret = skl_tplg_get_पूर्णांक_tkn(dev,
					tkn_elem, skl);
			अगर (ret < 0)
				वापस ret;

			tkn_count = tkn_count + ret;
			tkn_elem++;
		पूर्ण
		tuple_size += (tkn_count * माप(*tkn_elem));
		tkn_count = 0;
	पूर्ण

	वापस off;
पूर्ण

/*
 * Parse manअगरest निजी data क्रम tokens. The निजी data block is
 * preceded by descriptors क्रम type and size of data block.
 */
अटल पूर्णांक skl_tplg_get_manअगरest_data(काष्ठा snd_soc_tplg_manअगरest *manअगरest,
			काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु
	काष्ठा snd_soc_tplg_venकरोr_array *array;
	पूर्णांक num_blocks, block_size = 0, block_type, off = 0;
	अक्षर *data;
	पूर्णांक ret;

	/* Read the NUM_DATA_BLOCKS descriptor */
	array = (काष्ठा snd_soc_tplg_venकरोr_array *)manअगरest->priv.data;
	ret = skl_tplg_get_desc_blocks(dev, array);
	अगर (ret < 0)
		वापस ret;
	num_blocks = ret;

	off += array->size;
	/* Read the BLOCK_TYPE and BLOCK_SIZE descriptor */
	जबतक (num_blocks > 0) अणु
		array = (काष्ठा snd_soc_tplg_venकरोr_array *)
				(manअगरest->priv.data + off);
		ret = skl_tplg_get_desc_blocks(dev, array);

		अगर (ret < 0)
			वापस ret;
		block_type = ret;
		off += array->size;

		array = (काष्ठा snd_soc_tplg_venकरोr_array *)
			(manअगरest->priv.data + off);

		ret = skl_tplg_get_desc_blocks(dev, array);

		अगर (ret < 0)
			वापस ret;
		block_size = ret;
		off += array->size;

		array = (काष्ठा snd_soc_tplg_venकरोr_array *)
			(manअगरest->priv.data + off);

		data = (manअगरest->priv.data + off);

		अगर (block_type == SKL_TYPE_TUPLE) अणु
			ret = skl_tplg_get_manअगरest_tkn(dev, data, skl,
					block_size);

			अगर (ret < 0)
				वापस ret;

			--num_blocks;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		off += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_manअगरest_load(काष्ठा snd_soc_component *cmpnt, पूर्णांक index,
				काष्ठा snd_soc_tplg_manअगरest *manअगरest)
अणु
	काष्ठा hdac_bus *bus = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा skl_dev *skl = bus_to_skl(bus);

	/* proceed only अगर we have निजी data defined */
	अगर (manअगरest->priv.size == 0)
		वापस 0;

	skl_tplg_get_manअगरest_data(manअगरest, bus->dev, skl);

	अगर (skl->lib_count > SKL_MAX_LIB) अणु
		dev_err(bus->dev, "Exceeding max Library count. Got:%d\n",
					skl->lib_count);
		वापस  -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम skl_tplg_complete(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_करोbj *करोbj;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा snd_ctl_elem_value *val;
	पूर्णांक i;

	val = kदो_स्मृति(माप(*val), GFP_KERNEL);
	अगर (!val)
		वापस;

	mach = dev_get_platdata(component->card->dev);
	list_क्रम_each_entry(करोbj, &component->करोbj_list, list) अणु
		काष्ठा snd_kcontrol *kcontrol = करोbj->control.kcontrol;
		काष्ठा soc_क्रमागत *se;
		अक्षर **texts;
		अक्षर chan_text[4];

		अगर (करोbj->type != SND_SOC_DOBJ_ENUM || !kcontrol ||
		    kcontrol->put != skl_tplg_multi_config_set_dmic)
			जारी;

		se = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
		texts = करोbj->control.dtexts;
		प्र_लिखो(chan_text, "c%d", mach->mach_params.dmic_num);

		क्रम (i = 0; i < se->items; i++) अणु
			अगर (म_माला(texts[i], chan_text)) अणु
				स_रखो(val, 0, माप(*val));
				val->value.क्रमागतerated.item[0] = i;
				kcontrol->put(kcontrol, val);
			पूर्ण
		पूर्ण
	पूर्ण
	kमुक्त(val);
पूर्ण

अटल काष्ठा snd_soc_tplg_ops skl_tplg_ops  = अणु
	.widget_load = skl_tplg_widget_load,
	.control_load = skl_tplg_control_load,
	.bytes_ext_ops = skl_tlv_ops,
	.bytes_ext_ops_count = ARRAY_SIZE(skl_tlv_ops),
	.io_ops = skl_tplg_kcontrol_ops,
	.io_ops_count = ARRAY_SIZE(skl_tplg_kcontrol_ops),
	.manअगरest = skl_manअगरest_load,
	.dai_load = skl_dai_load,
	.complete = skl_tplg_complete,
पूर्ण;

/*
 * A pipe can have multiple modules, each of them will be a DAPM widget as
 * well. While managing a pipeline we need to get the list of all the
 * widमाला_लो in a pipelines, so this helper - skl_tplg_create_pipe_widget_list()
 * helps to get the SKL type widमाला_लो in that pipeline
 */
अटल पूर्णांक skl_tplg_create_pipe_widget_list(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा skl_module_cfg *mcfg = शून्य;
	काष्ठा skl_pipe_module *p_module = शून्य;
	काष्ठा skl_pipe *pipe;

	list_क्रम_each_entry(w, &component->card->widमाला_लो, list) अणु
		अगर (is_skl_dsp_widget_type(w, component->dev) && w->priv) अणु
			mcfg = w->priv;
			pipe = mcfg->pipe;

			p_module = devm_kzalloc(component->dev,
						माप(*p_module), GFP_KERNEL);
			अगर (!p_module)
				वापस -ENOMEM;

			p_module->w = w;
			list_add_tail(&p_module->node, &pipe->w_list);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम skl_tplg_set_pipe_type(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	काष्ठा skl_pipe_module *w_module;
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा skl_module_cfg *mconfig;
	bool host_found = false, link_found = false;

	list_क्रम_each_entry(w_module, &pipe->w_list, node) अणु
		w = w_module->w;
		mconfig = w->priv;

		अगर (mconfig->dev_type == SKL_DEVICE_HDAHOST)
			host_found = true;
		अन्यथा अगर (mconfig->dev_type != SKL_DEVICE_NONE)
			link_found = true;
	पूर्ण

	अगर (host_found && link_found)
		pipe->passthru = true;
	अन्यथा
		pipe->passthru = false;
पूर्ण

/*
 * SKL topology init routine
 */
पूर्णांक skl_tplg_init(काष्ठा snd_soc_component *component, काष्ठा hdac_bus *bus)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा skl_pipeline *ppl;

	ret = request_firmware(&fw, skl->tplg_name, bus->dev);
	अगर (ret < 0) अणु
		अक्षर alt_tplg_name[64];

		snम_लिखो(alt_tplg_name, माप(alt_tplg_name), "%s-tplg.bin",
			 skl->mach->drv_name);
		dev_info(bus->dev, "tplg fw %s load failed with %d, trying alternative tplg name %s",
			 skl->tplg_name, ret, alt_tplg_name);

		ret = request_firmware(&fw, alt_tplg_name, bus->dev);
		अगर (!ret)
			जाओ component_load;

		dev_info(bus->dev, "tplg %s failed with %d, falling back to dfw_sst.bin",
			 alt_tplg_name, ret);

		ret = request_firmware(&fw, "dfw_sst.bin", bus->dev);
		अगर (ret < 0) अणु
			dev_err(bus->dev, "Fallback tplg fw %s load failed with %d\n",
					"dfw_sst.bin", ret);
			वापस ret;
		पूर्ण
	पूर्ण

component_load:
	ret = snd_soc_tplg_component_load(component, &skl_tplg_ops, fw);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "tplg component load failed%d\n", ret);
		जाओ err;
	पूर्ण

	ret = skl_tplg_create_pipe_widget_list(component);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "tplg create pipe widget list failed%d\n",
				ret);
		जाओ err;
	पूर्ण

	list_क्रम_each_entry(ppl, &skl->ppl_list, node)
		skl_tplg_set_pipe_type(skl, ppl->pipe);

err:
	release_firmware(fw);
	वापस ret;
पूर्ण

व्योम skl_tplg_निकास(काष्ठा snd_soc_component *component, काष्ठा hdac_bus *bus)
अणु
	काष्ठा skl_dev *skl = bus_to_skl(bus);
	काष्ठा skl_pipeline *ppl, *पंचांगp;

	list_क्रम_each_entry_safe(ppl, पंचांगp, &skl->ppl_list, node)
		list_del(&ppl->node);

	/* clean up topology */
	snd_soc_tplg_component_हटाओ(component);
पूर्ण
