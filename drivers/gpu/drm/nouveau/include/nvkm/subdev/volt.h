<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_VOLT_H__
#घोषणा __NVKM_VOLT_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_volt अणु
	स्थिर काष्ठा nvkm_volt_func *func;
	काष्ठा nvkm_subdev subdev;

	u8 vid_mask;
	u8 vid_nr;
	काष्ठा अणु
		u32 uv;
		u8 vid;
	पूर्ण vid[256];

	u32 max_uv;
	u32 min_uv;

	/*
	 * These are fully functional map entries creating a sw उच्चमानing क्रम
	 * the voltage. These all can describe dअगरferent kind of curves, so
	 * that क्रम any given temperature a dअगरferent one can वापस the lowest
	 * value of all three.
	 */
	u8 max0_id;
	u8 max1_id;
	u8 max2_id;

	पूर्णांक speeकरो;
पूर्ण;

पूर्णांक nvkm_volt_map(काष्ठा nvkm_volt *volt, u8 id, u8 temperature);
पूर्णांक nvkm_volt_map_min(काष्ठा nvkm_volt *volt, u8 id);
पूर्णांक nvkm_volt_get(काष्ठा nvkm_volt *);
पूर्णांक nvkm_volt_set_id(काष्ठा nvkm_volt *, u8 id, u8 min_id, u8 temp,
		     पूर्णांक condition);

पूर्णांक nv40_volt_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_volt **);
पूर्णांक gf100_volt_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_volt **);
पूर्णांक gf117_volt_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_volt **);
पूर्णांक gk104_volt_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_volt **);
पूर्णांक gk20a_volt_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_volt **);
पूर्णांक gm20b_volt_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_volt **);
#पूर्ण_अगर
