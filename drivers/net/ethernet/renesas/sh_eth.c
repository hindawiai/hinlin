<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  SuperH Ethernet device driver
 *
 *  Copyright (C) 2014 Renesas Electronics Corporation
 *  Copyright (C) 2006-2012 Nobuhiro Iwamatsu
 *  Copyright (C) 2008-2014 Renesas Solutions Corp.
 *  Copyright (C) 2013-2017 Cogent Embedded, Inc.
 *  Copyright (C) 2014 Codethink Limited
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/cache.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/sh_eth.h>
#समावेश <linux/of_mdपन.स>

#समावेश "sh_eth.h"

#घोषणा SH_ETH_DEF_MSG_ENABLE \
		(NETIF_MSG_LINK	| \
		NETIF_MSG_TIMER	| \
		NETIF_MSG_RX_ERR| \
		NETIF_MSG_TX_ERR)

#घोषणा SH_ETH_OFFSET_INVALID	((u16)~0)

#घोषणा SH_ETH_OFFSET_DEFAULTS			\
	[0 ... SH_ETH_MAX_REGISTER_OFFSET - 1] = SH_ETH_OFFSET_INVALID

/* use some पूर्णांकentionally tricky logic here to initialize the whole काष्ठा to
 * 0xffff, but then override certain fields, requiring us to indicate that we
 * "know" that there are overrides in this काष्ठाure, and we'll need to disable
 * that warning from W=1 builds. GCC has supported this option since 4.2.X, but
 * the macros available to करो this only define GCC 8.
 */
__diag_push();
__diag_ignore(GCC, 8, "-Woverride-init",
	      "logic to initialize all and then override some is OK");
अटल स्थिर u16 sh_eth_offset_gigabit[SH_ETH_MAX_REGISTER_OFFSET] = अणु
	SH_ETH_OFFSET_DEFAULTS,

	[EDSR]		= 0x0000,
	[EDMR]		= 0x0400,
	[EDTRR]		= 0x0408,
	[EDRRR]		= 0x0410,
	[EESR]		= 0x0428,
	[EESIPR]	= 0x0430,
	[TDLAR]		= 0x0010,
	[TDFAR]		= 0x0014,
	[TDFXR]		= 0x0018,
	[TDFFR]		= 0x001c,
	[RDLAR]		= 0x0030,
	[RDFAR]		= 0x0034,
	[RDFXR]		= 0x0038,
	[RDFFR]		= 0x003c,
	[TRSCER]	= 0x0438,
	[RMFCR]		= 0x0440,
	[TFTR]		= 0x0448,
	[FDR]		= 0x0450,
	[RMCR]		= 0x0458,
	[RPAसूची]	= 0x0460,
	[FCFTR]		= 0x0468,
	[CSMR]		= 0x04E4,

	[ECMR]		= 0x0500,
	[ECSR]		= 0x0510,
	[ECSIPR]	= 0x0518,
	[PIR]		= 0x0520,
	[PSR]		= 0x0528,
	[PIPR]		= 0x052c,
	[RFLR]		= 0x0508,
	[APR]		= 0x0554,
	[MPR]		= 0x0558,
	[PFTCR]		= 0x055c,
	[PFRCR]		= 0x0560,
	[TPAUSER]	= 0x0564,
	[GECMR]		= 0x05b0,
	[BCULR]		= 0x05b4,
	[MAHR]		= 0x05c0,
	[MALR]		= 0x05c8,
	[TROCR]		= 0x0700,
	[CDCR]		= 0x0708,
	[LCCR]		= 0x0710,
	[CEFCR]		= 0x0740,
	[FRECR]		= 0x0748,
	[TSFRCR]	= 0x0750,
	[TLFRCR]	= 0x0758,
	[RFCR]		= 0x0760,
	[CERCR]		= 0x0768,
	[CEECR]		= 0x0770,
	[MAFCR]		= 0x0778,
	[RMII_MII]	= 0x0790,

	[ARSTR]		= 0x0000,
	[TSU_CTRST]	= 0x0004,
	[TSU_FWEN0]	= 0x0010,
	[TSU_FWEN1]	= 0x0014,
	[TSU_FCM]	= 0x0018,
	[TSU_BSYSL0]	= 0x0020,
	[TSU_BSYSL1]	= 0x0024,
	[TSU_PRISL0]	= 0x0028,
	[TSU_PRISL1]	= 0x002c,
	[TSU_FWSL0]	= 0x0030,
	[TSU_FWSL1]	= 0x0034,
	[TSU_FWSLC]	= 0x0038,
	[TSU_QTAGM0]	= 0x0040,
	[TSU_QTAGM1]	= 0x0044,
	[TSU_FWSR]	= 0x0050,
	[TSU_FWINMK]	= 0x0054,
	[TSU_ADQT0]	= 0x0048,
	[TSU_ADQT1]	= 0x004c,
	[TSU_VTAG0]	= 0x0058,
	[TSU_VTAG1]	= 0x005c,
	[TSU_ADSBSY]	= 0x0060,
	[TSU_TEN]	= 0x0064,
	[TSU_POST1]	= 0x0070,
	[TSU_POST2]	= 0x0074,
	[TSU_POST3]	= 0x0078,
	[TSU_POST4]	= 0x007c,
	[TSU_ADRH0]	= 0x0100,

	[TXNLCR0]	= 0x0080,
	[TXALCR0]	= 0x0084,
	[RXNLCR0]	= 0x0088,
	[RXALCR0]	= 0x008c,
	[FWNLCR0]	= 0x0090,
	[FWALCR0]	= 0x0094,
	[TXNLCR1]	= 0x00a0,
	[TXALCR1]	= 0x00a4,
	[RXNLCR1]	= 0x00a8,
	[RXALCR1]	= 0x00ac,
	[FWNLCR1]	= 0x00b0,
	[FWALCR1]	= 0x00b4,
पूर्ण;

अटल स्थिर u16 sh_eth_offset_fast_rcar[SH_ETH_MAX_REGISTER_OFFSET] = अणु
	SH_ETH_OFFSET_DEFAULTS,

	[ECMR]		= 0x0300,
	[RFLR]		= 0x0308,
	[ECSR]		= 0x0310,
	[ECSIPR]	= 0x0318,
	[PIR]		= 0x0320,
	[PSR]		= 0x0328,
	[RDMLR]		= 0x0340,
	[IPGR]		= 0x0350,
	[APR]		= 0x0354,
	[MPR]		= 0x0358,
	[RFCF]		= 0x0360,
	[TPAUSER]	= 0x0364,
	[TPAUSECR]	= 0x0368,
	[MAHR]		= 0x03c0,
	[MALR]		= 0x03c8,
	[TROCR]		= 0x03d0,
	[CDCR]		= 0x03d4,
	[LCCR]		= 0x03d8,
	[CNDCR]		= 0x03dc,
	[CEFCR]		= 0x03e4,
	[FRECR]		= 0x03e8,
	[TSFRCR]	= 0x03ec,
	[TLFRCR]	= 0x03f0,
	[RFCR]		= 0x03f4,
	[MAFCR]		= 0x03f8,

	[EDMR]		= 0x0200,
	[EDTRR]		= 0x0208,
	[EDRRR]		= 0x0210,
	[TDLAR]		= 0x0218,
	[RDLAR]		= 0x0220,
	[EESR]		= 0x0228,
	[EESIPR]	= 0x0230,
	[TRSCER]	= 0x0238,
	[RMFCR]		= 0x0240,
	[TFTR]		= 0x0248,
	[FDR]		= 0x0250,
	[RMCR]		= 0x0258,
	[TFUCR]		= 0x0264,
	[RFOCR]		= 0x0268,
	[RMIIMODE]      = 0x026c,
	[FCFTR]		= 0x0270,
	[TRIMD]		= 0x027c,
पूर्ण;

अटल स्थिर u16 sh_eth_offset_fast_sh4[SH_ETH_MAX_REGISTER_OFFSET] = अणु
	SH_ETH_OFFSET_DEFAULTS,

	[ECMR]		= 0x0100,
	[RFLR]		= 0x0108,
	[ECSR]		= 0x0110,
	[ECSIPR]	= 0x0118,
	[PIR]		= 0x0120,
	[PSR]		= 0x0128,
	[RDMLR]		= 0x0140,
	[IPGR]		= 0x0150,
	[APR]		= 0x0154,
	[MPR]		= 0x0158,
	[TPAUSER]	= 0x0164,
	[RFCF]		= 0x0160,
	[TPAUSECR]	= 0x0168,
	[BCFRR]		= 0x016c,
	[MAHR]		= 0x01c0,
	[MALR]		= 0x01c8,
	[TROCR]		= 0x01d0,
	[CDCR]		= 0x01d4,
	[LCCR]		= 0x01d8,
	[CNDCR]		= 0x01dc,
	[CEFCR]		= 0x01e4,
	[FRECR]		= 0x01e8,
	[TSFRCR]	= 0x01ec,
	[TLFRCR]	= 0x01f0,
	[RFCR]		= 0x01f4,
	[MAFCR]		= 0x01f8,
	[RTRATE]	= 0x01fc,

	[EDMR]		= 0x0000,
	[EDTRR]		= 0x0008,
	[EDRRR]		= 0x0010,
	[TDLAR]		= 0x0018,
	[RDLAR]		= 0x0020,
	[EESR]		= 0x0028,
	[EESIPR]	= 0x0030,
	[TRSCER]	= 0x0038,
	[RMFCR]		= 0x0040,
	[TFTR]		= 0x0048,
	[FDR]		= 0x0050,
	[RMCR]		= 0x0058,
	[TFUCR]		= 0x0064,
	[RFOCR]		= 0x0068,
	[FCFTR]		= 0x0070,
	[RPAसूची]	= 0x0078,
	[TRIMD]		= 0x007c,
	[RBWAR]		= 0x00c8,
	[RDFAR]		= 0x00cc,
	[TBRAR]		= 0x00d4,
	[TDFAR]		= 0x00d8,
पूर्ण;

अटल स्थिर u16 sh_eth_offset_fast_sh3_sh2[SH_ETH_MAX_REGISTER_OFFSET] = अणु
	SH_ETH_OFFSET_DEFAULTS,

	[EDMR]		= 0x0000,
	[EDTRR]		= 0x0004,
	[EDRRR]		= 0x0008,
	[TDLAR]		= 0x000c,
	[RDLAR]		= 0x0010,
	[EESR]		= 0x0014,
	[EESIPR]	= 0x0018,
	[TRSCER]	= 0x001c,
	[RMFCR]		= 0x0020,
	[TFTR]		= 0x0024,
	[FDR]		= 0x0028,
	[RMCR]		= 0x002c,
	[EDOCR]		= 0x0030,
	[FCFTR]		= 0x0034,
	[RPAसूची]	= 0x0038,
	[TRIMD]		= 0x003c,
	[RBWAR]		= 0x0040,
	[RDFAR]		= 0x0044,
	[TBRAR]		= 0x004c,
	[TDFAR]		= 0x0050,

	[ECMR]		= 0x0160,
	[ECSR]		= 0x0164,
	[ECSIPR]	= 0x0168,
	[PIR]		= 0x016c,
	[MAHR]		= 0x0170,
	[MALR]		= 0x0174,
	[RFLR]		= 0x0178,
	[PSR]		= 0x017c,
	[TROCR]		= 0x0180,
	[CDCR]		= 0x0184,
	[LCCR]		= 0x0188,
	[CNDCR]		= 0x018c,
	[CEFCR]		= 0x0194,
	[FRECR]		= 0x0198,
	[TSFRCR]	= 0x019c,
	[TLFRCR]	= 0x01a0,
	[RFCR]		= 0x01a4,
	[MAFCR]		= 0x01a8,
	[IPGR]		= 0x01b4,
	[APR]		= 0x01b8,
	[MPR]		= 0x01bc,
	[TPAUSER]	= 0x01c4,
	[BCFR]		= 0x01cc,

	[ARSTR]		= 0x0000,
	[TSU_CTRST]	= 0x0004,
	[TSU_FWEN0]	= 0x0010,
	[TSU_FWEN1]	= 0x0014,
	[TSU_FCM]	= 0x0018,
	[TSU_BSYSL0]	= 0x0020,
	[TSU_BSYSL1]	= 0x0024,
	[TSU_PRISL0]	= 0x0028,
	[TSU_PRISL1]	= 0x002c,
	[TSU_FWSL0]	= 0x0030,
	[TSU_FWSL1]	= 0x0034,
	[TSU_FWSLC]	= 0x0038,
	[TSU_QTAGM0]	= 0x0040,
	[TSU_QTAGM1]	= 0x0044,
	[TSU_ADQT0]	= 0x0048,
	[TSU_ADQT1]	= 0x004c,
	[TSU_FWSR]	= 0x0050,
	[TSU_FWINMK]	= 0x0054,
	[TSU_ADSBSY]	= 0x0060,
	[TSU_TEN]	= 0x0064,
	[TSU_POST1]	= 0x0070,
	[TSU_POST2]	= 0x0074,
	[TSU_POST3]	= 0x0078,
	[TSU_POST4]	= 0x007c,

	[TXNLCR0]	= 0x0080,
	[TXALCR0]	= 0x0084,
	[RXNLCR0]	= 0x0088,
	[RXALCR0]	= 0x008c,
	[FWNLCR0]	= 0x0090,
	[FWALCR0]	= 0x0094,
	[TXNLCR1]	= 0x00a0,
	[TXALCR1]	= 0x00a4,
	[RXNLCR1]	= 0x00a8,
	[RXALCR1]	= 0x00ac,
	[FWNLCR1]	= 0x00b0,
	[FWALCR1]	= 0x00b4,

	[TSU_ADRH0]	= 0x0100,
पूर्ण;
__diag_pop();

अटल व्योम sh_eth_rcv_snd_disable(काष्ठा net_device *ndev);
अटल काष्ठा net_device_stats *sh_eth_get_stats(काष्ठा net_device *ndev);

अटल व्योम sh_eth_ग_लिखो(काष्ठा net_device *ndev, u32 data, पूर्णांक क्रमागत_index)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u16 offset = mdp->reg_offset[क्रमागत_index];

	अगर (WARN_ON(offset == SH_ETH_OFFSET_INVALID))
		वापस;

	ioग_लिखो32(data, mdp->addr + offset);
पूर्ण

अटल u32 sh_eth_पढ़ो(काष्ठा net_device *ndev, पूर्णांक क्रमागत_index)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u16 offset = mdp->reg_offset[क्रमागत_index];

	अगर (WARN_ON(offset == SH_ETH_OFFSET_INVALID))
		वापस ~0U;

	वापस ioपढ़ो32(mdp->addr + offset);
पूर्ण

अटल व्योम sh_eth_modअगरy(काष्ठा net_device *ndev, पूर्णांक क्रमागत_index, u32 clear,
			  u32 set)
अणु
	sh_eth_ग_लिखो(ndev, (sh_eth_पढ़ो(ndev, क्रमागत_index) & ~clear) | set,
		     क्रमागत_index);
पूर्ण

अटल u16 sh_eth_tsu_get_offset(काष्ठा sh_eth_निजी *mdp, पूर्णांक क्रमागत_index)
अणु
	वापस mdp->reg_offset[क्रमागत_index];
पूर्ण

अटल व्योम sh_eth_tsu_ग_लिखो(काष्ठा sh_eth_निजी *mdp, u32 data,
			     पूर्णांक क्रमागत_index)
अणु
	u16 offset = sh_eth_tsu_get_offset(mdp, क्रमागत_index);

	अगर (WARN_ON(offset == SH_ETH_OFFSET_INVALID))
		वापस;

	ioग_लिखो32(data, mdp->tsu_addr + offset);
