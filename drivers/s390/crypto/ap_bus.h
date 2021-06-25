<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright IBM Corp. 2006, 2019
 * Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Ralph Wuerthner <rwuerthn@de.ibm.com>
 *	      Felix Beck <felix.beck@de.ibm.com>
 *	      Holger Dengler <hd@linux.vnet.ibm.com>
 *
 * Adjunct processor bus header file.
 */

#अगर_अघोषित _AP_BUS_H_
#घोषणा _AP_BUS_H_

#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/hashtable.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/ap.h>

#घोषणा AP_DEVICES 256		/* Number of AP devices. */
#घोषणा AP_DOMAINS 256		/* Number of AP करोमुख्यs. */
#घोषणा AP_IOCTLS  256		/* Number of ioctls. */
#घोषणा AP_RESET_TIMEOUT (HZ*0.7)	/* Time in ticks क्रम reset समयouts. */
#घोषणा AP_CONFIG_TIME 30	/* Time in seconds between AP bus rescans. */
#घोषणा AP_POLL_TIME 1		/* Time in ticks between receive polls. */

बाह्य पूर्णांक ap_करोमुख्य_index;

बाह्य DECLARE_HASHTABLE(ap_queues, 8);
बाह्य spinlock_t ap_queues_lock;

अटल अंतरभूत पूर्णांक ap_test_bit(अचिन्हित पूर्णांक *ptr, अचिन्हित पूर्णांक nr)
अणु
	वापस (*ptr & (0x80000000u >> nr)) != 0;
पूर्ण

#घोषणा AP_RESPONSE_NORMAL		0x00
#घोषणा AP_RESPONSE_Q_NOT_AVAIL		0x01
#घोषणा AP_RESPONSE_RESET_IN_PROGRESS	0x02
#घोषणा AP_RESPONSE_DECONFIGURED	0x03
#घोषणा AP_RESPONSE_CHECKSTOPPED	0x04
#घोषणा AP_RESPONSE_BUSY		0x05
#घोषणा AP_RESPONSE_INVALID_ADDRESS	0x06
#घोषणा AP_RESPONSE_OTHERWISE_CHANGED	0x07
#घोषणा AP_RESPONSE_Q_FULL		0x10
#घोषणा AP_RESPONSE_NO_PENDING_REPLY	0x10
#घोषणा AP_RESPONSE_INDEX_TOO_BIG	0x11
#घोषणा AP_RESPONSE_NO_FIRST_PART	0x13
#घोषणा AP_RESPONSE_MESSAGE_TOO_BIG	0x15
#घोषणा AP_RESPONSE_REQ_FAC_NOT_INST	0x16
#घोषणा AP_RESPONSE_INVALID_DOMAIN	0x42

/*
 * Known device types
 */
#घोषणा AP_DEVICE_TYPE_PCICC	3
#घोषणा AP_DEVICE_TYPE_PCICA	4
#घोषणा AP_DEVICE_TYPE_PCIXCC	5
#घोषणा AP_DEVICE_TYPE_CEX2A	6
#घोषणा AP_DEVICE_TYPE_CEX2C	7
#घोषणा AP_DEVICE_TYPE_CEX3A	8
#घोषणा AP_DEVICE_TYPE_CEX3C	9
#घोषणा AP_DEVICE_TYPE_CEX4	10
#घोषणा AP_DEVICE_TYPE_CEX5	11
#घोषणा AP_DEVICE_TYPE_CEX6	12
#घोषणा AP_DEVICE_TYPE_CEX7	13

/*
 * Known function facilities
 */
#घोषणा AP_FUNC_MEX4K 1
#घोषणा AP_FUNC_CRT4K 2
#घोषणा AP_FUNC_COPRO 3
#घोषणा AP_FUNC_ACCEL 4
#घोषणा AP_FUNC_EP11  5
#घोषणा AP_FUNC_APXA  6

/*
 * AP पूर्णांकerrupt states
 */
#घोषणा AP_INTR_DISABLED	0	/* AP पूर्णांकerrupt disabled */
#घोषणा AP_INTR_ENABLED		1	/* AP पूर्णांकerrupt enabled */

/*
 * AP queue state machine states
 */
क्रमागत ap_sm_state अणु
	AP_SM_STATE_RESET_START = 0,
	AP_SM_STATE_RESET_WAIT,
	AP_SM_STATE_SETIRQ_WAIT,
	AP_SM_STATE_IDLE,
	AP_SM_STATE_WORKING,
	AP_SM_STATE_QUEUE_FULL,
	NR_AP_SM_STATES
पूर्ण;

/*
 * AP queue state machine events
 */
क्रमागत ap_sm_event अणु
	AP_SM_EVENT_POLL,
	AP_SM_EVENT_TIMEOUT,
	NR_AP_SM_EVENTS
पूर्ण;

/*
 * AP queue state रुको behaviour
 */
क्रमागत ap_sm_रुको अणु
	AP_SM_WAIT_AGAIN,	/* retry immediately */
	AP_SM_WAIT_TIMEOUT,	/* रुको क्रम समयout */
	AP_SM_WAIT_INTERRUPT,	/* रुको क्रम thin पूर्णांकerrupt (अगर available) */
	AP_SM_WAIT_NONE,	/* no रुको */
	NR_AP_SM_WAIT
पूर्ण;

/*
 * AP queue device states
 */
क्रमागत ap_dev_state अणु
	AP_DEV_STATE_UNINITIATED = 0,	/* fresh and virgin, not touched */
	AP_DEV_STATE_OPERATING,		/* queue dev is working normal */
	AP_DEV_STATE_SHUTDOWN,		/* हटाओ/unbind/shutकरोwn in progress */
	AP_DEV_STATE_ERROR,		/* device is in error state */
	NR_AP_DEV_STATES
पूर्ण;

काष्ठा ap_device;
काष्ठा ap_message;

/*
 * The ap driver काष्ठा includes a flags field which holds some info क्रम
 * the ap bus about the driver. Currently only one flag is supported and
 * used: The DEFAULT flag marks an ap driver as a शेष driver which is
 * used together with the apmask and aqmask whitelisting of the ap bus.
 */
#घोषणा AP_DRIVER_FLAG_DEFAULT 0x0001

काष्ठा ap_driver अणु
	काष्ठा device_driver driver;
	काष्ठा ap_device_id *ids;
	अचिन्हित पूर्णांक flags;

	पूर्णांक (*probe)(काष्ठा ap_device *);
	व्योम (*हटाओ)(काष्ठा ap_device *);
पूर्ण;

#घोषणा to_ap_drv(x) container_of((x), काष्ठा ap_driver, driver)

पूर्णांक ap_driver_रेजिस्टर(काष्ठा ap_driver *, काष्ठा module *, अक्षर *);
व्योम ap_driver_unरेजिस्टर(काष्ठा ap_driver *);

काष्ठा ap_device अणु
	काष्ठा device device;
	काष्ठा ap_driver *drv;		/* Poपूर्णांकer to AP device driver. */
	पूर्णांक device_type;		/* AP device type. */
पूर्ण;

#घोषणा to_ap_dev(x) container_of((x), काष्ठा ap_device, device)

काष्ठा ap_card अणु
	काष्ठा ap_device ap_dev;
	व्योम *निजी;			/* ap driver निजी poपूर्णांकer. */
	पूर्णांक raw_hwtype;			/* AP raw hardware type. */
	अचिन्हित पूर्णांक functions;		/* AP device function bitfield. */
	पूर्णांक queue_depth;		/* AP queue depth.*/
	पूर्णांक id;				/* AP card number. */
	bool config;			/* configured state */
	atomic64_t total_request_count;	/* # requests ever क्रम this AP device.*/
पूर्ण;

#घोषणा to_ap_card(x) container_of((x), काष्ठा ap_card, ap_dev.device)

काष्ठा ap_queue अणु
	काष्ठा ap_device ap_dev;
	काष्ठा hlist_node hnode;	/* Node क्रम the ap_queues hashtable */
	काष्ठा ap_card *card;		/* Ptr to assoc. AP card. */
	spinlock_t lock;		/* Per device lock. */
	व्योम *निजी;			/* ap driver निजी poपूर्णांकer. */
	क्रमागत ap_dev_state dev_state;	/* queue device state */
	bool config;			/* configured state */
	ap_qid_t qid;			/* AP queue id. */
	पूर्णांक पूर्णांकerrupt;			/* indicate अगर पूर्णांकerrupts are enabled */
	पूर्णांक queue_count;		/* # messages currently on AP queue. */
	पूर्णांक pendingq_count;		/* # requests on pendingq list. */
	पूर्णांक requestq_count;		/* # requests on requestq list. */
	u64 total_request_count;	/* # requests ever क्रम this AP device.*/
	पूर्णांक request_समयout;		/* Request समयout in jअगरfies. */
	काष्ठा समयr_list समयout;	/* Timer क्रम request समयouts. */
	काष्ठा list_head pendingq;	/* List of message sent to AP queue. */
	काष्ठा list_head requestq;	/* List of message yet to be sent. */
	काष्ठा ap_message *reply;	/* Per device reply message. */
	क्रमागत ap_sm_state sm_state;	/* ap queue state machine state */
	पूर्णांक last_err_rc;		/* last error state response code */
