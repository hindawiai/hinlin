<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2010 Pavel Cheblakov <P.B.Cheblakov@inp.nsk.su>
 *
 * Derived from the ems_pci.c driver:
 *	Copyright (C) 2007 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 *	Copyright (C) 2008 Markus Plessing <plessing@ems-wuensche.com>
 *	Copyright (C) 2008 Sebastian Haas <haas@ems-wuensche.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/पन.स>

#समावेश "sja1000.h"

#घोषणा DRV_NAME  "sja1000_plx_pci"

MODULE_AUTHOR("Pavel Cheblakov <P.B.Cheblakov@inp.nsk.su>");
MODULE_DESCRIPTION("Socket-CAN driver for PLX90xx PCI-bridge cards with "
		   "the SJA1000 chips");
MODULE_LICENSE("GPL v2");

#घोषणा PLX_PCI_MAX_CHAN 2

काष्ठा plx_pci_card अणु
	पूर्णांक channels;			/* detected channels count */
	काष्ठा net_device *net_dev[PLX_PCI_MAX_CHAN];
	व्योम __iomem *conf_addr;

	/* Poपूर्णांकer to device-dependent reset function */
	व्योम (*reset_func)(काष्ठा pci_dev *pdev);
पूर्ण;

#घोषणा PLX_PCI_CAN_CLOCK (16000000 / 2)

/* PLX9030/9050/9052 रेजिस्टरs */
#घोषणा PLX_INTCSR	0x4c		/* Interrupt Control/Status */
#घोषणा PLX_CNTRL	0x50		/* User I/O, Direct Slave Response,
					 * Serial EEPROM, and Initialization
					 * Control रेजिस्टर
					 */

#घोषणा PLX_LINT1_EN	0x1		/* Local पूर्णांकerrupt 1 enable */
#घोषणा PLX_LINT1_POL	(1 << 1)	/* Local पूर्णांकerrupt 1 polarity */
#घोषणा PLX_LINT2_EN	(1 << 3)	/* Local पूर्णांकerrupt 2 enable */
#घोषणा PLX_LINT2_POL	(1 << 4)	/* Local पूर्णांकerrupt 2 polarity */
#घोषणा PLX_PCI_INT_EN	(1 << 6)	/* PCI Interrupt Enable */
#घोषणा PLX_PCI_RESET	(1 << 30)	/* PCI Adapter Software Reset */

/* PLX9056 रेजिस्टरs */
#घोषणा PLX9056_INTCSR	0x68		/* Interrupt Control/Status */
#घोषणा PLX9056_CNTRL	0x6c		/* Control / Software Reset */

#घोषणा PLX9056_LINTI	(1 << 11)
#घोषणा PLX9056_PCI_INT_EN (1 << 8)
#घोषणा PLX9056_PCI_RCR	(1 << 29)	/* Read Configuration Registers */

/*
 * The board configuration is probably following:
 * RX1 is connected to ground.
 * TX1 is not connected.
 * CLKO is not connected.
 * Setting the OCR रेजिस्टर to 0xDA is a good idea.
 * This means normal output mode, push-pull and the correct polarity.
 */
#घोषणा PLX_PCI_OCR	(OCR_TX0_PUSHPULL | OCR_TX1_PUSHPULL)

/* OCR setting क्रम ASEM Dual CAN raw */
#घोषणा ASEM_PCI_OCR	0xfe

/*
 * In the CDR रेजिस्टर, you should set CBP to 1.
 * You will probably also want to set the घड़ी भागider value to 7
 * (meaning direct oscillator output) because the second SJA1000 chip
 * is driven by the first one CLKOUT output.
 */
#घोषणा PLX_PCI_CDR			(CDR_CBP | CDR_CLKOUT_MASK)

/* SJA1000 Control Register in the BasicCAN Mode */
#घोषणा REG_CR				0x00

/* States of some SJA1000 रेजिस्टरs after hardware reset in the BasicCAN mode*/
#घोषणा REG_CR_BASICCAN_INITIAL		0x21
#घोषणा REG_CR_BASICCAN_INITIAL_MASK	0xa1
#घोषणा REG_SR_BASICCAN_INITIAL		0x0c
#घोषणा REG_IR_BASICCAN_INITIAL		0xe0

