<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Host AP (software wireless LAN access poपूर्णांक) driver क्रम
 * Intersil Prism2/2.5/3.
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <j@w1.fi>
 * Copyright (c) 2002-2005, Jouni Malinen <j@w1.fi>
 *
 * FIX:
 * - there is currently no way of associating TX packets to correct wds device
 *   when TX Exc/OK event occurs, so all tx_packets and some
 *   tx_errors/tx_dropped are added to the मुख्य netdevice; using sw_support
 *   field in txdesc might be used to fix this (using Alloc event to increment
 *   tx_packets would need some further info in txfid table)
 *
 * Buffer Access Path (BAP) usage:
 *   Prism2 cards have two separate BAPs क्रम accessing the card memory. These
 *   should allow concurrent access to two dअगरferent frames and the driver
 *   previously used BAP0 क्रम sending data and BAP1 क्रम receiving data.
 *   However, there seems to be number of issues with concurrent access and at
 *   least one know hardware bug in using BAP0 and BAP1 concurrently with PCI
 *   Prism2.5. Thereक्रमe, the driver now only uses BAP0 क्रम moving data between
 *   host and card memories. BAP0 accesses are रक्षित with local->baplock
 *   (spin_lock_bh) to prevent concurrent use.
 */



#समावेश <यंत्र/delay.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>
#समावेश <net/lib80211.h>
#समावेश <यंत्र/irq.h>

#समावेश "hostap_80211.h"
#समावेश "hostap.h"
#समावेश "hostap_ap.h"


/* #घोषणा final_version */

अटल पूर्णांक mtu = 1500;
module_param(mtu, पूर्णांक, 0444);
MODULE_PARM_DESC(mtu, "Maximum transfer unit");

अटल पूर्णांक channel[MAX_PARM_DEVICES] = अणु 3, DEF_INTS पूर्ण;
module_param_array(channel, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(channel, "Initial channel");

अटल अक्षर essid[33] = "test";
module_param_string(essid, essid, माप(essid), 0444);
MODULE_PARM_DESC(essid, "Host AP's ESSID");

अटल पूर्णांक iw_mode[MAX_PARM_DEVICES] = अणु IW_MODE_MASTER, DEF_INTS पूर्ण;
module_param_array(iw_mode, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(iw_mode, "Initial operation mode");

अटल पूर्णांक beacon_पूर्णांक[MAX_PARM_DEVICES] = अणु 100, DEF_INTS पूर्ण;
module_param_array(beacon_पूर्णांक, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(beacon_पूर्णांक, "Beacon interval (1 = 1024 usec)");

अटल पूर्णांक dtim_period[MAX_PARM_DEVICES] = अणु 1, DEF_INTS पूर्ण;
module_param_array(dtim_period, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(dtim_period, "DTIM period");

अटल अक्षर dev_ढाँचा[16] = "wlan%d";
module_param_string(dev_ढाँचा, dev_ढाँचा, माप(dev_ढाँचा), 0444);
MODULE_PARM_DESC(dev_ढाँचा, "Prefix for network device name (default: "
		 "wlan%d)");

#अगर_घोषित final_version
#घोषणा EXTRA_EVENTS_WTERR 0
#अन्यथा
/* check WTERR events (Wait Time-out) in development versions */
#घोषणा EXTRA_EVENTS_WTERR HFA384X_EV_WTERR
#पूर्ण_अगर

/* Events that will be using BAP0 */
#घोषणा HFA384X_BAP0_EVENTS \
	(HFA384X_EV_TXEXC | HFA384X_EV_RX | HFA384X_EV_INFO | HFA384X_EV_TX)

/* event mask, i.e., events that will result in an पूर्णांकerrupt */
#घोषणा HFA384X_EVENT_MASK \
	(HFA384X_BAP0_EVENTS | HFA384X_EV_ALLOC | HFA384X_EV_INFDROP | \
	HFA384X_EV_CMD | HFA384X_EV_TICK | \
	EXTRA_EVENTS_WTERR)

/* Default TX control flags: use 802.11 headers and request पूर्णांकerrupt क्रम
 * failed transmits. Frames that request ACK callback, will add
 * _TX_OK flag and _ALT_RTRY flag may be used to select dअगरferent retry policy.
 */
#घोषणा HFA384X_TX_CTRL_FLAGS \
	(HFA384X_TX_CTRL_802_11 | HFA384X_TX_CTRL_TX_EX)


/* ca. 1 usec */
#घोषणा HFA384X_CMD_BUSY_TIMEOUT 5000
#घोषणा HFA384X_BAP_BUSY_TIMEOUT 50000

/* ca. 10 usec */
#घोषणा HFA384X_CMD_COMPL_TIMEOUT 20000
#घोषणा HFA384X_DL_COMPL_TIMEOUT 1000000

/* Wait बार क्रम initialization; yield to other processes to aव्योम busy
 * रुकोing क्रम दीर्घ समय. */
#घोषणा HFA384X_INIT_TIMEOUT (HZ / 2) /* 500 ms */
#घोषणा HFA384X_ALLOC_COMPL_TIMEOUT (HZ / 20) /* 50 ms */


अटल व्योम prism2_hw_reset(काष्ठा net_device *dev);
अटल व्योम prism2_check_sta_fw_version(local_info_t *local);

#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
/* hostap_करोwnload.c */
अटल स्थिर काष्ठा proc_ops prism2_करोwnload_aux_dump_proc_ops;
अटल u8 * prism2_पढ़ो_pda(काष्ठा net_device *dev);
अटल पूर्णांक prism2_करोwnload(local_info_t *local,
			   काष्ठा prism2_करोwnload_param *param);
अटल व्योम prism2_करोwnload_मुक्त_data(काष्ठा prism2_करोwnload_data *dl);
अटल पूर्णांक prism2_करोwnload_अस्थिर(local_info_t *local,
				    काष्ठा prism2_करोwnload_data *param);
अटल पूर्णांक prism2_करोwnload_genesis(local_info_t *local,
				   काष्ठा prism2_करोwnload_data *param);
अटल पूर्णांक prism2_get_ram_size(local_info_t *local);
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */




#अगर_अघोषित final_version
/* magic value written to SWSUPPORT0 reg. क्रम detecting whether card is still
 * present */
#घोषणा HFA384X_MAGIC 0x8A32
#पूर्ण_अगर

अटल व्योम hfa384x_पढ़ो_regs(काष्ठा net_device *dev,
			      काष्ठा hfa384x_regs *regs)
अणु
	regs->cmd = HFA384X_INW(HFA384X_CMD_OFF);
	regs->evstat = HFA384X_INW(HFA384X_EVSTAT_OFF);
	regs->offset0 = HFA384X_INW(HFA384X_OFFSET0_OFF);
	regs->offset1 = HFA384X_INW(HFA384X_OFFSET1_OFF);
	regs->swsupport0 = HFA384X_INW(HFA384X_SWSUPPORT0_OFF);
पूर्ण


/**
 * __hostap_cmd_queue_मुक्त - Free Prism2 command queue entry (निजी)
 * @local: poपूर्णांकer to निजी Host AP driver data
 * @entry: Prism2 command queue entry to be मुक्तd
 * @del_req: request the entry to be हटाओd
 *
 * Internal helper function क्रम मुक्तing Prism2 command queue entries.
 * Caller must have acquired local->cmdlock beक्रमe calling this function.
 */
अटल अंतरभूत व्योम __hostap_cmd_queue_मुक्त(local_info_t *local,
					   काष्ठा hostap_cmd_queue *entry,
					   पूर्णांक del_req)
अणु
	अगर (del_req) अणु
		entry->del_req = 1;
		अगर (!list_empty(&entry->list)) अणु
			list_del_init(&entry->list);
			local->cmd_queue_len--;
		पूर्ण
	पूर्ण

	अगर (refcount_dec_and_test(&entry->usecnt) && entry->del_req)
		kमुक्त(entry);
पूर्ण


/**
 * hostap_cmd_queue_मुक्त - Free Prism2 command queue entry
 * @local: poपूर्णांकer to निजी Host AP driver data
 * @entry: Prism2 command queue entry to be मुक्तd
 * @del_req: request the entry to be हटाओd
 *
 * Free a Prism2 command queue entry.
 */
अटल अंतरभूत व्योम hostap_cmd_queue_मुक्त(local_info_t *local,
					 काष्ठा hostap_cmd_queue *entry,
					 पूर्णांक del_req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&local->cmdlock, flags);
	__hostap_cmd_queue_मुक्त(local, entry, del_req);
	spin_unlock_irqrestore(&local->cmdlock, flags);
पूर्ण


/**
 * prism2_clear_cmd_queue - Free all pending Prism2 command queue entries
 * @local: poपूर्णांकer to निजी Host AP driver data
 */
अटल व्योम prism2_clear_cmd_queue(local_info_t *local)
अणु
	काष्ठा list_head *ptr, *n;
	अचिन्हित दीर्घ flags;
	काष्ठा hostap_cmd_queue *entry;

	spin_lock_irqsave(&local->cmdlock, flags);
	list_क्रम_each_safe(ptr, n, &local->cmd_queue) अणु
		entry = list_entry(ptr, काष्ठा hostap_cmd_queue, list);
		refcount_inc(&entry->usecnt);
		prपूर्णांकk(KERN_DEBUG "%s: removed pending cmd_queue entry "
		       "(type=%d, cmd=0x%04x, param0=0x%04x)\n",
		       local->dev->name, entry->type, entry->cmd,
		       entry->param0);
		__hostap_cmd_queue_मुक्त(local, entry, 1);
	पूर्ण
	अगर (local->cmd_queue_len) अणु
		/* This should not happen; prपूर्णांक debug message and clear
		 * queue length. */
		prपूर्णांकk(KERN_DEBUG "%s: cmd_queue_len (%d) not zero after "
		       "flush\n", local->dev->name, local->cmd_queue_len);
		local->cmd_queue_len = 0;
	पूर्ण
	spin_unlock_irqrestore(&local->cmdlock, flags);
पूर्ण


/**
 * hfa384x_cmd_issue - Issue a Prism2 command to the hardware
 * @dev: poपूर्णांकer to net_device
 * @entry: Prism2 command queue entry to be issued
 */
अटल पूर्णांक hfa384x_cmd_issue(काष्ठा net_device *dev,
				    काष्ठा hostap_cmd_queue *entry)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक tries;
	u16 reg;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->card_present && !local->func->card_present(local))
		वापस -ENODEV;

	अगर (entry->issued) अणु
		prपूर्णांकk(KERN_DEBUG "%s: driver bug - re-issuing command @%p\n",
		       dev->name, entry);
	पूर्ण

	/* रुको until busy bit is clear; this should always be clear since the
	 * commands are serialized */
	tries = HFA384X_CMD_BUSY_TIMEOUT;
	जबतक (HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY && tries > 0) अणु
		tries--;
		udelay(1);
	पूर्ण
#अगर_अघोषित final_version
	अगर (tries != HFA384X_CMD_BUSY_TIMEOUT) अणु
		prism2_io_debug_error(dev, 1);
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd_issue: cmd reg was busy "
		       "for %d usec\n", dev->name,
		       HFA384X_CMD_BUSY_TIMEOUT - tries);
	पूर्ण
#पूर्ण_अगर
	अगर (tries == 0) अणु
		reg = HFA384X_INW(HFA384X_CMD_OFF);
		prism2_io_debug_error(dev, 2);
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd_issue - timeout - "
		       "reg=0x%04x\n", dev->name, reg);
		वापस -ETIMEDOUT;
	पूर्ण

	/* ग_लिखो command */
	spin_lock_irqsave(&local->cmdlock, flags);
	HFA384X_OUTW(entry->param0, HFA384X_PARAM0_OFF);
	HFA384X_OUTW(entry->param1, HFA384X_PARAM1_OFF);
	HFA384X_OUTW(entry->cmd, HFA384X_CMD_OFF);
	entry->issued = 1;
	spin_unlock_irqrestore(&local->cmdlock, flags);

	वापस 0;
पूर्ण


/**
 * hfa384x_cmd - Issue a Prism2 command and रुको (sleep) क्रम completion
 * @dev: poपूर्णांकer to net_device
 * @cmd: Prism2 command code (HFA384X_CMD_CODE_*)
 * @param0: value क्रम Param0 रेजिस्टर
 * @param1: value क्रम Param1 रेजिस्टर (poपूर्णांकer; %शून्य अगर not used)
 * @resp0: poपूर्णांकer क्रम Resp0 data or %शून्य अगर Resp0 is not needed
 *
 * Issue given command (possibly after रुकोing in command queue) and sleep
 * until the command is completed (or समयd out or पूर्णांकerrupted). This can be
 * called only from user process context.
 */
अटल पूर्णांक hfa384x_cmd(काष्ठा net_device *dev, u16 cmd, u16 param0,
		       u16 *param1, u16 *resp0)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक err, res, issue, issued = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा hostap_cmd_queue *entry;
	DECLARE_WAITQUEUE(रुको, current);

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->cmd_queue_len >= HOSTAP_CMD_QUEUE_MAX_LEN) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd: cmd_queue full\n",
		       dev->name);
		वापस -1;
	पूर्ण

	अगर (संकेत_pending(current))
		वापस -EINTR;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	refcount_set(&entry->usecnt, 1);
	entry->type = CMD_SLEEP;
	entry->cmd = cmd;
	entry->param0 = param0;
	अगर (param1)
		entry->param1 = *param1;
	init_रुकोqueue_head(&entry->compl);

	/* prepare to रुको क्रम command completion event, but करो not sleep yet
	 */
	add_रुको_queue(&entry->compl, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);

	spin_lock_irqsave(&local->cmdlock, flags);
	issue = list_empty(&local->cmd_queue);
	अगर (issue)
		entry->issuing = 1;
	list_add_tail(&entry->list, &local->cmd_queue);
	local->cmd_queue_len++;
	spin_unlock_irqrestore(&local->cmdlock, flags);

	err = 0;
	अगर (!issue)
		जाओ रुको_completion;

	अगर (संकेत_pending(current))
		err = -EINTR;

	अगर (!err) अणु
		अगर (hfa384x_cmd_issue(dev, entry))
			err = -ETIMEDOUT;
		अन्यथा
			issued = 1;
	पूर्ण

 रुको_completion:
	अगर (!err && entry->type != CMD_COMPLETED) अणु
		/* sleep until command is completed or समयd out */
		res = schedule_समयout(2 * HZ);
	पूर्ण अन्यथा
		res = -1;

	अगर (!err && संकेत_pending(current))
		err = -EINTR;

	अगर (err && issued) अणु
		/* the command was issued, so a CmdCompl event should occur
		 * soon; however, there's a pending संकेत and
		 * schedule_समयout() would be पूर्णांकerrupted; रुको a लघु period
		 * of समय to aव्योम removing entry from the list beक्रमe
		 * CmdCompl event */
		udelay(300);
	पूर्ण

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&entry->compl, &रुको);

	/* If entry->list is still in the list, it must be हटाओd
	 * first and in this हाल prism2_cmd_ev() करोes not yet have
	 * local reference to it, and the data can be kमुक्त()'d
	 * here. If the command completion event is still generated,
	 * it will be asचिन्हित to next (possibly) pending command, but
	 * the driver will reset the card anyway due to समयout
	 *
	 * If the entry is not in the list prism2_cmd_ev() has a local
	 * reference to it, but keeps cmdlock as दीर्घ as the data is
	 * needed, so the data can be kमुक्त()'d here. */

	/* FIX: अगर the entry->list is in the list, it has not been completed
	 * yet, so removing it here is somewhat wrong.. this could cause
	 * references to मुक्तd memory and next list_del() causing शून्य poपूर्णांकer
	 * dereference.. it would probably be better to leave the entry in the
	 * list and the list should be emptied during hw reset */

	spin_lock_irqsave(&local->cmdlock, flags);
	अगर (!list_empty(&entry->list)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd: entry still in list? "
		       "(entry=%p, type=%d, res=%d)\n", dev->name, entry,
		       entry->type, res);
		list_del_init(&entry->list);
		local->cmd_queue_len--;
	पूर्ण
	spin_unlock_irqrestore(&local->cmdlock, flags);

	अगर (err) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd: interrupted; err=%d\n",
		       dev->name, err);
		res = err;
		जाओ करोne;
	पूर्ण

	अगर (entry->type != CMD_COMPLETED) अणु
		u16 reg = HFA384X_INW(HFA384X_EVSTAT_OFF);
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd: command was not "
		       "completed (res=%d, entry=%p, type=%d, cmd=0x%04x, "
		       "param0=0x%04x, EVSTAT=%04x INTEN=%04x)\n", dev->name,
		       res, entry, entry->type, entry->cmd, entry->param0, reg,
		       HFA384X_INW(HFA384X_INTEN_OFF));
		अगर (reg & HFA384X_EV_CMD) अणु
			/* Command completion event is pending, but the
			 * पूर्णांकerrupt was not delivered - probably an issue
			 * with pcmcia-cs configuration. */
			prपूर्णांकk(KERN_WARNING "%s: interrupt delivery does not "
			       "seem to work\n", dev->name);
		पूर्ण
		prism2_io_debug_error(dev, 3);
		res = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	अगर (resp0 != शून्य)
		*resp0 = entry->resp0;
