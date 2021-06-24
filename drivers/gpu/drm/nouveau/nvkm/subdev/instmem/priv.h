<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_INSTMEM_PRIV_H__
#घोषणा __NVKM_INSTMEM_PRIV_H__
#घोषणा nvkm_insपंचांगem(p) container_of((p), काष्ठा nvkm_insपंचांगem, subdev)
#समावेश <subdev/insपंचांगem.h>

काष्ठा nvkm_insपंचांगem_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_insपंचांगem *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_insपंचांगem *);
	व्योम (*fini)(काष्ठा nvkm_insपंचांगem *);
	u32  (*rd32)(काष्ठा nvkm_insपंचांगem *, u32 addr);
	व्योम (*wr32)(काष्ठा nvkm_insपंचांगem *, u32 addr, u32 data);
	पूर्णांक (*memory_new)(काष्ठा nvkm_insपंचांगem *, u32 size, u32 align,
			  bool zero, काष्ठा nvkm_memory **);
	bool zero;
पूर्ण;

व्योम nvkm_insपंचांगem_ctor(स्थिर काष्ठा nvkm_insपंचांगem_func *, काष्ठा nvkm_device *,
		       क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_insपंचांगem *);
व्योम nvkm_insपंचांगem_boot(काष्ठा nvkm_insपंचांगem *);

#समावेश <core/memory.h>

काष्ठा nvkm_instobj अणु
	काष्ठा nvkm_memory memory;
	काष्ठा list_head head;
	u32 *suspend;
पूर्ण;

व्योम nvkm_instobj_ctor(स्थिर काष्ठा nvkm_memory_func *func,
		       काष्ठा nvkm_insपंचांगem *, काष्ठा nvkm_instobj *);
व्योम nvkm_instobj_dtor(काष्ठा nvkm_insपंचांगem *, काष्ठा nvkm_instobj *);
#पूर्ण_अगर
