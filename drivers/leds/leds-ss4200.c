<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SS4200-E Hardware API
 * Copyright (c) 2009, Intel Corporation.
 * Copyright IBM Corporation, 2009
 *
 * Author: Dave Hansen <dave@sr71.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

MODULE_AUTHOR("Rodney Girod <rgirod@confocus.com>, Dave Hansen <dave@sr71.net>");
MODULE_DESCRIPTION("Intel NAS/Home Server ICH7 GPIO Driver");
MODULE_LICENSE("GPL");

/*
 * ICH7 LPC/GPIO PCI Config रेजिस्टर offsets
 */
#घोषणा PMBASE		0x040
#घोषणा GPIO_BASE	0x048
#घोषणा GPIO_CTRL	0x04c
#घोषणा GPIO_EN		0x010

/*
 * The ICH7 GPIO रेजिस्टर block is 64 bytes in size.
 */
#घोषणा ICH7_GPIO_SIZE	64

/*
 * Define रेजिस्टर offsets within the ICH7 रेजिस्टर block.
 */
#घोषणा GPIO_USE_SEL	0x000
#घोषणा GP_IO_SEL	0x004
#घोषणा GP_LVL		0x00c
#घोषणा GPO_BLINK	0x018
#घोषणा GPI_INV		0x030
#घोषणा GPIO_USE_SEL2	0x034
#घोषणा GP_IO_SEL2	0x038
#घोषणा GP_LVL2		0x03c

/*
 * PCI ID of the Intel ICH7 LPC Device within which the GPIO block lives.
 */
अटल स्थिर काष्ठा pci_device_id ich7_lpc_pci_id[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_1) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_30) पूर्ण,
	अणु पूर्ण /* शून्य entry */
पूर्ण;

MODULE_DEVICE_TABLE(pci, ich7_lpc_pci_id);

अटल पूर्णांक __init ss4200_led_dmi_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("detected '%s'\n", id->ident);
	वापस 1;
पूर्ण

अटल bool nodetect;
module_param_named(nodetect, nodetect, bool, 0);
MODULE_PARM_DESC(nodetect, "Skip DMI-based hardware detection");

/*
 * काष्ठा nas_led_whitelist - List of known good models
 *
 * Contains the known good models this driver is compatible with.
 * When adding a new model try to be as strict as possible. This
 * makes it possible to keep the false positives (the model is
 * detected as working, but in reality it is not) as low as
 * possible.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id nas_led_whitelist[] __initस्थिर = अणु
	अणु
		.callback = ss4200_led_dmi_callback,
		.ident = "Intel SS4200-E",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SS4200-E"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "1.00.00")
		पूर्ण
	पूर्ण,
	अणु
		/*
		 * FUJITSU SIEMENS SCALEO Home Server/SS4200-E
		 * BIOS V090L 12/19/2007
		 */
		.callback = ss4200_led_dmi_callback,
		.ident = "Fujitsu Siemens SCALEO Home Server",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SCALEO Home Server"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "1.00.00")
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Base I/O address asचिन्हित to the Power Management रेजिस्टर block
 */
अटल u32 g_pm_io_base;

/*
 * Base I/O address asचिन्हित to the ICH7 GPIO रेजिस्टर block
 */
अटल u32 nas_gpio_io_base;

/*
 * When we successfully रेजिस्टर a region, we are वापसed a resource.
 * We use these to identअगरy which regions we need to release on our way
 * back out.
 */
अटल काष्ठा resource *gp_gpio_resource;

काष्ठा nasgpio_led अणु
	अक्षर *name;
	u32 gpio_bit;
	काष्ठा led_classdev led_cdev;
पूर्ण;

/*
 * gpio_bit(s) are the ICH7 GPIO bit assignments
 */
