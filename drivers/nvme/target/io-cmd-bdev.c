<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVMe I/O command implementation.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश "nvmet.h"

व्योम nvmet_bdev_set_limits(काष्ठा block_device *bdev, काष्ठा nvme_id_ns *id)
अणु
	स्थिर काष्ठा queue_limits *ql = &bdev_get_queue(bdev)->limits;
	/* Number of logical blocks per physical block. */
	स्थिर u32 lpp = ql->physical_block_size / ql->logical_block_size;
	/* Logical blocks per physical block, 0's based. */
	स्थिर __le16 lpp0b = to0based(lpp);

	/*
	 * For NVMe 1.2 and later, bit 1 indicates that the fields NAWUN,
	 * NAWUPF, and NACWU are defined क्रम this namespace and should be
	 * used by the host क्रम this namespace instead of the AWUN, AWUPF,
	 * and ACWU fields in the Identअगरy Controller data काष्ठाure. If
	 * any of these fields are zero that means that the corresponding
	 * field from the identअगरy controller data काष्ठाure should be used.
	 */
	id->nsfeat |= 1 << 1;
	id->nawun = lpp0b;
	id->nawupf = lpp0b;
	id->nacwu = lpp0b;

	/*
	 * Bit 4 indicates that the fields NPWG, NPWA, NPDG, NPDA, and
	 * NOWS are defined क्रम this namespace and should be used by
	 * the host क्रम I/O optimization.
	 */
	id->nsfeat |= 1 << 4;
	/* NPWG = Namespace Preferred Write Granularity. 0's based */
	id->npwg = lpp0b;
	/* NPWA = Namespace Preferred Write Alignment. 0's based */
	id->npwa = id->npwg;
	/* NPDG = Namespace Preferred Deallocate Granularity. 0's based */
	id->npdg = to0based(ql->discard_granularity / ql->logical_block_size);
	/* NPDG = Namespace Preferred Deallocate Alignment */
	id->npda = id->npdg;
	/* NOWS = Namespace Optimal Write Size */
	id->nows = to0based(ql->io_opt / ql->logical_block_size);
पूर्ण

अटल व्योम nvmet_bdev_ns_enable_पूर्णांकegrity(काष्ठा nvmet_ns *ns)
अणु
	काष्ठा blk_पूर्णांकegrity *bi = bdev_get_पूर्णांकegrity(ns->bdev);

	अगर (bi) अणु
		ns->metadata_size = bi->tuple_size;
		अगर (bi->profile == &t10_pi_type1_crc)
			ns->pi_type = NVME_NS_DPS_PI_TYPE1;
		अन्यथा अगर (bi->profile == &t10_pi_type3_crc)
			ns->pi_type = NVME_NS_DPS_PI_TYPE3;
		अन्यथा
			/* Unsupported metadata type */
			ns->metadata_size = 0;
	पूर्ण
पूर्ण

पूर्णांक nvmet_bdev_ns_enable(काष्ठा nvmet_ns *ns)
अणु
	पूर्णांक ret;

	ns->bdev = blkdev_get_by_path(ns->device_path,
			FMODE_READ | FMODE_WRITE, शून्य);
	अगर (IS_ERR(ns->bdev)) अणु
		ret = PTR_ERR(ns->bdev);
		अगर (ret != -ENOTBLK) अणु
			pr_err("failed to open block device %s: (%ld)\n",
					ns->device_path, PTR_ERR(ns->bdev));
		पूर्ण
		ns->bdev = शून्य;
		वापस ret;
	पूर्ण
	ns->size = i_size_पढ़ो(ns->bdev->bd_inode);
	ns->blksize_shअगरt = blksize_bits(bdev_logical_block_size(ns->bdev));

	ns->pi_type = 0;
	ns->metadata_size = 0;
	अगर (IS_ENABLED(CONFIG_BLK_DEV_INTEGRITY_T10))
		nvmet_bdev_ns_enable_पूर्णांकegrity(ns);

	वापस 0;
पूर्ण

व्योम nvmet_bdev_ns_disable(काष्ठा nvmet_ns *ns)
अणु
	अगर (ns->bdev) अणु
		blkdev_put(ns->bdev, FMODE_WRITE | FMODE_READ);
		ns->bdev = शून्य;
	पूर्ण
पूर्ण

व्योम nvmet_bdev_ns_revalidate(काष्ठा nvmet_ns *ns)
अणु
	ns->size = i_size_पढ़ो(ns->bdev->bd_inode);
पूर्ण

