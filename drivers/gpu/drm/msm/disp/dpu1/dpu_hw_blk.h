<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_BLK_H
#घोषणा _DPU_HW_BLK_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/atomic.h>

काष्ठा dpu_hw_blk;

/**
 * काष्ठा dpu_hw_blk_ops - common hardware block operations
 * @start: start operation on first get
 * @stop: stop operation on last put
 */
काष्ठा dpu_hw_blk_ops अणु
	पूर्णांक (*start)(काष्ठा dpu_hw_blk *);
	व्योम (*stop)(काष्ठा dpu_hw_blk *);
पूर्ण;

/**
 * काष्ठा dpu_hw_blk - definition of hardware block object
 * @list: list of hardware blocks
 * @type: hardware block type
 * @id: instance id
 * @refcount: reference/usage count
 */
काष्ठा dpu_hw_blk अणु
	काष्ठा list_head list;
	u32 type;
	पूर्णांक id;
	atomic_t refcount;
	काष्ठा dpu_hw_blk_ops ops;
पूर्ण;

व्योम dpu_hw_blk_init(काष्ठा dpu_hw_blk *hw_blk, u32 type, पूर्णांक id,
		काष्ठा dpu_hw_blk_ops *ops);
व्योम dpu_hw_blk_destroy(काष्ठा dpu_hw_blk *hw_blk);

काष्ठा dpu_hw_blk *dpu_hw_blk_get(काष्ठा dpu_hw_blk *hw_blk, u32 type, पूर्णांक id);
व्योम dpu_hw_blk_put(काष्ठा dpu_hw_blk *hw_blk);
#पूर्ण_अगर /*_DPU_HW_BLK_H */
