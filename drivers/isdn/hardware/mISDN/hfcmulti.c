<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * hfcmulti.c  low level driver क्रम hfc-4s/hfc-8s/hfc-e1 based cards
 *
 * Author	Andreas Eversberg (jolly@eversberg.eu)
 * ported to mqueue mechanism:
 *		Peter Sprenger (sprengermoving-bytes.de)
 *
 * inspired by existing hfc-pci driver:
 * Copyright 1999  by Werner Cornelius (werner@isdn-development.de)
 * Copyright 2008  by Karsten Keil (kkeil@suse.de)
 * Copyright 2008  by Andreas Eversberg (jolly@eversberg.eu)
 *
 * Thanks to Cologne Chip AG क्रम this great controller!
 */

/*
 * module parameters:
 * type:
 *	By शेष (0), the card is स्वतःmatically detected.
 *	Or use the following combinations:
 *	Bit 0-7   = 0x00001 = HFC-E1 (1 port)
 * or	Bit 0-7   = 0x00004 = HFC-4S (4 ports)
 * or	Bit 0-7   = 0x00008 = HFC-8S (8 ports)
 *	Bit 8     = 0x00100 = uLaw (instead of aLaw)
 *	Bit 9     = 0x00200 = Disable DTMF detect on all B-channels via hardware
 *	Bit 10    = spare
 *	Bit 11    = 0x00800 = Force PCM bus पूर्णांकo slave mode. (otherwhise स्वतः)
 * or   Bit 12    = 0x01000 = Force PCM bus पूर्णांकo master mode. (otherwhise स्वतः)
 *	Bit 13	  = spare
 *	Bit 14    = 0x04000 = Use बाह्यal ram (128K)
 *	Bit 15    = 0x08000 = Use बाह्यal ram (512K)
 *	Bit 16    = 0x10000 = Use 64 बारlots instead of 32
 * or	Bit 17    = 0x20000 = Use 128 बारlots instead of anything अन्यथा
 *	Bit 18    = spare
 *	Bit 19    = 0x80000 = Send the Watchकरोg a Signal (Dual E1 with Watchकरोg)
 * (all other bits are reserved and shall be 0)
 *	example: 0x20204 one HFC-4S with dपंचांगf detection and 128 बारlots on PCM
 *		 bus (PCM master)
 *
 * port: (optional or required क्रम all ports on all installed cards)
 *	HFC-4S/HFC-8S only bits:
 *	Bit 0	  = 0x001 = Use master घड़ी क्रम this S/T पूर्णांकerface
 *			    (ony once per chip).
 *	Bit 1     = 0x002 = transmitter line setup (non capacitive mode)
 *			    Don't use this unless you know what you are करोing!
 *	Bit 2     = 0x004 = Disable E-channel. (No E-channel processing)
 *	example: 0x0001,0x0000,0x0000,0x0000 one HFC-4S with master घड़ी
 *		 received from port 1
 *
 *	HFC-E1 only bits:
 *	Bit 0     = 0x0001 = पूर्णांकerface: 0=copper, 1=optical
 *	Bit 1     = 0x0002 = reserved (later क्रम 32 B-channels transparent mode)
 *	Bit 2     = 0x0004 = Report LOS
 *	Bit 3     = 0x0008 = Report AIS
 *	Bit 4     = 0x0010 = Report SLIP
 *	Bit 5     = 0x0020 = Report RDI
 *	Bit 8     = 0x0100 = Turn off CRC-4 Multअगरrame Mode, use द्विगुन frame
 *			     mode instead.
 *	Bit 9	  = 0x0200 = Force get घड़ी from पूर्णांकerface, even in NT mode.
 * or	Bit 10	  = 0x0400 = Force put घड़ी to पूर्णांकerface, even in TE mode.
 *	Bit 11    = 0x0800 = Use direct RX घड़ी क्रम PCM sync rather than PLL.
 *			     (E1 only)
 *	Bit 12-13 = 0xX000 = elastic jitter buffer (1-3), Set both bits to 0
 *			     क्रम शेष.
 * (all other bits are reserved and shall be 0)
 *
 * debug:
 *	NOTE: only one debug value must be given क्रम all cards
 *	enable debugging (see hfc_multi.h क्रम debug options)
 *
 * poll:
 *	NOTE: only one poll value must be given क्रम all cards
 *	Give the number of samples क्रम each fअगरo process.
 *	By शेष 128 is used. Decrease to reduce delay, increase to
 *	reduce cpu load. If unsure, करोn't mess with it!
 *	Valid is 8, 16, 32, 64, 128, 256.
 *
 * pcm:
 *	NOTE: only one pcm value must be given क्रम every card.
 *	The PCM bus id tells the mISDNdsp module about the connected PCM bus.
 *	By शेष (0), the PCM bus id is 100 क्रम the card that is PCM master.
 *	If multiple cards are PCM master (because they are not पूर्णांकerconnected),
 *	each card with PCM master will have increasing PCM id.
 *	All PCM busses with the same ID are expected to be connected and have
 *	common समय slots slots.
 *	Only one chip of the PCM bus must be master, the others slave.
 *	-1 means no support of PCM bus not even.
 *	Omit this value, अगर all cards are पूर्णांकerconnected or none is connected.
 *	If unsure, करोn't give this parameter.
 *
 * dmask and bmask:
 *	NOTE: One dmask value must be given क्रम every HFC-E1 card.
 *	If omitted, the E1 card has D-channel on समय slot 16, which is शेष.
 *	dmask is a 32 bit mask. The bit must be set क्रम an alternate समय slot.
 *	If multiple bits are set, multiple भव card fragments are created.
 *	For each bit set, a bmask value must be given. Each bit on the bmask
 *	value stands क्रम a B-channel. The bmask may not overlap with dmask or
 *	with other bmask values क्रम that card.
 *	Example: dmask=0x00020002 bmask=0x0000fffc,0xfffc0000
 *		This will create one fragment with D-channel on slot 1 with
 *		B-channels on slots 2..15, and a second fragment with D-channel
 *		on slot 17 with B-channels on slot 18..31. Slot 16 is unused.
 *	If bit 0 is set (dmask=0x00000001) the D-channel is on slot 0 and will
 *	not function.
 *	Example: dmask=0x00000001 bmask=0xfffffffe
 *		This will create a port with all 31 usable बारlots as
 *		B-channels.
 *	If no bits are set on bmask, no B-channel is created क्रम that fragment.
 *	Example: dmask=0xfffffffe bmask=0,0,0,0.... (31 0-values क्रम bmask)
 *		This will create 31 ports with one D-channel only.
 *	If you करोn't know how to use it, you don't need it!
 *
 * iomode:
 *	NOTE: only one mode value must be given क्रम every card.
 *	-> See hfc_multi.h क्रम HFC_IO_MODE_* values
 *	By शेष, the IO mode is pci memory IO (MEMIO).
 *	Some cards require specअगरic IO mode, so it cannot be changed.
 *	It may be useful to set IO mode to रेजिस्टर io (REGIO) to solve
 *	PCI bridge problems.
 *	If unsure, करोn't give this parameter.
 *
 * घड़ीdelay_nt:
 *	NOTE: only one घड़ीdelay_nt value must be given once क्रम all cards.
 *	Give the value of the घड़ी control रेजिस्टर (A_ST_CLK_DLY)
 *	of the S/T पूर्णांकerfaces in NT mode.
 *	This रेजिस्टर is needed क्रम the TBR3 certअगरication, so करोn't change it.
 *
 * घड़ीdelay_te:
 *	NOTE: only one घड़ीdelay_te value must be given once
 *	Give the value of the घड़ी control रेजिस्टर (A_ST_CLK_DLY)
 *	of the S/T पूर्णांकerfaces in TE mode.
 *	This रेजिस्टर is needed क्रम the TBR3 certअगरication, so करोn't change it.
 *
 * घड़ी:
 *	NOTE: only one घड़ी value must be given once
 *	Selects पूर्णांकerface with घड़ी source क्रम mISDN and applications.
 *	Set to card number starting with 1. Set to -1 to disable.
 *	By शेष, the first card is used as घड़ी source.
 *
 * hwid:
 *	NOTE: only one hwid value must be given once
 *	Enable special embedded devices with XHFC controllers.
 */

/*
 * debug रेजिस्टर access (never use this, it will flood your प्रणाली log)
 * #घोषणा HFC_REGISTER_DEBUG
 */

#घोषणा HFC_MULTI_VERSION	"2.03"

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/mISDNdsp.h>

/*
  #घोषणा IRQCOUNT_DEBUG
  #घोषणा IRQ_DEBUG
*/

#समावेश "hfc_multi.h"
#अगर_घोषित ECHOPREP
#समावेश "gaintab.h"
#पूर्ण_अगर

#घोषणा	MAX_CARDS	8
#घोषणा	MAX_PORTS	(8 * MAX_CARDS)
#घोषणा	MAX_FRAGS	(32 * MAX_CARDS)

अटल LIST_HEAD(HFClist);
अटल DEFINE_SPINLOCK(HFClock); /* global hfc list lock */

अटल व्योम ph_state_change(काष्ठा dchannel *);

अटल काष्ठा hfc_multi *syncmaster;
अटल पूर्णांक plxsd_master; /* अगर we have a master card (yet) */
अटल DEFINE_SPINLOCK(plx_lock); /* may not acquire other lock inside */

#घोषणा	TYP_E1		1
#घोषणा	TYP_4S		4
#घोषणा TYP_8S		8

अटल पूर्णांक poll_समयr = 6;	/* शेष = 128 samples = 16ms */
/* number of POLL_TIMER पूर्णांकerrupts क्रम G2 समयout (ca 1s) */
अटल पूर्णांक nt_t1_count[] = अणु 3840, 1920, 960, 480, 240, 120, 60, 30  पूर्ण;
#घोषणा	CLKDEL_TE	0x0f	/* CLKDEL in TE mode */
#घोषणा	CLKDEL_NT	0x6c	/* CLKDEL in NT mode
				   (0x60 MUST be included!) */

#घोषणा	DIP_4S	0x1		/* DIP Switches क्रम Beronet 1S/2S/4S cards */
#घोषणा	DIP_8S	0x2		/* DIP Switches क्रम Beronet 8S+ cards */
#घोषणा	DIP_E1	0x3		/* DIP Switches क्रम Beronet E1 cards */

/*
 * module stuff
 */

अटल uपूर्णांक	type[MAX_CARDS];
अटल पूर्णांक	pcm[MAX_CARDS];
अटल uपूर्णांक	dmask[MAX_CARDS];
अटल uपूर्णांक	bmask[MAX_FRAGS];
अटल uपूर्णांक	iomode[MAX_CARDS];
अटल uपूर्णांक	port[MAX_PORTS];
अटल uपूर्णांक	debug;
अटल uपूर्णांक	poll;
अटल पूर्णांक	घड़ी;
अटल uपूर्णांक	समयr;
अटल uपूर्णांक	घड़ीdelay_te = CLKDEL_TE;
अटल uपूर्णांक	घड़ीdelay_nt = CLKDEL_NT;
#घोषणा HWID_NONE	0
#घोषणा HWID_MINIP4	1
#घोषणा HWID_MINIP8	2
#घोषणा HWID_MINIP16	3
अटल uपूर्णांक	hwid = HWID_NONE;

अटल पूर्णांक	HFC_cnt, E1_cnt, bmask_cnt, Port_cnt, PCM_cnt = 99;

