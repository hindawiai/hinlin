<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम VT1720/VT1724 (Envy24PT/Envy24HT)
 *
 *   Lowlevel functions क्रम VT1720-based motherboards
 *
 *	Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "vt1720_mobo.h"


अटल पूर्णांक k8x800_init(काष्ठा snd_ice1712 *ice)
अणु
	ice->vt1720 = 1;

	/* VT1616 codec */
	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;

	/* WM8728 codec */
	/* FIXME: TODO */

	वापस 0;
पूर्ण

अटल पूर्णांक k8x800_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	/* FIXME: needs some quirks क्रम VT1616? */
	वापस 0;
पूर्ण

/* EEPROM image */

अटल स्थिर अचिन्हित अक्षर k8x800_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x01,	/* घड़ी 256, 1ADC, 2DACs */
	[ICE_EEP2_ACLINK]      = 0x02,	/* ACLINK, packed */
	[ICE_EEP2_I2S]         = 0x00,	/* - */
	[ICE_EEP2_SPDIF]       = 0x00,	/* - */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x00,	/* - */
	[ICE_EEP2_GPIO_MASK]   = 0xff,
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,	/* - */
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,	/* - */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर sn25p_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x01,	/* घड़ी 256, 1ADC, 2DACs */
	[ICE_EEP2_ACLINK]      = 0x02,	/* ACLINK, packed */
	[ICE_EEP2_I2S]         = 0x00,	/* - */
	[ICE_EEP2_SPDIF]       = 0x41,	/* - */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x00,	/* - */
	[ICE_EEP2_GPIO_MASK]   = 0xff,
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,	/* - */
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,	/* - */
पूर्ण;


/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1720_mobo_cards[] = अणु
	अणु
		.subvenकरोr = VT1720_SUBDEVICE_K8X800,
		.name = "Albatron K8X800 Pro II",
		.model = "k8x800",
		.chip_init = k8x800_init,
		.build_controls = k8x800_add_controls,
		.eeprom_size = माप(k8x800_eeprom),
		.eeprom_data = k8x800_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1720_SUBDEVICE_ZNF3_150,
		.name = "Chaintech ZNF3-150",
		/* identical with k8x800 */
		.chip_init = k8x800_init,
		.build_controls = k8x800_add_controls,
		.eeprom_size = माप(k8x800_eeprom),
		.eeprom_data = k8x800_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1720_SUBDEVICE_ZNF3_250,
		.name = "Chaintech ZNF3-250",
		/* identical with k8x800 */
		.chip_init = k8x800_init,
		.build_controls = k8x800_add_controls,
		.eeprom_size = माप(k8x800_eeprom),
		.eeprom_data = k8x800_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1720_SUBDEVICE_9CJS,
		.name = "Chaintech 9CJS",
		/* identical with k8x800 */
		.chip_init = k8x800_init,
		.build_controls = k8x800_add_controls,
		.eeprom_size = माप(k8x800_eeprom),
		.eeprom_data = k8x800_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1720_SUBDEVICE_SN25P,
		.name = "Shuttle SN25P",
		.model = "sn25p",
		.chip_init = k8x800_init,
		.build_controls = k8x800_add_controls,
		.eeprom_size = माप(k8x800_eeprom),
		.eeprom_data = sn25p_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

