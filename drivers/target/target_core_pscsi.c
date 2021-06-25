<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_pscsi.c
 *
 * This file contains the generic target mode <-> Linux SCSI subप्रणाली plugin.
 *
 * (c) Copyright 2003-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/समयr.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/genhd.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>

#समावेश "target_core_alua.h"
#समावेश "target_core_internal.h"
#समावेश "target_core_pscsi.h"

अटल अंतरभूत काष्ठा pscsi_dev_virt *PSCSI_DEV(काष्ठा se_device *dev)
अणु
	वापस container_of(dev, काष्ठा pscsi_dev_virt, dev);
पूर्ण

अटल sense_reason_t pscsi_execute_cmd(काष्ठा se_cmd *cmd);
अटल व्योम pscsi_req_करोne(काष्ठा request *, blk_status_t);

/*	pscsi_attach_hba():
 *
 * 	pscsi_get_sh() used scsi_host_lookup() to locate काष्ठा Scsi_Host.
 *	from the passed SCSI Host ID.
 */
अटल पूर्णांक pscsi_attach_hba(काष्ठा se_hba *hba, u32 host_id)
अणु
	काष्ठा pscsi_hba_virt *phv;

	phv = kzalloc(माप(काष्ठा pscsi_hba_virt), GFP_KERNEL);
	अगर (!phv) अणु
		pr_err("Unable to allocate struct pscsi_hba_virt\n");
		वापस -ENOMEM;
	पूर्ण
	phv->phv_host_id = host_id;
	phv->phv_mode = PHV_VIRTUAL_HOST_ID;

	hba->hba_ptr = phv;

	pr_debug("CORE_HBA[%d] - TCM SCSI HBA Driver %s on"
		" Generic Target Core Stack %s\n", hba->hba_id,
		PSCSI_VERSION, TARGET_CORE_VERSION);
	pr_debug("CORE_HBA[%d] - Attached SCSI HBA to Generic\n",
	       hba->hba_id);

	वापस 0;
पूर्ण

अटल व्योम pscsi_detach_hba(काष्ठा se_hba *hba)
अणु
	काष्ठा pscsi_hba_virt *phv = hba->hba_ptr;
	काष्ठा Scsi_Host *scsi_host = phv->phv_lld_host;

	अगर (scsi_host) अणु
		scsi_host_put(scsi_host);

		pr_debug("CORE_HBA[%d] - Detached SCSI HBA: %s from"
			" Generic Target Core\n", hba->hba_id,
			(scsi_host->hostt->name) ? (scsi_host->hostt->name) :
			"Unknown");
	पूर्ण अन्यथा
		pr_debug("CORE_HBA[%d] - Detached Virtual SCSI HBA"
			" from Generic Target Core\n", hba->hba_id);

	kमुक्त(phv);
	hba->hba_ptr = शून्य;
पूर्ण

अटल पूर्णांक pscsi_pmode_enable_hba(काष्ठा se_hba *hba, अचिन्हित दीर्घ mode_flag)
अणु
	काष्ठा pscsi_hba_virt *phv = hba->hba_ptr;
	काष्ठा Scsi_Host *sh = phv->phv_lld_host;
	/*
	 * Release the काष्ठा Scsi_Host
	 */
	अगर (!mode_flag) अणु
		अगर (!sh)
			वापस 0;

		phv->phv_lld_host = शून्य;
		phv->phv_mode = PHV_VIRTUAL_HOST_ID;

		pr_debug("CORE_HBA[%d] - Disabled pSCSI HBA Passthrough"
			" %s\n", hba->hba_id, (sh->hostt->name) ?
			(sh->hostt->name) : "Unknown");

		scsi_host_put(sh);
		वापस 0;
	पूर्ण
	/*
	 * Otherwise, locate काष्ठा Scsi_Host from the original passed
	 * pSCSI Host ID and enable क्रम phba mode
	 */
	sh = scsi_host_lookup(phv->phv_host_id);
	अगर (!sh) अणु
		pr_err("pSCSI: Unable to locate SCSI Host for"
			" phv_host_id: %d\n", phv->phv_host_id);
		वापस -EINVAL;
	पूर्ण

	phv->phv_lld_host = sh;
	phv->phv_mode = PHV_LLD_SCSI_HOST_NO;

	pr_debug("CORE_HBA[%d] - Enabled pSCSI HBA Passthrough %s\n",
		hba->hba_id, (sh->hostt->name) ? (sh->hostt->name) : "Unknown");

	वापस 1;
पूर्ण

अटल व्योम pscsi_tape_पढ़ो_blocksize(काष्ठा se_device *dev,
		काष्ठा scsi_device *sdev)
