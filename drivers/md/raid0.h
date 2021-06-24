<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RAID0_H
#घोषणा _RAID0_H

काष्ठा strip_zone अणु
	sector_t zone_end;	/* Start of the next zone (in sectors) */
	sector_t dev_start;	/* Zone offset in real dev (in sectors) */
	पूर्णांक	 nb_dev;	/* # of devices attached to the zone */
पूर्ण;

/* Linux 3.14 (20d0189b101) made an unपूर्णांकended change to
 * the RAID0 layout क्रम multi-zone arrays (where devices aren't all
 * the same size.
 * RAID0_ORIG_LAYOUT restores the original layout
 * RAID0_ALT_MULTIZONE_LAYOUT uses the altered layout
 * The layouts are identical when there is only one zone (all
 * devices the same size).
 */

क्रमागत r0layout अणु
	RAID0_ORIG_LAYOUT = 1,
	RAID0_ALT_MULTIZONE_LAYOUT = 2,
पूर्ण;
काष्ठा r0conf अणु
	काष्ठा strip_zone	*strip_zone;
	काष्ठा md_rdev		**devlist; /* lists of rdevs, poपूर्णांकed to
					    * by strip_zone->dev */
	पूर्णांक			nr_strip_zones;
	क्रमागत r0layout		layout;
पूर्ण;

#पूर्ण_अगर