MODULE_AUTHOR("Andreas Eversberg");
MODULE_LICENSE("GPL");
MODULE_VERSION(HFC_MULTI_VERSION);
module_param(debug, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(poll, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(घड़ी, पूर्णांक, S_IRUGO | S_IWUSR);
module_param(समयr, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(घड़ीdelay_te, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(घड़ीdelay_nt, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param_array(type, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(pcm, पूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(dmask, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(bmask, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(iomode, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(port, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param(hwid, uपूर्णांक, S_IRUGO | S_IWUSR); /* The hardware ID */

#अगर_घोषित HFC_REGISTER_DEBUG
#घोषणा HFC_outb(hc, reg, val)					\
	(hc->HFC_outb(hc, reg, val, __func__, __LINE__))
#घोषणा HFC_outb_nodebug(hc, reg, val)					\
	(hc->HFC_outb_nodebug(hc, reg, val, __func__, __LINE__))
#घोषणा HFC_inb(hc, reg)				\
	(hc->HFC_inb(hc, reg, __func__, __LINE__))
#घोषणा HFC_inb_nodebug(hc, reg)				\
	(hc->HFC_inb_nodebug(hc, reg, __func__, __LINE__))
#घोषणा HFC_inw(hc, reg)				\
	(hc->HFC_inw(hc, reg, __func__, __LINE__))
#घोषणा HFC_inw_nodebug(hc, reg)				\
	(hc->HFC_inw_nodebug(hc, reg, __func__, __LINE__))
#घोषणा HFC_रुको(hc)				\
	(hc->HFC_रुको(hc, __func__, __LINE__))
#घोषणा HFC_रुको_nodebug(hc)				\
	(hc->HFC_रुको_nodebug(hc, __func__, __LINE__))
#अन्यथा
#घोषणा HFC_outb(hc, reg, val)		(hc->HFC_outb(hc, reg, val))
#घोषणा HFC_outb_nodebug(hc, reg, val)	(hc->HFC_outb_nodebug(hc, reg, val))
#घोषणा HFC_inb(hc, reg)		(hc->HFC_inb(hc, reg))
#घोषणा HFC_inb_nodebug(hc, reg)	(hc->HFC_inb_nodebug(hc, reg))
#घोषणा HFC_inw(hc, reg)		(hc->HFC_inw(hc, reg))
#घोषणा HFC_inw_nodebug(hc, reg)	(hc->HFC_inw_nodebug(hc, reg))
#घोषणा HFC_रुको(hc)			(hc->HFC_रुको(hc))
#घोषणा HFC_रुको_nodebug(hc)		(hc->HFC_रुको_nodebug(hc))
#पूर्ण_अगर

#अगर_घोषित CONFIG_MISDN_HFCMULTI_8xx
#समावेश "hfc_multi_8xx.h"
#पूर्ण_अगर

/* HFC_IO_MODE_PCIMEM */
अटल व्योम
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_outb_pcimem(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val,
		स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_outb_pcimem(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val)
#पूर्ण_अगर
अणु
	ग_लिखोb(val, hc->pci_membase + reg);
पूर्ण
अटल u_अक्षर
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_inb_pcimem(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_inb_pcimem(काष्ठा hfc_multi *hc, u_अक्षर reg)
#पूर्ण_अगर
अणु
	वापस पढ़ोb(hc->pci_membase + reg);
पूर्ण
अटल u_लघु
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_inw_pcimem(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_inw_pcimem(काष्ठा hfc_multi *hc, u_अक्षर reg)
#पूर्ण_अगर
अणु
	वापस पढ़ोw(hc->pci_membase + reg);
पूर्ण
अटल व्योम
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_रुको_pcimem(काष्ठा hfc_multi *hc, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_रुको_pcimem(काष्ठा hfc_multi *hc)
#पूर्ण_अगर
अणु
	जबतक (पढ़ोb(hc->pci_membase + R_STATUS) & V_BUSY)
		cpu_relax();
पूर्ण

/* HFC_IO_MODE_REGIO */
अटल व्योम
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_outb_regio(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val,
	       स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_outb_regio(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val)
#पूर्ण_अगर
अणु
	outb(reg, hc->pci_iobase + 4);
	outb(val, hc->pci_iobase);
पूर्ण
अटल u_अक्षर
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_inb_regio(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_inb_regio(काष्ठा hfc_multi *hc, u_अक्षर reg)
#पूर्ण_अगर
अणु
	outb(reg, hc->pci_iobase + 4);
	वापस inb(hc->pci_iobase);
पूर्ण
अटल u_लघु
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_inw_regio(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_inw_regio(काष्ठा hfc_multi *hc, u_अक्षर reg)
#पूर्ण_अगर
अणु
	outb(reg, hc->pci_iobase + 4);
	वापस inw(hc->pci_iobase);
पूर्ण
अटल व्योम
#अगर_घोषित HFC_REGISTER_DEBUG
HFC_रुको_regio(काष्ठा hfc_multi *hc, स्थिर अक्षर *function, पूर्णांक line)
#अन्यथा
	HFC_रुको_regio(काष्ठा hfc_multi *hc)
#पूर्ण_अगर
अणु
	outb(R_STATUS, hc->pci_iobase + 4);
	जबतक (inb(hc->pci_iobase) & V_BUSY)
		cpu_relax();
पूर्ण

#अगर_घोषित HFC_REGISTER_DEBUG
अटल व्योम
HFC_outb_debug(काष्ठा hfc_multi *hc, u_अक्षर reg, u_अक्षर val,
	       स्थिर अक्षर *function, पूर्णांक line)
अणु
	अक्षर regname[256] = "", bits[9] = "xxxxxxxx";
	पूर्णांक i;

	i = -1;
	जबतक (hfc_रेजिस्टर_names[++i].name) अणु
		अगर (hfc_रेजिस्टर_names[i].reg == reg)
			म_जोड़ो(regname, hfc_रेजिस्टर_names[i].name);
	पूर्ण
	अगर (regname[0] == '\0')
		म_नकल(regname, "register");

	bits[7] = '0' + (!!(val & 1));
	bits[6] = '0' + (!!(val & 2));
	bits[5] = '0' + (!!(val & 4));
	bits[4] = '0' + (!!(val & 8));
	bits[3] = '0' + (!!(val & 16));
	bits[2] = '0' + (!!(val & 32));
	bits[1] = '0' + (!!(val & 64));
	bits[0] = '0' + (!!(val & 128));
	prपूर्णांकk(KERN_DEBUG
	       "HFC_outb(chip %d, %02x=%s, 0x%02x=%s); in %s() line %d\n",
	       hc->id, reg, regname, val, bits, function, line);
	HFC_outb_nodebug(hc, reg, val);
पूर्ण
अटल u_अक्षर
HFC_inb_debug(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
अणु
	अक्षर regname[256] = "", bits[9] = "xxxxxxxx";
	u_अक्षर val = HFC_inb_nodebug(hc, reg);
	पूर्णांक i;

	i = 0;
	जबतक (hfc_रेजिस्टर_names[i++].name)
		;
	जबतक (hfc_रेजिस्टर_names[++i].name) अणु
		अगर (hfc_रेजिस्टर_names[i].reg == reg)
			म_जोड़ो(regname, hfc_रेजिस्टर_names[i].name);
	पूर्ण
	अगर (regname[0] == '\0')
		म_नकल(regname, "register");

	bits[7] = '0' + (!!(val & 1));
	bits[6] = '0' + (!!(val & 2));
	bits[5] = '0' + (!!(val & 4));
	bits[4] = '0' + (!!(val & 8));
	bits[3] = '0' + (!!(val & 16));
	bits[2] = '0' + (!!(val & 32));
	bits[1] = '0' + (!!(val & 64));
	bits[0] = '0' + (!!(val & 128));
	prपूर्णांकk(KERN_DEBUG
	       "HFC_inb(chip %d, %02x=%s) = 0x%02x=%s; in %s() line %d\n",
	       hc->id, reg, regname, val, bits, function, line);
	वापस val;
पूर्ण
अटल u_लघु
HFC_inw_debug(काष्ठा hfc_multi *hc, u_अक्षर reg, स्थिर अक्षर *function, पूर्णांक line)
अणु
	अक्षर regname[256] = "";
	u_लघु val = HFC_inw_nodebug(hc, reg);
	पूर्णांक i;

	i = 0;
	जबतक (hfc_रेजिस्टर_names[i++].name)
		;
	जबतक (hfc_रेजिस्टर_names[++i].name) अणु
		अगर (hfc_रेजिस्टर_names[i].reg == reg)
			म_जोड़ो(regname, hfc_रेजिस्टर_names[i].name);
	पूर्ण
	अगर (regname[0] == '\0')
		म_नकल(regname, "register");

	prपूर्णांकk(KERN_DEBUG
	       "HFC_inw(chip %d, %02x=%s) = 0x%04x; in %s() line %d\n",
	       hc->id, reg, regname, val, function, line);
	वापस val;
पूर्ण
अटल व्योम
HFC_रुको_debug(काष्ठा hfc_multi *hc, स्थिर अक्षर *function, पूर्णांक line)
अणु
	prपूर्णांकk(KERN_DEBUG "HFC_wait(chip %d); in %s() line %d\n",
	       hc->id, function, line);
	HFC_रुको_nodebug(hc);
पूर्ण
#पूर्ण_अगर

/* ग_लिखो fअगरo data (REGIO) */
अटल व्योम
ग_लिखो_fअगरo_regio(काष्ठा hfc_multi *hc, u_अक्षर *data, पूर्णांक len)
अणु
	outb(A_FIFO_DATA0, (hc->pci_iobase) + 4);
	जबतक (len >> 2) अणु
		outl(cpu_to_le32(*(u32 *)data), hc->pci_iobase);
		data += 4;
		len -= 4;
	पूर्ण
	जबतक (len >> 1) अणु
		outw(cpu_to_le16(*(u16 *)data), hc->pci_iobase);
		data += 2;
		len -= 2;
	पूर्ण
	जबतक (len) अणु
		outb(*data, hc->pci_iobase);
		data++;
		len--;
	पूर्ण
पूर्ण
/* ग_लिखो fअगरo data (PCIMEM) */
अटल व्योम
ग_लिखो_fअगरo_pcimem(काष्ठा hfc_multi *hc, u_अक्षर *data, पूर्णांक len)
अणु
	जबतक (len >> 2) अणु
		ग_लिखोl(cpu_to_le32(*(u32 *)data),
		       hc->pci_membase + A_FIFO_DATA0);
		data += 4;
		len -= 4;
	पूर्ण
	जबतक (len >> 1) अणु
		ग_लिखोw(cpu_to_le16(*(u16 *)data),
		       hc->pci_membase + A_FIFO_DATA0);
		data += 2;
		len -= 2;
	पूर्ण
	जबतक (len) अणु
		ग_लिखोb(*data, hc->pci_membase + A_FIFO_DATA0);
		data++;
		len--;
	पूर्ण
पूर्ण

/* पढ़ो fअगरo data (REGIO) */
अटल व्योम
पढ़ो_fअगरo_regio(काष्ठा hfc_multi *hc, u_अक्षर *data, पूर्णांक len)
अणु
	outb(A_FIFO_DATA0, (hc->pci_iobase) + 4);
	जबतक (len >> 2) अणु
		*(u32 *)data = le32_to_cpu(inl(hc->pci_iobase));
		data += 4;
		len -= 4;
	पूर्ण
	जबतक (len >> 1) अणु
		*(u16 *)data = le16_to_cpu(inw(hc->pci_iobase));
		data += 2;
		len -= 2;
	पूर्ण
	जबतक (len) अणु
		*data = inb(hc->pci_iobase);
		data++;
		len--;
	पूर्ण
पूर्ण

/* पढ़ो fअगरo data (PCIMEM) */
अटल व्योम
पढ़ो_fअगरo_pcimem(काष्ठा hfc_multi *hc, u_अक्षर *data, पूर्णांक len)
अणु
	जबतक (len >> 2) अणु
		*(u32 *)data =
			le32_to_cpu(पढ़ोl(hc->pci_membase + A_FIFO_DATA0));
		data += 4;
		len -= 4;
	पूर्ण
	जबतक (len >> 1) अणु
		*(u16 *)data =
			le16_to_cpu(पढ़ोw(hc->pci_membase + A_FIFO_DATA0));
		data += 2;
		len -= 2;
	पूर्ण
	जबतक (len) अणु
		*data = पढ़ोb(hc->pci_membase + A_FIFO_DATA0);
		data++;
		len--;
	पूर्ण
पूर्ण

अटल व्योम
enable_hwirq(काष्ठा hfc_multi *hc)
अणु
	hc->hw.r_irq_ctrl |= V_GLOB_IRQ_EN;
	HFC_outb(hc, R_IRQ_CTRL, hc->hw.r_irq_ctrl);
पूर्ण

अटल व्योम
disable_hwirq(काष्ठा hfc_multi *hc)
अणु
	hc->hw.r_irq_ctrl &= ~((u_अक्षर)V_GLOB_IRQ_EN);
	HFC_outb(hc, R_IRQ_CTRL, hc->hw.r_irq_ctrl);
पूर्ण

#घोषणा	NUM_EC 2
#घोषणा	MAX_TDM_CHAN 32


अटल अंतरभूत व्योम
enablepcibridge(काष्ठा hfc_multi *c)
अणु
	HFC_outb(c, R_BRG_PCM_CFG, (0x0 << 6) | 0x3); /* was _io beक्रमe */
पूर्ण

अटल अंतरभूत व्योम
disablepcibridge(काष्ठा hfc_multi *c)
अणु
	HFC_outb(c, R_BRG_PCM_CFG, (0x0 << 6) | 0x2); /* was _io beक्रमe */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
पढ़ोpcibridge(काष्ठा hfc_multi *hc, अचिन्हित अक्षर address)
अणु
	अचिन्हित लघु cipv;
	अचिन्हित अक्षर data;

	अगर (!hc->pci_iobase)
		वापस 0;

	/* slow करोwn a PCI पढ़ो access by 1 PCI घड़ी cycle */
	HFC_outb(hc, R_CTRL, 0x4); /*was _io beक्रमe*/

	अगर (address == 0)
		cipv = 0x4000;
	अन्यथा
		cipv = 0x5800;

	/* select local bridge port address by writing to CIP port */
	/* data = HFC_inb(c, cipv); * was _io beक्रमe */
	outw(cipv, hc->pci_iobase + 4);
	data = inb(hc->pci_iobase);

	/* restore R_CTRL क्रम normal PCI पढ़ो cycle speed */
	HFC_outb(hc, R_CTRL, 0x0); /* was _io beक्रमe */

	वापस data;
पूर्ण

अटल अंतरभूत व्योम
ग_लिखोpcibridge(काष्ठा hfc_multi *hc, अचिन्हित अक्षर address, अचिन्हित अक्षर data)
अणु
	अचिन्हित लघु cipv;
	अचिन्हित पूर्णांक datav;

	अगर (!hc->pci_iobase)
		वापस;

	अगर (address == 0)
		cipv = 0x4000;
	अन्यथा
		cipv = 0x5800;

	/* select local bridge port address by writing to CIP port */
	outw(cipv, hc->pci_iobase + 4);
	/* define a 32 bit dword with 4 identical bytes क्रम ग_लिखो sequence */
	datav = data | ((__u32) data << 8) | ((__u32) data << 16) |
		((__u32) data << 24);

	/*
	 * ग_लिखो this 32 bit dword to the bridge data port
	 * this will initiate a ग_लिखो sequence of up to 4 ग_लिखोs to the same
	 * address on the local bus पूर्णांकerface the number of ग_लिखो accesses
	 * is undefined but >=1 and depends on the next PCI transaction
	 * during ग_लिखो sequence on the local bus
	 */
	outl(datav, hc->pci_iobase);
पूर्ण

अटल अंतरभूत व्योम
cpld_set_reg(काष्ठा hfc_multi *hc, अचिन्हित अक्षर reg)
अणु
	/* Do data pin पढ़ो low byte */
	HFC_outb(hc, R_GPIO_OUT1, reg);
पूर्ण

अटल अंतरभूत व्योम
cpld_ग_लिखो_reg(काष्ठा hfc_multi *hc, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	cpld_set_reg(hc, reg);

	enablepcibridge(hc);
	ग_लिखोpcibridge(hc, 1, val);
	disablepcibridge(hc);

	वापस;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
cpld_पढ़ो_reg(काष्ठा hfc_multi *hc, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर bytein;

	cpld_set_reg(hc, reg);

	/* Do data pin पढ़ो low byte */
	HFC_outb(hc, R_GPIO_OUT1, reg);

	enablepcibridge(hc);
	bytein = पढ़ोpcibridge(hc, 1);
	disablepcibridge(hc);

	वापस bytein;
पूर्ण

अटल अंतरभूत व्योम
vpm_ग_लिखो_address(काष्ठा hfc_multi *hc, अचिन्हित लघु addr)
अणु
	cpld_ग_लिखो_reg(hc, 0, 0xff & addr);
	cpld_ग_लिखो_reg(hc, 1, 0x01 & (addr >> 8));
पूर्ण

अटल अंतरभूत अचिन्हित लघु
vpm_पढ़ो_address(काष्ठा hfc_multi *c)
अणु
	अचिन्हित लघु addr;
	अचिन्हित लघु highbit;

	addr = cpld_पढ़ो_reg(c, 0);
	highbit = cpld_पढ़ो_reg(c, 1);

	addr = addr | (highbit << 8);

	वापस addr & 0x1ff;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
vpm_in(काष्ठा hfc_multi *c, पूर्णांक which, अचिन्हित लघु addr)
अणु
	अचिन्हित अक्षर res;

	vpm_ग_लिखो_address(c, addr);

	अगर (!which)
		cpld_set_reg(c, 2);
	अन्यथा
		cpld_set_reg(c, 3);

	enablepcibridge(c);
	res = पढ़ोpcibridge(c, 1);
	disablepcibridge(c);

	cpld_set_reg(c, 0);

	वापस res;
पूर्ण

अटल अंतरभूत व्योम
vpm_out(काष्ठा hfc_multi *c, पूर्णांक which, अचिन्हित लघु addr,
	अचिन्हित अक्षर data)
अणु
	vpm_ग_लिखो_address(c, addr);

	enablepcibridge(c);

	अगर (!which)
		cpld_set_reg(c, 2);
	अन्यथा
		cpld_set_reg(c, 3);

	ग_लिखोpcibridge(c, 1, data);

	cpld_set_reg(c, 0);

	disablepcibridge(c);

	अणु
		अचिन्हित अक्षर regin;
		regin = vpm_in(c, which, addr);
		अगर (regin != data)
			prपूर्णांकk(KERN_DEBUG "Wrote 0x%x to register 0x%x but got back "
			       "0x%x\n", data, addr, regin);
	पूर्ण

पूर्ण


अटल व्योम
vpm_init(काष्ठा hfc_multi *wc)
अणु
	अचिन्हित अक्षर reg;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक i, x, y;
	अचिन्हित पूर्णांक ver;

	क्रम (x = 0; x < NUM_EC; x++) अणु
		/* Setup GPIO's */
		अगर (!x) अणु
			ver = vpm_in(wc, x, 0x1a0);
			prपूर्णांकk(KERN_DEBUG "VPM: Chip %d: ver %02x\n", x, ver);
		पूर्ण

		क्रम (y = 0; y < 4; y++) अणु
			vpm_out(wc, x, 0x1a8 + y, 0x00); /* GPIO out */
			vpm_out(wc, x, 0x1ac + y, 0x00); /* GPIO dir */
			vpm_out(wc, x, 0x1b0 + y, 0x00); /* GPIO sel */
		पूर्ण

		/* Setup TDM path - sets fsync and tdm_clk as inमाला_दो */
		reg = vpm_in(wc, x, 0x1a3); /* misc_con */
		vpm_out(wc, x, 0x1a3, reg & ~2);

		/* Setup Echo length (256 taps) */
		vpm_out(wc, x, 0x022, 1);
		vpm_out(wc, x, 0x023, 0xff);

		/* Setup बारlots */
		vpm_out(wc, x, 0x02f, 0x00);
		mask = 0x02020202 << (x * 4);

		/* Setup the tdm channel masks क्रम all chips */
		क्रम (i = 0; i < 4; i++)
			vpm_out(wc, x, 0x33 - i, (mask >> (i << 3)) & 0xff);

		/* Setup convergence rate */
		prपूर्णांकk(KERN_DEBUG "VPM: A-law mode\n");
		reg = 0x00 | 0x10 | 0x01;
		vpm_out(wc, x, 0x20, reg);
		prपूर्णांकk(KERN_DEBUG "VPM reg 0x20 is %x\n", reg);
		/*vpm_out(wc, x, 0x20, (0x00 | 0x08 | 0x20 | 0x10)); */

		vpm_out(wc, x, 0x24, 0x02);
		reg = vpm_in(wc, x, 0x24);
		prपूर्णांकk(KERN_DEBUG "NLP Thresh is set to %d (0x%x)\n", reg, reg);

		/* Initialize echo cans */
		क्रम (i = 0; i < MAX_TDM_CHAN; i++) अणु
			अगर (mask & (0x00000001 << i))
				vpm_out(wc, x, i, 0x00);
		पूर्ण

		/*
		 * ARM arch at least disallows a udelay of
		 * more than 2ms... it gives a fake "__bad_udelay"
		 * reference at link-समय.
		 * दीर्घ delays in kernel code are pretty sucky anyway
		 * क्रम now work around it using 5 x 2ms instead of 1 x 10ms
		 */

		udelay(2000);
		udelay(2000);
		udelay(2000);
		udelay(2000);
		udelay(2000);

		/* Put in bypass mode */
		क्रम (i = 0; i < MAX_TDM_CHAN; i++) अणु
			अगर (mask & (0x00000001 << i))
				vpm_out(wc, x, i, 0x01);
		पूर्ण

		/* Enable bypass */
		क्रम (i = 0; i < MAX_TDM_CHAN; i++) अणु
			अगर (mask & (0x00000001 << i))
				vpm_out(wc, x, 0x78 + i, 0x01);
		पूर्ण

	पूर्ण
पूर्ण

#अगर_घोषित UNUSED
अटल व्योम
vpm_check(काष्ठा hfc_multi *hcपंचांगp)
अणु
	अचिन्हित अक्षर gpi2;

	gpi2 = HFC_inb(hcपंचांगp, R_GPI_IN2);

	अगर ((gpi2 & 0x3) != 0x3)
		prपूर्णांकk(KERN_DEBUG "Got interrupt 0x%x from VPM!\n", gpi2);
पूर्ण
#पूर्ण_अगर /* UNUSED */


/*
 * Interface to enable/disable the HW Echocan
 *
 * these functions are called within a spin_lock_irqsave on
 * the channel instance lock, so we are not disturbed by irqs
 *
 * we can later easily change the पूर्णांकerface to make  other
 * things configurable, क्रम now we configure the taps
 *
 */

अटल व्योम
vpm_echocan_on(काष्ठा hfc_multi *hc, पूर्णांक ch, पूर्णांक taps)
अणु
	अचिन्हित पूर्णांक बारlot;
	अचिन्हित पूर्णांक unit;
	काष्ठा bchannel *bch = hc->chan[ch].bch;
#अगर_घोषित TXADJ
	पूर्णांक txadj = -4;
	काष्ठा sk_buff *skb;
#पूर्ण_अगर
	अगर (hc->chan[ch].protocol != ISDN_P_B_RAW)
		वापस;

	अगर (!bch)
		वापस;

#अगर_घोषित TXADJ
	skb = _alloc_mISDN_skb(PH_CONTROL_IND, HFC_VOL_CHANGE_TX,
			       माप(पूर्णांक), &txadj, GFP_ATOMIC);
	अगर (skb)
		recv_Bchannel_skb(bch, skb);
#पूर्ण_अगर

	बारlot = ((ch / 4) * 8) + ((ch % 4) * 4) + 1;
	unit = ch % 4;

	prपूर्णांकk(KERN_NOTICE "vpm_echocan_on called taps [%d] on timeslot %d\n",
	       taps, बारlot);

	vpm_out(hc, unit, बारlot, 0x7e);
पूर्ण

अटल व्योम
vpm_echocan_off(काष्ठा hfc_multi *hc, पूर्णांक ch)
अणु
	अचिन्हित पूर्णांक बारlot;
	अचिन्हित पूर्णांक unit;
	काष्ठा bchannel *bch = hc->chan[ch].bch;
#अगर_घोषित TXADJ
	पूर्णांक txadj = 0;
	काष्ठा sk_buff *skb;
#पूर्ण_अगर

	अगर (hc->chan[ch].protocol != ISDN_P_B_RAW)
		वापस;

	अगर (!bch)
		वापस;

#अगर_घोषित TXADJ
	skb = _alloc_mISDN_skb(PH_CONTROL_IND, HFC_VOL_CHANGE_TX,
			       माप(पूर्णांक), &txadj, GFP_ATOMIC);
	अगर (skb)
		recv_Bchannel_skb(bch, skb);
#पूर्ण_अगर

	बारlot = ((ch / 4) * 8) + ((ch % 4) * 4) + 1;
	unit = ch % 4;

	prपूर्णांकk(KERN_NOTICE "vpm_echocan_off called on timeslot %d\n",
	       बारlot);
	/* FILLME */
	vpm_out(hc, unit, बारlot, 0x01);
पूर्ण


/*
 * Speech Design resync feature
 * NOTE: This is called someबार outside पूर्णांकerrupt handler.
 * We must lock irqsave, so no other पूर्णांकerrupt (other card) will occur!
 * Also multiple पूर्णांकerrupts may nest, so must lock each access (lists, card)!
 */
अटल अंतरभूत व्योम
hfcmulti_resync(काष्ठा hfc_multi *locked, काष्ठा hfc_multi *newmaster, पूर्णांक rm)
अणु
	काष्ठा hfc_multi *hc, *next, *pcmmaster = शून्य;
	व्योम __iomem *plx_acc_32;
	u_पूर्णांक pv;
	u_दीर्घ flags;

	spin_lock_irqsave(&HFClock, flags);
	spin_lock(&plx_lock); /* must be locked inside other locks */

	अगर (debug & DEBUG_HFCMULTI_PLXSD)
		prपूर्णांकk(KERN_DEBUG "%s: RESYNC(syncmaster=0x%p)\n",
		       __func__, syncmaster);

	/* select new master */
	अगर (newmaster) अणु
		अगर (debug & DEBUG_HFCMULTI_PLXSD)
			prपूर्णांकk(KERN_DEBUG "using provided controller\n");
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe(hc, next, &HFClist, list) अणु
			अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
				अगर (hc->syncronized) अणु
					newmaster = hc;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable sync of all cards */
	list_क्रम_each_entry_safe(hc, next, &HFClist, list) अणु
		अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			plx_acc_32 = hc->plx_membase + PLX_GPIOC;
			pv = पढ़ोl(plx_acc_32);
			pv &= ~PLX_SYNC_O_EN;
			ग_लिखोl(pv, plx_acc_32);
			अगर (test_bit(HFC_CHIP_PCM_MASTER, &hc->chip)) अणु
				pcmmaster = hc;
				अगर (hc->ctype == HFC_TYPE_E1) अणु
					अगर (debug & DEBUG_HFCMULTI_PLXSD)
						prपूर्णांकk(KERN_DEBUG
						       "Schedule SYNC_I\n");
					hc->e1_resync |= 1; /* get SYNC_I */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (newmaster) अणु
		hc = newmaster;
		अगर (debug & DEBUG_HFCMULTI_PLXSD)
			prपूर्णांकk(KERN_DEBUG "id=%d (0x%p) = syncronized with "
			       "interface.\n", hc->id, hc);
		/* Enable new sync master */
		plx_acc_32 = hc->plx_membase + PLX_GPIOC;
		pv = पढ़ोl(plx_acc_32);
		pv |= PLX_SYNC_O_EN;
		ग_लिखोl(pv, plx_acc_32);
		/* चयन to jatt PLL, अगर not disabled by RX_SYNC */
		अगर (hc->ctype == HFC_TYPE_E1
		    && !test_bit(HFC_CHIP_RX_SYNC, &hc->chip)) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG "Schedule jatt PLL\n");
			hc->e1_resync |= 2; /* चयन to jatt */
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pcmmaster) अणु
			hc = pcmmaster;
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG
				       "id=%d (0x%p) = PCM master syncronized "
				       "with QUARTZ\n", hc->id, hc);
			अगर (hc->ctype == HFC_TYPE_E1) अणु
				/* Use the crystal घड़ी क्रम the PCM
				   master card */
				अगर (debug & DEBUG_HFCMULTI_PLXSD)
					prपूर्णांकk(KERN_DEBUG
					       "Schedule QUARTZ for HFC-E1\n");
				hc->e1_resync |= 4; /* चयन quartz */
			पूर्ण अन्यथा अणु
				अगर (debug & DEBUG_HFCMULTI_PLXSD)
					prपूर्णांकk(KERN_DEBUG
					       "QUARTZ is automatically "
					       "enabled by HFC-%dS\n", hc->ctype);
			पूर्ण
			plx_acc_32 = hc->plx_membase + PLX_GPIOC;
			pv = पढ़ोl(plx_acc_32);
			pv |= PLX_SYNC_O_EN;
			ग_लिखोl(pv, plx_acc_32);
		पूर्ण अन्यथा
			अगर (!rm)
				prपूर्णांकk(KERN_ERR "%s no pcm master, this MUST "
				       "not happen!\n", __func__);
	पूर्ण
	syncmaster = newmaster;

	spin_unlock(&plx_lock);
	spin_unlock_irqrestore(&HFClock, flags);
पूर्ण

/* This must be called AND hc must be locked irqsave!!! */
अटल अंतरभूत व्योम
plxsd_checksync(काष्ठा hfc_multi *hc, पूर्णांक rm)
अणु
	अगर (hc->syncronized) अणु
		अगर (syncmaster == शून्य) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG "%s: GOT sync on card %d"
				       " (id=%d)\n", __func__, hc->id + 1,
				       hc->id);
			hfcmulti_resync(hc, hc, rm);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (syncmaster == hc) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG "%s: LOST sync on card %d"
				       " (id=%d)\n", __func__, hc->id + 1,
				       hc->id);
			hfcmulti_resync(hc, शून्य, rm);
		पूर्ण
	पूर्ण
पूर्ण


/*
 * मुक्त hardware resources used by driver
 */
अटल व्योम
release_io_hfcmulti(काष्ठा hfc_multi *hc)
अणु
	व्योम __iomem *plx_acc_32;
	u_पूर्णांक	pv;
	u_दीर्घ	plx_flags;

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: entered\n", __func__);

	/* soft reset also masks all पूर्णांकerrupts */
	hc->hw.r_cirm |= V_SRES;
	HFC_outb(hc, R_CIRM, hc->hw.r_cirm);
	udelay(1000);
	hc->hw.r_cirm &= ~V_SRES;
	HFC_outb(hc, R_CIRM, hc->hw.r_cirm);
	udelay(1000); /* instead of 'wait' that may cause locking */

	/* release Speech Design card, अगर PLX was initialized */
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip) && hc->plx_membase) अणु
		अगर (debug & DEBUG_HFCMULTI_PLXSD)
			prपूर्णांकk(KERN_DEBUG "%s: release PLXSD card %d\n",
			       __func__, hc->id + 1);
		spin_lock_irqsave(&plx_lock, plx_flags);
		plx_acc_32 = hc->plx_membase + PLX_GPIOC;
		ग_लिखोl(PLX_GPIOC_INIT, plx_acc_32);
		pv = पढ़ोl(plx_acc_32);
		/* Termination off */
		pv &= ~PLX_TERM_ON;
		/* Disconnect the PCM */
		pv |= PLX_SLAVE_EN_N;
		pv &= ~PLX_MASTER_EN;
		pv &= ~PLX_SYNC_O_EN;
		/* Put the DSP in Reset */
		pv &= ~PLX_DSP_RES_N;
		ग_लिखोl(pv, plx_acc_32);
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PCM off: PLX_GPIO=%x\n",
			       __func__, pv);
		spin_unlock_irqrestore(&plx_lock, plx_flags);
	पूर्ण

	/* disable memory mapped ports / io ports */
	test_and_clear_bit(HFC_CHIP_PLXSD, &hc->chip); /* prevent resync */
	अगर (hc->pci_dev)
		pci_ग_लिखो_config_word(hc->pci_dev, PCI_COMMAND, 0);
	अगर (hc->pci_membase)
		iounmap(hc->pci_membase);
	अगर (hc->plx_membase)
		iounmap(hc->plx_membase);
	अगर (hc->pci_iobase)
		release_region(hc->pci_iobase, 8);
	अगर (hc->xhfc_membase)
		iounmap((व्योम *)hc->xhfc_membase);

	अगर (hc->pci_dev) अणु
		pci_disable_device(hc->pci_dev);
		pci_set_drvdata(hc->pci_dev, शून्य);
	पूर्ण
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: done\n", __func__);
पूर्ण

/*
 * function called to reset the HFC chip. A complete software reset of chip
 * and fअगरos is करोne. All configuration of the chip is करोne.
 */

अटल पूर्णांक
init_chip(काष्ठा hfc_multi *hc)
अणु
	u_दीर्घ			flags, val, val2 = 0, rev;
	पूर्णांक			i, err = 0;
	u_अक्षर			r_conf_en, rval;
	व्योम __iomem		*plx_acc_32;
	u_पूर्णांक			pv;
	u_दीर्घ			plx_flags, hfc_flags;
	पूर्णांक			plx_count;
	काष्ठा hfc_multi	*pos, *next, *plx_last_hc;

	spin_lock_irqsave(&hc->lock, flags);
	/* reset all रेजिस्टरs */
	स_रखो(&hc->hw, 0, माप(काष्ठा hfcm_hw));

	/* revision check */
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: entered\n", __func__);
	val = HFC_inb(hc, R_CHIP_ID);
	अगर ((val >> 4) != 0x8 && (val >> 4) != 0xc && (val >> 4) != 0xe &&
	    (val >> 1) != 0x31) अणु
		prपूर्णांकk(KERN_INFO "HFC_multi: unknown CHIP_ID:%x\n", (u_पूर्णांक)val);
		err = -EIO;
		जाओ out;
	पूर्ण
	rev = HFC_inb(hc, R_CHIP_RV);
	prपूर्णांकk(KERN_INFO
	       "HFC_multi: detected HFC with chip ID=0x%lx revision=%ld%s\n",
	       val, rev, (rev == 0 && (hc->ctype != HFC_TYPE_XHFC)) ?
	       " (old FIFO handling)" : "");
	अगर (hc->ctype != HFC_TYPE_XHFC && rev == 0) अणु
		test_and_set_bit(HFC_CHIP_REVISION0, &hc->chip);
		prपूर्णांकk(KERN_WARNING
		       "HFC_multi: NOTE: Your chip is revision 0, "
		       "ask Cologne Chip for update. Newer chips "
		       "have a better FIFO handling. Old chips "
		       "still work but may have slightly lower "
		       "HDLC transmit performance.\n");
	पूर्ण
	अगर (rev > 1) अणु
		prपूर्णांकk(KERN_WARNING "HFC_multi: WARNING: This driver doesn't "
		       "consider chip revision = %ld. The chip / "
		       "bridge may not work.\n", rev);
	पूर्ण

	/* set s-ram size */
	hc->Flen = 0x10;
	hc->Zmin = 0x80;
	hc->Zlen = 384;
	hc->DTMFbase = 0x1000;
	अगर (test_bit(HFC_CHIP_EXRAM_128, &hc->chip)) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: changing to 128K external RAM\n",
			       __func__);
		hc->hw.r_ctrl |= V_EXT_RAM;
		hc->hw.r_ram_sz = 1;
		hc->Flen = 0x20;
		hc->Zmin = 0xc0;
		hc->Zlen = 1856;
		hc->DTMFbase = 0x2000;
	पूर्ण
	अगर (test_bit(HFC_CHIP_EXRAM_512, &hc->chip)) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: changing to 512K external RAM\n",
			       __func__);
		hc->hw.r_ctrl |= V_EXT_RAM;
		hc->hw.r_ram_sz = 2;
		hc->Flen = 0x20;
		hc->Zmin = 0xc0;
		hc->Zlen = 8000;
		hc->DTMFbase = 0x2000;
	पूर्ण
	अगर (hc->ctype == HFC_TYPE_XHFC) अणु
		hc->Flen = 0x8;
		hc->Zmin = 0x0;
		hc->Zlen = 64;
		hc->DTMFbase = 0x0;
	पूर्ण
	hc->max_trans = poll << 1;
	अगर (hc->max_trans > hc->Zlen)
		hc->max_trans = hc->Zlen;

	/* Speech Design PLX bridge */
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
		अगर (debug & DEBUG_HFCMULTI_PLXSD)
			prपूर्णांकk(KERN_DEBUG "%s: initializing PLXSD card %d\n",
			       __func__, hc->id + 1);
		spin_lock_irqsave(&plx_lock, plx_flags);
		plx_acc_32 = hc->plx_membase + PLX_GPIOC;
		ग_लिखोl(PLX_GPIOC_INIT, plx_acc_32);
		pv = पढ़ोl(plx_acc_32);
		/* The first and the last cards are terminating the PCM bus */
		pv |= PLX_TERM_ON; /* hc is currently the last */
		/* Disconnect the PCM */
		pv |= PLX_SLAVE_EN_N;
		pv &= ~PLX_MASTER_EN;
		pv &= ~PLX_SYNC_O_EN;
		/* Put the DSP in Reset */
		pv &= ~PLX_DSP_RES_N;
		ग_लिखोl(pv, plx_acc_32);
		spin_unlock_irqrestore(&plx_lock, plx_flags);
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: slave/term: PLX_GPIO=%x\n",
			       __func__, pv);
		/*
		 * If we are the 3rd PLXSD card or higher, we must turn
		 * termination of last PLXSD card off.
		 */
		spin_lock_irqsave(&HFClock, hfc_flags);
		plx_count = 0;
		plx_last_hc = शून्य;
		list_क्रम_each_entry_safe(pos, next, &HFClist, list) अणु
			अगर (test_bit(HFC_CHIP_PLXSD, &pos->chip)) अणु
				plx_count++;
				अगर (pos != hc)
					plx_last_hc = pos;
			पूर्ण
		पूर्ण
		अगर (plx_count >= 3) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG "%s: card %d is between, so "
				       "we disable termination\n",
				       __func__, plx_last_hc->id + 1);
			spin_lock_irqsave(&plx_lock, plx_flags);
			plx_acc_32 = plx_last_hc->plx_membase + PLX_GPIOC;
			pv = पढ़ोl(plx_acc_32);
			pv &= ~PLX_TERM_ON;
			ग_लिखोl(pv, plx_acc_32);
			spin_unlock_irqrestore(&plx_lock, plx_flags);
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: term off: PLX_GPIO=%x\n",
				       __func__, pv);
		पूर्ण
		spin_unlock_irqrestore(&HFClock, hfc_flags);
		hc->hw.r_pcm_md0 = V_F0_LEN; /* shअगरt घड़ी क्रम DSP */
	पूर्ण

	अगर (test_bit(HFC_CHIP_EMBSD, &hc->chip))
		hc->hw.r_pcm_md0 = V_F0_LEN; /* shअगरt घड़ी क्रम DSP */

	/* we only want the real Z2 पढ़ो-poपूर्णांकer क्रम revision > 0 */
	अगर (!test_bit(HFC_CHIP_REVISION0, &hc->chip))
		hc->hw.r_ram_sz |= V_FZ_MD;

	/* select pcm mode */
	अगर (test_bit(HFC_CHIP_PCM_SLAVE, &hc->chip)) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: setting PCM into slave mode\n",
			       __func__);
	पूर्ण अन्यथा
		अगर (test_bit(HFC_CHIP_PCM_MASTER, &hc->chip) && !plxsd_master) अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: setting PCM into master mode\n",
				       __func__);
			hc->hw.r_pcm_md0 |= V_PCM_MD;
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: performing PCM auto detect\n",
				       __func__);
		पूर्ण

	/* soft reset */
	HFC_outb(hc, R_CTRL, hc->hw.r_ctrl);
	अगर (hc->ctype == HFC_TYPE_XHFC)
		HFC_outb(hc, 0x0C /* R_FIFO_THRES */,
			 0x11 /* 16 Bytes TX/RX */);
	अन्यथा
		HFC_outb(hc, R_RAM_SZ, hc->hw.r_ram_sz);
	HFC_outb(hc, R_FIFO_MD, 0);
	अगर (hc->ctype == HFC_TYPE_XHFC)
		hc->hw.r_cirm = V_SRES | V_HFCRES | V_PCMRES | V_STRES;
	अन्यथा
		hc->hw.r_cirm = V_SRES | V_HFCRES | V_PCMRES | V_STRES
			| V_RLD_EPR;
	HFC_outb(hc, R_CIRM, hc->hw.r_cirm);
	udelay(100);
	hc->hw.r_cirm = 0;
	HFC_outb(hc, R_CIRM, hc->hw.r_cirm);
	udelay(100);
	अगर (hc->ctype != HFC_TYPE_XHFC)
		HFC_outb(hc, R_RAM_SZ, hc->hw.r_ram_sz);

	/* Speech Design PLX bridge pcm and sync mode */
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
		spin_lock_irqsave(&plx_lock, plx_flags);
		plx_acc_32 = hc->plx_membase + PLX_GPIOC;
		pv = पढ़ोl(plx_acc_32);
		/* Connect PCM */
		अगर (hc->hw.r_pcm_md0 & V_PCM_MD) अणु
			pv |= PLX_MASTER_EN | PLX_SLAVE_EN_N;
			pv |= PLX_SYNC_O_EN;
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: master: PLX_GPIO=%x\n",
				       __func__, pv);
		पूर्ण अन्यथा अणु
			pv &= ~(PLX_MASTER_EN | PLX_SLAVE_EN_N);
			pv &= ~PLX_SYNC_O_EN;
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: slave: PLX_GPIO=%x\n",
				       __func__, pv);
		पूर्ण
		ग_लिखोl(pv, plx_acc_32);
		spin_unlock_irqrestore(&plx_lock, plx_flags);
	पूर्ण

	/* PCM setup */
	HFC_outb(hc, R_PCM_MD0, hc->hw.r_pcm_md0 | 0x90);
	अगर (hc->slots == 32)
		HFC_outb(hc, R_PCM_MD1, 0x00);
	अगर (hc->slots == 64)
		HFC_outb(hc, R_PCM_MD1, 0x10);
	अगर (hc->slots == 128)
		HFC_outb(hc, R_PCM_MD1, 0x20);
	HFC_outb(hc, R_PCM_MD0, hc->hw.r_pcm_md0 | 0xa0);
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip))
		HFC_outb(hc, R_PCM_MD2, V_SYNC_SRC); /* sync via SYNC_I / O */
	अन्यथा अगर (test_bit(HFC_CHIP_EMBSD, &hc->chip))
		HFC_outb(hc, R_PCM_MD2, 0x10); /* V_C2O_EN */
	अन्यथा
		HFC_outb(hc, R_PCM_MD2, 0x00); /* sync from पूर्णांकerface */
	HFC_outb(hc, R_PCM_MD0, hc->hw.r_pcm_md0 | 0x00);
	क्रम (i = 0; i < 256; i++) अणु
		HFC_outb_nodebug(hc, R_SLOT, i);
		HFC_outb_nodebug(hc, A_SL_CFG, 0);
		अगर (hc->ctype != HFC_TYPE_XHFC)
			HFC_outb_nodebug(hc, A_CONF, 0);
		hc->slot_owner[i] = -1;
	पूर्ण

	/* set घड़ी speed */
	अगर (test_bit(HFC_CHIP_CLOCK2, &hc->chip)) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: setting double clock\n", __func__);
		HFC_outb(hc, R_BRG_PCM_CFG, V_PCM_CLK);
	पूर्ण

	अगर (test_bit(HFC_CHIP_EMBSD, &hc->chip))
		HFC_outb(hc, 0x02 /* R_CLK_CFG */, 0x40 /* V_CLKO_OFF */);

	/* B410P GPIO */
	अगर (test_bit(HFC_CHIP_B410P, &hc->chip)) अणु
		prपूर्णांकk(KERN_NOTICE "Setting GPIOs\n");
		HFC_outb(hc, R_GPIO_SEL, 0x30);
		HFC_outb(hc, R_GPIO_EN1, 0x3);
		udelay(1000);
		prपूर्णांकk(KERN_NOTICE "calling vpm_init\n");
		vpm_init(hc);
	पूर्ण

	/* check अगर R_F0_CNT counts (8 kHz frame count) */
	val = HFC_inb(hc, R_F0_CNTL);
	val += HFC_inb(hc, R_F0_CNTH) << 8;
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG
		       "HFC_multi F0_CNT %ld after reset\n", val);
	spin_unlock_irqrestore(&hc->lock, flags);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout((HZ / 100) ? : 1); /* Timeout minimum 10ms */
	spin_lock_irqsave(&hc->lock, flags);
	val2 = HFC_inb(hc, R_F0_CNTL);
	val2 += HFC_inb(hc, R_F0_CNTH) << 8;
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG
		       "HFC_multi F0_CNT %ld after 10 ms (1st try)\n",
		       val2);
	अगर (val2 >= val + 8) अणु /* 1 ms */
		/* it counts, so we keep the pcm mode */
		अगर (test_bit(HFC_CHIP_PCM_MASTER, &hc->chip))
			prपूर्णांकk(KERN_INFO "controller is PCM bus MASTER\n");
		अन्यथा
			अगर (test_bit(HFC_CHIP_PCM_SLAVE, &hc->chip))
				prपूर्णांकk(KERN_INFO "controller is PCM bus SLAVE\n");
			अन्यथा अणु
				test_and_set_bit(HFC_CHIP_PCM_SLAVE, &hc->chip);
				prपूर्णांकk(KERN_INFO "controller is PCM bus SLAVE "
				       "(auto detected)\n");
			पूर्ण
	पूर्ण अन्यथा अणु
		/* करोes not count */
		अगर (test_bit(HFC_CHIP_PCM_MASTER, &hc->chip)) अणु
		controller_fail:
			prपूर्णांकk(KERN_ERR "HFC_multi ERROR, getting no 125us "
			       "pulse. Seems that controller fails.\n");
			err = -EIO;
			जाओ out;
		पूर्ण
		अगर (test_bit(HFC_CHIP_PCM_SLAVE, &hc->chip)) अणु
			prपूर्णांकk(KERN_INFO "controller is PCM bus SLAVE "
			       "(ignoring missing PCM clock)\n");
		पूर्ण अन्यथा अणु
			/* only one pcm master */
			अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)
			    && plxsd_master) अणु
				prपूर्णांकk(KERN_ERR "HFC_multi ERROR, no clock "
				       "on another Speech Design card found. "
				       "Please be sure to connect PCM cable.\n");
				err = -EIO;
				जाओ out;
			पूर्ण
			/* retry with master घड़ी */
			अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
				spin_lock_irqsave(&plx_lock, plx_flags);
				plx_acc_32 = hc->plx_membase + PLX_GPIOC;
				pv = पढ़ोl(plx_acc_32);
				pv |= PLX_MASTER_EN | PLX_SLAVE_EN_N;
				pv |= PLX_SYNC_O_EN;
				ग_लिखोl(pv, plx_acc_32);
				spin_unlock_irqrestore(&plx_lock, plx_flags);
				अगर (debug & DEBUG_HFCMULTI_INIT)
					prपूर्णांकk(KERN_DEBUG "%s: master: "
					       "PLX_GPIO=%x\n", __func__, pv);
			पूर्ण
			hc->hw.r_pcm_md0 |= V_PCM_MD;
			HFC_outb(hc, R_PCM_MD0, hc->hw.r_pcm_md0 | 0x00);
			spin_unlock_irqrestore(&hc->lock, flags);
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout((HZ / 100) ?: 1); /* Timeout min. 10ms */
			spin_lock_irqsave(&hc->lock, flags);
			val2 = HFC_inb(hc, R_F0_CNTL);
			val2 += HFC_inb(hc, R_F0_CNTH) << 8;
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "HFC_multi F0_CNT %ld after "
				       "10 ms (2nd try)\n", val2);
			अगर (val2 >= val + 8) अणु /* 1 ms */
				test_and_set_bit(HFC_CHIP_PCM_MASTER,
						 &hc->chip);
				prपूर्णांकk(KERN_INFO "controller is PCM bus MASTER "
				       "(auto detected)\n");
			पूर्ण अन्यथा
				जाओ controller_fail;
		पूर्ण
	पूर्ण

	/* Release the DSP Reset */
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
		अगर (test_bit(HFC_CHIP_PCM_MASTER, &hc->chip))
			plxsd_master = 1;
		spin_lock_irqsave(&plx_lock, plx_flags);
		plx_acc_32 = hc->plx_membase + PLX_GPIOC;
		pv = पढ़ोl(plx_acc_32);
		pv |=  PLX_DSP_RES_N;
		ग_लिखोl(pv, plx_acc_32);
		spin_unlock_irqrestore(&plx_lock, plx_flags);
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: reset off: PLX_GPIO=%x\n",
			       __func__, pv);
	पूर्ण

	/* pcm id */
	अगर (hc->pcm)
		prपूर्णांकk(KERN_INFO "controller has given PCM BUS ID %d\n",
		       hc->pcm);
	अन्यथा अणु
		अगर (test_bit(HFC_CHIP_PCM_MASTER, &hc->chip)
		    || test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			PCM_cnt++; /* SD has proprietary bridging */
		पूर्ण
		hc->pcm = PCM_cnt;
		prपूर्णांकk(KERN_INFO "controller has PCM BUS ID %d "
		       "(auto selected)\n", hc->pcm);
	पूर्ण

	/* set up समयr */
	HFC_outb(hc, R_TI_WD, poll_समयr);
	hc->hw.r_irqmsk_misc |= V_TI_IRQMSK;

	/* set E1 state machine IRQ */
	अगर (hc->ctype == HFC_TYPE_E1)
		hc->hw.r_irqmsk_misc |= V_STA_IRQMSK;

	/* set DTMF detection */
	अगर (test_bit(HFC_CHIP_DTMF, &hc->chip)) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: enabling DTMF detection "
			       "for all B-channel\n", __func__);
		hc->hw.r_dपंचांगf = V_DTMF_EN | V_DTMF_STOP;
		अगर (test_bit(HFC_CHIP_ULAW, &hc->chip))
			hc->hw.r_dपंचांगf |= V_ULAW_SEL;
		HFC_outb(hc, R_DTMF_N, 102 - 1);
		hc->hw.r_irqmsk_misc |= V_DTMF_IRQMSK;
	पूर्ण

	/* conference engine */
	अगर (test_bit(HFC_CHIP_ULAW, &hc->chip))
		r_conf_en = V_CONF_EN | V_ULAW;
	अन्यथा
		r_conf_en = V_CONF_EN;
	अगर (hc->ctype != HFC_TYPE_XHFC)
		HFC_outb(hc, R_CONF_EN, r_conf_en);

	/* setting leds */
	चयन (hc->leds) अणु
	हाल 1: /* HFC-E1 OEM */
		अगर (test_bit(HFC_CHIP_WATCHDOG, &hc->chip))
			HFC_outb(hc, R_GPIO_SEL, 0x32);
		अन्यथा
			HFC_outb(hc, R_GPIO_SEL, 0x30);

		HFC_outb(hc, R_GPIO_EN1, 0x0f);
		HFC_outb(hc, R_GPIO_OUT1, 0x00);

		HFC_outb(hc, R_GPIO_EN0, V_GPIO_EN2 | V_GPIO_EN3);
		अवरोध;

	हाल 2: /* HFC-4S OEM */
	हाल 3:
		HFC_outb(hc, R_GPIO_SEL, 0xf0);
		HFC_outb(hc, R_GPIO_EN1, 0xff);
		HFC_outb(hc, R_GPIO_OUT1, 0x00);
		अवरोध;
	पूर्ण

	अगर (test_bit(HFC_CHIP_EMBSD, &hc->chip)) अणु
		hc->hw.r_st_sync = 0x10; /* V_AUTO_SYNCI */
		HFC_outb(hc, R_ST_SYNC, hc->hw.r_st_sync);
	पूर्ण

	/* set master घड़ी */
	अगर (hc->masterclk >= 0) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: setting ST master clock "
			       "to port %d (0..%d)\n",
			       __func__, hc->masterclk, hc->ports - 1);
		hc->hw.r_st_sync |= (hc->masterclk | V_AUTO_SYNC);
		HFC_outb(hc, R_ST_SYNC, hc->hw.r_st_sync);
	पूर्ण



	/* setting misc irq */
	HFC_outb(hc, R_IRQMSK_MISC, hc->hw.r_irqmsk_misc);
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "r_irqmsk_misc.2: 0x%x\n",
		       hc->hw.r_irqmsk_misc);

	/* RAM access test */
	HFC_outb(hc, R_RAM_ADDR0, 0);
	HFC_outb(hc, R_RAM_ADDR1, 0);
	HFC_outb(hc, R_RAM_ADDR2, 0);
	क्रम (i = 0; i < 256; i++) अणु
		HFC_outb_nodebug(hc, R_RAM_ADDR0, i);
		HFC_outb_nodebug(hc, R_RAM_DATA, ((i * 3) & 0xff));
	पूर्ण
	क्रम (i = 0; i < 256; i++) अणु
		HFC_outb_nodebug(hc, R_RAM_ADDR0, i);
		HFC_inb_nodebug(hc, R_RAM_DATA);
		rval = HFC_inb_nodebug(hc, R_INT_DATA);
		अगर (rval != ((i * 3) & 0xff)) अणु
			prपूर्णांकk(KERN_DEBUG
			       "addr:%x val:%x should:%x\n", i, rval,
			       (i * 3) & 0xff);
			err++;
		पूर्ण
	पूर्ण
	अगर (err) अणु
		prपूर्णांकk(KERN_DEBUG "aborting - %d RAM access errors\n", err);
		err = -EIO;
		जाओ out;
	पूर्ण

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: done\n", __func__);
out:
	spin_unlock_irqrestore(&hc->lock, flags);
	वापस err;
