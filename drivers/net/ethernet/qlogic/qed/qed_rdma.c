<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_int.h"
#समावेश "qed_ll2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश <linux/qed/qed_rdma_अगर.h>
#समावेश "qed_rdma.h"
#समावेश "qed_roce.h"
#समावेश "qed_sp.h"


पूर्णांक qed_rdma_bmap_alloc(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_bmap *bmap, u32 max_count, अक्षर *name)
अणु
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "max_count = %08x\n", max_count);

	bmap->max_count = max_count;

	bmap->biपंचांगap = kसुस्मृति(BITS_TO_LONGS(max_count), माप(दीर्घ),
			       GFP_KERNEL);
	अगर (!bmap->biपंचांगap)
		वापस -ENOMEM;

	snम_लिखो(bmap->name, QED_RDMA_MAX_BMAP_NAME, "%s", name);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "0\n");
	वापस 0;
पूर्ण

पूर्णांक qed_rdma_bmap_alloc_id(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_bmap *bmap, u32 *id_num)
अणु
	*id_num = find_first_zero_bit(bmap->biपंचांगap, bmap->max_count);
	अगर (*id_num >= bmap->max_count)
		वापस -EINVAL;

	__set_bit(*id_num, bmap->biपंचांगap);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "%s bitmap: allocated id %d\n",
		   bmap->name, *id_num);

	वापस 0;
पूर्ण

व्योम qed_bmap_set_id(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_bmap *bmap, u32 id_num)
अणु
	अगर (id_num >= bmap->max_count)
		वापस;

	__set_bit(id_num, bmap->biपंचांगap);
पूर्ण

व्योम qed_bmap_release_id(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_bmap *bmap, u32 id_num)
अणु
	bool b_acquired;

	अगर (id_num >= bmap->max_count)
		वापस;

	b_acquired = test_and_clear_bit(id_num, bmap->biपंचांगap);
	अगर (!b_acquired) अणु
		DP_NOTICE(p_hwfn, "%s bitmap: id %d already released\n",
			  bmap->name, id_num);
		वापस;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "%s bitmap: released id %d\n",
		   bmap->name, id_num);
पूर्ण

पूर्णांक qed_bmap_test_id(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_bmap *bmap, u32 id_num)
अणु
	अगर (id_num >= bmap->max_count)
		वापस -1;

	वापस test_bit(id_num, bmap->biपंचांगap);
पूर्ण

अटल bool qed_bmap_is_empty(काष्ठा qed_bmap *bmap)
अणु
	वापस bmap->max_count == find_first_bit(bmap->biपंचांगap, bmap->max_count);
पूर्ण

अटल u32 qed_rdma_get_sb_id(व्योम *p_hwfn, u32 rel_sb_id)
अणु
	/* First sb id क्रम RoCE is after all the l2 sb */
	वापस FEAT_NUM((काष्ठा qed_hwfn *)p_hwfn, QED_PF_L2_QUE) + rel_sb_id;
पूर्ण

पूर्णांक qed_rdma_info_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rdma_info *p_rdma_info;

	p_rdma_info = kzalloc(माप(*p_rdma_info), GFP_KERNEL);
	अगर (!p_rdma_info)
		वापस -ENOMEM;

	spin_lock_init(&p_rdma_info->lock);

	p_hwfn->p_rdma_info = p_rdma_info;
	वापस 0;
पूर्ण

व्योम qed_rdma_info_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	kमुक्त(p_hwfn->p_rdma_info);
	p_hwfn->p_rdma_info = शून्य;
पूर्ण

अटल पूर्णांक qed_rdma_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 num_cons, num_tasks;
	पूर्णांक rc = -ENOMEM;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Allocating RDMA\n");

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		p_rdma_info->proto = PROTOCOLID_IWARP;
	अन्यथा
		p_rdma_info->proto = PROTOCOLID_ROCE;

	num_cons = qed_cxt_get_proto_cid_count(p_hwfn, p_rdma_info->proto,
					       शून्य);

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		p_rdma_info->num_qps = num_cons;
	अन्यथा
		p_rdma_info->num_qps = num_cons / 2; /* 2 cids per qp */

	num_tasks = qed_cxt_get_proto_tid_count(p_hwfn, PROTOCOLID_ROCE);

	/* Each MR uses a single task */
	p_rdma_info->num_mrs = num_tasks;

	/* Queue zone lines are shared between RoCE and L2 in such a way that
	 * they can be used by each without obकाष्ठाing the other.
	 */
	p_rdma_info->queue_zone_base = (u16)RESC_START(p_hwfn, QED_L2_QUEUE);
	p_rdma_info->max_queue_zones = (u16)RESC_NUM(p_hwfn, QED_L2_QUEUE);

	/* Allocate a काष्ठा with device params and fill it */
	p_rdma_info->dev = kzalloc(माप(*p_rdma_info->dev), GFP_KERNEL);
	अगर (!p_rdma_info->dev)
		वापस rc;

	/* Allocate a काष्ठा with port params and fill it */
	p_rdma_info->port = kzalloc(माप(*p_rdma_info->port), GFP_KERNEL);
	अगर (!p_rdma_info->port)
		जाओ मुक्त_rdma_dev;

	/* Allocate bit map क्रम pd's */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->pd_map, RDMA_MAX_PDS,
				 "PD");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate pd_map, rc = %d\n",
			   rc);
		जाओ मुक्त_rdma_port;
	पूर्ण

	/* Allocate bit map क्रम XRC Doमुख्यs */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->xrcd_map,
				 QED_RDMA_MAX_XRCDS, "XRCD");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate xrcd_map,rc = %d\n", rc);
		जाओ मुक्त_pd_map;
	पूर्ण

	/* Allocate DPI biपंचांगap */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->dpi_map,
				 p_hwfn->dpi_count, "DPI");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate DPI bitmap, rc = %d\n", rc);
		जाओ मुक्त_xrcd_map;
	पूर्ण

	/* Allocate biपंचांगap क्रम cq's. The maximum number of CQs is bound to
	 * the number of connections we support. (num_qps in iWARP or
	 * num_qps/2 in RoCE).
	 */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->cq_map, num_cons, "CQ");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate cq bitmap, rc = %d\n", rc);
		जाओ मुक्त_dpi_map;
	पूर्ण

	/* Allocate biपंचांगap क्रम toggle bit क्रम cq icids
	 * We toggle the bit every समय we create or resize cq क्रम a given icid.
	 * Size needs to equal the size of the cq bmap.
	 */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->toggle_bits,
				 num_cons, "Toggle");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate toggle bits, rc = %d\n", rc);
		जाओ मुक्त_cq_map;
	पूर्ण

	/* Allocate biपंचांगap क्रम itids */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->tid_map,
				 p_rdma_info->num_mrs, "MR");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate itids bitmaps, rc = %d\n", rc);
		जाओ मुक्त_toggle_map;
	पूर्ण

	/* Allocate biपंचांगap क्रम cids used क्रम qps. */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->cid_map, num_cons,
				 "CID");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate cid bitmap, rc = %d\n", rc);
		जाओ मुक्त_tid_map;
	पूर्ण

	/* Allocate biपंचांगap क्रम cids used क्रम responders/requesters. */
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->real_cid_map, num_cons,
				 "REAL_CID");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate real cid bitmap, rc = %d\n", rc);
		जाओ मुक्त_cid_map;
	पूर्ण

	/* The first SRQ follows the last XRC SRQ. This means that the
	 * SRQ IDs start from an offset equals to max_xrc_srqs.
	 */
	p_rdma_info->srq_id_offset = p_hwfn->p_cxt_mngr->xrc_srq_count;
	rc = qed_rdma_bmap_alloc(p_hwfn,
				 &p_rdma_info->xrc_srq_map,
				 p_hwfn->p_cxt_mngr->xrc_srq_count, "XRC SRQ");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate xrc srq bitmap, rc = %d\n", rc);
		जाओ मुक्त_real_cid_map;
	पूर्ण

	/* Allocate biपंचांगap क्रम srqs */
	p_rdma_info->num_srqs = p_hwfn->p_cxt_mngr->srq_count;
	rc = qed_rdma_bmap_alloc(p_hwfn, &p_rdma_info->srq_map,
				 p_rdma_info->num_srqs, "SRQ");
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Failed to allocate srq bitmap, rc = %d\n", rc);
		जाओ मुक्त_xrc_srq_map;
	पूर्ण

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		rc = qed_iwarp_alloc(p_hwfn);

	अगर (rc)
		जाओ मुक्त_srq_map;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Allocation successful\n");
	वापस 0;

मुक्त_srq_map:
	kमुक्त(p_rdma_info->srq_map.biपंचांगap);
मुक्त_xrc_srq_map:
	kमुक्त(p_rdma_info->xrc_srq_map.biपंचांगap);
मुक्त_real_cid_map:
	kमुक्त(p_rdma_info->real_cid_map.biपंचांगap);
मुक्त_cid_map:
	kमुक्त(p_rdma_info->cid_map.biपंचांगap);
मुक्त_tid_map:
	kमुक्त(p_rdma_info->tid_map.biपंचांगap);
मुक्त_toggle_map:
	kमुक्त(p_rdma_info->toggle_bits.biपंचांगap);
मुक्त_cq_map:
	kमुक्त(p_rdma_info->cq_map.biपंचांगap);
मुक्त_dpi_map:
	kमुक्त(p_rdma_info->dpi_map.biपंचांगap);
मुक्त_xrcd_map:
	kमुक्त(p_rdma_info->xrcd_map.biपंचांगap);
मुक्त_pd_map:
	kमुक्त(p_rdma_info->pd_map.biपंचांगap);
मुक्त_rdma_port:
	kमुक्त(p_rdma_info->port);
मुक्त_rdma_dev:
	kमुक्त(p_rdma_info->dev);

	वापस rc;
पूर्ण

व्योम qed_rdma_bmap_मुक्त(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_bmap *bmap, bool check)
अणु
	पूर्णांक weight = biपंचांगap_weight(bmap->biपंचांगap, bmap->max_count);
	पूर्णांक last_line = bmap->max_count / (64 * 8);
	पूर्णांक last_item = last_line * 8 +
	    DIV_ROUND_UP(bmap->max_count % (64 * 8), 64);
	u64 *pmap = (u64 *)bmap->biपंचांगap;
	पूर्णांक line, item, offset;
	u8 str_last_line[200] = अणु 0 पूर्ण;

	अगर (!weight || !check)
		जाओ end;

	DP_NOTICE(p_hwfn,
		  "%s bitmap not free - size=%d, weight=%d, 512 bits per line\n",
		  bmap->name, bmap->max_count, weight);

	/* prपूर्णांक aligned non-zero lines, अगर any */
	क्रम (item = 0, line = 0; line < last_line; line++, item += 8)
		अगर (biपंचांगap_weight((अचिन्हित दीर्घ *)&pmap[item], 64 * 8))
			DP_NOTICE(p_hwfn,
				  "line 0x%04x: 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx 0x%016llx\n",
				  line,
				  pmap[item],
				  pmap[item + 1],
				  pmap[item + 2],
				  pmap[item + 3],
				  pmap[item + 4],
				  pmap[item + 5],
				  pmap[item + 6], pmap[item + 7]);

	/* prपूर्णांक last unaligned non-zero line, अगर any */
	अगर ((bmap->max_count % (64 * 8)) &&
	    (biपंचांगap_weight((अचिन्हित दीर्घ *)&pmap[item],
			   bmap->max_count - item * 64))) अणु
		offset = प्र_लिखो(str_last_line, "line 0x%04x: ", line);
		क्रम (; item < last_item; item++)
			offset += प्र_लिखो(str_last_line + offset,
					  "0x%016llx ", pmap[item]);
		DP_NOTICE(p_hwfn, "%s\n", str_last_line);
	पूर्ण

end:
	kमुक्त(bmap->biपंचांगap);
	bmap->biपंचांगap = शून्य;
पूर्ण

अटल व्योम qed_rdma_resc_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		qed_iwarp_resc_मुक्त(p_hwfn);

	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->cid_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->pd_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->dpi_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->cq_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->toggle_bits, 0);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->tid_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->srq_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->real_cid_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->xrc_srq_map, 1);
	qed_rdma_bmap_मुक्त(p_hwfn, &p_hwfn->p_rdma_info->xrcd_map, 1);

	kमुक्त(p_rdma_info->port);
	kमुक्त(p_rdma_info->dev);
पूर्ण

अटल व्योम qed_rdma_मुक्त_tid(व्योम *rdma_cxt, u32 itid)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "itid = %08x\n", itid);

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->tid_map, itid);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

अटल व्योम qed_rdma_मुक्त_reserved_lkey(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_rdma_मुक्त_tid(p_hwfn, p_hwfn->p_rdma_info->dev->reserved_lkey);
पूर्ण

अटल व्योम qed_rdma_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Freeing RDMA\n");

	qed_rdma_मुक्त_reserved_lkey(p_hwfn);
	qed_cxt_मुक्त_proto_ilt(p_hwfn, p_hwfn->p_rdma_info->proto);
	qed_rdma_resc_मुक्त(p_hwfn);
पूर्ण

अटल व्योम qed_rdma_get_guid(काष्ठा qed_hwfn *p_hwfn, u8 *guid)
अणु
	guid[0] = p_hwfn->hw_info.hw_mac_addr[0] ^ 2;
	guid[1] = p_hwfn->hw_info.hw_mac_addr[1];
	guid[2] = p_hwfn->hw_info.hw_mac_addr[2];
	guid[3] = 0xff;
	guid[4] = 0xfe;
	guid[5] = p_hwfn->hw_info.hw_mac_addr[3];
	guid[6] = p_hwfn->hw_info.hw_mac_addr[4];
	guid[7] = p_hwfn->hw_info.hw_mac_addr[5];
पूर्ण

अटल व्योम qed_rdma_init_events(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_rdma_start_in_params *params)
अणु
	काष्ठा qed_rdma_events *events;

	events = &p_hwfn->p_rdma_info->events;

	events->unaffiliated_event = params->events->unaffiliated_event;
	events->affiliated_event = params->events->affiliated_event;
	events->context = params->events->context;
पूर्ण

अटल व्योम qed_rdma_init_devinfo(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_rdma_start_in_params *params)
अणु
	काष्ठा qed_rdma_device *dev = p_hwfn->p_rdma_info->dev;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u32 pci_status_control;
	u32 num_qps;

	/* Venकरोr specअगरic inक्रमmation */
	dev->venकरोr_id = cdev->venकरोr_id;
	dev->venकरोr_part_id = cdev->device_id;
	dev->hw_ver = cdev->chip_rev;
	dev->fw_ver = (FW_MAJOR_VERSION << 24) | (FW_MINOR_VERSION << 16) |
		      (FW_REVISION_VERSION << 8) | (FW_ENGINEERING_VERSION);

	qed_rdma_get_guid(p_hwfn, (u8 *)&dev->sys_image_guid);
	dev->node_guid = dev->sys_image_guid;

	dev->max_sge = min_t(u32, RDMA_MAX_SGE_PER_SQ_WQE,
			     RDMA_MAX_SGE_PER_RQ_WQE);

	अगर (cdev->rdma_max_sge)
		dev->max_sge = min_t(u32, cdev->rdma_max_sge, dev->max_sge);

	dev->max_srq_sge = QED_RDMA_MAX_SGE_PER_SRQ_WQE;
	अगर (p_hwfn->cdev->rdma_max_srq_sge) अणु
		dev->max_srq_sge = min_t(u32,
					 p_hwfn->cdev->rdma_max_srq_sge,
					 dev->max_srq_sge);
	पूर्ण
	dev->max_अंतरभूत = ROCE_REQ_MAX_INLINE_DATA_SIZE;

	dev->max_अंतरभूत = (cdev->rdma_max_अंतरभूत) ?
			  min_t(u32, cdev->rdma_max_अंतरभूत, dev->max_अंतरभूत) :
			  dev->max_अंतरभूत;

	dev->max_wqe = QED_RDMA_MAX_WQE;
	dev->max_cnq = (u8)FEAT_NUM(p_hwfn, QED_RDMA_CNQ);

	/* The number of QPs may be higher than QED_ROCE_MAX_QPS, because
	 * it is up-aligned to 16 and then to ILT page size within qed cxt.
	 * This is OK in terms of ILT but we करोn't want to configure the FW
	 * above its abilities
	 */
	num_qps = ROCE_MAX_QPS;
	num_qps = min_t(u64, num_qps, p_hwfn->p_rdma_info->num_qps);
	dev->max_qp = num_qps;

	/* CQs uses the same icids that QPs use hence they are limited by the
	 * number of icids. There are two icids per QP.
	 */
	dev->max_cq = num_qps * 2;

	/* The number of mrs is smaller by 1 since the first is reserved */
	dev->max_mr = p_hwfn->p_rdma_info->num_mrs - 1;
	dev->max_mr_size = QED_RDMA_MAX_MR_SIZE;

	/* The maximum CQE capacity per CQ supported.
	 * max number of cqes will be in two layer pbl,
	 * 8 is the poपूर्णांकer size in bytes
	 * 32 is the size of cq element in bytes
	 */
	अगर (params->cq_mode == QED_RDMA_CQ_MODE_32_BITS)
		dev->max_cqe = QED_RDMA_MAX_CQE_32_BIT;
	अन्यथा
		dev->max_cqe = QED_RDMA_MAX_CQE_16_BIT;

	dev->max_mw = 0;
	dev->max_mr_mw_fmr_pbl = (PAGE_SIZE / 8) * (PAGE_SIZE / 8);
	dev->max_mr_mw_fmr_size = dev->max_mr_mw_fmr_pbl * PAGE_SIZE;
	अगर (QED_IS_ROCE_PERSONALITY(p_hwfn))
		dev->max_pkey = QED_RDMA_MAX_P_KEY;

	dev->max_srq = p_hwfn->p_rdma_info->num_srqs;
	dev->max_srq_wr = QED_RDMA_MAX_SRQ_WQE_ELEM;
	dev->max_qp_resp_rd_atomic_resc = RDMA_RING_PAGE_SIZE /
					  (RDMA_RESP_RD_ATOMIC_ELM_SIZE * 2);
	dev->max_qp_req_rd_atomic_resc = RDMA_RING_PAGE_SIZE /
					 RDMA_REQ_RD_ATOMIC_ELM_SIZE;
	dev->max_dev_resp_rd_atomic_resc = dev->max_qp_resp_rd_atomic_resc *
					   p_hwfn->p_rdma_info->num_qps;
	dev->page_size_caps = QED_RDMA_PAGE_SIZE_CAPS;
	dev->dev_ack_delay = QED_RDMA_ACK_DELAY;
	dev->max_pd = RDMA_MAX_PDS;
	dev->max_ah = p_hwfn->p_rdma_info->num_qps;
	dev->max_stats_queues = (u8)RESC_NUM(p_hwfn, QED_RDMA_STATS_QUEUE);

	/* Set capablities */
	dev->dev_caps = 0;
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_RNR_NAK, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_PORT_ACTIVE_EVENT, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_PORT_CHANGE_EVENT, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_RESIZE_CQ, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_BASE_MEMORY_EXT, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_BASE_QUEUE_EXT, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_ZBVA, 1);
	SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_LOCAL_INV_FENCE, 1);

	/* Check atomic operations support in PCI configuration space. */
	pcie_capability_पढ़ो_dword(cdev->pdev, PCI_EXP_DEVCTL2,
				   &pci_status_control);

	अगर (pci_status_control & PCI_EXP_DEVCTL2_LTR_EN)
		SET_FIELD(dev->dev_caps, QED_RDMA_DEV_CAP_ATOMIC_OP, 1);

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		qed_iwarp_init_devinfo(p_hwfn);
पूर्ण

