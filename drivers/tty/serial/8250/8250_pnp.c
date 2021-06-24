<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Probe क्रम 8250/16550-type ISAPNP serial ports.
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 *
 *  Ported to the Linux PnP Layer - (C) Adam Belay.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pnp.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "8250.h"

#घोषणा UNKNOWN_DEV 0x3000
#घोषणा CIR_PORT	0x0800

अटल स्थिर काष्ठा pnp_device_id pnp_dev_table[] = अणु
	/* Archtek America Corp. */
	/* Archtek SmartLink Modem 3334BT Plug & Play */
	अणु	"AAC000F",		0	पूर्ण,
	/* Anchor Datacomm BV */
	/* SXPro 144 External Data Fax Modem Plug & Play */
	अणु	"ADC0001",		0	पूर्ण,
	/* SXPro 288 External Data Fax Modem Plug & Play */
	अणु	"ADC0002",		0	पूर्ण,
	/* PROLiNK 1456VH ISA PnP K56flex Fax Modem */
	अणु	"AEI0250",		0	पूर्ण,
	/* Actiontec ISA PNP 56K X2 Fax Modem */
	अणु	"AEI1240",		0	पूर्ण,
	/* Rockwell 56K ACF II Fax+Data+Voice Modem */
	अणु	"AKY1021",		0 /*SPCI_FL_NO_SHIRQ*/	पूर्ण,
	/*
	 * ALi Fast Infrared Controller
	 * Native driver (ali-ircc) is broken so at least
	 * it can be used with irtty-sir.
	 */
	अणु	"ALI5123",		0	पूर्ण,
	/* AZT3005 PnP SOUND DEVICE */
	अणु	"AZT4001",		0	पूर्ण,
	/* Best Data Products Inc. Smart One 336F PnP Modem */
	अणु	"BDP3336",		0	पूर्ण,
	/*  Boca Research */
	/* Boca Complete Ofc Communicator 14.4 Data-FAX */
	अणु	"BRI0A49",		0	पूर्ण,
	/* Boca Research 33,600 ACF Modem */
	अणु	"BRI1400",		0	पूर्ण,
	/* Boca 33.6 Kbps Internal FD34FSVD */
	अणु	"BRI3400",		0	पूर्ण,
	/* Boca 33.6 Kbps Internal FD34FSVD */
	अणु	"BRI0A49",		0	पूर्ण,
	/* Best Data Products Inc. Smart One 336F PnP Modem */
	अणु	"BDP3336",		0	पूर्ण,
	/* Computer Peripherals Inc */
	/* EuroViVa CommCenter-33.6 SP PnP */
	अणु	"CPI4050",		0	पूर्ण,
	/* Creative Lअसल */
	/* Creative Lअसल Phone Blaster 28.8 DSVD PnP Voice */
	अणु	"CTL3001",		0	पूर्ण,
	/* Creative Lअसल Modem Blaster 28.8 DSVD PnP Voice */
	अणु	"CTL3011",		0	पूर्ण,
	/* Davicom ISA 33.6K Modem */
	अणु	"DAV0336",		0	पूर्ण,
	/* Creative */
	/* Creative Modem Blaster Flash56 DI5601-1 */
	अणु	"DMB1032",		0	पूर्ण,
	/* Creative Modem Blaster V.90 DI5660 */
	अणु	"DMB2001",		0	पूर्ण,
	/* E-Tech */
	/* E-Tech CyberBULLET PC56RVP */
	अणु	"ETT0002",		0	पूर्ण,
	/* FUJITSU */
	/* Fujitsu 33600 PnP-I2 R Plug & Play */
	अणु	"FUJ0202",		0	पूर्ण,
	/* Fujitsu FMV-FX431 Plug & Play */
	अणु	"FUJ0205",		0	पूर्ण,
	/* Fujitsu 33600 PnP-I4 R Plug & Play */
	अणु	"FUJ0206",		0	पूर्ण,
	/* Fujitsu Fax Voice 33600 PNP-I5 R Plug & Play */
	अणु	"FUJ0209",		0	पूर्ण,
	/* Archtek America Corp. */
	/* Archtek SmartLink Modem 3334BT Plug & Play */
	अणु	"GVC000F",		0	पूर्ण,
	/* Archtek SmartLink Modem 3334BRV 33.6K Data Fax Voice */
	अणु	"GVC0303",		0	पूर्ण,
	/* Hayes */
	/* Hayes Optima 288 V.34-V.FC + FAX + Voice Plug & Play */
	अणु	"HAY0001",		0	पूर्ण,
	/* Hayes Optima 336 V.34 + FAX + Voice PnP */
	अणु	"HAY000C",		0	पूर्ण,
	/* Hayes Optima 336B V.34 + FAX + Voice PnP */
	अणु	"HAY000D",		0	पूर्ण,
	/* Hayes Accura 56K Ext Fax Modem PnP */
	अणु	"HAY5670",		0	पूर्ण,
	/* Hayes Accura 56K Ext Fax Modem PnP */
	अणु	"HAY5674",		0	पूर्ण,
	/* Hayes Accura 56K Fax Modem PnP */
	अणु	"HAY5675",		0	पूर्ण,
	/* Hayes 288, V.34 + FAX */
	अणु	"HAYF000",		0	पूर्ण,
	/* Hayes Optima 288 V.34 + FAX + Voice, Plug & Play */
	अणु	"HAYF001",		0	पूर्ण,
	/* IBM */
	/* IBM Thinkpad 701 Internal Modem Voice */
	अणु	"IBM0033",		0	पूर्ण,
	/* Intermec */
	/* Intermec CV60 touchscreen port */
	अणु	"PNP4972",		0	पूर्ण,
	/* Intertex */
	/* Intertex 28k8 33k6 Voice EXT PnP */
	अणु	"IXDC801",		0	पूर्ण,
	/* Intertex 33k6 56k Voice EXT PnP */
	अणु	"IXDC901",		0	पूर्ण,
	/* Intertex 28k8 33k6 Voice SP EXT PnP */
	अणु	"IXDD801",		0	पूर्ण,
	/* Intertex 33k6 56k Voice SP EXT PnP */
	अणु	"IXDD901",		0	पूर्ण,
	/* Intertex 28k8 33k6 Voice SP INT PnP */
	अणु	"IXDF401",		0	पूर्ण,
	/* Intertex 28k8 33k6 Voice SP EXT PnP */
	अणु	"IXDF801",		0	पूर्ण,
	/* Intertex 33k6 56k Voice SP EXT PnP */
	अणु	"IXDF901",		0	पूर्ण,
	/* Kortex International */
	/* KORTEX 28800 Externe PnP */
	अणु	"KOR4522",		0	पूर्ण,
	/* KXPro 33.6 Vocal ASVD PnP */
	अणु	"KORF661",		0	पूर्ण,
	/* Lasat */
	/* LASAT Internet 33600 PnP */
	अणु	"LAS4040",		0	पूर्ण,
	/* Lasat Safire 560 PnP */
	अणु	"LAS4540",		0	पूर्ण,
	/* Lasat Safire 336  PnP */
	अणु	"LAS5440",		0	पूर्ण,
	/* Microcom, Inc. */
	/* Microcom TravelPorte FAST V.34 Plug & Play */
	अणु	"MNP0281",		0	पूर्ण,
	/* Microcom DeskPorte V.34 FAST or FAST+ Plug & Play */
	अणु	"MNP0336",		0	पूर्ण,
	/* Microcom DeskPorte FAST EP 28.8 Plug & Play */
	अणु	"MNP0339",		0	पूर्ण,
	/* Microcom DeskPorte 28.8P Plug & Play */
	अणु	"MNP0342",		0	पूर्ण,
	/* Microcom DeskPorte FAST ES 28.8 Plug & Play */
	अणु	"MNP0500",		0	पूर्ण,
	/* Microcom DeskPorte FAST ES 28.8 Plug & Play */
	अणु	"MNP0501",		0	पूर्ण,
	/* Microcom DeskPorte 28.8S Internal Plug & Play */
	अणु	"MNP0502",		0	पूर्ण,
	/* Motorola */
	/* Motorola BitSURFR Plug & Play */
	अणु	"MOT1105",		0	पूर्ण,
	/* Motorola TA210 Plug & Play */
	अणु	"MOT1111",		0	पूर्ण,
	/* Motorola HMTA 200 (ISDN) Plug & Play */
	अणु	"MOT1114",		0	पूर्ण,
	/* Motorola BitSURFR Plug & Play */
	अणु	"MOT1115",		0	पूर्ण,
	/* Motorola Lअगरestyle 28.8 Internal */
	अणु	"MOT1190",		0	पूर्ण,
	/* Motorola V.3400 Plug & Play */
	अणु	"MOT1501",		0	पूर्ण,
	/* Motorola Lअगरestyle 28.8 V.34 Plug & Play */
	अणु	"MOT1502",		0	पूर्ण,
	/* Motorola Power 28.8 V.34 Plug & Play */
	अणु	"MOT1505",		0	पूर्ण,
	/* Motorola ModemSURFR External 28.8 Plug & Play */
	अणु	"MOT1509",		0	पूर्ण,
	/* Motorola Premier 33.6 Desktop Plug & Play */
	अणु	"MOT150A",		0	पूर्ण,
	/* Motorola VoiceSURFR 56K External PnP */
	अणु	"MOT150F",		0	पूर्ण,
	/* Motorola ModemSURFR 56K External PnP */
	अणु	"MOT1510",		0	पूर्ण,
	/* Motorola ModemSURFR 56K Internal PnP */
	अणु	"MOT1550",		0	पूर्ण,
	/* Motorola ModemSURFR Internal 28.8 Plug & Play */
	अणु	"MOT1560",		0	पूर्ण,
	/* Motorola Premier 33.6 Internal Plug & Play */
	अणु	"MOT1580",		0	पूर्ण,
	/* Motorola OnlineSURFR 28.8 Internal Plug & Play */
	अणु	"MOT15B0",		0	पूर्ण,
	/* Motorola VoiceSURFR 56K Internal PnP */
	अणु	"MOT15F0",		0	पूर्ण,
	/* Com 1 */
	/*  Deskline K56 Phone System PnP */
	अणु	"MVX00A1",		0	पूर्ण,
	/* PC Rider K56 Phone System PnP */
	अणु	"MVX00F2",		0	पूर्ण,
	/* NEC 98NOTE SPEAKER PHONE FAX MODEM(33600bps) */
	अणु	"nEC8241",		0	पूर्ण,
	/* Pace 56 Voice Internal Plug & Play Modem */
	अणु	"PMC2430",		0	पूर्ण,
	/* Generic */
	/* Generic standard PC COM port	 */
	अणु	"PNP0500",		0	पूर्ण,
	/* Generic 16550A-compatible COM port */
	अणु	"PNP0501",		0	पूर्ण,
	/* Compaq 14400 Modem */
	अणु	"PNPC000",		0	पूर्ण,
	/* Compaq 2400/9600 Modem */
	अणु	"PNPC001",		0	पूर्ण,
	/* Dial-Up Networking Serial Cable between 2 PCs */
	अणु	"PNPC031",		0	पूर्ण,
	/* Dial-Up Networking Parallel Cable between 2 PCs */
	अणु	"PNPC032",		0	पूर्ण,
	/* Standard 9600 bps Modem */
	अणु	"PNPC100",		0	पूर्ण,
	/* Standard 14400 bps Modem */
	अणु	"PNPC101",		0	पूर्ण,
	/*  Standard 28800 bps Modem*/
	अणु	"PNPC102",		0	पूर्ण,
	/*  Standard Modem*/
	अणु	"PNPC103",		0	पूर्ण,
	/*  Standard 9600 bps Modem*/
	अणु	"PNPC104",		0	पूर्ण,
	/*  Standard 14400 bps Modem*/
	अणु	"PNPC105",		0	पूर्ण,
	/*  Standard 28800 bps Modem*/
	अणु	"PNPC106",		0	पूर्ण,
	/*  Standard Modem */
	अणु	"PNPC107",		0	पूर्ण,
	/* Standard 9600 bps Modem */
	अणु	"PNPC108",		0	पूर्ण,
	/* Standard 14400 bps Modem */
	अणु	"PNPC109",		0	पूर्ण,
	/* Standard 28800 bps Modem */
	अणु	"PNPC10A",		0	पूर्ण,
	/* Standard Modem */
	अणु	"PNPC10B",		0	पूर्ण,
	/* Standard 9600 bps Modem */
	अणु	"PNPC10C",		0	पूर्ण,
	/* Standard 14400 bps Modem */
	अणु	"PNPC10D",		0	पूर्ण,
	/* Standard 28800 bps Modem */
	अणु	"PNPC10E",		0	पूर्ण,
	/* Standard Modem */
	अणु	"PNPC10F",		0	पूर्ण,
	/* Standard PCMCIA Card Modem */
	अणु	"PNP2000",		0	पूर्ण,
	/* Rockwell */
	/* Modular Technology */
	/* Rockwell 33.6 DPF Internal PnP */
	/* Modular Technology 33.6 Internal PnP */
	अणु	"ROK0030",		0	पूर्ण,
	/* Kortex International */
	/* KORTEX 14400 Externe PnP */
	अणु	"ROK0100",		0	पूर्ण,
	/* Rockwell 28.8 */
	अणु	"ROK4120",		0	पूर्ण,
	/* Viking Components, Inc */
	/* Viking 28.8 INTERNAL Fax+Data+Voice PnP */
	अणु	"ROK4920",		0	पूर्ण,
	/* Rockwell */
	/* British Telecom */
	/* Modular Technology */
	/* Rockwell 33.6 DPF External PnP */
	/* BT Prologue 33.6 External PnP */
	/* Modular Technology 33.6 External PnP */
	अणु	"RSS00A0",		0	पूर्ण,
	/* Viking 56K FAX INT */
	अणु	"RSS0262",		0	पूर्ण,
	/* K56 par,VV,Voice,Speakphone,AudioSpan,PnP */
	अणु       "RSS0250",              0       पूर्ण,
	/* SupraExpress 28.8 Data/Fax PnP modem */
	अणु	"SUP1310",		0	पूर्ण,
	/* SupraExpress 336i PnP Voice Modem */
	अणु	"SUP1381",		0	पूर्ण,
	/* SupraExpress 33.6 Data/Fax PnP modem */
	अणु	"SUP1421",		0	पूर्ण,
	/* SupraExpress 33.6 Data/Fax PnP modem */
	अणु	"SUP1590",		0	पूर्ण,
	/* SupraExpress 336i Sp ASVD */
	अणु	"SUP1620",		0	पूर्ण,
	/* SupraExpress 33.6 Data/Fax PnP modem */
	अणु	"SUP1760",		0	पूर्ण,
	/* SupraExpress 56i Sp Intl */
	अणु	"SUP2171",		0	पूर्ण,
	/* Phoebe Micro */
	/* Phoebe Micro 33.6 Data Fax 1433VQH Plug & Play */
	अणु	"TEX0011",		0	पूर्ण,
	/* Archtek America Corp. */
	/* Archtek SmartLink Modem 3334BT Plug & Play */
	अणु	"UAC000F",		0	पूर्ण,
	/* 3Com Corp. */
	/* Gateway Telepath IIvi 33.6 */
	अणु	"USR0000",		0	पूर्ण,
	/* U.S. Robotics Sporster 33.6K Fax INT PnP */
	अणु	"USR0002",		0	पूर्ण,
	/*  Sportster Vi 14.4 PnP FAX Voicemail */
	अणु	"USR0004",		0	पूर्ण,
	/* U.S. Robotics 33.6K Voice INT PnP */
	अणु	"USR0006",		0	पूर्ण,
	/* U.S. Robotics 33.6K Voice EXT PnP */
	अणु	"USR0007",		0	पूर्ण,
	/* U.S. Robotics Courier V.Everything INT PnP */
	अणु	"USR0009",		0	पूर्ण,
	/* U.S. Robotics 33.6K Voice INT PnP */
	अणु	"USR2002",		0	पूर्ण,
	/* U.S. Robotics 56K Voice INT PnP */
	अणु	"USR2070",		0	पूर्ण,
	/* U.S. Robotics 56K Voice EXT PnP */
	अणु	"USR2080",		0	पूर्ण,
	/* U.S. Robotics 56K FAX INT */
	अणु	"USR3031",		0	पूर्ण,
	/* U.S. Robotics 56K FAX INT */
	अणु	"USR3050",		0	पूर्ण,
	/* U.S. Robotics 56K Voice INT PnP */
	अणु	"USR3070",		0	पूर्ण,
	/* U.S. Robotics 56K Voice EXT PnP */
	अणु	"USR3080",		0	पूर्ण,
	/* U.S. Robotics 56K Voice INT PnP */
	अणु	"USR3090",		0	पूर्ण,
	/* U.S. Robotics 56K Message  */
	अणु	"USR9100",		0	पूर्ण,
	/* U.S. Robotics 56K FAX EXT PnP*/
	अणु	"USR9160",		0	पूर्ण,
	/* U.S. Robotics 56K FAX INT PnP*/
	अणु	"USR9170",		0	पूर्ण,
	/* U.S. Robotics 56K Voice EXT PnP*/
	अणु	"USR9180",		0	पूर्ण,
	/* U.S. Robotics 56K Voice INT PnP*/
	अणु	"USR9190",		0	पूर्ण,
	/* Wacom tablets */
	अणु	"WACFXXX",		0	पूर्ण,
	/* Compaq touchscreen */
	अणु       "FPI2002",              0 पूर्ण,
	/* Fujitsu Stylistic touchscreens */
	अणु       "FUJ02B2",              0 पूर्ण,
	अणु       "FUJ02B3",              0 पूर्ण,
	/* Fujitsu Stylistic LT touchscreens */
	अणु       "FUJ02B4",              0 पूर्ण,
	/* Passive Fujitsu Stylistic touchscreens */
	अणु       "FUJ02B6",              0 पूर्ण,
	अणु       "FUJ02B7",              0 पूर्ण,
	अणु       "FUJ02B8",              0 पूर्ण,
	अणु       "FUJ02B9",              0 पूर्ण,
	अणु       "FUJ02BC",              0 पूर्ण,
	/* Fujitsu Wacom Tablet PC device */
	अणु	"FUJ02E5",		0	पूर्ण,
	/* Fujitsu P-series tablet PC device */
	अणु	"FUJ02E6",		0	पूर्ण,
	/* Fujitsu Wacom 2FGT Tablet PC device */
	अणु	"FUJ02E7",		0	पूर्ण,
	/* Fujitsu Wacom 1FGT Tablet PC device */
	अणु	"FUJ02E9",		0	पूर्ण,
	/*
	 * LG C1 EXPRESS DUAL (C1-PB11A3) touch screen (actually a FUJ02E6
	 * in disguise).
	 */
	अणु	"LTS0001",		0       पूर्ण,
	/* Rockwell's (PORALiNK) 33600 INT PNP */
	अणु	"WCI0003",		0	पूर्ण,
	/* Unknown PnP modems */
	अणु	"PNPCXXX",		UNKNOWN_DEV	पूर्ण,
	/* More unknown PnP modems */
	अणु	"PNPDXXX",		UNKNOWN_DEV	पूर्ण,
	/*
	 * Winbond CIR port, should not be probed. We should keep track of
	 * it to prevent the legacy serial driver from probing it.
	 */
	अणु	"WEC1022",		CIR_PORT	पूर्ण,
	/*
	 * SMSC IrCC SIR/FIR port, should not be probed by serial driver as
	 * well so its own driver can bind to it.
	 */
	अणु	"SMCF010",		CIR_PORT	पूर्ण,
	अणु	"",			0	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, pnp_dev_table);

