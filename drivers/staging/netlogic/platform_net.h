<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause) */
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 */

#घोषणा PORTS_PER_CONTROLLER		4

काष्ठा xlr_net_data अणु
	पूर्णांक cpu_mask;
	u32 __iomem *mii_addr;
	u32 __iomem *serdes_addr;
	u32 __iomem *pcs_addr;
	u32 __iomem *gpio_addr;
	पूर्णांक phy_पूर्णांकerface;
	पूर्णांक rfr_station;
	पूर्णांक tx_stnid[PORTS_PER_CONTROLLER];
	पूर्णांक *bucket_size;
	पूर्णांक phy_addr[PORTS_PER_CONTROLLER];
	काष्ठा xlr_fmn_info *gmac_fmn_info;
पूर्ण;
