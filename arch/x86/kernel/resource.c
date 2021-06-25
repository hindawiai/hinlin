<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ioport.h>
#समावेश <यंत्र/e820/api.h>

अटल व्योम resource_clip(काष्ठा resource *res, resource_माप_प्रकार start,
			  resource_माप_प्रकार end)
अणु
	resource_माप_प्रकार low = 0, high = 0;

	अगर (res->end < start || res->start > end)
		वापस;		/* no conflict */

	अगर (res->start < start)
		low = start - res->start;

	अगर (res->end > end)
		high = res->end - end;

	/* Keep the area above or below the conflict, whichever is larger */
	अगर (low > high)
		res->end = start - 1;
	अन्यथा
		res->start = end + 1;
पूर्ण

अटल व्योम हटाओ_e820_regions(काष्ठा resource *avail)
अणु
	पूर्णांक i;
	काष्ठा e820_entry *entry;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		entry = &e820_table->entries[i];

		resource_clip(avail, entry->addr,
			      entry->addr + entry->size - 1);
	पूर्ण
पूर्ण

व्योम arch_हटाओ_reservations(काष्ठा resource *avail)
अणु
	/*
	 * Trim out BIOS area (high 2MB) and E820 regions. We करो not हटाओ
	 * the low 1MB unconditionally, as this area is needed क्रम some ISA
	 * cards requiring a memory range, e.g. the i82365 PCMCIA controller.
	 */
	अगर (avail->flags & IORESOURCE_MEM) अणु
		resource_clip(avail, BIOS_ROM_BASE, BIOS_ROM_END);

		हटाओ_e820_regions(avail);
	पूर्ण
पूर्ण
