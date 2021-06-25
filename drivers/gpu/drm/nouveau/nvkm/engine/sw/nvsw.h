<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_NVSW_H__
#घोषणा __NVKM_NVSW_H__
#घोषणा nvkm_nvsw(p) container_of((p), काष्ठा nvkm_nvsw, object)
#समावेश <core/object.h>

काष्ठा nvkm_nvsw अणु
	काष्ठा nvkm_object object;
	स्थिर काष्ठा nvkm_nvsw_func *func;
	काष्ठा nvkm_sw_chan *chan;
पूर्ण;

काष्ठा nvkm_nvsw_func अणु
	पूर्णांक (*mthd)(काष्ठा nvkm_nvsw *, u32 mthd, व्योम *data, u32 size);
पूर्ण;

पूर्णांक nvkm_nvsw_new_(स्थिर काष्ठा nvkm_nvsw_func *, काष्ठा nvkm_sw_chan *,
		   स्थिर काष्ठा nvkm_oclass *, व्योम *data, u32 size,
		   काष्ठा nvkm_object **pobject);
पूर्णांक nvkm_nvsw_new(काष्ठा nvkm_sw_chan *, स्थिर काष्ठा nvkm_oclass *,
		  व्योम *data, u32 size, काष्ठा nvkm_object **pobject);
#पूर्ण_अगर