पूर्ण;

#घोषणा to_ap_queue(x) container_of((x), काष्ठा ap_queue, ap_dev.device)

प्रकार क्रमागत ap_sm_रुको (ap_func_t)(काष्ठा ap_queue *queue);

/* failure injection cmd काष्ठा */
काष्ठा ap_fi अणु
	जोड़ अणु
		u16 cmd;		/* fi flags + action */
		काष्ठा अणु
			u8 flags;	/* fi flags only */
			u8 action;	/* fi action only */
		पूर्ण;
	पूर्ण;
पूर्ण;

/* all currently known fi actions */
क्रमागत ap_fi_actions अणु
	AP_FI_ACTION_CCA_AGENT_FF   = 0x01,
	AP_FI_ACTION_CCA_DOM_INVAL  = 0x02,
	AP_FI_ACTION_NQAP_QID_INVAL = 0x03,
पूर्ण;

/* all currently known fi flags */
क्रमागत ap_fi_flags अणु
	AP_FI_FLAG_NO_RETRY	  = 0x01,
	AP_FI_FLAG_TOGGLE_SPECIAL = 0x02,
पूर्ण;

काष्ठा ap_message अणु
	काष्ठा list_head list;		/* Request queueing. */
	अचिन्हित दीर्घ दीर्घ psmid;	/* Message id. */
	व्योम *msg;			/* Poपूर्णांकer to message buffer. */
	अचिन्हित पूर्णांक len;		/* Message length. */
	u16 flags;			/* Flags, see AP_MSG_FLAG_xxx */
	काष्ठा ap_fi fi;		/* Failure Injection cmd */
	पूर्णांक rc;				/* Return code क्रम this message */
	व्योम *निजी;			/* ap driver निजी poपूर्णांकer. */
	/* receive is called from tasklet context */
	व्योम (*receive)(काष्ठा ap_queue *, काष्ठा ap_message *,
			काष्ठा ap_message *);
पूर्ण;

#घोषणा AP_MSG_FLAG_SPECIAL  1		/* flag msg as 'special' with NQAP */

/**
 * ap_init_message() - Initialize ap_message.
 * Initialize a message beक्रमe using. Otherwise this might result in
 * unexpected behaviour.
 */
अटल अंतरभूत व्योम ap_init_message(काष्ठा ap_message *ap_msg)
अणु
	स_रखो(ap_msg, 0, माप(*ap_msg));
पूर्ण

/**
 * ap_release_message() - Release ap_message.
 * Releases all memory used पूर्णांकernal within the ap_message काष्ठा
 * Currently this is the message and निजी field.
 */
अटल अंतरभूत व्योम ap_release_message(काष्ठा ap_message *ap_msg)
अणु
	kमुक्त_sensitive(ap_msg->msg);
	kमुक्त_sensitive(ap_msg->निजी);
पूर्ण

/*
 * Note: करोn't use ap_send/ap_recv after using ap_queue_message
 * क्रम the first समय. Otherwise the ap message queue will get
 * confused.
 */
पूर्णांक ap_send(ap_qid_t, अचिन्हित दीर्घ दीर्घ, व्योम *, माप_प्रकार);
पूर्णांक ap_recv(ap_qid_t, अचिन्हित दीर्घ दीर्घ *, व्योम *, माप_प्रकार);

क्रमागत ap_sm_रुको ap_sm_event(काष्ठा ap_queue *aq, क्रमागत ap_sm_event event);
क्रमागत ap_sm_रुको ap_sm_event_loop(काष्ठा ap_queue *aq, क्रमागत ap_sm_event event);

पूर्णांक ap_queue_message(काष्ठा ap_queue *aq, काष्ठा ap_message *ap_msg);
व्योम ap_cancel_message(काष्ठा ap_queue *aq, काष्ठा ap_message *ap_msg);
व्योम ap_flush_queue(काष्ठा ap_queue *aq);

व्योम *ap_airq_ptr(व्योम);
व्योम ap_रुको(क्रमागत ap_sm_रुको रुको);
व्योम ap_request_समयout(काष्ठा समयr_list *t);
व्योम ap_bus_क्रमce_rescan(व्योम);

