<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dcbx.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_fcoe.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_int.h"
#समावेश "qed_iscsi.h"
#समावेश "qed_ll2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_ooo.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश "qed_vf.h"
#समावेश "qed_rdma.h"

अटल DEFINE_SPINLOCK(qm_lock);

/******************** Doorbell Recovery *******************/
/* The करोorbell recovery mechanism consists of a list of entries which represent
 * करोorbelling entities (l2 queues, roce sq/rq/cqs, the slowpath spq, etc). Each
 * entity needs to रेजिस्टर with the mechanism and provide the parameters
 * describing it's करोorbell, including a location where last used करोorbell data
 * can be found. The करोorbell execute function will traverse the list and
 * करोorbell all of the रेजिस्टरed entries.
 */
काष्ठा qed_db_recovery_entry अणु
	काष्ठा list_head list_entry;
	व्योम __iomem *db_addr;
	व्योम *db_data;
	क्रमागत qed_db_rec_width db_width;
	क्रमागत qed_db_rec_space db_space;
	u8 hwfn_idx;
पूर्ण;

/* Display a single करोorbell recovery entry */
अटल व्योम qed_db_recovery_dp_entry(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_db_recovery_entry *db_entry,
				     अक्षर *action)
अणु
	DP_VERBOSE(p_hwfn,
		   QED_MSG_SPQ,
		   "(%s: db_entry %p, addr %p, data %p, width %s, %s space, hwfn %d)\n",
		   action,
		   db_entry,
		   db_entry->db_addr,
		   db_entry->db_data,
		   db_entry->db_width == DB_REC_WIDTH_32B ? "32b" : "64b",
		   db_entry->db_space == DB_REC_USER ? "user" : "kernel",
		   db_entry->hwfn_idx);
पूर्ण

/* Doorbell address sanity (address within करोorbell bar range) */
अटल bool qed_db_rec_sanity(काष्ठा qed_dev *cdev,
			      व्योम __iomem *db_addr,
			      क्रमागत qed_db_rec_width db_width,
			      व्योम *db_data)
अणु
	u32 width = (db_width == DB_REC_WIDTH_32B) ? 32 : 64;

	/* Make sure करोorbell address is within the करोorbell bar */
	अगर (db_addr < cdev->करोorbells ||
	    (u8 __iomem *)db_addr + width >
	    (u8 __iomem *)cdev->करोorbells + cdev->db_size) अणु
		WARN(true,
		     "Illegal doorbell address: %p. Legal range for doorbell addresses is [%p..%p]\n",
		     db_addr,
		     cdev->करोorbells,
		     (u8 __iomem *)cdev->करोorbells + cdev->db_size);
		वापस false;
	पूर्ण

	/* ake sure करोorbell data poपूर्णांकer is not null */
	अगर (!db_data) अणु
		WARN(true, "Illegal doorbell data pointer: %p", db_data);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Find hwfn according to the करोorbell address */
अटल काष्ठा qed_hwfn *qed_db_rec_find_hwfn(काष्ठा qed_dev *cdev,
					     व्योम __iomem *db_addr)
अणु
	काष्ठा qed_hwfn *p_hwfn;

	/* In CMT करोorbell bar is split करोwn the middle between engine 0 and enigne 1 */
	अगर (cdev->num_hwfns > 1)
		p_hwfn = db_addr < cdev->hwfns[1].करोorbells ?
		    &cdev->hwfns[0] : &cdev->hwfns[1];
	अन्यथा
		p_hwfn = QED_LEADING_HWFN(cdev);

	वापस p_hwfn;
पूर्ण

/* Add a new entry to the करोorbell recovery mechanism */
पूर्णांक qed_db_recovery_add(काष्ठा qed_dev *cdev,
			व्योम __iomem *db_addr,
			व्योम *db_data,
			क्रमागत qed_db_rec_width db_width,
			क्रमागत qed_db_rec_space db_space)
अणु
	काष्ठा qed_db_recovery_entry *db_entry;
	काष्ठा qed_hwfn *p_hwfn;

	/* Shortcircuit VFs, क्रम now */
	अगर (IS_VF(cdev)) अणु
		DP_VERBOSE(cdev,
			   QED_MSG_IOV, "db recovery - skipping VF doorbell\n");
		वापस 0;
	पूर्ण

	/* Sanitize करोorbell address */
	अगर (!qed_db_rec_sanity(cdev, db_addr, db_width, db_data))
		वापस -EINVAL;

	/* Obtain hwfn from करोorbell address */
	p_hwfn = qed_db_rec_find_hwfn(cdev, db_addr);

	/* Create entry */
	db_entry = kzalloc(माप(*db_entry), GFP_KERNEL);
	अगर (!db_entry) अणु
		DP_NOTICE(cdev, "Failed to allocate a db recovery entry\n");
		वापस -ENOMEM;
	पूर्ण

	/* Populate entry */
	db_entry->db_addr = db_addr;
	db_entry->db_data = db_data;
	db_entry->db_width = db_width;
	db_entry->db_space = db_space;
	db_entry->hwfn_idx = p_hwfn->my_id;

	/* Display */
	qed_db_recovery_dp_entry(p_hwfn, db_entry, "Adding");

	/* Protect the list */
	spin_lock_bh(&p_hwfn->db_recovery_info.lock);
	list_add_tail(&db_entry->list_entry, &p_hwfn->db_recovery_info.list);
	spin_unlock_bh(&p_hwfn->db_recovery_info.lock);

	वापस 0;
पूर्ण

/* Remove an entry from the करोorbell recovery mechanism */
पूर्णांक qed_db_recovery_del(काष्ठा qed_dev *cdev,
			व्योम __iomem *db_addr, व्योम *db_data)
अणु
	काष्ठा qed_db_recovery_entry *db_entry = शून्य;
	काष्ठा qed_hwfn *p_hwfn;
	पूर्णांक rc = -EINVAL;

	/* Shortcircuit VFs, क्रम now */
	अगर (IS_VF(cdev)) अणु
		DP_VERBOSE(cdev,
			   QED_MSG_IOV, "db recovery - skipping VF doorbell\n");
		वापस 0;
	पूर्ण

	/* Obtain hwfn from करोorbell address */
	p_hwfn = qed_db_rec_find_hwfn(cdev, db_addr);

	/* Protect the list */
	spin_lock_bh(&p_hwfn->db_recovery_info.lock);
	list_क्रम_each_entry(db_entry,
			    &p_hwfn->db_recovery_info.list, list_entry) अणु
		/* search according to db_data addr since db_addr is not unique (roce) */
		अगर (db_entry->db_data == db_data) अणु
			qed_db_recovery_dp_entry(p_hwfn, db_entry, "Deleting");
			list_del(&db_entry->list_entry);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&p_hwfn->db_recovery_info.lock);

	अगर (rc == -EINVAL)

		DP_NOTICE(p_hwfn,
			  "Failed to find element in list. Key (db_data addr) was %p. db_addr was %p\n",
			  db_data, db_addr);
	अन्यथा
		kमुक्त(db_entry);

	वापस rc;
पूर्ण

/* Initialize the करोorbell recovery mechanism */
अटल पूर्णांक qed_db_recovery_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	DP_VERBOSE(p_hwfn, QED_MSG_SPQ, "Setting up db recovery\n");

	/* Make sure db_size was set in cdev */
	अगर (!p_hwfn->cdev->db_size) अणु
		DP_ERR(p_hwfn->cdev, "db_size not set\n");
		वापस -EINVAL;
	पूर्ण

	INIT_LIST_HEAD(&p_hwfn->db_recovery_info.list);
	spin_lock_init(&p_hwfn->db_recovery_info.lock);
	p_hwfn->db_recovery_info.db_recovery_counter = 0;

	वापस 0;
पूर्ण

/* Destroy the करोorbell recovery mechanism */
अटल व्योम qed_db_recovery_tearकरोwn(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_db_recovery_entry *db_entry = शून्य;

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ, "Tearing down db recovery\n");
	अगर (!list_empty(&p_hwfn->db_recovery_info.list)) अणु
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SPQ,
			   "Doorbell Recovery teardown found the doorbell recovery list was not empty (Expected in disorderly driver unload (e.g. recovery) otherwise this probably means some flow forgot to db_recovery_del). Prepare to purge doorbell recovery list...\n");
		जबतक (!list_empty(&p_hwfn->db_recovery_info.list)) अणु
			db_entry =
			    list_first_entry(&p_hwfn->db_recovery_info.list,
					     काष्ठा qed_db_recovery_entry,
					     list_entry);
			qed_db_recovery_dp_entry(p_hwfn, db_entry, "Purging");
			list_del(&db_entry->list_entry);
			kमुक्त(db_entry);
		पूर्ण
	पूर्ण
	p_hwfn->db_recovery_info.db_recovery_counter = 0;
पूर्ण

/* Prपूर्णांक the content of the करोorbell recovery mechanism */
व्योम qed_db_recovery_dp(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_db_recovery_entry *db_entry = शून्य;

	DP_NOTICE(p_hwfn,
		  "Displaying doorbell recovery database. Counter was %d\n",
		  p_hwfn->db_recovery_info.db_recovery_counter);

	/* Protect the list */
	spin_lock_bh(&p_hwfn->db_recovery_info.lock);
	list_क्रम_each_entry(db_entry,
			    &p_hwfn->db_recovery_info.list, list_entry) अणु
		qed_db_recovery_dp_entry(p_hwfn, db_entry, "Printing");
	पूर्ण

	spin_unlock_bh(&p_hwfn->db_recovery_info.lock);
पूर्ण

/* Ring the करोorbell of a single करोorbell recovery entry */
अटल व्योम qed_db_recovery_ring(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_db_recovery_entry *db_entry)
अणु
	/* Prपूर्णांक according to width */
	अगर (db_entry->db_width == DB_REC_WIDTH_32B) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
			   "ringing doorbell address %p data %x\n",
			   db_entry->db_addr,
			   *(u32 *)db_entry->db_data);
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
			   "ringing doorbell address %p data %llx\n",
			   db_entry->db_addr,
			   *(u64 *)(db_entry->db_data));
	पूर्ण

	/* Sanity */
	अगर (!qed_db_rec_sanity(p_hwfn->cdev, db_entry->db_addr,
			       db_entry->db_width, db_entry->db_data))
		वापस;

	/* Flush the ग_लिखो combined buffer. Since there are multiple करोorbelling
	 * entities using the same address, अगर we करोn't flush, a transaction
	 * could be lost.
	 */
	wmb();

	/* Ring the करोorbell */
	अगर (db_entry->db_width == DB_REC_WIDTH_32B)
		सूचीECT_REG_WR(db_entry->db_addr,
			      *(u32 *)(db_entry->db_data));
	अन्यथा
		सूचीECT_REG_WR64(db_entry->db_addr,
				*(u64 *)(db_entry->db_data));

	/* Flush the ग_लिखो combined buffer. Next करोorbell may come from a
	 * dअगरferent entity to the same address...
	 */
	wmb();
पूर्ण

