<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_CLIENT_H__
#घोषणा __NVKM_CLIENT_H__
#घोषणा nvkm_client(p) container_of((p), काष्ठा nvkm_client, object)
#समावेश <core/object.h>

काष्ठा nvkm_client अणु
	काष्ठा nvkm_object object;
	अक्षर name[32];
	u64 device;
	u32 debug;

	काष्ठा nvkm_client_notअगरy *notअगरy[32];
	काष्ठा rb_root objroot;

	bool super;
	व्योम *data;
	पूर्णांक (*ntfy)(स्थिर व्योम *, u32, स्थिर व्योम *, u32);

	काष्ठा list_head umem;
	spinlock_t lock;
पूर्ण;

पूर्णांक  nvkm_client_new(स्थिर अक्षर *name, u64 device, स्थिर अक्षर *cfg,
		     स्थिर अक्षर *dbg,
		     पूर्णांक (*)(स्थिर व्योम *, u32, स्थिर व्योम *, u32),
		     काष्ठा nvkm_client **);
काष्ठा nvkm_client *nvkm_client_search(काष्ठा nvkm_client *, u64 handle);

पूर्णांक nvkm_client_notअगरy_new(काष्ठा nvkm_object *, काष्ठा nvkm_event *,
			   व्योम *data, u32 size);
पूर्णांक nvkm_client_notअगरy_del(काष्ठा nvkm_client *, पूर्णांक index);
पूर्णांक nvkm_client_notअगरy_get(काष्ठा nvkm_client *, पूर्णांक index);
पूर्णांक nvkm_client_notअगरy_put(काष्ठा nvkm_client *, पूर्णांक index);

/* logging क्रम client-facing objects */
#घोषणा nvअगर_prपूर्णांकk(o,l,p,f,a...) करो अणु                                         \
	स्थिर काष्ठा nvkm_object *_object = (o);                               \
	स्थिर काष्ठा nvkm_client *_client = _object->client;                   \
	अगर (_client->debug >= NV_DBG_##l)                                      \
		prपूर्णांकk(KERN_##p "nouveau: %s:%08x:%08x: "f, _client->name,     \
		       _object->handle, _object->oclass, ##a);                 \
पूर्ण जबतक(0)
#घोषणा nvअगर_fatal(o,f,a...) nvअगर_prपूर्णांकk((o), FATAL, CRIT, f, ##a)
#घोषणा nvअगर_error(o,f,a...) nvअगर_prपूर्णांकk((o), ERROR,  ERR, f, ##a)
#घोषणा nvअगर_debug(o,f,a...) nvअगर_prपूर्णांकk((o), DEBUG, INFO, f, ##a)
#घोषणा nvअगर_trace(o,f,a...) nvअगर_prपूर्णांकk((o), TRACE, INFO, f, ##a)
#घोषणा nvअगर_info(o,f,a...)  nvअगर_prपूर्णांकk((o),  INFO, INFO, f, ##a)
#घोषणा nvअगर_ioctl(o,f,a...) nvअगर_trace((o), "ioctl: "f, ##a)
#पूर्ण_अगर
