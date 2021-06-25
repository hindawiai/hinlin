<शैली गुरु>
#अगर_अघोषित __NVIF_MMU_H__
#घोषणा __NVIF_MMU_H__
#समावेश <nvअगर/object.h>

काष्ठा nvअगर_mmu अणु
	काष्ठा nvअगर_object object;
	u8  dmabits;
	u8  heap_nr;
	u8  type_nr;
	u8  kind_inv;
	u16 kind_nr;
	s32 mem;

	काष्ठा अणु
		u64 size;
	पूर्ण *heap;

	काष्ठा अणु
#घोषणा NVIF_MEM_VRAM                                                      0x01
#घोषणा NVIF_MEM_HOST                                                      0x02
#घोषणा NVIF_MEM_COMP                                                      0x04
#घोषणा NVIF_MEM_DISP                                                      0x08
#घोषणा NVIF_MEM_KIND                                                      0x10
#घोषणा NVIF_MEM_MAPPABLE                                                  0x20
#घोषणा NVIF_MEM_COHERENT                                                  0x40
#घोषणा NVIF_MEM_UNCACHED                                                  0x80
		u8 type;
		u8 heap;
	पूर्ण *type;

	u8 *kind;
पूर्ण;

पूर्णांक nvअगर_mmu_ctor(काष्ठा nvअगर_object *, स्थिर अक्षर *name, s32 oclass,
		  काष्ठा nvअगर_mmu *);
व्योम nvअगर_mmu_dtor(काष्ठा nvअगर_mmu *);

अटल अंतरभूत bool
nvअगर_mmu_kind_valid(काष्ठा nvअगर_mmu *mmu, u8 kind)
अणु
	अगर (kind) अणु
		अगर (kind >= mmu->kind_nr || mmu->kind[kind] == mmu->kind_inv)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक
nvअगर_mmu_type(काष्ठा nvअगर_mmu *mmu, u8 mask)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < mmu->type_nr; i++) अणु
		अगर ((mmu->type[i].type & mask) == mask)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर
