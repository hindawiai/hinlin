<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <यंत्र/भाग64.h>

#समावेश "core.h"
#समावेश "helpers.h"
#समावेश "hfi_helper.h"
#समावेश "pm_helpers.h"
#समावेश "hfi_platform.h"
#समावेश "hfi_parser.h"

#घोषणा NUM_MBS_720P	(((1280 + 15) >> 4) * ((720 + 15) >> 4))
#घोषणा NUM_MBS_4K	(((4096 + 15) >> 4) * ((2304 + 15) >> 4))

काष्ठा पूर्णांकbuf अणु
	काष्ठा list_head list;
	u32 type;
	माप_प्रकार size;
	व्योम *va;
	dma_addr_t da;
	अचिन्हित दीर्घ attrs;
पूर्ण;

bool venus_helper_check_codec(काष्ठा venus_inst *inst, u32 v4l2_pixfmt)
अणु
	काष्ठा venus_core *core = inst->core;
	u32 session_type = inst->session_type;
	u32 codec;

	चयन (v4l2_pixfmt) अणु
	हाल V4L2_PIX_FMT_H264:
		codec = HFI_VIDEO_CODEC_H264;
		अवरोध;
	हाल V4L2_PIX_FMT_H263:
		codec = HFI_VIDEO_CODEC_H263;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG1:
		codec = HFI_VIDEO_CODEC_MPEG1;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG2:
		codec = HFI_VIDEO_CODEC_MPEG2;
		अवरोध;
	हाल V4L2_PIX_FMT_MPEG4:
		codec = HFI_VIDEO_CODEC_MPEG4;
		अवरोध;
	हाल V4L2_PIX_FMT_VC1_ANNEX_G:
	हाल V4L2_PIX_FMT_VC1_ANNEX_L:
		codec = HFI_VIDEO_CODEC_VC1;
		अवरोध;
	हाल V4L2_PIX_FMT_VP8:
		codec = HFI_VIDEO_CODEC_VP8;
		अवरोध;
	हाल V4L2_PIX_FMT_VP9:
		codec = HFI_VIDEO_CODEC_VP9;
		अवरोध;
	हाल V4L2_PIX_FMT_XVID:
		codec = HFI_VIDEO_CODEC_DIVX;
		अवरोध;
	हाल V4L2_PIX_FMT_HEVC:
		codec = HFI_VIDEO_CODEC_HEVC;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (session_type == VIDC_SESSION_TYPE_ENC && core->enc_codecs & codec)
		वापस true;

	अगर (session_type == VIDC_SESSION_TYPE_DEC && core->dec_codecs & codec)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_check_codec);

पूर्णांक venus_helper_queue_dpb_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा पूर्णांकbuf *buf;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(buf, &inst->dpbbufs, list) अणु
		काष्ठा hfi_frame_data fdata;

		स_रखो(&fdata, 0, माप(fdata));
		fdata.alloc_len = buf->size;
		fdata.device_addr = buf->da;
		fdata.buffer_type = buf->type;

		ret = hfi_session_process_buf(inst, &fdata);
		अगर (ret)
			जाओ fail;
	पूर्ण

fail:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_queue_dpb_bufs);

पूर्णांक venus_helper_मुक्त_dpb_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा पूर्णांकbuf *buf, *n;

	list_क्रम_each_entry_safe(buf, n, &inst->dpbbufs, list) अणु
		list_del_init(&buf->list);
		dma_मुक्त_attrs(inst->core->dev, buf->size, buf->va, buf->da,
			       buf->attrs);
		kमुक्त(buf);
	पूर्ण

	INIT_LIST_HEAD(&inst->dpbbufs);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_मुक्त_dpb_bufs);

पूर्णांक venus_helper_alloc_dpb_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev;
	क्रमागत hfi_version ver = core->res->hfi_version;
	काष्ठा hfi_buffer_requirements bufreq;
	u32 buftype = inst->dpb_buftype;
	अचिन्हित पूर्णांक dpb_size = 0;
	काष्ठा पूर्णांकbuf *buf;
	अचिन्हित पूर्णांक i;
	u32 count;
	पूर्णांक ret;

	/* no need to allocate dpb buffers */
	अगर (!inst->dpb_fmt)
		वापस 0;

	अगर (inst->dpb_buftype == HFI_BUFFER_OUTPUT)
		dpb_size = inst->output_buf_size;
	अन्यथा अगर (inst->dpb_buftype == HFI_BUFFER_OUTPUT2)
		dpb_size = inst->output2_buf_size;

	अगर (!dpb_size)
		वापस 0;

	ret = venus_helper_get_bufreq(inst, buftype, &bufreq);
	अगर (ret)
		वापस ret;

	count = HFI_BUFREQ_COUNT_MIN(&bufreq, ver);

	क्रम (i = 0; i < count; i++) अणु
		buf = kzalloc(माप(*buf), GFP_KERNEL);
		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		buf->type = buftype;
		buf->size = dpb_size;
		buf->attrs = DMA_ATTR_WRITE_COMBINE |
			     DMA_ATTR_NO_KERNEL_MAPPING;
		buf->va = dma_alloc_attrs(dev, buf->size, &buf->da, GFP_KERNEL,
					  buf->attrs);
		अगर (!buf->va) अणु
			kमुक्त(buf);
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		list_add_tail(&buf->list, &inst->dpbbufs);
	पूर्ण

	वापस 0;

fail:
	venus_helper_मुक्त_dpb_bufs(inst);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_alloc_dpb_bufs);

अटल पूर्णांक पूर्णांकbufs_set_buffer(काष्ठा venus_inst *inst, u32 type)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev;
	काष्ठा hfi_buffer_requirements bufreq;
	काष्ठा hfi_buffer_desc bd;
	काष्ठा पूर्णांकbuf *buf;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = venus_helper_get_bufreq(inst, type, &bufreq);
	अगर (ret)
		वापस 0;

	अगर (!bufreq.size)
		वापस 0;

	क्रम (i = 0; i < bufreq.count_actual; i++) अणु
		buf = kzalloc(माप(*buf), GFP_KERNEL);
		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		buf->type = bufreq.type;
		buf->size = bufreq.size;
		buf->attrs = DMA_ATTR_WRITE_COMBINE |
			     DMA_ATTR_NO_KERNEL_MAPPING;
		buf->va = dma_alloc_attrs(dev, buf->size, &buf->da, GFP_KERNEL,
					  buf->attrs);
		अगर (!buf->va) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		स_रखो(&bd, 0, माप(bd));
		bd.buffer_size = buf->size;
		bd.buffer_type = buf->type;
		bd.num_buffers = 1;
		bd.device_addr = buf->da;

		ret = hfi_session_set_buffers(inst, &bd);
		अगर (ret) अणु
			dev_err(dev, "set session buffers failed\n");
			जाओ dma_मुक्त;
		पूर्ण

		list_add_tail(&buf->list, &inst->पूर्णांकernalbufs);
	पूर्ण

	वापस 0;

dma_मुक्त:
	dma_मुक्त_attrs(dev, buf->size, buf->va, buf->da, buf->attrs);
fail:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकbufs_unset_buffers(काष्ठा venus_inst *inst)
अणु
	काष्ठा hfi_buffer_desc bd = अणु0पूर्ण;
	काष्ठा पूर्णांकbuf *buf, *n;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_safe(buf, n, &inst->पूर्णांकernalbufs, list) अणु
		bd.buffer_size = buf->size;
		bd.buffer_type = buf->type;
		bd.num_buffers = 1;
		bd.device_addr = buf->da;
		bd.response_required = true;

		ret = hfi_session_unset_buffers(inst, &bd);

		list_del_init(&buf->list);
		dma_मुक्त_attrs(inst->core->dev, buf->size, buf->va, buf->da,
			       buf->attrs);
		kमुक्त(buf);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक पूर्णांकbuf_types_1xx[] = अणु
	HFI_BUFFER_INTERNAL_SCRATCH(HFI_VERSION_1XX),
	HFI_BUFFER_INTERNAL_SCRATCH_1(HFI_VERSION_1XX),
	HFI_BUFFER_INTERNAL_SCRATCH_2(HFI_VERSION_1XX),
	HFI_BUFFER_INTERNAL_PERSIST,
	HFI_BUFFER_INTERNAL_PERSIST_1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक पूर्णांकbuf_types_4xx[] = अणु
	HFI_BUFFER_INTERNAL_SCRATCH(HFI_VERSION_4XX),
	HFI_BUFFER_INTERNAL_SCRATCH_1(HFI_VERSION_4XX),
	HFI_BUFFER_INTERNAL_SCRATCH_2(HFI_VERSION_4XX),
	HFI_BUFFER_INTERNAL_PERSIST,
	HFI_BUFFER_INTERNAL_PERSIST_1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक पूर्णांकbuf_types_6xx[] = अणु
	HFI_BUFFER_INTERNAL_SCRATCH(HFI_VERSION_6XX),
	HFI_BUFFER_INTERNAL_SCRATCH_1(HFI_VERSION_6XX),
	HFI_BUFFER_INTERNAL_SCRATCH_2(HFI_VERSION_6XX),
	HFI_BUFFER_INTERNAL_PERSIST,
	HFI_BUFFER_INTERNAL_PERSIST_1,
