<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright IBM Corp. 2006, 2020
 * Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Ralph Wuerthner <rwuerthn@de.ibm.com>
 *	      Felix Beck <felix.beck@de.ibm.com>
 *	      Holger Dengler <hd@linux.vnet.ibm.com>
 *	      Harald Freudenberger <freude@linux.ibm.com>
 *
 * Adjunct processor bus.
 */

#घोषणा KMSG_COMPONENT "ap"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/airq.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/isc.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kसमय.स>
#समावेश <यंत्र/facility.h>
#समावेश <linux/crypto.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/प्रकार.स>

#समावेश "ap_bus.h"
#समावेश "ap_debug.h"

/*
 * Module parameters; note though this file itself isn't modular.
 */
पूर्णांक ap_करोमुख्य_index = -1;	/* Adjunct Processor Doमुख्य Index */
अटल DEFINE_SPINLOCK(ap_करोमुख्य_lock);
module_param_named(करोमुख्य, ap_करोमुख्य_index, पूर्णांक, 0440);
MODULE_PARM_DESC(करोमुख्य, "domain index for ap devices");
EXPORT_SYMBOL(ap_करोमुख्य_index);

अटल पूर्णांक ap_thपढ़ो_flag;
module_param_named(poll_thपढ़ो, ap_thपढ़ो_flag, पूर्णांक, 0440);
MODULE_PARM_DESC(poll_thपढ़ो, "Turn on/off poll thread, default is 0 (off).");

अटल अक्षर *apm_str;
module_param_named(apmask, apm_str, अक्षरp, 0440);
MODULE_PARM_DESC(apmask, "AP bus adapter mask.");

अटल अक्षर *aqm_str;
module_param_named(aqmask, aqm_str, अक्षरp, 0440);
MODULE_PARM_DESC(aqmask, "AP bus domain mask.");

अटल काष्ठा device *ap_root_device;

/* Hashtable of all queue devices on the AP bus */
DEFINE_HASHTABLE(ap_queues, 8);
/* lock used क्रम the ap_queues hashtable */
DEFINE_SPINLOCK(ap_queues_lock);

/* Default permissions (ioctl, card and करोमुख्य masking) */
काष्ठा ap_perms ap_perms;
EXPORT_SYMBOL(ap_perms);
DEFINE_MUTEX(ap_perms_mutex);
EXPORT_SYMBOL(ap_perms_mutex);

/* # of bus scans since init */
अटल atomic64_t ap_scan_bus_count;

/* completion क्रम initial APQN bindings complete */
अटल DECLARE_COMPLETION(ap_init_apqn_bindings_complete);

अटल काष्ठा ap_config_info *ap_qci_info;

/*
 * AP bus related debug feature things.
 */
debug_info_t *ap_dbf_info;

/*
 * Workqueue समयr क्रम bus rescan.
 */
अटल काष्ठा समयr_list ap_config_समयr;
अटल पूर्णांक ap_config_समय = AP_CONFIG_TIME;
अटल व्योम ap_scan_bus(काष्ठा work_काष्ठा *);
अटल DECLARE_WORK(ap_scan_work, ap_scan_bus);

/*
 * Tasklet & समयr क्रम AP request polling and पूर्णांकerrupts
 */
अटल व्योम ap_tasklet_fn(अचिन्हित दीर्घ);
अटल DECLARE_TASKLET_OLD(ap_tasklet, ap_tasklet_fn);
अटल DECLARE_WAIT_QUEUE_HEAD(ap_poll_रुको);
अटल काष्ठा task_काष्ठा *ap_poll_kthपढ़ो;
अटल DEFINE_MUTEX(ap_poll_thपढ़ो_mutex);
अटल DEFINE_SPINLOCK(ap_poll_समयr_lock);
अटल काष्ठा hrसमयr ap_poll_समयr;
/*
 * In LPAR poll with 4kHz frequency. Poll every 250000 nanoseconds.
 * If z/VM change to 1500000 nanoseconds to adjust to z/VM polling.
 */
अटल अचिन्हित दीर्घ दीर्घ poll_समयout = 250000;

/* Maximum करोमुख्य id, अगर not given via qci */
अटल पूर्णांक ap_max_करोमुख्य_id = 15;
/* Maximum adapter id, अगर not given via qci */
अटल पूर्णांक ap_max_adapter_id = 63;

अटल काष्ठा bus_type ap_bus_type;

/* Adapter पूर्णांकerrupt definitions */
अटल व्योम ap_पूर्णांकerrupt_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing);

अटल पूर्णांक ap_airq_flag;

अटल काष्ठा airq_काष्ठा ap_airq = अणु
	.handler = ap_पूर्णांकerrupt_handler,
	.isc = AP_ISC,
पूर्ण;

/**
 * ap_using_पूर्णांकerrupts() - Returns non-zero अगर पूर्णांकerrupt support is
 * available.
 */
अटल अंतरभूत पूर्णांक ap_using_पूर्णांकerrupts(व्योम)
अणु
	वापस ap_airq_flag;
पूर्ण

/**
 * ap_airq_ptr() - Get the address of the adapter पूर्णांकerrupt indicator
 *
 * Returns the address of the local-summary-indicator of the adapter
 * पूर्णांकerrupt handler क्रम AP, or शून्य अगर adapter पूर्णांकerrupts are not
 * available.
 */
व्योम *ap_airq_ptr(व्योम)
अणु
	अगर (ap_using_पूर्णांकerrupts())
		वापस ap_airq.lsi_ptr;
	वापस शून्य;
पूर्ण

/**
 * ap_पूर्णांकerrupts_available(): Test अगर AP पूर्णांकerrupts are available.
 *
 * Returns 1 अगर AP पूर्णांकerrupts are available.
 */
अटल पूर्णांक ap_पूर्णांकerrupts_available(व्योम)
अणु
	वापस test_facility(65);
पूर्ण

/**
 * ap_qci_available(): Test अगर AP configuration
 * inक्रमmation can be queried via QCI subfunction.
 *
 * Returns 1 अगर subfunction PQAP(QCI) is available.
 */
अटल पूर्णांक ap_qci_available(व्योम)
अणु
	वापस test_facility(12);
पूर्ण

/**
 * ap_apft_available(): Test अगर AP facilities test (APFT)
 * facility is available.
 *
 * Returns 1 अगर APFT is is available.
 */
अटल पूर्णांक ap_apft_available(व्योम)
अणु
	वापस test_facility(15);
पूर्ण

/*
 * ap_qact_available(): Test अगर the PQAP(QACT) subfunction is available.
 *
 * Returns 1 अगर the QACT subfunction is available.
 */
अटल अंतरभूत पूर्णांक ap_qact_available(व्योम)
अणु
	अगर (ap_qci_info)
		वापस ap_qci_info->qact;
	वापस 0;
पूर्ण

/*
 * ap_fetch_qci_info(): Fetch cryptographic config info
 *
 * Returns the ap configuration info fetched via PQAP(QCI).
 * On success 0 is वापसed, on failure a negative त्रुटि_सं
 * is वापसed, e.g. अगर the PQAP(QCI) inकाष्ठाion is not
 * available, the वापस value will be -EOPNOTSUPP.
 */
अटल अंतरभूत पूर्णांक ap_fetch_qci_info(काष्ठा ap_config_info *info)
अणु
	अगर (!ap_qci_available())
		वापस -EOPNOTSUPP;
	अगर (!info)
		वापस -EINVAL;
	वापस ap_qci(info);
पूर्ण

/**
 * ap_init_qci_info(): Allocate and query qci config info.
 * Does also update the अटल variables ap_max_करोमुख्य_id
 * and ap_max_adapter_id अगर this info is available.

 */
अटल व्योम __init ap_init_qci_info(व्योम)
अणु
	अगर (!ap_qci_available()) अणु
		AP_DBF_INFO("%s QCI not supported\n", __func__);
		वापस;
	पूर्ण

	ap_qci_info = kzalloc(माप(*ap_qci_info), GFP_KERNEL);
	अगर (!ap_qci_info)
		वापस;
	अगर (ap_fetch_qci_info(ap_qci_info) != 0) अणु
		kमुक्त(ap_qci_info);
		ap_qci_info = शून्य;
		वापस;
	पूर्ण
	AP_DBF_INFO("%s successful fetched initial qci info\n", __func__);

	अगर (ap_qci_info->apxa) अणु
		अगर (ap_qci_info->Na) अणु
			ap_max_adapter_id = ap_qci_info->Na;
			AP_DBF_INFO("%s new ap_max_adapter_id is %d\n",
				    __func__, ap_max_adapter_id);
		पूर्ण
		अगर (ap_qci_info->Nd) अणु
			ap_max_करोमुख्य_id = ap_qci_info->Nd;
			AP_DBF_INFO("%s new ap_max_domain_id is %d\n",
				    __func__, ap_max_करोमुख्य_id);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ap_test_config(): helper function to extract the nrth bit
 *		     within the अचिन्हित पूर्णांक array field.
 */
