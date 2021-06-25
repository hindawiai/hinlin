<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2011 Thomas Langer <thomas.langer@lantiq.com>
 * Copyright (C) 2011 John Crispin <john@phrozen.org>
 */

#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/delay.h>

#समावेश <lantiq_soc.h>

#समावेश "../clk.h"

/* infraकाष्ठाure control रेजिस्टर */
#घोषणा SYS1_INFRAC		0x00bc
/* Configuration fuses क्रम drivers and pll */
#घोषणा STATUS_CONFIG		0x0040

/* GPE frequency selection */
#घोषणा GPPC_OFFSET		24
#घोषणा GPEFREQ_MASK		0x0000C00
#घोषणा GPEFREQ_OFFSET		10
/* Clock status रेजिस्टर */
#घोषणा SYSCTL_CLKS		0x0000
/* Clock enable रेजिस्टर */
#घोषणा SYSCTL_CLKEN		0x0004
/* Clock clear रेजिस्टर */
#घोषणा SYSCTL_CLKCLR		0x0008
/* Activation Status Register */
#घोषणा SYSCTL_ACTS		0x0020
/* Activation Register */
#घोषणा SYSCTL_ACT		0x0024
/* Deactivation Register */
#घोषणा SYSCTL_DEACT		0x0028
/* reboot Register */
#घोषणा SYSCTL_RBT		0x002c
/* CPU0 Clock Control Register */
#घोषणा SYS1_CPU0CC		0x0040
/* HRST_OUT_N Control Register */
#घोषणा SYS1_HRSTOUTC		0x00c0
/* घड़ी भागider bit */
#घोषणा CPU0CC_CPUDIV		0x0001

/* Activation Status Register */
#घोषणा ACTS_ASC0_ACT	0x00001000
#घोषणा ACTS_SSC0	0x00002000
#घोषणा ACTS_ASC1_ACT	0x00000800
#घोषणा ACTS_I2C_ACT	0x00004000
#घोषणा ACTS_P0		0x00010000
#घोषणा ACTS_P1		0x00010000
#घोषणा ACTS_P2		0x00020000
#घोषणा ACTS_P3		0x00020000
#घोषणा ACTS_P4		0x00040000
#घोषणा ACTS_PADCTRL0	0x00100000
#घोषणा ACTS_PADCTRL1	0x00100000
#घोषणा ACTS_PADCTRL2	0x00200000
#घोषणा ACTS_PADCTRL3	0x00200000
#घोषणा ACTS_PADCTRL4	0x00400000

#घोषणा sysctl_w32(m, x, y)	ltq_w32((x), sysctl_membase[m] + (y))
#घोषणा sysctl_r32(m, x)	ltq_r32(sysctl_membase[m] + (x))
#घोषणा sysctl_w32_mask(m, clear, set, reg)	\
		sysctl_w32(m, (sysctl_r32(m, reg) & ~(clear)) | (set), reg)

#घोषणा status_w32(x, y)	ltq_w32((x), status_membase + (y))
#घोषणा status_r32(x)		ltq_r32(status_membase + (x))

अटल व्योम __iomem *sysctl_membase[3], *status_membase;
व्योम __iomem *ltq_sys1_membase, *ltq_ebu_membase;

व्योम falcon_trigger_hrst(पूर्णांक level)
अणु
	sysctl_w32(SYSCTL_SYS1, level & 1, SYS1_HRSTOUTC);
पूर्ण

