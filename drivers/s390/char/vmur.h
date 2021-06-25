<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux driver क्रम System z and s390 unit record devices
 * (z/VM भव punch, पढ़ोer, prपूर्णांकer)
 *
 * Copyright IBM Corp. 2001, 2007
 * Authors: Malcolm Beattie <beattiem@uk.ibm.com>
 *	    Michael Holzheu <holzheu@de.ibm.com>
 *	    Frank Munzert <munzert@de.ibm.com>
 */

#अगर_अघोषित _VMUR_H_
#घोषणा _VMUR_H_

#समावेश <linux/refcount.h>

#घोषणा DEV_CLASS_UR_I 0x20 /* diag210 unit record input device class */
#घोषणा DEV_CLASS_UR_O 0x10 /* diag210 unit record output device class */
/*
 * we only support z/VM's शेष unit record devices:
 * both in SPOOL directory control statement and in CP DEFINE statement
 *	RDR शेषs to 2540 पढ़ोer
 *	PUN शेषs to 2540 punch
 *	PRT शेषs to 1403 prपूर्णांकer
 */
#घोषणा READER_PUNCH_DEVTYPE	0x2540
#घोषणा PRINTER_DEVTYPE		0x1403

/* z/VM spool file control block SFBLOK */
काष्ठा file_control_block अणु
	अक्षर reserved_1[8];
	अक्षर user_owner[8];
	अक्षर user_orig[8];
	__s32 data_recs;
	__s16 rec_len;
	__s16 file_num;
	__u8  file_stat;
	__u8  dev_type;
	अक्षर  reserved_2[6];
	अक्षर  file_name[12];
	अक्षर  file_type[12];
	अक्षर  create_date[8];
	अक्षर  create_समय[8];
	अक्षर  reserved_3[6];
	__u8  file_class;
	__u8  sfb_lok;
	__u64 distr_code;
	__u32 reserved_4;
	__u8  current_starting_copy_number;
	__u8  sfblock_cntrl_flags;
	__u8  reserved_5;
	__u8  more_status_flags;
	अक्षर  rest[200];
पूर्ण __attribute__ ((packed));

#घोषणा FLG_SYSTEM_HOLD	0x04
#घोषणा FLG_CP_DUMP	0x10
#घोषणा FLG_USER_HOLD	0x20
#घोषणा FLG_IN_USE	0x80

/*
 * A काष्ठा urdev is created क्रम each ur device that is made available
 * via the ccw_device driver model.
 */
काष्ठा urdev अणु
	काष्ठा ccw_device *cdev;	/* Backpoपूर्णांकer to ccw device */
	काष्ठा mutex io_mutex;		/* Serialises device IO */
	काष्ठा completion *io_करोne;	/* करो_ur_io रुकोs; irq completes */
	काष्ठा device *device;
	काष्ठा cdev *अक्षर_device;
	काष्ठा ccw_dev_id dev_id;	/* device id */
	माप_प्रकार reclen;			/* Record length क्रम *ग_लिखो* CCWs */
	पूर्णांक class;			/* VM device class */
	पूर्णांक io_request_rc;		/* वापस code from I/O request */
	refcount_t ref_count;		/* reference counter */
	रुको_queue_head_t रुको;		/* रुको queue to serialize खोलो */
	पूर्णांक खोलो_flag;			/* "urdev is open" flag */
	spinlock_t खोलो_lock;		/* serialize critical sections */
पूर्ण;

/*
 * A काष्ठा urfile is allocated at खोलो() समय क्रम each device and
 * मुक्तd on release().
 */
काष्ठा urfile अणु
	काष्ठा urdev *urd;
	अचिन्हित पूर्णांक flags;
	माप_प्रकार dev_reclen;
	__u16 file_reclen;
पूर्ण;

/*
 * Device major/minor definitions.
 */

#घोषणा UR_MAJOR 0	/* get dynamic major */
/*
 * We map minor numbers directly to device numbers (0-FFFF) क्रम simplicity.
 * This aव्योमs having to allocate (and manage) slot numbers.
 */
#घोषणा NUM_MINORS 65536

/* Limiting each I/O to 511 records limits chan prog to 4KB (511 r/w + 1 NOP) */
#घोषणा MAX_RECS_PER_IO		511
#घोषणा WRITE_CCW_CMD		0x01

#घोषणा TRACE(x...) debug_प्र_लिखो_event(vmur_dbf, 1, x)
#घोषणा CCWDEV_CU_DI(cutype, di) \
		CCW_DEVICE(cutype, 0x00), .driver_info = (di)

#घोषणा खाता_RECLEN_OFFSET	4064 /* reclen offset in spool data block */

#पूर्ण_अगर /* _VMUR_H_ */
