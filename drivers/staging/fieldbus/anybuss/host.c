<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HMS Anybus-S Host Driver
 *
 * Copyright (C) 2018 Arcx Inc
 */

/*
 * Architecture Overview
 * =====================
 * This driver (running on the CPU/SoC) and the Anybus-S card communicate
 * by पढ़ोing and writing data to/from the Anybus-S Dual-Port RAM (dpram).
 * This is memory connected to both the SoC and Anybus-S card, which both sides
 * can access मुक्तly and concurrently.
 *
 * Synchronization happens by means of two रेजिस्टरs located in the dpram:
 * IND_AB: written exclusively by the Anybus card; and
 * IND_AP: written exclusively by this driver.
 *
 * Communication happens using one of the following mechanisms:
 * 1. reserve, पढ़ो/ग_लिखो, release dpram memory areas:
 *	using an IND_AB/IND_AP protocol, the driver is able to reserve certain
 *	memory areas. no dpram memory can be पढ़ो or written except अगर reserved.
 *	(with a few limited exceptions)
 * 2. send and receive data काष्ठाures via a shared mailbox:
 *	using an IND_AB/IND_AP protocol, the driver and Anybus card are able to
 *	exchange commands and responses using a shared mailbox.
 * 3. receive software पूर्णांकerrupts:
 *	using an IND_AB/IND_AP protocol, the Anybus card is able to notअगरy the
 *	driver of certain events such as: bus online/offline, data available.
 *	note that software पूर्णांकerrupt event bits are located in a memory area
 *	which must be reserved beक्रमe it can be accessed.
 *
 * The manual[1] is silent on whether these mechanisms can happen concurrently,
 * or how they should be synchronized. However, section 13 (Driver Example)
 * provides the following suggestion क्रम developing a driver:
 * a) an पूर्णांकerrupt handler which updates global variables;
 * b) a continuously-running task handling area requests (1 above)
 * c) a continuously-running task handling mailbox requests (2 above)
 * The example conspicuously leaves out software पूर्णांकerrupts (3 above), which
 * is the thorniest issue to get right (see below).
 *
 * The naive, straightक्रमward way to implement this would be:
 * - create an isr which updates shared variables;
 * - create a work_काष्ठा which handles software पूर्णांकerrupts on a queue;
 * - create a function which करोes reserve/update/unlock in a loop;
 * - create a function which करोes mailbox send/receive in a loop;
 * - call the above functions from the driver's पढ़ो/ग_लिखो/ioctl;
 * - synchronize using mutexes/spinlocks:
 *	+ only one area request at a समय
 *	+ only one mailbox request at a समय
 *	+ protect AB_IND, AB_IND against data hazards (e.g. पढ़ो-after-ग_लिखो)
 *
 * Unक्रमtunately, the presence of the software पूर्णांकerrupt causes subtle yet
 * considerable synchronization issues; especially problematic is the
 * requirement to reserve/release the area which contains the status bits.
 *
 * The driver architecture presented here sidesteps these synchronization issues
 * by accessing the dpram from a single kernel thपढ़ो only. User-space throws
 * "tasks" (i.e. 1, 2 above) पूर्णांकo a task queue, रुकोs क्रम their completion,
 * and the kernel thपढ़ो runs them to completion.
 *
 * Each task has a task_function, which is called/run by the queue thपढ़ो.
 * That function communicates with the Anybus card, and वापसs either
 * 0 (OK), a negative error code (error), or -EINPROGRESS (रुकोing).
 * On OK or error, the queue thपढ़ो completes and dequeues the task,
 * which also releases the user space thपढ़ो which may still be रुकोing क्रम it.
 * On -EINPROGRESS (रुकोing), the queue thपढ़ो will leave the task on the queue,
 * and revisit (call again) whenever an पूर्णांकerrupt event comes in.
 *
 * Each task has a state machine, which is run by calling its task_function.
 * It ensures that the task will go through its various stages over समय,
 * वापसing -EINPROGRESS अगर it wants to रुको क्रम an event to happen.
 *
 * Note that according to the manual's driver example, the following operations
 * may run independent of each other:
 * - area reserve/पढ़ो/ग_लिखो/release	(poपूर्णांक 1 above)
 * - mailbox operations			(poपूर्णांक 2 above)
 * - चयनing घातer on/off
 *
 * To allow them to run independently, each operation class माला_लो its own queue.
 *
 * Userspace processes A, B, C, D post tasks to the appropriate queue,
 * and रुको क्रम task completion:
 *
 *	process A	B	C	D
 *		|	|	|	|
 *		v	v	v	v
 *	|<-----	========================================
 *	|		|	   |		|
 *	|		v	   v		v-------<-------+
 *	|	+--------------------------------------+	|
 *	|	| घातer q     | mbox q    | area q     |	|
 *	|	|------------|------------|------------|	|
 *	|	| task       | task       | task       |	|
 *	|	| task       | task       | task       |	|
 *	|	| task रुको  | task रुको  | task रुको  |	|
 *	|	+--------------------------------------+	|
 *	|		^	   ^		^		|
 *	|		|	   |		|		^
 *	|	+--------------------------------------+	|
 *	|	|	     queue thपढ़ो	       |	|
 *	|	|--------------------------------------|	|
 *	|	| single-thपढ़ोed:		       |	|
 *	|	| loop:				       |	|
 *	v	|   क्रम each queue:		       |	|
 *	|	|     run task state machine	       |	|
 *	|	|     अगर task रुकोing:		       |	|
 *	|	|       leave on queue		       |	|
 *	|	|     अगर task करोne:		       |	|
 *	|	|       complete task, हटाओ from q   |	|
 *	|	|   अगर software irq event bits set:    |	|
 *	|	|     notअगरy userspace		       |	|
 *	|	|     post clear event bits task------>|>-------+
 *	|	|   रुको क्रम IND_AB changed event OR   |
 *	|	|            task added event	  OR   |
 *	|	|	     समयout		       |
 *	|	| end loop			       |
 *	|	+--------------------------------------+
 *	|	+		wake up		       +
 *	|	+--------------------------------------+
 *	|		^			^
 *	|		|			|
 *	+-------->-------			|
 *						|
 *		+--------------------------------------+
 *		|	पूर्णांकerrupt service routine      |
 *		|--------------------------------------|
 *		| wake up queue thपढ़ो on IND_AB change|
 *		+--------------------------------------+
 *
 * Note that the Anybus पूर्णांकerrupt is dual-purpose:
 * - after a reset, triggered when the card becomes पढ़ोy;
 * - during normal operation, triggered when AB_IND changes.
 * This is why the पूर्णांकerrupt service routine करोesn't just wake up the
 * queue thपढ़ो, but also completes the card_boot completion.
 *
 * [1] https://www.anybus.com/करोcs/librariesprovider7/शेष-करोcument-library/
 *	manuals-design-guides/hms-hmsi-27-275.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kref.h>
#समावेश <linux/of_address.h>

/* move to <linux/anybuss-*.h> when taking this out of staging */
#समावेश "anybuss-client.h"
#समावेश "anybuss-controller.h"

