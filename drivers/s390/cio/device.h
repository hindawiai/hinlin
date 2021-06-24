<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_DEVICE_H
#घोषणा S390_DEVICE_H

#समावेश <यंत्र/ccwdev.h>
#समावेश <linux/atomic.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश "io_sch.h"

/*
 * states of the device statemachine
 */
क्रमागत dev_state अणु
	DEV_STATE_NOT_OPER,
	DEV_STATE_SENSE_ID,
	DEV_STATE_OFFLINE,
	DEV_STATE_VERIFY,
	DEV_STATE_ONLINE,
	DEV_STATE_W4SENSE,
	DEV_STATE_DISBAND_PGID,
	DEV_STATE_BOXED,
	/* states to रुको क्रम i/o completion beक्रमe करोing something */
	DEV_STATE_TIMEOUT_KILL,
	DEV_STATE_QUIESCE,
	/* special states क्रम devices gone not operational */
	DEV_STATE_DISCONNECTED,
	DEV_STATE_DISCONNECTED_SENSE_ID,
	DEV_STATE_CMFCHANGE,
	DEV_STATE_CMFUPDATE,
	DEV_STATE_STEAL_LOCK,
	/* last element! */
	NR_DEV_STATES
पूर्ण;

/*
 * asynchronous events of the device statemachine
 */
क्रमागत dev_event अणु
	DEV_EVENT_NOTOPER,
	DEV_EVENT_INTERRUPT,
	DEV_EVENT_TIMEOUT,
	DEV_EVENT_VERIFY,
	/* last element! */
	NR_DEV_EVENTS
पूर्ण;

काष्ठा ccw_device;

/*
 * action called through jumptable
 */
प्रकार व्योम (fsm_func_t)(काष्ठा ccw_device *, क्रमागत dev_event);
बाह्य fsm_func_t *dev_jumptable[NR_DEV_STATES][NR_DEV_EVENTS];

अटल अंतरभूत व्योम
dev_fsm_event(काष्ठा ccw_device *cdev, क्रमागत dev_event dev_event)
अणु
	पूर्णांक state = cdev->निजी->state;

	अगर (dev_event == DEV_EVENT_INTERRUPT) अणु
		अगर (state == DEV_STATE_ONLINE)
			inc_irq_stat(cdev->निजी->पूर्णांक_class);
		अन्यथा अगर (state != DEV_STATE_CMFCHANGE &&
			 state != DEV_STATE_CMFUPDATE)
			inc_irq_stat(IRQIO_CIO);
	पूर्ण
	dev_jumptable[state][dev_event](cdev, dev_event);
पूर्ण

/*
 * Delivers 1 अगर the device state is final.
 */
अटल अंतरभूत पूर्णांक
dev_fsm_final_state(काष्ठा ccw_device *cdev)
अणु
	वापस (cdev->निजी->state == DEV_STATE_NOT_OPER ||
		cdev->निजी->state == DEV_STATE_OFFLINE ||
		cdev->निजी->state == DEV_STATE_ONLINE ||
		cdev->निजी->state == DEV_STATE_BOXED);
पूर्ण

पूर्णांक __init io_subchannel_init(व्योम);

व्योम io_subchannel_recog_करोne(काष्ठा ccw_device *cdev);
व्योम io_subchannel_init_config(काष्ठा subchannel *sch);

पूर्णांक ccw_device_cancel_halt_clear(काष्ठा ccw_device *);

पूर्णांक ccw_device_is_orphan(काष्ठा ccw_device *);

व्योम ccw_device_recognition(काष्ठा ccw_device *);
पूर्णांक ccw_device_online(काष्ठा ccw_device *);
पूर्णांक ccw_device_offline(काष्ठा ccw_device *);
व्योम ccw_device_update_sense_data(काष्ठा ccw_device *);
पूर्णांक ccw_device_test_sense_data(काष्ठा ccw_device *);
पूर्णांक ccw_purge_blacklisted(व्योम);
व्योम ccw_device_sched_toकरो(काष्ठा ccw_device *cdev, क्रमागत cdev_toकरो toकरो);
काष्ठा ccw_device *get_ccwdev_by_dev_id(काष्ठा ccw_dev_id *dev_id);

/* Function prototypes क्रम device status and basic sense stuff. */
व्योम ccw_device_accumulate_irb(काष्ठा ccw_device *, काष्ठा irb *);
व्योम ccw_device_accumulate_basic_sense(काष्ठा ccw_device *, काष्ठा irb *);
पूर्णांक ccw_device_accumulate_and_sense(काष्ठा ccw_device *, काष्ठा irb *);
पूर्णांक ccw_device_करो_sense(काष्ठा ccw_device *, काष्ठा irb *);

/* Function prototype क्रम पूर्णांकernal request handling. */
पूर्णांक lpm_adjust(पूर्णांक lpm, पूर्णांक mask);
व्योम ccw_request_start(काष्ठा ccw_device *);
पूर्णांक ccw_request_cancel(काष्ठा ccw_device *cdev);
व्योम ccw_request_handler(काष्ठा ccw_device *cdev);
व्योम ccw_request_समयout(काष्ठा ccw_device *cdev);
व्योम ccw_request_notoper(काष्ठा ccw_device *cdev);

/* Function prototypes क्रम sense id stuff. */
व्योम ccw_device_sense_id_start(काष्ठा ccw_device *);
व्योम ccw_device_sense_id_करोne(काष्ठा ccw_device *, पूर्णांक);

/* Function prototypes क्रम path grouping stuff. */
व्योम ccw_device_verअगरy_start(काष्ठा ccw_device *);
व्योम ccw_device_verअगरy_करोne(काष्ठा ccw_device *, पूर्णांक);

व्योम ccw_device_disband_start(काष्ठा ccw_device *);
व्योम ccw_device_disband_करोne(काष्ठा ccw_device *, पूर्णांक);

पूर्णांक ccw_device_stlck(काष्ठा ccw_device *);

/* Helper function क्रम machine check handling. */
व्योम ccw_device_trigger_reprobe(काष्ठा ccw_device *);
व्योम ccw_device_समाप्त_io(काष्ठा ccw_device *);
पूर्णांक ccw_device_notअगरy(काष्ठा ccw_device *, पूर्णांक);
व्योम ccw_device_set_disconnected(काष्ठा ccw_device *cdev);
व्योम ccw_device_set_notoper(काष्ठा ccw_device *cdev);

व्योम ccw_device_समयout(काष्ठा समयr_list *t);
व्योम ccw_device_set_समयout(काष्ठा ccw_device *, पूर्णांक);
व्योम ccw_device_schedule_recovery(व्योम);

/* Channel measurement facility related */
व्योम retry_set_schib(काष्ठा ccw_device *cdev);
व्योम cmf_retry_copy_block(काष्ठा ccw_device *);
पूर्णांक cmf_reenable(काष्ठा ccw_device *);
व्योम cmf_reactivate(व्योम);
बाह्य काष्ठा device_attribute dev_attr_cmb_enable;
#पूर्ण_अगर
