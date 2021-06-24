<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ds.c: Doमुख्य Services driver क्रम Logical Doमुख्यs
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/reboot.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/ldc.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/irq.h>

#समावेश "kernel.h"

#घोषणा DRV_MODULE_NAME		"ds"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_MODULE_VERSION	"1.0"
#घोषणा DRV_MODULE_RELDATE	"Jul 11, 2007"

अटल अक्षर version[] =
	DRV_MODULE_NAME ".c:v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";
MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Sun LDOM domain services driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

काष्ठा ds_msg_tag अणु
	__u32			type;
#घोषणा DS_INIT_REQ		0x00
#घोषणा DS_INIT_ACK		0x01
#घोषणा DS_INIT_NACK		0x02
#घोषणा DS_REG_REQ		0x03
#घोषणा DS_REG_ACK		0x04
#घोषणा DS_REG_NACK		0x05
#घोषणा DS_UNREG_REQ		0x06
#घोषणा DS_UNREG_ACK		0x07
#घोषणा DS_UNREG_NACK		0x08
#घोषणा DS_DATA			0x09
#घोषणा DS_NACK			0x0a

	__u32			len;
पूर्ण;

/* Result codes */
#घोषणा DS_OK			0x00
#घोषणा DS_REG_VER_NACK		0x01
#घोषणा DS_REG_DUP		0x02
#घोषणा DS_INV_HDL		0x03
#घोषणा DS_TYPE_UNKNOWN		0x04

काष्ठा ds_version अणु
	__u16			major;
	__u16			minor;
पूर्ण;

काष्ठा ds_ver_req अणु
	काष्ठा ds_msg_tag	tag;
	काष्ठा ds_version	ver;
पूर्ण;

काष्ठा ds_ver_ack अणु
	काष्ठा ds_msg_tag	tag;
	__u16			minor;
पूर्ण;

काष्ठा ds_ver_nack अणु
	काष्ठा ds_msg_tag	tag;
	__u16			major;
पूर्ण;

काष्ठा ds_reg_req अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
	__u16			major;
	__u16			minor;
	अक्षर			svc_id[];
पूर्ण;

काष्ठा ds_reg_ack अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
	__u16			minor;
पूर्ण;

काष्ठा ds_reg_nack अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
	__u16			major;
पूर्ण;

काष्ठा ds_unreg_req अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
पूर्ण;

काष्ठा ds_unreg_ack अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
पूर्ण;

काष्ठा ds_unreg_nack अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
पूर्ण;

काष्ठा ds_data अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
पूर्ण;

काष्ठा ds_data_nack अणु
	काष्ठा ds_msg_tag	tag;
	__u64			handle;
	__u64			result;
पूर्ण;

काष्ठा ds_info;
काष्ठा ds_cap_state अणु
	__u64			handle;

	व्योम			(*data)(काष्ठा ds_info *dp,
					काष्ठा ds_cap_state *cp,
					व्योम *buf, पूर्णांक len);

	स्थिर अक्षर		*service_id;

	u8			state;
#घोषणा CAP_STATE_UNKNOWN	0x00
#घोषणा CAP_STATE_REG_SENT	0x01
#घोषणा CAP_STATE_REGISTERED	0x02
पूर्ण;

अटल व्योम md_update_data(काष्ठा ds_info *dp, काष्ठा ds_cap_state *cp,
			   व्योम *buf, पूर्णांक len);
अटल व्योम करोमुख्य_shutकरोwn_data(काष्ठा ds_info *dp,
				 काष्ठा ds_cap_state *cp,
				 व्योम *buf, पूर्णांक len);
अटल व्योम करोमुख्य_panic_data(काष्ठा ds_info *dp,
			      काष्ठा ds_cap_state *cp,
			      व्योम *buf, पूर्णांक len);
#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम dr_cpu_data(काष्ठा ds_info *dp,
			काष्ठा ds_cap_state *cp,
			व्योम *buf, पूर्णांक len);
#पूर्ण_अगर
अटल व्योम ds_pri_data(काष्ठा ds_info *dp,
			काष्ठा ds_cap_state *cp,
			व्योम *buf, पूर्णांक len);
अटल व्योम ds_var_data(काष्ठा ds_info *dp,
			काष्ठा ds_cap_state *cp,
			व्योम *buf, पूर्णांक len);

अटल काष्ठा ds_cap_state ds_states_ढाँचा[] = अणु
	अणु
		.service_id	= "md-update",
		.data		= md_update_data,
	पूर्ण,
	अणु
		.service_id	= "domain-shutdown",
		.data		= करोमुख्य_shutकरोwn_data,
	पूर्ण,
	अणु
		.service_id	= "domain-panic",
		.data		= करोमुख्य_panic_data,
	पूर्ण,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	अणु
		.service_id	= "dr-cpu",
		.data		= dr_cpu_data,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.service_id	= "pri",
		.data		= ds_pri_data,
	पूर्ण,
	अणु
		.service_id	= "var-config",
		.data		= ds_var_data,
	पूर्ण,
	अणु
		.service_id	= "var-config-backup",
		.data		= ds_var_data,
	पूर्ण,
पूर्ण;

