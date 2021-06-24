<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2009
 */

#अगर_अघोषित DASD_INT_H
#घोषणा DASD_INT_H

/* we keep old device allocation scheme; IOW, minors are still in 0..255 */
#घोषणा DASD_PER_MAJOR (1U << (MINORBITS - DASD_PARTN_BITS))
#घोषणा DASD_PARTN_MASK ((1 << DASD_PARTN_BITS) - 1)

/*
 * States a dasd device can have:
 *   new: the dasd_device काष्ठाure is allocated.
 *   known: the discipline क्रम the device is identअगरied.
 *   basic: the device can करो basic i/o.
 *   unfmt: the device could not be analyzed (क्रमmat is unknown).
 *   पढ़ोy: partition detection is करोne and the device is can करो block io.
 *   online: the device accepts requests from the block device queue.
 *
 * Things to करो क्रम startup state transitions:
 *   new -> known: find discipline क्रम the device and create devfs entries.
 *   known -> basic: request irq line क्रम the device.
 *   basic -> पढ़ोy: करो the initial analysis, e.g. क्रमmat detection,
 *                   करो block device setup and detect partitions.
 *   पढ़ोy -> online: schedule the device tasklet.
 * Things to करो क्रम shutकरोwn state transitions:
 *   online -> पढ़ोy: just set the new device state.
 *   पढ़ोy -> basic: flush requests from the block device layer, clear
 *                   partition inक्रमmation and reset क्रमmat inक्रमmation.
 *   basic -> known: terminate all requests and मुक्त irq.
 *   known -> new: हटाओ devfs entries and क्रमget discipline.
 */

#घोषणा DASD_STATE_NEW	  0
#घोषणा DASD_STATE_KNOWN  1
#घोषणा DASD_STATE_BASIC  2
#घोषणा DASD_STATE_UNFMT  3
#घोषणा DASD_STATE_READY  4
#घोषणा DASD_STATE_ONLINE 5

#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/genhd.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <linux/workqueue.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/dasd.h>
#समावेश <यंत्र/idals.h>
#समावेश <linux/bitops.h>
#समावेश <linux/blk-mq.h>

/* DASD discipline magic */
#घोषणा DASD_ECKD_MAGIC 0xC5C3D2C4
#घोषणा DASD_DIAG_MAGIC 0xC4C9C1C7
#घोषणा DASD_FBA_MAGIC 0xC6C2C140

/*
 * SECTION: Type definitions
 */
काष्ठा dasd_device;
काष्ठा dasd_block;

/* BIT DEFINITIONS FOR SENSE DATA */
#घोषणा DASD_SENSE_BIT_0 0x80
#घोषणा DASD_SENSE_BIT_1 0x40
#घोषणा DASD_SENSE_BIT_2 0x20
#घोषणा DASD_SENSE_BIT_3 0x10

/* BIT DEFINITIONS FOR SIM SENSE */
#घोषणा DASD_SIM_SENSE 0x0F
#घोषणा DASD_SIM_MSG_TO_OP 0x03
#घोषणा DASD_SIM_LOG 0x0C

/* lock class क्रम nested cdev lock */
#घोषणा CDEV_NESTED_FIRST 1
#घोषणा CDEV_NESTED_SECOND 2

/*
 * SECTION: MACROs क्रम klogd and s390 debug feature (dbf)
 */
#घोषणा DBF_DEV_EVENT(d_level, d_device, d_str, d_data...) \
करो अणु \
	debug_प्र_लिखो_event(d_device->debug_area, \
			    d_level, \
			    d_str "\n", \
			    d_data); \
पूर्ण जबतक(0)

#घोषणा DBF_EVENT(d_level, d_str, d_data...)\
करो अणु \
	debug_प्र_लिखो_event(dasd_debug_area, \
			    d_level,\
			    d_str "\n", \
			    d_data); \
पूर्ण जबतक(0)

#घोषणा DBF_EVENT_DEVID(d_level, d_cdev, d_str, d_data...)	\
करो अणु \
	काष्ठा ccw_dev_id __dev_id;			\
	ccw_device_get_id(d_cdev, &__dev_id);		\
	debug_प्र_लिखो_event(dasd_debug_area,		\
			    d_level,					\
			    "0.%x.%04x " d_str "\n",			\
			    __dev_id.ssid, __dev_id.devno, d_data);	\
पूर्ण जबतक (0)

/* limit size क्रम an errorstring */
#घोषणा ERRORLENGTH 30

/* definition of dbf debug levels */
#घोषणा	DBF_EMERG	0	/* प्रणाली is unusable			*/
#घोषणा	DBF_ALERT	1	/* action must be taken immediately	*/
#घोषणा	DBF_CRIT	2	/* critical conditions			*/
#घोषणा	DBF_ERR		3	/* error conditions			*/
#घोषणा	DBF_WARNING	4	/* warning conditions			*/
#घोषणा	DBF_NOTICE	5	/* normal but signअगरicant condition	*/
#घोषणा	DBF_INFO	6	/* inक्रमmational			*/
#घोषणा	DBF_DEBUG	6	/* debug-level messages			*/

/* messages to be written via klogd and dbf */
#घोषणा DEV_MESSAGE(d_loglevel,d_device,d_string,d_args...)\
करो अणु \
	prपूर्णांकk(d_loglevel PRINTK_HEADER " %s: " d_string "\n", \
	       dev_name(&d_device->cdev->dev), d_args); \
	DBF_DEV_EVENT(DBF_ALERT, d_device, d_string, d_args); \
पूर्ण जबतक(0)

#घोषणा MESSAGE(d_loglevel,d_string,d_args...)\
करो अणु \
	prपूर्णांकk(d_loglevel PRINTK_HEADER " " d_string "\n", d_args); \
	DBF_EVENT(DBF_ALERT, d_string, d_args); \
पूर्ण जबतक(0)

/* messages to be written via klogd only */
#घोषणा DEV_MESSAGE_LOG(d_loglevel,d_device,d_string,d_args...)\
करो अणु \
	prपूर्णांकk(d_loglevel PRINTK_HEADER " %s: " d_string "\n", \
	       dev_name(&d_device->cdev->dev), d_args); \
पूर्ण जबतक(0)

#घोषणा MESSAGE_LOG(d_loglevel,d_string,d_args...)\
करो अणु \
	prपूर्णांकk(d_loglevel PRINTK_HEADER " " d_string "\n", d_args); \
पूर्ण जबतक(0)

/* Macro to calculate number of blocks per page */
#घोषणा BLOCKS_PER_PAGE(blksize) (PAGE_SIZE / blksize)

