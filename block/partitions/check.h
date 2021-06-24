<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/pagemap.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/genhd.h>
#समावेश "../blk.h"

/*
 * add_gd_partition adds a partitions details to the devices partition
 * description.
 */
काष्ठा parsed_partitions अणु
	काष्ठा block_device *bdev;
	अक्षर name[BDEVNAME_SIZE];
	काष्ठा अणु
		sector_t from;
		sector_t size;
		पूर्णांक flags;
		bool has_info;
		काष्ठा partition_meta_info info;
	पूर्ण *parts;
	पूर्णांक next;
	पूर्णांक limit;
	bool access_beyond_eod;
	अक्षर *pp_buf;
पूर्ण;

प्रकार काष्ठा अणु
	काष्ठा page *v;
पूर्ण Sector;

व्योम *पढ़ो_part_sector(काष्ठा parsed_partitions *state, sector_t n, Sector *p);
अटल अंतरभूत व्योम put_dev_sector(Sector p)
अणु
	put_page(p.v);
पूर्ण

अटल अंतरभूत व्योम
put_partition(काष्ठा parsed_partitions *p, पूर्णांक n, sector_t from, sector_t size)
अणु
	अगर (n < p->limit) अणु
		अक्षर पंचांगp[1 + BDEVNAME_SIZE + 10 + 1];

		p->parts[n].from = from;
		p->parts[n].size = size;
		snम_लिखो(पंचांगp, माप(पंचांगp), " %s%d", p->name, n);
		strlcat(p->pp_buf, पंचांगp, PAGE_SIZE);
	पूर्ण
पूर्ण

/* detection routines go here in alphabetical order: */
पूर्णांक adfspart_check_ADFS(काष्ठा parsed_partitions *state);
पूर्णांक adfspart_check_CUMANA(काष्ठा parsed_partitions *state);
पूर्णांक adfspart_check_EESOX(काष्ठा parsed_partitions *state);
पूर्णांक adfspart_check_ICS(काष्ठा parsed_partitions *state);
पूर्णांक adfspart_check_POWERTEC(काष्ठा parsed_partitions *state);
पूर्णांक aix_partition(काष्ठा parsed_partitions *state);
पूर्णांक amiga_partition(काष्ठा parsed_partitions *state);
पूर्णांक atari_partition(काष्ठा parsed_partitions *state);
पूर्णांक cmdline_partition(काष्ठा parsed_partitions *state);
पूर्णांक efi_partition(काष्ठा parsed_partitions *state);
पूर्णांक ibm_partition(काष्ठा parsed_partitions *);
पूर्णांक karma_partition(काष्ठा parsed_partitions *state);
पूर्णांक ldm_partition(काष्ठा parsed_partitions *state);
पूर्णांक mac_partition(काष्ठा parsed_partitions *state);
पूर्णांक msकरोs_partition(काष्ठा parsed_partitions *state);
पूर्णांक osf_partition(काष्ठा parsed_partitions *state);
पूर्णांक sgi_partition(काष्ठा parsed_partitions *state);
पूर्णांक sun_partition(काष्ठा parsed_partitions *state);
पूर्णांक sysv68_partition(काष्ठा parsed_partitions *state);
पूर्णांक ultrix_partition(काष्ठा parsed_partitions *state);