/* Traverse the करोorbell recovery entry list and ring all the करोorbells */
व्योम qed_db_recovery_execute(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_db_recovery_entry *db_entry = शून्य;

	DP_NOTICE(p_hwfn, "Executing doorbell recovery. Counter was %d\n",
		  p_hwfn->db_recovery_info.db_recovery_counter);

	/* Track amount of बार recovery was executed */
	p_hwfn->db_recovery_info.db_recovery_counter++;

	/* Protect the list */
	spin_lock_bh(&p_hwfn->db_recovery_info.lock);
	list_क्रम_each_entry(db_entry,
			    &p_hwfn->db_recovery_info.list, list_entry)
		qed_db_recovery_ring(p_hwfn, db_entry);
	spin_unlock_bh(&p_hwfn->db_recovery_info.lock);
पूर्ण

/******************** Doorbell Recovery end ****************/

/********************************** NIG LLH ***********************************/

क्रमागत qed_llh_filter_type अणु
	QED_LLH_FILTER_TYPE_MAC,
	QED_LLH_FILTER_TYPE_PROTOCOL,
पूर्ण;

काष्ठा qed_llh_mac_filter अणु
	u8 addr[ETH_ALEN];
पूर्ण;

काष्ठा qed_llh_protocol_filter अणु
	क्रमागत qed_llh_prot_filter_type_t type;
	u16 source_port_or_eth_type;
	u16 dest_port;
पूर्ण;

जोड़ qed_llh_filter अणु
	काष्ठा qed_llh_mac_filter mac;
	काष्ठा qed_llh_protocol_filter protocol;
पूर्ण;

काष्ठा qed_llh_filter_info अणु
	bool b_enabled;
	u32 ref_cnt;
	क्रमागत qed_llh_filter_type type;
	जोड़ qed_llh_filter filter;
पूर्ण;

काष्ठा qed_llh_info अणु
	/* Number of LLH filters banks */
	u8 num_ppfid;

#घोषणा MAX_NUM_PPFID   8
	u8 ppfid_array[MAX_NUM_PPFID];

	/* Array of filters arrays:
	 * "num_ppfid" elements of filters banks, where each is an array of
	 * "NIG_REG_LLH_FUNC_FILTER_EN_SIZE" filters.
	 */
	काष्ठा qed_llh_filter_info **pp_filters;
पूर्ण;

अटल व्योम qed_llh_मुक्त(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;
	u32 i;

	अगर (p_llh_info) अणु
		अगर (p_llh_info->pp_filters)
			क्रम (i = 0; i < p_llh_info->num_ppfid; i++)
				kमुक्त(p_llh_info->pp_filters[i]);

		kमुक्त(p_llh_info->pp_filters);
	पूर्ण

	kमुक्त(p_llh_info);
	cdev->p_llh_info = शून्य;
पूर्ण

अटल पूर्णांक qed_llh_alloc(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_llh_info *p_llh_info;
	u32 size, i;

	p_llh_info = kzalloc(माप(*p_llh_info), GFP_KERNEL);
	अगर (!p_llh_info)
		वापस -ENOMEM;
	cdev->p_llh_info = p_llh_info;

	क्रम (i = 0; i < MAX_NUM_PPFID; i++) अणु
		अगर (!(cdev->ppfid_biपंचांगap & (0x1 << i)))
			जारी;

		p_llh_info->ppfid_array[p_llh_info->num_ppfid] = i;
		DP_VERBOSE(cdev, QED_MSG_SP, "ppfid_array[%d] = %hhd\n",
			   p_llh_info->num_ppfid, i);
		p_llh_info->num_ppfid++;
	पूर्ण

	size = p_llh_info->num_ppfid * माप(*p_llh_info->pp_filters);
	p_llh_info->pp_filters = kzalloc(size, GFP_KERNEL);
	अगर (!p_llh_info->pp_filters)
		वापस -ENOMEM;

	size = NIG_REG_LLH_FUNC_FILTER_EN_SIZE *
	    माप(**p_llh_info->pp_filters);
	क्रम (i = 0; i < p_llh_info->num_ppfid; i++) अणु
		p_llh_info->pp_filters[i] = kzalloc(size, GFP_KERNEL);
		अगर (!p_llh_info->pp_filters[i])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_llh_shaकरोw_sanity(काष्ठा qed_dev *cdev,
				 u8 ppfid, u8 filter_idx, स्थिर अक्षर *action)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;

	अगर (ppfid >= p_llh_info->num_ppfid) अणु
		DP_NOTICE(cdev,
			  "LLH shadow [%s]: using ppfid %d while only %d ppfids are available\n",
			  action, ppfid, p_llh_info->num_ppfid);
		वापस -EINVAL;
	पूर्ण

	अगर (filter_idx >= NIG_REG_LLH_FUNC_FILTER_EN_SIZE) अणु
		DP_NOTICE(cdev,
			  "LLH shadow [%s]: using filter_idx %d while only %d filters are available\n",
			  action, filter_idx, NIG_REG_LLH_FUNC_FILTER_EN_SIZE);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा QED_LLH_INVALID_FILTER_IDX      0xff

अटल पूर्णांक
qed_llh_shaकरोw_search_filter(काष्ठा qed_dev *cdev,
			     u8 ppfid,
			     जोड़ qed_llh_filter *p_filter, u8 *p_filter_idx)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;
	काष्ठा qed_llh_filter_info *p_filters;
	पूर्णांक rc;
	u8 i;

	rc = qed_llh_shaकरोw_sanity(cdev, ppfid, 0, "search");
	अगर (rc)
		वापस rc;

	*p_filter_idx = QED_LLH_INVALID_FILTER_IDX;

	p_filters = p_llh_info->pp_filters[ppfid];
	क्रम (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) अणु
		अगर (!स_भेद(p_filter, &p_filters[i].filter,
			    माप(*p_filter))) अणु
			*p_filter_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_llh_shaकरोw_get_मुक्त_idx(काष्ठा qed_dev *cdev, u8 ppfid, u8 *p_filter_idx)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;
	काष्ठा qed_llh_filter_info *p_filters;
	पूर्णांक rc;
	u8 i;

	rc = qed_llh_shaकरोw_sanity(cdev, ppfid, 0, "get_free_idx");
	अगर (rc)
		वापस rc;

	*p_filter_idx = QED_LLH_INVALID_FILTER_IDX;

	p_filters = p_llh_info->pp_filters[ppfid];
	क्रम (i = 0; i < NIG_REG_LLH_FUNC_FILTER_EN_SIZE; i++) अणु
		अगर (!p_filters[i].b_enabled) अणु
			*p_filter_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__qed_llh_shaकरोw_add_filter(काष्ठा qed_dev *cdev,
			    u8 ppfid,
			    u8 filter_idx,
			    क्रमागत qed_llh_filter_type type,
			    जोड़ qed_llh_filter *p_filter, u32 *p_ref_cnt)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;
	काष्ठा qed_llh_filter_info *p_filters;
	पूर्णांक rc;

	rc = qed_llh_shaकरोw_sanity(cdev, ppfid, filter_idx, "add");
	अगर (rc)
		वापस rc;

	p_filters = p_llh_info->pp_filters[ppfid];
	अगर (!p_filters[filter_idx].ref_cnt) अणु
		p_filters[filter_idx].b_enabled = true;
		p_filters[filter_idx].type = type;
		स_नकल(&p_filters[filter_idx].filter, p_filter,
		       माप(p_filters[filter_idx].filter));
	पूर्ण

	*p_ref_cnt = ++p_filters[filter_idx].ref_cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_llh_shaकरोw_add_filter(काष्ठा qed_dev *cdev,
			  u8 ppfid,
			  क्रमागत qed_llh_filter_type type,
			  जोड़ qed_llh_filter *p_filter,
			  u8 *p_filter_idx, u32 *p_ref_cnt)
अणु
	पूर्णांक rc;

	/* Check अगर the same filter alपढ़ोy exist */
	rc = qed_llh_shaकरोw_search_filter(cdev, ppfid, p_filter, p_filter_idx);
	अगर (rc)
		वापस rc;

	/* Find a new entry in हाल of a new filter */
	अगर (*p_filter_idx == QED_LLH_INVALID_FILTER_IDX) अणु
		rc = qed_llh_shaकरोw_get_मुक्त_idx(cdev, ppfid, p_filter_idx);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* No मुक्त entry was found */
	अगर (*p_filter_idx == QED_LLH_INVALID_FILTER_IDX) अणु
		DP_NOTICE(cdev,
			  "Failed to find an empty LLH filter to utilize [ppfid %d]\n",
			  ppfid);
		वापस -EINVAL;
	पूर्ण

	वापस __qed_llh_shaकरोw_add_filter(cdev, ppfid, *p_filter_idx, type,
					   p_filter, p_ref_cnt);
पूर्ण

अटल पूर्णांक
__qed_llh_shaकरोw_हटाओ_filter(काष्ठा qed_dev *cdev,
			       u8 ppfid, u8 filter_idx, u32 *p_ref_cnt)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;
	काष्ठा qed_llh_filter_info *p_filters;
	पूर्णांक rc;

	rc = qed_llh_shaकरोw_sanity(cdev, ppfid, filter_idx, "remove");
	अगर (rc)
		वापस rc;

	p_filters = p_llh_info->pp_filters[ppfid];
	अगर (!p_filters[filter_idx].ref_cnt) अणु
		DP_NOTICE(cdev,
			  "LLH shadow: trying to remove a filter with ref_cnt=0\n");
		वापस -EINVAL;
	पूर्ण

	*p_ref_cnt = --p_filters[filter_idx].ref_cnt;
	अगर (!p_filters[filter_idx].ref_cnt)
		स_रखो(&p_filters[filter_idx],
		       0, माप(p_filters[filter_idx]));

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_llh_shaकरोw_हटाओ_filter(काष्ठा qed_dev *cdev,
			     u8 ppfid,
			     जोड़ qed_llh_filter *p_filter,
			     u8 *p_filter_idx, u32 *p_ref_cnt)
अणु
	पूर्णांक rc;

	rc = qed_llh_shaकरोw_search_filter(cdev, ppfid, p_filter, p_filter_idx);
	अगर (rc)
		वापस rc;

	/* No matching filter was found */
	अगर (*p_filter_idx == QED_LLH_INVALID_FILTER_IDX) अणु
		DP_NOTICE(cdev, "Failed to find a filter in the LLH shadow\n");
		वापस -EINVAL;
	पूर्ण

	वापस __qed_llh_shaकरोw_हटाओ_filter(cdev, ppfid, *p_filter_idx,
					      p_ref_cnt);
पूर्ण

अटल पूर्णांक qed_llh_असल_ppfid(काष्ठा qed_dev *cdev, u8 ppfid, u8 *p_असल_ppfid)
अणु
	काष्ठा qed_llh_info *p_llh_info = cdev->p_llh_info;

	अगर (ppfid >= p_llh_info->num_ppfid) अणु
		DP_NOTICE(cdev,
			  "ppfid %d is not valid, available indices are 0..%hhd\n",
			  ppfid, p_llh_info->num_ppfid - 1);
		*p_असल_ppfid = 0;
		वापस -EINVAL;
	पूर्ण

	*p_असल_ppfid = p_llh_info->ppfid_array[ppfid];

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_llh_set_engine_affin(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	क्रमागत qed_eng eng;
	u8 ppfid;
	पूर्णांक rc;

	rc = qed_mcp_get_engine_config(p_hwfn, p_ptt);
	अगर (rc != 0 && rc != -EOPNOTSUPP) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to get the engine affinity configuration\n");
		वापस rc;
	पूर्ण

	/* RoCE PF is bound to a single engine */
	अगर (QED_IS_ROCE_PERSONALITY(p_hwfn)) अणु
		eng = cdev->fir_affin ? QED_ENG1 : QED_ENG0;
		rc = qed_llh_set_roce_affinity(cdev, eng);
		अगर (rc) अणु
			DP_NOTICE(cdev,
				  "Failed to set the RoCE engine affinity\n");
			वापस rc;
		पूर्ण

		DP_VERBOSE(cdev,
			   QED_MSG_SP,
			   "LLH: Set the engine affinity of RoCE packets as %d\n",
			   eng);
	पूर्ण

	/* Storage PF is bound to a single engine जबतक L2 PF uses both */
	अगर (QED_IS_FCOE_PERSONALITY(p_hwfn) || QED_IS_ISCSI_PERSONALITY(p_hwfn))
		eng = cdev->fir_affin ? QED_ENG1 : QED_ENG0;
	अन्यथा			/* L2_PERSONALITY */
		eng = QED_BOTH_ENG;

	क्रम (ppfid = 0; ppfid < cdev->p_llh_info->num_ppfid; ppfid++) अणु
		rc = qed_llh_set_ppfid_affinity(cdev, ppfid, eng);
		अगर (rc) अणु
			DP_NOTICE(cdev,
				  "Failed to set the engine affinity of ppfid %d\n",
				  ppfid);
			वापस rc;
		पूर्ण
	पूर्ण

	DP_VERBOSE(cdev, QED_MSG_SP,
		   "LLH: Set the engine affinity of non-RoCE packets as %d\n",
		   eng);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_llh_hw_init_pf(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u8 ppfid, असल_ppfid;
	पूर्णांक rc;

	क्रम (ppfid = 0; ppfid < cdev->p_llh_info->num_ppfid; ppfid++) अणु
		u32 addr;

		rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
		अगर (rc)
			वापस rc;

		addr = NIG_REG_LLH_PPFID2PFID_TBL_0 + असल_ppfid * 0x4;
		qed_wr(p_hwfn, p_ptt, addr, p_hwfn->rel_pf_id);
	पूर्ण

	अगर (test_bit(QED_MF_LLH_MAC_CLSS, &cdev->mf_bits) &&
	    !QED_IS_FCOE_PERSONALITY(p_hwfn)) अणु
		rc = qed_llh_add_mac_filter(cdev, 0,
					    p_hwfn->hw_info.hw_mac_addr);
		अगर (rc)
			DP_NOTICE(cdev,
				  "Failed to add an LLH filter with the primary MAC\n");
	पूर्ण

	अगर (QED_IS_CMT(cdev)) अणु
		rc = qed_llh_set_engine_affin(p_hwfn, p_ptt);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

u8 qed_llh_get_num_ppfid(काष्ठा qed_dev *cdev)
अणु
	वापस cdev->p_llh_info->num_ppfid;
पूर्ण

#घोषणा NIG_REG_PPF_TO_ENGINE_SEL_ROCE_MASK             0x3
#घोषणा NIG_REG_PPF_TO_ENGINE_SEL_ROCE_SHIFT            0
#घोषणा NIG_REG_PPF_TO_ENGINE_SEL_NON_ROCE_MASK         0x3
#घोषणा NIG_REG_PPF_TO_ENGINE_SEL_NON_ROCE_SHIFT        2

पूर्णांक qed_llh_set_ppfid_affinity(काष्ठा qed_dev *cdev, u8 ppfid, क्रमागत qed_eng eng)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u32 addr, val, eng_sel;
	u8 असल_ppfid;
	पूर्णांक rc = 0;

	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (!QED_IS_CMT(cdev))
		जाओ out;

	rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
	अगर (rc)
		जाओ out;

	चयन (eng) अणु
	हाल QED_ENG0:
		eng_sel = 0;
		अवरोध;
	हाल QED_ENG1:
		eng_sel = 1;
		अवरोध;
	हाल QED_BOTH_ENG:
		eng_sel = 2;
		अवरोध;
	शेष:
		DP_NOTICE(cdev, "Invalid affinity value for ppfid [%d]\n", eng);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	addr = NIG_REG_PPF_TO_ENGINE_SEL + असल_ppfid * 0x4;
	val = qed_rd(p_hwfn, p_ptt, addr);
	SET_FIELD(val, NIG_REG_PPF_TO_ENGINE_SEL_NON_ROCE, eng_sel);
	qed_wr(p_hwfn, p_ptt, addr, val);

	/* The iWARP affinity is set as the affinity of ppfid 0 */
	अगर (!ppfid && QED_IS_IWARP_PERSONALITY(p_hwfn))
		cdev->iwarp_affin = (eng == QED_ENG1) ? 1 : 0;
out:
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

पूर्णांक qed_llh_set_roce_affinity(काष्ठा qed_dev *cdev, क्रमागत qed_eng eng)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u32 addr, val, eng_sel;
	u8 ppfid, असल_ppfid;
	पूर्णांक rc = 0;

	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (!QED_IS_CMT(cdev))
		जाओ out;

	चयन (eng) अणु
	हाल QED_ENG0:
		eng_sel = 0;
		अवरोध;
	हाल QED_ENG1:
		eng_sel = 1;
		अवरोध;
	हाल QED_BOTH_ENG:
		eng_sel = 2;
		qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_ENG_CLS_ROCE_QP_SEL,
		       0xf);  /* QP bit 15 */
		अवरोध;
	शेष:
		DP_NOTICE(cdev, "Invalid affinity value for RoCE [%d]\n", eng);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (ppfid = 0; ppfid < cdev->p_llh_info->num_ppfid; ppfid++) अणु
		rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
		अगर (rc)
			जाओ out;

		addr = NIG_REG_PPF_TO_ENGINE_SEL + असल_ppfid * 0x4;
		val = qed_rd(p_hwfn, p_ptt, addr);
		SET_FIELD(val, NIG_REG_PPF_TO_ENGINE_SEL_ROCE, eng_sel);
		qed_wr(p_hwfn, p_ptt, addr, val);
	पूर्ण
out:
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

काष्ठा qed_llh_filter_details अणु
	u64 value;
	u32 mode;
	u32 protocol_type;
	u32 hdr_sel;
	u32 enable;
पूर्ण;

अटल पूर्णांक
qed_llh_access_filter(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      u8 असल_ppfid,
		      u8 filter_idx,
		      काष्ठा qed_llh_filter_details *p_details)
अणु
	काष्ठा qed_dmae_params params = अणु0पूर्ण;
	u32 addr;
	u8 pfid;
	पूर्णांक rc;

	/* The NIG/LLH रेजिस्टरs that are accessed in this function have only 16
	 * rows which are exposed to a PF. I.e. only the 16 filters of its
	 * शेष ppfid. Accessing filters of other ppfids requires pretending
	 * to another PFs.
	 * The calculation of PPFID->PFID in AH is based on the relative index
	 * of a PF on its port.
	 * For BB the pfid is actually the असल_ppfid.
	 */
	अगर (QED_IS_BB(p_hwfn->cdev))
		pfid = असल_ppfid;
	अन्यथा
		pfid = असल_ppfid * p_hwfn->cdev->num_ports_in_engine +
		    MFW_PORT(p_hwfn);

	/* Filter enable - should be करोne first when removing a filter */
	अगर (!p_details->enable) अणु
		qed_fid_pretend(p_hwfn, p_ptt,
				pfid << PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);

		addr = NIG_REG_LLH_FUNC_FILTER_EN + filter_idx * 0x4;
		qed_wr(p_hwfn, p_ptt, addr, p_details->enable);

		qed_fid_pretend(p_hwfn, p_ptt,
				p_hwfn->rel_pf_id <<
				PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);
	पूर्ण

	/* Filter value */
	addr = NIG_REG_LLH_FUNC_FILTER_VALUE + 2 * filter_idx * 0x4;

	SET_FIELD(params.flags, QED_DMAE_PARAMS_DST_PF_VALID, 0x1);
	params.dst_pfid = pfid;
	rc = qed_dmae_host2grc(p_hwfn,
			       p_ptt,
			       (u64)(uपूर्णांकptr_t)&p_details->value,
			       addr, 2 /* size_in_dwords */,
			       &params);
	अगर (rc)
		वापस rc;

	qed_fid_pretend(p_hwfn, p_ptt,
			pfid << PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);

	/* Filter mode */
	addr = NIG_REG_LLH_FUNC_FILTER_MODE + filter_idx * 0x4;
	qed_wr(p_hwfn, p_ptt, addr, p_details->mode);

	/* Filter protocol type */
	addr = NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE + filter_idx * 0x4;
	qed_wr(p_hwfn, p_ptt, addr, p_details->protocol_type);

	/* Filter header select */
	addr = NIG_REG_LLH_FUNC_FILTER_HDR_SEL + filter_idx * 0x4;
	qed_wr(p_hwfn, p_ptt, addr, p_details->hdr_sel);

	/* Filter enable - should be करोne last when adding a filter */
	अगर (p_details->enable) अणु
		addr = NIG_REG_LLH_FUNC_FILTER_EN + filter_idx * 0x4;
		qed_wr(p_hwfn, p_ptt, addr, p_details->enable);
	पूर्ण

	qed_fid_pretend(p_hwfn, p_ptt,
			p_hwfn->rel_pf_id <<
			PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_llh_add_filter(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt,
		   u8 असल_ppfid,
		   u8 filter_idx, u8 filter_prot_type, u32 high, u32 low)
अणु
	काष्ठा qed_llh_filter_details filter_details;

	filter_details.enable = 1;
	filter_details.value = ((u64)high << 32) | low;
	filter_details.hdr_sel = 0;
	filter_details.protocol_type = filter_prot_type;
	/* Mode: 0: MAC-address classअगरication 1: protocol classअगरication */
	filter_details.mode = filter_prot_type ? 1 : 0;

	वापस qed_llh_access_filter(p_hwfn, p_ptt, असल_ppfid, filter_idx,
				     &filter_details);
पूर्ण

अटल पूर्णांक
qed_llh_हटाओ_filter(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, u8 असल_ppfid, u8 filter_idx)
अणु
	काष्ठा qed_llh_filter_details filter_details = अणु0पूर्ण;

	वापस qed_llh_access_filter(p_hwfn, p_ptt, असल_ppfid, filter_idx,
				     &filter_details);
पूर्ण

पूर्णांक qed_llh_add_mac_filter(काष्ठा qed_dev *cdev,
			   u8 ppfid, u8 mac_addr[ETH_ALEN])
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	जोड़ qed_llh_filter filter = अणुपूर्ण;
	u8 filter_idx, असल_ppfid = 0;
	u32 high, low, ref_cnt;
	पूर्णांक rc = 0;

	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (!test_bit(QED_MF_LLH_MAC_CLSS, &cdev->mf_bits))
		जाओ out;

	स_नकल(filter.mac.addr, mac_addr, ETH_ALEN);
	rc = qed_llh_shaकरोw_add_filter(cdev, ppfid,
				       QED_LLH_FILTER_TYPE_MAC,
				       &filter, &filter_idx, &ref_cnt);
	अगर (rc)
		जाओ err;

	/* Configure the LLH only in हाल of a new the filter */
	अगर (ref_cnt == 1) अणु
		rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
		अगर (rc)
			जाओ err;

		high = mac_addr[1] | (mac_addr[0] << 8);
		low = mac_addr[5] | (mac_addr[4] << 8) | (mac_addr[3] << 16) |
		      (mac_addr[2] << 24);
		rc = qed_llh_add_filter(p_hwfn, p_ptt, असल_ppfid, filter_idx,
					0, high, low);
		अगर (rc)
			जाओ err;
	पूर्ण

	DP_VERBOSE(cdev,
		   QED_MSG_SP,
		   "LLH: Added MAC filter [%pM] to ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   mac_addr, ppfid, असल_ppfid, filter_idx, ref_cnt);

	जाओ out;

err:	DP_NOTICE(cdev,
		  "LLH: Failed to add MAC filter [%pM] to ppfid %hhd\n",
		  mac_addr, ppfid);
out:
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_llh_protocol_filter_stringअगरy(काष्ठा qed_dev *cdev,
				  क्रमागत qed_llh_prot_filter_type_t type,
				  u16 source_port_or_eth_type,
				  u16 dest_port, u8 *str, माप_प्रकार str_len)
अणु
	चयन (type) अणु
	हाल QED_LLH_FILTER_ETHERTYPE:
		snम_लिखो(str, str_len, "Ethertype 0x%04x",
			 source_port_or_eth_type);
		अवरोध;
	हाल QED_LLH_FILTER_TCP_SRC_PORT:
		snम_लिखो(str, str_len, "TCP src port 0x%04x",
			 source_port_or_eth_type);
		अवरोध;
	हाल QED_LLH_FILTER_UDP_SRC_PORT:
		snम_लिखो(str, str_len, "UDP src port 0x%04x",
			 source_port_or_eth_type);
		अवरोध;
	हाल QED_LLH_FILTER_TCP_DEST_PORT:
		snम_लिखो(str, str_len, "TCP dst port 0x%04x", dest_port);
		अवरोध;
	हाल QED_LLH_FILTER_UDP_DEST_PORT:
		snम_लिखो(str, str_len, "UDP dst port 0x%04x", dest_port);
		अवरोध;
	हाल QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
		snम_लिखो(str, str_len, "TCP src/dst ports 0x%04x/0x%04x",
			 source_port_or_eth_type, dest_port);
		अवरोध;
	हाल QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		snम_लिखो(str, str_len, "UDP src/dst ports 0x%04x/0x%04x",
			 source_port_or_eth_type, dest_port);
		अवरोध;
	शेष:
		DP_NOTICE(cdev,
			  "Non valid LLH protocol filter type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_llh_protocol_filter_to_hilo(काष्ठा qed_dev *cdev,
				क्रमागत qed_llh_prot_filter_type_t type,
				u16 source_port_or_eth_type,
				u16 dest_port, u32 *p_high, u32 *p_low)
अणु
	*p_high = 0;
	*p_low = 0;

	चयन (type) अणु
	हाल QED_LLH_FILTER_ETHERTYPE:
		*p_high = source_port_or_eth_type;
		अवरोध;
	हाल QED_LLH_FILTER_TCP_SRC_PORT:
	हाल QED_LLH_FILTER_UDP_SRC_PORT:
		*p_low = source_port_or_eth_type << 16;
		अवरोध;
	हाल QED_LLH_FILTER_TCP_DEST_PORT:
	हाल QED_LLH_FILTER_UDP_DEST_PORT:
		*p_low = dest_port;
		अवरोध;
	हाल QED_LLH_FILTER_TCP_SRC_AND_DEST_PORT:
	हाल QED_LLH_FILTER_UDP_SRC_AND_DEST_PORT:
		*p_low = (source_port_or_eth_type << 16) | dest_port;
		अवरोध;
	शेष:
		DP_NOTICE(cdev,
			  "Non valid LLH protocol filter type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
qed_llh_add_protocol_filter(काष्ठा qed_dev *cdev,
			    u8 ppfid,
			    क्रमागत qed_llh_prot_filter_type_t type,
			    u16 source_port_or_eth_type, u16 dest_port)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u8 filter_idx, असल_ppfid, str[32], type_biपंचांगap;
	जोड़ qed_llh_filter filter = अणुपूर्ण;
	u32 high, low, ref_cnt;
	पूर्णांक rc = 0;

	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (!test_bit(QED_MF_LLH_PROTO_CLSS, &cdev->mf_bits))
		जाओ out;

	rc = qed_llh_protocol_filter_stringअगरy(cdev, type,
					       source_port_or_eth_type,
					       dest_port, str, माप(str));
	अगर (rc)
		जाओ err;

	filter.protocol.type = type;
	filter.protocol.source_port_or_eth_type = source_port_or_eth_type;
	filter.protocol.dest_port = dest_port;
	rc = qed_llh_shaकरोw_add_filter(cdev,
				       ppfid,
				       QED_LLH_FILTER_TYPE_PROTOCOL,
				       &filter, &filter_idx, &ref_cnt);
	अगर (rc)
		जाओ err;

	rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
	अगर (rc)
		जाओ err;

	/* Configure the LLH only in हाल of a new the filter */
	अगर (ref_cnt == 1) अणु
		rc = qed_llh_protocol_filter_to_hilo(cdev, type,
						     source_port_or_eth_type,
						     dest_port, &high, &low);
		अगर (rc)
			जाओ err;

		type_biपंचांगap = 0x1 << type;
		rc = qed_llh_add_filter(p_hwfn, p_ptt, असल_ppfid,
					filter_idx, type_biपंचांगap, high, low);
		अगर (rc)
			जाओ err;
	पूर्ण

	DP_VERBOSE(cdev,
		   QED_MSG_SP,
		   "LLH: Added protocol filter [%s] to ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   str, ppfid, असल_ppfid, filter_idx, ref_cnt);

	जाओ out;

err:	DP_NOTICE(p_hwfn,
		  "LLH: Failed to add protocol filter [%s] to ppfid %hhd\n",
		  str, ppfid);
out:
	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

व्योम qed_llh_हटाओ_mac_filter(काष्ठा qed_dev *cdev,
			       u8 ppfid, u8 mac_addr[ETH_ALEN])
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	जोड़ qed_llh_filter filter = अणुपूर्ण;
	u8 filter_idx, असल_ppfid;
	पूर्णांक rc = 0;
	u32 ref_cnt;

	अगर (!p_ptt)
		वापस;

	अगर (!test_bit(QED_MF_LLH_MAC_CLSS, &cdev->mf_bits))
		जाओ out;

	ether_addr_copy(filter.mac.addr, mac_addr);
	rc = qed_llh_shaकरोw_हटाओ_filter(cdev, ppfid, &filter, &filter_idx,
					  &ref_cnt);
	अगर (rc)
		जाओ err;

	rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
	अगर (rc)
		जाओ err;

	/* Remove from the LLH in हाल the filter is not in use */
	अगर (!ref_cnt) अणु
		rc = qed_llh_हटाओ_filter(p_hwfn, p_ptt, असल_ppfid,
					   filter_idx);
		अगर (rc)
			जाओ err;
	पूर्ण

	DP_VERBOSE(cdev,
		   QED_MSG_SP,
		   "LLH: Removed MAC filter [%pM] from ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   mac_addr, ppfid, असल_ppfid, filter_idx, ref_cnt);

	जाओ out;

err:	DP_NOTICE(cdev,
		  "LLH: Failed to remove MAC filter [%pM] from ppfid %hhd\n",
		  mac_addr, ppfid);
out:
	qed_ptt_release(p_hwfn, p_ptt);
पूर्ण

व्योम qed_llh_हटाओ_protocol_filter(काष्ठा qed_dev *cdev,
				    u8 ppfid,
				    क्रमागत qed_llh_prot_filter_type_t type,
				    u16 source_port_or_eth_type, u16 dest_port)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u8 filter_idx, असल_ppfid, str[32];
	जोड़ qed_llh_filter filter = अणुपूर्ण;
	पूर्णांक rc = 0;
	u32 ref_cnt;

	अगर (!p_ptt)
		वापस;

	अगर (!test_bit(QED_MF_LLH_PROTO_CLSS, &cdev->mf_bits))
		जाओ out;

	rc = qed_llh_protocol_filter_stringअगरy(cdev, type,
					       source_port_or_eth_type,
					       dest_port, str, माप(str));
	अगर (rc)
		जाओ err;

	filter.protocol.type = type;
	filter.protocol.source_port_or_eth_type = source_port_or_eth_type;
	filter.protocol.dest_port = dest_port;
	rc = qed_llh_shaकरोw_हटाओ_filter(cdev, ppfid, &filter, &filter_idx,
					  &ref_cnt);
	अगर (rc)
		जाओ err;

	rc = qed_llh_असल_ppfid(cdev, ppfid, &असल_ppfid);
	अगर (rc)
		जाओ err;

	/* Remove from the LLH in हाल the filter is not in use */
	अगर (!ref_cnt) अणु
		rc = qed_llh_हटाओ_filter(p_hwfn, p_ptt, असल_ppfid,
					   filter_idx);
		अगर (rc)
			जाओ err;
	पूर्ण

	DP_VERBOSE(cdev,
		   QED_MSG_SP,
		   "LLH: Removed protocol filter [%s] from ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   str, ppfid, असल_ppfid, filter_idx, ref_cnt);

	जाओ out;

err:	DP_NOTICE(cdev,
		  "LLH: Failed to remove protocol filter [%s] from ppfid %hhd\n",
		  str, ppfid);
out:
	qed_ptt_release(p_hwfn, p_ptt);
पूर्ण

/******************************* NIG LLH - End ********************************/

#घोषणा QED_MIN_DPIS            (4)
#घोषणा QED_MIN_PWM_REGION      (QED_WID_SIZE * QED_MIN_DPIS)

अटल u32 qed_hw_bar_size(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt, क्रमागत BAR_ID bar_id)
अणु
	u32 bar_reg = (bar_id == BAR_ID_0 ?
		       PGLUE_B_REG_PF_BAR0_SIZE : PGLUE_B_REG_PF_BAR1_SIZE);
	u32 val;

	अगर (IS_VF(p_hwfn->cdev))
		वापस qed_vf_hw_bar_size(p_hwfn, bar_id);

	val = qed_rd(p_hwfn, p_ptt, bar_reg);
	अगर (val)
		वापस 1 << (val + 15);

	/* Old MFW initialized above रेजिस्टरed only conditionally */
	अगर (p_hwfn->cdev->num_hwfns > 1) अणु
		DP_INFO(p_hwfn,
			"BAR size not configured. Assuming BAR size of 256kB for GRC and 512kB for DB\n");
			वापस BAR_ID_0 ? 256 * 1024 : 512 * 1024;
	पूर्ण अन्यथा अणु
		DP_INFO(p_hwfn,
			"BAR size not configured. Assuming BAR size of 512kB for GRC and 512kB for DB\n");
			वापस 512 * 1024;
	पूर्ण
पूर्ण

व्योम qed_init_dp(काष्ठा qed_dev *cdev, u32 dp_module, u8 dp_level)
अणु
	u32 i;

	cdev->dp_level = dp_level;
	cdev->dp_module = dp_module;
	क्रम (i = 0; i < MAX_HWFNS_PER_DEVICE; i++) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		p_hwfn->dp_level = dp_level;
		p_hwfn->dp_module = dp_module;
	पूर्ण
पूर्ण

व्योम qed_init_काष्ठा(काष्ठा qed_dev *cdev)
अणु
	u8 i;

	क्रम (i = 0; i < MAX_HWFNS_PER_DEVICE; i++) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		p_hwfn->cdev = cdev;
		p_hwfn->my_id = i;
		p_hwfn->b_active = false;

		mutex_init(&p_hwfn->dmae_info.mutex);
	पूर्ण

	/* hwfn 0 is always active */
	cdev->hwfns[0].b_active = true;

	/* set the शेष cache alignment to 128 */
	cdev->cache_shअगरt = 7;
पूर्ण

अटल व्योम qed_qm_info_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	kमुक्त(qm_info->qm_pq_params);
	qm_info->qm_pq_params = शून्य;
	kमुक्त(qm_info->qm_vport_params);
	qm_info->qm_vport_params = शून्य;
	kमुक्त(qm_info->qm_port_params);
	qm_info->qm_port_params = शून्य;
	kमुक्त(qm_info->wfq_data);
	qm_info->wfq_data = शून्य;
पूर्ण

अटल व्योम qed_dbg_user_data_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	kमुक्त(p_hwfn->dbg_user_info);
	p_hwfn->dbg_user_info = शून्य;
पूर्ण

व्योम qed_resc_मुक्त(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_rdma_info *rdma_info;
	काष्ठा qed_hwfn *p_hwfn;
	पूर्णांक i;

	अगर (IS_VF(cdev)) अणु
		क्रम_each_hwfn(cdev, i)
			qed_l2_मुक्त(&cdev->hwfns[i]);
		वापस;
	पूर्ण

	kमुक्त(cdev->fw_data);
	cdev->fw_data = शून्य;

	kमुक्त(cdev->reset_stats);
	cdev->reset_stats = शून्य;

	qed_llh_मुक्त(cdev);

	क्रम_each_hwfn(cdev, i) अणु
		p_hwfn = cdev->hwfns + i;
		rdma_info = p_hwfn->p_rdma_info;

		qed_cxt_mngr_मुक्त(p_hwfn);
		qed_qm_info_मुक्त(p_hwfn);
		qed_spq_मुक्त(p_hwfn);
		qed_eq_मुक्त(p_hwfn);
		qed_consq_मुक्त(p_hwfn);
		qed_पूर्णांक_मुक्त(p_hwfn);
#अगर_घोषित CONFIG_QED_LL2
		qed_ll2_मुक्त(p_hwfn);
#पूर्ण_अगर
		अगर (p_hwfn->hw_info.personality == QED_PCI_FCOE)
			qed_fcoe_मुक्त(p_hwfn);

		अगर (p_hwfn->hw_info.personality == QED_PCI_ISCSI) अणु
			qed_iscsi_मुक्त(p_hwfn);
			qed_ooo_मुक्त(p_hwfn);
		पूर्ण

		अगर (QED_IS_RDMA_PERSONALITY(p_hwfn) && rdma_info) अणु
			qed_spq_unरेजिस्टर_async_cb(p_hwfn, rdma_info->proto);
			qed_rdma_info_मुक्त(p_hwfn);
		पूर्ण

		qed_iov_मुक्त(p_hwfn);
		qed_l2_मुक्त(p_hwfn);
		qed_dmae_info_मुक्त(p_hwfn);
		qed_dcbx_info_मुक्त(p_hwfn);
		qed_dbg_user_data_मुक्त(p_hwfn);
		qed_fw_overlay_mem_मुक्त(p_hwfn, p_hwfn->fw_overlay_mem);

		/* Destroy करोorbell recovery mechanism */
		qed_db_recovery_tearकरोwn(p_hwfn);
	पूर्ण
पूर्ण

/******************** QM initialization *******************/
#घोषणा ACTIVE_TCS_BMAP 0x9f
#घोषणा ACTIVE_TCS_BMAP_4PORT_K2 0xf

/* determines the physical queue flags क्रम a given PF. */
अटल u32 qed_get_pq_flags(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 flags;

	/* common flags */
	flags = PQ_FLAGS_LB;

	/* feature flags */
	अगर (IS_QED_SRIOV(p_hwfn->cdev))
		flags |= PQ_FLAGS_VFS;

	/* protocol flags */
	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_ETH:
		flags |= PQ_FLAGS_MCOS;
		अवरोध;
	हाल QED_PCI_FCOE:
		flags |= PQ_FLAGS_OFLD;
		अवरोध;
	हाल QED_PCI_ISCSI:
		flags |= PQ_FLAGS_ACK | PQ_FLAGS_OOO | PQ_FLAGS_OFLD;
		अवरोध;
	हाल QED_PCI_ETH_ROCE:
		flags |= PQ_FLAGS_MCOS | PQ_FLAGS_OFLD | PQ_FLAGS_LLT;
		अगर (IS_QED_MULTI_TC_ROCE(p_hwfn))
			flags |= PQ_FLAGS_MTC;
		अवरोध;
	हाल QED_PCI_ETH_IWARP:
		flags |= PQ_FLAGS_MCOS | PQ_FLAGS_ACK | PQ_FLAGS_OOO |
		    PQ_FLAGS_OFLD;
		अवरोध;
	शेष:
		DP_ERR(p_hwfn,
		       "unknown personality %d\n", p_hwfn->hw_info.personality);
		वापस 0;
	पूर्ण

	वापस flags;
पूर्ण

/* Getters क्रम resource amounts necessary क्रम qm initialization */
अटल u8 qed_init_qm_get_num_tcs(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस p_hwfn->hw_info.num_hw_tc;
पूर्ण

अटल u16 qed_init_qm_get_num_vfs(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस IS_QED_SRIOV(p_hwfn->cdev) ?
	       p_hwfn->cdev->p_iov_info->total_vfs : 0;
पूर्ण

अटल u8 qed_init_qm_get_num_mtc_tcs(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 pq_flags = qed_get_pq_flags(p_hwfn);

	अगर (!(PQ_FLAGS_MTC & pq_flags))
		वापस 1;

	वापस qed_init_qm_get_num_tcs(p_hwfn);
पूर्ण

#घोषणा NUM_DEFAULT_RLS 1

अटल u16 qed_init_qm_get_num_pf_rls(काष्ठा qed_hwfn *p_hwfn)
अणु
	u16 num_pf_rls, num_vfs = qed_init_qm_get_num_vfs(p_hwfn);

	/* num RLs can't exceed resource amount of rls or vports */
	num_pf_rls = (u16) min_t(u32, RESC_NUM(p_hwfn, QED_RL),
				 RESC_NUM(p_hwfn, QED_VPORT));

	/* Make sure after we reserve there's something left */
	अगर (num_pf_rls < num_vfs + NUM_DEFAULT_RLS)
		वापस 0;

	/* subtract rls necessary क्रम VFs and one शेष one क्रम the PF */
	num_pf_rls -= num_vfs + NUM_DEFAULT_RLS;

	वापस num_pf_rls;
पूर्ण

अटल u16 qed_init_qm_get_num_vports(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 pq_flags = qed_get_pq_flags(p_hwfn);

	/* all pqs share the same vport, except क्रम vfs and pf_rl pqs */
	वापस (!!(PQ_FLAGS_RLS & pq_flags)) *
	       qed_init_qm_get_num_pf_rls(p_hwfn) +
	       (!!(PQ_FLAGS_VFS & pq_flags)) *
	       qed_init_qm_get_num_vfs(p_hwfn) + 1;
पूर्ण

/* calc amount of PQs according to the requested flags */
अटल u16 qed_init_qm_get_num_pqs(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 pq_flags = qed_get_pq_flags(p_hwfn);

	वापस (!!(PQ_FLAGS_RLS & pq_flags)) *
	       qed_init_qm_get_num_pf_rls(p_hwfn) +
	       (!!(PQ_FLAGS_MCOS & pq_flags)) *
	       qed_init_qm_get_num_tcs(p_hwfn) +
	       (!!(PQ_FLAGS_LB & pq_flags)) + (!!(PQ_FLAGS_OOO & pq_flags)) +
	       (!!(PQ_FLAGS_ACK & pq_flags)) +
	       (!!(PQ_FLAGS_OFLD & pq_flags)) *
	       qed_init_qm_get_num_mtc_tcs(p_hwfn) +
	       (!!(PQ_FLAGS_LLT & pq_flags)) *
	       qed_init_qm_get_num_mtc_tcs(p_hwfn) +
	       (!!(PQ_FLAGS_VFS & pq_flags)) * qed_init_qm_get_num_vfs(p_hwfn);
पूर्ण

/* initialize the top level QM params */
अटल व्योम qed_init_qm_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	bool four_port;

	/* pq and vport bases क्रम this PF */
	qm_info->start_pq = (u16) RESC_START(p_hwfn, QED_PQ);
	qm_info->start_vport = (u8) RESC_START(p_hwfn, QED_VPORT);

	/* rate limiting and weighted fair queueing are always enabled */
	qm_info->vport_rl_en = true;
	qm_info->vport_wfq_en = true;

	/* TC config is dअगरferent क्रम AH 4 port */
	four_port = p_hwfn->cdev->num_ports_in_engine == MAX_NUM_PORTS_K2;

	/* in AH 4 port we have fewer TCs per port */
	qm_info->max_phys_tcs_per_port = four_port ? NUM_PHYS_TCS_4PORT_K2 :
						     NUM_OF_PHYS_TCS;

	/* unless MFW indicated otherwise, ooo_tc == 3 क्रम
	 * AH 4-port and 4 otherwise.
	 */
	अगर (!qm_info->ooo_tc)
		qm_info->ooo_tc = four_port ? DCBX_TCP_OOO_K2_4PORT_TC :
					      DCBX_TCP_OOO_TC;
पूर्ण

/* initialize qm vport params */
अटल व्योम qed_init_qm_vport_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	u8 i;

	/* all vports participate in weighted fair queueing */
	क्रम (i = 0; i < qed_init_qm_get_num_vports(p_hwfn); i++)
		qm_info->qm_vport_params[i].wfq = 1;
पूर्ण

/* initialize qm port params */
अटल व्योम qed_init_qm_port_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* Initialize qm port parameters */
	u8 i, active_phys_tcs, num_ports = p_hwfn->cdev->num_ports_in_engine;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;

	/* indicate how ooo and high pri traffic is dealt with */
	active_phys_tcs = num_ports == MAX_NUM_PORTS_K2 ?
			  ACTIVE_TCS_BMAP_4PORT_K2 :
			  ACTIVE_TCS_BMAP;

	क्रम (i = 0; i < num_ports; i++) अणु
		काष्ठा init_qm_port_params *p_qm_port =
		    &p_hwfn->qm_info.qm_port_params[i];
		u16 pbf_max_cmd_lines;

		p_qm_port->active = 1;
		p_qm_port->active_phys_tcs = active_phys_tcs;
		pbf_max_cmd_lines = (u16)NUM_OF_PBF_CMD_LINES(cdev);
		p_qm_port->num_pbf_cmd_lines = pbf_max_cmd_lines / num_ports;
		p_qm_port->num_btb_blocks = NUM_OF_BTB_BLOCKS(cdev) / num_ports;
	पूर्ण
पूर्ण

/* Reset the params which must be reset क्रम qm init. QM init may be called as
 * a result of flows other than driver load (e.g. dcbx renegotiation). Other
 * params may be affected by the init but would simply recalculate to the same
 * values. The allocations made क्रम QM init, ports, vports, pqs and vfqs are not
 * affected as these amounts stay the same.
 */
अटल व्योम qed_init_qm_reset_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	qm_info->num_pqs = 0;
	qm_info->num_vports = 0;
	qm_info->num_pf_rls = 0;
	qm_info->num_vf_pqs = 0;
	qm_info->first_vf_pq = 0;
	qm_info->first_mcos_pq = 0;
	qm_info->first_rl_pq = 0;
पूर्ण

अटल व्योम qed_init_qm_advance_vport(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	qm_info->num_vports++;

	अगर (qm_info->num_vports > qed_init_qm_get_num_vports(p_hwfn))
		DP_ERR(p_hwfn,
		       "vport overflow! qm_info->num_vports %d, qm_init_get_num_vports() %d\n",
		       qm_info->num_vports, qed_init_qm_get_num_vports(p_hwfn));
पूर्ण

/* initialize a single pq and manage qm_info resources accounting.
 * The pq_init_flags param determines whether the PQ is rate limited
 * (क्रम VF or PF) and whether a new vport is allocated to the pq or not
 * (i.e. vport will be shared).
 */

/* flags क्रम pq init */
#घोषणा PQ_INIT_SHARE_VPORT     (1 << 0)
#घोषणा PQ_INIT_PF_RL           (1 << 1)
#घोषणा PQ_INIT_VF_RL           (1 << 2)

/* defines क्रम pq init */
#घोषणा PQ_INIT_DEFAULT_WRR_GROUP       1
#घोषणा PQ_INIT_DEFAULT_TC              0

व्योम qed_hw_info_set_offload_tc(काष्ठा qed_hw_info *p_info, u8 tc)
अणु
	p_info->offload_tc = tc;
	p_info->offload_tc_set = true;
पूर्ण

अटल bool qed_is_offload_tc_set(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस p_hwfn->hw_info.offload_tc_set;
पूर्ण

अटल u32 qed_get_offload_tc(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (qed_is_offload_tc_set(p_hwfn))
		वापस p_hwfn->hw_info.offload_tc;

	वापस PQ_INIT_DEFAULT_TC;
पूर्ण

अटल व्योम qed_init_qm_pq(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_qm_info *qm_info,
			   u8 tc, u32 pq_init_flags)
अणु
	u16 pq_idx = qm_info->num_pqs, max_pq = qed_init_qm_get_num_pqs(p_hwfn);

	अगर (pq_idx > max_pq)
		DP_ERR(p_hwfn,
		       "pq overflow! pq %d, max pq %d\n", pq_idx, max_pq);

	/* init pq params */
	qm_info->qm_pq_params[pq_idx].port_id = p_hwfn->port_id;
	qm_info->qm_pq_params[pq_idx].vport_id = qm_info->start_vport +
	    qm_info->num_vports;
	qm_info->qm_pq_params[pq_idx].tc_id = tc;
	qm_info->qm_pq_params[pq_idx].wrr_group = PQ_INIT_DEFAULT_WRR_GROUP;
	qm_info->qm_pq_params[pq_idx].rl_valid =
	    (pq_init_flags & PQ_INIT_PF_RL || pq_init_flags & PQ_INIT_VF_RL);

	/* qm params accounting */
	qm_info->num_pqs++;
	अगर (!(pq_init_flags & PQ_INIT_SHARE_VPORT))
		qm_info->num_vports++;

	अगर (pq_init_flags & PQ_INIT_PF_RL)
		qm_info->num_pf_rls++;

	अगर (qm_info->num_vports > qed_init_qm_get_num_vports(p_hwfn))
		DP_ERR(p_hwfn,
		       "vport overflow! qm_info->num_vports %d, qm_init_get_num_vports() %d\n",
		       qm_info->num_vports, qed_init_qm_get_num_vports(p_hwfn));

	अगर (qm_info->num_pf_rls > qed_init_qm_get_num_pf_rls(p_hwfn))
		DP_ERR(p_hwfn,
		       "rl overflow! qm_info->num_pf_rls %d, qm_init_get_num_pf_rls() %d\n",
		       qm_info->num_pf_rls, qed_init_qm_get_num_pf_rls(p_hwfn));
पूर्ण

/* get pq index according to PQ_FLAGS */
अटल u16 *qed_init_qm_get_idx_from_flags(काष्ठा qed_hwfn *p_hwfn,
					   अचिन्हित दीर्घ pq_flags)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	/* Can't have multiple flags set here */
	अगर (biपंचांगap_weight(&pq_flags,
			  माप(pq_flags) * BITS_PER_BYTE) > 1) अणु
		DP_ERR(p_hwfn, "requested multiple pq flags 0x%lx\n", pq_flags);
		जाओ err;
	पूर्ण

	अगर (!(qed_get_pq_flags(p_hwfn) & pq_flags)) अणु
		DP_ERR(p_hwfn, "pq flag 0x%lx is not set\n", pq_flags);
		जाओ err;
	पूर्ण

	चयन (pq_flags) अणु
	हाल PQ_FLAGS_RLS:
		वापस &qm_info->first_rl_pq;
	हाल PQ_FLAGS_MCOS:
		वापस &qm_info->first_mcos_pq;
	हाल PQ_FLAGS_LB:
		वापस &qm_info->pure_lb_pq;
	हाल PQ_FLAGS_OOO:
		वापस &qm_info->ooo_pq;
	हाल PQ_FLAGS_ACK:
		वापस &qm_info->pure_ack_pq;
	हाल PQ_FLAGS_OFLD:
		वापस &qm_info->first_ofld_pq;
	हाल PQ_FLAGS_LLT:
		वापस &qm_info->first_llt_pq;
	हाल PQ_FLAGS_VFS:
		वापस &qm_info->first_vf_pq;
	शेष:
		जाओ err;
	पूर्ण

err:
	वापस &qm_info->start_pq;
पूर्ण

/* save pq index in qm info */
अटल व्योम qed_init_qm_set_idx(काष्ठा qed_hwfn *p_hwfn,
				u32 pq_flags, u16 pq_val)
अणु
	u16 *base_pq_idx = qed_init_qm_get_idx_from_flags(p_hwfn, pq_flags);

	*base_pq_idx = p_hwfn->qm_info.start_pq + pq_val;
पूर्ण

/* get tx pq index, with the PQ TX base alपढ़ोy set (पढ़ोy क्रम context init) */
u16 qed_get_cm_pq_idx(काष्ठा qed_hwfn *p_hwfn, u32 pq_flags)
अणु
	u16 *base_pq_idx = qed_init_qm_get_idx_from_flags(p_hwfn, pq_flags);

	वापस *base_pq_idx + CM_TX_PQ_BASE;
पूर्ण

u16 qed_get_cm_pq_idx_mcos(काष्ठा qed_hwfn *p_hwfn, u8 tc)
अणु
	u8 max_tc = qed_init_qm_get_num_tcs(p_hwfn);

	अगर (max_tc == 0) अणु
		DP_ERR(p_hwfn, "pq with flag 0x%lx do not exist\n",
		       PQ_FLAGS_MCOS);
		वापस p_hwfn->qm_info.start_pq;
	पूर्ण

	अगर (tc > max_tc)
		DP_ERR(p_hwfn, "tc %d must be smaller than %d\n", tc, max_tc);

	वापस qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_MCOS) + (tc % max_tc);
पूर्ण

u16 qed_get_cm_pq_idx_vf(काष्ठा qed_hwfn *p_hwfn, u16 vf)
अणु
	u16 max_vf = qed_init_qm_get_num_vfs(p_hwfn);

	अगर (max_vf == 0) अणु
		DP_ERR(p_hwfn, "pq with flag 0x%lx do not exist\n",
		       PQ_FLAGS_VFS);
		वापस p_hwfn->qm_info.start_pq;
	पूर्ण

	अगर (vf > max_vf)
		DP_ERR(p_hwfn, "vf %d must be smaller than %d\n", vf, max_vf);

	वापस qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_VFS) + (vf % max_vf);
पूर्ण

u16 qed_get_cm_pq_idx_ofld_mtc(काष्ठा qed_hwfn *p_hwfn, u8 tc)
अणु
	u16 first_ofld_pq, pq_offset;

	first_ofld_pq = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	pq_offset = (tc < qed_init_qm_get_num_mtc_tcs(p_hwfn)) ?
		    tc : PQ_INIT_DEFAULT_TC;

	वापस first_ofld_pq + pq_offset;
पूर्ण

u16 qed_get_cm_pq_idx_llt_mtc(काष्ठा qed_hwfn *p_hwfn, u8 tc)
अणु
	u16 first_llt_pq, pq_offset;

	first_llt_pq = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LLT);
	pq_offset = (tc < qed_init_qm_get_num_mtc_tcs(p_hwfn)) ?
		    tc : PQ_INIT_DEFAULT_TC;

	वापस first_llt_pq + pq_offset;
पूर्ण

/* Functions क्रम creating specअगरic types of pqs */
अटल व्योम qed_init_qm_lb_pq(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_LB))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_LB, qm_info->num_pqs);
	qed_init_qm_pq(p_hwfn, qm_info, PURE_LB_TC, PQ_INIT_SHARE_VPORT);
पूर्ण

अटल व्योम qed_init_qm_ooo_pq(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_OOO))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_OOO, qm_info->num_pqs);
	qed_init_qm_pq(p_hwfn, qm_info, qm_info->ooo_tc, PQ_INIT_SHARE_VPORT);
पूर्ण

अटल व्योम qed_init_qm_pure_ack_pq(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_ACK))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_ACK, qm_info->num_pqs);
	qed_init_qm_pq(p_hwfn, qm_info, qed_get_offload_tc(p_hwfn),
		       PQ_INIT_SHARE_VPORT);
पूर्ण

अटल व्योम qed_init_qm_mtc_pqs(काष्ठा qed_hwfn *p_hwfn)
अणु
	u8 num_tcs = qed_init_qm_get_num_mtc_tcs(p_hwfn);
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	u8 tc;

	/* override pq's TC अगर offload TC is set */
	क्रम (tc = 0; tc < num_tcs; tc++)
		qed_init_qm_pq(p_hwfn, qm_info,
			       qed_is_offload_tc_set(p_hwfn) ?
			       p_hwfn->hw_info.offload_tc : tc,
			       PQ_INIT_SHARE_VPORT);
पूर्ण

अटल व्योम qed_init_qm_offload_pq(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_OFLD))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_OFLD, qm_info->num_pqs);
	qed_init_qm_mtc_pqs(p_hwfn);
पूर्ण

अटल व्योम qed_init_qm_low_latency_pq(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_LLT))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_LLT, qm_info->num_pqs);
	qed_init_qm_mtc_pqs(p_hwfn);
पूर्ण

अटल व्योम qed_init_qm_mcos_pqs(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	u8 tc_idx;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_MCOS))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_MCOS, qm_info->num_pqs);
	क्रम (tc_idx = 0; tc_idx < qed_init_qm_get_num_tcs(p_hwfn); tc_idx++)
		qed_init_qm_pq(p_hwfn, qm_info, tc_idx, PQ_INIT_SHARE_VPORT);
पूर्ण

अटल व्योम qed_init_qm_vf_pqs(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	u16 vf_idx, num_vfs = qed_init_qm_get_num_vfs(p_hwfn);

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_VFS))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_VFS, qm_info->num_pqs);
	qm_info->num_vf_pqs = num_vfs;
	क्रम (vf_idx = 0; vf_idx < num_vfs; vf_idx++)
		qed_init_qm_pq(p_hwfn,
			       qm_info, PQ_INIT_DEFAULT_TC, PQ_INIT_VF_RL);
पूर्ण

अटल व्योम qed_init_qm_rl_pqs(काष्ठा qed_hwfn *p_hwfn)
अणु
	u16 pf_rls_idx, num_pf_rls = qed_init_qm_get_num_pf_rls(p_hwfn);
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;

	अगर (!(qed_get_pq_flags(p_hwfn) & PQ_FLAGS_RLS))
		वापस;

	qed_init_qm_set_idx(p_hwfn, PQ_FLAGS_RLS, qm_info->num_pqs);
	क्रम (pf_rls_idx = 0; pf_rls_idx < num_pf_rls; pf_rls_idx++)
		qed_init_qm_pq(p_hwfn, qm_info, qed_get_offload_tc(p_hwfn),
			       PQ_INIT_PF_RL);
पूर्ण

अटल व्योम qed_init_qm_pq_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* rate limited pqs, must come first (FW assumption) */
	qed_init_qm_rl_pqs(p_hwfn);

	/* pqs क्रम multi cos */
	qed_init_qm_mcos_pqs(p_hwfn);

	/* pure loopback pq */
	qed_init_qm_lb_pq(p_hwfn);

	/* out of order pq */
	qed_init_qm_ooo_pq(p_hwfn);

	/* pure ack pq */
	qed_init_qm_pure_ack_pq(p_hwfn);

	/* pq क्रम offloaded protocol */
	qed_init_qm_offload_pq(p_hwfn);

	/* low latency pq */
	qed_init_qm_low_latency_pq(p_hwfn);

	/* करोne sharing vports */
	qed_init_qm_advance_vport(p_hwfn);

	/* pqs क्रम vfs */
	qed_init_qm_vf_pqs(p_hwfn);
पूर्ण

/* compare values of getters against resources amounts */
अटल पूर्णांक qed_init_qm_sanity(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (qed_init_qm_get_num_vports(p_hwfn) > RESC_NUM(p_hwfn, QED_VPORT)) अणु
		DP_ERR(p_hwfn, "requested amount of vports exceeds resource\n");
		वापस -EINVAL;
	पूर्ण

	अगर (qed_init_qm_get_num_pqs(p_hwfn) <= RESC_NUM(p_hwfn, QED_PQ))
		वापस 0;

	अगर (QED_IS_ROCE_PERSONALITY(p_hwfn)) अणु
		p_hwfn->hw_info.multi_tc_roce_en = false;
		DP_NOTICE(p_hwfn,
			  "multi-tc roce was disabled to reduce requested amount of pqs\n");
		अगर (qed_init_qm_get_num_pqs(p_hwfn) <= RESC_NUM(p_hwfn, QED_PQ))
			वापस 0;
	पूर्ण

	DP_ERR(p_hwfn, "requested amount of pqs exceeds resource\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम qed_dp_init_qm_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	काष्ठा init_qm_vport_params *vport;
	काष्ठा init_qm_port_params *port;
	काष्ठा init_qm_pq_params *pq;
	पूर्णांक i, tc;

	/* top level params */
	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_HW,
		   "qm init top level params: start_pq %d, start_vport %d, pure_lb_pq %d, offload_pq %d, llt_pq %d, pure_ack_pq %d\n",
		   qm_info->start_pq,
		   qm_info->start_vport,
		   qm_info->pure_lb_pq,
		   qm_info->first_ofld_pq,
		   qm_info->first_llt_pq,
		   qm_info->pure_ack_pq);
	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_HW,
		   "ooo_pq %d, first_vf_pq %d, num_pqs %d, num_vf_pqs %d, num_vports %d, max_phys_tcs_per_port %d\n",
		   qm_info->ooo_pq,
		   qm_info->first_vf_pq,
		   qm_info->num_pqs,
		   qm_info->num_vf_pqs,
		   qm_info->num_vports, qm_info->max_phys_tcs_per_port);
	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_HW,
		   "pf_rl_en %d, pf_wfq_en %d, vport_rl_en %d, vport_wfq_en %d, pf_wfq %d, pf_rl %d, num_pf_rls %d, pq_flags %x\n",
		   qm_info->pf_rl_en,
		   qm_info->pf_wfq_en,
		   qm_info->vport_rl_en,
		   qm_info->vport_wfq_en,
		   qm_info->pf_wfq,
		   qm_info->pf_rl,
		   qm_info->num_pf_rls, qed_get_pq_flags(p_hwfn));

	/* port table */
	क्रम (i = 0; i < p_hwfn->cdev->num_ports_in_engine; i++) अणु
		port = &(qm_info->qm_port_params[i]);
		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_HW,
			   "port idx %d, active %d, active_phys_tcs %d, num_pbf_cmd_lines %d, num_btb_blocks %d, reserved %d\n",
			   i,
			   port->active,
			   port->active_phys_tcs,
			   port->num_pbf_cmd_lines,
			   port->num_btb_blocks, port->reserved);
	पूर्ण

	/* vport table */
	क्रम (i = 0; i < qm_info->num_vports; i++) अणु
		vport = &(qm_info->qm_vport_params[i]);
		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_HW,
			   "vport idx %d, wfq %d, first_tx_pq_id [ ",
			   qm_info->start_vport + i, vport->wfq);
		क्रम (tc = 0; tc < NUM_OF_TCS; tc++)
			DP_VERBOSE(p_hwfn,
				   NETIF_MSG_HW,
				   "%d ", vport->first_tx_pq_id[tc]);
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW, "]\n");
	पूर्ण

	/* pq table */
	क्रम (i = 0; i < qm_info->num_pqs; i++) अणु
		pq = &(qm_info->qm_pq_params[i]);
		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_HW,
			   "pq idx %d, port %d, vport_id %d, tc %d, wrr_grp %d, rl_valid %d rl_id %d\n",
			   qm_info->start_pq + i,
			   pq->port_id,
			   pq->vport_id,
			   pq->tc_id, pq->wrr_group, pq->rl_valid, pq->rl_id);
	पूर्ण
