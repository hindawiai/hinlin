<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   raid0.c : Multiple Devices driver क्रम Linux
	     Copyright (C) 1994-96 Marc ZYNGIER
	     <zyngier@ufr-info-p7.ibp.fr> or
	     <maz@gloups.fdn.fr>
	     Copyright (C) 1999, 2000 Ingo Molnar, Red Hat

   RAID-0 management functions.

*/

#समावेश <linux/blkdev.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <trace/events/block.h>
#समावेश "md.h"
#समावेश "raid0.h"
#समावेश "raid5.h"

अटल पूर्णांक शेष_layout = 0;
module_param(शेष_layout, पूर्णांक, 0644);

#घोषणा UNSUPPORTED_MDDEV_FLAGS		\
	((1L << MD_HAS_JOURNAL) |	\
	 (1L << MD_JOURNAL_CLEAN) |	\
	 (1L << MD_FAILFAST_SUPPORTED) |\
	 (1L << MD_HAS_PPL) |		\
	 (1L << MD_HAS_MULTIPLE_PPLS))

/*
 * inक्रमm the user of the raid configuration
*/
अटल व्योम dump_zones(काष्ठा mddev *mddev)
अणु
	पूर्णांक j, k;
	sector_t zone_size = 0;
	sector_t zone_start = 0;
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा r0conf *conf = mddev->निजी;
	पूर्णांक raid_disks = conf->strip_zone[0].nb_dev;
	pr_debug("md: RAID0 configuration for %s - %d zone%s\n",
		 mdname(mddev),
		 conf->nr_strip_zones, conf->nr_strip_zones==1?"":"s");
	क्रम (j = 0; j < conf->nr_strip_zones; j++) अणु
		अक्षर line[200];
		पूर्णांक len = 0;

		क्रम (k = 0; k < conf->strip_zone[j].nb_dev; k++)
			len += snम_लिखो(line+len, 200-len, "%s%s", k?"/":"",
					bdevname(conf->devlist[j*raid_disks
							       + k]->bdev, b));
		pr_debug("md: zone%d=[%s]\n", j, line);

		zone_size  = conf->strip_zone[j].zone_end - zone_start;
		pr_debug("      zone-offset=%10lluKB, device-offset=%10lluKB, size=%10lluKB\n",
			(अचिन्हित दीर्घ दीर्घ)zone_start>>1,
			(अचिन्हित दीर्घ दीर्घ)conf->strip_zone[j].dev_start>>1,
			(अचिन्हित दीर्घ दीर्घ)zone_size>>1);
		zone_start = conf->strip_zone[j].zone_end;
	पूर्ण
पूर्ण

