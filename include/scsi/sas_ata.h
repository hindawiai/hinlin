<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Support क्रम SATA devices on Serial Attached SCSI (SAS) controllers
 *
 * Copyright (C) 2006 IBM Corporation
 *
 * Written by: Darrick J. Wong <djwong@us.ibm.com>, IBM Corporation
 */

#अगर_अघोषित _SAS_ATA_H_
#घोषणा _SAS_ATA_H_

#समावेश <linux/libata.h>
#समावेश <scsi/libsas.h>

#अगर_घोषित CONFIG_SCSI_SAS_ATA

अटल अंतरभूत पूर्णांक dev_is_sata(काष्ठा करोमुख्य_device *dev)
अणु
	वापस dev->dev_type == SAS_SATA_DEV || dev->dev_type == SAS_SATA_PM ||
	       dev->dev_type == SAS_SATA_PM_PORT || dev->dev_type == SAS_SATA_PENDING;
पूर्ण

पूर्णांक sas_get_ata_info(काष्ठा करोमुख्य_device *dev, काष्ठा ex_phy *phy);
पूर्णांक sas_ata_init(काष्ठा करोमुख्य_device *dev);
व्योम sas_ata_task_पात(काष्ठा sas_task *task);
व्योम sas_ata_strategy_handler(काष्ठा Scsi_Host *shost);
व्योम sas_ata_eh(काष्ठा Scsi_Host *shost, काष्ठा list_head *work_q,
		काष्ठा list_head *करोne_q);
व्योम sas_ata_schedule_reset(काष्ठा करोमुख्य_device *dev);
व्योम sas_ata_रुको_eh(काष्ठा करोमुख्य_device *dev);
व्योम sas_probe_sata(काष्ठा asd_sas_port *port);
व्योम sas_suspend_sata(काष्ठा asd_sas_port *port);
व्योम sas_resume_sata(काष्ठा asd_sas_port *port);
व्योम sas_ata_end_eh(काष्ठा ata_port *ap);
#अन्यथा


अटल अंतरभूत पूर्णांक dev_is_sata(काष्ठा करोमुख्य_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक sas_ata_init(काष्ठा करोमुख्य_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम sas_ata_task_पात(काष्ठा sas_task *task)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_ata_strategy_handler(काष्ठा Scsi_Host *shost)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_ata_eh(काष्ठा Scsi_Host *shost, काष्ठा list_head *work_q,
			      काष्ठा list_head *करोne_q)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_ata_schedule_reset(काष्ठा करोमुख्य_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_ata_रुको_eh(काष्ठा करोमुख्य_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_probe_sata(काष्ठा asd_sas_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_suspend_sata(काष्ठा asd_sas_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम sas_resume_sata(काष्ठा asd_sas_port *port)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक sas_get_ata_info(काष्ठा करोमुख्य_device *dev, काष्ठा ex_phy *phy)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sas_ata_end_eh(काष्ठा ata_port *ap)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _SAS_ATA_H_ */
