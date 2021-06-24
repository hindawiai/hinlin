<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Abilis Systems TB10x platक्रमm initialisation
 *
 * Copyright (C) Abilis Systems 2012
 *
 * Author: Christian Ruppert <christian.ruppert@abilis.com>
 */

#समावेश <linux/init.h>
#समावेश <यंत्र/mach_desc.h>

अटल स्थिर अक्षर *tb10x_compat[] __initdata = अणु
	"abilis,arc-tb10x",
	शून्य,
पूर्ण;

MACHINE_START(TB10x, "tb10x")
	.dt_compat	= tb10x_compat,
MACHINE_END
