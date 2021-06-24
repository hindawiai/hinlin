<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2012 Fusion-io  All rights reserved.
 * Copyright (C) 2012 Intel Corp. All rights reserved.
 */

#अगर_अघोषित BTRFS_RAID56_H
#घोषणा BTRFS_RAID56_H

अटल अंतरभूत पूर्णांक nr_parity_stripes(स्थिर काष्ठा map_lookup *map)
अणु
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID5)
		वापस 1;
	अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID6)
		वापस 2;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nr_data_stripes(स्थिर काष्ठा map_lookup *map)
अणु
	वापस map->num_stripes - nr_parity_stripes(map);
पूर्ण
#घोषणा RAID5_P_STRIPE ((u64)-2)
#घोषणा RAID6_Q_STRIPE ((u64)-1)

#घोषणा is_parity_stripe(x) (((x) == RAID5_P_STRIPE) ||		\
			     ((x) == RAID6_Q_STRIPE))

काष्ठा btrfs_raid_bio;
काष्ठा btrfs_device;

पूर्णांक raid56_parity_recover(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			  काष्ठा btrfs_bio *bbio, u64 stripe_len,
			  पूर्णांक mirror_num, पूर्णांक generic_io);
पूर्णांक raid56_parity_ग_लिखो(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			       काष्ठा btrfs_bio *bbio, u64 stripe_len);

व्योम raid56_add_scrub_pages(काष्ठा btrfs_raid_bio *rbio, काष्ठा page *page,
			    u64 logical);

काष्ठा btrfs_raid_bio *
raid56_parity_alloc_scrub_rbio(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			       काष्ठा btrfs_bio *bbio, u64 stripe_len,
			       काष्ठा btrfs_device *scrub_dev,
			       अचिन्हित दीर्घ *dbiपंचांगap, पूर्णांक stripe_nsectors);
व्योम raid56_parity_submit_scrub_rbio(काष्ठा btrfs_raid_bio *rbio);

काष्ठा btrfs_raid_bio *
raid56_alloc_missing_rbio(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			  काष्ठा btrfs_bio *bbio, u64 length);
व्योम raid56_submit_missing_rbio(काष्ठा btrfs_raid_bio *rbio);

पूर्णांक btrfs_alloc_stripe_hash_table(काष्ठा btrfs_fs_info *info);
व्योम btrfs_मुक्त_stripe_hash_table(काष्ठा btrfs_fs_info *info);

#पूर्ण_अगर