अटल DEFINE_SPINLOCK(ds_lock);

काष्ठा ds_info अणु
	काष्ठा ldc_channel	*lp;
	u8			hs_state;
#घोषणा DS_HS_START		0x01
#घोषणा DS_HS_DONE		0x02

	u64			id;

	व्योम			*rcv_buf;
	पूर्णांक			rcv_buf_len;

	काष्ठा ds_cap_state	*ds_states;
	पूर्णांक			num_ds_states;

	काष्ठा ds_info		*next;
पूर्ण;

अटल काष्ठा ds_info *ds_info_list;

अटल काष्ठा ds_cap_state *find_cap(काष्ठा ds_info *dp, u64 handle)
अणु
	अचिन्हित पूर्णांक index = handle >> 32;

	अगर (index >= dp->num_ds_states)
		वापस शून्य;
	वापस &dp->ds_states[index];
पूर्ण

अटल काष्ठा ds_cap_state *find_cap_by_string(काष्ठा ds_info *dp,
					       स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dp->num_ds_states; i++) अणु
		अगर (म_भेद(dp->ds_states[i].service_id, name))
			जारी;

		वापस &dp->ds_states[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक __ds_send(काष्ठा ldc_channel *lp, व्योम *data, पूर्णांक len)
अणु
	पूर्णांक err, limit = 1000;

	err = -EINVAL;
	जबतक (limit-- > 0) अणु
		err = ldc_ग_लिखो(lp, data, len);
		अगर (!err || (err != -EAGAIN))
			अवरोध;
		udelay(1);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ds_send(काष्ठा ldc_channel *lp, व्योम *data, पूर्णांक len)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&ds_lock, flags);
	err = __ds_send(lp, data, len);
	spin_unlock_irqrestore(&ds_lock, flags);

	वापस err;
पूर्ण

काष्ठा ds_md_update_req अणु
	__u64				req_num;
पूर्ण;

काष्ठा ds_md_update_res अणु
	__u64				req_num;
	__u32				result;
पूर्ण;

अटल व्योम md_update_data(काष्ठा ds_info *dp,
			   काष्ठा ds_cap_state *cp,
			   व्योम *buf, पूर्णांक len)
अणु
	काष्ठा ldc_channel *lp = dp->lp;
	काष्ठा ds_data *dpkt = buf;
	काष्ठा ds_md_update_req *rp;
	काष्ठा अणु
		काष्ठा ds_data		data;
		काष्ठा ds_md_update_res	res;
	पूर्ण pkt;

	rp = (काष्ठा ds_md_update_req *) (dpkt + 1);

	prपूर्णांकk(KERN_INFO "ds-%llu: Machine description update.\n", dp->id);

	mdesc_update();

	स_रखो(&pkt, 0, माप(pkt));
	pkt.data.tag.type = DS_DATA;
	pkt.data.tag.len = माप(pkt) - माप(काष्ठा ds_msg_tag);
	pkt.data.handle = cp->handle;
	pkt.res.req_num = rp->req_num;
	pkt.res.result = DS_OK;

	ds_send(lp, &pkt, माप(pkt));
पूर्ण

काष्ठा ds_shutकरोwn_req अणु
	__u64				req_num;
	__u32				ms_delay;
पूर्ण;

काष्ठा ds_shutकरोwn_res अणु
	__u64				req_num;
	__u32				result;
	अक्षर				reason[1];
पूर्ण;

अटल व्योम करोमुख्य_shutकरोwn_data(काष्ठा ds_info *dp,
				 काष्ठा ds_cap_state *cp,
				 व्योम *buf, पूर्णांक len)
अणु
	काष्ठा ldc_channel *lp = dp->lp;
	काष्ठा ds_data *dpkt = buf;
	काष्ठा ds_shutकरोwn_req *rp;
	काष्ठा अणु
		काष्ठा ds_data		data;
		काष्ठा ds_shutकरोwn_res	res;
	पूर्ण pkt;

	rp = (काष्ठा ds_shutकरोwn_req *) (dpkt + 1);

	prपूर्णांकk(KERN_ALERT "ds-%llu: Shutdown request from "
	       "LDOM manager received.\n", dp->id);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.data.tag.type = DS_DATA;
	pkt.data.tag.len = माप(pkt) - माप(काष्ठा ds_msg_tag);
	pkt.data.handle = cp->handle;
	pkt.res.req_num = rp->req_num;
	pkt.res.result = DS_OK;
	pkt.res.reason[0] = 0;

	ds_send(lp, &pkt, माप(pkt));

	orderly_घातeroff(true);
पूर्ण

काष्ठा ds_panic_req अणु
	__u64				req_num;
पूर्ण;

काष्ठा ds_panic_res अणु
	__u64				req_num;
	__u32				result;
	अक्षर				reason[1];
पूर्ण;

अटल व्योम करोमुख्य_panic_data(काष्ठा ds_info *dp,
			      काष्ठा ds_cap_state *cp,
			      व्योम *buf, पूर्णांक len)