#अगर_अघोषित final_version
	अगर (entry->res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: CMD=0x%04x => res=0x%02x, "
		       "resp0=0x%04x\n",
		       dev->name, cmd, entry->res, entry->resp0);
	पूर्ण
#पूर्ण_अगर /* final_version */

	res = entry->res;
 करोne:
	hostap_cmd_queue_मुक्त(local, entry, 1);
	वापस res;
पूर्ण


/**
 * hfa384x_cmd_callback - Issue a Prism2 command; callback when completed
 * @dev: poपूर्णांकer to net_device
 * @cmd: Prism2 command code (HFA384X_CMD_CODE_*)
 * @param0: value क्रम Param0 रेजिस्टर
 * @callback: command completion callback function (%शून्य = no callback)
 * @context: context data to be given to the callback function
 *
 * Issue given command (possibly after रुकोing in command queue) and use
 * callback function to indicate command completion. This can be called both
 * from user and पूर्णांकerrupt context. The callback function will be called in
 * hardware IRQ context. It can be %शून्य, when no function is called when
 * command is completed.
 */
अटल पूर्णांक hfa384x_cmd_callback(काष्ठा net_device *dev, u16 cmd, u16 param0,
				व्योम (*callback)(काष्ठा net_device *dev,
						 दीर्घ context, u16 resp0,
						 u16 status),
				दीर्घ context)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक issue, ret;
	अचिन्हित दीर्घ flags;
	काष्ठा hostap_cmd_queue *entry;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->cmd_queue_len >= HOSTAP_CMD_QUEUE_MAX_LEN + 2) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd: cmd_queue full\n",
		       dev->name);
		वापस -1;
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	refcount_set(&entry->usecnt, 1);
	entry->type = CMD_CALLBACK;
	entry->cmd = cmd;
	entry->param0 = param0;
	entry->callback = callback;
	entry->context = context;

	spin_lock_irqsave(&local->cmdlock, flags);
	issue = list_empty(&local->cmd_queue);
	अगर (issue)
		entry->issuing = 1;
	list_add_tail(&entry->list, &local->cmd_queue);
	local->cmd_queue_len++;
	spin_unlock_irqrestore(&local->cmdlock, flags);

	अगर (issue && hfa384x_cmd_issue(dev, entry))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = 0;

	hostap_cmd_queue_मुक्त(local, entry, ret);

	वापस ret;
पूर्ण


/**
 * __hfa384x_cmd_no_रुको - Issue a Prism2 command (निजी)
 * @dev: poपूर्णांकer to net_device
 * @cmd: Prism2 command code (HFA384X_CMD_CODE_*)
 * @param0: value क्रम Param0 रेजिस्टर
 * @io_debug_num: I/O debug error number
 *
 * Shared helper function क्रम hfa384x_cmd_रुको() and hfa384x_cmd_no_रुको().
 */
अटल पूर्णांक __hfa384x_cmd_no_रुको(काष्ठा net_device *dev, u16 cmd, u16 param0,
				 पूर्णांक io_debug_num)
अणु
	पूर्णांक tries;
	u16 reg;

	/* रुको until busy bit is clear; this should always be clear since the
	 * commands are serialized */
	tries = HFA384X_CMD_BUSY_TIMEOUT;
	जबतक (HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY && tries > 0) अणु
		tries--;
		udelay(1);
	पूर्ण
	अगर (tries == 0) अणु
		reg = HFA384X_INW(HFA384X_CMD_OFF);
		prism2_io_debug_error(dev, io_debug_num);
		prपूर्णांकk(KERN_DEBUG "%s: __hfa384x_cmd_no_wait(%d) - timeout - "
		       "reg=0x%04x\n", dev->name, io_debug_num, reg);
		वापस -ETIMEDOUT;
	पूर्ण

	/* ग_लिखो command */
	HFA384X_OUTW(param0, HFA384X_PARAM0_OFF);
	HFA384X_OUTW(cmd, HFA384X_CMD_OFF);

	वापस 0;
पूर्ण


/**
 * hfa384x_cmd_रुको - Issue a Prism2 command and busy रुको क्रम completion
 * @dev: poपूर्णांकer to net_device
 * @cmd: Prism2 command code (HFA384X_CMD_CODE_*)
 * @param0: value क्रम Param0 रेजिस्टर
 */
अटल पूर्णांक hfa384x_cmd_रुको(काष्ठा net_device *dev, u16 cmd, u16 param0)
अणु
	पूर्णांक res, tries;
	u16 reg;

	res = __hfa384x_cmd_no_रुको(dev, cmd, param0, 4);
	अगर (res)
		वापस res;

        /* रुको क्रम command completion */
	अगर ((cmd & HFA384X_CMDCODE_MASK) == HFA384X_CMDCODE_DOWNLOAD)
		tries = HFA384X_DL_COMPL_TIMEOUT;
	अन्यथा
		tries = HFA384X_CMD_COMPL_TIMEOUT;

        जबतक (!(HFA384X_INW(HFA384X_EVSTAT_OFF) & HFA384X_EV_CMD) &&
               tries > 0) अणु
                tries--;
                udelay(10);
        पूर्ण
        अगर (tries == 0) अणु
                reg = HFA384X_INW(HFA384X_EVSTAT_OFF);
		prism2_io_debug_error(dev, 5);
                prपूर्णांकk(KERN_DEBUG "%s: hfa384x_cmd_wait - timeout2 - "
		       "reg=0x%04x\n", dev->name, reg);
                वापस -ETIMEDOUT;
        पूर्ण

        res = (HFA384X_INW(HFA384X_STATUS_OFF) &
               (BIT(14) | BIT(13) | BIT(12) | BIT(11) | BIT(10) | BIT(9) |
                BIT(8))) >> 8;
#अगर_अघोषित final_version
	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: CMD=0x%04x => res=0x%02x\n",
		       dev->name, cmd, res);
	पूर्ण
#पूर्ण_अगर

	HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_EVACK_OFF);

	वापस res;
पूर्ण


/**
 * hfa384x_cmd_no_रुको - Issue a Prism2 command; करो not रुको क्रम completion
 * @dev: poपूर्णांकer to net_device
 * @cmd: Prism2 command code (HFA384X_CMD_CODE_*)
 * @param0: value क्रम Param0 रेजिस्टर
 */
अटल अंतरभूत पूर्णांक hfa384x_cmd_no_रुको(काष्ठा net_device *dev, u16 cmd,
				      u16 param0)
अणु
	वापस __hfa384x_cmd_no_रुको(dev, cmd, param0, 6);
पूर्ण


/**
 * prism2_cmd_ev - Prism2 command completion event handler
 * @dev: poपूर्णांकer to net_device
 *
 * Interrupt handler क्रम command completion events. Called by the मुख्य
 * पूर्णांकerrupt handler in hardware IRQ context. Read Resp0 and status रेजिस्टरs
 * from the hardware and ACK the event. Depending on the issued command type
 * either wake up the sleeping process that is रुकोing क्रम command completion
 * or call the callback function. Issue the next command, अगर one is pending.
 */
अटल व्योम prism2_cmd_ev(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hostap_cmd_queue *entry = शून्य;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	spin_lock(&local->cmdlock);
	अगर (!list_empty(&local->cmd_queue)) अणु
		entry = list_entry(local->cmd_queue.next,
				   काष्ठा hostap_cmd_queue, list);
		refcount_inc(&entry->usecnt);
		list_del_init(&entry->list);
		local->cmd_queue_len--;

		अगर (!entry->issued) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Command completion event, but "
			       "cmd not issued\n", dev->name);
			__hostap_cmd_queue_मुक्त(local, entry, 1);
			entry = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock(&local->cmdlock);

	अगर (!entry) अणु
		HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_EVACK_OFF);
		prपूर्णांकk(KERN_DEBUG "%s: Command completion event, but no "
		       "pending commands\n", dev->name);
		वापस;
	पूर्ण

	entry->resp0 = HFA384X_INW(HFA384X_RESP0_OFF);
	entry->res = (HFA384X_INW(HFA384X_STATUS_OFF) &
		      (BIT(14) | BIT(13) | BIT(12) | BIT(11) | BIT(10) |
		       BIT(9) | BIT(8))) >> 8;
	HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_EVACK_OFF);

	/* TODO: rest of the CmdEv handling could be moved to tasklet */
	अगर (entry->type == CMD_SLEEP) अणु
		entry->type = CMD_COMPLETED;
		wake_up_पूर्णांकerruptible(&entry->compl);
	पूर्ण अन्यथा अगर (entry->type == CMD_CALLBACK) अणु
		अगर (entry->callback)
			entry->callback(dev, entry->context, entry->resp0,
					entry->res);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: Invalid command completion type %d\n",
		       dev->name, entry->type);
	पूर्ण
	hostap_cmd_queue_मुक्त(local, entry, 1);

	/* issue next command, अगर pending */
	entry = शून्य;
	spin_lock(&local->cmdlock);
	अगर (!list_empty(&local->cmd_queue)) अणु
		entry = list_entry(local->cmd_queue.next,
				   काष्ठा hostap_cmd_queue, list);
		अगर (entry->issuing) अणु
			/* hfa384x_cmd() has alपढ़ोy started issuing this
			 * command, so करो not start here */
			entry = शून्य;
		पूर्ण
		अगर (entry)
			refcount_inc(&entry->usecnt);
	पूर्ण
	spin_unlock(&local->cmdlock);

	अगर (entry) अणु
		/* issue next command; अगर command issuing fails, हटाओ the
		 * entry from cmd_queue */
		पूर्णांक res = hfa384x_cmd_issue(dev, entry);
		spin_lock(&local->cmdlock);
		__hostap_cmd_queue_मुक्त(local, entry, res);
		spin_unlock(&local->cmdlock);
	पूर्ण
पूर्ण


अटल पूर्णांक hfa384x_रुको_offset(काष्ठा net_device *dev, u16 o_off)
अणु
	पूर्णांक tries = HFA384X_BAP_BUSY_TIMEOUT;
	पूर्णांक res = HFA384X_INW(o_off) & HFA384X_OFFSET_BUSY;

	जबतक (res && tries > 0) अणु
		tries--;
		udelay(1);
		res = HFA384X_INW(o_off) & HFA384X_OFFSET_BUSY;
	पूर्ण
	वापस res;
पूर्ण


/* Offset must be even */
अटल पूर्णांक hfa384x_setup_bap(काष्ठा net_device *dev, u16 bap, u16 id,
			     पूर्णांक offset)
अणु
	u16 o_off, s_off;
	पूर्णांक ret = 0;

	अगर (offset % 2 || bap > 1)
		वापस -EINVAL;

	अगर (bap == BAP1) अणु
		o_off = HFA384X_OFFSET1_OFF;
		s_off = HFA384X_SELECT1_OFF;
	पूर्ण अन्यथा अणु
		o_off = HFA384X_OFFSET0_OFF;
		s_off = HFA384X_SELECT0_OFF;
	पूर्ण

	अगर (hfa384x_रुको_offset(dev, o_off)) अणु
		prism2_io_debug_error(dev, 7);
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_setup_bap - timeout before\n",
		       dev->name);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	HFA384X_OUTW(id, s_off);
	HFA384X_OUTW(offset, o_off);

	अगर (hfa384x_रुको_offset(dev, o_off)) अणु
		prism2_io_debug_error(dev, 8);
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_setup_bap - timeout after\n",
		       dev->name);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण
#अगर_अघोषित final_version
	अगर (HFA384X_INW(o_off) & HFA384X_OFFSET_ERR) अणु
		prism2_io_debug_error(dev, 9);
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_setup_bap - offset error "
		       "(%d,0x04%x,%d); reg=0x%04x\n",
		       dev->name, bap, id, offset, HFA384X_INW(o_off));
		ret = -EINVAL;
	पूर्ण
#पूर्ण_अगर

 out:
	वापस ret;
पूर्ण


अटल पूर्णांक hfa384x_get_rid(काष्ठा net_device *dev, u16 rid, व्योम *buf, पूर्णांक len,
			   पूर्णांक exact_len)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक res, rlen = 0;
	काष्ठा hfa384x_rid_hdr rec;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->no_pri) अणु
		prपूर्णांकk(KERN_DEBUG "%s: cannot get RID %04x (len=%d) - no PRI "
		       "f/w\n", dev->name, rid, len);
		वापस -ENOTTY; /* Well.. not really correct, but वापस
				 * something unique enough.. */
	पूर्ण

	अगर ((local->func->card_present && !local->func->card_present(local)) ||
	    local->hw_करोwnloading)
		वापस -ENODEV;

	res = mutex_lock_पूर्णांकerruptible(&local->rid_bap_mtx);
	अगर (res)
		वापस res;

	res = hfa384x_cmd(dev, HFA384X_CMDCODE_ACCESS, rid, शून्य, शून्य);
	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_get_rid: CMDCODE_ACCESS failed "
		       "(res=%d, rid=%04x, len=%d)\n",
		       dev->name, res, rid, len);
		mutex_unlock(&local->rid_bap_mtx);
		वापस res;
	पूर्ण

	spin_lock_bh(&local->baplock);

	res = hfa384x_setup_bap(dev, BAP0, rid, 0);
	अगर (res)
		जाओ unlock;

	res = hfa384x_from_bap(dev, BAP0, &rec, माप(rec));
	अगर (res)
		जाओ unlock;

	अगर (le16_to_cpu(rec.len) == 0) अणु
		/* RID not available */
		res = -ENODATA;
		जाओ unlock;
	पूर्ण

	rlen = (le16_to_cpu(rec.len) - 1) * 2;
	अगर (exact_len && rlen != len) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_get_rid - RID len mismatch: "
		       "rid=0x%04x, len=%d (expected %d)\n",
		       dev->name, rid, rlen, len);
		res = -ENODATA;
	पूर्ण

	res = hfa384x_from_bap(dev, BAP0, buf, len);

