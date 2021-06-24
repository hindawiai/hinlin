<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl-message.c - HDA DSP पूर्णांकerface क्रम FW registration, Pipe and Module
 *  configurations
 *
 *  Copyright (C) 2015 Intel Corp
 *  Author:Rafal Redzimski <rafal.f.redzimski@पूर्णांकel.com>
 *	   Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <uapi/sound/skl-tplg-पूर्णांकerface.h>
#समावेश "skl-sst-dsp.h"
#समावेश "cnl-sst-dsp.h"
#समावेश "skl-sst-ipc.h"
#समावेश "skl.h"
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "skl-topology.h"

अटल पूर्णांक skl_alloc_dma_buf(काष्ठा device *dev,
		काष्ठा snd_dma_buffer *dmab, माप_प्रकार size)
अणु
	वापस snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, dev, size, dmab);
पूर्ण

अटल पूर्णांक skl_मुक्त_dma_buf(काष्ठा device *dev, काष्ठा snd_dma_buffer *dmab)
अणु
	snd_dma_मुक्त_pages(dmab);
	वापस 0;
पूर्ण

#घोषणा SKL_ASTATE_PARAM_ID	4

व्योम skl_dsp_set_astate_cfg(काष्ठा skl_dev *skl, u32 cnt, व्योम *data)
अणु
	काष्ठा skl_ipc_large_config_msg	msg = अणु0पूर्ण;

	msg.large_param_id = SKL_ASTATE_PARAM_ID;
	msg.param_data_size = (cnt * माप(काष्ठा skl_astate_param) +
				माप(cnt));

	skl_ipc_set_large_config(&skl->ipc, &msg, data);
पूर्ण

अटल पूर्णांक skl_dsp_setup_spib(काष्ठा device *dev, अचिन्हित पूर्णांक size,
				पूर्णांक stream_tag, पूर्णांक enable)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा hdac_stream *stream = snd_hdac_get_stream(bus,
			SNDRV_PCM_STREAM_PLAYBACK, stream_tag);
	काष्ठा hdac_ext_stream *estream;

	अगर (!stream)
		वापस -EINVAL;

	estream = stream_to_hdac_ext_stream(stream);
	/* enable/disable SPIB क्रम this hdac stream */
	snd_hdac_ext_stream_spbcap_enable(bus, enable, stream->index);

	/* set the spib value */
	snd_hdac_ext_stream_set_spib(bus, estream, size);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_dsp_prepare(काष्ठा device *dev, अचिन्हित पूर्णांक क्रमmat,
			अचिन्हित पूर्णांक size, काष्ठा snd_dma_buffer *dmab)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा hdac_ext_stream *estream;
	काष्ठा hdac_stream *stream;
	काष्ठा snd_pcm_substream substream;
	पूर्णांक ret;

	अगर (!bus)
		वापस -ENODEV;

	स_रखो(&substream, 0, माप(substream));
	substream.stream = SNDRV_PCM_STREAM_PLAYBACK;

	estream = snd_hdac_ext_stream_assign(bus, &substream,
					HDAC_EXT_STREAM_TYPE_HOST);
	अगर (!estream)
		वापस -ENODEV;

	stream = hdac_stream(estream);

	/* assign decouple host dma channel */
	ret = snd_hdac_dsp_prepare(stream, क्रमmat, size, dmab);
	अगर (ret < 0)
		वापस ret;

	skl_dsp_setup_spib(dev, size, stream->stream_tag, true);

	वापस stream->stream_tag;
पूर्ण

अटल पूर्णांक skl_dsp_trigger(काष्ठा device *dev, bool start, पूर्णांक stream_tag)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा hdac_stream *stream;

	अगर (!bus)
		वापस -ENODEV;

	stream = snd_hdac_get_stream(bus,
		SNDRV_PCM_STREAM_PLAYBACK, stream_tag);
	अगर (!stream)
		वापस -EINVAL;

	snd_hdac_dsp_trigger(stream, start);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_dsp_cleanup(काष्ठा device *dev,
		काष्ठा snd_dma_buffer *dmab, पूर्णांक stream_tag)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);
	काष्ठा hdac_stream *stream;
	काष्ठा hdac_ext_stream *estream;

	अगर (!bus)
		वापस -ENODEV;

	stream = snd_hdac_get_stream(bus,
		SNDRV_PCM_STREAM_PLAYBACK, stream_tag);
	अगर (!stream)
		वापस -EINVAL;

	estream = stream_to_hdac_ext_stream(stream);
	skl_dsp_setup_spib(dev, 0, stream_tag, false);
	snd_hdac_ext_stream_release(estream, HDAC_EXT_STREAM_TYPE_HOST);

	snd_hdac_dsp_cleanup(stream, dmab);

	वापस 0;
पूर्ण

अटल काष्ठा skl_dsp_loader_ops skl_get_loader_ops(व्योम)
अणु
	काष्ठा skl_dsp_loader_ops loader_ops;

	स_रखो(&loader_ops, 0, माप(काष्ठा skl_dsp_loader_ops));

	loader_ops.alloc_dma_buf = skl_alloc_dma_buf;
	loader_ops.मुक्त_dma_buf = skl_मुक्त_dma_buf;

	वापस loader_ops;
पूर्ण;

अटल काष्ठा skl_dsp_loader_ops bxt_get_loader_ops(व्योम)
अणु
	काष्ठा skl_dsp_loader_ops loader_ops;

	स_रखो(&loader_ops, 0, माप(loader_ops));

	loader_ops.alloc_dma_buf = skl_alloc_dma_buf;
	loader_ops.मुक्त_dma_buf = skl_मुक्त_dma_buf;
	loader_ops.prepare = skl_dsp_prepare;
	loader_ops.trigger = skl_dsp_trigger;
	loader_ops.cleanup = skl_dsp_cleanup;

	वापस loader_ops;
पूर्ण;

