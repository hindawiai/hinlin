<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *          mxser.c  -- MOXA Smartio/Industio family multiport serial driver.
 *
 *      Copyright (C) 1999-2006  Moxa Technologies (support@moxa.com).
 *	Copyright (C) 2006-2008  Jiri Slaby <jirislaby@gmail.com>
 *
 *      This code is loosely based on the 1.8 moxa driver which is based on
 *	Linux serial driver, written by Linus Torvalds, Theoकरोre T'so and
 *	others.
 *
 *	Fed through a cleanup, indent and हटाओ of non 2.6 code by Alan Cox
 *	<alan@lxorguk.ukuu.org.uk>. The original 1.8 code is available on
 *	www.moxa.com.
 *	- Fixed x86_64 cleanness
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#समावेश "mxser.h"

#घोषणा	MXSER_VERSION	"2.0.5"		/* 1.14 */
#घोषणा	MXSERMAJOR	 174

#घोषणा MXSER_BOARDS		4	/* Max. boards */
#घोषणा MXSER_PORTS_PER_BOARD	8	/* Max. ports per board */
#घोषणा MXSER_PORTS		(MXSER_BOARDS * MXSER_PORTS_PER_BOARD)
#घोषणा MXSER_ISR_PASS_LIMIT	100

/*CheckIsMoxaMust वापस value*/
#घोषणा MOXA_OTHER_UART		0x00
#घोषणा MOXA_MUST_MU150_HWID	0x01
#घोषणा MOXA_MUST_MU860_HWID	0x02

#घोषणा WAKEUP_CHARS		256

#घोषणा UART_MCR_AFE		0x20
#घोषणा UART_LSR_SPECIAL	0x1E

#घोषणा PCI_DEVICE_ID_POS104UL	0x1044
#घोषणा PCI_DEVICE_ID_CB108	0x1080
#घोषणा PCI_DEVICE_ID_CP102UF	0x1023
#घोषणा PCI_DEVICE_ID_CP112UL	0x1120
#घोषणा PCI_DEVICE_ID_CB114	0x1142
#घोषणा PCI_DEVICE_ID_CP114UL	0x1143
#घोषणा PCI_DEVICE_ID_CB134I	0x1341
#घोषणा PCI_DEVICE_ID_CP138U	0x1380


#घोषणा C168_ASIC_ID    1
#घोषणा C104_ASIC_ID    2
#घोषणा C102_ASIC_ID	0xB
#घोषणा CI132_ASIC_ID	4
#घोषणा CI134_ASIC_ID	3
#घोषणा CI104J_ASIC_ID  5

#घोषणा MXSER_HIGHBAUD	1
#घोषणा MXSER_HAS2	2

/* This is only क्रम PCI */
अटल स्थिर काष्ठा अणु
	पूर्णांक type;
	पूर्णांक tx_fअगरo;
	पूर्णांक rx_fअगरo;
	पूर्णांक xmit_fअगरo_size;
	पूर्णांक rx_high_water;
	पूर्णांक rx_trigger;
	पूर्णांक rx_low_water;
	दीर्घ max_baud;
पूर्ण Gpci_uart_info[] = अणु
	अणुMOXA_OTHER_UART, 16, 16, 16, 14, 14, 1, 921600Lपूर्ण,
	अणुMOXA_MUST_MU150_HWID, 64, 64, 64, 48, 48, 16, 230400Lपूर्ण,
	अणुMOXA_MUST_MU860_HWID, 128, 128, 128, 96, 96, 32, 921600Lपूर्ण
पूर्ण;
#घोषणा UART_INFO_NUM	ARRAY_SIZE(Gpci_uart_info)

काष्ठा mxser_cardinfo अणु
	अक्षर *name;
	अचिन्हित पूर्णांक nports;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा mxser_cardinfo mxser_cards[] = अणु
/* 0*/	अणु "C168 series",	8, पूर्ण,
	अणु "C104 series",	4, पूर्ण,
	अणु "CI-104J series",	4, पूर्ण,
	अणु "C168H/PCI series",	8, पूर्ण,
	अणु "C104H/PCI series",	4, पूर्ण,
/* 5*/	अणु "C102 series",	4, MXSER_HAS2 पूर्ण,	/* C102-ISA */
	अणु "CI-132 series",	4, MXSER_HAS2 पूर्ण,
	अणु "CI-134 series",	4, पूर्ण,
	अणु "CP-132 series",	2, पूर्ण,
	अणु "CP-114 series",	4, पूर्ण,
/*10*/	अणु "CT-114 series",	4, पूर्ण,
	अणु "CP-102 series",	2, MXSER_HIGHBAUD पूर्ण,
	अणु "CP-104U series",	4, पूर्ण,
	अणु "CP-168U series",	8, पूर्ण,
	अणु "CP-132U series",	2, पूर्ण,
/*15*/	अणु "CP-134U series",	4, पूर्ण,
	अणु "CP-104JU series",	4, पूर्ण,
	अणु "Moxa UC7000 Serial",	8, पूर्ण,		/* RC7000 */
	अणु "CP-118U series",	8, पूर्ण,
	अणु "CP-102UL series",	2, पूर्ण,
/*20*/	अणु "CP-102U series",	2, पूर्ण,
	अणु "CP-118EL series",	8, पूर्ण,
	अणु "CP-168EL series",	8, पूर्ण,
	अणु "CP-104EL series",	4, पूर्ण,
	अणु "CB-108 series",	8, पूर्ण,
/*25*/	अणु "CB-114 series",	4, पूर्ण,
	अणु "CB-134I series",	4, पूर्ण,
	अणु "CP-138U series",	8, पूर्ण,
	अणु "POS-104UL series",	4, पूर्ण,
	अणु "CP-114UL series",	4, पूर्ण,
/*30*/	अणु "CP-102UF series",	2, पूर्ण,
	अणु "CP-112UL series",	2, पूर्ण,
पूर्ण;

/* driver_data correspond to the lines in the काष्ठाure above
   see also ISA probe function beक्रमe you change something */
अटल स्थिर काष्ठा pci_device_id mxser_pcibrds[] = अणु
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_C168),	.driver_data = 3 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_C104),	.driver_data = 4 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP132),	.driver_data = 8 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP114),	.driver_data = 9 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CT114),	.driver_data = 10 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP102),	.driver_data = 11 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP104U),	.driver_data = 12 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP168U),	.driver_data = 13 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP132U),	.driver_data = 14 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP134U),	.driver_data = 15 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP104JU),.driver_data = 16 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_RC7000),	.driver_data = 17 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP118U),	.driver_data = 18 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP102UL),.driver_data = 19 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP102U),	.driver_data = 20 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP118EL),.driver_data = 21 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP168EL),.driver_data = 22 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_MOXA_CP104EL),.driver_data = 23 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CB108),	.driver_data = 24 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CB114),	.driver_data = 25 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CB134I),	.driver_data = 26 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CP138U),	.driver_data = 27 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_POS104UL),	.driver_data = 28 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CP114UL),	.driver_data = 29 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CP102UF),	.driver_data = 30 पूर्ण,
	अणु PCI_VDEVICE(MOXA, PCI_DEVICE_ID_CP112UL),	.driver_data = 31 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, mxser_pcibrds);

अटल अचिन्हित दीर्घ ioaddr[MXSER_BOARDS];
अटल पूर्णांक ttymajor = MXSERMAJOR;

/* Variables क्रम insmod */

MODULE_AUTHOR("Casper Yang");
MODULE_DESCRIPTION("MOXA Smartio/Industio Family Multiport Board Device Driver");
module_param_hw_array(ioaddr, uदीर्घ, ioport, शून्य, 0);
MODULE_PARM_DESC(ioaddr, "ISA io addresses to look for a moxa board");
module_param(ttymajor, पूर्णांक, 0);
MODULE_LICENSE("GPL");

काष्ठा mxser_log अणु
	पूर्णांक tick;
	अचिन्हित दीर्घ rxcnt[MXSER_PORTS];
	अचिन्हित दीर्घ txcnt[MXSER_PORTS];
पूर्ण;

काष्ठा mxser_mon अणु
	अचिन्हित दीर्घ rxcnt;
	अचिन्हित दीर्घ txcnt;
	अचिन्हित दीर्घ up_rxcnt;
	अचिन्हित दीर्घ up_txcnt;
	पूर्णांक modem_status;
	अचिन्हित अक्षर hold_reason;
पूर्ण;

काष्ठा mxser_mon_ext अणु
	अचिन्हित दीर्घ rx_cnt[32];
	अचिन्हित दीर्घ tx_cnt[32];
	अचिन्हित दीर्घ up_rxcnt[32];
	अचिन्हित दीर्घ up_txcnt[32];
	पूर्णांक modem_status[32];

	दीर्घ baudrate[32];
	पूर्णांक databits[32];
	पूर्णांक stopbits[32];
	पूर्णांक parity[32];
	पूर्णांक flowctrl[32];
	पूर्णांक fअगरo[32];
	पूर्णांक अगरtype[32];
पूर्ण;

काष्ठा mxser_board;

काष्ठा mxser_port अणु
	काष्ठा tty_port port;
	काष्ठा mxser_board *board;

	अचिन्हित दीर्घ ioaddr;
	अचिन्हित दीर्घ opmode_ioaddr;
	पूर्णांक max_baud;

	पूर्णांक rx_high_water;
	पूर्णांक rx_trigger;		/* Rx fअगरo trigger level */
	पूर्णांक rx_low_water;
	पूर्णांक baud_base;		/* max. speed */
	पूर्णांक type;		/* UART type */

	पूर्णांक x_अक्षर;		/* xon/xoff अक्षरacter */
	पूर्णांक IER;		/* Interrupt Enable Register */
	पूर्णांक MCR;		/* Modem control रेजिस्टर */

	अचिन्हित अक्षर stop_rx;
	अचिन्हित अक्षर ldisc_stop_rx;

	पूर्णांक custom_भागisor;
	अचिन्हित अक्षर err_shaकरोw;

	काष्ठा async_icount icount; /* kernel counters क्रम 4 input पूर्णांकerrupts */
	अचिन्हित पूर्णांक समयout;

	पूर्णांक पढ़ो_status_mask;
	पूर्णांक ignore_status_mask;
	अचिन्हित पूर्णांक xmit_fअगरo_size;
	पूर्णांक xmit_head;
	पूर्णांक xmit_tail;
	पूर्णांक xmit_cnt;
	पूर्णांक closing;

	काष्ठा ktermios normal_termios;

	काष्ठा mxser_mon mon_data;

	spinlock_t slock;
पूर्ण;

काष्ठा mxser_board अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक irq;
	स्थिर काष्ठा mxser_cardinfo *info;
	अचिन्हित दीर्घ vector;
	अचिन्हित दीर्घ vector_mask;

	पूर्णांक chip_flag;
	पूर्णांक uart_type;

	काष्ठा mxser_port ports[MXSER_PORTS_PER_BOARD];
पूर्ण;

काष्ठा mxser_mstatus अणु
	tcflag_t cflag;
	पूर्णांक cts;
	पूर्णांक dsr;
	पूर्णांक ri;
	पूर्णांक dcd;
पूर्ण;

अटल काष्ठा mxser_board mxser_boards[MXSER_BOARDS];
अटल काष्ठा tty_driver *mxvar_sdriver;
अटल काष्ठा mxser_log mxvar_log;
अटल पूर्णांक mxser_set_baud_method[MXSER_PORTS + 1];

