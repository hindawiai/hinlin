<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver dump header file.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _AIC94XX_DUMP_H_
#घोषणा _AIC94XX_DUMP_H_

#अगर_घोषित ASD_DEBUG

व्योम asd_dump_seq_state(काष्ठा asd_ha_काष्ठा *asd_ha, u8 lseq_mask);
व्योम asd_dump_frame_rcvd(काष्ठा asd_phy *phy,
			 काष्ठा करोne_list_काष्ठा *dl);
#अन्यथा /* ASD_DEBUG */

अटल अंतरभूत व्योम asd_dump_seq_state(काष्ठा asd_ha_काष्ठा *asd_ha,
				      u8 lseq_mask) अणु पूर्ण
अटल अंतरभूत व्योम asd_dump_frame_rcvd(काष्ठा asd_phy *phy,
				       काष्ठा करोne_list_काष्ठा *dl) अणु पूर्ण
#पूर्ण_अगर /* ASD_DEBUG */

#पूर्ण_अगर /* _AIC94XX_DUMP_H_ */
