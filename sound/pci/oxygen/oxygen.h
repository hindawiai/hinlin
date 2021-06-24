<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित OXYGEN_H_INCLUDED
#घोषणा OXYGEN_H_INCLUDED

#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश "oxygen_regs.h"

/* 1 << PCM_x == OXYGEN_CHANNEL_x */
#घोषणा PCM_A		0
#घोषणा PCM_B		1
#घोषणा PCM_C		2
#घोषणा PCM_SPDIF	3
#घोषणा PCM_MULTICH	4
#घोषणा PCM_AC97	5
#घोषणा PCM_COUNT	6

#घोषणा OXYGEN_MCLKS(f_single, f_द्विगुन, f_quad) ((MCLK_##f_single << 0) | \
						  (MCLK_##f_द्विगुन << 2) | \
						  (MCLK_##f_quad   << 4))

#घोषणा OXYGEN_IO_SIZE	0x100

#घोषणा OXYGEN_EEPROM_ID	0x434d	/* "CM" */

/* model-specअगरic configuration of outमाला_दो/inमाला_दो */
#घोषणा PLAYBACK_0_TO_I2S	0x0001
     /* PLAYBACK_0_TO_AC97_0		not implemented */
#घोषणा PLAYBACK_1_TO_SPDIF	0x0004
#घोषणा PLAYBACK_2_TO_AC97_1	0x0008
#घोषणा CAPTURE_0_FROM_I2S_1	0x0010
#घोषणा CAPTURE_0_FROM_I2S_2	0x0020
     /* CAPTURE_0_FROM_AC97_0		not implemented */
#घोषणा CAPTURE_1_FROM_SPDIF	0x0080
#घोषणा CAPTURE_2_FROM_I2S_2	0x0100
#घोषणा CAPTURE_2_FROM_AC97_1	0x0200
#घोषणा CAPTURE_3_FROM_I2S_3	0x0400
#घोषणा MIDI_OUTPUT		0x0800
#घोषणा MIDI_INPUT		0x1000
#घोषणा AC97_CD_INPUT		0x2000
#घोषणा AC97_FMIC_SWITCH	0x4000

क्रमागत अणु
	CONTROL_SPDIF_PCM,
	CONTROL_SPDIF_INPUT_BITS,
	CONTROL_MIC_CAPTURE_SWITCH,
	CONTROL_LINE_CAPTURE_SWITCH,
	CONTROL_CD_CAPTURE_SWITCH,
	CONTROL_AUX_CAPTURE_SWITCH,
	CONTROL_COUNT
पूर्ण;

#घोषणा OXYGEN_PCI_SUBID(sv, sd) \
	.venकरोr = PCI_VENDOR_ID_CMEDIA, \
	.device = 0x8788, \
	.subvenकरोr = sv, \
	.subdevice = sd

#घोषणा BROKEN_EEPROM_DRIVER_DATA ((अचिन्हित दीर्घ)-1)
#घोषणा OXYGEN_PCI_SUBID_BROKEN_EEPROM \
	OXYGEN_PCI_SUBID(PCI_VENDOR_ID_CMEDIA, 0x8788), \
	.driver_data = BROKEN_EEPROM_DRIVER_DATA

काष्ठा pci_dev;
काष्ठा pci_device_id;
काष्ठा snd_card;
काष्ठा snd_pcm_substream;
काष्ठा snd_pcm_hardware;
काष्ठा snd_pcm_hw_params;
काष्ठा snd_kcontrol_new;
काष्ठा snd_rawmidi;
काष्ठा snd_info_buffer;
काष्ठा oxygen;

काष्ठा oxygen_model अणु
	स्थिर अक्षर *लघुname;
	स्थिर अक्षर *दीर्घname;
	स्थिर अक्षर *chip;
	व्योम (*init)(काष्ठा oxygen *chip);
	पूर्णांक (*control_filter)(काष्ठा snd_kcontrol_new *ढाँचा);
	पूर्णांक (*mixer_init)(काष्ठा oxygen *chip);
	व्योम (*cleanup)(काष्ठा oxygen *chip);
	व्योम (*suspend)(काष्ठा oxygen *chip);
	व्योम (*resume)(काष्ठा oxygen *chip);
	व्योम (*pcm_hardware_filter)(अचिन्हित पूर्णांक channel,
				    काष्ठा snd_pcm_hardware *hardware);
	व्योम (*set_dac_params)(काष्ठा oxygen *chip,
			       काष्ठा snd_pcm_hw_params *params);
	व्योम (*set_adc_params)(काष्ठा oxygen *chip,
			       काष्ठा snd_pcm_hw_params *params);
	व्योम (*update_dac_volume)(काष्ठा oxygen *chip);
	व्योम (*update_dac_mute)(काष्ठा oxygen *chip);
	व्योम (*update_center_lfe_mix)(काष्ठा oxygen *chip, bool mixed);
	अचिन्हित पूर्णांक (*adjust_dac_routing)(काष्ठा oxygen *chip,
					   अचिन्हित पूर्णांक play_routing);
	व्योम (*gpio_changed)(काष्ठा oxygen *chip);
	व्योम (*uart_input)(काष्ठा oxygen *chip);
	व्योम (*ac97_चयन)(काष्ठा oxygen *chip,
			    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mute);
	व्योम (*dump_रेजिस्टरs)(काष्ठा oxygen *chip,
			       काष्ठा snd_info_buffer *buffer);
	स्थिर अचिन्हित पूर्णांक *dac_tlv;
	माप_प्रकार model_data_size;
	अचिन्हित पूर्णांक device_config;
	u8 dac_channels_pcm;
	u8 dac_channels_mixer;
	u8 dac_volume_min;
	u8 dac_volume_max;
	u8 misc_flags;
	u8 function_flags;
	u8 dac_mclks;
	u8 adc_mclks;
	u16 dac_i2s_क्रमmat;
	u16 adc_i2s_क्रमmat;
पूर्ण;

काष्ठा oxygen अणु
	अचिन्हित दीर्घ addr;
	spinlock_t reg_lock;
	काष्ठा mutex mutex;
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	काष्ठा snd_rawmidi *midi;
	पूर्णांक irq;
	व्योम *model_data;
	अचिन्हित पूर्णांक पूर्णांकerrupt_mask;
	u8 dac_volume[8];
	u8 dac_mute;
	u8 pcm_active;
	u8 pcm_running;
	u8 dac_routing;
	u8 spdअगर_playback_enable;
	u8 has_ac97_0;
	u8 has_ac97_1;
	u32 spdअगर_bits;
	u32 spdअगर_pcm_bits;
	काष्ठा snd_pcm_substream *streams[PCM_COUNT];
	काष्ठा snd_kcontrol *controls[CONTROL_COUNT];
	काष्ठा work_काष्ठा spdअगर_input_bits_work;
	काष्ठा work_काष्ठा gpio_work;
	रुको_queue_head_t ac97_रुकोqueue;
	जोड़ अणु
		u8 _8[OXYGEN_IO_SIZE];
		__le16 _16[OXYGEN_IO_SIZE / 2];
		__le32 _32[OXYGEN_IO_SIZE / 4];
	पूर्ण saved_रेजिस्टरs;
	u16 saved_ac97_रेजिस्टरs[2][0x40];
	अचिन्हित पूर्णांक uart_input_count;
	u8 uart_input[32];
	काष्ठा oxygen_model model;
पूर्ण;

/* oxygen_lib.c */

पूर्णांक oxygen_pci_probe(काष्ठा pci_dev *pci, पूर्णांक index, अक्षर *id,
		     काष्ठा module *owner,
		     स्थिर काष्ठा pci_device_id *ids,
		     पूर्णांक (*get_model)(काष्ठा oxygen *chip,
				      स्थिर काष्ठा pci_device_id *id
				     )
		    );
व्योम oxygen_pci_हटाओ(काष्ठा pci_dev *pci);
#अगर_घोषित CONFIG_PM_SLEEP
बाह्य स्थिर काष्ठा dev_pm_ops oxygen_pci_pm;
#पूर्ण_अगर
व्योम oxygen_pci_shutकरोwn(काष्ठा pci_dev *pci);

/* oxygen_mixer.c */

पूर्णांक oxygen_mixer_init(काष्ठा oxygen *chip);
व्योम oxygen_update_dac_routing(काष्ठा oxygen *chip);
व्योम oxygen_update_spdअगर_source(काष्ठा oxygen *chip);

/* oxygen_pcm.c */

पूर्णांक oxygen_pcm_init(काष्ठा oxygen *chip);

/* oxygen_io.c */

u8 oxygen_पढ़ो8(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg);
u16 oxygen_पढ़ो16(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg);
u32 oxygen_पढ़ो32(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg);
व्योम oxygen_ग_लिखो8(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg, u8 value);
व्योम oxygen_ग_लिखो16(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg, u16 value);
व्योम oxygen_ग_लिखो32(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg, u32 value);
व्योम oxygen_ग_लिखो8_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg,
			  u8 value, u8 mask);
व्योम oxygen_ग_लिखो16_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg,
			   u16 value, u16 mask);
