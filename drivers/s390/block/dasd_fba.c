<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2009
 */

#घोषणा KMSG_COMPONENT "dasd-fba"

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/debug.h>

#समावेश <linux/slab.h>
#समावेश <linux/hdreg.h>	/* HDIO_GETGEO			    */
#समावेश <linux/bपन.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ccwdev.h>

#समावेश "dasd_int.h"
#समावेश "dasd_fba.h"

#अगर_घोषित PRINTK_HEADER
#अघोषित PRINTK_HEADER
#पूर्ण_अगर				/* PRINTK_HEADER */
#घोषणा PRINTK_HEADER "dasd(fba):"

#घोषणा FBA_DEFAULT_RETRIES 32

#घोषणा DASD_FBA_CCW_WRITE 0x41
#घोषणा DASD_FBA_CCW_READ 0x42
#घोषणा DASD_FBA_CCW_LOCATE 0x43
#घोषणा DASD_FBA_CCW_DEFINE_EXTENT 0x63

MODULE_LICENSE("GPL");

अटल काष्ठा dasd_discipline dasd_fba_discipline;
अटल व्योम *dasd_fba_zero_page;

काष्ठा dasd_fba_निजी अणु
	काष्ठा dasd_fba_अक्षरacteristics rdc_data;
पूर्ण;

अटल काष्ठा ccw_device_id dasd_fba_ids[] = अणु
	अणु CCW_DEVICE_DEVTYPE (0x6310, 0, 0x9336, 0), .driver_info = 0x1पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x3880, 0, 0x3370, 0), .driver_info = 0x2पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ccw, dasd_fba_ids);

अटल पूर्णांक
dasd_fba_set_online(काष्ठा ccw_device *cdev)
अणु
	वापस dasd_generic_set_online(cdev, &dasd_fba_discipline);
पूर्ण

अटल काष्ठा ccw_driver dasd_fba_driver = अणु
	.driver = अणु
		.name	= "dasd-fba",
		.owner	= THIS_MODULE,
		.dev_groups = dasd_dev_groups,
	पूर्ण,
	.ids         = dasd_fba_ids,
	.probe       = dasd_generic_probe,
	.हटाओ      = dasd_generic_हटाओ,
	.set_offline = dasd_generic_set_offline,
	.set_online  = dasd_fba_set_online,
	.notअगरy      = dasd_generic_notअगरy,
	.path_event  = dasd_generic_path_event,
	.पूर्णांक_class   = IRQIO_DAS,
पूर्ण;

अटल व्योम
define_extent(काष्ठा ccw1 * ccw, काष्ठा DE_fba_data *data, पूर्णांक rw,
	      पूर्णांक blksize, पूर्णांक beg, पूर्णांक nr)
अणु
	ccw->cmd_code = DASD_FBA_CCW_DEFINE_EXTENT;
	ccw->flags = 0;
	ccw->count = 16;
	ccw->cda = (__u32) __pa(data);
	स_रखो(data, 0, माप (काष्ठा DE_fba_data));
	अगर (rw == WRITE)
		(data->mask).perm = 0x0;
	अन्यथा अगर (rw == READ)
		(data->mask).perm = 0x1;
	अन्यथा
		data->mask.perm = 0x2;
	data->blk_size = blksize;
	data->ext_loc = beg;
	data->ext_end = nr - 1;
पूर्ण

अटल व्योम
locate_record(काष्ठा ccw1 * ccw, काष्ठा LO_fba_data *data, पूर्णांक rw,
	      पूर्णांक block_nr, पूर्णांक block_ct)
अणु
	ccw->cmd_code = DASD_FBA_CCW_LOCATE;
	ccw->flags = 0;
	ccw->count = 8;
	ccw->cda = (__u32) __pa(data);
	स_रखो(data, 0, माप (काष्ठा LO_fba_data));
	अगर (rw == WRITE)
		data->operation.cmd = 0x5;
	अन्यथा अगर (rw == READ)
		data->operation.cmd = 0x6;
	अन्यथा
		data->operation.cmd = 0x8;
	data->blk_nr = block_nr;
	data->blk_ct = block_ct;
पूर्ण

