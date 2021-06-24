<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Silicon Laboratories CP210x USB to RS232 serial adaptor driver
 *
 * Copyright (C) 2005 Craig Shelley (craig@microtron.org.uk)
 * Copyright (C) 2010-2021 Johan Hovold (johan@kernel.org)
 *
 * Support to set flow control line levels using TIOCMGET and TIOCMSET
 * thanks to Karl Hiramoto karl@hiramoto.org. RTSCTS hardware flow
 * control thanks to Munir Nassar nassarmu@real-समय.com
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>

#घोषणा DRIVER_DESC "Silicon Labs CP210x RS232 serial adaptor driver"

/*
 * Function Prototypes
 */
अटल पूर्णांक cp210x_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *);
अटल व्योम cp210x_बंद(काष्ठा usb_serial_port *);
अटल व्योम cp210x_change_speed(काष्ठा tty_काष्ठा *, काष्ठा usb_serial_port *,
							काष्ठा ktermios *);
अटल व्योम cp210x_set_termios(काष्ठा tty_काष्ठा *, काष्ठा usb_serial_port *,
							काष्ठा ktermios*);
अटल bool cp210x_tx_empty(काष्ठा usb_serial_port *port);
अटल पूर्णांक cp210x_tiocmget(काष्ठा tty_काष्ठा *);
अटल पूर्णांक cp210x_tiocmset(काष्ठा tty_काष्ठा *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
अटल पूर्णांक cp210x_tiocmset_port(काष्ठा usb_serial_port *port,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
अटल व्योम cp210x_अवरोध_ctl(काष्ठा tty_काष्ठा *, पूर्णांक);
अटल पूर्णांक cp210x_attach(काष्ठा usb_serial *);
अटल व्योम cp210x_disconnect(काष्ठा usb_serial *);
अटल व्योम cp210x_release(काष्ठा usb_serial *);
अटल पूर्णांक cp210x_port_probe(काष्ठा usb_serial_port *);
अटल व्योम cp210x_port_हटाओ(काष्ठा usb_serial_port *);
अटल व्योम cp210x_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on);
अटल व्योम cp210x_process_पढ़ो_urb(काष्ठा urb *urb);
अटल व्योम cp210x_enable_event_mode(काष्ठा usb_serial_port *port);
अटल व्योम cp210x_disable_event_mode(काष्ठा usb_serial_port *port);

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x045B, 0x0053) पूर्ण, /* Renesas RX610 RX-Stick */
	अणु USB_DEVICE(0x0471, 0x066A) पूर्ण, /* AKTAKOM ACE-1001 cable */
	अणु USB_DEVICE(0x0489, 0xE000) पूर्ण, /* Pirelli Broadband S.p.A, DP-L10 SIP/GSM Mobile */
	अणु USB_DEVICE(0x0489, 0xE003) पूर्ण, /* Pirelli Broadband S.p.A, DP-L10 SIP/GSM Mobile */
	अणु USB_DEVICE(0x0745, 0x1000) पूर्ण, /* CipherLab USB CCD Barcode Scanner 1000 */
	अणु USB_DEVICE(0x0846, 0x1100) पूर्ण, /* NetGear Managed Switch M4100 series, M5300 series, M7100 series */
	अणु USB_DEVICE(0x08e6, 0x5501) पूर्ण, /* Gemalto Prox-PU/CU contactless smartcard पढ़ोer */
	अणु USB_DEVICE(0x08FD, 0x000A) पूर्ण, /* Digianswer A/S , ZigBee/802.15.4 MAC Device */
	अणु USB_DEVICE(0x0908, 0x01FF) पूर्ण, /* Siemens RUGGEDCOM USB Serial Console */
	अणु USB_DEVICE(0x0988, 0x0578) पूर्ण, /* Teraoka AD2000 */
	अणु USB_DEVICE(0x0B00, 0x3070) पूर्ण, /* Ingenico 3070 */
	अणु USB_DEVICE(0x0BED, 0x1100) पूर्ण, /* MEI (TM) Cashflow-SC Bill/Voucher Acceptor */
	अणु USB_DEVICE(0x0BED, 0x1101) पूर्ण, /* MEI series 2000 Combo Acceptor */
	अणु USB_DEVICE(0x0FCF, 0x1003) पूर्ण, /* Dynastream ANT development board */
	अणु USB_DEVICE(0x0FCF, 0x1004) पूर्ण, /* Dynastream ANT2USB */
	अणु USB_DEVICE(0x0FCF, 0x1006) पूर्ण, /* Dynastream ANT development board */
	अणु USB_DEVICE(0x0FDE, 0xCA05) पूर्ण, /* OWL Wireless Electricity Monitor CM-160 */
	अणु USB_DEVICE(0x10A6, 0xAA26) पूर्ण, /* Knock-off DCU-11 cable */
	अणु USB_DEVICE(0x10AB, 0x10C5) पूर्ण, /* Siemens MC60 Cable */
	अणु USB_DEVICE(0x10B5, 0xAC70) पूर्ण, /* Nokia CA-42 USB */
	अणु USB_DEVICE(0x10C4, 0x0F91) पूर्ण, /* Vstabi */
	अणु USB_DEVICE(0x10C4, 0x1101) पूर्ण, /* Arkham Technology DS101 Bus Monitor */
	अणु USB_DEVICE(0x10C4, 0x1601) पूर्ण, /* Arkham Technology DS101 Adapter */
	अणु USB_DEVICE(0x10C4, 0x800A) पूर्ण, /* SPORTident BSM7-D-USB मुख्य station */
	अणु USB_DEVICE(0x10C4, 0x803B) पूर्ण, /* Pololu USB-serial converter */
	अणु USB_DEVICE(0x10C4, 0x8044) पूर्ण, /* Cygnal Debug Adapter */
	अणु USB_DEVICE(0x10C4, 0x804E) पूर्ण, /* Software Bisque Paramount ME build-in converter */
	अणु USB_DEVICE(0x10C4, 0x8053) पूर्ण, /* Enक्रमa EDG1228 */
	अणु USB_DEVICE(0x10C4, 0x8054) पूर्ण, /* Enक्रमa GSM2228 */
	अणु USB_DEVICE(0x10C4, 0x8056) पूर्ण, /* Lorenz Messtechnik devices */
	अणु USB_DEVICE(0x10C4, 0x8066) पूर्ण, /* Argussoft In-System Programmer */
	अणु USB_DEVICE(0x10C4, 0x806F) पूर्ण, /* IMS USB to RS422 Converter Cable */
	अणु USB_DEVICE(0x10C4, 0x807A) पूर्ण, /* Crumb128 board */
	अणु USB_DEVICE(0x10C4, 0x80C4) पूर्ण, /* Cygnal Integrated Products, Inc., Optris infrared thermometer */
	अणु USB_DEVICE(0x10C4, 0x80CA) पूर्ण, /* Degree Controls Inc */
	अणु USB_DEVICE(0x10C4, 0x80DD) पूर्ण, /* Tracient RFID */
	अणु USB_DEVICE(0x10C4, 0x80F6) पूर्ण, /* Suunto sports instrument */
	अणु USB_DEVICE(0x10C4, 0x8115) पूर्ण, /* Arygon NFC/Mअगरare Reader */
	अणु USB_DEVICE(0x10C4, 0x813D) पूर्ण, /* Burnside Telecom Deskmobile */
	अणु USB_DEVICE(0x10C4, 0x813F) पूर्ण, /* Tams Master Easy Control */
	अणु USB_DEVICE(0x10C4, 0x814A) पूर्ण, /* West Mountain Radio RIGblaster P&P */
	अणु USB_DEVICE(0x10C4, 0x814B) पूर्ण, /* West Mountain Radio RIGtalk */
	अणु USB_DEVICE(0x2405, 0x0003) पूर्ण, /* West Mountain Radio RIGblaster Advantage */
	अणु USB_DEVICE(0x10C4, 0x8156) पूर्ण, /* B&G H3000 link cable */
	अणु USB_DEVICE(0x10C4, 0x815E) पूर्ण, /* Helicomm IP-Link 1220-DVM */
	अणु USB_DEVICE(0x10C4, 0x815F) पूर्ण, /* Timewave HamLinkUSB */
	अणु USB_DEVICE(0x10C4, 0x817C) पूर्ण, /* CESINEL MEDCAL N Power Quality Monitor */
	अणु USB_DEVICE(0x10C4, 0x817D) पूर्ण, /* CESINEL MEDCAL NT Power Quality Monitor */
	अणु USB_DEVICE(0x10C4, 0x817E) पूर्ण, /* CESINEL MEDCAL S Power Quality Monitor */
	अणु USB_DEVICE(0x10C4, 0x818B) पूर्ण, /* AVIT Research USB to TTL */
	अणु USB_DEVICE(0x10C4, 0x819F) पूर्ण, /* MJS USB Toslink Switcher */
	अणु USB_DEVICE(0x10C4, 0x81A6) पूर्ण, /* ThinkOptics WavIt */
	अणु USB_DEVICE(0x10C4, 0x81A9) पूर्ण, /* Multiplex RC Interface */
	अणु USB_DEVICE(0x10C4, 0x81AC) पूर्ण, /* MSD Dash Hawk */
	अणु USB_DEVICE(0x10C4, 0x81AD) पूर्ण, /* INSYS USB Modem */
	अणु USB_DEVICE(0x10C4, 0x81C8) पूर्ण, /* Liघातsky Industrie Elektronik GmbH, Baby-JTAG */
	अणु USB_DEVICE(0x10C4, 0x81D7) पूर्ण, /* IAI Corp. RCB-CV-USB USB to RS485 Adaptor */
	अणु USB_DEVICE(0x10C4, 0x81E2) पूर्ण, /* Liघातsky Industrie Elektronik GmbH, Baby-LIN */
	अणु USB_DEVICE(0x10C4, 0x81E7) पूर्ण, /* Aerocomm Radio */
	अणु USB_DEVICE(0x10C4, 0x81E8) पूर्ण, /* Zephyr Bioharness */
	अणु USB_DEVICE(0x10C4, 0x81F2) पूर्ण, /* C1007 HF band RFID controller */
	अणु USB_DEVICE(0x10C4, 0x8218) पूर्ण, /* Liघातsky Industrie Elektronik GmbH, HARP-1 */
	अणु USB_DEVICE(0x10C4, 0x822B) पूर्ण, /* Modem EDGE(GSM) Comander 2 */
	अणु USB_DEVICE(0x10C4, 0x826B) पूर्ण, /* Cygnal Integrated Products, Inc., Fasttrax GPS demonstration module */
	अणु USB_DEVICE(0x10C4, 0x8281) पूर्ण, /* Nanotec Plug & Drive */
	अणु USB_DEVICE(0x10C4, 0x8293) पूर्ण, /* Telegesis ETRX2USB */
	अणु USB_DEVICE(0x10C4, 0x82EF) पूर्ण, /* CESINEL FALCO 6105 AC Power Supply */
	अणु USB_DEVICE(0x10C4, 0x82F1) पूर्ण, /* CESINEL MEDCAL EFD Earth Fault Detector */
	अणु USB_DEVICE(0x10C4, 0x82F2) पूर्ण, /* CESINEL MEDCAL ST Network Analyzer */
	अणु USB_DEVICE(0x10C4, 0x82F4) पूर्ण, /* Starizona MicroTouch */
	अणु USB_DEVICE(0x10C4, 0x82F9) पूर्ण, /* Procyon AVS */
	अणु USB_DEVICE(0x10C4, 0x8341) पूर्ण, /* Siemens MC35PU GPRS Modem */
	अणु USB_DEVICE(0x10C4, 0x8382) पूर्ण, /* Cygnal Integrated Products, Inc. */
	अणु USB_DEVICE(0x10C4, 0x83A8) पूर्ण, /* Amber Wireless AMB2560 */
	अणु USB_DEVICE(0x10C4, 0x83AA) पूर्ण, /* Mark-10 Digital Force Gauge */
	अणु USB_DEVICE(0x10C4, 0x83D8) पूर्ण, /* DekTec DTA Plus VHF/UHF Booster/Attenuator */
	अणु USB_DEVICE(0x10C4, 0x8411) पूर्ण, /* Kyocera GPS Module */
	अणु USB_DEVICE(0x10C4, 0x8418) पूर्ण, /* IRZ Automation Teleport SG-10 GSM/GPRS Modem */
	अणु USB_DEVICE(0x10C4, 0x846E) पूर्ण, /* BEI USB Sensor Interface (VCP) */
	अणु USB_DEVICE(0x10C4, 0x8470) पूर्ण, /* Juniper Networks BX Series System Console */
	अणु USB_DEVICE(0x10C4, 0x8477) पूर्ण, /* Balluff RFID */
	अणु USB_DEVICE(0x10C4, 0x84B6) पूर्ण, /* Starizona Hyperion */
	अणु USB_DEVICE(0x10C4, 0x851E) पूर्ण, /* CESINEL MEDCAL PT Network Analyzer */
	अणु USB_DEVICE(0x10C4, 0x85A7) पूर्ण, /* LअगरeScan OneTouch Verio IQ */
	अणु USB_DEVICE(0x10C4, 0x85B8) पूर्ण, /* CESINEL ReCon T Energy Logger */
	अणु USB_DEVICE(0x10C4, 0x85EA) पूर्ण, /* AC-Services IBUS-IF */
	अणु USB_DEVICE(0x10C4, 0x85EB) पूर्ण, /* AC-Services CIS-IBUS */
	अणु USB_DEVICE(0x10C4, 0x85F8) पूर्ण, /* Virtenio Preon32 */
	अणु USB_DEVICE(0x10C4, 0x8664) पूर्ण, /* AC-Services CAN-IF */
	अणु USB_DEVICE(0x10C4, 0x8665) पूर्ण, /* AC-Services OBD-IF */
	अणु USB_DEVICE(0x10C4, 0x8856) पूर्ण,	/* CEL EM357 ZigBee USB Stick - LR */
	अणु USB_DEVICE(0x10C4, 0x8857) पूर्ण,	/* CEL EM357 ZigBee USB Stick */
	अणु USB_DEVICE(0x10C4, 0x88A4) पूर्ण, /* MMB Networks ZigBee USB Device */
	अणु USB_DEVICE(0x10C4, 0x88A5) पूर्ण, /* Planet Innovation Ingeni ZigBee USB Device */
	अणु USB_DEVICE(0x10C4, 0x88D8) पूर्ण, /* Acuity Bअक्रमs nLight Air Adapter */
	अणु USB_DEVICE(0x10C4, 0x88FB) पूर्ण, /* CESINEL MEDCAL STII Network Analyzer */
	अणु USB_DEVICE(0x10C4, 0x8938) पूर्ण, /* CESINEL MEDCAL S II Network Analyzer */
	अणु USB_DEVICE(0x10C4, 0x8946) पूर्ण, /* Ketra N1 Wireless Interface */
	अणु USB_DEVICE(0x10C4, 0x8962) पूर्ण, /* Brim Brothers अक्षरging करोck */
	अणु USB_DEVICE(0x10C4, 0x8977) पूर्ण,	/* CEL MeshWorks DevKit Device */
	अणु USB_DEVICE(0x10C4, 0x8998) पूर्ण, /* KCF Technologies PRN */
	अणु USB_DEVICE(0x10C4, 0x89A4) पूर्ण, /* CESINEL FTBC Flexible Thyristor Bridge Controller */
	अणु USB_DEVICE(0x10C4, 0x89FB) पूर्ण, /* Qivicon ZigBee USB Radio Stick */
	अणु USB_DEVICE(0x10C4, 0x8A2A) पूर्ण, /* HubZ dual ZigBee and Z-Wave करोngle */
	अणु USB_DEVICE(0x10C4, 0x8A5E) पूर्ण, /* CEL EM3588 ZigBee USB Stick Long Range */
	अणु USB_DEVICE(0x10C4, 0x8B34) पूर्ण, /* Qivicon ZigBee USB Radio Stick */
	अणु USB_DEVICE(0x10C4, 0xEA60) पूर्ण, /* Silicon Lअसल factory शेष */
	अणु USB_DEVICE(0x10C4, 0xEA61) पूर्ण, /* Silicon Lअसल factory शेष */
	अणु USB_DEVICE(0x10C4, 0xEA63) पूर्ण, /* Silicon Lअसल Winकरोws Update (CP2101-4/CP2102N) */
	अणु USB_DEVICE(0x10C4, 0xEA70) पूर्ण, /* Silicon Lअसल factory शेष */
	अणु USB_DEVICE(0x10C4, 0xEA71) पूर्ण, /* Infinity GPS-MIC-1 Radio Monophone */
	अणु USB_DEVICE(0x10C4, 0xEA7A) पूर्ण, /* Silicon Lअसल Winकरोws Update (CP2105) */
	अणु USB_DEVICE(0x10C4, 0xEA7B) पूर्ण, /* Silicon Lअसल Winकरोws Update (CP2108) */
	अणु USB_DEVICE(0x10C4, 0xF001) पूर्ण, /* Elan Digital Systems USBscope50 */
	अणु USB_DEVICE(0x10C4, 0xF002) पूर्ण, /* Elan Digital Systems USBwave12 */
	अणु USB_DEVICE(0x10C4, 0xF003) पूर्ण, /* Elan Digital Systems USBpulse100 */
	अणु USB_DEVICE(0x10C4, 0xF004) पूर्ण, /* Elan Digital Systems USBcount50 */
	अणु USB_DEVICE(0x10C5, 0xEA61) पूर्ण, /* Silicon Lअसल MobiData GPRS USB Modem */
	अणु USB_DEVICE(0x10CE, 0xEA6A) पूर्ण, /* Silicon Lअसल MobiData GPRS USB Modem 100EU */
	अणु USB_DEVICE(0x12B8, 0xEC60) पूर्ण, /* Link G4 ECU */
	अणु USB_DEVICE(0x12B8, 0xEC62) पूर्ण, /* Link G4+ ECU */
	अणु USB_DEVICE(0x13AD, 0x9999) पूर्ण, /* Baltech card पढ़ोer */
	अणु USB_DEVICE(0x1555, 0x0004) पूर्ण, /* Owen AC4 USB-RS485 Converter */
	अणु USB_DEVICE(0x155A, 0x1006) पूर्ण,	/* ELDAT Easywave RX09 */
	अणु USB_DEVICE(0x166A, 0x0201) पूर्ण, /* Clipsal 5500PACA C-Bus Pascal Automation Controller */
	अणु USB_DEVICE(0x166A, 0x0301) पूर्ण, /* Clipsal 5800PC C-Bus Wireless PC Interface */
	अणु USB_DEVICE(0x166A, 0x0303) पूर्ण, /* Clipsal 5500PCU C-Bus USB पूर्णांकerface */
	अणु USB_DEVICE(0x166A, 0x0304) पूर्ण, /* Clipsal 5000CT2 C-Bus Black and White Touchscreen */
	अणु USB_DEVICE(0x166A, 0x0305) पूर्ण, /* Clipsal C-5000CT2 C-Bus Spectrum Colour Touchscreen */
	अणु USB_DEVICE(0x166A, 0x0401) पूर्ण, /* Clipsal L51xx C-Bus Architectural Dimmer */
	अणु USB_DEVICE(0x166A, 0x0101) पूर्ण, /* Clipsal 5560884 C-Bus Multi-room Audio Matrix Switcher */
	अणु USB_DEVICE(0x16C0, 0x09B0) पूर्ण, /* Lunatico Seletek */
	अणु USB_DEVICE(0x16C0, 0x09B1) पूर्ण, /* Lunatico Seletek */
	अणु USB_DEVICE(0x16D6, 0x0001) पूर्ण, /* Jablotron serial पूर्णांकerface */
	अणु USB_DEVICE(0x16DC, 0x0010) पूर्ण, /* W-IE-NE-R Plein & Baus GmbH PL512 Power Supply */
	अणु USB_DEVICE(0x16DC, 0x0011) पूर्ण, /* W-IE-NE-R Plein & Baus GmbH RCM Remote Control क्रम MARATON Power Supply */
	अणु USB_DEVICE(0x16DC, 0x0012) पूर्ण, /* W-IE-NE-R Plein & Baus GmbH MPOD Multi Channel Power Supply */
	अणु USB_DEVICE(0x16DC, 0x0015) पूर्ण, /* W-IE-NE-R Plein & Baus GmbH CML Control, Monitoring and Data Logger */
	अणु USB_DEVICE(0x17A8, 0x0001) पूर्ण, /* Kamstrup Optical Eye/3-wire */
	अणु USB_DEVICE(0x17A8, 0x0005) पूर्ण, /* Kamstrup M-Bus Master MultiPort 250D */
	अणु USB_DEVICE(0x17F4, 0xAAAA) पूर्ण, /* Wavesense Jazz blood glucose meter */
	अणु USB_DEVICE(0x1843, 0x0200) पूर्ण, /* Vaisala USB Instrument Cable */
	अणु USB_DEVICE(0x18EF, 0xE00F) पूर्ण, /* ELV USB-I2C-Interface */
	अणु USB_DEVICE(0x18EF, 0xE025) पूर्ण, /* ELV Marble Sound Board 1 */
	अणु USB_DEVICE(0x18EF, 0xE030) पूर्ण, /* ELV ALC 8xxx Battery Charger */
	अणु USB_DEVICE(0x18EF, 0xE032) पूर्ण, /* ELV TFD500 Data Logger */
	अणु USB_DEVICE(0x1901, 0x0190) पूर्ण, /* GE B850 CP2105 Recorder पूर्णांकerface */
	अणु USB_DEVICE(0x1901, 0x0193) पूर्ण, /* GE B650 CP2104 PMC पूर्णांकerface */
	अणु USB_DEVICE(0x1901, 0x0194) पूर्ण,	/* GE Healthcare Remote Alarm Box */
	अणु USB_DEVICE(0x1901, 0x0195) पूर्ण,	/* GE B850/B650/B450 CP2104 DP UART पूर्णांकerface */
	अणु USB_DEVICE(0x1901, 0x0196) पूर्ण,	/* GE B850 CP2105 DP UART पूर्णांकerface */
	अणु USB_DEVICE(0x1901, 0x0197) पूर्ण, /* GE CS1000 Display serial पूर्णांकerface */
	अणु USB_DEVICE(0x1901, 0x0198) पूर्ण, /* GE CS1000 M.2 Key E serial पूर्णांकerface */
	अणु USB_DEVICE(0x199B, 0xBA30) पूर्ण, /* LORD WSDA-200-USB */
	अणु USB_DEVICE(0x19CF, 0x3000) पूर्ण, /* Parrot NMEA GPS Flight Recorder */
	अणु USB_DEVICE(0x1ADB, 0x0001) पूर्ण, /* Schweitzer Engineering C662 Cable */
	अणु USB_DEVICE(0x1B1C, 0x1C00) पूर्ण, /* Corsair USB Dongle */
	अणु USB_DEVICE(0x1BA4, 0x0002) पूर्ण,	/* Silicon Lअसल 358x factory शेष */
	अणु USB_DEVICE(0x1BE3, 0x07A6) पूर्ण, /* WAGO 750-923 USB Service Cable */
	अणु USB_DEVICE(0x1D6F, 0x0010) पूर्ण, /* Seluxit ApS RF Dongle */
	अणु USB_DEVICE(0x1E29, 0x0102) पूर्ण, /* Festo CPX-USB */
	अणु USB_DEVICE(0x1E29, 0x0501) पूर्ण, /* Festo CMSP */
	अणु USB_DEVICE(0x1FB9, 0x0100) पूर्ण, /* Lake Shore Model 121 Current Source */
	अणु USB_DEVICE(0x1FB9, 0x0200) पूर्ण, /* Lake Shore Model 218A Temperature Monitor */
	अणु USB_DEVICE(0x1FB9, 0x0201) पूर्ण, /* Lake Shore Model 219 Temperature Monitor */
	अणु USB_DEVICE(0x1FB9, 0x0202) पूर्ण, /* Lake Shore Model 233 Temperature Transmitter */
	अणु USB_DEVICE(0x1FB9, 0x0203) पूर्ण, /* Lake Shore Model 235 Temperature Transmitter */
	अणु USB_DEVICE(0x1FB9, 0x0300) पूर्ण, /* Lake Shore Model 335 Temperature Controller */
	अणु USB_DEVICE(0x1FB9, 0x0301) पूर्ण, /* Lake Shore Model 336 Temperature Controller */
	अणु USB_DEVICE(0x1FB9, 0x0302) पूर्ण, /* Lake Shore Model 350 Temperature Controller */
	अणु USB_DEVICE(0x1FB9, 0x0303) पूर्ण, /* Lake Shore Model 371 AC Bridge */
	अणु USB_DEVICE(0x1FB9, 0x0400) पूर्ण, /* Lake Shore Model 411 Handheld Gaussmeter */
	अणु USB_DEVICE(0x1FB9, 0x0401) पूर्ण, /* Lake Shore Model 425 Gaussmeter */
	अणु USB_DEVICE(0x1FB9, 0x0402) पूर्ण, /* Lake Shore Model 455A Gaussmeter */
	अणु USB_DEVICE(0x1FB9, 0x0403) पूर्ण, /* Lake Shore Model 475A Gaussmeter */
	अणु USB_DEVICE(0x1FB9, 0x0404) पूर्ण, /* Lake Shore Model 465 Three Axis Gaussmeter */
	अणु USB_DEVICE(0x1FB9, 0x0600) पूर्ण, /* Lake Shore Model 625A Superconducting MPS */
	अणु USB_DEVICE(0x1FB9, 0x0601) पूर्ण, /* Lake Shore Model 642A Magnet Power Supply */
	अणु USB_DEVICE(0x1FB9, 0x0602) पूर्ण, /* Lake Shore Model 648 Magnet Power Supply */
	अणु USB_DEVICE(0x1FB9, 0x0700) पूर्ण, /* Lake Shore Model 737 VSM Controller */
	अणु USB_DEVICE(0x1FB9, 0x0701) पूर्ण, /* Lake Shore Model 776 Hall Matrix */
	अणु USB_DEVICE(0x2626, 0xEA60) पूर्ण, /* Aruba Networks 7xxx USB Serial Console */
	अणु USB_DEVICE(0x3195, 0xF190) पूर्ण, /* Link Instruments MSO-19 */
	अणु USB_DEVICE(0x3195, 0xF280) पूर्ण, /* Link Instruments MSO-28 */
	अणु USB_DEVICE(0x3195, 0xF281) पूर्ण, /* Link Instruments MSO-28 */
	अणु USB_DEVICE(0x3923, 0x7A0B) पूर्ण, /* National Instruments USB Serial Console */
	अणु USB_DEVICE(0x413C, 0x9500) पूर्ण, /* DW700 GPS USB पूर्णांकerface */
	अणु पूर्ण /* Terminating Entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा cp210x_serial_निजी अणु
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip	gc;
	bool			gpio_रेजिस्टरed;
	u8			gpio_pushpull;
	u8			gpio_altfunc;
	u8			gpio_input;
#पूर्ण_अगर
	u8			partnum;
	u32			fw_version;
	speed_t			min_speed;
	speed_t			max_speed;
	bool			use_actual_rate;
	bool			no_flow_control;
पूर्ण;

क्रमागत cp210x_event_state अणु
	ES_DATA,
	ES_ESCAPE,
	ES_LSR,
	ES_LSR_DATA_0,
	ES_LSR_DATA_1,
	ES_MSR
पूर्ण;

काष्ठा cp210x_port_निजी अणु
	u8			bInterfaceNumber;
	bool			event_mode;
	क्रमागत cp210x_event_state event_state;
	u8			lsr;

	काष्ठा mutex		mutex;
	bool			crtscts;
	bool			dtr;
	bool			rts;
पूर्ण;

अटल काष्ठा usb_serial_driver cp210x_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"cp210x",
	पूर्ण,
	.id_table		= id_table,
	.num_ports		= 1,
	.bulk_in_size		= 256,
	.bulk_out_size		= 256,
	.खोलो			= cp210x_खोलो,
	.बंद			= cp210x_बंद,
	.अवरोध_ctl		= cp210x_अवरोध_ctl,
	.set_termios		= cp210x_set_termios,
	.tx_empty		= cp210x_tx_empty,
	.throttle		= usb_serial_generic_throttle,
	.unthrottle		= usb_serial_generic_unthrottle,
	.tiocmget		= cp210x_tiocmget,
	.tiocmset		= cp210x_tiocmset,
	.get_icount		= usb_serial_generic_get_icount,
	.attach			= cp210x_attach,
	.disconnect		= cp210x_disconnect,
	.release		= cp210x_release,
	.port_probe		= cp210x_port_probe,
	.port_हटाओ		= cp210x_port_हटाओ,
	.dtr_rts		= cp210x_dtr_rts,
	.process_पढ़ो_urb	= cp210x_process_पढ़ो_urb,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&cp210x_device, शून्य
पूर्ण;

/* Config request types */
#घोषणा REQTYPE_HOST_TO_INTERFACE	0x41
#घोषणा REQTYPE_INTERFACE_TO_HOST	0xc1
#घोषणा REQTYPE_HOST_TO_DEVICE	0x40
#घोषणा REQTYPE_DEVICE_TO_HOST	0xc0

