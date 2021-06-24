<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dma-fence-array: aggregate fences to be रुकोed together
 *
 * Copyright (C) 2016 Collabora Ltd
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 * Authors:
 *	Gustavo Paकरोvan <gustavo@paकरोvan.org>
 *	Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-fence-array.h>

#घोषणा PENDING_ERROR 1

अटल स्थिर अक्षर *dma_fence_array_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "dma_fence_array";
पूर्ण

अटल स्थिर अक्षर *dma_fence_array_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	वापस "unbound";
पूर्ण

अटल व्योम dma_fence_array_set_pending_error(काष्ठा dma_fence_array *array,
					      पूर्णांक error)
अणु
	/*
	 * Propagate the first error reported by any of our fences, but only
	 * beक्रमe we ourselves are संकेतed.
	 */
	अगर (error)
		cmpxchg(&array->base.error, PENDING_ERROR, error);
पूर्ण

अटल व्योम dma_fence_array_clear_pending_error(काष्ठा dma_fence_array *array)
अणु
	/* Clear the error flag अगर not actually set. */
	cmpxchg(&array->base.error, PENDING_ERROR, 0);
पूर्ण

अटल व्योम irq_dma_fence_array_work(काष्ठा irq_work *wrk)
अणु
	काष्ठा dma_fence_array *array = container_of(wrk, typeof(*array), work);

	dma_fence_array_clear_pending_error(array);

	dma_fence_संकेत(&array->base);
	dma_fence_put(&array->base);
पूर्ण

अटल व्योम dma_fence_array_cb_func(काष्ठा dma_fence *f,
				    काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा dma_fence_array_cb *array_cb =
		container_of(cb, काष्ठा dma_fence_array_cb, cb);
	काष्ठा dma_fence_array *array = array_cb->array;

	dma_fence_array_set_pending_error(array, f->error);

	अगर (atomic_dec_and_test(&array->num_pending))
		irq_work_queue(&array->work);
	अन्यथा
		dma_fence_put(&array->base);
पूर्ण

अटल bool dma_fence_array_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_array *array = to_dma_fence_array(fence);
	काष्ठा dma_fence_array_cb *cb = (व्योम *)(&array[1]);
	अचिन्हित i;

	क्रम (i = 0; i < array->num_fences; ++i) अणु
		cb[i].array = array;
		/*
		 * As we may report that the fence is संकेतed beक्रमe all
		 * callbacks are complete, we need to take an additional
		 * reference count on the array so that we करो not मुक्त it too
		 * early. The core fence handling will only hold the reference
		 * until we संकेत the array as complete (but that is now
		 * insufficient).
		 */
		dma_fence_get(&array->base);
		अगर (dma_fence_add_callback(array->fences[i], &cb[i].cb,
					   dma_fence_array_cb_func)) अणु
			पूर्णांक error = array->fences[i]->error;

			dma_fence_array_set_pending_error(array, error);
			dma_fence_put(&array->base);
			अगर (atomic_dec_and_test(&array->num_pending)) अणु
				dma_fence_array_clear_pending_error(array);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool dma_fence_array_संकेतed(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_array *array = to_dma_fence_array(fence);

	वापस atomic_पढ़ो(&array->num_pending) <= 0;
पूर्ण

अटल व्योम dma_fence_array_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_array *array = to_dma_fence_array(fence);
	अचिन्हित i;

	क्रम (i = 0; i < array->num_fences; ++i)
		dma_fence_put(array->fences[i]);

	kमुक्त(array->fences);
	dma_fence_मुक्त(fence);
पूर्ण

स्थिर काष्ठा dma_fence_ops dma_fence_array_ops = अणु
	.get_driver_name = dma_fence_array_get_driver_name,
	.get_समयline_name = dma_fence_array_get_समयline_name,
	.enable_संकेतing = dma_fence_array_enable_संकेतing,
	.संकेतed = dma_fence_array_संकेतed,
	.release = dma_fence_array_release,
पूर्ण;
EXPORT_SYMBOL(dma_fence_array_ops);

/**
 * dma_fence_array_create - Create a custom fence array
 * @num_fences:		[in]	number of fences to add in the array
 * @fences:		[in]	array containing the fences
 * @context:		[in]	fence context to use
 * @seqno:		[in]	sequence number to use
 * @संकेत_on_any:	[in]	संकेत on any fence in the array
 *
 * Allocate a dma_fence_array object and initialize the base fence with
 * dma_fence_init().
 * In हाल of error it वापसs शून्य.
 *
 * The caller should allocate the fences array with num_fences size
 * and fill it with the fences it wants to add to the object. Ownership of this
 * array is taken and dma_fence_put() is used on each fence on release.
 *
 * If @संकेत_on_any is true the fence array संकेतs अगर any fence in the array
 * संकेतs, otherwise it संकेतs when all fences in the array संकेत.
 */
काष्ठा dma_fence_array *dma_fence_array_create(पूर्णांक num_fences,
					       काष्ठा dma_fence **fences,
					       u64 context, अचिन्हित seqno,
					       bool संकेत_on_any)
अणु
	काष्ठा dma_fence_array *array;
	माप_प्रकार size = माप(*array);

	/* Allocate the callback काष्ठाures behind the array. */
	size += num_fences * माप(काष्ठा dma_fence_array_cb);
	array = kzalloc(size, GFP_KERNEL);
	अगर (!array)
		वापस शून्य;

	spin_lock_init(&array->lock);
	dma_fence_init(&array->base, &dma_fence_array_ops, &array->lock,
		       context, seqno);
	init_irq_work(&array->work, irq_dma_fence_array_work);

	array->num_fences = num_fences;
	atomic_set(&array->num_pending, संकेत_on_any ? 1 : num_fences);
	array->fences = fences;

	array->base.error = PENDING_ERROR;

	वापस array;
पूर्ण
EXPORT_SYMBOL(dma_fence_array_create);

/**
 * dma_fence_match_context - Check अगर all fences are from the given context
 * @fence:		[in]	fence or fence array
 * @context:		[in]	fence context to check all fences against
 *
 * Checks the provided fence or, क्रम a fence array, all fences in the array
 * against the given context. Returns false अगर any fence is from a dअगरferent
 * context.
 */
bool dma_fence_match_context(काष्ठा dma_fence *fence, u64 context)
अणु
	काष्ठा dma_fence_array *array = to_dma_fence_array(fence);
	अचिन्हित i;

	अगर (!dma_fence_is_array(fence))
		वापस fence->context == context;

	क्रम (i = 0; i < array->num_fences; i++) अणु
		अगर (array->fences[i]->context != context)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(dma_fence_match_context);
