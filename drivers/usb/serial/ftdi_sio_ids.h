<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * venकरोr/product IDs (VID/PID) of devices using FTDI USB serial converters.
 * Please keep numerically sorted within inभागidual areas, thanks!
 *
 * Philipp Gथञhring - pg@futureware.at - added the Device ID of the USB relais
 * from Ruकरोlf Gugler
 *
 */


/**********************************/
/***** devices using FTDI VID *****/
/**********************************/


#घोषणा FTDI_VID	0x0403	/* Venकरोr Id */


/*** "original" FTDI device PIDs ***/

#घोषणा FTDI_8U232AM_PID 0x6001 /* Similar device to SIO above */
#घोषणा FTDI_8U232AM_ALT_PID 0x6006 /* FTDI's alternate PID क्रम above */
#घोषणा FTDI_8U2232C_PID 0x6010 /* Dual channel device */
#घोषणा FTDI_4232H_PID 0x6011 /* Quad channel hi-speed device */
#घोषणा FTDI_232H_PID  0x6014 /* Single channel hi-speed device */
#घोषणा FTDI_FTX_PID   0x6015 /* FT-X series (FT201X, FT230X, FT231X, etc) */
#घोषणा FTDI_SIO_PID	0x8372	/* Product Id SIO application of 8U100AX */
#घोषणा FTDI_232RL_PID  0xFBFA  /* Product ID क्रम FT232RL */


/*** third-party PIDs (using FTDI_VID) ***/

/*
 * Certain versions of the official Winकरोws FTDI driver reprogrammed
 * counterfeit FTDI devices to PID 0. Support these devices anyway.
 */
#घोषणा FTDI_BRICK_PID		0x0000

#घोषणा FTDI_LUMEL_PD12_PID	0x6002

/*
 * Custom USB adapters made by Falconia Partners LLC
 * क्रम FreeCalypso project, ID codes allocated to Falconia by FTDI.
 */
#घोषणा FTDI_FALCONIA_JTAG_BUF_PID	0x7150
#घोषणा FTDI_FALCONIA_JTAG_UNBUF_PID	0x7151

/* Sienna Serial Interface by Secyourit GmbH */
#घोषणा FTDI_SIENNA_PID		0x8348

/* Cyber Cortex AV by Fabulous Silicon (http://fabuloussilicon.com) */
#घोषणा CYBER_CORTEX_AV_PID	0x8698

/*
 * Marvell OpenRD Base, Client
 * http://www.खोलो-rd.org
 * OpenRD Base, Client use VID 0x0403
 */
#घोषणा MARVELL_OPENRD_PID	0x9e90

/* www.candapter.com Ewert Energy Systems CANdapter device */
#घोषणा FTDI_CANDAPTER_PID 0x9F80 /* Product Id */

#घोषणा FTDI_BM_ATOM_न_अंकO_PID	0xa559	/* Basic Micro ATOM Nano USB2Serial */

/*
 * Texas Instruments XDS100v2 JTAG / BeagleBone A3
 * http://processors.wiki.ti.com/index.php/XDS100
 * http://beagleboard.org/bone
 */
#घोषणा TI_XDS100V2_PID		0xa6d0

#घोषणा FTDI_NXTCAM_PID		0xABB8 /* NXTCam क्रम Mindstorms NXT */
#घोषणा FTDI_EV3CON_PID		0xABB9 /* Mindstorms EV3 Console Adapter */

/* US Interface Navigator (http://www.usपूर्णांकerface.com/) */
#घोषणा FTDI_USINT_CAT_PID	0xb810	/* Navigator CAT and 2nd PTT lines */
#घोषणा FTDI_USINT_WKEY_PID	0xb811	/* Navigator WKEY and FSK lines */
#घोषणा FTDI_USINT_RS232_PID	0xb812	/* Navigator RS232 and CONFIG lines */

/* OOCDlink by Joern Kaipf <joernk@web.de>
 * (http://www.joernonline.de/) */
#घोषणा FTDI_OOCDLINK_PID	0xbaf8	/* Amontec JTAGkey */

/* Luminary Micro Stellaris Boards, VID = FTDI_VID */
/* FTDI 2332C Dual channel device, side A=245 FIFO (JTAG), Side B=RS232 UART */
#घोषणा LMI_LM3S_DEVEL_BOARD_PID	0xbcd8
#घोषणा LMI_LM3S_EVAL_BOARD_PID		0xbcd9
#घोषणा LMI_LM3S_ICDI_BOARD_PID		0xbcda

#घोषणा FTDI_TURTELIZER_PID	0xBDC8 /* JTAG/RS-232 adapter by egnite GmbH */

/* OpenDCC (www.खोलोdcc.de) product id */
#घोषणा FTDI_OPENDCC_PID	0xBFD8
#घोषणा FTDI_OPENDCC_SNIFFER_PID	0xBFD9
#घोषणा FTDI_OPENDCC_THROTTLE_PID	0xBFDA
#घोषणा FTDI_OPENDCC_GATEWAY_PID	0xBFDB
#घोषणा FTDI_OPENDCC_GBM_PID	0xBFDC
#घोषणा FTDI_OPENDCC_GBM_BOOST_PID	0xBFDD

/* NZR SEM 16+ USB (http://www.nzr.de) */
#घोषणा FTDI_NZR_SEM_USB_PID	0xC1E0	/* NZR SEM-LOG16+ */

/*
 * RR-CirKits LocoBuffer USB (http://www.rr-cirkits.com)
 */
#घोषणा FTDI_RRCIRKITS_LOCOBUFFER_PID	0xc7d0	/* LocoBuffer USB */

/* DMX4ALL DMX Interfaces */
#घोषणा FTDI_DMX4ALL 0xC850

/*
 * ASK.fr devices
 */
#घोषणा FTDI_ASK_RDR400_PID	0xC991	/* ASK RDR 400 series card पढ़ोer */

/* www.starting-poपूर्णांक-प्रणालीs.com तगChameleon device */
#घोषणा FTDI_MICRO_CHAMELEON_PID	0xCAA0	/* Product Id */

/*
 * Tactrix OpenPort (ECU) devices.
 * OpenPort 1.3M submitted by Donour Sizemore.
 * OpenPort 1.3S and 1.3U submitted by Ian Abbott.
 */
#घोषणा FTDI_TACTRIX_OPENPORT_13M_PID	0xCC48	/* OpenPort 1.3 Mitsubishi */
#घोषणा FTDI_TACTRIX_OPENPORT_13S_PID	0xCC49	/* OpenPort 1.3 Subaru */
#घोषणा FTDI_TACTRIX_OPENPORT_13U_PID	0xCC4A	/* OpenPort 1.3 Universal */

#घोषणा FTDI_DISTORTEC_JTAG_LOCK_PICK_PID	0xCFF8

/* SCS HF Radio Modems PID's (http://www.scs-ptc.com) */
/* the VID is the standard ftdi vid (FTDI_VID) */
#घोषणा FTDI_SCS_DEVICE_0_PID 0xD010    /* SCS PTC-IIusb */
#घोषणा FTDI_SCS_DEVICE_1_PID 0xD011    /* SCS Tracker / DSP TNC */
#घोषणा FTDI_SCS_DEVICE_2_PID 0xD012
#घोषणा FTDI_SCS_DEVICE_3_PID 0xD013
#घोषणा FTDI_SCS_DEVICE_4_PID 0xD014
#घोषणा FTDI_SCS_DEVICE_5_PID 0xD015
#घोषणा FTDI_SCS_DEVICE_6_PID 0xD016
#घोषणा FTDI_SCS_DEVICE_7_PID 0xD017

/* iPlus device */
#घोषणा FTDI_IPLUS_PID 0xD070 /* Product Id */
#घोषणा FTDI_IPLUS2_PID 0xD071 /* Product Id */

/*
 * Gamma Scout (http://gamma-scout.com/). Submitted by rsc@runtux.com.
 */
#घोषणा FTDI_GAMMA_SCOUT_PID		0xD678	/* Gamma Scout online */

/* Propox devices */
#घोषणा FTDI_PROPOX_JTAGCABLEII_PID	0xD738
#घोषणा FTDI_PROPOX_ISPCABLEIII_PID	0xD739

/* Lenz LI-USB Computer Interface. */
#घोषणा FTDI_LENZ_LIUSB_PID	0xD780

/* Vardaan Enterprises Serial Interface VEUSB422R3 */
#घोषणा FTDI_VARDAAN_PID	0xF070

/*
 * Xsens Technologies BV products (http://www.xsens.com).
 */
#घोषणा XSENS_VID		0x2639
#घोषणा XSENS_AWINDA_STATION_PID 0x0101
#घोषणा XSENS_AWINDA_DONGLE_PID 0x0102
#घोषणा XSENS_MTW_PID		0x0200	/* Xsens MTw */
#घोषणा XSENS_MTDEVBOARD_PID	0x0300	/* Motion Tracker Development Board */
#घोषणा XSENS_MTIUSBCONVERTER_PID	0x0301	/* MTi USB converter */
#घोषणा XSENS_CONVERTER_PID	0xD00D	/* Xsens USB-serial converter */

/* Xsens devices using FTDI VID */
#घोषणा XSENS_CONVERTER_0_PID	0xD388	/* Xsens USB converter */
#घोषणा XSENS_CONVERTER_1_PID	0xD389	/* Xsens Wireless Receiver */
#घोषणा XSENS_CONVERTER_2_PID	0xD38A
#घोषणा XSENS_CONVERTER_3_PID	0xD38B	/* Xsens USB-serial converter */
#घोषणा XSENS_CONVERTER_4_PID	0xD38C	/* Xsens Wireless Receiver */
#घोषणा XSENS_CONVERTER_5_PID	0xD38D	/* Xsens Awinda Station */
#घोषणा XSENS_CONVERTER_6_PID	0xD38E
#घोषणा XSENS_CONVERTER_7_PID	0xD38F

/**
 * Zolix (www.zolix.com.cb) product ids
 */
#घोषणा FTDI_OMNI1509			0xD491	/* Omni1509 embedded USB-serial */

/*
 * NDI (www.ndigital.com) product ids
 */
#घोषणा FTDI_NDI_HUC_PID		0xDA70	/* NDI Host USB Converter */
#घोषणा FTDI_NDI_SPECTRA_SCU_PID	0xDA71	/* NDI Spectra SCU */
#घोषणा FTDI_NDI_FUTURE_2_PID		0xDA72	/* NDI future device #2 */
#घोषणा FTDI_NDI_FUTURE_3_PID		0xDA73	/* NDI future device #3 */
#घोषणा FTDI_NDI_AURORA_SCU_PID		0xDA74	/* NDI Aurora SCU */

/*
 * ChamSys Limited (www.chamsys.co.uk) USB wing/पूर्णांकerface product IDs
 */
#घोषणा FTDI_CHAMSYS_24_MASTER_WING_PID        0xDAF8
#घोषणा FTDI_CHAMSYS_PC_WING_PID       0xDAF9
#घोषणा FTDI_CHAMSYS_USB_DMX_PID       0xDAFA
#घोषणा FTDI_CHAMSYS_MIDI_TIMECODE_PID 0xDAFB
#घोषणा FTDI_CHAMSYS_MINI_WING_PID     0xDAFC
#घोषणा FTDI_CHAMSYS_MAXI_WING_PID     0xDAFD
#घोषणा FTDI_CHAMSYS_MEDIA_WING_PID    0xDAFE
#घोषणा FTDI_CHAMSYS_WING_PID  0xDAFF

/*
 * Westrex International devices submitted by Cory Lee
 */
#घोषणा FTDI_WESTREX_MODEL_777_PID	0xDC00	/* Model 777 */
#घोषणा FTDI_WESTREX_MODEL_8900F_PID	0xDC01	/* Model 8900F */

/*
 * ACG Identअगरication Technologies GmbH products (http://www.acg.de/).
 * Submitted by anton -at- जाओ10 -करोt- org.
 */
#घोषणा FTDI_ACG_HFDUAL_PID		0xDD20	/* HF Dual ISO Reader (RFID) */

/*
 * Definitions क्रम Artemis astronomical USB based cameras
 * Check it at http://www.artemisccd.co.uk/
 */
#घोषणा FTDI_ARTEMIS_PID	0xDF28	/* All Artemis Cameras */

/*
 * Definitions क्रम ATIK Instruments astronomical USB based cameras
 * Check it at http://www.atik-instruments.com/
 */
#घोषणा FTDI_ATIK_ATK16_PID	0xDF30	/* ATIK ATK-16 Grayscale Camera */
#घोषणा FTDI_ATIK_ATK16C_PID	0xDF32	/* ATIK ATK-16C Colour Camera */
#घोषणा FTDI_ATIK_ATK16HR_PID	0xDF31	/* ATIK ATK-16HR Grayscale Camera */
#घोषणा FTDI_ATIK_ATK16HRC_PID	0xDF33	/* ATIK ATK-16HRC Colour Camera */
#घोषणा FTDI_ATIK_ATK16IC_PID   0xDF35  /* ATIK ATK-16IC Grayscale Camera */

