<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __OTX_CPTPF_H
#घोषणा __OTX_CPTPF_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश "otx_cptpf_ucode.h"

/*
 * OcteonTX CPT device काष्ठाure
 */
काष्ठा otx_cpt_device अणु
	व्योम __iomem *reg_base; /* Register start address */
	काष्ठा pci_dev *pdev;	/* Pci device handle */
	काष्ठा otx_cpt_eng_grps eng_grps;/* Engine groups inक्रमmation */
	काष्ठा list_head list;
	u8 pf_type;	/* PF type SE or AE */
	u8 max_vfs;	/* Maximum number of VFs supported by the CPT */
	u8 vfs_enabled;	/* Number of enabled VFs */
पूर्ण;

व्योम otx_cpt_mbox_पूर्णांकr_handler(काष्ठा otx_cpt_device *cpt, पूर्णांक mbx);
व्योम otx_cpt_disable_all_cores(काष्ठा otx_cpt_device *cpt);

#पूर्ण_अगर /* __OTX_CPTPF_H */
