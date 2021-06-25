<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_GR_H__
#घोषणा __NV50_GR_H__
#घोषणा nv50_gr(p) container_of((p), काष्ठा nv50_gr, base)
#समावेश "priv.h"

काष्ठा nv50_gr अणु
	काष्ठा nvkm_gr base;
	स्थिर काष्ठा nv50_gr_func *func;
	spinlock_t lock;
	u32 size;
पूर्ण;

पूर्णांक nv50_gr_new_(स्थिर काष्ठा nvkm_gr_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_gr **);
पूर्णांक nv50_gr_init(काष्ठा nvkm_gr *);
व्योम nv50_gr_पूर्णांकr(काष्ठा nvkm_gr *);
u64 nv50_gr_units(काष्ठा nvkm_gr *);

पूर्णांक g84_gr_tlb_flush(काष्ठा nvkm_gr *);

#घोषणा nv50_gr_chan(p) container_of((p), काष्ठा nv50_gr_chan, object)
#समावेश <core/object.h>

काष्ठा nv50_gr_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv50_gr *gr;
पूर्ण;

पूर्णांक nv50_gr_chan_new(काष्ठा nvkm_gr *, काष्ठा nvkm_fअगरo_chan *,
		     स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object **);

बाह्य स्थिर काष्ठा nvkm_object_func nv50_gr_object;

पूर्णांक  nv50_grctx_init(काष्ठा nvkm_device *, u32 *size);
व्योम nv50_grctx_fill(काष्ठा nvkm_device *, काष्ठा nvkm_gpuobj *);
#पूर्ण_अगर