अटल u16 blk_to_nvme_status(काष्ठा nvmet_req *req, blk_status_t blk_sts)
अणु
	u16 status = NVME_SC_SUCCESS;

	अगर (likely(blk_sts == BLK_STS_OK))
		वापस status;
	/*
	 * Right now there exists M : 1 mapping between block layer error
	 * to the NVMe status code (see nvme_error_status()). For consistency,
	 * when we reverse map we use most appropriate NVMe Status code from
	 * the group of the NVMe staus codes used in the nvme_error_status().
	 */
	चयन (blk_sts) अणु
	हाल BLK_STS_NOSPC:
		status = NVME_SC_CAP_EXCEEDED | NVME_SC_DNR;
		req->error_loc = दुरत्व(काष्ठा nvme_rw_command, length);
		अवरोध;
	हाल BLK_STS_TARGET:
		status = NVME_SC_LBA_RANGE | NVME_SC_DNR;
		req->error_loc = दुरत्व(काष्ठा nvme_rw_command, slba);
		अवरोध;
	हाल BLK_STS_NOTSUPP:
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
		चयन (req->cmd->common.opcode) अणु
		हाल nvme_cmd_dsm:
		हाल nvme_cmd_ग_लिखो_zeroes:
			status = NVME_SC_ONCS_NOT_SUPPORTED | NVME_SC_DNR;
			अवरोध;
		शेष:
			status = NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
		पूर्ण
		अवरोध;
	हाल BLK_STS_MEDIUM:
		status = NVME_SC_ACCESS_DENIED;
		req->error_loc = दुरत्व(काष्ठा nvme_rw_command, nsid);
		अवरोध;
	हाल BLK_STS_IOERR:
	शेष:
		status = NVME_SC_INTERNAL | NVME_SC_DNR;
		req->error_loc = दुरत्व(काष्ठा nvme_common_command, opcode);
	पूर्ण

	चयन (req->cmd->common.opcode) अणु
	हाल nvme_cmd_पढ़ो:
	हाल nvme_cmd_ग_लिखो:
		req->error_slba = le64_to_cpu(req->cmd->rw.slba);
		अवरोध;
	हाल nvme_cmd_ग_लिखो_zeroes:
		req->error_slba =
			le64_to_cpu(req->cmd->ग_लिखो_zeroes.slba);
		अवरोध;
	शेष:
		req->error_slba = 0;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम nvmet_bio_करोne(काष्ठा bio *bio)
अणु
	काष्ठा nvmet_req *req = bio->bi_निजी;

	nvmet_req_complete(req, blk_to_nvme_status(req, bio->bi_status));
	अगर (bio != &req->b.अंतरभूत_bio)
		bio_put(bio);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल पूर्णांक nvmet_bdev_alloc_bip(काष्ठा nvmet_req *req, काष्ठा bio *bio,
				काष्ठा sg_mapping_iter *miter)
अणु
	काष्ठा blk_पूर्णांकegrity *bi;
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	काष्ठा block_device *bdev = req->ns->bdev;
	पूर्णांक rc;
	माप_प्रकार resid, len;

	bi = bdev_get_पूर्णांकegrity(bdev);
	अगर (unlikely(!bi)) अणु
		pr_err("Unable to locate bio_integrity\n");
		वापस -ENODEV;
	पूर्ण

	bip = bio_पूर्णांकegrity_alloc(bio, GFP_NOIO,
					bio_max_segs(req->metadata_sg_cnt));
	अगर (IS_ERR(bip)) अणु
		pr_err("Unable to allocate bio_integrity_payload\n");
		वापस PTR_ERR(bip);
	पूर्ण

	bip->bip_iter.bi_size = bio_पूर्णांकegrity_bytes(bi, bio_sectors(bio));
	/* भव start sector must be in पूर्णांकegrity पूर्णांकerval units */
	bip_set_seed(bip, bio->bi_iter.bi_sector >>
		     (bi->पूर्णांकerval_exp - SECTOR_SHIFT));

	resid = bip->bip_iter.bi_size;
	जबतक (resid > 0 && sg_miter_next(miter)) अणु
		len = min_t(माप_प्रकार, miter->length, resid);
		rc = bio_पूर्णांकegrity_add_page(bio, miter->page, len,
					    offset_in_page(miter->addr));
		अगर (unlikely(rc != len)) अणु
			pr_err("bio_integrity_add_page() failed; %d\n", rc);
			sg_miter_stop(miter);
			वापस -ENOMEM;
		पूर्ण

		resid -= len;
		अगर (len < miter->length)
			miter->consumed -= miter->length - len;
	पूर्ण
	sg_miter_stop(miter);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक nvmet_bdev_alloc_bip(काष्ठा nvmet_req *req, काष्ठा bio *bio,
				काष्ठा sg_mapping_iter *miter)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