/*
 * Yost Engineering, Inc. products (www.yostengineering.com).
 * PID 0xE050 submitted by Aaron Prose.
 */
#घोषणा FTDI_YEI_SERVOCENTER31_PID	0xE050	/* YEI ServoCenter3.1 USB */

/*
 * ELV USB devices submitted by Christian Abt of ELV (www.elv.de).
 * Almost all of these devices use FTDI's venकरोr ID (0x0403).
 * Further IDs taken from ELV Winकरोws .inf file.
 *
 * The previously included PID क्रम the UO 100 module was incorrect.
 * In fact, that PID was क्रम ELV's UR 100 USB-RS232 converter (0xFB58).
 *
 * Armin Laeuger originally sent the PID क्रम the UM 100 module.
 */
#घोषणा FTDI_ELV_VID	0x1B1F	/* ELV AG */
#घोषणा FTDI_ELV_WS300_PID	0xC006	/* eQ3 WS 300 PC II */
#घोषणा FTDI_ELV_USR_PID	0xE000	/* ELV Universal-Sound-Recorder */
#घोषणा FTDI_ELV_MSM1_PID	0xE001	/* ELV Mini-Sound-Modul */
#घोषणा FTDI_ELV_KL100_PID	0xE002	/* ELV Kfz-Leistungsmesser KL 100 */
#घोषणा FTDI_ELV_WS550_PID	0xE004	/* WS 550 */
#घोषणा FTDI_ELV_EC3000_PID	0xE006	/* ENERGY CONTROL 3000 USB */
#घोषणा FTDI_ELV_WS888_PID	0xE008	/* WS 888 */
#घोषणा FTDI_ELV_TWS550_PID	0xE009	/* Technoline WS 550 */
#घोषणा FTDI_ELV_FEM_PID	0xE00A	/* Funk Energie Monitor */
#घोषणा FTDI_ELV_FHZ1300PC_PID	0xE0E8	/* FHZ 1300 PC */
#घोषणा FTDI_ELV_WS500_PID	0xE0E9	/* PC-Wetterstation (WS 500) */
#घोषणा FTDI_ELV_HS485_PID	0xE0EA	/* USB to RS-485 adapter */
#घोषणा FTDI_ELV_UMS100_PID	0xE0EB	/* ELV USB Master-Slave Schaltsteckकरोse UMS 100 */
#घोषणा FTDI_ELV_TFD128_PID	0xE0EC	/* ELV Temperatur-Feuchte-Datenlogger TFD 128 */
#घोषणा FTDI_ELV_FM3RX_PID	0xE0ED	/* ELV Messwertuebertragung FM3 RX */
#घोषणा FTDI_ELV_WS777_PID	0xE0EE	/* Conrad WS 777 */
#घोषणा FTDI_ELV_EM1010PC_PID	0xE0EF	/* Energy monitor EM 1010 PC */
#घोषणा FTDI_ELV_CSI8_PID	0xE0F0	/* Computer-Schalt-Interface (CSI 8) */
#घोषणा FTDI_ELV_EM1000DL_PID	0xE0F1	/* PC-Datenlogger fuer Energiemonitor (EM 1000 DL) */
#घोषणा FTDI_ELV_PCK100_PID	0xE0F2	/* PC-Kabeltester (PCK 100) */
#घोषणा FTDI_ELV_RFP500_PID	0xE0F3	/* HF-Leistungsmesser (RFP 500) */
#घोषणा FTDI_ELV_FS20SIG_PID	0xE0F4	/* Signalgeber (FS 20 SIG) */
#घोषणा FTDI_ELV_UTP8_PID	0xE0F5	/* ELV UTP 8 */
#घोषणा FTDI_ELV_WS300PC_PID	0xE0F6	/* PC-Wetterstation (WS 300 PC) */
#घोषणा FTDI_ELV_WS444PC_PID	0xE0F7	/* Conrad WS 444 PC */
#घोषणा FTDI_PHI_FISCO_PID      0xE40B  /* PHI Fisco USB to Serial cable */
#घोषणा FTDI_ELV_UAD8_PID	0xF068	/* USB-AD-Wandler (UAD 8) */
#घोषणा FTDI_ELV_UDA7_PID	0xF069	/* USB-DA-Wandler (UDA 7) */
#घोषणा FTDI_ELV_USI2_PID	0xF06A	/* USB-Schritपंचांगotoren-Interface (USI 2) */
#घोषणा FTDI_ELV_T1100_PID	0xF06B	/* Thermometer (T 1100) */
#घोषणा FTDI_ELV_PCD200_PID	0xF06C	/* PC-Datenlogger (PCD 200) */
#घोषणा FTDI_ELV_ULA200_PID	0xF06D	/* USB-LCD-Ansteuerung (ULA 200) */
#घोषणा FTDI_ELV_ALC8500_PID	0xF06E	/* ALC 8500 Expert */
#घोषणा FTDI_ELV_FHZ1000PC_PID	0xF06F	/* FHZ 1000 PC */
#घोषणा FTDI_ELV_UR100_PID	0xFB58	/* USB-RS232-Umsetzer (UR 100) */
#घोषणा FTDI_ELV_UM100_PID	0xFB5A	/* USB-Modul UM 100 */
#घोषणा FTDI_ELV_UO100_PID	0xFB5B	/* USB-Modul UO 100 */
/* Additional ELV PIDs that शेष to using the FTDI D2XX drivers on
 * MS Winकरोws, rather than the FTDI Virtual Com Port drivers.
 * Maybe these will be easier to use with the libftdi/libusb user-space
 * drivers, or possibly the Comedi drivers in some हालs. */
#घोषणा FTDI_ELV_CLI7000_PID	0xFB59	/* Computer-Light-Interface (CLI 7000) */
#घोषणा FTDI_ELV_PPS7330_PID	0xFB5C	/* Processor-Power-Supply (PPS 7330) */
#घोषणा FTDI_ELV_TFM100_PID	0xFB5D	/* Temperatur-Feuchte-Messgeraet (TFM 100) */
#घोषणा FTDI_ELV_UDF77_PID	0xFB5E	/* USB DCF Funkuhr (UDF 77) */
#घोषणा FTDI_ELV_UIO88_PID	0xFB5F	/* USB-I/O Interface (UIO 88) */

/*
 * EVER Eco Pro UPS (http://www.ever.com.pl/)
 */

#घोषणा	EVER_ECO_PRO_CDS	0xe520	/* RS-232 converter */

/*
 * Active Robots product ids.
 */
#घोषणा FTDI_ACTIVE_ROBOTS_PID	0xE548	/* USB comms board */

/* Pyramid Computer GmbH */
#घोषणा FTDI_PYRAMID_PID	0xE6C8	/* Pyramid Appliance Display */

/* www.elsterelectricity.com Elster Unicom III Optical Probe */
#घोषणा FTDI_ELSTER_UNICOM_PID		0xE700 /* Product Id */

/*
 * Gude Analog- und Digitalप्रणालीe GmbH
 */
#घोषणा FTDI_GUDEADS_E808_PID    0xE808
#घोषणा FTDI_GUDEADS_E809_PID    0xE809
#घोषणा FTDI_GUDEADS_E80A_PID    0xE80A
#घोषणा FTDI_GUDEADS_E80B_PID    0xE80B
#घोषणा FTDI_GUDEADS_E80C_PID    0xE80C
#घोषणा FTDI_GUDEADS_E80D_PID    0xE80D
#घोषणा FTDI_GUDEADS_E80E_PID    0xE80E
#घोषणा FTDI_GUDEADS_E80F_PID    0xE80F
#घोषणा FTDI_GUDEADS_E888_PID    0xE888  /* Expert ISDN Control USB */
#घोषणा FTDI_GUDEADS_E889_PID    0xE889  /* USB RS-232 OptoBridge */
#घोषणा FTDI_GUDEADS_E88A_PID    0xE88A
#घोषणा FTDI_GUDEADS_E88B_PID    0xE88B
#घोषणा FTDI_GUDEADS_E88C_PID    0xE88C
#घोषणा FTDI_GUDEADS_E88D_PID    0xE88D
#घोषणा FTDI_GUDEADS_E88E_PID    0xE88E
#घोषणा FTDI_GUDEADS_E88F_PID    0xE88F

/*
 * Eclo (http://www.eclo.pt/) product IDs.
 * PID 0xEA90 submitted by Martin Grill.
 */
#घोषणा FTDI_ECLO_COM_1WIRE_PID	0xEA90	/* COM to 1-Wire USB adaptor */

/* TNC-X USB-to-packet-radio adapter, versions prior to 3.0 (DLP module) */
#घोषणा FTDI_TNC_X_PID		0xEBE0

/*
 * Teratronik product ids.
 * Submitted by O. Wथघlfelschneider.
 */
#घोषणा FTDI_TERATRONIK_VCP_PID	 0xEC88	/* Teratronik device (preferring VCP driver on winकरोws) */
#घोषणा FTDI_TERATRONIK_D2XX_PID 0xEC89	/* Teratronik device (preferring D2XX driver on winकरोws) */

/* Rig Expert Ukraine devices */
#घोषणा FTDI_REU_TINY_PID		0xED22	/* RigExpert Tiny */

/*
 * Hameg HO820 and HO870 पूर्णांकerface (using VID 0x0403)
 */
#घोषणा HAMEG_HO820_PID			0xed74
#घोषणा HAMEG_HO730_PID			0xed73
#घोषणा HAMEG_HO720_PID			0xed72
#घोषणा HAMEG_HO870_PID			0xed71

/*
 *  MaxStream devices	www.maxstream.net
 */
#घोषणा FTDI_MAXSTREAM_PID	0xEE18	/* Xbee PKG-U Module */

/*
 * microHAM product IDs (http://www.microham.com).
 * Submitted by Justin Burket (KL1RL) <zorton@jtan.com>
 * and Mike Studer (K6EEP) <k6eep@hamsoftware.org>.
 * Ian Abbott <abbotti@mev.co.uk> added a few more from the driver INF file.
 */
#घोषणा FTDI_MHAM_KW_PID	0xEEE8	/* USB-KW पूर्णांकerface */
#घोषणा FTDI_MHAM_YS_PID	0xEEE9	/* USB-YS पूर्णांकerface */
#घोषणा FTDI_MHAM_Y6_PID	0xEEEA	/* USB-Y6 पूर्णांकerface */
#घोषणा FTDI_MHAM_Y8_PID	0xEEEB	/* USB-Y8 पूर्णांकerface */
#घोषणा FTDI_MHAM_IC_PID	0xEEEC	/* USB-IC पूर्णांकerface */
#घोषणा FTDI_MHAM_DB9_PID	0xEEED	/* USB-DB9 पूर्णांकerface */
#घोषणा FTDI_MHAM_RS232_PID	0xEEEE	/* USB-RS232 पूर्णांकerface */
#घोषणा FTDI_MHAM_Y9_PID	0xEEEF	/* USB-Y9 पूर्णांकerface */

/* Domपूर्णांकell products  http://www.करोmपूर्णांकell.com */
#घोषणा FTDI_DOMINTELL_DGQG_PID	0xEF50	/* Master */
#घोषणा FTDI_DOMINTELL_DUSB_PID	0xEF51	/* DUSB01 module */

/*
 * The following are the values क्रम the Perle Systems
 * UltraPort USB serial converters
 */
#घोषणा FTDI_PERLE_ULTRAPORT_PID 0xF0C0	/* Perle UltraPort Product Id */

/* Sprog II (Andrew Crosland's SprogII DCC पूर्णांकerface) */
#घोषणा FTDI_SPROG_II		0xF0C8

/*
 * Two of the Tagsys RFID Readers
 */
#घोषणा FTDI_TAGSYS_LP101_PID	0xF0E9	/* Tagsys L-P101 RFID*/
#घोषणा FTDI_TAGSYS_P200X_PID	0xF0EE	/* Tagsys Medio P200x RFID*/

/* an infrared receiver क्रम user access control with IR tags */
#घोषणा FTDI_PIEGROUP_PID	0xF208	/* Product Id */

/* ACT Solutions HomePro ZWave पूर्णांकerface
   (http://www.act-solutions.com/HomePro-Product-Matrix.hपंचांगl) */
#घोषणा FTDI_ACTZWAVE_PID	0xF2D0

/*
 * 4N-GALAXY.DE PIDs क्रम CAN-USB, USB-RS232, USB-RS422, USB-RS485,
 * USB-TTY aktiv, USB-TTY passiv.  Some PIDs are used by several devices
 * and I'm not entirely sure which are used by which.
 */
#घोषणा FTDI_4N_GALAXY_DE_1_PID	0xF3C0
#घोषणा FTDI_4N_GALAXY_DE_2_PID	0xF3C1
#घोषणा FTDI_4N_GALAXY_DE_3_PID	0xF3C2

