<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Private stuff क्रम vfio_ccw driver
 *
 * Copyright IBM Corp. 2017
 * Copyright Red Hat, Inc. 2019
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Xiao Feng Ren <renxiaof@linux.vnet.ibm.com>
 *            Cornelia Huck <cohuck@redhat.com>
 */

#अगर_अघोषित _VFIO_CCW_PRIVATE_H_
#घोषणा _VFIO_CCW_PRIVATE_H_

#समावेश <linux/completion.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/vfio_ccw.h>
#समावेश <यंत्र/crw.h>
#समावेश <यंत्र/debug.h>

#समावेश "css.h"
#समावेश "vfio_ccw_cp.h"

#घोषणा VFIO_CCW_OFFSET_SHIFT   10
#घोषणा VFIO_CCW_OFFSET_TO_INDEX(off)	(off >> VFIO_CCW_OFFSET_SHIFT)
#घोषणा VFIO_CCW_INDEX_TO_OFFSET(index)	((u64)(index) << VFIO_CCW_OFFSET_SHIFT)
#घोषणा VFIO_CCW_OFFSET_MASK	(((u64)(1) << VFIO_CCW_OFFSET_SHIFT) - 1)

/* capability chain handling similar to vfio-pci */
काष्ठा vfio_ccw_निजी;
काष्ठा vfio_ccw_region;