अटल पूर्णांक create_strip_zones(काष्ठा mddev *mddev, काष्ठा r0conf **निजी_conf)
अणु
	पूर्णांक i, c, err;
	sector_t curr_zone_end, sectors;
	काष्ठा md_rdev *smallest, *rdev1, *rdev2, *rdev, **dev;
	काष्ठा strip_zone *zone;
	पूर्णांक cnt;
	अक्षर b[BDEVNAME_SIZE];
	अक्षर b2[BDEVNAME_SIZE];
	काष्ठा r0conf *conf = kzalloc(माप(*conf), GFP_KERNEL);
	अचिन्हित blksize = 512;

	*निजी_conf = ERR_PTR(-ENOMEM);
	अगर (!conf)
		वापस -ENOMEM;
	rdev_क्रम_each(rdev1, mddev) अणु
		pr_debug("md/raid0:%s: looking at %s\n",
			 mdname(mddev),
			 bdevname(rdev1->bdev, b));
		c = 0;

		/* round size to chunk_size */
		sectors = rdev1->sectors;
		sector_भाग(sectors, mddev->chunk_sectors);
		rdev1->sectors = sectors * mddev->chunk_sectors;

		blksize = max(blksize, queue_logical_block_size(
				      rdev1->bdev->bd_disk->queue));

		rdev_क्रम_each(rdev2, mddev) अणु
			pr_debug("md/raid0:%s:   comparing %s(%llu)"
				 " with %s(%llu)\n",
				 mdname(mddev),
				 bdevname(rdev1->bdev,b),
				 (अचिन्हित दीर्घ दीर्घ)rdev1->sectors,
				 bdevname(rdev2->bdev,b2),
				 (अचिन्हित दीर्घ दीर्घ)rdev2->sectors);
			अगर (rdev2 == rdev1) अणु
				pr_debug("md/raid0:%s:   END\n",
					 mdname(mddev));
				अवरोध;
			पूर्ण
			अगर (rdev2->sectors == rdev1->sectors) अणु
				/*
				 * Not unique, करोn't count it as a new
				 * group
				 */
				pr_debug("md/raid0:%s:   EQUAL\n",
					 mdname(mddev));
				c = 1;
				अवरोध;
			पूर्ण
			pr_debug("md/raid0:%s:   NOT EQUAL\n",
				 mdname(mddev));
		पूर्ण
		अगर (!c) अणु
			pr_debug("md/raid0:%s:   ==> UNIQUE\n",
				 mdname(mddev));
			conf->nr_strip_zones++;
			pr_debug("md/raid0:%s: %d zones\n",
				 mdname(mddev), conf->nr_strip_zones);
		पूर्ण
	पूर्ण
	pr_debug("md/raid0:%s: FINAL %d zones\n",
		 mdname(mddev), conf->nr_strip_zones);

	अगर (conf->nr_strip_zones == 1) अणु
		conf->layout = RAID0_ORIG_LAYOUT;
	पूर्ण अन्यथा अगर (mddev->layout == RAID0_ORIG_LAYOUT ||
		   mddev->layout == RAID0_ALT_MULTIZONE_LAYOUT) अणु
		conf->layout = mddev->layout;
	पूर्ण अन्यथा अगर (शेष_layout == RAID0_ORIG_LAYOUT ||
		   शेष_layout == RAID0_ALT_MULTIZONE_LAYOUT) अणु
		conf->layout = शेष_layout;
	पूर्ण अन्यथा अणु
		pr_err("md/raid0:%s: cannot assemble multi-zone RAID0 with default_layout setting\n",
		       mdname(mddev));
		pr_err("md/raid0: please set raid0.default_layout to 1 or 2\n");
		err = -ENOTSUPP;
		जाओ पात;
	पूर्ण
	/*
	 * now since we have the hard sector sizes, we can make sure
	 * chunk size is a multiple of that sector size
	 */
	अगर ((mddev->chunk_sectors << 9) % blksize) अणु
		pr_warn("md/raid0:%s: chunk_size of %d not multiple of block size %d\n",
			mdname(mddev),
			mddev->chunk_sectors << 9, blksize);
		err = -EINVAL;
		जाओ पात;
	पूर्ण

	err = -ENOMEM;
	conf->strip_zone = kसुस्मृति(conf->nr_strip_zones,
				   माप(काष्ठा strip_zone),
				   GFP_KERNEL);
	अगर (!conf->strip_zone)
		जाओ पात;
	conf->devlist = kzalloc(array3_size(माप(काष्ठा md_rdev *),
					    conf->nr_strip_zones,
					    mddev->raid_disks),
				GFP_KERNEL);
	अगर (!conf->devlist)
		जाओ पात;

	/* The first zone must contain all devices, so here we check that
	 * there is a proper alignment of slots to devices and find them all
	 */
	zone = &conf->strip_zone[0];
	cnt = 0;
	smallest = शून्य;
	dev = conf->devlist;
	err = -EINVAL;
	rdev_क्रम_each(rdev1, mddev) अणु
		पूर्णांक j = rdev1->raid_disk;

		अगर (mddev->level == 10) अणु
			/* taking over a raid10-n2 array */
			j /= 2;
			rdev1->new_raid_disk = j;
		पूर्ण

		अगर (mddev->level == 1) अणु
			/* taiking over a raid1 array-
			 * we have only one active disk
			 */
			j = 0;
			rdev1->new_raid_disk = j;
		पूर्ण

		अगर (j < 0) अणु
			pr_warn("md/raid0:%s: remove inactive devices before converting to RAID0\n",
				mdname(mddev));
			जाओ पात;
		पूर्ण
		अगर (j >= mddev->raid_disks) अणु
			pr_warn("md/raid0:%s: bad disk number %d - aborting!\n",
				mdname(mddev), j);
			जाओ पात;
		पूर्ण
		अगर (dev[j]) अणु
			pr_warn("md/raid0:%s: multiple devices for %d - aborting!\n",
				mdname(mddev), j);
			जाओ पात;
		पूर्ण
		dev[j] = rdev1;

		अगर (!smallest || (rdev1->sectors < smallest->sectors))
			smallest = rdev1;
		cnt++;
	पूर्ण
	अगर (cnt != mddev->raid_disks) अणु
		pr_warn("md/raid0:%s: too few disks (%d of %d) - aborting!\n",
			mdname(mddev), cnt, mddev->raid_disks);
		जाओ पात;
	पूर्ण
	zone->nb_dev = cnt;
	zone->zone_end = smallest->sectors * cnt;

	curr_zone_end = zone->zone_end;

	/* now करो the other zones */
	क्रम (i = 1; i < conf->nr_strip_zones; i++)
	अणु
		पूर्णांक j;

		zone = conf->strip_zone + i;
		dev = conf->devlist + i * mddev->raid_disks;

		pr_debug("md/raid0:%s: zone %d\n", mdname(mddev), i);
		zone->dev_start = smallest->sectors;
		smallest = शून्य;
		c = 0;

		क्रम (j=0; j<cnt; j++) अणु
			rdev = conf->devlist[j];
			अगर (rdev->sectors <= zone->dev_start) अणु
				pr_debug("md/raid0:%s: checking %s ... nope\n",
					 mdname(mddev),
					 bdevname(rdev->bdev, b));
				जारी;
			पूर्ण
			pr_debug("md/raid0:%s: checking %s ..."
				 " contained as device %d\n",
				 mdname(mddev),
				 bdevname(rdev->bdev, b), c);
			dev[c] = rdev;
			c++;
			अगर (!smallest || rdev->sectors < smallest->sectors) अणु
				smallest = rdev;
				pr_debug("md/raid0:%s:  (%llu) is smallest!.\n",
					 mdname(mddev),
					 (अचिन्हित दीर्घ दीर्घ)rdev->sectors);
			पूर्ण
		पूर्ण

		zone->nb_dev = c;
		sectors = (smallest->sectors - zone->dev_start) * c;
		pr_debug("md/raid0:%s: zone->nb_dev: %d, sectors: %llu\n",
			 mdname(mddev),
			 zone->nb_dev, (अचिन्हित दीर्घ दीर्घ)sectors);

		curr_zone_end += sectors;
		zone->zone_end = curr_zone_end;

		pr_debug("md/raid0:%s: current zone start: %llu\n",
			 mdname(mddev),
			 (अचिन्हित दीर्घ दीर्घ)smallest->sectors);
	पूर्ण

	pr_debug("md/raid0:%s: done.\n", mdname(mddev));
	*निजी_conf = conf;

	वापस 0;
