<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_SEC2_H__
#घोषणा __NVKM_SEC2_H__
#घोषणा nvkm_sec2(p) container_of((p), काष्ठा nvkm_sec2, engine)
#समावेश <core/engine.h>
#समावेश <core/falcon.h>

काष्ठा nvkm_sec2 अणु
	स्थिर काष्ठा nvkm_sec2_func *func;
	काष्ठा nvkm_engine engine;
	काष्ठा nvkm_falcon falcon;

	काष्ठा nvkm_falcon_qmgr *qmgr;
	काष्ठा nvkm_falcon_cmdq *cmdq;
	काष्ठा nvkm_falcon_msgq *msgq;

	काष्ठा work_काष्ठा work;
	bool iniपंचांगsg_received;
पूर्ण;

पूर्णांक gp102_sec2_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sec2 **);
पूर्णांक gp108_sec2_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sec2 **);
पूर्णांक tu102_sec2_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_sec2 **);
#पूर्ण_अगर