अटल व्योम qed_rdma_init_port(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rdma_port *port = p_hwfn->p_rdma_info->port;
	काष्ठा qed_rdma_device *dev = p_hwfn->p_rdma_info->dev;

	port->port_state = p_hwfn->mcp_info->link_output.link_up ?
			   QED_RDMA_PORT_UP : QED_RDMA_PORT_DOWN;

	port->max_msg_size = min_t(u64,
				   (dev->max_mr_mw_fmr_size *
				    p_hwfn->cdev->rdma_max_sge),
				   BIT(31));

	port->pkey_bad_counter = 0;
पूर्ण

अटल पूर्णांक qed_rdma_init_hw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	पूर्णांक rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Initializing HW\n");
	p_hwfn->b_rdma_enabled_in_prs = false;

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		qed_iwarp_init_hw(p_hwfn, p_ptt);
	अन्यथा
		rc = qed_roce_init_hw(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_rdma_start_fw(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_rdma_start_in_params *params,
			     काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा rdma_init_func_ramrod_data *p_ramrod;
	काष्ठा qed_rdma_cnq_params *p_cnq_pbl_list;
	काष्ठा rdma_init_func_hdr *p_params_header;
	काष्ठा rdma_cnq_params *p_cnq_params;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u32 cnq_id, sb_id;
	u16 igu_sb_id;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Starting FW\n");

	/* Save the number of cnqs क्रम the function बंद ramrod */
	p_hwfn->p_rdma_info->num_cnqs = params->desired_cnq;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent, RDMA_RAMROD_FUNC_INIT,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		वापस rc;

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn)) अणु
		qed_iwarp_init_fw_ramrod(p_hwfn,
					 &p_ent->ramrod.iwarp_init_func);
		p_ramrod = &p_ent->ramrod.iwarp_init_func.rdma;
	पूर्ण अन्यथा अणु
		p_ramrod = &p_ent->ramrod.roce_init_func.rdma;
	पूर्ण

	p_params_header = &p_ramrod->params_header;
	p_params_header->cnq_start_offset = (u8)RESC_START(p_hwfn,
							   QED_RDMA_CNQ_RAM);
	p_params_header->num_cnqs = params->desired_cnq;
	p_params_header->first_reg_srq_id =
	    cpu_to_le16(p_hwfn->p_rdma_info->srq_id_offset);
	p_params_header->reg_srq_base_addr =
	    cpu_to_le32(qed_cxt_get_ilt_page_size(p_hwfn, ILT_CLI_TSDM));
	अगर (params->cq_mode == QED_RDMA_CQ_MODE_16_BITS)
		p_params_header->cq_ring_mode = 1;
	अन्यथा
		p_params_header->cq_ring_mode = 0;

	क्रम (cnq_id = 0; cnq_id < params->desired_cnq; cnq_id++) अणु
		sb_id = qed_rdma_get_sb_id(p_hwfn, cnq_id);
		igu_sb_id = qed_get_igu_sb_id(p_hwfn, sb_id);
		p_ramrod->cnq_params[cnq_id].sb_num = cpu_to_le16(igu_sb_id);
		p_cnq_params = &p_ramrod->cnq_params[cnq_id];
		p_cnq_pbl_list = &params->cnq_pbl_list[cnq_id];

		p_cnq_params->sb_index = p_hwfn->pf_params.rdma_pf_params.gl_pi;
		p_cnq_params->num_pbl_pages = p_cnq_pbl_list->num_pbl_pages;

		DMA_REGPAIR_LE(p_cnq_params->pbl_base_addr,
			       p_cnq_pbl_list->pbl_ptr);

		/* we assume here that cnq_id and qz_offset are the same */
		p_cnq_params->queue_zone_num =
			cpu_to_le16(p_hwfn->p_rdma_info->queue_zone_base +
				    cnq_id);
	पूर्ण

	वापस qed_spq_post(p_hwfn, p_ent, शून्य);
पूर्ण

अटल पूर्णांक qed_rdma_alloc_tid(व्योम *rdma_cxt, u32 *itid)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Allocate TID\n");

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn,
				    &p_hwfn->p_rdma_info->tid_map, itid);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
	अगर (rc)
		जाओ out;

	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_TASK, *itid);
out:
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Allocate TID - done, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_rdma_reserve_lkey(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rdma_device *dev = p_hwfn->p_rdma_info->dev;

	/* Tid 0 will be used as the key क्रम "reserved MR".
	 * The driver should allocate memory क्रम it so it can be loaded but no
	 * ramrod should be passed on it.
	 */
	qed_rdma_alloc_tid(p_hwfn, &dev->reserved_lkey);
	अगर (dev->reserved_lkey != RDMA_RESERVED_LKEY) अणु
		DP_NOTICE(p_hwfn,
			  "Reserved lkey should be equal to RDMA_RESERVED_LKEY\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_rdma_setup(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  काष्ठा qed_rdma_start_in_params *params)
अणु
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA setup\n");

	qed_rdma_init_devinfo(p_hwfn, params);
	qed_rdma_init_port(p_hwfn);
	qed_rdma_init_events(p_hwfn, params);

	rc = qed_rdma_reserve_lkey(p_hwfn);
	अगर (rc)
		वापस rc;

	rc = qed_rdma_init_hw(p_hwfn, p_ptt);
	अगर (rc)
		वापस rc;

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn)) अणु
		rc = qed_iwarp_setup(p_hwfn, params);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		rc = qed_roce_setup(p_hwfn);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस qed_rdma_start_fw(p_hwfn, params, p_ptt);
पूर्ण

अटल पूर्णांक qed_rdma_stop(व्योम *rdma_cxt)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा rdma_बंद_func_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	काष्ठा qed_ptt *p_ptt;
	u32 ll2_ethertype_en;
	पूर्णांक rc = -EBUSY;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA stop\n");

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Failed to acquire PTT\n");
		वापस rc;
	पूर्ण

	/* Disable RoCE search */
	qed_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 0);
	p_hwfn->b_rdma_enabled_in_prs = false;
	p_hwfn->p_rdma_info->active = 0;
	qed_wr(p_hwfn, p_ptt, PRS_REG_ROCE_DEST_QP_MAX_PF, 0);

	ll2_ethertype_en = qed_rd(p_hwfn, p_ptt, PRS_REG_LIGHT_L2_ETHERTYPE_EN);

	qed_wr(p_hwfn, p_ptt, PRS_REG_LIGHT_L2_ETHERTYPE_EN,
	       (ll2_ethertype_en & 0xFFFE));

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn)) अणु
		rc = qed_iwarp_stop(p_hwfn);
		अगर (rc) अणु
			qed_ptt_release(p_hwfn, p_ptt);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		qed_roce_stop(p_hwfn);
	पूर्ण

	qed_ptt_release(p_hwfn, p_ptt);

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	/* Stop RoCE */
	rc = qed_sp_init_request(p_hwfn, &p_ent, RDMA_RAMROD_FUNC_CLOSE,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		जाओ out;

	p_ramrod = &p_ent->ramrod.rdma_बंद_func;

	p_ramrod->num_cnqs = p_hwfn->p_rdma_info->num_cnqs;
	p_ramrod->cnq_start_offset = (u8)RESC_START(p_hwfn, QED_RDMA_CNQ_RAM);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);

