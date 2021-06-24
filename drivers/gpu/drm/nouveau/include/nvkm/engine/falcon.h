<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FLCNEN_H__
#घोषणा __NVKM_FLCNEN_H__
#घोषणा nvkm_falcon(p) container_of((p), काष्ठा nvkm_falcon, engine)
#समावेश <core/engine.h>
काष्ठा nvkm_fअगरo_chan;
काष्ठा nvkm_gpuobj;

क्रमागत nvkm_falcon_dmaidx अणु
	FALCON_DMAIDX_UCODE		= 0,
	FALCON_DMAIDX_VIRT		= 1,
	FALCON_DMAIDX_PHYS_VID		= 2,
	FALCON_DMAIDX_PHYS_SYS_COH	= 3,
	FALCON_DMAIDX_PHYS_SYS_NCOH	= 4,
	FALCON_SEC2_DMAIDX_UCODE	= 6,
पूर्ण;

काष्ठा nvkm_falcon अणु
	स्थिर काष्ठा nvkm_falcon_func *func;
	स्थिर काष्ठा nvkm_subdev *owner;
	स्थिर अक्षर *name;
	u32 addr;

	काष्ठा mutex mutex;
	काष्ठा mutex dmem_mutex;
	bool oneinit;

	स्थिर काष्ठा nvkm_subdev *user;

	u8 version;
	u8 secret;
	bool debug;

	काष्ठा nvkm_memory *core;
	bool बाह्यal;

	काष्ठा अणु
		u32 limit;
		u32 *data;
		u32  size;
		u8 ports;
	पूर्ण code;

	काष्ठा अणु
		u32 limit;
		u32 *data;
		u32  size;
		u8 ports;
	पूर्ण data;

	काष्ठा nvkm_engine engine;
पूर्ण;

/* This स्थिरructor must be called from the owner's oneinit() hook and
 * *not* its स्थिरructor.  This is to ensure that DEVINIT has been
 * completed, and that the device is correctly enabled beक्रमe we touch
 * falcon रेजिस्टरs.
 */
पूर्णांक nvkm_falcon_v1_new(काष्ठा nvkm_subdev *owner, स्थिर अक्षर *name, u32 addr,
		       काष्ठा nvkm_falcon **);

व्योम nvkm_falcon_del(काष्ठा nvkm_falcon **);
पूर्णांक nvkm_falcon_get(काष्ठा nvkm_falcon *, स्थिर काष्ठा nvkm_subdev *);
व्योम nvkm_falcon_put(काष्ठा nvkm_falcon *, स्थिर काष्ठा nvkm_subdev *);

पूर्णांक nvkm_falcon_new_(स्थिर काष्ठा nvkm_falcon_func *, काष्ठा nvkm_device *,
		     क्रमागत nvkm_subdev_type, पूर्णांक inst, bool enable, u32 addr, काष्ठा nvkm_engine **);

काष्ठा nvkm_falcon_func अणु
	काष्ठा अणु
		u32 *data;
		u32  size;
	पूर्ण code;
	काष्ठा अणु
		u32 *data;
		u32  size;
	पूर्ण data;
	व्योम (*init)(काष्ठा nvkm_falcon *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_falcon *, काष्ठा nvkm_fअगरo_chan *);

	u32 debug;
	u32 fbअगर;

	व्योम (*load_imem)(काष्ठा nvkm_falcon *, व्योम *, u32, u32, u16, u8, bool);
	व्योम (*load_dmem)(काष्ठा nvkm_falcon *, व्योम *, u32, u32, u8);
	व्योम (*पढ़ो_dmem)(काष्ठा nvkm_falcon *, u32, u32, u8, व्योम *);
	u32 emem_addr;
	व्योम (*bind_context)(काष्ठा nvkm_falcon *, काष्ठा nvkm_memory *);
	पूर्णांक (*रुको_क्रम_halt)(काष्ठा nvkm_falcon *, u32);
	पूर्णांक (*clear_पूर्णांकerrupt)(काष्ठा nvkm_falcon *, u32);
	व्योम (*set_start_addr)(काष्ठा nvkm_falcon *, u32 start_addr);
	व्योम (*start)(काष्ठा nvkm_falcon *);
	पूर्णांक (*enable)(काष्ठा nvkm_falcon *falcon);
	व्योम (*disable)(काष्ठा nvkm_falcon *falcon);
	पूर्णांक (*reset)(काष्ठा nvkm_falcon *);

	काष्ठा अणु
		u32 head;
		u32 tail;
		u32 stride;
	पूर्ण cmdq, msgq;

	काष्ठा nvkm_sclass sclass[];
पूर्ण;

अटल अंतरभूत u32
nvkm_falcon_rd32(काष्ठा nvkm_falcon *falcon, u32 addr)
अणु
	वापस nvkm_rd32(falcon->owner->device, falcon->addr + addr);
पूर्ण

अटल अंतरभूत व्योम
nvkm_falcon_wr32(काष्ठा nvkm_falcon *falcon, u32 addr, u32 data)
अणु
	nvkm_wr32(falcon->owner->device, falcon->addr + addr, data);
पूर्ण

अटल अंतरभूत u32
nvkm_falcon_mask(काष्ठा nvkm_falcon *falcon, u32 addr, u32 mask, u32 val)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;

	वापस nvkm_mask(device, falcon->addr + addr, mask, val);
पूर्ण

व्योम nvkm_falcon_load_imem(काष्ठा nvkm_falcon *, व्योम *, u32, u32, u16, u8,
			   bool);
व्योम nvkm_falcon_load_dmem(काष्ठा nvkm_falcon *, व्योम *, u32, u32, u8);
व्योम nvkm_falcon_पढ़ो_dmem(काष्ठा nvkm_falcon *, u32, u32, u8, व्योम *);
व्योम nvkm_falcon_bind_context(काष्ठा nvkm_falcon *, काष्ठा nvkm_memory *);
व्योम nvkm_falcon_set_start_addr(काष्ठा nvkm_falcon *, u32);
व्योम nvkm_falcon_start(काष्ठा nvkm_falcon *);
पूर्णांक nvkm_falcon_रुको_क्रम_halt(काष्ठा nvkm_falcon *, u32);
पूर्णांक nvkm_falcon_clear_पूर्णांकerrupt(काष्ठा nvkm_falcon *, u32);
पूर्णांक nvkm_falcon_enable(काष्ठा nvkm_falcon *);
व्योम nvkm_falcon_disable(काष्ठा nvkm_falcon *);
पूर्णांक nvkm_falcon_reset(काष्ठा nvkm_falcon *);
#पूर्ण_अगर
