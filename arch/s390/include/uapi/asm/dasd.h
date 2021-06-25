<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2000
 * EMC Symmetrix ioctl Copyright EMC Corporation, 2008
 * Author.........: Nigel Hislop <hislop_nigel@emc.com>
 *
 * This file is the पूर्णांकerface of the DASD device driver, which is exported to user space
 * any future changes wrt the API will result in a change of the APIVERSION reported
 * to userspace by the DASDAPIVER-ioctl
 *
 */

#अगर_अघोषित DASD_H
#घोषणा DASD_H
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा DASD_IOCTL_LETTER 'D'

#घोषणा DASD_API_VERSION 6

/*
 * काष्ठा dasd_inक्रमmation2_t
 * represents any data about the device, which is visible to userspace.
 *  including क्रमamt and featueres.
 */
प्रकार काष्ठा dasd_inक्रमmation2_t अणु
	अचिन्हित पूर्णांक devno;	    /* S/390 devno */
	अचिन्हित पूर्णांक real_devno;    /* क्रम aliases */
	अचिन्हित पूर्णांक schid;	    /* S/390 subchannel identअगरier */
	अचिन्हित पूर्णांक cu_type  : 16; /* from SenseID */
	अचिन्हित पूर्णांक cu_model :  8; /* from SenseID */
	अचिन्हित पूर्णांक dev_type : 16; /* from SenseID */
	अचिन्हित पूर्णांक dev_model : 8; /* from SenseID */
	अचिन्हित पूर्णांक खोलो_count;
	अचिन्हित पूर्णांक req_queue_len;
	अचिन्हित पूर्णांक chanq_len;     /* length of chanq */
	अक्षर type[4];		    /* from discipline.name, 'none' क्रम unknown */
	अचिन्हित पूर्णांक status;	    /* current device level */
	अचिन्हित पूर्णांक label_block;   /* where to find the VOLSER */
	अचिन्हित पूर्णांक FBA_layout;    /* fixed block size (like AIXVOL) */
	अचिन्हित पूर्णांक अक्षरacteristics_size;
	अचिन्हित पूर्णांक confdata_size;
	अक्षर अक्षरacteristics[64];   /* from पढ़ो_device_अक्षरacteristics */
	अक्षर configuration_data[256]; /* from पढ़ो_configuration_data */
	अचिन्हित पूर्णांक क्रमmat;	      /* क्रमmat info like क्रमmatted/cdl/ldl/... */
	अचिन्हित पूर्णांक features;	      /* dasd features like 'ro',...		*/
	अचिन्हित पूर्णांक reserved0;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved1;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved2;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved3;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved4;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved5;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved6;       /* reserved क्रम further use ,...		*/
	अचिन्हित पूर्णांक reserved7;       /* reserved क्रम further use ,...		*/
पूर्ण dasd_inक्रमmation2_t;

/*
 * values to be used क्रम dasd_inक्रमmation_t.क्रमmat
 * 0x00: NOT क्रमmatted
 * 0x01: Linux disc layout
 * 0x02: Common disc layout
 */
#घोषणा DASD_FORMAT_NONE 0
#घोषणा DASD_FORMAT_LDL  1
#घोषणा DASD_FORMAT_CDL  2
/*
 * values to be used क्रम dasd_inक्रमmation_t.features
 * 0x100: शेष features
 * 0x001: पढ़ोonly (ro)
 * 0x002: use diag discipline (diag)
 * 0x004: set the device initially online (पूर्णांकernal use only)
 * 0x008: enable ERP related logging
 * 0x010: allow I/O to fail on lost paths
 * 0x020: allow I/O to fail when a lock was stolen
 * 0x040: give access to raw eckd data
 * 0x080: enable discard support
 * 0x100: enable स्वतःdisable क्रम IFCC errors (शेष)
 */
#घोषणा DASD_FEATURE_READONLY	      0x001
#घोषणा DASD_FEATURE_USEDIAG	      0x002
#घोषणा DASD_FEATURE_INITIAL_ONLINE   0x004
#घोषणा DASD_FEATURE_ERPLOG	      0x008
#घोषणा DASD_FEATURE_FAILFAST	      0x010
#घोषणा DASD_FEATURE_FAILONSLCK       0x020
#घोषणा DASD_FEATURE_USERAW	      0x040
#घोषणा DASD_FEATURE_DISCARD	      0x080
#घोषणा DASD_FEATURE_PATH_AUTODISABLE 0x100
#घोषणा DASD_FEATURE_DEFAULT	      DASD_FEATURE_PATH_AUTODISABLE

#घोषणा DASD_PARTN_BITS 2

/*
 * काष्ठा dasd_inक्रमmation_t
 * represents any data about the data, which is visible to userspace
 */