अणु
	काष्ठा ldc_channel *lp = dp->lp;
	काष्ठा ds_data *dpkt = buf;
	काष्ठा ds_panic_req *rp;
	काष्ठा अणु
		काष्ठा ds_data		data;
		काष्ठा ds_panic_res	res;
	पूर्ण pkt;

	rp = (काष्ठा ds_panic_req *) (dpkt + 1);

	prपूर्णांकk(KERN_ALERT "ds-%llu: Panic request from "
	       "LDOM manager received.\n", dp->id);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.data.tag.type = DS_DATA;
	pkt.data.tag.len = माप(pkt) - माप(काष्ठा ds_msg_tag);
	pkt.data.handle = cp->handle;
	pkt.res.req_num = rp->req_num;
	pkt.res.result = DS_OK;
	pkt.res.reason[0] = 0;

	ds_send(lp, &pkt, माप(pkt));

	panic("PANIC requested by LDOM manager.");
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
काष्ठा dr_cpu_tag अणु
	__u64				req_num;
	__u32				type;
#घोषणा DR_CPU_CONFIGURE		0x43
#घोषणा DR_CPU_UNCONFIGURE		0x55
#घोषणा DR_CPU_FORCE_UNCONFIGURE	0x46
#घोषणा DR_CPU_STATUS			0x53

/* Responses */
#घोषणा DR_CPU_OK			0x6f
#घोषणा DR_CPU_ERROR			0x65

	__u32				num_records;
पूर्ण;

काष्ठा dr_cpu_resp_entry अणु
	__u32				cpu;
	__u32				result;
#घोषणा DR_CPU_RES_OK			0x00
#घोषणा DR_CPU_RES_FAILURE		0x01
#घोषणा DR_CPU_RES_BLOCKED		0x02
#घोषणा DR_CPU_RES_CPU_NOT_RESPONDING	0x03
#घोषणा DR_CPU_RES_NOT_IN_MD		0x04

	__u32				stat;
#घोषणा DR_CPU_STAT_NOT_PRESENT		0x00
#घोषणा DR_CPU_STAT_UNCONFIGURED	0x01
#घोषणा DR_CPU_STAT_CONFIGURED		0x02

	__u32				str_off;
पूर्ण;

अटल व्योम __dr_cpu_send_error(काष्ठा ds_info *dp,
				काष्ठा ds_cap_state *cp,
				काष्ठा ds_data *data)
अणु
	काष्ठा dr_cpu_tag *tag = (काष्ठा dr_cpu_tag *) (data + 1);
	काष्ठा अणु
		काष्ठा ds_data		data;
		काष्ठा dr_cpu_tag	tag;
	पूर्ण pkt;
	पूर्णांक msg_len;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.data.tag.type = DS_DATA;
	pkt.data.handle = cp->handle;
	pkt.tag.req_num = tag->req_num;
	pkt.tag.type = DR_CPU_ERROR;
	pkt.tag.num_records = 0;

	msg_len = (माप(काष्ठा ds_data) +
		   माप(काष्ठा dr_cpu_tag));

	pkt.data.tag.len = msg_len - माप(काष्ठा ds_msg_tag);

	__ds_send(dp->lp, &pkt, msg_len);
पूर्ण

अटल व्योम dr_cpu_send_error(काष्ठा ds_info *dp,
			      काष्ठा ds_cap_state *cp,
			      काष्ठा ds_data *data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ds_lock, flags);
	__dr_cpu_send_error(dp, cp, data);
	spin_unlock_irqrestore(&ds_lock, flags);
पूर्ण

#घोषणा CPU_SENTINEL	0xffffffff

अटल व्योम purge_dups(u32 *list, u32 num_ents)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_ents; i++) अणु
		u32 cpu = list[i];
		अचिन्हित पूर्णांक j;

		अगर (cpu == CPU_SENTINEL)
			जारी;

		क्रम (j = i + 1; j < num_ents; j++) अणु
			अगर (list[j] == cpu)
				list[j] = CPU_SENTINEL;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dr_cpu_size_response(पूर्णांक ncpus)
अणु
	वापस (माप(काष्ठा ds_data) +
		माप(काष्ठा dr_cpu_tag) +
		(माप(काष्ठा dr_cpu_resp_entry) * ncpus));
पूर्ण

अटल व्योम dr_cpu_init_response(काष्ठा ds_data *resp, u64 req_num,
				 u64 handle, पूर्णांक resp_len, पूर्णांक ncpus,
				 cpumask_t *mask, u32 शेष_stat)
अणु
	काष्ठा dr_cpu_resp_entry *ent;
	काष्ठा dr_cpu_tag *tag;
	पूर्णांक i, cpu;

	tag = (काष्ठा dr_cpu_tag *) (resp + 1);
	ent = (काष्ठा dr_cpu_resp_entry *) (tag + 1);

	resp->tag.type = DS_DATA;
	resp->tag.len = resp_len - माप(काष्ठा ds_msg_tag);
	resp->handle = handle;
	tag->req_num = req_num;
	tag->type = DR_CPU_OK;
	tag->num_records = ncpus;

	i = 0;
	क्रम_each_cpu(cpu, mask) अणु
		ent[i].cpu = cpu;
		ent[i].result = DR_CPU_RES_OK;
		ent[i].stat = शेष_stat;
		i++;
	पूर्ण
	BUG_ON(i != ncpus);
