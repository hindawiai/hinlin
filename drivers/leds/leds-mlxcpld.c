<शैली गुरु>
/*
 * drivers/leds/leds-mlxcpld.c
 * Copyright (c) 2016 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016 Vadim Pasternak <vadimp@mellanox.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा MLXPLAT_CPLD_LPC_REG_BASE_ADRR     0x2500 /* LPC bus access */

/* Color codes क्रम LEDs */
#घोषणा MLXCPLD_LED_OFFSET_HALF		0x01 /* Offset from solid: 3Hz blink */
#घोषणा MLXCPLD_LED_OFFSET_FULL		0x02 /* Offset from solid: 6Hz blink */
#घोषणा MLXCPLD_LED_IS_OFF		0x00 /* Off */
#घोषणा MLXCPLD_LED_RED_STATIC_ON	0x05 /* Solid red */
#घोषणा MLXCPLD_LED_RED_BLINK_HALF	(MLXCPLD_LED_RED_STATIC_ON + \
					 MLXCPLD_LED_OFFSET_HALF)
#घोषणा MLXCPLD_LED_RED_BLINK_FULL	(MLXCPLD_LED_RED_STATIC_ON + \
					 MLXCPLD_LED_OFFSET_FULL)
#घोषणा MLXCPLD_LED_GREEN_STATIC_ON	0x0D /* Solid green */
#घोषणा MLXCPLD_LED_GREEN_BLINK_HALF	(MLXCPLD_LED_GREEN_STATIC_ON + \
					 MLXCPLD_LED_OFFSET_HALF)
#घोषणा MLXCPLD_LED_GREEN_BLINK_FULL	(MLXCPLD_LED_GREEN_STATIC_ON + \
					 MLXCPLD_LED_OFFSET_FULL)
#घोषणा MLXCPLD_LED_BLINK_3HZ		167 /* ~167 msec off/on */
#घोषणा MLXCPLD_LED_BLINK_6HZ		83 /* ~83 msec off/on */

/**
 * mlxcpld_param - LED access parameters:
 * @offset - offset क्रम LED access in CPLD device
 * @mask - mask क्रम LED access in CPLD device
 * @base_color - base color code क्रम LED
**/
काष्ठा mlxcpld_param अणु
	u8 offset;
	u8 mask;
	u8 base_color;
पूर्ण;

/**
 * mlxcpld_led_priv - LED निजी data:
 * @cled - LED class device instance
 * @param - LED CPLD access parameters
**/
काष्ठा mlxcpld_led_priv अणु
	काष्ठा led_classdev cdev;
	काष्ठा mlxcpld_param param;
पूर्ण;

#घोषणा cdev_to_priv(c)		container_of(c, काष्ठा mlxcpld_led_priv, cdev)

/**
 * mlxcpld_led_profile - प्रणाली LED profile (defined per प्रणाली class):
 * @offset - offset क्रम LED access in CPLD device
 * @mask - mask क्रम LED access in CPLD device
 * @base_color - base color code
 * @brightness - शेष brightness setting (on/off)
 * @name - LED name
**/
काष्ठा mlxcpld_led_profile अणु
	u8 offset;
	u8 mask;
	u8 base_color;
	क्रमागत led_brightness brightness;
	स्थिर अक्षर *name;
पूर्ण;

/**
 * mlxcpld_led_pdata - प्रणाली LED निजी data
 * @pdev - platक्रमm device poपूर्णांकer
 * @pled - LED class device instance
 * @profile - प्रणाली configuration profile
 * @num_led_instances - number of LED instances
 * @lock - device access lock
**/
काष्ठा mlxcpld_led_pdata अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mlxcpld_led_priv *pled;
	काष्ठा mlxcpld_led_profile *profile;
	पूर्णांक num_led_instances;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा mlxcpld_led_pdata *mlxcpld_led;

/* Default profile fit the next Mellanox प्रणालीs:
 * "msx6710", "msx6720", "msb7700", "msn2700", "msx1410",
 * "msn2410", "msb7800", "msn2740"
 */
अटल काष्ठा mlxcpld_led_profile mlxcpld_led_शेष_profile[] = अणु
	अणु
		0x21, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:fan1:green",
	पूर्ण,
	अणु
		0x21, 0xf0, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:fan1:red",
	पूर्ण,
	अणु
		0x21, 0x0f, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:fan2:green",
	पूर्ण,
	अणु
		0x21, 0x0f, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:fan2:red",
	पूर्ण,
	अणु
		0x22, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:fan3:green",
	पूर्ण,
	अणु
		0x22, 0xf0, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:fan3:red",
	पूर्ण,
	अणु
		0x22, 0x0f, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:fan4:green",
	पूर्ण,
	अणु
		0x22, 0x0f, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:fan4:red",
	पूर्ण,
	अणु
		0x20, 0x0f, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:psu:green",
	पूर्ण,
	अणु
		0x20, 0x0f, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:psu:red",
	पूर्ण,
	अणु
		0x20, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:status:green",
	पूर्ण,
	अणु
		0x20, 0xf0, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:status:red",
	पूर्ण,
