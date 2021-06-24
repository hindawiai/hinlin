<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)
  * All rights reserved.  www.lanmedia.com
  * Generic HDLC port Copyright (C) 2008 Krzysztof Halasa <khc@pm.waw.pl>
  *
  * This code is written by:
  * Andrew Stanley-Jones (asj@cban.com)
  * Rob Braun (bbraun@vix.com),
  * Michael Graff (explorer@vix.com) and
  * Matt Thomas (matt@3am-software.com).
  *
  * With Help By:
  * David Boggs
  * Ron Crane
  * Alan Cox
  *
  * Driver क्रम the LanMedia LMC5200, LMC5245, LMC1000, LMC1200 cards.
  *
  * To control link specअगरic options lmcctl is required.
  * It can be obtained from ftp.lanmedia.com.
  *
  * Linux driver notes:
  * Linux uses the device काष्ठा lmc_निजी to pass निजी inक्रमmation
  * around.
  *
  * The initialization portion of this driver (the lmc_reset() and the
  * lmc_dec_reset() functions, as well as the led controls and the
  * lmc_initcsrs() functions.
  *
  * The watchकरोg function runs every second and checks to see अगर
  * we still have link, and that the timing source is what we expected
  * it to be.  If link is lost, the पूर्णांकerface is marked करोwn, and
  * we no दीर्घer can transmit.
  */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/processor.h>             /* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/uaccess.h>
//#समावेश <यंत्र/spinlock.h>

#घोषणा DRIVER_MAJOR_VERSION     1
#घोषणा DRIVER_MINOR_VERSION    34
#घोषणा DRIVER_SUB_VERSION       0

#घोषणा DRIVER_VERSION  ((DRIVER_MAJOR_VERSION << 8) + DRIVER_MINOR_VERSION)

#समावेश "lmc.h"
#समावेश "lmc_var.h"
#समावेश "lmc_ioctl.h"
#समावेश "lmc_debug.h"
#समावेश "lmc_proto.h"

अटल पूर्णांक LMC_PKT_BUF_SZ = 1542;

अटल स्थिर काष्ठा pci_device_id lmc_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP_FAST,
	  PCI_VENDOR_ID_LMC, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP_FAST,
	  PCI_ANY_ID, PCI_VENDOR_ID_LMC पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, lmc_pci_tbl);
MODULE_LICENSE("GPL v2");


अटल netdev_tx_t lmc_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);
अटल पूर्णांक lmc_rx (काष्ठा net_device *dev);
अटल पूर्णांक lmc_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक lmc_बंद(काष्ठा net_device *dev);
अटल काष्ठा net_device_stats *lmc_get_stats(काष्ठा net_device *dev);
अटल irqवापस_t lmc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम lmc_initcsrs(lmc_softc_t * स्थिर sc, lmc_csrptr_t csr_base, माप_प्रकार csr_size);
अटल व्योम lmc_softreset(lmc_softc_t * स्थिर);
अटल व्योम lmc_running_reset(काष्ठा net_device *dev);
अटल पूर्णांक lmc_अगरकरोwn(काष्ठा net_device * स्थिर);
अटल व्योम lmc_watchकरोg(काष्ठा समयr_list *t);
अटल व्योम lmc_reset(lmc_softc_t * स्थिर sc);
अटल व्योम lmc_dec_reset(lmc_softc_t * स्थिर sc);
अटल व्योम lmc_driver_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/*
 * linux reserves 16 device specअगरic IOCTLs.  We call them
 * LMCIOC* to control various bits of our world.
 */
पूर्णांक lmc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd) /*fold00*/
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    lmc_ctl_t ctl;
    पूर्णांक ret = -EOPNOTSUPP;
    u16 regVal;
    अचिन्हित दीर्घ flags;

    /*
     * Most functions mess with the काष्ठाure
     * Disable पूर्णांकerrupts जबतक we करो the polling
     */

    चयन (cmd) अणु
        /*
         * Return current driver state.  Since we keep this up
         * To date पूर्णांकernally, just copy this out to the user.
         */
    हाल LMCIOCGINFO: /*fold01*/
	अगर (copy_to_user(अगरr->अगरr_data, &sc->ictl, माप(lmc_ctl_t)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
        अवरोध;

    हाल LMCIOCSINFO: /*fold01*/
        अगर (!capable(CAP_NET_ADMIN)) अणु
            ret = -EPERM;
            अवरोध;
        पूर्ण

        अगर(dev->flags & IFF_UP)अणु
            ret = -EBUSY;
            अवरोध;
        पूर्ण

	अगर (copy_from_user(&ctl, अगरr->अगरr_data, माप(lmc_ctl_t))) अणु
		ret = -EFAULT;
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&sc->lmc_lock, flags);
        sc->lmc_media->set_status (sc, &ctl);

        अगर(ctl.crc_length != sc->ictl.crc_length) अणु
            sc->lmc_media->set_crc_length(sc, ctl.crc_length);
	    अगर (sc->ictl.crc_length == LMC_CTL_CRC_LENGTH_16)
		sc->TxDescriptControlInit |=  LMC_TDES_ADD_CRC_DISABLE;
	    अन्यथा
		sc->TxDescriptControlInit &= ~LMC_TDES_ADD_CRC_DISABLE;
        पूर्ण
	spin_unlock_irqrestore(&sc->lmc_lock, flags);

        ret = 0;
        अवरोध;

    हाल LMCIOCIFTYPE: /*fold01*/
        अणु
	    u16 old_type = sc->अगर_type;
	    u16	new_type;

	    अगर (!capable(CAP_NET_ADMIN)) अणु
		ret = -EPERM;
		अवरोध;
	    पूर्ण

	    अगर (copy_from_user(&new_type, अगरr->अगरr_data, माप(u16))) अणु
		ret = -EFAULT;
		अवरोध;
	    पूर्ण

            
	    अगर (new_type == old_type)
	    अणु
		ret = 0 ;
		अवरोध;				/* no change */
            पूर्ण
            
	    spin_lock_irqsave(&sc->lmc_lock, flags);
            lmc_proto_बंद(sc);

            sc->अगर_type = new_type;
            lmc_proto_attach(sc);
	    ret = lmc_proto_खोलो(sc);
	    spin_unlock_irqrestore(&sc->lmc_lock, flags);
	    अवरोध;
	पूर्ण

    हाल LMCIOCGETXINFO: /*fold01*/
	spin_lock_irqsave(&sc->lmc_lock, flags);
        sc->lmc_xinfo.Magic0 = 0xBEEFCAFE;

        sc->lmc_xinfo.PciCardType = sc->lmc_cardtype;
        sc->lmc_xinfo.PciSlotNumber = 0;
        sc->lmc_xinfo.DriverMajorVersion = DRIVER_MAJOR_VERSION;
        sc->lmc_xinfo.DriverMinorVersion = DRIVER_MINOR_VERSION;
        sc->lmc_xinfo.DriverSubVersion = DRIVER_SUB_VERSION;
        sc->lmc_xinfo.XilinxRevisionNumber =
            lmc_mii_पढ़ोreg (sc, 0, 3) & 0xf;
        sc->lmc_xinfo.MaxFrameSize = LMC_PKT_BUF_SZ;
        sc->lmc_xinfo.link_status = sc->lmc_media->get_link_status (sc);
        sc->lmc_xinfo.mii_reg16 = lmc_mii_पढ़ोreg (sc, 0, 16);
	spin_unlock_irqrestore(&sc->lmc_lock, flags);

        sc->lmc_xinfo.Magic1 = 0xDEADBEEF;

        अगर (copy_to_user(अगरr->अगरr_data, &sc->lmc_xinfo,
			 माप(काष्ठा lmc_xinfo)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;

        अवरोध;

    हाल LMCIOCGETLMCSTATS:
	    spin_lock_irqsave(&sc->lmc_lock, flags);
	    अगर (sc->lmc_cardtype == LMC_CARDTYPE_T1) अणु
		    lmc_mii_ग_लिखोreg(sc, 0, 17, T1FRAMER_FERR_LSB);
		    sc->extra_stats.framingBitErrorCount +=
			    lmc_mii_पढ़ोreg(sc, 0, 18) & 0xff;
		    lmc_mii_ग_लिखोreg(sc, 0, 17, T1FRAMER_FERR_MSB);
		    sc->extra_stats.framingBitErrorCount +=
			    (lmc_mii_पढ़ोreg(sc, 0, 18) & 0xff) << 8;
		    lmc_mii_ग_लिखोreg(sc, 0, 17, T1FRAMER_LCV_LSB);
		    sc->extra_stats.lineCodeViolationCount +=
			    lmc_mii_पढ़ोreg(sc, 0, 18) & 0xff;
		    lmc_mii_ग_लिखोreg(sc, 0, 17, T1FRAMER_LCV_MSB);
		    sc->extra_stats.lineCodeViolationCount +=
			    (lmc_mii_पढ़ोreg(sc, 0, 18) & 0xff) << 8;
		    lmc_mii_ग_लिखोreg(sc, 0, 17, T1FRAMER_AERR);
		    regVal = lmc_mii_पढ़ोreg(sc, 0, 18) & 0xff;

		    sc->extra_stats.lossOfFrameCount +=
			    (regVal & T1FRAMER_LOF_MASK) >> 4;
		    sc->extra_stats.changeOfFrameAlignmentCount +=
			    (regVal & T1FRAMER_COFA_MASK) >> 2;
		    sc->extra_stats.severelyErroredFrameCount +=
			    regVal & T1FRAMER_SEF_MASK;
	    पूर्ण
	    spin_unlock_irqrestore(&sc->lmc_lock, flags);
	    अगर (copy_to_user(अगरr->अगरr_data, &sc->lmc_device->stats,
			     माप(sc->lmc_device->stats)) ||
		copy_to_user(अगरr->अगरr_data + माप(sc->lmc_device->stats),
			     &sc->extra_stats, माप(sc->extra_stats)))
		    ret = -EFAULT;
	    अन्यथा
		    ret = 0;
	    अवरोध;

    हाल LMCIOCCLEARLMCSTATS:
	    अगर (!capable(CAP_NET_ADMIN)) अणु
		    ret = -EPERM;
		    अवरोध;
	    पूर्ण

	    spin_lock_irqsave(&sc->lmc_lock, flags);
	    स_रखो(&sc->lmc_device->stats, 0, माप(sc->lmc_device->stats));
	    स_रखो(&sc->extra_stats, 0, माप(sc->extra_stats));
	    sc->extra_stats.check = STATCHECK;
	    sc->extra_stats.version_size = (DRIVER_VERSION << 16) +
		    माप(sc->lmc_device->stats) + माप(sc->extra_stats);
	    sc->extra_stats.lmc_cardtype = sc->lmc_cardtype;
	    spin_unlock_irqrestore(&sc->lmc_lock, flags);
	    ret = 0;
	    अवरोध;

    हाल LMCIOCSETCIRCUIT: /*fold01*/
        अगर (!capable(CAP_NET_ADMIN))अणु
            ret = -EPERM;
            अवरोध;
        पूर्ण

        अगर(dev->flags & IFF_UP)अणु
            ret = -EBUSY;
            अवरोध;
        पूर्ण

	अगर (copy_from_user(&ctl, अगरr->अगरr_data, माप(lmc_ctl_t))) अणु
		ret = -EFAULT;
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&sc->lmc_lock, flags);
        sc->lmc_media->set_circuit_type(sc, ctl.circuit_type);
        sc->ictl.circuit_type = ctl.circuit_type;
	spin_unlock_irqrestore(&sc->lmc_lock, flags);
        ret = 0;

        अवरोध;

    हाल LMCIOCRESET: /*fold01*/
        अगर (!capable(CAP_NET_ADMIN))अणु
            ret = -EPERM;
            अवरोध;
        पूर्ण

	spin_lock_irqsave(&sc->lmc_lock, flags);
        /* Reset driver and bring back to current state */
        prपूर्णांकk (" REG16 before reset +%04x\n", lmc_mii_पढ़ोreg (sc, 0, 16));
        lmc_running_reset (dev);
        prपूर्णांकk (" REG16 after reset +%04x\n", lmc_mii_पढ़ोreg (sc, 0, 16));

        LMC_EVENT_LOG(LMC_EVENT_FORCEDRESET, LMC_CSR_READ (sc, csr_status), lmc_mii_पढ़ोreg (sc, 0, 16));
	spin_unlock_irqrestore(&sc->lmc_lock, flags);

        ret = 0;
        अवरोध;

#अगर_घोषित DEBUG
    हाल LMCIOCDUMPEVENTLOG:
	अगर (copy_to_user(अगरr->अगरr_data, &lmcEventLogIndex, माप(u32))) अणु
		ret = -EFAULT;
		अवरोध;
	पूर्ण
	अगर (copy_to_user(अगरr->अगरr_data + माप(u32), lmcEventLogBuf,
			 माप(lmcEventLogBuf)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;

        अवरोध;
#पूर्ण_अगर /* end अगरdef _DBG_EVENTLOG */
    हाल LMCIOCT1CONTROL: /*fold01*/
        अगर (sc->lmc_cardtype != LMC_CARDTYPE_T1)अणु
            ret = -EOPNOTSUPP;
            अवरोध;
        पूर्ण
        अवरोध;
    हाल LMCIOCXILINX: /*fold01*/
        अणु
            काष्ठा lmc_xilinx_control xc; /*fold02*/

            अगर (!capable(CAP_NET_ADMIN))अणु
                ret = -EPERM;
                अवरोध;
            पूर्ण

            /*
             * Stop the xwitter whlie we restart the hardware
             */
            netअगर_stop_queue(dev);

	    अगर (copy_from_user(&xc, अगरr->अगरr_data, माप(काष्ठा lmc_xilinx_control))) अणु
		ret = -EFAULT;
		अवरोध;
	    पूर्ण
            चयन(xc.command)अणु
            हाल lmc_xilinx_reset: /*fold02*/
                अणु
		    spin_lock_irqsave(&sc->lmc_lock, flags);
                    lmc_mii_पढ़ोreg (sc, 0, 16);

                    /*
                     * Make all of them 0 and make input
                     */
                    lmc_gpio_mkinput(sc, 0xff);

                    /*
                     * make the reset output
                     */
                    lmc_gpio_mkoutput(sc, LMC_GEP_RESET);

                    /*
                     * RESET low to क्रमce configuration.  This also क्रमces
                     * the transmitter घड़ी to be पूर्णांकernal, but we expect to reset
                     * that later anyway.
                     */

                    sc->lmc_gpio &= ~LMC_GEP_RESET;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);


                    /*
                     * hold क्रम more than 10 microseconds
                     */
                    udelay(50);

                    sc->lmc_gpio |= LMC_GEP_RESET;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);


                    /*
                     * stop driving Xilinx-related संकेतs
                     */
                    lmc_gpio_mkinput(sc, 0xff);

                    /* Reset the frammer hardware */
                    sc->lmc_media->set_link_status (sc, 1);
                    sc->lmc_media->set_status (sc, शून्य);
//                    lmc_softreset(sc);

                    अणु
                        पूर्णांक i;
                        क्रम(i = 0; i < 5; i++)अणु
                            lmc_led_on(sc, LMC_DS3_LED0);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED0);
                            lmc_led_on(sc, LMC_DS3_LED1);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED1);
                            lmc_led_on(sc, LMC_DS3_LED3);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED3);
                            lmc_led_on(sc, LMC_DS3_LED2);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED2);
                        पूर्ण
                    पूर्ण
		    spin_unlock_irqrestore(&sc->lmc_lock, flags);
                    
                    

                    ret = 0x0;

                पूर्ण

                अवरोध;
            हाल lmc_xilinx_load_prom: /*fold02*/
                अणु
                    पूर्णांक समयout = 500000;
		    spin_lock_irqsave(&sc->lmc_lock, flags);
                    lmc_mii_पढ़ोreg (sc, 0, 16);

                    /*
                     * Make all of them 0 and make input
                     */
                    lmc_gpio_mkinput(sc, 0xff);

                    /*
                     * make the reset output
                     */
                    lmc_gpio_mkoutput(sc,  LMC_GEP_DP | LMC_GEP_RESET);

                    /*
                     * RESET low to क्रमce configuration.  This also क्रमces
                     * the transmitter घड़ी to be पूर्णांकernal, but we expect to reset
                     * that later anyway.
                     */

                    sc->lmc_gpio &= ~(LMC_GEP_RESET | LMC_GEP_DP);
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);


                    /*
                     * hold क्रम more than 10 microseconds
                     */
                    udelay(50);

                    sc->lmc_gpio |= LMC_GEP_DP | LMC_GEP_RESET;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);

                    /*
                     * busy रुको क्रम the chip to reset
                     */
                    जबतक( (LMC_CSR_READ(sc, csr_gp) & LMC_GEP_INIT) == 0 &&
                           (समयout-- > 0))
                        cpu_relax();


                    /*
                     * stop driving Xilinx-related संकेतs
                     */
                    lmc_gpio_mkinput(sc, 0xff);
		    spin_unlock_irqrestore(&sc->lmc_lock, flags);

                    ret = 0x0;
                    

                    अवरोध;

                पूर्ण

            हाल lmc_xilinx_load: /*fold02*/
                अणु
                    अक्षर *data;
                    पूर्णांक pos;
                    पूर्णांक समयout = 500000;

                    अगर (!xc.data) अणु
                            ret = -EINVAL;
                            अवरोध;
                    पूर्ण

                    data = memdup_user(xc.data, xc.len);
                    अगर (IS_ERR(data)) अणु
                            ret = PTR_ERR(data);
                            अवरोध;
                    पूर्ण

                    prपूर्णांकk("%s: Starting load of data Len: %d at 0x%p == 0x%p\n", dev->name, xc.len, xc.data, data);

		    spin_lock_irqsave(&sc->lmc_lock, flags);
                    lmc_gpio_mkinput(sc, 0xff);

                    /*
                     * Clear the Xilinx and start prgramming from the DEC
                     */

                    /*
                     * Set ouput as:
                     * Reset: 0 (active)
                     * DP:    0 (active)
                     * Mode:  1
                     *
                     */
                    sc->lmc_gpio = 0x00;
                    sc->lmc_gpio &= ~LMC_GEP_DP;
                    sc->lmc_gpio &= ~LMC_GEP_RESET;
                    sc->lmc_gpio |=  LMC_GEP_MODE;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);

                    lmc_gpio_mkoutput(sc, LMC_GEP_MODE | LMC_GEP_DP | LMC_GEP_RESET);

                    /*
                     * Wait at least 10 us 20 to be safe
                     */
                    udelay(50);

                    /*
                     * Clear reset and activate programming lines
                     * Reset: Input
                     * DP:    Input
                     * Clock: Output
                     * Data:  Output
                     * Mode:  Output
                     */
                    lmc_gpio_mkinput(sc, LMC_GEP_DP | LMC_GEP_RESET);

                    /*
                     * Set LOAD, DATA, Clock to 1
                     */
                    sc->lmc_gpio = 0x00;
                    sc->lmc_gpio |= LMC_GEP_MODE;
                    sc->lmc_gpio |= LMC_GEP_DATA;
                    sc->lmc_gpio |= LMC_GEP_CLK;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);
                    
                    lmc_gpio_mkoutput(sc, LMC_GEP_DATA | LMC_GEP_CLK | LMC_GEP_MODE );

                    /*
                     * busy रुको क्रम the chip to reset
                     */
                    जबतक( (LMC_CSR_READ(sc, csr_gp) & LMC_GEP_INIT) == 0 &&
                           (समयout-- > 0))
                        cpu_relax();

                    prपूर्णांकk(KERN_DEBUG "%s: Waited %d for the Xilinx to clear it's memory\n", dev->name, 500000-समयout);

                    क्रम(pos = 0; pos < xc.len; pos++)अणु
                        चयन(data[pos])अणु
                        हाल 0:
                            sc->lmc_gpio &= ~LMC_GEP_DATA; /* Data is 0 */
                            अवरोध;
                        हाल 1:
                            sc->lmc_gpio |= LMC_GEP_DATA; /* Data is 1 */
                            अवरोध;
                        शेष:
                            prपूर्णांकk(KERN_WARNING "%s Bad data in xilinx programming data at %d, got %d wanted 0 or 1\n", dev->name, pos, data[pos]);
                            sc->lmc_gpio |= LMC_GEP_DATA; /* Assume it's 1 */
                        पूर्ण
                        sc->lmc_gpio &= ~LMC_GEP_CLK; /* Clock to zero */
                        sc->lmc_gpio |= LMC_GEP_MODE;
                        LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);
                        udelay(1);
                        
                        sc->lmc_gpio |= LMC_GEP_CLK; /* Put the clack back to one */
                        sc->lmc_gpio |= LMC_GEP_MODE;
                        LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);
                        udelay(1);
                    पूर्ण
                    अगर((LMC_CSR_READ(sc, csr_gp) & LMC_GEP_INIT) == 0)अणु
                        prपूर्णांकk(KERN_WARNING "%s: Reprogramming FAILED. Needs to be reprogrammed. (corrupted data)\n", dev->name);
                    पूर्ण
                    अन्यथा अगर((LMC_CSR_READ(sc, csr_gp) & LMC_GEP_DP) == 0)अणु
                        prपूर्णांकk(KERN_WARNING "%s: Reprogramming FAILED. Needs to be reprogrammed. (done)\n", dev->name);
                    पूर्ण
                    अन्यथा अणु
                        prपूर्णांकk(KERN_DEBUG "%s: Done reprogramming Xilinx, %d bits, good luck!\n", dev->name, pos);
                    पूर्ण

                    lmc_gpio_mkinput(sc, 0xff);
                    
                    sc->lmc_miireg16 |= LMC_MII16_FIFO_RESET;
                    lmc_mii_ग_लिखोreg(sc, 0, 16, sc->lmc_miireg16);

                    sc->lmc_miireg16 &= ~LMC_MII16_FIFO_RESET;
                    lmc_mii_ग_लिखोreg(sc, 0, 16, sc->lmc_miireg16);
		    spin_unlock_irqrestore(&sc->lmc_lock, flags);

                    kमुक्त(data);
                    
                    ret = 0;
                    
                    अवरोध;
                पूर्ण
            शेष: /*fold02*/
                ret = -EBADE;
                अवरोध;
            पूर्ण

            netअगर_wake_queue(dev);
            sc->lmc_txfull = 0;

        पूर्ण
        अवरोध;
    शेष: /*fold01*/
        /* If we करोn't know what to करो, give the protocol a shot. */
        ret = lmc_proto_ioctl (sc, अगरr, cmd);
        अवरोध;
    पूर्ण

    वापस ret;