पूर्ण

अटल व्योम qed_init_qm_info(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* reset params required क्रम init run */
	qed_init_qm_reset_params(p_hwfn);

	/* init QM top level params */
	qed_init_qm_params(p_hwfn);

	/* init QM port params */
	qed_init_qm_port_params(p_hwfn);

	/* init QM vport params */
	qed_init_qm_vport_params(p_hwfn);

	/* init QM physical queue params */
	qed_init_qm_pq_params(p_hwfn);

	/* display all that init */
	qed_dp_init_qm_params(p_hwfn);
पूर्ण

/* This function reconfigures the QM pf on the fly.
 * For this purpose we:
 * 1. reconfigure the QM database
 * 2. set new values to runसमय array
 * 3. send an sdm_qm_cmd through the rbc पूर्णांकerface to stop the QM
 * 4. activate init tool in QM_PF stage
 * 5. send an sdm_qm_cmd through rbc पूर्णांकerface to release the QM
 */
पूर्णांक qed_qm_reconf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	bool b_rc;
	पूर्णांक rc;

	/* initialize qed's qm data काष्ठाure */
	qed_init_qm_info(p_hwfn);

	/* stop PF's qm queues */
	spin_lock_bh(&qm_lock);
	b_rc = qed_send_qm_stop_cmd(p_hwfn, p_ptt, false, true,
				    qm_info->start_pq, qm_info->num_pqs);
	spin_unlock_bh(&qm_lock);
	अगर (!b_rc)
		वापस -EINVAL;

	/* prepare QM portion of runसमय array */
	qed_qm_init_pf(p_hwfn, p_ptt, false);

	/* activate init tool on runसमय array */
	rc = qed_init_run(p_hwfn, p_ptt, PHASE_QM_PF, p_hwfn->rel_pf_id,
			  p_hwfn->hw_info.hw_mode);
	अगर (rc)
		वापस rc;

	/* start PF's qm queues */
	spin_lock_bh(&qm_lock);
	b_rc = qed_send_qm_stop_cmd(p_hwfn, p_ptt, true, true,
				    qm_info->start_pq, qm_info->num_pqs);
	spin_unlock_bh(&qm_lock);
	अगर (!b_rc)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qed_alloc_qm_data(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	पूर्णांक rc;

	rc = qed_init_qm_sanity(p_hwfn);
	अगर (rc)
		जाओ alloc_err;

	qm_info->qm_pq_params = kसुस्मृति(qed_init_qm_get_num_pqs(p_hwfn),
					माप(*qm_info->qm_pq_params),
					GFP_KERNEL);
	अगर (!qm_info->qm_pq_params)
		जाओ alloc_err;

	qm_info->qm_vport_params = kसुस्मृति(qed_init_qm_get_num_vports(p_hwfn),
					   माप(*qm_info->qm_vport_params),
					   GFP_KERNEL);
	अगर (!qm_info->qm_vport_params)
		जाओ alloc_err;

	qm_info->qm_port_params = kसुस्मृति(p_hwfn->cdev->num_ports_in_engine,
					  माप(*qm_info->qm_port_params),
					  GFP_KERNEL);
	अगर (!qm_info->qm_port_params)
		जाओ alloc_err;

	qm_info->wfq_data = kसुस्मृति(qed_init_qm_get_num_vports(p_hwfn),
				    माप(*qm_info->wfq_data),
				    GFP_KERNEL);
	अगर (!qm_info->wfq_data)
		जाओ alloc_err;

	वापस 0;

alloc_err:
	DP_NOTICE(p_hwfn, "Failed to allocate memory for QM params\n");
	qed_qm_info_मुक्त(p_hwfn);
	वापस -ENOMEM;
पूर्ण

पूर्णांक qed_resc_alloc(काष्ठा qed_dev *cdev)
अणु
	u32 rdma_tasks, excess_tasks;
	u32 line_count;
	पूर्णांक i, rc = 0;

	अगर (IS_VF(cdev)) अणु
		क्रम_each_hwfn(cdev, i) अणु
			rc = qed_l2_alloc(&cdev->hwfns[i]);
			अगर (rc)
				वापस rc;
		पूर्ण
		वापस rc;
	पूर्ण

	cdev->fw_data = kzalloc(माप(*cdev->fw_data), GFP_KERNEL);
	अगर (!cdev->fw_data)
		वापस -ENOMEM;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		u32 n_eqes, num_cons;

		/* Initialize the करोorbell recovery mechanism */
		rc = qed_db_recovery_setup(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* First allocate the context manager काष्ठाure */
		rc = qed_cxt_mngr_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* Set the HW cid/tid numbers (in the contest manager)
		 * Must be करोne prior to any further computations.
		 */
		rc = qed_cxt_set_pf_params(p_hwfn, RDMA_MAX_TIDS);
		अगर (rc)
			जाओ alloc_err;

		rc = qed_alloc_qm_data(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* init qm info */
		qed_init_qm_info(p_hwfn);

		/* Compute the ILT client partition */
		rc = qed_cxt_cfg_ilt_compute(p_hwfn, &line_count);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "too many ILT lines; re-computing with less lines\n");
			/* In हाल there are not enough ILT lines we reduce the
			 * number of RDMA tasks and re-compute.
			 */
			excess_tasks =
			    qed_cxt_cfg_ilt_compute_excess(p_hwfn, line_count);
			अगर (!excess_tasks)
				जाओ alloc_err;

			rdma_tasks = RDMA_MAX_TIDS - excess_tasks;
			rc = qed_cxt_set_pf_params(p_hwfn, rdma_tasks);
			अगर (rc)
				जाओ alloc_err;

			rc = qed_cxt_cfg_ilt_compute(p_hwfn, &line_count);
			अगर (rc) अणु
				DP_ERR(p_hwfn,
				       "failed ILT compute. Requested too many lines: %u\n",
				       line_count);

				जाओ alloc_err;
			पूर्ण
		पूर्ण

		/* CID map / ILT shaकरोw table / T2
		 * The talbes sizes are determined by the computations above
		 */
		rc = qed_cxt_tables_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* SPQ, must follow ILT because initializes SPQ context */
		rc = qed_spq_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* SP status block allocation */
		p_hwfn->p_dpc_ptt = qed_get_reserved_ptt(p_hwfn,
							 RESERVED_PTT_DPC);

		rc = qed_पूर्णांक_alloc(p_hwfn, p_hwfn->p_मुख्य_ptt);
		अगर (rc)
			जाओ alloc_err;

		rc = qed_iov_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* EQ */
		n_eqes = qed_chain_get_capacity(&p_hwfn->p_spq->chain);
		अगर (QED_IS_RDMA_PERSONALITY(p_hwfn)) अणु
			u32 n_srq = qed_cxt_get_total_srq_count(p_hwfn);
			क्रमागत protocol_type rdma_proto;

			अगर (QED_IS_ROCE_PERSONALITY(p_hwfn))
				rdma_proto = PROTOCOLID_ROCE;
			अन्यथा
				rdma_proto = PROTOCOLID_IWARP;

			num_cons = qed_cxt_get_proto_cid_count(p_hwfn,
							       rdma_proto,
							       शून्य) * 2;
			/* EQ should be able to get events from all SRQ's
			 * at the same समय
			 */
			n_eqes += num_cons + 2 * MAX_NUM_VFS_BB + n_srq;
		पूर्ण अन्यथा अगर (p_hwfn->hw_info.personality == QED_PCI_ISCSI) अणु
			num_cons =
			    qed_cxt_get_proto_cid_count(p_hwfn,
							PROTOCOLID_ISCSI,
							शून्य);
			n_eqes += 2 * num_cons;
		पूर्ण

		अगर (n_eqes > 0xFFFF) अणु
			DP_ERR(p_hwfn,
			       "Cannot allocate 0x%x EQ elements. The maximum of a u16 chain is 0x%x\n",
			       n_eqes, 0xFFFF);
			जाओ alloc_no_mem;
		पूर्ण

		rc = qed_eq_alloc(p_hwfn, (u16) n_eqes);
		अगर (rc)
			जाओ alloc_err;

		rc = qed_consq_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		rc = qed_l2_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

#अगर_घोषित CONFIG_QED_LL2
		अगर (p_hwfn->using_ll2) अणु
			rc = qed_ll2_alloc(p_hwfn);
			अगर (rc)
				जाओ alloc_err;
		पूर्ण
#पूर्ण_अगर

		अगर (p_hwfn->hw_info.personality == QED_PCI_FCOE) अणु
			rc = qed_fcoe_alloc(p_hwfn);
			अगर (rc)
				जाओ alloc_err;
		पूर्ण

		अगर (p_hwfn->hw_info.personality == QED_PCI_ISCSI) अणु
			rc = qed_iscsi_alloc(p_hwfn);
			अगर (rc)
				जाओ alloc_err;
			rc = qed_ooo_alloc(p_hwfn);
			अगर (rc)
				जाओ alloc_err;
		पूर्ण

		अगर (QED_IS_RDMA_PERSONALITY(p_hwfn)) अणु
			rc = qed_rdma_info_alloc(p_hwfn);
			अगर (rc)
				जाओ alloc_err;
		पूर्ण

		/* DMA info initialization */
		rc = qed_dmae_info_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		/* DCBX initialization */
		rc = qed_dcbx_info_alloc(p_hwfn);
		अगर (rc)
			जाओ alloc_err;

		rc = qed_dbg_alloc_user_data(p_hwfn, &p_hwfn->dbg_user_info);
		अगर (rc)
			जाओ alloc_err;
	पूर्ण

	rc = qed_llh_alloc(cdev);
	अगर (rc) अणु
		DP_NOTICE(cdev,
			  "Failed to allocate memory for the llh_info structure\n");
		जाओ alloc_err;
	पूर्ण

	cdev->reset_stats = kzalloc(माप(*cdev->reset_stats), GFP_KERNEL);
	अगर (!cdev->reset_stats)
		जाओ alloc_no_mem;

	वापस 0;

alloc_no_mem:
	rc = -ENOMEM;
alloc_err:
	qed_resc_मुक्त(cdev);
	वापस rc;
पूर्ण

व्योम qed_resc_setup(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	अगर (IS_VF(cdev)) अणु
		क्रम_each_hwfn(cdev, i)
			qed_l2_setup(&cdev->hwfns[i]);
		वापस;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		qed_cxt_mngr_setup(p_hwfn);
		qed_spq_setup(p_hwfn);
		qed_eq_setup(p_hwfn);
		qed_consq_setup(p_hwfn);

		/* Read shaकरोw of current MFW mailbox */
		qed_mcp_पढ़ो_mb(p_hwfn, p_hwfn->p_मुख्य_ptt);
		स_नकल(p_hwfn->mcp_info->mfw_mb_shaकरोw,
		       p_hwfn->mcp_info->mfw_mb_cur,
		       p_hwfn->mcp_info->mfw_mb_length);

		qed_पूर्णांक_setup(p_hwfn, p_hwfn->p_मुख्य_ptt);

		qed_l2_setup(p_hwfn);
		qed_iov_setup(p_hwfn);
#अगर_घोषित CONFIG_QED_LL2
		अगर (p_hwfn->using_ll2)
			qed_ll2_setup(p_hwfn);
#पूर्ण_अगर
		अगर (p_hwfn->hw_info.personality == QED_PCI_FCOE)
			qed_fcoe_setup(p_hwfn);

		अगर (p_hwfn->hw_info.personality == QED_PCI_ISCSI) अणु
			qed_iscsi_setup(p_hwfn);
			qed_ooo_setup(p_hwfn);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा FINAL_CLEANUP_POLL_CNT          (100)
#घोषणा FINAL_CLEANUP_POLL_TIME         (10)
पूर्णांक qed_final_cleanup(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, u16 id, bool is_vf)
अणु
	u32 command = 0, addr, count = FINAL_CLEANUP_POLL_CNT;
	पूर्णांक rc = -EBUSY;

	addr = GTT_BAR0_MAP_REG_USDM_RAM +
		USTORM_FLR_FINAL_ACK_OFFSET(p_hwfn->rel_pf_id);

	अगर (is_vf)
		id += 0x10;

	command |= X_FINAL_CLEANUP_AGG_INT <<
		SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_SHIFT;
	command |= 1 << SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_SHIFT;
	command |= id << SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_SHIFT;
	command |= SDM_COMP_TYPE_AGG_INT << SDM_OP_GEN_COMP_TYPE_SHIFT;

	/* Make sure notअगरication is not set beक्रमe initiating final cleanup */
	अगर (REG_RD(p_hwfn, addr)) अणु
		DP_NOTICE(p_hwfn,
			  "Unexpected; Found final cleanup notification before initiating final cleanup\n");
		REG_WR(p_hwfn, addr, 0);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Sending final cleanup for PFVF[%d] [Command %08x]\n",
		   id, command);

	qed_wr(p_hwfn, p_ptt, XSDM_REG_OPERATION_GEN, command);

	/* Poll until completion */
	जबतक (!REG_RD(p_hwfn, addr) && count--)
		msleep(FINAL_CLEANUP_POLL_TIME);

	अगर (REG_RD(p_hwfn, addr))
		rc = 0;
	अन्यथा
		DP_NOTICE(p_hwfn,
			  "Failed to receive FW final cleanup notification\n");

	/* Cleanup afterwards */
	REG_WR(p_hwfn, addr, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_calc_hw_mode(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक hw_mode = 0;

	अगर (QED_IS_BB_B0(p_hwfn->cdev)) अणु
		hw_mode |= 1 << MODE_BB;
	पूर्ण अन्यथा अगर (QED_IS_AH(p_hwfn->cdev)) अणु
		hw_mode |= 1 << MODE_K2;
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "Unknown chip type %#x\n",
			  p_hwfn->cdev->type);
		वापस -EINVAL;
	पूर्ण

	चयन (p_hwfn->cdev->num_ports_in_engine) अणु
	हाल 1:
		hw_mode |= 1 << MODE_PORTS_PER_ENG_1;
		अवरोध;
	हाल 2:
		hw_mode |= 1 << MODE_PORTS_PER_ENG_2;
		अवरोध;
	हाल 4:
		hw_mode |= 1 << MODE_PORTS_PER_ENG_4;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "num_ports_in_engine = %d not supported\n",
			  p_hwfn->cdev->num_ports_in_engine);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(QED_MF_OVLAN_CLSS, &p_hwfn->cdev->mf_bits))
		hw_mode |= 1 << MODE_MF_SD;
	अन्यथा
		hw_mode |= 1 << MODE_MF_SI;

	hw_mode |= 1 << MODE_ASIC;

	अगर (p_hwfn->cdev->num_hwfns > 1)
		hw_mode |= 1 << MODE_100G;

	p_hwfn->hw_info.hw_mode = hw_mode;

	DP_VERBOSE(p_hwfn, (NETIF_MSG_PROBE | NETIF_MSG_IFUP),
		   "Configuring function for hw_mode: 0x%08x\n",
		   p_hwfn->hw_info.hw_mode);

	वापस 0;
पूर्ण

/* Init run समय data क्रम all PFs on an engine. */
अटल व्योम qed_init_cau_rt_data(काष्ठा qed_dev *cdev)
अणु
	u32 offset = CAU_REG_SB_VAR_MEMORY_RT_OFFSET;
	पूर्णांक i, igu_sb_id;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		काष्ठा qed_igu_info *p_igu_info;
		काष्ठा qed_igu_block *p_block;
		काष्ठा cau_sb_entry sb_entry;

		p_igu_info = p_hwfn->hw_info.p_igu_info;

		क्रम (igu_sb_id = 0;
		     igu_sb_id < QED_MAPPING_MEMORY_SIZE(cdev); igu_sb_id++) अणु
			p_block = &p_igu_info->entry[igu_sb_id];

			अगर (!p_block->is_pf)
				जारी;

			qed_init_cau_sb_entry(p_hwfn, &sb_entry,
					      p_block->function_id, 0, 0);
			STORE_RT_REG_AGG(p_hwfn, offset + igu_sb_id * 2,
					 sb_entry);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qed_init_cache_line_size(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt)
अणु
	u32 val, wr_mbs, cache_line_size;

	val = qed_rd(p_hwfn, p_ptt, PSWRQ2_REG_WR_MBS0);
	चयन (val) अणु
	हाल 0:
		wr_mbs = 128;
		अवरोध;
	हाल 1:
		wr_mbs = 256;
		अवरोध;
	हाल 2:
		wr_mbs = 512;
		अवरोध;
	शेष:
		DP_INFO(p_hwfn,
			"Unexpected value of PSWRQ2_REG_WR_MBS0 [0x%x]. Avoid configuring PGLUE_B_REG_CACHE_LINE_SIZE.\n",
			val);
		वापस;
	पूर्ण

	cache_line_size = min_t(u32, L1_CACHE_BYTES, wr_mbs);
	चयन (cache_line_size) अणु
	हाल 32:
		val = 0;
		अवरोध;
	हाल 64:
		val = 1;
		अवरोध;
	हाल 128:
		val = 2;
		अवरोध;
	हाल 256:
		val = 3;
		अवरोध;
	शेष:
		DP_INFO(p_hwfn,
			"Unexpected value of cache line size [0x%x]. Avoid configuring PGLUE_B_REG_CACHE_LINE_SIZE.\n",
			cache_line_size);
	पूर्ण

	अगर (L1_CACHE_BYTES > wr_mbs)
		DP_INFO(p_hwfn,
			"The cache line size for padding is suboptimal for performance [OS cache line size 0x%x, wr mbs 0x%x]\n",
			L1_CACHE_BYTES, wr_mbs);

	STORE_RT_REG(p_hwfn, PGLUE_REG_B_CACHE_LINE_SIZE_RT_OFFSET, val);
	अगर (val > 0) अणु
		STORE_RT_REG(p_hwfn, PSWRQ2_REG_DRAM_ALIGN_WR_RT_OFFSET, val);
		STORE_RT_REG(p_hwfn, PSWRQ2_REG_DRAM_ALIGN_RD_RT_OFFSET, val);
	पूर्ण
पूर्ण

अटल पूर्णांक qed_hw_init_common(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt, पूर्णांक hw_mode)
अणु
	काष्ठा qed_qm_info *qm_info = &p_hwfn->qm_info;
	काष्ठा qed_qm_common_rt_init_params params;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u8 vf_id, max_num_vfs;
	u16 num_pfs, pf_id;
	u32 concrete_fid;
	पूर्णांक rc = 0;

	qed_init_cau_rt_data(cdev);

	/* Program GTT winकरोws */
	qed_gtt_init(p_hwfn);

	अगर (p_hwfn->mcp_info) अणु
		अगर (p_hwfn->mcp_info->func_info.bandwidth_max)
			qm_info->pf_rl_en = true;
		अगर (p_hwfn->mcp_info->func_info.bandwidth_min)
			qm_info->pf_wfq_en = true;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.max_ports_per_engine = p_hwfn->cdev->num_ports_in_engine;
	params.max_phys_tcs_per_port = qm_info->max_phys_tcs_per_port;
	params.pf_rl_en = qm_info->pf_rl_en;
	params.pf_wfq_en = qm_info->pf_wfq_en;
	params.global_rl_en = qm_info->vport_rl_en;
	params.vport_wfq_en = qm_info->vport_wfq_en;
	params.port_params = qm_info->qm_port_params;

	qed_qm_common_rt_init(p_hwfn, &params);

	qed_cxt_hw_init_common(p_hwfn);

	qed_init_cache_line_size(p_hwfn, p_ptt);

	rc = qed_init_run(p_hwfn, p_ptt, PHASE_ENGINE, ANY_PHASE_ID, hw_mode);
	अगर (rc)
		वापस rc;

	qed_wr(p_hwfn, p_ptt, PSWRQ2_REG_L2P_VALIDATE_VFID, 0);
	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_USE_CLIENTID_IN_TAG, 1);

	अगर (QED_IS_BB(p_hwfn->cdev)) अणु
		num_pfs = NUM_OF_ENG_PFS(p_hwfn->cdev);
		क्रम (pf_id = 0; pf_id < num_pfs; pf_id++) अणु
			qed_fid_pretend(p_hwfn, p_ptt, pf_id);
			qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_ROCE, 0x0);
			qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TCP, 0x0);
		पूर्ण
		/* pretend to original PF */
		qed_fid_pretend(p_hwfn, p_ptt, p_hwfn->rel_pf_id);
	पूर्ण

	max_num_vfs = QED_IS_AH(cdev) ? MAX_NUM_VFS_K2 : MAX_NUM_VFS_BB;
	क्रम (vf_id = 0; vf_id < max_num_vfs; vf_id++) अणु
		concrete_fid = qed_vfid_to_concrete(p_hwfn, vf_id);
		qed_fid_pretend(p_hwfn, p_ptt, (u16) concrete_fid);
		qed_wr(p_hwfn, p_ptt, CCFC_REG_STRONG_ENABLE_VF, 0x1);
		qed_wr(p_hwfn, p_ptt, CCFC_REG_WEAK_ENABLE_VF, 0x0);
		qed_wr(p_hwfn, p_ptt, TCFC_REG_STRONG_ENABLE_VF, 0x1);
		qed_wr(p_hwfn, p_ptt, TCFC_REG_WEAK_ENABLE_VF, 0x0);
	पूर्ण
	/* pretend to original PF */
	qed_fid_pretend(p_hwfn, p_ptt, p_hwfn->rel_pf_id);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_hw_init_dpi_size(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt, u32 pwm_region_size, u32 n_cpus)