पात:
	kमुक्त(conf->strip_zone);
	kमुक्त(conf->devlist);
	kमुक्त(conf);
	*निजी_conf = ERR_PTR(err);
	वापस err;
पूर्ण

/* Find the zone which holds a particular offset
 * Update *sectorp to be an offset in that zone
 */
अटल काष्ठा strip_zone *find_zone(काष्ठा r0conf *conf,
				    sector_t *sectorp)
अणु
	पूर्णांक i;
	काष्ठा strip_zone *z = conf->strip_zone;
	sector_t sector = *sectorp;

	क्रम (i = 0; i < conf->nr_strip_zones; i++)
		अगर (sector < z[i].zone_end) अणु
			अगर (i)
				*sectorp = sector - z[i-1].zone_end;
			वापस z + i;
		पूर्ण
	BUG();
पूर्ण

/*
 * remaps the bio to the target device. we separate two flows.
 * घातer 2 flow and a general flow क्रम the sake of perक्रमmance
*/
अटल काष्ठा md_rdev *map_sector(काष्ठा mddev *mddev, काष्ठा strip_zone *zone,
				sector_t sector, sector_t *sector_offset)
अणु
	अचिन्हित पूर्णांक sect_in_chunk;
	sector_t chunk;
	काष्ठा r0conf *conf = mddev->निजी;
	पूर्णांक raid_disks = conf->strip_zone[0].nb_dev;
	अचिन्हित पूर्णांक chunk_sects = mddev->chunk_sectors;

	अगर (is_घातer_of_2(chunk_sects)) अणु
		पूर्णांक chunksect_bits = ffz(~chunk_sects);
		/* find the sector offset inside the chunk */
		sect_in_chunk  = sector & (chunk_sects - 1);
		sector >>= chunksect_bits;
		/* chunk in zone */
		chunk = *sector_offset;
		/* quotient is the chunk in real device*/
		sector_भाग(chunk, zone->nb_dev << chunksect_bits);
	पूर्ण अन्यथाअणु
		sect_in_chunk = sector_भाग(sector, chunk_sects);
		chunk = *sector_offset;
		sector_भाग(chunk, chunk_sects * zone->nb_dev);
	पूर्ण
	/*
	*  position the bio over the real device
	*  real sector = chunk in device + starting of zone
	*	+ the position in the chunk
	*/
	*sector_offset = (chunk * chunk_sects) + sect_in_chunk;
	वापस conf->devlist[(zone - conf->strip_zone)*raid_disks
			     + sector_भाग(sector, zone->nb_dev)];
