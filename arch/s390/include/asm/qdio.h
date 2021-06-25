<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2000, 2008
 * Author(s): Utz Bacher <utz.bacher@de.ibm.com>
 *	      Jan Glauber <jang@linux.vnet.ibm.com>
 *
 */
#अगर_अघोषित __QDIO_H__
#घोषणा __QDIO_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ccwdev.h>

/* only use 4 queues to save some cachelines */
#घोषणा QDIO_MAX_QUEUES_PER_IRQ		4
#घोषणा QDIO_MAX_BUFFERS_PER_Q		128
#घोषणा QDIO_MAX_BUFFERS_MASK		(QDIO_MAX_BUFFERS_PER_Q - 1)
#घोषणा QDIO_BUFNR(num)			((num) & QDIO_MAX_BUFFERS_MASK)
#घोषणा QDIO_MAX_ELEMENTS_PER_BUFFER	16
#घोषणा QDIO_SBAL_SIZE			256

#घोषणा QDIO_QETH_QFMT			0
#घोषणा QDIO_ZFCP_QFMT			1
#घोषणा QDIO_IQDIO_QFMT			2

/**
 * काष्ठा qdesfmt0 - queue descriptor, क्रमmat 0
 * @sliba: असलolute address of storage list inक्रमmation block
 * @sla: असलolute address of storage list
 * @slsba: असलolute address of storage list state block
 * @akey: access key क्रम SLIB
 * @bkey: access key क्रम SL
 * @ckey: access key क्रम SBALs
 * @dkey: access key क्रम SLSB
 */
काष्ठा qdesfmt0 अणु
	u64 sliba;
	u64 sla;
	u64 slsba;
	u32	 : 32;
	u32 akey : 4;
	u32 bkey : 4;
	u32 ckey : 4;
	u32 dkey : 4;
	u32	 : 16;
पूर्ण __attribute__ ((packed));

#घोषणा QDR_AC_MULTI_BUFFER_ENABLE 0x01

/**
 * काष्ठा qdr - queue description record (QDR)
 * @qfmt: queue क्रमmat
 * @ac: adapter अक्षरacteristics
 * @iqdcnt: input queue descriptor count
 * @oqdcnt: output queue descriptor count
 * @iqdsz: input queue descriptor size
 * @oqdsz: output queue descriptor size
 * @qiba: असलolute address of queue inक्रमmation block
 * @qkey: queue inक्रमmation block key
 * @qdf0: queue descriptions
 */
काष्ठा qdr अणु
	u32 qfmt   : 8;
	u32	   : 16;
	u32 ac	   : 8;
	u32	   : 8;
	u32 iqdcnt : 8;
	u32	   : 8;
	u32 oqdcnt : 8;
	u32	   : 8;
	u32 iqdsz  : 8;
	u32	   : 8;
	u32 oqdsz  : 8;
	/* निजी: */
	u32 res[9];
	/* खुला: */
	u64 qiba;
	u32	   : 32;
	u32 qkey   : 4;
	u32	   : 28;
	काष्ठा qdesfmt0 qdf0[126];
पूर्ण __packed __aligned(PAGE_SIZE);

#घोषणा QIB_AC_OUTBOUND_PCI_SUPPORTED	0x40
#घोषणा QIB_RFLAGS_ENABLE_QEBSM		0x80
#घोषणा QIB_RFLAGS_ENABLE_DATA_DIV	0x02

/**
 * काष्ठा qib - queue inक्रमmation block (QIB)
 * @qfmt: queue क्रमmat
 * @pfmt: implementation dependent parameter क्रमmat
 * @rflags: QEBSM
 * @ac: adapter अक्षरacteristics
 * @isliba: असलolute address of first input SLIB
 * @osliba: असलolute address of first output SLIB
 * @ebcnam: adapter identअगरier in EBCDIC
 * @parm: implementation dependent parameters
 */
काष्ठा qib अणु
	u32 qfmt   : 8;
	u32 pfmt   : 8;
	u32 rflags : 8;
	u32 ac	   : 8;
	u32	   : 32;
	u64 isliba;
	u64 osliba;
	u32	   : 32;
	u32	   : 32;
	u8 ebcnam[8];
	/* निजी: */
	u8 res[88];
	/* खुला: */
	u8 parm[128];
पूर्ण __attribute__ ((packed, aligned(256)));