/* Config request codes */
#घोषणा CP210X_IFC_ENABLE	0x00
#घोषणा CP210X_SET_BAUDDIV	0x01
#घोषणा CP210X_GET_BAUDDIV	0x02
#घोषणा CP210X_SET_LINE_CTL	0x03
#घोषणा CP210X_GET_LINE_CTL	0x04
#घोषणा CP210X_SET_BREAK	0x05
#घोषणा CP210X_IMM_CHAR		0x06
#घोषणा CP210X_SET_MHS		0x07
#घोषणा CP210X_GET_MDMSTS	0x08
#घोषणा CP210X_SET_XON		0x09
#घोषणा CP210X_SET_XOFF		0x0A
#घोषणा CP210X_SET_EVENTMASK	0x0B
#घोषणा CP210X_GET_EVENTMASK	0x0C
#घोषणा CP210X_SET_CHAR		0x0D
#घोषणा CP210X_GET_CHARS	0x0E
#घोषणा CP210X_GET_PROPS	0x0F
#घोषणा CP210X_GET_COMM_STATUS	0x10
#घोषणा CP210X_RESET		0x11
#घोषणा CP210X_PURGE		0x12
#घोषणा CP210X_SET_FLOW		0x13
#घोषणा CP210X_GET_FLOW		0x14
#घोषणा CP210X_EMBED_EVENTS	0x15
#घोषणा CP210X_GET_EVENTSTATE	0x16
#घोषणा CP210X_SET_CHARS	0x19
#घोषणा CP210X_GET_BAUDRATE	0x1D
#घोषणा CP210X_SET_BAUDRATE	0x1E
#घोषणा CP210X_VENDOR_SPECIFIC	0xFF