अणु
	u32 dpi_bit_shअगरt, dpi_count, dpi_page_size;
	u32 min_dpis;
	u32 n_wids;

	/* Calculate DPI size */
	n_wids = max_t(u32, QED_MIN_WIDS, n_cpus);
	dpi_page_size = QED_WID_SIZE * roundup_घात_of_two(n_wids);
	dpi_page_size = (dpi_page_size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	dpi_bit_shअगरt = ilog2(dpi_page_size / 4096);
	dpi_count = pwm_region_size / dpi_page_size;

	min_dpis = p_hwfn->pf_params.rdma_pf_params.min_dpis;
	min_dpis = max_t(u32, QED_MIN_DPIS, min_dpis);

	p_hwfn->dpi_size = dpi_page_size;
	p_hwfn->dpi_count = dpi_count;

	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_DPI_BIT_SHIFT, dpi_bit_shअगरt);

	अगर (dpi_count < min_dpis)
		वापस -EINVAL;

	वापस 0;
पूर्ण

क्रमागत QED_ROCE_EDPM_MODE अणु
	QED_ROCE_EDPM_MODE_ENABLE = 0,
	QED_ROCE_EDPM_MODE_FORCE_ON = 1,
	QED_ROCE_EDPM_MODE_DISABLE = 2,
पूर्ण;

bool qed_edpm_enabled(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (p_hwfn->dcbx_no_edpm || p_hwfn->db_bar_no_edpm)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
qed_hw_init_pf_करोorbell_bar(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 pwm_regsize, norm_regsize;
	u32 non_pwm_conn, min_addr_reg1;
	u32 db_bar_size, n_cpus = 1;
	u32 roce_edpm_mode;
	u32 pf_dems_shअगरt;
	पूर्णांक rc = 0;
	u8 cond;

	db_bar_size = qed_hw_bar_size(p_hwfn, p_ptt, BAR_ID_1);
	अगर (p_hwfn->cdev->num_hwfns > 1)
		db_bar_size /= 2;

	/* Calculate करोorbell regions */
	non_pwm_conn = qed_cxt_get_proto_cid_start(p_hwfn, PROTOCOLID_CORE) +
		       qed_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_CORE,
						   शून्य) +
		       qed_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_ETH,
						   शून्य);
	norm_regsize = roundup(QED_PF_DEMS_SIZE * non_pwm_conn, PAGE_SIZE);
	min_addr_reg1 = norm_regsize / 4096;
	pwm_regsize = db_bar_size - norm_regsize;

	/* Check that the normal and PWM sizes are valid */
	अगर (db_bar_size < norm_regsize) अणु
		DP_ERR(p_hwfn->cdev,
		       "Doorbell BAR size 0x%x is too small (normal region is 0x%0x )\n",
		       db_bar_size, norm_regsize);
		वापस -EINVAL;
	पूर्ण

	अगर (pwm_regsize < QED_MIN_PWM_REGION) अणु
		DP_ERR(p_hwfn->cdev,
		       "PWM region size 0x%0x is too small. Should be at least 0x%0x (Doorbell BAR size is 0x%x and normal region size is 0x%0x)\n",
		       pwm_regsize,
		       QED_MIN_PWM_REGION, db_bar_size, norm_regsize);
		वापस -EINVAL;
	पूर्ण

	/* Calculate number of DPIs */
	roce_edpm_mode = p_hwfn->pf_params.rdma_pf_params.roce_edpm_mode;
	अगर ((roce_edpm_mode == QED_ROCE_EDPM_MODE_ENABLE) ||
	    ((roce_edpm_mode == QED_ROCE_EDPM_MODE_FORCE_ON))) अणु
		/* Either EDPM is mandatory, or we are attempting to allocate a
		 * WID per CPU.
		 */
		n_cpus = num_present_cpus();
		rc = qed_hw_init_dpi_size(p_hwfn, p_ptt, pwm_regsize, n_cpus);
	पूर्ण

	cond = (rc && (roce_edpm_mode == QED_ROCE_EDPM_MODE_ENABLE)) ||
	       (roce_edpm_mode == QED_ROCE_EDPM_MODE_DISABLE);
	अगर (cond || p_hwfn->dcbx_no_edpm) अणु
		/* Either EDPM is disabled from user configuration, or it is
		 * disabled via DCBx, or it is not mandatory and we failed to
		 * allocated a WID per CPU.
		 */
		n_cpus = 1;
		rc = qed_hw_init_dpi_size(p_hwfn, p_ptt, pwm_regsize, n_cpus);

		अगर (cond)
			qed_rdma_dpm_bar(p_hwfn, p_ptt);
	पूर्ण

	p_hwfn->wid_count = (u16) n_cpus;

	DP_INFO(p_hwfn,
		"doorbell bar: normal_region_size=%d, pwm_region_size=%d, dpi_size=%d, dpi_count=%d, roce_edpm=%s, page_size=%lu\n",
		norm_regsize,
		pwm_regsize,
		p_hwfn->dpi_size,
		p_hwfn->dpi_count,
		(!qed_edpm_enabled(p_hwfn)) ?
		"disabled" : "enabled", PAGE_SIZE);

	अगर (rc) अणु
		DP_ERR(p_hwfn,
		       "Failed to allocate enough DPIs. Allocated %d but the current minimum is %d.\n",
		       p_hwfn->dpi_count,
		       p_hwfn->pf_params.rdma_pf_params.min_dpis);
		वापस -EINVAL;
	पूर्ण

	p_hwfn->dpi_start_offset = norm_regsize;

	/* DEMS size is configured log2 of DWORDs, hence the भागision by 4 */
	pf_dems_shअगरt = ilog2(QED_PF_DEMS_SIZE / 4);
	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_ICID_BIT_SHIFT_NORM, pf_dems_shअगरt);
	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_MIN_ADDR_REG1, min_addr_reg1);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_hw_init_port(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, पूर्णांक hw_mode)
