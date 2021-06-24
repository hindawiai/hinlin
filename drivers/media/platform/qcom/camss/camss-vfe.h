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
#अगर_अघोषित QC_MSM_CAMSS_VFE_H
#घोषणा QC_MSM_CAMSS_VFE_H

#समावेश <linux/clk.h>
#समावेश <linux/spinlock_types.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "camss-video.h"
#समावेश "camss-vfe-gen1.h"

#घोषणा MSM_VFE_PAD_SINK 0
#घोषणा MSM_VFE_PAD_SRC 1
#घोषणा MSM_VFE_PADS_NUM 2

#घोषणा MSM_VFE_IMAGE_MASTERS_NUM 7
#घोषणा MSM_VFE_COMPOSITE_IRQ_NUM 4

/* VFE halt समयout */
#घोषणा VFE_HALT_TIMEOUT_MS 100
/* Frame drop value. VAL + UPDATES - 1 should not exceed 31 */
#घोषणा VFE_FRAME_DROP_VAL 30

#घोषणा vfe_line_array(ptr_line)	\
	((स्थिर काष्ठा vfe_line (*)[]) &(ptr_line)[-(ptr_line)->id])

#घोषणा to_vfe(ptr_line)	\
	container_of(vfe_line_array(ptr_line), काष्ठा vfe_device, line)

क्रमागत vfe_output_state अणु
	VFE_OUTPUT_OFF,
	VFE_OUTPUT_RESERVED,
	VFE_OUTPUT_SINGLE,
	VFE_OUTPUT_CONTINUOUS,
	VFE_OUTPUT_IDLE,
	VFE_OUTPUT_STOPPING,
	VFE_OUTPUT_ON,
पूर्ण;

क्रमागत vfe_line_id अणु
	VFE_LINE_NONE = -1,
	VFE_LINE_RDI0 = 0,
	VFE_LINE_RDI1 = 1,
	VFE_LINE_RDI2 = 2,
	VFE_LINE_NUM_GEN2 = 3,
	VFE_LINE_PIX = 3,
	VFE_LINE_NUM_GEN1 = 4,
	VFE_LINE_NUM_MAX = 4
पूर्ण;

काष्ठा vfe_output अणु
	u8 wm_num;
	u8 wm_idx[3];

	काष्ठा camss_buffer *buf[2];
	काष्ठा camss_buffer *last_buffer;
	काष्ठा list_head pending_bufs;

	अचिन्हित पूर्णांक drop_update_idx;

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक active_buf;
			पूर्णांक रुको_sof;
		पूर्ण gen1;
		काष्ठा अणु
			पूर्णांक active_num;
		पूर्ण gen2;
	पूर्ण;
	क्रमागत vfe_output_state state;
	अचिन्हित पूर्णांक sequence;

	पूर्णांक रुको_reg_update;
	काष्ठा completion sof;
	काष्ठा completion reg_update;
पूर्ण;

काष्ठा vfe_line अणु
	क्रमागत vfe_line_id id;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[MSM_VFE_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt fmt[MSM_VFE_PADS_NUM];
	काष्ठा v4l2_rect compose;
	काष्ठा v4l2_rect crop;
	काष्ठा camss_video video_out;
	काष्ठा vfe_output output;
	स्थिर काष्ठा vfe_क्रमmat *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;
पूर्ण;

काष्ठा vfe_device;

काष्ठा vfe_hw_ops अणु
	व्योम (*enable_irq_common)(काष्ठा vfe_device *vfe);
	व्योम (*global_reset)(काष्ठा vfe_device *vfe);
	व्योम (*hw_version_पढ़ो)(काष्ठा vfe_device *vfe, काष्ठा device *dev);
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *dev);
	व्योम (*isr_पढ़ो)(काष्ठा vfe_device *vfe, u32 *value0, u32 *value1);
	व्योम (*pm_करोमुख्य_off)(काष्ठा vfe_device *vfe);
	पूर्णांक (*pm_करोमुख्य_on)(काष्ठा vfe_device *vfe);
	व्योम (*reg_update)(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id);
	व्योम (*reg_update_clear)(काष्ठा vfe_device *vfe,
				 क्रमागत vfe_line_id line_id);
	व्योम (*subdev_init)(काष्ठा device *dev, काष्ठा vfe_device *vfe);
	पूर्णांक (*vfe_disable)(काष्ठा vfe_line *line);
	पूर्णांक (*vfe_enable)(काष्ठा vfe_line *line);
	पूर्णांक (*vfe_halt)(काष्ठा vfe_device *vfe);
	व्योम (*violation_पढ़ो)(काष्ठा vfe_device *vfe);
