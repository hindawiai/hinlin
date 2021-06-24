<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश "main.h"

व्योम xge_wr_csr(काष्ठा xge_pdata *pdata, u32 offset, u32 val)
अणु
	व्योम __iomem *addr = pdata->resources.base_addr + offset;

	ioग_लिखो32(val, addr);
पूर्ण

u32 xge_rd_csr(काष्ठा xge_pdata *pdata, u32 offset)
अणु
	व्योम __iomem *addr = pdata->resources.base_addr + offset;

	वापस ioपढ़ो32(addr);
पूर्ण

पूर्णांक xge_port_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = &pdata->pdev->dev;
	u32 data, रुको = 10;

	xge_wr_csr(pdata, ENET_CLKEN, 0x3);
	xge_wr_csr(pdata, ENET_SRST, 0xf);
	xge_wr_csr(pdata, ENET_SRST, 0);
	xge_wr_csr(pdata, CFG_MEM_RAM_SHUTDOWN, 1);
	xge_wr_csr(pdata, CFG_MEM_RAM_SHUTDOWN, 0);

	करो अणु
		usleep_range(100, 110);
		data = xge_rd_csr(pdata, BLOCK_MEM_RDY);
	पूर्ण जबतक (data != MEM_RDY && रुको--);

	अगर (data != MEM_RDY) अणु
		dev_err(dev, "ECC init failed: %x\n", data);
		वापस -ETIMEDOUT;
	पूर्ण

	xge_wr_csr(pdata, ENET_SHIM, DEVM_ARAUX_COH | DEVM_AWAUX_COH);

	वापस 0;
पूर्ण

अटल व्योम xge_traffic_resume(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);

	xge_wr_csr(pdata, CFG_FORCE_LINK_STATUS_EN, 1);
	xge_wr_csr(pdata, FORCE_LINK_STATUS, 1);

	xge_wr_csr(pdata, CFG_LINK_AGGR_RESUME, 1);
	xge_wr_csr(pdata, RX_DV_GATE_REG, 1);
पूर्ण

व्योम xge_port_init(काष्ठा net_device *ndev)
अणु
	काष्ठा xge_pdata *pdata = netdev_priv(ndev);

	pdata->phy_speed = SPEED_1000;
	xge_mac_init(pdata);
	xge_traffic_resume(ndev);
पूर्ण