#घोषणा DPRAM_SIZE		0x800
#घोषणा MAX_MBOX_MSG_SZ		0x0FF
#घोषणा TIMEOUT			(HZ * 2)
#घोषणा MAX_DATA_AREA_SZ	0x200
#घोषणा MAX_FBCTRL_AREA_SZ	0x1BE

#घोषणा REG_BOOTLOADER_V	0x7C0
#घोषणा REG_API_V		0x7C2
#घोषणा REG_FIELDBUS_V		0x7C4
#घोषणा REG_SERIAL_NO		0x7C6
#घोषणा REG_FIELDBUS_TYPE	0x7CC
#घोषणा REG_MODULE_SW_V		0x7CE
#घोषणा REG_IND_AB		0x7FF
#घोषणा REG_IND_AP		0x7FE
#घोषणा REG_EVENT_CAUSE		0x7ED
#घोषणा MBOX_IN_AREA		0x400
#घोषणा MBOX_OUT_AREA		0x520
#घोषणा DATA_IN_AREA		0x000
#घोषणा DATA_OUT_AREA		0x200
#घोषणा FBCTRL_AREA		0x640

#घोषणा EVENT_CAUSE_DC          0x01
#घोषणा EVENT_CAUSE_FBOF        0x02
#घोषणा EVENT_CAUSE_FBON        0x04

#घोषणा IND_AB_UPDATED		0x08
#घोषणा IND_AX_MIN		0x80
#घोषणा IND_AX_MOUT		0x40
#घोषणा IND_AX_IN		0x04
#घोषणा IND_AX_OUT		0x02
#घोषणा IND_AX_FBCTRL		0x01
#घोषणा IND_AP_LOCK		0x08
#घोषणा IND_AP_ACTION		0x10
#घोषणा IND_AX_EVNT		0x20
#घोषणा IND_AP_ABITS		(IND_AX_IN | IND_AX_OUT | \
					IND_AX_FBCTRL | \
					IND_AP_ACTION | IND_AP_LOCK)

#घोषणा INFO_TYPE_FB		0x0002
#घोषणा INFO_TYPE_APP		0x0001
#घोषणा INFO_COMMAND		0x4000

#घोषणा OP_MODE_FBFC		0x0002
#घोषणा OP_MODE_FBS		0x0004
#घोषणा OP_MODE_CD		0x0200

#घोषणा CMD_START_INIT		0x0001
#घोषणा CMD_ANYBUS_INIT		0x0002
#घोषणा CMD_END_INIT		0x0003

/*
 * ---------------------------------------------------------------
 * Anybus mailbox messages - definitions
 * ---------------------------------------------------------------
 * note that we're depending on the layout of these काष्ठाures being
 * exactly as advertised.
 */

काष्ठा anybus_mbox_hdr अणु
	__be16 id;
	__be16 info;
	__be16 cmd_num;
	__be16 data_size;
	__be16 frame_count;
	__be16 frame_num;
	__be16 offset_high;
	__be16 offset_low;
	__be16 extended[8];
पूर्ण;

काष्ठा msg_anybus_init अणु
	__be16 input_io_len;
	__be16 input_dpram_len;
	__be16 input_total_len;
	__be16 output_io_len;
	__be16 output_dpram_len;
	__be16 output_total_len;
	__be16 op_mode;
	__be16 notअगर_config;
	__be16 wd_val;
पूर्ण;

/* ------------- ref counted tasks ------------- */

काष्ठा ab_task;
प्रकार पूर्णांक (*ab_task_fn_t)(काष्ठा anybuss_host *cd,
					काष्ठा ab_task *t);
प्रकार व्योम (*ab_करोne_fn_t)(काष्ठा anybuss_host *cd);

काष्ठा area_priv अणु
	bool is_ग_लिखो;
	u16 flags;
	u16 addr;
	माप_प्रकार count;
	u8 buf[MAX_DATA_AREA_SZ];
पूर्ण;

काष्ठा mbox_priv अणु
	काष्ठा anybus_mbox_hdr hdr;
	माप_प्रकार msg_out_sz;
	माप_प्रकार msg_in_sz;
	u8 msg[MAX_MBOX_MSG_SZ];
पूर्ण;

काष्ठा ab_task अणु
	काष्ठा kmem_cache	*cache;
	काष्ठा kref		refcount;
	ab_task_fn_t		task_fn;
	ab_करोne_fn_t		करोne_fn;
	पूर्णांक			result;
	काष्ठा completion	करोne;
	अचिन्हित दीर्घ		start_jअगरfies;
	जोड़ अणु
		काष्ठा area_priv area_pd;
		काष्ठा mbox_priv mbox_pd;
	पूर्ण;
पूर्ण;

अटल काष्ठा ab_task *ab_task_create_get(काष्ठा kmem_cache *cache,
					  ab_task_fn_t task_fn)
अणु
	काष्ठा ab_task *t;

	t = kmem_cache_alloc(cache, GFP_KERNEL);
	अगर (!t)
		वापस शून्य;
	t->cache = cache;
	kref_init(&t->refcount);
	t->task_fn = task_fn;
	t->करोne_fn = शून्य;
	t->result = 0;
	init_completion(&t->करोne);
	वापस t;
पूर्ण

अटल व्योम __ab_task_destroy(काष्ठा kref *refcount)
अणु
	काष्ठा ab_task *t = container_of(refcount, काष्ठा ab_task, refcount);
	काष्ठा kmem_cache *cache = t->cache;

	kmem_cache_मुक्त(cache, t);
पूर्ण

अटल व्योम ab_task_put(काष्ठा ab_task *t)
अणु
	kref_put(&t->refcount, __ab_task_destroy);
पूर्ण

अटल काष्ठा ab_task *__ab_task_get(काष्ठा ab_task *t)
अणु
	kref_get(&t->refcount);
	वापस t;
पूर्ण

अटल व्योम __ab_task_finish(काष्ठा ab_task *t, काष्ठा anybuss_host *cd)
अणु
	अगर (t->करोne_fn)
		t->करोne_fn(cd);
	complete(&t->करोne);
पूर्ण

अटल व्योम
ab_task_dequeue_finish_put(काष्ठा kfअगरo *q, काष्ठा anybuss_host *cd)
अणु
	पूर्णांक ret;
	काष्ठा ab_task *t;

	ret = kfअगरo_out(q, &t, माप(t));
	WARN_ON(!ret);
	__ab_task_finish(t, cd);
	ab_task_put(t);
पूर्ण

अटल पूर्णांक
ab_task_enqueue(काष्ठा ab_task *t, काष्ठा kfअगरo *q, spinlock_t *slock,
		रुको_queue_head_t *wq)
अणु
	पूर्णांक ret;

	t->start_jअगरfies = jअगरfies;
	__ab_task_get(t);
	ret = kfअगरo_in_spinlocked(q, &t, माप(t), slock);
	अगर (!ret) अणु
		ab_task_put(t);
		वापस -ENOMEM;
	पूर्ण
	wake_up(wq);
	वापस 0;