/*
 * Ivium Technologies product IDs
 */
#घोषणा FTDI_PALMSENS_PID	0xf440
#घोषणा FTDI_IVIUM_XSTAT_PID	0xf441

/*
 * Linx Technologies product ids
 */
#घोषणा LINX_SDMUSBQSS_PID	0xF448	/* Linx SDM-USB-QS-S */
#घोषणा LINX_MASTERDEVEL2_PID   0xF449	/* Linx Master Development 2.0 */
#घोषणा LINX_FUTURE_0_PID   0xF44A	/* Linx future device */
#घोषणा LINX_FUTURE_1_PID   0xF44B	/* Linx future device */
#घोषणा LINX_FUTURE_2_PID   0xF44C	/* Linx future device */

/*
 * Oceanic product ids
 */
#घोषणा FTDI_OCEANIC_PID	0xF460  /* Oceanic भागe instrument */

/*
 * SUUNTO product ids
 */
#घोषणा FTDI_SUUNTO_SPORTS_PID	0xF680	/* Suunto Sports instrument */

/* USB-UIRT - An infrared receiver and transmitter using the 8U232AM chip */
/* http://www.usbuirt.com/ */
#घोषणा FTDI_USB_UIRT_PID	0xF850	/* Product Id */

/* CCS Inc. ICDU/ICDU40 product ID -
 * the FT232BM is used in an in-circuit-debugger unit क्रम PIC16's/PIC18's */
#घोषणा FTDI_CCSICDU20_0_PID    0xF9D0
#घोषणा FTDI_CCSICDU40_1_PID    0xF9D1
#घोषणा FTDI_CCSMACHX_2_PID     0xF9D2
#घोषणा FTDI_CCSLOAD_N_GO_3_PID 0xF9D3
#घोषणा FTDI_CCSICDU64_4_PID    0xF9D4
#घोषणा FTDI_CCSPRIME8_5_PID    0xF9D5

/*
 * The following are the values क्रम the Matrix Orbital LCD displays,
 * which are the FT232BM ( similar to the 8U232AM )
 */
#घोषणा FTDI_MTXORB_0_PID      0xFA00  /* Matrix Orbital Product Id */
#घोषणा FTDI_MTXORB_1_PID      0xFA01  /* Matrix Orbital Product Id */
#घोषणा FTDI_MTXORB_2_PID      0xFA02  /* Matrix Orbital Product Id */
#घोषणा FTDI_MTXORB_3_PID      0xFA03  /* Matrix Orbital Product Id */
#घोषणा FTDI_MTXORB_4_PID      0xFA04  /* Matrix Orbital Product Id */
#घोषणा FTDI_MTXORB_5_PID      0xFA05  /* Matrix Orbital Product Id */
#घोषणा FTDI_MTXORB_6_PID      0xFA06  /* Matrix Orbital Product Id */

/*
 * Home Electronics (www.home-electro.com) USB gadमाला_लो
 */
#घोषणा FTDI_HE_TIRA1_PID	0xFA78	/* Tira-1 IR transceiver */

/* Inside Accesso contactless पढ़ोer (http://www.insidecontactless.com/) */
#घोषणा INSIDE_ACCESSO		0xFAD0

/*
 * ThorLअसल USB motor drivers
 */
#घोषणा FTDI_THORLABS_PID		0xfaf0 /* ThorLअसल USB motor drivers */

/*
 * Protego product ids
 */
#घोषणा PROTEGO_SPECIAL_1	0xFC70	/* special/unknown device */
#घोषणा PROTEGO_R2X0		0xFC71	/* R200-USB TRNG unit (R210, R220, and R230) */
#घोषणा PROTEGO_SPECIAL_3	0xFC72	/* special/unknown device */
#घोषणा PROTEGO_SPECIAL_4	0xFC73	/* special/unknown device */

/*
 * Sony Ericsson product ids
 */
#घोषणा FTDI_DSS20_PID		0xFC82	/* DSS-20 Sync Station क्रम Sony Ericsson P800 */
#घोषणा FTDI_URBAN_0_PID	0xFC8A	/* Sony Ericsson Urban, uart #0 */
#घोषणा FTDI_URBAN_1_PID	0xFC8B	/* Sony Ericsson Urban, uart #1 */

/* www.irtrans.de device */
#घोषणा FTDI_IRTRANS_PID 0xFC60 /* Product Id */

/*
 * RM Michaelides CANview USB (http://www.rmcan.com) (FTDI_VID)
 * CAN fieldbus पूर्णांकerface adapter, added by port GmbH www.port.de)
 * Ian Abbott changed the macro names क्रम consistency.
 */
#घोषणा FTDI_RM_CANVIEW_PID	0xfd60	/* Product Id */
/* www.thoughttechnology.com/ TT-USB provide with procomp use ftdi_sio */
#घोषणा FTDI_TTUSB_PID 0xFF20 /* Product Id */

#घोषणा FTDI_USBX_707_PID 0xF857	/* ADSTech IR Blaster USBX-707 (FTDI_VID) */

#घोषणा FTDI_RELAIS_PID	0xFA10  /* Relais device from Ruकरोlf Gugler */

/*
 * PCDJ use ftdi based dj-controllers. The following PID is
 * क्रम their DAC-2 device http://www.pcdjhardware.com/DAC2.asp
 * (the VID is the standard ftdi vid (FTDI_VID), PID sent by Wouter Paesen)
 */
#घोषणा FTDI_PCDJ_DAC2_PID 0xFA88

#घोषणा FTDI_R2000KU_TRUE_RNG	0xFB80  /* R2000KU TRUE RNG (FTDI_VID) */

/*
 * DIEBOLD BCS SE923 (FTDI_VID)
 */
#घोषणा DIEBOLD_BCS_SE923_PID	0xfb99

/* www.crystalfontz.com devices
 * - thanx क्रम providing मुक्त devices क्रम evaluation !
 * they use the ftdi chipset क्रम the USB पूर्णांकerface
 * and the venकरोr id is the same
 */
#घोषणा FTDI_XF_632_PID 0xFC08	/* 632: 16x2 Character Display */
#घोषणा FTDI_XF_634_PID 0xFC09	/* 634: 20x4 Character Display */
#घोषणा FTDI_XF_547_PID 0xFC0A	/* 547: Two line Display */
#घोषणा FTDI_XF_633_PID 0xFC0B	/* 633: 16x2 Character Display with Keys */
#घोषणा FTDI_XF_631_PID 0xFC0C	/* 631: 20x2 Character Display */
#घोषणा FTDI_XF_635_PID 0xFC0D	/* 635: 20x4 Character Display */
#घोषणा FTDI_XF_640_PID 0xFC0E	/* 640: Two line Display */
#घोषणा FTDI_XF_642_PID 0xFC0F	/* 642: Two line Display */

/*
 * Video Networks Limited / Homechoice in the UK use an ftdi-based device
 * क्रम their 1Mb broadband पूर्णांकernet service.  The following PID is exhibited
 * by the usb device supplied (the VID is the standard ftdi vid (FTDI_VID)
 */
#घोषणा FTDI_VNHCPCUSB_D_PID 0xfe38 /* Product Id */

/* AlphaMicro Components AMC-232USB01 device (FTDI_VID) */
#घोषणा FTDI_AMC232_PID 0xFF00 /* Product Id */

/*
 * IBS elektronik product ids (FTDI_VID)
 * Submitted by Thomas Schleusener
 */
#घोषणा FTDI_IBS_US485_PID	0xff38  /* IBS US485 (USB<-->RS422/485 पूर्णांकerface) */
#घोषणा FTDI_IBS_PICPRO_PID	0xff39  /* IBS PIC-Programmer */
#घोषणा FTDI_IBS_PCMCIA_PID	0xff3a  /* IBS Card पढ़ोer क्रम PCMCIA SRAM-cards */
#घोषणा FTDI_IBS_PK1_PID	0xff3b  /* IBS PK1 - Particel counter */
#घोषणा FTDI_IBS_RS232MON_PID	0xff3c  /* IBS RS232 - Monitor */
#घोषणा FTDI_IBS_APP70_PID	0xff3d  /* APP 70 (dust monitoring प्रणाली) */
#घोषणा FTDI_IBS_PEDO_PID	0xff3e  /* IBS PEDO-Modem (RF modem 868.35 MHz) */
#घोषणा FTDI_IBS_PROD_PID	0xff3f  /* future device */
/* www.canusb.com Lawicel CANUSB device (FTDI_VID) */
#घोषणा FTDI_CANUSB_PID 0xFFA8 /* Product Id */

/*
 * TavIR AVR product ids (FTDI_VID)
 */
#घोषणा FTDI_TAVIR_STK500_PID	0xFA33	/* STK500 AVR programmer */

/*
 * TIAO product ids (FTDI_VID)
 * http://www.tiaowiki.com/w/Main_Page
 */
#घोषणा FTDI_TIAO_UMPA_PID	0x8a98	/* TIAO/DIYGADGET USB Multi-Protocol Adapter */

/*
 * NovaTech product ids (FTDI_VID)
 */
#घोषणा FTDI_NT_ORIONLXM_PID		0x7c90	/* OrionLXm Substation Automation Platक्रमm */
#घोषणा FTDI_NT_ORIONLX_PLUS_PID	0x7c91	/* OrionLX+ Substation Automation Platक्रमm */
#घोषणा FTDI_NT_ORION_IO_PID		0x7c92	/* Orion I/O */
#घोषणा FTDI_NT_ORIONMX_PID		0x7c93	/* OrionMX */

/*
 * Synapse Wireless product ids (FTDI_VID)
 * http://www.synapse-wireless.com
 */
#घोषणा FTDI_SYNAPSE_SS200_PID 0x9090 /* SS200 - SNAP Stick 200 */

/*
 * CustomWare / ShipModul NMEA multiplexers product ids (FTDI_VID)
 */
#घोषणा FTDI_CUSTOMWARE_MINIPLEX_PID	0xfd48	/* MiniPlex first generation NMEA Multiplexer */
#घोषणा FTDI_CUSTOMWARE_MINIPLEX2_PID	0xfd49	/* MiniPlex-USB and MiniPlex-2 series */
#घोषणा FTDI_CUSTOMWARE_MINIPLEX2WI_PID	0xfd4a	/* MiniPlex-2Wi */
#घोषणा FTDI_CUSTOMWARE_MINIPLEX3_PID	0xfd4b	/* MiniPlex-3 series */


/********************************/
/** third-party VID/PID combos **/
/********************************/



/*
 * Aपंचांगel STK541
 */
#घोषणा ATMEL_VID		0x03eb /* Venकरोr ID */
#घोषणा STK541_PID		0x2109 /* Zigbee Controller */

/*
 * Texas Instruments
 */
#घोषणा TI_VID			0x0451
#घोषणा TI_CC3200_LAUNCHPAD_PID	0xC32A /* SimpleLink Wi-Fi CC3200 LaunchPad */

/*
 * Blackfin gnICE JTAG
 * http://करोcs.blackfin.uclinux.org/करोku.php?id=hw:jtag:gnice
 */
#घोषणा ADI_VID			0x0456
#घोषणा ADI_GNICE_PID		0xF000
#घोषणा ADI_GNICEPLUS_PID	0xF001

/*
 * Cypress WICED USB UART
 */
#घोषणा CYPRESS_VID			0x04B4
#घोषणा CYPRESS_WICED_BT_USB_PID	0x009B
#घोषणा CYPRESS_WICED_WL_USB_PID	0xF900

/*
 * Microchip Technology, Inc.
 *
 * MICROCHIP_VID (0x04D8) and MICROCHIP_USB_BOARD_PID (0x000A) are
 * used by single function CDC ACM class based firmware demo
 * applications.  The VID/PID has also been used in firmware
 * emulating FTDI serial chips by:
 * Hornby Elite - Digital Command Control Console
 * http://www.hornby.com/hornby-dcc/controllers/
 */
#घोषणा MICROCHIP_VID		0x04D8
#घोषणा MICROCHIP_USB_BOARD_PID	0x000A /* CDC RS-232 Emulation Demo */

/*
 * RATOC REX-USB60F
 */
#घोषणा RATOC_VENDOR_ID		0x0584
#घोषणा RATOC_PRODUCT_ID_USB60F	0xb020
#घोषणा RATOC_PRODUCT_ID_SCU18	0xb03a

/*
 * Infineon Technologies
 */
#घोषणा INFINEON_VID		        0x058b
#घोषणा INFINEON_TRIBOARD_TC1798_PID	0x0028 /* DAS JTAG TriBoard TC1798 V1.0 */
#घोषणा INFINEON_TRIBOARD_TC2X7_PID	0x0043 /* DAS JTAG TriBoard TC2X7 V1.0 */

/*
 * Acton Research Corp.
 */
#घोषणा ACTON_VID		0x0647	/* Venकरोr ID */
#घोषणा ACTON_SPECTRAPRO_PID	0x0100

