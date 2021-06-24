<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Low level x86 E820 memory map handling functions.
 *
 * The firmware and bootloader passes us the "E820 table", which is the primary
 * physical memory layout description available about x86 प्रणालीs.
 *
 * The kernel takes the E820 memory layout and optionally modअगरies it with
 * quirks and other tweaks, and feeds that पूर्णांकo the generic Linux memory
 * allocation code routines via a platक्रमm independent पूर्णांकerface (memblock, etc.).
 */
#समावेश <linux/crash_dump.h>
#समावेश <linux/memblock.h>
#समावेश <linux/suspend.h>
#समावेश <linux/acpi.h>
#समावेश <linux/firmware-map.h>
#समावेश <linux/sort.h>
#समावेश <linux/memory_hotplug.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/setup.h>

/*
 * We organize the E820 table पूर्णांकo three मुख्य data काष्ठाures:
 *
 * - 'e820_table_firmware': the original firmware version passed to us by the
 *   bootloader - not modअगरied by the kernel. It is composed of two parts:
 *   the first 128 E820 memory entries in boot_params.e820_table and the reमुख्यing
 *   (अगर any) entries of the SETUP_E820_EXT nodes. We use this to:
 *
 *       - inक्रमm the user about the firmware's notion of memory layout
 *         via /sys/firmware/memmap
 *
 *       - the hibernation code uses it to generate a kernel-independent CRC32
 *         checksum of the physical memory layout of a प्रणाली.
 *
 * - 'e820_table_kexec': a slightly modअगरied (by the kernel) firmware version
 *   passed to us by the bootloader - the major dअगरference between
 *   e820_table_firmware[] and this one is that, the latter marks the setup_data
 *   list created by the EFI boot stub as reserved, so that kexec can reuse the
 *   setup_data inक्रमmation in the second kernel. Besides, e820_table_kexec[]
 *   might also be modअगरied by the kexec itself to fake a mptable.
 *   We use this to:
 *
 *       - kexec, which is a bootloader in disguise, uses the original E820
 *         layout to pass to the kexec-ed kernel. This way the original kernel
 *         can have a restricted E820 map जबतक the kexec()-ed kexec-kernel
 *         can have access to full memory - etc.
 *
 * - 'e820_table': this is the मुख्य E820 table that is massaged by the
 *   low level x86 platक्रमm code, or modअगरied by boot parameters, beक्रमe
 *   passed on to higher level MM layers.
 *
 * Once the E820 map has been converted to the standard Linux memory layout
 * inक्रमmation its role stops - modअगरying it has no effect and करोes not get
 * re-propagated. So itsमुख्य role is a temporary bootstrap storage of firmware
 * specअगरic memory layout data during early bootup.
 */
अटल काष्ठा e820_table e820_table_init		__initdata;
अटल काष्ठा e820_table e820_table_kexec_init		__initdata;
अटल काष्ठा e820_table e820_table_firmware_init	__initdata;

काष्ठा e820_table *e820_table __refdata			= &e820_table_init;
काष्ठा e820_table *e820_table_kexec __refdata		= &e820_table_kexec_init;
काष्ठा e820_table *e820_table_firmware __refdata	= &e820_table_firmware_init;

/* For PCI or other memory-mapped resources */
अचिन्हित दीर्घ pci_mem_start = 0xaeedbabe;
#अगर_घोषित CONFIG_PCI
EXPORT_SYMBOL(pci_mem_start);
#पूर्ण_अगर

/*
 * This function checks अगर any part of the range <start,end> is mapped
 * with type.
 */
