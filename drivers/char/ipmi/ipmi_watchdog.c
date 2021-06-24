<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_watchकरोg.c
 *
 * A watchकरोg समयr based upon the IPMI पूर्णांकerface.
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 */

#घोषणा pr_fmt(fmt) "IPMI Watchdog: " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/ipmi_smi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/nmi.h>
#समावेश <linux/reboot.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched/संकेत.स>

#अगर_घोषित CONFIG_X86
/*
 * This is ugly, but I've determined that x86 is the only architecture
 * that can reasonably support the IPMI NMI watchकरोg समयout at this
 * समय.  If another architecture adds this capability somehow, it
 * will have to be a somewhat dअगरferent mechanism and I have no idea
 * how it will work.  So in the unlikely event that another
 * architecture supports this, we can figure out a good generic
 * mechanism क्रम it at that समय.
 */
#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/nmi.h>
#घोषणा HAVE_DIE_NMI
#पूर्ण_अगर

/*
 * The IPMI command/response inक्रमmation क्रम the watchकरोg समयr.
 */

/* values क्रम byte 1 of the set command, byte 2 of the get response. */
#घोषणा WDOG_DONT_LOG		(1 << 7)
#घोषणा WDOG_DONT_STOP_ON_SET	(1 << 6)
#घोषणा WDOG_SET_TIMER_USE(byte, use) \
	byte = ((byte) & 0xf8) | ((use) & 0x7)
#घोषणा WDOG_GET_TIMER_USE(byte) ((byte) & 0x7)
#घोषणा WDOG_TIMER_USE_BIOS_FRB2	1
#घोषणा WDOG_TIMER_USE_BIOS_POST	2
#घोषणा WDOG_TIMER_USE_OS_LOAD		3
#घोषणा WDOG_TIMER_USE_SMS_OS		4
#घोषणा WDOG_TIMER_USE_OEM		5

/* values क्रम byte 2 of the set command, byte 3 of the get response. */
#घोषणा WDOG_SET_PRETIMEOUT_ACT(byte, use) \
	byte = ((byte) & 0x8f) | (((use) & 0x7) << 4)
#घोषणा WDOG_GET_PRETIMEOUT_ACT(byte) (((byte) >> 4) & 0x7)
#घोषणा WDOG_PRETIMEOUT_NONE		0
#घोषणा WDOG_PRETIMEOUT_SMI		1
#घोषणा WDOG_PRETIMEOUT_NMI		2
#घोषणा WDOG_PRETIMEOUT_MSG_INT		3

/* Operations that can be perक्रमmed on a pretimout. */
#घोषणा WDOG_PREOP_NONE		0
#घोषणा WDOG_PREOP_PANIC	1
/* Cause data to be available to पढ़ो.  Doesn't work in NMI mode. */
#घोषणा WDOG_PREOP_GIVE_DATA	2

/* Actions to perक्रमm on a full समयout. */
#घोषणा WDOG_SET_TIMEOUT_ACT(byte, use) \
	byte = ((byte) & 0xf8) | ((use) & 0x7)
#घोषणा WDOG_GET_TIMEOUT_ACT(byte) ((byte) & 0x7)
#घोषणा WDOG_TIMEOUT_NONE		0
#घोषणा WDOG_TIMEOUT_RESET		1
#घोषणा WDOG_TIMEOUT_POWER_DOWN		2
#घोषणा WDOG_TIMEOUT_POWER_CYCLE	3

/*
 * Byte 3 of the get command, byte 4 of the get response is the
 * pre-समयout in seconds.
 */

/* Bits क्रम setting byte 4 of the set command, byte 5 of the get response. */
#घोषणा WDOG_EXPIRE_CLEAR_BIOS_FRB2	(1 << 1)
#घोषणा WDOG_EXPIRE_CLEAR_BIOS_POST	(1 << 2)
#घोषणा WDOG_EXPIRE_CLEAR_OS_LOAD	(1 << 3)
#घोषणा WDOG_EXPIRE_CLEAR_SMS_OS	(1 << 4)
#घोषणा WDOG_EXPIRE_CLEAR_OEM		(1 << 5)

/*
 * Setting/getting the watchकरोg समयr value.  This is क्रम bytes 5 and
 * 6 (the समयout समय) of the set command, and bytes 6 and 7 (the
 * समयout समय) and 8 and 9 (the current countकरोwn value) of the
 * response.  The समयout value is given in seconds (in the command it
 * is 100ms पूर्णांकervals).
 */
#घोषणा WDOG_SET_TIMEOUT(byte1, byte2, val) \
	(byte1) = (((val) * 10) & 0xff), (byte2) = (((val) * 10) >> 8)
#घोषणा WDOG_GET_TIMEOUT(byte1, byte2) \
	(((byte1) | ((byte2) << 8)) / 10)

#घोषणा IPMI_WDOG_RESET_TIMER		0x22
#घोषणा IPMI_WDOG_SET_TIMER		0x24
#घोषणा IPMI_WDOG_GET_TIMER		0x25

#घोषणा IPMI_WDOG_TIMER_NOT_INIT_RESP	0x80

अटल DEFINE_MUTEX(ipmi_watchकरोg_mutex);
अटल bool nowayout = WATCHDOG_NOWAYOUT;

अटल काष्ठा ipmi_user *watchकरोg_user;
अटल पूर्णांक watchकरोg_अगरnum;

/* Default the समयout to 10 seconds. */
अटल पूर्णांक समयout = 10;

/* The pre-समयout is disabled by शेष. */
अटल पूर्णांक preसमयout;

/* Default समयout to set on panic */
अटल पूर्णांक panic_wdt_समयout = 255;

/* Default action is to reset the board on a समयout. */
अटल अचिन्हित अक्षर action_val = WDOG_TIMEOUT_RESET;

अटल अक्षर action[16] = "reset";

अटल अचिन्हित अक्षर preaction_val = WDOG_PRETIMEOUT_NONE;

अटल अक्षर preaction[16] = "pre_none";

अटल अचिन्हित अक्षर preop_val = WDOG_PREOP_NONE;

