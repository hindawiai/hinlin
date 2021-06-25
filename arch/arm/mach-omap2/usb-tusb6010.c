<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/usb-tusb6010.c
 *
 * Copyright (C) 2006 Nokia Corporation
 */

#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_data/usb-omap.h>

#समावेश <linux/usb/musb.h>

#समावेश "gpmc.h"

अटल u8		async_cs, sync_cs;
अटल अचिन्हित		refclk_psec;

अटल काष्ठा gpmc_settings tusb_async = अणु
	.रुको_on_पढ़ो	= true,
	.रुको_on_ग_लिखो	= true,
	.device_width	= GPMC_DEVWIDTH_16BIT,
	.mux_add_data	= GPMC_MUX_AD,
पूर्ण;

अटल काष्ठा gpmc_settings tusb_sync = अणु
	.burst_पढ़ो	= true,
	.burst_ग_लिखो	= true,
	.sync_पढ़ो	= true,
	.sync_ग_लिखो	= true,
	.रुको_on_पढ़ो	= true,
	.रुको_on_ग_लिखो	= true,
	.burst_len	= GPMC_BURST_16,
	.device_width	= GPMC_DEVWIDTH_16BIT,
	.mux_add_data	= GPMC_MUX_AD,
पूर्ण;

/* NOTE:  timings are from tusb 6010 datasheet Rev 1.8, 12-Sept 2006 */

अटल पूर्णांक tusb_set_async_mode(अचिन्हित sysclk_ps)
अणु
	काष्ठा gpmc_device_timings dev_t;
	काष्ठा gpmc_timings	t;
	अचिन्हित		t_acsnh_advnh = sysclk_ps + 3000;

	स_रखो(&dev_t, 0, माप(dev_t));

	dev_t.t_ceasu = 8 * 1000;
	dev_t.t_avdasu = t_acsnh_advnh - 7000;
	dev_t.t_ce_avd = 1000;
	dev_t.t_avdp_r = t_acsnh_advnh;
	dev_t.t_oeasu = t_acsnh_advnh + 1000;
	dev_t.t_oe = 300;
	dev_t.t_cez_r = 7000;
	dev_t.t_cez_w = dev_t.t_cez_r;
	dev_t.t_avdp_w = t_acsnh_advnh;
	dev_t.t_weasu = t_acsnh_advnh + 1000;
	dev_t.t_wpl = 300;
	dev_t.cyc_aavdh_we = 1;

	gpmc_calc_timings(&t, &tusb_async, &dev_t);

	वापस gpmc_cs_set_timings(async_cs, &t, &tusb_async);
पूर्ण

अटल पूर्णांक tusb_set_sync_mode(अचिन्हित sysclk_ps)
अणु
	काष्ठा gpmc_device_timings dev_t;
	काष्ठा gpmc_timings	t;
	अचिन्हित		t_scsnh_advnh = sysclk_ps + 3000;

	स_रखो(&dev_t, 0, माप(dev_t));

	dev_t.clk = 11100;
	dev_t.t_bacc = 1000;
	dev_t.t_ces = 1000;
	dev_t.t_ceasu = 8 * 1000;
	dev_t.t_avdasu = t_scsnh_advnh - 7000;
	dev_t.t_ce_avd = 1000;
	dev_t.t_avdp_r = t_scsnh_advnh;
	dev_t.cyc_aavdh_oe = 3;
	dev_t.cyc_oe = 5;
	dev_t.t_ce_rdyz = 7000;
	dev_t.t_avdp_w = t_scsnh_advnh;
	dev_t.cyc_aavdh_we = 3;
	dev_t.cyc_wpl = 6;

	gpmc_calc_timings(&t, &tusb_sync, &dev_t);

	वापस gpmc_cs_set_timings(sync_cs, &t, &tusb_sync);
पूर्ण

