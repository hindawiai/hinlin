<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_DISP_ROOT_H__
#घोषणा __NV50_DISP_ROOT_H__
#घोषणा nv50_disp_root(p) container_of((p), काष्ठा nv50_disp_root, object)
#समावेश <core/object.h>
#समावेश "nv50.h"

काष्ठा nv50_disp_root अणु
	स्थिर काष्ठा nv50_disp_root_func *func;
	काष्ठा nv50_disp *disp;
	काष्ठा nvkm_object object;
पूर्ण;

काष्ठा nv50_disp_root_func अणु
	पूर्णांक blah;
	काष्ठा nv50_disp_user अणु
		काष्ठा nvkm_sclass base;
		पूर्णांक (*ctor)(स्थिर काष्ठा nvkm_oclass *, व्योम *argv, u32 argc,
			    काष्ठा nv50_disp *, काष्ठा nvkm_object **);
	पूर्ण user[];
पूर्ण;

पूर्णांक  nv50_disp_root_new_(स्थिर काष्ठा nv50_disp_root_func *, काष्ठा nvkm_disp *,
			 स्थिर काष्ठा nvkm_oclass *, व्योम *data, u32 size,
			 काष्ठा nvkm_object **);

पूर्णांक gv100_disp_caps_new(स्थिर काष्ठा nvkm_oclass *, व्योम *, u32,
			काष्ठा nv50_disp *, काष्ठा nvkm_object **);

बाह्य स्थिर काष्ठा nvkm_disp_oclass nv50_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass g84_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass g94_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gt200_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gt215_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gf119_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gk104_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gk110_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gm107_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gm200_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gp100_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gp102_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass gv100_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass tu102_disp_root_oclass;
बाह्य स्थिर काष्ठा nvkm_disp_oclass ga102_disp_root_oclass;
#पूर्ण_अगर