पूर्ण

अटल पूर्णांक
ab_task_enqueue_रुको(काष्ठा ab_task *t, काष्ठा kfअगरo *q, spinlock_t *slock,
		     रुको_queue_head_t *wq)
अणु
	पूर्णांक ret;

	ret = ab_task_enqueue(t, q, slock, wq);
	अगर (ret)
		वापस ret;
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&t->करोne);
	अगर (ret)
		वापस ret;
	वापस t->result;
पूर्ण

/* ------------------------ anybus hardware ------------------------ */

काष्ठा anybuss_host अणु
	काष्ठा device *dev;
	काष्ठा anybuss_client *client;
	व्योम (*reset)(काष्ठा device *dev, bool निश्चित);
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	पूर्णांक host_idx;
	काष्ठा task_काष्ठा *qthपढ़ो;
	रुको_queue_head_t wq;
	काष्ठा completion card_boot;
	atomic_t ind_ab;
	spinlock_t qlock; /* protects IN side of घातerq, mboxq, areaq */
	काष्ठा kmem_cache *qcache;
	काष्ठा kfअगरo qs[3];
	काष्ठा kfअगरo *घातerq;
	काष्ठा kfअगरo *mboxq;
	काष्ठा kfअगरo *areaq;
	bool घातer_on;
	bool softपूर्णांक_pending;
पूर्ण;

अटल व्योम reset_निश्चित(काष्ठा anybuss_host *cd)
अणु
	cd->reset(cd->dev, true);
पूर्ण

अटल व्योम reset_deनिश्चित(काष्ठा anybuss_host *cd)
अणु
	cd->reset(cd->dev, false);
पूर्ण

अटल पूर्णांक test_dpram(काष्ठा regmap *regmap)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक val;

	क्रम (i = 0; i < DPRAM_SIZE; i++)
		regmap_ग_लिखो(regmap, i, (u8)i);
	क्रम (i = 0; i < DPRAM_SIZE; i++) अणु
		regmap_पढ़ो(regmap, i, &val);
		अगर ((u8)val != (u8)i)
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_ind_ab(काष्ठा regmap *regmap)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ / 2;
	अचिन्हित पूर्णांक a, b, i = 0;

	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		regmap_पढ़ो(regmap, REG_IND_AB, &a);
		regmap_पढ़ो(regmap, REG_IND_AB, &b);
		अगर (likely(a == b))
			वापस (पूर्णांक)a;
		अगर (i < 10) अणु
			cpu_relax();
			i++;
		पूर्ण अन्यथा अणु
			usleep_range(500, 1000);
		पूर्ण
	पूर्ण
	WARN(1, "IND_AB register not stable");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ग_लिखो_ind_ap(काष्ठा regmap *regmap, अचिन्हित पूर्णांक ind_ap)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ / 2;
	अचिन्हित पूर्णांक v, i = 0;

	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		regmap_ग_लिखो(regmap, REG_IND_AP, ind_ap);
		regmap_पढ़ो(regmap, REG_IND_AP, &v);
		अगर (likely(ind_ap == v))
			वापस 0;
		अगर (i < 10) अणु
			cpu_relax();
			i++;
		पूर्ण अन्यथा अणु
			usleep_range(500, 1000);
		पूर्ण
	पूर्ण
	WARN(1, "IND_AP register not stable");
	वापस -ETIMEDOUT;
पूर्ण

अटल irqवापस_t irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा anybuss_host *cd = data;
	पूर्णांक ind_ab;

	/*
	 * irq handler needs exclusive access to the IND_AB रेजिस्टर,
	 * because the act of पढ़ोing the रेजिस्टर acks the पूर्णांकerrupt.
	 *
	 * store the रेजिस्टर value in cd->ind_ab (an atomic_t), so that the
	 * queue thपढ़ो is able to पढ़ो it without causing an पूर्णांकerrupt ack
	 * side-effect (and without spuriously acking an पूर्णांकerrupt).
	 */
	ind_ab = पढ़ो_ind_ab(cd->regmap);
	अगर (ind_ab < 0)
		वापस IRQ_NONE;
	atomic_set(&cd->ind_ab, ind_ab);
	complete(&cd->card_boot);
	wake_up(&cd->wq);
	वापस IRQ_HANDLED;
पूर्ण

/* ------------------------ घातer on/off tasks --------------------- */

अटल पूर्णांक task_fn_घातer_off(काष्ठा anybuss_host *cd,
			     काष्ठा ab_task *t)
अणु
	काष्ठा anybuss_client *client = cd->client;

	अगर (!cd->घातer_on)
		वापस 0;
	disable_irq(cd->irq);
	reset_निश्चित(cd);
	atomic_set(&cd->ind_ab, IND_AB_UPDATED);
	अगर (client->on_online_changed)
		client->on_online_changed(client, false);
	cd->घातer_on = false;
	वापस 0;
पूर्ण

अटल पूर्णांक task_fn_घातer_on_2(काष्ठा anybuss_host *cd,
			      काष्ठा ab_task *t)
अणु
	अगर (completion_करोne(&cd->card_boot)) अणु
		cd->घातer_on = true;
		वापस 0;
	पूर्ण
	अगर (समय_after(jअगरfies, t->start_jअगरfies + TIMEOUT)) अणु
		disable_irq(cd->irq);
		reset_निश्चित(cd);
		dev_err(cd->dev, "power on timed out");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक task_fn_घातer_on(काष्ठा anybuss_host *cd,
			    काष्ठा ab_task *t)
अणु
	अचिन्हित पूर्णांक dummy;

	अगर (cd->घातer_on)
		वापस 0;
	/*
	 * anybus करोcs: prevent false 'init done' पूर्णांकerrupt by
	 * करोing a dummy पढ़ो of IND_AB रेजिस्टर जबतक in reset.
	 */
	regmap_पढ़ो(cd->regmap, REG_IND_AB, &dummy);
	reinit_completion(&cd->card_boot);
	enable_irq(cd->irq);
	reset_deनिश्चित(cd);
	t->task_fn = task_fn_घातer_on_2;
	वापस -EINPROGRESS;
पूर्ण

पूर्णांक anybuss_set_घातer(काष्ठा anybuss_client *client, bool घातer_on)
अणु
	काष्ठा anybuss_host *cd = client->host;
	काष्ठा ab_task *t;
	पूर्णांक err;

	t = ab_task_create_get(cd->qcache, घातer_on ?
				task_fn_घातer_on : task_fn_घातer_off);
	अगर (!t)
		वापस -ENOMEM;
	err = ab_task_enqueue_रुको(t, cd->घातerq, &cd->qlock, &cd->wq);
	ab_task_put(t);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_set_घातer);

/* ---------------------------- area tasks ------------------------ */

