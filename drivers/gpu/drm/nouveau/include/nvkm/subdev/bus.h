<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BUS_H__
#घोषणा __NVKM_BUS_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_bus अणु
	स्थिर काष्ठा nvkm_bus_func *func;
	काष्ठा nvkm_subdev subdev;
पूर्ण;

/* पूर्णांकerface to sequencer */
काष्ठा nvkm_hwsq;
पूर्णांक  nvkm_hwsq_init(काष्ठा nvkm_subdev *, काष्ठा nvkm_hwsq **);
पूर्णांक  nvkm_hwsq_fini(काष्ठा nvkm_hwsq **, bool exec);
व्योम nvkm_hwsq_wr32(काष्ठा nvkm_hwsq *, u32 addr, u32 data);
व्योम nvkm_hwsq_setf(काष्ठा nvkm_hwsq *, u8 flag, पूर्णांक data);
व्योम nvkm_hwsq_रुको(काष्ठा nvkm_hwsq *, u8 flag, u8 data);
व्योम nvkm_hwsq_रुको_vblank(काष्ठा nvkm_hwsq *);
व्योम nvkm_hwsq_nsec(काष्ठा nvkm_hwsq *, u32 nsec);

पूर्णांक nv04_bus_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bus **);
पूर्णांक nv31_bus_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bus **);
पूर्णांक nv50_bus_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bus **);
पूर्णांक g94_bus_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bus **);
पूर्णांक gf100_bus_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bus **);
#पूर्ण_अगर