अटल काष्ठा nasgpio_led nasgpio_leds[] = अणु
	अणु .name = "hdd1:blue:sata",	.gpio_bit = 0 पूर्ण,
	अणु .name = "hdd1:amber:sata",	.gpio_bit = 1 पूर्ण,
	अणु .name = "hdd2:blue:sata",	.gpio_bit = 2 पूर्ण,
	अणु .name = "hdd2:amber:sata",	.gpio_bit = 3 पूर्ण,
	अणु .name = "hdd3:blue:sata",	.gpio_bit = 4 पूर्ण,
	अणु .name = "hdd3:amber:sata",	.gpio_bit = 5 पूर्ण,
	अणु .name = "hdd4:blue:sata",	.gpio_bit = 6 पूर्ण,
	अणु .name = "hdd4:amber:sata",	.gpio_bit = 7 पूर्ण,
	अणु .name = "power:blue:power",	.gpio_bit = 27पूर्ण,
	अणु .name = "power:amber:power",  .gpio_bit = 28पूर्ण,
पूर्ण;

#घोषणा NAS_RECOVERY	0x00000400	/* GPIO10 */

अटल काष्ठा nasgpio_led *
led_classdev_to_nasgpio_led(काष्ठा led_classdev *led_cdev)
अणु
	वापस container_of(led_cdev, काष्ठा nasgpio_led, led_cdev);
पूर्ण