अटल अक्षर preop[16] = "preop_none";
अटल DEFINE_SPINLOCK(ipmi_पढ़ो_lock);
अटल अक्षर data_to_पढ़ो;
अटल DECLARE_WAIT_QUEUE_HEAD(पढ़ो_q);
अटल काष्ठा fasync_काष्ठा *fasync_q;
अटल atomic_t preसमयout_since_last_heartbeat;
अटल अक्षर expect_बंद;

अटल पूर्णांक अगरnum_to_use = -1;

/* Parameters to ipmi_set_समयout */
#घोषणा IPMI_SET_TIMEOUT_NO_HB			0
#घोषणा IPMI_SET_TIMEOUT_HB_IF_NECESSARY	1
#घोषणा IPMI_SET_TIMEOUT_FORCE_HB		2

अटल पूर्णांक ipmi_set_समयout(पूर्णांक करो_heartbeat);
अटल व्योम ipmi_रेजिस्टर_watchकरोg(पूर्णांक ipmi_पूर्णांकf);
अटल व्योम ipmi_unरेजिस्टर_watchकरोg(पूर्णांक ipmi_पूर्णांकf);

/*
 * If true, the driver will start running as soon as it is configured
 * and पढ़ोy.
 */
अटल पूर्णांक start_now;

अटल पूर्णांक set_param_समयout(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अक्षर *endp;
	पूर्णांक  l;
	पूर्णांक  rv = 0;

	अगर (!val)
		वापस -EINVAL;
	l = simple_म_से_अदीर्घ(val, &endp, 0);
	अगर (endp == val)
		वापस -EINVAL;

	*((पूर्णांक *)kp->arg) = l;
	अगर (watchकरोg_user)
		rv = ipmi_set_समयout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

	वापस rv;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_समयout = अणु
	.set = set_param_समयout,
	.get = param_get_पूर्णांक,
पूर्ण;
#घोषणा param_check_समयout param_check_पूर्णांक

प्रकार पूर्णांक (*action_fn)(स्थिर अक्षर *पूर्णांकval, अक्षर *outval);

अटल पूर्णांक action_op(स्थिर अक्षर *inval, अक्षर *outval);
अटल पूर्णांक preaction_op(स्थिर अक्षर *inval, अक्षर *outval);
अटल पूर्णांक preop_op(स्थिर अक्षर *inval, अक्षर *outval);
अटल व्योम check_parms(व्योम);

अटल पूर्णांक set_param_str(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	action_fn  fn = (action_fn) kp->arg;
	पूर्णांक        rv = 0;
	अक्षर       valcp[16];
	अक्षर       *s;

	म_नकलन(valcp, val, 15);
	valcp[15] = '\0';

	s = म_मालाip(valcp);

	rv = fn(s, शून्य);
	अगर (rv)
		जाओ out;

	check_parms();
	अगर (watchकरोg_user)
		rv = ipmi_set_समयout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

 out:
	वापस rv;
पूर्ण

अटल पूर्णांक get_param_str(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	action_fn fn = (action_fn) kp->arg;
	पूर्णांक rv, len;

	rv = fn(शून्य, buffer);
	अगर (rv)
		वापस rv;

	len = म_माप(buffer);
	buffer[len++] = '\n';
	buffer[len] = 0;

	वापस len;
पूर्ण


अटल पूर्णांक set_param_wकरोg_अगरnum(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rv = param_set_पूर्णांक(val, kp);
	अगर (rv)
		वापस rv;
	अगर ((अगरnum_to_use < 0) || (अगरnum_to_use == watchकरोg_अगरnum))
		वापस 0;

	ipmi_unरेजिस्टर_watchकरोg(watchकरोg_अगरnum);
	ipmi_रेजिस्टर_watchकरोg(अगरnum_to_use);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_wकरोg_अगरnum = अणु
	.set = set_param_wकरोg_अगरnum,
	.get = param_get_पूर्णांक,
पूर्ण;

#घोषणा param_check_wकरोg_अगरnum param_check_पूर्णांक

अटल स्थिर काष्ठा kernel_param_ops param_ops_str = अणु
	.set = set_param_str,
	.get = get_param_str,
पूर्ण;

module_param(अगरnum_to_use, wकरोg_अगरnum, 0644);
MODULE_PARM_DESC(अगरnum_to_use, "The interface number to use for the watchdog "
		 "timer.  Setting to -1 defaults to the first registered "
		 "interface");

module_param(समयout, समयout, 0644);
MODULE_PARM_DESC(समयout, "Timeout value in seconds.");

module_param(preसमयout, समयout, 0644);
MODULE_PARM_DESC(preसमयout, "Pretimeout value in seconds.");

module_param(panic_wdt_समयout, समयout, 0644);
MODULE_PARM_DESC(panic_wdt_समयout, "Timeout value on kernel panic in seconds.");

module_param_cb(action, &param_ops_str, action_op, 0644);
MODULE_PARM_DESC(action, "Timeout action. One of: "
		 "reset, none, power_cycle, power_off.");

module_param_cb(preaction, &param_ops_str, preaction_op, 0644);
MODULE_PARM_DESC(preaction, "Pretimeout action.  One of: "
		 "pre_none, pre_smi, pre_nmi, pre_int.");

module_param_cb(preop, &param_ops_str, preop_op, 0644);
MODULE_PARM_DESC(preop, "Pretimeout driver operation.  One of: "
		 "preop_none, preop_panic, preop_give_data.");

module_param(start_now, पूर्णांक, 0444);
MODULE_PARM_DESC(start_now, "Set to 1 to start the watchdog as"
		 "soon as the driver is loaded.");

module_param(nowayout, bool, 0644);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started "
		 "(default=CONFIG_WATCHDOG_NOWAYOUT)");

/* Default state of the समयr. */
अटल अचिन्हित अक्षर ipmi_watchकरोg_state = WDOG_TIMEOUT_NONE;

/* Is someone using the watchकरोg?  Only one user is allowed. */
अटल अचिन्हित दीर्घ ipmi_wकरोg_खोलो;

/*
 * If set to 1, the heartbeat command will set the state to reset and
 * start the समयr.  The समयr करोesn't normally run when the driver is
 * first खोलोed until the heartbeat is set the first समय, this
 * variable is used to accomplish this.
 */
अटल पूर्णांक ipmi_start_समयr_on_heartbeat;

/* IPMI version of the BMC. */
अटल अचिन्हित अक्षर ipmi_version_major;
अटल अचिन्हित अक्षर ipmi_version_minor;

/* If a preसमयout occurs, this is used to allow only one panic to happen. */
अटल atomic_t preop_panic_excl = ATOMIC_INIT(-1);

#अगर_घोषित HAVE_DIE_NMI
अटल पूर्णांक testing_nmi;
अटल पूर्णांक nmi_handler_रेजिस्टरed;
#पूर्ण_अगर

अटल पूर्णांक __ipmi_heartbeat(व्योम);

/*
 * We use a mutex to make sure that only one thing can send a set a
 * message at one समय.  The mutex is claimed when a message is sent
 * and मुक्तd when both the send and receive messages are मुक्त.
 */
अटल atomic_t msg_toमुक्त = ATOMIC_INIT(0);
अटल DECLARE_COMPLETION(msg_रुको);
अटल व्योम msg_मुक्त_smi(काष्ठा ipmi_smi_msg *msg)
अणु
	अगर (atomic_dec_and_test(&msg_toमुक्त))
		complete(&msg_रुको);
पूर्ण
अटल व्योम msg_मुक्त_recv(काष्ठा ipmi_recv_msg *msg)
अणु
	अगर (atomic_dec_and_test(&msg_toमुक्त))
		complete(&msg_रुको);
पूर्ण
अटल काष्ठा ipmi_smi_msg smi_msg = अणु
	.करोne = msg_मुक्त_smi
पूर्ण;
अटल काष्ठा ipmi_recv_msg recv_msg = अणु
	.करोne = msg_मुक्त_recv
पूर्ण;

अटल पूर्णांक __ipmi_set_समयout(काष्ठा ipmi_smi_msg  *smi_msg,
			      काष्ठा ipmi_recv_msg *recv_msg,
			      पूर्णांक                  *send_heartbeat_now)
अणु
	काष्ठा kernel_ipmi_msg            msg;
	अचिन्हित अक्षर                     data[6];
	पूर्णांक                               rv;
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr addr;
	पूर्णांक                               hbnow = 0;


	data[0] = 0;
	WDOG_SET_TIMER_USE(data[0], WDOG_TIMER_USE_SMS_OS);

	अगर ((ipmi_version_major > 1)
	    || ((ipmi_version_major == 1) && (ipmi_version_minor >= 5))) अणु
		/* This is an IPMI 1.5-only feature. */
		data[0] |= WDOG_DONT_STOP_ON_SET;
	पूर्ण अन्यथा अगर (ipmi_watchकरोg_state != WDOG_TIMEOUT_NONE) अणु
		/*
		 * In ipmi 1.0, setting the समयr stops the watchकरोg, we
		 * need to start it back up again.
		 */
		hbnow = 1;
	पूर्ण

	data[1] = 0;
	WDOG_SET_TIMEOUT_ACT(data[1], ipmi_watchकरोg_state);
	अगर ((preसमयout > 0) && (ipmi_watchकरोg_state != WDOG_TIMEOUT_NONE)) अणु
	    WDOG_SET_PRETIMEOUT_ACT(data[1], preaction_val);
	    data[2] = preसमयout;
	पूर्ण अन्यथा अणु
	    WDOG_SET_PRETIMEOUT_ACT(data[1], WDOG_PRETIMEOUT_NONE);
	    data[2] = 0; /* No preसमयout. */
	पूर्ण
	data[3] = 0;
	WDOG_SET_TIMEOUT(data[4], data[5], समयout);

	addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	addr.channel = IPMI_BMC_CHANNEL;
	addr.lun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_SET_TIMER;
	msg.data = data;
	msg.data_len = माप(data);
	rv = ipmi_request_supply_msgs(watchकरोg_user,
				      (काष्ठा ipmi_addr *) &addr,
				      0,
				      &msg,
				      शून्य,
				      smi_msg,
				      recv_msg,
				      1);
	अगर (rv)
		pr_warn("set timeout error: %d\n", rv);
	अन्यथा अगर (send_heartbeat_now)
		*send_heartbeat_now = hbnow;

	वापस rv;
पूर्ण

अटल पूर्णांक _ipmi_set_समयout(पूर्णांक करो_heartbeat)
अणु
	पूर्णांक send_heartbeat_now;
	पूर्णांक rv;

	अगर (!watchकरोg_user)
		वापस -ENODEV;

	atomic_set(&msg_toमुक्त, 2);

	rv = __ipmi_set_समयout(&smi_msg,
				&recv_msg,
				&send_heartbeat_now);
	अगर (rv)
		वापस rv;

	रुको_क्रम_completion(&msg_रुको);

	अगर ((करो_heartbeat == IPMI_SET_TIMEOUT_FORCE_HB)
		|| ((send_heartbeat_now)
		    && (करो_heartbeat == IPMI_SET_TIMEOUT_HB_IF_NECESSARY)))
		rv = __ipmi_heartbeat();

	वापस rv;
पूर्ण

अटल पूर्णांक ipmi_set_समयout(पूर्णांक करो_heartbeat)
अणु
	पूर्णांक rv;

	mutex_lock(&ipmi_watchकरोg_mutex);
	rv = _ipmi_set_समयout(करो_heartbeat);
	mutex_unlock(&ipmi_watchकरोg_mutex);

	वापस rv;
पूर्ण

अटल atomic_t panic_करोne_count = ATOMIC_INIT(0);

अटल व्योम panic_smi_मुक्त(काष्ठा ipmi_smi_msg *msg)
अणु
	atomic_dec(&panic_करोne_count);
पूर्ण
अटल व्योम panic_recv_मुक्त(काष्ठा ipmi_recv_msg *msg)
अणु
	atomic_dec(&panic_करोne_count);
पूर्ण

अटल काष्ठा ipmi_smi_msg panic_halt_heartbeat_smi_msg = अणु
	.करोne = panic_smi_मुक्त
पूर्ण;
अटल काष्ठा ipmi_recv_msg panic_halt_heartbeat_recv_msg = अणु
	.करोne = panic_recv_मुक्त
पूर्ण;

अटल व्योम panic_halt_ipmi_heartbeat(व्योम)
अणु
	काष्ठा kernel_ipmi_msg             msg;
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr addr;
	पूर्णांक rv;

	/*
	 * Don't reset the समयr अगर we have the समयr turned off, that
	 * re-enables the watchकरोg.
	 */
	अगर (ipmi_watchकरोg_state == WDOG_TIMEOUT_NONE)
		वापस;

	addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	addr.channel = IPMI_BMC_CHANNEL;
	addr.lun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_RESET_TIMER;
	msg.data = शून्य;
	msg.data_len = 0;
	atomic_inc(&panic_करोne_count);
	rv = ipmi_request_supply_msgs(watchकरोg_user,
				      (काष्ठा ipmi_addr *) &addr,
				      0,
				      &msg,
				      शून्य,
				      &panic_halt_heartbeat_smi_msg,
				      &panic_halt_heartbeat_recv_msg,
				      1);
	अगर (rv)
		atomic_dec(&panic_करोne_count);
पूर्ण

अटल काष्ठा ipmi_smi_msg panic_halt_smi_msg = अणु
	.करोne = panic_smi_मुक्त
पूर्ण;
अटल काष्ठा ipmi_recv_msg panic_halt_recv_msg = अणु
	.करोne = panic_recv_मुक्त
पूर्ण;

/*
 * Special call, करोesn't claim any locks.  This is only to be called
 * at panic or halt समय, in run-to-completion mode, when the caller
 * is the only CPU and the only thing that will be going is these IPMI
 * calls.
 */
अटल व्योम panic_halt_ipmi_set_समयout(व्योम)
अणु
	पूर्णांक send_heartbeat_now;
	पूर्णांक rv;

	/* Wait क्रम the messages to be मुक्त. */
	जबतक (atomic_पढ़ो(&panic_करोne_count) != 0)
		ipmi_poll_पूर्णांकerface(watchकरोg_user);
	atomic_inc(&panic_करोne_count);
	rv = __ipmi_set_समयout(&panic_halt_smi_msg,
				&panic_halt_recv_msg,
				&send_heartbeat_now);
	अगर (rv) अणु
		atomic_dec(&panic_करोne_count);
		pr_warn("Unable to extend the watchdog timeout\n");
	पूर्ण अन्यथा अणु
		अगर (send_heartbeat_now)
			panic_halt_ipmi_heartbeat();
	पूर्ण
	जबतक (atomic_पढ़ो(&panic_करोne_count) != 0)
		ipmi_poll_पूर्णांकerface(watchकरोg_user);
पूर्ण

अटल पूर्णांक __ipmi_heartbeat(व्योम)
अणु
	काष्ठा kernel_ipmi_msg msg;
	पूर्णांक rv;
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr addr;
	पूर्णांक समयout_retries = 0;

restart:
	/*
	 * Don't reset the समयr अगर we have the समयr turned off, that
	 * re-enables the watchकरोg.
	 */
	अगर (ipmi_watchकरोg_state == WDOG_TIMEOUT_NONE)
		वापस 0;

	atomic_set(&msg_toमुक्त, 2);

	addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	addr.channel = IPMI_BMC_CHANNEL;
	addr.lun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_RESET_TIMER;
	msg.data = शून्य;
	msg.data_len = 0;
	rv = ipmi_request_supply_msgs(watchकरोg_user,
				      (काष्ठा ipmi_addr *) &addr,
				      0,
				      &msg,
				      शून्य,
				      &smi_msg,
				      &recv_msg,
				      1);
	अगर (rv) अणु
		pr_warn("heartbeat send failure: %d\n", rv);
		वापस rv;
	पूर्ण

	/* Wait क्रम the heartbeat to be sent. */
	रुको_क्रम_completion(&msg_रुको);

	अगर (recv_msg.msg.data[0] == IPMI_WDOG_TIMER_NOT_INIT_RESP)  अणु
		समयout_retries++;
		अगर (समयout_retries > 3) अणु
			pr_err("Unable to restore the IPMI watchdog's settings, giving up\n");
			rv = -EIO;
			जाओ out;
		पूर्ण

		/*
		 * The समयr was not initialized, that means the BMC was
		 * probably reset and lost the watchकरोg inक्रमmation.  Attempt
		 * to restore the समयr's info.  Note that we still hold
		 * the heartbeat lock, to keep a heartbeat from happening
		 * in this process, so must say no heartbeat to aव्योम a
		 * deadlock on this mutex
		 */
		rv = _ipmi_set_समयout(IPMI_SET_TIMEOUT_NO_HB);
		अगर (rv) अणु
			pr_err("Unable to send the command to set the watchdog's settings, giving up\n");
			जाओ out;
		पूर्ण

		/* Might need a heartbeat send, go ahead and करो it. */
		जाओ restart;
	पूर्ण अन्यथा अगर (recv_msg.msg.data[0] != 0) अणु
		/*
		 * Got an error in the heartbeat response.  It was alपढ़ोy
		 * reported in ipmi_wकरोg_msg_handler, but we should वापस
		 * an error here.
		 */
		rv = -EINVAL;
	पूर्ण

out:
	वापस rv;
पूर्ण

अटल पूर्णांक _ipmi_heartbeat(व्योम)
अणु
	पूर्णांक rv;

	अगर (!watchकरोg_user)
		वापस -ENODEV;

	अगर (ipmi_start_समयr_on_heartbeat) अणु
		ipmi_start_समयr_on_heartbeat = 0;
		ipmi_watchकरोg_state = action_val;
		rv = _ipmi_set_समयout(IPMI_SET_TIMEOUT_FORCE_HB);
	पूर्ण अन्यथा अगर (atomic_cmpxchg(&preसमयout_since_last_heartbeat, 1, 0)) अणु
		/*
		 * A preसमयout occurred, make sure we set the समयout.
		 * We करोn't want to set the action, though, we want to
		 * leave that alone (thus it can't be combined with the
		 * above operation.
		 */
		rv = _ipmi_set_समयout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);
	पूर्ण अन्यथा अणु
		rv = __ipmi_heartbeat();
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक ipmi_heartbeat(व्योम)
अणु
	पूर्णांक rv;

	mutex_lock(&ipmi_watchकरोg_mutex);
	rv = _ipmi_heartbeat();
	mutex_unlock(&ipmi_watchकरोg_mutex);

	वापस rv;
पूर्ण

अटल काष्ठा watchकरोg_info ident = अणु
	.options	= 0,	/* WDIOF_SETTIMEOUT, */
	.firmware_version = 1,
	.identity	= "IPMI"
पूर्ण;

अटल पूर्णांक ipmi_ioctl(काष्ठा file *file,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक i;
	पूर्णांक val;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		i = copy_to_user(argp, &ident, माप(ident));
		वापस i ? -EFAULT : 0;

	हाल WDIOC_SETTIMEOUT:
		i = copy_from_user(&val, argp, माप(पूर्णांक));
		अगर (i)
			वापस -EFAULT;
		समयout = val;
		वापस _ipmi_set_समयout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

	हाल WDIOC_GETTIMEOUT:
		i = copy_to_user(argp, &समयout, माप(समयout));
		अगर (i)
			वापस -EFAULT;
		वापस 0;

	हाल WDIOC_SETPRETIMEOUT:
		i = copy_from_user(&val, argp, माप(पूर्णांक));
		अगर (i)
			वापस -EFAULT;
		preसमयout = val;
		वापस _ipmi_set_समयout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

	हाल WDIOC_GETPRETIMEOUT:
		i = copy_to_user(argp, &preसमयout, माप(preसमयout));
		अगर (i)
			वापस -EFAULT;
		वापस 0;

	हाल WDIOC_KEEPALIVE:
		वापस _ipmi_heartbeat();

	हाल WDIOC_SETOPTIONS:
		i = copy_from_user(&val, argp, माप(पूर्णांक));
		अगर (i)
			वापस -EFAULT;
		अगर (val & WDIOS_DISABLECARD) अणु
			ipmi_watchकरोg_state = WDOG_TIMEOUT_NONE;
			_ipmi_set_समयout(IPMI_SET_TIMEOUT_NO_HB);
			ipmi_start_समयr_on_heartbeat = 0;
		पूर्ण

		अगर (val & WDIOS_ENABLECARD) अणु
			ipmi_watchकरोg_state = action_val;
			_ipmi_set_समयout(IPMI_SET_TIMEOUT_FORCE_HB);
		पूर्ण
		वापस 0;

	हाल WDIOC_GETSTATUS:
		val = 0;
		i = copy_to_user(argp, &val, माप(val));
		अगर (i)
			वापस -EFAULT;
		वापस 0;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल दीर्घ ipmi_unlocked_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&ipmi_watchकरोg_mutex);
	ret = ipmi_ioctl(file, cmd, arg);
	mutex_unlock(&ipmi_watchकरोg_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ipmi_ग_लिखो(काष्ठा file *file,
			  स्थिर अक्षर  __user *buf,
			  माप_प्रकार      len,
			  loff_t      *ppos)
अणु
	पूर्णांक rv;

	अगर (len) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* In हाल it was set दीर्घ ago */
			expect_बंद = 0;

			क्रम (i = 0; i != len; i++) अणु
				अक्षर c;

				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					expect_बंद = 42;
			पूर्ण
		पूर्ण
		rv = ipmi_heartbeat();
		अगर (rv)
			वापस rv;
	पूर्ण
	वापस len;
पूर्ण

अटल sमाप_प्रकार ipmi_पढ़ो(काष्ठा file *file,
			 अक्षर        __user *buf,
			 माप_प्रकार      count,
			 loff_t      *ppos)
अणु
	पूर्णांक          rv = 0;
	रुको_queue_entry_t रुको;

	अगर (count <= 0)
		वापस 0;

	/*
	 * Reading वापसs अगर the preसमयout has gone off, and it only करोes
	 * it once per preसमयout.
	 */
	spin_lock_irq(&ipmi_पढ़ो_lock);
	अगर (!data_to_पढ़ो) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			rv = -EAGAIN;
			जाओ out;
		पूर्ण

		init_रुकोqueue_entry(&रुको, current);
		add_रुको_queue(&पढ़ो_q, &रुको);
		जबतक (!data_to_पढ़ो) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&ipmi_पढ़ो_lock);
			schedule();
			spin_lock_irq(&ipmi_पढ़ो_lock);
		पूर्ण
		हटाओ_रुको_queue(&पढ़ो_q, &रुको);

		अगर (संकेत_pending(current)) अणु
			rv = -ERESTARTSYS;
			जाओ out;
		पूर्ण
	पूर्ण
	data_to_पढ़ो = 0;

 out:
	spin_unlock_irq(&ipmi_पढ़ो_lock);

	अगर (rv == 0) अणु
		अगर (copy_to_user(buf, &data_to_पढ़ो, 1))
			rv = -EFAULT;
		अन्यथा
			rv = 1;
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक ipmi_खोलो(काष्ठा inode *ino, काष्ठा file *filep)
अणु
	चयन (iminor(ino)) अणु
	हाल WATCHDOG_MINOR:
		अगर (test_and_set_bit(0, &ipmi_wकरोg_खोलो))
			वापस -EBUSY;


		/*
		 * Don't start the समयr now, let it start on the
		 * first heartbeat.
		 */
		ipmi_start_समयr_on_heartbeat = 1;
		वापस stream_खोलो(ino, filep);

	शेष:
		वापस (-ENODEV);
	पूर्ण
पूर्ण

अटल __poll_t ipmi_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = 0;

	poll_रुको(file, &पढ़ो_q, रुको);

	spin_lock_irq(&ipmi_पढ़ो_lock);
	अगर (data_to_पढ़ो)
		mask |= (EPOLLIN | EPOLLRDNORM);
	spin_unlock_irq(&ipmi_पढ़ो_lock);

	वापस mask;
पूर्ण

अटल पूर्णांक ipmi_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	पूर्णांक result;

	result = fasync_helper(fd, file, on, &fasync_q);

	वापस (result);
पूर्ण

अटल पूर्णांक ipmi_बंद(काष्ठा inode *ino, काष्ठा file *filep)
अणु
	अगर (iminor(ino) == WATCHDOG_MINOR) अणु
		अगर (expect_बंद == 42) अणु
			mutex_lock(&ipmi_watchकरोg_mutex);
			ipmi_watchकरोg_state = WDOG_TIMEOUT_NONE;
			_ipmi_set_समयout(IPMI_SET_TIMEOUT_NO_HB);
			mutex_unlock(&ipmi_watchकरोg_mutex);
		पूर्ण अन्यथा अणु
			pr_crit("Unexpected close, not stopping watchdog!\n");
			ipmi_heartbeat();
		पूर्ण
		clear_bit(0, &ipmi_wकरोg_खोलो);
	पूर्ण

	expect_बंद = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ipmi_wकरोg_fops = अणु
	.owner   = THIS_MODULE,
	.पढ़ो    = ipmi_पढ़ो,
	.poll    = ipmi_poll,
	.ग_लिखो   = ipmi_ग_लिखो,
	.unlocked_ioctl = ipmi_unlocked_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो    = ipmi_खोलो,
	.release = ipmi_बंद,
	.fasync  = ipmi_fasync,
	.llseek  = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice ipmi_wकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &ipmi_wकरोg_fops
पूर्ण;

अटल व्योम ipmi_wकरोg_msg_handler(काष्ठा ipmi_recv_msg *msg,
				  व्योम                 *handler_data)
अणु
	अगर (msg->msg.cmd == IPMI_WDOG_RESET_TIMER &&
			msg->msg.data[0] == IPMI_WDOG_TIMER_NOT_INIT_RESP)
		pr_info("response: The IPMI controller appears to have been reset, will attempt to reinitialize the watchdog timer\n");
	अन्यथा अगर (msg->msg.data[0] != 0)
		pr_err("response: Error %x on cmd %x\n",
		       msg->msg.data[0],
		       msg->msg.cmd);

	ipmi_मुक्त_recv_msg(msg);
पूर्ण

अटल व्योम ipmi_wकरोg_preसमयout_handler(व्योम *handler_data)
अणु
	अगर (preaction_val != WDOG_PRETIMEOUT_NONE) अणु
		अगर (preop_val == WDOG_PREOP_PANIC) अणु
			अगर (atomic_inc_and_test(&preop_panic_excl))
				panic("Watchdog pre-timeout");
		पूर्ण अन्यथा अगर (preop_val == WDOG_PREOP_GIVE_DATA) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&ipmi_पढ़ो_lock, flags);
			data_to_पढ़ो = 1;
			wake_up_पूर्णांकerruptible(&पढ़ो_q);
			समाप्त_fasync(&fasync_q, SIGIO, POLL_IN);
			spin_unlock_irqrestore(&ipmi_पढ़ो_lock, flags);
		पूर्ण
	पूर्ण

	/*
	 * On some machines, the heartbeat will give an error and not
	 * work unless we re-enable the समयr.  So करो so.
	 */
	atomic_set(&preसमयout_since_last_heartbeat, 1);
पूर्ण

अटल व्योम ipmi_wकरोg_panic_handler(व्योम *user_data)
अणु
	अटल पूर्णांक panic_event_handled;

	/*
	 * On a panic, अगर we have a panic समयout, make sure to extend
	 * the watchकरोg समयr to a reasonable value to complete the
	 * panic, अगर the watchकरोg समयr is running.  Plus the
	 * preसमयout is meaningless at panic समय.
	 */
	अगर (watchकरोg_user && !panic_event_handled &&
	    ipmi_watchकरोg_state != WDOG_TIMEOUT_NONE) अणु
		/* Make sure we करो this only once. */
		panic_event_handled = 1;

		समयout = panic_wdt_समयout;
		preसमयout = 0;
		panic_halt_ipmi_set_समयout();
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ipmi_user_hndl ipmi_hndlrs = अणु
	.ipmi_recv_hndl           = ipmi_wकरोg_msg_handler,
	.ipmi_watchकरोg_preसमयout = ipmi_wकरोg_preसमयout_handler,
	.ipmi_panic_handler       = ipmi_wकरोg_panic_handler
पूर्ण;

अटल व्योम ipmi_रेजिस्टर_watchकरोg(पूर्णांक ipmi_पूर्णांकf)
अणु
	पूर्णांक rv = -EBUSY;

	अगर (watchकरोg_user)
		जाओ out;

	अगर ((अगरnum_to_use >= 0) && (अगरnum_to_use != ipmi_पूर्णांकf))
		जाओ out;

	watchकरोg_अगरnum = ipmi_पूर्णांकf;

	rv = ipmi_create_user(ipmi_पूर्णांकf, &ipmi_hndlrs, शून्य, &watchकरोg_user);
	अगर (rv < 0) अणु
		pr_crit("Unable to register with ipmi\n");
		जाओ out;
	पूर्ण

	rv = ipmi_get_version(watchकरोg_user,
			      &ipmi_version_major,
			      &ipmi_version_minor);
	अगर (rv) अणु
		pr_warn("Unable to get IPMI version, assuming 1.0\n");
		ipmi_version_major = 1;
		ipmi_version_minor = 0;
	पूर्ण

	rv = misc_रेजिस्टर(&ipmi_wकरोg_miscdev);
	अगर (rv < 0) अणु
		ipmi_destroy_user(watchकरोg_user);
		watchकरोg_user = शून्य;
		pr_crit("Unable to register misc device\n");
	पूर्ण

#अगर_घोषित HAVE_DIE_NMI
	अगर (nmi_handler_रेजिस्टरed) अणु
		पूर्णांक old_preसमयout = preसमयout;
		पूर्णांक old_समयout = समयout;
		पूर्णांक old_preop_val = preop_val;

		/*
		 * Set the preसमयout to go off in a second and give
		 * ourselves plenty of समय to stop the समयr.
		 */
		ipmi_watchकरोg_state = WDOG_TIMEOUT_RESET;
		preop_val = WDOG_PREOP_NONE; /* Make sure nothing happens */
		preसमयout = 99;
		समयout = 100;

		testing_nmi = 1;

		rv = ipmi_set_समयout(IPMI_SET_TIMEOUT_FORCE_HB);
		अगर (rv) अणु
			pr_warn("Error starting timer to test NMI: 0x%x.  The NMI pretimeout will likely not work\n",
				rv);
			rv = 0;
			जाओ out_restore;
		पूर्ण

		msleep(1500);

		अगर (testing_nmi != 2) अणु
			pr_warn("IPMI NMI didn't seem to occur.  The NMI pretimeout will likely not work\n");
		पूर्ण
 out_restore:
		testing_nmi = 0;
		preop_val = old_preop_val;
		preसमयout = old_preसमयout;
		समयout = old_समयout;
	पूर्ण
#पूर्ण_अगर

 out:
	अगर ((start_now) && (rv == 0)) अणु
		/* Run from startup, so start the समयr now. */
		start_now = 0; /* Disable this function after first startup. */
		ipmi_watchकरोg_state = action_val;
		ipmi_set_समयout(IPMI_SET_TIMEOUT_FORCE_HB);
		pr_info("Starting now!\n");
	पूर्ण अन्यथा अणु
		/* Stop the समयr now. */
		ipmi_watchकरोg_state = WDOG_TIMEOUT_NONE;
		ipmi_set_समयout(IPMI_SET_TIMEOUT_NO_HB);
	पूर्ण
पूर्ण

अटल व्योम ipmi_unरेजिस्टर_watchकरोg(पूर्णांक ipmi_पूर्णांकf)
अणु
	पूर्णांक rv;
	काष्ठा ipmi_user *loc_user = watchकरोg_user;

	अगर (!loc_user)
		वापस;

	अगर (watchकरोg_अगरnum != ipmi_पूर्णांकf)
		वापस;

	/* Make sure no one can call us any more. */
	misc_deरेजिस्टर(&ipmi_wकरोg_miscdev);

	watchकरोg_user = शून्य;

	/*
	 * Wait to make sure the message makes it out.  The lower layer has
	 * poपूर्णांकers to our buffers, we want to make sure they are करोne beक्रमe
	 * we release our memory.
	 */
	जबतक (atomic_पढ़ो(&msg_toमुक्त))
		msg_मुक्त_smi(शून्य);

	mutex_lock(&ipmi_watchकरोg_mutex);

	/* Disconnect from IPMI. */
	rv = ipmi_destroy_user(loc_user);
	अगर (rv)
		pr_warn("error unlinking from IPMI: %d\n",  rv);

	/* If it comes back, restart it properly. */
	ipmi_start_समयr_on_heartbeat = 1;

	mutex_unlock(&ipmi_watchकरोg_mutex);
पूर्ण

#अगर_घोषित HAVE_DIE_NMI
अटल पूर्णांक
ipmi_nmi(अचिन्हित पूर्णांक val, काष्ठा pt_regs *regs)
अणु
	/*
	 * If we get here, it's an NMI that's not a memory or I/O
	 * error.  We can't truly tell if it's from IPMI or not
	 * without sending a message, and sending a message is almost
	 * impossible because of locking.
	 */

	अगर (testing_nmi) अणु
		testing_nmi = 2;
		वापस NMI_HANDLED;
	पूर्ण

	/* If we are not expecting a समयout, ignore it. */
	अगर (ipmi_watchकरोg_state == WDOG_TIMEOUT_NONE)
		वापस NMI_DONE;

	अगर (preaction_val != WDOG_PRETIMEOUT_NMI)
		वापस NMI_DONE;

	/*
	 * If no one अन्यथा handled the NMI, we assume it was the IPMI
	 * watchकरोg.
	 */
	अगर (preop_val == WDOG_PREOP_PANIC) अणु
		/* On some machines, the heartbeat will give
		   an error and not work unless we re-enable
		   the समयr.   So करो so. */
		atomic_set(&preसमयout_since_last_heartbeat, 1);
		अगर (atomic_inc_and_test(&preop_panic_excl))
			nmi_panic(regs, "pre-timeout");
	पूर्ण

	वापस NMI_HANDLED;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक wकरोg_reboot_handler(काष्ठा notअगरier_block *this,
			       अचिन्हित दीर्घ         code,
			       व्योम                  *unused)
अणु
	अटल पूर्णांक reboot_event_handled;

	अगर ((watchकरोg_user) && (!reboot_event_handled)) अणु
		/* Make sure we only करो this once. */
		reboot_event_handled = 1;

		अगर (code == SYS_POWER_OFF || code == SYS_HALT) अणु
			/* Disable the WDT अगर we are shutting करोwn. */
			ipmi_watchकरोg_state = WDOG_TIMEOUT_NONE;
			ipmi_set_समयout(IPMI_SET_TIMEOUT_NO_HB);
		पूर्ण अन्यथा अगर (ipmi_watchकरोg_state != WDOG_TIMEOUT_NONE) अणु
			/* Set a दीर्घ समयr to let the reboot happen or
			   reset अगर it hangs, but only अगर the watchकरोg
			   समयr was alपढ़ोy running. */
			अगर (समयout < 120)
				समयout = 120;
			preसमयout = 0;
			ipmi_watchकरोg_state = WDOG_TIMEOUT_RESET;
			ipmi_set_समयout(IPMI_SET_TIMEOUT_NO_HB);
		पूर्ण
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block wकरोg_reboot_notअगरier = अणु
	.notअगरier_call	= wकरोg_reboot_handler,
	.next		= शून्य,
	.priority	= 0
पूर्ण;

अटल व्योम ipmi_new_smi(पूर्णांक अगर_num, काष्ठा device *device)
अणु
	ipmi_रेजिस्टर_watchकरोg(अगर_num);
पूर्ण

अटल व्योम ipmi_smi_gone(पूर्णांक अगर_num)
अणु
	ipmi_unरेजिस्टर_watchकरोg(अगर_num);
पूर्ण

अटल काष्ठा ipmi_smi_watcher smi_watcher = अणु
	.owner    = THIS_MODULE,
	.new_smi  = ipmi_new_smi,
	.smi_gone = ipmi_smi_gone
पूर्ण;

अटल पूर्णांक action_op(स्थिर अक्षर *inval, अक्षर *outval)
अणु
	अगर (outval)
		म_नकल(outval, action);

	अगर (!inval)
		वापस 0;

	अगर (म_भेद(inval, "reset") == 0)
		action_val = WDOG_TIMEOUT_RESET;
	अन्यथा अगर (म_भेद(inval, "none") == 0)
		action_val = WDOG_TIMEOUT_NONE;
	अन्यथा अगर (म_भेद(inval, "power_cycle") == 0)
		action_val = WDOG_TIMEOUT_POWER_CYCLE;
	अन्यथा अगर (म_भेद(inval, "power_off") == 0)
		action_val = WDOG_TIMEOUT_POWER_DOWN;
	अन्यथा
		वापस -EINVAL;
	म_नकल(action, inval);
	वापस 0;
पूर्ण

अटल पूर्णांक preaction_op(स्थिर अक्षर *inval, अक्षर *outval)
अणु
	अगर (outval)
		म_नकल(outval, preaction);

	अगर (!inval)
		वापस 0;

	अगर (म_भेद(inval, "pre_none") == 0)
		preaction_val = WDOG_PRETIMEOUT_NONE;
	अन्यथा अगर (म_भेद(inval, "pre_smi") == 0)
		preaction_val = WDOG_PRETIMEOUT_SMI;
#अगर_घोषित HAVE_DIE_NMI
	अन्यथा अगर (म_भेद(inval, "pre_nmi") == 0)
		preaction_val = WDOG_PRETIMEOUT_NMI;
#पूर्ण_अगर
	अन्यथा अगर (म_भेद(inval, "pre_int") == 0)
		preaction_val = WDOG_PRETIMEOUT_MSG_INT;
	अन्यथा
		वापस -EINVAL;
	म_नकल(preaction, inval);
	वापस 0;
पूर्ण

अटल पूर्णांक preop_op(स्थिर अक्षर *inval, अक्षर *outval)
अणु
	अगर (outval)
		म_नकल(outval, preop);

	अगर (!inval)
		वापस 0;

	अगर (म_भेद(inval, "preop_none") == 0)
		preop_val = WDOG_PREOP_NONE;
	अन्यथा अगर (म_भेद(inval, "preop_panic") == 0)
		preop_val = WDOG_PREOP_PANIC;
	अन्यथा अगर (म_भेद(inval, "preop_give_data") == 0)
		preop_val = WDOG_PREOP_GIVE_DATA;
	अन्यथा
		वापस -EINVAL;
	म_नकल(preop, inval);
	वापस 0;
पूर्ण

अटल व्योम check_parms(व्योम)
अणु
#अगर_घोषित HAVE_DIE_NMI
	पूर्णांक करो_nmi = 0;
	पूर्णांक rv;

	अगर (preaction_val == WDOG_PRETIMEOUT_NMI) अणु
		करो_nmi = 1;
		अगर (preop_val == WDOG_PREOP_GIVE_DATA) अणु
			pr_warn("Pretimeout op is to give data but NMI pretimeout is enabled, setting pretimeout op to none\n");
			preop_op("preop_none", शून्य);
			करो_nmi = 0;
		पूर्ण
	पूर्ण
	अगर (करो_nmi && !nmi_handler_रेजिस्टरed) अणु
		rv = रेजिस्टर_nmi_handler(NMI_UNKNOWN, ipmi_nmi, 0,
						"ipmi");
		अगर (rv) अणु
			pr_warn("Can't register nmi handler\n");
			वापस;
		पूर्ण अन्यथा
			nmi_handler_रेजिस्टरed = 1;
	पूर्ण अन्यथा अगर (!करो_nmi && nmi_handler_रेजिस्टरed) अणु
		unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "ipmi");
		nmi_handler_रेजिस्टरed = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init ipmi_wकरोg_init(व्योम)
