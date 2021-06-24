<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>

#समावेश "core.h"
#समावेश "hfi.h"
#समावेश "hfi_cmds.h"
#समावेश "hfi_venus.h"

#घोषणा TIMEOUT		msecs_to_jअगरfies(1000)

अटल u32 to_codec_type(u32 pixfmt)
अणु
	चयन (pixfmt) अणु
	हाल V4L2_PIX_FMT_H264:
	हाल V4L2_PIX_FMT_H264_NO_SC:
		वापस HFI_VIDEO_CODEC_H264;
	हाल V4L2_PIX_FMT_H263:
		वापस HFI_VIDEO_CODEC_H263;
	हाल V4L2_PIX_FMT_MPEG1:
		वापस HFI_VIDEO_CODEC_MPEG1;
	हाल V4L2_PIX_FMT_MPEG2:
		वापस HFI_VIDEO_CODEC_MPEG2;
	हाल V4L2_PIX_FMT_MPEG4:
		वापस HFI_VIDEO_CODEC_MPEG4;
	हाल V4L2_PIX_FMT_VC1_ANNEX_G:
	हाल V4L2_PIX_FMT_VC1_ANNEX_L:
		वापस HFI_VIDEO_CODEC_VC1;
	हाल V4L2_PIX_FMT_VP8:
		वापस HFI_VIDEO_CODEC_VP8;
	हाल V4L2_PIX_FMT_VP9:
		वापस HFI_VIDEO_CODEC_VP9;
	हाल V4L2_PIX_FMT_XVID:
		वापस HFI_VIDEO_CODEC_DIVX;
	हाल V4L2_PIX_FMT_HEVC:
		वापस HFI_VIDEO_CODEC_HEVC;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक hfi_core_init(काष्ठा venus_core *core)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&core->lock);

	अगर (core->state >= CORE_INIT)
		जाओ unlock;

	reinit_completion(&core->करोne);

	ret = core->ops->core_init(core);
	अगर (ret)
		जाओ unlock;

	ret = रुको_क्रम_completion_समयout(&core->करोne, TIMEOUT);
	अगर (!ret) अणु
		ret = -ETIMEDOUT;
		जाओ unlock;
	पूर्ण

	ret = 0;

	अगर (core->error != HFI_ERR_NONE) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	core->state = CORE_INIT;
unlock:
	mutex_unlock(&core->lock);
	वापस ret;
पूर्ण

पूर्णांक hfi_core_deinit(काष्ठा venus_core *core, bool blocking)
अणु
	पूर्णांक ret = 0, empty;

	mutex_lock(&core->lock);

	अगर (core->state == CORE_UNINIT)
		जाओ unlock;

	empty = list_empty(&core->instances);

	अगर (!empty && !blocking) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (!empty) अणु
		mutex_unlock(&core->lock);
		रुको_var_event(&core->insts_count,
			       !atomic_पढ़ो(&core->insts_count));
		mutex_lock(&core->lock);
	पूर्ण

	ret = core->ops->core_deinit(core);

	अगर (!ret)
		core->state = CORE_UNINIT;

unlock:
	mutex_unlock(&core->lock);
	वापस ret;
पूर्ण

पूर्णांक hfi_core_suspend(काष्ठा venus_core *core)
अणु
	अगर (core->state != CORE_INIT)
		वापस 0;

	वापस core->ops->suspend(core);
पूर्ण

पूर्णांक hfi_core_resume(काष्ठा venus_core *core, bool क्रमce)
अणु
	अगर (!क्रमce && core->state != CORE_INIT)
		वापस 0;

	वापस core->ops->resume(core);
पूर्ण

पूर्णांक hfi_core_trigger_ssr(काष्ठा venus_core *core, u32 type)
अणु
	वापस core->ops->core_trigger_ssr(core, type);
पूर्ण

