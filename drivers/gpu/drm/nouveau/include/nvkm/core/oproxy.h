<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_OPROXY_H__
#घोषणा __NVKM_OPROXY_H__
#घोषणा nvkm_oproxy(p) container_of((p), काष्ठा nvkm_oproxy, base)
#समावेश <core/object.h>

काष्ठा nvkm_oproxy अणु
	स्थिर काष्ठा nvkm_oproxy_func *func;
	काष्ठा nvkm_object base;
	काष्ठा nvkm_object *object;
पूर्ण;

काष्ठा nvkm_oproxy_func अणु
	व्योम (*dtor[2])(काष्ठा nvkm_oproxy *);
	पूर्णांक  (*init[2])(काष्ठा nvkm_oproxy *);
	पूर्णांक  (*fini[2])(काष्ठा nvkm_oproxy *, bool suspend);
पूर्ण;

व्योम nvkm_oproxy_ctor(स्थिर काष्ठा nvkm_oproxy_func *,
		      स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_oproxy *);
पूर्णांक  nvkm_oproxy_new_(स्थिर काष्ठा nvkm_oproxy_func *,
		      स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_oproxy **);
#पूर्ण_अगर
