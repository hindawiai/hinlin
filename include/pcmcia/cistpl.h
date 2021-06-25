<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cistpl.h
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999             David A. Hinds
 */

#अगर_अघोषित _LINUX_CISTPL_H
#घोषणा _LINUX_CISTPL_H

प्रकार अचिन्हित अक्षर cisdata_t;

#घोषणा CISTPL_शून्य		0x00
#घोषणा CISTPL_DEVICE		0x01
#घोषणा CISTPL_LONGLINK_CB	0x02
#घोषणा CISTPL_INसूचीECT		0x03
#घोषणा CISTPL_CONFIG_CB	0x04
#घोषणा CISTPL_CFTABLE_ENTRY_CB	0x05
#घोषणा CISTPL_LONGLINK_MFC	0x06
#घोषणा CISTPL_BAR		0x07
#घोषणा CISTPL_PWR_MGMNT	0x08
#घोषणा CISTPL_EXTDEVICE	0x09
#घोषणा CISTPL_CHECKSUM		0x10
#घोषणा CISTPL_LONGLINK_A	0x11
#घोषणा CISTPL_LONGLINK_C	0x12
#घोषणा CISTPL_LINKTARGET	0x13
#घोषणा CISTPL_NO_LINK		0x14
#घोषणा CISTPL_VERS_1		0x15
#घोषणा CISTPL_ALTSTR		0x16
#घोषणा CISTPL_DEVICE_A		0x17
#घोषणा CISTPL_JEDEC_C		0x18
#घोषणा CISTPL_JEDEC_A		0x19
#घोषणा CISTPL_CONFIG		0x1a
#घोषणा CISTPL_CFTABLE_ENTRY	0x1b
#घोषणा CISTPL_DEVICE_OC	0x1c
#घोषणा CISTPL_DEVICE_OA	0x1d
#घोषणा CISTPL_DEVICE_GEO	0x1e
#घोषणा CISTPL_DEVICE_GEO_A	0x1f
#घोषणा CISTPL_MANFID		0x20
#घोषणा CISTPL_FUNCID		0x21
#घोषणा CISTPL_FUNCE		0x22
#घोषणा CISTPL_SWIL		0x23
#घोषणा CISTPL_END		0xff
/* Layer 2 tuples */
#घोषणा CISTPL_VERS_2		0x40
#घोषणा CISTPL_FORMAT		0x41
#घोषणा CISTPL_GEOMETRY		0x42
#घोषणा CISTPL_BYTEORDER	0x43
#घोषणा CISTPL_DATE		0x44
#घोषणा CISTPL_BATTERY		0x45
#घोषणा CISTPL_FORMAT_A		0x47
/* Layer 3 tuples */
#घोषणा CISTPL_ORG		0x46
#घोषणा CISTPL_SPCL		0x90

प्रकार काष्ठा cistpl_दीर्घlink_t अणु
    u_पूर्णांक	addr;
पूर्ण cistpl_दीर्घlink_t;

प्रकार काष्ठा cistpl_checksum_t अणु
    u_लघु	addr;
    u_लघु	len;
    u_अक्षर	sum;
पूर्ण cistpl_checksum_t;

#घोषणा CISTPL_MAX_FUNCTIONS	8
#घोषणा CISTPL_MFC_ATTR		0x00
#घोषणा CISTPL_MFC_COMMON	0x01

प्रकार काष्ठा cistpl_दीर्घlink_mfc_t अणु
    u_अक्षर	nfn;
    काष्ठा अणु
	u_अक्षर	space;
	u_पूर्णांक	addr;
    पूर्ण fn[CISTPL_MAX_FUNCTIONS];
पूर्ण cistpl_दीर्घlink_mfc_t;

#घोषणा CISTPL_MAX_ALTSTR_STRINGS	4

प्रकार काष्ठा cistpl_altstr_t अणु
    u_अक्षर	ns;
    u_अक्षर	ofs[CISTPL_MAX_ALTSTR_STRINGS];
    अक्षर	str[254];
पूर्ण cistpl_altstr_t;

#घोषणा CISTPL_DTYPE_शून्य	0x00
#घोषणा CISTPL_DTYPE_ROM	0x01
#घोषणा CISTPL_DTYPE_OTPROM	0x02
#घोषणा CISTPL_DTYPE_EPROM	0x03
#घोषणा CISTPL_DTYPE_EEPROM	0x04
#घोषणा CISTPL_DTYPE_FLASH	0x05
#घोषणा CISTPL_DTYPE_SRAM	0x06
#घोषणा CISTPL_DTYPE_DRAM	0x07
#घोषणा CISTPL_DTYPE_FUNCSPEC	0x0d
#घोषणा CISTPL_DTYPE_EXTEND	0x0e

