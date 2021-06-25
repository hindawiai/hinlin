<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - AC'97 support
//
// Copyright 2013 Linaro Ltd.  All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/ac97_codec.h>

bool regmap_ac97_शेष_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_RESET:
	हाल AC97_POWERDOWN:
	हाल AC97_INT_PAGING:
	हाल AC97_EXTENDED_ID:
	हाल AC97_EXTENDED_STATUS:
	हाल AC97_EXTENDED_MID:
	हाल AC97_EXTENDED_MSTATUS:
	हाल AC97_GPIO_STATUS:
	हाल AC97_MISC_AFE:
	हाल AC97_VENDOR_ID1:
	हाल AC97_VENDOR_ID2:
	हाल AC97_CODEC_CLASS_REV:
	हाल AC97_PCI_SVID:
	हाल AC97_PCI_SID:
	हाल AC97_FUNC_SELECT:
	हाल AC97_FUNC_INFO:
	हाल AC97_SENSE_INFO:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(regmap_ac97_शेष_अस्थिर);

अटल पूर्णांक regmap_ac97_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक *val)
अणु
	काष्ठा snd_ac97 *ac97 = context;

	*val = ac97->bus->ops->पढ़ो(ac97, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_ac97_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val)
अणु
	काष्ठा snd_ac97 *ac97 = context;

	ac97->bus->ops->ग_लिखो(ac97, reg, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_bus ac97_regmap_bus = अणु
	.reg_ग_लिखो = regmap_ac97_reg_ग_लिखो,
	.reg_पढ़ो = regmap_ac97_reg_पढ़ो,
पूर्ण;

काष्ठा regmap *__regmap_init_ac97(काष्ठा snd_ac97 *ac97,
				  स्थिर काष्ठा regmap_config *config,
				  काष्ठा lock_class_key *lock_key,
				  स्थिर अक्षर *lock_name)
अणु
	वापस __regmap_init(&ac97->dev, &ac97_regmap_bus, ac97, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_ac97);

काष्ठा regmap *__devm_regmap_init_ac97(काष्ठा snd_ac97 *ac97,
				       स्थिर काष्ठा regmap_config *config,
				       काष्ठा lock_class_key *lock_key,
				       स्थिर अक्षर *lock_name)
अणु
	वापस __devm_regmap_init(&ac97->dev, &ac97_regmap_bus, ac97, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_ac97);

MODULE_LICENSE("GPL v2");