unlock:
	spin_unlock_bh(&local->baplock);
	mutex_unlock(&local->rid_bap_mtx);

	अगर (res) अणु
		अगर (res != -ENODATA)
			prपूर्णांकk(KERN_DEBUG "%s: hfa384x_get_rid (rid=%04x, "
			       "len=%d) - failed - res=%d\n", dev->name, rid,
			       len, res);
		अगर (res == -ETIMEDOUT)
			prism2_hw_reset(dev);
		वापस res;
	पूर्ण

	वापस rlen;
पूर्ण


अटल पूर्णांक hfa384x_set_rid(काष्ठा net_device *dev, u16 rid, व्योम *buf, पूर्णांक len)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hfa384x_rid_hdr rec;
	पूर्णांक res;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->no_pri) अणु
		prपूर्णांकk(KERN_DEBUG "%s: cannot set RID %04x (len=%d) - no PRI "
		       "f/w\n", dev->name, rid, len);
		वापस -ENOTTY; /* Well.. not really correct, but वापस
				 * something unique enough.. */
	पूर्ण

	अगर ((local->func->card_present && !local->func->card_present(local)) ||
	    local->hw_करोwnloading)
		वापस -ENODEV;

	rec.rid = cpu_to_le16(rid);
	/* RID len in words and +1 क्रम rec.rid */
	rec.len = cpu_to_le16(len / 2 + len % 2 + 1);

	res = mutex_lock_पूर्णांकerruptible(&local->rid_bap_mtx);
	अगर (res)
		वापस res;

	spin_lock_bh(&local->baplock);
	res = hfa384x_setup_bap(dev, BAP0, rid, 0);
	अगर (!res)
		res = hfa384x_to_bap(dev, BAP0, &rec, माप(rec));
	अगर (!res)
		res = hfa384x_to_bap(dev, BAP0, buf, len);
	spin_unlock_bh(&local->baplock);

	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_set_rid (rid=%04x, len=%d) - "
		       "failed - res=%d\n", dev->name, rid, len, res);
		mutex_unlock(&local->rid_bap_mtx);
		वापस res;
	पूर्ण

	res = hfa384x_cmd(dev, HFA384X_CMDCODE_ACCESS_WRITE, rid, शून्य, शून्य);
	mutex_unlock(&local->rid_bap_mtx);

	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hfa384x_set_rid: CMDCODE_ACCESS_WRITE "
		       "failed (res=%d, rid=%04x, len=%d)\n",
		       dev->name, res, rid, len);

		अगर (res == -ETIMEDOUT)
			prism2_hw_reset(dev);
	पूर्ण

	वापस res;
पूर्ण


अटल व्योम hfa384x_disable_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	/* disable पूर्णांकerrupts and clear event status */
	HFA384X_OUTW(0, HFA384X_INTEN_OFF);
	HFA384X_OUTW(0xffff, HFA384X_EVACK_OFF);
पूर्ण


अटल व्योम hfa384x_enable_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	/* ack pending events and enable पूर्णांकerrupts from selected events */
	HFA384X_OUTW(0xffff, HFA384X_EVACK_OFF);
	HFA384X_OUTW(HFA384X_EVENT_MASK, HFA384X_INTEN_OFF);
पूर्ण


अटल व्योम hfa384x_events_no_bap0(काष्ठा net_device *dev)
अणु
	HFA384X_OUTW(HFA384X_EVENT_MASK & ~HFA384X_BAP0_EVENTS,
		     HFA384X_INTEN_OFF);
पूर्ण


अटल व्योम hfa384x_events_all(काष्ठा net_device *dev)
अणु
	HFA384X_OUTW(HFA384X_EVENT_MASK, HFA384X_INTEN_OFF);
पूर्ण


अटल व्योम hfa384x_events_only_cmd(काष्ठा net_device *dev)
अणु
	HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_INTEN_OFF);
पूर्ण


अटल u16 hfa384x_allocate_fid(काष्ठा net_device *dev, पूर्णांक len)
अणु
	u16 fid;
	अचिन्हित दीर्घ delay;

	/* FIX: this could be replace with hfa384x_cmd() अगर the Alloc event
	 * below would be handled like CmdCompl event (sleep here, wake up from
	 * पूर्णांकerrupt handler */
	अगर (hfa384x_cmd_रुको(dev, HFA384X_CMDCODE_ALLOC, len)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: cannot allocate fid, len=%d\n",
		       dev->name, len);
		वापस 0xffff;
	पूर्ण

	delay = jअगरfies + HFA384X_ALLOC_COMPL_TIMEOUT;
	जबतक (!(HFA384X_INW(HFA384X_EVSTAT_OFF) & HFA384X_EV_ALLOC) &&
	       समय_beक्रमe(jअगरfies, delay))
		yield();
	अगर (!(HFA384X_INW(HFA384X_EVSTAT_OFF) & HFA384X_EV_ALLOC)) अणु
		prपूर्णांकk("%s: fid allocate, len=%d - timeout\n", dev->name, len);
		वापस 0xffff;
	पूर्ण

	fid = HFA384X_INW(HFA384X_ALLOCFID_OFF);
	HFA384X_OUTW(HFA384X_EV_ALLOC, HFA384X_EVACK_OFF);

	वापस fid;
पूर्ण


अटल पूर्णांक prism2_reset_port(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक res;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (!local->dev_enabled)
		वापस 0;

	res = hfa384x_cmd(dev, HFA384X_CMDCODE_DISABLE, 0,
			  शून्य, शून्य);
	अगर (res)
		prपूर्णांकk(KERN_DEBUG "%s: reset port failed to disable port\n",
		       dev->name);
	अन्यथा अणु
		res = hfa384x_cmd(dev, HFA384X_CMDCODE_ENABLE, 0,
				  शून्य, शून्य);
		अगर (res)
			prपूर्णांकk(KERN_DEBUG "%s: reset port failed to enable "
			       "port\n", dev->name);
	पूर्ण

	/* It looks like at least some STA firmware versions reset
	 * fragmentation threshold back to 2346 after enable command. Restore
	 * the configured value, अगर it dअगरfers from this शेष. */
	अगर (local->fragm_threshold != 2346 &&
	    hostap_set_word(dev, HFA384X_RID_FRAGMENTATIONTHRESHOLD,
			    local->fragm_threshold)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: failed to restore fragmentation "
		       "threshold (%d) after Port0 enable\n",
		       dev->name, local->fragm_threshold);
	पूर्ण

	/* Some firmwares lose antenna selection settings on reset */
	(व्योम) hostap_set_antsel(local);

	वापस res;
पूर्ण


अटल पूर्णांक prism2_get_version_info(काष्ठा net_device *dev, u16 rid,
				   स्थिर अक्षर *txt)
अणु
	काष्ठा hfa384x_comp_ident comp;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->no_pri) अणु
		/* PRI f/w not yet available - cannot पढ़ो RIDs */
		वापस -1;
	पूर्ण
	अगर (hfa384x_get_rid(dev, rid, &comp, माप(comp), 1) < 0) अणु
		prपूर्णांकk(KERN_DEBUG "Could not get RID for component %s\n", txt);
		वापस -1;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: %s: id=0x%02x v%d.%d.%d\n", dev->name, txt,
	       __le16_to_cpu(comp.id), __le16_to_cpu(comp.major),
	       __le16_to_cpu(comp.minor), __le16_to_cpu(comp.variant));
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_setup_rids(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 पंचांगp;
	पूर्णांक ret = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	hostap_set_word(dev, HFA384X_RID_TICKTIME, 2000);

	अगर (!local->fw_ap) अणु
		u16 पंचांगp1 = hostap_get_porttype(local);
		ret = hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE, पंचांगp1);
		अगर (ret) अणु
			prपूर्णांकk("%s: Port type setting to %d failed\n",
			       dev->name, पंचांगp1);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Setting SSID to empty string seems to समाप्त the card in Host AP mode
	 */
	अगर (local->iw_mode != IW_MODE_MASTER || local->essid[0] != '\0') अणु
		ret = hostap_set_string(dev, HFA384X_RID_CNFOWNSSID,
					local->essid);
		अगर (ret) अणु
			prपूर्णांकk("%s: AP own SSID setting failed\n", dev->name);
			जाओ fail;
		पूर्ण
	पूर्ण

	ret = hostap_set_word(dev, HFA384X_RID_CNFMAXDATALEN,
			      PRISM2_DATA_MAXLEN);
	अगर (ret) अणु
		prपूर्णांकk("%s: MAC data length setting to %d failed\n",
		       dev->name, PRISM2_DATA_MAXLEN);
		जाओ fail;
	पूर्ण

	अगर (hfa384x_get_rid(dev, HFA384X_RID_CHANNELLIST, &पंचांगp, 2, 1) < 0) अणु
		prपूर्णांकk("%s: Channel list read failed\n", dev->name);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण
	local->channel_mask = le16_to_cpu(पंचांगp);

	अगर (local->channel < 1 || local->channel > 14 ||
	    !(local->channel_mask & (1 << (local->channel - 1)))) अणु
		prपूर्णांकk(KERN_WARNING "%s: Channel setting out of range "
		       "(%d)!\n", dev->name, local->channel);
		ret = -EBUSY;
		जाओ fail;
	पूर्ण

	ret = hostap_set_word(dev, HFA384X_RID_CNFOWNCHANNEL, local->channel);
	अगर (ret) अणु
		prपूर्णांकk("%s: Channel setting to %d failed\n",
		       dev->name, local->channel);
		जाओ fail;
	पूर्ण

	ret = hostap_set_word(dev, HFA384X_RID_CNFBEACONINT,
			      local->beacon_पूर्णांक);
	अगर (ret) अणु
		prपूर्णांकk("%s: Beacon interval setting to %d failed\n",
		       dev->name, local->beacon_पूर्णांक);
		/* this may fail with Symbol/Lucent firmware */
		अगर (ret == -ETIMEDOUT)
			जाओ fail;
	पूर्ण

	ret = hostap_set_word(dev, HFA384X_RID_CNFOWNDTIMPERIOD,
			      local->dtim_period);
	अगर (ret) अणु
		prपूर्णांकk("%s: DTIM period setting to %d failed\n",
		       dev->name, local->dtim_period);
		/* this may fail with Symbol/Lucent firmware */
		अगर (ret == -ETIMEDOUT)
			जाओ fail;
	पूर्ण

	ret = hostap_set_word(dev, HFA384X_RID_PROMISCUOUSMODE,
			      local->is_promisc);
	अगर (ret)
		prपूर्णांकk(KERN_INFO "%s: Setting promiscuous mode (%d) failed\n",
		       dev->name, local->is_promisc);

	अगर (!local->fw_ap) अणु
		ret = hostap_set_string(dev, HFA384X_RID_CNFDESIREDSSID,
					local->essid);
		अगर (ret) अणु
			prपूर्णांकk("%s: Desired SSID setting failed\n", dev->name);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Setup TXRateControl, शेषs to allow use of 1, 2, 5.5, and
	 * 11 Mbps in स्वतःmatic TX rate fallback and 1 and 2 Mbps as basic
	 * rates */
	अगर (local->tx_rate_control == 0) अणु
		local->tx_rate_control =
			HFA384X_RATES_1MBPS |
			HFA384X_RATES_2MBPS |
			HFA384X_RATES_5MBPS |
			HFA384X_RATES_11MBPS;
	पूर्ण
	अगर (local->basic_rates == 0)
		local->basic_rates = HFA384X_RATES_1MBPS | HFA384X_RATES_2MBPS;

	अगर (!local->fw_ap) अणु
		ret = hostap_set_word(dev, HFA384X_RID_TXRATECONTROL,
				      local->tx_rate_control);
		अगर (ret) अणु
			prपूर्णांकk("%s: TXRateControl setting to %d failed\n",
			       dev->name, local->tx_rate_control);
			जाओ fail;
		पूर्ण

		ret = hostap_set_word(dev, HFA384X_RID_CNFSUPPORTEDRATES,
				      local->tx_rate_control);
		अगर (ret) अणु
			prपूर्णांकk("%s: cnfSupportedRates setting to %d failed\n",
			       dev->name, local->tx_rate_control);
		पूर्ण

		ret = hostap_set_word(dev, HFA384X_RID_CNFBASICRATES,
				      local->basic_rates);
		अगर (ret) अणु
			prपूर्णांकk("%s: cnfBasicRates setting to %d failed\n",
			       dev->name, local->basic_rates);
		पूर्ण

		ret = hostap_set_word(dev, HFA384X_RID_CREATEIBSS, 1);
		अगर (ret) अणु
			prपूर्णांकk("%s: Create IBSS setting to 1 failed\n",
			       dev->name);
		पूर्ण
	पूर्ण

	अगर (local->name_set)
		(व्योम) hostap_set_string(dev, HFA384X_RID_CNFOWNNAME,
					 local->name);

	अगर (hostap_set_encryption(local)) अणु
		prपूर्णांकk(KERN_INFO "%s: could not configure encryption\n",
		       dev->name);
	पूर्ण

	(व्योम) hostap_set_antsel(local);

	अगर (hostap_set_roaming(local)) अणु
		prपूर्णांकk(KERN_INFO "%s: could not set host roaming\n",
		       dev->name);
	पूर्ण

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,6,3) &&
	    hostap_set_word(dev, HFA384X_RID_CNFENHSECURITY, local->enh_sec))
		prपूर्णांकk(KERN_INFO "%s: cnfEnhSecurity setting to 0x%x failed\n",
		       dev->name, local->enh_sec);

	/* 32-bit tallies were added in STA f/w 0.8.0, but they were apparently
	 * not working correctly (last seven counters report bogus values).
	 * This has been fixed in 0.8.2, so enable 32-bit tallies only
	 * beginning with that firmware version. Another bug fix क्रम 32-bit
	 * tallies in 1.4.0; should 16-bit tallies be used क्रम some other
	 * versions, too? */
	अगर (local->sta_fw_ver >= PRISM2_FW_VER(0,8,2)) अणु
		अगर (hostap_set_word(dev, HFA384X_RID_CNFTHIRTY2TALLY, 1)) अणु
			prपूर्णांकk(KERN_INFO "%s: cnfThirty2Tally setting "
			       "failed\n", dev->name);
			local->tallies32 = 0;
		पूर्ण अन्यथा
			local->tallies32 = 1;
	पूर्ण अन्यथा
		local->tallies32 = 0;

	hostap_set_auth_algs(local);

	अगर (hostap_set_word(dev, HFA384X_RID_FRAGMENTATIONTHRESHOLD,
			    local->fragm_threshold)) अणु
		prपूर्णांकk(KERN_INFO "%s: setting FragmentationThreshold to %d "
		       "failed\n", dev->name, local->fragm_threshold);
	पूर्ण

	अगर (hostap_set_word(dev, HFA384X_RID_RTSTHRESHOLD,
			    local->rts_threshold)) अणु
		prपूर्णांकk(KERN_INFO "%s: setting RTSThreshold to %d failed\n",
		       dev->name, local->rts_threshold);
	पूर्ण

	अगर (local->manual_retry_count >= 0 &&
	    hostap_set_word(dev, HFA384X_RID_CNFALTRETRYCOUNT,
			    local->manual_retry_count)) अणु
		prपूर्णांकk(KERN_INFO "%s: setting cnfAltRetryCount to %d failed\n",
		       dev->name, local->manual_retry_count);
	पूर्ण

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1) &&
	    hfa384x_get_rid(dev, HFA384X_RID_CNFDBMADJUST, &पंचांगp, 2, 1) == 2) अणु
		local->rssi_to_dBm = le16_to_cpu(पंचांगp);
	पूर्ण

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,7,0) && local->wpa &&
	    hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE, 1)) अणु
		prपूर्णांकk(KERN_INFO "%s: setting ssnHandlingMode to 1 failed\n",
		       dev->name);
	पूर्ण

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,7,0) && local->generic_elem &&
	    hfa384x_set_rid(dev, HFA384X_RID_GENERICELEMENT,
			    local->generic_elem, local->generic_elem_len)) अणु
		prपूर्णांकk(KERN_INFO "%s: setting genericElement failed\n",
		       dev->name);
	पूर्ण

 fail:
	वापस ret;
