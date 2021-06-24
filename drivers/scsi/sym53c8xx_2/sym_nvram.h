<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#अगर_अघोषित SYM_NVRAM_H
#घोषणा SYM_NVRAM_H

#समावेश "sym53c8xx.h"

/*
 *	Symbios NVRAM data क्रमmat
 */
#घोषणा SYMBIOS_NVRAM_SIZE 368
#घोषणा SYMBIOS_NVRAM_ADDRESS 0x100

काष्ठा Symbios_nvram अणु
/* Header 6 bytes */
	u_लघु type;		/* 0x0000 */
	u_लघु byte_count;	/* excluding header/trailer */
	u_लघु checksum;

/* Controller set up 20 bytes */
	u_अक्षर	v_major;	/* 0x00 */
	u_अक्षर	v_minor;	/* 0x30 */
	u32	boot_crc;
	u_लघु	flags;
#घोषणा SYMBIOS_SCAM_ENABLE	(1)
#घोषणा SYMBIOS_PARITY_ENABLE	(1<<1)
#घोषणा SYMBIOS_VERBOSE_MSGS	(1<<2)
#घोषणा SYMBIOS_CHS_MAPPING	(1<<3)
#घोषणा SYMBIOS_NO_NVRAM	(1<<3)	/* ??? */
	u_लघु	flags1;
#घोषणा SYMBIOS_SCAN_HI_LO	(1)
	u_लघु	term_state;
#घोषणा SYMBIOS_TERM_CANT_PROGRAM	(0)
#घोषणा SYMBIOS_TERM_ENABLED		(1)
#घोषणा SYMBIOS_TERM_DISABLED		(2)
	u_लघु	rmvbl_flags;
#घोषणा SYMBIOS_RMVBL_NO_SUPPORT	(0)
#घोषणा SYMBIOS_RMVBL_BOOT_DEVICE	(1)
#घोषणा SYMBIOS_RMVBL_MEDIA_INSTALLED	(2)
	u_अक्षर	host_id;
	u_अक्षर	num_hba;	/* 0x04 */
	u_अक्षर	num_devices;	/* 0x10 */
	u_अक्षर	max_scam_devices;	/* 0x04 */
	u_अक्षर	num_valid_scam_devices;	/* 0x00 */
	u_अक्षर	flags2;
#घोषणा SYMBIOS_AVOID_BUS_RESET		(1<<2)

/* Boot order 14 bytes * 4 */
	काष्ठा Symbios_hostअणु
		u_लघु	type;		/* 4:8xx / 0:nok */
		u_लघु	device_id;	/* PCI device id */
		u_लघु	venकरोr_id;	/* PCI venकरोr id */
		u_अक्षर	bus_nr;		/* PCI bus number */
		u_अक्षर	device_fn;	/* PCI device/function number << 3*/
		u_लघु	word8;
		u_लघु	flags;
#घोषणा	SYMBIOS_INIT_SCAN_AT_BOOT	(1)
		u_लघु	io_port;	/* PCI io_port address */
	पूर्ण host[4];

/* Tarमाला_लो 8 bytes * 16 */
	काष्ठा Symbios_target अणु
		u_अक्षर	flags;
#घोषणा SYMBIOS_DISCONNECT_ENABLE	(1)
#घोषणा SYMBIOS_SCAN_AT_BOOT_TIME	(1<<1)
#घोषणा SYMBIOS_SCAN_LUNS		(1<<2)
#घोषणा SYMBIOS_QUEUE_TAGS_ENABLED	(1<<3)
		u_अक्षर	rsvd;
		u_अक्षर	bus_width;	/* 0x08/0x10 */
		u_अक्षर	sync_offset;
		u_लघु	sync_period;	/* 4*period factor */
		u_लघु	समयout;
	पूर्ण target[16];
/* Scam table 8 bytes * 4 */
	काष्ठा Symbios_scam अणु
		u_लघु	id;
		u_लघु	method;
#घोषणा SYMBIOS_SCAM_DEFAULT_METHOD	(0)
#घोषणा SYMBIOS_SCAM_DONT_ASSIGN	(1)
#घोषणा SYMBIOS_SCAM_SET_SPECIFIC_ID	(2)
#घोषणा SYMBIOS_SCAM_USE_ORDER_GIVEN	(3)
		u_लघु status;
#घोषणा SYMBIOS_SCAM_UNKNOWN		(0)
#घोषणा SYMBIOS_SCAM_DEVICE_NOT_FOUND	(1)
#घोषणा SYMBIOS_SCAM_ID_NOT_SET		(2)
#घोषणा SYMBIOS_SCAM_ID_VALID		(3)
		u_अक्षर	target_id;
		u_अक्षर	rsvd;
	पूर्ण scam[4];

	u_अक्षर	spare_devices[15*8];
	u_अक्षर	trailer[6];		/* 0xfe 0xfe 0x00 0x00 0x00 0x00 */
