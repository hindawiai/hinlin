<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_FENCE_H__
#घोषणा __NOUVEAU_FENCE_H__

#समावेश <linux/dma-fence.h>
#समावेश <nvअगर/notअगरy.h>

काष्ठा nouveau_drm;
काष्ठा nouveau_bo;

काष्ठा nouveau_fence अणु
	काष्ठा dma_fence base;

	काष्ठा list_head head;

	काष्ठा nouveau_channel __rcu *channel;
	अचिन्हित दीर्घ समयout;
पूर्ण;

पूर्णांक  nouveau_fence_new(काष्ठा nouveau_channel *, bool sysmem,
		       काष्ठा nouveau_fence **);
व्योम nouveau_fence_unref(काष्ठा nouveau_fence **);

पूर्णांक  nouveau_fence_emit(काष्ठा nouveau_fence *, काष्ठा nouveau_channel *);
bool nouveau_fence_करोne(काष्ठा nouveau_fence *);
पूर्णांक  nouveau_fence_रुको(काष्ठा nouveau_fence *, bool lazy, bool पूर्णांकr);
पूर्णांक  nouveau_fence_sync(काष्ठा nouveau_bo *, काष्ठा nouveau_channel *, bool exclusive, bool पूर्णांकr);

काष्ठा nouveau_fence_chan अणु
	spinlock_t lock;
	काष्ठा kref fence_ref;

	काष्ठा list_head pending;
	काष्ठा list_head flip;

	पूर्णांक  (*emit)(काष्ठा nouveau_fence *);
	पूर्णांक  (*sync)(काष्ठा nouveau_fence *, काष्ठा nouveau_channel *,
		     काष्ठा nouveau_channel *);
	u32  (*पढ़ो)(काष्ठा nouveau_channel *);
	पूर्णांक  (*emit32)(काष्ठा nouveau_channel *, u64, u32);
	पूर्णांक  (*sync32)(काष्ठा nouveau_channel *, u64, u32);

	u32 sequence;
	u32 context;
	अक्षर name[32];

	काष्ठा nvअगर_notअगरy notअगरy;
	पूर्णांक notअगरy_ref, dead;
पूर्ण;

काष्ठा nouveau_fence_priv अणु
	व्योम (*dtor)(काष्ठा nouveau_drm *);
	bool (*suspend)(काष्ठा nouveau_drm *);
	व्योम (*resume)(काष्ठा nouveau_drm *);
	पूर्णांक  (*context_new)(काष्ठा nouveau_channel *);
	व्योम (*context_del)(काष्ठा nouveau_channel *);

	bool uevent;
पूर्ण;

#घोषणा nouveau_fence(drm) ((काष्ठा nouveau_fence_priv *)(drm)->fence)

व्योम nouveau_fence_context_new(काष्ठा nouveau_channel *, काष्ठा nouveau_fence_chan *);
व्योम nouveau_fence_context_del(काष्ठा nouveau_fence_chan *);
व्योम nouveau_fence_context_मुक्त(काष्ठा nouveau_fence_chan *);
व्योम nouveau_fence_context_समाप्त(काष्ठा nouveau_fence_chan *, पूर्णांक error);

पूर्णांक nv04_fence_create(काष्ठा nouveau_drm *);
पूर्णांक nv04_fence_mthd(काष्ठा nouveau_channel *, u32, u32, u32);

पूर्णांक  nv10_fence_emit(काष्ठा nouveau_fence *);
पूर्णांक  nv17_fence_sync(काष्ठा nouveau_fence *, काष्ठा nouveau_channel *,
		     काष्ठा nouveau_channel *);
u32  nv10_fence_पढ़ो(काष्ठा nouveau_channel *);
व्योम nv10_fence_context_del(काष्ठा nouveau_channel *);
व्योम nv10_fence_destroy(काष्ठा nouveau_drm *);
पूर्णांक  nv10_fence_create(काष्ठा nouveau_drm *);

पूर्णांक  nv17_fence_create(काष्ठा nouveau_drm *);
व्योम nv17_fence_resume(काष्ठा nouveau_drm *drm);

पूर्णांक nv50_fence_create(काष्ठा nouveau_drm *);
पूर्णांक nv84_fence_create(काष्ठा nouveau_drm *);
पूर्णांक nvc0_fence_create(काष्ठा nouveau_drm *);

काष्ठा nv84_fence_chan अणु
	काष्ठा nouveau_fence_chan base;
	काष्ठा nouveau_vma *vma;
पूर्ण;

काष्ठा nv84_fence_priv अणु
	काष्ठा nouveau_fence_priv base;
	काष्ठा nouveau_bo *bo;
	u32 *suspend;
	काष्ठा mutex mutex;
पूर्ण;

पूर्णांक  nv84_fence_context_new(काष्ठा nouveau_channel *);

#पूर्ण_अगर
