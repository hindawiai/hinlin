<शैली गुरु>
#अगर_अघोषित __NVKM_UMEM_H__
#घोषणा __NVKM_UMEM_H__
#घोषणा nvkm_umem(p) container_of((p), काष्ठा nvkm_umem, object)
#समावेश <core/object.h>
#समावेश "mem.h"

काष्ठा nvkm_umem अणु
	काष्ठा nvkm_object object;
	काष्ठा nvkm_mmu *mmu;
	u8 type:8;
	bool priv:1;
	bool mappable:1;
	bool io:1;

	काष्ठा nvkm_memory *memory;
	काष्ठा list_head head;

	जोड़ अणु
		काष्ठा nvkm_vma *bar;
		व्योम *map;
	पूर्ण;
पूर्ण;

पूर्णांक nvkm_umem_new(स्थिर काष्ठा nvkm_oclass *, व्योम *argv, u32 argc,
		  काष्ठा nvkm_object **);
#पूर्ण_अगर