out:
	qed_rdma_मुक्त(p_hwfn);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA stop done, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_rdma_add_user(व्योम *rdma_cxt,
			     काष्ठा qed_rdma_add_user_out_params *out_params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	u32 dpi_start_offset;
	u32 वापसed_id = 0;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Adding User\n");

	/* Allocate DPI */
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_hwfn->p_rdma_info->dpi_map,
				    &वापसed_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	out_params->dpi = (u16)वापसed_id;

	/* Calculate the corresponding DPI address */
	dpi_start_offset = p_hwfn->dpi_start_offset;

	out_params->dpi_addr = p_hwfn->करोorbells + dpi_start_offset +
			       out_params->dpi * p_hwfn->dpi_size;

	out_params->dpi_phys_addr = p_hwfn->db_phys_addr +
				    dpi_start_offset +
				    ((out_params->dpi) * p_hwfn->dpi_size);

	out_params->dpi_size = p_hwfn->dpi_size;
	out_params->wid_count = p_hwfn->wid_count;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Adding user - done, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल काष्ठा qed_rdma_port *qed_rdma_query_port(व्योम *rdma_cxt)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा qed_rdma_port *p_port = p_hwfn->p_rdma_info->port;
	काष्ठा qed_mcp_link_state *p_link_output;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA Query port\n");

	/* The link state is saved only क्रम the leading hwfn */
	p_link_output = &QED_LEADING_HWFN(p_hwfn->cdev)->mcp_info->link_output;

	p_port->port_state = p_link_output->link_up ? QED_RDMA_PORT_UP
	    : QED_RDMA_PORT_DOWN;

	p_port->link_speed = p_link_output->speed;

	p_port->max_msg_size = RDMA_MAX_DATA_SIZE_IN_WQE;

	वापस p_port;
पूर्ण

अटल काष्ठा qed_rdma_device *qed_rdma_query_device(व्योम *rdma_cxt)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Query device\n");

	/* Return काष्ठा with device parameters */
	वापस p_hwfn->p_rdma_info->dev;
पूर्ण

अटल व्योम qed_rdma_cnq_prod_update(व्योम *rdma_cxt, u8 qz_offset, u16 prod)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	u16 qz_num;
	u32 addr;

	p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;

	अगर (qz_offset > p_hwfn->p_rdma_info->max_queue_zones) अणु
		DP_NOTICE(p_hwfn,
			  "queue zone offset %d is too large (max is %d)\n",
			  qz_offset, p_hwfn->p_rdma_info->max_queue_zones);
		वापस;
	पूर्ण

	qz_num = p_hwfn->p_rdma_info->queue_zone_base + qz_offset;
	addr = GTT_BAR0_MAP_REG_USDM_RAM +
	       USTORM_COMMON_QUEUE_CONS_OFFSET(qz_num);

	REG_WR16(p_hwfn, addr, prod);

	/* keep prod updates ordered */
	wmb();
पूर्ण

अटल पूर्णांक qed_fill_rdma_dev_info(काष्ठा qed_dev *cdev,
				  काष्ठा qed_dev_rdma_info *info)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_AFFIN_HWFN(cdev);

	स_रखो(info, 0, माप(*info));

	info->rdma_type = QED_IS_ROCE_PERSONALITY(p_hwfn) ?
	    QED_RDMA_TYPE_ROCE : QED_RDMA_TYPE_IWARP;

	info->user_dpm_enabled = (p_hwfn->db_bar_no_edpm == 0);

	qed_fill_dev_info(cdev, &info->common);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_rdma_get_sb_start(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक feat_num;

	अगर (cdev->num_hwfns > 1)
		feat_num = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_PF_L2_QUE);
	अन्यथा
		feat_num = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_PF_L2_QUE) *
			   cdev->num_hwfns;

	वापस feat_num;
पूर्ण

अटल पूर्णांक qed_rdma_get_min_cnq_msix(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक n_cnq = FEAT_NUM(QED_AFFIN_HWFN(cdev), QED_RDMA_CNQ);
	पूर्णांक n_msix = cdev->पूर्णांक_params.rdma_msix_cnt;

	वापस min_t(पूर्णांक, n_cnq, n_msix);
पूर्ण

अटल पूर्णांक qed_rdma_set_पूर्णांक(काष्ठा qed_dev *cdev, u16 cnt)
अणु
	पूर्णांक limit = 0;

	/* Mark the fastpath as मुक्त/used */
	cdev->पूर्णांक_params.fp_initialized = cnt ? true : false;

	अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode != QED_INT_MODE_MSIX) अणु
		DP_ERR(cdev,
		       "qed roce supports only MSI-X interrupts (detected %d).\n",
		       cdev->पूर्णांक_params.out.पूर्णांक_mode);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (cdev->पूर्णांक_params.fp_msix_cnt) अणु
		limit = cdev->पूर्णांक_params.rdma_msix_cnt;
	पूर्ण

	अगर (!limit)
		वापस -ENOMEM;

	वापस min_t(पूर्णांक, cnt, limit);
पूर्ण

अटल पूर्णांक qed_rdma_get_पूर्णांक(काष्ठा qed_dev *cdev, काष्ठा qed_पूर्णांक_info *info)
अणु
	स_रखो(info, 0, माप(*info));

	अगर (!cdev->पूर्णांक_params.fp_initialized) अणु
		DP_INFO(cdev,
			"Protocol driver requested interrupt information, but its support is not yet configured\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_MSIX) अणु
		पूर्णांक msix_base = cdev->पूर्णांक_params.rdma_msix_base;

		info->msix_cnt = cdev->पूर्णांक_params.rdma_msix_cnt;
		info->msix = &cdev->पूर्णांक_params.msix_table[msix_base];

		DP_VERBOSE(cdev, QED_MSG_RDMA, "msix_cnt = %d msix_base=%d\n",
			   info->msix_cnt, msix_base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_rdma_alloc_pd(व्योम *rdma_cxt, u16 *pd)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	u32 वापसed_id;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Alloc PD\n");

	/* Allocates an unused protection करोमुख्य */
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn,
				    &p_hwfn->p_rdma_info->pd_map, &वापसed_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	*pd = (u16)वापसed_id;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Alloc PD - done, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल व्योम qed_rdma_मुक्त_pd(व्योम *rdma_cxt, u16 pd)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "pd = %08x\n", pd);

	/* Returns a previously allocated protection करोमुख्य क्रम reuse */
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->pd_map, pd);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

अटल पूर्णांक qed_rdma_alloc_xrcd(व्योम *rdma_cxt, u16 *xrcd_id)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	u32 वापसed_id;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Alloc XRCD\n");

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn,
				    &p_hwfn->p_rdma_info->xrcd_map,
				    &वापसed_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed in allocating xrcd id\n");
		वापस rc;
	पूर्ण

	*xrcd_id = (u16)वापसed_id;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Alloc XRCD - done, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल व्योम qed_rdma_मुक्त_xrcd(व्योम *rdma_cxt, u16 xrcd_id)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "xrcd_id = %08x\n", xrcd_id);

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->xrcd_map, xrcd_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

अटल क्रमागत qed_rdma_toggle_bit
qed_rdma_toggle_bit_create_resize_cq(काष्ठा qed_hwfn *p_hwfn, u16 icid)
अणु
	काष्ठा qed_rdma_info *p_info = p_hwfn->p_rdma_info;
	क्रमागत qed_rdma_toggle_bit toggle_bit;
	u32 bmap_id;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", icid);

	/* the function toggle the bit that is related to a given icid
	 * and वापसs the new toggle bit's value
	 */
	bmap_id = icid - qed_cxt_get_proto_cid_start(p_hwfn, p_info->proto);

	spin_lock_bh(&p_info->lock);
	toggle_bit = !test_and_change_bit(bmap_id,
					  p_info->toggle_bits.biपंचांगap);
	spin_unlock_bh(&p_info->lock);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QED_RDMA_TOGGLE_BIT_= %d\n",
		   toggle_bit);

	वापस toggle_bit;
पूर्ण

