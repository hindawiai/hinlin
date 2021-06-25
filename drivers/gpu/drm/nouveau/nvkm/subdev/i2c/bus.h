<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_I2C_BUS_H__
#घोषणा __NVKM_I2C_BUS_H__
#समावेश "pad.h"

काष्ठा nvkm_i2c_bus_func अणु
	व्योम (*init)(काष्ठा nvkm_i2c_bus *);
	व्योम (*drive_scl)(काष्ठा nvkm_i2c_bus *, पूर्णांक state);
	व्योम (*drive_sda)(काष्ठा nvkm_i2c_bus *, पूर्णांक state);
	पूर्णांक (*sense_scl)(काष्ठा nvkm_i2c_bus *);
	पूर्णांक (*sense_sda)(काष्ठा nvkm_i2c_bus *);
	पूर्णांक (*xfer)(काष्ठा nvkm_i2c_bus *, काष्ठा i2c_msg *, पूर्णांक num);
पूर्ण;

पूर्णांक nvkm_i2c_bus_ctor(स्थिर काष्ठा nvkm_i2c_bus_func *, काष्ठा nvkm_i2c_pad *,
		      पूर्णांक id, काष्ठा nvkm_i2c_bus *);
पूर्णांक nvkm_i2c_bus_new_(स्थिर काष्ठा nvkm_i2c_bus_func *, काष्ठा nvkm_i2c_pad *,
		      पूर्णांक id, काष्ठा nvkm_i2c_bus **);
व्योम nvkm_i2c_bus_del(काष्ठा nvkm_i2c_bus **);
व्योम nvkm_i2c_bus_init(काष्ठा nvkm_i2c_bus *);
व्योम nvkm_i2c_bus_fini(काष्ठा nvkm_i2c_bus *);

पूर्णांक nvkm_i2c_bit_xfer(काष्ठा nvkm_i2c_bus *, काष्ठा i2c_msg *, पूर्णांक);

पूर्णांक nv04_i2c_bus_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, u8,
		     काष्ठा nvkm_i2c_bus **);

पूर्णांक nv4e_i2c_bus_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, काष्ठा nvkm_i2c_bus **);
पूर्णांक nv50_i2c_bus_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, काष्ठा nvkm_i2c_bus **);
पूर्णांक gf119_i2c_bus_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, काष्ठा nvkm_i2c_bus **);

#घोषणा BUS_MSG(b,l,f,a...) करो अणु                                               \
	काष्ठा nvkm_i2c_bus *_bus = (b);                                       \
	nvkm_##l(&_bus->pad->i2c->subdev, "bus %04x: "f"\n", _bus->id, ##a);   \
पूर्ण जबतक(0)
#घोषणा BUS_ERR(b,f,a...) BUS_MSG((b), error, f, ##a)
#घोषणा BUS_DBG(b,f,a...) BUS_MSG((b), debug, f, ##a)
#घोषणा BUS_TRACE(b,f,a...) BUS_MSG((b), trace, f, ##a)
#पूर्ण_अगर