पूर्ण

अटल व्योम dr_cpu_mark(काष्ठा ds_data *resp, पूर्णांक cpu, पूर्णांक ncpus,
			u32 res, u32 stat)
अणु
	काष्ठा dr_cpu_resp_entry *ent;
	काष्ठा dr_cpu_tag *tag;
	पूर्णांक i;

	tag = (काष्ठा dr_cpu_tag *) (resp + 1);
	ent = (काष्ठा dr_cpu_resp_entry *) (tag + 1);

	क्रम (i = 0; i < ncpus; i++) अणु
		अगर (ent[i].cpu != cpu)
			जारी;
		ent[i].result = res;
		ent[i].stat = stat;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dr_cpu_configure(काष्ठा ds_info *dp, काष्ठा ds_cap_state *cp,
			    u64 req_num, cpumask_t *mask)
अणु
	काष्ठा ds_data *resp;
	पूर्णांक resp_len, ncpus, cpu;
	अचिन्हित दीर्घ flags;

	ncpus = cpumask_weight(mask);
	resp_len = dr_cpu_size_response(ncpus);
	resp = kzalloc(resp_len, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	dr_cpu_init_response(resp, req_num, cp->handle,
			     resp_len, ncpus, mask,
			     DR_CPU_STAT_CONFIGURED);

	mdesc_populate_present_mask(mask);
	mdesc_fill_in_cpu_data(mask);

	क्रम_each_cpu(cpu, mask) अणु
		पूर्णांक err;

		prपूर्णांकk(KERN_INFO "ds-%llu: Starting cpu %d...\n",
		       dp->id, cpu);
		err = add_cpu(cpu);
		अगर (err) अणु
			__u32 res = DR_CPU_RES_FAILURE;
			__u32 stat = DR_CPU_STAT_UNCONFIGURED;

			अगर (!cpu_present(cpu)) अणु
				/* CPU not present in MD */
				res = DR_CPU_RES_NOT_IN_MD;
				stat = DR_CPU_STAT_NOT_PRESENT;
			पूर्ण अन्यथा अगर (err == -ENODEV) अणु
				/* CPU did not call in successfully */
				res = DR_CPU_RES_CPU_NOT_RESPONDING;
			पूर्ण

			prपूर्णांकk(KERN_INFO "ds-%llu: CPU startup failed err=%d\n",
			       dp->id, err);
			dr_cpu_mark(resp, cpu, ncpus, res, stat);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ds_lock, flags);
	__ds_send(dp->lp, resp, resp_len);
	spin_unlock_irqrestore(&ds_lock, flags);

	kमुक्त(resp);

	/* Redistribute IRQs, taking पूर्णांकo account the new cpus.  */
	fixup_irqs();

	वापस 0;
पूर्ण

अटल पूर्णांक dr_cpu_unconfigure(काष्ठा ds_info *dp,
			      काष्ठा ds_cap_state *cp,
			      u64 req_num,
			      cpumask_t *mask)
