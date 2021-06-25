<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IUCV base infraकाष्ठाure.
 *
 * Copyright IBM Corp. 2001, 2009
 *
 * Author(s):
 *    Original source:
 *	Alan Alपंचांगark (Alan_Alपंचांगark@us.ibm.com)	Sept. 2000
 *	Xenia Tkatschow (xenia@us.ibm.com)
 *    2Gb awareness and general cleanup:
 *	Fritz Elfert (elfert@de.ibm.com, felfert@millenux.com)
 *    Rewritten क्रम af_iucv:
 *	Martin Schwidefsky <schwidefsky@de.ibm.com>
 *    PM functions:
 *	Ursula Braun (ursula.braun@de.ibm.com)
 *
 * Documentation used:
 *    The original source
 *    CP Programming Service, IBM करोcument # SC24-5760
 */

#घोषणा KMSG_COMPONENT "iucv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/reboot.h>
#समावेश <net/iucv/iucv.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/smp.h>

/*
 * FLAGS:
 * All flags are defined in the field IPFLAGS1 of each function
 * and can be found in CP Programming Services.
 * IPSRCCLS - Indicates you have specअगरied a source class.
 * IPTRGCLS - Indicates you have specअगरied a target class.
 * IPFGPID  - Indicates you have specअगरied a pathid.
 * IPFGMID  - Indicates you have specअगरied a message ID.
 * IPNORPY  - Indicates a one-way message. No reply expected.
 * IPALL    - Indicates that all paths are affected.
 */
#घोषणा IUCV_IPSRCCLS	0x01
#घोषणा IUCV_IPTRGCLS	0x01
#घोषणा IUCV_IPFGPID	0x02
#घोषणा IUCV_IPFGMID	0x04
#घोषणा IUCV_IPNORPY	0x10
#घोषणा IUCV_IPALL	0x80

अटल पूर्णांक iucv_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 0;
पूर्ण

काष्ठा bus_type iucv_bus = अणु
	.name = "iucv",
	.match = iucv_bus_match,
पूर्ण;
EXPORT_SYMBOL(iucv_bus);

काष्ठा device *iucv_root;
EXPORT_SYMBOL(iucv_root);

अटल पूर्णांक iucv_available;

/* General IUCV पूर्णांकerrupt काष्ठाure */
काष्ठा iucv_irq_data अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iptype;
	u32 res2[8];
पूर्ण;

काष्ठा iucv_irq_list अणु
	काष्ठा list_head list;
	काष्ठा iucv_irq_data data;
पूर्ण;

अटल काष्ठा iucv_irq_data *iucv_irq_data[NR_CPUS];
अटल cpumask_t iucv_buffer_cpumask = अणु CPU_BITS_NONE पूर्ण;
अटल cpumask_t iucv_irq_cpumask = अणु CPU_BITS_NONE पूर्ण;

/*
 * Queue of पूर्णांकerrupt buffers lock क्रम delivery via the tasklet
 * (fast but can't call smp_call_function).
 */
अटल LIST_HEAD(iucv_task_queue);

/*
 * The tasklet क्रम fast delivery of iucv पूर्णांकerrupts.
 */
अटल व्योम iucv_tasklet_fn(अचिन्हित दीर्घ);
अटल DECLARE_TASKLET_OLD(iucv_tasklet, iucv_tasklet_fn);

/*
 * Queue of पूर्णांकerrupt buffers क्रम delivery via a work queue
 * (slower but can call smp_call_function).
 */
अटल LIST_HEAD(iucv_work_queue);

/*
 * The work element to deliver path pending पूर्णांकerrupts.
 */
अटल व्योम iucv_work_fn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(iucv_work, iucv_work_fn);

/*
 * Spinlock protecting task and work queue.
 */
अटल DEFINE_SPINLOCK(iucv_queue_lock);

क्रमागत iucv_command_codes अणु
	IUCV_QUERY = 0,
	IUCV_RETRIEVE_BUFFER = 2,
	IUCV_SEND = 4,
	IUCV_RECEIVE = 5,
	IUCV_REPLY = 6,
	IUCV_REJECT = 8,
	IUCV_PURGE = 9,
	IUCV_ACCEPT = 10,
	IUCV_CONNECT = 11,
	IUCV_DECLARE_BUFFER = 12,
	IUCV_QUIESCE = 13,
	IUCV_RESUME = 14,
	IUCV_SEVER = 15,
	IUCV_SETMASK = 16,
	IUCV_SETCONTROLMASK = 17,
पूर्ण;

/*
 * Error messages that are used with the iucv_sever function. They get
 * converted to EBCDIC.
 */
अटल अक्षर iucv_error_no_listener[16] = "NO LISTENER";
अटल अक्षर iucv_error_no_memory[16] = "NO MEMORY";
अटल अक्षर iucv_error_pathid[16] = "INVALID PATHID";

/*
 * iucv_handler_list: List of रेजिस्टरed handlers.
 */
अटल LIST_HEAD(iucv_handler_list);

/*
 * iucv_path_table: an array of iucv_path काष्ठाures.
 */
अटल काष्ठा iucv_path **iucv_path_table;
अटल अचिन्हित दीर्घ iucv_max_pathid;

/*
 * iucv_lock: spinlock protecting iucv_handler_list and iucv_pathid_table
 */
अटल DEFINE_SPINLOCK(iucv_table_lock);

/*
 * iucv_active_cpu: contains the number of the cpu executing the tasklet
 * or the work handler. Needed क्रम iucv_path_sever called from tasklet.
 */
अटल पूर्णांक iucv_active_cpu = -1;

/*
 * Mutex and रुको queue क्रम iucv_रेजिस्टर/iucv_unरेजिस्टर.
 */
अटल DEFINE_MUTEX(iucv_रेजिस्टर_mutex);

/*
 * Counter क्रम number of non-smp capable handlers.
 */
अटल पूर्णांक iucv_nonsmp_handler;

/*
 * IUCV control data काष्ठाure. Used by iucv_path_accept, iucv_path_connect,
 * iucv_path_quiesce and iucv_path_sever.
 */
काष्ठा iucv_cmd_control अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iprcode;
	u16 ipmsglim;
	u16 res1;
	u8  ipvmid[8];
	u8  ipuser[16];
	u8  iptarget[8];
पूर्ण __attribute__ ((packed,aligned(8)));

/*
 * Data in parameter list iucv काष्ठाure. Used by iucv_message_send,
 * iucv_message_send2way and iucv_message_reply.
 */
काष्ठा iucv_cmd_dpl अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iprcode;
	u32 ipmsgid;
	u32 iptrgcls;
	u8  iprmmsg[8];
	u32 ipsrccls;
	u32 ipmsgtag;
	u32 ipbfadr2;
	u32 ipbfln2f;
	u32 res;
पूर्ण __attribute__ ((packed,aligned(8)));

/*
 * Data in buffer iucv काष्ठाure. Used by iucv_message_receive,
 * iucv_message_reject, iucv_message_send, iucv_message_send2way
 * and iucv_declare_cpu.
 */
काष्ठा iucv_cmd_db अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iprcode;
	u32 ipmsgid;
	u32 iptrgcls;
	u32 ipbfadr1;
	u32 ipbfln1f;
	u32 ipsrccls;
	u32 ipmsgtag;
	u32 ipbfadr2;
	u32 ipbfln2f;
	u32 res;
पूर्ण __attribute__ ((packed,aligned(8)));

/*
 * Purge message iucv काष्ठाure. Used by iucv_message_purge.
 */
काष्ठा iucv_cmd_purge अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iprcode;
	u32 ipmsgid;
	u8  ipaudit[3];
	u8  res1[5];
	u32 res2;
	u32 ipsrccls;
	u32 ipmsgtag;
	u32 res3[3];