काष्ठा dasd_ccw_req अणु
	अचिन्हित पूर्णांक magic;		/* Eye catcher */
	पूर्णांक पूर्णांकrc;			/* पूर्णांकernal error, e.g. from start_IO */
	काष्ठा list_head devlist;	/* क्रम dasd_device request queue */
	काष्ठा list_head blocklist;	/* क्रम dasd_block request queue */
	काष्ठा dasd_block *block;	/* the originating block device */
	काष्ठा dasd_device *memdev;	/* the device used to allocate this */
	काष्ठा dasd_device *startdev;	/* device the request is started on */
	काष्ठा dasd_device *basedev;	/* base device अगर no block->base */
	व्योम *cpaddr;			/* address of ccw or tcw */
	लघु retries;			/* A retry counter */
	अचिन्हित अक्षर cpmode;		/* 0 = cmd mode, 1 = itcw */
	अक्षर status;			/* status of this request */
	अक्षर lpm;			/* logical path mask */
	अचिन्हित दीर्घ flags;        	/* flags of this request */
	काष्ठा dasd_queue *dq;
	अचिन्हित दीर्घ startसमय;	/* jअगरfies समय of request start */
	अचिन्हित दीर्घ expires;		/* expiration period in jअगरfies */
	व्योम *data;			/* poपूर्णांकer to data area */
	काष्ठा irb irb;			/* device status in हाल of an error */
	काष्ठा dasd_ccw_req *refers;	/* ERP-chain queueing. */
	व्योम *function; 		/* originating ERP action */
	व्योम *mem_chunk;

	अचिन्हित दीर्घ buildclk;		/* TOD-घड़ी of request generation */
	अचिन्हित दीर्घ startclk;		/* TOD-घड़ी of request start */
	अचिन्हित दीर्घ stopclk;		/* TOD-घड़ी of request पूर्णांकerrupt */
	अचिन्हित दीर्घ endclk;		/* TOD-घड़ी of request termination */

	व्योम (*callback)(काष्ठा dasd_ccw_req *, व्योम *data);
	व्योम *callback_data;
	अचिन्हित पूर्णांक proc_bytes;	/* bytes क्रम partial completion */
पूर्ण;

/*
 * dasd_ccw_req -> status can be:
 */
#घोषणा DASD_CQR_FILLED 	0x00	/* request is पढ़ोy to be processed */
#घोषणा DASD_CQR_DONE		0x01	/* request is completed successfully */
#घोषणा DASD_CQR_NEED_ERP	0x02	/* request needs recovery action */
#घोषणा DASD_CQR_IN_ERP 	0x03	/* request is in recovery */
#घोषणा DASD_CQR_FAILED 	0x04	/* request is finally failed */
#घोषणा DASD_CQR_TERMINATED	0x05	/* request was stopped by driver */

#घोषणा DASD_CQR_QUEUED 	0x80	/* request is queued to be processed */
#घोषणा DASD_CQR_IN_IO		0x81	/* request is currently in IO */
#घोषणा DASD_CQR_ERROR		0x82	/* request is completed with error */
#घोषणा DASD_CQR_CLEAR_PENDING	0x83	/* request is clear pending */
#घोषणा DASD_CQR_CLEARED	0x84	/* request was cleared */
#घोषणा DASD_CQR_SUCCESS	0x85	/* request was successful */

/* शेष expiration समय*/
#घोषणा DASD_EXPIRES	  300
#घोषणा DASD_EXPIRES_MAX  40000000
#घोषणा DASD_RETRIES	  256
#घोषणा DASD_RETRIES_MAX  32768

/* per dasd_ccw_req flags */
#घोषणा DASD_CQR_FLAGS_USE_ERP   0	/* use ERP क्रम this request */
#घोषणा DASD_CQR_FLAGS_FAILFAST  1	/* FAILFAST */
#घोषणा DASD_CQR_VERIFY_PATH	 2	/* path verअगरication request */
#घोषणा DASD_CQR_ALLOW_SLOCK	 3	/* Try this request even when lock was
					 * stolen. Should not be combined with
					 * DASD_CQR_FLAGS_USE_ERP
					 */
/*
 * The following flags are used to suppress output of certain errors.
 */
#घोषणा DASD_CQR_SUPPRESS_NRF	4	/* Suppress 'No Record Found' error */
#घोषणा DASD_CQR_SUPPRESS_FP	5	/* Suppress 'File Protected' error*/
#घोषणा DASD_CQR_SUPPRESS_IL	6	/* Suppress 'Incorrect Length' error */
#घोषणा DASD_CQR_SUPPRESS_CR	7	/* Suppress 'Command Reject' error */

#घोषणा DASD_REQ_PER_DEV 4

/* Signature क्रम error recovery functions. */
प्रकार काष्ठा dasd_ccw_req *(*dasd_erp_fn_t) (काष्ठा dasd_ccw_req *);

/*
 * A single CQR can only contain a maximum of 255 CCWs. It is limited by
 * the locate record and locate record extended count value which can only hold
 * 1 Byte max.
 */
#घोषणा DASD_CQR_MAX_CCW 255

/*
 * Unique identअगरier क्रम dasd device.
 */
#घोषणा UA_NOT_CONFIGURED  0x00
#घोषणा UA_BASE_DEVICE	   0x01
#घोषणा UA_BASE_PAV_ALIAS  0x02
#घोषणा UA_HYPER_PAV_ALIAS 0x03

काष्ठा dasd_uid अणु
	__u8 type;
	अक्षर venकरोr[4];
	अक्षर serial[15];
	__u16 ssid;
	__u8 real_unit_addr;
	__u8 base_unit_addr;
	अक्षर vduit[33];
पूर्ण;

/*
 * the काष्ठा dasd_discipline is
 * sth like a table of भव functions, अगर you think of dasd_eckd
 * inheriting dasd...
 * no, currently we are not planning to reimplement the driver in C++
 */
काष्ठा dasd_discipline अणु
	काष्ठा module *owner;
	अक्षर ebcname[8];	/* a name used क्रम tagging and prपूर्णांकks */
	अक्षर name[8];		/* a name used क्रम tagging and prपूर्णांकks */

	काष्ठा list_head list;	/* used क्रम list of disciplines */

	/*
	 * Device recognition functions. check_device is used to verअगरy
	 * the sense data and the inक्रमmation वापसed by पढ़ो device
	 * अक्षरacteristics. It वापसs 0 अगर the discipline can be used
	 * क्रम the device in question. uncheck_device is called during
	 * device shutकरोwn to deरेजिस्टर a device from its discipline.
	 */
	पूर्णांक (*check_device) (काष्ठा dasd_device *);
	व्योम (*uncheck_device) (काष्ठा dasd_device *);

	/*
	 * करो_analysis is used in the step from device state "basic" to
	 * state "accept". It वापसs 0 अगर the device can be made पढ़ोy,
	 * it वापसs -EMEDIUMTYPE अगर the device can't be made पढ़ोy or
	 * -EAGAIN अगर करो_analysis started a ccw that needs to complete
	 * beक्रमe the analysis may be repeated.
	 */
	पूर्णांक (*करो_analysis) (काष्ठा dasd_block *);

	/*
	 * This function is called, when new paths become available.
	 * Disciplins may use this callback to करो necessary setup work,
	 * e.g. verअगरy that new path is compatible with the current
	 * configuration.
	 */
	पूर्णांक (*pe_handler)(काष्ठा dasd_device *, __u8, __u8);

	/*
	 * Last things to करो when a device is set online, and first things
	 * when it is set offline.
	 */
	पूर्णांक (*basic_to_पढ़ोy) (काष्ठा dasd_device *);
	पूर्णांक (*online_to_पढ़ोy) (काष्ठा dasd_device *);
	पूर्णांक (*basic_to_known)(काष्ठा dasd_device *);

	/*
	 * Initialize block layer request queue.
	 */
	व्योम (*setup_blk_queue)(काष्ठा dasd_block *);
	/* (काष्ठा dasd_device *);
	 * Device operation functions. build_cp creates a ccw chain क्रम
	 * a block device request, start_io starts the request and
	 * term_IO cancels it (e.g. in हाल of a समयout). क्रमmat_device
	 * क्रमmats the device and check_device_क्रमmat compares the क्रमmat of
	 * a device with the expected क्रमmat_data.
	 * handle_terminated_request allows to examine a cqr and prepare
	 * it क्रम retry.
	 */
	काष्ठा dasd_ccw_req *(*build_cp) (काष्ठा dasd_device *,
					  काष्ठा dasd_block *,
					  काष्ठा request *);
	पूर्णांक (*start_IO) (काष्ठा dasd_ccw_req *);
	पूर्णांक (*term_IO) (काष्ठा dasd_ccw_req *);
	व्योम (*handle_terminated_request) (काष्ठा dasd_ccw_req *);
	पूर्णांक (*क्रमmat_device) (काष्ठा dasd_device *,
			      काष्ठा क्रमmat_data_t *, पूर्णांक);
	पूर्णांक (*check_device_क्रमmat)(काष्ठा dasd_device *,
				   काष्ठा क्रमmat_check_t *, पूर्णांक);
	पूर्णांक (*मुक्त_cp) (काष्ठा dasd_ccw_req *, काष्ठा request *);

	/*
	 * Error recovery functions. examine_error() वापसs a value that
	 * indicates what to करो क्रम an error condition. If examine_error()
	 * वापसs 'dasd_era_recover' erp_action() is called to create a
	 * special error recovery ccw. erp_postaction() is called after
	 * an error recovery ccw has finished its execution. dump_sense
	 * is called क्रम every error condition to prपूर्णांक the sense data
	 * to the console.
	 */
	dasd_erp_fn_t(*erp_action) (काष्ठा dasd_ccw_req *);
	dasd_erp_fn_t(*erp_postaction) (काष्ठा dasd_ccw_req *);
	व्योम (*dump_sense) (काष्ठा dasd_device *, काष्ठा dasd_ccw_req *,
			    काष्ठा irb *);
	व्योम (*dump_sense_dbf) (काष्ठा dasd_device *, काष्ठा irb *, अक्षर *);
	व्योम (*check_क्रम_device_change) (काष्ठा dasd_device *,
					 काष्ठा dasd_ccw_req *,
					 काष्ठा irb *);

        /* i/o control functions. */
	पूर्णांक (*fill_geometry) (काष्ठा dasd_block *, काष्ठा hd_geometry *);
	पूर्णांक (*fill_info) (काष्ठा dasd_device *, काष्ठा dasd_inक्रमmation2_t *);
	पूर्णांक (*ioctl) (काष्ठा dasd_block *, अचिन्हित पूर्णांक, व्योम __user *);

	/* reload device after state change */
	पूर्णांक (*reload) (काष्ठा dasd_device *);

	पूर्णांक (*get_uid) (काष्ठा dasd_device *, काष्ठा dasd_uid *);
	व्योम (*kick_validate) (काष्ठा dasd_device *);
	पूर्णांक (*check_attention)(काष्ठा dasd_device *, __u8);
	पूर्णांक (*host_access_count)(काष्ठा dasd_device *);
	पूर्णांक (*hosts_prपूर्णांक)(काष्ठा dasd_device *, काष्ठा seq_file *);
	व्योम (*handle_hpf_error)(काष्ठा dasd_device *, काष्ठा irb *);
	व्योम (*disable_hpf)(काष्ठा dasd_device *);
	पूर्णांक (*hpf_enabled)(काष्ठा dasd_device *);
	व्योम (*reset_path)(काष्ठा dasd_device *, __u8);

	/*
	 * Extent Space Efficient (ESE) relevant functions
	 */
	पूर्णांक (*is_ese)(काष्ठा dasd_device *);
	/* Capacity */
	पूर्णांक (*space_allocated)(काष्ठा dasd_device *);
	पूर्णांक (*space_configured)(काष्ठा dasd_device *);
	पूर्णांक (*logical_capacity)(काष्ठा dasd_device *);
	पूर्णांक (*release_space)(काष्ठा dasd_device *, काष्ठा क्रमmat_data_t *);
	/* Extent Pool */
	पूर्णांक (*ext_pool_id)(काष्ठा dasd_device *);
	पूर्णांक (*ext_size)(काष्ठा dasd_device *);
	पूर्णांक (*ext_pool_cap_at_warnlevel)(काष्ठा dasd_device *);
	पूर्णांक (*ext_pool_warn_thrshld)(काष्ठा dasd_device *);
	पूर्णांक (*ext_pool_oos)(काष्ठा dasd_device *);
	पूर्णांक (*ext_pool_exhaust)(काष्ठा dasd_device *, काष्ठा dasd_ccw_req *);
	काष्ठा dasd_ccw_req *(*ese_क्रमmat)(काष्ठा dasd_device *,
					   काष्ठा dasd_ccw_req *, काष्ठा irb *);
	पूर्णांक (*ese_पढ़ो)(काष्ठा dasd_ccw_req *, काष्ठा irb *);
पूर्ण;

बाह्य काष्ठा dasd_discipline *dasd_diag_discipline_poपूर्णांकer;

/*
 * Notअगरication numbers क्रम extended error reporting notअगरications:
 * The DASD_EER_DISABLE notअगरication is sent beक्रमe a dasd_device (and it's
 * eer poपूर्णांकer) is मुक्तd. The error reporting module needs to करो all necessary
 * cleanup steps.
 * The DASD_EER_TRIGGER notअगरication sends the actual error reports (triggers).
 */
#घोषणा DASD_EER_DISABLE 0
#घोषणा DASD_EER_TRIGGER 1

/* Trigger IDs क्रम extended error reporting DASD_EER_TRIGGER notअगरication */
#घोषणा DASD_EER_FATALERROR  1
#घोषणा DASD_EER_NOPATH      2
#घोषणा DASD_EER_STATECHANGE 3
#घोषणा DASD_EER_PPRCSUSPEND 4
#घोषणा DASD_EER_NOSPC	     5

/* DASD path handling */

#घोषणा DASD_PATH_OPERATIONAL  1
#घोषणा DASD_PATH_TBV	       2
#घोषणा DASD_PATH_PP	       3
#घोषणा DASD_PATH_NPP	       4
#घोषणा DASD_PATH_MISCABLED    5
#घोषणा DASD_PATH_NOHPF        6
#घोषणा DASD_PATH_CUIR	       7
#घोषणा DASD_PATH_IFCC	       8
#घोषणा DASD_PATH_FCSEC	       9

#घोषणा DASD_THRHLD_MAX		4294967295U
#घोषणा DASD_INTERVAL_MAX	4294967295U

/* FC Endpoपूर्णांक Security Capabilities */
#घोषणा DASD_FC_SECURITY_UNSUP		0
#घोषणा DASD_FC_SECURITY_AUTH		1
#घोषणा DASD_FC_SECURITY_ENC_FCSP2	2
#घोषणा DASD_FC_SECURITY_ENC_ERAS	3

#घोषणा DASD_FC_SECURITY_ENC_STR	"Encryption"
अटल स्थिर काष्ठा अणु
	u8 value;
	अक्षर *name;
पूर्ण dasd_path_fcs_mnemonics[] = अणु
	अणु DASD_FC_SECURITY_UNSUP,	"Unsupported" पूर्ण,
	अणु DASD_FC_SECURITY_AUTH,	"Authentication" पूर्ण,
	अणु DASD_FC_SECURITY_ENC_FCSP2,	DASD_FC_SECURITY_ENC_STR पूर्ण,
	अणु DASD_FC_SECURITY_ENC_ERAS,	DASD_FC_SECURITY_ENC_STR पूर्ण,
पूर्ण;

अटल अंतरभूत अक्षर *dasd_path_get_fcs_str(पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dasd_path_fcs_mnemonics); i++) अणु
		अगर (dasd_path_fcs_mnemonics[i].value == val)
			वापस dasd_path_fcs_mnemonics[i].name;
	पूर्ण

	वापस dasd_path_fcs_mnemonics[0].name;
पूर्ण

काष्ठा dasd_path अणु
	अचिन्हित दीर्घ flags;
	u8 cssid;
	u8 ssid;
	u8 chpid;
	काष्ठा dasd_conf_data *conf_data;
	atomic_t error_count;
	अचिन्हित दीर्घ errorclk;
	u8 fc_security;
	काष्ठा kobject kobj;
	bool in_sysfs;
पूर्ण;

#घोषणा to_dasd_path(path) container_of(path, काष्ठा dasd_path, kobj)

अटल अंतरभूत व्योम dasd_path_release(काष्ठा kobject *kobj)
अणु
/* Memory क्रम the dasd_path kobject is मुक्तd when dasd_मुक्त_device() is called */
पूर्ण


काष्ठा dasd_profile_info अणु
	/* legacy part of profile data, as in dasd_profile_info_t */
	अचिन्हित पूर्णांक dasd_io_reqs;	 /* number of requests processed */
	अचिन्हित पूर्णांक dasd_io_sects;	 /* number of sectors processed */
	अचिन्हित पूर्णांक dasd_io_secs[32];	 /* histogram of request's sizes */
	अचिन्हित पूर्णांक dasd_io_बार[32];	 /* histogram of requests's बार */
	अचिन्हित पूर्णांक dasd_io_timps[32];	 /* h. of requests's बार per sector */
	अचिन्हित पूर्णांक dasd_io_समय1[32];	 /* hist. of समय from build to start */
	अचिन्हित पूर्णांक dasd_io_समय2[32];	 /* hist. of समय from start to irq */
	अचिन्हित पूर्णांक dasd_io_समय2ps[32]; /* hist. of समय from start to irq */
	अचिन्हित पूर्णांक dasd_io_समय3[32];	 /* hist. of समय from irq to end */
	अचिन्हित पूर्णांक dasd_io_nr_req[32]; /* hist. of # of requests in chanq */

	/* new data */
	काष्ठा बारpec64 starttod;	   /* समय of start or last reset */
	अचिन्हित पूर्णांक dasd_io_alias;	   /* requests using an alias */
	अचिन्हित पूर्णांक dasd_io_tpm;	   /* requests using transport mode */
	अचिन्हित पूर्णांक dasd_पढ़ो_reqs;	   /* total number of पढ़ो  requests */
	अचिन्हित पूर्णांक dasd_पढ़ो_sects;	   /* total number पढ़ो sectors */
	अचिन्हित पूर्णांक dasd_पढ़ो_alias;	   /* पढ़ो request using an alias */
	अचिन्हित पूर्णांक dasd_पढ़ो_tpm;	   /* पढ़ो requests in transport mode */
	अचिन्हित पूर्णांक dasd_पढ़ो_secs[32];   /* histogram of request's sizes */
	अचिन्हित पूर्णांक dasd_पढ़ो_बार[32];  /* histogram of requests's बार */
	अचिन्हित पूर्णांक dasd_पढ़ो_समय1[32];  /* hist. समय from build to start */
	अचिन्हित पूर्णांक dasd_पढ़ो_समय2[32];  /* hist. of समय from start to irq */
	अचिन्हित पूर्णांक dasd_पढ़ो_समय3[32];  /* hist. of समय from irq to end */
	अचिन्हित पूर्णांक dasd_पढ़ो_nr_req[32]; /* hist. of # of requests in chanq */
	अचिन्हित दीर्घ dasd_sum_बार;	   /* sum of request बार */
	अचिन्हित दीर्घ dasd_sum_समय_str;   /* sum of समय from build to start */
	अचिन्हित दीर्घ dasd_sum_समय_irq;   /* sum of समय from start to irq */
	अचिन्हित दीर्घ dasd_sum_समय_end;   /* sum of समय from irq to end */
पूर्ण;

काष्ठा dasd_profile अणु
	काष्ठा dentry *dentry;
	काष्ठा dasd_profile_info *data;
	spinlock_t lock;
पूर्ण;

काष्ठा dasd_क्रमmat_entry अणु
	काष्ठा list_head list;
	sector_t track;
पूर्ण;