अटल bool _e820__mapped_any(काष्ठा e820_table *table,
			      u64 start, u64 end, क्रमागत e820_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &table->entries[i];

		अगर (type && entry->type != type)
			जारी;
		अगर (entry->addr >= end || entry->addr + entry->size <= start)
			जारी;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool e820__mapped_raw_any(u64 start, u64 end, क्रमागत e820_type type)
अणु
	वापस _e820__mapped_any(e820_table_firmware, start, end, type);
पूर्ण
EXPORT_SYMBOL_GPL(e820__mapped_raw_any);

bool e820__mapped_any(u64 start, u64 end, क्रमागत e820_type type)
अणु
	वापस _e820__mapped_any(e820_table, start, end, type);
पूर्ण
EXPORT_SYMBOL_GPL(e820__mapped_any);

/*
 * This function checks अगर the entire <start,end> range is mapped with 'type'.
 *
 * Note: this function only works correctly once the E820 table is sorted and
 * not-overlapping (at least क्रम the range specअगरied), which is the हाल normally.
 */
अटल काष्ठा e820_entry *__e820__mapped_all(u64 start, u64 end,
					     क्रमागत e820_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];

		अगर (type && entry->type != type)
			जारी;

		/* Is the region (part) in overlap with the current region? */
		अगर (entry->addr >= end || entry->addr + entry->size <= start)
			जारी;

		/*
		 * If the region is at the beginning of <start,end> we move
		 * 'start' to the end of the region since it's ok until there
		 */
		अगर (entry->addr <= start)
			start = entry->addr + entry->size;

		/*
		 * If 'start' is now at or beyond 'end', we're करोne, full
		 * coverage of the desired range exists:
		 */
		अगर (start >= end)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * This function checks अगर the entire range <start,end> is mapped with type.
 */
bool __init e820__mapped_all(u64 start, u64 end, क्रमागत e820_type type)
अणु
	वापस __e820__mapped_all(start, end, type);
पूर्ण

/*
 * This function वापसs the type associated with the range <start,end>.
 */
पूर्णांक e820__get_entry_type(u64 start, u64 end)
अणु
	काष्ठा e820_entry *entry = __e820__mapped_all(start, end, 0);

	वापस entry ? entry->type : -EINVAL;
पूर्ण

/*
 * Add a memory region to the kernel E820 map.
 */
अटल व्योम __init __e820__range_add(काष्ठा e820_table *table, u64 start, u64 size, क्रमागत e820_type type)
अणु
	पूर्णांक x = table->nr_entries;

	अगर (x >= ARRAY_SIZE(table->entries)) अणु
		pr_err("too many entries; ignoring [mem %#010llx-%#010llx]\n",
		       start, start + size - 1);
		वापस;
	पूर्ण

	table->entries[x].addr = start;
	table->entries[x].size = size;
	table->entries[x].type = type;
	table->nr_entries++;
पूर्ण

व्योम __init e820__range_add(u64 start, u64 size, क्रमागत e820_type type)
अणु
	__e820__range_add(e820_table, start, size, type);
पूर्ण

अटल व्योम __init e820_prपूर्णांक_type(क्रमागत e820_type type)
अणु
	चयन (type) अणु
	हाल E820_TYPE_RAM:		/* Fall through: */
	हाल E820_TYPE_RESERVED_KERN:	pr_cont("usable");			अवरोध;
	हाल E820_TYPE_RESERVED:	pr_cont("reserved");			अवरोध;
	हाल E820_TYPE_SOFT_RESERVED:	pr_cont("soft reserved");		अवरोध;
	हाल E820_TYPE_ACPI:		pr_cont("ACPI data");			अवरोध;
	हाल E820_TYPE_NVS:		pr_cont("ACPI NVS");			अवरोध;
	हाल E820_TYPE_UNUSABLE:	pr_cont("unusable");			अवरोध;
	हाल E820_TYPE_PMEM:		/* Fall through: */
	हाल E820_TYPE_PRAM:		pr_cont("persistent (type %u)", type);	अवरोध;
	शेष:			pr_cont("type %u", type);		अवरोध;
	पूर्ण
पूर्ण

व्योम __init e820__prपूर्णांक_table(अक्षर *who)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		pr_info("%s: [mem %#018Lx-%#018Lx] ",
			who,
			e820_table->entries[i].addr,
			e820_table->entries[i].addr + e820_table->entries[i].size - 1);

		e820_prपूर्णांक_type(e820_table->entries[i].type);
		pr_cont("\n");
	पूर्ण
पूर्ण

/*
 * Sanitize an E820 map.
 *
 * Some E820 layouts include overlapping entries. The following
 * replaces the original E820 map with a new one, removing overlaps,
 * and resolving conflicting memory types in favor of highest
 * numbered type.
 *
 * The input parameter 'entries' points to an array of 'काष्ठा
 * e820_entry' which on entry has elements in the range [0, *nr_entries)
 * valid, and which has space क्रम up to max_nr_entries entries.
 * On वापस, the resulting sanitized E820 map entries will be in
 * overwritten in the same location, starting at 'entries'.
 *
 * The पूर्णांकeger poपूर्णांकed to by nr_entries must be valid on entry (the
 * current number of valid entries located at 'entries'). If the
 * sanitizing succeeds the *nr_entries will be updated with the new
 * number of valid entries (something no more than max_nr_entries).
 *
 * The वापस value from e820__update_table() is zero अगर it
 * successfully 'sanitized' the map entries passed in, and is -1
 * अगर it did nothing, which can happen अगर either of (1) it was
 * only passed one map entry, or (2) any of the input map entries
 * were invalid (start + size < start, meaning that the size was
 * so big the described memory range wrapped around through zero.)
 *
 *	Visually we're perक्रमming the following
 *	(1,2,3,4 = memory types)...
 *
 *	Sample memory map (w/overlaps):
 *	   ____22__________________
 *	   ______________________4_
 *	   ____1111________________
 *	   _44_____________________
 *	   11111111________________
 *	   ____________________33__
 *	   ___________44___________
 *	   __________33333_________
 *	   ______________22________
 *	   ___________________2222_
 *	   _________111111111______
 *	   _____________________11_
 *	   _________________4______
 *
 *	Sanitized equivalent (no overlap):
 *	   1_______________________
 *	   _44_____________________
 *	   ___1____________________
 *	   ____22__________________
 *	   ______11________________
 *	   _________1______________
 *	   __________3_____________
 *	   ___________44___________
 *	   _____________33_________
 *	   _______________2________
 *	   ________________1_______
 *	   _________________4______
 *	   ___________________2____
 *	   ____________________33__
 *	   ______________________4_
 */
काष्ठा change_member अणु
	/* Poपूर्णांकer to the original entry: */
	काष्ठा e820_entry	*entry;
	/* Address क्रम this change poपूर्णांक: */
	अचिन्हित दीर्घ दीर्घ	addr;
पूर्ण;

अटल काष्ठा change_member	change_poपूर्णांक_list[2*E820_MAX_ENTRIES]	__initdata;
अटल काष्ठा change_member	*change_poपूर्णांक[2*E820_MAX_ENTRIES]	__initdata;
अटल काष्ठा e820_entry	*overlap_list[E820_MAX_ENTRIES]		__initdata;
अटल काष्ठा e820_entry	new_entries[E820_MAX_ENTRIES]		__initdata;

अटल पूर्णांक __init cpcompare(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा change_member * स्थिर *app = a, * स्थिर *bpp = b;
	स्थिर काष्ठा change_member *ap = *app, *bp = *bpp;

	/*
	 * Inमाला_दो are poपूर्णांकers to two elements of change_poपूर्णांक[].  If their
	 * addresses are not equal, their dअगरference करोminates.  If the addresses
	 * are equal, then consider one that represents the end of its region
	 * to be greater than one that करोes not.
	 */
	अगर (ap->addr != bp->addr)
		वापस ap->addr > bp->addr ? 1 : -1;

	वापस (ap->addr != ap->entry->addr) - (bp->addr != bp->entry->addr);
पूर्ण

अटल bool e820_nomerge(क्रमागत e820_type type)
अणु
	/*
	 * These types may indicate distinct platक्रमm ranges aligned to
	 * numa node, protection करोमुख्य, perक्रमmance करोमुख्य, or other
	 * boundaries. Do not merge them.
	 */
	अगर (type == E820_TYPE_PRAM)
		वापस true;
	अगर (type == E820_TYPE_SOFT_RESERVED)
		वापस true;
	वापस false;
पूर्ण

पूर्णांक __init e820__update_table(काष्ठा e820_table *table)
अणु
	काष्ठा e820_entry *entries = table->entries;
	u32 max_nr_entries = ARRAY_SIZE(table->entries);
	क्रमागत e820_type current_type, last_type;
	अचिन्हित दीर्घ दीर्घ last_addr;
	u32 new_nr_entries, overlap_entries;
	u32 i, chg_idx, chg_nr;

	/* If there's only one memory region, don't bother: */
	अगर (table->nr_entries < 2)
		वापस -1;

	BUG_ON(table->nr_entries > max_nr_entries);

	/* Bail out अगर we find any unreasonable addresses in the map: */
	क्रम (i = 0; i < table->nr_entries; i++) अणु
		अगर (entries[i].addr + entries[i].size < entries[i].addr)
			वापस -1;
	पूर्ण

	/* Create poपूर्णांकers क्रम initial change-poपूर्णांक inक्रमmation (क्रम sorting): */
	क्रम (i = 0; i < 2 * table->nr_entries; i++)
		change_poपूर्णांक[i] = &change_poपूर्णांक_list[i];

	/*
	 * Record all known change-poपूर्णांकs (starting and ending addresses),
	 * omitting empty memory regions:
	 */
	chg_idx = 0;
	क्रम (i = 0; i < table->nr_entries; i++)	अणु
		अगर (entries[i].size != 0) अणु
			change_poपूर्णांक[chg_idx]->addr	= entries[i].addr;
			change_poपूर्णांक[chg_idx++]->entry	= &entries[i];
			change_poपूर्णांक[chg_idx]->addr	= entries[i].addr + entries[i].size;
			change_poपूर्णांक[chg_idx++]->entry	= &entries[i];
		पूर्ण
	पूर्ण
	chg_nr = chg_idx;

	/* Sort change-poपूर्णांक list by memory addresses (low -> high): */
	sort(change_poपूर्णांक, chg_nr, माप(*change_poपूर्णांक), cpcompare, शून्य);

	/* Create a new memory map, removing overlaps: */
	overlap_entries = 0;	 /* Number of entries in the overlap table */
	new_nr_entries = 0;	 /* Index क्रम creating new map entries */
	last_type = 0;		 /* Start with undefined memory type */
	last_addr = 0;		 /* Start with 0 as last starting address */

	/* Loop through change-poपूर्णांकs, determining effect on the new map: */
	क्रम (chg_idx = 0; chg_idx < chg_nr; chg_idx++) अणु
		/* Keep track of all overlapping entries */
		अगर (change_poपूर्णांक[chg_idx]->addr == change_poपूर्णांक[chg_idx]->entry->addr) अणु
			/* Add map entry to overlap list (> 1 entry implies an overlap) */
			overlap_list[overlap_entries++] = change_poपूर्णांक[chg_idx]->entry;
		पूर्ण अन्यथा अणु
			/* Remove entry from list (order independent, so swap with last): */
			क्रम (i = 0; i < overlap_entries; i++) अणु
				अगर (overlap_list[i] == change_poपूर्णांक[chg_idx]->entry)
					overlap_list[i] = overlap_list[overlap_entries-1];
			पूर्ण
			overlap_entries--;
		पूर्ण
		/*
		 * If there are overlapping entries, decide which
		 * "type" to use (larger value takes precedence --
		 * 1=usable, 2,3,4,4+=unusable)
		 */
		current_type = 0;
		क्रम (i = 0; i < overlap_entries; i++) अणु
			अगर (overlap_list[i]->type > current_type)
				current_type = overlap_list[i]->type;
		पूर्ण

		/* Continue building up new map based on this inक्रमmation: */
		अगर (current_type != last_type || e820_nomerge(current_type)) अणु
			अगर (last_type != 0)	 अणु
				new_entries[new_nr_entries].size = change_poपूर्णांक[chg_idx]->addr - last_addr;
				/* Move क्रमward only अगर the new size was non-zero: */
				अगर (new_entries[new_nr_entries].size != 0)
					/* No more space left क्रम new entries? */
					अगर (++new_nr_entries >= max_nr_entries)
						अवरोध;
			पूर्ण
			अगर (current_type != 0)	अणु
				new_entries[new_nr_entries].addr = change_poपूर्णांक[chg_idx]->addr;
				new_entries[new_nr_entries].type = current_type;
				last_addr = change_poपूर्णांक[chg_idx]->addr;
			पूर्ण
			last_type = current_type;
		पूर्ण
	पूर्ण

	/* Copy the new entries पूर्णांकo the original location: */
	स_नकल(entries, new_entries, new_nr_entries*माप(*entries));
	table->nr_entries = new_nr_entries;

	वापस 0;
पूर्ण

अटल पूर्णांक __init __append_e820_table(काष्ठा boot_e820_entry *entries, u32 nr_entries)
अणु
	काष्ठा boot_e820_entry *entry = entries;

	जबतक (nr_entries) अणु
		u64 start = entry->addr;
		u64 size = entry->size;
		u64 end = start + size - 1;
		u32 type = entry->type;

		/* Ignore the entry on 64-bit overflow: */
		अगर (start > end && likely(size))
			वापस -1;

		e820__range_add(start, size, type);

		entry++;
		nr_entries--;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Copy the BIOS E820 map पूर्णांकo a safe place.
 *
 * Sanity-check it जबतक we're at it..
 *
 * If we're lucky and live on a modern प्रणाली, the setup code
 * will have given us a memory map that we can use to properly
 * set up memory.  If we aren't, we'll fake a memory map.
 */
अटल पूर्णांक __init append_e820_table(काष्ठा boot_e820_entry *entries, u32 nr_entries)
अणु
	/* Only one memory region (or negative)? Ignore it */
	अगर (nr_entries < 2)
		वापस -1;

	वापस __append_e820_table(entries, nr_entries);
पूर्ण

अटल u64 __init
__e820__range_update(काष्ठा e820_table *table, u64 start, u64 size, क्रमागत e820_type old_type, क्रमागत e820_type new_type)
अणु
	u64 end;
	अचिन्हित पूर्णांक i;
	u64 real_updated_size = 0;

	BUG_ON(old_type == new_type);

	अगर (size > (ULदीर्घ_उच्च - start))
		size = ULदीर्घ_उच्च - start;

	end = start + size;
	prपूर्णांकk(KERN_DEBUG "e820: update [mem %#010Lx-%#010Lx] ", start, end - 1);
	e820_prपूर्णांक_type(old_type);
	pr_cont(" ==> ");
	e820_prपूर्णांक_type(new_type);
	pr_cont("\n");

	क्रम (i = 0; i < table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &table->entries[i];
		u64 final_start, final_end;
		u64 entry_end;

		अगर (entry->type != old_type)
			जारी;

		entry_end = entry->addr + entry->size;

		/* Completely covered by new range? */
		अगर (entry->addr >= start && entry_end <= end) अणु
			entry->type = new_type;
			real_updated_size += entry->size;
			जारी;
		पूर्ण

		/* New range is completely covered? */
		अगर (entry->addr < start && entry_end > end) अणु
			__e820__range_add(table, start, size, new_type);
			__e820__range_add(table, end, entry_end - end, entry->type);
			entry->size = start - entry->addr;
			real_updated_size += size;
			जारी;
		पूर्ण

		/* Partially covered: */
		final_start = max(start, entry->addr);
		final_end = min(end, entry_end);
		अगर (final_start >= final_end)
			जारी;

		__e820__range_add(table, final_start, final_end - final_start, new_type);

		real_updated_size += final_end - final_start;

		/*
		 * Left range could be head or tail, so need to update
		 * its size first:
		 */
		entry->size -= final_end - final_start;
		अगर (entry->addr < final_start)
			जारी;

		entry->addr = final_end;
	पूर्ण
	वापस real_updated_size;
पूर्ण

u64 __init e820__range_update(u64 start, u64 size, क्रमागत e820_type old_type, क्रमागत e820_type new_type)
अणु
	वापस __e820__range_update(e820_table, start, size, old_type, new_type);
पूर्ण

अटल u64 __init e820__range_update_kexec(u64 start, u64 size, क्रमागत e820_type old_type, क्रमागत e820_type  new_type)
अणु
	वापस __e820__range_update(e820_table_kexec, start, size, old_type, new_type);
पूर्ण

/* Remove a range of memory from the E820 table: */
u64 __init e820__range_हटाओ(u64 start, u64 size, क्रमागत e820_type old_type, bool check_type)
अणु
	पूर्णांक i;
	u64 end;
	u64 real_हटाओd_size = 0;

	अगर (size > (ULदीर्घ_उच्च - start))
		size = ULदीर्घ_उच्च - start;

	end = start + size;
	prपूर्णांकk(KERN_DEBUG "e820: remove [mem %#010Lx-%#010Lx] ", start, end - 1);
	अगर (check_type)
		e820_prपूर्णांक_type(old_type);
	pr_cont("\n");

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];
		u64 final_start, final_end;
		u64 entry_end;

		अगर (check_type && entry->type != old_type)
			जारी;

		entry_end = entry->addr + entry->size;

		/* Completely covered? */
		अगर (entry->addr >= start && entry_end <= end) अणु
			real_हटाओd_size += entry->size;
			स_रखो(entry, 0, माप(*entry));
			जारी;
		पूर्ण

		/* Is the new range completely covered? */
		अगर (entry->addr < start && entry_end > end) अणु
			e820__range_add(end, entry_end - end, entry->type);
			entry->size = start - entry->addr;
			real_हटाओd_size += size;
			जारी;
		पूर्ण

		/* Partially covered: */
		final_start = max(start, entry->addr);
		final_end = min(end, entry_end);
		अगर (final_start >= final_end)
			जारी;

		real_हटाओd_size += final_end - final_start;

		/*
		 * Left range could be head or tail, so need to update
		 * the size first:
		 */
		entry->size -= final_end - final_start;
		अगर (entry->addr < final_start)
			जारी;

		entry->addr = final_end;
	पूर्ण
	वापस real_हटाओd_size;
पूर्ण

व्योम __init e820__update_table_prपूर्णांक(व्योम)
अणु
	अगर (e820__update_table(e820_table))
		वापस;

	pr_info("modified physical RAM map:\n");
	e820__prपूर्णांक_table("modified");
पूर्ण

अटल व्योम __init e820__update_table_kexec(व्योम)
अणु
	e820__update_table(e820_table_kexec);
पूर्ण

#घोषणा MAX_GAP_END 0x100000000ull

/*
 * Search क्रम a gap in the E820 memory space from 0 to MAX_GAP_END (4GB).
 */
अटल पूर्णांक __init e820_search_gap(अचिन्हित दीर्घ *gapstart, अचिन्हित दीर्घ *gapsize)
अणु
	अचिन्हित दीर्घ दीर्घ last = MAX_GAP_END;
	पूर्णांक i = e820_table->nr_entries;
	पूर्णांक found = 0;

	जबतक (--i >= 0) अणु
		अचिन्हित दीर्घ दीर्घ start = e820_table->entries[i].addr;
		अचिन्हित दीर्घ दीर्घ end = start + e820_table->entries[i].size;

		/*
		 * Since "last" is at most 4GB, we know we'll
		 * fit in 32 bits अगर this condition is true:
		 */
		अगर (last > end) अणु
			अचिन्हित दीर्घ gap = last - end;

			अगर (gap >= *gapsize) अणु
				*gapsize = gap;
				*gapstart = end;
				found = 1;
			पूर्ण
		पूर्ण
		अगर (start < last)
			last = start;
	पूर्ण
	वापस found;
पूर्ण

/*
 * Search क्रम the biggest gap in the low 32 bits of the E820
 * memory space. We pass this space to the PCI subप्रणाली, so
 * that it can assign MMIO resources क्रम hotplug or
 * unconfigured devices in.
 *
 * Hopefully the BIOS let enough space left.
 */
__init व्योम e820__setup_pci_gap(व्योम)
अणु
	अचिन्हित दीर्घ gapstart, gapsize;
	पूर्णांक found;

	gapsize = 0x400000;
	found  = e820_search_gap(&gapstart, &gapsize);

	अगर (!found) अणु
#अगर_घोषित CONFIG_X86_64
		gapstart = (max_pfn << PAGE_SHIFT) + 1024*1024;
		pr_err("Cannot find an available gap in the 32-bit address range\n");
		pr_err("PCI devices with unassigned 32-bit BARs may not work!\n");
#अन्यथा
		gapstart = 0x10000000;
#पूर्ण_अगर
	पूर्ण

	/*
	 * e820__reserve_resources_late() protects stolen RAM alपढ़ोy:
	 */
	pci_mem_start = gapstart;

	pr_info("[mem %#010lx-%#010lx] available for PCI devices\n",
		gapstart, gapstart + gapsize - 1);
पूर्ण

/*
 * Called late during init, in मुक्त_iniपंचांगem().
 *
 * Initial e820_table and e820_table_kexec are largish __initdata arrays.
 *
 * Copy them to a (usually much smaller) dynamically allocated area that is
 * sized precisely after the number of e820 entries.
 *
 * This is करोne after we've perक्रमmed all the fixes and tweaks to the tables.
 * All functions which modअगरy them are __init functions, which won't exist
 * after मुक्त_iniपंचांगem().
 */
__init व्योम e820__पुनः_स्मृतिate_tables(व्योम)
अणु
	काष्ठा e820_table *n;
	पूर्णांक size;

	size = दुरत्व(काष्ठा e820_table, entries) + माप(काष्ठा e820_entry)*e820_table->nr_entries;
	n = kmemdup(e820_table, size, GFP_KERNEL);
	BUG_ON(!n);
	e820_table = n;

	size = दुरत्व(काष्ठा e820_table, entries) + माप(काष्ठा e820_entry)*e820_table_kexec->nr_entries;
	n = kmemdup(e820_table_kexec, size, GFP_KERNEL);
	BUG_ON(!n);
	e820_table_kexec = n;

	size = दुरत्व(काष्ठा e820_table, entries) + माप(काष्ठा e820_entry)*e820_table_firmware->nr_entries;
	n = kmemdup(e820_table_firmware, size, GFP_KERNEL);
	BUG_ON(!n);
	e820_table_firmware = n;
पूर्ण

/*
 * Because of the small fixed size of काष्ठा boot_params, only the first
 * 128 E820 memory entries are passed to the kernel via boot_params.e820_table,
 * the reमुख्यing (अगर any) entries are passed via the SETUP_E820_EXT node of
 * काष्ठा setup_data, which is parsed here.
 */
व्योम __init e820__memory_setup_extended(u64 phys_addr, u32 data_len)
अणु
	पूर्णांक entries;
	काष्ठा boot_e820_entry *exपंचांगap;
	काष्ठा setup_data *sdata;

	sdata = early_memremap(phys_addr, data_len);
	entries = sdata->len / माप(*exपंचांगap);
	exपंचांगap = (काष्ठा boot_e820_entry *)(sdata->data);

	__append_e820_table(exपंचांगap, entries);
	e820__update_table(e820_table);

	स_नकल(e820_table_kexec, e820_table, माप(*e820_table_kexec));
	स_नकल(e820_table_firmware, e820_table, माप(*e820_table_firmware));

	early_memunmap(sdata, data_len);
	pr_info("extended physical RAM map:\n");
	e820__prपूर्णांक_table("extended");
पूर्ण

/*
 * Find the ranges of physical addresses that करो not correspond to
 * E820 RAM areas and रेजिस्टर the corresponding pages as 'nosave' क्रम
 * hibernation (32-bit) or software suspend and suspend to RAM (64-bit).
 *
 * This function requires the E820 map to be sorted and without any
 * overlapping entries.
 */
व्योम __init e820__रेजिस्टर_nosave_regions(अचिन्हित दीर्घ limit_pfn)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ pfn = 0;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];

		अगर (pfn < PFN_UP(entry->addr))
			रेजिस्टर_nosave_region(pfn, PFN_UP(entry->addr));

		pfn = PFN_DOWN(entry->addr + entry->size);

		अगर (entry->type != E820_TYPE_RAM && entry->type != E820_TYPE_RESERVED_KERN)
			रेजिस्टर_nosave_region(PFN_UP(entry->addr), pfn);

		अगर (pfn >= limit_pfn)
			अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI
/*
 * Register ACPI NVS memory regions, so that we can save/restore them during
 * hibernation and the subsequent resume:
 */
अटल पूर्णांक __init e820__रेजिस्टर_nvs_regions(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];

		अगर (entry->type == E820_TYPE_NVS)
			acpi_nvs_रेजिस्टर(entry->addr, entry->size);
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(e820__रेजिस्टर_nvs_regions);
#पूर्ण_अगर

/*
 * Allocate the requested number of bytes with the requested alignment
 * and वापस (the physical address) to the caller. Also रेजिस्टर this
 * range in the 'kexec' E820 table as a reserved range.
 *
 * This allows kexec to fake a new mptable, as अगर it came from the real
 * प्रणाली.
 */
u64 __init e820__memblock_alloc_reserved(u64 size, u64 align)
अणु
	u64 addr;

	addr = memblock_phys_alloc(size, align);
	अगर (addr) अणु
		e820__range_update_kexec(addr, size, E820_TYPE_RAM, E820_TYPE_RESERVED);
		pr_info("update e820_table_kexec for e820__memblock_alloc_reserved()\n");
		e820__update_table_kexec();
	पूर्ण

	वापस addr;
पूर्ण

#अगर_घोषित CONFIG_X86_32
# अगरdef CONFIG_X86_PAE
#  define MAX_ARCH_PFN		(1ULL<<(36-PAGE_SHIFT))
# अन्यथा
#  define MAX_ARCH_PFN		(1ULL<<(32-PAGE_SHIFT))
# endअगर
#अन्यथा /* CONFIG_X86_32 */
# define MAX_ARCH_PFN MAXMEM>>PAGE_SHIFT
#पूर्ण_अगर

/*
 * Find the highest page frame number we have available
 */
अटल अचिन्हित दीर्घ __init e820_end_pfn(अचिन्हित दीर्घ limit_pfn, क्रमागत e820_type type)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ last_pfn = 0;
	अचिन्हित दीर्घ max_arch_pfn = MAX_ARCH_PFN;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];
		अचिन्हित दीर्घ start_pfn;
		अचिन्हित दीर्घ end_pfn;

		अगर (entry->type != type)
			जारी;

		start_pfn = entry->addr >> PAGE_SHIFT;
		end_pfn = (entry->addr + entry->size) >> PAGE_SHIFT;

		अगर (start_pfn >= limit_pfn)
			जारी;
		अगर (end_pfn > limit_pfn) अणु
			last_pfn = limit_pfn;
			अवरोध;
		पूर्ण
		अगर (end_pfn > last_pfn)
			last_pfn = end_pfn;
	पूर्ण

	अगर (last_pfn > max_arch_pfn)
		last_pfn = max_arch_pfn;

	pr_info("last_pfn = %#lx max_arch_pfn = %#lx\n",
		last_pfn, max_arch_pfn);
	वापस last_pfn;
