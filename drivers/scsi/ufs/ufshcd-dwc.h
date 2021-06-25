<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * UFS Host driver क्रम Synopsys Designware Core
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#अगर_अघोषित _UFSHCD_DWC_H
#घोषणा _UFSHCD_DWC_H

काष्ठा ufshcd_dme_attr_val अणु
	u32 attr_sel;
	u32 mib_val;
	u8 peer;
पूर्ण;

पूर्णांक ufshcd_dwc_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					क्रमागत ufs_notअगरy_change_status status);
पूर्णांक ufshcd_dwc_dme_set_attrs(काष्ठा ufs_hba *hba,
				स्थिर काष्ठा ufshcd_dme_attr_val *v, पूर्णांक n);
#पूर्ण_अगर /* End of Header */
