<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_INSTMEM_H__
#घोषणा __NVKM_INSTMEM_H__
#समावेश <core/subdev.h>
काष्ठा nvkm_memory;

काष्ठा nvkm_insपंचांगem अणु
	स्थिर काष्ठा nvkm_insपंचांगem_func *func;
	काष्ठा nvkm_subdev subdev;

	spinlock_t lock;
	काष्ठा list_head list;
	काष्ठा list_head boot;
	u32 reserved;

	/* <=nv4x: protects NV_PRAMIN/BAR2 MM
	 * >=nv50: protects BAR2 MM & LRU
	 */
	काष्ठा mutex mutex;

	काष्ठा nvkm_memory *vbios;
	काष्ठा nvkm_ramht  *ramht;
	काष्ठा nvkm_memory *ramro;
	काष्ठा nvkm_memory *ramfc;
पूर्ण;

u32 nvkm_insपंचांगem_rd32(काष्ठा nvkm_insपंचांगem *, u32 addr);
व्योम nvkm_insपंचांगem_wr32(काष्ठा nvkm_insपंचांगem *, u32 addr, u32 data);
पूर्णांक nvkm_instobj_new(काष्ठा nvkm_insपंचांगem *, u32 size, u32 align, bool zero,
		     काष्ठा nvkm_memory **);


पूर्णांक nv04_insपंचांगem_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_insपंचांगem **);
पूर्णांक nv40_insपंचांगem_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_insपंचांगem **);
पूर्णांक nv50_insपंचांगem_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_insपंचांगem **);
पूर्णांक gk20a_insपंचांगem_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_insपंचांगem **);
#पूर्ण_अगर
