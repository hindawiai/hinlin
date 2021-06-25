<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/biपंचांगap.h>
#समावेश "null_blk.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

अटल अंतरभूत sector_t mb_to_sects(अचिन्हित दीर्घ mb)
अणु
	वापस ((sector_t)mb * SZ_1M) >> SECTOR_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक null_zone_no(काष्ठा nullb_device *dev, sector_t sect)
अणु
	वापस sect >> ilog2(dev->zone_size_sects);
पूर्ण

अटल अंतरभूत व्योम null_lock_zone_res(काष्ठा nullb_device *dev)
अणु
	अगर (dev->need_zone_res_mgmt)
		spin_lock_irq(&dev->zone_res_lock);
पूर्ण

अटल अंतरभूत व्योम null_unlock_zone_res(काष्ठा nullb_device *dev)
अणु
	अगर (dev->need_zone_res_mgmt)
		spin_unlock_irq(&dev->zone_res_lock);
पूर्ण

अटल अंतरभूत व्योम null_init_zone_lock(काष्ठा nullb_device *dev,
				       काष्ठा nullb_zone *zone)
अणु
	अगर (!dev->memory_backed)
		spin_lock_init(&zone->spinlock);
	अन्यथा
		mutex_init(&zone->mutex);
पूर्ण

अटल अंतरभूत व्योम null_lock_zone(काष्ठा nullb_device *dev,
				  काष्ठा nullb_zone *zone)
अणु
	अगर (!dev->memory_backed)
		spin_lock_irq(&zone->spinlock);
	अन्यथा
		mutex_lock(&zone->mutex);
पूर्ण

अटल अंतरभूत व्योम null_unlock_zone(काष्ठा nullb_device *dev,
				    काष्ठा nullb_zone *zone)
अणु
	अगर (!dev->memory_backed)
		spin_unlock_irq(&zone->spinlock);
	अन्यथा
		mutex_unlock(&zone->mutex);
पूर्ण

