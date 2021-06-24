<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _KOMEDA_FRAMEBUFFER_H_
#घोषणा _KOMEDA_FRAMEBUFFER_H_

#समावेश <drm/drm_framebuffer.h>
#समावेश "komeda_format_caps.h"

/**
 * काष्ठा komeda_fb - Entending drm_framebuffer with komeda attribute
 */
काष्ठा komeda_fb अणु
	/** @base: &drm_framebuffer */
	काष्ठा drm_framebuffer base;
	/**
	 * @क्रमmat_caps:
	 * extends drm_क्रमmat_info क्रम komeda specअगरic inक्रमmation
	 */
	स्थिर काष्ठा komeda_क्रमmat_caps *क्रमmat_caps;
	/** @is_va: अगर smmu is enabled, it will be true */
	bool is_va;
	/** @aligned_w: aligned frame buffer width */
	u32 aligned_w;
	/** @aligned_h: aligned frame buffer height */
	u32 aligned_h;
	/** @afbc_size: minimum size of afbc */
	u32 afbc_size;
	/** @offset_payload: start of afbc body buffer */
	u32 offset_payload;
पूर्ण;

#घोषणा to_kfb(dfb)	container_of(dfb, काष्ठा komeda_fb, base)

काष्ठा drm_framebuffer *
komeda_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd);
पूर्णांक komeda_fb_check_src_coords(स्थिर काष्ठा komeda_fb *kfb,
			       u32 src_x, u32 src_y, u32 src_w, u32 src_h);
dma_addr_t
komeda_fb_get_pixel_addr(काष्ठा komeda_fb *kfb, पूर्णांक x, पूर्णांक y, पूर्णांक plane);
bool komeda_fb_is_layer_supported(काष्ठा komeda_fb *kfb, u32 layer_type,
		u32 rot);

#पूर्ण_अगर