अटल अंतरभूत पूर्णांक ap_test_config(अचिन्हित पूर्णांक *field, अचिन्हित पूर्णांक nr)
अणु
	वापस ap_test_bit((field + (nr >> 5)), (nr & 0x1f));
पूर्ण

/*
 * ap_test_config_card_id(): Test, whether an AP card ID is configured.
 *
 * Returns 0 अगर the card is not configured
 *	   1 अगर the card is configured or
 *	     अगर the configuration inक्रमmation is not available
 */
अटल अंतरभूत पूर्णांक ap_test_config_card_id(अचिन्हित पूर्णांक id)
अणु
	अगर (id > ap_max_adapter_id)
		वापस 0;
	अगर (ap_qci_info)
		वापस ap_test_config(ap_qci_info->apm, id);
	वापस 1;
पूर्ण

/*
 * ap_test_config_usage_करोमुख्य(): Test, whether an AP usage करोमुख्य
 * is configured.
 *
 * Returns 0 अगर the usage करोमुख्य is not configured
 *	   1 अगर the usage करोमुख्य is configured or
 *	     अगर the configuration inक्रमmation is not available
 */
पूर्णांक ap_test_config_usage_करोमुख्य(अचिन्हित पूर्णांक करोमुख्य)
अणु
	अगर (करोमुख्य > ap_max_करोमुख्य_id)
		वापस 0;
	अगर (ap_qci_info)
		वापस ap_test_config(ap_qci_info->aqm, करोमुख्य);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(ap_test_config_usage_करोमुख्य);

/*
 * ap_test_config_ctrl_करोमुख्य(): Test, whether an AP control करोमुख्य
 * is configured.
 * @करोमुख्य AP control करोमुख्य ID
 *
 * Returns 1 अगर the control करोमुख्य is configured
 *	   0 in all other हालs
 */
पूर्णांक ap_test_config_ctrl_करोमुख्य(अचिन्हित पूर्णांक करोमुख्य)
अणु
	अगर (!ap_qci_info || करोमुख्य > ap_max_करोमुख्य_id)
		वापस 0;
	वापस ap_test_config(ap_qci_info->adm, करोमुख्य);
पूर्ण
EXPORT_SYMBOL(ap_test_config_ctrl_करोमुख्य);

/*
 * ap_queue_info(): Check and get AP queue info.
 * Returns true अगर TAPQ succeeded and the info is filled or
 * false otherwise.
 */
अटल bool ap_queue_info(ap_qid_t qid, पूर्णांक *q_type,
			  अचिन्हित पूर्णांक *q_fac, पूर्णांक *q_depth, bool *q_decfg)
अणु
	काष्ठा ap_queue_status status;
	अचिन्हित दीर्घ info = 0;

	/* make sure we करोn't run पूर्णांकo a specअगरiation exception */
	अगर (AP_QID_CARD(qid) > ap_max_adapter_id ||
	    AP_QID_QUEUE(qid) > ap_max_करोमुख्य_id)
		वापस false;

	/* call TAPQ on this APQN */
	status = ap_test_queue(qid, ap_apft_available(), &info);
	चयन (status.response_code) अणु
	हाल AP_RESPONSE_NORMAL:
	हाल AP_RESPONSE_RESET_IN_PROGRESS:
	हाल AP_RESPONSE_DECONFIGURED:
	हाल AP_RESPONSE_CHECKSTOPPED:
	हाल AP_RESPONSE_BUSY:
		/*
		 * According to the architecture in all these हालs the
		 * info should be filled. All bits 0 is not possible as
		 * there is at least one of the mode bits set.
		 */
		अगर (WARN_ON_ONCE(!info))
			वापस false;
		*q_type = (पूर्णांक)((info >> 24) & 0xff);
		*q_fac = (अचिन्हित पूर्णांक)(info >> 32);
		*q_depth = (पूर्णांक)(info & 0xff);
		*q_decfg = status.response_code == AP_RESPONSE_DECONFIGURED;
		चयन (*q_type) अणु
			/* For CEX2 and CEX3 the available functions
			 * are not reflected by the facilities bits.
			 * Instead it is coded पूर्णांकo the type. So here
			 * modअगरy the function bits based on the type.
			 */
		हाल AP_DEVICE_TYPE_CEX2A:
		हाल AP_DEVICE_TYPE_CEX3A:
			*q_fac |= 0x08000000;
			अवरोध;
		हाल AP_DEVICE_TYPE_CEX2C:
		हाल AP_DEVICE_TYPE_CEX3C:
			*q_fac |= 0x10000000;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		वापस true;
	शेष:
		/*
		 * A response code which indicates, there is no info available.
		 */
		वापस false;
	पूर्ण
पूर्ण

व्योम ap_रुको(क्रमागत ap_sm_रुको रुको)
अणु
	kसमय_प्रकार hr_समय;

	चयन (रुको) अणु
	हाल AP_SM_WAIT_AGAIN:
	हाल AP_SM_WAIT_INTERRUPT:
		अगर (ap_using_पूर्णांकerrupts())
			अवरोध;
		अगर (ap_poll_kthपढ़ो) अणु
			wake_up(&ap_poll_रुको);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल AP_SM_WAIT_TIMEOUT:
		spin_lock_bh(&ap_poll_समयr_lock);
		अगर (!hrसमयr_is_queued(&ap_poll_समयr)) अणु
			hr_समय = poll_समयout;
			hrसमयr_क्रमward_now(&ap_poll_समयr, hr_समय);
			hrसमयr_restart(&ap_poll_समयr);
		पूर्ण
		spin_unlock_bh(&ap_poll_समयr_lock);
		अवरोध;
	हाल AP_SM_WAIT_NONE:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ap_request_समयout(): Handling of request समयouts
 * @t: समयr making this callback
 *
 * Handles request समयouts.
 */
व्योम ap_request_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ap_queue *aq = from_समयr(aq, t, समयout);

	spin_lock_bh(&aq->lock);
	ap_रुको(ap_sm_event(aq, AP_SM_EVENT_TIMEOUT));
	spin_unlock_bh(&aq->lock);
पूर्ण

/**
 * ap_poll_समयout(): AP receive polling क्रम finished AP requests.
 * @unused: Unused poपूर्णांकer.
 *
 * Schedules the AP tasklet using a high resolution समयr.
 */
अटल क्रमागत hrसमयr_restart ap_poll_समयout(काष्ठा hrसमयr *unused)
अणु
	tasklet_schedule(&ap_tasklet);
	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * ap_पूर्णांकerrupt_handler() - Schedule ap_tasklet on पूर्णांकerrupt
 * @airq: poपूर्णांकer to adapter पूर्णांकerrupt descriptor
 */
अटल व्योम ap_पूर्णांकerrupt_handler(काष्ठा airq_काष्ठा *airq, bool भग्नing)
अणु
	inc_irq_stat(IRQIO_APB);
	tasklet_schedule(&ap_tasklet);
पूर्ण

/**
 * ap_tasklet_fn(): Tasklet to poll all AP devices.
 * @dummy: Unused variable
 *
 * Poll all AP devices on the bus.
 */
अटल व्योम ap_tasklet_fn(अचिन्हित दीर्घ dummy)
अणु
	पूर्णांक bkt;
	काष्ठा ap_queue *aq;
	क्रमागत ap_sm_रुको रुको = AP_SM_WAIT_NONE;

	/* Reset the indicator अगर पूर्णांकerrupts are used. Thus new पूर्णांकerrupts can
	 * be received. Doing it in the beginning of the tasklet is thereक्रम
	 * important that no requests on any AP get lost.
	 */
	अगर (ap_using_पूर्णांकerrupts())
		xchg(ap_airq.lsi_ptr, 0);

	spin_lock_bh(&ap_queues_lock);
	hash_क्रम_each(ap_queues, bkt, aq, hnode) अणु
		spin_lock_bh(&aq->lock);
		रुको = min(रुको, ap_sm_event_loop(aq, AP_SM_EVENT_POLL));
		spin_unlock_bh(&aq->lock);
	पूर्ण
	spin_unlock_bh(&ap_queues_lock);

	ap_रुको(रुको);