/* CP210X_IFC_ENABLE */
#घोषणा UART_ENABLE		0x0001
#घोषणा UART_DISABLE		0x0000

/* CP210X_(SET|GET)_BAUDDIV */
#घोषणा BAUD_RATE_GEN_FREQ	0x384000

/* CP210X_(SET|GET)_LINE_CTL */
#घोषणा BITS_DATA_MASK		0X0f00
#घोषणा BITS_DATA_5		0X0500
#घोषणा BITS_DATA_6		0X0600
#घोषणा BITS_DATA_7		0X0700
#घोषणा BITS_DATA_8		0X0800
#घोषणा BITS_DATA_9		0X0900

#घोषणा BITS_PARITY_MASK	0x00f0
#घोषणा BITS_PARITY_NONE	0x0000
#घोषणा BITS_PARITY_ODD		0x0010
#घोषणा BITS_PARITY_EVEN	0x0020
#घोषणा BITS_PARITY_MARK	0x0030
#घोषणा BITS_PARITY_SPACE	0x0040

#घोषणा BITS_STOP_MASK		0x000f
#घोषणा BITS_STOP_1		0x0000
#घोषणा BITS_STOP_1_5		0x0001
#घोषणा BITS_STOP_2		0x0002

/* CP210X_SET_BREAK */
#घोषणा BREAK_ON		0x0001
#घोषणा BREAK_OFF		0x0000

/* CP210X_(SET_MHS|GET_MDMSTS) */
#घोषणा CONTROL_DTR		0x0001
#घोषणा CONTROL_RTS		0x0002
#घोषणा CONTROL_CTS		0x0010
#घोषणा CONTROL_DSR		0x0020
#घोषणा CONTROL_RING		0x0040
#घोषणा CONTROL_DCD		0x0080
#घोषणा CONTROL_WRITE_DTR	0x0100
#घोषणा CONTROL_WRITE_RTS	0x0200

/* CP210X_(GET|SET)_CHARS */
काष्ठा cp210x_special_अक्षरs अणु
	u8	bEofChar;
	u8	bErrorChar;
	u8	bBreakChar;
	u8	bEventChar;
	u8	bXonChar;
	u8	bXoffChar;
पूर्ण;

/* CP210X_VENDOR_SPECIFIC values */
#घोषणा CP210X_READ_2NCONFIG	0x000E
#घोषणा CP210X_GET_FW_VER_2N	0x0010
#घोषणा CP210X_READ_LATCH	0x00C2
#घोषणा CP210X_GET_PARTNUM	0x370B
#घोषणा CP210X_GET_PORTCONFIG	0x370C
#घोषणा CP210X_GET_DEVICEMODE	0x3711
#घोषणा CP210X_WRITE_LATCH	0x37E1

/* Part number definitions */
#घोषणा CP210X_PARTNUM_CP2101	0x01
#घोषणा CP210X_PARTNUM_CP2102	0x02
#घोषणा CP210X_PARTNUM_CP2103	0x03
#घोषणा CP210X_PARTNUM_CP2104	0x04
#घोषणा CP210X_PARTNUM_CP2105	0x05
#घोषणा CP210X_PARTNUM_CP2108	0x08
#घोषणा CP210X_PARTNUM_CP2102N_QFN28	0x20
#घोषणा CP210X_PARTNUM_CP2102N_QFN24	0x21
#घोषणा CP210X_PARTNUM_CP2102N_QFN20	0x22
#घोषणा CP210X_PARTNUM_UNKNOWN	0xFF

