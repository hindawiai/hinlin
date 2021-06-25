<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_PRIV_H__
#घोषणा __NVKM_DISP_PRIV_H__
#समावेश <engine/disp.h>
#समावेश "outp.h"

पूर्णांक nvkm_disp_ctor(स्थिर काष्ठा nvkm_disp_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_disp *);
पूर्णांक nvkm_disp_new_(स्थिर काष्ठा nvkm_disp_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_disp **);
व्योम nvkm_disp_vblank(काष्ठा nvkm_disp *, पूर्णांक head);

काष्ठा nvkm_disp_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_disp *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_disp *);
	पूर्णांक (*init)(काष्ठा nvkm_disp *);
	व्योम (*fini)(काष्ठा nvkm_disp *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_disp *);

	स्थिर काष्ठा nvkm_disp_oclass *(*root)(काष्ठा nvkm_disp *);
पूर्ण;

पूर्णांक  nvkm_disp_ntfy(काष्ठा nvkm_object *, u32, काष्ठा nvkm_event **);

बाह्य स्थिर काष्ठा nvkm_disp_oclass nv04_disp_root_oclass;

काष्ठा nvkm_disp_oclass अणु
	पूर्णांक (*ctor)(काष्ठा nvkm_disp *, स्थिर काष्ठा nvkm_oclass *,
		    व्योम *data, u32 size, काष्ठा nvkm_object **);
	काष्ठा nvkm_sclass base;
पूर्ण;
#पूर्ण_अगर
