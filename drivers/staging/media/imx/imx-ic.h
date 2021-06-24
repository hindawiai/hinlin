<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * V4L2 Image Converter Subdev क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2016 Mentor Graphics Inc.
 */
#अगर_अघोषित _IMX_IC_H
#घोषणा _IMX_IC_H

#समावेश <media/v4l2-subdev.h>

काष्ठा imx_ic_priv अणु
	काष्ठा device *ipu_dev;
	काष्ठा ipu_soc *ipu;
	काष्ठा v4l2_subdev sd;
	पूर्णांक    task_id;
	व्योम   *task_priv;
पूर्ण;

काष्ठा imx_ic_ops अणु
	स्थिर काष्ठा v4l2_subdev_ops *subdev_ops;
	स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops *पूर्णांकernal_ops;
	स्थिर काष्ठा media_entity_operations *entity_ops;

	पूर्णांक (*init)(काष्ठा imx_ic_priv *ic_priv);
	व्योम (*हटाओ)(काष्ठा imx_ic_priv *ic_priv);
पूर्ण;

बाह्य काष्ठा imx_ic_ops imx_ic_prp_ops;
बाह्य काष्ठा imx_ic_ops imx_ic_prpencvf_ops;

#पूर्ण_अगर
