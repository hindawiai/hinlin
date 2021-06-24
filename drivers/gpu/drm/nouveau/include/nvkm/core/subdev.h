<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_SUBDEV_H__
#घोषणा __NVKM_SUBDEV_H__
#समावेश <core/device.h>

क्रमागत nvkm_subdev_type अणु
#घोषणा NVKM_LAYOUT_ONCE(t,s,p,...) t,
#घोषणा NVKM_LAYOUT_INST NVKM_LAYOUT_ONCE
#समावेश <core/layout.h>
#अघोषित NVKM_LAYOUT_INST
#अघोषित NVKM_LAYOUT_ONCE
	NVKM_SUBDEV_NR
पूर्ण;

काष्ठा nvkm_subdev अणु
	स्थिर काष्ठा nvkm_subdev_func *func;
	काष्ठा nvkm_device *device;
	क्रमागत nvkm_subdev_type type;
	पूर्णांक inst;
	अक्षर name[16];
	u32 debug;
	काष्ठा list_head head;

	व्योम **pself;
	bool oneinit;
पूर्ण;

काष्ठा nvkm_subdev_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_subdev *);
	पूर्णांक (*preinit)(काष्ठा nvkm_subdev *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_subdev *);
	पूर्णांक (*info)(काष्ठा nvkm_subdev *, u64 mthd, u64 *data);
	पूर्णांक (*init)(काष्ठा nvkm_subdev *);
	पूर्णांक (*fini)(काष्ठा nvkm_subdev *, bool suspend);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_subdev *);
पूर्ण;

बाह्य स्थिर अक्षर *nvkm_subdev_type[NVKM_SUBDEV_NR];
पूर्णांक nvkm_subdev_new_(स्थिर काष्ठा nvkm_subdev_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		     पूर्णांक inst, काष्ठा nvkm_subdev **);
व्योम nvkm_subdev_ctor(स्थिर काष्ठा nvkm_subdev_func *, काष्ठा nvkm_device *,
		      क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_subdev *);
व्योम nvkm_subdev_disable(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst);
व्योम nvkm_subdev_del(काष्ठा nvkm_subdev **);
पूर्णांक  nvkm_subdev_preinit(काष्ठा nvkm_subdev *);
पूर्णांक  nvkm_subdev_init(काष्ठा nvkm_subdev *);
पूर्णांक  nvkm_subdev_fini(काष्ठा nvkm_subdev *, bool suspend);
पूर्णांक  nvkm_subdev_info(काष्ठा nvkm_subdev *, u64, u64 *);
व्योम nvkm_subdev_पूर्णांकr(काष्ठा nvkm_subdev *);

/* subdev logging */
#घोषणा nvkm_prपूर्णांकk_(s,l,p,f,a...) करो अणु                                        \
	स्थिर काष्ठा nvkm_subdev *_subdev = (s);                               \
	अगर (CONFIG_NOUVEAU_DEBUG >= (l) && _subdev->debug >= (l))              \
		dev_##p(_subdev->device->dev, "%s: "f, _subdev->name, ##a);    \
पूर्ण जबतक(0)
#घोषणा nvkm_prपूर्णांकk(s,l,p,f,a...) nvkm_prपूर्णांकk_((s), NV_DBG_##l, p, f, ##a)
#घोषणा nvkm_fatal(s,f,a...) nvkm_prपूर्णांकk((s), FATAL,   crit, f, ##a)
#घोषणा nvkm_error(s,f,a...) nvkm_prपूर्णांकk((s), ERROR,    err, f, ##a)
#घोषणा nvkm_warn(s,f,a...)  nvkm_prपूर्णांकk((s),  WARN, notice, f, ##a)
#घोषणा nvkm_info(s,f,a...)  nvkm_prपूर्णांकk((s),  INFO,   info, f, ##a)
#घोषणा nvkm_debug(s,f,a...) nvkm_prपूर्णांकk((s), DEBUG,   info, f, ##a)
#घोषणा nvkm_trace(s,f,a...) nvkm_prपूर्णांकk((s), TRACE,   info, f, ##a)
#घोषणा nvkm_spam(s,f,a...)  nvkm_prपूर्णांकk((s),  SPAM,    dbg, f, ##a)
#पूर्ण_अगर