/* States of some SJA1000 रेजिस्टरs after hardware reset in the PeliCAN mode*/
#घोषणा REG_MOD_PELICAN_INITIAL		0x01
#घोषणा REG_SR_PELICAN_INITIAL		0x3c
#घोषणा REG_IR_PELICAN_INITIAL		0x00

#घोषणा ADLINK_PCI_VENDOR_ID		0x144A
#घोषणा ADLINK_PCI_DEVICE_ID		0x7841

#घोषणा ESD_PCI_SUB_SYS_ID_PCI200	0x0004
#घोषणा ESD_PCI_SUB_SYS_ID_PCI266	0x0009
#घोषणा ESD_PCI_SUB_SYS_ID_PMC266	0x000e
#घोषणा ESD_PCI_SUB_SYS_ID_CPCI200	0x010b
#घोषणा ESD_PCI_SUB_SYS_ID_PCIE2000	0x0200
#घोषणा ESD_PCI_SUB_SYS_ID_PCI104200	0x0501

#घोषणा CAN200PCI_DEVICE_ID		0x9030
#घोषणा CAN200PCI_VENDOR_ID		0x10b5
#घोषणा CAN200PCI_SUB_DEVICE_ID		0x0301
#घोषणा CAN200PCI_SUB_VENDOR_ID		0xe1c5

#घोषणा IXXAT_PCI_VENDOR_ID		0x10b5
#घोषणा IXXAT_PCI_DEVICE_ID		0x9050
#घोषणा IXXAT_PCI_SUB_SYS_ID		0x2540

#घोषणा MARATHON_PCI_DEVICE_ID		0x2715
#घोषणा MARATHON_PCIE_DEVICE_ID		0x3432

#घोषणा TEWS_PCI_VENDOR_ID		0x1498
#घोषणा TEWS_PCI_DEVICE_ID_TMPC810	0x032A

#घोषणा CTI_PCI_VENDOR_ID		0x12c4
#घोषणा CTI_PCI_DEVICE_ID_CRG001	0x0900

#घोषणा MOXA_PCI_VENDOR_ID		0x1393
#घोषणा MOXA_PCI_DEVICE_ID		0x0100

#घोषणा ASEM_RAW_CAN_VENDOR_ID		0x10b5
#घोषणा ASEM_RAW_CAN_DEVICE_ID		0x9030
#घोषणा ASEM_RAW_CAN_SUB_VENDOR_ID	0x3000
#घोषणा ASEM_RAW_CAN_SUB_DEVICE_ID	0x1001
#घोषणा ASEM_RAW_CAN_SUB_DEVICE_ID_BIS	0x1002
#घोषणा ASEM_RAW_CAN_RST_REGISTER	0x54
#घोषणा ASEM_RAW_CAN_RST_MASK_CAN1	0x20
#घोषणा ASEM_RAW_CAN_RST_MASK_CAN2	0x04

अटल व्योम plx_pci_reset_common(काष्ठा pci_dev *pdev);
अटल व्योम plx9056_pci_reset_common(काष्ठा pci_dev *pdev);
अटल व्योम plx_pci_reset_marathon_pci(काष्ठा pci_dev *pdev);
अटल व्योम plx_pci_reset_marathon_pcie(काष्ठा pci_dev *pdev);
अटल व्योम plx_pci_reset_asem_dual_can_raw(काष्ठा pci_dev *pdev);

काष्ठा plx_pci_channel_map अणु
	u32 bar;
	u32 offset;
	u32 size;		/* 0x00 - स्वतः, e.g. length of entire bar */
पूर्ण;