/*
 * Contec products (http://www.contec.com)
 * Submitted by Daniel Sangorrin
 */
#घोषणा CONTEC_VID		0x06CE	/* Venकरोr ID */
#घोषणा CONTEC_COM1USBH_PID	0x8311	/* COM-1(USB)H */

/*
 * Mitsubishi Electric Corp. (http://www.meau.com)
 * Submitted by Konstantin Holoborodko
 */
#घोषणा MITSUBISHI_VID		0x06D3
#घोषणा MITSUBISHI_FXUSB_PID	0x0284 /* USB/RS422 converters: FX-USB-AW/-BD */

/*
 * Definitions क्रम B&B Electronics products.
 */
#घोषणा BANDB_VID		0x0856	/* B&B Electronics Venकरोr ID */
#घोषणा BANDB_USOTL4_PID	0xAC01	/* USOTL4 Isolated RS-485 Converter */
#घोषणा BANDB_USTL4_PID		0xAC02	/* USTL4 RS-485 Converter */
#घोषणा BANDB_USO9ML2_PID	0xAC03	/* USO9ML2 Isolated RS-232 Converter */
#घोषणा BANDB_USOPTL4_PID	0xAC11
#घोषणा BANDB_USPTL4_PID	0xAC12
#घोषणा BANDB_USO9ML2DR_2_PID	0xAC16
#घोषणा BANDB_USO9ML2DR_PID	0xAC17
#घोषणा BANDB_USOPTL4DR2_PID	0xAC18	/* USOPTL4R-2 2-port Isolated RS-232 Converter */
#घोषणा BANDB_USOPTL4DR_PID	0xAC19
#घोषणा BANDB_485USB9F_2W_PID	0xAC25
#घोषणा BANDB_485USB9F_4W_PID	0xAC26
#घोषणा BANDB_232USB9M_PID	0xAC27
#घोषणा BANDB_485USBTB_2W_PID	0xAC33
#घोषणा BANDB_485USBTB_4W_PID	0xAC34
#घोषणा BANDB_TTL5USB9M_PID	0xAC49
#घोषणा BANDB_TTL3USB9M_PID	0xAC50
#घोषणा BANDB_ZZ_PROG1_USB_PID	0xBA02

/*
 * Echelon USB Serial Interface
 */
#घोषणा ECHELON_VID		0x0920
#घोषणा ECHELON_U20_PID		0x7500

/*
 * Intrepid Control Systems (http://www.पूर्णांकrepidcs.com/) ValueCAN and NeoVI
 */
#घोषणा INTREPID_VID		0x093C
#घोषणा INTREPID_VALUECAN_PID	0x0601
#घोषणा INTREPID_NEOVI_PID	0x0701

/*
 * WICED USB UART
 */
#घोषणा WICED_VID		0x0A5C
#घोषणा WICED_USB20706V2_PID	0x6422

/*
 * Definitions क्रम ID TECH (www.idt-net.com) devices
 */
#घोषणा IDTECH_VID		0x0ACD	/* ID TECH Venकरोr ID */
#घोषणा IDTECH_IDT1221U_PID	0x0300	/* IDT1221U USB to RS-232 adapter */

/*
 * Definitions क्रम Omnidirectional Control Technology, Inc. devices
 */
#घोषणा OCT_VID			0x0B39	/* OCT venकरोr ID */
/* Note: OCT US101 is also rebadged as Dick Smith Electronics (NZ) XH6381 */
/* Also rebadged as Dick Smith Electronics (Aus) XH6451 */
/* Also rebadged as SIIG Inc. model US2308 hardware version 1 */
#घोषणा OCT_DK201_PID		0x0103	/* OCT DK201 USB करोcking station */
#घोषणा OCT_US101_PID		0x0421	/* OCT US101 USB to RS-232 */

/*
 * Definitions क्रम Icom Inc. devices
 */
#घोषणा ICOM_VID		0x0C26 /* Icom venकरोr ID */
/* Note: ID-1 is a communications tranceiver क्रम HAM-radio चालकs */
#घोषणा ICOM_ID_1_PID		0x0004 /* ID-1 USB to RS-232 */
/* Note: OPC is an Optional cable to connect an Icom Tranceiver */
#घोषणा ICOM_OPC_U_UC_PID	0x0018 /* OPC-478UC, OPC-1122U cloning cable */
/* Note: ID-RP* devices are Icom Repeater Devices क्रम HAM-radio */
#घोषणा ICOM_ID_RP2C1_PID	0x0009 /* ID-RP2C Asset 1 to RS-232 */
#घोषणा ICOM_ID_RP2C2_PID	0x000A /* ID-RP2C Asset 2 to RS-232 */
#घोषणा ICOM_ID_RP2D_PID	0x000B /* ID-RP2D configuration port*/
#घोषणा ICOM_ID_RP2VT_PID	0x000C /* ID-RP2V Transmit config port */
#घोषणा ICOM_ID_RP2VR_PID	0x000D /* ID-RP2V Receive config port */
#घोषणा ICOM_ID_RP4KVT_PID	0x0010 /* ID-RP4000V Transmit config port */
#घोषणा ICOM_ID_RP4KVR_PID	0x0011 /* ID-RP4000V Receive config port */
#घोषणा ICOM_ID_RP2KVT_PID	0x0012 /* ID-RP2000V Transmit config port */
#घोषणा ICOM_ID_RP2KVR_PID	0x0013 /* ID-RP2000V Receive config port */

/*
 * GN Otometrics (http://www.otometrics.com)
 * Submitted by Ville Sundberg.
 */
#घोषणा GN_OTOMETRICS_VID	0x0c33	/* Venकरोr ID */
#घोषणा AURICAL_USB_PID		0x0010	/* Aurical USB Audiometer */

/*
 * The following are the values क्रम the Sealevel SeaLINK+ adapters.
 * (Original list sent by Tuan Hoang.  Ian Abbott नामd the macros and
 * हटाओd some PIDs that करोn't seem to match any existing products.)
 */
#घोषणा SEALEVEL_VID		0x0c52	/* Sealevel Venकरोr ID */
#घोषणा SEALEVEL_2101_PID	0x2101	/* SeaLINK+232 (2101/2105) */
#घोषणा SEALEVEL_2102_PID	0x2102	/* SeaLINK+485 (2102) */
#घोषणा SEALEVEL_2103_PID	0x2103	/* SeaLINK+232I (2103) */
#घोषणा SEALEVEL_2104_PID	0x2104	/* SeaLINK+485I (2104) */
#घोषणा SEALEVEL_2106_PID	0x9020	/* SeaLINK+422 (2106) */
#घोषणा SEALEVEL_2201_1_PID	0x2211	/* SeaPORT+2/232 (2201) Port 1 */
#घोषणा SEALEVEL_2201_2_PID	0x2221	/* SeaPORT+2/232 (2201) Port 2 */
#घोषणा SEALEVEL_2202_1_PID	0x2212	/* SeaPORT+2/485 (2202) Port 1 */
#घोषणा SEALEVEL_2202_2_PID	0x2222	/* SeaPORT+2/485 (2202) Port 2 */
#घोषणा SEALEVEL_2203_1_PID	0x2213	/* SeaPORT+2 (2203) Port 1 */
#घोषणा SEALEVEL_2203_2_PID	0x2223	/* SeaPORT+2 (2203) Port 2 */
#घोषणा SEALEVEL_2401_1_PID	0x2411	/* SeaPORT+4/232 (2401) Port 1 */
#घोषणा SEALEVEL_2401_2_PID	0x2421	/* SeaPORT+4/232 (2401) Port 2 */
#घोषणा SEALEVEL_2401_3_PID	0x2431	/* SeaPORT+4/232 (2401) Port 3 */
#घोषणा SEALEVEL_2401_4_PID	0x2441	/* SeaPORT+4/232 (2401) Port 4 */
#घोषणा SEALEVEL_2402_1_PID	0x2412	/* SeaPORT+4/485 (2402) Port 1 */
#घोषणा SEALEVEL_2402_2_PID	0x2422	/* SeaPORT+4/485 (2402) Port 2 */
#घोषणा SEALEVEL_2402_3_PID	0x2432	/* SeaPORT+4/485 (2402) Port 3 */
#घोषणा SEALEVEL_2402_4_PID	0x2442	/* SeaPORT+4/485 (2402) Port 4 */
#घोषणा SEALEVEL_2403_1_PID	0x2413	/* SeaPORT+4 (2403) Port 1 */
#घोषणा SEALEVEL_2403_2_PID	0x2423	/* SeaPORT+4 (2403) Port 2 */
#घोषणा SEALEVEL_2403_3_PID	0x2433	/* SeaPORT+4 (2403) Port 3 */
#घोषणा SEALEVEL_2403_4_PID	0x2443	/* SeaPORT+4 (2403) Port 4 */
#घोषणा SEALEVEL_2801_1_PID	0X2811	/* SeaLINK+8/232 (2801) Port 1 */
#घोषणा SEALEVEL_2801_2_PID	0X2821	/* SeaLINK+8/232 (2801) Port 2 */
#घोषणा SEALEVEL_2801_3_PID	0X2831	/* SeaLINK+8/232 (2801) Port 3 */
#घोषणा SEALEVEL_2801_4_PID	0X2841	/* SeaLINK+8/232 (2801) Port 4 */
#घोषणा SEALEVEL_2801_5_PID	0X2851	/* SeaLINK+8/232 (2801) Port 5 */
#घोषणा SEALEVEL_2801_6_PID	0X2861	/* SeaLINK+8/232 (2801) Port 6 */
#घोषणा SEALEVEL_2801_7_PID	0X2871	/* SeaLINK+8/232 (2801) Port 7 */
#घोषणा SEALEVEL_2801_8_PID	0X2881	/* SeaLINK+8/232 (2801) Port 8 */
#घोषणा SEALEVEL_2802_1_PID	0X2812	/* SeaLINK+8/485 (2802) Port 1 */
#घोषणा SEALEVEL_2802_2_PID	0X2822	/* SeaLINK+8/485 (2802) Port 2 */
#घोषणा SEALEVEL_2802_3_PID	0X2832	/* SeaLINK+8/485 (2802) Port 3 */
#घोषणा SEALEVEL_2802_4_PID	0X2842	/* SeaLINK+8/485 (2802) Port 4 */
#घोषणा SEALEVEL_2802_5_PID	0X2852	/* SeaLINK+8/485 (2802) Port 5 */
#घोषणा SEALEVEL_2802_6_PID	0X2862	/* SeaLINK+8/485 (2802) Port 6 */
#घोषणा SEALEVEL_2802_7_PID	0X2872	/* SeaLINK+8/485 (2802) Port 7 */
#घोषणा SEALEVEL_2802_8_PID	0X2882	/* SeaLINK+8/485 (2802) Port 8 */
#घोषणा SEALEVEL_2803_1_PID	0X2813	/* SeaLINK+8 (2803) Port 1 */
#घोषणा SEALEVEL_2803_2_PID	0X2823	/* SeaLINK+8 (2803) Port 2 */
#घोषणा SEALEVEL_2803_3_PID	0X2833	/* SeaLINK+8 (2803) Port 3 */
#घोषणा SEALEVEL_2803_4_PID	0X2843	/* SeaLINK+8 (2803) Port 4 */
#घोषणा SEALEVEL_2803_5_PID	0X2853	/* SeaLINK+8 (2803) Port 5 */
#घोषणा SEALEVEL_2803_6_PID	0X2863	/* SeaLINK+8 (2803) Port 6 */
#घोषणा SEALEVEL_2803_7_PID	0X2873	/* SeaLINK+8 (2803) Port 7 */
#घोषणा SEALEVEL_2803_8_PID	0X2883	/* SeaLINK+8 (2803) Port 8 */
#घोषणा SEALEVEL_2803R_1_PID	0Xa02a	/* SeaLINK+8 (2803-ROHS) Port 1+2 */
#घोषणा SEALEVEL_2803R_2_PID	0Xa02b	/* SeaLINK+8 (2803-ROHS) Port 3+4 */
#घोषणा SEALEVEL_2803R_3_PID	0Xa02c	/* SeaLINK+8 (2803-ROHS) Port 5+6 */
#घोषणा SEALEVEL_2803R_4_PID	0Xa02d	/* SeaLINK+8 (2803-ROHS) Port 7+8 */

/*
 * JETI SPECTROMETER SPECBOS 1201
 * http://www.jeti.com/cms/index.php/instruments/other-instruments/specbos-2101
 */
#घोषणा JETI_VID		0x0c6c
#घोषणा JETI_SPC1201_PID	0x04b2

/*
 * FTDI USB UART chips used in स्थिरruction projects from the
 * Elektor Electronics magazine (http://www.elektor.com/)
 */
#घोषणा ELEKTOR_VID		0x0C7D
#घोषणा ELEKTOR_FT323R_PID	0x0005	/* RFID-Reader, issue 09-2006 */