पूर्ण

अटल पूर्णांक ap_pending_requests(व्योम)
अणु
	पूर्णांक bkt;
	काष्ठा ap_queue *aq;

	spin_lock_bh(&ap_queues_lock);
	hash_क्रम_each(ap_queues, bkt, aq, hnode) अणु
		अगर (aq->queue_count == 0)
			जारी;
		spin_unlock_bh(&ap_queues_lock);
		वापस 1;
	पूर्ण
	spin_unlock_bh(&ap_queues_lock);
	वापस 0;
पूर्ण

/**
 * ap_poll_thपढ़ो(): Thपढ़ो that polls क्रम finished requests.
 * @data: Unused poपूर्णांकer
 *
 * AP bus poll thपढ़ो. The purpose of this thपढ़ो is to poll क्रम
 * finished requests in a loop अगर there is a "free" cpu - that is
 * a cpu that करोesn't have anything better to करो. The polling stops
 * as soon as there is another task or अगर all messages have been
 * delivered.
 */
अटल पूर्णांक ap_poll_thपढ़ो(व्योम *data)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	set_user_nice(current, MAX_NICE);
	set_मुक्तzable();
	जबतक (!kthपढ़ो_should_stop()) अणु
		add_रुको_queue(&ap_poll_रुको, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!ap_pending_requests()) अणु
			schedule();
			try_to_मुक्तze();
		पूर्ण
		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&ap_poll_रुको, &रुको);
		अगर (need_resched()) अणु
			schedule();
			try_to_मुक्तze();
			जारी;
		पूर्ण
		ap_tasklet_fn(0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ap_poll_thपढ़ो_start(व्योम)
अणु
	पूर्णांक rc;

	अगर (ap_using_पूर्णांकerrupts() || ap_poll_kthपढ़ो)
		वापस 0;
	mutex_lock(&ap_poll_thपढ़ो_mutex);
	ap_poll_kthपढ़ो = kthपढ़ो_run(ap_poll_thपढ़ो, शून्य, "appoll");
	rc = PTR_ERR_OR_ZERO(ap_poll_kthपढ़ो);
	अगर (rc)
		ap_poll_kthपढ़ो = शून्य;
	mutex_unlock(&ap_poll_thपढ़ो_mutex);
	वापस rc;
पूर्ण

अटल व्योम ap_poll_thपढ़ो_stop(व्योम)
अणु
	अगर (!ap_poll_kthपढ़ो)
		वापस;
	mutex_lock(&ap_poll_thपढ़ो_mutex);
	kthपढ़ो_stop(ap_poll_kthपढ़ो);
	ap_poll_kthपढ़ो = शून्य;
	mutex_unlock(&ap_poll_thपढ़ो_mutex);
पूर्ण

#घोषणा is_card_dev(x) ((x)->parent == ap_root_device)
#घोषणा is_queue_dev(x) ((x)->parent != ap_root_device)

/**
 * ap_bus_match()
 * @dev: Poपूर्णांकer to device
 * @drv: Poपूर्णांकer to device_driver
 *
 * AP bus driver registration/unregistration.
 */
अटल पूर्णांक ap_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा ap_driver *ap_drv = to_ap_drv(drv);
	काष्ठा ap_device_id *id;

	/*
	 * Compare device type of the device with the list of
	 * supported types of the device_driver.
	 */
	क्रम (id = ap_drv->ids; id->match_flags; id++) अणु
		अगर (is_card_dev(dev) &&
		    id->match_flags & AP_DEVICE_ID_MATCH_CARD_TYPE &&
		    id->dev_type == to_ap_dev(dev)->device_type)
			वापस 1;
		अगर (is_queue_dev(dev) &&
		    id->match_flags & AP_DEVICE_ID_MATCH_QUEUE_TYPE &&
		    id->dev_type == to_ap_dev(dev)->device_type)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ap_uevent(): Uevent function क्रम AP devices.
 * @dev: Poपूर्णांकer to device
 * @env: Poपूर्णांकer to kobj_uevent_env
 *
 * It sets up a single environment variable DEV_TYPE which contains the
 * hardware device type.
 */
अटल पूर्णांक ap_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक rc;
	काष्ठा ap_device *ap_dev = to_ap_dev(dev);

	/* Uevents from ap bus core करोn't need extensions to the env */
	अगर (dev == ap_root_device)
		वापस 0;

	/* Set up DEV_TYPE environment variable. */
	rc = add_uevent_var(env, "DEV_TYPE=%04X", ap_dev->device_type);
	अगर (rc)
		वापस rc;

	/* Add MODALIAS= */
	rc = add_uevent_var(env, "MODALIAS=ap:t%02X", ap_dev->device_type);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम ap_send_init_scan_करोne_uevent(व्योम)
अणु
	अक्षर *envp[] = अणु "INITSCAN=done", शून्य पूर्ण;

	kobject_uevent_env(&ap_root_device->kobj, KOBJ_CHANGE, envp);
पूर्ण

अटल व्योम ap_send_bindings_complete_uevent(व्योम)
अणु
	अक्षर *envp[] = अणु "BINDINGS=complete", शून्य पूर्ण;

	kobject_uevent_env(&ap_root_device->kobj, KOBJ_CHANGE, envp);
पूर्ण

/*
 * calc # of bound APQNs
 */

काष्ठा __ap_calc_ctrs अणु
	अचिन्हित पूर्णांक apqns;
	अचिन्हित पूर्णांक bound;
पूर्ण;

अटल पूर्णांक __ap_calc_helper(काष्ठा device *dev, व्योम *arg)
अणु
	काष्ठा __ap_calc_ctrs *pctrs = (काष्ठा __ap_calc_ctrs *) arg;

	अगर (is_queue_dev(dev)) अणु
		pctrs->apqns++;
		अगर ((to_ap_dev(dev))->drv)
			pctrs->bound++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ap_calc_bound_apqns(अचिन्हित पूर्णांक *apqns, अचिन्हित पूर्णांक *bound)
अणु
	काष्ठा __ap_calc_ctrs ctrs;

	स_रखो(&ctrs, 0, माप(ctrs));
	bus_क्रम_each_dev(&ap_bus_type, शून्य, (व्योम *) &ctrs, __ap_calc_helper);

	*apqns = ctrs.apqns;
	*bound = ctrs.bound;
पूर्ण

/*
 * After initial ap bus scan करो check अगर all existing APQNs are
 * bound to device drivers.
 */
अटल व्योम ap_check_bindings_complete(व्योम)
अणु
	अचिन्हित पूर्णांक apqns, bound;

	अगर (atomic64_पढ़ो(&ap_scan_bus_count) >= 1) अणु
		ap_calc_bound_apqns(&apqns, &bound);
		अगर (bound == apqns) अणु
			अगर (!completion_करोne(&ap_init_apqn_bindings_complete)) अणु
				complete_all(&ap_init_apqn_bindings_complete);
				AP_DBF(DBF_INFO, "%s complete\n", __func__);
			पूर्ण
			ap_send_bindings_complete_uevent();
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Interface to रुको क्रम the AP bus to have करोne one initial ap bus
 * scan and all detected APQNs have been bound to device drivers.
 * If these both conditions are not fulfilled, this function blocks
 * on a condition with रुको_क्रम_completion_पूर्णांकerruptible_समयout().
 * If these both conditions are fulfilled (beक्रमe the समयout hits)
 * the वापस value is 0. If the समयout (in jअगरfies) hits instead
 * -ETIME is वापसed. On failures negative वापस values are
 * वापसed to the caller.
 */
पूर्णांक ap_रुको_init_apqn_bindings_complete(अचिन्हित दीर्घ समयout)
अणु
	दीर्घ l;

	अगर (completion_करोne(&ap_init_apqn_bindings_complete))
		वापस 0;

	अगर (समयout)
		l = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&ap_init_apqn_bindings_complete, समयout);
	अन्यथा
		l = रुको_क्रम_completion_पूर्णांकerruptible(
			&ap_init_apqn_bindings_complete);
	अगर (l < 0)
		वापस l == -ERESTARTSYS ? -EINTR : l;
	अन्यथा अगर (l == 0 && समयout)
		वापस -ETIME;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ap_रुको_init_apqn_bindings_complete);

अटल पूर्णांक __ap_queue_devices_with_id_unरेजिस्टर(काष्ठा device *dev, व्योम *data)
अणु
	अगर (is_queue_dev(dev) &&
	    AP_QID_CARD(to_ap_queue(dev)->qid) == (पूर्णांक)(दीर्घ) data)
		device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __ap_revise_reserved(काष्ठा device *dev, व्योम *dummy)
