<शैली गुरु>
/*
 * Based on linux/arch/mips/txx9/rbtx4938/setup.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * 2003-2005 (c) MontaVista Software, Inc.
 * (C) Copyright TOSHIBA CORPORATION 2000-2001, 2004-2007
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/txx9/ndfmc.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/leds.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9पंचांगr.h>
#समावेश <यंत्र/txx9/dmac.h>
#अगर_घोषित CONFIG_CPU_TX49XX
#समावेश <यंत्र/txx9/tx4938.h>
#पूर्ण_अगर

/* EBUSC settings of TX4927, etc. */
काष्ठा resource txx9_ce_res[8];
अटल अक्षर txx9_ce_res_name[8][4];	/* "CEn" */

/* pcode, पूर्णांकernal रेजिस्टर */
अचिन्हित पूर्णांक txx9_pcode;
अक्षर txx9_pcode_str[8];
अटल काष्ठा resource txx9_reg_res = अणु
	.name = txx9_pcode_str,
	.flags = IORESOURCE_MEM,
पूर्ण;
व्योम __init
txx9_reg_res_init(अचिन्हित पूर्णांक pcode, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(txx9_ce_res); i++) अणु
		प्र_लिखो(txx9_ce_res_name[i], "CE%d", i);
		txx9_ce_res[i].flags = IORESOURCE_MEM;
		txx9_ce_res[i].name = txx9_ce_res_name[i];
	पूर्ण

	txx9_pcode = pcode;
	प्र_लिखो(txx9_pcode_str, "TX%x", pcode);
	अगर (base) अणु
		txx9_reg_res.start = base & 0xfffffffffULL;
		txx9_reg_res.end = (base & 0xfffffffffULL) + (size - 1);
		request_resource(&iomem_resource, &txx9_reg_res);
	पूर्ण
पूर्ण

/* घड़ीs */
अचिन्हित पूर्णांक txx9_master_घड़ी;
अचिन्हित पूर्णांक txx9_cpu_घड़ी;
अचिन्हित पूर्णांक txx9_gbus_घड़ी;

#अगर_घोषित CONFIG_CPU_TX39XX
/* करोn't enable by शेष - see errata */
पूर्णांक txx9_ccfg_toeon __initdata;
#अन्यथा
पूर्णांक txx9_ccfg_toeon __initdata = 1;
#पूर्ण_अगर

#घोषणा BOARD_VEC(board)	बाह्य काष्ठा txx9_board_vec board;
#समावेश <यंत्र/txx9/boards.h>
#अघोषित BOARD_VEC

काष्ठा txx9_board_vec *txx9_board_vec __initdata;
अटल अक्षर txx9_प्रणाली_type[32];

अटल काष्ठा txx9_board_vec *board_vecs[] __initdata = अणु
#घोषणा BOARD_VEC(board)	&board,
#समावेश <यंत्र/txx9/boards.h>
#अघोषित BOARD_VEC
पूर्ण;

