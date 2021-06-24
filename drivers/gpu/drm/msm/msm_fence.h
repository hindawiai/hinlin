<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013-2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_FENCE_H__
#घोषणा __MSM_FENCE_H__

#समावेश "msm_drv.h"

काष्ठा msm_fence_context अणु
	काष्ठा drm_device *dev;
	अक्षर name[32];
	अचिन्हित context;
	/* last_fence == completed_fence --> no pending work */
	uपूर्णांक32_t last_fence;          /* last asचिन्हित fence */
	uपूर्णांक32_t completed_fence;     /* last completed fence */
	रुको_queue_head_t event;
	spinlock_t spinlock;
पूर्ण;

काष्ठा msm_fence_context * msm_fence_context_alloc(काष्ठा drm_device *dev,
		स्थिर अक्षर *name);
व्योम msm_fence_context_मुक्त(काष्ठा msm_fence_context *fctx);

पूर्णांक msm_रुको_fence(काष्ठा msm_fence_context *fctx, uपूर्णांक32_t fence,
		kसमय_प्रकार *समयout, bool पूर्णांकerruptible);
व्योम msm_update_fence(काष्ठा msm_fence_context *fctx, uपूर्णांक32_t fence);

काष्ठा dma_fence * msm_fence_alloc(काष्ठा msm_fence_context *fctx);

#पूर्ण_अगर
