<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_FIFO_CHAN_H__
#घोषणा __NV50_FIFO_CHAN_H__
#घोषणा nv50_fअगरo_chan(p) container_of((p), काष्ठा nv50_fअगरo_chan, base)
#समावेश "chan.h"
#समावेश "nv50.h"

काष्ठा nv50_fअगरo_chan अणु
	काष्ठा nv50_fअगरo *fअगरo;
	काष्ठा nvkm_fअगरo_chan base;

	काष्ठा nvkm_gpuobj *ramfc;
	काष्ठा nvkm_gpuobj *cache;
	काष्ठा nvkm_gpuobj *eng;
	काष्ठा nvkm_gpuobj *pgd;
	काष्ठा nvkm_ramht *ramht;

#घोषणा NV50_FIFO_ENGN_SW   0
#घोषणा NV50_FIFO_ENGN_GR   1
#घोषणा NV50_FIFO_ENGN_MPEG 2
#घोषणा NV50_FIFO_ENGN_DMA  3

#घोषणा G84_FIFO_ENGN_SW     0
#घोषणा G84_FIFO_ENGN_GR     1
#घोषणा G84_FIFO_ENGN_MPEG   2
#घोषणा G84_FIFO_ENGN_MSPPP  2
#घोषणा G84_FIFO_ENGN_ME     3
#घोषणा G84_FIFO_ENGN_CE0    3
#घोषणा G84_FIFO_ENGN_VP     4
#घोषणा G84_FIFO_ENGN_MSPDEC 4
#घोषणा G84_FIFO_ENGN_CIPHER 5
#घोषणा G84_FIFO_ENGN_SEC    5
#घोषणा G84_FIFO_ENGN_VIC    5
#घोषणा G84_FIFO_ENGN_BSP    6
#घोषणा G84_FIFO_ENGN_MSVLD  6
#घोषणा G84_FIFO_ENGN_DMA    7
	काष्ठा nvkm_gpuobj *engn[NVKM_FIFO_ENGN_NR];
पूर्ण;

पूर्णांक nv50_fअगरo_chan_ctor(काष्ठा nv50_fअगरo *, u64 vmm, u64 push,
			स्थिर काष्ठा nvkm_oclass *, काष्ठा nv50_fअगरo_chan *);
व्योम *nv50_fअगरo_chan_dtor(काष्ठा nvkm_fअगरo_chan *);
व्योम nv50_fअगरo_chan_fini(काष्ठा nvkm_fअगरo_chan *);
काष्ठा nvkm_gpuobj **nv50_fअगरo_chan_engine(काष्ठा nv50_fअगरo_chan *, काष्ठा nvkm_engine *);
व्योम nv50_fअगरo_chan_engine_dtor(काष्ठा nvkm_fअगरo_chan *, काष्ठा nvkm_engine *);
व्योम nv50_fअगरo_chan_object_dtor(काष्ठा nvkm_fअगरo_chan *, पूर्णांक);

पूर्णांक g84_fअगरo_chan_ctor(काष्ठा nv50_fअगरo *, u64 vmm, u64 push,
		       स्थिर काष्ठा nvkm_oclass *, काष्ठा nv50_fअगरo_chan *);

बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass nv50_fअगरo_dma_oclass;
बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass nv50_fअगरo_gpfअगरo_oclass;
बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass g84_fअगरo_dma_oclass;
बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass g84_fअगरo_gpfअगरo_oclass;
#पूर्ण_अगर
