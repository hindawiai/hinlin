<शैली गुरु>
/*
 * Copyright (C) 2013 Red Hat
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित DRM_FLIP_WORK_H
#घोषणा DRM_FLIP_WORK_H

#समावेश <linux/kfअगरo.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

/**
 * DOC: flip utils
 *
 * Util to queue up work to run from work-queue context after flip/vblank.
 * Typically this can be used to defer unref of framebuffer's, cursor
 * bo's, etc until after vblank.  The APIs are all thपढ़ो-safe.
 * Moreover, drm_flip_work_queue_task and drm_flip_work_queue can be called
 * in atomic context.
 */

काष्ठा drm_flip_work;

/*
 * drm_flip_func_t - callback function
 *
 * @work: the flip work
 * @val: value queued via drm_flip_work_queue()
 *
 * Callback function to be called क्रम each of the  queue'd work items after
 * drm_flip_work_commit() is called.
 */
प्रकार व्योम (*drm_flip_func_t)(काष्ठा drm_flip_work *work, व्योम *val);

/**
 * काष्ठा drm_flip_task - flip work task
 * @node: list entry element
 * @data: data to pass to &drm_flip_work.func
 */
काष्ठा drm_flip_task अणु
	काष्ठा list_head node;
	व्योम *data;
पूर्ण;

/**
 * काष्ठा drm_flip_work - flip work queue
 * @name: debug name
 * @func: callback fxn called क्रम each committed item
 * @worker: worker which calls @func
 * @queued: queued tasks
 * @commited: commited tasks
 * @lock: lock to access queued and commited lists
 */
काष्ठा drm_flip_work अणु
	स्थिर अक्षर *name;
	drm_flip_func_t func;
	काष्ठा work_काष्ठा worker;
	काष्ठा list_head queued;
	काष्ठा list_head commited;
	spinlock_t lock;
पूर्ण;

काष्ठा drm_flip_task *drm_flip_work_allocate_task(व्योम *data, gfp_t flags);
व्योम drm_flip_work_queue_task(काष्ठा drm_flip_work *work,
			      काष्ठा drm_flip_task *task);
व्योम drm_flip_work_queue(काष्ठा drm_flip_work *work, व्योम *val);
व्योम drm_flip_work_commit(काष्ठा drm_flip_work *work,
		काष्ठा workqueue_काष्ठा *wq);
व्योम drm_flip_work_init(काष्ठा drm_flip_work *work,
		स्थिर अक्षर *name, drm_flip_func_t func);
व्योम drm_flip_work_cleanup(काष्ठा drm_flip_work *work);

#पूर्ण_अगर  /* DRM_FLIP_WORK_H */