#घोषणा CISTPL_MAX_DEVICES	4

प्रकार काष्ठा cistpl_device_t अणु
    u_अक्षर	ndev;
    काष्ठा अणु
	u_अक्षर 	type;
	u_अक्षर	wp;
	u_पूर्णांक	speed;
	u_पूर्णांक	size;
    पूर्ण dev[CISTPL_MAX_DEVICES];
पूर्ण cistpl_device_t;

#घोषणा CISTPL_DEVICE_MWAIT	0x01
#घोषणा CISTPL_DEVICE_3VCC	0x02

प्रकार काष्ठा cistpl_device_o_t अणु
    u_अक्षर		flags;
    cistpl_device_t	device;
पूर्ण cistpl_device_o_t;

#घोषणा CISTPL_VERS_1_MAX_PROD_STRINGS	4

प्रकार काष्ठा cistpl_vers_1_t अणु
    u_अक्षर	major;
    u_अक्षर	minor;
    u_अक्षर	ns;
    u_अक्षर	ofs[CISTPL_VERS_1_MAX_PROD_STRINGS];
    अक्षर	str[254];
पूर्ण cistpl_vers_1_t;

प्रकार काष्ठा cistpl_jedec_t अणु
    u_अक्षर	nid;
    काष्ठा अणु
	u_अक्षर	mfr;
	u_अक्षर	info;
    पूर्ण id[CISTPL_MAX_DEVICES];
पूर्ण cistpl_jedec_t;

प्रकार काष्ठा cistpl_manfid_t अणु
    u_लघु	manf;
    u_लघु	card;
पूर्ण cistpl_manfid_t;

#घोषणा CISTPL_FUNCID_MULTI	0x00
#घोषणा CISTPL_FUNCID_MEMORY	0x01
#घोषणा CISTPL_FUNCID_SERIAL	0x02
#घोषणा CISTPL_FUNCID_PARALLEL	0x03
#घोषणा CISTPL_FUNCID_FIXED	0x04
#घोषणा CISTPL_FUNCID_VIDEO	0x05
#घोषणा CISTPL_FUNCID_NETWORK	0x06
#घोषणा CISTPL_FUNCID_AIMS	0x07
#घोषणा CISTPL_FUNCID_SCSI	0x08

#घोषणा CISTPL_SYSINIT_POST	0x01
#घोषणा CISTPL_SYSINIT_ROM	0x02

प्रकार काष्ठा cistpl_funcid_t अणु
    u_अक्षर	func;
    u_अक्षर	sysinit;
पूर्ण cistpl_funcid_t;

प्रकार काष्ठा cistpl_funce_t अणु
    u_अक्षर	type;
    u_अक्षर	data[];
पूर्ण cistpl_funce_t;

/*======================================================================

    Modem Function Extension Tuples

======================================================================*/

#घोषणा CISTPL_FUNCE_SERIAL_IF		0x00
#घोषणा CISTPL_FUNCE_SERIAL_CAP		0x01
#घोषणा CISTPL_FUNCE_SERIAL_SERV_DATA	0x02
#घोषणा CISTPL_FUNCE_SERIAL_SERV_FAX	0x03
#घोषणा CISTPL_FUNCE_SERIAL_SERV_VOICE	0x04
#घोषणा CISTPL_FUNCE_SERIAL_CAP_DATA	0x05
#घोषणा CISTPL_FUNCE_SERIAL_CAP_FAX	0x06
#घोषणा CISTPL_FUNCE_SERIAL_CAP_VOICE	0x07
#घोषणा CISTPL_FUNCE_SERIAL_IF_DATA	0x08
#घोषणा CISTPL_FUNCE_SERIAL_IF_FAX	0x09
#घोषणा CISTPL_FUNCE_SERIAL_IF_VOICE	0x0a

/* UART identअगरication */
#घोषणा CISTPL_SERIAL_UART_8250		0x00
#घोषणा CISTPL_SERIAL_UART_16450	0x01
#घोषणा CISTPL_SERIAL_UART_16550	0x02
#घोषणा CISTPL_SERIAL_UART_8251		0x03
#घोषणा CISTPL_SERIAL_UART_8530		0x04
#घोषणा CISTPL_SERIAL_UART_85230	0x05