अटल स्थिर काष्ठा skl_dsp_ops dsp_ops[] = अणु
	अणु
		.id = 0x9d70,
		.num_cores = 2,
		.loader_ops = skl_get_loader_ops,
		.init = skl_sst_dsp_init,
		.init_fw = skl_sst_init_fw,
		.cleanup = skl_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0x9d71,
		.num_cores = 2,
		.loader_ops = skl_get_loader_ops,
		.init = skl_sst_dsp_init,
		.init_fw = skl_sst_init_fw,
		.cleanup = skl_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0x5a98,
		.num_cores = 2,
		.loader_ops = bxt_get_loader_ops,
		.init = bxt_sst_dsp_init,
		.init_fw = bxt_sst_init_fw,
		.cleanup = bxt_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0x3198,
		.num_cores = 2,
		.loader_ops = bxt_get_loader_ops,
		.init = bxt_sst_dsp_init,
		.init_fw = bxt_sst_init_fw,
		.cleanup = bxt_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0x9dc8,
		.num_cores = 4,
		.loader_ops = bxt_get_loader_ops,
		.init = cnl_sst_dsp_init,
		.init_fw = cnl_sst_init_fw,
		.cleanup = cnl_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0xa348,
		.num_cores = 4,
		.loader_ops = bxt_get_loader_ops,
		.init = cnl_sst_dsp_init,
		.init_fw = cnl_sst_init_fw,
		.cleanup = cnl_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0x02c8,
		.num_cores = 4,
		.loader_ops = bxt_get_loader_ops,
		.init = cnl_sst_dsp_init,
		.init_fw = cnl_sst_init_fw,
		.cleanup = cnl_sst_dsp_cleanup
	पूर्ण,
	अणु
		.id = 0x06c8,
		.num_cores = 4,
		.loader_ops = bxt_get_loader_ops,
		.init = cnl_sst_dsp_init,
		.init_fw = cnl_sst_init_fw,
		.cleanup = cnl_sst_dsp_cleanup
	पूर्ण,
पूर्ण;

स्थिर काष्ठा skl_dsp_ops *skl_get_dsp_ops(पूर्णांक pci_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dsp_ops); i++) अणु
		अगर (dsp_ops[i].id == pci_id)
			वापस &dsp_ops[i];
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक skl_init_dsp(काष्ठा skl_dev *skl)
अणु
	व्योम __iomem *mmio_base;
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	काष्ठा skl_dsp_loader_ops loader_ops;
	पूर्णांक irq = bus->irq;
	स्थिर काष्ठा skl_dsp_ops *ops;
	काष्ठा skl_dsp_cores *cores;
	पूर्णांक ret;

	/* enable ppcap पूर्णांकerrupt */
	snd_hdac_ext_bus_ppcap_enable(bus, true);
	snd_hdac_ext_bus_ppcap_पूर्णांक_enable(bus, true);

	/* पढ़ो the BAR of the ADSP MMIO */
	mmio_base = pci_ioremap_bar(skl->pci, 4);
	अगर (mmio_base == शून्य) अणु
		dev_err(bus->dev, "ioremap error\n");
		वापस -ENXIO;
	पूर्ण

	ops = skl_get_dsp_ops(skl->pci->device);
	अगर (!ops) अणु
		ret = -EIO;
		जाओ unmap_mmio;
	पूर्ण

	loader_ops = ops->loader_ops();
	ret = ops->init(bus->dev, mmio_base, irq,
				skl->fw_name, loader_ops,
				&skl);

	अगर (ret < 0)
		जाओ unmap_mmio;

	skl->dsp_ops = ops;
	cores = &skl->cores;
	cores->count = ops->num_cores;

	cores->state = kसुस्मृति(cores->count, माप(*cores->state), GFP_KERNEL);
	अगर (!cores->state) अणु
		ret = -ENOMEM;
		जाओ unmap_mmio;
	पूर्ण

	cores->usage_count = kसुस्मृति(cores->count, माप(*cores->usage_count),
				     GFP_KERNEL);
	अगर (!cores->usage_count) अणु
		ret = -ENOMEM;
		जाओ मुक्त_core_state;
	पूर्ण

	dev_dbg(bus->dev, "dsp registration status=%d\n", ret);

	वापस 0;

मुक्त_core_state:
	kमुक्त(cores->state);

unmap_mmio:
	iounmap(mmio_base);

	वापस ret;
पूर्ण

पूर्णांक skl_मुक्त_dsp(काष्ठा skl_dev *skl)
अणु
	काष्ठा hdac_bus *bus = skl_to_bus(skl);

	/* disable  ppcap पूर्णांकerrupt */
	snd_hdac_ext_bus_ppcap_पूर्णांक_enable(bus, false);

	skl->dsp_ops->cleanup(bus->dev, skl);

	kमुक्त(skl->cores.state);
	kमुक्त(skl->cores.usage_count);

	अगर (skl->dsp->addr.lpe)
		iounmap(skl->dsp->addr.lpe);

	वापस 0;
पूर्ण

/*
 * In the हाल of "suspend_active" i.e, the Audio IP being active
 * during प्रणाली suspend, immediately excecute any pending D0i3 work
 * beक्रमe suspending. This is needed क्रम the IP to work in low घातer
 * mode during प्रणाली suspend. In the हाल of normal suspend, cancel
 * any pending D0i3 work.
 */
पूर्णांक skl_suspend_late_dsp(काष्ठा skl_dev *skl)
अणु
	काष्ठा delayed_work *dwork;

	अगर (!skl)
		वापस 0;

	dwork = &skl->d0i3.work;

	अगर (dwork->work.func) अणु
		अगर (skl->supend_active)
			flush_delayed_work(dwork);
		अन्यथा
			cancel_delayed_work_sync(dwork);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक skl_suspend_dsp(काष्ठा skl_dev *skl)
अणु
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	पूर्णांक ret;

	/* अगर ppcap is not supported वापस 0 */
	अगर (!bus->ppcap)
		वापस 0;

	ret = skl_dsp_sleep(skl->dsp);
	अगर (ret < 0)
		वापस ret;

	/* disable ppcap पूर्णांकerrupt */
	snd_hdac_ext_bus_ppcap_पूर्णांक_enable(bus, false);
	snd_hdac_ext_bus_ppcap_enable(bus, false);

	वापस 0;
पूर्ण

