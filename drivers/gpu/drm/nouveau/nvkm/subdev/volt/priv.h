<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_VOLT_PRIV_H__
#घोषणा __NVKM_VOLT_PRIV_H__
#घोषणा nvkm_volt(p) container_of((p), काष्ठा nvkm_volt, subdev)
#समावेश <subdev/volt.h>

व्योम nvkm_volt_ctor(स्थिर काष्ठा nvkm_volt_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		    काष्ठा nvkm_volt *);
पूर्णांक nvkm_volt_new_(स्थिर काष्ठा nvkm_volt_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_volt **);

काष्ठा nvkm_volt_func अणु
	पूर्णांक (*oneinit)(काष्ठा nvkm_volt *);
	पूर्णांक (*volt_get)(काष्ठा nvkm_volt *);
	पूर्णांक (*volt_set)(काष्ठा nvkm_volt *, u32 uv);
	पूर्णांक (*vid_get)(काष्ठा nvkm_volt *);
	पूर्णांक (*vid_set)(काष्ठा nvkm_volt *, u8 vid);
	पूर्णांक (*set_id)(काष्ठा nvkm_volt *, u8 id, पूर्णांक condition);
	पूर्णांक (*speeकरो_पढ़ो)(काष्ठा nvkm_volt *);
पूर्ण;

पूर्णांक nvkm_voltgpio_init(काष्ठा nvkm_volt *);
पूर्णांक nvkm_voltgpio_get(काष्ठा nvkm_volt *);
पूर्णांक nvkm_voltgpio_set(काष्ठा nvkm_volt *, u8);

पूर्णांक nvkm_voltpwm_init(काष्ठा nvkm_volt *volt);
पूर्णांक nvkm_voltpwm_get(काष्ठा nvkm_volt *volt);
पूर्णांक nvkm_voltpwm_set(काष्ठा nvkm_volt *volt, u32 uv);

पूर्णांक gf100_volt_oneinit(काष्ठा nvkm_volt *);
#पूर्ण_अगर