पूर्णांक hfi_core_ping(काष्ठा venus_core *core)
अणु
	पूर्णांक ret;

	mutex_lock(&core->lock);

	ret = core->ops->core_ping(core, 0xbeef);
	अगर (ret)
		जाओ unlock;

	ret = रुको_क्रम_completion_समयout(&core->करोne, TIMEOUT);
	अगर (!ret) अणु
		ret = -ETIMEDOUT;
		जाओ unlock;
	पूर्ण
	ret = 0;
	अगर (core->error != HFI_ERR_NONE)
		ret = -ENODEV;
unlock:
	mutex_unlock(&core->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक रुको_session_msg(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&inst->करोne, TIMEOUT);
	अगर (!ret)
		वापस -ETIMEDOUT;

	अगर (inst->error != HFI_ERR_NONE)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक hfi_session_create(काष्ठा venus_inst *inst, स्थिर काष्ठा hfi_inst_ops *ops)
अणु
	काष्ठा venus_core *core = inst->core;
	bool max;
	पूर्णांक ret;

	अगर (!ops)
		वापस -EINVAL;

	inst->state = INST_UNINIT;
	init_completion(&inst->करोne);
	inst->ops = ops;

	mutex_lock(&core->lock);

	max = atomic_add_unless(&core->insts_count, 1,
				core->max_sessions_supported);
	अगर (!max) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		list_add_tail(&inst->list, &core->instances);
		ret = 0;
	पूर्ण

	mutex_unlock(&core->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_create);

पूर्णांक hfi_session_init(काष्ठा venus_inst *inst, u32 pixfmt)
अणु
	काष्ठा venus_core *core = inst->core;
	स्थिर काष्ठा hfi_ops *ops = core->ops;
	पूर्णांक ret;

	/*
	 * If core shutकरोwn is in progress or अगर we are in प्रणाली
	 * recovery, वापस an error as during प्रणाली error recovery
	 * session_init() can't pass successfully
	 */
	mutex_lock(&core->lock);
	अगर (!core->ops || core->sys_error) अणु
		mutex_unlock(&core->lock);
		वापस -EIO;
	पूर्ण
	mutex_unlock(&core->lock);

	अगर (inst->state != INST_UNINIT)
		वापस -EALREADY;

	inst->hfi_codec = to_codec_type(pixfmt);
	reinit_completion(&inst->करोne);

	ret = ops->session_init(inst, inst->session_type, inst->hfi_codec);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	inst->state = INST_INIT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_init);

व्योम hfi_session_destroy(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;

	mutex_lock(&core->lock);
	list_del_init(&inst->list);
	अगर (atomic_dec_and_test(&core->insts_count))
		wake_up_var(&core->insts_count);
	mutex_unlock(&core->lock);
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_destroy);

पूर्णांक hfi_session_deinit(काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	अगर (inst->state == INST_UNINIT)
		वापस 0;

	अगर (inst->state < INST_INIT)
		वापस -EINVAL;

	reinit_completion(&inst->करोne);

	ret = ops->session_end(inst);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	inst->state = INST_UNINIT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_deinit);

पूर्णांक hfi_session_start(काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	अगर (inst->state != INST_LOAD_RESOURCES)
		वापस -EINVAL;

	reinit_completion(&inst->करोne);

	ret = ops->session_start(inst);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	inst->state = INST_START;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_start);

पूर्णांक hfi_session_stop(काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	अगर (inst->state != INST_START)
		वापस -EINVAL;

	reinit_completion(&inst->करोne);

	ret = ops->session_stop(inst);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	inst->state = INST_STOP;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_stop);

पूर्णांक hfi_session_जारी(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;

	अगर (core->res->hfi_version == HFI_VERSION_1XX)
		वापस 0;

	वापस core->ops->session_जारी(inst);
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_जारी);

पूर्णांक hfi_session_पात(काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	reinit_completion(&inst->करोne);

	ret = ops->session_पात(inst);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_पात);