/*
 * Posअगरlex inc retail equipment (http://www.posअगरlex.com.tw)
 */
#घोषणा POSIFLEX_VID		0x0d3a  /* Venकरोr ID */
#घोषणा POSIFLEX_PP7000_PID	0x0300  /* PP-7000II thermal prपूर्णांकer */

/*
 * The following are the values क्रम two KOBIL chipcard terminals.
 */
#घोषणा KOBIL_VID		0x0d46	/* KOBIL Venकरोr ID */
#घोषणा KOBIL_CONV_B1_PID	0x2020	/* KOBIL Konverter क्रम B1 */
#घोषणा KOBIL_CONV_KAAN_PID	0x2021	/* KOBIL_Konverter क्रम KAAN */

#घोषणा FTDI_NF_RIC_VID	0x0DCD	/* Venकरोr Id */
#घोषणा FTDI_NF_RIC_PID	0x0001	/* Product Id */

/*
 * Falcom Wireless Communications GmbH
 */
#घोषणा FALCOM_VID		0x0F94	/* Venकरोr Id */
#घोषणा FALCOM_TWIST_PID	0x0001	/* Falcom Twist USB GPRS modem */
#घोषणा FALCOM_SAMBA_PID	0x0005	/* Falcom Samba USB GPRS modem */

/* Larsen and Brusgaard AltiTrack/USBtrack */
#घोषणा LARSENBRUSGAARD_VID		0x0FD8
#घोषणा LB_ALTITRACK_PID		0x0001

/*
 * TTi (Thurlby Thandar Instruments)
 */
#घोषणा TTI_VID			0x103E	/* Venकरोr Id */
#घोषणा TTI_QL355P_PID		0x03E8	/* TTi QL355P घातer supply */

/*
 * Newport Cooperation (www.newport.com)
 */
#घोषणा NEWPORT_VID			0x104D
#घोषणा NEWPORT_AGILIS_PID		0x3000
#घोषणा NEWPORT_CONEX_CC_PID		0x3002
#घोषणा NEWPORT_CONEX_AGP_PID		0x3006

/* Interbiometrics USB I/O Board */
/* Developed क्रम Interbiometrics by Ruकरोlf Gugler */
#घोषणा INTERBIOMETRICS_VID              0x1209
#घोषणा INTERBIOMETRICS_IOBOARD_PID      0x1002
#घोषणा INTERBIOMETRICS_MINI_IOBOARD_PID 0x1006

/*
 * Testo products (http://www.testo.com/)
 * Submitted by Colin Leroy
 */
#घोषणा TESTO_VID			0x128D
#घोषणा TESTO_1_PID			0x0001
#घोषणा TESTO_3_PID			0x0003

/*
 * Mobility Electronics products.
 */
#घोषणा MOBILITY_VID			0x1342
#घोषणा MOBILITY_USB_SERIAL_PID		0x0202	/* EasiDock USB 200 serial */

/*
 * FIC / OpenMoko, Inc. http://wiki.खोलोmoko.org/wiki/Neo1973_Debug_Board_v3
 * Submitted by Harald Welte <laक्रमge@खोलोmoko.org>
 */
#घोषणा	FIC_VID			0x1457
#घोषणा	FIC_NEO1973_DEBUG_PID	0x5118

/*
 * Actel / Microsemi
 */
#घोषणा ACTEL_VID				0x1514
#घोषणा MICROSEMI_ARROW_SF2PLUS_BOARD_PID	0x2008

/* Olimex */
#घोषणा OLIMEX_VID			0x15BA
#घोषणा OLIMEX_ARM_USB_OCD_PID		0x0003
#घोषणा OLIMEX_ARM_USB_TINY_PID	0x0004
#घोषणा OLIMEX_ARM_USB_TINY_H_PID	0x002a
#घोषणा OLIMEX_ARM_USB_OCD_H_PID	0x002b

/*
 * Telldus Technologies
 */
#घोषणा TELLDUS_VID			0x1781	/* Venकरोr ID */
#घोषणा TELLDUS_TELLSTICK_PID		0x0C30	/* RF control करोngle 433 MHz using FT232RL */

/*
 * NOVITUS prपूर्णांकers
 */
#घोषणा NOVITUS_VID			0x1a28
#घोषणा NOVITUS_BONO_E_PID		0x6010

/*
 * ICPDAS I-756*U devices
 */
#घोषणा ICPDAS_VID			0x1b5c
#घोषणा ICPDAS_I7560U_PID		0x0103
#घोषणा ICPDAS_I7561U_PID		0x0104
#घोषणा ICPDAS_I7563U_PID		0x0105

/*
 * Airbus Defence and Space
 */
#घोषणा AIRBUS_DS_VID			0x1e8e  /* Venकरोr ID */
#घोषणा AIRBUS_DS_P8GR			0x6001  /* Tetra P8GR */

/*
 * RT Systems programming cables क्रम various ham radios
 */
/* This device uses the VID of FTDI */
#घोषणा RTSYSTEMS_USB_VX8_PID   0x9e50  /* USB-VX8 USB to 7 pin modular plug क्रम Yaesu VX-8 radio */

#घोषणा RTSYSTEMS_VID		0x2100	/* Venकरोr ID */
#घोषणा RTSYSTEMS_USB_S03_PID	0x9001	/* RTS-03 USB to Serial Adapter */
#घोषणा RTSYSTEMS_USB_59_PID	0x9e50	/* USB-59 USB to 8 pin plug */
#घोषणा RTSYSTEMS_USB_57A_PID	0x9e51	/* USB-57A USB to 4pin 3.5mm plug */
#घोषणा RTSYSTEMS_USB_57B_PID	0x9e52	/* USB-57B USB to extended 4pin 3.5mm plug */
#घोषणा RTSYSTEMS_USB_29A_PID	0x9e53	/* USB-29A USB to 3.5mm stereo plug */
#घोषणा RTSYSTEMS_USB_29B_PID	0x9e54	/* USB-29B USB to 6 pin mini din */
#घोषणा RTSYSTEMS_USB_29F_PID	0x9e55	/* USB-29F USB to 6 pin modular plug */
#घोषणा RTSYSTEMS_USB_62B_PID	0x9e56	/* USB-62B USB to 8 pin mini din plug*/
#घोषणा RTSYSTEMS_USB_S01_PID	0x9e57	/* USB-RTS01 USB to 3.5 mm stereo plug*/
#घोषणा RTSYSTEMS_USB_63_PID	0x9e58	/* USB-63 USB to 9 pin female*/
#घोषणा RTSYSTEMS_USB_29C_PID	0x9e59	/* USB-29C USB to 4 pin modular plug*/
#घोषणा RTSYSTEMS_USB_81B_PID	0x9e5A	/* USB-81 USB to 8 pin mini din plug*/
#घोषणा RTSYSTEMS_USB_82B_PID	0x9e5B	/* USB-82 USB to 2.5 mm stereo plug*/
#घोषणा RTSYSTEMS_USB_K5D_PID	0x9e5C	/* USB-K5D USB to 8 pin modular plug*/
#घोषणा RTSYSTEMS_USB_K4Y_PID	0x9e5D	/* USB-K4Y USB to 2.5/3.5 mm plugs*/
#घोषणा RTSYSTEMS_USB_K5G_PID	0x9e5E	/* USB-K5G USB to 8 pin modular plug*/
#घोषणा RTSYSTEMS_USB_S05_PID	0x9e5F	/* USB-RTS05 USB to 2.5 mm stereo plug*/
#घोषणा RTSYSTEMS_USB_60_PID	0x9e60	/* USB-60 USB to 6 pin din*/
#घोषणा RTSYSTEMS_USB_61_PID	0x9e61	/* USB-61 USB to 6 pin mini din*/
#घोषणा RTSYSTEMS_USB_62_PID	0x9e62	/* USB-62 USB to 8 pin mini din*/
#घोषणा RTSYSTEMS_USB_63B_PID	0x9e63	/* USB-63 USB to 9 pin female*/
#घोषणा RTSYSTEMS_USB_64_PID	0x9e64	/* USB-64 USB to 9 pin male*/
#घोषणा RTSYSTEMS_USB_65_PID	0x9e65	/* USB-65 USB to 9 pin female null modem*/
#घोषणा RTSYSTEMS_USB_92_PID	0x9e66	/* USB-92 USB to 12 pin plug*/
#घोषणा RTSYSTEMS_USB_92D_PID	0x9e67	/* USB-92D USB to 12 pin plug data*/
#घोषणा RTSYSTEMS_USB_W5R_PID	0x9e68	/* USB-W5R USB to 8 pin modular plug*/
#घोषणा RTSYSTEMS_USB_A5R_PID	0x9e69	/* USB-A5R USB to 8 pin modular plug*/
#घोषणा RTSYSTEMS_USB_PW1_PID	0x9e6A	/* USB-PW1 USB to 8 pin modular plug*/

/*
 * Physik Instrumente
 * http://www.physikinstrumente.com/en/products/
 */
/* These two devices use the VID of FTDI */
#घोषणा PI_C865_PID	0xe0a0  /* PI C-865 Piezomotor Controller */
#घोषणा PI_C857_PID	0xe0a1  /* PI Encoder Trigger Box */

#घोषणा PI_VID              0x1a72  /* Venकरोr ID */
#घोषणा PI_C866_PID	0x1000  /* PI C-866 Piezomotor Controller */
#घोषणा PI_C663_PID	0x1001  /* PI C-663 Mercury-Step */
#घोषणा PI_C725_PID	0x1002  /* PI C-725 Piezomotor Controller */
#घोषणा PI_E517_PID	0x1005  /* PI E-517 Digital Piezo Controller Operation Module */
#घोषणा PI_C863_PID	0x1007  /* PI C-863 */
#घोषणा PI_E861_PID	0x1008  /* PI E-861 Piezomotor Controller */
#घोषणा PI_C867_PID	0x1009  /* PI C-867 Piezomotor Controller */
#घोषणा PI_E609_PID	0x100D  /* PI E-609 Digital Piezo Controller */
#घोषणा PI_E709_PID	0x100E  /* PI E-709 Digital Piezo Controller */
#घोषणा PI_100F_PID	0x100F  /* PI Digital Piezo Controller */
#घोषणा PI_1011_PID	0x1011  /* PI Digital Piezo Controller */
#घोषणा PI_1012_PID	0x1012  /* PI Motion Controller */
#घोषणा PI_1013_PID	0x1013  /* PI Motion Controller */
#घोषणा PI_1014_PID	0x1014  /* PI Device */
#घोषणा PI_1015_PID	0x1015  /* PI Device */
#घोषणा PI_1016_PID	0x1016  /* PI Digital Servo Module */

/*
 * Konकरो Kagaku Co.Ltd.
 * http://www.konकरो-robot.com/EN
 */
#घोषणा KONDO_VID 		0x165c
#घोषणा KONDO_USB_SERIAL_PID	0x0002

/*
 * Bayer Ascensia Contour blood glucose meter USB-converter cable.
 * http://winglucofacts.com/cables/
 */
#घोषणा BAYER_VID                      0x1A79
#घोषणा BAYER_CONTOUR_CABLE_PID        0x6001

/*
 * Matrix Orbital Intelligent USB displays.
 * http://www.matrixorbital.com
 */
