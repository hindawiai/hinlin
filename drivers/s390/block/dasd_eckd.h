<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2000
 *
 */

#अगर_अघोषित DASD_ECKD_H
#घोषणा DASD_ECKD_H

/*****************************************************************************
 * SECTION: CCW Definitions
 ****************************************************************************/
#घोषणा DASD_ECKD_CCW_WRITE		 0x05
#घोषणा DASD_ECKD_CCW_READ		 0x06
#घोषणा DASD_ECKD_CCW_WRITE_HOME_ADDRESS 0x09
#घोषणा DASD_ECKD_CCW_READ_HOME_ADDRESS	 0x0a
#घोषणा DASD_ECKD_CCW_WRITE_KD		 0x0d
#घोषणा DASD_ECKD_CCW_READ_KD		 0x0e
#घोषणा DASD_ECKD_CCW_ERASE		 0x11
#घोषणा DASD_ECKD_CCW_READ_COUNT	 0x12
#घोषणा DASD_ECKD_CCW_SLCK		 0x14
#घोषणा DASD_ECKD_CCW_WRITE_RECORD_ZERO	 0x15
#घोषणा DASD_ECKD_CCW_READ_RECORD_ZERO	 0x16
#घोषणा DASD_ECKD_CCW_WRITE_CKD		 0x1d
#घोषणा DASD_ECKD_CCW_READ_CKD		 0x1e
#घोषणा DASD_ECKD_CCW_PSF		 0x27
#घोषणा DASD_ECKD_CCW_SNID		 0x34
#घोषणा DASD_ECKD_CCW_RSSD		 0x3e
#घोषणा DASD_ECKD_CCW_LOCATE_RECORD	 0x47
#घोषणा DASD_ECKD_CCW_LOCATE_RECORD_EXT	 0x4b
#घोषणा DASD_ECKD_CCW_SNSS		 0x54
#घोषणा DASD_ECKD_CCW_DEFINE_EXTENT	 0x63
#घोषणा DASD_ECKD_CCW_WRITE_MT		 0x85
#घोषणा DASD_ECKD_CCW_READ_MT		 0x86
#घोषणा DASD_ECKD_CCW_WRITE_KD_MT	 0x8d
#घोषणा DASD_ECKD_CCW_READ_KD_MT	 0x8e
#घोषणा DASD_ECKD_CCW_READ_COUNT_MT	 0x92
#घोषणा DASD_ECKD_CCW_RELEASE		 0x94
#घोषणा DASD_ECKD_CCW_WRITE_FULL_TRACK	 0x95
#घोषणा DASD_ECKD_CCW_READ_CKD_MT	 0x9e
#घोषणा DASD_ECKD_CCW_WRITE_CKD_MT	 0x9d
#घोषणा DASD_ECKD_CCW_WRITE_TRACK_DATA	 0xA5
#घोषणा DASD_ECKD_CCW_READ_TRACK_DATA	 0xA6
#घोषणा DASD_ECKD_CCW_RESERVE		 0xB4
#घोषणा DASD_ECKD_CCW_READ_TRACK	 0xDE
#घोषणा DASD_ECKD_CCW_PFX		 0xE7
#घोषणा DASD_ECKD_CCW_PFX_READ		 0xEA
#घोषणा DASD_ECKD_CCW_RSCK		 0xF9
#घोषणा DASD_ECKD_CCW_RCD		 0xFA
#घोषणा DASD_ECKD_CCW_DSO		 0xF7

/* Define Subप्रणाली Function / Orders */
#घोषणा DSO_ORDER_RAS			 0x81

/*
 * Perक्रमm Subप्रणाली Function / Orders
 */
#घोषणा PSF_ORDER_PRSSD			 0x18
#घोषणा PSF_ORDER_CUIR_RESPONSE		 0x1A
#घोषणा PSF_ORDER_SSC			 0x1D

/*
 * Perक्रमm Subप्रणाली Function / Sub-Orders
 */