पूर्ण;

पूर्णांक venus_helper_पूर्णांकbufs_alloc(काष्ठा venus_inst *inst)
अणु
	स्थिर अचिन्हित पूर्णांक *पूर्णांकbuf;
	माप_प्रकार arr_sz, i;
	पूर्णांक ret;

	अगर (IS_V6(inst->core)) अणु
		arr_sz = ARRAY_SIZE(पूर्णांकbuf_types_6xx);
		पूर्णांकbuf = पूर्णांकbuf_types_6xx;
	पूर्ण अन्यथा अगर (IS_V4(inst->core)) अणु
		arr_sz = ARRAY_SIZE(पूर्णांकbuf_types_4xx);
		पूर्णांकbuf = पूर्णांकbuf_types_4xx;
	पूर्ण अन्यथा अणु
		arr_sz = ARRAY_SIZE(पूर्णांकbuf_types_1xx);
		पूर्णांकbuf = पूर्णांकbuf_types_1xx;
	पूर्ण

	क्रम (i = 0; i < arr_sz; i++) अणु
		ret = पूर्णांकbufs_set_buffer(inst, पूर्णांकbuf[i]);
		अगर (ret)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	पूर्णांकbufs_unset_buffers(inst);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_पूर्णांकbufs_alloc);

पूर्णांक venus_helper_पूर्णांकbufs_मुक्त(काष्ठा venus_inst *inst)
अणु
	वापस पूर्णांकbufs_unset_buffers(inst);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_पूर्णांकbufs_मुक्त);

पूर्णांक venus_helper_पूर्णांकbufs_पुनः_स्मृति(काष्ठा venus_inst *inst)
अणु
	क्रमागत hfi_version ver = inst->core->res->hfi_version;
	काष्ठा hfi_buffer_desc bd;
	काष्ठा पूर्णांकbuf *buf, *n;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(buf, n, &inst->पूर्णांकernalbufs, list) अणु
		अगर (buf->type == HFI_BUFFER_INTERNAL_PERSIST ||
		    buf->type == HFI_BUFFER_INTERNAL_PERSIST_1)
			जारी;

		स_रखो(&bd, 0, माप(bd));
		bd.buffer_size = buf->size;
		bd.buffer_type = buf->type;
		bd.num_buffers = 1;
		bd.device_addr = buf->da;
		bd.response_required = true;

		ret = hfi_session_unset_buffers(inst, &bd);

		dma_मुक्त_attrs(inst->core->dev, buf->size, buf->va, buf->da,
			       buf->attrs);

		list_del_init(&buf->list);
		kमुक्त(buf);
	पूर्ण

	ret = पूर्णांकbufs_set_buffer(inst, HFI_BUFFER_INTERNAL_SCRATCH(ver));
	अगर (ret)
		जाओ err;

	ret = पूर्णांकbufs_set_buffer(inst, HFI_BUFFER_INTERNAL_SCRATCH_1(ver));
	अगर (ret)
		जाओ err;

	ret = पूर्णांकbufs_set_buffer(inst, HFI_BUFFER_INTERNAL_SCRATCH_2(ver));
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_पूर्णांकbufs_पुनः_स्मृति);

अटल व्योम fill_buffer_desc(स्थिर काष्ठा venus_buffer *buf,
			     काष्ठा hfi_buffer_desc *bd, bool response)
अणु
	स_रखो(bd, 0, माप(*bd));
	bd->buffer_type = HFI_BUFFER_OUTPUT;
	bd->buffer_size = buf->size;
	bd->num_buffers = 1;
	bd->device_addr = buf->dma_addr;
	bd->response_required = response;
पूर्ण