पूर्ण


अटल पूर्णांक prism2_hw_init(काष्ठा net_device *dev, पूर्णांक initial)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret, first = 1;
	अचिन्हित दीर्घ start, delay;

	PDEBUG(DEBUG_FLOW, "prism2_hw_init()\n");

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	clear_bit(HOSTAP_BITS_TRANSMIT, &local->bits);

 init:
	/* initialize HFA 384x */
	ret = hfa384x_cmd_no_रुको(dev, HFA384X_CMDCODE_INIT, 0);
	अगर (ret) अणु
		prपूर्णांकk(KERN_INFO "%s: first command failed - assuming card "
		       "does not have primary firmware\n", dev_info);
	पूर्ण

	अगर (first && (HFA384X_INW(HFA384X_EVSTAT_OFF) & HFA384X_EV_CMD)) अणु
		/* EvStat has Cmd bit set in some हालs, so retry once अगर no
		 * रुको was needed */
		HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_EVACK_OFF);
		prपूर्णांकk(KERN_DEBUG "%s: init command completed too quickly - "
		       "retrying\n", dev->name);
		first = 0;
		जाओ init;
	पूर्ण

	start = jअगरfies;
	delay = jअगरfies + HFA384X_INIT_TIMEOUT;
	जबतक (!(HFA384X_INW(HFA384X_EVSTAT_OFF) & HFA384X_EV_CMD) &&
	       समय_beक्रमe(jअगरfies, delay))
		yield();
	अगर (!(HFA384X_INW(HFA384X_EVSTAT_OFF) & HFA384X_EV_CMD)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: assuming no Primary image in "
		       "flash - card initialization not completed\n",
		       dev_info);
		local->no_pri = 1;
#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
			अगर (local->sram_type == -1)
				local->sram_type = prism2_get_ram_size(local);
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */
		वापस 1;
	पूर्ण
	local->no_pri = 0;
	prपूर्णांकk(KERN_DEBUG "prism2_hw_init: initialized in %lu ms\n",
	       (jअगरfies - start) * 1000 / HZ);
	HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_EVACK_OFF);
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_hw_init2(काष्ठा net_device *dev, पूर्णांक initial)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक i;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
	kमुक्त(local->pda);
	अगर (local->no_pri)
		local->pda = शून्य;
	अन्यथा
		local->pda = prism2_पढ़ो_pda(dev);
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */

	hfa384x_disable_पूर्णांकerrupts(dev);

#अगर_अघोषित final_version
	HFA384X_OUTW(HFA384X_MAGIC, HFA384X_SWSUPPORT0_OFF);
	अगर (HFA384X_INW(HFA384X_SWSUPPORT0_OFF) != HFA384X_MAGIC) अणु
		prपूर्णांकk("SWSUPPORT0 write/read failed: %04X != %04X\n",
		       HFA384X_INW(HFA384X_SWSUPPORT0_OFF), HFA384X_MAGIC);
		जाओ failed;
	पूर्ण
#पूर्ण_अगर

	अगर (initial || local->pri_only) अणु
		hfa384x_events_only_cmd(dev);
		/* get card version inक्रमmation */
		अगर (prism2_get_version_info(dev, HFA384X_RID_NICID, "NIC") ||
		    prism2_get_version_info(dev, HFA384X_RID_PRIID, "PRI")) अणु
			hfa384x_disable_पूर्णांकerrupts(dev);
			जाओ failed;
		पूर्ण

		अगर (prism2_get_version_info(dev, HFA384X_RID_STAID, "STA")) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Failed to read STA f/w version "
			       "- only Primary f/w present\n", dev->name);
			local->pri_only = 1;
			वापस 0;
		पूर्ण
		local->pri_only = 0;
		hfa384x_disable_पूर्णांकerrupts(dev);
	पूर्ण

	/* FIX: could convert allocate_fid to use sleeping CmdCompl रुको and
	 * enable पूर्णांकerrupts beक्रमe this. This would also require some sort of
	 * sleeping AllocEv रुकोing */

	/* allocate TX FIDs */
	local->txfid_len = PRISM2_TXFID_LEN;
	क्रम (i = 0; i < PRISM2_TXFID_COUNT; i++) अणु
		local->txfid[i] = hfa384x_allocate_fid(dev, local->txfid_len);
		अगर (local->txfid[i] == 0xffff && local->txfid_len > 1600) अणु
			local->txfid[i] = hfa384x_allocate_fid(dev, 1600);
			अगर (local->txfid[i] != 0xffff) अणु
				prपूर्णांकk(KERN_DEBUG "%s: Using shorter TX FID "
				       "(1600 bytes)\n", dev->name);
				local->txfid_len = 1600;
			पूर्ण
		पूर्ण
		अगर (local->txfid[i] == 0xffff)
			जाओ failed;
		local->पूर्णांकransmitfid[i] = PRISM2_TXFID_EMPTY;
	पूर्ण

	hfa384x_events_only_cmd(dev);

	अगर (initial) अणु
		काष्ठा list_head *ptr;
		prism2_check_sta_fw_version(local);

		अगर (hfa384x_get_rid(dev, HFA384X_RID_CNFOWNMACADDR,
				    dev->dev_addr, 6, 1) < 0) अणु
			prपूर्णांकk("%s: could not get own MAC address\n",
			       dev->name);
		पूर्ण
		list_क्रम_each(ptr, &local->hostap_पूर्णांकerfaces) अणु
			अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
			eth_hw_addr_inherit(अगरace->dev, dev);
		पूर्ण
	पूर्ण अन्यथा अगर (local->fw_ap)
		prism2_check_sta_fw_version(local);

	prism2_setup_rids(dev);

	/* MAC is now configured, but port 0 is not yet enabled */
	वापस 0;

 failed:
	अगर (!local->no_pri)
		prपूर्णांकk(KERN_WARNING "%s: Initialization failed\n", dev_info);
	वापस 1;
पूर्ण


अटल पूर्णांक prism2_hw_enable(काष्ठा net_device *dev, पूर्णांक initial)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक was_resetting;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	was_resetting = local->hw_resetting;

	अगर (hfa384x_cmd(dev, HFA384X_CMDCODE_ENABLE, 0, शून्य, शून्य)) अणु
		prपूर्णांकk("%s: MAC port 0 enabling failed\n", dev->name);
		वापस 1;
	पूर्ण

	local->hw_पढ़ोy = 1;
	local->hw_reset_tries = 0;
	local->hw_resetting = 0;
	hfa384x_enable_पूर्णांकerrupts(dev);

	/* at least D-Link DWL-650 seems to require additional port reset
	 * beक्रमe it starts acting as an AP, so reset port स्वतःmatically
	 * here just in हाल */
	अगर (initial && prism2_reset_port(dev)) अणु
		prपूर्णांकk("%s: MAC port 0 resetting failed\n", dev->name);
		वापस 1;
	पूर्ण

	अगर (was_resetting && netअगर_queue_stopped(dev)) अणु
		/* If hw_reset() was called during pending transmit, netअगर
		 * queue was stopped. Wake it up now since the wlan card has
		 * been resetted. */
		netअगर_wake_queue(dev);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_hw_config(काष्ठा net_device *dev, पूर्णांक initial)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->hw_करोwnloading)
		वापस 1;

	अगर (prism2_hw_init(dev, initial)) अणु
		वापस local->no_pri ? 0 : 1;
	पूर्ण

	अगर (prism2_hw_init2(dev, initial))
		वापस 1;

	/* Enable firmware अगर secondary image is loaded and at least one of the
	 * netdevices is up. */
	अगर (!local->pri_only &&
	    (initial == 0 || (initial == 2 && local->num_dev_खोलो > 0))) अणु
		अगर (!local->dev_enabled)
			prism2_callback(local, PRISM2_CALLBACK_ENABLE);
		local->dev_enabled = 1;
		वापस prism2_hw_enable(dev, initial);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम prism2_hw_shutकरोwn(काष्ठा net_device *dev, पूर्णांक no_disable)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Allow only command completion events during disable */
	hfa384x_events_only_cmd(dev);

	local->hw_पढ़ोy = 0;
	अगर (local->dev_enabled)
		prism2_callback(local, PRISM2_CALLBACK_DISABLE);
	local->dev_enabled = 0;

	अगर (local->func->card_present && !local->func->card_present(local)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: card already removed or not configured "
		       "during shutdown\n", dev->name);
		वापस;
	पूर्ण

	अगर ((no_disable & HOSTAP_HW_NO_DISABLE) == 0 &&
	    hfa384x_cmd(dev, HFA384X_CMDCODE_DISABLE, 0, शून्य, शून्य))
		prपूर्णांकk(KERN_WARNING "%s: Shutdown failed\n", dev_info);

	hfa384x_disable_पूर्णांकerrupts(dev);

	अगर (no_disable & HOSTAP_HW_ENABLE_CMDCOMPL)
		hfa384x_events_only_cmd(dev);
	अन्यथा
		prism2_clear_cmd_queue(local);
पूर्ण


अटल व्योम prism2_hw_reset(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

#अगर 0
	अटल दीर्घ last_reset = 0;

	/* करो not reset card more than once per second to aव्योम ending up in a
	 * busy loop resetting the card */
	अगर (समय_beक्रमe_eq(jअगरfies, last_reset + HZ))
		वापस;
	last_reset = jअगरfies;
#पूर्ण_अगर

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->hw_करोwnloading)
		वापस;

	अगर (local->hw_resetting) अणु
		prपूर्णांकk(KERN_WARNING "%s: %s: already resetting card - "
		       "ignoring reset request\n", dev_info, dev->name);
		वापस;
	पूर्ण

	local->hw_reset_tries++;
	अगर (local->hw_reset_tries > 10) अणु
		prपूर्णांकk(KERN_WARNING "%s: too many reset tries, skipping\n",
		       dev->name);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_WARNING "%s: %s: resetting card\n", dev_info, dev->name);
	hfa384x_disable_पूर्णांकerrupts(dev);
	local->hw_resetting = 1;
	अगर (local->func->cor_sreset) अणु
		/* Host प्रणाली seems to hang in some हालs with high traffic
		 * load or shared पूर्णांकerrupts during COR sreset. Disable shared
		 * पूर्णांकerrupts during reset to aव्योम these crashes. COS sreset
		 * takes quite a दीर्घ समय, so it is unक्रमtunate that this
		 * seems to be needed. Anyway, I करो not know of any better way
		 * of aव्योमing the crash. */
		disable_irq(dev->irq);
		local->func->cor_sreset(local);
		enable_irq(dev->irq);
	पूर्ण
	prism2_hw_shutकरोwn(dev, 1);
	prism2_hw_config(dev, 0);
	local->hw_resetting = 0;

#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
	अगर (local->dl_pri) अणु
		prपूर्णांकk(KERN_DEBUG "%s: persistent download of primary "
		       "firmware\n", dev->name);
		अगर (prism2_करोwnload_genesis(local, local->dl_pri) < 0)
			prपूर्णांकk(KERN_WARNING "%s: download (PRI) failed\n",
			       dev->name);
	पूर्ण

	अगर (local->dl_sec) अणु
		prपूर्णांकk(KERN_DEBUG "%s: persistent download of secondary "
		       "firmware\n", dev->name);
		अगर (prism2_करोwnload_अस्थिर(local, local->dl_sec) < 0)
			prपूर्णांकk(KERN_WARNING "%s: download (SEC) failed\n",
			       dev->name);
	पूर्ण
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */

	/* TODO: restore beacon TIM bits क्रम STAs that have buffered frames */
पूर्ण


अटल व्योम prism2_schedule_reset(local_info_t *local)
अणु
	schedule_work(&local->reset_queue);
पूर्ण


/* Called only as scheduled task after noticing card समयout in पूर्णांकerrupt
 * context */
अटल व्योम handle_reset_queue(काष्ठा work_काष्ठा *work)
अणु
	local_info_t *local = container_of(work, local_info_t, reset_queue);

	prपूर्णांकk(KERN_DEBUG "%s: scheduled card reset\n", local->dev->name);
	prism2_hw_reset(local->dev);

	अगर (netअगर_queue_stopped(local->dev)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PRISM2_TXFID_COUNT; i++)
			अगर (local->पूर्णांकransmitfid[i] == PRISM2_TXFID_EMPTY) अणु
				PDEBUG(DEBUG_EXTRA, "prism2_tx_timeout: "
				       "wake up queue\n");
				netअगर_wake_queue(local->dev);
				अवरोध;
			पूर्ण
	पूर्ण
पूर्ण


अटल पूर्णांक prism2_get_txfid_idx(local_info_t *local)
अणु
	पूर्णांक idx, end;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&local->txfidlock, flags);
	end = idx = local->next_txfid;
	करो अणु
		अगर (local->पूर्णांकransmitfid[idx] == PRISM2_TXFID_EMPTY) अणु
			local->पूर्णांकransmitfid[idx] = PRISM2_TXFID_RESERVED;
			spin_unlock_irqrestore(&local->txfidlock, flags);
			वापस idx;
		पूर्ण
		idx++;
		अगर (idx >= PRISM2_TXFID_COUNT)
			idx = 0;
	पूर्ण जबतक (idx != end);
	spin_unlock_irqrestore(&local->txfidlock, flags);

	PDEBUG(DEBUG_EXTRA2, "prism2_get_txfid_idx: no room in txfid buf: "
	       "packet dropped\n");
	local->dev->stats.tx_dropped++;

	वापस -1;
पूर्ण


/* Called only from hardware IRQ */
अटल व्योम prism2_transmit_cb(काष्ठा net_device *dev, दीर्घ context,
			       u16 resp0, u16 res)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक idx = (पूर्णांक) context;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: prism2_transmit_cb - res=0x%02x\n",
		       dev->name, res);
		वापस;
	पूर्ण

	अगर (idx < 0 || idx >= PRISM2_TXFID_COUNT) अणु
		prपूर्णांकk(KERN_DEBUG "%s: prism2_transmit_cb called with invalid "
		       "idx=%d\n", dev->name, idx);
		वापस;
	पूर्ण

	अगर (!test_and_clear_bit(HOSTAP_BITS_TRANSMIT, &local->bits)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: driver bug: prism2_transmit_cb called "
		       "with no pending transmit\n", dev->name);
	पूर्ण

	अगर (netअगर_queue_stopped(dev)) अणु
		/* पढ़ोy क्रम next TX, so wake up queue that was stopped in
		 * prism2_transmit() */
		netअगर_wake_queue(dev);
	पूर्ण

	spin_lock(&local->txfidlock);

	/* With reclaim, Resp0 contains new txfid क्रम transmit; the old txfid
	 * will be स्वतःmatically allocated क्रम the next TX frame */
	local->पूर्णांकransmitfid[idx] = resp0;

	PDEBUG(DEBUG_FID, "%s: prism2_transmit_cb: txfid[%d]=0x%04x, "
	       "resp0=0x%04x, transmit_txfid=0x%04x\n",
	       dev->name, idx, local->txfid[idx],
	       resp0, local->पूर्णांकransmitfid[local->next_txfid]);

	idx++;
	अगर (idx >= PRISM2_TXFID_COUNT)
		idx = 0;
	local->next_txfid = idx;

	/* check अगर all TX buffers are occupied */
	करो अणु
		अगर (local->पूर्णांकransmitfid[idx] == PRISM2_TXFID_EMPTY) अणु
			spin_unlock(&local->txfidlock);
			वापस;
		पूर्ण
		idx++;
		अगर (idx >= PRISM2_TXFID_COUNT)
			idx = 0;
	पूर्ण जबतक (idx != local->next_txfid);
	spin_unlock(&local->txfidlock);

	/* no empty TX buffers, stop queue */
	netअगर_stop_queue(dev);
