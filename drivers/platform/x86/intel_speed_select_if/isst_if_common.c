<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Speed Select Interface: Common functions
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#समावेश <linux/cpufeature.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/fs.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/isst_अगर.h>

#समावेश "isst_if_common.h"

#घोषणा MSR_THREAD_ID_INFO	0x53
#घोषणा MSR_CPU_BUS_NUMBER	0x128

अटल काष्ठा isst_अगर_cmd_cb punit_callbacks[ISST_IF_DEV_MAX];

अटल पूर्णांक punit_msr_white_list[] = अणु
	MSR_TURBO_RATIO_LIMIT,
	MSR_CONFIG_TDP_CONTROL,
	MSR_TURBO_RATIO_LIMIT1,
	MSR_TURBO_RATIO_LIMIT2,
पूर्ण;

काष्ठा isst_valid_cmd_ranges अणु
	u16 cmd;
	u16 sub_cmd_beg;
	u16 sub_cmd_end;
पूर्ण;

काष्ठा isst_cmd_set_req_type अणु
	u16 cmd;
	u16 sub_cmd;
	u16 param;
पूर्ण;

अटल स्थिर काष्ठा isst_valid_cmd_ranges isst_valid_cmds[] = अणु
	अणु0xD0, 0x00, 0x03पूर्ण,
	अणु0x7F, 0x00, 0x0Bपूर्ण,
	अणु0x7F, 0x10, 0x12पूर्ण,
	अणु0x7F, 0x20, 0x23पूर्ण,
	अणु0x94, 0x03, 0x03पूर्ण,
	अणु0x95, 0x03, 0x03पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा isst_cmd_set_req_type isst_cmd_set_reqs[] = अणु
	अणु0xD0, 0x00, 0x08पूर्ण,
	अणु0xD0, 0x01, 0x08पूर्ण,
	अणु0xD0, 0x02, 0x08पूर्ण,
	अणु0xD0, 0x03, 0x08पूर्ण,
	अणु0x7F, 0x02, 0x00पूर्ण,
	अणु0x7F, 0x08, 0x00पूर्ण,
	अणु0x95, 0x03, 0x03पूर्ण,
पूर्ण;

काष्ठा isst_cmd अणु
	काष्ठा hlist_node hnode;
	u64 data;
	u32 cmd;
	पूर्णांक cpu;
	पूर्णांक mbox_cmd_type;
	u32 param;
पूर्ण;

अटल DECLARE_HASHTABLE(isst_hash, 8);
अटल DEFINE_MUTEX(isst_hash_lock);

अटल पूर्णांक isst_store_new_cmd(पूर्णांक cmd, u32 cpu, पूर्णांक mbox_cmd_type, u32 param,
			      u32 data)
अणु
	काष्ठा isst_cmd *sst_cmd;

	sst_cmd = kदो_स्मृति(माप(*sst_cmd), GFP_KERNEL);
	अगर (!sst_cmd)
		वापस -ENOMEM;

	sst_cmd->cpu = cpu;
	sst_cmd->cmd = cmd;
	sst_cmd->mbox_cmd_type = mbox_cmd_type;
	sst_cmd->param = param;
	sst_cmd->data = data;

	hash_add(isst_hash, &sst_cmd->hnode, sst_cmd->cmd);

	वापस 0;
पूर्ण

अटल व्योम isst_delete_hash(व्योम)
अणु
	काष्ठा isst_cmd *sst_cmd;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_safe(isst_hash, i, पंचांगp, sst_cmd, hnode) अणु
		hash_del(&sst_cmd->hnode);
		kमुक्त(sst_cmd);
	पूर्ण
पूर्ण

/**
 * isst_store_cmd() - Store command to a hash table
 * @cmd: Mailbox command.
 * @sub_cmd: Mailbox sub-command or MSR id.
 * @mbox_cmd_type: Mailbox or MSR command.
 * @param: Mailbox parameter.
 * @data: Mailbox request data or MSR data.
 *
 * Stores the command to a hash table अगर there is no such command alपढ़ोy
 * stored. If alपढ़ोy stored update the latest parameter and data क्रम the
 * command.
 *
 * Return: Return result of store to hash table, 0 क्रम success, others क्रम
 * failure.
 */