पूर्ण


/*
 * control the watchकरोg
 */
अटल व्योम
hfcmulti_watchकरोg(काष्ठा hfc_multi *hc)
अणु
	hc->wdcount++;

	अगर (hc->wdcount > 10) अणु
		hc->wdcount = 0;
		hc->wdbyte = hc->wdbyte == V_GPIO_OUT2 ?
			V_GPIO_OUT3 : V_GPIO_OUT2;

		/* prपूर्णांकk("Sending Watchdog Kill %x\n",hc->wdbyte); */
		HFC_outb(hc, R_GPIO_EN0, V_GPIO_EN2 | V_GPIO_EN3);
		HFC_outb(hc, R_GPIO_OUT0, hc->wdbyte);
	पूर्ण
पूर्ण



/*
 * output leds
 */
अटल व्योम
hfcmulti_leds(काष्ठा hfc_multi *hc)
अणु
	अचिन्हित दीर्घ lled;
	अचिन्हित दीर्घ leddw;
	पूर्णांक i, state, active, leds;
	काष्ठा dchannel *dch;
	पूर्णांक led[4];

	चयन (hc->leds) अणु
	हाल 1: /* HFC-E1 OEM */
		/* 2 red steady:       LOS
		 * 1 red steady:       L1 not active
		 * 2 green steady:     L1 active
		 * 1st green flashing: activity on TX
		 * 2nd green flashing: activity on RX
		 */
		led[0] = 0;
		led[1] = 0;
		led[2] = 0;
		led[3] = 0;
		dch = hc->chan[hc->dnum[0]].dch;
		अगर (dch) अणु
			अगर (hc->chan[hc->dnum[0]].los)
				led[1] = 1;
			अगर (hc->e1_state != 1) अणु
				led[0] = 1;
				hc->flash[2] = 0;
				hc->flash[3] = 0;
			पूर्ण अन्यथा अणु
				led[2] = 1;
				led[3] = 1;
				अगर (!hc->flash[2] && hc->activity_tx)
					hc->flash[2] = poll;
				अगर (!hc->flash[3] && hc->activity_rx)
					hc->flash[3] = poll;
				अगर (hc->flash[2] && hc->flash[2] < 1024)
					led[2] = 0;
				अगर (hc->flash[3] && hc->flash[3] < 1024)
					led[3] = 0;
				अगर (hc->flash[2] >= 2048)
					hc->flash[2] = 0;
				अगर (hc->flash[3] >= 2048)
					hc->flash[3] = 0;
				अगर (hc->flash[2])
					hc->flash[2] += poll;
				अगर (hc->flash[3])
					hc->flash[3] += poll;
			पूर्ण
		पूर्ण
		leds = (led[0] | (led[1]<<2) | (led[2]<<1) | (led[3]<<3))^0xF;
		/* leds are inverted */
		अगर (leds != (पूर्णांक)hc->ledstate) अणु
			HFC_outb_nodebug(hc, R_GPIO_OUT1, leds);
			hc->ledstate = leds;
		पूर्ण
		अवरोध;

	हाल 2: /* HFC-4S OEM */
		/* red steady:     PH_DEACTIVATE
		 * green steady:   PH_ACTIVATE
		 * green flashing: activity on TX
		 */
		क्रम (i = 0; i < 4; i++) अणु
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			अगर (dch) अणु
				state = dch->state;
				अगर (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				अन्यथा
					active = 7;
			पूर्ण
			अगर (state) अणु
				अगर (state == active) अणु
					led[i] = 1; /* led green */
					hc->activity_tx |= hc->activity_rx;
					अगर (!hc->flash[i] &&
						(hc->activity_tx & (1 << i)))
							hc->flash[i] = poll;
					अगर (hc->flash[i] && hc->flash[i] < 1024)
						led[i] = 0; /* led off */
					अगर (hc->flash[i] >= 2048)
						hc->flash[i] = 0;
					अगर (hc->flash[i])
						hc->flash[i] += poll;
				पूर्ण अन्यथा अणु
					led[i] = 2; /* led red */
					hc->flash[i] = 0;
				पूर्ण
			पूर्ण अन्यथा
				led[i] = 0; /* led off */
		पूर्ण
		अगर (test_bit(HFC_CHIP_B410P, &hc->chip)) अणु
			leds = 0;
			क्रम (i = 0; i < 4; i++) अणु
				अगर (led[i] == 1) अणु
					/*green*/
					leds |= (0x2 << (i * 2));
				पूर्ण अन्यथा अगर (led[i] == 2) अणु
					/*red*/
					leds |= (0x1 << (i * 2));
				पूर्ण
			पूर्ण
			अगर (leds != (पूर्णांक)hc->ledstate) अणु
				vpm_out(hc, 0, 0x1a8 + 3, leds);
				hc->ledstate = leds;
			पूर्ण
		पूर्ण अन्यथा अणु
			leds = ((led[3] > 0) << 0) | ((led[1] > 0) << 1) |
				((led[0] > 0) << 2) | ((led[2] > 0) << 3) |
				((led[3] & 1) << 4) | ((led[1] & 1) << 5) |
				((led[0] & 1) << 6) | ((led[2] & 1) << 7);
			अगर (leds != (पूर्णांक)hc->ledstate) अणु
				HFC_outb_nodebug(hc, R_GPIO_EN1, leds & 0x0F);
				HFC_outb_nodebug(hc, R_GPIO_OUT1, leds >> 4);
				hc->ledstate = leds;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 3: /* HFC 1S/2S Beronet */
		/* red steady:     PH_DEACTIVATE
		 * green steady:   PH_ACTIVATE
		 * green flashing: activity on TX
		 */
		क्रम (i = 0; i < 2; i++) अणु
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			अगर (dch) अणु
				state = dch->state;
				अगर (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				अन्यथा
					active = 7;
			पूर्ण
			अगर (state) अणु
				अगर (state == active) अणु
					led[i] = 1; /* led green */
					hc->activity_tx |= hc->activity_rx;
					अगर (!hc->flash[i] &&
						(hc->activity_tx & (1 << i)))
							hc->flash[i] = poll;
					अगर (hc->flash[i] < 1024)
						led[i] = 0; /* led off */
					अगर (hc->flash[i] >= 2048)
						hc->flash[i] = 0;
					अगर (hc->flash[i])
						hc->flash[i] += poll;
				पूर्ण अन्यथा अणु
					led[i] = 2; /* led red */
					hc->flash[i] = 0;
				पूर्ण
			पूर्ण अन्यथा
				led[i] = 0; /* led off */
		पूर्ण
		leds = (led[0] > 0) | ((led[1] > 0) << 1) | ((led[0]&1) << 2)
			| ((led[1]&1) << 3);
		अगर (leds != (पूर्णांक)hc->ledstate) अणु
			HFC_outb_nodebug(hc, R_GPIO_EN1,
					 ((led[0] > 0) << 2) | ((led[1] > 0) << 3));
			HFC_outb_nodebug(hc, R_GPIO_OUT1,
					 ((led[0] & 1) << 2) | ((led[1] & 1) << 3));
			hc->ledstate = leds;
		पूर्ण
		अवरोध;
	हाल 8: /* HFC 8S+ Beronet */
		/* off:      PH_DEACTIVATE
		 * steady:   PH_ACTIVATE
		 * flashing: activity on TX
		 */
		lled = 0xff; /* leds off */
		क्रम (i = 0; i < 8; i++) अणु
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			अगर (dch) अणु
				state = dch->state;
				अगर (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				अन्यथा
					active = 7;
			पूर्ण
			अगर (state) अणु
				अगर (state == active) अणु
					lled &= ~(1 << i); /* led on */
					hc->activity_tx |= hc->activity_rx;
					अगर (!hc->flash[i] &&
						(hc->activity_tx & (1 << i)))
							hc->flash[i] = poll;
					अगर (hc->flash[i] < 1024)
						lled |= 1 << i; /* led off */
					अगर (hc->flash[i] >= 2048)
						hc->flash[i] = 0;
					अगर (hc->flash[i])
						hc->flash[i] += poll;
				पूर्ण अन्यथा
					hc->flash[i] = 0;
			पूर्ण
		पूर्ण
		leddw = lled << 24 | lled << 16 | lled << 8 | lled;
		अगर (leddw != hc->ledstate) अणु
			/* HFC_outb(hc, R_BRG_PCM_CFG, 1);
			   HFC_outb(c, R_BRG_PCM_CFG, (0x0 << 6) | 0x3); */
			/* was _io beक्रमe */
			HFC_outb_nodebug(hc, R_BRG_PCM_CFG, 1 | V_PCM_CLK);
			outw(0x4000, hc->pci_iobase + 4);
			outl(leddw, hc->pci_iobase);
			HFC_outb_nodebug(hc, R_BRG_PCM_CFG, V_PCM_CLK);
			hc->ledstate = leddw;
		पूर्ण
		अवरोध;
	पूर्ण
	hc->activity_tx = 0;
	hc->activity_rx = 0;
पूर्ण
/*
 * पढ़ो dपंचांगf coefficients
 */

अटल व्योम
hfcmulti_dपंचांगf(काष्ठा hfc_multi *hc)
अणु
	s32		*coeff;
	u_पूर्णांक		mantissa;
	पूर्णांक		co, ch;
	काष्ठा bchannel	*bch = शून्य;
	u8		exponent;
	पूर्णांक		dपंचांगf = 0;
	पूर्णांक		addr;
	u16		w_भग्न;
	काष्ठा sk_buff	*skb;
	काष्ठा mISDNhead *hh;

	अगर (debug & DEBUG_HFCMULTI_DTMF)
		prपूर्णांकk(KERN_DEBUG "%s: dtmf detection irq\n", __func__);
	क्रम (ch = 0; ch <= 31; ch++) अणु
		/* only process enabled B-channels */
		bch = hc->chan[ch].bch;
		अगर (!bch)
			जारी;
		अगर (!hc->created[hc->chan[ch].port])
			जारी;
		अगर (!test_bit(FLG_TRANSPARENT, &bch->Flags))
			जारी;
		अगर (debug & DEBUG_HFCMULTI_DTMF)
			prपूर्णांकk(KERN_DEBUG "%s: dtmf channel %d:",
			       __func__, ch);
		coeff = &(hc->chan[ch].coeff[hc->chan[ch].coeff_count * 16]);
		dपंचांगf = 1;
		क्रम (co = 0; co < 8; co++) अणु
			/* पढ़ो W(n-1) coefficient */
			addr = hc->DTMFbase + ((co << 7) | (ch << 2));
			HFC_outb_nodebug(hc, R_RAM_ADDR0, addr);
			HFC_outb_nodebug(hc, R_RAM_ADDR1, addr >> 8);
			HFC_outb_nodebug(hc, R_RAM_ADDR2, (addr >> 16)
					 | V_ADDR_INC);
			w_भग्न = HFC_inb_nodebug(hc, R_RAM_DATA);
			w_भग्न |= (HFC_inb_nodebug(hc, R_RAM_DATA) << 8);
			अगर (debug & DEBUG_HFCMULTI_DTMF)
				prपूर्णांकk(" %04x", w_भग्न);

			/* decode भग्न (see chip करोc) */
			mantissa = w_भग्न & 0x0fff;
			अगर (w_भग्न & 0x8000)
				mantissa |= 0xfffff000;
			exponent = (w_भग्न >> 12) & 0x7;
			अगर (exponent) अणु
				mantissa ^= 0x1000;
				mantissa <<= (exponent - 1);
			पूर्ण

			/* store coefficient */
			coeff[co << 1] = mantissa;

			/* पढ़ो W(n) coefficient */
			w_भग्न = HFC_inb_nodebug(hc, R_RAM_DATA);
			w_भग्न |= (HFC_inb_nodebug(hc, R_RAM_DATA) << 8);
			अगर (debug & DEBUG_HFCMULTI_DTMF)
				prपूर्णांकk(" %04x", w_भग्न);

			/* decode भग्न (see chip करोc) */
			mantissa = w_भग्न & 0x0fff;
			अगर (w_भग्न & 0x8000)
				mantissa |= 0xfffff000;
			exponent = (w_भग्न >> 12) & 0x7;
			अगर (exponent) अणु
				mantissa ^= 0x1000;
				mantissa <<= (exponent - 1);
			पूर्ण

			/* store coefficient */
			coeff[(co << 1) | 1] = mantissa;
		पूर्ण
		अगर (debug & DEBUG_HFCMULTI_DTMF)
			prपूर्णांकk(" DTMF ready %08x %08x %08x %08x "
			       "%08x %08x %08x %08x\n",
			       coeff[0], coeff[1], coeff[2], coeff[3],
			       coeff[4], coeff[5], coeff[6], coeff[7]);
		hc->chan[ch].coeff_count++;
		अगर (hc->chan[ch].coeff_count == 8) अणु
			hc->chan[ch].coeff_count = 0;
			skb = mI_alloc_skb(512, GFP_ATOMIC);
			अगर (!skb) अणु
				prपूर्णांकk(KERN_DEBUG "%s: No memory for skb\n",
				       __func__);
				जारी;
			पूर्ण
			hh = mISDN_HEAD_P(skb);
			hh->prim = PH_CONTROL_IND;
			hh->id = DTMF_HFC_COEF;
			skb_put_data(skb, hc->chan[ch].coeff, 512);
			recv_Bchannel_skb(bch, skb);
		पूर्ण
	पूर्ण

	/* restart DTMF processing */
	hc->dपंचांगf = dपंचांगf;
	अगर (dपंचांगf)
		HFC_outb_nodebug(hc, R_DTMF, hc->hw.r_dपंचांगf | V_RST_DTMF);
पूर्ण


/*
 * fill fअगरo as much as possible
 */

अटल व्योम
hfcmulti_tx(काष्ठा hfc_multi *hc, पूर्णांक ch)
अणु
	पूर्णांक i, ii, temp, len = 0;
	पूर्णांक Zspace, z1, z2; /* must be पूर्णांक क्रम calculation */
	पूर्णांक Fspace, f1, f2;
	u_अक्षर *d;
	पूर्णांक *txpending, slot_tx;
	काष्ठा	bchannel *bch;
	काष्ठा  dchannel *dch;
	काष्ठा  sk_buff **sp = शून्य;
	पूर्णांक *idxp;

	bch = hc->chan[ch].bch;
	dch = hc->chan[ch].dch;
	अगर ((!dch) && (!bch))
		वापस;

	txpending = &hc->chan[ch].txpending;
	slot_tx = hc->chan[ch].slot_tx;
	अगर (dch) अणु
		अगर (!test_bit(FLG_ACTIVE, &dch->Flags))
			वापस;
		sp = &dch->tx_skb;
		idxp = &dch->tx_idx;
	पूर्ण अन्यथा अणु
		अगर (!test_bit(FLG_ACTIVE, &bch->Flags))
			वापस;
		sp = &bch->tx_skb;
		idxp = &bch->tx_idx;
	पूर्ण
	अगर (*sp)
		len = (*sp)->len;

	अगर ((!len) && *txpending != 1)
		वापस; /* no data */

	अगर (test_bit(HFC_CHIP_B410P, &hc->chip) &&
	    (hc->chan[ch].protocol == ISDN_P_B_RAW) &&
	    (hc->chan[ch].slot_rx < 0) &&
	    (hc->chan[ch].slot_tx < 0))
		HFC_outb_nodebug(hc, R_FIFO, 0x20 | (ch << 1));
	अन्यथा
		HFC_outb_nodebug(hc, R_FIFO, ch << 1);
	HFC_रुको_nodebug(hc);

	अगर (*txpending == 2) अणु
		/* reset fअगरo */
		HFC_outb_nodebug(hc, R_INC_RES_FIFO, V_RES_F);
		HFC_रुको_nodebug(hc);
		HFC_outb(hc, A_SUBCH_CFG, 0);
		*txpending = 1;
	पूर्ण
next_frame:
	अगर (dch || test_bit(FLG_HDLC, &bch->Flags)) अणु
		f1 = HFC_inb_nodebug(hc, A_F1);
		f2 = HFC_inb_nodebug(hc, A_F2);
		जबतक (f2 != (temp = HFC_inb_nodebug(hc, A_F2))) अणु
			अगर (debug & DEBUG_HFCMULTI_FIFO)
				prपूर्णांकk(KERN_DEBUG
				       "%s(card %d): reread f2 because %d!=%d\n",
				       __func__, hc->id + 1, temp, f2);
			f2 = temp; /* repeat until F2 is equal */
		पूर्ण
		Fspace = f2 - f1 - 1;
		अगर (Fspace < 0)
			Fspace += hc->Flen;
		/*
		 * Old FIFO handling करोesn't give us the current Z2 पढ़ो
		 * poपूर्णांकer, so we cannot send the next frame beक्रमe the fअगरo
		 * is empty. It makes no dअगरference except क्रम a slightly
		 * lower perक्रमmance.
		 */
		अगर (test_bit(HFC_CHIP_REVISION0, &hc->chip)) अणु
			अगर (f1 != f2)
				Fspace = 0;
			अन्यथा
				Fspace = 1;
		पूर्ण
		/* one frame only क्रम ST D-channels, to allow resending */
		अगर (hc->ctype != HFC_TYPE_E1 && dch) अणु
			अगर (f1 != f2)
				Fspace = 0;
		पूर्ण
		/* F-counter full condition */
		अगर (Fspace == 0)
			वापस;
	पूर्ण
	z1 = HFC_inw_nodebug(hc, A_Z1) - hc->Zmin;
	z2 = HFC_inw_nodebug(hc, A_Z2) - hc->Zmin;
	जबतक (z2 != (temp = (HFC_inw_nodebug(hc, A_Z2) - hc->Zmin))) अणु
		अगर (debug & DEBUG_HFCMULTI_FIFO)
			prपूर्णांकk(KERN_DEBUG "%s(card %d): reread z2 because "
			       "%d!=%d\n", __func__, hc->id + 1, temp, z2);
		z2 = temp; /* repeat unti Z2 is equal */
	पूर्ण
	hc->chan[ch].Zfill = z1 - z2;
	अगर (hc->chan[ch].Zfill < 0)
		hc->chan[ch].Zfill += hc->Zlen;
	Zspace = z2 - z1;
	अगर (Zspace <= 0)
		Zspace += hc->Zlen;
	Zspace -= 4; /* keep not too full, so poपूर्णांकers will not overrun */
	/* fill transparent data only to maxinum transparent load (minus 4) */
	अगर (bch && test_bit(FLG_TRANSPARENT, &bch->Flags))
		Zspace = Zspace - hc->Zlen + hc->max_trans;
	अगर (Zspace <= 0) /* no space of 4 bytes */
		वापस;

	/* अगर no data */
	अगर (!len) अणु
		अगर (z1 == z2) अणु /* empty */
			/* अगर करोne with FIFO audio data during PCM connection */
			अगर (bch && (!test_bit(FLG_HDLC, &bch->Flags)) &&
			    *txpending && slot_tx >= 0) अणु
				अगर (debug & DEBUG_HFCMULTI_MODE)
					prपूर्णांकk(KERN_DEBUG
					       "%s: reconnecting PCM due to no "
					       "more FIFO data: channel %d "
					       "slot_tx %d\n",
					       __func__, ch, slot_tx);
				/* connect slot */
				अगर (hc->ctype == HFC_TYPE_XHFC)
					HFC_outb(hc, A_CON_HDLC, 0xc0
						 | 0x07 << 2 | V_HDLC_TRP | V_IFF);
				/* Enable FIFO, no पूर्णांकerrupt */
				अन्यथा
					HFC_outb(hc, A_CON_HDLC, 0xc0 | 0x00 |
						 V_HDLC_TRP | V_IFF);
				HFC_outb_nodebug(hc, R_FIFO, ch << 1 | 1);
				HFC_रुको_nodebug(hc);
				अगर (hc->ctype == HFC_TYPE_XHFC)
					HFC_outb(hc, A_CON_HDLC, 0xc0
						 | 0x07 << 2 | V_HDLC_TRP | V_IFF);
				/* Enable FIFO, no पूर्णांकerrupt */
				अन्यथा
					HFC_outb(hc, A_CON_HDLC, 0xc0 | 0x00 |
						 V_HDLC_TRP | V_IFF);
				HFC_outb_nodebug(hc, R_FIFO, ch << 1);
				HFC_रुको_nodebug(hc);
			पूर्ण
			*txpending = 0;
		पूर्ण
		वापस; /* no data */
	पूर्ण

	/* "fill fifo if empty" feature */
	अगर (bch && test_bit(FLG_FILLEMPTY, &bch->Flags)
	    && !test_bit(FLG_HDLC, &bch->Flags) && z2 == z1) अणु
		अगर (debug & DEBUG_HFCMULTI_FILL)
			prपूर्णांकk(KERN_DEBUG "%s: buffer empty, so we have "
			       "underrun\n", __func__);
		/* fill buffer, to prevent future underrun */
		hc->ग_लिखो_fअगरo(hc, hc->silence_data, poll >> 1);
		Zspace -= (poll >> 1);
	पूर्ण

	/* अगर audio data and connected slot */
	अगर (bch && (!test_bit(FLG_HDLC, &bch->Flags)) && (!*txpending)
	    && slot_tx >= 0) अणु
		अगर (debug & DEBUG_HFCMULTI_MODE)
			prपूर्णांकk(KERN_DEBUG "%s: disconnecting PCM due to "
			       "FIFO data: channel %d slot_tx %d\n",
			       __func__, ch, slot_tx);
		/* disconnect slot */
		अगर (hc->ctype == HFC_TYPE_XHFC)
			HFC_outb(hc, A_CON_HDLC, 0x80
				 | 0x07 << 2 | V_HDLC_TRP | V_IFF);
		/* Enable FIFO, no पूर्णांकerrupt */
		अन्यथा
			HFC_outb(hc, A_CON_HDLC, 0x80 | 0x00 |
				 V_HDLC_TRP | V_IFF);
		HFC_outb_nodebug(hc, R_FIFO, ch << 1 | 1);
		HFC_रुको_nodebug(hc);
		अगर (hc->ctype == HFC_TYPE_XHFC)
			HFC_outb(hc, A_CON_HDLC, 0x80
				 | 0x07 << 2 | V_HDLC_TRP | V_IFF);
		/* Enable FIFO, no पूर्णांकerrupt */
		अन्यथा
			HFC_outb(hc, A_CON_HDLC, 0x80 | 0x00 |
				 V_HDLC_TRP | V_IFF);
		HFC_outb_nodebug(hc, R_FIFO, ch << 1);
		HFC_रुको_nodebug(hc);
	पूर्ण
	*txpending = 1;

	/* show activity */
	अगर (dch)
		hc->activity_tx |= 1 << hc->chan[ch].port;

	/* fill fअगरo to what we have left */
	ii = len;
	अगर (dch || test_bit(FLG_HDLC, &bch->Flags))
		temp = 1;
	अन्यथा
		temp = 0;
	i = *idxp;
	d = (*sp)->data + i;
	अगर (ii - i > Zspace)
		ii = Zspace + i;
	अगर (debug & DEBUG_HFCMULTI_FIFO)
		prपूर्णांकk(KERN_DEBUG "%s(card %d): fifo(%d) has %d bytes space "
		       "left (z1=%04x, z2=%04x) sending %d of %d bytes %s\n",
		       __func__, hc->id + 1, ch, Zspace, z1, z2, ii-i, len-i,
		       temp ? "HDLC" : "TRANS");

	/* Have to prep the audio data */
	hc->ग_लिखो_fअगरo(hc, d, ii - i);
	hc->chan[ch].Zfill += ii - i;
	*idxp = ii;

	/* अगर not all data has been written */
	अगर (ii != len) अणु
		/* NOTE: fअगरo is started by the calling function */
		वापस;
	पूर्ण

	/* अगर all data has been written, terminate frame */
	अगर (dch || test_bit(FLG_HDLC, &bch->Flags)) अणु
		/* increment f-counter */
		HFC_outb_nodebug(hc, R_INC_RES_FIFO, V_INC_F);
		HFC_रुको_nodebug(hc);
	पूर्ण

	dev_kमुक्त_skb(*sp);
	/* check क्रम next frame */
	अगर (bch && get_next_bframe(bch)) अणु
		len = (*sp)->len;
		जाओ next_frame;
	पूर्ण
	अगर (dch && get_next_dframe(dch)) अणु
		len = (*sp)->len;
		जाओ next_frame;
	पूर्ण

	/*
	 * now we have no more data, so in हाल of transparent,
	 * we set the last byte in fअगरo to 'silence' in हाल we will get
	 * no more data at all. this prevents sending an undefined value.
	 */
	अगर (bch && test_bit(FLG_TRANSPARENT, &bch->Flags))
		HFC_outb_nodebug(hc, A_FIFO_DATA0_NOINC, hc->silence);
पूर्ण


/* NOTE: only called अगर E1 card is in active state */
अटल व्योम
hfcmulti_rx(काष्ठा hfc_multi *hc, पूर्णांक ch)
अणु
	पूर्णांक temp;
	पूर्णांक Zsize, z1, z2 = 0; /* = 0, to make GCC happy */
	पूर्णांक f1 = 0, f2 = 0; /* = 0, to make GCC happy */
	पूर्णांक again = 0;
	काष्ठा	bchannel *bch;
	काष्ठा  dchannel *dch = शून्य;
	काष्ठा sk_buff	*skb, **sp = शून्य;
	पूर्णांक	maxlen;

	bch = hc->chan[ch].bch;
	अगर (bch) अणु
		अगर (!test_bit(FLG_ACTIVE, &bch->Flags))
			वापस;
	पूर्ण अन्यथा अगर (hc->chan[ch].dch) अणु
		dch = hc->chan[ch].dch;
		अगर (!test_bit(FLG_ACTIVE, &dch->Flags))
			वापस;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
next_frame:
	/* on first AND beक्रमe getting next valid frame, R_FIFO must be written
	   to. */
	अगर (test_bit(HFC_CHIP_B410P, &hc->chip) &&
	    (hc->chan[ch].protocol == ISDN_P_B_RAW) &&
	    (hc->chan[ch].slot_rx < 0) &&
	    (hc->chan[ch].slot_tx < 0))
		HFC_outb_nodebug(hc, R_FIFO, 0x20 | (ch << 1) | 1);
	अन्यथा
		HFC_outb_nodebug(hc, R_FIFO, (ch << 1) | 1);
	HFC_रुको_nodebug(hc);

	/* ignore अगर rx is off BUT change fअगरo (above) to start pending TX */
	अगर (hc->chan[ch].rx_off) अणु
		अगर (bch)
			bch->dropcnt += poll; /* not exact but fair enough */
		वापस;
	पूर्ण

	अगर (dch || test_bit(FLG_HDLC, &bch->Flags)) अणु
		f1 = HFC_inb_nodebug(hc, A_F1);
		जबतक (f1 != (temp = HFC_inb_nodebug(hc, A_F1))) अणु
			अगर (debug & DEBUG_HFCMULTI_FIFO)
				prपूर्णांकk(KERN_DEBUG
				       "%s(card %d): reread f1 because %d!=%d\n",
				       __func__, hc->id + 1, temp, f1);
			f1 = temp; /* repeat until F1 is equal */
		पूर्ण
		f2 = HFC_inb_nodebug(hc, A_F2);
	पूर्ण
	z1 = HFC_inw_nodebug(hc, A_Z1) - hc->Zmin;
	जबतक (z1 != (temp = (HFC_inw_nodebug(hc, A_Z1) - hc->Zmin))) अणु
		अगर (debug & DEBUG_HFCMULTI_FIFO)
			prपूर्णांकk(KERN_DEBUG "%s(card %d): reread z2 because "
			       "%d!=%d\n", __func__, hc->id + 1, temp, z2);
		z1 = temp; /* repeat until Z1 is equal */
	पूर्ण
	z2 = HFC_inw_nodebug(hc, A_Z2) - hc->Zmin;
	Zsize = z1 - z2;
	अगर ((dch || test_bit(FLG_HDLC, &bch->Flags)) && f1 != f2)
		/* complete hdlc frame */
		Zsize++;
	अगर (Zsize < 0)
		Zsize += hc->Zlen;
	/* अगर buffer is empty */
	अगर (Zsize <= 0)
		वापस;

	अगर (bch) अणु
		maxlen = bchannel_get_rxbuf(bch, Zsize);
		अगर (maxlen < 0) अणु
			pr_warn("card%d.B%d: No bufferspace for %d bytes\n",
				hc->id + 1, bch->nr, Zsize);
			वापस;
		पूर्ण
		sp = &bch->rx_skb;
		maxlen = bch->maxlen;
	पूर्ण अन्यथा अणु /* Dchannel */
		sp = &dch->rx_skb;
		maxlen = dch->maxlen + 3;
		अगर (*sp == शून्य) अणु
			*sp = mI_alloc_skb(maxlen, GFP_ATOMIC);
			अगर (*sp == शून्य) अणु
				pr_warn("card%d: No mem for dch rx_skb\n",
					hc->id + 1);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	/* show activity */
	अगर (dch)
		hc->activity_rx |= 1 << hc->chan[ch].port;

	/* empty fअगरo with what we have */
	अगर (dch || test_bit(FLG_HDLC, &bch->Flags)) अणु
		अगर (debug & DEBUG_HFCMULTI_FIFO)
			prपूर्णांकk(KERN_DEBUG "%s(card %d): fifo(%d) reading %d "
			       "bytes (z1=%04x, z2=%04x) HDLC %s (f1=%d, f2=%d) "
			       "got=%d (again %d)\n", __func__, hc->id + 1, ch,
			       Zsize, z1, z2, (f1 == f2) ? "fragment" : "COMPLETE",
			       f1, f2, Zsize + (*sp)->len, again);
		/* HDLC */
		अगर ((Zsize + (*sp)->len) > maxlen) अणु
			अगर (debug & DEBUG_HFCMULTI_FIFO)
				prपूर्णांकk(KERN_DEBUG
				       "%s(card %d): hdlc-frame too large.\n",
				       __func__, hc->id + 1);
			skb_trim(*sp, 0);
			HFC_outb_nodebug(hc, R_INC_RES_FIFO, V_RES_F);
			HFC_रुको_nodebug(hc);
			वापस;
		पूर्ण

		hc->पढ़ो_fअगरo(hc, skb_put(*sp, Zsize), Zsize);

		अगर (f1 != f2) अणु
			/* increment Z2,F2-counter */
			HFC_outb_nodebug(hc, R_INC_RES_FIFO, V_INC_F);
			HFC_रुको_nodebug(hc);
			/* check size */
			अगर ((*sp)->len < 4) अणु
				अगर (debug & DEBUG_HFCMULTI_FIFO)
					prपूर्णांकk(KERN_DEBUG
					       "%s(card %d): Frame below minimum "
					       "size\n", __func__, hc->id + 1);
				skb_trim(*sp, 0);
				जाओ next_frame;
			पूर्ण
			/* there is at least one complete frame, check crc */
			अगर ((*sp)->data[(*sp)->len - 1]) अणु
				अगर (debug & DEBUG_HFCMULTI_CRC)
					prपूर्णांकk(KERN_DEBUG
					       "%s: CRC-error\n", __func__);
				skb_trim(*sp, 0);
				जाओ next_frame;
			पूर्ण
			skb_trim(*sp, (*sp)->len - 3);
			अगर ((*sp)->len < MISDN_COPY_SIZE) अणु
				skb = *sp;
				*sp = mI_alloc_skb(skb->len, GFP_ATOMIC);
				अगर (*sp) अणु
					skb_put_data(*sp, skb->data, skb->len);
					skb_trim(skb, 0);
				पूर्ण अन्यथा अणु
					prपूर्णांकk(KERN_DEBUG "%s: No mem\n",
					       __func__);
					*sp = skb;
					skb = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				skb = शून्य;
			पूर्ण
			अगर (debug & DEBUG_HFCMULTI_FIFO) अणु
				prपूर्णांकk(KERN_DEBUG "%s(card %d):",
				       __func__, hc->id + 1);
				temp = 0;
				जबतक (temp < (*sp)->len)
					prपूर्णांकk(" %02x", (*sp)->data[temp++]);
				prपूर्णांकk("\n");
			पूर्ण
			अगर (dch)
				recv_Dchannel(dch);
			अन्यथा
				recv_Bchannel(bch, MISDN_ID_ANY, false);
			*sp = skb;
			again++;
			जाओ next_frame;
		पूर्ण
		/* there is an incomplete frame */
	पूर्ण अन्यथा अणु
		/* transparent */
		hc->पढ़ो_fअगरo(hc, skb_put(*sp, Zsize), Zsize);
		अगर (debug & DEBUG_HFCMULTI_FIFO)
			prपूर्णांकk(KERN_DEBUG
			       "%s(card %d): fifo(%d) reading %d bytes "
			       "(z1=%04x, z2=%04x) TRANS\n",
			       __func__, hc->id + 1, ch, Zsize, z1, z2);
		/* only bch is transparent */
		recv_Bchannel(bch, hc->chan[ch].Zfill, false);
	पूर्ण
पूर्ण


/*
 * Interrupt handler
 */
अटल व्योम
संकेत_state_up(काष्ठा dchannel *dch, पूर्णांक info, अक्षर *msg)
अणु
	काष्ठा sk_buff	*skb;
	पूर्णांक		id, data = info;

	अगर (debug & DEBUG_HFCMULTI_STATE)
		prपूर्णांकk(KERN_DEBUG "%s: %s\n", __func__, msg);

	id = TEI_SAPI | (GROUP_TEI << 8); /* manager address */

	skb = _alloc_mISDN_skb(MPH_INFORMATION_IND, id, माप(data), &data,
			       GFP_ATOMIC);
	अगर (!skb)
		वापस;
	recv_Dchannel_skb(dch, skb);
पूर्ण

अटल अंतरभूत व्योम
handle_समयr_irq(काष्ठा hfc_multi *hc)
अणु
	पूर्णांक		ch, temp;
	काष्ठा dchannel	*dch;
	u_दीर्घ		flags;

	/* process queued resync jobs */
	अगर (hc->e1_resync) अणु
		/* lock, so e1_resync माला_लो not changed */
		spin_lock_irqsave(&HFClock, flags);
		अगर (hc->e1_resync & 1) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG "Enable SYNC_I\n");
			HFC_outb(hc, R_SYNC_CTRL, V_EXT_CLK_SYNC);
			/* disable JATT, अगर RX_SYNC is set */
			अगर (test_bit(HFC_CHIP_RX_SYNC, &hc->chip))
				HFC_outb(hc, R_SYNC_OUT, V_SYNC_E1_RX);
		पूर्ण
		अगर (hc->e1_resync & 2) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG "Enable jatt PLL\n");
			HFC_outb(hc, R_SYNC_CTRL, V_SYNC_OFFS);
		पूर्ण
		अगर (hc->e1_resync & 4) अणु
			अगर (debug & DEBUG_HFCMULTI_PLXSD)
				prपूर्णांकk(KERN_DEBUG
				       "Enable QUARTZ for HFC-E1\n");
			/* set jatt to quartz */
			HFC_outb(hc, R_SYNC_CTRL, V_EXT_CLK_SYNC
				 | V_JATT_OFF);
			/* चयन to JATT, in हाल it is not alपढ़ोy */
			HFC_outb(hc, R_SYNC_OUT, 0);
		पूर्ण
		hc->e1_resync = 0;
		spin_unlock_irqrestore(&HFClock, flags);
	पूर्ण

	अगर (hc->ctype != HFC_TYPE_E1 || hc->e1_state == 1)
		क्रम (ch = 0; ch <= 31; ch++) अणु
			अगर (hc->created[hc->chan[ch].port]) अणु
				hfcmulti_tx(hc, ch);
				/* fअगरo is started when चयनing to rx-fअगरo */
				hfcmulti_rx(hc, ch);
				अगर (hc->chan[ch].dch &&
				    hc->chan[ch].nt_समयr > -1) अणु
					dch = hc->chan[ch].dch;
					अगर (!(--hc->chan[ch].nt_समयr)) अणु
						schedule_event(dch,
							       FLG_PHCHANGE);
						अगर (debug &
						    DEBUG_HFCMULTI_STATE)
							prपूर्णांकk(KERN_DEBUG
							       "%s: nt_timer at "
							       "state %x\n",
							       __func__,
							       dch->state);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	अगर (hc->ctype == HFC_TYPE_E1 && hc->created[0]) अणु
		dch = hc->chan[hc->dnum[0]].dch;
		/* LOS */
		temp = HFC_inb_nodebug(hc, R_SYNC_STA) & V_SIG_LOS;
		hc->chan[hc->dnum[0]].los = temp;
		अगर (test_bit(HFC_CFG_REPORT_LOS, &hc->chan[hc->dnum[0]].cfg)) अणु
			अगर (!temp && hc->chan[hc->dnum[0]].los)
				संकेत_state_up(dch, L1_SIGNAL_LOS_ON,
						"LOS detected");
			अगर (temp && !hc->chan[hc->dnum[0]].los)
				संकेत_state_up(dch, L1_SIGNAL_LOS_OFF,
						"LOS gone");
		पूर्ण
		अगर (test_bit(HFC_CFG_REPORT_AIS, &hc->chan[hc->dnum[0]].cfg)) अणु
			/* AIS */
			temp = HFC_inb_nodebug(hc, R_SYNC_STA) & V_AIS;
			अगर (!temp && hc->chan[hc->dnum[0]].ais)
				संकेत_state_up(dch, L1_SIGNAL_AIS_ON,
						"AIS detected");
			अगर (temp && !hc->chan[hc->dnum[0]].ais)
				संकेत_state_up(dch, L1_SIGNAL_AIS_OFF,
						"AIS gone");
			hc->chan[hc->dnum[0]].ais = temp;
		पूर्ण
		अगर (test_bit(HFC_CFG_REPORT_SLIP, &hc->chan[hc->dnum[0]].cfg)) अणु
			/* SLIP */
			temp = HFC_inb_nodebug(hc, R_SLIP) & V_FOSLIP_RX;
			अगर (!temp && hc->chan[hc->dnum[0]].slip_rx)
				संकेत_state_up(dch, L1_SIGNAL_SLIP_RX,
						" bit SLIP detected RX");
			hc->chan[hc->dnum[0]].slip_rx = temp;
			temp = HFC_inb_nodebug(hc, R_SLIP) & V_FOSLIP_TX;
			अगर (!temp && hc->chan[hc->dnum[0]].slip_tx)
				संकेत_state_up(dch, L1_SIGNAL_SLIP_TX,
						" bit SLIP detected TX");
			hc->chan[hc->dnum[0]].slip_tx = temp;
		पूर्ण
		अगर (test_bit(HFC_CFG_REPORT_RDI, &hc->chan[hc->dnum[0]].cfg)) अणु
			/* RDI */
			temp = HFC_inb_nodebug(hc, R_RX_SL0_0) & V_A;
			अगर (!temp && hc->chan[hc->dnum[0]].rdi)
				संकेत_state_up(dch, L1_SIGNAL_RDI_ON,
						"RDI detected");
			अगर (temp && !hc->chan[hc->dnum[0]].rdi)
				संकेत_state_up(dch, L1_SIGNAL_RDI_OFF,
						"RDI gone");
			hc->chan[hc->dnum[0]].rdi = temp;
		पूर्ण
		temp = HFC_inb_nodebug(hc, R_JATT_सूची);
		चयन (hc->chan[hc->dnum[0]].sync) अणु
		हाल 0:
			अगर ((temp & 0x60) == 0x60) अणु
				अगर (debug & DEBUG_HFCMULTI_SYNC)
					prपूर्णांकk(KERN_DEBUG
					       "%s: (id=%d) E1 now "
					       "in clock sync\n",
					       __func__, hc->id);
				HFC_outb(hc, R_RX_OFF,
				    hc->chan[hc->dnum[0]].jitter | V_RX_INIT);
				HFC_outb(hc, R_TX_OFF,
				    hc->chan[hc->dnum[0]].jitter | V_RX_INIT);
				hc->chan[hc->dnum[0]].sync = 1;
				जाओ check_framesync;
			पूर्ण
			अवरोध;
		हाल 1:
			अगर ((temp & 0x60) != 0x60) अणु
				अगर (debug & DEBUG_HFCMULTI_SYNC)
					prपूर्णांकk(KERN_DEBUG
					       "%s: (id=%d) E1 "
					       "lost clock sync\n",
					       __func__, hc->id);
				hc->chan[hc->dnum[0]].sync = 0;
				अवरोध;
			पूर्ण
		check_framesync:
			temp = HFC_inb_nodebug(hc, R_SYNC_STA);
			अगर (temp == 0x27) अणु
				अगर (debug & DEBUG_HFCMULTI_SYNC)
					prपूर्णांकk(KERN_DEBUG
					       "%s: (id=%d) E1 "
					       "now in frame sync\n",
					       __func__, hc->id);
				hc->chan[hc->dnum[0]].sync = 2;
			पूर्ण
			अवरोध;
		हाल 2:
			अगर ((temp & 0x60) != 0x60) अणु
				अगर (debug & DEBUG_HFCMULTI_SYNC)
					prपूर्णांकk(KERN_DEBUG
					       "%s: (id=%d) E1 lost "
					       "clock & frame sync\n",
					       __func__, hc->id);
				hc->chan[hc->dnum[0]].sync = 0;
				अवरोध;
			पूर्ण
			temp = HFC_inb_nodebug(hc, R_SYNC_STA);
			अगर (temp != 0x27) अणु
				अगर (debug & DEBUG_HFCMULTI_SYNC)
					prपूर्णांकk(KERN_DEBUG
					       "%s: (id=%d) E1 "
					       "lost frame sync\n",
					       __func__, hc->id);
				hc->chan[hc->dnum[0]].sync = 1;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (test_bit(HFC_CHIP_WATCHDOG, &hc->chip))
		hfcmulti_watchकरोg(hc);

	अगर (hc->leds)
		hfcmulti_leds(hc);
पूर्ण

अटल व्योम
ph_state_irq(काष्ठा hfc_multi *hc, u_अक्षर r_irq_statech)
अणु
	काष्ठा dchannel	*dch;
	पूर्णांक		ch;
	पूर्णांक		active;
	u_अक्षर		st_status, temp;

	/* state machine */
	क्रम (ch = 0; ch <= 31; ch++) अणु
		अगर (hc->chan[ch].dch) अणु
			dch = hc->chan[ch].dch;
			अगर (r_irq_statech & 1) अणु
				HFC_outb_nodebug(hc, R_ST_SEL,
						 hc->chan[ch].port);
				/* unकरोcumented: delay after R_ST_SEL */
				udelay(1);
				/* unकरोcumented: status changes during पढ़ो */
				st_status = HFC_inb_nodebug(hc, A_ST_RD_STATE);
				जबतक (st_status != (temp =
						     HFC_inb_nodebug(hc, A_ST_RD_STATE))) अणु
					अगर (debug & DEBUG_HFCMULTI_STATE)
						prपूर्णांकk(KERN_DEBUG "%s: reread "
						       "STATE because %d!=%d\n",
						       __func__, temp,
						       st_status);
					st_status = temp; /* repeat */
				पूर्ण

				/* Speech Design TE-sync indication */
				अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip) &&
				    dch->dev.D.protocol == ISDN_P_TE_S0) अणु
					अगर (st_status & V_FR_SYNC_ST)
						hc->syncronized |=
							(1 << hc->chan[ch].port);
					अन्यथा
						hc->syncronized &=
							~(1 << hc->chan[ch].port);
				पूर्ण
				dch->state = st_status & 0x0f;
				अगर (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				अन्यथा
					active = 7;
				अगर (dch->state == active) अणु
					HFC_outb_nodebug(hc, R_FIFO,
							 (ch << 1) | 1);
					HFC_रुको_nodebug(hc);
					HFC_outb_nodebug(hc,
							 R_INC_RES_FIFO, V_RES_F);
					HFC_रुको_nodebug(hc);
					dch->tx_idx = 0;
				पूर्ण
				schedule_event(dch, FLG_PHCHANGE);
				अगर (debug & DEBUG_HFCMULTI_STATE)
					prपूर्णांकk(KERN_DEBUG
					       "%s: S/T newstate %x port %d\n",
					       __func__, dch->state,
					       hc->chan[ch].port);
			पूर्ण
			r_irq_statech >>= 1;
		पूर्ण
	पूर्ण
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip))
		plxsd_checksync(hc, 0);
