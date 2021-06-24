<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __EDP_CONNECTOR_H__
#घोषणा __EDP_CONNECTOR_H__

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>

#समावेश "msm_drv.h"

#घोषणा edp_पढ़ो(offset) msm_पढ़ोl((offset))
#घोषणा edp_ग_लिखो(offset, data) msm_ग_लिखोl((data), (offset))

काष्ठा edp_ctrl;
काष्ठा edp_aux;
काष्ठा edp_phy;

काष्ठा msm_edp अणु
	काष्ठा drm_device *dev;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा drm_connector *connector;
	काष्ठा drm_bridge *bridge;

	/* the encoder we are hooked to (outside of eDP block) */
	काष्ठा drm_encoder *encoder;

	काष्ठा edp_ctrl *ctrl;

	पूर्णांक irq;
पूर्ण;

/* eDP bridge */
काष्ठा drm_bridge *msm_edp_bridge_init(काष्ठा msm_edp *edp);
व्योम edp_bridge_destroy(काष्ठा drm_bridge *bridge);

/* eDP connector */
काष्ठा drm_connector *msm_edp_connector_init(काष्ठा msm_edp *edp);

/* AUX */
व्योम *msm_edp_aux_init(काष्ठा device *dev, व्योम __iomem *regbase,
			काष्ठा drm_dp_aux **drm_aux);
व्योम msm_edp_aux_destroy(काष्ठा device *dev, काष्ठा edp_aux *aux);
irqवापस_t msm_edp_aux_irq(काष्ठा edp_aux *aux, u32 isr);
व्योम msm_edp_aux_ctrl(काष्ठा edp_aux *aux, पूर्णांक enable);

/* Phy */
bool msm_edp_phy_पढ़ोy(काष्ठा edp_phy *phy);
व्योम msm_edp_phy_ctrl(काष्ठा edp_phy *phy, पूर्णांक enable);
व्योम msm_edp_phy_vm_pe_init(काष्ठा edp_phy *phy);
व्योम msm_edp_phy_vm_pe_cfg(काष्ठा edp_phy *phy, u32 v0, u32 v1);
व्योम msm_edp_phy_lane_घातer_ctrl(काष्ठा edp_phy *phy, bool up, u32 max_lane);
व्योम *msm_edp_phy_init(काष्ठा device *dev, व्योम __iomem *regbase);

/* Ctrl */
irqवापस_t msm_edp_ctrl_irq(काष्ठा edp_ctrl *ctrl);
व्योम msm_edp_ctrl_घातer(काष्ठा edp_ctrl *ctrl, bool on);
पूर्णांक msm_edp_ctrl_init(काष्ठा msm_edp *edp);
व्योम msm_edp_ctrl_destroy(काष्ठा edp_ctrl *ctrl);
bool msm_edp_ctrl_panel_connected(काष्ठा edp_ctrl *ctrl);
पूर्णांक msm_edp_ctrl_get_panel_info(काष्ठा edp_ctrl *ctrl,
	काष्ठा drm_connector *connector, काष्ठा edid **edid);
पूर्णांक msm_edp_ctrl_timing_cfg(काष्ठा edp_ctrl *ctrl,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_info *info);
/* @pixel_rate is in kHz */
bool msm_edp_ctrl_pixel_घड़ी_valid(काष्ठा edp_ctrl *ctrl,
	u32 pixel_rate, u32 *pm, u32 *pn);

#पूर्ण_अगर /* __EDP_CONNECTOR_H__ */
