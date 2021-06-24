<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_ICCSENSE_H__
#घोषणा __NVBIOS_ICCSENSE_H__
काष्ठा pwr_rail_resistor_t अणु
	u8 mohm;
	bool enabled;
पूर्ण;

काष्ठा pwr_rail_t अणु
	u8 mode;
	u8 extdev_id;
	u8 resistor_count;
	काष्ठा pwr_rail_resistor_t resistors[3];
	u16 config;
पूर्ण;

काष्ठा nvbios_iccsense अणु
	पूर्णांक nr_entry;
	काष्ठा pwr_rail_t *rail;
पूर्ण;

पूर्णांक nvbios_iccsense_parse(काष्ठा nvkm_bios *, काष्ठा nvbios_iccsense *);
#पूर्ण_अगर