अटल पूर्णांक task_fn_area_3(काष्ठा anybuss_host *cd, काष्ठा ab_task *t)
अणु
	काष्ठा area_priv *pd = &t->area_pd;

	अगर (!cd->घातer_on)
		वापस -EIO;
	अगर (atomic_पढ़ो(&cd->ind_ab) & pd->flags) अणु
		/* area not released yet */
		अगर (समय_after(jअगरfies, t->start_jअगरfies + TIMEOUT))
			वापस -ETIMEDOUT;
		वापस -EINPROGRESS;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक task_fn_area_2(काष्ठा anybuss_host *cd, काष्ठा ab_task *t)
अणु
	काष्ठा area_priv *pd = &t->area_pd;
	अचिन्हित पूर्णांक ind_ap;
	पूर्णांक ret;

	अगर (!cd->घातer_on)
		वापस -EIO;
	regmap_पढ़ो(cd->regmap, REG_IND_AP, &ind_ap);
	अगर (!(atomic_पढ़ो(&cd->ind_ab) & pd->flags)) अणु
		/* we करोn't own the area yet */
		अगर (समय_after(jअगरfies, t->start_jअगरfies + TIMEOUT)) अणु
			dev_warn(cd->dev, "timeout waiting for area");
			dump_stack();
			वापस -ETIMEDOUT;
		पूर्ण
		वापस -EINPROGRESS;
	पूर्ण
	/* we own the area, करो what we're here to करो */
	अगर (pd->is_ग_लिखो)
		regmap_bulk_ग_लिखो(cd->regmap, pd->addr, pd->buf,
				  pd->count);
	अन्यथा
		regmap_bulk_पढ़ो(cd->regmap, pd->addr, pd->buf,
				 pd->count);
	/* ask to release the area, must use unlocked release */
	ind_ap &= ~IND_AP_ABITS;
	ind_ap |= pd->flags;
	ret = ग_लिखो_ind_ap(cd->regmap, ind_ap);
	अगर (ret)
		वापस ret;
	t->task_fn = task_fn_area_3;
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक task_fn_area(काष्ठा anybuss_host *cd, काष्ठा ab_task *t)
अणु
	काष्ठा area_priv *pd = &t->area_pd;
	अचिन्हित पूर्णांक ind_ap;
	पूर्णांक ret;

	अगर (!cd->घातer_on)
		वापस -EIO;
	regmap_पढ़ो(cd->regmap, REG_IND_AP, &ind_ap);
	/* ask to take the area */
	ind_ap &= ~IND_AP_ABITS;
	ind_ap |= pd->flags | IND_AP_ACTION | IND_AP_LOCK;
	ret = ग_लिखो_ind_ap(cd->regmap, ind_ap);
	अगर (ret)
		वापस ret;
	t->task_fn = task_fn_area_2;
	वापस -EINPROGRESS;
पूर्ण

अटल काष्ठा ab_task *
create_area_पढ़ोer(काष्ठा kmem_cache *qcache, u16 flags, u16 addr,
		   माप_प्रकार count)
अणु
	काष्ठा ab_task *t;
	काष्ठा area_priv *ap;

	t = ab_task_create_get(qcache, task_fn_area);
	अगर (!t)
		वापस शून्य;
	ap = &t->area_pd;
	ap->flags = flags;
	ap->addr = addr;
	ap->is_ग_लिखो = false;
	ap->count = count;
	वापस t;
पूर्ण