/* UART capabilities */
#घोषणा CISTPL_SERIAL_UART_SPACE	0x01
#घोषणा CISTPL_SERIAL_UART_MARK		0x02
#घोषणा CISTPL_SERIAL_UART_ODD		0x04
#घोषणा CISTPL_SERIAL_UART_EVEN		0x08
#घोषणा CISTPL_SERIAL_UART_5BIT		0x01
#घोषणा CISTPL_SERIAL_UART_6BIT		0x02
#घोषणा CISTPL_SERIAL_UART_7BIT		0x04
#घोषणा CISTPL_SERIAL_UART_8BIT		0x08
#घोषणा CISTPL_SERIAL_UART_1STOP	0x10
#घोषणा CISTPL_SERIAL_UART_MSTOP	0x20
#घोषणा CISTPL_SERIAL_UART_2STOP	0x40

प्रकार काष्ठा cistpl_serial_t अणु
    u_अक्षर	uart_type;
    u_अक्षर	uart_cap_0;
    u_अक्षर	uart_cap_1;
पूर्ण cistpl_serial_t;

प्रकार काष्ठा cistpl_modem_cap_t अणु
    u_अक्षर	flow;
    u_अक्षर	cmd_buf;
    u_अक्षर	rcv_buf_0, rcv_buf_1, rcv_buf_2;
    u_अक्षर	xmit_buf_0, xmit_buf_1, xmit_buf_2;
पूर्ण cistpl_modem_cap_t;

#घोषणा CISTPL_SERIAL_MOD_103		0x01
#घोषणा CISTPL_SERIAL_MOD_V21		0x02
#घोषणा CISTPL_SERIAL_MOD_V23		0x04
#घोषणा CISTPL_SERIAL_MOD_V22		0x08
#घोषणा CISTPL_SERIAL_MOD_212A		0x10
#घोषणा CISTPL_SERIAL_MOD_V22BIS	0x20
#घोषणा CISTPL_SERIAL_MOD_V26		0x40
#घोषणा CISTPL_SERIAL_MOD_V26BIS	0x80
#घोषणा CISTPL_SERIAL_MOD_V27BIS	0x01
#घोषणा CISTPL_SERIAL_MOD_V29		0x02
#घोषणा CISTPL_SERIAL_MOD_V32		0x04
#घोषणा CISTPL_SERIAL_MOD_V32BIS	0x08
#घोषणा CISTPL_SERIAL_MOD_V34		0x10

#घोषणा CISTPL_SERIAL_ERR_MNP2_4	0x01
#घोषणा CISTPL_SERIAL_ERR_V42_LAPM	0x02

#घोषणा CISTPL_SERIAL_CMPR_V42BIS	0x01
#घोषणा CISTPL_SERIAL_CMPR_MNP5		0x02

#घोषणा CISTPL_SERIAL_CMD_AT1		0x01
#घोषणा CISTPL_SERIAL_CMD_AT2		0x02
#घोषणा CISTPL_SERIAL_CMD_AT3		0x04
#घोषणा CISTPL_SERIAL_CMD_MNP_AT	0x08
#घोषणा CISTPL_SERIAL_CMD_V25BIS	0x10
#घोषणा CISTPL_SERIAL_CMD_V25A		0x20
#घोषणा CISTPL_SERIAL_CMD_DMCL		0x40

प्रकार काष्ठा cistpl_data_serv_t अणु
    u_अक्षर	max_data_0;
    u_अक्षर	max_data_1;
    u_अक्षर	modulation_0;
    u_अक्षर	modulation_1;
    u_अक्षर	error_control;
    u_अक्षर	compression;
    u_अक्षर	cmd_protocol;
    u_अक्षर	escape;
    u_अक्षर	encrypt;
    u_अक्षर	misc_features;
    u_अक्षर	ccitt_code[];
पूर्ण cistpl_data_serv_t;

प्रकार काष्ठा cistpl_fax_serv_t अणु
    u_अक्षर	max_data_0;
    u_अक्षर	max_data_1;
    u_अक्षर	modulation;
    u_अक्षर	encrypt;
    u_अक्षर	features_0;
    u_अक्षर	features_1;
    u_अक्षर	ccitt_code[];
पूर्ण cistpl_fax_serv_t;

प्रकार काष्ठा cistpl_voice_serv_t अणु
    u_अक्षर	max_data_0;
    u_अक्षर	max_data_1;
पूर्ण cistpl_voice_serv_t;

/*======================================================================

    LAN Function Extension Tuples

======================================================================*/

