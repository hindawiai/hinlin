<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#अगर_अघोषित __VENUS_HELPERS_H__
#घोषणा __VENUS_HELPERS_H__

#समावेश <media/videobuf2-v4l2.h>

काष्ठा venus_inst;
काष्ठा venus_core;

bool venus_helper_check_codec(काष्ठा venus_inst *inst, u32 v4l2_pixfmt);
काष्ठा vb2_v4l2_buffer *venus_helper_find_buf(काष्ठा venus_inst *inst,
					      अचिन्हित पूर्णांक type, u32 idx);
व्योम venus_helper_buffers_करोne(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक type,
			       क्रमागत vb2_buffer_state state);
पूर्णांक venus_helper_vb2_buf_init(काष्ठा vb2_buffer *vb);
पूर्णांक venus_helper_vb2_buf_prepare(काष्ठा vb2_buffer *vb);
व्योम venus_helper_vb2_buf_queue(काष्ठा vb2_buffer *vb);
व्योम venus_helper_vb2_stop_streaming(काष्ठा vb2_queue *q);
पूर्णांक venus_helper_vb2_start_streaming(काष्ठा venus_inst *inst);
व्योम venus_helper_m2m_device_run(व्योम *priv);
व्योम venus_helper_m2m_job_पात(व्योम *priv);
पूर्णांक venus_helper_get_bufreq(काष्ठा venus_inst *inst, u32 type,
			    काष्ठा hfi_buffer_requirements *req);
u32 venus_helper_get_framesz_raw(u32 hfi_fmt, u32 width, u32 height);
u32 venus_helper_get_framesz(u32 v4l2_fmt, u32 width, u32 height);
पूर्णांक venus_helper_set_input_resolution(काष्ठा venus_inst *inst,
				      अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);
पूर्णांक venus_helper_set_output_resolution(काष्ठा venus_inst *inst,
				       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				       u32 buftype);
पूर्णांक venus_helper_set_work_mode(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_set_क्रमmat_स्थिरraपूर्णांकs(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_set_num_bufs(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक input_bufs,
			      अचिन्हित पूर्णांक output_bufs,
			      अचिन्हित पूर्णांक output2_bufs);
पूर्णांक venus_helper_set_raw_क्रमmat(काष्ठा venus_inst *inst, u32 hfi_क्रमmat,
				u32 buftype);
पूर्णांक venus_helper_set_color_क्रमmat(काष्ठा venus_inst *inst, u32 fmt);
पूर्णांक venus_helper_set_dyn_buभ_शेषe(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_set_bufsize(काष्ठा venus_inst *inst, u32 bufsize, u32 buftype);
पूर्णांक venus_helper_set_multistream(काष्ठा venus_inst *inst, bool out_en,
				 bool out2_en);
अचिन्हित पूर्णांक venus_helper_get_opb_size(काष्ठा venus_inst *inst);
व्योम venus_helper_acquire_buf_ref(काष्ठा vb2_v4l2_buffer *vbuf);
व्योम venus_helper_release_buf_ref(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक idx);
व्योम venus_helper_init_instance(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_session_init(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_get_out_fmts(काष्ठा venus_inst *inst, u32 fmt, u32 *out_fmt,
			      u32 *out2_fmt, bool ubwc);
पूर्णांक venus_helper_alloc_dpb_bufs(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_मुक्त_dpb_bufs(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_पूर्णांकbufs_alloc(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_पूर्णांकbufs_मुक्त(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_पूर्णांकbufs_पुनः_स्मृति(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_queue_dpb_bufs(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_unरेजिस्टर_bufs(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_process_initial_cap_bufs(काष्ठा venus_inst *inst);
पूर्णांक venus_helper_process_initial_out_bufs(काष्ठा venus_inst *inst);
व्योम venus_helper_get_ts_metadata(काष्ठा venus_inst *inst, u64 बारtamp_us,
				  काष्ठा vb2_v4l2_buffer *vbuf);
पूर्णांक venus_helper_get_profile_level(काष्ठा venus_inst *inst, u32 *profile, u32 *level);
पूर्णांक venus_helper_set_profile_level(काष्ठा venus_inst *inst, u32 profile, u32 level);
पूर्णांक venus_helper_set_stride(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक aligned_width,
			    अचिन्हित पूर्णांक aligned_height);
#पूर्ण_अगर
