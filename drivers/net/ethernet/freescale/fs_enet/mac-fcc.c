<शैली गुरु>
/*
 * FCC driver क्रम Motorola MPC82xx (PQ2).
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
#समावेश <linux/phy.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/immap_cpm2.h>
#समावेश <यंत्र/mpc8260.h>
#समावेश <यंत्र/cpm2.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "fs_enet.h"

/*************************************************/

/* FCC access macros */

/* ग_लिखो, पढ़ो, set bits, clear bits */
#घोषणा W32(_p, _m, _v)	out_be32(&(_p)->_m, (_v))
#घोषणा R32(_p, _m)	in_be32(&(_p)->_m)
#घोषणा S32(_p, _m, _v)	W32(_p, _m, R32(_p, _m) | (_v))
#घोषणा C32(_p, _m, _v)	W32(_p, _m, R32(_p, _m) & ~(_v))

#घोषणा W16(_p, _m, _v)	out_be16(&(_p)->_m, (_v))
#घोषणा R16(_p, _m)	in_be16(&(_p)->_m)
#घोषणा S16(_p, _m, _v)	W16(_p, _m, R16(_p, _m) | (_v))
#घोषणा C16(_p, _m, _v)	W16(_p, _m, R16(_p, _m) & ~(_v))

#घोषणा W8(_p, _m, _v)	out_8(&(_p)->_m, (_v))
#घोषणा R8(_p, _m)	in_8(&(_p)->_m)
#घोषणा S8(_p, _m, _v)	W8(_p, _m, R8(_p, _m) | (_v))
#घोषणा C8(_p, _m, _v)	W8(_p, _m, R8(_p, _m) & ~(_v))

/*************************************************/

#घोषणा FCC_MAX_MULTICAST_ADDRS	64

#घोषणा mk_mii_पढ़ो(REG)	(0x60020000 | ((REG & 0x1f) << 18))
#घोषणा mk_mii_ग_लिखो(REG, VAL)	(0x50020000 | ((REG & 0x1f) << 18) | (VAL & 0xffff))
#घोषणा mk_mii_end		0

#घोषणा MAX_CR_CMD_LOOPS	10000

अटल अंतरभूत पूर्णांक fcc_cr_cmd(काष्ठा fs_enet_निजी *fep, u32 op)
अणु
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;

	वापस cpm_command(fpi->cp_command, op);
पूर्ण

अटल पूर्णांक करो_pd_setup(काष्ठा fs_enet_निजी *fep)
अणु
	काष्ठा platक्रमm_device *ofdev = to_platक्रमm_device(fep->dev);
	काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	पूर्णांक ret = -EINVAL;

	fep->पूर्णांकerrupt = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	अगर (!fep->पूर्णांकerrupt)
		जाओ out;

	fep->fcc.fccp = of_iomap(ofdev->dev.of_node, 0);
	अगर (!fep->fcc.fccp)
		जाओ out;

	fep->fcc.ep = of_iomap(ofdev->dev.of_node, 1);
	अगर (!fep->fcc.ep)
		जाओ out_fccp;

	fep->fcc.fcccp = of_iomap(ofdev->dev.of_node, 2);
	अगर (!fep->fcc.fcccp)
		जाओ out_ep;

	fep->fcc.mem = (व्योम __iomem *)cpm2_immr;
	fpi->dpram_offset = cpm_dpalloc(128, 32);
	अगर (IS_ERR_VALUE(fpi->dpram_offset)) अणु
		ret = fpi->dpram_offset;
		जाओ out_fcccp;
	पूर्ण

	वापस 0;

out_fcccp:
	iounmap(fep->fcc.fcccp);
out_ep:
	iounmap(fep->fcc.ep);
out_fccp:
	iounmap(fep->fcc.fccp);
out:
	वापस ret;
पूर्ण

#घोषणा FCC_NAPI_EVENT_MSK	(FCC_ENET_RXF | FCC_ENET_RXB | FCC_ENET_TXB)
#घोषणा FCC_EVENT		(FCC_ENET_RXF | FCC_ENET_TXB)
#घोषणा FCC_ERR_EVENT_MSK	(FCC_ENET_TXE)

