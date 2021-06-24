<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_ENGINE_H__
#घोषणा __NVKM_ENGINE_H__
#घोषणा nvkm_engine(p) container_of((p), काष्ठा nvkm_engine, subdev)
#समावेश <core/subdev.h>
काष्ठा nvkm_fअगरo_chan;
काष्ठा nvkm_fb_tile;

बाह्य स्थिर काष्ठा nvkm_subdev_func nvkm_engine;

काष्ठा nvkm_engine अणु
	स्थिर काष्ठा nvkm_engine_func *func;
	काष्ठा nvkm_subdev subdev;
	spinlock_t lock;

	काष्ठा अणु
		refcount_t refcount;
		काष्ठा mutex mutex;
		bool enabled;
	पूर्ण use;
पूर्ण;

काष्ठा nvkm_engine_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_engine *);
	व्योम (*preinit)(काष्ठा nvkm_engine *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_engine *);
	पूर्णांक (*info)(काष्ठा nvkm_engine *, u64 mthd, u64 *data);
	पूर्णांक (*init)(काष्ठा nvkm_engine *);
	पूर्णांक (*fini)(काष्ठा nvkm_engine *, bool suspend);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_engine *);
	व्योम (*tile)(काष्ठा nvkm_engine *, पूर्णांक region, काष्ठा nvkm_fb_tile *);
	bool (*chsw_load)(काष्ठा nvkm_engine *);

	काष्ठा अणु
		पूर्णांक (*sclass)(काष्ठा nvkm_oclass *, पूर्णांक index,
			      स्थिर काष्ठा nvkm_device_oclass **);
	पूर्ण base;

	काष्ठा अणु
		पूर्णांक (*cclass)(काष्ठा nvkm_fअगरo_chan *,
			      स्थिर काष्ठा nvkm_oclass *,
			      काष्ठा nvkm_object **);
		पूर्णांक (*sclass)(काष्ठा nvkm_oclass *, पूर्णांक index);
	पूर्ण fअगरo;

	स्थिर काष्ठा nvkm_object_func *cclass;
	काष्ठा nvkm_sclass sclass[];
पूर्ण;

पूर्णांक nvkm_engine_ctor(स्थिर काष्ठा nvkm_engine_func *, काष्ठा nvkm_device *,
		     क्रमागत nvkm_subdev_type, पूर्णांक inst, bool enable, काष्ठा nvkm_engine *);
पूर्णांक nvkm_engine_new_(स्थिर काष्ठा nvkm_engine_func *, काष्ठा nvkm_device *,
		     क्रमागत nvkm_subdev_type, पूर्णांक, bool enable, काष्ठा nvkm_engine **);

काष्ठा nvkm_engine *nvkm_engine_ref(काष्ठा nvkm_engine *);
व्योम nvkm_engine_unref(काष्ठा nvkm_engine **);
व्योम nvkm_engine_tile(काष्ठा nvkm_engine *, पूर्णांक region);
bool nvkm_engine_chsw_load(काष्ठा nvkm_engine *);
#पूर्ण_अगर
