<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STRATO AG 2011.  All rights reserved.
 */

#अगर_अघोषित BTRFS_CHECK_INTEGRITY_H
#घोषणा BTRFS_CHECK_INTEGRITY_H

#अगर_घोषित CONFIG_BTRFS_FS_CHECK_INTEGRITY
व्योम btrfsic_submit_bio(काष्ठा bio *bio);
पूर्णांक btrfsic_submit_bio_रुको(काष्ठा bio *bio);
#अन्यथा
#घोषणा btrfsic_submit_bio submit_bio
#घोषणा btrfsic_submit_bio_रुको submit_bio_रुको
#पूर्ण_अगर

पूर्णांक btrfsic_mount(काष्ठा btrfs_fs_info *fs_info,
		  काष्ठा btrfs_fs_devices *fs_devices,
		  पूर्णांक including_extent_data, u32 prपूर्णांक_mask);
व्योम btrfsic_unmount(काष्ठा btrfs_fs_devices *fs_devices);

#पूर्ण_अगर