काष्ठा dasd_device अणु
	/* Block device stuff. */
	काष्ठा dasd_block *block;

        अचिन्हित पूर्णांक devindex;
	अचिन्हित दीर्घ flags;	   /* per device flags */
	अचिन्हित लघु features;   /* copy of devmap-features (पढ़ो-only!) */

	/* extended error reporting stuff (eer) */
	काष्ठा dasd_ccw_req *eer_cqr;

	/* Device discipline stuff. */
	काष्ठा dasd_discipline *discipline;
	काष्ठा dasd_discipline *base_discipline;
	व्योम *निजी;
	काष्ठा dasd_path path[8];
	__u8 opm;

	/* Device state and target state. */
	पूर्णांक state, target;
	काष्ठा mutex state_mutex;
	पूर्णांक stopped;		/* device (ccw_device_start) was stopped */

	/* reference count. */
        atomic_t ref_count;

	/* ccw queue and memory क्रम अटल ccw/erp buffers. */
	काष्ठा list_head ccw_queue;
	spinlock_t mem_lock;
	व्योम *ccw_mem;
	व्योम *erp_mem;
	व्योम *ese_mem;
	काष्ठा list_head ccw_chunks;
	काष्ठा list_head erp_chunks;
	काष्ठा list_head ese_chunks;

	atomic_t tasklet_scheduled;
        काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा work_काष्ठा kick_work;
	काष्ठा work_काष्ठा reload_device;
	काष्ठा work_काष्ठा kick_validate;
	काष्ठा work_काष्ठा suc_work;
	काष्ठा work_काष्ठा requeue_requests;
	काष्ठा समयr_list समयr;

	debug_info_t *debug_area;

	काष्ठा ccw_device *cdev;

	/* hook क्रम alias management */
	काष्ठा list_head alias_list;

	/* शेष expiration समय in s */
	अचिन्हित दीर्घ शेष_expires;
	अचिन्हित दीर्घ शेष_retries;

	अचिन्हित दीर्घ blk_समयout;

	अचिन्हित दीर्घ path_thrhld;
	अचिन्हित दीर्घ path_पूर्णांकerval;

	काष्ठा dentry *debugfs_dentry;
	काष्ठा dentry *hosts_dentry;
	काष्ठा dasd_profile profile;
	काष्ठा dasd_क्रमmat_entry क्रमmat_entry;
	काष्ठा kset *paths_info;
पूर्ण;

काष्ठा dasd_block अणु
	/* Block device stuff. */
	काष्ठा gendisk *gdp;
	काष्ठा request_queue *request_queue;
	spinlock_t request_queue_lock;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा block_device *bdev;
	atomic_t खोलो_count;

	अचिन्हित दीर्घ blocks;	   /* size of volume in blocks */
	अचिन्हित पूर्णांक bp_block;	   /* bytes per block */
	अचिन्हित पूर्णांक s2b_shअगरt;	   /* log2 (bp_block/512) */

	काष्ठा dasd_device *base;
	काष्ठा list_head ccw_queue;
	spinlock_t queue_lock;

	atomic_t tasklet_scheduled;
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा समयr_list समयr;

	काष्ठा dentry *debugfs_dentry;
	काष्ठा dasd_profile profile;

	काष्ठा list_head क्रमmat_list;
	spinlock_t क्रमmat_lock;
पूर्ण;

काष्ठा dasd_attention_data अणु
	काष्ठा dasd_device *device;
	__u8 lpum;
पूर्ण;

काष्ठा dasd_queue अणु
	spinlock_t lock;
पूर्ण;

/* reasons why device (ccw_device_start) was stopped */
#घोषणा DASD_STOPPED_NOT_ACC 1         /* not accessible */
#घोषणा DASD_STOPPED_QUIESCE 2         /* Quiesced */
#घोषणा DASD_STOPPED_PENDING 4         /* दीर्घ busy */
#घोषणा DASD_STOPPED_DC_WAIT 8         /* disconnected, रुको */
#घोषणा DASD_STOPPED_SU      16        /* summary unit check handling */
#घोषणा DASD_STOPPED_NOSPC   128       /* no space left */

/* per device flags */
#घोषणा DASD_FLAG_OFFLINE	3	/* device is in offline processing */
#घोषणा DASD_FLAG_EER_SNSS	4	/* A SNSS is required */
#घोषणा DASD_FLAG_EER_IN_USE	5	/* A SNSS request is running */
#घोषणा DASD_FLAG_DEVICE_RO	6	/* The device itself is पढ़ो-only. Don't
					 * confuse this with the user specअगरied
					 * पढ़ो-only feature.
					 */
#घोषणा DASD_FLAG_IS_RESERVED	7	/* The device is reserved */
#घोषणा DASD_FLAG_LOCK_STOLEN	8	/* The device lock was stolen */
#घोषणा DASD_FLAG_SUSPENDED	9	/* The device was suspended */
#घोषणा DASD_FLAG_SAFE_OFFLINE	10	/* safe offline processing requested*/
#घोषणा DASD_FLAG_SAFE_OFFLINE_RUNNING	11	/* safe offline running */
#घोषणा DASD_FLAG_ABORTALL	12	/* Abort all noretry requests */
#घोषणा DASD_FLAG_PATH_VERIFY	13	/* Path verअगरication worker running */
#घोषणा DASD_FLAG_SUC		14	/* unhandled summary unit check */

#घोषणा DASD_SLEEPON_START_TAG	((व्योम *) 1)
#घोषणा DASD_SLEEPON_END_TAG	((व्योम *) 2)

व्योम dasd_put_device_wake(काष्ठा dasd_device *);

/*
 * Reference count अंतरभूतrs
 */
अटल अंतरभूत व्योम
dasd_get_device(काष्ठा dasd_device *device)
अणु
	atomic_inc(&device->ref_count);
पूर्ण

अटल अंतरभूत व्योम
dasd_put_device(काष्ठा dasd_device *device)
अणु
	अगर (atomic_dec_वापस(&device->ref_count) == 0)
		dasd_put_device_wake(device);
पूर्ण

/*
 * The अटल memory in ccw_mem and erp_mem is managed by a sorted
 * list of मुक्त memory chunks.
 */
काष्ठा dasd_mchunk
अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ size;
पूर्ण __attribute__ ((aligned(8)));

अटल अंतरभूत व्योम
dasd_init_chunklist(काष्ठा list_head *chunk_list, व्योम *mem,
		    अचिन्हित दीर्घ size)
अणु
	काष्ठा dasd_mchunk *chunk;

	INIT_LIST_HEAD(chunk_list);
	chunk = (काष्ठा dasd_mchunk *) mem;
	chunk->size = size - माप(काष्ठा dasd_mchunk);
	list_add(&chunk->list, chunk_list);
पूर्ण

अटल अंतरभूत व्योम *
dasd_alloc_chunk(काष्ठा list_head *chunk_list, अचिन्हित दीर्घ size)
अणु
	काष्ठा dasd_mchunk *chunk, *पंचांगp;

	size = (size + 7L) & -8L;
	list_क्रम_each_entry(chunk, chunk_list, list) अणु
		अगर (chunk->size < size)
			जारी;
		अगर (chunk->size > size + माप(काष्ठा dasd_mchunk)) अणु
			अक्षर *endaddr = (अक्षर *) (chunk + 1) + chunk->size;
			पंचांगp = (काष्ठा dasd_mchunk *) (endaddr - size) - 1;
			पंचांगp->size = size;
			chunk->size -= size + माप(काष्ठा dasd_mchunk);
			chunk = पंचांगp;
		पूर्ण अन्यथा
			list_del(&chunk->list);
		वापस (व्योम *) (chunk + 1);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