अणु
	काष्ठा ds_data *resp;
	पूर्णांक resp_len, ncpus, cpu;
	अचिन्हित दीर्घ flags;

	ncpus = cpumask_weight(mask);
	resp_len = dr_cpu_size_response(ncpus);
	resp = kzalloc(resp_len, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	dr_cpu_init_response(resp, req_num, cp->handle,
			     resp_len, ncpus, mask,
			     DR_CPU_STAT_UNCONFIGURED);

	क्रम_each_cpu(cpu, mask) अणु
		पूर्णांक err;

		prपूर्णांकk(KERN_INFO "ds-%llu: Shutting down cpu %d...\n",
		       dp->id, cpu);
		err = हटाओ_cpu(cpu);
		अगर (err)
			dr_cpu_mark(resp, cpu, ncpus,
				    DR_CPU_RES_FAILURE,
				    DR_CPU_STAT_CONFIGURED);
	पूर्ण

	spin_lock_irqsave(&ds_lock, flags);
	__ds_send(dp->lp, resp, resp_len);
	spin_unlock_irqrestore(&ds_lock, flags);

	kमुक्त(resp);

	वापस 0;
पूर्ण

अटल व्योम dr_cpu_data(काष्ठा ds_info *dp, काष्ठा ds_cap_state *cp, व्योम *buf,
			पूर्णांक len)
अणु
	काष्ठा ds_data *data = buf;
	काष्ठा dr_cpu_tag *tag = (काष्ठा dr_cpu_tag *) (data + 1);
	u32 *cpu_list = (u32 *) (tag + 1);
	u64 req_num = tag->req_num;
	cpumask_t mask;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	चयन (tag->type) अणु
	हाल DR_CPU_CONFIGURE:
	हाल DR_CPU_UNCONFIGURE:
	हाल DR_CPU_FORCE_UNCONFIGURE:
		अवरोध;

	शेष:
		dr_cpu_send_error(dp, cp, data);
		वापस;
	पूर्ण

	purge_dups(cpu_list, tag->num_records);

	cpumask_clear(&mask);
	क्रम (i = 0; i < tag->num_records; i++) अणु
		अगर (cpu_list[i] == CPU_SENTINEL)
			जारी;

		अगर (cpu_list[i] < nr_cpu_ids)
			cpumask_set_cpu(cpu_list[i], &mask);
	पूर्ण

	अगर (tag->type == DR_CPU_CONFIGURE)
		err = dr_cpu_configure(dp, cp, req_num, &mask);
	अन्यथा
		err = dr_cpu_unconfigure(dp, cp, req_num, &mask);

	अगर (err)
		dr_cpu_send_error(dp, cp, data);
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

काष्ठा ds_pri_msg अणु
	__u64				req_num;
	__u64				type;
#घोषणा DS_PRI_REQUEST			0x00
#घोषणा DS_PRI_DATA			0x01
#घोषणा DS_PRI_UPDATE			0x02
पूर्ण;

अटल व्योम ds_pri_data(काष्ठा ds_info *dp,
			काष्ठा ds_cap_state *cp,
			व्योम *buf, पूर्णांक len)
अणु
	काष्ठा ds_data *dpkt = buf;
	काष्ठा ds_pri_msg *rp;

	rp = (काष्ठा ds_pri_msg *) (dpkt + 1);

	prपूर्णांकk(KERN_INFO "ds-%llu: PRI REQ [%llx:%llx], len=%d\n",
	       dp->id, rp->req_num, rp->type, len);
पूर्ण

काष्ठा ds_var_hdr अणु
	__u32				type;
#घोषणा DS_VAR_SET_REQ			0x00
#घोषणा DS_VAR_DELETE_REQ		0x01
#घोषणा DS_VAR_SET_RESP			0x02
#घोषणा DS_VAR_DELETE_RESP		0x03
पूर्ण;

काष्ठा ds_var_set_msg अणु
	काष्ठा ds_var_hdr		hdr;
	अक्षर				name_and_value[];
पूर्ण;

काष्ठा ds_var_delete_msg अणु
	काष्ठा ds_var_hdr		hdr;
	अक्षर				name[];
पूर्ण;

काष्ठा ds_var_resp अणु
	काष्ठा ds_var_hdr		hdr;
	__u32				result;
#घोषणा DS_VAR_SUCCESS			0x00
#घोषणा DS_VAR_NO_SPACE			0x01
#घोषणा DS_VAR_INVALID_VAR		0x02
#घोषणा DS_VAR_INVALID_VAL		0x03
#घोषणा DS_VAR_NOT_PRESENT		0x04
पूर्ण;

अटल DEFINE_MUTEX(ds_var_mutex);
अटल पूर्णांक ds_var_करोorbell;
अटल पूर्णांक ds_var_response;

अटल व्योम ds_var_data(काष्ठा ds_info *dp,
			काष्ठा ds_cap_state *cp,
			व्योम *buf, पूर्णांक len)
अणु
	काष्ठा ds_data *dpkt = buf;
	काष्ठा ds_var_resp *rp;

	rp = (काष्ठा ds_var_resp *) (dpkt + 1);

	अगर (rp->hdr.type != DS_VAR_SET_RESP &&
	    rp->hdr.type != DS_VAR_DELETE_RESP)
		वापस;

	ds_var_response = rp->result;
	wmb();
	ds_var_करोorbell = 1;
पूर्ण

व्योम lकरोm_set_var(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	काष्ठा ds_cap_state *cp;
	काष्ठा ds_info *dp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ds_lock, flags);
	cp = शून्य;
	क्रम (dp = ds_info_list; dp; dp = dp->next) अणु
		काष्ठा ds_cap_state *पंचांगp;

		पंचांगp = find_cap_by_string(dp, "var-config");
		अगर (पंचांगp && पंचांगp->state == CAP_STATE_REGISTERED) अणु
			cp = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!cp) अणु
		क्रम (dp = ds_info_list; dp; dp = dp->next) अणु
			काष्ठा ds_cap_state *पंचांगp;

			पंचांगp = find_cap_by_string(dp, "var-config-backup");
			अगर (पंचांगp && पंचांगp->state == CAP_STATE_REGISTERED) अणु
				cp = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ds_lock, flags);

	अगर (cp) अणु
		जोड़ अणु
			काष्ठा अणु
				काष्ठा ds_data		data;
				काष्ठा ds_var_set_msg	msg;
			पूर्ण header;
			अक्षर			all[512];
		पूर्ण pkt;
		अक्षर  *base, *p;
		पूर्णांक msg_len, loops;

		अगर (म_माप(var) + म_माप(value) + 2 >
		    माप(pkt) - माप(pkt.header)) अणु
			prपूर्णांकk(KERN_ERR PFX
				"contents length: %zu, which more than max: %lu,"
				"so could not set (%s) variable to (%s).\n",
				म_माप(var) + म_माप(value) + 2,
				माप(pkt) - माप(pkt.header), var, value);
			वापस;
		पूर्ण

		स_रखो(&pkt, 0, माप(pkt));
		pkt.header.data.tag.type = DS_DATA;
		pkt.header.data.handle = cp->handle;
		pkt.header.msg.hdr.type = DS_VAR_SET_REQ;
		base = p = &pkt.header.msg.name_and_value[0];
		म_नकल(p, var);
		p += म_माप(var) + 1;
		म_नकल(p, value);
		p += म_माप(value) + 1;

		msg_len = (माप(काष्ठा ds_data) +
			   माप(काष्ठा ds_var_set_msg) +
			   (p - base));
		msg_len = (msg_len + 3) & ~3;
		pkt.header.data.tag.len = msg_len - माप(काष्ठा ds_msg_tag);

		mutex_lock(&ds_var_mutex);

		spin_lock_irqsave(&ds_lock, flags);
		ds_var_करोorbell = 0;
		ds_var_response = -1;

		__ds_send(dp->lp, &pkt, msg_len);
		spin_unlock_irqrestore(&ds_lock, flags);

		loops = 1000;
		जबतक (ds_var_करोorbell == 0) अणु
			अगर (loops-- < 0)
				अवरोध;
			barrier();
			udelay(100);
		पूर्ण

		mutex_unlock(&ds_var_mutex);

		अगर (ds_var_करोorbell == 0 ||
		    ds_var_response != DS_VAR_SUCCESS)
			prपूर्णांकk(KERN_ERR "ds-%llu: var-config [%s:%s] "
			       "failed, response(%d).\n",
			       dp->id, var, value,
			       ds_var_response);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "var-config not registered so "
		       "could not set (%s) variable to (%s).\n",
		       var, value);
	पूर्ण