पूर्ण


/* Called only from software IRQ अगर PCI bus master is not used (with bus master
 * this can be called both from software and hardware IRQ) */
अटल पूर्णांक prism2_transmit(काष्ठा net_device *dev, पूर्णांक idx)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक res;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* The driver tries to stop netअगर queue so that there would not be
	 * more than one attempt to transmit frames going on; check that this
	 * is really the हाल */

	अगर (test_and_set_bit(HOSTAP_BITS_TRANSMIT, &local->bits)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: driver bug - prism2_transmit() called "
		       "when previous TX was pending\n", dev->name);
		वापस -1;
	पूर्ण

	/* stop the queue क्रम the समय that transmit is pending */
	netअगर_stop_queue(dev);

	/* transmit packet */
	res = hfa384x_cmd_callback(
		dev,
		HFA384X_CMDCODE_TRANSMIT | HFA384X_CMD_TX_RECLAIM,
		local->txfid[idx],
		prism2_transmit_cb, (दीर्घ) idx);

	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: prism2_transmit: CMDCODE_TRANSMIT "
		       "failed (res=%d)\n", dev->name, res);
		dev->stats.tx_dropped++;
		netअगर_wake_queue(dev);
		वापस -1;
	पूर्ण
	netअगर_trans_update(dev);

	/* Since we did not रुको क्रम command completion, the card जारीs
	 * to process on the background and we will finish handling when
	 * command completion event is handled (prism2_cmd_ev() function) */

	वापस 0;
पूर्ण


/* Send IEEE 802.11 frame (convert the header पूर्णांकo Prism2 TX descriptor and
 * send the payload with this descriptor) */
/* Called only from software IRQ */
अटल पूर्णांक prism2_tx_80211(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hfa384x_tx_frame txdesc;
	काष्ठा hostap_skb_tx_data *meta;
	पूर्णांक hdr_len, data_len, idx, res, ret = -1;
	u16 tx_control;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;

	prism2_callback(local, PRISM2_CALLBACK_TX_START);

	अगर ((local->func->card_present && !local->func->card_present(local)) ||
	    !local->hw_पढ़ोy || local->hw_करोwnloading || local->pri_only) अणु
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: prism2_tx_80211: hw not ready -"
			       " skipping\n", dev->name);
		पूर्ण
		जाओ fail;
	पूर्ण

	स_रखो(&txdesc, 0, माप(txdesc));

	/* skb->data starts with txdesc->frame_control */
	hdr_len = 24;
	skb_copy_from_linear_data(skb, &txdesc.frame_control, hdr_len);
	अगर (ieee80211_is_data(txdesc.frame_control) &&
	    ieee80211_has_a4(txdesc.frame_control) &&
	    skb->len >= 30) अणु
		/* Addr4 */
		skb_copy_from_linear_data_offset(skb, hdr_len, txdesc.addr4,
						 ETH_ALEN);
		hdr_len += ETH_ALEN;
	पूर्ण

	tx_control = local->tx_control;
	अगर (meta->tx_cb_idx) अणु
		tx_control |= HFA384X_TX_CTRL_TX_OK;
		txdesc.sw_support = cpu_to_le32(meta->tx_cb_idx);
	पूर्ण
	txdesc.tx_control = cpu_to_le16(tx_control);
	txdesc.tx_rate = meta->rate;

	data_len = skb->len - hdr_len;
	txdesc.data_len = cpu_to_le16(data_len);
	txdesc.len = cpu_to_be16(data_len);

	idx = prism2_get_txfid_idx(local);
	अगर (idx < 0)
		जाओ fail;

	अगर (local->frame_dump & PRISM2_DUMP_TX_HDR)
		hostap_dump_tx_header(dev->name, &txdesc);

	spin_lock(&local->baplock);
	res = hfa384x_setup_bap(dev, BAP0, local->txfid[idx], 0);

	अगर (!res)
		res = hfa384x_to_bap(dev, BAP0, &txdesc, माप(txdesc));
	अगर (!res)
		res = hfa384x_to_bap(dev, BAP0, skb->data + hdr_len,
				     skb->len - hdr_len);
	spin_unlock(&local->baplock);

	अगर (!res)
		res = prism2_transmit(dev, idx);
	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: prism2_tx_80211 - to BAP0 failed\n",
		       dev->name);
		local->पूर्णांकransmitfid[idx] = PRISM2_TXFID_EMPTY;
		schedule_work(&local->reset_queue);
		जाओ fail;
	पूर्ण

	ret = 0;

fail:
	prism2_callback(local, PRISM2_CALLBACK_TX_END);
	वापस ret;
पूर्ण


/* Some SMP प्रणालीs have reported number of odd errors with hostap_pci. fid
 * रेजिस्टर has changed values between consecutive पढ़ोs क्रम an unknown reason.
 * This should really not happen, so more debugging is needed. This test
 * version is a bit slower, but it will detect most of such रेजिस्टर changes
 * and will try to get the correct fid eventually. */
#घोषणा EXTRA_FID_READ_TESTS

अटल u16 prism2_पढ़ो_fid_reg(काष्ठा net_device *dev, u16 reg)
अणु
#अगर_घोषित EXTRA_FID_READ_TESTS
	u16 val, val2, val3;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		val = HFA384X_INW(reg);
		val2 = HFA384X_INW(reg);
		val3 = HFA384X_INW(reg);

		अगर (val == val2 && val == val3)
			वापस val;

		prपूर्णांकk(KERN_DEBUG "%s: detected fid change (try=%d, reg=%04x):"
		       " %04x %04x %04x\n",
		       dev->name, i, reg, val, val2, val3);
		अगर ((val == val2 || val == val3) && val != 0)
			वापस val;
		अगर (val2 == val3 && val2 != 0)
			वापस val2;
	पूर्ण
	prपूर्णांकk(KERN_WARNING "%s: Uhhuh.. could not read good fid from reg "
	       "%04x (%04x %04x %04x)\n", dev->name, reg, val, val2, val3);
	वापस val;
#अन्यथा /* EXTRA_FID_READ_TESTS */
	वापस HFA384X_INW(reg);
#पूर्ण_अगर /* EXTRA_FID_READ_TESTS */
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_rx(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->dev;
	पूर्णांक res, rx_pending = 0;
	u16 len, hdr_len, rxfid, status, macport;
	काष्ठा hfa384x_rx_frame rxdesc;
	काष्ठा sk_buff *skb = शून्य;

	prism2_callback(local, PRISM2_CALLBACK_RX_START);

	rxfid = prism2_पढ़ो_fid_reg(dev, HFA384X_RXFID_OFF);
#अगर_अघोषित final_version
	अगर (rxfid == 0) अणु
		rxfid = HFA384X_INW(HFA384X_RXFID_OFF);
		prपूर्णांकk(KERN_DEBUG "prism2_rx: rxfid=0 (next 0x%04x)\n",
		       rxfid);
		अगर (rxfid == 0) अणु
			schedule_work(&local->reset_queue);
			जाओ rx_dropped;
		पूर्ण
		/* try to जारी with the new rxfid value */
	पूर्ण
#पूर्ण_अगर

	spin_lock(&local->baplock);
	res = hfa384x_setup_bap(dev, BAP0, rxfid, 0);
	अगर (!res)
		res = hfa384x_from_bap(dev, BAP0, &rxdesc, माप(rxdesc));

	अगर (res) अणु
		spin_unlock(&local->baplock);
		prपूर्णांकk(KERN_DEBUG "%s: copy from BAP0 failed %d\n", dev->name,
		       res);
		अगर (res == -ETIMEDOUT) अणु
			schedule_work(&local->reset_queue);
		पूर्ण
		जाओ rx_dropped;
	पूर्ण

	len = le16_to_cpu(rxdesc.data_len);
	hdr_len = माप(rxdesc);
	status = le16_to_cpu(rxdesc.status);
	macport = (status >> 8) & 0x07;

	/* Drop frames with too large reported payload length. Monitor mode
	 * seems to someबार pass frames (e.g., ctrl::ack) with चिन्हित and
	 * negative value, so allow also values 65522 .. 65534 (-14 .. -2) क्रम
	 * macport 7 */
	अगर (len > PRISM2_DATA_MAXLEN + 8 /* WEP */) अणु
		अगर (macport == 7 && local->iw_mode == IW_MODE_MONITOR) अणु
			अगर (len >= (u16) -14) अणु
				hdr_len -= 65535 - len;
				hdr_len--;
			पूर्ण
			len = 0;
		पूर्ण अन्यथा अणु
			spin_unlock(&local->baplock);
			prपूर्णांकk(KERN_DEBUG "%s: Received frame with invalid "
			       "length 0x%04x\n", dev->name, len);
			hostap_dump_rx_header(dev->name, &rxdesc);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

	skb = dev_alloc_skb(len + hdr_len);
	अगर (!skb) अणु
		spin_unlock(&local->baplock);
		prपूर्णांकk(KERN_DEBUG "%s: RX failed to allocate skb\n",
		       dev->name);
		जाओ rx_dropped;
	पूर्ण
	skb->dev = dev;
	skb_put_data(skb, &rxdesc, hdr_len);

	अगर (len > 0)
		res = hfa384x_from_bap(dev, BAP0, skb_put(skb, len), len);
	spin_unlock(&local->baplock);
	अगर (res) अणु
		prपूर्णांकk(KERN_DEBUG "%s: RX failed to read "
		       "frame data\n", dev->name);
		जाओ rx_dropped;
	पूर्ण

	skb_queue_tail(&local->rx_list, skb);
	tasklet_schedule(&local->rx_tasklet);

 rx_निकास:
	prism2_callback(local, PRISM2_CALLBACK_RX_END);
	अगर (!rx_pending) अणु
		HFA384X_OUTW(HFA384X_EV_RX, HFA384X_EVACK_OFF);
	पूर्ण

	वापस;

 rx_dropped:
	dev->stats.rx_dropped++;
	अगर (skb)
		dev_kमुक्त_skb(skb);
	जाओ rx_निकास;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_rx_skb(local_info_t *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा hfa384x_rx_frame *rxdesc;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा hostap_80211_rx_status stats;
	पूर्णांक hdrlen, rx_hdrlen;

	rx_hdrlen = माप(*rxdesc);
	अगर (skb->len < माप(*rxdesc)) अणु
		/* Allow monitor mode to receive लघुer frames */
		अगर (local->iw_mode == IW_MODE_MONITOR &&
		    skb->len >= माप(*rxdesc) - 30) अणु
			rx_hdrlen = skb->len;
		पूर्ण अन्यथा अणु
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	rxdesc = (काष्ठा hfa384x_rx_frame *) skb->data;

	अगर (local->frame_dump & PRISM2_DUMP_RX_HDR &&
	    skb->len >= माप(*rxdesc))
		hostap_dump_rx_header(dev->name, rxdesc);

	अगर (le16_to_cpu(rxdesc->status) & HFA384X_RX_STATUS_FCSERR &&
	    (!local->monitor_allow_fcserr ||
	     local->iw_mode != IW_MODE_MONITOR))
		जाओ drop;

	अगर (skb->len > PRISM2_DATA_MAXLEN) अणु
		prपूर्णांकk(KERN_DEBUG "%s: RX: len(%d) > MAX(%d)\n",
		       dev->name, skb->len, PRISM2_DATA_MAXLEN);
		जाओ drop;
	पूर्ण

	stats.mac_समय = le32_to_cpu(rxdesc->समय);
	stats.संकेत = rxdesc->संकेत - local->rssi_to_dBm;
	stats.noise = rxdesc->silence - local->rssi_to_dBm;
	stats.rate = rxdesc->rate;

	/* Convert Prism2 RX काष्ठाure पूर्णांकo IEEE 802.11 header */
	hdrlen = hostap_80211_get_hdrlen(rxdesc->frame_control);
	अगर (hdrlen > rx_hdrlen)
		hdrlen = rx_hdrlen;

	स_हटाओ(skb_pull(skb, rx_hdrlen - hdrlen),
		&rxdesc->frame_control, hdrlen);

	hostap_80211_rx(dev, skb, &stats);
	वापस;

 drop:
	dev_kमुक्त_skb(skb);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	local_info_t *local = from_tasklet(local, t, rx_tasklet);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&local->rx_list)) != शून्य)
		hostap_rx_skb(local, skb);
पूर्ण


