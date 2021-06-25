<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV04_DEVINIT_H__
#घोषणा __NV04_DEVINIT_H__
#घोषणा nv04_devinit(p) container_of((p), काष्ठा nv04_devinit, base)
#समावेश "priv.h"
काष्ठा nvkm_pll_vals;

काष्ठा nv04_devinit अणु
	काष्ठा nvkm_devinit base;
	पूर्णांक owner;
पूर्ण;

पूर्णांक nv04_devinit_new_(स्थिर काष्ठा nvkm_devinit_func *, काष्ठा nvkm_device *,
		      क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_devinit **);
व्योम *nv04_devinit_dtor(काष्ठा nvkm_devinit *);
व्योम nv04_devinit_preinit(काष्ठा nvkm_devinit *);
व्योम nv04_devinit_fini(काष्ठा nvkm_devinit *);
पूर्णांक  nv04_devinit_pll_set(काष्ठा nvkm_devinit *, u32, u32);

व्योम setPLL_single(काष्ठा nvkm_devinit *, u32, काष्ठा nvkm_pll_vals *);
व्योम setPLL_द्विगुन_highregs(काष्ठा nvkm_devinit *, u32, काष्ठा nvkm_pll_vals *);
व्योम setPLL_द्विगुन_lowregs(काष्ठा nvkm_devinit *, u32, काष्ठा nvkm_pll_vals *);
#पूर्ण_अगर
