<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i2c-boardinfo.c - collect pre-declarations of I2C devices
 */

#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/property.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>

#समावेश "i2c-core.h"


/* These symbols are exported ONLY FOR the i2c core.
 * No other users will be supported.
 */
DECLARE_RWSEM(__i2c_board_lock);
EXPORT_SYMBOL_GPL(__i2c_board_lock);

LIST_HEAD(__i2c_board_list);
EXPORT_SYMBOL_GPL(__i2c_board_list);

पूर्णांक __i2c_first_dynamic_bus_num;
EXPORT_SYMBOL_GPL(__i2c_first_dynamic_bus_num);


/**
 * i2c_रेजिस्टर_board_info - अटलally declare I2C devices
 * @busnum: identअगरies the bus to which these devices beदीर्घ
 * @info: vector of i2c device descriptors
 * @len: how many descriptors in the vector; may be zero to reserve
 *	the specअगरied bus number.
 *
 * Systems using the Linux I2C driver stack can declare tables of board info
 * जबतक they initialize.  This should be करोne in board-specअगरic init code
 * near arch_initcall() समय, or equivalent, beक्रमe any I2C adapter driver is
 * रेजिस्टरed.  For example, मुख्यboard init code could define several devices,
 * as could the init code क्रम each daughtercard in a board stack.
 *
 * The I2C devices will be created later, after the adapter क्रम the relevant
 * bus has been रेजिस्टरed.  After that moment, standard driver model tools
 * are used to bind "new style" I2C drivers to the devices.  The bus number
 * क्रम any device declared using this routine is not available क्रम dynamic
 * allocation.
 *
 * The board info passed can safely be __initdata, but be careful of embedded
 * poपूर्णांकers (क्रम platक्रमm_data, functions, etc) since that won't be copied.
 */
पूर्णांक i2c_रेजिस्टर_board_info(पूर्णांक busnum, काष्ठा i2c_board_info स्थिर *info, अचिन्हित len)
अणु
	पूर्णांक status;

	करोwn_ग_लिखो(&__i2c_board_lock);

	/* dynamic bus numbers will be asचिन्हित after the last अटल one */
	अगर (busnum >= __i2c_first_dynamic_bus_num)
		__i2c_first_dynamic_bus_num = busnum + 1;

	क्रम (status = 0; len; len--, info++) अणु
		काष्ठा i2c_devinfo	*devinfo;

		devinfo = kzalloc(माप(*devinfo), GFP_KERNEL);
		अगर (!devinfo) अणु
			pr_debug("i2c-core: can't register boardinfo!\n");
			status = -ENOMEM;
			अवरोध;
		पूर्ण

		devinfo->busnum = busnum;
		devinfo->board_info = *info;

		अगर (info->resources) अणु
			devinfo->board_info.resources =
				kmemdup(info->resources,
					info->num_resources *
						माप(*info->resources),
					GFP_KERNEL);
			अगर (!devinfo->board_info.resources) अणु
				status = -ENOMEM;
				kमुक्त(devinfo);
				अवरोध;
			पूर्ण
		पूर्ण

		list_add_tail(&devinfo->list, &__i2c_board_list);
	पूर्ण

	up_ग_लिखो(&__i2c_board_lock);

	वापस status;
पूर्ण
