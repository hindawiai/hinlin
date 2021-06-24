<शैली गुरु>
/* bnx2i_sysfs.c: QLogic NetXtreme II iSCSI driver.
 *
 * Copyright (c) 2004 - 2013 Broadcom Corporation
 * Copyright (c) 2014, QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Anil Veerabhadrappa (anilgv@broadcom.com)
 * Previously Maपूर्णांकained by: Eddie Wai (eddie.wai@broadcom.com)
 * Maपूर्णांकained by: QLogic-Storage-Upstream@qlogic.com
 */

#समावेश "bnx2i.h"

/**
 * bnx2i_dev_to_hba - maps dev poपूर्णांकer to adapter काष्ठा
 * @dev:	device poपूर्णांकer
 *
 * Map device to hba काष्ठाure
 */
अटल अंतरभूत काष्ठा bnx2i_hba *bnx2i_dev_to_hba(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	वापस iscsi_host_priv(shost);
पूर्ण


/**
 * bnx2i_show_sq_info - वापस(s currently configured send queue (SQ) size
 * @dev:	device poपूर्णांकer
 * @attr:	device attribute (unused)
 * @buf:	buffer to वापस current SQ size parameter
 *
 * Returns current SQ size parameter, this paramater determines the number
 * outstanding iSCSI commands supported on a connection
 */
अटल sमाप_प्रकार bnx2i_show_sq_info(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	वापस प्र_लिखो(buf, "0x%x\n", hba->max_sqes);
पूर्ण


/**
 * bnx2i_set_sq_info - update send queue (SQ) size parameter
 * @dev:	device poपूर्णांकer
 * @attr:	device attribute (unused)
 * @buf:	buffer to वापस current SQ size parameter
 * @count:	parameter buffer size
 *
 * Interface क्रम user to change shared queue size allocated क्रम each conn
 * Must be within SQ limits and a घातer of 2. For the latter this is needed
 * because of how libiscsi pपुनः_स्मृतिates tasks.
 */
अटल sमाप_प्रकार bnx2i_set_sq_info(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bnx2i_hba *hba = bnx2i_dev_to_hba(dev);
	u32 val;
	पूर्णांक max_sq_size;

	अगर (hba->ofld_conns_active)
		जाओ skip_config;

	अगर (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		max_sq_size = BNX2I_5770X_SQ_WQES_MAX;
	अन्यथा
		max_sq_size = BNX2I_570X_SQ_WQES_MAX;

	अगर (माला_पूछो(buf, " 0x%x ", &val) > 0) अणु
		अगर ((val >= BNX2I_SQ_WQES_MIN) && (val <= max_sq_size) &&
		    (is_घातer_of_2(val)))
			hba->max_sqes = val;
	पूर्ण

	वापस count;

skip_config:
	prपूर्णांकk(KERN_ERR "bnx2i: device busy, cannot change SQ size\n");
	वापस 0;
पूर्ण


/**
 * bnx2i_show_ccell_info - वापसs command cell (HQ) size
 * @dev:	device poपूर्णांकer
 * @attr:	device attribute (unused)
 * @buf:	buffer to वापस current SQ size parameter
 *
 * वापसs per-connection TCP history queue size parameter
 */
अटल sमाप_प्रकार bnx2i_show_ccell_info(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	वापस प्र_लिखो(buf, "0x%x\n", hba->num_ccell);
पूर्ण


/**
 * bnx2i_set_ccell_info - set command cell (HQ) size
 * @dev:	device poपूर्णांकer
 * @attr:	device attribute (unused)
 * @buf:	buffer to वापस current SQ size parameter
 * @count:	parameter buffer size
 *
 * updates per-connection TCP history queue size parameter
 */
अटल sमाप_प्रकार bnx2i_set_ccell_info(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 val;
	काष्ठा bnx2i_hba *hba = bnx2i_dev_to_hba(dev);

	अगर (hba->ofld_conns_active)
		जाओ skip_config;

	अगर (माला_पूछो(buf, " 0x%x ", &val) > 0) अणु
		अगर ((val >= BNX2I_CCELLS_MIN) &&
		    (val <= BNX2I_CCELLS_MAX)) अणु
			hba->num_ccell = val;
		पूर्ण
	पूर्ण

	वापस count;

skip_config:
	prपूर्णांकk(KERN_ERR "bnx2i: device busy, cannot change CCELL size\n");
	वापस 0;
पूर्ण


अटल DEVICE_ATTR(sq_size, S_IRUGO | S_IWUSR,
		   bnx2i_show_sq_info, bnx2i_set_sq_info);
अटल DEVICE_ATTR(num_ccell, S_IRUGO | S_IWUSR,
		   bnx2i_show_ccell_info, bnx2i_set_ccell_info);

काष्ठा device_attribute *bnx2i_dev_attributes[] = अणु
	&dev_attr_sq_size,
	&dev_attr_num_ccell,
	शून्य
पूर्ण;