अटल व्योम वापस_buf_error(काष्ठा venus_inst *inst,
			     काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;

	अगर (vbuf->vb2_buf.type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		v4l2_m2m_src_buf_हटाओ_by_buf(m2m_ctx, vbuf);
	अन्यथा
		v4l2_m2m_dst_buf_हटाओ_by_buf(m2m_ctx, vbuf);

	v4l2_m2m_buf_करोne(vbuf, VB2_BUF_STATE_ERROR);
पूर्ण

अटल व्योम
put_ts_metadata(काष्ठा venus_inst *inst, काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा vb2_buffer *vb = &vbuf->vb2_buf;
	अचिन्हित पूर्णांक i;
	पूर्णांक slot = -1;
	u64 ts_us = vb->बारtamp;

	क्रम (i = 0; i < ARRAY_SIZE(inst->tss); i++) अणु
		अगर (!inst->tss[i].used) अणु
			slot = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (slot == -1) अणु
		dev_dbg(inst->core->dev, VDBGL "no free slot\n");
		वापस;
	पूर्ण

	करो_भाग(ts_us, NSEC_PER_USEC);

	inst->tss[slot].used = true;
	inst->tss[slot].flags = vbuf->flags;
	inst->tss[slot].tc = vbuf->समयcode;
	inst->tss[slot].ts_us = ts_us;
	inst->tss[slot].ts_ns = vb->बारtamp;
पूर्ण

व्योम venus_helper_get_ts_metadata(काष्ठा venus_inst *inst, u64 बारtamp_us,
				  काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा vb2_buffer *vb = &vbuf->vb2_buf;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(inst->tss); ++i) अणु
		अगर (!inst->tss[i].used)
			जारी;

		अगर (inst->tss[i].ts_us != बारtamp_us)
			जारी;

		inst->tss[i].used = false;
		vbuf->flags |= inst->tss[i].flags;
		vbuf->समयcode = inst->tss[i].tc;
		vb->बारtamp = inst->tss[i].ts_ns;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_ts_metadata);

अटल पूर्णांक
session_process_buf(काष्ठा venus_inst *inst, काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा venus_buffer *buf = to_venus_buffer(vbuf);
	काष्ठा vb2_buffer *vb = &vbuf->vb2_buf;
	अचिन्हित पूर्णांक type = vb->type;
	काष्ठा hfi_frame_data fdata;
	पूर्णांक ret;

	स_रखो(&fdata, 0, माप(fdata));
	fdata.alloc_len = buf->size;
	fdata.device_addr = buf->dma_addr;
	fdata.बारtamp = vb->बारtamp;
	करो_भाग(fdata.बारtamp, NSEC_PER_USEC);
	fdata.flags = 0;
	fdata.clnt_data = vbuf->vb2_buf.index;

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		fdata.buffer_type = HFI_BUFFER_INPUT;
		fdata.filled_len = vb2_get_plane_payload(vb, 0);
		fdata.offset = vb->planes[0].data_offset;

		अगर (vbuf->flags & V4L2_BUF_FLAG_LAST || !fdata.filled_len)
			fdata.flags |= HFI_BUFFERFLAG_EOS;

		अगर (inst->session_type == VIDC_SESSION_TYPE_DEC)
			put_ts_metadata(inst, vbuf);

		venus_pm_load_scale(inst);
	पूर्ण अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		अगर (inst->session_type == VIDC_SESSION_TYPE_ENC)
			fdata.buffer_type = HFI_BUFFER_OUTPUT;
		अन्यथा
			fdata.buffer_type = inst->opb_buftype;
		fdata.filled_len = 0;
		fdata.offset = 0;
	पूर्ण

	ret = hfi_session_process_buf(inst, &fdata);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल bool is_dynamic_buभ_शेषe(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा hfi_plat_caps *caps;

	/*
	 * v4 करोesn't send BUFFER_ALLOC_MODE_SUPPORTED property and supports
	 * dynamic buffer mode by शेष क्रम HFI_BUFFER_OUTPUT/OUTPUT2.
	 */
	अगर (IS_V4(core) || IS_V6(core))
		वापस true;

	caps = venus_caps_by_codec(core, inst->hfi_codec, inst->session_type);
	अगर (!caps)
		वापस false;

	वापस caps->cap_bufs_mode_dynamic;
पूर्ण

पूर्णांक venus_helper_unरेजिस्टर_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_buffer *buf, *n;
	काष्ठा hfi_buffer_desc bd;
	पूर्णांक ret = 0;

	अगर (is_dynamic_buभ_शेषe(inst))
		वापस 0;

	list_क्रम_each_entry_safe(buf, n, &inst->रेजिस्टरedbufs, reg_list) अणु
		fill_buffer_desc(buf, &bd, true);
		ret = hfi_session_unset_buffers(inst, &bd);
		list_del_init(&buf->reg_list);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_unरेजिस्टर_bufs);

अटल पूर्णांक session_रेजिस्टर_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा device *dev = core->dev;
	काष्ठा hfi_buffer_desc bd;
	काष्ठा venus_buffer *buf;
	पूर्णांक ret = 0;

	अगर (is_dynamic_buभ_शेषe(inst))
		वापस 0;

	list_क्रम_each_entry(buf, &inst->रेजिस्टरedbufs, reg_list) अणु
		fill_buffer_desc(buf, &bd, false);
		ret = hfi_session_set_buffers(inst, &bd);
		अगर (ret) अणु
			dev_err(dev, "%s: set buffer failed\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 to_hfi_raw_fmt(u32 v4l2_fmt)
अणु
	चयन (v4l2_fmt) अणु
	हाल V4L2_PIX_FMT_NV12:
		वापस HFI_COLOR_FORMAT_NV12;
	हाल V4L2_PIX_FMT_NV21:
		वापस HFI_COLOR_FORMAT_NV21;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_get_bufreq(काष्ठा venus_inst *inst, u32 buftype,
			       काष्ठा hfi_buffer_requirements *req)
अणु
	क्रमागत hfi_version version = inst->core->res->hfi_version;
	स्थिर काष्ठा hfi_platक्रमm *hfi_plat;
	काष्ठा hfi_plat_buffers_params params;
	bool is_dec = inst->session_type == VIDC_SESSION_TYPE_DEC;
	काष्ठा venc_controls *enc_ctr = &inst->controls.enc;

	hfi_plat = hfi_platक्रमm_get(version);

	अगर (!hfi_plat || !hfi_plat->bufreq)
		वापस -EINVAL;

	params.version = version;
	params.num_vpp_pipes = hfi_platक्रमm_num_vpp_pipes(version);

	अगर (is_dec) अणु
		params.width = inst->width;
		params.height = inst->height;
		params.codec = inst->fmt_out->pixfmt;
		params.hfi_color_fmt = to_hfi_raw_fmt(inst->fmt_cap->pixfmt);
		params.dec.max_mbs_per_frame = mbs_per_frame_max(inst);
		params.dec.buffer_size_limit = 0;
		params.dec.is_secondary_output =
			inst->opb_buftype == HFI_BUFFER_OUTPUT2;
		params.dec.is_पूर्णांकerlaced =
			inst->pic_काष्ठा != HFI_INTERLACE_FRAME_PROGRESSIVE ?
				true : false;
	पूर्ण अन्यथा अणु
		params.width = inst->out_width;
		params.height = inst->out_height;
		params.codec = inst->fmt_cap->pixfmt;
		params.hfi_color_fmt = to_hfi_raw_fmt(inst->fmt_out->pixfmt);
		params.enc.work_mode = VIDC_WORK_MODE_2;
		params.enc.rc_type = HFI_RATE_CONTROL_OFF;
		अगर (enc_ctr->bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_CQ)
			params.enc.rc_type = HFI_RATE_CONTROL_CQ;
		params.enc.num_b_frames = enc_ctr->num_b_frames;
		params.enc.is_tenbit = inst->bit_depth == VIDC_BITDEPTH_10;
	पूर्ण

	वापस hfi_plat->bufreq(&params, inst->session_type, buftype, req);
पूर्ण

पूर्णांक venus_helper_get_bufreq(काष्ठा venus_inst *inst, u32 type,
			    काष्ठा hfi_buffer_requirements *req)
अणु
	u32 ptype = HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS;
	जोड़ hfi_get_property hprop;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (req)
		स_रखो(req, 0, माप(*req));

	ret = platक्रमm_get_bufreq(inst, type, req);
	अगर (!ret)
		वापस 0;

	ret = hfi_session_get_property(inst, ptype, &hprop);
	अगर (ret)
		वापस ret;

	ret = -EINVAL;

	क्रम (i = 0; i < HFI_BUFFER_TYPE_MAX; i++) अणु
		अगर (hprop.bufreq[i].type != type)
			जारी;

		अगर (req)
			स_नकल(req, &hprop.bufreq[i], माप(*req));
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_bufreq);

काष्ठा id_mapping अणु
	u32 hfi_id;
	u32 v4l2_id;
पूर्ण;

अटल स्थिर काष्ठा id_mapping mpeg4_profiles[] = अणु
	अणु HFI_MPEG4_PROखाता_SIMPLE, V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE पूर्ण,
	अणु HFI_MPEG4_PROखाता_ADVANCEDSIMPLE, V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_SIMPLE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping mpeg4_levels[] = अणु
	अणु HFI_MPEG4_LEVEL_0, V4L2_MPEG_VIDEO_MPEG4_LEVEL_0 पूर्ण,
	अणु HFI_MPEG4_LEVEL_0b, V4L2_MPEG_VIDEO_MPEG4_LEVEL_0B पूर्ण,
	अणु HFI_MPEG4_LEVEL_1, V4L2_MPEG_VIDEO_MPEG4_LEVEL_1 पूर्ण,
	अणु HFI_MPEG4_LEVEL_2, V4L2_MPEG_VIDEO_MPEG4_LEVEL_2 पूर्ण,
	अणु HFI_MPEG4_LEVEL_3, V4L2_MPEG_VIDEO_MPEG4_LEVEL_3 पूर्ण,
	अणु HFI_MPEG4_LEVEL_4, V4L2_MPEG_VIDEO_MPEG4_LEVEL_4 पूर्ण,
	अणु HFI_MPEG4_LEVEL_5, V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping mpeg2_profiles[] = अणु
	अणु HFI_MPEG2_PROखाता_SIMPLE, V4L2_MPEG_VIDEO_MPEG2_PROखाता_SIMPLE पूर्ण,
	अणु HFI_MPEG2_PROखाता_MAIN, V4L2_MPEG_VIDEO_MPEG2_PROखाता_MAIN पूर्ण,
	अणु HFI_MPEG2_PROखाता_SNR, V4L2_MPEG_VIDEO_MPEG2_PROखाता_SNR_SCALABLE पूर्ण,
	अणु HFI_MPEG2_PROखाता_SPATIAL, V4L2_MPEG_VIDEO_MPEG2_PROखाता_SPATIALLY_SCALABLE पूर्ण,
	अणु HFI_MPEG2_PROखाता_HIGH, V4L2_MPEG_VIDEO_MPEG2_PROखाता_HIGH पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping mpeg2_levels[] = अणु
	अणु HFI_MPEG2_LEVEL_LL, V4L2_MPEG_VIDEO_MPEG2_LEVEL_LOW पूर्ण,
	अणु HFI_MPEG2_LEVEL_ML, V4L2_MPEG_VIDEO_MPEG2_LEVEL_MAIN पूर्ण,
	अणु HFI_MPEG2_LEVEL_H14, V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH_1440 पूर्ण,
	अणु HFI_MPEG2_LEVEL_HL, V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping h264_profiles[] = अणु
	अणु HFI_H264_PROखाता_BASELINE, V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE पूर्ण,
	अणु HFI_H264_PROखाता_MAIN, V4L2_MPEG_VIDEO_H264_PROखाता_MAIN पूर्ण,
	अणु HFI_H264_PROखाता_HIGH, V4L2_MPEG_VIDEO_H264_PROखाता_HIGH पूर्ण,
	अणु HFI_H264_PROखाता_STEREO_HIGH, V4L2_MPEG_VIDEO_H264_PROखाता_STEREO_HIGH पूर्ण,
	अणु HFI_H264_PROखाता_MULTIVIEW_HIGH, V4L2_MPEG_VIDEO_H264_PROखाता_MULTIVIEW_HIGH पूर्ण,
	अणु HFI_H264_PROखाता_CONSTRAINED_BASE, V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE पूर्ण,
	अणु HFI_H264_PROखाता_CONSTRAINED_HIGH, V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_HIGH पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping h264_levels[] = अणु
	अणु HFI_H264_LEVEL_1, V4L2_MPEG_VIDEO_H264_LEVEL_1_0 पूर्ण,
	अणु HFI_H264_LEVEL_1b, V4L2_MPEG_VIDEO_H264_LEVEL_1B पूर्ण,
	अणु HFI_H264_LEVEL_11, V4L2_MPEG_VIDEO_H264_LEVEL_1_1 पूर्ण,
	अणु HFI_H264_LEVEL_12, V4L2_MPEG_VIDEO_H264_LEVEL_1_2 पूर्ण,
	अणु HFI_H264_LEVEL_13, V4L2_MPEG_VIDEO_H264_LEVEL_1_3 पूर्ण,
	अणु HFI_H264_LEVEL_2, V4L2_MPEG_VIDEO_H264_LEVEL_2_0 पूर्ण,
	अणु HFI_H264_LEVEL_21, V4L2_MPEG_VIDEO_H264_LEVEL_2_1 पूर्ण,
	अणु HFI_H264_LEVEL_22, V4L2_MPEG_VIDEO_H264_LEVEL_2_2 पूर्ण,
	अणु HFI_H264_LEVEL_3, V4L2_MPEG_VIDEO_H264_LEVEL_3_0 पूर्ण,
	अणु HFI_H264_LEVEL_31, V4L2_MPEG_VIDEO_H264_LEVEL_3_1 पूर्ण,
	अणु HFI_H264_LEVEL_32, V4L2_MPEG_VIDEO_H264_LEVEL_3_2 पूर्ण,
	अणु HFI_H264_LEVEL_4, V4L2_MPEG_VIDEO_H264_LEVEL_4_0 पूर्ण,
	अणु HFI_H264_LEVEL_41, V4L2_MPEG_VIDEO_H264_LEVEL_4_1 पूर्ण,
	अणु HFI_H264_LEVEL_42, V4L2_MPEG_VIDEO_H264_LEVEL_4_2 पूर्ण,
	अणु HFI_H264_LEVEL_5, V4L2_MPEG_VIDEO_H264_LEVEL_5_0 पूर्ण,
	अणु HFI_H264_LEVEL_51, V4L2_MPEG_VIDEO_H264_LEVEL_5_1 पूर्ण,
	अणु HFI_H264_LEVEL_52, V4L2_MPEG_VIDEO_H264_LEVEL_5_1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping hevc_profiles[] = अणु
	अणु HFI_HEVC_PROखाता_MAIN, V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN पूर्ण,
	अणु HFI_HEVC_PROखाता_MAIN_STILL_PIC, V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_STILL_PICTURE पूर्ण,
	अणु HFI_HEVC_PROखाता_MAIN10, V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping hevc_levels[] = अणु
	अणु HFI_HEVC_LEVEL_1, V4L2_MPEG_VIDEO_HEVC_LEVEL_1 पूर्ण,
	अणु HFI_HEVC_LEVEL_2, V4L2_MPEG_VIDEO_HEVC_LEVEL_2 पूर्ण,
	अणु HFI_HEVC_LEVEL_21, V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1 पूर्ण,
	अणु HFI_HEVC_LEVEL_3, V4L2_MPEG_VIDEO_HEVC_LEVEL_3 पूर्ण,
	अणु HFI_HEVC_LEVEL_31, V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1 पूर्ण,
	अणु HFI_HEVC_LEVEL_4, V4L2_MPEG_VIDEO_HEVC_LEVEL_4 पूर्ण,
	अणु HFI_HEVC_LEVEL_41, V4L2_MPEG_VIDEO_HEVC_LEVEL_4_1 पूर्ण,
	अणु HFI_HEVC_LEVEL_5, V4L2_MPEG_VIDEO_HEVC_LEVEL_5 पूर्ण,
	अणु HFI_HEVC_LEVEL_51, V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1 पूर्ण,
	अणु HFI_HEVC_LEVEL_52, V4L2_MPEG_VIDEO_HEVC_LEVEL_5_2 पूर्ण,
	अणु HFI_HEVC_LEVEL_6, V4L2_MPEG_VIDEO_HEVC_LEVEL_6 पूर्ण,
	अणु HFI_HEVC_LEVEL_61, V4L2_MPEG_VIDEO_HEVC_LEVEL_6_1 पूर्ण,
	अणु HFI_HEVC_LEVEL_62, V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping vp8_profiles[] = अणु
	अणु HFI_VPX_PROखाता_VERSION_0, V4L2_MPEG_VIDEO_VP8_PROखाता_0 पूर्ण,
	अणु HFI_VPX_PROखाता_VERSION_1, V4L2_MPEG_VIDEO_VP8_PROखाता_1 पूर्ण,
	अणु HFI_VPX_PROखाता_VERSION_2, V4L2_MPEG_VIDEO_VP8_PROखाता_2 पूर्ण,
	अणु HFI_VPX_PROखाता_VERSION_3, V4L2_MPEG_VIDEO_VP8_PROखाता_3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping vp9_profiles[] = अणु
	अणु HFI_VP9_PROखाता_P0, V4L2_MPEG_VIDEO_VP9_PROखाता_0 पूर्ण,
	अणु HFI_VP9_PROखाता_P2_10B, V4L2_MPEG_VIDEO_VP9_PROखाता_2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा id_mapping vp9_levels[] = अणु
	अणु HFI_VP9_LEVEL_1, V4L2_MPEG_VIDEO_VP9_LEVEL_1_0 पूर्ण,
	अणु HFI_VP9_LEVEL_11, V4L2_MPEG_VIDEO_VP9_LEVEL_1_1 पूर्ण,
	अणु HFI_VP9_LEVEL_2, V4L2_MPEG_VIDEO_VP9_LEVEL_2_0पूर्ण,
	अणु HFI_VP9_LEVEL_21, V4L2_MPEG_VIDEO_VP9_LEVEL_2_1 पूर्ण,
	अणु HFI_VP9_LEVEL_3, V4L2_MPEG_VIDEO_VP9_LEVEL_3_0पूर्ण,
	अणु HFI_VP9_LEVEL_31, V4L2_MPEG_VIDEO_VP9_LEVEL_3_1 पूर्ण,
	अणु HFI_VP9_LEVEL_4, V4L2_MPEG_VIDEO_VP9_LEVEL_4_0 पूर्ण,
	अणु HFI_VP9_LEVEL_41, V4L2_MPEG_VIDEO_VP9_LEVEL_4_1 पूर्ण,
	अणु HFI_VP9_LEVEL_5, V4L2_MPEG_VIDEO_VP9_LEVEL_5_0 पूर्ण,
	अणु HFI_VP9_LEVEL_51, V4L2_MPEG_VIDEO_VP9_LEVEL_5_1 पूर्ण,
	अणु HFI_VP9_LEVEL_6, V4L2_MPEG_VIDEO_VP9_LEVEL_6_0 पूर्ण,
	अणु HFI_VP9_LEVEL_61, V4L2_MPEG_VIDEO_VP9_LEVEL_6_1 पूर्ण,
पूर्ण;

अटल u32 find_v4l2_id(u32 hfi_id, स्थिर काष्ठा id_mapping *array, अचिन्हित पूर्णांक array_sz)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!array || !array_sz)
		वापस 0;

	क्रम (i = 0; i < array_sz; i++)
		अगर (hfi_id == array[i].hfi_id)
			वापस array[i].v4l2_id;

	वापस 0;
पूर्ण

अटल u32 find_hfi_id(u32 v4l2_id, स्थिर काष्ठा id_mapping *array, अचिन्हित पूर्णांक array_sz)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!array || !array_sz)
		वापस 0;

	क्रम (i = 0; i < array_sz; i++)
		अगर (v4l2_id == array[i].v4l2_id)
			वापस array[i].hfi_id;

	वापस 0;
पूर्ण

अटल व्योम
v4l2_id_profile_level(u32 hfi_codec, काष्ठा hfi_profile_level *pl, u32 *profile, u32 *level)
अणु
	u32 hfi_pf = pl->profile;
	u32 hfi_lvl = pl->level;

	चयन (hfi_codec) अणु
	हाल HFI_VIDEO_CODEC_H264:
		*profile = find_v4l2_id(hfi_pf, h264_profiles, ARRAY_SIZE(h264_profiles));
		*level = find_v4l2_id(hfi_lvl, h264_levels, ARRAY_SIZE(h264_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_MPEG2:
		*profile = find_v4l2_id(hfi_pf, mpeg2_profiles, ARRAY_SIZE(mpeg2_profiles));
		*level = find_v4l2_id(hfi_lvl, mpeg2_levels, ARRAY_SIZE(mpeg2_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_MPEG4:
		*profile = find_v4l2_id(hfi_pf, mpeg4_profiles, ARRAY_SIZE(mpeg4_profiles));
		*level = find_v4l2_id(hfi_lvl, mpeg4_levels, ARRAY_SIZE(mpeg4_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_VP8:
		*profile = find_v4l2_id(hfi_pf, vp8_profiles, ARRAY_SIZE(vp8_profiles));
		*level = 0;
		अवरोध;
	हाल HFI_VIDEO_CODEC_VP9:
		*profile = find_v4l2_id(hfi_pf, vp9_profiles, ARRAY_SIZE(vp9_profiles));
		*level = find_v4l2_id(hfi_lvl, vp9_levels, ARRAY_SIZE(vp9_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_HEVC:
		*profile = find_v4l2_id(hfi_pf, hevc_profiles, ARRAY_SIZE(hevc_profiles));
		*level = find_v4l2_id(hfi_lvl, hevc_levels, ARRAY_SIZE(hevc_levels));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
hfi_id_profile_level(u32 hfi_codec, u32 v4l2_pf, u32 v4l2_lvl, काष्ठा hfi_profile_level *pl)
अणु
	चयन (hfi_codec) अणु
	हाल HFI_VIDEO_CODEC_H264:
		pl->profile = find_hfi_id(v4l2_pf, h264_profiles, ARRAY_SIZE(h264_profiles));
		pl->level = find_hfi_id(v4l2_lvl, h264_levels, ARRAY_SIZE(h264_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_MPEG2:
		pl->profile = find_hfi_id(v4l2_pf, mpeg2_profiles, ARRAY_SIZE(mpeg2_profiles));
		pl->level = find_hfi_id(v4l2_lvl, mpeg2_levels, ARRAY_SIZE(mpeg2_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_MPEG4:
		pl->profile = find_hfi_id(v4l2_pf, mpeg4_profiles, ARRAY_SIZE(mpeg4_profiles));
		pl->level = find_hfi_id(v4l2_lvl, mpeg4_levels, ARRAY_SIZE(mpeg4_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_VP8:
		pl->profile = find_hfi_id(v4l2_pf, vp8_profiles, ARRAY_SIZE(vp8_profiles));
		pl->level = 0;
		अवरोध;
	हाल HFI_VIDEO_CODEC_VP9:
		pl->profile = find_hfi_id(v4l2_pf, vp9_profiles, ARRAY_SIZE(vp9_profiles));
		pl->level = find_hfi_id(v4l2_lvl, vp9_levels, ARRAY_SIZE(vp9_levels));
		अवरोध;
	हाल HFI_VIDEO_CODEC_HEVC:
		pl->profile = find_hfi_id(v4l2_pf, hevc_profiles, ARRAY_SIZE(hevc_profiles));
		pl->level = find_hfi_id(v4l2_lvl, hevc_levels, ARRAY_SIZE(hevc_levels));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक venus_helper_get_profile_level(काष्ठा venus_inst *inst, u32 *profile, u32 *level)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT;
	जोड़ hfi_get_property hprop;
	पूर्णांक ret;

	ret = hfi_session_get_property(inst, ptype, &hprop);
	अगर (ret)
		वापस ret;

	v4l2_id_profile_level(inst->hfi_codec, &hprop.profile_level, profile, level);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_profile_level);

पूर्णांक venus_helper_set_profile_level(काष्ठा venus_inst *inst, u32 profile, u32 level)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT;
	काष्ठा hfi_profile_level pl;

	hfi_id_profile_level(inst->hfi_codec, profile, level, &pl);

	वापस hfi_session_set_property(inst, ptype, &pl);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_profile_level);

अटल u32 get_framesize_raw_nv12(u32 width, u32 height)
अणु
	u32 y_stride, uv_stride, y_plane;
	u32 y_sclines, uv_sclines, uv_plane;
	u32 size;

	y_stride = ALIGN(width, 128);
	uv_stride = ALIGN(width, 128);
	y_sclines = ALIGN(height, 32);
	uv_sclines = ALIGN(((height + 1) >> 1), 16);

	y_plane = y_stride * y_sclines;
	uv_plane = uv_stride * uv_sclines + SZ_4K;
	size = y_plane + uv_plane + SZ_8K;

	वापस ALIGN(size, SZ_4K);
पूर्ण

अटल u32 get_framesize_raw_nv12_ubwc(u32 width, u32 height)
अणु
	u32 y_meta_stride, y_meta_plane;
	u32 y_stride, y_plane;
	u32 uv_meta_stride, uv_meta_plane;
	u32 uv_stride, uv_plane;
	u32 extradata = SZ_16K;

	y_meta_stride = ALIGN(DIV_ROUND_UP(width, 32), 64);
	y_meta_plane = y_meta_stride * ALIGN(DIV_ROUND_UP(height, 8), 16);
	y_meta_plane = ALIGN(y_meta_plane, SZ_4K);

	y_stride = ALIGN(width, 128);
	y_plane = ALIGN(y_stride * ALIGN(height, 32), SZ_4K);

	uv_meta_stride = ALIGN(DIV_ROUND_UP(width / 2, 16), 64);
	uv_meta_plane = uv_meta_stride * ALIGN(DIV_ROUND_UP(height / 2, 8), 16);
	uv_meta_plane = ALIGN(uv_meta_plane, SZ_4K);

	uv_stride = ALIGN(width, 128);
	uv_plane = ALIGN(uv_stride * ALIGN(height / 2, 32), SZ_4K);

	वापस ALIGN(y_meta_plane + y_plane + uv_meta_plane + uv_plane +
		     max(extradata, y_stride * 48), SZ_4K);
पूर्ण

अटल u32 get_framesize_raw_p010(u32 width, u32 height)
अणु
	u32 y_plane, uv_plane, y_stride, uv_stride, y_sclines, uv_sclines;

	y_stride = ALIGN(width * 2, 256);
	uv_stride = ALIGN(width * 2, 256);
	y_sclines = ALIGN(height, 32);
	uv_sclines = ALIGN((height + 1) >> 1, 16);
	y_plane = y_stride * y_sclines;
	uv_plane = uv_stride * uv_sclines;

	वापस ALIGN((y_plane + uv_plane), SZ_4K);
पूर्ण

अटल u32 get_framesize_raw_p010_ubwc(u32 width, u32 height)
अणु
	u32 y_stride, uv_stride, y_sclines, uv_sclines;
	u32 y_ubwc_plane, uv_ubwc_plane;
	u32 y_meta_stride, y_meta_scanlines;
	u32 uv_meta_stride, uv_meta_scanlines;
	u32 y_meta_plane, uv_meta_plane;
	u32 size;

	y_stride = ALIGN(width * 2, 256);
	uv_stride = ALIGN(width * 2, 256);
	y_sclines = ALIGN(height, 16);
	uv_sclines = ALIGN((height + 1) >> 1, 16);

	y_ubwc_plane = ALIGN(y_stride * y_sclines, SZ_4K);
	uv_ubwc_plane = ALIGN(uv_stride * uv_sclines, SZ_4K);
	y_meta_stride = ALIGN(DIV_ROUND_UP(width, 32), 64);
	y_meta_scanlines = ALIGN(DIV_ROUND_UP(height, 4), 16);
	y_meta_plane = ALIGN(y_meta_stride * y_meta_scanlines, SZ_4K);
	uv_meta_stride = ALIGN(DIV_ROUND_UP((width + 1) >> 1, 16), 64);
	uv_meta_scanlines = ALIGN(DIV_ROUND_UP((height + 1) >> 1, 4), 16);
	uv_meta_plane = ALIGN(uv_meta_stride * uv_meta_scanlines, SZ_4K);

	size = y_ubwc_plane + uv_ubwc_plane + y_meta_plane + uv_meta_plane;

	वापस ALIGN(size, SZ_4K);
पूर्ण

अटल u32 get_framesize_raw_yuv420_tp10_ubwc(u32 width, u32 height)
अणु
	u32 y_stride, uv_stride, y_sclines, uv_sclines;
	u32 y_ubwc_plane, uv_ubwc_plane;
	u32 y_meta_stride, y_meta_scanlines;
	u32 uv_meta_stride, uv_meta_scanlines;
	u32 y_meta_plane, uv_meta_plane;
	u32 extradata = SZ_16K;
	u32 size;

	y_stride = ALIGN(ALIGN(width, 192) * 4 / 3, 256);
	uv_stride = ALIGN(ALIGN(width, 192) * 4 / 3, 256);
	y_sclines = ALIGN(height, 16);
	uv_sclines = ALIGN((height + 1) >> 1, 16);

	y_ubwc_plane = ALIGN(y_stride * y_sclines, SZ_4K);
	uv_ubwc_plane = ALIGN(uv_stride * uv_sclines, SZ_4K);
	y_meta_stride = ALIGN(DIV_ROUND_UP(width, 48), 64);
	y_meta_scanlines = ALIGN(DIV_ROUND_UP(height, 4), 16);
	y_meta_plane = ALIGN(y_meta_stride * y_meta_scanlines, SZ_4K);
	uv_meta_stride = ALIGN(DIV_ROUND_UP((width + 1) >> 1, 24), 64);
	uv_meta_scanlines = ALIGN(DIV_ROUND_UP((height + 1) >> 1, 4), 16);
	uv_meta_plane = ALIGN(uv_meta_stride * uv_meta_scanlines, SZ_4K);

	size = y_ubwc_plane + uv_ubwc_plane + y_meta_plane + uv_meta_plane;
	size += max(extradata + SZ_8K, y_stride * 48);

	वापस ALIGN(size, SZ_4K);
पूर्ण

u32 venus_helper_get_framesz_raw(u32 hfi_fmt, u32 width, u32 height)
अणु
	चयन (hfi_fmt) अणु
	हाल HFI_COLOR_FORMAT_NV12:
	हाल HFI_COLOR_FORMAT_NV21:
		वापस get_framesize_raw_nv12(width, height);
	हाल HFI_COLOR_FORMAT_NV12_UBWC:
		वापस get_framesize_raw_nv12_ubwc(width, height);
	हाल HFI_COLOR_FORMAT_P010:
		वापस get_framesize_raw_p010(width, height);
	हाल HFI_COLOR_FORMAT_P010_UBWC:
		वापस get_framesize_raw_p010_ubwc(width, height);
	हाल HFI_COLOR_FORMAT_YUV420_TP10_UBWC:
		वापस get_framesize_raw_yuv420_tp10_ubwc(width, height);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_framesz_raw);

u32 venus_helper_get_framesz(u32 v4l2_fmt, u32 width, u32 height)
अणु
	u32 hfi_fmt, sz;
	bool compressed;

	चयन (v4l2_fmt) अणु
	हाल V4L2_PIX_FMT_MPEG:
	हाल V4L2_PIX_FMT_H264:
	हाल V4L2_PIX_FMT_H264_NO_SC:
	हाल V4L2_PIX_FMT_H264_MVC:
	हाल V4L2_PIX_FMT_H263:
	हाल V4L2_PIX_FMT_MPEG1:
	हाल V4L2_PIX_FMT_MPEG2:
	हाल V4L2_PIX_FMT_MPEG4:
	हाल V4L2_PIX_FMT_XVID:
	हाल V4L2_PIX_FMT_VC1_ANNEX_G:
	हाल V4L2_PIX_FMT_VC1_ANNEX_L:
	हाल V4L2_PIX_FMT_VP8:
	हाल V4L2_PIX_FMT_VP9:
	हाल V4L2_PIX_FMT_HEVC:
		compressed = true;
		अवरोध;
	शेष:
		compressed = false;
		अवरोध;
	पूर्ण

	अगर (compressed) अणु
		sz = ALIGN(height, 32) * ALIGN(width, 32) * 3 / 2 / 2;
		अगर (width < 1280 || height < 720)
			sz *= 8;
		वापस ALIGN(sz, SZ_4K);
	पूर्ण

	hfi_fmt = to_hfi_raw_fmt(v4l2_fmt);
	अगर (!hfi_fmt)
		वापस 0;

	वापस venus_helper_get_framesz_raw(hfi_fmt, width, height);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_framesz);

पूर्णांक venus_helper_set_input_resolution(काष्ठा venus_inst *inst,
				      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	u32 ptype = HFI_PROPERTY_PARAM_FRAME_SIZE;
	काष्ठा hfi_framesize fs;

	fs.buffer_type = HFI_BUFFER_INPUT;
	fs.width = width;
	fs.height = height;

	वापस hfi_session_set_property(inst, ptype, &fs);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_input_resolution);

पूर्णांक venus_helper_set_output_resolution(काष्ठा venus_inst *inst,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       u32 buftype)
अणु
	u32 ptype = HFI_PROPERTY_PARAM_FRAME_SIZE;
	काष्ठा hfi_framesize fs;

	fs.buffer_type = buftype;
	fs.width = width;
	fs.height = height;

	वापस hfi_session_set_property(inst, ptype, &fs);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_output_resolution);

अटल u32 venus_helper_get_work_mode(काष्ठा venus_inst *inst)
अणु
	u32 mode;
	u32 num_mbs;

	mode = VIDC_WORK_MODE_2;
	अगर (inst->session_type == VIDC_SESSION_TYPE_DEC) अणु
		num_mbs = (ALIGN(inst->height, 16) * ALIGN(inst->width, 16)) / 256;
		अगर (inst->hfi_codec == HFI_VIDEO_CODEC_MPEG2 ||
		    inst->pic_काष्ठा != HFI_INTERLACE_FRAME_PROGRESSIVE ||
		    num_mbs <= NUM_MBS_720P)
			mode = VIDC_WORK_MODE_1;
	पूर्ण अन्यथा अणु
		num_mbs = (ALIGN(inst->out_height, 16) * ALIGN(inst->out_width, 16)) / 256;
		अगर (inst->hfi_codec == HFI_VIDEO_CODEC_VP8 &&
		    num_mbs <= NUM_MBS_4K)
			mode = VIDC_WORK_MODE_1;
	पूर्ण

	वापस mode;
पूर्ण

पूर्णांक venus_helper_set_work_mode(काष्ठा venus_inst *inst)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_WORK_MODE;
	काष्ठा hfi_video_work_mode wm;
	u32 mode;

	अगर (!IS_V4(inst->core) && !IS_V6(inst->core))
		वापस 0;

	mode = venus_helper_get_work_mode(inst);
	wm.video_work_mode = mode;
	वापस hfi_session_set_property(inst, ptype, &wm);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_work_mode);

पूर्णांक venus_helper_set_क्रमmat_स्थिरraपूर्णांकs(काष्ठा venus_inst *inst)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_UNCOMPRESSED_PLANE_ACTUAL_CONSTRAINTS_INFO;
	काष्ठा hfi_uncompressed_plane_actual_स्थिरraपूर्णांकs_info pस्थिरraपूर्णांक;

	अगर (!IS_V6(inst->core))
		वापस 0;

	pस्थिरraपूर्णांक.buffer_type = HFI_BUFFER_OUTPUT2;
	pस्थिरraपूर्णांक.num_planes = 2;
	pस्थिरraपूर्णांक.plane_क्रमmat[0].stride_multiples = 128;
	pस्थिरraपूर्णांक.plane_क्रमmat[0].max_stride = 8192;
	pस्थिरraपूर्णांक.plane_क्रमmat[0].min_plane_buffer_height_multiple = 32;
	pस्थिरraपूर्णांक.plane_क्रमmat[0].buffer_alignment = 256;

	pस्थिरraपूर्णांक.plane_क्रमmat[1].stride_multiples = 128;
	pस्थिरraपूर्णांक.plane_क्रमmat[1].max_stride = 8192;
	pस्थिरraपूर्णांक.plane_क्रमmat[1].min_plane_buffer_height_multiple = 16;
	pस्थिरraपूर्णांक.plane_क्रमmat[1].buffer_alignment = 256;

	वापस hfi_session_set_property(inst, ptype, &pस्थिरraपूर्णांक);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_क्रमmat_स्थिरraपूर्णांकs);

पूर्णांक venus_helper_set_num_bufs(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक input_bufs,
			      अचिन्हित पूर्णांक output_bufs,
			      अचिन्हित पूर्णांक output2_bufs)
अणु
	u32 ptype = HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL;
	काष्ठा hfi_buffer_count_actual buf_count;
	पूर्णांक ret;

	buf_count.type = HFI_BUFFER_INPUT;
	buf_count.count_actual = input_bufs;

	ret = hfi_session_set_property(inst, ptype, &buf_count);
	अगर (ret)
		वापस ret;

	buf_count.type = HFI_BUFFER_OUTPUT;
	buf_count.count_actual = output_bufs;

	ret = hfi_session_set_property(inst, ptype, &buf_count);
	अगर (ret)
		वापस ret;

	अगर (output2_bufs) अणु
		buf_count.type = HFI_BUFFER_OUTPUT2;
		buf_count.count_actual = output2_bufs;

		ret = hfi_session_set_property(inst, ptype, &buf_count);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_num_bufs);

पूर्णांक venus_helper_set_raw_क्रमmat(काष्ठा venus_inst *inst, u32 hfi_क्रमmat,
				u32 buftype)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SELECT;
	काष्ठा hfi_uncompressed_क्रमmat_select fmt;

	fmt.buffer_type = buftype;
	fmt.क्रमmat = hfi_क्रमmat;

	वापस hfi_session_set_property(inst, ptype, &fmt);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_raw_क्रमmat);

पूर्णांक venus_helper_set_color_क्रमmat(काष्ठा venus_inst *inst, u32 pixfmt)
अणु
	u32 hfi_क्रमmat, buftype;

	अगर (inst->session_type == VIDC_SESSION_TYPE_DEC)
		buftype = HFI_BUFFER_OUTPUT;
	अन्यथा अगर (inst->session_type == VIDC_SESSION_TYPE_ENC)
		buftype = HFI_BUFFER_INPUT;
	अन्यथा
		वापस -EINVAL;

	hfi_क्रमmat = to_hfi_raw_fmt(pixfmt);
	अगर (!hfi_क्रमmat)
		वापस -EINVAL;

	वापस venus_helper_set_raw_क्रमmat(inst, hfi_क्रमmat, buftype);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_color_क्रमmat);

पूर्णांक venus_helper_set_multistream(काष्ठा venus_inst *inst, bool out_en,
				 bool out2_en)
अणु
	काष्ठा hfi_multi_stream multi = अणु0पूर्ण;
	u32 ptype = HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM;
	पूर्णांक ret;

	multi.buffer_type = HFI_BUFFER_OUTPUT;
	multi.enable = out_en;

	ret = hfi_session_set_property(inst, ptype, &multi);
	अगर (ret)
		वापस ret;

	multi.buffer_type = HFI_BUFFER_OUTPUT2;
	multi.enable = out2_en;

	वापस hfi_session_set_property(inst, ptype, &multi);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_multistream);

पूर्णांक venus_helper_set_dyn_buभ_शेषe(काष्ठा venus_inst *inst)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE;
	काष्ठा hfi_buffer_alloc_mode mode;
	पूर्णांक ret;

	अगर (!is_dynamic_buभ_शेषe(inst))
		वापस 0;

	mode.type = HFI_BUFFER_OUTPUT;
	mode.mode = HFI_BUFFER_MODE_DYNAMIC;

	ret = hfi_session_set_property(inst, ptype, &mode);
	अगर (ret)
		वापस ret;

	mode.type = HFI_BUFFER_OUTPUT2;

	वापस hfi_session_set_property(inst, ptype, &mode);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_dyn_buभ_शेषe);

पूर्णांक venus_helper_set_bufsize(काष्ठा venus_inst *inst, u32 bufsize, u32 buftype)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL;
	काष्ठा hfi_buffer_size_actual bufsz;

	bufsz.type = buftype;
	bufsz.size = bufsize;

	वापस hfi_session_set_property(inst, ptype, &bufsz);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_bufsize);

अचिन्हित पूर्णांक venus_helper_get_opb_size(काष्ठा venus_inst *inst)
अणु
	/* the encoder has only one output */
	अगर (inst->session_type == VIDC_SESSION_TYPE_ENC)
		वापस inst->output_buf_size;

	अगर (inst->opb_buftype == HFI_BUFFER_OUTPUT)
		वापस inst->output_buf_size;
	अन्यथा अगर (inst->opb_buftype == HFI_BUFFER_OUTPUT2)
		वापस inst->output2_buf_size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_opb_size);

अटल व्योम delayed_process_buf_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा venus_buffer *buf, *n;
	काष्ठा venus_inst *inst;
	पूर्णांक ret;

	inst = container_of(work, काष्ठा venus_inst, delayed_process_work);

	mutex_lock(&inst->lock);

	अगर (!(inst->streamon_out & inst->streamon_cap))
		जाओ unlock;

	list_क्रम_each_entry_safe(buf, n, &inst->delayed_process, ref_list) अणु
		अगर (buf->flags & HFI_BUFFERFLAG_READONLY)
			जारी;

		ret = session_process_buf(inst, &buf->vb);
		अगर (ret)
			वापस_buf_error(inst, &buf->vb);

		list_del_init(&buf->ref_list);
	पूर्ण
unlock:
	mutex_unlock(&inst->lock);
पूर्ण

व्योम venus_helper_release_buf_ref(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा venus_buffer *buf;

	list_क्रम_each_entry(buf, &inst->रेजिस्टरedbufs, reg_list) अणु
		अगर (buf->vb.vb2_buf.index == idx) अणु
			buf->flags &= ~HFI_BUFFERFLAG_READONLY;
			schedule_work(&inst->delayed_process_work);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_release_buf_ref);

व्योम venus_helper_acquire_buf_ref(काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा venus_buffer *buf = to_venus_buffer(vbuf);

	buf->flags |= HFI_BUFFERFLAG_READONLY;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_acquire_buf_ref);

अटल पूर्णांक is_buf_refed(काष्ठा venus_inst *inst, काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	काष्ठा venus_buffer *buf = to_venus_buffer(vbuf);

	अगर (buf->flags & HFI_BUFFERFLAG_READONLY) अणु
		list_add_tail(&buf->ref_list, &inst->delayed_process);
		schedule_work(&inst->delayed_process_work);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा vb2_v4l2_buffer *
venus_helper_find_buf(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक type, u32 idx)
अणु
	काष्ठा v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		वापस v4l2_m2m_src_buf_हटाओ_by_idx(m2m_ctx, idx);
	अन्यथा
		वापस v4l2_m2m_dst_buf_हटाओ_by_idx(m2m_ctx, idx);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_find_buf);

पूर्णांक venus_helper_vb2_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा venus_buffer *buf = to_venus_buffer(vbuf);

	buf->size = vb2_plane_size(vb, 0);
	buf->dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);

	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		list_add_tail(&buf->reg_list, &inst->रेजिस्टरedbufs);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_vb2_buf_init);

