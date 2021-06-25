<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL high level पूर्णांकerfaces
 *
 * Copyright 2011 IBM Corp.
 */

#घोषणा pr_fmt(fmt)	"opal: " fmt

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/kobject.h>
#समावेश <linux/delay.h>
#समावेश <linux/memblock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/console.h>
#समावेश <linux/sched/debug.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/imc-pmu.h>
#समावेश <यंत्र/bug.h>

#समावेश "powernv.h"

#घोषणा OPAL_MSG_QUEUE_MAX 16

काष्ठा opal_msg_node अणु
	काष्ठा list_head	list;
	काष्ठा opal_msg		msg;
पूर्ण;

अटल DEFINE_SPINLOCK(msg_list_lock);
अटल LIST_HEAD(msg_list);

/* /sys/firmware/opal */
काष्ठा kobject *opal_kobj;

काष्ठा opal अणु
	u64 base;
	u64 entry;
	u64 size;
पूर्ण opal;

काष्ठा mcheck_recoverable_range अणु
	u64 start_addr;
	u64 end_addr;
	u64 recover_addr;
पूर्ण;

अटल पूर्णांक msg_list_size;

अटल काष्ठा mcheck_recoverable_range *mc_recoverable_range;
अटल पूर्णांक mc_recoverable_range_len;

काष्ठा device_node *opal_node;
अटल DEFINE_SPINLOCK(opal_ग_लिखो_lock);
अटल काष्ठा atomic_notअगरier_head opal_msg_notअगरier_head[OPAL_MSG_TYPE_MAX];
अटल uपूर्णांक32_t opal_heartbeat;
अटल काष्ठा task_काष्ठा *kopald_tsk;
अटल काष्ठा opal_msg *opal_msg;
अटल u32 opal_msg_size __ro_after_init;

व्योम opal_configure_cores(व्योम)
अणु
	u64 reinit_flags = 0;

	/* Do the actual re-init, This will clobber all FPRs, VRs, etc...
	 *
	 * It will preserve non अस्थिर GPRs and HSPRG0/1. It will
	 * also restore HIDs and other SPRs to their original value
	 * but it might clobber a bunch.
	 */
#अगर_घोषित __BIG_ENDIAN__
	reinit_flags |= OPAL_REINIT_CPUS_HILE_BE;
#अन्यथा
	reinit_flags |= OPAL_REINIT_CPUS_HILE_LE;
