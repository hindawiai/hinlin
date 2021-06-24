<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_GPUOBJ_H__
#घोषणा __NVKM_GPUOBJ_H__
#समावेश <core/memory.h>
#समावेश <core/mm.h>

#घोषणा NVOBJ_FLAG_ZERO_ALLOC 0x00000001
#घोषणा NVOBJ_FLAG_HEAP       0x00000004

काष्ठा nvkm_gpuobj अणु
	जोड़ अणु
		स्थिर काष्ठा nvkm_gpuobj_func *func;
		स्थिर काष्ठा nvkm_gpuobj_func *ptrs;
	पूर्ण;
	काष्ठा nvkm_gpuobj *parent;
	काष्ठा nvkm_memory *memory;
	काष्ठा nvkm_mm_node *node;

	u64 addr;
	u32 size;
	काष्ठा nvkm_mm heap;

	व्योम __iomem *map;
पूर्ण;

काष्ठा nvkm_gpuobj_func अणु
	व्योम *(*acquire)(काष्ठा nvkm_gpuobj *);
	व्योम (*release)(काष्ठा nvkm_gpuobj *);
	u32 (*rd32)(काष्ठा nvkm_gpuobj *, u32 offset);
	व्योम (*wr32)(काष्ठा nvkm_gpuobj *, u32 offset, u32 data);
	पूर्णांक (*map)(काष्ठा nvkm_gpuobj *, u64 offset, काष्ठा nvkm_vmm *,
		   काष्ठा nvkm_vma *, व्योम *argv, u32 argc);
पूर्ण;

पूर्णांक nvkm_gpuobj_new(काष्ठा nvkm_device *, u32 size, पूर्णांक align, bool zero,
		    काष्ठा nvkm_gpuobj *parent, काष्ठा nvkm_gpuobj **);
व्योम nvkm_gpuobj_del(काष्ठा nvkm_gpuobj **);
पूर्णांक nvkm_gpuobj_wrap(काष्ठा nvkm_memory *, काष्ठा nvkm_gpuobj **);
व्योम nvkm_gpuobj_स_नकल_to(काष्ठा nvkm_gpuobj *dst, u32 dstoffset, व्योम *src,
			   u32 length);
व्योम nvkm_gpuobj_स_नकल_from(व्योम *dst, काष्ठा nvkm_gpuobj *src, u32 srcoffset,
			     u32 length);
#पूर्ण_अगर
