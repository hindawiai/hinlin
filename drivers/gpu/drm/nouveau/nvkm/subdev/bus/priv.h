<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BUS_PRIV_H__
#घोषणा __NVKM_BUS_PRIV_H__
#घोषणा nvkm_bus(p) container_of((p), काष्ठा nvkm_bus, subdev)
#समावेश <subdev/bus.h>

काष्ठा nvkm_bus_func अणु
	व्योम (*init)(काष्ठा nvkm_bus *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_bus *);
	पूर्णांक (*hwsq_exec)(काष्ठा nvkm_bus *, u32 *, u32);
	u32 hwsq_size;
पूर्ण;

पूर्णांक nvkm_bus_new_(स्थिर काष्ठा nvkm_bus_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_bus **);

व्योम nv50_bus_init(काष्ठा nvkm_bus *);
व्योम nv50_bus_पूर्णांकr(काष्ठा nvkm_bus *);
#पूर्ण_अगर