पूर्ण

अटल व्योम
fअगरo_irq(काष्ठा hfc_multi *hc, पूर्णांक block)
अणु
	पूर्णांक	ch, j;
	काष्ठा dchannel	*dch;
	काष्ठा bchannel	*bch;
	u_अक्षर r_irq_fअगरo_bl;

	r_irq_fअगरo_bl = HFC_inb_nodebug(hc, R_IRQ_FIFO_BL0 + block);
	j = 0;
	जबतक (j < 8) अणु
		ch = (block << 2) + (j >> 1);
		dch = hc->chan[ch].dch;
		bch = hc->chan[ch].bch;
		अगर (((!dch) && (!bch)) || (!hc->created[hc->chan[ch].port])) अणु
			j += 2;
			जारी;
		पूर्ण
		अगर (dch && (r_irq_fअगरo_bl & (1 << j)) &&
		    test_bit(FLG_ACTIVE, &dch->Flags)) अणु
			hfcmulti_tx(hc, ch);
			/* start fअगरo */
			HFC_outb_nodebug(hc, R_FIFO, 0);
			HFC_रुको_nodebug(hc);
		पूर्ण
		अगर (bch && (r_irq_fअगरo_bl & (1 << j)) &&
		    test_bit(FLG_ACTIVE, &bch->Flags)) अणु
			hfcmulti_tx(hc, ch);
			/* start fअगरo */
			HFC_outb_nodebug(hc, R_FIFO, 0);
			HFC_रुको_nodebug(hc);
		पूर्ण
		j++;
		अगर (dch && (r_irq_fअगरo_bl & (1 << j)) &&
		    test_bit(FLG_ACTIVE, &dch->Flags)) अणु
			hfcmulti_rx(hc, ch);
		पूर्ण
		अगर (bch && (r_irq_fअगरo_bl & (1 << j)) &&
		    test_bit(FLG_ACTIVE, &bch->Flags)) अणु
			hfcmulti_rx(hc, ch);
		पूर्ण
		j++;
	पूर्ण
पूर्ण

