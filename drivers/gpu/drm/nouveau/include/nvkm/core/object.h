<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_OBJECT_H__
#घोषणा __NVKM_OBJECT_H__
#समावेश <core/oclass.h>
काष्ठा nvkm_event;
काष्ठा nvkm_gpuobj;

काष्ठा nvkm_object अणु
	स्थिर काष्ठा nvkm_object_func *func;
	काष्ठा nvkm_client *client;
	काष्ठा nvkm_engine *engine;
	s32 oclass;
	u32 handle;

	काष्ठा list_head head;
	काष्ठा list_head tree;
	u8  route;
	u64 token;
	u64 object;
	काष्ठा rb_node node;
पूर्ण;

क्रमागत nvkm_object_map अणु
	NVKM_OBJECT_MAP_IO,
	NVKM_OBJECT_MAP_VA
पूर्ण;

काष्ठा nvkm_object_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_object *);
	पूर्णांक (*init)(काष्ठा nvkm_object *);
	पूर्णांक (*fini)(काष्ठा nvkm_object *, bool suspend);
	पूर्णांक (*mthd)(काष्ठा nvkm_object *, u32 mthd, व्योम *data, u32 size);
	पूर्णांक (*ntfy)(काष्ठा nvkm_object *, u32 mthd, काष्ठा nvkm_event **);
	पूर्णांक (*map)(काष्ठा nvkm_object *, व्योम *argv, u32 argc,
		   क्रमागत nvkm_object_map *, u64 *addr, u64 *size);
	पूर्णांक (*unmap)(काष्ठा nvkm_object *);
	पूर्णांक (*rd08)(काष्ठा nvkm_object *, u64 addr, u8 *data);
	पूर्णांक (*rd16)(काष्ठा nvkm_object *, u64 addr, u16 *data);
	पूर्णांक (*rd32)(काष्ठा nvkm_object *, u64 addr, u32 *data);
	पूर्णांक (*wr08)(काष्ठा nvkm_object *, u64 addr, u8 data);
	पूर्णांक (*wr16)(काष्ठा nvkm_object *, u64 addr, u16 data);
	पूर्णांक (*wr32)(काष्ठा nvkm_object *, u64 addr, u32 data);
	पूर्णांक (*bind)(काष्ठा nvkm_object *, काष्ठा nvkm_gpuobj *, पूर्णांक align,
		    काष्ठा nvkm_gpuobj **);
	पूर्णांक (*sclass)(काष्ठा nvkm_object *, पूर्णांक index, काष्ठा nvkm_oclass *);
पूर्ण;

व्योम nvkm_object_ctor(स्थिर काष्ठा nvkm_object_func *,
		      स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object *);
पूर्णांक nvkm_object_new_(स्थिर काष्ठा nvkm_object_func *,
		     स्थिर काष्ठा nvkm_oclass *, व्योम *data, u32 size,
		     काष्ठा nvkm_object **);
पूर्णांक nvkm_object_new(स्थिर काष्ठा nvkm_oclass *, व्योम *data, u32 size,
		    काष्ठा nvkm_object **);
व्योम nvkm_object_del(काष्ठा nvkm_object **);
व्योम *nvkm_object_dtor(काष्ठा nvkm_object *);
पूर्णांक nvkm_object_init(काष्ठा nvkm_object *);
पूर्णांक nvkm_object_fini(काष्ठा nvkm_object *, bool suspend);
पूर्णांक nvkm_object_mthd(काष्ठा nvkm_object *, u32 mthd, व्योम *data, u32 size);
पूर्णांक nvkm_object_ntfy(काष्ठा nvkm_object *, u32 mthd, काष्ठा nvkm_event **);
पूर्णांक nvkm_object_map(काष्ठा nvkm_object *, व्योम *argv, u32 argc,
		    क्रमागत nvkm_object_map *, u64 *addr, u64 *size);
पूर्णांक nvkm_object_unmap(काष्ठा nvkm_object *);
पूर्णांक nvkm_object_rd08(काष्ठा nvkm_object *, u64 addr, u8  *data);
पूर्णांक nvkm_object_rd16(काष्ठा nvkm_object *, u64 addr, u16 *data);
पूर्णांक nvkm_object_rd32(काष्ठा nvkm_object *, u64 addr, u32 *data);
पूर्णांक nvkm_object_wr08(काष्ठा nvkm_object *, u64 addr, u8   data);
पूर्णांक nvkm_object_wr16(काष्ठा nvkm_object *, u64 addr, u16  data);
पूर्णांक nvkm_object_wr32(काष्ठा nvkm_object *, u64 addr, u32  data);
पूर्णांक nvkm_object_bind(काष्ठा nvkm_object *, काष्ठा nvkm_gpuobj *, पूर्णांक align,
		     काष्ठा nvkm_gpuobj **);

bool nvkm_object_insert(काष्ठा nvkm_object *);
व्योम nvkm_object_हटाओ(काष्ठा nvkm_object *);
काष्ठा nvkm_object *nvkm_object_search(काष्ठा nvkm_client *, u64 object,
				       स्थिर काष्ठा nvkm_object_func *);
#पूर्ण_अगर
