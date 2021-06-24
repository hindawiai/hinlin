<शैली गुरु>
/* lasi_82596.c -- driver क्रम the पूर्णांकel 82596 ethernet controller, as
   munged पूर्णांकo HPPA boxen .

   This driver is based upon 82596.c, original credits are below...
   but there were too many hoops which HP wants jumped through to
   keep this code in there in a sane manner.

   3 primary sources of the mess --
   1) hppa needs *lots* of cacheline flushing to keep this kind of
   MMIO running.

   2) The 82596 needs to see all of its poपूर्णांकers as their physical
   address.  Thus virt_to_bus/bus_to_virt are *everywhere*.

   3) The implementation HP is using seems to be signअगरicantly pickier
   about when and how the command and RX units are started.  some
   command ordering was changed.

   Examination of the mach driver leads one to believe that there
   might be a saner way to pull this off...  anyone who feels like a
   full reग_लिखो can be my guest.

   Split 02/13/2000 Sam Creasey (sammy@oh.verio.com)

   02/01/2000  Initial modअगरications क्रम parisc by Helge Deller (deller@gmx.de)
   03/02/2000  changes क्रम better/correct(?) cache-flushing (deller)
*/

/* 82596.c: A generic 82596 ethernet driver क्रम linux. */
/*
   Based on Apricot.c
   Written 1994 by Mark Evans.
   This driver is क्रम the Apricot 82596 bus-master पूर्णांकerface

   Modularised 12/94 Mark Evans


   Modअगरied to support the 82596 ethernet chips on 680x0 VME boards.
   by Riअक्षरd Hirst <riअक्षरd@sleepie.demon.co.uk>
   Renamed to be 82596.c

   980825:  Changed to receive directly in to sk_buffs which are
   allocated at खोलो() समय.  Eliminates copy on incoming frames
   (small ones are still copied).  Shared data now held in a
   non-cached page, so we can run on 68060 in copyback mode.

   TBD:
   * look at deferring rx frames rather than discarding (as per tulip)
   * handle tx ring full as per tulip
   * perक्रमmance test to tune rx_copyअवरोध

   Most of my modअगरications relate to the braindead big-endian
   implementation by Intel.  When the i596 is operating in
   'big-endian' mode, it thinks a 32 bit value of 0x12345678
   should be stored as 0x56781234.  This is a real pain, when
   you have linked lists which are shared by the 680x0 and the
   i596.

   Driver skeleton
   Written 1993 by Donald Becker.
   Copyright 1993 United States Government as represented by the Director,
   National Security Agency. This software may only be used and distributed
   according to the terms of the GNU General Public License as modअगरied by SRC,
   incorporated herein by reference.

   The author may be reached as becker@scyld.com, or C/O
   Scyld Computing Corporation, 410 Severn Ave., Suite 210, Annapolis MD 21403

 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/parisc-device.h>

#घोषणा LASI_82596_DRIVER_VERSION "LASI 82596 driver - Revision: 1.30"

#घोषणा PA_I82596_RESET		0	/* Offsets relative to LASI-LAN-Addr.*/
#घोषणा PA_CPU_PORT_L_ACCESS	4
#घोषणा PA_CHANNEL_ATTENTION	8

#घोषणा OPT_SWAP_PORT	0x0001	/* Need to wordswp on the MPU port */

#घोषणा SYSBUS      0x0000006c

/* big endian CPU, 82596 "big" endian mode */
#घोषणा SWAP32(x)   (((u32)(x)<<16) | ((((u32)(x)))>>16))
#घोषणा SWAP16(x)   (x)

#घोषणा NONCOHERENT_DMA 1

#समावेश "lib82596.c"

MODULE_AUTHOR("Richard Hirst");
MODULE_DESCRIPTION("i82596 driver");
MODULE_LICENSE("GPL");
module_param(i596_debug, पूर्णांक, 0);
MODULE_PARM_DESC(i596_debug, "lasi_82596 debug mask");

अटल अंतरभूत व्योम ca(काष्ठा net_device *dev)
अणु
	gsc_ग_लिखोl(0, dev->base_addr + PA_CHANNEL_ATTENTION);
पूर्ण