पूर्ण


/* the watchकरोg process that cruises around */
अटल व्योम lmc_watchकरोg(काष्ठा समयr_list *t) /*fold00*/
अणु
    lmc_softc_t *sc = from_समयr(sc, t, समयr);
    काष्ठा net_device *dev = sc->lmc_device;
    पूर्णांक link_status;
    u32 ticks;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&sc->lmc_lock, flags);

    अगर(sc->check != 0xBEAFCAFE)अणु
        prपूर्णांकk("LMC: Corrupt net_device struct, breaking out\n");
	spin_unlock_irqrestore(&sc->lmc_lock, flags);
        वापस;
    पूर्ण


    /* Make sure the tx jabber and rx watchकरोg are off,
     * and the transmit and receive processes are running.
     */

    LMC_CSR_WRITE (sc, csr_15, 0x00000011);
    sc->lmc_cmdmode |= TULIP_CMD_TXRUN | TULIP_CMD_RXRUN;
    LMC_CSR_WRITE (sc, csr_command, sc->lmc_cmdmode);

    अगर (sc->lmc_ok == 0)
        जाओ kick_समयr;

    LMC_EVENT_LOG(LMC_EVENT_WATCHDOG, LMC_CSR_READ (sc, csr_status), lmc_mii_पढ़ोreg (sc, 0, 16));

    /* --- begin समय out check -----------------------------------
     * check क्रम a transmit पूर्णांकerrupt समयout
     * Has the packet xmt vs xmt serviced threshold been exceeded */
    अगर (sc->lmc_taपूर्णांक_tx == sc->lastlmc_taपूर्णांक_tx &&
	sc->lmc_device->stats.tx_packets > sc->lasttx_packets &&
	sc->tx_TimeoutInd == 0)
    अणु

        /* रुको क्रम the watchकरोg to come around again */
        sc->tx_TimeoutInd = 1;
    पूर्ण
    अन्यथा अगर (sc->lmc_taपूर्णांक_tx == sc->lastlmc_taपूर्णांक_tx &&
	     sc->lmc_device->stats.tx_packets > sc->lasttx_packets &&
	     sc->tx_TimeoutInd)
    अणु

        LMC_EVENT_LOG(LMC_EVENT_XMTINTTMO, LMC_CSR_READ (sc, csr_status), 0);

        sc->tx_TimeoutDisplay = 1;
	sc->extra_stats.tx_TimeoutCnt++;

        /* DEC chip is stuck, hit it with a RESET!!!! */
        lmc_running_reset (dev);


        /* look at receive & transmit process state to make sure they are running */
        LMC_EVENT_LOG(LMC_EVENT_RESET1, LMC_CSR_READ (sc, csr_status), 0);

        /* look at: DSR - 02  क्रम Reg 16
         *                  CTS - 08
         *                  DCD - 10
         *                  RI  - 20
         * क्रम Reg 17
         */
        LMC_EVENT_LOG(LMC_EVENT_RESET2, lmc_mii_पढ़ोreg (sc, 0, 16), lmc_mii_पढ़ोreg (sc, 0, 17));

        /* reset the transmit समयout detection flag */
        sc->tx_TimeoutInd = 0;
        sc->lastlmc_taपूर्णांक_tx = sc->lmc_taपूर्णांक_tx;
	sc->lasttx_packets = sc->lmc_device->stats.tx_packets;
    पूर्ण अन्यथा अणु
        sc->tx_TimeoutInd = 0;
        sc->lastlmc_taपूर्णांक_tx = sc->lmc_taपूर्णांक_tx;
	sc->lasttx_packets = sc->lmc_device->stats.tx_packets;
    पूर्ण

    /* --- end समय out check ----------------------------------- */


    link_status = sc->lmc_media->get_link_status (sc);

    /*
     * hardware level link lost, but the पूर्णांकerface is marked as up.
     * Mark it as करोwn.
     */
    अगर ((link_status == 0) && (sc->last_link_status != 0)) अणु
        prपूर्णांकk(KERN_WARNING "%s: hardware/physical link down\n", dev->name);
        sc->last_link_status = 0;
        /* lmc_reset (sc); Why reset??? The link can go करोwn ok */

        /* Inक्रमm the world that link has been lost */
	netअगर_carrier_off(dev);
    पूर्ण

    /*
     * hardware link is up, but the पूर्णांकerface is marked as करोwn.
     * Bring it back up again.
     */
     अगर (link_status != 0 && sc->last_link_status == 0) अणु
         prपूर्णांकk(KERN_WARNING "%s: hardware/physical link up\n", dev->name);
         sc->last_link_status = 1;
         /* lmc_reset (sc); Again why reset??? */

	 netअगर_carrier_on(dev);
     पूर्ण

    /* Call media specअगरic watchकरोg functions */
    sc->lmc_media->watchकरोg(sc);

    /*
     * Poke the transmitter to make sure it
     * never stops, even अगर we run out of mem
     */
    LMC_CSR_WRITE(sc, csr_rxpoll, 0);

    /*
     * Check क्रम code that failed
     * and try and fix it as appropriate
     */
    अगर(sc->failed_ring == 1)अणु
        /*
         * Failed to setup the recv/xmit rin
         * Try again
         */
        sc->failed_ring = 0;
        lmc_softreset(sc);
    पूर्ण
    अगर(sc->failed_recv_alloc == 1)अणु
        /*
         * We failed to alloc mem in the
         * पूर्णांकerrupt handler, go through the rings
         * and rebuild them
         */
        sc->failed_recv_alloc = 0;
        lmc_softreset(sc);
    पूर्ण


    /*
     * remember the समयr value
     */