पूर्णांक venus_helper_vb2_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित पूर्णांक out_buf_size = venus_helper_get_opb_size(inst);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			dev_err(inst->core->dev, "%s field isn't supported\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    vb2_plane_size(vb, 0) < out_buf_size)
		वापस -EINVAL;
	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
	    vb2_plane_size(vb, 0) < inst->input_buf_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_vb2_buf_prepare);

अटल व्योम cache_payload(काष्ठा venus_inst *inst, काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	अचिन्हित पूर्णांक idx = vbuf->vb2_buf.index;

	अगर (vbuf->vb2_buf.type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->payloads[idx] = vb2_get_plane_payload(vb, 0);
पूर्ण

व्योम venus_helper_vb2_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा venus_inst *inst = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	पूर्णांक ret;

	v4l2_m2m_buf_queue(m2m_ctx, vbuf);

	/* Skip processing queued capture buffers after LAST flag */
	अगर (inst->session_type == VIDC_SESSION_TYPE_DEC &&
	    V4L2_TYPE_IS_CAPTURE(vb->vb2_queue->type) &&
	    inst->codec_state == VENUS_DEC_STATE_DRC)
		वापस;

	cache_payload(inst, vb);

	अगर (inst->session_type == VIDC_SESSION_TYPE_ENC &&
	    !(inst->streamon_out && inst->streamon_cap))
		वापस;

	अगर (vb2_start_streaming_called(vb->vb2_queue)) अणु
		ret = is_buf_refed(inst, vbuf);
		अगर (ret)
			वापस;

		ret = session_process_buf(inst, vbuf);
		अगर (ret)
			वापस_buf_error(inst, vbuf);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_vb2_buf_queue);

व्योम venus_helper_buffers_करोne(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक type,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vb2_v4l2_buffer *buf;

	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) अणु
		जबतक ((buf = v4l2_m2m_src_buf_हटाओ(inst->m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, state);
	पूर्ण अन्यथा अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) अणु
		जबतक ((buf = v4l2_m2m_dst_buf_हटाओ(inst->m2m_ctx)))
			v4l2_m2m_buf_करोne(buf, state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_buffers_करोne);

व्योम venus_helper_vb2_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा venus_inst *inst = vb2_get_drv_priv(q);
	काष्ठा venus_core *core = inst->core;
	पूर्णांक ret;

	mutex_lock(&inst->lock);

	अगर (inst->streamon_out & inst->streamon_cap) अणु
		ret = hfi_session_stop(inst);
		ret |= hfi_session_unload_res(inst);
		ret |= venus_helper_unरेजिस्टर_bufs(inst);
		ret |= venus_helper_पूर्णांकbufs_मुक्त(inst);
		ret |= hfi_session_deinit(inst);

		अगर (inst->session_error || core->sys_error)
			ret = -EIO;

		अगर (ret)
			hfi_session_पात(inst);

		venus_helper_मुक्त_dpb_bufs(inst);

		venus_pm_load_scale(inst);
		INIT_LIST_HEAD(&inst->रेजिस्टरedbufs);
	पूर्ण

	venus_helper_buffers_करोne(inst, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,
				  VB2_BUF_STATE_ERROR);
	venus_helper_buffers_करोne(inst, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
				  VB2_BUF_STATE_ERROR);

	अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		inst->streamon_out = 0;
	अन्यथा
		inst->streamon_cap = 0;

	venus_pm_release_core(inst);

	mutex_unlock(&inst->lock);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_vb2_stop_streaming);

पूर्णांक venus_helper_process_initial_cap_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	काष्ठा v4l2_m2m_buffer *buf, *n;
	पूर्णांक ret;

	v4l2_m2m_क्रम_each_dst_buf_safe(m2m_ctx, buf, n) अणु
		ret = session_process_buf(inst, &buf->vb);
		अगर (ret) अणु
			वापस_buf_error(inst, &buf->vb);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_process_initial_cap_bufs);

