<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_ICCSENSE_H__
#घोषणा __NVKM_ICCSENSE_H__

#समावेश <core/subdev.h>

काष्ठा nvkm_iccsense अणु
	काष्ठा nvkm_subdev subdev;
	bool data_valid;
	काष्ठा list_head sensors;
	काष्ठा list_head rails;

	u32 घातer_w_max;
	u32 घातer_w_crit;
पूर्ण;

पूर्णांक gf100_iccsense_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_iccsense **);
पूर्णांक nvkm_iccsense_पढ़ो_all(काष्ठा nvkm_iccsense *iccsense);
#पूर्ण_अगर
