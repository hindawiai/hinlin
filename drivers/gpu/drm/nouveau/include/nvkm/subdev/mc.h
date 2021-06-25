<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_MC_H__
#घोषणा __NVKM_MC_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_mc अणु
	स्थिर काष्ठा nvkm_mc_func *func;
	काष्ठा nvkm_subdev subdev;
पूर्ण;

व्योम nvkm_mc_enable(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
व्योम nvkm_mc_disable(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
bool nvkm_mc_enabled(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
व्योम nvkm_mc_reset(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक);
व्योम nvkm_mc_पूर्णांकr(काष्ठा nvkm_device *, bool *handled);
व्योम nvkm_mc_पूर्णांकr_unarm(काष्ठा nvkm_device *);
व्योम nvkm_mc_पूर्णांकr_rearm(काष्ठा nvkm_device *);
व्योम nvkm_mc_पूर्णांकr_mask(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, bool enable);
व्योम nvkm_mc_unk260(काष्ठा nvkm_device *, u32 data);

पूर्णांक nv04_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक nv11_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक nv17_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक nv44_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक nv50_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक g84_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक g98_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक gt215_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक gf100_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक gk104_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक gk20a_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक gp100_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक gp10b_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक tu102_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
पूर्णांक ga100_mc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_mc **);
#पूर्ण_अगर