व्योम oxygen_ग_लिखो32_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक reg,
			   u32 value, u32 mask);

u16 oxygen_पढ़ो_ac97(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
		     अचिन्हित पूर्णांक index);
व्योम oxygen_ग_लिखो_ac97(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
		       अचिन्हित पूर्णांक index, u16 data);
व्योम oxygen_ग_लिखो_ac97_masked(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
			      अचिन्हित पूर्णांक index, u16 data, u16 mask);

पूर्णांक oxygen_ग_लिखो_spi(काष्ठा oxygen *chip, u8 control, अचिन्हित पूर्णांक data);
व्योम oxygen_ग_लिखो_i2c(काष्ठा oxygen *chip, u8 device, u8 map, u8 data);

व्योम oxygen_reset_uart(काष्ठा oxygen *chip);
व्योम oxygen_ग_लिखो_uart(काष्ठा oxygen *chip, u8 data);

u16 oxygen_पढ़ो_eeprom(काष्ठा oxygen *chip, अचिन्हित पूर्णांक index);
व्योम oxygen_ग_लिखो_eeprom(काष्ठा oxygen *chip, अचिन्हित पूर्णांक index, u16 value);

अटल अंतरभूत व्योम oxygen_set_bits8(काष्ठा oxygen *chip,
				    अचिन्हित पूर्णांक reg, u8 value)
