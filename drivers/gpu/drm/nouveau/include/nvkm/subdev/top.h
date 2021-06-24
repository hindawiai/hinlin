<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_TOP_H__
#घोषणा __NVKM_TOP_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_top अणु
	स्थिर काष्ठा nvkm_top_func *func;
	काष्ठा nvkm_subdev subdev;
	काष्ठा list_head device;
पूर्ण;

काष्ठा nvkm_top_device अणु
	क्रमागत nvkm_subdev_type type;
	पूर्णांक inst;
	u32 addr;
	पूर्णांक fault;
	पूर्णांक engine;
	पूर्णांक runlist;
	पूर्णांक reset;
	पूर्णांक पूर्णांकr;
	काष्ठा list_head head;
पूर्ण;

u32 nvkm_top_addr(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
u32 nvkm_top_reset(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
u32 nvkm_top_पूर्णांकr_mask(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
पूर्णांक nvkm_top_fault_id(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
काष्ठा nvkm_subdev *nvkm_top_fault(काष्ठा nvkm_device *, पूर्णांक fault);

पूर्णांक gk104_top_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_top **);
पूर्णांक ga100_top_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_top **);
#पूर्ण_अगर