dasd_मुक्त_chunk(काष्ठा list_head *chunk_list, व्योम *mem)
अणु
	काष्ठा dasd_mchunk *chunk, *पंचांगp;
	काष्ठा list_head *p, *left;

	chunk = (काष्ठा dasd_mchunk *)
		((अक्षर *) mem - माप(काष्ठा dasd_mchunk));
	/* Find out the left neighbour in chunk_list. */
	left = chunk_list;
	list_क्रम_each(p, chunk_list) अणु
		अगर (list_entry(p, काष्ठा dasd_mchunk, list) > chunk)
			अवरोध;
		left = p;
	पूर्ण
	/* Try to merge with right neighbour = next element from left. */
	अगर (left->next != chunk_list) अणु
		पंचांगp = list_entry(left->next, काष्ठा dasd_mchunk, list);
		अगर ((अक्षर *) (chunk + 1) + chunk->size == (अक्षर *) पंचांगp) अणु
			list_del(&पंचांगp->list);
			chunk->size += पंचांगp->size + माप(काष्ठा dasd_mchunk);
		पूर्ण
	पूर्ण
	/* Try to merge with left neighbour. */
	अगर (left != chunk_list) अणु
		पंचांगp = list_entry(left, काष्ठा dasd_mchunk, list);
		अगर ((अक्षर *) (पंचांगp + 1) + पंचांगp->size == (अक्षर *) chunk) अणु
			पंचांगp->size += chunk->size + माप(काष्ठा dasd_mchunk);
			वापस;
		पूर्ण
	पूर्ण
	__list_add(&chunk->list, left, left->next);
पूर्ण

/*
 * Check अगर bsize is in अणु 512, 1024, 2048, 4096 पूर्ण
 */
अटल अंतरभूत पूर्णांक
dasd_check_blocksize(पूर्णांक bsize)
अणु
	अगर (bsize < 512 || bsize > 4096 || !is_घातer_of_2(bsize))
		वापस -EMEDIUMTYPE;
	वापस 0;
पूर्ण

/* बाह्यals in dasd.c */
#घोषणा DASD_PROखाता_OFF	 0
#घोषणा DASD_PROखाता_ON 	 1
#घोषणा DASD_PROखाता_GLOBAL_ONLY 2

बाह्य debug_info_t *dasd_debug_area;
बाह्य काष्ठा dasd_profile dasd_global_profile;
बाह्य अचिन्हित पूर्णांक dasd_global_profile_level;
बाह्य स्थिर काष्ठा block_device_operations dasd_device_operations;

बाह्य काष्ठा kmem_cache *dasd_page_cache;

काष्ठा dasd_ccw_req *
dasd_sदो_स्मृति_request(पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा dasd_device *, काष्ठा dasd_ccw_req *);
काष्ठा dasd_ccw_req *dasd_fदो_स्मृति_request(पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा dasd_device *);
व्योम dasd_sमुक्त_request(काष्ठा dasd_ccw_req *, काष्ठा dasd_device *);
व्योम dasd_fमुक्त_request(काष्ठा dasd_ccw_req *, काष्ठा dasd_device *);
व्योम dasd_wakeup_cb(काष्ठा dasd_ccw_req *, व्योम *);

काष्ठा dasd_device *dasd_alloc_device(व्योम);
व्योम dasd_मुक्त_device(काष्ठा dasd_device *);

काष्ठा dasd_block *dasd_alloc_block(व्योम);
व्योम dasd_मुक्त_block(काष्ठा dasd_block *);

क्रमागत blk_eh_समयr_वापस dasd_बार_out(काष्ठा request *req, bool reserved);

व्योम dasd_enable_device(काष्ठा dasd_device *);
व्योम dasd_set_target_state(काष्ठा dasd_device *, पूर्णांक);
व्योम dasd_kick_device(काष्ठा dasd_device *);
व्योम dasd_reload_device(काष्ठा dasd_device *);
व्योम dasd_schedule_requeue(काष्ठा dasd_device *);

व्योम dasd_add_request_head(काष्ठा dasd_ccw_req *);
व्योम dasd_add_request_tail(काष्ठा dasd_ccw_req *);
पूर्णांक  dasd_start_IO(काष्ठा dasd_ccw_req *);
पूर्णांक  dasd_term_IO(काष्ठा dasd_ccw_req *);
व्योम dasd_schedule_device_bh(काष्ठा dasd_device *);
व्योम dasd_schedule_block_bh(काष्ठा dasd_block *);
पूर्णांक  dasd_sleep_on(काष्ठा dasd_ccw_req *);
पूर्णांक  dasd_sleep_on_queue(काष्ठा list_head *);
पूर्णांक  dasd_sleep_on_immediatly(काष्ठा dasd_ccw_req *);
पूर्णांक  dasd_sleep_on_queue_पूर्णांकerruptible(काष्ठा list_head *);
पूर्णांक  dasd_sleep_on_पूर्णांकerruptible(काष्ठा dasd_ccw_req *);
व्योम dasd_device_set_समयr(काष्ठा dasd_device *, पूर्णांक);
व्योम dasd_device_clear_समयr(काष्ठा dasd_device *);
व्योम dasd_block_set_समयr(काष्ठा dasd_block *, पूर्णांक);
व्योम dasd_block_clear_समयr(काष्ठा dasd_block *);
पूर्णांक  dasd_cancel_req(काष्ठा dasd_ccw_req *);
पूर्णांक dasd_flush_device_queue(काष्ठा dasd_device *);
पूर्णांक dasd_generic_probe(काष्ठा ccw_device *);
व्योम dasd_generic_मुक्त_discipline(काष्ठा dasd_device *);
व्योम dasd_generic_हटाओ (काष्ठा ccw_device *cdev);
पूर्णांक dasd_generic_set_online(काष्ठा ccw_device *, काष्ठा dasd_discipline *);
पूर्णांक dasd_generic_set_offline (काष्ठा ccw_device *cdev);
पूर्णांक dasd_generic_notअगरy(काष्ठा ccw_device *, पूर्णांक);
पूर्णांक dasd_generic_last_path_gone(काष्ठा dasd_device *);
पूर्णांक dasd_generic_path_operational(काष्ठा dasd_device *);
व्योम dasd_generic_shutकरोwn(काष्ठा ccw_device *);

व्योम dasd_generic_handle_state_change(काष्ठा dasd_device *);
क्रमागत uc_toकरो dasd_generic_uc_handler(काष्ठा ccw_device *, काष्ठा irb *);
व्योम dasd_generic_path_event(काष्ठा ccw_device *, पूर्णांक *);
पूर्णांक dasd_generic_verअगरy_path(काष्ठा dasd_device *, __u8);
व्योम dasd_generic_space_exhaust(काष्ठा dasd_device *, काष्ठा dasd_ccw_req *);
व्योम dasd_generic_space_avail(काष्ठा dasd_device *);