/**
 * काष्ठा slibe - storage list inक्रमmation block element (SLIBE)
 * @parms: implementation dependent parameters
 */
काष्ठा slibe अणु
	u64 parms;
पूर्ण;

/**
 * काष्ठा qaob - queue asynchronous operation block
 * @res0: reserved parameters
 * @res1: reserved parameter
 * @res2: reserved parameter
 * @res3: reserved parameter
 * @aorc: asynchronous operation वापस code
 * @flags: पूर्णांकernal flags
 * @cbtbs: control block type
 * @sb_count: number of storage blocks
 * @sba: storage block element addresses
 * @dcount: size of storage block elements
 * @user0: user defineable value
 * @res4: reserved paramater
 * @user1: user defineable value
 * @user2: user defineable value
 */
काष्ठा qaob अणु
	u64 res0[6];
	u8 res1;
	u8 res2;
	u8 res3;
	u8 aorc;
	u8 flags;
	u16 cbtbs;
	u8 sb_count;
	u64 sba[QDIO_MAX_ELEMENTS_PER_BUFFER];
	u16 dcount[QDIO_MAX_ELEMENTS_PER_BUFFER];
	u64 user0;
	u64 res4[2];
	u64 user1;
	u64 user2;
पूर्ण __attribute__ ((packed, aligned(256)));

/**
 * काष्ठा slib - storage list inक्रमmation block (SLIB)
 * @nsliba: next SLIB address (अगर any)
 * @sla: SL address
 * @slsba: SLSB address
 * @slibe: SLIB elements
 */
काष्ठा slib अणु
	u64 nsliba;
	u64 sla;
	u64 slsba;
	/* निजी: */
	u8 res[1000];
	/* खुला: */
	काष्ठा slibe slibe[QDIO_MAX_BUFFERS_PER_Q];
पूर्ण __attribute__ ((packed, aligned(2048)));

#घोषणा SBAL_EFLAGS_LAST_ENTRY		0x40
#घोषणा SBAL_EFLAGS_CONTIGUOUS		0x20
#घोषणा SBAL_EFLAGS_FIRST_FRAG		0x04
#घोषणा SBAL_EFLAGS_MIDDLE_FRAG		0x08
#घोषणा SBAL_EFLAGS_LAST_FRAG		0x0c
#घोषणा SBAL_EFLAGS_MASK		0x6f

#घोषणा SBAL_SFLAGS0_PCI_REQ		0x40
#घोषणा SBAL_SFLAGS0_DATA_CONTINUATION	0x20

/* Awesome OpenFCP extensions */
#घोषणा SBAL_SFLAGS0_TYPE_STATUS	0x00
#घोषणा SBAL_SFLAGS0_TYPE_WRITE		0x08
#घोषणा SBAL_SFLAGS0_TYPE_READ		0x10
#घोषणा SBAL_SFLAGS0_TYPE_WRITE_READ	0x18
#घोषणा SBAL_SFLAGS0_MORE_SBALS		0x04
#घोषणा SBAL_SFLAGS0_COMMAND		0x02
#घोषणा SBAL_SFLAGS0_LAST_SBAL		0x00
#घोषणा SBAL_SFLAGS0_ONLY_SBAL		SBAL_SFLAGS0_COMMAND
#घोषणा SBAL_SFLAGS0_MIDDLE_SBAL	SBAL_SFLAGS0_MORE_SBALS
#घोषणा SBAL_SFLAGS0_FIRST_SBAL (SBAL_SFLAGS0_MORE_SBALS | SBAL_SFLAGS0_COMMAND)

/**
 * काष्ठा qdio_buffer_element - SBAL entry
 * @eflags: SBAL entry flags
 * @scount: SBAL count
 * @sflags: whole SBAL flags
 * @length: length
 * @addr: असलolute data address
*/
काष्ठा qdio_buffer_element अणु
	u8 eflags;
	/* निजी: */
	u8 res1;
	/* खुला: */
	u8 scount;
	u8 sflags;
	u32 length;
	u64 addr;
पूर्ण __attribute__ ((packed, aligned(16)));

/**
 * काष्ठा qdio_buffer - storage block address list (SBAL)
 * @element: SBAL entries
 */
काष्ठा qdio_buffer अणु
	काष्ठा qdio_buffer_element element[QDIO_MAX_ELEMENTS_PER_BUFFER];
पूर्ण __attribute__ ((packed, aligned(256)));