अटल पूर्णांक
dasd_fba_check_अक्षरacteristics(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_fba_निजी *निजी = device->निजी;
	काष्ठा ccw_device *cdev = device->cdev;
	काष्ठा dasd_block *block;
	पूर्णांक पढ़ोonly, rc;

	अगर (!निजी) अणु
		निजी = kzalloc(माप(*निजी), GFP_KERNEL | GFP_DMA);
		अगर (!निजी) अणु
			dev_warn(&device->cdev->dev,
				 "Allocating memory for private DASD "
				 "data failed\n");
			वापस -ENOMEM;
		पूर्ण
		device->निजी = निजी;
	पूर्ण अन्यथा अणु
		स_रखो(निजी, 0, माप(*निजी));
	पूर्ण
	block = dasd_alloc_block();
	अगर (IS_ERR(block)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s", "could not allocate "
				"dasd block structure");
		device->निजी = शून्य;
		kमुक्त(निजी);
		वापस PTR_ERR(block);
	पूर्ण
	device->block = block;
	block->base = device;

	/* Read Device Characteristics */
	rc = dasd_generic_पढ़ो_dev_अक्षरs(device, DASD_FBA_MAGIC,
					 &निजी->rdc_data, 32);
	अगर (rc) अणु
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "Read device "
				"characteristics returned error %d", rc);
		device->block = शून्य;
		dasd_मुक्त_block(block);
		device->निजी = शून्य;
		kमुक्त(निजी);
		वापस rc;
	पूर्ण

	device->शेष_expires = DASD_EXPIRES;
	device->शेष_retries = FBA_DEFAULT_RETRIES;
	dasd_path_set_opm(device, LPM_ANYPATH);

	पढ़ोonly = dasd_device_is_ro(device);
	अगर (पढ़ोonly)
		set_bit(DASD_FLAG_DEVICE_RO, &device->flags);

	/* FBA supports discard, set the according feature bit */
	dasd_set_feature(cdev, DASD_FEATURE_DISCARD, 1);

	dev_info(&device->cdev->dev,
		 "New FBA DASD %04X/%02X (CU %04X/%02X) with %d MB "
		 "and %d B/blk%s\n",
		 cdev->id.dev_type,
		 cdev->id.dev_model,
		 cdev->id.cu_type,
		 cdev->id.cu_model,
		 ((निजी->rdc_data.blk_bdsa *
		   (निजी->rdc_data.blk_size >> 9)) >> 11),
		 निजी->rdc_data.blk_size,
		 पढ़ोonly ? ", read-only device" : "");
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_fba_करो_analysis(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_fba_निजी *निजी = block->base->निजी;
	पूर्णांक sb, rc;

	rc = dasd_check_blocksize(निजी->rdc_data.blk_size);
	अगर (rc) अणु
		DBF_DEV_EVENT(DBF_WARNING, block->base, "unknown blocksize %d",
			    निजी->rdc_data.blk_size);
		वापस rc;
	पूर्ण
	block->blocks = निजी->rdc_data.blk_bdsa;
	block->bp_block = निजी->rdc_data.blk_size;
	block->s2b_shअगरt = 0;	/* bits to shअगरt 512 to get a block */
	क्रम (sb = 512; sb < निजी->rdc_data.blk_size; sb = sb << 1)
		block->s2b_shअगरt++;
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_fba_fill_geometry(काष्ठा dasd_block *block,
				  काष्ठा hd_geometry *geo)
अणु
	अगर (dasd_check_blocksize(block->bp_block) != 0)
		वापस -EINVAL;
	geo->cylinders = (block->blocks << block->s2b_shअगरt) >> 10;
	geo->heads = 16;
	geo->sectors = 128 >> block->s2b_shअगरt;
	वापस 0;
पूर्ण

अटल dasd_erp_fn_t
dasd_fba_erp_action(काष्ठा dasd_ccw_req * cqr)
अणु
	वापस dasd_शेष_erp_action;
पूर्ण

अटल dasd_erp_fn_t
dasd_fba_erp_postaction(काष्ठा dasd_ccw_req * cqr)
अणु
	अगर (cqr->function == dasd_शेष_erp_action)
		वापस dasd_शेष_erp_postaction;

	DBF_DEV_EVENT(DBF_WARNING, cqr->startdev, "unknown ERP action %p",
		    cqr->function);
	वापस शून्य;
पूर्ण

अटल व्योम dasd_fba_check_क्रम_device_change(काष्ठा dasd_device *device,
					     काष्ठा dasd_ccw_req *cqr,
					     काष्ठा irb *irb)
अणु
	अक्षर mask;

	/* first of all check क्रम state change pending पूर्णांकerrupt */
	mask = DEV_STAT_ATTENTION | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP;
	अगर ((irb->scsw.cmd.dstat & mask) == mask)
		dasd_generic_handle_state_change(device);
पूर्ण;


/*
 * Builds a CCW with no data payload
 */
अटल व्योम ccw_ग_लिखो_no_data(काष्ठा ccw1 *ccw)
अणु
	ccw->cmd_code = DASD_FBA_CCW_WRITE;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 0;
पूर्ण

/*
 * Builds a CCW that ग_लिखोs only zeroes.
 */
अटल व्योम ccw_ग_लिखो_zero(काष्ठा ccw1 *ccw, पूर्णांक count)
अणु
	ccw->cmd_code = DASD_FBA_CCW_WRITE;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = count;
	ccw->cda = (__u32) (addr_t) dasd_fba_zero_page;
पूर्ण

/*
 * Helper function to count the amount of necessary CCWs within a given range
 * with 4k alignment and command chaining in mind.
 */
अटल पूर्णांक count_ccws(sector_t first_rec, sector_t last_rec,
		      अचिन्हित पूर्णांक blocks_per_page)
अणु
	sector_t wz_stop = 0, d_stop = 0;
	पूर्णांक cur_pos = 0;
	पूर्णांक count = 0;

	अगर (first_rec % blocks_per_page != 0) अणु
		wz_stop = first_rec + blocks_per_page -
			(first_rec % blocks_per_page) - 1;
		अगर (wz_stop > last_rec)
			wz_stop = last_rec;
		cur_pos = wz_stop - first_rec + 1;
		count++;
	पूर्ण

	अगर (last_rec - (first_rec + cur_pos) + 1 >= blocks_per_page) अणु
		अगर ((last_rec - blocks_per_page + 1) % blocks_per_page != 0)
			d_stop = last_rec - ((last_rec - blocks_per_page + 1) %
					     blocks_per_page);
		अन्यथा
			d_stop = last_rec;

		cur_pos += d_stop - (first_rec + cur_pos) + 1;
		count++;
	पूर्ण

	अगर (cur_pos == 0 || first_rec + cur_pos - 1 < last_rec)
		count++;

	वापस count;
पूर्ण

/*
 * This function builds a CCW request क्रम block layer discard requests.
 * Each page in the z/VM hypervisor that represents certain records of an FBA
 * device will be padded with zeros. This is a special behaviour of the WRITE
 * command which is triggered when no data payload is added to the CCW.
 *
 * Note: Due to issues in some z/VM versions, we can't fully utilise this
 * special behaviour. We have to keep a 4k (or 8 block) alignment in mind to
 * work around those issues and ग_लिखो actual zeroes to the unaligned parts in
 * the request. This workaround might be हटाओd in the future.
 */
अटल काष्ठा dasd_ccw_req *dasd_fba_build_cp_discard(
						काष्ठा dasd_device *memdev,
						काष्ठा dasd_block *block,
						काष्ठा request *req)
अणु
	काष्ठा LO_fba_data *LO_data;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;

	sector_t wz_stop = 0, d_stop = 0;
	sector_t first_rec, last_rec;

	अचिन्हित पूर्णांक blksize = block->bp_block;
	अचिन्हित पूर्णांक blocks_per_page;
	पूर्णांक wz_count = 0;
	पूर्णांक d_count = 0;
	पूर्णांक cur_pos = 0; /* Current position within the extent */
	पूर्णांक count = 0;
	पूर्णांक cplength;
	पूर्णांक datasize;
	पूर्णांक nr_ccws;

	first_rec = blk_rq_pos(req) >> block->s2b_shअगरt;
	last_rec =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shअगरt;
	count = last_rec - first_rec + 1;

	blocks_per_page = BLOCKS_PER_PAGE(blksize);
	nr_ccws = count_ccws(first_rec, last_rec, blocks_per_page);

	/* define extent + nr_ccws * locate record + nr_ccws * single CCW */
	cplength = 1 + 2 * nr_ccws;
	datasize = माप(काष्ठा DE_fba_data) +
		nr_ccws * (माप(काष्ठा LO_fba_data) + माप(काष्ठा ccw1));

	cqr = dasd_sदो_स्मृति_request(DASD_FBA_MAGIC, cplength, datasize, memdev,
				   blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;

	ccw = cqr->cpaddr;

	define_extent(ccw++, cqr->data, WRITE, blksize, first_rec, count);
	LO_data = cqr->data + माप(काष्ठा DE_fba_data);

	/* First part is not aligned. Calculate range to ग_लिखो zeroes. */
	अगर (first_rec % blocks_per_page != 0) अणु
		wz_stop = first_rec + blocks_per_page -
			(first_rec % blocks_per_page) - 1;
		अगर (wz_stop > last_rec)
			wz_stop = last_rec;
		wz_count = wz_stop - first_rec + 1;

		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, WRITE, cur_pos, wz_count);

		ccw[-1].flags |= CCW_FLAG_CC;
		ccw_ग_लिखो_zero(ccw++, wz_count * blksize);

		cur_pos = wz_count;
	पूर्ण

	/* We can करो proper discard when we've got at least blocks_per_page blocks. */
	अगर (last_rec - (first_rec + cur_pos) + 1 >= blocks_per_page) अणु
		/* is last record at page boundary? */
		अगर ((last_rec - blocks_per_page + 1) % blocks_per_page != 0)
			d_stop = last_rec - ((last_rec - blocks_per_page + 1) %
					     blocks_per_page);
		अन्यथा
			d_stop = last_rec;

		d_count = d_stop - (first_rec + cur_pos) + 1;

		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, WRITE, cur_pos, d_count);

		ccw[-1].flags |= CCW_FLAG_CC;
		ccw_ग_लिखो_no_data(ccw++);

		cur_pos += d_count;
	पूर्ण

	/* We might still have some bits left which need to be zeroed. */
	अगर (cur_pos == 0 || first_rec + cur_pos - 1 < last_rec) अणु
		अगर (d_stop != 0)
			wz_count = last_rec - d_stop;
		अन्यथा अगर (wz_stop != 0)
			wz_count = last_rec - wz_stop;
		अन्यथा
			wz_count = count;

		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, WRITE, cur_pos, wz_count);

		ccw[-1].flags |= CCW_FLAG_CC;
		ccw_ग_लिखो_zero(ccw++, wz_count * blksize);
	पूर्ण

	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);

	cqr->startdev = memdev;
	cqr->memdev = memdev;
	cqr->block = block;
	cqr->expires = memdev->शेष_expires * HZ;	/* शेष 5 minutes */
	cqr->retries = memdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	वापस cqr;
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_fba_build_cp_regular(
						काष्ठा dasd_device *memdev,
						काष्ठा dasd_block *block,
						काष्ठा request *req)
