<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FB_NV50_H__
#घोषणा __NVKM_FB_NV50_H__
#घोषणा nv50_fb(p) container_of((p), काष्ठा nv50_fb, base)
#समावेश "priv.h"

काष्ठा nv50_fb अणु
	स्थिर काष्ठा nv50_fb_func *func;
	काष्ठा nvkm_fb base;
	काष्ठा page *r100c08_page;
	dma_addr_t r100c08;
पूर्ण;

काष्ठा nv50_fb_func अणु
	पूर्णांक (*ram_new)(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
	u32 (*tags)(काष्ठा nvkm_fb *);
	u32 trap;
पूर्ण;

पूर्णांक nv50_fb_new_(स्थिर काष्ठा nv50_fb_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_fb **pfb);
#पूर्ण_अगर
