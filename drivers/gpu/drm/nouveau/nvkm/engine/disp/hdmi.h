<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_HDMI_H__
#घोषणा __NVKM_DISP_HDMI_H__
#समावेश "ior.h"

काष्ठा packed_hdmi_infoframe अणु
	u32 header;
	u32 subpack0_low;
	u32 subpack0_high;
	u32 subpack1_low;
	u32 subpack1_high;
पूर्ण;

व्योम pack_hdmi_infoframe(काष्ठा packed_hdmi_infoframe *packed_frame,
			 u8 *raw_frame, sमाप_प्रकार len);
#पूर्ण_अगर
