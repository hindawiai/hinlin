<शैली गुरु>
/*
 * Copyright (C) 2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश "clk-iproc.h"

अटल व्योम __init bcm63138_armpll_init(काष्ठा device_node *node)
अणु
	iproc_armpll_setup(node);
पूर्ण
CLK_OF_DECLARE(bcm63138_armpll, "brcm,bcm63138-armpll", bcm63138_armpll_init);