#पूर्ण_अगर

	/*
	 * POWER9 always support running hash:
	 *  ie. Host hash  supports  hash guests
	 *      Host radix supports  hash/radix guests
	 */
	अगर (early_cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		reinit_flags |= OPAL_REINIT_CPUS_MMU_HASH;
		अगर (early_radix_enabled())
			reinit_flags |= OPAL_REINIT_CPUS_MMU_RADIX;
	पूर्ण

	opal_reinit_cpus(reinit_flags);

	/* Restore some bits */
	अगर (cur_cpu_spec->cpu_restore)
		cur_cpu_spec->cpu_restore();
पूर्ण

पूर्णांक __init early_init_dt_scan_opal(अचिन्हित दीर्घ node,
				   स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data)
अणु
	स्थिर व्योम *basep, *entryp, *sizep;
	पूर्णांक basesz, entrysz, runबारz;

	अगर (depth != 1 || म_भेद(uname, "ibm,opal") != 0)
		वापस 0;

	basep  = of_get_flat_dt_prop(node, "opal-base-address", &basesz);
	entryp = of_get_flat_dt_prop(node, "opal-entry-address", &entrysz);
	sizep = of_get_flat_dt_prop(node, "opal-runtime-size", &runबारz);

	अगर (!basep || !entryp || !sizep)
		वापस 1;

	opal.base = of_पढ़ो_number(basep, basesz/4);
	opal.entry = of_पढ़ो_number(entryp, entrysz/4);
	opal.size = of_पढ़ो_number(sizep, runबारz/4);

	pr_debug("OPAL Base  = 0x%llx (basep=%p basesz=%d)\n",
		 opal.base, basep, basesz);
	pr_debug("OPAL Entry = 0x%llx (entryp=%p basesz=%d)\n",
		 opal.entry, entryp, entrysz);
	pr_debug("OPAL Entry = 0x%llx (sizep=%p runtimesz=%d)\n",
		 opal.size, sizep, runबारz);

	अगर (of_flat_dt_is_compatible(node, "ibm,opal-v3")) अणु
		घातerpc_firmware_features |= FW_FEATURE_OPAL;
		pr_debug("OPAL detected !\n");
	पूर्ण अन्यथा अणु
		panic("OPAL != V3 detected, no longer supported.\n");
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक __init early_init_dt_scan_recoverable_ranges(अचिन्हित दीर्घ node,
				   स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data)
अणु
	पूर्णांक i, psize, size;
	स्थिर __be32 *prop;

	अगर (depth != 1 || म_भेद(uname, "ibm,opal") != 0)
		वापस 0;

	prop = of_get_flat_dt_prop(node, "mcheck-recoverable-ranges", &psize);

	अगर (!prop)
		वापस 1;

	pr_debug("Found machine check recoverable ranges.\n");

	/*
	 * Calculate number of available entries.
	 *
	 * Each recoverable address range entry is (start address, len,
	 * recovery address), 2 cells each क्रम start and recovery address,
	 * 1 cell क्रम len, totalling 5 cells per entry.
	 */
	mc_recoverable_range_len = psize / (माप(*prop) * 5);

	/* Sanity check */
	अगर (!mc_recoverable_range_len)
		वापस 1;

	/* Size required to hold all the entries. */
	size = mc_recoverable_range_len *
			माप(काष्ठा mcheck_recoverable_range);

	/*
	 * Allocate a buffer to hold the MC recoverable ranges.
	 */
	mc_recoverable_range = memblock_alloc(size, __alignof__(u64));
	अगर (!mc_recoverable_range)
		panic("%s: Failed to allocate %u bytes align=0x%lx\n",
		      __func__, size, __alignof__(u64));

	क्रम (i = 0; i < mc_recoverable_range_len; i++) अणु
		mc_recoverable_range[i].start_addr =
					of_पढ़ो_number(prop + (i * 5) + 0, 2);
		mc_recoverable_range[i].end_addr =
					mc_recoverable_range[i].start_addr +
					of_पढ़ो_number(prop + (i * 5) + 2, 1);
		mc_recoverable_range[i].recover_addr =
					of_पढ़ो_number(prop + (i * 5) + 3, 2);

		pr_debug("Machine check recoverable range: %llx..%llx: %llx\n",
				mc_recoverable_range[i].start_addr,
				mc_recoverable_range[i].end_addr,
				mc_recoverable_range[i].recover_addr);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __init opal_रेजिस्टर_exception_handlers(व्योम)
अणु
#अगर_घोषित __BIG_ENDIAN__
	u64 glue;

	अगर (!(घातerpc_firmware_features & FW_FEATURE_OPAL))
		वापस -ENODEV;

	/* Hookup some exception handlers except machine check. We use the
	 * fwnmi area at 0x7000 to provide the glue space to OPAL
	 */
	glue = 0x7000;

	/*
	 * Only ancient OPAL firmware requires this.
	 * Specअगरically, firmware from FW810.00 (released June 2014)
	 * through FW810.20 (Released October 2014).
	 *
	 * Check अगर we are running on newer (post Oct 2014) firmware that
	 * exports the OPAL_HANDLE_HMI token. If yes, then करोn't ask OPAL to
	 * patch the HMI पूर्णांकerrupt and we catch it directly in Linux.
	 *
	 * For older firmware (i.e < FW810.20), we fallback to old behavior and
	 * let OPAL patch the HMI vector and handle it inside OPAL firmware.
	 *
	 * For newer firmware we catch/handle the HMI directly in Linux.
	 */
	अगर (!opal_check_token(OPAL_HANDLE_HMI)) अणु
		pr_info("Old firmware detected, OPAL handles HMIs.\n");
		opal_रेजिस्टर_exception_handler(
				OPAL_HYPERVISOR_MAINTEन_अंकCE_HANDLER,
				0, glue);
		glue += 128;
	पूर्ण

	/*
	 * Only applicable to ancient firmware, all modern
	 * (post March 2015/skiboot 5.0) firmware will just वापस
	 * OPAL_UNSUPPORTED.
	 */
	opal_रेजिस्टर_exception_handler(OPAL_SOFTPATCH_HANDLER, 0, glue);
#पूर्ण_अगर

	वापस 0;
पूर्ण
machine_early_initcall(घातernv, opal_रेजिस्टर_exception_handlers);

अटल व्योम queue_replay_msg(व्योम *msg)
अणु
	काष्ठा opal_msg_node *msg_node;

	अगर (msg_list_size < OPAL_MSG_QUEUE_MAX) अणु
		msg_node = kzalloc(माप(*msg_node), GFP_ATOMIC);
		अगर (msg_node) अणु
			INIT_LIST_HEAD(&msg_node->list);
			स_नकल(&msg_node->msg, msg, माप(काष्ठा opal_msg));
			list_add_tail(&msg_node->list, &msg_list);
			msg_list_size++;
		पूर्ण अन्यथा
			pr_warn_once("message queue no memory\n");

		अगर (msg_list_size >= OPAL_MSG_QUEUE_MAX)
			pr_warn_once("message queue full\n");
	पूर्ण
पूर्ण

अटल व्योम dequeue_replay_msg(क्रमागत opal_msg_type msg_type)
अणु
	काष्ठा opal_msg_node *msg_node, *पंचांगp;

	list_क्रम_each_entry_safe(msg_node, पंचांगp, &msg_list, list) अणु
		अगर (be32_to_cpu(msg_node->msg.msg_type) != msg_type)
			जारी;

		atomic_notअगरier_call_chain(&opal_msg_notअगरier_head[msg_type],
					msg_type,
					&msg_node->msg);

		list_del(&msg_node->list);
		kमुक्त(msg_node);
		msg_list_size--;
	पूर्ण
पूर्ण

/*
 * Opal message notअगरier based on message type. Allow subscribers to get
 * notअगरied क्रम specअगरic messgae type.
 */
पूर्णांक opal_message_notअगरier_रेजिस्टर(क्रमागत opal_msg_type msg_type,
					काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!nb || msg_type >= OPAL_MSG_TYPE_MAX) अणु
		pr_warn("%s: Invalid arguments, msg_type:%d\n",
			__func__, msg_type);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&msg_list_lock, flags);
	ret = atomic_notअगरier_chain_रेजिस्टर(
		&opal_msg_notअगरier_head[msg_type], nb);

	/*
	 * If the registration succeeded, replay any queued messages that came
	 * in prior to the notअगरier chain registration. msg_list_lock held here
	 * to ensure they're delivered prior to any subsequent messages.
	 */
	अगर (ret == 0)
		dequeue_replay_msg(msg_type);

	spin_unlock_irqrestore(&msg_list_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(opal_message_notअगरier_रेजिस्टर);

पूर्णांक opal_message_notअगरier_unरेजिस्टर(क्रमागत opal_msg_type msg_type,
				     काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(
			&opal_msg_notअगरier_head[msg_type], nb);
पूर्ण
EXPORT_SYMBOL_GPL(opal_message_notअगरier_unरेजिस्टर);

अटल व्योम opal_message_करो_notअगरy(uपूर्णांक32_t msg_type, व्योम *msg)
अणु
	अचिन्हित दीर्घ flags;
	bool queued = false;

	spin_lock_irqsave(&msg_list_lock, flags);
	अगर (opal_msg_notअगरier_head[msg_type].head == शून्य) अणु
		/*
		 * Queue up the msg since no notअगरiers have रेजिस्टरed
		 * yet क्रम this msg_type.
		 */
		queue_replay_msg(msg);
		queued = true;
	पूर्ण
	spin_unlock_irqrestore(&msg_list_lock, flags);

	अगर (queued)
		वापस;

	/* notअगरy subscribers */
	atomic_notअगरier_call_chain(&opal_msg_notअगरier_head[msg_type],
					msg_type, msg);
पूर्ण

अटल व्योम opal_handle_message(व्योम)
अणु
	s64 ret;
	u32 type;

	ret = opal_get_msg(__pa(opal_msg), opal_msg_size);
	/* No opal message pending. */
	अगर (ret == OPAL_RESOURCE)
		वापस;

	/* check क्रम errors. */
	अगर (ret) अणु
		pr_warn("%s: Failed to retrieve opal message, err=%lld\n",
			__func__, ret);
		वापस;
	पूर्ण

	type = be32_to_cpu(opal_msg->msg_type);

	/* Sanity check */
	अगर (type >= OPAL_MSG_TYPE_MAX) अणु
		pr_warn_once("%s: Unknown message type: %u\n", __func__, type);
		वापस;
	पूर्ण
	opal_message_करो_notअगरy(type, (व्योम *)opal_msg);
पूर्ण

अटल irqवापस_t opal_message_notअगरy(पूर्णांक irq, व्योम *data)
अणु
	opal_handle_message();
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init opal_message_init(काष्ठा device_node *opal_node)
अणु
	पूर्णांक ret, i, irq;

	ret = of_property_पढ़ो_u32(opal_node, "opal-msg-size", &opal_msg_size);
	अगर (ret) अणु
		pr_notice("Failed to read opal-msg-size property\n");
		opal_msg_size = माप(काष्ठा opal_msg);
	पूर्ण

	opal_msg = kदो_स्मृति(opal_msg_size, GFP_KERNEL);
	अगर (!opal_msg) अणु
		opal_msg_size = माप(काष्ठा opal_msg);
		/* Try to allocate fixed message size */
		opal_msg = kदो_स्मृति(opal_msg_size, GFP_KERNEL);
		BUG_ON(opal_msg == शून्य);
	पूर्ण

	क्रम (i = 0; i < OPAL_MSG_TYPE_MAX; i++)
		ATOMIC_INIT_NOTIFIER_HEAD(&opal_msg_notअगरier_head[i]);

	irq = opal_event_request(ilog2(OPAL_EVENT_MSG_PENDING));
	अगर (!irq) अणु
		pr_err("%s: Can't register OPAL event irq (%d)\n",
		       __func__, irq);
		वापस irq;
	पूर्ण

	ret = request_irq(irq, opal_message_notअगरy,
			IRQ_TYPE_LEVEL_HIGH, "opal-msg", शून्य);
	अगर (ret) अणु
		pr_err("%s: Can't request OPAL event irq (%d)\n",
		       __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक opal_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	s64 rc;
	__be64 evt, len;

	अगर (!opal.entry)
		वापस -ENODEV;
	opal_poll_events(&evt);
	अगर ((be64_to_cpu(evt) & OPAL_EVENT_CONSOLE_INPUT) == 0)
		वापस 0;
	len = cpu_to_be64(count);
	rc = opal_console_पढ़ो(vtermno, &len, buf);
	अगर (rc == OPAL_SUCCESS)
		वापस be64_to_cpu(len);
	वापस 0;
पूर्ण

अटल पूर्णांक __opal_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *data, पूर्णांक total_len, bool atomic)
अणु
	अचिन्हित दीर्घ flags = 0 /* shut up gcc */;
	पूर्णांक written;
	__be64 olen;
	s64 rc;

	अगर (!opal.entry)
		वापस -ENODEV;

	अगर (atomic)
		spin_lock_irqsave(&opal_ग_लिखो_lock, flags);
	rc = opal_console_ग_लिखो_buffer_space(vtermno, &olen);
	अगर (rc || be64_to_cpu(olen) < total_len) अणु
		/* Closed -> drop अक्षरacters */
		अगर (rc)
			written = total_len;
		अन्यथा
			written = -EAGAIN;
		जाओ out;
	पूर्ण

	/* Should not get a partial ग_लिखो here because space is available. */
	olen = cpu_to_be64(total_len);
	rc = opal_console_ग_लिखो(vtermno, &olen, data);
	अगर (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		अगर (rc == OPAL_BUSY_EVENT)
			opal_poll_events(शून्य);
		written = -EAGAIN;
		जाओ out;
	पूर्ण

	/* Closed or other error drop */
	अगर (rc != OPAL_SUCCESS) अणु
		written = opal_error_code(rc);
		जाओ out;
	पूर्ण

	written = be64_to_cpu(olen);
	अगर (written < total_len) अणु
		अगर (atomic) अणु
			/* Should not happen */
			pr_warn("atomic console write returned partial "
				"len=%d written=%d\n", total_len, written);
		पूर्ण
		अगर (!written)
			written = -EAGAIN;
	पूर्ण

out:
	अगर (atomic)
		spin_unlock_irqrestore(&opal_ग_लिखो_lock, flags);

	वापस written;
पूर्ण

पूर्णांक opal_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *data, पूर्णांक total_len)
अणु
	वापस __opal_put_अक्षरs(vtermno, data, total_len, false);
पूर्ण

/*
 * opal_put_अक्षरs_atomic will not perक्रमm partial-ग_लिखोs. Data will be
 * atomically written to the terminal or not at all. This is not strictly
 * true at the moment because console space can race with OPAL's console
 * ग_लिखोs.
 */
पूर्णांक opal_put_अक्षरs_atomic(uपूर्णांक32_t vtermno, स्थिर अक्षर *data, पूर्णांक total_len)
अणु
	वापस __opal_put_अक्षरs(vtermno, data, total_len, true);
पूर्ण

अटल s64 __opal_flush_console(uपूर्णांक32_t vtermno)
अणु
	s64 rc;

	अगर (!opal_check_token(OPAL_CONSOLE_FLUSH)) अणु
		__be64 evt;

		/*
		 * If OPAL_CONSOLE_FLUSH is not implemented in the firmware,
		 * the console can still be flushed by calling the polling
		 * function जबतक it has OPAL_EVENT_CONSOLE_OUTPUT events.
		 */
		WARN_ONCE(1, "opal: OPAL_CONSOLE_FLUSH missing.\n");

		opal_poll_events(&evt);
		अगर (!(be64_to_cpu(evt) & OPAL_EVENT_CONSOLE_OUTPUT))
			वापस OPAL_SUCCESS;
		वापस OPAL_BUSY;

	पूर्ण अन्यथा अणु
		rc = opal_console_flush(vtermno);
		अगर (rc == OPAL_BUSY_EVENT) अणु
			opal_poll_events(शून्य);
			rc = OPAL_BUSY;
		पूर्ण
		वापस rc;
	पूर्ण

पूर्ण

/*
 * opal_flush_console spins until the console is flushed
 */
पूर्णांक opal_flush_console(uपूर्णांक32_t vtermno)
अणु
	क्रम (;;) अणु
		s64 rc = __opal_flush_console(vtermno);

		अगर (rc == OPAL_BUSY || rc == OPAL_PARTIAL) अणु
			mdelay(1);
			जारी;
		पूर्ण

		वापस opal_error_code(rc);
	पूर्ण
पूर्ण

/*
 * opal_flush_अक्षरs is an hvc पूर्णांकerface that sleeps until the console is
 * flushed अगर रुको, otherwise it will वापस -EBUSY अगर the console has data,
 * -EAGAIN अगर it has data and some of it was flushed.
 */
पूर्णांक opal_flush_अक्षरs(uपूर्णांक32_t vtermno, bool रुको)
अणु
	क्रम (;;) अणु
		s64 rc = __opal_flush_console(vtermno);

		अगर (rc == OPAL_BUSY || rc == OPAL_PARTIAL) अणु
			अगर (रुको) अणु
				msleep(OPAL_BUSY_DELAY_MS);
				जारी;
			पूर्ण
			अगर (rc == OPAL_PARTIAL)
				वापस -EAGAIN;
		पूर्ण

		वापस opal_error_code(rc);
	पूर्ण
पूर्ण

अटल पूर्णांक opal_recover_mce(काष्ठा pt_regs *regs,
					काष्ठा machine_check_event *evt)
अणु
	पूर्णांक recovered = 0;

	अगर (!(regs->msr & MSR_RI)) अणु
		/* If MSR_RI isn't set, we cannot recover */
		pr_err("Machine check interrupt unrecoverable: MSR(RI=0)\n");
		recovered = 0;
	पूर्ण अन्यथा अगर (evt->disposition == MCE_DISPOSITION_RECOVERED) अणु
		/* Platक्रमm corrected itself */
		recovered = 1;
	पूर्ण अन्यथा अगर (evt->severity == MCE_SEV_FATAL) अणु
		/* Fatal machine check */
		pr_err("Machine check interrupt is fatal\n");
		recovered = 0;
	पूर्ण

	अगर (!recovered && evt->sync_error) अणु
		/*
		 * Try to समाप्त processes अगर we get a synchronous machine check
		 * (e.g., one caused by execution of this inकाष्ठाion). This
		 * will devolve पूर्णांकo a panic अगर we try to समाप्त init or are in
		 * an पूर्णांकerrupt etc.
		 *
		 * TODO: Queue up this address क्रम hwpoisioning later.
		 * TODO: This is not quite right क्रम d-side machine
		 *       checks ->nip is not necessarily the important
		 *       address.
		 */
		अगर ((user_mode(regs))) अणु
			_exception(SIGBUS, regs, BUS_MCEERR_AR, regs->nip);
			recovered = 1;
		पूर्ण अन्यथा अगर (die_will_crash()) अणु
			/*
			 * die() would समाप्त the kernel, so better to go via
			 * the platक्रमm reboot code that will log the
			 * machine check.
			 */
			recovered = 0;
		पूर्ण अन्यथा अणु
			die_mce("Machine check", regs, SIGBUS);
			recovered = 1;
		पूर्ण
	पूर्ण

	वापस recovered;
पूर्ण

व्योम __noवापस pnv_platक्रमm_error_reboot(काष्ठा pt_regs *regs, स्थिर अक्षर *msg)
अणु
	panic_flush_kmsg_start();

	pr_emerg("Hardware platform error: %s\n", msg);
	अगर (regs)
		show_regs(regs);
	smp_send_stop();

	panic_flush_kmsg_end();

	/*
	 * Don't bother to shut things करोwn because this will
	 * xstop the प्रणाली.
	 */
	अगर (opal_cec_reboot2(OPAL_REBOOT_PLATFORM_ERROR, msg)
						== OPAL_UNSUPPORTED) अणु
		pr_emerg("Reboot type %d not supported for %s\n",
				OPAL_REBOOT_PLATFORM_ERROR, msg);
	पूर्ण

	/*
	 * We reached here. There can be three possibilities:
	 * 1. We are running on a firmware level that करो not support
	 *    opal_cec_reboot2()
	 * 2. We are running on a firmware level that करो not support
	 *    OPAL_REBOOT_PLATFORM_ERROR reboot type.
	 * 3. We are running on FSP based प्रणाली that करोes not need
	 *    opal to trigger checkstop explicitly क्रम error analysis.
	 *    The FSP PRD component would have alपढ़ोy got notअगरied
	 *    about this error through other channels.
	 * 4. We are running on a newer skiboot that by शेष करोes
	 *    not cause a checkstop, drops us back to the kernel to
	 *    extract context and state at the समय of the error.
	 */

	panic(msg);
पूर्ण

पूर्णांक opal_machine_check(काष्ठा pt_regs *regs)
अणु
	काष्ठा machine_check_event evt;

	अगर (!get_mce_event(&evt, MCE_EVENT_RELEASE))
		वापस 0;

	/* Prपूर्णांक things out */
	अगर (evt.version != MCE_V1) अणु
		pr_err("Machine Check Exception, Unknown event version %d !\n",
		       evt.version);
		वापस 0;
	पूर्ण
	machine_check_prपूर्णांक_event_info(&evt, user_mode(regs), false);

	अगर (opal_recover_mce(regs, &evt))
		वापस 1;

	pnv_platक्रमm_error_reboot(regs, "Unrecoverable Machine Check exception");
पूर्ण

/* Early hmi handler called in real mode. */
पूर्णांक opal_hmi_exception_early(काष्ठा pt_regs *regs)
अणु
	s64 rc;

	/*
	 * call opal hmi handler. Pass paca address as token.
	 * The वापस value OPAL_SUCCESS is an indication that there is
	 * an HMI event generated रुकोing to pull by Linux.
	 */
	rc = opal_handle_hmi();
	अगर (rc == OPAL_SUCCESS) अणु
		local_paca->hmi_event_available = 1;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक opal_hmi_exception_early2(काष्ठा pt_regs *regs)
अणु
	s64 rc;
	__be64 out_flags;

	/*
	 * call opal hmi handler.
	 * Check 64-bit flag mask to find out अगर an event was generated,
	 * and whether TB is still valid or not etc.
	 */
	rc = opal_handle_hmi2(&out_flags);
	अगर (rc != OPAL_SUCCESS)
		वापस 0;

	अगर (be64_to_cpu(out_flags) & OPAL_HMI_FLAGS_NEW_EVENT)
		local_paca->hmi_event_available = 1;
	अगर (be64_to_cpu(out_flags) & OPAL_HMI_FLAGS_TOD_TB_FAIL)
		tb_invalid = true;
	वापस 1;
पूर्ण

/* HMI exception handler called in भव mode when irqs are next enabled. */
पूर्णांक opal_handle_hmi_exception(काष्ठा pt_regs *regs)
अणु
	/*
	 * Check अगर HMI event is available.
	 * अगर Yes, then wake kopald to process them.
	 */
	अगर (!local_paca->hmi_event_available)
		वापस 0;

	local_paca->hmi_event_available = 0;
	opal_wake_poller();

	वापस 1;
पूर्ण

अटल uपूर्णांक64_t find_recovery_address(uपूर्णांक64_t nip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mc_recoverable_range_len; i++)
		अगर ((nip >= mc_recoverable_range[i].start_addr) &&
		    (nip < mc_recoverable_range[i].end_addr))
		    वापस mc_recoverable_range[i].recover_addr;
	वापस 0;
पूर्ण

bool opal_mce_check_early_recovery(काष्ठा pt_regs *regs)
अणु
	uपूर्णांक64_t recover_addr = 0;

	अगर (!opal.base || !opal.size)
		जाओ out;

	अगर ((regs->nip >= opal.base) &&
			(regs->nip < (opal.base + opal.size)))
		recover_addr = find_recovery_address(regs->nip);

	/*
	 * Setup regs->nip to rfi पूर्णांकo fixup address.
	 */
	अगर (recover_addr)
		regs->nip = recover_addr;

out:
	वापस !!recover_addr;
पूर्ण

अटल पूर्णांक opal_sysfs_init(व्योम)
अणु
	opal_kobj = kobject_create_and_add("opal", firmware_kobj);
	अगर (!opal_kobj) अणु
		pr_warn("kobject_create_and_add opal failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार export_attr_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	वापस memory_पढ़ो_from_buffer(buf, count, &off, bin_attr->निजी,
				       bin_attr->size);
पूर्ण

अटल पूर्णांक opal_add_one_export(काष्ठा kobject *parent, स्थिर अक्षर *export_name,
			       काष्ठा device_node *np, स्थिर अक्षर *prop_name)
अणु
	काष्ठा bin_attribute *attr = शून्य;
	स्थिर अक्षर *name = शून्य;
	u64 vals[2];
	पूर्णांक rc;

	rc = of_property_पढ़ो_u64_array(np, prop_name, &vals[0], 2);
	अगर (rc)
		जाओ out;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	name = kstrdup(export_name, GFP_KERNEL);
	अगर (!name) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	sysfs_bin_attr_init(attr);
	attr->attr.name = name;
	attr->attr.mode = 0400;
	attr->पढ़ो = export_attr_पढ़ो;
	attr->निजी = __va(vals[0]);
	attr->size = vals[1];

	rc = sysfs_create_bin_file(parent, attr);
out:
	अगर (rc) अणु
		kमुक्त(name);
		kमुक्त(attr);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम opal_add_exported_attrs(काष्ठा device_node *np,
				    काष्ठा kobject *kobj)
अणु
	काष्ठा device_node *child;
	काष्ठा property *prop;

	क्रम_each_property_of_node(np, prop) अणु
		पूर्णांक rc;

		अगर (!म_भेद(prop->name, "name") ||
		    !म_भेद(prop->name, "phandle"))
			जारी;

		rc = opal_add_one_export(kobj, prop->name, np, prop->name);
		अगर (rc) अणु
			pr_warn("Unable to add export %pOF/%s, rc = %d!\n",
				np, prop->name, rc);
		पूर्ण
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		काष्ठा kobject *child_kobj;

		child_kobj = kobject_create_and_add(child->name, kobj);
		अगर (!child_kobj) अणु
			pr_err("Unable to create export dir for %pOF\n", child);
			जारी;
		पूर्ण

		opal_add_exported_attrs(child, child_kobj);
	पूर्ण
पूर्ण

/*
 * opal_export_attrs: creates a sysfs node क्रम each property listed in
 * the device-tree under /ibm,opal/firmware/exports/
 * All new sysfs nodes are created under /opal/exports/.
 * This allows क्रम reserved memory regions (e.g. HDAT) to be पढ़ो.
 * The new sysfs nodes are only पढ़ोable by root.
 */
अटल व्योम opal_export_attrs(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा kobject *kobj;
	पूर्णांक rc;

	np = of_find_node_by_path("/ibm,opal/firmware/exports");
	अगर (!np)
		वापस;

	/* Create new 'exports' directory - /sys/firmware/opal/exports */
	kobj = kobject_create_and_add("exports", opal_kobj);
	अगर (!kobj) अणु
		pr_warn("kobject_create_and_add() of exports failed\n");
		वापस;
	पूर्ण

	opal_add_exported_attrs(np, kobj);

	/*
	 * NB: symbol_map existed beक्रमe the generic export पूर्णांकerface so it
	 * lives under the top level opal_kobj.
	 */
	rc = opal_add_one_export(opal_kobj, "symbol_map",
				 np->parent, "symbol-map");
	अगर (rc)
		pr_warn("Error %d creating OPAL symbols file\n", rc);

	of_node_put(np);
पूर्ण

अटल व्योम __init opal_dump_region_init(व्योम)
अणु
	व्योम *addr;
	uपूर्णांक64_t size;
	पूर्णांक rc;

	अगर (!opal_check_token(OPAL_REGISTER_DUMP_REGION))
		वापस;

	/* Register kernel log buffer */
	addr = log_buf_addr_get();
	अगर (addr == शून्य)
		वापस;

	size = log_buf_len_get();
	अगर (size == 0)
		वापस;

	rc = opal_रेजिस्टर_dump_region(OPAL_DUMP_REGION_LOG_BUF,
				       __pa(addr), size);
	/* Don't warn if this is just an older OPAL that doesn't
	 * know about that call
	 */
	अगर (rc && rc != OPAL_UNSUPPORTED)
		pr_warn("DUMP: Failed to register kernel log buffer. "
			"rc = %d\n", rc);
पूर्ण

अटल व्योम opal_pdev_init(स्थिर अक्षर *compatible)
अणु
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, शून्य, compatible)
		of_platक्रमm_device_create(np, शून्य, शून्य);
पूर्ण

अटल व्योम __init opal_imc_init_dev(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, IMC_DTB_COMPAT);
	अगर (np)
		of_platक्रमm_device_create(np, शून्य, शून्य);
पूर्ण

अटल पूर्णांक kopald(व्योम *unused)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(opal_heartbeat) + 1;

	set_मुक्तzable();
	करो अणु
		try_to_मुक्तze();

		opal_handle_events();

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (opal_have_pending_events())
			__set_current_state(TASK_RUNNING);
		अन्यथा
			schedule_समयout(समयout);

	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

व्योम opal_wake_poller(व्योम)
अणु
	अगर (kopald_tsk)
		wake_up_process(kopald_tsk);
पूर्ण

अटल व्योम opal_init_heartbeat(व्योम)
अणु
	/* Old firwmware, we assume the HVC heartbeat is sufficient */
	अगर (of_property_पढ़ो_u32(opal_node, "ibm,heartbeat-ms",
				 &opal_heartbeat) != 0)
		opal_heartbeat = 0;

	अगर (opal_heartbeat)
		kopald_tsk = kthपढ़ो_run(kopald, शून्य, "kopald");
पूर्ण

अटल पूर्णांक __init opal_init(व्योम)
अणु
	काष्ठा device_node *np, *consoles, *leds;
	पूर्णांक rc;

	opal_node = of_find_node_by_path("/ibm,opal");
	अगर (!opal_node) अणु
		pr_warn("Device node not found\n");
		वापस -ENODEV;
	पूर्ण

	/* Register OPAL consoles अगर any ports */
	consoles = of_find_node_by_path("/ibm,opal/consoles");
	अगर (consoles) अणु
		क्रम_each_child_of_node(consoles, np) अणु
			अगर (!of_node_name_eq(np, "serial"))
				जारी;
			of_platक्रमm_device_create(np, शून्य, शून्य);
		पूर्ण
		of_node_put(consoles);
	पूर्ण

	/* Initialise OPAL messaging प्रणाली */
	opal_message_init(opal_node);

	/* Initialise OPAL asynchronous completion पूर्णांकerface */
	opal_async_comp_init();

	/* Initialise OPAL sensor पूर्णांकerface */
	opal_sensor_init();

	/* Initialise OPAL hypervisor मुख्यtainence पूर्णांकerrupt handling */
	opal_hmi_handler_init();

	/* Create i2c platक्रमm devices */
	opal_pdev_init("ibm,opal-i2c");

	/* Handle non-अस्थिर memory devices */
	opal_pdev_init("pmem-region");

	/* Setup a heatbeat thपढ़ो अगर requested by OPAL */
	opal_init_heartbeat();

	/* Detect In-Memory Collection counters and create devices*/
	opal_imc_init_dev();

	/* Create leds platक्रमm devices */
	leds = of_find_node_by_path("/ibm,opal/leds");
	अगर (leds) अणु
		of_platक्रमm_device_create(leds, "opal_leds", शून्य);
		of_node_put(leds);
	पूर्ण

	/* Initialise OPAL message log पूर्णांकerface */
	opal_msglog_init();

	/* Create "opal" kobject under /sys/firmware */
	rc = opal_sysfs_init();
	अगर (rc == 0) अणु
		/* Setup dump region पूर्णांकerface */
		opal_dump_region_init();
		/* Setup error log पूर्णांकerface */
		rc = opal_elog_init();
		/* Setup code update पूर्णांकerface */
		opal_flash_update_init();
		/* Setup platक्रमm dump extract पूर्णांकerface */
		opal_platक्रमm_dump_init();
		/* Setup प्रणाली parameters पूर्णांकerface */
		opal_sys_param_init();
		/* Setup message log sysfs पूर्णांकerface. */
		opal_msglog_sysfs_init();
		/* Add all export properties*/
		opal_export_attrs();
	पूर्ण

	/* Initialize platक्रमm devices: IPMI backend, PRD & flash पूर्णांकerface */
	opal_pdev_init("ibm,opal-ipmi");
	opal_pdev_init("ibm,opal-flash");
	opal_pdev_init("ibm,opal-prd");

	/* Initialise platक्रमm device: oppanel पूर्णांकerface */
	opal_pdev_init("ibm,opal-oppanel");

	/* Initialise OPAL kmsg dumper क्रम flushing console on panic */
	opal_kmsg_init();

	/* Initialise OPAL घातercap पूर्णांकerface */
	opal_घातercap_init();

	/* Initialise OPAL Power-Shअगरting-Ratio पूर्णांकerface */
	opal_psr_init();

	/* Initialise OPAL sensor groups */
	opal_sensor_groups_init();

	/* Initialise OPAL Power control पूर्णांकerface */
	opal_घातer_control_init();

	/* Initialize OPAL secure variables */
	opal_pdev_init("ibm,secvar-backend");

	वापस 0;
पूर्ण
machine_subsys_initcall(घातernv, opal_init);

व्योम opal_shutकरोwn(व्योम)
अणु
	दीर्घ rc = OPAL_BUSY;

	opal_event_shutकरोwn();

	/*
	 * Then sync with OPAL which ensure anything that can
	 * potentially ग_लिखो to our memory has completed such
	 * as an ongoing dump retrieval
	 */
	जबतक (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) अणु
		rc = opal_sync_host_reboot();
		अगर (rc == OPAL_BUSY)
			opal_poll_events(शून्य);
		अन्यथा
			mdelay(10);
	पूर्ण

	/* Unरेजिस्टर memory dump region */
	अगर (opal_check_token(OPAL_UNREGISTER_DUMP_REGION))
		opal_unरेजिस्टर_dump_region(OPAL_DUMP_REGION_LOG_BUF);
पूर्ण

/* Export this so that test modules can use it */
EXPORT_SYMBOL_GPL(opal_invalid_call);
EXPORT_SYMBOL_GPL(opal_xscom_पढ़ो);
EXPORT_SYMBOL_GPL(opal_xscom_ग_लिखो);
EXPORT_SYMBOL_GPL(opal_ipmi_send);
EXPORT_SYMBOL_GPL(opal_ipmi_recv);
EXPORT_SYMBOL_GPL(opal_flash_पढ़ो);
EXPORT_SYMBOL_GPL(opal_flash_ग_लिखो);
EXPORT_SYMBOL_GPL(opal_flash_erase);
EXPORT_SYMBOL_GPL(opal_prd_msg);
EXPORT_SYMBOL_GPL(opal_check_token);

/* Convert a region of vदो_स्मृति memory to an opal sg list */
काष्ठा opal_sg_list *opal_vदो_स्मृति_to_sg_list(व्योम *vदो_स्मृति_addr,
					     अचिन्हित दीर्घ vदो_स्मृति_size)
अणु
	काष्ठा opal_sg_list *sg, *first = शून्य;
	अचिन्हित दीर्घ i = 0;

	sg = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!sg)
		जाओ nomem;

	first = sg;

	जबतक (vदो_स्मृति_size > 0) अणु
		uपूर्णांक64_t data = vदो_स्मृति_to_pfn(vदो_स्मृति_addr) << PAGE_SHIFT;
		uपूर्णांक64_t length = min(vदो_स्मृति_size, PAGE_SIZE);

		sg->entry[i].data = cpu_to_be64(data);
		sg->entry[i].length = cpu_to_be64(length);
		i++;

		अगर (i >= SG_ENTRIES_PER_NODE) अणु
			काष्ठा opal_sg_list *next;

			next = kzalloc(PAGE_SIZE, GFP_KERNEL);
			अगर (!next)
				जाओ nomem;

			sg->length = cpu_to_be64(
					i * माप(काष्ठा opal_sg_entry) + 16);
			i = 0;
			sg->next = cpu_to_be64(__pa(next));
			sg = next;
		पूर्ण

		vदो_स्मृति_addr += length;
		vदो_स्मृति_size -= length;
	पूर्ण

	sg->length = cpu_to_be64(i * माप(काष्ठा opal_sg_entry) + 16);

	वापस first;

nomem:
	pr_err("%s : Failed to allocate memory\n", __func__);
	opal_मुक्त_sg_list(first);
	वापस शून्य;
पूर्ण

व्योम opal_मुक्त_sg_list(काष्ठा opal_sg_list *sg)
अणु
	जबतक (sg) अणु
		uपूर्णांक64_t next = be64_to_cpu(sg->next);

		kमुक्त(sg);

		अगर (next)
			sg = __va(next);
		अन्यथा
			sg = शून्य;
	पूर्ण
पूर्ण

पूर्णांक opal_error_code(पूर्णांक rc)
अणु
	चयन (rc) अणु
	हाल OPAL_SUCCESS:		वापस 0;

	हाल OPAL_PARAMETER:		वापस -EINVAL;
	हाल OPAL_ASYNC_COMPLETION:	वापस -EINPROGRESS;
	हाल OPAL_BUSY:
	हाल OPAL_BUSY_EVENT:		वापस -EBUSY;
	हाल OPAL_NO_MEM:		वापस -ENOMEM;
	हाल OPAL_PERMISSION:		वापस -EPERM;

	हाल OPAL_UNSUPPORTED:		वापस -EIO;
	हाल OPAL_HARDWARE:		वापस -EIO;
	हाल OPAL_INTERNAL_ERROR:	वापस -EIO;
	हाल OPAL_TIMEOUT:		वापस -ETIMEDOUT;
	शेष:
		pr_err("%s: unexpected OPAL error %d\n", __func__, rc);
		वापस -EIO;
	पूर्ण
पूर्ण

व्योम घातernv_set_nmmu_ptcr(अचिन्हित दीर्घ ptcr)
अणु
	पूर्णांक rc;

	अगर (firmware_has_feature(FW_FEATURE_OPAL)) अणु
		rc = opal_nmmu_set_ptcr(-1UL, ptcr);
		अगर (rc != OPAL_SUCCESS && rc != OPAL_UNSUPPORTED)
			pr_warn("%s: Unable to set nest mmu ptcr\n", __func__);
	पूर्ण
पूर्ण

EXPORT_SYMBOL_GPL(opal_poll_events);
EXPORT_SYMBOL_GPL(opal_rtc_पढ़ो);
EXPORT_SYMBOL_GPL(opal_rtc_ग_लिखो);
EXPORT_SYMBOL_GPL(opal_tpo_पढ़ो);
EXPORT_SYMBOL_GPL(opal_tpo_ग_लिखो);
EXPORT_SYMBOL_GPL(opal_i2c_request);
/* Export these symbols क्रम PowerNV LED class driver */
EXPORT_SYMBOL_GPL(opal_leds_get_ind);
EXPORT_SYMBOL_GPL(opal_leds_set_ind);
/* Export this symbol क्रम PowerNV Operator Panel class driver */
EXPORT_SYMBOL_GPL(opal_ग_लिखो_oppanel_async);
/* Export this क्रम KVM */
EXPORT_SYMBOL_GPL(opal_पूर्णांक_set_mfrr);
EXPORT_SYMBOL_GPL(opal_पूर्णांक_eoi);
EXPORT_SYMBOL_GPL(opal_error_code);
/* Export the below symbol क्रम NX compression */
EXPORT_SYMBOL(opal_nx_coproc_init);
