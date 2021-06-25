<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DEVINIT_PRIV_H__
#घोषणा __NVKM_DEVINIT_PRIV_H__
#घोषणा nvkm_devinit(p) container_of((p), काष्ठा nvkm_devinit, subdev)
#समावेश <subdev/devinit.h>

काष्ठा nvkm_devinit_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_devinit *);
	व्योम (*preinit)(काष्ठा nvkm_devinit *);
	व्योम (*init)(काष्ठा nvkm_devinit *);
	पूर्णांक  (*post)(काष्ठा nvkm_devinit *, bool post);
	u32  (*mmio)(काष्ठा nvkm_devinit *, u32);
	व्योम (*meminit)(काष्ठा nvkm_devinit *);
	पूर्णांक  (*pll_set)(काष्ठा nvkm_devinit *, u32 type, u32 freq);
	u64  (*disable)(काष्ठा nvkm_devinit *);
पूर्ण;

व्योम nvkm_devinit_ctor(स्थिर काष्ठा nvkm_devinit_func *, काष्ठा nvkm_device *,
		       क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_devinit *);
u64 nvkm_devinit_disable(काष्ठा nvkm_devinit *);

पूर्णांक nv04_devinit_post(काष्ठा nvkm_devinit *, bool);
पूर्णांक tu102_devinit_post(काष्ठा nvkm_devinit *, bool);
#पूर्ण_अगर