अणु
	काष्ठा dasd_fba_निजी *निजी = block->base->निजी;
	अचिन्हित दीर्घ *idaws;
	काष्ठा LO_fba_data *LO_data;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst;
	पूर्णांक count, cidaw, cplength, datasize;
	sector_t recid, first_rec, last_rec;
	अचिन्हित पूर्णांक blksize, off;
	अचिन्हित अक्षर cmd;

	अगर (rq_data_dir(req) == READ) अणु
		cmd = DASD_FBA_CCW_READ;
	पूर्ण अन्यथा अगर (rq_data_dir(req) == WRITE) अणु
		cmd = DASD_FBA_CCW_WRITE;
	पूर्ण अन्यथा
		वापस ERR_PTR(-EINVAL);
	blksize = block->bp_block;
	/* Calculate record id of first and last block. */
	first_rec = blk_rq_pos(req) >> block->s2b_shअगरt;
	last_rec =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shअगरt;
	/* Check काष्ठा bio and count the number of blocks क्रम the request. */
	count = 0;
	cidaw = 0;
	rq_क्रम_each_segment(bv, req, iter) अणु
		अगर (bv.bv_len & (blksize - 1))
			/* Fba can only करो full blocks. */
			वापस ERR_PTR(-EINVAL);
		count += bv.bv_len >> (block->s2b_shअगरt + 9);
		अगर (idal_is_needed (page_address(bv.bv_page), bv.bv_len))
			cidaw += bv.bv_len / blksize;
	पूर्ण
	/* Paranoia. */
	अगर (count != last_rec - first_rec + 1)
		वापस ERR_PTR(-EINVAL);
	/* 1x define extent + 1x locate record + number of blocks */
	cplength = 2 + count;
	/* 1x define extent + 1x locate record */
	datasize = माप(काष्ठा DE_fba_data) + माप(काष्ठा LO_fba_data) +
		cidaw * माप(अचिन्हित दीर्घ);
	/*
	 * Find out number of additional locate record ccws अगर the device
	 * can't करो data chaining.
	 */
	अगर (निजी->rdc_data.mode.bits.data_chain == 0) अणु
		cplength += count - 1;
		datasize += (count - 1)*माप(काष्ठा LO_fba_data);
	पूर्ण
	/* Allocate the ccw request. */
	cqr = dasd_sदो_स्मृति_request(DASD_FBA_MAGIC, cplength, datasize, memdev,
				   blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;
	ccw = cqr->cpaddr;
	/* First ccw is define extent. */
	define_extent(ccw++, cqr->data, rq_data_dir(req),
		      block->bp_block, blk_rq_pos(req), blk_rq_sectors(req));
	/* Build locate_record + पढ़ो/ग_लिखो ccws. */
	idaws = (अचिन्हित दीर्घ *) (cqr->data + माप(काष्ठा DE_fba_data));
	LO_data = (काष्ठा LO_fba_data *) (idaws + cidaw);
	/* Locate record क्रम all blocks क्रम smart devices. */
	अगर (निजी->rdc_data.mode.bits.data_chain != 0) अणु
		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, rq_data_dir(req), 0, count);
	पूर्ण
	recid = first_rec;
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		अगर (dasd_page_cache) अणु
			अक्षर *copy = kmem_cache_alloc(dasd_page_cache,
						      GFP_DMA | __GFP_NOWARN);
			अगर (copy && rq_data_dir(req) == WRITE)
				स_नकल(copy + bv.bv_offset, dst, bv.bv_len);
			अगर (copy)
				dst = copy + bv.bv_offset;
		पूर्ण
		क्रम (off = 0; off < bv.bv_len; off += blksize) अणु
			/* Locate record क्रम stupid devices. */
			अगर (निजी->rdc_data.mode.bits.data_chain == 0) अणु
				ccw[-1].flags |= CCW_FLAG_CC;
				locate_record(ccw, LO_data++,
					      rq_data_dir(req),
					      recid - first_rec, 1);
				ccw->flags = CCW_FLAG_CC;
				ccw++;
			पूर्ण अन्यथा अणु
				अगर (recid > first_rec)
					ccw[-1].flags |= CCW_FLAG_DC;
				अन्यथा
					ccw[-1].flags |= CCW_FLAG_CC;
			पूर्ण
			ccw->cmd_code = cmd;
			ccw->count = block->bp_block;
			अगर (idal_is_needed(dst, blksize)) अणु
				ccw->cda = (__u32)(addr_t) idaws;
				ccw->flags = CCW_FLAG_IDA;
				idaws = idal_create_words(idaws, dst, blksize);
			पूर्ण अन्यथा अणु
				ccw->cda = (__u32)(addr_t) dst;
				ccw->flags = 0;
			पूर्ण
			ccw++;
			dst += blksize;
			recid++;
		पूर्ण
	पूर्ण
	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->startdev = memdev;
	cqr->memdev = memdev;
	cqr->block = block;
	cqr->expires = memdev->शेष_expires * HZ;	/* शेष 5 minutes */
	cqr->retries = memdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	वापस cqr;
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_fba_build_cp(काष्ठा dasd_device *memdev,
					      काष्ठा dasd_block *block,
					      काष्ठा request *req)
