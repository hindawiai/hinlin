<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************/

/*
 *    yam.c  -- YAM radio modem driver.
 *
 *      Copyright (C) 1998 Frederic Rible F1OAT (frible@teaser.fr)
 *      Adapted from baycom.c driver written by Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  Please note that the GPL allows you to use the driver, NOT the radio.
 *  In order to use the radio, you need a license from the communications
 *  authority of your country.
 *
 *  History:
 *   0.0 F1OAT 06.06.98  Begin of work with baycom.c source code V 0.3
 *   0.1 F1OAT 07.06.98  Add समयr polling routine क्रम channel arbitration
 *   0.2 F6FBB 08.06.98  Added delay after FPGA programming
 *   0.3 F6FBB 29.07.98  Delayed PTT implementation क्रम dupmode=2
 *   0.4 F6FBB 30.07.98  Added TxTail, Slotसमय and Persistence
 *   0.5 F6FBB 01.08.98  Shared IRQs, /proc/net and network statistics
 *   0.6 F6FBB 25.08.98  Added 1200Bds क्रमmat
 *   0.7 F6FBB 12.09.98  Added to the kernel configuration
 *   0.8 F6FBB 14.10.98  Fixed slotसमय/persistence timing bug
 *       OK1ZIA 2.09.01  Fixed "kfree_skb on hard IRQ" 
 *                       using dev_kमुक्त_skb_any(). (important in 2.4 kernel)
 */

/*****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bitops.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/firmware.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/ax25.h>

#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/net_namespace.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>

#समावेश <linux/yam.h>

/* --------------------------------------------------------------------- */

अटल स्थिर अक्षर yam_drvname[] = "yam";
अटल स्थिर अक्षर yam_drvinfo[] __initस्थिर = KERN_INFO \
	"YAM driver version 0.8 by F1OAT/F6FBB\n";

/* --------------------------------------------------------------------- */

#घोषणा FIRMWARE_9600	"yam/9600.bin"
#घोषणा FIRMWARE_1200	"yam/1200.bin"

#घोषणा YAM_9600	1
#घोषणा YAM_1200	2

#घोषणा NR_PORTS	4
#घोषणा YAM_MAGIC	0xF10A7654

/* Transmitter states */

#घोषणा TX_OFF		0
#घोषणा TX_HEAD		1
#घोषणा TX_DATA		2
#घोषणा TX_CRC1		3
#घोषणा TX_CRC2		4
#घोषणा TX_TAIL		5

#घोषणा YAM_MAX_FRAME	1024

#घोषणा DEFAULT_BITRATE	9600			/* bps */
#घोषणा DEFAULT_HOLDD	10			/* sec */
#घोषणा DEFAULT_TXD	300			/* ms */
#घोषणा DEFAULT_TXTAIL	10			/* ms */
#घोषणा DEFAULT_SLOT	100			/* ms */
#घोषणा DEFAULT_PERS	64			/* 0->255 */

काष्ठा yam_port अणु
	पूर्णांक magic;
	पूर्णांक bitrate;
	पूर्णांक baudrate;
	पूर्णांक iobase;
	पूर्णांक irq;
	पूर्णांक dupmode;

	काष्ठा net_device *dev;

	पूर्णांक nb_rxपूर्णांक;
	पूर्णांक nb_mdपूर्णांक;

	/* Parameters section */

	पूर्णांक txd;				/* tx delay */
	पूर्णांक holdd;				/* duplex ptt delay */
	पूर्णांक txtail;				/* txtail delay */
	पूर्णांक slot;				/* slotसमय */
	पूर्णांक pers;				/* persistence */

	/* Tx section */

	पूर्णांक tx_state;
	पूर्णांक tx_count;
	पूर्णांक slotcnt;
	अचिन्हित अक्षर tx_buf[YAM_MAX_FRAME];
	पूर्णांक tx_len;
	पूर्णांक tx_crcl, tx_crch;
	काष्ठा sk_buff_head send_queue;		/* Packets aरुकोing transmission */

	/* Rx section */

	पूर्णांक dcd;
	अचिन्हित अक्षर rx_buf[YAM_MAX_FRAME];
	पूर्णांक rx_len;
	पूर्णांक rx_crcl, rx_crch;
पूर्ण;

काष्ठा yam_mcs अणु
	अचिन्हित अक्षर bits[YAM_FPGA_SIZE];
	पूर्णांक bitrate;
	काष्ठा yam_mcs *next;
पूर्ण;

अटल काष्ठा net_device *yam_devs[NR_PORTS];

अटल काष्ठा yam_mcs *yam_data;

अटल DEFINE_TIMER(yam_समयr, शून्य);

/* --------------------------------------------------------------------- */

#घोषणा RBR(iobase)	(iobase+0)
#घोषणा THR(iobase)	(iobase+0)
#घोषणा IER(iobase)	(iobase+1)
#घोषणा IIR(iobase)	(iobase+2)
#घोषणा FCR(iobase)	(iobase+2)
#घोषणा LCR(iobase)	(iobase+3)
#घोषणा MCR(iobase)	(iobase+4)
#घोषणा LSR(iobase)	(iobase+5)
#घोषणा MSR(iobase)	(iobase+6)
#घोषणा SCR(iobase)	(iobase+7)
#घोषणा DLL(iobase)	(iobase+0)
#घोषणा DLM(iobase)	(iobase+1)

#घोषणा YAM_EXTENT	8

/* Interrupt Identअगरication Register Bit Masks */
#घोषणा IIR_NOPEND	1
#घोषणा IIR_MSR		0
#घोषणा IIR_TX		2
#घोषणा IIR_RX		4
#घोषणा IIR_LSR		6
#घोषणा IIR_TIMEOUT	12			/* Fअगरo mode only */

#घोषणा IIR_MASK	0x0F

/* Interrupt Enable Register Bit Masks */
#घोषणा IER_RX		1			/* enable rx पूर्णांकerrupt */
#घोषणा IER_TX		2			/* enable tx पूर्णांकerrupt */
#घोषणा IER_LSR		4			/* enable line status पूर्णांकerrupts */
#घोषणा IER_MSR		8			/* enable modem status पूर्णांकerrupts */

