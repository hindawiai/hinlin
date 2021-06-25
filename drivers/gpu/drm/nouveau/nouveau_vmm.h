<शैली गुरु>
#अगर_अघोषित __NOUVEAU_VMA_H__
#घोषणा __NOUVEAU_VMA_H__
#समावेश <nvअगर/vmm.h>
काष्ठा nouveau_bo;
काष्ठा nouveau_mem;

काष्ठा nouveau_vma अणु
	काष्ठा nouveau_vmm *vmm;
	पूर्णांक refs;
	काष्ठा list_head head;
	u64 addr;

	काष्ठा nouveau_mem *mem;

	काष्ठा nouveau_fence *fence;
पूर्ण;

काष्ठा nouveau_vma *nouveau_vma_find(काष्ठा nouveau_bo *, काष्ठा nouveau_vmm *);
पूर्णांक nouveau_vma_new(काष्ठा nouveau_bo *, काष्ठा nouveau_vmm *,
		    काष्ठा nouveau_vma **);
व्योम nouveau_vma_del(काष्ठा nouveau_vma **);
पूर्णांक nouveau_vma_map(काष्ठा nouveau_vma *, काष्ठा nouveau_mem *);
व्योम nouveau_vma_unmap(काष्ठा nouveau_vma *);

काष्ठा nouveau_vmm अणु
	काष्ठा nouveau_cli *cli;
	काष्ठा nvअगर_vmm vmm;
	काष्ठा nouveau_svmm *svmm;
पूर्ण;

पूर्णांक nouveau_vmm_init(काष्ठा nouveau_cli *, s32 oclass, काष्ठा nouveau_vmm *);
व्योम nouveau_vmm_fini(काष्ठा nouveau_vmm *);
#पूर्ण_अगर
