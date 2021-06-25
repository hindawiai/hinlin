<शैली गुरु>
#अगर_अघोषित __NVKM_MEM_H__
#घोषणा __NVKM_MEM_H__
#समावेश "priv.h"

पूर्णांक nvkm_mem_new_type(काष्ठा nvkm_mmu *, पूर्णांक type, u8 page, u64 size,
		      व्योम *argv, u32 argc, काष्ठा nvkm_memory **);
पूर्णांक nvkm_mem_map_host(काष्ठा nvkm_memory *, व्योम **pmap);

पूर्णांक nv04_mem_new(काष्ठा nvkm_mmu *, पूर्णांक, u8, u64, व्योम *, u32,
		 काष्ठा nvkm_memory **);
पूर्णांक nv04_mem_map(काष्ठा nvkm_mmu *, काष्ठा nvkm_memory *, व्योम *, u32,
		 u64 *, u64 *, काष्ठा nvkm_vma **);

पूर्णांक nv50_mem_new(काष्ठा nvkm_mmu *, पूर्णांक, u8, u64, व्योम *, u32,
		 काष्ठा nvkm_memory **);
पूर्णांक nv50_mem_map(काष्ठा nvkm_mmu *, काष्ठा nvkm_memory *, व्योम *, u32,
		 u64 *, u64 *, काष्ठा nvkm_vma **);

पूर्णांक gf100_mem_new(काष्ठा nvkm_mmu *, पूर्णांक, u8, u64, व्योम *, u32,
		  काष्ठा nvkm_memory **);
पूर्णांक gf100_mem_map(काष्ठा nvkm_mmu *, काष्ठा nvkm_memory *, व्योम *, u32,
		  u64 *, u64 *, काष्ठा nvkm_vma **);
#पूर्ण_अगर