/* Modem Control Register Bit Masks */
#घोषणा MCR_DTR		0x01			/* DTR output */
#घोषणा MCR_RTS		0x02			/* RTS output */
#घोषणा MCR_OUT1	0x04			/* OUT1 output (not accessible in RS232) */
#घोषणा MCR_OUT2	0x08			/* Master Interrupt enable (must be set on PCs) */
#घोषणा MCR_LOOP	0x10			/* Loopback enable */

/* Modem Status Register Bit Masks */
#घोषणा MSR_DCTS	0x01			/* Delta CTS input */
#घोषणा MSR_DDSR	0x02			/* Delta DSR */
#घोषणा MSR_DRIN	0x04			/* Delta RI */
#घोषणा MSR_DDCD	0x08			/* Delta DCD */
#घोषणा MSR_CTS		0x10			/* CTS input */
#घोषणा MSR_DSR		0x20			/* DSR input */
#घोषणा MSR_RING	0x40			/* RI  input */
#घोषणा MSR_DCD		0x80			/* DCD input */

/* line status रेजिस्टर bit mask */
#घोषणा LSR_RXC		0x01
#घोषणा LSR_OE		0x02
#घोषणा LSR_PE		0x04
#घोषणा LSR_FE		0x08
#घोषणा LSR_BREAK	0x10
#घोषणा LSR_THRE	0x20
#घोषणा LSR_TSRE	0x40

/* Line Control Register Bit Masks */
#घोषणा LCR_DLAB	0x80
#घोषणा LCR_BREAK	0x40
#घोषणा LCR_PZERO	0x28
#घोषणा LCR_PEVEN	0x18
#घोषणा LCR_PODD	0x08
#घोषणा LCR_STOP1	0x00
#घोषणा LCR_STOP2	0x04
#घोषणा LCR_BIT5	0x00
#घोषणा LCR_BIT6	0x02
#घोषणा LCR_BIT7	0x01
#घोषणा LCR_BIT8	0x03

/* YAM Modem <-> UART Port mapping */

#घोषणा TX_RDY		MSR_DCTS		/* transmitter पढ़ोy to send */
#घोषणा RX_DCD		MSR_DCD			/* carrier detect */
#घोषणा RX_FLAG		MSR_RING		/* hdlc flag received */
#घोषणा FPGA_DONE	MSR_DSR			/* FPGA is configured */
#घोषणा PTT_ON		(MCR_RTS|MCR_OUT2)	/* activate PTT */
#घोषणा PTT_OFF		(MCR_DTR|MCR_OUT2)	/* release PTT */

#घोषणा ENABLE_RXINT	IER_RX			/* enable uart rx पूर्णांकerrupt during rx */
#घोषणा ENABLE_TXINT	IER_MSR			/* enable uart ms पूर्णांकerrupt during tx */
#घोषणा ENABLE_RTXINT	(IER_RX|IER_MSR)	/* full duplex operations */


/*************************************************************************
* CRC Tables
************************************************************************/

अटल स्थिर अचिन्हित अक्षर chktabl[256] =
अणु0x00, 0x89, 0x12, 0x9b, 0x24, 0xad, 0x36, 0xbf, 0x48, 0xc1, 0x5a, 0xd3, 0x6c, 0xe5, 0x7e,
 0xf7, 0x81, 0x08, 0x93, 0x1a, 0xa5, 0x2c, 0xb7, 0x3e, 0xc9, 0x40, 0xdb, 0x52, 0xed, 0x64,
 0xff, 0x76, 0x02, 0x8b, 0x10, 0x99, 0x26, 0xaf, 0x34, 0xbd, 0x4a, 0xc3, 0x58, 0xd1, 0x6e,
 0xe7, 0x7c, 0xf5, 0x83, 0x0a, 0x91, 0x18, 0xa7, 0x2e, 0xb5, 0x3c, 0xcb, 0x42, 0xd9, 0x50,
 0xef, 0x66, 0xfd, 0x74, 0x04, 0x8d, 0x16, 0x9f, 0x20, 0xa9, 0x32, 0xbb, 0x4c, 0xc5, 0x5e,
 0xd7, 0x68, 0xe1, 0x7a, 0xf3, 0x85, 0x0c, 0x97, 0x1e, 0xa1, 0x28, 0xb3, 0x3a, 0xcd, 0x44,
 0xdf, 0x56, 0xe9, 0x60, 0xfb, 0x72, 0x06, 0x8f, 0x14, 0x9d, 0x22, 0xab, 0x30, 0xb9, 0x4e,
 0xc7, 0x5c, 0xd5, 0x6a, 0xe3, 0x78, 0xf1, 0x87, 0x0e, 0x95, 0x1c, 0xa3, 0x2a, 0xb1, 0x38,
 0xcf, 0x46, 0xdd, 0x54, 0xeb, 0x62, 0xf9, 0x70, 0x08, 0x81, 0x1a, 0x93, 0x2c, 0xa5, 0x3e,
 0xb7, 0x40, 0xc9, 0x52, 0xdb, 0x64, 0xed, 0x76, 0xff, 0x89, 0x00, 0x9b, 0x12, 0xad, 0x24,
 0xbf, 0x36, 0xc1, 0x48, 0xd3, 0x5a, 0xe5, 0x6c, 0xf7, 0x7e, 0x0a, 0x83, 0x18, 0x91, 0x2e,
 0xa7, 0x3c, 0xb5, 0x42, 0xcb, 0x50, 0xd9, 0x66, 0xef, 0x74, 0xfd, 0x8b, 0x02, 0x99, 0x10,
 0xaf, 0x26, 0xbd, 0x34, 0xc3, 0x4a, 0xd1, 0x58, 0xe7, 0x6e, 0xf5, 0x7c, 0x0c, 0x85, 0x1e,
 0x97, 0x28, 0xa1, 0x3a, 0xb3, 0x44, 0xcd, 0x56, 0xdf, 0x60, 0xe9, 0x72, 0xfb, 0x8d, 0x04,
 0x9f, 0x16, 0xa9, 0x20, 0xbb, 0x32, 0xc5, 0x4c, 0xd7, 0x5e, 0xe1, 0x68, 0xf3, 0x7a, 0x0e,
 0x87, 0x1c, 0x95, 0x2a, 0xa3, 0x38, 0xb1, 0x46, 0xcf, 0x54, 0xdd, 0x62, 0xeb, 0x70, 0xf9,
 0x8f, 0x06, 0x9d, 0x14, 0xab, 0x22, 0xb9, 0x30, 0xc7, 0x4e, 0xd5, 0x5c, 0xe3, 0x6a, 0xf1,
 0x78पूर्ण;
