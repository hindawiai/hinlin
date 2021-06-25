<शैली गुरु>
/*
 * LSI/Engenio/NetApp E-Series RDAC SCSI Device Handler
 *
 * Copyright (C) 2005 Mike Christie. All rights reserved.
 * Copyright (C) Chandra Seetharaman, IBM Corp. 2007
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dh.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा RDAC_NAME "rdac"
#घोषणा RDAC_RETRY_COUNT 5

/*
 * LSI mode page stuff
 *
 * These काष्ठा definitions and the क्रमming of the
 * mode page were taken from the LSI RDAC 2.4 GPL'd
 * driver, and then converted to Linux conventions.
 */
#घोषणा RDAC_QUIESCENCE_TIME 20
/*
 * Page Codes
 */
#घोषणा RDAC_PAGE_CODE_REDUNDANT_CONTROLLER 0x2c

/*
 * Controller modes definitions
 */
#घोषणा RDAC_MODE_TRANSFER_SPECIFIED_LUNS	0x02

/*
 * RDAC Options field
 */
#घोषणा RDAC_FORCED_QUIESENCE 0x02

#घोषणा RDAC_TIMEOUT	(60 * HZ)
#घोषणा RDAC_RETRIES	3

काष्ठा rdac_mode_6_hdr अणु
	u8	data_len;
	u8	medium_type;
	u8	device_params;
	u8	block_desc_len;
पूर्ण;

काष्ठा rdac_mode_10_hdr अणु
	u16	data_len;
	u8	medium_type;
	u8	device_params;
	u16	reserved;
	u16	block_desc_len;
पूर्ण;

काष्ठा rdac_mode_common अणु
	u8	controller_serial[16];
	u8	alt_controller_serial[16];
	u8	rdac_mode[2];
	u8	alt_rdac_mode[2];
	u8	quiescence_समयout;
	u8	rdac_options;
पूर्ण;

काष्ठा rdac_pg_legacy अणु
	काष्ठा rdac_mode_6_hdr hdr;
	u8	page_code;
	u8	page_len;
	काष्ठा rdac_mode_common common;
#घोषणा MODE6_MAX_LUN	32
	u8	lun_table[MODE6_MAX_LUN];
	u8	reserved2[32];
	u8	reserved3;
	u8	reserved4;
पूर्ण;

काष्ठा rdac_pg_expanded अणु
	काष्ठा rdac_mode_10_hdr hdr;
	u8	page_code;
	u8	subpage_code;
	u8	page_len[2];
	काष्ठा rdac_mode_common common;
	u8	lun_table[256];
	u8	reserved3;
	u8	reserved4;
पूर्ण;

काष्ठा c9_inquiry अणु
	u8	peripheral_info;
	u8	page_code;	/* 0xC9 */
	u8	reserved1;
	u8	page_len;
	u8	page_id[4];	/* "vace" */
	u8	avte_cvp;
	u8	path_prio;
	u8	reserved2[38];
पूर्ण;

#घोषणा SUBSYS_ID_LEN	16
#घोषणा SLOT_ID_LEN	2
#घोषणा ARRAY_LABEL_LEN	31

काष्ठा c4_inquiry अणु
	u8	peripheral_info;
	u8	page_code;	/* 0xC4 */
	u8	reserved1;
	u8	page_len;
	u8	page_id[4];	/* "subs" */
	u8	subsys_id[SUBSYS_ID_LEN];
	u8	revision[4];
	u8	slot_id[SLOT_ID_LEN];
	u8	reserved[2];
पूर्ण;

#घोषणा UNIQUE_ID_LEN 16
काष्ठा c8_inquiry अणु
	u8	peripheral_info;
	u8	page_code; /* 0xC8 */
	u8	reserved1;
	u8	page_len;
	u8	page_id[4]; /* "edid" */
	u8	reserved2[3];
	u8	vol_uniq_id_len;
	u8	vol_uniq_id[16];
	u8	vol_user_label_len;
	u8	vol_user_label[60];
	u8	array_uniq_id_len;
	u8	array_unique_id[UNIQUE_ID_LEN];
	u8	array_user_label_len;
	u8	array_user_label[60];
	u8	lun[8];