अणु
	पूर्णांक rc, card, queue, devres, drvres;

	अगर (is_queue_dev(dev)) अणु
		card = AP_QID_CARD(to_ap_queue(dev)->qid);
		queue = AP_QID_QUEUE(to_ap_queue(dev)->qid);
		mutex_lock(&ap_perms_mutex);
		devres = test_bit_inv(card, ap_perms.apm)
			&& test_bit_inv(queue, ap_perms.aqm);
		mutex_unlock(&ap_perms_mutex);
		drvres = to_ap_drv(dev->driver)->flags
			& AP_DRIVER_FLAG_DEFAULT;
		अगर (!!devres != !!drvres) अणु
			AP_DBF_DBG("reprobing queue=%02x.%04x\n",
				   card, queue);
			rc = device_reprobe(dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ap_bus_revise_bindings(व्योम)
अणु
	bus_क्रम_each_dev(&ap_bus_type, शून्य, शून्य, __ap_revise_reserved);
पूर्ण

पूर्णांक ap_owned_by_def_drv(पूर्णांक card, पूर्णांक queue)
अणु
	पूर्णांक rc = 0;

	अगर (card < 0 || card >= AP_DEVICES || queue < 0 || queue >= AP_DOMAINS)
		वापस -EINVAL;

	mutex_lock(&ap_perms_mutex);

	अगर (test_bit_inv(card, ap_perms.apm)
	    && test_bit_inv(queue, ap_perms.aqm))
		rc = 1;

	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(ap_owned_by_def_drv);

पूर्णांक ap_apqn_in_matrix_owned_by_def_drv(अचिन्हित दीर्घ *apm,
				       अचिन्हित दीर्घ *aqm)
अणु
	पूर्णांक card, queue, rc = 0;

	mutex_lock(&ap_perms_mutex);

	क्रम (card = 0; !rc && card < AP_DEVICES; card++)
		अगर (test_bit_inv(card, apm) &&
		    test_bit_inv(card, ap_perms.apm))
			क्रम (queue = 0; !rc && queue < AP_DOMAINS; queue++)
				अगर (test_bit_inv(queue, aqm) &&
				    test_bit_inv(queue, ap_perms.aqm))
					rc = 1;

	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(ap_apqn_in_matrix_owned_by_def_drv);

अटल पूर्णांक ap_device_probe(काष्ठा device *dev)
अणु
	काष्ठा ap_device *ap_dev = to_ap_dev(dev);
	काष्ठा ap_driver *ap_drv = to_ap_drv(dev->driver);
	पूर्णांक card, queue, devres, drvres, rc = -ENODEV;

	अगर (!get_device(dev))
		वापस rc;

	अगर (is_queue_dev(dev)) अणु
		/*
		 * If the apqn is marked as reserved/used by ap bus and
		 * शेष drivers, only probe with drivers with the शेष
		 * flag set. If it is not marked, only probe with drivers
		 * with the शेष flag not set.
		 */
		card = AP_QID_CARD(to_ap_queue(dev)->qid);
		queue = AP_QID_QUEUE(to_ap_queue(dev)->qid);
		mutex_lock(&ap_perms_mutex);
		devres = test_bit_inv(card, ap_perms.apm)
			&& test_bit_inv(queue, ap_perms.aqm);
		mutex_unlock(&ap_perms_mutex);
		drvres = ap_drv->flags & AP_DRIVER_FLAG_DEFAULT;
		अगर (!!devres != !!drvres)
			जाओ out;
	पूर्ण

	/* Add queue/card to list of active queues/cards */
	spin_lock_bh(&ap_queues_lock);
	अगर (is_queue_dev(dev))
		hash_add(ap_queues, &to_ap_queue(dev)->hnode,
			 to_ap_queue(dev)->qid);
	spin_unlock_bh(&ap_queues_lock);

	ap_dev->drv = ap_drv;
	rc = ap_drv->probe ? ap_drv->probe(ap_dev) : -ENODEV;

	अगर (rc) अणु
		spin_lock_bh(&ap_queues_lock);
		अगर (is_queue_dev(dev))
			hash_del(&to_ap_queue(dev)->hnode);
		spin_unlock_bh(&ap_queues_lock);
		ap_dev->drv = शून्य;
	पूर्ण अन्यथा
		ap_check_bindings_complete();

out:
	अगर (rc)
		put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक ap_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ap_device *ap_dev = to_ap_dev(dev);
	काष्ठा ap_driver *ap_drv = ap_dev->drv;

	/* prepare ap queue device removal */
	अगर (is_queue_dev(dev))
		ap_queue_prepare_हटाओ(to_ap_queue(dev));

	/* driver's chance to clean up gracefully */
	अगर (ap_drv->हटाओ)
		ap_drv->हटाओ(ap_dev);

	/* now करो the ap queue device हटाओ */
	अगर (is_queue_dev(dev))
		ap_queue_हटाओ(to_ap_queue(dev));

	/* Remove queue/card from list of active queues/cards */
	spin_lock_bh(&ap_queues_lock);
	अगर (is_queue_dev(dev))
		hash_del(&to_ap_queue(dev)->hnode);
	spin_unlock_bh(&ap_queues_lock);
	ap_dev->drv = शून्य;

	put_device(dev);

	वापस 0;
पूर्ण

काष्ठा ap_queue *ap_get_qdev(ap_qid_t qid)
अणु
	पूर्णांक bkt;
	काष्ठा ap_queue *aq;

	spin_lock_bh(&ap_queues_lock);
	hash_क्रम_each(ap_queues, bkt, aq, hnode) अणु
		अगर (aq->qid == qid) अणु
			get_device(&aq->ap_dev.device);
			spin_unlock_bh(&ap_queues_lock);
			वापस aq;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ap_queues_lock);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ap_get_qdev);

पूर्णांक ap_driver_रेजिस्टर(काष्ठा ap_driver *ap_drv, काष्ठा module *owner,
		       अक्षर *name)
अणु
	काष्ठा device_driver *drv = &ap_drv->driver;

	drv->bus = &ap_bus_type;
	drv->probe = ap_device_probe;
	drv->हटाओ = ap_device_हटाओ;
	drv->owner = owner;
	drv->name = name;
	वापस driver_रेजिस्टर(drv);
पूर्ण
EXPORT_SYMBOL(ap_driver_रेजिस्टर);

व्योम ap_driver_unरेजिस्टर(काष्ठा ap_driver *ap_drv)
अणु
	driver_unरेजिस्टर(&ap_drv->driver);
पूर्ण
EXPORT_SYMBOL(ap_driver_unरेजिस्टर);

व्योम ap_bus_क्रमce_rescan(व्योम)
अणु
	/* processing a asynchronous bus rescan */
	del_समयr(&ap_config_समयr);
	queue_work(प्रणाली_दीर्घ_wq, &ap_scan_work);
	flush_work(&ap_scan_work);
पूर्ण
EXPORT_SYMBOL(ap_bus_क्रमce_rescan);

/*
* A config change has happened, क्रमce an ap bus rescan.
*/
व्योम ap_bus_cfg_chg(व्योम)
अणु
	AP_DBF_DBG("%s config change, forcing bus rescan\n", __func__);

	ap_bus_क्रमce_rescan();
पूर्ण

/*
 * hex2biपंचांगap() - parse hex mask string and set biपंचांगap.
 * Valid strings are "0x012345678" with at least one valid hex number.
 * Rest of the biपंचांगap to the right is padded with 0. No spaces allowed
 * within the string, the leading 0x may be omitted.
 * Returns the biपंचांगask with exactly the bits set as given by the hex
 * string (both in big endian order).
 */