#अगर_घोषित IRQ_DEBUG
पूर्णांक irqsem;
#पूर्ण_अगर
अटल irqवापस_t
hfcmulti_पूर्णांकerrupt(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
#अगर_घोषित IRQCOUNT_DEBUG
	अटल पूर्णांक iq1 = 0, iq2 = 0, iq3 = 0, iq4 = 0,
		iq5 = 0, iq6 = 0, iqcnt = 0;
#पूर्ण_अगर
	काष्ठा hfc_multi	*hc = dev_id;
	काष्ठा dchannel		*dch;
	u_अक्षर			r_irq_statech, status, r_irq_misc, r_irq_oview;
	पूर्णांक			i;
	व्योम __iomem		*plx_acc;
	u_लघु			wval;
	u_अक्षर			e1_syncsta, temp, temp2;
	u_दीर्घ			flags;

	अगर (!hc) अणु
		prपूर्णांकk(KERN_ERR "HFC-multi: Spurious interrupt!\n");
		वापस IRQ_NONE;
	पूर्ण

	spin_lock(&hc->lock);

#अगर_घोषित IRQ_DEBUG
	अगर (irqsem)
		prपूर्णांकk(KERN_ERR "irq for card %d during irq from "
		       "card %d, this is no bug.\n", hc->id + 1, irqsem);
	irqsem = hc->id + 1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MISDN_HFCMULTI_8xx
	अगर (hc->immap->im_cpm.cp_pbdat & hc->pb_irqmsk)
		जाओ irq_notक्रमus;
#पूर्ण_अगर
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
		spin_lock_irqsave(&plx_lock, flags);
		plx_acc = hc->plx_membase + PLX_INTCSR;
		wval = पढ़ोw(plx_acc);
		spin_unlock_irqrestore(&plx_lock, flags);
		अगर (!(wval & PLX_INTCSR_LINTI1_STATUS))
			जाओ irq_notक्रमus;
	पूर्ण

	status = HFC_inb_nodebug(hc, R_STATUS);
	r_irq_statech = HFC_inb_nodebug(hc, R_IRQ_STATECH);
#अगर_घोषित IRQCOUNT_DEBUG
	अगर (r_irq_statech)
		iq1++;
	अगर (status & V_DTMF_STA)
		iq2++;
	अगर (status & V_LOST_STA)
		iq3++;
	अगर (status & V_EXT_IRQSTA)
		iq4++;
	अगर (status & V_MISC_IRQSTA)
		iq5++;
	अगर (status & V_FR_IRQSTA)
		iq6++;
	अगर (iqcnt++ > 5000) अणु
		prपूर्णांकk(KERN_ERR "iq1:%x iq2:%x iq3:%x iq4:%x iq5:%x iq6:%x\n",
		       iq1, iq2, iq3, iq4, iq5, iq6);
		iqcnt = 0;
	पूर्ण
#पूर्ण_अगर

	अगर (!r_irq_statech &&
	    !(status & (V_DTMF_STA | V_LOST_STA | V_EXT_IRQSTA |
			V_MISC_IRQSTA | V_FR_IRQSTA))) अणु
		/* irq is not क्रम us */
		जाओ irq_notक्रमus;
	पूर्ण
	hc->irqcnt++;
	अगर (r_irq_statech) अणु
		अगर (hc->ctype != HFC_TYPE_E1)
			ph_state_irq(hc, r_irq_statech);
	पूर्ण
	अगर (status & V_LOST_STA) अणु
		/* LOST IRQ */
		HFC_outb(hc, R_INC_RES_FIFO, V_RES_LOST); /* clear irq! */
	पूर्ण
	अगर (status & V_MISC_IRQSTA) अणु
		/* misc IRQ */
		r_irq_misc = HFC_inb_nodebug(hc, R_IRQ_MISC);
		r_irq_misc &= hc->hw.r_irqmsk_misc; /* ignore disabled irqs */
		अगर (r_irq_misc & V_STA_IRQ) अणु
			अगर (hc->ctype == HFC_TYPE_E1) अणु
				/* state machine */
				dch = hc->chan[hc->dnum[0]].dch;
				e1_syncsta = HFC_inb_nodebug(hc, R_SYNC_STA);
				अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)
				    && hc->e1_अ_लोlock) अणु
					अगर (e1_syncsta & V_FR_SYNC_E1)
						hc->syncronized = 1;
					अन्यथा
						hc->syncronized = 0;
				पूर्ण
				/* unकरोcumented: status changes during पढ़ो */
				temp = HFC_inb_nodebug(hc, R_E1_RD_STA);
				जबतक (temp != (temp2 =
						      HFC_inb_nodebug(hc, R_E1_RD_STA))) अणु
					अगर (debug & DEBUG_HFCMULTI_STATE)
						prपूर्णांकk(KERN_DEBUG "%s: reread "
						       "STATE because %d!=%d\n",
						    __func__, temp, temp2);
					temp = temp2; /* repeat */
				पूर्ण
				/* broadcast state change to all fragments */
				अगर (debug & DEBUG_HFCMULTI_STATE)
					prपूर्णांकk(KERN_DEBUG
					       "%s: E1 (id=%d) newstate %x\n",
					    __func__, hc->id, temp & 0x7);
				क्रम (i = 0; i < hc->ports; i++) अणु
					dch = hc->chan[hc->dnum[i]].dch;
					dch->state = temp & 0x7;
					schedule_event(dch, FLG_PHCHANGE);
				पूर्ण

				अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip))
					plxsd_checksync(hc, 0);
			पूर्ण
		पूर्ण
		अगर (r_irq_misc & V_TI_IRQ) अणु
			अगर (hc->iघड़ी_on)
				mISDN_घड़ी_update(hc->iघड़ी, poll, शून्य);
			handle_समयr_irq(hc);
		पूर्ण

		अगर (r_irq_misc & V_DTMF_IRQ)
			hfcmulti_dपंचांगf(hc);

		अगर (r_irq_misc & V_IRQ_PROC) अणु
			अटल पूर्णांक irq_proc_cnt;
			अगर (!irq_proc_cnt++)
				prपूर्णांकk(KERN_DEBUG "%s: got V_IRQ_PROC -"
				       " this should not happen\n", __func__);
		पूर्ण

	पूर्ण
	अगर (status & V_FR_IRQSTA) अणु
		/* FIFO IRQ */
		r_irq_oview = HFC_inb_nodebug(hc, R_IRQ_OVIEW);
		क्रम (i = 0; i < 8; i++) अणु
			अगर (r_irq_oview & (1 << i))
				fअगरo_irq(hc, i);
		पूर्ण
	पूर्ण

#अगर_घोषित IRQ_DEBUG
	irqsem = 0;
#पूर्ण_अगर
	spin_unlock(&hc->lock);
	वापस IRQ_HANDLED;

irq_notक्रमus:
#अगर_घोषित IRQ_DEBUG
	irqsem = 0;
#पूर्ण_अगर
	spin_unlock(&hc->lock);
	वापस IRQ_NONE;
पूर्ण


/*
 * समयr callback क्रम D-chan busy resolution. Currently no function
 */

अटल व्योम
hfcmulti_dbusy_समयr(काष्ठा समयr_list *t)
अणु
पूर्ण


/*
 * activate/deactivate hardware क्रम selected channels and mode
 *
 * configure B-channel with the given protocol
 * ch eqals to the HFC-channel (0-31)
 * ch is the number of channel (0-4,4-7,8-11,12-15,16-19,20-23,24-27,28-31
 * क्रम S/T, 1-31 क्रम E1)
 * the hdlc पूर्णांकerrupts will be set/unset
 */
अटल पूर्णांक
mode_hfcmulti(काष्ठा hfc_multi *hc, पूर्णांक ch, पूर्णांक protocol, पूर्णांक slot_tx,
	      पूर्णांक bank_tx, पूर्णांक slot_rx, पूर्णांक bank_rx)
अणु
	पूर्णांक flow_tx = 0, flow_rx = 0, routing = 0;
	पूर्णांक oslot_tx, oslot_rx;
	पूर्णांक conf;

	अगर (ch < 0 || ch > 31)
		वापस -EINVAL;
	oslot_tx = hc->chan[ch].slot_tx;
	oslot_rx = hc->chan[ch].slot_rx;
	conf = hc->chan[ch].conf;

	अगर (debug & DEBUG_HFCMULTI_MODE)
		prपूर्णांकk(KERN_DEBUG
		       "%s: card %d channel %d protocol %x slot old=%d new=%d "
		       "bank new=%d (TX) slot old=%d new=%d bank new=%d (RX)\n",
		       __func__, hc->id, ch, protocol, oslot_tx, slot_tx,
		       bank_tx, oslot_rx, slot_rx, bank_rx);

	अगर (oslot_tx >= 0 && slot_tx != oslot_tx) अणु
		/* हटाओ from slot */
		अगर (debug & DEBUG_HFCMULTI_MODE)
			prपूर्णांकk(KERN_DEBUG "%s: remove from slot %d (TX)\n",
			       __func__, oslot_tx);
		अगर (hc->slot_owner[oslot_tx << 1] == ch) अणु
			HFC_outb(hc, R_SLOT, oslot_tx << 1);
			HFC_outb(hc, A_SL_CFG, 0);
			अगर (hc->ctype != HFC_TYPE_XHFC)
				HFC_outb(hc, A_CONF, 0);
			hc->slot_owner[oslot_tx << 1] = -1;
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_MODE)
				prपूर्णांकk(KERN_DEBUG
				       "%s: we are not owner of this tx slot "
				       "anymore, channel %d is.\n",
				       __func__, hc->slot_owner[oslot_tx << 1]);
		पूर्ण
	पूर्ण

	अगर (oslot_rx >= 0 && slot_rx != oslot_rx) अणु
		/* हटाओ from slot */
		अगर (debug & DEBUG_HFCMULTI_MODE)
			prपूर्णांकk(KERN_DEBUG
			       "%s: remove from slot %d (RX)\n",
			       __func__, oslot_rx);
		अगर (hc->slot_owner[(oslot_rx << 1) | 1] == ch) अणु
			HFC_outb(hc, R_SLOT, (oslot_rx << 1) | V_SL_सूची);
			HFC_outb(hc, A_SL_CFG, 0);
			hc->slot_owner[(oslot_rx << 1) | 1] = -1;
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_MODE)
				prपूर्णांकk(KERN_DEBUG
				       "%s: we are not owner of this rx slot "
				       "anymore, channel %d is.\n",
				       __func__,
				       hc->slot_owner[(oslot_rx << 1) | 1]);
		पूर्ण
	पूर्ण

	अगर (slot_tx < 0) अणु
		flow_tx = 0x80; /* FIFO->ST */
		/* disable pcm slot */
		hc->chan[ch].slot_tx = -1;
		hc->chan[ch].bank_tx = 0;
	पूर्ण अन्यथा अणु
		/* set pcm slot */
		अगर (hc->chan[ch].txpending)
			flow_tx = 0x80; /* FIFO->ST */
		अन्यथा
			flow_tx = 0xc0; /* PCM->ST */
		/* put on slot */
		routing = bank_tx ? 0xc0 : 0x80;
		अगर (conf >= 0 || bank_tx > 1)
			routing = 0x40; /* loop */
		अगर (debug & DEBUG_HFCMULTI_MODE)
			prपूर्णांकk(KERN_DEBUG "%s: put channel %d to slot %d bank"
			       " %d flow %02x routing %02x conf %d (TX)\n",
			       __func__, ch, slot_tx, bank_tx,
			       flow_tx, routing, conf);
		HFC_outb(hc, R_SLOT, slot_tx << 1);
		HFC_outb(hc, A_SL_CFG, (ch << 1) | routing);
		अगर (hc->ctype != HFC_TYPE_XHFC)
			HFC_outb(hc, A_CONF,
				 (conf < 0) ? 0 : (conf | V_CONF_SL));
		hc->slot_owner[slot_tx << 1] = ch;
		hc->chan[ch].slot_tx = slot_tx;
		hc->chan[ch].bank_tx = bank_tx;
	पूर्ण
	अगर (slot_rx < 0) अणु
		/* disable pcm slot */
		flow_rx = 0x80; /* ST->FIFO */
		hc->chan[ch].slot_rx = -1;
		hc->chan[ch].bank_rx = 0;
	पूर्ण अन्यथा अणु
		/* set pcm slot */
		अगर (hc->chan[ch].txpending)
			flow_rx = 0x80; /* ST->FIFO */
		अन्यथा
			flow_rx = 0xc0; /* ST->(FIFO,PCM) */
		/* put on slot */
		routing = bank_rx ? 0x80 : 0xc0; /* reversed */
		अगर (conf >= 0 || bank_rx > 1)
			routing = 0x40; /* loop */
		अगर (debug & DEBUG_HFCMULTI_MODE)
			prपूर्णांकk(KERN_DEBUG "%s: put channel %d to slot %d bank"
			       " %d flow %02x routing %02x conf %d (RX)\n",
			       __func__, ch, slot_rx, bank_rx,
			       flow_rx, routing, conf);
		HFC_outb(hc, R_SLOT, (slot_rx << 1) | V_SL_सूची);
		HFC_outb(hc, A_SL_CFG, (ch << 1) | V_CH_सूची | routing);
		hc->slot_owner[(slot_rx << 1) | 1] = ch;
		hc->chan[ch].slot_rx = slot_rx;
		hc->chan[ch].bank_rx = bank_rx;
	पूर्ण

	चयन (protocol) अणु
	हाल (ISDN_P_NONE):
		/* disable TX fअगरo */
		HFC_outb(hc, R_FIFO, ch << 1);
		HFC_रुको(hc);
		HFC_outb(hc, A_CON_HDLC, flow_tx | 0x00 | V_IFF);
		HFC_outb(hc, A_SUBCH_CFG, 0);
		HFC_outb(hc, A_IRQ_MSK, 0);
		HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
		HFC_रुको(hc);
		/* disable RX fअगरo */
		HFC_outb(hc, R_FIFO, (ch << 1) | 1);
		HFC_रुको(hc);
		HFC_outb(hc, A_CON_HDLC, flow_rx | 0x00);
		HFC_outb(hc, A_SUBCH_CFG, 0);
		HFC_outb(hc, A_IRQ_MSK, 0);
		HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
		HFC_रुको(hc);
		अगर (hc->chan[ch].bch && hc->ctype != HFC_TYPE_E1) अणु
			hc->hw.a_st_ctrl0[hc->chan[ch].port] &=
				((ch & 0x3) == 0) ? ~V_B1_EN : ~V_B2_EN;
			HFC_outb(hc, R_ST_SEL, hc->chan[ch].port);
			/* unकरोcumented: delay after R_ST_SEL */
			udelay(1);
			HFC_outb(hc, A_ST_CTRL0,
				 hc->hw.a_st_ctrl0[hc->chan[ch].port]);
		पूर्ण
		अगर (hc->chan[ch].bch) अणु
			test_and_clear_bit(FLG_HDLC, &hc->chan[ch].bch->Flags);
			test_and_clear_bit(FLG_TRANSPARENT,
					   &hc->chan[ch].bch->Flags);
		पूर्ण
		अवरोध;
	हाल (ISDN_P_B_RAW): /* B-channel */

		अगर (test_bit(HFC_CHIP_B410P, &hc->chip) &&
		    (hc->chan[ch].slot_rx < 0) &&
		    (hc->chan[ch].slot_tx < 0)) अणु

			prपूर्णांकk(KERN_DEBUG
			       "Setting B-channel %d to echo cancelable "
			       "state on PCM slot %d\n", ch,
			       ((ch / 4) * 8) + ((ch % 4) * 4) + 1);
			prपूर्णांकk(KERN_DEBUG
			       "Enabling pass through for channel\n");
			vpm_out(hc, ch, ((ch / 4) * 8) +
				((ch % 4) * 4) + 1, 0x01);
			/* rx path */
			/* S/T -> PCM */
			HFC_outb(hc, R_FIFO, (ch << 1));
			HFC_रुको(hc);
			HFC_outb(hc, A_CON_HDLC, 0xc0 | V_HDLC_TRP | V_IFF);
			HFC_outb(hc, R_SLOT, (((ch / 4) * 8) +
					      ((ch % 4) * 4) + 1) << 1);
			HFC_outb(hc, A_SL_CFG, 0x80 | (ch << 1));

			/* PCM -> FIFO */
			HFC_outb(hc, R_FIFO, 0x20 | (ch << 1) | 1);
			HFC_रुको(hc);
			HFC_outb(hc, A_CON_HDLC, 0x20 | V_HDLC_TRP | V_IFF);
			HFC_outb(hc, A_SUBCH_CFG, 0);
			HFC_outb(hc, A_IRQ_MSK, 0);
			अगर (hc->chan[ch].protocol != protocol) अणु
				HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
				HFC_रुको(hc);
			पूर्ण
			HFC_outb(hc, R_SLOT, ((((ch / 4) * 8) +
					       ((ch % 4) * 4) + 1) << 1) | 1);
			HFC_outb(hc, A_SL_CFG, 0x80 | 0x20 | (ch << 1) | 1);

			/* tx path */
			/* PCM -> S/T */
			HFC_outb(hc, R_FIFO, (ch << 1) | 1);
			HFC_रुको(hc);
			HFC_outb(hc, A_CON_HDLC, 0xc0 | V_HDLC_TRP | V_IFF);
			HFC_outb(hc, R_SLOT, ((((ch / 4) * 8) +
					       ((ch % 4) * 4)) << 1) | 1);
			HFC_outb(hc, A_SL_CFG, 0x80 | 0x40 | (ch << 1) | 1);

			/* FIFO -> PCM */
			HFC_outb(hc, R_FIFO, 0x20 | (ch << 1));
			HFC_रुको(hc);
			HFC_outb(hc, A_CON_HDLC, 0x20 | V_HDLC_TRP | V_IFF);
			HFC_outb(hc, A_SUBCH_CFG, 0);
			HFC_outb(hc, A_IRQ_MSK, 0);
			अगर (hc->chan[ch].protocol != protocol) अणु
				HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
				HFC_रुको(hc);
			पूर्ण
			/* tx silence */
			HFC_outb_nodebug(hc, A_FIFO_DATA0_NOINC, hc->silence);
			HFC_outb(hc, R_SLOT, (((ch / 4) * 8) +
					      ((ch % 4) * 4)) << 1);
			HFC_outb(hc, A_SL_CFG, 0x80 | 0x20 | (ch << 1));
		पूर्ण अन्यथा अणु
			/* enable TX fअगरo */
			HFC_outb(hc, R_FIFO, ch << 1);
			HFC_रुको(hc);
			अगर (hc->ctype == HFC_TYPE_XHFC)
				HFC_outb(hc, A_CON_HDLC, flow_tx | 0x07 << 2 |
					 V_HDLC_TRP | V_IFF);
			/* Enable FIFO, no पूर्णांकerrupt */
			अन्यथा
				HFC_outb(hc, A_CON_HDLC, flow_tx | 0x00 |
					 V_HDLC_TRP | V_IFF);
			HFC_outb(hc, A_SUBCH_CFG, 0);
			HFC_outb(hc, A_IRQ_MSK, 0);
			अगर (hc->chan[ch].protocol != protocol) अणु
				HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
				HFC_रुको(hc);
			पूर्ण
			/* tx silence */
			HFC_outb_nodebug(hc, A_FIFO_DATA0_NOINC, hc->silence);
			/* enable RX fअगरo */
			HFC_outb(hc, R_FIFO, (ch << 1) | 1);
			HFC_रुको(hc);
			अगर (hc->ctype == HFC_TYPE_XHFC)
				HFC_outb(hc, A_CON_HDLC, flow_rx | 0x07 << 2 |
					 V_HDLC_TRP);
			/* Enable FIFO, no पूर्णांकerrupt*/
			अन्यथा
				HFC_outb(hc, A_CON_HDLC, flow_rx | 0x00 |
					 V_HDLC_TRP);
			HFC_outb(hc, A_SUBCH_CFG, 0);
			HFC_outb(hc, A_IRQ_MSK, 0);
			अगर (hc->chan[ch].protocol != protocol) अणु
				HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
				HFC_रुको(hc);
			पूर्ण
		पूर्ण
		अगर (hc->ctype != HFC_TYPE_E1) अणु
			hc->hw.a_st_ctrl0[hc->chan[ch].port] |=
				((ch & 0x3) == 0) ? V_B1_EN : V_B2_EN;
			HFC_outb(hc, R_ST_SEL, hc->chan[ch].port);
			/* unकरोcumented: delay after R_ST_SEL */
			udelay(1);
			HFC_outb(hc, A_ST_CTRL0,
				 hc->hw.a_st_ctrl0[hc->chan[ch].port]);
		पूर्ण
		अगर (hc->chan[ch].bch)
			test_and_set_bit(FLG_TRANSPARENT,
					 &hc->chan[ch].bch->Flags);
		अवरोध;
	हाल (ISDN_P_B_HDLC): /* B-channel */
	हाल (ISDN_P_TE_S0): /* D-channel */
	हाल (ISDN_P_NT_S0):
	हाल (ISDN_P_TE_E1):
	हाल (ISDN_P_NT_E1):
		/* enable TX fअगरo */
		HFC_outb(hc, R_FIFO, ch << 1);
		HFC_रुको(hc);
		अगर (hc->ctype == HFC_TYPE_E1 || hc->chan[ch].bch) अणु
			/* E1 or B-channel */
			HFC_outb(hc, A_CON_HDLC, flow_tx | 0x04);
			HFC_outb(hc, A_SUBCH_CFG, 0);
		पूर्ण अन्यथा अणु
			/* D-Channel without HDLC fill flags */
			HFC_outb(hc, A_CON_HDLC, flow_tx | 0x04 | V_IFF);
			HFC_outb(hc, A_SUBCH_CFG, 2);
		पूर्ण
		HFC_outb(hc, A_IRQ_MSK, V_IRQ);
		HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
		HFC_रुको(hc);
		/* enable RX fअगरo */
		HFC_outb(hc, R_FIFO, (ch << 1) | 1);
		HFC_रुको(hc);
		HFC_outb(hc, A_CON_HDLC, flow_rx | 0x04);
		अगर (hc->ctype == HFC_TYPE_E1 || hc->chan[ch].bch)
			HFC_outb(hc, A_SUBCH_CFG, 0); /* full 8 bits */
		अन्यथा
			HFC_outb(hc, A_SUBCH_CFG, 2); /* 2 bits dchannel */
		HFC_outb(hc, A_IRQ_MSK, V_IRQ);
		HFC_outb(hc, R_INC_RES_FIFO, V_RES_F);
		HFC_रुको(hc);
		अगर (hc->chan[ch].bch) अणु
			test_and_set_bit(FLG_HDLC, &hc->chan[ch].bch->Flags);
			अगर (hc->ctype != HFC_TYPE_E1) अणु
				hc->hw.a_st_ctrl0[hc->chan[ch].port] |=
					((ch & 0x3) == 0) ? V_B1_EN : V_B2_EN;
				HFC_outb(hc, R_ST_SEL, hc->chan[ch].port);
				/* unकरोcumented: delay after R_ST_SEL */
				udelay(1);
				HFC_outb(hc, A_ST_CTRL0,
					 hc->hw.a_st_ctrl0[hc->chan[ch].port]);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "%s: protocol not known %x\n",
		       __func__, protocol);
		hc->chan[ch].protocol = ISDN_P_NONE;
		वापस -ENOPROTOOPT;
	पूर्ण
	hc->chan[ch].protocol = protocol;
	वापस 0;
पूर्ण


/*
 * connect/disconnect PCM
 */

अटल व्योम
hfcmulti_pcm(काष्ठा hfc_multi *hc, पूर्णांक ch, पूर्णांक slot_tx, पूर्णांक bank_tx,
	     पूर्णांक slot_rx, पूर्णांक bank_rx)
अणु
	अगर (slot_tx < 0 || slot_rx < 0 || bank_tx < 0 || bank_rx < 0) अणु
		/* disable PCM */
		mode_hfcmulti(hc, ch, hc->chan[ch].protocol, -1, 0, -1, 0);
		वापस;
	पूर्ण

	/* enable pcm */
	mode_hfcmulti(hc, ch, hc->chan[ch].protocol, slot_tx, bank_tx,
		      slot_rx, bank_rx);
पूर्ण

/*
 * set/disable conference
 */

अटल व्योम
hfcmulti_conf(काष्ठा hfc_multi *hc, पूर्णांक ch, पूर्णांक num)
अणु
	अगर (num >= 0 && num <= 7)
		hc->chan[ch].conf = num;
	अन्यथा
		hc->chan[ch].conf = -1;
	mode_hfcmulti(hc, ch, hc->chan[ch].protocol, hc->chan[ch].slot_tx,
		      hc->chan[ch].bank_tx, hc->chan[ch].slot_rx,
		      hc->chan[ch].bank_rx);
पूर्ण


/*
 * set/disable sample loop
 */

/* NOTE: this function is experimental and thereक्रमe disabled */

/*
 * Layer 1 callback function
 */
अटल पूर्णांक
hfcm_l1callback(काष्ठा dchannel *dch, u_पूर्णांक cmd)
अणु
	काष्ठा hfc_multi	*hc = dch->hw;
	u_दीर्घ	flags;

	चयन (cmd) अणु
	हाल INFO3_P8:
	हाल INFO3_P10:
		अवरोध;
	हाल HW_RESET_REQ:
		/* start activation */
		spin_lock_irqsave(&hc->lock, flags);
		अगर (hc->ctype == HFC_TYPE_E1) अणु
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG
				       "%s: HW_RESET_REQ no BRI\n",
				       __func__);
		पूर्ण अन्यथा अणु
			HFC_outb(hc, R_ST_SEL, hc->chan[dch->slot].port);
			/* unकरोcumented: delay after R_ST_SEL */
			udelay(1);
			HFC_outb(hc, A_ST_WR_STATE, V_ST_LD_STA | 3); /* F3 */
			udelay(6); /* रुको at least 5,21us */
			HFC_outb(hc, A_ST_WR_STATE, 3);
			HFC_outb(hc, A_ST_WR_STATE, 3 | (V_ST_ACT * 3));
			/* activate */
		पूर्ण
		spin_unlock_irqrestore(&hc->lock, flags);
		l1_event(dch->l1, HW_POWERUP_IND);
		अवरोध;
	हाल HW_DEACT_REQ:
		/* start deactivation */
		spin_lock_irqsave(&hc->lock, flags);
		अगर (hc->ctype == HFC_TYPE_E1) अणु
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG
				       "%s: HW_DEACT_REQ no BRI\n",
				       __func__);
		पूर्ण अन्यथा अणु
			HFC_outb(hc, R_ST_SEL, hc->chan[dch->slot].port);
			/* unकरोcumented: delay after R_ST_SEL */
			udelay(1);
			HFC_outb(hc, A_ST_WR_STATE, V_ST_ACT * 2);
			/* deactivate */
			अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
				hc->syncronized &=
					~(1 << hc->chan[dch->slot].port);
				plxsd_checksync(hc, 0);
			पूर्ण
		पूर्ण
		skb_queue_purge(&dch->squeue);
		अगर (dch->tx_skb) अणु
			dev_kमुक्त_skb(dch->tx_skb);
			dch->tx_skb = शून्य;
		पूर्ण
		dch->tx_idx = 0;
		अगर (dch->rx_skb) अणु
			dev_kमुक्त_skb(dch->rx_skb);
			dch->rx_skb = शून्य;
		पूर्ण
		test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
		अगर (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
			del_समयr(&dch->समयr);
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	हाल HW_POWERUP_REQ:
		spin_lock_irqsave(&hc->lock, flags);
		अगर (hc->ctype == HFC_TYPE_E1) अणु
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG
				       "%s: HW_POWERUP_REQ no BRI\n",
				       __func__);
		पूर्ण अन्यथा अणु
			HFC_outb(hc, R_ST_SEL, hc->chan[dch->slot].port);
			/* unकरोcumented: delay after R_ST_SEL */
			udelay(1);
			HFC_outb(hc, A_ST_WR_STATE, 3 | 0x10); /* activate */
			udelay(6); /* रुको at least 5,21us */
			HFC_outb(hc, A_ST_WR_STATE, 3); /* activate */
		पूर्ण
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	हाल PH_ACTIVATE_IND:
		test_and_set_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, शून्य,
			    GFP_ATOMIC);
		अवरोध;
	हाल PH_DEACTIVATE_IND:
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, शून्य,
			    GFP_ATOMIC);
		अवरोध;
	शेष:
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Layer2 -> Layer 1 Transfer
 */

अटल पूर्णांक
handle_dmsg(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा hfc_multi	*hc = dch->hw;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	पूर्णांक			ret = -EINVAL;
	अचिन्हित पूर्णांक		id;
	u_दीर्घ			flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		अगर (skb->len < 1)
			अवरोध;
		spin_lock_irqsave(&hc->lock, flags);
		ret = dchannel_senddata(dch, skb);
		अगर (ret > 0) अणु /* direct TX */
			id = hh->id; /* skb can be मुक्तd */
			hfcmulti_tx(hc, dch->slot);
			ret = 0;
			/* start fअगरo */
			HFC_outb(hc, R_FIFO, 0);
			HFC_रुको(hc);
			spin_unlock_irqrestore(&hc->lock, flags);
			queue_ch_frame(ch, PH_DATA_CNF, id, शून्य);
		पूर्ण अन्यथा
			spin_unlock_irqrestore(&hc->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		अगर (dch->dev.D.protocol != ISDN_P_TE_S0) अणु
			spin_lock_irqsave(&hc->lock, flags);
			ret = 0;
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG
				       "%s: PH_ACTIVATE port %d (0..%d)\n",
				       __func__, hc->chan[dch->slot].port,
				       hc->ports - 1);
			/* start activation */
			अगर (hc->ctype == HFC_TYPE_E1) अणु
				ph_state_change(dch);
				अगर (debug & DEBUG_HFCMULTI_STATE)
					prपूर्णांकk(KERN_DEBUG
					       "%s: E1 report state %x \n",
					       __func__, dch->state);
			पूर्ण अन्यथा अणु
				HFC_outb(hc, R_ST_SEL,
					 hc->chan[dch->slot].port);
				/* unकरोcumented: delay after R_ST_SEL */
				udelay(1);
				HFC_outb(hc, A_ST_WR_STATE, V_ST_LD_STA | 1);
				/* G1 */
				udelay(6); /* रुको at least 5,21us */
				HFC_outb(hc, A_ST_WR_STATE, 1);
				HFC_outb(hc, A_ST_WR_STATE, 1 |
					 (V_ST_ACT * 3)); /* activate */
				dch->state = 1;
			पूर्ण
			spin_unlock_irqrestore(&hc->lock, flags);
		पूर्ण अन्यथा
			ret = l1_event(dch->l1, hh->prim);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		test_and_clear_bit(FLG_L2_ACTIVATED, &dch->Flags);
		अगर (dch->dev.D.protocol != ISDN_P_TE_S0) अणु
			spin_lock_irqsave(&hc->lock, flags);
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG
				       "%s: PH_DEACTIVATE port %d (0..%d)\n",
				       __func__, hc->chan[dch->slot].port,
				       hc->ports - 1);
			/* start deactivation */
			अगर (hc->ctype == HFC_TYPE_E1) अणु
				अगर (debug & DEBUG_HFCMULTI_MSG)
					prपूर्णांकk(KERN_DEBUG
					       "%s: PH_DEACTIVATE no BRI\n",
					       __func__);
			पूर्ण अन्यथा अणु
				HFC_outb(hc, R_ST_SEL,
					 hc->chan[dch->slot].port);
				/* unकरोcumented: delay after R_ST_SEL */
				udelay(1);
				HFC_outb(hc, A_ST_WR_STATE, V_ST_ACT * 2);
				/* deactivate */
				dch->state = 1;
			पूर्ण
			skb_queue_purge(&dch->squeue);
			अगर (dch->tx_skb) अणु
				dev_kमुक्त_skb(dch->tx_skb);
				dch->tx_skb = शून्य;
			पूर्ण
			dch->tx_idx = 0;
			अगर (dch->rx_skb) अणु
				dev_kमुक्त_skb(dch->rx_skb);
				dch->rx_skb = शून्य;
			पूर्ण
			test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
			अगर (test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags))
				del_समयr(&dch->समयr);
