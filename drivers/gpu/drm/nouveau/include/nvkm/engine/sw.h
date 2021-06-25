<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_SW_H__
#घोषणा __NVKM_SW_H__
#समावेश <core/engine.h>

काष्ठा nvkm_sw अणु
	स्थिर काष्ठा nvkm_sw_func *func;
	काष्ठा nvkm_engine engine;

	काष्ठा list_head chan;
पूर्ण;

bool nvkm_sw_mthd(काष्ठा nvkm_sw *sw, पूर्णांक chid, पूर्णांक subc, u32 mthd, u32 data);

पूर्णांक nv04_sw_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sw **);
पूर्णांक nv10_sw_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sw **);
पूर्णांक nv50_sw_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sw **);
पूर्णांक gf100_sw_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sw **);
#पूर्ण_अगर