पूर्ण

अटल sector_t raid0_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	sector_t array_sectors = 0;
	काष्ठा md_rdev *rdev;

	WARN_ONCE(sectors || raid_disks,
		  "%s does not support generic reshape\n", __func__);

	rdev_क्रम_each(rdev, mddev)
		array_sectors += (rdev->sectors &
				  ~(sector_t)(mddev->chunk_sectors-1));

	वापस array_sectors;
पूर्ण

अटल व्योम raid0_मुक्त(काष्ठा mddev *mddev, व्योम *priv);

अटल पूर्णांक raid0_run(काष्ठा mddev *mddev)
अणु
	काष्ठा r0conf *conf;
	पूर्णांक ret;

	अगर (mddev->chunk_sectors == 0) अणु
		pr_warn("md/raid0:%s: chunk size must be set.\n", mdname(mddev));
		वापस -EINVAL;
	पूर्ण
	अगर (md_check_no_biपंचांगap(mddev))
		वापस -EINVAL;

	/* अगर निजी is not null, we are here after takeover */
	अगर (mddev->निजी == शून्य) अणु
		ret = create_strip_zones(mddev, &conf);
		अगर (ret < 0)
			वापस ret;
		mddev->निजी = conf;
	पूर्ण
	conf = mddev->निजी;
	अगर (mddev->queue) अणु
		काष्ठा md_rdev *rdev;
		bool discard_supported = false;

		blk_queue_max_hw_sectors(mddev->queue, mddev->chunk_sectors);
		blk_queue_max_ग_लिखो_same_sectors(mddev->queue, mddev->chunk_sectors);
		blk_queue_max_ग_लिखो_zeroes_sectors(mddev->queue, mddev->chunk_sectors);
		blk_queue_max_discard_sectors(mddev->queue, अच_पूर्णांक_उच्च);

		blk_queue_io_min(mddev->queue, mddev->chunk_sectors << 9);
		blk_queue_io_opt(mddev->queue,
				 (mddev->chunk_sectors << 9) * mddev->raid_disks);

		rdev_क्रम_each(rdev, mddev) अणु
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->data_offset << 9);
			अगर (blk_queue_discard(bdev_get_queue(rdev->bdev)))
				discard_supported = true;
		पूर्ण
		अगर (!discard_supported)
			blk_queue_flag_clear(QUEUE_FLAG_DISCARD, mddev->queue);
		अन्यथा
			blk_queue_flag_set(QUEUE_FLAG_DISCARD, mddev->queue);
	पूर्ण

	/* calculate array device size */
	md_set_array_sectors(mddev, raid0_size(mddev, 0, 0));

	pr_debug("md/raid0:%s: md_size is %llu sectors.\n",
		 mdname(mddev),
		 (अचिन्हित दीर्घ दीर्घ)mddev->array_sectors);

	dump_zones(mddev);

	ret = md_पूर्णांकegrity_रेजिस्टर(mddev);

	वापस ret;