प्रकार काष्ठा dasd_inक्रमmation_t अणु
	अचिन्हित पूर्णांक devno;	    /* S/390 devno */
	अचिन्हित पूर्णांक real_devno;    /* क्रम aliases */
	अचिन्हित पूर्णांक schid;	    /* S/390 subchannel identअगरier */
	अचिन्हित पूर्णांक cu_type  : 16; /* from SenseID */
	अचिन्हित पूर्णांक cu_model :  8; /* from SenseID */
	अचिन्हित पूर्णांक dev_type : 16; /* from SenseID */
	अचिन्हित पूर्णांक dev_model : 8; /* from SenseID */
	अचिन्हित पूर्णांक खोलो_count;
	अचिन्हित पूर्णांक req_queue_len;
	अचिन्हित पूर्णांक chanq_len;     /* length of chanq */
	अक्षर type[4];		    /* from discipline.name, 'none' क्रम unknown */
	अचिन्हित पूर्णांक status;	    /* current device level */
	अचिन्हित पूर्णांक label_block;   /* where to find the VOLSER */
	अचिन्हित पूर्णांक FBA_layout;    /* fixed block size (like AIXVOL) */
	अचिन्हित पूर्णांक अक्षरacteristics_size;
	अचिन्हित पूर्णांक confdata_size;
	अक्षर अक्षरacteristics[64];   /* from पढ़ो_device_अक्षरacteristics */
	अक्षर configuration_data[256]; /* from पढ़ो_configuration_data */
पूर्ण dasd_inक्रमmation_t;

/*
 * Read Subप्रणाली Data - Perक्रमmance Statistics
 */
प्रकार काष्ठा dasd_rssd_perf_stats_t अणु
	अचिन्हित अक्षर  invalid:1;
	अचिन्हित अक्षर  क्रमmat:3;
	अचिन्हित अक्षर  data_क्रमmat:4;
	अचिन्हित अक्षर  unit_address;
	अचिन्हित लघु device_status;
	अचिन्हित पूर्णांक   nr_पढ़ो_normal;
	अचिन्हित पूर्णांक   nr_पढ़ो_normal_hits;
	अचिन्हित पूर्णांक   nr_ग_लिखो_normal;
	अचिन्हित पूर्णांक   nr_ग_लिखो_fast_normal_hits;
	अचिन्हित पूर्णांक   nr_पढ़ो_seq;
	अचिन्हित पूर्णांक   nr_पढ़ो_seq_hits;
	अचिन्हित पूर्णांक   nr_ग_लिखो_seq;
	अचिन्हित पूर्णांक   nr_ग_लिखो_fast_seq_hits;
	अचिन्हित पूर्णांक   nr_पढ़ो_cache;
	अचिन्हित पूर्णांक   nr_पढ़ो_cache_hits;
	अचिन्हित पूर्णांक   nr_ग_लिखो_cache;
	अचिन्हित पूर्णांक   nr_ग_लिखो_fast_cache_hits;
	अचिन्हित पूर्णांक   nr_inhibit_cache;
	अचिन्हित पूर्णांक   nr_bybass_cache;
	अचिन्हित पूर्णांक   nr_seq_dasd_to_cache;
	अचिन्हित पूर्णांक   nr_dasd_to_cache;
	अचिन्हित पूर्णांक   nr_cache_to_dasd;
	अचिन्हित पूर्णांक   nr_delayed_fast_ग_लिखो;
	अचिन्हित पूर्णांक   nr_normal_fast_ग_लिखो;
	अचिन्हित पूर्णांक   nr_seq_fast_ग_लिखो;
	अचिन्हित पूर्णांक   nr_cache_miss;
	अचिन्हित अक्षर  status2;
	अचिन्हित पूर्णांक   nr_quick_ग_लिखो_promotes;
	अचिन्हित अक्षर  reserved;
	अचिन्हित लघु ssid;
	अचिन्हित अक्षर  reseved2[96];
पूर्ण __attribute__((packed)) dasd_rssd_perf_stats_t;

/*
 * काष्ठा profile_info_t
 * holds the profinling inक्रमmation
 */
प्रकार काष्ठा dasd_profile_info_t अणु
	अचिन्हित पूर्णांक dasd_io_reqs;	 /* number of requests processed at all */
	अचिन्हित पूर्णांक dasd_io_sects;	 /* number of sectors processed at all */
	अचिन्हित पूर्णांक dasd_io_secs[32];	 /* histogram of request's sizes */
	अचिन्हित पूर्णांक dasd_io_बार[32];	 /* histogram of requests's बार */
	अचिन्हित पूर्णांक dasd_io_timps[32];	 /* histogram of requests's बार per sector */
	अचिन्हित पूर्णांक dasd_io_समय1[32];	 /* histogram of समय from build to start */
	अचिन्हित पूर्णांक dasd_io_समय2[32];	 /* histogram of समय from start to irq */
	अचिन्हित पूर्णांक dasd_io_समय2ps[32]; /* histogram of समय from start to irq */
	अचिन्हित पूर्णांक dasd_io_समय3[32];	 /* histogram of समय from irq to end */
	अचिन्हित पूर्णांक dasd_io_nr_req[32]; /* histogram of # of requests in chanq */
