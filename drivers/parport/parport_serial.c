<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Support क्रम common PCI multi-I/O cards (which is most of them)
 *
 * Copyright (C) 2001  Tim Waugh <twaugh@redhat.com>
 *
 * Multi-function PCI cards are supposed to present separate logical
 * devices on the bus.  A common thing to करो seems to be to just use
 * one logical device with lots of base address रेजिस्टरs क्रम both
 * parallel ports and serial ports.  This driver is क्रम dealing with
 * that.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/parport_pc.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/8250_pci.h>

क्रमागत parport_pc_pci_cards अणु
	titan_110l = 0,
	titan_210l,
	neपंचांगos_9xx5_combo,
	neपंचांगos_9855,
	neपंचांगos_9855_2p,
	neपंचांगos_9900,
	neपंचांगos_9900_2p,
	neपंचांगos_99xx_1p,
	avlab_1s1p,
	avlab_1s2p,
	avlab_2s1p,
	siig_1s1p_10x,
	siig_2s1p_10x,
	siig_2p1s_20x,
	siig_1s1p_20x,
	siig_2s1p_20x,
	समयdia_4078a,
	समयdia_4079h,
	समयdia_4085h,
	समयdia_4088a,
	समयdia_4089a,
	समयdia_4095a,
	समयdia_4096a,
	समयdia_4078u,
	समयdia_4079a,
	समयdia_4085u,
	समयdia_4079r,
	समयdia_4079s,
	समयdia_4079d,
	समयdia_4079e,
	समयdia_4079f,
	समयdia_9079a,
	समयdia_9079b,
	समयdia_9079c,
	wch_ch353_1s1p,
	wch_ch353_2s1p,
	wch_ch382_0s1p,
	wch_ch382_2s1p,
	brainboxes_5s1p,
	sunix_4008a,
	sunix_5069a,
	sunix_5079a,
	sunix_5099a,
पूर्ण;

/* each element directly indexed from क्रमागत list, above */
काष्ठा parport_pc_pci अणु
	पूर्णांक numports;
	काष्ठा अणु /* BAR (base address रेजिस्टरs) numbers in the config
                    space header */
		पूर्णांक lo;
		पूर्णांक hi; /* -1 अगर not there, >6 क्रम offset-method (max
                           BAR is 6) */
	पूर्ण addr[4];

	/* If set, this is called immediately after pci_enable_device.
	 * If it वापसs non-zero, no probing will take place and the
	 * ports will not be used. */
	पूर्णांक (*preinit_hook) (काष्ठा pci_dev *pdev, काष्ठा parport_pc_pci *card,
				पूर्णांक स्वतःirq, पूर्णांक स्वतःdma);

	/* If set, this is called after probing क्रम ports.  If 'failed'
	 * is non-zero we couldn't use any of the ports. */
	व्योम (*postinit_hook) (काष्ठा pci_dev *pdev,
				काष्ठा parport_pc_pci *card, पूर्णांक failed);
पूर्ण;