पूर्ण __attribute__ ((packed,aligned(8)));

/*
 * Set mask iucv काष्ठाure. Used by iucv_enable_cpu.
 */
काष्ठा iucv_cmd_set_mask अणु
	u8  ipmask;
	u8  res1[2];
	u8  iprcode;
	u32 res2[9];
पूर्ण __attribute__ ((packed,aligned(8)));

जोड़ iucv_param अणु
	काष्ठा iucv_cmd_control ctrl;
	काष्ठा iucv_cmd_dpl dpl;
	काष्ठा iucv_cmd_db db;
	काष्ठा iucv_cmd_purge purge;
	काष्ठा iucv_cmd_set_mask set_mask;
पूर्ण;

/*
 * Anchor क्रम per-cpu IUCV command parameter block.
 */
अटल जोड़ iucv_param *iucv_param[NR_CPUS];
अटल जोड़ iucv_param *iucv_param_irq[NR_CPUS];

/**
 * iucv_call_b2f0
 * @code: identअगरier of IUCV call to CP.
 * @parm: poपूर्णांकer to a काष्ठा iucv_parm block
 *
 * Calls CP to execute IUCV commands.
 *
 * Returns the result of the CP IUCV call.
 */
अटल अंतरभूत पूर्णांक __iucv_call_b2f0(पूर्णांक command, जोड़ iucv_param *parm)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0");
	रेजिस्टर अचिन्हित दीर्घ reg1 यंत्र ("1");
	पूर्णांक ccode;

	reg0 = command;
	reg1 = (अचिन्हित दीर्घ)parm;
	यंत्र अस्थिर(
		"	.long 0xb2f01000\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (ccode), "=m" (*parm), "+d" (reg0), "+a" (reg1)
		:  "m" (*parm) : "cc");
	वापस ccode;
पूर्ण

अटल अंतरभूत पूर्णांक iucv_call_b2f0(पूर्णांक command, जोड़ iucv_param *parm)
अणु
	पूर्णांक ccode;

	ccode = __iucv_call_b2f0(command, parm);
	वापस ccode == 1 ? parm->ctrl.iprcode : ccode;
पूर्ण

/**
 * iucv_query_maxconn
 *
 * Determines the maximum number of connections that may be established.
 *
 * Returns the maximum number of connections or -EPERM is IUCV is not
 * available.
 */
अटल पूर्णांक __iucv_query_maxconn(व्योम *param, अचिन्हित दीर्घ *max_pathid)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0");
	रेजिस्टर अचिन्हित दीर्घ reg1 यंत्र ("1");
	पूर्णांक ccode;

	reg0 = IUCV_QUERY;
	reg1 = (अचिन्हित दीर्घ) param;
	यंत्र अस्थिर (
		"	.long	0xb2f01000\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (ccode), "+d" (reg0), "+d" (reg1) : : "cc");
	*max_pathid = reg1;
	वापस ccode;
पूर्ण

अटल पूर्णांक iucv_query_maxconn(व्योम)
अणु
	अचिन्हित दीर्घ max_pathid;
	व्योम *param;
	पूर्णांक ccode;

	param = kzalloc(माप(जोड़ iucv_param), GFP_KERNEL | GFP_DMA);
	अगर (!param)
		वापस -ENOMEM;
	ccode = __iucv_query_maxconn(param, &max_pathid);
	अगर (ccode == 0)
		iucv_max_pathid = max_pathid;
	kमुक्त(param);
	वापस ccode ? -EPERM : 0;
पूर्ण

/**
 * iucv_allow_cpu
 * @data: unused
 *
 * Allow iucv पूर्णांकerrupts on this cpu.
 */
अटल व्योम iucv_allow_cpu(व्योम *data)
अणु
	पूर्णांक cpu = smp_processor_id();
	जोड़ iucv_param *parm;

	/*
	 * Enable all iucv पूर्णांकerrupts.
	 * ipmask contains bits क्रम the dअगरferent पूर्णांकerrupts
	 *	0x80 - Flag to allow nonpriority message pending पूर्णांकerrupts
	 *	0x40 - Flag to allow priority message pending पूर्णांकerrupts
	 *	0x20 - Flag to allow nonpriority message completion पूर्णांकerrupts
	 *	0x10 - Flag to allow priority message completion पूर्णांकerrupts
	 *	0x08 - Flag to allow IUCV control पूर्णांकerrupts
	 */
	parm = iucv_param_irq[cpu];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->set_mask.ipmask = 0xf8;
	iucv_call_b2f0(IUCV_SETMASK, parm);

	/*
	 * Enable all iucv control पूर्णांकerrupts.
	 * ipmask contains bits क्रम the dअगरferent पूर्णांकerrupts
	 *	0x80 - Flag to allow pending connections पूर्णांकerrupts
	 *	0x40 - Flag to allow connection complete पूर्णांकerrupts
	 *	0x20 - Flag to allow connection severed पूर्णांकerrupts
	 *	0x10 - Flag to allow connection quiesced पूर्णांकerrupts
	 *	0x08 - Flag to allow connection resumed पूर्णांकerrupts
	 */
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->set_mask.ipmask = 0xf8;
	iucv_call_b2f0(IUCV_SETCONTROLMASK, parm);
	/* Set indication that iucv पूर्णांकerrupts are allowed क्रम this cpu. */
	cpumask_set_cpu(cpu, &iucv_irq_cpumask);
पूर्ण

/**
 * iucv_block_cpu
 * @data: unused
 *
 * Block iucv पूर्णांकerrupts on this cpu.
 */
अटल व्योम iucv_block_cpu(व्योम *data)
अणु
	पूर्णांक cpu = smp_processor_id();
	जोड़ iucv_param *parm;

	/* Disable all iucv पूर्णांकerrupts. */
	parm = iucv_param_irq[cpu];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	iucv_call_b2f0(IUCV_SETMASK, parm);

	/* Clear indication that iucv पूर्णांकerrupts are allowed क्रम this cpu. */
	cpumask_clear_cpu(cpu, &iucv_irq_cpumask);
पूर्ण

/**
 * iucv_declare_cpu
 * @data: unused
 *
 * Declare a पूर्णांकerrupt buffer on this cpu.
 */
अटल व्योम iucv_declare_cpu(व्योम *data)
अणु
	पूर्णांक cpu = smp_processor_id();
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	अगर (cpumask_test_cpu(cpu, &iucv_buffer_cpumask))
		वापस;

	/* Declare पूर्णांकerrupt buffer. */
	parm = iucv_param_irq[cpu];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->db.ipbfadr1 = virt_to_phys(iucv_irq_data[cpu]);
	rc = iucv_call_b2f0(IUCV_DECLARE_BUFFER, parm);
	अगर (rc) अणु
		अक्षर *err = "Unknown";
		चयन (rc) अणु
		हाल 0x03:
			err = "Directory error";
			अवरोध;
		हाल 0x0a:
			err = "Invalid length";
			अवरोध;
		हाल 0x13:
			err = "Buffer already exists";
			अवरोध;
		हाल 0x3e:
			err = "Buffer overlap";
			अवरोध;
		हाल 0x5c:
			err = "Paging or storage error";
			अवरोध;
		पूर्ण
		pr_warn("Defining an interrupt buffer on CPU %i failed with 0x%02x (%s)\n",
			cpu, rc, err);
		वापस;
	पूर्ण

	/* Set indication that an iucv buffer exists क्रम this cpu. */
	cpumask_set_cpu(cpu, &iucv_buffer_cpumask);

	अगर (iucv_nonsmp_handler == 0 || cpumask_empty(&iucv_irq_cpumask))
		/* Enable iucv पूर्णांकerrupts on this cpu. */
		iucv_allow_cpu(शून्य);
	अन्यथा
		/* Disable iucv पूर्णांकerrupts on this cpu. */
		iucv_block_cpu(शून्य);
पूर्ण

/**
 * iucv_retrieve_cpu
 * @data: unused
 *
 * Retrieve पूर्णांकerrupt buffer on this cpu.
 */
अटल व्योम iucv_retrieve_cpu(व्योम *data)
अणु
	पूर्णांक cpu = smp_processor_id();
	जोड़ iucv_param *parm;

	अगर (!cpumask_test_cpu(cpu, &iucv_buffer_cpumask))
		वापस;

	/* Block iucv पूर्णांकerrupts. */
	iucv_block_cpu(शून्य);

	/* Retrieve पूर्णांकerrupt buffer. */
	parm = iucv_param_irq[cpu];
	iucv_call_b2f0(IUCV_RETRIEVE_BUFFER, parm);

	/* Clear indication that an iucv buffer exists क्रम this cpu. */
	cpumask_clear_cpu(cpu, &iucv_buffer_cpumask);
पूर्ण

/**
 * iucv_seपंचांगask_smp
 *
 * Allow iucv पूर्णांकerrupts on all cpus.
 */
अटल व्योम iucv_seपंचांगask_mp(व्योम)
अणु
	पूर्णांक cpu;

	get_online_cpus();
	क्रम_each_online_cpu(cpu)
		/* Enable all cpus with a declared buffer. */
		अगर (cpumask_test_cpu(cpu, &iucv_buffer_cpumask) &&
		    !cpumask_test_cpu(cpu, &iucv_irq_cpumask))
			smp_call_function_single(cpu, iucv_allow_cpu,
						 शून्य, 1);
	put_online_cpus();
पूर्ण

/**
 * iucv_seपंचांगask_up
 *
 * Allow iucv पूर्णांकerrupts on a single cpu.
 */
अटल व्योम iucv_seपंचांगask_up(व्योम)
अणु
	cpumask_t cpumask;
	पूर्णांक cpu;

	/* Disable all cpu but the first in cpu_irq_cpumask. */
	cpumask_copy(&cpumask, &iucv_irq_cpumask);
	cpumask_clear_cpu(cpumask_first(&iucv_irq_cpumask), &cpumask);
	क्रम_each_cpu(cpu, &cpumask)
		smp_call_function_single(cpu, iucv_block_cpu, शून्य, 1);
पूर्ण

/**
 * iucv_enable
 *
 * This function makes iucv पढ़ोy क्रम use. It allocates the pathid
 * table, declares an iucv पूर्णांकerrupt buffer and enables the iucv
 * पूर्णांकerrupts. Called when the first user has रेजिस्टरed an iucv
 * handler.
 */
अटल पूर्णांक iucv_enable(व्योम)
अणु
	माप_प्रकार alloc_size;
	पूर्णांक cpu, rc;

	get_online_cpus();
	rc = -ENOMEM;
	alloc_size = iucv_max_pathid * माप(काष्ठा iucv_path);
	iucv_path_table = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!iucv_path_table)
		जाओ out;
	/* Declare per cpu buffers. */
	rc = -EIO;
	क्रम_each_online_cpu(cpu)
		smp_call_function_single(cpu, iucv_declare_cpu, शून्य, 1);
	अगर (cpumask_empty(&iucv_buffer_cpumask))
		/* No cpu could declare an iucv buffer. */
		जाओ out;
	put_online_cpus();
	वापस 0;