#अगर_घोषित FIXME
			अगर (test_and_clear_bit(FLG_L1_BUSY, &dch->Flags))
				dchannel_sched_event(&hc->dch, D_CLEARBUSY);
#पूर्ण_अगर
			ret = 0;
			spin_unlock_irqrestore(&hc->lock, flags);
		पूर्ण अन्यथा
			ret = l1_event(dch->l1, hh->prim);
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल व्योम
deactivate_bchannel(काष्ठा bchannel *bch)
अणु
	काष्ठा hfc_multi	*hc = bch->hw;
	u_दीर्घ			flags;

	spin_lock_irqsave(&hc->lock, flags);
	mISDN_clear_bchannel(bch);
	hc->chan[bch->slot].coeff_count = 0;
	hc->chan[bch->slot].rx_off = 0;
	hc->chan[bch->slot].conf = -1;
	mode_hfcmulti(hc, bch->slot, ISDN_P_NONE, -1, 0, -1, 0);
	spin_unlock_irqrestore(&hc->lock, flags);
पूर्ण

अटल पूर्णांक
handle_bmsg(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel		*bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hfc_multi	*hc = bch->hw;
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	अचिन्हित दीर्घ		flags;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		अगर (!skb->len)
			अवरोध;
		spin_lock_irqsave(&hc->lock, flags);
		ret = bchannel_senddata(bch, skb);
		अगर (ret > 0) अणु /* direct TX */
			hfcmulti_tx(hc, bch->slot);
			ret = 0;
			/* start fअगरo */
			HFC_outb_nodebug(hc, R_FIFO, 0);
			HFC_रुको_nodebug(hc);
		पूर्ण
		spin_unlock_irqrestore(&hc->lock, flags);
		वापस ret;
	हाल PH_ACTIVATE_REQ:
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: PH_ACTIVATE ch %d (0..32)\n",
			       __func__, bch->slot);
		spin_lock_irqsave(&hc->lock, flags);
		/* activate B-channel अगर not alपढ़ोy activated */
		अगर (!test_and_set_bit(FLG_ACTIVE, &bch->Flags)) अणु
			hc->chan[bch->slot].txpending = 0;
			ret = mode_hfcmulti(hc, bch->slot,
					    ch->protocol,
					    hc->chan[bch->slot].slot_tx,
					    hc->chan[bch->slot].bank_tx,
					    hc->chan[bch->slot].slot_rx,
					    hc->chan[bch->slot].bank_rx);
			अगर (!ret) अणु
				अगर (ch->protocol == ISDN_P_B_RAW && !hc->dपंचांगf
				    && test_bit(HFC_CHIP_DTMF, &hc->chip)) अणु
					/* start decoder */
					hc->dपंचांगf = 1;
					अगर (debug & DEBUG_HFCMULTI_DTMF)
						prपूर्णांकk(KERN_DEBUG
						       "%s: start dtmf decoder\n",
						       __func__);
					HFC_outb(hc, R_DTMF, hc->hw.r_dपंचांगf |
						 V_RST_DTMF);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			ret = 0;
		spin_unlock_irqrestore(&hc->lock, flags);
		अगर (!ret)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0, शून्य,
				    GFP_KERNEL);
		अवरोध;
	हाल PH_CONTROL_REQ:
		spin_lock_irqsave(&hc->lock, flags);
		चयन (hh->id) अणु
		हाल HFC_SPL_LOOP_ON: /* set sample loop */
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG
				       "%s: HFC_SPL_LOOP_ON (len = %d)\n",
				       __func__, skb->len);
			ret = 0;
			अवरोध;
		हाल HFC_SPL_LOOP_OFF: /* set silence */
			अगर (debug & DEBUG_HFCMULTI_MSG)
				prपूर्णांकk(KERN_DEBUG "%s: HFC_SPL_LOOP_OFF\n",
				       __func__);
			ret = 0;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR
			       "%s: unknown PH_CONTROL_REQ info %x\n",
			       __func__, hh->id);
			ret = -EINVAL;
		पूर्ण
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	हाल PH_DEACTIVATE_REQ:
		deactivate_bchannel(bch); /* locked there */
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0, शून्य,
			    GFP_KERNEL);
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/*
 * bchannel control function
 */
अटल पूर्णांक
channel_bctrl(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक			ret = 0;
	काष्ठा dsp_features	*features =
		(काष्ठा dsp_features *)(*((u_दीर्घ *)&cq->p1));
	काष्ठा hfc_multi	*hc = bch->hw;
	पूर्णांक			slot_tx;
	पूर्णांक			bank_tx;
	पूर्णांक			slot_rx;
	पूर्णांक			bank_rx;
	पूर्णांक			num;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		ret = mISDN_ctrl_bchannel(bch, cq);
		cq->op |= MISDN_CTRL_HFC_OP | MISDN_CTRL_HW_FEATURES_OP;
		अवरोध;
	हाल MISDN_CTRL_RX_OFF: /* turn off / on rx stream */
		ret = mISDN_ctrl_bchannel(bch, cq);
		hc->chan[bch->slot].rx_off = !!cq->p1;
		अगर (!hc->chan[bch->slot].rx_off) अणु
			/* reset fअगरo on rx on */
			HFC_outb_nodebug(hc, R_FIFO, (bch->slot << 1) | 1);
			HFC_रुको_nodebug(hc);
			HFC_outb_nodebug(hc, R_INC_RES_FIFO, V_RES_F);
			HFC_रुको_nodebug(hc);
		पूर्ण
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: RX_OFF request (nr=%d off=%d)\n",
			       __func__, bch->nr, hc->chan[bch->slot].rx_off);
		अवरोध;
	हाल MISDN_CTRL_FILL_EMPTY:
		ret = mISDN_ctrl_bchannel(bch, cq);
		hc->silence = bch->fill[0];
		स_रखो(hc->silence_data, hc->silence, माप(hc->silence_data));
		अवरोध;
	हाल MISDN_CTRL_HW_FEATURES: /* fill features काष्ठाure */
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HW_FEATURE request\n",
			       __func__);
		/* create confirm */
		features->hfc_id = hc->id;
		अगर (test_bit(HFC_CHIP_DTMF, &hc->chip))
			features->hfc_dपंचांगf = 1;
		अगर (test_bit(HFC_CHIP_CONF, &hc->chip))
			features->hfc_conf = 1;
		features->hfc_loops = 0;
		अगर (test_bit(HFC_CHIP_B410P, &hc->chip)) अणु
			features->hfc_echocanhw = 1;
		पूर्ण अन्यथा अणु
			features->pcm_id = hc->pcm;
			features->pcm_slots = hc->slots;
			features->pcm_banks = 2;
		पूर्ण
		अवरोध;
	हाल MISDN_CTRL_HFC_PCM_CONN: /* connect to pcm बारlot (0..N) */
		slot_tx = cq->p1 & 0xff;
		bank_tx = cq->p1 >> 8;
		slot_rx = cq->p2 & 0xff;
		bank_rx = cq->p2 >> 8;
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG
			       "%s: HFC_PCM_CONN slot %d bank %d (TX) "
			       "slot %d bank %d (RX)\n",
			       __func__, slot_tx, bank_tx,
			       slot_rx, bank_rx);
		अगर (slot_tx < hc->slots && bank_tx <= 2 &&
		    slot_rx < hc->slots && bank_rx <= 2)
			hfcmulti_pcm(hc, bch->slot,
				     slot_tx, bank_tx, slot_rx, bank_rx);
		अन्यथा अणु
			prपूर्णांकk(KERN_WARNING
			       "%s: HFC_PCM_CONN slot %d bank %d (TX) "
			       "slot %d bank %d (RX) out of range\n",
			       __func__, slot_tx, bank_tx,
			       slot_rx, bank_rx);
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल MISDN_CTRL_HFC_PCM_DISC: /* release पूर्णांकerface from pcm बारlot */
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HFC_PCM_DISC\n",
			       __func__);
		hfcmulti_pcm(hc, bch->slot, -1, 0, -1, 0);
		अवरोध;
	हाल MISDN_CTRL_HFC_CONF_JOIN: /* join conference (0..7) */
		num = cq->p1 & 0xff;
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HFC_CONF_JOIN conf %d\n",
			       __func__, num);
		अगर (num <= 7)
			hfcmulti_conf(hc, bch->slot, num);
		अन्यथा अणु
			prपूर्णांकk(KERN_WARNING
			       "%s: HW_CONF_JOIN conf %d out of range\n",
			       __func__, num);
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल MISDN_CTRL_HFC_CONF_SPLIT: /* split conference */
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HFC_CONF_SPLIT\n", __func__);
		hfcmulti_conf(hc, bch->slot, -1);
		अवरोध;
	हाल MISDN_CTRL_HFC_ECHOCAN_ON:
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HFC_ECHOCAN_ON\n", __func__);
		अगर (test_bit(HFC_CHIP_B410P, &hc->chip))
			vpm_echocan_on(hc, bch->slot, cq->p1);
		अन्यथा
			ret = -EINVAL;
		अवरोध;

	हाल MISDN_CTRL_HFC_ECHOCAN_OFF:
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HFC_ECHOCAN_OFF\n",
			       __func__);
		अगर (test_bit(HFC_CHIP_B410P, &hc->chip))
			vpm_echocan_off(hc, bch->slot);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	शेष:
		ret = mISDN_ctrl_bchannel(bch, cq);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
hfcm_bctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा bchannel		*bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा hfc_multi	*hc = bch->hw;
	पूर्णांक			err = -EINVAL;
	u_दीर्घ	flags;

	अगर (bch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		deactivate_bchannel(bch); /* locked there */
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		err = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		spin_lock_irqsave(&hc->lock, flags);
		err = channel_bctrl(bch, arg);
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown prim(%x)\n",
		       __func__, cmd);
	पूर्ण
	वापस err;
पूर्ण

/*
 * handle D-channel events
 *
 * handle state change event
 */
अटल व्योम
ph_state_change(काष्ठा dchannel *dch)
अणु
	काष्ठा hfc_multi *hc;
	पूर्णांक ch, i;

	अगर (!dch) अणु
		prपूर्णांकk(KERN_WARNING "%s: ERROR given dch is NULL\n", __func__);
		वापस;
	पूर्ण
	hc = dch->hw;
	ch = dch->slot;

	अगर (hc->ctype == HFC_TYPE_E1) अणु
		अगर (dch->dev.D.protocol == ISDN_P_TE_E1) अणु
			अगर (debug & DEBUG_HFCMULTI_STATE)
				prपूर्णांकk(KERN_DEBUG
				       "%s: E1 TE (id=%d) newstate %x\n",
				       __func__, hc->id, dch->state);
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_STATE)
				prपूर्णांकk(KERN_DEBUG
				       "%s: E1 NT (id=%d) newstate %x\n",
				       __func__, hc->id, dch->state);
		पूर्ण
		चयन (dch->state) अणु
		हाल (1):
			अगर (hc->e1_state != 1) अणु
				क्रम (i = 1; i <= 31; i++) अणु
					/* reset fअगरos on e1 activation */
					HFC_outb_nodebug(hc, R_FIFO,
							 (i << 1) | 1);
					HFC_रुको_nodebug(hc);
					HFC_outb_nodebug(hc, R_INC_RES_FIFO,
							 V_RES_F);
					HFC_रुको_nodebug(hc);
				पूर्ण
			पूर्ण
			test_and_set_bit(FLG_ACTIVE, &dch->Flags);
			_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
				    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
			अवरोध;

		शेष:
			अगर (hc->e1_state != 1)
				वापस;
			test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
			_queue_data(&dch->dev.D, PH_DEACTIVATE_IND,
				    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
		पूर्ण
		hc->e1_state = dch->state;
	पूर्ण अन्यथा अणु
		अगर (dch->dev.D.protocol == ISDN_P_TE_S0) अणु
			अगर (debug & DEBUG_HFCMULTI_STATE)
				prपूर्णांकk(KERN_DEBUG
				       "%s: S/T TE newstate %x\n",
				       __func__, dch->state);
			चयन (dch->state) अणु
			हाल (0):
				l1_event(dch->l1, HW_RESET_IND);
				अवरोध;
			हाल (3):
				l1_event(dch->l1, HW_DEACT_IND);
				अवरोध;
			हाल (5):
			हाल (8):
				l1_event(dch->l1, ANYSIGNAL);
				अवरोध;
			हाल (6):
				l1_event(dch->l1, INFO2);
				अवरोध;
			हाल (7):
				l1_event(dch->l1, INFO4_P8);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_STATE)
				prपूर्णांकk(KERN_DEBUG "%s: S/T NT newstate %x\n",
				       __func__, dch->state);
			चयन (dch->state) अणु
			हाल (2):
				अगर (hc->chan[ch].nt_समयr == 0) अणु
					hc->chan[ch].nt_समयr = -1;
					HFC_outb(hc, R_ST_SEL,
						 hc->chan[ch].port);
					/* unकरोcumented: delay after R_ST_SEL */
					udelay(1);
					HFC_outb(hc, A_ST_WR_STATE, 4 |
						 V_ST_LD_STA); /* G4 */
					udelay(6); /* रुको at least 5,21us */
					HFC_outb(hc, A_ST_WR_STATE, 4);
					dch->state = 4;
				पूर्ण अन्यथा अणु
					/* one extra count क्रम the next event */
					hc->chan[ch].nt_समयr =
						nt_t1_count[poll_समयr] + 1;
					HFC_outb(hc, R_ST_SEL,
						 hc->chan[ch].port);
					/* unकरोcumented: delay after R_ST_SEL */
					udelay(1);
					/* allow G2 -> G3 transition */
					HFC_outb(hc, A_ST_WR_STATE, 2 |
						 V_SET_G2_G3);
				पूर्ण
				अवरोध;
			हाल (1):
				hc->chan[ch].nt_समयr = -1;
				test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
				_queue_data(&dch->dev.D, PH_DEACTIVATE_IND,
					    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
				अवरोध;
			हाल (4):
				hc->chan[ch].nt_समयr = -1;
				अवरोध;
			हाल (3):
				hc->chan[ch].nt_समयr = -1;
				test_and_set_bit(FLG_ACTIVE, &dch->Flags);
				_queue_data(&dch->dev.D, PH_ACTIVATE_IND,
					    MISDN_ID_ANY, 0, शून्य, GFP_ATOMIC);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * called क्रम card mode init message
 */

अटल व्योम
hfcmulti_iniपंचांगode(काष्ठा dchannel *dch)
अणु
	काष्ठा hfc_multi *hc = dch->hw;
	u_अक्षर		a_st_wr_state, r_e1_wr_sta;
	पूर्णांक		i, pt;

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: entered\n", __func__);

	i = dch->slot;
	pt = hc->chan[i].port;
	अगर (hc->ctype == HFC_TYPE_E1) अणु
		/* E1 */
		hc->chan[hc->dnum[pt]].slot_tx = -1;
		hc->chan[hc->dnum[pt]].slot_rx = -1;
		hc->chan[hc->dnum[pt]].conf = -1;
		अगर (hc->dnum[pt]) अणु
			mode_hfcmulti(hc, dch->slot, dch->dev.D.protocol,
				      -1, 0, -1, 0);
			समयr_setup(&dch->समयr, hfcmulti_dbusy_समयr, 0);
		पूर्ण
		क्रम (i = 1; i <= 31; i++) अणु
			अगर (!((1 << i) & hc->bmask[pt])) /* skip unused chan */
				जारी;
			hc->chan[i].slot_tx = -1;
			hc->chan[i].slot_rx = -1;
			hc->chan[i].conf = -1;
			mode_hfcmulti(hc, i, ISDN_P_NONE, -1, 0, -1, 0);
		पूर्ण
	पूर्ण
	अगर (hc->ctype == HFC_TYPE_E1 && pt == 0) अणु
		/* E1, port 0 */
		dch = hc->chan[hc->dnum[0]].dch;
		अगर (test_bit(HFC_CFG_REPORT_LOS, &hc->chan[hc->dnum[0]].cfg)) अणु
			HFC_outb(hc, R_LOS0, 255); /* 2 ms */
			HFC_outb(hc, R_LOS1, 255); /* 512 ms */
		पूर्ण
		अगर (test_bit(HFC_CFG_OPTICAL, &hc->chan[hc->dnum[0]].cfg)) अणु
			HFC_outb(hc, R_RX0, 0);
			hc->hw.r_tx0 = 0 | V_OUT_EN;
		पूर्ण अन्यथा अणु
			HFC_outb(hc, R_RX0, 1);
			hc->hw.r_tx0 = 1 | V_OUT_EN;
		पूर्ण
		hc->hw.r_tx1 = V_ATX | V_NTRI;
		HFC_outb(hc, R_TX0, hc->hw.r_tx0);
		HFC_outb(hc, R_TX1, hc->hw.r_tx1);
		HFC_outb(hc, R_TX_FR0, 0x00);
		HFC_outb(hc, R_TX_FR1, 0xf8);

		अगर (test_bit(HFC_CFG_CRC4, &hc->chan[hc->dnum[0]].cfg))
			HFC_outb(hc, R_TX_FR2, V_TX_MF | V_TX_E | V_NEG_E);

		HFC_outb(hc, R_RX_FR0, V_AUTO_RESYNC | V_AUTO_RECO | 0);

		अगर (test_bit(HFC_CFG_CRC4, &hc->chan[hc->dnum[0]].cfg))
			HFC_outb(hc, R_RX_FR1, V_RX_MF | V_RX_MF_SYNC);

		अगर (dch->dev.D.protocol == ISDN_P_NT_E1) अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: E1 port is NT-mode\n",
				       __func__);
			r_e1_wr_sta = 0; /* G0 */
			hc->e1_अ_लोlock = 0;
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: E1 port is TE-mode\n",
				       __func__);
			r_e1_wr_sta = 0; /* F0 */
			hc->e1_अ_लोlock = 1;
		पूर्ण
		अगर (test_bit(HFC_CHIP_RX_SYNC, &hc->chip))
			HFC_outb(hc, R_SYNC_OUT, V_SYNC_E1_RX);
		अन्यथा
			HFC_outb(hc, R_SYNC_OUT, 0);
		अगर (test_bit(HFC_CHIP_E1CLOCK_GET, &hc->chip))
			hc->e1_अ_लोlock = 1;
		अगर (test_bit(HFC_CHIP_E1CLOCK_PUT, &hc->chip))
			hc->e1_अ_लोlock = 0;
		अगर (test_bit(HFC_CHIP_PCM_SLAVE, &hc->chip)) अणु
			/* SLAVE (घड़ी master) */
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: E1 port is clock master "
				       "(clock from PCM)\n", __func__);
			HFC_outb(hc, R_SYNC_CTRL, V_EXT_CLK_SYNC | V_PCM_SYNC);
		पूर्ण अन्यथा अणु
			अगर (hc->e1_अ_लोlock) अणु
				/* MASTER (घड़ी slave) */
				अगर (debug & DEBUG_HFCMULTI_INIT)
					prपूर्णांकk(KERN_DEBUG
					       "%s: E1 port is clock slave "
					       "(clock to PCM)\n", __func__);
				HFC_outb(hc, R_SYNC_CTRL, V_SYNC_OFFS);
			पूर्ण अन्यथा अणु
				/* MASTER (घड़ी master) */
				अगर (debug & DEBUG_HFCMULTI_INIT)
					prपूर्णांकk(KERN_DEBUG "%s: E1 port is "
					       "clock master "
					       "(clock from QUARTZ)\n",
					       __func__);
				HFC_outb(hc, R_SYNC_CTRL, V_EXT_CLK_SYNC |
					 V_PCM_SYNC | V_JATT_OFF);
				HFC_outb(hc, R_SYNC_OUT, 0);
			पूर्ण
		पूर्ण
		HFC_outb(hc, R_JATT_ATT, 0x9c); /* unकरोc रेजिस्टर */
		HFC_outb(hc, R_PWM_MD, V_PWM0_MD);
		HFC_outb(hc, R_PWM0, 0x50);
		HFC_outb(hc, R_PWM1, 0xff);
		/* state machine setup */
		HFC_outb(hc, R_E1_WR_STA, r_e1_wr_sta | V_E1_LD_STA);
		udelay(6); /* रुको at least 5,21us */
		HFC_outb(hc, R_E1_WR_STA, r_e1_wr_sta);
		अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			hc->syncronized = 0;
			plxsd_checksync(hc, 0);
		पूर्ण
	पूर्ण
	अगर (hc->ctype != HFC_TYPE_E1) अणु
		/* ST */
		hc->chan[i].slot_tx = -1;
		hc->chan[i].slot_rx = -1;
		hc->chan[i].conf = -1;
		mode_hfcmulti(hc, i, dch->dev.D.protocol, -1, 0, -1, 0);
		समयr_setup(&dch->समयr, hfcmulti_dbusy_समयr, 0);
		hc->chan[i - 2].slot_tx = -1;
		hc->chan[i - 2].slot_rx = -1;
		hc->chan[i - 2].conf = -1;
		mode_hfcmulti(hc, i - 2, ISDN_P_NONE, -1, 0, -1, 0);
		hc->chan[i - 1].slot_tx = -1;
		hc->chan[i - 1].slot_rx = -1;
		hc->chan[i - 1].conf = -1;
		mode_hfcmulti(hc, i - 1, ISDN_P_NONE, -1, 0, -1, 0);
		/* select पूर्णांकerface */
		HFC_outb(hc, R_ST_SEL, pt);
		/* unकरोcumented: delay after R_ST_SEL */
		udelay(1);
		अगर (dch->dev.D.protocol == ISDN_P_NT_S0) अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: ST port %d is NT-mode\n",
				       __func__, pt);
			/* घड़ी delay */
			HFC_outb(hc, A_ST_CLK_DLY, घड़ीdelay_nt);
			a_st_wr_state = 1; /* G1 */
			hc->hw.a_st_ctrl0[pt] = V_ST_MD;
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: ST port %d is TE-mode\n",
				       __func__, pt);
			/* घड़ी delay */
			HFC_outb(hc, A_ST_CLK_DLY, घड़ीdelay_te);
			a_st_wr_state = 2; /* F2 */
			hc->hw.a_st_ctrl0[pt] = 0;
		पूर्ण
		अगर (!test_bit(HFC_CFG_NONCAP_TX, &hc->chan[i].cfg))
			hc->hw.a_st_ctrl0[pt] |= V_TX_LI;
		अगर (hc->ctype == HFC_TYPE_XHFC) अणु
			hc->hw.a_st_ctrl0[pt] |= 0x40 /* V_ST_PU_CTRL */;
			HFC_outb(hc, 0x35 /* A_ST_CTRL3 */,
				 0x7c << 1 /* V_ST_PULSE */);
		पूर्ण
		/* line setup */
		HFC_outb(hc, A_ST_CTRL0,  hc->hw.a_st_ctrl0[pt]);
		/* disable E-channel */
		अगर ((dch->dev.D.protocol == ISDN_P_NT_S0) ||
		    test_bit(HFC_CFG_DIS_ECHANNEL, &hc->chan[i].cfg))
			HFC_outb(hc, A_ST_CTRL1, V_E_IGNO);
		अन्यथा
			HFC_outb(hc, A_ST_CTRL1, 0);
		/* enable B-channel receive */
		HFC_outb(hc, A_ST_CTRL2,  V_B1_RX_EN | V_B2_RX_EN);
		/* state machine setup */
		HFC_outb(hc, A_ST_WR_STATE, a_st_wr_state | V_ST_LD_STA);
		udelay(6); /* रुको at least 5,21us */
		HFC_outb(hc, A_ST_WR_STATE, a_st_wr_state);
		hc->hw.r_sci_msk |= 1 << pt;
		/* state machine पूर्णांकerrupts */
		HFC_outb(hc, R_SCI_MSK, hc->hw.r_sci_msk);
		/* unset sync on port */
		अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			hc->syncronized &=
				~(1 << hc->chan[dch->slot].port);
			plxsd_checksync(hc, 0);
		पूर्ण
	पूर्ण
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk("%s: done\n", __func__);
पूर्ण


अटल पूर्णांक
खोलो_dchannel(काष्ठा hfc_multi *hc, काष्ठा dchannel *dch,
	      काष्ठा channel_req *rq)
