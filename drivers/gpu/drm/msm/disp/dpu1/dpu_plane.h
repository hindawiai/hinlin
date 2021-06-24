<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित _DPU_PLANE_H_
#घोषणा _DPU_PLANE_H_

#समावेश <drm/drm_crtc.h>

#समावेश "dpu_kms.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_sspp.h"

/**
 * काष्ठा dpu_plane_state: Define dpu extension of drm plane state object
 * @base:	base drm plane state object
 * @aspace:	poपूर्णांकer to address space क्रम input/output buffers
 * @stage:	asचिन्हित by crtc blender
 * @needs_qos_remap: qos remap settings need to be updated
 * @multirect_index: index of the rectangle of SSPP
 * @multirect_mode: parallel or समय multiplex multirect mode
 * @pending:	whether the current update is still pending
 * @scaler3_cfg: configuration data क्रम scaler3
 * @pixel_ext: configuration data क्रम pixel extensions
 * @cdp_cfg:	CDP configuration
 * @plane_fetch_bw: calculated BW per plane
 * @plane_clk: calculated clk per plane
 */
काष्ठा dpu_plane_state अणु
	काष्ठा drm_plane_state base;
	काष्ठा msm_gem_address_space *aspace;
	क्रमागत dpu_stage stage;
	bool needs_qos_remap;
	uपूर्णांक32_t multirect_index;
	uपूर्णांक32_t multirect_mode;
	bool pending;

	/* scaler configuration */
	काष्ठा dpu_hw_scaler3_cfg scaler3_cfg;
	काष्ठा dpu_hw_pixel_ext pixel_ext;

	काष्ठा dpu_hw_pipe_cdp_cfg cdp_cfg;
	u64 plane_fetch_bw;
	u64 plane_clk;
पूर्ण;

/**
 * काष्ठा dpu_multirect_plane_states: Defines multirect pair of drm plane states
 * @r0: drm plane configured on rect 0
 * @r1: drm plane configured on rect 1
 */
काष्ठा dpu_multirect_plane_states अणु
	स्थिर काष्ठा drm_plane_state *r0;
	स्थिर काष्ठा drm_plane_state *r1;
पूर्ण;

#घोषणा to_dpu_plane_state(x) \
	container_of(x, काष्ठा dpu_plane_state, base)

/**
 * dpu_plane_pipe - वापस sspp identअगरier क्रम the given plane
 * @plane:   Poपूर्णांकer to DRM plane object
 * Returns: sspp identअगरier of the given plane
 */
क्रमागत dpu_sspp dpu_plane_pipe(काष्ठा drm_plane *plane);

/**
 * is_dpu_plane_भव - check क्रम भव plane
 * @plane: Poपूर्णांकer to DRM plane object
 * वापसs: true - अगर the plane is भव
 *          false - अगर the plane is primary
 */
bool is_dpu_plane_भव(काष्ठा drm_plane *plane);

/**
 * dpu_plane_get_ctl_flush - get control flush mask
 * @plane:   Poपूर्णांकer to DRM plane object
 * @ctl: Poपूर्णांकer to control hardware
 * @flush_sspp: Poपूर्णांकer to sspp flush control word
 */
व्योम dpu_plane_get_ctl_flush(काष्ठा drm_plane *plane, काष्ठा dpu_hw_ctl *ctl,
		u32 *flush_sspp);

/**
 * dpu_plane_flush - final plane operations beक्रमe commit flush
 * @plane: Poपूर्णांकer to drm plane काष्ठाure
 */
व्योम dpu_plane_flush(काष्ठा drm_plane *plane);

/**
 * dpu_plane_set_error: enable/disable error condition
 * @plane: poपूर्णांकer to drm_plane काष्ठाure
 */
व्योम dpu_plane_set_error(काष्ठा drm_plane *plane, bool error);

/**
 * dpu_plane_init - create new dpu plane क्रम the given pipe
 * @dev:   Poपूर्णांकer to DRM device
 * @pipe:  dpu hardware pipe identअगरier
 * @type:  Plane type - PRIMARY/OVERLAY/CURSOR
 * @possible_crtcs: biपंचांगask of crtc that can be attached to the given pipe
 * @master_plane_id: primary plane id of a multirect pipe. 0 value passed क्रम
 *                   a regular plane initialization. A non-zero primary plane
 *                   id will be passed क्रम a भव pipe initialization.
 *
 */
काष्ठा drm_plane *dpu_plane_init(काष्ठा drm_device *dev,
		uपूर्णांक32_t pipe, क्रमागत drm_plane_type type,
		अचिन्हित दीर्घ possible_crtcs, u32 master_plane_id);

/**
 * dpu_plane_validate_multirecti_v2 - validate the multirect planes
 *				      against hw limitations
 * @plane: drm plate states of the multirect pair
 */
पूर्णांक dpu_plane_validate_multirect_v2(काष्ठा dpu_multirect_plane_states *plane);

/**
 * dpu_plane_clear_multirect - clear multirect bits क्रम the given pipe
 * @drm_state: Poपूर्णांकer to DRM plane state
 */
व्योम dpu_plane_clear_multirect(स्थिर काष्ठा drm_plane_state *drm_state);

/**
 * dpu_plane_color_fill - enables color fill on plane
 * @plane:  Poपूर्णांकer to DRM plane object
 * @color:  RGB fill color value, [23..16] Blue, [15..8] Green, [7..0] Red
 * @alpha:  8-bit fill alpha value, 255 selects 100% alpha
 * Returns: 0 on success
 */
पूर्णांक dpu_plane_color_fill(काष्ठा drm_plane *plane,
		uपूर्णांक32_t color, uपूर्णांक32_t alpha);

#पूर्ण_अगर /* _DPU_PLANE_H_ */