अणु
	पूर्णांक rc = 0;

	/* In CMT the gate should be cleared by the 2nd hwfn */
	अगर (!QED_IS_CMT(p_hwfn->cdev) || !IS_LEAD_HWFN(p_hwfn))
		STORE_RT_REG(p_hwfn, NIG_REG_BRB_GATE_DNTFWD_PORT_RT_OFFSET, 0);

	rc = qed_init_run(p_hwfn, p_ptt, PHASE_PORT, p_hwfn->port_id, hw_mode);
	अगर (rc)
		वापस rc;

	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_MASTER_WRITE_PAD_ENABLE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_hw_init_pf(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  काष्ठा qed_tunnel_info *p_tunn,
			  पूर्णांक hw_mode,
			  bool b_hw_start,
			  क्रमागत qed_पूर्णांक_mode पूर्णांक_mode,
			  bool allow_npar_tx_चयन)
अणु
	u8 rel_pf_id = p_hwfn->rel_pf_id;
	पूर्णांक rc = 0;

	अगर (p_hwfn->mcp_info) अणु
		काष्ठा qed_mcp_function_info *p_info;

		p_info = &p_hwfn->mcp_info->func_info;
		अगर (p_info->bandwidth_min)
			p_hwfn->qm_info.pf_wfq = p_info->bandwidth_min;

		/* Update rate limit once we'll actually have a link */
		p_hwfn->qm_info.pf_rl = 100000;
	पूर्ण

	qed_cxt_hw_init_pf(p_hwfn, p_ptt);

	qed_पूर्णांक_igu_init_rt(p_hwfn);

	/* Set VLAN in NIG अगर needed */
	अगर (hw_mode & BIT(MODE_MF_SD)) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW, "Configuring LLH_FUNC_TAG\n");
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_TAG_EN_RT_OFFSET, 1);
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_TAG_VALUE_RT_OFFSET,
			     p_hwfn->hw_info.ovlan);

		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "Configuring LLH_FUNC_FILTER_HDR_SEL\n");
		STORE_RT_REG(p_hwfn, NIG_REG_LLH_FUNC_FILTER_HDR_SEL_RT_OFFSET,
			     1);
	पूर्ण

	/* Enable classअगरication by MAC अगर needed */
	अगर (hw_mode & BIT(MODE_MF_SI)) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
			   "Configuring TAGMAC_CLS_TYPE\n");
		STORE_RT_REG(p_hwfn,
			     NIG_REG_LLH_FUNC_TAGMAC_CLS_TYPE_RT_OFFSET, 1);
	पूर्ण

	/* Protocol Configuration */
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_TCP_RT_OFFSET,
		     (p_hwfn->hw_info.personality == QED_PCI_ISCSI) ? 1 : 0);
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_FCOE_RT_OFFSET,
		     (p_hwfn->hw_info.personality == QED_PCI_FCOE) ? 1 : 0);
	STORE_RT_REG(p_hwfn, PRS_REG_SEARCH_ROCE_RT_OFFSET, 0);

	/* Sanity check beक्रमe the PF init sequence that uses DMAE */
	rc = qed_dmae_sanity(p_hwfn, p_ptt, "pf_phase");
	अगर (rc)
		वापस rc;

	/* PF Init sequence */
	rc = qed_init_run(p_hwfn, p_ptt, PHASE_PF, rel_pf_id, hw_mode);
	अगर (rc)
		वापस rc;

	/* QM_PF Init sequence (may be invoked separately e.g. क्रम DCB) */
	rc = qed_init_run(p_hwfn, p_ptt, PHASE_QM_PF, rel_pf_id, hw_mode);
	अगर (rc)
		वापस rc;

	qed_fw_overlay_init_ram(p_hwfn, p_ptt, p_hwfn->fw_overlay_mem);

	/* Pure runसमय initializations - directly to the HW  */
	qed_पूर्णांक_igu_init_pure_rt(p_hwfn, p_ptt, true, true);

	rc = qed_hw_init_pf_करोorbell_bar(p_hwfn, p_ptt);
	अगर (rc)
		वापस rc;

	/* Use the leading hwfn since in CMT only NIG #0 is operational */
	अगर (IS_LEAD_HWFN(p_hwfn)) अणु
		rc = qed_llh_hw_init_pf(p_hwfn, p_ptt);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (b_hw_start) अणु
		/* enable पूर्णांकerrupts */
		qed_पूर्णांक_igu_enable(p_hwfn, p_ptt, पूर्णांक_mode);

		/* send function start command */
		rc = qed_sp_pf_start(p_hwfn, p_ptt, p_tunn,
				     allow_npar_tx_चयन);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn, "Function start ramrod failed\n");
			वापस rc;
		पूर्ण
		अगर (p_hwfn->hw_info.personality == QED_PCI_FCOE) अणु
			qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TAG1, BIT(2));
			qed_wr(p_hwfn, p_ptt,
			       PRS_REG_PKT_LEN_STAT_TAGS_NOT_COUNTED_FIRST,
			       0x100);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक qed_pglueb_set_pfid_enable(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ptt *p_ptt, bool b_enable)
अणु
	u32 delay_idx = 0, val, set_val = b_enable ? 1 : 0;

	/* Configure the PF's पूर्णांकernal FID_enable क्रम master transactions */
	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, set_val);

	/* Wait until value is set - try क्रम 1 second every 50us */
	क्रम (delay_idx = 0; delay_idx < 20000; delay_idx++) अणु
		val = qed_rd(p_hwfn, p_ptt,
			     PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER);
		अगर (val == set_val)
			अवरोध;

		usleep_range(50, 60);
	पूर्ण

	अगर (val != set_val) अणु
		DP_NOTICE(p_hwfn,
			  "PFID_ENABLE_MASTER wasn't changed after a second\n");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_reset_mb_shaकरोw(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_मुख्य_ptt)
अणु
	/* Read shaकरोw of current MFW mailbox */
	qed_mcp_पढ़ो_mb(p_hwfn, p_मुख्य_ptt);
	स_नकल(p_hwfn->mcp_info->mfw_mb_shaकरोw,
	       p_hwfn->mcp_info->mfw_mb_cur, p_hwfn->mcp_info->mfw_mb_length);
पूर्ण

अटल व्योम
qed_fill_load_req_params(काष्ठा qed_load_req_params *p_load_req,
			 काष्ठा qed_drv_load_params *p_drv_load)
अणु
	स_रखो(p_load_req, 0, माप(*p_load_req));

	p_load_req->drv_role = p_drv_load->is_crash_kernel ?
			       QED_DRV_ROLE_KDUMP : QED_DRV_ROLE_OS;
	p_load_req->समयout_val = p_drv_load->mfw_समयout_val;
	p_load_req->aव्योम_eng_reset = p_drv_load->aव्योम_eng_reset;
	p_load_req->override_क्रमce_load = p_drv_load->override_क्रमce_load;
पूर्ण

अटल पूर्णांक qed_vf_start(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_hw_init_params *p_params)
अणु
	अगर (p_params->p_tunn) अणु
		qed_vf_set_vf_start_tunn_update_param(p_params->p_tunn);
		qed_vf_pf_tunnel_param_update(p_hwfn, p_params->p_tunn);
	पूर्ण

	p_hwfn->b_पूर्णांक_enabled = true;

	वापस 0;
पूर्ण

अटल व्योम qed_pglueb_clear_err(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_WAS_ERROR_PF_31_0_CLR,
	       BIT(p_hwfn->असल_pf_id));
पूर्ण

पूर्णांक qed_hw_init(काष्ठा qed_dev *cdev, काष्ठा qed_hw_init_params *p_params)
अणु
	काष्ठा qed_load_req_params load_req_params;
	u32 load_code, resp, param, drv_mb_param;
	bool b_शेष_mtu = true;
	काष्ठा qed_hwfn *p_hwfn;
	स्थिर u32 *fw_overlays;
	u32 fw_overlays_len;
	u16 ether_type;
	पूर्णांक rc = 0, i;

	अगर ((p_params->पूर्णांक_mode == QED_INT_MODE_MSI) && (cdev->num_hwfns > 1)) अणु
		DP_NOTICE(cdev, "MSI mode is not supported for CMT devices\n");
		वापस -EINVAL;
	पूर्ण

	अगर (IS_PF(cdev)) अणु
		rc = qed_init_fw_data(cdev, p_params->bin_fw_data);
		अगर (rc)
			वापस rc;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		p_hwfn = &cdev->hwfns[i];

		/* If management didn't provide a शेष, set one of our own */
		अगर (!p_hwfn->hw_info.mtu) अणु
			p_hwfn->hw_info.mtu = 1500;
			b_शेष_mtu = false;
		पूर्ण

		अगर (IS_VF(cdev)) अणु
			qed_vf_start(p_hwfn, p_params);
			जारी;
		पूर्ण

		rc = qed_calc_hw_mode(p_hwfn);
		अगर (rc)
			वापस rc;

		अगर (IS_PF(cdev) && (test_bit(QED_MF_8021Q_TAGGING,
					     &cdev->mf_bits) ||
				    test_bit(QED_MF_8021AD_TAGGING,
					     &cdev->mf_bits))) अणु
			अगर (test_bit(QED_MF_8021Q_TAGGING, &cdev->mf_bits))
				ether_type = ETH_P_8021Q;
			अन्यथा
				ether_type = ETH_P_8021AD;
			STORE_RT_REG(p_hwfn, PRS_REG_TAG_ETHERTYPE_0_RT_OFFSET,
				     ether_type);
			STORE_RT_REG(p_hwfn, NIG_REG_TAG_ETHERTYPE_0_RT_OFFSET,
				     ether_type);
			STORE_RT_REG(p_hwfn, PBF_REG_TAG_ETHERTYPE_0_RT_OFFSET,
				     ether_type);
			STORE_RT_REG(p_hwfn, DORQ_REG_TAG1_ETHERTYPE_RT_OFFSET,
				     ether_type);
		पूर्ण

		qed_fill_load_req_params(&load_req_params,
					 p_params->p_drv_load_params);
		rc = qed_mcp_load_req(p_hwfn, p_hwfn->p_मुख्य_ptt,
				      &load_req_params);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn, "Failed sending a LOAD_REQ command\n");
			वापस rc;
		पूर्ण

		load_code = load_req_params.load_code;
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Load request was sent. Load code: 0x%x\n",
			   load_code);

		/* Only relevant क्रम recovery:
		 * Clear the indication after LOAD_REQ is responded by the MFW.
		 */
		cdev->recov_in_prog = false;

		qed_mcp_set_capabilities(p_hwfn, p_hwfn->p_मुख्य_ptt);

		qed_reset_mb_shaकरोw(p_hwfn, p_hwfn->p_मुख्य_ptt);

		/* Clean up chip from previous driver अगर such reमुख्यs exist.
		 * This is not needed when the PF is the first one on the
		 * engine, since afterwards we are going to init the FW.
		 */
		अगर (load_code != FW_MSG_CODE_DRV_LOAD_ENGINE) अणु
			rc = qed_final_cleanup(p_hwfn, p_hwfn->p_मुख्य_ptt,
					       p_hwfn->rel_pf_id, false);
			अगर (rc) अणु
				qed_hw_err_notअगरy(p_hwfn, p_hwfn->p_मुख्य_ptt,
						  QED_HW_ERR_RAMROD_FAIL,
						  "Final cleanup failed\n");
				जाओ load_err;
			पूर्ण
		पूर्ण

		/* Log and clear previous pglue_b errors अगर such exist */
		qed_pglueb_rbc_attn_handler(p_hwfn, p_hwfn->p_मुख्य_ptt, true);

		/* Enable the PF's पूर्णांकernal FID_enable in the PXP */
		rc = qed_pglueb_set_pfid_enable(p_hwfn, p_hwfn->p_मुख्य_ptt,
						true);
		अगर (rc)
			जाओ load_err;

		/* Clear the pglue_b was_error indication.
		 * In E4 it must be करोne after the BME and the पूर्णांकernal
		 * FID_enable क्रम the PF are set, since VDMs may cause the
		 * indication to be set again.
		 */
		qed_pglueb_clear_err(p_hwfn, p_hwfn->p_मुख्य_ptt);

		fw_overlays = cdev->fw_data->fw_overlays;
		fw_overlays_len = cdev->fw_data->fw_overlays_len;
		p_hwfn->fw_overlay_mem =
		    qed_fw_overlay_mem_alloc(p_hwfn, fw_overlays,
					     fw_overlays_len);
		अगर (!p_hwfn->fw_overlay_mem) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to allocate fw overlay memory\n");
			rc = -ENOMEM;
			जाओ load_err;
		पूर्ण

		चयन (load_code) अणु
		हाल FW_MSG_CODE_DRV_LOAD_ENGINE:
			rc = qed_hw_init_common(p_hwfn, p_hwfn->p_मुख्य_ptt,
						p_hwfn->hw_info.hw_mode);
			अगर (rc)
				अवरोध;
			fallthrough;
		हाल FW_MSG_CODE_DRV_LOAD_PORT:
			rc = qed_hw_init_port(p_hwfn, p_hwfn->p_मुख्य_ptt,
					      p_hwfn->hw_info.hw_mode);
			अगर (rc)
				अवरोध;

			fallthrough;
		हाल FW_MSG_CODE_DRV_LOAD_FUNCTION:
			rc = qed_hw_init_pf(p_hwfn, p_hwfn->p_मुख्य_ptt,
					    p_params->p_tunn,
					    p_hwfn->hw_info.hw_mode,
					    p_params->b_hw_start,
					    p_params->पूर्णांक_mode,
					    p_params->allow_npar_tx_चयन);
			अवरोध;
		शेष:
			DP_NOTICE(p_hwfn,
				  "Unexpected load code [0x%08x]", load_code);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "init phase failed for loadcode 0x%x (rc %d)\n",
				  load_code, rc);
			जाओ load_err;
		पूर्ण

		rc = qed_mcp_load_करोne(p_hwfn, p_hwfn->p_मुख्य_ptt);
		अगर (rc)
			वापस rc;

		/* send DCBX attention request command */
		DP_VERBOSE(p_hwfn,
			   QED_MSG_DCB,
			   "sending phony dcbx set command to trigger DCBx attention handling\n");
		rc = qed_mcp_cmd(p_hwfn, p_hwfn->p_मुख्य_ptt,
				 DRV_MSG_CODE_SET_DCBX,
				 1 << DRV_MB_PARAM_DCBX_NOTIFY_SHIFT,
				 &resp, &param);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to send DCBX attention request\n");
			वापस rc;
		पूर्ण

		p_hwfn->hw_init_करोne = true;
	पूर्ण

	अगर (IS_PF(cdev)) अणु
		p_hwfn = QED_LEADING_HWFN(cdev);

		/* Get pre-negotiated values क्रम stag, bandwidth etc. */
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SPQ,
			   "Sending GET_OEM_UPDATES command to trigger stag/bandwidth attention handling\n");
		drv_mb_param = 1 << DRV_MB_PARAM_DUMMY_OEM_UPDATES_OFFSET;
		rc = qed_mcp_cmd(p_hwfn, p_hwfn->p_मुख्य_ptt,
				 DRV_MSG_CODE_GET_OEM_UPDATES,
				 drv_mb_param, &resp, &param);
		अगर (rc)
			DP_NOTICE(p_hwfn,
				  "Failed to send GET_OEM_UPDATES attention request\n");

		drv_mb_param = STORM_FW_VERSION;
		rc = qed_mcp_cmd(p_hwfn, p_hwfn->p_मुख्य_ptt,
				 DRV_MSG_CODE_OV_UPDATE_STORM_FW_VER,
				 drv_mb_param, &load_code, &param);
		अगर (rc)
			DP_INFO(p_hwfn, "Failed to update firmware version\n");

		अगर (!b_शेष_mtu) अणु
			rc = qed_mcp_ov_update_mtu(p_hwfn, p_hwfn->p_मुख्य_ptt,
						   p_hwfn->hw_info.mtu);
			अगर (rc)
				DP_INFO(p_hwfn,
					"Failed to update default mtu\n");
		पूर्ण

		rc = qed_mcp_ov_update_driver_state(p_hwfn,
						    p_hwfn->p_मुख्य_ptt,
						  QED_OV_DRIVER_STATE_DISABLED);
		अगर (rc)
			DP_INFO(p_hwfn, "Failed to update driver state\n");

		rc = qed_mcp_ov_update_eचयन(p_hwfn, p_hwfn->p_मुख्य_ptt,
					       QED_OV_ESWITCH_NONE);
		अगर (rc)
			DP_INFO(p_hwfn, "Failed to update eswitch mode\n");
	पूर्ण

	वापस 0;

load_err:
	/* The MFW load lock should be released also when initialization fails.
	 */
	qed_mcp_load_करोne(p_hwfn, p_hwfn->p_मुख्य_ptt);
	वापस rc;
पूर्ण

#घोषणा QED_HW_STOP_RETRY_LIMIT (10)
अटल व्योम qed_hw_समयrs_stop(काष्ठा qed_dev *cdev,
			       काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	पूर्णांक i;

	/* बंद समयrs */
	qed_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_CONN, 0x0);
	qed_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_TASK, 0x0);

	अगर (cdev->recov_in_prog)
		वापस;

	क्रम (i = 0; i < QED_HW_STOP_RETRY_LIMIT; i++) अणु
		अगर ((!qed_rd(p_hwfn, p_ptt,
			     TM_REG_PF_SCAN_ACTIVE_CONN)) &&
		    (!qed_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_TASK)))
			अवरोध;

		/* Dependent on number of connection/tasks, possibly
		 * 1ms sleep is required between polls
		 */
		usleep_range(1000, 2000);
	पूर्ण

	अगर (i < QED_HW_STOP_RETRY_LIMIT)
		वापस;

	DP_NOTICE(p_hwfn,
		  "Timers linear scans are not over [Connection %02x Tasks %02x]\n",
		  (u8)qed_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_CONN),
		  (u8)qed_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_TASK));
पूर्ण

व्योम qed_hw_समयrs_stop_all(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक j;

	क्रम_each_hwfn(cdev, j) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[j];
		काष्ठा qed_ptt *p_ptt = p_hwfn->p_मुख्य_ptt;

		qed_hw_समयrs_stop(cdev, p_hwfn, p_ptt);
	पूर्ण
पूर्ण

पूर्णांक qed_hw_stop(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc, rc2 = 0;
	पूर्णांक j;

	क्रम_each_hwfn(cdev, j) अणु
		p_hwfn = &cdev->hwfns[j];
		p_ptt = p_hwfn->p_मुख्य_ptt;

		DP_VERBOSE(p_hwfn, NETIF_MSG_IFDOWN, "Stopping hw/fw\n");

		अगर (IS_VF(cdev)) अणु
			qed_vf_pf_पूर्णांक_cleanup(p_hwfn);
			rc = qed_vf_pf_reset(p_hwfn);
			अगर (rc) अणु
				DP_NOTICE(p_hwfn,
					  "qed_vf_pf_reset failed. rc = %d.\n",
					  rc);
				rc2 = -EINVAL;
			पूर्ण
			जारी;
		पूर्ण

		/* mark the hw as uninitialized... */
		p_hwfn->hw_init_करोne = false;

		/* Send unload command to MCP */
		अगर (!cdev->recov_in_prog) अणु
			rc = qed_mcp_unload_req(p_hwfn, p_ptt);
			अगर (rc) अणु
				DP_NOTICE(p_hwfn,
					  "Failed sending a UNLOAD_REQ command. rc = %d.\n",
					  rc);
				rc2 = -EINVAL;
			पूर्ण
		पूर्ण

		qed_slowpath_irq_sync(p_hwfn);

		/* After this poपूर्णांक no MFW attentions are expected, e.g. prevent
		 * race between pf stop and dcbx pf update.
		 */
		rc = qed_sp_pf_stop(p_hwfn);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to close PF against FW [rc = %d]. Continue to stop HW to prevent illegal host access by the device.\n",
				  rc);
			rc2 = -EINVAL;
		पूर्ण

		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_RX_LLH_BRB_GATE_DNTFWD_PERPF, 0x1);

		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TCP, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_UDP, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_FCOE, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_ROCE, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_OPENFLOW, 0x0);

		qed_hw_समयrs_stop(cdev, p_hwfn, p_ptt);

		/* Disable Attention Generation */
		qed_पूर्णांक_igu_disable_पूर्णांक(p_hwfn, p_ptt);

		qed_wr(p_hwfn, p_ptt, IGU_REG_LEADING_EDGE_LATCH, 0);
		qed_wr(p_hwfn, p_ptt, IGU_REG_TRAILING_EDGE_LATCH, 0);

		qed_पूर्णांक_igu_init_pure_rt(p_hwfn, p_ptt, false, true);

		/* Need to रुको 1ms to guarantee SBs are cleared */
		usleep_range(1000, 2000);

		/* Disable PF in HW blocks */
		qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_DB_ENABLE, 0);
		qed_wr(p_hwfn, p_ptt, QM_REG_PF_EN, 0);

		अगर (IS_LEAD_HWFN(p_hwfn) &&
		    test_bit(QED_MF_LLH_MAC_CLSS, &cdev->mf_bits) &&
		    !QED_IS_FCOE_PERSONALITY(p_hwfn))
			qed_llh_हटाओ_mac_filter(cdev, 0,
						  p_hwfn->hw_info.hw_mac_addr);

		अगर (!cdev->recov_in_prog) अणु
			rc = qed_mcp_unload_करोne(p_hwfn, p_ptt);
			अगर (rc) अणु
				DP_NOTICE(p_hwfn,
					  "Failed sending a UNLOAD_DONE command. rc = %d.\n",
					  rc);
				rc2 = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (IS_PF(cdev) && !cdev->recov_in_prog) अणु
		p_hwfn = QED_LEADING_HWFN(cdev);
		p_ptt = QED_LEADING_HWFN(cdev)->p_मुख्य_ptt;

		/* Clear the PF's पूर्णांकernal FID_enable in the PXP.
		 * In CMT this should only be करोne क्रम first hw-function, and
		 * only after all transactions have stopped क्रम all active
		 * hw-functions.
		 */
		rc = qed_pglueb_set_pfid_enable(p_hwfn, p_ptt, false);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "qed_pglueb_set_pfid_enable() failed. rc = %d.\n",
				  rc);
			rc2 = -EINVAL;
		पूर्ण
	पूर्ण

	वापस rc2;
पूर्ण

पूर्णांक qed_hw_stop_fastpath(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक j;

	क्रम_each_hwfn(cdev, j) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[j];
		काष्ठा qed_ptt *p_ptt;

		अगर (IS_VF(cdev)) अणु
			qed_vf_pf_पूर्णांक_cleanup(p_hwfn);
			जारी;
		पूर्ण
		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt)
			वापस -EAGAIN;

		DP_VERBOSE(p_hwfn,
			   NETIF_MSG_IFDOWN, "Shutting down the fastpath\n");

		qed_wr(p_hwfn, p_ptt,
		       NIG_REG_RX_LLH_BRB_GATE_DNTFWD_PERPF, 0x1);

		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TCP, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_UDP, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_FCOE, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_ROCE, 0x0);
		qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_OPENFLOW, 0x0);

		qed_पूर्णांक_igu_init_pure_rt(p_hwfn, p_ptt, false, false);

		/* Need to रुको 1ms to guarantee SBs are cleared */
		usleep_range(1000, 2000);
		qed_ptt_release(p_hwfn, p_ptt);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_hw_start_fastpath(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ptt *p_ptt;

	अगर (IS_VF(p_hwfn->cdev))
		वापस 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (p_hwfn->p_rdma_info &&
	    p_hwfn->p_rdma_info->active && p_hwfn->b_rdma_enabled_in_prs)
		qed_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 0x1);

	/* Re-खोलो incoming traffic */
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_LLH_BRB_GATE_DNTFWD_PERPF, 0x0);
	qed_ptt_release(p_hwfn, p_ptt);

	वापस 0;
पूर्ण

/* Free hwfn memory and resources acquired in hw_hwfn_prepare */
अटल व्योम qed_hw_hwfn_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_ptt_pool_मुक्त(p_hwfn);
	kमुक्त(p_hwfn->hw_info.p_igu_info);
	p_hwfn->hw_info.p_igu_info = शून्य;
पूर्ण

