<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/pnic2.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.
        Modअगरied to hep support PNIC_II by Kevin B. Hendricks

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

        Please submit bugs to http://bugzilla.kernel.org/ .
*/


/* Understanding the PNIC_II - everything is this file is based
 * on the PNIC_II_PDF datasheet which is sorely lacking in detail
 *
 * As I understand things, here are the रेजिस्टरs and bits that
 * explain the masks and स्थिरants used in this file that are
 * either dअगरferent from the 21142/3 or important क्रम basic operation.
 *
 *
 * CSR 6  (mask = 0xfe3bd1fd of bits not to change)
 * -----
 * Bit 24    - SCR
 * Bit 23    - PCS
 * Bit 22    - TTM (Trयंत्रit Threshold Mode)
 * Bit 18    - Port Select
 * Bit 13    - Start - 1, Stop - 0 Transmissions
 * Bit 11:10 - Loop Back Operation Mode
 * Bit 9     - Full Duplex mode (Advertise 10BaseT-FD is CSR14<7> is set)
 * Bit 1     - Start - 1, Stop - 0 Receive
 *
 *
 * CSR 14  (mask = 0xfff0ee39 of bits not to change)
 * ------
 * Bit 19    - PAUSE-Pause
 * Bit 18    - Advertise T4
 * Bit 17    - Advertise 100baseTx-FD
 * Bit 16    - Advertise 100baseTx-HD
 * Bit 12    - LTE - Link Test Enable
 * Bit 7     - ANE - Auto Negotiate Enable
 * Bit 6     - HDE - Advertise 10baseT-HD
 * Bit 2     - Reset to Power करोwn - kept as 1 क्रम normal operation
 * Bit 1     -  Loop Back enable क्रम 10baseT MCC
 *
 *
 * CSR 12
 * ------
 * Bit 25    - Partner can करो T4
 * Bit 24    - Partner can करो 100baseTx-FD
 * Bit 23    - Partner can करो 100baseTx-HD
 * Bit 22    - Partner can करो 10baseT-FD
 * Bit 21    - Partner can करो 10baseT-HD
 * Bit 15    - LPN is 1 अगर all above bits are valid other wise 0
 * Bit 14:12 - स्वतःnegotiation state (ग_लिखो 001 to start स्वतःnegotiate)
 * Bit 3     - Autopolarity state
 * Bit 2     - LS10B - link state of 10baseT 0 - good, 1 - failed
 * Bit 1     - LS100B - link state of 100baseT 0 - good, 1 - failed
 *
 *
 * Data Port Selection Info
 *-------------------------
 *
 * CSR14<7>   CSR6<18>    CSR6<22>    CSR6<23>    CSR6<24>   MODE/PORT
 *   1           0           0 (X)       0 (X)       1        NWAY
 *   0           0           1           0 (X)       0        10baseT
 *   0           1           0           1           1 (X)    100baseT
 *
 *
 */



#समावेश "tulip.h"
#समावेश <linux/delay.h>


व्योम pnic2_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tulip_निजी *tp = from_समयr(tp, t, समयr);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->base_addr;
	पूर्णांक next_tick = 60*HZ;

	अगर (tulip_debug > 3)
		dev_info(&dev->dev, "PNIC2 negotiation status %08x\n",
			 ioपढ़ो32(ioaddr + CSR12));

	अगर (next_tick) अणु
		mod_समयr(&tp->समयr, RUN_AT(next_tick));
	पूर्ण
पूर्ण


व्योम pnic2_start_nway(काष्ठा net_device *dev)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
        पूर्णांक csr14;
        पूर्णांक csr12;

        /* set up what to advertise during the negotiation */

        /* load in csr14  and mask off bits not to touch
         * comment at top of file explains mask value
         */
	csr14 = (ioपढ़ो32(ioaddr + CSR14) & 0xfff0ee39);

        /* bit 17 - advetise 100baseTx-FD */
        अगर (tp->sym_advertise & 0x0100) csr14 |= 0x00020000;

        /* bit 16 - advertise 100baseTx-HD */
        अगर (tp->sym_advertise & 0x0080) csr14 |= 0x00010000;

        /* bit 6 - advertise 10baseT-HD */
        अगर (tp->sym_advertise & 0x0020) csr14 |= 0x00000040;

        /* Now set bit 12 Link Test Enable, Bit 7 Autonegotiation Enable
         * and bit 0 Don't PowerDown 10baseT
         */
        csr14 |= 0x00001184;

	अगर (tulip_debug > 1)
		netdev_dbg(dev, "Restarting PNIC2 autonegotiation, csr14=%08x\n",
			   csr14);

        /* tell pnic2_lnk_change we are करोing an nway negotiation */
	dev->अगर_port = 0;
	tp->nway = tp->mediasense = 1;
	tp->nwayset = tp->lpar = 0;

        /* now we have to set up csr6 क्रम NWAY state */

	tp->csr6 = ioपढ़ो32(ioaddr + CSR6);
	अगर (tulip_debug > 1)
		netdev_dbg(dev, "On Entry to Nway, csr6=%08x\n", tp->csr6);

        /* mask off any bits not to touch
         * comment at top of file explains mask value
         */
	tp->csr6 = tp->csr6 & 0xfe3bd1fd;

        /* करोn't क्रमget that bit 9 is also used क्रम advertising */
        /* advertise 10baseT-FD क्रम the negotiation (bit 9) */
        अगर (tp->sym_advertise & 0x0040) tp->csr6 |= 0x00000200;

        /* set bit 24 क्रम nway negotiation mode ...
         * see Data Port Selection comment at top of file
         * and "Stop" - reset both Transmit (bit 13) and Receive (bit 1)
         */
        tp->csr6 |= 0x01000000;
	ioग_लिखो32(csr14, ioaddr + CSR14);
	ioग_लिखो32(tp->csr6, ioaddr + CSR6);
        udelay(100);

        /* all set up so now क्रमce the negotiation to begin */

        /* पढ़ो in current values and mask off all but the
	 * Autonegotiation bits 14:12.  Writing a 001 to those bits
         * should start the स्वतःnegotiation
         */
        csr12 = (ioपढ़ो32(ioaddr + CSR12) & 0xffff8fff);
        csr12 |= 0x1000;
	ioग_लिखो32(csr12, ioaddr + CSR12);