पूर्णांक skl_resume_dsp(काष्ठा skl_dev *skl)
अणु
	काष्ठा hdac_bus *bus = skl_to_bus(skl);
	पूर्णांक ret;

	/* अगर ppcap is not supported वापस 0 */
	अगर (!bus->ppcap)
		वापस 0;

	/* enable ppcap पूर्णांकerrupt */
	snd_hdac_ext_bus_ppcap_enable(bus, true);
	snd_hdac_ext_bus_ppcap_पूर्णांक_enable(bus, true);

	/* check अगर DSP 1st boot is करोne */
	अगर (skl->is_first_boot)
		वापस 0;

	/*
	 * Disable dynamic घड़ी and घातer gating during firmware
	 * and library करोwnload
	 */
	skl->enable_miscbdcge(skl->dev, false);
	skl->घड़ी_घातer_gating(skl->dev, false);

	ret = skl_dsp_wake(skl->dsp);
	skl->enable_miscbdcge(skl->dev, true);
	skl->घड़ी_घातer_gating(skl->dev, true);
	अगर (ret < 0)
		वापस ret;

	अगर (skl->cfg.astate_cfg != शून्य) अणु
		skl_dsp_set_astate_cfg(skl, skl->cfg.astate_cfg->count,
					skl->cfg.astate_cfg);
	पूर्ण
	वापस ret;
पूर्ण

क्रमागत skl_bitdepth skl_get_bit_depth(पूर्णांक params)
अणु
	चयन (params) अणु
	हाल 8:
		वापस SKL_DEPTH_8BIT;

	हाल 16:
		वापस SKL_DEPTH_16BIT;

	हाल 24:
		वापस SKL_DEPTH_24BIT;

	हाल 32:
		वापस SKL_DEPTH_32BIT;

	शेष:
		वापस SKL_DEPTH_INVALID;

	पूर्ण
पूर्ण

/*
 * Each module in DSP expects a base module configuration, which consists of
 * PCM क्रमmat inक्रमmation, which we calculate in driver and resource values
 * which are पढ़ो from widget inक्रमmation passed through topology binary
 * This is send when we create a module with INIT_INSTANCE IPC msg
 */
अटल व्योम skl_set_base_module_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_base_cfg *base_cfg)
अणु
	काष्ठा skl_module *module = mconfig->module;
	काष्ठा skl_module_res *res = &module->resources[mconfig->res_idx];
	काष्ठा skl_module_अगरace *fmt = &module->क्रमmats[mconfig->fmt_idx];
	काष्ठा skl_module_fmt *क्रमmat = &fmt->inमाला_दो[0].fmt;

	base_cfg->audio_fmt.number_of_channels = क्रमmat->channels;

	base_cfg->audio_fmt.s_freq = क्रमmat->s_freq;
	base_cfg->audio_fmt.bit_depth = क्रमmat->bit_depth;
	base_cfg->audio_fmt.valid_bit_depth = क्रमmat->valid_bit_depth;
	base_cfg->audio_fmt.ch_cfg = क्रमmat->ch_cfg;
	base_cfg->audio_fmt.sample_type = क्रमmat->sample_type;

	dev_dbg(skl->dev, "bit_depth=%x valid_bd=%x ch_config=%x\n",
			क्रमmat->bit_depth, क्रमmat->valid_bit_depth,
			क्रमmat->ch_cfg);

	base_cfg->audio_fmt.channel_map = क्रमmat->ch_map;

	base_cfg->audio_fmt.पूर्णांकerleaving = क्रमmat->पूर्णांकerleaving_style;

	base_cfg->cpc = res->cpc;
	base_cfg->ibs = res->ibs;
	base_cfg->obs = res->obs;
	base_cfg->is_pages = res->is_pages;
पूर्ण

/*
 * Copies copier capabilities पूर्णांकo copier module and updates copier module
 * config size.
 */
अटल व्योम skl_copy_copier_caps(काष्ठा skl_module_cfg *mconfig,
				काष्ठा skl_cpr_cfg *cpr_mconfig)
अणु
	अगर (mconfig->क्रमmats_config.caps_size == 0)
		वापस;

	स_नकल(cpr_mconfig->gtw_cfg.config_data,
			mconfig->क्रमmats_config.caps,
			mconfig->क्रमmats_config.caps_size);

	cpr_mconfig->gtw_cfg.config_length =
			(mconfig->क्रमmats_config.caps_size) / 4;
पूर्ण

#घोषणा SKL_NON_GATEWAY_CPR_NODE_ID 0xFFFFFFFF
/*
 * Calculate the gatewat settings required क्रम copier module, type of
 * gateway and index of gateway to use
 */
अटल u32 skl_get_node_id(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig)
अणु
	जोड़ skl_connector_node_id node_id = अणु0पूर्ण;
	जोड़ skl_ssp_dma_node ssp_node  = अणु0पूर्ण;
	काष्ठा skl_pipe_params *params = mconfig->pipe->p_params;

	चयन (mconfig->dev_type) अणु
	हाल SKL_DEVICE_BT:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_I2S_LINK_OUTPUT_CLASS :
			SKL_DMA_I2S_LINK_INPUT_CLASS;
		node_id.node.vindex = params->host_dma_id +
					(mconfig->vbus_id << 3);
		अवरोध;

	हाल SKL_DEVICE_I2S:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_I2S_LINK_OUTPUT_CLASS :
			SKL_DMA_I2S_LINK_INPUT_CLASS;
		ssp_node.dma_node.समय_slot_index = mconfig->समय_slot;
		ssp_node.dma_node.i2s_instance = mconfig->vbus_id;
		node_id.node.vindex = ssp_node.val;
		अवरोध;

	हाल SKL_DEVICE_DMIC:
		node_id.node.dma_type = SKL_DMA_DMIC_LINK_INPUT_CLASS;
		node_id.node.vindex = mconfig->vbus_id +
					 (mconfig->समय_slot);
		अवरोध;

	हाल SKL_DEVICE_HDALINK:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_HDA_LINK_OUTPUT_CLASS :
			SKL_DMA_HDA_LINK_INPUT_CLASS;
		node_id.node.vindex = params->link_dma_id;
		अवरोध;

	हाल SKL_DEVICE_HDAHOST:
		node_id.node.dma_type =
			(SKL_CONN_SOURCE == mconfig->hw_conn_type) ?
			SKL_DMA_HDA_HOST_OUTPUT_CLASS :
			SKL_DMA_HDA_HOST_INPUT_CLASS;
		node_id.node.vindex = params->host_dma_id;
		अवरोध;

	शेष:
		node_id.val = 0xFFFFFFFF;
		अवरोध;
	पूर्ण

	वापस node_id.val;
