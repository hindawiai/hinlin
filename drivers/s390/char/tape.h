<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    tape device driver क्रम 3480/3490E/3590 tapes.
 *
 *  S390 and zSeries version
 *    Copyright IBM Corp. 2001, 2009
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		 Stefan Bader <shbader@de.ibm.com>
 */

#अगर_अघोषित _TAPE_H
#घोषणा _TAPE_H

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/idals.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>

काष्ठा gendisk;

/*
 * Define DBF_LIKE_HELL क्रम lots of messages in the debug feature.
 */
#घोषणा DBF_LIKE_HELL
#अगर_घोषित  DBF_LIKE_HELL
#घोषणा DBF_LH(level, str, ...) \
करो अणु \
	debug_प्र_लिखो_event(TAPE_DBF_AREA, level, str, ## __VA_ARGS__); \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा DBF_LH(level, str, ...) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * macros s390 debug feature (dbf)
 */
#घोषणा DBF_EVENT(d_level, d_str...) \
करो अणु \
	debug_प्र_लिखो_event(TAPE_DBF_AREA, d_level, d_str); \
पूर्ण जबतक (0)

#घोषणा DBF_EXCEPTION(d_level, d_str...) \
करो अणु \
	debug_प्र_लिखो_exception(TAPE_DBF_AREA, d_level, d_str); \
पूर्ण जबतक (0)

#घोषणा TAPE_VERSION_MAJOR 2
#घोषणा TAPE_VERSION_MINOR 0
#घोषणा TAPE_MAGIC "tape"

#घोषणा TAPE_MINORS_PER_DEV 2	    /* two minors per device */
#घोषणा TAPEBLOCK_HSEC_SIZE	2048
#घोषणा TAPEBLOCK_HSEC_S2B	2
#घोषणा TAPEBLOCK_RETRIES	5

क्रमागत tape_medium_state अणु
	MS_UNKNOWN,
	MS_LOADED,
	MS_UNLOADED,
	MS_SIZE
पूर्ण;

क्रमागत tape_state अणु
	TS_UNUSED=0,
	TS_IN_USE,
	TS_BLKUSE,
	TS_INIT,
	TS_NOT_OPER,
	TS_SIZE
पूर्ण;

क्रमागत tape_op अणु
	TO_BLOCK,	/* Block पढ़ो */
	TO_BSB,		/* Backward space block */
	TO_BSF,		/* Backward space filemark */
	TO_DSE,		/* Data security erase */
	TO_FSB,		/* Forward space block */
	TO_FSF,		/* Forward space filemark */
	TO_LBL,		/* Locate block label */
	TO_NOP,		/* No operation */
	TO_RBA,		/* Read backward */
	TO_RBI,		/* Read block inक्रमmation */
	TO_RFO,		/* Read क्रमward */
	TO_REW,		/* Rewind tape */
	TO_RUN,		/* Rewind and unload tape */
	TO_WRI,		/* Write block */
	TO_WTM,		/* Write tape mark */
	TO_MSEN,	/* Medium sense */
	TO_LOAD,	/* Load tape */
	TO_READ_CONFIG, /* Read configuration data */
	TO_READ_ATTMSG, /* Read attention message */
	TO_DIS,		/* Tape display */
	TO_ASSIGN,	/* Assign tape to channel path */
	TO_UNASSIGN,	/* Unassign tape from channel path */
	TO_CRYPT_ON,	/* Enable encrpytion */
	TO_CRYPT_OFF,	/* Disable encrpytion */
	TO_KEKL_SET,	/* Set KEK label */
	TO_KEKL_QUERY,	/* Query KEK label */
	TO_RDC,		/* Read device अक्षरacteristics */
	TO_SIZE,	/* #entries in tape_op_t */
पूर्ण;

/* Forward declaration */
काष्ठा tape_device;

/* tape_request->status can be: */
क्रमागत tape_request_status अणु
	TAPE_REQUEST_INIT,	/* request is पढ़ोy to be processed */
	TAPE_REQUEST_QUEUED,	/* request is queued to be processed */
	TAPE_REQUEST_IN_IO,	/* request is currently in IO */
	TAPE_REQUEST_DONE,	/* request is completed. */
	TAPE_REQUEST_CANCEL,	/* request should be canceled. */
	TAPE_REQUEST_LONG_BUSY, /* request has to be restarted after दीर्घ busy */
पूर्ण;

/* Tape CCW request */
काष्ठा tape_request अणु
	काष्ठा list_head list;		/* list head क्रम request queueing. */
	काष्ठा tape_device *device;	/* tape device of this request */
	काष्ठा ccw1 *cpaddr;		/* address of the channel program. */
	व्योम *cpdata;			/* poपूर्णांकer to ccw data. */
	क्रमागत tape_request_status status;/* status of this request */
	पूर्णांक options;			/* options क्रम execution. */
	पूर्णांक retries;			/* retry counter क्रम error recovery. */
	पूर्णांक rescnt;			/* residual count from devstat. */
	काष्ठा समयr_list समयr;	/* समयr क्रम std_assign_समयout(). */

	/* Callback क्रम delivering final status. */
	व्योम (*callback)(काष्ठा tape_request *, व्योम *);
	व्योम *callback_data;

	क्रमागत tape_op op;
	पूर्णांक rc;
पूर्ण;

/* Function type क्रम magnetic tape commands */
प्रकार पूर्णांक (*tape_mtop_fn)(काष्ठा tape_device *, पूर्णांक);

/* Size of the array containing the mtops क्रम a discipline */
#घोषणा TAPE_NR_MTOPS (MTMKPART+1)

/* Tape Discipline */
काष्ठा tape_discipline अणु
	काष्ठा module *owner;
	पूर्णांक  (*setup_device)(काष्ठा tape_device *);
	व्योम (*cleanup_device)(काष्ठा tape_device *);
	पूर्णांक (*irq)(काष्ठा tape_device *, काष्ठा tape_request *, काष्ठा irb *);
	काष्ठा tape_request *(*पढ़ो_block)(काष्ठा tape_device *, माप_प्रकार);
	काष्ठा tape_request *(*ग_लिखो_block)(काष्ठा tape_device *, माप_प्रकार);
	व्योम (*process_eov)(काष्ठा tape_device*);
	/* ioctl function क्रम additional ioctls. */
	पूर्णांक (*ioctl_fn)(काष्ठा tape_device *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	/* Array of tape commands with TAPE_NR_MTOPS entries */
	tape_mtop_fn *mtop_array;
पूर्ण;

/*
 * The discipline irq function either वापसs an error code (<0) which
 * means that the request has failed with an error or one of the following:
 */
#घोषणा TAPE_IO_SUCCESS		0	/* request successful */
#घोषणा TAPE_IO_PENDING		1	/* request still running */
#घोषणा TAPE_IO_RETRY		2	/* retry to current request */
#घोषणा TAPE_IO_STOP		3	/* stop the running request */
#घोषणा TAPE_IO_LONG_BUSY	4	/* delay the running request */

/* Char Frontend Data */
काष्ठा tape_अक्षर_data अणु
	काष्ठा idal_buffer *idal_buf;	/* idal buffer क्रम user अक्षर data */
	पूर्णांक block_size;			/*   of size block_size. */
पूर्ण;

/* Tape Info */
काष्ठा tape_device अणु
	/* entry in tape_device_list */
	काष्ठा list_head		node;

	पूर्णांक				cdev_id;
	काष्ठा ccw_device *		cdev;
	काष्ठा tape_class_device *	nt;
	काष्ठा tape_class_device *	rt;

	/* Device mutex to serialize tape commands. */
	काष्ठा mutex			mutex;

	/* Device discipline inक्रमmation. */
	काष्ठा tape_discipline *	discipline;
	व्योम *				discdata;

	/* Generic status flags */
	दीर्घ				tape_generic_status;

	/* Device state inक्रमmation. */
	रुको_queue_head_t		state_change_wq;
	क्रमागत tape_state			tape_state;
	क्रमागत tape_medium_state		medium_state;
	अचिन्हित अक्षर *			modeset_byte;

	/* Reference count. */
	atomic_t			ref_count;

	/* Request queue. */
	काष्ठा list_head		req_queue;

	/* Request रुको queue. */
	रुको_queue_head_t		रुको_queue;

	/* Each tape device has (currently) two minor numbers. */
	पूर्णांक				first_minor;

	/* Number of tapemarks required क्रम correct termination. */
	पूर्णांक				required_tapemarks;

	/* Block ID of the BOF */
	अचिन्हित पूर्णांक			bof;

	/* Character device frontend data */
	काष्ठा tape_अक्षर_data		अक्षर_data;

	/* Function to start or stop the next request later. */
	काष्ठा delayed_work		tape_dnr;

	/* Timer क्रम दीर्घ busy */
	काष्ठा समयr_list		lb_समयout;

पूर्ण;

/* Externals from tape_core.c */
बाह्य काष्ठा tape_request *tape_alloc_request(पूर्णांक cplength, पूर्णांक datasize);
बाह्य व्योम tape_मुक्त_request(काष्ठा tape_request *);
बाह्य पूर्णांक tape_करो_io(काष्ठा tape_device *, काष्ठा tape_request *);
बाह्य पूर्णांक tape_करो_io_async(काष्ठा tape_device *, काष्ठा tape_request *);
बाह्य पूर्णांक tape_करो_io_पूर्णांकerruptible(काष्ठा tape_device *, काष्ठा tape_request *);
बाह्य पूर्णांक tape_cancel_io(काष्ठा tape_device *, काष्ठा tape_request *);

अटल अंतरभूत पूर्णांक
tape_करो_io_मुक्त(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	पूर्णांक rc;

	rc = tape_करो_io(device, request);
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम
tape_करो_io_async_मुक्त(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	request->callback = (व्योम *) tape_मुक्त_request;
	request->callback_data = शून्य;
	tape_करो_io_async(device, request);
पूर्ण

बाह्य पूर्णांक tape_खोलो(काष्ठा tape_device *);
बाह्य पूर्णांक tape_release(काष्ठा tape_device *);
बाह्य पूर्णांक tape_mtop(काष्ठा tape_device *, पूर्णांक, पूर्णांक);
बाह्य व्योम tape_state_set(काष्ठा tape_device *, क्रमागत tape_state);

बाह्य पूर्णांक tape_generic_online(काष्ठा tape_device *, काष्ठा tape_discipline *);
बाह्य पूर्णांक tape_generic_offline(काष्ठा ccw_device *);

/* Externals from tape_devmap.c */
बाह्य पूर्णांक tape_generic_probe(काष्ठा ccw_device *);
बाह्य व्योम tape_generic_हटाओ(काष्ठा ccw_device *);

बाह्य काष्ठा tape_device *tape_find_device(पूर्णांक devindex);
बाह्य काष्ठा tape_device *tape_get_device(काष्ठा tape_device *);
बाह्य व्योम tape_put_device(काष्ठा tape_device *);

/* Externals from tape_अक्षर.c */
बाह्य पूर्णांक tapeअक्षर_init(व्योम);
बाह्य व्योम tapeअक्षर_निकास(व्योम);
बाह्य पूर्णांक  tapeअक्षर_setup_device(काष्ठा tape_device *);
बाह्य व्योम tapeअक्षर_cleanup_device(काष्ठा tape_device *);

/* tape initialisation functions */
#अगर_घोषित CONFIG_PROC_FS
बाह्य व्योम tape_proc_init (व्योम);
बाह्य व्योम tape_proc_cleanup (व्योम);
#अन्यथा
अटल अंतरभूत व्योम tape_proc_init (व्योम) अणु;पूर्ण
अटल अंतरभूत व्योम tape_proc_cleanup (व्योम) अणु;पूर्ण
#पूर्ण_अगर

/* a function क्रम dumping device sense info */
बाह्य व्योम tape_dump_sense_dbf(काष्ठा tape_device *, काष्ठा tape_request *,
				काष्ठा irb *);

/* functions क्रम handling the status of a device */
बाह्य व्योम tape_med_state_set(काष्ठा tape_device *, क्रमागत tape_medium_state);

/* The debug area */
बाह्य debug_info_t *TAPE_DBF_AREA;

/* functions क्रम building ccws */
अटल अंतरभूत काष्ठा ccw1 *
tape_ccw_cc(काष्ठा ccw1 *ccw, __u8 cmd_code, __u16 memsize, व्योम *cda)
अणु
	ccw->cmd_code = cmd_code;
	ccw->flags = CCW_FLAG_CC;
	ccw->count = memsize;
	ccw->cda = (__u32)(addr_t) cda;
	वापस ccw + 1;
पूर्ण

अटल अंतरभूत काष्ठा ccw1 *
tape_ccw_end(काष्ठा ccw1 *ccw, __u8 cmd_code, __u16 memsize, व्योम *cda)
अणु
	ccw->cmd_code = cmd_code;
	ccw->flags = 0;
	ccw->count = memsize;
	ccw->cda = (__u32)(addr_t) cda;
	वापस ccw + 1;
पूर्ण

अटल अंतरभूत काष्ठा ccw1 *
tape_ccw_cmd(काष्ठा ccw1 *ccw, __u8 cmd_code)
अणु
	ccw->cmd_code = cmd_code;
	ccw->flags = 0;
	ccw->count = 0;
	ccw->cda = (__u32)(addr_t) &ccw->cmd_code;
	वापस ccw + 1;
पूर्ण

अटल अंतरभूत काष्ठा ccw1 *
tape_ccw_repeat(काष्ठा ccw1 *ccw, __u8 cmd_code, पूर्णांक count)
अणु
	जबतक (count-- > 0) अणु
		ccw->cmd_code = cmd_code;
		ccw->flags = CCW_FLAG_CC;
		ccw->count = 0;
		ccw->cda = (__u32)(addr_t) &ccw->cmd_code;
		ccw++;
	पूर्ण
	वापस ccw;
पूर्ण

अटल अंतरभूत काष्ठा ccw1 *
tape_ccw_cc_idal(काष्ठा ccw1 *ccw, __u8 cmd_code, काष्ठा idal_buffer *idal)
अणु
	ccw->cmd_code = cmd_code;
	ccw->flags    = CCW_FLAG_CC;
	idal_buffer_set_cda(idal, ccw);
	वापस ccw++;
पूर्ण

अटल अंतरभूत काष्ठा ccw1 *
tape_ccw_end_idal(काष्ठा ccw1 *ccw, __u8 cmd_code, काष्ठा idal_buffer *idal)
अणु
	ccw->cmd_code = cmd_code;
	ccw->flags    = 0;
	idal_buffer_set_cda(idal, ccw);
	वापस ccw++;
पूर्ण

/* Global vars */
बाह्य स्थिर अक्षर *tape_state_verbose[];
बाह्य स्थिर अक्षर *tape_op_verbose[];

#पूर्ण_अगर /* क्रम अगरdef tape.h */