पूर्णांक venus_helper_process_initial_out_bufs(काष्ठा venus_inst *inst)
अणु
	काष्ठा v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	काष्ठा v4l2_m2m_buffer *buf, *n;
	पूर्णांक ret;

	v4l2_m2m_क्रम_each_src_buf_safe(m2m_ctx, buf, n) अणु
		ret = session_process_buf(inst, &buf->vb);
		अगर (ret) अणु
			वापस_buf_error(inst, &buf->vb);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_process_initial_out_bufs);

पूर्णांक venus_helper_vb2_start_streaming(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	ret = venus_helper_पूर्णांकbufs_alloc(inst);
	अगर (ret)
		वापस ret;

	ret = session_रेजिस्टर_bufs(inst);
	अगर (ret)
		जाओ err_bufs_मुक्त;

	venus_pm_load_scale(inst);

	ret = hfi_session_load_res(inst);
	अगर (ret)
		जाओ err_unreg_bufs;

	ret = hfi_session_start(inst);
	अगर (ret)
		जाओ err_unload_res;

	वापस 0;

err_unload_res:
	hfi_session_unload_res(inst);
err_unreg_bufs:
	venus_helper_unरेजिस्टर_bufs(inst);
err_bufs_मुक्त:
	venus_helper_पूर्णांकbufs_मुक्त(inst);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_vb2_start_streaming);