अटल पूर्णांक hex2biपंचांगap(स्थिर अक्षर *str, अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bits)
अणु
	पूर्णांक i, n, b;

	/* bits needs to be a multiple of 8 */
	अगर (bits & 0x07)
		वापस -EINVAL;

	अगर (str[0] == '0' && str[1] == 'x')
		str++;
	अगर (*str == 'x')
		str++;

	क्रम (i = 0; है_षष्ठादशक(*str) && i < bits; str++) अणु
		b = hex_to_bin(*str);
		क्रम (n = 0; n < 4; n++)
			अगर (b & (0x08 >> n))
				set_bit_inv(i + n, biपंचांगap);
		i += 4;
	पूर्ण

	अगर (*str == '\n')
		str++;
	अगर (*str)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * modअगरy_biपंचांगap() - parse biपंचांगask argument and modअगरy an existing
 * bit mask accordingly. A concatenation (करोne with ',') of these
 * terms is recognized:
 *   +<bitnr>[-<bitnr>] or -<bitnr>[-<bitnr>]
 * <bitnr> may be any valid number (hex, decimal or octal) in the range
 * 0...bits-1; the leading + or - is required. Here are some examples:
 *   +0-15,+32,-128,-0xFF
 *   -0-255,+1-16,+0x128
 *   +1,+2,+3,+4,-5,-7-10
 * Returns the new biपंचांगap after all changes have been applied. Every
 * positive value in the string will set a bit and every negative value
 * in the string will clear a bit. As a bit may be touched more than once,
 * the last 'operation' wins:
 * +0-255,-128 = first bits 0-255 will be set, then bit 128 will be
 * cleared again. All other bits are unmodअगरied.
 */
अटल पूर्णांक modअगरy_biपंचांगap(स्थिर अक्षर *str, अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bits)
अणु
	पूर्णांक a, i, z;
	अक्षर *np, sign;

	/* bits needs to be a multiple of 8 */
	अगर (bits & 0x07)
		वापस -EINVAL;

	जबतक (*str) अणु
		sign = *str++;
		अगर (sign != '+' && sign != '-')
			वापस -EINVAL;
		a = z = simple_म_से_अदीर्घ(str, &np, 0);
		अगर (str == np || a >= bits)
			वापस -EINVAL;
		str = np;
		अगर (*str == '-') अणु
			z = simple_म_से_अदीर्घ(++str, &np, 0);
			अगर (str == np || a > z || z >= bits)
				वापस -EINVAL;
			str = np;
		पूर्ण
		क्रम (i = a; i <= z; i++)
			अगर (sign == '+')
				set_bit_inv(i, biपंचांगap);
			अन्यथा
				clear_bit_inv(i, biपंचांगap);
		जबतक (*str == ',' || *str == '\n')
			str++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ap_parse_mask_str(स्थिर अक्षर *str,
		      अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bits,
		      काष्ठा mutex *lock)
अणु
	अचिन्हित दीर्घ *newmap, size;
	पूर्णांक rc;

	/* bits needs to be a multiple of 8 */
	अगर (bits & 0x07)
		वापस -EINVAL;

	size = BITS_TO_LONGS(bits)*माप(अचिन्हित दीर्घ);
	newmap = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!newmap)
		वापस -ENOMEM;
	अगर (mutex_lock_पूर्णांकerruptible(lock)) अणु
		kमुक्त(newmap);
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (*str == '+' || *str == '-') अणु
		स_नकल(newmap, biपंचांगap, size);
		rc = modअगरy_biपंचांगap(str, newmap, bits);
	पूर्ण अन्यथा अणु
		स_रखो(newmap, 0, size);
		rc = hex2biपंचांगap(str, newmap, bits);
	पूर्ण
	अगर (rc == 0)
		स_नकल(biपंचांगap, newmap, size);
	mutex_unlock(lock);
	kमुक्त(newmap);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ap_parse_mask_str);

/*
 * AP bus attributes.
 */

अटल sमाप_प्रकार ap_करोमुख्य_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ap_करोमुख्य_index);
पूर्ण

अटल sमाप_प्रकार ap_करोमुख्य_store(काष्ठा bus_type *bus,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक करोमुख्य;

	अगर (माला_पूछो(buf, "%i\n", &करोमुख्य) != 1 ||
	    करोमुख्य < 0 || करोमुख्य > ap_max_करोमुख्य_id ||
	    !test_bit_inv(करोमुख्य, ap_perms.aqm))
		वापस -EINVAL;

	spin_lock_bh(&ap_करोमुख्य_lock);
	ap_करोमुख्य_index = करोमुख्य;
	spin_unlock_bh(&ap_करोमुख्य_lock);

	AP_DBF_INFO("stored new default domain=%d\n", करोमुख्य);

	वापस count;
पूर्ण

अटल BUS_ATTR_RW(ap_करोमुख्य);

अटल sमाप_प्रकार ap_control_करोमुख्य_mask_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	अगर (!ap_qci_info)	/* QCI not supported */
		वापस scnम_लिखो(buf, PAGE_SIZE, "not supported\n");

	वापस scnम_लिखो(buf, PAGE_SIZE,
			 "0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			 ap_qci_info->adm[0], ap_qci_info->adm[1],
			 ap_qci_info->adm[2], ap_qci_info->adm[3],
			 ap_qci_info->adm[4], ap_qci_info->adm[5],
			 ap_qci_info->adm[6], ap_qci_info->adm[7]);
पूर्ण

अटल BUS_ATTR_RO(ap_control_करोमुख्य_mask);

अटल sमाप_प्रकार ap_usage_करोमुख्य_mask_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	अगर (!ap_qci_info)	/* QCI not supported */
		वापस scnम_लिखो(buf, PAGE_SIZE, "not supported\n");

	वापस scnम_लिखो(buf, PAGE_SIZE,
			 "0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			 ap_qci_info->aqm[0], ap_qci_info->aqm[1],
			 ap_qci_info->aqm[2], ap_qci_info->aqm[3],
			 ap_qci_info->aqm[4], ap_qci_info->aqm[5],
			 ap_qci_info->aqm[6], ap_qci_info->aqm[7]);
पूर्ण

अटल BUS_ATTR_RO(ap_usage_करोमुख्य_mask);

अटल sमाप_प्रकार ap_adapter_mask_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	अगर (!ap_qci_info)	/* QCI not supported */
		वापस scnम_लिखो(buf, PAGE_SIZE, "not supported\n");

	वापस scnम_लिखो(buf, PAGE_SIZE,
			 "0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			 ap_qci_info->apm[0], ap_qci_info->apm[1],
			 ap_qci_info->apm[2], ap_qci_info->apm[3],
			 ap_qci_info->apm[4], ap_qci_info->apm[5],
			 ap_qci_info->apm[6], ap_qci_info->apm[7]);
पूर्ण

अटल BUS_ATTR_RO(ap_adapter_mask);

अटल sमाप_प्रकार ap_पूर्णांकerrupts_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 ap_using_पूर्णांकerrupts() ? 1 : 0);
पूर्ण

अटल BUS_ATTR_RO(ap_पूर्णांकerrupts);

अटल sमाप_प्रकार config_समय_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ap_config_समय);
पूर्ण

अटल sमाप_प्रकार config_समय_store(काष्ठा bus_type *bus,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक समय;

	अगर (माला_पूछो(buf, "%d\n", &समय) != 1 || समय < 5 || समय > 120)
		वापस -EINVAL;
	ap_config_समय = समय;
	mod_समयr(&ap_config_समयr, jअगरfies + ap_config_समय * HZ);
	वापस count;
पूर्ण

अटल BUS_ATTR_RW(config_समय);

अटल sमाप_प्रकार poll_thपढ़ो_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ap_poll_kthपढ़ो ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार poll_thपढ़ो_store(काष्ठा bus_type *bus,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक flag, rc;

	अगर (माला_पूछो(buf, "%d\n", &flag) != 1)
		वापस -EINVAL;
	अगर (flag) अणु
		rc = ap_poll_thपढ़ो_start();
		अगर (rc)
			count = rc;
	पूर्ण अन्यथा
		ap_poll_thपढ़ो_stop();
	वापस count;
पूर्ण

अटल BUS_ATTR_RW(poll_thपढ़ो);

अटल sमाप_प्रकार poll_समयout_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", poll_समयout);
पूर्ण

अटल sमाप_प्रकार poll_समयout_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	अचिन्हित दीर्घ दीर्घ समय;
	kसमय_प्रकार hr_समय;

	/* 120 seconds = maximum poll पूर्णांकerval */
	अगर (माला_पूछो(buf, "%llu\n", &समय) != 1 || समय < 1 ||
	    समय > 120000000000ULL)
		वापस -EINVAL;
	poll_समयout = समय;
	hr_समय = poll_समयout;

	spin_lock_bh(&ap_poll_समयr_lock);
	hrसमयr_cancel(&ap_poll_समयr);
	hrसमयr_set_expires(&ap_poll_समयr, hr_समय);
	hrसमयr_start_expires(&ap_poll_समयr, HRTIMER_MODE_ABS);
	spin_unlock_bh(&ap_poll_समयr_lock);

	वापस count;
पूर्ण

अटल BUS_ATTR_RW(poll_समयout);

अटल sमाप_प्रकार ap_max_करोमुख्य_id_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ap_max_करोमुख्य_id);
पूर्ण

अटल BUS_ATTR_RO(ap_max_करोमुख्य_id);

अटल sमाप_प्रकार ap_max_adapter_id_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ap_max_adapter_id);
पूर्ण

