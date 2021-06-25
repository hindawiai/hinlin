<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_VOLT_H__
#घोषणा __NVBIOS_VOLT_H__

क्रमागत nvbios_volt_type अणु
	NVBIOS_VOLT_GPIO = 0,
	NVBIOS_VOLT_PWM,
पूर्ण;

काष्ठा nvbios_volt अणु
	क्रमागत nvbios_volt_type type;
	u32 min;
	u32 max;
	u32 base;

	/* GPIO mode */
	bool ranged;
	u8   vidmask;
	s16  step;

	/* PWM mode */
	u32 pwm_freq;
	u32 pwm_range;
पूर्ण;

u32 nvbios_volt_table(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u32 nvbios_volt_parse(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		      काष्ठा nvbios_volt *);

काष्ठा nvbios_volt_entry अणु
	u32 voltage;
	u8  vid;
पूर्ण;

u32 nvbios_volt_entry(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *len);
u32 nvbios_volt_entry_parse(काष्ठा nvkm_bios *, पूर्णांक idx, u8 *ver, u8 *len,
			    काष्ठा nvbios_volt_entry *);
#पूर्ण_अगर