/* CP210X_GET_COMM_STATUS वापसs these 0x13 bytes */
काष्ठा cp210x_comm_status अणु
	__le32   ulErrors;
	__le32   ulHoldReasons;
	__le32   ulAmountInInQueue;
	__le32   ulAmountInOutQueue;
	u8       bEofReceived;
	u8       bWaitForImmediate;
	u8       bReserved;
पूर्ण __packed;

/*
 * CP210X_PURGE - 16 bits passed in wValue of USB request.
 * SiLअसल app note AN571 gives a strange description of the 4 bits:
 * bit 0 or bit 2 clears the transmit queue and 1 or 3 receive.
 * writing 1 to all, however, purges cp2108 well enough to aव्योम the hang.
 */
#घोषणा PURGE_ALL		0x000f

/* CP210X_EMBED_EVENTS */
#घोषणा CP210X_ESCCHAR		0xec

#घोषणा CP210X_LSR_OVERRUN	BIT(1)
#घोषणा CP210X_LSR_PARITY	BIT(2)
#घोषणा CP210X_LSR_FRAME	BIT(3)
#घोषणा CP210X_LSR_BREAK	BIT(4)


/* CP210X_GET_FLOW/CP210X_SET_FLOW पढ़ो/ग_लिखो these 0x10 bytes */
काष्ठा cp210x_flow_ctl अणु
	__le32	ulControlHandshake;
	__le32	ulFlowReplace;
	__le32	ulXonLimit;
	__le32	ulXoffLimit;
पूर्ण;

/* cp210x_flow_ctl::ulControlHandshake */
#घोषणा CP210X_SERIAL_DTR_MASK		GENMASK(1, 0)
#घोषणा CP210X_SERIAL_DTR_INACTIVE	(0 << 0)
#घोषणा CP210X_SERIAL_DTR_ACTIVE	(1 << 0)
#घोषणा CP210X_SERIAL_DTR_FLOW_CTL	(2 << 0)
#घोषणा CP210X_SERIAL_CTS_HANDSHAKE	BIT(3)
#घोषणा CP210X_SERIAL_DSR_HANDSHAKE	BIT(4)
#घोषणा CP210X_SERIAL_DCD_HANDSHAKE	BIT(5)
#घोषणा CP210X_SERIAL_DSR_SENSITIVITY	BIT(6)

/* cp210x_flow_ctl::ulFlowReplace */
#घोषणा CP210X_SERIAL_AUTO_TRANSMIT	BIT(0)
#घोषणा CP210X_SERIAL_AUTO_RECEIVE	BIT(1)
#घोषणा CP210X_SERIAL_ERROR_CHAR	BIT(2)
#घोषणा CP210X_SERIAL_शून्य_STRIPPING	BIT(3)
#घोषणा CP210X_SERIAL_BREAK_CHAR	BIT(4)
#घोषणा CP210X_SERIAL_RTS_MASK		GENMASK(7, 6)
#घोषणा CP210X_SERIAL_RTS_INACTIVE	(0 << 6)
#घोषणा CP210X_SERIAL_RTS_ACTIVE	(1 << 6)
#घोषणा CP210X_SERIAL_RTS_FLOW_CTL	(2 << 6)
#घोषणा CP210X_SERIAL_XOFF_CONTINUE	BIT(31)

/* CP210X_VENDOR_SPECIFIC, CP210X_GET_DEVICEMODE call पढ़ोs these 0x2 bytes. */
काष्ठा cp210x_pin_mode अणु
	u8	eci;
	u8	sci;
पूर्ण;

#घोषणा CP210X_PIN_MODE_MODEM		0
#घोषणा CP210X_PIN_MODE_GPIO		BIT(0)

/*
 * CP210X_VENDOR_SPECIFIC, CP210X_GET_PORTCONFIG call पढ़ोs these 0xf bytes
 * on a CP2105 chip. Structure needs padding due to unused/unspecअगरied bytes.
 */
काष्ठा cp210x_dual_port_config अणु
	__le16	gpio_mode;
	u8	__pad0[2];
	__le16	reset_state;
	u8	__pad1[4];
	__le16	suspend_state;
	u8	sci_cfg;
	u8	eci_cfg;
	u8	device_cfg;
पूर्ण __packed;

/*
 * CP210X_VENDOR_SPECIFIC, CP210X_GET_PORTCONFIG call पढ़ोs these 0xd bytes
 * on a CP2104 chip. Structure needs padding due to unused/unspecअगरied bytes.
 */
काष्ठा cp210x_single_port_config अणु
	__le16	gpio_mode;
	u8	__pad0[2];
	__le16	reset_state;
	u8	__pad1[4];
	__le16	suspend_state;
	u8	device_cfg;
पूर्ण __packed;

/* GPIO modes */
#घोषणा CP210X_SCI_GPIO_MODE_OFFSET	9
#घोषणा CP210X_SCI_GPIO_MODE_MASK	GENMASK(11, 9)

#घोषणा CP210X_ECI_GPIO_MODE_OFFSET	2
#घोषणा CP210X_ECI_GPIO_MODE_MASK	GENMASK(3, 2)

#घोषणा CP210X_GPIO_MODE_OFFSET		8
#घोषणा CP210X_GPIO_MODE_MASK		GENMASK(11, 8)

/* CP2105 port configuration values */
#घोषणा CP2105_GPIO0_TXLED_MODE		BIT(0)
#घोषणा CP2105_GPIO1_RXLED_MODE		BIT(1)
#घोषणा CP2105_GPIO1_RS485_MODE		BIT(2)

/* CP2104 port configuration values */
#घोषणा CP2104_GPIO0_TXLED_MODE		BIT(0)
#घोषणा CP2104_GPIO1_RXLED_MODE		BIT(1)
#घोषणा CP2104_GPIO2_RS485_MODE		BIT(2)

/* CP2102N configuration array indices */
#घोषणा CP210X_2NCONFIG_CONFIG_VERSION_IDX	2
#घोषणा CP210X_2NCONFIG_GPIO_MODE_IDX		581
#घोषणा CP210X_2NCONFIG_GPIO_RSTLATCH_IDX	587
#घोषणा CP210X_2NCONFIG_GPIO_CONTROL_IDX	600

/* CP2102N QFN20 port configuration values */
#घोषणा CP2102N_QFN20_GPIO2_TXLED_MODE		BIT(2)
#घोषणा CP2102N_QFN20_GPIO3_RXLED_MODE		BIT(3)
#घोषणा CP2102N_QFN20_GPIO1_RS485_MODE		BIT(4)
#घोषणा CP2102N_QFN20_GPIO0_CLK_MODE		BIT(6)

/* CP210X_VENDOR_SPECIFIC, CP210X_WRITE_LATCH call ग_लिखोs these 0x2 bytes. */
काष्ठा cp210x_gpio_ग_लिखो अणु
	u8	mask;
	u8	state;
पूर्ण;

/*
 * Helper to get पूर्णांकerface number when we only have काष्ठा usb_serial.
 */
अटल u8 cp210x_पूर्णांकerface_num(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_host_पूर्णांकerface *cur_altsetting;

	cur_altsetting = serial->पूर्णांकerface->cur_altsetting;

	वापस cur_altsetting->desc.bInterfaceNumber;
पूर्ण

/*
 * Reads a variable-sized block of CP210X_ रेजिस्टरs, identअगरied by req.
 * Returns data पूर्णांकo buf in native USB byte order.
 */
अटल पूर्णांक cp210x_पढ़ो_reg_block(काष्ठा usb_serial_port *port, u8 req,
		व्योम *buf, पूर्णांक bufsize)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	व्योम *dmabuf;
	पूर्णांक result;

	dmabuf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			req, REQTYPE_INTERFACE_TO_HOST, 0,
			port_priv->bInterfaceNumber, dmabuf, bufsize,
			USB_CTRL_SET_TIMEOUT);
	अगर (result == bufsize) अणु
		स_नकल(buf, dmabuf, bufsize);
		result = 0;
	पूर्ण अन्यथा अणु
		dev_err(&port->dev, "failed get req 0x%x size %d status: %d\n",
				req, bufsize, result);
		अगर (result >= 0)
			result = -EIO;
	पूर्ण

	kमुक्त(dmabuf);

	वापस result;
पूर्ण

/*
 * Reads any 8-bit CP210X_ रेजिस्टर identअगरied by req.
 */
अटल पूर्णांक cp210x_पढ़ो_u8_reg(काष्ठा usb_serial_port *port, u8 req, u8 *val)
अणु
	वापस cp210x_पढ़ो_reg_block(port, req, val, माप(*val));
पूर्ण

/*
 * Reads a variable-sized venकरोr block of CP210X_ रेजिस्टरs, identअगरied by val.
 * Returns data पूर्णांकo buf in native USB byte order.
 */
अटल पूर्णांक cp210x_पढ़ो_venकरोr_block(काष्ठा usb_serial *serial, u8 type, u16 val,
				    व्योम *buf, पूर्णांक bufsize)
अणु
	व्योम *dmabuf;
	पूर्णांक result;

	dmabuf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				 CP210X_VENDOR_SPECIFIC, type, val,
				 cp210x_पूर्णांकerface_num(serial), dmabuf, bufsize,
				 USB_CTRL_GET_TIMEOUT);
	अगर (result == bufsize) अणु
		स_नकल(buf, dmabuf, bufsize);
		result = 0;
	पूर्ण अन्यथा अणु
		dev_err(&serial->पूर्णांकerface->dev,
			"failed to get vendor val 0x%04x size %d: %d\n", val,
			bufsize, result);
		अगर (result >= 0)
			result = -EIO;
	पूर्ण

	kमुक्त(dmabuf);

	वापस result;
पूर्ण

/*
 * Writes any 16-bit CP210X_ रेजिस्टर (req) whose value is passed
 * entirely in the wValue field of the USB request.
 */
अटल पूर्णांक cp210x_ग_लिखो_u16_reg(काष्ठा usb_serial_port *port, u8 req, u16 val)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक result;

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			req, REQTYPE_HOST_TO_INTERFACE, val,
			port_priv->bInterfaceNumber, शून्य, 0,
			USB_CTRL_SET_TIMEOUT);
	अगर (result < 0) अणु
		dev_err(&port->dev, "failed set request 0x%x status: %d\n",
				req, result);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Writes a variable-sized block of CP210X_ रेजिस्टरs, identअगरied by req.
 * Data in buf must be in native USB byte order.
 */
अटल पूर्णांक cp210x_ग_लिखो_reg_block(काष्ठा usb_serial_port *port, u8 req,
		व्योम *buf, पूर्णांक bufsize)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	व्योम *dmabuf;
	पूर्णांक result;

	dmabuf = kmemdup(buf, bufsize, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			req, REQTYPE_HOST_TO_INTERFACE, 0,
			port_priv->bInterfaceNumber, dmabuf, bufsize,
			USB_CTRL_SET_TIMEOUT);

	kमुक्त(dmabuf);

	अगर (result < 0) अणु
		dev_err(&port->dev, "failed set req 0x%x size %d status: %d\n",
				req, bufsize, result);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Writes any 32-bit CP210X_ रेजिस्टर identअगरied by req.
 */