पूर्ण

अटल व्योम skl_setup_cpr_gateway_cfg(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_cpr_cfg *cpr_mconfig)
अणु
	u32 dma_io_buf;
	काष्ठा skl_module_res *res;
	पूर्णांक res_idx = mconfig->res_idx;

	cpr_mconfig->gtw_cfg.node_id = skl_get_node_id(skl, mconfig);

	अगर (cpr_mconfig->gtw_cfg.node_id == SKL_NON_GATEWAY_CPR_NODE_ID) अणु
		cpr_mconfig->cpr_feature_mask = 0;
		वापस;
	पूर्ण

	अगर (skl->nr_modules) अणु
		res = &mconfig->module->resources[mconfig->res_idx];
		cpr_mconfig->gtw_cfg.dma_buffer_size = res->dma_buffer_size;
		जाओ skip_buf_size_calc;
	पूर्ण अन्यथा अणु
		res = &mconfig->module->resources[res_idx];
	पूर्ण

	चयन (mconfig->hw_conn_type) अणु
	हाल SKL_CONN_SOURCE:
		अगर (mconfig->dev_type == SKL_DEVICE_HDAHOST)
			dma_io_buf =  res->ibs;
		अन्यथा
			dma_io_buf =  res->obs;
		अवरोध;

	हाल SKL_CONN_SINK:
		अगर (mconfig->dev_type == SKL_DEVICE_HDAHOST)
			dma_io_buf =  res->obs;
		अन्यथा
			dma_io_buf =  res->ibs;
		अवरोध;

	शेष:
		dev_warn(skl->dev, "wrong connection type: %d\n",
				mconfig->hw_conn_type);
		वापस;
	पूर्ण

	cpr_mconfig->gtw_cfg.dma_buffer_size =
				mconfig->dma_buffer_size * dma_io_buf;

	/* fallback to 2ms शेष value */
	अगर (!cpr_mconfig->gtw_cfg.dma_buffer_size) अणु
		अगर (mconfig->hw_conn_type == SKL_CONN_SOURCE)
			cpr_mconfig->gtw_cfg.dma_buffer_size = 2 * res->obs;
		अन्यथा
			cpr_mconfig->gtw_cfg.dma_buffer_size = 2 * res->ibs;
	पूर्ण

skip_buf_size_calc:
	cpr_mconfig->cpr_feature_mask = 0;
	cpr_mconfig->gtw_cfg.config_length  = 0;

	skl_copy_copier_caps(mconfig, cpr_mconfig);
पूर्ण

#घोषणा DMA_CONTROL_ID 5
#घोषणा DMA_I2S_BLOB_SIZE 21

पूर्णांक skl_dsp_set_dma_control(काष्ठा skl_dev *skl, u32 *caps,
				u32 caps_size, u32 node_id)
अणु
	काष्ठा skl_dma_control *dma_ctrl;
	काष्ठा skl_ipc_large_config_msg msg = अणु0पूर्ण;
	पूर्णांक err = 0;


	/*
	 * अगर blob size zero, then वापस
	 */
	अगर (caps_size == 0)
		वापस 0;

	msg.large_param_id = DMA_CONTROL_ID;
	msg.param_data_size = माप(काष्ठा skl_dma_control) + caps_size;

	dma_ctrl = kzalloc(msg.param_data_size, GFP_KERNEL);
	अगर (dma_ctrl == शून्य)
		वापस -ENOMEM;

	dma_ctrl->node_id = node_id;

	/*
	 * NHLT blob may contain additional configs aदीर्घ with i2s blob.
	 * firmware expects only the i2s blob size as the config_length.
	 * So fix to i2s blob size.
	 * size in dwords.
	 */
	dma_ctrl->config_length = DMA_I2S_BLOB_SIZE;

	स_नकल(dma_ctrl->config_data, caps, caps_size);

	err = skl_ipc_set_large_config(&skl->ipc, &msg, (u32 *)dma_ctrl);

	kमुक्त(dma_ctrl);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(skl_dsp_set_dma_control);

अटल व्योम skl_setup_out_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_audio_data_क्रमmat *out_fmt)
अणु
	काष्ठा skl_module *module = mconfig->module;
	काष्ठा skl_module_अगरace *fmt = &module->क्रमmats[mconfig->fmt_idx];
	काष्ठा skl_module_fmt *क्रमmat = &fmt->outमाला_दो[0].fmt;

	out_fmt->number_of_channels = (u8)क्रमmat->channels;
	out_fmt->s_freq = क्रमmat->s_freq;
	out_fmt->bit_depth = क्रमmat->bit_depth;
	out_fmt->valid_bit_depth = क्रमmat->valid_bit_depth;
	out_fmt->ch_cfg = क्रमmat->ch_cfg;

	out_fmt->channel_map = क्रमmat->ch_map;
	out_fmt->पूर्णांकerleaving = क्रमmat->पूर्णांकerleaving_style;
	out_fmt->sample_type = क्रमmat->sample_type;

	dev_dbg(skl->dev, "copier out format chan=%d fre=%d bitdepth=%d\n",
		out_fmt->number_of_channels, क्रमmat->s_freq, क्रमmat->bit_depth);
पूर्ण

/*
 * DSP needs SRC module क्रम frequency conversion, SRC takes base module
 * configuration and the target frequency as extra parameter passed as src
 * config
 */
अटल व्योम skl_set_src_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_src_module_cfg *src_mconfig)
अणु
	काष्ठा skl_module *module = mconfig->module;
	काष्ठा skl_module_अगरace *अगरace = &module->क्रमmats[mconfig->fmt_idx];
	काष्ठा skl_module_fmt *fmt = &अगरace->outमाला_दो[0].fmt;

	skl_set_base_module_क्रमmat(skl, mconfig,
		(काष्ठा skl_base_cfg *)src_mconfig);

	src_mconfig->src_cfg = fmt->s_freq;
पूर्ण

/*
 * DSP needs upकरोwn module to करो channel conversion. upकरोwn module take base
 * module configuration and channel configuration
 * It also take coefficients and now we have शेषs applied here
 */
