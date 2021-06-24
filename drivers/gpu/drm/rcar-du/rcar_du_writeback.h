<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_ग_लिखोback.h  --  R-Car Display Unit Writeback Support
 *
 * Copyright (C) 2019 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __RCAR_DU_WRITEBACK_H__
#घोषणा __RCAR_DU_WRITEBACK_H__

#समावेश <drm/drm_plane.h>

काष्ठा rcar_du_crtc;
काष्ठा rcar_du_device;
काष्ठा vsp1_du_atomic_pipe_config;

#अगर_घोषित CONFIG_DRM_RCAR_WRITEBACK
पूर्णांक rcar_du_ग_लिखोback_init(काष्ठा rcar_du_device *rcdu,
			   काष्ठा rcar_du_crtc *rcrtc);
व्योम rcar_du_ग_लिखोback_setup(काष्ठा rcar_du_crtc *rcrtc,
			     काष्ठा vsp1_du_ग_लिखोback_config *cfg);
व्योम rcar_du_ग_लिखोback_complete(काष्ठा rcar_du_crtc *rcrtc);
#अन्यथा
अटल अंतरभूत पूर्णांक rcar_du_ग_लिखोback_init(काष्ठा rcar_du_device *rcdu,
					 काष्ठा rcar_du_crtc *rcrtc)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत व्योम
rcar_du_ग_लिखोback_setup(काष्ठा rcar_du_crtc *rcrtc,
			काष्ठा vsp1_du_ग_लिखोback_config *cfg)
अणु
पूर्ण
अटल अंतरभूत व्योम rcar_du_ग_लिखोback_complete(काष्ठा rcar_du_crtc *rcrtc)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __RCAR_DU_WRITEBACK_H__ */