अटल स्थिर अचिन्हित अक्षर chktabh[256] =
अणु0x00, 0x11, 0x23, 0x32, 0x46, 0x57, 0x65, 0x74, 0x8c, 0x9d, 0xaf, 0xbe, 0xca, 0xdb, 0xe9,
 0xf8, 0x10, 0x01, 0x33, 0x22, 0x56, 0x47, 0x75, 0x64, 0x9c, 0x8d, 0xbf, 0xae, 0xda, 0xcb,
 0xf9, 0xe8, 0x21, 0x30, 0x02, 0x13, 0x67, 0x76, 0x44, 0x55, 0xad, 0xbc, 0x8e, 0x9f, 0xeb,
 0xfa, 0xc8, 0xd9, 0x31, 0x20, 0x12, 0x03, 0x77, 0x66, 0x54, 0x45, 0xbd, 0xac, 0x9e, 0x8f,
 0xfb, 0xea, 0xd8, 0xc9, 0x42, 0x53, 0x61, 0x70, 0x04, 0x15, 0x27, 0x36, 0xce, 0xdf, 0xed,
 0xfc, 0x88, 0x99, 0xab, 0xba, 0x52, 0x43, 0x71, 0x60, 0x14, 0x05, 0x37, 0x26, 0xde, 0xcf,
 0xfd, 0xec, 0x98, 0x89, 0xbb, 0xaa, 0x63, 0x72, 0x40, 0x51, 0x25, 0x34, 0x06, 0x17, 0xef,
 0xfe, 0xcc, 0xdd, 0xa9, 0xb8, 0x8a, 0x9b, 0x73, 0x62, 0x50, 0x41, 0x35, 0x24, 0x16, 0x07,
 0xff, 0xee, 0xdc, 0xcd, 0xb9, 0xa8, 0x9a, 0x8b, 0x84, 0x95, 0xa7, 0xb6, 0xc2, 0xd3, 0xe1,
 0xf0, 0x08, 0x19, 0x2b, 0x3a, 0x4e, 0x5f, 0x6d, 0x7c, 0x94, 0x85, 0xb7, 0xa6, 0xd2, 0xc3,
 0xf1, 0xe0, 0x18, 0x09, 0x3b, 0x2a, 0x5e, 0x4f, 0x7d, 0x6c, 0xa5, 0xb4, 0x86, 0x97, 0xe3,
 0xf2, 0xc0, 0xd1, 0x29, 0x38, 0x0a, 0x1b, 0x6f, 0x7e, 0x4c, 0x5d, 0xb5, 0xa4, 0x96, 0x87,
 0xf3, 0xe2, 0xd0, 0xc1, 0x39, 0x28, 0x1a, 0x0b, 0x7f, 0x6e, 0x5c, 0x4d, 0xc6, 0xd7, 0xe5,
 0xf4, 0x80, 0x91, 0xa3, 0xb2, 0x4a, 0x5b, 0x69, 0x78, 0x0c, 0x1d, 0x2f, 0x3e, 0xd6, 0xc7,
 0xf5, 0xe4, 0x90, 0x81, 0xb3, 0xa2, 0x5a, 0x4b, 0x79, 0x68, 0x1c, 0x0d, 0x3f, 0x2e, 0xe7,
 0xf6, 0xc4, 0xd5, 0xa1, 0xb0, 0x82, 0x93, 0x6b, 0x7a, 0x48, 0x59, 0x2d, 0x3c, 0x0e, 0x1f,
 0xf7, 0xe6, 0xd4, 0xc5, 0xb1, 0xa0, 0x92, 0x83, 0x7b, 0x6a, 0x58, 0x49, 0x3d, 0x2c, 0x1e,
 0x0fपूर्ण;

/*************************************************************************
* FPGA functions
************************************************************************/

