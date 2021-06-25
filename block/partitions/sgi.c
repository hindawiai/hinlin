<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/sgi.c
 *
 *  Code extracted from drivers/block/genhd.c
 */

#समावेश "check.h"

#घोषणा SGI_LABEL_MAGIC 0x0be5a941

क्रमागत अणु
	LINUX_RAID_PARTITION = 0xfd,	/* स्वतःdetect RAID partition */
पूर्ण;

काष्ठा sgi_disklabel अणु
	__be32 magic_mushroom;		/* Big fat splअगरf... */
	__be16 root_part_num;		/* Root partition number */
	__be16 swap_part_num;		/* Swap partition number */
	s8 boot_file[16];		/* Name of boot file क्रम ARCS */
	u8 _unused0[48];		/* Device parameter useless crapola.. */
	काष्ठा sgi_volume अणु
		s8 name[8];		/* Name of volume */
		__be32 block_num;		/* Logical block number */
		__be32 num_bytes;		/* How big, in bytes */
	पूर्ण volume[15];
	काष्ठा sgi_partition अणु
		__be32 num_blocks;		/* Size in logical blocks */
		__be32 first_block;	/* First logical block */
		__be32 type;		/* Type of this partition */
	पूर्ण partitions[16];
	__be32 csum;			/* Disk label checksum */
	__be32 _unused1;			/* Padding */
पूर्ण;

पूर्णांक sgi_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i, csum;
	__be32 magic;
	पूर्णांक slot = 1;
	अचिन्हित पूर्णांक start, blocks;
	__be32 *ui, cs;
	Sector sect;
	काष्ठा sgi_disklabel *label;
	काष्ठा sgi_partition *p;
	अक्षर b[BDEVNAME_SIZE];

	label = पढ़ो_part_sector(state, 0, &sect);
	अगर (!label)
		वापस -1;
	p = &label->partitions[0];
	magic = label->magic_mushroom;
	अगर(be32_to_cpu(magic) != SGI_LABEL_MAGIC) अणु
		/*prपूर्णांकk("Dev %s SGI disklabel: bad magic %08x\n",
		       bdevname(bdev, b), be32_to_cpu(magic));*/
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	ui = ((__be32 *) (label + 1)) - 1;
	क्रम(csum = 0; ui >= ((__be32 *) label);) अणु
		cs = *ui--;
		csum += be32_to_cpu(cs);
	पूर्ण
	अगर(csum) अणु
		prपूर्णांकk(KERN_WARNING "Dev %s SGI disklabel: csum bad, label corrupted\n",
		       bdevname(state->bdev, b));
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	/* All SGI disk labels have 16 partitions, disks under Linux only
	 * have 15 minor's.  Luckily there are always a few zero length
	 * partitions which we करोn't care about so we never overflow the
	 * current_minor.
	 */
	क्रम(i = 0; i < 16; i++, p++) अणु
		blocks = be32_to_cpu(p->num_blocks);
		start  = be32_to_cpu(p->first_block);
		अगर (blocks) अणु
			put_partition(state, slot, start, blocks);
			अगर (be32_to_cpu(p->type) == LINUX_RAID_PARTITION)
				state->parts[slot].flags = ADDPART_FLAG_RAID;
		पूर्ण
		slot++;
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sector(sect);
	वापस 1;
पूर्ण
