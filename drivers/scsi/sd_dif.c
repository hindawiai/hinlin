<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sd_dअगर.c - SCSI Data Integrity Field
 *
 * Copyright (C) 2007, 2008 Oracle Corporation
 * Written by: Martin K. Petersen <martin.petersen@oracle.com>
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/t10-pi.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsicam.h>

#समावेश "sd.h"

/*
 * Configure exchange of protection inक्रमmation between OS and HBA.
 */
व्योम sd_dअगर_config_host(काष्ठा scsi_disk *sdkp)
अणु
	काष्ठा scsi_device *sdp = sdkp->device;
	काष्ठा gendisk *disk = sdkp->disk;
	u8 type = sdkp->protection_type;
	काष्ठा blk_पूर्णांकegrity bi;
	पूर्णांक dअगर, dix;

	dअगर = scsi_host_dअगर_capable(sdp->host, type);
	dix = scsi_host_dix_capable(sdp->host, type);

	अगर (!dix && scsi_host_dix_capable(sdp->host, 0)) अणु
		dअगर = 0; dix = 1;
	पूर्ण

	अगर (!dix)
		वापस;

	स_रखो(&bi, 0, माप(bi));

	/* Enable DMA of protection inक्रमmation */
	अगर (scsi_host_get_guard(sdkp->device->host) & SHOST_DIX_GUARD_IP) अणु
		अगर (type == T10_PI_TYPE3_PROTECTION)
			bi.profile = &t10_pi_type3_ip;
		अन्यथा
			bi.profile = &t10_pi_type1_ip;

		bi.flags |= BLK_INTEGRITY_IP_CHECKSUM;
	पूर्ण अन्यथा
		अगर (type == T10_PI_TYPE3_PROTECTION)
			bi.profile = &t10_pi_type3_crc;
		अन्यथा
			bi.profile = &t10_pi_type1_crc;

	bi.tuple_size = माप(काष्ठा t10_pi_tuple);
	sd_prपूर्णांकk(KERN_NOTICE, sdkp,
		  "Enabling DIX %s protection\n", bi.profile->name);

	अगर (dअगर && type) अणु
		bi.flags |= BLK_INTEGRITY_DEVICE_CAPABLE;

		अगर (!sdkp->ATO)
			जाओ out;

		अगर (type == T10_PI_TYPE3_PROTECTION)
			bi.tag_size = माप(u16) + माप(u32);
		अन्यथा
			bi.tag_size = माप(u16);

		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "DIF application tag size %u\n",
			  bi.tag_size);
	पूर्ण

out:
	blk_पूर्णांकegrity_रेजिस्टर(disk, &bi);
पूर्ण