kick_समयr:

    ticks = LMC_CSR_READ (sc, csr_gp_समयr);
    LMC_CSR_WRITE (sc, csr_gp_समयr, 0xffffffffUL);
    sc->ictl.ticks = 0x0000ffff - (ticks & 0x0000ffff);

    /*
     * restart this समयr.
     */
    sc->समयr.expires = jअगरfies + (HZ);
    add_समयr (&sc->समयr);

    spin_unlock_irqrestore(&sc->lmc_lock, flags);
पूर्ण

अटल पूर्णांक lmc_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
		      अचिन्हित लघु parity)
अणु
	अगर (encoding == ENCODING_NRZ && parity == PARITY_CRC16_PR1_CCITT)
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा net_device_ops lmc_ops = अणु
	.nकरो_खोलो       = lmc_खोलो,
	.nकरो_stop       = lmc_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = lmc_ioctl,
	.nकरो_tx_समयout = lmc_driver_समयout,
	.nकरो_get_stats  = lmc_get_stats,
पूर्ण;

अटल पूर्णांक lmc_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	lmc_softc_t *sc;
	काष्ठा net_device *dev;
	u16 subdevice;
	u16 AdapModelNum;
	पूर्णांक err;
	अटल पूर्णांक cards_found;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "lmc: pci enable failed: %d\n", err);
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, "lmc");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "lmc: pci_request_region failed\n");
		वापस err;
	पूर्ण

	/*
	 * Allocate our own device काष्ठाure
	 */
	sc = devm_kzalloc(&pdev->dev, माप(lmc_softc_t), GFP_KERNEL);
	अगर (!sc)
		वापस -ENOMEM;

	dev = alloc_hdlcdev(sc);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "lmc:alloc_netdev for device failed\n");
		वापस -ENOMEM;
	पूर्ण


	dev->type = ARPHRD_HDLC;
	dev_to_hdlc(dev)->xmit = lmc_start_xmit;
	dev_to_hdlc(dev)->attach = lmc_attach;
	dev->netdev_ops = &lmc_ops;
	dev->watchकरोg_समयo = HZ; /* 1 second */
	dev->tx_queue_len = 100;
	sc->lmc_device = dev;
	sc->name = dev->name;
	sc->अगर_type = LMC_PPP;
	sc->check = 0xBEAFCAFE;
	dev->base_addr = pci_resource_start(pdev, 0);
	dev->irq = pdev->irq;
	pci_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	/*
	 * This will get the protocol layer पढ़ोy and करो any 1 समय init's
	 * Must have a valid sc and dev काष्ठाure
	 */
	lmc_proto_attach(sc);

	/* Init the spin lock so can call it latter */

	spin_lock_init(&sc->lmc_lock);
	pci_set_master(pdev);

	prपूर्णांकk(KERN_INFO "hdlc: detected at %lx, irq %d\n",
	       dev->base_addr, dev->irq);

	err = रेजिस्टर_hdlc_device(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: register_netdev failed.\n", dev->name);
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण

    sc->lmc_cardtype = LMC_CARDTYPE_UNKNOWN;
    sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_EXT;

    /*
     *
     * Check either the subvenकरोr or the subdevice, some प्रणालीs reverse
     * the setting in the bois, seems to be version and arch dependent?
     * Fix the error, exchange the two values 
     */
    अगर ((subdevice = pdev->subप्रणाली_device) == PCI_VENDOR_ID_LMC)
	    subdevice = pdev->subप्रणाली_venकरोr;

    चयन (subdevice) अणु
    हाल PCI_DEVICE_ID_LMC_HSSI:
	prपूर्णांकk(KERN_INFO "%s: LMC HSSI\n", dev->name);
        sc->lmc_cardtype = LMC_CARDTYPE_HSSI;
        sc->lmc_media = &lmc_hssi_media;
        अवरोध;
    हाल PCI_DEVICE_ID_LMC_DS3:
	prपूर्णांकk(KERN_INFO "%s: LMC DS3\n", dev->name);
        sc->lmc_cardtype = LMC_CARDTYPE_DS3;
        sc->lmc_media = &lmc_ds3_media;
        अवरोध;
    हाल PCI_DEVICE_ID_LMC_SSI:
	prपूर्णांकk(KERN_INFO "%s: LMC SSI\n", dev->name);
        sc->lmc_cardtype = LMC_CARDTYPE_SSI;
        sc->lmc_media = &lmc_ssi_media;
        अवरोध;
    हाल PCI_DEVICE_ID_LMC_T1:
	prपूर्णांकk(KERN_INFO "%s: LMC T1\n", dev->name);
        sc->lmc_cardtype = LMC_CARDTYPE_T1;
        sc->lmc_media = &lmc_t1_media;
        अवरोध;
    शेष:
	prपूर्णांकk(KERN_WARNING "%s: LMC UNKNOWN CARD!\n", dev->name);
	unरेजिस्टर_hdlc_device(dev);
	वापस -EIO;
        अवरोध;
    पूर्ण

    lmc_initcsrs (sc, dev->base_addr, 8);

    lmc_gpio_mkinput (sc, 0xff);
    sc->lmc_gpio = 0;		/* drive no संकेतs yet */

    sc->lmc_media->शेषs (sc);

    sc->lmc_media->set_link_status (sc, LMC_LINK_UP);

    /* verअगरy that the PCI Sub System ID matches the Adapter Model number
     * from the MII रेजिस्टर
     */
    AdapModelNum = (lmc_mii_पढ़ोreg (sc, 0, 3) & 0x3f0) >> 4;

    अगर ((AdapModelNum != LMC_ADAP_T1 || /* detect LMC1200 */
	 subdevice != PCI_DEVICE_ID_LMC_T1) &&
	(AdapModelNum != LMC_ADAP_SSI || /* detect LMC1000 */
	 subdevice != PCI_DEVICE_ID_LMC_SSI) &&
	(AdapModelNum != LMC_ADAP_DS3 || /* detect LMC5245 */
	 subdevice != PCI_DEVICE_ID_LMC_DS3) &&
	(AdapModelNum != LMC_ADAP_HSSI || /* detect LMC5200 */
	 subdevice != PCI_DEVICE_ID_LMC_HSSI))
	    prपूर्णांकk(KERN_WARNING "%s: Model number (%d) miscompare for PCI"
		   " Subsystem ID = 0x%04x\n",
		   dev->name, AdapModelNum, subdevice);

    /*
     * reset घड़ी
     */
    LMC_CSR_WRITE (sc, csr_gp_समयr, 0xFFFFFFFFUL);

    sc->board_idx = cards_found++;
    sc->extra_stats.check = STATCHECK;
    sc->extra_stats.version_size = (DRIVER_VERSION << 16) +
	    माप(sc->lmc_device->stats) + माप(sc->extra_stats);
    sc->extra_stats.lmc_cardtype = sc->lmc_cardtype;

    sc->lmc_ok = 0;
    sc->last_link_status = 0;

    वापस 0;
पूर्ण

/*
 * Called from pci when removing module.
 */
अटल व्योम lmc_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		prपूर्णांकk(KERN_DEBUG "%s: removing...\n", dev->name);
		unरेजिस्टर_hdlc_device(dev);
		मुक्त_netdev(dev);
	पूर्ण
पूर्ण

/* After this is called, packets can be sent.
 * Does not initialize the addresses
 */
अटल पूर्णांक lmc_खोलो(काष्ठा net_device *dev)
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    पूर्णांक err;

    lmc_led_on(sc, LMC_DS3_LED0);

    lmc_dec_reset(sc);
    lmc_reset(sc);

    LMC_EVENT_LOG(LMC_EVENT_RESET1, LMC_CSR_READ(sc, csr_status), 0);
    LMC_EVENT_LOG(LMC_EVENT_RESET2, lmc_mii_पढ़ोreg(sc, 0, 16),
		  lmc_mii_पढ़ोreg(sc, 0, 17));

    अगर (sc->lmc_ok)
        वापस 0;

    lmc_softreset (sc);

    /* Since we have to use PCI bus, this should work on x86,alpha,ppc */
    अगर (request_irq (dev->irq, lmc_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev))अणु
        prपूर्णांकk(KERN_WARNING "%s: could not get irq: %d\n", dev->name, dev->irq);
        वापस -EAGAIN;
    पूर्ण
    sc->got_irq = 1;

    /* Assert Terminal Active */
    sc->lmc_miireg16 |= LMC_MII16_LED_ALL;
    sc->lmc_media->set_link_status (sc, LMC_LINK_UP);

    /*
     * reset to last state.
     */
    sc->lmc_media->set_status (sc, शून्य);

    /* setup शेष bits to be used in tulip_desc_t transmit descriptor
     * -baz */
    sc->TxDescriptControlInit = (
                                 LMC_TDES_INTERRUPT_ON_COMPLETION
                                 | LMC_TDES_FIRST_SEGMENT
                                 | LMC_TDES_LAST_SEGMENT
                                 | LMC_TDES_SECOND_ADDR_CHAINED
                                 | LMC_TDES_DISABLE_PADDING
                                );

    अगर (sc->ictl.crc_length == LMC_CTL_CRC_LENGTH_16) अणु
        /* disable 32 bit CRC generated by ASIC */
        sc->TxDescriptControlInit |= LMC_TDES_ADD_CRC_DISABLE;
    पूर्ण
    sc->lmc_media->set_crc_length(sc, sc->ictl.crc_length);
    /* Acknoledge the Terminal Active and light LEDs */

    /* dev->flags |= IFF_UP; */

    अगर ((err = lmc_proto_खोलो(sc)) != 0)
	    वापस err;

    netअगर_start_queue(dev);
    sc->extra_stats.tx_tbusy0++;

    /*
     * select what पूर्णांकerrupts we want to get
     */
    sc->lmc_पूर्णांकrmask = 0;
    /* Should be using the शेष पूर्णांकerrupt mask defined in the .h file. */
    sc->lmc_पूर्णांकrmask |= (TULIP_STS_NORMALINTR
                         | TULIP_STS_RXINTR
                         | TULIP_STS_TXINTR
                         | TULIP_STS_ABNRMLINTR
                         | TULIP_STS_SYSERROR
                         | TULIP_STS_TXSTOPPED
                         | TULIP_STS_TXUNDERFLOW
                         | TULIP_STS_RXSTOPPED
		         | TULIP_STS_RXNOBUF
                        );
    LMC_CSR_WRITE (sc, csr_पूर्णांकr, sc->lmc_पूर्णांकrmask);

    sc->lmc_cmdmode |= TULIP_CMD_TXRUN;
    sc->lmc_cmdmode |= TULIP_CMD_RXRUN;
    LMC_CSR_WRITE (sc, csr_command, sc->lmc_cmdmode);

    sc->lmc_ok = 1; /* Run watchकरोg */

    /*
     * Set the अगर up now - pfb
     */

    sc->last_link_status = 1;

    /*
     * Setup a समयr क्रम the watchकरोg on probe, and start it running.
     * Since lmc_ok == 0, it will be a NOP क्रम now.
     */
    समयr_setup(&sc->समयr, lmc_watchकरोg, 0);
    sc->समयr.expires = jअगरfies + HZ;
    add_समयr (&sc->समयr);

    वापस 0;
पूर्ण

/* Total reset to compensate क्रम the AdTran DSU करोing bad things
 *  under heavy load
 */

अटल व्योम lmc_running_reset (काष्ठा net_device *dev) /*fold00*/
अणु
    lmc_softc_t *sc = dev_to_sc(dev);

    /* stop पूर्णांकerrupts */
    /* Clear the पूर्णांकerrupt mask */
    LMC_CSR_WRITE (sc, csr_पूर्णांकr, 0x00000000);

    lmc_dec_reset (sc);
    lmc_reset (sc);
    lmc_softreset (sc);
    /* sc->lmc_miireg16 |= LMC_MII16_LED_ALL; */
    sc->lmc_media->set_link_status (sc, 1);
    sc->lmc_media->set_status (sc, शून्य);

    netअगर_wake_queue(dev);

    sc->lmc_txfull = 0;
    sc->extra_stats.tx_tbusy0++;

    sc->lmc_पूर्णांकrmask = TULIP_DEFAULT_INTR_MASK;
    LMC_CSR_WRITE (sc, csr_पूर्णांकr, sc->lmc_पूर्णांकrmask);

    sc->lmc_cmdmode |= (TULIP_CMD_TXRUN | TULIP_CMD_RXRUN);
    LMC_CSR_WRITE (sc, csr_command, sc->lmc_cmdmode);
पूर्ण


/* This is what is called when you अगरconfig करोwn a device.
 * This disables the समयr क्रम the watchकरोg and keepalives,
 * and disables the irq क्रम dev.
 */
अटल पूर्णांक lmc_बंद(काष्ठा net_device *dev)
अणु
    /* not calling release_region() as we should */
    lmc_softc_t *sc = dev_to_sc(dev);

    sc->lmc_ok = 0;
    sc->lmc_media->set_link_status (sc, 0);
    del_समयr (&sc->समयr);
    lmc_proto_बंद(sc);
    lmc_अगरकरोwn (dev);

    वापस 0;
पूर्ण

/* Ends the transfer of packets */
/* When the पूर्णांकerface goes करोwn, this is called */
अटल पूर्णांक lmc_अगरकरोwn (काष्ठा net_device *dev) /*fold00*/
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 csr6;
    पूर्णांक i;

    /* Don't let anything अन्यथा go on right now */
    //    dev->start = 0;
    netअगर_stop_queue(dev);
    sc->extra_stats.tx_tbusy1++;

    /* stop पूर्णांकerrupts */
    /* Clear the पूर्णांकerrupt mask */
    LMC_CSR_WRITE (sc, csr_पूर्णांकr, 0x00000000);

    /* Stop Tx and Rx on the chip */
    csr6 = LMC_CSR_READ (sc, csr_command);
    csr6 &= ~LMC_DEC_ST;		/* Turn off the Transmission bit */
    csr6 &= ~LMC_DEC_SR;		/* Turn off the Receive bit */
    LMC_CSR_WRITE (sc, csr_command, csr6);

    sc->lmc_device->stats.rx_missed_errors +=
	    LMC_CSR_READ(sc, csr_missed_frames) & 0xffff;

    /* release the पूर्णांकerrupt */
    अगर(sc->got_irq == 1)अणु
        मुक्त_irq (dev->irq, dev);
        sc->got_irq = 0;
    पूर्ण

    /* मुक्त skbuffs in the Rx queue */
    क्रम (i = 0; i < LMC_RXDESCS; i++)
    अणु
        काष्ठा sk_buff *skb = sc->lmc_rxq[i];
        sc->lmc_rxq[i] = शून्य;
        sc->lmc_rxring[i].status = 0;
        sc->lmc_rxring[i].length = 0;
        sc->lmc_rxring[i].buffer1 = 0xDEADBEEF;
        अगर (skb != शून्य)
            dev_kमुक्त_skb(skb);
        sc->lmc_rxq[i] = शून्य;
    पूर्ण

    क्रम (i = 0; i < LMC_TXDESCS; i++)
    अणु
        अगर (sc->lmc_txq[i] != शून्य)
            dev_kमुक्त_skb(sc->lmc_txq[i]);
        sc->lmc_txq[i] = शून्य;
    पूर्ण

    lmc_led_off (sc, LMC_MII16_LED_ALL);

    netअगर_wake_queue(dev);
    sc->extra_stats.tx_tbusy0++;

    वापस 0;
पूर्ण

/* Interrupt handling routine.  This will take an incoming packet, or clean
 * up after a trयंत्रit.
 */
अटल irqवापस_t lmc_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance) /*fold00*/
अणु
    काष्ठा net_device *dev = (काष्ठा net_device *) dev_instance;
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 csr;
    पूर्णांक i;
    s32 stat;
    अचिन्हित पूर्णांक badtx;
    पूर्णांक max_work = LMC_RXDESCS;
    पूर्णांक handled = 0;

    spin_lock(&sc->lmc_lock);

    /*
     * Read the csr to find what पूर्णांकerrupts we have (अगर any)
     */
    csr = LMC_CSR_READ (sc, csr_status);

    /*
     * Make sure this is our पूर्णांकerrupt
     */
    अगर ( ! (csr & sc->lmc_पूर्णांकrmask)) अणु
        जाओ lmc_पूर्णांक_fail_out;
    पूर्ण

    /* always go through this loop at least once */
    जबतक (csr & sc->lmc_पूर्णांकrmask) अणु
	handled = 1;

        /*
         * Clear पूर्णांकerrupt bits, we handle all हाल below
         */
        LMC_CSR_WRITE (sc, csr_status, csr);

        /*
         * One of
         *  - Transmit process समयd out CSR5<1>
         *  - Transmit jabber समयout    CSR5<3>
         *  - Transmit underflow         CSR5<5>
         *  - Transmit Receiver buffer unavailable CSR5<7>
         *  - Receive process stopped    CSR5<8>
         *  - Receive watchकरोg समयout   CSR5<9>
         *  - Early transmit पूर्णांकerrupt   CSR5<10>
         *
         * Is this really right? Should we करो a running reset क्रम jabber?
         * (being a WAN card and all)
         */
        अगर (csr & TULIP_STS_ABNRMLINTR)अणु
            lmc_running_reset (dev);
            अवरोध;
        पूर्ण

        अगर (csr & TULIP_STS_RXINTR)
            lmc_rx (dev);

        अगर (csr & (TULIP_STS_TXINTR | TULIP_STS_TXNOBUF | TULIP_STS_TXSTOPPED)) अणु

	    पूर्णांक		n_compl = 0 ;
            /* reset the transmit समयout detection flag -baz */
	    sc->extra_stats.tx_NoCompleteCnt = 0;

            badtx = sc->lmc_taपूर्णांक_tx;
            i = badtx % LMC_TXDESCS;

            जबतक ((badtx < sc->lmc_next_tx)) अणु
                stat = sc->lmc_txring[i].status;

                LMC_EVENT_LOG (LMC_EVENT_XMTINT, stat,
						 sc->lmc_txring[i].length);
                /*
                 * If bit 31 is 1 the tulip owns it अवरोध out of the loop
                 */
                अगर (stat & 0x80000000)
                    अवरोध;

		n_compl++ ;		/* i.e., have an empty slot in ring */
                /*
                 * If we have no skbuff or have cleared it
                 * Alपढ़ोy जारी to the next buffer
                 */
                अगर (sc->lmc_txq[i] == शून्य)
                    जारी;

		/*
		 * Check the total error summary to look क्रम any errors
		 */
		अगर (stat & 0x8000) अणु
			sc->lmc_device->stats.tx_errors++;
			अगर (stat & 0x4104)
				sc->lmc_device->stats.tx_पातed_errors++;
			अगर (stat & 0x0C00)
				sc->lmc_device->stats.tx_carrier_errors++;
			अगर (stat & 0x0200)
				sc->lmc_device->stats.tx_winकरोw_errors++;
			अगर (stat & 0x0002)
				sc->lmc_device->stats.tx_fअगरo_errors++;
		पूर्ण अन्यथा अणु
			sc->lmc_device->stats.tx_bytes += sc->lmc_txring[i].length & 0x7ff;

			sc->lmc_device->stats.tx_packets++;
                पूर्ण

		dev_consume_skb_irq(sc->lmc_txq[i]);
                sc->lmc_txq[i] = शून्य;

                badtx++;
                i = badtx % LMC_TXDESCS;
            पूर्ण

            अगर (sc->lmc_next_tx - badtx > LMC_TXDESCS)
            अणु
                prपूर्णांकk ("%s: out of sync pointer\n", dev->name);
                badtx += LMC_TXDESCS;
            पूर्ण
            LMC_EVENT_LOG(LMC_EVENT_TBUSY0, n_compl, 0);
            sc->lmc_txfull = 0;
            netअगर_wake_queue(dev);
	    sc->extra_stats.tx_tbusy0++;