अटल पूर्णांक qed_rdma_create_cq(व्योम *rdma_cxt,
			      काष्ठा qed_rdma_create_cq_in_params *params,
			      u16 *icid)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा qed_rdma_info *p_info = p_hwfn->p_rdma_info;
	काष्ठा rdma_create_cq_ramrod_data *p_ramrod;
	क्रमागत qed_rdma_toggle_bit toggle_bit;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	u32 वापसed_id, start_cid;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "cq_handle = %08x%08x\n",
		   params->cq_handle_hi, params->cq_handle_lo);

	/* Allocate icid */
	spin_lock_bh(&p_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, &p_info->cq_map, &वापसed_id);
	spin_unlock_bh(&p_info->lock);

	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Can't create CQ, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	start_cid = qed_cxt_get_proto_cid_start(p_hwfn,
						p_info->proto);
	*icid = वापसed_id + start_cid;

	/* Check अगर icid requires a page allocation */
	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, QED_ELEM_CXT, *icid);
	अगर (rc)
		जाओ err;

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = *icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	/* Send create CQ ramrod */
	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_CREATE_CQ,
				 p_info->proto, &init_data);
	अगर (rc)
		जाओ err;

	p_ramrod = &p_ent->ramrod.rdma_create_cq;

	p_ramrod->cq_handle.hi = cpu_to_le32(params->cq_handle_hi);
	p_ramrod->cq_handle.lo = cpu_to_le32(params->cq_handle_lo);
	p_ramrod->dpi = cpu_to_le16(params->dpi);
	p_ramrod->is_two_level_pbl = params->pbl_two_level;
	p_ramrod->max_cqes = cpu_to_le32(params->cq_size);
	DMA_REGPAIR_LE(p_ramrod->pbl_addr, params->pbl_ptr);
	p_ramrod->pbl_num_pages = cpu_to_le16(params->pbl_num_pages);
	p_ramrod->cnq_id = (u8)RESC_START(p_hwfn, QED_RDMA_CNQ_RAM) +
			   params->cnq_id;
	p_ramrod->पूर्णांक_समयout = cpu_to_le16(params->पूर्णांक_समयout);

	/* toggle the bit क्रम every resize or create cq क्रम a given icid */
	toggle_bit = qed_rdma_toggle_bit_create_resize_cq(p_hwfn, *icid);

	p_ramrod->toggle_bit = toggle_bit;

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc) अणु
		/* restore toggle bit */
		qed_rdma_toggle_bit_create_resize_cq(p_hwfn, *icid);
		जाओ err;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Created CQ, rc = %d\n", rc);
	वापस rc;

err:
	/* release allocated icid */
	spin_lock_bh(&p_info->lock);
	qed_bmap_release_id(p_hwfn, &p_info->cq_map, वापसed_id);
	spin_unlock_bh(&p_info->lock);
	DP_NOTICE(p_hwfn, "Create CQ failed, rc = %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_rdma_destroy_cq(व्योम *rdma_cxt,
		    काष्ठा qed_rdma_destroy_cq_in_params *in_params,
		    काष्ठा qed_rdma_destroy_cq_out_params *out_params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा rdma_destroy_cq_output_params *p_ramrod_res;
	काष्ठा rdma_destroy_cq_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	dma_addr_t ramrod_res_phys;
	क्रमागत protocol_type proto;
	पूर्णांक rc = -ENOMEM;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", in_params->icid);

	p_ramrod_res =
	    dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
			       माप(काष्ठा rdma_destroy_cq_output_params),
			       &ramrod_res_phys, GFP_KERNEL);
	अगर (!p_ramrod_res) अणु
		DP_NOTICE(p_hwfn,
			  "qed destroy cq failed: cannot allocate memory (ramrod)\n");
		वापस rc;
	पूर्ण

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.cid = in_params->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;
	proto = p_hwfn->p_rdma_info->proto;
	/* Send destroy CQ ramrod */
	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_DESTROY_CQ,
				 proto, &init_data);
	अगर (rc)
		जाओ err;

	p_ramrod = &p_ent->ramrod.rdma_destroy_cq;
	DMA_REGPAIR_LE(p_ramrod->output_params_addr, ramrod_res_phys);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err;

	out_params->num_cq_notअगर = le16_to_cpu(p_ramrod_res->cnq_num);

	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा rdma_destroy_cq_output_params),
			  p_ramrod_res, ramrod_res_phys);

	/* Free icid */
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);

	qed_bmap_release_id(p_hwfn,
			    &p_hwfn->p_rdma_info->cq_map,
			    (in_params->icid -
			     qed_cxt_get_proto_cid_start(p_hwfn, proto)));

	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Destroyed CQ, rc = %d\n", rc);
	वापस rc;

err:	dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
			  माप(काष्ठा rdma_destroy_cq_output_params),
			  p_ramrod_res, ramrod_res_phys);

	वापस rc;
पूर्ण

व्योम qed_rdma_set_fw_mac(__le16 *p_fw_mac, स्थिर u8 *p_qed_mac)
अणु
	p_fw_mac[0] = cpu_to_le16((p_qed_mac[0] << 8) + p_qed_mac[1]);
	p_fw_mac[1] = cpu_to_le16((p_qed_mac[2] << 8) + p_qed_mac[3]);
	p_fw_mac[2] = cpu_to_le16((p_qed_mac[4] << 8) + p_qed_mac[5]);
पूर्ण

अटल पूर्णांक qed_rdma_query_qp(व्योम *rdma_cxt,
			     काष्ठा qed_rdma_qp *qp,
			     काष्ठा qed_rdma_query_qp_out_params *out_params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	पूर्णांक rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	/* The following fields are filled in from qp and not FW as they can't
	 * be modअगरied by FW
	 */
	out_params->mtu = qp->mtu;
	out_params->dest_qp = qp->dest_qp;
	out_params->incoming_atomic_en = qp->incoming_atomic_en;
	out_params->e2e_flow_control_en = qp->e2e_flow_control_en;
	out_params->incoming_rdma_पढ़ो_en = qp->incoming_rdma_पढ़ो_en;
	out_params->incoming_rdma_ग_लिखो_en = qp->incoming_rdma_ग_लिखो_en;
	out_params->dgid = qp->dgid;
	out_params->flow_label = qp->flow_label;
	out_params->hop_limit_ttl = qp->hop_limit_ttl;
	out_params->traffic_class_tos = qp->traffic_class_tos;
	out_params->समयout = qp->ack_समयout;
	out_params->rnr_retry = qp->rnr_retry_cnt;
	out_params->retry_cnt = qp->retry_cnt;
	out_params->min_rnr_nak_समयr = qp->min_rnr_nak_समयr;
	out_params->pkey_index = 0;
	out_params->max_rd_atomic = qp->max_rd_atomic_req;
	out_params->max_dest_rd_atomic = qp->max_rd_atomic_resp;
	out_params->sqd_async = qp->sqd_async;

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		qed_iwarp_query_qp(qp, out_params);
	अन्यथा
		rc = qed_roce_query_qp(p_hwfn, qp, out_params);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Query QP, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_rdma_destroy_qp(व्योम *rdma_cxt, काष्ठा qed_rdma_qp *qp)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	पूर्णांक rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn))
		rc = qed_iwarp_destroy_qp(p_hwfn, qp);
	अन्यथा
		rc = qed_roce_destroy_qp(p_hwfn, qp);

	/* मुक्त qp params काष्ठा */
	kमुक्त(qp);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP destroyed\n");
	वापस rc;
पूर्ण

अटल काष्ठा qed_rdma_qp *
qed_rdma_create_qp(व्योम *rdma_cxt,
		   काष्ठा qed_rdma_create_qp_in_params *in_params,
		   काष्ठा qed_rdma_create_qp_out_params *out_params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा qed_rdma_qp *qp;
	u8 max_stats_queues;
	पूर्णांक rc;

	अगर (!rdma_cxt || !in_params || !out_params ||
	    !p_hwfn->p_rdma_info->active) अणु
		DP_ERR(p_hwfn->cdev,
		       "qed roce create qp failed due to NULL entry (rdma_cxt=%p, in=%p, out=%p, roce_info=?\n",
		       rdma_cxt, in_params, out_params);
		वापस शून्य;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "qed rdma create qp called with qp_handle = %08x%08x\n",
		   in_params->qp_handle_hi, in_params->qp_handle_lo);

	/* Some sanity checks... */
	max_stats_queues = p_hwfn->p_rdma_info->dev->max_stats_queues;
	अगर (in_params->stats_queue >= max_stats_queues) अणु
		DP_ERR(p_hwfn->cdev,
		       "qed rdma create qp failed due to invalid statistics queue %d. maximum is %d\n",
		       in_params->stats_queue, max_stats_queues);
		वापस शून्य;
	पूर्ण

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn)) अणु
		अगर (in_params->sq_num_pages * माप(काष्ठा regpair) >
		    IWARP_SHARED_QUEUE_PAGE_SQ_PBL_MAX_SIZE) अणु
			DP_NOTICE(p_hwfn->cdev,
				  "Sq num pages: %d exceeds maximum\n",
				  in_params->sq_num_pages);
			वापस शून्य;
		पूर्ण
		अगर (in_params->rq_num_pages * माप(काष्ठा regpair) >
		    IWARP_SHARED_QUEUE_PAGE_RQ_PBL_MAX_SIZE) अणु
			DP_NOTICE(p_hwfn->cdev,
				  "Rq num pages: %d exceeds maximum\n",
				  in_params->rq_num_pages);
			वापस शून्य;
		पूर्ण
	पूर्ण

	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस शून्य;

	qp->cur_state = QED_ROCE_QP_STATE_RESET;
	qp->qp_handle.hi = cpu_to_le32(in_params->qp_handle_hi);
	qp->qp_handle.lo = cpu_to_le32(in_params->qp_handle_lo);
	qp->qp_handle_async.hi = cpu_to_le32(in_params->qp_handle_async_hi);
	qp->qp_handle_async.lo = cpu_to_le32(in_params->qp_handle_async_lo);
	qp->use_srq = in_params->use_srq;
	qp->संकेत_all = in_params->संकेत_all;
	qp->fmr_and_reserved_lkey = in_params->fmr_and_reserved_lkey;
	qp->pd = in_params->pd;
	qp->dpi = in_params->dpi;
	qp->sq_cq_id = in_params->sq_cq_id;
	qp->sq_num_pages = in_params->sq_num_pages;
	qp->sq_pbl_ptr = in_params->sq_pbl_ptr;
	qp->rq_cq_id = in_params->rq_cq_id;
	qp->rq_num_pages = in_params->rq_num_pages;
	qp->rq_pbl_ptr = in_params->rq_pbl_ptr;
	qp->srq_id = in_params->srq_id;
	qp->req_offloaded = false;
	qp->resp_offloaded = false;
	qp->e2e_flow_control_en = qp->use_srq ? false : true;
	qp->stats_queue = in_params->stats_queue;
	qp->qp_type = in_params->qp_type;
	qp->xrcd_id = in_params->xrcd_id;

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn)) अणु
		rc = qed_iwarp_create_qp(p_hwfn, qp, out_params);
		qp->qpid = qp->icid;
	पूर्ण अन्यथा अणु
		qp->edpm_mode = GET_FIELD(in_params->flags, QED_ROCE_EDPM_MODE);
		rc = qed_roce_alloc_cid(p_hwfn, &qp->icid);
		qp->qpid = ((0xFF << 16) | qp->icid);
	पूर्ण

	अगर (rc) अणु
		kमुक्त(qp);
		वापस शून्य;
	पूर्ण

	out_params->icid = qp->icid;
	out_params->qp_id = qp->qpid;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Create QP, rc = %d\n", rc);
	वापस qp;