#घोषणा MTXORB_VID			0x1B3D
#घोषणा MTXORB_FTDI_RANGE_0100_PID	0x0100
#घोषणा MTXORB_FTDI_RANGE_0101_PID	0x0101
#घोषणा MTXORB_FTDI_RANGE_0102_PID	0x0102
#घोषणा MTXORB_FTDI_RANGE_0103_PID	0x0103
#घोषणा MTXORB_FTDI_RANGE_0104_PID	0x0104
#घोषणा MTXORB_FTDI_RANGE_0105_PID	0x0105
#घोषणा MTXORB_FTDI_RANGE_0106_PID	0x0106
#घोषणा MTXORB_FTDI_RANGE_0107_PID	0x0107
#घोषणा MTXORB_FTDI_RANGE_0108_PID	0x0108
#घोषणा MTXORB_FTDI_RANGE_0109_PID	0x0109
#घोषणा MTXORB_FTDI_RANGE_010A_PID	0x010A
#घोषणा MTXORB_FTDI_RANGE_010B_PID	0x010B
#घोषणा MTXORB_FTDI_RANGE_010C_PID	0x010C
#घोषणा MTXORB_FTDI_RANGE_010D_PID	0x010D
#घोषणा MTXORB_FTDI_RANGE_010E_PID	0x010E
#घोषणा MTXORB_FTDI_RANGE_010F_PID	0x010F
#घोषणा MTXORB_FTDI_RANGE_0110_PID	0x0110
#घोषणा MTXORB_FTDI_RANGE_0111_PID	0x0111
#घोषणा MTXORB_FTDI_RANGE_0112_PID	0x0112
#घोषणा MTXORB_FTDI_RANGE_0113_PID	0x0113
#घोषणा MTXORB_FTDI_RANGE_0114_PID	0x0114
#घोषणा MTXORB_FTDI_RANGE_0115_PID	0x0115
#घोषणा MTXORB_FTDI_RANGE_0116_PID	0x0116
#घोषणा MTXORB_FTDI_RANGE_0117_PID	0x0117
#घोषणा MTXORB_FTDI_RANGE_0118_PID	0x0118
#घोषणा MTXORB_FTDI_RANGE_0119_PID	0x0119
#घोषणा MTXORB_FTDI_RANGE_011A_PID	0x011A
#घोषणा MTXORB_FTDI_RANGE_011B_PID	0x011B
#घोषणा MTXORB_FTDI_RANGE_011C_PID	0x011C
#घोषणा MTXORB_FTDI_RANGE_011D_PID	0x011D
#घोषणा MTXORB_FTDI_RANGE_011E_PID	0x011E
#घोषणा MTXORB_FTDI_RANGE_011F_PID	0x011F
#घोषणा MTXORB_FTDI_RANGE_0120_PID	0x0120
#घोषणा MTXORB_FTDI_RANGE_0121_PID	0x0121
#घोषणा MTXORB_FTDI_RANGE_0122_PID	0x0122
#घोषणा MTXORB_FTDI_RANGE_0123_PID	0x0123
#घोषणा MTXORB_FTDI_RANGE_0124_PID	0x0124
#घोषणा MTXORB_FTDI_RANGE_0125_PID	0x0125
#घोषणा MTXORB_FTDI_RANGE_0126_PID	0x0126
#घोषणा MTXORB_FTDI_RANGE_0127_PID	0x0127
#घोषणा MTXORB_FTDI_RANGE_0128_PID	0x0128
#घोषणा MTXORB_FTDI_RANGE_0129_PID	0x0129
#घोषणा MTXORB_FTDI_RANGE_012A_PID	0x012A
#घोषणा MTXORB_FTDI_RANGE_012B_PID	0x012B
#घोषणा MTXORB_FTDI_RANGE_012C_PID	0x012C
#घोषणा MTXORB_FTDI_RANGE_012D_PID	0x012D
#घोषणा MTXORB_FTDI_RANGE_012E_PID	0x012E
#घोषणा MTXORB_FTDI_RANGE_012F_PID	0x012F
#घोषणा MTXORB_FTDI_RANGE_0130_PID	0x0130
#घोषणा MTXORB_FTDI_RANGE_0131_PID	0x0131
#घोषणा MTXORB_FTDI_RANGE_0132_PID	0x0132
#घोषणा MTXORB_FTDI_RANGE_0133_PID	0x0133
#घोषणा MTXORB_FTDI_RANGE_0134_PID	0x0134
#घोषणा MTXORB_FTDI_RANGE_0135_PID	0x0135
#घोषणा MTXORB_FTDI_RANGE_0136_PID	0x0136
#घोषणा MTXORB_FTDI_RANGE_0137_PID	0x0137
#घोषणा MTXORB_FTDI_RANGE_0138_PID	0x0138
#घोषणा MTXORB_FTDI_RANGE_0139_PID	0x0139
#घोषणा MTXORB_FTDI_RANGE_013A_PID	0x013A
#घोषणा MTXORB_FTDI_RANGE_013B_PID	0x013B
#घोषणा MTXORB_FTDI_RANGE_013C_PID	0x013C
#घोषणा MTXORB_FTDI_RANGE_013D_PID	0x013D
#घोषणा MTXORB_FTDI_RANGE_013E_PID	0x013E
#घोषणा MTXORB_FTDI_RANGE_013F_PID	0x013F
#घोषणा MTXORB_FTDI_RANGE_0140_PID	0x0140
#घोषणा MTXORB_FTDI_RANGE_0141_PID	0x0141
#घोषणा MTXORB_FTDI_RANGE_0142_PID	0x0142
#घोषणा MTXORB_FTDI_RANGE_0143_PID	0x0143
#घोषणा MTXORB_FTDI_RANGE_0144_PID	0x0144
#घोषणा MTXORB_FTDI_RANGE_0145_PID	0x0145
#घोषणा MTXORB_FTDI_RANGE_0146_PID	0x0146
#घोषणा MTXORB_FTDI_RANGE_0147_PID	0x0147
#घोषणा MTXORB_FTDI_RANGE_0148_PID	0x0148
#घोषणा MTXORB_FTDI_RANGE_0149_PID	0x0149
#घोषणा MTXORB_FTDI_RANGE_014A_PID	0x014A
#घोषणा MTXORB_FTDI_RANGE_014B_PID	0x014B
#घोषणा MTXORB_FTDI_RANGE_014C_PID	0x014C
#घोषणा MTXORB_FTDI_RANGE_014D_PID	0x014D
#घोषणा MTXORB_FTDI_RANGE_014E_PID	0x014E
#घोषणा MTXORB_FTDI_RANGE_014F_PID	0x014F
#घोषणा MTXORB_FTDI_RANGE_0150_PID	0x0150
#घोषणा MTXORB_FTDI_RANGE_0151_PID	0x0151
#घोषणा MTXORB_FTDI_RANGE_0152_PID	0x0152
#घोषणा MTXORB_FTDI_RANGE_0153_PID	0x0153
#घोषणा MTXORB_FTDI_RANGE_0154_PID	0x0154
#घोषणा MTXORB_FTDI_RANGE_0155_PID	0x0155
#घोषणा MTXORB_FTDI_RANGE_0156_PID	0x0156
#घोषणा MTXORB_FTDI_RANGE_0157_PID	0x0157
#घोषणा MTXORB_FTDI_RANGE_0158_PID	0x0158
#घोषणा MTXORB_FTDI_RANGE_0159_PID	0x0159
#घोषणा MTXORB_FTDI_RANGE_015A_PID	0x015A
#घोषणा MTXORB_FTDI_RANGE_015B_PID	0x015B
#घोषणा MTXORB_FTDI_RANGE_015C_PID	0x015C
#घोषणा MTXORB_FTDI_RANGE_015D_PID	0x015D
#घोषणा MTXORB_FTDI_RANGE_015E_PID	0x015E
#घोषणा MTXORB_FTDI_RANGE_015F_PID	0x015F
#घोषणा MTXORB_FTDI_RANGE_0160_PID	0x0160
#घोषणा MTXORB_FTDI_RANGE_0161_PID	0x0161
#घोषणा MTXORB_FTDI_RANGE_0162_PID	0x0162
#घोषणा MTXORB_FTDI_RANGE_0163_PID	0x0163
#घोषणा MTXORB_FTDI_RANGE_0164_PID	0x0164
#घोषणा MTXORB_FTDI_RANGE_0165_PID	0x0165
#घोषणा MTXORB_FTDI_RANGE_0166_PID	0x0166
#घोषणा MTXORB_FTDI_RANGE_0167_PID	0x0167
#घोषणा MTXORB_FTDI_RANGE_0168_PID	0x0168
#घोषणा MTXORB_FTDI_RANGE_0169_PID	0x0169
#घोषणा MTXORB_FTDI_RANGE_016A_PID	0x016A
#घोषणा MTXORB_FTDI_RANGE_016B_PID	0x016B
#घोषणा MTXORB_FTDI_RANGE_016C_PID	0x016C
#घोषणा MTXORB_FTDI_RANGE_016D_PID	0x016D
#घोषणा MTXORB_FTDI_RANGE_016E_PID	0x016E
#घोषणा MTXORB_FTDI_RANGE_016F_PID	0x016F
#घोषणा MTXORB_FTDI_RANGE_0170_PID	0x0170
#घोषणा MTXORB_FTDI_RANGE_0171_PID	0x0171
#घोषणा MTXORB_FTDI_RANGE_0172_PID	0x0172
#घोषणा MTXORB_FTDI_RANGE_0173_PID	0x0173
#घोषणा MTXORB_FTDI_RANGE_0174_PID	0x0174
#घोषणा MTXORB_FTDI_RANGE_0175_PID	0x0175
#घोषणा MTXORB_FTDI_RANGE_0176_PID	0x0176
#घोषणा MTXORB_FTDI_RANGE_0177_PID	0x0177
#घोषणा MTXORB_FTDI_RANGE_0178_PID	0x0178
#घोषणा MTXORB_FTDI_RANGE_0179_PID	0x0179
#घोषणा MTXORB_FTDI_RANGE_017A_PID	0x017A
#घोषणा MTXORB_FTDI_RANGE_017B_PID	0x017B
#घोषणा MTXORB_FTDI_RANGE_017C_PID	0x017C
#घोषणा MTXORB_FTDI_RANGE_017D_PID	0x017D
#घोषणा MTXORB_FTDI_RANGE_017E_PID	0x017E
#घोषणा MTXORB_FTDI_RANGE_017F_PID	0x017F
#घोषणा MTXORB_FTDI_RANGE_0180_PID	0x0180
#घोषणा MTXORB_FTDI_RANGE_0181_PID	0x0181
#घोषणा MTXORB_FTDI_RANGE_0182_PID	0x0182
#घोषणा MTXORB_FTDI_RANGE_0183_PID	0x0183
#घोषणा MTXORB_FTDI_RANGE_0184_PID	0x0184
#घोषणा MTXORB_FTDI_RANGE_0185_PID	0x0185
#घोषणा MTXORB_FTDI_RANGE_0186_PID	0x0186
#घोषणा MTXORB_FTDI_RANGE_0187_PID	0x0187
#घोषणा MTXORB_FTDI_RANGE_0188_PID	0x0188
#घोषणा MTXORB_FTDI_RANGE_0189_PID	0x0189
#घोषणा MTXORB_FTDI_RANGE_018A_PID	0x018A
#घोषणा MTXORB_FTDI_RANGE_018B_PID	0x018B
#घोषणा MTXORB_FTDI_RANGE_018C_PID	0x018C
#घोषणा MTXORB_FTDI_RANGE_018D_PID	0x018D
#घोषणा MTXORB_FTDI_RANGE_018E_PID	0x018E
#घोषणा MTXORB_FTDI_RANGE_018F_PID	0x018F
#घोषणा MTXORB_FTDI_RANGE_0190_PID	0x0190
#घोषणा MTXORB_FTDI_RANGE_0191_PID	0x0191
#घोषणा MTXORB_FTDI_RANGE_0192_PID	0x0192
#घोषणा MTXORB_FTDI_RANGE_0193_PID	0x0193
#घोषणा MTXORB_FTDI_RANGE_0194_PID	0x0194
#घोषणा MTXORB_FTDI_RANGE_0195_PID	0x0195
#घोषणा MTXORB_FTDI_RANGE_0196_PID	0x0196
#घोषणा MTXORB_FTDI_RANGE_0197_PID	0x0197
#घोषणा MTXORB_FTDI_RANGE_0198_PID	0x0198
#घोषणा MTXORB_FTDI_RANGE_0199_PID	0x0199
#घोषणा MTXORB_FTDI_RANGE_019A_PID	0x019A
#घोषणा MTXORB_FTDI_RANGE_019B_PID	0x019B
#घोषणा MTXORB_FTDI_RANGE_019C_PID	0x019C
#घोषणा MTXORB_FTDI_RANGE_019D_PID	0x019D
#घोषणा MTXORB_FTDI_RANGE_019E_PID	0x019E
#घोषणा MTXORB_FTDI_RANGE_019F_PID	0x019F
#घोषणा MTXORB_FTDI_RANGE_01A0_PID	0x01A0
#घोषणा MTXORB_FTDI_RANGE_01A1_PID	0x01A1
#घोषणा MTXORB_FTDI_RANGE_01A2_PID	0x01A2
#घोषणा MTXORB_FTDI_RANGE_01A3_PID	0x01A3
#घोषणा MTXORB_FTDI_RANGE_01A4_PID	0x01A4
#घोषणा MTXORB_FTDI_RANGE_01A5_PID	0x01A5
#घोषणा MTXORB_FTDI_RANGE_01A6_PID	0x01A6
#घोषणा MTXORB_FTDI_RANGE_01A7_PID	0x01A7
#घोषणा MTXORB_FTDI_RANGE_01A8_PID	0x01A8
#घोषणा MTXORB_FTDI_RANGE_01A9_PID	0x01A9
#घोषणा MTXORB_FTDI_RANGE_01AA_PID	0x01AA
#घोषणा MTXORB_FTDI_RANGE_01AB_PID	0x01AB
#घोषणा MTXORB_FTDI_RANGE_01AC_PID	0x01AC
#घोषणा MTXORB_FTDI_RANGE_01AD_PID	0x01AD
#घोषणा MTXORB_FTDI_RANGE_01AE_PID	0x01AE
#घोषणा MTXORB_FTDI_RANGE_01AF_PID	0x01AF
#घोषणा MTXORB_FTDI_RANGE_01B0_PID	0x01B0
#घोषणा MTXORB_FTDI_RANGE_01B1_PID	0x01B1
#घोषणा MTXORB_FTDI_RANGE_01B2_PID	0x01B2
#घोषणा MTXORB_FTDI_RANGE_01B3_PID	0x01B3
#घोषणा MTXORB_FTDI_RANGE_01B4_PID	0x01B4
#घोषणा MTXORB_FTDI_RANGE_01B5_PID	0x01B5
#घोषणा MTXORB_FTDI_RANGE_01B6_PID	0x01B6
#घोषणा MTXORB_FTDI_RANGE_01B7_PID	0x01B7
#घोषणा MTXORB_FTDI_RANGE_01B8_PID	0x01B8
#घोषणा MTXORB_FTDI_RANGE_01B9_PID	0x01B9
#घोषणा MTXORB_FTDI_RANGE_01BA_PID	0x01BA
#घोषणा MTXORB_FTDI_RANGE_01BB_PID	0x01BB
#घोषणा MTXORB_FTDI_RANGE_01BC_PID	0x01BC
#घोषणा MTXORB_FTDI_RANGE_01BD_PID	0x01BD
#घोषणा MTXORB_FTDI_RANGE_01BE_PID	0x01BE
#घोषणा MTXORB_FTDI_RANGE_01BF_PID	0x01BF
#घोषणा MTXORB_FTDI_RANGE_01C0_PID	0x01C0
#घोषणा MTXORB_FTDI_RANGE_01C1_PID	0x01C1
#घोषणा MTXORB_FTDI_RANGE_01C2_PID	0x01C2
#घोषणा MTXORB_FTDI_RANGE_01C3_PID	0x01C3
#घोषणा MTXORB_FTDI_RANGE_01C4_PID	0x01C4
#घोषणा MTXORB_FTDI_RANGE_01C5_PID	0x01C5
#घोषणा MTXORB_FTDI_RANGE_01C6_PID	0x01C6
#घोषणा MTXORB_FTDI_RANGE_01C7_PID	0x01C7
#घोषणा MTXORB_FTDI_RANGE_01C8_PID	0x01C8
#घोषणा MTXORB_FTDI_RANGE_01C9_PID	0x01C9
#घोषणा MTXORB_FTDI_RANGE_01CA_PID	0x01CA
#घोषणा MTXORB_FTDI_RANGE_01CB_PID	0x01CB
#घोषणा MTXORB_FTDI_RANGE_01CC_PID	0x01CC
#घोषणा MTXORB_FTDI_RANGE_01CD_PID	0x01CD
#घोषणा MTXORB_FTDI_RANGE_01CE_PID	0x01CE
#घोषणा MTXORB_FTDI_RANGE_01CF_PID	0x01CF
#घोषणा MTXORB_FTDI_RANGE_01D0_PID	0x01D0
#घोषणा MTXORB_FTDI_RANGE_01D1_PID	0x01D1
#घोषणा MTXORB_FTDI_RANGE_01D2_PID	0x01D2
#घोषणा MTXORB_FTDI_RANGE_01D3_PID	0x01D3
#घोषणा MTXORB_FTDI_RANGE_01D4_PID	0x01D4
#घोषणा MTXORB_FTDI_RANGE_01D5_PID	0x01D5
#घोषणा MTXORB_FTDI_RANGE_01D6_PID	0x01D6
#घोषणा MTXORB_FTDI_RANGE_01D7_PID	0x01D7
#घोषणा MTXORB_FTDI_RANGE_01D8_PID	0x01D8
#घोषणा MTXORB_FTDI_RANGE_01D9_PID	0x01D9
#घोषणा MTXORB_FTDI_RANGE_01DA_PID	0x01DA
#घोषणा MTXORB_FTDI_RANGE_01DB_PID	0x01DB
#घोषणा MTXORB_FTDI_RANGE_01DC_PID	0x01DC
#घोषणा MTXORB_FTDI_RANGE_01DD_PID	0x01DD
#घोषणा MTXORB_FTDI_RANGE_01DE_PID	0x01DE
#घोषणा MTXORB_FTDI_RANGE_01DF_PID	0x01DF
#घोषणा MTXORB_FTDI_RANGE_01E0_PID	0x01E0
#घोषणा MTXORB_FTDI_RANGE_01E1_PID	0x01E1
#घोषणा MTXORB_FTDI_RANGE_01E2_PID	0x01E2
#घोषणा MTXORB_FTDI_RANGE_01E3_PID	0x01E3
#घोषणा MTXORB_FTDI_RANGE_01E4_PID	0x01E4
#घोषणा MTXORB_FTDI_RANGE_01E5_PID	0x01E5
#घोषणा MTXORB_FTDI_RANGE_01E6_PID	0x01E6
#घोषणा MTXORB_FTDI_RANGE_01E7_PID	0x01E7
#घोषणा MTXORB_FTDI_RANGE_01E8_PID	0x01E8
#घोषणा MTXORB_FTDI_RANGE_01E9_PID	0x01E9
#घोषणा MTXORB_FTDI_RANGE_01EA_PID	0x01EA
#घोषणा MTXORB_FTDI_RANGE_01EB_PID	0x01EB
#घोषणा MTXORB_FTDI_RANGE_01EC_PID	0x01EC
#घोषणा MTXORB_FTDI_RANGE_01ED_PID	0x01ED
#घोषणा MTXORB_FTDI_RANGE_01EE_PID	0x01EE
#घोषणा MTXORB_FTDI_RANGE_01EF_PID	0x01EF
#घोषणा MTXORB_FTDI_RANGE_01F0_PID	0x01F0
#घोषणा MTXORB_FTDI_RANGE_01F1_PID	0x01F1
#घोषणा MTXORB_FTDI_RANGE_01F2_PID	0x01F2
#घोषणा MTXORB_FTDI_RANGE_01F3_PID	0x01F3
#घोषणा MTXORB_FTDI_RANGE_01F4_PID	0x01F4
#घोषणा MTXORB_FTDI_RANGE_01F5_PID	0x01F5
#घोषणा MTXORB_FTDI_RANGE_01F6_PID	0x01F6
#घोषणा MTXORB_FTDI_RANGE_01F7_PID	0x01F7
#घोषणा MTXORB_FTDI_RANGE_01F8_PID	0x01F8
#घोषणा MTXORB_FTDI_RANGE_01F9_PID	0x01F9
#घोषणा MTXORB_FTDI_RANGE_01FA_PID	0x01FA
#घोषणा MTXORB_FTDI_RANGE_01FB_PID	0x01FB
#घोषणा MTXORB_FTDI_RANGE_01FC_PID	0x01FC
#घोषणा MTXORB_FTDI_RANGE_01FD_PID	0x01FD
#घोषणा MTXORB_FTDI_RANGE_01FE_PID	0x01FE
#घोषणा MTXORB_FTDI_RANGE_01FF_PID	0x01FF
#घोषणा MTXORB_FTDI_RANGE_4701_PID	0x4701
#घोषणा MTXORB_FTDI_RANGE_9300_PID	0x9300
#घोषणा MTXORB_FTDI_RANGE_9301_PID	0x9301
#घोषणा MTXORB_FTDI_RANGE_9302_PID	0x9302
#घोषणा MTXORB_FTDI_RANGE_9303_PID	0x9303
#घोषणा MTXORB_FTDI_RANGE_9304_PID	0x9304
#घोषणा MTXORB_FTDI_RANGE_9305_PID	0x9305
#घोषणा MTXORB_FTDI_RANGE_9306_PID	0x9306
#घोषणा MTXORB_FTDI_RANGE_9307_PID	0x9307
#घोषणा MTXORB_FTDI_RANGE_9308_PID	0x9308
#घोषणा MTXORB_FTDI_RANGE_9309_PID	0x9309
#घोषणा MTXORB_FTDI_RANGE_930A_PID	0x930A
#घोषणा MTXORB_FTDI_RANGE_930B_PID	0x930B
#घोषणा MTXORB_FTDI_RANGE_930C_PID	0x930C
#घोषणा MTXORB_FTDI_RANGE_930D_PID	0x930D
#घोषणा MTXORB_FTDI_RANGE_930E_PID	0x930E
#घोषणा MTXORB_FTDI_RANGE_930F_PID	0x930F
#घोषणा MTXORB_FTDI_RANGE_9310_PID	0x9310
#घोषणा MTXORB_FTDI_RANGE_9311_PID	0x9311
#घोषणा MTXORB_FTDI_RANGE_9312_PID	0x9312
#घोषणा MTXORB_FTDI_RANGE_9313_PID	0x9313
#घोषणा MTXORB_FTDI_RANGE_9314_PID	0x9314
#घोषणा MTXORB_FTDI_RANGE_9315_PID	0x9315
#घोषणा MTXORB_FTDI_RANGE_9316_PID	0x9316
#घोषणा MTXORB_FTDI_RANGE_9317_PID	0x9317
#घोषणा MTXORB_FTDI_RANGE_9318_PID	0x9318
#घोषणा MTXORB_FTDI_RANGE_9319_PID	0x9319
#घोषणा MTXORB_FTDI_RANGE_931A_PID	0x931A
#घोषणा MTXORB_FTDI_RANGE_931B_PID	0x931B
#घोषणा MTXORB_FTDI_RANGE_931C_PID	0x931C
#घोषणा MTXORB_FTDI_RANGE_931D_PID	0x931D
#घोषणा MTXORB_FTDI_RANGE_931E_PID	0x931E
#घोषणा MTXORB_FTDI_RANGE_931F_PID	0x931F

