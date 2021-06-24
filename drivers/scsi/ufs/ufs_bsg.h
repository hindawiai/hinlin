<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Western Digital Corporation
 */
#अगर_अघोषित UFS_BSG_H
#घोषणा UFS_BSG_H

#समावेश <linux/bsg-lib.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>

#समावेश "ufshcd.h"
#समावेश "ufs.h"

#अगर_घोषित CONFIG_SCSI_UFS_BSG
व्योम ufs_bsg_हटाओ(काष्ठा ufs_hba *hba);
पूर्णांक ufs_bsg_probe(काष्ठा ufs_hba *hba);
#अन्यथा
अटल अंतरभूत व्योम ufs_bsg_हटाओ(काष्ठा ufs_hba *hba) अणुपूर्ण
अटल अंतरभूत पूर्णांक ufs_bsg_probe(काष्ठा ufs_hba *hba) अणुवापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* UFS_BSG_H */
