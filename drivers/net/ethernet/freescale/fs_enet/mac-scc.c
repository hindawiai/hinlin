<शैली गुरु>
/*
 * Ethernet on Serial Communications Controller (SCC) driver क्रम Motorola MPC8xx and MPC82xx.
 *
 * Copyright (c) 2003 Intracom S.A.
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
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "fs_enet.h"

/*************************************************/
#अगर defined(CONFIG_CPM1)
/* क्रम a 8xx __raw_xxx's are sufficient */
#घोषणा __fs_out32(addr, x)	__raw_ग_लिखोl(x, addr)
#घोषणा __fs_out16(addr, x)	__raw_ग_लिखोw(x, addr)
#घोषणा __fs_out8(addr, x)	__raw_ग_लिखोb(x, addr)
#घोषणा __fs_in32(addr)	__raw_पढ़ोl(addr)
#घोषणा __fs_in16(addr)	__raw_पढ़ोw(addr)
#घोषणा __fs_in8(addr)	__raw_पढ़ोb(addr)
#अन्यथा
/* क्रम others play it safe */
#घोषणा __fs_out32(addr, x)	out_be32(addr, x)
#घोषणा __fs_out16(addr, x)	out_be16(addr, x)
#घोषणा __fs_in32(addr)	in_be32(addr)
#घोषणा __fs_in16(addr)	in_be16(addr)
#घोषणा __fs_out8(addr, x)	out_8(addr, x)
#घोषणा __fs_in8(addr)	in_8(addr)
#पूर्ण_अगर

/* ग_लिखो, पढ़ो, set bits, clear bits */
#घोषणा W32(_p, _m, _v) __fs_out32(&(_p)->_m, (_v))
#घोषणा R32(_p, _m)     __fs_in32(&(_p)->_m)
#घोषणा S32(_p, _m, _v) W32(_p, _m, R32(_p, _m) | (_v))
#घोषणा C32(_p, _m, _v) W32(_p, _m, R32(_p, _m) & ~(_v))

#घोषणा W16(_p, _m, _v) __fs_out16(&(_p)->_m, (_v))
#घोषणा R16(_p, _m)     __fs_in16(&(_p)->_m)
#घोषणा S16(_p, _m, _v) W16(_p, _m, R16(_p, _m) | (_v))
#घोषणा C16(_p, _m, _v) W16(_p, _m, R16(_p, _m) & ~(_v))

#घोषणा W8(_p, _m, _v)  __fs_out8(&(_p)->_m, (_v))
#घोषणा R8(_p, _m)      __fs_in8(&(_p)->_m)
#घोषणा S8(_p, _m, _v)  W8(_p, _m, R8(_p, _m) | (_v))
#घोषणा C8(_p, _m, _v)  W8(_p, _m, R8(_p, _m) & ~(_v))

#घोषणा SCC_MAX_MULTICAST_ADDRS	64

/*
 * Delay to रुको क्रम SCC reset command to complete (in us)
 */
#घोषणा SCC_RESET_DELAY		50

अटल अंतरभूत पूर्णांक scc_cr_cmd(काष्ठा fs_enet_निजी *fep, u32 op)
अणु
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;

	वापस cpm_command(fpi->cp_command, op);
पूर्ण

अटल पूर्णांक करो_pd_setup(काष्ठा fs_enet_निजी *fep)
अणु
	काष्ठा platक्रमm_device *ofdev = to_platक्रमm_device(fep->dev);

	fep->पूर्णांकerrupt = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	अगर (!fep->पूर्णांकerrupt)
		वापस -EINVAL;

	fep->scc.sccp = of_iomap(ofdev->dev.of_node, 0);
	अगर (!fep->scc.sccp)
		वापस -EINVAL;

	fep->scc.ep = of_iomap(ofdev->dev.of_node, 1);
	अगर (!fep->scc.ep) अणु
		iounmap(fep->scc.sccp);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SCC_NAPI_EVENT_MSK	(SCCE_ENET_RXF | SCCE_ENET_RXB | SCCE_ENET_TXB)
#घोषणा SCC_EVENT		(SCCE_ENET_RXF | SCCE_ENET_TXB)
#घोषणा SCC_ERR_EVENT_MSK	(SCCE_ENET_TXE | SCCE_ENET_BSY)