अटल पूर्णांक neपंचांगos_parallel_init(काष्ठा pci_dev *dev, काष्ठा parport_pc_pci *par,
				पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	/* the rule described below करोesn't hold क्रम this device */
	अगर (dev->device == PCI_DEVICE_ID_NETMOS_9835 &&
			dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_IBM &&
			dev->subप्रणाली_device == 0x0299)
		वापस -ENODEV;

	अगर (dev->device == PCI_DEVICE_ID_NETMOS_9912) अणु
		par->numports = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Neपंचांगos uses the subdevice ID to indicate the number of parallel
		 * and serial ports.  The क्रमm is 0x00PS, where <P> is the number of
		 * parallel ports and <S> is the number of serial ports.
		 */
		par->numports = (dev->subप्रणाली_device & 0xf0) >> 4;
		अगर (par->numports > ARRAY_SIZE(par->addr))
			par->numports = ARRAY_SIZE(par->addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा parport_pc_pci cards[] = अणु
	/* titan_110l */		अणु 1, अणु अणु 3, -1 पूर्ण, पूर्ण पूर्ण,
	/* titan_210l */		अणु 1, अणु अणु 3, -1 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_9xx5_combo */		अणु 1, अणु अणु 2, -1 पूर्ण, पूर्ण, neपंचांगos_parallel_init पूर्ण,
	/* neपंचांगos_9855 */		अणु 1, अणु अणु 0, -1 पूर्ण, पूर्ण, neपंचांगos_parallel_init पूर्ण,
	/* neपंचांगos_9855_2p */		अणु 2, अणु अणु 0, -1 पूर्ण, अणु 2, -1 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_9900 */		अणु1, अणु अणु 3, 4 पूर्ण, पूर्ण, neपंचांगos_parallel_init पूर्ण,
	/* neपंचांगos_9900_2p */		अणु2, अणु अणु 0, 1 पूर्ण, अणु 3, 4 पूर्ण, पूर्ण पूर्ण,
	/* neपंचांगos_99xx_1p */		अणु1, अणु अणु 0, 1 पूर्ण, पूर्ण पूर्ण,
	/* avlab_1s1p     */		अणु 1, अणु अणु 1, 2पूर्ण, पूर्ण पूर्ण,
	/* avlab_1s2p     */		अणु 2, अणु अणु 1, 2पूर्ण, अणु 3, 4 पूर्ण,पूर्ण पूर्ण,
	/* avlab_2s1p     */		अणु 1, अणु अणु 2, 3पूर्ण, पूर्ण पूर्ण,
	/* siig_1s1p_10x */		अणु 1, अणु अणु 3, 4 पूर्ण, पूर्ण पूर्ण,
	/* siig_2s1p_10x */		अणु 1, अणु अणु 4, 5 पूर्ण, पूर्ण पूर्ण,
	/* siig_2p1s_20x */		अणु 2, अणु अणु 1, 2 पूर्ण, अणु 3, 4 पूर्ण, पूर्ण पूर्ण,
	/* siig_1s1p_20x */		अणु 1, अणु अणु 1, 2 पूर्ण, पूर्ण पूर्ण,
	/* siig_2s1p_20x */		अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4078a */		अणु 1, अणु अणु 2, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079h */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4085h */             अणु 2, अणु अणु 2, -1 पूर्ण, अणु 4, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4088a */             अणु 2, अणु अणु 2, 3 पूर्ण, अणु 4, 5 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4089a */             अणु 2, अणु अणु 2, 3 पूर्ण, अणु 4, 5 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4095a */             अणु 2, अणु अणु 2, 3 पूर्ण, अणु 4, 5 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4096a */             अणु 2, अणु अणु 2, 3 पूर्ण, अणु 4, 5 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4078u */             अणु 1, अणु अणु 2, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079a */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4085u */             अणु 2, अणु अणु 2, -1 पूर्ण, अणु 4, -1 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079r */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079s */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079d */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079e */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_4079f */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_9079a */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_9079b */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* समयdia_9079c */             अणु 1, अणु अणु 2, 3 पूर्ण, पूर्ण पूर्ण,
	/* wch_ch353_1s1p*/             अणु 1, अणु अणु 1, -1पूर्ण, पूर्ण पूर्ण,
	/* wch_ch353_2s1p*/             अणु 1, अणु अणु 2, -1पूर्ण, पूर्ण पूर्ण,
	/* wch_ch382_0s1p*/		अणु 1, अणु अणु 2, -1पूर्ण, पूर्ण पूर्ण,
	/* wch_ch382_2s1p*/             अणु 1, अणु अणु 2, -1पूर्ण, पूर्ण पूर्ण,
	/* brainboxes_5s1p */           अणु 1, अणु अणु 3, -1 पूर्ण, पूर्ण पूर्ण,
	/* sunix_4008a */		अणु 1, अणु अणु 1, 2 पूर्ण, पूर्ण पूर्ण,
	/* sunix_5069a */		अणु 1, अणु अणु 1, 2 पूर्ण, पूर्ण पूर्ण,
	/* sunix_5079a */		अणु 1, अणु अणु 1, 2 पूर्ण, पूर्ण पूर्ण,
	/* sunix_5099a */		अणु 1, अणु अणु 1, 2 पूर्ण, पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा pci_device_id parport_serial_pci_tbl[] = अणु
	/* PCI cards */
	अणु PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_110L,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, titan_110l पूर्ण,
	अणु PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_210L,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, titan_210l पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9735,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9xx5_combo पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9745,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9xx5_combo पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9835,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9xx5_combo पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9845,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9xx5_combo पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9855,
	  0x1000, 0x0020, 0, 0, neपंचांगos_9855_2p पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9855,
	  0x1000, 0x0022, 0, 0, neपंचांगos_9855_2p पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9855,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, neपंचांगos_9855 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x3011, 0, 0, neपंचांगos_9900 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x3012, 0, 0, neपंचांगos_9900 पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x3020, 0, 0, neपंचांगos_9900_2p पूर्ण,
	अणु PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9912,
	  0xA000, 0x2000, 0, 0, neपंचांगos_99xx_1p पूर्ण,
	/* PCI_VENDOR_ID_AVLAB/Intek21 has another bunch of cards ...*/
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2110,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1s1p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2111,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1s1p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2112,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1s1p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2140,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1s2p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2141,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1s2p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2142,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_1s2p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2160,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_2s1p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2161,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_2s1p पूर्ण,
	अणु PCI_VENDOR_ID_AFAVLAB, 0x2162,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avlab_2s1p पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_10x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_10x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_10x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_10x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_10x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_10x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_10x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2P1S_20x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p1s_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2P1S_20x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p1s_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2P1S_20x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p1s_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_20x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_20x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_20x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_20x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_20x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x पूर्ण,
	अणु PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_20x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x पूर्ण,
	/* PCI_VENDOR_ID_TIMEDIA/SUNIX has many dअगरfering cards ...*/
	अणु 0x1409, 0x7168, 0x1409, 0x4078, 0, 0, समयdia_4078a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x4079, 0, 0, समयdia_4079h पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x4085, 0, 0, समयdia_4085h पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x4088, 0, 0, समयdia_4088a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x4089, 0, 0, समयdia_4089a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x4095, 0, 0, समयdia_4095a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x4096, 0, 0, समयdia_4096a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x5078, 0, 0, समयdia_4078u पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x5079, 0, 0, समयdia_4079a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x5085, 0, 0, समयdia_4085u पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x6079, 0, 0, समयdia_4079r पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x7079, 0, 0, समयdia_4079s पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x8079, 0, 0, समयdia_4079d पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0x9079, 0, 0, समयdia_4079e पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0xa079, 0, 0, समयdia_4079f पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0xb079, 0, 0, समयdia_9079a पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0xc079, 0, 0, समयdia_9079b पूर्ण,
	अणु 0x1409, 0x7168, 0x1409, 0xd079, 0, 0, समयdia_9079c पूर्ण,

	/* WCH CARDS */
	अणु 0x4348, 0x5053, PCI_ANY_ID, PCI_ANY_ID, 0, 0, wch_ch353_1s1pपूर्ण,
	अणु 0x4348, 0x7053, 0x4348, 0x3253, 0, 0, wch_ch353_2s1pपूर्ण,
	अणु 0x1c00, 0x3050, 0x1c00, 0x3050, 0, 0, wch_ch382_0s1pपूर्ण,
	अणु 0x1c00, 0x3250, 0x1c00, 0x3250, 0, 0, wch_ch382_2s1pपूर्ण,

	/* BrainBoxes PX272/PX306 MIO card */
	अणु PCI_VENDOR_ID_INTASHIELD, 0x4100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, brainboxes_5s1p पूर्ण,

	/* Sunix boards */
	अणु PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOR_ID_SUNIX,
	  0x0100, 0, 0, sunix_4008a पूर्ण,
	अणु PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOR_ID_SUNIX,
	  0x0101, 0, 0, sunix_5069a पूर्ण,
	अणु PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOR_ID_SUNIX,
	  0x0102, 0, 0, sunix_5079a पूर्ण,
	अणु PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOR_ID_SUNIX,
	  0x0104, 0, 0, sunix_5099a पूर्ण,

	अणु 0, पूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci,parport_serial_pci_tbl);

/*
 * This table describes the serial "geometry" of these boards.  Any
 * quirks क्रम these can be found in drivers/serial/8250_pci.c
 *
 * Cards not tested are marked n/t
 * If you have one of these cards and it works क्रम you, please tell me..
 */
अटल काष्ठा pciserial_board pci_parport_serial_boards[] = अणु
	[titan_110l] = अणु
		.flags		= FL_BASE1 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[titan_210l] = अणु
		.flags		= FL_BASE1 | FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[neपंचांगos_9xx5_combo] = अणु
		.flags		= FL_BASE0 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[neपंचांगos_9855] = अणु
		.flags		= FL_BASE2 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[neपंचांगos_9855_2p] = अणु
		.flags		= FL_BASE4 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[neपंचांगos_9900] = अणु /* n/t */
		.flags		= FL_BASE0 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[neपंचांगos_9900_2p] = अणु /* parallel only */ /* n/t */
		.flags		= FL_BASE0,
		.num_ports	= 0,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[neपंचांगos_99xx_1p] = अणु /* parallel only */ /* n/t */
		.flags		= FL_BASE0,
		.num_ports	= 0,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[avlab_1s1p] = अणु /* n/t */
		.flags		= FL_BASE0 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[avlab_1s2p] = अणु /* n/t */
		.flags		= FL_BASE0 | FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[avlab_2s1p] = अणु /* n/t */
		.flags		= FL_BASE0 | FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[siig_1s1p_10x] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 1,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,
	[siig_2s1p_10x] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[siig_2p1s_20x] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[siig_1s1p_20x] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[siig_2s1p_20x] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4078a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079h] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4085h] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4088a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4089a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4095a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4096a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4078u] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4085u] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079r] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079s] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079d] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079e] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_4079f] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_9079a] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_9079b] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[समयdia_9079c] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[wch_ch353_1s1p] = अणु
		.flags          = FL_BASE0|FL_BASE_BARS,
		.num_ports      = 1,
		.base_baud      = 115200,
		.uart_offset    = 8,
	पूर्ण,
	[wch_ch353_2s1p] = अणु
		.flags          = FL_BASE0|FL_BASE_BARS,
		.num_ports      = 2,
		.base_baud      = 115200,
		.uart_offset    = 8,
	पूर्ण,
	[wch_ch382_0s1p] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 0,
		.base_baud      = 115200,
		.uart_offset    = 8,
	पूर्ण,
	[wch_ch382_2s1p] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 2,
		.base_baud      = 115200,
		.uart_offset    = 8,
		.first_offset   = 0xC0,
	पूर्ण,
	[brainboxes_5s1p] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 5,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[sunix_4008a] = अणु
		.num_ports	= 0,
	पूर्ण,
	[sunix_5069a] = अणु
		.num_ports	= 1,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[sunix_5079a] = अणु
		.num_ports	= 2,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[sunix_5099a] = अणु
		.num_ports	= 4,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