अटल काष्ठा ab_task *
create_area_ग_लिखोr(काष्ठा kmem_cache *qcache, u16 flags, u16 addr,
		   स्थिर व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा ab_task *t;
	काष्ठा area_priv *ap;

	t = ab_task_create_get(qcache, task_fn_area);
	अगर (!t)
		वापस शून्य;
	ap = &t->area_pd;
	ap->flags = flags;
	ap->addr = addr;
	ap->is_ग_लिखो = true;
	ap->count = count;
	स_नकल(ap->buf, buf, count);
	वापस t;
पूर्ण

अटल काष्ठा ab_task *
create_area_user_ग_लिखोr(काष्ठा kmem_cache *qcache, u16 flags, u16 addr,
			स्थिर व्योम __user *buf, माप_प्रकार count)
अणु
	काष्ठा ab_task *t;
	काष्ठा area_priv *ap;

	t = ab_task_create_get(qcache, task_fn_area);
	अगर (!t)
		वापस ERR_PTR(-ENOMEM);
	ap = &t->area_pd;
	ap->flags = flags;
	ap->addr = addr;
	ap->is_ग_लिखो = true;
	ap->count = count;
	अगर (copy_from_user(ap->buf, buf, count)) अणु
		ab_task_put(t);
		वापस ERR_PTR(-EFAULT);
	पूर्ण
	वापस t;
पूर्ण

अटल bool area_range_ok(u16 addr, माप_प्रकार count, u16 area_start,
			  माप_प्रकार area_sz)
अणु
	u16 area_end_ex = area_start + area_sz;
	u16 addr_end_ex;

	अगर (addr < area_start)
		वापस false;
	अगर (addr >= area_end_ex)
		वापस false;
	addr_end_ex = addr + count;
	अगर (addr_end_ex > area_end_ex)
		वापस false;
	वापस true;
पूर्ण

/* -------------------------- mailbox tasks ----------------------- */

अटल पूर्णांक task_fn_mbox_2(काष्ठा anybuss_host *cd, काष्ठा ab_task *t)
अणु
	काष्ठा mbox_priv *pd = &t->mbox_pd;
	अचिन्हित पूर्णांक ind_ap;

	अगर (!cd->घातer_on)
		वापस -EIO;
	regmap_पढ़ो(cd->regmap, REG_IND_AP, &ind_ap);
	अगर (((atomic_पढ़ो(&cd->ind_ab) ^ ind_ap) & IND_AX_MOUT) == 0) अणु
		/* output message not here */
		अगर (समय_after(jअगरfies, t->start_jअगरfies + TIMEOUT))
			वापस -ETIMEDOUT;
		वापस -EINPROGRESS;
	पूर्ण
	/* grab the वापसed header and msg */
	regmap_bulk_पढ़ो(cd->regmap, MBOX_OUT_AREA, &pd->hdr,
			 माप(pd->hdr));
	regmap_bulk_पढ़ो(cd->regmap, MBOX_OUT_AREA + माप(pd->hdr),
			 pd->msg, pd->msg_in_sz);
	/* tell anybus we've consumed the message */
	ind_ap ^= IND_AX_MOUT;
	वापस ग_लिखो_ind_ap(cd->regmap, ind_ap);
पूर्ण

अटल पूर्णांक task_fn_mbox(काष्ठा anybuss_host *cd, काष्ठा ab_task *t)
अणु
	काष्ठा mbox_priv *pd = &t->mbox_pd;
	अचिन्हित पूर्णांक ind_ap;
	पूर्णांक ret;

	अगर (!cd->घातer_on)
		वापस -EIO;
	regmap_पढ़ो(cd->regmap, REG_IND_AP, &ind_ap);
	अगर ((atomic_पढ़ो(&cd->ind_ab) ^ ind_ap) & IND_AX_MIN) अणु
		/* mbox input area busy */
		अगर (समय_after(jअगरfies, t->start_jअगरfies + TIMEOUT))
			वापस -ETIMEDOUT;
		वापस -EINPROGRESS;
	पूर्ण
	/* ग_लिखो the header and msg to input area */
	regmap_bulk_ग_लिखो(cd->regmap, MBOX_IN_AREA, &pd->hdr,
			  माप(pd->hdr));
	regmap_bulk_ग_लिखो(cd->regmap, MBOX_IN_AREA + माप(pd->hdr),
			  pd->msg, pd->msg_out_sz);
	/* tell anybus we gave it a message */
	ind_ap ^= IND_AX_MIN;
	ret = ग_लिखो_ind_ap(cd->regmap, ind_ap);
	अगर (ret)
		वापस ret;
	t->start_jअगरfies = jअगरfies;
	t->task_fn = task_fn_mbox_2;
	वापस -EINPROGRESS;
पूर्ण

अटल व्योम log_invalid_other(काष्ठा device *dev,
			      काष्ठा anybus_mbox_hdr *hdr)
अणु
	माप_प्रकार ext_offs = ARRAY_SIZE(hdr->extended) - 1;
	u16 code = be16_to_cpu(hdr->extended[ext_offs]);

	dev_err(dev, "   Invalid other: [0x%02X]", code);
पूर्ण

अटल स्थिर अक्षर * स्थिर EMSGS[] = अणु
	"Invalid Message ID",
	"Invalid Message Type",
	"Invalid Command",
	"Invalid Data Size",
	"Message Header Malformed (offset 008h)",
	"Message Header Malformed (offset 00Ah)",
	"Message Header Malformed (offset 00Ch - 00Dh)",
	"Invalid Address",
	"Invalid Response",
	"Flash Config Error",
पूर्ण;

अटल पूर्णांक mbox_cmd_err(काष्ठा device *dev, काष्ठा mbox_priv *mpriv)
अणु
	पूर्णांक i;
	u8 ecode;
	काष्ठा anybus_mbox_hdr *hdr = &mpriv->hdr;
	u16 info = be16_to_cpu(hdr->info);
	u8 *phdr = (u8 *)hdr;
	u8 *pmsg = mpriv->msg;

	अगर (!(info & 0x8000))
		वापस 0;
	ecode = (info >> 8) & 0x0F;
	dev_err(dev, "mailbox command failed:");
	अगर (ecode == 0x0F)
		log_invalid_other(dev, hdr);
	अन्यथा अगर (ecode < ARRAY_SIZE(EMSGS))
		dev_err(dev, "   Error code: %s (0x%02X)",
			EMSGS[ecode], ecode);
	अन्यथा
		dev_err(dev, "   Error code: 0x%02X\n", ecode);
	dev_err(dev, "Failed command:");
	dev_err(dev, "Message Header:");
	क्रम (i = 0; i < माप(mpriv->hdr); i += 2)
		dev_err(dev, "%02X%02X", phdr[i], phdr[i + 1]);
	dev_err(dev, "Message Data:");
	क्रम (i = 0; i < mpriv->msg_in_sz; i += 2)
		dev_err(dev, "%02X%02X", pmsg[i], pmsg[i + 1]);
	dev_err(dev, "Stack dump:");
	dump_stack();
	वापस -EIO;
पूर्ण

अटल पूर्णांक _anybus_mbox_cmd(काष्ठा anybuss_host *cd,
			    u16 cmd_num, bool is_fb_cmd,
				स्थिर व्योम *msg_out, माप_प्रकार msg_out_sz,
				व्योम *msg_in, माप_प्रकार msg_in_sz,
				स्थिर व्योम *ext, माप_प्रकार ext_sz)
अणु
	काष्ठा ab_task *t;
	काष्ठा mbox_priv *pd;
	काष्ठा anybus_mbox_hdr *h;
	माप_प्रकार msg_sz = max(msg_in_sz, msg_out_sz);
	u16 info;
	पूर्णांक err;

	अगर (msg_sz > MAX_MBOX_MSG_SZ)
		वापस -EINVAL;
	अगर (ext && ext_sz > माप(h->extended))
		वापस -EINVAL;
	t = ab_task_create_get(cd->qcache, task_fn_mbox);
	अगर (!t)
		वापस -ENOMEM;
	pd = &t->mbox_pd;
	h = &pd->hdr;
	info = is_fb_cmd ? INFO_TYPE_FB : INFO_TYPE_APP;
	/*
	 * prevent uninitialized memory in the header from being sent
	 * across the anybus
	 */
	स_रखो(h, 0, माप(*h));
	h->info = cpu_to_be16(info | INFO_COMMAND);
	h->cmd_num = cpu_to_be16(cmd_num);
	h->data_size = cpu_to_be16(msg_out_sz);
	h->frame_count = cpu_to_be16(1);
	h->frame_num = cpu_to_be16(1);
	h->offset_high = cpu_to_be16(0);
	h->offset_low = cpu_to_be16(0);
	अगर (ext)
		स_नकल(h->extended, ext, ext_sz);
	स_नकल(pd->msg, msg_out, msg_out_sz);
	pd->msg_out_sz = msg_out_sz;
	pd->msg_in_sz = msg_in_sz;
	err = ab_task_enqueue_रुको(t, cd->घातerq, &cd->qlock, &cd->wq);
	अगर (err)
		जाओ out;
	/*
	 * mailbox mechanism worked ok, but maybe the mbox response
	 * contains an error ?
	 */
	err = mbox_cmd_err(cd->dev, pd);
	अगर (err)
		जाओ out;
	स_नकल(msg_in, pd->msg, msg_in_sz);
out:
	ab_task_put(t);
	वापस err;
पूर्ण

/* ------------------------ anybus queues ------------------------ */

अटल व्योम process_q(काष्ठा anybuss_host *cd, काष्ठा kfअगरo *q)
अणु
	काष्ठा ab_task *t;
	पूर्णांक ret;

	ret = kfअगरo_out_peek(q, &t, माप(t));
	अगर (!ret)
		वापस;
	t->result = t->task_fn(cd, t);
	अगर (t->result != -EINPROGRESS)
		ab_task_dequeue_finish_put(q, cd);
पूर्ण

अटल bool qs_have_work(काष्ठा kfअगरo *qs, माप_प्रकार num)
अणु
	माप_प्रकार i;
	काष्ठा ab_task *t;
	पूर्णांक ret;

	क्रम (i = 0; i < num; i++, qs++) अणु
		ret = kfअगरo_out_peek(qs, &t, माप(t));
		अगर (ret && (t->result != -EINPROGRESS))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम process_qs(काष्ठा anybuss_host *cd)
अणु
	माप_प्रकार i;
	काष्ठा kfअगरo *qs = cd->qs;
	माप_प्रकार nqs = ARRAY_SIZE(cd->qs);

	क्रम (i = 0; i < nqs; i++, qs++)
		process_q(cd, qs);
पूर्ण

अटल व्योम softपूर्णांक_ack(काष्ठा anybuss_host *cd)
अणु
	अचिन्हित पूर्णांक ind_ap;

	cd->softपूर्णांक_pending = false;
	अगर (!cd->घातer_on)
		वापस;
	regmap_पढ़ो(cd->regmap, REG_IND_AP, &ind_ap);
	ind_ap &= ~IND_AX_EVNT;
	ind_ap |= atomic_पढ़ो(&cd->ind_ab) & IND_AX_EVNT;
	ग_लिखो_ind_ap(cd->regmap, ind_ap);
पूर्ण

अटल व्योम process_softपूर्णांक(काष्ठा anybuss_host *cd)
अणु
	काष्ठा anybuss_client *client = cd->client;
	अटल स्थिर u8 zero;
	पूर्णांक ret;
	अचिन्हित पूर्णांक ind_ap, ev;
	काष्ठा ab_task *t;

	अगर (!cd->घातer_on)
		वापस;
	अगर (cd->softपूर्णांक_pending)
		वापस;
	regmap_पढ़ो(cd->regmap, REG_IND_AP, &ind_ap);
	अगर (!((atomic_पढ़ो(&cd->ind_ab) ^ ind_ap) & IND_AX_EVNT))
		वापस;
	/* process software पूर्णांकerrupt */
	regmap_पढ़ो(cd->regmap, REG_EVENT_CAUSE, &ev);
	अगर (ev & EVENT_CAUSE_FBON) अणु
		अगर (client->on_online_changed)
			client->on_online_changed(client, true);
		dev_dbg(cd->dev, "Fieldbus ON");
	पूर्ण
	अगर (ev & EVENT_CAUSE_FBOF) अणु
		अगर (client->on_online_changed)
			client->on_online_changed(client, false);
		dev_dbg(cd->dev, "Fieldbus OFF");
	पूर्ण
	अगर (ev & EVENT_CAUSE_DC) अणु
		अगर (client->on_area_updated)
			client->on_area_updated(client);
		dev_dbg(cd->dev, "Fieldbus data changed");
	पूर्ण
	/*
	 * reset the event cause bits.
	 * this must be करोne जबतक owning the fbctrl area, so we'll
	 * enqueue a task to करो that.
	 */
	t = create_area_ग_लिखोr(cd->qcache, IND_AX_FBCTRL,
			       REG_EVENT_CAUSE, &zero, माप(zero));
	अगर (!t) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	t->करोne_fn = softपूर्णांक_ack;
	ret = ab_task_enqueue(t, cd->घातerq, &cd->qlock, &cd->wq);
	ab_task_put(t);
	cd->softपूर्णांक_pending = true;
out:
	WARN_ON(ret);
	अगर (ret)
		softपूर्णांक_ack(cd);
पूर्ण

अटल पूर्णांक qthपढ़ो_fn(व्योम *data)
अणु
	काष्ठा anybuss_host *cd = data;
	काष्ठा kfअगरo *qs = cd->qs;
	माप_प्रकार nqs = ARRAY_SIZE(cd->qs);
	अचिन्हित पूर्णांक ind_ab;

	/*
	 * this kernel thपढ़ो has exclusive access to the anybus's memory.
	 * only exception: the IND_AB रेजिस्टर, which is accessed exclusively
	 * by the पूर्णांकerrupt service routine (ISR). This thपढ़ो must not touch
	 * the IND_AB रेजिस्टर, but it करोes require access to its value.
	 *
	 * the पूर्णांकerrupt service routine stores the रेजिस्टर's value in
	 * cd->ind_ab (an atomic_t), where we may safely access it, with the
	 * understanding that it can be modअगरied by the ISR at any समय.
	 */

	जबतक (!kthपढ़ो_should_stop()) अणु
		/*
		 * make a local copy of IND_AB, so we can go around the loop
		 * again in हाल it changed जबतक processing queues and softपूर्णांक.
		 */
		ind_ab = atomic_पढ़ो(&cd->ind_ab);
		process_qs(cd);
		process_softपूर्णांक(cd);
		रुको_event_समयout(cd->wq,
				   (atomic_पढ़ो(&cd->ind_ab) != ind_ab) ||
				qs_have_work(qs, nqs) ||
				kthपढ़ो_should_stop(),
			HZ);
		/*
		 * समय out so even 'stuck' tasks will run eventually,
		 * and can समय out.
		 */
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------ anybus exports ------------------------ */

पूर्णांक anybuss_start_init(काष्ठा anybuss_client *client,
		       स्थिर काष्ठा anybuss_memcfg *cfg)
अणु
	पूर्णांक ret;
	u16 op_mode;
	काष्ठा anybuss_host *cd = client->host;
	काष्ठा msg_anybus_init msg = अणु
		.input_io_len = cpu_to_be16(cfg->input_io),
		.input_dpram_len = cpu_to_be16(cfg->input_dpram),
		.input_total_len = cpu_to_be16(cfg->input_total),
		.output_io_len = cpu_to_be16(cfg->output_io),
		.output_dpram_len = cpu_to_be16(cfg->output_dpram),
		.output_total_len = cpu_to_be16(cfg->output_total),
		.notअगर_config = cpu_to_be16(0x000F),
		.wd_val = cpu_to_be16(0),
	पूर्ण;

	चयन (cfg->offl_mode) अणु
	हाल FIELDBUS_DEV_OFFL_MODE_CLEAR:
		op_mode = 0;
		अवरोध;
	हाल FIELDBUS_DEV_OFFL_MODE_FREEZE:
		op_mode = OP_MODE_FBFC;
		अवरोध;
	हाल FIELDBUS_DEV_OFFL_MODE_SET:
		op_mode = OP_MODE_FBS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	msg.op_mode = cpu_to_be16(op_mode | OP_MODE_CD);
	ret = _anybus_mbox_cmd(cd, CMD_START_INIT, false, शून्य, 0,
			       शून्य, 0, शून्य, 0);
	अगर (ret)
		वापस ret;
	वापस _anybus_mbox_cmd(cd, CMD_ANYBUS_INIT, false,
			&msg, माप(msg), शून्य, 0, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_start_init);

पूर्णांक anybuss_finish_init(काष्ठा anybuss_client *client)
अणु
	काष्ठा anybuss_host *cd = client->host;

	वापस _anybus_mbox_cmd(cd, CMD_END_INIT, false, शून्य, 0,
					शून्य, 0, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_finish_init);

पूर्णांक anybuss_पढ़ो_fbctrl(काष्ठा anybuss_client *client, u16 addr,
			व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा anybuss_host *cd = client->host;
	काष्ठा ab_task *t;
	पूर्णांक ret;

	अगर (count == 0)
		वापस 0;
	अगर (!area_range_ok(addr, count, FBCTRL_AREA,
			   MAX_FBCTRL_AREA_SZ))
		वापस -EFAULT;
	t = create_area_पढ़ोer(cd->qcache, IND_AX_FBCTRL, addr, count);
	अगर (!t)
		वापस -ENOMEM;
	ret = ab_task_enqueue_रुको(t, cd->घातerq, &cd->qlock, &cd->wq);
	अगर (ret)
		जाओ out;
	स_नकल(buf, t->area_pd.buf, count);
out:
	ab_task_put(t);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_पढ़ो_fbctrl);

पूर्णांक anybuss_ग_लिखो_input(काष्ठा anybuss_client *client,
			स्थिर अक्षर __user *buf, माप_प्रकार size,
				loff_t *offset)
अणु
	sमाप_प्रकार len = min_t(loff_t, MAX_DATA_AREA_SZ - *offset, size);
	काष्ठा anybuss_host *cd = client->host;
	काष्ठा ab_task *t;
	पूर्णांक ret;

	अगर (len <= 0)
		वापस 0;
	t = create_area_user_ग_लिखोr(cd->qcache, IND_AX_IN,
				    DATA_IN_AREA + *offset, buf, len);
	अगर (IS_ERR(t))
		वापस PTR_ERR(t);
	ret = ab_task_enqueue_रुको(t, cd->घातerq, &cd->qlock, &cd->wq);
	ab_task_put(t);
	अगर (ret)
		वापस ret;
	/* success */
	*offset += len;
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_ग_लिखो_input);