/* Setup bar access */
अटल व्योम qed_hw_hwfn_prepare(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* clear indirect access */
	अगर (QED_IS_AH(p_hwfn->cdev)) अणु
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_E8_F0_K2, 0);
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_EC_F0_K2, 0);
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_F0_F0_K2, 0);
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_F4_F0_K2, 0);
	पूर्ण अन्यथा अणु
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_88_F0_BB, 0);
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_8C_F0_BB, 0);
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_90_F0_BB, 0);
		qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
		       PGLUE_B_REG_PGL_ADDR_94_F0_BB, 0);
	पूर्ण

	/* Clean previous pglue_b errors अगर such exist */
	qed_pglueb_clear_err(p_hwfn, p_hwfn->p_मुख्य_ptt);

	/* enable पूर्णांकernal target-पढ़ो */
	qed_wr(p_hwfn, p_hwfn->p_मुख्य_ptt,
	       PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ, 1);
पूर्ण

अटल व्योम get_function_id(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* ME Register */
	p_hwfn->hw_info.opaque_fid = (u16) REG_RD(p_hwfn,
						  PXP_PF_ME_OPAQUE_ADDR);

	p_hwfn->hw_info.concrete_fid = REG_RD(p_hwfn, PXP_PF_ME_CONCRETE_ADDR);

	p_hwfn->असल_pf_id = (p_hwfn->hw_info.concrete_fid >> 16) & 0xf;
	p_hwfn->rel_pf_id = GET_FIELD(p_hwfn->hw_info.concrete_fid,
				      PXP_CONCRETE_FID_PFID);
	p_hwfn->port_id = GET_FIELD(p_hwfn->hw_info.concrete_fid,
				    PXP_CONCRETE_FID_PORT);

	DP_VERBOSE(p_hwfn, NETIF_MSG_PROBE,
		   "Read ME register: Concrete 0x%08x Opaque 0x%04x\n",
		   p_hwfn->hw_info.concrete_fid, p_hwfn->hw_info.opaque_fid);
पूर्ण

अटल व्योम qed_hw_set_feat(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 *feat_num = p_hwfn->hw_info.feat_num;
	काष्ठा qed_sb_cnt_info sb_cnt;
	u32 non_l2_sbs = 0;

	स_रखो(&sb_cnt, 0, माप(sb_cnt));
	qed_पूर्णांक_get_num_sbs(p_hwfn, &sb_cnt);

	अगर (IS_ENABLED(CONFIG_QED_RDMA) &&
	    QED_IS_RDMA_PERSONALITY(p_hwfn)) अणु
		/* Roce CNQ each requires: 1 status block + 1 CNQ. We भागide
		 * the status blocks equally between L2 / RoCE but with
		 * consideration as to how many l2 queues / cnqs we have.
		 */
		feat_num[QED_RDMA_CNQ] =
			min_t(u32, sb_cnt.cnt / 2,
			      RESC_NUM(p_hwfn, QED_RDMA_CNQ_RAM));

		non_l2_sbs = feat_num[QED_RDMA_CNQ];
	पूर्ण
	अगर (QED_IS_L2_PERSONALITY(p_hwfn)) अणु
		/* Start by allocating VF queues, then PF's */
		feat_num[QED_VF_L2_QUE] = min_t(u32,
						RESC_NUM(p_hwfn, QED_L2_QUEUE),
						sb_cnt.iov_cnt);
		feat_num[QED_PF_L2_QUE] = min_t(u32,
						sb_cnt.cnt - non_l2_sbs,
						RESC_NUM(p_hwfn,
							 QED_L2_QUEUE) -
						FEAT_NUM(p_hwfn,
							 QED_VF_L2_QUE));
	पूर्ण

	अगर (QED_IS_FCOE_PERSONALITY(p_hwfn))
		feat_num[QED_FCOE_CQ] =  min_t(u32, sb_cnt.cnt,
					       RESC_NUM(p_hwfn,
							QED_CMDQS_CQS));

	अगर (QED_IS_ISCSI_PERSONALITY(p_hwfn))
		feat_num[QED_ISCSI_CQ] = min_t(u32, sb_cnt.cnt,
					       RESC_NUM(p_hwfn,
							QED_CMDQS_CQS));
	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_PROBE,
		   "#PF_L2_QUEUES=%d VF_L2_QUEUES=%d #ROCE_CNQ=%d FCOE_CQ=%d ISCSI_CQ=%d #SBS=%d\n",
		   (पूर्णांक)FEAT_NUM(p_hwfn, QED_PF_L2_QUE),
		   (पूर्णांक)FEAT_NUM(p_hwfn, QED_VF_L2_QUE),
		   (पूर्णांक)FEAT_NUM(p_hwfn, QED_RDMA_CNQ),
		   (पूर्णांक)FEAT_NUM(p_hwfn, QED_FCOE_CQ),
		   (पूर्णांक)FEAT_NUM(p_hwfn, QED_ISCSI_CQ),
		   (पूर्णांक)sb_cnt.cnt);
पूर्ण

स्थिर अक्षर *qed_hw_get_resc_name(क्रमागत qed_resources res_id)
अणु
	चयन (res_id) अणु
	हाल QED_L2_QUEUE:
		वापस "L2_QUEUE";
	हाल QED_VPORT:
		वापस "VPORT";
	हाल QED_RSS_ENG:
		वापस "RSS_ENG";
	हाल QED_PQ:
		वापस "PQ";
	हाल QED_RL:
		वापस "RL";
	हाल QED_MAC:
		वापस "MAC";
	हाल QED_VLAN:
		वापस "VLAN";
	हाल QED_RDMA_CNQ_RAM:
		वापस "RDMA_CNQ_RAM";
	हाल QED_ILT:
		वापस "ILT";
	हाल QED_LL2_RAM_QUEUE:
		वापस "LL2_RAM_QUEUE";
	हाल QED_LL2_CTX_QUEUE:
		वापस "LL2_CTX_QUEUE";
	हाल QED_CMDQS_CQS:
		वापस "CMDQS_CQS";
	हाल QED_RDMA_STATS_QUEUE:
		वापस "RDMA_STATS_QUEUE";
	हाल QED_BDQ:
		वापस "BDQ";
	हाल QED_SB:
		वापस "SB";
	शेष:
		वापस "UNKNOWN_RESOURCE";
	पूर्ण
पूर्ण

अटल पूर्णांक
__qed_hw_set_soft_resc_size(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt,
			    क्रमागत qed_resources res_id,
			    u32 resc_max_val, u32 *p_mcp_resp)
अणु
	पूर्णांक rc;

	rc = qed_mcp_set_resc_max_val(p_hwfn, p_ptt, res_id,
				      resc_max_val, p_mcp_resp);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn,
			  "MFW response failure for a max value setting of resource %d [%s]\n",
			  res_id, qed_hw_get_resc_name(res_id));
		वापस rc;
	पूर्ण

	अगर (*p_mcp_resp != FW_MSG_CODE_RESOURCE_ALLOC_OK)
		DP_INFO(p_hwfn,
			"Failed to set the max value of resource %d [%s]. mcp_resp = 0x%08x.\n",
			res_id, qed_hw_get_resc_name(res_id), *p_mcp_resp);

	वापस 0;
पूर्ण

अटल u32 qed_hsi_def_val[][MAX_CHIP_IDS] = अणु
	अणुMAX_NUM_VFS_BB, MAX_NUM_VFS_K2पूर्ण,
	अणुMAX_NUM_L2_QUEUES_BB, MAX_NUM_L2_QUEUES_K2पूर्ण,
	अणुMAX_NUM_PORTS_BB, MAX_NUM_PORTS_K2पूर्ण,
	अणुMAX_SB_PER_PATH_BB, MAX_SB_PER_PATH_K2,पूर्ण,
	अणुMAX_NUM_PFS_BB, MAX_NUM_PFS_K2पूर्ण,
	अणुMAX_NUM_VPORTS_BB, MAX_NUM_VPORTS_K2पूर्ण,
	अणुETH_RSS_ENGINE_NUM_BB, ETH_RSS_ENGINE_NUM_K2पूर्ण,
	अणुMAX_QM_TX_QUEUES_BB, MAX_QM_TX_QUEUES_K2पूर्ण,
	अणुPXP_NUM_ILT_RECORDS_BB, PXP_NUM_ILT_RECORDS_K2पूर्ण,
	अणुRDMA_NUM_STATISTIC_COUNTERS_BB, RDMA_NUM_STATISTIC_COUNTERS_K2पूर्ण,
	अणुMAX_QM_GLOBAL_RLS, MAX_QM_GLOBAL_RLSपूर्ण,
	अणुPBF_MAX_CMD_LINES, PBF_MAX_CMD_LINESपूर्ण,
	अणुBTB_MAX_BLOCKS_BB, BTB_MAX_BLOCKS_K2पूर्ण,
पूर्ण;

u32 qed_get_hsi_def_val(काष्ठा qed_dev *cdev, क्रमागत qed_hsi_def_type type)
अणु
	क्रमागत chip_ids chip_id = QED_IS_BB(cdev) ? CHIP_BB : CHIP_K2;

	अगर (type >= QED_NUM_HSI_DEFS) अणु
		DP_ERR(cdev, "Unexpected HSI definition type [%d]\n", type);
		वापस 0;
	पूर्ण

	वापस qed_hsi_def_val[type][chip_id];
पूर्ण
अटल पूर्णांक
qed_hw_set_soft_resc_size(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 resc_max_val, mcp_resp;
	u8 res_id;
	पूर्णांक rc;
	क्रम (res_id = 0; res_id < QED_MAX_RESC; res_id++) अणु
		चयन (res_id) अणु
		हाल QED_LL2_RAM_QUEUE:
			resc_max_val = MAX_NUM_LL2_RX_RAM_QUEUES;
			अवरोध;
		हाल QED_LL2_CTX_QUEUE:
			resc_max_val = MAX_NUM_LL2_RX_CTX_QUEUES;
			अवरोध;
		हाल QED_RDMA_CNQ_RAM:
			/* No need क्रम a हाल क्रम QED_CMDQS_CQS since
			 * CNQ/CMDQS are the same resource.
			 */
			resc_max_val = NUM_OF_GLOBAL_QUEUES;
			अवरोध;
		हाल QED_RDMA_STATS_QUEUE:
			resc_max_val =
			    NUM_OF_RDMA_STATISTIC_COUNTERS(p_hwfn->cdev);
			अवरोध;
		हाल QED_BDQ:
			resc_max_val = BDQ_NUM_RESOURCES;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		rc = __qed_hw_set_soft_resc_size(p_hwfn, p_ptt, res_id,
						 resc_max_val, &mcp_resp);
		अगर (rc)
			वापस rc;

		/* There's no poपूर्णांक to जारी to the next resource अगर the
		 * command is not supported by the MFW.
		 * We करो जारी अगर the command is supported but the resource
		 * is unknown to the MFW. Such a resource will be later
		 * configured with the शेष allocation values.
		 */
		अगर (mcp_resp == FW_MSG_CODE_UNSUPPORTED)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक qed_hw_get_dflt_resc(काष्ठा qed_hwfn *p_hwfn,
			 क्रमागत qed_resources res_id,
			 u32 *p_resc_num, u32 *p_resc_start)
अणु
	u8 num_funcs = p_hwfn->num_funcs_on_engine;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;

	चयन (res_id) अणु
	हाल QED_L2_QUEUE:
		*p_resc_num = NUM_OF_L2_QUEUES(cdev) / num_funcs;
		अवरोध;
	हाल QED_VPORT:
		*p_resc_num = NUM_OF_VPORTS(cdev) / num_funcs;
		अवरोध;
	हाल QED_RSS_ENG:
		*p_resc_num = NUM_OF_RSS_ENGINES(cdev) / num_funcs;
		अवरोध;
	हाल QED_PQ:
		*p_resc_num = NUM_OF_QM_TX_QUEUES(cdev) / num_funcs;
		*p_resc_num &= ~0x7;	/* The granularity of the PQs is 8 */
		अवरोध;
	हाल QED_RL:
		*p_resc_num = NUM_OF_QM_GLOBAL_RLS(cdev) / num_funcs;
		अवरोध;
	हाल QED_MAC:
	हाल QED_VLAN:
		/* Each VFC resource can accommodate both a MAC and a VLAN */
		*p_resc_num = ETH_NUM_MAC_FILTERS / num_funcs;
		अवरोध;
	हाल QED_ILT:
		*p_resc_num = NUM_OF_PXP_ILT_RECORDS(cdev) / num_funcs;
		अवरोध;
	हाल QED_LL2_RAM_QUEUE:
		*p_resc_num = MAX_NUM_LL2_RX_RAM_QUEUES / num_funcs;
		अवरोध;
	हाल QED_LL2_CTX_QUEUE:
		*p_resc_num = MAX_NUM_LL2_RX_CTX_QUEUES / num_funcs;
		अवरोध;
	हाल QED_RDMA_CNQ_RAM:
	हाल QED_CMDQS_CQS:
		/* CNQ/CMDQS are the same resource */
		*p_resc_num = NUM_OF_GLOBAL_QUEUES / num_funcs;
		अवरोध;
	हाल QED_RDMA_STATS_QUEUE:
		*p_resc_num = NUM_OF_RDMA_STATISTIC_COUNTERS(cdev) / num_funcs;
		अवरोध;
	हाल QED_BDQ:
		अगर (p_hwfn->hw_info.personality != QED_PCI_ISCSI &&
		    p_hwfn->hw_info.personality != QED_PCI_FCOE)
			*p_resc_num = 0;
		अन्यथा
			*p_resc_num = 1;
		अवरोध;
	हाल QED_SB:
		/* Since we want its value to reflect whether MFW supports
		 * the new scheme, have a शेष of 0.
		 */
		*p_resc_num = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (res_id) अणु
	हाल QED_BDQ:
		अगर (!*p_resc_num)
			*p_resc_start = 0;
		अन्यथा अगर (p_hwfn->cdev->num_ports_in_engine == 4)
			*p_resc_start = p_hwfn->port_id;
		अन्यथा अगर (p_hwfn->hw_info.personality == QED_PCI_ISCSI)
			*p_resc_start = p_hwfn->port_id;
		अन्यथा अगर (p_hwfn->hw_info.personality == QED_PCI_FCOE)
			*p_resc_start = p_hwfn->port_id + 2;
		अवरोध;
	शेष:
		*p_resc_start = *p_resc_num * p_hwfn->enabled_func_idx;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __qed_hw_set_resc_info(काष्ठा qed_hwfn *p_hwfn,
				  क्रमागत qed_resources res_id)
अणु
	u32 dflt_resc_num = 0, dflt_resc_start = 0;
	u32 mcp_resp, *p_resc_num, *p_resc_start;
	पूर्णांक rc;

	p_resc_num = &RESC_NUM(p_hwfn, res_id);
	p_resc_start = &RESC_START(p_hwfn, res_id);

	rc = qed_hw_get_dflt_resc(p_hwfn, res_id, &dflt_resc_num,
				  &dflt_resc_start);
	अगर (rc) अणु
		DP_ERR(p_hwfn,
		       "Failed to get default amount for resource %d [%s]\n",
		       res_id, qed_hw_get_resc_name(res_id));
		वापस rc;
	पूर्ण

	rc = qed_mcp_get_resc_info(p_hwfn, p_hwfn->p_मुख्य_ptt, res_id,
				   &mcp_resp, p_resc_num, p_resc_start);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn,
			  "MFW response failure for an allocation request for resource %d [%s]\n",
			  res_id, qed_hw_get_resc_name(res_id));
		वापस rc;
	पूर्ण

	/* Default driver values are applied in the following हालs:
	 * - The resource allocation MB command is not supported by the MFW
	 * - There is an पूर्णांकernal error in the MFW जबतक processing the request
	 * - The resource ID is unknown to the MFW
	 */
	अगर (mcp_resp != FW_MSG_CODE_RESOURCE_ALLOC_OK) अणु
		DP_INFO(p_hwfn,
			"Failed to receive allocation info for resource %d [%s]. mcp_resp = 0x%x. Applying default values [%d,%d].\n",
			res_id,
			qed_hw_get_resc_name(res_id),
			mcp_resp, dflt_resc_num, dflt_resc_start);
		*p_resc_num = dflt_resc_num;
		*p_resc_start = dflt_resc_start;
		जाओ out;
	पूर्ण

out:
	/* PQs have to भागide by 8 [that's the HW granularity].
	 * Reduce number so it would fit.
	 */
	अगर ((res_id == QED_PQ) && ((*p_resc_num % 8) || (*p_resc_start % 8))) अणु
		DP_INFO(p_hwfn,
			"PQs need to align by 8; Number %08x --> %08x, Start %08x --> %08x\n",
			*p_resc_num,
			(*p_resc_num) & ~0x7,
			*p_resc_start, (*p_resc_start) & ~0x7);
		*p_resc_num &= ~0x7;
		*p_resc_start &= ~0x7;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_hw_set_resc_info(काष्ठा qed_hwfn *p_hwfn)
