<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_vsp.h  --  R-Car Display Unit VSP-Based Compositor
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_VSP_H__
#घोषणा __RCAR_DU_VSP_H__

#समावेश <drm/drm_plane.h>

काष्ठा drm_framebuffer;
काष्ठा rcar_du_क्रमmat_info;
काष्ठा rcar_du_vsp;
काष्ठा sg_table;

काष्ठा rcar_du_vsp_plane अणु
	काष्ठा drm_plane plane;
	काष्ठा rcar_du_vsp *vsp;
	अचिन्हित पूर्णांक index;
पूर्ण;

काष्ठा rcar_du_vsp अणु
	अचिन्हित पूर्णांक index;
	काष्ठा device *vsp;
	काष्ठा rcar_du_device *dev;
	काष्ठा rcar_du_vsp_plane *planes;
	अचिन्हित पूर्णांक num_planes;
पूर्ण;

अटल अंतरभूत काष्ठा rcar_du_vsp_plane *to_rcar_vsp_plane(काष्ठा drm_plane *p)
अणु
	वापस container_of(p, काष्ठा rcar_du_vsp_plane, plane);
पूर्ण

/**
 * काष्ठा rcar_du_vsp_plane_state - Driver-specअगरic plane state
 * @state: base DRM plane state
 * @क्रमmat: inक्रमmation about the pixel क्रमmat used by the plane
 * @sg_tables: scatter-gather tables क्रम the frame buffer memory
 */
काष्ठा rcar_du_vsp_plane_state अणु
	काष्ठा drm_plane_state state;

	स्थिर काष्ठा rcar_du_क्रमmat_info *क्रमmat;
	काष्ठा sg_table sg_tables[3];
पूर्ण;

अटल अंतरभूत काष्ठा rcar_du_vsp_plane_state *
to_rcar_vsp_plane_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा rcar_du_vsp_plane_state, state);
पूर्ण

#अगर_घोषित CONFIG_DRM_RCAR_VSP
पूर्णांक rcar_du_vsp_init(काष्ठा rcar_du_vsp *vsp, काष्ठा device_node *np,
		     अचिन्हित पूर्णांक crtcs);
व्योम rcar_du_vsp_enable(काष्ठा rcar_du_crtc *crtc);
व्योम rcar_du_vsp_disable(काष्ठा rcar_du_crtc *crtc);
व्योम rcar_du_vsp_atomic_begin(काष्ठा rcar_du_crtc *crtc);
व्योम rcar_du_vsp_atomic_flush(काष्ठा rcar_du_crtc *crtc);
पूर्णांक rcar_du_vsp_map_fb(काष्ठा rcar_du_vsp *vsp, काष्ठा drm_framebuffer *fb,
		       काष्ठा sg_table sg_tables[3]);
व्योम rcar_du_vsp_unmap_fb(काष्ठा rcar_du_vsp *vsp, काष्ठा drm_framebuffer *fb,
			  काष्ठा sg_table sg_tables[3]);
#अन्यथा
अटल अंतरभूत पूर्णांक rcar_du_vsp_init(काष्ठा rcar_du_vsp *vsp,
				   काष्ठा device_node *np,
				   अचिन्हित पूर्णांक crtcs)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत व्योम rcar_du_vsp_enable(काष्ठा rcar_du_crtc *crtc) अणु पूर्ण;
अटल अंतरभूत व्योम rcar_du_vsp_disable(काष्ठा rcar_du_crtc *crtc) अणु पूर्ण;
अटल अंतरभूत व्योम rcar_du_vsp_atomic_begin(काष्ठा rcar_du_crtc *crtc) अणु पूर्ण;
अटल अंतरभूत व्योम rcar_du_vsp_atomic_flush(काष्ठा rcar_du_crtc *crtc) अणु पूर्ण;
अटल अंतरभूत पूर्णांक rcar_du_vsp_map_fb(काष्ठा rcar_du_vsp *vsp,
				     काष्ठा drm_framebuffer *fb,
				     काष्ठा sg_table sg_tables[3])
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत व्योम rcar_du_vsp_unmap_fb(काष्ठा rcar_du_vsp *vsp,
					काष्ठा drm_framebuffer *fb,
					काष्ठा sg_table sg_tables[3])
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __RCAR_DU_VSP_H__ */