अटल स्थिर अक्षर *modem_names[] = अणु
	"MODEM", "Modem", "modem", "FAX", "Fax", "fax",
	"56K", "56k", "K56", "33.6", "28.8", "14.4",
	"33,600", "28,800", "14,400", "33.600", "28.800", "14.400",
	"33600", "28800", "14400", "V.90", "V.34", "V.32", शून्य
पूर्ण;

अटल bool check_name(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर **पंचांगp;

	क्रम (पंचांगp = modem_names; *पंचांगp; पंचांगp++)
		अगर (म_माला(name, *पंचांगp))
			वापस true;

	वापस false;
पूर्ण

अटल bool check_resources(काष्ठा pnp_dev *dev)
अणु
	अटल स्थिर resource_माप_प्रकार base[] = अणु0x2f8, 0x3f8, 0x2e8, 0x3e8पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(base); i++) अणु
		अगर (pnp_possible_config(dev, IORESOURCE_IO, base[i], 8))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Given a complete unknown PnP device, try to use some heuristics to
 * detect modems. Currently use such heuristic set:
 *     - dev->name or dev->bus->name must contain "modem" substring;
 *     - device must have only one IO region (8 byte दीर्घ) with base address
 *       0x2e8, 0x3e8, 0x2f8 or 0x3f8.
 *
 * Such detection looks very ugly, but can detect at least some of numerous
 * PnP modems, alternatively we must hardcode all modems in pnp_devices[]
 * table.
 */