पूर्ण

अचिन्हित दीर्घ __init e820__end_of_ram_pfn(व्योम)
अणु
	वापस e820_end_pfn(MAX_ARCH_PFN, E820_TYPE_RAM);
पूर्ण

अचिन्हित दीर्घ __init e820__end_of_low_ram_pfn(व्योम)
अणु
	वापस e820_end_pfn(1UL << (32 - PAGE_SHIFT), E820_TYPE_RAM);
पूर्ण

अटल व्योम __init early_panic(अक्षर *msg)
अणु
	early_prपूर्णांकk(msg);
	panic(msg);
पूर्ण

अटल पूर्णांक userdef __initdata;

/* The "mem=nopentium" boot option disables 4MB page tables on 32-bit kernels: */
अटल पूर्णांक __init parse_memopt(अक्षर *p)
अणु
	u64 mem_size;

	अगर (!p)
		वापस -EINVAL;

	अगर (!म_भेद(p, "nopentium")) अणु
#अगर_घोषित CONFIG_X86_32
		setup_clear_cpu_cap(X86_FEATURE_PSE);
		वापस 0;
#अन्यथा
		pr_warn("mem=nopentium ignored! (only supported on x86_32)\n");
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण

	userdef = 1;
	mem_size = memparse(p, &p);

	/* Don't हटाओ all memory when getting "mem={invalid}" parameter: */
	अगर (mem_size == 0)
		वापस -EINVAL;

	e820__range_हटाओ(mem_size, ULदीर्घ_उच्च - mem_size, E820_TYPE_RAM, 1);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	max_mem_size = mem_size;