पूर्णांक dasd_generic_पढ़ो_dev_अक्षरs(काष्ठा dasd_device *, पूर्णांक, व्योम *, पूर्णांक);
अक्षर *dasd_get_sense(काष्ठा irb *);

व्योम dasd_device_set_stop_bits(काष्ठा dasd_device *, पूर्णांक);
व्योम dasd_device_हटाओ_stop_bits(काष्ठा dasd_device *, पूर्णांक);

पूर्णांक dasd_device_is_ro(काष्ठा dasd_device *);

व्योम dasd_profile_reset(काष्ठा dasd_profile *);
पूर्णांक dasd_profile_on(काष्ठा dasd_profile *);
व्योम dasd_profile_off(काष्ठा dasd_profile *);
अक्षर *dasd_get_user_string(स्थिर अक्षर __user *, माप_प्रकार);

/* बाह्यals in dasd_devmap.c */
बाह्य पूर्णांक dasd_max_devindex;
बाह्य पूर्णांक dasd_probeonly;
बाह्य पूर्णांक dasd_स्वतःdetect;
बाह्य पूर्णांक dasd_nopav;
बाह्य पूर्णांक dasd_nofcx;

पूर्णांक dasd_devmap_init(व्योम);
व्योम dasd_devmap_निकास(व्योम);

काष्ठा dasd_device *dasd_create_device(काष्ठा ccw_device *);
व्योम dasd_delete_device(काष्ठा dasd_device *);

पूर्णांक dasd_get_feature(काष्ठा ccw_device *, पूर्णांक);
पूर्णांक dasd_set_feature(काष्ठा ccw_device *, पूर्णांक, पूर्णांक);

बाह्य स्थिर काष्ठा attribute_group *dasd_dev_groups[];
व्योम dasd_path_create_kobj(काष्ठा dasd_device *, पूर्णांक);
व्योम dasd_path_create_kobjects(काष्ठा dasd_device *);
व्योम dasd_path_हटाओ_kobjects(काष्ठा dasd_device *);

काष्ठा dasd_device *dasd_device_from_cdev(काष्ठा ccw_device *);
काष्ठा dasd_device *dasd_device_from_cdev_locked(काष्ठा ccw_device *);
काष्ठा dasd_device *dasd_device_from_devindex(पूर्णांक);

व्योम dasd_add_link_to_gendisk(काष्ठा gendisk *, काष्ठा dasd_device *);
काष्ठा dasd_device *dasd_device_from_gendisk(काष्ठा gendisk *);

पूर्णांक dasd_parse(व्योम) __init;
पूर्णांक dasd_busid_known(स्थिर अक्षर *);

/* बाह्यals in dasd_gendisk.c */
पूर्णांक  dasd_gendisk_init(व्योम);
व्योम dasd_gendisk_निकास(व्योम);
पूर्णांक dasd_gendisk_alloc(काष्ठा dasd_block *);
व्योम dasd_gendisk_मुक्त(काष्ठा dasd_block *);
पूर्णांक dasd_scan_partitions(काष्ठा dasd_block *);
व्योम dasd_destroy_partitions(काष्ठा dasd_block *);

