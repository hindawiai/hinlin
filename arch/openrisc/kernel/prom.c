<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC prom.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * Architecture specअगरic procedures क्रम creating, accessing and
 * पूर्णांकerpreting the device tree.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/page.h>

व्योम __init early_init_devtree(व्योम *params)
अणु
	early_init_dt_scan(params);
	memblock_allow_resize();
पूर्ण