पूर्ण

अटल u32 sh_eth_tsu_पढ़ो(काष्ठा sh_eth_निजी *mdp, पूर्णांक क्रमागत_index)
अणु
	u16 offset = sh_eth_tsu_get_offset(mdp, क्रमागत_index);

	अगर (WARN_ON(offset == SH_ETH_OFFSET_INVALID))
		वापस ~0U;

	वापस ioपढ़ो32(mdp->tsu_addr + offset);
पूर्ण

अटल व्योम sh_eth_soft_swap(अक्षर *src, पूर्णांक len)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	u32 *p = (u32 *)src;
	u32 *maxp = p + DIV_ROUND_UP(len, माप(u32));

	क्रम (; p < maxp; p++)
		*p = swab32(*p);
#पूर्ण_अगर
पूर्ण

अटल व्योम sh_eth_select_mii(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u32 value;

	चयन (mdp->phy_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII ... PHY_INTERFACE_MODE_RGMII_TXID:
		value = 0x3;
		अवरोध;
	हाल PHY_INTERFACE_MODE_GMII:
		value = 0x2;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		value = 0x1;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		value = 0x0;
		अवरोध;
	शेष:
		netdev_warn(ndev,
			    "PHY interface mode was not setup. Set to MII.\n");
		value = 0x1;
		अवरोध;
	पूर्ण

	sh_eth_ग_लिखो(ndev, value, RMII_MII);
पूर्ण

अटल व्योम sh_eth_set_duplex(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	sh_eth_modअगरy(ndev, ECMR, ECMR_DM, mdp->duplex ? ECMR_DM : 0);
पूर्ण

अटल व्योम sh_eth_chip_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	/* reset device */
	sh_eth_tsu_ग_लिखो(mdp, ARSTR_ARST, ARSTR);
	mdelay(1);
पूर्ण

अटल पूर्णांक sh_eth_soft_reset(काष्ठा net_device *ndev)
अणु
	sh_eth_modअगरy(ndev, EDMR, EDMR_SRST_ETHER, EDMR_SRST_ETHER);
	mdelay(3);
	sh_eth_modअगरy(ndev, EDMR, EDMR_SRST_ETHER, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_check_soft_reset(काष्ठा net_device *ndev)
अणु
	पूर्णांक cnt;

	क्रम (cnt = 100; cnt > 0; cnt--) अणु
		अगर (!(sh_eth_पढ़ो(ndev, EDMR) & EDMR_SRST_GETHER))
			वापस 0;
		mdelay(1);
	पूर्ण

	netdev_err(ndev, "Device reset failed\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sh_eth_soft_reset_gether(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret;

	sh_eth_ग_लिखो(ndev, EDSR_ENALL, EDSR);
	sh_eth_modअगरy(ndev, EDMR, EDMR_SRST_GETHER, EDMR_SRST_GETHER);

	ret = sh_eth_check_soft_reset(ndev);
	अगर (ret)
		वापस ret;

	/* Table Init */
	sh_eth_ग_लिखो(ndev, 0, TDLAR);
	sh_eth_ग_लिखो(ndev, 0, TDFAR);
	sh_eth_ग_लिखो(ndev, 0, TDFXR);
	sh_eth_ग_लिखो(ndev, 0, TDFFR);
	sh_eth_ग_लिखो(ndev, 0, RDLAR);
	sh_eth_ग_लिखो(ndev, 0, RDFAR);
	sh_eth_ग_लिखो(ndev, 0, RDFXR);
	sh_eth_ग_लिखो(ndev, 0, RDFFR);

	/* Reset HW CRC रेजिस्टर */
	अगर (mdp->cd->csmr)
		sh_eth_ग_लिखो(ndev, 0, CSMR);

	/* Select MII mode */
	अगर (mdp->cd->select_mii)
		sh_eth_select_mii(ndev);

	वापस ret;
पूर्ण

अटल व्योम sh_eth_set_rate_gether(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	अगर (WARN_ON(!mdp->cd->gecmr))
		वापस;

	चयन (mdp->speed) अणु
	हाल 10: /* 10BASE */
		sh_eth_ग_लिखो(ndev, GECMR_10, GECMR);
		अवरोध;
	हाल 100:/* 100BASE */
		sh_eth_ग_लिखो(ndev, GECMR_100, GECMR);
		अवरोध;
	हाल 1000: /* 1000BASE */
		sh_eth_ग_लिखो(ndev, GECMR_1000, GECMR);
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF
/* R7S72100 */
अटल काष्ठा sh_eth_cpu_data r7s72100_data = अणु
	.soft_reset	= sh_eth_soft_reset_gether,

	.chip_reset	= sh_eth_chip_reset,
	.set_duplex	= sh_eth_set_duplex,

	.रेजिस्टर_type	= SH_ETH_REG_GIGABIT,

	.edtrr_trns	= EDTRR_TRNS_GETHER,
	.ecsr_value	= ECSR_ICD,
	.ecsipr_value	= ECSIPR_ICDIP,
	.eesipr_value	= EESIPR_TWB1IP | EESIPR_TWBIP | EESIPR_TC1IP |
			  EESIPR_TABTIP | EESIPR_RABTIP | EESIPR_RFCOFIP |
			  EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_RMAFIP | EESIPR_RRFIP |
			  EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_TC1 | EESR_FTC,
	.eesr_err_check	= EESR_TWB1 | EESR_TWB | EESR_TABT | EESR_RABT |
			  EESR_RFE | EESR_RDE | EESR_RFRMER | EESR_TFE |
			  EESR_TDE,
	.fdr_value	= 0x0000070f,

	.trscer_err_mask = TRSCER_RMAFCE | TRSCER_RRFCE,

	.no_psr		= 1,
	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
	.rpadir		= 1,
	.no_trimd	= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
	.csmr		= 1,
	.rx_csum	= 1,
	.tsu		= 1,
	.no_tx_cntrs	= 1,
पूर्ण;

अटल व्योम sh_eth_chip_reset_r8a7740(काष्ठा net_device *ndev)
अणु
	sh_eth_chip_reset(ndev);

	sh_eth_select_mii(ndev);
पूर्ण

/* R8A7740 */
अटल काष्ठा sh_eth_cpu_data r8a7740_data = अणु
	.soft_reset	= sh_eth_soft_reset_gether,

	.chip_reset	= sh_eth_chip_reset_r8a7740,
	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_gether,

	.रेजिस्टर_type	= SH_ETH_REG_GIGABIT,

	.edtrr_trns	= EDTRR_TRNS_GETHER,
	.ecsr_value	= ECSR_ICD | ECSR_MPD,
	.ecsipr_value	= ECSIPR_LCHNGIP | ECSIPR_ICDIP | ECSIPR_MPDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  0x0000f000 | EESIPR_CNDIP | EESIPR_DLCIP |
			  EESIPR_CDIP | EESIPR_TROIP | EESIPR_RMAFIP |
			  EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_TC1 | EESR_FTC,
	.eesr_err_check	= EESR_TWB1 | EESR_TWB | EESR_TABT | EESR_RABT |
			  EESR_RFE | EESR_RDE | EESR_RFRMER | EESR_TFE |
			  EESR_TDE,
	.fdr_value	= 0x0000070f,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.gecmr		= 1,
	.bculr		= 1,
	.hw_swap	= 1,
	.rpadir		= 1,
	.no_trimd	= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
	.csmr		= 1,
	.rx_csum	= 1,
	.tsu		= 1,
	.select_mii	= 1,
	.magic		= 1,
	.cexcr		= 1,
पूर्ण;

/* There is CPU dependent code */
अटल व्योम sh_eth_set_rate_rcar(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	चयन (mdp->speed) अणु
	हाल 10: /* 10BASE */
		sh_eth_modअगरy(ndev, ECMR, ECMR_ELB, 0);
		अवरोध;
	हाल 100:/* 100BASE */
		sh_eth_modअगरy(ndev, ECMR, ECMR_ELB, ECMR_ELB);
		अवरोध;
	पूर्ण
पूर्ण

/* R-Car Gen1 */
अटल काष्ठा sh_eth_cpu_data rcar_gen1_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_rcar,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_RCAR,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.ecsr_value	= ECSR_PSRTO | ECSR_LCHNG | ECSR_ICD,
	.ecsipr_value	= ECSIPR_PSRTOIP | ECSIPR_LCHNGIP | ECSIPR_ICDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ADEIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_RMAFIP | EESIPR_RRFIP |
			  EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_FTC | EESR_CND | EESR_DLC | EESR_CD | EESR_TRO,
	.eesr_err_check	= EESR_TWB | EESR_TABT | EESR_RABT | EESR_RFE |
			  EESR_RDE | EESR_RFRMER | EESR_TFE | EESR_TDE,
	.fdr_value	= 0x00000f0f,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
	.no_xdfar	= 1,
पूर्ण;

/* R-Car Gen2 and RZ/G1 */
अटल काष्ठा sh_eth_cpu_data rcar_gen2_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_rcar,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_RCAR,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.ecsr_value	= ECSR_PSRTO | ECSR_LCHNG | ECSR_ICD | ECSR_MPD,
	.ecsipr_value	= ECSIPR_PSRTOIP | ECSIPR_LCHNGIP | ECSIPR_ICDIP |
			  ECSIPR_MPDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ADEIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_RMAFIP | EESIPR_RRFIP |
			  EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_FTC | EESR_CND | EESR_DLC | EESR_CD | EESR_TRO,
	.eesr_err_check	= EESR_TWB | EESR_TABT | EESR_RABT | EESR_RFE |
			  EESR_RDE | EESR_RFRMER | EESR_TFE | EESR_TDE,
	.fdr_value	= 0x00000f0f,

	.trscer_err_mask = TRSCER_RMAFCE,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
	.no_xdfar	= 1,
	.rmiimode	= 1,
	.magic		= 1,
पूर्ण;

/* R8A77980 */
अटल काष्ठा sh_eth_cpu_data r8a77980_data = अणु
	.soft_reset	= sh_eth_soft_reset_gether,

	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_gether,

	.रेजिस्टर_type  = SH_ETH_REG_GIGABIT,

	.edtrr_trns	= EDTRR_TRNS_GETHER,
	.ecsr_value	= ECSR_PSRTO | ECSR_LCHNG | ECSR_ICD | ECSR_MPD,
	.ecsipr_value	= ECSIPR_PSRTOIP | ECSIPR_LCHNGIP | ECSIPR_ICDIP |
			  ECSIPR_MPDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_RMAFIP | EESIPR_RRFIP |
			  EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check       = EESR_FTC | EESR_CD | EESR_TRO,
	.eesr_err_check = EESR_TWB1 | EESR_TWB | EESR_TABT | EESR_RABT |
			  EESR_RFE | EESR_RDE | EESR_RFRMER |
			  EESR_TFE | EESR_TDE | EESR_ECI,
	.fdr_value	= 0x0000070f,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.gecmr		= 1,
	.bculr		= 1,
	.hw_swap	= 1,
	.nbst		= 1,
	.rpadir		= 1,
	.no_trimd	= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
	.csmr		= 1,
	.rx_csum	= 1,
	.select_mii	= 1,
	.magic		= 1,
	.cexcr		= 1,
पूर्ण;

/* R7S9210 */
अटल काष्ठा sh_eth_cpu_data r7s9210_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_rcar,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_SH4,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.ecsr_value	= ECSR_ICD,
	.ecsipr_value	= ECSIPR_ICDIP,
	.eesipr_value	= EESIPR_TWBIP | EESIPR_TABTIP | EESIPR_RABTIP |
			  EESIPR_RFCOFIP | EESIPR_ECIIP | EESIPR_FTCIP |
			  EESIPR_TDEIP | EESIPR_TFUFIP | EESIPR_FRIP |
			  EESIPR_RDEIP | EESIPR_RFOFIP | EESIPR_CNDIP |
			  EESIPR_DLCIP | EESIPR_CDIP | EESIPR_TROIP |
			  EESIPR_RMAFIP | EESIPR_RRFIP | EESIPR_RTLFIP |
			  EESIPR_RTSFIP | EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_FTC | EESR_CND | EESR_DLC | EESR_CD | EESR_TRO,
	.eesr_err_check	= EESR_TWB | EESR_TABT | EESR_RABT | EESR_RFE |
			  EESR_RDE | EESR_RFRMER | EESR_TFE | EESR_TDE,

	.fdr_value	= 0x0000070f,

	.trscer_err_mask = TRSCER_RMAFCE | TRSCER_RRFCE,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
	.rpadir		= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
पूर्ण;
#पूर्ण_अगर /* CONFIG_OF */

अटल व्योम sh_eth_set_rate_sh7724(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	चयन (mdp->speed) अणु
	हाल 10: /* 10BASE */
		sh_eth_modअगरy(ndev, ECMR, ECMR_RTM, 0);
		अवरोध;
	हाल 100:/* 100BASE */
		sh_eth_modअगरy(ndev, ECMR, ECMR_RTM, ECMR_RTM);
		अवरोध;
	पूर्ण
पूर्ण

/* SH7724 */
अटल काष्ठा sh_eth_cpu_data sh7724_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_sh7724,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_SH4,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.ecsr_value	= ECSR_PSRTO | ECSR_LCHNG | ECSR_ICD,
	.ecsipr_value	= ECSIPR_PSRTOIP | ECSIPR_LCHNGIP | ECSIPR_ICDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ADEIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_RMAFIP | EESIPR_RRFIP |
			  EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_FTC | EESR_CND | EESR_DLC | EESR_CD | EESR_TRO,
	.eesr_err_check	= EESR_TWB | EESR_TABT | EESR_RABT | EESR_RFE |
			  EESR_RDE | EESR_RFRMER | EESR_TFE | EESR_TDE,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
	.rpadir		= 1,
पूर्ण;

अटल व्योम sh_eth_set_rate_sh7757(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	चयन (mdp->speed) अणु
	हाल 10: /* 10BASE */
		sh_eth_ग_लिखो(ndev, 0, RTRATE);
		अवरोध;
	हाल 100:/* 100BASE */
		sh_eth_ग_लिखो(ndev, 1, RTRATE);
		अवरोध;
	पूर्ण
पूर्ण

/* SH7757 */
अटल काष्ठा sh_eth_cpu_data sh7757_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_sh7757,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_SH4,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  0x0000f000 | EESIPR_CNDIP | EESIPR_DLCIP |
			  EESIPR_CDIP | EESIPR_TROIP | EESIPR_RMAFIP |
			  EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_FTC | EESR_CND | EESR_DLC | EESR_CD | EESR_TRO,
	.eesr_err_check	= EESR_TWB | EESR_TABT | EESR_RABT | EESR_RFE |
			  EESR_RDE | EESR_RFRMER | EESR_TFE | EESR_TDE,

	.irq_flags	= IRQF_SHARED,
	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
	.no_ade		= 1,
	.rpadir		= 1,
	.rtrate		= 1,
	.dual_port	= 1,
पूर्ण;

#घोषणा SH_GIGA_ETH_BASE	0xfee00000UL
#घोषणा GIGA_MALR(port)		(SH_GIGA_ETH_BASE + 0x800 * (port) + 0x05c8)
#घोषणा GIGA_MAHR(port)		(SH_GIGA_ETH_BASE + 0x800 * (port) + 0x05c0)
अटल व्योम sh_eth_chip_reset_giga(काष्ठा net_device *ndev)
अणु
	u32 mahr[2], malr[2];
	पूर्णांक i;

	/* save MAHR and MALR */
	क्रम (i = 0; i < 2; i++) अणु
		malr[i] = ioपढ़ो32((व्योम *)GIGA_MALR(i));
		mahr[i] = ioपढ़ो32((व्योम *)GIGA_MAHR(i));
	पूर्ण

	sh_eth_chip_reset(ndev);

	/* restore MAHR and MALR */
	क्रम (i = 0; i < 2; i++) अणु
		ioग_लिखो32(malr[i], (व्योम *)GIGA_MALR(i));
		ioग_लिखो32(mahr[i], (व्योम *)GIGA_MAHR(i));
	पूर्ण
पूर्ण

अटल व्योम sh_eth_set_rate_giga(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	अगर (WARN_ON(!mdp->cd->gecmr))
		वापस;

	चयन (mdp->speed) अणु
	हाल 10: /* 10BASE */
		sh_eth_ग_लिखो(ndev, 0x00000000, GECMR);
		अवरोध;
	हाल 100:/* 100BASE */
		sh_eth_ग_लिखो(ndev, 0x00000010, GECMR);
		अवरोध;
	हाल 1000: /* 1000BASE */
		sh_eth_ग_लिखो(ndev, 0x00000020, GECMR);
		अवरोध;
	पूर्ण
पूर्ण

/* SH7757(GETHERC) */
अटल काष्ठा sh_eth_cpu_data sh7757_data_giga = अणु
	.soft_reset	= sh_eth_soft_reset_gether,

	.chip_reset	= sh_eth_chip_reset_giga,
	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_giga,

	.रेजिस्टर_type	= SH_ETH_REG_GIGABIT,

	.edtrr_trns	= EDTRR_TRNS_GETHER,
	.ecsr_value	= ECSR_ICD | ECSR_MPD,
	.ecsipr_value	= ECSIPR_LCHNGIP | ECSIPR_ICDIP | ECSIPR_MPDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  0x0000f000 | EESIPR_CNDIP | EESIPR_DLCIP |
			  EESIPR_CDIP | EESIPR_TROIP | EESIPR_RMAFIP |
			  EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_TC1 | EESR_FTC,
	.eesr_err_check	= EESR_TWB1 | EESR_TWB | EESR_TABT | EESR_RABT |
			  EESR_RFE | EESR_RDE | EESR_RFRMER | EESR_TFE |
			  EESR_TDE,
	.fdr_value	= 0x0000072f,

	.irq_flags	= IRQF_SHARED,
	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.gecmr		= 1,
	.bculr		= 1,
	.hw_swap	= 1,
	.rpadir		= 1,
	.no_trimd	= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
	.tsu		= 1,
	.cexcr		= 1,
	.dual_port	= 1,
पूर्ण;

/* SH7734 */
अटल काष्ठा sh_eth_cpu_data sh7734_data = अणु
	.soft_reset	= sh_eth_soft_reset_gether,

	.chip_reset	= sh_eth_chip_reset,
	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_gether,

	.रेजिस्टर_type	= SH_ETH_REG_GIGABIT,

	.edtrr_trns	= EDTRR_TRNS_GETHER,
	.ecsr_value	= ECSR_ICD | ECSR_MPD,
	.ecsipr_value	= ECSIPR_LCHNGIP | ECSIPR_ICDIP | ECSIPR_MPDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_DLCIP | EESIPR_CDIP | EESIPR_TROIP |
			  EESIPR_RMAFIP | EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_TC1 | EESR_FTC,
	.eesr_err_check	= EESR_TWB1 | EESR_TWB | EESR_TABT | EESR_RABT |
			  EESR_RFE | EESR_RDE | EESR_RFRMER | EESR_TFE |
			  EESR_TDE,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.gecmr		= 1,
	.bculr		= 1,
	.hw_swap	= 1,
	.no_trimd	= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
	.tsu		= 1,
	.csmr		= 1,
	.rx_csum	= 1,
	.select_mii	= 1,
	.magic		= 1,
	.cexcr		= 1,
पूर्ण;

/* SH7763 */
अटल काष्ठा sh_eth_cpu_data sh7763_data = अणु
	.soft_reset	= sh_eth_soft_reset_gether,

	.chip_reset	= sh_eth_chip_reset,
	.set_duplex	= sh_eth_set_duplex,
	.set_rate	= sh_eth_set_rate_gether,

	.रेजिस्टर_type	= SH_ETH_REG_GIGABIT,

	.edtrr_trns	= EDTRR_TRNS_GETHER,
	.ecsr_value	= ECSR_ICD | ECSR_MPD,
	.ecsipr_value	= ECSIPR_LCHNGIP | ECSIPR_ICDIP | ECSIPR_MPDIP,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  EESIPR_DLCIP | EESIPR_CDIP | EESIPR_TROIP |
			  EESIPR_RMAFIP | EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.tx_check	= EESR_TC1 | EESR_FTC,
	.eesr_err_check	= EESR_TWB1 | EESR_TWB | EESR_TABT | EESR_RABT |
			  EESR_RDE | EESR_RFRMER | EESR_TFE | EESR_TDE,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.gecmr		= 1,
	.bculr		= 1,
	.hw_swap	= 1,
	.no_trimd	= 1,
	.no_ade		= 1,
	.xdfar_rw	= 1,
	.tsu		= 1,
	.irq_flags	= IRQF_SHARED,
	.magic		= 1,
	.cexcr		= 1,
	.rx_csum	= 1,
	.dual_port	= 1,
पूर्ण;

अटल काष्ठा sh_eth_cpu_data sh7619_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_SH3_SH2,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  0x0000f000 | EESIPR_CNDIP | EESIPR_DLCIP |
			  EESIPR_CDIP | EESIPR_TROIP | EESIPR_RMAFIP |
			  EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.apr		= 1,
	.mpr		= 1,
	.tछोड़ोr	= 1,
	.hw_swap	= 1,
पूर्ण;

अटल काष्ठा sh_eth_cpu_data sh771x_data = अणु
	.soft_reset	= sh_eth_soft_reset,

	.रेजिस्टर_type	= SH_ETH_REG_FAST_SH3_SH2,

	.edtrr_trns	= EDTRR_TRNS_ETHER,
	.eesipr_value	= EESIPR_RFCOFIP | EESIPR_ECIIP |
			  EESIPR_FTCIP | EESIPR_TDEIP | EESIPR_TFUFIP |
			  EESIPR_FRIP | EESIPR_RDEIP | EESIPR_RFOFIP |
			  0x0000f000 | EESIPR_CNDIP | EESIPR_DLCIP |
			  EESIPR_CDIP | EESIPR_TROIP | EESIPR_RMAFIP |
			  EESIPR_CEEFIP | EESIPR_CELFIP |
			  EESIPR_RRFIP | EESIPR_RTLFIP | EESIPR_RTSFIP |
			  EESIPR_PREIP | EESIPR_CERFIP,

	.trscer_err_mask = TRSCER_RMAFCE,

	.tsu		= 1,
	.dual_port	= 1,
पूर्ण;

अटल व्योम sh_eth_set_शेष_cpu_data(काष्ठा sh_eth_cpu_data *cd)
अणु
	अगर (!cd->ecsr_value)
		cd->ecsr_value = DEFAULT_ECSR_INIT;

	अगर (!cd->ecsipr_value)
		cd->ecsipr_value = DEFAULT_ECSIPR_INIT;

	अगर (!cd->fcftr_value)
		cd->fcftr_value = DEFAULT_FIFO_F_D_RFF |
				  DEFAULT_FIFO_F_D_RFD;

	अगर (!cd->fdr_value)
		cd->fdr_value = DEFAULT_FDR_INIT;

	अगर (!cd->tx_check)
		cd->tx_check = DEFAULT_TX_CHECK;

	अगर (!cd->eesr_err_check)
		cd->eesr_err_check = DEFAULT_EESR_ERR_CHECK;

	अगर (!cd->trscer_err_mask)
		cd->trscer_err_mask = DEFAULT_TRSCER_ERR_MASK;
पूर्ण

अटल व्योम sh_eth_set_receive_align(काष्ठा sk_buff *skb)
अणु
	uपूर्णांकptr_t reserve = (uपूर्णांकptr_t)skb->data & (SH_ETH_RX_ALIGN - 1);

	अगर (reserve)
		skb_reserve(skb, SH_ETH_RX_ALIGN - reserve);
पूर्ण

/* Program the hardware MAC address from dev->dev_addr. */
अटल व्योम update_mac_address(काष्ठा net_device *ndev)
अणु
	sh_eth_ग_लिखो(ndev,
		     (ndev->dev_addr[0] << 24) | (ndev->dev_addr[1] << 16) |
		     (ndev->dev_addr[2] << 8) | (ndev->dev_addr[3]), MAHR);
	sh_eth_ग_लिखो(ndev,
		     (ndev->dev_addr[4] << 8) | (ndev->dev_addr[5]), MALR);
पूर्ण

/* Get MAC address from SuperH MAC address रेजिस्टर
 *
 * SuperH's Ethernet device doesn't have 'ROM' to MAC address.
 * This driver get MAC address that use by bootloader(U-boot or sh-ipl+g).
 * When you want use this device, you must set MAC address in bootloader.
 *
 */
अटल व्योम पढ़ो_mac_address(काष्ठा net_device *ndev, अचिन्हित अक्षर *mac)
अणु
	अगर (mac[0] || mac[1] || mac[2] || mac[3] || mac[4] || mac[5]) अणु
		स_नकल(ndev->dev_addr, mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		u32 mahr = sh_eth_पढ़ो(ndev, MAHR);
		u32 malr = sh_eth_पढ़ो(ndev, MALR);

		ndev->dev_addr[0] = (mahr >> 24) & 0xFF;
		ndev->dev_addr[1] = (mahr >> 16) & 0xFF;
		ndev->dev_addr[2] = (mahr >>  8) & 0xFF;
		ndev->dev_addr[3] = (mahr >>  0) & 0xFF;
		ndev->dev_addr[4] = (malr >>  8) & 0xFF;
		ndev->dev_addr[5] = (malr >>  0) & 0xFF;
	पूर्ण
पूर्ण

काष्ठा bb_info अणु
	व्योम (*set_gate)(व्योम *addr);
	काष्ठा mdiobb_ctrl ctrl;
	व्योम *addr;
पूर्ण;

अटल व्योम sh_mdio_ctrl(काष्ठा mdiobb_ctrl *ctrl, u32 mask, पूर्णांक set)
अणु
	काष्ठा bb_info *bitbang = container_of(ctrl, काष्ठा bb_info, ctrl);
	u32 pir;

	अगर (bitbang->set_gate)
		bitbang->set_gate(bitbang->addr);

	pir = ioपढ़ो32(bitbang->addr);
	अगर (set)
		pir |=  mask;
	अन्यथा
		pir &= ~mask;
	ioग_लिखो32(pir, bitbang->addr);
पूर्ण

/* Data I/O pin control */
अटल व्योम sh_mmd_ctrl(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक bit)
अणु
	sh_mdio_ctrl(ctrl, PIR_MMD, bit);
पूर्ण

/* Set bit data*/
अटल व्योम sh_set_mdio(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक bit)
अणु
	sh_mdio_ctrl(ctrl, PIR_MDO, bit);
पूर्ण

/* Get bit data*/
अटल पूर्णांक sh_get_mdio(काष्ठा mdiobb_ctrl *ctrl)
अणु
	काष्ठा bb_info *bitbang = container_of(ctrl, काष्ठा bb_info, ctrl);

	अगर (bitbang->set_gate)
		bitbang->set_gate(bitbang->addr);

	वापस (ioपढ़ो32(bitbang->addr) & PIR_MDI) != 0;
पूर्ण

/* MDC pin control */
अटल व्योम sh_mdc_ctrl(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक bit)
अणु
	sh_mdio_ctrl(ctrl, PIR_MDC, bit);
पूर्ण

/* mdio bus control काष्ठा */
अटल स्थिर काष्ठा mdiobb_ops bb_ops = अणु
	.owner = THIS_MODULE,
	.set_mdc = sh_mdc_ctrl,
	.set_mdio_dir = sh_mmd_ctrl,
	.set_mdio_data = sh_set_mdio,
	.get_mdio_data = sh_get_mdio,
पूर्ण;

/* मुक्त Tx skb function */
अटल पूर्णांक sh_eth_tx_मुक्त(काष्ठा net_device *ndev, bool sent_only)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा sh_eth_txdesc *txdesc;
	पूर्णांक मुक्त_num = 0;
	पूर्णांक entry;
	bool sent;

	क्रम (; mdp->cur_tx - mdp->dirty_tx > 0; mdp->dirty_tx++) अणु
		entry = mdp->dirty_tx % mdp->num_tx_ring;
		txdesc = &mdp->tx_ring[entry];
		sent = !(txdesc->status & cpu_to_le32(TD_TACT));
		अगर (sent_only && !sent)
			अवरोध;
		/* TACT bit must be checked beक्रमe all the following पढ़ोs */
		dma_rmb();
		netअगर_info(mdp, tx_करोne, ndev,
			   "tx entry %d status 0x%08x\n",
			   entry, le32_to_cpu(txdesc->status));
		/* Free the original skb. */
		अगर (mdp->tx_skbuff[entry]) अणु
			dma_unmap_single(&mdp->pdev->dev,
					 le32_to_cpu(txdesc->addr),
					 le32_to_cpu(txdesc->len) >> 16,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_irq(mdp->tx_skbuff[entry]);
			mdp->tx_skbuff[entry] = शून्य;
			मुक्त_num++;
		पूर्ण
		txdesc->status = cpu_to_le32(TD_TFP);
		अगर (entry >= mdp->num_tx_ring - 1)
			txdesc->status |= cpu_to_le32(TD_TDLE);

		अगर (sent) अणु
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += le32_to_cpu(txdesc->len) >> 16;
		पूर्ण
	पूर्ण
	वापस मुक्त_num;
पूर्ण

/* मुक्त skb and descriptor buffer */
अटल व्योम sh_eth_ring_मुक्त(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ringsize, i;

	अगर (mdp->rx_ring) अणु
		क्रम (i = 0; i < mdp->num_rx_ring; i++) अणु
			अगर (mdp->rx_skbuff[i]) अणु
				काष्ठा sh_eth_rxdesc *rxdesc = &mdp->rx_ring[i];

				dma_unmap_single(&mdp->pdev->dev,
						 le32_to_cpu(rxdesc->addr),
						 ALIGN(mdp->rx_buf_sz, 32),
						 DMA_FROM_DEVICE);
			पूर्ण
		पूर्ण
		ringsize = माप(काष्ठा sh_eth_rxdesc) * mdp->num_rx_ring;
		dma_मुक्त_coherent(&mdp->pdev->dev, ringsize, mdp->rx_ring,
				  mdp->rx_desc_dma);
		mdp->rx_ring = शून्य;
	पूर्ण

	/* Free Rx skb ringbuffer */
	अगर (mdp->rx_skbuff) अणु
		क्रम (i = 0; i < mdp->num_rx_ring; i++)
			dev_kमुक्त_skb(mdp->rx_skbuff[i]);
	पूर्ण
	kमुक्त(mdp->rx_skbuff);
	mdp->rx_skbuff = शून्य;

	अगर (mdp->tx_ring) अणु
		sh_eth_tx_मुक्त(ndev, false);

		ringsize = माप(काष्ठा sh_eth_txdesc) * mdp->num_tx_ring;
		dma_मुक्त_coherent(&mdp->pdev->dev, ringsize, mdp->tx_ring,
				  mdp->tx_desc_dma);
		mdp->tx_ring = शून्य;
	पूर्ण

	/* Free Tx skb ringbuffer */
	kमुक्त(mdp->tx_skbuff);
	mdp->tx_skbuff = शून्य;
पूर्ण

/* क्रमmat skb and descriptor buffer */
अटल व्योम sh_eth_ring_क्रमmat(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा sh_eth_rxdesc *rxdesc = शून्य;
	काष्ठा sh_eth_txdesc *txdesc = शून्य;
	पूर्णांक rx_ringsize = माप(*rxdesc) * mdp->num_rx_ring;
	पूर्णांक tx_ringsize = माप(*txdesc) * mdp->num_tx_ring;
	पूर्णांक skbuff_size = mdp->rx_buf_sz + SH_ETH_RX_ALIGN + 32 - 1;
	dma_addr_t dma_addr;
	u32 buf_len;

	mdp->cur_rx = 0;
	mdp->cur_tx = 0;
	mdp->dirty_rx = 0;
	mdp->dirty_tx = 0;

	स_रखो(mdp->rx_ring, 0, rx_ringsize);

	/* build Rx ring buffer */
	क्रम (i = 0; i < mdp->num_rx_ring; i++) अणु
		/* skb */
		mdp->rx_skbuff[i] = शून्य;
		skb = netdev_alloc_skb(ndev, skbuff_size);
		अगर (skb == शून्य)
			अवरोध;
		sh_eth_set_receive_align(skb);

		/* The size of the buffer is a multiple of 32 bytes. */
		buf_len = ALIGN(mdp->rx_buf_sz, 32);
		dma_addr = dma_map_single(&mdp->pdev->dev, skb->data, buf_len,
					  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&mdp->pdev->dev, dma_addr)) अणु
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
		mdp->rx_skbuff[i] = skb;

		/* RX descriptor */
		rxdesc = &mdp->rx_ring[i];
		rxdesc->len = cpu_to_le32(buf_len << 16);
		rxdesc->addr = cpu_to_le32(dma_addr);
		rxdesc->status = cpu_to_le32(RD_RACT | RD_RFP);

		/* Rx descriptor address set */
		अगर (i == 0) अणु
			sh_eth_ग_लिखो(ndev, mdp->rx_desc_dma, RDLAR);
			अगर (mdp->cd->xdfar_rw)
				sh_eth_ग_लिखो(ndev, mdp->rx_desc_dma, RDFAR);
		पूर्ण
	पूर्ण

	mdp->dirty_rx = (u32) (i - mdp->num_rx_ring);

	/* Mark the last entry as wrapping the ring. */
	अगर (rxdesc)
		rxdesc->status |= cpu_to_le32(RD_RDLE);

	स_रखो(mdp->tx_ring, 0, tx_ringsize);

	/* build Tx ring buffer */
	क्रम (i = 0; i < mdp->num_tx_ring; i++) अणु
		mdp->tx_skbuff[i] = शून्य;
		txdesc = &mdp->tx_ring[i];
		txdesc->status = cpu_to_le32(TD_TFP);
		txdesc->len = cpu_to_le32(0);
		अगर (i == 0) अणु
			/* Tx descriptor address set */
			sh_eth_ग_लिखो(ndev, mdp->tx_desc_dma, TDLAR);
			अगर (mdp->cd->xdfar_rw)
				sh_eth_ग_लिखो(ndev, mdp->tx_desc_dma, TDFAR);
		पूर्ण
	पूर्ण

	txdesc->status |= cpu_to_le32(TD_TDLE);
पूर्ण

/* Get skb and descriptor buffer */
अटल पूर्णांक sh_eth_ring_init(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक rx_ringsize, tx_ringsize;

	/* +26 माला_लो the maximum ethernet encapsulation, +7 & ~7 because the
	 * card needs room to करो 8 byte alignment, +2 so we can reserve
	 * the first 2 bytes, and +16 माला_लो room क्रम the status word from the
	 * card.
	 */
	mdp->rx_buf_sz = (ndev->mtu <= 1492 ? PKT_BUF_SZ :
			  (((ndev->mtu + 26 + 7) & ~7) + 2 + 16));
	अगर (mdp->cd->rpadir)
		mdp->rx_buf_sz += NET_IP_ALIGN;

	/* Allocate RX and TX skb rings */
	mdp->rx_skbuff = kसुस्मृति(mdp->num_rx_ring, माप(*mdp->rx_skbuff),
				 GFP_KERNEL);
	अगर (!mdp->rx_skbuff)
		वापस -ENOMEM;

	mdp->tx_skbuff = kसुस्मृति(mdp->num_tx_ring, माप(*mdp->tx_skbuff),
				 GFP_KERNEL);
	अगर (!mdp->tx_skbuff)
		जाओ ring_मुक्त;

	/* Allocate all Rx descriptors. */
	rx_ringsize = माप(काष्ठा sh_eth_rxdesc) * mdp->num_rx_ring;
	mdp->rx_ring = dma_alloc_coherent(&mdp->pdev->dev, rx_ringsize,
					  &mdp->rx_desc_dma, GFP_KERNEL);
	अगर (!mdp->rx_ring)
		जाओ ring_मुक्त;

	mdp->dirty_rx = 0;

	/* Allocate all Tx descriptors. */
	tx_ringsize = माप(काष्ठा sh_eth_txdesc) * mdp->num_tx_ring;
	mdp->tx_ring = dma_alloc_coherent(&mdp->pdev->dev, tx_ringsize,
					  &mdp->tx_desc_dma, GFP_KERNEL);
	अगर (!mdp->tx_ring)
		जाओ ring_मुक्त;
	वापस 0;

ring_मुक्त:
	/* Free Rx and Tx skb ring buffer and DMA buffer */
	sh_eth_ring_मुक्त(ndev);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक sh_eth_dev_init(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret;

	/* Soft Reset */
	ret = mdp->cd->soft_reset(ndev);
	अगर (ret)
		वापस ret;

	अगर (mdp->cd->rmiimode)
		sh_eth_ग_लिखो(ndev, 0x1, RMIIMODE);

	/* Descriptor क्रमmat */
	sh_eth_ring_क्रमmat(ndev);
	अगर (mdp->cd->rpadir)
		sh_eth_ग_लिखो(ndev, NET_IP_ALIGN << 16, RPAसूची);

	/* all sh_eth पूर्णांक mask */
	sh_eth_ग_लिखो(ndev, 0, EESIPR);

#अगर defined(__LITTLE_ENDIAN)
	अगर (mdp->cd->hw_swap)
		sh_eth_ग_लिखो(ndev, EDMR_EL, EDMR);
	अन्यथा
#पूर्ण_अगर
		sh_eth_ग_लिखो(ndev, 0, EDMR);

	/* FIFO size set */
	sh_eth_ग_लिखो(ndev, mdp->cd->fdr_value, FDR);
	sh_eth_ग_लिखो(ndev, 0, TFTR);

	/* Frame recv control (enable multiple-packets per rx irq) */
	sh_eth_ग_लिखो(ndev, RMCR_RNC, RMCR);

	sh_eth_ग_लिखो(ndev, mdp->cd->trscer_err_mask, TRSCER);

	/* DMA transfer burst mode */
	अगर (mdp->cd->nbst)
		sh_eth_modअगरy(ndev, EDMR, EDMR_NBST, EDMR_NBST);

	/* Burst cycle count upper-limit */
	अगर (mdp->cd->bculr)
		sh_eth_ग_लिखो(ndev, 0x800, BCULR);

	sh_eth_ग_लिखो(ndev, mdp->cd->fcftr_value, FCFTR);

	अगर (!mdp->cd->no_trimd)
		sh_eth_ग_लिखो(ndev, 0, TRIMD);

	/* Recv frame limit set रेजिस्टर */
	sh_eth_ग_लिखो(ndev, ndev->mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN,
		     RFLR);

	sh_eth_modअगरy(ndev, EESR, 0, 0);
	mdp->irq_enabled = true;
	sh_eth_ग_लिखो(ndev, mdp->cd->eesipr_value, EESIPR);

	/* EMAC Mode: PAUSE prohibition; Duplex; RX Checksum; TX; RX */
	sh_eth_ग_लिखो(ndev, ECMR_ZPF | (mdp->duplex ? ECMR_DM : 0) |
		     (ndev->features & NETIF_F_RXCSUM ? ECMR_RCSC : 0) |
		     ECMR_TE | ECMR_RE, ECMR);

	अगर (mdp->cd->set_rate)
		mdp->cd->set_rate(ndev);

	/* E-MAC Status Register clear */
	sh_eth_ग_लिखो(ndev, mdp->cd->ecsr_value, ECSR);

	/* E-MAC Interrupt Enable रेजिस्टर */
	sh_eth_ग_लिखो(ndev, mdp->cd->ecsipr_value, ECSIPR);

	/* Set MAC address */
	update_mac_address(ndev);

	/* mask reset */
	अगर (mdp->cd->apr)
		sh_eth_ग_लिखो(ndev, 1, APR);
	अगर (mdp->cd->mpr)
		sh_eth_ग_लिखो(ndev, 1, MPR);
	अगर (mdp->cd->tछोड़ोr)
		sh_eth_ग_लिखो(ndev, TPAUSER_UNLIMITED, TPAUSER);

	/* Setting the Rx mode will start the Rx process. */
	sh_eth_ग_लिखो(ndev, EDRRR_R, EDRRR);

	वापस ret;
पूर्ण

अटल व्योम sh_eth_dev_निकास(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक i;

	/* Deactivate all TX descriptors, so DMA should stop at next
	 * packet boundary अगर it's currently running
	 */
	क्रम (i = 0; i < mdp->num_tx_ring; i++)
		mdp->tx_ring[i].status &= ~cpu_to_le32(TD_TACT);

	/* Disable TX FIFO egress to MAC */
	sh_eth_rcv_snd_disable(ndev);

	/* Stop RX DMA at next packet boundary */
	sh_eth_ग_लिखो(ndev, 0, EDRRR);

	/* Aside from TX DMA, we can't tell when the hardware is
	 * really stopped, so we need to reset to make sure.
	 * Beक्रमe करोing that, रुको क्रम दीर्घ enough to *probably*
	 * finish transmitting the last packet and poll stats.
	 */
	msleep(2); /* max frame समय at 10 Mbps < 1250 us */
	sh_eth_get_stats(ndev);
	mdp->cd->soft_reset(ndev);

	/* Set the RMII mode again अगर required */
	अगर (mdp->cd->rmiimode)
		sh_eth_ग_लिखो(ndev, 0x1, RMIIMODE);

	/* Set MAC address again */
	update_mac_address(ndev);
पूर्ण

अटल व्योम sh_eth_rx_csum(काष्ठा sk_buff *skb)
अणु
	u8 *hw_csum;

	/* The hardware checksum is 2 bytes appended to packet data */
	अगर (unlikely(skb->len < माप(__sum16)))
		वापस;
	hw_csum = skb_tail_poपूर्णांकer(skb) - माप(__sum16);
	skb->csum = csum_unfold((__क्रमce __sum16)get_unaligned_le16(hw_csum));
	skb->ip_summed = CHECKSUM_COMPLETE;
	skb_trim(skb, skb->len - माप(__sum16));
पूर्ण

/* Packet receive function */
अटल पूर्णांक sh_eth_rx(काष्ठा net_device *ndev, u32 पूर्णांकr_status, पूर्णांक *quota)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा sh_eth_rxdesc *rxdesc;

	पूर्णांक entry = mdp->cur_rx % mdp->num_rx_ring;
	पूर्णांक boguscnt = (mdp->dirty_rx + mdp->num_rx_ring) - mdp->cur_rx;
	पूर्णांक limit;
	काष्ठा sk_buff *skb;
	u32 desc_status;
	पूर्णांक skbuff_size = mdp->rx_buf_sz + SH_ETH_RX_ALIGN + 32 - 1;
	dma_addr_t dma_addr;
	u16 pkt_len;
	u32 buf_len;

	boguscnt = min(boguscnt, *quota);
	limit = boguscnt;
	rxdesc = &mdp->rx_ring[entry];
	जबतक (!(rxdesc->status & cpu_to_le32(RD_RACT))) अणु
		/* RACT bit must be checked beक्रमe all the following पढ़ोs */
		dma_rmb();
		desc_status = le32_to_cpu(rxdesc->status);
		pkt_len = le32_to_cpu(rxdesc->len) & RD_RFL;

		अगर (--boguscnt < 0)
			अवरोध;

		netअगर_info(mdp, rx_status, ndev,
			   "rx entry %d status 0x%08x len %d\n",
			   entry, desc_status, pkt_len);

		अगर (!(desc_status & RDFEND))
			ndev->stats.rx_length_errors++;

		/* In हाल of almost all GETHER/ETHERs, the Receive Frame State
		 * (RFS) bits in the Receive Descriptor 0 are from bit 9 to
		 * bit 0. However, in हाल of the R8A7740 and R7S72100
		 * the RFS bits are from bit 25 to bit 16. So, the
		 * driver needs right shअगरting by 16.
		 */
		अगर (mdp->cd->csmr)
			desc_status >>= 16;

		skb = mdp->rx_skbuff[entry];
		अगर (desc_status & (RD_RFS1 | RD_RFS2 | RD_RFS3 | RD_RFS4 |
				   RD_RFS5 | RD_RFS6 | RD_RFS10)) अणु
			ndev->stats.rx_errors++;
			अगर (desc_status & RD_RFS1)
				ndev->stats.rx_crc_errors++;
			अगर (desc_status & RD_RFS2)
				ndev->stats.rx_frame_errors++;
			अगर (desc_status & RD_RFS3)
				ndev->stats.rx_length_errors++;
			अगर (desc_status & RD_RFS4)
				ndev->stats.rx_length_errors++;
			अगर (desc_status & RD_RFS6)
				ndev->stats.rx_missed_errors++;
			अगर (desc_status & RD_RFS10)
				ndev->stats.rx_over_errors++;
		पूर्ण अन्यथा	अगर (skb) अणु
			dma_addr = le32_to_cpu(rxdesc->addr);
			अगर (!mdp->cd->hw_swap)
				sh_eth_soft_swap(
					phys_to_virt(ALIGN(dma_addr, 4)),
					pkt_len + 2);
			mdp->rx_skbuff[entry] = शून्य;
			अगर (mdp->cd->rpadir)
				skb_reserve(skb, NET_IP_ALIGN);
			dma_unmap_single(&mdp->pdev->dev, dma_addr,
					 ALIGN(mdp->rx_buf_sz, 32),
					 DMA_FROM_DEVICE);
			skb_put(skb, pkt_len);
			skb->protocol = eth_type_trans(skb, ndev);
			अगर (ndev->features & NETIF_F_RXCSUM)
				sh_eth_rx_csum(skb);
			netअगर_receive_skb(skb);
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += pkt_len;
			अगर (desc_status & RD_RFS8)
				ndev->stats.multicast++;
		पूर्ण
		entry = (++mdp->cur_rx) % mdp->num_rx_ring;
		rxdesc = &mdp->rx_ring[entry];
	पूर्ण

	/* Refill the Rx ring buffers. */
	क्रम (; mdp->cur_rx - mdp->dirty_rx > 0; mdp->dirty_rx++) अणु
		entry = mdp->dirty_rx % mdp->num_rx_ring;
		rxdesc = &mdp->rx_ring[entry];
		/* The size of the buffer is 32 byte boundary. */
		buf_len = ALIGN(mdp->rx_buf_sz, 32);
		rxdesc->len = cpu_to_le32(buf_len << 16);

		अगर (mdp->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb(ndev, skbuff_size);
			अगर (skb == शून्य)
				अवरोध;	/* Better luck next round. */
			sh_eth_set_receive_align(skb);
			dma_addr = dma_map_single(&mdp->pdev->dev, skb->data,
						  buf_len, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&mdp->pdev->dev, dma_addr)) अणु
				kमुक्त_skb(skb);
				अवरोध;
			पूर्ण
			mdp->rx_skbuff[entry] = skb;

			skb_checksum_none_निश्चित(skb);
			rxdesc->addr = cpu_to_le32(dma_addr);
		पूर्ण
		dma_wmb(); /* RACT bit must be set after all the above ग_लिखोs */
		अगर (entry >= mdp->num_rx_ring - 1)
			rxdesc->status |=
				cpu_to_le32(RD_RACT | RD_RFP | RD_RDLE);
		अन्यथा
			rxdesc->status |= cpu_to_le32(RD_RACT | RD_RFP);
	पूर्ण

	/* Restart Rx engine अगर stopped. */
	/* If we करोn't need to check status, don't. -KDU */
	अगर (!(sh_eth_पढ़ो(ndev, EDRRR) & EDRRR_R)) अणु
		/* fix the values क्रम the next receiving अगर RDE is set */
		अगर (पूर्णांकr_status & EESR_RDE && !mdp->cd->no_xdfar) अणु
			u32 count = (sh_eth_पढ़ो(ndev, RDFAR) -
				     sh_eth_पढ़ो(ndev, RDLAR)) >> 4;

			mdp->cur_rx = count;
			mdp->dirty_rx = count;
		पूर्ण
		sh_eth_ग_लिखो(ndev, EDRRR_R, EDRRR);
	पूर्ण

	*quota -= limit - boguscnt - 1;

	वापस *quota <= 0;
पूर्ण

अटल व्योम sh_eth_rcv_snd_disable(काष्ठा net_device *ndev)
अणु
	/* disable tx and rx */
	sh_eth_modअगरy(ndev, ECMR, ECMR_RE | ECMR_TE, 0);
पूर्ण

अटल व्योम sh_eth_rcv_snd_enable(काष्ठा net_device *ndev)
अणु
	/* enable tx and rx */
	sh_eth_modअगरy(ndev, ECMR, ECMR_RE | ECMR_TE, ECMR_RE | ECMR_TE);
पूर्ण

/* E-MAC पूर्णांकerrupt handler */
अटल व्योम sh_eth_emac_पूर्णांकerrupt(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u32 felic_stat;
	u32 link_stat;

	felic_stat = sh_eth_पढ़ो(ndev, ECSR) & sh_eth_पढ़ो(ndev, ECSIPR);
	sh_eth_ग_लिखो(ndev, felic_stat, ECSR);	/* clear पूर्णांक */
	अगर (felic_stat & ECSR_ICD)
		ndev->stats.tx_carrier_errors++;
	अगर (felic_stat & ECSR_MPD)
		pm_wakeup_event(&mdp->pdev->dev, 0);
	अगर (felic_stat & ECSR_LCHNG) अणु
		/* Link Changed */
		अगर (mdp->cd->no_psr || mdp->no_ether_link)
			वापस;
		link_stat = sh_eth_पढ़ो(ndev, PSR);
		अगर (mdp->ether_link_active_low)
			link_stat = ~link_stat;
		अगर (!(link_stat & PSR_LMON)) अणु
			sh_eth_rcv_snd_disable(ndev);
		पूर्ण अन्यथा अणु
			/* Link Up */
			sh_eth_modअगरy(ndev, EESIPR, EESIPR_ECIIP, 0);
			/* clear पूर्णांक */
			sh_eth_modअगरy(ndev, ECSR, 0, 0);
			sh_eth_modअगरy(ndev, EESIPR, EESIPR_ECIIP, EESIPR_ECIIP);
			/* enable tx and rx */
			sh_eth_rcv_snd_enable(ndev);
		पूर्ण
	पूर्ण
पूर्ण

/* error control function */
अटल व्योम sh_eth_error(काष्ठा net_device *ndev, u32 पूर्णांकr_status)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u32 mask;

	अगर (पूर्णांकr_status & EESR_TWB) अणु
		/* Unused ग_लिखो back पूर्णांकerrupt */
		अगर (पूर्णांकr_status & EESR_TABT) अणु	/* Transmit Abort पूर्णांक */
			ndev->stats.tx_पातed_errors++;
			netअगर_err(mdp, tx_err, ndev, "Transmit Abort\n");
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr_status & EESR_RABT) अणु
		/* Receive Abort पूर्णांक */
		अगर (पूर्णांकr_status & EESR_RFRMER) अणु
			/* Receive Frame Overflow पूर्णांक */
			ndev->stats.rx_frame_errors++;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr_status & EESR_TDE) अणु
		/* Transmit Descriptor Empty पूर्णांक */
		ndev->stats.tx_fअगरo_errors++;
		netअगर_err(mdp, tx_err, ndev, "Transmit Descriptor Empty\n");
	पूर्ण

	अगर (पूर्णांकr_status & EESR_TFE) अणु
		/* FIFO under flow */
		ndev->stats.tx_fअगरo_errors++;
		netअगर_err(mdp, tx_err, ndev, "Transmit FIFO Under flow\n");
	पूर्ण

	अगर (पूर्णांकr_status & EESR_RDE) अणु
		/* Receive Descriptor Empty पूर्णांक */
		ndev->stats.rx_over_errors++;
	पूर्ण

	अगर (पूर्णांकr_status & EESR_RFE) अणु
		/* Receive FIFO Overflow पूर्णांक */
		ndev->stats.rx_fअगरo_errors++;
	पूर्ण

	अगर (!mdp->cd->no_ade && (पूर्णांकr_status & EESR_ADE)) अणु
		/* Address Error */
		ndev->stats.tx_fअगरo_errors++;
		netअगर_err(mdp, tx_err, ndev, "Address Error\n");
	पूर्ण

	mask = EESR_TWB | EESR_TABT | EESR_ADE | EESR_TDE | EESR_TFE;
	अगर (mdp->cd->no_ade)
		mask &= ~EESR_ADE;
	अगर (पूर्णांकr_status & mask) अणु
		/* Tx error */
		u32 edtrr = sh_eth_पढ़ो(ndev, EDTRR);

		/* dmesg */
		netdev_err(ndev, "TX error. status=%8.8x cur_tx=%8.8x dirty_tx=%8.8x state=%8.8x EDTRR=%8.8x.\n",
			   पूर्णांकr_status, mdp->cur_tx, mdp->dirty_tx,
			   (u32)ndev->state, edtrr);
		/* dirty buffer मुक्त */
		sh_eth_tx_मुक्त(ndev, true);

		/* SH7712 BUG */
		अगर (edtrr ^ mdp->cd->edtrr_trns) अणु
			/* tx dma start */
			sh_eth_ग_लिखो(ndev, mdp->cd->edtrr_trns, EDTRR);
		पूर्ण
		/* wakeup */
		netअगर_wake_queue(ndev);
	पूर्ण
पूर्ण

अटल irqवापस_t sh_eth_पूर्णांकerrupt(पूर्णांक irq, व्योम *netdev)
अणु
	काष्ठा net_device *ndev = netdev;
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा sh_eth_cpu_data *cd = mdp->cd;
	irqवापस_t ret = IRQ_NONE;
	u32 पूर्णांकr_status, पूर्णांकr_enable;

	spin_lock(&mdp->lock);

	/* Get पूर्णांकerrupt status */
	पूर्णांकr_status = sh_eth_पढ़ो(ndev, EESR);
	/* Mask it with the पूर्णांकerrupt mask, क्रमcing ECI पूर्णांकerrupt  to be always
	 * enabled since it's the one that  comes  thru regardless of the mask,
	 * and  we need to fully handle it  in sh_eth_emac_पूर्णांकerrupt() in order
	 * to quench it as it करोesn't get cleared by just writing 1 to the  ECI
	 * bit...
	 */
	पूर्णांकr_enable = sh_eth_पढ़ो(ndev, EESIPR);
	पूर्णांकr_status &= पूर्णांकr_enable | EESIPR_ECIIP;
	अगर (पूर्णांकr_status & (EESR_RX_CHECK | cd->tx_check | EESR_ECI |
			   cd->eesr_err_check))
		ret = IRQ_HANDLED;
	अन्यथा
		जाओ out;

	अगर (unlikely(!mdp->irq_enabled)) अणु
		sh_eth_ग_लिखो(ndev, 0, EESIPR);
		जाओ out;
	पूर्ण

	अगर (पूर्णांकr_status & EESR_RX_CHECK) अणु
		अगर (napi_schedule_prep(&mdp->napi)) अणु
			/* Mask Rx पूर्णांकerrupts */
			sh_eth_ग_लिखो(ndev, पूर्णांकr_enable & ~EESR_RX_CHECK,
				     EESIPR);
			__napi_schedule(&mdp->napi);
		पूर्ण अन्यथा अणु
			netdev_warn(ndev,
				    "ignoring interrupt, status 0x%08x, mask 0x%08x.\n",
				    पूर्णांकr_status, पूर्णांकr_enable);
		पूर्ण
	पूर्ण

	/* Tx Check */
	अगर (पूर्णांकr_status & cd->tx_check) अणु
		/* Clear Tx पूर्णांकerrupts */
		sh_eth_ग_लिखो(ndev, पूर्णांकr_status & cd->tx_check, EESR);

		sh_eth_tx_मुक्त(ndev, true);
		netअगर_wake_queue(ndev);
	पूर्ण

	/* E-MAC पूर्णांकerrupt */
	अगर (पूर्णांकr_status & EESR_ECI)
		sh_eth_emac_पूर्णांकerrupt(ndev);

	अगर (पूर्णांकr_status & cd->eesr_err_check) अणु
		/* Clear error पूर्णांकerrupts */
		sh_eth_ग_लिखो(ndev, पूर्णांकr_status & cd->eesr_err_check, EESR);

		sh_eth_error(ndev, पूर्णांकr_status);
	पूर्ण

out:
	spin_unlock(&mdp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sh_eth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा sh_eth_निजी *mdp = container_of(napi, काष्ठा sh_eth_निजी,
						  napi);
	काष्ठा net_device *ndev = napi->dev;
	पूर्णांक quota = budget;
	u32 पूर्णांकr_status;

	क्रम (;;) अणु
		पूर्णांकr_status = sh_eth_पढ़ो(ndev, EESR);
		अगर (!(पूर्णांकr_status & EESR_RX_CHECK))
			अवरोध;
		/* Clear Rx पूर्णांकerrupts */
		sh_eth_ग_लिखो(ndev, पूर्णांकr_status & EESR_RX_CHECK, EESR);

		अगर (sh_eth_rx(ndev, पूर्णांकr_status, &quota))
			जाओ out;
	पूर्ण

	napi_complete(napi);

	/* Reenable Rx पूर्णांकerrupts */
	अगर (mdp->irq_enabled)
		sh_eth_ग_लिखो(ndev, mdp->cd->eesipr_value, EESIPR);
out:
	वापस budget - quota;
पूर्ण

/* PHY state control function */
अटल व्योम sh_eth_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक new_state = 0;

	spin_lock_irqsave(&mdp->lock, flags);

	/* Disable TX and RX right over here, अगर E-MAC change is ignored */
	अगर (mdp->cd->no_psr || mdp->no_ether_link)
		sh_eth_rcv_snd_disable(ndev);

	अगर (phydev->link) अणु
		अगर (phydev->duplex != mdp->duplex) अणु
			new_state = 1;
			mdp->duplex = phydev->duplex;
			अगर (mdp->cd->set_duplex)
				mdp->cd->set_duplex(ndev);
		पूर्ण

		अगर (phydev->speed != mdp->speed) अणु
			new_state = 1;
			mdp->speed = phydev->speed;
			अगर (mdp->cd->set_rate)
				mdp->cd->set_rate(ndev);
		पूर्ण
		अगर (!mdp->link) अणु
			sh_eth_modअगरy(ndev, ECMR, ECMR_TXF, 0);
			new_state = 1;
			mdp->link = phydev->link;
		पूर्ण
	पूर्ण अन्यथा अगर (mdp->link) अणु
		new_state = 1;
		mdp->link = 0;
		mdp->speed = 0;
		mdp->duplex = -1;
	पूर्ण

	/* Enable TX and RX right over here, अगर E-MAC change is ignored */
	अगर ((mdp->cd->no_psr || mdp->no_ether_link) && phydev->link)
		sh_eth_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&mdp->lock, flags);

	अगर (new_state && netअगर_msg_link(mdp))
		phy_prपूर्णांक_status(phydev);
पूर्ण

/* PHY init function */
अटल पूर्णांक sh_eth_phy_init(काष्ठा net_device *ndev)
अणु
	काष्ठा device_node *np = ndev->dev.parent->of_node;
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा phy_device *phydev;

	mdp->link = 0;
	mdp->speed = 0;
	mdp->duplex = -1;

	/* Try connect to PHY */
	अगर (np) अणु
		काष्ठा device_node *pn;

		pn = of_parse_phandle(np, "phy-handle", 0);
		phydev = of_phy_connect(ndev, pn,
					sh_eth_adjust_link, 0,
					mdp->phy_पूर्णांकerface);

		of_node_put(pn);
		अगर (!phydev)
			phydev = ERR_PTR(-ENOENT);
	पूर्ण अन्यथा अणु
		अक्षर phy_id[MII_BUS_ID_SIZE + 3];

		snम_लिखो(phy_id, माप(phy_id), PHY_ID_FMT,
			 mdp->mii_bus->id, mdp->phy_id);

		phydev = phy_connect(ndev, phy_id, sh_eth_adjust_link,
				     mdp->phy_पूर्णांकerface);
	पूर्ण

	अगर (IS_ERR(phydev)) अणु
		netdev_err(ndev, "failed to connect PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	/* mask with MAC supported features */
	अगर (mdp->cd->रेजिस्टर_type != SH_ETH_REG_GIGABIT) अणु
		पूर्णांक err = phy_set_max_speed(phydev, SPEED_100);
		अगर (err) अणु
			netdev_err(ndev, "failed to limit PHY to 100 Mbit/s\n");
			phy_disconnect(phydev);
			वापस err;
		पूर्ण
	पूर्ण

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

/* PHY control start function */
अटल पूर्णांक sh_eth_phy_start(काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;

	ret = sh_eth_phy_init(ndev);
	अगर (ret)
		वापस ret;

	phy_start(ndev->phydev);

	वापस 0;
पूर्ण

/* If it is ever necessary to increase SH_ETH_REG_DUMP_MAX_REGS, the
 * version must be bumped as well.  Just adding रेजिस्टरs up to that
 * limit is fine, as दीर्घ as the existing रेजिस्टर indices करोn't
 * change.
 */
#घोषणा SH_ETH_REG_DUMP_VERSION		1
#घोषणा SH_ETH_REG_DUMP_MAX_REGS	256

अटल माप_प्रकार __sh_eth_get_regs(काष्ठा net_device *ndev, u32 *buf)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा sh_eth_cpu_data *cd = mdp->cd;
	u32 *valid_map;
	माप_प्रकार len;

	BUILD_BUG_ON(SH_ETH_MAX_REGISTER_OFFSET > SH_ETH_REG_DUMP_MAX_REGS);

	/* Dump starts with a biपंचांगap that tells ethtool which
	 * रेजिस्टरs are defined क्रम this chip.
	 */
	len = DIV_ROUND_UP(SH_ETH_REG_DUMP_MAX_REGS, 32);
	अगर (buf) अणु
		valid_map = buf;
		buf += len;
	पूर्ण अन्यथा अणु
		valid_map = शून्य;
	पूर्ण

	/* Add a रेजिस्टर to the dump, अगर it has a defined offset.
	 * This स्वतःmatically skips most undefined रेजिस्टरs, but क्रम
	 * some it is also necessary to check a capability flag in
	 * काष्ठा sh_eth_cpu_data.
	 */
#घोषणा mark_reg_valid(reg) valid_map[reg / 32] |= 1U << (reg % 32)
#घोषणा add_reg_from(reg, पढ़ो_expr) करो अणु				\
		अगर (mdp->reg_offset[reg] != SH_ETH_OFFSET_INVALID) अणु	\
			अगर (buf) अणु					\
				mark_reg_valid(reg);			\
				*buf++ = पढ़ो_expr;			\
			पूर्ण						\
			++len;						\
		पूर्ण							\
	पूर्ण जबतक (0)
#घोषणा add_reg(reg) add_reg_from(reg, sh_eth_पढ़ो(ndev, reg))
#घोषणा add_tsu_reg(reg) add_reg_from(reg, sh_eth_tsu_पढ़ो(mdp, reg))

	add_reg(EDSR);
	add_reg(EDMR);
	add_reg(EDTRR);
	add_reg(EDRRR);
	add_reg(EESR);
	add_reg(EESIPR);
	add_reg(TDLAR);
	अगर (!cd->no_xdfar)
		add_reg(TDFAR);
	add_reg(TDFXR);
	add_reg(TDFFR);
	add_reg(RDLAR);
	अगर (!cd->no_xdfar)
		add_reg(RDFAR);
	add_reg(RDFXR);
	add_reg(RDFFR);
	add_reg(TRSCER);
	add_reg(RMFCR);
	add_reg(TFTR);
	add_reg(FDR);
	add_reg(RMCR);
	add_reg(TFUCR);
	add_reg(RFOCR);
	अगर (cd->rmiimode)
		add_reg(RMIIMODE);
	add_reg(FCFTR);
	अगर (cd->rpadir)
		add_reg(RPAसूची);
	अगर (!cd->no_trimd)
		add_reg(TRIMD);
	add_reg(ECMR);
	add_reg(ECSR);
	add_reg(ECSIPR);
	add_reg(PIR);
	अगर (!cd->no_psr)
		add_reg(PSR);
	add_reg(RDMLR);
	add_reg(RFLR);
	add_reg(IPGR);
	अगर (cd->apr)
		add_reg(APR);
	अगर (cd->mpr)
		add_reg(MPR);
	add_reg(RFCR);
	add_reg(RFCF);
	अगर (cd->tछोड़ोr)
		add_reg(TPAUSER);
	add_reg(TPAUSECR);
	अगर (cd->gecmr)
		add_reg(GECMR);
	अगर (cd->bculr)
		add_reg(BCULR);
	add_reg(MAHR);
	add_reg(MALR);
	अगर (!cd->no_tx_cntrs) अणु
		add_reg(TROCR);
		add_reg(CDCR);
		add_reg(LCCR);
		add_reg(CNDCR);
	पूर्ण
	add_reg(CEFCR);
	add_reg(FRECR);
	add_reg(TSFRCR);
	add_reg(TLFRCR);
	अगर (cd->cexcr) अणु
		add_reg(CERCR);
		add_reg(CEECR);
	पूर्ण
	add_reg(MAFCR);
	अगर (cd->rtrate)
		add_reg(RTRATE);
	अगर (cd->csmr)
		add_reg(CSMR);
	अगर (cd->select_mii)
		add_reg(RMII_MII);
	अगर (cd->tsu) अणु
		add_tsu_reg(ARSTR);
		add_tsu_reg(TSU_CTRST);
		अगर (cd->dual_port) अणु
			add_tsu_reg(TSU_FWEN0);
			add_tsu_reg(TSU_FWEN1);
			add_tsu_reg(TSU_FCM);
			add_tsu_reg(TSU_BSYSL0);
			add_tsu_reg(TSU_BSYSL1);
			add_tsu_reg(TSU_PRISL0);
			add_tsu_reg(TSU_PRISL1);
			add_tsu_reg(TSU_FWSL0);
			add_tsu_reg(TSU_FWSL1);
		पूर्ण
		add_tsu_reg(TSU_FWSLC);
		अगर (cd->dual_port) अणु
			add_tsu_reg(TSU_QTAGM0);
			add_tsu_reg(TSU_QTAGM1);
			add_tsu_reg(TSU_FWSR);
			add_tsu_reg(TSU_FWINMK);
			add_tsu_reg(TSU_ADQT0);
			add_tsu_reg(TSU_ADQT1);
			add_tsu_reg(TSU_VTAG0);
			add_tsu_reg(TSU_VTAG1);
		पूर्ण
		add_tsu_reg(TSU_ADSBSY);
		add_tsu_reg(TSU_TEN);
		add_tsu_reg(TSU_POST1);
		add_tsu_reg(TSU_POST2);
		add_tsu_reg(TSU_POST3);
		add_tsu_reg(TSU_POST4);
		/* This is the start of a table, not just a single रेजिस्टर. */
		अगर (buf) अणु
			अचिन्हित पूर्णांक i;

			mark_reg_valid(TSU_ADRH0);
			क्रम (i = 0; i < SH_ETH_TSU_CAM_ENTRIES * 2; i++)
				*buf++ = ioपढ़ो32(mdp->tsu_addr +
						  mdp->reg_offset[TSU_ADRH0] +
						  i * 4);
		पूर्ण
		len += SH_ETH_TSU_CAM_ENTRIES * 2;
	पूर्ण

#अघोषित mark_reg_valid
#अघोषित add_reg_from
#अघोषित add_reg
#अघोषित add_tsu_reg

	वापस len * 4;
पूर्ण

अटल पूर्णांक sh_eth_get_regs_len(काष्ठा net_device *ndev)
अणु
	वापस __sh_eth_get_regs(ndev, शून्य);
पूर्ण

अटल व्योम sh_eth_get_regs(काष्ठा net_device *ndev, काष्ठा ethtool_regs *regs,
			    व्योम *buf)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	regs->version = SH_ETH_REG_DUMP_VERSION;

	pm_runसमय_get_sync(&mdp->pdev->dev);
	__sh_eth_get_regs(ndev, buf);
	pm_runसमय_put_sync(&mdp->pdev->dev);
पूर्ण

अटल u32 sh_eth_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	वापस mdp->msg_enable;
पूर्ण

अटल व्योम sh_eth_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	mdp->msg_enable = value;
पूर्ण

अटल स्थिर अक्षर sh_eth_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"rx_current", "tx_current",
	"rx_dirty", "tx_dirty",
पूर्ण;
#घोषणा SH_ETH_STATS_LEN  ARRAY_SIZE(sh_eth_gstrings_stats)

अटल पूर्णांक sh_eth_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस SH_ETH_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम sh_eth_get_ethtool_stats(काष्ठा net_device *ndev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक i = 0;

	/* device-specअगरic stats */
	data[i++] = mdp->cur_rx;
	data[i++] = mdp->cur_tx;
	data[i++] = mdp->dirty_rx;
	data[i++] = mdp->dirty_tx;
पूर्ण

अटल व्योम sh_eth_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, sh_eth_gstrings_stats,
		       माप(sh_eth_gstrings_stats));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sh_eth_get_ringparam(काष्ठा net_device *ndev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	ring->rx_max_pending = RX_RING_MAX;
	ring->tx_max_pending = TX_RING_MAX;
	ring->rx_pending = mdp->num_rx_ring;
	ring->tx_pending = mdp->num_tx_ring;
पूर्ण

अटल पूर्णांक sh_eth_set_ringparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (ring->tx_pending > TX_RING_MAX ||
	    ring->rx_pending > RX_RING_MAX ||
	    ring->tx_pending < TX_RING_MIN ||
	    ring->rx_pending < RX_RING_MIN)
		वापस -EINVAL;
	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	अगर (netअगर_running(ndev)) अणु
		netअगर_device_detach(ndev);
		netअगर_tx_disable(ndev);

		/* Serialise with the पूर्णांकerrupt handler and NAPI, then
		 * disable पूर्णांकerrupts.  We have to clear the
		 * irq_enabled flag first to ensure that पूर्णांकerrupts
		 * won't be re-enabled.
		 */
		mdp->irq_enabled = false;
		synchronize_irq(ndev->irq);
		napi_synchronize(&mdp->napi);
		sh_eth_ग_लिखो(ndev, 0x0000, EESIPR);

		sh_eth_dev_निकास(ndev);

		/* Free all the skbuffs in the Rx queue and the DMA buffers. */
		sh_eth_ring_मुक्त(ndev);
	पूर्ण

	/* Set new parameters */
	mdp->num_rx_ring = ring->rx_pending;
	mdp->num_tx_ring = ring->tx_pending;

	अगर (netअगर_running(ndev)) अणु
		ret = sh_eth_ring_init(ndev);
		अगर (ret < 0) अणु
			netdev_err(ndev, "%s: sh_eth_ring_init failed.\n",
				   __func__);
			वापस ret;
		पूर्ण
		ret = sh_eth_dev_init(ndev);
		अगर (ret < 0) अणु
			netdev_err(ndev, "%s: sh_eth_dev_init failed.\n",
				   __func__);
			वापस ret;
		पूर्ण

		netअगर_device_attach(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sh_eth_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (mdp->cd->magic) अणु
		wol->supported = WAKE_MAGIC;
		wol->wolopts = mdp->wol_enabled ? WAKE_MAGIC : 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_eth_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	अगर (!mdp->cd->magic || wol->wolopts & ~WAKE_MAGIC)
		वापस -EOPNOTSUPP;

	mdp->wol_enabled = !!(wol->wolopts & WAKE_MAGIC);

	device_set_wakeup_enable(&mdp->pdev->dev, mdp->wol_enabled);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sh_eth_ethtool_ops = अणु
	.get_regs_len	= sh_eth_get_regs_len,
	.get_regs	= sh_eth_get_regs,
	.nway_reset	= phy_ethtool_nway_reset,
	.get_msglevel	= sh_eth_get_msglevel,
	.set_msglevel	= sh_eth_set_msglevel,
	.get_link	= ethtool_op_get_link,
	.get_strings	= sh_eth_get_strings,
	.get_ethtool_stats  = sh_eth_get_ethtool_stats,
	.get_sset_count     = sh_eth_get_sset_count,
	.get_ringparam	= sh_eth_get_ringparam,
	.set_ringparam	= sh_eth_set_ringparam,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
	.get_wol	= sh_eth_get_wol,
	.set_wol	= sh_eth_set_wol,
पूर्ण;

/* network device खोलो function */
अटल पूर्णांक sh_eth_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret;

	pm_runसमय_get_sync(&mdp->pdev->dev);

	napi_enable(&mdp->napi);

	ret = request_irq(ndev->irq, sh_eth_पूर्णांकerrupt,
			  mdp->cd->irq_flags, ndev->name, ndev);
	अगर (ret) अणु
		netdev_err(ndev, "Can not assign IRQ number\n");
		जाओ out_napi_off;
	पूर्ण

	/* Descriptor set */
	ret = sh_eth_ring_init(ndev);
	अगर (ret)
		जाओ out_मुक्त_irq;

	/* device init */
	ret = sh_eth_dev_init(ndev);
	अगर (ret)
		जाओ out_मुक्त_irq;

	/* PHY control start*/
	ret = sh_eth_phy_start(ndev);
	अगर (ret)
		जाओ out_मुक्त_irq;

	netअगर_start_queue(ndev);

	mdp->is_खोलोed = 1;

	वापस ret;

out_मुक्त_irq:
	मुक्त_irq(ndev->irq, ndev);
out_napi_off:
	napi_disable(&mdp->napi);
	pm_runसमय_put_sync(&mdp->pdev->dev);
	वापस ret;
पूर्ण

/* Timeout function */
अटल व्योम sh_eth_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा sh_eth_rxdesc *rxdesc;
	पूर्णांक i;

	netअगर_stop_queue(ndev);

	netअगर_err(mdp, समयr, ndev,
		  "transmit timed out, status %8.8x, resetting...\n",
		  sh_eth_पढ़ो(ndev, EESR));

	/* tx_errors count up */
	ndev->stats.tx_errors++;

	/* Free all the skbuffs in the Rx queue. */
	क्रम (i = 0; i < mdp->num_rx_ring; i++) अणु
		rxdesc = &mdp->rx_ring[i];
		rxdesc->status = cpu_to_le32(0);
		rxdesc->addr = cpu_to_le32(0xBADF00D0);
		dev_kमुक्त_skb(mdp->rx_skbuff[i]);
		mdp->rx_skbuff[i] = शून्य;
	पूर्ण
	क्रम (i = 0; i < mdp->num_tx_ring; i++) अणु
		dev_kमुक्त_skb(mdp->tx_skbuff[i]);
		mdp->tx_skbuff[i] = शून्य;
	पूर्ण

	/* device init */
	sh_eth_dev_init(ndev);

	netअगर_start_queue(ndev);
पूर्ण

/* Packet transmit function */
अटल netdev_tx_t sh_eth_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	काष्ठा sh_eth_txdesc *txdesc;
	dma_addr_t dma_addr;
	u32 entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdp->lock, flags);
	अगर ((mdp->cur_tx - mdp->dirty_tx) >= (mdp->num_tx_ring - 4)) अणु
		अगर (!sh_eth_tx_मुक्त(ndev, true)) अणु
			netअगर_warn(mdp, tx_queued, ndev, "TxFD exhausted.\n");
			netअगर_stop_queue(ndev);
			spin_unlock_irqrestore(&mdp->lock, flags);
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mdp->lock, flags);

	अगर (skb_put_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;

	entry = mdp->cur_tx % mdp->num_tx_ring;
	mdp->tx_skbuff[entry] = skb;
	txdesc = &mdp->tx_ring[entry];
	/* soft swap. */
	अगर (!mdp->cd->hw_swap)
		sh_eth_soft_swap(PTR_ALIGN(skb->data, 4), skb->len + 2);
	dma_addr = dma_map_single(&mdp->pdev->dev, skb->data, skb->len,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(&mdp->pdev->dev, dma_addr)) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	txdesc->addr = cpu_to_le32(dma_addr);
	txdesc->len  = cpu_to_le32(skb->len << 16);

	dma_wmb(); /* TACT bit must be set after all the above ग_लिखोs */
	अगर (entry >= mdp->num_tx_ring - 1)
		txdesc->status |= cpu_to_le32(TD_TACT | TD_TDLE);
	अन्यथा
		txdesc->status |= cpu_to_le32(TD_TACT);

	mdp->cur_tx++;

	अगर (!(sh_eth_पढ़ो(ndev, EDTRR) & mdp->cd->edtrr_trns))
		sh_eth_ग_लिखो(ndev, mdp->cd->edtrr_trns, EDTRR);

	वापस NETDEV_TX_OK;
पूर्ण

/* The statistics रेजिस्टरs have ग_लिखो-clear behaviour, which means we
 * will lose any increment between the पढ़ो and ग_लिखो.  We mitigate
 * this by only clearing when we पढ़ो a non-zero value, so we will
 * never falsely report a total of zero.
 */
अटल व्योम
sh_eth_update_stat(काष्ठा net_device *ndev, अचिन्हित दीर्घ *stat, पूर्णांक reg)
अणु
	u32 delta = sh_eth_पढ़ो(ndev, reg);

	अगर (delta) अणु
		*stat += delta;
		sh_eth_ग_लिखो(ndev, 0, reg);
	पूर्ण
पूर्ण

अटल काष्ठा net_device_stats *sh_eth_get_stats(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	अगर (mdp->cd->no_tx_cntrs)
		वापस &ndev->stats;

	अगर (!mdp->is_खोलोed)
		वापस &ndev->stats;

	sh_eth_update_stat(ndev, &ndev->stats.tx_dropped, TROCR);
	sh_eth_update_stat(ndev, &ndev->stats.collisions, CDCR);
	sh_eth_update_stat(ndev, &ndev->stats.tx_carrier_errors, LCCR);

	अगर (mdp->cd->cexcr) अणु
		sh_eth_update_stat(ndev, &ndev->stats.tx_carrier_errors,
				   CERCR);
		sh_eth_update_stat(ndev, &ndev->stats.tx_carrier_errors,
				   CEECR);
	पूर्ण अन्यथा अणु
		sh_eth_update_stat(ndev, &ndev->stats.tx_carrier_errors,
				   CNDCR);
	पूर्ण

	वापस &ndev->stats;
पूर्ण

/* device बंद function */
अटल पूर्णांक sh_eth_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	netअगर_stop_queue(ndev);

	/* Serialise with the पूर्णांकerrupt handler and NAPI, then disable
	 * पूर्णांकerrupts.  We have to clear the irq_enabled flag first to
	 * ensure that पूर्णांकerrupts won't be re-enabled.
	 */
	mdp->irq_enabled = false;
	synchronize_irq(ndev->irq);
	napi_disable(&mdp->napi);
	sh_eth_ग_लिखो(ndev, 0x0000, EESIPR);

	sh_eth_dev_निकास(ndev);

	/* PHY Disconnect */
	अगर (ndev->phydev) अणु
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	पूर्ण

	मुक्त_irq(ndev->irq, ndev);

	/* Free all the skbuffs in the Rx queue and the DMA buffer. */
	sh_eth_ring_मुक्त(ndev);

	mdp->is_खोलोed = 0;

	pm_runसमय_put(&mdp->pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	ndev->mtu = new_mtu;
	netdev_update_features(ndev);

	वापस 0;
पूर्ण

/* For TSU_POSTn. Please refer to the manual about this (strange) bitfields */
अटल u32 sh_eth_tsu_get_post_mask(पूर्णांक entry)
अणु
	वापस 0x0f << (28 - ((entry % 8) * 4));
पूर्ण

अटल u32 sh_eth_tsu_get_post_bit(काष्ठा sh_eth_निजी *mdp, पूर्णांक entry)
अणु
	वापस (0x08 >> (mdp->port << 1)) << (28 - ((entry % 8) * 4));
पूर्ण

अटल व्योम sh_eth_tsu_enable_cam_entry_post(काष्ठा net_device *ndev,
					     पूर्णांक entry)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक reg = TSU_POST1 + entry / 8;
	u32 पंचांगp;

	पंचांगp = sh_eth_tsu_पढ़ो(mdp, reg);
	sh_eth_tsu_ग_लिखो(mdp, पंचांगp | sh_eth_tsu_get_post_bit(mdp, entry), reg);
पूर्ण

अटल bool sh_eth_tsu_disable_cam_entry_post(काष्ठा net_device *ndev,
					      पूर्णांक entry)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक reg = TSU_POST1 + entry / 8;
	u32 post_mask, ref_mask, पंचांगp;

	post_mask = sh_eth_tsu_get_post_mask(entry);
	ref_mask = sh_eth_tsu_get_post_bit(mdp, entry) & ~post_mask;

	पंचांगp = sh_eth_tsu_पढ़ो(mdp, reg);
	sh_eth_tsu_ग_लिखो(mdp, पंचांगp & ~post_mask, reg);

	/* If other port enables, the function वापसs "true" */
	वापस पंचांगp & ref_mask;
पूर्ण

अटल पूर्णांक sh_eth_tsu_busy(काष्ठा net_device *ndev)
अणु
	पूर्णांक समयout = SH_ETH_TSU_TIMEOUT_MS * 100;
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	जबतक ((sh_eth_tsu_पढ़ो(mdp, TSU_ADSBSY) & TSU_ADSBSY_0)) अणु
		udelay(10);
		समयout--;
		अगर (समयout <= 0) अणु
			netdev_err(ndev, "%s: timeout\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_tsu_ग_लिखो_entry(काष्ठा net_device *ndev, u16 offset,
				  स्थिर u8 *addr)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u32 val;

	val = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
	ioग_लिखो32(val, mdp->tsu_addr + offset);
	अगर (sh_eth_tsu_busy(ndev) < 0)
		वापस -EBUSY;

	val = addr[4] << 8 | addr[5];
	ioग_लिखो32(val, mdp->tsu_addr + offset + 4);
	अगर (sh_eth_tsu_busy(ndev) < 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम sh_eth_tsu_पढ़ो_entry(काष्ठा net_device *ndev, u16 offset, u8 *addr)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u32 val;

	val = ioपढ़ो32(mdp->tsu_addr + offset);
	addr[0] = (val >> 24) & 0xff;
	addr[1] = (val >> 16) & 0xff;
	addr[2] = (val >> 8) & 0xff;
	addr[3] = val & 0xff;
	val = ioपढ़ो32(mdp->tsu_addr + offset + 4);
	addr[4] = (val >> 8) & 0xff;
	addr[5] = val & 0xff;
पूर्ण


अटल पूर्णांक sh_eth_tsu_find_entry(काष्ठा net_device *ndev, स्थिर u8 *addr)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	पूर्णांक i;
	u8 c_addr[ETH_ALEN];

	क्रम (i = 0; i < SH_ETH_TSU_CAM_ENTRIES; i++, reg_offset += 8) अणु
		sh_eth_tsu_पढ़ो_entry(ndev, reg_offset, c_addr);
		अगर (ether_addr_equal(addr, c_addr))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक sh_eth_tsu_find_empty(काष्ठा net_device *ndev)
अणु
	u8 blank[ETH_ALEN];
	पूर्णांक entry;

	स_रखो(blank, 0, माप(blank));
	entry = sh_eth_tsu_find_entry(ndev, blank);
	वापस (entry < 0) ? -ENOMEM : entry;
पूर्ण

अटल पूर्णांक sh_eth_tsu_disable_cam_entry_table(काष्ठा net_device *ndev,
					      पूर्णांक entry)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	पूर्णांक ret;
	u8 blank[ETH_ALEN];

	sh_eth_tsu_ग_लिखो(mdp, sh_eth_tsu_पढ़ो(mdp, TSU_TEN) &
			 ~(1 << (31 - entry)), TSU_TEN);

	स_रखो(blank, 0, माप(blank));
	ret = sh_eth_tsu_ग_लिखो_entry(ndev, reg_offset + entry * 8, blank);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_tsu_add_entry(काष्ठा net_device *ndev, स्थिर u8 *addr)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	पूर्णांक i, ret;

	अगर (!mdp->cd->tsu)
		वापस 0;

	i = sh_eth_tsu_find_entry(ndev, addr);
	अगर (i < 0) अणु
		/* No entry found, create one */
		i = sh_eth_tsu_find_empty(ndev);
		अगर (i < 0)
			वापस -ENOMEM;
		ret = sh_eth_tsu_ग_लिखो_entry(ndev, reg_offset + i * 8, addr);
		अगर (ret < 0)
			वापस ret;

		/* Enable the entry */
		sh_eth_tsu_ग_लिखो(mdp, sh_eth_tsu_पढ़ो(mdp, TSU_TEN) |
				 (1 << (31 - i)), TSU_TEN);
	पूर्ण

	/* Entry found or created, enable POST */
	sh_eth_tsu_enable_cam_entry_post(ndev, i);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_tsu_del_entry(काष्ठा net_device *ndev, स्थिर u8 *addr)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक i, ret;

	अगर (!mdp->cd->tsu)
		वापस 0;

	i = sh_eth_tsu_find_entry(ndev, addr);
	अगर (i) अणु
		/* Entry found */
		अगर (sh_eth_tsu_disable_cam_entry_post(ndev, i))
			जाओ करोne;

		/* Disable the entry अगर both ports was disabled */
		ret = sh_eth_tsu_disable_cam_entry_table(ndev, i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
करोne:
	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_tsu_purge_all(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक i, ret;

	अगर (!mdp->cd->tsu)
		वापस 0;

	क्रम (i = 0; i < SH_ETH_TSU_CAM_ENTRIES; i++) अणु
		अगर (sh_eth_tsu_disable_cam_entry_post(ndev, i))
			जारी;

		/* Disable the entry अगर both ports was disabled */
		ret = sh_eth_tsu_disable_cam_entry_table(ndev, i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sh_eth_tsu_purge_mcast(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u16 reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	u8 addr[ETH_ALEN];
	पूर्णांक i;

	अगर (!mdp->cd->tsu)
		वापस;

	क्रम (i = 0; i < SH_ETH_TSU_CAM_ENTRIES; i++, reg_offset += 8) अणु
		sh_eth_tsu_पढ़ो_entry(ndev, reg_offset, addr);
		अगर (is_multicast_ether_addr(addr))
			sh_eth_tsu_del_entry(ndev, addr);
	पूर्ण
पूर्ण

/* Update promiscuous flag and multicast filter */
अटल व्योम sh_eth_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	u32 ecmr_bits;
	पूर्णांक mcast_all = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdp->lock, flags);
	/* Initial condition is MCT = 1, PRM = 0.
	 * Depending on ndev->flags, set PRM or clear MCT
	 */
	ecmr_bits = sh_eth_पढ़ो(ndev, ECMR) & ~ECMR_PRM;
	अगर (mdp->cd->tsu)
		ecmr_bits |= ECMR_MCT;

	अगर (!(ndev->flags & IFF_MULTICAST)) अणु
		sh_eth_tsu_purge_mcast(ndev);
		mcast_all = 1;
	पूर्ण
	अगर (ndev->flags & IFF_ALLMULTI) अणु
		sh_eth_tsu_purge_mcast(ndev);
		ecmr_bits &= ~ECMR_MCT;
		mcast_all = 1;
	पूर्ण

	अगर (ndev->flags & IFF_PROMISC) अणु
		sh_eth_tsu_purge_all(ndev);
		ecmr_bits = (ecmr_bits & ~ECMR_MCT) | ECMR_PRM;
	पूर्ण अन्यथा अगर (mdp->cd->tsu) अणु
		काष्ठा netdev_hw_addr *ha;
		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			अगर (mcast_all && is_multicast_ether_addr(ha->addr))
				जारी;

			अगर (sh_eth_tsu_add_entry(ndev, ha->addr) < 0) अणु
				अगर (!mcast_all) अणु
					sh_eth_tsu_purge_mcast(ndev);
					ecmr_bits &= ~ECMR_MCT;
					mcast_all = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* update the ethernet mode */
	sh_eth_ग_लिखो(ndev, ecmr_bits, ECMR);

	spin_unlock_irqrestore(&mdp->lock, flags);
पूर्ण

अटल व्योम sh_eth_set_rx_csum(काष्ठा net_device *ndev, bool enable)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdp->lock, flags);

	/* Disable TX and RX */
	sh_eth_rcv_snd_disable(ndev);

	/* Modअगरy RX Checksum setting */
	sh_eth_modअगरy(ndev, ECMR, ECMR_RCSC, enable ? ECMR_RCSC : 0);

	/* Enable TX and RX */
	sh_eth_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&mdp->lock, flags);
पूर्ण

अटल पूर्णांक sh_eth_set_features(काष्ठा net_device *ndev,
			       netdev_features_t features)
अणु
	netdev_features_t changed = ndev->features ^ features;
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	अगर (changed & NETIF_F_RXCSUM && mdp->cd->rx_csum)
		sh_eth_set_rx_csum(ndev, features & NETIF_F_RXCSUM);

	ndev->features = features;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_get_vtag_index(काष्ठा sh_eth_निजी *mdp)
अणु
	अगर (!mdp->port)
		वापस TSU_VTAG0;
	अन्यथा
		वापस TSU_VTAG1;
पूर्ण

अटल पूर्णांक sh_eth_vlan_rx_add_vid(काष्ठा net_device *ndev,
				  __be16 proto, u16 vid)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक vtag_reg_index = sh_eth_get_vtag_index(mdp);

	अगर (unlikely(!mdp->cd->tsu))
		वापस -EPERM;

	/* No filtering अगर vid = 0 */
	अगर (!vid)
		वापस 0;

	mdp->vlan_num_ids++;

	/* The controller has one VLAN tag HW filter. So, अगर the filter is
	 * alपढ़ोy enabled, the driver disables it and the filte
	 */
	अगर (mdp->vlan_num_ids > 1) अणु
		/* disable VLAN filter */
		sh_eth_tsu_ग_लिखो(mdp, 0, vtag_reg_index);
		वापस 0;
	पूर्ण

	sh_eth_tsu_ग_लिखो(mdp, TSU_VTAG_ENABLE | (vid & TSU_VTAG_VID_MASK),
			 vtag_reg_index);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_eth_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक vtag_reg_index = sh_eth_get_vtag_index(mdp);

	अगर (unlikely(!mdp->cd->tsu))
		वापस -EPERM;

	/* No filtering अगर vid = 0 */
	अगर (!vid)
		वापस 0;

	mdp->vlan_num_ids--;
	sh_eth_tsu_ग_लिखो(mdp, 0, vtag_reg_index);

	वापस 0;
पूर्ण

/* SuperH's TSU रेजिस्टर init function */
अटल व्योम sh_eth_tsu_init(काष्ठा sh_eth_निजी *mdp)
अणु
	अगर (!mdp->cd->dual_port) अणु
		sh_eth_tsu_ग_लिखो(mdp, 0, TSU_TEN); /* Disable all CAM entry */
		sh_eth_tsu_ग_लिखो(mdp, TSU_FWSLC_POSTENU | TSU_FWSLC_POSTENL,
				 TSU_FWSLC);	/* Enable POST रेजिस्टरs */
		वापस;
	पूर्ण

	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FWEN0);	/* Disable क्रमward(0->1) */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FWEN1);	/* Disable क्रमward(1->0) */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FCM);	/* क्रमward fअगरo 3k-3k */
	sh_eth_tsu_ग_लिखो(mdp, 0xc, TSU_BSYSL0);
	sh_eth_tsu_ग_लिखो(mdp, 0xc, TSU_BSYSL1);
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_PRISL0);
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_PRISL1);
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FWSL0);
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FWSL1);
	sh_eth_tsu_ग_लिखो(mdp, TSU_FWSLC_POSTENU | TSU_FWSLC_POSTENL, TSU_FWSLC);
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_QTAGM0);	/* Disable QTAG(0->1) */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_QTAGM1);	/* Disable QTAG(1->0) */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FWSR);	/* all पूर्णांकerrupt status clear */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_FWINMK);	/* Disable all पूर्णांकerrupt */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_TEN);	/* Disable all CAM entry */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_POST1);	/* Disable CAM entry [ 0- 7] */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_POST2);	/* Disable CAM entry [ 8-15] */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_POST3);	/* Disable CAM entry [16-23] */
	sh_eth_tsu_ग_लिखो(mdp, 0, TSU_POST4);	/* Disable CAM entry [24-31] */
पूर्ण

/* MDIO bus release function */
अटल पूर्णांक sh_mdio_release(काष्ठा sh_eth_निजी *mdp)
अणु
	/* unरेजिस्टर mdio bus */
	mdiobus_unरेजिस्टर(mdp->mii_bus);

	/* मुक्त bitbang info */
	मुक्त_mdio_bitbang(mdp->mii_bus);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mdiobb_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg)
अणु
	पूर्णांक res;

	pm_runसमय_get_sync(bus->parent);
	res = mdiobb_पढ़ो(bus, phy, reg);
	pm_runसमय_put(bus->parent);

	वापस res;
पूर्ण

अटल पूर्णांक sh_mdiobb_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	पूर्णांक res;

	pm_runसमय_get_sync(bus->parent);
	res = mdiobb_ग_लिखो(bus, phy, reg, val);
	pm_runसमय_put(bus->parent);

	वापस res;
पूर्ण

/* MDIO bus init function */
अटल पूर्णांक sh_mdio_init(काष्ठा sh_eth_निजी *mdp,
			काष्ठा sh_eth_plat_data *pd)
अणु
	पूर्णांक ret;
	काष्ठा bb_info *bitbang;
	काष्ठा platक्रमm_device *pdev = mdp->pdev;
	काष्ठा device *dev = &mdp->pdev->dev;

	/* create bit control काष्ठा क्रम PHY */
	bitbang = devm_kzalloc(dev, माप(काष्ठा bb_info), GFP_KERNEL);
	अगर (!bitbang)
		वापस -ENOMEM;

	/* bitbang init */
	bitbang->addr = mdp->addr + mdp->reg_offset[PIR];
	bitbang->set_gate = pd->set_mdio_gate;
	bitbang->ctrl.ops = &bb_ops;

	/* MII controller setting */
	mdp->mii_bus = alloc_mdio_bitbang(&bitbang->ctrl);
	अगर (!mdp->mii_bus)
		वापस -ENOMEM;

	/* Wrap accessors with Runसमय PM-aware ops */
	mdp->mii_bus->पढ़ो = sh_mdiobb_पढ़ो;
	mdp->mii_bus->ग_लिखो = sh_mdiobb_ग_लिखो;

	/* Hook up MII support क्रम ethtool */
	mdp->mii_bus->name = "sh_mii";
	mdp->mii_bus->parent = dev;
	snम_लिखो(mdp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	/* रेजिस्टर MDIO bus */
	अगर (pd->phy_irq > 0)
		mdp->mii_bus->irq[pd->phy] = pd->phy_irq;

	ret = of_mdiobus_रेजिस्टर(mdp->mii_bus, dev->of_node);
	अगर (ret)
		जाओ out_मुक्त_bus;

	वापस 0;

out_मुक्त_bus:
	मुक्त_mdio_bitbang(mdp->mii_bus);
	वापस ret;
पूर्ण

अटल स्थिर u16 *sh_eth_get_रेजिस्टर_offset(पूर्णांक रेजिस्टर_type)
अणु
	स्थिर u16 *reg_offset = शून्य;

	चयन (रेजिस्टर_type) अणु
	हाल SH_ETH_REG_GIGABIT:
		reg_offset = sh_eth_offset_gigabit;
		अवरोध;
	हाल SH_ETH_REG_FAST_RCAR:
		reg_offset = sh_eth_offset_fast_rcar;
		अवरोध;
	हाल SH_ETH_REG_FAST_SH4:
		reg_offset = sh_eth_offset_fast_sh4;
		अवरोध;
	हाल SH_ETH_REG_FAST_SH3_SH2:
		reg_offset = sh_eth_offset_fast_sh3_sh2;
		अवरोध;
	पूर्ण

	वापस reg_offset;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sh_eth_netdev_ops = अणु
	.nकरो_खोलो		= sh_eth_खोलो,
	.nकरो_stop		= sh_eth_बंद,
	.nकरो_start_xmit		= sh_eth_start_xmit,
	.nकरो_get_stats		= sh_eth_get_stats,
	.nकरो_set_rx_mode	= sh_eth_set_rx_mode,
	.nकरो_tx_समयout		= sh_eth_tx_समयout,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_change_mtu		= sh_eth_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_set_features	= sh_eth_set_features,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops sh_eth_netdev_ops_tsu = अणु
	.nकरो_खोलो		= sh_eth_खोलो,
	.nकरो_stop		= sh_eth_बंद,
	.nकरो_start_xmit		= sh_eth_start_xmit,
	.nकरो_get_stats		= sh_eth_get_stats,
	.nकरो_set_rx_mode	= sh_eth_set_rx_mode,
	.nकरो_vlan_rx_add_vid	= sh_eth_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= sh_eth_vlan_rx_समाप्त_vid,
	.nकरो_tx_समयout		= sh_eth_tx_समयout,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_change_mtu		= sh_eth_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_set_features	= sh_eth_set_features,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा sh_eth_plat_data *sh_eth_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sh_eth_plat_data *pdata;
	phy_पूर्णांकerface_t पूर्णांकerface;
	पूर्णांक ret;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	ret = of_get_phy_mode(np, &पूर्णांकerface);
	अगर (ret)
		वापस शून्य;
	pdata->phy_पूर्णांकerface = पूर्णांकerface;

	of_get_mac_address(np, pdata->mac_addr);

	pdata->no_ether_link =
		of_property_पढ़ो_bool(np, "renesas,no-ether-link");
	pdata->ether_link_active_low =
		of_property_पढ़ो_bool(np, "renesas,ether-link-active-low");

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id sh_eth_match_table[] = अणु
	अणु .compatible = "renesas,gether-r8a7740", .data = &r8a7740_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7743", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7745", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7778", .data = &rcar_gen1_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7779", .data = &rcar_gen1_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7790", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7791", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7793", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,ether-r8a7794", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,gether-r8a77980", .data = &r8a77980_data पूर्ण,
	अणु .compatible = "renesas,ether-r7s72100", .data = &r7s72100_data पूर्ण,
	अणु .compatible = "renesas,ether-r7s9210", .data = &r7s9210_data पूर्ण,
	अणु .compatible = "renesas,rcar-gen1-ether", .data = &rcar_gen1_data पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-ether", .data = &rcar_gen2_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_eth_match_table);
#अन्यथा
अटल अंतरभूत काष्ठा sh_eth_plat_data *sh_eth_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sh_eth_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा sh_eth_plat_data *pd = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	काष्ठा sh_eth_निजी *mdp;
	काष्ठा net_device *ndev;
	पूर्णांक ret;

	/* get base addr */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	ndev = alloc_etherdev(माप(काष्ठा sh_eth_निजी));
	अगर (!ndev)
		वापस -ENOMEM;

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ out_release;
	ndev->irq = ret;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	mdp = netdev_priv(ndev);
	mdp->num_tx_ring = TX_RING_SIZE;
	mdp->num_rx_ring = RX_RING_SIZE;
	mdp->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mdp->addr)) अणु
		ret = PTR_ERR(mdp->addr);
		जाओ out_release;
	पूर्ण

	ndev->base_addr = res->start;

	spin_lock_init(&mdp->lock);
	mdp->pdev = pdev;

	अगर (pdev->dev.of_node)
		pd = sh_eth_parse_dt(&pdev->dev);
	अगर (!pd) अणु
		dev_err(&pdev->dev, "no platform data\n");
		ret = -EINVAL;
		जाओ out_release;
	पूर्ण

	/* get PHY ID */
	mdp->phy_id = pd->phy;
	mdp->phy_पूर्णांकerface = pd->phy_पूर्णांकerface;
	mdp->no_ether_link = pd->no_ether_link;
	mdp->ether_link_active_low = pd->ether_link_active_low;

	/* set cpu data */
	अगर (id)
		mdp->cd = (काष्ठा sh_eth_cpu_data *)id->driver_data;
	अन्यथा
		mdp->cd = (काष्ठा sh_eth_cpu_data *)of_device_get_match_data(&pdev->dev);

	mdp->reg_offset = sh_eth_get_रेजिस्टर_offset(mdp->cd->रेजिस्टर_type);
	अगर (!mdp->reg_offset) अणु
		dev_err(&pdev->dev, "Unknown register type (%d)\n",
			mdp->cd->रेजिस्टर_type);
		ret = -EINVAL;
		जाओ out_release;
	पूर्ण
	sh_eth_set_शेष_cpu_data(mdp->cd);

	/* User's manual states max MTU should be 2048 but due to the
	 * alignment calculations in sh_eth_ring_init() the practical
	 * MTU is a bit less. Maybe this can be optimized some more.
	 */
	ndev->max_mtu = 2000 - (ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN);
	ndev->min_mtu = ETH_MIN_MTU;

	अगर (mdp->cd->rx_csum) अणु
		ndev->features = NETIF_F_RXCSUM;
		ndev->hw_features = NETIF_F_RXCSUM;
	पूर्ण

	/* set function */
	अगर (mdp->cd->tsu)
		ndev->netdev_ops = &sh_eth_netdev_ops_tsu;
	अन्यथा
		ndev->netdev_ops = &sh_eth_netdev_ops;
	ndev->ethtool_ops = &sh_eth_ethtool_ops;
	ndev->watchकरोg_समयo = TX_TIMEOUT;

	/* debug message level */
	mdp->msg_enable = SH_ETH_DEF_MSG_ENABLE;

	/* पढ़ो and set MAC address */
	पढ़ो_mac_address(ndev, pd->mac_addr);
	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		dev_warn(&pdev->dev,
			 "no valid MAC address supplied, using a random one.\n");
		eth_hw_addr_अक्रमom(ndev);
	पूर्ण

	अगर (mdp->cd->tsu) अणु
		पूर्णांक port = pdev->id < 0 ? 0 : pdev->id % 2;
		काष्ठा resource *rtsu;

		rtsu = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (!rtsu) अणु
			dev_err(&pdev->dev, "no TSU resource\n");
			ret = -ENODEV;
			जाओ out_release;
		पूर्ण
		/* We can only request the  TSU region  क्रम the first port
		 * of the two  sharing this TSU क्रम the probe to succeed...
		 */
		अगर (port == 0 &&
		    !devm_request_mem_region(&pdev->dev, rtsu->start,
					     resource_size(rtsu),
					     dev_name(&pdev->dev))) अणु
			dev_err(&pdev->dev, "can't request TSU resource.\n");
			ret = -EBUSY;
			जाओ out_release;
		पूर्ण
		/* ioremap the TSU रेजिस्टरs */
		mdp->tsu_addr = devm_ioremap(&pdev->dev, rtsu->start,
					     resource_size(rtsu));
		अगर (!mdp->tsu_addr) अणु
			dev_err(&pdev->dev, "TSU region ioremap() failed.\n");
			ret = -ENOMEM;
			जाओ out_release;
		पूर्ण
		mdp->port = port;
		ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

		/* Need to init only the first port of the two sharing a TSU */
		अगर (port == 0) अणु
			अगर (mdp->cd->chip_reset)
				mdp->cd->chip_reset(ndev);

			/* TSU init (Init only)*/
			sh_eth_tsu_init(mdp);
		पूर्ण
	पूर्ण

	अगर (mdp->cd->rmiimode)
		sh_eth_ग_लिखो(ndev, 0x1, RMIIMODE);

	/* MDIO bus init */
	ret = sh_mdio_init(mdp, pd);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "MDIO init failed: %d\n", ret);
		जाओ out_release;
	पूर्ण

	netअगर_napi_add(ndev, &mdp->napi, sh_eth_poll, 64);

	/* network device रेजिस्टर */
	ret = रेजिस्टर_netdev(ndev);
	अगर (ret)
		जाओ out_napi_del;

	अगर (mdp->cd->magic)
		device_set_wakeup_capable(&pdev->dev, 1);

	/* prपूर्णांक device inक्रमmation */
	netdev_info(ndev, "Base address at 0x%x, %pM, IRQ %d.\n",
		    (u32)ndev->base_addr, ndev->dev_addr, ndev->irq);

	pm_runसमय_put(&pdev->dev);
	platक्रमm_set_drvdata(pdev, ndev);

	वापस ret;

out_napi_del:
	netअगर_napi_del(&mdp->napi);
	sh_mdio_release(mdp);

out_release:
	/* net_dev मुक्त */
	मुक्त_netdev(ndev);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_eth_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	netअगर_napi_del(&mdp->napi);
	sh_mdio_release(mdp);
	pm_runसमय_disable(&pdev->dev);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sh_eth_wol_setup(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);

	/* Only allow ECI पूर्णांकerrupts */
	synchronize_irq(ndev->irq);
	napi_disable(&mdp->napi);
	sh_eth_ग_लिखो(ndev, EESIPR_ECIIP, EESIPR);

	/* Enable MagicPacket */
	sh_eth_modअगरy(ndev, ECMR, ECMR_MPDE, ECMR_MPDE);

	वापस enable_irq_wake(ndev->irq);
पूर्ण

अटल पूर्णांक sh_eth_wol_restore(काष्ठा net_device *ndev)
अणु
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret;

	napi_enable(&mdp->napi);

	/* Disable MagicPacket */
	sh_eth_modअगरy(ndev, ECMR, ECMR_MPDE, 0);

	/* The device needs to be reset to restore MagicPacket logic
	 * क्रम next wakeup. If we बंद and खोलो the device it will
	 * both be reset and all रेजिस्टरs restored. This is what
	 * happens during suspend and resume without WoL enabled.
	 */
	ret = sh_eth_बंद(ndev);
	अगर (ret < 0)
		वापस ret;
	ret = sh_eth_खोलो(ndev);
	अगर (ret < 0)
		वापस ret;

	वापस disable_irq_wake(ndev->irq);
पूर्ण

अटल पूर्णांक sh_eth_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret = 0;

	अगर (!netअगर_running(ndev))
		वापस 0;

	netअगर_device_detach(ndev);

	अगर (mdp->wol_enabled)
		ret = sh_eth_wol_setup(ndev);
	अन्यथा
		ret = sh_eth_बंद(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक sh_eth_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sh_eth_निजी *mdp = netdev_priv(ndev);
	पूर्णांक ret = 0;

	अगर (!netअगर_running(ndev))
		वापस 0;

	अगर (mdp->wol_enabled)
		ret = sh_eth_wol_restore(ndev);
	अन्यथा
		ret = sh_eth_खोलो(ndev);

	अगर (ret < 0)
		वापस ret;

	netअगर_device_attach(ndev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sh_eth_runसमय_nop(काष्ठा device *dev)
अणु
	/* Runसमय PM callback shared between ->runसमय_suspend()
	 * and ->runसमय_resume(). Simply वापसs success.
	 *
	 * This driver re-initializes all रेजिस्टरs after
	 * pm_runसमय_get_sync() anyway so there is no need
	 * to save and restore रेजिस्टरs here.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sh_eth_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sh_eth_suspend, sh_eth_resume)
	SET_RUNTIME_PM_OPS(sh_eth_runसमय_nop, sh_eth_runसमय_nop, शून्य)
पूर्ण;
#घोषणा SH_ETH_PM_OPS (&sh_eth_dev_pm_ops)
#अन्यथा
#घोषणा SH_ETH_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id sh_eth_id_table[] = अणु
	अणु "sh7619-ether", (kernel_uदीर्घ_t)&sh7619_data पूर्ण,
	अणु "sh771x-ether", (kernel_uदीर्घ_t)&sh771x_data पूर्ण,
	अणु "sh7724-ether", (kernel_uदीर्घ_t)&sh7724_data पूर्ण,
	अणु "sh7734-gether", (kernel_uदीर्घ_t)&sh7734_data पूर्ण,
	अणु "sh7757-ether", (kernel_uदीर्घ_t)&sh7757_data पूर्ण,
	अणु "sh7757-gether", (kernel_uदीर्घ_t)&sh7757_data_giga पूर्ण,
	अणु "sh7763-gether", (kernel_uदीर्घ_t)&sh7763_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sh_eth_id_table);

अटल काष्ठा platक्रमm_driver sh_eth_driver = अणु
	.probe = sh_eth_drv_probe,
	.हटाओ = sh_eth_drv_हटाओ,
	.id_table = sh_eth_id_table,
	.driver = अणु
		   .name = CARDNAME,
		   .pm = SH_ETH_PM_OPS,
		   .of_match_table = of_match_ptr(sh_eth_match_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sh_eth_driver);

MODULE_AUTHOR("Nobuhiro Iwamatsu, Yoshihiro Shimoda");
MODULE_DESCRIPTION("Renesas SuperH Ethernet driver");
MODULE_LICENSE("GPL v2");
