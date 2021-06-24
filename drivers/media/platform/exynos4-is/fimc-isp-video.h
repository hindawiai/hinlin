<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#अगर_अघोषित FIMC_ISP_VIDEO__
#घोषणा FIMC_ISP_VIDEO__

#समावेश <media/videobuf2-v4l2.h>
#समावेश "fimc-isp.h"

#अगर_घोषित CONFIG_VIDEO_EXYNOS4_ISP_DMA_CAPTURE
पूर्णांक fimc_isp_video_device_रेजिस्टर(काष्ठा fimc_isp *isp,
				काष्ठा v4l2_device *v4l2_dev,
				क्रमागत v4l2_buf_type type);

व्योम fimc_isp_video_device_unरेजिस्टर(काष्ठा fimc_isp *isp,
				क्रमागत v4l2_buf_type type);

व्योम fimc_isp_video_irq_handler(काष्ठा fimc_is *is);
#अन्यथा
अटल अंतरभूत व्योम fimc_isp_video_irq_handler(काष्ठा fimc_is *is)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक fimc_isp_video_device_रेजिस्टर(काष्ठा fimc_isp *isp,
						काष्ठा v4l2_device *v4l2_dev,
						क्रमागत v4l2_buf_type type)
अणु
	वापस 0;
पूर्ण

व्योम fimc_isp_video_device_unरेजिस्टर(काष्ठा fimc_isp *isp,
				क्रमागत v4l2_buf_type type)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_VIDEO_EXYNOS4_ISP_DMA_CAPTURE */

#पूर्ण_अगर /* FIMC_ISP_VIDEO__ */
