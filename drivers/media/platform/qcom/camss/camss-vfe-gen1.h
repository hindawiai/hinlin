<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * camss-vfe.h
 *
 * Qualcomm MSM Camera Subप्रणाली - VFE (Video Front End) Module
 *
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#अगर_अघोषित QC_MSM_CAMSS_VFE_GEN1_H
#घोषणा QC_MSM_CAMSS_VFE_GEN1_H

#समावेश "camss-vfe.h"

क्रमागत vfe_line_id;
काष्ठा vfe_device;
काष्ठा vfe_line;
काष्ठा vfe_output;

काष्ठा vfe_hw_ops_gen1 अणु
	व्योम (*bus_connect_wm_to_rdi)(काष्ठा vfe_device *vfe, u8 wm, क्रमागत vfe_line_id id);
	व्योम (*bus_disconnect_wm_from_rdi)(काष्ठा vfe_device *vfe, u8 wm, क्रमागत vfe_line_id id);
	व्योम (*bus_enable_wr_अगर)(काष्ठा vfe_device *vfe, u8 enable);
	व्योम (*bus_reload_wm)(काष्ठा vfe_device *vfe, u8 wm);
	पूर्णांक (*camअगर_रुको_क्रम_stop)(काष्ठा vfe_device *vfe, काष्ठा device *dev);
	व्योम (*enable_irq_common)(काष्ठा vfe_device *vfe);
	व्योम (*enable_irq_wm_line)(काष्ठा vfe_device *vfe, u8 wm, क्रमागत vfe_line_id line_id,
				   u8 enable);
	व्योम (*enable_irq_pix_line)(काष्ठा vfe_device *vfe, u8 comp, क्रमागत vfe_line_id line_id,
				    u8 enable);
	u16 (*get_ub_size)(u8 vfe_id);
	व्योम (*halt_clear)(काष्ठा vfe_device *vfe);
	व्योम (*halt_request)(काष्ठा vfe_device *vfe);
	व्योम (*set_camअगर_cfg)(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line);
	व्योम (*set_camअगर_cmd)(काष्ठा vfe_device *vfe, u8 enable);
	व्योम (*set_cgc_override)(काष्ठा vfe_device *vfe, u8 wm, u8 enable);
	व्योम (*set_clamp_cfg)(काष्ठा vfe_device *vfe);
	व्योम (*set_crop_cfg)(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line);
	व्योम (*set_demux_cfg)(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line);
	व्योम (*set_ds)(काष्ठा vfe_device *vfe);
	व्योम (*set_module_cfg)(काष्ठा vfe_device *vfe, u8 enable);
	व्योम (*set_scale_cfg)(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line);
	व्योम (*set_rdi_cid)(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id id, u8 cid);
	व्योम (*set_realign_cfg)(काष्ठा vfe_device *vfe, काष्ठा vfe_line *line, u8 enable);
	व्योम (*set_qos)(काष्ठा vfe_device *vfe);
	व्योम (*set_xbar_cfg)(काष्ठा vfe_device *vfe, काष्ठा vfe_output *output, u8 enable);
	व्योम (*wm_frame_based)(काष्ठा vfe_device *vfe, u8 wm, u8 enable);
	व्योम (*wm_line_based)(काष्ठा vfe_device *vfe, u32 wm, काष्ठा v4l2_pix_क्रमmat_mplane *pix,
			      u8 plane, u32 enable);
	व्योम (*wm_set_ub_cfg)(काष्ठा vfe_device *vfe, u8 wm, u16 offset, u16 depth);
	व्योम (*wm_set_subsample)(काष्ठा vfe_device *vfe, u8 wm);
	व्योम (*wm_set_framedrop_period)(काष्ठा vfe_device *vfe, u8 wm, u8 per);
	व्योम (*wm_set_framedrop_pattern)(काष्ठा vfe_device *vfe, u8 wm, u32 pattern);
	व्योम (*wm_set_ping_addr)(काष्ठा vfe_device *vfe, u8 wm, u32 addr);
	व्योम (*wm_set_pong_addr)(काष्ठा vfe_device *vfe, u8 wm, u32 addr);
	पूर्णांक (*wm_get_ping_pong_status)(काष्ठा vfe_device *vfe, u8 wm);
	व्योम (*wm_enable)(काष्ठा vfe_device *vfe, u8 wm, u8 enable);
पूर्ण;

/*
 * vfe_calc_पूर्णांकerp_reso - Calculate पूर्णांकerpolation mode
 * @input: Input resolution
 * @output: Output resolution
 *
 * Return पूर्णांकerpolation mode
 */
अटल अंतरभूत u8 vfe_calc_पूर्णांकerp_reso(u16 input, u16 output)
अणु
	अगर (input / output >= 16)
		वापस 0;

	अगर (input / output >= 8)
		वापस 1;

	अगर (input / output >= 4)
		वापस 2;

	वापस 3;
पूर्ण

/*
 * vfe_gen1_disable - Disable streaming on VFE line
 * @line: VFE line
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक vfe_gen1_disable(काष्ठा vfe_line *line);

/*
 * vfe_gen1_enable - Enable VFE module
 * @line: VFE line
 *
 * Return 0 on success
 */
पूर्णांक vfe_gen1_enable(काष्ठा vfe_line *line);

/*
 * vfe_gen1_enable - Halt VFE module
 * @vfe: VFE device
 *
 * Return 0 on success
 */
पूर्णांक vfe_gen1_halt(काष्ठा vfe_device *vfe);

/*
 * vfe_word_per_line - Calculate number of words per frame width
 * @क्रमmat: V4L2 क्रमmat
 * @width: Frame width
 *
 * Return number of words per frame width
 */
पूर्णांक vfe_word_per_line(u32 क्रमmat, u32 width);

बाह्य स्थिर काष्ठा vfe_isr_ops vfe_isr_ops_gen1;
बाह्य स्थिर काष्ठा camss_video_ops vfe_video_ops_gen1;

#पूर्ण_अगर /* QC_MSM_CAMSS_VFE_GEN1_H */
