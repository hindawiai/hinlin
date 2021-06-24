<शैली गुरु>
/*
 * TX3927 setup routines
 * Based on linux/arch/mips/txx9/jmr3927/setup.c
 *
 * Copyright 2001 MontaVista Software Inc.
 * Copyright (C) 2000-2001 Toshiba Corporation
 * Copyright (C) 2007 Ralf Baechle (ralf@linux-mips.org)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/param.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/physmap.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9पंचांगr.h>
#समावेश <यंत्र/txx9pपन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/tx3927.h>

व्योम __init tx3927_wdt_init(व्योम)
अणु
	txx9_wdt_init(TX3927_TMR_REG(2));
पूर्ण

व्योम __init tx3927_setup(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक conf;

	txx9_reg_res_init(TX3927_REV_PCODE(), TX3927_REG_BASE,
			  TX3927_REG_SIZE);

	/* SDRAMC,ROMC are configured by PROM */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(tx3927_romcptr->cr[i] & 0x8))
			जारी;	/* disabled */
		txx9_ce_res[i].start = (अचिन्हित दीर्घ)TX3927_ROMC_BA(i);
		txx9_ce_res[i].end =
			txx9_ce_res[i].start + TX3927_ROMC_SIZE(i) - 1;
		request_resource(&iomem_resource, &txx9_ce_res[i]);
	पूर्ण

	/* घड़ीs */
	txx9_gbus_घड़ी = txx9_cpu_घड़ी / 2;
	/* change शेष value to udelay/mdelay take reasonable समय */
	loops_per_jअगरfy = txx9_cpu_घड़ी / HZ / 2;

	/* CCFG */
	/* enable Timeout BusError */
	अगर (txx9_ccfg_toeon)
		tx3927_ccfgptr->ccfg |= TX3927_CCFG_TOE;

	/* clear BusErrorOnWrite flag */
	tx3927_ccfgptr->ccfg &= ~TX3927_CCFG_BEOW;
	अगर (पढ़ो_c0_conf() & TX39_CONF_WBON)
		/* Disable PCI snoop */
		tx3927_ccfgptr->ccfg &= ~TX3927_CCFG_PSNP;
	अन्यथा
		/* Enable PCI SNOOP - with ग_लिखो through only */
		tx3927_ccfgptr->ccfg |= TX3927_CCFG_PSNP;
	/* करो reset on watchकरोg */
	tx3927_ccfgptr->ccfg |= TX3927_CCFG_WR;

	pr_info("TX3927 -- CRIR:%08lx CCFG:%08lx PCFG:%08lx\n",
		tx3927_ccfgptr->crir, tx3927_ccfgptr->ccfg,
		tx3927_ccfgptr->pcfg);

	/* TMR */
	क्रम (i = 0; i < TX3927_NR_TMR; i++)
		txx9_पंचांगr_init(TX3927_TMR_REG(i));

	/* DMA */
	tx3927_dmaptr->mcr = 0;
	क्रम (i = 0; i < ARRAY_SIZE(tx3927_dmaptr->ch); i++) अणु
		/* reset channel */
		tx3927_dmaptr->ch[i].ccr = TX3927_DMA_CCR_CHRST;
		tx3927_dmaptr->ch[i].ccr = 0;
	पूर्ण
	/* enable DMA */
#अगर_घोषित __BIG_ENDIAN
	tx3927_dmaptr->mcr = TX3927_DMA_MCR_MSTEN;
#अन्यथा
	tx3927_dmaptr->mcr = TX3927_DMA_MCR_MSTEN | TX3927_DMA_MCR_LE;
#पूर्ण_अगर

	/* PIO */
	__raw_ग_लिखोl(0, &tx3927_pioptr->maskcpu);
	__raw_ग_लिखोl(0, &tx3927_pioptr->maskext);

	conf = पढ़ो_c0_conf();
	अगर (conf & TX39_CONF_DCE) अणु
		अगर (!(conf & TX39_CONF_WBON))
			pr_info("TX3927 D-Cache WriteThrough.\n");
		अन्यथा अगर (!(conf & TX39_CONF_CWFON))
			pr_info("TX3927 D-Cache WriteBack.\n");
		अन्यथा
			pr_info("TX3927 D-Cache WriteBack (CWF) .\n");
	पूर्ण
पूर्ण

व्योम __init tx3927_समय_init(अचिन्हित पूर्णांक evt_पंचांगrnr, अचिन्हित पूर्णांक src_पंचांगrnr)
अणु
	txx9_घड़ीevent_init(TX3927_TMR_REG(evt_पंचांगrnr),
			     TXX9_IRQ_BASE + TX3927_IR_TMR(evt_पंचांगrnr),
			     TXX9_IMCLK);
	txx9_घड़ीsource_init(TX3927_TMR_REG(src_पंचांगrnr), TXX9_IMCLK);
पूर्ण

व्योम __init tx3927_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		txx9_sio_init(TX3927_SIO_REG(i),
			      TXX9_IRQ_BASE + TX3927_IR_SIO(i),
			      i, sclk, (1 << i) & cts_mask);
पूर्ण

व्योम __init tx3927_mtd_init(पूर्णांक ch)
अणु
	काष्ठा physmap_flash_data pdata = अणु
		.width = TX3927_ROMC_WIDTH(ch) / 8,
	पूर्ण;
	अचिन्हित दीर्घ start = txx9_ce_res[ch].start;
	अचिन्हित दीर्घ size = txx9_ce_res[ch].end - start + 1;

	अगर (!(tx3927_romcptr->cr[ch] & 0x8))
		वापस; /* disabled */
	txx9_physmap_flash_init(ch, start, size, &pdata);
पूर्ण
