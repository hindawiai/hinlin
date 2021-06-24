<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV40_GR_H__
#घोषणा __NV40_GR_H__
#घोषणा nv40_gr(p) container_of((p), काष्ठा nv40_gr, base)
#समावेश "priv.h"

काष्ठा nv40_gr अणु
	काष्ठा nvkm_gr base;
	u32 size;
	काष्ठा list_head chan;
पूर्ण;

पूर्णांक nv40_gr_new_(स्थिर काष्ठा nvkm_gr_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_gr **);
पूर्णांक nv40_gr_init(काष्ठा nvkm_gr *);
व्योम nv40_gr_पूर्णांकr(काष्ठा nvkm_gr *);
u64 nv40_gr_units(काष्ठा nvkm_gr *);

#घोषणा nv40_gr_chan(p) container_of((p), काष्ठा nv40_gr_chan, object)
#समावेश <core/object.h>

काष्ठा nv40_gr_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv40_gr *gr;
	काष्ठा nvkm_fअगरo_chan *fअगरo;
	u32 inst;
	काष्ठा list_head head;
पूर्ण;

पूर्णांक nv40_gr_chan_new(काष्ठा nvkm_gr *, काष्ठा nvkm_fअगरo_chan *,
		     स्थिर काष्ठा nvkm_oclass *, काष्ठा nvkm_object **);

बाह्य स्थिर काष्ठा nvkm_object_func nv40_gr_object;

/* वापसs 1 अगर device is one of the nv4x using the 0x4497 object class,
 * helpful to determine a number of other hardware features
 */
अटल अंतरभूत पूर्णांक
nv44_gr_class(काष्ठा nvkm_device *device)
अणु
	अगर ((device->chipset & 0xf0) == 0x60)
		वापस 1;

	वापस !(0x0aaf & (1 << (device->chipset & 0x0f)));
पूर्ण

पूर्णांक  nv40_grctx_init(काष्ठा nvkm_device *, u32 *size);
व्योम nv40_grctx_fill(काष्ठा nvkm_device *, काष्ठा nvkm_gpuobj *);
#पूर्ण_अगर