out:
	kमुक्त(iucv_path_table);
	iucv_path_table = शून्य;
	put_online_cpus();
	वापस rc;
पूर्ण

/**
 * iucv_disable
 *
 * This function shuts करोwn iucv. It disables iucv पूर्णांकerrupts, retrieves
 * the iucv पूर्णांकerrupt buffer and मुक्तs the pathid table. Called after the
 * last user unरेजिस्टर its iucv handler.
 */
अटल व्योम iucv_disable(व्योम)
अणु
	get_online_cpus();
	on_each_cpu(iucv_retrieve_cpu, शून्य, 1);
	kमुक्त(iucv_path_table);
	iucv_path_table = शून्य;
	put_online_cpus();
पूर्ण

अटल पूर्णांक iucv_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	kमुक्त(iucv_param_irq[cpu]);
	iucv_param_irq[cpu] = शून्य;
	kमुक्त(iucv_param[cpu]);
	iucv_param[cpu] = शून्य;
	kमुक्त(iucv_irq_data[cpu]);
	iucv_irq_data[cpu] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक iucv_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	/* Note: GFP_DMA used to get memory below 2G */
	iucv_irq_data[cpu] = kदो_स्मृति_node(माप(काष्ठा iucv_irq_data),
			     GFP_KERNEL|GFP_DMA, cpu_to_node(cpu));
	अगर (!iucv_irq_data[cpu])
		जाओ out_मुक्त;

	/* Allocate parameter blocks. */
	iucv_param[cpu] = kदो_स्मृति_node(माप(जोड़ iucv_param),
			  GFP_KERNEL|GFP_DMA, cpu_to_node(cpu));
	अगर (!iucv_param[cpu])
		जाओ out_मुक्त;

	iucv_param_irq[cpu] = kदो_स्मृति_node(माप(जोड़ iucv_param),
			  GFP_KERNEL|GFP_DMA, cpu_to_node(cpu));
	अगर (!iucv_param_irq[cpu])
		जाओ out_मुक्त;

	वापस 0;

