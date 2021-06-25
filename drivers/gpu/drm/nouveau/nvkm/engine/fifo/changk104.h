<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __GK104_FIFO_CHAN_H__
#घोषणा __GK104_FIFO_CHAN_H__
#घोषणा gk104_fअगरo_chan(p) container_of((p), काष्ठा gk104_fअगरo_chan, base)
#समावेश "chan.h"
#समावेश "gk104.h"

काष्ठा gk104_fअगरo_chan अणु
	काष्ठा nvkm_fअगरo_chan base;
	काष्ठा gk104_fअगरo *fअगरo;
	पूर्णांक runl;

	काष्ठा nvkm_fअगरo_cgrp *cgrp;
	काष्ठा list_head head;
	bool समाप्तed;

	काष्ठा nvkm_memory *mthd;

#घोषणा GK104_FIFO_ENGN_SW 15
	काष्ठा gk104_fअगरo_engn अणु
		काष्ठा nvkm_gpuobj *inst;
		काष्ठा nvkm_vma *vma;
	पूर्ण engn[NVKM_FIFO_ENGN_NR];
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_func gk104_fअगरo_gpfअगरo_func;

पूर्णांक gk104_fअगरo_gpfअगरo_new(काष्ठा gk104_fअगरo *, स्थिर काष्ठा nvkm_oclass *,
			  व्योम *data, u32 size, काष्ठा nvkm_object **);
व्योम *gk104_fअगरo_gpfअगरo_dtor(काष्ठा nvkm_fअगरo_chan *);
व्योम gk104_fअगरo_gpfअगरo_init(काष्ठा nvkm_fअगरo_chan *);
व्योम gk104_fअगरo_gpfअगरo_fini(काष्ठा nvkm_fअगरo_chan *);
काष्ठा gk104_fअगरo_engn *gk104_fअगरo_gpfअगरo_engine(काष्ठा gk104_fअगरo_chan *, काष्ठा nvkm_engine *);
पूर्णांक gk104_fअगरo_gpfअगरo_engine_ctor(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_engine *,
				  काष्ठा nvkm_object *);
व्योम gk104_fअगरo_gpfअगरo_engine_dtor(काष्ठा nvkm_fअगरo_chan *,
				   काष्ठा nvkm_engine *);
पूर्णांक gk104_fअगरo_gpfअगरo_kick(काष्ठा gk104_fअगरo_chan *);
पूर्णांक gk104_fअगरo_gpfअगरo_kick_locked(काष्ठा gk104_fअगरo_chan *);

पूर्णांक gv100_fअगरo_gpfअगरo_new(काष्ठा gk104_fअगरo *, स्थिर काष्ठा nvkm_oclass *,
			  व्योम *data, u32 size, काष्ठा nvkm_object **);
पूर्णांक gv100_fअगरo_gpfअगरo_new_(स्थिर काष्ठा nvkm_fअगरo_chan_func *,
			   काष्ठा gk104_fअगरo *, u64 *, u16 *, u64, u64, u64,
			   u64 *, bool, u32 *, स्थिर काष्ठा nvkm_oclass *,
			   काष्ठा nvkm_object **);
पूर्णांक gv100_fअगरo_gpfअगरo_engine_init(काष्ठा nvkm_fअगरo_chan *,
				  काष्ठा nvkm_engine *);
पूर्णांक gv100_fअगरo_gpfअगरo_engine_fini(काष्ठा nvkm_fअगरo_chan *,
				  काष्ठा nvkm_engine *, bool);

पूर्णांक tu102_fअगरo_gpfअगरo_new(काष्ठा gk104_fअगरo *, स्थिर काष्ठा nvkm_oclass *,
			  व्योम *data, u32 size, काष्ठा nvkm_object **);
#पूर्ण_अगर
