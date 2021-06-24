<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_MMU_PRIV_H__
#घोषणा __NVKM_MMU_PRIV_H__
#घोषणा nvkm_mmu(p) container_of((p), काष्ठा nvkm_mmu, subdev)
#समावेश <subdev/mmu.h>

व्योम nvkm_mmu_ctor(स्थिर काष्ठा nvkm_mmu_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_mmu *);
पूर्णांक nvkm_mmu_new_(स्थिर काष्ठा nvkm_mmu_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_mmu **);

काष्ठा nvkm_mmu_func अणु
	व्योम (*init)(काष्ठा nvkm_mmu *);

	u8  dma_bits;

	काष्ठा अणु
		काष्ठा nvkm_sclass user;
	पूर्ण mmu;

	काष्ठा अणु
		काष्ठा nvkm_sclass user;
		पूर्णांक (*vram)(काष्ठा nvkm_mmu *, पूर्णांक type, u8 page, u64 size,
			    व्योम *argv, u32 argc, काष्ठा nvkm_memory **);
		पूर्णांक (*umap)(काष्ठा nvkm_mmu *, काष्ठा nvkm_memory *, व्योम *argv,
			    u32 argc, u64 *addr, u64 *size, काष्ठा nvkm_vma **);
	पूर्ण mem;

	काष्ठा अणु
		काष्ठा nvkm_sclass user;
		पूर्णांक (*ctor)(काष्ठा nvkm_mmu *, bool managed, u64 addr, u64 size,
			    व्योम *argv, u32 argc, काष्ठा lock_class_key *,
			    स्थिर अक्षर *name, काष्ठा nvkm_vmm **);
		bool global;
		u32 pd_offset;
	पूर्ण vmm;

	स्थिर u8 *(*kind)(काष्ठा nvkm_mmu *, पूर्णांक *count, u8 *invalid);
	bool kind_sys;
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_mmu_func nv04_mmu;

स्थिर u8 *nv50_mmu_kind(काष्ठा nvkm_mmu *, पूर्णांक *count, u8 *invalid);

स्थिर u8 *gf100_mmu_kind(काष्ठा nvkm_mmu *, पूर्णांक *count, u8 *invalid);

स्थिर u8 *gm200_mmu_kind(काष्ठा nvkm_mmu *, पूर्णांक *, u8 *);

काष्ठा nvkm_mmu_pt अणु
	जोड़ अणु
		काष्ठा nvkm_mmu_ptc *ptc;
		काष्ठा nvkm_mmu_ptp *ptp;
	पूर्ण;
	काष्ठा nvkm_memory *memory;
	bool sub;
	u16 base;
	u64 addr;
	काष्ठा list_head head;
पूर्ण;

व्योम nvkm_mmu_ptc_dump(काष्ठा nvkm_mmu *);
काष्ठा nvkm_mmu_pt *
nvkm_mmu_ptc_get(काष्ठा nvkm_mmu *, u32 size, u32 align, bool zero);
व्योम nvkm_mmu_ptc_put(काष्ठा nvkm_mmu *, bool क्रमce, काष्ठा nvkm_mmu_pt **);
#पूर्ण_अगर
