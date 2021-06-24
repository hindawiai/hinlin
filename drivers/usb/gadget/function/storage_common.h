<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित USB_STORAGE_COMMON_H
#घोषणा USB_STORAGE_COMMON_H

#समावेश <linux/device.h>
#समावेश <linux/usb/storage.h>
#समावेश <scsi/scsi.h>
#समावेश <यंत्र/unaligned.h>

#अगर_अघोषित DEBUG
#अघोषित VERBOSE_DEBUG
#अघोषित DUMP_MSGS
#पूर्ण_अगर /* !DEBUG */

#अगर_घोषित VERBOSE_DEBUG
#घोषणा VLDBG	LDBG
#अन्यथा
#घोषणा VLDBG(lun, fmt, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* VERBOSE_DEBUG */

#घोषणा _LMSG(func, lun, fmt, args...)					\
	करो अणु								\
		अगर ((lun)->name_pfx && *(lun)->name_pfx)		\
			func("%s/%s: " fmt, *(lun)->name_pfx,		\
				 (lun)->name, ## args);			\
		अन्यथा							\
			func("%s: " fmt, (lun)->name, ## args);		\
	पूर्ण जबतक (0)

#घोषणा LDBG(lun, fmt, args...)		_LMSG(pr_debug, lun, fmt, ## args)
#घोषणा LERROR(lun, fmt, args...)	_LMSG(pr_err, lun, fmt, ## args)
#घोषणा LWARN(lun, fmt, args...)	_LMSG(pr_warn, lun, fmt, ## args)
#घोषणा LINFO(lun, fmt, args...)	_LMSG(pr_info, lun, fmt, ## args)


#अगर_घोषित DUMP_MSGS

#  define dump_msg(fsg, /* स्थिर अक्षर * */ label,			\
		   /* स्थिर u8 * */ buf, /* अचिन्हित */ length)		\
करो अणु									\
	अगर (length < 512) अणु						\
		DBG(fsg, "%s, length %u:\n", label, length);		\
		prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET,	\
			       16, 1, buf, length, 0);			\
	पूर्ण								\
पूर्ण जबतक (0)

#  define dump_cdb(fsg) करो अणु पूर्ण जबतक (0)

#अन्यथा

#  define dump_msg(fsg, /* स्थिर अक्षर * */ label, \
		   /* स्थिर u8 * */ buf, /* अचिन्हित */ length) करो अणु पूर्ण जबतक (0)

#  अगरdef VERBOSE_DEBUG

#    define dump_cdb(fsg)						\
	prपूर्णांक_hex_dump(KERN_DEBUG, "SCSI CDB: ", DUMP_PREFIX_NONE,	\
		       16, 1, (fsg)->cmnd, (fsg)->cmnd_size, 0)		\

#  अन्यथा

#    define dump_cdb(fsg) करो अणु पूर्ण जबतक (0)

#  endअगर /* VERBOSE_DEBUG */

#पूर्ण_अगर /* DUMP_MSGS */

/* Length of a SCSI Command Data Block */
#घोषणा MAX_COMMAND_SIZE	16

/* SCSI Sense Key/Additional Sense Code/ASC Qualअगरier values */
#घोषणा SS_NO_SENSE				0
#घोषणा SS_COMMUNICATION_FAILURE		0x040800
#घोषणा SS_INVALID_COMMAND			0x052000
#घोषणा SS_INVALID_FIELD_IN_CDB			0x052400
#घोषणा SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE	0x052100
#घोषणा SS_LOGICAL_UNIT_NOT_SUPPORTED		0x052500
#घोषणा SS_MEDIUM_NOT_PRESENT			0x023a00
#घोषणा SS_MEDIUM_REMOVAL_PREVENTED		0x055302
#घोषणा SS_NOT_READY_TO_READY_TRANSITION	0x062800
#घोषणा SS_RESET_OCCURRED			0x062900
#घोषणा SS_SAVING_PARAMETERS_NOT_SUPPORTED	0x053900
#घोषणा SS_UNRECOVERED_READ_ERROR		0x031100
#घोषणा SS_WRITE_ERROR				0x030c02
#घोषणा SS_WRITE_PROTECTED			0x072700

#घोषणा SK(x)		((u8) ((x) >> 16))	/* Sense Key byte, etc. */
#घोषणा ASC(x)		((u8) ((x) >> 8))
#घोषणा ASCQ(x)		((u8) (x))

/*
 * Venकरोr (8 अक्षरs), product (16 अक्षरs), release (4 hexadecimal digits) and NUL
 * byte
 */
#घोषणा INQUIRY_STRING_LEN ((माप_प्रकार) (8 + 16 + 4 + 1))

काष्ठा fsg_lun अणु
	काष्ठा file	*filp;
	loff_t		file_length;
	loff_t		num_sectors;

	अचिन्हित पूर्णांक	initially_ro:1;
	अचिन्हित पूर्णांक	ro:1;
	अचिन्हित पूर्णांक	removable:1;
	अचिन्हित पूर्णांक	cdrom:1;
	अचिन्हित पूर्णांक	prevent_medium_removal:1;
	अचिन्हित पूर्णांक	रेजिस्टरed:1;
	अचिन्हित पूर्णांक	info_valid:1;
	अचिन्हित पूर्णांक	nofua:1;

	u32		sense_data;
	u32		sense_data_info;
	u32		unit_attention_data;

	अचिन्हित पूर्णांक	blkbits; /* Bits of logical block size
						       of bound block device */
	अचिन्हित पूर्णांक	blksize; /* logical block size of bound block device */
	काष्ठा device	dev;
	स्थिर अक्षर	*name;		/* "lun.name" */
	स्थिर अक्षर	**name_pfx;	/* "function.name" */
	अक्षर		inquiry_string[INQUIRY_STRING_LEN];
