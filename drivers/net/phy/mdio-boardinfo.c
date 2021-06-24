<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * mdio-boardinfo - Collect pre-declarations क्रम MDIO devices
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>

#समावेश "mdio-boardinfo.h"

अटल LIST_HEAD(mdio_board_list);
अटल DEFINE_MUTEX(mdio_board_lock);

/**
 * mdiobus_setup_mdiodev_from_board_info - create and setup MDIO devices
 * from pre-collected board specअगरic MDIO inक्रमmation
 * @bus: Bus the board_info beदीर्घs to
 * @cb: Callback to create device on bus
 * Context: can sleep
 */
व्योम mdiobus_setup_mdiodev_from_board_info(काष्ठा mii_bus *bus,
					   पूर्णांक (*cb)
					   (काष्ठा mii_bus *bus,
					    काष्ठा mdio_board_info *bi))
अणु
	काष्ठा mdio_board_entry *be;
	काष्ठा mdio_board_entry *पंचांगp;
	काष्ठा mdio_board_info *bi;
	पूर्णांक ret;

	mutex_lock(&mdio_board_lock);
	list_क्रम_each_entry_safe(be, पंचांगp, &mdio_board_list, list) अणु
		bi = &be->board_info;

		अगर (म_भेद(bus->id, bi->bus_id))
			जारी;

		mutex_unlock(&mdio_board_lock);
		ret = cb(bus, bi);
		mutex_lock(&mdio_board_lock);
		अगर (ret)
			जारी;

	पूर्ण
	mutex_unlock(&mdio_board_lock);
पूर्ण
EXPORT_SYMBOL(mdiobus_setup_mdiodev_from_board_info);

/**
 * mdiobus_रेजिस्टर_board_info - रेजिस्टर MDIO devices क्रम a given board
 * @info: array of devices descriptors
 * @n: number of descriptors provided
 * Context: can sleep
 *
 * The board info passed can be marked with __initdata but be poपूर्णांकers
 * such as platक्रमm_data etc. are copied as-is
 */
पूर्णांक mdiobus_रेजिस्टर_board_info(स्थिर काष्ठा mdio_board_info *info,
				अचिन्हित पूर्णांक n)
अणु
	काष्ठा mdio_board_entry *be;
	अचिन्हित पूर्णांक i;

	be = kसुस्मृति(n, माप(*be), GFP_KERNEL);
	अगर (!be)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++, be++, info++) अणु
		स_नकल(&be->board_info, info, माप(*info));
		mutex_lock(&mdio_board_lock);
		list_add_tail(&be->list, &mdio_board_list);
		mutex_unlock(&mdio_board_lock);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdiobus_रेजिस्टर_board_info);
