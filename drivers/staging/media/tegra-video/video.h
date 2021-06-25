<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __TEGRA_VIDEO_H__
#घोषणा __TEGRA_VIDEO_H__

#समावेश <linux/host1x.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-device.h>

#समावेश "vi.h"
#समावेश "csi.h"

काष्ठा tegra_video_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा tegra_vi *vi;
	काष्ठा tegra_csi *csi;
पूर्ण;

पूर्णांक tegra_v4l2_nodes_setup_tpg(काष्ठा tegra_video_device *vid);
व्योम tegra_v4l2_nodes_cleanup_tpg(काष्ठा tegra_video_device *vid);

बाह्य काष्ठा platक्रमm_driver tegra_vi_driver;
बाह्य काष्ठा platक्रमm_driver tegra_csi_driver;
#पूर्ण_अगर