काष्ठा plx_pci_card_info अणु
	स्थिर अक्षर *name;
	पूर्णांक channel_count;
	u32 can_घड़ी;
	u8 ocr;			/* output control रेजिस्टर */
	u8 cdr;			/* घड़ी भागider रेजिस्टर */

	/* Parameters क्रम mapping local configuration space */
	काष्ठा plx_pci_channel_map conf_map;

	/* Parameters क्रम mapping the SJA1000 chips */
	काष्ठा plx_pci_channel_map chan_map_tbl[PLX_PCI_MAX_CHAN];

	/* Poपूर्णांकer to device-dependent reset function */
	व्योम (*reset_func)(काष्ठा pci_dev *pdev);
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_adlink = अणु
	"Adlink PCI-7841/cPCI-7841", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु1, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु2, 0x80, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9052 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_adlink_se = अणु
	"Adlink PCI-7841/cPCI-7841 SE", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु2, 0x80, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9052 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_esd200 = अणु
	"esd CAN-PCI/CPCI/PCI104/200", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु2, 0x100, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9030/9050 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_esd266 = अणु
	"esd CAN-PCI/PMC/266", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु2, 0x100, 0x80पूर्ण पूर्ण,
	&plx9056_pci_reset_common
	/* based on PLX9056 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_esd2000 = अणु
	"esd CAN-PCIe/2000", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु2, 0x100, 0x80पूर्ण पूर्ण,
	&plx9056_pci_reset_common
	/* based on PEX8311 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_ixxat = अणु
	"IXXAT PC-I 04/PCI", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु2, 0x200, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9050 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_marathon_pci = अणु
	"Marathon CAN-bus-PCI", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x00पूर्ण, अणु4, 0x00, 0x00पूर्ण पूर्ण,
	&plx_pci_reset_marathon_pci
	/* based on PLX9052 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_marathon_pcie = अणु
	"Marathon CAN-bus-PCIe", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x00पूर्ण, अणु3, 0x80, 0x00पूर्ण पूर्ण,
	&plx_pci_reset_marathon_pcie
	/* based on PEX8311 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_tews = अणु
	"TEWS TECHNOLOGIES TPMC810", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x000, 0x80पूर्ण, अणु2, 0x100, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9030 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_cti = अणु
	"Connect Tech Inc. CANpro/104-Plus Opto (CRG001)", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x000, 0x80पूर्ण, अणु2, 0x100, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9030 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_elcus = अणु
	"Eclus CAN-200-PCI", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु1, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x80पूर्ण, अणु3, 0x00, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	/* based on PLX9030 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_moxa = अणु
	"MOXA", 2,
	PLX_PCI_CAN_CLOCK, PLX_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु0, 0x00, 0x80पूर्ण, अणु1, 0x00, 0x80पूर्ण पूर्ण,
	&plx_pci_reset_common
	 /* based on PLX9052 */
पूर्ण;

अटल काष्ठा plx_pci_card_info plx_pci_card_info_asem_dual_can = अणु
	"ASEM Dual CAN raw PCI", 2,
	PLX_PCI_CAN_CLOCK, ASEM_PCI_OCR, PLX_PCI_CDR,
	अणु0, 0x00, 0x00पूर्ण, अणु अणु2, 0x00, 0x00पूर्ण, अणु4, 0x00, 0x00पूर्ण पूर्ण,
	&plx_pci_reset_asem_dual_can_raw
	/* based on PLX9030 */
पूर्ण;