/* Called only from hardware IRQ */
अटल व्योम prism2_alloc_ev(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक idx;
	u16 fid;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	fid = prism2_पढ़ो_fid_reg(dev, HFA384X_ALLOCFID_OFF);

	PDEBUG(DEBUG_FID, "FID: interrupt: ALLOC - fid=0x%04x\n", fid);

	spin_lock(&local->txfidlock);
	idx = local->next_alloc;

	करो अणु
		अगर (local->txfid[idx] == fid) अणु
			PDEBUG(DEBUG_FID, "FID: found matching txfid[%d]\n",
			       idx);

#अगर_अघोषित final_version
			अगर (local->पूर्णांकransmitfid[idx] == PRISM2_TXFID_EMPTY)
				prपूर्णांकk("Already released txfid found at idx "
				       "%d\n", idx);
			अगर (local->पूर्णांकransmitfid[idx] == PRISM2_TXFID_RESERVED)
				prपूर्णांकk("Already reserved txfid found at idx "
				       "%d\n", idx);
#पूर्ण_अगर
			local->पूर्णांकransmitfid[idx] = PRISM2_TXFID_EMPTY;
			idx++;
			local->next_alloc = idx >= PRISM2_TXFID_COUNT ? 0 :
				idx;

			अगर (!test_bit(HOSTAP_BITS_TRANSMIT, &local->bits) &&
			    netअगर_queue_stopped(dev))
				netअगर_wake_queue(dev);

			spin_unlock(&local->txfidlock);
			वापस;
		पूर्ण

		idx++;
		अगर (idx >= PRISM2_TXFID_COUNT)
			idx = 0;
	पूर्ण जबतक (idx != local->next_alloc);

	prपूर्णांकk(KERN_WARNING "%s: could not find matching txfid (0x%04x, new "
	       "read 0x%04x) for alloc event\n", dev->name, fid,
	       HFA384X_INW(HFA384X_ALLOCFID_OFF));
	prपूर्णांकk(KERN_DEBUG "TXFIDs:");
	क्रम (idx = 0; idx < PRISM2_TXFID_COUNT; idx++)
		prपूर्णांकk(" %04x[%04x]", local->txfid[idx],
		       local->पूर्णांकransmitfid[idx]);
	prपूर्णांकk("\n");
	spin_unlock(&local->txfidlock);

	/* FIX: should probably schedule reset; reference to one txfid was lost
	 * completely.. Bad things will happen अगर we run out of txfids
	 * Actually, this will cause netdev watchकरोg to notice TX समयout and
	 * then card reset after all txfids have been leaked. */
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_tx_callback(local_info_t *local,
			       काष्ठा hfa384x_tx_frame *txdesc, पूर्णांक ok,
			       अक्षर *payload)
अणु
	u16 sw_support, hdrlen, len;
	काष्ठा sk_buff *skb;
	काष्ठा hostap_tx_callback_info *cb;

	/* Make sure that frame was from us. */
	अगर (!ether_addr_equal(txdesc->addr2, local->dev->dev_addr)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: TX callback - foreign frame\n",
		       local->dev->name);
		वापस;
	पूर्ण

	sw_support = le32_to_cpu(txdesc->sw_support);

	spin_lock(&local->lock);
	cb = local->tx_callback;
	जबतक (cb != शून्य && cb->idx != sw_support)
		cb = cb->next;
	spin_unlock(&local->lock);

	अगर (cb == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: could not find TX callback (idx %d)\n",
		       local->dev->name, sw_support);
		वापस;
	पूर्ण

	hdrlen = hostap_80211_get_hdrlen(txdesc->frame_control);
	len = le16_to_cpu(txdesc->data_len);
	skb = dev_alloc_skb(hdrlen + len);
	अगर (skb == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_tx_callback failed to allocate "
		       "skb\n", local->dev->name);
		वापस;
	पूर्ण

	skb_put_data(skb, (व्योम *)&txdesc->frame_control, hdrlen);
	अगर (payload)
		skb_put_data(skb, payload, len);

	skb->dev = local->dev;
	skb_reset_mac_header(skb);

	cb->func(skb, ok, cb->data);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक hostap_tx_compl_पढ़ो(local_info_t *local, पूर्णांक error,
				काष्ठा hfa384x_tx_frame *txdesc,
				अक्षर **payload)
अणु
	u16 fid, len;
	पूर्णांक res, ret = 0;
	काष्ठा net_device *dev = local->dev;

	fid = prism2_पढ़ो_fid_reg(dev, HFA384X_TXCOMPLFID_OFF);

	PDEBUG(DEBUG_FID, "interrupt: TX (err=%d) - fid=0x%04x\n", fid, error);

	spin_lock(&local->baplock);
	res = hfa384x_setup_bap(dev, BAP0, fid, 0);
	अगर (!res)
		res = hfa384x_from_bap(dev, BAP0, txdesc, माप(*txdesc));
	अगर (res) अणु
		PDEBUG(DEBUG_EXTRA, "%s: TX (err=%d) - fid=0x%04x - could not "
		       "read txdesc\n", dev->name, error, fid);
		अगर (res == -ETIMEDOUT) अणु
			schedule_work(&local->reset_queue);
		पूर्ण
		ret = -1;
		जाओ fail;
	पूर्ण
	अगर (txdesc->sw_support) अणु
		len = le16_to_cpu(txdesc->data_len);
		अगर (len < PRISM2_DATA_MAXLEN) अणु
			*payload = kदो_स्मृति(len, GFP_ATOMIC);
			अगर (*payload == शून्य ||
			    hfa384x_from_bap(dev, BAP0, *payload, len)) अणु
				PDEBUG(DEBUG_EXTRA, "%s: could not read TX "
				       "frame payload\n", dev->name);
				kमुक्त(*payload);
				*payload = शून्य;
				ret = -1;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

 fail:
	spin_unlock(&local->baplock);

	वापस ret;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_tx_ev(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->dev;
	अक्षर *payload = शून्य;
	काष्ठा hfa384x_tx_frame txdesc;

	अगर (hostap_tx_compl_पढ़ो(local, 0, &txdesc, &payload))
		जाओ fail;

	अगर (local->frame_dump & PRISM2_DUMP_TX_HDR) अणु
		PDEBUG(DEBUG_EXTRA, "%s: TX - status=0x%04x "
		       "retry_count=%d tx_rate=%d seq_ctrl=%d "
		       "duration_id=%d\n",
		       dev->name, le16_to_cpu(txdesc.status),
		       txdesc.retry_count, txdesc.tx_rate,
		       le16_to_cpu(txdesc.seq_ctrl),
		       le16_to_cpu(txdesc.duration_id));
	पूर्ण

	अगर (txdesc.sw_support)
		hostap_tx_callback(local, &txdesc, 1, payload);
	kमुक्त(payload);

 fail:
	HFA384X_OUTW(HFA384X_EV_TX, HFA384X_EVACK_OFF);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_sta_tx_exc_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	local_info_t *local = from_tasklet(local, t, sta_tx_exc_tasklet);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&local->sta_tx_exc_list)) != शून्य) अणु
		काष्ठा hfa384x_tx_frame *txdesc =
			(काष्ठा hfa384x_tx_frame *) skb->data;

		अगर (skb->len >= माप(*txdesc)) अणु
			/* Convert Prism2 RX काष्ठाure पूर्णांकo IEEE 802.11 header
			 */
			पूर्णांक hdrlen = hostap_80211_get_hdrlen(txdesc->frame_control);
			स_हटाओ(skb_pull(skb, माप(*txdesc) - hdrlen),
				&txdesc->frame_control, hdrlen);

			hostap_handle_sta_tx_exc(local, skb);
		पूर्ण
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_txexc(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->dev;
	u16 status, fc;
	पूर्णांक show_dump, res;
	अक्षर *payload = शून्य;
	काष्ठा hfa384x_tx_frame txdesc;

	show_dump = local->frame_dump & PRISM2_DUMP_TXEXC_HDR;
	dev->stats.tx_errors++;

	res = hostap_tx_compl_पढ़ो(local, 1, &txdesc, &payload);
	HFA384X_OUTW(HFA384X_EV_TXEXC, HFA384X_EVACK_OFF);
	अगर (res)
		वापस;

	status = le16_to_cpu(txdesc.status);

	/* We produce a TXDROP event only क्रम retry or lअगरeसमय
	 * exceeded, because that's the only status that really mean
	 * that this particular node went away.
	 * Other errors means that *we* screwed up. - Jean II */
	अगर (status & (HFA384X_TX_STATUS_RETRYERR | HFA384X_TX_STATUS_AGEDERR))
	अणु
		जोड़ iwreq_data wrqu;

		/* Copy 802.11 dest address. */
		स_नकल(wrqu.addr.sa_data, txdesc.addr1, ETH_ALEN);
		wrqu.addr.sa_family = ARPHRD_ETHER;
		wireless_send_event(dev, IWEVTXDROP, &wrqu, शून्य);
	पूर्ण अन्यथा
		show_dump = 1;

	अगर (local->iw_mode == IW_MODE_MASTER ||
	    local->iw_mode == IW_MODE_REPEAT ||
	    local->wds_type & HOSTAP_WDS_AP_CLIENT) अणु
		काष्ठा sk_buff *skb;
		skb = dev_alloc_skb(माप(txdesc));
		अगर (skb) अणु
			skb_put_data(skb, &txdesc, माप(txdesc));
			skb_queue_tail(&local->sta_tx_exc_list, skb);
			tasklet_schedule(&local->sta_tx_exc_tasklet);
		पूर्ण
	पूर्ण

	अगर (txdesc.sw_support)
		hostap_tx_callback(local, &txdesc, 0, payload);
	kमुक्त(payload);

	अगर (!show_dump)
		वापस;

	PDEBUG(DEBUG_EXTRA, "%s: TXEXC - status=0x%04x (%s%s%s%s)"
	       " tx_control=%04x\n",
	       dev->name, status,
	       status & HFA384X_TX_STATUS_RETRYERR ? "[RetryErr]" : "",
	       status & HFA384X_TX_STATUS_AGEDERR ? "[AgedErr]" : "",
	       status & HFA384X_TX_STATUS_DISCON ? "[Discon]" : "",
	       status & HFA384X_TX_STATUS_FORMERR ? "[FormErr]" : "",
	       le16_to_cpu(txdesc.tx_control));

	fc = le16_to_cpu(txdesc.frame_control);
	PDEBUG(DEBUG_EXTRA, "   retry_count=%d tx_rate=%d fc=0x%04x "
	       "(%s%s%s::%d%s%s)\n",
	       txdesc.retry_count, txdesc.tx_rate, fc,
	       ieee80211_is_mgmt(txdesc.frame_control) ? "Mgmt" : "",
	       ieee80211_is_ctl(txdesc.frame_control) ? "Ctrl" : "",
	       ieee80211_is_data(txdesc.frame_control) ? "Data" : "",
	       (fc & IEEE80211_FCTL_STYPE) >> 4,
	       ieee80211_has_tods(txdesc.frame_control) ? " ToDS" : "",
	       ieee80211_has_fromds(txdesc.frame_control) ? " FromDS" : "");
	PDEBUG(DEBUG_EXTRA, "   A1=%pM A2=%pM A3=%pM A4=%pM\n",
	       txdesc.addr1, txdesc.addr2,
	       txdesc.addr3, txdesc.addr4);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_info_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	local_info_t *local = from_tasklet(local, t, info_tasklet);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&local->info_list)) != शून्य) अणु
		hostap_info_process(local, skb);
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम prism2_info(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->dev;
	u16 fid;
	पूर्णांक res, left;
	काष्ठा hfa384x_info_frame info;
	काष्ठा sk_buff *skb;

	fid = HFA384X_INW(HFA384X_INFOFID_OFF);

	spin_lock(&local->baplock);
	res = hfa384x_setup_bap(dev, BAP0, fid, 0);
	अगर (!res)
		res = hfa384x_from_bap(dev, BAP0, &info, माप(info));
	अगर (res) अणु
		spin_unlock(&local->baplock);
		prपूर्णांकk(KERN_DEBUG "Could not get info frame (fid=0x%04x)\n",
		       fid);
		अगर (res == -ETIMEDOUT) अणु
			schedule_work(&local->reset_queue);
		पूर्ण
		जाओ out;
	पूर्ण

	left = (le16_to_cpu(info.len) - 1) * 2;

	अगर (info.len & cpu_to_le16(0x8000) || info.len == 0 || left > 2060) अणु
		/* data रेजिस्टर seems to give 0x8000 in some error हालs even
		 * though busy bit is not set in offset रेजिस्टर;
		 * in addition, length must be at least 1 due to type field */
		spin_unlock(&local->baplock);
		prपूर्णांकk(KERN_DEBUG "%s: Received info frame with invalid "
		       "length 0x%04x (type 0x%04x)\n", dev->name,
		       le16_to_cpu(info.len), le16_to_cpu(info.type));
		जाओ out;
	पूर्ण

	skb = dev_alloc_skb(माप(info) + left);
	अगर (skb == शून्य) अणु
		spin_unlock(&local->baplock);
		prपूर्णांकk(KERN_DEBUG "%s: Could not allocate skb for info "
		       "frame\n", dev->name);
		जाओ out;
	पूर्ण

	skb_put_data(skb, &info, माप(info));
	अगर (left > 0 && hfa384x_from_bap(dev, BAP0, skb_put(skb, left), left))
	अणु
		spin_unlock(&local->baplock);
		prपूर्णांकk(KERN_WARNING "%s: Info frame read failed (fid=0x%04x, "
		       "len=0x%04x, type=0x%04x\n", dev->name, fid,
		       le16_to_cpu(info.len), le16_to_cpu(info.type));
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण
	spin_unlock(&local->baplock);

	skb_queue_tail(&local->info_list, skb);
	tasklet_schedule(&local->info_tasklet);

 out:
	HFA384X_OUTW(HFA384X_EV_INFO, HFA384X_EVACK_OFF);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम hostap_bap_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	local_info_t *local = from_tasklet(local, t, bap_tasklet);
	काष्ठा net_device *dev = local->dev;
	u16 ev;
	पूर्णांक frames = 30;

	अगर (local->func->card_present && !local->func->card_present(local))
		वापस;

	set_bit(HOSTAP_BITS_BAP_TASKLET, &local->bits);

	/* Process all pending BAP events without generating new पूर्णांकerrupts
	 * क्रम them */
	जबतक (frames-- > 0) अणु
		ev = HFA384X_INW(HFA384X_EVSTAT_OFF);
		अगर (ev == 0xffff || !(ev & HFA384X_BAP0_EVENTS))
			अवरोध;
		अगर (ev & HFA384X_EV_RX)
			prism2_rx(local);
		अगर (ev & HFA384X_EV_INFO)
			prism2_info(local);
		अगर (ev & HFA384X_EV_TX)
			prism2_tx_ev(local);
		अगर (ev & HFA384X_EV_TXEXC)
			prism2_txexc(local);
	पूर्ण

	set_bit(HOSTAP_BITS_BAP_TASKLET2, &local->bits);
	clear_bit(HOSTAP_BITS_BAP_TASKLET, &local->bits);

	/* Enable पूर्णांकerrupts क्रम new BAP events */
	hfa384x_events_all(dev);
	clear_bit(HOSTAP_BITS_BAP_TASKLET2, &local->bits);
पूर्ण


/* Called only from hardware IRQ */
अटल व्योम prism2_infdrop(काष्ठा net_device *dev)
अणु
	अटल अचिन्हित दीर्घ last_inquire = 0;

	PDEBUG(DEBUG_EXTRA, "%s: INFDROP event\n", dev->name);

	/* some firmware versions seem to get stuck with
	 * full CommTallies in high traffic load हालs; every
	 * packet will then cause INFDROP event and CommTallies
	 * info frame will not be sent स्वतःmatically. Try to
	 * get out of this state by inquiring CommTallies. */
	अगर (!last_inquire || समय_after(jअगरfies, last_inquire + HZ)) अणु
		hfa384x_cmd_callback(dev, HFA384X_CMDCODE_INQUIRE,
				     HFA384X_INFO_COMMTALLIES, शून्य, 0);
		last_inquire = jअगरfies;
	पूर्ण
पूर्ण


/* Called only from hardware IRQ */
अटल व्योम prism2_ev_tick(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u16 evstat, पूर्णांकen;
	अटल पूर्णांक prev_stuck = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (समय_after(jअगरfies, local->last_tick_समयr + 5 * HZ) &&
	    local->last_tick_समयr) अणु
		evstat = HFA384X_INW(HFA384X_EVSTAT_OFF);
		पूर्णांकen = HFA384X_INW(HFA384X_INTEN_OFF);
		अगर (!prev_stuck) अणु
			prपूर्णांकk(KERN_INFO "%s: SW TICK stuck? "
			       "bits=0x%lx EvStat=%04x IntEn=%04x\n",
			       dev->name, local->bits, evstat, पूर्णांकen);
		पूर्ण
		local->sw_tick_stuck++;
		अगर ((evstat & HFA384X_BAP0_EVENTS) &&
		    (पूर्णांकen & HFA384X_BAP0_EVENTS)) अणु
			prपूर्णांकk(KERN_INFO "%s: trying to recover from IRQ "
			       "hang\n", dev->name);
			hfa384x_events_no_bap0(dev);
		पूर्ण
		prev_stuck = 1;
	पूर्ण अन्यथा
		prev_stuck = 0;
पूर्ण


/* Called only from hardware IRQ */
अटल व्योम prism2_check_magic(local_info_t *local)
अणु
	/* at least PCI Prism2.5 with bus mastering seems to someबार
	 * वापस 0x0000 in SWSUPPORT0 क्रम unknown reason, but re-पढ़ोing the
	 * रेजिस्टर once or twice seems to get the correct value.. PCI cards
	 * cannot anyway be हटाओd during normal operation, so there is not
	 * really any need क्रम this verअगरication with them. */

#अगर_अघोषित PRISM2_PCI
#अगर_अघोषित final_version
	अटल अचिन्हित दीर्घ last_magic_err = 0;
	काष्ठा net_device *dev = local->dev;

	अगर (HFA384X_INW(HFA384X_SWSUPPORT0_OFF) != HFA384X_MAGIC) अणु
		अगर (!local->hw_पढ़ोy)
			वापस;
		HFA384X_OUTW(0xffff, HFA384X_EVACK_OFF);
		अगर (समय_after(jअगरfies, last_magic_err + 10 * HZ)) अणु
			prपूर्णांकk("%s: Interrupt, but SWSUPPORT0 does not match: "
			       "%04X != %04X - card removed?\n", dev->name,
			       HFA384X_INW(HFA384X_SWSUPPORT0_OFF),
			       HFA384X_MAGIC);
			last_magic_err = jअगरfies;
		पूर्ण अन्यथा अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: interrupt - SWSUPPORT0=%04x "
			       "MAGIC=%04x\n", dev->name,
			       HFA384X_INW(HFA384X_SWSUPPORT0_OFF),
			       HFA384X_MAGIC);
		पूर्ण
		अगर (HFA384X_INW(HFA384X_SWSUPPORT0_OFF) != 0xffff)
			schedule_work(&local->reset_queue);
		वापस;
	पूर्ण
#पूर्ण_अगर /* final_version */
#पूर्ण_अगर /* !PRISM2_PCI */
पूर्ण


/* Called only from hardware IRQ */
अटल irqवापस_t prism2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक events = 0;
	u16 ev;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Detect early पूर्णांकerrupt beक्रमe driver is fully configured */
	spin_lock(&local->irq_init_lock);
	अगर (!dev->base_addr) अणु
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Interrupt, but dev not configured\n",
			       dev->name);
		पूर्ण
		spin_unlock(&local->irq_init_lock);
		वापस IRQ_HANDLED;
	पूर्ण
	spin_unlock(&local->irq_init_lock);

	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INTERRUPT, 0, 0);

	अगर (local->func->card_present && !local->func->card_present(local)) अणु
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Interrupt, but dev not OK\n",
			       dev->name);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	prism2_check_magic(local);

	क्रम (;;) अणु
		ev = HFA384X_INW(HFA384X_EVSTAT_OFF);
		अगर (ev == 0xffff) अणु
			अगर (local->shutकरोwn)
				वापस IRQ_HANDLED;
			HFA384X_OUTW(0xffff, HFA384X_EVACK_OFF);
			prपूर्णांकk(KERN_DEBUG "%s: prism2_interrupt: ev=0xffff\n",
			       dev->name);
			वापस IRQ_HANDLED;
		पूर्ण

		ev &= HFA384X_INW(HFA384X_INTEN_OFF);
		अगर (ev == 0)
			अवरोध;

		अगर (ev & HFA384X_EV_CMD) अणु
			prism2_cmd_ev(dev);
		पूर्ण

		/* Above events are needed even beक्रमe hw is पढ़ोy, but other
		 * events should be skipped during initialization. This may
		 * change क्रम AllocEv अगर allocate_fid is implemented without
		 * busy रुकोing. */
		अगर (!local->hw_पढ़ोy || local->hw_resetting ||
		    !local->dev_enabled) अणु
			ev = HFA384X_INW(HFA384X_EVSTAT_OFF);
			अगर (ev & HFA384X_EV_CMD)
				जाओ next_event;
			अगर ((ev & HFA384X_EVENT_MASK) == 0)
				वापस IRQ_HANDLED;
			अगर (local->dev_enabled && (ev & ~HFA384X_EV_TICK) &&
			    net_ratelimit()) अणु
				prपूर्णांकk(KERN_DEBUG "%s: prism2_interrupt: hw "
				       "not ready; skipping events 0x%04x "
				       "(IntEn=0x%04x)%s%s%s\n",
				       dev->name, ev,
				       HFA384X_INW(HFA384X_INTEN_OFF),
				       !local->hw_पढ़ोy ? " (!hw_ready)" : "",
				       local->hw_resetting ?
				       " (hw_resetting)" : "",
				       !local->dev_enabled ?
				       " (!dev_enabled)" : "");
			पूर्ण
			HFA384X_OUTW(ev, HFA384X_EVACK_OFF);
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (ev & HFA384X_EV_TICK) अणु
			prism2_ev_tick(dev);
			HFA384X_OUTW(HFA384X_EV_TICK, HFA384X_EVACK_OFF);
		पूर्ण

		अगर (ev & HFA384X_EV_ALLOC) अणु
			prism2_alloc_ev(dev);
			HFA384X_OUTW(HFA384X_EV_ALLOC, HFA384X_EVACK_OFF);
		पूर्ण

		/* Reading data from the card is quite समय consuming, so करो it
		 * in tasklets. TX, TXEXC, RX, and INFO events will be ACKed
		 * and unmasked after needed data has been पढ़ो completely. */
		अगर (ev & HFA384X_BAP0_EVENTS) अणु
			hfa384x_events_no_bap0(dev);
			tasklet_schedule(&local->bap_tasklet);
		पूर्ण