out_मुक्त:
	iucv_cpu_dead(cpu);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक iucv_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!iucv_path_table)
		वापस 0;
	iucv_declare_cpu(शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक iucv_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	cpumask_t cpumask;

	अगर (!iucv_path_table)
		वापस 0;

	cpumask_copy(&cpumask, &iucv_buffer_cpumask);
	cpumask_clear_cpu(cpu, &cpumask);
	अगर (cpumask_empty(&cpumask))
		/* Can't offline last IUCV enabled cpu. */
		वापस -EINVAL;

	iucv_retrieve_cpu(शून्य);
	अगर (!cpumask_empty(&iucv_irq_cpumask))
		वापस 0;
	smp_call_function_single(cpumask_first(&iucv_buffer_cpumask),
				 iucv_allow_cpu, शून्य, 1);
	वापस 0;
पूर्ण

/**
 * iucv_sever_pathid
 * @pathid: path identअगरication number.
 * @userdata: 16-bytes of user data.
 *
 * Sever an iucv path to मुक्त up the pathid. Used पूर्णांकernally.
 */
अटल पूर्णांक iucv_sever_pathid(u16 pathid, u8 *userdata)
अणु
	जोड़ iucv_param *parm;

	parm = iucv_param_irq[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	अगर (userdata)
		स_नकल(parm->ctrl.ipuser, userdata, माप(parm->ctrl.ipuser));
	parm->ctrl.ippathid = pathid;
	वापस iucv_call_b2f0(IUCV_SEVER, parm);
पूर्ण

/**
 * __iucv_cleanup_queue
 * @dummy: unused dummy argument
 *
 * Nop function called via smp_call_function to क्रमce work items from
 * pending बाह्यal iucv पूर्णांकerrupts to the work queue.
 */
अटल व्योम __iucv_cleanup_queue(व्योम *dummy)
अणु
पूर्ण

/**
 * iucv_cleanup_queue
 *
 * Function called after a path has been severed to find all reमुख्यing
 * work items क्रम the now stale pathid. The caller needs to hold the
 * iucv_table_lock.
 */
अटल व्योम iucv_cleanup_queue(व्योम)
अणु
	काष्ठा iucv_irq_list *p, *n;

	/*
	 * When a path is severed, the pathid can be reused immediately
	 * on a iucv connect or a connection pending पूर्णांकerrupt. Remove
	 * all entries from the task queue that refer to a stale pathid
	 * (iucv_path_table[ix] == शून्य). Only then करो the iucv connect
	 * or deliver the connection pending पूर्णांकerrupt. To get all the
	 * pending पूर्णांकerrupts क्रमce them to the work queue by calling
	 * an empty function on all cpus.
	 */
	smp_call_function(__iucv_cleanup_queue, शून्य, 1);
	spin_lock_irq(&iucv_queue_lock);
	list_क्रम_each_entry_safe(p, n, &iucv_task_queue, list) अणु
		/* Remove stale work items from the task queue. */
		अगर (iucv_path_table[p->data.ippathid] == शून्य) अणु
			list_del(&p->list);
			kमुक्त(p);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&iucv_queue_lock);
पूर्ण

/**
 * iucv_रेजिस्टर:
 * @handler: address of iucv handler काष्ठाure
 * @smp: != 0 indicates that the handler can deal with out of order messages
 *
 * Registers a driver with IUCV.
 *
 * Returns 0 on success, -ENOMEM अगर the memory allocation क्रम the pathid
 * table failed, or -EIO अगर IUCV_DECLARE_BUFFER failed on all cpus.
 */
पूर्णांक iucv_रेजिस्टर(काष्ठा iucv_handler *handler, पूर्णांक smp)
अणु
	पूर्णांक rc;

	अगर (!iucv_available)
		वापस -ENOSYS;
	mutex_lock(&iucv_रेजिस्टर_mutex);
	अगर (!smp)
		iucv_nonsmp_handler++;
	अगर (list_empty(&iucv_handler_list)) अणु
		rc = iucv_enable();
		अगर (rc)
			जाओ out_mutex;
	पूर्ण अन्यथा अगर (!smp && iucv_nonsmp_handler == 1)
		iucv_seपंचांगask_up();
	INIT_LIST_HEAD(&handler->paths);

	spin_lock_bh(&iucv_table_lock);
	list_add_tail(&handler->list, &iucv_handler_list);
	spin_unlock_bh(&iucv_table_lock);
	rc = 0;
out_mutex:
	mutex_unlock(&iucv_रेजिस्टर_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_रेजिस्टर);

/**
 * iucv_unरेजिस्टर
 * @handler:  address of iucv handler काष्ठाure
 * @smp: != 0 indicates that the handler can deal with out of order messages
 *
 * Unरेजिस्टर driver from IUCV.
 */
व्योम iucv_unरेजिस्टर(काष्ठा iucv_handler *handler, पूर्णांक smp)
अणु
	काष्ठा iucv_path *p, *n;

	mutex_lock(&iucv_रेजिस्टर_mutex);
	spin_lock_bh(&iucv_table_lock);
	/* Remove handler from the iucv_handler_list. */
	list_del_init(&handler->list);
	/* Sever all pathids still referring to the handler. */
	list_क्रम_each_entry_safe(p, n, &handler->paths, list) अणु
		iucv_sever_pathid(p->pathid, शून्य);
		iucv_path_table[p->pathid] = शून्य;
		list_del(&p->list);
		iucv_path_मुक्त(p);
	पूर्ण
	spin_unlock_bh(&iucv_table_lock);
	अगर (!smp)
		iucv_nonsmp_handler--;
	अगर (list_empty(&iucv_handler_list))
		iucv_disable();
	अन्यथा अगर (!smp && iucv_nonsmp_handler == 0)
		iucv_seपंचांगask_mp();
	mutex_unlock(&iucv_रेजिस्टर_mutex);
पूर्ण
EXPORT_SYMBOL(iucv_unरेजिस्टर);

अटल पूर्णांक iucv_reboot_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	पूर्णांक i;

	अगर (cpumask_empty(&iucv_irq_cpumask))
		वापस NOTIFY_DONE;

	get_online_cpus();
	on_each_cpu_mask(&iucv_irq_cpumask, iucv_block_cpu, शून्य, 1);
	preempt_disable();
	क्रम (i = 0; i < iucv_max_pathid; i++) अणु
		अगर (iucv_path_table[i])
			iucv_sever_pathid(i, शून्य);
	पूर्ण
	preempt_enable();
	put_online_cpus();
	iucv_disable();
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block iucv_reboot_notअगरier = अणु
	.notअगरier_call = iucv_reboot_event,
पूर्ण;

/**
 * iucv_path_accept
 * @path: address of iucv path काष्ठाure
 * @handler: address of iucv handler काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 * @निजी: निजी data passed to पूर्णांकerrupt handlers क्रम this path
 *
 * This function is issued after the user received a connection pending
 * बाह्यal पूर्णांकerrupt and now wishes to complete the IUCV communication path.
 *
 * Returns the result of the CP IUCV call.
 */
पूर्णांक iucv_path_accept(काष्ठा iucv_path *path, काष्ठा iucv_handler *handler,
		     u8 *userdata, व्योम *निजी)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	/* Prepare parameter block. */
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->ctrl.ippathid = path->pathid;
	parm->ctrl.ipmsglim = path->msglim;
	अगर (userdata)
		स_नकल(parm->ctrl.ipuser, userdata, माप(parm->ctrl.ipuser));
	parm->ctrl.ipflags1 = path->flags;

	rc = iucv_call_b2f0(IUCV_ACCEPT, parm);
	अगर (!rc) अणु
		path->निजी = निजी;
		path->msglim = parm->ctrl.ipmsglim;
		path->flags = parm->ctrl.ipflags1;
	पूर्ण
out:
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_path_accept);

/**
 * iucv_path_connect
 * @path: address of iucv path काष्ठाure
 * @handler: address of iucv handler काष्ठाure
 * @userid: 8-byte user identअगरication
 * @प्रणाली: 8-byte target प्रणाली identअगरication
 * @userdata: 16 bytes of data reflected to the communication partner
 * @निजी: निजी data passed to पूर्णांकerrupt handlers क्रम this path
 *
 * This function establishes an IUCV path. Although the connect may complete
 * successfully, you are not able to use the path until you receive an IUCV
 * Connection Complete बाह्यal पूर्णांकerrupt.
 *
 * Returns the result of the CP IUCV call.
 */
पूर्णांक iucv_path_connect(काष्ठा iucv_path *path, काष्ठा iucv_handler *handler,
		      u8 *userid, u8 *प्रणाली, u8 *userdata,
		      व्योम *निजी)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	spin_lock_bh(&iucv_table_lock);
	iucv_cleanup_queue();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->ctrl.ipmsglim = path->msglim;
	parm->ctrl.ipflags1 = path->flags;
	अगर (userid) अणु
		स_नकल(parm->ctrl.ipvmid, userid, माप(parm->ctrl.ipvmid));
		ASCEBC(parm->ctrl.ipvmid, माप(parm->ctrl.ipvmid));
		EBC_TOUPPER(parm->ctrl.ipvmid, माप(parm->ctrl.ipvmid));
	पूर्ण
	अगर (प्रणाली) अणु
		स_नकल(parm->ctrl.iptarget, प्रणाली,
		       माप(parm->ctrl.iptarget));
		ASCEBC(parm->ctrl.iptarget, माप(parm->ctrl.iptarget));
		EBC_TOUPPER(parm->ctrl.iptarget, माप(parm->ctrl.iptarget));
	पूर्ण
	अगर (userdata)
		स_नकल(parm->ctrl.ipuser, userdata, माप(parm->ctrl.ipuser));

	rc = iucv_call_b2f0(IUCV_CONNECT, parm);
	अगर (!rc) अणु
		अगर (parm->ctrl.ippathid < iucv_max_pathid) अणु
			path->pathid = parm->ctrl.ippathid;
			path->msglim = parm->ctrl.ipmsglim;
			path->flags = parm->ctrl.ipflags1;
			path->handler = handler;
			path->निजी = निजी;
			list_add_tail(&path->list, &handler->paths);
			iucv_path_table[path->pathid] = path;
		पूर्ण अन्यथा अणु
			iucv_sever_pathid(parm->ctrl.ippathid,
					  iucv_error_pathid);
			rc = -EIO;
		पूर्ण
	पूर्ण