#घोषणा PSF_SUBORDER_QHA		 0x1C /* Query Host Access */
#घोषणा PSF_SUBORDER_VSQ		 0x52 /* Volume Storage Query */
#घोषणा PSF_SUBORDER_LCQ		 0x53 /* Logical Configuration Query */

/*
 * CUIR response condition codes
 */
#घोषणा PSF_CUIR_INVALID		 0x00
#घोषणा PSF_CUIR_COMPLETED		 0x01
#घोषणा PSF_CUIR_NOT_SUPPORTED		 0x02
#घोषणा PSF_CUIR_ERROR_IN_REQ		 0x03
#घोषणा PSF_CUIR_DENIED			 0x04
#घोषणा PSF_CUIR_LAST_PATH		 0x05
#घोषणा PSF_CUIR_DEVICE_ONLINE		 0x06
#घोषणा PSF_CUIR_VARY_FAILURE		 0x07
#घोषणा PSF_CUIR_SOFTWARE_FAILURE	 0x08
#घोषणा PSF_CUIR_NOT_RECOGNIZED		 0x09

/*
 * CUIR codes
 */
#घोषणा CUIR_QUIESCE			 0x01
#घोषणा CUIR_RESUME			 0x02

/*
 * Out-of-space (OOS) Codes
 */
#घोषणा REPO_WARN			 0x01
#घोषणा REPO_EXHAUST			 0x02
#घोषणा POOL_WARN			 0x03
#घोषणा POOL_EXHAUST			 0x04
#घोषणा REPO_RELIEVE			 0x05
#घोषणा POOL_RELIEVE			 0x06

/*
 * attention message definitions
 */
#घोषणा ATTENTION_LENGTH_CUIR		 0x0e
#घोषणा ATTENTION_FORMAT_CUIR		 0x01
#घोषणा ATTENTION_LENGTH_OOS		 0x10
#घोषणा ATTENTION_FORMAT_OOS		 0x06

#घोषणा DASD_ECKD_PG_GROUPED		 0x10

/*
 * Size that is reported क्रम large volumes in the old 16-bit no_cyl field
 */
#घोषणा LV_COMPAT_CYL 0xFFFE


#घोषणा FCX_MAX_DATA_FACTOR 65536
#घोषणा DASD_ECKD_RCD_DATA_SIZE 256

#घोषणा DASD_ECKD_PATH_THRHLD		 256
#घोषणा DASD_ECKD_PATH_INTERVAL		 300

/*
 * Maximum number of blocks to be chained
 */
#घोषणा DASD_ECKD_MAX_BLOCKS		 190
#घोषणा DASD_ECKD_MAX_BLOCKS_RAW	 256

/*****************************************************************************
 * SECTION: Type Definitions
 ****************************************************************************/

काष्ठा eckd_count अणु
	__u16 cyl;
	__u16 head;
	__u8 record;
	__u8 kl;
	__u16 dl;
पूर्ण __attribute__ ((packed));

काष्ठा ch_t अणु
	__u16 cyl;
	__u16 head;
पूर्ण __attribute__ ((packed));

काष्ठा chr_t अणु
	__u16 cyl;
	__u16 head;
	__u8 record;
पूर्ण __attribute__ ((packed));