अणु
	अगर (req_op(req) == REQ_OP_DISCARD || req_op(req) == REQ_OP_WRITE_ZEROES)
		वापस dasd_fba_build_cp_discard(memdev, block, req);
	अन्यथा
		वापस dasd_fba_build_cp_regular(memdev, block, req);
पूर्ण

अटल पूर्णांक
dasd_fba_मुक्त_cp(काष्ठा dasd_ccw_req *cqr, काष्ठा request *req)
अणु
	काष्ठा dasd_fba_निजी *निजी = cqr->block->base->निजी;
	काष्ठा ccw1 *ccw;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst, *cda;
	अचिन्हित पूर्णांक blksize, off;
	पूर्णांक status;

	अगर (!dasd_page_cache)
		जाओ out;
	blksize = cqr->block->bp_block;
	ccw = cqr->cpaddr;
	/* Skip over define extent & locate record. */
	ccw++;
	अगर (निजी->rdc_data.mode.bits.data_chain != 0)
		ccw++;
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		क्रम (off = 0; off < bv.bv_len; off += blksize) अणु
			/* Skip locate record. */
			अगर (निजी->rdc_data.mode.bits.data_chain == 0)
				ccw++;
			अगर (dst) अणु
				अगर (ccw->flags & CCW_FLAG_IDA)
					cda = *((अक्षर **)((addr_t) ccw->cda));
				अन्यथा
					cda = (अक्षर *)((addr_t) ccw->cda);
				अगर (dst != cda) अणु
					अगर (rq_data_dir(req) == READ)
						स_नकल(dst, cda, bv.bv_len);
					kmem_cache_मुक्त(dasd_page_cache,
					    (व्योम *)((addr_t)cda & PAGE_MASK));
				पूर्ण
				dst = शून्य;
			पूर्ण
			ccw++;
		पूर्ण
	पूर्ण
