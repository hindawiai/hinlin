<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nvme-lightnvm.c - LightNVM NVMe device
 *
 * Copyright (C) 2014-2015 IT University of Cखोलोhagen
 * Initial release: Matias Bjorling <mb@lightnvm.io>
 */

#समावेश "nvme.h"

#समावेश <linux/nvme.h>
#समावेश <linux/bitops.h>
#समावेश <linux/lightnvm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <uapi/linux/lightnvm.h>

क्रमागत nvme_nvm_admin_opcode अणु
	nvme_nvm_admin_identity		= 0xe2,
	nvme_nvm_admin_get_bb_tbl	= 0xf2,
	nvme_nvm_admin_set_bb_tbl	= 0xf1,
पूर्ण;

क्रमागत nvme_nvm_log_page अणु
	NVME_NVM_LOG_REPORT_CHUNK	= 0xca,
पूर्ण;

काष्ठा nvme_nvm_ph_rw अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd2;
	__le64			metadata;
	__le64			prp1;
	__le64			prp2;
	__le64			spba;
	__le16			length;
	__le16			control;
	__le32			dsmgmt;
	__le64			resv;
पूर्ण;

काष्ठा nvme_nvm_erase_blk अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd[2];
	__le64			prp1;
	__le64			prp2;
	__le64			spba;
	__le16			length;
	__le16			control;
	__le32			dsmgmt;
	__le64			resv;
पूर्ण;

काष्ठा nvme_nvm_identity अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd[2];
	__le64			prp1;
	__le64			prp2;
	__u32			rsvd11[6];
पूर्ण;

काष्ठा nvme_nvm_getbbtbl अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__u64			rsvd[2];
	__le64			prp1;
	__le64			prp2;
	__le64			spba;
	__u32			rsvd4[4];
पूर्ण;

काष्ठा nvme_nvm_setbbtbl अणु
	__u8			opcode;
	__u8			flags;
	__u16			command_id;
	__le32			nsid;
	__le64			rsvd[2];
	__le64			prp1;
	__le64			prp2;
	__le64			spba;
	__le16			nlb;
	__u8			value;
	__u8			rsvd3;
	__u32			rsvd4[3];
पूर्ण;

काष्ठा nvme_nvm_command अणु
	जोड़ अणु
		काष्ठा nvme_common_command common;
		काष्ठा nvme_nvm_ph_rw ph_rw;
		काष्ठा nvme_nvm_erase_blk erase;
		काष्ठा nvme_nvm_identity identity;
		काष्ठा nvme_nvm_getbbtbl get_bb;
		काष्ठा nvme_nvm_setbbtbl set_bb;
	पूर्ण;
पूर्ण;

काष्ठा nvme_nvm_id12_grp अणु
	__u8			mtype;
	__u8			fmtype;
	__le16			res16;
	__u8			num_ch;
	__u8			num_lun;
	__u8			num_pln;
	__u8			rsvd1;
	__le16			num_chk;
	__le16			num_pg;
	__le16			fpg_sz;
	__le16			csecs;
	__le16			sos;
	__le16			rsvd2;
	__le32			trdt;
	__le32			trdm;
	__le32			tprt;
	__le32			tprm;
	__le32			tbet;
	__le32			tbem;
	__le32			mpos;
	__le32			mccap;
	__le16			cpar;
	__u8			reserved[906];
पूर्ण __packed;

काष्ठा nvme_nvm_id12_addrf अणु
	__u8			ch_offset;
	__u8			ch_len;
	__u8			lun_offset;
	__u8			lun_len;
	__u8			pln_offset;
	__u8			pln_len;
	__u8			blk_offset;
	__u8			blk_len;
	__u8			pg_offset;
	__u8			pg_len;
	__u8			sec_offset;
	__u8			sec_len;
	__u8			res[4];
पूर्ण __packed;

काष्ठा nvme_nvm_id12 अणु
	__u8			ver_id;
	__u8			vmnt;
	__u8			cgrps;
	__u8			res;
	__le32			cap;
	__le32			करोm;
	काष्ठा nvme_nvm_id12_addrf ppaf;
	__u8			resv[228];
	काष्ठा nvme_nvm_id12_grp grp;
	__u8			resv2[2880];
पूर्ण __packed;

काष्ठा nvme_nvm_bb_tbl अणु
	__u8	tblid[4];
	__le16	verid;
	__le16	revid;
	__le32	rvsd1;
	__le32	tblks;
	__le32	tfact;
	__le32	tgrown;
	__le32	tdresv;
	__le32	thresv;
	__le32	rsvd2[8];
	__u8	blk[];
पूर्ण;

काष्ठा nvme_nvm_id20_addrf अणु
	__u8			grp_len;
	__u8			pu_len;
	__u8			chk_len;
	__u8			lba_len;
	__u8			resv[4];
पूर्ण;

काष्ठा nvme_nvm_id20 अणु
	__u8			mjr;
	__u8			mnr;
	__u8			resv[6];

	काष्ठा nvme_nvm_id20_addrf lbaf;

	__le32			mccap;
	__u8			resv2[12];

	__u8			wit;
	__u8			resv3[31];

	/* Geometry */
	__le16			num_grp;
	__le16			num_pu;
	__le32			num_chk;
	__le32			clba;
	__u8			resv4[52];

	/* Write data requirements */
	__le32			ws_min;
	__le32			ws_opt;
	__le32			mw_cunits;
	__le32			maxoc;
	__le32			maxocpu;
	__u8			resv5[44];

	/* Perक्रमmance related metrics */
	__le32			trdt;
	__le32			trdm;
	__le32			twrt;
	__le32			twrm;
	__le32			tcrst;
	__le32			tcrsm;
	__u8			resv6[40];

	/* Reserved area */
	__u8			resv7[2816];

	/* Venकरोr specअगरic */
	__u8			vs[1024];
पूर्ण;