#पूर्ण_अगर

	वापस 0;
पूर्ण
early_param("mem", parse_memopt);

अटल पूर्णांक __init parse_memmap_one(अक्षर *p)
अणु
	अक्षर *oldp;
	u64 start_at, mem_size;

	अगर (!p)
		वापस -EINVAL;

	अगर (!म_भेदन(p, "exactmap", 8)) अणु
		e820_table->nr_entries = 0;
		userdef = 1;
		वापस 0;
	पूर्ण

	oldp = p;
	mem_size = memparse(p, &p);
	अगर (p == oldp)
		वापस -EINVAL;

	userdef = 1;
	अगर (*p == '@') अणु
		start_at = memparse(p+1, &p);
		e820__range_add(start_at, mem_size, E820_TYPE_RAM);
	पूर्ण अन्यथा अगर (*p == '#') अणु
		start_at = memparse(p+1, &p);
		e820__range_add(start_at, mem_size, E820_TYPE_ACPI);
	पूर्ण अन्यथा अगर (*p == '$') अणु
		start_at = memparse(p+1, &p);
		e820__range_add(start_at, mem_size, E820_TYPE_RESERVED);
	पूर्ण अन्यथा अगर (*p == '!') अणु
		start_at = memparse(p+1, &p);
		e820__range_add(start_at, mem_size, E820_TYPE_PRAM);
	पूर्ण अन्यथा अगर (*p == '%') अणु
		क्रमागत e820_type from = 0, to = 0;

		start_at = memparse(p + 1, &p);
		अगर (*p == '-')
			from = simple_म_से_अदीर्घl(p + 1, &p, 0);
		अगर (*p == '+')
			to = simple_म_से_अदीर्घl(p + 1, &p, 0);
		अगर (*p != '\0')
			वापस -EINVAL;
		अगर (from && to)
			e820__range_update(start_at, mem_size, from, to);
		अन्यथा अगर (to)
			e820__range_add(start_at, mem_size, to);
		अन्यथा अगर (from)
			e820__range_हटाओ(start_at, mem_size, from, 1);
		अन्यथा
			e820__range_हटाओ(start_at, mem_size, 0, 0);
	पूर्ण अन्यथा अणु
		e820__range_हटाओ(mem_size, ULदीर्घ_उच्च - mem_size, E820_TYPE_RAM, 1);
	पूर्ण

	वापस *p == '\0' ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक __init parse_memmap_opt(अक्षर *str)
