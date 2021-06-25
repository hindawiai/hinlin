<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OPAL asynchronus Memory error handling support in PowerNV.
 *
 * Copyright 2013 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/cputable.h>

अटल पूर्णांक opal_mem_err_nb_init;
अटल LIST_HEAD(opal_memory_err_list);
अटल DEFINE_SPINLOCK(opal_mem_err_lock);

काष्ठा OpalMsgNode अणु
	काष्ठा list_head list;
	काष्ठा opal_msg msg;
पूर्ण;

अटल व्योम handle_memory_error_event(काष्ठा OpalMemoryErrorData *merr_evt)
अणु
	uपूर्णांक64_t paddr_start, paddr_end;

	pr_debug("%s: Retrieved memory error event, type: 0x%x\n",
		  __func__, merr_evt->type);
	चयन (merr_evt->type) अणु
	हाल OPAL_MEM_ERR_TYPE_RESILIENCE:
		paddr_start = be64_to_cpu(merr_evt->u.resilience.physical_address_start);
		paddr_end = be64_to_cpu(merr_evt->u.resilience.physical_address_end);
		अवरोध;
	हाल OPAL_MEM_ERR_TYPE_DYN_DALLOC:
		paddr_start = be64_to_cpu(merr_evt->u.dyn_dealloc.physical_address_start);
		paddr_end = be64_to_cpu(merr_evt->u.dyn_dealloc.physical_address_end);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (; paddr_start < paddr_end; paddr_start += PAGE_SIZE) अणु
		memory_failure(paddr_start >> PAGE_SHIFT, 0);
	पूर्ण
पूर्ण

अटल व्योम handle_memory_error(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा OpalMemoryErrorData *merr_evt;
	काष्ठा OpalMsgNode *msg_node;

	spin_lock_irqsave(&opal_mem_err_lock, flags);
	जबतक (!list_empty(&opal_memory_err_list)) अणु
		 msg_node = list_entry(opal_memory_err_list.next,
					   काष्ठा OpalMsgNode, list);
		list_del(&msg_node->list);
		spin_unlock_irqrestore(&opal_mem_err_lock, flags);

		merr_evt = (काष्ठा OpalMemoryErrorData *)
					&msg_node->msg.params[0];
		handle_memory_error_event(merr_evt);
		kमुक्त(msg_node);
		spin_lock_irqsave(&opal_mem_err_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&opal_mem_err_lock, flags);
पूर्ण

अटल व्योम mem_error_handler(काष्ठा work_काष्ठा *work)
अणु
	handle_memory_error();
पूर्ण

अटल DECLARE_WORK(mem_error_work, mem_error_handler);

/*
 * opal_memory_err_event - notअगरier handler that queues up the opal message
 * to be preocessed later.
 */
अटल पूर्णांक opal_memory_err_event(काष्ठा notअगरier_block *nb,
			  अचिन्हित दीर्घ msg_type, व्योम *msg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा OpalMsgNode *msg_node;

	अगर (msg_type != OPAL_MSG_MEM_ERR)
		वापस 0;

	msg_node = kzalloc(माप(*msg_node), GFP_ATOMIC);
	अगर (!msg_node) अणु
		pr_err("MEMORY_ERROR: out of memory, Opal message event not"
		       "handled\n");
		वापस -ENOMEM;
	पूर्ण
	स_नकल(&msg_node->msg, msg, माप(msg_node->msg));

	spin_lock_irqsave(&opal_mem_err_lock, flags);
	list_add(&msg_node->list, &opal_memory_err_list);
	spin_unlock_irqrestore(&opal_mem_err_lock, flags);

	schedule_work(&mem_error_work);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block opal_mem_err_nb = अणु
	.notअगरier_call	= opal_memory_err_event,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

अटल पूर्णांक __init opal_mem_err_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!opal_mem_err_nb_init) अणु
		ret = opal_message_notअगरier_रेजिस्टर(
					OPAL_MSG_MEM_ERR, &opal_mem_err_nb);
		अगर (ret) अणु
			pr_err("%s: Can't register OPAL event notifier (%d)\n",
			       __func__, ret);
			वापस ret;
		पूर्ण
		opal_mem_err_nb_init = 1;
	पूर्ण
	वापस 0;
पूर्ण
machine_device_initcall(घातernv, opal_mem_err_init);