अटल व्योम delay(पूर्णांक ms)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + ((ms * HZ) / 1000);
	जबतक (समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();
पूर्ण

/*
 * reset FPGA
 */

अटल व्योम fpga_reset(पूर्णांक iobase)
अणु
	outb(0, IER(iobase));
	outb(LCR_DLAB | LCR_BIT5, LCR(iobase));
	outb(1, DLL(iobase));
	outb(0, DLM(iobase));

	outb(LCR_BIT5, LCR(iobase));
	inb(LSR(iobase));
	inb(MSR(iobase));
	/* turn off FPGA supply voltage */
	outb(MCR_OUT1 | MCR_OUT2, MCR(iobase));
	delay(100);
	/* turn on FPGA supply voltage again */
	outb(MCR_DTR | MCR_RTS | MCR_OUT1 | MCR_OUT2, MCR(iobase));
	delay(100);
पूर्ण

/*
 * send one byte to FPGA
 */

अटल पूर्णांक fpga_ग_लिखो(पूर्णांक iobase, अचिन्हित अक्षर wrd)
अणु
	अचिन्हित अक्षर bit;
	पूर्णांक k;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ / 10;

	क्रम (k = 0; k < 8; k++) अणु
		bit = (wrd & 0x80) ? (MCR_RTS | MCR_DTR) : MCR_DTR;
		outb(bit | MCR_OUT1 | MCR_OUT2, MCR(iobase));
		wrd <<= 1;
		outb(0xfc, THR(iobase));
		जबतक ((inb(LSR(iobase)) & LSR_TSRE) == 0)
			अगर (समय_after(jअगरfies, समयout))
				वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * predef should be 0 क्रम loading user defined mcs
 * predef should be YAM_1200 क्रम loading predef 1200 mcs
 * predef should be YAM_9600 क्रम loading predef 9600 mcs
 */
अटल अचिन्हित अक्षर *add_mcs(अचिन्हित अक्षर *bits, पूर्णांक bitrate,
			      अचिन्हित पूर्णांक predef)
अणु
	स्थिर अक्षर *fw_name[2] = अणुFIRMWARE_9600, FIRMWARE_1200पूर्ण;
	स्थिर काष्ठा firmware *fw;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा yam_mcs *p;
	पूर्णांक err;

	चयन (predef) अणु
	हाल 0:
		fw = शून्य;
		अवरोध;
	हाल YAM_1200:
	हाल YAM_9600:
		predef--;
		pdev = platक्रमm_device_रेजिस्टर_simple("yam", 0, शून्य, 0);
		अगर (IS_ERR(pdev)) अणु
			prपूर्णांकk(KERN_ERR "yam: Failed to register firmware\n");
			वापस शून्य;
		पूर्ण
		err = request_firmware(&fw, fw_name[predef], &pdev->dev);
		platक्रमm_device_unरेजिस्टर(pdev);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "Failed to load firmware \"%s\"\n",
			       fw_name[predef]);
			वापस शून्य;
		पूर्ण
		अगर (fw->size != YAM_FPGA_SIZE) अणु
			prपूर्णांकk(KERN_ERR "Bogus length %zu in firmware \"%s\"\n",
			       fw->size, fw_name[predef]);
			release_firmware(fw);
			वापस शून्य;
		पूर्ण
		bits = (अचिन्हित अक्षर *)fw->data;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "yam: Invalid predef number %u\n", predef);
		वापस शून्य;
	पूर्ण

	/* If it alपढ़ोy exists, replace the bit data */
	p = yam_data;
	जबतक (p) अणु
		अगर (p->bitrate == bitrate) अणु
			स_नकल(p->bits, bits, YAM_FPGA_SIZE);
			जाओ out;
		पूर्ण
		p = p->next;
	पूर्ण

	/* Allocate a new mcs */
	अगर ((p = kदो_स्मृति(माप(काष्ठा yam_mcs), GFP_KERNEL)) == शून्य) अणु
		release_firmware(fw);
		वापस शून्य;
	पूर्ण
	स_नकल(p->bits, bits, YAM_FPGA_SIZE);
	p->bitrate = bitrate;
	p->next = yam_data;
	yam_data = p;
 out:
	release_firmware(fw);
	वापस p->bits;
पूर्ण

अटल अचिन्हित अक्षर *get_mcs(पूर्णांक bitrate)
अणु
	काष्ठा yam_mcs *p;

	p = yam_data;
	जबतक (p) अणु
		अगर (p->bitrate == bitrate)
			वापस p->bits;
		p = p->next;
	पूर्ण

	/* Load predefined mcs data */
	चयन (bitrate) अणु
	हाल 1200:
		/* setting predef as YAM_1200 क्रम loading predef 1200 mcs */
		वापस add_mcs(शून्य, bitrate, YAM_1200);
	शेष:
		/* setting predef as YAM_9600 क्रम loading predef 9600 mcs */
		वापस add_mcs(शून्य, bitrate, YAM_9600);
	पूर्ण
पूर्ण

/*
 * करोwnload bitstream to FPGA
 * data is contained in bits[] array in yam1200.h resp. yam9600.h
 */

अटल पूर्णांक fpga_करोwnload(पूर्णांक iobase, पूर्णांक bitrate)
अणु
	पूर्णांक i, rc;
	अचिन्हित अक्षर *pbits;

	pbits = get_mcs(bitrate);
	अगर (pbits == शून्य)
		वापस -1;

	fpga_reset(iobase);
	क्रम (i = 0; i < YAM_FPGA_SIZE; i++) अणु
		अगर (fpga_ग_लिखो(iobase, pbits[i])) अणु
			prपूर्णांकk(KERN_ERR "yam: error in write cycle\n");
			वापस -1;			/* ग_लिखो... */
		पूर्ण
	पूर्ण

	fpga_ग_लिखो(iobase, 0xFF);
	rc = inb(MSR(iobase));		/* check DONE संकेत */

	/* Needed क्रम some hardwares */
	delay(50);

	वापस (rc & MSR_DSR) ? 0 : -1;
पूर्ण


/************************************************************************
* Serial port init 
************************************************************************/

अटल व्योम yam_set_uart(काष्ठा net_device *dev)
अणु
	काष्ठा yam_port *yp = netdev_priv(dev);
	पूर्णांक भागisor = 115200 / yp->baudrate;

	outb(0, IER(dev->base_addr));
	outb(LCR_DLAB | LCR_BIT8, LCR(dev->base_addr));
	outb(भागisor, DLL(dev->base_addr));
	outb(0, DLM(dev->base_addr));
	outb(LCR_BIT8, LCR(dev->base_addr));
	outb(PTT_OFF, MCR(dev->base_addr));
	outb(0x00, FCR(dev->base_addr));

	/* Flush pending irq */

	inb(RBR(dev->base_addr));
	inb(MSR(dev->base_addr));

	/* Enable rx irq */

	outb(ENABLE_RTXINT, IER(dev->base_addr));
पूर्ण


/* --------------------------------------------------------------------- */

क्रमागत uart अणु
	c_uart_unknown, c_uart_8250,
	c_uart_16450, c_uart_16550, c_uart_16550A
पूर्ण;

अटल स्थिर अक्षर *uart_str[] =
अणु"unknown", "8250", "16450", "16550", "16550A"पूर्ण;

अटल क्रमागत uart yam_check_uart(अचिन्हित पूर्णांक iobase)
अणु
	अचिन्हित अक्षर b1, b2, b3;
	क्रमागत uart u;
	क्रमागत uart uart_tab[] =
	अणुc_uart_16450, c_uart_unknown, c_uart_16550, c_uart_16550Aपूर्ण;

	b1 = inb(MCR(iobase));
	outb(b1 | 0x10, MCR(iobase));	/* loopback mode */
	b2 = inb(MSR(iobase));
	outb(0x1a, MCR(iobase));
	b3 = inb(MSR(iobase)) & 0xf0;
	outb(b1, MCR(iobase));		/* restore old values */
	outb(b2, MSR(iobase));
	अगर (b3 != 0x90)
		वापस c_uart_unknown;
	inb(RBR(iobase));
	inb(RBR(iobase));
	outb(0x01, FCR(iobase));	/* enable FIFOs */
	u = uart_tab[(inb(IIR(iobase)) >> 6) & 3];
	अगर (u == c_uart_16450) अणु
		outb(0x5a, SCR(iobase));
		b1 = inb(SCR(iobase));
		outb(0xa5, SCR(iobase));
		b2 = inb(SCR(iobase));
		अगर ((b1 != 0x5a) || (b2 != 0xa5))
			u = c_uart_8250;
	पूर्ण
	वापस u;