अणु
	पूर्णांक	err = 0;
	u_दीर्घ	flags;

	अगर (debug & DEBUG_HW_OPEN)
		prपूर्णांकk(KERN_DEBUG "%s: dev(%d) open from %p\n", __func__,
		       dch->dev.id, __builtin_वापस_address(0));
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	अगर ((dch->dev.D.protocol != ISDN_P_NONE) &&
	    (dch->dev.D.protocol != rq->protocol)) अणु
		अगर (debug & DEBUG_HFCMULTI_MODE)
			prपूर्णांकk(KERN_DEBUG "%s: change protocol %x to %x\n",
			       __func__, dch->dev.D.protocol, rq->protocol);
	पूर्ण
	अगर ((dch->dev.D.protocol == ISDN_P_TE_S0) &&
	    (rq->protocol != ISDN_P_TE_S0))
		l1_event(dch->l1, CLOSE_CHANNEL);
	अगर (dch->dev.D.protocol != rq->protocol) अणु
		अगर (rq->protocol == ISDN_P_TE_S0) अणु
			err = create_l1(dch, hfcm_l1callback);
			अगर (err)
				वापस err;
		पूर्ण
		dch->dev.D.protocol = rq->protocol;
		spin_lock_irqsave(&hc->lock, flags);
		hfcmulti_iniपंचांगode(dch);
		spin_unlock_irqrestore(&hc->lock, flags);
	पूर्ण
	अगर (test_bit(FLG_ACTIVE, &dch->Flags))
		_queue_data(&dch->dev.D, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
	rq->ch = &dch->dev.D;
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s:cannot get module\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा hfc_multi *hc, काष्ठा dchannel *dch,
	      काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel	*bch;
	पूर्णांक		ch;

	अगर (!test_channelmap(rq->adr.channel, dch->dev.channelmap))
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	अगर (hc->ctype == HFC_TYPE_E1)
		ch = rq->adr.channel;
	अन्यथा
		ch = (rq->adr.channel - 1) + (dch->slot - 2);
	bch = hc->chan[ch].bch;
	अगर (!bch) अणु
		prपूर्णांकk(KERN_ERR "%s:internal error ch %d has no bch\n",
		       __func__, ch);
		वापस -EINVAL;
	पूर्ण
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	hc->chan[ch].rx_off = 0;
	rq->ch = &bch->ch;
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s:cannot get module\n", __func__);
	वापस 0;
पूर्ण

/*
 * device control function
 */
अटल पूर्णांक
channel_dctrl(काष्ठा dchannel *dch, काष्ठा mISDN_ctrl_req *cq)
अणु
	काष्ठा hfc_multi	*hc = dch->hw;
	पूर्णांक	ret = 0;
	पूर्णांक	wd_mode, wd_cnt;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_HFC_OP | MISDN_CTRL_L1_TIMER3;
		अवरोध;
	हाल MISDN_CTRL_HFC_WD_INIT: /* init the watchकरोg */
		wd_cnt = cq->p1 & 0xf;
		wd_mode = !!(cq->p1 >> 4);
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: MISDN_CTRL_HFC_WD_INIT mode %s"
			       ", counter 0x%x\n", __func__,
			       wd_mode ? "AUTO" : "MANUAL", wd_cnt);
		/* set the watchकरोg समयr */
		HFC_outb(hc, R_TI_WD, poll_समयr | (wd_cnt << 4));
		hc->hw.r_bert_wd_md = (wd_mode ? V_AUTO_WD_RES : 0);
		अगर (hc->ctype == HFC_TYPE_XHFC)
			hc->hw.r_bert_wd_md |= 0x40 /* V_WD_EN */;
		/* init the watchकरोg रेजिस्टर and reset the counter */
		HFC_outb(hc, R_BERT_WD_MD, hc->hw.r_bert_wd_md | V_WD_RES);
		अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			/* enable the watchकरोg output क्रम Speech-Design */
			HFC_outb(hc, R_GPIO_SEL,  V_GPIO_SEL7);
			HFC_outb(hc, R_GPIO_EN1,  V_GPIO_EN15);
			HFC_outb(hc, R_GPIO_OUT1, 0);
			HFC_outb(hc, R_GPIO_OUT1, V_GPIO_OUT15);
		पूर्ण
		अवरोध;
	हाल MISDN_CTRL_HFC_WD_RESET: /* reset the watchकरोg counter */
		अगर (debug & DEBUG_HFCMULTI_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: MISDN_CTRL_HFC_WD_RESET\n",
			       __func__);
		HFC_outb(hc, R_BERT_WD_MD, hc->hw.r_bert_wd_md | V_WD_RES);
		अवरोध;
	हाल MISDN_CTRL_L1_TIMER3:
		ret = l1_event(dch->l1, HW_TIMER3_VALUE | (cq->p1 & 0xff));
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
hfcm_dctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा hfc_multi	*hc = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;
	u_दीर्घ			flags;

	अगर (dch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		चयन (rq->protocol) अणु
		हाल ISDN_P_TE_S0:
		हाल ISDN_P_NT_S0:
			अगर (hc->ctype == HFC_TYPE_E1) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			err = खोलो_dchannel(hc, dch, rq); /* locked there */
			अवरोध;
		हाल ISDN_P_TE_E1:
		हाल ISDN_P_NT_E1:
			अगर (hc->ctype != HFC_TYPE_E1) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			err = खोलो_dchannel(hc, dch, rq); /* locked there */
			अवरोध;
		शेष:
			spin_lock_irqsave(&hc->lock, flags);
			err = खोलो_bchannel(hc, dch, rq);
			spin_unlock_irqrestore(&hc->lock, flags);
		पूर्ण
		अवरोध;
	हाल CLOSE_CHANNEL:
		अगर (debug & DEBUG_HW_OPEN)
			prपूर्णांकk(KERN_DEBUG "%s: dev(%d) close from %p\n",
			       __func__, dch->dev.id,
			       __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		spin_lock_irqsave(&hc->lock, flags);
		err = channel_dctrl(dch, arg);
		spin_unlock_irqrestore(&hc->lock, flags);
		अवरोध;
	शेष:
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
घड़ीctl(व्योम *priv, पूर्णांक enable)
अणु
	काष्ठा hfc_multi *hc = priv;

	hc->iघड़ी_on = enable;
	वापस 0;
पूर्ण

/*
 * initialize the card
 */

/*
 * start समयr irq, रुको some समय and check अगर we have पूर्णांकerrupts.
 * अगर not, reset chip and try again.
 */
अटल पूर्णांक
init_card(काष्ठा hfc_multi *hc)
अणु
	पूर्णांक	err = -EIO;
	u_दीर्घ	flags;
	व्योम	__iomem *plx_acc;
	u_दीर्घ	plx_flags;

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: entered\n", __func__);

	spin_lock_irqsave(&hc->lock, flags);
	/* set पूर्णांकerrupts but leave global पूर्णांकerrupt disabled */
	hc->hw.r_irq_ctrl = V_FIFO_IRQ;
	disable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);

	अगर (request_irq(hc->irq, hfcmulti_पूर्णांकerrupt, IRQF_SHARED,
			"HFC-multi", hc)) अणु
		prपूर्णांकk(KERN_WARNING "mISDN: Could not get interrupt %d.\n",
		       hc->irq);
		hc->irq = 0;
		वापस -EIO;
	पूर्ण

	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
		spin_lock_irqsave(&plx_lock, plx_flags);
		plx_acc = hc->plx_membase + PLX_INTCSR;
		ग_लिखोw((PLX_INTCSR_PCIINT_ENABLE | PLX_INTCSR_LINTI1_ENABLE),
		       plx_acc); /* enable PCI & LINT1 irq */
		spin_unlock_irqrestore(&plx_lock, plx_flags);
	पूर्ण

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: IRQ %d count %d\n",
		       __func__, hc->irq, hc->irqcnt);
	err = init_chip(hc);
	अगर (err)
		जाओ error;
	/*
	 * Finally enable IRQ output
	 * this is only allowed, अगर an IRQ routine is alपढ़ोy
	 * established क्रम this HFC, so करोn't करो that earlier
	 */
	spin_lock_irqsave(&hc->lock, flags);
	enable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);
	/* prपूर्णांकk(KERN_DEBUG "no master irq set!!!\n"); */
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_समयout((100 * HZ) / 1000); /* Timeout 100ms */
	/* turn IRQ off until chip is completely initialized */
	spin_lock_irqsave(&hc->lock, flags);
	disable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: IRQ %d count %d\n",
		       __func__, hc->irq, hc->irqcnt);
	अगर (hc->irqcnt) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: done\n", __func__);

		वापस 0;
	पूर्ण
	अगर (test_bit(HFC_CHIP_PCM_SLAVE, &hc->chip)) अणु
		prपूर्णांकk(KERN_INFO "ignoring missing interrupts\n");
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "HFC PCI: IRQ(%d) getting no interrupts during init.\n",
	       hc->irq);

	err = -EIO;

error:
	अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
		spin_lock_irqsave(&plx_lock, plx_flags);
		plx_acc = hc->plx_membase + PLX_INTCSR;
		ग_लिखोw(0x00, plx_acc); /*disable IRQs*/
		spin_unlock_irqrestore(&plx_lock, plx_flags);
	पूर्ण

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: free irq %d\n", __func__, hc->irq);
	अगर (hc->irq) अणु
		मुक्त_irq(hc->irq, hc);
		hc->irq = 0;
	पूर्ण

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: done (err=%d)\n", __func__, err);
	वापस err;
पूर्ण

/*
 * find pci device and set it up
 */

अटल पूर्णांक
setup_pci(काष्ठा hfc_multi *hc, काष्ठा pci_dev *pdev,
	  स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा hm_map	*m = (काष्ठा hm_map *)ent->driver_data;

	prपूर्णांकk(KERN_INFO
	       "HFC-multi: card manufacturer: '%s' card name: '%s' clock: %s\n",
	       m->venकरोr_name, m->card_name, m->घड़ी2 ? "double" : "normal");

	hc->pci_dev = pdev;
	अगर (m->घड़ी2)
		test_and_set_bit(HFC_CHIP_CLOCK2, &hc->chip);

	अगर (ent->venकरोr == PCI_VENDOR_ID_DIGIUM &&
	    ent->device == PCI_DEVICE_ID_DIGIUM_HFC4S) अणु
		test_and_set_bit(HFC_CHIP_B410P, &hc->chip);
		test_and_set_bit(HFC_CHIP_PCM_MASTER, &hc->chip);
		test_and_clear_bit(HFC_CHIP_PCM_SLAVE, &hc->chip);
		hc->slots = 32;
	पूर्ण

	अगर (hc->pci_dev->irq <= 0) अणु
		prपूर्णांकk(KERN_WARNING "HFC-multi: No IRQ for PCI card found.\n");
		वापस -EIO;
	पूर्ण
	अगर (pci_enable_device(hc->pci_dev)) अणु
		prपूर्णांकk(KERN_WARNING "HFC-multi: Error enabling PCI card.\n");
		वापस -EIO;
	पूर्ण
	hc->leds = m->leds;
	hc->ledstate = 0xAFFEAFFE;
	hc->opticalsupport = m->opticalsupport;

	hc->pci_iobase = 0;
	hc->pci_membase = शून्य;
	hc->plx_membase = शून्य;

	/* set memory access methods */
	अगर (m->io_mode) /* use mode from card config */
		hc->io_mode = m->io_mode;
	चयन (hc->io_mode) अणु
	हाल HFC_IO_MODE_PLXSD:
		test_and_set_bit(HFC_CHIP_PLXSD, &hc->chip);
		hc->slots = 128; /* required */
		hc->HFC_outb = HFC_outb_pcimem;
		hc->HFC_inb = HFC_inb_pcimem;
		hc->HFC_inw = HFC_inw_pcimem;
		hc->HFC_रुको = HFC_रुको_pcimem;
		hc->पढ़ो_fअगरo = पढ़ो_fअगरo_pcimem;
		hc->ग_लिखो_fअगरo = ग_लिखो_fअगरo_pcimem;
		hc->plx_origmembase =  hc->pci_dev->resource[0].start;
		/* MEMBASE 1 is PLX PCI Bridge */

		अगर (!hc->plx_origmembase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: No IO-Memory for PCI PLX bridge found\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण

		hc->plx_membase = ioremap(hc->plx_origmembase, 0x80);
		अगर (!hc->plx_membase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: failed to remap plx address space. "
			       "(internal error)\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण
		prपूर्णांकk(KERN_INFO
		       "HFC-multi: plx_membase:%#lx plx_origmembase:%#lx\n",
		       (u_दीर्घ)hc->plx_membase, hc->plx_origmembase);

		hc->pci_origmembase =  hc->pci_dev->resource[2].start;
		/* MEMBASE 1 is PLX PCI Bridge */
		अगर (!hc->pci_origmembase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: No IO-Memory for PCI card found\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण

		hc->pci_membase = ioremap(hc->pci_origmembase, 0x400);
		अगर (!hc->pci_membase) अणु
			prपूर्णांकk(KERN_WARNING "HFC-multi: failed to remap io "
			       "address space. (internal error)\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण

		prपूर्णांकk(KERN_INFO
		       "card %d: defined at MEMBASE %#lx (%#lx) IRQ %d HZ %d "
		       "leds-type %d\n",
		       hc->id, (u_दीर्घ)hc->pci_membase, hc->pci_origmembase,
		       hc->pci_dev->irq, HZ, hc->leds);
		pci_ग_लिखो_config_word(hc->pci_dev, PCI_COMMAND, PCI_ENA_MEMIO);
		अवरोध;
	हाल HFC_IO_MODE_PCIMEM:
		hc->HFC_outb = HFC_outb_pcimem;
		hc->HFC_inb = HFC_inb_pcimem;
		hc->HFC_inw = HFC_inw_pcimem;
		hc->HFC_रुको = HFC_रुको_pcimem;
		hc->पढ़ो_fअगरo = पढ़ो_fअगरo_pcimem;
		hc->ग_लिखो_fअगरo = ग_लिखो_fअगरo_pcimem;
		hc->pci_origmembase = hc->pci_dev->resource[1].start;
		अगर (!hc->pci_origmembase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: No IO-Memory for PCI card found\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण

		hc->pci_membase = ioremap(hc->pci_origmembase, 256);
		अगर (!hc->pci_membase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: failed to remap io address space. "
			       "(internal error)\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण
		prपूर्णांकk(KERN_INFO "card %d: defined at MEMBASE %#lx (%#lx) IRQ "
		       "%d HZ %d leds-type %d\n", hc->id, (u_दीर्घ)hc->pci_membase,
		       hc->pci_origmembase, hc->pci_dev->irq, HZ, hc->leds);
		pci_ग_लिखो_config_word(hc->pci_dev, PCI_COMMAND, PCI_ENA_MEMIO);
		अवरोध;
	हाल HFC_IO_MODE_REGIO:
		hc->HFC_outb = HFC_outb_regio;
		hc->HFC_inb = HFC_inb_regio;
		hc->HFC_inw = HFC_inw_regio;
		hc->HFC_रुको = HFC_रुको_regio;
		hc->पढ़ो_fअगरo = पढ़ो_fअगरo_regio;
		hc->ग_लिखो_fअगरo = ग_लिखो_fअगरo_regio;
		hc->pci_iobase = (u_पूर्णांक) hc->pci_dev->resource[0].start;
		अगर (!hc->pci_iobase) अणु
			prपूर्णांकk(KERN_WARNING
			       "HFC-multi: No IO for PCI card found\n");
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण

		अगर (!request_region(hc->pci_iobase, 8, "hfcmulti")) अणु
			prपूर्णांकk(KERN_WARNING "HFC-multi: failed to request "
			       "address space at 0x%08lx (internal error)\n",
			       hc->pci_iobase);
			pci_disable_device(hc->pci_dev);
			वापस -EIO;
		पूर्ण

		prपूर्णांकk(KERN_INFO
		       "%s %s: defined at IOBASE %#x IRQ %d HZ %d leds-type %d\n",
		       m->venकरोr_name, m->card_name, (u_पूर्णांक) hc->pci_iobase,
		       hc->pci_dev->irq, HZ, hc->leds);
		pci_ग_लिखो_config_word(hc->pci_dev, PCI_COMMAND, PCI_ENA_REGIO);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "HFC-multi: Invalid IO mode.\n");
		pci_disable_device(hc->pci_dev);
		वापस -EIO;
	पूर्ण

	pci_set_drvdata(hc->pci_dev, hc);

	/* At this poपूर्णांक the needed PCI config is करोne */
	/* fअगरos are still not enabled */
	वापस 0;
पूर्ण


/*
 * हटाओ port
 */

अटल व्योम
release_port(काष्ठा hfc_multi *hc, काष्ठा dchannel *dch)
अणु
	पूर्णांक	pt, ci, i = 0;
	u_दीर्घ	flags;
	काष्ठा bchannel *pb;

	ci = dch->slot;
	pt = hc->chan[ci].port;

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: entered for port %d\n",
		       __func__, pt + 1);

	अगर (pt >= hc->ports) अणु
		prपूर्णांकk(KERN_WARNING "%s: ERROR port out of range (%d).\n",
		       __func__, pt + 1);
		वापस;
	पूर्ण

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: releasing port=%d\n",
		       __func__, pt + 1);

	अगर (dch->dev.D.protocol == ISDN_P_TE_S0)
		l1_event(dch->l1, CLOSE_CHANNEL);

	hc->chan[ci].dch = शून्य;

	अगर (hc->created[pt]) अणु
		hc->created[pt] = 0;
		mISDN_unरेजिस्टर_device(&dch->dev);
	पूर्ण

	spin_lock_irqsave(&hc->lock, flags);

	अगर (dch->समयr.function) अणु
		del_समयr(&dch->समयr);
		dch->समयr.function = शून्य;
	पूर्ण

	अगर (hc->ctype == HFC_TYPE_E1) अणु /* E1 */
		/* हटाओ sync */
		अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			hc->syncronized = 0;
			plxsd_checksync(hc, 1);
		पूर्ण
		/* मुक्त channels */
		क्रम (i = 0; i <= 31; i++) अणु
			अगर (!((1 << i) & hc->bmask[pt])) /* skip unused chan */
				जारी;
			अगर (hc->chan[i].bch) अणु
				अगर (debug & DEBUG_HFCMULTI_INIT)
					prपूर्णांकk(KERN_DEBUG
					       "%s: free port %d channel %d\n",
					       __func__, hc->chan[i].port + 1, i);
				pb = hc->chan[i].bch;
				hc->chan[i].bch = शून्य;
				spin_unlock_irqrestore(&hc->lock, flags);
				mISDN_मुक्तbchannel(pb);
				kमुक्त(pb);
				kमुक्त(hc->chan[i].coeff);
				spin_lock_irqsave(&hc->lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* हटाओ sync */
		अगर (test_bit(HFC_CHIP_PLXSD, &hc->chip)) अणु
			hc->syncronized &=
				~(1 << hc->chan[ci].port);
			plxsd_checksync(hc, 1);
		पूर्ण
		/* मुक्त channels */
		अगर (hc->chan[ci - 2].bch) अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: free port %d channel %d\n",
				       __func__, hc->chan[ci - 2].port + 1,
				       ci - 2);
			pb = hc->chan[ci - 2].bch;
			hc->chan[ci - 2].bch = शून्य;
			spin_unlock_irqrestore(&hc->lock, flags);
			mISDN_मुक्तbchannel(pb);
			kमुक्त(pb);
			kमुक्त(hc->chan[ci - 2].coeff);
			spin_lock_irqsave(&hc->lock, flags);
		पूर्ण
		अगर (hc->chan[ci - 1].bch) अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: free port %d channel %d\n",
				       __func__, hc->chan[ci - 1].port + 1,
				       ci - 1);
			pb = hc->chan[ci - 1].bch;
			hc->chan[ci - 1].bch = शून्य;
			spin_unlock_irqrestore(&hc->lock, flags);
			mISDN_मुक्तbchannel(pb);
			kमुक्त(pb);
			kमुक्त(hc->chan[ci - 1].coeff);
			spin_lock_irqsave(&hc->lock, flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&hc->lock, flags);

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: free port %d channel D(%d)\n", __func__,
			pt+1, ci);
	mISDN_मुक्तdchannel(dch);
	kमुक्त(dch);

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: done!\n", __func__);
पूर्ण

अटल व्योम
release_card(काष्ठा hfc_multi *hc)
अणु
	u_दीर्घ	flags;
	पूर्णांक	ch;

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: release card (%d) entered\n",
		       __func__, hc->id);

	/* unरेजिस्टर घड़ी source */
	अगर (hc->iघड़ी)
		mISDN_unरेजिस्टर_घड़ी(hc->iघड़ी);

	/* disable and मुक्त irq */
	spin_lock_irqsave(&hc->lock, flags);
	disable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);
	udelay(1000);
	अगर (hc->irq) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: free irq %d (hc=%p)\n",
			    __func__, hc->irq, hc);
		मुक्त_irq(hc->irq, hc);
		hc->irq = 0;

	पूर्ण

	/* disable D-channels & B-channels */
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: disable all channels (d and b)\n",
		       __func__);
	क्रम (ch = 0; ch <= 31; ch++) अणु
		अगर (hc->chan[ch].dch)
			release_port(hc, hc->chan[ch].dch);
	पूर्ण

	/* dimm leds */
	अगर (hc->leds)
		hfcmulti_leds(hc);

	/* release hardware */
	release_io_hfcmulti(hc);

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: remove instance from list\n",
		       __func__);
	list_del(&hc->list);

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: delete instance\n", __func__);
	अगर (hc == syncmaster)
		syncmaster = शून्य;
	kमुक्त(hc);
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: card successfully removed\n",
		       __func__);
पूर्ण

अटल व्योम
init_e1_port_hw(काष्ठा hfc_multi *hc, काष्ठा hm_map *m)
अणु
	/* set optical line type */
	अगर (port[Port_cnt] & 0x001) अणु
		अगर (!m->opticalsupport)  अणु
			prपूर्णांकk(KERN_INFO
			       "This board has no optical "
			       "support\n");
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG
				       "%s: PORT set optical "
				       "interfacs: card(%d) "
				       "port(%d)\n",
				       __func__,
				       HFC_cnt + 1, 1);
			test_and_set_bit(HFC_CFG_OPTICAL,
			    &hc->chan[hc->dnum[0]].cfg);
		पूर्ण
	पूर्ण
	/* set LOS report */
	अगर (port[Port_cnt] & 0x004) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PORT set "
			       "LOS report: card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CFG_REPORT_LOS,
		    &hc->chan[hc->dnum[0]].cfg);
	पूर्ण
	/* set AIS report */
	अगर (port[Port_cnt] & 0x008) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PORT set "
			       "AIS report: card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CFG_REPORT_AIS,
		    &hc->chan[hc->dnum[0]].cfg);
	पूर्ण
	/* set SLIP report */
	अगर (port[Port_cnt] & 0x010) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: PORT set SLIP report: "
			       "card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CFG_REPORT_SLIP,
		    &hc->chan[hc->dnum[0]].cfg);
	पूर्ण
	/* set RDI report */
	अगर (port[Port_cnt] & 0x020) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: PORT set RDI report: "
			       "card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CFG_REPORT_RDI,
		    &hc->chan[hc->dnum[0]].cfg);
	पूर्ण
	/* set CRC-4 Mode */
	अगर (!(port[Port_cnt] & 0x100)) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PORT turn on CRC4 report:"
			       " card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CFG_CRC4,
		    &hc->chan[hc->dnum[0]].cfg);
	पूर्ण अन्यथा अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PORT turn off CRC4"
			       " report: card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
	पूर्ण
	/* set क्रमced घड़ी */
	अगर (port[Port_cnt] & 0x0200) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PORT force getting clock from "
			       "E1: card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CHIP_E1CLOCK_GET, &hc->chip);
	पूर्ण अन्यथा
		अगर (port[Port_cnt] & 0x0400) अणु
			अगर (debug & DEBUG_HFCMULTI_INIT)
				prपूर्णांकk(KERN_DEBUG "%s: PORT force putting clock to "
				       "E1: card(%d) port(%d)\n",
				       __func__, HFC_cnt + 1, 1);
			test_and_set_bit(HFC_CHIP_E1CLOCK_PUT, &hc->chip);
		पूर्ण
	/* set JATT PLL */
	अगर (port[Port_cnt] & 0x0800) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: PORT disable JATT PLL on "
			       "E1: card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, 1);
		test_and_set_bit(HFC_CHIP_RX_SYNC, &hc->chip);
	पूर्ण
	/* set elastic jitter buffer */
	अगर (port[Port_cnt] & 0x3000) अणु
		hc->chan[hc->dnum[0]].jitter = (port[Port_cnt]>>12) & 0x3;
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: PORT set elastic "
			       "buffer to %d: card(%d) port(%d)\n",
			    __func__, hc->chan[hc->dnum[0]].jitter,
			       HFC_cnt + 1, 1);
	पूर्ण अन्यथा
		hc->chan[hc->dnum[0]].jitter = 2; /* शेष */
पूर्ण

अटल पूर्णांक
init_e1_port(काष्ठा hfc_multi *hc, काष्ठा hm_map *m, पूर्णांक pt)
अणु
	काष्ठा dchannel	*dch;
	काष्ठा bchannel	*bch;
	पूर्णांक		ch, ret = 0;
	अक्षर		name[MISDN_MAX_IDLEN];
	पूर्णांक		bcount = 0;

	dch = kzalloc(माप(काष्ठा dchannel), GFP_KERNEL);
	अगर (!dch)
		वापस -ENOMEM;
	dch->debug = debug;
	mISDN_initdchannel(dch, MAX_DFRAME_LEN_L1, ph_state_change);
	dch->hw = hc;
	dch->dev.Dprotocols = (1 << ISDN_P_TE_E1) | (1 << ISDN_P_NT_E1);
	dch->dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
	    (1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	dch->dev.D.send = handle_dmsg;
	dch->dev.D.ctrl = hfcm_dctrl;
	dch->slot = hc->dnum[pt];
	hc->chan[hc->dnum[pt]].dch = dch;
	hc->chan[hc->dnum[pt]].port = pt;
	hc->chan[hc->dnum[pt]].nt_समयr = -1;
	क्रम (ch = 1; ch <= 31; ch++) अणु
		अगर (!((1 << ch) & hc->bmask[pt])) /* skip unused channel */
			जारी;
		bch = kzalloc(माप(काष्ठा bchannel), GFP_KERNEL);
		अगर (!bch) अणु
			prपूर्णांकk(KERN_ERR "%s: no memory for bchannel\n",
			    __func__);
			ret = -ENOMEM;
			जाओ मुक्त_chan;
		पूर्ण
		hc->chan[ch].coeff = kzalloc(512, GFP_KERNEL);
		अगर (!hc->chan[ch].coeff) अणु
			prपूर्णांकk(KERN_ERR "%s: no memory for coeffs\n",
			    __func__);
			ret = -ENOMEM;
			kमुक्त(bch);
			जाओ मुक्त_chan;
		पूर्ण
		bch->nr = ch;
		bch->slot = ch;
		bch->debug = debug;
		mISDN_initbchannel(bch, MAX_DATA_MEM, poll >> 1);
		bch->hw = hc;
		bch->ch.send = handle_bmsg;
		bch->ch.ctrl = hfcm_bctrl;
		bch->ch.nr = ch;
		list_add(&bch->ch.list, &dch->dev.bchannels);
		hc->chan[ch].bch = bch;
		hc->chan[ch].port = pt;
		set_channelmap(bch->nr, dch->dev.channelmap);
		bcount++;
	पूर्ण
	dch->dev.nrbchan = bcount;
	अगर (pt == 0)
		init_e1_port_hw(hc, m);
	अगर (hc->ports > 1)
		snम_लिखो(name, MISDN_MAX_IDLEN - 1, "hfc-e1.%d-%d",
				HFC_cnt + 1, pt+1);
	अन्यथा
		snम_लिखो(name, MISDN_MAX_IDLEN - 1, "hfc-e1.%d", HFC_cnt + 1);
	ret = mISDN_रेजिस्टर_device(&dch->dev, &hc->pci_dev->dev, name);
	अगर (ret)
		जाओ मुक्त_chan;
	hc->created[pt] = 1;
	वापस ret;
मुक्त_chan:
	release_port(hc, dch);
	वापस ret;
पूर्ण

अटल पूर्णांक
init_multi_port(काष्ठा hfc_multi *hc, पूर्णांक pt)
अणु
	काष्ठा dchannel	*dch;
	काष्ठा bchannel	*bch;
	पूर्णांक		ch, i, ret = 0;
	अक्षर		name[MISDN_MAX_IDLEN];

	dch = kzalloc(माप(काष्ठा dchannel), GFP_KERNEL);
	अगर (!dch)
		वापस -ENOMEM;
	dch->debug = debug;
	mISDN_initdchannel(dch, MAX_DFRAME_LEN_L1, ph_state_change);
	dch->hw = hc;
	dch->dev.Dprotocols = (1 << ISDN_P_TE_S0) | (1 << ISDN_P_NT_S0);
	dch->dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	dch->dev.D.send = handle_dmsg;
	dch->dev.D.ctrl = hfcm_dctrl;
	dch->dev.nrbchan = 2;
	i = pt << 2;
	dch->slot = i + 2;
	hc->chan[i + 2].dch = dch;
	hc->chan[i + 2].port = pt;
	hc->chan[i + 2].nt_समयr = -1;
	क्रम (ch = 0; ch < dch->dev.nrbchan; ch++) अणु
		bch = kzalloc(माप(काष्ठा bchannel), GFP_KERNEL);
		अगर (!bch) अणु
			prपूर्णांकk(KERN_ERR "%s: no memory for bchannel\n",
			       __func__);
			ret = -ENOMEM;
			जाओ मुक्त_chan;
		पूर्ण
		hc->chan[i + ch].coeff = kzalloc(512, GFP_KERNEL);
		अगर (!hc->chan[i + ch].coeff) अणु
			prपूर्णांकk(KERN_ERR "%s: no memory for coeffs\n",
			       __func__);
			ret = -ENOMEM;
			kमुक्त(bch);
			जाओ मुक्त_chan;
		पूर्ण
		bch->nr = ch + 1;
		bch->slot = i + ch;
		bch->debug = debug;
		mISDN_initbchannel(bch, MAX_DATA_MEM, poll >> 1);
		bch->hw = hc;
		bch->ch.send = handle_bmsg;
		bch->ch.ctrl = hfcm_bctrl;
		bch->ch.nr = ch + 1;
		list_add(&bch->ch.list, &dch->dev.bchannels);
		hc->chan[i + ch].bch = bch;
		hc->chan[i + ch].port = pt;
		set_channelmap(bch->nr, dch->dev.channelmap);
	पूर्ण
	/* set master घड़ी */
	अगर (port[Port_cnt] & 0x001) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: PROTOCOL set master clock: "
			       "card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, pt + 1);
		अगर (dch->dev.D.protocol != ISDN_P_TE_S0) अणु
			prपूर्णांकk(KERN_ERR "Error: Master clock "
			       "for port(%d) of card(%d) is only"
			       " possible with TE-mode\n",
			       pt + 1, HFC_cnt + 1);
			ret = -EINVAL;
			जाओ मुक्त_chan;
		पूर्ण
		अगर (hc->masterclk >= 0) अणु
			prपूर्णांकk(KERN_ERR "Error: Master clock "
			       "for port(%d) of card(%d) already "
			       "defined for port(%d)\n",
			       pt + 1, HFC_cnt + 1, hc->masterclk + 1);
			ret = -EINVAL;
			जाओ मुक्त_chan;
		पूर्ण
		hc->masterclk = pt;
	पूर्ण
	/* set transmitter line to non capacitive */
	अगर (port[Port_cnt] & 0x002) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: PROTOCOL set non capacitive "
			       "transmitter: card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, pt + 1);
		test_and_set_bit(HFC_CFG_NONCAP_TX,
				 &hc->chan[i + 2].cfg);
	पूर्ण
	/* disable E-channel */
	अगर (port[Port_cnt] & 0x004) अणु
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			       "%s: PROTOCOL disable E-channel: "
			       "card(%d) port(%d)\n",
			       __func__, HFC_cnt + 1, pt + 1);
		test_and_set_bit(HFC_CFG_DIS_ECHANNEL,
				 &hc->chan[i + 2].cfg);
	पूर्ण
	अगर (hc->ctype == HFC_TYPE_XHFC) अणु
		snम_लिखो(name, MISDN_MAX_IDLEN - 1, "xhfc.%d-%d",
			 HFC_cnt + 1, pt + 1);
		ret = mISDN_रेजिस्टर_device(&dch->dev, शून्य, name);
	पूर्ण अन्यथा अणु
		snम_लिखो(name, MISDN_MAX_IDLEN - 1, "hfc-%ds.%d-%d",
			 hc->ctype, HFC_cnt + 1, pt + 1);
		ret = mISDN_रेजिस्टर_device(&dch->dev, &hc->pci_dev->dev, name);
	पूर्ण
	अगर (ret)
		जाओ मुक्त_chan;
	hc->created[pt] = 1;
	वापस ret;