/**
 * काष्ठा sl_element - storage list entry
 * @sbal: असलolute SBAL address
 */
काष्ठा sl_element अणु
	u64 sbal;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा sl - storage list (SL)
 * @element: SL entries
 */
काष्ठा sl अणु
	काष्ठा sl_element element[QDIO_MAX_BUFFERS_PER_Q];
पूर्ण __attribute__ ((packed, aligned(1024)));

/**
 * काष्ठा slsb - storage list state block (SLSB)
 * @val: state per buffer
 */
काष्ठा slsb अणु
	u8 val[QDIO_MAX_BUFFERS_PER_Q];
पूर्ण __attribute__ ((packed, aligned(256)));

/* qdio adapter-अक्षरacteristics-1 flag */
#घोषणा CHSC_AC1_INITIATE_INPUTQ	0x80
#घोषणा AC1_SIGA_INPUT_NEEDED		0x40	/* process input queues */
#घोषणा AC1_SIGA_OUTPUT_NEEDED		0x20	/* process output queues */
#घोषणा AC1_SIGA_SYNC_NEEDED		0x10	/* ask hypervisor to sync */
#घोषणा AC1_AUTOMATIC_SYNC_ON_THININT	0x08	/* set by hypervisor */
#घोषणा AC1_AUTOMATIC_SYNC_ON_OUT_PCI	0x04	/* set by hypervisor */
#घोषणा AC1_SC_QEBSM_AVAILABLE		0x02	/* available क्रम subchannel */
#घोषणा AC1_SC_QEBSM_ENABLED		0x01	/* enabled क्रम subchannel */

#घोषणा CHSC_AC2_MULTI_BUFFER_AVAILABLE	0x0080
#घोषणा CHSC_AC2_MULTI_BUFFER_ENABLED	0x0040
#घोषणा CHSC_AC2_DATA_DIV_AVAILABLE	0x0010
#घोषणा CHSC_AC2_SNIFFER_AVAILABLE	0x0008
#घोषणा CHSC_AC2_DATA_DIV_ENABLED	0x0002

#घोषणा CHSC_AC3_FORMAT2_CQ_AVAILABLE	0x8000

काष्ठा qdio_ssqd_desc अणु
	u8 flags;
	u8:8;
	u16 sch;
	u8 qfmt;
	u8 parm;
	u8 qdioac1;
	u8 sch_class;
	u8 pcnt;
	u8 icnt;
	u8:8;
	u8 ocnt;
	u8:8;
	u8 mbccnt;
	u16 qdioac2;
	u64 sch_token;
	u8 mro;
	u8 mri;
	u16 qdioac3;
	u16:16;
	u8:8;
	u8 mmwc;
पूर्ण __attribute__ ((packed));

/* params are: ccw_device, qdio_error, queue_number,
   first element processed, number of elements processed, पूर्णांक_parm */
प्रकार व्योम qdio_handler_t(काष्ठा ccw_device *, अचिन्हित पूर्णांक, पूर्णांक,
			    पूर्णांक, पूर्णांक, अचिन्हित दीर्घ);

/* qdio errors reported to the upper-layer program */
#घोषणा QDIO_ERROR_ACTIVATE			0x0001
#घोषणा QDIO_ERROR_GET_BUF_STATE		0x0002
#घोषणा QDIO_ERROR_SET_BUF_STATE		0x0004
#घोषणा QDIO_ERROR_SLSB_STATE			0x0100
#घोषणा QDIO_ERROR_SLSB_PENDING			0x0200

#घोषणा QDIO_ERROR_FATAL			0x00ff
#घोषणा QDIO_ERROR_TEMPORARY			0xff00

/* क्रम qdio_cleanup */
#घोषणा QDIO_FLAG_CLEANUP_USING_CLEAR		0x01
#घोषणा QDIO_FLAG_CLEANUP_USING_HALT		0x02