अणु
	oxygen_ग_लिखो8_masked(chip, reg, value, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_set_bits16(काष्ठा oxygen *chip,
				     अचिन्हित पूर्णांक reg, u16 value)
अणु
	oxygen_ग_लिखो16_masked(chip, reg, value, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_set_bits32(काष्ठा oxygen *chip,
				     अचिन्हित पूर्णांक reg, u32 value)
अणु
	oxygen_ग_लिखो32_masked(chip, reg, value, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_clear_bits8(काष्ठा oxygen *chip,
				      अचिन्हित पूर्णांक reg, u8 value)
अणु
	oxygen_ग_लिखो8_masked(chip, reg, 0, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_clear_bits16(काष्ठा oxygen *chip,
				       अचिन्हित पूर्णांक reg, u16 value)
अणु
	oxygen_ग_लिखो16_masked(chip, reg, 0, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_clear_bits32(काष्ठा oxygen *chip,
				       अचिन्हित पूर्णांक reg, u32 value)
अणु
	oxygen_ग_लिखो32_masked(chip, reg, 0, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_ac97_set_bits(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
					अचिन्हित पूर्णांक index, u16 value)
अणु
	oxygen_ग_लिखो_ac97_masked(chip, codec, index, value, value);
पूर्ण

अटल अंतरभूत व्योम oxygen_ac97_clear_bits(काष्ठा oxygen *chip,
					  अचिन्हित पूर्णांक codec,
					  अचिन्हित पूर्णांक index, u16 value)
अणु
	oxygen_ग_लिखो_ac97_masked(chip, codec, index, 0, value);
पूर्ण

#पूर्ण_अगर