पूर्ण

अटल पूर्णांक qed_rdma_modअगरy_qp(व्योम *rdma_cxt,
			      काष्ठा qed_rdma_qp *qp,
			      काष्ठा qed_rdma_modअगरy_qp_in_params *params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	क्रमागत qed_roce_qp_state prev_state;
	पूर्णांक rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x params->new_state=%d\n",
		   qp->icid, params->new_state);

	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN)) अणु
		qp->incoming_rdma_पढ़ो_en = params->incoming_rdma_पढ़ो_en;
		qp->incoming_rdma_ग_लिखो_en = params->incoming_rdma_ग_लिखो_en;
		qp->incoming_atomic_en = params->incoming_atomic_en;
	पूर्ण

	/* Update QP काष्ठाure with the updated values */
	अगर (GET_FIELD(params->modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_ROCE_MODE))
		qp->roce_mode = params->roce_mode;
	अगर (GET_FIELD(params->modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_PKEY))
		qp->pkey = params->pkey;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN))
		qp->e2e_flow_control_en = params->e2e_flow_control_en;
	अगर (GET_FIELD(params->modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_DEST_QP))
		qp->dest_qp = params->dest_qp;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR)) अणु
		/* Indicates that the following parameters have changed:
		 * Traffic class, flow label, hop limit, source GID,
		 * destination GID, loopback indicator
		 */
		qp->traffic_class_tos = params->traffic_class_tos;
		qp->flow_label = params->flow_label;
		qp->hop_limit_ttl = params->hop_limit_ttl;

		qp->sgid = params->sgid;
		qp->dgid = params->dgid;
		qp->udp_src_port = 0;
		qp->vlan_id = params->vlan_id;
		qp->mtu = params->mtu;
		qp->lb_indication = params->lb_indication;
		स_नकल((u8 *)&qp->remote_mac_addr[0],
		       (u8 *)&params->remote_mac_addr[0], ETH_ALEN);
		अगर (params->use_local_mac) अणु
			स_नकल((u8 *)&qp->local_mac_addr[0],
			       (u8 *)&params->local_mac_addr[0], ETH_ALEN);
		पूर्ण अन्यथा अणु
			स_नकल((u8 *)&qp->local_mac_addr[0],
			       (u8 *)&p_hwfn->hw_info.hw_mac_addr, ETH_ALEN);
		पूर्ण
	पूर्ण
	अगर (GET_FIELD(params->modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_RQ_PSN))
		qp->rq_psn = params->rq_psn;
	अगर (GET_FIELD(params->modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_SQ_PSN))
		qp->sq_psn = params->sq_psn;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ))
		qp->max_rd_atomic_req = params->max_rd_atomic_req;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP))
		qp->max_rd_atomic_resp = params->max_rd_atomic_resp;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT))
		qp->ack_समयout = params->ack_समयout;
	अगर (GET_FIELD(params->modअगरy_flags, QED_ROCE_MODIFY_QP_VALID_RETRY_CNT))
		qp->retry_cnt = params->retry_cnt;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT))
		qp->rnr_retry_cnt = params->rnr_retry_cnt;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER))
		qp->min_rnr_nak_समयr = params->min_rnr_nak_समयr;

	qp->sqd_async = params->sqd_async;

	prev_state = qp->cur_state;
	अगर (GET_FIELD(params->modअगरy_flags,
		      QED_RDMA_MODIFY_QP_VALID_NEW_STATE)) अणु
		qp->cur_state = params->new_state;
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "qp->cur_state=%d\n",
			   qp->cur_state);
	पूर्ण

	चयन (qp->qp_type) अणु
	हाल QED_RDMA_QP_TYPE_XRC_INI:
		qp->has_req = true;
		अवरोध;
	हाल QED_RDMA_QP_TYPE_XRC_TGT:
		qp->has_resp = true;
		अवरोध;
	शेष:
		qp->has_req  = true;
		qp->has_resp = true;
	पूर्ण

	अगर (QED_IS_IWARP_PERSONALITY(p_hwfn)) अणु
		क्रमागत qed_iwarp_qp_state new_state =
		    qed_roce2iwarp_state(qp->cur_state);

		rc = qed_iwarp_modअगरy_qp(p_hwfn, qp, new_state, 0);
	पूर्ण अन्यथा अणु
		rc = qed_roce_modअगरy_qp(p_hwfn, qp, prev_state, params);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Modify QP, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक
qed_rdma_रेजिस्टर_tid(व्योम *rdma_cxt,
		      काष्ठा qed_rdma_रेजिस्टर_tid_in_params *params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा rdma_रेजिस्टर_tid_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	क्रमागत rdma_tid_type tid_type;
	u8 fw_वापस_code;
	u16 flags = 0;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "itid = %08x\n", params->itid);

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent, RDMA_RAMROD_REGISTER_MR,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (p_hwfn->p_rdma_info->last_tid < params->itid)
		p_hwfn->p_rdma_info->last_tid = params->itid;

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_TWO_LEVEL_PBL,
		  params->pbl_two_level);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_ZERO_BASED,
		  false);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_PHY_MR, params->phy_mr);

	/* Don't initialize D/C field, as it may override other bits. */
	अगर (!(params->tid_type == QED_RDMA_TID_FMR) && !(params->dma_mr))
		SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_PAGE_SIZE_LOG,
			  params->page_size_log - 12);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_READ,
		  params->remote_पढ़ो);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_WRITE,
		  params->remote_ग_लिखो);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_REMOTE_ATOMIC,
		  params->remote_atomic);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_LOCAL_WRITE,
		  params->local_ग_लिखो);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_LOCAL_READ,
		  params->local_पढ़ो);

	SET_FIELD(flags, RDMA_REGISTER_TID_RAMROD_DATA_ENABLE_MW_BIND,
		  params->mw_bind);

	p_ramrod = &p_ent->ramrod.rdma_रेजिस्टर_tid;
	p_ramrod->flags = cpu_to_le16(flags);

	SET_FIELD(p_ramrod->flags1,
		  RDMA_REGISTER_TID_RAMROD_DATA_PBL_PAGE_SIZE_LOG,
		  params->pbl_page_size_log - 12);

	SET_FIELD(p_ramrod->flags2, RDMA_REGISTER_TID_RAMROD_DATA_DMA_MR,
		  params->dma_mr);

	चयन (params->tid_type) अणु
	हाल QED_RDMA_TID_REGISTERED_MR:
		tid_type = RDMA_TID_REGISTERED_MR;
		अवरोध;
	हाल QED_RDMA_TID_FMR:
		tid_type = RDMA_TID_FMR;
		अवरोध;
	हाल QED_RDMA_TID_MW:
		tid_type = RDMA_TID_MW;
		अवरोध;
	शेष:
		rc = -EINVAL;
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = %d\n", rc);
		qed_sp_destroy_request(p_hwfn, p_ent);
		वापस rc;
	पूर्ण

	SET_FIELD(p_ramrod->flags1, RDMA_REGISTER_TID_RAMROD_DATA_TID_TYPE,
		  tid_type);

	p_ramrod->itid = cpu_to_le32(params->itid);
	p_ramrod->key = params->key;
	p_ramrod->pd = cpu_to_le16(params->pd);
	p_ramrod->length_hi = (u8)(params->length >> 32);
	p_ramrod->length_lo = DMA_LO_LE(params->length);
	DMA_REGPAIR_LE(p_ramrod->va, params->vaddr);
	DMA_REGPAIR_LE(p_ramrod->pbl_base, params->pbl_ptr);

	/* DIF */
	अगर (params->dअगर_enabled) अणु
		SET_FIELD(p_ramrod->flags2,
			  RDMA_REGISTER_TID_RAMROD_DATA_DIF_ON_HOST_FLG, 1);
		DMA_REGPAIR_LE(p_ramrod->dअगर_error_addr,
			       params->dअगर_error_addr);
	पूर्ण

	rc = qed_spq_post(p_hwfn, p_ent, &fw_वापस_code);
	अगर (rc)
		वापस rc;

	अगर (fw_वापस_code != RDMA_RETURN_OK) अणु
		DP_NOTICE(p_hwfn, "fw_return_code = %d\n", fw_वापस_code);
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Register TID, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_rdma_deरेजिस्टर_tid(व्योम *rdma_cxt, u32 itid)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा rdma_deरेजिस्टर_tid_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data;
	काष्ठा qed_spq_entry *p_ent;
	काष्ठा qed_ptt *p_ptt;
	u8 fw_वापस_code;
	पूर्णांक rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "itid = %08x\n", itid);

	/* Get SPQ entry */
	स_रखो(&init_data, 0, माप(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent, RDMA_RAMROD_DEREGISTER_MR,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = %d\n", rc);
		वापस rc;
	पूर्ण

	p_ramrod = &p_ent->ramrod.rdma_deरेजिस्टर_tid;
	p_ramrod->itid = cpu_to_le32(itid);

	rc = qed_spq_post(p_hwfn, p_ent, &fw_वापस_code);
	अगर (rc) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (fw_वापस_code == RDMA_RETURN_DEREGISTER_MR_BAD_STATE_ERR) अणु
		DP_NOTICE(p_hwfn, "fw_return_code = %d\n", fw_वापस_code);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (fw_वापस_code == RDMA_RETURN_NIG_DRAIN_REQ) अणु
		/* Bit indicating that the TID is in use and a nig drain is
		 * required beक्रमe sending the ramrod again
		 */
		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt) अणु
			rc = -EBUSY;
			DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
				   "Failed to acquire PTT\n");
			वापस rc;
		पूर्ण

		rc = qed_mcp_drain(p_hwfn, p_ptt);
		अगर (rc) अणु
			qed_ptt_release(p_hwfn, p_ptt);
			DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
				   "Drain failed\n");
			वापस rc;
		पूर्ण

		qed_ptt_release(p_hwfn, p_ptt);

		/* Resend the ramrod */
		rc = qed_sp_init_request(p_hwfn, &p_ent,
					 RDMA_RAMROD_DEREGISTER_MR,
					 p_hwfn->p_rdma_info->proto,
					 &init_data);
		अगर (rc) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
				   "Failed to init sp-element\n");
			वापस rc;
		पूर्ण

		rc = qed_spq_post(p_hwfn, p_ent, &fw_वापस_code);
		अगर (rc) अणु
			DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
				   "Ramrod failed\n");
			वापस rc;
		पूर्ण

		अगर (fw_वापस_code != RDMA_RETURN_OK) अणु
			DP_NOTICE(p_hwfn, "fw_return_code = %d\n",
				  fw_वापस_code);
			वापस rc;
		पूर्ण
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "De-registered TID, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल व्योम *qed_rdma_get_rdma_ctx(काष्ठा qed_dev *cdev)
अणु
	वापस QED_AFFIN_HWFN(cdev);
पूर्ण

अटल काष्ठा qed_bmap *qed_rdma_get_srq_bmap(काष्ठा qed_hwfn *p_hwfn,
					      bool is_xrc)
अणु
	अगर (is_xrc)
		वापस &p_hwfn->p_rdma_info->xrc_srq_map;

	वापस &p_hwfn->p_rdma_info->srq_map;
पूर्ण

अटल पूर्णांक qed_rdma_modअगरy_srq(व्योम *rdma_cxt,
			       काष्ठा qed_rdma_modअगरy_srq_in_params *in_params)
अणु
	काष्ठा rdma_srq_modअगरy_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data = अणुपूर्ण;
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_spq_entry *p_ent;
	u16 opaque_fid;
	पूर्णांक rc;

	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_MODIFY_SRQ,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.rdma_modअगरy_srq;
	p_ramrod->srq_id.srq_idx = cpu_to_le16(in_params->srq_id);
	opaque_fid = p_hwfn->hw_info.opaque_fid;
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(opaque_fid);
	p_ramrod->wqe_limit = cpu_to_le32(in_params->wqe_limit);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		वापस rc;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "modified SRQ id = %x, is_xrc=%u\n",
		   in_params->srq_id, in_params->is_xrc);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_rdma_destroy_srq(व्योम *rdma_cxt,
		     काष्ठा qed_rdma_destroy_srq_in_params *in_params)
अणु
	काष्ठा rdma_srq_destroy_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data = अणुपूर्ण;
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	काष्ठा qed_spq_entry *p_ent;
	काष्ठा qed_bmap *bmap;
	u16 opaque_fid;
	u16 offset;
	पूर्णांक rc;

	opaque_fid = p_hwfn->hw_info.opaque_fid;

	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_DESTROY_SRQ,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		वापस rc;

	p_ramrod = &p_ent->ramrod.rdma_destroy_srq;
	p_ramrod->srq_id.srq_idx = cpu_to_le16(in_params->srq_id);
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(opaque_fid);

	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		वापस rc;

	bmap = qed_rdma_get_srq_bmap(p_hwfn, in_params->is_xrc);
	offset = (in_params->is_xrc) ? 0 : p_hwfn->p_rdma_info->srq_id_offset;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, bmap, in_params->srq_id - offset);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "XRC/SRQ destroyed Id = %x, is_xrc=%u\n",
		   in_params->srq_id, in_params->is_xrc);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_rdma_create_srq(व्योम *rdma_cxt,
		    काष्ठा qed_rdma_create_srq_in_params *in_params,
		    काष्ठा qed_rdma_create_srq_out_params *out_params)
अणु
	काष्ठा rdma_srq_create_ramrod_data *p_ramrod;
	काष्ठा qed_sp_init_data init_data = अणुपूर्ण;
	काष्ठा qed_hwfn *p_hwfn = rdma_cxt;
	क्रमागत qed_cxt_elem_type elem_type;
	काष्ठा qed_spq_entry *p_ent;
	u16 opaque_fid, srq_id;
	काष्ठा qed_bmap *bmap;
	u32 वापसed_id;
	u16 offset;
	पूर्णांक rc;

	bmap = qed_rdma_get_srq_bmap(p_hwfn, in_params->is_xrc);
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	rc = qed_rdma_bmap_alloc_id(p_hwfn, bmap, &वापसed_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	अगर (rc) अणु
		DP_NOTICE(p_hwfn,
			  "failed to allocate xrc/srq id (is_xrc=%u)\n",
			  in_params->is_xrc);
		वापस rc;
	पूर्ण

	elem_type = (in_params->is_xrc) ? (QED_ELEM_XRC_SRQ) : (QED_ELEM_SRQ);
	rc = qed_cxt_dynamic_ilt_alloc(p_hwfn, elem_type, वापसed_id);
	अगर (rc)
		जाओ err;

	opaque_fid = p_hwfn->hw_info.opaque_fid;

	opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.opaque_fid = opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 RDMA_RAMROD_CREATE_SRQ,
				 p_hwfn->p_rdma_info->proto, &init_data);
	अगर (rc)
		जाओ err;

	p_ramrod = &p_ent->ramrod.rdma_create_srq;
	DMA_REGPAIR_LE(p_ramrod->pbl_base_addr, in_params->pbl_base_addr);
	p_ramrod->pages_in_srq_pbl = cpu_to_le16(in_params->num_pages);
	p_ramrod->pd_id = cpu_to_le16(in_params->pd_id);
	p_ramrod->srq_id.opaque_fid = cpu_to_le16(opaque_fid);
	p_ramrod->page_size = cpu_to_le16(in_params->page_size);
	DMA_REGPAIR_LE(p_ramrod->producers_addr, in_params->prod_pair_addr);
	offset = (in_params->is_xrc) ? 0 : p_hwfn->p_rdma_info->srq_id_offset;
	srq_id = (u16)वापसed_id + offset;
	p_ramrod->srq_id.srq_idx = cpu_to_le16(srq_id);

	अगर (in_params->is_xrc) अणु
		SET_FIELD(p_ramrod->flags,
			  RDMA_SRQ_CREATE_RAMROD_DATA_XRC_FLAG, 1);
		SET_FIELD(p_ramrod->flags,
			  RDMA_SRQ_CREATE_RAMROD_DATA_RESERVED_KEY_EN,
			  in_params->reserved_key_en);
		p_ramrod->xrc_srq_cq_cid =
			cpu_to_le32((p_hwfn->hw_info.opaque_fid << 16) |
				     in_params->cq_cid);
		p_ramrod->xrc_करोमुख्य = cpu_to_le16(in_params->xrcd_id);
	पूर्ण
	rc = qed_spq_post(p_hwfn, p_ent, शून्य);
	अगर (rc)
		जाओ err;

	out_params->srq_id = srq_id;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_RDMA,
		   "XRC/SRQ created Id = %x (is_xrc=%u)\n",
		   out_params->srq_id, in_params->is_xrc);
	वापस rc;

