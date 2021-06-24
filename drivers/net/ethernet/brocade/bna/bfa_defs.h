<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#अगर_अघोषित __BFA_DEFS_H__
#घोषणा __BFA_DEFS_H__

#समावेश "cna.h"
#समावेश "bfa_defs_status.h"
#समावेश "bfa_defs_mfg_comm.h"

#घोषणा BFA_VERSION_LEN 64

/* ---------------------- adapter definitions ------------ */

/* BFA adapter level attributes. */
क्रमागत अणु
	BFA_ADAPTER_SERIAL_NUM_LEN = STRSZ(BFA_MFG_SERIALNUM_SIZE),
					/*
					 *!< adapter serial num length
					 */
	BFA_ADAPTER_MODEL_NAME_LEN  = 16,  /*!< model name length */
	BFA_ADAPTER_MODEL_DESCR_LEN = 128, /*!< model description length */
	BFA_ADAPTER_MFG_NAME_LEN    = 8,   /*!< manufacturer name length */
	BFA_ADAPTER_SYM_NAME_LEN    = 64,  /*!< adapter symbolic name length */
	BFA_ADAPTER_OS_TYPE_LEN	    = 64,  /*!< adapter os type length */
पूर्ण;

काष्ठा bfa_adapter_attr अणु
	अक्षर		manufacturer[BFA_ADAPTER_MFG_NAME_LEN];
	अक्षर		serial_num[BFA_ADAPTER_SERIAL_NUM_LEN];
	u32	card_type;
	अक्षर		model[BFA_ADAPTER_MODEL_NAME_LEN];
	अक्षर		model_descr[BFA_ADAPTER_MODEL_DESCR_LEN];
	u64		pwwn;
	अक्षर		node_symname[FC_SYMNAME_MAX];
	अक्षर		hw_ver[BFA_VERSION_LEN];
	अक्षर		fw_ver[BFA_VERSION_LEN];
	अक्षर		optrom_ver[BFA_VERSION_LEN];
	अक्षर		os_type[BFA_ADAPTER_OS_TYPE_LEN];
	काष्ठा bfa_mfg_vpd vpd;
	u8		mac[ETH_ALEN];

	u8		nports;
	u8		max_speed;
	u8		prototype;
	अक्षर	        asic_rev;

	u8		pcie_gen;
	u8		pcie_lanes_orig;
	u8		pcie_lanes;
	u8	        cna_capable;

	u8		is_mezz;
	u8		trunk_capable;
पूर्ण;

/* ---------------------- IOC definitions ------------ */

क्रमागत अणु
	BFA_IOC_DRIVER_LEN	= 16,
	BFA_IOC_CHIP_REV_LEN	= 8,
पूर्ण;

/* Driver and firmware versions. */
काष्ठा bfa_ioc_driver_attr अणु
	अक्षर		driver[BFA_IOC_DRIVER_LEN];	/*!< driver name */
	अक्षर		driver_ver[BFA_VERSION_LEN];	/*!< driver version */
	अक्षर		fw_ver[BFA_VERSION_LEN];	/*!< firmware version */
	अक्षर		bios_ver[BFA_VERSION_LEN];	/*!< bios version */
	अक्षर		efi_ver[BFA_VERSION_LEN];	/*!< EFI version */
	अक्षर		ob_ver[BFA_VERSION_LEN];	/*!< खोलोboot version */
पूर्ण;

/* IOC PCI device attributes */
काष्ठा bfa_ioc_pci_attr अणु
	u16	venकरोr_id;	/*!< PCI venकरोr ID */
	u16	device_id;	/*!< PCI device ID */
	u16	ssid;		/*!< subप्रणाली ID */
	u16	ssvid;		/*!< subप्रणाली venकरोr ID */
	u32	pcअगरn;		/*!< PCI device function */
	u32	rsvd;		/* padding */
	अक्षर		chip_rev[BFA_IOC_CHIP_REV_LEN];	 /*!< chip revision */
पूर्ण;