काष्ठा nvme_nvm_chk_meta अणु
	__u8	state;
	__u8	type;
	__u8	wi;
	__u8	rsvd[5];
	__le64	slba;
	__le64	cnlb;
	__le64	wp;
पूर्ण;

/*
 * Check we didn't inadvertently grow the command काष्ठा
 */
अटल अंतरभूत व्योम _nvme_nvm_check_size(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_identity) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_ph_rw) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_erase_blk) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_getbbtbl) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_setbbtbl) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_id12_grp) != 960);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_id12_addrf) != 16);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_id12) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_bb_tbl) != 64);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_id20_addrf) != 8);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_id20) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_chk_meta) != 32);
	BUILD_BUG_ON(माप(काष्ठा nvme_nvm_chk_meta) !=
						माप(काष्ठा nvm_chk_meta));
पूर्ण

अटल व्योम nvme_nvm_set_addr_12(काष्ठा nvm_addrf_12 *dst,
				 काष्ठा nvme_nvm_id12_addrf *src)
अणु
	dst->ch_len = src->ch_len;
	dst->lun_len = src->lun_len;
	dst->blk_len = src->blk_len;
	dst->pg_len = src->pg_len;
	dst->pln_len = src->pln_len;
	dst->sec_len = src->sec_len;

	dst->ch_offset = src->ch_offset;
	dst->lun_offset = src->lun_offset;
	dst->blk_offset = src->blk_offset;
	dst->pg_offset = src->pg_offset;
	dst->pln_offset = src->pln_offset;
	dst->sec_offset = src->sec_offset;

	dst->ch_mask = ((1ULL << dst->ch_len) - 1) << dst->ch_offset;
	dst->lun_mask = ((1ULL << dst->lun_len) - 1) << dst->lun_offset;
	dst->blk_mask = ((1ULL << dst->blk_len) - 1) << dst->blk_offset;
	dst->pg_mask = ((1ULL << dst->pg_len) - 1) << dst->pg_offset;
	dst->pln_mask = ((1ULL << dst->pln_len) - 1) << dst->pln_offset;
	dst->sec_mask = ((1ULL << dst->sec_len) - 1) << dst->sec_offset;
पूर्ण

अटल पूर्णांक nvme_nvm_setup_12(काष्ठा nvme_nvm_id12 *id,
			     काष्ठा nvm_geo *geo)