पूर्णांक null_init_zoned_dev(काष्ठा nullb_device *dev, काष्ठा request_queue *q)
अणु
	sector_t dev_capacity_sects, zone_capacity_sects;
	काष्ठा nullb_zone *zone;
	sector_t sector = 0;
	अचिन्हित पूर्णांक i;

	अगर (!is_घातer_of_2(dev->zone_size)) अणु
		pr_err("zone_size must be power-of-two\n");
		वापस -EINVAL;
	पूर्ण
	अगर (dev->zone_size > dev->size) अणु
		pr_err("Zone size larger than device capacity\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!dev->zone_capacity)
		dev->zone_capacity = dev->zone_size;

	अगर (dev->zone_capacity > dev->zone_size) अणु
		pr_err("null_blk: zone capacity (%lu MB) larger than zone size (%lu MB)\n",
					dev->zone_capacity, dev->zone_size);
		वापस -EINVAL;
	पूर्ण

	zone_capacity_sects = mb_to_sects(dev->zone_capacity);
	dev_capacity_sects = mb_to_sects(dev->size);
	dev->zone_size_sects = mb_to_sects(dev->zone_size);
	dev->nr_zones = round_up(dev_capacity_sects, dev->zone_size_sects)
		>> ilog2(dev->zone_size_sects);

	dev->zones = kvदो_स्मृति_array(dev->nr_zones, माप(काष्ठा nullb_zone),
				    GFP_KERNEL | __GFP_ZERO);
	अगर (!dev->zones)
		वापस -ENOMEM;

	spin_lock_init(&dev->zone_res_lock);

	अगर (dev->zone_nr_conv >= dev->nr_zones) अणु
		dev->zone_nr_conv = dev->nr_zones - 1;
		pr_info("changed the number of conventional zones to %u",
			dev->zone_nr_conv);
	पूर्ण

	/* Max active zones has to be < nbr of seq zones in order to be enक्रमceable */
	अगर (dev->zone_max_active >= dev->nr_zones - dev->zone_nr_conv) अणु
		dev->zone_max_active = 0;
		pr_info("zone_max_active limit disabled, limit >= zone count\n");
	पूर्ण

	/* Max खोलो zones has to be <= max active zones */
	अगर (dev->zone_max_active && dev->zone_max_खोलो > dev->zone_max_active) अणु
		dev->zone_max_खोलो = dev->zone_max_active;
		pr_info("changed the maximum number of open zones to %u\n",
			dev->nr_zones);
	पूर्ण अन्यथा अगर (dev->zone_max_खोलो >= dev->nr_zones - dev->zone_nr_conv) अणु
		dev->zone_max_खोलो = 0;
		pr_info("zone_max_open limit disabled, limit >= zone count\n");
	पूर्ण
	dev->need_zone_res_mgmt = dev->zone_max_active || dev->zone_max_खोलो;
	dev->imp_बंद_zone_no = dev->zone_nr_conv;

	क्रम (i = 0; i <  dev->zone_nr_conv; i++) अणु
		zone = &dev->zones[i];

		null_init_zone_lock(dev, zone);
		zone->start = sector;
		zone->len = dev->zone_size_sects;
		zone->capacity = zone->len;
		zone->wp = zone->start + zone->len;
		zone->type = BLK_ZONE_TYPE_CONVENTIONAL;
		zone->cond = BLK_ZONE_COND_NOT_WP;

		sector += dev->zone_size_sects;
	पूर्ण

	क्रम (i = dev->zone_nr_conv; i < dev->nr_zones; i++) अणु
		zone = &dev->zones[i];

		null_init_zone_lock(dev, zone);
		zone->start = zone->wp = sector;
		अगर (zone->start + dev->zone_size_sects > dev_capacity_sects)
			zone->len = dev_capacity_sects - zone->start;
		अन्यथा
			zone->len = dev->zone_size_sects;
		zone->capacity =
			min_t(sector_t, zone->len, zone_capacity_sects);
		zone->type = BLK_ZONE_TYPE_SEQWRITE_REQ;
		zone->cond = BLK_ZONE_COND_EMPTY;

		sector += dev->zone_size_sects;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक null_रेजिस्टर_zoned_dev(काष्ठा nullb *nullb)
अणु
	काष्ठा nullb_device *dev = nullb->dev;
	काष्ठा request_queue *q = nullb->q;

	blk_queue_set_zoned(nullb->disk, BLK_ZONED_HM);
	blk_queue_flag_set(QUEUE_FLAG_ZONE_RESETALL, q);
	blk_queue_required_elevator_features(q, ELEVATOR_F_ZBD_SEQ_WRITE);

	अगर (queue_is_mq(q)) अणु
		पूर्णांक ret = blk_revalidate_disk_zones(nullb->disk, शून्य);

		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		blk_queue_chunk_sectors(q, dev->zone_size_sects);
		q->nr_zones = blkdev_nr_zones(nullb->disk);
	पूर्ण

	blk_queue_max_zone_append_sectors(q, dev->zone_size_sects);
	blk_queue_max_खोलो_zones(q, dev->zone_max_खोलो);
	blk_queue_max_active_zones(q, dev->zone_max_active);

	वापस 0;
पूर्ण

व्योम null_मुक्त_zoned_dev(काष्ठा nullb_device *dev)
अणु
	kvमुक्त(dev->zones);
	dev->zones = शून्य;
पूर्ण

पूर्णांक null_report_zones(काष्ठा gendisk *disk, sector_t sector,
		अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा nullb *nullb = disk->निजी_data;
	काष्ठा nullb_device *dev = nullb->dev;
	अचिन्हित पूर्णांक first_zone, i;
	काष्ठा nullb_zone *zone;
	काष्ठा blk_zone blkz;
	पूर्णांक error;

	first_zone = null_zone_no(dev, sector);
	अगर (first_zone >= dev->nr_zones)
		वापस 0;

	nr_zones = min(nr_zones, dev->nr_zones - first_zone);
	trace_nullb_report_zones(nullb, nr_zones);

	स_रखो(&blkz, 0, माप(काष्ठा blk_zone));
	zone = &dev->zones[first_zone];
	क्रम (i = 0; i < nr_zones; i++, zone++) अणु
		/*
		 * Stacked DM target drivers will remap the zone inक्रमmation by
		 * modअगरying the zone inक्रमmation passed to the report callback.
		 * So use a local copy to aव्योम corruption of the device zone
		 * array.
		 */
		null_lock_zone(dev, zone);
		blkz.start = zone->start;
		blkz.len = zone->len;
		blkz.wp = zone->wp;
		blkz.type = zone->type;
		blkz.cond = zone->cond;
		blkz.capacity = zone->capacity;
		null_unlock_zone(dev, zone);

		error = cb(&blkz, i, data);
		अगर (error)
			वापस error;
	पूर्ण

	वापस nr_zones;
पूर्ण

/*
 * This is called in the हाल of memory backing from null_process_cmd()
 * with the target zone alपढ़ोy locked.
 */
माप_प्रकार null_zone_valid_पढ़ो_len(काष्ठा nullb *nullb,
				sector_t sector, अचिन्हित पूर्णांक len)
अणु
	काष्ठा nullb_device *dev = nullb->dev;
	काष्ठा nullb_zone *zone = &dev->zones[null_zone_no(dev, sector)];
	अचिन्हित पूर्णांक nr_sectors = len >> SECTOR_SHIFT;

	/* Read must be below the ग_लिखो poपूर्णांकer position */
	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL ||
	    sector + nr_sectors <= zone->wp)
		वापस len;

	अगर (sector > zone->wp)
		वापस 0;

	वापस (zone->wp - sector) << SECTOR_SHIFT;
पूर्ण

अटल blk_status_t __null_बंद_zone(काष्ठा nullb_device *dev,
				      काष्ठा nullb_zone *zone)
अणु
	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_CLOSED:
		/* बंद operation on बंदd is not an error */
		वापस BLK_STS_OK;
	हाल BLK_ZONE_COND_IMP_OPEN:
		dev->nr_zones_imp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_EXP_OPEN:
		dev->nr_zones_exp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_EMPTY:
	हाल BLK_ZONE_COND_FULL:
	शेष:
		वापस BLK_STS_IOERR;
	पूर्ण

	अगर (zone->wp == zone->start) अणु
		zone->cond = BLK_ZONE_COND_EMPTY;
	पूर्ण अन्यथा अणु
		zone->cond = BLK_ZONE_COND_CLOSED;
		dev->nr_zones_बंदd++;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल व्योम null_बंद_imp_खोलो_zone(काष्ठा nullb_device *dev)
अणु
	काष्ठा nullb_zone *zone;
	अचिन्हित पूर्णांक zno, i;

	zno = dev->imp_बंद_zone_no;
	अगर (zno >= dev->nr_zones)
		zno = dev->zone_nr_conv;

	क्रम (i = dev->zone_nr_conv; i < dev->nr_zones; i++) अणु
		zone = &dev->zones[zno];
		zno++;
		अगर (zno >= dev->nr_zones)
			zno = dev->zone_nr_conv;

		अगर (zone->cond == BLK_ZONE_COND_IMP_OPEN) अणु
			__null_बंद_zone(dev, zone);
			dev->imp_बंद_zone_no = zno;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल blk_status_t null_check_active(काष्ठा nullb_device *dev)
अणु
	अगर (!dev->zone_max_active)
		वापस BLK_STS_OK;

	अगर (dev->nr_zones_exp_खोलो + dev->nr_zones_imp_खोलो +
			dev->nr_zones_बंदd < dev->zone_max_active)
		वापस BLK_STS_OK;

	वापस BLK_STS_ZONE_ACTIVE_RESOURCE;
पूर्ण

अटल blk_status_t null_check_खोलो(काष्ठा nullb_device *dev)
अणु
	अगर (!dev->zone_max_खोलो)
		वापस BLK_STS_OK;

	अगर (dev->nr_zones_exp_खोलो + dev->nr_zones_imp_खोलो < dev->zone_max_खोलो)
		वापस BLK_STS_OK;

	अगर (dev->nr_zones_imp_खोलो) अणु
		अगर (null_check_active(dev) == BLK_STS_OK) अणु
			null_बंद_imp_खोलो_zone(dev);
			वापस BLK_STS_OK;
		पूर्ण
	पूर्ण

	वापस BLK_STS_ZONE_OPEN_RESOURCE;
पूर्ण

/*
 * This function matches the manage खोलो zone resources function in the ZBC standard,
 * with the addition of max active zones support (added in the ZNS standard).
 *
 * The function determines अगर a zone can transition to implicit खोलो or explicit खोलो,
 * जबतक मुख्यtaining the max खोलो zone (and max active zone) limit(s). It may बंद an
 * implicit खोलो zone in order to make additional zone resources available.
 *
 * ZBC states that an implicit खोलो zone shall be बंदd only अगर there is not
 * room within the खोलो limit. However, with the addition of an active limit,
 * it is not certain that closing an implicit खोलो zone will allow a new zone
 * to be खोलोed, since we might alपढ़ोy be at the active limit capacity.
 */
अटल blk_status_t null_check_zone_resources(काष्ठा nullb_device *dev,
					      काष्ठा nullb_zone *zone)
अणु
	blk_status_t ret;

	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_EMPTY:
		ret = null_check_active(dev);
		अगर (ret != BLK_STS_OK)
			वापस ret;
		fallthrough;
	हाल BLK_ZONE_COND_CLOSED:
		वापस null_check_खोलो(dev);
	शेष:
		/* Should never be called क्रम other states */
		WARN_ON(1);
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

अटल blk_status_t null_zone_ग_लिखो(काष्ठा nullb_cmd *cmd, sector_t sector,
				    अचिन्हित पूर्णांक nr_sectors, bool append)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	अचिन्हित पूर्णांक zno = null_zone_no(dev, sector);
	काष्ठा nullb_zone *zone = &dev->zones[zno];
	blk_status_t ret;

	trace_nullb_zone_op(cmd, zno, zone->cond);

	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL) अणु
		अगर (append)
			वापस BLK_STS_IOERR;
		वापस null_process_cmd(cmd, REQ_OP_WRITE, sector, nr_sectors);
	पूर्ण

	null_lock_zone(dev, zone);

	अगर (zone->cond == BLK_ZONE_COND_FULL) अणु
		/* Cannot ग_लिखो to a full zone */
		ret = BLK_STS_IOERR;
		जाओ unlock;
	पूर्ण

	/*
	 * Regular ग_लिखोs must be at the ग_लिखो poपूर्णांकer position.
	 * Zone append ग_लिखोs are स्वतःmatically issued at the ग_लिखो
	 * poपूर्णांकer and the position वापसed using the request or BIO
	 * sector.
	 */
	अगर (append) अणु
		sector = zone->wp;
		अगर (cmd->bio)
			cmd->bio->bi_iter.bi_sector = sector;
		अन्यथा
			cmd->rq->__sector = sector;
	पूर्ण अन्यथा अगर (sector != zone->wp) अणु
		ret = BLK_STS_IOERR;
		जाओ unlock;
	पूर्ण

	अगर (zone->wp + nr_sectors > zone->start + zone->capacity) अणु
		ret = BLK_STS_IOERR;
		जाओ unlock;
	पूर्ण

	अगर (zone->cond == BLK_ZONE_COND_CLOSED ||
	    zone->cond == BLK_ZONE_COND_EMPTY) अणु
		null_lock_zone_res(dev);

		ret = null_check_zone_resources(dev, zone);
		अगर (ret != BLK_STS_OK) अणु
			null_unlock_zone_res(dev);
			जाओ unlock;
		पूर्ण
		अगर (zone->cond == BLK_ZONE_COND_CLOSED) अणु
			dev->nr_zones_बंदd--;
			dev->nr_zones_imp_खोलो++;
		पूर्ण अन्यथा अगर (zone->cond == BLK_ZONE_COND_EMPTY) अणु
			dev->nr_zones_imp_खोलो++;
		पूर्ण

		अगर (zone->cond != BLK_ZONE_COND_EXP_OPEN)
			zone->cond = BLK_ZONE_COND_IMP_OPEN;

		null_unlock_zone_res(dev);
	पूर्ण

	ret = null_process_cmd(cmd, REQ_OP_WRITE, sector, nr_sectors);
	अगर (ret != BLK_STS_OK)
		जाओ unlock;

	zone->wp += nr_sectors;
	अगर (zone->wp == zone->start + zone->capacity) अणु
		null_lock_zone_res(dev);
		अगर (zone->cond == BLK_ZONE_COND_EXP_OPEN)
			dev->nr_zones_exp_खोलो--;
		अन्यथा अगर (zone->cond == BLK_ZONE_COND_IMP_OPEN)
			dev->nr_zones_imp_खोलो--;
		zone->cond = BLK_ZONE_COND_FULL;
		null_unlock_zone_res(dev);
	पूर्ण

	ret = BLK_STS_OK;

