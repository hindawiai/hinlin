<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007,2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: John Rigby <jrigby@मुक्तscale.com>
 *
 * Description:
 * MPC512x Shared code
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/fsl-diu-fb.h>
#समावेश <linux/memblock.h>
#समावेश <sysdev/fsl_soc.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpc5121.h>
#समावेश <यंत्र/mpc52xx_psc.h>

#समावेश "mpc512x.h"

अटल काष्ठा mpc512x_reset_module __iomem *reset_module_base;

अटल व्योम __init mpc512x_restart_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर अक्षर *reset_compat;

	reset_compat = mpc512x_select_reset_compat();
	np = of_find_compatible_node(शून्य, शून्य, reset_compat);
	अगर (!np)
		वापस;

	reset_module_base = of_iomap(np, 0);
	of_node_put(np);
पूर्ण

व्योम __noवापस mpc512x_restart(अक्षर *cmd)
अणु
	अगर (reset_module_base) अणु
		/* Enable software reset "RSTE" */
		out_be32(&reset_module_base->rpr, 0x52535445);
		/* Set software hard reset */
		out_be32(&reset_module_base->rcr, 0x2);
	पूर्ण अन्यथा अणु
		pr_err("Restart module not mapped.\n");
	पूर्ण
	क्रम (;;)
		;
पूर्ण

काष्ठा fsl_diu_shared_fb अणु
	u8		gamma[0x300];	/* 32-bit aligned! */
	काष्ठा diu_ad	ad0;		/* 32-bit aligned! */
	phys_addr_t	fb_phys;
	माप_प्रकार		fb_len;
	bool		in_use;
पूर्ण;

/* receives a pixel घड़ी spec in pico seconds, adjusts the DIU घड़ी rate */
अटल व्योम mpc512x_set_pixel_घड़ी(अचिन्हित पूर्णांक pixघड़ी)
अणु
	काष्ठा device_node *np;
	काष्ठा clk *clk_diu;
	अचिन्हित दीर्घ epsilon, minpixघड़ी, maxpixघड़ी;
	अचिन्हित दीर्घ offset, want, got, delta;

	/* lookup and enable the DIU घड़ी */
	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-diu");
	अगर (!np) अणु
		pr_err("Could not find DIU device tree node.\n");
		वापस;
	पूर्ण
	clk_diu = of_clk_get(np, 0);
	अगर (IS_ERR(clk_diu)) अणु
		/* backwards compat with device trees that lack घड़ी specs */
		clk_diu = clk_get_sys(np->name, "ipg");
	पूर्ण
	of_node_put(np);
	अगर (IS_ERR(clk_diu)) अणु
		pr_err("Could not lookup DIU clock.\n");
		वापस;
	पूर्ण
	अगर (clk_prepare_enable(clk_diu)) अणु
		pr_err("Could not enable DIU clock.\n");
		वापस;
	पूर्ण

	/*
	 * convert the picoseconds spec पूर्णांकo the desired घड़ी rate,
	 * determine the acceptable घड़ी range क्रम the monitor (+/- 5%),
	 * करो the calculation in steps to aव्योम पूर्णांकeger overflow
	 */
	pr_debug("DIU pixclock in ps - %u\n", pixघड़ी);
	pixघड़ी = (1000000000 / pixघड़ी) * 1000;
	pr_debug("DIU pixclock freq  - %u\n", pixघड़ी);
	epsilon = pixघड़ी / 20; /* pixघड़ी * 0.05 */
	pr_debug("DIU deviation      - %lu\n", epsilon);
	minpixघड़ी = pixघड़ी - epsilon;
	maxpixघड़ी = pixघड़ी + epsilon;
	pr_debug("DIU minpixclock    - %lu\n", minpixघड़ी);
	pr_debug("DIU maxpixclock    - %lu\n", maxpixघड़ी);

	/*
	 * check whether the DIU supports the desired pixel घड़ी
	 *
	 * - simply request the desired घड़ी and see what the
	 *   platक्रमm's घड़ी driver will make of it, assuming that it
	 *   will setup the best approximation of the requested value
	 * - try other candidate frequencies in the order of decreasing
	 *   preference (i.e. with increasing distance from the desired
	 *   pixel घड़ी, and checking the lower frequency beक्रमe the
	 *   higher frequency to not overload the hardware) until the
	 *   first match is found -- any potential subsequent match
	 *   would only be as good as the क्रमmer match or typically
	 *   would be less preferrable
	 *
	 * the offset increment of pixelघड़ी भागided by 64 is an
	 * arbitrary choice -- it's simple to calculate, in the typical
	 * हाल we expect the first check to succeed alपढ़ोy, in the
	 * worst हाल seven frequencies get tested (the exact center and
	 * three more values each to the left and to the right) beक्रमe
	 * the 5% tolerance winकरोw is exceeded, resulting in fast enough
	 * execution yet high enough probability of finding a suitable
	 * value, जबतक the error rate will be in the order of single
	 * percents
	 */
	क्रम (offset = 0; offset <= epsilon; offset += pixघड़ी / 64) अणु
		want = pixघड़ी - offset;
		pr_debug("DIU checking clock - %lu\n", want);
		clk_set_rate(clk_diu, want);
		got = clk_get_rate(clk_diu);
		delta = असल(pixघड़ी - got);
		अगर (delta < epsilon)
			अवरोध;
		अगर (!offset)
			जारी;
		want = pixघड़ी + offset;
		pr_debug("DIU checking clock - %lu\n", want);
		clk_set_rate(clk_diu, want);
		got = clk_get_rate(clk_diu);
		delta = असल(pixघड़ी - got);
		अगर (delta < epsilon)
			अवरोध;
	पूर्ण
	अगर (offset <= epsilon) अणु
		pr_debug("DIU clock accepted - %lu\n", want);
		pr_debug("DIU pixclock want %u, got %lu, delta %lu, eps %lu\n",
			 pixघड़ी, got, delta, epsilon);
		वापस;
	पूर्ण
	pr_warn("DIU pixclock auto search unsuccessful\n");

	/*
	 * what is the most appropriate action to take when the search
	 * क्रम an available pixel घड़ी which is acceptable to the
	 * monitor has failed?  disable the DIU (घड़ी) or just provide
	 * a "best effort"?  we go with the latter
	 */
	pr_warn("DIU pixclock best effort fallback (backend's choice)\n");
	clk_set_rate(clk_diu, pixघड़ी);
	got = clk_get_rate(clk_diu);
	delta = असल(pixघड़ी - got);
	pr_debug("DIU pixclock want %u, got %lu, delta %lu, eps %lu\n",
		 pixघड़ी, got, delta, epsilon);
