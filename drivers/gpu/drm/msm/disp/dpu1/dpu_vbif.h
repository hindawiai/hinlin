<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DPU_VBIF_H__
#घोषणा __DPU_VBIF_H__

#समावेश "dpu_kms.h"

काष्ठा dpu_vbअगर_set_ot_params अणु
	u32 xin_id;
	u32 num;
	u32 width;
	u32 height;
	u32 frame_rate;
	bool rd;
	bool is_wfd;
	u32 vbअगर_idx;
	u32 clk_ctrl;
पूर्ण;

काष्ठा dpu_vbअगर_set_memtype_params अणु
	u32 xin_id;
	u32 vbअगर_idx;
	u32 clk_ctrl;
	bool is_cacheable;
पूर्ण;

/**
 * काष्ठा dpu_vbअगर_set_qos_params - QoS remapper parameter
 * @vbअगर_idx: vbअगर identअगरier
 * @xin_id: client पूर्णांकerface identअगरier
 * @clk_ctrl: घड़ी control identअगरier of the xin
 * @num: pipe identअगरier (debug only)
 * @is_rt: true अगर pipe is used in real-समय use हाल
 */
काष्ठा dpu_vbअगर_set_qos_params अणु
	u32 vbअगर_idx;
	u32 xin_id;
	u32 clk_ctrl;
	u32 num;
	bool is_rt;
पूर्ण;

/**
 * dpu_vbअगर_set_ot_limit - set OT limit क्रम vbअगर client
 * @dpu_kms:	DPU handler
 * @params:	Poपूर्णांकer to OT configuration parameters
 */
व्योम dpu_vbअगर_set_ot_limit(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dpu_vbअगर_set_ot_params *params);

/**
 * dpu_vbअगर_set_qos_remap - set QoS priority level remap
 * @dpu_kms:	DPU handler
 * @params:	Poपूर्णांकer to QoS configuration parameters
 */
व्योम dpu_vbअगर_set_qos_remap(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dpu_vbअगर_set_qos_params *params);

/**
 * dpu_vbअगर_clear_errors - clear any vbअगर errors
 * @dpu_kms:	DPU handler
 */
व्योम dpu_vbअगर_clear_errors(काष्ठा dpu_kms *dpu_kms);

/**
 * dpu_vbअगर_init_memtypes - initialize xin memory types क्रम vbअगर
 * @dpu_kms:	DPU handler
 */
व्योम dpu_vbअगर_init_memtypes(काष्ठा dpu_kms *dpu_kms);

व्योम dpu_debugfs_vbअगर_init(काष्ठा dpu_kms *dpu_kms, काष्ठा dentry *debugfs_root);

#पूर्ण_अगर /* __DPU_VBIF_H__ */