पूर्ण

/******************************************************************************
* Rx Section
******************************************************************************/
अटल अंतरभूत व्योम yam_rx_flag(काष्ठा net_device *dev, काष्ठा yam_port *yp)
अणु
	अगर (yp->dcd && yp->rx_len >= 3 && yp->rx_len < YAM_MAX_FRAME) अणु
		पूर्णांक pkt_len = yp->rx_len - 2 + 1;	/* -CRC + kiss */
		काष्ठा sk_buff *skb;

		अगर ((yp->rx_crch & yp->rx_crcl) != 0xFF) अणु
			/* Bad crc */
		पूर्ण अन्यथा अणु
			अगर (!(skb = dev_alloc_skb(pkt_len))) अणु
				prपूर्णांकk(KERN_WARNING "%s: memory squeeze, dropping packet\n", dev->name);
				++dev->stats.rx_dropped;
			पूर्ण अन्यथा अणु
				अचिन्हित अक्षर *cp;
				cp = skb_put(skb, pkt_len);
				*cp++ = 0;		/* KISS kludge */
				स_नकल(cp, yp->rx_buf, pkt_len - 1);
				skb->protocol = ax25_type_trans(skb, dev);
				netअगर_rx(skb);
				++dev->stats.rx_packets;
			पूर्ण
		पूर्ण
	पूर्ण
	yp->rx_len = 0;
	yp->rx_crcl = 0x21;
	yp->rx_crch = 0xf3;
पूर्ण

अटल अंतरभूत व्योम yam_rx_byte(काष्ठा net_device *dev, काष्ठा yam_port *yp, अचिन्हित अक्षर rxb)
अणु
	अगर (yp->rx_len < YAM_MAX_FRAME) अणु
		अचिन्हित अक्षर c = yp->rx_crcl;
		yp->rx_crcl = (chktabl[c] ^ yp->rx_crch);
		yp->rx_crch = (chktabh[c] ^ rxb);
		yp->rx_buf[yp->rx_len++] = rxb;
	पूर्ण
पूर्ण

/********************************************************************************
* TX Section
********************************************************************************/

अटल व्योम ptt_on(काष्ठा net_device *dev)
अणु
	outb(PTT_ON, MCR(dev->base_addr));
पूर्ण

अटल व्योम ptt_off(काष्ठा net_device *dev)
अणु
	outb(PTT_OFF, MCR(dev->base_addr));
पूर्ण

