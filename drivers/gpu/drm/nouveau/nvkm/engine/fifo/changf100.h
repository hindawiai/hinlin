<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __GF100_FIFO_CHAN_H__
#घोषणा __GF100_FIFO_CHAN_H__
#घोषणा gf100_fअगरo_chan(p) container_of((p), काष्ठा gf100_fअगरo_chan, base)
#समावेश "chan.h"
#समावेश "gf100.h"

काष्ठा gf100_fअगरo_chan अणु
	काष्ठा nvkm_fअगरo_chan base;
	काष्ठा gf100_fअगरo *fअगरo;

	काष्ठा list_head head;
	bool समाप्तed;

#घोषणा GF100_FIFO_ENGN_GR     0
#घोषणा GF100_FIFO_ENGN_MSPDEC 1
#घोषणा GF100_FIFO_ENGN_MSPPP  2
#घोषणा GF100_FIFO_ENGN_MSVLD  3
#घोषणा GF100_FIFO_ENGN_CE0    4
#घोषणा GF100_FIFO_ENGN_CE1    5
#घोषणा GF100_FIFO_ENGN_SW     15
	काष्ठा gf100_fअगरo_engn अणु
		काष्ठा nvkm_gpuobj *inst;
		काष्ठा nvkm_vma *vma;
	पूर्ण engn[NVKM_FIFO_ENGN_NR];
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_fअगरo_chan_oclass gf100_fअगरo_gpfअगरo_oclass;
#पूर्ण_अगर