व्योम venus_helper_m2m_device_run(व्योम *priv)
अणु
	काष्ठा venus_inst *inst = priv;
	काष्ठा v4l2_m2m_ctx *m2m_ctx = inst->m2m_ctx;
	काष्ठा v4l2_m2m_buffer *buf, *n;
	पूर्णांक ret;

	mutex_lock(&inst->lock);

	v4l2_m2m_क्रम_each_dst_buf_safe(m2m_ctx, buf, n) अणु
		ret = session_process_buf(inst, &buf->vb);
		अगर (ret)
			वापस_buf_error(inst, &buf->vb);
	पूर्ण

	v4l2_m2m_क्रम_each_src_buf_safe(m2m_ctx, buf, n) अणु
		ret = session_process_buf(inst, &buf->vb);
		अगर (ret)
			वापस_buf_error(inst, &buf->vb);
	पूर्ण

	mutex_unlock(&inst->lock);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_m2m_device_run);

व्योम venus_helper_m2m_job_पात(व्योम *priv)
अणु
	काष्ठा venus_inst *inst = priv;

	v4l2_m2m_job_finish(inst->m2m_dev, inst->m2m_ctx);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_m2m_job_पात);

पूर्णांक venus_helper_session_init(काष्ठा venus_inst *inst)
अणु
	क्रमागत hfi_version version = inst->core->res->hfi_version;
	u32 session_type = inst->session_type;
	u32 codec;
	पूर्णांक ret;

	codec = inst->session_type == VIDC_SESSION_TYPE_DEC ?
			inst->fmt_out->pixfmt : inst->fmt_cap->pixfmt;

	ret = hfi_session_init(inst, codec);
	अगर (ret)
		वापस ret;

	inst->clk_data.vpp_freq = hfi_platक्रमm_get_codec_vpp_freq(version, codec,
								  session_type);
	inst->clk_data.vsp_freq = hfi_platक्रमm_get_codec_vsp_freq(version, codec,
								  session_type);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_session_init);

