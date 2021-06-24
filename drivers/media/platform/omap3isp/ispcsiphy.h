<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ispcsiphy.h
 *
 * TI OMAP3 ISP - CSI PHY module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_CSI_PHY_H
#घोषणा OMAP3_ISP_CSI_PHY_H

#समावेश "omap3isp.h"

काष्ठा isp_csi2_device;
काष्ठा regulator;

काष्ठा isp_csiphy अणु
	काष्ठा isp_device *isp;
	काष्ठा mutex mutex;	/* serialize csiphy configuration */
	काष्ठा isp_csi2_device *csi2;
	काष्ठा regulator *vdd;
	/* the entity that acquired the phy */
	काष्ठा media_entity *entity;

	/* mem resources - क्रमागतs as defined in क्रमागत isp_mem_resources */
	अचिन्हित पूर्णांक cfg_regs;
	अचिन्हित पूर्णांक phy_regs;

	u8 num_data_lanes;	/* number of CSI2 Data Lanes supported */
पूर्ण;

पूर्णांक omap3isp_csiphy_acquire(काष्ठा isp_csiphy *phy,
			    काष्ठा media_entity *entity);
व्योम omap3isp_csiphy_release(काष्ठा isp_csiphy *phy);
पूर्णांक omap3isp_csiphy_init(काष्ठा isp_device *isp);
व्योम omap3isp_csiphy_cleanup(काष्ठा isp_device *isp);

#पूर्ण_अगर	/* OMAP3_ISP_CSI_PHY_H */
