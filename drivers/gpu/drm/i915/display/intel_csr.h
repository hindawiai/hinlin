<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_CSR_H__
#घोषणा __INTEL_CSR_H__

काष्ठा drm_i915_निजी;

#घोषणा CSR_VERSION(major, minor)	((major) << 16 | (minor))
#घोषणा CSR_VERSION_MAJOR(version)	((version) >> 16)
#घोषणा CSR_VERSION_MINOR(version)	((version) & 0xffff)

व्योम पूर्णांकel_csr_ucode_init(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_csr_load_program(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_csr_ucode_fini(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_csr_ucode_suspend(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_csr_ucode_resume(काष्ठा drm_i915_निजी *i915);

#पूर्ण_अगर /* __INTEL_CSR_H__ */