/* बाह्यals in dasd_ioctl.c */
पूर्णांक dasd_ioctl(काष्ठा block_device *, भ_शेषe_t, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
पूर्णांक dasd_set_पढ़ो_only(काष्ठा block_device *bdev, bool ro);

/* बाह्यals in dasd_proc.c */
पूर्णांक dasd_proc_init(व्योम);
व्योम dasd_proc_निकास(व्योम);

/* बाह्यals in dasd_erp.c */
काष्ठा dasd_ccw_req *dasd_शेष_erp_action(काष्ठा dasd_ccw_req *);
काष्ठा dasd_ccw_req *dasd_शेष_erp_postaction(काष्ठा dasd_ccw_req *);
काष्ठा dasd_ccw_req *dasd_alloc_erp_request(अक्षर *, पूर्णांक, पूर्णांक,
					    काष्ठा dasd_device *);
व्योम dasd_मुक्त_erp_request(काष्ठा dasd_ccw_req *, काष्ठा dasd_device *);
व्योम dasd_log_sense(काष्ठा dasd_ccw_req *, काष्ठा irb *);
व्योम dasd_log_sense_dbf(काष्ठा dasd_ccw_req *cqr, काष्ठा irb *irb);

/* बाह्यals in dasd_3990_erp.c */
काष्ठा dasd_ccw_req *dasd_3990_erp_action(काष्ठा dasd_ccw_req *);
व्योम dasd_3990_erp_handle_sim(काष्ठा dasd_device *, अक्षर *);

/* बाह्यals in dasd_eer.c */
#अगर_घोषित CONFIG_DASD_EER
पूर्णांक dasd_eer_init(व्योम);
व्योम dasd_eer_निकास(व्योम);
पूर्णांक dasd_eer_enable(काष्ठा dasd_device *);
व्योम dasd_eer_disable(काष्ठा dasd_device *);
व्योम dasd_eer_ग_लिखो(काष्ठा dasd_device *, काष्ठा dasd_ccw_req *cqr,
		    अचिन्हित पूर्णांक id);
व्योम dasd_eer_snss(काष्ठा dasd_device *);

अटल अंतरभूत पूर्णांक dasd_eer_enabled(काष्ठा dasd_device *device)
अणु
	वापस device->eer_cqr != शून्य;
पूर्ण
#अन्यथा
#घोषणा dasd_eer_init()		(0)
#घोषणा dasd_eer_निकास()		करो अणु पूर्ण जबतक (0)
#घोषणा dasd_eer_enable(d)	(0)
#घोषणा dasd_eer_disable(d)	करो अणु पूर्ण जबतक (0)
#घोषणा dasd_eer_ग_लिखो(d,c,i)	करो अणु पूर्ण जबतक (0)
#घोषणा dasd_eer_snss(d)	करो अणु पूर्ण जबतक (0)
#घोषणा dasd_eer_enabled(d)	(0)
#पूर्ण_अगर	/* CONFIG_DASD_ERR */


/* DASD path handling functions */

/*
 * helper functions to modअगरy bit masks क्रम a given channel path क्रम a device
 */
अटल अंतरभूत पूर्णांक dasd_path_is_operational(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_OPERATIONAL, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_need_verअगरy(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_TBV, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_verअगरy(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_TBV, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_verअगरy(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_TBV, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_all_verअगरy(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		dasd_path_clear_verअगरy(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_fcsec(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_FCSEC, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_fcsec(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_FCSEC, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_need_fcsec(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_FCSEC, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_all_fcsec(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		dasd_path_clear_fcsec(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_operational(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_OPERATIONAL, &device->path[chp].flags);
	device->opm |= (0x80 >> chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_nonpreferred(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_NPP, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_is_nonpreferred(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_NPP, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_nonpreferred(काष्ठा dasd_device *device,
						पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_NPP, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_preferred(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_PP, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_is_preferred(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_PP, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_preferred(काष्ठा dasd_device *device,
					     पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_PP, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_oper(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_OPERATIONAL, &device->path[chp].flags);
	device->opm &= ~(0x80 >> chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_cable(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_MISCABLED, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_cuir(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_CUIR, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_is_cuir(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_CUIR, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_cuir(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_CUIR, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_अगरcc(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	set_bit(DASD_PATH_IFCC, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_is_अगरcc(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_IFCC, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_अगरcc(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	clear_bit(DASD_PATH_IFCC, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_clear_nohpf(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__clear_bit(DASD_PATH_NOHPF, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_miscabled(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_MISCABLED, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_is_miscabled(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_MISCABLED, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत व्योम dasd_path_nohpf(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	__set_bit(DASD_PATH_NOHPF, &device->path[chp].flags);
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_is_nohpf(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस test_bit(DASD_PATH_NOHPF, &device->path[chp].flags);
पूर्ण

/*
 * get functions क्रम path masks
 * will वापस a path masks क्रम the given device
 */

अटल अंतरभूत __u8 dasd_path_get_opm(काष्ठा dasd_device *device)
अणु
	वापस device->opm;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_tbvpm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 tbvpm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_need_verअगरy(device, chp))
			tbvpm |= 0x80 >> chp;
	वापस tbvpm;
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_get_fcsecpm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_need_fcsec(device, chp))
			वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_nppm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 npm = 0x00;

	क्रम (chp = 0; chp < 8; chp++) अणु
		अगर (dasd_path_is_nonpreferred(device, chp))
			npm |= 0x80 >> chp;
	पूर्ण
	वापस npm;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_ppm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 ppm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_is_preferred(device, chp))
			ppm |= 0x80 >> chp;
	वापस ppm;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_cablepm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 cablepm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_is_miscabled(device, chp))
			cablepm |= 0x80 >> chp;
	वापस cablepm;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_cuirpm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 cuirpm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_is_cuir(device, chp))
			cuirpm |= 0x80 >> chp;
	वापस cuirpm;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_अगरccpm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 अगरccpm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_is_अगरcc(device, chp))
			अगरccpm |= 0x80 >> chp;
	वापस अगरccpm;
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_hpfpm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 hpfpm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_is_nohpf(device, chp))
			hpfpm |= 0x80 >> chp;
	वापस hpfpm;
पूर्ण

अटल अंतरभूत u8 dasd_path_get_fcs_path(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	वापस device->path[chp].fc_security;
पूर्ण

अटल अंतरभूत पूर्णांक dasd_path_get_fcs_device(काष्ठा dasd_device *device)
अणु
	u8 fc_sec = 0;
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++) अणु
		अगर (device->opm & (0x80 >> chp)) अणु
			fc_sec = device->path[chp].fc_security;
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (; chp < 8; chp++) अणु
		अगर (device->opm & (0x80 >> chp))
			अगर (device->path[chp].fc_security != fc_sec)
				वापस -EINVAL;
	पूर्ण

	वापस fc_sec;
पूर्ण

/*
 * add functions क्रम path masks
 * the existing path mask will be extended by the given path mask
 */
अटल अंतरभूत व्योम dasd_path_add_tbvpm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_verअगरy(device, chp);
पूर्ण

अटल अंतरभूत __u8 dasd_path_get_notoperpm(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;
	__u8 nopm = 0x00;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (dasd_path_is_nohpf(device, chp) ||
		    dasd_path_is_अगरcc(device, chp) ||
		    dasd_path_is_cuir(device, chp) ||
		    dasd_path_is_miscabled(device, chp))
			nopm |= 0x80 >> chp;
	वापस nopm;
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_opm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp)) अणु
			dasd_path_operational(device, chp);
			/*
			 * अगर the path is used
			 * it should not be in one of the negative lists
			 */
			dasd_path_clear_nohpf(device, chp);
			dasd_path_clear_cuir(device, chp);
			dasd_path_clear_cable(device, chp);
			dasd_path_clear_अगरcc(device, chp);
		पूर्ण
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_cablepm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_miscabled(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_cuirpm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_cuir(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_अगरccpm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_अगरcc(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_nppm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_nonpreferred(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_nohpfpm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_nohpf(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_add_ppm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_preferred(device, chp);
पूर्ण

/*
 * set functions क्रम path masks
 * the existing path mask will be replaced by the given path mask
 */
अटल अंतरभूत व्योम dasd_path_set_tbvpm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		अगर (pm & (0x80 >> chp))
			dasd_path_verअगरy(device, chp);
		अन्यथा
			dasd_path_clear_verअगरy(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_set_opm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++) अणु
		dasd_path_clear_oper(device, chp);
		अगर (pm & (0x80 >> chp)) अणु
			dasd_path_operational(device, chp);
			/*
			 * अगर the path is used
			 * it should not be in one of the negative lists
			 */
			dasd_path_clear_nohpf(device, chp);
			dasd_path_clear_cuir(device, chp);
			dasd_path_clear_cable(device, chp);
			dasd_path_clear_अगरcc(device, chp);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * हटाओ functions क्रम path masks
 * the existing path mask will be cleared with the given path mask
 */
अटल अंतरभूत व्योम dasd_path_हटाओ_opm(काष्ठा dasd_device *device, __u8 pm)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++) अणु
		अगर (pm & (0x80 >> chp))
			dasd_path_clear_oper(device, chp);
	पूर्ण
पूर्ण

/*
 * add the newly available path to the to be verअगरied pm and हटाओ it from
 * normal operation until it is verअगरied
 */
अटल अंतरभूत व्योम dasd_path_available(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	dasd_path_clear_oper(device, chp);
	dasd_path_verअगरy(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_notoper(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	dasd_path_clear_oper(device, chp);
	dasd_path_clear_preferred(device, chp);
	dasd_path_clear_nonpreferred(device, chp);
पूर्ण

अटल अंतरभूत व्योम dasd_path_fcsec_update(काष्ठा dasd_device *device, पूर्णांक chp)
अणु
	dasd_path_fcsec(device, chp);
पूर्ण

/*
 * हटाओ all paths from normal operation
 */
अटल अंतरभूत व्योम dasd_path_no_path(काष्ठा dasd_device *device)
अणु
	पूर्णांक chp;

	क्रम (chp = 0; chp < 8; chp++)
		dasd_path_notoper(device, chp);

	dasd_path_clear_all_verअगरy(device);
पूर्ण

/* end - path handling */

#पूर्ण_अगर				/* DASD_H */