अटल व्योम nvmet_bdev_execute_rw(काष्ठा nvmet_req *req)
अणु
	अचिन्हित पूर्णांक sg_cnt = req->sg_cnt;
	काष्ठा bio *bio;
	काष्ठा scatterlist *sg;
	काष्ठा blk_plug plug;
	sector_t sector;
	पूर्णांक op, i, rc;
	काष्ठा sg_mapping_iter prot_miter;
	अचिन्हित पूर्णांक iter_flags;
	अचिन्हित पूर्णांक total_len = nvmet_rw_data_len(req) + req->metadata_len;

	अगर (!nvmet_check_transfer_len(req, total_len))
		वापस;

	अगर (!req->sg_cnt) अणु
		nvmet_req_complete(req, 0);
		वापस;
	पूर्ण

	अगर (req->cmd->rw.opcode == nvme_cmd_ग_लिखो) अणु
		op = REQ_OP_WRITE | REQ_SYNC | REQ_IDLE;
		अगर (req->cmd->rw.control & cpu_to_le16(NVME_RW_FUA))
			op |= REQ_FUA;
		iter_flags = SG_MITER_TO_SG;
	पूर्ण अन्यथा अणु
		op = REQ_OP_READ;
		iter_flags = SG_MITER_FROM_SG;
	पूर्ण

	अगर (is_pci_p2pdma_page(sg_page(req->sg)))
		op |= REQ_NOMERGE;

	sector = nvmet_lba_to_sect(req->ns, req->cmd->rw.slba);

	अगर (nvmet_use_अंतरभूत_bvec(req)) अणु
		bio = &req->b.अंतरभूत_bio;
		bio_init(bio, req->अंतरभूत_bvec, ARRAY_SIZE(req->अंतरभूत_bvec));
	पूर्ण अन्यथा अणु
		bio = bio_alloc(GFP_KERNEL, bio_max_segs(sg_cnt));
	पूर्ण
	bio_set_dev(bio, req->ns->bdev);
	bio->bi_iter.bi_sector = sector;
	bio->bi_निजी = req;
	bio->bi_end_io = nvmet_bio_करोne;
	bio->bi_opf = op;

	blk_start_plug(&plug);
	अगर (req->metadata_len)
		sg_miter_start(&prot_miter, req->metadata_sg,
			       req->metadata_sg_cnt, iter_flags);

	क्रम_each_sg(req->sg, sg, req->sg_cnt, i) अणु
		जबतक (bio_add_page(bio, sg_page(sg), sg->length, sg->offset)
				!= sg->length) अणु
			काष्ठा bio *prev = bio;

			अगर (req->metadata_len) अणु
				rc = nvmet_bdev_alloc_bip(req, bio,
							  &prot_miter);
				अगर (unlikely(rc)) अणु
					bio_io_error(bio);
					वापस;
				पूर्ण
			पूर्ण

			bio = bio_alloc(GFP_KERNEL, bio_max_segs(sg_cnt));
			bio_set_dev(bio, req->ns->bdev);
			bio->bi_iter.bi_sector = sector;
			bio->bi_opf = op;

			bio_chain(bio, prev);
			submit_bio(prev);
		पूर्ण

		sector += sg->length >> 9;
		sg_cnt--;
	पूर्ण

	अगर (req->metadata_len) अणु
		rc = nvmet_bdev_alloc_bip(req, bio, &prot_miter);
		अगर (unlikely(rc)) अणु
			bio_io_error(bio);
			वापस;
		पूर्ण
	पूर्ण

	submit_bio(bio);
	blk_finish_plug(&plug);
पूर्ण

अटल व्योम nvmet_bdev_execute_flush(काष्ठा nvmet_req *req)
अणु
	काष्ठा bio *bio = &req->b.अंतरभूत_bio;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	bio_init(bio, req->अंतरभूत_bvec, ARRAY_SIZE(req->अंतरभूत_bvec));
	bio_set_dev(bio, req->ns->bdev);
	bio->bi_निजी = req;
	bio->bi_end_io = nvmet_bio_करोne;
	bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;

	submit_bio(bio);
पूर्ण

u16 nvmet_bdev_flush(काष्ठा nvmet_req *req)
अणु
	अगर (blkdev_issue_flush(req->ns->bdev))
		वापस NVME_SC_INTERNAL | NVME_SC_DNR;
	वापस 0;