अटल अंतरभूत व्योम sysctl_रुको(काष्ठा clk *clk,
		अचिन्हित पूर्णांक test, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक err = 1000000;

	करो अणुपूर्ण जबतक (--err && ((sysctl_r32(clk->module, reg)
					& clk->bits) != test));
	अगर (!err)
		pr_err("module de/activation failed %d %08X %08X %08X\n",
			clk->module, clk->bits, test,
			sysctl_r32(clk->module, reg) & clk->bits);
पूर्ण

अटल पूर्णांक sysctl_activate(काष्ठा clk *clk)
अणु
	sysctl_w32(clk->module, clk->bits, SYSCTL_CLKEN);
	sysctl_w32(clk->module, clk->bits, SYSCTL_ACT);
	sysctl_रुको(clk, clk->bits, SYSCTL_ACTS);
	वापस 0;
पूर्ण

अटल व्योम sysctl_deactivate(काष्ठा clk *clk)
अणु
	sysctl_w32(clk->module, clk->bits, SYSCTL_CLKCLR);
	sysctl_w32(clk->module, clk->bits, SYSCTL_DEACT);
	sysctl_रुको(clk, 0, SYSCTL_ACTS);
पूर्ण

अटल पूर्णांक sysctl_clken(काष्ठा clk *clk)
अणु
	sysctl_w32(clk->module, clk->bits, SYSCTL_CLKEN);
	sysctl_w32(clk->module, clk->bits, SYSCTL_ACT);
	sysctl_रुको(clk, clk->bits, SYSCTL_CLKS);
	वापस 0;
पूर्ण

अटल व्योम sysctl_clkdis(काष्ठा clk *clk)
अणु
	sysctl_w32(clk->module, clk->bits, SYSCTL_CLKCLR);
	sysctl_रुको(clk, 0, SYSCTL_CLKS);
पूर्ण

अटल व्योम sysctl_reboot(काष्ठा clk *clk)
अणु
	अचिन्हित पूर्णांक act;
	अचिन्हित पूर्णांक bits;

	act = sysctl_r32(clk->module, SYSCTL_ACT);
	bits = ~act & clk->bits;
	अगर (bits != 0) अणु
		sysctl_w32(clk->module, bits, SYSCTL_CLKEN);
		sysctl_w32(clk->module, bits, SYSCTL_ACT);
		sysctl_रुको(clk, bits, SYSCTL_ACTS);
	पूर्ण
	sysctl_w32(clk->module, act & clk->bits, SYSCTL_RBT);
	sysctl_रुको(clk, clk->bits, SYSCTL_ACTS);
पूर्ण

/* enable the ONU core */
अटल व्योम falcon_gpe_enable(व्योम)
अणु
	अचिन्हित पूर्णांक freq;
	अचिन्हित पूर्णांक status;

	/* अगर अगर the घड़ी is alपढ़ोy enabled */
	status = sysctl_r32(SYSCTL_SYS1, SYS1_INFRAC);
	अगर (status & (1 << (GPPC_OFFSET + 1)))
		वापस;

	freq = (status_r32(STATUS_CONFIG) &
		GPEFREQ_MASK) >>
		GPEFREQ_OFFSET;
	अगर (freq == 0)
		freq = 1; /* use 625MHz on unfused chip */

	/* apply new frequency */
	sysctl_w32_mask(SYSCTL_SYS1, 7 << (GPPC_OFFSET + 1),
		freq << (GPPC_OFFSET + 2) , SYS1_INFRAC);
	udelay(1);

	/* enable new frequency */
	sysctl_w32_mask(SYSCTL_SYS1, 0, 1 << (GPPC_OFFSET + 1), SYS1_INFRAC);
	udelay(1);
पूर्ण

अटल अंतरभूत व्योम clkdev_add_sys(स्थिर अक्षर *dev, अचिन्हित पूर्णांक module,
					अचिन्हित पूर्णांक bits)
अणु
	काष्ठा clk *clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);

	clk->cl.dev_id = dev;
	clk->cl.con_id = शून्य;
	clk->cl.clk = clk;
	clk->module = module;
	clk->bits = bits;
	clk->activate = sysctl_activate;
	clk->deactivate = sysctl_deactivate;
	clk->enable = sysctl_clken;
	clk->disable = sysctl_clkdis;
	clk->reboot = sysctl_reboot;
	clkdev_add(&clk->cl);
पूर्ण

