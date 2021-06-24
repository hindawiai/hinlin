<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "nvme.h"

पूर्णांक nvme_revalidate_zones(काष्ठा nvme_ns *ns)
अणु
	काष्ठा request_queue *q = ns->queue;
	पूर्णांक ret;

	ret = blk_revalidate_disk_zones(ns->disk, शून्य);
	अगर (!ret)
		blk_queue_max_zone_append_sectors(q, ns->ctrl->max_zone_append);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_set_max_append(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_command c = अणु पूर्ण;
	काष्ठा nvme_id_ctrl_zns *id;
	पूर्णांक status;

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस -ENOMEM;

	c.identअगरy.opcode = nvme_admin_identअगरy;
	c.identअगरy.cns = NVME_ID_CNS_CS_CTRL;
	c.identअगरy.csi = NVME_CSI_ZNS;

	status = nvme_submit_sync_cmd(ctrl->admin_q, &c, id, माप(*id));
	अगर (status) अणु
		kमुक्त(id);
		वापस status;
	पूर्ण

	अगर (id->zasl)
		ctrl->max_zone_append = 1 << (id->zasl + 3);
	अन्यथा
		ctrl->max_zone_append = ctrl->max_hw_sectors;
	kमुक्त(id);
	वापस 0;
पूर्ण

पूर्णांक nvme_update_zone_info(काष्ठा nvme_ns *ns, अचिन्हित lbaf)
अणु
	काष्ठा nvme_effects_log *log = ns->head->effects;
	काष्ठा request_queue *q = ns->queue;
	काष्ठा nvme_command c = अणु पूर्ण;
	काष्ठा nvme_id_ns_zns *id;
	पूर्णांक status;

	/* Driver requires zone append support */
	अगर ((le32_to_cpu(log->iocs[nvme_cmd_zone_append]) &
			NVME_CMD_EFFECTS_CSUPP)) अणु
		अगर (test_and_clear_bit(NVME_NS_FORCE_RO, &ns->flags))
			dev_warn(ns->ctrl->device,
				 "Zone Append supported for zoned namespace:%d. Remove read-only mode\n",
				 ns->head->ns_id);
	पूर्ण अन्यथा अणु
		set_bit(NVME_NS_FORCE_RO, &ns->flags);
		dev_warn(ns->ctrl->device,
			 "Zone Append not supported for zoned namespace:%d. Forcing to read-only mode\n",
			 ns->head->ns_id);
	पूर्ण

	/* Lazily query controller append limit क्रम the first zoned namespace */
	अगर (!ns->ctrl->max_zone_append) अणु
		status = nvme_set_max_append(ns->ctrl);
		अगर (status)
			वापस status;
	पूर्ण

	id = kzalloc(माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस -ENOMEM;

	c.identअगरy.opcode = nvme_admin_identअगरy;
	c.identअगरy.nsid = cpu_to_le32(ns->head->ns_id);
	c.identअगरy.cns = NVME_ID_CNS_CS_NS;
	c.identअगरy.csi = NVME_CSI_ZNS;

	status = nvme_submit_sync_cmd(ns->ctrl->admin_q, &c, id, माप(*id));
	अगर (status)
		जाओ मुक्त_data;

	/*
	 * We currently करो not handle devices requiring any of the zoned
	 * operation अक्षरacteristics.
	 */
	अगर (id->zoc) अणु
		dev_warn(ns->ctrl->device,
			"zone operations:%x not supported for namespace:%u\n",
			le16_to_cpu(id->zoc), ns->head->ns_id);
		status = -ENODEV;
		जाओ मुक्त_data;
	पूर्ण

	ns->zsze = nvme_lba_to_sect(ns, le64_to_cpu(id->lbafe[lbaf].zsze));
	अगर (!is_घातer_of_2(ns->zsze)) अणु
		dev_warn(ns->ctrl->device,
			"invalid zone size:%llu for namespace:%u\n",
			ns->zsze, ns->head->ns_id);
		status = -ENODEV;
		जाओ मुक्त_data;
	पूर्ण

	blk_queue_set_zoned(ns->disk, BLK_ZONED_HM);
	blk_queue_flag_set(QUEUE_FLAG_ZONE_RESETALL, q);
	blk_queue_max_खोलो_zones(q, le32_to_cpu(id->mor) + 1);
	blk_queue_max_active_zones(q, le32_to_cpu(id->mar) + 1);
मुक्त_data:
	kमुक्त(id);
	वापस status;
पूर्ण

अटल व्योम *nvme_zns_alloc_report_buffer(काष्ठा nvme_ns *ns,
					  अचिन्हित पूर्णांक nr_zones, माप_प्रकार *buflen)
अणु
	काष्ठा request_queue *q = ns->disk->queue;
	माप_प्रकार bufsize;
	व्योम *buf;

	स्थिर माप_प्रकार min_bufsize = माप(काष्ठा nvme_zone_report) +
				   माप(काष्ठा nvme_zone_descriptor);

	nr_zones = min_t(अचिन्हित पूर्णांक, nr_zones,
			 get_capacity(ns->disk) >> ilog2(ns->zsze));

	bufsize = माप(काष्ठा nvme_zone_report) +
		nr_zones * माप(काष्ठा nvme_zone_descriptor);
	bufsize = min_t(माप_प्रकार, bufsize,
			queue_max_hw_sectors(q) << SECTOR_SHIFT);
	bufsize = min_t(माप_प्रकार, bufsize, queue_max_segments(q) << PAGE_SHIFT);

	जबतक (bufsize >= min_bufsize) अणु
		buf = __vदो_स्मृति(bufsize, GFP_KERNEL | __GFP_NORETRY);
		अगर (buf) अणु
			*buflen = bufsize;
			वापस buf;
		पूर्ण
		bufsize >>= 1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक nvme_zone_parse_entry(काष्ठा nvme_ns *ns,
				 काष्ठा nvme_zone_descriptor *entry,
				 अचिन्हित पूर्णांक idx, report_zones_cb cb,
				 व्योम *data)
अणु
	काष्ठा blk_zone zone = अणु पूर्ण;

	अगर ((entry->zt & 0xf) != NVME_ZONE_TYPE_SEQWRITE_REQ) अणु
		dev_err(ns->ctrl->device, "invalid zone type %#x\n",
				entry->zt);
		वापस -EINVAL;
	पूर्ण

	zone.type = BLK_ZONE_TYPE_SEQWRITE_REQ;
	zone.cond = entry->zs >> 4;
	zone.len = ns->zsze;
	zone.capacity = nvme_lba_to_sect(ns, le64_to_cpu(entry->zcap));
	zone.start = nvme_lba_to_sect(ns, le64_to_cpu(entry->zslba));
	zone.wp = nvme_lba_to_sect(ns, le64_to_cpu(entry->wp));

	वापस cb(&zone, idx, data);
पूर्ण

अटल पूर्णांक nvme_ns_report_zones(काष्ठा nvme_ns *ns, sector_t sector,
			अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा nvme_zone_report *report;
	काष्ठा nvme_command c = अणु पूर्ण;
	पूर्णांक ret, zone_idx = 0;
	अचिन्हित पूर्णांक nz, i;
	माप_प्रकार buflen;

	report = nvme_zns_alloc_report_buffer(ns, nr_zones, &buflen);
	अगर (!report)
		वापस -ENOMEM;

	c.zmr.opcode = nvme_cmd_zone_mgmt_recv;
	c.zmr.nsid = cpu_to_le32(ns->head->ns_id);
	c.zmr.numd = cpu_to_le32(nvme_bytes_to_numd(buflen));
	c.zmr.zra = NVME_ZRA_ZONE_REPORT;
	c.zmr.zrasf = NVME_ZRASF_ZONE_REPORT_ALL;
	c.zmr.pr = NVME_REPORT_ZONE_PARTIAL;

	sector &= ~(ns->zsze - 1);
	जबतक (zone_idx < nr_zones && sector < get_capacity(ns->disk)) अणु
		स_रखो(report, 0, buflen);

		c.zmr.slba = cpu_to_le64(nvme_sect_to_lba(ns, sector));
		ret = nvme_submit_sync_cmd(ns->queue, &c, report, buflen);
		अगर (ret) अणु
			अगर (ret > 0)
				ret = -EIO;
			जाओ out_मुक्त;
		पूर्ण

		nz = min((अचिन्हित पूर्णांक)le64_to_cpu(report->nr_zones), nr_zones);
		अगर (!nz)
			अवरोध;

		क्रम (i = 0; i < nz && zone_idx < nr_zones; i++) अणु
			ret = nvme_zone_parse_entry(ns, &report->entries[i],
						    zone_idx, cb, data);
			अगर (ret)
				जाओ out_मुक्त;
			zone_idx++;
		पूर्ण

		sector += ns->zsze * nz;
	पूर्ण

	अगर (zone_idx > 0)
		ret = zone_idx;
	अन्यथा
		ret = -EINVAL;
out_मुक्त:
	kvमुक्त(report);
	वापस ret;
पूर्ण

पूर्णांक nvme_report_zones(काष्ठा gendisk *disk, sector_t sector,
		      अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा nvme_ns_head *head = शून्य;
	काष्ठा nvme_ns *ns;
	पूर्णांक srcu_idx, ret;

	ns = nvme_get_ns_from_disk(disk, &head, &srcu_idx);
	अगर (unlikely(!ns))
		वापस -EWOULDBLOCK;

	अगर (ns->head->ids.csi == NVME_CSI_ZNS)
		ret = nvme_ns_report_zones(ns, sector, nr_zones, cb, data);
	अन्यथा
		ret = -EINVAL;
	nvme_put_ns_from_disk(head, srcu_idx);

	वापस ret;
पूर्ण

blk_status_t nvme_setup_zone_mgmt_send(काष्ठा nvme_ns *ns, काष्ठा request *req,
		काष्ठा nvme_command *c, क्रमागत nvme_zone_mgmt_action action)
अणु
	c->zms.opcode = nvme_cmd_zone_mgmt_send;
	c->zms.nsid = cpu_to_le32(ns->head->ns_id);
	c->zms.slba = cpu_to_le64(nvme_sect_to_lba(ns, blk_rq_pos(req)));
	c->zms.zsa = action;

	अगर (req_op(req) == REQ_OP_ZONE_RESET_ALL)
		c->zms.select_all = 1;

	वापस BLK_STS_OK;
पूर्ण