पूर्ण



व्योम pnic2_lnk_change(काष्ठा net_device *dev, पूर्णांक csr5)
अणु
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->base_addr;
        पूर्णांक csr14;

        /* पढ़ो the staus रेजिस्टर to find out what is up */
	पूर्णांक csr12 = ioपढ़ो32(ioaddr + CSR12);

	अगर (tulip_debug > 1)
		dev_info(&dev->dev,
			 "PNIC2 link status interrupt %08x,  CSR5 %x, %08x\n",
			 csr12, csr5, ioपढ़ो32(ioaddr + CSR14));

	/* If NWay finished and we have a negotiated partner capability.
         * check bits 14:12 क्रम bit pattern 101 - all is good
         */
	अगर (tp->nway  &&  !tp->nwayset) अणु

	        /* we did an स्वतः negotiation */

                अगर ((csr12 & 0x7000) == 0x5000) अणु

	               /* negotiation ended successfully */

	               /* get the link partners reply and mask out all but
                        * bits 24-21 which show the partners capabilities
                        * and match those to what we advertised
                        *
                        * then begin to पूर्णांकerpret the results of the negotiation.
                        * Always go in this order : (we are ignoring T4 क्रम now)
                        *     100baseTx-FD, 100baseTx-HD, 10baseT-FD, 10baseT-HD
                        */

		        पूर्णांक negotiated = ((csr12 >> 16) & 0x01E0) & tp->sym_advertise;
		        tp->lpar = (csr12 >> 16);
		        tp->nwayset = 1;

                        अगर (negotiated & 0x0100)        dev->अगर_port = 5;
		        अन्यथा अगर (negotiated & 0x0080)	dev->अगर_port = 3;
		        अन्यथा अगर (negotiated & 0x0040)	dev->अगर_port = 4;
			अन्यथा अगर (negotiated & 0x0020)	dev->अगर_port = 0;
			अन्यथा अणु
			     अगर (tulip_debug > 1)
				     dev_info(&dev->dev,
					      "funny autonegotiate result csr12 %08x advertising %04x\n",
					      csr12, tp->sym_advertise);
			     tp->nwayset = 0;
			     /* so check  अगर 100baseTx link state is okay */
			     अगर ((csr12 & 2) == 0  &&  (tp->sym_advertise & 0x0180))
			       dev->अगर_port = 3;
			पूर्ण

			/* now record the duplex that was negotiated */
			tp->full_duplex = 0;
			अगर ((dev->अगर_port == 4) || (dev->अगर_port == 5))
			       tp->full_duplex = 1;

			अगर (tulip_debug > 1) अणु
			       अगर (tp->nwayset)
				       dev_info(&dev->dev,
						"Switching to %s based on link negotiation %04x & %04x = %04x\n",
						medianame[dev->अगर_port],
						tp->sym_advertise, tp->lpar,
						negotiated);
			पूर्ण

                        /* remember to turn off bit 7 - स्वतःnegotiate
                         * enable so we can properly end nway mode and
                         * set duplex (ie. use csr6<9> again)
                         */
	                csr14 = (ioपढ़ो32(ioaddr + CSR14) & 0xffffff7f);
                        ioग_लिखो32(csr14,ioaddr + CSR14);


                        /* now set the data port and operating mode
			 * (see the Data Port Selection comments at
			 * the top of the file
			 */

			/* get current csr6 and mask off bits not to touch */
			/* see comment at top of file */

			tp->csr6 = (ioपढ़ो32(ioaddr + CSR6) & 0xfe3bd1fd);

			/* so अगर using अगर_port 3 or 5 then select the 100baseT
			 * port अन्यथा select the 10baseT port.
			 * See the Data Port Selection table at the top
			 * of the file which was taken from the PNIC_II.PDF
			 * datasheet
			 */
			अगर (dev->अगर_port & 1) tp->csr6 |= 0x01840000;
			अन्यथा tp->csr6 |= 0x00400000;

			/* now set the full duplex bit appropriately */
			अगर (tp->full_duplex) tp->csr6 |= 0x00000200;

			ioग_लिखो32(1, ioaddr + CSR13);

			अगर (tulip_debug > 2)
				netdev_dbg(dev, "Setting CSR6 %08x/%x CSR12 %08x\n",
					   tp->csr6,
					   ioपढ़ो32(ioaddr + CSR6),
					   ioपढ़ो32(ioaddr + CSR12));

			/* now the following actually ग_लिखोs out the
			 * new csr6 values
			 */
			tulip_start_rxtx(tp);

                        वापस;

	        पूर्ण अन्यथा अणु
	                dev_info(&dev->dev,
				 "Autonegotiation failed, using %s, link beat status %04x\n",
				 medianame[dev->अगर_port], csr12);

                        /* remember to turn off bit 7 - स्वतःnegotiate
                         * enable so we करोn't क्रमget
                         */
	                csr14 = (ioपढ़ो32(ioaddr + CSR14) & 0xffffff7f);
                        ioग_लिखो32(csr14,ioaddr + CSR14);

                        /* what should we करो when स्वतःnegotiate fails?
                         * should we try again or शेष to baseline
                         * हाल.  I just करोn't know.
                         *
                         * क्रम now शेष to some baseline हाल
                         */

	                 dev->अगर_port = 0;
                         tp->nway = 0;
                         tp->nwayset = 1;

                         /* set to 10baseTx-HD - see Data Port Selection
                          * comment given at the top of the file
                          */
	                 tp->csr6 = (ioपढ़ो32(ioaddr + CSR6) & 0xfe3bd1fd);
                         tp->csr6 |= 0x00400000;

	                 tulip_restart_rxtx(tp);

                         वापस;

		पूर्ण
	पूर्ण

	अगर ((tp->nwayset  &&  (csr5 & 0x08000000) &&
	     (dev->अगर_port == 3  ||  dev->अगर_port == 5) &&
	     (csr12 & 2) == 2) || (tp->nway && (csr5 & (TPLnkFail)))) अणु

		/* Link blew? Maybe restart NWay. */

		अगर (tulip_debug > 2)
			netdev_dbg(dev, "Ugh! Link blew?\n");

		del_समयr_sync(&tp->समयr);
		pnic2_start_nway(dev);
		tp->समयr.expires = RUN_AT(3*HZ);
		add_समयr(&tp->समयr);

                वापस;
	पूर्ण


        अगर (dev->अगर_port == 3  ||  dev->अगर_port == 5) अणु

	        /* we are at 100mb and a potential link change occurred */

		अगर (tulip_debug > 1)
			dev_info(&dev->dev, "PNIC2 %s link beat %s\n",
				 medianame[dev->अगर_port],
				 (csr12 & 2) ? "failed" : "good");

                /* check 100 link beat */

                tp->nway = 0;
                tp->nwayset = 1;

                /* अगर failed then try करोing an nway to get in sync */
		अगर ((csr12 & 2)  &&  ! tp->medialock) अणु
			del_समयr_sync(&tp->समयr);
			pnic2_start_nway(dev);
			tp->समयr.expires = RUN_AT(3*HZ);
       			add_समयr(&tp->समयr);
                पूर्ण

                वापस;
        पूर्ण

	अगर (dev->अगर_port == 0  ||  dev->अगर_port == 4) अणु

	        /* we are at 10mb and a potential link change occurred */

		अगर (tulip_debug > 1)
			dev_info(&dev->dev, "PNIC2 %s link beat %s\n",
				 medianame[dev->अगर_port],
				 (csr12 & 4) ? "failed" : "good");


                tp->nway = 0;
                tp->nwayset = 1;

                /* अगर failed, try करोing an nway to get in sync */
		अगर ((csr12 & 4)  &&  ! tp->medialock) अणु
			del_समयr_sync(&tp->समयr);
			pnic2_start_nway(dev);
			tp->समयr.expires = RUN_AT(3*HZ);
       			add_समयr(&tp->समयr);
                पूर्ण

                वापस;
        पूर्ण


	अगर (tulip_debug > 1)
		dev_info(&dev->dev, "PNIC2 Link Change Default?\n");

        /* अगर all अन्यथा fails शेष to trying 10baseT-HD */
	dev->अगर_port = 0;

        /* make sure स्वतःnegotiate enable is off */
	csr14 = (ioपढ़ो32(ioaddr + CSR14) & 0xffffff7f);
        ioग_लिखो32(csr14,ioaddr + CSR14);

        /* set to 10baseTx-HD - see Data Port Selection
         * comment given at the top of the file
         */
	tp->csr6 = (ioपढ़ो32(ioaddr + CSR6) & 0xfe3bd1fd);
        tp->csr6 |= 0x00400000;

	tulip_restart_rxtx(tp);
पूर्ण