/*
 * The Mobility Lab (TML)
 * Submitted by Pierre Castella
 */
#घोषणा TML_VID			0x1B91	/* Venकरोr ID */
#घोषणा TML_USB_SERIAL_PID	0x0064	/* USB - Serial Converter */

/* Alti-2 products  http://www.alti-2.com */
#घोषणा ALTI2_VID	0x1BC9
#घोषणा ALTI2_N3_PID	0x6001	/* Neptune 3 */

/*
 * Ionics PlugComputer
 */
#घोषणा IONICS_VID			0x1c0c
#घोषणा IONICS_PLUGCOMPUTER_PID		0x0102

/*
 * EZPrototypes (PID reseller)
 */
#घोषणा EZPROTOTYPES_VID		0x1c40
#घोषणा HJELMSLUND_USB485_ISO_PID	0x0477

/*
 * Dresden Elektronik Sensor Terminal Board
 */
#घोषणा DE_VID			0x1cf1 /* Venकरोr ID */
#घोषणा STB_PID			0x0001 /* Sensor Terminal Board */
#घोषणा WHT_PID			0x0004 /* Wireless Handheld Terminal */

/*
 * STMicroelectonics
 */
#घोषणा ST_VID			0x0483
#घोषणा ST_STMCLT_2232_PID	0x3746
#घोषणा ST_STMCLT_4232_PID	0x3747

/*
 * Papouch products (http://www.papouch.com/)
 * Submitted by Folkert van Heusden
 */

#घोषणा PAPOUCH_VID			0x5050	/* Venकरोr ID */
#घोषणा PAPOUCH_SB485_PID		0x0100	/* Papouch SB485 USB-485/422 Converter */
#घोषणा PAPOUCH_AP485_PID		0x0101	/* AP485 USB-RS485 Converter */
#घोषणा PAPOUCH_SB422_PID		0x0102	/* Papouch SB422 USB-RS422 Converter  */
#घोषणा PAPOUCH_SB485_2_PID		0x0103	/* Papouch SB485 USB-485/422 Converter */
#घोषणा PAPOUCH_AP485_2_PID		0x0104	/* AP485 USB-RS485 Converter */
#घोषणा PAPOUCH_SB422_2_PID		0x0105	/* Papouch SB422 USB-RS422 Converter  */
#घोषणा PAPOUCH_SB485S_PID		0x0106	/* Papouch SB485S USB-485/422 Converter */
#घोषणा PAPOUCH_SB485C_PID		0x0107	/* Papouch SB485C USB-485/422 Converter */
#घोषणा PAPOUCH_LEC_PID			0x0300	/* LEC USB Converter */
#घोषणा PAPOUCH_SB232_PID		0x0301	/* Papouch SB232 USB-RS232 Converter */
#घोषणा PAPOUCH_TMU_PID			0x0400	/* TMU USB Thermometer */
#घोषणा PAPOUCH_IRAMP_PID		0x0500	/* Papouch IRAmp Duplex */
#घोषणा PAPOUCH_DRAK5_PID		0x0700	/* Papouch DRAK5 */
#घोषणा PAPOUCH_QUIDO8x8_PID		0x0800	/* Papouch Quiकरो 8/8 Module */
#घोषणा PAPOUCH_QUIDO4x4_PID		0x0900	/* Papouch Quiकरो 4/4 Module */
#घोषणा PAPOUCH_QUIDO2x2_PID		0x0a00	/* Papouch Quiकरो 2/2 Module */
#घोषणा PAPOUCH_QUIDO10x1_PID		0x0b00	/* Papouch Quiकरो 10/1 Module */
#घोषणा PAPOUCH_QUIDO30x3_PID		0x0c00	/* Papouch Quiकरो 30/3 Module */
#घोषणा PAPOUCH_QUIDO60x3_PID		0x0d00	/* Papouch Quiकरो 60(100)/3 Module */
#घोषणा PAPOUCH_QUIDO2x16_PID		0x0e00	/* Papouch Quiकरो 2/16 Module */
#घोषणा PAPOUCH_QUIDO3x32_PID		0x0f00	/* Papouch Quiकरो 3/32 Module */
#घोषणा PAPOUCH_DRAK6_PID		0x1000	/* Papouch DRAK6 */
#घोषणा PAPOUCH_UPSUSB_PID		0x8000	/* Papouch UPS-USB adapter */
#घोषणा PAPOUCH_MU_PID			0x8001	/* MU controller */
#घोषणा PAPOUCH_SIMUKEY_PID		0x8002	/* Papouch SimuKey */
#घोषणा PAPOUCH_AD4USB_PID		0x8003	/* AD4USB Measurement Module */
#घोषणा PAPOUCH_GMUX_PID		0x8004	/* Papouch GOLIATH MUX */
#घोषणा PAPOUCH_GMSR_PID		0x8005	/* Papouch GOLIATH MSR */

