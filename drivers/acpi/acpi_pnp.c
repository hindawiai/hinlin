<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI support क्रम PNP bus type
 *
 * Copyright (C) 2014, Intel Corporation
 * Authors: Zhang Rui <rui.zhang@पूर्णांकel.com>
 *          Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>

#समावेश "internal.h"

अटल स्थिर काष्ठा acpi_device_id acpi_pnp_device_ids[] = अणु
	/* pata_isapnp */
	अणु"PNP0600"पूर्ण,		/* Generic ESDI/IDE/ATA compatible hard disk controller */
	/* floppy */
	अणु"PNP0700"पूर्ण,
	/* tpm_inf_pnp */
	अणु"IFX0101"पूर्ण,		/* Infineon TPMs */
	अणु"IFX0102"पूर्ण,		/* Infineon TPMs */
	/*tpm_tis */
	अणु"PNP0C31"पूर्ण,		/* TPM */
	अणु"ATM1200"पूर्ण,		/* Aपंचांगel */
	अणु"IFX0102"पूर्ण,		/* Infineon */
	अणु"BCM0101"पूर्ण,		/* Broadcom */
	अणु"BCM0102"पूर्ण,		/* Broadcom */
	अणु"NSC1200"पूर्ण,		/* National */
	अणु"ICO0102"पूर्ण,		/* Intel */
	/* ide   */
	अणु"PNP0600"पूर्ण,		/* Generic ESDI/IDE/ATA compatible hard disk controller */
	/* ns558 */
	अणु"ASB16fd"पूर्ण,		/* AdLib NSC16 */
	अणु"AZT3001"पूर्ण,		/* AZT1008 */
	अणु"CDC0001"पूर्ण,		/* Opl3-SAx */
	अणु"CSC0001"पूर्ण,		/* CS4232 */
	अणु"CSC000f"पूर्ण,		/* CS4236 */
	अणु"CSC0101"पूर्ण,		/* CS4327 */
	अणु"CTL7001"पूर्ण,		/* SB16 */
	अणु"CTL7002"पूर्ण,		/* AWE64 */
	अणु"CTL7005"पूर्ण,		/* Vibra16 */
	अणु"ENS2020"पूर्ण,		/* SoundscapeVIVO */
	अणु"ESS0001"पूर्ण,		/* ES1869 */
	अणु"ESS0005"पूर्ण,		/* ES1878 */
	अणु"ESS6880"पूर्ण,		/* ES688 */
	अणु"IBM0012"पूर्ण,		/* CS4232 */
	अणु"OPT0001"पूर्ण,		/* OPTi Audio16 */
	अणु"YMH0006"पूर्ण,		/* Opl3-SA */
	अणु"YMH0022"पूर्ण,		/* Opl3-SAx */
	अणु"PNPb02f"पूर्ण,		/* Generic */
	/* i8042 kbd */
	अणु"PNP0300"पूर्ण,
	अणु"PNP0301"पूर्ण,
	अणु"PNP0302"पूर्ण,
	अणु"PNP0303"पूर्ण,
	अणु"PNP0304"पूर्ण,
	अणु"PNP0305"पूर्ण,
	अणु"PNP0306"पूर्ण,
	अणु"PNP0309"पूर्ण,
	अणु"PNP030a"पूर्ण,
	अणु"PNP030b"पूर्ण,
	अणु"PNP0320"पूर्ण,
	अणु"PNP0343"पूर्ण,
	अणु"PNP0344"पूर्ण,
	अणु"PNP0345"पूर्ण,
	अणु"CPQA0D7"पूर्ण,
	/* i8042 aux */
	अणु"AUI0200"पूर्ण,
	अणु"FJC6000"पूर्ण,
	अणु"FJC6001"पूर्ण,
	अणु"PNP0f03"पूर्ण,
	अणु"PNP0f0b"पूर्ण,
	अणु"PNP0f0e"पूर्ण,
	अणु"PNP0f12"पूर्ण,
	अणु"PNP0f13"पूर्ण,
	अणु"PNP0f19"पूर्ण,
	अणु"PNP0f1c"पूर्ण,
	अणु"SYN0801"पूर्ण,
	/* fcpnp */
	अणु"AVM0900"पूर्ण,
	/* radio-cadet */
	अणु"MSM0c24"पूर्ण,		/* ADS Cadet AM/FM Radio Card */
	/* radio-gemtek */
	अणु"ADS7183"पूर्ण,		/* AOpen FX-3D/Pro Radio */
	/* radio-sf16fmr2 */
	अणु"MFRad13"पूर्ण,		/* tuner subdevice of SF16-FMD2 */
	/* ene_ir */
	अणु"ENE0100"पूर्ण,
	अणु"ENE0200"पूर्ण,
	अणु"ENE0201"पूर्ण,
	अणु"ENE0202"पूर्ण,
	/* fपूर्णांकek-cir */
	अणु"FIT0002"पूर्ण,		/* CIR */
	/* ite-cir */
	अणु"ITE8704"पूर्ण,		/* Default model */
	अणु"ITE8713"पूर्ण,		/* CIR found in EEEBox 1501U */
	अणु"ITE8708"पूर्ण,		/* Bridged IT8512 */
	अणु"ITE8709"पूर्ण,		/* SRAM-Bridged IT8512 */
	/* nuvoton-cir */
	अणु"WEC0530"पूर्ण,		/* CIR */
	अणु"NTN0530"पूर्ण,		/* CIR क्रम new chip's pnp id */
	/* Winbond CIR */
	अणु"WEC1022"पूर्ण,
	/* wbsd */
	अणु"WEC0517"पूर्ण,
	अणु"WEC0518"पूर्ण,
	/* Winbond CIR */
	अणु"TCM5090"पूर्ण,		/* 3Com Etherlink III (TP) */
	अणु"TCM5091"पूर्ण,		/* 3Com Etherlink III */
	अणु"TCM5094"पूर्ण,		/* 3Com Etherlink III (combo) */
	अणु"TCM5095"पूर्ण,		/* 3Com Etherlink III (TPO) */
	अणु"TCM5098"पूर्ण,		/* 3Com Etherlink III (TPC) */
	अणु"PNP80f7"पूर्ण,		/* 3Com Etherlink III compatible */
	अणु"PNP80f8"पूर्ण,		/* 3Com Etherlink III compatible */
	/* nsc-ircc */
	अणु"NSC6001"पूर्ण,
	अणु"HWPC224"पूर्ण,
	अणु"IBM0071"पूर्ण,
	/* smsc-ircc2 */
	अणु"SMCf010"पूर्ण,
	/* sb1000 */
	अणु"GIC1000"पूर्ण,
	/* parport_pc */
	अणु"PNP0400"पूर्ण,		/* Standard LPT Prपूर्णांकer Port */
	अणु"PNP0401"पूर्ण,		/* ECP Prपूर्णांकer Port */
	/* apple-gmux */
	अणु"APP000B"पूर्ण,
	/* प्रणाली */
	अणु"PNP0c02"पूर्ण,		/* General ID क्रम reserving resources */
	अणु"PNP0c01"पूर्ण,		/* memory controller */
	/* rtc_cmos */
	अणु"PNP0b00"पूर्ण,
	अणु"PNP0b01"पूर्ण,
	अणु"PNP0b02"पूर्ण,
	/* c6xdigio */
	अणु"PNP0400"पूर्ण,		/* Standard LPT Prपूर्णांकer Port */
	अणु"PNP0401"पूर्ण,		/* ECP Prपूर्णांकer Port */
	/* ni_aपंचांगio.c */
	अणु"NIC1900"पूर्ण,
	अणु"NIC2400"पूर्ण,
	अणु"NIC2500"पूर्ण,
	अणु"NIC2600"पूर्ण,
	अणु"NIC2700"पूर्ण,
	/* serial */
	अणु"AAC000F"पूर्ण,		/* Archtek America Corp. Archtek SmartLink Modem 3334BT Plug & Play */
	अणु"ADC0001"पूर्ण,		/* Anchor Datacomm BV. SXPro 144 External Data Fax Modem Plug & Play */
	अणु"ADC0002"पूर्ण,		/* SXPro 288 External Data Fax Modem Plug & Play */
	अणु"AEI0250"पूर्ण,		/* PROLiNK 1456VH ISA PnP K56flex Fax Modem */
	अणु"AEI1240"पूर्ण,		/* Actiontec ISA PNP 56K X2 Fax Modem */
	अणु"AKY1021"पूर्ण,		/* Rockwell 56K ACF II Fax+Data+Voice Modem */
	अणु"ALI5123"पूर्ण,		/* ALi Fast Infrared Controller */
	अणु"AZT4001"पूर्ण,		/* AZT3005 PnP SOUND DEVICE */
	अणु"BDP3336"पूर्ण,		/* Best Data Products Inc. Smart One 336F PnP Modem */
	अणु"BRI0A49"पूर्ण,		/* Boca Complete Ofc Communicator 14.4 Data-FAX */
	अणु"BRI1400"पूर्ण,		/* Boca Research 33,600 ACF Modem */
	अणु"BRI3400"पूर्ण,		/* Boca 33.6 Kbps Internal FD34FSVD */
	अणु"BRI0A49"पूर्ण,		/* Boca 33.6 Kbps Internal FD34FSVD */
	अणु"BDP3336"पूर्ण,		/* Best Data Products Inc. Smart One 336F PnP Modem */
	अणु"CPI4050"पूर्ण,		/* Computer Peripherals Inc. EuroViVa CommCenter-33.6 SP PnP */
	अणु"CTL3001"पूर्ण,		/* Creative Lअसल Phone Blaster 28.8 DSVD PnP Voice */
	अणु"CTL3011"पूर्ण,		/* Creative Lअसल Modem Blaster 28.8 DSVD PnP Voice */
	अणु"DAV0336"पूर्ण,		/* Davicom ISA 33.6K Modem */
	अणु"DMB1032"पूर्ण,		/* Creative Modem Blaster Flash56 DI5601-1 */
	अणु"DMB2001"पूर्ण,		/* Creative Modem Blaster V.90 DI5660 */
	अणु"ETT0002"पूर्ण,		/* E-Tech CyberBULLET PC56RVP */
	अणु"FUJ0202"पूर्ण,		/* Fujitsu 33600 PnP-I2 R Plug & Play */
	अणु"FUJ0205"पूर्ण,		/* Fujitsu FMV-FX431 Plug & Play */
	अणु"FUJ0206"पूर्ण,		/* Fujitsu 33600 PnP-I4 R Plug & Play */
	अणु"FUJ0209"पूर्ण,		/* Fujitsu Fax Voice 33600 PNP-I5 R Plug & Play */
	अणु"GVC000F"पूर्ण,		/* Archtek SmartLink Modem 3334BT Plug & Play */
	अणु"GVC0303"पूर्ण,		/* Archtek SmartLink Modem 3334BRV 33.6K Data Fax Voice */
	अणु"HAY0001"पूर्ण,		/* Hayes Optima 288 V.34-V.FC + FAX + Voice Plug & Play */
	अणु"HAY000C"पूर्ण,		/* Hayes Optima 336 V.34 + FAX + Voice PnP */
	अणु"HAY000D"पूर्ण,		/* Hayes Optima 336B V.34 + FAX + Voice PnP */
	अणु"HAY5670"पूर्ण,		/* Hayes Accura 56K Ext Fax Modem PnP */
	अणु"HAY5674"पूर्ण,		/* Hayes Accura 56K Ext Fax Modem PnP */
	अणु"HAY5675"पूर्ण,		/* Hayes Accura 56K Fax Modem PnP */
	अणु"HAYF000"पूर्ण,		/* Hayes 288, V.34 + FAX */
	अणु"HAYF001"पूर्ण,		/* Hayes Optima 288 V.34 + FAX + Voice, Plug & Play */
	अणु"IBM0033"पूर्ण,		/* IBM Thinkpad 701 Internal Modem Voice */
	अणु"PNP4972"पूर्ण,		/* Intermec CV60 touchscreen port */
	अणु"IXDC801"पूर्ण,		/* Intertex 28k8 33k6 Voice EXT PnP */
	अणु"IXDC901"पूर्ण,		/* Intertex 33k6 56k Voice EXT PnP */
	अणु"IXDD801"पूर्ण,		/* Intertex 28k8 33k6 Voice SP EXT PnP */
	अणु"IXDD901"पूर्ण,		/* Intertex 33k6 56k Voice SP EXT PnP */
	अणु"IXDF401"पूर्ण,		/* Intertex 28k8 33k6 Voice SP INT PnP */
	अणु"IXDF801"पूर्ण,		/* Intertex 28k8 33k6 Voice SP EXT PnP */
	अणु"IXDF901"पूर्ण,		/* Intertex 33k6 56k Voice SP EXT PnP */
	अणु"KOR4522"पूर्ण,		/* KORTEX 28800 Externe PnP */
	अणु"KORF661"पूर्ण,		/* KXPro 33.6 Vocal ASVD PnP */
	अणु"LAS4040"पूर्ण,		/* LASAT Internet 33600 PnP */
	अणु"LAS4540"पूर्ण,		/* Lasat Safire 560 PnP */
	अणु"LAS5440"पूर्ण,		/* Lasat Safire 336  PnP */
	अणु"MNP0281"पूर्ण,		/* Microcom TravelPorte FAST V.34 Plug & Play */
	अणु"MNP0336"पूर्ण,		/* Microcom DeskPorte V.34 FAST or FAST+ Plug & Play */
	अणु"MNP0339"पूर्ण,		/* Microcom DeskPorte FAST EP 28.8 Plug & Play */
	अणु"MNP0342"पूर्ण,		/* Microcom DeskPorte 28.8P Plug & Play */
	अणु"MNP0500"पूर्ण,		/* Microcom DeskPorte FAST ES 28.8 Plug & Play */
	अणु"MNP0501"पूर्ण,		/* Microcom DeskPorte FAST ES 28.8 Plug & Play */
	अणु"MNP0502"पूर्ण,		/* Microcom DeskPorte 28.8S Internal Plug & Play */
	अणु"MOT1105"पूर्ण,		/* Motorola BitSURFR Plug & Play */
	अणु"MOT1111"पूर्ण,		/* Motorola TA210 Plug & Play */
	अणु"MOT1114"पूर्ण,		/* Motorola HMTA 200 (ISDN) Plug & Play */
	अणु"MOT1115"पूर्ण,		/* Motorola BitSURFR Plug & Play */
	अणु"MOT1190"पूर्ण,		/* Motorola Lअगरestyle 28.8 Internal */
	अणु"MOT1501"पूर्ण,		/* Motorola V.3400 Plug & Play */
	अणु"MOT1502"पूर्ण,		/* Motorola Lअगरestyle 28.8 V.34 Plug & Play */
	अणु"MOT1505"पूर्ण,		/* Motorola Power 28.8 V.34 Plug & Play */
	अणु"MOT1509"पूर्ण,		/* Motorola ModemSURFR External 28.8 Plug & Play */
	अणु"MOT150A"पूर्ण,		/* Motorola Premier 33.6 Desktop Plug & Play */
	अणु"MOT150F"पूर्ण,		/* Motorola VoiceSURFR 56K External PnP */
	अणु"MOT1510"पूर्ण,		/* Motorola ModemSURFR 56K External PnP */
	अणु"MOT1550"पूर्ण,		/* Motorola ModemSURFR 56K Internal PnP */
	अणु"MOT1560"पूर्ण,		/* Motorola ModemSURFR Internal 28.8 Plug & Play */
	अणु"MOT1580"पूर्ण,		/* Motorola Premier 33.6 Internal Plug & Play */
	अणु"MOT15B0"पूर्ण,		/* Motorola OnlineSURFR 28.8 Internal Plug & Play */
	अणु"MOT15F0"पूर्ण,		/* Motorola VoiceSURFR 56K Internal PnP */
	अणु"MVX00A1"पूर्ण,		/*  Deskline K56 Phone System PnP */
	अणु"MVX00F2"पूर्ण,		/* PC Rider K56 Phone System PnP */
	अणु"nEC8241"पूर्ण,		/* NEC 98NOTE SPEAKER PHONE FAX MODEM(33600bps) */
	अणु"PMC2430"पूर्ण,		/* Pace 56 Voice Internal Plug & Play Modem */
	अणु"PNP0500"पूर्ण,		/* Generic standard PC COM port     */
	अणु"PNP0501"पूर्ण,		/* Generic 16550A-compatible COM port */
	अणु"PNPC000"पूर्ण,		/* Compaq 14400 Modem */
	अणु"PNPC001"पूर्ण,		/* Compaq 2400/9600 Modem */
	अणु"PNPC031"पूर्ण,		/* Dial-Up Networking Serial Cable between 2 PCs */
	अणु"PNPC032"पूर्ण,		/* Dial-Up Networking Parallel Cable between 2 PCs */
	अणु"PNPC100"पूर्ण,		/* Standard 9600 bps Modem */
	अणु"PNPC101"पूर्ण,		/* Standard 14400 bps Modem */
	अणु"PNPC102"पूर्ण,		/*  Standard 28800 bps Modem */
	अणु"PNPC103"पूर्ण,		/*  Standard Modem */
	अणु"PNPC104"पूर्ण,		/*  Standard 9600 bps Modem */
	अणु"PNPC105"पूर्ण,		/*  Standard 14400 bps Modem */
	अणु"PNPC106"पूर्ण,		/*  Standard 28800 bps Modem */
	अणु"PNPC107"पूर्ण,		/*  Standard Modem */
	अणु"PNPC108"पूर्ण,		/* Standard 9600 bps Modem */
	अणु"PNPC109"पूर्ण,		/* Standard 14400 bps Modem */
	अणु"PNPC10A"पूर्ण,		/* Standard 28800 bps Modem */
	अणु"PNPC10B"पूर्ण,		/* Standard Modem */
	अणु"PNPC10C"पूर्ण,		/* Standard 9600 bps Modem */
	अणु"PNPC10D"पूर्ण,		/* Standard 14400 bps Modem */
	अणु"PNPC10E"पूर्ण,		/* Standard 28800 bps Modem */
	अणु"PNPC10F"पूर्ण,		/* Standard Modem */
	अणु"PNP2000"पूर्ण,		/* Standard PCMCIA Card Modem */
	अणु"ROK0030"पूर्ण,		/* Rockwell 33.6 DPF Internal PnP, Modular Technology 33.6 Internal PnP */
	अणु"ROK0100"पूर्ण,		/* KORTEX 14400 Externe PnP */
	अणु"ROK4120"पूर्ण,		/* Rockwell 28.8 */
	अणु"ROK4920"पूर्ण,		/* Viking 28.8 INTERNAL Fax+Data+Voice PnP */
	अणु"RSS00A0"पूर्ण,		/* Rockwell 33.6 DPF External PnP, BT Prologue 33.6 External PnP, Modular Technology 33.6 External PnP */
	अणु"RSS0262"पूर्ण,		/* Viking 56K FAX INT */
	अणु"RSS0250"पूर्ण,		/* K56 par,VV,Voice,Speakphone,AudioSpan,PnP */
	अणु"SUP1310"पूर्ण,		/* SupraExpress 28.8 Data/Fax PnP modem */
	अणु"SUP1381"पूर्ण,		/* SupraExpress 336i PnP Voice Modem */
	अणु"SUP1421"पूर्ण,		/* SupraExpress 33.6 Data/Fax PnP modem */
	अणु"SUP1590"पूर्ण,		/* SupraExpress 33.6 Data/Fax PnP modem */
	अणु"SUP1620"पूर्ण,		/* SupraExpress 336i Sp ASVD */
	अणु"SUP1760"पूर्ण,		/* SupraExpress 33.6 Data/Fax PnP modem */
	अणु"SUP2171"पूर्ण,		/* SupraExpress 56i Sp Intl */
	अणु"TEX0011"पूर्ण,		/* Phoebe Micro 33.6 Data Fax 1433VQH Plug & Play */
	अणु"UAC000F"पूर्ण,		/* Archtek SmartLink Modem 3334BT Plug & Play */
	अणु"USR0000"पूर्ण,		/* 3Com Corp. Gateway Telepath IIvi 33.6 */
	अणु"USR0002"पूर्ण,		/* U.S. Robotics Sporster 33.6K Fax INT PnP */
	अणु"USR0004"पूर्ण,		/*  Sportster Vi 14.4 PnP FAX Voicemail */
	अणु"USR0006"पूर्ण,		/* U.S. Robotics 33.6K Voice INT PnP */
	अणु"USR0007"पूर्ण,		/* U.S. Robotics 33.6K Voice EXT PnP */
	अणु"USR0009"पूर्ण,		/* U.S. Robotics Courier V.Everything INT PnP */
	अणु"USR2002"पूर्ण,		/* U.S. Robotics 33.6K Voice INT PnP */
	अणु"USR2070"पूर्ण,		/* U.S. Robotics 56K Voice INT PnP */
	अणु"USR2080"पूर्ण,		/* U.S. Robotics 56K Voice EXT PnP */
	अणु"USR3031"पूर्ण,		/* U.S. Robotics 56K FAX INT */
	अणु"USR3050"पूर्ण,		/* U.S. Robotics 56K FAX INT */
	अणु"USR3070"पूर्ण,		/* U.S. Robotics 56K Voice INT PnP */
	अणु"USR3080"पूर्ण,		/* U.S. Robotics 56K Voice EXT PnP */
	अणु"USR3090"पूर्ण,		/* U.S. Robotics 56K Voice INT PnP */
	अणु"USR9100"पूर्ण,		/* U.S. Robotics 56K Message  */
	अणु"USR9160"पूर्ण,		/* U.S. Robotics 56K FAX EXT PnP */
	अणु"USR9170"पूर्ण,		/* U.S. Robotics 56K FAX INT PnP */
	अणु"USR9180"पूर्ण,		/* U.S. Robotics 56K Voice EXT PnP */
	अणु"USR9190"पूर्ण,		/* U.S. Robotics 56K Voice INT PnP */
	अणु"WACFXXX"पूर्ण,		/* Wacom tablets */
	अणु"FPI2002"पूर्ण,		/* Compaq touchscreen */
	अणु"FUJ02B2"पूर्ण,		/* Fujitsu Stylistic touchscreens */
	अणु"FUJ02B3"पूर्ण,
	अणु"FUJ02B4"पूर्ण,		/* Fujitsu Stylistic LT touchscreens */
	अणु"FUJ02B6"पूर्ण,		/* Passive Fujitsu Stylistic touchscreens */
	अणु"FUJ02B7"पूर्ण,
	अणु"FUJ02B8"पूर्ण,
	अणु"FUJ02B9"पूर्ण,
	अणु"FUJ02BC"पूर्ण,
	अणु"FUJ02E5"पूर्ण,		/* Fujitsu Wacom Tablet PC device */
	अणु"FUJ02E6"पूर्ण,		/* Fujitsu P-series tablet PC device */
	अणु"FUJ02E7"पूर्ण,		/* Fujitsu Wacom 2FGT Tablet PC device */
	अणु"FUJ02E9"पूर्ण,		/* Fujitsu Wacom 1FGT Tablet PC device */
	अणु"LTS0001"पूर्ण,		/* LG C1 EXPRESS DUAL (C1-PB11A3) touch screen (actually a FUJ02E6 in disguise) */
	अणु"WCI0003"पूर्ण,		/* Rockwell's (PORALiNK) 33600 INT PNP */
	अणु"WEC1022"पूर्ण,		/* Winbond CIR port, should not be probed. We should keep track of it to prevent the legacy serial driver from probing it */
	/* scl200wdt */
	अणु"NSC0800"पूर्ण,		/* National Semiconductor PC87307/PC97307 watchकरोg component */
	/* mpu401 */
	अणु"PNPb006"पूर्ण,
	/* cs423x-pnpbios */
	अणु"CSC0100"पूर्ण,
	अणु"CSC0103"पूर्ण,
	अणु"CSC0110"पूर्ण,
	अणु"CSC0000"पूर्ण,
	अणु"GIM0100"पूर्ण,		/* Guillemot Turtlebeach something appears to be cs4232 compatible */
	/* es18xx-pnpbios */
	अणु"ESS1869"पूर्ण,
	अणु"ESS1879"पूर्ण,
	/* snd-opl3sa2-pnpbios */
	अणु"YMH0021"पूर्ण,
	अणु"NMX2210"पूर्ण,		/* Gateway Solo 2500 */
	अणु""पूर्ण,
