<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SBP2 driver (SCSI over IEEE1394)
 *
 * Copyright (C) 2005-2007  Kristian Hoegsberg <krh@bitplanet.net>
 */

/*
 * The basic काष्ठाure of this driver is based on the old storage driver,
 * drivers/ieee1394/sbp2.c, originally written by
 *     James Goodwin <jamesg@filanet.com>
 * with later contributions and ongoing मुख्यtenance from
 *     Ben Collins <bcollins@debian.org>,
 *     Stefan Richter <stefanr@s5r6.in-berlin.de>
 * and many others.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/bug.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/byteorder.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

/*
 * So far only bridges from Oxक्रमd Semiconductor are known to support
 * concurrent logins. Depending on firmware, four or two concurrent logins
 * are possible on OXFW911 and newer Oxsemi bridges.
 *
 * Concurrent logins are useful together with cluster fileप्रणालीs.
 */
अटल bool sbp2_param_exclusive_login = 1;
module_param_named(exclusive_login, sbp2_param_exclusive_login, bool, 0644);
MODULE_PARM_DESC(exclusive_login, "Exclusive login to sbp2 device "
		 "(default = Y, use N for concurrent initiators)");

/*
 * Flags क्रम firmware oddities
 *
 * - 128kB max transfer
 *   Limit transfer size. Necessary क्रम some old bridges.
 *
 * - 36 byte inquiry
 *   When scsi_mod probes the device, let the inquiry command look like that
 *   from MS Winकरोws.
 *
 * - skip mode page 8
 *   Suppress sending of mode_sense क्रम mode page 8 अगर the device pretends to
 *   support the SCSI Primary Block commands instead of Reduced Block Commands.
 *
 * - fix capacity
 *   Tell sd_mod to correct the last sector number reported by पढ़ो_capacity.
 *   Aव्योमs access beyond actual disk limits on devices with an off-by-one bug.
 *   Don't use this with devices which don't have this bug.
 *
 * - delay inquiry
 *   Wait extra SBP2_INQUIRY_DELAY seconds after login beक्रमe SCSI inquiry.
 *
 * - घातer condition
 *   Set the घातer condition field in the START STOP UNIT commands sent by
 *   sd_mod on suspend, resume, and shutकरोwn (अगर manage_start_stop is on).
 *   Some disks need this to spin करोwn or to resume properly.
 *
 * - override पूर्णांकernal blacklist
 *   Instead of adding to the built-in blacklist, use only the workarounds
 *   specअगरied in the module load parameter.
 *   Useful अगर a blacklist entry पूर्णांकerfered with a non-broken device.
 */
#घोषणा SBP2_WORKAROUND_128K_MAX_TRANS	0x1
#घोषणा SBP2_WORKAROUND_INQUIRY_36	0x2
#घोषणा SBP2_WORKAROUND_MODE_SENSE_8	0x4
#घोषणा SBP2_WORKAROUND_FIX_CAPACITY	0x8
#घोषणा SBP2_WORKAROUND_DELAY_INQUIRY	0x10
#घोषणा SBP2_INQUIRY_DELAY		12
#घोषणा SBP2_WORKAROUND_POWER_CONDITION	0x20
#घोषणा SBP2_WORKAROUND_OVERRIDE	0x100

अटल पूर्णांक sbp2_param_workarounds;
module_param_named(workarounds, sbp2_param_workarounds, पूर्णांक, 0644);
MODULE_PARM_DESC(workarounds, "Work around device bugs (default = 0"
	", 128kB max transfer = " __stringअगरy(SBP2_WORKAROUND_128K_MAX_TRANS)
	", 36 byte inquiry = "    __stringअगरy(SBP2_WORKAROUND_INQUIRY_36)
	", skip mode page 8 = "   __stringअगरy(SBP2_WORKAROUND_MODE_SENSE_8)
	", fix capacity = "       __stringअगरy(SBP2_WORKAROUND_FIX_CAPACITY)
	", delay inquiry = "      __stringअगरy(SBP2_WORKAROUND_DELAY_INQUIRY)
	", set power condition in start stop unit = "
				  __stringअगरy(SBP2_WORKAROUND_POWER_CONDITION)
	", override internal blacklist = " __stringअगरy(SBP2_WORKAROUND_OVERRIDE)
	", or a combination)");

/*
 * We create one काष्ठा sbp2_logical_unit per SBP-2 Logical Unit Number Entry
 * and one काष्ठा scsi_device per sbp2_logical_unit.
 */
काष्ठा sbp2_logical_unit अणु
	काष्ठा sbp2_target *tgt;
	काष्ठा list_head link;
	काष्ठा fw_address_handler address_handler;
	काष्ठा list_head orb_list;

	u64 command_block_agent_address;
	u16 lun;
	पूर्णांक login_id;

	/*
	 * The generation is updated once we've logged in or reconnected
	 * to the logical unit.  Thus, I/O to the device will स्वतःmatically
	 * fail and get retried अगर it happens in a winकरोw where the device
	 * is not पढ़ोy, e.g. after a bus reset but beक्रमe we reconnect.
	 */
	पूर्णांक generation;
	पूर्णांक retries;
	work_func_t workfn;
	काष्ठा delayed_work work;
	bool has_sdev;
	bool blocked;
पूर्ण;