err:
	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, bmap, वापसed_id);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);

	वापस rc;
पूर्ण

bool qed_rdma_allocated_qps(काष्ठा qed_hwfn *p_hwfn)
अणु
	bool result;

	/* अगर rdma wasn't activated yet, naturally there are no qps */
	अगर (!p_hwfn->p_rdma_info->active)
		वापस false;

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	अगर (!p_hwfn->p_rdma_info->cid_map.biपंचांगap)
		result = false;
	अन्यथा
		result = !qed_bmap_is_empty(&p_hwfn->p_rdma_info->cid_map);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
	वापस result;
पूर्ण

व्योम qed_rdma_dpm_conf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 val;

	val = (p_hwfn->dcbx_no_edpm || p_hwfn->db_bar_no_edpm) ? 0 : 1;

	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_DPM_ENABLE, val);
	DP_VERBOSE(p_hwfn, (QED_MSG_DCB | QED_MSG_RDMA),
		   "Changing DPM_EN state to %d (DCBX=%d, DB_BAR=%d)\n",
		   val, p_hwfn->dcbx_no_edpm, p_hwfn->db_bar_no_edpm);
पूर्ण


व्योम qed_rdma_dpm_bar(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	p_hwfn->db_bar_no_edpm = true;

	qed_rdma_dpm_conf(p_hwfn, p_ptt);
पूर्ण

अटल पूर्णांक qed_rdma_start(व्योम *rdma_cxt,
			  काष्ठा qed_rdma_start_in_params *params)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = -EBUSY;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "desired_cnq = %08x\n", params->desired_cnq);

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		जाओ err;

	rc = qed_rdma_alloc(p_hwfn);
	अगर (rc)
		जाओ err1;

	rc = qed_rdma_setup(p_hwfn, p_ptt, params);
	अगर (rc)
		जाओ err2;

	qed_ptt_release(p_hwfn, p_ptt);
	p_hwfn->p_rdma_info->active = 1;

	वापस rc;

err2:
	qed_rdma_मुक्त(p_hwfn);
err1:
	qed_ptt_release(p_hwfn, p_ptt);
err:
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "RDMA start - error, rc = %d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_rdma_init(काष्ठा qed_dev *cdev,
			 काष्ठा qed_rdma_start_in_params *params)
अणु
	वापस qed_rdma_start(QED_AFFIN_HWFN(cdev), params);
पूर्ण

अटल व्योम qed_rdma_हटाओ_user(व्योम *rdma_cxt, u16 dpi)
अणु
	काष्ठा qed_hwfn *p_hwfn = (काष्ठा qed_hwfn *)rdma_cxt;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "dpi = %08x\n", dpi);

	spin_lock_bh(&p_hwfn->p_rdma_info->lock);
	qed_bmap_release_id(p_hwfn, &p_hwfn->p_rdma_info->dpi_map, dpi);
	spin_unlock_bh(&p_hwfn->p_rdma_info->lock);
पूर्ण

अटल पूर्णांक qed_roce_ll2_set_mac_filter(काष्ठा qed_dev *cdev,
				       u8 *old_mac_address,
				       u8 *new_mac_address)
अणु
	पूर्णांक rc = 0;

	अगर (old_mac_address)
		qed_llh_हटाओ_mac_filter(cdev, 0, old_mac_address);
	अगर (new_mac_address)
		rc = qed_llh_add_mac_filter(cdev, 0, new_mac_address);

	अगर (rc)
		DP_ERR(cdev,
		       "qed roce ll2 mac filter set: failed to add MAC filter\n");

	वापस rc;
पूर्ण

अटल पूर्णांक qed_iwarp_set_engine_affin(काष्ठा qed_dev *cdev, bool b_reset)
अणु
	क्रमागत qed_eng eng;
	u8 ppfid = 0;
	पूर्णांक rc;

	/* Make sure iwarp cmt mode is enabled beक्रमe setting affinity */
	अगर (!cdev->iwarp_cmt)
		वापस -EINVAL;

	अगर (b_reset)
		eng = QED_BOTH_ENG;
	अन्यथा
		eng = cdev->l2_affin_hपूर्णांक ? QED_ENG1 : QED_ENG0;

	rc = qed_llh_set_ppfid_affinity(cdev, ppfid, eng);
	अगर (rc) अणु
		DP_NOTICE(cdev,
			  "Failed to set the engine affinity of ppfid %d\n",
			  ppfid);
		वापस rc;
	पूर्ण

	DP_VERBOSE(cdev, (QED_MSG_RDMA | QED_MSG_SP),
		   "LLH: Set the engine affinity of non-RoCE packets as %d\n",
		   eng);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qed_rdma_ops qed_rdma_ops_pass = अणु
	.common = &qed_common_ops_pass,
	.fill_dev_info = &qed_fill_rdma_dev_info,
	.rdma_get_rdma_ctx = &qed_rdma_get_rdma_ctx,
	.rdma_init = &qed_rdma_init,
	.rdma_add_user = &qed_rdma_add_user,
	.rdma_हटाओ_user = &qed_rdma_हटाओ_user,
	.rdma_stop = &qed_rdma_stop,
	.rdma_query_port = &qed_rdma_query_port,
	.rdma_query_device = &qed_rdma_query_device,
	.rdma_get_start_sb = &qed_rdma_get_sb_start,
	.rdma_get_rdma_पूर्णांक = &qed_rdma_get_पूर्णांक,
	.rdma_set_rdma_पूर्णांक = &qed_rdma_set_पूर्णांक,
	.rdma_get_min_cnq_msix = &qed_rdma_get_min_cnq_msix,
	.rdma_cnq_prod_update = &qed_rdma_cnq_prod_update,
	.rdma_alloc_pd = &qed_rdma_alloc_pd,
	.rdma_dealloc_pd = &qed_rdma_मुक्त_pd,
	.rdma_alloc_xrcd = &qed_rdma_alloc_xrcd,
	.rdma_dealloc_xrcd = &qed_rdma_मुक्त_xrcd,
	.rdma_create_cq = &qed_rdma_create_cq,
	.rdma_destroy_cq = &qed_rdma_destroy_cq,
	.rdma_create_qp = &qed_rdma_create_qp,
	.rdma_modअगरy_qp = &qed_rdma_modअगरy_qp,
	.rdma_query_qp = &qed_rdma_query_qp,
	.rdma_destroy_qp = &qed_rdma_destroy_qp,
	.rdma_alloc_tid = &qed_rdma_alloc_tid,
	.rdma_मुक्त_tid = &qed_rdma_मुक्त_tid,
	.rdma_रेजिस्टर_tid = &qed_rdma_रेजिस्टर_tid,
	.rdma_deरेजिस्टर_tid = &qed_rdma_deरेजिस्टर_tid,
	.rdma_create_srq = &qed_rdma_create_srq,
	.rdma_modअगरy_srq = &qed_rdma_modअगरy_srq,
	.rdma_destroy_srq = &qed_rdma_destroy_srq,
	.ll2_acquire_connection = &qed_ll2_acquire_connection,
	.ll2_establish_connection = &qed_ll2_establish_connection,
	.ll2_terminate_connection = &qed_ll2_terminate_connection,
	.ll2_release_connection = &qed_ll2_release_connection,
	.ll2_post_rx_buffer = &qed_ll2_post_rx_buffer,
	.ll2_prepare_tx_packet = &qed_ll2_prepare_tx_packet,
	.ll2_set_fragment_of_tx_packet = &qed_ll2_set_fragment_of_tx_packet,
	.ll2_set_mac_filter = &qed_roce_ll2_set_mac_filter,
	.ll2_get_stats = &qed_ll2_get_stats,
	.iwarp_set_engine_affin = &qed_iwarp_set_engine_affin,
	.iwarp_connect = &qed_iwarp_connect,
	.iwarp_create_listen = &qed_iwarp_create_listen,
	.iwarp_destroy_listen = &qed_iwarp_destroy_listen,
	.iwarp_accept = &qed_iwarp_accept,
	.iwarp_reject = &qed_iwarp_reject,
	.iwarp_send_rtr = &qed_iwarp_send_rtr,
पूर्ण;

स्थिर काष्ठा qed_rdma_ops *qed_get_rdma_ops(व्योम)
अणु
	वापस &qed_rdma_ops_pass;
पूर्ण
EXPORT_SYMBOL(qed_get_rdma_ops);
