<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/memory.h>
#समावेश <linux/of.h>

#समावेश "base.h"

/**
 * driver_init - initialize driver model.
 *
 * Call the driver model init functions to initialize their
 * subप्रणालीs. Called early from init/मुख्य.c.
 */
व्योम __init driver_init(व्योम)
अणु
	/* These are the core pieces */
	devपंचांगpfs_init();
	devices_init();
	buses_init();
	classes_init();
	firmware_init();
	hypervisor_init();

	/* These are also core pieces, but must come after the
	 * core core pieces.
	 */
	of_core_init();
	platक्रमm_bus_init();
	auxiliary_bus_init();
	cpu_dev_init();
	memory_dev_init();
	container_dev_init();
पूर्ण
