<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_I2C_PRIV_H__
#घोषणा __NVKM_I2C_PRIV_H__
#घोषणा nvkm_i2c(p) container_of((p), काष्ठा nvkm_i2c, subdev)
#समावेश <subdev/i2c.h>

पूर्णांक nvkm_i2c_new_(स्थिर काष्ठा nvkm_i2c_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_i2c **);

काष्ठा nvkm_i2c_func अणु
	पूर्णांक (*pad_x_new)(काष्ठा nvkm_i2c *, पूर्णांक id, काष्ठा nvkm_i2c_pad **);
	पूर्णांक (*pad_s_new)(काष्ठा nvkm_i2c *, पूर्णांक id, काष्ठा nvkm_i2c_pad **);

	/* number of native dp aux channels present */
	पूर्णांक aux;

	/* पढ़ो and ack pending पूर्णांकerrupts, वापसing only data
	 * क्रम ports that have not been masked off, जबतक still
	 * perक्रमming the ack क्रम anything that was pending.
	 */
	व्योम (*aux_stat)(काष्ठा nvkm_i2c *, u32 *, u32 *, u32 *, u32 *);

	/* mask on/off पूर्णांकerrupt types क्रम a given set of auxch
	 */
	व्योम (*aux_mask)(काष्ठा nvkm_i2c *, u32, u32, u32);

	/* enable/disable HW-initiated DPCD पढ़ोs
	 */
	व्योम (*aux_स्वतःdpcd)(काष्ठा nvkm_i2c *, पूर्णांक aux, bool enable);
पूर्ण;

व्योम g94_aux_stat(काष्ठा nvkm_i2c *, u32 *, u32 *, u32 *, u32 *);
व्योम g94_aux_mask(काष्ठा nvkm_i2c *, u32, u32, u32);

व्योम gk104_aux_stat(काष्ठा nvkm_i2c *, u32 *, u32 *, u32 *, u32 *);
व्योम gk104_aux_mask(काष्ठा nvkm_i2c *, u32, u32, u32);
#पूर्ण_अगर
