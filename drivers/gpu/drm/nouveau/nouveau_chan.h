<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_CHAN_H__
#घोषणा __NOUVEAU_CHAN_H__
#समावेश <nvअगर/object.h>
#समावेश <nvअगर/notअगरy.h>
#समावेश <nvअगर/push.h>
काष्ठा nvअगर_device;

काष्ठा nouveau_channel अणु
	काष्ठा अणु
		काष्ठा nvअगर_push _push;
		काष्ठा nvअगर_push *push;
	पूर्ण chan;

	काष्ठा nvअगर_device *device;
	काष्ठा nouveau_drm *drm;
	काष्ठा nouveau_vmm *vmm;

	पूर्णांक chid;
	u64 inst;
	u32 token;

	काष्ठा nvअगर_object vram;
	काष्ठा nvअगर_object gart;
	काष्ठा nvअगर_object nvsw;

	काष्ठा अणु
		काष्ठा nouveau_bo *buffer;
		काष्ठा nouveau_vma *vma;
		काष्ठा nvअगर_object ctxdma;
		u64 addr;
	पूर्ण push;

	/* TODO: this will be reworked in the near future */
	bool accel_करोne;
	व्योम *fence;
	काष्ठा अणु
		पूर्णांक max;
		पूर्णांक मुक्त;
		पूर्णांक cur;
		पूर्णांक put;
		पूर्णांक ib_base;
		पूर्णांक ib_max;
		पूर्णांक ib_मुक्त;
		पूर्णांक ib_put;
	पूर्ण dma;
	u32 user_get_hi;
	u32 user_get;
	u32 user_put;

	काष्ठा nvअगर_object user;

	काष्ठा nvअगर_notअगरy समाप्त;
	atomic_t समाप्तed;
पूर्ण;

पूर्णांक nouveau_channels_init(काष्ठा nouveau_drm *);

पूर्णांक  nouveau_channel_new(काष्ठा nouveau_drm *, काष्ठा nvअगर_device *,
			 u32 arg0, u32 arg1, bool priv,
			 काष्ठा nouveau_channel **);
व्योम nouveau_channel_del(काष्ठा nouveau_channel **);
पूर्णांक  nouveau_channel_idle(काष्ठा nouveau_channel *);

बाह्य पूर्णांक nouveau_vram_pushbuf;

#पूर्ण_अगर