/* IOC states */
क्रमागत bfa_ioc_state अणु
	BFA_IOC_UNINIT		= 1,	/*!< IOC is in uninit state */
	BFA_IOC_RESET		= 2,	/*!< IOC is in reset state */
	BFA_IOC_SEMWAIT		= 3,	/*!< Waiting क्रम IOC h/w semaphore */
	BFA_IOC_HWINIT		= 4,	/*!< IOC h/w is being initialized */
	BFA_IOC_GETATTR		= 5,	/*!< IOC is being configured */
	BFA_IOC_OPERATIONAL	= 6,	/*!< IOC is operational */
	BFA_IOC_INITFAIL	= 7,	/*!< IOC hardware failure */
	BFA_IOC_FAIL		= 8,	/*!< IOC heart-beat failure */
	BFA_IOC_DISABLING	= 9,	/*!< IOC is being disabled */
	BFA_IOC_DISABLED	= 10,	/*!< IOC is disabled */
	BFA_IOC_FWMISMATCH	= 11,	/*!< IOC f/w dअगरferent from drivers */
	BFA_IOC_ENABLING	= 12,	/*!< IOC is being enabled */
	BFA_IOC_HWFAIL		= 13,	/*!< PCI mapping करोesn't exist */
पूर्ण;

/* IOC firmware stats */
काष्ठा bfa_fw_ioc_stats अणु
	u32	enable_reqs;
	u32	disable_reqs;
	u32	get_attr_reqs;
	u32	dbg_sync;
	u32	dbg_dump;
	u32	unknown_reqs;
पूर्ण;

/* IOC driver stats */
काष्ठा bfa_ioc_drv_stats अणु
	u32	ioc_isrs;
	u32	ioc_enables;
	u32	ioc_disables;
	u32	ioc_hbfails;
	u32	ioc_boots;
	u32	stats_पंचांगos;
	u32	hb_count;
	u32	disable_reqs;
	u32	enable_reqs;
	u32	disable_replies;
	u32	enable_replies;
	u32	rsvd;
पूर्ण;

/* IOC statistics */
काष्ठा bfa_ioc_stats अणु
	काष्ठा bfa_ioc_drv_stats drv_stats; /*!< driver IOC stats */
	काष्ठा bfa_fw_ioc_stats fw_stats;  /*!< firmware IOC stats */
पूर्ण;

क्रमागत bfa_ioc_type अणु
	BFA_IOC_TYPE_FC		= 1,
	BFA_IOC_TYPE_FCoE	= 2,
	BFA_IOC_TYPE_LL		= 3,
पूर्ण;

/* IOC attributes वापसed in queries */
काष्ठा bfa_ioc_attr अणु
	क्रमागत bfa_ioc_type ioc_type;
	क्रमागत bfa_ioc_state		state;		/*!< IOC state      */
	काष्ठा bfa_adapter_attr adapter_attr;	/*!< HBA attributes */
	काष्ठा bfa_ioc_driver_attr driver_attr;	/*!< driver attr    */
	काष्ठा bfa_ioc_pci_attr pci_attr;
	u8				port_id;	/*!< port number */
	u8				port_mode;	/*!< क्रमागत bfa_mode */
	u8				cap_bm;		/*!< capability */
	u8				port_mode_cfg;	/*!< क्रमागत bfa_mode */
	u8				def_fn;		/*!< 1 अगर शेष fn */
	u8				rsvd[3];	/*!< 64bit align */
पूर्ण;

/* Adapter capability mask definition */
क्रमागत अणु
	BFA_CM_HBA	=	0x01,
	BFA_CM_CNA	=	0x02,
	BFA_CM_NIC	=	0x04,
पूर्ण;

/* ---------------------- mfg definitions ------------ */

/* Checksum size */
#घोषणा BFA_MFG_CHKSUM_SIZE			16

#घोषणा BFA_MFG_PARTNUM_SIZE			14
#घोषणा BFA_MFG_SUPPLIER_ID_SIZE		10
#घोषणा BFA_MFG_SUPPLIER_PARTNUM_SIZE		20
#घोषणा BFA_MFG_SUPPLIER_SERIALNUM_SIZE		20
#घोषणा BFA_MFG_SUPPLIER_REVISION_SIZE		4

/* BFA adapter manufacturing block definition.
 *
 * All numerical fields are in big-endian क्रमmat.
 */
