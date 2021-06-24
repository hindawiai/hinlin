<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_ICCSENSE_PRIV_H__
#घोषणा __NVKM_ICCSENSE_PRIV_H__
#घोषणा nvkm_iccsense(p) container_of((p), काष्ठा nvkm_iccsense, subdev)
#समावेश <subdev/iccsense.h>
#समावेश <subdev/bios/extdev.h>

काष्ठा nvkm_iccsense_sensor अणु
	काष्ठा list_head head;
	पूर्णांक id;
	क्रमागत nvbios_extdev_type type;
	काष्ठा i2c_adapter *i2c;
	u8 addr;
	u16 config;
पूर्ण;

काष्ठा nvkm_iccsense_rail अणु
	काष्ठा list_head head;
	पूर्णांक (*पढ़ो)(काष्ठा nvkm_iccsense *, काष्ठा nvkm_iccsense_rail *);
	काष्ठा nvkm_iccsense_sensor *sensor;
	u8 idx;
	u8 mohm;
पूर्ण;

व्योम nvkm_iccsense_ctor(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_iccsense *);
पूर्णांक nvkm_iccsense_new_(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_iccsense **);
#पूर्ण_अगर