पूर्ण

अटल अक्षर full_boot_str[256] __attribute__((aligned(32)));
अटल पूर्णांक reboot_data_supported;

व्योम lकरोm_reboot(स्थिर अक्षर *boot_command)
अणु
	/* Don't bother with any of this अगर the boot_command
	 * is empty.
	 */
	अगर (boot_command && म_माप(boot_command)) अणु
		अचिन्हित दीर्घ len;

		snम_लिखो(full_boot_str, माप(full_boot_str), "boot %s",
			 boot_command);
		len = म_माप(full_boot_str);

		अगर (reboot_data_supported) अणु
			अचिन्हित दीर्घ ra = kimage_addr_to_ra(full_boot_str);
			अचिन्हित दीर्घ hv_ret;

			hv_ret = sun4v_reboot_data_set(ra, len);
			अगर (hv_ret != HV_EOK)
				pr_err("SUN4V: Unable to set reboot data "
				       "hv_ret=%lu\n", hv_ret);
		पूर्ण अन्यथा अणु
			lकरोm_set_var("reboot-command", full_boot_str);
		पूर्ण
	पूर्ण
	sun4v_mach_sir();
पूर्ण

व्योम lकरोm_घातer_off(व्योम)
अणु
	sun4v_mach_निकास(0);
पूर्ण

अटल व्योम ds_conn_reset(काष्ठा ds_info *dp)
अणु
	prपूर्णांकk(KERN_ERR "ds-%llu: ds_conn_reset() from %ps\n",
	       dp->id, __builtin_वापस_address(0));
पूर्ण

अटल पूर्णांक रेजिस्टर_services(काष्ठा ds_info *dp)
अणु
	काष्ठा ldc_channel *lp = dp->lp;
	पूर्णांक i;

	क्रम (i = 0; i < dp->num_ds_states; i++) अणु
		काष्ठा अणु
			काष्ठा ds_reg_req req;
			u8 id_buf[256];
		पूर्ण pbuf;
		काष्ठा ds_cap_state *cp = &dp->ds_states[i];
		पूर्णांक err, msg_len;
		u64 new_count;

		अगर (cp->state == CAP_STATE_REGISTERED)
			जारी;

		new_count = sched_घड़ी() & 0xffffffff;
		cp->handle = ((u64) i << 32) | new_count;

		msg_len = (माप(काष्ठा ds_reg_req) +
			   म_माप(cp->service_id));

		स_रखो(&pbuf, 0, माप(pbuf));
		pbuf.req.tag.type = DS_REG_REQ;
		pbuf.req.tag.len = (msg_len - माप(काष्ठा ds_msg_tag));
		pbuf.req.handle = cp->handle;
		pbuf.req.major = 1;
		pbuf.req.minor = 0;
		म_नकल(pbuf.id_buf, cp->service_id);

		err = __ds_send(lp, &pbuf, msg_len);
		अगर (err > 0)
			cp->state = CAP_STATE_REG_SENT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ds_handshake(काष्ठा ds_info *dp, काष्ठा ds_msg_tag *pkt)
अणु

	अगर (dp->hs_state == DS_HS_START) अणु
		अगर (pkt->type != DS_INIT_ACK)
			जाओ conn_reset;

		dp->hs_state = DS_HS_DONE;

		वापस रेजिस्टर_services(dp);
	पूर्ण

	अगर (dp->hs_state != DS_HS_DONE)
		जाओ conn_reset;

	अगर (pkt->type == DS_REG_ACK) अणु
		काष्ठा ds_reg_ack *ap = (काष्ठा ds_reg_ack *) pkt;
		काष्ठा ds_cap_state *cp = find_cap(dp, ap->handle);

		अगर (!cp) अणु
			prपूर्णांकk(KERN_ERR "ds-%llu: REG ACK for unknown "
			       "handle %llx\n", dp->id, ap->handle);
			वापस 0;
		पूर्ण
		prपूर्णांकk(KERN_INFO "ds-%llu: Registered %s service.\n",
		       dp->id, cp->service_id);
		cp->state = CAP_STATE_REGISTERED;
	पूर्ण अन्यथा अगर (pkt->type == DS_REG_NACK) अणु
		काष्ठा ds_reg_nack *np = (काष्ठा ds_reg_nack *) pkt;
		काष्ठा ds_cap_state *cp = find_cap(dp, np->handle);

		अगर (!cp) अणु
			prपूर्णांकk(KERN_ERR "ds-%llu: REG NACK for "
			       "unknown handle %llx\n",
			       dp->id, np->handle);
			वापस 0;
		पूर्ण
		cp->state = CAP_STATE_UNKNOWN;
	पूर्ण

	वापस 0;