अटल पूर्णांक serial_pnp_guess_board(काष्ठा pnp_dev *dev)
अणु
	अगर (!(check_name(pnp_dev_name(dev)) ||
	    (dev->card && check_name(dev->card->name))))
		वापस -ENODEV;

	अगर (check_resources(dev))
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
serial_pnp_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा uart_8250_port uart, *port;
	पूर्णांक ret, line, flags = dev_id->driver_data;

	अगर (flags & UNKNOWN_DEV) अणु
		ret = serial_pnp_guess_board(dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	स_रखो(&uart, 0, माप(uart));
	अगर (pnp_irq_valid(dev, 0))
		uart.port.irq = pnp_irq(dev, 0);
	अगर ((flags & CIR_PORT) && pnp_port_valid(dev, 2)) अणु
		uart.port.iobase = pnp_port_start(dev, 2);
		uart.port.iotype = UPIO_PORT;
	पूर्ण अन्यथा अगर (pnp_port_valid(dev, 0)) अणु
		uart.port.iobase = pnp_port_start(dev, 0);
		uart.port.iotype = UPIO_PORT;
	पूर्ण अन्यथा अगर (pnp_mem_valid(dev, 0)) अणु
		uart.port.mapbase = pnp_mem_start(dev, 0);
		uart.port.iotype = UPIO_MEM;
		uart.port.flags = UPF_IOREMAP;
	पूर्ण अन्यथा
		वापस -ENODEV;

	dev_dbg(&dev->dev,
		 "Setup PNP port: port %#lx, mem %#llx, irq %u, type %u\n",
		 uart.port.iobase, (अचिन्हित दीर्घ दीर्घ)uart.port.mapbase,
		 uart.port.irq, uart.port.iotype);

	अगर (flags & CIR_PORT) अणु
		uart.port.flags |= UPF_FIXED_PORT | UPF_FIXED_TYPE;
		uart.port.type = PORT_8250_CIR;
	पूर्ण

	uart.port.flags |= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF;
	अगर (pnp_irq_flags(dev, 0) & IORESOURCE_IRQ_SHAREABLE)
		uart.port.flags |= UPF_SHARE_IRQ;
	uart.port.uartclk = 1843200;
	uart.port.dev = &dev->dev;

	line = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (line < 0 || (flags & CIR_PORT))
		वापस -ENODEV;

	port = serial8250_get_port(line);
	अगर (uart_console(&port->port))
		dev->capabilities |= PNP_CONSOLE;

	pnp_set_drvdata(dev, (व्योम *)((दीर्घ)line + 1));
	वापस 0;
पूर्ण

अटल व्योम serial_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	दीर्घ line = (दीर्घ)pnp_get_drvdata(dev);

	dev->capabilities &= ~PNP_CONSOLE;
	अगर (line)
		serial8250_unरेजिस्टर_port(line - 1);
पूर्ण

अटल पूर्णांक __maybe_unused serial_pnp_suspend(काष्ठा device *dev)
अणु
	दीर्घ line = (दीर्घ)dev_get_drvdata(dev);

	अगर (!line)
		वापस -ENODEV;
	serial8250_suspend_port(line - 1);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused serial_pnp_resume(काष्ठा device *dev)
अणु
	दीर्घ line = (दीर्घ)dev_get_drvdata(dev);

	अगर (!line)
		वापस -ENODEV;
	serial8250_resume_port(line - 1);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(serial_pnp_pm_ops, serial_pnp_suspend, serial_pnp_resume);

अटल काष्ठा pnp_driver serial_pnp_driver = अणु
	.name		= "serial",
	.probe		= serial_pnp_probe,
	.हटाओ		= serial_pnp_हटाओ,
	.driver         = अणु
		.pm     = &serial_pnp_pm_ops,
	पूर्ण,
	.id_table	= pnp_dev_table,
पूर्ण;

पूर्णांक serial8250_pnp_init(व्योम)
अणु
	वापस pnp_रेजिस्टर_driver(&serial_pnp_driver);
पूर्ण

व्योम serial8250_pnp_निकास(व्योम)
अणु
	pnp_unरेजिस्टर_driver(&serial_pnp_driver);
पूर्ण

