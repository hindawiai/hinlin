<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_I2C_PAD_H__
#घोषणा __NVKM_I2C_PAD_H__
#समावेश "priv.h"

काष्ठा nvkm_i2c_pad अणु
	स्थिर काष्ठा nvkm_i2c_pad_func *func;
	काष्ठा nvkm_i2c *i2c;
#घोषणा NVKM_I2C_PAD_HYBRID(n) /* 'n' is hw pad index */                     (n)
#घोषणा NVKM_I2C_PAD_CCB(n) /* 'n' is ccb index */                 ((n) + 0x100)
#घोषणा NVKM_I2C_PAD_EXT(n) /* 'n' is dcb बाह्यal encoder type */ ((n) + 0x200)
	पूर्णांक id;

	क्रमागत nvkm_i2c_pad_mode अणु
		NVKM_I2C_PAD_OFF,
		NVKM_I2C_PAD_I2C,
		NVKM_I2C_PAD_AUX,
	पूर्ण mode;
	काष्ठा mutex mutex;
	काष्ठा list_head head;
पूर्ण;

काष्ठा nvkm_i2c_pad_func अणु
	पूर्णांक (*bus_new_0)(काष्ठा nvkm_i2c_pad *, पूर्णांक id, u8 drive, u8 sense,
			 काष्ठा nvkm_i2c_bus **);
	पूर्णांक (*bus_new_4)(काष्ठा nvkm_i2c_pad *, पूर्णांक id, u8 drive,
			 काष्ठा nvkm_i2c_bus **);

	पूर्णांक (*aux_new_6)(काष्ठा nvkm_i2c_pad *, पूर्णांक id, u8 drive,
			 काष्ठा nvkm_i2c_aux **);

	व्योम (*mode)(काष्ठा nvkm_i2c_pad *, क्रमागत nvkm_i2c_pad_mode);
पूर्ण;

व्योम nvkm_i2c_pad_ctor(स्थिर काष्ठा nvkm_i2c_pad_func *, काष्ठा nvkm_i2c *,
		       पूर्णांक id, काष्ठा nvkm_i2c_pad *);
पूर्णांक nvkm_i2c_pad_new_(स्थिर काष्ठा nvkm_i2c_pad_func *, काष्ठा nvkm_i2c *,
		      पूर्णांक id, काष्ठा nvkm_i2c_pad **);
व्योम nvkm_i2c_pad_del(काष्ठा nvkm_i2c_pad **);
व्योम nvkm_i2c_pad_init(काष्ठा nvkm_i2c_pad *);
व्योम nvkm_i2c_pad_fini(काष्ठा nvkm_i2c_pad *);
व्योम nvkm_i2c_pad_mode(काष्ठा nvkm_i2c_pad *, क्रमागत nvkm_i2c_pad_mode);
पूर्णांक nvkm_i2c_pad_acquire(काष्ठा nvkm_i2c_pad *, क्रमागत nvkm_i2c_pad_mode);
व्योम nvkm_i2c_pad_release(काष्ठा nvkm_i2c_pad *);

व्योम g94_i2c_pad_mode(काष्ठा nvkm_i2c_pad *, क्रमागत nvkm_i2c_pad_mode);

पूर्णांक nv04_i2c_pad_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक nv4e_i2c_pad_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक nv50_i2c_pad_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक g94_i2c_pad_x_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक gf119_i2c_pad_x_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक gm200_i2c_pad_x_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);

पूर्णांक g94_i2c_pad_s_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक gf119_i2c_pad_s_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);
पूर्णांक gm200_i2c_pad_s_new(काष्ठा nvkm_i2c *, पूर्णांक, काष्ठा nvkm_i2c_pad **);

पूर्णांक anx9805_pad_new(काष्ठा nvkm_i2c_bus *, पूर्णांक, u8, काष्ठा nvkm_i2c_pad **);

#घोषणा PAD_MSG(p,l,f,a...) करो अणु                                               \
	काष्ठा nvkm_i2c_pad *_pad = (p);                                       \
	nvkm_##l(&_pad->i2c->subdev, "pad %04x: "f"\n", _pad->id, ##a);        \
पूर्ण जबतक(0)
#घोषणा PAD_ERR(p,f,a...) PAD_MSG((p), error, f, ##a)
#घोषणा PAD_DBG(p,f,a...) PAD_MSG((p), debug, f, ##a)
#घोषणा PAD_TRACE(p,f,a...) PAD_MSG((p), trace, f, ##a)
#पूर्ण_अगर
