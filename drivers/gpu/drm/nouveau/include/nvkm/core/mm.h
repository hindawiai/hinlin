<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_MM_H__
#घोषणा __NVKM_MM_H__
#समावेश <core/os.h>

काष्ठा nvkm_mm_node अणु
	काष्ठा list_head nl_entry;
	काष्ठा list_head fl_entry;
	काष्ठा nvkm_mm_node *next;

#घोषणा NVKM_MM_HEAP_ANY 0x00
	u8  heap;
#घोषणा NVKM_MM_TYPE_NONE 0x00
#घोषणा NVKM_MM_TYPE_HOLE 0xff
	u8  type;
	u32 offset;
	u32 length;
पूर्ण;

काष्ठा nvkm_mm अणु
	काष्ठा list_head nodes;
	काष्ठा list_head मुक्त;

	u32 block_size;
	पूर्णांक heap_nodes;
पूर्ण;

अटल अंतरभूत bool
nvkm_mm_initialised(काष्ठा nvkm_mm *mm)
अणु
	वापस mm->heap_nodes;
पूर्ण

पूर्णांक  nvkm_mm_init(काष्ठा nvkm_mm *, u8 heap, u32 offset, u32 length, u32 block);
पूर्णांक  nvkm_mm_fini(काष्ठा nvkm_mm *);
पूर्णांक  nvkm_mm_head(काष्ठा nvkm_mm *, u8 heap, u8 type, u32 size_max,
		  u32 size_min, u32 align, काष्ठा nvkm_mm_node **);
पूर्णांक  nvkm_mm_tail(काष्ठा nvkm_mm *, u8 heap, u8 type, u32 size_max,
		  u32 size_min, u32 align, काष्ठा nvkm_mm_node **);
व्योम nvkm_mm_मुक्त(काष्ठा nvkm_mm *, काष्ठा nvkm_mm_node **);
व्योम nvkm_mm_dump(काष्ठा nvkm_mm *, स्थिर अक्षर *);

अटल अंतरभूत u32
nvkm_mm_heap_size(काष्ठा nvkm_mm *mm, u8 heap)
अणु
	काष्ठा nvkm_mm_node *node;
	u32 size = 0;
	list_क्रम_each_entry(node, &mm->nodes, nl_entry) अणु
		अगर (node->heap == heap)
			size += node->length;
	पूर्ण
	वापस size;
पूर्ण

अटल अंतरभूत bool
nvkm_mm_contiguous(काष्ठा nvkm_mm_node *node)
अणु
	वापस !node->next;
पूर्ण

अटल अंतरभूत u32
nvkm_mm_addr(काष्ठा nvkm_mm_node *node)
अणु
	अगर (WARN_ON(!nvkm_mm_contiguous(node)))
		वापस 0;
	वापस node->offset;
पूर्ण

अटल अंतरभूत u32
nvkm_mm_size(काष्ठा nvkm_mm_node *node)
अणु
	u32 size = 0;
	करो अणु
		size += node->length;
	पूर्ण जबतक ((node = node->next));
	वापस size;
पूर्ण
#पूर्ण_अगर