#अगर_अघोषित final_version
		अगर (ev & HFA384X_EV_WTERR) अणु
			PDEBUG(DEBUG_EXTRA, "%s: WTERR event\n", dev->name);
			HFA384X_OUTW(HFA384X_EV_WTERR, HFA384X_EVACK_OFF);
		पूर्ण
#पूर्ण_अगर /* final_version */

		अगर (ev & HFA384X_EV_INFDROP) अणु
			prism2_infdrop(dev);
			HFA384X_OUTW(HFA384X_EV_INFDROP, HFA384X_EVACK_OFF);
		पूर्ण

	next_event:
		events++;
		अगर (events >= PRISM2_MAX_INTERRUPT_EVENTS) अणु
			PDEBUG(DEBUG_EXTRA, "prism2_interrupt: >%d events "
			       "(EvStat=0x%04x)\n",
			       PRISM2_MAX_INTERRUPT_EVENTS,
			       HFA384X_INW(HFA384X_EVSTAT_OFF));
			अवरोध;
		पूर्ण
	पूर्ण
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INTERRUPT, 0, 1);
	वापस IRQ_RETVAL(events);
पूर्ण


अटल व्योम prism2_check_sta_fw_version(local_info_t *local)
अणु
	काष्ठा hfa384x_comp_ident comp;
	पूर्णांक id, variant, major, minor;

	अगर (hfa384x_get_rid(local->dev, HFA384X_RID_STAID,
			    &comp, माप(comp), 1) < 0)
		वापस;

	local->fw_ap = 0;
	id = le16_to_cpu(comp.id);
	अगर (id != HFA384X_COMP_ID_STA) अणु
		अगर (id == HFA384X_COMP_ID_FW_AP)
			local->fw_ap = 1;
		वापस;
	पूर्ण

	major = __le16_to_cpu(comp.major);
	minor = __le16_to_cpu(comp.minor);
	variant = __le16_to_cpu(comp.variant);
	local->sta_fw_ver = PRISM2_FW_VER(major, minor, variant);

	/* Station firmware versions beक्रमe 1.4.x seem to have a bug in
	 * firmware-based WEP encryption when using Host AP mode, so use
	 * host_encrypt as a शेष क्रम them. Firmware version 1.4.9 is the
	 * first one that has been seen to produce correct encryption, but the
	 * bug might be fixed beक्रमe that (although, at least 1.4.2 is broken).
	 */
	local->fw_encrypt_ok = local->sta_fw_ver >= PRISM2_FW_VER(1,4,9);

	अगर (local->iw_mode == IW_MODE_MASTER && !local->host_encrypt &&
	    !local->fw_encrypt_ok) अणु
		prपूर्णांकk(KERN_DEBUG "%s: defaulting to host-based encryption as "
		       "a workaround for firmware bug in Host AP mode WEP\n",
		       local->dev->name);
		local->host_encrypt = 1;
	पूर्ण

	/* IEEE 802.11 standard compliant WDS frames (4 addresses) were broken
	 * in station firmware versions beक्रमe 1.5.x. With these versions, the
	 * driver uses a workaround with bogus frame क्रमmat (4th address after
	 * the payload). This is not compatible with other AP devices. Since
	 * the firmware bug is fixed in the latest station firmware versions,
	 * स्वतःmatically enable standard compliant mode क्रम cards using station
	 * firmware version 1.5.0 or newer. */
	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,5,0))
		local->wds_type |= HOSTAP_WDS_STANDARD_FRAME;
	अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: defaulting to bogus WDS frame as a "
		       "workaround for firmware bug in Host AP mode WDS\n",
		       local->dev->name);
	पूर्ण

	hostap_check_sta_fw_version(local->ap, local->sta_fw_ver);
पूर्ण


अटल व्योम hostap_passive_scan(काष्ठा समयr_list *t)
अणु
	local_info_t *local = from_समयr(local, t, passive_scan_समयr);
	काष्ठा net_device *dev = local->dev;
	u16 chan;

	अगर (local->passive_scan_पूर्णांकerval <= 0)
		वापस;

	अगर (local->passive_scan_state == PASSIVE_SCAN_LISTEN) अणु
		पूर्णांक max_tries = 16;

		/* Even though host प्रणाली करोes not really know when the WLAN
		 * MAC is sending frames, try to aव्योम changing channels क्रम
		 * passive scanning when a host-generated frame is being
		 * transmitted */
		अगर (test_bit(HOSTAP_BITS_TRANSMIT, &local->bits)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: passive scan detected pending "
			       "TX - delaying\n", dev->name);
			local->passive_scan_समयr.expires = jअगरfies + HZ / 10;
			add_समयr(&local->passive_scan_समयr);
			वापस;
		पूर्ण

		करो अणु
			local->passive_scan_channel++;
			अगर (local->passive_scan_channel > 14)
				local->passive_scan_channel = 1;
			max_tries--;
		पूर्ण जबतक (!(local->channel_mask &
			   (1 << (local->passive_scan_channel - 1))) &&
			 max_tries > 0);

		अगर (max_tries == 0) अणु
			prपूर्णांकk(KERN_INFO "%s: no allowed passive scan channels"
			       " found\n", dev->name);
			वापस;
		पूर्ण

		prपूर्णांकk(KERN_DEBUG "%s: passive scan channel %d\n",
		       dev->name, local->passive_scan_channel);
		chan = local->passive_scan_channel;
		local->passive_scan_state = PASSIVE_SCAN_WAIT;
		local->passive_scan_समयr.expires = jअगरfies + HZ / 10;
	पूर्ण अन्यथा अणु
		chan = local->channel;
		local->passive_scan_state = PASSIVE_SCAN_LISTEN;
		local->passive_scan_समयr.expires = jअगरfies +
			local->passive_scan_पूर्णांकerval * HZ;
	पूर्ण

	अगर (hfa384x_cmd_callback(dev, HFA384X_CMDCODE_TEST |
				 (HFA384X_TEST_CHANGE_CHANNEL << 8),
				 chan, शून्य, 0))
		prपूर्णांकk(KERN_ERR "%s: passive scan channel set %d "
		       "failed\n", dev->name, chan);

	add_समयr(&local->passive_scan_समयr);
पूर्ण


/* Called only as a scheduled task when communications quality values should
 * be updated. */
अटल व्योम handle_comms_qual_update(काष्ठा work_काष्ठा *work)
अणु
	local_info_t *local =
		container_of(work, local_info_t, comms_qual_update);
	prism2_update_comms_qual(local->dev);
पूर्ण


/* Software watchकरोg - called as a समयr. Hardware पूर्णांकerrupt (Tick event) is
 * used to monitor that local->last_tick_समयr is being updated. If not,
 * पूर्णांकerrupt busy-loop is assumed and driver tries to recover by masking out
 * some events. */
अटल व्योम hostap_tick_समयr(काष्ठा समयr_list *t)
अणु
	अटल अचिन्हित दीर्घ last_inquire = 0;
	local_info_t *local = from_समयr(local, t, tick_समयr);
	local->last_tick_समयr = jअगरfies;

	/* Inquire CommTallies every 10 seconds to keep the statistics updated
	 * more often during low load and when using 32-bit tallies. */
	अगर ((!last_inquire || समय_after(jअगरfies, last_inquire + 10 * HZ)) &&
	    !local->hw_करोwnloading && local->hw_पढ़ोy &&
	    !local->hw_resetting && local->dev_enabled) अणु
		hfa384x_cmd_callback(local->dev, HFA384X_CMDCODE_INQUIRE,
				     HFA384X_INFO_COMMTALLIES, शून्य, 0);
		last_inquire = jअगरfies;
	पूर्ण

	अगर ((local->last_comms_qual_update == 0 ||
	     समय_after(jअगरfies, local->last_comms_qual_update + 10 * HZ)) &&
	    (local->iw_mode == IW_MODE_INFRA ||
	     local->iw_mode == IW_MODE_ADHOC)) अणु
		schedule_work(&local->comms_qual_update);
	पूर्ण

	local->tick_समयr.expires = jअगरfies + 2 * HZ;
	add_समयr(&local->tick_समयr);
पूर्ण


#अगर !defined(PRISM2_NO_PROCFS_DEBUG) && defined(CONFIG_PROC_FS)
अटल u16 hfa384x_पढ़ो_reg(काष्ठा net_device *dev, u16 reg)
अणु
	वापस HFA384X_INW(reg);
पूर्ण

अटल पूर्णांक prism2_रेजिस्टरs_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = m->निजी;