#अगर_घोषित DEBUG
	    sc->extra_stats.dirtyTx = badtx;
	    sc->extra_stats.lmc_next_tx = sc->lmc_next_tx;
	    sc->extra_stats.lmc_txfull = sc->lmc_txfull;
#पूर्ण_अगर
            sc->lmc_taपूर्णांक_tx = badtx;

            /*
             * Why was there a अवरोध here???
             */
        पूर्ण			/* end handle transmit पूर्णांकerrupt */

        अगर (csr & TULIP_STS_SYSERROR) अणु
            u32 error;
            prपूर्णांकk (KERN_WARNING "%s: system bus error csr: %#8.8x\n", dev->name, csr);
            error = csr>>23 & 0x7;
            चयन(error)अणु
            हाल 0x000:
                prपूर्णांकk(KERN_WARNING "%s: Parity Fault (bad)\n", dev->name);
                अवरोध;
            हाल 0x001:
                prपूर्णांकk(KERN_WARNING "%s: Master Abort (naughty)\n", dev->name);
                अवरोध;
            हाल 0x002:
                prपूर्णांकk(KERN_WARNING "%s: Target Abort (not so naughty)\n", dev->name);
                अवरोध;
            शेष:
                prपूर्णांकk(KERN_WARNING "%s: This bus error code was supposed to be reserved!\n", dev->name);
            पूर्ण
            lmc_dec_reset (sc);
            lmc_reset (sc);
            LMC_EVENT_LOG(LMC_EVENT_RESET1, LMC_CSR_READ (sc, csr_status), 0);
            LMC_EVENT_LOG(LMC_EVENT_RESET2,
                          lmc_mii_पढ़ोreg (sc, 0, 16),
                          lmc_mii_पढ़ोreg (sc, 0, 17));

        पूर्ण

        
        अगर(max_work-- <= 0)
            अवरोध;
        
        /*
         * Get current csr status to make sure
         * we've cleared all पूर्णांकerrupts
         */
        csr = LMC_CSR_READ (sc, csr_status);
    पूर्ण				/* end पूर्णांकerrupt loop */
    LMC_EVENT_LOG(LMC_EVENT_INT, firstcsr, csr);

