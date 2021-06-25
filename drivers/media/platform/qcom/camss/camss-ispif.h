<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * camss-ispअगर.h
 *
 * Qualcomm MSM Camera Subप्रणाली - ISPIF (ISP Interface) Module
 *
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#अगर_अघोषित QC_MSM_CAMSS_ISPIF_H
#घोषणा QC_MSM_CAMSS_ISPIF_H

#समावेश <linux/clk.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा MSM_ISPIF_PAD_SINK 0
#घोषणा MSM_ISPIF_PAD_SRC 1
#घोषणा MSM_ISPIF_PADS_NUM 2

#घोषणा MSM_ISPIF_VFE_NUM 2

क्रमागत ispअगर_पूर्णांकf अणु
	PIX0,
	RDI0,
	PIX1,
	RDI1,
	RDI2
पूर्ण;

काष्ठा ispअगर_पूर्णांकf_cmd_reg अणु
	u32 cmd_0;
	u32 cmd_1;
पूर्ण;

काष्ठा ispअगर_line अणु
	काष्ठा ispअगर_device *ispअगर;
	u8 id;
	u8 csid_id;
	u8 vfe_id;
	क्रमागत ispअगर_पूर्णांकf पूर्णांकerface;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[MSM_ISPIF_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt fmt[MSM_ISPIF_PADS_NUM];
	स्थिर u32 *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;
पूर्ण;

काष्ठा ispअगर_device अणु
	व्योम __iomem *base;
	व्योम __iomem *base_clk_mux;
	u32 irq;
	अक्षर irq_name[30];
	काष्ठा camss_घड़ी *घड़ी;
	पूर्णांक nघड़ीs;
	काष्ठा camss_घड़ी  *घड़ी_क्रम_reset;
	पूर्णांक nघड़ीs_क्रम_reset;
	काष्ठा completion reset_complete[MSM_ISPIF_VFE_NUM];
	पूर्णांक घातer_count;
	काष्ठा mutex घातer_lock;
	काष्ठा ispअगर_पूर्णांकf_cmd_reg पूर्णांकf_cmd[MSM_ISPIF_VFE_NUM];
	काष्ठा mutex config_lock;
	अचिन्हित पूर्णांक line_num;
	काष्ठा ispअगर_line *line;
	काष्ठा camss *camss;
पूर्ण;

काष्ठा resources_ispअगर;

पूर्णांक msm_ispअगर_subdev_init(काष्ठा camss *camss,
			  स्थिर काष्ठा resources_ispअगर *res);

पूर्णांक msm_ispअगर_रेजिस्टर_entities(काष्ठा ispअगर_device *ispअगर,
				काष्ठा v4l2_device *v4l2_dev);

व्योम msm_ispअगर_unरेजिस्टर_entities(काष्ठा ispअगर_device *ispअगर);

#पूर्ण_अगर /* QC_MSM_CAMSS_ISPIF_H */
