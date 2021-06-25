<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDK7786 FPGA Support.
 *
 * Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/bcd.h>
#समावेश <mach/fpga.h>
#समावेश <linux/sizes.h>

#घोषणा FPGA_REGS_OFFSET	0x03fff800
#घोषणा FPGA_REGS_SIZE		0x490

/*
 * The FPGA can be mapped in any of the generally available areas,
 * so we attempt to scan क्रम it using the fixed SRSTR पढ़ो magic.
 *
 * Once the FPGA is located, the rest of the mapping data क्रम the other
 * components can be determined dynamically from its section mapping
 * रेजिस्टरs.
 */
अटल व्योम __iomem *sdk7786_fpga_probe(व्योम)
अणु
	अचिन्हित दीर्घ area;
	व्योम __iomem *base;

	/*
	 * Iterate over all of the areas where the FPGA could be mapped.
	 * The possible range is anywhere from area 0 through 6, area 7
	 * is reserved.
	 */
	क्रम (area = PA_AREA0; area < PA_AREA7; area += SZ_64M) अणु
		base = ioremap(area + FPGA_REGS_OFFSET, FPGA_REGS_SIZE);
		अगर (!base) अणु
			/* Failed to remap this area, move aदीर्घ. */
			जारी;
		पूर्ण

		अगर (ioपढ़ो16(base + SRSTR) == SRSTR_MAGIC)
			वापस base;	/* Found it! */

		iounmap(base);
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __iomem *sdk7786_fpga_base;

व्योम __init sdk7786_fpga_init(व्योम)
अणु
	u16 version, date;

	sdk7786_fpga_base = sdk7786_fpga_probe();
	अगर (unlikely(!sdk7786_fpga_base)) अणु
		panic("FPGA detection failed.\n");
		वापस;
	पूर्ण

	version = fpga_पढ़ो_reg(FPGAVR);
	date = fpga_पढ़ो_reg(FPGADR);

	pr_info("\tFPGA version:\t%d.%d (built on %d/%d/%d)\n",
		bcd2bin(version >> 8) & 0xf, bcd2bin(version & 0xf),
		((date >> 12) & 0xf) + 2000,
		(date >> 8) & 0xf, bcd2bin(date & 0xff));
पूर्ण
