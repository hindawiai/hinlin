<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __DPU_KMS_H__
#घोषणा __DPU_KMS_H__

#समावेश <linux/पूर्णांकerconnect.h>

#समावेश <drm/drm_drv.h>

#समावेश "msm_drv.h"
#समावेश "msm_kms.h"
#समावेश "msm_mmu.h"
#समावेश "msm_gem.h"
#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_ctl.h"
#समावेश "dpu_hw_lm.h"
#समावेश "dpu_hw_interrupts.h"
#समावेश "dpu_hw_top.h"
#समावेश "dpu_io_util.h"
#समावेश "dpu_rm.h"
#समावेश "dpu_core_perf.h"

#घोषणा DRMID(x) ((x) ? (x)->base.id : -1)

/**
 * DPU_DEBUG - macro क्रम kms/plane/crtc/encoder/connector logs
 * @fmt: Poपूर्णांकer to क्रमmat string
 */
#घोषणा DPU_DEBUG(fmt, ...)                                                \
	करो अणु                                                               \
		अगर (drm_debug_enabled(DRM_UT_KMS))                         \
			DRM_DEBUG(fmt, ##__VA_ARGS__); \
		अन्यथा                                                       \
			pr_debug(fmt, ##__VA_ARGS__);                      \
	पूर्ण जबतक (0)

/**
 * DPU_DEBUG_DRIVER - macro क्रम hardware driver logging
 * @fmt: Poपूर्णांकer to क्रमmat string
 */
#घोषणा DPU_DEBUG_DRIVER(fmt, ...)                                         \
	करो अणु                                                               \
		अगर (drm_debug_enabled(DRM_UT_DRIVER))                      \
			DRM_ERROR(fmt, ##__VA_ARGS__); \
		अन्यथा                                                       \
			pr_debug(fmt, ##__VA_ARGS__);                      \
	पूर्ण जबतक (0)

#घोषणा DPU_ERROR(fmt, ...) pr_err("[dpu error]" fmt, ##__VA_ARGS__)

/**
 * kसमय_compare_safe - compare two kसमय काष्ठाures
 *	This macro is similar to the standard kसमय_compare() function, but
 *	attempts to also handle kसमय overflows.
 * @A: First kसमय value
 * @B: Second kसमय value
 * Returns: -1 अगर A < B, 0 अगर A == B, 1 अगर A > B
 */
#घोषणा kसमय_compare_safe(A, B) \
	kसमय_compare(kसमय_sub((A), (B)), kसमय_set(0, 0))

#घोषणा DPU_NAME_SIZE  12

/*
 * काष्ठा dpu_irq_callback - IRQ callback handlers
 * @list: list to callback
 * @func: पूर्णांकr handler
 * @arg: argument क्रम the handler
 */
काष्ठा dpu_irq_callback अणु
	काष्ठा list_head list;
	व्योम (*func)(व्योम *arg, पूर्णांक irq_idx);
	व्योम *arg;
पूर्ण;

/**
 * काष्ठा dpu_irq: IRQ काष्ठाure contains callback registration info
 * @total_irq:    total number of irq_idx obtained from HW पूर्णांकerrupts mapping
 * @irq_cb_tbl:   array of IRQ callbacks setting
 * @enable_counts array of IRQ enable counts
 * @cb_lock:      callback lock
 * @debugfs_file: debugfs file क्रम irq statistics
 */
काष्ठा dpu_irq अणु
	u32 total_irqs;
	काष्ठा list_head *irq_cb_tbl;
	atomic_t *enable_counts;
	atomic_t *irq_counts;
	spinlock_t cb_lock;
पूर्ण;

काष्ठा dpu_kms अणु
	काष्ठा msm_kms base;
	काष्ठा drm_device *dev;
	पूर्णांक core_rev;
	काष्ठा dpu_mdss_cfg *catalog;

	/* io/रेजिस्टर spaces: */
	व्योम __iomem *mmio, *vbअगर[VBIF_MAX], *reg_dma;

	काष्ठा regulator *vdd;
	काष्ठा regulator *mmagic;
	काष्ठा regulator *venus;

	काष्ठा dpu_hw_पूर्णांकr *hw_पूर्णांकr;
	काष्ठा dpu_irq irq_obj;

	काष्ठा dpu_core_perf perf;

	/*
	 * Global निजी object state, Do not access directly, use
	 * dpu_kms_global_get_state()
	 */
	काष्ठा drm_modeset_lock global_state_lock;
	काष्ठा drm_निजी_obj global_state;

	काष्ठा dpu_rm rm;
	bool rm_init;

	काष्ठा dpu_hw_vbअगर *hw_vbअगर[VBIF_MAX];
	काष्ठा dpu_hw_mdp *hw_mdp;

	bool has_danger_ctrl;

	काष्ठा platक्रमm_device *pdev;
	bool rpm_enabled;

	काष्ठा opp_table *opp_table;

	काष्ठा dss_module_घातer mp;

	/* reference count bandwidth requests, so we know when we can
	 * release bandwidth.  Each atomic update increments, and frame-
	 * करोne event decrements.  Additionally, क्रम video mode, the
	 * reference is incremented when crtc is enabled, and decremented
	 * when disabled.
	 */
	atomic_t bandwidth_ref;
	काष्ठा icc_path *path[2];
	u32 num_paths;
पूर्ण;

काष्ठा vsync_info अणु
	u32 frame_count;
	u32 line_count;
पूर्ण;

#घोषणा to_dpu_kms(x) container_of(x, काष्ठा dpu_kms, base)

#घोषणा to_dpu_global_state(x) container_of(x, काष्ठा dpu_global_state, base)

/* Global निजी object state क्रम tracking resources that are shared across
 * multiple kms objects (planes/crtcs/etc).
 */
काष्ठा dpu_global_state अणु
	काष्ठा drm_निजी_state base;

	uपूर्णांक32_t pingpong_to_enc_id[PINGPONG_MAX - PINGPONG_0];
	uपूर्णांक32_t mixer_to_enc_id[LM_MAX - LM_0];
	uपूर्णांक32_t ctl_to_enc_id[CTL_MAX - CTL_0];
	uपूर्णांक32_t पूर्णांकf_to_enc_id[INTF_MAX - INTF_0];
	uपूर्णांक32_t dspp_to_enc_id[DSPP_MAX - DSPP_0];
पूर्ण;

काष्ठा dpu_global_state
	*dpu_kms_get_existing_global_state(काष्ठा dpu_kms *dpu_kms);
काष्ठा dpu_global_state
	*__must_check dpu_kms_get_global_state(काष्ठा drm_atomic_state *s);

/**
 * Debugfs functions - extra helper functions क्रम debugfs support
 *
 * Main debugfs करोcumentation is located at,
 *
 * Documentation/fileप्रणालीs/debugfs.rst
 *
 * @dpu_debugfs_setup_regset32: Initialize data क्रम dpu_debugfs_create_regset32
 * @dpu_debugfs_create_regset32: Create 32-bit रेजिस्टर dump file
 * @dpu_debugfs_get_root: Get root dentry क्रम DPU_KMS's debugfs node
 */

/**
 * Companion काष्ठाure क्रम dpu_debugfs_create_regset32. Do not initialize the
 * members of this काष्ठाure explicitly; use dpu_debugfs_setup_regset32 instead.
 */
काष्ठा dpu_debugfs_regset32 अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t blk_len;
	काष्ठा dpu_kms *dpu_kms;
पूर्ण;

/**
 * dpu_debugfs_setup_regset32 - Initialize रेजिस्टर block definition क्रम debugfs
 * This function is meant to initialize dpu_debugfs_regset32 काष्ठाures क्रम use
 * with dpu_debugfs_create_regset32.
 * @regset: opaque रेजिस्टर definition काष्ठाure
 * @offset: sub-block offset
 * @length: sub-block length, in bytes
 * @dpu_kms: poपूर्णांकer to dpu kms काष्ठाure
 */
व्योम dpu_debugfs_setup_regset32(काष्ठा dpu_debugfs_regset32 *regset,
		uपूर्णांक32_t offset, uपूर्णांक32_t length, काष्ठा dpu_kms *dpu_kms);

/**
 * dpu_debugfs_create_regset32 - Create रेजिस्टर पढ़ो back file क्रम debugfs
 *
 * This function is almost identical to the standard debugfs_create_regset32()
 * function, with the मुख्य dअगरference being that a list of रेजिस्टर
 * names/offsets करो not need to be provided. The 'read' function simply outमाला_दो
 * sequential रेजिस्टर values over a specअगरied range.
 *
 * Similar to the related debugfs_create_regset32 API, the काष्ठाure poपूर्णांकed to
 * by regset needs to persist क्रम the lअगरeसमय of the created file. The calling
 * code is responsible क्रम initialization/management of this काष्ठाure.
 *
 * The काष्ठाure poपूर्णांकed to by regset is meant to be opaque. Please use
 * dpu_debugfs_setup_regset32 to initialize it.
 *
 * @name:   File name within debugfs
 * @mode:   File mode within debugfs
 * @parent: Parent directory entry within debugfs, can be शून्य
 * @regset: Poपूर्णांकer to persistent रेजिस्टर block definition
 */
व्योम dpu_debugfs_create_regset32(स्थिर अक्षर *name, umode_t mode,
		व्योम *parent, काष्ठा dpu_debugfs_regset32 *regset);

/**
 * dpu_debugfs_get_root - Return root directory entry क्रम KMS's debugfs
 *
 * The वापस value should be passed as the 'parent' argument to subsequent
 * debugfs create calls.
 *
 * @dpu_kms: Poपूर्णांकer to DPU's KMS काष्ठाure
 *
 * Return: dentry poपूर्णांकer क्रम DPU's debugfs location
 */
व्योम *dpu_debugfs_get_root(काष्ठा dpu_kms *dpu_kms);

/**
 * DPU info management functions
 * These functions/definitions allow क्रम building up a 'dpu_info' काष्ठाure
 * containing one or more "key=value\n" entries.
 */
#घोषणा DPU_KMS_INFO_MAX_SIZE	4096

/**
 * Vblank enable/disable functions
 */
पूर्णांक dpu_enable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);
व्योम dpu_disable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc);

व्योम dpu_kms_encoder_enable(काष्ठा drm_encoder *encoder);

/**
 * dpu_kms_get_clk_rate() - get the घड़ी rate
 * @dpu_kms:  poiner to dpu_kms काष्ठाure
 * @घड़ी_name: घड़ी name to get the rate
 *
 * Return: current घड़ी rate
 */
u64 dpu_kms_get_clk_rate(काष्ठा dpu_kms *dpu_kms, अक्षर *घड़ी_name);

#पूर्ण_अगर /* __dpu_kms_H__ */