अणु
	काष्ठा nvme_nvm_id12_grp *src;
	पूर्णांक sec_per_pg, sec_per_pl, pg_per_blk;

	अगर (id->cgrps != 1)
		वापस -EINVAL;

	src = &id->grp;

	अगर (src->mtype != 0) अणु
		pr_err("nvm: memory type not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* 1.2 spec. only reports a single version id - unfold */
	geo->major_ver_id = id->ver_id;
	geo->minor_ver_id = 2;

	/* Set compacted version क्रम upper layers */
	geo->version = NVM_OCSSD_SPEC_12;

	geo->num_ch = src->num_ch;
	geo->num_lun = src->num_lun;
	geo->all_luns = geo->num_ch * geo->num_lun;

	geo->num_chk = le16_to_cpu(src->num_chk);

	geo->csecs = le16_to_cpu(src->csecs);
	geo->sos = le16_to_cpu(src->sos);

	pg_per_blk = le16_to_cpu(src->num_pg);
	sec_per_pg = le16_to_cpu(src->fpg_sz) / geo->csecs;
	sec_per_pl = sec_per_pg * src->num_pln;
	geo->clba = sec_per_pl * pg_per_blk;

	geo->all_chunks = geo->all_luns * geo->num_chk;
	geo->total_secs = geo->clba * geo->all_chunks;

	geo->ws_min = sec_per_pg;
	geo->ws_opt = sec_per_pg;
	geo->mw_cunits = geo->ws_opt << 3;	/* शेष to MLC safe values */

	/* Do not impose values क्रम maximum number of खोलो blocks as it is
	 * unspecअगरied in 1.2. Users of 1.2 must be aware of this and eventually
	 * specअगरy these values through a quirk अगर restrictions apply.
	 */
	geo->maxoc = geo->all_luns * geo->num_chk;
	geo->maxocpu = geo->num_chk;

	geo->mccap = le32_to_cpu(src->mccap);

	geo->trdt = le32_to_cpu(src->trdt);
	geo->trdm = le32_to_cpu(src->trdm);
	geo->tprt = le32_to_cpu(src->tprt);
	geo->tprm = le32_to_cpu(src->tprm);
	geo->tbet = le32_to_cpu(src->tbet);
	geo->tbem = le32_to_cpu(src->tbem);

	/* 1.2 compatibility */
	geo->vmnt = id->vmnt;
	geo->cap = le32_to_cpu(id->cap);
	geo->करोm = le32_to_cpu(id->करोm);

	geo->mtype = src->mtype;
	geo->fmtype = src->fmtype;

	geo->cpar = le16_to_cpu(src->cpar);
	geo->mpos = le32_to_cpu(src->mpos);

	geo->pln_mode = NVM_PLANE_SINGLE;

	अगर (geo->mpos & 0x020202) अणु
		geo->pln_mode = NVM_PLANE_DOUBLE;
		geo->ws_opt <<= 1;
	पूर्ण अन्यथा अगर (geo->mpos & 0x040404) अणु
		geo->pln_mode = NVM_PLANE_QUAD;
		geo->ws_opt <<= 2;
	पूर्ण

	geo->num_pln = src->num_pln;
	geo->num_pg = le16_to_cpu(src->num_pg);
	geo->fpg_sz = le16_to_cpu(src->fpg_sz);

	nvme_nvm_set_addr_12((काष्ठा nvm_addrf_12 *)&geo->addrf, &id->ppaf);

	वापस 0;
पूर्ण

अटल व्योम nvme_nvm_set_addr_20(काष्ठा nvm_addrf *dst,
				 काष्ठा nvme_nvm_id20_addrf *src)
अणु
	dst->ch_len = src->grp_len;
	dst->lun_len = src->pu_len;
	dst->chk_len = src->chk_len;
	dst->sec_len = src->lba_len;

	dst->sec_offset = 0;
	dst->chk_offset = dst->sec_len;
	dst->lun_offset = dst->chk_offset + dst->chk_len;
	dst->ch_offset = dst->lun_offset + dst->lun_len;

	dst->ch_mask = ((1ULL << dst->ch_len) - 1) << dst->ch_offset;
	dst->lun_mask = ((1ULL << dst->lun_len) - 1) << dst->lun_offset;
	dst->chk_mask = ((1ULL << dst->chk_len) - 1) << dst->chk_offset;
	dst->sec_mask = ((1ULL << dst->sec_len) - 1) << dst->sec_offset;
पूर्ण

अटल पूर्णांक nvme_nvm_setup_20(काष्ठा nvme_nvm_id20 *id,
			     काष्ठा nvm_geo *geo)
अणु
	geo->major_ver_id = id->mjr;
	geo->minor_ver_id = id->mnr;

	/* Set compacted version क्रम upper layers */
	geo->version = NVM_OCSSD_SPEC_20;

	geo->num_ch = le16_to_cpu(id->num_grp);
	geo->num_lun = le16_to_cpu(id->num_pu);
	geo->all_luns = geo->num_ch * geo->num_lun;

	geo->num_chk = le32_to_cpu(id->num_chk);
	geo->clba = le32_to_cpu(id->clba);

	geo->all_chunks = geo->all_luns * geo->num_chk;
	geo->total_secs = geo->clba * geo->all_chunks;

	geo->ws_min = le32_to_cpu(id->ws_min);
	geo->ws_opt = le32_to_cpu(id->ws_opt);
	geo->mw_cunits = le32_to_cpu(id->mw_cunits);
	geo->maxoc = le32_to_cpu(id->maxoc);
	geo->maxocpu = le32_to_cpu(id->maxocpu);

	geo->trdt = le32_to_cpu(id->trdt);
	geo->trdm = le32_to_cpu(id->trdm);
	geo->tprt = le32_to_cpu(id->twrt);
	geo->tprm = le32_to_cpu(id->twrm);
	geo->tbet = le32_to_cpu(id->tcrst);
	geo->tbem = le32_to_cpu(id->tcrsm);

	nvme_nvm_set_addr_20(&geo->addrf, &id->lbaf);

	वापस 0;
पूर्ण

अटल पूर्णांक nvme_nvm_identity(काष्ठा nvm_dev *nvmdev)
अणु
	काष्ठा nvme_ns *ns = nvmdev->q->queuedata;
	काष्ठा nvme_nvm_id12 *id;
	काष्ठा nvme_nvm_command c = अणुपूर्ण;
	पूर्णांक ret;

	c.identity.opcode = nvme_nvm_admin_identity;
	c.identity.nsid = cpu_to_le32(ns->head->ns_id);

	id = kदो_स्मृति(माप(काष्ठा nvme_nvm_id12), GFP_KERNEL);
	अगर (!id)
		वापस -ENOMEM;

	ret = nvme_submit_sync_cmd(ns->ctrl->admin_q, (काष्ठा nvme_command *)&c,
				id, माप(काष्ठा nvme_nvm_id12));
	अगर (ret) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * The 1.2 and 2.0 specअगरications share the first byte in their geometry
	 * command to make it possible to know what version a device implements.
	 */
	चयन (id->ver_id) अणु
	हाल 1:
		ret = nvme_nvm_setup_12(id, &nvmdev->geo);
		अवरोध;
	हाल 2:
		ret = nvme_nvm_setup_20((काष्ठा nvme_nvm_id20 *)id,
							&nvmdev->geo);
		अवरोध;
	शेष:
		dev_err(ns->ctrl->device, "OCSSD revision not supported (%d)\n",
							id->ver_id);
		ret = -EINVAL;
	पूर्ण

out:
	kमुक्त(id);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_nvm_get_bb_tbl(काष्ठा nvm_dev *nvmdev, काष्ठा ppa_addr ppa,
								u8 *blks)
अणु
	काष्ठा request_queue *q = nvmdev->q;
	काष्ठा nvm_geo *geo = &nvmdev->geo;
	काष्ठा nvme_ns *ns = q->queuedata;
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	काष्ठा nvme_nvm_command c = अणुपूर्ण;
	काष्ठा nvme_nvm_bb_tbl *bb_tbl;
	पूर्णांक nr_blks = geo->num_chk * geo->num_pln;
	पूर्णांक tblsz = माप(काष्ठा nvme_nvm_bb_tbl) + nr_blks;
	पूर्णांक ret = 0;

	c.get_bb.opcode = nvme_nvm_admin_get_bb_tbl;
	c.get_bb.nsid = cpu_to_le32(ns->head->ns_id);
	c.get_bb.spba = cpu_to_le64(ppa.ppa);

	bb_tbl = kzalloc(tblsz, GFP_KERNEL);
	अगर (!bb_tbl)
		वापस -ENOMEM;

	ret = nvme_submit_sync_cmd(ctrl->admin_q, (काष्ठा nvme_command *)&c,
								bb_tbl, tblsz);
	अगर (ret) अणु
		dev_err(ctrl->device, "get bad block table failed (%d)\n", ret);
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (bb_tbl->tblid[0] != 'B' || bb_tbl->tblid[1] != 'B' ||
		bb_tbl->tblid[2] != 'L' || bb_tbl->tblid[3] != 'T') अणु
		dev_err(ctrl->device, "bbt format mismatch\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(bb_tbl->verid) != 1) अणु
		ret = -EINVAL;
		dev_err(ctrl->device, "bbt version not supported\n");
		जाओ out;
	पूर्ण

	अगर (le32_to_cpu(bb_tbl->tblks) != nr_blks) अणु
		ret = -EINVAL;
		dev_err(ctrl->device,
				"bbt unsuspected blocks returned (%u!=%u)",
				le32_to_cpu(bb_tbl->tblks), nr_blks);
		जाओ out;
	पूर्ण

	स_नकल(blks, bb_tbl->blk, geo->num_chk * geo->num_pln);
out:
	kमुक्त(bb_tbl);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_nvm_set_bb_tbl(काष्ठा nvm_dev *nvmdev, काष्ठा ppa_addr *ppas,
							पूर्णांक nr_ppas, पूर्णांक type)
अणु
	काष्ठा nvme_ns *ns = nvmdev->q->queuedata;
	काष्ठा nvme_nvm_command c = अणुपूर्ण;
	पूर्णांक ret = 0;

	c.set_bb.opcode = nvme_nvm_admin_set_bb_tbl;
	c.set_bb.nsid = cpu_to_le32(ns->head->ns_id);
	c.set_bb.spba = cpu_to_le64(ppas->ppa);
	c.set_bb.nlb = cpu_to_le16(nr_ppas - 1);
	c.set_bb.value = type;

	ret = nvme_submit_sync_cmd(ns->ctrl->admin_q, (काष्ठा nvme_command *)&c,
								शून्य, 0);
	अगर (ret)
		dev_err(ns->ctrl->device, "set bad block table failed (%d)\n",
									ret);
	वापस ret;
पूर्ण

/*
 * Expect the lba in device क्रमmat
 */
अटल पूर्णांक nvme_nvm_get_chk_meta(काष्ठा nvm_dev *ndev,
				 sector_t slba, पूर्णांक nchks,
				 काष्ठा nvm_chk_meta *meta)
अणु
	काष्ठा nvm_geo *geo = &ndev->geo;
	काष्ठा nvme_ns *ns = ndev->q->queuedata;
	काष्ठा nvme_ctrl *ctrl = ns->ctrl;
	काष्ठा nvme_nvm_chk_meta *dev_meta, *dev_meta_off;
	काष्ठा ppa_addr ppa;
	माप_प्रकार left = nchks * माप(काष्ठा nvme_nvm_chk_meta);
	माप_प्रकार log_pos, offset, len;
	पूर्णांक i, max_len;
	पूर्णांक ret = 0;

	/*
	 * limit requests to maximum 256K to aव्योम issuing arbitrary large
	 * requests when the device करोes not specअगरic a maximum transfer size.
	 */
	max_len = min_t(अचिन्हित पूर्णांक, ctrl->max_hw_sectors << 9, 256 * 1024);

	dev_meta = kदो_स्मृति(max_len, GFP_KERNEL);
	अगर (!dev_meta)
		वापस -ENOMEM;

	/* Normalize lba address space to obtain log offset */
	ppa.ppa = slba;
	ppa = dev_to_generic_addr(ndev, ppa);

	log_pos = ppa.m.chk;
	log_pos += ppa.m.pu * geo->num_chk;
	log_pos += ppa.m.grp * geo->num_lun * geo->num_chk;

	offset = log_pos * माप(काष्ठा nvme_nvm_chk_meta);

	जबतक (left) अणु
		len = min_t(अचिन्हित पूर्णांक, left, max_len);

		स_रखो(dev_meta, 0, max_len);
		dev_meta_off = dev_meta;

		ret = nvme_get_log(ctrl, ns->head->ns_id,
				NVME_NVM_LOG_REPORT_CHUNK, 0, NVME_CSI_NVM,
				dev_meta, len, offset);
		अगर (ret) अणु
			dev_err(ctrl->device, "Get REPORT CHUNK log error\n");
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < len; i += माप(काष्ठा nvme_nvm_chk_meta)) अणु
			meta->state = dev_meta_off->state;
			meta->type = dev_meta_off->type;
			meta->wi = dev_meta_off->wi;
			meta->slba = le64_to_cpu(dev_meta_off->slba);
			meta->cnlb = le64_to_cpu(dev_meta_off->cnlb);
			meta->wp = le64_to_cpu(dev_meta_off->wp);

			meta++;
			dev_meta_off++;
		पूर्ण

		offset += len;
		left -= len;
	पूर्ण

	kमुक्त(dev_meta);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम nvme_nvm_rqtocmd(काष्ठा nvm_rq *rqd, काष्ठा nvme_ns *ns,
				    काष्ठा nvme_nvm_command *c)
अणु
	c->ph_rw.opcode = rqd->opcode;
	c->ph_rw.nsid = cpu_to_le32(ns->head->ns_id);
	c->ph_rw.spba = cpu_to_le64(rqd->ppa_addr.ppa);
	c->ph_rw.metadata = cpu_to_le64(rqd->dma_meta_list);
	c->ph_rw.control = cpu_to_le16(rqd->flags);
	c->ph_rw.length = cpu_to_le16(rqd->nr_ppas - 1);
पूर्ण

अटल व्योम nvme_nvm_end_io(काष्ठा request *rq, blk_status_t status)
अणु
	काष्ठा nvm_rq *rqd = rq->end_io_data;

	rqd->ppa_status = le64_to_cpu(nvme_req(rq)->result.u64);
	rqd->error = nvme_req(rq)->status;
	nvm_end_io(rqd);

	kमुक्त(nvme_req(rq)->cmd);
	blk_mq_मुक्त_request(rq);
पूर्ण

अटल काष्ठा request *nvme_nvm_alloc_request(काष्ठा request_queue *q,
					      काष्ठा nvm_rq *rqd,
					      काष्ठा nvme_nvm_command *cmd)
अणु
	काष्ठा nvme_ns *ns = q->queuedata;
	काष्ठा request *rq;

	nvme_nvm_rqtocmd(rqd, ns, cmd);

	rq = nvme_alloc_request(q, (काष्ठा nvme_command *)cmd, 0);
	अगर (IS_ERR(rq))
		वापस rq;

	rq->cmd_flags &= ~REQ_FAILFAST_DRIVER;

	अगर (rqd->bio)
		blk_rq_append_bio(rq, rqd->bio);
	अन्यथा
		rq->ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, IOPRIO_NORM);

	वापस rq;
