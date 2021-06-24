<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_LTC_H__
#घोषणा __NVKM_LTC_H__
#समावेश <core/subdev.h>
#समावेश <core/mm.h>

#घोषणा NVKM_LTC_MAX_ZBC_CNT 16

काष्ठा nvkm_ltc अणु
	स्थिर काष्ठा nvkm_ltc_func *func;
	काष्ठा nvkm_subdev subdev;

	u32 ltc_nr;
	u32 lts_nr;

	काष्ठा mutex mutex; /* serialises CBC operations */
	u32 num_tags;
	u32 tag_base;
	काष्ठा nvkm_memory *tag_ram;

	पूर्णांक zbc_min;
	पूर्णांक zbc_max;
	u32 zbc_color[NVKM_LTC_MAX_ZBC_CNT][4];
	u32 zbc_depth[NVKM_LTC_MAX_ZBC_CNT];
	u32 zbc_stencil[NVKM_LTC_MAX_ZBC_CNT];
पूर्ण;

व्योम nvkm_ltc_tags_clear(काष्ठा nvkm_device *, u32 first, u32 count);

पूर्णांक nvkm_ltc_zbc_color_get(काष्ठा nvkm_ltc *, पूर्णांक index, स्थिर u32[4]);
पूर्णांक nvkm_ltc_zbc_depth_get(काष्ठा nvkm_ltc *, पूर्णांक index, स्थिर u32);
पूर्णांक nvkm_ltc_zbc_stencil_get(काष्ठा nvkm_ltc *, पूर्णांक index, स्थिर u32);

व्योम nvkm_ltc_invalidate(काष्ठा nvkm_ltc *);
व्योम nvkm_ltc_flush(काष्ठा nvkm_ltc *);

पूर्णांक gf100_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
पूर्णांक gk104_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
पूर्णांक gm107_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
पूर्णांक gm200_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
पूर्णांक gp100_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
पूर्णांक gp102_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
पूर्णांक gp10b_ltc_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_ltc **);
#पूर्ण_अगर