अटल स्थिर काष्ठा pci_device_id plx_pci_tbl[] = अणु
	अणु
		/* Adlink PCI-7841/cPCI-7841 */
		ADLINK_PCI_VENDOR_ID, ADLINK_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_NETWORK_OTHER << 8, ~0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_adlink
	पूर्ण,
	अणु
		/* Adlink PCI-7841/cPCI-7841 SE */
		ADLINK_PCI_VENDOR_ID, ADLINK_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_COMMUNICATION_OTHER << 8, ~0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_adlink_se
	पूर्ण,
	अणु
		/* esd CAN-PCI/200 */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_VENDOR_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCI200,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_esd200
	पूर्ण,
	अणु
		/* esd CAN-CPCI/200 */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030,
		PCI_VENDOR_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_CPCI200,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_esd200
	पूर्ण,
	अणु
		/* esd CAN-PCI104/200 */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030,
		PCI_VENDOR_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCI104200,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_esd200
	पूर्ण,
	अणु
		/* esd CAN-PCI/266 */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9056,
		PCI_VENDOR_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCI266,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_esd266
	पूर्ण,
	अणु
		/* esd CAN-PMC/266 */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9056,
		PCI_VENDOR_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PMC266,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_esd266
	पूर्ण,
	अणु
		/* esd CAN-PCIE/2000 */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9056,
		PCI_VENDOR_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCIE2000,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_esd2000
	पूर्ण,
	अणु
		/* IXXAT PC-I 04/PCI card */
		IXXAT_PCI_VENDOR_ID, IXXAT_PCI_DEVICE_ID,
		PCI_ANY_ID, IXXAT_PCI_SUB_SYS_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_ixxat
	पूर्ण,
	अणु
		/* Marathon CAN-bus-PCI card */
		PCI_VENDOR_ID_PLX, MARATHON_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_marathon_pci
	पूर्ण,
	अणु
		/* Marathon CAN-bus-PCIe card */
		PCI_VENDOR_ID_PLX, MARATHON_PCIE_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_marathon_pcie
	पूर्ण,
	अणु
		/* TEWS TECHNOLOGIES TPMC810 card */
		TEWS_PCI_VENDOR_ID, TEWS_PCI_DEVICE_ID_TMPC810,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_tews
	पूर्ण,
	अणु
		/* Connect Tech Inc. CANpro/104-Plus Opto (CRG001) card */
		PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030,
		CTI_PCI_VENDOR_ID, CTI_PCI_DEVICE_ID_CRG001,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_cti
	पूर्ण,
	अणु
		/* Elcus CAN-200-PCI */
		CAN200PCI_VENDOR_ID, CAN200PCI_DEVICE_ID,
		CAN200PCI_SUB_VENDOR_ID, CAN200PCI_SUB_DEVICE_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_elcus
	पूर्ण,
	अणु
		/* moxa */
		MOXA_PCI_VENDOR_ID, MOXA_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_moxa
	पूर्ण,
	अणु
		/* ASEM Dual CAN raw */
		ASEM_RAW_CAN_VENDOR_ID, ASEM_RAW_CAN_DEVICE_ID,
		ASEM_RAW_CAN_SUB_VENDOR_ID, ASEM_RAW_CAN_SUB_DEVICE_ID,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_asem_dual_can
	पूर्ण,
	अणु
		/* ASEM Dual CAN raw -new model */
		ASEM_RAW_CAN_VENDOR_ID, ASEM_RAW_CAN_DEVICE_ID,
		ASEM_RAW_CAN_SUB_VENDOR_ID, ASEM_RAW_CAN_SUB_DEVICE_ID_BIS,
		0, 0,
		(kernel_uदीर्घ_t)&plx_pci_card_info_asem_dual_can
	पूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, plx_pci_tbl);

अटल u8 plx_pci_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस ioपढ़ो8(priv->reg_base + port);
पूर्ण

अटल व्योम plx_pci_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port, u8 val)
अणु
	ioग_लिखो8(val, priv->reg_base + port);
पूर्ण

/*
 * Check अगर a CAN controller is present at the specअगरied location
 * by trying to चयन 'em from the Basic mode पूर्णांकo the PeliCAN mode.
 * Also check states of some रेजिस्टरs in reset mode.
 */
अटल अंतरभूत पूर्णांक plx_pci_check_sja1000(स्थिर काष्ठा sja1000_priv *priv)
अणु
	पूर्णांक flag = 0;

	/*
	 * Check रेजिस्टरs after hardware reset (the Basic mode)
	 * See states on p. 10 of the Datasheet.
	 */
	अगर ((priv->पढ़ो_reg(priv, REG_CR) & REG_CR_BASICCAN_INITIAL_MASK) ==
	    REG_CR_BASICCAN_INITIAL &&
	    (priv->पढ़ो_reg(priv, SJA1000_SR) == REG_SR_BASICCAN_INITIAL) &&
	    (priv->पढ़ो_reg(priv, SJA1000_IR) == REG_IR_BASICCAN_INITIAL))
		flag = 1;

	/* Bring the SJA1000 पूर्णांकo the PeliCAN mode*/
	priv->ग_लिखो_reg(priv, SJA1000_CDR, CDR_PELICAN);

	/*
	 * Check रेजिस्टरs after reset in the PeliCAN mode.
	 * See states on p. 23 of the Datasheet.
	 */
	अगर (priv->पढ़ो_reg(priv, SJA1000_MOD) == REG_MOD_PELICAN_INITIAL &&
	    priv->पढ़ो_reg(priv, SJA1000_SR) == REG_SR_PELICAN_INITIAL &&
	    priv->पढ़ो_reg(priv, SJA1000_IR) == REG_IR_PELICAN_INITIAL)
		वापस flag;

	वापस 0;
