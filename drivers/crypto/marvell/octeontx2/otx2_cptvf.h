<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __OTX2_CPTVF_H
#घोषणा __OTX2_CPTVF_H

#समावेश "mbox.h"
#समावेश "otx2_cptlf.h"

काष्ठा otx2_cptvf_dev अणु
	व्योम __iomem *reg_base;		/* Register start address */
	व्योम __iomem *pfvf_mbox_base;	/* PF-VF mbox start address */
	काष्ठा pci_dev *pdev;		/* PCI device handle */
	काष्ठा otx2_cptlfs_info lfs;	/* CPT LFs attached to this VF */
	u8 vf_id;			/* Virtual function index */

	/* PF <=> VF mbox */
	काष्ठा otx2_mbox	pfvf_mbox;
	काष्ठा work_काष्ठा	pfvf_mbox_work;
	काष्ठा workqueue_काष्ठा *pfvf_mbox_wq;
पूर्ण;

irqवापस_t otx2_cptvf_pfvf_mbox_पूर्णांकr(पूर्णांक irq, व्योम *arg);
व्योम otx2_cptvf_pfvf_mbox_handler(काष्ठा work_काष्ठा *work);
पूर्णांक otx2_cptvf_send_eng_grp_num_msg(काष्ठा otx2_cptvf_dev *cptvf, पूर्णांक eng_type);
पूर्णांक otx2_cptvf_send_kvf_limits_msg(काष्ठा otx2_cptvf_dev *cptvf);

#पूर्ण_अगर /* __OTX2_CPTVF_H */
