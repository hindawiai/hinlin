<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __GK104_FIFO_H__
#घोषणा __GK104_FIFO_H__
#घोषणा gk104_fअगरo(p) container_of((p), काष्ठा gk104_fअगरo, base)
#समावेश "priv.h"
काष्ठा nvkm_fअगरo_cgrp;

#समावेश <core/क्रमागत.h>
#समावेश <subdev/mmu.h>

काष्ठा gk104_fअगरo_chan;
काष्ठा gk104_fअगरo अणु
	स्थिर काष्ठा gk104_fअगरo_func *func;
	काष्ठा nvkm_fअगरo base;

	काष्ठा अणु
		काष्ठा work_काष्ठा work;
		u32 engm;
		u32 runm;
	पूर्ण recover;

	पूर्णांक pbdma_nr;

	काष्ठा अणु
		काष्ठा nvkm_engine *engine;
		पूर्णांक runl;
		पूर्णांक pbid;
	पूर्ण engine[16];
	पूर्णांक engine_nr;

	काष्ठा अणु
		काष्ठा nvkm_memory *mem[2];
		पूर्णांक next;
		रुको_queue_head_t रुको;
		काष्ठा list_head cgrp;
		काष्ठा list_head chan;
		u32 engm;
		u32 engm_sw;
	पूर्ण runlist[16];
	पूर्णांक runlist_nr;

	काष्ठा अणु
		काष्ठा nvkm_memory *mem;
		काष्ठा nvkm_vma *bar;
	पूर्ण user;
पूर्ण;

काष्ठा gk104_fअगरo_func अणु
	काष्ठा अणु
		व्योम (*fault)(काष्ठा nvkm_fअगरo *, पूर्णांक unit);
	पूर्ण पूर्णांकr;

	स्थिर काष्ठा gk104_fअगरo_pbdma_func अणु
		पूर्णांक (*nr)(काष्ठा gk104_fअगरo *);
		व्योम (*init)(काष्ठा gk104_fअगरo *);
		व्योम (*init_समयout)(काष्ठा gk104_fअगरo *);
	पूर्ण *pbdma;

	काष्ठा अणु
		स्थिर काष्ठा nvkm_क्रमागत *access;
		स्थिर काष्ठा nvkm_क्रमागत *engine;
		स्थिर काष्ठा nvkm_क्रमागत *reason;
		स्थिर काष्ठा nvkm_क्रमागत *hubclient;
		स्थिर काष्ठा nvkm_क्रमागत *gpcclient;
	पूर्ण fault;

	स्थिर काष्ठा gk104_fअगरo_runlist_func अणु
		u8 size;
		व्योम (*cgrp)(काष्ठा nvkm_fअगरo_cgrp *,
			     काष्ठा nvkm_memory *, u32 offset);
		व्योम (*chan)(काष्ठा gk104_fअगरo_chan *,
			     काष्ठा nvkm_memory *, u32 offset);
		व्योम (*commit)(काष्ठा gk104_fअगरo *, पूर्णांक runl,
			       काष्ठा nvkm_memory *, पूर्णांक entries);
	पूर्ण *runlist;

	काष्ठा gk104_fअगरo_user_user अणु
		काष्ठा nvkm_sclass user;
		पूर्णांक (*ctor)(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			    काष्ठा nvkm_object **);
	पूर्ण user;

	काष्ठा gk104_fअगरo_chan_user अणु
		काष्ठा nvkm_sclass user;
		पूर्णांक (*ctor)(काष्ठा gk104_fअगरo *, स्थिर काष्ठा nvkm_oclass *,
			    व्योम *, u32, काष्ठा nvkm_object **);
	पूर्ण chan;
	bool cgrp_क्रमce;
पूर्ण;

काष्ठा gk104_fअगरo_engine_status अणु
	bool busy;
	bool faulted;
	bool chsw;
	bool save;
	bool load;
	काष्ठा अणु
		bool tsg;
		u32 id;
	पूर्ण prev, next, *chan;
पूर्ण;

पूर्णांक gk104_fअगरo_new_(स्थिर काष्ठा gk104_fअगरo_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		    पूर्णांक index, पूर्णांक nr, काष्ठा nvkm_fअगरo **);
व्योम gk104_fअगरo_runlist_insert(काष्ठा gk104_fअगरo *, काष्ठा gk104_fअगरo_chan *);
व्योम gk104_fअगरo_runlist_हटाओ(काष्ठा gk104_fअगरo *, काष्ठा gk104_fअगरo_chan *);
व्योम gk104_fअगरo_runlist_update(काष्ठा gk104_fअगरo *, पूर्णांक runl);
व्योम gk104_fअगरo_engine_status(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक engn,
			      काष्ठा gk104_fअगरo_engine_status *status);
