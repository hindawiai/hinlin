<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * i915_sw_fence.h - library routines क्रम N:M synchronisation poपूर्णांकs
 *
 * Copyright (C) 2016 Intel Corporation
 */

#अगर_अघोषित _I915_SW_FENCE_H_
#घोषणा _I915_SW_FENCE_H_

#समावेश <linux/dma-fence.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kref.h>
#समावेश <linux/notअगरier.h> /* क्रम NOTIFY_DONE */
#समावेश <linux/रुको.h>

काष्ठा completion;
काष्ठा dma_resv;

काष्ठा i915_sw_fence अणु
	रुको_queue_head_t रुको;
	अचिन्हित दीर्घ flags;
	atomic_t pending;
	पूर्णांक error;
पूर्ण;

#घोषणा I915_SW_FENCE_CHECKED_BIT	0 /* used पूर्णांकernally क्रम DAG checking */
#घोषणा I915_SW_FENCE_PRIVATE_BIT	1 /* available क्रम use by owner */
#घोषणा I915_SW_FENCE_MASK		(~3)

क्रमागत i915_sw_fence_notअगरy अणु
	FENCE_COMPLETE,
	FENCE_FREE
पूर्ण;

प्रकार पूर्णांक (*i915_sw_fence_notअगरy_t)(काष्ठा i915_sw_fence *,
				      क्रमागत i915_sw_fence_notअगरy state);
#घोषणा __i915_sw_fence_call __aligned(4)

व्योम __i915_sw_fence_init(काष्ठा i915_sw_fence *fence,
			  i915_sw_fence_notअगरy_t fn,
			  स्थिर अक्षर *name,
			  काष्ठा lock_class_key *key);
#अगर_घोषित CONFIG_LOCKDEP
#घोषणा i915_sw_fence_init(fence, fn)				\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	__i915_sw_fence_init((fence), (fn), #fence, &__key);	\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा i915_sw_fence_init(fence, fn)				\
	__i915_sw_fence_init((fence), (fn), शून्य, शून्य)
#पूर्ण_अगर

व्योम i915_sw_fence_reinit(काष्ठा i915_sw_fence *fence);

#अगर_घोषित CONFIG_DRM_I915_SW_FENCE_DEBUG_OBJECTS
व्योम i915_sw_fence_fini(काष्ठा i915_sw_fence *fence);
#अन्यथा
अटल अंतरभूत व्योम i915_sw_fence_fini(काष्ठा i915_sw_fence *fence) अणुपूर्ण
#पूर्ण_अगर

व्योम i915_sw_fence_commit(काष्ठा i915_sw_fence *fence);

पूर्णांक i915_sw_fence_aरुको_sw_fence(काष्ठा i915_sw_fence *fence,
				 काष्ठा i915_sw_fence *after,
				 रुको_queue_entry_t *wq);
पूर्णांक i915_sw_fence_aरुको_sw_fence_gfp(काष्ठा i915_sw_fence *fence,
				     काष्ठा i915_sw_fence *after,
				     gfp_t gfp);

काष्ठा i915_sw_dma_fence_cb अणु
	काष्ठा dma_fence_cb base;
	काष्ठा i915_sw_fence *fence;
पूर्ण;

पूर्णांक __i915_sw_fence_aरुको_dma_fence(काष्ठा i915_sw_fence *fence,
				    काष्ठा dma_fence *dma,
				    काष्ठा i915_sw_dma_fence_cb *cb);
पूर्णांक i915_sw_fence_aरुको_dma_fence(काष्ठा i915_sw_fence *fence,
				  काष्ठा dma_fence *dma,
				  अचिन्हित दीर्घ समयout,
				  gfp_t gfp);

पूर्णांक i915_sw_fence_aरुको_reservation(काष्ठा i915_sw_fence *fence,
				    काष्ठा dma_resv *resv,
				    स्थिर काष्ठा dma_fence_ops *exclude,
				    bool ग_लिखो,
				    अचिन्हित दीर्घ समयout,
				    gfp_t gfp);

bool i915_sw_fence_aरुको(काष्ठा i915_sw_fence *fence);
व्योम i915_sw_fence_complete(काष्ठा i915_sw_fence *fence);

अटल अंतरभूत bool i915_sw_fence_संकेतed(स्थिर काष्ठा i915_sw_fence *fence)
अणु
	वापस atomic_पढ़ो(&fence->pending) <= 0;
पूर्ण

अटल अंतरभूत bool i915_sw_fence_करोne(स्थिर काष्ठा i915_sw_fence *fence)
अणु
	वापस atomic_पढ़ो(&fence->pending) < 0;
पूर्ण

अटल अंतरभूत व्योम i915_sw_fence_रुको(काष्ठा i915_sw_fence *fence)
अणु
	रुको_event(fence->रुको, i915_sw_fence_करोne(fence));
पूर्ण

अटल अंतरभूत व्योम
i915_sw_fence_set_error_once(काष्ठा i915_sw_fence *fence, पूर्णांक error)
अणु
	अगर (unlikely(error))
		cmpxchg(&fence->error, 0, error);
पूर्ण

#पूर्ण_अगर /* _I915_SW_FENCE_H_ */
