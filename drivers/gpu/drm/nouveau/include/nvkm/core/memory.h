<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_MEMORY_H__
#घोषणा __NVKM_MEMORY_H__
#समावेश <core/os.h>
काष्ठा nvkm_device;
काष्ठा nvkm_vma;
काष्ठा nvkm_vmm;

काष्ठा nvkm_tags अणु
	काष्ठा nvkm_mm_node *mn;
	refcount_t refcount;
पूर्ण;

क्रमागत nvkm_memory_target अणु
	NVKM_MEM_TARGET_INST, /* instance memory */
	NVKM_MEM_TARGET_VRAM, /* video memory */
	NVKM_MEM_TARGET_HOST, /* coherent प्रणाली memory */
	NVKM_MEM_TARGET_NCOH, /* non-coherent प्रणाली memory */
पूर्ण;

काष्ठा nvkm_memory अणु
	स्थिर काष्ठा nvkm_memory_func *func;
	स्थिर काष्ठा nvkm_memory_ptrs *ptrs;
	काष्ठा kref kref;
	काष्ठा nvkm_tags *tags;
पूर्ण;

काष्ठा nvkm_memory_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_memory *);
	क्रमागत nvkm_memory_target (*target)(काष्ठा nvkm_memory *);
	u8 (*page)(काष्ठा nvkm_memory *);
	u64 (*bar2)(काष्ठा nvkm_memory *);
	u64 (*addr)(काष्ठा nvkm_memory *);
	u64 (*size)(काष्ठा nvkm_memory *);
	व्योम (*boot)(काष्ठा nvkm_memory *, काष्ठा nvkm_vmm *);
	व्योम __iomem *(*acquire)(काष्ठा nvkm_memory *);
	व्योम (*release)(काष्ठा nvkm_memory *);
	पूर्णांक (*map)(काष्ठा nvkm_memory *, u64 offset, काष्ठा nvkm_vmm *,
		   काष्ठा nvkm_vma *, व्योम *argv, u32 argc);
पूर्ण;

काष्ठा nvkm_memory_ptrs अणु
	u32 (*rd32)(काष्ठा nvkm_memory *, u64 offset);
	व्योम (*wr32)(काष्ठा nvkm_memory *, u64 offset, u32 data);
पूर्ण;

व्योम nvkm_memory_ctor(स्थिर काष्ठा nvkm_memory_func *, काष्ठा nvkm_memory *);
पूर्णांक nvkm_memory_new(काष्ठा nvkm_device *, क्रमागत nvkm_memory_target,
		    u64 size, u32 align, bool zero, काष्ठा nvkm_memory **);
काष्ठा nvkm_memory *nvkm_memory_ref(काष्ठा nvkm_memory *);
व्योम nvkm_memory_unref(काष्ठा nvkm_memory **);
पूर्णांक nvkm_memory_tags_get(काष्ठा nvkm_memory *, काष्ठा nvkm_device *, u32 tags,
			 व्योम (*clear)(काष्ठा nvkm_device *, u32, u32),
			 काष्ठा nvkm_tags **);
व्योम nvkm_memory_tags_put(काष्ठा nvkm_memory *, काष्ठा nvkm_device *,
			  काष्ठा nvkm_tags **);

#घोषणा nvkm_memory_target(p) (p)->func->target(p)
#घोषणा nvkm_memory_page(p) (p)->func->page(p)
#घोषणा nvkm_memory_bar2(p) (p)->func->bar2(p)
#घोषणा nvkm_memory_addr(p) (p)->func->addr(p)
#घोषणा nvkm_memory_size(p) (p)->func->size(p)
#घोषणा nvkm_memory_boot(p,v) (p)->func->boot((p),(v))
#घोषणा nvkm_memory_map(p,o,vm,va,av,ac)                                       \
	(p)->func->map((p),(o),(vm),(va),(av),(ac))

/* accessor macros - kmap()/करोne() must bracket use of the other accessor
 * macros to guarantee correct behaviour across all chipsets
 */
#घोषणा nvkm_kmap(o)     (o)->func->acquire(o)
#घोषणा nvkm_करोne(o)     (o)->func->release(o)

#घोषणा nvkm_ro32(o,a)   (o)->ptrs->rd32((o), (a))
#घोषणा nvkm_wo32(o,a,d) (o)->ptrs->wr32((o), (a), (d))
#घोषणा nvkm_mo32(o,a,m,d) (अणु                                                  \
	u32 _addr = (a), _data = nvkm_ro32((o), _addr);                        \
	nvkm_wo32((o), _addr, (_data & ~(m)) | (d));                           \
	_data;                                                                 \
पूर्ण)

#घोषणा nvkm_wo64(o,a,d) करो अणु                                                  \
	u64 __a = (a), __d = (d);                                              \
	nvkm_wo32((o), __a + 0, lower_32_bits(__d));                           \
	nvkm_wo32((o), __a + 4, upper_32_bits(__d));                           \
पूर्ण जबतक(0)

#घोषणा nvkm_robj(o,a,p,s) करो अणु                                                \
	u32 _addr = (a), _size = (s) >> 2, *_data = (व्योम *)(p);               \
	जबतक (_size--) अणु                                                      \
		*(_data++) = nvkm_ro32((o), _addr);                            \
		_addr += 4;                                                    \
	पूर्ण                                                                      \
पूर्ण जबतक(0)

#घोषणा nvkm_wobj(o,a,p,s) करो अणु                                                \
	u32 _addr = (a), _size = (s) >> 2, *_data = (व्योम *)(p);               \
	जबतक (_size--) अणु                                                      \
		nvkm_wo32((o), _addr, *(_data++));                             \
		_addr += 4;                                                    \
	पूर्ण                                                                      \
पूर्ण जबतक(0)

#घोषणा nvkm_fill(t,s,o,a,d,c) करो अणु                                            \
	u64 _a = (a), _c = (c), _d = (d), _o = _a >> s, _s = _c << s;          \
	u##t __iomem *_m = nvkm_kmap(o);                                       \
	अगर (likely(_m)) अणु                                                      \
		अगर (_d) अणु                                                      \
			जबतक (_c--)                                           \
				ioग_लिखो##t##_native(_d, &_m[_o++]);            \
		पूर्ण अन्यथा अणु                                                       \
			स_रखो_io(&_m[_o], _d, _s);                            \
		पूर्ण                                                              \
	पूर्ण अन्यथा अणु                                                               \
		क्रम (; _c; _c--, _a += BIT(s))                                 \
			nvkm_wo##t((o), _a, _d);                               \
	पूर्ण                                                                      \
	nvkm_करोne(o);                                                          \
पूर्ण जबतक(0)
#घोषणा nvkm_fo32(o,a,d,c) nvkm_fill(32, 2, (o), (a), (d), (c))
#घोषणा nvkm_fo64(o,a,d,c) nvkm_fill(64, 3, (o), (a), (d), (c))
#पूर्ण_अगर
