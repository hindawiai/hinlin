<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_CORE_PERF_H_
#घोषणा _DPU_CORE_PERF_H_

#समावेश <linux/types.h>
#समावेश <linux/dcache.h>
#समावेश <linux/mutex.h>
#समावेश <drm/drm_crtc.h>

#समावेश "dpu_hw_catalog.h"

#घोषणा	DPU_PERF_DEFAULT_MAX_CORE_CLK_RATE	412500000

/**
 * क्रमागत dpu_core_perf_data_bus_id - data bus identअगरier
 * @DPU_CORE_PERF_DATA_BUS_ID_MNOC: DPU/MNOC data bus
 * @DPU_CORE_PERF_DATA_BUS_ID_LLCC: MNOC/LLCC data bus
 * @DPU_CORE_PERF_DATA_BUS_ID_EBI: LLCC/EBI data bus
 */
क्रमागत dpu_core_perf_data_bus_id अणु
	DPU_CORE_PERF_DATA_BUS_ID_MNOC,
	DPU_CORE_PERF_DATA_BUS_ID_LLCC,
	DPU_CORE_PERF_DATA_BUS_ID_EBI,
	DPU_CORE_PERF_DATA_BUS_ID_MAX,
पूर्ण;

/**
 * काष्ठा dpu_core_perf_params - definition of perक्रमmance parameters
 * @max_per_pipe_ib: maximum instantaneous bandwidth request
 * @bw_ctl: arbitrated bandwidth request
 * @core_clk_rate: core घड़ी rate request
 */
काष्ठा dpu_core_perf_params अणु
	u64 max_per_pipe_ib;
	u64 bw_ctl;
	u64 core_clk_rate;
पूर्ण;

/**
 * काष्ठा dpu_core_perf_tune - definition of perक्रमmance tuning control
 * @mode: perक्रमmance mode
 * @min_core_clk: minimum core घड़ी
 * @min_bus_vote: minimum bus vote
 */
काष्ठा dpu_core_perf_tune अणु
	u32 mode;
	u64 min_core_clk;
	u64 min_bus_vote;
पूर्ण;

/**
 * काष्ठा dpu_core_perf - definition of core perक्रमmance context
 * @dev: Poपूर्णांकer to drm device
 * @debugfs_root: top level debug folder
 * @catalog: Poपूर्णांकer to catalog configuration
 * @core_clk: Poपूर्णांकer to core घड़ी काष्ठाure
 * @core_clk_rate: current core घड़ी rate
 * @max_core_clk_rate: maximum allowable core घड़ी rate
 * @perf_tune: debug control क्रम perक्रमmance tuning
 * @enable_bw_release: debug control क्रम bandwidth release
 * @fix_core_clk_rate: fixed core घड़ी request in Hz used in mode 2
 * @fix_core_ib_vote: fixed core ib vote in bps used in mode 2
 * @fix_core_ab_vote: fixed core ab vote in bps used in mode 2
 */
काष्ठा dpu_core_perf अणु
	काष्ठा drm_device *dev;
	काष्ठा dentry *debugfs_root;
	काष्ठा dpu_mdss_cfg *catalog;
	काष्ठा dss_clk *core_clk;
	u64 core_clk_rate;
	u64 max_core_clk_rate;
	काष्ठा dpu_core_perf_tune perf_tune;
	u32 enable_bw_release;
	u64 fix_core_clk_rate;
	u64 fix_core_ib_vote;
	u64 fix_core_ab_vote;
पूर्ण;

/**
 * dpu_core_perf_crtc_check - validate perक्रमmance of the given crtc state
 * @crtc: Poपूर्णांकer to crtc
 * @state: Poपूर्णांकer to new crtc state
 * वापस: zero अगर success, or error code otherwise
 */
पूर्णांक dpu_core_perf_crtc_check(काष्ठा drm_crtc *crtc,
		काष्ठा drm_crtc_state *state);

/**
 * dpu_core_perf_crtc_update - update perक्रमmance of the given crtc
 * @crtc: Poपूर्णांकer to crtc
 * @params_changed: true अगर crtc parameters are modअगरied
 * @stop_req: true अगर this is a stop request
 * वापस: zero अगर success, or error code otherwise
 */
पूर्णांक dpu_core_perf_crtc_update(काष्ठा drm_crtc *crtc,
		पूर्णांक params_changed, bool stop_req);

/**
 * dpu_core_perf_crtc_release_bw - release bandwidth of the given crtc
 * @crtc: Poपूर्णांकer to crtc
 */
व्योम dpu_core_perf_crtc_release_bw(काष्ठा drm_crtc *crtc);

/**
 * dpu_core_perf_destroy - destroy the given core perक्रमmance context
 * @perf: Poपूर्णांकer to core perक्रमmance context
 */
व्योम dpu_core_perf_destroy(काष्ठा dpu_core_perf *perf);

/**
 * dpu_core_perf_init - initialize the given core perक्रमmance context
 * @perf: Poपूर्णांकer to core perक्रमmance context
 * @dev: Poपूर्णांकer to drm device
 * @catalog: Poपूर्णांकer to catalog
 * @core_clk: poपूर्णांकer to core घड़ी
 */
पूर्णांक dpu_core_perf_init(काष्ठा dpu_core_perf *perf,
		काष्ठा drm_device *dev,
		काष्ठा dpu_mdss_cfg *catalog,
		काष्ठा dss_clk *core_clk);

काष्ठा dpu_kms;

/**
 * dpu_core_perf_debugfs_init - initialize debugfs क्रम core perक्रमmance context
 * @dpu_kms: Poपूर्णांकer to the dpu_kms काष्ठा
 * @debugfs_parent: Poपूर्णांकer to parent debugfs
 */
पूर्णांक dpu_core_perf_debugfs_init(काष्ठा dpu_kms *dpu_kms, काष्ठा dentry *parent);

#पूर्ण_अगर /* _DPU_CORE_PERF_H_ */
