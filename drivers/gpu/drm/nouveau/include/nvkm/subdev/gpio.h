<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_GPIO_H__
#घोषणा __NVKM_GPIO_H__
#समावेश <core/subdev.h>
#समावेश <core/event.h>

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/gpपन.स>

काष्ठा nvkm_gpio_ntfy_req अणु
#घोषणा NVKM_GPIO_HI                                                       0x01
#घोषणा NVKM_GPIO_LO                                                       0x02
#घोषणा NVKM_GPIO_TOGGLED                                                  0x03
	u8 mask;
	u8 line;
पूर्ण;

काष्ठा nvkm_gpio_ntfy_rep अणु
	u8 mask;
पूर्ण;

काष्ठा nvkm_gpio अणु
	स्थिर काष्ठा nvkm_gpio_func *func;
	काष्ठा nvkm_subdev subdev;

	काष्ठा nvkm_event event;
पूर्ण;

व्योम nvkm_gpio_reset(काष्ठा nvkm_gpio *, u8 func);
पूर्णांक nvkm_gpio_find(काष्ठा nvkm_gpio *, पूर्णांक idx, u8 tag, u8 line,
		   काष्ठा dcb_gpio_func *);
पूर्णांक nvkm_gpio_set(काष्ठा nvkm_gpio *, पूर्णांक idx, u8 tag, u8 line, पूर्णांक state);
पूर्णांक nvkm_gpio_get(काष्ठा nvkm_gpio *, पूर्णांक idx, u8 tag, u8 line);

पूर्णांक nv10_gpio_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_gpio **);
पूर्णांक nv50_gpio_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_gpio **);
पूर्णांक g94_gpio_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_gpio **);
पूर्णांक gf119_gpio_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_gpio **);
पूर्णांक gk104_gpio_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_gpio **);
पूर्णांक ga102_gpio_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_gpio **);
#पूर्ण_अगर