पूर्ण dasd_profile_info_t;

/*
 * काष्ठा क्रमmat_data_t
 * represents all data necessary to क्रमmat a dasd
 */
प्रकार काष्ठा क्रमmat_data_t अणु
	अचिन्हित पूर्णांक start_unit; /* from track */
	अचिन्हित पूर्णांक stop_unit;  /* to track */
	अचिन्हित पूर्णांक blksize;	 /* sectorsize */
	अचिन्हित पूर्णांक पूर्णांकensity;
पूर्ण क्रमmat_data_t;

/*
 * values to be used क्रम क्रमmat_data_t.पूर्णांकensity
 * 0/8: normal क्रमmat
 * 1/9: also ग_लिखो record zero
 * 3/11: also ग_लिखो home address
 * 4/12: invalidate track
 */
#घोषणा DASD_FMT_INT_FMT_R0	1	/* ग_लिखो record zero */
#घोषणा DASD_FMT_INT_FMT_HA	2	/* ग_लिखो home address, also set FMT_R0 ! */
#घोषणा DASD_FMT_INT_INVAL	4	/* invalidate tracks */
#घोषणा DASD_FMT_INT_COMPAT	8	/* use OS/390 compatible disk layout */
#घोषणा DASD_FMT_INT_FMT_NOR0	16	/* हटाओ permission to ग_लिखो record zero */
#घोषणा DASD_FMT_INT_ESE_FULL	32	/* release space क्रम entire volume */

/*
 * काष्ठा क्रमmat_check_t
 * represents all data necessary to evaluate the क्रमmat of
 * dअगरferent tracks of a dasd
 */
प्रकार काष्ठा क्रमmat_check_t अणु
	/* Input */
	काष्ठा क्रमmat_data_t expect;

	/* Output */
	अचिन्हित पूर्णांक result;		/* Error indication (DASD_FMT_ERR_*) */
	अचिन्हित पूर्णांक unit;		/* Track that is in error */
	अचिन्हित पूर्णांक rec;		/* Record that is in error */
	अचिन्हित पूर्णांक num_records;	/* Records in the track in error */
	अचिन्हित पूर्णांक blksize;		/* Blocksize of first record in error */
	अचिन्हित पूर्णांक key_length;	/* Key length of first record in error */
पूर्ण क्रमmat_check_t;

/* Values वापसed in क्रमmat_check_t when a क्रमmat error is detected: */
/* Too few records were found on a single track */
#घोषणा DASD_FMT_ERR_TOO_FEW_RECORDS	1
/* Too many records were found on a single track */
#घोषणा DASD_FMT_ERR_TOO_MANY_RECORDS	2
/* Blocksize/data-length of a record was wrong */
#घोषणा DASD_FMT_ERR_BLKSIZE		3
/* A record ID is defined by cylinder, head, and record number (CHR). */
/* On mismatch, this error is set */
#घोषणा DASD_FMT_ERR_RECORD_ID		4
/* If key-length was != 0 */
#घोषणा DASD_FMT_ERR_KEY_LENGTH		5

/*
 * काष्ठा attrib_data_t
 * represents the operation (cache) bits क्रम the device.
 * Used in DE to influence caching of the DASD.
 */
प्रकार काष्ठा attrib_data_t अणु
	अचिन्हित अक्षर operation:3;     /* cache operation mode */
	अचिन्हित अक्षर reserved:5;      /* cache operation mode */
	__u16         nr_cyl;          /* no of cyliners क्रम पढ़ो ahaed */
	__u8          reserved2[29];   /* क्रम future use */
पूर्ण __attribute__ ((packed)) attrib_data_t;

/* definition of operation (cache) bits within attributes of DE */
#घोषणा DASD_NORMAL_CACHE  0x0
#घोषणा DASD_BYPASS_CACHE  0x1
#घोषणा DASD_INHIBIT_LOAD  0x2
#घोषणा DASD_SEQ_ACCESS    0x3
#घोषणा DASD_SEQ_PRESTAGE  0x4
#घोषणा DASD_REC_ACCESS    0x5

/*
 * Perक्रमm EMC Symmetrix I/O
 */
