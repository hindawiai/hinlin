<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_blk.h"

/* Serialization lock क्रम dpu_hw_blk_list */
अटल DEFINE_MUTEX(dpu_hw_blk_lock);

/* List of all hw block objects */
अटल LIST_HEAD(dpu_hw_blk_list);

/**
 * dpu_hw_blk_init - initialize hw block object
 * @hw_blk: poपूर्णांकer to hw block object
 * @type: hw block type - क्रमागत dpu_hw_blk_type
 * @id: instance id of the hw block
 * @ops: Poपूर्णांकer to block operations
 */
व्योम dpu_hw_blk_init(काष्ठा dpu_hw_blk *hw_blk, u32 type, पूर्णांक id,
		काष्ठा dpu_hw_blk_ops *ops)
अणु
	INIT_LIST_HEAD(&hw_blk->list);
	hw_blk->type = type;
	hw_blk->id = id;
	atomic_set(&hw_blk->refcount, 0);

	अगर (ops)
		hw_blk->ops = *ops;

	mutex_lock(&dpu_hw_blk_lock);
	list_add(&hw_blk->list, &dpu_hw_blk_list);
	mutex_unlock(&dpu_hw_blk_lock);
पूर्ण

/**
 * dpu_hw_blk_destroy - destroy hw block object.
 * @hw_blk:  poपूर्णांकer to hw block object
 * वापस: none
 */
व्योम dpu_hw_blk_destroy(काष्ठा dpu_hw_blk *hw_blk)
अणु
	अगर (!hw_blk) अणु
		pr_err("invalid parameters\n");
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&hw_blk->refcount))
		pr_err("hw_blk:%d.%d invalid refcount\n", hw_blk->type,
				hw_blk->id);

	mutex_lock(&dpu_hw_blk_lock);
	list_del(&hw_blk->list);
	mutex_unlock(&dpu_hw_blk_lock);
पूर्ण

/**
 * dpu_hw_blk_get - get hw_blk from मुक्त pool
 * @hw_blk: अगर specअगरied, increment reference count only
 * @type: अगर hw_blk is not specअगरied, allocate the next available of this type
 * @id: अगर specअगरied (>= 0), allocate the given instance of the above type
 * वापस: poपूर्णांकer to hw block object
 */
काष्ठा dpu_hw_blk *dpu_hw_blk_get(काष्ठा dpu_hw_blk *hw_blk, u32 type, पूर्णांक id)
अणु
	काष्ठा dpu_hw_blk *curr;
	पूर्णांक rc, refcount;

	अगर (!hw_blk) अणु
		mutex_lock(&dpu_hw_blk_lock);
		list_क्रम_each_entry(curr, &dpu_hw_blk_list, list) अणु
			अगर ((curr->type != type) ||
					(id >= 0 && curr->id != id) ||
					(id < 0 &&
						atomic_पढ़ो(&curr->refcount)))
				जारी;

			hw_blk = curr;
			अवरोध;
		पूर्ण
		mutex_unlock(&dpu_hw_blk_lock);
	पूर्ण

	अगर (!hw_blk) अणु
		pr_debug("no hw_blk:%d\n", type);
		वापस शून्य;
	पूर्ण

	refcount = atomic_inc_वापस(&hw_blk->refcount);

	अगर (refcount == 1 && hw_blk->ops.start) अणु
		rc = hw_blk->ops.start(hw_blk);
		अगर (rc) अणु
			pr_err("failed to start  hw_blk:%d rc:%d\n", type, rc);
			जाओ error_start;
		पूर्ण
	पूर्ण

	pr_debug("hw_blk:%d.%d refcount:%d\n", hw_blk->type,
			hw_blk->id, refcount);
	वापस hw_blk;

error_start:
	dpu_hw_blk_put(hw_blk);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * dpu_hw_blk_put - put hw_blk to मुक्त pool अगर decremented refcount is zero
 * @hw_blk: hw block to be मुक्तd
 */
व्योम dpu_hw_blk_put(काष्ठा dpu_hw_blk *hw_blk)
अणु
	अगर (!hw_blk) अणु
		pr_err("invalid parameters\n");
		वापस;
	पूर्ण

	pr_debug("hw_blk:%d.%d refcount:%d\n", hw_blk->type, hw_blk->id,
			atomic_पढ़ो(&hw_blk->refcount));

	अगर (!atomic_पढ़ो(&hw_blk->refcount)) अणु
		pr_err("hw_blk:%d.%d invalid put\n", hw_blk->type, hw_blk->id);
		वापस;
	पूर्ण

	अगर (atomic_dec_वापस(&hw_blk->refcount))
		वापस;

	अगर (hw_blk->ops.stop)
		hw_blk->ops.stop(hw_blk);
पूर्ण
