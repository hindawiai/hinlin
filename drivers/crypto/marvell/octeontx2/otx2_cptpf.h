<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __OTX2_CPTPF_H
#घोषणा __OTX2_CPTPF_H

#समावेश "otx2_cpt_common.h"
#समावेश "otx2_cptpf_ucode.h"
#समावेश "otx2_cptlf.h"

काष्ठा otx2_cptpf_dev;
काष्ठा otx2_cptvf_info अणु
	काष्ठा otx2_cptpf_dev *cptpf;	/* PF poपूर्णांकer this VF beदीर्घs to */
	काष्ठा work_काष्ठा vfpf_mbox_work;
	काष्ठा pci_dev *vf_dev;
	पूर्णांक vf_id;
	पूर्णांक पूर्णांकr_idx;
पूर्ण;

काष्ठा cptpf_flr_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा otx2_cptpf_dev *pf;
पूर्ण;

काष्ठा otx2_cptpf_dev अणु
	व्योम __iomem *reg_base;		/* CPT PF रेजिस्टरs start address */
	व्योम __iomem *afpf_mbox_base;	/* PF-AF mbox start address */
	व्योम __iomem *vfpf_mbox_base;   /* VF-PF mbox start address */
	काष्ठा pci_dev *pdev;		/* PCI device handle */
	काष्ठा otx2_cptvf_info vf[OTX2_CPT_MAX_VFS_NUM];
	काष्ठा otx2_cpt_eng_grps eng_grps;/* Engine groups inक्रमmation */
	काष्ठा otx2_cptlfs_info lfs;      /* CPT LFs attached to this PF */
	/* HW capabilities क्रम each engine type */
	जोड़ otx2_cpt_eng_caps eng_caps[OTX2_CPT_MAX_ENG_TYPES];
	bool is_eng_caps_discovered;

	/* AF <=> PF mbox */
	काष्ठा otx2_mbox	afpf_mbox;
	काष्ठा work_काष्ठा	afpf_mbox_work;
	काष्ठा workqueue_काष्ठा *afpf_mbox_wq;

	/* VF <=> PF mbox */
	काष्ठा otx2_mbox	vfpf_mbox;
	काष्ठा workqueue_काष्ठा *vfpf_mbox_wq;

	काष्ठा workqueue_काष्ठा	*flr_wq;
	काष्ठा cptpf_flr_work   *flr_work;

	u8 pf_id;               /* RVU PF number */
	u8 max_vfs;		/* Maximum number of VFs supported by CPT */
	u8 enabled_vfs;		/* Number of enabled VFs */
	u8 kvf_limits;		/* Kernel crypto limits */
	bool has_cpt1;
पूर्ण;

irqवापस_t otx2_cptpf_afpf_mbox_पूर्णांकr(पूर्णांक irq, व्योम *arg);
व्योम otx2_cptpf_afpf_mbox_handler(काष्ठा work_काष्ठा *work);
irqवापस_t otx2_cptpf_vfpf_mbox_पूर्णांकr(पूर्णांक irq, व्योम *arg);
व्योम otx2_cptpf_vfpf_mbox_handler(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* __OTX2_CPTPF_H */