काष्ठा bfa_mfg_block अणु
	u8	version;	/* manufacturing block version */
	u8	mfg_sig[3];	/* अक्षरacters 'M', 'F', 'G' */
	u16	mfgsize;	/* mfg block size */
	u16	u16_chksum;	/* old u16 checksum */
	अक्षर	brcd_serialnum[STRSZ(BFA_MFG_SERIALNUM_SIZE)];
	अक्षर	brcd_partnum[STRSZ(BFA_MFG_PARTNUM_SIZE)];
	u8	mfg_day;	/* manufacturing day */
	u8	mfg_month;	/* manufacturing month */
	u16	mfg_year;	/* manufacturing year */
	u64	mfg_wwn;	/* wwn base क्रम this adapter */
	u8	num_wwn;	/* number of wwns asचिन्हित */
	u8	mfg_speeds;	/* speeds allowed क्रम this adapter */
	u8	rsv[2];
	अक्षर	supplier_id[STRSZ(BFA_MFG_SUPPLIER_ID_SIZE)];
	अक्षर	supplier_partnum[STRSZ(BFA_MFG_SUPPLIER_PARTNUM_SIZE)];
	अक्षर	supplier_serialnum[STRSZ(BFA_MFG_SUPPLIER_SERIALNUM_SIZE)];
	अक्षर	supplier_revision[STRSZ(BFA_MFG_SUPPLIER_REVISION_SIZE)];
	u8	mfg_mac[ETH_ALEN]; /* base mac address */
	u8	num_mac;	/* number of mac addresses */
	u8	rsv2;
	u32	card_type;	/* card type          */
	अक्षर	cap_nic;	/* capability nic     */
	अक्षर	cap_cna;	/* capability cna     */
	अक्षर	cap_hba;	/* capability hba     */
	अक्षर	cap_fc16g;	/* capability fc 16g      */
	अक्षर	cap_sriov;	/* capability sriov       */
	अक्षर	cap_mezz;	/* capability mezz        */
	u8	rsv3;
	u8	mfg_nports;	/* number of ports        */
	अक्षर	media[8];	/* xfi/xaui           */
	अक्षर	initial_mode[8]; /* initial mode: hba/cna/nic */
	u8	rsv4[84];
	u8	md5_chksum[BFA_MFG_CHKSUM_SIZE]; /* md5 checksum */
पूर्ण __packed;

/* ---------------------- pci definitions ------------ */

/*
 * PCI device ID inक्रमmation
 */
क्रमागत अणु
	BFA_PCI_DEVICE_ID_CT2		= 0x22,
पूर्ण;

#घोषणा bfa_asic_id_ct(device)			\
	((device) == PCI_DEVICE_ID_BROCADE_CT ||	\
	 (device) == PCI_DEVICE_ID_BROCADE_CT_FC)
#घोषणा bfa_asic_id_ct2(device)			\
	((device) == BFA_PCI_DEVICE_ID_CT2)
#घोषणा bfa_asic_id_ctc(device)			\
	(bfa_asic_id_ct(device) || bfa_asic_id_ct2(device))

/* PCI sub-प्रणाली device and venकरोr ID inक्रमmation */
क्रमागत अणु
	BFA_PCI_FCOE_SSDEVICE_ID	= 0x14,
	BFA_PCI_CT2_SSID_FCoE		= 0x22,
	BFA_PCI_CT2_SSID_ETH		= 0x23,
	BFA_PCI_CT2_SSID_FC		= 0x24,
पूर्ण;

क्रमागत bfa_mode अणु
	BFA_MODE_HBA		= 1,
	BFA_MODE_CNA		= 2,
	BFA_MODE_NIC		= 3
पूर्ण;

/*
 *	Flash module specअगरic
 */
#घोषणा BFA_FLASH_PART_ENTRY_SIZE	32	/* partition entry size */
#घोषणा BFA_FLASH_PART_MAX		32	/* maximal # of partitions */
#घोषणा BFA_TOTAL_FLASH_SIZE		0x400000
#घोषणा BFA_FLASH_PART_FWIMG		2
#घोषणा BFA_FLASH_PART_MFG		7

/*
 * flash partition attributes
 */
काष्ठा bfa_flash_part_attr अणु
	u32	part_type;	/* partition type */
	u32	part_instance;	/* partition instance */
	u32	part_off;	/* partition offset */
	u32	part_size;	/* partition size */
	u32	part_len;	/* partition content length */
	u32	part_status;	/* partition status */
	अक्षर	rsv[BFA_FLASH_PART_ENTRY_SIZE - 24];
पूर्ण;

/*
 * flash attributes
 */
काष्ठा bfa_flash_attr अणु
	u32	status;	/* flash overall status */
	u32	npart;  /* num of partitions */
	काष्ठा bfa_flash_part_attr part[BFA_FLASH_PART_MAX];
पूर्ण;

#पूर्ण_अगर /* __BFA_DEFS_H__ */