out:
	status = cqr->status == DASD_CQR_DONE;
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस status;
पूर्ण

अटल व्योम dasd_fba_handle_terminated_request(काष्ठा dasd_ccw_req *cqr)
अणु
	अगर (cqr->retries < 0)
		cqr->status = DASD_CQR_FAILED;
	अन्यथा
		cqr->status = DASD_CQR_FILLED;
पूर्ण;

अटल पूर्णांक
dasd_fba_fill_info(काष्ठा dasd_device * device,
		   काष्ठा dasd_inक्रमmation2_t * info)
अणु
	काष्ठा dasd_fba_निजी *निजी = device->निजी;

	info->label_block = 1;
	info->FBA_layout = 1;
	info->क्रमmat = DASD_FORMAT_LDL;
	info->अक्षरacteristics_size = माप(निजी->rdc_data);
	स_नकल(info->अक्षरacteristics, &निजी->rdc_data,
	       माप(निजी->rdc_data));
	info->confdata_size = 0;
	वापस 0;
पूर्ण

अटल व्योम
dasd_fba_dump_sense_dbf(काष्ठा dasd_device *device, काष्ठा irb *irb,
			अक्षर *reason)
अणु
	u64 *sense;

	sense = (u64 *) dasd_get_sense(irb);
	अगर (sense) अणु
		DBF_DEV_EVENT(DBF_EMERG, device,
			      "%s: %s %02x%02x%02x %016llx %016llx %016llx "
			      "%016llx", reason,
			      scsw_is_पंचांग(&irb->scsw) ? "t" : "c",
			      scsw_cc(&irb->scsw), scsw_cstat(&irb->scsw),
			      scsw_dstat(&irb->scsw), sense[0], sense[1],
			      sense[2], sense[3]);
	पूर्ण अन्यथा अणु
		DBF_DEV_EVENT(DBF_EMERG, device, "%s",
			      "SORRY - NO VALID SENSE AVAILABLE\n");
	पूर्ण
