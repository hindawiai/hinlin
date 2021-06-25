<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Load firmware files from Analog Devices SigmaStudio
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#अगर_अघोषित __SIGMA_FIRMWARE_H__
#घोषणा __SIGMA_FIRMWARE_H__

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/list.h>

#समावेश <sound/pcm.h>

काष्ठा sigmadsp;
काष्ठा snd_soc_component;
काष्ठा snd_pcm_substream;

काष्ठा sigmadsp_ops अणु
	पूर्णांक (*safeload)(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक addr,
			स्थिर uपूर्णांक8_t *data, माप_प्रकार len);
पूर्ण;

काष्ठा sigmadsp अणु
	स्थिर काष्ठा sigmadsp_ops *ops;

	काष्ठा list_head ctrl_list;
	काष्ठा list_head data_list;

	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list rate_स्थिरraपूर्णांकs;

	अचिन्हित पूर्णांक current_samplerate;
	काष्ठा snd_soc_component *component;
	काष्ठा device *dev;

	काष्ठा mutex lock;

	व्योम *control_data;
	पूर्णांक (*ग_लिखो)(व्योम *, अचिन्हित पूर्णांक, स्थिर uपूर्णांक8_t *, माप_प्रकार);
	पूर्णांक (*पढ़ो)(व्योम *, अचिन्हित पूर्णांक, uपूर्णांक8_t *, माप_प्रकार);
पूर्ण;

काष्ठा sigmadsp *devm_sigmadsp_init(काष्ठा device *dev,
	स्थिर काष्ठा sigmadsp_ops *ops, स्थिर अक्षर *firmware_name);
व्योम sigmadsp_reset(काष्ठा sigmadsp *sigmadsp);

पूर्णांक sigmadsp_restrict_params(काष्ठा sigmadsp *sigmadsp,
	काष्ठा snd_pcm_substream *substream);

काष्ठा i2c_client;

काष्ठा sigmadsp *devm_sigmadsp_init_regmap(काष्ठा device *dev,
	काष्ठा regmap *regmap, स्थिर काष्ठा sigmadsp_ops *ops,
	स्थिर अक्षर *firmware_name);
काष्ठा sigmadsp *devm_sigmadsp_init_i2c(काष्ठा i2c_client *client,
	स्थिर काष्ठा sigmadsp_ops *ops,	स्थिर अक्षर *firmware_name);

पूर्णांक sigmadsp_attach(काष्ठा sigmadsp *sigmadsp,
	काष्ठा snd_soc_component *component);
पूर्णांक sigmadsp_setup(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक samplerate);
व्योम sigmadsp_reset(काष्ठा sigmadsp *sigmadsp);

#पूर्ण_अगर