पूर्णांक anybuss_पढ़ो_output(काष्ठा anybuss_client *client,
			अक्षर __user *buf, माप_प्रकार size,
				loff_t *offset)
अणु
	sमाप_प्रकार len = min_t(loff_t, MAX_DATA_AREA_SZ - *offset, size);
	काष्ठा anybuss_host *cd = client->host;
	काष्ठा ab_task *t;
	पूर्णांक ret;

	अगर (len <= 0)
		वापस 0;
	t = create_area_पढ़ोer(cd->qcache, IND_AX_OUT,
			       DATA_OUT_AREA + *offset, len);
	अगर (!t)
		वापस -ENOMEM;
	ret = ab_task_enqueue_रुको(t, cd->घातerq, &cd->qlock, &cd->wq);
	अगर (ret)
		जाओ out;
	अगर (copy_to_user(buf, t->area_pd.buf, len))
		ret = -EFAULT;
out:
	ab_task_put(t);
	अगर (ret)
		वापस ret;
	/* success */
	*offset += len;
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_पढ़ो_output);

पूर्णांक anybuss_send_msg(काष्ठा anybuss_client *client, u16 cmd_num,
		     स्थिर व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा anybuss_host *cd = client->host;

	वापस _anybus_mbox_cmd(cd, cmd_num, true, buf, count, शून्य, 0,
					शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_send_msg);

पूर्णांक anybuss_send_ext(काष्ठा anybuss_client *client, u16 cmd_num,
		     स्थिर व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा anybuss_host *cd = client->host;

	वापस _anybus_mbox_cmd(cd, cmd_num, true, शून्य, 0, शून्य, 0,
					buf, count);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_send_ext);

पूर्णांक anybuss_recv_msg(काष्ठा anybuss_client *client, u16 cmd_num,
		     व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा anybuss_host *cd = client->host;

	वापस _anybus_mbox_cmd(cd, cmd_num, true, शून्य, 0, buf, count,
					शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_recv_msg);

/* ------------------------ bus functions ------------------------ */

अटल पूर्णांक anybus_bus_match(काष्ठा device *dev,
			    काष्ठा device_driver *drv)
अणु
	काष्ठा anybuss_client_driver *adrv =
		to_anybuss_client_driver(drv);
	काष्ठा anybuss_client *adev =
		to_anybuss_client(dev);

	वापस adrv->anybus_id == be16_to_cpu(adev->anybus_id);
पूर्ण

अटल पूर्णांक anybus_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा anybuss_client_driver *adrv =
		to_anybuss_client_driver(dev->driver);
	काष्ठा anybuss_client *adev =
		to_anybuss_client(dev);

	अगर (!adrv->probe)
		वापस -ENODEV;
	वापस adrv->probe(adev);
पूर्ण

अटल पूर्णांक anybus_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा anybuss_client_driver *adrv =
		to_anybuss_client_driver(dev->driver);

	अगर (adrv->हटाओ)
		वापस adrv->हटाओ(to_anybuss_client(dev));
	वापस 0;
पूर्ण

अटल काष्ठा bus_type anybus_bus = अणु
	.name		= "anybuss",
	.match		= anybus_bus_match,
	.probe		= anybus_bus_probe,
	.हटाओ		= anybus_bus_हटाओ,
पूर्ण;

पूर्णांक anybuss_client_driver_रेजिस्टर(काष्ठा anybuss_client_driver *drv)
अणु
	drv->driver.bus = &anybus_bus;
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_client_driver_रेजिस्टर);

व्योम anybuss_client_driver_unरेजिस्टर(काष्ठा anybuss_client_driver *drv)
अणु
	वापस driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_client_driver_unरेजिस्टर);