पूर्ण


अटल व्योम
dasd_fba_dump_sense(काष्ठा dasd_device *device, काष्ठा dasd_ccw_req * req,
		    काष्ठा irb *irb)
अणु
	अक्षर *page;
	काष्ठा ccw1 *act, *end, *last;
	पूर्णांक len, sl, sct, count;

	page = (अक्षर *) get_zeroed_page(GFP_ATOMIC);
	अगर (page == शून्य) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "No memory to dump sense data");
		वापस;
	पूर्ण
	len = प्र_लिखो(page, PRINTK_HEADER
		      " I/O status report for device %s:\n",
		      dev_name(&device->cdev->dev));
	len += प्र_लिखो(page + len, PRINTK_HEADER
		       " in req: %p CS: 0x%02X DS: 0x%02X\n", req,
		       irb->scsw.cmd.cstat, irb->scsw.cmd.dstat);
	len += प्र_लिखो(page + len, PRINTK_HEADER
		       " device %s: Failing CCW: %p\n",
		       dev_name(&device->cdev->dev),
		       (व्योम *) (addr_t) irb->scsw.cmd.cpa);
	अगर (irb->esw.esw0.erw.cons) अणु
		क्रम (sl = 0; sl < 4; sl++) अणु
			len += प्र_लिखो(page + len, PRINTK_HEADER
				       " Sense(hex) %2d-%2d:",
				       (8 * sl), ((8 * sl) + 7));

			क्रम (sct = 0; sct < 8; sct++) अणु
				len += प्र_लिखो(page + len, " %02x",
					       irb->ecw[8 * sl + sct]);
			पूर्ण
			len += प्र_लिखो(page + len, "\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " SORRY - NO VALID SENSE AVAILABLE\n");
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s", page);

	/* dump the Channel Program */
	/* prपूर्णांक first CCWs (maximum 8) */
	act = req->cpaddr;
        क्रम (last = act; last->flags & (CCW_FLAG_CC | CCW_FLAG_DC); last++);
	end = min(act + 8, last);
	len = प्र_लिखो(page, PRINTK_HEADER " Related CP in req: %p\n", req);
	जबतक (act <= end) अणु
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " CCW %p: %08X %08X DAT:",
			       act, ((पूर्णांक *) act)[0], ((पूर्णांक *) act)[1]);
		क्रम (count = 0; count < 32 && count < act->count;
		     count += माप(पूर्णांक))
			len += प्र_लिखो(page + len, " %08X",
				       ((पूर्णांक *) (addr_t) act->cda)
				       [(count>>2)]);
		len += प्र_लिखो(page + len, "\n");
		act++;
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s", page);


	/* prपूर्णांक failing CCW area */
	len = 0;
	अगर (act <  ((काष्ठा ccw1 *)(addr_t) irb->scsw.cmd.cpa) - 2) अणु
		act = ((काष्ठा ccw1 *)(addr_t) irb->scsw.cmd.cpa) - 2;
		len += प्र_लिखो(page + len, PRINTK_HEADER "......\n");
	पूर्ण
	end = min((काष्ठा ccw1 *)(addr_t) irb->scsw.cmd.cpa + 2, last);
	जबतक (act <= end) अणु
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " CCW %p: %08X %08X DAT:",
			       act, ((पूर्णांक *) act)[0], ((पूर्णांक *) act)[1]);
		क्रम (count = 0; count < 32 && count < act->count;
		     count += माप(पूर्णांक))
			len += प्र_लिखो(page + len, " %08X",
				       ((पूर्णांक *) (addr_t) act->cda)
				       [(count>>2)]);
		len += प्र_लिखो(page + len, "\n");
		act++;
	पूर्ण

	/* prपूर्णांक last CCWs */
	अगर (act <  last - 2) अणु
		act = last - 2;
		len += प्र_लिखो(page + len, PRINTK_HEADER "......\n");
	पूर्ण
	जबतक (act <= last) अणु
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " CCW %p: %08X %08X DAT:",
			       act, ((पूर्णांक *) act)[0], ((पूर्णांक *) act)[1]);
		क्रम (count = 0; count < 32 && count < act->count;
		     count += माप(पूर्णांक))
			len += प्र_लिखो(page + len, " %08X",
				       ((पूर्णांक *) (addr_t) act->cda)
				       [(count>>2)]);
		len += प्र_लिखो(page + len, "\n");
		act++;
	पूर्ण
	अगर (len > 0)
		prपूर्णांकk(KERN_ERR "%s", page);
	मुक्त_page((अचिन्हित दीर्घ) page);
