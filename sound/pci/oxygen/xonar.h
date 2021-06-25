<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित XONAR_H_INCLUDED
#घोषणा XONAR_H_INCLUDED

#समावेश "oxygen.h"

काष्ठा xonar_generic अणु
	अचिन्हित पूर्णांक anti_pop_delay;
	u16 output_enable_bit;
	u8 ext_घातer_reg;
	u8 ext_घातer_पूर्णांक_reg;
	u8 ext_घातer_bit;
	u8 has_घातer;
पूर्ण;

काष्ठा xonar_hdmi अणु
	u8 params[5];
पूर्ण;

/* generic helper functions */

व्योम xonar_enable_output(काष्ठा oxygen *chip);
व्योम xonar_disable_output(काष्ठा oxygen *chip);
व्योम xonar_init_ext_घातer(काष्ठा oxygen *chip);
व्योम xonar_init_cs53x1(काष्ठा oxygen *chip);
व्योम xonar_set_cs53x1_params(काष्ठा oxygen *chip,
			     काष्ठा snd_pcm_hw_params *params);

#घोषणा XONAR_GPIO_BIT_INVERT	(1 << 16)
पूर्णांक xonar_gpio_bit_चयन_get(काष्ठा snd_kcontrol *ctl,
			      काष्ठा snd_ctl_elem_value *value);
पूर्णांक xonar_gpio_bit_चयन_put(काष्ठा snd_kcontrol *ctl,
			      काष्ठा snd_ctl_elem_value *value);

/* model-specअगरic card drivers */

पूर्णांक get_xonar_pcm179x_model(काष्ठा oxygen *chip,
			    स्थिर काष्ठा pci_device_id *id);
पूर्णांक get_xonar_cs43xx_model(काष्ठा oxygen *chip,
			   स्थिर काष्ठा pci_device_id *id);
पूर्णांक get_xonar_wm87x6_model(काष्ठा oxygen *chip,
			   स्थिर काष्ठा pci_device_id *id);

/* HDMI helper functions */

व्योम xonar_hdmi_init(काष्ठा oxygen *chip, काष्ठा xonar_hdmi *data);
व्योम xonar_hdmi_cleanup(काष्ठा oxygen *chip);
व्योम xonar_hdmi_resume(काष्ठा oxygen *chip, काष्ठा xonar_hdmi *hdmi);
व्योम xonar_hdmi_pcm_hardware_filter(अचिन्हित पूर्णांक channel,
				    काष्ठा snd_pcm_hardware *hardware);
व्योम xonar_set_hdmi_params(काष्ठा oxygen *chip, काष्ठा xonar_hdmi *hdmi,
			   काष्ठा snd_pcm_hw_params *params);
व्योम xonar_hdmi_uart_input(काष्ठा oxygen *chip);

#पूर्ण_अगर