व्योम __init ltq_soc_init(व्योम)
अणु
	काष्ठा device_node *np_status =
		of_find_compatible_node(शून्य, शून्य, "lantiq,status-falcon");
	काष्ठा device_node *np_ebu =
		of_find_compatible_node(शून्य, शून्य, "lantiq,ebu-falcon");
	काष्ठा device_node *np_sys1 =
		of_find_compatible_node(शून्य, शून्य, "lantiq,sys1-falcon");
	काष्ठा device_node *np_syseth =
		of_find_compatible_node(शून्य, शून्य, "lantiq,syseth-falcon");
	काष्ठा device_node *np_sysgpe =
		of_find_compatible_node(शून्य, शून्य, "lantiq,sysgpe-falcon");
	काष्ठा resource res_status, res_ebu, res_sys[3];
	पूर्णांक i;

	/* check अगर all the core रेजिस्टर ranges are available */
	अगर (!np_status || !np_ebu || !np_sys1 || !np_syseth || !np_sysgpe)
		panic("Failed to load core nodes from devicetree");

	अगर (of_address_to_resource(np_status, 0, &res_status) ||
			of_address_to_resource(np_ebu, 0, &res_ebu) ||
			of_address_to_resource(np_sys1, 0, &res_sys[0]) ||
			of_address_to_resource(np_syseth, 0, &res_sys[1]) ||
			of_address_to_resource(np_sysgpe, 0, &res_sys[2]))
		panic("Failed to get core resources");

	अगर ((request_mem_region(res_status.start, resource_size(&res_status),
				res_status.name) < 0) ||
		(request_mem_region(res_ebu.start, resource_size(&res_ebu),
				res_ebu.name) < 0) ||
		(request_mem_region(res_sys[0].start,
				resource_size(&res_sys[0]),
				res_sys[0].name) < 0) ||
		(request_mem_region(res_sys[1].start,
				resource_size(&res_sys[1]),
				res_sys[1].name) < 0) ||
		(request_mem_region(res_sys[2].start,
				resource_size(&res_sys[2]),
				res_sys[2].name) < 0))
		pr_err("Failed to request core resources");

	status_membase = ioremap(res_status.start,
					resource_size(&res_status));
	ltq_ebu_membase = ioremap(res_ebu.start,
					resource_size(&res_ebu));

	अगर (!status_membase || !ltq_ebu_membase)
		panic("Failed to remap core resources");

	क्रम (i = 0; i < 3; i++) अणु
		sysctl_membase[i] = ioremap(res_sys[i].start,
						resource_size(&res_sys[i]));
		अगर (!sysctl_membase[i])
			panic("Failed to remap sysctrl resources");
	पूर्ण
	ltq_sys1_membase = sysctl_membase[0];

	falcon_gpe_enable();

	/* get our 3 अटल rates क्रम cpu, fpi and io घड़ीs */
	अगर (ltq_sys1_r32(SYS1_CPU0CC) & CPU0CC_CPUDIV)
		clkdev_add_अटल(CLOCK_200M, CLOCK_100M, CLOCK_200M, 0);
	अन्यथा
		clkdev_add_अटल(CLOCK_400M, CLOCK_100M, CLOCK_200M, 0);

	/* add our घड़ी करोमुख्यs */
	clkdev_add_sys("1d810000.gpio", SYSCTL_SYSETH, ACTS_P0);
	clkdev_add_sys("1d810100.gpio", SYSCTL_SYSETH, ACTS_P2);
	clkdev_add_sys("1e800100.gpio", SYSCTL_SYS1, ACTS_P1);
	clkdev_add_sys("1e800200.gpio", SYSCTL_SYS1, ACTS_P3);
	clkdev_add_sys("1e800300.gpio", SYSCTL_SYS1, ACTS_P4);
	clkdev_add_sys("1db01000.pad", SYSCTL_SYSETH, ACTS_PADCTRL0);
	clkdev_add_sys("1db02000.pad", SYSCTL_SYSETH, ACTS_PADCTRL2);
	clkdev_add_sys("1e800400.pad", SYSCTL_SYS1, ACTS_PADCTRL1);
	clkdev_add_sys("1e800500.pad", SYSCTL_SYS1, ACTS_PADCTRL3);
	clkdev_add_sys("1e800600.pad", SYSCTL_SYS1, ACTS_PADCTRL4);
	clkdev_add_sys("1e100b00.serial", SYSCTL_SYS1, ACTS_ASC1_ACT);
	clkdev_add_sys("1e100c00.serial", SYSCTL_SYS1, ACTS_ASC0_ACT);
	clkdev_add_sys("1e100d00.spi", SYSCTL_SYS1, ACTS_SSC0);
	clkdev_add_sys("1e200000.i2c", SYSCTL_SYS1, ACTS_I2C_ACT);
पूर्ण