#घोषणा CISTPL_FUNCE_LAN_TECH		0x01
#घोषणा CISTPL_FUNCE_LAN_SPEED		0x02
#घोषणा CISTPL_FUNCE_LAN_MEDIA		0x03
#घोषणा CISTPL_FUNCE_LAN_NODE_ID	0x04
#घोषणा CISTPL_FUNCE_LAN_CONNECTOR	0x05

/* LAN technologies */
#घोषणा CISTPL_LAN_TECH_ARCNET		0x01
#घोषणा CISTPL_LAN_TECH_ETHERNET	0x02
#घोषणा CISTPL_LAN_TECH_TOKENRING	0x03
#घोषणा CISTPL_LAN_TECH_LOCALTALK	0x04
#घोषणा CISTPL_LAN_TECH_FDDI		0x05
#घोषणा CISTPL_LAN_TECH_ATM		0x06
#घोषणा CISTPL_LAN_TECH_WIRELESS	0x07

प्रकार काष्ठा cistpl_lan_tech_t अणु
    u_अक्षर	tech;
पूर्ण cistpl_lan_tech_t;

प्रकार काष्ठा cistpl_lan_speed_t अणु
    u_पूर्णांक	speed;
पूर्ण cistpl_lan_speed_t;

/* LAN media definitions */
#घोषणा CISTPL_LAN_MEDIA_UTP		0x01
#घोषणा CISTPL_LAN_MEDIA_STP		0x02
#घोषणा CISTPL_LAN_MEDIA_THIN_COAX	0x03
#घोषणा CISTPL_LAN_MEDIA_THICK_COAX	0x04
#घोषणा CISTPL_LAN_MEDIA_FIBER		0x05
#घोषणा CISTPL_LAN_MEDIA_900MHZ		0x06
#घोषणा CISTPL_LAN_MEDIA_2GHZ		0x07
#घोषणा CISTPL_LAN_MEDIA_5GHZ		0x08
#घोषणा CISTPL_LAN_MEDIA_DIFF_IR	0x09
#घोषणा CISTPL_LAN_MEDIA_PTP_IR		0x0a

प्रकार काष्ठा cistpl_lan_media_t अणु
    u_अक्षर	media;
पूर्ण cistpl_lan_media_t;

प्रकार काष्ठा cistpl_lan_node_id_t अणु
    u_अक्षर	nb;
    u_अक्षर	id[16];
पूर्ण cistpl_lan_node_id_t;

प्रकार काष्ठा cistpl_lan_connector_t अणु
    u_अक्षर	code;
पूर्ण cistpl_lan_connector_t;

/*======================================================================

    IDE Function Extension Tuples

======================================================================*/

#घोषणा CISTPL_IDE_INTERFACE		0x01

प्रकार काष्ठा cistpl_ide_पूर्णांकerface_t अणु
    u_अक्षर	पूर्णांकerface;
पूर्ण cistpl_ide_पूर्णांकerface_t;

/* First feature byte */
#घोषणा CISTPL_IDE_SILICON		0x04
#घोषणा CISTPL_IDE_UNIQUE		0x08
#घोषणा CISTPL_IDE_DUAL			0x10

/* Second feature byte */
#घोषणा CISTPL_IDE_HAS_SLEEP		0x01
#घोषणा CISTPL_IDE_HAS_STANDBY		0x02
#घोषणा CISTPL_IDE_HAS_IDLE		0x04
#घोषणा CISTPL_IDE_LOW_POWER		0x08
#घोषणा CISTPL_IDE_REG_INHIBIT		0x10
#घोषणा CISTPL_IDE_HAS_INDEX		0x20
#घोषणा CISTPL_IDE_IOIS16		0x40

प्रकार काष्ठा cistpl_ide_feature_t अणु
    u_अक्षर	feature1;
    u_अक्षर	feature2;
पूर्ण cistpl_ide_feature_t;

#घोषणा CISTPL_FUNCE_IDE_IFACE		0x01
#घोषणा CISTPL_FUNCE_IDE_MASTER		0x02
#घोषणा CISTPL_FUNCE_IDE_SLAVE		0x03

/*======================================================================

    Configuration Table Entries

======================================================================*/

#घोषणा CISTPL_BAR_SPACE	0x07
#घोषणा CISTPL_BAR_SPACE_IO	0x10
#घोषणा CISTPL_BAR_PREFETCH	0x20
#घोषणा CISTPL_BAR_CACHEABLE	0x40
#घोषणा CISTPL_BAR_1MEG_MAP	0x80

