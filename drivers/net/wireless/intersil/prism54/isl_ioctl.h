<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *            (C) 2003 Aurelien Alleaume <slts@मुक्त.fr>
 *            (C) 2003 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>
 */

#अगर_अघोषित _ISL_IOCTL_H
#घोषणा _ISL_IOCTL_H

#समावेश "islpci_mgt.h"
#समावेश "islpci_dev.h"

#समावेश <net/iw_handler.h>	/* New driver API */

#घोषणा SUPPORTED_WIRELESS_EXT                  19

व्योम prism54_mib_init(islpci_निजी *);

काष्ठा iw_statistics *prism54_get_wireless_stats(काष्ठा net_device *);
व्योम prism54_update_stats(काष्ठा work_काष्ठा *);

व्योम prism54_acl_init(काष्ठा islpci_acl *);
व्योम prism54_acl_clean(काष्ठा islpci_acl *);

व्योम prism54_process_trap(काष्ठा work_काष्ठा *);

व्योम prism54_wpa_bss_ie_init(islpci_निजी *priv);
व्योम prism54_wpa_bss_ie_clean(islpci_निजी *priv);

पूर्णांक prism54_set_mac_address(काष्ठा net_device *, व्योम *);

बाह्य स्थिर काष्ठा iw_handler_def prism54_handler_def;

#पूर्ण_अगर				/* _ISL_IOCTL_H */