पूर्ण

/*
 * Initialize block layer request queue.
 */
अटल व्योम dasd_fba_setup_blk_queue(काष्ठा dasd_block *block)
अणु
	अचिन्हित पूर्णांक logical_block_size = block->bp_block;
	काष्ठा request_queue *q = block->request_queue;
	अचिन्हित पूर्णांक max_bytes, max_discard_sectors;
	पूर्णांक max;

	max = DASD_FBA_MAX_BLOCKS << block->s2b_shअगरt;
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	q->limits.max_dev_sectors = max;
	blk_queue_logical_block_size(q, logical_block_size);
	blk_queue_max_hw_sectors(q, max);
	blk_queue_max_segments(q, अच_लघु_उच्च);
	/* With page sized segments each segment can be translated पूर्णांकo one idaw/tidaw */
	blk_queue_max_segment_size(q, PAGE_SIZE);
	blk_queue_segment_boundary(q, PAGE_SIZE - 1);

	q->limits.discard_granularity = logical_block_size;
	q->limits.discard_alignment = PAGE_SIZE;

	/* Calculate max_discard_sectors and make it PAGE aligned */
	max_bytes = अच_लघु_उच्च * logical_block_size;
	max_bytes = ALIGN_DOWN(max_bytes, PAGE_SIZE);
	max_discard_sectors = max_bytes / logical_block_size;

	blk_queue_max_discard_sectors(q, max_discard_sectors);
	blk_queue_max_ग_लिखो_zeroes_sectors(q, max_discard_sectors);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