अटल व्योम mxser_enable_must_enchance_mode(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr |= MOXA_MUST_EFR_EFRB_ENABLE;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

#अगर_घोषित	CONFIG_PCI
अटल व्योम mxser_disable_must_enchance_mode(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_EFRB_ENABLE;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण
#पूर्ण_अगर

अटल व्योम mxser_set_must_xon1_value(अचिन्हित दीर्घ baseio, u8 value)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_BANK_MASK;
	efr |= MOXA_MUST_EFR_BANK0;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(value, baseio + MOXA_MUST_XON1_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

अटल व्योम mxser_set_must_xoff1_value(अचिन्हित दीर्घ baseio, u8 value)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_BANK_MASK;
	efr |= MOXA_MUST_EFR_BANK0;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(value, baseio + MOXA_MUST_XOFF1_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

अटल व्योम mxser_set_must_fअगरo_value(काष्ठा mxser_port *info)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(info->ioaddr + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, info->ioaddr + UART_LCR);

	efr = inb(info->ioaddr + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_BANK_MASK;
	efr |= MOXA_MUST_EFR_BANK1;

	outb(efr, info->ioaddr + MOXA_MUST_EFR_REGISTER);
	outb((u8)info->rx_high_water, info->ioaddr + MOXA_MUST_RBRTH_REGISTER);
	outb((u8)info->rx_trigger, info->ioaddr + MOXA_MUST_RBRTI_REGISTER);
	outb((u8)info->rx_low_water, info->ioaddr + MOXA_MUST_RBRTL_REGISTER);
	outb(oldlcr, info->ioaddr + UART_LCR);
पूर्ण

अटल व्योम mxser_set_must_क्रमागत_value(अचिन्हित दीर्घ baseio, u8 value)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_BANK_MASK;
	efr |= MOXA_MUST_EFR_BANK2;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(value, baseio + MOXA_MUST_ENUM_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल व्योम mxser_get_must_hardware_id(अचिन्हित दीर्घ baseio, u8 *pId)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_BANK_MASK;
	efr |= MOXA_MUST_EFR_BANK2;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	*pId = inb(baseio + MOXA_MUST_HWID_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण
#पूर्ण_अगर

अटल व्योम SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_SF_MASK;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

अटल व्योम mxser_enable_must_tx_software_flow_control(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_SF_TX_MASK;
	efr |= MOXA_MUST_EFR_SF_TX1;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

अटल व्योम mxser_disable_must_tx_software_flow_control(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_SF_TX_MASK;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

अटल व्योम mxser_enable_must_rx_software_flow_control(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_SF_RX_MASK;
	efr |= MOXA_MUST_EFR_SF_RX1;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

अटल व्योम mxser_disable_must_rx_software_flow_control(अचिन्हित दीर्घ baseio)
अणु
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(baseio + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, baseio + UART_LCR);

	efr = inb(baseio + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_SF_RX_MASK;

	outb(efr, baseio + MOXA_MUST_EFR_REGISTER);
	outb(oldlcr, baseio + UART_LCR);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक CheckIsMoxaMust(अचिन्हित दीर्घ io)
अणु
	u8 oldmcr, hwid;
	पूर्णांक i;

	outb(0, io + UART_LCR);
	mxser_disable_must_enchance_mode(io);
	oldmcr = inb(io + UART_MCR);
	outb(0, io + UART_MCR);
	mxser_set_must_xon1_value(io, 0x11);
	अगर ((hwid = inb(io + UART_MCR)) != 0) अणु
		outb(oldmcr, io + UART_MCR);
		वापस MOXA_OTHER_UART;
	पूर्ण

	mxser_get_must_hardware_id(io, &hwid);
	क्रम (i = 1; i < UART_INFO_NUM; i++) अणु /* 0 = OTHER_UART */
		अगर (hwid == Gpci_uart_info[i].type)
			वापस (पूर्णांक)hwid;
	पूर्ण
	वापस MOXA_OTHER_UART;
पूर्ण
#पूर्ण_अगर

अटल व्योम process_txrx_fअगरo(काष्ठा mxser_port *info)
अणु
	पूर्णांक i;

	अगर ((info->type == PORT_16450) || (info->type == PORT_8250)) अणु
		info->rx_trigger = 1;
		info->rx_high_water = 1;
		info->rx_low_water = 1;
		info->xmit_fअगरo_size = 1;
	पूर्ण अन्यथा
		क्रम (i = 0; i < UART_INFO_NUM; i++)
			अगर (info->board->chip_flag == Gpci_uart_info[i].type) अणु
				info->rx_trigger = Gpci_uart_info[i].rx_trigger;
				info->rx_low_water = Gpci_uart_info[i].rx_low_water;
				info->rx_high_water = Gpci_uart_info[i].rx_high_water;
				info->xmit_fअगरo_size = Gpci_uart_info[i].xmit_fअगरo_size;
				अवरोध;
			पूर्ण
पूर्ण

अटल अचिन्हित अक्षर mxser_get_msr(पूर्णांक baseaddr, पूर्णांक mode, पूर्णांक port)
अणु
	अटल अचिन्हित अक्षर mxser_msr[MXSER_PORTS + 1];
	अचिन्हित अक्षर status = 0;

	status = inb(baseaddr + UART_MSR);

	mxser_msr[port] &= 0x0F;
	mxser_msr[port] |= status;
	status = mxser_msr[port];
	अगर (mode)
		mxser_msr[port] = 0;

	वापस status;
पूर्ण

अटल पूर्णांक mxser_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	काष्ठा mxser_port *mp = container_of(port, काष्ठा mxser_port, port);
	वापस (inb(mp->ioaddr + UART_MSR) & UART_MSR_DCD)?1:0;
पूर्ण

अटल व्योम mxser_dtr_rts(काष्ठा tty_port *port, पूर्णांक on)
अणु
	काष्ठा mxser_port *mp = container_of(port, काष्ठा mxser_port, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mp->slock, flags);
	अगर (on)
		outb(inb(mp->ioaddr + UART_MCR) |
			UART_MCR_DTR | UART_MCR_RTS, mp->ioaddr + UART_MCR);
	अन्यथा
		outb(inb(mp->ioaddr + UART_MCR)&~(UART_MCR_DTR | UART_MCR_RTS),
			mp->ioaddr + UART_MCR);
	spin_unlock_irqrestore(&mp->slock, flags);
पूर्ण

अटल पूर्णांक mxser_set_baud(काष्ठा tty_काष्ठा *tty, दीर्घ newspd)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित पूर्णांक quot = 0, baud;
	अचिन्हित अक्षर cval;
	u64 समयout;

	अगर (!info->ioaddr)
		वापस -1;

	अगर (newspd > info->max_baud)
		वापस -1;

	अगर (newspd == 134) अणु
		quot = 2 * info->baud_base / 269;
		tty_encode_baud_rate(tty, 134, 134);
	पूर्ण अन्यथा अगर (newspd) अणु
		quot = info->baud_base / newspd;
		अगर (quot == 0)
			quot = 1;
		baud = info->baud_base/quot;
		tty_encode_baud_rate(tty, baud, baud);
	पूर्ण अन्यथा अणु
		quot = 0;
	पूर्ण

	/*
	 * worst हाल (128 * 1000 * 10 * 18432) needs 35 bits, so भागide in the
	 * u64 करोमुख्य
	 */
	समयout = (u64)info->xmit_fअगरo_size * HZ * 10 * quot;
	करो_भाग(समयout, info->baud_base);
	info->समयout = समयout + HZ / 50; /* Add .02 seconds of slop */

	अगर (quot) अणु
		info->MCR |= UART_MCR_DTR;
		outb(info->MCR, info->ioaddr + UART_MCR);
	पूर्ण अन्यथा अणु
		info->MCR &= ~UART_MCR_DTR;
		outb(info->MCR, info->ioaddr + UART_MCR);
		वापस 0;
	पूर्ण

	cval = inb(info->ioaddr + UART_LCR);

	outb(cval | UART_LCR_DLAB, info->ioaddr + UART_LCR);	/* set DLAB */

	outb(quot & 0xff, info->ioaddr + UART_DLL);	/* LS of भागisor */
	outb(quot >> 8, info->ioaddr + UART_DLM);	/* MS of भागisor */
	outb(cval, info->ioaddr + UART_LCR);	/* reset DLAB */

#अगर_घोषित BOTHER
	अगर (C_BAUD(tty) == BOTHER) अणु
		quot = info->baud_base % newspd;
		quot *= 8;
		अगर (quot % newspd > newspd / 2) अणु
			quot /= newspd;
			quot++;
		पूर्ण अन्यथा
			quot /= newspd;

		mxser_set_must_क्रमागत_value(info->ioaddr, quot);
	पूर्ण अन्यथा
#पूर्ण_अगर
		mxser_set_must_क्रमागत_value(info->ioaddr, 0);

	वापस 0;
पूर्ण

/*
 * This routine is called to set the UART भागisor रेजिस्टरs to match
 * the specअगरied baud rate क्रम a serial port.
 */
अटल व्योम mxser_change_speed(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित cflag, cval, fcr;
	अचिन्हित अक्षर status;

	cflag = tty->termios.c_cflag;
	अगर (!info->ioaddr)
		वापस;

	अगर (mxser_set_baud_method[tty->index] == 0)
		mxser_set_baud(tty, tty_get_baud_rate(tty));

	/* byte size and parity */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		cval = 0x00;
		अवरोध;
	हाल CS6:
		cval = 0x01;
		अवरोध;
	हाल CS7:
		cval = 0x02;
		अवरोध;
	हाल CS8:
		cval = 0x03;
		अवरोध;
	शेष:
		cval = 0x00;
		अवरोध;		/* too keep GCC shut... */
	पूर्ण
	अगर (cflag & CSTOPB)
		cval |= 0x04;
	अगर (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	अगर (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
	अगर (cflag & CMSPAR)
		cval |= UART_LCR_SPAR;

	अगर ((info->type == PORT_8250) || (info->type == PORT_16450)) अणु
		अगर (info->board->chip_flag) अणु
			fcr = UART_FCR_ENABLE_FIFO;
			fcr |= MOXA_MUST_FCR_GDA_MODE_ENABLE;
			mxser_set_must_fअगरo_value(info);
		पूर्ण अन्यथा
			fcr = 0;
	पूर्ण अन्यथा अणु
		fcr = UART_FCR_ENABLE_FIFO;
		अगर (info->board->chip_flag) अणु
			fcr |= MOXA_MUST_FCR_GDA_MODE_ENABLE;
			mxser_set_must_fअगरo_value(info);
		पूर्ण अन्यथा अणु
			चयन (info->rx_trigger) अणु
			हाल 1:
				fcr |= UART_FCR_TRIGGER_1;
				अवरोध;
			हाल 4:
				fcr |= UART_FCR_TRIGGER_4;
				अवरोध;
			हाल 8:
				fcr |= UART_FCR_TRIGGER_8;
				अवरोध;
			शेष:
				fcr |= UART_FCR_TRIGGER_14;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* CTS flow control flag and modem status पूर्णांकerrupts */
	info->IER &= ~UART_IER_MSI;
	info->MCR &= ~UART_MCR_AFE;
	tty_port_set_cts_flow(&info->port, cflag & CRTSCTS);
	अगर (cflag & CRTSCTS) अणु
		info->IER |= UART_IER_MSI;
		अगर ((info->type == PORT_16550A) || (info->board->chip_flag)) अणु
			info->MCR |= UART_MCR_AFE;
		पूर्ण अन्यथा अणु
			status = inb(info->ioaddr + UART_MSR);
			अगर (tty->hw_stopped) अणु
				अगर (status & UART_MSR_CTS) अणु
					tty->hw_stopped = 0;
					अगर (info->type != PORT_16550A &&
							!info->board->chip_flag) अणु
						outb(info->IER & ~UART_IER_THRI,
							info->ioaddr +
							UART_IER);
						info->IER |= UART_IER_THRI;
						outb(info->IER, info->ioaddr +
								UART_IER);
					पूर्ण
					tty_wakeup(tty);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!(status & UART_MSR_CTS)) अणु
					tty->hw_stopped = 1;
					अगर ((info->type != PORT_16550A) &&
							(!info->board->chip_flag)) अणु
						info->IER &= ~UART_IER_THRI;
						outb(info->IER, info->ioaddr +
								UART_IER);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	outb(info->MCR, info->ioaddr + UART_MCR);
	tty_port_set_check_carrier(&info->port, ~cflag & CLOCAL);
	अगर (~cflag & CLOCAL)
		info->IER |= UART_IER_MSI;
	outb(info->IER, info->ioaddr + UART_IER);

	/*
	 * Set up parity check flag
	 */
	info->पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (I_INPCK(tty))
		info->पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (I_BRKINT(tty) || I_PARMRK(tty))
		info->पढ़ो_status_mask |= UART_LSR_BI;

	info->ignore_status_mask = 0;

	अगर (I_IGNBRK(tty)) अणु
		info->ignore_status_mask |= UART_LSR_BI;
		info->पढ़ो_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignore parity and अवरोध indicators, ignore
		 * overruns too.  (For real raw support).
		 */
		अगर (I_IGNPAR(tty)) अणु
			info->ignore_status_mask |=
						UART_LSR_OE |
						UART_LSR_PE |
						UART_LSR_FE;
			info->पढ़ो_status_mask |=
						UART_LSR_OE |
						UART_LSR_PE |
						UART_LSR_FE;
		पूर्ण
	पूर्ण
	अगर (info->board->chip_flag) अणु
		mxser_set_must_xon1_value(info->ioaddr, START_CHAR(tty));
		mxser_set_must_xoff1_value(info->ioaddr, STOP_CHAR(tty));
		अगर (I_IXON(tty)) अणु
			mxser_enable_must_rx_software_flow_control(
					info->ioaddr);
		पूर्ण अन्यथा अणु
			mxser_disable_must_rx_software_flow_control(
					info->ioaddr);
		पूर्ण
		अगर (I_IXOFF(tty)) अणु
			mxser_enable_must_tx_software_flow_control(
					info->ioaddr);
		पूर्ण अन्यथा अणु
			mxser_disable_must_tx_software_flow_control(
					info->ioaddr);
		पूर्ण
	पूर्ण


	outb(fcr, info->ioaddr + UART_FCR);	/* set fcr */
	outb(cval, info->ioaddr + UART_LCR);
पूर्ण

अटल व्योम mxser_check_modem_status(काष्ठा tty_काष्ठा *tty,
				काष्ठा mxser_port *port, पूर्णांक status)
अणु
	/* update input line counters */
	अगर (status & UART_MSR_TERI)
		port->icount.rng++;
	अगर (status & UART_MSR_DDSR)
		port->icount.dsr++;
	अगर (status & UART_MSR_DDCD)
		port->icount.dcd++;
	अगर (status & UART_MSR_DCTS)
		port->icount.cts++;
	port->mon_data.modem_status = status;
	wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);

	अगर (tty_port_check_carrier(&port->port) && (status & UART_MSR_DDCD)) अणु
		अगर (status & UART_MSR_DCD)
			wake_up_पूर्णांकerruptible(&port->port.खोलो_रुको);
	पूर्ण

	अगर (tty_port_cts_enabled(&port->port)) अणु
		अगर (tty->hw_stopped) अणु
			अगर (status & UART_MSR_CTS) अणु
				tty->hw_stopped = 0;

				अगर ((port->type != PORT_16550A) &&
						(!port->board->chip_flag)) अणु
					outb(port->IER & ~UART_IER_THRI,
						port->ioaddr + UART_IER);
					port->IER |= UART_IER_THRI;
					outb(port->IER, port->ioaddr +
							UART_IER);
				पूर्ण
				tty_wakeup(tty);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(status & UART_MSR_CTS)) अणु
				tty->hw_stopped = 1;
				अगर (port->type != PORT_16550A &&
						!port->board->chip_flag) अणु
					port->IER &= ~UART_IER_THRI;
					outb(port->IER, port->ioaddr +
							UART_IER);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mxser_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = container_of(port, काष्ठा mxser_port, port);
	अचिन्हित दीर्घ page;
	अचिन्हित दीर्घ flags;

	page = __get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	spin_lock_irqsave(&info->slock, flags);

	अगर (!info->ioaddr || !info->type) अणु
		set_bit(TTY_IO_ERROR, &tty->flags);
		मुक्त_page(page);
		spin_unlock_irqrestore(&info->slock, flags);
		वापस 0;
	पूर्ण
	info->port.xmit_buf = (अचिन्हित अक्षर *) page;

	/*
	 * Clear the FIFO buffers and disable them
	 * (they will be reenabled in mxser_change_speed())
	 */
	अगर (info->board->chip_flag)
		outb((UART_FCR_CLEAR_RCVR |
			UART_FCR_CLEAR_XMIT |
			MOXA_MUST_FCR_GDA_MODE_ENABLE), info->ioaddr + UART_FCR);
	अन्यथा
		outb((UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT),
			info->ioaddr + UART_FCR);

	/*
	 * At this poपूर्णांक there's no way the LSR could still be 0xFF;
	 * अगर it is, then bail out, because there's likely no UART
	 * here.
	 */
	अगर (inb(info->ioaddr + UART_LSR) == 0xff) अणु
		spin_unlock_irqrestore(&info->slock, flags);
		अगर (capable(CAP_SYS_ADMIN)) अणु
			set_bit(TTY_IO_ERROR, &tty->flags);
			वापस 0;
		पूर्ण अन्यथा
			वापस -ENODEV;
	पूर्ण

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	(व्योम) inb(info->ioaddr + UART_LSR);
	(व्योम) inb(info->ioaddr + UART_RX);
	(व्योम) inb(info->ioaddr + UART_IIR);
	(व्योम) inb(info->ioaddr + UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	outb(UART_LCR_WLEN8, info->ioaddr + UART_LCR);	/* reset DLAB */
	info->MCR = UART_MCR_DTR | UART_MCR_RTS;
	outb(info->MCR, info->ioaddr + UART_MCR);

	/*
	 * Finally, enable पूर्णांकerrupts
	 */
	info->IER = UART_IER_MSI | UART_IER_RLSI | UART_IER_RDI;

	अगर (info->board->chip_flag)
		info->IER |= MOXA_MUST_IER_EGDAI;
	outb(info->IER, info->ioaddr + UART_IER);	/* enable पूर्णांकerrupts */

	/*
	 * And clear the पूर्णांकerrupt रेजिस्टरs again क्रम luck.
	 */
	(व्योम) inb(info->ioaddr + UART_LSR);
	(व्योम) inb(info->ioaddr + UART_RX);
	(व्योम) inb(info->ioaddr + UART_IIR);
	(व्योम) inb(info->ioaddr + UART_MSR);

	clear_bit(TTY_IO_ERROR, &tty->flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;

	/*
	 * and set the speed of the serial port
	 */
	mxser_change_speed(tty);
	spin_unlock_irqrestore(&info->slock, flags);

	वापस 0;
पूर्ण

/*
 * This routine will shutकरोwn a serial port
 */
अटल व्योम mxser_shutकरोwn_port(काष्ठा tty_port *port)
अणु
	काष्ठा mxser_port *info = container_of(port, काष्ठा mxser_port, port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);

	/*
	 * clear delta_msr_रुको queue to aव्योम mem leaks: we may मुक्त the irq
	 * here so the queue might never be waken up
	 */
	wake_up_पूर्णांकerruptible(&info->port.delta_msr_रुको);

	/*
	 * Free the xmit buffer, अगर necessary
	 */
	अगर (info->port.xmit_buf) अणु
		मुक्त_page((अचिन्हित दीर्घ) info->port.xmit_buf);
		info->port.xmit_buf = शून्य;
	पूर्ण

	info->IER = 0;
	outb(0x00, info->ioaddr + UART_IER);

	/* clear Rx/Tx FIFO's */
	अगर (info->board->chip_flag)
		outb(UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT |
				MOXA_MUST_FCR_GDA_MODE_ENABLE,
				info->ioaddr + UART_FCR);
	अन्यथा
		outb(UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT,
			info->ioaddr + UART_FCR);

	/* पढ़ो data port to reset things */
	(व्योम) inb(info->ioaddr + UART_RX);


	अगर (info->board->chip_flag)
		SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL(info->ioaddr);

	spin_unlock_irqrestore(&info->slock, flags);
पूर्ण

/*
 * This routine is called whenever a serial port is खोलोed.  It
 * enables पूर्णांकerrupts क्रम a serial port, linking in its async काष्ठाure पूर्णांकo
 * the IRQ chain.   It also perक्रमms the serial-specअगरic
 * initialization क्रम the tty काष्ठाure.
 */
अटल पूर्णांक mxser_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा mxser_port *info;
	पूर्णांक line;

	line = tty->index;
	अगर (line == MXSER_PORTS)
		वापस 0;
	info = &mxser_boards[line / MXSER_PORTS_PER_BOARD].ports[line % MXSER_PORTS_PER_BOARD];
	अगर (!info->ioaddr)
		वापस -ENODEV;

	tty->driver_data = info;
	वापस tty_port_खोलो(&info->port, tty, filp);
पूर्ण

अटल व्योम mxser_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अक्षर fcr;
	अचिन्हित दीर्घ flags;


	spin_lock_irqsave(&info->slock, flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;

	fcr = inb(info->ioaddr + UART_FCR);
	outb((fcr | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT),
		info->ioaddr + UART_FCR);
	outb(fcr, info->ioaddr + UART_FCR);

	spin_unlock_irqrestore(&info->slock, flags);

	tty_wakeup(tty);
पूर्ण


अटल व्योम mxser_बंद_port(काष्ठा tty_port *port)
अणु
	काष्ठा mxser_port *info = container_of(port, काष्ठा mxser_port, port);
	अचिन्हित दीर्घ समयout;
	/*
	 * At this poपूर्णांक we stop accepting input.  To करो this, we
	 * disable the receive line status पूर्णांकerrupts, and tell the
	 * पूर्णांकerrupt driver to stop checking the data पढ़ोy bit in the
	 * line status रेजिस्टर.
	 */
	info->IER &= ~UART_IER_RLSI;
	अगर (info->board->chip_flag)
		info->IER &= ~MOXA_MUST_RECV_ISR;

	outb(info->IER, info->ioaddr + UART_IER);
	/*
	 * Beक्रमe we drop DTR, make sure the UART transmitter
	 * has completely drained; this is especially
	 * important अगर there is a transmit FIFO!
	 */
	समयout = jअगरfies + HZ;
	जबतक (!(inb(info->ioaddr + UART_LSR) & UART_LSR_TEMT)) अणु
		schedule_समयout_पूर्णांकerruptible(5);
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
	पूर्ण
पूर्ण

/*
 * This routine is called when the serial port माला_लो बंदd.  First, we
 * रुको क्रम the last reमुख्यing data to be sent.  Then, we unlink its
 * async काष्ठाure from the पूर्णांकerrupt chain अगर necessary, and we मुक्त
 * that IRQ अगर nothing is left in the chain.
 */
अटल व्योम mxser_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	काष्ठा tty_port *port = &info->port;

	अगर (tty->index == MXSER_PORTS || info == शून्य)
		वापस;
	अगर (tty_port_बंद_start(port, tty, filp) == 0)
		वापस;
	info->closing = 1;
	mutex_lock(&port->mutex);
	mxser_बंद_port(port);
	mxser_flush_buffer(tty);
	अगर (tty_port_initialized(port) && C_HUPCL(tty))
		tty_port_lower_dtr_rts(port);
	mxser_shutकरोwn_port(port);
	tty_port_set_initialized(port, 0);
	mutex_unlock(&port->mutex);
	info->closing = 0;
	/* Right now the tty_port set is करोne outside of the बंद_end helper
	   as we करोn't yet have everyone using refcounts */	
	tty_port_बंद_end(port, tty);
	tty_port_tty_set(port, शून्य);
पूर्ण

अटल पूर्णांक mxser_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक c, total = 0;
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (!info->port.xmit_buf)
		वापस 0;

	जबतक (1) अणु
		c = min_t(पूर्णांक, count, min(SERIAL_XMIT_SIZE - info->xmit_cnt - 1,
					  SERIAL_XMIT_SIZE - info->xmit_head));
		अगर (c <= 0)
			अवरोध;

		स_नकल(info->port.xmit_buf + info->xmit_head, buf, c);
		spin_lock_irqsave(&info->slock, flags);
		info->xmit_head = (info->xmit_head + c) &
				  (SERIAL_XMIT_SIZE - 1);
		info->xmit_cnt += c;
		spin_unlock_irqrestore(&info->slock, flags);

		buf += c;
		count -= c;
		total += c;
	पूर्ण

	अगर (info->xmit_cnt && !tty->stopped) अणु
		अगर (!tty->hw_stopped ||
				(info->type == PORT_16550A) ||
				(info->board->chip_flag)) अणु
			spin_lock_irqsave(&info->slock, flags);
			outb(info->IER & ~UART_IER_THRI, info->ioaddr +
					UART_IER);
			info->IER |= UART_IER_THRI;
			outb(info->IER, info->ioaddr + UART_IER);
			spin_unlock_irqrestore(&info->slock, flags);
		पूर्ण
	पूर्ण
	वापस total;
पूर्ण

अटल पूर्णांक mxser_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (!info->port.xmit_buf)
		वापस 0;

	अगर (info->xmit_cnt >= SERIAL_XMIT_SIZE - 1)
		वापस 0;

	spin_lock_irqsave(&info->slock, flags);
	info->port.xmit_buf[info->xmit_head++] = ch;
	info->xmit_head &= SERIAL_XMIT_SIZE - 1;
	info->xmit_cnt++;
	spin_unlock_irqrestore(&info->slock, flags);
	अगर (!tty->stopped) अणु
		अगर (!tty->hw_stopped ||
				(info->type == PORT_16550A) ||
				info->board->chip_flag) अणु
			spin_lock_irqsave(&info->slock, flags);
			outb(info->IER & ~UART_IER_THRI, info->ioaddr + UART_IER);
			info->IER |= UART_IER_THRI;
			outb(info->IER, info->ioaddr + UART_IER);
			spin_unlock_irqrestore(&info->slock, flags);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण


अटल व्योम mxser_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (info->xmit_cnt <= 0 || tty->stopped || !info->port.xmit_buf ||
			(tty->hw_stopped && info->type != PORT_16550A &&
			 !info->board->chip_flag))
		वापस;

	spin_lock_irqsave(&info->slock, flags);

	outb(info->IER & ~UART_IER_THRI, info->ioaddr + UART_IER);
	info->IER |= UART_IER_THRI;
	outb(info->IER, info->ioaddr + UART_IER);

	spin_unlock_irqrestore(&info->slock, flags);
पूर्ण

अटल पूर्णांक mxser_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	पूर्णांक ret;

	ret = SERIAL_XMIT_SIZE - info->xmit_cnt - 1;
	वापस ret < 0 ? 0 : ret;
पूर्ण

अटल पूर्णांक mxser_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	वापस info->xmit_cnt;
पूर्ण

/*
 * ------------------------------------------------------------
 * मित्रs of mxser_ioctl()
 * ------------------------------------------------------------
 */
अटल पूर्णांक mxser_get_serial_info(काष्ठा tty_काष्ठा *tty,
		काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	काष्ठा tty_port *port = &info->port;
	अचिन्हित पूर्णांक closing_रुको, बंद_delay;

	अगर (tty->index == MXSER_PORTS)
		वापस -ENOTTY;

	mutex_lock(&port->mutex);

	बंद_delay = jअगरfies_to_msecs(info->port.बंद_delay) / 10;
	closing_रुको = info->port.closing_रुको;
	अगर (closing_रुको != ASYNC_CLOSING_WAIT_NONE)
		closing_रुको = jअगरfies_to_msecs(closing_रुको) / 10;

	ss->type = info->type,
	ss->line = tty->index,
	ss->port = info->ioaddr,
	ss->irq = info->board->irq,
	ss->flags = info->port.flags,
	ss->baud_base = info->baud_base,
	ss->बंद_delay = बंद_delay;
	ss->closing_रुको = closing_रुको;
	ss->custom_भागisor = info->custom_भागisor,
	mutex_unlock(&port->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mxser_set_serial_info(काष्ठा tty_काष्ठा *tty,
		काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	काष्ठा tty_port *port = &info->port;
	speed_t baud;
	अचिन्हित दीर्घ sl_flags;
	अचिन्हित पूर्णांक flags, बंद_delay, closing_रुको;
	पूर्णांक retval = 0;

	अगर (tty->index == MXSER_PORTS)
		वापस -ENOTTY;
	अगर (tty_io_error(tty))
		वापस -EIO;

	mutex_lock(&port->mutex);
	अगर (!info->ioaddr) अणु
		mutex_unlock(&port->mutex);
		वापस -ENODEV;
	पूर्ण

	अगर (ss->irq != info->board->irq ||
			ss->port != info->ioaddr) अणु
		mutex_unlock(&port->mutex);
		वापस -EINVAL;
	पूर्ण

	flags = port->flags & ASYNC_SPD_MASK;

	बंद_delay = msecs_to_jअगरfies(ss->बंद_delay * 10);
	closing_रुको = ss->closing_रुको;
	अगर (closing_रुको != ASYNC_CLOSING_WAIT_NONE)
		closing_रुको = msecs_to_jअगरfies(closing_रुको * 10);

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		अगर ((ss->baud_base != info->baud_base) ||
				(बंद_delay != info->port.बंद_delay) ||
				(closing_रुको != info->port.closing_रुको) ||
				((ss->flags & ~ASYNC_USR_MASK) != (info->port.flags & ~ASYNC_USR_MASK))) अणु
			mutex_unlock(&port->mutex);
			वापस -EPERM;
		पूर्ण
		info->port.flags = ((info->port.flags & ~ASYNC_USR_MASK) |
				(ss->flags & ASYNC_USR_MASK));
	पूर्ण अन्यथा अणु
		/*
		 * OK, past this poपूर्णांक, all the error checking has been करोne.
		 * At this poपूर्णांक, we start making changes.....
		 */
		port->flags = ((port->flags & ~ASYNC_FLAGS) |
				(ss->flags & ASYNC_FLAGS));
		port->बंद_delay = बंद_delay;
		port->closing_रुको = closing_रुको;
		अगर ((port->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST &&
				(ss->baud_base != info->baud_base ||
				ss->custom_भागisor !=
				info->custom_भागisor)) अणु
			अगर (ss->custom_भागisor == 0) अणु
				mutex_unlock(&port->mutex);
				वापस -EINVAL;
			पूर्ण
			baud = ss->baud_base / ss->custom_भागisor;
			tty_encode_baud_rate(tty, baud, baud);
		पूर्ण

		info->type = ss->type;

		process_txrx_fअगरo(info);
	पूर्ण

	अगर (tty_port_initialized(port)) अणु
		अगर (flags != (port->flags & ASYNC_SPD_MASK)) अणु
			spin_lock_irqsave(&info->slock, sl_flags);
			mxser_change_speed(tty);
			spin_unlock_irqrestore(&info->slock, sl_flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = mxser_activate(port, tty);
		अगर (retval == 0)
			tty_port_set_initialized(port, 1);
	पूर्ण
	mutex_unlock(&port->mutex);
	वापस retval;
पूर्ण

/*
 * mxser_get_lsr_info - get line status रेजिस्टर info
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 *	    is emptied.  On bus types like RS485, the transmitter must
 *	    release the bus after transmitting. This must be करोne when
 *	    the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 *	    transmit holding रेजिस्टर is empty.  This functionality
 *	    allows an RS485 driver to be written in user space.
 */
अटल पूर्णांक mxser_get_lsr_info(काष्ठा mxser_port *info,
		अचिन्हित पूर्णांक __user *value)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);
	status = inb(info->ioaddr + UART_LSR);
	spin_unlock_irqrestore(&info->slock, flags);
	result = ((status & UART_LSR_TEMT) ? TIOCSER_TEMT : 0);
	वापस put_user(result, value);
पूर्ण

अटल पूर्णांक mxser_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित अक्षर control, status;
	अचिन्हित दीर्घ flags;


	अगर (tty->index == MXSER_PORTS)
		वापस -ENOIOCTLCMD;
	अगर (tty_io_error(tty))
		वापस -EIO;

	control = info->MCR;

	spin_lock_irqsave(&info->slock, flags);
	status = inb(info->ioaddr + UART_MSR);
	अगर (status & UART_MSR_ANY_DELTA)
		mxser_check_modem_status(tty, info, status);
	spin_unlock_irqrestore(&info->slock, flags);
	वापस ((control & UART_MCR_RTS) ? TIOCM_RTS : 0) |
		    ((control & UART_MCR_DTR) ? TIOCM_DTR : 0) |
		    ((status & UART_MSR_DCD) ? TIOCM_CAR : 0) |
		    ((status & UART_MSR_RI) ? TIOCM_RNG : 0) |
		    ((status & UART_MSR_DSR) ? TIOCM_DSR : 0) |
		    ((status & UART_MSR_CTS) ? TIOCM_CTS : 0);
पूर्ण

अटल पूर्णांक mxser_tiocmset(काष्ठा tty_काष्ठा *tty,
		अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;


	अगर (tty->index == MXSER_PORTS)
		वापस -ENOIOCTLCMD;
	अगर (tty_io_error(tty))
		वापस -EIO;

	spin_lock_irqsave(&info->slock, flags);

	अगर (set & TIOCM_RTS)
		info->MCR |= UART_MCR_RTS;
	अगर (set & TIOCM_DTR)
		info->MCR |= UART_MCR_DTR;

	अगर (clear & TIOCM_RTS)
		info->MCR &= ~UART_MCR_RTS;
	अगर (clear & TIOCM_DTR)
		info->MCR &= ~UART_MCR_DTR;

	outb(info->MCR, info->ioaddr + UART_MCR);
	spin_unlock_irqrestore(&info->slock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक __init mxser_program_mode(पूर्णांक port)
अणु
	पूर्णांक id, i, j, n;

	outb(0, port);
	outb(0, port);
	outb(0, port);
	(व्योम)inb(port);
	(व्योम)inb(port);
	outb(0, port);
	(व्योम)inb(port);

	id = inb(port + 1) & 0x1F;
	अगर ((id != C168_ASIC_ID) &&
			(id != C104_ASIC_ID) &&
			(id != C102_ASIC_ID) &&
			(id != CI132_ASIC_ID) &&
			(id != CI134_ASIC_ID) &&
			(id != CI104J_ASIC_ID))
		वापस -1;
	क्रम (i = 0, j = 0; i < 4; i++) अणु
		n = inb(port + 2);
		अगर (n == 'M') अणु
			j = 1;
		पूर्ण अन्यथा अगर ((j == 1) && (n == 1)) अणु
			j = 2;
			अवरोध;
		पूर्ण अन्यथा
			j = 0;
	पूर्ण
	अगर (j != 2)
		id = -2;
	वापस id;
पूर्ण

अटल व्योम __init mxser_normal_mode(पूर्णांक port)
अणु
	पूर्णांक i, n;

	outb(0xA5, port + 1);
	outb(0x80, port + 3);
	outb(12, port + 0);	/* 9600 bps */
	outb(0, port + 1);
	outb(0x03, port + 3);	/* 8 data bits */
	outb(0x13, port + 4);	/* loop back mode */
	क्रम (i = 0; i < 16; i++) अणु
		n = inb(port + 5);
		अगर ((n & 0x61) == 0x60)
			अवरोध;
		अगर ((n & 1) == 1)
			(व्योम)inb(port);
	पूर्ण
	outb(0x00, port + 4);
पूर्ण

#घोषणा CHIP_SK 	0x01	/* Serial Data Clock  in Eprom */
#घोषणा CHIP_DO 	0x02	/* Serial Data Output in Eprom */
#घोषणा CHIP_CS 	0x04	/* Serial Chip Select in Eprom */
#घोषणा CHIP_DI 	0x08	/* Serial Data Input  in Eprom */
#घोषणा EN_CCMD 	0x000	/* Chip's command रेजिस्टर     */
#घोषणा EN0_RSARLO	0x008	/* Remote start address reg 0  */
#घोषणा EN0_RSARHI	0x009	/* Remote start address reg 1  */
#घोषणा EN0_RCNTLO	0x00A	/* Remote byte count reg WR    */
#घोषणा EN0_RCNTHI	0x00B	/* Remote byte count reg WR    */
#घोषणा EN0_DCFG	0x00E	/* Data configuration reg WR   */
#घोषणा EN0_PORT	0x010	/* Rcv missed frame error counter RD */
#घोषणा ENC_PAGE0	0x000	/* Select page 0 of chip रेजिस्टरs   */
#घोषणा ENC_PAGE3	0x0C0	/* Select page 3 of chip रेजिस्टरs   */
अटल पूर्णांक __init mxser_पढ़ो_रेजिस्टर(पूर्णांक port, अचिन्हित लघु *regs)
अणु
	पूर्णांक i, k, value, id;
	अचिन्हित पूर्णांक j;

	id = mxser_program_mode(port);
	अगर (id < 0)
		वापस id;
	क्रम (i = 0; i < 14; i++) अणु
		k = (i & 0x3F) | 0x180;
		क्रम (j = 0x100; j > 0; j >>= 1) अणु
			outb(CHIP_CS, port);
			अगर (k & j) अणु
				outb(CHIP_CS | CHIP_DO, port);
				outb(CHIP_CS | CHIP_DO | CHIP_SK, port);	/* A? bit of पढ़ो */
			पूर्ण अन्यथा अणु
				outb(CHIP_CS, port);
				outb(CHIP_CS | CHIP_SK, port);	/* A? bit of पढ़ो */
			पूर्ण
		पूर्ण
		(व्योम)inb(port);
		value = 0;
		क्रम (k = 0, j = 0x8000; k < 16; k++, j >>= 1) अणु
			outb(CHIP_CS, port);
			outb(CHIP_CS | CHIP_SK, port);
			अगर (inb(port) & CHIP_DI)
				value |= j;
		पूर्ण
		regs[i] = value;
		outb(0, port);
	पूर्ण
	mxser_normal_mode(port);
	वापस id;
पूर्ण

अटल पूर्णांक mxser_ioctl_special(अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा mxser_port *ip;
	काष्ठा tty_port *port;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक result, status;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल MOXA_GET_MAJOR:
		prपूर्णांकk_ratelimited(KERN_WARNING "mxser: '%s' uses deprecated ioctl "
					"%x (GET_MAJOR), fix your userspace\n",
					current->comm, cmd);
		वापस put_user(ttymajor, (पूर्णांक __user *)argp);

	हाल MOXA_CHKPORTENABLE:
		result = 0;
		क्रम (i = 0; i < MXSER_BOARDS; i++)
			क्रम (j = 0; j < MXSER_PORTS_PER_BOARD; j++)
				अगर (mxser_boards[i].ports[j].ioaddr)
					result |= (1 << i);
		वापस put_user(result, (अचिन्हित दीर्घ __user *)argp);
	हाल MOXA_GETDATACOUNT:
		/* The receive side is locked by port->slock but it isn't
		   clear that an exact snapshot is worth copying here */
		अगर (copy_to_user(argp, &mxvar_log, माप(mxvar_log)))
			ret = -EFAULT;
		वापस ret;
	हाल MOXA_GETMSTATUS: अणु
		काष्ठा mxser_mstatus ms, __user *msu = argp;
		क्रम (i = 0; i < MXSER_BOARDS; i++)
			क्रम (j = 0; j < MXSER_PORTS_PER_BOARD; j++) अणु
				ip = &mxser_boards[i].ports[j];
				port = &ip->port;
				स_रखो(&ms, 0, माप(ms));

				mutex_lock(&port->mutex);
				अगर (!ip->ioaddr)
					जाओ copy;
				
				tty = tty_port_tty_get(port);

				अगर (!tty)
					ms.cflag = ip->normal_termios.c_cflag;
				अन्यथा
					ms.cflag = tty->termios.c_cflag;
				tty_kref_put(tty);
				spin_lock_irq(&ip->slock);
				status = inb(ip->ioaddr + UART_MSR);
				spin_unlock_irq(&ip->slock);
				अगर (status & UART_MSR_DCD)
					ms.dcd = 1;
				अगर (status & UART_MSR_DSR)
					ms.dsr = 1;
				अगर (status & UART_MSR_CTS)
					ms.cts = 1;
			copy:
				mutex_unlock(&port->mutex);
				अगर (copy_to_user(msu, &ms, माप(ms)))
					वापस -EFAULT;
				msu++;
			पूर्ण
		वापस 0;
	पूर्ण
	हाल MOXA_ASPP_MON_EXT: अणु
		काष्ठा mxser_mon_ext *me; /* it's 2k, stack unमित्रly */
		अचिन्हित पूर्णांक cflag, अगरlag, p;
		u8 opmode;

		me = kzalloc(माप(*me), GFP_KERNEL);
		अगर (!me)
			वापस -ENOMEM;

		क्रम (i = 0, p = 0; i < MXSER_BOARDS; i++) अणु
			क्रम (j = 0; j < MXSER_PORTS_PER_BOARD; j++, p++) अणु
				अगर (p >= ARRAY_SIZE(me->rx_cnt)) अणु
					i = MXSER_BOARDS;
					अवरोध;
				पूर्ण
				ip = &mxser_boards[i].ports[j];
				port = &ip->port;

				mutex_lock(&port->mutex);
				अगर (!ip->ioaddr) अणु
					mutex_unlock(&port->mutex);
					जारी;
				पूर्ण

				spin_lock_irq(&ip->slock);
				status = mxser_get_msr(ip->ioaddr, 0, p);

				अगर (status & UART_MSR_TERI)
					ip->icount.rng++;
				अगर (status & UART_MSR_DDSR)
					ip->icount.dsr++;
				अगर (status & UART_MSR_DDCD)
					ip->icount.dcd++;
				अगर (status & UART_MSR_DCTS)
					ip->icount.cts++;

				ip->mon_data.modem_status = status;
				me->rx_cnt[p] = ip->mon_data.rxcnt;
				me->tx_cnt[p] = ip->mon_data.txcnt;
				me->up_rxcnt[p] = ip->mon_data.up_rxcnt;
				me->up_txcnt[p] = ip->mon_data.up_txcnt;
				me->modem_status[p] =
					ip->mon_data.modem_status;
				spin_unlock_irq(&ip->slock);

				tty = tty_port_tty_get(&ip->port);

				अगर (!tty) अणु
					cflag = ip->normal_termios.c_cflag;
					अगरlag = ip->normal_termios.c_अगरlag;
					me->baudrate[p] = tty_termios_baud_rate(&ip->normal_termios);
				पूर्ण अन्यथा अणु
					cflag = tty->termios.c_cflag;
					अगरlag = tty->termios.c_अगरlag;
					me->baudrate[p] = tty_get_baud_rate(tty);
				पूर्ण
				tty_kref_put(tty);

				me->databits[p] = cflag & CSIZE;
				me->stopbits[p] = cflag & CSTOPB;
				me->parity[p] = cflag & (PARENB | PARODD |
						CMSPAR);

				अगर (cflag & CRTSCTS)
					me->flowctrl[p] |= 0x03;

				अगर (अगरlag & (IXON | IXOFF))
					me->flowctrl[p] |= 0x0C;

				अगर (ip->type == PORT_16550A)
					me->fअगरo[p] = 1;

				अगर (ip->board->chip_flag == MOXA_MUST_MU860_HWID) अणु
					opmode = inb(ip->opmode_ioaddr)>>((p % 4) * 2);
					opmode &= OP_MODE_MASK;
				पूर्ण अन्यथा अणु
					opmode = RS232_MODE;
				पूर्ण
				me->अगरtype[p] = opmode;
				mutex_unlock(&port->mutex);
			पूर्ण
		पूर्ण
		अगर (copy_to_user(argp, me, माप(*me)))
			ret = -EFAULT;
		kमुक्त(me);
		वापस ret;
	पूर्ण
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxser_cflags_changed(काष्ठा mxser_port *info, अचिन्हित दीर्घ arg,
		काष्ठा async_icount *cprev)
अणु
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&info->slock, flags);
	cnow = info->icount;	/* atomic copy */
	spin_unlock_irqrestore(&info->slock, flags);

	ret =	((arg & TIOCM_RNG) && (cnow.rng != cprev->rng)) ||
		((arg & TIOCM_DSR) && (cnow.dsr != cprev->dsr)) ||
		((arg & TIOCM_CD)  && (cnow.dcd != cprev->dcd)) ||
		((arg & TIOCM_CTS) && (cnow.cts != cprev->cts));

	*cprev = cnow;

	वापस ret;
पूर्ण

अटल पूर्णांक mxser_ioctl(काष्ठा tty_काष्ठा *tty,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (tty->index == MXSER_PORTS)
		वापस mxser_ioctl_special(cmd, argp);

	अगर (cmd == MOXA_SET_OP_MODE || cmd == MOXA_GET_OP_MODE) अणु
		पूर्णांक p;
		अचिन्हित दीर्घ opmode;
		अटल अचिन्हित अक्षर ModeMask[] = अणु 0xfc, 0xf3, 0xcf, 0x3f पूर्ण;
		पूर्णांक shअगरtbit;
		अचिन्हित अक्षर val, mask;

		अगर (info->board->chip_flag != MOXA_MUST_MU860_HWID)
			वापस -EFAULT;

		p = tty->index % 4;
		अगर (cmd == MOXA_SET_OP_MODE) अणु
			अगर (get_user(opmode, (पूर्णांक __user *) argp))
				वापस -EFAULT;
			अगर (opmode != RS232_MODE &&
					opmode != RS485_2WIRE_MODE &&
					opmode != RS422_MODE &&
					opmode != RS485_4WIRE_MODE)
				वापस -EFAULT;
			mask = ModeMask[p];
			shअगरtbit = p * 2;
			spin_lock_irq(&info->slock);
			val = inb(info->opmode_ioaddr);
			val &= mask;
			val |= (opmode << shअगरtbit);
			outb(val, info->opmode_ioaddr);
			spin_unlock_irq(&info->slock);
		पूर्ण अन्यथा अणु
			shअगरtbit = p * 2;
			spin_lock_irq(&info->slock);
			opmode = inb(info->opmode_ioaddr) >> shअगरtbit;
			spin_unlock_irq(&info->slock);
			opmode &= OP_MODE_MASK;
			अगर (put_user(opmode, (पूर्णांक __user *)argp))
				वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (cmd != TIOCMIWAIT && tty_io_error(tty))
		वापस -EIO;

	चयन (cmd) अणु
	हाल TIOCSERGETLSR:	/* Get line status रेजिस्टर */
		वापस  mxser_get_lsr_info(info, argp);
		/*
		 * Wait क्रम any of the 4 modem inमाला_दो (DCD,RI,DSR,CTS) to change
		 * - mask passed in arg क्रम lines of पूर्णांकerest
		 *   (use |'ed TIOCM_RNG/DSR/CD/CTS क्रम masking)
		 * Caller should use TIOCGICOUNT to see which one it was
		 */
	हाल TIOCMIWAIT:
		spin_lock_irqsave(&info->slock, flags);
		cnow = info->icount;	/* note the counters on entry */
		spin_unlock_irqrestore(&info->slock, flags);

		वापस रुको_event_पूर्णांकerruptible(info->port.delta_msr_रुको,
				mxser_cflags_changed(info, arg, &cnow));
	हाल MOXA_HighSpeedOn:
		वापस put_user(info->baud_base != 115200 ? 1 : 0, (पूर्णांक __user *)argp);
	हाल MOXA_SDS_RSTICOUNTER:
		spin_lock_irq(&info->slock);
		info->mon_data.rxcnt = 0;
		info->mon_data.txcnt = 0;
		spin_unlock_irq(&info->slock);
		वापस 0;

	हाल MOXA_ASPP_OQUEUE:अणु
		पूर्णांक len, lsr;

		len = mxser_अक्षरs_in_buffer(tty);
		spin_lock_irq(&info->slock);
		lsr = inb(info->ioaddr + UART_LSR) & UART_LSR_THRE;
		spin_unlock_irq(&info->slock);
		len += (lsr ? 0 : 1);

		वापस put_user(len, (पूर्णांक __user *)argp);
	पूर्ण
	हाल MOXA_ASPP_MON: अणु
		पूर्णांक mcr, status;

		spin_lock_irq(&info->slock);
		status = mxser_get_msr(info->ioaddr, 1, tty->index);
		mxser_check_modem_status(tty, info, status);

		mcr = inb(info->ioaddr + UART_MCR);
		spin_unlock_irq(&info->slock);

		अगर (mcr & MOXA_MUST_MCR_XON_FLAG)
			info->mon_data.hold_reason &= ~NPPI_NOTIFY_XOFFHOLD;
		अन्यथा
			info->mon_data.hold_reason |= NPPI_NOTIFY_XOFFHOLD;

		अगर (mcr & MOXA_MUST_MCR_TX_XON)
			info->mon_data.hold_reason &= ~NPPI_NOTIFY_XOFFXENT;
		अन्यथा
			info->mon_data.hold_reason |= NPPI_NOTIFY_XOFFXENT;

		अगर (tty->hw_stopped)
			info->mon_data.hold_reason |= NPPI_NOTIFY_CTSHOLD;
		अन्यथा
			info->mon_data.hold_reason &= ~NPPI_NOTIFY_CTSHOLD;

		अगर (copy_to_user(argp, &info->mon_data,
				माप(काष्ठा mxser_mon)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल MOXA_ASPP_LSTATUS: अणु
		अगर (put_user(info->err_shaकरोw, (अचिन्हित अक्षर __user *)argp))
			वापस -EFAULT;

		info->err_shaकरोw = 0;
		वापस 0;
	पूर्ण
	हाल MOXA_SET_BAUD_METHOD: अणु
		पूर्णांक method;

		अगर (get_user(method, (पूर्णांक __user *)argp))
			वापस -EFAULT;
		mxser_set_baud_method[tty->index] = method;
		वापस put_user(method, (पूर्णांक __user *)argp);
	पूर्ण
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

	/*
	 * Get counter of input serial line पूर्णांकerrupts (DCD,RI,DSR,CTS)
	 * Return: ग_लिखो counters to the user passed counter काष्ठा
	 * NB: both 1->0 and 0->1 transitions are counted except क्रम
	 *     RI where only 0->1 is counted.
	 */

अटल पूर्णांक mxser_get_icount(काष्ठा tty_काष्ठा *tty,
		काष्ठा serial_icounter_काष्ठा *icount)

अणु
	काष्ठा mxser_port *info = tty->driver_data;
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);
	cnow = info->icount;
	spin_unlock_irqrestore(&info->slock, flags);

	icount->frame = cnow.frame;
	icount->brk = cnow.brk;
	icount->overrun = cnow.overrun;
	icount->buf_overrun = cnow.buf_overrun;
	icount->parity = cnow.parity;
	icount->rx = cnow.rx;
	icount->tx = cnow.tx;
	icount->cts = cnow.cts;
	icount->dsr = cnow.dsr;
	icount->rng = cnow.rng;
	icount->dcd = cnow.dcd;
	वापस 0;
पूर्ण

अटल व्योम mxser_stoprx(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;

	info->ldisc_stop_rx = 1;
	अगर (I_IXOFF(tty)) अणु
		अगर (info->board->chip_flag) अणु
			info->IER &= ~MOXA_MUST_RECV_ISR;
			outb(info->IER, info->ioaddr + UART_IER);
		पूर्ण अन्यथा अणु
			info->x_अक्षर = STOP_CHAR(tty);
			outb(0, info->ioaddr + UART_IER);
			info->IER |= UART_IER_THRI;
			outb(info->IER, info->ioaddr + UART_IER);
		पूर्ण
	पूर्ण

	अगर (C_CRTSCTS(tty)) अणु
		info->MCR &= ~UART_MCR_RTS;
		outb(info->MCR, info->ioaddr + UART_MCR);
	पूर्ण
पूर्ण

/*
 * This routine is called by the upper-layer tty layer to संकेत that
 * incoming अक्षरacters should be throttled.
 */
अटल व्योम mxser_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	mxser_stoprx(tty);
पूर्ण

अटल व्योम mxser_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;

	/* startrx */
	info->ldisc_stop_rx = 0;
	अगर (I_IXOFF(tty)) अणु
		अगर (info->x_अक्षर)
			info->x_अक्षर = 0;
		अन्यथा अणु
			अगर (info->board->chip_flag) अणु
				info->IER |= MOXA_MUST_RECV_ISR;
				outb(info->IER, info->ioaddr + UART_IER);
			पूर्ण अन्यथा अणु
				info->x_अक्षर = START_CHAR(tty);
				outb(0, info->ioaddr + UART_IER);
				info->IER |= UART_IER_THRI;
				outb(info->IER, info->ioaddr + UART_IER);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (C_CRTSCTS(tty)) अणु
		info->MCR |= UART_MCR_RTS;
		outb(info->MCR, info->ioaddr + UART_MCR);
	पूर्ण
पूर्ण

/*
 * mxser_stop() and mxser_start()
 *
 * This routines are called beक्रमe setting or resetting tty->stopped.
 * They enable or disable transmitter पूर्णांकerrupts, as necessary.
 */
अटल व्योम mxser_stop(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);
	अगर (info->IER & UART_IER_THRI) अणु
		info->IER &= ~UART_IER_THRI;
		outb(info->IER, info->ioaddr + UART_IER);
	पूर्ण
	spin_unlock_irqrestore(&info->slock, flags);
पूर्ण

अटल व्योम mxser_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);
	अगर (info->xmit_cnt && info->port.xmit_buf) अणु
		outb(info->IER & ~UART_IER_THRI, info->ioaddr + UART_IER);
		info->IER |= UART_IER_THRI;
		outb(info->IER, info->ioaddr + UART_IER);
	पूर्ण
	spin_unlock_irqrestore(&info->slock, flags);
पूर्ण

अटल व्योम mxser_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old_termios)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);
	mxser_change_speed(tty);
	spin_unlock_irqrestore(&info->slock, flags);

	अगर ((old_termios->c_cflag & CRTSCTS) && !C_CRTSCTS(tty)) अणु
		tty->hw_stopped = 0;
		mxser_start(tty);
	पूर्ण

	/* Handle sw stopped */
	अगर ((old_termios->c_अगरlag & IXON) && !I_IXON(tty)) अणु
		tty->stopped = 0;

		अगर (info->board->chip_flag) अणु
			spin_lock_irqsave(&info->slock, flags);
			mxser_disable_must_rx_software_flow_control(
					info->ioaddr);
			spin_unlock_irqrestore(&info->slock, flags);
		पूर्ण

		mxser_start(tty);
	पूर्ण
पूर्ण

/*
 * mxser_रुको_until_sent() --- रुको until the transmitter is empty
 */
अटल व्योम mxser_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ orig_jअगरfies, अक्षर_समय;
	अचिन्हित दीर्घ flags;
	पूर्णांक lsr;

	अगर (info->type == PORT_UNKNOWN)
		वापस;

	अगर (info->xmit_fअगरo_size == 0)
		वापस;		/* Just in हाल.... */

	orig_jअगरfies = jअगरfies;
	/*
	 * Set the check पूर्णांकerval to be 1/5 of the estimated समय to
	 * send a single अक्षरacter, and make it at least 1.  The check
	 * पूर्णांकerval should also be less than the समयout.
	 *
	 * Note: we have to use pretty tight timings here to satisfy
	 * the NIST-PCTS.
	 */
	अक्षर_समय = (info->समयout - HZ / 50) / info->xmit_fअगरo_size;
	अक्षर_समय = अक्षर_समय / 5;
	अगर (अक्षर_समय == 0)
		अक्षर_समय = 1;
	अगर (समयout && समयout < अक्षर_समय)
		अक्षर_समय = समयout;
	/*
	 * If the transmitter hasn't cleared in twice the approximate
	 * amount of समय to send the entire FIFO, it probably won't
	 * ever clear.  This assumes the UART isn't करोing flow
	 * control, which is currently the हाल.  Hence, अगर it ever
	 * takes दीर्घer than info->समयout, this is probably due to a
	 * UART bug of some kind.  So, we clamp the समयout parameter at
	 * 2*info->समयout.
	 */
	अगर (!समयout || समयout > 2 * info->समयout)
		समयout = 2 * info->समयout;

	spin_lock_irqsave(&info->slock, flags);
	जबतक (!((lsr = inb(info->ioaddr + UART_LSR)) & UART_LSR_TEMT)) अणु
		spin_unlock_irqrestore(&info->slock, flags);
		schedule_समयout_पूर्णांकerruptible(अक्षर_समय);
		spin_lock_irqsave(&info->slock, flags);
		अगर (संकेत_pending(current))
			अवरोध;
		अगर (समयout && समय_after(jअगरfies, orig_jअगरfies + समयout))
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&info->slock, flags);
	set_current_state(TASK_RUNNING);
पूर्ण

/*
 * This routine is called by tty_hangup() when a hangup is संकेतed.
 */
अटल व्योम mxser_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mxser_port *info = tty->driver_data;

	mxser_flush_buffer(tty);
	tty_port_hangup(&info->port);
पूर्ण

/*
 * mxser_rs_अवरोध() --- routine which turns the अवरोध handling on or off
 */
अटल पूर्णांक mxser_rs_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा mxser_port *info = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&info->slock, flags);
	अगर (अवरोध_state == -1)
		outb(inb(info->ioaddr + UART_LCR) | UART_LCR_SBC,
			info->ioaddr + UART_LCR);
	अन्यथा
		outb(inb(info->ioaddr + UART_LCR) & ~UART_LCR_SBC,
			info->ioaddr + UART_LCR);
	spin_unlock_irqrestore(&info->slock, flags);
	वापस 0;
पूर्ण

अटल व्योम mxser_receive_अक्षरs(काष्ठा tty_काष्ठा *tty,
				काष्ठा mxser_port *port, पूर्णांक *status)
अणु
	अचिन्हित अक्षर ch, gdl;
	पूर्णांक ignored = 0;
	पूर्णांक cnt = 0;
	पूर्णांक recv_room;
	पूर्णांक max = 256;

	recv_room = tty->receive_room;
	अगर (recv_room == 0 && !port->ldisc_stop_rx)
		mxser_stoprx(tty);
	अगर (port->board->chip_flag != MOXA_OTHER_UART) अणु

		अगर (*status & UART_LSR_SPECIAL)
			जाओ पूर्णांकr_old;
		अगर (port->board->chip_flag == MOXA_MUST_MU860_HWID &&
				(*status & MOXA_MUST_LSR_RERR))
			जाओ पूर्णांकr_old;
		अगर (*status & MOXA_MUST_LSR_RERR)
			जाओ पूर्णांकr_old;

		gdl = inb(port->ioaddr + MOXA_MUST_GDL_REGISTER);

		अगर (port->board->chip_flag == MOXA_MUST_MU150_HWID)
			gdl &= MOXA_MUST_GDL_MASK;
		अगर (gdl >= recv_room) अणु
			अगर (!port->ldisc_stop_rx)
				mxser_stoprx(tty);
		पूर्ण
		जबतक (gdl--) अणु
			ch = inb(port->ioaddr + UART_RX);
			tty_insert_flip_अक्षर(&port->port, ch, 0);
			cnt++;
		पूर्ण
		जाओ end_पूर्णांकr;
	पूर्ण
पूर्णांकr_old:

	करो अणु
		अगर (max-- < 0)
			अवरोध;

		ch = inb(port->ioaddr + UART_RX);
		अगर (port->board->chip_flag && (*status & UART_LSR_OE))
			outb(0x23, port->ioaddr + UART_FCR);
		*status &= port->पढ़ो_status_mask;
		अगर (*status & port->ignore_status_mask) अणु
			अगर (++ignored > 100)
				अवरोध;
		पूर्ण अन्यथा अणु
			अक्षर flag = 0;
			अगर (*status & UART_LSR_SPECIAL) अणु
				अगर (*status & UART_LSR_BI) अणु
					flag = TTY_BREAK;
					port->icount.brk++;

					अगर (port->port.flags & ASYNC_SAK)
						करो_SAK(tty);
				पूर्ण अन्यथा अगर (*status & UART_LSR_PE) अणु
					flag = TTY_PARITY;
					port->icount.parity++;
				पूर्ण अन्यथा अगर (*status & UART_LSR_FE) अणु
					flag = TTY_FRAME;
					port->icount.frame++;
				पूर्ण अन्यथा अगर (*status & UART_LSR_OE) अणु
					flag = TTY_OVERRUN;
					port->icount.overrun++;
				पूर्ण अन्यथा
					flag = TTY_BREAK;
			पूर्ण
			tty_insert_flip_अक्षर(&port->port, ch, flag);
			cnt++;
			अगर (cnt >= recv_room) अणु
				अगर (!port->ldisc_stop_rx)
					mxser_stoprx(tty);
				अवरोध;
			पूर्ण

		पूर्ण

		अगर (port->board->chip_flag)
			अवरोध;

		*status = inb(port->ioaddr + UART_LSR);
	पूर्ण जबतक (*status & UART_LSR_DR);

end_पूर्णांकr:
	mxvar_log.rxcnt[tty->index] += cnt;
	port->mon_data.rxcnt += cnt;
	port->mon_data.up_rxcnt += cnt;

	tty_flip_buffer_push(&port->port);
पूर्ण

अटल व्योम mxser_transmit_अक्षरs(काष्ठा tty_काष्ठा *tty, काष्ठा mxser_port *port)
अणु
	पूर्णांक count, cnt;

	अगर (port->x_अक्षर) अणु
		outb(port->x_अक्षर, port->ioaddr + UART_TX);
		port->x_अक्षर = 0;
		mxvar_log.txcnt[tty->index]++;
		port->mon_data.txcnt++;
		port->mon_data.up_txcnt++;
		port->icount.tx++;
		वापस;
	पूर्ण

	अगर (port->port.xmit_buf == शून्य)
		वापस;

	अगर (port->xmit_cnt <= 0 || tty->stopped ||
			(tty->hw_stopped &&
			(port->type != PORT_16550A) &&
			(!port->board->chip_flag))) अणु
		port->IER &= ~UART_IER_THRI;
		outb(port->IER, port->ioaddr + UART_IER);
		वापस;
	पूर्ण

	cnt = port->xmit_cnt;
	count = port->xmit_fअगरo_size;
	करो अणु
		outb(port->port.xmit_buf[port->xmit_tail++],
			port->ioaddr + UART_TX);
		port->xmit_tail = port->xmit_tail & (SERIAL_XMIT_SIZE - 1);
		अगर (--port->xmit_cnt <= 0)
			अवरोध;
	पूर्ण जबतक (--count > 0);
	mxvar_log.txcnt[tty->index] += (cnt - port->xmit_cnt);

	port->mon_data.txcnt += (cnt - port->xmit_cnt);
	port->mon_data.up_txcnt += (cnt - port->xmit_cnt);
	port->icount.tx += (cnt - port->xmit_cnt);

	अगर (port->xmit_cnt < WAKEUP_CHARS)
		tty_wakeup(tty);

	अगर (port->xmit_cnt <= 0) अणु
		port->IER &= ~UART_IER_THRI;
		outb(port->IER, port->ioaddr + UART_IER);
	पूर्ण
पूर्ण

/*
 * This is the serial driver's generic पूर्णांकerrupt routine
 */
अटल irqवापस_t mxser_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक status, iir, i;
	काष्ठा mxser_board *brd = शून्य;
	काष्ठा mxser_port *port;
	पूर्णांक max, irqbits, bits, msr;
	अचिन्हित पूर्णांक पूर्णांक_cnt, pass_counter = 0;
	पूर्णांक handled = IRQ_NONE;
	काष्ठा tty_काष्ठा *tty;

	क्रम (i = 0; i < MXSER_BOARDS; i++)
		अगर (dev_id == &mxser_boards[i]) अणु
			brd = dev_id;
			अवरोध;
		पूर्ण

	अगर (i == MXSER_BOARDS)
		जाओ irq_stop;
	अगर (brd == शून्य)
		जाओ irq_stop;
	max = brd->info->nports;
	जबतक (pass_counter++ < MXSER_ISR_PASS_LIMIT) अणु
		irqbits = inb(brd->vector) & brd->vector_mask;
		अगर (irqbits == brd->vector_mask)
			अवरोध;

		handled = IRQ_HANDLED;
		क्रम (i = 0, bits = 1; i < max; i++, irqbits |= bits, bits <<= 1) अणु
			अगर (irqbits == brd->vector_mask)
				अवरोध;
			अगर (bits & irqbits)
				जारी;
			port = &brd->ports[i];

			पूर्णांक_cnt = 0;
			spin_lock(&port->slock);
			करो अणु
				iir = inb(port->ioaddr + UART_IIR);
				अगर (iir & UART_IIR_NO_INT)
					अवरोध;
				iir &= MOXA_MUST_IIR_MASK;
				tty = tty_port_tty_get(&port->port);
				अगर (!tty || port->closing ||
				    !tty_port_initialized(&port->port)) अणु
					status = inb(port->ioaddr + UART_LSR);
					outb(0x27, port->ioaddr + UART_FCR);
					inb(port->ioaddr + UART_MSR);
					tty_kref_put(tty);
					अवरोध;
				पूर्ण

				status = inb(port->ioaddr + UART_LSR);

				अगर (status & UART_LSR_PE)
					port->err_shaकरोw |= NPPI_NOTIFY_PARITY;
				अगर (status & UART_LSR_FE)
					port->err_shaकरोw |= NPPI_NOTIFY_FRAMING;
				अगर (status & UART_LSR_OE)
					port->err_shaकरोw |=
						NPPI_NOTIFY_HW_OVERRUN;
				अगर (status & UART_LSR_BI)
					port->err_shaकरोw |= NPPI_NOTIFY_BREAK;

				अगर (port->board->chip_flag) अणु
					अगर (iir == MOXA_MUST_IIR_GDA ||
					    iir == MOXA_MUST_IIR_RDA ||
					    iir == MOXA_MUST_IIR_RTO ||
					    iir == MOXA_MUST_IIR_LSR)
						mxser_receive_अक्षरs(tty, port,
								&status);

				पूर्ण अन्यथा अणु
					status &= port->पढ़ो_status_mask;
					अगर (status & UART_LSR_DR)
						mxser_receive_अक्षरs(tty, port,
								&status);
				पूर्ण
				msr = inb(port->ioaddr + UART_MSR);
				अगर (msr & UART_MSR_ANY_DELTA)
					mxser_check_modem_status(tty, port, msr);

				अगर (port->board->chip_flag) अणु
					अगर (iir == 0x02 && (status &
								UART_LSR_THRE))
						mxser_transmit_अक्षरs(tty, port);
				पूर्ण अन्यथा अणु
					अगर (status & UART_LSR_THRE)
						mxser_transmit_अक्षरs(tty, port);
				पूर्ण
				tty_kref_put(tty);
			पूर्ण जबतक (पूर्णांक_cnt++ < MXSER_ISR_PASS_LIMIT);
			spin_unlock(&port->slock);
		पूर्ण
	पूर्ण

irq_stop:
	वापस handled;
पूर्ण

अटल स्थिर काष्ठा tty_operations mxser_ops = अणु
	.खोलो = mxser_खोलो,
	.बंद = mxser_बंद,
	.ग_लिखो = mxser_ग_लिखो,
	.put_अक्षर = mxser_put_अक्षर,
	.flush_अक्षरs = mxser_flush_अक्षरs,
	.ग_लिखो_room = mxser_ग_लिखो_room,
	.अक्षरs_in_buffer = mxser_अक्षरs_in_buffer,
	.flush_buffer = mxser_flush_buffer,
	.ioctl = mxser_ioctl,
	.throttle = mxser_throttle,
	.unthrottle = mxser_unthrottle,
	.set_termios = mxser_set_termios,
	.stop = mxser_stop,
	.start = mxser_start,
	.hangup = mxser_hangup,
	.अवरोध_ctl = mxser_rs_अवरोध,
	.रुको_until_sent = mxser_रुको_until_sent,
	.tiocmget = mxser_tiocmget,
	.tiocmset = mxser_tiocmset,
	.set_serial = mxser_set_serial_info,
	.get_serial = mxser_get_serial_info,
	.get_icount = mxser_get_icount,
पूर्ण;

अटल स्थिर काष्ठा tty_port_operations mxser_port_ops = अणु
	.carrier_उठाओd = mxser_carrier_उठाओd,
	.dtr_rts = mxser_dtr_rts,
	.activate = mxser_activate,
	.shutकरोwn = mxser_shutकरोwn_port,
पूर्ण;

/*
 * The MOXA Smartio/Industio serial driver boot-समय initialization code!
 */

अटल bool allow_overlapping_vector;
module_param(allow_overlapping_vector, bool, S_IRUGO);
MODULE_PARM_DESC(allow_overlapping_vector, "whether we allow ISA cards to be configured such that vector overlabs IO ports (default=no)");

अटल bool mxser_overlapping_vector(काष्ठा mxser_board *brd)
अणु
	वापस allow_overlapping_vector &&
		brd->vector >= brd->ports[0].ioaddr &&
		brd->vector < brd->ports[0].ioaddr + 8 * brd->info->nports;
पूर्ण

अटल पूर्णांक mxser_request_vector(काष्ठा mxser_board *brd)
अणु
	अगर (mxser_overlapping_vector(brd))
		वापस 0;
	वापस request_region(brd->vector, 1, "mxser(vector)") ? 0 : -EIO;
पूर्ण

अटल व्योम mxser_release_vector(काष्ठा mxser_board *brd)
अणु
	अगर (mxser_overlapping_vector(brd))
		वापस;
	release_region(brd->vector, 1);
पूर्ण

अटल व्योम mxser_release_ISA_res(काष्ठा mxser_board *brd)
अणु
	release_region(brd->ports[0].ioaddr, 8 * brd->info->nports);
	mxser_release_vector(brd);
पूर्ण

अटल पूर्णांक mxser_initbrd(काष्ठा mxser_board *brd)
अणु
	काष्ठा mxser_port *info;
	अचिन्हित पूर्णांक i;
	पूर्णांक retval;

	prपूर्णांकk(KERN_INFO "mxser: max. baud rate = %d bps\n",
			brd->ports[0].max_baud);

	क्रम (i = 0; i < brd->info->nports; i++) अणु
		info = &brd->ports[i];
		tty_port_init(&info->port);
		info->port.ops = &mxser_port_ops;
		info->board = brd;
		info->stop_rx = 0;
		info->ldisc_stop_rx = 0;

		/* Enhance mode enabled here */
		अगर (brd->chip_flag != MOXA_OTHER_UART)
			mxser_enable_must_enchance_mode(info->ioaddr);

		info->type = brd->uart_type;

		process_txrx_fअगरo(info);

		info->custom_भागisor = info->baud_base * 16;
		info->port.बंद_delay = 5 * HZ / 10;
		info->port.closing_रुको = 30 * HZ;
		info->normal_termios = mxvar_sdriver->init_termios;
		स_रखो(&info->mon_data, 0, माप(काष्ठा mxser_mon));
		info->err_shaकरोw = 0;
		spin_lock_init(&info->slock);

		/* beक्रमe set INT ISR, disable all पूर्णांक */
		outb(inb(info->ioaddr + UART_IER) & 0xf0,
			info->ioaddr + UART_IER);
	पूर्ण

	retval = request_irq(brd->irq, mxser_पूर्णांकerrupt, IRQF_SHARED, "mxser",
			brd);
	अगर (retval) अणु
		क्रम (i = 0; i < brd->info->nports; i++)
			tty_port_destroy(&brd->ports[i].port);
		prपूर्णांकk(KERN_ERR "Board %s: Request irq failed, IRQ (%d) may "
			"conflict with another device.\n",
			brd->info->name, brd->irq);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम mxser_board_हटाओ(काष्ठा mxser_board *brd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < brd->info->nports; i++) अणु
		tty_unरेजिस्टर_device(mxvar_sdriver, brd->idx + i);
		tty_port_destroy(&brd->ports[i].port);
	पूर्ण
	मुक्त_irq(brd->irq, brd);
पूर्ण

अटल पूर्णांक __init mxser_get_ISA_conf(पूर्णांक cap, काष्ठा mxser_board *brd)
अणु
	पूर्णांक id, i, bits, ret;
	अचिन्हित लघु regs[16], irq;
	अचिन्हित अक्षर scratch, scratch2;

	brd->chip_flag = MOXA_OTHER_UART;

	id = mxser_पढ़ो_रेजिस्टर(cap, regs);
	चयन (id) अणु
	हाल C168_ASIC_ID:
		brd->info = &mxser_cards[0];
		अवरोध;
	हाल C104_ASIC_ID:
		brd->info = &mxser_cards[1];
		अवरोध;
	हाल CI104J_ASIC_ID:
		brd->info = &mxser_cards[2];
		अवरोध;
	हाल C102_ASIC_ID:
		brd->info = &mxser_cards[5];
		अवरोध;
	हाल CI132_ASIC_ID:
		brd->info = &mxser_cards[6];
		अवरोध;
	हाल CI134_ASIC_ID:
		brd->info = &mxser_cards[7];
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	irq = 0;
	/* some ISA cards have 2 ports, but we want to see them as 4-port (why?)
	   Flag-hack checks अगर configuration should be पढ़ो as 2-port here. */
	अगर (brd->info->nports == 2 || (brd->info->flags & MXSER_HAS2)) अणु
		irq = regs[9] & 0xF000;
		irq = irq | (irq >> 4);
		अगर (irq != (regs[9] & 0xFF00))
			जाओ err_irqconflict;
	पूर्ण अन्यथा अगर (brd->info->nports == 4) अणु
		irq = regs[9] & 0xF000;
		irq = irq | (irq >> 4);
		irq = irq | (irq >> 8);
		अगर (irq != regs[9])
			जाओ err_irqconflict;
	पूर्ण अन्यथा अगर (brd->info->nports == 8) अणु
		irq = regs[9] & 0xF000;
		irq = irq | (irq >> 4);
		irq = irq | (irq >> 8);
		अगर ((irq != regs[9]) || (irq != regs[10]))
			जाओ err_irqconflict;
	पूर्ण

	अगर (!irq) अणु
		prपूर्णांकk(KERN_ERR "mxser: interrupt number unset\n");
		वापस -EIO;
	पूर्ण
	brd->irq = ((पूर्णांक)(irq & 0xF000) >> 12);
	क्रम (i = 0; i < 8; i++)
		brd->ports[i].ioaddr = (पूर्णांक) regs[i + 1] & 0xFFF8;
	अगर ((regs[12] & 0x80) == 0) अणु
		prपूर्णांकk(KERN_ERR "mxser: invalid interrupt vector\n");
		वापस -EIO;
	पूर्ण
	brd->vector = (पूर्णांक)regs[11];	/* पूर्णांकerrupt vector */
	अगर (id == 1)
		brd->vector_mask = 0x00FF;
	अन्यथा
		brd->vector_mask = 0x000F;
	क्रम (i = 7, bits = 0x0100; i >= 0; i--, bits <<= 1) अणु
		अगर (regs[12] & bits) अणु
			brd->ports[i].baud_base = 921600;
			brd->ports[i].max_baud = 921600;
		पूर्ण अन्यथा अणु
			brd->ports[i].baud_base = 115200;
			brd->ports[i].max_baud = 115200;
		पूर्ण
	पूर्ण
	scratch2 = inb(cap + UART_LCR) & (~UART_LCR_DLAB);
	outb(scratch2 | UART_LCR_DLAB, cap + UART_LCR);
	outb(0, cap + UART_EFR);	/* EFR is the same as FCR */
	outb(scratch2, cap + UART_LCR);
	outb(UART_FCR_ENABLE_FIFO, cap + UART_FCR);
	scratch = inb(cap + UART_IIR);

	अगर (scratch & 0xC0)
		brd->uart_type = PORT_16550A;
	अन्यथा
		brd->uart_type = PORT_16450;
	अगर (!request_region(brd->ports[0].ioaddr, 8 * brd->info->nports,
			"mxser(IO)")) अणु
		prपूर्णांकk(KERN_ERR "mxser: can't request ports I/O region: "
				"0x%.8lx-0x%.8lx\n",
				brd->ports[0].ioaddr, brd->ports[0].ioaddr +
				8 * brd->info->nports - 1);
		वापस -EIO;
	पूर्ण

	ret = mxser_request_vector(brd);
	अगर (ret) अणु
		release_region(brd->ports[0].ioaddr, 8 * brd->info->nports);
		prपूर्णांकk(KERN_ERR "mxser: can't request interrupt vector region: "
				"0x%.8lx-0x%.8lx\n",
				brd->ports[0].ioaddr, brd->ports[0].ioaddr +
				8 * brd->info->nports - 1);
		वापस ret;
	पूर्ण
	वापस brd->info->nports;

err_irqconflict:
	prपूर्णांकk(KERN_ERR "mxser: invalid interrupt number\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक mxser_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा mxser_board *brd;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित दीर्घ ioaddress;
	काष्ठा device *tty_dev;
	पूर्णांक retval = -EINVAL;

	क्रम (i = 0; i < MXSER_BOARDS; i++)
		अगर (mxser_boards[i].info == शून्य)
			अवरोध;

	अगर (i >= MXSER_BOARDS) अणु
		dev_err(&pdev->dev, "too many boards found (maximum %d), board "
				"not configured\n", MXSER_BOARDS);
		जाओ err;
	पूर्ण

	brd = &mxser_boards[i];
	brd->idx = i * MXSER_PORTS_PER_BOARD;
	dev_info(&pdev->dev, "found MOXA %s board (BusNo=%d, DevNo=%d)\n",
		mxser_cards[ent->driver_data].name,
		pdev->bus->number, PCI_SLOT(pdev->devfn));

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "PCI enable failed\n");
		जाओ err;
	पूर्ण

	/* io address */
	ioaddress = pci_resource_start(pdev, 2);
	retval = pci_request_region(pdev, 2, "mxser(IO)");
	अगर (retval)
		जाओ err_dis;

	brd->info = &mxser_cards[ent->driver_data];
	क्रम (i = 0; i < brd->info->nports; i++)
		brd->ports[i].ioaddr = ioaddress + 8 * i;

	/* vector */
	ioaddress = pci_resource_start(pdev, 3);
	retval = pci_request_region(pdev, 3, "mxser(vector)");
	अगर (retval)
		जाओ err_zero;
	brd->vector = ioaddress;

	/* irq */
	brd->irq = pdev->irq;

	brd->chip_flag = CheckIsMoxaMust(brd->ports[0].ioaddr);
	brd->uart_type = PORT_16550A;
	brd->vector_mask = 0;

	क्रम (i = 0; i < brd->info->nports; i++) अणु
		क्रम (j = 0; j < UART_INFO_NUM; j++) अणु
			अगर (Gpci_uart_info[j].type == brd->chip_flag) अणु
				brd->ports[i].max_baud =
					Gpci_uart_info[j].max_baud;

				/* exception....CP-102 */
				अगर (brd->info->flags & MXSER_HIGHBAUD)
					brd->ports[i].max_baud = 921600;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (brd->chip_flag == MOXA_MUST_MU860_HWID) अणु
		क्रम (i = 0; i < brd->info->nports; i++) अणु
			अगर (i < 4)
				brd->ports[i].opmode_ioaddr = ioaddress + 4;
			अन्यथा
				brd->ports[i].opmode_ioaddr = ioaddress + 0x0c;
		पूर्ण
		outb(0, ioaddress + 4);	/* शेष set to RS232 mode */
		outb(0, ioaddress + 0x0c);	/* शेष set to RS232 mode */
	पूर्ण

	क्रम (i = 0; i < brd->info->nports; i++) अणु
		brd->vector_mask |= (1 << i);
		brd->ports[i].baud_base = 921600;
	पूर्ण

	/* mxser_initbrd will hook ISR. */
	retval = mxser_initbrd(brd);
	अगर (retval)
		जाओ err_rel3;

	क्रम (i = 0; i < brd->info->nports; i++) अणु
		tty_dev = tty_port_रेजिस्टर_device(&brd->ports[i].port,
				mxvar_sdriver, brd->idx + i, &pdev->dev);
		अगर (IS_ERR(tty_dev)) अणु
			retval = PTR_ERR(tty_dev);
			क्रम (; i > 0; i--)
				tty_unरेजिस्टर_device(mxvar_sdriver,
					brd->idx + i - 1);
			जाओ err_relbrd;
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, brd);

	वापस 0;
err_relbrd:
	क्रम (i = 0; i < brd->info->nports; i++)
		tty_port_destroy(&brd->ports[i].port);
	मुक्त_irq(brd->irq, brd);
err_rel3:
	pci_release_region(pdev, 3);
err_zero:
	brd->info = शून्य;
	pci_release_region(pdev, 2);
err_dis:
	pci_disable_device(pdev);
err:
	वापस retval;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल व्योम mxser_हटाओ(काष्ठा pci_dev *pdev)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा mxser_board *brd = pci_get_drvdata(pdev);

	mxser_board_हटाओ(brd);

	pci_release_region(pdev, 2);
	pci_release_region(pdev, 3);
	pci_disable_device(pdev);
	brd->info = शून्य;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा pci_driver mxser_driver = अणु
	.name = "mxser",
	.id_table = mxser_pcibrds,
	.probe = mxser_probe,
	.हटाओ = mxser_हटाओ
पूर्ण;

अटल पूर्णांक __init mxser_module_init(व्योम)
अणु
	काष्ठा mxser_board *brd;
	काष्ठा device *tty_dev;
	अचिन्हित पूर्णांक b, i, m;
	पूर्णांक retval;

	mxvar_sdriver = alloc_tty_driver(MXSER_PORTS + 1);
	अगर (!mxvar_sdriver)
		वापस -ENOMEM;

	prपूर्णांकk(KERN_INFO "MOXA Smartio/Industio family driver version %s\n",
		MXSER_VERSION);

	/* Initialize the tty_driver काष्ठाure */
	mxvar_sdriver->name = "ttyMI";
	mxvar_sdriver->major = ttymajor;
	mxvar_sdriver->minor_start = 0;
	mxvar_sdriver->type = TTY_DRIVER_TYPE_SERIAL;
	mxvar_sdriver->subtype = SERIAL_TYPE_NORMAL;
	mxvar_sdriver->init_termios = tty_std_termios;
	mxvar_sdriver->init_termios.c_cflag = B9600|CS8|CREAD|HUPCL|CLOCAL;
	mxvar_sdriver->flags = TTY_DRIVER_REAL_RAW|TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(mxvar_sdriver, &mxser_ops);

	retval = tty_रेजिस्टर_driver(mxvar_sdriver);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "Couldn't install MOXA Smartio/Industio family "
				"tty driver !\n");
		जाओ err_put;
	पूर्ण

	/* Start finding ISA boards here */
	क्रम (m = 0, b = 0; b < MXSER_BOARDS; b++) अणु
		अगर (!ioaddr[b])
			जारी;

		brd = &mxser_boards[m];
		retval = mxser_get_ISA_conf(ioaddr[b], brd);
		अगर (retval <= 0) अणु
			brd->info = शून्य;
			जारी;
		पूर्ण

		prपूर्णांकk(KERN_INFO "mxser: found MOXA %s board (CAP=0x%lx)\n",
				brd->info->name, ioaddr[b]);

		/* mxser_initbrd will hook ISR. */
		अगर (mxser_initbrd(brd) < 0) अणु
			mxser_release_ISA_res(brd);
			brd->info = शून्य;
			जारी;
		पूर्ण

		brd->idx = m * MXSER_PORTS_PER_BOARD;
		क्रम (i = 0; i < brd->info->nports; i++) अणु
			tty_dev = tty_port_रेजिस्टर_device(&brd->ports[i].port,
					mxvar_sdriver, brd->idx + i, शून्य);
			अगर (IS_ERR(tty_dev)) अणु
				क्रम (; i > 0; i--)
					tty_unरेजिस्टर_device(mxvar_sdriver,
						brd->idx + i - 1);
				क्रम (i = 0; i < brd->info->nports; i++)
					tty_port_destroy(&brd->ports[i].port);
				मुक्त_irq(brd->irq, brd);
				mxser_release_ISA_res(brd);
				brd->info = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (brd->info == शून्य)
			जारी;

		m++;
	पूर्ण

	retval = pci_रेजिस्टर_driver(&mxser_driver);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "mxser: can't register pci driver\n");
		अगर (!m) अणु
			retval = -ENODEV;
			जाओ err_unr;
		पूर्ण /* अन्यथा: we have some ISA cards under control */
	पूर्ण

	वापस 0;
err_unr:
	tty_unरेजिस्टर_driver(mxvar_sdriver);
err_put:
	put_tty_driver(mxvar_sdriver);
	वापस retval;
पूर्ण

अटल व्योम __निकास mxser_module_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	pci_unरेजिस्टर_driver(&mxser_driver);

	क्रम (i = 0; i < MXSER_BOARDS; i++) /* ISA reमुख्यs */
		अगर (mxser_boards[i].info != शून्य)
			mxser_board_हटाओ(&mxser_boards[i]);
	tty_unरेजिस्टर_driver(mxvar_sdriver);
	put_tty_driver(mxvar_sdriver);

	क्रम (i = 0; i < MXSER_BOARDS; i++)
		अगर (mxser_boards[i].info != शून्य)
			mxser_release_ISA_res(&mxser_boards[i]);
पूर्ण

module_init(mxser_module_init);
module_निकास(mxser_module_निकास);