#घोषणा SHOW_REG(n) \
  seq_म_लिखो(m, #n "=%04x\n", hfa384x_पढ़ो_reg(local->dev, HFA384X_##n##_OFF))

	SHOW_REG(CMD);
	SHOW_REG(PARAM0);
	SHOW_REG(PARAM1);
	SHOW_REG(PARAM2);
	SHOW_REG(STATUS);
	SHOW_REG(RESP0);
	SHOW_REG(RESP1);
	SHOW_REG(RESP2);
	SHOW_REG(INFOFID);
	SHOW_REG(CONTROL);
	SHOW_REG(SELECT0);
	SHOW_REG(SELECT1);
	SHOW_REG(OFFSET0);
	SHOW_REG(OFFSET1);
	SHOW_REG(RXFID);
	SHOW_REG(ALLOCFID);
	SHOW_REG(TXCOMPLFID);
	SHOW_REG(SWSUPPORT0);
	SHOW_REG(SWSUPPORT1);
	SHOW_REG(SWSUPPORT2);
	SHOW_REG(EVSTAT);
	SHOW_REG(INTEN);
	SHOW_REG(EVACK);
	/* Do not पढ़ो data रेजिस्टरs, because they change the state of the
	 * MAC (offset += 2) */
	/* SHOW_REG(DATA0); */
	/* SHOW_REG(DATA1); */
	SHOW_REG(AUXPAGE);
	SHOW_REG(AUXOFFSET);
	/* SHOW_REG(AUXDATA); */
#अगर_घोषित PRISM2_PCI
	SHOW_REG(PCICOR);
	SHOW_REG(PCIHCR);
	SHOW_REG(PCI_M0_ADDRH);
	SHOW_REG(PCI_M0_ADDRL);
	SHOW_REG(PCI_M0_LEN);
	SHOW_REG(PCI_M0_CTL);
	SHOW_REG(PCI_STATUS);
	SHOW_REG(PCI_M1_ADDRH);
	SHOW_REG(PCI_M1_ADDRL);
	SHOW_REG(PCI_M1_LEN);
	SHOW_REG(PCI_M1_CTL);
#पूर्ण_अगर /* PRISM2_PCI */

	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा set_tim_data अणु
	काष्ठा list_head list;
	पूर्णांक aid;
	पूर्णांक set;
पूर्ण;

अटल पूर्णांक prism2_set_tim(काष्ठा net_device *dev, पूर्णांक aid, पूर्णांक set)
अणु
	काष्ठा list_head *ptr;
	काष्ठा set_tim_data *new_entry;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	new_entry = kzalloc(माप(*new_entry), GFP_ATOMIC);
	अगर (new_entry == शून्य)
		वापस -ENOMEM;

	new_entry->aid = aid;
	new_entry->set = set;

	spin_lock_bh(&local->set_tim_lock);
	list_क्रम_each(ptr, &local->set_tim_list) अणु
		काष्ठा set_tim_data *entry =
			list_entry(ptr, काष्ठा set_tim_data, list);
		अगर (entry->aid == aid) अणु
			PDEBUG(DEBUG_PS2, "%s: prism2_set_tim: aid=%d "
			       "set=%d ==> %d\n",
			       local->dev->name, aid, entry->set, set);
			entry->set = set;
			kमुक्त(new_entry);
			new_entry = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (new_entry)
		list_add_tail(&new_entry->list, &local->set_tim_list);
	spin_unlock_bh(&local->set_tim_lock);

	schedule_work(&local->set_tim_queue);

	वापस 0;
पूर्ण


अटल व्योम handle_set_tim_queue(काष्ठा work_काष्ठा *work)
अणु
	local_info_t *local = container_of(work, local_info_t, set_tim_queue);
	काष्ठा set_tim_data *entry;
	u16 val;

	क्रम (;;) अणु
		entry = शून्य;
		spin_lock_bh(&local->set_tim_lock);
		अगर (!list_empty(&local->set_tim_list)) अणु
			entry = list_entry(local->set_tim_list.next,
					   काष्ठा set_tim_data, list);
			list_del(&entry->list);
		पूर्ण
		spin_unlock_bh(&local->set_tim_lock);
		अगर (!entry)
			अवरोध;

		PDEBUG(DEBUG_PS2, "%s: handle_set_tim_queue: aid=%d set=%d\n",
		       local->dev->name, entry->aid, entry->set);

		val = entry->aid;
		अगर (entry->set)
			val |= 0x8000;
		अगर (hostap_set_word(local->dev, HFA384X_RID_CNFTIMCTRL, val)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: set_tim failed (aid=%d "
			       "set=%d)\n",
			       local->dev->name, entry->aid, entry->set);
		पूर्ण

		kमुक्त(entry);
	पूर्ण
पूर्ण


अटल व्योम prism2_clear_set_tim_queue(local_info_t *local)
अणु
	काष्ठा list_head *ptr, *n;

	list_क्रम_each_safe(ptr, n, &local->set_tim_list) अणु
		काष्ठा set_tim_data *entry;
		entry = list_entry(ptr, काष्ठा set_tim_data, list);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
पूर्ण


/*
 * HostAP uses two layers of net devices, where the inner
 * layer माला_लो called all the समय from the outer layer.
 * This is a natural nesting, which needs a split lock type.
 */
अटल काष्ठा lock_class_key hostap_netdev_xmit_lock_key;
अटल काष्ठा lock_class_key hostap_netdev_addr_lock_key;

अटल व्योम prism2_set_lockdep_class_one(काष्ठा net_device *dev,
					 काष्ठा netdev_queue *txq,
					 व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock,
			  &hostap_netdev_xmit_lock_key);
पूर्ण

अटल व्योम prism2_set_lockdep_class(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock,
			  &hostap_netdev_addr_lock_key);
	netdev_क्रम_each_tx_queue(dev, prism2_set_lockdep_class_one, शून्य);
पूर्ण

अटल काष्ठा net_device *
prism2_init_local_data(काष्ठा prism2_helper_functions *funcs, पूर्णांक card_idx,
		       काष्ठा device *sdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा local_info *local;
	पूर्णांक len, i, ret;

	अगर (funcs == शून्य)
		वापस शून्य;

	len = म_माप(dev_ढाँचा);
	अगर (len >= IFNAMSIZ || म_माला(dev_ढाँचा, "%d") == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "hostap: Invalid dev_template='%s'\n",
		       dev_ढाँचा);
		वापस शून्य;
	पूर्ण

	len = माप(काष्ठा hostap_पूर्णांकerface) +
		3 + माप(काष्ठा local_info) +
		3 + माप(काष्ठा ap_data);

	dev = alloc_etherdev(len);
	अगर (dev == शून्य)
		वापस शून्य;

	अगरace = netdev_priv(dev);
	local = (काष्ठा local_info *) ((((दीर्घ) (अगरace + 1)) + 3) & ~3);
	local->ap = (काष्ठा ap_data *) ((((दीर्घ) (local + 1)) + 3) & ~3);
	local->dev = अगरace->dev = dev;
	अगरace->local = local;
	अगरace->type = HOSTAP_INTERFACE_MASTER;
	INIT_LIST_HEAD(&local->hostap_पूर्णांकerfaces);

	local->hw_module = THIS_MODULE;

#अगर_घोषित PRISM2_IO_DEBUG
	local->io_debug_enabled = 1;
#पूर्ण_अगर /* PRISM2_IO_DEBUG */

	local->func = funcs;
	local->func->cmd = hfa384x_cmd;
	local->func->पढ़ो_regs = hfa384x_पढ़ो_regs;
	local->func->get_rid = hfa384x_get_rid;
	local->func->set_rid = hfa384x_set_rid;
	local->func->hw_enable = prism2_hw_enable;
	local->func->hw_config = prism2_hw_config;
	local->func->hw_reset = prism2_hw_reset;
	local->func->hw_shutकरोwn = prism2_hw_shutकरोwn;
	local->func->reset_port = prism2_reset_port;
	local->func->schedule_reset = prism2_schedule_reset;
#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
	local->func->पढ़ो_aux_proc_ops = &prism2_करोwnload_aux_dump_proc_ops;
	local->func->करोwnload = prism2_करोwnload;
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */
	local->func->tx = prism2_tx_80211;
	local->func->set_tim = prism2_set_tim;
	local->func->need_tx_headroom = 0; /* no need to add txdesc in
					    * skb->data (FIX: maybe क्रम DMA bus
					    * mastering? */

	local->mtu = mtu;

	rwlock_init(&local->अगरace_lock);
	spin_lock_init(&local->txfidlock);
	spin_lock_init(&local->cmdlock);
	spin_lock_init(&local->baplock);
	spin_lock_init(&local->lock);
	spin_lock_init(&local->irq_init_lock);
	mutex_init(&local->rid_bap_mtx);

	अगर (card_idx < 0 || card_idx >= MAX_PARM_DEVICES)
		card_idx = 0;
	local->card_idx = card_idx;

	len = म_माप(essid);
	स_नकल(local->essid, essid,
	       len > MAX_SSID_LEN ? MAX_SSID_LEN : len);
	local->essid[MAX_SSID_LEN] = '\0';
	i = GET_INT_PARM(iw_mode, card_idx);
	अगर ((i >= IW_MODE_ADHOC && i <= IW_MODE_REPEAT) ||
	    i == IW_MODE_MONITOR) अणु
		local->iw_mode = i;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "prism2: Unknown iw_mode %d; using "
		       "IW_MODE_MASTER\n", i);
		local->iw_mode = IW_MODE_MASTER;
	पूर्ण
	local->channel = GET_INT_PARM(channel, card_idx);
	local->beacon_पूर्णांक = GET_INT_PARM(beacon_पूर्णांक, card_idx);
	local->dtim_period = GET_INT_PARM(dtim_period, card_idx);
	local->wds_max_connections = 16;
	local->tx_control = HFA384X_TX_CTRL_FLAGS;
	local->manual_retry_count = -1;
	local->rts_threshold = 2347;
	local->fragm_threshold = 2346;
	local->rssi_to_dBm = 100; /* शेष; to be overriden by
				   * cnfDbmAdjust, अगर available */
	local->auth_algs = PRISM2_AUTH_OPEN | PRISM2_AUTH_SHARED_KEY;
	local->sram_type = -1;
	local->scan_channel_mask = 0xffff;
	local->monitor_type = PRISM2_MONITOR_RADIOTAP;

	/* Initialize task queue काष्ठाures */
	INIT_WORK(&local->reset_queue, handle_reset_queue);
	INIT_WORK(&local->set_multicast_list_queue,
		  hostap_set_multicast_list_queue);

	INIT_WORK(&local->set_tim_queue, handle_set_tim_queue);
	INIT_LIST_HEAD(&local->set_tim_list);
	spin_lock_init(&local->set_tim_lock);

	INIT_WORK(&local->comms_qual_update, handle_comms_qual_update);

	/* Initialize tasklets क्रम handling hardware IRQ related operations
	 * outside hw IRQ handler */
	tasklet_setup(&local->bap_tasklet, hostap_bap_tasklet);
	tasklet_setup(&local->info_tasklet, hostap_info_tasklet);
	hostap_info_init(local);

	tasklet_setup(&local->rx_tasklet, hostap_rx_tasklet);
	skb_queue_head_init(&local->rx_list);

	tasklet_setup(&local->sta_tx_exc_tasklet,
			    hostap_sta_tx_exc_tasklet);
	skb_queue_head_init(&local->sta_tx_exc_list);

	INIT_LIST_HEAD(&local->cmd_queue);
	init_रुकोqueue_head(&local->hostscan_wq);

	lib80211_crypt_info_init(&local->crypt_info, dev->name, &local->lock);

	समयr_setup(&local->passive_scan_समयr, hostap_passive_scan, 0);
	समयr_setup(&local->tick_समयr, hostap_tick_समयr, 0);
	local->tick_समयr.expires = jअगरfies + 2 * HZ;
	add_समयr(&local->tick_समयr);

	INIT_LIST_HEAD(&local->bss_list);

	hostap_setup_dev(dev, local, HOSTAP_INTERFACE_MASTER);

	dev->type = ARPHRD_IEEE80211;
	dev->header_ops = &hostap_80211_ops;

	rtnl_lock();
	ret = dev_alloc_name(dev, "wifi%d");
	SET_NETDEV_DEV(dev, sdev);
	अगर (ret >= 0)
		ret = रेजिस्टर_netdevice(dev);

	prism2_set_lockdep_class(dev);
	rtnl_unlock();
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: register netdevice failed!\n",
		       dev_info);
		जाओ fail;
	पूर्ण
	prपूर्णांकk(KERN_INFO "%s: Registered netdevice %s\n", dev_info, dev->name);

	hostap_init_data(local);
	वापस dev;

 fail:
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण


अटल पूर्णांक hostap_hw_पढ़ोy(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा local_info *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	local->ddev = hostap_add_पूर्णांकerface(local, HOSTAP_INTERFACE_MAIN, 0,
					   "", dev_ढाँचा);

	अगर (local->ddev) अणु
		अगर (local->iw_mode == IW_MODE_INFRA ||
		    local->iw_mode == IW_MODE_ADHOC) अणु
			netअगर_carrier_off(local->dev);
			netअगर_carrier_off(local->ddev);
		पूर्ण
		hostap_init_proc(local);
#अगर_अघोषित PRISM2_NO_PROCFS_DEBUG
		proc_create_single_data("registers", 0, local->proc,
				 prism2_रेजिस्टरs_proc_show, local);
#पूर्ण_अगर /* PRISM2_NO_PROCFS_DEBUG */
		hostap_init_ap_proc(local);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण


अटल व्योम prism2_मुक्त_local_data(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_tx_callback_info *tx_cb, *tx_cb_prev;
	पूर्णांक i;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा local_info *local;
	काष्ठा list_head *ptr, *n;

	अगर (dev == शून्य)
		वापस;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Unरेजिस्टर all netdevs beक्रमe मुक्तing local data. */
	list_क्रम_each_safe(ptr, n, &local->hostap_पूर्णांकerfaces) अणु
		अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
		अगर (अगरace->type == HOSTAP_INTERFACE_MASTER) अणु
			/* special handling क्रम this पूर्णांकerface below */
			जारी;
		पूर्ण
		hostap_हटाओ_पूर्णांकerface(अगरace->dev, 0, 1);
	पूर्ण

	unरेजिस्टर_netdev(local->dev);

	flush_work(&local->reset_queue);
	flush_work(&local->set_multicast_list_queue);
	flush_work(&local->set_tim_queue);
#अगर_अघोषित PRISM2_NO_STATION_MODES
	flush_work(&local->info_queue);
#पूर्ण_अगर
	flush_work(&local->comms_qual_update);

	lib80211_crypt_info_मुक्त(&local->crypt_info);

	अगर (समयr_pending(&local->passive_scan_समयr))
		del_समयr(&local->passive_scan_समयr);

	अगर (समयr_pending(&local->tick_समयr))
		del_समयr(&local->tick_समयr);

	prism2_clear_cmd_queue(local);

	skb_queue_purge(&local->info_list);
	skb_queue_purge(&local->rx_list);
	skb_queue_purge(&local->sta_tx_exc_list);

	अगर (local->dev_enabled)
		prism2_callback(local, PRISM2_CALLBACK_DISABLE);

	अगर (local->ap != शून्य)
		hostap_मुक्त_data(local->ap);

#अगर_अघोषित PRISM2_NO_PROCFS_DEBUG
	अगर (local->proc != शून्य)
		हटाओ_proc_entry("registers", local->proc);
#पूर्ण_अगर /* PRISM2_NO_PROCFS_DEBUG */
	hostap_हटाओ_proc(local);

	tx_cb = local->tx_callback;
	जबतक (tx_cb != शून्य) अणु
		tx_cb_prev = tx_cb;
		tx_cb = tx_cb->next;
		kमुक्त(tx_cb_prev);
	पूर्ण

	hostap_set_hostapd(local, 0, 0);
	hostap_set_hostapd_sta(local, 0, 0);

	क्रम (i = 0; i < PRISM2_FRAG_CACHE_LEN; i++) अणु
		अगर (local->frag_cache[i].skb != शून्य)
			dev_kमुक्त_skb(local->frag_cache[i].skb);
	पूर्ण

#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
	prism2_करोwnload_मुक्त_data(local->dl_pri);
	prism2_करोwnload_मुक्त_data(local->dl_sec);
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */

	prism2_clear_set_tim_queue(local);

	list_क्रम_each_safe(ptr, n, &local->bss_list) अणु
		काष्ठा hostap_bss_info *bss =
			list_entry(ptr, काष्ठा hostap_bss_info, list);
		kमुक्त(bss);
	पूर्ण

	kमुक्त(local->pda);
	kमुक्त(local->last_scan_results);
	kमुक्त(local->generic_elem);

	मुक्त_netdev(local->dev);
पूर्ण


#अगर defined(PRISM2_PCI) || defined(PRISM2_PCCARD)
अटल व्योम __maybe_unused prism2_suspend(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा local_info *local;
	जोड़ iwreq_data wrqu;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Send disconnect event, e.g., to trigger reassociation after resume
	 * अगर wpa_supplicant is used. */
	स_रखो(&wrqu, 0, माप(wrqu));
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(local->dev, SIOCGIWAP, &wrqu, शून्य);

	/* Disable hardware and firmware */
	prism2_hw_shutकरोwn(dev, 0);
पूर्ण
#पूर्ण_अगर /* PRISM2_PCI || PRISM2_PCCARD */


/* These might at some poपूर्णांक be compiled separately and used as separate
 * kernel modules or linked पूर्णांकo one */
#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
#समावेश "hostap_download.c"
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */

#अगर_घोषित PRISM2_CALLBACK
/* External hostap_callback.c file can be used to, e.g., blink activity led.
 * This can use platक्रमm specअगरic code and must define prism2_callback()
 * function (अगर PRISM2_CALLBACK is not defined, these function calls are not
 * used. */
#समावेश "hostap_callback.c"
#पूर्ण_अगर /* PRISM2_CALLBACK */