पूर्ण;

अटल bool matching_id(स्थिर अक्षर *idstr, स्थिर अक्षर *list_id)
अणु
	पूर्णांक i;

	अगर (म_माप(idstr) != म_माप(list_id))
		वापस false;

	अगर (स_भेद(idstr, list_id, 3))
		वापस false;

	क्रम (i = 3; i < 7; i++) अणु
		अक्षर c = बड़े(idstr[i]);

		अगर (!है_षष्ठादशक(c)
		    || (list_id[i] != 'X' && c != बड़े(list_id[i])))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool acpi_pnp_match(स्थिर अक्षर *idstr, स्थिर काष्ठा acpi_device_id **matchid)
अणु
	स्थिर काष्ठा acpi_device_id *devid;

	क्रम (devid = acpi_pnp_device_ids; devid->id[0]; devid++)
		अगर (matching_id(idstr, (अक्षर *)devid->id)) अणु
			अगर (matchid)
				*matchid = devid;

			वापस true;
		पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक acpi_pnp_attach(काष्ठा acpi_device *adev,
			   स्थिर काष्ठा acpi_device_id *id)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा acpi_scan_handler acpi_pnp_handler = अणु
	.ids = acpi_pnp_device_ids,
	.match = acpi_pnp_match,
	.attach = acpi_pnp_attach,
पूर्ण;

/*
 * For CMOS RTC devices, the PNP ACPI scan handler करोes not work, because
 * there is a CMOS RTC ACPI scan handler installed alपढ़ोy, so we need to
 * check those devices and क्रमागतerate them to the PNP bus directly.
 */
अटल पूर्णांक is_cmos_rtc_device(काष्ठा acpi_device *adev)
अणु
	अटल स्थिर काष्ठा acpi_device_id ids[] = अणु
		अणु "PNP0B00" पूर्ण,
		अणु "PNP0B01" पूर्ण,
		अणु "PNP0B02" पूर्ण,
		अणु""पूर्ण,
	पूर्ण;
	वापस !acpi_match_device_ids(adev, ids);
पूर्ण

bool acpi_is_pnp_device(काष्ठा acpi_device *adev)
अणु
	वापस adev->handler == &acpi_pnp_handler || is_cmos_rtc_device(adev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_is_pnp_device);

व्योम __init acpi_pnp_init(व्योम)
अणु
	acpi_scan_add_handler(&acpi_pnp_handler);
पूर्ण
