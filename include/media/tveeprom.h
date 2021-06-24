<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * tveeprom - Contains काष्ठाures and functions to work with Hauppauge
 *	      eeproms.
 */

#समावेश <linux/अगर_ether.h>

/**
 * क्रमागत tveeprom_audio_processor - Specअगरies the type of audio processor
 *				   used on a Hauppauge device.
 *
 * @TVEEPROM_AUDPROC_NONE:	No audio processor present
 * @TVEEPROM_AUDPROC_INTERNAL:	The audio processor is पूर्णांकernal to the
 *				video processor
 * @TVEEPROM_AUDPROC_MSP:	The audio processor is a MSPXXXX device
 * @TVEEPROM_AUDPROC_OTHER:	The audio processor is another device
 */
क्रमागत tveeprom_audio_processor अणु
	TVEEPROM_AUDPROC_NONE,
	TVEEPROM_AUDPROC_INTERNAL,
	TVEEPROM_AUDPROC_MSP,
	TVEEPROM_AUDPROC_OTHER,
पूर्ण;

/**
 * काष्ठा tveeprom - Contains the fields parsed from Hauppauge eeproms
 *
 * @has_radio:			1 अगर the device has radio; 0 otherwise.
 *
 * @has_ir:			If has_ir == 0, then it is unknown what the IR
 *				capabilities are. Otherwise:
 *				bit 0) 1 (= IR capabilities are known);
 *				bit 1) IR receiver present;
 *				bit 2) IR transmitter (blaster) present.
 *
 * @has_MAC_address:		0: no MAC, 1: MAC present, 2: unknown.
 * @tuner_type:			type of the tuner (TUNER_*, as defined at
 *				include/media/tuner.h).
 *
 * @tuner_क्रमmats:		Supported analog TV standards (V4L2_STD_*).
 * @tuner_hauppauge_model:	Hauppauge's code क्रम the device model number.
 * @tuner2_type:		type of the second tuner (TUNER_*, as defined
 *				at include/media/tuner.h).
 *
 * @tuner2_क्रमmats:		Tuner 2 supported analog TV standards
 *				(V4L2_STD_*).
 *
 * @tuner2_hauppauge_model:	tuner 2 Hauppauge's code क्रम the device model
 *				number.
 *
 * @audio_processor:		analog audio decoder, as defined by क्रमागत
 *				tveeprom_audio_processor.
 *
 * @decoder_processor:		Hauppauge's code क्रम the decoder chipset.
 *				Unused by the drivers, as they probe the
 *				decoder based on the PCI or USB ID.
 *
 * @model:			Hauppauge's model number
 *
 * @revision:			Card revision number
 *
 * @serial_number:		Card's serial number
 *
 * @rev_str:			Card revision converted to number
 *
 * @MAC_address:		MAC address क्रम the network पूर्णांकerface
 */
काष्ठा tveeprom अणु
	u32 has_radio;
	u32 has_ir;
	u32 has_MAC_address;

	u32 tuner_type;
	u32 tuner_क्रमmats;
	u32 tuner_hauppauge_model;

	u32 tuner2_type;
	u32 tuner2_क्रमmats;
	u32 tuner2_hauppauge_model;

	u32 audio_processor;
	u32 decoder_processor;

	u32 model;
	u32 revision;
	u32 serial_number;
	अक्षर rev_str[5];
	u8 MAC_address[ETH_ALEN];
पूर्ण;

/**
 * tveeprom_hauppauge_analog - Fill काष्ठा tveeprom using the contents
 *			       of the eeprom previously filled at
 *			       @eeprom_data field.
 *
 * @tvee:		Struct to where the eeprom parsed data will be filled;
 * @eeprom_data:	Array with the contents of the eeprom_data. It should
 *			contain 256 bytes filled with the contents of the
 *			eeprom पढ़ो from the Hauppauge device.
 */
व्योम tveeprom_hauppauge_analog(काष्ठा tveeprom *tvee,
			       अचिन्हित अक्षर *eeprom_data);

/**
 * tveeprom_पढ़ो - Reads the contents of the eeprom found at the Hauppauge
 *		   devices.
 *
 * @c:		I2C client काष्ठा
 * @eedata:	Array where the eeprom content will be stored.
 * @len:	Size of @eedata array. If the eeprom content will be latter
 *		be parsed by tveeprom_hauppauge_analog(), len should be, at
 *		least, 256.
 */
पूर्णांक tveeprom_पढ़ो(काष्ठा i2c_client *c, अचिन्हित अक्षर *eedata, पूर्णांक len);