व्योम gk104_fअगरo_पूर्णांकr_bind(काष्ठा gk104_fअगरo *fअगरo);
व्योम gk104_fअगरo_पूर्णांकr_chsw(काष्ठा gk104_fअगरo *fअगरo);
व्योम gk104_fअगरo_पूर्णांकr_dropped_fault(काष्ठा gk104_fअगरo *fअगरo);
व्योम gk104_fअगरo_पूर्णांकr_pbdma_0(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक unit);
व्योम gk104_fअगरo_पूर्णांकr_pbdma_1(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक unit);
व्योम gk104_fअगरo_पूर्णांकr_runlist(काष्ठा gk104_fअगरo *fअगरo);
व्योम gk104_fअगरo_पूर्णांकr_engine(काष्ठा gk104_fअगरo *fअगरo);
व्योम *gk104_fअगरo_dtor(काष्ठा nvkm_fअगरo *base);
पूर्णांक gk104_fअगरo_oneinit(काष्ठा nvkm_fअगरo *base);
पूर्णांक gk104_fअगरo_info(काष्ठा nvkm_fअगरo *base, u64 mthd, u64 *data);
व्योम gk104_fअगरo_init(काष्ठा nvkm_fअगरo *base);
व्योम gk104_fअगरo_fini(काष्ठा nvkm_fअगरo *base);
पूर्णांक gk104_fअगरo_class_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
			 व्योम *argv, u32 argc, काष्ठा nvkm_object **pobject);
पूर्णांक gk104_fअगरo_class_get(काष्ठा nvkm_fअगरo *base, पूर्णांक index,
			 काष्ठा nvkm_oclass *oclass);
व्योम gk104_fअगरo_uevent_fini(काष्ठा nvkm_fअगरo *fअगरo);
व्योम gk104_fअगरo_uevent_init(काष्ठा nvkm_fअगरo *fअगरo);

बाह्य स्थिर काष्ठा gk104_fअगरo_pbdma_func gk104_fअगरo_pbdma;
पूर्णांक gk104_fअगरo_pbdma_nr(काष्ठा gk104_fअगरo *);
व्योम gk104_fअगरo_pbdma_init(काष्ठा gk104_fअगरo *);
बाह्य स्थिर काष्ठा nvkm_क्रमागत gk104_fअगरo_fault_access[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gk104_fअगरo_fault_engine[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gk104_fअगरo_fault_reason[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gk104_fअगरo_fault_hubclient[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gk104_fअगरo_fault_gpcclient[];
बाह्य स्थिर काष्ठा gk104_fअगरo_runlist_func gk104_fअगरo_runlist;
व्योम gk104_fअगरo_runlist_chan(काष्ठा gk104_fअगरo_chan *,
			     काष्ठा nvkm_memory *, u32);
व्योम gk104_fअगरo_runlist_commit(काष्ठा gk104_fअगरo *, पूर्णांक runl,
			       काष्ठा nvkm_memory *, पूर्णांक);

बाह्य स्थिर काष्ठा gk104_fअगरo_runlist_func gk110_fअगरo_runlist;
व्योम gk110_fअगरo_runlist_cgrp(काष्ठा nvkm_fअगरo_cgrp *,
			     काष्ठा nvkm_memory *, u32);

बाह्य स्थिर काष्ठा gk104_fअगरo_pbdma_func gk208_fअगरo_pbdma;
व्योम gk208_fअगरo_pbdma_init_समयout(काष्ठा gk104_fअगरo *);

व्योम gm107_fअगरo_पूर्णांकr_fault(काष्ठा nvkm_fअगरo *, पूर्णांक);
बाह्य स्थिर काष्ठा nvkm_क्रमागत gm107_fअगरo_fault_engine[];
बाह्य स्थिर काष्ठा gk104_fअगरo_runlist_func gm107_fअगरo_runlist;

बाह्य स्थिर काष्ठा gk104_fअगरo_pbdma_func gm200_fअगरo_pbdma;
पूर्णांक gm200_fअगरo_pbdma_nr(काष्ठा gk104_fअगरo *);

व्योम gp100_fअगरo_पूर्णांकr_fault(काष्ठा nvkm_fअगरo *, पूर्णांक);
बाह्य स्थिर काष्ठा nvkm_क्रमागत gp100_fअगरo_fault_engine[];

बाह्य स्थिर काष्ठा nvkm_क्रमागत gv100_fअगरo_fault_access[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gv100_fअगरo_fault_reason[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gv100_fअगरo_fault_hubclient[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gv100_fअगरo_fault_gpcclient[];
व्योम gv100_fअगरo_runlist_cgrp(काष्ठा nvkm_fअगरo_cgrp *,
			     काष्ठा nvkm_memory *, u32);
व्योम gv100_fअगरo_runlist_chan(काष्ठा gk104_fअगरo_chan *,
			     काष्ठा nvkm_memory *, u32);
#पूर्ण_अगर