अटल व्योम sbp2_queue_work(काष्ठा sbp2_logical_unit *lu, अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(fw_workqueue, &lu->work, delay);
पूर्ण

/*
 * We create one काष्ठा sbp2_target per IEEE 1212 Unit Directory
 * and one काष्ठा Scsi_Host per sbp2_target.
 */
काष्ठा sbp2_target अणु
	काष्ठा fw_unit *unit;
	काष्ठा list_head lu_list;

	u64 management_agent_address;
	u64 guid;
	पूर्णांक directory_id;
	पूर्णांक node_id;
	पूर्णांक address_high;
	अचिन्हित पूर्णांक workarounds;
	अचिन्हित पूर्णांक mgt_orb_समयout;
	अचिन्हित पूर्णांक max_payload;

	spinlock_t lock;
	पूर्णांक करोnt_block;	/* counter क्रम each logical unit */
	पूर्णांक blocked;	/* ditto */
पूर्ण;

अटल काष्ठा fw_device *target_parent_device(काष्ठा sbp2_target *tgt)
अणु
	वापस fw_parent_device(tgt->unit);
पूर्ण

अटल स्थिर काष्ठा device *tgt_dev(स्थिर काष्ठा sbp2_target *tgt)
अणु
	वापस &tgt->unit->device;
पूर्ण

अटल स्थिर काष्ठा device *lu_dev(स्थिर काष्ठा sbp2_logical_unit *lu)
अणु
	वापस &lu->tgt->unit->device;
पूर्ण

/* Impossible login_id, to detect logout attempt beक्रमe successful login */
#घोषणा INVALID_LOGIN_ID 0x10000

#घोषणा SBP2_ORB_TIMEOUT		2000U		/* Timeout in ms */
#घोषणा SBP2_ORB_शून्य			0x80000000
#घोषणा SBP2_RETRY_LIMIT		0xf		/* 15 retries */
#घोषणा SBP2_CYCLE_LIMIT		(0xc8 << 12)	/* 200 125us cycles */

/*
 * There is no transport protocol limit to the CDB length,  but we implement
 * a fixed length only.  16 bytes is enough क्रम disks larger than 2 TB.
 */
#घोषणा SBP2_MAX_CDB_SIZE		16

/*
 * The maximum SBP-2 data buffer size is 0xffff.  We quadlet-align this
 * क्रम compatibility with earlier versions of this driver.
 */
#घोषणा SBP2_MAX_SEG_SIZE		0xfffc

/* Unit directory keys */
#घोषणा SBP2_CSR_UNIT_CHARACTERISTICS	0x3a
#घोषणा SBP2_CSR_FIRMWARE_REVISION	0x3c
#घोषणा SBP2_CSR_LOGICAL_UNIT_NUMBER	0x14
#घोषणा SBP2_CSR_UNIT_UNIQUE_ID		0x8d
#घोषणा SBP2_CSR_LOGICAL_UNIT_सूचीECTORY	0xd4

/* Management orb opcodes */
#घोषणा SBP2_LOGIN_REQUEST		0x0
#घोषणा SBP2_QUERY_LOGINS_REQUEST	0x1
#घोषणा SBP2_RECONNECT_REQUEST		0x3
#घोषणा SBP2_SET_PASSWORD_REQUEST	0x4
#घोषणा SBP2_LOGOUT_REQUEST		0x7
#घोषणा SBP2_ABORT_TASK_REQUEST		0xb
#घोषणा SBP2_ABORT_TASK_SET		0xc
#घोषणा SBP2_LOGICAL_UNIT_RESET		0xe
#घोषणा SBP2_TARGET_RESET_REQUEST	0xf

/* Offsets क्रम command block agent रेजिस्टरs */
#घोषणा SBP2_AGENT_STATE		0x00
#घोषणा SBP2_AGENT_RESET		0x04
#घोषणा SBP2_ORB_POINTER		0x08
#घोषणा SBP2_DOORBELL			0x10
#घोषणा SBP2_UNSOLICITED_STATUS_ENABLE	0x14

/* Status ग_लिखो response codes */
#घोषणा SBP2_STATUS_REQUEST_COMPLETE	0x0
#घोषणा SBP2_STATUS_TRANSPORT_FAILURE	0x1
#घोषणा SBP2_STATUS_ILLEGAL_REQUEST	0x2
#घोषणा SBP2_STATUS_VENDOR_DEPENDENT	0x3

#घोषणा STATUS_GET_ORB_HIGH(v)		((v).status & 0xffff)
#घोषणा STATUS_GET_SBP_STATUS(v)	(((v).status >> 16) & 0xff)
#घोषणा STATUS_GET_LEN(v)		(((v).status >> 24) & 0x07)
#घोषणा STATUS_GET_DEAD(v)		(((v).status >> 27) & 0x01)
#घोषणा STATUS_GET_RESPONSE(v)		(((v).status >> 28) & 0x03)
#घोषणा STATUS_GET_SOURCE(v)		(((v).status >> 30) & 0x03)
#घोषणा STATUS_GET_ORB_LOW(v)		((v).orb_low)
#घोषणा STATUS_GET_DATA(v)		((v).data)

काष्ठा sbp2_status अणु
	u32 status;
	u32 orb_low;
	u8 data[24];
पूर्ण;

काष्ठा sbp2_poपूर्णांकer अणु
	__be32 high;
	__be32 low;
पूर्ण;

काष्ठा sbp2_orb अणु
	काष्ठा fw_transaction t;
	काष्ठा kref kref;
	dma_addr_t request_bus;
	पूर्णांक rcode;
	व्योम (*callback)(काष्ठा sbp2_orb * orb, काष्ठा sbp2_status * status);
	काष्ठा sbp2_logical_unit *lu;
	काष्ठा list_head link;
पूर्ण;

#घोषणा MANAGEMENT_ORB_LUN(v)			((v))
#घोषणा MANAGEMENT_ORB_FUNCTION(v)		((v) << 16)
#घोषणा MANAGEMENT_ORB_RECONNECT(v)		((v) << 20)
#घोषणा MANAGEMENT_ORB_EXCLUSIVE(v)		((v) ? 1 << 28 : 0)
#घोषणा MANAGEMENT_ORB_REQUEST_FORMAT(v)	((v) << 29)
#घोषणा MANAGEMENT_ORB_NOTIFY			((1) << 31)

#घोषणा MANAGEMENT_ORB_RESPONSE_LENGTH(v)	((v))
#घोषणा MANAGEMENT_ORB_PASSWORD_LENGTH(v)	((v) << 16)

काष्ठा sbp2_management_orb अणु
	काष्ठा sbp2_orb base;
	काष्ठा अणु
		काष्ठा sbp2_poपूर्णांकer password;
		काष्ठा sbp2_poपूर्णांकer response;
		__be32 misc;
		__be32 length;
		काष्ठा sbp2_poपूर्णांकer status_fअगरo;
	पूर्ण request;
	__be32 response[4];
	dma_addr_t response_bus;
	काष्ठा completion करोne;
	काष्ठा sbp2_status status;
पूर्ण;

काष्ठा sbp2_login_response अणु
	__be32 misc;
	काष्ठा sbp2_poपूर्णांकer command_block_agent;
	__be32 reconnect_hold;
पूर्ण;
#घोषणा COMMAND_ORB_DATA_SIZE(v)	((v))
#घोषणा COMMAND_ORB_PAGE_SIZE(v)	((v) << 16)
#घोषणा COMMAND_ORB_PAGE_TABLE_PRESENT	((1) << 19)
#घोषणा COMMAND_ORB_MAX_PAYLOAD(v)	((v) << 20)
#घोषणा COMMAND_ORB_SPEED(v)		((v) << 24)
#घोषणा COMMAND_ORB_सूचीECTION		((1) << 27)
#घोषणा COMMAND_ORB_REQUEST_FORMAT(v)	((v) << 29)
#घोषणा COMMAND_ORB_NOTIFY		((1) << 31)

काष्ठा sbp2_command_orb अणु
	काष्ठा sbp2_orb base;
	काष्ठा अणु
		काष्ठा sbp2_poपूर्णांकer next;
		काष्ठा sbp2_poपूर्णांकer data_descriptor;
		__be32 misc;
		u8 command_block[SBP2_MAX_CDB_SIZE];
	पूर्ण request;
	काष्ठा scsi_cmnd *cmd;

	काष्ठा sbp2_poपूर्णांकer page_table[SG_ALL] __attribute__((aligned(8)));
	dma_addr_t page_table_bus;
पूर्ण;

#घोषणा SBP2_ROM_VALUE_WILDCARD ~0         /* match all */
#घोषणा SBP2_ROM_VALUE_MISSING  0xff000000 /* not present in the unit dir. */

/*
 * List of devices with known bugs.
 *
 * The firmware_revision field, masked with 0xffff00, is the best
 * indicator क्रम the type of bridge chip of a device.  It yields a few
 * false positives but this did not अवरोध correctly behaving devices
 * so far.
 */
अटल स्थिर काष्ठा अणु
	u32 firmware_revision;
	u32 model;
	अचिन्हित पूर्णांक workarounds;
पूर्ण sbp2_workarounds_table[] = अणु
	/* DViCO Momobay CX-1 with TSB42AA9 bridge */ अणु
		.firmware_revision	= 0x002800,
		.model			= 0x001010,
		.workarounds		= SBP2_WORKAROUND_INQUIRY_36 |
					  SBP2_WORKAROUND_MODE_SENSE_8 |
					  SBP2_WORKAROUND_POWER_CONDITION,
	पूर्ण,
	/* DViCO Momobay FX-3A with TSB42AA9A bridge */ अणु
		.firmware_revision	= 0x002800,
		.model			= 0x000000,
		.workarounds		= SBP2_WORKAROUND_POWER_CONDITION,
	पूर्ण,
	/* Initio bridges, actually only needed क्रम some older ones */ अणु
		.firmware_revision	= 0x000200,
		.model			= SBP2_ROM_VALUE_WILDCARD,
		.workarounds		= SBP2_WORKAROUND_INQUIRY_36,
	पूर्ण,
	/* PL-3507 bridge with Prolअगरic firmware */ अणु
		.firmware_revision	= 0x012800,
		.model			= SBP2_ROM_VALUE_WILDCARD,
		.workarounds		= SBP2_WORKAROUND_POWER_CONDITION,
	पूर्ण,
	/* Symbios bridge */ अणु
		.firmware_revision	= 0xa0b800,
		.model			= SBP2_ROM_VALUE_WILDCARD,
		.workarounds		= SBP2_WORKAROUND_128K_MAX_TRANS,
	पूर्ण,
	/* Datafab MD2-FW2 with Symbios/LSILogic SYM13FW500 bridge */ अणु
		.firmware_revision	= 0x002600,
		.model			= SBP2_ROM_VALUE_WILDCARD,
		.workarounds		= SBP2_WORKAROUND_128K_MAX_TRANS,
	पूर्ण,
	/*
	 * iPod 2nd generation: needs 128k max transfer size workaround
	 * iPod 3rd generation: needs fix capacity workaround
	 */
	अणु
		.firmware_revision	= 0x0a2700,
		.model			= 0x000000,
		.workarounds		= SBP2_WORKAROUND_128K_MAX_TRANS |
					  SBP2_WORKAROUND_FIX_CAPACITY,
	पूर्ण,
	/* iPod 4th generation */ अणु
		.firmware_revision	= 0x0a2700,
		.model			= 0x000021,
		.workarounds		= SBP2_WORKAROUND_FIX_CAPACITY,
	पूर्ण,
	/* iPod mini */ अणु
		.firmware_revision	= 0x0a2700,
		.model			= 0x000022,
		.workarounds		= SBP2_WORKAROUND_FIX_CAPACITY,
	पूर्ण,
	/* iPod mini */ अणु
		.firmware_revision	= 0x0a2700,
		.model			= 0x000023,
		.workarounds		= SBP2_WORKAROUND_FIX_CAPACITY,
	पूर्ण,
	/* iPod Photo */ अणु
		.firmware_revision	= 0x0a2700,
		.model			= 0x00007e,
		.workarounds		= SBP2_WORKAROUND_FIX_CAPACITY,
	पूर्ण
पूर्ण;

अटल व्योम मुक्त_orb(काष्ठा kref *kref)
अणु
	काष्ठा sbp2_orb *orb = container_of(kref, काष्ठा sbp2_orb, kref);

	kमुक्त(orb);
पूर्ण

अटल व्योम sbp2_status_ग_लिखो(काष्ठा fw_card *card, काष्ठा fw_request *request,
			      पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			      पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			      व्योम *payload, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा sbp2_logical_unit *lu = callback_data;
	काष्ठा sbp2_orb *orb;
	काष्ठा sbp2_status status;
	अचिन्हित दीर्घ flags;

	अगर (tcode != TCODE_WRITE_BLOCK_REQUEST ||
	    length < 8 || length > माप(status)) अणु
		fw_send_response(card, request, RCODE_TYPE_ERROR);
		वापस;
	पूर्ण

	status.status  = be32_to_cpup(payload);
	status.orb_low = be32_to_cpup(payload + 4);
	स_रखो(status.data, 0, माप(status.data));
	अगर (length > 8)
		स_नकल(status.data, payload + 8, length - 8);

	अगर (STATUS_GET_SOURCE(status) == 2 || STATUS_GET_SOURCE(status) == 3) अणु
		dev_notice(lu_dev(lu),
			   "non-ORB related status write, not handled\n");
		fw_send_response(card, request, RCODE_COMPLETE);
		वापस;
	पूर्ण

	/* Lookup the orb corresponding to this status ग_लिखो. */
	spin_lock_irqsave(&lu->tgt->lock, flags);
	list_क्रम_each_entry(orb, &lu->orb_list, link) अणु
		अगर (STATUS_GET_ORB_HIGH(status) == 0 &&
		    STATUS_GET_ORB_LOW(status) == orb->request_bus) अणु
			orb->rcode = RCODE_COMPLETE;
			list_del(&orb->link);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&lu->tgt->lock, flags);

	अगर (&orb->link != &lu->orb_list) अणु
		orb->callback(orb, &status);
		kref_put(&orb->kref, मुक्त_orb); /* orb callback reference */
	पूर्ण अन्यथा अणु
		dev_err(lu_dev(lu), "status write for unknown ORB\n");
	पूर्ण

	fw_send_response(card, request, RCODE_COMPLETE);
पूर्ण

अटल व्योम complete_transaction(काष्ठा fw_card *card, पूर्णांक rcode,
				 व्योम *payload, माप_प्रकार length, व्योम *data)
अणु
	काष्ठा sbp2_orb *orb = data;
	अचिन्हित दीर्घ flags;

	/*
	 * This is a little tricky.  We can get the status ग_लिखो क्रम
	 * the orb beक्रमe we get this callback.  The status ग_लिखो
	 * handler above will assume the orb poपूर्णांकer transaction was
	 * successful and set the rcode to RCODE_COMPLETE क्रम the orb.
	 * So this callback only sets the rcode अगर it hasn't alपढ़ोy
	 * been set and only करोes the cleanup अगर the transaction
	 * failed and we didn't alपढ़ोy get a status ग_लिखो.
	 */
	spin_lock_irqsave(&orb->lu->tgt->lock, flags);

	अगर (orb->rcode == -1)
		orb->rcode = rcode;
	अगर (orb->rcode != RCODE_COMPLETE) अणु
		list_del(&orb->link);
		spin_unlock_irqrestore(&orb->lu->tgt->lock, flags);

		orb->callback(orb, शून्य);
		kref_put(&orb->kref, मुक्त_orb); /* orb callback reference */
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&orb->lu->tgt->lock, flags);
	पूर्ण

	kref_put(&orb->kref, मुक्त_orb); /* transaction callback reference */