पूर्ण

अटल पूर्णांक nvme_nvm_submit_io(काष्ठा nvm_dev *dev, काष्ठा nvm_rq *rqd,
			      व्योम *buf)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा request_queue *q = dev->q;
	काष्ठा nvme_nvm_command *cmd;
	काष्ठा request *rq;
	पूर्णांक ret;

	cmd = kzalloc(माप(काष्ठा nvme_nvm_command), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	rq = nvme_nvm_alloc_request(q, rqd, cmd);
	अगर (IS_ERR(rq)) अणु
		ret = PTR_ERR(rq);
		जाओ err_मुक्त_cmd;
	पूर्ण

	अगर (buf) अणु
		ret = blk_rq_map_kern(q, rq, buf, geo->csecs * rqd->nr_ppas,
				GFP_KERNEL);
		अगर (ret)
			जाओ err_मुक्त_cmd;
	पूर्ण

	rq->end_io_data = rqd;

	blk_execute_rq_noरुको(शून्य, rq, 0, nvme_nvm_end_io);

	वापस 0;

err_मुक्त_cmd:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

अटल व्योम *nvme_nvm_create_dma_pool(काष्ठा nvm_dev *nvmdev, अक्षर *name,
					पूर्णांक size)
अणु
	काष्ठा nvme_ns *ns = nvmdev->q->queuedata;

	वापस dma_pool_create(name, ns->ctrl->dev, size, PAGE_SIZE, 0);
पूर्ण

अटल व्योम nvme_nvm_destroy_dma_pool(व्योम *pool)
अणु
	काष्ठा dma_pool *dma_pool = pool;

	dma_pool_destroy(dma_pool);
पूर्ण

अटल व्योम *nvme_nvm_dev_dma_alloc(काष्ठा nvm_dev *dev, व्योम *pool,
				    gfp_t mem_flags, dma_addr_t *dma_handler)
अणु
	वापस dma_pool_alloc(pool, mem_flags, dma_handler);
पूर्ण

अटल व्योम nvme_nvm_dev_dma_मुक्त(व्योम *pool, व्योम *addr,
							dma_addr_t dma_handler)
अणु
	dma_pool_मुक्त(pool, addr, dma_handler);
पूर्ण

अटल काष्ठा nvm_dev_ops nvme_nvm_dev_ops = अणु
	.identity		= nvme_nvm_identity,

	.get_bb_tbl		= nvme_nvm_get_bb_tbl,
	.set_bb_tbl		= nvme_nvm_set_bb_tbl,

	.get_chk_meta		= nvme_nvm_get_chk_meta,

	.submit_io		= nvme_nvm_submit_io,

	.create_dma_pool	= nvme_nvm_create_dma_pool,
	.destroy_dma_pool	= nvme_nvm_destroy_dma_pool,
	.dev_dma_alloc		= nvme_nvm_dev_dma_alloc,
	.dev_dma_मुक्त		= nvme_nvm_dev_dma_मुक्त,
पूर्ण;

अटल पूर्णांक nvme_nvm_submit_user_cmd(काष्ठा request_queue *q,
				काष्ठा nvme_ns *ns,
				काष्ठा nvme_nvm_command *vcmd,
				व्योम __user *ubuf, अचिन्हित पूर्णांक bufflen,
				व्योम __user *meta_buf, अचिन्हित पूर्णांक meta_len,
				व्योम __user *ppa_buf, अचिन्हित पूर्णांक ppa_len,
				u32 *result, u64 *status, अचिन्हित पूर्णांक समयout)
अणु
	bool ग_लिखो = nvme_is_ग_लिखो((काष्ठा nvme_command *)vcmd);
	काष्ठा nvm_dev *dev = ns->ndev;
	काष्ठा request *rq;
	काष्ठा bio *bio = शून्य;
	__le64 *ppa_list = शून्य;
	dma_addr_t ppa_dma;
	__le64 *metadata = शून्य;
	dma_addr_t metadata_dma;
	DECLARE_COMPLETION_ONSTACK(रुको);
	पूर्णांक ret = 0;

	rq = nvme_alloc_request(q, (काष्ठा nvme_command *)vcmd, 0);
	अगर (IS_ERR(rq)) अणु
		ret = -ENOMEM;
		जाओ err_cmd;
	पूर्ण

	अगर (समयout)
		rq->समयout = समयout;

	अगर (ppa_buf && ppa_len) अणु
		ppa_list = dma_pool_alloc(dev->dma_pool, GFP_KERNEL, &ppa_dma);
		अगर (!ppa_list) अणु
			ret = -ENOMEM;
			जाओ err_rq;
		पूर्ण
		अगर (copy_from_user(ppa_list, (व्योम __user *)ppa_buf,
						माप(u64) * (ppa_len + 1))) अणु
			ret = -EFAULT;
			जाओ err_ppa;
		पूर्ण
		vcmd->ph_rw.spba = cpu_to_le64(ppa_dma);
	पूर्ण अन्यथा अणु
		vcmd->ph_rw.spba = cpu_to_le64((uपूर्णांकptr_t)ppa_buf);
	पूर्ण

	अगर (ubuf && bufflen) अणु
		ret = blk_rq_map_user(q, rq, शून्य, ubuf, bufflen, GFP_KERNEL);
		अगर (ret)
			जाओ err_ppa;
		bio = rq->bio;

		अगर (meta_buf && meta_len) अणु
			metadata = dma_pool_alloc(dev->dma_pool, GFP_KERNEL,
								&metadata_dma);
			अगर (!metadata) अणु
				ret = -ENOMEM;
				जाओ err_map;
			पूर्ण

			अगर (ग_लिखो) अणु
				अगर (copy_from_user(metadata,
						(व्योम __user *)meta_buf,
						meta_len)) अणु
					ret = -EFAULT;
					जाओ err_meta;
				पूर्ण
			पूर्ण
			vcmd->ph_rw.metadata = cpu_to_le64(metadata_dma);
		पूर्ण

		bio_set_dev(bio, ns->disk->part0);
	पूर्ण

	blk_execute_rq(शून्य, rq, 0);

	अगर (nvme_req(rq)->flags & NVME_REQ_CANCELLED)
		ret = -EINTR;
	अन्यथा अगर (nvme_req(rq)->status & 0x7ff)
		ret = -EIO;
	अगर (result)
		*result = nvme_req(rq)->status & 0x7ff;
	अगर (status)
		*status = le64_to_cpu(nvme_req(rq)->result.u64);

	अगर (metadata && !ret && !ग_लिखो) अणु
		अगर (copy_to_user(meta_buf, (व्योम *)metadata, meta_len))
			ret = -EFAULT;
	पूर्ण
err_meta:
	अगर (meta_buf && meta_len)
		dma_pool_मुक्त(dev->dma_pool, metadata, metadata_dma);
err_map:
	अगर (bio)
		blk_rq_unmap_user(bio);
err_ppa:
	अगर (ppa_buf && ppa_len)
		dma_pool_मुक्त(dev->dma_pool, ppa_list, ppa_dma);
err_rq:
	blk_mq_मुक्त_request(rq);
err_cmd:
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_nvm_submit_vio(काष्ठा nvme_ns *ns,
					काष्ठा nvm_user_vio __user *uvio)
अणु
	काष्ठा nvm_user_vio vio;
	काष्ठा nvme_nvm_command c;
	अचिन्हित पूर्णांक length;
	पूर्णांक ret;

	अगर (copy_from_user(&vio, uvio, माप(vio)))
		वापस -EFAULT;
	अगर (vio.flags)
		वापस -EINVAL;

	स_रखो(&c, 0, माप(c));
	c.ph_rw.opcode = vio.opcode;
	c.ph_rw.nsid = cpu_to_le32(ns->head->ns_id);
	c.ph_rw.control = cpu_to_le16(vio.control);
	c.ph_rw.length = cpu_to_le16(vio.nppas);

	length = (vio.nppas + 1) << ns->lba_shअगरt;

	ret = nvme_nvm_submit_user_cmd(ns->queue, ns, &c,
			(व्योम __user *)(uपूर्णांकptr_t)vio.addr, length,
			(व्योम __user *)(uपूर्णांकptr_t)vio.metadata,
							vio.metadata_len,
			(व्योम __user *)(uपूर्णांकptr_t)vio.ppa_list, vio.nppas,
			&vio.result, &vio.status, 0);

	अगर (ret && copy_to_user(uvio, &vio, माप(vio)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक nvme_nvm_user_vcmd(काष्ठा nvme_ns *ns, पूर्णांक admin,
					काष्ठा nvm_passthru_vio __user *uvcmd)
अणु
	काष्ठा nvm_passthru_vio vcmd;
	काष्ठा nvme_nvm_command c;
	काष्ठा request_queue *q;
	अचिन्हित पूर्णांक समयout = 0;
	पूर्णांक ret;

	अगर (copy_from_user(&vcmd, uvcmd, माप(vcmd)))
		वापस -EFAULT;
	अगर ((vcmd.opcode != 0xF2) && (!capable(CAP_SYS_ADMIN)))
		वापस -EACCES;
	अगर (vcmd.flags)
		वापस -EINVAL;

	स_रखो(&c, 0, माप(c));
	c.common.opcode = vcmd.opcode;
	c.common.nsid = cpu_to_le32(ns->head->ns_id);
	c.common.cdw2[0] = cpu_to_le32(vcmd.cdw2);
	c.common.cdw2[1] = cpu_to_le32(vcmd.cdw3);
	/* cdw11-12 */
	c.ph_rw.length = cpu_to_le16(vcmd.nppas);
	c.ph_rw.control  = cpu_to_le16(vcmd.control);
	c.common.cdw13 = cpu_to_le32(vcmd.cdw13);
	c.common.cdw14 = cpu_to_le32(vcmd.cdw14);
	c.common.cdw15 = cpu_to_le32(vcmd.cdw15);

	अगर (vcmd.समयout_ms)
		समयout = msecs_to_jअगरfies(vcmd.समयout_ms);

	q = admin ? ns->ctrl->admin_q : ns->queue;

	ret = nvme_nvm_submit_user_cmd(q, ns,
			(काष्ठा nvme_nvm_command *)&c,
			(व्योम __user *)(uपूर्णांकptr_t)vcmd.addr, vcmd.data_len,
			(व्योम __user *)(uपूर्णांकptr_t)vcmd.metadata,
							vcmd.metadata_len,
			(व्योम __user *)(uपूर्णांकptr_t)vcmd.ppa_list, vcmd.nppas,
			&vcmd.result, &vcmd.status, समयout);

	अगर (ret && copy_to_user(uvcmd, &vcmd, माप(vcmd)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

पूर्णांक nvme_nvm_ioctl(काष्ठा nvme_ns *ns, अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	चयन (cmd) अणु
	हाल NVME_NVM_IOCTL_ADMIN_VIO:
		वापस nvme_nvm_user_vcmd(ns, 1, argp);
	हाल NVME_NVM_IOCTL_IO_VIO:
		वापस nvme_nvm_user_vcmd(ns, 0, argp);
	हाल NVME_NVM_IOCTL_SUBMIT_VIO:
		वापस nvme_nvm_submit_vio(ns, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

पूर्णांक nvme_nvm_रेजिस्टर(काष्ठा nvme_ns *ns, अक्षर *disk_name, पूर्णांक node)
अणु
	काष्ठा request_queue *q = ns->queue;
	काष्ठा nvm_dev *dev;
	काष्ठा nvm_geo *geo;

	_nvme_nvm_check_size();

	dev = nvm_alloc_dev(node);
	अगर (!dev)
		वापस -ENOMEM;

	/* Note that csecs and sos will be overridden अगर it is a 1.2 drive. */
	geo = &dev->geo;
	geo->csecs = 1 << ns->lba_shअगरt;
	geo->sos = ns->ms;
	अगर (ns->features & NVME_NS_EXT_LBAS)
		geo->ext = true;
	अन्यथा
		geo->ext = false;
	geo->mdts = ns->ctrl->max_hw_sectors;

	dev->q = q;
	स_नकल(dev->name, disk_name, DISK_NAME_LEN);
	dev->ops = &nvme_nvm_dev_ops;
	dev->निजी_data = ns;
	ns->ndev = dev;

	वापस nvm_रेजिस्टर(dev);
पूर्ण

व्योम nvme_nvm_unरेजिस्टर(काष्ठा nvme_ns *ns)
अणु
	nvm_unरेजिस्टर(ns->ndev);
पूर्ण

अटल sमाप_प्रकार nvm_dev_attr_show(काष्ठा device *dev,
		काष्ठा device_attribute *dattr, अक्षर *page)
अणु
	काष्ठा nvme_ns *ns = nvme_get_ns_from_dev(dev);
	काष्ठा nvm_dev *ndev = ns->ndev;
	काष्ठा nvm_geo *geo = &ndev->geo;
	काष्ठा attribute *attr;

	अगर (!ndev)
		वापस 0;

	attr = &dattr->attr;

	अगर (म_भेद(attr->name, "version") == 0) अणु
		अगर (geo->major_ver_id == 1)
			वापस scnम_लिखो(page, PAGE_SIZE, "%u\n",
						geo->major_ver_id);
		अन्यथा
			वापस scnम_लिखो(page, PAGE_SIZE, "%u.%u\n",
						geo->major_ver_id,
						geo->minor_ver_id);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "capabilities") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->cap);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "read_typ") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->trdt);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "read_max") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->trdm);
	पूर्ण अन्यथा अणु
		वापस scnम_लिखो(page,
				 PAGE_SIZE,
				 "Unhandled attr(%s) in `%s`\n",
				 attr->name, __func__);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार nvm_dev_attr_show_ppaf(काष्ठा nvm_addrf_12 *ppaf, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE,
		"0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
				ppaf->ch_offset, ppaf->ch_len,
				ppaf->lun_offset, ppaf->lun_len,
				ppaf->pln_offset, ppaf->pln_len,
				ppaf->blk_offset, ppaf->blk_len,
				ppaf->pg_offset, ppaf->pg_len,
				ppaf->sec_offset, ppaf->sec_len);
पूर्ण

अटल sमाप_प्रकार nvm_dev_attr_show_12(काष्ठा device *dev,
		काष्ठा device_attribute *dattr, अक्षर *page)
अणु
	काष्ठा nvme_ns *ns = nvme_get_ns_from_dev(dev);
	काष्ठा nvm_dev *ndev = ns->ndev;
	काष्ठा nvm_geo *geo = &ndev->geo;
	काष्ठा attribute *attr;

	अगर (!ndev)
		वापस 0;

	attr = &dattr->attr;

	अगर (म_भेद(attr->name, "vendor_opcode") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->vmnt);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "device_mode") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->करोm);
	/* kept क्रम compatibility */
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "media_manager") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%s\n", "gennvm");
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "ppa_format") == 0) अणु
		वापस nvm_dev_attr_show_ppaf((व्योम *)&geo->addrf, page);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "media_type") == 0) अणु	/* u8 */
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->mtype);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "flash_media_type") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->fmtype);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "num_channels") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_ch);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "num_luns") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_lun);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "num_planes") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_pln);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "num_blocks") == 0) अणु	/* u16 */
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_chk);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "num_pages") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_pg);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "page_size") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->fpg_sz);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "hw_sector_size") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->csecs);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "oob_sector_size") == 0) अणु/* u32 */
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->sos);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "prog_typ") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tprt);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "prog_max") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tprm);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "erase_typ") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tbet);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "erase_max") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tbem);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "multiplane_modes") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "0x%08x\n", geo->mpos);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "media_capabilities") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "0x%08x\n", geo->mccap);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "max_phys_secs") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", NVM_MAX_VLBA);
	पूर्ण अन्यथा अणु
		वापस scnम_लिखो(page, PAGE_SIZE,
			"Unhandled attr(%s) in `%s`\n",
			attr->name, __func__);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार nvm_dev_attr_show_20(काष्ठा device *dev,
		काष्ठा device_attribute *dattr, अक्षर *page)
