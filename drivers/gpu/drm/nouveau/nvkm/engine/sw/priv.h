<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_SW_PRIV_H__
#घोषणा __NVKM_SW_PRIV_H__
#घोषणा nvkm_sw(p) container_of((p), काष्ठा nvkm_sw, engine)
#समावेश <engine/sw.h>
काष्ठा nvkm_sw_chan;

पूर्णांक nvkm_sw_new_(स्थिर काष्ठा nvkm_sw_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_sw **);

काष्ठा nvkm_sw_chan_sclass अणु
	पूर्णांक (*ctor)(काष्ठा nvkm_sw_chan *, स्थिर काष्ठा nvkm_oclass *,
		    व्योम *data, u32 size, काष्ठा nvkm_object **);
	काष्ठा nvkm_sclass base;
पूर्ण;

काष्ठा nvkm_sw_func अणु
	पूर्णांक (*chan_new)(काष्ठा nvkm_sw *, काष्ठा nvkm_fअगरo_chan *,
			स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object **);
	स्थिर काष्ठा nvkm_sw_chan_sclass sclass[];
पूर्ण;
#पूर्ण_अगर
