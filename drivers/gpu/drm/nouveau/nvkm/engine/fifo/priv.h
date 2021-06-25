<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FIFO_PRIV_H__
#घोषणा __NVKM_FIFO_PRIV_H__
#घोषणा nvkm_fअगरo(p) container_of((p), काष्ठा nvkm_fअगरo, engine)
#समावेश <engine/fअगरo.h>

पूर्णांक nvkm_fअगरo_ctor(स्थिर काष्ठा nvkm_fअगरo_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   पूर्णांक nr, काष्ठा nvkm_fअगरo *);
व्योम nvkm_fअगरo_uevent(काष्ठा nvkm_fअगरo *);
व्योम nvkm_fअगरo_cevent(काष्ठा nvkm_fअगरo *);
व्योम nvkm_fअगरo_kevent(काष्ठा nvkm_fअगरo *, पूर्णांक chid);
व्योम nvkm_fअगरo_recover_chan(काष्ठा nvkm_fअगरo *, पूर्णांक chid);

काष्ठा nvkm_fअगरo_chan *
nvkm_fअगरo_chan_inst_locked(काष्ठा nvkm_fअगरo *, u64 inst);

काष्ठा nvkm_fअगरo_chan_oclass;
काष्ठा nvkm_fअगरo_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_fअगरo *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_fअगरo *);
	पूर्णांक (*info)(काष्ठा nvkm_fअगरo *, u64 mthd, u64 *data);
	व्योम (*init)(काष्ठा nvkm_fअगरo *);
	व्योम (*fini)(काष्ठा nvkm_fअगरo *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_fअगरo *);
	व्योम (*fault)(काष्ठा nvkm_fअगरo *, काष्ठा nvkm_fault_data *);
	पूर्णांक (*engine_id)(काष्ठा nvkm_fअगरo *, काष्ठा nvkm_engine *);
	काष्ठा nvkm_engine *(*id_engine)(काष्ठा nvkm_fअगरo *, पूर्णांक engi);
	व्योम (*छोड़ो)(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ *);
	व्योम (*start)(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ *);
	व्योम (*uevent_init)(काष्ठा nvkm_fअगरo *);
	व्योम (*uevent_fini)(काष्ठा nvkm_fअगरo *);
	व्योम (*recover_chan)(काष्ठा nvkm_fअगरo *, पूर्णांक chid);
	पूर्णांक (*class_get)(काष्ठा nvkm_fअगरo *, पूर्णांक index, काष्ठा nvkm_oclass *);
	पूर्णांक (*class_new)(काष्ठा nvkm_fअगरo *, स्थिर काष्ठा nvkm_oclass *,
			 व्योम *, u32, काष्ठा nvkm_object **);
	स्थिर काष्ठा nvkm_fअगरo_chan_oclass *chan[];
पूर्ण;

व्योम nv04_fअगरo_पूर्णांकr(काष्ठा nvkm_fअगरo *);
पूर्णांक nv04_fअगरo_engine_id(काष्ठा nvkm_fअगरo *, काष्ठा nvkm_engine *);
काष्ठा nvkm_engine *nv04_fअगरo_id_engine(काष्ठा nvkm_fअगरo *, पूर्णांक);
व्योम nv04_fअगरo_छोड़ो(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ *);
व्योम nv04_fअगरo_start(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ *);

व्योम gf100_fअगरo_पूर्णांकr_fault(काष्ठा nvkm_fअगरo *, पूर्णांक);

पूर्णांक gk104_fअगरo_engine_id(काष्ठा nvkm_fअगरo *, काष्ठा nvkm_engine *);
काष्ठा nvkm_engine *gk104_fअगरo_id_engine(काष्ठा nvkm_fअगरo *, पूर्णांक);
#पूर्ण_अगर