अणु
	पूर्णांक rc;
	u8 res_id;

	क्रम (res_id = 0; res_id < QED_MAX_RESC; res_id++) अणु
		rc = __qed_hw_set_resc_info(p_hwfn, res_id);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_hw_get_ppfid_biपंचांगap(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u8 native_ppfid_idx;
	पूर्णांक rc;

	/* Calculation of BB/AH is dअगरferent क्रम native_ppfid_idx */
	अगर (QED_IS_BB(cdev))
		native_ppfid_idx = p_hwfn->rel_pf_id;
	अन्यथा
		native_ppfid_idx = p_hwfn->rel_pf_id /
		    cdev->num_ports_in_engine;

	rc = qed_mcp_get_ppfid_biपंचांगap(p_hwfn, p_ptt);
	अगर (rc != 0 && rc != -EOPNOTSUPP)
		वापस rc;
	अन्यथा अगर (rc == -EOPNOTSUPP)
		cdev->ppfid_biपंचांगap = 0x1 << native_ppfid_idx;

	अगर (!(cdev->ppfid_biपंचांगap & (0x1 << native_ppfid_idx))) अणु
		DP_INFO(p_hwfn,
			"Fix the PPFID bitmap to include the native PPFID [native_ppfid_idx %hhd, orig_bitmap 0x%hhx]\n",
			native_ppfid_idx, cdev->ppfid_biपंचांगap);
		cdev->ppfid_biपंचांगap = 0x1 << native_ppfid_idx;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_hw_get_resc(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_resc_unlock_params resc_unlock_params;
	काष्ठा qed_resc_lock_params resc_lock_params;
	bool b_ah = QED_IS_AH(p_hwfn->cdev);
	u8 res_id;
	पूर्णांक rc;

	/* Setting the max values of the soft resources and the following
	 * resources allocation queries should be atomic. Since several PFs can
	 * run in parallel - a resource lock is needed.
	 * If either the resource lock or resource set value commands are not
	 * supported - skip the the max values setting, release the lock अगर
	 * needed, and proceed to the queries. Other failures, including a
	 * failure to acquire the lock, will cause this function to fail.
	 */
	qed_mcp_resc_lock_शेष_init(&resc_lock_params, &resc_unlock_params,
				       QED_RESC_LOCK_RESC_ALLOC, false);

	rc = qed_mcp_resc_lock(p_hwfn, p_ptt, &resc_lock_params);
	अगर (rc && rc != -EINVAL) अणु
		वापस rc;
	पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
		DP_INFO(p_hwfn,
			"Skip the max values setting of the soft resources since the resource lock is not supported by the MFW\n");
	पूर्ण अन्यथा अगर (!rc && !resc_lock_params.b_granted) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to acquire the resource lock for the resource allocation commands\n");
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		rc = qed_hw_set_soft_resc_size(p_hwfn, p_ptt);
		अगर (rc && rc != -EINVAL) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to set the max values of the soft resources\n");
			जाओ unlock_and_निकास;
		पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
			DP_INFO(p_hwfn,
				"Skip the max values setting of the soft resources since it is not supported by the MFW\n");
			rc = qed_mcp_resc_unlock(p_hwfn, p_ptt,
						 &resc_unlock_params);
			अगर (rc)
				DP_INFO(p_hwfn,
					"Failed to release the resource lock for the resource allocation commands\n");
		पूर्ण
	पूर्ण

	rc = qed_hw_set_resc_info(p_hwfn);
	अगर (rc)
		जाओ unlock_and_निकास;

	अगर (resc_lock_params.b_granted && !resc_unlock_params.b_released) अणु
		rc = qed_mcp_resc_unlock(p_hwfn, p_ptt, &resc_unlock_params);
		अगर (rc)
			DP_INFO(p_hwfn,
				"Failed to release the resource lock for the resource allocation commands\n");
	पूर्ण

	/* PPFID biपंचांगap */
	अगर (IS_LEAD_HWFN(p_hwfn)) अणु
		rc = qed_hw_get_ppfid_biपंचांगap(p_hwfn, p_ptt);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Sanity क्रम ILT */
	अगर ((b_ah && (RESC_END(p_hwfn, QED_ILT) > PXP_NUM_ILT_RECORDS_K2)) ||
	    (!b_ah && (RESC_END(p_hwfn, QED_ILT) > PXP_NUM_ILT_RECORDS_BB))) अणु
		DP_NOTICE(p_hwfn, "Can't assign ILT pages [%08x,...,%08x]\n",
			  RESC_START(p_hwfn, QED_ILT),
			  RESC_END(p_hwfn, QED_ILT) - 1);
		वापस -EINVAL;
	पूर्ण

	/* This will also learn the number of SBs from MFW */
	अगर (qed_पूर्णांक_igu_reset_cam(p_hwfn, p_ptt))
		वापस -EINVAL;

	qed_hw_set_feat(p_hwfn);

	क्रम (res_id = 0; res_id < QED_MAX_RESC; res_id++)
		DP_VERBOSE(p_hwfn, NETIF_MSG_PROBE, "%s = %d start = %d\n",
			   qed_hw_get_resc_name(res_id),
			   RESC_NUM(p_hwfn, res_id),
			   RESC_START(p_hwfn, res_id));

	वापस 0;

unlock_and_निकास:
	अगर (resc_lock_params.b_granted && !resc_unlock_params.b_released)
		qed_mcp_resc_unlock(p_hwfn, p_ptt, &resc_unlock_params);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_hw_get_nvm_info(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 port_cfg_addr, link_temp, nvm_cfg_addr, device_capabilities, fld;
	u32 nvm_cfg1_offset, mf_mode, addr, generic_cont0, core_cfg;
	काष्ठा qed_mcp_link_speed_params *ext_speed;
	काष्ठा qed_mcp_link_capabilities *p_caps;
	काष्ठा qed_mcp_link_params *link;
	पूर्णांक i;

	/* Read global nvm_cfg address */
	nvm_cfg_addr = qed_rd(p_hwfn, p_ptt, MISC_REG_GEN_PURP_CR0);

	/* Verअगरy MCP has initialized it */
	अगर (!nvm_cfg_addr) अणु
		DP_NOTICE(p_hwfn, "Shared memory not initialized\n");
		वापस -EINVAL;
	पूर्ण

	/* Read nvm_cfg1  (Notice this is just offset, and not offsize (TBD) */
	nvm_cfg1_offset = qed_rd(p_hwfn, p_ptt, nvm_cfg_addr + 4);

	addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
	       दुरत्व(काष्ठा nvm_cfg1, glob) +
	       दुरत्व(काष्ठा nvm_cfg1_glob, core_cfg);

	core_cfg = qed_rd(p_hwfn, p_ptt, addr);

	चयन ((core_cfg & NVM_CFG1_GLOB_NETWORK_PORT_MODE_MASK) >>
		NVM_CFG1_GLOB_NETWORK_PORT_MODE_OFFSET) अणु
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_2X40G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_2X50G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_1X100G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_4X10G_F:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_4X10G_E:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_BB_4X20G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_1X40G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_2X25G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_2X10G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_1X25G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_4X25G:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_2X50G_R1:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_4X50G_R1:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_1X100G_R2:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_2X100G_R2:
	हाल NVM_CFG1_GLOB_NETWORK_PORT_MODE_AHP_1X100G_R4:
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown port mode in 0x%08x\n", core_cfg);
		अवरोध;
	पूर्ण

	/* Read शेष link configuration */
	link = &p_hwfn->mcp_info->link_input;
	p_caps = &p_hwfn->mcp_info->link_capabilities;
	port_cfg_addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
			दुरत्व(काष्ठा nvm_cfg1, port[MFW_PORT(p_hwfn)]);
	link_temp = qed_rd(p_hwfn, p_ptt,
			   port_cfg_addr +
			   दुरत्व(काष्ठा nvm_cfg1_port, speed_cap_mask));
	link_temp &= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_MASK;
	link->speed.advertised_speeds = link_temp;

	p_caps->speed_capabilities = link->speed.advertised_speeds;

	link_temp = qed_rd(p_hwfn, p_ptt,
			   port_cfg_addr +
			   दुरत्व(काष्ठा nvm_cfg1_port, link_settings));
	चयन ((link_temp & NVM_CFG1_PORT_DRV_LINK_SPEED_MASK) >>
		NVM_CFG1_PORT_DRV_LINK_SPEED_OFFSET) अणु
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_AUTONEG:
		link->speed.स्वतःneg = true;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_1G:
		link->speed.क्रमced_speed = 1000;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_10G:
		link->speed.क्रमced_speed = 10000;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_20G:
		link->speed.क्रमced_speed = 20000;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_25G:
		link->speed.क्रमced_speed = 25000;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_40G:
		link->speed.क्रमced_speed = 40000;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_50G:
		link->speed.क्रमced_speed = 50000;
		अवरोध;
	हाल NVM_CFG1_PORT_DRV_LINK_SPEED_BB_100G:
		link->speed.क्रमced_speed = 100000;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown Speed in 0x%08x\n", link_temp);
	पूर्ण

	p_caps->शेष_speed_स्वतःneg = link->speed.स्वतःneg;

	fld = GET_MFW_FIELD(link_temp, NVM_CFG1_PORT_DRV_FLOW_CONTROL);
	link->छोड़ो.स्वतःneg = !!(fld & NVM_CFG1_PORT_DRV_FLOW_CONTROL_AUTONEG);
	link->छोड़ो.क्रमced_rx = !!(fld & NVM_CFG1_PORT_DRV_FLOW_CONTROL_RX);
	link->छोड़ो.क्रमced_tx = !!(fld & NVM_CFG1_PORT_DRV_FLOW_CONTROL_TX);
	link->loopback_mode = 0;

	अगर (p_hwfn->mcp_info->capabilities &
	    FW_MB_PARAM_FEATURE_SUPPORT_FEC_CONTROL) अणु
		चयन (GET_MFW_FIELD(link_temp,
				      NVM_CFG1_PORT_FEC_FORCE_MODE)) अणु
		हाल NVM_CFG1_PORT_FEC_FORCE_MODE_NONE:
			p_caps->fec_शेष |= QED_FEC_MODE_NONE;
			अवरोध;
		हाल NVM_CFG1_PORT_FEC_FORCE_MODE_FIRECODE:
			p_caps->fec_शेष |= QED_FEC_MODE_FIRECODE;
			अवरोध;
		हाल NVM_CFG1_PORT_FEC_FORCE_MODE_RS:
			p_caps->fec_शेष |= QED_FEC_MODE_RS;
			अवरोध;
		हाल NVM_CFG1_PORT_FEC_FORCE_MODE_AUTO:
			p_caps->fec_शेष |= QED_FEC_MODE_AUTO;
			अवरोध;
		शेष:
			DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
				   "unknown FEC mode in 0x%08x\n", link_temp);
		पूर्ण
	पूर्ण अन्यथा अणु
		p_caps->fec_शेष = QED_FEC_MODE_UNSUPPORTED;
	पूर्ण

	link->fec = p_caps->fec_शेष;

	अगर (p_hwfn->mcp_info->capabilities & FW_MB_PARAM_FEATURE_SUPPORT_EEE) अणु
		link_temp = qed_rd(p_hwfn, p_ptt, port_cfg_addr +
				   दुरत्व(काष्ठा nvm_cfg1_port, ext_phy));
		link_temp &= NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_MASK;
		link_temp >>= NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_OFFSET;
		p_caps->शेष_eee = QED_MCP_EEE_ENABLED;
		link->eee.enable = true;
		चयन (link_temp) अणु
		हाल NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_DISABLED:
			p_caps->शेष_eee = QED_MCP_EEE_DISABLED;
			link->eee.enable = false;
			अवरोध;
		हाल NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_BALANCED:
			p_caps->eee_lpi_समयr = EEE_TX_TIMER_USEC_BALANCED_TIME;
			अवरोध;
		हाल NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_AGGRESSIVE:
			p_caps->eee_lpi_समयr =
			    EEE_TX_TIMER_USEC_AGGRESSIVE_TIME;
			अवरोध;
		हाल NVM_CFG1_PORT_EEE_POWER_SAVING_MODE_LOW_LATENCY:
			p_caps->eee_lpi_समयr = EEE_TX_TIMER_USEC_LATENCY_TIME;
			अवरोध;
		पूर्ण

		link->eee.tx_lpi_समयr = p_caps->eee_lpi_समयr;
		link->eee.tx_lpi_enable = link->eee.enable;
		link->eee.adv_caps = QED_EEE_1G_ADV | QED_EEE_10G_ADV;
	पूर्ण अन्यथा अणु
		p_caps->शेष_eee = QED_MCP_EEE_UNSUPPORTED;
	पूर्ण

	अगर (p_hwfn->mcp_info->capabilities &
	    FW_MB_PARAM_FEATURE_SUPPORT_EXT_SPEED_FEC_CONTROL) अणु
		ext_speed = &link->ext_speed;

		link_temp = qed_rd(p_hwfn, p_ptt,
				   port_cfg_addr +
				   दुरत्व(काष्ठा nvm_cfg1_port,
					    extended_speed));

		fld = GET_MFW_FIELD(link_temp, NVM_CFG1_PORT_EXTENDED_SPEED);
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_AN)
			ext_speed->स्वतःneg = true;

		ext_speed->क्रमced_speed = 0;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_1G)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_1G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_10G)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_10G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_20G)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_20G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_25G)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_25G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_40G)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_40G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_50G_R)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_50G_R;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_50G_R2)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_50G_R2;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_100G_R2)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_100G_R2;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_100G_R4)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_100G_R4;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_EXTND_SPD_100G_P4)
			ext_speed->क्रमced_speed |= QED_EXT_SPEED_100G_P4;

		fld = GET_MFW_FIELD(link_temp,
				    NVM_CFG1_PORT_EXTENDED_SPEED_CAP);

		ext_speed->advertised_speeds = 0;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_RESERVED)
			ext_speed->advertised_speeds |= QED_EXT_SPEED_MASK_RES;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_1G)
			ext_speed->advertised_speeds |= QED_EXT_SPEED_MASK_1G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_10G)
			ext_speed->advertised_speeds |= QED_EXT_SPEED_MASK_10G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_20G)
			ext_speed->advertised_speeds |= QED_EXT_SPEED_MASK_20G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_25G)
			ext_speed->advertised_speeds |= QED_EXT_SPEED_MASK_25G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_40G)
			ext_speed->advertised_speeds |= QED_EXT_SPEED_MASK_40G;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_50G_R)
			ext_speed->advertised_speeds |=
				QED_EXT_SPEED_MASK_50G_R;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_50G_R2)
			ext_speed->advertised_speeds |=
				QED_EXT_SPEED_MASK_50G_R2;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_100G_R2)
			ext_speed->advertised_speeds |=
				QED_EXT_SPEED_MASK_100G_R2;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_100G_R4)
			ext_speed->advertised_speeds |=
				QED_EXT_SPEED_MASK_100G_R4;
		अगर (fld & NVM_CFG1_PORT_EXTENDED_SPEED_CAP_EXTND_SPD_100G_P4)
			ext_speed->advertised_speeds |=
				QED_EXT_SPEED_MASK_100G_P4;

		link_temp = qed_rd(p_hwfn, p_ptt,
				   port_cfg_addr +
				   दुरत्व(काष्ठा nvm_cfg1_port,
					    extended_fec_mode));
		link->ext_fec_mode = link_temp;

		p_caps->शेष_ext_speed_caps = ext_speed->advertised_speeds;
		p_caps->शेष_ext_speed = ext_speed->क्रमced_speed;
		p_caps->शेष_ext_स्वतःneg = ext_speed->स्वतःneg;
		p_caps->शेष_ext_fec = link->ext_fec_mode;

		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Read default extended link config: Speed 0x%08x, Adv. Speed 0x%08x, AN: 0x%02x, FEC: 0x%02x\n",
			   ext_speed->क्रमced_speed,
			   ext_speed->advertised_speeds, ext_speed->स्वतःneg,
			   p_caps->शेष_ext_fec);
	पूर्ण

	DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
		   "Read default link: Speed 0x%08x, Adv. Speed 0x%08x, AN: 0x%02x, PAUSE AN: 0x%02x, EEE: 0x%02x [0x%08x usec], FEC: 0x%02x\n",
		   link->speed.क्रमced_speed, link->speed.advertised_speeds,
		   link->speed.स्वतःneg, link->छोड़ो.स्वतःneg,
		   p_caps->शेष_eee, p_caps->eee_lpi_समयr,
		   p_caps->fec_शेष);

	अगर (IS_LEAD_HWFN(p_hwfn)) अणु
		काष्ठा qed_dev *cdev = p_hwfn->cdev;

		/* Read Multi-function inक्रमmation from shmem */
		addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
		       दुरत्व(काष्ठा nvm_cfg1, glob) +
		       दुरत्व(काष्ठा nvm_cfg1_glob, generic_cont0);

		generic_cont0 = qed_rd(p_hwfn, p_ptt, addr);

		mf_mode = (generic_cont0 & NVM_CFG1_GLOB_MF_MODE_MASK) >>
			  NVM_CFG1_GLOB_MF_MODE_OFFSET;

		चयन (mf_mode) अणु
		हाल NVM_CFG1_GLOB_MF_MODE_MF_ALLOWED:
			cdev->mf_bits = BIT(QED_MF_OVLAN_CLSS);
			अवरोध;
		हाल NVM_CFG1_GLOB_MF_MODE_UFP:
			cdev->mf_bits = BIT(QED_MF_OVLAN_CLSS) |
					BIT(QED_MF_LLH_PROTO_CLSS) |
					BIT(QED_MF_UFP_SPECIFIC) |
					BIT(QED_MF_8021Q_TAGGING) |
					BIT(QED_MF_DONT_ADD_VLAN0_TAG);
			अवरोध;
		हाल NVM_CFG1_GLOB_MF_MODE_BD:
			cdev->mf_bits = BIT(QED_MF_OVLAN_CLSS) |
					BIT(QED_MF_LLH_PROTO_CLSS) |
					BIT(QED_MF_8021AD_TAGGING) |
					BIT(QED_MF_DONT_ADD_VLAN0_TAG);
			अवरोध;
		हाल NVM_CFG1_GLOB_MF_MODE_NPAR1_0:
			cdev->mf_bits = BIT(QED_MF_LLH_MAC_CLSS) |
					BIT(QED_MF_LLH_PROTO_CLSS) |
					BIT(QED_MF_LL2_NON_UNICAST) |
					BIT(QED_MF_INTER_PF_SWITCH) |
					BIT(QED_MF_DISABLE_ARFS);
			अवरोध;
		हाल NVM_CFG1_GLOB_MF_MODE_DEFAULT:
			cdev->mf_bits = BIT(QED_MF_LLH_MAC_CLSS) |
					BIT(QED_MF_LLH_PROTO_CLSS) |
					BIT(QED_MF_LL2_NON_UNICAST);
			अगर (QED_IS_BB(p_hwfn->cdev))
				cdev->mf_bits |= BIT(QED_MF_NEED_DEF_PF);
			अवरोध;
		पूर्ण

		DP_INFO(p_hwfn, "Multi function mode is 0x%lx\n",
			cdev->mf_bits);

		/* In CMT the PF is unknown when the GFS block processes the
		 * packet. Thereक्रमe cannot use searcher as it has a per PF
		 * database, and thus ARFS must be disabled.
		 *
		 */
		अगर (QED_IS_CMT(cdev))
			cdev->mf_bits |= BIT(QED_MF_DISABLE_ARFS);
	पूर्ण

	DP_INFO(p_hwfn, "Multi function mode is 0x%lx\n",
		p_hwfn->cdev->mf_bits);

	/* Read device capabilities inक्रमmation from shmem */
	addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
		दुरत्व(काष्ठा nvm_cfg1, glob) +
		दुरत्व(काष्ठा nvm_cfg1_glob, device_capabilities);

	device_capabilities = qed_rd(p_hwfn, p_ptt, addr);
	अगर (device_capabilities & NVM_CFG1_GLOB_DEVICE_CAPABILITIES_ETHERNET)
		__set_bit(QED_DEV_CAP_ETH,
			  &p_hwfn->hw_info.device_capabilities);
	अगर (device_capabilities & NVM_CFG1_GLOB_DEVICE_CAPABILITIES_FCOE)
		__set_bit(QED_DEV_CAP_FCOE,
			  &p_hwfn->hw_info.device_capabilities);
	अगर (device_capabilities & NVM_CFG1_GLOB_DEVICE_CAPABILITIES_ISCSI)
		__set_bit(QED_DEV_CAP_ISCSI,
			  &p_hwfn->hw_info.device_capabilities);
	अगर (device_capabilities & NVM_CFG1_GLOB_DEVICE_CAPABILITIES_ROCE)
		__set_bit(QED_DEV_CAP_ROCE,
			  &p_hwfn->hw_info.device_capabilities);

	/* Read device serial number inक्रमmation from shmem */
	addr = MCP_REG_SCRATCH + nvm_cfg1_offset +
		दुरत्व(काष्ठा nvm_cfg1, glob) +
		दुरत्व(काष्ठा nvm_cfg1_glob, serial_number);

	क्रम (i = 0; i < 4; i++)
		p_hwfn->hw_info.part_num[i] = qed_rd(p_hwfn, p_ptt, addr + i * 4);

	वापस qed_mcp_fill_shmem_func_info(p_hwfn, p_ptt);
पूर्ण

अटल व्योम qed_get_num_funcs(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u8 num_funcs, enabled_func_idx = p_hwfn->rel_pf_id;
	u32 reg_function_hide, पंचांगp, eng_mask, low_pfs_mask;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;

	num_funcs = QED_IS_AH(cdev) ? MAX_NUM_PFS_K2 : MAX_NUM_PFS_BB;

	/* Bit 0 of MISCS_REG_FUNCTION_HIDE indicates whether the bypass values
	 * in the other bits are selected.
	 * Bits 1-15 are क्रम functions 1-15, respectively, and their value is
	 * '0' only क्रम enabled functions (function 0 always exists and
	 * enabled).
	 * In हाल of CMT, only the "even" functions are enabled, and thus the
	 * number of functions क्रम both hwfns is learnt from the same bits.
	 */
	reg_function_hide = qed_rd(p_hwfn, p_ptt, MISCS_REG_FUNCTION_HIDE);

	अगर (reg_function_hide & 0x1) अणु
		अगर (QED_IS_BB(cdev)) अणु
			अगर (QED_PATH_ID(p_hwfn) && cdev->num_hwfns == 1) अणु
				num_funcs = 0;
				eng_mask = 0xaaaa;
			पूर्ण अन्यथा अणु
				num_funcs = 1;
				eng_mask = 0x5554;
			पूर्ण
		पूर्ण अन्यथा अणु
			num_funcs = 1;
			eng_mask = 0xfffe;
		पूर्ण

		/* Get the number of the enabled functions on the engine */
		पंचांगp = (reg_function_hide ^ 0xffffffff) & eng_mask;
		जबतक (पंचांगp) अणु
			अगर (पंचांगp & 0x1)
				num_funcs++;
			पंचांगp >>= 0x1;
		पूर्ण

		/* Get the PF index within the enabled functions */
		low_pfs_mask = (0x1 << p_hwfn->असल_pf_id) - 1;
		पंचांगp = reg_function_hide & eng_mask & low_pfs_mask;
		जबतक (पंचांगp) अणु
			अगर (पंचांगp & 0x1)
				enabled_func_idx--;
			पंचांगp >>= 0x1;
		पूर्ण
	पूर्ण

	p_hwfn->num_funcs_on_engine = num_funcs;
	p_hwfn->enabled_func_idx = enabled_func_idx;

	DP_VERBOSE(p_hwfn,
		   NETIF_MSG_PROBE,
		   "PF [rel_id %d, abs_id %d] occupies index %d within the %d enabled functions on the engine\n",
		   p_hwfn->rel_pf_id,
		   p_hwfn->असल_pf_id,
		   p_hwfn->enabled_func_idx, p_hwfn->num_funcs_on_engine);
पूर्ण

अटल व्योम qed_hw_info_port_num(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 addr, global_offsize, global_addr, port_mode;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;

	/* In CMT there is always only one port */
	अगर (cdev->num_hwfns > 1) अणु
		cdev->num_ports_in_engine = 1;
		cdev->num_ports = 1;
		वापस;
	पूर्ण

	/* Determine the number of ports per engine */
	port_mode = qed_rd(p_hwfn, p_ptt, MISC_REG_PORT_MODE);
	चयन (port_mode) अणु
	हाल 0x0:
		cdev->num_ports_in_engine = 1;
		अवरोध;
	हाल 0x1:
		cdev->num_ports_in_engine = 2;
		अवरोध;
	हाल 0x2:
		cdev->num_ports_in_engine = 4;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown port mode 0x%08x\n", port_mode);
		cdev->num_ports_in_engine = 1;	/* Default to something */
		अवरोध;
	पूर्ण

	/* Get the total number of ports of the device */
	addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->खुला_base,
				    PUBLIC_GLOBAL);
	global_offsize = qed_rd(p_hwfn, p_ptt, addr);
	global_addr = SECTION_ADDR(global_offsize, 0);
	addr = global_addr + दुरत्व(काष्ठा खुला_global, max_ports);
	cdev->num_ports = (u8)qed_rd(p_hwfn, p_ptt, addr);
पूर्ण

अटल व्योम qed_get_eee_caps(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_link_capabilities *p_caps;
	u32 eee_status;

	p_caps = &p_hwfn->mcp_info->link_capabilities;
	अगर (p_caps->शेष_eee == QED_MCP_EEE_UNSUPPORTED)
		वापस;

	p_caps->eee_speed_caps = 0;
	eee_status = qed_rd(p_hwfn, p_ptt, p_hwfn->mcp_info->port_addr +
			    दुरत्व(काष्ठा खुला_port, eee_status));
	eee_status = (eee_status & EEE_SUPPORTED_SPEED_MASK) >>
			EEE_SUPPORTED_SPEED_OFFSET;

	अगर (eee_status & EEE_1G_SUPPORTED)
		p_caps->eee_speed_caps |= QED_EEE_1G_ADV;
	अगर (eee_status & EEE_10G_ADV)
		p_caps->eee_speed_caps |= QED_EEE_10G_ADV;
पूर्ण

अटल पूर्णांक
qed_get_hw_info(काष्ठा qed_hwfn *p_hwfn,
		काष्ठा qed_ptt *p_ptt,
		क्रमागत qed_pci_personality personality)
अणु
	पूर्णांक rc;

	/* Since all inक्रमmation is common, only first hwfns should करो this */
	अगर (IS_LEAD_HWFN(p_hwfn)) अणु
		rc = qed_iov_hw_info(p_hwfn);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (IS_LEAD_HWFN(p_hwfn))
		qed_hw_info_port_num(p_hwfn, p_ptt);

	qed_mcp_get_capabilities(p_hwfn, p_ptt);

	qed_hw_get_nvm_info(p_hwfn, p_ptt);

	rc = qed_पूर्णांक_igu_पढ़ो_cam(p_hwfn, p_ptt);
	अगर (rc)
		वापस rc;

	अगर (qed_mcp_is_init(p_hwfn))
		ether_addr_copy(p_hwfn->hw_info.hw_mac_addr,
				p_hwfn->mcp_info->func_info.mac);
	अन्यथा
		eth_अक्रमom_addr(p_hwfn->hw_info.hw_mac_addr);

	अगर (qed_mcp_is_init(p_hwfn)) अणु
		अगर (p_hwfn->mcp_info->func_info.ovlan != QED_MCP_VLAN_UNSET)
			p_hwfn->hw_info.ovlan =
				p_hwfn->mcp_info->func_info.ovlan;

		qed_mcp_cmd_port_init(p_hwfn, p_ptt);

		qed_get_eee_caps(p_hwfn, p_ptt);

		qed_mcp_पढ़ो_ufp_config(p_hwfn, p_ptt);
	पूर्ण

	अगर (qed_mcp_is_init(p_hwfn)) अणु
		क्रमागत qed_pci_personality protocol;

		protocol = p_hwfn->mcp_info->func_info.protocol;
		p_hwfn->hw_info.personality = protocol;
	पूर्ण

	अगर (QED_IS_ROCE_PERSONALITY(p_hwfn))
		p_hwfn->hw_info.multi_tc_roce_en = true;

	p_hwfn->hw_info.num_hw_tc = NUM_PHYS_TCS_4PORT_K2;
	p_hwfn->hw_info.num_active_tc = 1;

	qed_get_num_funcs(p_hwfn, p_ptt);

	अगर (qed_mcp_is_init(p_hwfn))
		p_hwfn->hw_info.mtu = p_hwfn->mcp_info->func_info.mtu;

	वापस qed_hw_get_resc(p_hwfn, p_ptt);
पूर्ण

अटल पूर्णांक qed_get_dev_info(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u16 device_id_mask;
	u32 पंचांगp;

	/* Read Venकरोr Id / Device Id */
	pci_पढ़ो_config_word(cdev->pdev, PCI_VENDOR_ID, &cdev->venकरोr_id);
	pci_पढ़ो_config_word(cdev->pdev, PCI_DEVICE_ID, &cdev->device_id);

	/* Determine type */
	device_id_mask = cdev->device_id & QED_DEV_ID_MASK;
	चयन (device_id_mask) अणु
	हाल QED_DEV_ID_MASK_BB:
		cdev->type = QED_DEV_TYPE_BB;
		अवरोध;
	हाल QED_DEV_ID_MASK_AH:
		cdev->type = QED_DEV_TYPE_AH;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unknown device id 0x%x\n", cdev->device_id);
		वापस -EBUSY;
	पूर्ण

	cdev->chip_num = (u16)qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_NUM);
	cdev->chip_rev = (u16)qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_REV);

	MASK_FIELD(CHIP_REV, cdev->chip_rev);

	/* Learn number of HW-functions */
	पंचांगp = qed_rd(p_hwfn, p_ptt, MISCS_REG_CMT_ENABLED_FOR_PAIR);

	अगर (पंचांगp & (1 << p_hwfn->rel_pf_id)) अणु
		DP_NOTICE(cdev->hwfns, "device in CMT mode\n");
		cdev->num_hwfns = 2;
	पूर्ण अन्यथा अणु
		cdev->num_hwfns = 1;
	पूर्ण

	cdev->chip_bond_id = qed_rd(p_hwfn, p_ptt,
				    MISCS_REG_CHIP_TEST_REG) >> 4;
	MASK_FIELD(CHIP_BOND_ID, cdev->chip_bond_id);
	cdev->chip_metal = (u16)qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_METAL);
	MASK_FIELD(CHIP_METAL, cdev->chip_metal);

	DP_INFO(cdev->hwfns,
		"Chip details - %s %c%d, Num: %04x Rev: %04x Bond id: %04x Metal: %04x\n",
		QED_IS_BB(cdev) ? "BB" : "AH",
		'A' + cdev->chip_rev,
		(पूर्णांक)cdev->chip_metal,
		cdev->chip_num, cdev->chip_rev,
		cdev->chip_bond_id, cdev->chip_metal);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_hw_prepare_single(काष्ठा qed_hwfn *p_hwfn,
				 व्योम __iomem *p_regview,
				 व्योम __iomem *p_करोorbells,
				 u64 db_phys_addr,
				 क्रमागत qed_pci_personality personality)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	पूर्णांक rc = 0;

	/* Split PCI bars evenly between hwfns */
	p_hwfn->regview = p_regview;
	p_hwfn->करोorbells = p_करोorbells;
	p_hwfn->db_phys_addr = db_phys_addr;

	अगर (IS_VF(p_hwfn->cdev))
		वापस qed_vf_hw_prepare(p_hwfn);

	/* Validate that chip access is feasible */
	अगर (REG_RD(p_hwfn, PXP_PF_ME_OPAQUE_ADDR) == 0xffffffff) अणु
		DP_ERR(p_hwfn,
		       "Reading the ME register returns all Fs; Preventing further chip access\n");
		वापस -EINVAL;
	पूर्ण

	get_function_id(p_hwfn);

	/* Allocate PTT pool */
	rc = qed_ptt_pool_alloc(p_hwfn);
	अगर (rc)
		जाओ err0;

	/* Allocate the मुख्य PTT */
	p_hwfn->p_मुख्य_ptt = qed_get_reserved_ptt(p_hwfn, RESERVED_PTT_MAIN);

	/* First hwfn learns basic inक्रमmation, e.g., number of hwfns */
	अगर (!p_hwfn->my_id) अणु
		rc = qed_get_dev_info(p_hwfn, p_hwfn->p_मुख्य_ptt);
		अगर (rc)
			जाओ err1;
	पूर्ण

	qed_hw_hwfn_prepare(p_hwfn);

	/* Initialize MCP काष्ठाure */
	rc = qed_mcp_cmd_init(p_hwfn, p_hwfn->p_मुख्य_ptt);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed initializing mcp command\n");
		जाओ err1;
	पूर्ण

	/* Read the device configuration inक्रमmation from the HW and SHMEM */
	rc = qed_get_hw_info(p_hwfn, p_hwfn->p_मुख्य_ptt, personality);
	अगर (rc) अणु
		DP_NOTICE(p_hwfn, "Failed to get HW information\n");
		जाओ err2;
	पूर्ण

	/* Sending a mailbox to the MFW should be करोne after qed_get_hw_info()
	 * is called as it sets the ports number in an engine.
	 */
	अगर (IS_LEAD_HWFN(p_hwfn) && !cdev->recov_in_prog) अणु
		rc = qed_mcp_initiate_pf_flr(p_hwfn, p_hwfn->p_मुख्य_ptt);
		अगर (rc)
			DP_NOTICE(p_hwfn, "Failed to initiate PF FLR\n");
	पूर्ण

	/* NVRAM info initialization and population */
	अगर (IS_LEAD_HWFN(p_hwfn)) अणु
		rc = qed_mcp_nvm_info_populate(p_hwfn);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to populate nvm info shadow\n");
			जाओ err2;
		पूर्ण
	पूर्ण

	/* Allocate the init RT array and initialize the init-ops engine */
	rc = qed_init_alloc(p_hwfn);
	अगर (rc)
		जाओ err3;

	वापस rc;
