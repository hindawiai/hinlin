<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Marek Vasut <marex@denx.de>
 *
 * i.MX23/i.MX28/i.MX6SX MXSFB LCD controller driver.
 */

#अगर_अघोषित __MXSFB_DRV_H__
#घोषणा __MXSFB_DRV_H__

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_plane.h>

काष्ठा clk;

काष्ठा mxsfb_devdata अणु
	अचिन्हित पूर्णांक	transfer_count;
	अचिन्हित पूर्णांक	cur_buf;
	अचिन्हित पूर्णांक	next_buf;
	अचिन्हित पूर्णांक	hs_wdth_mask;
	अचिन्हित पूर्णांक	hs_wdth_shअगरt;
	bool		has_overlay;
पूर्ण;

काष्ठा mxsfb_drm_निजी अणु
	स्थिर काष्ठा mxsfb_devdata	*devdata;

	व्योम __iomem			*base;	/* रेजिस्टरs */
	काष्ठा clk			*clk;
	काष्ठा clk			*clk_axi;
	काष्ठा clk			*clk_disp_axi;

	काष्ठा drm_device		*drm;
	काष्ठा अणु
		काष्ठा drm_plane	primary;
		काष्ठा drm_plane	overlay;
	पूर्ण planes;
	काष्ठा drm_crtc			crtc;
	काष्ठा drm_encoder		encoder;
	काष्ठा drm_connector		*connector;
	काष्ठा drm_bridge		*bridge;
पूर्ण;

अटल अंतरभूत काष्ठा mxsfb_drm_निजी *
to_mxsfb_drm_निजी(काष्ठा drm_device *drm)
अणु
	वापस drm->dev_निजी;
पूर्ण

व्योम mxsfb_enable_axi_clk(काष्ठा mxsfb_drm_निजी *mxsfb);
व्योम mxsfb_disable_axi_clk(काष्ठा mxsfb_drm_निजी *mxsfb);

पूर्णांक mxsfb_kms_init(काष्ठा mxsfb_drm_निजी *mxsfb);

#पूर्ण_अगर /* __MXSFB_DRV_H__ */
