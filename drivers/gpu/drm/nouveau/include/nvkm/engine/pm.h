<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PM_H__
#घोषणा __NVKM_PM_H__
#समावेश <core/engine.h>

काष्ठा nvkm_pm अणु
	स्थिर काष्ठा nvkm_pm_func *func;
	काष्ठा nvkm_engine engine;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा nvkm_object *object;
	पूर्ण client;

	काष्ठा list_head करोमुख्यs;
	काष्ठा list_head sources;
	u32 sequence;
पूर्ण;

पूर्णांक nv40_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक nv50_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक g84_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक gt200_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक gt215_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक gf100_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक gf108_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक gf117_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
पूर्णांक gk104_pm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_pm **);
#पूर्ण_अगर
