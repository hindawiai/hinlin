<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FIFO_CHAN_H__
#घोषणा __NVKM_FIFO_CHAN_H__
#घोषणा nvkm_fअगरo_chan(p) container_of((p), काष्ठा nvkm_fअगरo_chan, object)
#समावेश "priv.h"

काष्ठा nvkm_fअगरo_chan_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_fअगरo_chan *);
	व्योम (*init)(काष्ठा nvkm_fअगरo_chan *);
	व्योम (*fini)(काष्ठा nvkm_fअगरo_chan *);
	पूर्णांक (*ntfy)(काष्ठा nvkm_fअगरo_chan *, u32 type, काष्ठा nvkm_event **);
	पूर्णांक  (*engine_ctor)(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_engine *,
			    काष्ठा nvkm_object *);
	व्योम (*engine_dtor)(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_engine *);
	पूर्णांक  (*engine_init)(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_engine *);
	पूर्णांक  (*engine_fini)(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_engine *,
			    bool suspend);
	पूर्णांक  (*object_ctor)(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_object *);
	व्योम (*object_dtor)(काष्ठा nvkm_fअगरo_chan *, पूर्णांक);
	u32 (*submit_token)(काष्ठा nvkm_fअगरo_chan *);
पूर्ण;

पूर्णांक nvkm_fअगरo_chan_ctor(स्थिर काष्ठा nvkm_fअगरo_chan_func *, काष्ठा nvkm_fअगरo *,
			u32 size, u32 align, bool zero, u64 vm, u64 push,
			u32 engm, पूर्णांक bar, u32 base, u32 user,
			स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_fअगरo_chan *);

काष्ठा nvkm_fअगरo_chan_oclass अणु
	पूर्णांक (*ctor)(काष्ठा nvkm_fअगरo *, स्थिर काष्ठा nvkm_oclass *,
		    व्योम *data, u32 size, काष्ठा nvkm_object **);
	काष्ठा nvkm_sclass base;
पूर्ण;

पूर्णांक gf100_fअगरo_chan_ntfy(काष्ठा nvkm_fअगरo_chan *, u32, काष्ठा nvkm_event **);
#पूर्ण_अगर