पूर्ण

अटल व्योम sbp2_send_orb(काष्ठा sbp2_orb *orb, काष्ठा sbp2_logical_unit *lu,
			  पूर्णांक node_id, पूर्णांक generation, u64 offset)
अणु
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	काष्ठा sbp2_poपूर्णांकer orb_poपूर्णांकer;
	अचिन्हित दीर्घ flags;

	orb_poपूर्णांकer.high = 0;
	orb_poपूर्णांकer.low = cpu_to_be32(orb->request_bus);

	orb->lu = lu;
	spin_lock_irqsave(&lu->tgt->lock, flags);
	list_add_tail(&orb->link, &lu->orb_list);
	spin_unlock_irqrestore(&lu->tgt->lock, flags);

	kref_get(&orb->kref); /* transaction callback reference */
	kref_get(&orb->kref); /* orb callback reference */

	fw_send_request(device->card, &orb->t, TCODE_WRITE_BLOCK_REQUEST,
			node_id, generation, device->max_speed, offset,
			&orb_poपूर्णांकer, 8, complete_transaction, orb);
पूर्ण

अटल पूर्णांक sbp2_cancel_orbs(काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	काष्ठा sbp2_orb *orb, *next;
	काष्ठा list_head list;
	पूर्णांक retval = -ENOENT;

	INIT_LIST_HEAD(&list);
	spin_lock_irq(&lu->tgt->lock);
	list_splice_init(&lu->orb_list, &list);
	spin_unlock_irq(&lu->tgt->lock);

	list_क्रम_each_entry_safe(orb, next, &list, link) अणु
		retval = 0;
		अगर (fw_cancel_transaction(device->card, &orb->t) == 0)
			जारी;

		orb->rcode = RCODE_CANCELLED;
		orb->callback(orb, शून्य);
		kref_put(&orb->kref, मुक्त_orb); /* orb callback reference */
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम complete_management_orb(काष्ठा sbp2_orb *base_orb,
				    काष्ठा sbp2_status *status)
अणु
	काष्ठा sbp2_management_orb *orb =
		container_of(base_orb, काष्ठा sbp2_management_orb, base);

	अगर (status)
		स_नकल(&orb->status, status, माप(*status));
	complete(&orb->करोne);
पूर्ण

अटल पूर्णांक sbp2_send_management_orb(काष्ठा sbp2_logical_unit *lu, पूर्णांक node_id,
				    पूर्णांक generation, पूर्णांक function,
				    पूर्णांक lun_or_login_id, व्योम *response)
अणु
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	काष्ठा sbp2_management_orb *orb;
	अचिन्हित पूर्णांक समयout;
	पूर्णांक retval = -ENOMEM;

	अगर (function == SBP2_LOGOUT_REQUEST && fw_device_is_shutकरोwn(device))
		वापस 0;

	orb = kzalloc(माप(*orb), GFP_NOIO);
	अगर (orb == शून्य)
		वापस -ENOMEM;

	kref_init(&orb->base.kref);
	orb->response_bus =
		dma_map_single(device->card->device, &orb->response,
			       माप(orb->response), DMA_FROM_DEVICE);
	अगर (dma_mapping_error(device->card->device, orb->response_bus))
		जाओ fail_mapping_response;

	orb->request.response.high = 0;
	orb->request.response.low  = cpu_to_be32(orb->response_bus);

	orb->request.misc = cpu_to_be32(
		MANAGEMENT_ORB_NOTIFY |
		MANAGEMENT_ORB_FUNCTION(function) |
		MANAGEMENT_ORB_LUN(lun_or_login_id));
	orb->request.length = cpu_to_be32(
		MANAGEMENT_ORB_RESPONSE_LENGTH(माप(orb->response)));

	orb->request.status_fअगरo.high =
		cpu_to_be32(lu->address_handler.offset >> 32);
	orb->request.status_fअगरo.low  =
		cpu_to_be32(lu->address_handler.offset);

	अगर (function == SBP2_LOGIN_REQUEST) अणु
		/* Ask क्रम 2^2 == 4 seconds reconnect grace period */
		orb->request.misc |= cpu_to_be32(
			MANAGEMENT_ORB_RECONNECT(2) |
			MANAGEMENT_ORB_EXCLUSIVE(sbp2_param_exclusive_login));
		समयout = lu->tgt->mgt_orb_समयout;
	पूर्ण अन्यथा अणु
		समयout = SBP2_ORB_TIMEOUT;
	पूर्ण

	init_completion(&orb->करोne);
	orb->base.callback = complete_management_orb;

	orb->base.request_bus =
		dma_map_single(device->card->device, &orb->request,
			       माप(orb->request), DMA_TO_DEVICE);
	अगर (dma_mapping_error(device->card->device, orb->base.request_bus))
		जाओ fail_mapping_request;

	sbp2_send_orb(&orb->base, lu, node_id, generation,
		      lu->tgt->management_agent_address);

	रुको_क्रम_completion_समयout(&orb->करोne, msecs_to_jअगरfies(समयout));

	retval = -EIO;
	अगर (sbp2_cancel_orbs(lu) == 0) अणु
		dev_err(lu_dev(lu), "ORB reply timed out, rcode 0x%02x\n",
			orb->base.rcode);
		जाओ out;
	पूर्ण

	अगर (orb->base.rcode != RCODE_COMPLETE) अणु
		dev_err(lu_dev(lu), "management write failed, rcode 0x%02x\n",
			orb->base.rcode);
		जाओ out;
	पूर्ण

	अगर (STATUS_GET_RESPONSE(orb->status) != 0 ||
	    STATUS_GET_SBP_STATUS(orb->status) != 0) अणु
		dev_err(lu_dev(lu), "error status: %d:%d\n",
			 STATUS_GET_RESPONSE(orb->status),
			 STATUS_GET_SBP_STATUS(orb->status));
		जाओ out;
	पूर्ण

	retval = 0;
 out:
	dma_unmap_single(device->card->device, orb->base.request_bus,
			 माप(orb->request), DMA_TO_DEVICE);
 fail_mapping_request:
	dma_unmap_single(device->card->device, orb->response_bus,
			 माप(orb->response), DMA_FROM_DEVICE);
 fail_mapping_response:
	अगर (response)
		स_नकल(response, orb->response, माप(orb->response));
	kref_put(&orb->base.kref, मुक्त_orb);

	वापस retval;
पूर्ण

अटल व्योम sbp2_agent_reset(काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	__be32 d = 0;

	fw_run_transaction(device->card, TCODE_WRITE_QUADLET_REQUEST,
			   lu->tgt->node_id, lu->generation, device->max_speed,
			   lu->command_block_agent_address + SBP2_AGENT_RESET,
			   &d, 4);
पूर्ण

अटल व्योम complete_agent_reset_ग_लिखो_no_रुको(काष्ठा fw_card *card,
		पूर्णांक rcode, व्योम *payload, माप_प्रकार length, व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

अटल व्योम sbp2_agent_reset_no_रुको(काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	काष्ठा fw_transaction *t;
	अटल __be32 d;

	t = kदो_स्मृति(माप(*t), GFP_ATOMIC);
	अगर (t == शून्य)
		वापस;

	fw_send_request(device->card, t, TCODE_WRITE_QUADLET_REQUEST,
			lu->tgt->node_id, lu->generation, device->max_speed,
			lu->command_block_agent_address + SBP2_AGENT_RESET,
			&d, 4, complete_agent_reset_ग_लिखो_no_रुको, t);
पूर्ण

अटल अंतरभूत व्योम sbp2_allow_block(काष्ठा sbp2_target *tgt)
अणु
	spin_lock_irq(&tgt->lock);
	--tgt->करोnt_block;
	spin_unlock_irq(&tgt->lock);
पूर्ण

/*
 * Blocks lu->tgt अगर all of the following conditions are met:
 *   - Login, INQUIRY, and high-level SCSI setup of all of the target's
 *     logical units have been finished (indicated by करोnt_block == 0).
 *   - lu->generation is stale.
 *
 * Note, scsi_block_requests() must be called जबतक holding tgt->lock,
 * otherwise it might foil sbp2_[conditionally_]unblock()'s attempt to
 * unblock the target.
 */
अटल व्योम sbp2_conditionally_block(काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा sbp2_target *tgt = lu->tgt;
	काष्ठा fw_card *card = target_parent_device(tgt)->card;
	काष्ठा Scsi_Host *shost =
		container_of((व्योम *)tgt, काष्ठा Scsi_Host, hostdata[0]);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tgt->lock, flags);
	अगर (!tgt->करोnt_block && !lu->blocked &&
	    lu->generation != card->generation) अणु
		lu->blocked = true;
		अगर (++tgt->blocked == 1)
			scsi_block_requests(shost);
	पूर्ण
	spin_unlock_irqrestore(&tgt->lock, flags);
पूर्ण

/*
 * Unblocks lu->tgt as soon as all its logical units can be unblocked.
 * Note, it is harmless to run scsi_unblock_requests() outside the
 * tgt->lock रक्षित section.  On the other hand, running it inside
 * the section might clash with shost->host_lock.
 */
अटल व्योम sbp2_conditionally_unblock(काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा sbp2_target *tgt = lu->tgt;
	काष्ठा fw_card *card = target_parent_device(tgt)->card;
	काष्ठा Scsi_Host *shost =
		container_of((व्योम *)tgt, काष्ठा Scsi_Host, hostdata[0]);
	bool unblock = false;

	spin_lock_irq(&tgt->lock);
	अगर (lu->blocked && lu->generation == card->generation) अणु
		lu->blocked = false;
		unblock = --tgt->blocked == 0;
	पूर्ण
	spin_unlock_irq(&tgt->lock);

	अगर (unblock)
		scsi_unblock_requests(shost);
पूर्ण

/*
 * Prevents future blocking of tgt and unblocks it.
 * Note, it is harmless to run scsi_unblock_requests() outside the
 * tgt->lock रक्षित section.  On the other hand, running it inside
 * the section might clash with shost->host_lock.
 */
अटल व्योम sbp2_unblock(काष्ठा sbp2_target *tgt)
अणु
	काष्ठा Scsi_Host *shost =
		container_of((व्योम *)tgt, काष्ठा Scsi_Host, hostdata[0]);

	spin_lock_irq(&tgt->lock);
	++tgt->करोnt_block;
	spin_unlock_irq(&tgt->lock);

	scsi_unblock_requests(shost);
पूर्ण

अटल पूर्णांक sbp2_lun2पूर्णांक(u16 lun)
अणु
	काष्ठा scsi_lun eight_bytes_lun;

	स_रखो(&eight_bytes_lun, 0, माप(eight_bytes_lun));
	eight_bytes_lun.scsi_lun[0] = (lun >> 8) & 0xff;
	eight_bytes_lun.scsi_lun[1] = lun & 0xff;

	वापस scsilun_to_पूर्णांक(&eight_bytes_lun);
पूर्ण

/*
 * Write retransmit retry values पूर्णांकo the BUSY_TIMEOUT रेजिस्टर.
 * - The single-phase retry protocol is supported by all SBP-2 devices, but the
 *   शेष retry_limit value is 0 (i.e. never retry transmission). We ग_लिखो a
 *   saner value after logging पूर्णांकo the device.
 * - The dual-phase retry protocol is optional to implement, and अगर not
 *   supported, ग_लिखोs to the dual-phase portion of the रेजिस्टर will be
 *   ignored. We try to ग_लिखो the original 1394-1995 शेष here.
 * - In the हाल of devices that are also SBP-3-compliant, all ग_लिखोs are
 *   ignored, as the रेजिस्टर is पढ़ो-only, but contains single-phase retry of
 *   15, which is what we're trying to set क्रम all SBP-2 device anyway, so this
 *   ग_लिखो attempt is safe and yields more consistent behavior क्रम all devices.
 *
 * See section 8.3.2.3.5 of the 1394-1995 spec, section 6.2 of the SBP-2 spec,
 * and section 6.4 of the SBP-3 spec क्रम further details.
 */
अटल व्योम sbp2_set_busy_समयout(काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	__be32 d = cpu_to_be32(SBP2_CYCLE_LIMIT | SBP2_RETRY_LIMIT);

	fw_run_transaction(device->card, TCODE_WRITE_QUADLET_REQUEST,
			   lu->tgt->node_id, lu->generation, device->max_speed,
			   CSR_REGISTER_BASE + CSR_BUSY_TIMEOUT, &d, 4);
पूर्ण

अटल व्योम sbp2_reconnect(काष्ठा work_काष्ठा *work);

अटल व्योम sbp2_login(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp2_logical_unit *lu =
		container_of(work, काष्ठा sbp2_logical_unit, work.work);
	काष्ठा sbp2_target *tgt = lu->tgt;
	काष्ठा fw_device *device = target_parent_device(tgt);
	काष्ठा Scsi_Host *shost;
	काष्ठा scsi_device *sdev;
	काष्ठा sbp2_login_response response;
	पूर्णांक generation, node_id, local_node_id;

	अगर (fw_device_is_shutकरोwn(device))
		वापस;

	generation    = device->generation;
	smp_rmb();    /* node IDs must not be older than generation */
	node_id       = device->node_id;
	local_node_id = device->card->node_id;

	/* If this is a re-login attempt, log out, or we might be rejected. */
	अगर (lu->has_sdev)
		sbp2_send_management_orb(lu, device->node_id, generation,
				SBP2_LOGOUT_REQUEST, lu->login_id, शून्य);

	अगर (sbp2_send_management_orb(lu, node_id, generation,
				SBP2_LOGIN_REQUEST, lu->lun, &response) < 0) अणु
		अगर (lu->retries++ < 5) अणु
			sbp2_queue_work(lu, DIV_ROUND_UP(HZ, 5));
		पूर्ण अन्यथा अणु
			dev_err(tgt_dev(tgt), "failed to login to LUN %04x\n",
				lu->lun);
			/* Let any रुकोing I/O fail from now on. */
			sbp2_unblock(lu->tgt);
		पूर्ण
		वापस;
	पूर्ण

	tgt->node_id	  = node_id;
	tgt->address_high = local_node_id << 16;
	smp_wmb();	  /* node IDs must not be older than generation */
	lu->generation	  = generation;

	lu->command_block_agent_address =
		((u64)(be32_to_cpu(response.command_block_agent.high) & 0xffff)
		      << 32) | be32_to_cpu(response.command_block_agent.low);
	lu->login_id = be32_to_cpu(response.misc) & 0xffff;

	dev_notice(tgt_dev(tgt), "logged in to LUN %04x (%d retries)\n",
		   lu->lun, lu->retries);

	/* set appropriate retry limit(s) in BUSY_TIMEOUT रेजिस्टर */
	sbp2_set_busy_समयout(lu);

	lu->workfn = sbp2_reconnect;
	sbp2_agent_reset(lu);

	/* This was a re-login. */
	अगर (lu->has_sdev) अणु
		sbp2_cancel_orbs(lu);
		sbp2_conditionally_unblock(lu);

		वापस;
	पूर्ण

	अगर (lu->tgt->workarounds & SBP2_WORKAROUND_DELAY_INQUIRY)
		ssleep(SBP2_INQUIRY_DELAY);

	shost = container_of((व्योम *)tgt, काष्ठा Scsi_Host, hostdata[0]);
	sdev = __scsi_add_device(shost, 0, 0, sbp2_lun2पूर्णांक(lu->lun), lu);
	/*
	 * FIXME:  We are unable to perक्रमm reconnects जबतक in sbp2_login().
	 * Thereक्रमe __scsi_add_device() will get पूर्णांकo trouble अगर a bus reset
	 * happens in parallel.  It will either fail or leave us with an
	 * unusable sdev.  As a workaround we check क्रम this and retry the
	 * whole login and SCSI probing.
	 */

	/* Reported error during __scsi_add_device() */
	अगर (IS_ERR(sdev))
		जाओ out_logout_login;

	/* Unreported error during __scsi_add_device() */
	smp_rmb(); /* get current card generation */
	अगर (generation != device->card->generation) अणु
		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
		जाओ out_logout_login;
	पूर्ण

	/* No error during __scsi_add_device() */
	lu->has_sdev = true;
	scsi_device_put(sdev);
	sbp2_allow_block(tgt);

	वापस;

 out_logout_login:
	smp_rmb(); /* generation may have changed */
	generation = device->generation;
	smp_rmb(); /* node_id must not be older than generation */

	sbp2_send_management_orb(lu, device->node_id, generation,
				 SBP2_LOGOUT_REQUEST, lu->login_id, शून्य);
	/*
	 * If a bus reset happened, sbp2_update will have requeued
	 * lu->work alपढ़ोy.  Reset the work from reconnect to login.
	 */
	lu->workfn = sbp2_login;
पूर्ण

अटल व्योम sbp2_reconnect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp2_logical_unit *lu =
		container_of(work, काष्ठा sbp2_logical_unit, work.work);
	काष्ठा sbp2_target *tgt = lu->tgt;
	काष्ठा fw_device *device = target_parent_device(tgt);
	पूर्णांक generation, node_id, local_node_id;

	अगर (fw_device_is_shutकरोwn(device))
		वापस;

	generation    = device->generation;
	smp_rmb();    /* node IDs must not be older than generation */
	node_id       = device->node_id;
	local_node_id = device->card->node_id;

	अगर (sbp2_send_management_orb(lu, node_id, generation,
				     SBP2_RECONNECT_REQUEST,
				     lu->login_id, शून्य) < 0) अणु
		/*
		 * If reconnect was impossible even though we are in the
		 * current generation, fall back and try to log in again.
		 *
		 * We could check क्रम "Function rejected" status, but
		 * looking at the bus generation as simpler and more general.
		 */
		smp_rmb(); /* get current card generation */
		अगर (generation == device->card->generation ||
		    lu->retries++ >= 5) अणु
			dev_err(tgt_dev(tgt), "failed to reconnect\n");
			lu->retries = 0;
			lu->workfn = sbp2_login;
		पूर्ण
		sbp2_queue_work(lu, DIV_ROUND_UP(HZ, 5));

		वापस;
	पूर्ण

	tgt->node_id      = node_id;
	tgt->address_high = local_node_id << 16;
	smp_wmb();	  /* node IDs must not be older than generation */
	lu->generation	  = generation;

	dev_notice(tgt_dev(tgt), "reconnected to LUN %04x (%d retries)\n",
		   lu->lun, lu->retries);

	sbp2_agent_reset(lu);
	sbp2_cancel_orbs(lu);
	sbp2_conditionally_unblock(lu);
पूर्ण

अटल व्योम sbp2_lu_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp2_logical_unit *lu = container_of(to_delayed_work(work),
						काष्ठा sbp2_logical_unit, work);
	lu->workfn(work);
पूर्ण

अटल पूर्णांक sbp2_add_logical_unit(काष्ठा sbp2_target *tgt, पूर्णांक lun_entry)
अणु
	काष्ठा sbp2_logical_unit *lu;

	lu = kदो_स्मृति(माप(*lu), GFP_KERNEL);
	अगर (!lu)
		वापस -ENOMEM;

	lu->address_handler.length           = 0x100;
	lu->address_handler.address_callback = sbp2_status_ग_लिखो;
	lu->address_handler.callback_data    = lu;

	अगर (fw_core_add_address_handler(&lu->address_handler,
					&fw_high_memory_region) < 0) अणु
		kमुक्त(lu);
		वापस -ENOMEM;
	पूर्ण

	lu->tgt      = tgt;
	lu->lun      = lun_entry & 0xffff;
	lu->login_id = INVALID_LOGIN_ID;
	lu->retries  = 0;
	lu->has_sdev = false;
	lu->blocked  = false;
	++tgt->करोnt_block;
	INIT_LIST_HEAD(&lu->orb_list);
	lu->workfn = sbp2_login;
	INIT_DELAYED_WORK(&lu->work, sbp2_lu_workfn);

	list_add_tail(&lu->link, &tgt->lu_list);
	वापस 0;
पूर्ण

अटल व्योम sbp2_get_unit_unique_id(काष्ठा sbp2_target *tgt,
				    स्थिर u32 *leaf)
अणु
	अगर ((leaf[0] & 0xffff0000) == 0x00020000)
		tgt->guid = (u64)leaf[1] << 32 | leaf[2];
पूर्ण

अटल पूर्णांक sbp2_scan_logical_unit_dir(काष्ठा sbp2_target *tgt,
				      स्थिर u32 *directory)
अणु
	काष्ठा fw_csr_iterator ci;
	पूर्णांक key, value;

	fw_csr_iterator_init(&ci, directory);
	जबतक (fw_csr_iterator_next(&ci, &key, &value))
		अगर (key == SBP2_CSR_LOGICAL_UNIT_NUMBER &&
		    sbp2_add_logical_unit(tgt, value) < 0)
			वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक sbp2_scan_unit_dir(काष्ठा sbp2_target *tgt, स्थिर u32 *directory,
			      u32 *model, u32 *firmware_revision)
अणु
	काष्ठा fw_csr_iterator ci;
	पूर्णांक key, value;

	fw_csr_iterator_init(&ci, directory);
	जबतक (fw_csr_iterator_next(&ci, &key, &value)) अणु
		चयन (key) अणु

		हाल CSR_DEPENDENT_INFO | CSR_OFFSET:
			tgt->management_agent_address =
					CSR_REGISTER_BASE + 4 * value;
			अवरोध;

		हाल CSR_सूचीECTORY_ID:
			tgt->directory_id = value;
			अवरोध;

		हाल CSR_MODEL:
			*model = value;
			अवरोध;

		हाल SBP2_CSR_FIRMWARE_REVISION:
			*firmware_revision = value;
			अवरोध;

		हाल SBP2_CSR_UNIT_CHARACTERISTICS:
			/* the समयout value is stored in 500ms units */
			tgt->mgt_orb_समयout = (value >> 8 & 0xff) * 500;
			अवरोध;

		हाल SBP2_CSR_LOGICAL_UNIT_NUMBER:
			अगर (sbp2_add_logical_unit(tgt, value) < 0)
				वापस -ENOMEM;
			अवरोध;

		हाल SBP2_CSR_UNIT_UNIQUE_ID:
			sbp2_get_unit_unique_id(tgt, ci.p - 1 + value);
			अवरोध;

		हाल SBP2_CSR_LOGICAL_UNIT_सूचीECTORY:
			/* Adjust क्रम the increment in the iterator */
			अगर (sbp2_scan_logical_unit_dir(tgt, ci.p - 1 + value) < 0)
				वापस -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Per section 7.4.8 of the SBP-2 spec, a mgt_ORB_समयout value can be
 * provided in the config rom. Most devices करो provide a value, which
 * we'll use क्रम login management orbs, but with some sane limits.
 */
अटल व्योम sbp2_clamp_management_orb_समयout(काष्ठा sbp2_target *tgt)
अणु
	अचिन्हित पूर्णांक समयout = tgt->mgt_orb_समयout;

	अगर (समयout > 40000)
		dev_notice(tgt_dev(tgt), "%ds mgt_ORB_timeout limited to 40s\n",
			   समयout / 1000);

	tgt->mgt_orb_समयout = clamp_val(समयout, 5000, 40000);
पूर्ण

अटल व्योम sbp2_init_workarounds(काष्ठा sbp2_target *tgt, u32 model,
				  u32 firmware_revision)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक w = sbp2_param_workarounds;

	अगर (w)
		dev_notice(tgt_dev(tgt),
			   "Please notify linux1394-devel@lists.sf.net "
			   "if you need the workarounds parameter\n");

	अगर (w & SBP2_WORKAROUND_OVERRIDE)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(sbp2_workarounds_table); i++) अणु

		अगर (sbp2_workarounds_table[i].firmware_revision !=
		    (firmware_revision & 0xffffff00))
			जारी;

		अगर (sbp2_workarounds_table[i].model != model &&
		    sbp2_workarounds_table[i].model != SBP2_ROM_VALUE_WILDCARD)
			जारी;

		w |= sbp2_workarounds_table[i].workarounds;
		अवरोध;
	पूर्ण
 out:
	अगर (w)
		dev_notice(tgt_dev(tgt), "workarounds 0x%x "
			   "(firmware_revision 0x%06x, model_id 0x%06x)\n",
			   w, firmware_revision, model);
	tgt->workarounds = w;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा scsi_driver_ढाँचा;
अटल व्योम sbp2_हटाओ(काष्ठा fw_unit *unit);

अटल पूर्णांक sbp2_probe(काष्ठा fw_unit *unit, स्थिर काष्ठा ieee1394_device_id *id)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	काष्ठा sbp2_target *tgt;
	काष्ठा sbp2_logical_unit *lu;
	काष्ठा Scsi_Host *shost;
	u32 model, firmware_revision;

	/* cannot (or should not) handle tarमाला_लो on the local node */
	अगर (device->is_local)
		वापस -ENODEV;

	shost = scsi_host_alloc(&scsi_driver_ढाँचा, माप(*tgt));
	अगर (shost == शून्य)
		वापस -ENOMEM;

	tgt = (काष्ठा sbp2_target *)shost->hostdata;
	dev_set_drvdata(&unit->device, tgt);
	tgt->unit = unit;
	INIT_LIST_HEAD(&tgt->lu_list);
	spin_lock_init(&tgt->lock);
	tgt->guid = (u64)device->config_rom[3] << 32 | device->config_rom[4];

	अगर (fw_device_enable_phys_dma(device) < 0)
		जाओ fail_shost_put;

	shost->max_cmd_len = SBP2_MAX_CDB_SIZE;

	अगर (scsi_add_host_with_dma(shost, &unit->device,
				   device->card->device) < 0)
		जाओ fail_shost_put;

	/* implicit directory ID */
	tgt->directory_id = ((unit->directory - device->config_rom) * 4
			     + CSR_CONFIG_ROM) & 0xffffff;

	firmware_revision = SBP2_ROM_VALUE_MISSING;
	model		  = SBP2_ROM_VALUE_MISSING;

	अगर (sbp2_scan_unit_dir(tgt, unit->directory, &model,
			       &firmware_revision) < 0)
		जाओ fail_हटाओ;

	sbp2_clamp_management_orb_समयout(tgt);
	sbp2_init_workarounds(tgt, model, firmware_revision);

	/*
	 * At S100 we can करो 512 bytes per packet, at S200 1024 bytes,
	 * and so on up to 4096 bytes.  The SBP-2 max_payload field
	 * specअगरies the max payload size as 2 ^ (max_payload + 2), so
	 * अगर we set this to max_speed + 7, we get the right value.
	 */
	tgt->max_payload = min3(device->max_speed + 7, 10U,
				device->card->max_receive - 1);

	/* Do the login in a workqueue so we can easily reschedule retries. */
	list_क्रम_each_entry(lu, &tgt->lu_list, link)
		sbp2_queue_work(lu, DIV_ROUND_UP(HZ, 5));

	वापस 0;

 fail_हटाओ:
	sbp2_हटाओ(unit);
	वापस -ENOMEM;

 fail_shost_put:
	scsi_host_put(shost);
	वापस -ENOMEM;
पूर्ण

अटल व्योम sbp2_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा sbp2_target *tgt = dev_get_drvdata(&unit->device);
	काष्ठा sbp2_logical_unit *lu;

	fw_device_enable_phys_dma(fw_parent_device(unit));

	/*
	 * Fw-core serializes sbp2_update() against sbp2_हटाओ().
	 * Iteration over tgt->lu_list is thereक्रमe safe here.
	 */
	list_क्रम_each_entry(lu, &tgt->lu_list, link) अणु
		sbp2_conditionally_block(lu);
		lu->retries = 0;
		sbp2_queue_work(lu, 0);
	पूर्ण
पूर्ण

अटल व्योम sbp2_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	काष्ठा sbp2_target *tgt = dev_get_drvdata(&unit->device);
	काष्ठा sbp2_logical_unit *lu, *next;
	काष्ठा Scsi_Host *shost =
		container_of((व्योम *)tgt, काष्ठा Scsi_Host, hostdata[0]);
	काष्ठा scsi_device *sdev;

	/* prevent deadlocks */
	sbp2_unblock(tgt);

	list_क्रम_each_entry_safe(lu, next, &tgt->lu_list, link) अणु
		cancel_delayed_work_sync(&lu->work);
		sdev = scsi_device_lookup(shost, 0, 0, sbp2_lun2पूर्णांक(lu->lun));
		अगर (sdev) अणु
			scsi_हटाओ_device(sdev);
			scsi_device_put(sdev);
		पूर्ण
		अगर (lu->login_id != INVALID_LOGIN_ID) अणु
			पूर्णांक generation, node_id;
			/*
			 * tgt->node_id may be obsolete here अगर we failed
			 * during initial login or after a bus reset where
			 * the topology changed.
			 */
			generation = device->generation;
			smp_rmb(); /* node_id vs. generation */
			node_id    = device->node_id;
			sbp2_send_management_orb(lu, node_id, generation,
						 SBP2_LOGOUT_REQUEST,
						 lu->login_id, शून्य);
		पूर्ण
		fw_core_हटाओ_address_handler(&lu->address_handler);
		list_del(&lu->link);
		kमुक्त(lu);
	पूर्ण
	scsi_हटाओ_host(shost);
	dev_notice(&unit->device, "released target %d:0:0\n", shost->host_no);

	scsi_host_put(shost);
पूर्ण

#घोषणा SBP2_UNIT_SPEC_ID_ENTRY	0x0000609e
#घोषणा SBP2_SW_VERSION_ENTRY	0x00010483

अटल स्थिर काष्ठा ieee1394_device_id sbp2_id_table[] = अणु
	अणु
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specअगरier_id = SBP2_UNIT_SPEC_ID_ENTRY,
		.version      = SBP2_SW_VERSION_ENTRY,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा fw_driver sbp2_driver = अणु
	.driver   = अणु
		.owner  = THIS_MODULE,
		.name   = KBUILD_MODNAME,
		.bus    = &fw_bus_type,
	पूर्ण,
	.probe    = sbp2_probe,
	.update   = sbp2_update,
	.हटाओ   = sbp2_हटाओ,
	.id_table = sbp2_id_table,
पूर्ण;

अटल व्योम sbp2_unmap_scatterlist(काष्ठा device *card_device,
				   काष्ठा sbp2_command_orb *orb)
अणु
	scsi_dma_unmap(orb->cmd);

	अगर (orb->request.misc & cpu_to_be32(COMMAND_ORB_PAGE_TABLE_PRESENT))
		dma_unmap_single(card_device, orb->page_table_bus,
				 माप(orb->page_table), DMA_TO_DEVICE);
पूर्ण

अटल अचिन्हित पूर्णांक sbp2_status_to_sense_data(u8 *sbp2_status, u8 *sense_data)
अणु
	पूर्णांक sam_status;
	पूर्णांक sfmt = (sbp2_status[0] >> 6) & 0x03;

	अगर (sfmt == 2 || sfmt == 3) अणु
		/*
		 * Reserved क्रम future standardization (2) or
		 * Status block क्रमmat venकरोr-dependent (3)
		 */
		वापस DID_ERROR << 16;
	पूर्ण

	sense_data[0] = 0x70 | sfmt | (sbp2_status[1] & 0x80);
	sense_data[1] = 0x0;
	sense_data[2] = ((sbp2_status[1] << 1) & 0xe0) | (sbp2_status[1] & 0x0f);
	sense_data[3] = sbp2_status[4];
	sense_data[4] = sbp2_status[5];
	sense_data[5] = sbp2_status[6];
	sense_data[6] = sbp2_status[7];
	sense_data[7] = 10;
	sense_data[8] = sbp2_status[8];
	sense_data[9] = sbp2_status[9];
	sense_data[10] = sbp2_status[10];
	sense_data[11] = sbp2_status[11];
	sense_data[12] = sbp2_status[2];
	sense_data[13] = sbp2_status[3];
	sense_data[14] = sbp2_status[12];
	sense_data[15] = sbp2_status[13];

	sam_status = sbp2_status[0] & 0x3f;

	चयन (sam_status) अणु
	हाल SAM_STAT_GOOD:
	हाल SAM_STAT_CHECK_CONDITION:
	हाल SAM_STAT_CONDITION_MET:
	हाल SAM_STAT_BUSY:
	हाल SAM_STAT_RESERVATION_CONFLICT:
	हाल SAM_STAT_COMMAND_TERMINATED:
		वापस DID_OK << 16 | sam_status;

	शेष:
		वापस DID_ERROR << 16;
	पूर्ण
पूर्ण

अटल व्योम complete_command_orb(काष्ठा sbp2_orb *base_orb,
				 काष्ठा sbp2_status *status)
अणु
	काष्ठा sbp2_command_orb *orb =
		container_of(base_orb, काष्ठा sbp2_command_orb, base);
	काष्ठा fw_device *device = target_parent_device(base_orb->lu->tgt);
	पूर्णांक result;

	अगर (status != शून्य) अणु
		अगर (STATUS_GET_DEAD(*status))
			sbp2_agent_reset_no_रुको(base_orb->lu);

		चयन (STATUS_GET_RESPONSE(*status)) अणु
		हाल SBP2_STATUS_REQUEST_COMPLETE:
			result = DID_OK << 16;
			अवरोध;
		हाल SBP2_STATUS_TRANSPORT_FAILURE:
			result = DID_BUS_BUSY << 16;
			अवरोध;
		हाल SBP2_STATUS_ILLEGAL_REQUEST:
		हाल SBP2_STATUS_VENDOR_DEPENDENT:
		शेष:
			result = DID_ERROR << 16;
			अवरोध;
		पूर्ण

		अगर (result == DID_OK << 16 && STATUS_GET_LEN(*status) > 1)
			result = sbp2_status_to_sense_data(STATUS_GET_DATA(*status),
							   orb->cmd->sense_buffer);
	पूर्ण अन्यथा अणु
		/*
		 * If the orb completes with status == शून्य, something
		 * went wrong, typically a bus reset happened mid-orb
		 * or when sending the ग_लिखो (less likely).
		 */
		result = DID_BUS_BUSY << 16;
		sbp2_conditionally_block(base_orb->lu);
	पूर्ण

	dma_unmap_single(device->card->device, orb->base.request_bus,
			 माप(orb->request), DMA_TO_DEVICE);
	sbp2_unmap_scatterlist(device->card->device, orb);

	orb->cmd->result = result;
	orb->cmd->scsi_करोne(orb->cmd);
पूर्ण

अटल पूर्णांक sbp2_map_scatterlist(काष्ठा sbp2_command_orb *orb,
		काष्ठा fw_device *device, काष्ठा sbp2_logical_unit *lu)
अणु
	काष्ठा scatterlist *sg = scsi_sglist(orb->cmd);
	पूर्णांक i, n;

	n = scsi_dma_map(orb->cmd);
	अगर (n <= 0)
		जाओ fail;

	/*
	 * Handle the special हाल where there is only one element in
	 * the scatter list by converting it to an immediate block
	 * request. This is also a workaround क्रम broken devices such
	 * as the second generation iPod which करोesn't support page
	 * tables.
	 */
	अगर (n == 1) अणु
		orb->request.data_descriptor.high =
			cpu_to_be32(lu->tgt->address_high);
		orb->request.data_descriptor.low  =
			cpu_to_be32(sg_dma_address(sg));
		orb->request.misc |=
			cpu_to_be32(COMMAND_ORB_DATA_SIZE(sg_dma_len(sg)));
		वापस 0;
	पूर्ण

	क्रम_each_sg(sg, sg, n, i) अणु
		orb->page_table[i].high = cpu_to_be32(sg_dma_len(sg) << 16);
		orb->page_table[i].low = cpu_to_be32(sg_dma_address(sg));
	पूर्ण

	orb->page_table_bus =
		dma_map_single(device->card->device, orb->page_table,
			       माप(orb->page_table), DMA_TO_DEVICE);
	अगर (dma_mapping_error(device->card->device, orb->page_table_bus))
		जाओ fail_page_table;

	/*
	 * The data_descriptor poपूर्णांकer is the one हाल where we need
	 * to fill in the node ID part of the address.  All other
	 * poपूर्णांकers assume that the data referenced reside on the
	 * initiator (i.e. us), but data_descriptor can refer to data
	 * on other nodes so we need to put our ID in descriptor.high.
	 */
	orb->request.data_descriptor.high = cpu_to_be32(lu->tgt->address_high);
	orb->request.data_descriptor.low  = cpu_to_be32(orb->page_table_bus);
	orb->request.misc |= cpu_to_be32(COMMAND_ORB_PAGE_TABLE_PRESENT |
					 COMMAND_ORB_DATA_SIZE(n));

	वापस 0;

 fail_page_table:
	scsi_dma_unmap(orb->cmd);
 fail:
	वापस -ENOMEM;
पूर्ण

/* SCSI stack पूर्णांकegration */

अटल पूर्णांक sbp2_scsi_queuecommand(काष्ठा Scsi_Host *shost,
				  काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा sbp2_logical_unit *lu = cmd->device->hostdata;
	काष्ठा fw_device *device = target_parent_device(lu->tgt);
	काष्ठा sbp2_command_orb *orb;
	पूर्णांक generation, retval = SCSI_MLQUEUE_HOST_BUSY;

	orb = kzalloc(माप(*orb), GFP_ATOMIC);
	अगर (orb == शून्य)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/* Initialize rcode to something not RCODE_COMPLETE. */
	orb->base.rcode = -1;
	kref_init(&orb->base.kref);
	orb->cmd = cmd;
	orb->request.next.high = cpu_to_be32(SBP2_ORB_शून्य);
	orb->request.misc = cpu_to_be32(
		COMMAND_ORB_MAX_PAYLOAD(lu->tgt->max_payload) |
		COMMAND_ORB_SPEED(device->max_speed) |
		COMMAND_ORB_NOTIFY);

	अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
		orb->request.misc |= cpu_to_be32(COMMAND_ORB_सूचीECTION);

	generation = device->generation;
	smp_rmb();    /* sbp2_map_scatterlist looks at tgt->address_high */

	अगर (scsi_sg_count(cmd) && sbp2_map_scatterlist(orb, device, lu) < 0)
		जाओ out;

	स_नकल(orb->request.command_block, cmd->cmnd, cmd->cmd_len);

	orb->base.callback = complete_command_orb;
	orb->base.request_bus =
		dma_map_single(device->card->device, &orb->request,
			       माप(orb->request), DMA_TO_DEVICE);
	अगर (dma_mapping_error(device->card->device, orb->base.request_bus)) अणु
		sbp2_unmap_scatterlist(device->card->device, orb);
		जाओ out;
	पूर्ण

	sbp2_send_orb(&orb->base, lu, lu->tgt->node_id, generation,
		      lu->command_block_agent_address + SBP2_ORB_POINTER);
	retval = 0;
 out:
	kref_put(&orb->base.kref, मुक्त_orb);
	वापस retval;
पूर्ण

अटल पूर्णांक sbp2_scsi_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sbp2_logical_unit *lu = sdev->hostdata;

	/* (Re-)Adding logical units via the SCSI stack is not supported. */
	अगर (!lu)
		वापस -ENOSYS;

	sdev->allow_restart = 1;

	/*
	 * SBP-2 करोes not require any alignment, but we set it anyway
	 * क्रम compatibility with earlier versions of this driver.
	 */
	blk_queue_update_dma_alignment(sdev->request_queue, 4 - 1);

	अगर (lu->tgt->workarounds & SBP2_WORKAROUND_INQUIRY_36)
		sdev->inquiry_len = 36;

	वापस 0;
पूर्ण

अटल पूर्णांक sbp2_scsi_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sbp2_logical_unit *lu = sdev->hostdata;

	sdev->use_10_क्रम_rw = 1;

	अगर (sbp2_param_exclusive_login)
		sdev->manage_start_stop = 1;

	अगर (sdev->type == TYPE_ROM)
		sdev->use_10_क्रम_ms = 1;

	अगर (sdev->type == TYPE_DISK &&
	    lu->tgt->workarounds & SBP2_WORKAROUND_MODE_SENSE_8)
		sdev->skip_ms_page_8 = 1;

	अगर (lu->tgt->workarounds & SBP2_WORKAROUND_FIX_CAPACITY)
		sdev->fix_capacity = 1;

	अगर (lu->tgt->workarounds & SBP2_WORKAROUND_POWER_CONDITION)
		sdev->start_stop_pwr_cond = 1;

	अगर (lu->tgt->workarounds & SBP2_WORKAROUND_128K_MAX_TRANS)
		blk_queue_max_hw_sectors(sdev->request_queue, 128 * 1024 / 512);

	वापस 0;
पूर्ण

/*
 * Called by scsi stack when something has really gone wrong.  Usually
 * called when a command has समयd-out क्रम some reason.
 */
अटल पूर्णांक sbp2_scsi_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा sbp2_logical_unit *lu = cmd->device->hostdata;

	dev_notice(lu_dev(lu), "sbp2_scsi_abort\n");
	sbp2_agent_reset(lu);
	sbp2_cancel_orbs(lu);

	वापस SUCCESS;
पूर्ण

/*
 * Format of /sys/bus/scsi/devices/.../ieee1394_id:
 * u64 EUI-64 : u24 directory_ID : u16 LUN  (all prपूर्णांकed in hexadecimal)
 *
 * This is the concatenation of target port identअगरier and logical unit
 * identअगरier as per SAM-2...SAM-4 annex A.
 */
अटल sमाप_प्रकार sbp2_sysfs_ieee1394_id_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा sbp2_logical_unit *lu;

	अगर (!sdev)
		वापस 0;

	lu = sdev->hostdata;

	वापस प्र_लिखो(buf, "%016llx:%06x:%04x\n",
			(अचिन्हित दीर्घ दीर्घ)lu->tgt->guid,
			lu->tgt->directory_id, lu->lun);
पूर्ण

अटल DEVICE_ATTR(ieee1394_id, S_IRUGO, sbp2_sysfs_ieee1394_id_show, शून्य);

अटल काष्ठा device_attribute *sbp2_scsi_sysfs_attrs[] = अणु
	&dev_attr_ieee1394_id,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा scsi_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "SBP-2 IEEE-1394",
	.proc_name		= "sbp2",
	.queuecommand		= sbp2_scsi_queuecommand,
	.slave_alloc		= sbp2_scsi_slave_alloc,
	.slave_configure	= sbp2_scsi_slave_configure,
	.eh_पात_handler	= sbp2_scsi_पात,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
	.max_segment_size	= SBP2_MAX_SEG_SIZE,
	.can_queue		= 1,
	.sdev_attrs		= sbp2_scsi_sysfs_attrs,
पूर्ण;

MODULE_AUTHOR("Kristian Hoegsberg <krh@bitplanet.net>");
MODULE_DESCRIPTION("SCSI over IEEE1394");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(ieee1394, sbp2_id_table);

/* Provide a module alias so root-on-sbp2 initrds करोn't अवरोध. */
MODULE_ALIAS("sbp2");

अटल पूर्णांक __init sbp2_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&sbp2_driver.driver);
पूर्ण

अटल व्योम __निकास sbp2_cleanup(व्योम)
अणु
	driver_unरेजिस्टर(&sbp2_driver.driver);
पूर्ण

module_init(sbp2_init);
module_निकास(sbp2_cleanup);