lmc_पूर्णांक_fail_out:

    spin_unlock(&sc->lmc_lock);

    वापस IRQ_RETVAL(handled);
पूर्ण

अटल netdev_tx_t lmc_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 flag;
    पूर्णांक entry;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&sc->lmc_lock, flags);

    /* normal path, tbusy known to be zero */

    entry = sc->lmc_next_tx % LMC_TXDESCS;

    sc->lmc_txq[entry] = skb;
    sc->lmc_txring[entry].buffer1 = virt_to_bus (skb->data);

    LMC_CONSOLE_LOG("xmit", skb->data, skb->len);

#अगर_अघोषित GCOM
    /* If the queue is less than half full, करोn't पूर्णांकerrupt */
    अगर (sc->lmc_next_tx - sc->lmc_taपूर्णांक_tx < LMC_TXDESCS / 2)
    अणु
        /* Do not पूर्णांकerrupt on completion of this packet */
        flag = 0x60000000;
        netअगर_wake_queue(dev);
    पूर्ण
    अन्यथा अगर (sc->lmc_next_tx - sc->lmc_taपूर्णांक_tx == LMC_TXDESCS / 2)
    अणु
        /* This generates an पूर्णांकerrupt on completion of this packet */
        flag = 0xe0000000;
        netअगर_wake_queue(dev);
    पूर्ण
    अन्यथा अगर (sc->lmc_next_tx - sc->lmc_taपूर्णांक_tx < LMC_TXDESCS - 1)
    अणु
        /* Do not पूर्णांकerrupt on completion of this packet */
        flag = 0x60000000;
        netअगर_wake_queue(dev);
    पूर्ण
    अन्यथा
    अणु
        /* This generates an पूर्णांकerrupt on completion of this packet */
        flag = 0xe0000000;
        sc->lmc_txfull = 1;
        netअगर_stop_queue(dev);
    पूर्ण