पूर्ण

/*
 * PLX9030/50/52 software reset
 * Also LRESET# निश्चितs and brings to reset device on the Local Bus (अगर wired).
 * For most cards it's enough क्रम reset the SJA1000 chips.
 */
अटल व्योम plx_pci_reset_common(काष्ठा pci_dev *pdev)
अणु
	काष्ठा plx_pci_card *card = pci_get_drvdata(pdev);
	u32 cntrl;

	cntrl = ioपढ़ो32(card->conf_addr + PLX_CNTRL);
	cntrl |= PLX_PCI_RESET;
	ioग_लिखो32(cntrl, card->conf_addr + PLX_CNTRL);
	udelay(100);
	cntrl ^= PLX_PCI_RESET;
	ioग_लिखो32(cntrl, card->conf_addr + PLX_CNTRL);
पूर्ण;

/*
 * PLX9056 software reset
 * Assert LRESET# and reset device(s) on the Local Bus (अगर wired).
 */
अटल व्योम plx9056_pci_reset_common(काष्ठा pci_dev *pdev)
अणु
	काष्ठा plx_pci_card *card = pci_get_drvdata(pdev);
	u32 cntrl;

	/* issue a local bus reset */
	cntrl = ioपढ़ो32(card->conf_addr + PLX9056_CNTRL);
	cntrl |= PLX_PCI_RESET;
	ioग_लिखो32(cntrl, card->conf_addr + PLX9056_CNTRL);
	udelay(100);
	cntrl ^= PLX_PCI_RESET;
	ioग_लिखो32(cntrl, card->conf_addr + PLX9056_CNTRL);

	/* reload local configuration from EEPROM */
	cntrl |= PLX9056_PCI_RCR;
	ioग_लिखो32(cntrl, card->conf_addr + PLX9056_CNTRL);

	/*
	 * There is no safe way to poll क्रम the end
	 * of reconfiguration process. Waiting क्रम 10ms
	 * is safe.
	 */
	mdelay(10);

	cntrl ^= PLX9056_PCI_RCR;
	ioग_लिखो32(cntrl, card->conf_addr + PLX9056_CNTRL);
पूर्ण;

