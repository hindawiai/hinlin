<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_I2C_AUX_H__
#घोषणा __NVKM_I2C_AUX_H__
#समावेश "pad.h"

अटल अंतरभूत व्योम
nvkm_i2c_aux_स्वतःdpcd(काष्ठा nvkm_i2c *i2c, पूर्णांक aux, bool enable)
अणु
	अगर (i2c->func->aux_स्वतःdpcd)
		i2c->func->aux_स्वतःdpcd(i2c, aux, false);
पूर्ण

काष्ठा nvkm_i2c_aux_func अणु
	bool address_only;
	पूर्णांक  (*xfer)(काष्ठा nvkm_i2c_aux *, bool retry, u8 type,
		     u32 addr, u8 *data, u8 *size);
	पूर्णांक  (*lnk_ctl)(काष्ठा nvkm_i2c_aux *, पूर्णांक link_nr, पूर्णांक link_bw,
			bool enhanced_framing);
पूर्ण;

पूर्णांक nvkm_i2c_aux_ctor(स्थिर काष्ठा nvkm_i2c_aux_func *, काष्ठा nvkm_i2c_pad *,
		      पूर्णांक id, काष्ठा nvkm_i2c_aux *);
पूर्णांक nvkm_i2c_aux_new_(स्थिर काष्ठा nvkm_i2c_aux_func *, काष्ठा nvkm_i2c_pad *,
		      पूर्णांक id, काष्ठा nvkm_i2c_aux **);
व्योम nvkm_i2c_aux_del(काष्ठा nvkm_i2c_aux **);
व्योम nvkm_i2c_aux_init(काष्ठा nvkm_i2c_aux *);
व्योम nvkm_i2c_aux_fini(काष्ठा nvkm_i2c_aux *);
पूर्णांक nvkm_i2c_aux_xfer(काष्ठा nvkm_i2c_aux *, bool retry, u8 type,
		      u32 addr, u8 *data, u8 *size);

पूर्णांक g94_i2c_aux_new_(स्थिर काष्ठा nvkm_i2c_aux_func *, काष्ठा nvkm_i2c_pad *,
		     पूर्णांक, u8, काष्ठा nvkm_i2c_aux **);

पूर्णांक g94_i2c_aux_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, काष्ठा nvkm_i2c_aux **);
पूर्णांक g94_i2c_aux_xfer(काष्ठा nvkm_i2c_aux *, bool, u8, u32, u8 *, u8 *);
पूर्णांक gf119_i2c_aux_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, काष्ठा nvkm_i2c_aux **);
पूर्णांक gm200_i2c_aux_new(काष्ठा nvkm_i2c_pad *, पूर्णांक, u8, काष्ठा nvkm_i2c_aux **);

#घोषणा AUX_MSG(b,l,f,a...) करो अणु                                               \
	काष्ठा nvkm_i2c_aux *_aux = (b);                                       \
	nvkm_##l(&_aux->pad->i2c->subdev, "aux %04x: "f"\n", _aux->id, ##a);   \
पूर्ण जबतक(0)
#घोषणा AUX_ERR(b,f,a...) AUX_MSG((b), error, f, ##a)
#घोषणा AUX_DBG(b,f,a...) AUX_MSG((b), debug, f, ##a)
#घोषणा AUX_TRACE(b,f,a...) AUX_MSG((b), trace, f, ##a)
#पूर्ण_अगर