अणु
	काष्ठा nvme_ns *ns = nvme_get_ns_from_dev(dev);
	काष्ठा nvm_dev *ndev = ns->ndev;
	काष्ठा nvm_geo *geo = &ndev->geo;
	काष्ठा attribute *attr;

	अगर (!ndev)
		वापस 0;

	attr = &dattr->attr;

	अगर (म_भेद(attr->name, "groups") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_ch);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "punits") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_lun);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "chunks") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->num_chk);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "clba") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->clba);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "ws_min") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->ws_min);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "ws_opt") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->ws_opt);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "maxoc") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->maxoc);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "maxocpu") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->maxocpu);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "mw_cunits") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->mw_cunits);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "write_typ") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tprt);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "write_max") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tprm);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "reset_typ") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tbet);
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "reset_max") == 0) अणु
		वापस scnम_लिखो(page, PAGE_SIZE, "%u\n", geo->tbem);
	पूर्ण अन्यथा अणु
		वापस scnम_लिखो(page, PAGE_SIZE,
			"Unhandled attr(%s) in `%s`\n",
			attr->name, __func__);
	पूर्ण
पूर्ण

#घोषणा NVM_DEV_ATTR_RO(_name)					\
	DEVICE_ATTR(_name, S_IRUGO, nvm_dev_attr_show, शून्य)