#अन्यथा
    flag = LMC_TDES_INTERRUPT_ON_COMPLETION;

    अगर (sc->lmc_next_tx - sc->lmc_taपूर्णांक_tx >= LMC_TXDESCS - 1)
    अणु				/* ring full, go busy */
        sc->lmc_txfull = 1;
	netअगर_stop_queue(dev);
	sc->extra_stats.tx_tbusy1++;
        LMC_EVENT_LOG(LMC_EVENT_TBUSY1, entry, 0);
    पूर्ण
#पूर्ण_अगर


    अगर (entry == LMC_TXDESCS - 1)	/* last descriptor in ring */
	flag |= LMC_TDES_END_OF_RING;	/* flag as such क्रम Tulip */

    /* करोn't pad small packets either */
    flag = sc->lmc_txring[entry].length = (skb->len) | flag |
						sc->TxDescriptControlInit;

    /* set the transmit समयout flag to be checked in
     * the watchकरोg समयr handler. -baz
     */

    sc->extra_stats.tx_NoCompleteCnt++;
    sc->lmc_next_tx++;

    /* give ownership to the chip */
    LMC_EVENT_LOG(LMC_EVENT_XMT, flag, entry);
    sc->lmc_txring[entry].status = 0x80000000;

    /* send now! */
    LMC_CSR_WRITE (sc, csr_txpoll, 0);

    spin_unlock_irqrestore(&sc->lmc_lock, flags);

    वापस NETDEV_TX_OK;
पूर्ण


