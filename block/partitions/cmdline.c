<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 HUAWEI
 * Author: Cai Zhiyong <caizhiyong@huawei.com>
 *
 * Read block device partition table from the command line.
 * Typically used क्रम fixed block (eMMC) embedded devices.
 * It has no MBR, so saves storage space. Bootloader can be easily accessed
 * by असलolute address of data on the block device.
 * Users can easily change the partition.
 *
 * The क्रमmat क्रम the command line is just like mtdparts.
 *
 * For further inक्रमmation, see "Documentation/block/cmdline-partition.rst"
 *
 */

#समावेश <linux/cmdline-parser.h>

#समावेश "check.h"

अटल अक्षर *cmdline;
अटल काष्ठा cmdline_parts *bdev_parts;

अटल पूर्णांक add_part(पूर्णांक slot, काष्ठा cmdline_subpart *subpart, व्योम *param)
अणु
	पूर्णांक label_min;
	काष्ठा partition_meta_info *info;
	अक्षर पंचांगp[माप(info->volname) + 4];
	काष्ठा parsed_partitions *state = (काष्ठा parsed_partitions *)param;

	अगर (slot >= state->limit)
		वापस 1;

	put_partition(state, slot, subpart->from >> 9,
		      subpart->size >> 9);

	info = &state->parts[slot].info;

	label_min = min_t(पूर्णांक, माप(info->volname) - 1,
			  माप(subpart->name));
	म_नकलन(info->volname, subpart->name, label_min);
	info->volname[label_min] = '\0';

	snम_लिखो(पंचांगp, माप(पंचांगp), "(%s)", info->volname);
	strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);

	state->parts[slot].has_info = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __init cmdline_parts_setup(अक्षर *s)
अणु
	cmdline = s;
	वापस 1;
पूर्ण
__setup("blkdevparts=", cmdline_parts_setup);

अटल bool has_overlaps(sector_t from, sector_t size,
			 sector_t from2, sector_t size2)
अणु
	sector_t end = from + size;
	sector_t end2 = from2 + size2;

	अगर (from >= from2 && from < end2)
		वापस true;

	अगर (end > from2 && end <= end2)
		वापस true;

	अगर (from2 >= from && from2 < end)
		वापस true;

	अगर (end2 > from && end2 <= end)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत व्योम overlaps_warns_header(व्योम)
अणु
	pr_warn("Overlapping partitions are used in command line partitions.");
	pr_warn("Don't use filesystems on overlapping partitions:");
पूर्ण

अटल व्योम cmdline_parts_verअगरier(पूर्णांक slot, काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i;
	bool header = true;

	क्रम (; slot < state->limit && state->parts[slot].has_info; slot++) अणु
		क्रम (i = slot+1; i < state->limit && state->parts[i].has_info;
		     i++) अणु
			अगर (has_overlaps(state->parts[slot].from,
					 state->parts[slot].size,
					 state->parts[i].from,
					 state->parts[i].size)) अणु
				अगर (header) अणु
					header = false;
					overlaps_warns_header();
				पूर्ण
				pr_warn("%s[%llu,%llu] overlaps with "
					"%s[%llu,%llu].",
					state->parts[slot].info.volname,
					(u64)state->parts[slot].from << 9,
					(u64)state->parts[slot].size << 9,
					state->parts[i].info.volname,
					(u64)state->parts[i].from << 9,
					(u64)state->parts[i].size << 9);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Purpose: allocate cmdline partitions.
 * Returns:
 * -1 अगर unable to पढ़ो the partition table
 *  0 अगर this isn't our partition table
 *  1 अगर successful
 */
पूर्णांक cmdline_partition(काष्ठा parsed_partitions *state)
अणु
	sector_t disk_size;
	अक्षर bdev[BDEVNAME_SIZE];
	काष्ठा cmdline_parts *parts;

	अगर (cmdline) अणु
		अगर (bdev_parts)
			cmdline_parts_मुक्त(&bdev_parts);

		अगर (cmdline_parts_parse(&bdev_parts, cmdline)) अणु
			cmdline = शून्य;
			वापस -1;
		पूर्ण
		cmdline = शून्य;
	पूर्ण

	अगर (!bdev_parts)
		वापस 0;

	bdevname(state->bdev, bdev);
	parts = cmdline_parts_find(bdev_parts, bdev);
	अगर (!parts)
		वापस 0;

	disk_size = get_capacity(state->bdev->bd_disk) << 9;

	cmdline_parts_set(parts, disk_size, 1, add_part, (व्योम *)state);
	cmdline_parts_verअगरier(1, state);

	strlcat(state->pp_buf, "\n", PAGE_SIZE);

	वापस 1;
पूर्ण
