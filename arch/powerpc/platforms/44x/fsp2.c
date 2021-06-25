<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FSP-2 board specअगरic routines
 *
 * Based on earlier code:
 *    Matt Porter <mporter@kernel.crashing.org>
 *    Copyright 2002-2005 MontaVista Software Inc.
 *
 *    Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *    Copyright (c) 2003-2005 Zultys Technologies
 *
 *    Rewritten and ported to the merged घातerpc tree:
 *    Copyright 2007 David Gibson <dwg@au1.ibm.com>, IBM Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uic.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <यंत्र/dcr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश "fsp2.h"

#घोषणा FSP2_BUS_ERR	"ibm,bus-error-irq"
#घोषणा FSP2_CMU_ERR	"ibm,cmu-error-irq"
#घोषणा FSP2_CONF_ERR	"ibm,conf-error-irq"
#घोषणा FSP2_OPBD_ERR	"ibm,opbd-error-irq"
#घोषणा FSP2_MCUE	"ibm,mc-ue-irq"
#घोषणा FSP2_RST_WRN	"ibm,reset-warning-irq"

अटल __initdata काष्ठा of_device_id fsp2_of_bus[] = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,plb6", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम l2regs(व्योम)
अणु
	pr_err("L2 Controller:\n");
	pr_err("MCK:      0x%08x\n", mfl2(L2MCK));
	pr_err("INT:      0x%08x\n", mfl2(L2INT));
	pr_err("PLBSTAT0: 0x%08x\n", mfl2(L2PLBSTAT0));
	pr_err("PLBSTAT1: 0x%08x\n", mfl2(L2PLBSTAT1));
	pr_err("ARRSTAT0: 0x%08x\n", mfl2(L2ARRSTAT0));
	pr_err("ARRSTAT1: 0x%08x\n", mfl2(L2ARRSTAT1));
	pr_err("ARRSTAT2: 0x%08x\n", mfl2(L2ARRSTAT2));
	pr_err("CPUSTAT:  0x%08x\n", mfl2(L2CPUSTAT));
	pr_err("RACSTAT0: 0x%08x\n", mfl2(L2RACSTAT0));
	pr_err("WACSTAT0: 0x%08x\n", mfl2(L2WACSTAT0));
	pr_err("WACSTAT1: 0x%08x\n", mfl2(L2WACSTAT1));
	pr_err("WACSTAT2: 0x%08x\n", mfl2(L2WACSTAT2));
	pr_err("WDFSTAT:  0x%08x\n", mfl2(L2WDFSTAT));
	pr_err("LOG0:     0x%08x\n", mfl2(L2LOG0));
	pr_err("LOG1:     0x%08x\n", mfl2(L2LOG1));
	pr_err("LOG2:     0x%08x\n", mfl2(L2LOG2));
	pr_err("LOG3:     0x%08x\n", mfl2(L2LOG3));
	pr_err("LOG4:     0x%08x\n", mfl2(L2LOG4));
	pr_err("LOG5:     0x%08x\n", mfl2(L2LOG5));
पूर्ण

अटल व्योम show_plbopb_regs(u32 base, पूर्णांक num)
अणु
	pr_err("\nPLBOPB Bridge %d:\n", num);
	pr_err("GESR0: 0x%08x\n", mfdcr(base + PLB4OPB_GESR0));
	pr_err("GESR1: 0x%08x\n", mfdcr(base + PLB4OPB_GESR1));
	pr_err("GESR2: 0x%08x\n", mfdcr(base + PLB4OPB_GESR2));
	pr_err("GEARU: 0x%08x\n", mfdcr(base + PLB4OPB_GEARU));
	pr_err("GEAR:  0x%08x\n", mfdcr(base + PLB4OPB_GEAR));
पूर्ण

अटल irqवापस_t bus_err_handler(पूर्णांक irq, व्योम *data)
अणु
	pr_err("Bus Error\n");

	l2regs();

	pr_err("\nPLB6 Controller:\n");
	pr_err("BC_SHD: 0x%08x\n", mfdcr(DCRN_PLB6_SHD));
	pr_err("BC_ERR: 0x%08x\n", mfdcr(DCRN_PLB6_ERR));

	pr_err("\nPLB6-to-PLB4 Bridge:\n");
	pr_err("ESR:  0x%08x\n", mfdcr(DCRN_PLB6PLB4_ESR));
	pr_err("EARH: 0x%08x\n", mfdcr(DCRN_PLB6PLB4_EARH));
	pr_err("EARL: 0x%08x\n", mfdcr(DCRN_PLB6PLB4_EARL));

	pr_err("\nPLB4-to-PLB6 Bridge:\n");
	pr_err("ESR:  0x%08x\n", mfdcr(DCRN_PLB4PLB6_ESR));
	pr_err("EARH: 0x%08x\n", mfdcr(DCRN_PLB4PLB6_EARH));
	pr_err("EARL: 0x%08x\n", mfdcr(DCRN_PLB4PLB6_EARL));

	pr_err("\nPLB6-to-MCIF Bridge:\n");
	pr_err("BESR0: 0x%08x\n", mfdcr(DCRN_PLB6MCIF_BESR0));
	pr_err("BESR1: 0x%08x\n", mfdcr(DCRN_PLB6MCIF_BESR1));
	pr_err("BEARH: 0x%08x\n", mfdcr(DCRN_PLB6MCIF_BEARH));
	pr_err("BEARL: 0x%08x\n", mfdcr(DCRN_PLB6MCIF_BEARL));

	pr_err("\nPLB4 Arbiter:\n");
	pr_err("P0ESRH 0x%08x\n", mfdcr(DCRN_PLB4_P0ESRH));
	pr_err("P0ESRL 0x%08x\n", mfdcr(DCRN_PLB4_P0ESRL));
	pr_err("P0EARH 0x%08x\n", mfdcr(DCRN_PLB4_P0EARH));
	pr_err("P0EARH 0x%08x\n", mfdcr(DCRN_PLB4_P0EARH));
	pr_err("P1ESRH 0x%08x\n", mfdcr(DCRN_PLB4_P1ESRH));
	pr_err("P1ESRL 0x%08x\n", mfdcr(DCRN_PLB4_P1ESRL));
	pr_err("P1EARH 0x%08x\n", mfdcr(DCRN_PLB4_P1EARH));
	pr_err("P1EARH 0x%08x\n", mfdcr(DCRN_PLB4_P1EARH));

	show_plbopb_regs(DCRN_PLB4OPB0_BASE, 0);
	show_plbopb_regs(DCRN_PLB4OPB1_BASE, 1);
	show_plbopb_regs(DCRN_PLB4OPB2_BASE, 2);
	show_plbopb_regs(DCRN_PLB4OPB3_BASE, 3);

	pr_err("\nPLB4-to-AHB Bridge:\n");
	pr_err("ESR:   0x%08x\n", mfdcr(DCRN_PLB4AHB_ESR));
	pr_err("SEUAR: 0x%08x\n", mfdcr(DCRN_PLB4AHB_SEUAR));
	pr_err("SELAR: 0x%08x\n", mfdcr(DCRN_PLB4AHB_SELAR));

	pr_err("\nAHB-to-PLB4 Bridge:\n");
	pr_err("\nESR: 0x%08x\n", mfdcr(DCRN_AHBPLB4_ESR));
	pr_err("\nEAR: 0x%08x\n", mfdcr(DCRN_AHBPLB4_EAR));
	panic("Bus Error\n");
पूर्ण

अटल irqवापस_t cmu_err_handler(पूर्णांक irq, व्योम *data) अणु
	pr_err("CMU Error\n");
	pr_err("FIR0: 0x%08x\n", mfcmu(CMUN_FIR0));
	panic("CMU Error\n");