conn_reset:
	ds_conn_reset(dp);
	वापस -ECONNRESET;
पूर्ण

अटल व्योम __send_ds_nack(काष्ठा ds_info *dp, u64 handle)
अणु
	काष्ठा ds_data_nack nack = अणु
		.tag = अणु
			.type = DS_NACK,
			.len = (माप(काष्ठा ds_data_nack) -
				माप(काष्ठा ds_msg_tag)),
		पूर्ण,
		.handle = handle,
		.result = DS_INV_HDL,
	पूर्ण;

	__ds_send(dp->lp, &nack, माप(nack));
पूर्ण

अटल LIST_HEAD(ds_work_list);
अटल DECLARE_WAIT_QUEUE_HEAD(ds_रुको);

काष्ठा ds_queue_entry अणु
	काष्ठा list_head		list;
	काष्ठा ds_info			*dp;
	पूर्णांक				req_len;
	पूर्णांक				__pad;
	u64				req[];
पूर्ण;

अटल व्योम process_ds_work(व्योम)
अणु
	काष्ठा ds_queue_entry *qp, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(toकरो);

	spin_lock_irqsave(&ds_lock, flags);
	list_splice_init(&ds_work_list, &toकरो);
	spin_unlock_irqrestore(&ds_lock, flags);

	list_क्रम_each_entry_safe(qp, पंचांगp, &toकरो, list) अणु
		काष्ठा ds_data *dpkt = (काष्ठा ds_data *) qp->req;
		काष्ठा ds_info *dp = qp->dp;
		काष्ठा ds_cap_state *cp = find_cap(dp, dpkt->handle);
		पूर्णांक req_len = qp->req_len;

		अगर (!cp) अणु
			prपूर्णांकk(KERN_ERR "ds-%llu: Data for unknown "
			       "handle %llu\n",
			       dp->id, dpkt->handle);

			spin_lock_irqsave(&ds_lock, flags);
			__send_ds_nack(dp, dpkt->handle);
			spin_unlock_irqrestore(&ds_lock, flags);
		पूर्ण अन्यथा अणु
			cp->data(dp, cp, dpkt, req_len);
		पूर्ण

		list_del(&qp->list);
		kमुक्त(qp);
	पूर्ण
पूर्ण

अटल पूर्णांक ds_thपढ़ो(व्योम *__unused)
अणु
	DEFINE_WAIT(रुको);

	जबतक (1) अणु
		prepare_to_रुको(&ds_रुको, &रुको, TASK_INTERRUPTIBLE);
		अगर (list_empty(&ds_work_list))
			schedule();
		finish_रुको(&ds_रुको, &रुको);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		process_ds_work();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds_data(काष्ठा ds_info *dp, काष्ठा ds_msg_tag *pkt, पूर्णांक len)
अणु
	काष्ठा ds_data *dpkt = (काष्ठा ds_data *) pkt;
	काष्ठा ds_queue_entry *qp;

	qp = kदो_स्मृति(माप(काष्ठा ds_queue_entry) + len, GFP_ATOMIC);
	अगर (!qp) अणु
		__send_ds_nack(dp, dpkt->handle);
	पूर्ण अन्यथा अणु
		qp->dp = dp;
		स_नकल(&qp->req, pkt, len);
		list_add_tail(&qp->list, &ds_work_list);
		wake_up(&ds_रुको);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ds_up(काष्ठा ds_info *dp)
अणु
	काष्ठा ldc_channel *lp = dp->lp;
	काष्ठा ds_ver_req req;
	पूर्णांक err;

	req.tag.type = DS_INIT_REQ;
	req.tag.len = माप(req) - माप(काष्ठा ds_msg_tag);
	req.ver.major = 1;
	req.ver.minor = 0;

	err = __ds_send(lp, &req, माप(req));
	अगर (err > 0)
		dp->hs_state = DS_HS_START;
पूर्ण

अटल व्योम ds_reset(काष्ठा ds_info *dp)
अणु
	पूर्णांक i;

	dp->hs_state = 0;

	क्रम (i = 0; i < dp->num_ds_states; i++) अणु
		काष्ठा ds_cap_state *cp = &dp->ds_states[i];

		cp->state = CAP_STATE_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम ds_event(व्योम *arg, पूर्णांक event)
