<शैली गुरु>
/*
 * Freescale Ethernet controllers
 *
 * Copyright (c) 2005 Intracom S.A.
 *  by Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2005 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crc32.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "fs_enet.h"
#समावेश "fec.h"

/*************************************************/

#अगर defined(CONFIG_CPM1)
/* क्रम a CPM1 __raw_xxx's are sufficient */
#घोषणा __fs_out32(addr, x)	__raw_ग_लिखोl(x, addr)
#घोषणा __fs_out16(addr, x)	__raw_ग_लिखोw(x, addr)
#घोषणा __fs_in32(addr)	__raw_पढ़ोl(addr)
#घोषणा __fs_in16(addr)	__raw_पढ़ोw(addr)
#अन्यथा
/* क्रम others play it safe */
#घोषणा __fs_out32(addr, x)	out_be32(addr, x)
#घोषणा __fs_out16(addr, x)	out_be16(addr, x)
#घोषणा __fs_in32(addr)	in_be32(addr)
#घोषणा __fs_in16(addr)	in_be16(addr)
#पूर्ण_अगर

/* ग_लिखो */
#घोषणा FW(_fecp, _reg, _v) __fs_out32(&(_fecp)->fec_ ## _reg, (_v))

/* पढ़ो */
#घोषणा FR(_fecp, _reg)	__fs_in32(&(_fecp)->fec_ ## _reg)

/* set bits */
#घोषणा FS(_fecp, _reg, _v) FW(_fecp, _reg, FR(_fecp, _reg) | (_v))

/* clear bits */
#घोषणा FC(_fecp, _reg, _v) FW(_fecp, _reg, FR(_fecp, _reg) & ~(_v))

/*
 * Delay to रुको क्रम FEC reset command to complete (in us)
 */
#घोषणा FEC_RESET_DELAY		50

अटल पूर्णांक whack_reset(काष्ठा fec __iomem *fecp)
अणु
	पूर्णांक i;

	FW(fecp, ecntrl, FEC_ECNTRL_PINMUX | FEC_ECNTRL_RESET);
	क्रम (i = 0; i < FEC_RESET_DELAY; i++) अणु
		अगर ((FR(fecp, ecntrl) & FEC_ECNTRL_RESET) == 0)
			वापस 0;	/* OK */
		udelay(1);
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक करो_pd_setup(काष्ठा fs_enet_निजी *fep)
अणु
	काष्ठा platक्रमm_device *ofdev = to_platक्रमm_device(fep->dev);

	fep->पूर्णांकerrupt = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	अगर (!fep->पूर्णांकerrupt)
		वापस -EINVAL;

	fep->fec.fecp = of_iomap(ofdev->dev.of_node, 0);
	अगर (!fep->fcc.fccp)
		वापस -EINVAL;

	वापस 0;
पूर्ण

#घोषणा FEC_NAPI_EVENT_MSK	(FEC_ENET_RXF | FEC_ENET_RXB | FEC_ENET_TXF)
#घोषणा FEC_EVENT		(FEC_ENET_RXF | FEC_ENET_TXF)
#घोषणा FEC_ERR_EVENT_MSK	(FEC_ENET_HBERR | FEC_ENET_BABR | \
				 FEC_ENET_BABT | FEC_ENET_EBERR)

