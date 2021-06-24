<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/mac.c
 *
 *  Code extracted from drivers/block/genhd.c
 *  Copyright (C) 1991-1998  Linus Torvalds
 *  Re-organised Feb 1998 Russell King
 */

#समावेश <linux/प्रकार.स>
#समावेश "check.h"
#समावेश "mac.h"

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/machdep.h>
बाह्य व्योम note_bootable_part(dev_t dev, पूर्णांक part, पूर्णांक goodness);
#पूर्ण_अगर

/*
 * Code to understand MacOS partition tables.
 */

अटल अंतरभूत व्योम mac_fix_string(अक्षर *stg, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = len - 1; i >= 0 && stg[i] == ' '; i--)
		stg[i] = 0;
पूर्ण

पूर्णांक mac_partition(काष्ठा parsed_partitions *state)
अणु
	Sector sect;
	अचिन्हित अक्षर *data;
	पूर्णांक slot, blocks_in_map;
	अचिन्हित secsize, datasize, partoffset;
#अगर_घोषित CONFIG_PPC_PMAC
	पूर्णांक found_root = 0;
	पूर्णांक found_root_goodness = 0;
#पूर्ण_अगर
	काष्ठा mac_partition *part;
	काष्ठा mac_driver_desc *md;

	/* Get 0th block and look at the first partition map entry. */
	md = पढ़ो_part_sector(state, 0, &sect);
	अगर (!md)
		वापस -1;
	अगर (be16_to_cpu(md->signature) != MAC_DRIVER_MAGIC) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	secsize = be16_to_cpu(md->block_size);
	put_dev_sector(sect);
	datasize = round_करोwn(secsize, 512);
	data = पढ़ो_part_sector(state, datasize / 512, &sect);
	अगर (!data)
		वापस -1;
	partoffset = secsize % 512;
	अगर (partoffset + माप(*part) > datasize)
		वापस -1;
	part = (काष्ठा mac_partition *) (data + partoffset);
	अगर (be16_to_cpu(part->signature) != MAC_PARTITION_MAGIC) अणु
		put_dev_sector(sect);
		वापस 0;		/* not a MacOS disk */
	पूर्ण
	blocks_in_map = be32_to_cpu(part->map_count);
	अगर (blocks_in_map < 0 || blocks_in_map >= DISK_MAX_PARTS) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण

	अगर (blocks_in_map >= state->limit)
		blocks_in_map = state->limit - 1;

	strlcat(state->pp_buf, " [mac]", PAGE_SIZE);
	क्रम (slot = 1; slot <= blocks_in_map; ++slot) अणु
		पूर्णांक pos = slot * secsize;
		put_dev_sector(sect);
		data = पढ़ो_part_sector(state, pos/512, &sect);
		अगर (!data)
			वापस -1;
		part = (काष्ठा mac_partition *) (data + pos%512);
		अगर (be16_to_cpu(part->signature) != MAC_PARTITION_MAGIC)
			अवरोध;
		put_partition(state, slot,
			be32_to_cpu(part->start_block) * (secsize/512),
			be32_to_cpu(part->block_count) * (secsize/512));

		अगर (!strnहालcmp(part->type, "Linux_RAID", 10))
			state->parts[slot].flags = ADDPART_FLAG_RAID;
#अगर_घोषित CONFIG_PPC_PMAC
		/*
		 * If this is the first bootable partition, tell the
		 * setup code, in हाल it wants to make this the root.
		 */
		अगर (machine_is(घातermac)) अणु
			पूर्णांक goodness = 0;

			mac_fix_string(part->processor, 16);
			mac_fix_string(part->name, 32);
			mac_fix_string(part->type, 32);					
		    
			अगर ((be32_to_cpu(part->status) & MAC_STATUS_BOOTABLE)
			    && strहालcmp(part->processor, "powerpc") == 0)
				goodness++;

			अगर (strहालcmp(part->type, "Apple_UNIX_SVR2") == 0
			    || (strnहालcmp(part->type, "Linux", 5) == 0
			        && strहालcmp(part->type, "Linux_swap") != 0)) अणु
				पूर्णांक i, l;

				goodness++;
				l = म_माप(part->name);
				अगर (म_भेद(part->name, "/") == 0)
					goodness++;
				क्रम (i = 0; i <= l - 4; ++i) अणु
					अगर (strnहालcmp(part->name + i, "root",
						     4) == 0) अणु
						goodness += 2;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर (strnहालcmp(part->name, "swap", 4) == 0)
					goodness--;
			पूर्ण

			अगर (goodness > found_root_goodness) अणु
				found_root = slot;
				found_root_goodness = goodness;
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
	पूर्ण
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (found_root_goodness)
		note_bootable_part(state->bdev->bd_dev, found_root,
				   found_root_goodness);
#पूर्ण_अगर

	put_dev_sector(sect);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण
