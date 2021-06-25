<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2016 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#अगर_अघोषित AC97_CONTROLLER_H
#घोषणा AC97_CONTROLLER_H

#समावेश <linux/device.h>
#समावेश <linux/list.h>

#घोषणा AC97_BUS_MAX_CODECS 4
#घोषणा AC97_SLOTS_AVAILABLE_ALL 0xf

काष्ठा ac97_controller_ops;

/**
 * काष्ठा ac97_controller - The AC97 controller of the AC-Link
 * @ops:		the AC97 operations.
 * @controllers:	linked list of all existing controllers.
 * @adap:		the shell device ac97-%d, ie. ac97 adapter
 * @nr:			the number of the shell device
 * @slots_available:	the mask of accessible/scanable codecs.
 * @parent:		the device providing the AC97 controller.
 * @codecs:		the 4 possible AC97 codecs (शून्य अगर none found).
 * @codecs_pdata:	platक्रमm_data क्रम each codec (शून्य अगर no pdata).
 *
 * This काष्ठाure is पूर्णांकernal to AC97 bus, and should not be used by the
 * controllers themselves, excepting क्रम using @dev.
 */
काष्ठा ac97_controller अणु
	स्थिर काष्ठा ac97_controller_ops *ops;
	काष्ठा list_head controllers;
	काष्ठा device adap;
	पूर्णांक nr;
	अचिन्हित लघु slots_available;
	काष्ठा device *parent;
	काष्ठा ac97_codec_device *codecs[AC97_BUS_MAX_CODECS];
	व्योम *codecs_pdata[AC97_BUS_MAX_CODECS];
पूर्ण;

/**
 * काष्ठा ac97_controller_ops - The AC97 operations
 * @reset:	Cold reset of the AC97 AC-Link.
 * @warm_reset:	Warm reset of the AC97 AC-Link.
 * @पढ़ो:	Read of a single AC97 रेजिस्टर.
 *		Returns the रेजिस्टर value or a negative error code.
 * @ग_लिखो:	Write of a single AC97 रेजिस्टर.
 *
 * These are the basic operation an AC97 controller must provide क्रम an AC97
 * access functions. Amongst these, all but the last 2 are mandatory.
 * The slot number is also known as the AC97 codec number, between 0 and 3.
 */
काष्ठा ac97_controller_ops अणु
	व्योम (*reset)(काष्ठा ac97_controller *adrv);
	व्योम (*warm_reset)(काष्ठा ac97_controller *adrv);
	पूर्णांक (*ग_लिखो)(काष्ठा ac97_controller *adrv, पूर्णांक slot,
		     अचिन्हित लघु reg, अचिन्हित लघु val);
	पूर्णांक (*पढ़ो)(काष्ठा ac97_controller *adrv, पूर्णांक slot, अचिन्हित लघु reg);
पूर्ण;

#अगर IS_ENABLED(CONFIG_AC97_BUS_NEW)
काष्ठा ac97_controller *snd_ac97_controller_रेजिस्टर(
	स्थिर काष्ठा ac97_controller_ops *ops, काष्ठा device *dev,
	अचिन्हित लघु slots_available, व्योम **codecs_pdata);
व्योम snd_ac97_controller_unरेजिस्टर(काष्ठा ac97_controller *ac97_ctrl);
#अन्यथा
अटल अंतरभूत काष्ठा ac97_controller *
snd_ac97_controller_रेजिस्टर(स्थिर काष्ठा ac97_controller_ops *ops,
			     काष्ठा device *dev,
			     अचिन्हित लघु slots_available,
			     व्योम **codecs_pdata)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम
snd_ac97_controller_unरेजिस्टर(काष्ठा ac97_controller *ac97_ctrl)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