अटल पूर्णांक setup_data(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	करो_pd_setup(fep);

	fep->scc.hthi = 0;
	fep->scc.htlo = 0;

	fep->ev_napi = SCC_NAPI_EVENT_MSK;
	fep->ev = SCC_EVENT | SCCE_ENET_TXE;
	fep->ev_err = SCC_ERR_EVENT_MSK;

	वापस 0;
पूर्ण

अटल पूर्णांक allocate_bd(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;

	fep->ring_mem_addr = cpm_dpalloc((fpi->tx_ring + fpi->rx_ring) *
					 माप(cbd_t), 8);
	अगर (IS_ERR_VALUE(fep->ring_mem_addr))
		वापस -ENOMEM;

	fep->ring_base = (व्योम __iomem __क्रमce*)
		cpm_dpram_addr(fep->ring_mem_addr);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_bd(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	अगर (fep->ring_base)
		cpm_dpमुक्त(fep->ring_mem_addr);
पूर्ण

अटल व्योम cleanup_data(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

अटल व्योम set_promiscuous_mode(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	S16(sccp, scc_psmr, SCC_PSMR_PRO);
पूर्ण

अटल व्योम set_multicast_start(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_enet_t __iomem *ep = fep->scc.ep;

	W16(ep, sen_gaddr1, 0);
	W16(ep, sen_gaddr2, 0);
	W16(ep, sen_gaddr3, 0);
	W16(ep, sen_gaddr4, 0);
पूर्ण

अटल व्योम set_multicast_one(काष्ठा net_device *dev, स्थिर u8 * mac)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_enet_t __iomem *ep = fep->scc.ep;
	u16 taddrh, taddrm, taddrl;

	taddrh = ((u16) mac[5] << 8) | mac[4];
	taddrm = ((u16) mac[3] << 8) | mac[2];
	taddrl = ((u16) mac[1] << 8) | mac[0];

	W16(ep, sen_taddrh, taddrh);
	W16(ep, sen_taddrm, taddrm);
	W16(ep, sen_taddrl, taddrl);
	scc_cr_cmd(fep, CPM_CR_SET_GADDR);
पूर्ण

अटल व्योम set_multicast_finish(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;
	scc_enet_t __iomem *ep = fep->scc.ep;

	/* clear promiscuous always */
	C16(sccp, scc_psmr, SCC_PSMR_PRO);

	/* अगर all multi or too many multicasts; just enable all */
	अगर ((dev->flags & IFF_ALLMULTI) != 0 ||
	    netdev_mc_count(dev) > SCC_MAX_MULTICAST_ADDRS) अणु

		W16(ep, sen_gaddr1, 0xffff);
		W16(ep, sen_gaddr2, 0xffff);
		W16(ep, sen_gaddr3, 0xffff);
		W16(ep, sen_gaddr4, 0xffff);
	पूर्ण
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

/*
 * This function is called to start or restart the FEC during a link
 * change.  This only happens when चयनing between half and full
 * duplex.
 */
अटल व्योम restart(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;
	scc_enet_t __iomem *ep = fep->scc.ep;
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	u16 paddrh, paddrm, paddrl;
	स्थिर अचिन्हित अक्षर *mac;
	पूर्णांक i;

	C32(sccp, scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);

	/* clear everything (slow & steady करोes it) */
	क्रम (i = 0; i < माप(*ep); i++)
		__fs_out8((u8 __iomem *)ep + i, 0);

	/* poपूर्णांक to bds */
	W16(ep, sen_genscc.scc_rbase, fep->ring_mem_addr);
	W16(ep, sen_genscc.scc_tbase,
	    fep->ring_mem_addr + माप(cbd_t) * fpi->rx_ring);

	/* Initialize function code रेजिस्टरs क्रम big-endian.
	 */
#अगर_अघोषित CONFIG_NOT_COHERENT_CACHE
	W8(ep, sen_genscc.scc_rfcr, SCC_EB | SCC_GBL);
	W8(ep, sen_genscc.scc_tfcr, SCC_EB | SCC_GBL);
#अन्यथा
	W8(ep, sen_genscc.scc_rfcr, SCC_EB);
	W8(ep, sen_genscc.scc_tfcr, SCC_EB);
#पूर्ण_अगर

	/* Set maximum bytes per receive buffer.
	 * This appears to be an Ethernet frame size, not the buffer
	 * fragment size.  It must be a multiple of four.
	 */
	W16(ep, sen_genscc.scc_mrblr, 0x5f0);

	/* Set CRC preset and mask.
	 */
	W32(ep, sen_cpres, 0xffffffff);
	W32(ep, sen_cmask, 0xdebb20e3);

	W32(ep, sen_crcec, 0);	/* CRC Error counter */
	W32(ep, sen_alec, 0);	/* alignment error counter */
	W32(ep, sen_disfc, 0);	/* discard frame counter */

	W16(ep, sen_pads, 0x8888);	/* Tx लघु frame pad अक्षरacter */
	W16(ep, sen_retlim, 15);	/* Retry limit threshold */

	W16(ep, sen_maxflr, 0x5ee);	/* maximum frame length रेजिस्टर */

	W16(ep, sen_minflr, PKT_MINBUF_SIZE);	/* minimum frame length रेजिस्टर */

	W16(ep, sen_maxd1, 0x000005f0);	/* maximum DMA1 length */
	W16(ep, sen_maxd2, 0x000005f0);	/* maximum DMA2 length */

	/* Clear hash tables.
	 */
	W16(ep, sen_gaddr1, 0);
	W16(ep, sen_gaddr2, 0);
	W16(ep, sen_gaddr3, 0);
	W16(ep, sen_gaddr4, 0);
	W16(ep, sen_iaddr1, 0);
	W16(ep, sen_iaddr2, 0);
	W16(ep, sen_iaddr3, 0);
	W16(ep, sen_iaddr4, 0);

	/* set address
	 */
	mac = dev->dev_addr;
	paddrh = ((u16) mac[5] << 8) | mac[4];
	paddrm = ((u16) mac[3] << 8) | mac[2];
	paddrl = ((u16) mac[1] << 8) | mac[0];

	W16(ep, sen_paddrh, paddrh);
	W16(ep, sen_paddrm, paddrm);
	W16(ep, sen_paddrl, paddrl);

	W16(ep, sen_pper, 0);
	W16(ep, sen_taddrl, 0);
	W16(ep, sen_taddrm, 0);
	W16(ep, sen_taddrh, 0);

	fs_init_bds(dev);

	scc_cr_cmd(fep, CPM_CR_INIT_TRX);

	W16(sccp, scc_scce, 0xffff);

	/* Enable पूर्णांकerrupts we wish to service.
	 */
	W16(sccp, scc_sccm, SCCE_ENET_TXE | SCCE_ENET_RXF | SCCE_ENET_TXB);

	/* Set GSMR_H to enable all normal operating modes.
	 * Set GSMR_L to enable Ethernet to MC68160.
	 */
	W32(sccp, scc_gsmrh, 0);
	W32(sccp, scc_gsmrl,
	    SCC_GSMRL_TCI | SCC_GSMRL_TPL_48 | SCC_GSMRL_TPP_10 |
	    SCC_GSMRL_MODE_ENET);

	/* Set sync/delimiters.
	 */
	W16(sccp, scc_dsr, 0xd555);

	/* Set processing mode.  Use Ethernet CRC, catch broadcast, and
	 * start frame search 22 bit बार after RENA.
	 */
	W16(sccp, scc_psmr, SCC_PSMR_ENCRC | SCC_PSMR_NIB22);

	/* Set full duplex mode अगर needed */
	अगर (dev->phydev->duplex)
		S16(sccp, scc_psmr, SCC_PSMR_LPB | SCC_PSMR_FDE);

	/* Restore multicast and promiscuous settings */
	set_multicast_list(dev);

	S32(sccp, scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);
पूर्ण

अटल व्योम stop(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;
	पूर्णांक i;

	क्रम (i = 0; (R16(sccp, scc_sccm) == 0) && i < SCC_RESET_DELAY; i++)
		udelay(1);

	अगर (i == SCC_RESET_DELAY)
		dev_warn(fep->dev, "SCC timeout on graceful transmit stop\n");

	W16(sccp, scc_sccm, 0);
	C32(sccp, scc_gsmrl, SCC_GSMRL_ENR | SCC_GSMRL_ENT);

	fs_cleanup_bds(dev);
पूर्ण

अटल व्योम napi_clear_event_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	W16(sccp, scc_scce, SCC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम napi_enable_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	S16(sccp, scc_sccm, SCC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम napi_disable_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	C16(sccp, scc_sccm, SCC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम rx_bd_करोne(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

अटल व्योम tx_kickstart(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

अटल u32 get_पूर्णांक_events(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	वापस (u32) R16(sccp, scc_scce);
पूर्ण

अटल व्योम clear_पूर्णांक_events(काष्ठा net_device *dev, u32 पूर्णांक_events)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	W16(sccp, scc_scce, पूर्णांक_events & 0xffff);
पूर्ण

अटल व्योम ev_error(काष्ठा net_device *dev, u32 पूर्णांक_events)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	dev_warn(fep->dev, "SCC ERROR(s) 0x%x\n", पूर्णांक_events);
पूर्ण

अटल पूर्णांक get_regs(काष्ठा net_device *dev, व्योम *p, पूर्णांक *sizep)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	अगर (*sizep < माप(scc_t) + माप(scc_enet_t __iomem *))
		वापस -EINVAL;

	स_नकल_fromio(p, fep->scc.sccp, माप(scc_t));
	p = (अक्षर *)p + माप(scc_t);

	स_नकल_fromio(p, fep->scc.ep, माप(scc_enet_t __iomem *));

	वापस 0;
पूर्ण

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	वापस माप(scc_t) + माप(scc_enet_t __iomem *);
पूर्ण

अटल व्योम tx_restart(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	scc_cr_cmd(fep, CPM_CR_RESTART_TX);
पूर्ण



/*************************************************************************/

स्थिर काष्ठा fs_ops fs_scc_ops = अणु
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
