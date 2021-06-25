<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DEVICE_H__
#घोषणा __NVKM_DEVICE_H__
#समावेश <core/oclass.h>
#समावेश <core/event.h>
क्रमागत nvkm_subdev_type;

क्रमागत nvkm_device_type अणु
	NVKM_DEVICE_PCI,
	NVKM_DEVICE_AGP,
	NVKM_DEVICE_PCIE,
	NVKM_DEVICE_TEGRA,
पूर्ण;

काष्ठा nvkm_device अणु
	स्थिर काष्ठा nvkm_device_func *func;
	स्थिर काष्ठा nvkm_device_quirk *quirk;
	काष्ठा device *dev;
	क्रमागत nvkm_device_type type;
	u64 handle;
	स्थिर अक्षर *name;
	स्थिर अक्षर *cfgopt;
	स्थिर अक्षर *dbgopt;

	काष्ठा list_head head;
	काष्ठा mutex mutex;
	पूर्णांक refcount;

	व्योम __iomem *pri;

	काष्ठा nvkm_event event;

	u32 debug;

	स्थिर काष्ठा nvkm_device_chip *chip;
	क्रमागत अणु
		NV_04    = 0x04,
		NV_10    = 0x10,
		NV_11    = 0x11,
		NV_20    = 0x20,
		NV_30    = 0x30,
		NV_40    = 0x40,
		NV_50    = 0x50,
		NV_C0    = 0xc0,
		NV_E0    = 0xe0,
		GM100    = 0x110,
		GP100    = 0x130,
		GV100    = 0x140,
		TU100    = 0x160,
		GA100    = 0x170,
	पूर्ण card_type;
	u32 chipset;
	u8  chiprev;
	u32 crystal;

	काष्ठा अणु
		काष्ठा notअगरier_block nb;
	पूर्ण acpi;

#घोषणा NVKM_LAYOUT_ONCE(type,data,ptr) data *ptr;
#घोषणा NVKM_LAYOUT_INST(type,data,ptr,cnt) data *ptr[cnt];
#समावेश <core/layout.h>
#अघोषित NVKM_LAYOUT_INST
#अघोषित NVKM_LAYOUT_ONCE
	काष्ठा list_head subdev;
पूर्ण;

काष्ठा nvkm_subdev *nvkm_device_subdev(काष्ठा nvkm_device *, पूर्णांक type, पूर्णांक inst);
काष्ठा nvkm_engine *nvkm_device_engine(काष्ठा nvkm_device *, पूर्णांक type, पूर्णांक inst);

काष्ठा nvkm_device_func अणु
	काष्ठा nvkm_device_pci *(*pci)(काष्ठा nvkm_device *);
	काष्ठा nvkm_device_tegra *(*tegra)(काष्ठा nvkm_device *);
	व्योम *(*dtor)(काष्ठा nvkm_device *);
	पूर्णांक (*preinit)(काष्ठा nvkm_device *);
	पूर्णांक (*init)(काष्ठा nvkm_device *);
	व्योम (*fini)(काष्ठा nvkm_device *, bool suspend);
	resource_माप_प्रकार (*resource_addr)(काष्ठा nvkm_device *, अचिन्हित bar);
	resource_माप_प्रकार (*resource_size)(काष्ठा nvkm_device *, अचिन्हित bar);
	bool cpu_coherent;
पूर्ण;

काष्ठा nvkm_device_quirk अणु
	u8 tv_pin_mask;
	u8 tv_gpio;
पूर्ण;

काष्ठा nvkm_device_chip अणु
	स्थिर अक्षर *name;
#घोषणा NVKM_LAYOUT_ONCE(type,data,ptr,...)                                                  \
	काष्ठा अणु                                                                             \
		u32 inst;                                                                    \
		पूर्णांक (*ctor)(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, data **); \
	पूर्ण ptr;
#घोषणा NVKM_LAYOUT_INST(A...) NVKM_LAYOUT_ONCE(A)
#समावेश <core/layout.h>
#अघोषित NVKM_LAYOUT_INST
#अघोषित NVKM_LAYOUT_ONCE
पूर्ण;

काष्ठा nvkm_device *nvkm_device_find(u64 name);
पूर्णांक nvkm_device_list(u64 *name, पूर्णांक size);

/* privileged रेजिस्टर पूर्णांकerface accessor macros */
#घोषणा nvkm_rd08(d,a) ioपढ़ो8((d)->pri + (a))
#घोषणा nvkm_rd16(d,a) ioपढ़ो16_native((d)->pri + (a))
#घोषणा nvkm_rd32(d,a) ioपढ़ो32_native((d)->pri + (a))
#घोषणा nvkm_wr08(d,a,v) ioग_लिखो8((v), (d)->pri + (a))
#घोषणा nvkm_wr16(d,a,v) ioग_लिखो16_native((v), (d)->pri + (a))
#घोषणा nvkm_wr32(d,a,v) ioग_लिखो32_native((v), (d)->pri + (a))
#घोषणा nvkm_mask(d,a,m,v) (अणु                                                  \
	काष्ठा nvkm_device *_device = (d);                                     \
	u32 _addr = (a), _temp = nvkm_rd32(_device, _addr);                    \
	nvkm_wr32(_device, _addr, (_temp & ~(m)) | (v));                       \
	_temp;                                                                 \
पूर्ण)

व्योम nvkm_device_del(काष्ठा nvkm_device **);

काष्ठा nvkm_device_oclass अणु
	पूर्णांक (*ctor)(काष्ठा nvkm_device *, स्थिर काष्ठा nvkm_oclass *,
		    व्योम *data, u32 size, काष्ठा nvkm_object **);
	काष्ठा nvkm_sclass base;
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_sclass nvkm_udevice_sclass;

/* device logging */
#घोषणा nvdev_prपूर्णांकk_(d,l,p,f,a...) करो अणु                                       \
	स्थिर काष्ठा nvkm_device *_device = (d);                               \
	अगर (_device->debug >= (l))                                             \
		dev_##p(_device->dev, f, ##a);                                 \
पूर्ण जबतक(0)
#घोषणा nvdev_prपूर्णांकk(d,l,p,f,a...) nvdev_prपूर्णांकk_((d), NV_DBG_##l, p, f, ##a)
#घोषणा nvdev_fatal(d,f,a...) nvdev_prपूर्णांकk((d), FATAL,   crit, f, ##a)
#घोषणा nvdev_error(d,f,a...) nvdev_prपूर्णांकk((d), ERROR,    err, f, ##a)
#घोषणा nvdev_warn(d,f,a...)  nvdev_prपूर्णांकk((d),  WARN, notice, f, ##a)
#घोषणा nvdev_info(d,f,a...)  nvdev_prपूर्णांकk((d),  INFO,   info, f, ##a)
#घोषणा nvdev_debug(d,f,a...) nvdev_prपूर्णांकk((d), DEBUG,   info, f, ##a)
#घोषणा nvdev_trace(d,f,a...) nvdev_prपूर्णांकk((d), TRACE,   info, f, ##a)
#घोषणा nvdev_spam(d,f,a...)  nvdev_prपूर्णांकk((d),  SPAM,    dbg, f, ##a)
#पूर्ण_अगर