पूर्ण

अटल व्योम raid0_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा r0conf *conf = priv;

	kमुक्त(conf->strip_zone);
	kमुक्त(conf->devlist);
	kमुक्त(conf);
पूर्ण

अटल व्योम raid0_handle_discard(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा r0conf *conf = mddev->निजी;
	काष्ठा strip_zone *zone;
	sector_t start = bio->bi_iter.bi_sector;
	sector_t end;
	अचिन्हित पूर्णांक stripe_size;
	sector_t first_stripe_index, last_stripe_index;
	sector_t start_disk_offset;
	अचिन्हित पूर्णांक start_disk_index;
	sector_t end_disk_offset;
	अचिन्हित पूर्णांक end_disk_index;
	अचिन्हित पूर्णांक disk;

	zone = find_zone(conf, &start);

	अगर (bio_end_sector(bio) > zone->zone_end) अणु
		काष्ठा bio *split = bio_split(bio,
			zone->zone_end - bio->bi_iter.bi_sector, GFP_NOIO,
			&mddev->bio_set);
		bio_chain(split, bio);
		submit_bio_noacct(bio);
		bio = split;
		end = zone->zone_end;
	पूर्ण अन्यथा
		end = bio_end_sector(bio);

	अगर (zone != conf->strip_zone)
		end = end - zone[-1].zone_end;

	/* Now start and end is the offset in zone */
	stripe_size = zone->nb_dev * mddev->chunk_sectors;

	first_stripe_index = start;
	sector_भाग(first_stripe_index, stripe_size);
	last_stripe_index = end;
	sector_भाग(last_stripe_index, stripe_size);

	start_disk_index = (पूर्णांक)(start - first_stripe_index * stripe_size) /
		mddev->chunk_sectors;
	start_disk_offset = ((पूर्णांक)(start - first_stripe_index * stripe_size) %
		mddev->chunk_sectors) +
		first_stripe_index * mddev->chunk_sectors;
	end_disk_index = (पूर्णांक)(end - last_stripe_index * stripe_size) /
		mddev->chunk_sectors;
	end_disk_offset = ((पूर्णांक)(end - last_stripe_index * stripe_size) %
		mddev->chunk_sectors) +
		last_stripe_index * mddev->chunk_sectors;

	क्रम (disk = 0; disk < zone->nb_dev; disk++) अणु
		sector_t dev_start, dev_end;
		काष्ठा md_rdev *rdev;

		अगर (disk < start_disk_index)
			dev_start = (first_stripe_index + 1) *
				mddev->chunk_sectors;
		अन्यथा अगर (disk > start_disk_index)
			dev_start = first_stripe_index * mddev->chunk_sectors;
		अन्यथा
			dev_start = start_disk_offset;

		अगर (disk < end_disk_index)
			dev_end = (last_stripe_index + 1) * mddev->chunk_sectors;
		अन्यथा अगर (disk > end_disk_index)
			dev_end = last_stripe_index * mddev->chunk_sectors;
		अन्यथा
			dev_end = end_disk_offset;

		अगर (dev_end <= dev_start)
			जारी;

		rdev = conf->devlist[(zone - conf->strip_zone) *
			conf->strip_zone[0].nb_dev + disk];
		md_submit_discard_bio(mddev, rdev, bio,
			dev_start + zone->dev_start + rdev->data_offset,
			dev_end - dev_start);
	पूर्ण
	bio_endio(bio);
पूर्ण

अटल bool raid0_make_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा r0conf *conf = mddev->निजी;
	काष्ठा strip_zone *zone;
	काष्ठा md_rdev *पंचांगp_dev;
	sector_t bio_sector;
	sector_t sector;
	sector_t orig_sector;
	अचिन्हित chunk_sects;
	अचिन्हित sectors;

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)
	    && md_flush_request(mddev, bio))
		वापस true;

	अगर (unlikely((bio_op(bio) == REQ_OP_DISCARD))) अणु
		raid0_handle_discard(mddev, bio);
		वापस true;
	पूर्ण

	bio_sector = bio->bi_iter.bi_sector;
	sector = bio_sector;
	chunk_sects = mddev->chunk_sectors;

	sectors = chunk_sects -
		(likely(is_घातer_of_2(chunk_sects))
		 ? (sector & (chunk_sects-1))
		 : sector_भाग(sector, chunk_sects));

	/* Restore due to sector_भाग */
	sector = bio_sector;

	अगर (sectors < bio_sectors(bio)) अणु
		काष्ठा bio *split = bio_split(bio, sectors, GFP_NOIO,
					      &mddev->bio_set);
		bio_chain(split, bio);
		submit_bio_noacct(bio);
		bio = split;
	पूर्ण

	orig_sector = sector;
	zone = find_zone(mddev->निजी, &sector);
	चयन (conf->layout) अणु
	हाल RAID0_ORIG_LAYOUT:
		पंचांगp_dev = map_sector(mddev, zone, orig_sector, &sector);
		अवरोध;
	हाल RAID0_ALT_MULTIZONE_LAYOUT:
		पंचांगp_dev = map_sector(mddev, zone, sector, &sector);
		अवरोध;
	शेष:
		WARN(1, "md/raid0:%s: Invalid layout\n", mdname(mddev));
		bio_io_error(bio);
		वापस true;
	पूर्ण

	अगर (unlikely(is_mddev_broken(पंचांगp_dev, "raid0"))) अणु
		bio_io_error(bio);
		वापस true;
	पूर्ण

	bio_set_dev(bio, पंचांगp_dev->bdev);
	bio->bi_iter.bi_sector = sector + zone->dev_start +
		पंचांगp_dev->data_offset;

	अगर (mddev->gendisk)
		trace_block_bio_remap(bio, disk_devt(mddev->gendisk),
				      bio_sector);
	mddev_check_ग_लिखोsame(mddev, bio);
	mddev_check_ग_लिखो_zeroes(mddev, bio);
	submit_bio_noacct(bio);
	वापस true;
