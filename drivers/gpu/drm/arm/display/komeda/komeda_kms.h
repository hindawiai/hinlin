<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _KOMEDA_KMS_H_
#घोषणा _KOMEDA_KMS_H_

#समावेश <linux/list.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_ग_लिखोback.h>
#समावेश <drm/drm_prपूर्णांक.h>

/**
 * काष्ठा komeda_plane - komeda instance of drm_plane
 */
काष्ठा komeda_plane अणु
	/** @base: &drm_plane */
	काष्ठा drm_plane base;
	/**
	 * @layer:
	 *
	 * represents available layer input pipelines क्रम this plane.
	 *
	 * NOTE:
	 * the layer is not क्रम a specअगरic Layer, but indicate a group of
	 * Layers with same capabilities.
	 */
	काष्ठा komeda_layer *layer;
पूर्ण;

/**
 * काष्ठा komeda_plane_state
 *
 * The plane_state can be split पूर्णांकo two data flow (left/right) and handled
 * by two layers &komeda_plane.layer and &komeda_plane.layer.right
 */
काष्ठा komeda_plane_state अणु
	/** @base: &drm_plane_state */
	काष्ठा drm_plane_state base;
	/** @zlist_node: zorder list node */
	काष्ठा list_head zlist_node;

	/** @layer_split: on/off layer_split */
	u8 layer_split : 1;
पूर्ण;

/**
 * काष्ठा komeda_wb_connector
 */
काष्ठा komeda_wb_connector अणु
	/** @base: &drm_ग_लिखोback_connector */
	काष्ठा drm_ग_लिखोback_connector base;

	/** @wb_layer: represents associated ग_लिखोback pipeline of komeda */
	काष्ठा komeda_layer *wb_layer;
पूर्ण;

/**
 * काष्ठा komeda_crtc
 */
काष्ठा komeda_crtc अणु
	/** @base: &drm_crtc */
	काष्ठा drm_crtc base;
	/** @master: only master has display output */
	काष्ठा komeda_pipeline *master;
	/**
	 * @slave: optional
	 *
	 * Doesn't have its own display output, the handled data flow will
	 * merge पूर्णांकo the master.
	 */
	काष्ठा komeda_pipeline *slave;

	/** @slave_planes: komeda slave planes mask */
	u32 slave_planes;

	/** @wb_conn: komeda ग_लिखो back connector */
	काष्ठा komeda_wb_connector *wb_conn;

	/** @disable_करोne: this flip_करोne is क्रम tracing the disable */
	काष्ठा completion *disable_करोne;
पूर्ण;

/**
 * काष्ठा komeda_crtc_state
 */
काष्ठा komeda_crtc_state अणु
	/** @base: &drm_crtc_state */
	काष्ठा drm_crtc_state base;

	/* निजी properties */

	/* computed state which are used by validate/check */
	/**
	 * @affected_pipes:
	 * the affected pipelines in once display instance
	 */
	u32 affected_pipes;
	/**
	 * @active_pipes:
	 * the active pipelines in once display instance
	 */
	u32 active_pipes;

	/** @घड़ी_ratio: ratio of (aclk << 32)/pxlclk */
	u64 घड़ी_ratio;

	/** @max_slave_zorder: the maximum of slave zorder */
	u32 max_slave_zorder;
पूर्ण;

/** काष्ठा komeda_kms_dev - क्रम gather KMS related things */
काष्ठा komeda_kms_dev अणु
	/** @base: &drm_device */
	काष्ठा drm_device base;

	/** @n_crtcs: valid numbers of crtcs in &komeda_kms_dev.crtcs */
	पूर्णांक n_crtcs;
	/** @crtcs: crtcs list */
	काष्ठा komeda_crtc crtcs[KOMEDA_MAX_PIPELINES];
पूर्ण;

#घोषणा to_kplane(p)	container_of(p, काष्ठा komeda_plane, base)
#घोषणा to_kplane_st(p)	container_of(p, काष्ठा komeda_plane_state, base)
#घोषणा to_kconn(p)	container_of(p, काष्ठा komeda_wb_connector, base)
#घोषणा to_kcrtc(p)	container_of(p, काष्ठा komeda_crtc, base)
#घोषणा to_kcrtc_st(p)	container_of(p, काष्ठा komeda_crtc_state, base)
#घोषणा to_kdev(p)	container_of(p, काष्ठा komeda_kms_dev, base)
#घोषणा to_wb_conn(x)	container_of(x, काष्ठा drm_ग_लिखोback_connector, base)

अटल अंतरभूत bool is_ग_लिखोback_only(काष्ठा drm_crtc_state *st)
अणु
	काष्ठा komeda_wb_connector *wb_conn = to_kcrtc(st->crtc)->wb_conn;
	काष्ठा drm_connector *conn = wb_conn ? &wb_conn->base.base : शून्य;

	वापस conn && (st->connector_mask == BIT(drm_connector_index(conn)));
पूर्ण

अटल अंतरभूत bool
is_only_changed_connector(काष्ठा drm_crtc_state *st, काष्ठा drm_connector *conn)
अणु
	काष्ठा drm_crtc_state *old_st;
	u32 changed_connectors;

	old_st = drm_atomic_get_old_crtc_state(st->state, st->crtc);
	changed_connectors = st->connector_mask ^ old_st->connector_mask;

	वापस BIT(drm_connector_index(conn)) == changed_connectors;
पूर्ण

अटल अंतरभूत bool has_flip_h(u32 rot)
अणु
	u32 rotation = drm_rotation_simplअगरy(rot,
					     DRM_MODE_ROTATE_0 |
					     DRM_MODE_ROTATE_90 |
					     DRM_MODE_REFLECT_MASK);

	अगर (rotation & DRM_MODE_ROTATE_90)
		वापस !!(rotation & DRM_MODE_REFLECT_Y);
	अन्यथा
		वापस !!(rotation & DRM_MODE_REFLECT_X);
पूर्ण

व्योम komeda_crtc_get_color_config(काष्ठा drm_crtc_state *crtc_st,
				  u32 *color_depths, u32 *color_क्रमmats);
अचिन्हित दीर्घ komeda_crtc_get_aclk(काष्ठा komeda_crtc_state *kcrtc_st);

पूर्णांक komeda_kms_setup_crtcs(काष्ठा komeda_kms_dev *kms, काष्ठा komeda_dev *mdev);

पूर्णांक komeda_kms_add_crtcs(काष्ठा komeda_kms_dev *kms, काष्ठा komeda_dev *mdev);
पूर्णांक komeda_kms_add_planes(काष्ठा komeda_kms_dev *kms, काष्ठा komeda_dev *mdev);
पूर्णांक komeda_kms_add_निजी_objs(काष्ठा komeda_kms_dev *kms,
				काष्ठा komeda_dev *mdev);
पूर्णांक komeda_kms_add_wb_connectors(काष्ठा komeda_kms_dev *kms,
				 काष्ठा komeda_dev *mdev);
व्योम komeda_kms_cleanup_निजी_objs(काष्ठा komeda_kms_dev *kms);

व्योम komeda_crtc_handle_event(काष्ठा komeda_crtc   *kcrtc,
			      काष्ठा komeda_events *evts);

काष्ठा komeda_kms_dev *komeda_kms_attach(काष्ठा komeda_dev *mdev);
व्योम komeda_kms_detach(काष्ठा komeda_kms_dev *kms);

#पूर्ण_अगर /*_KOMEDA_KMS_H_*/