unlock:
	null_unlock_zone(dev, zone);

	वापस ret;
पूर्ण

अटल blk_status_t null_खोलो_zone(काष्ठा nullb_device *dev,
				   काष्ठा nullb_zone *zone)
अणु
	blk_status_t ret = BLK_STS_OK;

	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
		वापस BLK_STS_IOERR;

	null_lock_zone_res(dev);

	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_EXP_OPEN:
		/* खोलो operation on exp खोलो is not an error */
		जाओ unlock;
	हाल BLK_ZONE_COND_EMPTY:
		ret = null_check_zone_resources(dev, zone);
		अगर (ret != BLK_STS_OK)
			जाओ unlock;
		अवरोध;
	हाल BLK_ZONE_COND_IMP_OPEN:
		dev->nr_zones_imp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_CLOSED:
		ret = null_check_zone_resources(dev, zone);
		अगर (ret != BLK_STS_OK)
			जाओ unlock;
		dev->nr_zones_बंदd--;
		अवरोध;
	हाल BLK_ZONE_COND_FULL:
	शेष:
		ret = BLK_STS_IOERR;
		जाओ unlock;
	पूर्ण

	zone->cond = BLK_ZONE_COND_EXP_OPEN;
	dev->nr_zones_exp_खोलो++;

unlock:
	null_unlock_zone_res(dev);

	वापस ret;
