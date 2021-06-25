<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * helper functions क्रम HDMI models (Xonar HDAV1.3/HDAV1.3 Slim)
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "xonar.h"

अटल व्योम hdmi_ग_लिखो_command(काष्ठा oxygen *chip, u8 command,
			       अचिन्हित पूर्णांक count, स्थिर u8 *params)
अणु
	अचिन्हित पूर्णांक i;
	u8 checksum;

	oxygen_ग_लिखो_uart(chip, 0xfb);
	oxygen_ग_लिखो_uart(chip, 0xef);
	oxygen_ग_लिखो_uart(chip, command);
	oxygen_ग_लिखो_uart(chip, count);
	क्रम (i = 0; i < count; ++i)
		oxygen_ग_लिखो_uart(chip, params[i]);
	checksum = 0xfb + 0xef + command + count;
	क्रम (i = 0; i < count; ++i)
		checksum += params[i];
	oxygen_ग_लिखो_uart(chip, checksum);
पूर्ण

अटल व्योम xonar_hdmi_init_commands(काष्ठा oxygen *chip,
				     काष्ठा xonar_hdmi *hdmi)
अणु
	u8 param;

	oxygen_reset_uart(chip);
	param = 0;
	hdmi_ग_लिखो_command(chip, 0x61, 1, &param);
	param = 1;
	hdmi_ग_लिखो_command(chip, 0x74, 1, &param);
	hdmi_ग_लिखो_command(chip, 0x54, 5, hdmi->params);
पूर्ण

व्योम xonar_hdmi_init(काष्ठा oxygen *chip, काष्ठा xonar_hdmi *hdmi)
अणु
	hdmi->params[1] = IEC958_AES3_CON_FS_48000;
	hdmi->params[4] = 1;
	xonar_hdmi_init_commands(chip, hdmi);
पूर्ण

व्योम xonar_hdmi_cleanup(काष्ठा oxygen *chip)
अणु
	u8 param = 0;

	hdmi_ग_लिखो_command(chip, 0x74, 1, &param);
पूर्ण

व्योम xonar_hdmi_resume(काष्ठा oxygen *chip, काष्ठा xonar_hdmi *hdmi)
अणु
	xonar_hdmi_init_commands(chip, hdmi);
पूर्ण

व्योम xonar_hdmi_pcm_hardware_filter(अचिन्हित पूर्णांक channel,
				    काष्ठा snd_pcm_hardware *hardware)
अणु
	अगर (channel == PCM_MULTICH) अणु
		hardware->rates = SNDRV_PCM_RATE_44100 |
				  SNDRV_PCM_RATE_48000 |
				  SNDRV_PCM_RATE_96000 |
				  SNDRV_PCM_RATE_192000;
		hardware->rate_min = 44100;
	पूर्ण
पूर्ण

व्योम xonar_set_hdmi_params(काष्ठा oxygen *chip, काष्ठा xonar_hdmi *hdmi,
			   काष्ठा snd_pcm_hw_params *params)
अणु
	hdmi->params[0] = 0; /* 1 = non-audio */
	चयन (params_rate(params)) अणु
	हाल 44100:
		hdmi->params[1] = IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		hdmi->params[1] = IEC958_AES3_CON_FS_48000;
		अवरोध;
	शेष: /* 96000 */
		hdmi->params[1] = IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 192000:
		hdmi->params[1] = IEC958_AES3_CON_FS_192000;
		अवरोध;
	पूर्ण
	hdmi->params[2] = params_channels(params) / 2 - 1;
	अगर (params_क्रमmat(params) == SNDRV_PCM_FORMAT_S16_LE)
		hdmi->params[3] = 0;
	अन्यथा
		hdmi->params[3] = 0xc0;
	hdmi->params[4] = 1; /* ? */
	hdmi_ग_लिखो_command(chip, 0x54, 5, hdmi->params);
पूर्ण

व्योम xonar_hdmi_uart_input(काष्ठा oxygen *chip)
अणु
	अगर (chip->uart_input_count >= 2 &&
	    chip->uart_input[chip->uart_input_count - 2] == 'O' &&
	    chip->uart_input[chip->uart_input_count - 1] == 'K') अणु
		dev_dbg(chip->card->dev, "message from HDMI chip received:\n");
		prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_OFFSET,
				     chip->uart_input, chip->uart_input_count);
		chip->uart_input_count = 0;
	पूर्ण
पूर्ण
