<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2009 ST-Ericsson AB
 *
 * ABX500 core access functions.
 * The abx500 पूर्णांकerface is used क्रम the Analog Baseband chips.
 *
 * Author: Mattias Wallin <mattias.wallin@stericsson.com>
 * Author: Mattias Nilsson <mattias.i.nilsson@stericsson.com>
 * Author: Bengt Jonsson <bengt.g.jonsson@stericsson.com>
 * Author: Rickard Andersson <rickard.andersson@stericsson.com>
 */

#समावेश <linux/regulator/machine.h>

काष्ठा device;

#अगर_अघोषित MFD_ABX500_H
#घोषणा MFD_ABX500_H

/**
 * काष्ठा abx500_init_setting
 * Initial value of the रेजिस्टरs क्रम driver to use during setup.
 */
काष्ठा abx500_init_settings अणु
	u8 bank;
	u8 reg;
	u8 setting;
पूर्ण;

पूर्णांक abx500_set_रेजिस्टर_पूर्णांकerruptible(काष्ठा device *dev, u8 bank, u8 reg,
	u8 value);
पूर्णांक abx500_get_रेजिस्टर_पूर्णांकerruptible(काष्ठा device *dev, u8 bank, u8 reg,
	u8 *value);
पूर्णांक abx500_get_रेजिस्टर_page_पूर्णांकerruptible(काष्ठा device *dev, u8 bank,
	u8 first_reg, u8 *regvals, u8 numregs);
पूर्णांक abx500_set_रेजिस्टर_page_पूर्णांकerruptible(काष्ठा device *dev, u8 bank,
	u8 first_reg, u8 *regvals, u8 numregs);
/**
 * abx500_mask_and_set_रेजिस्टर_inerruptible() - Modअगरies selected bits of a
 *	target रेजिस्टर
 *
 * @dev: The AB sub device.
 * @bank: The i2c bank number.
 * @biपंचांगask: The bit mask to use.
 * @bitvalues: The new bit values.
 *
 * Updates the value of an AB रेजिस्टर:
 * value -> ((value & ~biपंचांगask) | (bitvalues & biपंचांगask))
 */
पूर्णांक abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(काष्ठा device *dev, u8 bank,
	u8 reg, u8 biपंचांगask, u8 bitvalues);
पूर्णांक abx500_get_chip_id(काष्ठा device *dev);
पूर्णांक abx500_event_रेजिस्टरs_startup_state_get(काष्ठा device *dev, u8 *event);
पूर्णांक abx500_startup_irq_enabled(काष्ठा device *dev, अचिन्हित पूर्णांक irq);

काष्ठा abx500_ops अणु
	पूर्णांक (*get_chip_id) (काष्ठा device *);
	पूर्णांक (*get_रेजिस्टर) (काष्ठा device *, u8, u8, u8 *);
	पूर्णांक (*set_रेजिस्टर) (काष्ठा device *, u8, u8, u8);
	पूर्णांक (*get_रेजिस्टर_page) (काष्ठा device *, u8, u8, u8 *, u8);
	पूर्णांक (*set_रेजिस्टर_page) (काष्ठा device *, u8, u8, u8 *, u8);
	पूर्णांक (*mask_and_set_रेजिस्टर) (काष्ठा device *, u8, u8, u8, u8);
	पूर्णांक (*event_रेजिस्टरs_startup_state_get) (काष्ठा device *, u8 *);
	पूर्णांक (*startup_irq_enabled) (काष्ठा device *, अचिन्हित पूर्णांक);
	व्योम (*dump_all_banks) (काष्ठा device *);
पूर्ण;

पूर्णांक abx500_रेजिस्टर_ops(काष्ठा device *core_dev, काष्ठा abx500_ops *ops);
व्योम abx500_हटाओ_ops(काष्ठा device *dev);
#पूर्ण_अगर
