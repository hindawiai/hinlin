<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
 *
 * Copyright (c) 2018 Baylibre SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_AXG_TDM_FORMATTER_H
#घोषणा _MESON_AXG_TDM_FORMATTER_H

#समावेश "axg-tdm.h"

काष्ठा platक्रमm_device;
काष्ठा regmap;
काष्ठा snd_soc_dapm_widget;
काष्ठा snd_kcontrol;

काष्ठा axg_tdm_क्रमmatter_hw अणु
	अचिन्हित पूर्णांक skew_offset;
पूर्ण;

काष्ठा axg_tdm_क्रमmatter_ops अणु
	काष्ठा axg_tdm_stream *(*get_stream)(काष्ठा snd_soc_dapm_widget *w);
	व्योम (*enable)(काष्ठा regmap *map);
	व्योम (*disable)(काष्ठा regmap *map);
	पूर्णांक (*prepare)(काष्ठा regmap *map,
		       स्थिर काष्ठा axg_tdm_क्रमmatter_hw *quirks,
		       काष्ठा axg_tdm_stream *ts);
पूर्ण;

काष्ठा axg_tdm_क्रमmatter_driver अणु
	स्थिर काष्ठा snd_soc_component_driver *component_drv;
	स्थिर काष्ठा regmap_config *regmap_cfg;
	स्थिर काष्ठा axg_tdm_क्रमmatter_ops *ops;
	स्थिर काष्ठा axg_tdm_क्रमmatter_hw *quirks;
पूर्ण;

पूर्णांक axg_tdm_क्रमmatter_set_channel_masks(काष्ठा regmap *map,
					काष्ठा axg_tdm_stream *ts,
					अचिन्हित पूर्णांक offset);
पूर्णांक axg_tdm_क्रमmatter_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *control,
			    पूर्णांक event);
पूर्णांक axg_tdm_क्रमmatter_probe(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* _MESON_AXG_TDM_FORMATTER_H */
