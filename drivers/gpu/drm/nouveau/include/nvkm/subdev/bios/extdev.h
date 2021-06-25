<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_EXTDEV_H__
#घोषणा __NVBIOS_EXTDEV_H__
क्रमागत nvbios_extdev_type अणु
	NVBIOS_EXTDEV_LM89		= 0x02,
	NVBIOS_EXTDEV_VT1103M		= 0x40,
	NVBIOS_EXTDEV_PX3540		= 0x41,
	NVBIOS_EXTDEV_VT1105M		= 0x42, /* or बंद enough... */
	NVBIOS_EXTDEV_INA219		= 0x4c,
	NVBIOS_EXTDEV_INA209		= 0x4d,
	NVBIOS_EXTDEV_INA3221		= 0x4e,
	NVBIOS_EXTDEV_ADT7473		= 0x70, /* can also be a LM64 */
	NVBIOS_EXTDEV_HDCP_EEPROM	= 0x90,
	NVBIOS_EXTDEV_NONE		= 0xff,
पूर्ण;

काष्ठा nvbios_extdev_func अणु
	u8 type;
	u8 addr;
	u8 bus;
पूर्ण;

पूर्णांक
nvbios_extdev_parse(काष्ठा nvkm_bios *, पूर्णांक, काष्ठा nvbios_extdev_func *);

पूर्णांक
nvbios_extdev_find(काष्ठा nvkm_bios *, क्रमागत nvbios_extdev_type,
		   काष्ठा nvbios_extdev_func *);

bool nvbios_extdev_skip_probe(काष्ठा nvkm_bios *);
#पूर्ण_अगर
