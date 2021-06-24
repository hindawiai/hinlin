<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helper module क्रम board specअगरic I2C bus registration
 *
 * Copyright (C) 2009 Nokia Corporation.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-omap.h>
#समावेश <mach/mux.h>
#समावेश "soc.h"

#घोषणा OMAP_I2C_SIZE		0x3f
#घोषणा OMAP1_I2C_BASE		0xfffb3800

अटल स्थिर अक्षर name[] = "omap_i2c";

अटल काष्ठा resource i2c_resources[2] = अणु
पूर्ण;

अटल काष्ठा platक्रमm_device omap_i2c_devices[1] = अणु
पूर्ण;

अटल व्योम __init omap1_i2c_mux_pins(पूर्णांक bus_id)
अणु
	अगर (cpu_is_omap7xx()) अणु
		omap_cfg_reg(I2C_7XX_SDA);
		omap_cfg_reg(I2C_7XX_SCL);
	पूर्ण अन्यथा अणु
		omap_cfg_reg(I2C_SDA);
		omap_cfg_reg(I2C_SCL);
	पूर्ण
पूर्ण

पूर्णांक __init omap_i2c_add_bus(काष्ठा omap_i2c_bus_platक्रमm_data *pdata,
				पूर्णांक bus_id)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *res;

	अगर (bus_id > 1)
		वापस -EINVAL;

	omap1_i2c_mux_pins(bus_id);

	pdev = &omap_i2c_devices[bus_id - 1];
	pdev->id = bus_id;
	pdev->name = name;
	pdev->num_resources = ARRAY_SIZE(i2c_resources);
	res = i2c_resources;
	res[0].start = OMAP1_I2C_BASE;
	res[0].end = res[0].start + OMAP_I2C_SIZE;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = INT_I2C;
	res[1].flags = IORESOURCE_IRQ;
	pdev->resource = res;

	/* all OMAP1 have IP version 1 रेजिस्टर set */
	pdata->rev = OMAP_I2C_IP_VERSION_1;

	/* all OMAP1 I2C are implemented like this */
	pdata->flags = OMAP_I2C_FLAG_NO_FIFO |
		       OMAP_I2C_FLAG_SIMPLE_CLOCK |
		       OMAP_I2C_FLAG_16BIT_DATA_REG |
		       OMAP_I2C_FLAG_ALWAYS_ARMXOR_CLK;

	/* how the cpu bus is wired up dअगरfers क्रम 7xx only */

	अगर (cpu_is_omap7xx())
		pdata->flags |= OMAP_I2C_FLAG_BUS_SHIFT_1;
	अन्यथा
		pdata->flags |= OMAP_I2C_FLAG_BUS_SHIFT_2;

	pdev->dev.platक्रमm_data = pdata;

	वापस platक्रमm_device_रेजिस्टर(pdev);
पूर्ण

#घोषणा OMAP_I2C_MAX_CONTROLLERS 4
अटल काष्ठा omap_i2c_bus_platक्रमm_data i2c_pdata[OMAP_I2C_MAX_CONTROLLERS];

#घोषणा OMAP_I2C_CMDLINE_SETUP	(BIT(31))

/**
 * omap_i2c_bus_setup - Process command line options क्रम the I2C bus speed
 * @str: String of options
 *
 * This function allow to override the शेष I2C bus speed क्रम given I2C
 * bus with a command line option.
 *
 * Format: i2c_bus=bus_id,clkrate (in kHz)
 *
 * Returns 1 on success, 0 otherwise.
 */
अटल पूर्णांक __init omap_i2c_bus_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[3];

	get_options(str, 3, पूर्णांकs);
	अगर (पूर्णांकs[0] < 2 || पूर्णांकs[1] < 1 ||
			पूर्णांकs[1] > OMAP_I2C_MAX_CONTROLLERS)
		वापस 0;
	i2c_pdata[पूर्णांकs[1] - 1].clkrate = पूर्णांकs[2];
	i2c_pdata[पूर्णांकs[1] - 1].clkrate |= OMAP_I2C_CMDLINE_SETUP;

	वापस 1;
पूर्ण
__setup("i2c_bus=", omap_i2c_bus_setup);

/*
 * Register busses defined in command line but that are not रेजिस्टरed with
 * omap_रेजिस्टर_i2c_bus from board initialization code.
 */
पूर्णांक __init omap_रेजिस्टर_i2c_bus_cmdline(व्योम)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_pdata); i++)
		अगर (i2c_pdata[i].clkrate & OMAP_I2C_CMDLINE_SETUP) अणु
			i2c_pdata[i].clkrate &= ~OMAP_I2C_CMDLINE_SETUP;
			err = omap_i2c_add_bus(&i2c_pdata[i], i + 1);
			अगर (err)
				जाओ out;
		पूर्ण

out:
	वापस err;
पूर्ण

/**
 * omap_रेजिस्टर_i2c_bus - रेजिस्टर I2C bus with device descriptors
 * @bus_id: bus id counting from number 1
 * @clkrate: घड़ी rate of the bus in kHz
 * @info: poपूर्णांकer पूर्णांकo I2C device descriptor table or शून्य
 * @len: number of descriptors in the table
 *
 * Returns 0 on success or an error code.
 */
पूर्णांक __init omap_रेजिस्टर_i2c_bus(पूर्णांक bus_id, u32 clkrate,
			  काष्ठा i2c_board_info स्थिर *info,
			  अचिन्हित len)
अणु
	पूर्णांक err;

	BUG_ON(bus_id < 1 || bus_id > OMAP_I2C_MAX_CONTROLLERS);

	अगर (info) अणु
		err = i2c_रेजिस्टर_board_info(bus_id, info, len);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!i2c_pdata[bus_id - 1].clkrate)
		i2c_pdata[bus_id - 1].clkrate = clkrate;

	i2c_pdata[bus_id - 1].clkrate &= ~OMAP_I2C_CMDLINE_SETUP;

	वापस omap_i2c_add_bus(&i2c_pdata[bus_id - 1], bus_id);
पूर्ण

अटल  पूर्णांक __init omap_i2c_cmdline(व्योम)
अणु
	वापस omap_रेजिस्टर_i2c_bus_cmdline();
पूर्ण
subsys_initcall(omap_i2c_cmdline);