पूर्ण;

काष्ठा vfe_isr_ops अणु
	व्योम (*reset_ack)(काष्ठा vfe_device *vfe);
	व्योम (*halt_ack)(काष्ठा vfe_device *vfe);
	व्योम (*reg_update)(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id);
	व्योम (*sof)(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id);
	व्योम (*comp_करोne)(काष्ठा vfe_device *vfe, u8 comp);
	व्योम (*wm_करोne)(काष्ठा vfe_device *vfe, u8 wm);
पूर्ण;

काष्ठा vfe_device अणु
	काष्ठा camss *camss;
	u8 id;
	व्योम __iomem *base;
	u32 irq;
	अक्षर irq_name[30];
	काष्ठा camss_घड़ी *घड़ी;
	पूर्णांक nघड़ीs;
	काष्ठा completion reset_complete;
	काष्ठा completion halt_complete;
	काष्ठा mutex घातer_lock;
	पूर्णांक घातer_count;
	काष्ठा mutex stream_lock;
	पूर्णांक stream_count;
	spinlock_t output_lock;
	क्रमागत vfe_line_id wm_output_map[MSM_VFE_IMAGE_MASTERS_NUM];
	काष्ठा vfe_line line[VFE_LINE_NUM_MAX];
	u8 line_num;
	u32 reg_update;
	u8 was_streaming;
	स्थिर काष्ठा vfe_hw_ops *ops;
	स्थिर काष्ठा vfe_hw_ops_gen1 *ops_gen1;
	काष्ठा vfe_isr_ops isr_ops;
	काष्ठा camss_video_ops video_ops;
पूर्ण;

काष्ठा resources;

पूर्णांक msm_vfe_subdev_init(काष्ठा camss *camss, काष्ठा vfe_device *vfe,
			स्थिर काष्ठा resources *res, u8 id);

पूर्णांक msm_vfe_रेजिस्टर_entities(काष्ठा vfe_device *vfe,
			      काष्ठा v4l2_device *v4l2_dev);

व्योम msm_vfe_unरेजिस्टर_entities(काष्ठा vfe_device *vfe);

व्योम msm_vfe_get_vfe_id(काष्ठा media_entity *entity, u8 *id);
व्योम msm_vfe_get_vfe_line_id(काष्ठा media_entity *entity, क्रमागत vfe_line_id *id);

/*
 * vfe_buf_add_pending - Add output buffer to list of pending
 * @output: VFE output
 * @buffer: Video buffer
 */
व्योम vfe_buf_add_pending(काष्ठा vfe_output *output, काष्ठा camss_buffer *buffer);

काष्ठा camss_buffer *vfe_buf_get_pending(काष्ठा vfe_output *output);

पूर्णांक vfe_flush_buffers(काष्ठा camss_video *vid, क्रमागत vb2_buffer_state state);

/*
 * vfe_isr_comp_करोne - Process composite image करोne पूर्णांकerrupt
 * @vfe: VFE Device
 * @comp: Composite image id
 */
व्योम vfe_isr_comp_करोne(काष्ठा vfe_device *vfe, u8 comp);

व्योम vfe_isr_reset_ack(काष्ठा vfe_device *vfe);
पूर्णांक vfe_put_output(काष्ठा vfe_line *line);
पूर्णांक vfe_release_wm(काष्ठा vfe_device *vfe, u8 wm);
पूर्णांक vfe_reserve_wm(काष्ठा vfe_device *vfe, क्रमागत vfe_line_id line_id);

/*
 * vfe_reset - Trigger reset on VFE module and रुको to complete
 * @vfe: VFE device
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक vfe_reset(काष्ठा vfe_device *vfe);

बाह्य स्थिर काष्ठा vfe_hw_ops vfe_ops_4_1;
बाह्य स्थिर काष्ठा vfe_hw_ops vfe_ops_4_7;
बाह्य स्थिर काष्ठा vfe_hw_ops vfe_ops_4_8;
बाह्य स्थिर काष्ठा vfe_hw_ops vfe_ops_170;

#पूर्ण_अगर /* QC_MSM_CAMSS_VFE_H */
