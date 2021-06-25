<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * camss-csiphy.h
 *
 * Qualcomm MSM Camera Subप्रणाली - CSIPHY Module
 *
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2016-2018 Linaro Ltd.
 */
#अगर_अघोषित QC_MSM_CAMSS_CSIPHY_H
#घोषणा QC_MSM_CAMSS_CSIPHY_H

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा MSM_CSIPHY_PAD_SINK 0
#घोषणा MSM_CSIPHY_PAD_SRC 1
#घोषणा MSM_CSIPHY_PADS_NUM 2

काष्ठा csiphy_lane अणु
	u8 pos;
	u8 pol;
पूर्ण;

काष्ठा csiphy_lanes_cfg अणु
	पूर्णांक num_data;
	काष्ठा csiphy_lane *data;
	काष्ठा csiphy_lane clk;
पूर्ण;

काष्ठा csiphy_csi2_cfg अणु
	काष्ठा csiphy_lanes_cfg lane_cfg;
पूर्ण;

काष्ठा csiphy_config अणु
	u8 combo_mode;
	u8 csid_id;
	काष्ठा csiphy_csi2_cfg *csi2;
पूर्ण;

काष्ठा csiphy_device;

काष्ठा csiphy_hw_ops अणु
	व्योम (*hw_version_पढ़ो)(काष्ठा csiphy_device *csiphy,
				काष्ठा device *dev);
	व्योम (*reset)(काष्ठा csiphy_device *csiphy);
	व्योम (*lanes_enable)(काष्ठा csiphy_device *csiphy,
			     काष्ठा csiphy_config *cfg,
			     s64 link_freq, u8 lane_mask);
	व्योम (*lanes_disable)(काष्ठा csiphy_device *csiphy,
			      काष्ठा csiphy_config *cfg);
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *dev);
पूर्ण;

काष्ठा csiphy_device अणु
	काष्ठा camss *camss;
	u8 id;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[MSM_CSIPHY_PADS_NUM];
	व्योम __iomem *base;
	व्योम __iomem *base_clk_mux;
	u32 irq;
	अक्षर irq_name[30];
	काष्ठा camss_घड़ी *घड़ी;
	bool *rate_set;
	पूर्णांक nघड़ीs;
	u32 समयr_clk_rate;
	काष्ठा csiphy_config cfg;
	काष्ठा v4l2_mbus_framefmt fmt[MSM_CSIPHY_PADS_NUM];
	स्थिर काष्ठा csiphy_hw_ops *ops;
	स्थिर काष्ठा csiphy_क्रमmat *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;
पूर्ण;

काष्ठा resources;

पूर्णांक msm_csiphy_subdev_init(काष्ठा camss *camss,
			   काष्ठा csiphy_device *csiphy,
			   स्थिर काष्ठा resources *res, u8 id);

पूर्णांक msm_csiphy_रेजिस्टर_entity(काष्ठा csiphy_device *csiphy,
			       काष्ठा v4l2_device *v4l2_dev);

व्योम msm_csiphy_unरेजिस्टर_entity(काष्ठा csiphy_device *csiphy);

बाह्य स्थिर काष्ठा csiphy_hw_ops csiphy_ops_2ph_1_0;
बाह्य स्थिर काष्ठा csiphy_hw_ops csiphy_ops_3ph_1_0;

#पूर्ण_अगर /* QC_MSM_CAMSS_CSIPHY_H */