पूर्ण;

अटल अंतरभूत bool fsg_lun_is_खोलो(काष्ठा fsg_lun *curlun)
अणु
	वापस curlun->filp != शून्य;
पूर्ण

/* Default size of buffer length. */
#घोषणा FSG_BUFLEN	((u32)16384)

/* Maximal number of LUNs supported in mass storage function */
#घोषणा FSG_MAX_LUNS	16

क्रमागत fsg_buffer_state अणु
	BUF_STATE_SENDING = -2,
	BUF_STATE_RECEIVING,
	BUF_STATE_EMPTY = 0,
	BUF_STATE_FULL
पूर्ण;

काष्ठा fsg_buffhd अणु
	व्योम				*buf;
	क्रमागत fsg_buffer_state		state;
	काष्ठा fsg_buffhd		*next;

	/*
	 * The NetChip 2280 is faster, and handles some protocol faults
	 * better, अगर we करोn't submit any लघु bulk-out पढ़ो requests.
	 * So we will record the पूर्णांकended request length here.
	 */
	अचिन्हित पूर्णांक			bulk_out_पूर्णांकended_length;

	काष्ठा usb_request		*inreq;
	काष्ठा usb_request		*outreq;
पूर्ण;

क्रमागत fsg_state अणु
	FSG_STATE_NORMAL,
	FSG_STATE_ABORT_BULK_OUT,
	FSG_STATE_PROTOCOL_RESET,
	FSG_STATE_CONFIG_CHANGE,
	FSG_STATE_EXIT,
	FSG_STATE_TERMINATED
पूर्ण;

क्रमागत data_direction अणु
	DATA_सूची_UNKNOWN = 0,
	DATA_सूची_FROM_HOST,
	DATA_सूची_TO_HOST,
	DATA_सूची_NONE
पूर्ण;

अटल अंतरभूत काष्ठा fsg_lun *fsg_lun_from_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा fsg_lun, dev);
पूर्ण

क्रमागत अणु
	FSG_STRING_INTERFACE
पूर्ण;

बाह्य काष्ठा usb_पूर्णांकerface_descriptor fsg_पूर्णांकf_desc;

बाह्य काष्ठा usb_endpoपूर्णांक_descriptor fsg_fs_bulk_in_desc;
बाह्य काष्ठा usb_endpoपूर्णांक_descriptor fsg_fs_bulk_out_desc;
बाह्य काष्ठा usb_descriptor_header *fsg_fs_function[];

बाह्य काष्ठा usb_endpoपूर्णांक_descriptor fsg_hs_bulk_in_desc;
बाह्य काष्ठा usb_endpoपूर्णांक_descriptor fsg_hs_bulk_out_desc;
बाह्य काष्ठा usb_descriptor_header *fsg_hs_function[];

बाह्य काष्ठा usb_endpoपूर्णांक_descriptor fsg_ss_bulk_in_desc;
बाह्य काष्ठा usb_ss_ep_comp_descriptor fsg_ss_bulk_in_comp_desc;
बाह्य काष्ठा usb_endpoपूर्णांक_descriptor fsg_ss_bulk_out_desc;
बाह्य काष्ठा usb_ss_ep_comp_descriptor fsg_ss_bulk_out_comp_desc;
बाह्य काष्ठा usb_descriptor_header *fsg_ss_function[];

व्योम fsg_lun_बंद(काष्ठा fsg_lun *curlun);
पूर्णांक fsg_lun_खोलो(काष्ठा fsg_lun *curlun, स्थिर अक्षर *filename);
पूर्णांक fsg_lun_fsync_sub(काष्ठा fsg_lun *curlun);
व्योम store_cdrom_address(u8 *dest, पूर्णांक msf, u32 addr);
sमाप_प्रकार fsg_show_ro(काष्ठा fsg_lun *curlun, अक्षर *buf);
sमाप_प्रकार fsg_show_nofua(काष्ठा fsg_lun *curlun, अक्षर *buf);
sमाप_प्रकार fsg_show_file(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
		      अक्षर *buf);
sमाप_प्रकार fsg_show_inquiry_string(काष्ठा fsg_lun *curlun, अक्षर *buf);
sमाप_प्रकार fsg_show_cdrom(काष्ठा fsg_lun *curlun, अक्षर *buf);
sमाप_प्रकार fsg_show_removable(काष्ठा fsg_lun *curlun, अक्षर *buf);
sमाप_प्रकार fsg_store_ro(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
		     स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार fsg_store_nofua(काष्ठा fsg_lun *curlun, स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार fsg_store_file(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
		       स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार fsg_store_cdrom(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
			स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार fsg_store_removable(काष्ठा fsg_lun *curlun, स्थिर अक्षर *buf,
			    माप_प्रकार count);
sमाप_प्रकार fsg_store_inquiry_string(काष्ठा fsg_lun *curlun, स्थिर अक्षर *buf,
				 माप_प्रकार count);

#पूर्ण_अगर /* USB_STORAGE_COMMON_H */
