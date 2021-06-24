<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __HFI_PLATFORM_H__
#घोषणा __HFI_PLATFORM_H__

#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश "hfi.h"
#समावेश "hfi_plat_bufs.h"
#समावेश "hfi_helper.h"

#घोषणा MAX_PLANES		4
#घोषणा MAX_FMT_ENTRIES		32
#घोषणा MAX_CAP_ENTRIES		32
#घोषणा MAX_ALLOC_MODE_ENTRIES	16
#घोषणा MAX_CODEC_NUM		32
#घोषणा MAX_SESSIONS		16

काष्ठा raw_क्रमmats अणु
	u32 buftype;
	u32 fmt;
पूर्ण;

काष्ठा hfi_plat_caps अणु
	u32 codec;
	u32 करोमुख्य;
	bool cap_bufs_mode_dynamic;
	अचिन्हित पूर्णांक num_caps;
	काष्ठा hfi_capability caps[MAX_CAP_ENTRIES];
	अचिन्हित पूर्णांक num_pl;
	काष्ठा hfi_profile_level pl[HFI_MAX_PROखाता_COUNT];
	अचिन्हित पूर्णांक num_fmts;
	काष्ठा raw_क्रमmats fmts[MAX_FMT_ENTRIES];
	bool valid;	/* used only क्रम Venus v1xx */
पूर्ण;

काष्ठा hfi_platक्रमm_codec_freq_data अणु
	u32 pixfmt;
	u32 session_type;
	अचिन्हित दीर्घ vpp_freq;
	अचिन्हित दीर्घ vsp_freq;
पूर्ण;

काष्ठा hfi_platक्रमm अणु
	अचिन्हित दीर्घ (*codec_vpp_freq)(u32 session_type, u32 codec);
	अचिन्हित दीर्घ (*codec_vsp_freq)(u32 session_type, u32 codec);
	व्योम (*codecs)(u32 *enc_codecs, u32 *dec_codecs, u32 *count);
	स्थिर काष्ठा hfi_plat_caps *(*capabilities)(अचिन्हित पूर्णांक *entries);
	u8 (*num_vpp_pipes)(व्योम);
	पूर्णांक (*bufreq)(काष्ठा hfi_plat_buffers_params *params, u32 session_type,
		      u32 buftype, काष्ठा hfi_buffer_requirements *bufreq);
पूर्ण;

बाह्य स्थिर काष्ठा hfi_platक्रमm hfi_plat_v4;
बाह्य स्थिर काष्ठा hfi_platक्रमm hfi_plat_v6;

स्थिर काष्ठा hfi_platक्रमm *hfi_platक्रमm_get(क्रमागत hfi_version version);
अचिन्हित दीर्घ hfi_platक्रमm_get_codec_vpp_freq(क्रमागत hfi_version version, u32 codec,
					      u32 session_type);
अचिन्हित दीर्घ hfi_platक्रमm_get_codec_vsp_freq(क्रमागत hfi_version version, u32 codec,
					      u32 session_type);
u8 hfi_platक्रमm_num_vpp_pipes(क्रमागत hfi_version version);
#पूर्ण_अगर
