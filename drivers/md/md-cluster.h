<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */


#अगर_अघोषित _MD_CLUSTER_H
#घोषणा _MD_CLUSTER_H

#समावेश "md.h"

काष्ठा mddev;
काष्ठा md_rdev;

काष्ठा md_cluster_operations अणु
	पूर्णांक (*join)(काष्ठा mddev *mddev, पूर्णांक nodes);
	पूर्णांक (*leave)(काष्ठा mddev *mddev);
	पूर्णांक (*slot_number)(काष्ठा mddev *mddev);
	पूर्णांक (*resync_info_update)(काष्ठा mddev *mddev, sector_t lo, sector_t hi);
	व्योम (*resync_info_get)(काष्ठा mddev *mddev, sector_t *lo, sector_t *hi);
	पूर्णांक (*metadata_update_start)(काष्ठा mddev *mddev);
	पूर्णांक (*metadata_update_finish)(काष्ठा mddev *mddev);
	व्योम (*metadata_update_cancel)(काष्ठा mddev *mddev);
	पूर्णांक (*resync_start)(काष्ठा mddev *mddev);
	पूर्णांक (*resync_finish)(काष्ठा mddev *mddev);
	पूर्णांक (*area_resyncing)(काष्ठा mddev *mddev, पूर्णांक direction, sector_t lo, sector_t hi);
	पूर्णांक (*add_new_disk)(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
	व्योम (*add_new_disk_cancel)(काष्ठा mddev *mddev);
	पूर्णांक (*new_disk_ack)(काष्ठा mddev *mddev, bool ack);
	पूर्णांक (*हटाओ_disk)(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
	व्योम (*load_biपंचांगaps)(काष्ठा mddev *mddev, पूर्णांक total_slots);
	पूर्णांक (*gather_biपंचांगaps)(काष्ठा md_rdev *rdev);
	पूर्णांक (*resize_biपंचांगaps)(काष्ठा mddev *mddev, sector_t newsize, sector_t oldsize);
	पूर्णांक (*lock_all_biपंचांगaps)(काष्ठा mddev *mddev);
	व्योम (*unlock_all_biपंचांगaps)(काष्ठा mddev *mddev);
	व्योम (*update_size)(काष्ठा mddev *mddev, sector_t old_dev_sectors);
पूर्ण;

#पूर्ण_अगर /* _MD_CLUSTER_H */