पूर्ण;

काष्ठा parport_serial_निजी अणु
	काष्ठा serial_निजी	*serial;
	पूर्णांक num_par;
	काष्ठा parport *port[PARPORT_MAX];
	काष्ठा parport_pc_pci par;
पूर्ण;

/* Register the serial port(s) of a PCI card. */
अटल पूर्णांक serial_रेजिस्टर(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा parport_serial_निजी *priv = pci_get_drvdata (dev);
	काष्ठा pciserial_board *board;
	काष्ठा serial_निजी *serial;

	board = &pci_parport_serial_boards[id->driver_data];
	अगर (board->num_ports == 0)
		वापस 0;

	serial = pciserial_init_ports(dev, board);
	अगर (IS_ERR(serial))
		वापस PTR_ERR(serial);

	priv->serial = serial;
	वापस 0;
पूर्ण

/* Register the parallel port(s) of a PCI card. */
अटल पूर्णांक parport_रेजिस्टर(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा parport_pc_pci *card;
	काष्ठा parport_serial_निजी *priv = pci_get_drvdata (dev);
	पूर्णांक n, success = 0;

	priv->par = cards[id->driver_data];
	card = &priv->par;
	अगर (card->preinit_hook &&
	    card->preinit_hook (dev, card, PARPORT_IRQ_NONE, PARPORT_DMA_NONE))
		वापस -ENODEV;

	क्रम (n = 0; n < card->numports; n++) अणु
		काष्ठा parport *port;
		पूर्णांक lo = card->addr[n].lo;
		पूर्णांक hi = card->addr[n].hi;
		अचिन्हित दीर्घ io_lo, io_hi;
		पूर्णांक irq;

		अगर (priv->num_par == ARRAY_SIZE (priv->port)) अणु
			dev_warn(&dev->dev,
				 "only %zu parallel ports supported (%d reported)\n",
				 ARRAY_SIZE(priv->port), card->numports);
			अवरोध;
		पूर्ण

		io_lo = pci_resource_start (dev, lo);
		io_hi = 0;
		अगर ((hi >= 0) && (hi <= 6))
			io_hi = pci_resource_start (dev, hi);
		अन्यथा अगर (hi > 6)
			io_lo += hi; /* Reपूर्णांकerpret the meaning of
                                        "hi" as an offset (see SYBA
                                        def.) */
		/* TODO: test अगर sharing पूर्णांकerrupts works */
		irq = dev->irq;
		अगर (irq == IRQ_NONE) अणु
			dev_dbg(&dev->dev,
				"PCI parallel port detected: I/O at %#lx(%#lx)\n",
				io_lo, io_hi);
			irq = PARPORT_IRQ_NONE;
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->dev,
				"PCI parallel port detected: I/O at %#lx(%#lx), IRQ %d\n",
				io_lo, io_hi, irq);
		पूर्ण
		port = parport_pc_probe_port (io_lo, io_hi, irq,
			      PARPORT_DMA_NONE, &dev->dev, IRQF_SHARED);
		अगर (port) अणु
			priv->port[priv->num_par++] = port;
			success = 1;
		पूर्ण
	पूर्ण

	अगर (card->postinit_hook)
		card->postinit_hook (dev, card, !success);

	वापस 0;
पूर्ण

अटल पूर्णांक parport_serial_pci_probe(काष्ठा pci_dev *dev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा parport_serial_निजी *priv;
	पूर्णांक err;

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	pci_set_drvdata (dev, priv);

	err = pcim_enable_device(dev);
	अगर (err)
		वापस err;

	err = parport_रेजिस्टर(dev, id);
	अगर (err)
		वापस err;

	err = serial_रेजिस्टर(dev, id);
	अगर (err) अणु
		पूर्णांक i;
		क्रम (i = 0; i < priv->num_par; i++)
			parport_pc_unरेजिस्टर_port (priv->port[i]);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम parport_serial_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा parport_serial_निजी *priv = pci_get_drvdata (dev);
	पूर्णांक i;

	// Serial ports
	अगर (priv->serial)
		pciserial_हटाओ_ports(priv->serial);

	// Parallel ports
	क्रम (i = 0; i < priv->num_par; i++)
		parport_pc_unरेजिस्टर_port (priv->port[i]);

	वापस;
पूर्ण

अटल पूर्णांक __maybe_unused parport_serial_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा parport_serial_निजी *priv = dev_get_drvdata(dev);

	अगर (priv->serial)
		pciserial_suspend_ports(priv->serial);

	/* FIXME: What about parport? */
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused parport_serial_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा parport_serial_निजी *priv = dev_get_drvdata(dev);

	अगर (priv->serial)
		pciserial_resume_ports(priv->serial);

	/* FIXME: What about parport? */
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(parport_serial_pm_ops,
			 parport_serial_pci_suspend, parport_serial_pci_resume);

अटल काष्ठा pci_driver parport_serial_pci_driver = अणु
	.name		= "parport_serial",
	.id_table	= parport_serial_pci_tbl,
	.probe		= parport_serial_pci_probe,
	.हटाओ		= parport_serial_pci_हटाओ,
	.driver         = अणु
		.pm     = &parport_serial_pm_ops,
	पूर्ण,
पूर्ण;
module_pci_driver(parport_serial_pci_driver);

MODULE_AUTHOR("Tim Waugh <twaugh@redhat.com>");
MODULE_DESCRIPTION("Driver for common parallel+serial multi-I/O PCI cards");
MODULE_LICENSE("GPL");