अटल पूर्णांक cp210x_ग_लिखो_u32_reg(काष्ठा usb_serial_port *port, u8 req, u32 val)
अणु
	__le32 le32_val;

	le32_val = cpu_to_le32(val);

	वापस cp210x_ग_लिखो_reg_block(port, req, &le32_val, माप(le32_val));
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
/*
 * Writes a variable-sized venकरोr block of CP210X_ रेजिस्टरs, identअगरied by val.
 * Data in buf must be in native USB byte order.
 */
अटल पूर्णांक cp210x_ग_लिखो_venकरोr_block(काष्ठा usb_serial *serial, u8 type,
				     u16 val, व्योम *buf, पूर्णांक bufsize)
अणु
	व्योम *dmabuf;
	पूर्णांक result;

	dmabuf = kmemdup(buf, bufsize, GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				 CP210X_VENDOR_SPECIFIC, type, val,
				 cp210x_पूर्णांकerface_num(serial), dmabuf, bufsize,
				 USB_CTRL_SET_TIMEOUT);

	kमुक्त(dmabuf);

	अगर (result < 0) अणु
		dev_err(&serial->पूर्णांकerface->dev,
			"failed to set vendor val 0x%04x size %d: %d\n", val,
			bufsize, result);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cp210x_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक result;

	result = cp210x_ग_लिखो_u16_reg(port, CP210X_IFC_ENABLE, UART_ENABLE);
	अगर (result) अणु
		dev_err(&port->dev, "%s - Unable to enable UART\n", __func__);
		वापस result;
	पूर्ण

	अगर (tty)
		cp210x_set_termios(tty, port, शून्य);

	result = usb_serial_generic_खोलो(tty, port);
	अगर (result)
		जाओ err_disable;

	वापस 0;

err_disable:
	cp210x_ग_लिखो_u16_reg(port, CP210X_IFC_ENABLE, UART_DISABLE);
	port_priv->event_mode = false;

	वापस result;
पूर्ण

अटल व्योम cp210x_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);

	usb_serial_generic_बंद(port);

	/* Clear both queues; cp2108 needs this to aव्योम an occasional hang */
	cp210x_ग_लिखो_u16_reg(port, CP210X_PURGE, PURGE_ALL);

	cp210x_ग_लिखो_u16_reg(port, CP210X_IFC_ENABLE, UART_DISABLE);

	/* Disabling the पूर्णांकerface disables event-insertion mode. */
	port_priv->event_mode = false;
पूर्ण

अटल व्योम cp210x_process_lsr(काष्ठा usb_serial_port *port, अचिन्हित अक्षर lsr, अक्षर *flag)
अणु
	अगर (lsr & CP210X_LSR_BREAK) अणु
		port->icount.brk++;
		*flag = TTY_BREAK;
	पूर्ण अन्यथा अगर (lsr & CP210X_LSR_PARITY) अणु
		port->icount.parity++;
		*flag = TTY_PARITY;
	पूर्ण अन्यथा अगर (lsr & CP210X_LSR_FRAME) अणु
		port->icount.frame++;
		*flag = TTY_FRAME;
	पूर्ण

	अगर (lsr & CP210X_LSR_OVERRUN) अणु
		port->icount.overrun++;
		tty_insert_flip_अक्षर(&port->port, 0, TTY_OVERRUN);
	पूर्ण
पूर्ण

अटल bool cp210x_process_अक्षर(काष्ठा usb_serial_port *port, अचिन्हित अक्षर *ch, अक्षर *flag)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);

	चयन (port_priv->event_state) अणु
	हाल ES_DATA:
		अगर (*ch == CP210X_ESCCHAR) अणु
			port_priv->event_state = ES_ESCAPE;
			अवरोध;
		पूर्ण
		वापस false;
	हाल ES_ESCAPE:
		चयन (*ch) अणु
		हाल 0:
			dev_dbg(&port->dev, "%s - escape char\n", __func__);
			*ch = CP210X_ESCCHAR;
			port_priv->event_state = ES_DATA;
			वापस false;
		हाल 1:
			port_priv->event_state = ES_LSR_DATA_0;
			अवरोध;
		हाल 2:
			port_priv->event_state = ES_LSR;
			अवरोध;
		हाल 3:
			port_priv->event_state = ES_MSR;
			अवरोध;
		शेष:
			dev_err(&port->dev, "malformed event 0x%02x\n", *ch);
			port_priv->event_state = ES_DATA;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ES_LSR_DATA_0:
		port_priv->lsr = *ch;
		port_priv->event_state = ES_LSR_DATA_1;
		अवरोध;
	हाल ES_LSR_DATA_1:
		dev_dbg(&port->dev, "%s - lsr = 0x%02x, data = 0x%02x\n",
				__func__, port_priv->lsr, *ch);
		cp210x_process_lsr(port, port_priv->lsr, flag);
		port_priv->event_state = ES_DATA;
		वापस false;
	हाल ES_LSR:
		dev_dbg(&port->dev, "%s - lsr = 0x%02x\n", __func__, *ch);
		port_priv->lsr = *ch;
		cp210x_process_lsr(port, port_priv->lsr, flag);
		port_priv->event_state = ES_DATA;
		अवरोध;
	हाल ES_MSR:
		dev_dbg(&port->dev, "%s - msr = 0x%02x\n", __func__, *ch);
		/* unimplemented */
		port_priv->event_state = ES_DATA;
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम cp210x_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *ch = urb->transfer_buffer;
	अक्षर flag;
	पूर्णांक i;

	अगर (!urb->actual_length)
		वापस;

	अगर (port_priv->event_mode) अणु
		क्रम (i = 0; i < urb->actual_length; i++, ch++) अणु
			flag = TTY_NORMAL;

			अगर (cp210x_process_अक्षर(port, ch, &flag))
				जारी;

			tty_insert_flip_अक्षर(&port->port, *ch, flag);
		पूर्ण
	पूर्ण अन्यथा अणु
		tty_insert_flip_string(&port->port, ch, urb->actual_length);
	पूर्ण
	tty_flip_buffer_push(&port->port);
पूर्ण

/*
 * Read how many bytes are रुकोing in the TX queue.
 */
अटल पूर्णांक cp210x_get_tx_queue_byte_count(काष्ठा usb_serial_port *port,
		u32 *count)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	काष्ठा cp210x_comm_status *sts;
	पूर्णांक result;

	sts = kदो_स्मृति(माप(*sts), GFP_KERNEL);
	अगर (!sts)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			CP210X_GET_COMM_STATUS, REQTYPE_INTERFACE_TO_HOST,
			0, port_priv->bInterfaceNumber, sts, माप(*sts),
			USB_CTRL_GET_TIMEOUT);
	अगर (result == माप(*sts)) अणु
		*count = le32_to_cpu(sts->ulAmountInOutQueue);
		result = 0;
	पूर्ण अन्यथा अणु
		dev_err(&port->dev, "failed to get comm status: %d\n", result);
		अगर (result >= 0)
			result = -EIO;
	पूर्ण

	kमुक्त(sts);

	वापस result;
पूर्ण

अटल bool cp210x_tx_empty(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक err;
	u32 count;

	err = cp210x_get_tx_queue_byte_count(port, &count);
	अगर (err)
		वापस true;

	वापस !count;
पूर्ण

काष्ठा cp210x_rate अणु
	speed_t rate;
	speed_t high;
पूर्ण;

अटल स्थिर काष्ठा cp210x_rate cp210x_an205_table1[] = अणु
	अणु 300, 300 पूर्ण,
	अणु 600, 600 पूर्ण,
	अणु 1200, 1200 पूर्ण,
	अणु 1800, 1800 पूर्ण,
	अणु 2400, 2400 पूर्ण,
	अणु 4000, 4000 पूर्ण,
	अणु 4800, 4803 पूर्ण,
	अणु 7200, 7207 पूर्ण,
	अणु 9600, 9612 पूर्ण,
	अणु 14400, 14428 पूर्ण,
	अणु 16000, 16062 पूर्ण,
	अणु 19200, 19250 पूर्ण,
	अणु 28800, 28912 पूर्ण,
	अणु 38400, 38601 पूर्ण,
	अणु 51200, 51558 पूर्ण,
	अणु 56000, 56280 पूर्ण,
	अणु 57600, 58053 पूर्ण,
	अणु 64000, 64111 पूर्ण,
	अणु 76800, 77608 पूर्ण,
	अणु 115200, 117028 पूर्ण,
	अणु 128000, 129347 पूर्ण,
	अणु 153600, 156868 पूर्ण,
	अणु 230400, 237832 पूर्ण,
	अणु 250000, 254234 पूर्ण,
	अणु 256000, 273066 पूर्ण,
	अणु 460800, 491520 पूर्ण,
	अणु 500000, 567138 पूर्ण,
	अणु 576000, 670254 पूर्ण,
	अणु 921600, अच_पूर्णांक_उच्च पूर्ण
पूर्ण;

/*
 * Quantises the baud rate as per AN205 Table 1
 */
अटल speed_t cp210x_get_an205_rate(speed_t baud)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cp210x_an205_table1); ++i) अणु
		अगर (baud <= cp210x_an205_table1[i].high)
			अवरोध;
	पूर्ण

	वापस cp210x_an205_table1[i].rate;
पूर्ण

अटल speed_t cp210x_get_actual_rate(speed_t baud)
अणु
	अचिन्हित पूर्णांक prescale = 1;
	अचिन्हित पूर्णांक भाग;

	अगर (baud <= 365)
		prescale = 4;

	भाग = DIV_ROUND_CLOSEST(48000000, 2 * prescale * baud);
	baud = 48000000 / (2 * prescale * भाग);

	वापस baud;
पूर्ण

/*
 * CP2101 supports the following baud rates:
 *
 *	300, 600, 1200, 1800, 2400, 4800, 7200, 9600, 14400, 19200, 28800,
 *	38400, 56000, 57600, 115200, 128000, 230400, 460800, 921600
 *
 * CP2102 and CP2103 support the following additional rates:
 *
 *	4000, 16000, 51200, 64000, 76800, 153600, 250000, 256000, 500000,
 *	576000
 *
 * The device will map a requested rate to a supported one, but the result
 * of requests क्रम rates greater than 1053257 is undefined (see AN205).
 *
 * CP2104, CP2105 and CP2110 support most rates up to 2M, 921k and 1M baud,
 * respectively, with an error less than 1%. The actual rates are determined
 * by
 *
 *	भाग = round(freq / (2 x prescale x request))
 *	actual = freq / (2 x prescale x भाग)
 *
 * For CP2104 and CP2105 freq is 48Mhz and prescale is 4 क्रम request <= 365bps
 * or 1 otherwise.
 * For CP2110 freq is 24Mhz and prescale is 4 क्रम request <= 300bps or 1
 * otherwise.
 */
