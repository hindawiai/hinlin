<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FIFO_H__
#घोषणा __NVKM_FIFO_H__
#समावेश <core/engine.h>
#समावेश <core/object.h>
#समावेश <core/event.h>
काष्ठा nvkm_fault_data;

#घोषणा NVKM_FIFO_CHID_NR 4096
#घोषणा NVKM_FIFO_ENGN_NR 16

काष्ठा nvkm_fअगरo_engn अणु
	काष्ठा nvkm_object *object;
	पूर्णांक refcount;
	पूर्णांक usecount;
पूर्ण;

काष्ठा nvkm_fअगरo_chan अणु
	स्थिर काष्ठा nvkm_fअगरo_chan_func *func;
	काष्ठा nvkm_fअगरo *fअगरo;
	u32 engm;
	काष्ठा nvkm_object object;

	काष्ठा list_head head;
	u16 chid;
	काष्ठा nvkm_gpuobj *inst;
	काष्ठा nvkm_gpuobj *push;
	काष्ठा nvkm_vmm *vmm;
	व्योम __iomem *user;
	u64 addr;
	u32 size;

	काष्ठा nvkm_fअगरo_engn engn[NVKM_FIFO_ENGN_NR];
पूर्ण;

काष्ठा nvkm_fअगरo अणु
	स्थिर काष्ठा nvkm_fअगरo_func *func;
	काष्ठा nvkm_engine engine;

	DECLARE_BITMAP(mask, NVKM_FIFO_CHID_NR);
	पूर्णांक nr;
	काष्ठा list_head chan;
	spinlock_t lock;
	काष्ठा mutex mutex;

	काष्ठा nvkm_event uevent; /* async user trigger */
	काष्ठा nvkm_event cevent; /* channel creation event */
	काष्ठा nvkm_event kevent; /* channel समाप्तed */
पूर्ण;

व्योम nvkm_fअगरo_fault(काष्ठा nvkm_fअगरo *, काष्ठा nvkm_fault_data *);
व्योम nvkm_fअगरo_छोड़ो(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ *);
व्योम nvkm_fअगरo_start(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ *);

व्योम nvkm_fअगरo_chan_put(काष्ठा nvkm_fअगरo *, अचिन्हित दीर्घ flags,
			काष्ठा nvkm_fअगरo_chan **);
काष्ठा nvkm_fअगरo_chan *
nvkm_fअगरo_chan_inst(काष्ठा nvkm_fअगरo *, u64 inst, अचिन्हित दीर्घ *flags);
काष्ठा nvkm_fअगरo_chan *
nvkm_fअगरo_chan_chid(काष्ठा nvkm_fअगरo *, पूर्णांक chid, अचिन्हित दीर्घ *flags);

पूर्णांक nv04_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक nv10_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक nv17_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक nv40_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक nv50_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक g84_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gf100_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gk104_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gk110_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gk208_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gk20a_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gm107_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gm200_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gm20b_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gp100_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gp10b_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक gv100_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
पूर्णांक tu102_fअगरo_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fअगरo **);
#पूर्ण_अगर