अटल व्योम client_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_anybuss_client(dev));
पूर्ण

अटल पूर्णांक taskq_alloc(काष्ठा device *dev, काष्ठा kfअगरo *q)
अणु
	व्योम *buf;
	माप_प्रकार size = 64 * माप(काष्ठा ab_task *);

	buf = devm_kzalloc(dev, size, GFP_KERNEL);
	अगर (!buf)
		वापस -EIO;
	वापस kfअगरo_init(q, buf, size);
पूर्ण

अटल पूर्णांक anybus_of_get_host_idx(काष्ठा device_node *np)
अणु
	स्थिर __be32 *host_idx;

	host_idx = of_get_address(np, 0, शून्य, शून्य);
	अगर (!host_idx)
		वापस -ENOENT;
	वापस __be32_to_cpu(*host_idx);
पूर्ण

अटल काष्ठा device_node *
anybus_of_find_child_device(काष्ठा device *dev, पूर्णांक host_idx)
अणु
	काष्ठा device_node *node;

	अगर (!dev || !dev->of_node)
		वापस शून्य;
	क्रम_each_child_of_node(dev->of_node, node) अणु
		अगर (anybus_of_get_host_idx(node) == host_idx)
			वापस node;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा anybuss_host * __must_check
anybuss_host_common_probe(काष्ठा device *dev,
			  स्थिर काष्ठा anybuss_ops *ops)