पूर्णांक isst_store_cmd(पूर्णांक cmd, पूर्णांक sub_cmd, u32 cpu, पूर्णांक mbox_cmd_type,
		   u32 param, u64 data)
अणु
	काष्ठा isst_cmd *sst_cmd;
	पूर्णांक full_cmd, ret;

	full_cmd = (cmd & GENMASK_ULL(15, 0)) << 16;
	full_cmd |= (sub_cmd & GENMASK_ULL(15, 0));
	mutex_lock(&isst_hash_lock);
	hash_क्रम_each_possible(isst_hash, sst_cmd, hnode, full_cmd) अणु
		अगर (sst_cmd->cmd == full_cmd && sst_cmd->cpu == cpu &&
		    sst_cmd->mbox_cmd_type == mbox_cmd_type) अणु
			sst_cmd->param = param;
			sst_cmd->data = data;
			mutex_unlock(&isst_hash_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	ret = isst_store_new_cmd(full_cmd, cpu, mbox_cmd_type, param, data);
	mutex_unlock(&isst_hash_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(isst_store_cmd);

अटल व्योम isst_mbox_resume_command(काष्ठा isst_अगर_cmd_cb *cb,
				     काष्ठा isst_cmd *sst_cmd)
अणु
	काष्ठा isst_अगर_mbox_cmd mbox_cmd;
	पूर्णांक wr_only;

	mbox_cmd.command = (sst_cmd->cmd & GENMASK_ULL(31, 16)) >> 16;
	mbox_cmd.sub_command = sst_cmd->cmd & GENMASK_ULL(15, 0);
	mbox_cmd.parameter = sst_cmd->param;
	mbox_cmd.req_data = sst_cmd->data;
	mbox_cmd.logical_cpu = sst_cmd->cpu;
	(cb->cmd_callback)((u8 *)&mbox_cmd, &wr_only, 1);
पूर्ण

/**
 * isst_resume_common() - Process Resume request
 *
 * On resume replay all mailbox commands and MSRs.
 *
 * Return: None.
 */
व्योम isst_resume_common(व्योम)
अणु
	काष्ठा isst_cmd *sst_cmd;
	पूर्णांक i;

	hash_क्रम_each(isst_hash, i, sst_cmd, hnode) अणु
		काष्ठा isst_अगर_cmd_cb *cb;

		अगर (sst_cmd->mbox_cmd_type) अणु
			cb = &punit_callbacks[ISST_IF_DEV_MBOX];
			अगर (cb->रेजिस्टरed)
				isst_mbox_resume_command(cb, sst_cmd);
		पूर्ण अन्यथा अणु
			wrmsrl_safe_on_cpu(sst_cmd->cpu, sst_cmd->cmd,
					   sst_cmd->data);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(isst_resume_common);

अटल व्योम isst_restore_msr_local(पूर्णांक cpu)
अणु
	काष्ठा isst_cmd *sst_cmd;
	पूर्णांक i;

	mutex_lock(&isst_hash_lock);
	क्रम (i = 0; i < ARRAY_SIZE(punit_msr_white_list); ++i) अणु
		अगर (!punit_msr_white_list[i])
			अवरोध;

		hash_क्रम_each_possible(isst_hash, sst_cmd, hnode,
				       punit_msr_white_list[i]) अणु
			अगर (!sst_cmd->mbox_cmd_type && sst_cmd->cpu == cpu)
				wrmsrl_safe(sst_cmd->cmd, sst_cmd->data);
		पूर्ण
	पूर्ण
	mutex_unlock(&isst_hash_lock);
पूर्ण

/**
 * isst_अगर_mbox_cmd_invalid() - Check invalid mailbox commands
 * @cmd: Poपूर्णांकer to the command काष्ठाure to verअगरy.
 *
 * Invalid command to PUNIT to may result in instability of the platक्रमm.
 * This function has a whitelist of commands, which are allowed.
 *
 * Return: Return true अगर the command is invalid, अन्यथा false.
 */
bool isst_अगर_mbox_cmd_invalid(काष्ठा isst_अगर_mbox_cmd *cmd)
अणु
	पूर्णांक i;

	अगर (cmd->logical_cpu >= nr_cpu_ids)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(isst_valid_cmds); ++i) अणु
		अगर (cmd->command == isst_valid_cmds[i].cmd &&
		    (cmd->sub_command >= isst_valid_cmds[i].sub_cmd_beg &&
		     cmd->sub_command <= isst_valid_cmds[i].sub_cmd_end)) अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(isst_अगर_mbox_cmd_invalid);

/**
 * isst_अगर_mbox_cmd_set_req() - Check mailbox command is a set request
 * @cmd: Poपूर्णांकer to the command काष्ठाure to verअगरy.
 *
 * Check अगर the given mail box level is set request and not a get request.
 *
 * Return: Return true अगर the command is set_req, अन्यथा false.
 */
bool isst_अगर_mbox_cmd_set_req(काष्ठा isst_अगर_mbox_cmd *cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(isst_cmd_set_reqs); ++i) अणु
		अगर (cmd->command == isst_cmd_set_reqs[i].cmd &&
		    cmd->sub_command == isst_cmd_set_reqs[i].sub_cmd &&
		    cmd->parameter == isst_cmd_set_reqs[i].param) अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(isst_अगर_mbox_cmd_set_req);

अटल पूर्णांक isst_अगर_get_platक्रमm_info(व्योम __user *argp)
अणु
	काष्ठा isst_अगर_platक्रमm_info info;

	info.api_version = ISST_IF_API_VERSION,
	info.driver_version = ISST_IF_DRIVER_VERSION,
	info.max_cmds_per_ioctl = ISST_IF_CMD_LIMIT,
	info.mbox_supported = punit_callbacks[ISST_IF_DEV_MBOX].रेजिस्टरed;
	info.mmio_supported = punit_callbacks[ISST_IF_DEV_MMIO].रेजिस्टरed;

	अगर (copy_to_user(argp, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण


काष्ठा isst_अगर_cpu_info अणु
	/* For BUS 0 and BUS 1 only, which we need क्रम PUNIT पूर्णांकerface */
	पूर्णांक bus_info[2];
	पूर्णांक punit_cpu_id;
पूर्ण;

अटल काष्ठा isst_अगर_cpu_info *isst_cpu_info;

/**
 * isst_अगर_get_pci_dev() - Get the PCI device instance क्रम a CPU
 * @cpu: Logical CPU number.
 * @bus_number: The bus number asचिन्हित by the hardware.
 * @dev: The device number asचिन्हित by the hardware.
 * @fn: The function number asचिन्हित by the hardware.
 *
 * Using cached bus inक्रमmation, find out the PCI device क्रम a bus number,
 * device and function.
 *
 * Return: Return pci_dev poपूर्णांकer or शून्य.
 */
काष्ठा pci_dev *isst_अगर_get_pci_dev(पूर्णांक cpu, पूर्णांक bus_no, पूर्णांक dev, पूर्णांक fn)
अणु
	पूर्णांक bus_number;

	अगर (bus_no < 0 || bus_no > 1 || cpu < 0 || cpu >= nr_cpu_ids ||
	    cpu >= num_possible_cpus())
		वापस शून्य;

	bus_number = isst_cpu_info[cpu].bus_info[bus_no];
	अगर (bus_number < 0)
		वापस शून्य;

	वापस pci_get_करोमुख्य_bus_and_slot(0, bus_number, PCI_DEVFN(dev, fn));
पूर्ण
EXPORT_SYMBOL_GPL(isst_अगर_get_pci_dev);

अटल पूर्णांक isst_अगर_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	u64 data;
	पूर्णांक ret;

	ret = rdmsrl_safe(MSR_CPU_BUS_NUMBER, &data);
	अगर (ret) अणु
		/* This is not a fatal error on MSR mailbox only I/F */
		isst_cpu_info[cpu].bus_info[0] = -1;
		isst_cpu_info[cpu].bus_info[1] = -1;
	पूर्ण अन्यथा अणु
		isst_cpu_info[cpu].bus_info[0] = data & 0xff;
		isst_cpu_info[cpu].bus_info[1] = (data >> 8) & 0xff;
	पूर्ण

	ret = rdmsrl_safe(MSR_THREAD_ID_INFO, &data);
	अगर (ret) अणु
		isst_cpu_info[cpu].punit_cpu_id = -1;
		वापस ret;
	पूर्ण
	isst_cpu_info[cpu].punit_cpu_id = data;

	isst_restore_msr_local(cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक isst_अगर_online_id;

अटल पूर्णांक isst_अगर_cpu_info_init(व्योम)
अणु
	पूर्णांक ret;

	isst_cpu_info = kसुस्मृति(num_possible_cpus(),
				माप(*isst_cpu_info),
				GFP_KERNEL);
	अगर (!isst_cpu_info)
		वापस -ENOMEM;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
				"platform/x86/isst-if:online",
				isst_अगर_cpu_online, शून्य);
	अगर (ret < 0) अणु
		kमुक्त(isst_cpu_info);
		वापस ret;
	पूर्ण

	isst_अगर_online_id = ret;

	वापस 0;
पूर्ण

अटल व्योम isst_अगर_cpu_info_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(isst_अगर_online_id);
	kमुक्त(isst_cpu_info);
पूर्ण;

अटल दीर्घ isst_अगर_proc_phyid_req(u8 *cmd_ptr, पूर्णांक *ग_लिखो_only, पूर्णांक resume)
अणु
	काष्ठा isst_अगर_cpu_map *cpu_map;

	cpu_map = (काष्ठा isst_अगर_cpu_map *)cmd_ptr;
	अगर (cpu_map->logical_cpu >= nr_cpu_ids ||
	    cpu_map->logical_cpu >= num_possible_cpus())
		वापस -EINVAL;

	*ग_लिखो_only = 0;
	cpu_map->physical_cpu = isst_cpu_info[cpu_map->logical_cpu].punit_cpu_id;

	वापस 0;
पूर्ण

अटल bool match_punit_msr_white_list(पूर्णांक msr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(punit_msr_white_list); ++i) अणु
		अगर (punit_msr_white_list[i] == msr)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल दीर्घ isst_अगर_msr_cmd_req(u8 *cmd_ptr, पूर्णांक *ग_लिखो_only, पूर्णांक resume)
अणु
	काष्ठा isst_अगर_msr_cmd *msr_cmd;
	पूर्णांक ret;

	msr_cmd = (काष्ठा isst_अगर_msr_cmd *)cmd_ptr;

	अगर (!match_punit_msr_white_list(msr_cmd->msr))
		वापस -EINVAL;

	अगर (msr_cmd->logical_cpu >= nr_cpu_ids)
		वापस -EINVAL;

	अगर (msr_cmd->पढ़ो_ग_लिखो) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		ret = wrmsrl_safe_on_cpu(msr_cmd->logical_cpu,
					 msr_cmd->msr,
					 msr_cmd->data);
		*ग_लिखो_only = 1;
		अगर (!ret && !resume)
			ret = isst_store_cmd(0, msr_cmd->msr,
					     msr_cmd->logical_cpu,
					     0, 0, msr_cmd->data);
	पूर्ण अन्यथा अणु
		u64 data;

		ret = rdmsrl_safe_on_cpu(msr_cmd->logical_cpu,
					 msr_cmd->msr, &data);
		अगर (!ret) अणु
			msr_cmd->data = data;
			*ग_लिखो_only = 0;
		पूर्ण
	पूर्ण


	वापस ret;
पूर्ण

अटल दीर्घ isst_अगर_exec_multi_cmd(व्योम __user *argp, काष्ठा isst_अगर_cmd_cb *cb)
अणु
	अचिन्हित अक्षर __user *ptr;
	u32 cmd_count;
	u8 *cmd_ptr;
	दीर्घ ret;
	पूर्णांक i;

	/* Each multi command has u32 command count as the first field */
	अगर (copy_from_user(&cmd_count, argp, माप(cmd_count)))
		वापस -EFAULT;

	अगर (!cmd_count || cmd_count > ISST_IF_CMD_LIMIT)
		वापस -EINVAL;

	cmd_ptr = kदो_स्मृति(cb->cmd_size, GFP_KERNEL);
	अगर (!cmd_ptr)
		वापस -ENOMEM;

	/* cb->offset poपूर्णांकs to start of the command after the command count */
	ptr = argp + cb->offset;

	क्रम (i = 0; i < cmd_count; ++i) अणु
		पूर्णांक wr_only;

		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		अगर (copy_from_user(cmd_ptr, ptr, cb->cmd_size)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = cb->cmd_callback(cmd_ptr, &wr_only, 0);
		अगर (ret)
			अवरोध;

		अगर (!wr_only && copy_to_user(ptr, cmd_ptr, cb->cmd_size)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ptr += cb->cmd_size;
	पूर्ण

	kमुक्त(cmd_ptr);

	वापस i ? i : ret;
पूर्ण

अटल दीर्घ isst_अगर_def_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा isst_अगर_cmd_cb cmd_cb;
	काष्ठा isst_अगर_cmd_cb *cb;
	दीर्घ ret = -ENOTTY;

	चयन (cmd) अणु
	हाल ISST_IF_GET_PLATFORM_INFO:
		ret = isst_अगर_get_platक्रमm_info(argp);
		अवरोध;
	हाल ISST_IF_GET_PHY_ID:
		cmd_cb.cmd_size = माप(काष्ठा isst_अगर_cpu_map);
		cmd_cb.offset = दुरत्व(काष्ठा isst_अगर_cpu_maps, cpu_map);
		cmd_cb.cmd_callback = isst_अगर_proc_phyid_req;
		ret = isst_अगर_exec_multi_cmd(argp, &cmd_cb);
		अवरोध;
	हाल ISST_IF_IO_CMD:
		cb = &punit_callbacks[ISST_IF_DEV_MMIO];
		अगर (cb->रेजिस्टरed)
			ret = isst_अगर_exec_multi_cmd(argp, cb);
		अवरोध;
	हाल ISST_IF_MBOX_COMMAND:
		cb = &punit_callbacks[ISST_IF_DEV_MBOX];
		अगर (cb->रेजिस्टरed)
			ret = isst_अगर_exec_multi_cmd(argp, cb);
		अवरोध;
	हाल ISST_IF_MSR_COMMAND:
		cmd_cb.cmd_size = माप(काष्ठा isst_अगर_msr_cmd);
		cmd_cb.offset = दुरत्व(काष्ठा isst_अगर_msr_cmds, msr_cmd);
		cmd_cb.cmd_callback = isst_अगर_msr_cmd_req;
		ret = isst_अगर_exec_multi_cmd(argp, &cmd_cb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल DEFINE_MUTEX(punit_misc_dev_lock);
अटल पूर्णांक misc_usage_count;
अटल पूर्णांक misc_device_ret;
अटल पूर्णांक misc_device_खोलो;

अटल पूर्णांक isst_अगर_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक i, ret = 0;

	/* Fail खोलो, अगर a module is going away */
	mutex_lock(&punit_misc_dev_lock);
	क्रम (i = 0; i < ISST_IF_DEV_MAX; ++i) अणु
		काष्ठा isst_अगर_cmd_cb *cb = &punit_callbacks[i];

		अगर (cb->रेजिस्टरed && !try_module_get(cb->owner)) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		पूर्णांक j;

		क्रम (j = 0; j < i; ++j) अणु
			काष्ठा isst_अगर_cmd_cb *cb;

			cb = &punit_callbacks[j];
			अगर (cb->रेजिस्टरed)
				module_put(cb->owner);
		पूर्ण
	पूर्ण अन्यथा अणु
		misc_device_खोलो++;
	पूर्ण
	mutex_unlock(&punit_misc_dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक isst_अगर_relase(काष्ठा inode *inode, काष्ठा file *f)
अणु
	पूर्णांक i;

	mutex_lock(&punit_misc_dev_lock);
	misc_device_खोलो--;
	क्रम (i = 0; i < ISST_IF_DEV_MAX; ++i) अणु
		काष्ठा isst_अगर_cmd_cb *cb = &punit_callbacks[i];

		अगर (cb->रेजिस्टरed)
			module_put(cb->owner);
	पूर्ण
	mutex_unlock(&punit_misc_dev_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations isst_अगर_अक्षर_driver_ops = अणु
	.खोलो = isst_अगर_खोलो,
	.unlocked_ioctl = isst_अगर_def_ioctl,
	.release = isst_अगर_relase,
पूर्ण;

अटल काष्ठा miscdevice isst_अगर_अक्षर_driver = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "isst_interface",
	.fops		= &isst_अगर_अक्षर_driver_ops,
पूर्ण;

/**
 * isst_अगर_cdev_रेजिस्टर() - Register callback क्रम IOCTL
 * @device_type: The device type this callback handling.
 * @cb:	Callback काष्ठाure.
 *
 * This function रेजिस्टरs a callback to device type. On very first call
 * it will रेजिस्टर a misc device, which is used क्रम user kernel पूर्णांकerface.
 * Other calls simply increment ref count. Registry will fail, अगर the user
 * alपढ़ोy खोलोed misc device क्रम operation. Also अगर the misc device
 * creation failed, then it will not try again and all callers will get
 * failure code.
 *
 * Return: Return the वापस value from the misc creation device or -EINVAL
 * क्रम unsupported device type.
 */
पूर्णांक isst_अगर_cdev_रेजिस्टर(पूर्णांक device_type, काष्ठा isst_अगर_cmd_cb *cb)
अणु
	अगर (misc_device_ret)
		वापस misc_device_ret;

	अगर (device_type >= ISST_IF_DEV_MAX)
		वापस -EINVAL;

	mutex_lock(&punit_misc_dev_lock);
	अगर (misc_device_खोलो) अणु
		mutex_unlock(&punit_misc_dev_lock);
		वापस -EAGAIN;
	पूर्ण
	अगर (!misc_usage_count) अणु
		पूर्णांक ret;

		misc_device_ret = misc_रेजिस्टर(&isst_अगर_अक्षर_driver);
		अगर (misc_device_ret)
			जाओ unlock_निकास;

		ret = isst_अगर_cpu_info_init();
		अगर (ret) अणु
			misc_deरेजिस्टर(&isst_अगर_अक्षर_driver);
			misc_device_ret = ret;
			जाओ unlock_निकास;
		पूर्ण
	पूर्ण
	स_नकल(&punit_callbacks[device_type], cb, माप(*cb));
	punit_callbacks[device_type].रेजिस्टरed = 1;
	misc_usage_count++;
unlock_निकास:
	mutex_unlock(&punit_misc_dev_lock);

	वापस misc_device_ret;
पूर्ण
EXPORT_SYMBOL_GPL(isst_अगर_cdev_रेजिस्टर);

/**
 * isst_अगर_cdev_unरेजिस्टर() - Unरेजिस्टर callback क्रम IOCTL
 * @device_type: The device type to unरेजिस्टर.
 *
 * This function unरेजिस्टरs the previously रेजिस्टरed callback. If this
 * is the last callback unरेजिस्टरing, then misc device is हटाओd.
 *
 * Return: None.
 */
व्योम isst_अगर_cdev_unरेजिस्टर(पूर्णांक device_type)
अणु
	mutex_lock(&punit_misc_dev_lock);
	misc_usage_count--;
	punit_callbacks[device_type].रेजिस्टरed = 0;
	अगर (device_type == ISST_IF_DEV_MBOX)
		isst_delete_hash();
	अगर (!misc_usage_count && !misc_device_ret) अणु
		misc_deरेजिस्टर(&isst_अगर_अक्षर_driver);
		isst_अगर_cpu_info_निकास();
	पूर्ण
	mutex_unlock(&punit_misc_dev_lock);
पूर्ण
EXPORT_SYMBOL_GPL(isst_अगर_cdev_unरेजिस्टर);

MODULE_LICENSE("GPL v2");