अटल पूर्णांक lmc_rx(काष्ठा net_device *dev)
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    पूर्णांक i;
    पूर्णांक rx_work_limit = LMC_RXDESCS;
    पूर्णांक rxIntLoopCnt;		/* debug -baz */
    पूर्णांक localLengthErrCnt = 0;
    दीर्घ stat;
    काष्ठा sk_buff *skb, *nsb;
    u16 len;

    lmc_led_on(sc, LMC_DS3_LED3);

    rxIntLoopCnt = 0;		/* debug -baz */

    i = sc->lmc_next_rx % LMC_RXDESCS;

    जबतक (((stat = sc->lmc_rxring[i].status) & LMC_RDES_OWN_BIT) != DESC_OWNED_BY_DC21X4)
    अणु
        rxIntLoopCnt++;		/* debug -baz */
        len = ((stat & LMC_RDES_FRAME_LENGTH) >> RDES_FRAME_LENGTH_BIT_NUMBER);
        अगर ((stat & 0x0300) != 0x0300) अणु  /* Check first segment and last segment */
		अगर ((stat & 0x0000ffff) != 0x7fff) अणु
			/* Oversized frame */
			sc->lmc_device->stats.rx_length_errors++;
			जाओ skip_packet;
		पूर्ण
	पूर्ण

	अगर (stat & 0x00000008) अणु /* Catch a dribbling bit error */
		sc->lmc_device->stats.rx_errors++;
		sc->lmc_device->stats.rx_frame_errors++;
		जाओ skip_packet;
	पूर्ण


	अगर (stat & 0x00000004) अणु /* Catch a CRC error by the Xilinx */
		sc->lmc_device->stats.rx_errors++;
		sc->lmc_device->stats.rx_crc_errors++;
		जाओ skip_packet;
	पूर्ण

	अगर (len > LMC_PKT_BUF_SZ) अणु
		sc->lmc_device->stats.rx_length_errors++;
		localLengthErrCnt++;
		जाओ skip_packet;
	पूर्ण

	अगर (len < sc->lmc_crcSize + 2) अणु
		sc->lmc_device->stats.rx_length_errors++;
		sc->extra_stats.rx_SmallPktCnt++;
		localLengthErrCnt++;
		जाओ skip_packet;
	पूर्ण

        अगर(stat & 0x00004000)अणु
            prपूर्णांकk(KERN_WARNING "%s: Receiver descriptor error, receiver out of sync?\n", dev->name);
        पूर्ण

        len -= sc->lmc_crcSize;

        skb = sc->lmc_rxq[i];

        /*
         * We ran out of memory at some poपूर्णांक
         * just allocate an skb buff and जारी.
         */
        
        अगर (!skb) अणु
            nsb = dev_alloc_skb (LMC_PKT_BUF_SZ + 2);
            अगर (nsb) अणु
                sc->lmc_rxq[i] = nsb;
                nsb->dev = dev;
                sc->lmc_rxring[i].buffer1 = virt_to_bus(skb_tail_poपूर्णांकer(nsb));
            पूर्ण
            sc->failed_recv_alloc = 1;
            जाओ skip_packet;
        पूर्ण
        
	sc->lmc_device->stats.rx_packets++;
	sc->lmc_device->stats.rx_bytes += len;

        LMC_CONSOLE_LOG("recv", skb->data, len);

        /*
         * I'm not sure of the sanity of this
         * Packets could be arriving at a स्थिरant
         * 44.210mbits/sec and we're going to copy
         * them पूर्णांकo a new buffer??
         */
        
        अगर(len > (LMC_MTU - (LMC_MTU>>2)))अणु /* len > LMC_MTU * 0.75 */
            /*
             * If it's a large packet don't copy it just hand it up
             */
        give_it_anyways:

            sc->lmc_rxq[i] = शून्य;
            sc->lmc_rxring[i].buffer1 = 0x0;

            skb_put (skb, len);
            skb->protocol = lmc_proto_type(sc, skb);
            skb_reset_mac_header(skb);
            /* skb_reset_network_header(skb); */
            skb->dev = dev;
            lmc_proto_netअगर(sc, skb);

            /*
             * This skb will be destroyed by the upper layers, make a new one
             */
            nsb = dev_alloc_skb (LMC_PKT_BUF_SZ + 2);
            अगर (nsb) अणु
                sc->lmc_rxq[i] = nsb;
                nsb->dev = dev;
                sc->lmc_rxring[i].buffer1 = virt_to_bus(skb_tail_poपूर्णांकer(nsb));
                /* Transferred to 21140 below */
            पूर्ण
            अन्यथा अणु
                /*
                 * We've run out of memory, stop trying to allocate
                 * memory and निकास the पूर्णांकerrupt handler
                 *
                 * The chip may run out of receivers and stop
                 * in which care we'll try to allocate the buffer
                 * again.  (once a second)
                 */
		sc->extra_stats.rx_BuffAllocErr++;
                LMC_EVENT_LOG(LMC_EVENT_RCVINT, stat, len);
                sc->failed_recv_alloc = 1;
                जाओ skip_out_of_mem;
            पूर्ण
        पूर्ण
        अन्यथा अणु
            nsb = dev_alloc_skb(len);
            अगर(!nsb) अणु
                जाओ give_it_anyways;
            पूर्ण
            skb_copy_from_linear_data(skb, skb_put(nsb, len), len);
            
            nsb->protocol = lmc_proto_type(sc, nsb);
            skb_reset_mac_header(nsb);
            /* skb_reset_network_header(nsb); */
            nsb->dev = dev;
            lmc_proto_netअगर(sc, nsb);
        पूर्ण

    skip_packet:
        LMC_EVENT_LOG(LMC_EVENT_RCVINT, stat, len);
        sc->lmc_rxring[i].status = DESC_OWNED_BY_DC21X4;

        sc->lmc_next_rx++;
        i = sc->lmc_next_rx % LMC_RXDESCS;
        rx_work_limit--;
        अगर (rx_work_limit < 0)
            अवरोध;
    पूर्ण

    /* detect condition क्रम LMC1000 where DSU cable attaches and fills
     * descriptors with bogus packets
     *
    अगर (localLengthErrCnt > LMC_RXDESCS - 3) अणु
	sc->extra_stats.rx_BadPktSurgeCnt++;
	LMC_EVENT_LOG(LMC_EVENT_BADPKTSURGE, localLengthErrCnt,
		      sc->extra_stats.rx_BadPktSurgeCnt);
    पूर्ण */

    /* save max count of receive descriptors serviced */
    अगर (rxIntLoopCnt > sc->extra_stats.rxIntLoopCnt)
	    sc->extra_stats.rxIntLoopCnt = rxIntLoopCnt; /* debug -baz */

#अगर_घोषित DEBUG
    अगर (rxIntLoopCnt == 0)
    अणु
        क्रम (i = 0; i < LMC_RXDESCS; i++)
        अणु
            अगर ((sc->lmc_rxring[i].status & LMC_RDES_OWN_BIT)
                != DESC_OWNED_BY_DC21X4)
            अणु
                rxIntLoopCnt++;
            पूर्ण
        पूर्ण
        LMC_EVENT_LOG(LMC_EVENT_RCVEND, rxIntLoopCnt, 0);
    पूर्ण
#पूर्ण_अगर


    lmc_led_off(sc, LMC_DS3_LED3);

skip_out_of_mem:
    वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *lmc_get_stats(काष्ठा net_device *dev)
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&sc->lmc_lock, flags);

    sc->lmc_device->stats.rx_missed_errors += LMC_CSR_READ(sc, csr_missed_frames) & 0xffff;

    spin_unlock_irqrestore(&sc->lmc_lock, flags);

    वापस &sc->lmc_device->stats;
पूर्ण

अटल काष्ठा pci_driver lmc_driver = अणु
	.name		= "lmc",
	.id_table	= lmc_pci_tbl,
	.probe		= lmc_init_one,
	.हटाओ		= lmc_हटाओ_one,
पूर्ण;

module_pci_driver(lmc_driver);