पूर्ण;

काष्ठा rdac_controller अणु
	u8			array_id[UNIQUE_ID_LEN];
	पूर्णांक			use_ms10;
	काष्ठा kref		kref;
	काष्ठा list_head	node; /* list of all controllers */
	जोड़			अणु
		काष्ठा rdac_pg_legacy legacy;
		काष्ठा rdac_pg_expanded expanded;
	पूर्ण mode_select;
	u8	index;
	u8	array_name[ARRAY_LABEL_LEN];
	काष्ठा Scsi_Host	*host;
	spinlock_t		ms_lock;
	पूर्णांक			ms_queued;
	काष्ठा work_काष्ठा	ms_work;
	काष्ठा scsi_device	*ms_sdev;
	काष्ठा list_head	ms_head;
	काष्ठा list_head	dh_list;
पूर्ण;

काष्ठा c2_inquiry अणु
	u8	peripheral_info;
	u8	page_code;	/* 0xC2 */
	u8	reserved1;
	u8	page_len;
	u8	page_id[4];	/* "swr4" */
	u8	sw_version[3];
	u8	sw_date[3];
	u8	features_enabled;
	u8	max_lun_supported;
	u8	partitions[239]; /* Total allocation length should be 0xFF */
पूर्ण;

काष्ठा rdac_dh_data अणु
	काष्ठा list_head	node;
	काष्ठा rdac_controller	*ctlr;
	काष्ठा scsi_device	*sdev;
#घोषणा UNINITIALIZED_LUN	(1 << 8)
	अचिन्हित		lun;

#घोषणा RDAC_MODE		0
#घोषणा RDAC_MODE_AVT		1
#घोषणा RDAC_MODE_IOSHIP	2
	अचिन्हित अक्षर		mode;

#घोषणा RDAC_STATE_ACTIVE	0
#घोषणा RDAC_STATE_PASSIVE	1
	अचिन्हित अक्षर		state;

#घोषणा RDAC_LUN_UNOWNED	0
#घोषणा RDAC_LUN_OWNED		1
	अक्षर			lun_state;

#घोषणा RDAC_PREFERRED		0
#घोषणा RDAC_NON_PREFERRED	1
	अक्षर			preferred;

	जोड़			अणु
		काष्ठा c2_inquiry c2;
		काष्ठा c4_inquiry c4;
		काष्ठा c8_inquiry c8;
		काष्ठा c9_inquiry c9;
	पूर्ण inq;
पूर्ण;

अटल स्थिर अक्षर *mode[] = अणु
	"RDAC",
	"AVT",
	"IOSHIP",
पूर्ण;
अटल स्थिर अक्षर *lun_state[] =
अणु
	"unowned",
	"owned",
पूर्ण;

काष्ठा rdac_queue_data अणु
	काष्ठा list_head	entry;
	काष्ठा rdac_dh_data	*h;
	activate_complete	callback_fn;
	व्योम			*callback_data;
पूर्ण;

अटल LIST_HEAD(ctlr_list);
अटल DEFINE_SPINLOCK(list_lock);
अटल काष्ठा workqueue_काष्ठा *kmpath_rdacd;
अटल व्योम send_mode_select(काष्ठा work_काष्ठा *work);

/*
 * module parameter to enable rdac debug logging.
 * 2 bits क्रम each type of logging, only two types defined क्रम now
 * Can be enhanced अगर required at later poपूर्णांक
 */
