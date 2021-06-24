<शैली गुरु>
/*
 * drivers/leds/leds-apu.c
 * Copyright (C) 2017 Alan Mizrahi, alan at mizrahi करोt com करोt ve
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा APU1_FCH_ACPI_MMIO_BASE 0xFED80000
#घोषणा APU1_FCH_GPIO_BASE      (APU1_FCH_ACPI_MMIO_BASE + 0x01BD)
#घोषणा APU1_LEDON              0x08
#घोषणा APU1_LEDOFF             0xC8
#घोषणा APU1_NUM_GPIO           3
#घोषणा APU1_IOSIZE             माप(u8)

/* LED access parameters */
काष्ठा apu_param अणु
	व्योम __iomem *addr; /* क्रम ioपढ़ो/ioग_लिखो */
पूर्ण;

/* LED निजी data */
काष्ठा apu_led_priv अणु
	काष्ठा led_classdev cdev;
	काष्ठा apu_param param;
पूर्ण;
#घोषणा cdev_to_priv(c) container_of(c, काष्ठा apu_led_priv, cdev)

/* LED profile */
काष्ठा apu_led_profile अणु
	स्थिर अक्षर *name;
	क्रमागत led_brightness brightness;
	अचिन्हित दीर्घ offset; /* क्रम devm_ioremap */
पूर्ण;

काष्ठा apu_led_pdata अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा apu_led_priv *pled;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा apu_led_pdata *apu_led;

अटल स्थिर काष्ठा apu_led_profile apu1_led_profile[] = अणु
	अणु "apu:green:1", LED_ON,  APU1_FCH_GPIO_BASE + 0 * APU1_IOSIZE पूर्ण,
	अणु "apu:green:2", LED_OFF, APU1_FCH_GPIO_BASE + 1 * APU1_IOSIZE पूर्ण,
	अणु "apu:green:3", LED_OFF, APU1_FCH_GPIO_BASE + 2 * APU1_IOSIZE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id apu_led_dmi_table[] __initस्थिर = अणु
	/* PC Engines APU with factory bios "SageBios_PCEngines_APU-45" */
	अणु
		.ident = "apu",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_PRODUCT_NAME, "APU")
		पूर्ण
	पूर्ण,
	/* PC Engines APU with "Mainline" bios >= 4.6.8 */
	अणु
		.ident = "apu",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PC Engines"),
			DMI_MATCH(DMI_PRODUCT_NAME, "apu1")
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, apu_led_dmi_table);

अटल व्योम apu1_led_brightness_set(काष्ठा led_classdev *led, क्रमागत led_brightness value)
अणु
	काष्ठा apu_led_priv *pled = cdev_to_priv(led);

	spin_lock(&apu_led->lock);
	ioग_लिखो8(value ? APU1_LEDON : APU1_LEDOFF, pled->param.addr);
	spin_unlock(&apu_led->lock);
पूर्ण

अटल पूर्णांक apu_led_config(काष्ठा device *dev, काष्ठा apu_led_pdata *apuld)
अणु
	पूर्णांक i;
	पूर्णांक err;

	apu_led->pled = devm_kसुस्मृति(dev,
		ARRAY_SIZE(apu1_led_profile), माप(काष्ठा apu_led_priv),
		GFP_KERNEL);

	अगर (!apu_led->pled)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(apu1_led_profile); i++) अणु
		काष्ठा apu_led_priv *pled = &apu_led->pled[i];
		काष्ठा led_classdev *led_cdev = &pled->cdev;

		led_cdev->name = apu1_led_profile[i].name;
		led_cdev->brightness = apu1_led_profile[i].brightness;
		led_cdev->max_brightness = 1;
		led_cdev->flags = LED_CORE_SUSPENDRESUME;
		led_cdev->brightness_set = apu1_led_brightness_set;

		pled->param.addr = devm_ioremap(dev,
				apu1_led_profile[i].offset, APU1_IOSIZE);
		अगर (!pled->param.addr) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण

		err = led_classdev_रेजिस्टर(dev, led_cdev);
		अगर (err)
			जाओ error;

		apu1_led_brightness_set(led_cdev, apu1_led_profile[i].brightness);
	पूर्ण

	वापस 0;

error:
	जबतक (i-- > 0)
		led_classdev_unरेजिस्टर(&apu_led->pled[i].cdev);

	वापस err;
पूर्ण

अटल पूर्णांक __init apu_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	apu_led = devm_kzalloc(&pdev->dev, माप(*apu_led), GFP_KERNEL);

	अगर (!apu_led)
		वापस -ENOMEM;

	apu_led->pdev = pdev;

	spin_lock_init(&apu_led->lock);
	वापस apu_led_config(&pdev->dev, apu_led);
पूर्ण

अटल काष्ठा platक्रमm_driver apu_led_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init apu_led_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	अगर (!(dmi_match(DMI_SYS_VENDOR, "PC Engines") &&
	      (dmi_match(DMI_PRODUCT_NAME, "APU") || dmi_match(DMI_PRODUCT_NAME, "apu1")))) अणु
		pr_err("No PC Engines APUv1 board detected. For APUv2,3 support, enable CONFIG_PCENGINES_APU2\n");
		वापस -ENODEV;
	पूर्ण

	pdev = platक्रमm_device_रेजिस्टर_simple(KBUILD_MODNAME, -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		pr_err("Device allocation failed\n");
		वापस PTR_ERR(pdev);
	पूर्ण

	err = platक्रमm_driver_probe(&apu_led_driver, apu_led_probe);
	अगर (err) अणु
		pr_err("Probe platform driver failed\n");
		platक्रमm_device_unरेजिस्टर(pdev);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास apu_led_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(apu1_led_profile); i++)
		led_classdev_unरेजिस्टर(&apu_led->pled[i].cdev);

	platक्रमm_device_unरेजिस्टर(apu_led->pdev);
	platक्रमm_driver_unरेजिस्टर(&apu_led_driver);
पूर्ण

module_init(apu_led_init);
module_निकास(apu_led_निकास);

MODULE_AUTHOR("Alan Mizrahi");
MODULE_DESCRIPTION("PC Engines APU1 front LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:leds_apu");
