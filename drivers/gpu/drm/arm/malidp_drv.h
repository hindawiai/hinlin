<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * ARM Mali DP500/DP550/DP650 KMS/DRM driver काष्ठाures
 */

#अगर_अघोषित __MALIDP_DRV_H__
#घोषणा __MALIDP_DRV_H__

#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_ग_लिखोback.h>
#समावेश <drm/drm_encoder.h>

#समावेश "malidp_hw.h"

#घोषणा MALIDP_CONFIG_VALID_INIT	0
#घोषणा MALIDP_CONFIG_VALID_DONE	1
#घोषणा MALIDP_CONFIG_START		0xd0

काष्ठा malidp_error_stats अणु
	s32 num_errors;
	u32 last_error_status;
	s64 last_error_vblank;
पूर्ण;

काष्ठा malidp_drm अणु
	काष्ठा malidp_hw_device *dev;
	काष्ठा drm_crtc crtc;
	काष्ठा drm_ग_लिखोback_connector mw_connector;
	रुको_queue_head_t wq;
	काष्ठा drm_pending_vblank_event *event;
	atomic_t config_valid;
	u32 core_id;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा malidp_error_stats de_errors;
	काष्ठा malidp_error_stats se_errors;
	/* Protects errors stats */
	spinlock_t errors_lock;
#पूर्ण_अगर
पूर्ण;

#घोषणा crtc_to_malidp_device(x) container_of(x, काष्ठा malidp_drm, crtc)

काष्ठा malidp_plane अणु
	काष्ठा drm_plane base;
	काष्ठा malidp_hw_device *hwdev;
	स्थिर काष्ठा malidp_layer *layer;
पूर्ण;

क्रमागत mmu_prefetch_mode अणु
	MALIDP_PREFETCH_MODE_NONE,
	MALIDP_PREFETCH_MODE_PARTIAL,
	MALIDP_PREFETCH_MODE_FULL,
पूर्ण;

काष्ठा malidp_plane_state अणु
	काष्ठा drm_plane_state base;

	/* size of the required rotation memory अगर plane is rotated */
	u32 roपंचांगem_size;
	/* पूर्णांकernal क्रमmat ID */
	u8 क्रमmat;
	u8 n_planes;
	क्रमागत mmu_prefetch_mode mmu_prefetch_mode;
	u32 mmu_prefetch_pgsize;
पूर्ण;

#घोषणा to_malidp_plane(x) container_of(x, काष्ठा malidp_plane, base)
#घोषणा to_malidp_plane_state(x) container_of(x, काष्ठा malidp_plane_state, base)

काष्ठा malidp_crtc_state अणु
	काष्ठा drm_crtc_state base;
	u32 gamma_coeffs[MALIDP_COEFFTAB_NUM_COEFFS];
	u32 coloradj_coeffs[MALIDP_COLORADJ_NUM_COEFFS];
	काष्ठा malidp_se_config scaler_config;
	/* Bitfield of all the planes that have requested a scaled output. */
	u8 scaled_planes_mask;
पूर्ण;

#घोषणा to_malidp_crtc_state(x) container_of(x, काष्ठा malidp_crtc_state, base)

पूर्णांक malidp_de_planes_init(काष्ठा drm_device *drm);
पूर्णांक malidp_crtc_init(काष्ठा drm_device *drm);

bool malidp_hw_क्रमmat_is_linear_only(u32 क्रमmat);
bool malidp_hw_क्रमmat_is_afbc_only(u32 क्रमmat);

bool malidp_क्रमmat_mod_supported(काष्ठा drm_device *drm,
				 u32 क्रमmat, u64 modअगरier);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम malidp_error(काष्ठा malidp_drm *malidp,
		  काष्ठा malidp_error_stats *error_stats, u32 status,
		  u64 vblank);
#पूर्ण_अगर

/* often used combination of rotational bits */
#घोषणा MALIDP_ROTATED_MASK	(DRM_MODE_ROTATE_90 | DRM_MODE_ROTATE_270)

#पूर्ण_अगर  /* __MALIDP_DRV_H__ */
