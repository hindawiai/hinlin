<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV10_FENCE_H_
#घोषणा __NV10_FENCE_H_

#समावेश "nouveau_fence.h"
#समावेश "nouveau_bo.h"

काष्ठा nv10_fence_chan अणु
	काष्ठा nouveau_fence_chan base;
	काष्ठा nvअगर_object sema;
पूर्ण;

काष्ठा nv10_fence_priv अणु
	काष्ठा nouveau_fence_priv base;
	काष्ठा nouveau_bo *bo;
	spinlock_t lock;
	u32 sequence;
पूर्ण;

#पूर्ण_अगर
