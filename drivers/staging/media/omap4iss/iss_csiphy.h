<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - CSI PHY module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित OMAP4_ISS_CSI_PHY_H
#घोषणा OMAP4_ISS_CSI_PHY_H

#समावेश <linux/platक्रमm_data/media/omap4iss.h>

काष्ठा iss_csi2_device;

काष्ठा iss_csiphy_dphy_cfg अणु
	u8 ths_term;
	u8 ths_settle;
	u8 tclk_term;
	अचिन्हित tclk_miss:1;
	u8 tclk_settle;
पूर्ण;

काष्ठा iss_csiphy अणु
	काष्ठा iss_device *iss;
	काष्ठा mutex mutex;	/* serialize csiphy configuration */
	u8 phy_in_use;
	काष्ठा iss_csi2_device *csi2;

	/* memory resources, as defined in क्रमागत iss_mem_resources */
	अचिन्हित पूर्णांक cfg_regs;
	अचिन्हित पूर्णांक phy_regs;

	u8 max_data_lanes;	/* number of CSI2 Data Lanes supported */
	u8 used_data_lanes;	/* number of CSI2 Data Lanes used */
	काष्ठा iss_csiphy_lanes_cfg lanes;
	काष्ठा iss_csiphy_dphy_cfg dphy;
पूर्ण;

पूर्णांक omap4iss_csiphy_config(काष्ठा iss_device *iss,
			   काष्ठा v4l2_subdev *csi2_subdev);
पूर्णांक omap4iss_csiphy_acquire(काष्ठा iss_csiphy *phy);
व्योम omap4iss_csiphy_release(काष्ठा iss_csiphy *phy);
पूर्णांक omap4iss_csiphy_init(काष्ठा iss_device *iss);

#पूर्ण_अगर	/* OMAP4_ISS_CSI_PHY_H */