/**
 * काष्ठा qdio_initialize - qdio initialization data
 * @q_क्रमmat: queue क्रमmat
 * @qdr_ac: feature flags to set
 * @qib_param_field_क्रमmat: क्रमmat क्रम qib_parm_field
 * @qib_param_field: poपूर्णांकer to 128 bytes or शून्य, अगर no param field
 * @qib_rflags: rflags to set
 * @input_slib_elements: poपूर्णांकer to no_input_qs * 128 words of data or शून्य
 * @output_slib_elements: poपूर्णांकer to no_output_qs * 128 words of data or शून्य
 * @no_input_qs: number of input queues
 * @no_output_qs: number of output queues
 * @input_handler: handler to be called क्रम input queues
 * @output_handler: handler to be called क्रम output queues
 * @irq_poll: Data IRQ polling handler
 * @scan_threshold: # of in-use buffers that triggers scan on output queue
 * @पूर्णांक_parm: पूर्णांकerruption parameter
 * @input_sbal_addr_array:  per-queue array, each element poपूर्णांकs to 128 SBALs
 * @output_sbal_addr_array: per-queue array, each element poपूर्णांकs to 128 SBALs
 */
काष्ठा qdio_initialize अणु
	अचिन्हित अक्षर q_क्रमmat;
	अचिन्हित अक्षर qdr_ac;
	अचिन्हित पूर्णांक qib_param_field_क्रमmat;
	अचिन्हित अक्षर *qib_param_field;
	अचिन्हित अक्षर qib_rflags;
	अचिन्हित दीर्घ *input_slib_elements;
	अचिन्हित दीर्घ *output_slib_elements;
	अचिन्हित पूर्णांक no_input_qs;
	अचिन्हित पूर्णांक no_output_qs;
	qdio_handler_t *input_handler;
	qdio_handler_t *output_handler;
	व्योम (*irq_poll)(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ data);
	अचिन्हित पूर्णांक scan_threshold;
	अचिन्हित दीर्घ पूर्णांक_parm;
	काष्ठा qdio_buffer ***input_sbal_addr_array;
	काष्ठा qdio_buffer ***output_sbal_addr_array;
पूर्ण;

#घोषणा QDIO_STATE_INACTIVE		0x00000002 /* after qdio_cleanup */
#घोषणा QDIO_STATE_ESTABLISHED		0x00000004 /* after qdio_establish */
#घोषणा QDIO_STATE_ACTIVE		0x00000008 /* after qdio_activate */
#घोषणा QDIO_STATE_STOPPED		0x00000010 /* after queues went करोwn */

#घोषणा QDIO_FLAG_SYNC_INPUT		0x01
#घोषणा QDIO_FLAG_SYNC_OUTPUT		0x02
#घोषणा QDIO_FLAG_PCI_OUT		0x10

पूर्णांक qdio_alloc_buffers(काष्ठा qdio_buffer **buf, अचिन्हित पूर्णांक count);
व्योम qdio_मुक्त_buffers(काष्ठा qdio_buffer **buf, अचिन्हित पूर्णांक count);
व्योम qdio_reset_buffers(काष्ठा qdio_buffer **buf, अचिन्हित पूर्णांक count);

बाह्य पूर्णांक qdio_allocate(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक no_input_qs,
			 अचिन्हित पूर्णांक no_output_qs);
बाह्य पूर्णांक qdio_establish(काष्ठा ccw_device *cdev,
			  काष्ठा qdio_initialize *init_data);
बाह्य पूर्णांक qdio_activate(काष्ठा ccw_device *);
बाह्य काष्ठा qaob *qdio_allocate_aob(व्योम);
बाह्य व्योम qdio_release_aob(काष्ठा qaob *);
बाह्य पूर्णांक करो_QDIO(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक callflags, पूर्णांक q_nr,
		   अचिन्हित पूर्णांक bufnr, अचिन्हित पूर्णांक count, काष्ठा qaob *aob);
बाह्य पूर्णांक qdio_start_irq(काष्ठा ccw_device *cdev);
बाह्य पूर्णांक qdio_stop_irq(काष्ठा ccw_device *cdev);
बाह्य पूर्णांक qdio_get_next_buffers(काष्ठा ccw_device *, पूर्णांक, पूर्णांक *, पूर्णांक *);
बाह्य पूर्णांक qdio_inspect_queue(काष्ठा ccw_device *cdev, अचिन्हित पूर्णांक nr,
			      bool is_input, अचिन्हित पूर्णांक *bufnr,
			      अचिन्हित पूर्णांक *error);
बाह्य पूर्णांक qdio_shutकरोwn(काष्ठा ccw_device *, पूर्णांक);
बाह्य पूर्णांक qdio_मुक्त(काष्ठा ccw_device *);
बाह्य पूर्णांक qdio_get_ssqd_desc(काष्ठा ccw_device *, काष्ठा qdio_ssqd_desc *);

#पूर्ण_अगर /* __QDIO_H__ */