अणु
	जबतक (str) अणु
		अक्षर *k = म_अक्षर(str, ',');

		अगर (k)
			*k++ = 0;

		parse_memmap_one(str);
		str = k;
	पूर्ण

	वापस 0;
पूर्ण
early_param("memmap", parse_memmap_opt);

/*
 * Reserve all entries from the bootloader's extensible data nodes list,
 * because अगर present we are going to use it later on to fetch e820
 * entries from it:
 */
व्योम __init e820__reserve_setup_data(व्योम)
अणु
	काष्ठा setup_data *data;
	u64 pa_data;

	pa_data = boot_params.hdr.setup_data;
	अगर (!pa_data)
		वापस;

	जबतक (pa_data) अणु
		data = early_memremap(pa_data, माप(*data));
		e820__range_update(pa_data, माप(*data)+data->len, E820_TYPE_RAM, E820_TYPE_RESERVED_KERN);

		/*
		 * SETUP_EFI is supplied by kexec and करोes not need to be
		 * reserved.
		 */
		अगर (data->type != SETUP_EFI)
			e820__range_update_kexec(pa_data,
						 माप(*data) + data->len,
						 E820_TYPE_RAM, E820_TYPE_RESERVED_KERN);

		अगर (data->type == SETUP_INसूचीECT &&
		    ((काष्ठा setup_indirect *)data->data)->type != SETUP_INसूचीECT) अणु
			e820__range_update(((काष्ठा setup_indirect *)data->data)->addr,
					   ((काष्ठा setup_indirect *)data->data)->len,
					   E820_TYPE_RAM, E820_TYPE_RESERVED_KERN);
			e820__range_update_kexec(((काष्ठा setup_indirect *)data->data)->addr,
						 ((काष्ठा setup_indirect *)data->data)->len,
						 E820_TYPE_RAM, E820_TYPE_RESERVED_KERN);
		पूर्ण

		pa_data = data->next;
		early_memunmap(data, माप(*data));
	पूर्ण

	e820__update_table(e820_table);
	e820__update_table(e820_table_kexec);

	pr_info("extended physical RAM map:\n");
	e820__prपूर्णांक_table("reserve setup_data");