/* Special reset function क्रम Marathon CAN-bus-PCI card */
अटल व्योम plx_pci_reset_marathon_pci(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *reset_addr;
	पूर्णांक i;
	अटल स्थिर पूर्णांक reset_bar[2] = अणु3, 5पूर्ण;

	plx_pci_reset_common(pdev);

	क्रम (i = 0; i < 2; i++) अणु
		reset_addr = pci_iomap(pdev, reset_bar[i], 0);
		अगर (!reset_addr) अणु
			dev_err(&pdev->dev, "Failed to remap reset "
				"space %d (BAR%d)\n", i, reset_bar[i]);
		पूर्ण अन्यथा अणु
			/* reset the SJA1000 chip */
			ioग_लिखो8(0x1, reset_addr);
			udelay(100);
			pci_iounmap(pdev, reset_addr);
		पूर्ण
	पूर्ण
पूर्ण

/* Special reset function क्रम Marathon CAN-bus-PCIe card */
अटल व्योम plx_pci_reset_marathon_pcie(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *addr;
	व्योम __iomem *reset_addr;
	पूर्णांक i;

	plx9056_pci_reset_common(pdev);

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा plx_pci_channel_map *chan_map =
			&plx_pci_card_info_marathon_pcie.chan_map_tbl[i];
		addr = pci_iomap(pdev, chan_map->bar, chan_map->size);
		अगर (!addr) अणु
			dev_err(&pdev->dev, "Failed to remap reset "
				"space %d (BAR%d)\n", i, chan_map->bar);
		पूर्ण अन्यथा अणु
			/* reset the SJA1000 chip */
			#घोषणा MARATHON_PCIE_RESET_OFFSET 32
			reset_addr = addr + chan_map->offset +
			             MARATHON_PCIE_RESET_OFFSET;
			ioग_लिखो8(0x1, reset_addr);
			udelay(100);
			pci_iounmap(pdev, addr);
		पूर्ण
	पूर्ण
पूर्ण

/* Special reset function क्रम ASEM Dual CAN raw card */
अटल व्योम plx_pci_reset_asem_dual_can_raw(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *bar0_addr;
	u8 पंचांगpval;

	plx_pci_reset_common(pdev);

	bar0_addr = pci_iomap(pdev, 0, 0);
	अगर (!bar0_addr) अणु
		dev_err(&pdev->dev, "Failed to remap reset space 0 (BAR0)\n");
		वापस;
	पूर्ण

	/* reset the two SJA1000 chips */
	पंचांगpval = ioपढ़ो8(bar0_addr + ASEM_RAW_CAN_RST_REGISTER);
	पंचांगpval &= ~(ASEM_RAW_CAN_RST_MASK_CAN1 | ASEM_RAW_CAN_RST_MASK_CAN2);
	ioग_लिखो8(पंचांगpval, bar0_addr + ASEM_RAW_CAN_RST_REGISTER);
	usleep_range(300, 400);
	पंचांगpval |= ASEM_RAW_CAN_RST_MASK_CAN1 | ASEM_RAW_CAN_RST_MASK_CAN2;
	ioग_लिखो8(पंचांगpval, bar0_addr + ASEM_RAW_CAN_RST_REGISTER);
	usleep_range(300, 400);
	pci_iounmap(pdev, bar0_addr);
पूर्ण

अटल व्योम plx_pci_del_card(काष्ठा pci_dev *pdev)
अणु
	काष्ठा plx_pci_card *card = pci_get_drvdata(pdev);
	काष्ठा net_device *dev;
	काष्ठा sja1000_priv *priv;
	पूर्णांक i = 0;

	क्रम (i = 0; i < PLX_PCI_MAX_CHAN; i++) अणु
		dev = card->net_dev[i];
		अगर (!dev)
			जारी;

		dev_info(&pdev->dev, "Removing %s\n", dev->name);
		unरेजिस्टर_sja1000dev(dev);
		priv = netdev_priv(dev);
		अगर (priv->reg_base)
			pci_iounmap(pdev, priv->reg_base);
		मुक्त_sja1000dev(dev);
	पूर्ण

	card->reset_func(pdev);

	/*
	 * Disable पूर्णांकerrupts from PCI-card and disable local
	 * पूर्णांकerrupts
	 */
	अगर (pdev->device != PCI_DEVICE_ID_PLX_9056 &&
	    pdev->device != MARATHON_PCIE_DEVICE_ID)
		ioग_लिखो32(0x0, card->conf_addr + PLX_INTCSR);
	अन्यथा
		ioग_लिखो32(0x0, card->conf_addr + PLX9056_INTCSR);

	अगर (card->conf_addr)
		pci_iounmap(pdev, card->conf_addr);

	kमुक्त(card);

	pci_disable_device(pdev);
पूर्ण

/*
 * Probe PLX90xx based device क्रम the SJA1000 chips and रेजिस्टर each
 * available CAN channel to SJA1000 Socket-CAN subप्रणाली.
 */
अटल पूर्णांक plx_pci_add_card(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sja1000_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा plx_pci_card *card;
	काष्ठा plx_pci_card_info *ci;
	पूर्णांक err, i;
	u32 val;
	व्योम __iomem *addr;

	ci = (काष्ठा plx_pci_card_info *)ent->driver_data;

	अगर (pci_enable_device(pdev) < 0) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(&pdev->dev, "Detected \"%s\" card at slot #%i\n",
		 ci->name, PCI_SLOT(pdev->devfn));

	/* Allocate card काष्ठाures to hold addresses, ... */
	card = kzalloc(माप(*card), GFP_KERNEL);
	अगर (!card) अणु
		pci_disable_device(pdev);
		वापस -ENOMEM;
	पूर्ण

	pci_set_drvdata(pdev, card);

	card->channels = 0;

	/* Remap PLX90xx configuration space */
	addr = pci_iomap(pdev, ci->conf_map.bar, ci->conf_map.size);
	अगर (!addr) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "Failed to remap configuration space "
			"(BAR%d)\n", ci->conf_map.bar);
		जाओ failure_cleanup;
	पूर्ण
	card->conf_addr = addr + ci->conf_map.offset;

	ci->reset_func(pdev);
	card->reset_func = ci->reset_func;

	/* Detect available channels */
	क्रम (i = 0; i < ci->channel_count; i++) अणु
		काष्ठा plx_pci_channel_map *cm = &ci->chan_map_tbl[i];

		dev = alloc_sja1000dev(0);
		अगर (!dev) अणु
			err = -ENOMEM;
			जाओ failure_cleanup;
		पूर्ण

		card->net_dev[i] = dev;
		priv = netdev_priv(dev);
		priv->priv = card;
		priv->irq_flags = IRQF_SHARED;

		dev->irq = pdev->irq;

		/*
		 * Remap IO space of the SJA1000 chips
		 * This is device-dependent mapping
		 */
		addr = pci_iomap(pdev, cm->bar, cm->size);
		अगर (!addr) अणु
			err = -ENOMEM;
			dev_err(&pdev->dev, "Failed to remap BAR%d\n", cm->bar);
			जाओ failure_cleanup;
		पूर्ण

		priv->reg_base = addr + cm->offset;
		priv->पढ़ो_reg = plx_pci_पढ़ो_reg;
		priv->ग_लिखो_reg = plx_pci_ग_लिखो_reg;

		/* Check अगर channel is present */
		अगर (plx_pci_check_sja1000(priv)) अणु
			priv->can.घड़ी.freq = ci->can_घड़ी;
			priv->ocr = ci->ocr;
			priv->cdr = ci->cdr;

			SET_NETDEV_DEV(dev, &pdev->dev);
			dev->dev_id = i;

			/* Register SJA1000 device */
			err = रेजिस्टर_sja1000dev(dev);
			अगर (err) अणु
				dev_err(&pdev->dev, "Registering device failed "
					"(err=%d)\n", err);
				जाओ failure_cleanup;
			पूर्ण

			card->channels++;

			dev_info(&pdev->dev, "Channel #%d at 0x%p, irq %d "
				 "registered as %s\n", i + 1, priv->reg_base,
				 dev->irq, dev->name);
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "Channel #%d not detected\n",
				i + 1);
			मुक्त_sja1000dev(dev);
			card->net_dev[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (!card->channels) अणु
		err = -ENODEV;
		जाओ failure_cleanup;
	पूर्ण

	/*
	 * Enable पूर्णांकerrupts from PCI-card (PLX90xx) and enable Local_1,
	 * Local_2 पूर्णांकerrupts from the SJA1000 chips
	 */
	अगर (pdev->device != PCI_DEVICE_ID_PLX_9056 &&
	    pdev->device != MARATHON_PCIE_DEVICE_ID) अणु
		val = ioपढ़ो32(card->conf_addr + PLX_INTCSR);
		अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ESDGMBH)
			val |= PLX_LINT1_EN | PLX_PCI_INT_EN;
		अन्यथा
			val |= PLX_LINT1_EN | PLX_LINT2_EN | PLX_PCI_INT_EN;
		ioग_लिखो32(val, card->conf_addr + PLX_INTCSR);
	पूर्ण अन्यथा अणु
		ioग_लिखो32(PLX9056_LINTI | PLX9056_PCI_INT_EN,
			  card->conf_addr + PLX9056_INTCSR);
	पूर्ण
	वापस 0;

failure_cleanup:
	dev_err(&pdev->dev, "Error: %d. Cleaning Up.\n", err);

	plx_pci_del_card(pdev);

	वापस err;
पूर्ण

अटल काष्ठा pci_driver plx_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = plx_pci_tbl,
	.probe = plx_pci_add_card,
	.हटाओ = plx_pci_del_card,
पूर्ण;

module_pci_driver(plx_pci_driver);