अटल व्योम skl_set_upकरोwn_mixer_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_up_करोwn_mixer_cfg *mixer_mconfig)
अणु
	काष्ठा skl_module *module = mconfig->module;
	काष्ठा skl_module_अगरace *अगरace = &module->क्रमmats[mconfig->fmt_idx];
	काष्ठा skl_module_fmt *fmt = &अगरace->outमाला_दो[0].fmt;

	skl_set_base_module_क्रमmat(skl,	mconfig,
		(काष्ठा skl_base_cfg *)mixer_mconfig);
	mixer_mconfig->out_ch_cfg = fmt->ch_cfg;
	mixer_mconfig->ch_map = fmt->ch_map;
पूर्ण

/*
 * 'copier' is DSP पूर्णांकernal module which copies data from Host DMA (HDA host
 * dma) or link (hda link, SSP, PDM)
 * Here we calculate the copier module parameters, like PCM क्रमmat, output
 * क्रमmat, gateway settings
 * copier_module_config is sent as input buffer with INIT_INSTANCE IPC msg
 */
अटल व्योम skl_set_copier_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_cpr_cfg *cpr_mconfig)
अणु
	काष्ठा skl_audio_data_क्रमmat *out_fmt = &cpr_mconfig->out_fmt;
	काष्ठा skl_base_cfg *base_cfg = (काष्ठा skl_base_cfg *)cpr_mconfig;

	skl_set_base_module_क्रमmat(skl, mconfig, base_cfg);

	skl_setup_out_क्रमmat(skl, mconfig, out_fmt);
	skl_setup_cpr_gateway_cfg(skl, mconfig, cpr_mconfig);
पूर्ण

/*
 * Algo module are DSP pre processing modules. Algo module take base module
 * configuration and params
 */

अटल व्योम skl_set_algo_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_algo_cfg *algo_mcfg)
अणु
	काष्ठा skl_base_cfg *base_cfg = (काष्ठा skl_base_cfg *)algo_mcfg;

	skl_set_base_module_क्रमmat(skl, mconfig, base_cfg);

	अगर (mconfig->क्रमmats_config.caps_size == 0)
		वापस;

	स_नकल(algo_mcfg->params,
			mconfig->क्रमmats_config.caps,
			mconfig->क्रमmats_config.caps_size);

पूर्ण

/*
 * Mic select module allows selecting one or many input channels, thus
 * acting as a demux.
 *
 * Mic select module take base module configuration and out-क्रमmat
 * configuration
 */
अटल व्योम skl_set_base_outfmt_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig,
			काष्ठा skl_base_outfmt_cfg *base_outfmt_mcfg)
अणु
	काष्ठा skl_audio_data_क्रमmat *out_fmt = &base_outfmt_mcfg->out_fmt;
	काष्ठा skl_base_cfg *base_cfg =
				(काष्ठा skl_base_cfg *)base_outfmt_mcfg;

	skl_set_base_module_क्रमmat(skl, mconfig, base_cfg);
	skl_setup_out_क्रमmat(skl, mconfig, out_fmt);
पूर्ण

अटल u16 skl_get_module_param_size(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig)
अणु
	u16 param_size;

	चयन (mconfig->m_type) अणु
	हाल SKL_MODULE_TYPE_COPIER:
		param_size = माप(काष्ठा skl_cpr_cfg);
		param_size += mconfig->क्रमmats_config.caps_size;
		वापस param_size;

	हाल SKL_MODULE_TYPE_SRCINT:
		वापस माप(काष्ठा skl_src_module_cfg);

	हाल SKL_MODULE_TYPE_UPDWMIX:
		वापस माप(काष्ठा skl_up_करोwn_mixer_cfg);

	हाल SKL_MODULE_TYPE_ALGO:
		param_size = माप(काष्ठा skl_base_cfg);
		param_size += mconfig->क्रमmats_config.caps_size;
		वापस param_size;

	हाल SKL_MODULE_TYPE_BASE_OUTFMT:
	हाल SKL_MODULE_TYPE_MIC_SELECT:
	हाल SKL_MODULE_TYPE_KPB:
		वापस माप(काष्ठा skl_base_outfmt_cfg);

	शेष:
		/*
		 * वापस only base cfg when no specअगरic module type is
		 * specअगरied
		 */
		वापस माप(काष्ठा skl_base_cfg);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * DSP firmware supports various modules like copier, SRC, upकरोwn etc.
 * These modules required various parameters to be calculated and sent क्रम
 * the module initialization to DSP. By शेष a generic module needs only
 * base module क्रमmat configuration
 */

अटल पूर्णांक skl_set_module_क्रमmat(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *module_config,
			u16 *module_config_size,
			व्योम **param_data)
अणु
	u16 param_size;

	param_size  = skl_get_module_param_size(skl, module_config);

	*param_data = kzalloc(param_size, GFP_KERNEL);
	अगर (शून्य == *param_data)
		वापस -ENOMEM;

	*module_config_size = param_size;

	चयन (module_config->m_type) अणु
	हाल SKL_MODULE_TYPE_COPIER:
		skl_set_copier_क्रमmat(skl, module_config, *param_data);
		अवरोध;

	हाल SKL_MODULE_TYPE_SRCINT:
		skl_set_src_क्रमmat(skl, module_config, *param_data);
		अवरोध;

	हाल SKL_MODULE_TYPE_UPDWMIX:
		skl_set_upकरोwn_mixer_क्रमmat(skl, module_config, *param_data);
		अवरोध;

	हाल SKL_MODULE_TYPE_ALGO:
		skl_set_algo_क्रमmat(skl, module_config, *param_data);
		अवरोध;

	हाल SKL_MODULE_TYPE_BASE_OUTFMT:
	हाल SKL_MODULE_TYPE_MIC_SELECT:
	हाल SKL_MODULE_TYPE_KPB:
		skl_set_base_outfmt_क्रमmat(skl, module_config, *param_data);
		अवरोध;

	शेष:
		skl_set_base_module_क्रमmat(skl, module_config, *param_data);
		अवरोध;

	पूर्ण

	dev_dbg(skl->dev, "Module type=%d id=%d config size: %d bytes\n",
			module_config->m_type, module_config->id.module_id,
			param_size);
	prपूर्णांक_hex_dump_debug("Module params:", DUMP_PREFIX_OFFSET, 8, 4,
			*param_data, param_size, false);
	वापस 0;
