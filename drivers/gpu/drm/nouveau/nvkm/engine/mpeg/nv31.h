<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV31_MPEG_H__
#घोषणा __NV31_MPEG_H__
#घोषणा nv31_mpeg(p) container_of((p), काष्ठा nv31_mpeg, engine)
#समावेश "priv.h"
#समावेश <engine/mpeg.h>

काष्ठा nv31_mpeg अणु
	स्थिर काष्ठा nv31_mpeg_func *func;
	काष्ठा nvkm_engine engine;
	काष्ठा nv31_mpeg_chan *chan;
पूर्ण;

पूर्णांक nv31_mpeg_new_(स्थिर काष्ठा nv31_mpeg_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_engine **);

काष्ठा nv31_mpeg_func अणु
	bool (*mthd_dma)(काष्ठा nvkm_device *, u32 mthd, u32 data);
पूर्ण;

#घोषणा nv31_mpeg_chan(p) container_of((p), काष्ठा nv31_mpeg_chan, object)
#समावेश <core/object.h>

काष्ठा nv31_mpeg_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv31_mpeg *mpeg;
	काष्ठा nvkm_fअगरo_chan *fअगरo;
पूर्ण;

पूर्णांक nv31_mpeg_chan_new(काष्ठा nvkm_fअगरo_chan *, स्थिर काष्ठा nvkm_oclass *,
		       काष्ठा nvkm_object **);
#पूर्ण_अगर