काष्ठा vfio_ccw_regops अणु
	sमाप_प्रकार	(*पढ़ो)(काष्ठा vfio_ccw_निजी *निजी, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार	(*ग_लिखो)(काष्ठा vfio_ccw_निजी *निजी,
			 स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
	व्योम	(*release)(काष्ठा vfio_ccw_निजी *निजी,
			   काष्ठा vfio_ccw_region *region);
पूर्ण;

काष्ठा vfio_ccw_region अणु
	u32				type;
	u32				subtype;
	स्थिर काष्ठा vfio_ccw_regops	*ops;
	व्योम				*data;
	माप_प्रकार				size;
	u32				flags;
पूर्ण;

पूर्णांक vfio_ccw_रेजिस्टर_dev_region(काष्ठा vfio_ccw_निजी *निजी,
				 अचिन्हित पूर्णांक subtype,
				 स्थिर काष्ठा vfio_ccw_regops *ops,
				 माप_प्रकार size, u32 flags, व्योम *data);
व्योम vfio_ccw_unरेजिस्टर_dev_regions(काष्ठा vfio_ccw_निजी *निजी);

पूर्णांक vfio_ccw_रेजिस्टर_async_dev_regions(काष्ठा vfio_ccw_निजी *निजी);
पूर्णांक vfio_ccw_रेजिस्टर_schib_dev_regions(काष्ठा vfio_ccw_निजी *निजी);
पूर्णांक vfio_ccw_रेजिस्टर_crw_dev_regions(काष्ठा vfio_ccw_निजी *निजी);

काष्ठा vfio_ccw_crw अणु
	काष्ठा list_head	next;
	काष्ठा crw		crw;
पूर्ण;

/**
 * काष्ठा vfio_ccw_निजी
 * @sch: poपूर्णांकer to the subchannel
 * @state: पूर्णांकernal state of the device
 * @completion: synchronization helper of the I/O completion
 * @avail: available क्रम creating a mediated device
 * @mdev: poपूर्णांकer to the mediated device
 * @nb: notअगरier क्रम vfio events
 * @io_region: MMIO region to input/output I/O arguments/results
 * @io_mutex: protect against concurrent update of I/O regions
 * @region: additional regions क्रम other subchannel operations
 * @cmd_region: MMIO region क्रम asynchronous I/O commands other than START
 * @schib_region: MMIO region क्रम SCHIB inक्रमmation
 * @crw_region: MMIO region क्रम getting channel report words
 * @num_regions: number of additional regions
 * @cp: channel program क्रम the current I/O operation
 * @irb: irb info received from पूर्णांकerrupt
 * @scsw: scsw info
 * @io_trigger: eventfd ctx क्रम संकेतing userspace I/O results
 * @crw_trigger: eventfd ctx क्रम संकेतing userspace CRW inक्रमmation
 * @req_trigger: eventfd ctx क्रम संकेतing userspace to वापस device
 * @io_work: work क्रम deferral process of I/O handling
 * @crw_work: work क्रम deferral process of CRW handling
 */
काष्ठा vfio_ccw_निजी अणु
	काष्ठा subchannel	*sch;
	पूर्णांक			state;
	काष्ठा completion	*completion;
	atomic_t		avail;
	काष्ठा mdev_device	*mdev;
	काष्ठा notअगरier_block	nb;
	काष्ठा ccw_io_region	*io_region;
	काष्ठा mutex		io_mutex;
	काष्ठा vfio_ccw_region *region;
	काष्ठा ccw_cmd_region	*cmd_region;
	काष्ठा ccw_schib_region *schib_region;
	काष्ठा ccw_crw_region	*crw_region;
	पूर्णांक num_regions;

	काष्ठा channel_program	cp;
	काष्ठा irb		irb;
	जोड़ scsw		scsw;
	काष्ठा list_head	crw;

	काष्ठा eventfd_ctx	*io_trigger;
	काष्ठा eventfd_ctx	*crw_trigger;
	काष्ठा eventfd_ctx	*req_trigger;
	काष्ठा work_काष्ठा	io_work;
	काष्ठा work_काष्ठा	crw_work;
पूर्ण __aligned(8);

बाह्य पूर्णांक vfio_ccw_mdev_reg(काष्ठा subchannel *sch);
बाह्य व्योम vfio_ccw_mdev_unreg(काष्ठा subchannel *sch);

बाह्य पूर्णांक vfio_ccw_sch_quiesce(काष्ठा subchannel *sch);

/*
 * States of the device statemachine.
 */
क्रमागत vfio_ccw_state अणु
	VFIO_CCW_STATE_NOT_OPER,
	VFIO_CCW_STATE_STANDBY,
	VFIO_CCW_STATE_IDLE,
	VFIO_CCW_STATE_CP_PROCESSING,
	VFIO_CCW_STATE_CP_PENDING,
	/* last element! */
	NR_VFIO_CCW_STATES
पूर्ण;

/*
 * Asynchronous events of the device statemachine.
 */
क्रमागत vfio_ccw_event अणु
	VFIO_CCW_EVENT_NOT_OPER,
	VFIO_CCW_EVENT_IO_REQ,
	VFIO_CCW_EVENT_INTERRUPT,
	VFIO_CCW_EVENT_ASYNC_REQ,
	/* last element! */
	NR_VFIO_CCW_EVENTS
पूर्ण;

/*
 * Action called through jumptable.
 */
प्रकार व्योम (fsm_func_t)(काष्ठा vfio_ccw_निजी *, क्रमागत vfio_ccw_event);
बाह्य fsm_func_t *vfio_ccw_jumptable[NR_VFIO_CCW_STATES][NR_VFIO_CCW_EVENTS];

अटल अंतरभूत व्योम vfio_ccw_fsm_event(काष्ठा vfio_ccw_निजी *निजी,
				     पूर्णांक event)
अणु
	trace_vfio_ccw_fsm_event(निजी->sch->schid, निजी->state, event);
	vfio_ccw_jumptable[निजी->state][event](निजी, event);
पूर्ण

बाह्य काष्ठा workqueue_काष्ठा *vfio_ccw_work_q;


/* s390 debug feature, similar to base cio */
बाह्य debug_info_t *vfio_ccw_debug_msg_id;
बाह्य debug_info_t *vfio_ccw_debug_trace_id;

#घोषणा VFIO_CCW_TRACE_EVENT(imp, txt) \
		debug_text_event(vfio_ccw_debug_trace_id, imp, txt)

#घोषणा VFIO_CCW_MSG_EVENT(imp, args...) \
		debug_प्र_लिखो_event(vfio_ccw_debug_msg_id, imp, ##args)

अटल अंतरभूत व्योम VFIO_CCW_HEX_EVENT(पूर्णांक level, व्योम *data, पूर्णांक length)
अणु
	debug_event(vfio_ccw_debug_trace_id, level, data, length);
पूर्ण

#पूर्ण_अगर