out:
	spin_unlock_bh(&iucv_table_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_path_connect);

/**
 * iucv_path_quiesce:
 * @path: address of iucv path काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 *
 * This function temporarily suspends incoming messages on an IUCV path.
 * You can later reactivate the path by invoking the iucv_resume function.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_path_quiesce(काष्ठा iucv_path *path, u8 *userdata)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	अगर (userdata)
		स_नकल(parm->ctrl.ipuser, userdata, माप(parm->ctrl.ipuser));
	parm->ctrl.ippathid = path->pathid;
	rc = iucv_call_b2f0(IUCV_QUIESCE, parm);
out:
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_path_quiesce);

/**
 * iucv_path_resume:
 * @path: address of iucv path काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 *
 * This function resumes incoming messages on an IUCV path that has
 * been stopped with iucv_path_quiesce.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_path_resume(काष्ठा iucv_path *path, u8 *userdata)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	अगर (userdata)
		स_नकल(parm->ctrl.ipuser, userdata, माप(parm->ctrl.ipuser));
	parm->ctrl.ippathid = path->pathid;
	rc = iucv_call_b2f0(IUCV_RESUME, parm);
out:
	local_bh_enable();
	वापस rc;
पूर्ण

/**
 * iucv_path_sever
 * @path: address of iucv path काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 *
 * This function terminates an IUCV path.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_path_sever(काष्ठा iucv_path *path, u8 *userdata)
अणु
	पूर्णांक rc;

	preempt_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (iucv_active_cpu != smp_processor_id())
		spin_lock_bh(&iucv_table_lock);
	rc = iucv_sever_pathid(path->pathid, userdata);
	iucv_path_table[path->pathid] = शून्य;
	list_del_init(&path->list);
	अगर (iucv_active_cpu != smp_processor_id())
		spin_unlock_bh(&iucv_table_lock);
out:
	preempt_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_path_sever);

/**
 * iucv_message_purge
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @srccls: source class of message
 *
 * Cancels a message you have sent.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_purge(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		       u32 srccls)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->purge.ippathid = path->pathid;
	parm->purge.ipmsgid = msg->id;
	parm->purge.ipsrccls = srccls;
	parm->purge.ipflags1 = IUCV_IPSRCCLS | IUCV_IPFGMID | IUCV_IPFGPID;
	rc = iucv_call_b2f0(IUCV_PURGE, parm);
	अगर (!rc) अणु
		msg->audit = (*(u32 *) &parm->purge.ipaudit) >> 8;
		msg->tag = parm->purge.ipmsgtag;
	पूर्ण
out:
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_message_purge);

/**
 * iucv_message_receive_iprmdata
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is received (IUCV_IPBUFLST)
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of data buffer
 * @residual:
 *
 * Internal function used by iucv_message_receive and __iucv_message_receive
 * to receive RMDATA data stored in काष्ठा iucv_message.
 */
अटल पूर्णांक iucv_message_receive_iprmdata(काष्ठा iucv_path *path,
					 काष्ठा iucv_message *msg,
					 u8 flags, व्योम *buffer,
					 माप_प्रकार size, माप_प्रकार *residual)
अणु
	काष्ठा iucv_array *array;
	u8 *rmmsg;
	माप_प्रकार copy;

	/*
	 * Message is 8 bytes दीर्घ and has been stored to the
	 * message descriptor itself.
	 */
	अगर (residual)
		*residual = असल(size - 8);
	rmmsg = msg->rmmsg;
	अगर (flags & IUCV_IPBUFLST) अणु
		/* Copy to काष्ठा iucv_array. */
		size = (size < 8) ? size : 8;
		क्रम (array = buffer; size > 0; array++) अणु
			copy = min_t(माप_प्रकार, size, array->length);
			स_नकल((u8 *)(addr_t) array->address,
				rmmsg, copy);
			rmmsg += copy;
			size -= copy;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Copy to direct buffer. */
		स_नकल(buffer, rmmsg, min_t(माप_प्रकार, size, 8));
	पूर्ण
	वापस 0;
पूर्ण

