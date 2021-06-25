<शैली गुरु>
#अगर_अघोषित __NOUVEAU_MEM_H__
#घोषणा __NOUVEAU_MEM_H__
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
काष्ठा tपंचांग_tt;

#समावेश <nvअगर/स्मृति.स>
#समावेश <nvअगर/vmm.h>

अटल अंतरभूत काष्ठा nouveau_mem *
nouveau_mem(काष्ठा tपंचांग_resource *reg)
अणु
	वापस reg->mm_node;
पूर्ण

काष्ठा nouveau_mem अणु
	काष्ठा nouveau_cli *cli;
	u8 kind;
	u8 comp;
	काष्ठा nvअगर_mem mem;
	काष्ठा nvअगर_vma vma[2];
पूर्ण;

पूर्णांक nouveau_mem_new(काष्ठा nouveau_cli *, u8 kind, u8 comp,
		    काष्ठा tपंचांग_resource *);
व्योम nouveau_mem_del(काष्ठा tपंचांग_resource *);
पूर्णांक nouveau_mem_vram(काष्ठा tपंचांग_resource *, bool contig, u8 page);
पूर्णांक nouveau_mem_host(काष्ठा tपंचांग_resource *, काष्ठा tपंचांग_tt *);
व्योम nouveau_mem_fini(काष्ठा nouveau_mem *);
पूर्णांक nouveau_mem_map(काष्ठा nouveau_mem *, काष्ठा nvअगर_vmm *, काष्ठा nvअगर_vma *);
#पूर्ण_अगर