अटल व्योम cp210x_change_speed(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	u32 baud;

	/*
	 * This maps the requested rate to the actual rate, a valid rate on
	 * cp2102 or cp2103, or to an arbitrary rate in [1M, max_speed].
	 *
	 * NOTE: B0 is not implemented.
	 */
	baud = clamp(tty->termios.c_ospeed, priv->min_speed, priv->max_speed);

	अगर (priv->use_actual_rate)
		baud = cp210x_get_actual_rate(baud);
	अन्यथा अगर (baud < 1000000)
		baud = cp210x_get_an205_rate(baud);

	dev_dbg(&port->dev, "%s - setting baud rate to %u\n", __func__, baud);
	अगर (cp210x_ग_लिखो_u32_reg(port, CP210X_SET_BAUDRATE, baud)) अणु
		dev_warn(&port->dev, "failed to set baud rate to %u\n", baud);
		अगर (old_termios)
			baud = old_termios->c_ospeed;
		अन्यथा
			baud = 9600;
	पूर्ण

	tty_encode_baud_rate(tty, baud, baud);
पूर्ण

अटल व्योम cp210x_enable_event_mode(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक ret;

	अगर (port_priv->event_mode)
		वापस;

	port_priv->event_state = ES_DATA;
	port_priv->event_mode = true;

	ret = cp210x_ग_लिखो_u16_reg(port, CP210X_EMBED_EVENTS, CP210X_ESCCHAR);
	अगर (ret) अणु
		dev_err(&port->dev, "failed to enable events: %d\n", ret);
		port_priv->event_mode = false;
	पूर्ण
पूर्ण

अटल व्योम cp210x_disable_event_mode(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	पूर्णांक ret;

	अगर (!port_priv->event_mode)
		वापस;

	ret = cp210x_ग_लिखो_u16_reg(port, CP210X_EMBED_EVENTS, 0);
	अगर (ret) अणु
		dev_err(&port->dev, "failed to disable events: %d\n", ret);
		वापस;
	पूर्ण

	port_priv->event_mode = false;
पूर्ण

अटल पूर्णांक cp210x_set_अक्षरs(काष्ठा usb_serial_port *port,
		काष्ठा cp210x_special_अक्षरs *अक्षरs)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	काष्ठा usb_serial *serial = port->serial;
	व्योम *dmabuf;
	पूर्णांक result;

	dmabuf = kmemdup(अक्षरs, माप(*अक्षरs), GFP_KERNEL);
	अगर (!dmabuf)
		वापस -ENOMEM;

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				CP210X_SET_CHARS, REQTYPE_HOST_TO_INTERFACE, 0,
				port_priv->bInterfaceNumber,
				dmabuf, माप(*अक्षरs), USB_CTRL_SET_TIMEOUT);

	kमुक्त(dmabuf);

	अगर (result < 0) अणु
		dev_err(&port->dev, "failed to set special chars: %d\n", result);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool cp210x_termios_change(स्थिर काष्ठा ktermios *a, स्थिर काष्ठा ktermios *b)
अणु
	bool अगरlag_change, cc_change;

	अगरlag_change = ((a->c_अगरlag ^ b->c_अगरlag) & (INPCK | IXON | IXOFF));
	cc_change = a->c_cc[VSTART] != b->c_cc[VSTART] ||
			a->c_cc[VSTOP] != b->c_cc[VSTOP];

	वापस tty_termios_hw_change(a, b) || अगरlag_change || cc_change;
पूर्ण

अटल व्योम cp210x_set_flow_control(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(port->serial);
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	काष्ठा cp210x_special_अक्षरs अक्षरs;
	काष्ठा cp210x_flow_ctl flow_ctl;
	u32 flow_repl;
	u32 ctl_hs;
	पूर्णांक ret;

	/*
	 * Some CP2102N पूर्णांकerpret ulXonLimit as ulFlowReplace (erratum
	 * CP2102N_E104). Report back that flow control is not supported.
	 */
	अगर (priv->no_flow_control) अणु
		tty->termios.c_cflag &= ~CRTSCTS;
		tty->termios.c_अगरlag &= ~(IXON | IXOFF);
	पूर्ण

	अगर (old_termios &&
			C_CRTSCTS(tty) == (old_termios->c_cflag & CRTSCTS) &&
			I_IXON(tty) == (old_termios->c_अगरlag & IXON) &&
			I_IXOFF(tty) == (old_termios->c_अगरlag & IXOFF) &&
			START_CHAR(tty) == old_termios->c_cc[VSTART] &&
			STOP_CHAR(tty) == old_termios->c_cc[VSTOP]) अणु
		वापस;
	पूर्ण

	अगर (I_IXON(tty) || I_IXOFF(tty)) अणु
		स_रखो(&अक्षरs, 0, माप(अक्षरs));

		अक्षरs.bXonChar = START_CHAR(tty);
		अक्षरs.bXoffChar = STOP_CHAR(tty);

		ret = cp210x_set_अक्षरs(port, &अक्षरs);
		अगर (ret)
			वापस;
	पूर्ण

	mutex_lock(&port_priv->mutex);

	ret = cp210x_पढ़ो_reg_block(port, CP210X_GET_FLOW, &flow_ctl,
			माप(flow_ctl));
	अगर (ret)
		जाओ out_unlock;

	ctl_hs = le32_to_cpu(flow_ctl.ulControlHandshake);
	flow_repl = le32_to_cpu(flow_ctl.ulFlowReplace);

	ctl_hs &= ~CP210X_SERIAL_DSR_HANDSHAKE;
	ctl_hs &= ~CP210X_SERIAL_DCD_HANDSHAKE;
	ctl_hs &= ~CP210X_SERIAL_DSR_SENSITIVITY;
	ctl_hs &= ~CP210X_SERIAL_DTR_MASK;
	अगर (port_priv->dtr)
		ctl_hs |= CP210X_SERIAL_DTR_ACTIVE;
	अन्यथा
		ctl_hs |= CP210X_SERIAL_DTR_INACTIVE;

	flow_repl &= ~CP210X_SERIAL_RTS_MASK;
	अगर (C_CRTSCTS(tty)) अणु
		ctl_hs |= CP210X_SERIAL_CTS_HANDSHAKE;
		अगर (port_priv->rts)
			flow_repl |= CP210X_SERIAL_RTS_FLOW_CTL;
		अन्यथा
			flow_repl |= CP210X_SERIAL_RTS_INACTIVE;
		port_priv->crtscts = true;
	पूर्ण अन्यथा अणु
		ctl_hs &= ~CP210X_SERIAL_CTS_HANDSHAKE;
		अगर (port_priv->rts)
			flow_repl |= CP210X_SERIAL_RTS_ACTIVE;
		अन्यथा
			flow_repl |= CP210X_SERIAL_RTS_INACTIVE;
		port_priv->crtscts = false;
	पूर्ण

	अगर (I_IXOFF(tty)) अणु
		flow_repl |= CP210X_SERIAL_AUTO_RECEIVE;

		flow_ctl.ulXonLimit = cpu_to_le32(128);
		flow_ctl.ulXoffLimit = cpu_to_le32(128);
	पूर्ण अन्यथा अणु
		flow_repl &= ~CP210X_SERIAL_AUTO_RECEIVE;
	पूर्ण

	अगर (I_IXON(tty))
		flow_repl |= CP210X_SERIAL_AUTO_TRANSMIT;
	अन्यथा
		flow_repl &= ~CP210X_SERIAL_AUTO_TRANSMIT;

	dev_dbg(&port->dev, "%s - ctrl = 0x%02x, flow = 0x%02x\n", __func__,
			ctl_hs, flow_repl);

	flow_ctl.ulControlHandshake = cpu_to_le32(ctl_hs);
	flow_ctl.ulFlowReplace = cpu_to_le32(flow_repl);

	cp210x_ग_लिखो_reg_block(port, CP210X_SET_FLOW, &flow_ctl,
			माप(flow_ctl));
out_unlock:
	mutex_unlock(&port_priv->mutex);
पूर्ण

अटल व्योम cp210x_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(port->serial);
	u16 bits;
	पूर्णांक ret;

	अगर (old_termios && !cp210x_termios_change(&tty->termios, old_termios))
		वापस;

	अगर (!old_termios || tty->termios.c_ospeed != old_termios->c_ospeed)
		cp210x_change_speed(tty, port, old_termios);

	/* CP2101 only supports CS8, 1 stop bit and non-stick parity. */
	अगर (priv->partnum == CP210X_PARTNUM_CP2101) अणु
		tty->termios.c_cflag &= ~(CSIZE | CSTOPB | CMSPAR);
		tty->termios.c_cflag |= CS8;
	पूर्ण

	bits = 0;

	चयन (C_CSIZE(tty)) अणु
	हाल CS5:
		bits |= BITS_DATA_5;
		अवरोध;
	हाल CS6:
		bits |= BITS_DATA_6;
		अवरोध;
	हाल CS7:
		bits |= BITS_DATA_7;
		अवरोध;
	हाल CS8:
	शेष:
		bits |= BITS_DATA_8;
		अवरोध;
	पूर्ण

	अगर (C_PARENB(tty)) अणु
		अगर (C_CMSPAR(tty)) अणु
			अगर (C_PARODD(tty))
				bits |= BITS_PARITY_MARK;
			अन्यथा
				bits |= BITS_PARITY_SPACE;
		पूर्ण अन्यथा अणु
			अगर (C_PARODD(tty))
				bits |= BITS_PARITY_ODD;
			अन्यथा
				bits |= BITS_PARITY_EVEN;
		पूर्ण
	पूर्ण

	अगर (C_CSTOPB(tty))
		bits |= BITS_STOP_2;
	अन्यथा
		bits |= BITS_STOP_1;

	ret = cp210x_ग_लिखो_u16_reg(port, CP210X_SET_LINE_CTL, bits);
	अगर (ret)
		dev_err(&port->dev, "failed to set line control: %d\n", ret);

	cp210x_set_flow_control(tty, port, old_termios);

	/*
	 * Enable event-insertion mode only अगर input parity checking is
	 * enabled क्रम now.
	 */
	अगर (I_INPCK(tty))
		cp210x_enable_event_mode(port);
	अन्यथा
		cp210x_disable_event_mode(port);
पूर्ण

अटल पूर्णांक cp210x_tiocmset(काष्ठा tty_काष्ठा *tty,
		अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	वापस cp210x_tiocmset_port(port, set, clear);
पूर्ण

अटल पूर्णांक cp210x_tiocmset_port(काष्ठा usb_serial_port *port,
		अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा cp210x_port_निजी *port_priv = usb_get_serial_port_data(port);
	काष्ठा cp210x_flow_ctl flow_ctl;
	u32 ctl_hs, flow_repl;
	u16 control = 0;
	पूर्णांक ret;

	mutex_lock(&port_priv->mutex);

	अगर (set & TIOCM_RTS) अणु
		port_priv->rts = true;
		control |= CONTROL_RTS;
		control |= CONTROL_WRITE_RTS;
	पूर्ण
	अगर (set & TIOCM_DTR) अणु
		port_priv->dtr = true;
		control |= CONTROL_DTR;
		control |= CONTROL_WRITE_DTR;
	पूर्ण
	अगर (clear & TIOCM_RTS) अणु
		port_priv->rts = false;
		control &= ~CONTROL_RTS;
		control |= CONTROL_WRITE_RTS;
	पूर्ण
	अगर (clear & TIOCM_DTR) अणु
		port_priv->dtr = false;
		control &= ~CONTROL_DTR;
		control |= CONTROL_WRITE_DTR;
	पूर्ण

	/*
	 * Use SET_FLOW to set DTR and enable/disable स्वतः-RTS when hardware
	 * flow control is enabled.
	 */
	अगर (port_priv->crtscts && control & CONTROL_WRITE_RTS) अणु
		ret = cp210x_पढ़ो_reg_block(port, CP210X_GET_FLOW, &flow_ctl,
				माप(flow_ctl));
		अगर (ret)
			जाओ out_unlock;

		ctl_hs = le32_to_cpu(flow_ctl.ulControlHandshake);
		flow_repl = le32_to_cpu(flow_ctl.ulFlowReplace);

		ctl_hs &= ~CP210X_SERIAL_DTR_MASK;
		अगर (port_priv->dtr)
			ctl_hs |= CP210X_SERIAL_DTR_ACTIVE;
		अन्यथा
			ctl_hs |= CP210X_SERIAL_DTR_INACTIVE;

		flow_repl &= ~CP210X_SERIAL_RTS_MASK;
		अगर (port_priv->rts)
			flow_repl |= CP210X_SERIAL_RTS_FLOW_CTL;
		अन्यथा
			flow_repl |= CP210X_SERIAL_RTS_INACTIVE;

		flow_ctl.ulControlHandshake = cpu_to_le32(ctl_hs);
		flow_ctl.ulFlowReplace = cpu_to_le32(flow_repl);

		dev_dbg(&port->dev, "%s - ctrl = 0x%02x, flow = 0x%02x\n",
				__func__, ctl_hs, flow_repl);

		ret = cp210x_ग_लिखो_reg_block(port, CP210X_SET_FLOW, &flow_ctl,
				माप(flow_ctl));
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "%s - control = 0x%04x\n", __func__, control);

		ret = cp210x_ग_लिखो_u16_reg(port, CP210X_SET_MHS, control);
	पूर्ण
out_unlock:
	mutex_unlock(&port_priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम cp210x_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on)
अणु
	अगर (on)
		cp210x_tiocmset_port(port, TIOCM_DTR | TIOCM_RTS, 0);
	अन्यथा
		cp210x_tiocmset_port(port, 0, TIOCM_DTR | TIOCM_RTS);
पूर्ण

अटल पूर्णांक cp210x_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	u8 control;
	पूर्णांक result;

	result = cp210x_पढ़ो_u8_reg(port, CP210X_GET_MDMSTS, &control);
	अगर (result)
		वापस result;

	result = ((control & CONTROL_DTR) ? TIOCM_DTR : 0)
		|((control & CONTROL_RTS) ? TIOCM_RTS : 0)
		|((control & CONTROL_CTS) ? TIOCM_CTS : 0)
		|((control & CONTROL_DSR) ? TIOCM_DSR : 0)
		|((control & CONTROL_RING)? TIOCM_RI  : 0)
		|((control & CONTROL_DCD) ? TIOCM_CD  : 0);

	dev_dbg(&port->dev, "%s - control = 0x%02x\n", __func__, control);

	वापस result;
पूर्ण

अटल व्योम cp210x_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	u16 state;

	अगर (अवरोध_state == 0)
		state = BREAK_OFF;
	अन्यथा
		state = BREAK_ON;
	dev_dbg(&port->dev, "%s - turning break %s\n", __func__,
		state == BREAK_OFF ? "off" : "on");
	cp210x_ग_लिखो_u16_reg(port, CP210X_SET_BREAK, state);
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक cp210x_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	u8 req_type = REQTYPE_DEVICE_TO_HOST;
	पूर्णांक result;
	u8 buf;

	अगर (priv->partnum == CP210X_PARTNUM_CP2105)
		req_type = REQTYPE_INTERFACE_TO_HOST;

	result = usb_स्वतःpm_get_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (result)
		वापस result;

	result = cp210x_पढ़ो_venकरोr_block(serial, req_type,
					  CP210X_READ_LATCH, &buf, माप(buf));
	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (result < 0)
		वापस result;

	वापस !!(buf & BIT(gpio));
पूर्ण

अटल व्योम cp210x_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	काष्ठा cp210x_gpio_ग_लिखो buf;
	पूर्णांक result;

	अगर (value == 1)
		buf.state = BIT(gpio);
	अन्यथा
		buf.state = 0;

	buf.mask = BIT(gpio);

	result = usb_स्वतःpm_get_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (result)
		जाओ out;

	अगर (priv->partnum == CP210X_PARTNUM_CP2105) अणु
		result = cp210x_ग_लिखो_venकरोr_block(serial,
						   REQTYPE_HOST_TO_INTERFACE,
						   CP210X_WRITE_LATCH, &buf,
						   माप(buf));
	पूर्ण अन्यथा अणु
		u16 wIndex = buf.state << 8 | buf.mask;

		result = usb_control_msg(serial->dev,
					 usb_sndctrlpipe(serial->dev, 0),
					 CP210X_VENDOR_SPECIFIC,
					 REQTYPE_HOST_TO_DEVICE,
					 CP210X_WRITE_LATCH,
					 wIndex,
					 शून्य, 0, USB_CTRL_SET_TIMEOUT);
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);
out:
	अगर (result < 0) अणु
		dev_err(&serial->पूर्णांकerface->dev, "failed to set GPIO value: %d\n",
				result);
	पूर्ण
पूर्ण

अटल पूर्णांक cp210x_gpio_direction_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);

	वापस priv->gpio_input & BIT(gpio);
पूर्ण

अटल पूर्णांक cp210x_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);

	अगर (priv->partnum == CP210X_PARTNUM_CP2105) अणु
		/* hardware करोes not support an input mode */
		वापस -ENOTSUPP;
	पूर्ण

	/* push-pull pins cannot be changed to be inमाला_दो */
	अगर (priv->gpio_pushpull & BIT(gpio))
		वापस -EINVAL;

	/* make sure to release pin अगर it is being driven low */
	cp210x_gpio_set(gc, gpio, 1);

	priv->gpio_input |= BIT(gpio);

	वापस 0;
पूर्ण

अटल पूर्णांक cp210x_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
					पूर्णांक value)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);

	priv->gpio_input &= ~BIT(gpio);
	cp210x_gpio_set(gc, gpio, value);

	वापस 0;