पूर्ण;

/* Profile fit the Mellanox प्रणालीs based on "msn2100" */
अटल काष्ठा mlxcpld_led_profile mlxcpld_led_msn2100_profile[] = अणु
	अणु
		0x21, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:fan:green",
	पूर्ण,
	अणु
		0x21, 0xf0, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:fan:red",
	पूर्ण,
	अणु
		0x23, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:psu1:green",
	पूर्ण,
	अणु
		0x23, 0xf0, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:psu1:red",
	पूर्ण,
	अणु
		0x23, 0x0f, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:psu2:green",
	पूर्ण,
	अणु
		0x23, 0x0f, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:psu2:red",
	पूर्ण,
	अणु
		0x20, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, 1,
		"mlxcpld:status:green",
	पूर्ण,
	अणु
		0x20, 0xf0, MLXCPLD_LED_RED_STATIC_ON, LED_OFF,
		"mlxcpld:status:red",
	पूर्ण,
	अणु
		0x24, 0xf0, MLXCPLD_LED_GREEN_STATIC_ON, LED_OFF,
		"mlxcpld:uid:blue",
	पूर्ण,
पूर्ण;

क्रमागत mlxcpld_led_platक्रमm_types अणु
	MLXCPLD_LED_PLATFORM_DEFAULT,
	MLXCPLD_LED_PLATFORM_MSN2100,
पूर्ण;

अटल स्थिर अक्षर *mlx_product_names[] = अणु
	"DEFAULT",
	"MSN2100",
पूर्ण;

अटल क्रमागत
mlxcpld_led_platक्रमm_types mlxcpld_led_platक्रमm_check_sys_type(व्योम)
अणु
	स्थिर अक्षर *mlx_product_name;
	पूर्णांक i;

	mlx_product_name = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (!mlx_product_name)
		वापस MLXCPLD_LED_PLATFORM_DEFAULT;

	क्रम (i = 1;  i < ARRAY_SIZE(mlx_product_names); i++) अणु
		अगर (म_माला(mlx_product_name, mlx_product_names[i]))
			वापस i;
	पूर्ण

	वापस MLXCPLD_LED_PLATFORM_DEFAULT;
पूर्ण

अटल व्योम mlxcpld_led_bus_access_func(u16 base, u8 offset, u8 rw_flag,
					u8 *data)
अणु
	u32 addr = base + offset;

	अगर (rw_flag == 0)
		outb(*data, addr);
	अन्यथा
		*data = inb(addr);
पूर्ण

अटल व्योम mlxcpld_led_store_hw(u8 mask, u8 off, u8 vset)
अणु
	u8 nib, val;

	/*
	 * Each LED is controlled through low or high nibble of the relevant
	 * CPLD रेजिस्टर. Register offset is specअगरied by off parameter.
	 * Parameter vset provides color code: 0x0 क्रम off, 0x5 क्रम solid red,
	 * 0x6 क्रम 3Hz blink red, 0xd क्रम solid green, 0xe क्रम 3Hz blink
	 * green.
	 * Parameter mask specअगरies which nibble is used क्रम specअगरic LED: mask
	 * 0xf0 - lower nibble is to be used (bits from 0 to 3), mask 0x0f -
	 * higher nibble (bits from 4 to 7).
	 */
	spin_lock(&mlxcpld_led->lock);
	mlxcpld_led_bus_access_func(MLXPLAT_CPLD_LPC_REG_BASE_ADRR, off, 1,
				    &val);
	nib = (mask == 0xf0) ? vset : (vset << 4);
	val = (val & mask) | nib;
	mlxcpld_led_bus_access_func(MLXPLAT_CPLD_LPC_REG_BASE_ADRR, off, 0,
				    &val);
	spin_unlock(&mlxcpld_led->lock);
पूर्ण

अटल व्योम mlxcpld_led_brightness_set(काष्ठा led_classdev *led,
				       क्रमागत led_brightness value)
अणु
	काष्ठा mlxcpld_led_priv *pled = cdev_to_priv(led);

	अगर (value) अणु
		mlxcpld_led_store_hw(pled->param.mask, pled->param.offset,
				     pled->param.base_color);
		वापस;
	पूर्ण

	mlxcpld_led_store_hw(pled->param.mask, pled->param.offset,
			     MLXCPLD_LED_IS_OFF);
पूर्ण