पूर्णांक ap_test_config_usage_करोमुख्य(अचिन्हित पूर्णांक करोमुख्य);
पूर्णांक ap_test_config_ctrl_करोमुख्य(अचिन्हित पूर्णांक करोमुख्य);

व्योम ap_queue_init_reply(काष्ठा ap_queue *aq, काष्ठा ap_message *ap_msg);
काष्ठा ap_queue *ap_queue_create(ap_qid_t qid, पूर्णांक device_type);
व्योम ap_queue_prepare_हटाओ(काष्ठा ap_queue *aq);
व्योम ap_queue_हटाओ(काष्ठा ap_queue *aq);
व्योम ap_queue_init_state(काष्ठा ap_queue *aq);

काष्ठा ap_card *ap_card_create(पूर्णांक id, पूर्णांक queue_depth, पूर्णांक raw_device_type,
			       पूर्णांक comp_device_type, अचिन्हित पूर्णांक functions);

काष्ठा ap_perms अणु
	अचिन्हित दीर्घ ioctlm[BITS_TO_LONGS(AP_IOCTLS)];
	अचिन्हित दीर्घ apm[BITS_TO_LONGS(AP_DEVICES)];
	अचिन्हित दीर्घ aqm[BITS_TO_LONGS(AP_DOMAINS)];
पूर्ण;
बाह्य काष्ठा ap_perms ap_perms;
बाह्य काष्ठा mutex ap_perms_mutex;

/*
 * Get ap_queue device क्रम this qid.
 * Returns ptr to the काष्ठा ap_queue device or शून्य अगर there
 * was no ap_queue device with this qid found. When something is
 * found, the reference count of the embedded device is increased.
 * So the caller has to decrease the reference count after use
 * with a call to put_device(&aq->ap_dev.device).
 */
काष्ठा ap_queue *ap_get_qdev(ap_qid_t qid);

/*
 * check APQN क्रम owned/reserved by ap bus and शेष driver(s).
 * Checks अगर this APQN is or will be in use by the ap bus
 * and the शेष set of drivers.
 * If yes, वापसs 1, अगर not वापसs 0. On error a negative
 * त्रुटि_सं value is वापसed.
 */
पूर्णांक ap_owned_by_def_drv(पूर्णांक card, पूर्णांक queue);

/*
 * check 'matrix' of APQNs क्रम owned/reserved by ap bus and
 * शेष driver(s).
 * Checks अगर there is at least one APQN in the given 'matrix'
 * marked as owned/reserved by the ap bus and शेष driver(s).
 * If such an APQN is found the वापस value is 1, otherwise
 * 0 is वापसed. On error a negative त्रुटि_सं value is वापसed.
 * The parameter apm is a biपंचांगask which should be declared
 * as DECLARE_BITMAP(apm, AP_DEVICES), the aqm parameter is
 * similar, should be declared as DECLARE_BITMAP(aqm, AP_DOMAINS).
 */
पूर्णांक ap_apqn_in_matrix_owned_by_def_drv(अचिन्हित दीर्घ *apm,
				       अचिन्हित दीर्घ *aqm);

/*
 * ap_parse_mask_str() - helper function to parse a biपंचांगap string
 * and clear/set the bits in the biपंचांगap accordingly. The string may be
 * given as असलolute value, a hex string like 0x1F2E3D4C5B6A" simple
 * overwriting the current content of the biपंचांगap. Or as relative string
 * like "+1-16,-32,-0x40,+128" where only single bits or ranges of
 * bits are cleared or set. Distinction is करोne based on the very
 * first अक्षरacter which may be '+' or '-' क्रम the relative string
 * and othewise assume to be an असलolute value string. If parsing fails
 * a negative त्रुटि_सं value is वापसed. All arguments and biपंचांगaps are
 * big endian order.
 */
पूर्णांक ap_parse_mask_str(स्थिर अक्षर *str,
		      अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bits,
		      काष्ठा mutex *lock);

/*
 * Interface to रुको क्रम the AP bus to have करोne one initial ap bus
 * scan and all detected APQNs have been bound to device drivers.
 * If these both conditions are not fulfilled, this function blocks
 * on a condition with रुको_क्रम_completion_समाप्तable_समयout().
 * If these both conditions are fulfilled (beक्रमe the समयout hits)
 * the वापस value is 0. If the समयout (in jअगरfies) hits instead
 * -ETIME is वापसed. On failures negative वापस values are
 * वापसed to the caller.
 */
पूर्णांक ap_रुको_init_apqn_bindings_complete(अचिन्हित दीर्घ समयout);

#पूर्ण_अगर /* _AP_BUS_H_ */
