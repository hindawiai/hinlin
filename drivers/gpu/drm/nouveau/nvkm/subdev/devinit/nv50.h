<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_DEVINIT_H__
#घोषणा __NV50_DEVINIT_H__
#घोषणा nv50_devinit(p) container_of((p), काष्ठा nv50_devinit, base)
#समावेश "priv.h"

काष्ठा nv50_devinit अणु
	काष्ठा nvkm_devinit base;
	u32 r001540;
पूर्ण;

पूर्णांक nv50_devinit_new_(स्थिर काष्ठा nvkm_devinit_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		      पूर्णांक, काष्ठा nvkm_devinit **);
व्योम nv50_devinit_preinit(काष्ठा nvkm_devinit *);
व्योम nv50_devinit_init(काष्ठा nvkm_devinit *);
पूर्णांक  nv50_devinit_pll_set(काष्ठा nvkm_devinit *, u32, u32);

पूर्णांक  gt215_devinit_pll_set(काष्ठा nvkm_devinit *, u32, u32);

पूर्णांक  gf100_devinit_ctor(काष्ठा nvkm_object *, काष्ठा nvkm_object *,
			काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nvkm_object **);
पूर्णांक  gf100_devinit_pll_set(काष्ठा nvkm_devinit *, u32, u32);
व्योम gf100_devinit_preinit(काष्ठा nvkm_devinit *);

u64  gm107_devinit_disable(काष्ठा nvkm_devinit *);

पूर्णांक gm200_devinit_post(काष्ठा nvkm_devinit *, bool);
व्योम gm200_devinit_preos(काष्ठा nv50_devinit *, bool);
#पूर्ण_अगर