/**
 * __iucv_message_receive
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is received (IUCV_IPBUFLST)
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of data buffer
 * @residual:
 *
 * This function receives messages that are being sent to you over
 * established paths. This function will deal with RMDATA messages
 * embedded in काष्ठा iucv_message as well.
 *
 * Locking:	no locking
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक __iucv_message_receive(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			   u8 flags, व्योम *buffer, माप_प्रकार size, माप_प्रकार *residual)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	अगर (msg->flags & IUCV_IPRMDATA)
		वापस iucv_message_receive_iprmdata(path, msg, flags,
						     buffer, size, residual);
	अगर (cpumask_empty(&iucv_buffer_cpumask))
		वापस -EIO;

	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->db.ipbfadr1 = (u32)(addr_t) buffer;
	parm->db.ipbfln1f = (u32) size;
	parm->db.ipmsgid = msg->id;
	parm->db.ippathid = path->pathid;
	parm->db.iptrgcls = msg->class;
	parm->db.ipflags1 = (flags | IUCV_IPFGPID |
			     IUCV_IPFGMID | IUCV_IPTRGCLS);
	rc = iucv_call_b2f0(IUCV_RECEIVE, parm);
	अगर (!rc || rc == 5) अणु
		msg->flags = parm->db.ipflags1;
		अगर (residual)
			*residual = parm->db.ipbfln1f;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(__iucv_message_receive);

/**
 * iucv_message_receive
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is received (IUCV_IPBUFLST)
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of data buffer
 * @residual:
 *
 * This function receives messages that are being sent to you over
 * established paths. This function will deal with RMDATA messages
 * embedded in काष्ठा iucv_message as well.
 *
 * Locking:	local_bh_enable/local_bh_disable
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_receive(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			 u8 flags, व्योम *buffer, माप_प्रकार size, माप_प्रकार *residual)
अणु
	पूर्णांक rc;

	अगर (msg->flags & IUCV_IPRMDATA)
		वापस iucv_message_receive_iprmdata(path, msg, flags,
						     buffer, size, residual);
	local_bh_disable();
	rc = __iucv_message_receive(path, msg, flags, buffer, size, residual);
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_message_receive);

/**
 * iucv_message_reject
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 *
 * The reject function refuses a specअगरied message. Between the समय you
 * are notअगरied of a message and the समय that you complete the message,
 * the message may be rejected.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_reject(काष्ठा iucv_path *path, काष्ठा iucv_message *msg)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	parm->db.ippathid = path->pathid;
	parm->db.ipmsgid = msg->id;
	parm->db.iptrgcls = msg->class;
	parm->db.ipflags1 = (IUCV_IPTRGCLS | IUCV_IPFGMID | IUCV_IPFGPID);
	rc = iucv_call_b2f0(IUCV_REJECT, parm);
out:
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_message_reject);

/**
 * iucv_message_reply
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the reply is sent (IUCV_IPRMDATA, IUCV_IPPRTY, IUCV_IPBUFLST)
 * @reply: address of reply data buffer or address of काष्ठा iucv_array
 * @size: length of reply data buffer
 *
 * This function responds to the two-way messages that you receive. You
 * must identअगरy completely the message to which you wish to reply. ie,
 * pathid, msgid, and trgcls. Prmmsg signअगरies the data is moved पूर्णांकo
 * the parameter list.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_reply(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		       u8 flags, व्योम *reply, माप_प्रकार size)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	अगर (flags & IUCV_IPRMDATA) अणु
		parm->dpl.ippathid = path->pathid;
		parm->dpl.ipflags1 = flags;
		parm->dpl.ipmsgid = msg->id;
		parm->dpl.iptrgcls = msg->class;
		स_नकल(parm->dpl.iprmmsg, reply, min_t(माप_प्रकार, size, 8));
	पूर्ण अन्यथा अणु
		parm->db.ipbfadr1 = (u32)(addr_t) reply;
		parm->db.ipbfln1f = (u32) size;
		parm->db.ippathid = path->pathid;
		parm->db.ipflags1 = flags;
		parm->db.ipmsgid = msg->id;
		parm->db.iptrgcls = msg->class;
	पूर्ण
	rc = iucv_call_b2f0(IUCV_REPLY, parm);
out:
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_message_reply);

/**
 * __iucv_message_send
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is sent (IUCV_IPRMDATA, IUCV_IPPRTY, IUCV_IPBUFLST)
 * @srccls: source class of message
 * @buffer: address of send buffer or address of काष्ठा iucv_array
 * @size: length of send buffer
 *
 * This function transmits data to another application. Data to be
 * transmitted is in a buffer and this is a one-way message and the
 * receiver will not reply to the message.
 *
 * Locking:	no locking
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक __iucv_message_send(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		      u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	अगर (flags & IUCV_IPRMDATA) अणु
		/* Message of 8 bytes can be placed पूर्णांकo the parameter list. */
		parm->dpl.ippathid = path->pathid;
		parm->dpl.ipflags1 = flags | IUCV_IPNORPY;
		parm->dpl.iptrgcls = msg->class;
		parm->dpl.ipsrccls = srccls;
		parm->dpl.ipmsgtag = msg->tag;
		स_नकल(parm->dpl.iprmmsg, buffer, 8);
	पूर्ण अन्यथा अणु
		parm->db.ipbfadr1 = (u32)(addr_t) buffer;
		parm->db.ipbfln1f = (u32) size;
		parm->db.ippathid = path->pathid;
		parm->db.ipflags1 = flags | IUCV_IPNORPY;
		parm->db.iptrgcls = msg->class;
		parm->db.ipsrccls = srccls;
		parm->db.ipmsgtag = msg->tag;
	पूर्ण
	rc = iucv_call_b2f0(IUCV_SEND, parm);
	अगर (!rc)
		msg->id = parm->db.ipmsgid;
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(__iucv_message_send);

/**
 * iucv_message_send
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is sent (IUCV_IPRMDATA, IUCV_IPPRTY, IUCV_IPBUFLST)
 * @srccls: source class of message
 * @buffer: address of send buffer or address of काष्ठा iucv_array
 * @size: length of send buffer
 *
 * This function transmits data to another application. Data to be
 * transmitted is in a buffer and this is a one-way message and the
 * receiver will not reply to the message.
 *
 * Locking:	local_bh_enable/local_bh_disable
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_send(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		      u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक rc;

	local_bh_disable();
	rc = __iucv_message_send(path, msg, flags, srccls, buffer, size);
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_message_send);

/**
 * iucv_message_send2way
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is sent and the reply is received
 *	   (IUCV_IPRMDATA, IUCV_IPBUFLST, IUCV_IPPRTY, IUCV_ANSLST)
 * @srccls: source class of message
 * @buffer: address of send buffer or address of काष्ठा iucv_array
 * @size: length of send buffer
 * @ansbuf: address of answer buffer or address of काष्ठा iucv_array
 * @asize: size of reply buffer
 *
 * This function transmits data to another application. Data to be
 * transmitted is in a buffer. The receiver of the send is expected to
 * reply to the message and a buffer is provided पूर्णांकo which IUCV moves
 * the reply to this message.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_send2way(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			  u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size,
			  व्योम *answer, माप_प्रकार asize, माप_प्रकार *residual)
अणु
	जोड़ iucv_param *parm;
	पूर्णांक rc;

	local_bh_disable();
	अगर (cpumask_empty(&iucv_buffer_cpumask)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	parm = iucv_param[smp_processor_id()];
	स_रखो(parm, 0, माप(जोड़ iucv_param));
	अगर (flags & IUCV_IPRMDATA) अणु
		parm->dpl.ippathid = path->pathid;
		parm->dpl.ipflags1 = path->flags;	/* priority message */
		parm->dpl.iptrgcls = msg->class;
		parm->dpl.ipsrccls = srccls;
		parm->dpl.ipmsgtag = msg->tag;
		parm->dpl.ipbfadr2 = (u32)(addr_t) answer;
		parm->dpl.ipbfln2f = (u32) asize;
		स_नकल(parm->dpl.iprmmsg, buffer, 8);
	पूर्ण अन्यथा अणु
		parm->db.ippathid = path->pathid;
		parm->db.ipflags1 = path->flags;	/* priority message */
		parm->db.iptrgcls = msg->class;
		parm->db.ipsrccls = srccls;
		parm->db.ipmsgtag = msg->tag;
		parm->db.ipbfadr1 = (u32)(addr_t) buffer;
		parm->db.ipbfln1f = (u32) size;
		parm->db.ipbfadr2 = (u32)(addr_t) answer;
		parm->db.ipbfln2f = (u32) asize;
	पूर्ण
	rc = iucv_call_b2f0(IUCV_SEND, parm);
	अगर (!rc)
		msg->id = parm->db.ipmsgid;
out:
	local_bh_enable();
	वापस rc;
पूर्ण
EXPORT_SYMBOL(iucv_message_send2way);

/**
 * iucv_path_pending
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process connection pending work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_path_pending अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iptype;
	u16 ipmsglim;
	u16 res1;
	u8  ipvmid[8];
	u8  ipuser[16];
	u32 res3;
	u8  ippollfg;
	u8  res4[3];
पूर्ण __packed;

अटल व्योम iucv_path_pending(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_path_pending *ipp = (व्योम *) data;
	काष्ठा iucv_handler *handler;
	काष्ठा iucv_path *path;
	अक्षर *error;

	BUG_ON(iucv_path_table[ipp->ippathid]);
	/* New pathid, handler found. Create a new path काष्ठा. */
	error = iucv_error_no_memory;
	path = iucv_path_alloc(ipp->ipmsglim, ipp->ipflags1, GFP_ATOMIC);
	अगर (!path)
		जाओ out_sever;
	path->pathid = ipp->ippathid;
	iucv_path_table[path->pathid] = path;
	EBCASC(ipp->ipvmid, 8);

	/* Call रेजिस्टरed handler until one is found that wants the path. */
	list_क्रम_each_entry(handler, &iucv_handler_list, list) अणु
		अगर (!handler->path_pending)
			जारी;
		/*
		 * Add path to handler to allow a call to iucv_path_sever
		 * inside the path_pending function. If the handler वापसs
		 * an error हटाओ the path from the handler again.
		 */
		list_add(&path->list, &handler->paths);
		path->handler = handler;
		अगर (!handler->path_pending(path, ipp->ipvmid, ipp->ipuser))
			वापस;
		list_del(&path->list);
		path->handler = शून्य;
	पूर्ण
	/* No handler wanted the path. */
	iucv_path_table[path->pathid] = शून्य;
	iucv_path_मुक्त(path);
	error = iucv_error_no_listener;