अटल पूर्णांक mlxcpld_led_blink_set(काष्ठा led_classdev *led,
				 अचिन्हित दीर्घ *delay_on,
				 अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा mlxcpld_led_priv *pled = cdev_to_priv(led);

	/*
	 * HW supports two types of blinking: full (6Hz) and half (3Hz).
	 * For delay on/off zero शेष setting 3Hz is used.
	 */
	अगर (!(*delay_on == 0 && *delay_off == 0) &&
	    !(*delay_on == MLXCPLD_LED_BLINK_3HZ &&
	      *delay_off == MLXCPLD_LED_BLINK_3HZ) &&
	    !(*delay_on == MLXCPLD_LED_BLINK_6HZ &&
	      *delay_off == MLXCPLD_LED_BLINK_6HZ))
		वापस -EINVAL;

	अगर (*delay_on == MLXCPLD_LED_BLINK_6HZ)
		mlxcpld_led_store_hw(pled->param.mask, pled->param.offset,
				     pled->param.base_color +
				     MLXCPLD_LED_OFFSET_FULL);
	अन्यथा
		mlxcpld_led_store_hw(pled->param.mask, pled->param.offset,
				     pled->param.base_color +
				     MLXCPLD_LED_OFFSET_HALF);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxcpld_led_config(काष्ठा device *dev,
			      काष्ठा mlxcpld_led_pdata *cpld)
अणु
	पूर्णांक i;
	पूर्णांक err;

	cpld->pled = devm_kसुस्मृति(dev,
				  cpld->num_led_instances,
				  माप(काष्ठा mlxcpld_led_priv),
				  GFP_KERNEL);
	अगर (!cpld->pled)
		वापस -ENOMEM;

	क्रम (i = 0; i < cpld->num_led_instances; i++) अणु
		cpld->pled[i].cdev.name = cpld->profile[i].name;
		cpld->pled[i].cdev.brightness = cpld->profile[i].brightness;
		cpld->pled[i].cdev.max_brightness = 1;
		cpld->pled[i].cdev.brightness_set = mlxcpld_led_brightness_set;
		cpld->pled[i].cdev.blink_set = mlxcpld_led_blink_set;
		cpld->pled[i].cdev.flags = LED_CORE_SUSPENDRESUME;
		err = devm_led_classdev_रेजिस्टर(dev, &cpld->pled[i].cdev);
		अगर (err)
			वापस err;

		cpld->pled[i].param.offset = mlxcpld_led->profile[i].offset;
		cpld->pled[i].param.mask = mlxcpld_led->profile[i].mask;
		cpld->pled[i].param.base_color =
					mlxcpld_led->profile[i].base_color;

		अगर (mlxcpld_led->profile[i].brightness)
			mlxcpld_led_brightness_set(&cpld->pled[i].cdev,
					mlxcpld_led->profile[i].brightness);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init mlxcpld_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत mlxcpld_led_platक्रमm_types mlxcpld_led_plat =
					mlxcpld_led_platक्रमm_check_sys_type();

	mlxcpld_led = devm_kzalloc(&pdev->dev, माप(*mlxcpld_led),
				   GFP_KERNEL);
	अगर (!mlxcpld_led)
		वापस -ENOMEM;

	mlxcpld_led->pdev = pdev;

	चयन (mlxcpld_led_plat) अणु
	हाल MLXCPLD_LED_PLATFORM_MSN2100:
		mlxcpld_led->profile = mlxcpld_led_msn2100_profile;
		mlxcpld_led->num_led_instances =
				ARRAY_SIZE(mlxcpld_led_msn2100_profile);
		अवरोध;

	शेष:
		mlxcpld_led->profile = mlxcpld_led_शेष_profile;
		mlxcpld_led->num_led_instances =
				ARRAY_SIZE(mlxcpld_led_शेष_profile);
		अवरोध;
	पूर्ण

	spin_lock_init(&mlxcpld_led->lock);

	वापस mlxcpld_led_config(&pdev->dev, mlxcpld_led);
पूर्ण

अटल काष्ठा platक्रमm_driver mlxcpld_led_driver = अणु
	.driver = अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mlxcpld_led_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	अगर (!dmi_match(DMI_CHASSIS_VENDOR, "Mellanox Technologies Ltd."))
		वापस -ENODEV;

	pdev = platक्रमm_device_रेजिस्टर_simple(KBUILD_MODNAME, -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		pr_err("Device allocation failed\n");
		वापस PTR_ERR(pdev);
	पूर्ण

	err = platक्रमm_driver_probe(&mlxcpld_led_driver, mlxcpld_led_probe);
	अगर (err) अणु
		pr_err("Probe platform driver failed\n");
		platक्रमm_device_unरेजिस्टर(pdev);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास mlxcpld_led_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(mlxcpld_led->pdev);
	platक्रमm_driver_unरेजिस्टर(&mlxcpld_led_driver);
पूर्ण

module_init(mlxcpld_led_init);
module_निकास(mlxcpld_led_निकास);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox board LED driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:leds_mlxcpld");
