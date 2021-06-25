<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ioctl पूर्णांकerface क्रम the scsi media changer driver
 */

#अगर_अघोषित _UAPI_LINUX_CHIO_H
#घोषणा _UAPI_LINUX_CHIO_H

/* changer element types */
#घोषणा CHET_MT   0	/* media transport element (robot) */
#घोषणा CHET_ST   1	/* storage element (media slots) */
#घोषणा CHET_IE   2	/* import/export element */
#घोषणा CHET_DT   3	/* data transfer element (tape/cdrom/whatever) */
#घोषणा CHET_V1   4	/* venकरोr specअगरic #1 */
#घोषणा CHET_V2   5	/* venकरोr specअगरic #2 */
#घोषणा CHET_V3   6	/* venकरोr specअगरic #3 */
#घोषणा CHET_V4   7	/* venकरोr specअगरic #4 */


/*
 * CHIOGPARAMS
 *    query changer properties
 *
 * CHIOVGPARAMS
 *    query venकरोr-specअगरic element types
 *
 *    accessing elements works by specअगरing type and unit of the element.
 *    क्रम example, storage elements are addressed with type = CHET_ST and
 *    unit = 0 .. cp_nslots-1
 *
 */
काष्ठा changer_params अणु
	पूर्णांक cp_curpicker;  /* current transport element */
	पूर्णांक cp_npickers;   /* number of transport elements      (CHET_MT) */
	पूर्णांक cp_nslots;     /* number of storage elements        (CHET_ST) */
	पूर्णांक cp_nportals;   /* number of import/export elements  (CHET_IE) */
	पूर्णांक cp_ndrives;    /* number of data transfer elements  (CHET_DT) */
पूर्ण;
काष्ठा changer_venकरोr_params अणु
	पूर्णांक  cvp_n1;       /* number of venकरोr specअगरic elems   (CHET_V1) */
	अक्षर cvp_label1[16];
	पूर्णांक  cvp_n2;       /* number of venकरोr specअगरic elems   (CHET_V2) */
	अक्षर cvp_label2[16];
	पूर्णांक  cvp_n3;       /* number of venकरोr specअगरic elems   (CHET_V3) */
	अक्षर cvp_label3[16];
	पूर्णांक  cvp_n4;       /* number of venकरोr specअगरic elems   (CHET_V4) */
	अक्षर cvp_label4[16];
	पूर्णांक  reserved[8];
पूर्ण;


/*
 * CHIOMOVE
 *    move a medium from one element to another
 */
काष्ठा changer_move अणु
	पूर्णांक cm_fromtype;	/* type/unit of source element */
	पूर्णांक cm_fromunit;	
	पूर्णांक cm_totype;	/* type/unit of destination element */
	पूर्णांक cm_tounit;
	पूर्णांक cm_flags;
पूर्ण;
#घोषणा CM_INVERT   1   /* flag: rotate media (क्रम द्विगुन-sided like MOD) */


/*
 * CHIOEXCHANGE
 *    move one medium from element #1 to element #2,
 *    and another one from element #2 to element #3.
 *    element #1 and #3 are allowed to be identical.
 */
काष्ठा changer_exchange अणु
	पूर्णांक ce_srctype;	    /* type/unit of element #1 */
	पूर्णांक ce_srcunit;
	पूर्णांक ce_fdsttype;    /* type/unit of element #2 */
	पूर्णांक ce_fdstunit;
	पूर्णांक ce_sdsttype;    /* type/unit of element #3 */
	पूर्णांक ce_sdstunit;
	पूर्णांक ce_flags;
पूर्ण;
#घोषणा CE_INVERT1   1
#घोषणा CE_INVERT2   2


/*
 * CHIOPOSITION
 *    move the transport element (robot arm) to a specअगरic element.
 */
काष्ठा changer_position अणु
	पूर्णांक cp_type;
	पूर्णांक cp_unit;
	पूर्णांक cp_flags;