अटल काष्ठा nasgpio_led *get_led_named(अक्षर *name)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++) अणु
		अगर (म_भेद(nasgpio_leds[i].name, name))
			जारी;
		वापस &nasgpio_leds[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * This protects access to the gpio ports.
 */
अटल DEFINE_SPINLOCK(nasgpio_gpio_lock);

/*
 * There are two gpio ports, one क्रम blinking and the other
 * क्रम घातer.  @port tells us अगर we're करोing blinking or
 * घातer control.
 *
 * Caller must hold nasgpio_gpio_lock
 */
अटल व्योम __nasgpio_led_set_attr(काष्ठा led_classdev *led_cdev,
				   u32 port, u32 value)
अणु
	काष्ठा nasgpio_led *led = led_classdev_to_nasgpio_led(led_cdev);
	u32 gpio_out;

	gpio_out = inl(nas_gpio_io_base + port);
	अगर (value)
		gpio_out |= (1<<led->gpio_bit);
	अन्यथा
		gpio_out &= ~(1<<led->gpio_bit);

	outl(gpio_out, nas_gpio_io_base + port);
पूर्ण

अटल व्योम nasgpio_led_set_attr(काष्ठा led_classdev *led_cdev,
				 u32 port, u32 value)
अणु
	spin_lock(&nasgpio_gpio_lock);
	__nasgpio_led_set_attr(led_cdev, port, value);
	spin_unlock(&nasgpio_gpio_lock);
पूर्ण

अटल u32 nasgpio_led_get_attr(काष्ठा led_classdev *led_cdev, u32 port)
अणु
	काष्ठा nasgpio_led *led = led_classdev_to_nasgpio_led(led_cdev);
	u32 gpio_in;

	spin_lock(&nasgpio_gpio_lock);
	gpio_in = inl(nas_gpio_io_base + port);
	spin_unlock(&nasgpio_gpio_lock);
	अगर (gpio_in & (1<<led->gpio_bit))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * There is actual brightness control in the hardware,
 * but it is via smbus commands and not implemented
 * in this driver.
 */
अटल व्योम nasgpio_led_set_brightness(काष्ठा led_classdev *led_cdev,
				       क्रमागत led_brightness brightness)
अणु
	u32 setting = 0;
	अगर (brightness >= LED_HALF)
		setting = 1;
	/*
	 * Hold the lock across both operations.  This ensures
	 * consistency so that both the "turn off blinking"
	 * and "turn light off" operations complete as a set.
	 */
	spin_lock(&nasgpio_gpio_lock);
	/*
	 * LED class करोcumentation asks that past blink state
	 * be disabled when brightness is turned to zero.
	 */
	अगर (brightness == 0)
		__nasgpio_led_set_attr(led_cdev, GPO_BLINK, 0);
	__nasgpio_led_set_attr(led_cdev, GP_LVL, setting);
	spin_unlock(&nasgpio_gpio_lock);
पूर्ण

अटल पूर्णांक nasgpio_led_set_blink(काष्ठा led_classdev *led_cdev,
				 अचिन्हित दीर्घ *delay_on,
				 अचिन्हित दीर्घ *delay_off)
अणु
	u32 setting = 1;
	अगर (!(*delay_on == 0 && *delay_off == 0) &&
	    !(*delay_on == 500 && *delay_off == 500))
		वापस -EINVAL;
	/*
	 * These are very approximate.
	 */
	*delay_on = 500;
	*delay_off = 500;

	nasgpio_led_set_attr(led_cdev, GPO_BLINK, setting);

	वापस 0;
पूर्ण


/*
 * Initialize the ICH7 GPIO रेजिस्टरs क्रम NAS usage.  The BIOS should have
 * alपढ़ोy taken care of this, but we will करो so in a non deकाष्ठाive manner
 * so that we have what we need whether the BIOS did it or not.
 */
अटल पूर्णांक ich7_gpio_init(काष्ठा device *dev)
अणु
	पूर्णांक i;
	u32 config_data = 0;
	u32 all_nas_led = 0;

	क्रम (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++)
		all_nas_led |= (1<<nasgpio_leds[i].gpio_bit);

	spin_lock(&nasgpio_gpio_lock);
	/*
	 * We need to enable all of the GPIO lines used by the NAS box,
	 * so we will पढ़ो the current Use Selection and add our usage
	 * to it.  This should be benign with regard to the original
	 * BIOS configuration.
	 */
	config_data = inl(nas_gpio_io_base + GPIO_USE_SEL);
	dev_dbg(dev, ": Data read from GPIO_USE_SEL = 0x%08x\n", config_data);
	config_data |= all_nas_led + NAS_RECOVERY;
	outl(config_data, nas_gpio_io_base + GPIO_USE_SEL);
	config_data = inl(nas_gpio_io_base + GPIO_USE_SEL);
	dev_dbg(dev, ": GPIO_USE_SEL = 0x%08x\n\n", config_data);

	/*
	 * The LED GPIO outमाला_दो need to be configured क्रम output, so we
	 * will ensure that all LED lines are cleared क्रम output and the
	 * RECOVERY line पढ़ोy क्रम input.  This too should be benign with
	 * regard to BIOS configuration.
	 */
	config_data = inl(nas_gpio_io_base + GP_IO_SEL);
	dev_dbg(dev, ": Data read from GP_IO_SEL = 0x%08x\n",
					config_data);
	config_data &= ~all_nas_led;
	config_data |= NAS_RECOVERY;
	outl(config_data, nas_gpio_io_base + GP_IO_SEL);
	config_data = inl(nas_gpio_io_base + GP_IO_SEL);
	dev_dbg(dev, ": GP_IO_SEL = 0x%08x\n", config_data);

	/*
	 * In our final प्रणाली, the BIOS will initialize the state of all
	 * of the LEDs.  For now, we turn them all off (or Low).
	 */
	config_data = inl(nas_gpio_io_base + GP_LVL);
	dev_dbg(dev, ": Data read from GP_LVL = 0x%08x\n", config_data);
	/*
	 * In our final प्रणाली, the BIOS will initialize the blink state of all
	 * of the LEDs.  For now, we turn blink off क्रम all of them.
	 */
	config_data = inl(nas_gpio_io_base + GPO_BLINK);
	dev_dbg(dev, ": Data read from GPO_BLINK = 0x%08x\n", config_data);

	/*
	 * At this moment, I am unsure अगर anything needs to happen with GPI_INV
	 */
	config_data = inl(nas_gpio_io_base + GPI_INV);
	dev_dbg(dev, ": Data read from GPI_INV = 0x%08x\n", config_data);

	spin_unlock(&nasgpio_gpio_lock);
	वापस 0;
पूर्ण

अटल व्योम ich7_lpc_cleanup(काष्ठा device *dev)
अणु
	/*
	 * If we were given exclusive use of the GPIO
	 * I/O Address range, we must वापस it.
	 */
	अगर (gp_gpio_resource) अणु
		dev_dbg(dev, ": Releasing GPIO I/O addresses\n");
		release_region(nas_gpio_io_base, ICH7_GPIO_SIZE);
		gp_gpio_resource = शून्य;
	पूर्ण
पूर्ण

/*
 * The OS has determined that the LPC of the Intel ICH7 Southbridge is present
 * so we can retrive the required operational inक्रमmation and prepare the GPIO.
 */
अटल काष्ठा pci_dev *nas_gpio_pci_dev;
अटल पूर्णांक ich7_lpc_probe(काष्ठा pci_dev *dev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक status;
	u32 gc = 0;

	status = pci_enable_device(dev);
	अगर (status) अणु
		dev_err(&dev->dev, "pci_enable_device failed\n");
		वापस -EIO;
	पूर्ण

	nas_gpio_pci_dev = dev;
	status = pci_पढ़ो_config_dword(dev, PMBASE, &g_pm_io_base);
	अगर (status)
		जाओ out;
	g_pm_io_base &= 0x00000ff80;

	status = pci_पढ़ो_config_dword(dev, GPIO_CTRL, &gc);
	अगर (!(GPIO_EN & gc)) अणु
		status = -EEXIST;
		dev_info(&dev->dev,
			   "ERROR: The LPC GPIO Block has not been enabled.\n");
		जाओ out;
	पूर्ण

	status = pci_पढ़ो_config_dword(dev, GPIO_BASE, &nas_gpio_io_base);
	अगर (0 > status) अणु
		dev_info(&dev->dev, "Unable to read GPIOBASE.\n");
		जाओ out;
	पूर्ण
	dev_dbg(&dev->dev, ": GPIOBASE = 0x%08x\n", nas_gpio_io_base);
	nas_gpio_io_base &= 0x00000ffc0;

	/*
	 * Insure that we have exclusive access to the GPIO I/O address range.
	 */
	gp_gpio_resource = request_region(nas_gpio_io_base, ICH7_GPIO_SIZE,
					  KBUILD_MODNAME);
	अगर (शून्य == gp_gpio_resource) अणु
		dev_info(&dev->dev,
			 "ERROR Unable to register GPIO I/O addresses.\n");
		status = -1;
		जाओ out;
	पूर्ण

	/*
	 * Initialize the GPIO क्रम NAS/Home Server Use
	 */
	ich7_gpio_init(&dev->dev);

out:
	अगर (status) अणु
		ich7_lpc_cleanup(&dev->dev);
		pci_disable_device(dev);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम ich7_lpc_हटाओ(काष्ठा pci_dev *dev)
अणु
	ich7_lpc_cleanup(&dev->dev);
	pci_disable_device(dev);
पूर्ण

/*
 * pci_driver काष्ठाure passed to the PCI modules
 */
अटल काष्ठा pci_driver nas_gpio_pci_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = ich7_lpc_pci_id,
	.probe = ich7_lpc_probe,
	.हटाओ = ich7_lpc_हटाओ,
पूर्ण;

अटल काष्ठा led_classdev *get_classdev_क्रम_led_nr(पूर्णांक nr)
अणु
	काष्ठा nasgpio_led *nas_led = &nasgpio_leds[nr];
	काष्ठा led_classdev *led = &nas_led->led_cdev;
	वापस led;
पूर्ण


अटल व्योम set_घातer_light_amber_noblink(व्योम)
अणु
	काष्ठा nasgpio_led *amber = get_led_named("power:amber:power");
	काष्ठा nasgpio_led *blue = get_led_named("power:blue:power");

	अगर (!amber || !blue)
		वापस;
	/*
	 * LED_OFF implies disabling future blinking
	 */
	pr_debug("setting blue off and amber on\n");

	nasgpio_led_set_brightness(&blue->led_cdev, LED_OFF);
	nasgpio_led_set_brightness(&amber->led_cdev, LED_FULL);
पूर्ण

अटल sमाप_प्रकार blink_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led = dev_get_drvdata(dev);
	पूर्णांक blinking = 0;
	अगर (nasgpio_led_get_attr(led, GPO_BLINK))
		blinking = 1;
	वापस प्र_लिखो(buf, "%u\n", blinking);
पूर्ण

अटल sमाप_प्रकार blink_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	काष्ठा led_classdev *led = dev_get_drvdata(dev);
	अचिन्हित दीर्घ blink_state;

	ret = kम_से_अदीर्घ(buf, 10, &blink_state);
	अगर (ret)
		वापस ret;

	nasgpio_led_set_attr(led, GPO_BLINK, blink_state);

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(blink);

अटल काष्ठा attribute *nasgpio_led_attrs[] = अणु
	&dev_attr_blink.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(nasgpio_led);

अटल पूर्णांक रेजिस्टर_nasgpio_led(पूर्णांक led_nr)
अणु
	काष्ठा nasgpio_led *nas_led = &nasgpio_leds[led_nr];
	काष्ठा led_classdev *led = get_classdev_क्रम_led_nr(led_nr);

	led->name = nas_led->name;
	led->brightness = LED_OFF;
	अगर (nasgpio_led_get_attr(led, GP_LVL))
		led->brightness = LED_FULL;
	led->brightness_set = nasgpio_led_set_brightness;
	led->blink_set = nasgpio_led_set_blink;
	led->groups = nasgpio_led_groups;

	वापस led_classdev_रेजिस्टर(&nas_gpio_pci_dev->dev, led);
पूर्ण

अटल व्योम unरेजिस्टर_nasgpio_led(पूर्णांक led_nr)
अणु
	काष्ठा led_classdev *led = get_classdev_क्रम_led_nr(led_nr);
	led_classdev_unरेजिस्टर(led);
पूर्ण
/*
 * module load/initialization
 */
अटल पूर्णांक __init nas_gpio_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक nr_devices = 0;

	nr_devices = dmi_check_प्रणाली(nas_led_whitelist);
	अगर (nodetect) अणु
		pr_info("skipping hardware autodetection\n");
		pr_info("Please send 'dmidecode' output to dave@sr71.net\n");
		nr_devices++;
	पूर्ण

	अगर (nr_devices <= 0) अणु
		pr_info("no LED devices found\n");
		वापस -ENODEV;
	पूर्ण

	pr_info("registering PCI driver\n");
	ret = pci_रेजिस्टर_driver(&nas_gpio_pci_driver);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++) अणु
		ret = रेजिस्टर_nasgpio_led(i);
		अगर (ret)
			जाओ out_err;
	पूर्ण
	/*
	 * When the प्रणाली घातers on, the BIOS leaves the घातer
	 * light blue and blinking.  This will turn it solid
	 * amber once the driver is loaded.
	 */
	set_घातer_light_amber_noblink();
	वापस 0;
out_err:
	क्रम (i--; i >= 0; i--)
		unरेजिस्टर_nasgpio_led(i);
	pci_unरेजिस्टर_driver(&nas_gpio_pci_driver);
	वापस ret;
पूर्ण

/*
 * module unload
 */
अटल व्योम __निकास nas_gpio_निकास(व्योम)
अणु
	पूर्णांक i;
	pr_info("Unregistering driver\n");
	क्रम (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++)
		unरेजिस्टर_nasgpio_led(i);
	pci_unरेजिस्टर_driver(&nas_gpio_pci_driver);
पूर्ण

module_init(nas_gpio_init);
module_निकास(nas_gpio_निकास);