पूर्ण

अटल पूर्णांक cp210x_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
				  अचिन्हित दीर्घ config)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	क्रमागत pin_config_param param = pinconf_to_config_param(config);

	/* Succeed only अगर in correct mode (this can't be set at runसमय) */
	अगर ((param == PIN_CONFIG_DRIVE_PUSH_PULL) &&
	    (priv->gpio_pushpull & BIT(gpio)))
		वापस 0;

	अगर ((param == PIN_CONFIG_DRIVE_OPEN_DRAIN) &&
	    !(priv->gpio_pushpull & BIT(gpio)))
		वापस 0;

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक cp210x_gpio_init_valid_mask(काष्ठा gpio_chip *gc,
		अचिन्हित दीर्घ *valid_mask, अचिन्हित पूर्णांक ngpios)
अणु
	काष्ठा usb_serial *serial = gpiochip_get_data(gc);
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	अचिन्हित दीर्घ altfunc_mask = priv->gpio_altfunc;

	biपंचांगap_complement(valid_mask, &altfunc_mask, ngpios);

	अगर (biपंचांगap_empty(valid_mask, ngpios))
		dev_dbg(dev, "no pin configured for GPIO\n");
	अन्यथा
		dev_dbg(dev, "GPIO.%*pbl configured for GPIO\n", ngpios,
				valid_mask);
	वापस 0;
पूर्ण

/*
 * This function is क्रम configuring GPIO using shared pins, where other संकेतs
 * are made unavailable by configuring the use of GPIO. This is believed to be
 * only applicable to the cp2105 at this poपूर्णांक, the other devices supported by
 * this driver that provide GPIO करो so in a way that करोes not impact other
 * संकेतs and are thus expected to have very dअगरferent initialisation.
 */