अटल BUS_ATTR_RO(ap_max_adapter_id);

अटल sमाप_प्रकार apmask_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	पूर्णांक rc;

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;
	rc = scnम_लिखो(buf, PAGE_SIZE,
		       "0x%016lx%016lx%016lx%016lx\n",
		       ap_perms.apm[0], ap_perms.apm[1],
		       ap_perms.apm[2], ap_perms.apm[3]);
	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार apmask_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = ap_parse_mask_str(buf, ap_perms.apm, AP_DEVICES, &ap_perms_mutex);
	अगर (rc)
		वापस rc;

	ap_bus_revise_bindings();

	वापस count;
पूर्ण

अटल BUS_ATTR_RW(apmask);

अटल sमाप_प्रकार aqmask_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	पूर्णांक rc;

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;
	rc = scnम_लिखो(buf, PAGE_SIZE,
		       "0x%016lx%016lx%016lx%016lx\n",
		       ap_perms.aqm[0], ap_perms.aqm[1],
		       ap_perms.aqm[2], ap_perms.aqm[3]);
	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार aqmask_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = ap_parse_mask_str(buf, ap_perms.aqm, AP_DOMAINS, &ap_perms_mutex);
	अगर (rc)
		वापस rc;

	ap_bus_revise_bindings();

	वापस count;
पूर्ण

अटल BUS_ATTR_RW(aqmask);

अटल sमाप_प्रकार scans_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n",
			 atomic64_पढ़ो(&ap_scan_bus_count));
पूर्ण

अटल BUS_ATTR_RO(scans);

अटल sमाप_प्रकार bindings_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक apqns, n;

	ap_calc_bound_apqns(&apqns, &n);
	अगर (atomic64_पढ़ो(&ap_scan_bus_count) >= 1 && n == apqns)
		rc = scnम_लिखो(buf, PAGE_SIZE, "%u/%u (complete)\n", n, apqns);
	अन्यथा
		rc = scnम_लिखो(buf, PAGE_SIZE, "%u/%u\n", n, apqns);

	वापस rc;
पूर्ण

अटल BUS_ATTR_RO(bindings);

अटल काष्ठा attribute *ap_bus_attrs[] = अणु
	&bus_attr_ap_करोमुख्य.attr,
	&bus_attr_ap_control_करोमुख्य_mask.attr,
	&bus_attr_ap_usage_करोमुख्य_mask.attr,
	&bus_attr_ap_adapter_mask.attr,
	&bus_attr_config_समय.attr,
	&bus_attr_poll_thपढ़ो.attr,
	&bus_attr_ap_पूर्णांकerrupts.attr,
	&bus_attr_poll_समयout.attr,
	&bus_attr_ap_max_करोमुख्य_id.attr,
	&bus_attr_ap_max_adapter_id.attr,
	&bus_attr_apmask.attr,
	&bus_attr_aqmask.attr,
	&bus_attr_scans.attr,
	&bus_attr_bindings.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ap_bus);

अटल काष्ठा bus_type ap_bus_type = अणु
	.name = "ap",
	.bus_groups = ap_bus_groups,
	.match = &ap_bus_match,
	.uevent = &ap_uevent,
पूर्ण;

/**
 * ap_select_करोमुख्य(): Select an AP करोमुख्य अगर possible and we haven't
 * alपढ़ोy करोne so beक्रमe.
 */
अटल व्योम ap_select_करोमुख्य(व्योम)
अणु
	काष्ठा ap_queue_status status;
	पूर्णांक card, करोm;

	/*
	 * Choose the शेष करोमुख्य. Either the one specअगरied with
	 * the "domain=" parameter or the first करोमुख्य with at least
	 * one valid APQN.
	 */
	spin_lock_bh(&ap_करोमुख्य_lock);
	अगर (ap_करोमुख्य_index >= 0) अणु
		/* Doमुख्य has alपढ़ोy been selected. */
		जाओ out;
	पूर्ण
	क्रम (करोm = 0; करोm <= ap_max_करोमुख्य_id; करोm++) अणु
		अगर (!ap_test_config_usage_करोमुख्य(करोm) ||
		    !test_bit_inv(करोm, ap_perms.aqm))
			जारी;
		क्रम (card = 0; card <= ap_max_adapter_id; card++) अणु
			अगर (!ap_test_config_card_id(card) ||
			    !test_bit_inv(card, ap_perms.apm))
				जारी;
			status = ap_test_queue(AP_MKQID(card, करोm),
					       ap_apft_available(),
					       शून्य);
			अगर (status.response_code == AP_RESPONSE_NORMAL)
				अवरोध;
		पूर्ण
		अगर (card <= ap_max_adapter_id)
			अवरोध;
	पूर्ण
	अगर (करोm <= ap_max_करोमुख्य_id) अणु
		ap_करोमुख्य_index = करोm;
		AP_DBF_INFO("%s new default domain is %d\n",
			    __func__, ap_करोमुख्य_index);
	पूर्ण
out:
	spin_unlock_bh(&ap_करोमुख्य_lock);
पूर्ण

/*
 * This function checks the type and वापसs either 0 क्रम not
 * supported or the highest compatible type value (which may
 * include the input type value).
 */
अटल पूर्णांक ap_get_compatible_type(ap_qid_t qid, पूर्णांक rawtype, अचिन्हित पूर्णांक func)
अणु
	पूर्णांक comp_type = 0;

	/* < CEX2A is not supported */
	अगर (rawtype < AP_DEVICE_TYPE_CEX2A) अणु
		AP_DBF_WARN("get_comp_type queue=%02x.%04x unsupported type %d\n",
			    AP_QID_CARD(qid), AP_QID_QUEUE(qid), rawtype);
		वापस 0;
	पूर्ण
	/* up to CEX7 known and fully supported */
	अगर (rawtype <= AP_DEVICE_TYPE_CEX7)
		वापस rawtype;
	/*
	 * unknown new type > CEX7, check क्रम compatibility
	 * to the highest known and supported type which is
	 * currently CEX7 with the help of the QACT function.
	 */
	अगर (ap_qact_available()) अणु
		काष्ठा ap_queue_status status;
		जोड़ ap_qact_ap_info apinfo = अणु0पूर्ण;

		apinfo.mode = (func >> 26) & 0x07;
		apinfo.cat = AP_DEVICE_TYPE_CEX7;
		status = ap_qact(qid, 0, &apinfo);
		अगर (status.response_code == AP_RESPONSE_NORMAL
		    && apinfo.cat >= AP_DEVICE_TYPE_CEX2A
		    && apinfo.cat <= AP_DEVICE_TYPE_CEX7)
			comp_type = apinfo.cat;
	पूर्ण
	अगर (!comp_type)
		AP_DBF_WARN("get_comp_type queue=%02x.%04x unable to map type %d\n",
			    AP_QID_CARD(qid), AP_QID_QUEUE(qid), rawtype);
	अन्यथा अगर (comp_type != rawtype)
		AP_DBF_INFO("get_comp_type queue=%02x.%04x map type %d to %d\n",
			    AP_QID_CARD(qid), AP_QID_QUEUE(qid),
			    rawtype, comp_type);
	वापस comp_type;
पूर्ण

/*
 * Helper function to be used with bus_find_dev
 * matches क्रम the card device with the given id
 */
अटल पूर्णांक __match_card_device_with_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस is_card_dev(dev) && to_ap_card(dev)->id == (पूर्णांक)(दीर्घ)(व्योम *) data;
पूर्ण

/*
 * Helper function to be used with bus_find_dev
 * matches क्रम the queue device with a given qid
 */
