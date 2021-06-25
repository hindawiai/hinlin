<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>

#समावेश <scsi/scsi_host.h>
#समावेश <uapi/scsi/cxlflash_ioctl.h>

#समावेश "sislite.h"
#समावेश "common.h"
#समावेश "vlun.h"
#समावेश "superpipe.h"

/**
 * create_local() - allocate and initialize a local LUN inक्रमmation काष्ठाure
 * @sdev:	SCSI device associated with LUN.
 * @wwid:	World Wide Node Name क्रम LUN.
 *
 * Return: Allocated local llun_info काष्ठाure on success, शून्य on failure
 */
अटल काष्ठा llun_info *create_local(काष्ठा scsi_device *sdev, u8 *wwid)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = शून्य;

	lli = kzalloc(माप(*lli), GFP_KERNEL);
	अगर (unlikely(!lli)) अणु
		dev_err(dev, "%s: could not allocate lli\n", __func__);
		जाओ out;
	पूर्ण

	lli->sdev = sdev;
	lli->host_no = sdev->host->host_no;
	lli->in_table = false;

	स_नकल(lli->wwid, wwid, DK_CXLFLASH_MANAGE_LUN_WWID_LEN);
out:
	वापस lli;
पूर्ण

/**
 * create_global() - allocate and initialize a global LUN inक्रमmation काष्ठाure
 * @sdev:	SCSI device associated with LUN.
 * @wwid:	World Wide Node Name क्रम LUN.
 *
 * Return: Allocated global glun_info काष्ठाure on success, शून्य on failure
 */
अटल काष्ठा glun_info *create_global(काष्ठा scsi_device *sdev, u8 *wwid)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा glun_info *gli = शून्य;

	gli = kzalloc(माप(*gli), GFP_KERNEL);
	अगर (unlikely(!gli)) अणु
		dev_err(dev, "%s: could not allocate gli\n", __func__);
		जाओ out;
	पूर्ण

	mutex_init(&gli->mutex);
	स_नकल(gli->wwid, wwid, DK_CXLFLASH_MANAGE_LUN_WWID_LEN);
out:
	वापस gli;
पूर्ण

/**
 * lookup_local() - find a local LUN inक्रमmation काष्ठाure by WWID
 * @cfg:	Internal काष्ठाure associated with the host.
 * @wwid:	WWID associated with LUN.
 *
 * Return: Found local lun_info काष्ठाure on success, शून्य on failure
 */
अटल काष्ठा llun_info *lookup_local(काष्ठा cxlflash_cfg *cfg, u8 *wwid)
अणु
	काष्ठा llun_info *lli, *temp;

	list_क्रम_each_entry_safe(lli, temp, &cfg->lluns, list)
		अगर (!स_भेद(lli->wwid, wwid, DK_CXLFLASH_MANAGE_LUN_WWID_LEN))
			वापस lli;

	वापस शून्य;
पूर्ण

/**
 * lookup_global() - find a global LUN inक्रमmation काष्ठाure by WWID
 * @wwid:	WWID associated with LUN.
 *
 * Return: Found global lun_info काष्ठाure on success, शून्य on failure
 */
अटल काष्ठा glun_info *lookup_global(u8 *wwid)
अणु
	काष्ठा glun_info *gli, *temp;

	list_क्रम_each_entry_safe(gli, temp, &global.gluns, list)
		अगर (!स_भेद(gli->wwid, wwid, DK_CXLFLASH_MANAGE_LUN_WWID_LEN))
			वापस gli;

	वापस शून्य;
पूर्ण

/**
 * find_and_create_lun() - find or create a local LUN inक्रमmation काष्ठाure
 * @sdev:	SCSI device associated with LUN.
 * @wwid:	WWID associated with LUN.
 *
 * The LUN is kept both in a local list (per adapter) and in a global list
 * (across all adapters). Certain attributes of the LUN are local to the
 * adapter (such as index, port selection mask, etc.).
 *
 * The block allocation map is shared across all adapters (i.e. associated
 * wih the global list). Since dअगरferent attributes are associated with
 * the per adapter and global entries, allocate two separate काष्ठाures क्रम each
 * LUN (one local, one global).
 *
 * Keep a poपूर्णांकer back from the local to the global entry.
 *
 * This routine assumes the caller holds the global mutex.
 *
 * Return: Found/Allocated local lun_info काष्ठाure on success, शून्य on failure
 */
