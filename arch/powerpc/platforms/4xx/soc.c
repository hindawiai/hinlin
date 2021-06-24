<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM/AMCC PPC4xx SoC setup code
 *
 * Copyright 2008 DENX Software Engineering, Stefan Roese <sr@denx.de>
 *
 * L2 cache routines cloned from arch/ppc/syslib/ibm440gx_common.c which is:
 *   Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *   Copyright (c) 2003 - 2006 Zultys Technologies
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>
#समावेश <यंत्र/reg.h>

अटल u32 dcrbase_l2c;

/*
 * L2-cache
 */

/* Issue L2C diagnostic command */
अटल अंतरभूत u32 l2c_diag(u32 addr)
अणु
	mtdcr(dcrbase_l2c + DCRN_L2C0_ADDR, addr);
	mtdcr(dcrbase_l2c + DCRN_L2C0_CMD, L2C_CMD_DIAG);
	जबतक (!(mfdcr(dcrbase_l2c + DCRN_L2C0_SR) & L2C_SR_CC))
		;

	वापस mfdcr(dcrbase_l2c + DCRN_L2C0_DATA);
पूर्ण

अटल irqवापस_t l2c_error_handler(पूर्णांक irq, व्योम *dev)
अणु
	u32 sr = mfdcr(dcrbase_l2c + DCRN_L2C0_SR);

	अगर (sr & L2C_SR_CPE) अणु
		/* Read cache trapped address */
		u32 addr = l2c_diag(0x42000000);
		prपूर्णांकk(KERN_EMERG "L2C: Cache Parity Error, addr[16:26] = 0x%08x\n",
		       addr);
	पूर्ण
	अगर (sr & L2C_SR_TPE) अणु
		/* Read tag trapped address */
		u32 addr = l2c_diag(0x82000000) >> 16;
		prपूर्णांकk(KERN_EMERG "L2C: Tag Parity Error, addr[16:26] = 0x%08x\n",
		       addr);
	पूर्ण

	/* Clear parity errors */
	अगर (sr & (L2C_SR_CPE | L2C_SR_TPE))अणु
		mtdcr(dcrbase_l2c + DCRN_L2C0_ADDR, 0);
		mtdcr(dcrbase_l2c + DCRN_L2C0_CMD, L2C_CMD_CCP | L2C_CMD_CTE);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_EMERG "L2C: LRU error\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ppc4xx_l2c_probe(व्योम)