पूर्ण

अटल blk_status_t null_बंद_zone(काष्ठा nullb_device *dev,
				    काष्ठा nullb_zone *zone)
अणु
	blk_status_t ret;

	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
		वापस BLK_STS_IOERR;

	null_lock_zone_res(dev);
	ret = __null_बंद_zone(dev, zone);
	null_unlock_zone_res(dev);

	वापस ret;
पूर्ण

अटल blk_status_t null_finish_zone(काष्ठा nullb_device *dev,
				     काष्ठा nullb_zone *zone)
अणु
	blk_status_t ret = BLK_STS_OK;

	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
		वापस BLK_STS_IOERR;

	null_lock_zone_res(dev);

	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_FULL:
		/* finish operation on full is not an error */
		जाओ unlock;
	हाल BLK_ZONE_COND_EMPTY:
		ret = null_check_zone_resources(dev, zone);
		अगर (ret != BLK_STS_OK)
			जाओ unlock;
		अवरोध;
	हाल BLK_ZONE_COND_IMP_OPEN:
		dev->nr_zones_imp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_EXP_OPEN:
		dev->nr_zones_exp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_CLOSED:
		ret = null_check_zone_resources(dev, zone);
		अगर (ret != BLK_STS_OK)
			जाओ unlock;
		dev->nr_zones_बंदd--;
		अवरोध;
	शेष:
		ret = BLK_STS_IOERR;
		जाओ unlock;
	पूर्ण

	zone->cond = BLK_ZONE_COND_FULL;
	zone->wp = zone->start + zone->len;