प्रकार काष्ठा cistpl_bar_t अणु
    u_अक्षर	attr;
    u_पूर्णांक	size;
पूर्ण cistpl_bar_t;

प्रकार काष्ठा cistpl_config_t अणु
    u_अक्षर	last_idx;
    u_पूर्णांक	base;
    u_पूर्णांक	rmask[4];
    u_अक्षर	subtuples;
पूर्ण cistpl_config_t;

/* These are bits in the 'present' field, and indices in 'param' */
#घोषणा CISTPL_POWER_VNOM	0
#घोषणा CISTPL_POWER_VMIN	1
#घोषणा CISTPL_POWER_VMAX	2
#घोषणा CISTPL_POWER_ISTATIC	3
#घोषणा CISTPL_POWER_IAVG	4
#घोषणा CISTPL_POWER_IPEAK	5
#घोषणा CISTPL_POWER_IDOWN	6

#घोषणा CISTPL_POWER_HIGHZ_OK	0x01
#घोषणा CISTPL_POWER_HIGHZ_REQ	0x02

प्रकार काष्ठा cistpl_घातer_t अणु
    u_अक्षर	present;
    u_अक्षर	flags;
    u_पूर्णांक	param[7];
पूर्ण cistpl_घातer_t;

प्रकार काष्ठा cistpl_timing_t अणु
    u_पूर्णांक	रुको, रुकोscale;
    u_पूर्णांक	पढ़ोy, rdyscale;
    u_पूर्णांक	reserved, rsvscale;
पूर्ण cistpl_timing_t;

#घोषणा CISTPL_IO_LINES_MASK	0x1f
#घोषणा CISTPL_IO_8BIT		0x20
#घोषणा CISTPL_IO_16BIT		0x40
#घोषणा CISTPL_IO_RANGE		0x80

#घोषणा CISTPL_IO_MAX_WIN	16

प्रकार काष्ठा cistpl_io_t अणु
    u_अक्षर	flags;
    u_अक्षर	nwin;
    काष्ठा अणु
	u_पूर्णांक	base;
	u_पूर्णांक	len;
    पूर्ण win[CISTPL_IO_MAX_WIN];
पूर्ण cistpl_io_t;

प्रकार काष्ठा cistpl_irq_t अणु
    u_पूर्णांक	IRQInfo1;
    u_पूर्णांक	IRQInfo2;
पूर्ण cistpl_irq_t;

#घोषणा CISTPL_MEM_MAX_WIN	8

प्रकार काष्ठा cistpl_mem_t अणु
    u_अक्षर	flags;
    u_अक्षर	nwin;
    काष्ठा अणु
	u_पूर्णांक	len;
	u_पूर्णांक	card_addr;
	u_पूर्णांक	host_addr;
    पूर्ण win[CISTPL_MEM_MAX_WIN];
पूर्ण cistpl_mem_t;

#घोषणा CISTPL_CFTABLE_DEFAULT		0x0001
#घोषणा CISTPL_CFTABLE_BVDS		0x0002
#घोषणा CISTPL_CFTABLE_WP		0x0004
#घोषणा CISTPL_CFTABLE_RDYBSY		0x0008
#घोषणा CISTPL_CFTABLE_MWAIT		0x0010
#घोषणा CISTPL_CFTABLE_AUDIO		0x0800
#घोषणा CISTPL_CFTABLE_READONLY		0x1000
#घोषणा CISTPL_CFTABLE_PWRDOWN		0x2000

प्रकार काष्ठा cistpl_cftable_entry_t अणु
    u_अक्षर		index;
    u_लघु		flags;
    u_अक्षर		पूर्णांकerface;
    cistpl_घातer_t	vcc, vpp1, vpp2;
    cistpl_timing_t	timing;
    cistpl_io_t		io;
    cistpl_irq_t	irq;
    cistpl_mem_t	mem;
    u_अक्षर		subtuples;
पूर्ण cistpl_cftable_entry_t;

#घोषणा CISTPL_CFTABLE_MASTER		0x000100
#घोषणा CISTPL_CFTABLE_INVALIDATE	0x000200
#घोषणा CISTPL_CFTABLE_VGA_PALETTE	0x000400
#घोषणा CISTPL_CFTABLE_PARITY		0x000800
#घोषणा CISTPL_CFTABLE_WAIT		0x001000
#घोषणा CISTPL_CFTABLE_SERR		0x002000
#घोषणा CISTPL_CFTABLE_FAST_BACK	0x004000
#घोषणा CISTPL_CFTABLE_BINARY_AUDIO	0x010000
#घोषणा CISTPL_CFTABLE_PWM_AUDIO	0x020000