अटल पूर्णांक setup_data(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	अगर (करो_pd_setup(fep) != 0)
		वापस -EINVAL;

	fep->fec.hthi = 0;
	fep->fec.htlo = 0;

	fep->ev_napi = FEC_NAPI_EVENT_MSK;
	fep->ev = FEC_EVENT;
	fep->ev_err = FEC_ERR_EVENT_MSK;

	वापस 0;
पूर्ण

अटल पूर्णांक allocate_bd(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;

	fep->ring_base = (व्योम __क्रमce __iomem *)dma_alloc_coherent(fep->dev,
					    (fpi->tx_ring + fpi->rx_ring) *
					    माप(cbd_t), &fep->ring_mem_addr,
					    GFP_KERNEL);
	अगर (fep->ring_base == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_bd(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;

	अगर(fep->ring_base)
		dma_मुक्त_coherent(fep->dev, (fpi->tx_ring + fpi->rx_ring)
					* माप(cbd_t),
					(व्योम __क्रमce *)fep->ring_base,
					fep->ring_mem_addr);
पूर्ण

अटल व्योम cleanup_data(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

अटल व्योम set_promiscuous_mode(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FS(fecp, r_cntrl, FEC_RCNTRL_PROM);
पूर्ण

अटल व्योम set_multicast_start(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	fep->fec.hthi = 0;
	fep->fec.htlo = 0;
पूर्ण

अटल व्योम set_multicast_one(काष्ठा net_device *dev, स्थिर u8 *mac)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	पूर्णांक temp, hash_index;
	u32 crc, csrVal;

	crc = ether_crc(6, mac);

	temp = (crc & 0x3f) >> 1;
	hash_index = ((temp & 0x01) << 4) |
		     ((temp & 0x02) << 2) |
		     ((temp & 0x04)) |
		     ((temp & 0x08) >> 2) |
		     ((temp & 0x10) >> 4);
	csrVal = 1 << hash_index;
	अगर (crc & 1)
		fep->fec.hthi |= csrVal;
	अन्यथा
		fep->fec.htlo |= csrVal;
पूर्ण

अटल व्योम set_multicast_finish(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	/* अगर all multi or too many multicasts; just enable all */
	अगर ((dev->flags & IFF_ALLMULTI) != 0 ||
	    netdev_mc_count(dev) > FEC_MAX_MULTICAST_ADDRS) अणु
		fep->fec.hthi = 0xffffffffU;
		fep->fec.htlo = 0xffffffffU;
	पूर्ण

	FC(fecp, r_cntrl, FEC_RCNTRL_PROM);
	FW(fecp, grp_hash_table_high, fep->fec.hthi);
	FW(fecp, grp_hash_table_low, fep->fec.htlo);
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;

	अगर ((dev->flags & IFF_PROMISC) == 0) अणु
		set_multicast_start(dev);
		netdev_क्रम_each_mc_addr(ha, dev)
			set_multicast_one(dev, ha->addr);
		set_multicast_finish(dev);
	पूर्ण अन्यथा
		set_promiscuous_mode(dev);
पूर्ण

अटल व्योम restart(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	dma_addr_t rx_bd_base_phys, tx_bd_base_phys;
	पूर्णांक r;
	u32 addrhi, addrlo;

	काष्ठा mii_bus *mii = dev->phydev->mdio.bus;
	काष्ठा fec_info* fec_inf = mii->priv;

	r = whack_reset(fep->fec.fecp);
	अगर (r != 0)
		dev_err(fep->dev, "FEC Reset FAILED!\n");
	/*
	 * Set station address.
	 */
	addrhi = ((u32) dev->dev_addr[0] << 24) |
		 ((u32) dev->dev_addr[1] << 16) |
		 ((u32) dev->dev_addr[2] <<  8) |
		  (u32) dev->dev_addr[3];
	addrlo = ((u32) dev->dev_addr[4] << 24) |
		 ((u32) dev->dev_addr[5] << 16);
	FW(fecp, addr_low, addrhi);
	FW(fecp, addr_high, addrlo);

	/*
	 * Reset all multicast.
	 */
	FW(fecp, grp_hash_table_high, fep->fec.hthi);
	FW(fecp, grp_hash_table_low, fep->fec.htlo);

	/*
	 * Set maximum receive buffer size.
	 */
	FW(fecp, r_buff_size, PKT_MAXBLR_SIZE);
#अगर_घोषित CONFIG_FS_ENET_MPC5121_FEC
	FW(fecp, r_cntrl, PKT_MAXBUF_SIZE << 16);
#अन्यथा
	FW(fecp, r_hash, PKT_MAXBUF_SIZE);
#पूर्ण_अगर

	/* get physical address */
	rx_bd_base_phys = fep->ring_mem_addr;
	tx_bd_base_phys = rx_bd_base_phys + माप(cbd_t) * fpi->rx_ring;

	/*
	 * Set receive and transmit descriptor base.
	 */
	FW(fecp, r_des_start, rx_bd_base_phys);
	FW(fecp, x_des_start, tx_bd_base_phys);

	fs_init_bds(dev);

	/*
	 * Enable big endian and करोn't care about SDMA FC.
	 */
#अगर_घोषित CONFIG_FS_ENET_MPC5121_FEC
	FS(fecp, dma_control, 0xC0000000);
#अन्यथा
	FW(fecp, fun_code, 0x78000000);
#पूर्ण_अगर

	/*
	 * Set MII speed.
	 */
	FW(fecp, mii_speed, fec_inf->mii_speed);

	/*
	 * Clear any outstanding पूर्णांकerrupt.
	 */
	FW(fecp, ievent, 0xffc0);
#अगर_अघोषित CONFIG_FS_ENET_MPC5121_FEC
	FW(fecp, ivec, (virq_to_hw(fep->पूर्णांकerrupt) / 2) << 29);

	FW(fecp, r_cntrl, FEC_RCNTRL_MII_MODE);	/* MII enable */
#अन्यथा
	/*
	 * Only set MII/RMII mode - करो not touch maximum frame length
	 * configured beक्रमe.
	 */
	FS(fecp, r_cntrl, fpi->use_rmii ?
			FEC_RCNTRL_RMII_MODE : FEC_RCNTRL_MII_MODE);
#पूर्ण_अगर
	/*
	 * adjust to duplex mode
	 */
	अगर (dev->phydev->duplex) अणु
		FC(fecp, r_cntrl, FEC_RCNTRL_DRT);
		FS(fecp, x_cntrl, FEC_TCNTRL_FDEN);	/* FD enable */
	पूर्ण अन्यथा अणु
		FS(fecp, r_cntrl, FEC_RCNTRL_DRT);
		FC(fecp, x_cntrl, FEC_TCNTRL_FDEN);	/* FD disable */
	पूर्ण

	/* Restore multicast and promiscuous settings */
	set_multicast_list(dev);

	/*
	 * Enable पूर्णांकerrupts we wish to service.
	 */
	FW(fecp, imask, FEC_ENET_TXF | FEC_ENET_TXB |
	   FEC_ENET_RXF | FEC_ENET_RXB);

	/*
	 * And last, enable the transmit and receive processing.
	 */
	FW(fecp, ecntrl, FEC_ECNTRL_PINMUX | FEC_ECNTRL_ETHER_EN);
	FW(fecp, r_des_active, 0x01000000);
पूर्ण

अटल व्योम stop(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	काष्ठा fec_info *feci = dev->phydev->mdio.bus->priv;

	पूर्णांक i;

	अगर ((FR(fecp, ecntrl) & FEC_ECNTRL_ETHER_EN) == 0)
		वापस;		/* alपढ़ोy करोwn */

	FW(fecp, x_cntrl, 0x01);	/* Graceful transmit stop */
	क्रम (i = 0; ((FR(fecp, ievent) & 0x10000000) == 0) &&
	     i < FEC_RESET_DELAY; i++)
		udelay(1);

	अगर (i == FEC_RESET_DELAY)
		dev_warn(fep->dev, "FEC timeout on graceful transmit stop\n");
	/*
	 * Disable FEC. Let only MII पूर्णांकerrupts.
	 */
	FW(fecp, imask, 0);
	FC(fecp, ecntrl, FEC_ECNTRL_ETHER_EN);

	fs_cleanup_bds(dev);

	/* shut करोwn FEC1? that's where the mii bus is */
	अगर (fpi->has_phy) अणु
		FS(fecp, r_cntrl, fpi->use_rmii ?
				FEC_RCNTRL_RMII_MODE :
				FEC_RCNTRL_MII_MODE);	/* MII/RMII enable */
		FS(fecp, ecntrl, FEC_ECNTRL_PINMUX | FEC_ECNTRL_ETHER_EN);
		FW(fecp, ievent, FEC_ENET_MII);
		FW(fecp, mii_speed, feci->mii_speed);
	पूर्ण
पूर्ण

अटल व्योम napi_clear_event_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, ievent, FEC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम napi_enable_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FS(fecp, imask, FEC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम napi_disable_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FC(fecp, imask, FEC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम rx_bd_करोne(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, r_des_active, 0x01000000);
पूर्ण

अटल व्योम tx_kickstart(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, x_des_active, 0x01000000);
पूर्ण

अटल u32 get_पूर्णांक_events(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	वापस FR(fecp, ievent) & FR(fecp, imask);
पूर्ण

अटल व्योम clear_पूर्णांक_events(काष्ठा net_device *dev, u32 पूर्णांक_events)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	काष्ठा fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, ievent, पूर्णांक_events);
पूर्ण

अटल व्योम ev_error(काष्ठा net_device *dev, u32 पूर्णांक_events)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	dev_warn(fep->dev, "FEC ERROR(s) 0x%x\n", पूर्णांक_events);
पूर्ण

अटल पूर्णांक get_regs(काष्ठा net_device *dev, व्योम *p, पूर्णांक *sizep)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	अगर (*sizep < माप(काष्ठा fec))
		वापस -EINVAL;

	स_नकल_fromio(p, fep->fec.fecp, माप(काष्ठा fec));

	वापस 0;
पूर्ण

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	वापस माप(काष्ठा fec);
पूर्ण

अटल व्योम tx_restart(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

/*************************************************************************/

स्थिर काष्ठा fs_ops fs_fec_ops = अणु
	.setup_data		= setup_data,
	.cleanup_data		= cleanup_data,
	.set_multicast_list	= set_multicast_list,
	.restart		= restart,
	.stop			= stop,
	.napi_clear_event	= napi_clear_event_fs,
	.napi_enable		= napi_enable_fs,
	.napi_disable		= napi_disable_fs,
	.rx_bd_करोne		= rx_bd_करोne,
	.tx_kickstart		= tx_kickstart,
	.get_पूर्णांक_events		= get_पूर्णांक_events,
	.clear_पूर्णांक_events	= clear_पूर्णांक_events,
	.ev_error		= ev_error,
	.get_regs		= get_regs,
	.get_regs_len		= get_regs_len,
	.tx_restart		= tx_restart,
	.allocate_bd		= allocate_bd,
	.मुक्त_bd		= मुक्त_bd,
पूर्ण;