पूर्ण

/*
 * Called after parse_early_param(), after early parameters (such as mem=)
 * have been processed, in which हाल we alपढ़ोy have an E820 table filled in
 * via the parameter callback function(s), but it's not sorted and prपूर्णांकed yet:
 */
व्योम __init e820__finish_early_params(व्योम)
अणु
	अगर (userdef) अणु
		अगर (e820__update_table(e820_table) < 0)
			early_panic("Invalid user supplied memory map");

		pr_info("user-defined physical RAM map:\n");
		e820__prपूर्णांक_table("user");
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *__init e820_type_to_string(काष्ठा e820_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल E820_TYPE_RESERVED_KERN:	/* Fall-through: */
	हाल E820_TYPE_RAM:		वापस "System RAM";
	हाल E820_TYPE_ACPI:		वापस "ACPI Tables";
	हाल E820_TYPE_NVS:		वापस "ACPI Non-volatile Storage";
	हाल E820_TYPE_UNUSABLE:	वापस "Unusable memory";
	हाल E820_TYPE_PRAM:		वापस "Persistent Memory (legacy)";
	हाल E820_TYPE_PMEM:		वापस "Persistent Memory";
	हाल E820_TYPE_RESERVED:	वापस "Reserved";
	हाल E820_TYPE_SOFT_RESERVED:	वापस "Soft Reserved";
	शेष:			वापस "Unknown E820 type";
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ __init e820_type_to_iomem_type(काष्ठा e820_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल E820_TYPE_RESERVED_KERN:	/* Fall-through: */
	हाल E820_TYPE_RAM:		वापस IORESOURCE_SYSTEM_RAM;
	हाल E820_TYPE_ACPI:		/* Fall-through: */
	हाल E820_TYPE_NVS:		/* Fall-through: */
	हाल E820_TYPE_UNUSABLE:	/* Fall-through: */
	हाल E820_TYPE_PRAM:		/* Fall-through: */
	हाल E820_TYPE_PMEM:		/* Fall-through: */
	हाल E820_TYPE_RESERVED:	/* Fall-through: */
	हाल E820_TYPE_SOFT_RESERVED:	/* Fall-through: */
	शेष:			वापस IORESOURCE_MEM;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ __init e820_type_to_iores_desc(काष्ठा e820_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल E820_TYPE_ACPI:		वापस IORES_DESC_ACPI_TABLES;
	हाल E820_TYPE_NVS:		वापस IORES_DESC_ACPI_NV_STORAGE;
	हाल E820_TYPE_PMEM:		वापस IORES_DESC_PERSISTENT_MEMORY;
	हाल E820_TYPE_PRAM:		वापस IORES_DESC_PERSISTENT_MEMORY_LEGACY;
	हाल E820_TYPE_RESERVED:	वापस IORES_DESC_RESERVED;
	हाल E820_TYPE_SOFT_RESERVED:	वापस IORES_DESC_SOFT_RESERVED;
	हाल E820_TYPE_RESERVED_KERN:	/* Fall-through: */
	हाल E820_TYPE_RAM:		/* Fall-through: */
	हाल E820_TYPE_UNUSABLE:	/* Fall-through: */
	शेष:			वापस IORES_DESC_NONE;
	पूर्ण
पूर्ण

अटल bool __init करो_mark_busy(क्रमागत e820_type type, काष्ठा resource *res)
अणु
	/* this is the legacy bios/करोs rom-shaकरोw + mmio region */
	अगर (res->start < (1ULL<<20))
		वापस true;

	/*
	 * Treat persistent memory and other special memory ranges like
	 * device memory, i.e. reserve it क्रम exclusive use of a driver
	 */
	चयन (type) अणु
	हाल E820_TYPE_RESERVED:
	हाल E820_TYPE_SOFT_RESERVED:
	हाल E820_TYPE_PRAM:
	हाल E820_TYPE_PMEM:
		वापस false;
	हाल E820_TYPE_RESERVED_KERN:
	हाल E820_TYPE_RAM:
	हाल E820_TYPE_ACPI:
	हाल E820_TYPE_NVS:
	हाल E820_TYPE_UNUSABLE:
	शेष:
		वापस true;
	पूर्ण
पूर्ण

/*
 * Mark E820 reserved areas as busy क्रम the resource manager:
 */

अटल काष्ठा resource __initdata *e820_res;

व्योम __init e820__reserve_resources(व्योम)
अणु
	पूर्णांक i;
	काष्ठा resource *res;
	u64 end;

	res = memblock_alloc(माप(*res) * e820_table->nr_entries,
			     SMP_CACHE_BYTES);
	अगर (!res)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*res) * e820_table->nr_entries);
	e820_res = res;

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = e820_table->entries + i;

		end = entry->addr + entry->size - 1;
		अगर (end != (resource_माप_प्रकार)end) अणु
			res++;
			जारी;
		पूर्ण
		res->start = entry->addr;
		res->end   = end;
		res->name  = e820_type_to_string(entry);
		res->flags = e820_type_to_iomem_type(entry);
		res->desc  = e820_type_to_iores_desc(entry);

		/*
		 * Don't रेजिस्टर the region that could be conflicted with
		 * PCI device BAR resources and insert them later in
		 * pcibios_resource_survey():
		 */
		अगर (करो_mark_busy(entry->type, res)) अणु
			res->flags |= IORESOURCE_BUSY;
			insert_resource(&iomem_resource, res);
		पूर्ण
		res++;
	पूर्ण

	/* Expose the bootloader-provided memory layout to the sysfs. */
	क्रम (i = 0; i < e820_table_firmware->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = e820_table_firmware->entries + i;

		firmware_map_add_early(entry->addr, entry->addr + entry->size, e820_type_to_string(entry));
	पूर्ण
पूर्ण

/*
 * How much should we pad the end of RAM, depending on where it is?
 */
अटल अचिन्हित दीर्घ __init ram_alignment(resource_माप_प्रकार pos)
अणु
	अचिन्हित दीर्घ mb = pos >> 20;

	/* To 64kB in the first megabyte */
	अगर (!mb)
		वापस 64*1024;

	/* To 1MB in the first 16MB */
	अगर (mb < 16)
		वापस 1024*1024;

	/* To 64MB क्रम anything above that */
	वापस 64*1024*1024;
पूर्ण

#घोषणा MAX_RESOURCE_SIZE ((resource_माप_प्रकार)-1)

व्योम __init e820__reserve_resources_late(व्योम)
अणु
	पूर्णांक i;
	काष्ठा resource *res;

	res = e820_res;
	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		अगर (!res->parent && res->end)
			insert_resource_expand_to_fit(&iomem_resource, res);
		res++;
	पूर्ण

	/*
	 * Try to bump up RAM regions to reasonable boundaries, to
	 * aव्योम stolen RAM:
	 */
	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];
		u64 start, end;

		अगर (entry->type != E820_TYPE_RAM)
			जारी;

		start = entry->addr + entry->size;
		end = round_up(start, ram_alignment(start)) - 1;
		अगर (end > MAX_RESOURCE_SIZE)
			end = MAX_RESOURCE_SIZE;
		अगर (start >= end)
			जारी;

		prपूर्णांकk(KERN_DEBUG "e820: reserve RAM buffer [mem %#010llx-%#010llx]\n", start, end);
		reserve_region_with_split(&iomem_resource, start, end, "RAM buffer");
	पूर्ण
पूर्ण

/*
 * Pass the firmware (bootloader) E820 map to the kernel and process it:
 */
अक्षर *__init e820__memory_setup_शेष(व्योम)
अणु
	अक्षर *who = "BIOS-e820";

	/*
	 * Try to copy the BIOS-supplied E820-map.
	 *
	 * Otherwise fake a memory map; one section from 0k->640k,
	 * the next section from 1mb->appropriate_mem_k
	 */
	अगर (append_e820_table(boot_params.e820_table, boot_params.e820_entries) < 0) अणु
		u64 mem_size;

		/* Compare results from other methods and take the one that gives more RAM: */
		अगर (boot_params.alt_mem_k < boot_params.screen_info.ext_mem_k) अणु
			mem_size = boot_params.screen_info.ext_mem_k;
			who = "BIOS-88";
		पूर्ण अन्यथा अणु
			mem_size = boot_params.alt_mem_k;
			who = "BIOS-e801";
		पूर्ण

		e820_table->nr_entries = 0;
		e820__range_add(0, LOWMEMSIZE(), E820_TYPE_RAM);
		e820__range_add(HIGH_MEMORY, mem_size << 10, E820_TYPE_RAM);
	पूर्ण

	/* We just appended a lot of ranges, sanitize the table: */
	e820__update_table(e820_table);

	वापस who;
पूर्ण

/*
 * Calls e820__memory_setup_शेष() in essence to pick up the firmware/bootloader
 * E820 map - with an optional platक्रमm quirk available क्रम भव platक्रमms
 * to override this method of boot environment processing:
 */
व्योम __init e820__memory_setup(व्योम)
अणु
	अक्षर *who;

	/* This is a firmware पूर्णांकerface ABI - make sure we करोn't अवरोध it: */
	BUILD_BUG_ON(माप(काष्ठा boot_e820_entry) != 20);

	who = x86_init.resources.memory_setup();

	स_नकल(e820_table_kexec, e820_table, माप(*e820_table_kexec));
	स_नकल(e820_table_firmware, e820_table, माप(*e820_table_firmware));

	pr_info("BIOS-provided physical RAM map:\n");
	e820__prपूर्णांक_table(who);
पूर्ण

व्योम __init e820__memblock_setup(व्योम)
अणु
	पूर्णांक i;
	u64 end;

	/*
	 * The bootstrap memblock region count maximum is 128 entries
	 * (INIT_MEMBLOCK_REGIONS), but EFI might pass us more E820 entries
	 * than that - so allow memblock resizing.
	 *
	 * This is safe, because this call happens pretty late during x86 setup,
	 * so we know about reserved memory regions alपढ़ोy. (This is important
	 * so that memblock resizing करोes no stomp over reserved areas.)
	 */
	memblock_allow_resize();

	क्रम (i = 0; i < e820_table->nr_entries; i++) अणु
		काष्ठा e820_entry *entry = &e820_table->entries[i];

		end = entry->addr + entry->size;
		अगर (end != (resource_माप_प्रकार)end)
			जारी;

		अगर (entry->type == E820_TYPE_SOFT_RESERVED)
			memblock_reserve(entry->addr, entry->size);

		अगर (entry->type != E820_TYPE_RAM && entry->type != E820_TYPE_RESERVED_KERN)
			जारी;

		memblock_add(entry->addr, entry->size);
	पूर्ण

	/* Throw away partial pages: */
	memblock_trim_memory(PAGE_SIZE);

	memblock_dump_all();
पूर्ण