प्रकार काष्ठा cistpl_cftable_entry_cb_t अणु
    u_अक्षर		index;
    u_पूर्णांक		flags;
    cistpl_घातer_t	vcc, vpp1, vpp2;
    u_अक्षर		io;
    cistpl_irq_t	irq;
    u_अक्षर		mem;
    u_अक्षर		subtuples;
पूर्ण cistpl_cftable_entry_cb_t;

प्रकार काष्ठा cistpl_device_geo_t अणु
    u_अक्षर		ngeo;
    काष्ठा अणु
	u_अक्षर		buswidth;
	u_पूर्णांक		erase_block;
	u_पूर्णांक		पढ़ो_block;
	u_पूर्णांक		ग_लिखो_block;
	u_पूर्णांक		partition;
	u_पूर्णांक		पूर्णांकerleave;
    पूर्ण geo[CISTPL_MAX_DEVICES];
पूर्ण cistpl_device_geo_t;

प्रकार काष्ठा cistpl_vers_2_t अणु
    u_अक्षर	vers;
    u_अक्षर	comply;
    u_लघु	dindex;
    u_अक्षर	vspec8, vspec9;
    u_अक्षर	nhdr;
    u_अक्षर	venकरोr, info;
    अक्षर	str[244];
पूर्ण cistpl_vers_2_t;

प्रकार काष्ठा cistpl_org_t अणु
    u_अक्षर	data_org;
    अक्षर	desc[30];
पूर्ण cistpl_org_t;

#घोषणा CISTPL_ORG_FS		0x00
#घोषणा CISTPL_ORG_APPSPEC	0x01
#घोषणा CISTPL_ORG_XIP		0x02

प्रकार काष्ठा cistpl_क्रमmat_t अणु
    u_अक्षर	type;
    u_अक्षर	edc;
    u_पूर्णांक	offset;
    u_पूर्णांक	length;
पूर्ण cistpl_क्रमmat_t;

#घोषणा CISTPL_FORMAT_DISK	0x00
#घोषणा CISTPL_FORMAT_MEM	0x01

#घोषणा CISTPL_EDC_NONE		0x00
#घोषणा CISTPL_EDC_CKSUM	0x01
#घोषणा CISTPL_EDC_CRC		0x02
#घोषणा CISTPL_EDC_PCC		0x03

प्रकार जोड़ cisparse_t अणु
    cistpl_device_t		device;
    cistpl_checksum_t		checksum;
    cistpl_दीर्घlink_t		दीर्घlink;
    cistpl_दीर्घlink_mfc_t	दीर्घlink_mfc;
    cistpl_vers_1_t		version_1;
    cistpl_altstr_t		altstr;
    cistpl_jedec_t		jedec;
    cistpl_manfid_t		manfid;
    cistpl_funcid_t		funcid;
    cistpl_funce_t		funce;
    cistpl_bar_t		bar;
    cistpl_config_t		config;
    cistpl_cftable_entry_t	cftable_entry;
    cistpl_cftable_entry_cb_t	cftable_entry_cb;
    cistpl_device_geo_t		device_geo;
    cistpl_vers_2_t		vers_2;
    cistpl_org_t		org;
    cistpl_क्रमmat_t		क्रमmat;
पूर्ण cisparse_t;

प्रकार काष्ठा tuple_t अणु
    u_पूर्णांक	Attributes;
    cisdata_t 	DesiredTuple;
    u_पूर्णांक	Flags;		/* पूर्णांकernal use */
    u_पूर्णांक	LinkOffset;	/* पूर्णांकernal use */
    u_पूर्णांक	CISOffset;	/* पूर्णांकernal use */
    cisdata_t	TupleCode;
    cisdata_t	TupleLink;
    cisdata_t	TupleOffset;
    cisdata_t	TupleDataMax;
    cisdata_t	TupleDataLen;
    cisdata_t	*TupleData;
पूर्ण tuple_t;

/* Special cisdata_t value */
#घोषणा RETURN_FIRST_TUPLE	0xff

/* Attributes क्रम tuple calls */
#घोषणा TUPLE_RETURN_LINK	0x01
#घोषणा TUPLE_RETURN_COMMON	0x02

#घोषणा CISTPL_MAX_CIS_SIZE	0x200

#पूर्ण_अगर /* LINUX_CISTPL_H */
