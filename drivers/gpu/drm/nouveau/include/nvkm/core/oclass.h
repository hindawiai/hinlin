<शैली गुरु>
#अगर_अघोषित __NVKM_OCLASS_H__
#घोषणा __NVKM_OCLASS_H__
#समावेश <core/os.h>
#समावेश <core/debug.h>
काष्ठा nvkm_oclass;
काष्ठा nvkm_object;

काष्ठा nvkm_sclass अणु
	पूर्णांक minver;
	पूर्णांक maxver;
	s32 oclass;
	स्थिर काष्ठा nvkm_object_func *func;
	पूर्णांक (*ctor)(स्थिर काष्ठा nvkm_oclass *, व्योम *data, u32 size,
		    काष्ठा nvkm_object **);
पूर्ण;

काष्ठा nvkm_oclass अणु
	पूर्णांक (*ctor)(स्थिर काष्ठा nvkm_oclass *, व्योम *data, u32 size,
		    काष्ठा nvkm_object **);
	काष्ठा nvkm_sclass base;
	स्थिर व्योम *priv;
	स्थिर व्योम *engn;
	u32 handle;
	u8  route;
	u64 token;
	u64 object;
	काष्ठा nvkm_client *client;
	काष्ठा nvkm_object *parent;
	काष्ठा nvkm_engine *engine;
पूर्ण;
#पूर्ण_अगर