व्योम venus_helper_init_instance(काष्ठा venus_inst *inst)
अणु
	अगर (inst->session_type == VIDC_SESSION_TYPE_DEC) अणु
		INIT_LIST_HEAD(&inst->delayed_process);
		INIT_WORK(&inst->delayed_process_work,
			  delayed_process_buf_func);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_init_instance);

अटल bool find_fmt_from_caps(काष्ठा hfi_plat_caps *caps, u32 buftype, u32 fmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < caps->num_fmts; i++) अणु
		अगर (caps->fmts[i].buftype == buftype &&
		    caps->fmts[i].fmt == fmt)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक venus_helper_get_out_fmts(काष्ठा venus_inst *inst, u32 v4l2_fmt,
			      u32 *out_fmt, u32 *out2_fmt, bool ubwc)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा hfi_plat_caps *caps;
	u32 ubwc_fmt, fmt = to_hfi_raw_fmt(v4l2_fmt);
	bool found, found_ubwc;

	*out_fmt = *out2_fmt = 0;

	अगर (!fmt)
		वापस -EINVAL;

	caps = venus_caps_by_codec(core, inst->hfi_codec, inst->session_type);
	अगर (!caps)
		वापस -EINVAL;

	अगर (inst->bit_depth == VIDC_BITDEPTH_10 &&
	    inst->session_type == VIDC_SESSION_TYPE_DEC) अणु
		found_ubwc =
			find_fmt_from_caps(caps, HFI_BUFFER_OUTPUT,
					   HFI_COLOR_FORMAT_YUV420_TP10_UBWC);
		found = find_fmt_from_caps(caps, HFI_BUFFER_OUTPUT2,
					   HFI_COLOR_FORMAT_NV12);
		अगर (found_ubwc && found) अणु
			/*
			 * Hard-code DPB buffers to be 10bit UBWC and decoder
			 * output buffers in 8bit NV12 until V4L2 is able to
			 * expose compressed/tiled क्रमmats to applications.
			 */
			*out_fmt = HFI_COLOR_FORMAT_YUV420_TP10_UBWC;
			*out2_fmt = HFI_COLOR_FORMAT_NV12;
			वापस 0;
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	अगर (ubwc) अणु
		ubwc_fmt = fmt | HFI_COLOR_FORMAT_UBWC_BASE;
		found_ubwc = find_fmt_from_caps(caps, HFI_BUFFER_OUTPUT,
						ubwc_fmt);
		found = find_fmt_from_caps(caps, HFI_BUFFER_OUTPUT2, fmt);

		अगर (found_ubwc && found) अणु
			*out_fmt = ubwc_fmt;
			*out2_fmt = fmt;
			वापस 0;
		पूर्ण
	पूर्ण

	found = find_fmt_from_caps(caps, HFI_BUFFER_OUTPUT, fmt);
	अगर (found) अणु
		*out_fmt = fmt;
		*out2_fmt = 0;
		वापस 0;
	पूर्ण

	found = find_fmt_from_caps(caps, HFI_BUFFER_OUTPUT2, fmt);
	अगर (found) अणु
		*out_fmt = 0;
		*out2_fmt = fmt;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_get_out_fmts);

पूर्णांक venus_helper_set_stride(काष्ठा venus_inst *inst,
			    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_PARAM_UNCOMPRESSED_PLANE_ACTUAL_INFO;

	काष्ठा hfi_uncompressed_plane_actual_info plane_actual_info;

	plane_actual_info.buffer_type = HFI_BUFFER_INPUT;
	plane_actual_info.num_planes = 2;
	plane_actual_info.plane_क्रमmat[0].actual_stride = width;
	plane_actual_info.plane_क्रमmat[0].actual_plane_buffer_height = height;
	plane_actual_info.plane_क्रमmat[1].actual_stride = width;
	plane_actual_info.plane_क्रमmat[1].actual_plane_buffer_height = height / 2;

	वापस hfi_session_set_property(inst, ptype, &plane_actual_info);
पूर्ण
EXPORT_SYMBOL_GPL(venus_helper_set_stride);