पूर्ण

अटल व्योम raid0_status(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	seq_म_लिखो(seq, " %dk chunks", mddev->chunk_sectors / 2);
	वापस;
पूर्ण

अटल व्योम *raid0_takeover_raid45(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;
	काष्ठा r0conf *priv_conf;

	अगर (mddev->degraded != 1) अणु
		pr_warn("md/raid0:%s: raid5 must be degraded! Degraded disks: %d\n",
			mdname(mddev),
			mddev->degraded);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rdev_क्रम_each(rdev, mddev) अणु
		/* check slot number क्रम a disk */
		अगर (rdev->raid_disk == mddev->raid_disks-1) अणु
			pr_warn("md/raid0:%s: raid5 must have missing parity disk!\n",
				mdname(mddev));
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		rdev->sectors = mddev->dev_sectors;
	पूर्ण

	/* Set new parameters */
	mddev->new_level = 0;
	mddev->new_layout = 0;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->raid_disks--;
	mddev->delta_disks = -1;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;
	mddev_clear_unsupported_flags(mddev, UNSUPPORTED_MDDEV_FLAGS);

	create_strip_zones(mddev, &priv_conf);

	वापस priv_conf;
पूर्ण

अटल व्योम *raid0_takeover_raid10(काष्ठा mddev *mddev)
अणु
	काष्ठा r0conf *priv_conf;

	/* Check layout:
	 *  - far_copies must be 1
	 *  - near_copies must be 2
	 *  - disks number must be even
	 *  - all mirrors must be alपढ़ोy degraded
	 */
	अगर (mddev->layout != ((1 << 8) + 2)) अणु
		pr_warn("md/raid0:%s:: Raid0 cannot takeover layout: 0x%x\n",
			mdname(mddev),
			mddev->layout);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (mddev->raid_disks & 1) अणु
		pr_warn("md/raid0:%s: Raid0 cannot takeover Raid10 with odd disk number.\n",
			mdname(mddev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (mddev->degraded != (mddev->raid_disks>>1)) अणु
		pr_warn("md/raid0:%s: All mirrors must be already degraded!\n",
			mdname(mddev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Set new parameters */
	mddev->new_level = 0;
	mddev->new_layout = 0;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->delta_disks = - mddev->raid_disks / 2;
	mddev->raid_disks += mddev->delta_disks;
	mddev->degraded = 0;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;
	mddev_clear_unsupported_flags(mddev, UNSUPPORTED_MDDEV_FLAGS);

	create_strip_zones(mddev, &priv_conf);
	वापस priv_conf;
पूर्ण

अटल व्योम *raid0_takeover_raid1(काष्ठा mddev *mddev)
अणु
	काष्ठा r0conf *priv_conf;
	पूर्णांक chunksect;

	/* Check layout:
	 *  - (N - 1) mirror drives must be alपढ़ोy faulty
	 */
	अगर ((mddev->raid_disks - 1) != mddev->degraded) अणु
		pr_err("md/raid0:%s: (N - 1) mirrors drives must be already faulty!\n",
		       mdname(mddev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * a raid1 करोesn't have the notion of chunk size, so
	 * figure out the largest suitable size we can use.
	 */
	chunksect = 64 * 2; /* 64K by शेष */

	/* The array must be an exact multiple of chunksize */
	जबतक (chunksect && (mddev->array_sectors & (chunksect - 1)))
		chunksect >>= 1;

	अगर ((chunksect << 9) < PAGE_SIZE)
		/* array size करोes not allow a suitable chunk size */
		वापस ERR_PTR(-EINVAL);

	/* Set new parameters */
	mddev->new_level = 0;
	mddev->new_layout = 0;
	mddev->new_chunk_sectors = chunksect;
	mddev->chunk_sectors = chunksect;
	mddev->delta_disks = 1 - mddev->raid_disks;
	mddev->raid_disks = 1;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;
	mddev_clear_unsupported_flags(mddev, UNSUPPORTED_MDDEV_FLAGS);

	create_strip_zones(mddev, &priv_conf);
	वापस priv_conf;
पूर्ण

अटल व्योम *raid0_takeover(काष्ठा mddev *mddev)
अणु
	/* raid0 can take over:
	 *  raid4 - अगर all data disks are active.
	 *  raid5 - providing it is Raid4 layout and one disk is faulty
	 *  raid10 - assuming we have all necessary active disks
	 *  raid1 - with (N -1) mirror drives faulty
	 */

	अगर (mddev->biपंचांगap) अणु
		pr_warn("md/raid0: %s: cannot takeover array with bitmap\n",
			mdname(mddev));
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	अगर (mddev->level == 4)
		वापस raid0_takeover_raid45(mddev);

	अगर (mddev->level == 5) अणु
		अगर (mddev->layout == ALGORITHM_PARITY_N)
			वापस raid0_takeover_raid45(mddev);

		pr_warn("md/raid0:%s: Raid can only takeover Raid5 with layout: %d\n",
			mdname(mddev), ALGORITHM_PARITY_N);
	पूर्ण

	अगर (mddev->level == 10)
		वापस raid0_takeover_raid10(mddev);

	अगर (mddev->level == 1)
		वापस raid0_takeover_raid1(mddev);

	pr_warn("Takeover from raid%i to raid0 not supported\n",
		mddev->level);

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल व्योम raid0_quiesce(काष्ठा mddev *mddev, पूर्णांक quiesce)
अणु
पूर्ण

अटल काष्ठा md_personality raid0_personality=
अणु
	.name		= "raid0",
	.level		= 0,
	.owner		= THIS_MODULE,
	.make_request	= raid0_make_request,
	.run		= raid0_run,
	.मुक्त		= raid0_मुक्त,
	.status		= raid0_status,
	.size		= raid0_size,
	.takeover	= raid0_takeover,
	.quiesce	= raid0_quiesce,
पूर्ण;

अटल पूर्णांक __init raid0_init (व्योम)
अणु
	वापस रेजिस्टर_md_personality (&raid0_personality);
पूर्ण

अटल व्योम raid0_निकास (व्योम)
अणु
	unरेजिस्टर_md_personality (&raid0_personality);
पूर्ण

module_init(raid0_init);
module_निकास(raid0_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RAID0 (striping) personality for MD");
MODULE_ALIAS("md-personality-2"); /* RAID0 */
MODULE_ALIAS("md-raid0");
MODULE_ALIAS("md-level-0");