पूर्ण;
#घोषणा CP_INVERT   1


/*
 * CHIOGSTATUS
 *    get element status क्रम all elements of a specअगरic type
 */
काष्ठा changer_element_status अणु
	पूर्णांक             ces_type;
	अचिन्हित अक्षर   __user *ces_data;
पूर्ण;
#घोषणा CESTATUS_FULL     0x01 /* full */
#घोषणा CESTATUS_IMPEXP   0x02	/* media was imported (inserted by sysop) */
#घोषणा CESTATUS_EXCEPT   0x04	/* error condition */
#घोषणा CESTATUS_ACCESS   0x08	/* access allowed */
#घोषणा CESTATUS_EXENAB   0x10	/* element can export media */
#घोषणा CESTATUS_INENAB   0x20	/* element can import media */


/*
 * CHIOGELEM
 *    get more detailed status inक्रमmation क्रम a single element
 */
काष्ठा changer_get_element अणु
	पूर्णांक	cge_type;	 /* type/unit */
	पूर्णांक	cge_unit;
	पूर्णांक	cge_status;      /* status */
	पूर्णांक     cge_त्रुटि_सं;       /* त्रुटि_सं */
	पूर्णांक     cge_srctype;     /* source element of the last move/exchange */
	पूर्णांक     cge_srcunit;
	पूर्णांक     cge_id;          /* scsi id  (क्रम data transfer elements) */
	पूर्णांक     cge_lun;         /* scsi lun (क्रम data transfer elements) */
	अक्षर    cge_pvoltag[36]; /* primary volume tag */
	अक्षर    cge_avoltag[36]; /* alternate volume tag */
	पूर्णांक     cge_flags;
पूर्ण;
/* flags */
#घोषणा CGE_ERRNO     0x01       /* त्रुटि_सं available       */
#घोषणा CGE_INVERT    0x02       /* media inverted        */
#घोषणा CGE_SRC       0x04       /* media src available   */
#घोषणा CGE_IDLUN     0x08       /* ID+LUN available      */
#घोषणा CGE_PVOLTAG   0x10       /* primary volume tag available */
#घोषणा CGE_AVOLTAG   0x20       /* alternate volume tag available */


/*
 * CHIOSVOLTAG
 *    set volume tag
 */
काष्ठा changer_set_voltag अणु
	पूर्णांक	csv_type;	 /* type/unit */
	पूर्णांक	csv_unit;
	अक्षर    csv_voltag[36];  /* volume tag */
	पूर्णांक     csv_flags;
पूर्ण;
#घोषणा CSV_PVOLTAG   0x01       /* primary volume tag */
#घोषणा CSV_AVOLTAG   0x02       /* alternate volume tag */
#घोषणा CSV_CLEARTAG  0x04       /* clear volume tag */

/* ioctls */
#घोषणा CHIOMOVE       _IOW('c', 1,काष्ठा changer_move)
#घोषणा CHIOEXCHANGE   _IOW('c', 2,काष्ठा changer_exchange)
#घोषणा CHIOPOSITION   _IOW('c', 3,काष्ठा changer_position)
#घोषणा CHIOGPICKER    _IOR('c', 4,पूर्णांक)                        /* not impl. */
#घोषणा CHIOSPICKER    _IOW('c', 5,पूर्णांक)                        /* not impl. */
#घोषणा CHIOGPARAMS    _IOR('c', 6,काष्ठा changer_params)
#घोषणा CHIOGSTATUS    _IOW('c', 8,काष्ठा changer_element_status)
#घोषणा CHIOGELEM      _IOW('c',16,काष्ठा changer_get_element)
#घोषणा CHIOINITELEM   _IO('c',17)
#घोषणा CHIOSVOLTAG    _IOW('c',18,काष्ठा changer_set_voltag)
#घोषणा CHIOGVPARAMS   _IOR('c',19,काष्ठा changer_venकरोr_params)

#पूर्ण_अगर /* _UAPI_LINUX_CHIO_H */
