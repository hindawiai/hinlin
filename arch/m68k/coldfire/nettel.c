<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	nettel.c -- startup code support क्रम the NETtel boards
 *
 *	Copyright (C) 2009, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/nettel.h>

/***************************************************************************/

/*
 * Define the IO and पूर्णांकerrupt resources of the 2 SMC9196 पूर्णांकerfaces.
 */
#घोषणा	NETTEL_SMC0_ADDR	0x30600300
#घोषणा	NETTEL_SMC0_IRQ		29

#घोषणा	NETTEL_SMC1_ADDR	0x30600000
#घोषणा	NETTEL_SMC1_IRQ		27

/*
 * We need some access पूर्णांकo the SMC9196 रेजिस्टरs. Define those रेजिस्टरs
 * we will need here (including the smc91x.h करोesn't seem to give us these
 * in a simple क्रमm).
 */
#घोषणा	SMC91xx_BANKSELECT	14
#घोषणा	SMC91xx_BASEADDR	2
#घोषणा	SMC91xx_BASEMAC		4

/***************************************************************************/

अटल काष्ठा resource nettel_smc91x_0_resources[] = अणु
	अणु
		.start		= NETTEL_SMC0_ADDR,
		.end		= NETTEL_SMC0_ADDR + 0x20,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= NETTEL_SMC0_IRQ,
		.end		= NETTEL_SMC0_IRQ,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource nettel_smc91x_1_resources[] = अणु
	अणु
		.start		= NETTEL_SMC1_ADDR,
		.end		= NETTEL_SMC1_ADDR + 0x20,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= NETTEL_SMC1_IRQ,
		.end		= NETTEL_SMC1_IRQ,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device nettel_smc91x[] = अणु
	अणु
		.name			= "smc91x",
		.id			= 0,
		.num_resources		= ARRAY_SIZE(nettel_smc91x_0_resources),
		.resource		= nettel_smc91x_0_resources,
	पूर्ण,
	अणु
		.name			= "smc91x",
		.id			= 1,
		.num_resources		= ARRAY_SIZE(nettel_smc91x_1_resources),
		.resource		= nettel_smc91x_1_resources,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *nettel_devices[] __initdata = अणु
	&nettel_smc91x[0],
	&nettel_smc91x[1],
पूर्ण;

/***************************************************************************/

अटल u8 nettel_macशेष[] __initdata = अणु
	0x00, 0xd0, 0xcf, 0x00, 0x00, 0x01,
पूर्ण;

/*
 * Set flash contained MAC address पूर्णांकo SMC9196 core. Make sure the flash
 * MAC address is sane, and not an empty flash. If no good use the Moreton
 * Bay शेष MAC address instead.
 */

अटल व्योम __init nettel_smc91x_seपंचांगac(अचिन्हित पूर्णांक ioaddr, अचिन्हित पूर्णांक flashaddr)
अणु
	u16 *macp;

	macp = (u16 *) flashaddr;
	अगर ((macp[0] == 0xffff) && (macp[1] == 0xffff) && (macp[2] == 0xffff))
		macp = (u16 *) &nettel_macशेष[0];

	ग_लिखोw(1, NETTEL_SMC0_ADDR + SMC91xx_BANKSELECT);
	ग_लिखोw(macp[0], ioaddr + SMC91xx_BASEMAC);
	ग_लिखोw(macp[1], ioaddr + SMC91xx_BASEMAC + 2);
	ग_लिखोw(macp[2], ioaddr + SMC91xx_BASEMAC + 4);
पूर्ण

/***************************************************************************/

/*
 * Re-map the address space of at least one of the SMC ethernet
 * parts. Both parts घातer up decoding the same address, so we
 * need to move one of them first, beक्रमe करोing anything अन्यथा.
 */

अटल व्योम __init nettel_smc91x_init(व्योम)
अणु
	ग_लिखोw(0x00ec, MCFSIM_PADDR);
	mcf_setppdata(0, 0x0080);
	ग_लिखोw(1, NETTEL_SMC0_ADDR + SMC91xx_BANKSELECT);
	ग_लिखोw(0x0067, NETTEL_SMC0_ADDR + SMC91xx_BASEADDR);
	mcf_setppdata(0x0080, 0);

	/* Set correct chip select timing क्रम SMC9196 accesses */
	ग_लिखोw(0x1180, MCFSIM_CSCR3);

	/* Set the SMC पूर्णांकerrupts to be स्वतः-vectored */
	mcf_स्वतःvector(NETTEL_SMC0_IRQ);
	mcf_स्वतःvector(NETTEL_SMC1_IRQ);

	/* Set MAC addresses from flash क्रम both पूर्णांकerfaces */
	nettel_smc91x_seपंचांगac(NETTEL_SMC0_ADDR, 0xf0006000);
	nettel_smc91x_seपंचांगac(NETTEL_SMC1_ADDR, 0xf0006006);
पूर्ण

/***************************************************************************/

अटल पूर्णांक __init init_nettel(व्योम)
अणु
	nettel_smc91x_init();
	platक्रमm_add_devices(nettel_devices, ARRAY_SIZE(nettel_devices));
	वापस 0;
पूर्ण

arch_initcall(init_nettel);

/***************************************************************************/