अटल पूर्णांक setup_data(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	अगर (करो_pd_setup(fep) != 0)
		वापस -EINVAL;

	fep->ev_napi = FCC_NAPI_EVENT_MSK;
	fep->ev = FCC_EVENT;
	fep->ev_err = FCC_ERR_EVENT_MSK;

	वापस 0;
पूर्ण

अटल पूर्णांक allocate_bd(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;

	fep->ring_base = (व्योम __iomem __क्रमce *)dma_alloc_coherent(fep->dev,
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

	अगर (fep->ring_base)
		dma_मुक्त_coherent(fep->dev,
			(fpi->tx_ring + fpi->rx_ring) * माप(cbd_t),
			(व्योम __क्रमce *)fep->ring_base, fep->ring_mem_addr);
पूर्ण

अटल व्योम cleanup_data(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

अटल व्योम set_promiscuous_mode(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	S32(fccp, fcc_fpsmr, FCC_PSMR_PRO);
पूर्ण

अटल व्योम set_multicast_start(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_enet_t __iomem *ep = fep->fcc.ep;

	W32(ep, fen_gaddrh, 0);
	W32(ep, fen_gaddrl, 0);
पूर्ण

अटल व्योम set_multicast_one(काष्ठा net_device *dev, स्थिर u8 *mac)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_enet_t __iomem *ep = fep->fcc.ep;
	u16 taddrh, taddrm, taddrl;

	taddrh = ((u16)mac[5] << 8) | mac[4];
	taddrm = ((u16)mac[3] << 8) | mac[2];
	taddrl = ((u16)mac[1] << 8) | mac[0];

	W16(ep, fen_taddrh, taddrh);
	W16(ep, fen_taddrm, taddrm);
	W16(ep, fen_taddrl, taddrl);
	fcc_cr_cmd(fep, CPM_CR_SET_GADDR);
पूर्ण

अटल व्योम set_multicast_finish(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;
	fcc_enet_t __iomem *ep = fep->fcc.ep;

	/* clear promiscuous always */
	C32(fccp, fcc_fpsmr, FCC_PSMR_PRO);

	/* अगर all multi or too many multicasts; just enable all */
	अगर ((dev->flags & IFF_ALLMULTI) != 0 ||
	    netdev_mc_count(dev) > FCC_MAX_MULTICAST_ADDRS) अणु

		W32(ep, fen_gaddrh, 0xffffffff);
		W32(ep, fen_gaddrl, 0xffffffff);
	पूर्ण

	/* पढ़ो back */
	fep->fcc.gaddrh = R32(ep, fen_gaddrh);
	fep->fcc.gaddrl = R32(ep, fen_gaddrl);
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
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	fcc_t __iomem *fccp = fep->fcc.fccp;
	fcc_c_t __iomem *fcccp = fep->fcc.fcccp;
	fcc_enet_t __iomem *ep = fep->fcc.ep;
	dma_addr_t rx_bd_base_phys, tx_bd_base_phys;
	u16 paddrh, paddrm, paddrl;
	स्थिर अचिन्हित अक्षर *mac;
	पूर्णांक i;

	C32(fccp, fcc_gfmr, FCC_GFMR_ENR | FCC_GFMR_ENT);

	/* clear everything (slow & steady करोes it) */
	क्रम (i = 0; i < माप(*ep); i++)
		out_8((u8 __iomem *)ep + i, 0);

	/* get physical address */
	rx_bd_base_phys = fep->ring_mem_addr;
	tx_bd_base_phys = rx_bd_base_phys + माप(cbd_t) * fpi->rx_ring;

	/* poपूर्णांक to bds */
	W32(ep, fen_genfcc.fcc_rbase, rx_bd_base_phys);
	W32(ep, fen_genfcc.fcc_tbase, tx_bd_base_phys);

	/* Set maximum bytes per receive buffer.
	 * It must be a multiple of 32.
	 */
	W16(ep, fen_genfcc.fcc_mrblr, PKT_MAXBLR_SIZE);

	W32(ep, fen_genfcc.fcc_rstate, (CPMFCR_GBL | CPMFCR_EB) << 24);
	W32(ep, fen_genfcc.fcc_tstate, (CPMFCR_GBL | CPMFCR_EB) << 24);

	/* Allocate space in the reserved FCC area of DPRAM क्रम the
	 * पूर्णांकernal buffers.  No one uses this space (yet), so we
	 * can करो this.  Later, we will add resource management क्रम
	 * this area.
	 */

	W16(ep, fen_genfcc.fcc_riptr, fpi->dpram_offset);
	W16(ep, fen_genfcc.fcc_tiptr, fpi->dpram_offset + 32);

	W16(ep, fen_padptr, fpi->dpram_offset + 64);

	/* fill with special symbol...  */
	स_रखो_io(fep->fcc.mem + fpi->dpram_offset + 64, 0x88, 32);

	W32(ep, fen_genfcc.fcc_rbptr, 0);
	W32(ep, fen_genfcc.fcc_tbptr, 0);
	W32(ep, fen_genfcc.fcc_rcrc, 0);
	W32(ep, fen_genfcc.fcc_tcrc, 0);
	W16(ep, fen_genfcc.fcc_res1, 0);
	W32(ep, fen_genfcc.fcc_res2, 0);

	/* no CAM */
	W32(ep, fen_camptr, 0);

	/* Set CRC preset and mask */
	W32(ep, fen_cmask, 0xdebb20e3);
	W32(ep, fen_cpres, 0xffffffff);

	W32(ep, fen_crcec, 0);		/* CRC Error counter       */
	W32(ep, fen_alec, 0);		/* alignment error counter */
	W32(ep, fen_disfc, 0);		/* discard frame counter   */
	W16(ep, fen_retlim, 15);	/* Retry limit threshold   */
	W16(ep, fen_pper, 0);		/* Normal persistence      */

	/* set group address */
	W32(ep, fen_gaddrh, fep->fcc.gaddrh);
	W32(ep, fen_gaddrl, fep->fcc.gaddrh);

	/* Clear hash filter tables */
	W32(ep, fen_iaddrh, 0);
	W32(ep, fen_iaddrl, 0);

	/* Clear the Out-of-sequence TxBD  */
	W16(ep, fen_tfcstat, 0);
	W16(ep, fen_tfclen, 0);
	W32(ep, fen_tfcptr, 0);

	W16(ep, fen_mflr, PKT_MAXBUF_SIZE);	/* maximum frame length रेजिस्टर */
	W16(ep, fen_minflr, PKT_MINBUF_SIZE);	/* minimum frame length रेजिस्टर */

	/* set address */
	mac = dev->dev_addr;
	paddrh = ((u16)mac[5] << 8) | mac[4];
	paddrm = ((u16)mac[3] << 8) | mac[2];
	paddrl = ((u16)mac[1] << 8) | mac[0];

	W16(ep, fen_paddrh, paddrh);
	W16(ep, fen_paddrm, paddrm);
	W16(ep, fen_paddrl, paddrl);

	W16(ep, fen_taddrh, 0);
	W16(ep, fen_taddrm, 0);
	W16(ep, fen_taddrl, 0);

	W16(ep, fen_maxd1, 1520);	/* maximum DMA1 length */
	W16(ep, fen_maxd2, 1520);	/* maximum DMA2 length */

	/* Clear stat counters, in हाल we ever enable RMON */
	W32(ep, fen_octc, 0);
	W32(ep, fen_colc, 0);
	W32(ep, fen_broc, 0);
	W32(ep, fen_mulc, 0);
	W32(ep, fen_uspc, 0);
	W32(ep, fen_frgc, 0);
	W32(ep, fen_ospc, 0);
	W32(ep, fen_jbrc, 0);
	W32(ep, fen_p64c, 0);
	W32(ep, fen_p65c, 0);
	W32(ep, fen_p128c, 0);
	W32(ep, fen_p256c, 0);
	W32(ep, fen_p512c, 0);
	W32(ep, fen_p1024c, 0);

	W16(ep, fen_rfthr, 0);	/* Suggested by manual */
	W16(ep, fen_rfcnt, 0);
	W16(ep, fen_cftype, 0);

	fs_init_bds(dev);

	/* adjust to speed (क्रम RMII mode) */
	अगर (fpi->use_rmii) अणु
		अगर (dev->phydev->speed == 100)
			C8(fcccp, fcc_gfemr, 0x20);
		अन्यथा
			S8(fcccp, fcc_gfemr, 0x20);
	पूर्ण

	fcc_cr_cmd(fep, CPM_CR_INIT_TRX);

	/* clear events */
	W16(fccp, fcc_fcce, 0xffff);

	/* Enable पूर्णांकerrupts we wish to service */
	W16(fccp, fcc_fccm, FCC_ENET_TXE | FCC_ENET_RXF | FCC_ENET_TXB);

	/* Set GFMR to enable Ethernet operating mode */
	W32(fccp, fcc_gfmr, FCC_GFMR_TCI | FCC_GFMR_MODE_ENET);

	/* set sync/delimiters */
	W16(fccp, fcc_fdsr, 0xd555);

	W32(fccp, fcc_fpsmr, FCC_PSMR_ENCRC);

	अगर (fpi->use_rmii)
		S32(fccp, fcc_fpsmr, FCC_PSMR_RMII);

	/* adjust to duplex mode */
	अगर (dev->phydev->duplex)
		S32(fccp, fcc_fpsmr, FCC_PSMR_FDE | FCC_PSMR_LPB);
	अन्यथा
		C32(fccp, fcc_fpsmr, FCC_PSMR_FDE | FCC_PSMR_LPB);

	/* Restore multicast and promiscuous settings */
	set_multicast_list(dev);

	S32(fccp, fcc_gfmr, FCC_GFMR_ENR | FCC_GFMR_ENT);
पूर्ण

अटल व्योम stop(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	/* stop ethernet */
	C32(fccp, fcc_gfmr, FCC_GFMR_ENR | FCC_GFMR_ENT);

	/* clear events */
	W16(fccp, fcc_fcce, 0xffff);

	/* clear पूर्णांकerrupt mask */
	W16(fccp, fcc_fccm, 0);

	fs_cleanup_bds(dev);
पूर्ण

अटल व्योम napi_clear_event_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	W16(fccp, fcc_fcce, FCC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम napi_enable_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	S16(fccp, fcc_fccm, FCC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम napi_disable_fs(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	C16(fccp, fcc_fccm, FCC_NAPI_EVENT_MSK);
पूर्ण

अटल व्योम rx_bd_करोne(काष्ठा net_device *dev)
अणु
	/* nothing */
पूर्ण

अटल व्योम tx_kickstart(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	S16(fccp, fcc_ftodr, 0x8000);
पूर्ण

अटल u32 get_पूर्णांक_events(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	वापस (u32)R16(fccp, fcc_fcce);
पूर्ण

अटल व्योम clear_पूर्णांक_events(काष्ठा net_device *dev, u32 पूर्णांक_events)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	W16(fccp, fcc_fcce, पूर्णांक_events & 0xffff);
पूर्ण

अटल व्योम ev_error(काष्ठा net_device *dev, u32 पूर्णांक_events)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	dev_warn(fep->dev, "FS_ENET ERROR(s) 0x%x\n", पूर्णांक_events);
पूर्ण

अटल पूर्णांक get_regs(काष्ठा net_device *dev, व्योम *p, पूर्णांक *sizep)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);

	अगर (*sizep < माप(fcc_t) + माप(fcc_enet_t) + 1)
		वापस -EINVAL;

	स_नकल_fromio(p, fep->fcc.fccp, माप(fcc_t));
	p = (अक्षर *)p + माप(fcc_t);

	स_नकल_fromio(p, fep->fcc.ep, माप(fcc_enet_t));
	p = (अक्षर *)p + माप(fcc_enet_t);

	स_नकल_fromio(p, fep->fcc.fcccp, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	वापस माप(fcc_t) + माप(fcc_enet_t) + 1;
पूर्ण

/* Some transmit errors cause the transmitter to shut
 * करोwn.  We now issue a restart transmit.
 * Also, to workaround 8260 device erratum CPM37, we must
 * disable and then re-enable the transmitterfollowing a
 * Late Collision, Underrun, or Retry Limit error.
 * In addition, tbptr may poपूर्णांक beyond BDs beyond still marked
 * as पढ़ोy due to पूर्णांकernal pipelining, so we need to look back
 * through the BDs and adjust tbptr to poपूर्णांक to the last BD
 * marked as पढ़ोy.  This may result in some buffers being
 * retransmitted.
 */
अटल व्योम tx_restart(काष्ठा net_device *dev)
अणु
	काष्ठा fs_enet_निजी *fep = netdev_priv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;
	स्थिर काष्ठा fs_platक्रमm_info *fpi = fep->fpi;
	fcc_enet_t __iomem *ep = fep->fcc.ep;
	cbd_t __iomem *curr_tbptr;
	cbd_t __iomem *recheck_bd;
	cbd_t __iomem *prev_bd;
	cbd_t __iomem *last_tx_bd;

	last_tx_bd = fep->tx_bd_base + (fpi->tx_ring - 1);

	/* get the current bd held in TBPTR  and scan back from this poपूर्णांक */
	recheck_bd = curr_tbptr = (cbd_t __iomem *)
		((R32(ep, fen_genfcc.fcc_tbptr) - fep->ring_mem_addr) +
		fep->ring_base);

	prev_bd = (recheck_bd == fep->tx_bd_base) ? last_tx_bd : recheck_bd - 1;

	/* Move through the bds in reverse, look क्रम the earliest buffer
	 * that is not पढ़ोy.  Adjust TBPTR to the following buffer */
	जबतक ((CBDR_SC(prev_bd) & BD_ENET_TX_READY) != 0) अणु
		/* Go back one buffer */
		recheck_bd = prev_bd;

		/* update the previous buffer */
		prev_bd = (prev_bd == fep->tx_bd_base) ? last_tx_bd : prev_bd - 1;

		/* We should never see all bds marked as पढ़ोy, check anyway */
		अगर (recheck_bd == curr_tbptr)
			अवरोध;
	पूर्ण
	/* Now update the TBPTR and dirty flag to the current buffer */
	W32(ep, fen_genfcc.fcc_tbptr,
		(uपूर्णांक) (((व्योम *)recheck_bd - fep->ring_base) +
		fep->ring_mem_addr));
	fep->dirty_tx = recheck_bd;

	C32(fccp, fcc_gfmr, FCC_GFMR_ENT);
	udelay(10);
	S32(fccp, fcc_gfmr, FCC_GFMR_ENT);

	fcc_cr_cmd(fep, CPM_CR_RESTART_TX);
पूर्ण

/*************************************************************************/

स्थिर काष्ठा fs_ops fs_fcc_ops = अणु
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