मुक्त_chan:
	release_port(hc, dch);
	वापस ret;
पूर्ण

अटल पूर्णांक
hfcmulti_init(काष्ठा hm_map *m, काष्ठा pci_dev *pdev,
	      स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक		ret_err = 0;
	पूर्णांक		pt;
	काष्ठा hfc_multi	*hc;
	u_दीर्घ		flags;
	u_अक्षर		dips = 0, pmj = 0; /* dip settings, port mode Jumpers */
	पूर्णांक		i, ch;
	u_पूर्णांक		maskcheck;

	अगर (HFC_cnt >= MAX_CARDS) अणु
		prपूर्णांकk(KERN_ERR "too many cards (max=%d).\n",
		       MAX_CARDS);
		वापस -EINVAL;
	पूर्ण
	अगर ((type[HFC_cnt] & 0xff) && (type[HFC_cnt] & 0xff) != m->type) अणु
		prपूर्णांकk(KERN_WARNING "HFC-MULTI: Card '%s:%s' type %d found but "
		       "type[%d] %d was supplied as module parameter\n",
		       m->venकरोr_name, m->card_name, m->type, HFC_cnt,
		       type[HFC_cnt] & 0xff);
		prपूर्णांकk(KERN_WARNING "HFC-MULTI: Load module without parameters "
		       "first, to see cards and their types.");
		वापस -EINVAL;
	पूर्ण
	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: Registering %s:%s chip type %d (0x%x)\n",
		       __func__, m->venकरोr_name, m->card_name, m->type,
		       type[HFC_cnt]);

	/* allocate card+fअगरo काष्ठाure */
	hc = kzalloc(माप(काष्ठा hfc_multi), GFP_KERNEL);
	अगर (!hc) अणु
		prपूर्णांकk(KERN_ERR "No kmem for HFC-Multi card\n");
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&hc->lock);
	hc->mtyp = m;
	hc->ctype =  m->type;
	hc->ports = m->ports;
	hc->id = HFC_cnt;
	hc->pcm = pcm[HFC_cnt];
	hc->io_mode = iomode[HFC_cnt];
	अगर (hc->ctype == HFC_TYPE_E1 && dmask[E1_cnt]) अणु
		/* fragment card */
		pt = 0;
		maskcheck = 0;
		क्रम (ch = 0; ch <= 31; ch++) अणु
			अगर (!((1 << ch) & dmask[E1_cnt]))
				जारी;
			hc->dnum[pt] = ch;
			hc->bmask[pt] = bmask[bmask_cnt++];
			अगर ((maskcheck & hc->bmask[pt])
			 || (dmask[E1_cnt] & hc->bmask[pt])) अणु
				prपूर्णांकk(KERN_INFO
				       "HFC-E1 #%d has overlapping B-channels on fragment #%d\n",
				       E1_cnt + 1, pt);
				kमुक्त(hc);
				वापस -EINVAL;
			पूर्ण
			maskcheck |= hc->bmask[pt];
			prपूर्णांकk(KERN_INFO
			       "HFC-E1 #%d uses D-channel on slot %d and a B-channel map of 0x%08x\n",
				E1_cnt + 1, ch, hc->bmask[pt]);
			pt++;
		पूर्ण
		hc->ports = pt;
	पूर्ण
	अगर (hc->ctype == HFC_TYPE_E1 && !dmask[E1_cnt]) अणु
		/* शेष card layout */
		hc->dnum[0] = 16;
		hc->bmask[0] = 0xfffefffe;
		hc->ports = 1;
	पूर्ण

	/* set chip specअगरic features */
	hc->masterclk = -1;
	अगर (type[HFC_cnt] & 0x100) अणु
		test_and_set_bit(HFC_CHIP_ULAW, &hc->chip);
		hc->silence = 0xff; /* ulaw silence */
	पूर्ण अन्यथा
		hc->silence = 0x2a; /* alaw silence */
	अगर ((poll >> 1) > माप(hc->silence_data)) अणु
		prपूर्णांकk(KERN_ERR "HFCMULTI error: silence_data too small, "
		       "please fix\n");
		kमुक्त(hc);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < (poll >> 1); i++)
		hc->silence_data[i] = hc->silence;

	अगर (hc->ctype != HFC_TYPE_XHFC) अणु
		अगर (!(type[HFC_cnt] & 0x200))
			test_and_set_bit(HFC_CHIP_DTMF, &hc->chip);
		test_and_set_bit(HFC_CHIP_CONF, &hc->chip);
	पूर्ण

	अगर (type[HFC_cnt] & 0x800)
		test_and_set_bit(HFC_CHIP_PCM_SLAVE, &hc->chip);
	अगर (type[HFC_cnt] & 0x1000) अणु
		test_and_set_bit(HFC_CHIP_PCM_MASTER, &hc->chip);
		test_and_clear_bit(HFC_CHIP_PCM_SLAVE, &hc->chip);
	पूर्ण
	अगर (type[HFC_cnt] & 0x4000)
		test_and_set_bit(HFC_CHIP_EXRAM_128, &hc->chip);
	अगर (type[HFC_cnt] & 0x8000)
		test_and_set_bit(HFC_CHIP_EXRAM_512, &hc->chip);
	hc->slots = 32;
	अगर (type[HFC_cnt] & 0x10000)
		hc->slots = 64;
	अगर (type[HFC_cnt] & 0x20000)
		hc->slots = 128;
	अगर (type[HFC_cnt] & 0x80000) अणु
		test_and_set_bit(HFC_CHIP_WATCHDOG, &hc->chip);
		hc->wdcount = 0;
		hc->wdbyte = V_GPIO_OUT2;
		prपूर्णांकk(KERN_NOTICE "Watchdog enabled\n");
	पूर्ण

	अगर (pdev && ent)
		/* setup pci, hc->slots may change due to PLXSD */
		ret_err = setup_pci(hc, pdev, ent);
	अन्यथा
#अगर_घोषित CONFIG_MISDN_HFCMULTI_8xx
		ret_err = setup_embedded(hc, m);
#अन्यथा
	अणु
		prपूर्णांकk(KERN_WARNING "Embedded IO Mode not selected\n");
		ret_err = -EIO;
	पूर्ण
#पूर्ण_अगर
	अगर (ret_err) अणु
		अगर (hc == syncmaster)
			syncmaster = शून्य;
		kमुक्त(hc);
		वापस ret_err;
	पूर्ण

	hc->HFC_outb_nodebug = hc->HFC_outb;
	hc->HFC_inb_nodebug = hc->HFC_inb;
	hc->HFC_inw_nodebug = hc->HFC_inw;
	hc->HFC_रुको_nodebug = hc->HFC_रुको;
#अगर_घोषित HFC_REGISTER_DEBUG
	hc->HFC_outb = HFC_outb_debug;
	hc->HFC_inb = HFC_inb_debug;
	hc->HFC_inw = HFC_inw_debug;
	hc->HFC_रुको = HFC_रुको_debug;
#पूर्ण_अगर
	/* create channels */
	क्रम (pt = 0; pt < hc->ports; pt++) अणु
		अगर (Port_cnt >= MAX_PORTS) अणु
			prपूर्णांकk(KERN_ERR "too many ports (max=%d).\n",
			       MAX_PORTS);
			ret_err = -EINVAL;
			जाओ मुक्त_card;
		पूर्ण
		अगर (hc->ctype == HFC_TYPE_E1)
			ret_err = init_e1_port(hc, m, pt);
		अन्यथा
			ret_err = init_multi_port(hc, pt);
		अगर (debug & DEBUG_HFCMULTI_INIT)
			prपूर्णांकk(KERN_DEBUG
			    "%s: Registering D-channel, card(%d) port(%d) "
			       "result %d\n",
			    __func__, HFC_cnt + 1, pt + 1, ret_err);

		अगर (ret_err) अणु
			जबतक (pt) अणु /* release alपढ़ोy रेजिस्टरed ports */
				pt--;
				अगर (hc->ctype == HFC_TYPE_E1)
					release_port(hc,
						hc->chan[hc->dnum[pt]].dch);
				अन्यथा
					release_port(hc,
						hc->chan[(pt << 2) + 2].dch);
			पूर्ण
			जाओ मुक्त_card;
		पूर्ण
		अगर (hc->ctype != HFC_TYPE_E1)
			Port_cnt++; /* क्रम each S0 port */
	पूर्ण
	अगर (hc->ctype == HFC_TYPE_E1) अणु
		Port_cnt++; /* क्रम each E1 port */
		E1_cnt++;
	पूर्ण

	/* disp चयनes */
	चयन (m->dip_type) अणु
	हाल DIP_4S:
		/*
		 * Get DIP setting क्रम beroNet 1S/2S/4S cards
		 * DIP Setting: (collect GPIO 13/14/15 (R_GPIO_IN1) +
		 * GPI 19/23 (R_GPI_IN2))
		 */
		dips = ((~HFC_inb(hc, R_GPIO_IN1) & 0xE0) >> 5) |
			((~HFC_inb(hc, R_GPI_IN2) & 0x80) >> 3) |
			(~HFC_inb(hc, R_GPI_IN2) & 0x08);

		/* Port mode (TE/NT) jumpers */
		pmj = ((HFC_inb(hc, R_GPI_IN3) >> 4)  & 0xf);

		अगर (test_bit(HFC_CHIP_B410P, &hc->chip))
			pmj = ~pmj & 0xf;

		prपूर्णांकk(KERN_INFO "%s: %s DIPs(0x%x) jumpers(0x%x)\n",
		       m->venकरोr_name, m->card_name, dips, pmj);
		अवरोध;
	हाल DIP_8S:
		/*
		 * Get DIP Setting क्रम beroNet 8S0+ cards
		 * Enable PCI auxbridge function
		 */
		HFC_outb(hc, R_BRG_PCM_CFG, 1 | V_PCM_CLK);
		/* prepare access to auxport */
		outw(0x4000, hc->pci_iobase + 4);
		/*
		 * some dummy पढ़ोs are required to
		 * पढ़ो valid DIP चयन data
		 */
		dips = inb(hc->pci_iobase);
		dips = inb(hc->pci_iobase);
		dips = inb(hc->pci_iobase);
		dips = ~inb(hc->pci_iobase) & 0x3F;
		outw(0x0, hc->pci_iobase + 4);
		/* disable PCI auxbridge function */
		HFC_outb(hc, R_BRG_PCM_CFG, V_PCM_CLK);
		prपूर्णांकk(KERN_INFO "%s: %s DIPs(0x%x)\n",
		       m->venकरोr_name, m->card_name, dips);
		अवरोध;
	हाल DIP_E1:
		/*
		 * get DIP Setting क्रम beroNet E1 cards
		 * DIP Setting: collect GPI 4/5/6/7 (R_GPI_IN0)
		 */
		dips = (~HFC_inb(hc, R_GPI_IN0) & 0xF0) >> 4;
		prपूर्णांकk(KERN_INFO "%s: %s DIPs(0x%x)\n",
		       m->venकरोr_name, m->card_name, dips);
		अवरोध;
	पूर्ण

	/* add to list */
	spin_lock_irqsave(&HFClock, flags);
	list_add_tail(&hc->list, &HFClist);
	spin_unlock_irqrestore(&HFClock, flags);

	/* use as घड़ी source */
	अगर (घड़ी == HFC_cnt + 1)
		hc->iघड़ी = mISDN_रेजिस्टर_घड़ी("HFCMulti", 0, घड़ीctl, hc);

	/* initialize hardware */
	hc->irq = (m->irq) ? : hc->pci_dev->irq;
	ret_err = init_card(hc);
	अगर (ret_err) अणु
		prपूर्णांकk(KERN_ERR "init card returns %d\n", ret_err);
		release_card(hc);
		वापस ret_err;
	पूर्ण

	/* start IRQ and वापस */
	spin_lock_irqsave(&hc->lock, flags);
	enable_hwirq(hc);
	spin_unlock_irqrestore(&hc->lock, flags);
	वापस 0;

मुक्त_card:
	release_io_hfcmulti(hc);
	अगर (hc == syncmaster)
		syncmaster = शून्य;
	kमुक्त(hc);
	वापस ret_err;
पूर्ण

अटल व्योम hfc_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hfc_multi	*card = pci_get_drvdata(pdev);
	u_दीर्घ			flags;

	अगर (debug)
		prपूर्णांकk(KERN_INFO "removing hfc_multi card vendor:%x "
		       "device:%x subvendor:%x subdevice:%x\n",
		       pdev->venकरोr, pdev->device,
		       pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device);

	अगर (card) अणु
		spin_lock_irqsave(&HFClock, flags);
		release_card(card);
		spin_unlock_irqrestore(&HFClock, flags);
	पूर्ण  अन्यथा अणु
		अगर (debug)
			prपूर्णांकk(KERN_DEBUG "%s: drvdata already removed\n",
			       __func__);
	पूर्ण
पूर्ण

#घोषणा	VENDOR_CCD	"Cologne Chip AG"
#घोषणा	VENDOR_BN	"beroNet GmbH"
#घोषणा	VENDOR_DIG	"Digium Inc."
#घोषणा VENDOR_JH	"Junghanns.NET GmbH"
#घोषणा VENDOR_PRIM	"PrimuX"

अटल स्थिर काष्ठा hm_map hfcm_map[] = अणु
	/*0*/	अणुVENDOR_BN, "HFC-1S Card (mini PCI)", 4, 1, 1, 3, 0, DIP_4S, 0, 0पूर्ण,
	/*1*/	अणुVENDOR_BN, "HFC-2S Card", 4, 2, 1, 3, 0, DIP_4S, 0, 0पूर्ण,
	/*2*/	अणुVENDOR_BN, "HFC-2S Card (mini PCI)", 4, 2, 1, 3, 0, DIP_4S, 0, 0पूर्ण,
	/*3*/	अणुVENDOR_BN, "HFC-4S Card", 4, 4, 1, 2, 0, DIP_4S, 0, 0पूर्ण,
	/*4*/	अणुVENDOR_BN, "HFC-4S Card (mini PCI)", 4, 4, 1, 2, 0, 0, 0, 0पूर्ण,
	/*5*/	अणुVENDOR_CCD, "HFC-4S Eval (old)", 4, 4, 0, 0, 0, 0, 0, 0पूर्ण,
	/*6*/	अणुVENDOR_CCD, "HFC-4S IOB4ST", 4, 4, 1, 2, 0, DIP_4S, 0, 0पूर्ण,
	/*7*/	अणुVENDOR_CCD, "HFC-4S", 4, 4, 1, 2, 0, 0, 0, 0पूर्ण,
	/*8*/	अणुVENDOR_DIG, "HFC-4S Card", 4, 4, 0, 2, 0, 0, HFC_IO_MODE_REGIO, 0पूर्ण,
	/*9*/	अणुVENDOR_CCD, "HFC-4S Swyx 4xS0 SX2 QuadBri", 4, 4, 1, 2, 0, 0, 0, 0पूर्ण,
	/*10*/	अणुVENDOR_JH, "HFC-4S (junghanns 2.0)", 4, 4, 1, 2, 0, 0, 0, 0पूर्ण,
	/*11*/	अणुVENDOR_PRIM, "HFC-2S Primux Card", 4, 2, 0, 0, 0, 0, 0, 0पूर्ण,

	/*12*/	अणुVENDOR_BN, "HFC-8S Card", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,
	/*13*/	अणुVENDOR_BN, "HFC-8S Card (+)", 8, 8, 1, 8, 0, DIP_8S,
		 HFC_IO_MODE_REGIO, 0पूर्ण,
	/*14*/	अणुVENDOR_CCD, "HFC-8S Eval (old)", 8, 8, 0, 0, 0, 0, 0, 0पूर्ण,
	/*15*/	अणुVENDOR_CCD, "HFC-8S IOB4ST Recording", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,

	/*16*/	अणुVENDOR_CCD, "HFC-8S IOB8ST", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,
	/*17*/	अणुVENDOR_CCD, "HFC-8S", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,
	/*18*/	अणुVENDOR_CCD, "HFC-8S", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,

	/*19*/	अणुVENDOR_BN, "HFC-E1 Card", 1, 1, 0, 1, 0, DIP_E1, 0, 0पूर्ण,
	/*20*/	अणुVENDOR_BN, "HFC-E1 Card (mini PCI)", 1, 1, 0, 1, 0, 0, 0, 0पूर्ण,
	/*21*/	अणुVENDOR_BN, "HFC-E1+ Card (Dual)", 1, 1, 0, 1, 0, DIP_E1, 0, 0पूर्ण,
	/*22*/	अणुVENDOR_BN, "HFC-E1 Card (Dual)", 1, 1, 0, 1, 0, DIP_E1, 0, 0पूर्ण,

	/*23*/	अणुVENDOR_CCD, "HFC-E1 Eval (old)", 1, 1, 0, 0, 0, 0, 0, 0पूर्ण,
	/*24*/	अणुVENDOR_CCD, "HFC-E1 IOB1E1", 1, 1, 0, 1, 0, 0, 0, 0पूर्ण,
	/*25*/	अणुVENDOR_CCD, "HFC-E1", 1, 1, 0, 1, 0, 0, 0, 0पूर्ण,

	/*26*/	अणुVENDOR_CCD, "HFC-4S Speech Design", 4, 4, 0, 0, 0, 0,
		 HFC_IO_MODE_PLXSD, 0पूर्ण,
	/*27*/	अणुVENDOR_CCD, "HFC-E1 Speech Design", 1, 1, 0, 0, 0, 0,
		 HFC_IO_MODE_PLXSD, 0पूर्ण,
	/*28*/	अणुVENDOR_CCD, "HFC-4S OpenVox", 4, 4, 1, 0, 0, 0, 0, 0पूर्ण,
	/*29*/	अणुVENDOR_CCD, "HFC-2S OpenVox", 4, 2, 1, 0, 0, 0, 0, 0पूर्ण,
	/*30*/	अणुVENDOR_CCD, "HFC-8S OpenVox", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,
	/*31*/	अणुVENDOR_CCD, "XHFC-4S Speech Design", 5, 4, 0, 0, 0, 0,
		 HFC_IO_MODE_EMBSD, XHFC_IRQपूर्ण,
	/*32*/	अणुVENDOR_JH, "HFC-8S (junghanns)", 8, 8, 1, 0, 0, 0, 0, 0पूर्ण,
	/*33*/	अणुVENDOR_BN, "HFC-2S Beronet Card PCIe", 4, 2, 1, 3, 0, DIP_4S, 0, 0पूर्ण,
	/*34*/	अणुVENDOR_BN, "HFC-4S Beronet Card PCIe", 4, 4, 1, 2, 0, DIP_4S, 0, 0पूर्ण,
पूर्ण;

#अघोषित H
#घोषणा H(x)	((अचिन्हित दीर्घ)&hfcm_map[x])
अटल स्थिर काष्ठा pci_device_id hfmultipci_ids[] = अणु

	/* Cards with HFC-4S Chip */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN1SM, 0, 0, H(0)पूर्ण, /* BN1S mini PCI */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN2S, 0, 0, H(1)पूर्ण, /* BN2S */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN2SM, 0, 0, H(2)पूर्ण, /* BN2S mini PCI */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN4S, 0, 0, H(3)पूर्ण, /* BN4S */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN4SM, 0, 0, H(4)पूर्ण, /* BN4S mini PCI */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_DEVICE_ID_CCD_HFC4S, 0, 0, H(5)पूर्ण, /* Old Eval */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_IOB4ST, 0, 0, H(6)पूर्ण, /* IOB4ST */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_HFC4S, 0, 0, H(7)पूर्ण, /* 4S */
	अणु PCI_VENDOR_ID_DIGIUM, PCI_DEVICE_ID_DIGIUM_HFC4S,
	  PCI_VENDOR_ID_DIGIUM, PCI_DEVICE_ID_DIGIUM_HFC4S, 0, 0, H(8)पूर्ण,
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_SWYX4S, 0, 0, H(9)पूर्ण, /* 4S Swyx */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_JH4S20, 0, 0, H(10)पूर्ण,
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_PMX2S, 0, 0, H(11)पूर्ण, /* Primux */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_OV4S, 0, 0, H(28)पूर्ण, /* OpenVox 4 */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_OV2S, 0, 0, H(29)पूर्ण, /* OpenVox 2 */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  0xb761, 0, 0, H(33)पूर्ण, /* BN2S PCIe */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC4S, PCI_VENDOR_ID_CCD,
	  0xb762, 0, 0, H(34)पूर्ण, /* BN4S PCIe */

	/* Cards with HFC-8S Chip */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN8S, 0, 0, H(12)पूर्ण, /* BN8S */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BN8SP, 0, 0, H(13)पूर्ण, /* BN8S+ */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_DEVICE_ID_CCD_HFC8S, 0, 0, H(14)पूर्ण, /* old Eval */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_IOB8STR, 0, 0, H(15)पूर्ण, /* IOB8ST Recording */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_IOB8ST, 0, 0, H(16)पूर्ण, /* IOB8ST  */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_IOB8ST_1, 0, 0, H(17)पूर्ण, /* IOB8ST  */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_HFC8S, 0, 0, H(18)पूर्ण, /* 8S */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_OV8S, 0, 0, H(30)पूर्ण, /* OpenVox 8 */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFC8S, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_JH8S, 0, 0, H(32)पूर्ण, /* Junganns 8S  */


	/* Cards with HFC-E1 Chip */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BNE1, 0, 0, H(19)पूर्ण, /* BNE1 */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BNE1M, 0, 0, H(20)पूर्ण, /* BNE1 mini PCI */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BNE1DP, 0, 0, H(21)पूर्ण, /* BNE1 + (Dual) */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_BNE1D, 0, 0, H(22)पूर्ण, /* BNE1 (Dual) */

	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_DEVICE_ID_CCD_HFCE1, 0, 0, H(23)पूर्ण, /* Old Eval */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_IOB1E1, 0, 0, H(24)पूर्ण, /* IOB1E1 */
	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_HFCE1, 0, 0, H(25)पूर्ण, /* E1 */

	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_SPD4S, 0, 0, H(26)पूर्ण, /* PLX PCI Bridge */
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_SPDE1, 0, 0, H(27)पूर्ण, /* PLX PCI Bridge */

	अणु PCI_VENDOR_ID_CCD, PCI_DEVICE_ID_CCD_HFCE1, PCI_VENDOR_ID_CCD,
	  PCI_SUBDEVICE_ID_CCD_JHSE1, 0, 0, H(25)पूर्ण, /* Junghanns E1 */

	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_HFC4S), 0 पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_HFC8S), 0 पूर्ण,
	अणु PCI_VDEVICE(CCD, PCI_DEVICE_ID_CCD_HFCE1), 0 पूर्ण,
	अणु0, पूर्ण
पूर्ण;
#अघोषित H

MODULE_DEVICE_TABLE(pci, hfmultipci_ids);

अटल पूर्णांक
hfcmulti_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा hm_map	*m = (काष्ठा hm_map *)ent->driver_data;
	पूर्णांक		ret;

	अगर (m == शून्य && ent->venकरोr == PCI_VENDOR_ID_CCD && (
		    ent->device == PCI_DEVICE_ID_CCD_HFC4S ||
		    ent->device == PCI_DEVICE_ID_CCD_HFC8S ||
		    ent->device == PCI_DEVICE_ID_CCD_HFCE1)) अणु
		prपूर्णांकk(KERN_ERR
		       "Unknown HFC multiport controller (vendor:%04x device:%04x "
		       "subvendor:%04x subdevice:%04x)\n", pdev->venकरोr,
		       pdev->device, pdev->subप्रणाली_venकरोr,
		       pdev->subप्रणाली_device);
		prपूर्णांकk(KERN_ERR
		       "Please contact the driver maintainer for support.\n");
		वापस -ENODEV;
	पूर्ण
	ret = hfcmulti_init(m, pdev, ent);
	अगर (ret)
		वापस ret;
	HFC_cnt++;
	prपूर्णांकk(KERN_INFO "%d devices registered\n", HFC_cnt);
	वापस 0;
पूर्ण

अटल काष्ठा pci_driver hfcmultipci_driver = अणु
	.name		= "hfc_multi",
	.probe		= hfcmulti_probe,
	.हटाओ		= hfc_हटाओ_pci,
	.id_table	= hfmultipci_ids,
पूर्ण;

अटल व्योम __निकास
HFCmulti_cleanup(व्योम)
अणु
	काष्ठा hfc_multi *card, *next;

	/* get rid of all devices of this driver */
	list_क्रम_each_entry_safe(card, next, &HFClist, list)
		release_card(card);
	pci_unरेजिस्टर_driver(&hfcmultipci_driver);
पूर्ण

अटल पूर्णांक __init
HFCmulti_init(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक i, xhfc = 0;
	काष्ठा hm_map m;

	prपूर्णांकk(KERN_INFO "mISDN: HFC-multi driver %s\n", HFC_MULTI_VERSION);

#अगर_घोषित IRQ_DEBUG
	prपूर्णांकk(KERN_DEBUG "%s: IRQ_DEBUG IS ENABLED!\n", __func__);
#पूर्ण_अगर

	अगर (debug & DEBUG_HFCMULTI_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: init entered\n", __func__);

	चयन (poll) अणु
	हाल 0:
		poll_समयr = 6;
		poll = 128;
		अवरोध;
	हाल 8:
		poll_समयr = 2;
		अवरोध;
	हाल 16:
		poll_समयr = 3;
		अवरोध;
	हाल 32:
		poll_समयr = 4;
		अवरोध;
	हाल 64:
		poll_समयr = 5;
		अवरोध;
	हाल 128:
		poll_समयr = 6;
		अवरोध;
	हाल 256:
		poll_समयr = 7;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR
		       "%s: Wrong poll value (%d).\n", __func__, poll);
		err = -EINVAL;
		वापस err;

	पूर्ण

	अगर (!घड़ी)
		घड़ी = 1;

	/* Register the embedded devices.
	 * This should be करोne beक्रमe the PCI cards registration */
	चयन (hwid) अणु
	हाल HWID_MINIP4:
		xhfc = 1;
		m = hfcm_map[31];
		अवरोध;
	हाल HWID_MINIP8:
		xhfc = 2;
		m = hfcm_map[31];
		अवरोध;
	हाल HWID_MINIP16:
		xhfc = 4;
		m = hfcm_map[31];
		अवरोध;
	शेष:
		xhfc = 0;
	पूर्ण

	क्रम (i = 0; i < xhfc; ++i) अणु
		err = hfcmulti_init(&m, शून्य, शून्य);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "error registering embedded driver: "
			       "%x\n", err);
			वापस err;
		पूर्ण
		HFC_cnt++;
		prपूर्णांकk(KERN_INFO "%d devices registered\n", HFC_cnt);
	पूर्ण

	/* Register the PCI cards */
	err = pci_रेजिस्टर_driver(&hfcmultipci_driver);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "error registering pci driver: %x\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण


module_init(HFCmulti_init);
module_निकास(HFCmulti_cleanup);