अटल पूर्णांक __match_queue_device_with_qid(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस is_queue_dev(dev) && to_ap_queue(dev)->qid == (पूर्णांक)(दीर्घ) data;
पूर्ण

/*
 * Helper function to be used with bus_find_dev
 * matches any queue device with given queue id
 */
अटल पूर्णांक __match_queue_device_with_queue_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस is_queue_dev(dev)
		&& AP_QID_QUEUE(to_ap_queue(dev)->qid) == (पूर्णांक)(दीर्घ) data;
पूर्ण

/*
 * Helper function क्रम ap_scan_bus().
 * Remove card device and associated queue devices.
 */
अटल अंतरभूत व्योम ap_scan_rm_card_dev_and_queue_devs(काष्ठा ap_card *ac)
अणु
	bus_क्रम_each_dev(&ap_bus_type, शून्य,
			 (व्योम *)(दीर्घ) ac->id,
			 __ap_queue_devices_with_id_unरेजिस्टर);
	device_unरेजिस्टर(&ac->ap_dev.device);
पूर्ण

/*
 * Helper function क्रम ap_scan_bus().
 * Does the scan bus job क्रम all the करोमुख्यs within
 * a valid adapter given by an ap_card ptr.
 */
अटल अंतरभूत व्योम ap_scan_करोमुख्यs(काष्ठा ap_card *ac)
अणु
	bool decfg;
	ap_qid_t qid;
	अचिन्हित पूर्णांक func;
	काष्ठा device *dev;
	काष्ठा ap_queue *aq;
	पूर्णांक rc, करोm, depth, type;

	/*
	 * Go through the configuration क्रम the करोमुख्यs and compare them
	 * to the existing queue devices. Also take care of the config
	 * and error state क्रम the queue devices.
	 */

	क्रम (करोm = 0; करोm <= ap_max_करोमुख्य_id; करोm++) अणु
		qid = AP_MKQID(ac->id, करोm);
		dev = bus_find_device(&ap_bus_type, शून्य,
				      (व्योम *)(दीर्घ) qid,
				      __match_queue_device_with_qid);
		aq = dev ? to_ap_queue(dev) : शून्य;
		अगर (!ap_test_config_usage_करोमुख्य(करोm)) अणु
			अगर (dev) अणु
				AP_DBF_INFO("%s(%d,%d) not in config any more, rm queue device\n",
					    __func__, ac->id, करोm);
				device_unरेजिस्टर(dev);
				put_device(dev);
			पूर्ण
			जारी;
		पूर्ण
		/* करोमुख्य is valid, get info from this APQN */
		अगर (!ap_queue_info(qid, &type, &func, &depth, &decfg)) अणु
			अगर (aq) अणु
				AP_DBF_INFO(
					"%s(%d,%d) ap_queue_info() not successful, rm queue device\n",
					__func__, ac->id, करोm);
				device_unरेजिस्टर(dev);
				put_device(dev);
			पूर्ण
			जारी;
		पूर्ण
		/* अगर no queue device exists, create a new one */
		अगर (!aq) अणु
			aq = ap_queue_create(qid, ac->ap_dev.device_type);
			अगर (!aq) अणु
				AP_DBF_WARN("%s(%d,%d) ap_queue_create() failed\n",
					    __func__, ac->id, करोm);
				जारी;
			पूर्ण
			aq->card = ac;
			aq->config = !decfg;
			dev = &aq->ap_dev.device;
			dev->bus = &ap_bus_type;
			dev->parent = &ac->ap_dev.device;
			dev_set_name(dev, "%02x.%04x", ac->id, करोm);
			/* रेजिस्टर queue device */
			rc = device_रेजिस्टर(dev);
			अगर (rc) अणु
				AP_DBF_WARN("%s(%d,%d) device_register() failed\n",
					    __func__, ac->id, करोm);
				जाओ put_dev_and_जारी;
			पूर्ण
			/* get it and thus adjust reference counter */
			get_device(dev);
			अगर (decfg)
				AP_DBF_INFO("%s(%d,%d) new (decfg) queue device created\n",
					    __func__, ac->id, करोm);
			अन्यथा
				AP_DBF_INFO("%s(%d,%d) new queue device created\n",
					    __func__, ac->id, करोm);
			जाओ put_dev_and_जारी;
		पूर्ण
		/* Check config state on the alपढ़ोy existing queue device */
		spin_lock_bh(&aq->lock);
		अगर (decfg && aq->config) अणु
			/* config off this queue device */
			aq->config = false;
			अगर (aq->dev_state > AP_DEV_STATE_UNINITIATED) अणु
				aq->dev_state = AP_DEV_STATE_ERROR;
				aq->last_err_rc = AP_RESPONSE_DECONFIGURED;
			पूर्ण
			spin_unlock_bh(&aq->lock);
			AP_DBF_INFO("%s(%d,%d) queue device config off\n",
				    __func__, ac->id, करोm);
			/* 'receive' pending messages with -EAGAIN */
			ap_flush_queue(aq);
			जाओ put_dev_and_जारी;
		पूर्ण
		अगर (!decfg && !aq->config) अणु
			/* config on this queue device */
			aq->config = true;
			अगर (aq->dev_state > AP_DEV_STATE_UNINITIATED) अणु
				aq->dev_state = AP_DEV_STATE_OPERATING;
				aq->sm_state = AP_SM_STATE_RESET_START;
			पूर्ण
			spin_unlock_bh(&aq->lock);
			AP_DBF_INFO("%s(%d,%d) queue device config on\n",
				    __func__, ac->id, करोm);
			जाओ put_dev_and_जारी;
		पूर्ण
		/* handle other error states */
		अगर (!decfg && aq->dev_state == AP_DEV_STATE_ERROR) अणु
			spin_unlock_bh(&aq->lock);
			/* 'receive' pending messages with -EAGAIN */
			ap_flush_queue(aq);
			/* re-init (with reset) the queue device */
			ap_queue_init_state(aq);
			AP_DBF_INFO("%s(%d,%d) queue device reinit enforced\n",
				    __func__, ac->id, करोm);
			जाओ put_dev_and_जारी;
		पूर्ण
		spin_unlock_bh(&aq->lock);
put_dev_and_जारी:
		put_device(dev);
	पूर्ण
पूर्ण

/*
 * Helper function क्रम ap_scan_bus().
 * Does the scan bus job क्रम the given adapter id.
 */
अटल अंतरभूत व्योम ap_scan_adapter(पूर्णांक ap)
अणु
	bool decfg;
	ap_qid_t qid;
	अचिन्हित पूर्णांक func;
	काष्ठा device *dev;
	काष्ठा ap_card *ac;
	पूर्णांक rc, करोm, depth, type, comp_type;

	/* Is there currently a card device क्रम this adapter ? */
	dev = bus_find_device(&ap_bus_type, शून्य,
			      (व्योम *)(दीर्घ) ap,
			      __match_card_device_with_id);
	ac = dev ? to_ap_card(dev) : शून्य;

	/* Adapter not in configuration ? */
	अगर (!ap_test_config_card_id(ap)) अणु
		अगर (ac) अणु
			AP_DBF_INFO("%s(%d) ap not in config any more, rm card and queue devices\n",
				    __func__, ap);
			ap_scan_rm_card_dev_and_queue_devs(ac);
			put_device(dev);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Adapter ap is valid in the current configuration. So करो some checks:
	 * If no card device exists, build one. If a card device exists, check
	 * क्रम type and functions changed. For all this we need to find a valid
	 * APQN first.
	 */

	क्रम (करोm = 0; करोm <= ap_max_करोमुख्य_id; करोm++)
		अगर (ap_test_config_usage_करोमुख्य(करोm)) अणु
			qid = AP_MKQID(ap, करोm);
			अगर (ap_queue_info(qid, &type, &func, &depth, &decfg))
				अवरोध;
		पूर्ण
	अगर (करोm > ap_max_करोमुख्य_id) अणु
		/* Could not find a valid APQN क्रम this adapter */
		अगर (ac) अणु
			AP_DBF_INFO(
				"%s(%d) no type info (no APQN found), rm card and queue devices\n",
				__func__, ap);
			ap_scan_rm_card_dev_and_queue_devs(ac);
			put_device(dev);
		पूर्ण अन्यथा अणु
			AP_DBF_DBG("%s(%d) no type info (no APQN found), ignored\n",
				   __func__, ap);
		पूर्ण
		वापस;
	पूर्ण
	अगर (!type) अणु
		/* No apdater type info available, an unusable adapter */
		अगर (ac) अणु
			AP_DBF_INFO("%s(%d) no valid type (0) info, rm card and queue devices\n",
				    __func__, ap);
			ap_scan_rm_card_dev_and_queue_devs(ac);
			put_device(dev);
		पूर्ण अन्यथा अणु
			AP_DBF_DBG("%s(%d) no valid type (0) info, ignored\n",
				   __func__, ap);
		पूर्ण
		वापस;
	पूर्ण

	अगर (ac) अणु
		/* Check APQN against existing card device क्रम changes */
		अगर (ac->raw_hwtype != type) अणु
			AP_DBF_INFO("%s(%d) hwtype %d changed, rm card and queue devices\n",
				    __func__, ap, type);
			ap_scan_rm_card_dev_and_queue_devs(ac);
			put_device(dev);
			ac = शून्य;
		पूर्ण अन्यथा अगर (ac->functions != func) अणु
			AP_DBF_INFO("%s(%d) functions 0x%08x changed, rm card and queue devices\n",
				    __func__, ap, type);
			ap_scan_rm_card_dev_and_queue_devs(ac);
			put_device(dev);
			ac = शून्य;
		पूर्ण अन्यथा अणु
			अगर (decfg && ac->config) अणु
				ac->config = false;
				AP_DBF_INFO("%s(%d) card device config off\n",
					    __func__, ap);

			पूर्ण
			अगर (!decfg && !ac->config) अणु
				ac->config = true;
				AP_DBF_INFO("%s(%d) card device config on\n",
					    __func__, ap);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ac) अणु
		/* Build a new card device */
		comp_type = ap_get_compatible_type(qid, type, func);
		अगर (!comp_type) अणु
			AP_DBF_WARN("%s(%d) type %d, can't get compatibility type\n",
				    __func__, ap, type);
			वापस;
		पूर्ण
		ac = ap_card_create(ap, depth, type, comp_type, func);
		अगर (!ac) अणु
			AP_DBF_WARN("%s(%d) ap_card_create() failed\n",
				    __func__, ap);
			वापस;
		पूर्ण
		ac->config = !decfg;
		dev = &ac->ap_dev.device;
		dev->bus = &ap_bus_type;
		dev->parent = ap_root_device;
		dev_set_name(dev, "card%02x", ap);
		/* Register the new card device with AP bus */
		rc = device_रेजिस्टर(dev);
		अगर (rc) अणु
			AP_DBF_WARN("%s(%d) device_register() failed\n",
				    __func__, ap);
			put_device(dev);
			वापस;
		पूर्ण
		/* get it and thus adjust reference counter */
		get_device(dev);
		अगर (decfg)
			AP_DBF_INFO("%s(%d) new (decfg) card device type=%d func=0x%08x created\n",
				    __func__, ap, type, func);
		अन्यथा
			AP_DBF_INFO("%s(%d) new card device type=%d func=0x%08x created\n",
				    __func__, ap, type, func);
	पूर्ण

	/* Verअगरy the करोमुख्यs and the queue devices क्रम this card */
	ap_scan_करोमुख्यs(ac);

	/* release the card device */
	put_device(&ac->ap_dev.device);