अणु
	अचिन्हित अक्षर cdb[MAX_COMMAND_SIZE], *buf;
	पूर्णांक ret;

	buf = kzalloc(12, GFP_KERNEL);
	अगर (!buf)
		जाओ out_मुक्त;

	स_रखो(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = MODE_SENSE;
	cdb[4] = 0x0c; /* 12 bytes */

	ret = scsi_execute_req(sdev, cdb, DMA_FROM_DEVICE, buf, 12, शून्य,
			HZ, 1, शून्य);
	अगर (ret)
		जाओ out_मुक्त;

	/*
	 * If MODE_SENSE still वापसs zero, set the शेष value to 1024.
	 */
	sdev->sector_size = get_unaligned_be24(&buf[9]);
out_मुक्त:
	अगर (!sdev->sector_size)
		sdev->sector_size = 1024;

	kमुक्त(buf);
पूर्ण

अटल व्योम
pscsi_set_inquiry_info(काष्ठा scsi_device *sdev, काष्ठा t10_wwn *wwn)
अणु
	अगर (sdev->inquiry_len < INQUIRY_LEN)
		वापस;
	/*
	 * Use sdev->inquiry data from drivers/scsi/scsi_scan.c:scsi_add_lun()
	 */
	BUILD_BUG_ON(माप(wwn->venकरोr) != INQUIRY_VENDOR_LEN + 1);
	snम_लिखो(wwn->venकरोr, माप(wwn->venकरोr),
		 "%." __stringअगरy(INQUIRY_VENDOR_LEN) "s", sdev->venकरोr);
	BUILD_BUG_ON(माप(wwn->model) != INQUIRY_MODEL_LEN + 1);
	snम_लिखो(wwn->model, माप(wwn->model),
		 "%." __stringअगरy(INQUIRY_MODEL_LEN) "s", sdev->model);
	BUILD_BUG_ON(माप(wwn->revision) != INQUIRY_REVISION_LEN + 1);
	snम_लिखो(wwn->revision, माप(wwn->revision),
		 "%." __stringअगरy(INQUIRY_REVISION_LEN) "s", sdev->rev);
पूर्ण

अटल पूर्णांक
pscsi_get_inquiry_vpd_serial(काष्ठा scsi_device *sdev, काष्ठा t10_wwn *wwn)
अणु
	अचिन्हित अक्षर cdb[MAX_COMMAND_SIZE], *buf;
	पूर्णांक ret;

	buf = kzalloc(INQUIRY_VPD_SERIAL_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	स_रखो(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = INQUIRY;
	cdb[1] = 0x01; /* Query VPD */
	cdb[2] = 0x80; /* Unit Serial Number */
	put_unaligned_be16(INQUIRY_VPD_SERIAL_LEN, &cdb[3]);

	ret = scsi_execute_req(sdev, cdb, DMA_FROM_DEVICE, buf,
			      INQUIRY_VPD_SERIAL_LEN, शून्य, HZ, 1, शून्य);
	अगर (ret)
		जाओ out_मुक्त;

	snम_लिखो(&wwn->unit_serial[0], INQUIRY_VPD_SERIAL_LEN, "%s", &buf[4]);

	wwn->t10_dev->dev_flags |= DF_FIRMWARE_VPD_UNIT_SERIAL;

	kमुक्त(buf);
	वापस 0;

out_मुक्त:
	kमुक्त(buf);
	वापस -EPERM;
पूर्ण

अटल व्योम
pscsi_get_inquiry_vpd_device_ident(काष्ठा scsi_device *sdev,
		काष्ठा t10_wwn *wwn)
अणु
	अचिन्हित अक्षर cdb[MAX_COMMAND_SIZE], *buf, *page_83;
	पूर्णांक ident_len, page_len, off = 4, ret;
	काष्ठा t10_vpd *vpd;

	buf = kzalloc(INQUIRY_VPD_SERIAL_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस;

	स_रखो(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = INQUIRY;
	cdb[1] = 0x01; /* Query VPD */
	cdb[2] = 0x83; /* Device Identअगरier */
	put_unaligned_be16(INQUIRY_VPD_DEVICE_IDENTIFIER_LEN, &cdb[3]);

	ret = scsi_execute_req(sdev, cdb, DMA_FROM_DEVICE, buf,
			      INQUIRY_VPD_DEVICE_IDENTIFIER_LEN,
			      शून्य, HZ, 1, शून्य);
	अगर (ret)
		जाओ out;

	page_len = get_unaligned_be16(&buf[2]);
	जबतक (page_len > 0) अणु
		/* Grab a poपूर्णांकer to the Identअगरication descriptor */
		page_83 = &buf[off];
		ident_len = page_83[3];
		अगर (!ident_len) अणु
			pr_err("page_83[3]: identifier"
					" length zero!\n");
			अवरोध;
		पूर्ण
		pr_debug("T10 VPD Identifier Length: %d\n", ident_len);

		vpd = kzalloc(माप(काष्ठा t10_vpd), GFP_KERNEL);
		अगर (!vpd) अणु
			pr_err("Unable to allocate memory for"
					" struct t10_vpd\n");
			जाओ out;
		पूर्ण
		INIT_LIST_HEAD(&vpd->vpd_list);

		transport_set_vpd_proto_id(vpd, page_83);
		transport_set_vpd_assoc(vpd, page_83);

		अगर (transport_set_vpd_ident_type(vpd, page_83) < 0) अणु
			off += (ident_len + 4);
			page_len -= (ident_len + 4);
			kमुक्त(vpd);
			जारी;
		पूर्ण
		अगर (transport_set_vpd_ident(vpd, page_83) < 0) अणु
			off += (ident_len + 4);
			page_len -= (ident_len + 4);
			kमुक्त(vpd);
			जारी;
		पूर्ण

		list_add_tail(&vpd->vpd_list, &wwn->t10_vpd_list);
		off += (ident_len + 4);
		page_len -= (ident_len + 4);
	पूर्ण

out:
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक pscsi_add_device_to_list(काष्ठा se_device *dev,
		काष्ठा scsi_device *sd)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा request_queue *q = sd->request_queue;

	pdv->pdv_sd = sd;

	अगर (!sd->queue_depth) अणु
		sd->queue_depth = PSCSI_DEFAULT_QUEUEDEPTH;

		pr_err("Set broken SCSI Device %d:%d:%llu"
			" queue_depth to %d\n", sd->channel, sd->id,
				sd->lun, sd->queue_depth);
	पूर्ण

	dev->dev_attrib.hw_block_size =
		min_not_zero((पूर्णांक)sd->sector_size, 512);
	dev->dev_attrib.hw_max_sectors =
		min_not_zero(sd->host->max_sectors, queue_max_hw_sectors(q));
	dev->dev_attrib.hw_queue_depth = sd->queue_depth;

	/*
	 * Setup our standard INQUIRY info पूर्णांकo se_dev->t10_wwn
	 */
	pscsi_set_inquiry_info(sd, &dev->t10_wwn);

	/*
	 * Locate VPD WWN Inक्रमmation used क्रम various purposes within
	 * the Storage Engine.
	 */
	अगर (!pscsi_get_inquiry_vpd_serial(sd, &dev->t10_wwn)) अणु
		/*
		 * If VPD Unit Serial वापसed GOOD status, try
		 * VPD Device Identअगरication page (0x83).
		 */
		pscsi_get_inquiry_vpd_device_ident(sd, &dev->t10_wwn);
	पूर्ण

	/*
	 * For TYPE_TAPE, attempt to determine blocksize with MODE_SENSE.
	 */
	अगर (sd->type == TYPE_TAPE) अणु
		pscsi_tape_पढ़ो_blocksize(dev, sd);
		dev->dev_attrib.hw_block_size = sd->sector_size;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा se_device *pscsi_alloc_device(काष्ठा se_hba *hba,
		स्थिर अक्षर *name)
अणु
	काष्ठा pscsi_dev_virt *pdv;

	pdv = kzalloc(माप(काष्ठा pscsi_dev_virt), GFP_KERNEL);
	अगर (!pdv) अणु
		pr_err("Unable to allocate memory for struct pscsi_dev_virt\n");
		वापस शून्य;
	पूर्ण

	pr_debug("PSCSI: Allocated pdv: %p for %s\n", pdv, name);
	वापस &pdv->dev;
पूर्ण

/*
 * Called with काष्ठा Scsi_Host->host_lock called.
 */
अटल पूर्णांक pscsi_create_type_disk(काष्ठा se_device *dev, काष्ठा scsi_device *sd)
	__releases(sh->host_lock)
अणु
	काष्ठा pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा Scsi_Host *sh = sd->host;
	काष्ठा block_device *bd;
	पूर्णांक ret;

	अगर (scsi_device_get(sd)) अणु
		pr_err("scsi_device_get() failed for %d:%d:%d:%llu\n",
			sh->host_no, sd->channel, sd->id, sd->lun);
		spin_unlock_irq(sh->host_lock);
		वापस -EIO;
	पूर्ण
	spin_unlock_irq(sh->host_lock);
	/*
	 * Claim exclusive काष्ठा block_device access to काष्ठा scsi_device
	 * क्रम TYPE_DISK and TYPE_ZBC using supplied udev_path
	 */
	bd = blkdev_get_by_path(dev->udev_path,
				FMODE_WRITE|FMODE_READ|FMODE_EXCL, pdv);
	अगर (IS_ERR(bd)) अणु
		pr_err("pSCSI: blkdev_get_by_path() failed\n");
		scsi_device_put(sd);
		वापस PTR_ERR(bd);
	पूर्ण
	pdv->pdv_bd = bd;

	ret = pscsi_add_device_to_list(dev, sd);
	अगर (ret) अणु
		blkdev_put(pdv->pdv_bd, FMODE_WRITE|FMODE_READ|FMODE_EXCL);
		scsi_device_put(sd);
		वापस ret;
	पूर्ण

	pr_debug("CORE_PSCSI[%d] - Added TYPE_%s for %d:%d:%d:%llu\n",
		phv->phv_host_id, sd->type == TYPE_DISK ? "DISK" : "ZBC",
		sh->host_no, sd->channel, sd->id, sd->lun);
	वापस 0;
पूर्ण

/*
 * Called with काष्ठा Scsi_Host->host_lock called.
 */
अटल पूर्णांक pscsi_create_type_nondisk(काष्ठा se_device *dev, काष्ठा scsi_device *sd)
	__releases(sh->host_lock)
अणु
	काष्ठा pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	काष्ठा Scsi_Host *sh = sd->host;
	पूर्णांक ret;

	अगर (scsi_device_get(sd)) अणु
		pr_err("scsi_device_get() failed for %d:%d:%d:%llu\n",
			sh->host_no, sd->channel, sd->id, sd->lun);
		spin_unlock_irq(sh->host_lock);
		वापस -EIO;
	पूर्ण
	spin_unlock_irq(sh->host_lock);

	ret = pscsi_add_device_to_list(dev, sd);
	अगर (ret) अणु
		scsi_device_put(sd);
		वापस ret;
	पूर्ण
	pr_debug("CORE_PSCSI[%d] - Added Type: %s for %d:%d:%d:%llu\n",
		phv->phv_host_id, scsi_device_type(sd->type), sh->host_no,
		sd->channel, sd->id, sd->lun);

	वापस 0;
पूर्ण

अटल पूर्णांक pscsi_configure_device(काष्ठा se_device *dev)
अणु
	काष्ठा se_hba *hba = dev->se_hba;
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा scsi_device *sd;
	काष्ठा pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	काष्ठा Scsi_Host *sh = phv->phv_lld_host;
	पूर्णांक legacy_mode_enable = 0;
	पूर्णांक ret;

	अगर (!(pdv->pdv_flags & PDF_HAS_CHANNEL_ID) ||
	    !(pdv->pdv_flags & PDF_HAS_TARGET_ID) ||
	    !(pdv->pdv_flags & PDF_HAS_LUN_ID)) अणु
		pr_err("Missing scsi_channel_id=, scsi_target_id= and"
			" scsi_lun_id= parameters\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * If not running in PHV_LLD_SCSI_HOST_NO mode, locate the
	 * काष्ठा Scsi_Host we will need to bring the TCM/pSCSI object online
	 */
	अगर (!sh) अणु
		अगर (phv->phv_mode == PHV_LLD_SCSI_HOST_NO) अणु
			pr_err("pSCSI: Unable to locate struct"
				" Scsi_Host for PHV_LLD_SCSI_HOST_NO\n");
			वापस -ENODEV;
		पूर्ण
		/*
		 * For the newer PHV_VIRTUAL_HOST_ID काष्ठा scsi_device
		 * reference, we enक्रमce that udev_path has been set
		 */
		अगर (!(dev->dev_flags & DF_USING_UDEV_PATH)) अणु
			pr_err("pSCSI: udev_path attribute has not"
				" been set before ENABLE=1\n");
			वापस -EINVAL;
		पूर्ण
		/*
		 * If no scsi_host_id= was passed क्रम PHV_VIRTUAL_HOST_ID,
		 * use the original TCM hba ID to reference Linux/SCSI Host No
		 * and enable क्रम PHV_LLD_SCSI_HOST_NO mode.
		 */
		अगर (!(pdv->pdv_flags & PDF_HAS_VIRT_HOST_ID)) अणु
			अगर (hba->dev_count) अणु
				pr_err("pSCSI: Unable to set hba_mode"
					" with active devices\n");
				वापस -EEXIST;
			पूर्ण

			अगर (pscsi_pmode_enable_hba(hba, 1) != 1)
				वापस -ENODEV;

			legacy_mode_enable = 1;
			hba->hba_flags |= HBA_FLAGS_PSCSI_MODE;
			sh = phv->phv_lld_host;
		पूर्ण अन्यथा अणु
			sh = scsi_host_lookup(pdv->pdv_host_id);
			अगर (!sh) अणु
				pr_err("pSCSI: Unable to locate"
					" pdv_host_id: %d\n", pdv->pdv_host_id);
				वापस -EINVAL;
			पूर्ण
			pdv->pdv_lld_host = sh;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (phv->phv_mode == PHV_VIRTUAL_HOST_ID) अणु
			pr_err("pSCSI: PHV_VIRTUAL_HOST_ID set while"
				" struct Scsi_Host exists\n");
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	spin_lock_irq(sh->host_lock);
	list_क्रम_each_entry(sd, &sh->__devices, siblings) अणु
		अगर ((pdv->pdv_channel_id != sd->channel) ||
		    (pdv->pdv_target_id != sd->id) ||
		    (pdv->pdv_lun_id != sd->lun))
			जारी;
		/*
		 * Functions will release the held काष्ठा scsi_host->host_lock
		 * beक्रमe calling calling pscsi_add_device_to_list() to रेजिस्टर
		 * काष्ठा scsi_device with target_core_mod.
		 */
		चयन (sd->type) अणु
		हाल TYPE_DISK:
		हाल TYPE_ZBC:
			ret = pscsi_create_type_disk(dev, sd);
			अवरोध;
		शेष:
			ret = pscsi_create_type_nondisk(dev, sd);
			अवरोध;
		पूर्ण

		अगर (ret) अणु
			अगर (phv->phv_mode == PHV_VIRTUAL_HOST_ID)
				scsi_host_put(sh);
			अन्यथा अगर (legacy_mode_enable) अणु
				pscsi_pmode_enable_hba(hba, 0);
				hba->hba_flags &= ~HBA_FLAGS_PSCSI_MODE;
			पूर्ण
			pdv->pdv_sd = शून्य;
			वापस ret;
		पूर्ण
		वापस 0;
	पूर्ण
	spin_unlock_irq(sh->host_lock);

	pr_err("pSCSI: Unable to locate %d:%d:%d:%d\n", sh->host_no,
		pdv->pdv_channel_id,  pdv->pdv_target_id, pdv->pdv_lun_id);

	अगर (phv->phv_mode == PHV_VIRTUAL_HOST_ID)
		scsi_host_put(sh);
	अन्यथा अगर (legacy_mode_enable) अणु
		pscsi_pmode_enable_hba(hba, 0);
		hba->hba_flags &= ~HBA_FLAGS_PSCSI_MODE;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम pscsi_dev_call_rcu(काष्ठा rcu_head *p)
अणु
	काष्ठा se_device *dev = container_of(p, काष्ठा se_device, rcu_head);
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);

	kमुक्त(pdv);
पूर्ण

अटल व्योम pscsi_मुक्त_device(काष्ठा se_device *dev)
अणु
	call_rcu(&dev->rcu_head, pscsi_dev_call_rcu);
पूर्ण

अटल व्योम pscsi_destroy_device(काष्ठा se_device *dev)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	काष्ठा scsi_device *sd = pdv->pdv_sd;

	अगर (sd) अणु
		/*
		 * Release exclusive pSCSI पूर्णांकernal काष्ठा block_device claim क्रम
		 * काष्ठा scsi_device with TYPE_DISK or TYPE_ZBC
		 * from pscsi_create_type_disk()
		 */
		अगर ((sd->type == TYPE_DISK || sd->type == TYPE_ZBC) &&
		    pdv->pdv_bd) अणु
			blkdev_put(pdv->pdv_bd,
				   FMODE_WRITE|FMODE_READ|FMODE_EXCL);
			pdv->pdv_bd = शून्य;
		पूर्ण
		/*
		 * For HBA mode PHV_LLD_SCSI_HOST_NO, release the reference
		 * to काष्ठा Scsi_Host now.
		 */
		अगर ((phv->phv_mode == PHV_LLD_SCSI_HOST_NO) &&
		    (phv->phv_lld_host != शून्य))
			scsi_host_put(phv->phv_lld_host);
		अन्यथा अगर (pdv->pdv_lld_host)
			scsi_host_put(pdv->pdv_lld_host);

		scsi_device_put(sd);

		pdv->pdv_sd = शून्य;
	पूर्ण
पूर्ण

अटल व्योम pscsi_complete_cmd(काष्ठा se_cmd *cmd, u8 scsi_status,
			       अचिन्हित अक्षर *req_sense)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(cmd->se_dev);
	काष्ठा scsi_device *sd = pdv->pdv_sd;
	काष्ठा pscsi_plugin_task *pt = cmd->priv;
	अचिन्हित अक्षर *cdb;
	/*
	 * Special हाल क्रम REPORT_LUNs handling where pscsi_plugin_task has
	 * not been allocated because TCM is handling the emulation directly.
	 */
	अगर (!pt)
		वापस;

	cdb = &pt->pscsi_cdb[0];
	/*
	 * Hack to make sure that Write-Protect modepage is set अगर R/O mode is
	 * क्रमced.
	 */
	अगर (!cmd->data_length)
		जाओ after_mode_sense;

	अगर (((cdb[0] == MODE_SENSE) || (cdb[0] == MODE_SENSE_10)) &&
	    scsi_status == SAM_STAT_GOOD) अणु
		bool पढ़ो_only = target_lun_is_rकरोnly(cmd);

		अगर (पढ़ो_only) अणु
			अचिन्हित अक्षर *buf;

			buf = transport_kmap_data_sg(cmd);
			अगर (!buf) अणु
				; /* XXX: TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE */
			पूर्ण

			अगर (cdb[0] == MODE_SENSE_10) अणु
				अगर (!(buf[3] & 0x80))
					buf[3] |= 0x80;
			पूर्ण अन्यथा अणु
				अगर (!(buf[2] & 0x80))
					buf[2] |= 0x80;
			पूर्ण

			transport_kunmap_data_sg(cmd);
		पूर्ण
	पूर्ण
after_mode_sense:

	अगर (sd->type != TYPE_TAPE || !cmd->data_length)
		जाओ after_mode_select;

	/*
	 * Hack to correctly obtain the initiator requested blocksize क्रम
	 * TYPE_TAPE.  Since this value is dependent upon each tape media,
	 * काष्ठा scsi_device->sector_size will not contain the correct value
	 * by शेष, so we go ahead and set it so
	 * TRANSPORT(dev)->get_blockdev() वापसs the correct value to the
	 * storage engine.
	 */
	अगर (((cdb[0] == MODE_SELECT) || (cdb[0] == MODE_SELECT_10)) &&
	     scsi_status == SAM_STAT_GOOD) अणु
		अचिन्हित अक्षर *buf;
		u16 bdl;
		u32 blocksize;

		buf = sg_virt(&cmd->t_data_sg[0]);
		अगर (!buf) अणु
			pr_err("Unable to get buf for scatterlist\n");
			जाओ after_mode_select;
		पूर्ण

		अगर (cdb[0] == MODE_SELECT)
			bdl = buf[3];
		अन्यथा
			bdl = get_unaligned_be16(&buf[6]);

		अगर (!bdl)
			जाओ after_mode_select;

		अगर (cdb[0] == MODE_SELECT)
			blocksize = get_unaligned_be24(&buf[9]);
		अन्यथा
			blocksize = get_unaligned_be24(&buf[13]);

		sd->sector_size = blocksize;
	पूर्ण
after_mode_select:

	अगर (scsi_status == SAM_STAT_CHECK_CONDITION) अणु
		transport_copy_sense_to_cmd(cmd, req_sense);

		/*
		 * check क्रम TAPE device पढ़ोs with
		 * FM/EOM/ILI set, so that we can get data
		 * back despite framework assumption that a
		 * check condition means there is no data
		 */
		अगर (sd->type == TYPE_TAPE &&
		    cmd->data_direction == DMA_FROM_DEVICE) अणु
			/*
			 * is sense data valid, fixed क्रमmat,
			 * and have FM, EOM, or ILI set?
			 */
			अगर (req_sense[0] == 0xf0 &&	/* valid, fixed क्रमmat */
			    req_sense[2] & 0xe0 &&	/* FM, EOM, or ILI */
			    (req_sense[2] & 0xf) == 0) अणु /* key==NO_SENSE */
				pr_debug("Tape FM/EOM/ILI status detected. Treat as normal read.\n");
				cmd->se_cmd_flags |= SCF_TREAT_READ_AS_NORMAL;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

क्रमागत अणु
	Opt_scsi_host_id, Opt_scsi_channel_id, Opt_scsi_target_id,
	Opt_scsi_lun_id, Opt_err
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_scsi_host_id, "scsi_host_id=%d"पूर्ण,
	अणुOpt_scsi_channel_id, "scsi_channel_id=%d"पूर्ण,
	अणुOpt_scsi_target_id, "scsi_target_id=%d"पूर्ण,
	अणुOpt_scsi_lun_id, "scsi_lun_id=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल sमाप_प्रकार pscsi_set_configfs_dev_params(काष्ठा se_device *dev,
		स्थिर अक्षर *page, sमाप_प्रकार count)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	अक्षर *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक ret = 0, arg, token;

	opts = kstrdup(page, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	orig = opts;

	जबतक ((ptr = strsep(&opts, ",\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		token = match_token(ptr, tokens, args);
		चयन (token) अणु
		हाल Opt_scsi_host_id:
			अगर (phv->phv_mode == PHV_LLD_SCSI_HOST_NO) अणु
				pr_err("PSCSI[%d]: Unable to accept"
					" scsi_host_id while phv_mode =="
					" PHV_LLD_SCSI_HOST_NO\n",
					phv->phv_host_id);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			pdv->pdv_host_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI Host ID:"
				" %d\n", phv->phv_host_id, pdv->pdv_host_id);
			pdv->pdv_flags |= PDF_HAS_VIRT_HOST_ID;
			अवरोध;
		हाल Opt_scsi_channel_id:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			pdv->pdv_channel_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI Channel"
				" ID: %d\n",  phv->phv_host_id,
				pdv->pdv_channel_id);
			pdv->pdv_flags |= PDF_HAS_CHANNEL_ID;
			अवरोध;
		हाल Opt_scsi_target_id:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			pdv->pdv_target_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI Target"
				" ID: %d\n", phv->phv_host_id,
				pdv->pdv_target_id);
			pdv->pdv_flags |= PDF_HAS_TARGET_ID;
			अवरोध;
		हाल Opt_scsi_lun_id:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			pdv->pdv_lun_id = arg;
			pr_debug("PSCSI[%d]: Referencing SCSI LUN ID:"
				" %d\n", phv->phv_host_id, pdv->pdv_lun_id);
			pdv->pdv_flags |= PDF_HAS_LUN_ID;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त(orig);
	वापस (!ret) ? count : ret;
पूर्ण

अटल sमाप_प्रकार pscsi_show_configfs_dev_params(काष्ठा se_device *dev, अक्षर *b)
अणु
	काष्ठा pscsi_hba_virt *phv = dev->se_hba->hba_ptr;
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा scsi_device *sd = pdv->pdv_sd;
	अचिन्हित अक्षर host_id[16];
	sमाप_प्रकार bl;

	अगर (phv->phv_mode == PHV_VIRTUAL_HOST_ID)
		snम_लिखो(host_id, 16, "%d", pdv->pdv_host_id);
	अन्यथा
		snम_लिखो(host_id, 16, "PHBA Mode");

	bl = प्र_लिखो(b, "SCSI Device Bus Location:"
		" Channel ID: %d Target ID: %d LUN: %d Host ID: %s\n",
		pdv->pdv_channel_id, pdv->pdv_target_id, pdv->pdv_lun_id,
		host_id);

	अगर (sd) अणु
		bl += प्र_लिखो(b + bl, "        Vendor: %."
			__stringअगरy(INQUIRY_VENDOR_LEN) "s", sd->venकरोr);
		bl += प्र_लिखो(b + bl, " Model: %."
			__stringअगरy(INQUIRY_MODEL_LEN) "s", sd->model);
		bl += प्र_लिखो(b + bl, " Rev: %."
			__stringअगरy(INQUIRY_REVISION_LEN) "s\n", sd->rev);
	पूर्ण
	वापस bl;
पूर्ण

अटल व्योम pscsi_bi_endio(काष्ठा bio *bio)
अणु
	bio_put(bio);
पूर्ण

अटल अंतरभूत काष्ठा bio *pscsi_get_bio(पूर्णांक nr_vecs)
अणु
	काष्ठा bio *bio;
	/*
	 * Use bio_दो_स्मृति() following the comment in क्रम bio -> काष्ठा request
	 * in block/blk-core.c:blk_make_request()
	 */
	bio = bio_kदो_स्मृति(GFP_KERNEL, nr_vecs);
	अगर (!bio) अणु
		pr_err("PSCSI: bio_kmalloc() failed\n");
		वापस शून्य;
	पूर्ण
	bio->bi_end_io = pscsi_bi_endio;

	वापस bio;
पूर्ण

अटल sense_reason_t
pscsi_map_sg(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl, u32 sgl_nents,
		काष्ठा request *req)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(cmd->se_dev);
	काष्ठा bio *bio = शून्य;
	काष्ठा page *page;
	काष्ठा scatterlist *sg;
	u32 data_len = cmd->data_length, i, len, bytes, off;
	पूर्णांक nr_pages = (cmd->data_length + sgl[0].offset +
			PAGE_SIZE - 1) >> PAGE_SHIFT;
	पूर्णांक nr_vecs = 0, rc;
	पूर्णांक rw = (cmd->data_direction == DMA_TO_DEVICE);

	BUG_ON(!cmd->data_length);

	pr_debug("PSCSI: nr_pages: %d\n", nr_pages);

	क्रम_each_sg(sgl, sg, sgl_nents, i) अणु
		page = sg_page(sg);
		off = sg->offset;
		len = sg->length;

		pr_debug("PSCSI: i: %d page: %p len: %d off: %d\n", i,
			page, len, off);

		/*
		 * We only have one page of data in each sg element,
		 * we can not cross a page boundary.
		 */
		अगर (off + len > PAGE_SIZE)
			जाओ fail;

		अगर (len > 0 && data_len > 0) अणु
			bytes = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE - off);
			bytes = min(bytes, data_len);

			अगर (!bio) अणु
new_bio:
				nr_vecs = bio_max_segs(nr_pages);
				/*
				 * Calls bio_kदो_स्मृति() and sets bio->bi_end_io()
				 */
				bio = pscsi_get_bio(nr_vecs);
				अगर (!bio)
					जाओ fail;

				अगर (rw)
					bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

				pr_debug("PSCSI: Allocated bio: %p,"
					" dir: %s nr_vecs: %d\n", bio,
					(rw) ? "rw" : "r", nr_vecs);
			पूर्ण

			pr_debug("PSCSI: Calling bio_add_pc_page() i: %d"
				" bio: %p page: %p len: %d off: %d\n", i, bio,
				page, len, off);

			rc = bio_add_pc_page(pdv->pdv_sd->request_queue,
					bio, page, bytes, off);
			pr_debug("PSCSI: bio->bi_vcnt: %d nr_vecs: %d\n",
				bio_segments(bio), nr_vecs);
			अगर (rc != bytes) अणु
				pr_debug("PSCSI: Reached bio->bi_vcnt max:"
					" %d i: %d bio: %p, allocating another"
					" bio\n", bio->bi_vcnt, i, bio);

				rc = blk_rq_append_bio(req, bio);
				अगर (rc) अणु
					pr_err("pSCSI: failed to append bio\n");
					जाओ fail;
				पूर्ण

				/*
				 * Clear the poपूर्णांकer so that another bio will
				 * be allocated with pscsi_get_bio() above.
				 */
				bio = शून्य;
				जाओ new_bio;
			पूर्ण

			data_len -= bytes;
		पूर्ण
	पूर्ण

	अगर (bio) अणु
		rc = blk_rq_append_bio(req, bio);
		अगर (rc) अणु
			pr_err("pSCSI: failed to append bio\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	अगर (bio)
		bio_put(bio);
	जबतक (req->bio) अणु
		bio = req->bio;
		req->bio = bio->bi_next;
		bio_put(bio);
	पूर्ण
	req->biotail = शून्य;
	वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
पूर्ण

अटल sense_reason_t
pscsi_parse_cdb(काष्ठा se_cmd *cmd)
अणु
	अगर (cmd->se_cmd_flags & SCF_BIDI)
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;

	वापस passthrough_parse_cdb(cmd, pscsi_execute_cmd);
पूर्ण

अटल sense_reason_t
pscsi_execute_cmd(काष्ठा se_cmd *cmd)
अणु
	काष्ठा scatterlist *sgl = cmd->t_data_sg;
	u32 sgl_nents = cmd->t_data_nents;
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(cmd->se_dev);
	काष्ठा pscsi_plugin_task *pt;
	काष्ठा request *req;
	sense_reason_t ret;

	/*
	 * Dynamically alloc cdb space, since it may be larger than
	 * TCM_MAX_COMMAND_SIZE
	 */
	pt = kzalloc(माप(*pt) + scsi_command_size(cmd->t_task_cdb), GFP_KERNEL);
	अगर (!pt) अणु
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	cmd->priv = pt;

	स_नकल(pt->pscsi_cdb, cmd->t_task_cdb,
		scsi_command_size(cmd->t_task_cdb));

	req = blk_get_request(pdv->pdv_sd->request_queue,
			cmd->data_direction == DMA_TO_DEVICE ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(req)) अणु
		pr_err("PSCSI: blk_get_request() failed\n");
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		जाओ fail;
	पूर्ण

	अगर (sgl) अणु
		ret = pscsi_map_sg(cmd, sgl, sgl_nents, req);
		अगर (ret)
			जाओ fail_put_request;
	पूर्ण

	req->end_io = pscsi_req_करोne;
	req->end_io_data = cmd;
	scsi_req(req)->cmd_len = scsi_command_size(pt->pscsi_cdb);
	scsi_req(req)->cmd = &pt->pscsi_cdb[0];
	अगर (pdv->pdv_sd->type == TYPE_DISK ||
	    pdv->pdv_sd->type == TYPE_ZBC)
		req->समयout = PS_TIMEOUT_DISK;
	अन्यथा
		req->समयout = PS_TIMEOUT_OTHER;
	scsi_req(req)->retries = PS_RETRY;

	blk_execute_rq_noरुको(शून्य, req, (cmd->sam_task_attr == TCM_HEAD_TAG),
			pscsi_req_करोne);

	वापस 0;

fail_put_request:
	blk_put_request(req);
fail:
	kमुक्त(pt);
	वापस ret;
पूर्ण

/*	pscsi_get_device_type():
 *
 *
 */
अटल u32 pscsi_get_device_type(काष्ठा se_device *dev)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);
	काष्ठा scsi_device *sd = pdv->pdv_sd;

	वापस (sd) ? sd->type : TYPE_NO_LUN;
पूर्ण

अटल sector_t pscsi_get_blocks(काष्ठा se_device *dev)
अणु
	काष्ठा pscsi_dev_virt *pdv = PSCSI_DEV(dev);

	अगर (pdv->pdv_bd)
		वापस bdev_nr_sectors(pdv->pdv_bd);
	वापस 0;
पूर्ण

अटल व्योम pscsi_req_करोne(काष्ठा request *req, blk_status_t status)
अणु
	काष्ठा se_cmd *cmd = req->end_io_data;
	काष्ठा pscsi_plugin_task *pt = cmd->priv;
	पूर्णांक result = scsi_req(req)->result;
	u8 scsi_status = status_byte(result) << 1;

	अगर (scsi_status != SAM_STAT_GOOD) अणु
		pr_debug("PSCSI Status Byte exception at cmd: %p CDB:"
			" 0x%02x Result: 0x%08x\n", cmd, pt->pscsi_cdb[0],
			result);
	पूर्ण

	pscsi_complete_cmd(cmd, scsi_status, scsi_req(req)->sense);

	चयन (host_byte(result)) अणु
	हाल DID_OK:
		target_complete_cmd_with_length(cmd, scsi_status,
			cmd->data_length - scsi_req(req)->resid_len);
		अवरोध;
	शेष:
		pr_debug("PSCSI Host Byte exception at cmd: %p CDB:"
			" 0x%02x Result: 0x%08x\n", cmd, pt->pscsi_cdb[0],
			result);
		target_complete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
		अवरोध;
	पूर्ण

	blk_put_request(req);
	kमुक्त(pt);
पूर्ण

अटल स्थिर काष्ठा target_backend_ops pscsi_ops = अणु
	.name			= "pscsi",
	.owner			= THIS_MODULE,
	.transport_flags_शेष = TRANSPORT_FLAG_PASSTHROUGH |
				   TRANSPORT_FLAG_PASSTHROUGH_ALUA |
				   TRANSPORT_FLAG_PASSTHROUGH_PGR,
	.attach_hba		= pscsi_attach_hba,
	.detach_hba		= pscsi_detach_hba,
	.pmode_enable_hba	= pscsi_pmode_enable_hba,
	.alloc_device		= pscsi_alloc_device,
	.configure_device	= pscsi_configure_device,
	.destroy_device		= pscsi_destroy_device,
	.मुक्त_device		= pscsi_मुक्त_device,
	.parse_cdb		= pscsi_parse_cdb,
	.set_configfs_dev_params = pscsi_set_configfs_dev_params,
	.show_configfs_dev_params = pscsi_show_configfs_dev_params,
	.get_device_type	= pscsi_get_device_type,
	.get_blocks		= pscsi_get_blocks,
	.tb_dev_attrib_attrs	= passthrough_attrib_attrs,
पूर्ण;

अटल पूर्णांक __init pscsi_module_init(व्योम)
अणु
	वापस transport_backend_रेजिस्टर(&pscsi_ops);
पूर्ण

अटल व्योम __निकास pscsi_module_निकास(व्योम)
अणु
	target_backend_unरेजिस्टर(&pscsi_ops);
पूर्ण

MODULE_DESCRIPTION("TCM PSCSI subsystem plugin");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(pscsi_module_init);
module_निकास(pscsi_module_निकास);