पूर्ण

अटल पूर्णांक dasd_fba_pe_handler(काष्ठा dasd_device *device,
			       __u8 tbvpm, __u8 fcsecpm)
अणु
	वापस dasd_generic_verअगरy_path(device, tbvpm);
पूर्ण

अटल काष्ठा dasd_discipline dasd_fba_discipline = अणु
	.owner = THIS_MODULE,
	.name = "FBA ",
	.ebcname = "FBA ",
	.check_device = dasd_fba_check_अक्षरacteristics,
	.करो_analysis = dasd_fba_करो_analysis,
	.pe_handler = dasd_fba_pe_handler,
	.setup_blk_queue = dasd_fba_setup_blk_queue,
	.fill_geometry = dasd_fba_fill_geometry,
	.start_IO = dasd_start_IO,
	.term_IO = dasd_term_IO,
	.handle_terminated_request = dasd_fba_handle_terminated_request,
	.erp_action = dasd_fba_erp_action,
	.erp_postaction = dasd_fba_erp_postaction,
	.check_क्रम_device_change = dasd_fba_check_क्रम_device_change,
	.build_cp = dasd_fba_build_cp,
	.मुक्त_cp = dasd_fba_मुक्त_cp,
	.dump_sense = dasd_fba_dump_sense,
	.dump_sense_dbf = dasd_fba_dump_sense_dbf,
	.fill_info = dasd_fba_fill_info,
पूर्ण;

अटल पूर्णांक __init
dasd_fba_init(व्योम)
अणु
	पूर्णांक ret;

	ASCEBC(dasd_fba_discipline.ebcname, 4);

	dasd_fba_zero_page = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!dasd_fba_zero_page)
		वापस -ENOMEM;

	ret = ccw_driver_रेजिस्टर(&dasd_fba_driver);
	अगर (!ret)
		रुको_क्रम_device_probe();

	वापस ret;
पूर्ण

अटल व्योम __निकास
dasd_fba_cleanup(व्योम)
अणु
	ccw_driver_unरेजिस्टर(&dasd_fba_driver);
	मुक्त_page((अचिन्हित दीर्घ)dasd_fba_zero_page);
पूर्ण

module_init(dasd_fba_init);
module_निकास(dasd_fba_cleanup);