पूर्ण

अटल पूर्णांक skl_get_queue_index(काष्ठा skl_module_pin *mpin,
				काष्ठा skl_module_inst_id id, पूर्णांक max)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < max; i++)  अणु
		अगर (mpin[i].id.module_id == id.module_id &&
			mpin[i].id.instance_id == id.instance_id)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Allocates queue क्रम each module.
 * अगर dynamic, the pin_index is allocated 0 to max_pin.
 * In अटल, the pin_index is fixed based on module_id and instance id
 */
अटल पूर्णांक skl_alloc_queue(काष्ठा skl_module_pin *mpin,
			काष्ठा skl_module_cfg *tgt_cfg, पूर्णांक max)
अणु
	पूर्णांक i;
	काष्ठा skl_module_inst_id id = tgt_cfg->id;
	/*
	 * अगर pin in dynamic, find first मुक्त pin
	 * otherwise find match module and instance id pin as topology will
	 * ensure a unique pin is asचिन्हित to this so no need to
	 * allocate/मुक्त
	 */
	क्रम (i = 0; i < max; i++)  अणु
		अगर (mpin[i].is_dynamic) अणु
			अगर (!mpin[i].in_use &&
				mpin[i].pin_state == SKL_PIN_UNBIND) अणु

				mpin[i].in_use = true;
				mpin[i].id.module_id = id.module_id;
				mpin[i].id.instance_id = id.instance_id;
				mpin[i].id.pvt_id = id.pvt_id;
				mpin[i].tgt_mcfg = tgt_cfg;
				वापस i;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mpin[i].id.module_id == id.module_id &&
				mpin[i].id.instance_id == id.instance_id &&
				mpin[i].pin_state == SKL_PIN_UNBIND) अणु

				mpin[i].tgt_mcfg = tgt_cfg;
				वापस i;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम skl_मुक्त_queue(काष्ठा skl_module_pin *mpin, पूर्णांक q_index)
अणु
	अगर (mpin[q_index].is_dynamic) अणु
		mpin[q_index].in_use = false;
		mpin[q_index].id.module_id = 0;
		mpin[q_index].id.instance_id = 0;
		mpin[q_index].id.pvt_id = 0;
	पूर्ण
	mpin[q_index].pin_state = SKL_PIN_UNBIND;
	mpin[q_index].tgt_mcfg = शून्य;
पूर्ण

/* Module state will be set to unपूर्णांक, अगर all the out pin state is UNBIND */

अटल व्योम skl_clear_module_state(काष्ठा skl_module_pin *mpin, पूर्णांक max,
						काष्ठा skl_module_cfg *mcfg)
अणु
	पूर्णांक i;
	bool found = false;

	क्रम (i = 0; i < max; i++)  अणु
		अगर (mpin[i].pin_state == SKL_PIN_UNBIND)
			जारी;
		found = true;
		अवरोध;
	पूर्ण

	अगर (!found)
		mcfg->m_state = SKL_MODULE_INIT_DONE;
	वापस;
पूर्ण

/*
 * A module needs to be instanataited in DSP. A mकरोule is present in a
 * collection of module referred as a PIPE.
 * We first calculate the module क्रमmat, based on module type and then
 * invoke the DSP by sending IPC INIT_INSTANCE using ipc helper
 */
पूर्णांक skl_init_module(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *mconfig)
अणु
	u16 module_config_size = 0;
	व्योम *param_data = शून्य;
	पूर्णांक ret;
	काष्ठा skl_ipc_init_instance_msg msg;

	dev_dbg(skl->dev, "%s: module_id = %d instance=%d\n", __func__,
		 mconfig->id.module_id, mconfig->id.pvt_id);

	अगर (mconfig->pipe->state != SKL_PIPE_CREATED) अणु
		dev_err(skl->dev, "Pipe not created state= %d pipe_id= %d\n",
				 mconfig->pipe->state, mconfig->pipe->ppl_id);
		वापस -EIO;
	पूर्ण

	ret = skl_set_module_क्रमmat(skl, mconfig,
			&module_config_size, &param_data);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to set module format ret=%d\n", ret);
		वापस ret;
	पूर्ण

	msg.module_id = mconfig->id.module_id;
	msg.instance_id = mconfig->id.pvt_id;
	msg.ppl_instance_id = mconfig->pipe->ppl_id;
	msg.param_data_size = module_config_size;
	msg.core_id = mconfig->core_id;
	msg.करोमुख्य = mconfig->करोमुख्य;

	ret = skl_ipc_init_instance(&skl->ipc, &msg, param_data);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to init instance ret=%d\n", ret);
		kमुक्त(param_data);
		वापस ret;
	पूर्ण
	mconfig->m_state = SKL_MODULE_INIT_DONE;
	kमुक्त(param_data);
	वापस ret;
पूर्ण

अटल व्योम skl_dump_bind_info(काष्ठा skl_dev *skl, काष्ठा skl_module_cfg
	*src_module, काष्ठा skl_module_cfg *dst_module)
अणु
	dev_dbg(skl->dev, "%s: src module_id = %d  src_instance=%d\n",
		__func__, src_module->id.module_id, src_module->id.pvt_id);
	dev_dbg(skl->dev, "%s: dst_module=%d dst_instance=%d\n", __func__,
		 dst_module->id.module_id, dst_module->id.pvt_id);

	dev_dbg(skl->dev, "src_module state = %d dst module state = %d\n",
		src_module->m_state, dst_module->m_state);
पूर्ण

/*
 * On module मुक्तup, we need to unbind the module with modules
 * it is alपढ़ोy bind.
 * Find the pin allocated and unbind then using bind_unbind IPC
 */
पूर्णांक skl_unbind_modules(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *src_mcfg,
			काष्ठा skl_module_cfg *dst_mcfg)