पूर्ण

/**
 * ap_scan_bus(): Scan the AP bus क्रम new devices
 * Runs periodically, workqueue समयr (ap_config_समय)
 */
अटल व्योम ap_scan_bus(काष्ठा work_काष्ठा *unused)
अणु
	पूर्णांक ap;

	ap_fetch_qci_info(ap_qci_info);
	ap_select_करोमुख्य();

	AP_DBF_DBG("%s running\n", __func__);

	/* loop over all possible adapters */
	क्रम (ap = 0; ap <= ap_max_adapter_id; ap++)
		ap_scan_adapter(ap);

	/* check अगर there is at least one queue available with शेष करोमुख्य */
	अगर (ap_करोमुख्य_index >= 0) अणु
		काष्ठा device *dev =
			bus_find_device(&ap_bus_type, शून्य,
					(व्योम *)(दीर्घ) ap_करोमुख्य_index,
					__match_queue_device_with_queue_id);
		अगर (dev)
			put_device(dev);
		अन्यथा
			AP_DBF_INFO("no queue device with default domain %d available\n",
				    ap_करोमुख्य_index);
	पूर्ण

	अगर (atomic64_inc_वापस(&ap_scan_bus_count) == 1) अणु
		AP_DBF(DBF_DEBUG, "%s init scan complete\n", __func__);
		ap_send_init_scan_करोne_uevent();
		ap_check_bindings_complete();
	पूर्ण

	mod_समयr(&ap_config_समयr, jअगरfies + ap_config_समय * HZ);
पूर्ण

अटल व्योम ap_config_समयout(काष्ठा समयr_list *unused)
अणु
	queue_work(प्रणाली_दीर्घ_wq, &ap_scan_work);
पूर्ण

अटल पूर्णांक __init ap_debug_init(व्योम)
अणु
	ap_dbf_info = debug_रेजिस्टर("ap", 1, 1,
				     DBF_MAX_SPRINTF_ARGS * माप(दीर्घ));
	debug_रेजिस्टर_view(ap_dbf_info, &debug_प्र_लिखो_view);
	debug_set_level(ap_dbf_info, DBF_ERR);

	वापस 0;
पूर्ण

अटल व्योम __init ap_perms_init(व्योम)
अणु
	/* all resources useable अगर no kernel parameter string given */
	स_रखो(&ap_perms.ioctlm, 0xFF, माप(ap_perms.ioctlm));
	स_रखो(&ap_perms.apm, 0xFF, माप(ap_perms.apm));
	स_रखो(&ap_perms.aqm, 0xFF, माप(ap_perms.aqm));

	/* apm kernel parameter string */
	अगर (apm_str) अणु
		स_रखो(&ap_perms.apm, 0, माप(ap_perms.apm));
		ap_parse_mask_str(apm_str, ap_perms.apm, AP_DEVICES,
				  &ap_perms_mutex);
	पूर्ण

	/* aqm kernel parameter string */
	अगर (aqm_str) अणु
		स_रखो(&ap_perms.aqm, 0, माप(ap_perms.aqm));
		ap_parse_mask_str(aqm_str, ap_perms.aqm, AP_DOMAINS,
				  &ap_perms_mutex);
	पूर्ण
पूर्ण

/**
 * ap_module_init(): The module initialization code.
 *
 * Initializes the module.
 */
अटल पूर्णांक __init ap_module_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ap_debug_init();
	अगर (rc)
		वापस rc;

	अगर (!ap_inकाष्ठाions_available()) अणु
		pr_warn("The hardware system does not support AP instructions\n");
		वापस -ENODEV;
	पूर्ण

	/* init ap_queue hashtable */
	hash_init(ap_queues);

	/* set up the AP permissions (ioctls, ap and aq masks) */
	ap_perms_init();

	/* Get AP configuration data अगर available */
	ap_init_qci_info();

	/* check शेष करोमुख्य setting */
	अगर (ap_करोमुख्य_index < -1 || ap_करोमुख्य_index > ap_max_करोमुख्य_id ||
	    (ap_करोमुख्य_index >= 0 &&
	     !test_bit_inv(ap_करोमुख्य_index, ap_perms.aqm))) अणु
		pr_warn("%d is not a valid cryptographic domain\n",
			ap_करोमुख्य_index);
		ap_करोमुख्य_index = -1;
	पूर्ण

	/* enable पूर्णांकerrupts अगर available */
	अगर (ap_पूर्णांकerrupts_available()) अणु
		rc = रेजिस्टर_adapter_पूर्णांकerrupt(&ap_airq);
		ap_airq_flag = (rc == 0);
	पूर्ण

	/* Create /sys/bus/ap. */
	rc = bus_रेजिस्टर(&ap_bus_type);
	अगर (rc)
		जाओ out;

	/* Create /sys/devices/ap. */
	ap_root_device = root_device_रेजिस्टर("ap");
	rc = PTR_ERR_OR_ZERO(ap_root_device);
	अगर (rc)
		जाओ out_bus;
	ap_root_device->bus = &ap_bus_type;

	/* Setup the AP bus rescan समयr. */
	समयr_setup(&ap_config_समयr, ap_config_समयout, 0);

	/*
	 * Setup the high resultion poll समयr.
	 * If we are running under z/VM adjust polling to z/VM polling rate.
	 */
	अगर (MACHINE_IS_VM)
		poll_समयout = 1500000;
	hrसमयr_init(&ap_poll_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	ap_poll_समयr.function = ap_poll_समयout;

	/* Start the low priority AP bus poll thपढ़ो. */
	अगर (ap_thपढ़ो_flag) अणु
		rc = ap_poll_thपढ़ो_start();
		अगर (rc)
			जाओ out_work;
	पूर्ण

	queue_work(प्रणाली_दीर्घ_wq, &ap_scan_work);

	वापस 0;

out_work:
	hrसमयr_cancel(&ap_poll_समयr);
	root_device_unरेजिस्टर(ap_root_device);
out_bus:
	bus_unरेजिस्टर(&ap_bus_type);
out:
	अगर (ap_using_पूर्णांकerrupts())
		unरेजिस्टर_adapter_पूर्णांकerrupt(&ap_airq);
	kमुक्त(ap_qci_info);
	वापस rc;
पूर्ण
device_initcall(ap_module_init);