अटल netdev_tx_t yam_send_packet(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा yam_port *yp = netdev_priv(dev);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	skb_queue_tail(&yp->send_queue, skb);
	netअगर_trans_update(dev);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम yam_start_tx(काष्ठा net_device *dev, काष्ठा yam_port *yp)
अणु
	अगर ((yp->tx_state == TX_TAIL) || (yp->txd == 0))
		yp->tx_count = 1;
	अन्यथा
		yp->tx_count = (yp->bitrate * yp->txd) / 8000;
	yp->tx_state = TX_HEAD;
	ptt_on(dev);
पूर्ण

अटल व्योम yam_arbitrate(काष्ठा net_device *dev)
अणु
	काष्ठा yam_port *yp = netdev_priv(dev);

	अगर (yp->magic != YAM_MAGIC || yp->tx_state != TX_OFF ||
	    skb_queue_empty(&yp->send_queue))
		वापस;
	/* tx_state is TX_OFF and there is data to send */

	अगर (yp->dupmode) अणु
		/* Full duplex mode, करोn't रुको */
		yam_start_tx(dev, yp);
		वापस;
	पूर्ण
	अगर (yp->dcd) अणु
		/* DCD on, रुको sloसमय ... */
		yp->slotcnt = yp->slot / 10;
		वापस;
	पूर्ण
	/* Is slotसमय passed ? */
	अगर ((--yp->slotcnt) > 0)
		वापस;

	yp->slotcnt = yp->slot / 10;

	/* is अक्रमom > persist ? */
	अगर ((pअक्रमom_u32() % 256) > yp->pers)
		वापस;

	yam_start_tx(dev, yp);
पूर्ण

अटल व्योम yam_करोसमयr(काष्ठा समयr_list *unused)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev = yam_devs[i];
		अगर (dev && netअगर_running(dev))
			yam_arbitrate(dev);
	पूर्ण
	yam_समयr.expires = jअगरfies + HZ / 100;
	add_समयr(&yam_समयr);
पूर्ण

अटल व्योम yam_tx_byte(काष्ठा net_device *dev, काष्ठा yam_port *yp)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर b, temp;

	चयन (yp->tx_state) अणु
	हाल TX_OFF:
		अवरोध;
	हाल TX_HEAD:
		अगर (--yp->tx_count <= 0) अणु
			अगर (!(skb = skb_dequeue(&yp->send_queue))) अणु
				ptt_off(dev);
				yp->tx_state = TX_OFF;
				अवरोध;
			पूर्ण
			yp->tx_state = TX_DATA;
			अगर (skb->data[0] != 0) अणु
/*                              करो_kiss_params(s, skb->data, skb->len); */
				dev_kमुक्त_skb_any(skb);
				अवरोध;
			पूर्ण
			yp->tx_len = skb->len - 1;	/* strip KISS byte */
			अगर (yp->tx_len >= YAM_MAX_FRAME || yp->tx_len < 2) अणु
        			dev_kमुक्त_skb_any(skb);
				अवरोध;
			पूर्ण
			skb_copy_from_linear_data_offset(skb, 1,
							 yp->tx_buf,
							 yp->tx_len);
			dev_kमुक्त_skb_any(skb);
			yp->tx_count = 0;
			yp->tx_crcl = 0x21;
			yp->tx_crch = 0xf3;
			yp->tx_state = TX_DATA;
		पूर्ण
		अवरोध;
	हाल TX_DATA:
		b = yp->tx_buf[yp->tx_count++];
		outb(b, THR(dev->base_addr));
		temp = yp->tx_crcl;
		yp->tx_crcl = chktabl[temp] ^ yp->tx_crch;
		yp->tx_crch = chktabh[temp] ^ b;
		अगर (yp->tx_count >= yp->tx_len) अणु
			yp->tx_state = TX_CRC1;
		पूर्ण
		अवरोध;
	हाल TX_CRC1:
		yp->tx_crch = chktabl[yp->tx_crcl] ^ yp->tx_crch;
		yp->tx_crcl = chktabh[yp->tx_crcl] ^ chktabl[yp->tx_crch] ^ 0xff;
		outb(yp->tx_crcl, THR(dev->base_addr));
		yp->tx_state = TX_CRC2;
		अवरोध;
	हाल TX_CRC2:
		outb(chktabh[yp->tx_crch] ^ 0xFF, THR(dev->base_addr));
		अगर (skb_queue_empty(&yp->send_queue)) अणु
			yp->tx_count = (yp->bitrate * yp->txtail) / 8000;
			अगर (yp->dupmode == 2)
				yp->tx_count += (yp->bitrate * yp->holdd) / 8;
			अगर (yp->tx_count == 0)
				yp->tx_count = 1;
			yp->tx_state = TX_TAIL;
		पूर्ण अन्यथा अणु
			yp->tx_count = 1;
			yp->tx_state = TX_HEAD;
		पूर्ण
		++dev->stats.tx_packets;
		अवरोध;
	हाल TX_TAIL:
		अगर (--yp->tx_count <= 0) अणु
			yp->tx_state = TX_OFF;
			ptt_off(dev);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/***********************************************************************************
* ISR routine
************************************************************************************/

अटल irqवापस_t yam_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev;
	काष्ठा yam_port *yp;
	अचिन्हित अक्षर iir;
	पूर्णांक counter = 100;
	पूर्णांक i;
	पूर्णांक handled = 0;

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		dev = yam_devs[i];
		yp = netdev_priv(dev);

		अगर (!netअगर_running(dev))
			जारी;

		जबतक ((iir = IIR_MASK & inb(IIR(dev->base_addr))) != IIR_NOPEND) अणु
			अचिन्हित अक्षर msr = inb(MSR(dev->base_addr));
			अचिन्हित अक्षर lsr = inb(LSR(dev->base_addr));
			अचिन्हित अक्षर rxb;

			handled = 1;

			अगर (lsr & LSR_OE)
				++dev->stats.rx_fअगरo_errors;

			yp->dcd = (msr & RX_DCD) ? 1 : 0;

			अगर (--counter <= 0) अणु
				prपूर्णांकk(KERN_ERR "%s: too many irq iir=%d\n",
						dev->name, iir);
				जाओ out;
			पूर्ण
			अगर (msr & TX_RDY) अणु
				++yp->nb_mdपूर्णांक;
				yam_tx_byte(dev, yp);
			पूर्ण
			अगर (lsr & LSR_RXC) अणु
				++yp->nb_rxपूर्णांक;
				rxb = inb(RBR(dev->base_addr));
				अगर (msr & RX_FLAG)
					yam_rx_flag(dev, yp);
				अन्यथा
					yam_rx_byte(dev, yp, rxb);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *yam_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस (*pos < NR_PORTS) ? yam_devs[*pos] : शून्य;
पूर्ण

अटल व्योम *yam_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस (*pos < NR_PORTS) ? yam_devs[*pos] : शून्य;
पूर्ण

अटल व्योम yam_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक yam_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net_device *dev = v;
	स्थिर काष्ठा yam_port *yp = netdev_priv(dev);

	seq_म_लिखो(seq, "Device %s\n", dev->name);
	seq_म_लिखो(seq, "  Up       %d\n", netअगर_running(dev));
	seq_म_लिखो(seq, "  Speed    %u\n", yp->bitrate);
	seq_म_लिखो(seq, "  IoBase   0x%x\n", yp->iobase);
	seq_म_लिखो(seq, "  BaudRate %u\n", yp->baudrate);
	seq_म_लिखो(seq, "  IRQ      %u\n", yp->irq);
	seq_म_लिखो(seq, "  TxState  %u\n", yp->tx_state);
	seq_म_लिखो(seq, "  Duplex   %u\n", yp->dupmode);
	seq_म_लिखो(seq, "  HoldDly  %u\n", yp->holdd);
	seq_म_लिखो(seq, "  TxDelay  %u\n", yp->txd);
	seq_म_लिखो(seq, "  TxTail   %u\n", yp->txtail);
	seq_म_लिखो(seq, "  SlotTime %u\n", yp->slot);
	seq_म_लिखो(seq, "  Persist  %u\n", yp->pers);
	seq_म_लिखो(seq, "  TxFrames %lu\n", dev->stats.tx_packets);
	seq_म_लिखो(seq, "  RxFrames %lu\n", dev->stats.rx_packets);
	seq_म_लिखो(seq, "  TxInt    %u\n", yp->nb_mdपूर्णांक);
	seq_म_लिखो(seq, "  RxInt    %u\n", yp->nb_rxपूर्णांक);
	seq_म_लिखो(seq, "  RxOver   %lu\n", dev->stats.rx_fअगरo_errors);
	seq_म_लिखो(seq, "\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations yam_seqops = अणु
	.start = yam_seq_start,
	.next = yam_seq_next,
	.stop = yam_seq_stop,
	.show = yam_seq_show,
पूर्ण;
#पूर्ण_अगर


/* --------------------------------------------------------------------- */

अटल पूर्णांक yam_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा yam_port *yp = netdev_priv(dev);
	क्रमागत uart u;
	पूर्णांक i;
	पूर्णांक ret=0;

	prपूर्णांकk(KERN_INFO "Trying %s at iobase 0x%lx irq %u\n", dev->name, dev->base_addr, dev->irq);

	अगर (!yp->bitrate)
		वापस -ENXIO;
	अगर (!dev->base_addr || dev->base_addr > 0x1000 - YAM_EXTENT ||
		dev->irq < 2 || dev->irq > 15) अणु
		वापस -ENXIO;
	पूर्ण
	अगर (!request_region(dev->base_addr, YAM_EXTENT, dev->name))
	अणु
		prपूर्णांकk(KERN_ERR "%s: cannot 0x%lx busy\n", dev->name, dev->base_addr);
		वापस -EACCES;
	पूर्ण
	अगर ((u = yam_check_uart(dev->base_addr)) == c_uart_unknown) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot find uart type\n", dev->name);
		ret = -EIO;
		जाओ out_release_base;
	पूर्ण
	अगर (fpga_करोwnload(dev->base_addr, yp->bitrate)) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot init FPGA\n", dev->name);
		ret = -EIO;
		जाओ out_release_base;
	पूर्ण
	outb(0, IER(dev->base_addr));
	अगर (request_irq(dev->irq, yam_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: irq %d busy\n", dev->name, dev->irq);
		ret = -EBUSY;
		जाओ out_release_base;
	पूर्ण

	yam_set_uart(dev);

	netअगर_start_queue(dev);
	
	yp->slotcnt = yp->slot / 10;

	/* Reset overruns क्रम all ports - FPGA programming makes overruns */
	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *yam_dev = yam_devs[i];

		inb(LSR(yam_dev->base_addr));
		yam_dev->stats.rx_fअगरo_errors = 0;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s at iobase 0x%lx irq %u uart %s\n", dev->name, dev->base_addr, dev->irq,
		   uart_str[u]);
	वापस 0;

out_release_base:
	release_region(dev->base_addr, YAM_EXTENT);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक yam_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा yam_port *yp = netdev_priv(dev);

	अगर (!dev)
		वापस -EINVAL;

	/*
	 * disable पूर्णांकerrupts
	 */
	outb(0, IER(dev->base_addr));
	outb(1, MCR(dev->base_addr));
	/* Remove IRQ handler अगर last */
	मुक्त_irq(dev->irq,dev);
	release_region(dev->base_addr, YAM_EXTENT);
	netअगर_stop_queue(dev);
	जबतक ((skb = skb_dequeue(&yp->send_queue)))
		dev_kमुक्त_skb(skb);

	prपूर्णांकk(KERN_INFO "%s: close yam at iobase 0x%lx irq %u\n",
		   yam_drvname, dev->base_addr, dev->irq);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक yam_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा yam_port *yp = netdev_priv(dev);
	काष्ठा yamdrv_ioctl_cfg yi;
	काष्ठा yamdrv_ioctl_mcs *ym;
	पूर्णांक ioctl_cmd;

	अगर (copy_from_user(&ioctl_cmd, अगरr->अगरr_data, माप(पूर्णांक)))
		 वापस -EFAULT;

	अगर (yp->magic != YAM_MAGIC)
		वापस -EINVAL;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (cmd != SIOCDEVPRIVATE)
		वापस -EINVAL;

	चयन (ioctl_cmd) अणु

	हाल SIOCYAMRESERVED:
		वापस -EINVAL;			/* unused */

	हाल SIOCYAMSMCS:
		अगर (netअगर_running(dev))
			वापस -EINVAL;		/* Cannot change this parameter when up */
		ym = memdup_user(अगरr->अगरr_data,
				 माप(काष्ठा yamdrv_ioctl_mcs));
		अगर (IS_ERR(ym))
			वापस PTR_ERR(ym);
		अगर (ym->cmd != SIOCYAMSMCS)
			वापस -EINVAL;
		अगर (ym->bitrate > YAM_MAXBITRATE) अणु
			kमुक्त(ym);
			वापस -EINVAL;
		पूर्ण
		/* setting predef as 0 क्रम loading userdefined mcs data */
		add_mcs(ym->bits, ym->bitrate, 0);
		kमुक्त(ym);
		अवरोध;

	हाल SIOCYAMSCFG:
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EPERM;
		अगर (copy_from_user(&yi, अगरr->अगरr_data, माप(काष्ठा yamdrv_ioctl_cfg)))
			 वापस -EFAULT;

		अगर (yi.cmd != SIOCYAMSCFG)
			वापस -EINVAL;
		अगर ((yi.cfg.mask & YAM_IOBASE) && netअगर_running(dev))
			वापस -EINVAL;		/* Cannot change this parameter when up */
		अगर ((yi.cfg.mask & YAM_IRQ) && netअगर_running(dev))
			वापस -EINVAL;		/* Cannot change this parameter when up */
		अगर ((yi.cfg.mask & YAM_BITRATE) && netअगर_running(dev))
			वापस -EINVAL;		/* Cannot change this parameter when up */
		अगर ((yi.cfg.mask & YAM_BAUDRATE) && netअगर_running(dev))
			वापस -EINVAL;		/* Cannot change this parameter when up */

		अगर (yi.cfg.mask & YAM_IOBASE) अणु
			yp->iobase = yi.cfg.iobase;
			dev->base_addr = yi.cfg.iobase;
		पूर्ण
		अगर (yi.cfg.mask & YAM_IRQ) अणु
			अगर (yi.cfg.irq > 15)
				वापस -EINVAL;
			yp->irq = yi.cfg.irq;
			dev->irq = yi.cfg.irq;
		पूर्ण
		अगर (yi.cfg.mask & YAM_BITRATE) अणु
			अगर (yi.cfg.bitrate > YAM_MAXBITRATE)
				वापस -EINVAL;
			yp->bitrate = yi.cfg.bitrate;
		पूर्ण
		अगर (yi.cfg.mask & YAM_BAUDRATE) अणु
			अगर (yi.cfg.baudrate > YAM_MAXBAUDRATE)
				वापस -EINVAL;
			yp->baudrate = yi.cfg.baudrate;
		पूर्ण
		अगर (yi.cfg.mask & YAM_MODE) अणु
			अगर (yi.cfg.mode > YAM_MAXMODE)
				वापस -EINVAL;
			yp->dupmode = yi.cfg.mode;
		पूर्ण
		अगर (yi.cfg.mask & YAM_HOLDDLY) अणु
			अगर (yi.cfg.holddly > YAM_MAXHOLDDLY)
				वापस -EINVAL;
			yp->holdd = yi.cfg.holddly;
		पूर्ण
		अगर (yi.cfg.mask & YAM_TXDELAY) अणु
			अगर (yi.cfg.txdelay > YAM_MAXTXDELAY)
				वापस -EINVAL;
			yp->txd = yi.cfg.txdelay;
		पूर्ण
		अगर (yi.cfg.mask & YAM_TXTAIL) अणु
			अगर (yi.cfg.txtail > YAM_MAXTXTAIL)
				वापस -EINVAL;
			yp->txtail = yi.cfg.txtail;
		पूर्ण
		अगर (yi.cfg.mask & YAM_PERSIST) अणु
			अगर (yi.cfg.persist > YAM_MAXPERSIST)
				वापस -EINVAL;
			yp->pers = yi.cfg.persist;
		पूर्ण
		अगर (yi.cfg.mask & YAM_SLOTTIME) अणु
			अगर (yi.cfg.slotसमय > YAM_MAXSLOTTIME)
				वापस -EINVAL;
			yp->slot = yi.cfg.slotसमय;
			yp->slotcnt = yp->slot / 10;
		पूर्ण
		अवरोध;

	हाल SIOCYAMGCFG:
		स_रखो(&yi, 0, माप(yi));
		yi.cfg.mask = 0xffffffff;
		yi.cfg.iobase = yp->iobase;
		yi.cfg.irq = yp->irq;
		yi.cfg.bitrate = yp->bitrate;
		yi.cfg.baudrate = yp->baudrate;
		yi.cfg.mode = yp->dupmode;
		yi.cfg.txdelay = yp->txd;
		yi.cfg.holddly = yp->holdd;
		yi.cfg.txtail = yp->txtail;
		yi.cfg.persist = yp->pers;
		yi.cfg.slotसमय = yp->slot;
		अगर (copy_to_user(अगरr->अगरr_data, &yi, माप(काष्ठा yamdrv_ioctl_cfg)))
			 वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -EINVAL;

	पूर्ण

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक yam_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *) addr;

	/* addr is an AX.25 shअगरted ASCII mac address */
	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा net_device_ops yam_netdev_ops = अणु
	.nकरो_खोलो	     = yam_खोलो,
	.nकरो_stop	     = yam_बंद,
	.nकरो_start_xmit      = yam_send_packet,
	.nकरो_करो_ioctl 	     = yam_ioctl,
	.nकरो_set_mac_address = yam_set_mac_address,
पूर्ण;

अटल व्योम yam_setup(काष्ठा net_device *dev)
अणु
	काष्ठा yam_port *yp = netdev_priv(dev);

	yp->magic = YAM_MAGIC;
	yp->bitrate = DEFAULT_BITRATE;
	yp->baudrate = DEFAULT_BITRATE * 2;
	yp->iobase = 0;
	yp->irq = 0;
	yp->dupmode = 0;
	yp->holdd = DEFAULT_HOLDD;
	yp->txd = DEFAULT_TXD;
	yp->txtail = DEFAULT_TXTAIL;
	yp->slot = DEFAULT_SLOT;
	yp->pers = DEFAULT_PERS;
	yp->dev = dev;

	dev->base_addr = yp->iobase;
	dev->irq = yp->irq;

	skb_queue_head_init(&yp->send_queue);

	dev->netdev_ops = &yam_netdev_ops;
	dev->header_ops = &ax25_header_ops;

	dev->type = ARPHRD_AX25;
	dev->hard_header_len = AX25_MAX_HEADER_LEN;
	dev->mtu = AX25_MTU;
	dev->addr_len = AX25_ADDR_LEN;
	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);
पूर्ण

अटल पूर्णांक __init yam_init_driver(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i, err;
	अक्षर name[IFNAMSIZ];

	prपूर्णांकk(yam_drvinfo);

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		प्र_लिखो(name, "yam%d", i);
		
		dev = alloc_netdev(माप(काष्ठा yam_port), name,
				   NET_NAME_UNKNOWN, yam_setup);
		अगर (!dev) अणु
			pr_err("yam: cannot allocate net device\n");
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		
		err = रेजिस्टर_netdev(dev);
		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING "yam: cannot register net device %s\n", dev->name);
			मुक्त_netdev(dev);
			जाओ error;
		पूर्ण
		yam_devs[i] = dev;

	पूर्ण

	समयr_setup(&yam_समयr, yam_करोसमयr, 0);
	yam_समयr.expires = jअगरfies + HZ / 100;
	add_समयr(&yam_समयr);

	proc_create_seq("yam", 0444, init_net.proc_net, &yam_seqops);
	वापस 0;
 error:
	जबतक (--i >= 0) अणु
		unरेजिस्टर_netdev(yam_devs[i]);
		मुक्त_netdev(yam_devs[i]);
	पूर्ण
	वापस err;
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम __निकास yam_cleanup_driver(व्योम)
अणु
	काष्ठा yam_mcs *p;
	पूर्णांक i;

	del_समयr_sync(&yam_समयr);
	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev = yam_devs[i];
		अगर (dev) अणु
			unरेजिस्टर_netdev(dev);
			मुक्त_netdev(dev);
		पूर्ण
	पूर्ण

	जबतक (yam_data) अणु
		p = yam_data;
		yam_data = yam_data->next;
		kमुक्त(p);
	पूर्ण

	हटाओ_proc_entry("yam", init_net.proc_net);
पूर्ण

/* --------------------------------------------------------------------- */

MODULE_AUTHOR("Frederic Rible F1OAT frible@teaser.fr");
MODULE_DESCRIPTION("Yam amateur radio modem driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_1200);
MODULE_FIRMWARE(FIRMWARE_9600);

module_init(yam_init_driver);
module_निकास(yam_cleanup_driver);

/* --------------------------------------------------------------------- */