अटल काष्ठा llun_info *find_and_create_lun(काष्ठा scsi_device *sdev, u8 *wwid)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = शून्य;
	काष्ठा glun_info *gli = शून्य;

	अगर (unlikely(!wwid))
		जाओ out;

	lli = lookup_local(cfg, wwid);
	अगर (lli)
		जाओ out;

	lli = create_local(sdev, wwid);
	अगर (unlikely(!lli))
		जाओ out;

	gli = lookup_global(wwid);
	अगर (gli) अणु
		lli->parent = gli;
		list_add(&lli->list, &cfg->lluns);
		जाओ out;
	पूर्ण

	gli = create_global(sdev, wwid);
	अगर (unlikely(!gli)) अणु
		kमुक्त(lli);
		lli = शून्य;
		जाओ out;
	पूर्ण

	lli->parent = gli;
	list_add(&lli->list, &cfg->lluns);

	list_add(&gli->list, &global.gluns);

out:
	dev_dbg(dev, "%s: returning lli=%p, gli=%p\n", __func__, lli, gli);
	वापस lli;
पूर्ण

/**
 * cxlflash_term_local_luns() - Delete all entries from local LUN list, मुक्त.
 * @cfg:	Internal काष्ठाure associated with the host.
 */
व्योम cxlflash_term_local_luns(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा llun_info *lli, *temp;

	mutex_lock(&global.mutex);
	list_क्रम_each_entry_safe(lli, temp, &cfg->lluns, list) अणु
		list_del(&lli->list);
		kमुक्त(lli);
	पूर्ण
	mutex_unlock(&global.mutex);
पूर्ण

/**
 * cxlflash_list_init() - initializes the global LUN list
 */
व्योम cxlflash_list_init(व्योम)
अणु
	INIT_LIST_HEAD(&global.gluns);
	mutex_init(&global.mutex);
	global.err_page = शून्य;
पूर्ण

/**
 * cxlflash_term_global_luns() - मुक्तs resources associated with global LUN list
 */
व्योम cxlflash_term_global_luns(व्योम)
अणु
	काष्ठा glun_info *gli, *temp;

	mutex_lock(&global.mutex);
	list_क्रम_each_entry_safe(gli, temp, &global.gluns, list) अणु
		list_del(&gli->list);
		cxlflash_ba_terminate(&gli->blka.ba_lun);
		kमुक्त(gli);
	पूर्ण
	mutex_unlock(&global.mutex);
पूर्ण

/**
 * cxlflash_manage_lun() - handles LUN management activities
 * @sdev:	SCSI device associated with LUN.
 * @manage:	Manage ioctl data काष्ठाure.
 *
 * This routine is used to notअगरy the driver about a LUN's WWID and associate
 * SCSI devices (sdev) with a global LUN instance. Additionally it serves to
 * change a LUN's operating mode: legacy or superpipe.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_manage_lun(काष्ठा scsi_device *sdev,
			काष्ठा dk_cxlflash_manage_lun *manage)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = शून्य;
	पूर्णांक rc = 0;
	u64 flags = manage->hdr.flags;
	u32 chan = sdev->channel;

	mutex_lock(&global.mutex);
	lli = find_and_create_lun(sdev, manage->wwid);
	dev_dbg(dev, "%s: WWID=%016llx%016llx, flags=%016llx lli=%p\n",
		__func__, get_unaligned_be64(&manage->wwid[0]),
		get_unaligned_be64(&manage->wwid[8]), manage->hdr.flags, lli);
	अगर (unlikely(!lli)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (flags & DK_CXLFLASH_MANAGE_LUN_ENABLE_SUPERPIPE) अणु
		/*
		 * Update port selection mask based upon channel, store off LUN
		 * in unpacked, AFU-मित्रly क्रमmat, and hang LUN reference in
		 * the sdev.
		 */
		lli->port_sel |= CHAN2PORTMASK(chan);
		lli->lun_id[chan] = lun_to_lunid(sdev->lun);
		sdev->hostdata = lli;
	पूर्ण अन्यथा अगर (flags & DK_CXLFLASH_MANAGE_LUN_DISABLE_SUPERPIPE) अणु
		अगर (lli->parent->mode != MODE_NONE)
			rc = -EBUSY;
		अन्यथा अणु
			/*
			 * Clean up local LUN क्रम this port and reset table
			 * tracking when no more references exist.
			 */
			sdev->hostdata = शून्य;
			lli->port_sel &= ~CHAN2PORTMASK(chan);
			अगर (lli->port_sel == 0U)
				lli->in_table = false;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "%s: port_sel=%08x chan=%u lun_id=%016llx\n",
		__func__, lli->port_sel, chan, lli->lun_id[chan]);

out:
	mutex_unlock(&global.mutex);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण
