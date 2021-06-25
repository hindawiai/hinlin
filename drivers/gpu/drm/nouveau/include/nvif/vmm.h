<शैली गुरु>
#अगर_अघोषित __NVIF_VMM_H__
#घोषणा __NVIF_VMM_H__
#समावेश <nvअगर/object.h>
काष्ठा nvअगर_mem;
काष्ठा nvअगर_mmu;

क्रमागत nvअगर_vmm_get अणु
	ADDR,
	PTES,
	LAZY
पूर्ण;

काष्ठा nvअगर_vma अणु
	u64 addr;
	u64 size;
पूर्ण;

काष्ठा nvअगर_vmm अणु
	काष्ठा nvअगर_object object;
	u64 start;
	u64 limit;

	काष्ठा अणु
		u8 shअगरt;
		bool sparse:1;
		bool vram:1;
		bool host:1;
		bool comp:1;
	पूर्ण *page;
	पूर्णांक page_nr;
पूर्ण;

पूर्णांक nvअगर_vmm_ctor(काष्ठा nvअगर_mmu *, स्थिर अक्षर *name, s32 oclass, bool managed,
		  u64 addr, u64 size, व्योम *argv, u32 argc, काष्ठा nvअगर_vmm *);
व्योम nvअगर_vmm_dtor(काष्ठा nvअगर_vmm *);
पूर्णांक nvअगर_vmm_get(काष्ठा nvअगर_vmm *, क्रमागत nvअगर_vmm_get, bool sparse,
		 u8 page, u8 align, u64 size, काष्ठा nvअगर_vma *);
व्योम nvअगर_vmm_put(काष्ठा nvअगर_vmm *, काष्ठा nvअगर_vma *);
पूर्णांक nvअगर_vmm_map(काष्ठा nvअगर_vmm *, u64 addr, u64 size, व्योम *argv, u32 argc,
		 काष्ठा nvअगर_mem *, u64 offset);
पूर्णांक nvअगर_vmm_unmap(काष्ठा nvअगर_vmm *, u64);
#पूर्ण_अगर
