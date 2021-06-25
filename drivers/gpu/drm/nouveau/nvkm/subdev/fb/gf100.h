<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_RAM_NVC0_H__
#घोषणा __NVKM_RAM_NVC0_H__
#घोषणा gf100_fb(p) container_of((p), काष्ठा gf100_fb, base)
#समावेश "priv.h"

काष्ठा gf100_fb अणु
	काष्ठा nvkm_fb base;
	काष्ठा page *r100c10_page;
	dma_addr_t r100c10;
पूर्ण;

पूर्णांक gf100_fb_new_(स्थिर काष्ठा nvkm_fb_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_fb **);
व्योम *gf100_fb_dtor(काष्ठा nvkm_fb *);
व्योम gf100_fb_init(काष्ठा nvkm_fb *);
व्योम gf100_fb_पूर्णांकr(काष्ठा nvkm_fb *);

व्योम gp100_fb_init(काष्ठा nvkm_fb *);

व्योम gm200_fb_init(काष्ठा nvkm_fb *base);
#पूर्ण_अगर