काष्ठा DE_eckd_data अणु
	काष्ठा अणु
		अचिन्हित अक्षर perm:2;	/* Permissions on this extent */
		अचिन्हित अक्षर reserved:1;
		अचिन्हित अक्षर seek:2;	/* Seek control */
		अचिन्हित अक्षर auth:2;	/* Access authorization */
		अचिन्हित अक्षर pci:1;	/* PCI Fetch mode */
	पूर्ण __attribute__ ((packed)) mask;
	काष्ठा अणु
		अचिन्हित अक्षर mode:2;	/* Architecture mode */
		अचिन्हित अक्षर ckd:1;	/* CKD Conversion */
		अचिन्हित अक्षर operation:3;	/* Operation mode */
		अचिन्हित अक्षर cfw:1;	/* Cache fast ग_लिखो */
		अचिन्हित अक्षर dfw:1;	/* DASD fast ग_लिखो */
	पूर्ण __attribute__ ((packed)) attributes;
	__u16 blk_size;		/* Blocksize */
	__u16 fast_ग_लिखो_id;
	__u8 ga_additional;	/* Global Attributes Additional */
	__u8 ga_extended;	/* Global Attributes Extended	*/
	काष्ठा ch_t beg_ext;
	काष्ठा ch_t end_ext;
	अचिन्हित दीर्घ ep_sys_समय; /* Ext Parameter - System Time Stamp */
	__u8 ep_क्रमmat;        /* Extended Parameter क्रमmat byte       */
	__u8 ep_prio;          /* Extended Parameter priority I/O byte */
	__u8 ep_reserved1;     /* Extended Parameter Reserved	       */
	__u8 ep_rec_per_track; /* Number of records on a track	       */
	__u8 ep_reserved[4];   /* Extended Parameter Reserved	       */
पूर्ण __attribute__ ((packed));

काष्ठा LO_eckd_data अणु
	काष्ठा अणु
		अचिन्हित अक्षर orientation:2;
		अचिन्हित अक्षर operation:6;
	पूर्ण __attribute__ ((packed)) operation;
	काष्ठा अणु
		अचिन्हित अक्षर last_bytes_used:1;
		अचिन्हित अक्षर reserved:6;
		अचिन्हित अक्षर पढ़ो_count_suffix:1;
	पूर्ण __attribute__ ((packed)) auxiliary;
	__u8 unused;
	__u8 count;
	काष्ठा ch_t seek_addr;
	काष्ठा chr_t search_arg;
	__u8 sector;
	__u16 length;
पूर्ण __attribute__ ((packed));

काष्ठा LRE_eckd_data अणु
	काष्ठा अणु
		अचिन्हित अक्षर orientation:2;
		अचिन्हित अक्षर operation:6;
	पूर्ण __attribute__ ((packed)) operation;
	काष्ठा अणु
		अचिन्हित अक्षर length_valid:1;
		अचिन्हित अक्षर length_scope:1;
		अचिन्हित अक्षर imbedded_ccw_valid:1;
		अचिन्हित अक्षर check_bytes:2;
		अचिन्हित अक्षर imbedded_count_valid:1;
		अचिन्हित अक्षर reserved:1;
		अचिन्हित अक्षर पढ़ो_count_suffix:1;
	पूर्ण __attribute__ ((packed)) auxiliary;
	__u8 imbedded_ccw;
	__u8 count;
	काष्ठा ch_t seek_addr;
	काष्ठा chr_t search_arg;
	__u8 sector;
	__u16 length;
	__u8 imbedded_count;
	__u8 extended_operation;
	__u16 extended_parameter_length;
	__u8 extended_parameter[];
पूर्ण __attribute__ ((packed));

/* Prefix data क्रम क्रमmat 0x00 and 0x01 */
काष्ठा PFX_eckd_data अणु
	अचिन्हित अक्षर क्रमmat;
	काष्ठा अणु
		अचिन्हित अक्षर define_extent:1;
		अचिन्हित अक्षर समय_stamp:1;
		अचिन्हित अक्षर verअगरy_base:1;
		अचिन्हित अक्षर hyper_pav:1;
		अचिन्हित अक्षर reserved:4;
	पूर्ण __attribute__ ((packed)) validity;
	__u8 base_address;
	__u8 aux;
	__u8 base_lss;
	__u8 reserved[7];
	काष्ठा DE_eckd_data define_extent;
	काष्ठा LRE_eckd_data locate_record;
पूर्ण __attribute__ ((packed));