अणु
	पूर्णांक ret;
	काष्ठा skl_ipc_bind_unbind_msg msg;
	काष्ठा skl_module_inst_id src_id = src_mcfg->id;
	काष्ठा skl_module_inst_id dst_id = dst_mcfg->id;
	पूर्णांक in_max = dst_mcfg->module->max_input_pins;
	पूर्णांक out_max = src_mcfg->module->max_output_pins;
	पूर्णांक src_index, dst_index, src_pin_state, dst_pin_state;

	skl_dump_bind_info(skl, src_mcfg, dst_mcfg);

	/* get src queue index */
	src_index = skl_get_queue_index(src_mcfg->m_out_pin, dst_id, out_max);
	अगर (src_index < 0)
		वापस 0;

	msg.src_queue = src_index;

	/* get dst queue index */
	dst_index  = skl_get_queue_index(dst_mcfg->m_in_pin, src_id, in_max);
	अगर (dst_index < 0)
		वापस 0;

	msg.dst_queue = dst_index;

	src_pin_state = src_mcfg->m_out_pin[src_index].pin_state;
	dst_pin_state = dst_mcfg->m_in_pin[dst_index].pin_state;

	अगर (src_pin_state != SKL_PIN_BIND_DONE ||
		dst_pin_state != SKL_PIN_BIND_DONE)
		वापस 0;

	msg.module_id = src_mcfg->id.module_id;
	msg.instance_id = src_mcfg->id.pvt_id;
	msg.dst_module_id = dst_mcfg->id.module_id;
	msg.dst_instance_id = dst_mcfg->id.pvt_id;
	msg.bind = false;

	ret = skl_ipc_bind_unbind(&skl->ipc, &msg);
	अगर (!ret) अणु
		/* मुक्त queue only अगर unbind is success */
		skl_मुक्त_queue(src_mcfg->m_out_pin, src_index);
		skl_मुक्त_queue(dst_mcfg->m_in_pin, dst_index);

		/*
		 * check only अगर src module bind state, bind is
		 * always from src -> sink
		 */
		skl_clear_module_state(src_mcfg->m_out_pin, out_max, src_mcfg);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम fill_pin_params(काष्ठा skl_audio_data_क्रमmat *pin_fmt,
				काष्ठा skl_module_fmt *क्रमmat)
अणु
	pin_fmt->number_of_channels = क्रमmat->channels;
	pin_fmt->s_freq = क्रमmat->s_freq;
	pin_fmt->bit_depth = क्रमmat->bit_depth;
	pin_fmt->valid_bit_depth = क्रमmat->valid_bit_depth;
	pin_fmt->ch_cfg = क्रमmat->ch_cfg;
	pin_fmt->sample_type = क्रमmat->sample_type;
	pin_fmt->channel_map = क्रमmat->ch_map;
	pin_fmt->पूर्णांकerleaving = क्रमmat->पूर्णांकerleaving_style;
पूर्ण

#घोषणा CPR_SINK_FMT_PARAM_ID 2

/*
 * Once a module is instantiated it need to be 'bind' with other modules in
 * the pipeline. For binding we need to find the module pins which are bind
 * together
 * This function finds the pins and then sends bund_unbind IPC message to
 * DSP using IPC helper
 */
पूर्णांक skl_bind_modules(काष्ठा skl_dev *skl,
			काष्ठा skl_module_cfg *src_mcfg,
			काष्ठा skl_module_cfg *dst_mcfg)
अणु
	पूर्णांक ret = 0;
	काष्ठा skl_ipc_bind_unbind_msg msg;
	पूर्णांक in_max = dst_mcfg->module->max_input_pins;
	पूर्णांक out_max = src_mcfg->module->max_output_pins;
	पूर्णांक src_index, dst_index;
	काष्ठा skl_module_fmt *क्रमmat;
	काष्ठा skl_cpr_pin_fmt pin_fmt;
	काष्ठा skl_module *module;
	काष्ठा skl_module_अगरace *fmt;

	skl_dump_bind_info(skl, src_mcfg, dst_mcfg);

	अगर (src_mcfg->m_state < SKL_MODULE_INIT_DONE ||
		dst_mcfg->m_state < SKL_MODULE_INIT_DONE)
		वापस 0;

	src_index = skl_alloc_queue(src_mcfg->m_out_pin, dst_mcfg, out_max);
	अगर (src_index < 0)
		वापस -EINVAL;

	msg.src_queue = src_index;
	dst_index = skl_alloc_queue(dst_mcfg->m_in_pin, src_mcfg, in_max);
	अगर (dst_index < 0) अणु
		skl_मुक्त_queue(src_mcfg->m_out_pin, src_index);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Copier module requires the separate large_config_set_ipc to
	 * configure the pins other than 0
	 */
	अगर (src_mcfg->m_type == SKL_MODULE_TYPE_COPIER && src_index > 0) अणु
		pin_fmt.sink_id = src_index;
		module = src_mcfg->module;
		fmt = &module->क्रमmats[src_mcfg->fmt_idx];

		/* Input fmt is same as that of src module input cfg */
		क्रमmat = &fmt->inमाला_दो[0].fmt;
		fill_pin_params(&(pin_fmt.src_fmt), क्रमmat);

		क्रमmat = &fmt->outमाला_दो[src_index].fmt;
		fill_pin_params(&(pin_fmt.dst_fmt), क्रमmat);
		ret = skl_set_module_params(skl, (व्योम *)&pin_fmt,
					माप(काष्ठा skl_cpr_pin_fmt),
					CPR_SINK_FMT_PARAM_ID, src_mcfg);

		अगर (ret < 0)
			जाओ out;
	पूर्ण

	msg.dst_queue = dst_index;

	dev_dbg(skl->dev, "src queue = %d dst queue =%d\n",
			 msg.src_queue, msg.dst_queue);

	msg.module_id = src_mcfg->id.module_id;
	msg.instance_id = src_mcfg->id.pvt_id;
	msg.dst_module_id = dst_mcfg->id.module_id;
	msg.dst_instance_id = dst_mcfg->id.pvt_id;
	msg.bind = true;

	ret = skl_ipc_bind_unbind(&skl->ipc, &msg);

	अगर (!ret) अणु
		src_mcfg->m_state = SKL_MODULE_BIND_DONE;
		src_mcfg->m_out_pin[src_index].pin_state = SKL_PIN_BIND_DONE;
		dst_mcfg->m_in_pin[dst_index].pin_state = SKL_PIN_BIND_DONE;
		वापस ret;
	पूर्ण