अटल काष्ठा txx9_board_vec *__init find_board_byname(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	/* search board_vecs table */
	क्रम (i = 0; i < ARRAY_SIZE(board_vecs); i++) अणु
		अगर (म_माला(board_vecs[i]->प्रणाली, name))
			वापस board_vecs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __init prom_init_cmdline(व्योम)
अणु
	पूर्णांक argc;
	पूर्णांक *argv32;
	पूर्णांक i;			/* Always ignore the "-c" at argv[0] */

	अगर (fw_arg0 >= CKSEG0 || fw_arg1 < CKSEG0) अणु
		/*
		 * argc is not a valid number, or argv32 is not a valid
		 * poपूर्णांकer
		 */
		argc = 0;
		argv32 = शून्य;
	पूर्ण अन्यथा अणु
		argc = (पूर्णांक)fw_arg0;
		argv32 = (पूर्णांक *)fw_arg1;
	पूर्ण

	arcs_cmdline[0] = '\0';

	क्रम (i = 1; i < argc; i++) अणु
		अक्षर *str = (अक्षर *)(दीर्घ)argv32[i];
		अगर (i != 1)
			म_जोड़ो(arcs_cmdline, " ");
		अगर (म_अक्षर(str, ' ')) अणु
			म_जोड़ो(arcs_cmdline, "\"");
			म_जोड़ो(arcs_cmdline, str);
			म_जोड़ो(arcs_cmdline, "\"");
		पूर्ण अन्यथा
			म_जोड़ो(arcs_cmdline, str);
	पूर्ण
पूर्ण

अटल पूर्णांक txx9_ic_disable __initdata;
अटल पूर्णांक txx9_dc_disable __initdata;

#अगर defined(CONFIG_CPU_TX49XX)
/* flush all cache on very early stage (beक्रमe 4k_cache_init) */
अटल व्योम __init early_flush_dcache(व्योम)
अणु
	अचिन्हित पूर्णांक conf = पढ़ो_c0_config();
	अचिन्हित पूर्णांक dc_size = 1 << (12 + ((conf & CONF_DC) >> 6));
	अचिन्हित पूर्णांक linesz = 32;
	अचिन्हित दीर्घ addr, end;

	end = INDEX_BASE + dc_size / 4;
	/* 4way, waybit=0 */
	क्रम (addr = INDEX_BASE; addr < end; addr += linesz) अणु
		cache_op(Index_Writeback_Inv_D, addr | 0);
		cache_op(Index_Writeback_Inv_D, addr | 1);
		cache_op(Index_Writeback_Inv_D, addr | 2);
		cache_op(Index_Writeback_Inv_D, addr | 3);
	पूर्ण
पूर्ण

अटल व्योम __init txx9_cache_fixup(व्योम)
अणु
	अचिन्हित पूर्णांक conf;

	conf = पढ़ो_c0_config();
	/* flush and disable */
	अगर (txx9_ic_disable) अणु
		conf |= TX49_CONF_IC;
		ग_लिखो_c0_config(conf);
	पूर्ण
	अगर (txx9_dc_disable) अणु
		early_flush_dcache();
		conf |= TX49_CONF_DC;
		ग_लिखो_c0_config(conf);
	पूर्ण

	/* enable cache */
	conf = पढ़ो_c0_config();
	अगर (!txx9_ic_disable)
		conf &= ~TX49_CONF_IC;
	अगर (!txx9_dc_disable)
		conf &= ~TX49_CONF_DC;
	ग_लिखो_c0_config(conf);

	अगर (conf & TX49_CONF_IC)
		pr_info("TX49XX I-Cache disabled.\n");
	अगर (conf & TX49_CONF_DC)
		pr_info("TX49XX D-Cache disabled.\n");
पूर्ण
#या_अगर defined(CONFIG_CPU_TX39XX)
/* flush all cache on very early stage (beक्रमe tx39_cache_init) */
अटल व्योम __init early_flush_dcache(व्योम)
अणु
	अचिन्हित पूर्णांक conf = पढ़ो_c0_config();
	अचिन्हित पूर्णांक dc_size = 1 << (10 + ((conf & TX39_CONF_DCS_MASK) >>
					   TX39_CONF_DCS_SHIFT));
	अचिन्हित पूर्णांक linesz = 16;
	अचिन्हित दीर्घ addr, end;

	end = INDEX_BASE + dc_size / 2;
	/* 2way, waybit=0 */
	क्रम (addr = INDEX_BASE; addr < end; addr += linesz) अणु
		cache_op(Index_Writeback_Inv_D, addr | 0);
		cache_op(Index_Writeback_Inv_D, addr | 1);
	पूर्ण
पूर्ण

अटल व्योम __init txx9_cache_fixup(व्योम)
अणु
	अचिन्हित पूर्णांक conf;

	conf = पढ़ो_c0_config();
	/* flush and disable */
	अगर (txx9_ic_disable) अणु
		conf &= ~TX39_CONF_ICE;
		ग_लिखो_c0_config(conf);
	पूर्ण
	अगर (txx9_dc_disable) अणु
		early_flush_dcache();
		conf &= ~TX39_CONF_DCE;
		ग_लिखो_c0_config(conf);
	पूर्ण

	/* enable cache */
	conf = पढ़ो_c0_config();
	अगर (!txx9_ic_disable)
		conf |= TX39_CONF_ICE;
	अगर (!txx9_dc_disable)
		conf |= TX39_CONF_DCE;
	ग_लिखो_c0_config(conf);

	अगर (!(conf & TX39_CONF_ICE))
		pr_info("TX39XX I-Cache disabled.\n");
	अगर (!(conf & TX39_CONF_DCE))
		pr_info("TX39XX D-Cache disabled.\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम txx9_cache_fixup(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init preprocess_cmdline(व्योम)
अणु
	अटल अक्षर cmdline[COMMAND_LINE_SIZE] __initdata;
	अक्षर *s;

	म_नकल(cmdline, arcs_cmdline);
	s = cmdline;
	arcs_cmdline[0] = '\0';
	जबतक (s && *s) अणु
		अक्षर *str = strsep(&s, " ");
		अगर (म_भेदन(str, "board=", 6) == 0) अणु
			txx9_board_vec = find_board_byname(str + 6);
			जारी;
		पूर्ण अन्यथा अगर (म_भेदन(str, "masterclk=", 10) == 0) अणु
			अचिन्हित पूर्णांक val;
			अगर (kstrtouपूर्णांक(str + 10, 10, &val) == 0)
				txx9_master_घड़ी = val;
			जारी;
		पूर्ण अन्यथा अगर (म_भेद(str, "icdisable") == 0) अणु
			txx9_ic_disable = 1;
			जारी;
		पूर्ण अन्यथा अगर (म_भेद(str, "dcdisable") == 0) अणु
			txx9_dc_disable = 1;
			जारी;
		पूर्ण अन्यथा अगर (म_भेद(str, "toeoff") == 0) अणु
			txx9_ccfg_toeon = 0;
			जारी;
		पूर्ण अन्यथा अगर (म_भेद(str, "toeon") == 0) अणु
			txx9_ccfg_toeon = 1;
			जारी;
		पूर्ण
		अगर (arcs_cmdline[0])
			म_जोड़ो(arcs_cmdline, " ");
		म_जोड़ो(arcs_cmdline, str);
	पूर्ण

	txx9_cache_fixup();
पूर्ण

अटल व्योम __init select_board(व्योम)
अणु
	स्थिर अक्षर *envstr;

	/* first, determine by "board=" argument in preprocess_cmdline() */
	अगर (txx9_board_vec)
		वापस;
	/* next, determine by "board" envvar */
	envstr = prom_दो_पर्या("board");
	अगर (envstr) अणु
		txx9_board_vec = find_board_byname(envstr);
		अगर (txx9_board_vec)
			वापस;
	पूर्ण

	/* select "default" board */
#अगर_घोषित CONFIG_TOSHIBA_JMR3927
	txx9_board_vec = &jmr3927_vec;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_TX49XX
	चयन (TX4938_REV_PCODE()) अणु
#अगर_घोषित CONFIG_TOSHIBA_RBTX4927
	हाल 0x4927:
		txx9_board_vec = &rbtx4927_vec;
		अवरोध;
	हाल 0x4937:
		txx9_board_vec = &rbtx4937_vec;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TOSHIBA_RBTX4938
	हाल 0x4938:
		txx9_board_vec = &rbtx4938_vec;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TOSHIBA_RBTX4939
	हाल 0x4939:
		txx9_board_vec = &rbtx4939_vec;
		अवरोध;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	prom_init_cmdline();
	preprocess_cmdline();
	select_board();

	म_नकल(txx9_प्रणाली_type, txx9_board_vec->प्रणाली);

	txx9_board_vec->prom_init();
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस txx9_प्रणाली_type;
पूर्ण

स्थिर अक्षर *__init prom_दो_पर्या(स्थिर अक्षर *name)
अणु
	स्थिर s32 *str;

	अगर (fw_arg2 < CKSEG0)
		वापस शून्य;

	str = (स्थिर s32 *)fw_arg2;
	/* YAMON style ("name", "value" pairs) */
	जबतक (str[0] && str[1]) अणु
		अगर (!म_भेद((स्थिर अक्षर *)(अचिन्हित दीर्घ)str[0], name))
			वापस (स्थिर अक्षर *)(अचिन्हित दीर्घ)str[1];
		str += 2;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __noवापस txx9_machine_halt(व्योम)
अणु
	local_irq_disable();
	clear_c0_status(ST0_IM);
	जबतक (1) अणु
		अगर (cpu_रुको) अणु
			(*cpu_रुको)();
			अगर (cpu_has_counter) अणु
				/*
				 * Clear counter पूर्णांकerrupt जबतक it
				 * अवरोधs WAIT inकाष्ठाion even अगर
				 * masked.
				 */
				ग_लिखो_c0_compare(0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Watchकरोg support */
व्योम __init txx9_wdt_init(अचिन्हित दीर्घ base)
अणु
	काष्ठा resource res = अणु
		.start	= base,
		.end	= base + 0x100 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण;
	platक्रमm_device_रेजिस्टर_simple("txx9wdt", -1, &res, 1);
पूर्ण

व्योम txx9_wdt_now(अचिन्हित दीर्घ base)
अणु
	काष्ठा txx9_पंचांगr_reg __iomem *पंचांगrptr =
		ioremap(base, माप(काष्ठा txx9_पंचांगr_reg));
	/* disable watch करोg समयr */
	__raw_ग_लिखोl(TXx9_TMWTMR_WDIS | TXx9_TMWTMR_TWC, &पंचांगrptr->wपंचांगr);
	__raw_ग_लिखोl(0, &पंचांगrptr->tcr);
	/* kick watchकरोg */
	__raw_ग_लिखोl(TXx9_TMWTMR_TWIE, &पंचांगrptr->wपंचांगr);
	__raw_ग_लिखोl(1, &पंचांगrptr->cpra); /* immediate */
	__raw_ग_लिखोl(TXx9_TMTCR_TCE | TXx9_TMTCR_CCDE | TXx9_TMTCR_TMODE_WDOG,
		     &पंचांगrptr->tcr);
पूर्ण

/* SPI support */
व्योम __init txx9_spi_init(पूर्णांक busid, अचिन्हित दीर्घ base, पूर्णांक irq)
अणु
	काष्ठा resource res[] = अणु
		अणु
			.start	= base,
			.end	= base + 0x20 - 1,
			.flags	= IORESOURCE_MEM,
		पूर्ण, अणु
			.start	= irq,
			.flags	= IORESOURCE_IRQ,
		पूर्ण,
	पूर्ण;
	platक्रमm_device_रेजिस्टर_simple("spi_txx9", busid,
					res, ARRAY_SIZE(res));
पूर्ण

व्योम __init txx9_ethaddr_init(अचिन्हित पूर्णांक id, अचिन्हित अक्षर *ethaddr)
अणु
	काष्ठा platक्रमm_device *pdev =
		platक्रमm_device_alloc("tc35815-mac", id);
	अगर (!pdev ||
	    platक्रमm_device_add_data(pdev, ethaddr, 6) ||
	    platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
पूर्ण

व्योम __init txx9_sio_init(अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
			  अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक sclk, पूर्णांक nocts)
अणु
#अगर_घोषित CONFIG_SERIAL_TXX9
	काष्ठा uart_port req;

	स_रखो(&req, 0, माप(req));
	req.line = line;
	req.iotype = UPIO_MEM;
	req.membase = ioremap(baseaddr, 0x24);
	req.mapbase = baseaddr;
	req.irq = irq;
	अगर (!nocts)
		req.flags |= UPF_BUGGY_UART /*HAVE_CTS_LINE*/;
	अगर (sclk) अणु
		req.flags |= UPF_MAGIC_MULTIPLIER /*USE_SCLK*/;
		req.uartclk = sclk;
	पूर्ण अन्यथा
		req.uartclk = TXX9_IMCLK;
	early_serial_txx9_setup(&req);
#पूर्ण_अगर /* CONFIG_SERIAL_TXX9 */
पूर्ण

#अगर_घोषित CONFIG_EARLY_PRINTK
अटल व्योम null_prom_अक्षर_दो(अक्षर c)
अणु
पूर्ण
व्योम (*txx9_prom_अक्षर_दो)(अक्षर c) = null_prom_अक्षर_दो;

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	txx9_prom_अक्षर_दो(c);
पूर्ण

अटल व्योम __iomem *early_txx9_sio_port;

अटल व्योम early_txx9_sio_अक्षर_दो(अक्षर c)
अणु
#घोषणा TXX9_SICISR	0x0c
#घोषणा TXX9_SITFIFO	0x1c
#घोषणा TXX9_SICISR_TXALS	0x00000002
	जबतक (!(__raw_पढ़ोl(early_txx9_sio_port + TXX9_SICISR) &
		 TXX9_SICISR_TXALS))
		;
	__raw_ग_लिखोl(c, early_txx9_sio_port + TXX9_SITFIFO);
पूर्ण

व्योम __init txx9_sio_अक्षर_दो_init(अचिन्हित दीर्घ baseaddr)
अणु
	early_txx9_sio_port = ioremap(baseaddr, 0x24);
	txx9_prom_अक्षर_दो = early_txx9_sio_अक्षर_दो;
पूर्ण
#पूर्ण_अगर /* CONFIG_EARLY_PRINTK */

/* wrappers */
व्योम __init plat_mem_setup(व्योम)
अणु
	ioport_resource.start = 0;
	ioport_resource.end = ~0UL;	/* no limit */
	iomem_resource.start = 0;
	iomem_resource.end = ~0UL;	/* no limit */

	/* fallback restart/halt routines */
	_machine_restart = (व्योम (*)(अक्षर *))txx9_machine_halt;
	_machine_halt = txx9_machine_halt;
	pm_घातer_off = txx9_machine_halt;

#अगर_घोषित CONFIG_PCI
	pcibios_plat_setup = txx9_pcibios_setup;
#पूर्ण_अगर
	txx9_board_vec->mem_setup();
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	txx9_board_vec->irq_setup();
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_TX49XX
	mips_hpt_frequency = txx9_cpu_घड़ी / 2;
#पूर्ण_अगर
	txx9_board_vec->समय_init();
पूर्ण

अटल व्योम txx9_clk_init(व्योम)
अणु
	काष्ठा clk_hw *hw;
	पूर्णांक error;

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "gbus", शून्य, 0, txx9_gbus_घड़ी);
	अगर (IS_ERR(hw)) अणु
		error = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "imbus", "gbus", 0, 1, 2);
	error = clk_hw_रेजिस्टर_clkdev(hw, "imbus_clk", शून्य);
	अगर (error)
		जाओ fail;

#अगर_घोषित CONFIG_CPU_TX49XX
	अगर (TX4938_REV_PCODE() == 0x4938) अणु
		hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, "spi", "gbus", 0, 1, 4);
		error = clk_hw_रेजिस्टर_clkdev(hw, "spi-baseclk", शून्य);
		अगर (error)
			जाओ fail;
	पूर्ण
#पूर्ण_अगर

	वापस;

fail:
	pr_err("Failed to register clocks: %d\n", error);
पूर्ण

अटल पूर्णांक __init _txx9_arch_init(व्योम)
अणु
	txx9_clk_init();

	अगर (txx9_board_vec->arch_init)
		txx9_board_vec->arch_init();
	वापस 0;
पूर्ण
arch_initcall(_txx9_arch_init);

अटल पूर्णांक __init _txx9_device_init(व्योम)
अणु
	अगर (txx9_board_vec->device_init)
		txx9_board_vec->device_init();
	वापस 0;
पूर्ण
device_initcall(_txx9_device_init);

पूर्णांक (*txx9_irq_dispatch)(पूर्णांक pending);
यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	पूर्णांक pending = पढ़ो_c0_status() & पढ़ो_c0_cause() & ST0_IM;
	पूर्णांक irq = txx9_irq_dispatch(pending);

	अगर (likely(irq >= 0))
		करो_IRQ(irq);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

/* see include/यंत्र-mips/mach-tx39xx/mangle-port.h, क्रम example. */
#अगर_घोषित NEEDS_TXX9_SWIZZLE_ADDR_B
अटल अचिन्हित दीर्घ __swizzle_addr_none(अचिन्हित दीर्घ port)
अणु
	वापस port;
पूर्ण
अचिन्हित दीर्घ (*__swizzle_addr_b)(अचिन्हित दीर्घ port) = __swizzle_addr_none;
EXPORT_SYMBOL(__swizzle_addr_b);
#पूर्ण_अगर

#अगर_घोषित NEEDS_TXX9_IOSWABW
अटल u16 ioswabw_शेष(अस्थिर u16 *a, u16 x)
अणु
	वापस le16_to_cpu(x);
पूर्ण
अटल u16 __mem_ioswabw_शेष(अस्थिर u16 *a, u16 x)
अणु
	वापस x;
पूर्ण
u16 (*ioswabw)(अस्थिर u16 *a, u16 x) = ioswabw_शेष;
EXPORT_SYMBOL(ioswabw);
u16 (*__mem_ioswabw)(अस्थिर u16 *a, u16 x) = __mem_ioswabw_शेष;
EXPORT_SYMBOL(__mem_ioswabw);
#पूर्ण_अगर

व्योम __init txx9_physmap_flash_init(पूर्णांक no, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ size,
				    स्थिर काष्ठा physmap_flash_data *pdata)
अणु
#अगर IS_ENABLED(CONFIG_MTD_PHYSMAP)
	काष्ठा resource res = अणु
		.start = addr,
		.end = addr + size - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev;
	अटल काष्ठा mtd_partition parts[2];
	काष्ठा physmap_flash_data pdata_part;

	/* If this area contained boot area, make separate partition */
	अगर (pdata->nr_parts == 0 && !pdata->parts &&
	    addr < 0x1fc00000 && addr + size > 0x1fc00000 &&
	    !parts[0].name) अणु
		parts[0].name = "boot";
		parts[0].offset = 0x1fc00000 - addr;
		parts[0].size = addr + size - 0x1fc00000;
		parts[1].name = "user";
		parts[1].offset = 0;
		parts[1].size = 0x1fc00000 - addr;
		pdata_part = *pdata;
		pdata_part.nr_parts = ARRAY_SIZE(parts);
		pdata_part.parts = parts;
		pdata = &pdata_part;
	पूर्ण

	pdev = platक्रमm_device_alloc("physmap-flash", no);
	अगर (!pdev ||
	    platक्रमm_device_add_resources(pdev, &res, 1) ||
	    platक्रमm_device_add_data(pdev, pdata, माप(*pdata)) ||
	    platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
#पूर्ण_अगर
पूर्ण

व्योम __init txx9_ndfmc_init(अचिन्हित दीर्घ baseaddr,
			    स्थिर काष्ठा txx9ndfmc_platक्रमm_data *pdata)
अणु
#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_TXX9NDFMC)
	काष्ठा resource res = अणु
		.start = baseaddr,
		.end = baseaddr + 0x1000 - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev = platक्रमm_device_alloc("txx9ndfmc", -1);

	अगर (!pdev ||
	    platक्रमm_device_add_resources(pdev, &res, 1) ||
	    platक्रमm_device_add_data(pdev, pdata, माप(*pdata)) ||
	    platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
#पूर्ण_अगर
पूर्ण

#अगर IS_ENABLED(CONFIG_LEDS_GPIO)
अटल DEFINE_SPINLOCK(txx9_iocled_lock);

#घोषणा TXX9_IOCLED_MAXLEDS 8

काष्ठा txx9_iocled_data अणु
	काष्ठा gpio_chip chip;
	u8 cur_val;
	व्योम __iomem *mmioaddr;
	काष्ठा gpio_led_platक्रमm_data pdata;
	काष्ठा gpio_led leds[TXX9_IOCLED_MAXLEDS];
	अक्षर names[TXX9_IOCLED_MAXLEDS][32];
पूर्ण;

अटल पूर्णांक txx9_iocled_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा txx9_iocled_data *data = gpiochip_get_data(chip);
	वापस !!(data->cur_val & (1 << offset));
पूर्ण

अटल व्योम txx9_iocled_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा txx9_iocled_data *data = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&txx9_iocled_lock, flags);
	अगर (value)
		data->cur_val |= 1 << offset;
	अन्यथा
		data->cur_val &= ~(1 << offset);
	ग_लिखोb(data->cur_val, data->mmioaddr);
	mmiowb();
	spin_unlock_irqrestore(&txx9_iocled_lock, flags);
पूर्ण

अटल पूर्णांक txx9_iocled_dir_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक txx9_iocled_dir_out(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			       पूर्णांक value)
अणु
	txx9_iocled_set(chip, offset, value);
	वापस 0;
पूर्ण

व्योम __init txx9_iocled_init(अचिन्हित दीर्घ baseaddr,
			     पूर्णांक basक्रमागत, अचिन्हित पूर्णांक num, पूर्णांक lowactive,
			     स्थिर अक्षर *color, अक्षर **deftriggers)
अणु
	काष्ठा txx9_iocled_data *iocled;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक i;
	अटल अक्षर *शेष_triggers[] __initdata = अणु
		"heartbeat",
		"disk-activity",
		"nand-disk",
		शून्य,
	पूर्ण;

	अगर (!deftriggers)
		deftriggers = शेष_triggers;
	iocled = kzalloc(माप(*iocled), GFP_KERNEL);
	अगर (!iocled)
		वापस;
	iocled->mmioaddr = ioremap(baseaddr, 1);
	अगर (!iocled->mmioaddr)
		जाओ out_मुक्त;
	iocled->chip.get = txx9_iocled_get;
	iocled->chip.set = txx9_iocled_set;
	iocled->chip.direction_input = txx9_iocled_dir_in;
	iocled->chip.direction_output = txx9_iocled_dir_out;
	iocled->chip.label = "iocled";
	iocled->chip.base = basक्रमागत;
	iocled->chip.ngpio = num;
	अगर (gpiochip_add_data(&iocled->chip, iocled))
		जाओ out_unmap;
	अगर (basक्रमागत < 0)
		basक्रमागत = iocled->chip.base;

	pdev = platक्रमm_device_alloc("leds-gpio", basक्रमागत);
	अगर (!pdev)
		जाओ out_gpio;
	iocled->pdata.num_leds = num;
	iocled->pdata.leds = iocled->leds;
	क्रम (i = 0; i < num; i++) अणु
		काष्ठा gpio_led *led = &iocled->leds[i];
		snम_लिखो(iocled->names[i], माप(iocled->names[i]),
			 "iocled:%s:%u", color, i);
		led->name = iocled->names[i];
		led->gpio = basक्रमागत + i;
		led->active_low = lowactive;
		अगर (deftriggers && *deftriggers)
			led->शेष_trigger = *deftriggers++;
	पूर्ण
	pdev->dev.platक्रमm_data = &iocled->pdata;
	अगर (platक्रमm_device_add(pdev))
		जाओ out_pdev;
	वापस;

out_pdev:
	platक्रमm_device_put(pdev);
out_gpio:
	gpiochip_हटाओ(&iocled->chip);
out_unmap:
	iounmap(iocled->mmioaddr);
out_मुक्त:
	kमुक्त(iocled);
पूर्ण
#अन्यथा /* CONFIG_LEDS_GPIO */
व्योम __init txx9_iocled_init(अचिन्हित दीर्घ baseaddr,
			     पूर्णांक basक्रमागत, अचिन्हित पूर्णांक num, पूर्णांक lowactive,
			     स्थिर अक्षर *color, अक्षर **deftriggers)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_LEDS_GPIO */

व्योम __init txx9_dmac_init(पूर्णांक id, अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
			   स्थिर काष्ठा txx9dmac_platक्रमm_data *pdata)
अणु
#अगर IS_ENABLED(CONFIG_TXX9_DMAC)
	काष्ठा resource res[] = अणु
		अणु
			.start = baseaddr,
			.end = baseaddr + 0x800 - 1,
			.flags = IORESOURCE_MEM,
#अगर_अघोषित CONFIG_MACH_TX49XX
		पूर्ण, अणु
			.start = irq,
			.flags = IORESOURCE_IRQ,
#पूर्ण_अगर
		पूर्ण
	पूर्ण;
#अगर_घोषित CONFIG_MACH_TX49XX
	काष्ठा resource chan_res[] = अणु
		अणु
			.flags = IORESOURCE_IRQ,
		पूर्ण
	पूर्ण;
#पूर्ण_अगर
	काष्ठा platक्रमm_device *pdev = platक्रमm_device_alloc("txx9dmac", id);
	काष्ठा txx9dmac_chan_platक्रमm_data cpdata;
	पूर्णांक i;

	अगर (!pdev ||
	    platक्रमm_device_add_resources(pdev, res, ARRAY_SIZE(res)) ||
	    platक्रमm_device_add_data(pdev, pdata, माप(*pdata)) ||
	    platक्रमm_device_add(pdev)) अणु
		platक्रमm_device_put(pdev);
		वापस;
	पूर्ण
	स_रखो(&cpdata, 0, माप(cpdata));
	cpdata.dmac_dev = pdev;
	क्रम (i = 0; i < TXX9_DMA_MAX_NR_CHANNELS; i++) अणु
#अगर_घोषित CONFIG_MACH_TX49XX
		chan_res[0].start = irq + i;
#पूर्ण_अगर
		pdev = platक्रमm_device_alloc("txx9dmac-chan",
					     id * TXX9_DMA_MAX_NR_CHANNELS + i);
		अगर (!pdev ||
#अगर_घोषित CONFIG_MACH_TX49XX
		    platक्रमm_device_add_resources(pdev, chan_res,
						  ARRAY_SIZE(chan_res)) ||
#पूर्ण_अगर
		    platक्रमm_device_add_data(pdev, &cpdata, माप(cpdata)) ||
		    platक्रमm_device_add(pdev))
			platक्रमm_device_put(pdev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init txx9_aclc_init(अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
			   अचिन्हित पूर्णांक dmac_id,
			   अचिन्हित पूर्णांक dma_chan_out,
			   अचिन्हित पूर्णांक dma_chan_in)
अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_TXX9ACLC)
	अचिन्हित पूर्णांक dma_base = dmac_id * TXX9_DMA_MAX_NR_CHANNELS;
	काष्ठा resource res[] = अणु
		अणु
			.start = baseaddr,
			.end = baseaddr + 0x100 - 1,
			.flags = IORESOURCE_MEM,
		पूर्ण, अणु
			.start = irq,
			.flags = IORESOURCE_IRQ,
		पूर्ण, अणु
			.name = "txx9dmac-chan",
			.start = dma_base + dma_chan_out,
			.flags = IORESOURCE_DMA,
		पूर्ण, अणु
			.name = "txx9dmac-chan",
			.start = dma_base + dma_chan_in,
			.flags = IORESOURCE_DMA,
		पूर्ण
	पूर्ण;
	काष्ठा platक्रमm_device *pdev =
		platक्रमm_device_alloc("txx9aclc-ac97", -1);

	अगर (!pdev ||
	    platक्रमm_device_add_resources(pdev, res, ARRAY_SIZE(res)) ||
	    platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा bus_type txx9_sramc_subsys = अणु
	.name = "txx9_sram",
	.dev_name = "txx9_sram",
पूर्ण;

काष्ठा txx9_sramc_dev अणु
	काष्ठा device dev;
	काष्ठा bin_attribute bindata_attr;
	व्योम __iomem *base;
पूर्ण;

अटल sमाप_प्रकार txx9_sram_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr,
			      अक्षर *buf, loff_t pos, माप_प्रकार size)
अणु
	काष्ठा txx9_sramc_dev *dev = bin_attr->निजी;
	माप_प्रकार ramsize = bin_attr->size;

	अगर (pos >= ramsize)
		वापस 0;
	अगर (pos + size > ramsize)
		size = ramsize - pos;
	स_नकल_fromio(buf, dev->base + pos, size);
	वापस size;
पूर्ण

अटल sमाप_प्रकार txx9_sram_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buf, loff_t pos, माप_प्रकार size)
अणु
	काष्ठा txx9_sramc_dev *dev = bin_attr->निजी;
	माप_प्रकार ramsize = bin_attr->size;

	अगर (pos >= ramsize)
		वापस 0;
	अगर (pos + size > ramsize)
		size = ramsize - pos;
	स_नकल_toio(dev->base + pos, buf, size);
	वापस size;
पूर्ण

अटल व्योम txx9_device_release(काष्ठा device *dev)
अणु
	काष्ठा txx9_sramc_dev *tdev;

	tdev = container_of(dev, काष्ठा txx9_sramc_dev, dev);
	kमुक्त(tdev);
पूर्ण

व्योम __init txx9_sramc_init(काष्ठा resource *r)
अणु
	काष्ठा txx9_sramc_dev *dev;
	माप_प्रकार size;
	पूर्णांक err;

	err = subsys_प्रणाली_रेजिस्टर(&txx9_sramc_subsys, शून्य);
	अगर (err)
		वापस;
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस;
	size = resource_size(r);
	dev->base = ioremap(r->start, size);
	अगर (!dev->base) अणु
		kमुक्त(dev);
		वापस;
	पूर्ण
	dev->dev.release = &txx9_device_release;
	dev->dev.bus = &txx9_sramc_subsys;
	sysfs_bin_attr_init(&dev->bindata_attr);
	dev->bindata_attr.attr.name = "bindata";
	dev->bindata_attr.attr.mode = S_IRUSR | S_IWUSR;
	dev->bindata_attr.पढ़ो = txx9_sram_पढ़ो;
	dev->bindata_attr.ग_लिखो = txx9_sram_ग_लिखो;
	dev->bindata_attr.size = size;
	dev->bindata_attr.निजी = dev;
	err = device_रेजिस्टर(&dev->dev);
	अगर (err)
		जाओ निकास_put;
	err = sysfs_create_bin_file(&dev->dev.kobj, &dev->bindata_attr);
	अगर (err) अणु
		iounmap(dev->base);
		device_unरेजिस्टर(&dev->dev);
	पूर्ण
	वापस;
निकास_put:
	iounmap(dev->base);
	put_device(&dev->dev);
पूर्ण