#घोषणा NVM_DEV_ATTR_12_RO(_name)					\
	DEVICE_ATTR(_name, S_IRUGO, nvm_dev_attr_show_12, शून्य)
#घोषणा NVM_DEV_ATTR_20_RO(_name)					\
	DEVICE_ATTR(_name, S_IRUGO, nvm_dev_attr_show_20, शून्य)

/* general attributes */
अटल NVM_DEV_ATTR_RO(version);
अटल NVM_DEV_ATTR_RO(capabilities);

अटल NVM_DEV_ATTR_RO(पढ़ो_typ);
अटल NVM_DEV_ATTR_RO(पढ़ो_max);

/* 1.2 values */
अटल NVM_DEV_ATTR_12_RO(venकरोr_opcode);
अटल NVM_DEV_ATTR_12_RO(device_mode);
अटल NVM_DEV_ATTR_12_RO(ppa_क्रमmat);
अटल NVM_DEV_ATTR_12_RO(media_manager);
अटल NVM_DEV_ATTR_12_RO(media_type);
अटल NVM_DEV_ATTR_12_RO(flash_media_type);
अटल NVM_DEV_ATTR_12_RO(num_channels);
अटल NVM_DEV_ATTR_12_RO(num_luns);
अटल NVM_DEV_ATTR_12_RO(num_planes);
अटल NVM_DEV_ATTR_12_RO(num_blocks);
अटल NVM_DEV_ATTR_12_RO(num_pages);
अटल NVM_DEV_ATTR_12_RO(page_size);
अटल NVM_DEV_ATTR_12_RO(hw_sector_size);
अटल NVM_DEV_ATTR_12_RO(oob_sector_size);
अटल NVM_DEV_ATTR_12_RO(prog_typ);
अटल NVM_DEV_ATTR_12_RO(prog_max);
अटल NVM_DEV_ATTR_12_RO(erase_typ);
अटल NVM_DEV_ATTR_12_RO(erase_max);
अटल NVM_DEV_ATTR_12_RO(multiplane_modes);
अटल NVM_DEV_ATTR_12_RO(media_capabilities);
अटल NVM_DEV_ATTR_12_RO(max_phys_secs);

