<शैली गुरु>
#अगर_अघोषित __NVIF_MEM_H__
#घोषणा __NVIF_MEM_H__
#समावेश "mmu.h"

काष्ठा nvअगर_mem अणु
	काष्ठा nvअगर_object object;
	u8  type;
	u8  page;
	u64 addr;
	u64 size;
पूर्ण;

पूर्णांक nvअगर_mem_ctor_type(काष्ठा nvअगर_mmu *mmu, स्थिर अक्षर *name, s32 oclass,
		       पूर्णांक type, u8 page, u64 size, व्योम *argv, u32 argc,
		       काष्ठा nvअगर_mem *);
पूर्णांक nvअगर_mem_ctor(काष्ठा nvअगर_mmu *mmu, स्थिर अक्षर *name, s32 oclass, u8 type,
		  u8 page, u64 size, व्योम *argv, u32 argc, काष्ठा nvअगर_mem *);
व्योम nvअगर_mem_dtor(काष्ठा nvअगर_mem *);

पूर्णांक nvअगर_mem_ctor_map(काष्ठा nvअगर_mmu *, स्थिर अक्षर *name, u8 type, u64 size,
		      काष्ठा nvअगर_mem *);
#पूर्ण_अगर