पूर्ण

अटल क्रमागत fsl_diu_monitor_port
mpc512x_valid_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	वापस FSL_DIU_PORT_DVI;
पूर्ण

अटल काष्ठा fsl_diu_shared_fb __attribute__ ((__aligned__(8))) diu_shared_fb;

अटल अंतरभूत व्योम mpc512x_मुक्त_booपंचांगem(काष्ठा page *page)
अणु
	BUG_ON(PageTail(page));
	BUG_ON(page_ref_count(page) > 1);
	मुक्त_reserved_page(page);
पूर्ण

अटल व्योम mpc512x_release_booपंचांगem(व्योम)
अणु
	अचिन्हित दीर्घ addr = diu_shared_fb.fb_phys & PAGE_MASK;
	अचिन्हित दीर्घ size = diu_shared_fb.fb_len;
	अचिन्हित दीर्घ start, end;

	अगर (diu_shared_fb.in_use) अणु
		start = PFN_UP(addr);
		end = PFN_DOWN(addr + size);

		क्रम (; start < end; start++)
			mpc512x_मुक्त_booपंचांगem(pfn_to_page(start));

		diu_shared_fb.in_use = false;
	पूर्ण
	diu_ops.release_booपंचांगem	= शून्य;
पूर्ण

/*
 * Check अगर DIU was pre-initialized. If so, perक्रमm steps
 * needed to जारी displaying through the whole boot process.
 * Move area descriptor and gamma table अन्यथाwhere, they are
 * destroyed by booपंचांगem allocator otherwise. The frame buffer
 * address range will be reserved in setup_arch() after booपंचांगem
 * allocator is up.
 */