अटल पूर्णांक rdac_logging = 1;
module_param(rdac_logging, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(rdac_logging, "A bit mask of rdac logging levels, "
		"Default is 1 - failover logging enabled, "
		"set it to 0xF to enable all the logs");

#घोषणा RDAC_LOG_FAILOVER	0
#घोषणा RDAC_LOG_SENSE		2

#घोषणा RDAC_LOG_BITS		2

#घोषणा RDAC_LOG_LEVEL(SHIFT)  \
	((rdac_logging >> (SHIFT)) & ((1 << (RDAC_LOG_BITS)) - 1))

#घोषणा RDAC_LOG(SHIFT, sdev, f, arg...) \
करो अणु \
	अगर (unlikely(RDAC_LOG_LEVEL(SHIFT))) \
		sdev_prपूर्णांकk(KERN_INFO, sdev, RDAC_NAME ": " f "\n", ## arg); \
पूर्ण जबतक (0);

अटल अचिन्हित पूर्णांक rdac_failover_get(काष्ठा rdac_controller *ctlr,
				      काष्ठा list_head *list,
				      अचिन्हित अक्षर *cdb)
अणु
	काष्ठा rdac_mode_common *common;
	अचिन्हित data_size;
	काष्ठा rdac_queue_data *qdata;
	u8 *lun_table;

	अगर (ctlr->use_ms10) अणु
		काष्ठा rdac_pg_expanded *rdac_pg;

		data_size = माप(काष्ठा rdac_pg_expanded);
		rdac_pg = &ctlr->mode_select.expanded;
		स_रखो(rdac_pg, 0, data_size);
		common = &rdac_pg->common;
		rdac_pg->page_code = RDAC_PAGE_CODE_REDUNDANT_CONTROLLER + 0x40;
		rdac_pg->subpage_code = 0x1;
		rdac_pg->page_len[0] = 0x01;
		rdac_pg->page_len[1] = 0x28;
		lun_table = rdac_pg->lun_table;
	पूर्ण अन्यथा अणु
		काष्ठा rdac_pg_legacy *rdac_pg;

		data_size = माप(काष्ठा rdac_pg_legacy);
		rdac_pg = &ctlr->mode_select.legacy;
		स_रखो(rdac_pg, 0, data_size);
		common = &rdac_pg->common;
		rdac_pg->page_code = RDAC_PAGE_CODE_REDUNDANT_CONTROLLER;
		rdac_pg->page_len = 0x68;
		lun_table = rdac_pg->lun_table;
	पूर्ण
	common->rdac_mode[1] = RDAC_MODE_TRANSFER_SPECIFIED_LUNS;
	common->quiescence_समयout = RDAC_QUIESCENCE_TIME;
	common->rdac_options = RDAC_FORCED_QUIESENCE;

	list_क्रम_each_entry(qdata, list, entry) अणु
		lun_table[qdata->h->lun] = 0x81;
	पूर्ण

	/* Prepare the command. */
	अगर (ctlr->use_ms10) अणु
		cdb[0] = MODE_SELECT_10;
		cdb[7] = data_size >> 8;
		cdb[8] = data_size & 0xff;
	पूर्ण अन्यथा अणु
		cdb[0] = MODE_SELECT;
		cdb[4] = data_size;
	पूर्ण

	वापस data_size;
पूर्ण

अटल व्योम release_controller(काष्ठा kref *kref)
अणु
	काष्ठा rdac_controller *ctlr;
	ctlr = container_of(kref, काष्ठा rdac_controller, kref);

	list_del(&ctlr->node);
	kमुक्त(ctlr);
पूर्ण

अटल काष्ठा rdac_controller *get_controller(पूर्णांक index, अक्षर *array_name,
			u8 *array_id, काष्ठा scsi_device *sdev)
अणु
	काष्ठा rdac_controller *ctlr, *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &ctlr_list, node) अणु
		अगर ((स_भेद(पंचांगp->array_id, array_id, UNIQUE_ID_LEN) == 0) &&
			  (पंचांगp->index == index) &&
			  (पंचांगp->host == sdev->host)) अणु
			kref_get(&पंचांगp->kref);
			वापस पंचांगp;
		पूर्ण
	पूर्ण
	ctlr = kदो_स्मृति(माप(*ctlr), GFP_ATOMIC);
	अगर (!ctlr)
		वापस शून्य;

	/* initialize fields of controller */
	स_नकल(ctlr->array_id, array_id, UNIQUE_ID_LEN);
	ctlr->index = index;
	ctlr->host = sdev->host;
	स_नकल(ctlr->array_name, array_name, ARRAY_LABEL_LEN);

	kref_init(&ctlr->kref);
	ctlr->use_ms10 = -1;
	ctlr->ms_queued = 0;
	ctlr->ms_sdev = शून्य;
	spin_lock_init(&ctlr->ms_lock);
	INIT_WORK(&ctlr->ms_work, send_mode_select);
	INIT_LIST_HEAD(&ctlr->ms_head);
	list_add(&ctlr->node, &ctlr_list);
	INIT_LIST_HEAD(&ctlr->dh_list);

	वापस ctlr;
पूर्ण

अटल पूर्णांक get_lun_info(काष्ठा scsi_device *sdev, काष्ठा rdac_dh_data *h,
			अक्षर *array_name, u8 *array_id)
अणु
	पूर्णांक err = SCSI_DH_IO, i;
	काष्ठा c8_inquiry *inqp = &h->inq.c8;

	अगर (!scsi_get_vpd_page(sdev, 0xC8, (अचिन्हित अक्षर *)inqp,
			       माप(काष्ठा c8_inquiry))) अणु
		अगर (inqp->page_code != 0xc8)
			वापस SCSI_DH_NOSYS;
		अगर (inqp->page_id[0] != 'e' || inqp->page_id[1] != 'd' ||
		    inqp->page_id[2] != 'i' || inqp->page_id[3] != 'd')
			वापस SCSI_DH_NOSYS;
		h->lun = inqp->lun[7]; /* Uses only the last byte */

		क्रम(i=0; i<ARRAY_LABEL_LEN-1; ++i)
			*(array_name+i) = inqp->array_user_label[(2*i)+1];

		*(array_name+ARRAY_LABEL_LEN-1) = '\0';
		स_रखो(array_id, 0, UNIQUE_ID_LEN);
		स_नकल(array_id, inqp->array_unique_id, inqp->array_uniq_id_len);
		err = SCSI_DH_OK;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक check_ownership(काष्ठा scsi_device *sdev, काष्ठा rdac_dh_data *h)
अणु
	पूर्णांक err = SCSI_DH_IO, access_state;
	काष्ठा rdac_dh_data *पंचांगp;
	काष्ठा c9_inquiry *inqp = &h->inq.c9;

	h->state = RDAC_STATE_ACTIVE;
	अगर (!scsi_get_vpd_page(sdev, 0xC9, (अचिन्हित अक्षर *)inqp,
			       माप(काष्ठा c9_inquiry))) अणु
		/* detect the operating mode */
		अगर ((inqp->avte_cvp >> 5) & 0x1)
			h->mode = RDAC_MODE_IOSHIP; /* LUN in IOSHIP mode */
		अन्यथा अगर (inqp->avte_cvp >> 7)
			h->mode = RDAC_MODE_AVT; /* LUN in AVT mode */
		अन्यथा
			h->mode = RDAC_MODE; /* LUN in RDAC mode */

		/* Update ownership */
		अगर (inqp->avte_cvp & 0x1) अणु
			h->lun_state = RDAC_LUN_OWNED;
			access_state = SCSI_ACCESS_STATE_OPTIMAL;
		पूर्ण अन्यथा अणु
			h->lun_state = RDAC_LUN_UNOWNED;
			अगर (h->mode == RDAC_MODE) अणु
				h->state = RDAC_STATE_PASSIVE;
				access_state = SCSI_ACCESS_STATE_STANDBY;
			पूर्ण अन्यथा
				access_state = SCSI_ACCESS_STATE_ACTIVE;
		पूर्ण

		/* Update path prio*/
		अगर (inqp->path_prio & 0x1) अणु
			h->preferred = RDAC_PREFERRED;
			access_state |= SCSI_ACCESS_STATE_PREFERRED;
		पूर्ण अन्यथा
			h->preferred = RDAC_NON_PREFERRED;
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(पंचांगp, &h->ctlr->dh_list, node) अणु
			/* h->sdev should always be valid */
			BUG_ON(!पंचांगp->sdev);
			पंचांगp->sdev->access_state = access_state;
		पूर्ण
		rcu_पढ़ो_unlock();
		err = SCSI_DH_OK;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक initialize_controller(काष्ठा scsi_device *sdev,
		काष्ठा rdac_dh_data *h, अक्षर *array_name, u8 *array_id)
अणु
	पूर्णांक err = SCSI_DH_IO, index;
	काष्ठा c4_inquiry *inqp = &h->inq.c4;

	अगर (!scsi_get_vpd_page(sdev, 0xC4, (अचिन्हित अक्षर *)inqp,
			       माप(काष्ठा c4_inquiry))) अणु
		/* get the controller index */
		अगर (inqp->slot_id[1] == 0x31)
			index = 0;
		अन्यथा
			index = 1;

		spin_lock(&list_lock);
		h->ctlr = get_controller(index, array_name, array_id, sdev);
		अगर (!h->ctlr)
			err = SCSI_DH_RES_TEMP_UNAVAIL;
		अन्यथा अणु
			list_add_rcu(&h->node, &h->ctlr->dh_list);
			h->sdev = sdev;
		पूर्ण
		spin_unlock(&list_lock);
		err = SCSI_DH_OK;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक set_mode_select(काष्ठा scsi_device *sdev, काष्ठा rdac_dh_data *h)
अणु
	पूर्णांक err = SCSI_DH_IO;
	काष्ठा c2_inquiry *inqp = &h->inq.c2;

	अगर (!scsi_get_vpd_page(sdev, 0xC2, (अचिन्हित अक्षर *)inqp,
			       माप(काष्ठा c2_inquiry))) अणु
		/*
		 * If more than MODE6_MAX_LUN luns are supported, use
		 * mode select 10
		 */
		अगर (inqp->max_lun_supported >= MODE6_MAX_LUN)
			h->ctlr->use_ms10 = 1;
		अन्यथा
			h->ctlr->use_ms10 = 0;
		err = SCSI_DH_OK;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mode_select_handle_sense(काष्ठा scsi_device *sdev,
				    काष्ठा scsi_sense_hdr *sense_hdr)
अणु
	पूर्णांक err = SCSI_DH_IO;
	काष्ठा rdac_dh_data *h = sdev->handler_data;

	अगर (!scsi_sense_valid(sense_hdr))
		जाओ करोne;

	चयन (sense_hdr->sense_key) अणु
	हाल NO_SENSE:
	हाल ABORTED_COMMAND:
	हाल UNIT_ATTENTION:
		err = SCSI_DH_RETRY;
		अवरोध;
	हाल NOT_READY:
		अगर (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x01)
			/* LUN Not Ready and is in the Process of Becoming
			 * Ready
			 */
			err = SCSI_DH_RETRY;
		अवरोध;
	हाल ILLEGAL_REQUEST:
		अगर (sense_hdr->asc == 0x91 && sense_hdr->ascq == 0x36)
			/*
			 * Command Lock contention
			 */
			err = SCSI_DH_IMM_RETRY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	RDAC_LOG(RDAC_LOG_FAILOVER, sdev, "array %s, ctlr %d, "
		"MODE_SELECT returned with sense %02x/%02x/%02x",
		(अक्षर *) h->ctlr->array_name, h->ctlr->index,
		sense_hdr->sense_key, sense_hdr->asc, sense_hdr->ascq);

करोne:
	वापस err;
पूर्ण

अटल व्योम send_mode_select(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rdac_controller *ctlr =
		container_of(work, काष्ठा rdac_controller, ms_work);
	काष्ठा scsi_device *sdev = ctlr->ms_sdev;
	काष्ठा rdac_dh_data *h = sdev->handler_data;
	पूर्णांक err = SCSI_DH_OK, retry_cnt = RDAC_RETRY_COUNT;
	काष्ठा rdac_queue_data *पंचांगp, *qdata;
	LIST_HEAD(list);
	अचिन्हित अक्षर cdb[MAX_COMMAND_SIZE];
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित पूर्णांक data_size;
	u64 req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

	spin_lock(&ctlr->ms_lock);
	list_splice_init(&ctlr->ms_head, &list);
	ctlr->ms_queued = 0;
	ctlr->ms_sdev = शून्य;
	spin_unlock(&ctlr->ms_lock);

 retry:
	स_रखो(cdb, 0, माप(cdb));

	data_size = rdac_failover_get(ctlr, &list, cdb);

	RDAC_LOG(RDAC_LOG_FAILOVER, sdev, "array %s, ctlr %d, "
		"%s MODE_SELECT command",
		(अक्षर *) h->ctlr->array_name, h->ctlr->index,
		(retry_cnt == RDAC_RETRY_COUNT) ? "queueing" : "retrying");

	अगर (scsi_execute(sdev, cdb, DMA_TO_DEVICE, &h->ctlr->mode_select,
			data_size, शून्य, &sshdr, RDAC_TIMEOUT * HZ,
			RDAC_RETRIES, req_flags, 0, शून्य)) अणु
		err = mode_select_handle_sense(sdev, &sshdr);
		अगर (err == SCSI_DH_RETRY && retry_cnt--)
			जाओ retry;
		अगर (err == SCSI_DH_IMM_RETRY)
			जाओ retry;
	पूर्ण
	अगर (err == SCSI_DH_OK) अणु
		h->state = RDAC_STATE_ACTIVE;
		RDAC_LOG(RDAC_LOG_FAILOVER, sdev, "array %s, ctlr %d, "
				"MODE_SELECT completed",
				(अक्षर *) h->ctlr->array_name, h->ctlr->index);
	पूर्ण

	list_क्रम_each_entry_safe(qdata, पंचांगp, &list, entry) अणु
		list_del(&qdata->entry);
		अगर (err == SCSI_DH_OK)
			qdata->h->state = RDAC_STATE_ACTIVE;
		अगर (qdata->callback_fn)
			qdata->callback_fn(qdata->callback_data, err);
		kमुक्त(qdata);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक queue_mode_select(काष्ठा scsi_device *sdev,
				activate_complete fn, व्योम *data)
अणु
	काष्ठा rdac_queue_data *qdata;
	काष्ठा rdac_controller *ctlr;

	qdata = kzalloc(माप(*qdata), GFP_KERNEL);
	अगर (!qdata)
		वापस SCSI_DH_RETRY;

	qdata->h = sdev->handler_data;
	qdata->callback_fn = fn;
	qdata->callback_data = data;

	ctlr = qdata->h->ctlr;
	spin_lock(&ctlr->ms_lock);
	list_add_tail(&qdata->entry, &ctlr->ms_head);
	अगर (!ctlr->ms_queued) अणु
		ctlr->ms_queued = 1;
		ctlr->ms_sdev = sdev;
		queue_work(kmpath_rdacd, &ctlr->ms_work);
	पूर्ण
	spin_unlock(&ctlr->ms_lock);
	वापस SCSI_DH_OK;
पूर्ण

अटल पूर्णांक rdac_activate(काष्ठा scsi_device *sdev,
			activate_complete fn, व्योम *data)
अणु
	काष्ठा rdac_dh_data *h = sdev->handler_data;
	पूर्णांक err = SCSI_DH_OK;
	पूर्णांक act = 0;

	err = check_ownership(sdev, h);
	अगर (err != SCSI_DH_OK)
		जाओ करोne;

	चयन (h->mode) अणु
	हाल RDAC_MODE:
		अगर (h->lun_state == RDAC_LUN_UNOWNED)
			act = 1;
		अवरोध;
	हाल RDAC_MODE_IOSHIP:
		अगर ((h->lun_state == RDAC_LUN_UNOWNED) &&
		    (h->preferred == RDAC_PREFERRED))
			act = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (act) अणु
		err = queue_mode_select(sdev, fn, data);
		अगर (err == SCSI_DH_OK)
			वापस 0;
	पूर्ण
करोne:
	अगर (fn)
		fn(data, err);
	वापस 0;
पूर्ण

अटल blk_status_t rdac_prep_fn(काष्ठा scsi_device *sdev, काष्ठा request *req)
अणु
	काष्ठा rdac_dh_data *h = sdev->handler_data;

	अगर (h->state != RDAC_STATE_ACTIVE) अणु
		req->rq_flags |= RQF_QUIET;
		वापस BLK_STS_IOERR;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल क्रमागत scsi_disposition rdac_check_sense(काष्ठा scsi_device *sdev,
					      काष्ठा scsi_sense_hdr *sense_hdr)
अणु
	काष्ठा rdac_dh_data *h = sdev->handler_data;

	RDAC_LOG(RDAC_LOG_SENSE, sdev, "array %s, ctlr %d, "
			"I/O returned with sense %02x/%02x/%02x",
			(अक्षर *) h->ctlr->array_name, h->ctlr->index,
			sense_hdr->sense_key, sense_hdr->asc, sense_hdr->ascq);

	चयन (sense_hdr->sense_key) अणु
	हाल NOT_READY:
		अगर (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x01)
			/* LUN Not Ready - Logical Unit Not Ready and is in
			* the process of becoming पढ़ोy
			* Just retry.
			*/
			वापस ADD_TO_MLQUEUE;
		अगर (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x81)
			/* LUN Not Ready - Storage firmware incompatible
			 * Manual code synchonisation required.
			 *
			 * Nothing we can करो here. Try to bypass the path.
			 */
			वापस SUCCESS;
		अगर (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0xA1)
			/* LUN Not Ready - Quiescense in progress
			 *
			 * Just retry and रुको.
			 */
			वापस ADD_TO_MLQUEUE;
		अगर (sense_hdr->asc == 0xA1  && sense_hdr->ascq == 0x02)
			/* LUN Not Ready - Quiescense in progress
			 * or has been achieved
			 * Just retry.
			 */
			वापस ADD_TO_MLQUEUE;
		अवरोध;
	हाल ILLEGAL_REQUEST:
		अगर (sense_hdr->asc == 0x94 && sense_hdr->ascq == 0x01) अणु
			/* Invalid Request - Current Logical Unit Ownership.
			 * Controller is not the current owner of the LUN,
			 * Fail the path, so that the other path be used.
			 */
			h->state = RDAC_STATE_PASSIVE;
			वापस SUCCESS;
		पूर्ण
		अवरोध;
	हाल UNIT_ATTENTION:
		अगर (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x00)
			/*
			 * Power On, Reset, or Bus Device Reset, just retry.
			 */
			वापस ADD_TO_MLQUEUE;
		अगर (sense_hdr->asc == 0x8b && sense_hdr->ascq == 0x02)
			/*
			 * Quiescence in progress , just retry.
			 */
			वापस ADD_TO_MLQUEUE;
		अवरोध;
	पूर्ण
	/* success just means we करो not care what scsi-ml करोes */
	वापस SCSI_RETURN_NOT_HANDLED;
पूर्ण

अटल पूर्णांक rdac_bus_attach(काष्ठा scsi_device *sdev)
अणु
	काष्ठा rdac_dh_data *h;
	पूर्णांक err;
	अक्षर array_name[ARRAY_LABEL_LEN];
	अक्षर array_id[UNIQUE_ID_LEN];

	h = kzalloc(माप(*h) , GFP_KERNEL);
	अगर (!h)
		वापस SCSI_DH_NOMEM;
	h->lun = UNINITIALIZED_LUN;
	h->state = RDAC_STATE_ACTIVE;

	err = get_lun_info(sdev, h, array_name, array_id);
	अगर (err != SCSI_DH_OK)
		जाओ failed;

	err = initialize_controller(sdev, h, array_name, array_id);
	अगर (err != SCSI_DH_OK)
		जाओ failed;

	err = check_ownership(sdev, h);
	अगर (err != SCSI_DH_OK)
		जाओ clean_ctlr;

	err = set_mode_select(sdev, h);
	अगर (err != SCSI_DH_OK)
		जाओ clean_ctlr;

	sdev_prपूर्णांकk(KERN_NOTICE, sdev,
		    "%s: LUN %d (%s) (%s)\n",
		    RDAC_NAME, h->lun, mode[(पूर्णांक)h->mode],
		    lun_state[(पूर्णांक)h->lun_state]);

	sdev->handler_data = h;
	वापस SCSI_DH_OK;

clean_ctlr:
	spin_lock(&list_lock);
	kref_put(&h->ctlr->kref, release_controller);
	spin_unlock(&list_lock);

failed:
	kमुक्त(h);
	वापस err;
पूर्ण

अटल व्योम rdac_bus_detach( काष्ठा scsi_device *sdev )
अणु
	काष्ठा rdac_dh_data *h = sdev->handler_data;

	अगर (h->ctlr && h->ctlr->ms_queued)
		flush_workqueue(kmpath_rdacd);

	spin_lock(&list_lock);
	अगर (h->ctlr) अणु
		list_del_rcu(&h->node);
		h->sdev = शून्य;
		kref_put(&h->ctlr->kref, release_controller);
	पूर्ण
	spin_unlock(&list_lock);
	sdev->handler_data = शून्य;
	kमुक्त(h);
पूर्ण

अटल काष्ठा scsi_device_handler rdac_dh = अणु
	.name = RDAC_NAME,
	.module = THIS_MODULE,
	.prep_fn = rdac_prep_fn,
	.check_sense = rdac_check_sense,
	.attach = rdac_bus_attach,
	.detach = rdac_bus_detach,
	.activate = rdac_activate,
पूर्ण;

अटल पूर्णांक __init rdac_init(व्योम)
अणु
	पूर्णांक r;

	r = scsi_रेजिस्टर_device_handler(&rdac_dh);
	अगर (r != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register scsi device handler.");
		जाओ करोne;
	पूर्ण

	/*
	 * Create workqueue to handle mode selects क्रम rdac
	 */
	kmpath_rdacd = create_singlethपढ़ो_workqueue("kmpath_rdacd");
	अगर (!kmpath_rdacd) अणु
		scsi_unरेजिस्टर_device_handler(&rdac_dh);
		prपूर्णांकk(KERN_ERR "kmpath_rdacd creation failed.\n");

		r = -EINVAL;
	पूर्ण
करोne:
	वापस r;
पूर्ण

अटल व्योम __निकास rdac_निकास(व्योम)
अणु
	destroy_workqueue(kmpath_rdacd);
	scsi_unरेजिस्टर_device_handler(&rdac_dh);
पूर्ण

module_init(rdac_init);
module_निकास(rdac_निकास);

MODULE_DESCRIPTION("Multipath LSI/Engenio/NetApp E-Series RDAC driver");
MODULE_AUTHOR("Mike Christie, Chandra Seetharaman");
MODULE_VERSION("01.00.0000.0000");
MODULE_LICENSE("GPL");