err3:
	अगर (IS_LEAD_HWFN(p_hwfn))
		qed_mcp_nvm_info_मुक्त(p_hwfn);
err2:
	अगर (IS_LEAD_HWFN(p_hwfn))
		qed_iov_मुक्त_hw_info(p_hwfn->cdev);
	qed_mcp_मुक्त(p_hwfn);
err1:
	qed_hw_hwfn_मुक्त(p_hwfn);
err0:
	वापस rc;
पूर्ण

पूर्णांक qed_hw_prepare(काष्ठा qed_dev *cdev,
		   पूर्णांक personality)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	पूर्णांक rc;

	/* Store the precompiled init data ptrs */
	अगर (IS_PF(cdev))
		qed_init_iro_array(cdev);

	/* Initialize the first hwfn - will learn number of hwfns */
	rc = qed_hw_prepare_single(p_hwfn,
				   cdev->regview,
				   cdev->करोorbells,
				   cdev->db_phys_addr,
				   personality);
	अगर (rc)
		वापस rc;

	personality = p_hwfn->hw_info.personality;

	/* Initialize the rest of the hwfns */
	अगर (cdev->num_hwfns > 1) अणु
		व्योम __iomem *p_regview, *p_करोorbell;
		u64 db_phys_addr;
		u32 offset;

		/* adjust bar offset क्रम second engine */
		offset = qed_hw_bar_size(p_hwfn, p_hwfn->p_मुख्य_ptt,
					 BAR_ID_0) / 2;
		p_regview = cdev->regview + offset;

		offset = qed_hw_bar_size(p_hwfn, p_hwfn->p_मुख्य_ptt,
					 BAR_ID_1) / 2;

		p_करोorbell = cdev->करोorbells + offset;

		db_phys_addr = cdev->db_phys_addr + offset;

		/* prepare second hw function */
		rc = qed_hw_prepare_single(&cdev->hwfns[1], p_regview,
					   p_करोorbell, db_phys_addr,
					   personality);

		/* in हाल of error, need to मुक्त the previously
		 * initiliazed hwfn 0.
		 */
		अगर (rc) अणु
			अगर (IS_PF(cdev)) अणु
				qed_init_मुक्त(p_hwfn);
				qed_mcp_nvm_info_मुक्त(p_hwfn);
				qed_mcp_मुक्त(p_hwfn);
				qed_hw_hwfn_मुक्त(p_hwfn);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

व्योम qed_hw_हटाओ(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	पूर्णांक i;

	अगर (IS_PF(cdev))
		qed_mcp_ov_update_driver_state(p_hwfn, p_hwfn->p_मुख्य_ptt,
					       QED_OV_DRIVER_STATE_NOT_LOADED);

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		अगर (IS_VF(cdev)) अणु
			qed_vf_pf_release(p_hwfn);
			जारी;
		पूर्ण

		qed_init_मुक्त(p_hwfn);
		qed_hw_hwfn_मुक्त(p_hwfn);
		qed_mcp_मुक्त(p_hwfn);
	पूर्ण

	qed_iov_मुक्त_hw_info(cdev);

	qed_mcp_nvm_info_मुक्त(p_hwfn);
पूर्ण

पूर्णांक qed_fw_l2_queue(काष्ठा qed_hwfn *p_hwfn, u16 src_id, u16 *dst_id)
अणु
	अगर (src_id >= RESC_NUM(p_hwfn, QED_L2_QUEUE)) अणु
		u16 min, max;

		min = (u16) RESC_START(p_hwfn, QED_L2_QUEUE);
		max = min + RESC_NUM(p_hwfn, QED_L2_QUEUE);
		DP_NOTICE(p_hwfn,
			  "l2_queue id [%d] is not valid, available indices [%d - %d]\n",
			  src_id, min, max);

		वापस -EINVAL;
	पूर्ण

	*dst_id = RESC_START(p_hwfn, QED_L2_QUEUE) + src_id;

	वापस 0;
पूर्ण

पूर्णांक qed_fw_vport(काष्ठा qed_hwfn *p_hwfn, u8 src_id, u8 *dst_id)
अणु
	अगर (src_id >= RESC_NUM(p_hwfn, QED_VPORT)) अणु
		u8 min, max;

		min = (u8)RESC_START(p_hwfn, QED_VPORT);
		max = min + RESC_NUM(p_hwfn, QED_VPORT);
		DP_NOTICE(p_hwfn,
			  "vport id [%d] is not valid, available indices [%d - %d]\n",
			  src_id, min, max);

		वापस -EINVAL;
	पूर्ण

	*dst_id = RESC_START(p_hwfn, QED_VPORT) + src_id;

	वापस 0;
पूर्ण

पूर्णांक qed_fw_rss_eng(काष्ठा qed_hwfn *p_hwfn, u8 src_id, u8 *dst_id)
अणु
	अगर (src_id >= RESC_NUM(p_hwfn, QED_RSS_ENG)) अणु
		u8 min, max;

		min = (u8)RESC_START(p_hwfn, QED_RSS_ENG);
		max = min + RESC_NUM(p_hwfn, QED_RSS_ENG);
		DP_NOTICE(p_hwfn,
			  "rss_eng id [%d] is not valid, available indices [%d - %d]\n",
			  src_id, min, max);

		वापस -EINVAL;
	पूर्ण

	*dst_id = RESC_START(p_hwfn, QED_RSS_ENG) + src_id;

	वापस 0;
पूर्ण

अटल पूर्णांक qed_set_coalesce(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			    u32 hw_addr, व्योम *p_eth_qzone,
			    माप_प्रकार eth_qzone_size, u8 बारet)
अणु
	काष्ठा coalescing_बारet *p_coal_बारet;

	अगर (p_hwfn->cdev->पूर्णांक_coalescing_mode != QED_COAL_MODE_ENABLE) अणु
		DP_NOTICE(p_hwfn, "Coalescing configuration not enabled\n");
		वापस -EINVAL;
	पूर्ण

	p_coal_बारet = p_eth_qzone;
	स_रखो(p_eth_qzone, 0, eth_qzone_size);
	SET_FIELD(p_coal_बारet->value, COALESCING_TIMESET_TIMESET, बारet);
	SET_FIELD(p_coal_बारet->value, COALESCING_TIMESET_VALID, 1);
	qed_स_नकल_to(p_hwfn, p_ptt, hw_addr, p_eth_qzone, eth_qzone_size);

	वापस 0;
पूर्ण

पूर्णांक qed_set_queue_coalesce(u16 rx_coal, u16 tx_coal, व्योम *p_handle)
अणु
	काष्ठा qed_queue_cid *p_cid = p_handle;
	काष्ठा qed_hwfn *p_hwfn;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0;

	p_hwfn = p_cid->p_owner;

	अगर (IS_VF(p_hwfn->cdev))
		वापस qed_vf_pf_set_coalesce(p_hwfn, rx_coal, tx_coal, p_cid);

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EAGAIN;

	अगर (rx_coal) अणु
		rc = qed_set_rxq_coalesce(p_hwfn, p_ptt, rx_coal, p_cid);
		अगर (rc)
			जाओ out;
		p_hwfn->cdev->rx_coalesce_usecs = rx_coal;
	पूर्ण

	अगर (tx_coal) अणु
		rc = qed_set_txq_coalesce(p_hwfn, p_ptt, tx_coal, p_cid);
		अगर (rc)
			जाओ out;
		p_hwfn->cdev->tx_coalesce_usecs = tx_coal;
	पूर्ण
out:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण

पूर्णांक qed_set_rxq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 u16 coalesce, काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा ustorm_eth_queue_zone eth_qzone;
	u8 बारet, समयr_res;
	u32 address;
	पूर्णांक rc;

	/* Coalesce = (बारet << समयr-resolution), बारet is 7bit wide */
	अगर (coalesce <= 0x7F) अणु
		समयr_res = 0;
	पूर्ण अन्यथा अगर (coalesce <= 0xFF) अणु
		समयr_res = 1;
	पूर्ण अन्यथा अगर (coalesce <= 0x1FF) अणु
		समयr_res = 2;
	पूर्ण अन्यथा अणु
		DP_ERR(p_hwfn, "Invalid coalesce value - %d\n", coalesce);
		वापस -EINVAL;
	पूर्ण
	बारet = (u8)(coalesce >> समयr_res);

	rc = qed_पूर्णांक_set_समयr_res(p_hwfn, p_ptt, समयr_res,
				   p_cid->sb_igu_id, false);
	अगर (rc)
		जाओ out;

	address = BAR0_MAP_REG_USDM_RAM +
		  USTORM_ETH_QUEUE_ZONE_OFFSET(p_cid->असल.queue_id);

	rc = qed_set_coalesce(p_hwfn, p_ptt, address, &eth_qzone,
			      माप(काष्ठा ustorm_eth_queue_zone), बारet);
	अगर (rc)
		जाओ out;

out:
	वापस rc;
पूर्ण

पूर्णांक qed_set_txq_coalesce(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 u16 coalesce, काष्ठा qed_queue_cid *p_cid)
अणु
	काष्ठा xstorm_eth_queue_zone eth_qzone;
	u8 बारet, समयr_res;
	u32 address;
	पूर्णांक rc;

	/* Coalesce = (बारet << समयr-resolution), बारet is 7bit wide */
	अगर (coalesce <= 0x7F) अणु
		समयr_res = 0;
	पूर्ण अन्यथा अगर (coalesce <= 0xFF) अणु
		समयr_res = 1;
	पूर्ण अन्यथा अगर (coalesce <= 0x1FF) अणु
		समयr_res = 2;
	पूर्ण अन्यथा अणु
		DP_ERR(p_hwfn, "Invalid coalesce value - %d\n", coalesce);
		वापस -EINVAL;
	पूर्ण
	बारet = (u8)(coalesce >> समयr_res);

	rc = qed_पूर्णांक_set_समयr_res(p_hwfn, p_ptt, समयr_res,
				   p_cid->sb_igu_id, true);
	अगर (rc)
		जाओ out;

	address = BAR0_MAP_REG_XSDM_RAM +
		  XSTORM_ETH_QUEUE_ZONE_OFFSET(p_cid->असल.queue_id);

	rc = qed_set_coalesce(p_hwfn, p_ptt, address, &eth_qzone,
			      माप(काष्ठा xstorm_eth_queue_zone), बारet);
out:
	वापस rc;
पूर्ण

/* Calculate final WFQ values क्रम all vports and configure them.
 * After this configuration each vport will have
 * approx min rate =  min_pf_rate * (vport_wfq / QED_WFQ_UNIT)
 */
अटल व्योम qed_configure_wfq_क्रम_all_vports(काष्ठा qed_hwfn *p_hwfn,
					     काष्ठा qed_ptt *p_ptt,
					     u32 min_pf_rate)
अणु
	काष्ठा init_qm_vport_params *vport_params;
	पूर्णांक i;

	vport_params = p_hwfn->qm_info.qm_vport_params;

	क्रम (i = 0; i < p_hwfn->qm_info.num_vports; i++) अणु
		u32 wfq_speed = p_hwfn->qm_info.wfq_data[i].min_speed;

		vport_params[i].wfq = (wfq_speed * QED_WFQ_UNIT) /
						min_pf_rate;
		qed_init_vport_wfq(p_hwfn, p_ptt,
				   vport_params[i].first_tx_pq_id,
				   vport_params[i].wfq);
	पूर्ण
पूर्ण

अटल व्योम qed_init_wfq_शेष_param(काष्ठा qed_hwfn *p_hwfn,
				       u32 min_pf_rate)

अणु
	पूर्णांक i;

	क्रम (i = 0; i < p_hwfn->qm_info.num_vports; i++)
		p_hwfn->qm_info.qm_vport_params[i].wfq = 1;
पूर्ण

अटल व्योम qed_disable_wfq_क्रम_all_vports(काष्ठा qed_hwfn *p_hwfn,
					   काष्ठा qed_ptt *p_ptt,
					   u32 min_pf_rate)
अणु
	काष्ठा init_qm_vport_params *vport_params;
	पूर्णांक i;

	vport_params = p_hwfn->qm_info.qm_vport_params;

	क्रम (i = 0; i < p_hwfn->qm_info.num_vports; i++) अणु
		qed_init_wfq_शेष_param(p_hwfn, min_pf_rate);
		qed_init_vport_wfq(p_hwfn, p_ptt,
				   vport_params[i].first_tx_pq_id,
				   vport_params[i].wfq);
	पूर्ण
पूर्ण

/* This function perक्रमms several validations क्रम WFQ
 * configuration and required min rate क्रम a given vport
 * 1. req_rate must be greater than one percent of min_pf_rate.
 * 2. req_rate should not cause other vports [not configured क्रम WFQ explicitly]
 *    rates to get less than one percent of min_pf_rate.
 * 3. total_req_min_rate [all vports min rate sum] shouldn't exceed min_pf_rate.
 */
अटल पूर्णांक qed_init_wfq_param(काष्ठा qed_hwfn *p_hwfn,
			      u16 vport_id, u32 req_rate, u32 min_pf_rate)
अणु
	u32 total_req_min_rate = 0, total_left_rate = 0, left_rate_per_vp = 0;
	पूर्णांक non_requested_count = 0, req_count = 0, i, num_vports;

	num_vports = p_hwfn->qm_info.num_vports;

	/* Accounting क्रम the vports which are configured क्रम WFQ explicitly */
	क्रम (i = 0; i < num_vports; i++) अणु
		u32 पंचांगp_speed;

		अगर ((i != vport_id) &&
		    p_hwfn->qm_info.wfq_data[i].configured) अणु
			req_count++;
			पंचांगp_speed = p_hwfn->qm_info.wfq_data[i].min_speed;
			total_req_min_rate += पंचांगp_speed;
		पूर्ण
	पूर्ण

	/* Include current vport data as well */
	req_count++;
	total_req_min_rate += req_rate;
	non_requested_count = num_vports - req_count;

	अगर (req_rate < min_pf_rate / QED_WFQ_UNIT) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Vport [%d] - Requested rate[%d Mbps] is less than one percent of configured PF min rate[%d Mbps]\n",
			   vport_id, req_rate, min_pf_rate);
		वापस -EINVAL;
	पूर्ण

	अगर (num_vports > QED_WFQ_UNIT) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Number of vports is greater than %d\n",
			   QED_WFQ_UNIT);
		वापस -EINVAL;
	पूर्ण

	अगर (total_req_min_rate > min_pf_rate) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Total requested min rate for all vports[%d Mbps] is greater than configured PF min rate[%d Mbps]\n",
			   total_req_min_rate, min_pf_rate);
		वापस -EINVAL;
	पूर्ण

	total_left_rate	= min_pf_rate - total_req_min_rate;

	left_rate_per_vp = total_left_rate / non_requested_count;
	अगर (left_rate_per_vp <  min_pf_rate / QED_WFQ_UNIT) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
			   "Non WFQ configured vports rate [%d Mbps] is less than one percent of configured PF min rate[%d Mbps]\n",
			   left_rate_per_vp, min_pf_rate);
		वापस -EINVAL;
	पूर्ण

	p_hwfn->qm_info.wfq_data[vport_id].min_speed = req_rate;
	p_hwfn->qm_info.wfq_data[vport_id].configured = true;

	क्रम (i = 0; i < num_vports; i++) अणु
		अगर (p_hwfn->qm_info.wfq_data[i].configured)
			जारी;

		p_hwfn->qm_info.wfq_data[i].min_speed = left_rate_per_vp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __qed_configure_vport_wfq(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt, u16 vp_id, u32 rate)
अणु
	काष्ठा qed_mcp_link_state *p_link;
	पूर्णांक rc = 0;

	p_link = &p_hwfn->cdev->hwfns[0].mcp_info->link_output;

	अगर (!p_link->min_pf_rate) अणु
		p_hwfn->qm_info.wfq_data[vp_id].min_speed = rate;
		p_hwfn->qm_info.wfq_data[vp_id].configured = true;
		वापस rc;
	पूर्ण

	rc = qed_init_wfq_param(p_hwfn, vp_id, rate, p_link->min_pf_rate);

	अगर (!rc)
		qed_configure_wfq_क्रम_all_vports(p_hwfn, p_ptt,
						 p_link->min_pf_rate);
	अन्यथा
		DP_NOTICE(p_hwfn,
			  "Validation failed while configuring min rate\n");

	वापस rc;
पूर्ण

अटल पूर्णांक __qed_configure_vp_wfq_on_link_change(काष्ठा qed_hwfn *p_hwfn,
						 काष्ठा qed_ptt *p_ptt,
						 u32 min_pf_rate)
अणु
	bool use_wfq = false;
	पूर्णांक rc = 0;
	u16 i;

	/* Validate all pre configured vports क्रम wfq */
	क्रम (i = 0; i < p_hwfn->qm_info.num_vports; i++) अणु
		u32 rate;

		अगर (!p_hwfn->qm_info.wfq_data[i].configured)
			जारी;

		rate = p_hwfn->qm_info.wfq_data[i].min_speed;
		use_wfq = true;

		rc = qed_init_wfq_param(p_hwfn, i, rate, min_pf_rate);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn,
				  "WFQ validation failed while configuring min rate\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rc && use_wfq)
		qed_configure_wfq_क्रम_all_vports(p_hwfn, p_ptt, min_pf_rate);
	अन्यथा
		qed_disable_wfq_क्रम_all_vports(p_hwfn, p_ptt, min_pf_rate);

	वापस rc;
पूर्ण

/* Main API क्रम qed clients to configure vport min rate.
 * vp_id - vport id in PF Range[0 - (total_num_vports_per_pf - 1)]
 * rate - Speed in Mbps needs to be asचिन्हित to a given vport.
 */
पूर्णांक qed_configure_vport_wfq(काष्ठा qed_dev *cdev, u16 vp_id, u32 rate)
अणु
	पूर्णांक i, rc = -EINVAL;

	/* Currently not supported; Might change in future */
	अगर (cdev->num_hwfns > 1) अणु
		DP_NOTICE(cdev,
			  "WFQ configuration is not supported for this device\n");
		वापस rc;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		काष्ठा qed_ptt *p_ptt;

		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt)
			वापस -EBUSY;

		rc = __qed_configure_vport_wfq(p_hwfn, p_ptt, vp_id, rate);

		अगर (rc) अणु
			qed_ptt_release(p_hwfn, p_ptt);
			वापस rc;
		पूर्ण

		qed_ptt_release(p_hwfn, p_ptt);
	पूर्ण

	वापस rc;
पूर्ण

/* API to configure WFQ from mcp link change */
व्योम qed_configure_vp_wfq_on_link_change(काष्ठा qed_dev *cdev,
					 काष्ठा qed_ptt *p_ptt, u32 min_pf_rate)
अणु
	पूर्णांक i;

	अगर (cdev->num_hwfns > 1) अणु
		DP_VERBOSE(cdev,
			   NETIF_MSG_LINK,
			   "WFQ configuration is not supported for this device\n");
		वापस;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		__qed_configure_vp_wfq_on_link_change(p_hwfn, p_ptt,
						      min_pf_rate);
	पूर्ण
पूर्ण

पूर्णांक __qed_configure_pf_max_bandwidth(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_mcp_link_state *p_link,
				     u8 max_bw)
अणु
	पूर्णांक rc = 0;

	p_hwfn->mcp_info->func_info.bandwidth_max = max_bw;

	अगर (!p_link->line_speed && (max_bw != 100))
		वापस rc;

	p_link->speed = (p_link->line_speed * max_bw) / 100;
	p_hwfn->qm_info.pf_rl = p_link->speed;

	/* Since the limiter also affects Tx-चयनed traffic, we करोn't want it
	 * to limit such traffic in हाल there's no actual limit.
	 * In that हाल, set limit to imaginary high boundary.
	 */
	अगर (max_bw == 100)
		p_hwfn->qm_info.pf_rl = 100000;

	rc = qed_init_pf_rl(p_hwfn, p_ptt, p_hwfn->rel_pf_id,
			    p_hwfn->qm_info.pf_rl);

	DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
		   "Configured MAX bandwidth to be %08x Mb/sec\n",
		   p_link->speed);

	वापस rc;
पूर्ण

/* Main API to configure PF max bandwidth where bw range is [1 - 100] */
पूर्णांक qed_configure_pf_max_bandwidth(काष्ठा qed_dev *cdev, u8 max_bw)
अणु
	पूर्णांक i, rc = -EINVAL;

	अगर (max_bw < 1 || max_bw > 100) अणु
		DP_NOTICE(cdev, "PF max bw valid range is [1-100]\n");
		वापस rc;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn	*p_hwfn = &cdev->hwfns[i];
		काष्ठा qed_hwfn *p_lead = QED_LEADING_HWFN(cdev);
		काष्ठा qed_mcp_link_state *p_link;
		काष्ठा qed_ptt *p_ptt;

		p_link = &p_lead->mcp_info->link_output;

		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt)
			वापस -EBUSY;

		rc = __qed_configure_pf_max_bandwidth(p_hwfn, p_ptt,
						      p_link, max_bw);

		qed_ptt_release(p_hwfn, p_ptt);

		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक __qed_configure_pf_min_bandwidth(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा qed_mcp_link_state *p_link,
				     u8 min_bw)
अणु
	पूर्णांक rc = 0;

	p_hwfn->mcp_info->func_info.bandwidth_min = min_bw;
	p_hwfn->qm_info.pf_wfq = min_bw;

	अगर (!p_link->line_speed)
		वापस rc;

	p_link->min_pf_rate = (p_link->line_speed * min_bw) / 100;

	rc = qed_init_pf_wfq(p_hwfn, p_ptt, p_hwfn->rel_pf_id, min_bw);

	DP_VERBOSE(p_hwfn, NETIF_MSG_LINK,
		   "Configured MIN bandwidth to be %d Mb/sec\n",
		   p_link->min_pf_rate);

	वापस rc;
पूर्ण

/* Main API to configure PF min bandwidth where bw range is [1-100] */
पूर्णांक qed_configure_pf_min_bandwidth(काष्ठा qed_dev *cdev, u8 min_bw)
अणु
	पूर्णांक i, rc = -EINVAL;

	अगर (min_bw < 1 || min_bw > 100) अणु
		DP_NOTICE(cdev, "PF min bw valid range is [1-100]\n");
		वापस rc;
	पूर्ण

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];
		काष्ठा qed_hwfn *p_lead = QED_LEADING_HWFN(cdev);
		काष्ठा qed_mcp_link_state *p_link;
		काष्ठा qed_ptt *p_ptt;

		p_link = &p_lead->mcp_info->link_output;

		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt)
			वापस -EBUSY;

		rc = __qed_configure_pf_min_bandwidth(p_hwfn, p_ptt,
						      p_link, min_bw);
		अगर (rc) अणु
			qed_ptt_release(p_hwfn, p_ptt);
			वापस rc;
		पूर्ण

		अगर (p_link->min_pf_rate) अणु
			u32 min_rate = p_link->min_pf_rate;

			rc = __qed_configure_vp_wfq_on_link_change(p_hwfn,
								   p_ptt,
								   min_rate);
		पूर्ण

		qed_ptt_release(p_hwfn, p_ptt);
	पूर्ण

	वापस rc;
पूर्ण

व्योम qed_clean_wfq_db(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_mcp_link_state *p_link;

	p_link = &p_hwfn->mcp_info->link_output;

	अगर (p_link->min_pf_rate)
		qed_disable_wfq_क्रम_all_vports(p_hwfn, p_ptt,
					       p_link->min_pf_rate);

	स_रखो(p_hwfn->qm_info.wfq_data, 0,
	       माप(*p_hwfn->qm_info.wfq_data) * p_hwfn->qm_info.num_vports);
पूर्ण

पूर्णांक qed_device_num_ports(काष्ठा qed_dev *cdev)
अणु
	वापस cdev->num_ports;
पूर्ण

व्योम qed_set_fw_mac_addr(__le16 *fw_msb,
			 __le16 *fw_mid, __le16 *fw_lsb, u8 *mac)
अणु
	((u8 *)fw_msb)[0] = mac[1];
	((u8 *)fw_msb)[1] = mac[0];
	((u8 *)fw_mid)[0] = mac[3];
	((u8 *)fw_mid)[1] = mac[2];
	((u8 *)fw_lsb)[0] = mac[5];
	((u8 *)fw_lsb)[1] = mac[4];
पूर्ण
