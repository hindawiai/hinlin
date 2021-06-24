<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_DRIVER_H__
#घोषणा __NVIF_DRIVER_H__
#समावेश <nvअगर/os.h>
काष्ठा nvअगर_client;

काष्ठा nvअगर_driver अणु
	स्थिर अक्षर *name;
	पूर्णांक (*init)(स्थिर अक्षर *name, u64 device, स्थिर अक्षर *cfg,
		    स्थिर अक्षर *dbg, व्योम **priv);
	व्योम (*fini)(व्योम *priv);
	पूर्णांक (*suspend)(व्योम *priv);
	पूर्णांक (*resume)(व्योम *priv);
	पूर्णांक (*ioctl)(व्योम *priv, bool super, व्योम *data, u32 size, व्योम **hack);
	व्योम __iomem *(*map)(व्योम *priv, u64 handle, u32 size);
	व्योम (*unmap)(व्योम *priv, व्योम __iomem *ptr, u32 size);
	bool keep;
पूर्ण;

पूर्णांक nvअगर_driver_init(स्थिर अक्षर *drv, स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		     स्थिर अक्षर *name, u64 device, काष्ठा nvअगर_client *);

बाह्य स्थिर काष्ठा nvअगर_driver nvअगर_driver_nvkm;
बाह्य स्थिर काष्ठा nvअगर_driver nvअगर_driver_drm;
बाह्य स्थिर काष्ठा nvअगर_driver nvअगर_driver_lib;
बाह्य स्थिर काष्ठा nvअगर_driver nvअगर_driver_null;
#पूर्ण_अगर