काष्ठा dasd_eckd_अक्षरacteristics अणु
	__u16 cu_type;
	काष्ठा अणु
		अचिन्हित अक्षर support:2;
		अचिन्हित अक्षर async:1;
		अचिन्हित अक्षर reserved:1;
		अचिन्हित अक्षर cache_info:1;
		अचिन्हित अक्षर model:3;
	पूर्ण __attribute__ ((packed)) cu_model;
	__u16 dev_type;
	__u8 dev_model;
	काष्ठा अणु
		अचिन्हित अक्षर mult_burst:1;
		अचिन्हित अक्षर RT_in_LR:1;
		अचिन्हित अक्षर reserved1:1;
		अचिन्हित अक्षर RD_IN_LR:1;
		अचिन्हित अक्षर reserved2:4;
		अचिन्हित अक्षर reserved3:8;
		अचिन्हित अक्षर defect_wr:1;
		अचिन्हित अक्षर XRC_supported:1;
		अचिन्हित अक्षर reserved4:1;
		अचिन्हित अक्षर striping:1;
		अचिन्हित अक्षर reserved5:4;
		अचिन्हित अक्षर cfw:1;
		अचिन्हित अक्षर reserved6:2;
		अचिन्हित अक्षर cache:1;
		अचिन्हित अक्षर dual_copy:1;
		अचिन्हित अक्षर dfw:1;
		अचिन्हित अक्षर reset_alleg:1;
		अचिन्हित अक्षर sense_करोwn:1;
	पूर्ण __attribute__ ((packed)) facilities;
	__u8 dev_class;
	__u8 unit_type;
	__u16 no_cyl;
	__u16 trk_per_cyl;
	__u8 sec_per_trk;
	__u8 byte_per_track[3];
	__u16 home_bytes;
	__u8 क्रमmula;
	जोड़ अणु
		काष्ठा अणु
			__u8 f1;
			__u16 f2;
			__u16 f3;
		पूर्ण __attribute__ ((packed)) f_0x01;
		काष्ठा अणु
			__u8 f1;
			__u8 f2;
			__u8 f3;
			__u8 f4;
			__u8 f5;
		पूर्ण __attribute__ ((packed)) f_0x02;
	पूर्ण __attribute__ ((packed)) factors;
	__u16 first_alt_trk;
	__u16 no_alt_trk;
	__u16 first_dia_trk;
	__u16 no_dia_trk;
	__u16 first_sup_trk;
	__u16 no_sup_trk;
	__u8 MDR_ID;
	__u8 OBR_ID;
	__u8 director;
	__u8 rd_trk_set;
	__u16 max_rec_zero;
	__u8 reserved1;
	__u8 RWANY_in_LR;
	__u8 factor6;
	__u8 factor7;
	__u8 factor8;
	__u8 reserved2[3];
	__u8 reserved3[6];
	__u32 दीर्घ_no_cyl;
पूर्ण __attribute__ ((packed));

/* elements of the configuration data */
काष्ठा dasd_ned अणु
	काष्ठा अणु
		__u8 identअगरier:2;
		__u8 token_id:1;
		__u8 sno_valid:1;
		__u8 subst_sno:1;
		__u8 recNED:1;
		__u8 emuNED:1;
		__u8 reserved:1;
	पूर्ण __attribute__ ((packed)) flags;
	__u8 descriptor;
	__u8 dev_class;
	__u8 reserved;
	__u8 dev_type[6];
	__u8 dev_model[3];
	__u8 HDA_manufacturer[3];
	__u8 HDA_location[2];
	__u8 HDA_seqno[12];
	__u8 ID;
	__u8 unit_addr;
पूर्ण __attribute__ ((packed));

काष्ठा dasd_sneq अणु
	काष्ठा अणु
		__u8 identअगरier:2;
		__u8 reserved:6;
	पूर्ण __attribute__ ((packed)) flags;
	__u8 res1;
	__u16 क्रमmat;
	__u8 res2[4];		/* byte  4- 7 */
	__u8 sua_flags;		/* byte  8    */
	__u8 base_unit_addr;	/* byte  9    */
	__u8 res3[22];		/* byte 10-31 */
पूर्ण __attribute__ ((packed));

काष्ठा vd_sneq अणु
	काष्ठा अणु
		__u8 identअगरier:2;
		__u8 reserved:6;
	पूर्ण __attribute__ ((packed)) flags;
	__u8 res1;
	__u16 क्रमmat;
	__u8 res2[4];	/* byte  4- 7 */
	__u8 uit[16];	/* byte  8-23 */
	__u8 res3[8];	/* byte 24-31 */