पूर्ण

अटल u16 nvmet_bdev_discard_range(काष्ठा nvmet_req *req,
		काष्ठा nvme_dsm_range *range, काष्ठा bio **bio)
अणु
	काष्ठा nvmet_ns *ns = req->ns;
	पूर्णांक ret;

	ret = __blkdev_issue_discard(ns->bdev,
			nvmet_lba_to_sect(ns, range->slba),
			le32_to_cpu(range->nlb) << (ns->blksize_shअगरt - 9),
			GFP_KERNEL, 0, bio);
	अगर (ret && ret != -EOPNOTSUPP) अणु
		req->error_slba = le64_to_cpu(range->slba);
		वापस त्रुटि_सं_to_nvme_status(req, ret);
	पूर्ण
	वापस NVME_SC_SUCCESS;
पूर्ण

अटल व्योम nvmet_bdev_execute_discard(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_dsm_range range;
	काष्ठा bio *bio = शून्य;
	पूर्णांक i;
	u16 status;

	क्रम (i = 0; i <= le32_to_cpu(req->cmd->dsm.nr); i++) अणु
		status = nvmet_copy_from_sgl(req, i * माप(range), &range,
				माप(range));
		अगर (status)
			अवरोध;

		status = nvmet_bdev_discard_range(req, &range, &bio);
		अगर (status)
			अवरोध;
	पूर्ण

	अगर (bio) अणु
		bio->bi_निजी = req;
		bio->bi_end_io = nvmet_bio_करोne;
		अगर (status)
			bio_io_error(bio);
		अन्यथा
			submit_bio(bio);
	पूर्ण अन्यथा अणु
		nvmet_req_complete(req, status);
	पूर्ण
पूर्ण

अटल व्योम nvmet_bdev_execute_dsm(काष्ठा nvmet_req *req)
अणु
	अगर (!nvmet_check_data_len_lte(req, nvmet_dsm_len(req)))
		वापस;

	चयन (le32_to_cpu(req->cmd->dsm.attributes)) अणु
	हाल NVME_DSMGMT_AD:
		nvmet_bdev_execute_discard(req);
		वापस;
	हाल NVME_DSMGMT_IDR:
	हाल NVME_DSMGMT_IDW:
	शेष:
		/* Not supported yet */
		nvmet_req_complete(req, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम nvmet_bdev_execute_ग_लिखो_zeroes(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_ग_लिखो_zeroes_cmd *ग_लिखो_zeroes = &req->cmd->ग_लिखो_zeroes;
	काष्ठा bio *bio = शून्य;
	sector_t sector;
	sector_t nr_sector;
	पूर्णांक ret;

	अगर (!nvmet_check_transfer_len(req, 0))
		वापस;

	sector = nvmet_lba_to_sect(req->ns, ग_लिखो_zeroes->slba);
	nr_sector = (((sector_t)le16_to_cpu(ग_लिखो_zeroes->length) + 1) <<
		(req->ns->blksize_shअगरt - 9));

	ret = __blkdev_issue_zeroout(req->ns->bdev, sector, nr_sector,
			GFP_KERNEL, &bio, 0);
	अगर (bio) अणु
		bio->bi_निजी = req;
		bio->bi_end_io = nvmet_bio_करोne;
		submit_bio(bio);
	पूर्ण अन्यथा अणु
		nvmet_req_complete(req, त्रुटि_सं_to_nvme_status(req, ret));
	पूर्ण
पूर्ण

u16 nvmet_bdev_parse_io_cmd(काष्ठा nvmet_req *req)
अणु
	काष्ठा nvme_command *cmd = req->cmd;

	चयन (cmd->common.opcode) अणु
	हाल nvme_cmd_पढ़ो:
	हाल nvme_cmd_ग_लिखो:
		req->execute = nvmet_bdev_execute_rw;
		अगर (req->sq->ctrl->pi_support && nvmet_ns_has_pi(req->ns))
			req->metadata_len = nvmet_rw_metadata_len(req);
		वापस 0;
	हाल nvme_cmd_flush:
		req->execute = nvmet_bdev_execute_flush;
		वापस 0;
	हाल nvme_cmd_dsm:
		req->execute = nvmet_bdev_execute_dsm;
		वापस 0;
	हाल nvme_cmd_ग_लिखो_zeroes:
		req->execute = nvmet_bdev_execute_ग_लिखो_zeroes;
		वापस 0;
	शेष:
		वापस nvmet_report_invalid_opcode(req);
	पूर्ण
पूर्ण