/* 2.0 values */
अटल NVM_DEV_ATTR_20_RO(groups);
अटल NVM_DEV_ATTR_20_RO(punits);
अटल NVM_DEV_ATTR_20_RO(chunks);
अटल NVM_DEV_ATTR_20_RO(clba);
अटल NVM_DEV_ATTR_20_RO(ws_min);
अटल NVM_DEV_ATTR_20_RO(ws_opt);
अटल NVM_DEV_ATTR_20_RO(maxoc);
अटल NVM_DEV_ATTR_20_RO(maxocpu);
अटल NVM_DEV_ATTR_20_RO(mw_cunits);
अटल NVM_DEV_ATTR_20_RO(ग_लिखो_typ);
अटल NVM_DEV_ATTR_20_RO(ग_लिखो_max);
अटल NVM_DEV_ATTR_20_RO(reset_typ);
अटल NVM_DEV_ATTR_20_RO(reset_max);

अटल काष्ठा attribute *nvm_dev_attrs[] = अणु
	/* version agnostic attrs */
	&dev_attr_version.attr,
	&dev_attr_capabilities.attr,
	&dev_attr_पढ़ो_typ.attr,
	&dev_attr_पढ़ो_max.attr,

	/* 1.2 attrs */
	&dev_attr_venकरोr_opcode.attr,
	&dev_attr_device_mode.attr,
	&dev_attr_media_manager.attr,
	&dev_attr_ppa_क्रमmat.attr,
	&dev_attr_media_type.attr,
	&dev_attr_flash_media_type.attr,
	&dev_attr_num_channels.attr,
	&dev_attr_num_luns.attr,
	&dev_attr_num_planes.attr,
	&dev_attr_num_blocks.attr,
	&dev_attr_num_pages.attr,
	&dev_attr_page_size.attr,
	&dev_attr_hw_sector_size.attr,
	&dev_attr_oob_sector_size.attr,
	&dev_attr_prog_typ.attr,
	&dev_attr_prog_max.attr,
	&dev_attr_erase_typ.attr,
	&dev_attr_erase_max.attr,
	&dev_attr_multiplane_modes.attr,
	&dev_attr_media_capabilities.attr,
	&dev_attr_max_phys_secs.attr,

	/* 2.0 attrs */
	&dev_attr_groups.attr,
	&dev_attr_punits.attr,
	&dev_attr_chunks.attr,
	&dev_attr_clba.attr,
	&dev_attr_ws_min.attr,
	&dev_attr_ws_opt.attr,
	&dev_attr_maxoc.attr,
	&dev_attr_maxocpu.attr,
	&dev_attr_mw_cunits.attr,

	&dev_attr_ग_लिखो_typ.attr,
	&dev_attr_ग_लिखो_max.attr,
	&dev_attr_reset_typ.attr,
	&dev_attr_reset_max.attr,

	शून्य,
पूर्ण;

अटल umode_t nvm_dev_attrs_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा nvme_ns *ns = disk->निजी_data;
	काष्ठा nvm_dev *ndev = ns->ndev;
	काष्ठा device_attribute *dev_attr =
		container_of(attr, typeof(*dev_attr), attr);

	अगर (!ndev)
		वापस 0;

	अगर (dev_attr->show == nvm_dev_attr_show)
		वापस attr->mode;

	चयन (ndev->geo.major_ver_id) अणु
	हाल 1:
		अगर (dev_attr->show == nvm_dev_attr_show_12)
			वापस attr->mode;
		अवरोध;
	हाल 2:
		अगर (dev_attr->show == nvm_dev_attr_show_20)
			वापस attr->mode;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा attribute_group nvme_nvm_attr_group = अणु
	.name		= "lightnvm",
	.attrs		= nvm_dev_attrs,
	.is_visible	= nvm_dev_attrs_visible,
पूर्ण;
