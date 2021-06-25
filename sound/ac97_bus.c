<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver model AC97 bus पूर्णांकerface
 *
 * Author:	Nicolas Pitre
 * Created:	Jan 14, 2005
 * Copyright:	(C) MontaVista Software Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <sound/ac97_codec.h>

/*
 * snd_ac97_check_id() - Reads and checks the venकरोr ID of the device
 * @ac97: The AC97 device to check
 * @id: The ID to compare to
 * @id_mask: Mask that is applied to the device ID beक्रमe comparing to @id
 *
 * If @id is 0 this function वापसs true अगर the पढ़ो device venकरोr ID is
 * a valid ID. If @id is non 0 this functions वापसs true अगर @id
 * matches the पढ़ो venकरोr ID. Otherwise the function वापसs false.
 */
अटल bool snd_ac97_check_id(काष्ठा snd_ac97 *ac97, अचिन्हित पूर्णांक id,
	अचिन्हित पूर्णांक id_mask)
अणु
	ac97->id = ac97->bus->ops->पढ़ो(ac97, AC97_VENDOR_ID1) << 16;
	ac97->id |= ac97->bus->ops->पढ़ो(ac97, AC97_VENDOR_ID2);

	अगर (ac97->id == 0x0 || ac97->id == 0xffffffff)
		वापस false;

	अगर (id != 0 && id != (ac97->id & id_mask))
		वापस false;

	वापस true;
पूर्ण

/**
 * snd_ac97_reset() - Reset AC'97 device
 * @ac97: The AC'97 device to reset
 * @try_warm: Try a warm reset first
 * @id: Expected device venकरोr ID
 * @id_mask: Mask that is applied to the device ID beक्रमe comparing to @id
 *
 * This function resets the AC'97 device. If @try_warm is true the function
 * first perक्रमms a warm reset. If the warm reset is successful the function
 * वापसs 1. Otherwise or अगर @try_warm is false the function issues cold reset
 * followed by a warm reset. If this is successful the function वापसs 0,
 * otherwise a negative error code. If @id is 0 any valid device ID will be
 * accepted, otherwise only the ID that matches @id and @id_mask is accepted.
 */
पूर्णांक snd_ac97_reset(काष्ठा snd_ac97 *ac97, bool try_warm, अचिन्हित पूर्णांक id,
	अचिन्हित पूर्णांक id_mask)
अणु
	स्थिर काष्ठा snd_ac97_bus_ops *ops = ac97->bus->ops;

	अगर (try_warm && ops->warm_reset) अणु
		ops->warm_reset(ac97);
		अगर (snd_ac97_check_id(ac97, id, id_mask))
			वापस 1;
	पूर्ण

	अगर (ops->reset)
		ops->reset(ac97);
	अगर (ops->warm_reset)
		ops->warm_reset(ac97);

	अगर (snd_ac97_check_id(ac97, id, id_mask))
		वापस 0;

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_reset);

/*
 * Let drivers decide whether they want to support given codec from their
 * probe method. Drivers have direct access to the काष्ठा snd_ac97
 * काष्ठाure and may  decide based on the id field amongst other things.
 */
अटल पूर्णांक ac97_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 1;
पूर्ण

काष्ठा bus_type ac97_bus_type = अणु
	.name		= "ac97",
	.match		= ac97_bus_match,
पूर्ण;

अटल पूर्णांक __init ac97_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&ac97_bus_type);
पूर्ण

subsys_initcall(ac97_bus_init);

अटल व्योम __निकास ac97_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&ac97_bus_type);
पूर्ण

module_निकास(ac97_bus_निकास);

EXPORT_SYMBOL(ac97_bus_type);

MODULE_LICENSE("GPL");