अणु
	काष्ठा device_node *np;
	u32 r;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq;
	स्थिर u32 *dcrreg;
	u32 dcrbase_isram;
	पूर्णांक len;
	स्थिर u32 *prop;
	u32 l2_size;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,l2-cache");
	अगर (!np)
		वापस 0;

	/* Get l2 cache size */
	prop = of_get_property(np, "cache-size", शून्य);
	अगर (prop == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get cache-size!\n", np);
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण
	l2_size = prop[0];

	/* Map DCRs */
	dcrreg = of_get_property(np, "dcr-reg", &len);
	अगर (!dcrreg || (len != 4 * माप(u32))) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get DCR register base !", np);
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण
	dcrbase_isram = dcrreg[0];
	dcrbase_l2c = dcrreg[2];

	/* Get and map irq number from device tree */
	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		prपूर्णांकk(KERN_ERR "irq_of_parse_and_map failed\n");
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	/* Install error handler */
	अगर (request_irq(irq, l2c_error_handler, 0, "L2C", 0) < 0) अणु
		prपूर्णांकk(KERN_ERR "Cannot install L2C error handler"
		       ", cache is not enabled\n");
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	local_irq_save(flags);
	यंत्र अस्थिर ("sync" ::: "memory");

	/* Disable SRAM */
	mtdcr(dcrbase_isram + DCRN_SRAM0_DPC,
	      mfdcr(dcrbase_isram + DCRN_SRAM0_DPC) & ~SRAM_DPC_ENABLE);
	mtdcr(dcrbase_isram + DCRN_SRAM0_SB0CR,
	      mfdcr(dcrbase_isram + DCRN_SRAM0_SB0CR) & ~SRAM_SBCR_BU_MASK);
	mtdcr(dcrbase_isram + DCRN_SRAM0_SB1CR,
	      mfdcr(dcrbase_isram + DCRN_SRAM0_SB1CR) & ~SRAM_SBCR_BU_MASK);
	mtdcr(dcrbase_isram + DCRN_SRAM0_SB2CR,
	      mfdcr(dcrbase_isram + DCRN_SRAM0_SB2CR) & ~SRAM_SBCR_BU_MASK);
	mtdcr(dcrbase_isram + DCRN_SRAM0_SB3CR,
	      mfdcr(dcrbase_isram + DCRN_SRAM0_SB3CR) & ~SRAM_SBCR_BU_MASK);

	/* Enable L2_MODE without ICU/DCU */
	r = mfdcr(dcrbase_l2c + DCRN_L2C0_CFG) &
		~(L2C_CFG_ICU | L2C_CFG_DCU | L2C_CFG_SS_MASK);
	r |= L2C_CFG_L2M | L2C_CFG_SS_256;
	mtdcr(dcrbase_l2c + DCRN_L2C0_CFG, r);

	mtdcr(dcrbase_l2c + DCRN_L2C0_ADDR, 0);

	/* Hardware Clear Command */
	mtdcr(dcrbase_l2c + DCRN_L2C0_CMD, L2C_CMD_HCC);
	जबतक (!(mfdcr(dcrbase_l2c + DCRN_L2C0_SR) & L2C_SR_CC))
		;

	/* Clear Cache Parity and Tag Errors */
	mtdcr(dcrbase_l2c + DCRN_L2C0_CMD, L2C_CMD_CCP | L2C_CMD_CTE);

	/* Enable 64G snoop region starting at 0 */
	r = mfdcr(dcrbase_l2c + DCRN_L2C0_SNP0) &
		~(L2C_SNP_BA_MASK | L2C_SNP_SSR_MASK);
	r |= L2C_SNP_SSR_32G | L2C_SNP_ESR;
	mtdcr(dcrbase_l2c + DCRN_L2C0_SNP0, r);

	r = mfdcr(dcrbase_l2c + DCRN_L2C0_SNP1) &
		~(L2C_SNP_BA_MASK | L2C_SNP_SSR_MASK);
	r |= 0x80000000 | L2C_SNP_SSR_32G | L2C_SNP_ESR;
	mtdcr(dcrbase_l2c + DCRN_L2C0_SNP1, r);

	यंत्र अस्थिर ("sync" ::: "memory");

	/* Enable ICU/DCU ports */
	r = mfdcr(dcrbase_l2c + DCRN_L2C0_CFG);
	r &= ~(L2C_CFG_DCW_MASK | L2C_CFG_PMUX_MASK | L2C_CFG_PMIM
	       | L2C_CFG_TPEI | L2C_CFG_CPEI | L2C_CFG_NAM | L2C_CFG_NBRM);
	r |= L2C_CFG_ICU | L2C_CFG_DCU | L2C_CFG_TPC | L2C_CFG_CPC | L2C_CFG_FRAN
		| L2C_CFG_CPIM | L2C_CFG_TPIM | L2C_CFG_LIM | L2C_CFG_SMCM;

	/* Check क्रम 460EX/GT special handling */
	अगर (of_device_is_compatible(np, "ibm,l2-cache-460ex") ||
	    of_device_is_compatible(np, "ibm,l2-cache-460gt"))
		r |= L2C_CFG_RDBW;

	mtdcr(dcrbase_l2c + DCRN_L2C0_CFG, r);

	यंत्र अस्थिर ("sync; isync" ::: "memory");
	local_irq_restore(flags);

	prपूर्णांकk(KERN_INFO "%dk L2-cache enabled\n", l2_size >> 10);

	of_node_put(np);
	वापस 0;
पूर्ण
arch_initcall(ppc4xx_l2c_probe);

/*
 * Apply a प्रणाली reset. Alternatively a board specअगरic value may be
 * provided via the "reset-type" property in the cpu node.
 */
व्योम ppc4xx_reset_प्रणाली(अक्षर *cmd)
अणु
	काष्ठा device_node *np;
	u32 reset_type = DBCR0_RST_SYSTEM;
	स्थिर u32 *prop;

	np = of_get_cpu_node(0, शून्य);
	अगर (np) अणु
		prop = of_get_property(np, "reset-type", शून्य);

		/*
		 * Check अगर property exists and अगर it is in range:
		 * 1 - PPC4xx core reset
		 * 2 - PPC4xx chip reset
		 * 3 - PPC4xx प्रणाली reset (शेष)
		 */
		अगर ((prop) && ((prop[0] >= 1) && (prop[0] <= 3)))
			reset_type = prop[0] << 28;
	पूर्ण

	mtspr(SPRN_DBCR0, mfspr(SPRN_DBCR0) | reset_type);

	जबतक (1)
		;	/* Just in हाल the reset करोesn't work */
पूर्ण
