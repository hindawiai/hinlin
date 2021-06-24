<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 National Instruments Corp.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>

#घोषणा NIWD_CONTROL	0x01
#घोषणा NIWD_COUNTER2	0x02
#घोषणा NIWD_COUNTER1	0x03
#घोषणा NIWD_COUNTER0	0x04
#घोषणा NIWD_SEED2	0x05
#घोषणा NIWD_SEED1	0x06
#घोषणा NIWD_SEED0	0x07

#घोषणा NIWD_IO_SIZE	0x08

#घोषणा NIWD_CONTROL_MODE		0x80
#घोषणा NIWD_CONTROL_PROC_RESET		0x20
#घोषणा NIWD_CONTROL_PET		0x10
#घोषणा NIWD_CONTROL_RUNNING		0x08
#घोषणा NIWD_CONTROL_CAPTURECOUNTER	0x04
#घोषणा NIWD_CONTROL_RESET		0x02
#घोषणा NIWD_CONTROL_ALARM		0x01

#घोषणा NIWD_PERIOD_NS		30720
#घोषणा NIWD_MIN_TIMEOUT	1
#घोषणा NIWD_MAX_TIMEOUT	515
#घोषणा NIWD_DEFAULT_TIMEOUT	60

#घोषणा NIWD_NAME		"ni903x_wdt"

काष्ठा ni903x_wdt अणु
	काष्ठा device *dev;
	u16 io_base;
	काष्ठा watchकरोg_device wdd;
पूर्ण;

