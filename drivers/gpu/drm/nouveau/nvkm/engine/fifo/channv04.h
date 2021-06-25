<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV04_FIFO_CHAN_H__
#घोषणा __NV04_FIFO_CHAN_H__
#घोषणा nv04_fअगरo_chan(p) container_of((p), काष्ठा nv04_fअगरo_chan, base)
#समावेश "chan.h"
#समावेश "nv04.h"

काष्ठा nv04_fअगरo_chan अणु
	काष्ठा nvkm_fअगरo_chan base;
	काष्ठा nv04_fअगरo *fअगरo;
	u32 ramfc;
#घोषणा NV04_FIFO_ENGN_SW   0
#घोषणा NV04_FIFO_ENGN_GR   1
#घोषणा NV04_FIFO_ENGN_MPEG 2
#घोषणा NV04_FIFO_ENGN_DMA  3
	काष्ठा nvkm_gpuobj *engn[NVKM_FIFO_ENGN_NR];
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_func nv04_fअगरo_dma_func;
व्योम *nv04_fअगरo_dma_dtor(काष्ठा nvkm_fअगरo_chan *);
व्योम nv04_fअगरo_dma_init(काष्ठा nvkm_fअगरo_chan *);
व्योम nv04_fअगरo_dma_fini(काष्ठा nvkm_fअगरo_chan *);
व्योम nv04_fअगरo_dma_object_dtor(काष्ठा nvkm_fअगरo_chan *, पूर्णांक);

बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass nv04_fअगरo_dma_oclass;
बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass nv10_fअगरo_dma_oclass;
बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass nv17_fअगरo_dma_oclass;
बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass nv40_fअगरo_dma_oclass;
#पूर्ण_अगर