पूर्ण;
प्रकार काष्ठा Symbios_nvram	Symbios_nvram;
प्रकार काष्ठा Symbios_host	Symbios_host;
प्रकार काष्ठा Symbios_target	Symbios_target;
प्रकार काष्ठा Symbios_scam	Symbios_scam;

/*
 *	Tekram NvRAM data क्रमmat.
 */
#घोषणा TEKRAM_NVRAM_SIZE 64
#घोषणा TEKRAM_93C46_NVRAM_ADDRESS 0
#घोषणा TEKRAM_24C16_NVRAM_ADDRESS 0x40

काष्ठा Tekram_nvram अणु
	काष्ठा Tekram_target अणु
		u_अक्षर	flags;
#घोषणा	TEKRAM_PARITY_CHECK		(1)
#घोषणा TEKRAM_SYNC_NEGO		(1<<1)
#घोषणा TEKRAM_DISCONNECT_ENABLE	(1<<2)
#घोषणा	TEKRAM_START_CMD		(1<<3)
#घोषणा TEKRAM_TAGGED_COMMANDS		(1<<4)
#घोषणा TEKRAM_WIDE_NEGO		(1<<5)
		u_अक्षर	sync_index;
		u_लघु	word2;
	पूर्ण target[16];
	u_अक्षर	host_id;
	u_अक्षर	flags;
#घोषणा TEKRAM_MORE_THAN_2_DRIVES	(1)
#घोषणा TEKRAM_DRIVES_SUP_1GB		(1<<1)
#घोषणा	TEKRAM_RESET_ON_POWER_ON	(1<<2)
#घोषणा TEKRAM_ACTIVE_NEGATION		(1<<3)
#घोषणा TEKRAM_IMMEDIATE_SEEK		(1<<4)
#घोषणा	TEKRAM_SCAN_LUNS		(1<<5)
#घोषणा	TEKRAM_REMOVABLE_FLAGS		(3<<6)	/* 0: disable; */
						/* 1: boot device; 2:all */
	u_अक्षर	boot_delay_index;
	u_अक्षर	max_tags_index;
	u_लघु	flags1;
#घोषणा TEKRAM_F2_F6_ENABLED		(1)
	u_लघु	spare[29];
पूर्ण;
प्रकार काष्ठा Tekram_nvram	Tekram_nvram;
प्रकार काष्ठा Tekram_target	Tekram_target;

#अगर_अघोषित CONFIG_PARISC
काष्ठा pdc_initiator अणु पूर्णांक dummy; पूर्ण;
#पूर्ण_अगर

/*
 *  Union of supported NVRAM क्रमmats.
 */
काष्ठा sym_nvram अणु
	पूर्णांक type;
#घोषणा	SYM_SYMBIOS_NVRAM	(1)
#घोषणा	SYM_TEKRAM_NVRAM	(2)
#घोषणा SYM_PARISC_PDC		(3)
#अगर SYM_CONF_NVRAM_SUPPORT
	जोड़ अणु
		Symbios_nvram Symbios;
		Tekram_nvram Tekram;
		काष्ठा pdc_initiator parisc;
	पूर्ण data;
#पूर्ण_अगर
पूर्ण;

#अगर SYM_CONF_NVRAM_SUPPORT
व्योम sym_nvram_setup_host(काष्ठा Scsi_Host *shost, काष्ठा sym_hcb *np, काष्ठा sym_nvram *nvram);
व्योम sym_nvram_setup_target (काष्ठा sym_tcb *tp, पूर्णांक target, काष्ठा sym_nvram *nvp);
पूर्णांक sym_पढ़ो_nvram (काष्ठा sym_device *np, काष्ठा sym_nvram *nvp);
अक्षर *sym_nvram_type(काष्ठा sym_nvram *nvp);
#अन्यथा
अटल अंतरभूत व्योम sym_nvram_setup_host(काष्ठा Scsi_Host *shost, काष्ठा sym_hcb *np, काष्ठा sym_nvram *nvram) अणु पूर्ण
अटल अंतरभूत व्योम sym_nvram_setup_target(काष्ठा sym_tcb *tp, काष्ठा sym_nvram *nvram) अणु पूर्ण
अटल अंतरभूत पूर्णांक sym_पढ़ो_nvram(काष्ठा sym_device *np, काष्ठा sym_nvram *nvp)
अणु
	nvp->type = 0;
	वापस 0;
पूर्ण
अटल अंतरभूत अक्षर *sym_nvram_type(काष्ठा sym_nvram *nvp)
अणु
	वापस "No NVRAM";
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* SYM_NVRAM_H */