अटल व्योम mpu_port(काष्ठा net_device *dev, पूर्णांक c, dma_addr_t x)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);

	u32 v = (u32) (c) | (u32) (x);
	u16 a, b;

	अगर (lp->options & OPT_SWAP_PORT) अणु
		a = v >> 16;
		b = v & 0xffff;
	पूर्ण अन्यथा अणु
		a = v & 0xffff;
		b = v >> 16;
	पूर्ण

	gsc_ग_लिखोl(a, dev->base_addr + PA_CPU_PORT_L_ACCESS);
	अगर (!running_on_qemu)
		udelay(1);
	gsc_ग_लिखोl(b, dev->base_addr + PA_CPU_PORT_L_ACCESS);
पूर्ण

#घोषणा LAN_PROM_ADDR	0xF0810000

अटल पूर्णांक __init
lan_init_chip(काष्ठा parisc_device *dev)
अणु
	काष्ठा	net_device *netdevice;
	काष्ठा i596_निजी *lp;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक i;

	अगर (!dev->irq) अणु
		prपूर्णांकk(KERN_ERR "%s: IRQ not found for i82596 at 0x%lx\n",
			__खाता__, (अचिन्हित दीर्घ)dev->hpa.start);
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Found i82596 at 0x%lx, IRQ %d\n",
			(अचिन्हित दीर्घ)dev->hpa.start, dev->irq);

	netdevice = alloc_etherdev(माप(काष्ठा i596_निजी));
	अगर (!netdevice)
		वापस -ENOMEM;
	SET_NETDEV_DEV(netdevice, &dev->dev);
	parisc_set_drvdata (dev, netdevice);

	netdevice->base_addr = dev->hpa.start;
	netdevice->irq = dev->irq;

	अगर (pdc_lan_station_id(netdevice->dev_addr, netdevice->base_addr)) अणु
		क्रम (i = 0; i < 6; i++) अणु
			netdevice->dev_addr[i] = gsc_पढ़ोb(LAN_PROM_ADDR + i);
		पूर्ण
		prपूर्णांकk(KERN_INFO
		       "%s: MAC of HP700 LAN read from EEPROM\n", __खाता__);
	पूर्ण

	lp = netdev_priv(netdevice);
	lp->options = dev->id.sversion == 0x72 ? OPT_SWAP_PORT : 0;
	lp->dma = dma_alloc_noncoherent(&dev->dev,
			माप(काष्ठा i596_dma), &lp->dma_addr,
			DMA_BIसूचीECTIONAL, GFP_KERNEL);
	अगर (!lp->dma)
		जाओ out_मुक्त_netdev;

	retval = i82596_probe(netdevice);
	अगर (retval)
		जाओ out_मुक्त_dma;
	वापस 0;

out_मुक्त_dma:
	dma_मुक्त_noncoherent(&dev->dev, माप(काष्ठा i596_dma),
		       lp->dma, lp->dma_addr, DMA_BIसूचीECTIONAL);
out_मुक्त_netdev:
	मुक्त_netdev(netdevice);
	वापस retval;
पूर्ण

अटल पूर्णांक __निकास lan_हटाओ_chip(काष्ठा parisc_device *pdev)
अणु
	काष्ठा net_device *dev = parisc_get_drvdata(pdev);
	काष्ठा i596_निजी *lp = netdev_priv(dev);

	unरेजिस्टर_netdev (dev);
	dma_मुक्त_noncoherent(&pdev->dev, माप(काष्ठा i596_निजी), lp->dma,
		       lp->dma_addr, DMA_BIसूचीECTIONAL);
	मुक्त_netdev (dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id lan_tbl[] __initस्थिर = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0008a पूर्ण,
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00072 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, lan_tbl);

अटल काष्ठा parisc_driver lan_driver __refdata = अणु
	.name		= "lasi_82596",
	.id_table	= lan_tbl,
	.probe		= lan_init_chip,
	.हटाओ         = __निकास_p(lan_हटाओ_chip),
पूर्ण;

अटल पूर्णांक lasi_82596_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO LASI_82596_DRIVER_VERSION "\n");
	वापस रेजिस्टर_parisc_driver(&lan_driver);
पूर्ण

module_init(lasi_82596_init);

अटल व्योम __निकास lasi_82596_निकास(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&lan_driver);
पूर्ण

module_निकास(lasi_82596_निकास);