अचिन्हित lmc_mii_पढ़ोreg (lmc_softc_t * स्थिर sc, अचिन्हित devaddr, अचिन्हित regno) /*fold00*/
अणु
    पूर्णांक i;
    पूर्णांक command = (0xf6 << 10) | (devaddr << 5) | regno;
    पूर्णांक retval = 0;

    LMC_MII_SYNC (sc);

    क्रम (i = 15; i >= 0; i--)
    अणु
        पूर्णांक dataval = (command & (1 << i)) ? 0x20000 : 0;

        LMC_CSR_WRITE (sc, csr_9, dataval);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        LMC_CSR_WRITE (sc, csr_9, dataval | 0x10000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
    पूर्ण

    क्रम (i = 19; i > 0; i--)
    अणु
        LMC_CSR_WRITE (sc, csr_9, 0x40000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        retval = (retval << 1) | ((LMC_CSR_READ (sc, csr_9) & 0x80000) ? 1 : 0);
        LMC_CSR_WRITE (sc, csr_9, 0x40000 | 0x10000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
    पूर्ण

    वापस (retval >> 1) & 0xffff;
पूर्ण

व्योम lmc_mii_ग_लिखोreg (lmc_softc_t * स्थिर sc, अचिन्हित devaddr, अचिन्हित regno, अचिन्हित data) /*fold00*/
अणु
    पूर्णांक i = 32;
    पूर्णांक command = (0x5002 << 16) | (devaddr << 23) | (regno << 18) | data;

    LMC_MII_SYNC (sc);

    i = 31;
    जबतक (i >= 0)
    अणु
        पूर्णांक datav;

        अगर (command & (1 << i))
            datav = 0x20000;
        अन्यथा
            datav = 0x00000;

        LMC_CSR_WRITE (sc, csr_9, datav);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        LMC_CSR_WRITE (sc, csr_9, (datav | 0x10000));
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        i--;
    पूर्ण

    i = 2;
    जबतक (i > 0)
    अणु
        LMC_CSR_WRITE (sc, csr_9, 0x40000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        LMC_CSR_WRITE (sc, csr_9, 0x50000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        i--;
    पूर्ण
पूर्ण

अटल व्योम lmc_softreset (lmc_softc_t * स्थिर sc) /*fold00*/
अणु
    पूर्णांक i;

    /* Initialize the receive rings and buffers. */
    sc->lmc_txfull = 0;
    sc->lmc_next_rx = 0;
    sc->lmc_next_tx = 0;
    sc->lmc_taपूर्णांक_rx = 0;
    sc->lmc_taपूर्णांक_tx = 0;

    /*
     * Setup each one of the receiver buffers
     * allocate an skbuff क्रम each one, setup the descriptor table
     * and poपूर्णांक each buffer at the next one
     */

    क्रम (i = 0; i < LMC_RXDESCS; i++)
    अणु
        काष्ठा sk_buff *skb;

        अगर (sc->lmc_rxq[i] == शून्य)
        अणु
            skb = dev_alloc_skb (LMC_PKT_BUF_SZ + 2);
            अगर(skb == शून्य)अणु
                prपूर्णांकk(KERN_WARNING "%s: Failed to allocate receiver ring, will try again\n", sc->name);
                sc->failed_ring = 1;
                अवरोध;
            पूर्ण
            अन्यथाअणु
                sc->lmc_rxq[i] = skb;
            पूर्ण
        पूर्ण
        अन्यथा
        अणु
            skb = sc->lmc_rxq[i];
        पूर्ण

        skb->dev = sc->lmc_device;

        /* owned by 21140 */
        sc->lmc_rxring[i].status = 0x80000000;

        /* used to be PKT_BUF_SZ now uses skb since we lose some to head room */
        sc->lmc_rxring[i].length = skb_tailroom(skb);

        /* use to be tail which is dumb since you're thinking why ग_लिखो
         * to the end of the packj,et but since there's nothing there tail == data
         */
        sc->lmc_rxring[i].buffer1 = virt_to_bus (skb->data);

        /* This is fair since the काष्ठाure is अटल and we have the next address */
        sc->lmc_rxring[i].buffer2 = virt_to_bus (&sc->lmc_rxring[i + 1]);

    पूर्ण

    /*
     * Sets end of ring
     */
    अगर (i != 0) अणु
        sc->lmc_rxring[i - 1].length |= 0x02000000; /* Set end of buffers flag */
        sc->lmc_rxring[i - 1].buffer2 = virt_to_bus(&sc->lmc_rxring[0]); /* Poपूर्णांक back to the start */
    पूर्ण
    LMC_CSR_WRITE (sc, csr_rxlist, virt_to_bus (sc->lmc_rxring)); /* ग_लिखो base address */

    /* Initialize the transmit rings and buffers */
    क्रम (i = 0; i < LMC_TXDESCS; i++)
    अणु
        अगर (sc->lmc_txq[i] != शून्य)अणु		/* have buffer */
            dev_kमुक्त_skb(sc->lmc_txq[i]);	/* मुक्त it */
	    sc->lmc_device->stats.tx_dropped++;	/* We just dropped a packet */
        पूर्ण
        sc->lmc_txq[i] = शून्य;
        sc->lmc_txring[i].status = 0x00000000;
        sc->lmc_txring[i].buffer2 = virt_to_bus (&sc->lmc_txring[i + 1]);
    पूर्ण
    sc->lmc_txring[i - 1].buffer2 = virt_to_bus (&sc->lmc_txring[0]);
    LMC_CSR_WRITE (sc, csr_txlist, virt_to_bus (sc->lmc_txring));
पूर्ण

व्योम lmc_gpio_mkinput(lmc_softc_t * स्थिर sc, u32 bits) /*fold00*/
अणु
    sc->lmc_gpio_io &= ~bits;
    LMC_CSR_WRITE(sc, csr_gp, TULIP_GP_PINSET | (sc->lmc_gpio_io));
पूर्ण

व्योम lmc_gpio_mkoutput(lmc_softc_t * स्थिर sc, u32 bits) /*fold00*/
अणु
    sc->lmc_gpio_io |= bits;
    LMC_CSR_WRITE(sc, csr_gp, TULIP_GP_PINSET | (sc->lmc_gpio_io));
पूर्ण

व्योम lmc_led_on(lmc_softc_t * स्थिर sc, u32 led) /*fold00*/
अणु
    अगर ((~sc->lmc_miireg16) & led) /* Alपढ़ोy on! */
        वापस;

    sc->lmc_miireg16 &= ~led;
    lmc_mii_ग_लिखोreg(sc, 0, 16, sc->lmc_miireg16);
पूर्ण

व्योम lmc_led_off(lmc_softc_t * स्थिर sc, u32 led) /*fold00*/
अणु
    अगर (sc->lmc_miireg16 & led) /* Alपढ़ोy set करोn't करो anything */
        वापस;

    sc->lmc_miireg16 |= led;
    lmc_mii_ग_लिखोreg(sc, 0, 16, sc->lmc_miireg16);
पूर्ण

अटल व्योम lmc_reset(lmc_softc_t * स्थिर sc) /*fold00*/
अणु
    sc->lmc_miireg16 |= LMC_MII16_FIFO_RESET;
    lmc_mii_ग_लिखोreg(sc, 0, 16, sc->lmc_miireg16);

    sc->lmc_miireg16 &= ~LMC_MII16_FIFO_RESET;
    lmc_mii_ग_लिखोreg(sc, 0, 16, sc->lmc_miireg16);

    /*
     * make some of the GPIO pins be outमाला_दो
     */
    lmc_gpio_mkoutput(sc, LMC_GEP_RESET);

    /*
     * RESET low to क्रमce state reset.  This also क्रमces
     * the transmitter घड़ी to be पूर्णांकernal, but we expect to reset
     * that later anyway.
     */
    sc->lmc_gpio &= ~(LMC_GEP_RESET);
    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);

    /*
     * hold क्रम more than 10 microseconds
     */
    udelay(50);

    /*
     * stop driving Xilinx-related संकेतs
     */
    lmc_gpio_mkinput(sc, LMC_GEP_RESET);

    /*
     * Call media specअगरic init routine
     */
    sc->lmc_media->init(sc);

    sc->extra_stats.resetCount++;
पूर्ण

अटल व्योम lmc_dec_reset(lmc_softc_t * स्थिर sc) /*fold00*/
अणु
    u32 val;

    /*
     * disable all पूर्णांकerrupts
     */
    sc->lmc_पूर्णांकrmask = 0;
    LMC_CSR_WRITE(sc, csr_पूर्णांकr, sc->lmc_पूर्णांकrmask);

    /*
     * Reset the chip with a software reset command.
     * Wait 10 microseconds (actually 50 PCI cycles but at
     * 33MHz that comes to two microseconds but रुको a
     * bit दीर्घer anyways)
     */
    LMC_CSR_WRITE(sc, csr_busmode, TULIP_BUSMODE_SWRESET);
    udelay(25);
#अगर_घोषित __sparc__
    sc->lmc_busmode = LMC_CSR_READ(sc, csr_busmode);
    sc->lmc_busmode = 0x00100000;
    sc->lmc_busmode &= ~TULIP_BUSMODE_SWRESET;
    LMC_CSR_WRITE(sc, csr_busmode, sc->lmc_busmode);
#पूर्ण_अगर
    sc->lmc_cmdmode = LMC_CSR_READ(sc, csr_command);

    /*
     * We want:
     *   no ethernet address in frames we ग_लिखो
     *   disable padding (txdesc, padding disable)
     *   ignore runt frames (rdes0 bit 15)
     *   no receiver watchकरोg or transmitter jabber समयr
     *       (csr15 bit 0,14 == 1)
     *   अगर using 16-bit CRC, turn off CRC (trans desc, crc disable)
     */

    sc->lmc_cmdmode |= ( TULIP_CMD_PROMISCUOUS
                         | TULIP_CMD_FULLDUPLEX
                         | TULIP_CMD_PASSBADPKT
                         | TULIP_CMD_NOHEARTBEAT
                         | TULIP_CMD_PORTSELECT
                         | TULIP_CMD_RECEIVEALL
                         | TULIP_CMD_MUSTBEONE
                       );
    sc->lmc_cmdmode &= ~( TULIP_CMD_OPERMODE
                          | TULIP_CMD_THRESHOLDCTL
                          | TULIP_CMD_STOREFWD
                          | TULIP_CMD_TXTHRSHLDCTL
                        );

    LMC_CSR_WRITE(sc, csr_command, sc->lmc_cmdmode);

    /*
     * disable receiver watchकरोg and transmit jabber
     */
    val = LMC_CSR_READ(sc, csr_sia_general);
    val |= (TULIP_WATCHDOG_TXDISABLE | TULIP_WATCHDOG_RXDISABLE);
    LMC_CSR_WRITE(sc, csr_sia_general, val);
पूर्ण

अटल व्योम lmc_initcsrs(lmc_softc_t * स्थिर sc, lmc_csrptr_t csr_base, /*fold00*/
                         माप_प्रकार csr_size)
अणु
    sc->lmc_csrs.csr_busmode	        = csr_base +  0 * csr_size;
    sc->lmc_csrs.csr_txpoll		= csr_base +  1 * csr_size;
    sc->lmc_csrs.csr_rxpoll		= csr_base +  2 * csr_size;
    sc->lmc_csrs.csr_rxlist		= csr_base +  3 * csr_size;
    sc->lmc_csrs.csr_txlist		= csr_base +  4 * csr_size;
    sc->lmc_csrs.csr_status		= csr_base +  5 * csr_size;
    sc->lmc_csrs.csr_command	        = csr_base +  6 * csr_size;
    sc->lmc_csrs.csr_पूर्णांकr		= csr_base +  7 * csr_size;
    sc->lmc_csrs.csr_missed_frames	= csr_base +  8 * csr_size;
    sc->lmc_csrs.csr_9		        = csr_base +  9 * csr_size;
    sc->lmc_csrs.csr_10		        = csr_base + 10 * csr_size;
    sc->lmc_csrs.csr_11		        = csr_base + 11 * csr_size;
    sc->lmc_csrs.csr_12		        = csr_base + 12 * csr_size;
    sc->lmc_csrs.csr_13		        = csr_base + 13 * csr_size;
    sc->lmc_csrs.csr_14		        = csr_base + 14 * csr_size;
    sc->lmc_csrs.csr_15		        = csr_base + 15 * csr_size;
पूर्ण

अटल व्योम lmc_driver_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
    lmc_softc_t *sc = dev_to_sc(dev);
    u32 csr6;
    अचिन्हित दीर्घ flags;

    spin_lock_irqsave(&sc->lmc_lock, flags);

    prपूर्णांकk("%s: Xmitter busy|\n", dev->name);

    sc->extra_stats.tx_tbusy_calls++;
    अगर (jअगरfies - dev_trans_start(dev) < TX_TIMEOUT)
	    जाओ bug_out;

    /*
     * Chip seems to have locked up
     * Reset it
     * This whips out all our descriptor
     * table and starts from scartch
     */

    LMC_EVENT_LOG(LMC_EVENT_XMTPRCTMO,
                  LMC_CSR_READ (sc, csr_status),
		  sc->extra_stats.tx_ProcTimeout);

    lmc_running_reset (dev);

    LMC_EVENT_LOG(LMC_EVENT_RESET1, LMC_CSR_READ (sc, csr_status), 0);
    LMC_EVENT_LOG(LMC_EVENT_RESET2,
                  lmc_mii_पढ़ोreg (sc, 0, 16),
                  lmc_mii_पढ़ोreg (sc, 0, 17));

    /* restart the tx processes */
    csr6 = LMC_CSR_READ (sc, csr_command);
    LMC_CSR_WRITE (sc, csr_command, csr6 | 0x0002);
    LMC_CSR_WRITE (sc, csr_command, csr6 | 0x2002);

    /* immediate transmit */
    LMC_CSR_WRITE (sc, csr_txpoll, 0);

    sc->lmc_device->stats.tx_errors++;
    sc->extra_stats.tx_ProcTimeout++; /* -baz */

    netअगर_trans_update(dev); /* prevent tx समयout */

bug_out:

    spin_unlock_irqrestore(&sc->lmc_lock, flags);
पूर्ण
