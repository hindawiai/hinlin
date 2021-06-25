<शैली गुरु>
/*
 * mcf8390.c  -- platक्रमm support क्रम 8390 ethernet on many boards
 *
 * (C) Copyright 2012, Greg Ungerer <gerg@uclinux.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/resource.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/mcf8390.h>

अटल काष्ठा resource mcf8390_resources[] = अणु
	अणु
		.start	= NE2000_ADDR,
		.end	= NE2000_ADDR + NE2000_ADDRSIZE - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= NE2000_IRQ_VECTOR,
		.end	= NE2000_IRQ_VECTOR,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mcf8390_platक्रमm_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("mcf8390", -1, mcf8390_resources,
		ARRAY_SIZE(mcf8390_resources));
	वापस 0;
पूर्ण

arch_initcall(mcf8390_platक्रमm_init);
