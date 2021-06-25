<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_PSCSI_H
#घोषणा TARGET_CORE_PSCSI_H

#घोषणा PSCSI_VERSION		"v4.0"

/* used in pscsi_find_alloc_len() */
#अगर_अघोषित INQUIRY_DATA_SIZE
#घोषणा INQUIRY_DATA_SIZE	0x24
#पूर्ण_अगर

/* used in pscsi_add_device_to_list() */
#घोषणा PSCSI_DEFAULT_QUEUEDEPTH	1

#घोषणा PS_RETRY		5
#घोषणा PS_TIMEOUT_DISK		(15*HZ)
#घोषणा PS_TIMEOUT_OTHER	(500*HZ)

#समावेश <linux/cache.h>             /* ___cacheline_aligned */
#समावेश <target/target_core_base.h> /* काष्ठा se_device */

काष्ठा block_device;
काष्ठा scsi_device;
काष्ठा Scsi_Host;

काष्ठा pscsi_plugin_task अणु
	अचिन्हित अक्षर pscsi_cdb[0];
पूर्ण ____cacheline_aligned;

#घोषणा PDF_HAS_CHANNEL_ID	0x01
#घोषणा PDF_HAS_TARGET_ID	0x02
#घोषणा PDF_HAS_LUN_ID		0x04
#घोषणा PDF_HAS_VPD_UNIT_SERIAL 0x08
#घोषणा PDF_HAS_VPD_DEV_IDENT	0x10
#घोषणा PDF_HAS_VIRT_HOST_ID	0x20

काष्ठा pscsi_dev_virt अणु
	काष्ठा se_device dev;
	पूर्णांक	pdv_flags;
	पूर्णांक	pdv_host_id;
	पूर्णांक	pdv_channel_id;
	पूर्णांक	pdv_target_id;
	पूर्णांक	pdv_lun_id;
	काष्ठा block_device *pdv_bd;
	काष्ठा scsi_device *pdv_sd;
	काष्ठा Scsi_Host *pdv_lld_host;
पूर्ण ____cacheline_aligned;

प्रकार क्रमागत phv_modes अणु
	PHV_VIRTUAL_HOST_ID,
	PHV_LLD_SCSI_HOST_NO
पूर्ण phv_modes_t;

काष्ठा pscsi_hba_virt अणु
	पूर्णांक			phv_host_id;
	phv_modes_t		phv_mode;
	काष्ठा Scsi_Host	*phv_lld_host;
पूर्ण ____cacheline_aligned;

#पूर्ण_अगर   /*** TARGET_CORE_PSCSI_H ***/
