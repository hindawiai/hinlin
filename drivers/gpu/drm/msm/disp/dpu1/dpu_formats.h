<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_FORMATS_H
#घोषणा _DPU_FORMATS_H

#समावेश <drm/drm_fourcc.h>
#समावेश "msm_gem.h"
#समावेश "dpu_hw_mdss.h"

/**
 * dpu_get_dpu_क्रमmat_ext() - Returns dpu क्रमmat काष्ठाure poपूर्णांकer.
 * @क्रमmat:          DRM FourCC Code
 * @modअगरiers:       क्रमmat modअगरier array from client, one per plane
 */
स्थिर काष्ठा dpu_क्रमmat *dpu_get_dpu_क्रमmat_ext(
		स्थिर uपूर्णांक32_t क्रमmat,
		स्थिर uपूर्णांक64_t modअगरier);

#घोषणा dpu_get_dpu_क्रमmat(f) dpu_get_dpu_क्रमmat_ext(f, 0)

/**
 * dpu_get_msm_क्रमmat - get an dpu_क्रमmat by its msm_क्रमmat base
 *                     callback function रेजिस्टरs with the msm_kms layer
 * @kms:             kms driver
 * @क्रमmat:          DRM FourCC Code
 * @modअगरiers:       data layout modअगरier
 */
स्थिर काष्ठा msm_क्रमmat *dpu_get_msm_क्रमmat(
		काष्ठा msm_kms *kms,
		स्थिर uपूर्णांक32_t क्रमmat,
		स्थिर uपूर्णांक64_t modअगरiers);

/**
 * dpu_क्रमmat_check_modअगरied_क्रमmat - validate क्रमmat and buffers क्रम
 *                   dpu non-standard, i.e. modअगरied क्रमmat
 * @kms:             kms driver
 * @msm_fmt:         poपूर्णांकer to the msm_fmt base poपूर्णांकer of an dpu_क्रमmat
 * @cmd:             fb_cmd2 काष्ठाure user request
 * @bos:             gem buffer object list
 *
 * Return: error code on failure, 0 on success
 */
पूर्णांक dpu_क्रमmat_check_modअगरied_क्रमmat(
		स्थिर काष्ठा msm_kms *kms,
		स्थिर काष्ठा msm_क्रमmat *msm_fmt,
		स्थिर काष्ठा drm_mode_fb_cmd2 *cmd,
		काष्ठा drm_gem_object **bos);

/**
 * dpu_क्रमmat_populate_layout - populate the given क्रमmat layout based on
 *                     mmu, fb, and क्रमmat found in the fb
 * @aspace:            address space poपूर्णांकer
 * @fb:                framebuffer poपूर्णांकer
 * @fmtl:              क्रमmat layout काष्ठाure to populate
 *
 * Return: error code on failure, -EAGAIN अगर success but the addresses
 *         are the same as beक्रमe or 0 अगर new addresses were populated
 */
पूर्णांक dpu_क्रमmat_populate_layout(
		काष्ठा msm_gem_address_space *aspace,
		काष्ठा drm_framebuffer *fb,
		काष्ठा dpu_hw_fmt_layout *fmtl);

#पूर्ण_अगर /*_DPU_FORMATS_H */