पूर्णांक hfi_session_load_res(काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	अगर (inst->state != INST_INIT)
		वापस -EINVAL;

	reinit_completion(&inst->करोne);

	ret = ops->session_load_res(inst);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	inst->state = INST_LOAD_RESOURCES;

	वापस 0;
पूर्ण

पूर्णांक hfi_session_unload_res(काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	अगर (inst->state != INST_STOP)
		वापस -EINVAL;

	reinit_completion(&inst->करोne);

	ret = ops->session_release_res(inst);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	inst->state = INST_RELEASE_RESOURCES;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_unload_res);

पूर्णांक hfi_session_flush(काष्ठा venus_inst *inst, u32 type, bool block)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	reinit_completion(&inst->करोne);

	ret = ops->session_flush(inst, type);
	अगर (ret)
		वापस ret;

	अगर (block) अणु
		ret = रुको_session_msg(inst);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_flush);

पूर्णांक hfi_session_set_buffers(काष्ठा venus_inst *inst, काष्ठा hfi_buffer_desc *bd)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;

	वापस ops->session_set_buffers(inst, bd);
पूर्ण

पूर्णांक hfi_session_unset_buffers(काष्ठा venus_inst *inst,
			      काष्ठा hfi_buffer_desc *bd)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	reinit_completion(&inst->करोne);

	ret = ops->session_unset_buffers(inst, bd);
	अगर (ret)
		वापस ret;

	अगर (!bd->response_required)
		वापस 0;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक hfi_session_get_property(काष्ठा venus_inst *inst, u32 ptype,
			     जोड़ hfi_get_property *hprop)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;
	पूर्णांक ret;

	अगर (inst->state < INST_INIT || inst->state >= INST_STOP)
		वापस -EINVAL;

	reinit_completion(&inst->करोne);

	ret = ops->session_get_property(inst, ptype);
	अगर (ret)
		वापस ret;

	ret = रुको_session_msg(inst);
	अगर (ret)
		वापस ret;

	*hprop = inst->hprop;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_get_property);

पूर्णांक hfi_session_set_property(काष्ठा venus_inst *inst, u32 ptype, व्योम *pdata)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;

	अगर (inst->state < INST_INIT || inst->state >= INST_STOP)
		वापस -EINVAL;

	वापस ops->session_set_property(inst, ptype, pdata);
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_set_property);

पूर्णांक hfi_session_process_buf(काष्ठा venus_inst *inst, काष्ठा hfi_frame_data *fd)
अणु
	स्थिर काष्ठा hfi_ops *ops = inst->core->ops;

	अगर (fd->buffer_type == HFI_BUFFER_INPUT)
		वापस ops->session_etb(inst, fd);
	अन्यथा अगर (fd->buffer_type == HFI_BUFFER_OUTPUT ||
		 fd->buffer_type == HFI_BUFFER_OUTPUT2)
		वापस ops->session_ftb(inst, fd);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(hfi_session_process_buf);

irqवापस_t hfi_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा venus_core *core = dev_id;

	वापस core->ops->isr_thपढ़ो(core);
पूर्ण

irqवापस_t hfi_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा venus_core *core = dev;

	वापस core->ops->isr(core);
पूर्ण

पूर्णांक hfi_create(काष्ठा venus_core *core, स्थिर काष्ठा hfi_core_ops *ops)
अणु
	पूर्णांक ret;

	अगर (!ops)
		वापस -EINVAL;

	atomic_set(&core->insts_count, 0);
	core->core_ops = ops;
	core->state = CORE_UNINIT;
	init_completion(&core->करोne);
	pkt_set_version(core->res->hfi_version);
	ret = venus_hfi_create(core);

	वापस ret;
पूर्ण

व्योम hfi_destroy(काष्ठा venus_core *core)
अणु
	venus_hfi_destroy(core);
पूर्ण

व्योम hfi_reinit(काष्ठा venus_core *core)
अणु
	venus_hfi_queues_reinit(core);
पूर्ण
