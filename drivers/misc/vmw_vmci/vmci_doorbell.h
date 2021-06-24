<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित VMCI_DOORBELL_H
#घोषणा VMCI_DOORBELL_H

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/types.h>

#समावेश "vmci_driver.h"

/*
 * VMCINotअगरyResourceInfo: Used to create and destroy करोorbells, and
 * generate a notअगरication क्रम a करोorbell or queue pair.
 */
काष्ठा vmci_dbell_notअगरy_resource_info अणु
	काष्ठा vmci_handle handle;
	u16 resource;
	u16 action;
	s32 result;
पूर्ण;

/*
 * Structure used क्रम checkpoपूर्णांकing the करोorbell mappings. It is
 * written to the checkpoपूर्णांक as is, so changing this काष्ठाure will
 * अवरोध checkpoपूर्णांक compatibility.
 */
काष्ठा dbell_cpt_state अणु
	काष्ठा vmci_handle handle;
	u64 biपंचांगap_idx;
पूर्ण;

पूर्णांक vmci_dbell_host_context_notअगरy(u32 src_cid, काष्ठा vmci_handle handle);
पूर्णांक vmci_dbell_get_priv_flags(काष्ठा vmci_handle handle, u32 *priv_flags);

bool vmci_dbell_रेजिस्टर_notअगरication_biपंचांगap(u64 biपंचांगap_ppn);
व्योम vmci_dbell_scan_notअगरication_entries(u8 *biपंचांगap);

#पूर्ण_अगर /* VMCI_DOORBELL_H */