अटल पूर्णांक cp2105_gpioconf_init(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	काष्ठा cp210x_pin_mode mode;
	काष्ठा cp210x_dual_port_config config;
	u8 पूर्णांकf_num = cp210x_पूर्णांकerface_num(serial);
	u8 अगरace_config;
	पूर्णांक result;

	result = cp210x_पढ़ो_venकरोr_block(serial, REQTYPE_DEVICE_TO_HOST,
					  CP210X_GET_DEVICEMODE, &mode,
					  माप(mode));
	अगर (result < 0)
		वापस result;

	result = cp210x_पढ़ो_venकरोr_block(serial, REQTYPE_DEVICE_TO_HOST,
					  CP210X_GET_PORTCONFIG, &config,
					  माप(config));
	अगर (result < 0)
		वापस result;

	/*  2 banks of GPIO - One क्रम the pins taken from each serial port */
	अगर (पूर्णांकf_num == 0) अणु
		अगर (mode.eci == CP210X_PIN_MODE_MODEM) अणु
			/* mark all GPIOs of this पूर्णांकerface as reserved */
			priv->gpio_altfunc = 0xff;
			वापस 0;
		पूर्ण

		अगरace_config = config.eci_cfg;
		priv->gpio_pushpull = (u8)((le16_to_cpu(config.gpio_mode) &
						CP210X_ECI_GPIO_MODE_MASK) >>
						CP210X_ECI_GPIO_MODE_OFFSET);
		priv->gc.ngpio = 2;
	पूर्ण अन्यथा अगर (पूर्णांकf_num == 1) अणु
		अगर (mode.sci == CP210X_PIN_MODE_MODEM) अणु
			/* mark all GPIOs of this पूर्णांकerface as reserved */
			priv->gpio_altfunc = 0xff;
			वापस 0;
		पूर्ण

		अगरace_config = config.sci_cfg;
		priv->gpio_pushpull = (u8)((le16_to_cpu(config.gpio_mode) &
						CP210X_SCI_GPIO_MODE_MASK) >>
						CP210X_SCI_GPIO_MODE_OFFSET);
		priv->gc.ngpio = 3;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	/* mark all pins which are not in GPIO mode */
	अगर (अगरace_config & CP2105_GPIO0_TXLED_MODE)	/* GPIO 0 */
		priv->gpio_altfunc |= BIT(0);
	अगर (अगरace_config & (CP2105_GPIO1_RXLED_MODE |	/* GPIO 1 */
			CP2105_GPIO1_RS485_MODE))
		priv->gpio_altfunc |= BIT(1);

	/* driver implementation क्रम CP2105 only supports outमाला_दो */
	priv->gpio_input = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cp2104_gpioconf_init(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	काष्ठा cp210x_single_port_config config;
	u8 अगरace_config;
	u8 gpio_latch;
	पूर्णांक result;
	u8 i;

	result = cp210x_पढ़ो_venकरोr_block(serial, REQTYPE_DEVICE_TO_HOST,
					  CP210X_GET_PORTCONFIG, &config,
					  माप(config));
	अगर (result < 0)
		वापस result;

	priv->gc.ngpio = 4;

	अगरace_config = config.device_cfg;
	priv->gpio_pushpull = (u8)((le16_to_cpu(config.gpio_mode) &
					CP210X_GPIO_MODE_MASK) >>
					CP210X_GPIO_MODE_OFFSET);
	gpio_latch = (u8)((le16_to_cpu(config.reset_state) &
					CP210X_GPIO_MODE_MASK) >>
					CP210X_GPIO_MODE_OFFSET);

	/* mark all pins which are not in GPIO mode */
	अगर (अगरace_config & CP2104_GPIO0_TXLED_MODE)	/* GPIO 0 */
		priv->gpio_altfunc |= BIT(0);
	अगर (अगरace_config & CP2104_GPIO1_RXLED_MODE)	/* GPIO 1 */
		priv->gpio_altfunc |= BIT(1);
	अगर (अगरace_config & CP2104_GPIO2_RS485_MODE)	/* GPIO 2 */
		priv->gpio_altfunc |= BIT(2);

	/*
	 * Like CP2102N, CP2104 has also no strict input and output pin
	 * modes.
	 * Do the same input mode emulation as CP2102N.
	 */
	क्रम (i = 0; i < priv->gc.ngpio; ++i) अणु
		/*
		 * Set direction to "input" अगरf pin is खोलो-drain and reset
		 * value is 1.
		 */
		अगर (!(priv->gpio_pushpull & BIT(i)) && (gpio_latch & BIT(i)))
			priv->gpio_input |= BIT(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cp2102n_gpioconf_init(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	स्थिर u16 config_size = 0x02a6;
	u8 gpio_rst_latch;
	u8 config_version;
	u8 gpio_pushpull;
	u8 *config_buf;
	u8 gpio_latch;
	u8 gpio_ctrl;
	पूर्णांक result;
	u8 i;

	/*
	 * Retrieve device configuration from the device.
	 * The array received contains all customization settings करोne at the
	 * factory/manufacturer. Format of the array is करोcumented at the
	 * समय of writing at:
	 * https://www.siद_असल.com/community/पूर्णांकerface/knowledge-base.entry.hपंचांगl/2017/03/31/cp2102n_setconfig-xsfa
	 */
	config_buf = kदो_स्मृति(config_size, GFP_KERNEL);
	अगर (!config_buf)
		वापस -ENOMEM;

	result = cp210x_पढ़ो_venकरोr_block(serial,
					  REQTYPE_DEVICE_TO_HOST,
					  CP210X_READ_2NCONFIG,
					  config_buf,
					  config_size);
	अगर (result < 0) अणु
		kमुक्त(config_buf);
		वापस result;
	पूर्ण

	config_version = config_buf[CP210X_2NCONFIG_CONFIG_VERSION_IDX];
	gpio_pushpull = config_buf[CP210X_2NCONFIG_GPIO_MODE_IDX];
	gpio_ctrl = config_buf[CP210X_2NCONFIG_GPIO_CONTROL_IDX];
	gpio_rst_latch = config_buf[CP210X_2NCONFIG_GPIO_RSTLATCH_IDX];

	kमुक्त(config_buf);

	/* Make sure this is a config क्रमmat we understand. */
	अगर (config_version != 0x01)
		वापस -ENOTSUPP;

	priv->gc.ngpio = 4;

	/*
	 * Get शेष pin states after reset. Needed so we can determine
	 * the direction of an खोलो-drain pin.
	 */
	gpio_latch = (gpio_rst_latch >> 3) & 0x0f;

	/* 0 indicates खोलो-drain mode, 1 is push-pull */
	priv->gpio_pushpull = (gpio_pushpull >> 3) & 0x0f;

	/* 0 indicates GPIO mode, 1 is alternate function */
	अगर (priv->partnum == CP210X_PARTNUM_CP2102N_QFN20) अणु
		/* QFN20 is special... */
		अगर (gpio_ctrl & CP2102N_QFN20_GPIO0_CLK_MODE)   /* GPIO 0 */
			priv->gpio_altfunc |= BIT(0);
		अगर (gpio_ctrl & CP2102N_QFN20_GPIO1_RS485_MODE) /* GPIO 1 */
			priv->gpio_altfunc |= BIT(1);
		अगर (gpio_ctrl & CP2102N_QFN20_GPIO2_TXLED_MODE) /* GPIO 2 */
			priv->gpio_altfunc |= BIT(2);
		अगर (gpio_ctrl & CP2102N_QFN20_GPIO3_RXLED_MODE) /* GPIO 3 */
			priv->gpio_altfunc |= BIT(3);
	पूर्ण अन्यथा अणु
		priv->gpio_altfunc = (gpio_ctrl >> 2) & 0x0f;
	पूर्ण

	अगर (priv->partnum == CP210X_PARTNUM_CP2102N_QFN28) अणु
		/*
		 * For the QFN28 package, GPIO4-6 are controlled by
		 * the low three bits of the mode/latch fields.
		 * Contrary to the करोcument linked above, the bits क्रम
		 * the SUSPEND pins are अन्यथाwhere.  No alternate
		 * function is available क्रम these pins.
		 */
		priv->gc.ngpio = 7;
		gpio_latch |= (gpio_rst_latch & 7) << 4;
		priv->gpio_pushpull |= (gpio_pushpull & 7) << 4;
	पूर्ण

	/*
	 * The CP2102N करोes not strictly has input and output pin modes,
	 * it only knows खोलो-drain and push-pull modes which is set at
	 * factory. An खोलो-drain pin can function both as an
	 * input or an output. We emulate input mode क्रम खोलो-drain pins
	 * by making sure they are not driven low, and we करो not allow
	 * push-pull pins to be set as an input.
	 */
	क्रम (i = 0; i < priv->gc.ngpio; ++i) अणु
		/*
		 * Set direction to "input" अगरf pin is खोलो-drain and reset
		 * value is 1.
		 */
		अगर (!(priv->gpio_pushpull & BIT(i)) && (gpio_latch & BIT(i)))
			priv->gpio_input |= BIT(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cp210x_gpio_init(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	पूर्णांक result;

	चयन (priv->partnum) अणु
	हाल CP210X_PARTNUM_CP2104:
		result = cp2104_gpioconf_init(serial);
		अवरोध;
	हाल CP210X_PARTNUM_CP2105:
		result = cp2105_gpioconf_init(serial);
		अवरोध;
	हाल CP210X_PARTNUM_CP2102N_QFN28:
	हाल CP210X_PARTNUM_CP2102N_QFN24:
	हाल CP210X_PARTNUM_CP2102N_QFN20:
		result = cp2102n_gpioconf_init(serial);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (result < 0)
		वापस result;

	priv->gc.label = "cp210x";
	priv->gc.get_direction = cp210x_gpio_direction_get;
	priv->gc.direction_input = cp210x_gpio_direction_input;
	priv->gc.direction_output = cp210x_gpio_direction_output;
	priv->gc.get = cp210x_gpio_get;
	priv->gc.set = cp210x_gpio_set;
	priv->gc.set_config = cp210x_gpio_set_config;
	priv->gc.init_valid_mask = cp210x_gpio_init_valid_mask;
	priv->gc.owner = THIS_MODULE;
	priv->gc.parent = &serial->पूर्णांकerface->dev;
	priv->gc.base = -1;
	priv->gc.can_sleep = true;

	result = gpiochip_add_data(&priv->gc, serial);
	अगर (!result)
		priv->gpio_रेजिस्टरed = true;

	वापस result;
पूर्ण

अटल व्योम cp210x_gpio_हटाओ(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);

	अगर (priv->gpio_रेजिस्टरed) अणु
		gpiochip_हटाओ(&priv->gc);
		priv->gpio_रेजिस्टरed = false;
	पूर्ण
पूर्ण

#अन्यथा

अटल पूर्णांक cp210x_gpio_init(काष्ठा usb_serial *serial)
अणु
	वापस 0;
पूर्ण

अटल व्योम cp210x_gpio_हटाओ(काष्ठा usb_serial *serial)
अणु
	/* Nothing to करो */
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक cp210x_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा cp210x_port_निजी *port_priv;

	port_priv = kzalloc(माप(*port_priv), GFP_KERNEL);
	अगर (!port_priv)
		वापस -ENOMEM;

	port_priv->bInterfaceNumber = cp210x_पूर्णांकerface_num(serial);
	mutex_init(&port_priv->mutex);

	usb_set_serial_port_data(port, port_priv);

	वापस 0;
पूर्ण

अटल व्योम cp210x_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा cp210x_port_निजी *port_priv;

	port_priv = usb_get_serial_port_data(port);
	kमुक्त(port_priv);
पूर्ण

अटल व्योम cp210x_init_max_speed(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	bool use_actual_rate = false;
	speed_t min = 300;
	speed_t max;

	चयन (priv->partnum) अणु
	हाल CP210X_PARTNUM_CP2101:
		max = 921600;
		अवरोध;
	हाल CP210X_PARTNUM_CP2102:
	हाल CP210X_PARTNUM_CP2103:
		max = 1000000;
		अवरोध;
	हाल CP210X_PARTNUM_CP2104:
		use_actual_rate = true;
		max = 2000000;
		अवरोध;
	हाल CP210X_PARTNUM_CP2108:
		max = 2000000;
		अवरोध;
	हाल CP210X_PARTNUM_CP2105:
		अगर (cp210x_पूर्णांकerface_num(serial) == 0) अणु
			use_actual_rate = true;
			max = 2000000;	/* ECI */
		पूर्ण अन्यथा अणु
			min = 2400;
			max = 921600;	/* SCI */
		पूर्ण
		अवरोध;
	हाल CP210X_PARTNUM_CP2102N_QFN28:
	हाल CP210X_PARTNUM_CP2102N_QFN24:
	हाल CP210X_PARTNUM_CP2102N_QFN20:
		use_actual_rate = true;
		max = 3000000;
		अवरोध;
	शेष:
		max = 2000000;
		अवरोध;
	पूर्ण

	priv->min_speed = min;
	priv->max_speed = max;
	priv->use_actual_rate = use_actual_rate;
पूर्ण

अटल पूर्णांक cp210x_get_fw_version(काष्ठा usb_serial *serial, u16 value)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	u8 ver[3];
	पूर्णांक ret;

	ret = cp210x_पढ़ो_venकरोr_block(serial, REQTYPE_DEVICE_TO_HOST, value,
			ver, माप(ver));
	अगर (ret)
		वापस ret;

	dev_dbg(&serial->पूर्णांकerface->dev, "%s - %d.%d.%d\n", __func__,
			ver[0], ver[1], ver[2]);

	priv->fw_version = ver[0] << 16 | ver[1] << 8 | ver[2];

	वापस 0;
पूर्ण

अटल व्योम cp210x_determine_quirks(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);
	पूर्णांक ret;

	चयन (priv->partnum) अणु
	हाल CP210X_PARTNUM_CP2102N_QFN28:
	हाल CP210X_PARTNUM_CP2102N_QFN24:
	हाल CP210X_PARTNUM_CP2102N_QFN20:
		ret = cp210x_get_fw_version(serial, CP210X_GET_FW_VER_2N);
		अगर (ret)
			अवरोध;
		अगर (priv->fw_version <= 0x10004)
			priv->no_flow_control = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cp210x_attach(काष्ठा usb_serial *serial)
अणु
	पूर्णांक result;
	काष्ठा cp210x_serial_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	result = cp210x_पढ़ो_venकरोr_block(serial, REQTYPE_DEVICE_TO_HOST,
					  CP210X_GET_PARTNUM, &priv->partnum,
					  माप(priv->partnum));
	अगर (result < 0) अणु
		dev_warn(&serial->पूर्णांकerface->dev,
			 "querying part number failed\n");
		priv->partnum = CP210X_PARTNUM_UNKNOWN;
	पूर्ण

	usb_set_serial_data(serial, priv);

	cp210x_determine_quirks(serial);
	cp210x_init_max_speed(serial);

	result = cp210x_gpio_init(serial);
	अगर (result < 0) अणु
		dev_err(&serial->पूर्णांकerface->dev, "GPIO initialisation failed: %d\n",
				result);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cp210x_disconnect(काष्ठा usb_serial *serial)
अणु
	cp210x_gpio_हटाओ(serial);
पूर्ण

अटल व्योम cp210x_release(काष्ठा usb_serial *serial)
अणु
	काष्ठा cp210x_serial_निजी *priv = usb_get_serial_data(serial);

	cp210x_gpio_हटाओ(serial);

	kमुक्त(priv);
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