/* tusb driver calls this when it changes the chip's घड़ीing */
पूर्णांक tusb6010_platक्रमm_reसमय(अचिन्हित is_refclk)
अणु
	अटल स्थिर अक्षर	error[] =
		KERN_ERR "tusb6010 %s retime error %d\n";

	अचिन्हित	sysclk_ps;
	पूर्णांक		status;

	अगर (!refclk_psec)
		वापस -ENODEV;

	sysclk_ps = is_refclk ? refclk_psec : TUSB6010_OSCCLK_60;

	status = tusb_set_async_mode(sysclk_ps);
	अगर (status < 0) अणु
		prपूर्णांकk(error, "async", status);
		जाओ करोne;
	पूर्ण
	status = tusb_set_sync_mode(sysclk_ps);
	अगर (status < 0)
		prपूर्णांकk(error, "sync", status);
करोne:
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(tusb6010_platक्रमm_reसमय);

अटल काष्ठा resource tusb_resources[] = अणु
	/* Order is signअगरicant!  The start/end fields
	 * are updated during setup..
	 */
	अणु /* Asynchronous access */
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु /* Synchronous access */
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु /* IRQ */
		.name	= "mc",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 tusb_dmamask = ~(u32)0;

अटल काष्ठा platक्रमm_device tusb_device = अणु
	.name		= "musb-tusb",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &tusb_dmamask,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(tusb_resources),
	.resource	= tusb_resources,
पूर्ण;


/* this may be called only from board-*.c setup code */
पूर्णांक __init
tusb6010_setup_पूर्णांकerface(काष्ठा musb_hdrc_platक्रमm_data *data,
		अचिन्हित ps_refclk, अचिन्हित रुकोpin,
		अचिन्हित async, अचिन्हित sync,
		अचिन्हित irq, अचिन्हित dmachan)
अणु
	पूर्णांक		status;
	अटल अक्षर	error[] __initdata =
		KERN_ERR "tusb6010 init error %d, %d\n";

	/* ASYNC region, primarily क्रम PIO */
	status = gpmc_cs_request(async, SZ_16M, (अचिन्हित दीर्घ *)
				&tusb_resources[0].start);
	अगर (status < 0) अणु
		prपूर्णांकk(error, 1, status);
		वापस status;
	पूर्ण
	tusb_resources[0].end = tusb_resources[0].start + 0x9ff;
	tusb_async.रुको_pin = रुकोpin;
	async_cs = async;

	status = gpmc_cs_program_settings(async_cs, &tusb_async);
	अगर (status < 0)
		वापस status;

	/* SYNC region, primarily क्रम DMA */
	status = gpmc_cs_request(sync, SZ_16M, (अचिन्हित दीर्घ *)
				&tusb_resources[1].start);
	अगर (status < 0) अणु
		prपूर्णांकk(error, 2, status);
		वापस status;
	पूर्ण
	tusb_resources[1].end = tusb_resources[1].start + 0x9ff;
	tusb_sync.रुको_pin = रुकोpin;
	sync_cs = sync;

	status = gpmc_cs_program_settings(sync_cs, &tusb_sync);
	अगर (status < 0)
		वापस status;

	/* IRQ */
	status = gpio_request_one(irq, GPIOF_IN, "TUSB6010 irq");
	अगर (status < 0) अणु
		prपूर्णांकk(error, 3, status);
		वापस status;
	पूर्ण
	tusb_resources[2].start = gpio_to_irq(irq);

	/* set up memory timings ... can speed them up later */
	अगर (!ps_refclk) अणु
		prपूर्णांकk(error, 4, status);
		वापस -ENODEV;
	पूर्ण
	refclk_psec = ps_refclk;
	status = tusb6010_platक्रमm_reसमय(1);
	अगर (status < 0) अणु
		prपूर्णांकk(error, 5, status);
		वापस status;
	पूर्ण

	/* finish device setup ... */
	अगर (!data) अणु
		prपूर्णांकk(error, 6, status);
		वापस -ENODEV;
	पूर्ण
	tusb_device.dev.platक्रमm_data = data;

	/* so far so good ... रेजिस्टर the device */
	status = platक्रमm_device_रेजिस्टर(&tusb_device);
	अगर (status < 0) अणु
		prपूर्णांकk(error, 7, status);
		वापस status;
	पूर्ण
	वापस 0;
पूर्ण
