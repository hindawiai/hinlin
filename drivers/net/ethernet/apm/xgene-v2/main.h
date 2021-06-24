<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_V2_MAIN_H__
#घोषणा __XGENE_ENET_V2_MAIN_H__

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/efi.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/phy.h>
#समावेश <net/ip.h>
#समावेश "mac.h"
#समावेश "enet.h"
#समावेश "ring.h"
#समावेश "ethtool.h"

#घोषणा XGENE_ENET_STD_MTU	1536
#घोषणा XGENE_ENET_MIN_FRAME	60
#घोषणा IRQ_ID_SIZE             16

काष्ठा xge_resource अणु
	व्योम __iomem *base_addr;
	पूर्णांक phy_mode;
	u32 irq;
पूर्ण;

काष्ठा xge_stats अणु
	u64 tx_packets;
	u64 tx_bytes;
	u64 rx_packets;
	u64 rx_bytes;
	u64 rx_errors;
पूर्ण;

/* ethernet निजी data */
काष्ठा xge_pdata अणु
	काष्ठा xge_resource resources;
	काष्ठा xge_desc_ring *tx_ring;
	काष्ठा xge_desc_ring *rx_ring;
	काष्ठा platक्रमm_device *pdev;
	अक्षर irq_name[IRQ_ID_SIZE];
	काष्ठा mii_bus *mdio_bus;
	काष्ठा net_device *ndev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा xge_stats stats;
	पूर्णांक phy_speed;
	u8 nbufs;
पूर्ण;

पूर्णांक xge_mdio_config(काष्ठा net_device *ndev);
व्योम xge_mdio_हटाओ(काष्ठा net_device *ndev);

#पूर्ण_अगर /* __XGENE_ENET_V2_MAIN_H__ */
