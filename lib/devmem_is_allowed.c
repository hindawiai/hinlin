<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A generic version of devmem_is_allowed.
 *
 * Based on arch/arm64/mm/mmap.c
 *
 * Copyright (C) 2020 Google, Inc.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>

/*
 * devmem_is_allowed() checks to see अगर /dev/mem access to a certain address
 * is valid. The argument is a physical page number.  We mimic x86 here by
 * disallowing access to प्रणाली RAM as well as device-exclusive MMIO regions.
 * This effectively disable पढ़ो()/ग_लिखो() on /dev/mem.
 */
पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pfn)
अणु
	अगर (iomem_is_exclusive(pfn << PAGE_SHIFT))
		वापस 0;
	अगर (!page_is_ram(pfn))
		वापस 1;
	वापस 0;
पूर्ण
