<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALSA SoC TWL6040 codec driver
 *
 * Author:	Misael Lopez Cruz <x0052729@ti.com>
 */

#अगर_अघोषित __TWL6040_H__
#घोषणा __TWL6040_H__

क्रमागत twl6040_trim अणु
	TWL6040_TRIM_TRIM1 = 0,
	TWL6040_TRIM_TRIM2,
	TWL6040_TRIM_TRIM3,
	TWL6040_TRIM_HSOTRIM,
	TWL6040_TRIM_HFOTRIM,
	TWL6040_TRIM_INVAL,
पूर्ण;

#घोषणा TWL6040_HSF_TRIM_LEFT(x)	(x & 0x0f)
#घोषणा TWL6040_HSF_TRIM_RIGHT(x)	((x >> 4) & 0x0f)

पूर्णांक twl6040_get_dl1_gain(काष्ठा snd_soc_component *component);
व्योम twl6040_hs_jack_detect(काष्ठा snd_soc_component *component,
			    काष्ठा snd_soc_jack *jack, पूर्णांक report);
पूर्णांक twl6040_get_clk_id(काष्ठा snd_soc_component *component);
पूर्णांक twl6040_get_trim_value(काष्ठा snd_soc_component *component, क्रमागत twl6040_trim trim);
पूर्णांक twl6040_get_hs_step_size(काष्ठा snd_soc_component *component);

#पूर्ण_अगर /* End of __TWL6040_H__ */