अटल व्योम __init mpc512x_init_diu(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा diu __iomem *diu_reg;
	phys_addr_t desc;
	व्योम __iomem *vaddr;
	अचिन्हित दीर्घ mode, pix_fmt, res, bpp;
	अचिन्हित दीर्घ dst;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-diu");
	अगर (!np) अणु
		pr_err("No DIU node\n");
		वापस;
	पूर्ण

	diu_reg = of_iomap(np, 0);
	of_node_put(np);
	अगर (!diu_reg) अणु
		pr_err("Can't map DIU\n");
		वापस;
	पूर्ण

	mode = in_be32(&diu_reg->diu_mode);
	अगर (mode == MFB_MODE0) अणु
		pr_info("%s: DIU OFF\n", __func__);
		जाओ out;
	पूर्ण

	desc = in_be32(&diu_reg->desc[0]);
	vaddr = ioremap(desc, माप(काष्ठा diu_ad));
	अगर (!vaddr) अणु
		pr_err("Can't map DIU area desc.\n");
		जाओ out;
	पूर्ण
	स_नकल(&diu_shared_fb.ad0, vaddr, माप(काष्ठा diu_ad));
	/* flush fb area descriptor */
	dst = (अचिन्हित दीर्घ)&diu_shared_fb.ad0;
	flush_dcache_range(dst, dst + माप(काष्ठा diu_ad) - 1);

	res = in_be32(&diu_reg->disp_size);
	pix_fmt = in_le32(vaddr);
	bpp = ((pix_fmt >> 16) & 0x3) + 1;
	diu_shared_fb.fb_phys = in_le32(vaddr + 4);
	diu_shared_fb.fb_len = ((res & 0xfff0000) >> 16) * (res & 0xfff) * bpp;
	diu_shared_fb.in_use = true;
	iounmap(vaddr);

	desc = in_be32(&diu_reg->gamma);
	vaddr = ioremap(desc, माप(diu_shared_fb.gamma));
	अगर (!vaddr) अणु
		pr_err("Can't map DIU area desc.\n");
		diu_shared_fb.in_use = false;
		जाओ out;
	पूर्ण
	स_नकल(&diu_shared_fb.gamma, vaddr, माप(diu_shared_fb.gamma));
	/* flush gamma table */
	dst = (अचिन्हित दीर्घ)&diu_shared_fb.gamma;
	flush_dcache_range(dst, dst + माप(diu_shared_fb.gamma) - 1);

	iounmap(vaddr);
	out_be32(&diu_reg->gamma, virt_to_phys(&diu_shared_fb.gamma));
	out_be32(&diu_reg->desc[1], 0);
	out_be32(&diu_reg->desc[2], 0);
	out_be32(&diu_reg->desc[0], virt_to_phys(&diu_shared_fb.ad0));

out:
	iounmap(diu_reg);
पूर्ण

अटल व्योम __init mpc512x_setup_diu(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * We करो not allocate and configure new area क्रम biपंचांगap buffer
	 * because it would requere copying biपंचांगap data (splash image)
	 * and so negatively affect boot समय. Instead we reserve the
	 * alपढ़ोy configured frame buffer area so that it won't be
	 * destroyed. The starting address of the area to reserve and
	 * also it's length is passed to memblock_reserve(). It will be
	 * मुक्तd later on first खोलो of fbdev, when splash image is not
	 * needed any more.
	 */
	अगर (diu_shared_fb.in_use) अणु
		ret = memblock_reserve(diu_shared_fb.fb_phys,
				       diu_shared_fb.fb_len);
		अगर (ret) अणु
			pr_err("%s: reserve bootmem failed\n", __func__);
			diu_shared_fb.in_use = false;
		पूर्ण
	पूर्ण

	diu_ops.set_pixel_घड़ी		= mpc512x_set_pixel_घड़ी;
	diu_ops.valid_monitor_port	= mpc512x_valid_monitor_port;
	diu_ops.release_booपंचांगem		= mpc512x_release_booपंचांगem;
पूर्ण

व्योम __init mpc512x_init_IRQ(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-ipic");
	अगर (!np)
		वापस;

	ipic_init(np, 0);
	of_node_put(np);

	/*
	 * Initialize the शेष पूर्णांकerrupt mapping priorities,
	 * in हाल the boot rom changed something on us.
	 */
	ipic_set_शेष_priority();
पूर्ण

/*
 * Nodes to करो bus probe on, soc and localbus
 */
अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc5121-immr", पूर्ण,
	अणु .compatible = "fsl,mpc5121-localbus", पूर्ण,
	अणु .compatible = "fsl,mpc5121-mbx", पूर्ण,
	अणु .compatible = "fsl,mpc5121-nfc", पूर्ण,
	अणु .compatible = "fsl,mpc5121-sram", पूर्ण,
	अणु .compatible = "fsl,mpc5121-pci", पूर्ण,
	अणु .compatible = "gpio-leds", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init mpc512x_declare_of_platक्रमm_devices(व्योम)
अणु
	अगर (of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य))
		prपूर्णांकk(KERN_ERR __खाता__ ": "
			"Error while probing of_platform bus\n");
पूर्ण

#घोषणा DEFAULT_FIFO_SIZE 16

स्थिर अक्षर *mpc512x_select_psc_compat(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,mpc5121"))
		वापस "fsl,mpc5121-psc";

	अगर (of_machine_is_compatible("fsl,mpc5125"))
		वापस "fsl,mpc5125-psc";

	वापस शून्य;
पूर्ण

स्थिर अक्षर *mpc512x_select_reset_compat(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,mpc5121"))
		वापस "fsl,mpc5121-reset";

	अगर (of_machine_is_compatible("fsl,mpc5125"))
		वापस "fsl,mpc5125-reset";

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक __init get_fअगरo_size(काष्ठा device_node *np,
					 अक्षर *prop_name)
अणु
	स्थिर अचिन्हित पूर्णांक *fp;

	fp = of_get_property(np, prop_name, शून्य);
	अगर (fp)
		वापस *fp;

	pr_warn("no %s property in %pOF node, defaulting to %d\n",
		prop_name, np, DEFAULT_FIFO_SIZE);

	वापस DEFAULT_FIFO_SIZE;
पूर्ण

#घोषणा FIFOC(_base) ((काष्ठा mpc512x_psc_fअगरo __iomem *) \
		    ((u32)(_base) + माप(काष्ठा mpc52xx_psc)))

/* Init PSC FIFO space क्रम TX and RX slices */
अटल व्योम __init mpc512x_psc_fअगरo_init(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *psc;
	अचिन्हित पूर्णांक tx_fअगरo_size;
	अचिन्हित पूर्णांक rx_fअगरo_size;
	स्थिर अक्षर *psc_compat;
	पूर्णांक fअगरobase = 0; /* current fअगरo address in 32 bit words */

	psc_compat = mpc512x_select_psc_compat();
	अगर (!psc_compat) अणु
		pr_err("%s: no compatible devices found\n", __func__);
		वापस;
	पूर्ण

	क्रम_each_compatible_node(np, शून्य, psc_compat) अणु
		tx_fअगरo_size = get_fअगरo_size(np, "fsl,tx-fifo-size");
		rx_fअगरo_size = get_fअगरo_size(np, "fsl,rx-fifo-size");

		/* size in रेजिस्टर is in 4 byte units */
		tx_fअगरo_size /= 4;
		rx_fअगरo_size /= 4;
		अगर (!tx_fअगरo_size)
			tx_fअगरo_size = 1;
		अगर (!rx_fअगरo_size)
			rx_fअगरo_size = 1;

		psc = of_iomap(np, 0);
		अगर (!psc) अणु
			pr_err("%s: Can't map %pOF device\n",
				__func__, np);
			जारी;
		पूर्ण

		/* FIFO space is 4KiB, check अगर requested size is available */
		अगर ((fअगरobase + tx_fअगरo_size + rx_fअगरo_size) > 0x1000) अणु
			pr_err("%s: no fifo space available for %pOF\n",
				__func__, np);
			iounmap(psc);
			/*
			 * chances are that another device requests less
			 * fअगरo space, so we जारी.
			 */
			जारी;
		पूर्ण

		/* set tx and rx fअगरo size रेजिस्टरs */
		out_be32(&FIFOC(psc)->txsz, (fअगरobase << 16) | tx_fअगरo_size);
		fअगरobase += tx_fअगरo_size;
		out_be32(&FIFOC(psc)->rxsz, (fअगरobase << 16) | rx_fअगरo_size);
		fअगरobase += rx_fअगरo_size;

		/* reset and enable the slices */
		out_be32(&FIFOC(psc)->txcmd, 0x80);
		out_be32(&FIFOC(psc)->txcmd, 0x01);
		out_be32(&FIFOC(psc)->rxcmd, 0x80);
		out_be32(&FIFOC(psc)->rxcmd, 0x01);

		iounmap(psc);
	पूर्ण
पूर्ण

व्योम __init mpc512x_init_early(व्योम)
अणु
	mpc512x_restart_init();
	अगर (IS_ENABLED(CONFIG_FB_FSL_DIU))
		mpc512x_init_diu();
पूर्ण

व्योम __init mpc512x_init(व्योम)
अणु
	mpc5121_clk_init();
	mpc512x_declare_of_platक्रमm_devices();
	mpc512x_psc_fअगरo_init();
पूर्ण

व्योम __init mpc512x_setup_arch(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_FB_FSL_DIU))
		mpc512x_setup_diu();
पूर्ण

/**
 * mpc512x_cs_config - Setup chip select configuration
 * @cs: chip select number
 * @val: chip select configuration value
 *
 * Perक्रमm chip select configuration क्रम devices on LocalPlus Bus.
 * Intended to dynamically reconfigure the chip select parameters
 * क्रम configurable devices on the bus.
 */
पूर्णांक mpc512x_cs_config(अचिन्हित पूर्णांक cs, u32 val)
अणु
	अटल काष्ठा mpc512x_lpc __iomem *lpc;
	काष्ठा device_node *np;

	अगर (cs > 7)
		वापस -EINVAL;

	अगर (!lpc) अणु
		np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-lpc");
		lpc = of_iomap(np, 0);
		of_node_put(np);
		अगर (!lpc)
			वापस -ENOMEM;
	पूर्ण

	out_be32(&lpc->cs_cfg[cs], val);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpc512x_cs_config);