अटल अचिन्हित पूर्णांक समयout;
module_param(समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(समयout,
		 "Watchdog timeout in seconds. (default="
		 __MODULE_STRING(NIWD_DEFAULT_TIMEOUT) ")");

अटल पूर्णांक nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(nowayout,
		 "Watchdog cannot be stopped once started (default="
		 __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल व्योम ni903x_start(काष्ठा ni903x_wdt *wdt)
अणु
	u8 control = inb(wdt->io_base + NIWD_CONTROL);

	outb(control | NIWD_CONTROL_RESET, wdt->io_base + NIWD_CONTROL);
	outb(control | NIWD_CONTROL_PET, wdt->io_base + NIWD_CONTROL);
पूर्ण

अटल पूर्णांक ni903x_wdd_set_समयout(काष्ठा watchकरोg_device *wdd,
				  अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा ni903x_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u32 counter = समयout * (1000000000 / NIWD_PERIOD_NS);

	outb(((0x00FF0000 & counter) >> 16), wdt->io_base + NIWD_SEED2);
	outb(((0x0000FF00 & counter) >> 8), wdt->io_base + NIWD_SEED1);
	outb((0x000000FF & counter), wdt->io_base + NIWD_SEED0);

	wdd->समयout = समयout;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ni903x_wdd_get_समयleft(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ni903x_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u8 control, counter0, counter1, counter2;
	u32 counter;

	control = inb(wdt->io_base + NIWD_CONTROL);
	control |= NIWD_CONTROL_CAPTURECOUNTER;
	outb(control, wdt->io_base + NIWD_CONTROL);

	counter2 = inb(wdt->io_base + NIWD_COUNTER2);
	counter1 = inb(wdt->io_base + NIWD_COUNTER1);
	counter0 = inb(wdt->io_base + NIWD_COUNTER0);

	counter = (counter2 << 16) | (counter1 << 8) | counter0;

	वापस counter / (1000000000 / NIWD_PERIOD_NS);
पूर्ण

अटल पूर्णांक ni903x_wdd_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ni903x_wdt *wdt = watchकरोg_get_drvdata(wdd);
	u8 control;

	control = inb(wdt->io_base + NIWD_CONTROL);
	outb(control | NIWD_CONTROL_PET, wdt->io_base + NIWD_CONTROL);

	वापस 0;
पूर्ण

अटल पूर्णांक ni903x_wdd_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ni903x_wdt *wdt = watchकरोg_get_drvdata(wdd);

	outb(NIWD_CONTROL_RESET | NIWD_CONTROL_PROC_RESET,
	     wdt->io_base + NIWD_CONTROL);

	ni903x_wdd_set_समयout(wdd, wdd->समयout);
	ni903x_start(wdt);

	वापस 0;
पूर्ण

अटल पूर्णांक ni903x_wdd_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा ni903x_wdt *wdt = watchकरोg_get_drvdata(wdd);

	outb(NIWD_CONTROL_RESET, wdt->io_base + NIWD_CONTROL);

	वापस 0;
पूर्ण

अटल acpi_status ni903x_resources(काष्ठा acpi_resource *res, व्योम *data)
अणु
	काष्ठा ni903x_wdt *wdt = data;
	u16 io_size;

	चयन (res->type) अणु
	हाल ACPI_RESOURCE_TYPE_IO:
		अगर (wdt->io_base != 0) अणु
			dev_err(wdt->dev, "too many IO resources\n");
			वापस AE_ERROR;
		पूर्ण

		wdt->io_base = res->data.io.minimum;
		io_size = res->data.io.address_length;

		अगर (io_size < NIWD_IO_SIZE) अणु
			dev_err(wdt->dev, "memory region too small\n");
			वापस AE_ERROR;
		पूर्ण

		अगर (!devm_request_region(wdt->dev, wdt->io_base, io_size,
					 NIWD_NAME)) अणु
			dev_err(wdt->dev, "failed to get memory region\n");
			वापस AE_ERROR;
		पूर्ण

		वापस AE_OK;

	हाल ACPI_RESOURCE_TYPE_END_TAG:
	शेष:
		/* Ignore unsupported resources, e.g. IRQ */
		वापस AE_OK;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info ni903x_wdd_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "NI Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ni903x_wdd_ops = अणु
	.owner = THIS_MODULE,
	.start = ni903x_wdd_start,
	.stop = ni903x_wdd_stop,
	.ping = ni903x_wdd_ping,
	.set_समयout = ni903x_wdd_set_समयout,
	.get_समयleft = ni903x_wdd_get_समयleft,
पूर्ण;

अटल पूर्णांक ni903x_acpi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा device *dev = &device->dev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा ni903x_wdt *wdt;
	acpi_status status;
	पूर्णांक ret;

	wdt = devm_kzalloc(dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	device->driver_data = wdt;
	wdt->dev = dev;

	status = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
				     ni903x_resources, wdt);
	अगर (ACPI_FAILURE(status) || wdt->io_base == 0) अणु
		dev_err(dev, "failed to get resources\n");
		वापस -ENODEV;
	पूर्ण

	wdd = &wdt->wdd;
	wdd->info = &ni903x_wdd_info;
	wdd->ops = &ni903x_wdd_ops;
	wdd->min_समयout = NIWD_MIN_TIMEOUT;
	wdd->max_समयout = NIWD_MAX_TIMEOUT;
	wdd->समयout = NIWD_DEFAULT_TIMEOUT;
	wdd->parent = dev;
	watchकरोg_set_drvdata(wdd, wdt);
	watchकरोg_set_nowayout(wdd, nowayout);
	watchकरोg_init_समयout(wdd, समयout, dev);

	ret = watchकरोg_रेजिस्टर_device(wdd);
	अगर (ret)
		वापस ret;

	/* Switch from boot mode to user mode */
	outb(NIWD_CONTROL_RESET | NIWD_CONTROL_MODE,
	     wdt->io_base + NIWD_CONTROL);

	dev_dbg(dev, "io_base=0x%04X, timeout=%d, nowayout=%d\n",
		wdt->io_base, समयout, nowayout);

	वापस 0;
पूर्ण

अटल पूर्णांक ni903x_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा ni903x_wdt *wdt = acpi_driver_data(device);

	ni903x_wdd_stop(&wdt->wdd);
	watchकरोg_unरेजिस्टर_device(&wdt->wdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ni903x_device_ids[] = अणु
	अणु"NIC775C", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ni903x_device_ids);

अटल काष्ठा acpi_driver ni903x_acpi_driver = अणु
	.name = NIWD_NAME,
	.ids = ni903x_device_ids,
	.ops = अणु
		.add = ni903x_acpi_add,
		.हटाओ = ni903x_acpi_हटाओ,
	पूर्ण,
पूर्ण;

module_acpi_driver(ni903x_acpi_driver);

MODULE_DESCRIPTION("NI 903x Watchdog");
MODULE_AUTHOR("Jeff Westfahl <jeff.westfahl@ni.com>");
MODULE_AUTHOR("Kyle Roeschley <kyle.roeschley@ni.com>");
MODULE_LICENSE("GPL");
