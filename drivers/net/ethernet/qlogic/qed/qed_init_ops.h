<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_INIT_OPS_H
#घोषणा _QED_INIT_OPS_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश "qed.h"

/**
 * @brief qed_init_iro_array - init iro_arr.
 *
 *
 * @param cdev
 */
व्योम qed_init_iro_array(काष्ठा qed_dev *cdev);

/**
 * @brief qed_init_run - Run the init-sequence.
 *
 *
 * @param p_hwfn
 * @param p_ptt
 * @param phase
 * @param phase_id
 * @param modes
 * @वापस _qed_status_t
 */
पूर्णांक qed_init_run(काष्ठा qed_hwfn *p_hwfn,
		 काष्ठा qed_ptt *p_ptt,
		 पूर्णांक phase,
		 पूर्णांक phase_id,
		 पूर्णांक modes);

/**
 * @brief qed_init_hwfn_allocate - Allocate RT array, Store 'values' ptrs.
 *
 *
 * @param p_hwfn
 *
 * @वापस _qed_status_t
 */
पूर्णांक qed_init_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_init_hwfn_deallocate
 *
 *
 * @param p_hwfn
 */
व्योम qed_init_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_init_store_rt_reg - Store a configuration value in the RT array.
 *
 *
 * @param p_hwfn
 * @param rt_offset
 * @param val
 */
व्योम qed_init_store_rt_reg(काष्ठा qed_hwfn *p_hwfn,
			   u32 rt_offset,
			   u32 val);

#घोषणा STORE_RT_REG(hwfn, offset, val)	\
	qed_init_store_rt_reg(hwfn, offset, val)

#घोषणा OVERWRITE_RT_REG(hwfn, offset, val) \
	qed_init_store_rt_reg(hwfn, offset, val)

/**
 * @brief
 *
 *
 * @param p_hwfn
 * @param rt_offset
 * @param val
 * @param size
 */
व्योम qed_init_store_rt_agg(काष्ठा qed_hwfn *p_hwfn,
			   u32 rt_offset,
			   u32 *val,
			   माप_प्रकार size);

#घोषणा STORE_RT_REG_AGG(hwfn, offset, val) \
	qed_init_store_rt_agg(hwfn, offset, (u32 *)&val, माप(val))

/**
 * @brief
 *      Initialize GTT global winकरोws and set admin winकरोw
 *      related params of GTT/PTT to शेष values.
 *
 * @param p_hwfn
 */
व्योम qed_gtt_init(काष्ठा qed_hwfn *p_hwfn);
#पूर्ण_अगर