out_sever:
	iucv_sever_pathid(ipp->ippathid, error);
पूर्ण

/**
 * iucv_path_complete
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process connection complete work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_path_complete अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iptype;
	u16 ipmsglim;
	u16 res1;
	u8  res2[8];
	u8  ipuser[16];
	u32 res3;
	u8  ippollfg;
	u8  res4[3];
पूर्ण __packed;

अटल व्योम iucv_path_complete(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_path_complete *ipc = (व्योम *) data;
	काष्ठा iucv_path *path = iucv_path_table[ipc->ippathid];

	अगर (path)
		path->flags = ipc->ipflags1;
	अगर (path && path->handler && path->handler->path_complete)
		path->handler->path_complete(path, ipc->ipuser);
पूर्ण

/**
 * iucv_path_severed
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process connection severed work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_path_severed अणु
	u16 ippathid;
	u8  res1;
	u8  iptype;
	u32 res2;
	u8  res3[8];
	u8  ipuser[16];
	u32 res4;
	u8  ippollfg;
	u8  res5[3];
पूर्ण __packed;

अटल व्योम iucv_path_severed(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_path_severed *ips = (व्योम *) data;
	काष्ठा iucv_path *path = iucv_path_table[ips->ippathid];

	अगर (!path || !path->handler)	/* Alपढ़ोy severed */
		वापस;
	अगर (path->handler->path_severed)
		path->handler->path_severed(path, ips->ipuser);
	अन्यथा अणु
		iucv_sever_pathid(path->pathid, शून्य);
		iucv_path_table[path->pathid] = शून्य;
		list_del(&path->list);
		iucv_path_मुक्त(path);
	पूर्ण
पूर्ण

/**
 * iucv_path_quiesced
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process connection quiesced work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_path_quiesced अणु
	u16 ippathid;
	u8  res1;
	u8  iptype;
	u32 res2;
	u8  res3[8];
	u8  ipuser[16];
	u32 res4;
	u8  ippollfg;
	u8  res5[3];
पूर्ण __packed;

अटल व्योम iucv_path_quiesced(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_path_quiesced *ipq = (व्योम *) data;
	काष्ठा iucv_path *path = iucv_path_table[ipq->ippathid];

	अगर (path && path->handler && path->handler->path_quiesced)
		path->handler->path_quiesced(path, ipq->ipuser);
पूर्ण

/**
 * iucv_path_resumed
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process connection resumed work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_path_resumed अणु
	u16 ippathid;
	u8  res1;
	u8  iptype;
	u32 res2;
	u8  res3[8];
	u8  ipuser[16];
	u32 res4;
	u8  ippollfg;
	u8  res5[3];
पूर्ण __packed;

अटल व्योम iucv_path_resumed(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_path_resumed *ipr = (व्योम *) data;
	काष्ठा iucv_path *path = iucv_path_table[ipr->ippathid];

	अगर (path && path->handler && path->handler->path_resumed)
		path->handler->path_resumed(path, ipr->ipuser);
पूर्ण

/**
 * iucv_message_complete
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process message complete work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_message_complete अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iptype;
	u32 ipmsgid;
	u32 ipaudit;
	u8  iprmmsg[8];
	u32 ipsrccls;
	u32 ipmsgtag;
	u32 res;
	u32 ipbfln2f;
	u8  ippollfg;
	u8  res2[3];
पूर्ण __packed;

अटल व्योम iucv_message_complete(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_message_complete *imc = (व्योम *) data;
	काष्ठा iucv_path *path = iucv_path_table[imc->ippathid];
	काष्ठा iucv_message msg;

	अगर (path && path->handler && path->handler->message_complete) अणु
		msg.flags = imc->ipflags1;
		msg.id = imc->ipmsgid;
		msg.audit = imc->ipaudit;
		स_नकल(msg.rmmsg, imc->iprmmsg, 8);
		msg.class = imc->ipsrccls;
		msg.tag = imc->ipmsgtag;
		msg.length = imc->ipbfln2f;
		path->handler->message_complete(path, &msg);
	पूर्ण
पूर्ण

/**
 * iucv_message_pending
 * @data: Poपूर्णांकer to बाह्यal पूर्णांकerrupt buffer
 *
 * Process message pending work item. Called from tasklet जबतक holding
 * iucv_table_lock.
 */
काष्ठा iucv_message_pending अणु
	u16 ippathid;
	u8  ipflags1;
	u8  iptype;
	u32 ipmsgid;
	u32 iptrgcls;
	जोड़ अणु
		u32 iprmmsg1_u32;
		u8  iprmmsg1[4];
	पूर्ण ln1msg1;
	जोड़ अणु
		u32 ipbfln1f;
		u8  iprmmsg2[4];
	पूर्ण ln1msg2;
	u32 res1[3];
	u32 ipbfln2f;
	u8  ippollfg;
	u8  res2[3];
पूर्ण __packed;

अटल व्योम iucv_message_pending(काष्ठा iucv_irq_data *data)
अणु
	काष्ठा iucv_message_pending *imp = (व्योम *) data;
	काष्ठा iucv_path *path = iucv_path_table[imp->ippathid];
	काष्ठा iucv_message msg;

	अगर (path && path->handler && path->handler->message_pending) अणु
		msg.flags = imp->ipflags1;
		msg.id = imp->ipmsgid;
		msg.class = imp->iptrgcls;
		अगर (imp->ipflags1 & IUCV_IPRMDATA) अणु
			स_नकल(msg.rmmsg, imp->ln1msg1.iprmmsg1, 8);
			msg.length = 8;
		पूर्ण अन्यथा
			msg.length = imp->ln1msg2.ipbfln1f;
		msg.reply_size = imp->ipbfln2f;
		path->handler->message_pending(path, &msg);
	पूर्ण
पूर्ण

/**
 * iucv_tasklet_fn:
 *
 * This tasklet loops over the queue of irq buffers created by
 * iucv_बाह्यal_पूर्णांकerrupt, calls the appropriate action handler
 * and then मुक्तs the buffer.
 */
अटल व्योम iucv_tasklet_fn(अचिन्हित दीर्घ ignored)
अणु
	प्रकार व्योम iucv_irq_fn(काष्ठा iucv_irq_data *);
	अटल iucv_irq_fn *irq_fn[] = अणु
		[0x02] = iucv_path_complete,
		[0x03] = iucv_path_severed,
		[0x04] = iucv_path_quiesced,
		[0x05] = iucv_path_resumed,
		[0x06] = iucv_message_complete,
		[0x07] = iucv_message_complete,
		[0x08] = iucv_message_pending,
		[0x09] = iucv_message_pending,
	पूर्ण;
	LIST_HEAD(task_queue);
	काष्ठा iucv_irq_list *p, *n;

	/* Serialize tasklet, iucv_path_sever and iucv_path_connect. */
	अगर (!spin_trylock(&iucv_table_lock)) अणु
		tasklet_schedule(&iucv_tasklet);
		वापस;
	पूर्ण
	iucv_active_cpu = smp_processor_id();

	spin_lock_irq(&iucv_queue_lock);
	list_splice_init(&iucv_task_queue, &task_queue);
	spin_unlock_irq(&iucv_queue_lock);

	list_क्रम_each_entry_safe(p, n, &task_queue, list) अणु
		list_del_init(&p->list);
		irq_fn[p->data.iptype](&p->data);
		kमुक्त(p);
	पूर्ण

	iucv_active_cpu = -1;
	spin_unlock(&iucv_table_lock);
पूर्ण

