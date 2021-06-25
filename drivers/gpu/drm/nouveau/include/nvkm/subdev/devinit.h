<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DEVINIT_H__
#घोषणा __NVKM_DEVINIT_H__
#समावेश <core/subdev.h>
काष्ठा nvkm_devinit;

काष्ठा nvkm_devinit अणु
	स्थिर काष्ठा nvkm_devinit_func *func;
	काष्ठा nvkm_subdev subdev;
	bool post;
	bool क्रमce_post;
पूर्ण;

u32 nvkm_devinit_mmio(काष्ठा nvkm_devinit *, u32 addr);
पूर्णांक nvkm_devinit_pll_set(काष्ठा nvkm_devinit *, u32 type, u32 khz);
व्योम nvkm_devinit_meminit(काष्ठा nvkm_devinit *);
पूर्णांक nvkm_devinit_post(काष्ठा nvkm_devinit *);

पूर्णांक nv04_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक nv05_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक nv10_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक nv1a_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक nv20_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक nv50_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक g84_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक g98_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक gt215_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक mcp89_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक gf100_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक gm107_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक gm200_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक gv100_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक tu102_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
पूर्णांक ga100_devinit_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
#पूर्ण_अगर