out:
	/* error हाल , अगर IPC fails, clear the queue index */
	skl_मुक्त_queue(src_mcfg->m_out_pin, src_index);
	skl_मुक्त_queue(dst_mcfg->m_in_pin, dst_index);

	वापस ret;
पूर्ण

अटल पूर्णांक skl_set_pipe_state(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe,
	क्रमागत skl_ipc_pipeline_state state)
अणु
	dev_dbg(skl->dev, "%s: pipe_state = %d\n", __func__, state);

	वापस skl_ipc_set_pipeline_state(&skl->ipc, pipe->ppl_id, state);
पूर्ण

/*
 * A pipeline is a collection of modules. Beक्रमe a module in instantiated a
 * pipeline needs to be created क्रम it.
 * This function creates pipeline, by sending create pipeline IPC messages
 * to FW
 */
पूर्णांक skl_create_pipeline(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	पूर्णांक ret;

	dev_dbg(skl->dev, "%s: pipe_id = %d\n", __func__, pipe->ppl_id);

	ret = skl_ipc_create_pipeline(&skl->ipc, pipe->memory_pages,
				pipe->pipe_priority, pipe->ppl_id,
				pipe->lp_mode);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to create pipeline\n");
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_CREATED;

	वापस 0;
पूर्ण

/*
 * A pipeline needs to be deleted on cleanup. If a pipeline is running,
 * then छोड़ो it first. Beक्रमe actual deletion, pipeline should enter
 * reset state. Finish the procedure by sending delete pipeline IPC.
 * DSP will stop the DMA engines and release resources
 */
पूर्णांक skl_delete_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	पूर्णांक ret;

	dev_dbg(skl->dev, "%s: pipe = %d\n", __func__, pipe->ppl_id);

	/* If pipe was not created in FW, करो not try to delete it */
	अगर (pipe->state < SKL_PIPE_CREATED)
		वापस 0;

	/* If pipe is started, करो stop the pipe in FW. */
	अगर (pipe->state >= SKL_PIPE_STARTED) अणु
		ret = skl_set_pipe_state(skl, pipe, PPL_PAUSED);
		अगर (ret < 0) अणु
			dev_err(skl->dev, "Failed to stop pipeline\n");
			वापस ret;
		पूर्ण

		pipe->state = SKL_PIPE_PAUSED;
	पूर्ण

	/* reset pipe state beक्रमe deletion */
	ret = skl_set_pipe_state(skl, pipe, PPL_RESET);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to reset pipe ret=%d\n", ret);
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_RESET;

	ret = skl_ipc_delete_pipeline(&skl->ipc, pipe->ppl_id);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to delete pipeline\n");
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_INVALID;

	वापस ret;
पूर्ण

/*
 * A pipeline is also a scheduling entity in DSP which can be run, stopped
 * For processing data the pipe need to be run by sending IPC set pipe state
 * to DSP
 */
पूर्णांक skl_run_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	पूर्णांक ret;

	dev_dbg(skl->dev, "%s: pipe = %d\n", __func__, pipe->ppl_id);

	/* If pipe was not created in FW, करो not try to छोड़ो or delete */
	अगर (pipe->state < SKL_PIPE_CREATED)
		वापस 0;

	/* Pipe has to be छोड़ोd beक्रमe it is started */
	ret = skl_set_pipe_state(skl, pipe, PPL_PAUSED);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to pause pipe\n");
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_PAUSED;

	ret = skl_set_pipe_state(skl, pipe, PPL_RUNNING);
	अगर (ret < 0) अणु
		dev_err(skl->dev, "Failed to start pipe\n");
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_STARTED;

	वापस 0;
पूर्ण

/*
 * Stop the pipeline by sending set pipe state IPC
 * DSP करोesnt implement stop so we always send छोड़ो message
 */
पूर्णांक skl_stop_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	पूर्णांक ret;

	dev_dbg(skl->dev, "In %s pipe=%d\n", __func__, pipe->ppl_id);

	/* If pipe was not created in FW, करो not try to छोड़ो or delete */
	अगर (pipe->state < SKL_PIPE_PAUSED)
		वापस 0;

	ret = skl_set_pipe_state(skl, pipe, PPL_PAUSED);
	अगर (ret < 0) अणु
		dev_dbg(skl->dev, "Failed to stop pipe\n");
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_PAUSED;

	वापस 0;
पूर्ण

/*
 * Reset the pipeline by sending set pipe state IPC this will reset the DMA
 * from the DSP side
 */
पूर्णांक skl_reset_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe)
अणु
	पूर्णांक ret;

	/* If pipe was not created in FW, करो not try to छोड़ो or delete */
	अगर (pipe->state < SKL_PIPE_PAUSED)
		वापस 0;

	ret = skl_set_pipe_state(skl, pipe, PPL_RESET);
	अगर (ret < 0) अणु
		dev_dbg(skl->dev, "Failed to reset pipe ret=%d\n", ret);
		वापस ret;
	पूर्ण

	pipe->state = SKL_PIPE_RESET;

	वापस 0;
पूर्ण

/* Algo parameter set helper function */
पूर्णांक skl_set_module_params(काष्ठा skl_dev *skl, u32 *params, पूर्णांक size,
				u32 param_id, काष्ठा skl_module_cfg *mcfg)
अणु
	काष्ठा skl_ipc_large_config_msg msg;

	msg.module_id = mcfg->id.module_id;
	msg.instance_id = mcfg->id.pvt_id;
	msg.param_data_size = size;
	msg.large_param_id = param_id;

	वापस skl_ipc_set_large_config(&skl->ipc, &msg, params);
पूर्ण

पूर्णांक skl_get_module_params(काष्ठा skl_dev *skl, u32 *params, पूर्णांक size,
			  u32 param_id, काष्ठा skl_module_cfg *mcfg)
अणु
	काष्ठा skl_ipc_large_config_msg msg;
	माप_प्रकार bytes = size;

	msg.module_id = mcfg->id.module_id;
	msg.instance_id = mcfg->id.pvt_id;
	msg.param_data_size = size;
	msg.large_param_id = param_id;

	वापस skl_ipc_get_large_config(&skl->ipc, &msg, &params, &bytes);
पूर्ण