unlock:
	null_unlock_zone_res(dev);

	वापस ret;
पूर्ण

अटल blk_status_t null_reset_zone(काष्ठा nullb_device *dev,
				    काष्ठा nullb_zone *zone)
अणु
	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
		वापस BLK_STS_IOERR;

	null_lock_zone_res(dev);

	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_EMPTY:
		/* reset operation on empty is not an error */
		null_unlock_zone_res(dev);
		वापस BLK_STS_OK;
	हाल BLK_ZONE_COND_IMP_OPEN:
		dev->nr_zones_imp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_EXP_OPEN:
		dev->nr_zones_exp_खोलो--;
		अवरोध;
	हाल BLK_ZONE_COND_CLOSED:
		dev->nr_zones_बंदd--;
		अवरोध;
	हाल BLK_ZONE_COND_FULL:
		अवरोध;
	शेष:
		null_unlock_zone_res(dev);
		वापस BLK_STS_IOERR;
	पूर्ण

	zone->cond = BLK_ZONE_COND_EMPTY;
	zone->wp = zone->start;

	null_unlock_zone_res(dev);

	अगर (dev->memory_backed)
		वापस null_handle_discard(dev, zone->start, zone->len);

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t null_zone_mgmt(काष्ठा nullb_cmd *cmd, क्रमागत req_opf op,
				   sector_t sector)