अणु
	काष्ठा ds_info *dp = arg;
	काष्ठा ldc_channel *lp = dp->lp;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&ds_lock, flags);

	अगर (event == LDC_EVENT_UP) अणु
		ds_up(dp);
		spin_unlock_irqrestore(&ds_lock, flags);
		वापस;
	पूर्ण

	अगर (event == LDC_EVENT_RESET) अणु
		ds_reset(dp);
		spin_unlock_irqrestore(&ds_lock, flags);
		वापस;
	पूर्ण

	अगर (event != LDC_EVENT_DATA_READY) अणु
		prपूर्णांकk(KERN_WARNING "ds-%llu: Unexpected LDC event %d\n",
		       dp->id, event);
		spin_unlock_irqrestore(&ds_lock, flags);
		वापस;
	पूर्ण

	err = 0;
	जबतक (1) अणु
		काष्ठा ds_msg_tag *tag;

		err = ldc_पढ़ो(lp, dp->rcv_buf, माप(*tag));

		अगर (unlikely(err < 0)) अणु
			अगर (err == -ECONNRESET)
				ds_conn_reset(dp);
			अवरोध;
		पूर्ण
		अगर (err == 0)
			अवरोध;

		tag = dp->rcv_buf;
		err = ldc_पढ़ो(lp, tag + 1, tag->len);

		अगर (unlikely(err < 0)) अणु
			अगर (err == -ECONNRESET)
				ds_conn_reset(dp);
			अवरोध;
		पूर्ण
		अगर (err < tag->len)
			अवरोध;

		अगर (tag->type < DS_DATA)
			err = ds_handshake(dp, dp->rcv_buf);
		अन्यथा
			err = ds_data(dp, dp->rcv_buf,
				      माप(*tag) + err);
		अगर (err == -ECONNRESET)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ds_lock, flags);
पूर्ण

अटल पूर्णांक ds_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	अटल पूर्णांक ds_version_prपूर्णांकed;
	काष्ठा ldc_channel_config ds_cfg = अणु
		.event		= ds_event,
		.mtu		= 4096,
		.mode		= LDC_MODE_STREAM,
	पूर्ण;
	काष्ठा mdesc_handle *hp;
	काष्ठा ldc_channel *lp;
	काष्ठा ds_info *dp;
	स्थिर u64 *val;
	पूर्णांक err, i;

	अगर (ds_version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);

	dp = kzalloc(माप(*dp), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!dp)
		जाओ out_err;

	hp = mdesc_grab();
	val = mdesc_get_property(hp, vdev->mp, "id", शून्य);
	अगर (val)
		dp->id = *val;
	mdesc_release(hp);

	dp->rcv_buf = kzalloc(4096, GFP_KERNEL);
	अगर (!dp->rcv_buf)
		जाओ out_मुक्त_dp;

	dp->rcv_buf_len = 4096;

	dp->ds_states = kmemdup(ds_states_ढाँचा,
				माप(ds_states_ढाँचा), GFP_KERNEL);
	अगर (!dp->ds_states)
		जाओ out_मुक्त_rcv_buf;

	dp->num_ds_states = ARRAY_SIZE(ds_states_ढाँचा);

	क्रम (i = 0; i < dp->num_ds_states; i++)
		dp->ds_states[i].handle = ((u64)i << 32);

	ds_cfg.tx_irq = vdev->tx_irq;
	ds_cfg.rx_irq = vdev->rx_irq;

	lp = ldc_alloc(vdev->channel_id, &ds_cfg, dp, "DS");
	अगर (IS_ERR(lp)) अणु
		err = PTR_ERR(lp);
		जाओ out_मुक्त_ds_states;
	पूर्ण
	dp->lp = lp;

	err = ldc_bind(lp);
	अगर (err)
		जाओ out_मुक्त_ldc;

	spin_lock_irq(&ds_lock);
	dp->next = ds_info_list;
	ds_info_list = dp;
	spin_unlock_irq(&ds_lock);

	वापस err;

out_मुक्त_ldc:
	ldc_मुक्त(dp->lp);

out_मुक्त_ds_states:
	kमुक्त(dp->ds_states);

out_मुक्त_rcv_buf:
	kमुक्त(dp->rcv_buf);

out_मुक्त_dp:
	kमुक्त(dp);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक ds_हटाओ(काष्ठा vio_dev *vdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vio_device_id ds_match[] = अणु
	अणु
		.type = "domain-services-port",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा vio_driver ds_driver = अणु
	.id_table	= ds_match,
	.probe		= ds_probe,
	.हटाओ		= ds_हटाओ,
	.name		= "ds",
पूर्ण;

अटल पूर्णांक __init ds_init(व्योम)
अणु
	अचिन्हित दीर्घ hv_ret, major, minor;

	अगर (tlb_type == hypervisor) अणु
		hv_ret = sun4v_get_version(HV_GRP_REBOOT_DATA, &major, &minor);
		अगर (hv_ret == HV_EOK) अणु
			pr_info("SUN4V: Reboot data supported (maj=%lu,min=%lu).\n",
				major, minor);
			reboot_data_supported = 1;
		पूर्ण
	पूर्ण
	kthपढ़ो_run(ds_thपढ़ो, शून्य, "kldomd");

	वापस vio_रेजिस्टर_driver(&ds_driver);
पूर्ण

fs_initcall(ds_init);
