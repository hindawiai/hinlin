<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_H__
#घोषणा __NVKM_DISP_H__
#घोषणा nvkm_disp(p) container_of((p), काष्ठा nvkm_disp, engine)
#समावेश <core/engine.h>
#समावेश <core/event.h>

काष्ठा nvkm_disp अणु
	स्थिर काष्ठा nvkm_disp_func *func;
	काष्ठा nvkm_engine engine;

	काष्ठा list_head head;
	काष्ठा list_head ior;
	काष्ठा list_head outp;
	काष्ठा list_head conn;

	काष्ठा nvkm_event hpd;
	काष्ठा nvkm_event vblank;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा nvkm_oproxy *object;
	पूर्ण client;
पूर्ण;

पूर्णांक nv04_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक nv50_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक g84_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gt200_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक g94_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक mcp77_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gt215_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक mcp89_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gf119_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gk104_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gk110_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gm107_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gm200_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gp100_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gp102_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक gv100_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक tu102_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
पूर्णांक ga102_disp_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_disp **);
#पूर्ण_अगर
