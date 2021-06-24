<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __GF100_FIFO_H__
#घोषणा __GF100_FIFO_H__
#घोषणा gf100_fअगरo(p) container_of((p), काष्ठा gf100_fअगरo, base)
#समावेश "priv.h"

#समावेश <subdev/mmu.h>

काष्ठा gf100_fअगरo_chan;
काष्ठा gf100_fअगरo अणु
	काष्ठा nvkm_fअगरo base;

	काष्ठा list_head chan;

	काष्ठा अणु
		काष्ठा work_काष्ठा work;
		u64 mask;
	पूर्ण recover;

	पूर्णांक pbdma_nr;

	काष्ठा अणु
		काष्ठा nvkm_memory *mem[2];
		पूर्णांक active;
		रुको_queue_head_t रुको;
	पूर्ण runlist;

	काष्ठा अणु
		काष्ठा nvkm_memory *mem;
		काष्ठा nvkm_vma *bar;
	पूर्ण user;
पूर्ण;

व्योम gf100_fअगरo_पूर्णांकr_engine(काष्ठा gf100_fअगरo *);
व्योम gf100_fअगरo_runlist_insert(काष्ठा gf100_fअगरo *, काष्ठा gf100_fअगरo_chan *);
व्योम gf100_fअगरo_runlist_हटाओ(काष्ठा gf100_fअगरo *, काष्ठा gf100_fअगरo_chan *);
व्योम gf100_fअगरo_runlist_commit(काष्ठा gf100_fअगरo *);
#पूर्ण_अगर
