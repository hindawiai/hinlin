<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 */
#अगर_अघोषित __IWL_PHYDB_H__
#घोषणा __IWL_PHYDB_H__

#समावेश <linux/types.h>

#समावेश "iwl-op-mode.h"
#समावेश "iwl-trans.h"

काष्ठा iwl_phy_db *iwl_phy_db_init(काष्ठा iwl_trans *trans);

व्योम iwl_phy_db_मुक्त(काष्ठा iwl_phy_db *phy_db);

पूर्णांक iwl_phy_db_set_section(काष्ठा iwl_phy_db *phy_db,
			   काष्ठा iwl_rx_packet *pkt);


पूर्णांक iwl_send_phy_db_data(काष्ठा iwl_phy_db *phy_db);

#पूर्ण_अगर /* __IWL_PHYDB_H__ */
