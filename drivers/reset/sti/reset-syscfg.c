<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 STMicroelectronics Limited
 * Author: Stephen Gallimore <stephen.gallimore@st.com>
 *
 * Inspired by mach-imx/src.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "reset-syscfg.h"

/**
 * काष्ठा syscfg_reset_channel - Reset channel regmap configuration
 *
 * @reset: regmap field क्रम the channel's reset bit.
 * @ack: regmap field क्रम the channel's ack bit (optional).
 */
काष्ठा syscfg_reset_channel अणु
	काष्ठा regmap_field *reset;
	काष्ठा regmap_field *ack;
पूर्ण;

/**
 * काष्ठा syscfg_reset_controller - A reset controller which groups together
 * a set of related reset bits, which may be located in dअगरferent प्रणाली
 * configuration रेजिस्टरs.
 *
 * @rst: base reset controller काष्ठाure.
 * @active_low: are the resets in this controller active low, i.e. clearing
 *              the reset bit माला_दो the hardware पूर्णांकo reset.
 * @channels: An array of reset channels क्रम this controller.
 */
काष्ठा syscfg_reset_controller अणु
	काष्ठा reset_controller_dev rst;
	bool active_low;
	काष्ठा syscfg_reset_channel *channels;
पूर्ण;

#घोषणा to_syscfg_reset_controller(_rst) \
	container_of(_rst, काष्ठा syscfg_reset_controller, rst)

अटल पूर्णांक syscfg_reset_program_hw(काष्ठा reset_controller_dev *rcdev,
				   अचिन्हित दीर्घ idx, पूर्णांक निश्चित)
अणु
	काष्ठा syscfg_reset_controller *rst = to_syscfg_reset_controller(rcdev);
	स्थिर काष्ठा syscfg_reset_channel *ch;
	u32 ctrl_val = rst->active_low ? !निश्चित : !!निश्चित;
	पूर्णांक err;

	अगर (idx >= rcdev->nr_resets)
		वापस -EINVAL;

	ch = &rst->channels[idx];

	err = regmap_field_ग_लिखो(ch->reset, ctrl_val);
	अगर (err)
		वापस err;

	अगर (ch->ack) अणु
		अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
		u32 ack_val;

		जबतक (true) अणु
			err = regmap_field_पढ़ो(ch->ack, &ack_val);
			अगर (err)
				वापस err;

			अगर (ack_val == ctrl_val)
				अवरोध;

			अगर (समय_after(jअगरfies, समयout))
				वापस -ETIME;

			cpu_relax();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक syscfg_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ idx)
अणु
	वापस syscfg_reset_program_hw(rcdev, idx, true);
पूर्ण

अटल पूर्णांक syscfg_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ idx)
अणु
	वापस syscfg_reset_program_hw(rcdev, idx, false);
पूर्ण

अटल पूर्णांक syscfg_reset_dev(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ idx)
अणु
	पूर्णांक err;

	err = syscfg_reset_निश्चित(rcdev, idx);
	अगर (err)
		वापस err;

	वापस syscfg_reset_deनिश्चित(rcdev, idx);
पूर्ण

अटल पूर्णांक syscfg_reset_status(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ idx)
अणु
	काष्ठा syscfg_reset_controller *rst = to_syscfg_reset_controller(rcdev);
	स्थिर काष्ठा syscfg_reset_channel *ch;
	u32 ret_val = 0;
	पूर्णांक err;

	अगर (idx >= rcdev->nr_resets)
		वापस -EINVAL;

	ch = &rst->channels[idx];
	अगर (ch->ack)
		err = regmap_field_पढ़ो(ch->ack, &ret_val);
	अन्यथा
		err = regmap_field_पढ़ो(ch->reset, &ret_val);
	अगर (err)
		वापस err;

	वापस rst->active_low ? !ret_val : !!ret_val;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops syscfg_reset_ops = अणु
	.reset    = syscfg_reset_dev,
	.निश्चित   = syscfg_reset_निश्चित,
	.deनिश्चित = syscfg_reset_deनिश्चित,
	.status   = syscfg_reset_status,
पूर्ण;

अटल पूर्णांक syscfg_reset_controller_रेजिस्टर(काष्ठा device *dev,
				स्थिर काष्ठा syscfg_reset_controller_data *data)
अणु
	काष्ठा syscfg_reset_controller *rc;
	पूर्णांक i, err;

	rc = devm_kzalloc(dev, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	rc->channels = devm_kसुस्मृति(dev, data->nr_channels,
				    माप(*rc->channels), GFP_KERNEL);
	अगर (!rc->channels)
		वापस -ENOMEM;

	rc->rst.ops = &syscfg_reset_ops,
	rc->rst.of_node = dev->of_node;
	rc->rst.nr_resets = data->nr_channels;
	rc->active_low = data->active_low;

	क्रम (i = 0; i < data->nr_channels; i++) अणु
		काष्ठा regmap *map;
		काष्ठा regmap_field *f;
		स्थिर अक्षर *compatible = data->channels[i].compatible;

		map = syscon_regmap_lookup_by_compatible(compatible);
		अगर (IS_ERR(map))
			वापस PTR_ERR(map);

		f = devm_regmap_field_alloc(dev, map, data->channels[i].reset);
		अगर (IS_ERR(f))
			वापस PTR_ERR(f);

		rc->channels[i].reset = f;

		अगर (!data->रुको_क्रम_ack)
			जारी;

		f = devm_regmap_field_alloc(dev, map, data->channels[i].ack);
		अगर (IS_ERR(f))
			वापस PTR_ERR(f);

		rc->channels[i].ack = f;
	पूर्ण

	err = reset_controller_रेजिस्टर(&rc->rst);
	अगर (!err)
		dev_info(dev, "registered\n");

	वापस err;
पूर्ण

पूर्णांक syscfg_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = pdev ? &pdev->dev : शून्य;
	स्थिर काष्ठा of_device_id *match;

	अगर (!dev || !dev->driver)
		वापस -ENODEV;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	वापस syscfg_reset_controller_रेजिस्टर(dev, match->data);
पूर्ण