पूर्ण

अटल irqवापस_t conf_err_handler(पूर्णांक irq, व्योम *data) अणु
	pr_err("Configuration Logic Error\n");
	pr_err("CONF_FIR: 0x%08x\n", mfdcr(DCRN_CONF_FIR_RWC));
	pr_err("RPERR0:   0x%08x\n", mfdcr(DCRN_CONF_RPERR0));
	pr_err("RPERR1:   0x%08x\n", mfdcr(DCRN_CONF_RPERR1));
	panic("Configuration Logic Error\n");
पूर्ण

अटल irqवापस_t opbd_err_handler(पूर्णांक irq, व्योम *data) अणु
	panic("OPBD Error\n");
पूर्ण

अटल irqवापस_t mcue_handler(पूर्णांक irq, व्योम *data) अणु
	pr_err("DDR: Uncorrectable Error\n");
	pr_err("MCSTAT:            0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_MCSTAT));
	pr_err("MCOPT1:            0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_MCOPT1));
	pr_err("MCOPT2:            0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_MCOPT2));
	pr_err("PHYSTAT:           0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_PHYSTAT));
	pr_err("CFGR0:             0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_CFGR0));
	pr_err("CFGR1:             0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_CFGR1));
	pr_err("CFGR2:             0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_CFGR2));
	pr_err("CFGR3:             0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_CFGR3));
	pr_err("SCRUB_CNTL:        0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_SCRUB_CNTL));
	pr_err("ECCERR_PORT0:      0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_ECCERR_PORT0));
	pr_err("ECCERR_ADDR_PORT0: 0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_ECCERR_ADDR_PORT0));
	pr_err("ECCERR_CNT_PORT0:  0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_ECCERR_COUNT_PORT0));
	pr_err("ECC_CHECK_PORT0:   0x%08x\n",
		mfdcr(DCRN_DDR34_BASE + DCRN_DDR34_ECC_CHECK_PORT0));
	pr_err("MCER0:            0x%08x\n",
		mfdcr(DCRN_CW_BASE + DCRN_CW_MCER0));
	pr_err("MCER1:            0x%08x\n",
		mfdcr(DCRN_CW_BASE + DCRN_CW_MCER1));
	pr_err("BESR:             0x%08x\n",
		mfdcr(DCRN_PLB6MCIF_BESR0));
	pr_err("BEARL:            0x%08x\n",
		mfdcr(DCRN_PLB6MCIF_BEARL));
	pr_err("BEARH:            0x%08x\n",
		mfdcr(DCRN_PLB6MCIF_BEARH));
	panic("DDR: Uncorrectable Error\n");
पूर्ण

अटल irqवापस_t rst_wrn_handler(पूर्णांक irq, व्योम *data) अणु
	u32 crcs = mfcmu(CMUN_CRCS);
	चयन (crcs & CRCS_STAT_MASK) अणु
	हाल CRCS_STAT_CHIP_RST_B:
		panic("Received chassis-initiated reset request");
	शेष:
		panic("Unknown external reset: CRCS=0x%x", crcs);
	पूर्ण
पूर्ण

अटल व्योम node_irq_request(स्थिर अक्षर *compat, irq_handler_t errirq_handler)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक irq;
	पूर्णांक32_t rc;

	क्रम_each_compatible_node(np, शून्य, compat) अणु
		irq = irq_of_parse_and_map(np, 0);
		अगर (irq == NO_IRQ) अणु
			pr_err("device tree node %pOFn is missing a interrupt",
			      np);
			वापस;
		पूर्ण

		rc = request_irq(irq, errirq_handler, 0, np->name, np);
		अगर (rc) अणु
			pr_err("fsp_of_probe: request_irq failed: np=%pOF rc=%d",
			      np, rc);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम critical_irq_setup(व्योम)
अणु
	node_irq_request(FSP2_CMU_ERR, cmu_err_handler);
	node_irq_request(FSP2_BUS_ERR, bus_err_handler);
	node_irq_request(FSP2_CONF_ERR, conf_err_handler);
	node_irq_request(FSP2_OPBD_ERR, opbd_err_handler);
	node_irq_request(FSP2_MCUE, mcue_handler);
	node_irq_request(FSP2_RST_WRN, rst_wrn_handler);
पूर्ण

अटल पूर्णांक __init fsp2_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, fsp2_of_bus, शून्य);
	वापस 0;
पूर्ण
machine_device_initcall(fsp2, fsp2_device_probe);

अटल पूर्णांक __init fsp2_probe(व्योम)
अणु
	u32 val;
	अचिन्हित दीर्घ root = of_get_flat_dt_root();

	अगर (!of_flat_dt_is_compatible(root, "ibm,fsp2"))
		वापस 0;

	/* Clear BC_ERR and mask snoopable request plb errors. */
	val = mfdcr(DCRN_PLB6_CR0);
	val |= 0x20000000;
	mtdcr(DCRN_PLB6_BASE, val);
	mtdcr(DCRN_PLB6_HD, 0xffff0000);
	mtdcr(DCRN_PLB6_SHD, 0xffff0000);

	/* TVSENSE reset is blocked (घड़ी gated) by the POR शेष of the TVS
	 * sleep config bit. As a consequence, TVSENSE will provide erratic
	 * sensor values, which may result in spurious (parity) errors
	 * recorded in the CMU FIR and leading to erroneous पूर्णांकerrupt requests
	 * once the CMU पूर्णांकerrupt is unmasked.
	 */

	/* 1. set TVS1[UNDOZE] */
	val = mfcmu(CMUN_TVS1);
	val |= 0x4;
	mtcmu(CMUN_TVS1, val);

	/* 2. clear FIR[TVS] and FIR[TVSPAR] */
	val = mfcmu(CMUN_FIR0);
	val |= 0x30000000;
	mtcmu(CMUN_FIR0, val);

	/* L2 machine checks */
	mtl2(L2PLBMCKEN0, 0xffffffff);
	mtl2(L2PLBMCKEN1, 0x0000ffff);
	mtl2(L2ARRMCKEN0, 0xffffffff);
	mtl2(L2ARRMCKEN1, 0xffffffff);
	mtl2(L2ARRMCKEN2, 0xfffff000);
	mtl2(L2CPUMCKEN,  0xffffffff);
	mtl2(L2RACMCKEN0, 0xffffffff);
	mtl2(L2WACMCKEN0, 0xffffffff);
	mtl2(L2WACMCKEN1, 0xffffffff);
	mtl2(L2WACMCKEN2, 0xffffffff);
	mtl2(L2WDFMCKEN,  0xffffffff);

	/* L2 पूर्णांकerrupts */
	mtl2(L2PLBINTEN1, 0xffff0000);

	/*
	 * At a global level, enable all L2 machine checks and पूर्णांकerrupts
	 * reported by the L2 subप्रणालीs, except क्रम the बाह्यal machine check
	 * input (UIC0.1).
	 */
	mtl2(L2MCKEN, 0x000007ff);
	mtl2(L2INTEN, 0x000004ff);

	/* Enable FSP-2 configuration logic parity errors */
	mtdcr(DCRN_CONF_EIR_RS, 0x80000000);
	वापस 1;
पूर्ण

अटल व्योम __init fsp2_irq_init(व्योम)
अणु
	uic_init_tree();
	critical_irq_setup();
पूर्ण

define_machine(fsp2) अणु
	.name			= "FSP-2",
	.probe			= fsp2_probe,
	.progress		= udbg_progress,
	.init_IRQ		= fsp2_irq_init,
	.get_irq		= uic_get_irq,
	.restart		= ppc4xx_reset_प्रणाली,
	.calibrate_decr		= generic_calibrate_decr,
पूर्ण;