पूर्ण __attribute__ ((packed));

काष्ठा dasd_gneq अणु
	काष्ठा अणु
		__u8 identअगरier:2;
		__u8 reserved:6;
	पूर्ण __attribute__ ((packed)) flags;
	__u8 record_selector;
	__u8 reserved[4];
	काष्ठा अणु
		__u8 value:2;
		__u8 number:6;
	पूर्ण __attribute__ ((packed)) समयout;
	__u8 reserved3;
	__u16 subप्रणालीID;
	__u8 reserved2[22];
पूर्ण __attribute__ ((packed));

काष्ठा dasd_rssd_features अणु
	अक्षर feature[256];
पूर्ण __attribute__((packed));

काष्ठा dasd_rssd_messages अणु
	__u16 length;
	__u8 क्रमmat;
	__u8 code;
	__u32 message_id;
	__u8 flags;
	अक्षर messages[4087];
पूर्ण __packed;

/*
 * Read Subप्रणाली Data - Volume Storage Query
 */
काष्ठा dasd_rssd_vsq अणु
	काष्ठा अणु
		__u8 tse:1;
		__u8 space_not_available:1;
		__u8 ese:1;
		__u8 unused:5;
	पूर्ण __packed vol_info;
	__u8 unused1;
	__u16 extent_pool_id;
	__u8 warn_cap_limit;
	__u8 warn_cap_guaranteed;
	__u16 unused2;
	__u32 limit_capacity;
	__u32 guaranteed_capacity;
	__u32 space_allocated;
	__u32 space_configured;
	__u32 logical_capacity;
पूर्ण __packed;

/*
 * Extent Pool Summary
 */
काष्ठा dasd_ext_pool_sum अणु
	__u16 pool_id;
	__u8 repo_warn_thrshld;
	__u8 warn_thrshld;
	काष्ठा अणु
		__u8 type:1;			/* 0 - CKD / 1 - FB */
		__u8 track_space_efficient:1;
		__u8 extent_space_efficient:1;
		__u8 standard_volume:1;
		__u8 extent_size_valid:1;
		__u8 capacity_at_warnlevel:1;
		__u8 pool_oos:1;
		__u8 unused0:1;
		__u8 unused1;
	पूर्ण __packed flags;
	काष्ठा अणु
		__u8 reserved0:1;
		__u8 size_1G:1;
		__u8 reserved1:5;
		__u8 size_16M:1;
	पूर्ण __packed extent_size;
	__u8 unused;
पूर्ण __packed;

/*
 * Read Subप्रणाली Data-Response - Logical Configuration Query - Header
 */
काष्ठा dasd_rssd_lcq अणु
	__u16 data_length;		/* Length of data वापसed */
	__u16 pool_count;		/* Count of extent pools वापसed - Max: 448 */
	काष्ठा अणु
		__u8 pool_info_valid:1;	/* Detailed Inक्रमmation valid */
		__u8 pool_id_volume:1;
		__u8 pool_id_cec:1;
		__u8 unused0:5;
		__u8 unused1;
	पूर्ण __packed header_flags;
	अक्षर sfi_type[6];		/* Storage Facility Image Type (EBCDIC) */
	अक्षर sfi_model[3];		/* Storage Facility Image Model (EBCDIC) */
	__u8 sfi_seq_num[10];		/* Storage Facility Image Sequence Number */
	__u8 reserved[7];
	काष्ठा dasd_ext_pool_sum ext_pool_sum[448];
पूर्ण __packed;

काष्ठा dasd_oos_message अणु
	__u16 length;
	__u8 क्रमmat;
	__u8 code;
	__u8 percentage_empty;
	__u8 reserved;
	__u16 ext_pool_id;
	__u16 token;
	__u8 unused[6];
पूर्ण __packed;