/*
 * Marvell SheevaPlug
 */
#घोषणा MARVELL_VID		0x9e88
#घोषणा MARVELL_SHEEVAPLUG_PID	0x9e8f

/*
 * Evolution Robotics products (http://www.evolution.com/).
 * Submitted by Shawn M. Lavelle.
 */
#घोषणा EVOLUTION_VID		0xDEEE	/* Venकरोr ID */
#घोषणा EVOLUTION_ER1_PID	0x0300	/* ER1 Control Module */
#घोषणा EVO_8U232AM_PID		0x02FF	/* Evolution robotics RCM2 (FT232AM)*/
#घोषणा EVO_HYBRID_PID		0x0302	/* Evolution robotics RCM4 PID (FT232BM)*/
#घोषणा EVO_RCM4_PID		0x0303	/* Evolution robotics RCM4 PID */

/*
 * MJS Gadमाला_लो HD Radio / XM Radio / Sirius Radio पूर्णांकerfaces (using VID 0x0403)
 */
#घोषणा MJSG_GENERIC_PID	0x9378
#घोषणा MJSG_SR_RADIO_PID	0x9379
#घोषणा MJSG_XM_RADIO_PID	0x937A
#घोषणा MJSG_HD_RADIO_PID	0x937C

/*
 * D.O.Tec products (http://www.directout.eu)
 */
#घोषणा FTDI_DOTEC_PID 0x9868

/*
 * Xverve Signalyzer tools (http://www.संकेतyzer.com/)
 */
#घोषणा XVERVE_SIGNALYZER_ST_PID	0xBCA0
#घोषणा XVERVE_SIGNALYZER_SLITE_PID	0xBCA1
#घोषणा XVERVE_SIGNALYZER_SH2_PID	0xBCA2
#घोषणा XVERVE_SIGNALYZER_SH4_PID	0xBCA4

/*
 * Segway Robotic Mobility Platक्रमm USB पूर्णांकerface (using VID 0x0403)
 * Submitted by John G. Rogers
 */
#घोषणा SEGWAY_RMP200_PID	0xe729


/*
 * Accesio USB Data Acquisition products (http://www.accesio.com/)
 */
#घोषणा ACCESIO_COM4SM_PID 	0xD578

/* www.sciencescope.co.uk educational dataloggers */
#घोषणा FTDI_SCIENCESCOPE_LOGBOOKML_PID		0xFF18
#घोषणा FTDI_SCIENCESCOPE_LS_LOGBOOK_PID	0xFF1C
#घोषणा FTDI_SCIENCESCOPE_HS_LOGBOOK_PID	0xFF1D

/*
 * Milkymist One JTAG/Serial
 */
#घोषणा QIHARDWARE_VID			0x20B7
#घोषणा MILKYMISTONE_JTAGSERIAL_PID	0x0713

/*
 * CTI GmbH RS485 Converter http://www.cti-lean.com/
 */
/* USB-485-Mini*/
#घोषणा FTDI_CTI_MINI_PID	0xF608
/* USB-Nano-485*/
#घोषणा FTDI_CTI_न_अंकO_PID	0xF60B

/*
 * ZeitControl cardप्रणालीs GmbH rfid-पढ़ोers http://zeitcontrol.de
 */
/* TagTracer MIFARE*/
#घोषणा FTDI_ZEITCONTROL_TAGTRACE_MIFARE_PID	0xF7C0

/*
 * Rainक्रमest Automation
 */
/* ZigBee controller */
#घोषणा FTDI_RF_R106		0x8A28

/*
 * Product: HCP HIT GPRS modem
 * Manufacturer: HCP d.o.o.
 * ATI command output: Cपूर्णांकerion MC55i
 */
#घोषणा FTDI_CINTERION_MC55I_PID	0xA951

/*
 * Product: FirmwareHubEmulator
 * Manufacturer: Harman Becker Automotive Systems
 */
#घोषणा FTDI_FHE_PID		0xA9A0

/*
 * Product: Comet Caller ID decoder
 * Manufacturer: Crucible Technologies
 */
#घोषणा FTDI_CT_COMET_PID	0x8e08

/*
 * Product: Z3X Box
 * Manufacturer: Smart GSM Team
 */
#घोषणा FTDI_Z3X_PID		0x0011

/*
 * Product: Cressi PC Interface
 * Manufacturer: Cressi
 */
#घोषणा FTDI_CRESSI_PID		0x87d0

/*
 * Brainboxes devices
 */
#घोषणा BRAINBOXES_VID			0x05d1
#घोषणा BRAINBOXES_VX_001_PID		0x1001 /* VX-001 ExpressCard 1 Port RS232 */
#घोषणा BRAINBOXES_VX_012_PID		0x1002 /* VX-012 ExpressCard 2 Port RS232 */
#घोषणा BRAINBOXES_VX_023_PID		0x1003 /* VX-023 ExpressCard 1 Port RS422/485 */
#घोषणा BRAINBOXES_VX_034_PID		0x1004 /* VX-034 ExpressCard 2 Port RS422/485 */
#घोषणा BRAINBOXES_US_101_PID		0x1011 /* US-101 1xRS232 */
#घोषणा BRAINBOXES_US_324_PID		0x1013 /* US-324 1xRS422/485 1Mbaud */
#घोषणा BRAINBOXES_US_606_1_PID		0x2001 /* US-606 6 Port RS232 Serial Port 1 and 2 */
#घोषणा BRAINBOXES_US_606_2_PID		0x2002 /* US-606 6 Port RS232 Serial Port 3 and 4 */
#घोषणा BRAINBOXES_US_606_3_PID		0x2003 /* US-606 6 Port RS232 Serial Port 4 and 6 */
#घोषणा BRAINBOXES_US_701_1_PID		0x2011 /* US-701 4xRS232 1Mbaud Port 1 and 2 */
#घोषणा BRAINBOXES_US_701_2_PID		0x2012 /* US-701 4xRS422 1Mbaud Port 3 and 4 */
#घोषणा BRAINBOXES_US_279_1_PID		0x2021 /* US-279 8xRS422 1Mbaud Port 1 and 2 */
#घोषणा BRAINBOXES_US_279_2_PID		0x2022 /* US-279 8xRS422 1Mbaud Port 3 and 4 */
#घोषणा BRAINBOXES_US_279_3_PID		0x2023 /* US-279 8xRS422 1Mbaud Port 5 and 6 */
#घोषणा BRAINBOXES_US_279_4_PID		0x2024 /* US-279 8xRS422 1Mbaud Port 7 and 8 */
#घोषणा BRAINBOXES_US_346_1_PID		0x3011 /* US-346 4xRS422/485 1Mbaud Port 1 and 2 */
#घोषणा BRAINBOXES_US_346_2_PID		0x3012 /* US-346 4xRS422/485 1Mbaud Port 3 and 4 */
#घोषणा BRAINBOXES_US_257_PID		0x5001 /* US-257 2xRS232 1Mbaud */
#घोषणा BRAINBOXES_US_313_PID		0x6001 /* US-313 2xRS422/485 1Mbaud */
#घोषणा BRAINBOXES_US_357_PID		0x7001 /* US_357 1xRS232/422/485 */
#घोषणा BRAINBOXES_US_842_1_PID		0x8001 /* US-842 8xRS422/485 1Mbaud Port 1 and 2 */
#घोषणा BRAINBOXES_US_842_2_PID		0x8002 /* US-842 8xRS422/485 1Mbaud Port 3 and 4 */
#घोषणा BRAINBOXES_US_842_3_PID		0x8003 /* US-842 8xRS422/485 1Mbaud Port 5 and 6 */
#घोषणा BRAINBOXES_US_842_4_PID		0x8004 /* US-842 8xRS422/485 1Mbaud Port 7 and 8 */
#घोषणा BRAINBOXES_US_160_1_PID		0x9001 /* US-160 16xRS232 1Mbaud Port 1 and 2 */
#घोषणा BRAINBOXES_US_160_2_PID		0x9002 /* US-160 16xRS232 1Mbaud Port 3 and 4 */
#घोषणा BRAINBOXES_US_160_3_PID		0x9003 /* US-160 16xRS232 1Mbaud Port 5 and 6 */
#घोषणा BRAINBOXES_US_160_4_PID		0x9004 /* US-160 16xRS232 1Mbaud Port 7 and 8 */
#घोषणा BRAINBOXES_US_160_5_PID		0x9005 /* US-160 16xRS232 1Mbaud Port 9 and 10 */
#घोषणा BRAINBOXES_US_160_6_PID		0x9006 /* US-160 16xRS232 1Mbaud Port 11 and 12 */
#घोषणा BRAINBOXES_US_160_7_PID		0x9007 /* US-160 16xRS232 1Mbaud Port 13 and 14 */
#घोषणा BRAINBOXES_US_160_8_PID		0x9008 /* US-160 16xRS232 1Mbaud Port 15 and 16 */

/*
 * ekey biometric प्रणालीs GmbH (http://ekey.net/)
 */
#घोषणा FTDI_EKEY_CONV_USB_PID		0xCB08	/* Converter USB */

/*
 * GE Healthcare devices
 */
#घोषणा GE_HEALTHCARE_VID		0x1901
#घोषणा GE_HEALTHCARE_NEMO_TRACKER_PID	0x0015

/*
 * Active Research (Actisense) devices
 */
#घोषणा ACTISENSE_NDC_PID		0xD9A8 /* NDC USB Serial Adapter */
#घोषणा ACTISENSE_USG_PID		0xD9A9 /* USG USB Serial Adapter */
#घोषणा ACTISENSE_NGT_PID		0xD9AA /* NGT NMEA2000 Interface */
#घोषणा ACTISENSE_NGW_PID		0xD9AB /* NGW NMEA2000 Gateway */
#घोषणा ACTISENSE_D9AC_PID		0xD9AC /* Actisense Reserved */
#घोषणा ACTISENSE_D9AD_PID		0xD9AD /* Actisense Reserved */
#घोषणा ACTISENSE_D9AE_PID		0xD9AE /* Actisense Reserved */
#घोषणा ACTISENSE_D9AF_PID		0xD9AF /* Actisense Reserved */
#घोषणा CHETCO_SEAGAUGE_PID		0xA548 /* SeaGauge USB Adapter */
#घोषणा CHETCO_SEASWITCH_PID		0xA549 /* SeaSwitch USB Adapter */
#घोषणा CHETCO_SEASMART_NMEA2000_PID	0xA54A /* SeaSmart NMEA2000 Gateway */
#घोषणा CHETCO_SEASMART_ETHERNET_PID	0xA54B /* SeaSmart Ethernet Gateway */
#घोषणा CHETCO_SEASMART_WIFI_PID	0xA5AC /* SeaSmart Wअगरi Gateway */
#घोषणा CHETCO_SEASMART_DISPLAY_PID	0xA5AD /* SeaSmart NMEA2000 Display */
#घोषणा CHETCO_SEASMART_LITE_PID	0xA5AE /* SeaSmart Lite USB Adapter */
#घोषणा CHETCO_SEASMART_ANALOG_PID	0xA5AF /* SeaSmart Analog Adapter */

/*
 * Unjo AB
 */
#घोषणा UNJO_VID			0x22B7
#घोषणा UNJO_ISODEBUG_V1_PID		0x150D

/*
 * IDS GmbH
 */
#घोषणा IDS_VID				0x2CAF
#घोषणा IDS_SI31A_PID			0x13A2
#घोषणा IDS_CM31A_PID			0x13A3

/*
 * U-Blox products (http://www.u-blox.com).
 */
#घोषणा UBLOX_VID			0x1546
#घोषणा UBLOX_C099F9P_ZED_PID		0x0502
#घोषणा UBLOX_C099F9P_ODIN_PID		0x0503