अणु
	पूर्णांक rv;

	अगर (action_op(action, शून्य)) अणु
		action_op("reset", शून्य);
		pr_info("Unknown action '%s', defaulting to reset\n", action);
	पूर्ण

	अगर (preaction_op(preaction, शून्य)) अणु
		preaction_op("pre_none", शून्य);
		pr_info("Unknown preaction '%s', defaulting to none\n",
			preaction);
	पूर्ण

	अगर (preop_op(preop, शून्य)) अणु
		preop_op("preop_none", शून्य);
		pr_info("Unknown preop '%s', defaulting to none\n", preop);
	पूर्ण

	check_parms();

	रेजिस्टर_reboot_notअगरier(&wकरोg_reboot_notअगरier);

	rv = ipmi_smi_watcher_रेजिस्टर(&smi_watcher);
	अगर (rv) अणु
#अगर_घोषित HAVE_DIE_NMI
		अगर (nmi_handler_रेजिस्टरed)
			unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "ipmi");
#पूर्ण_अगर
		unरेजिस्टर_reboot_notअगरier(&wकरोg_reboot_notअगरier);
		pr_warn("can't register smi watcher\n");
		वापस rv;
	पूर्ण

	pr_info("driver initialized\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास ipmi_wकरोg_निकास(व्योम)
अणु
	ipmi_smi_watcher_unरेजिस्टर(&smi_watcher);
	ipmi_unरेजिस्टर_watchकरोg(watchकरोg_अगरnum);

#अगर_घोषित HAVE_DIE_NMI
	अगर (nmi_handler_रेजिस्टरed)
		unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "ipmi");
#पूर्ण_अगर

	unरेजिस्टर_reboot_notअगरier(&wकरोg_reboot_notअगरier);
पूर्ण
module_निकास(ipmi_wकरोg_निकास);
module_init(ipmi_wकरोg_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corey Minyard <minyard@mvista.com>");
MODULE_DESCRIPTION("watchdog timer based upon the IPMI interface.");