काष्ठा dasd_cuir_message अणु
	__u16 length;
	__u8 क्रमmat;
	__u8 code;
	__u32 message_id;
	__u8 flags;
	__u8 neq_map[3];
	__u8 ned_map;
	__u8 record_selector;
पूर्ण __packed;

काष्ठा dasd_psf_cuir_response अणु
	__u8 order;
	__u8 flags;
	__u8 cc;
	__u8 chpid;
	__u16 device_nr;
	__u16 reserved;
	__u32 message_id;
	__u64 प्रणाली_id;
	__u8 cssid;
	__u8 ssid;
पूर्ण __packed;

काष्ठा dasd_ckd_path_group_entry अणु
	__u8 status_flags;
	__u8 pgid[11];
	__u8 sysplex_name[8];
	__u32 बारtamp;
	__u32 cylinder;
	__u8 reserved[4];
पूर्ण __packed;

काष्ठा dasd_ckd_host_inक्रमmation अणु
	__u8 access_flags;
	__u8 entry_size;
	__u16 entry_count;
	__u8 entry[16390];
पूर्ण __packed;

काष्ठा dasd_psf_query_host_access अणु
	__u8 access_flag;
	__u8 version;
	__u16 CKD_length;
	__u16 SCSI_length;
	__u8 unused[10];
	__u8 host_access_inक्रमmation[16394];
पूर्ण __packed;

/*
 * Perक्रमm Subप्रणाली Function - Prepare क्रम Read Subप्रणाली Data
 */
काष्ठा dasd_psf_prssd_data अणु
	अचिन्हित अक्षर order;
	अचिन्हित अक्षर flags;
	अचिन्हित अक्षर reserved1;
	अचिन्हित अक्षर reserved2;
	अचिन्हित अक्षर lss;
	अचिन्हित अक्षर volume;
	अचिन्हित अक्षर suborder;
	अचिन्हित अक्षर varies[5];
पूर्ण __attribute__ ((packed));

/*
 * Perक्रमm Subप्रणाली Function - Set Subप्रणाली Characteristics
 */
काष्ठा dasd_psf_ssc_data अणु
	अचिन्हित अक्षर order;
	अचिन्हित अक्षर flags;
	अचिन्हित अक्षर cu_type[4];
	अचिन्हित अक्षर suborder;
	अचिन्हित अक्षर reserved[59];
पूर्ण __attribute__((packed));

/* Maximum number of extents क्रम a single Release Allocated Space command */
#घोषणा DASD_ECKD_RAS_EXTS_MAX		110U

काष्ठा dasd_dso_ras_ext_range अणु
	काष्ठा ch_t beg_ext;
	काष्ठा ch_t end_ext;
पूर्ण __packed;

/*
 * Define Subप्रणाली Operation - Release Allocated Space
 */
काष्ठा dasd_dso_ras_data अणु
	__u8 order;
	काष्ठा अणु
		__u8 message:1;		/* Must be zero */
		__u8 reserved1:2;
		__u8 vol_type:1;	/* 0 - CKD/FBA, 1 - FB */
		__u8 reserved2:4;
	पूर्ण __packed flags;
	/* Operation Flags to specअगरy scope */
	काष्ठा अणु
		__u8 reserved1:2;
		/* Release Space by Extent */
		__u8 by_extent:1;	/* 0 - entire volume, 1 - specअगरied extents */
		__u8 guarantee_init:1;
		__u8 क्रमce_release:1;	/* Internal - will be ignored */
		__u16 reserved2:11;
	पूर्ण __packed op_flags;
	__u8 lss;
	__u8 dev_addr;
	__u32 reserved1;
	__u8 reserved2[10];
	__u16 nr_exts;			/* Defines number of ext_scope - max 110 */
	__u16 reserved3;
पूर्ण __packed;


/*
 * some काष्ठाures and definitions क्रम alias handling
 */
काष्ठा dasd_unit_address_configuration अणु
	काष्ठा अणु
		अक्षर ua_type;
		अक्षर base_ua;
	पूर्ण unit[256];
पूर्ण __attribute__((packed));


#घोषणा MAX_DEVICES_PER_LCU 256

