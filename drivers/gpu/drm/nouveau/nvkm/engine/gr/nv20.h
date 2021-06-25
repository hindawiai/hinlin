<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV20_GR_H__
#घोषणा __NV20_GR_H__
#घोषणा nv20_gr(p) container_of((p), काष्ठा nv20_gr, base)
#समावेश "priv.h"

काष्ठा nv20_gr अणु
	काष्ठा nvkm_gr base;
	काष्ठा nvkm_memory *ctxtab;
पूर्ण;

पूर्णांक nv20_gr_new_(स्थिर काष्ठा nvkm_gr_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_gr **);
व्योम *nv20_gr_dtor(काष्ठा nvkm_gr *);
पूर्णांक nv20_gr_oneinit(काष्ठा nvkm_gr *);
पूर्णांक nv20_gr_init(काष्ठा nvkm_gr *);
व्योम nv20_gr_पूर्णांकr(काष्ठा nvkm_gr *);
व्योम nv20_gr_tile(काष्ठा nvkm_gr *, पूर्णांक, काष्ठा nvkm_fb_tile *);

पूर्णांक nv30_gr_init(काष्ठा nvkm_gr *);

#घोषणा nv20_gr_chan(p) container_of((p), काष्ठा nv20_gr_chan, object)
#समावेश <core/object.h>

काष्ठा nv20_gr_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv20_gr *gr;
	पूर्णांक chid;
	काष्ठा nvkm_memory *inst;
पूर्ण;

व्योम *nv20_gr_chan_dtor(काष्ठा nvkm_object *);
पूर्णांक nv20_gr_chan_init(काष्ठा nvkm_object *);
पूर्णांक nv20_gr_chan_fini(काष्ठा nvkm_object *, bool);
#पूर्ण_अगर