अणु
	काष्ठा nullb_device *dev = cmd->nq->dev;
	अचिन्हित पूर्णांक zone_no;
	काष्ठा nullb_zone *zone;
	blk_status_t ret;
	माप_प्रकार i;

	अगर (op == REQ_OP_ZONE_RESET_ALL) अणु
		क्रम (i = dev->zone_nr_conv; i < dev->nr_zones; i++) अणु
			zone = &dev->zones[i];
			null_lock_zone(dev, zone);
			अगर (zone->cond != BLK_ZONE_COND_EMPTY) अणु
				null_reset_zone(dev, zone);
				trace_nullb_zone_op(cmd, i, zone->cond);
			पूर्ण
			null_unlock_zone(dev, zone);
		पूर्ण
		वापस BLK_STS_OK;
	पूर्ण

	zone_no = null_zone_no(dev, sector);
	zone = &dev->zones[zone_no];

	null_lock_zone(dev, zone);

	चयन (op) अणु
	हाल REQ_OP_ZONE_RESET:
		ret = null_reset_zone(dev, zone);
		अवरोध;
	हाल REQ_OP_ZONE_OPEN:
		ret = null_खोलो_zone(dev, zone);
		अवरोध;
	हाल REQ_OP_ZONE_CLOSE:
		ret = null_बंद_zone(dev, zone);
		अवरोध;
	हाल REQ_OP_ZONE_FINISH:
		ret = null_finish_zone(dev, zone);
		अवरोध;
	शेष:
		ret = BLK_STS_NOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret == BLK_STS_OK)
		trace_nullb_zone_op(cmd, zone_no, zone->cond);

	null_unlock_zone(dev, zone);

	वापस ret;
पूर्ण

blk_status_t null_process_zoned_cmd(काष्ठा nullb_cmd *cmd, क्रमागत req_opf op,
				    sector_t sector, sector_t nr_sectors)
अणु
	काष्ठा nullb_device *dev;
	काष्ठा nullb_zone *zone;
	blk_status_t sts;

	चयन (op) अणु
	हाल REQ_OP_WRITE:
		वापस null_zone_ग_लिखो(cmd, sector, nr_sectors, false);
	हाल REQ_OP_ZONE_APPEND:
		वापस null_zone_ग_लिखो(cmd, sector, nr_sectors, true);
	हाल REQ_OP_ZONE_RESET:
	हाल REQ_OP_ZONE_RESET_ALL:
	हाल REQ_OP_ZONE_OPEN:
	हाल REQ_OP_ZONE_CLOSE:
	हाल REQ_OP_ZONE_FINISH:
		वापस null_zone_mgmt(cmd, op, sector);
	शेष:
		dev = cmd->nq->dev;
		zone = &dev->zones[null_zone_no(dev, sector)];

		null_lock_zone(dev, zone);
		sts = null_process_cmd(cmd, op, sector, nr_sectors);
		null_unlock_zone(dev, zone);
		वापस sts;
	पूर्ण
पूर्ण