/**
 * iucv_work_fn:
 *
 * This work function loops over the queue of path pending irq blocks
 * created by iucv_बाह्यal_पूर्णांकerrupt, calls the appropriate action
 * handler and then मुक्तs the buffer.
 */
अटल व्योम iucv_work_fn(काष्ठा work_काष्ठा *work)
अणु
	LIST_HEAD(work_queue);
	काष्ठा iucv_irq_list *p, *n;

	/* Serialize tasklet, iucv_path_sever and iucv_path_connect. */
	spin_lock_bh(&iucv_table_lock);
	iucv_active_cpu = smp_processor_id();

	spin_lock_irq(&iucv_queue_lock);
	list_splice_init(&iucv_work_queue, &work_queue);
	spin_unlock_irq(&iucv_queue_lock);

	iucv_cleanup_queue();
	list_क्रम_each_entry_safe(p, n, &work_queue, list) अणु
		list_del_init(&p->list);
		iucv_path_pending(&p->data);
		kमुक्त(p);
	पूर्ण

	iucv_active_cpu = -1;
	spin_unlock_bh(&iucv_table_lock);
पूर्ण

/**
 * iucv_बाह्यal_पूर्णांकerrupt
 * @code: irq code
 *
 * Handles बाह्यal पूर्णांकerrupts coming in from CP.
 * Places the पूर्णांकerrupt buffer on a queue and schedules iucv_tasklet_fn().
 */
अटल व्योम iucv_बाह्यal_पूर्णांकerrupt(काष्ठा ext_code ext_code,
				    अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	काष्ठा iucv_irq_data *p;
	काष्ठा iucv_irq_list *work;

	inc_irq_stat(IRQEXT_IUC);
	p = iucv_irq_data[smp_processor_id()];
	अगर (p->ippathid >= iucv_max_pathid) अणु
		WARN_ON(p->ippathid >= iucv_max_pathid);
		iucv_sever_pathid(p->ippathid, iucv_error_no_listener);
		वापस;
	पूर्ण
	BUG_ON(p->iptype  < 0x01 || p->iptype > 0x09);
	work = kदो_स्मृति(माप(काष्ठा iucv_irq_list), GFP_ATOMIC);
	अगर (!work) अणु
		pr_warn("iucv_external_interrupt: out of memory\n");
		वापस;
	पूर्ण
	स_नकल(&work->data, p, माप(work->data));
	spin_lock(&iucv_queue_lock);
	अगर (p->iptype == 0x01) अणु
		/* Path pending पूर्णांकerrupt. */
		list_add_tail(&work->list, &iucv_work_queue);
		schedule_work(&iucv_work);
	पूर्ण अन्यथा अणु
		/* The other पूर्णांकerrupts. */
		list_add_tail(&work->list, &iucv_task_queue);
		tasklet_schedule(&iucv_tasklet);
	पूर्ण
	spin_unlock(&iucv_queue_lock);
पूर्ण

काष्ठा iucv_पूर्णांकerface iucv_अगर = अणु
	.message_receive = iucv_message_receive,
	.__message_receive = __iucv_message_receive,
	.message_reply = iucv_message_reply,
	.message_reject = iucv_message_reject,
	.message_send = iucv_message_send,
	.__message_send = __iucv_message_send,
	.message_send2way = iucv_message_send2way,
	.message_purge = iucv_message_purge,
	.path_accept = iucv_path_accept,
	.path_connect = iucv_path_connect,
	.path_quiesce = iucv_path_quiesce,
	.path_resume = iucv_path_resume,
	.path_sever = iucv_path_sever,
	.iucv_रेजिस्टर = iucv_रेजिस्टर,
	.iucv_unरेजिस्टर = iucv_unरेजिस्टर,
	.bus = शून्य,
	.root = शून्य,
पूर्ण;
EXPORT_SYMBOL(iucv_अगर);

अटल क्रमागत cpuhp_state iucv_online;
/**
 * iucv_init
 *
 * Allocates and initializes various data काष्ठाures.
 */
अटल पूर्णांक __init iucv_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM) अणु
		rc = -EPROTONOSUPPORT;
		जाओ out;
	पूर्ण
	ctl_set_bit(0, 1);
	rc = iucv_query_maxconn();
	अगर (rc)
		जाओ out_ctl;
	rc = रेजिस्टर_बाह्यal_irq(EXT_IRQ_IUCV, iucv_बाह्यal_पूर्णांकerrupt);
	अगर (rc)
		जाओ out_ctl;
	iucv_root = root_device_रेजिस्टर("iucv");
	अगर (IS_ERR(iucv_root)) अणु
		rc = PTR_ERR(iucv_root);
		जाओ out_पूर्णांक;
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_NET_IUCV_PREPARE, "net/iucv:prepare",
			       iucv_cpu_prepare, iucv_cpu_dead);
	अगर (rc)
		जाओ out_dev;
	rc = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "net/iucv:online",
			       iucv_cpu_online, iucv_cpu_करोwn_prep);
	अगर (rc < 0)
		जाओ out_prep;
	iucv_online = rc;

	rc = रेजिस्टर_reboot_notअगरier(&iucv_reboot_notअगरier);
	अगर (rc)
		जाओ out_हटाओ_hp;
	ASCEBC(iucv_error_no_listener, 16);
	ASCEBC(iucv_error_no_memory, 16);
	ASCEBC(iucv_error_pathid, 16);
	iucv_available = 1;
	rc = bus_रेजिस्टर(&iucv_bus);
	अगर (rc)
		जाओ out_reboot;
	iucv_अगर.root = iucv_root;
	iucv_अगर.bus = &iucv_bus;
	वापस 0;

out_reboot:
	unरेजिस्टर_reboot_notअगरier(&iucv_reboot_notअगरier);
out_हटाओ_hp:
	cpuhp_हटाओ_state(iucv_online);
out_prep:
	cpuhp_हटाओ_state(CPUHP_NET_IUCV_PREPARE);
out_dev:
	root_device_unरेजिस्टर(iucv_root);
out_पूर्णांक:
	unरेजिस्टर_बाह्यal_irq(EXT_IRQ_IUCV, iucv_बाह्यal_पूर्णांकerrupt);
out_ctl:
	ctl_clear_bit(0, 1);
out:
	वापस rc;
पूर्ण

/**
 * iucv_निकास
 *
 * Frees everything allocated from iucv_init.
 */
अटल व्योम __निकास iucv_निकास(व्योम)
अणु
	काष्ठा iucv_irq_list *p, *n;

	spin_lock_irq(&iucv_queue_lock);
	list_क्रम_each_entry_safe(p, n, &iucv_task_queue, list)
		kमुक्त(p);
	list_क्रम_each_entry_safe(p, n, &iucv_work_queue, list)
		kमुक्त(p);
	spin_unlock_irq(&iucv_queue_lock);
	unरेजिस्टर_reboot_notअगरier(&iucv_reboot_notअगरier);

	cpuhp_हटाओ_state_nocalls(iucv_online);
	cpuhp_हटाओ_state(CPUHP_NET_IUCV_PREPARE);
	root_device_unरेजिस्टर(iucv_root);
	bus_unरेजिस्टर(&iucv_bus);
	unरेजिस्टर_बाह्यal_irq(EXT_IRQ_IUCV, iucv_बाह्यal_पूर्णांकerrupt);
पूर्ण

subsys_initcall(iucv_init);
module_निकास(iucv_निकास);

MODULE_AUTHOR("(C) 2001 IBM Corp. by Fritz Elfert (felfert@millenux.com)");
MODULE_DESCRIPTION("Linux for S/390 IUCV lowlevel driver");
MODULE_LICENSE("GPL");