/* flags on the LCU  */
#घोषणा NEED_UAC_UPDATE  0x01
#घोषणा UPDATE_PENDING	0x02

क्रमागत pavtype अणुNO_PAV, BASE_PAV, HYPER_PAVपूर्ण;


काष्ठा alias_root अणु
	काष्ठा list_head serverlist;
	spinlock_t lock;
पूर्ण;

काष्ठा alias_server अणु
	काष्ठा list_head server;
	काष्ठा dasd_uid uid;
	काष्ठा list_head lculist;
पूर्ण;

काष्ठा summary_unit_check_work_data अणु
	अक्षर reason;
	काष्ठा dasd_device *device;
	काष्ठा work_काष्ठा worker;
पूर्ण;

काष्ठा पढ़ो_uac_work_data अणु
	काष्ठा dasd_device *device;
	काष्ठा delayed_work dwork;
पूर्ण;

काष्ठा alias_lcu अणु
	काष्ठा list_head lcu;
	काष्ठा dasd_uid uid;
	क्रमागत pavtype pav;
	अक्षर flags;
	spinlock_t lock;
	काष्ठा list_head grouplist;
	काष्ठा list_head active_devices;
	काष्ठा list_head inactive_devices;
	काष्ठा dasd_unit_address_configuration *uac;
	काष्ठा summary_unit_check_work_data suc_data;
	काष्ठा पढ़ो_uac_work_data ruac_data;
	काष्ठा dasd_ccw_req *rsu_cqr;
	काष्ठा completion lcu_setup;
पूर्ण;

काष्ठा alias_pav_group अणु
	काष्ठा list_head group;
	काष्ठा dasd_uid uid;
	काष्ठा alias_lcu *lcu;
	काष्ठा list_head baselist;
	काष्ठा list_head aliaslist;
	काष्ठा dasd_device *next;
पूर्ण;

काष्ठा dasd_conf_data अणु
	काष्ठा dasd_ned neds[5];
	u8 reserved[64];
	काष्ठा dasd_gneq gneq;
पूर्ण __packed;

काष्ठा dasd_eckd_निजी अणु
	काष्ठा dasd_eckd_अक्षरacteristics rdc_data;
	u8 *conf_data;
	पूर्णांक conf_len;

	/* poपूर्णांकers to specअगरic parts in the conf_data */
	काष्ठा dasd_ned *ned;
	काष्ठा dasd_sneq *sneq;
	काष्ठा vd_sneq *vdsneq;
	काष्ठा dasd_gneq *gneq;

	काष्ठा eckd_count count_area[5];
	पूर्णांक init_cqr_status;
	पूर्णांक uses_cdl;
	काष्ठा attrib_data_t attrib;	/* e.g. cache operations */
	काष्ठा dasd_rssd_features features;
	काष्ठा dasd_rssd_vsq vsq;
	काष्ठा dasd_ext_pool_sum eps;
	u32 real_cyl;

	/* alias management */
	काष्ठा dasd_uid uid;
	काष्ठा alias_pav_group *pavgroup;
	काष्ठा alias_lcu *lcu;
	पूर्णांक count;

	u32 fcx_max_data;
	अक्षर suc_reason;
पूर्ण;



पूर्णांक dasd_alias_make_device_known_to_lcu(काष्ठा dasd_device *);
व्योम dasd_alias_disconnect_device_from_lcu(काष्ठा dasd_device *);
पूर्णांक dasd_alias_add_device(काष्ठा dasd_device *);
पूर्णांक dasd_alias_हटाओ_device(काष्ठा dasd_device *);
काष्ठा dasd_device *dasd_alias_get_start_dev(काष्ठा dasd_device *);
व्योम dasd_alias_handle_summary_unit_check(काष्ठा work_काष्ठा *);
व्योम dasd_eckd_reset_ccw_to_base_io(काष्ठा dasd_ccw_req *);
पूर्णांक dasd_alias_update_add_device(काष्ठा dasd_device *);
#पूर्ण_अगर				/* DASD_ECKD_H */
