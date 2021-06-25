<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Parsing command line, get the partitions inक्रमmation.
 *
 * Written by Cai Zhiyong <caizhiyong@huawei.com>
 *
 */
#अगर_अघोषित CMDLINEPARSEH
#घोषणा CMDLINEPARSEH

#समावेश <linux/blkdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>

/* partition flags */
#घोषणा PF_RDONLY                   0x01 /* Device is पढ़ो only */
#घोषणा PF_POWERUP_LOCK             0x02 /* Always locked after reset */

काष्ठा cmdline_subpart अणु
	अक्षर name[BDEVNAME_SIZE]; /* partition name, such as 'rootfs' */
	sector_t from;
	sector_t size;
	पूर्णांक flags;
	काष्ठा cmdline_subpart *next_subpart;
पूर्ण;

काष्ठा cmdline_parts अणु
	अक्षर name[BDEVNAME_SIZE]; /* block device, such as 'mmcblk0' */
	अचिन्हित पूर्णांक nr_subparts;
	काष्ठा cmdline_subpart *subpart;
	काष्ठा cmdline_parts *next_parts;
पूर्ण;

व्योम cmdline_parts_मुक्त(काष्ठा cmdline_parts **parts);

पूर्णांक cmdline_parts_parse(काष्ठा cmdline_parts **parts, स्थिर अक्षर *cmdline);

काष्ठा cmdline_parts *cmdline_parts_find(काष्ठा cmdline_parts *parts,
					 स्थिर अक्षर *bdev);

पूर्णांक cmdline_parts_set(काष्ठा cmdline_parts *parts, sector_t disk_size,
		      पूर्णांक slot,
		      पूर्णांक (*add_part)(पूर्णांक, काष्ठा cmdline_subpart *, व्योम *),
		      व्योम *param);

#पूर्ण_अगर /* CMDLINEPARSEH */