प्रकार काष्ठा dasd_symmio_parms अणु
	अचिन्हित अक्षर reserved[8];	/* compat with older releases */
	अचिन्हित दीर्घ दीर्घ psf_data;	/* अक्षर * cast to u64 */
	अचिन्हित दीर्घ दीर्घ rssd_result; /* अक्षर * cast to u64 */
	पूर्णांक psf_data_len;
	पूर्णांक rssd_result_len;
पूर्ण __attribute__ ((packed)) dasd_symmio_parms_t;

/*
 * Data वापसed by Sense Path Group ID (SNID)
 */
काष्ठा dasd_snid_data अणु
	काष्ठा अणु
		__u8 group:2;
		__u8 reserve:2;
		__u8 mode:1;
		__u8 res:3;
	पूर्ण __attribute__ ((packed)) path_state;
	__u8 pgid[11];
पूर्ण __attribute__ ((packed));

काष्ठा dasd_snid_ioctl_data अणु
	काष्ठा dasd_snid_data data;
	__u8 path_mask;
पूर्ण __attribute__ ((packed));


/********************************************************************************
 * SECTION: Definition of IOCTLs
 *
 * Here ist how the ioctl-nr should be used:
 *    0 -   31   DASD driver itself
 *   32 -  239   still खोलो
 *  240 -  255	 reserved क्रम EMC
 *******************************************************************************/

/* Disable the volume (क्रम Linux) */
#घोषणा BIODASDDISABLE _IO(DASD_IOCTL_LETTER,0)
/* Enable the volume (क्रम Linux) */
#घोषणा BIODASDENABLE  _IO(DASD_IOCTL_LETTER,1)
/* Issue a reserve/release command, rsp. */
#घोषणा BIODASDRSRV    _IO(DASD_IOCTL_LETTER,2) /* reserve */
#घोषणा BIODASDRLSE    _IO(DASD_IOCTL_LETTER,3) /* release */
#घोषणा BIODASDSLCK    _IO(DASD_IOCTL_LETTER,4) /* steal lock */
/* reset profiling inक्रमmation of a device */
#घोषणा BIODASDPRRST   _IO(DASD_IOCTL_LETTER,5)
/* Quiesce IO on device */
#घोषणा BIODASDQUIESCE _IO(DASD_IOCTL_LETTER,6)
/* Resume IO on device */
#घोषणा BIODASDRESUME  _IO(DASD_IOCTL_LETTER,7)
/* Abort all I/O on a device */
#घोषणा BIODASDABORTIO _IO(DASD_IOCTL_LETTER, 240)
/* Allow I/O on a device */
#घोषणा BIODASDALLOWIO _IO(DASD_IOCTL_LETTER, 241)


/* retrieve API version number */
#घोषणा DASDAPIVER     _IOR(DASD_IOCTL_LETTER,0,पूर्णांक)
/* Get inक्रमmation on a dasd device */
#घोषणा BIODASDINFO    _IOR(DASD_IOCTL_LETTER,1,dasd_inक्रमmation_t)
/* retrieve profiling inक्रमmation of a device */
#घोषणा BIODASDPRRD    _IOR(DASD_IOCTL_LETTER,2,dasd_profile_info_t)
/* Get inक्रमmation on a dasd device (enhanced) */
#घोषणा BIODASDINFO2   _IOR(DASD_IOCTL_LETTER,3,dasd_inक्रमmation2_t)
/* Perक्रमmance Statistics Read */
#घोषणा BIODASDPSRD    _IOR(DASD_IOCTL_LETTER,4,dasd_rssd_perf_stats_t)
/* Get Attributes (cache operations) */
#घोषणा BIODASDGATTR   _IOR(DASD_IOCTL_LETTER,5,attrib_data_t)


/* #घोषणा BIODASDFORMAT  _IOW(IOCTL_LETTER,0,क्रमmat_data_t) , deprecated */
#घोषणा BIODASDFMT     _IOW(DASD_IOCTL_LETTER,1,क्रमmat_data_t)
/* Set Attributes (cache operations) */
#घोषणा BIODASDSATTR   _IOW(DASD_IOCTL_LETTER,2,attrib_data_t)
/* Release Allocated Space */
#घोषणा BIODASDRAS     _IOW(DASD_IOCTL_LETTER, 3, क्रमmat_data_t)

/* Get Sense Path Group ID (SNID) data */
#घोषणा BIODASDSNID    _IOWR(DASD_IOCTL_LETTER, 1, काष्ठा dasd_snid_ioctl_data)
/* Check device क्रमmat according to क्रमmat_check_t */
#घोषणा BIODASDCHECKFMT _IOWR(DASD_IOCTL_LETTER, 2, क्रमmat_check_t)

#घोषणा BIODASDSYMMIO  _IOWR(DASD_IOCTL_LETTER, 240, dasd_symmio_parms_t)

#पूर्ण_अगर				/* DASD_H */