अणु
	पूर्णांक ret, i;
	u8 val[4];
	__be16 fieldbus_type;
	काष्ठा anybuss_host *cd;

	cd = devm_kzalloc(dev, माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस ERR_PTR(-ENOMEM);
	cd->dev = dev;
	cd->host_idx = ops->host_idx;
	init_completion(&cd->card_boot);
	init_रुकोqueue_head(&cd->wq);
	क्रम (i = 0; i < ARRAY_SIZE(cd->qs); i++) अणु
		ret = taskq_alloc(dev, &cd->qs[i]);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण
	अगर (WARN_ON(ARRAY_SIZE(cd->qs) < 3))
		वापस ERR_PTR(-EINVAL);
	cd->घातerq = &cd->qs[0];
	cd->mboxq = &cd->qs[1];
	cd->areaq = &cd->qs[2];
	cd->reset = ops->reset;
	अगर (!cd->reset)
		वापस ERR_PTR(-EINVAL);
	cd->regmap = ops->regmap;
	अगर (!cd->regmap)
		वापस ERR_PTR(-EINVAL);
	spin_lock_init(&cd->qlock);
	cd->qcache = kmem_cache_create(dev_name(dev),
				       माप(काष्ठा ab_task), 0, 0, शून्य);
	अगर (!cd->qcache)
		वापस ERR_PTR(-ENOMEM);
	cd->irq = ops->irq;
	अगर (cd->irq <= 0) अणु
		ret = -EINVAL;
		जाओ err_qcache;
	पूर्ण
	/*
	 * use a dpram test to check अगर a card is present, this is only
	 * possible जबतक in reset.
	 */
	reset_निश्चित(cd);
	अगर (test_dpram(cd->regmap)) अणु
		dev_err(dev, "no Anybus-S card in slot");
		ret = -ENODEV;
		जाओ err_qcache;
	पूर्ण
	ret = devm_request_thपढ़ोed_irq(dev, cd->irq, शून्य, irq_handler,
					IRQF_ONESHOT, dev_name(dev), cd);
	अगर (ret) अणु
		dev_err(dev, "could not request irq");
		जाओ err_qcache;
	पूर्ण
	/*
	 * startup sequence:
	 *   perक्रमm dummy IND_AB पढ़ो to prevent false 'init done' irq
	 *     (alपढ़ोy करोne by test_dpram() above)
	 *   release reset
	 *   रुको क्रम first पूर्णांकerrupt
	 *   पूर्णांकerrupt came in: पढ़ोy to go !
	 */
	reset_deनिश्चित(cd);
	अगर (!रुको_क्रम_completion_समयout(&cd->card_boot, TIMEOUT)) अणु
		ret = -ETIMEDOUT;
		जाओ err_reset;
	पूर्ण
	/*
	 * according to the anybus करोcs, we're allowed to पढ़ो these
	 * without handshaking / reserving the area
	 */
	dev_info(dev, "Anybus-S card detected");
	regmap_bulk_पढ़ो(cd->regmap, REG_BOOTLOADER_V, val, 2);
	dev_info(dev, "Bootloader version: %02X%02X",
		 val[0], val[1]);
	regmap_bulk_पढ़ो(cd->regmap, REG_API_V, val, 2);
	dev_info(dev, "API version: %02X%02X", val[0], val[1]);
	regmap_bulk_पढ़ो(cd->regmap, REG_FIELDBUS_V, val, 2);
	dev_info(dev, "Fieldbus version: %02X%02X", val[0], val[1]);
	regmap_bulk_पढ़ो(cd->regmap, REG_SERIAL_NO, val, 4);
	dev_info(dev, "Serial number: %02X%02X%02X%02X",
		 val[0], val[1], val[2], val[3]);
	add_device_अक्रमomness(&val, 4);
	regmap_bulk_पढ़ो(cd->regmap, REG_FIELDBUS_TYPE, &fieldbus_type,
			 माप(fieldbus_type));
	dev_info(dev, "Fieldbus type: %04X", be16_to_cpu(fieldbus_type));
	regmap_bulk_पढ़ो(cd->regmap, REG_MODULE_SW_V, val, 2);
	dev_info(dev, "Module SW version: %02X%02X",
		 val[0], val[1]);
	/* put card back reset until a client driver releases it */
	disable_irq(cd->irq);
	reset_निश्चित(cd);
	atomic_set(&cd->ind_ab, IND_AB_UPDATED);
	/* fire up the queue thपढ़ो */
	cd->qthपढ़ो = kthपढ़ो_run(qthपढ़ो_fn, cd, dev_name(dev));
	अगर (IS_ERR(cd->qthपढ़ो)) अणु
		dev_err(dev, "could not create kthread");
		ret = PTR_ERR(cd->qthपढ़ो);
		जाओ err_reset;
	पूर्ण
	/*
	 * now advertise that we've detected a client device (card).
	 * the bus infraकाष्ठाure will match it to a client driver.
	 */
	cd->client = kzalloc(माप(*cd->client), GFP_KERNEL);
	अगर (!cd->client) अणु
		ret = -ENOMEM;
		जाओ err_kthपढ़ो;
	पूर्ण
	cd->client->anybus_id = fieldbus_type;
	cd->client->host = cd;
	cd->client->dev.bus = &anybus_bus;
	cd->client->dev.parent = dev;
	cd->client->dev.release = client_device_release;
	cd->client->dev.of_node =
		anybus_of_find_child_device(dev, cd->host_idx);
	dev_set_name(&cd->client->dev, "anybuss.card%d", cd->host_idx);
	ret = device_रेजिस्टर(&cd->client->dev);
	अगर (ret)
		जाओ err_device;
	वापस cd;
err_device:
	device_unरेजिस्टर(&cd->client->dev);
err_kthपढ़ो:
	kthपढ़ो_stop(cd->qthपढ़ो);
err_reset:
	reset_निश्चित(cd);
err_qcache:
	kmem_cache_destroy(cd->qcache);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_host_common_probe);

व्योम anybuss_host_common_हटाओ(काष्ठा anybuss_host *host)
अणु
	काष्ठा anybuss_host *cd = host;

	device_unरेजिस्टर(&cd->client->dev);
	kthपढ़ो_stop(cd->qthपढ़ो);
	reset_निश्चित(cd);
	kmem_cache_destroy(cd->qcache);
पूर्ण
EXPORT_SYMBOL_GPL(anybuss_host_common_हटाओ);

अटल व्योम host_release(व्योम *res)
अणु
	anybuss_host_common_हटाओ(res);
पूर्ण

काष्ठा anybuss_host * __must_check
devm_anybuss_host_common_probe(काष्ठा device *dev,
			       स्थिर काष्ठा anybuss_ops *ops)
अणु
	काष्ठा anybuss_host *host;
	पूर्णांक ret;

	host = anybuss_host_common_probe(dev, ops);
	अगर (IS_ERR(host))
		वापस host;

	ret = devm_add_action_or_reset(dev, host_release, host);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस host;
पूर्ण
EXPORT_SYMBOL_GPL(devm_anybuss_host_common_probe);

अटल पूर्णांक __init anybus_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&anybus_bus);
	अगर (ret)
		pr_err("could not register Anybus-S bus: %d\n", ret);
	वापस ret;
पूर्ण
module_init(anybus_init);

अटल व्योम __निकास anybus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&anybus_bus);
पूर्ण
module_निकास(anybus_निकास);

MODULE_DESCRIPTION("HMS Anybus-S Host Driver");
MODULE_AUTHOR("Sven Van Asbroeck <TheSven73@gmail.com>");
MODULE_LICENSE("GPL v2");
