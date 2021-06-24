<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __HFI_PLATFORM_BUFFERS_H__
#घोषणा __HFI_PLATFORM_BUFFERS_H__

#समावेश <linux/types.h>
#समावेश "hfi_helper.h"

काष्ठा hfi_plat_buffers_params अणु
	u32 width;
	u32 height;
	u32 codec;
	u32 hfi_color_fmt;
	क्रमागत hfi_version version;
	u32 num_vpp_pipes;
	जोड़ अणु
		काष्ठा अणु
			u32 max_mbs_per_frame;
			u32 buffer_size_limit;
			bool is_secondary_output;
			bool is_पूर्णांकerlaced;
		पूर्ण dec;
		काष्ठा अणु
			u32 work_mode;
			u32 rc_type;
			u32 num_b_frames;
			bool is_tenbit;
		पूर्ण enc;
	पूर्ण;
पूर्ण;

पूर्णांक hfi_plat_bufreq_v6(काष्ठा hfi_plat_buffers_params *params, u32 session_type,
		       u32 buftype, काष्ठा hfi_buffer_requirements *bufreq);

#पूर्ण_अगर
