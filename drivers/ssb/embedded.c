<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Embedded प्रणालीs support code
 *
 * Copyright 2005-2008, Broadcom Corporation
 * Copyright 2006-2008, Michael Buesch <m@bues.ch>
 * Copyright 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_embedded.h>
#समावेश <linux/ssb/ssb_driver_pci.h>
#समावेश <linux/ssb/ssb_driver_gige.h>
#समावेश <linux/pci.h>


पूर्णांक ssb_watchकरोg_समयr_set(काष्ठा ssb_bus *bus, u32 ticks)
अणु
	अगर (ssb_chipco_available(&bus->chipco)) अणु
		ssb_chipco_watchकरोg_समयr_set(&bus->chipco, ticks);
		वापस 0;
	पूर्ण
	अगर (ssb_extअगर_available(&bus->extअगर)) अणु
		ssb_extअगर_watchकरोg_समयr_set(&bus->extअगर, ticks);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(ssb_watchकरोg_समयr_set);

पूर्णांक ssb_watchकरोg_रेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	काष्ठा bcm47xx_wdt wdt = अणुपूर्ण;
	काष्ठा platक्रमm_device *pdev;

	अगर (ssb_chipco_available(&bus->chipco)) अणु
		wdt.driver_data = &bus->chipco;
		wdt.समयr_set = ssb_chipco_watchकरोg_समयr_set_wdt;
		wdt.समयr_set_ms = ssb_chipco_watchकरोg_समयr_set_ms;
		wdt.max_समयr_ms = bus->chipco.max_समयr_ms;
	पूर्ण अन्यथा अगर (ssb_extअगर_available(&bus->extअगर)) अणु
		wdt.driver_data = &bus->extअगर;
		wdt.समयr_set = ssb_extअगर_watchकरोg_समयr_set_wdt;
		wdt.समयr_set_ms = ssb_extअगर_watchकरोg_समयr_set_ms;
		wdt.max_समयr_ms = SSB_EXTIF_WATCHDOG_MAX_TIMER_MS;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "bcm47xx-wdt",
					     bus->busnumber, &wdt,
					     माप(wdt));
	अगर (IS_ERR(pdev)) अणु
		pr_debug("can not register watchdog device, err: %li\n",
			 PTR_ERR(pdev));
		वापस PTR_ERR(pdev);
	पूर्ण

	bus->watchकरोg = pdev;
	वापस 0;
पूर्ण

u32 ssb_gpio_in(काष्ठा ssb_bus *bus, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	अगर (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_in(&bus->chipco, mask);
	अन्यथा अगर (ssb_extअगर_available(&bus->extअगर))
		res = ssb_extअगर_gpio_in(&bus->extअगर, mask);
	अन्यथा
		WARN_ON(1);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_gpio_in);

u32 ssb_gpio_out(काष्ठा ssb_bus *bus, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	अगर (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_out(&bus->chipco, mask, value);
	अन्यथा अगर (ssb_extअगर_available(&bus->extअगर))
		res = ssb_extअगर_gpio_out(&bus->extअगर, mask, value);
	अन्यथा
		WARN_ON(1);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_gpio_out);

u32 ssb_gpio_outen(काष्ठा ssb_bus *bus, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	अगर (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_outen(&bus->chipco, mask, value);
	अन्यथा अगर (ssb_extअगर_available(&bus->extअगर))
		res = ssb_extअगर_gpio_outen(&bus->extअगर, mask, value);
	अन्यथा
		WARN_ON(1);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_gpio_outen);

u32 ssb_gpio_control(काष्ठा ssb_bus *bus, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	अगर (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_control(&bus->chipco, mask, value);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_gpio_control);

u32 ssb_gpio_पूर्णांकmask(काष्ठा ssb_bus *bus, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	अगर (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_पूर्णांकmask(&bus->chipco, mask, value);
	अन्यथा अगर (ssb_extअगर_available(&bus->extअगर))
		res = ssb_extअगर_gpio_पूर्णांकmask(&bus->extअगर, mask, value);
	अन्यथा
		WARN_ON(1);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_gpio_पूर्णांकmask);

u32 ssb_gpio_polarity(काष्ठा ssb_bus *bus, u32 mask, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	अगर (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_polarity(&bus->chipco, mask, value);
	अन्यथा अगर (ssb_extअगर_available(&bus->extअगर))
		res = ssb_extअगर_gpio_polarity(&bus->extअगर, mask, value);
	अन्यथा
		WARN_ON(1);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(ssb_gpio_polarity);

#अगर_घोषित CONFIG_SSB_DRIVER_GIGE
अटल पूर्णांक gige_pci_init_callback(काष्ठा ssb_bus *bus, अचिन्हित दीर्घ data)
अणु
	काष्ठा pci_dev *pdev = (काष्ठा pci_dev *)data;
	काष्ठा ssb_device *dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक res;

	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		dev = &(bus->devices[i]);
		अगर (dev->id.coreid != SSB_DEV_ETHERNET_GBIT)
			जारी;
		अगर (!dev->dev ||
		    !dev->dev->driver ||
		    !device_is_रेजिस्टरed(dev->dev))
			जारी;
		res = ssb_gige_pcibios_plat_dev_init(dev, pdev);
		अगर (res >= 0)
			वापस res;
	पूर्ण

	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_DRIVER_GIGE */

पूर्णांक ssb_pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err;

	err = ssb_pcicore_plat_dev_init(dev);
	अगर (!err)
		वापस 0;
#अगर_घोषित CONFIG_SSB_DRIVER_GIGE
	err = ssb_क्रम_each_bus_call((अचिन्हित दीर्घ)dev, gige_pci_init_callback);
	अगर (err >= 0)
		वापस err;
#पूर्ण_अगर
	/* This is not a PCI device on any SSB device. */

	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_SSB_DRIVER_GIGE
अटल पूर्णांक gige_map_irq_callback(काष्ठा ssb_bus *bus, अचिन्हित दीर्घ data)
अणु
	स्थिर काष्ठा pci_dev *pdev = (स्थिर काष्ठा pci_dev *)data;
	काष्ठा ssb_device *dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक res;

	क्रम (i = 0; i < bus->nr_devices; i++) अणु
		dev = &(bus->devices[i]);
		अगर (dev->id.coreid != SSB_DEV_ETHERNET_GBIT)
			जारी;
		अगर (!dev->dev ||
		    !dev->dev->driver ||
		    !device_is_रेजिस्टरed(dev->dev))
			जारी;
		res = ssb_gige_map_irq(dev, pdev);
		अगर (res >= 0)
			वापस res;
	पूर्ण

	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_DRIVER_GIGE */

पूर्णांक ssb_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक res;

	/* Check अगर this PCI device is a device on a SSB bus or device
	 * and वापस the IRQ number क्रम it. */

	res = ssb_pcicore_pcibios_map_irq(dev, slot, pin);
	अगर (res >= 0)
		वापस res;
#अगर_घोषित CONFIG_SSB_DRIVER_GIGE
	res = ssb_क्रम_each_bus_call((अचिन्हित दीर्घ)dev, gige_map_irq_callback);
	अगर (res >= 0)
		वापस res;
#पूर्ण_अगर
	/* This is not a PCI device on any SSB device. */

	वापस -ENODEV;
पूर्ण
