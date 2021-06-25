<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bioscalls.c - the lowlevel layer of the PnPBIOS driver
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/pnp.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kmod.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "pnpbios.h"

__visible काष्ठा अणु
	u16 offset;
	u16 segment;
पूर्ण pnp_bios_callpoपूर्णांक;

/*
 * These are some opcodes क्रम a "static asmlinkage"
 * As this code is *not* executed inside the linux kernel segment, but in a
 * alias at offset 0, we need a far वापस that can not be compiled by
 * शेष (please, prove me wrong! this is *really* ugly!)
 * This is the only way to get the bios to वापस पूर्णांकo the kernel code,
 * because the bios code runs in 16 bit रक्षित mode and thereक्रमe can only
 * वापस to the caller अगर the call is within the first 64kB, and the linux
 * kernel begins at offset 3GB...
 */

यंत्रlinkage __visible व्योम pnp_bios_callfunc(व्योम);

__यंत्र__(".text			\n"
	__ALIGN_STR "\n"
	".globl pnp_bios_callfunc\n"
	"pnp_bios_callfunc:\n"
	"	pushl %edx	\n"
	"	pushl %ecx	\n"
	"	pushl %ebx	\n"
	"	pushl %eax	\n"
	"	lcallw *pnp_bios_callpoint\n"
	"	addl $16, %esp	\n"
	"	lret		\n"
	".previous		\n");

#घोषणा Q2_SET_SEL(cpu, selname, address, size) \
करो अणु \
	काष्ठा desc_काष्ठा *gdt = get_cpu_gdt_rw((cpu)); \
	set_desc_base(&gdt[(selname) >> 3], (u32)(address)); \
	set_desc_limit(&gdt[(selname) >> 3], (size) - 1); \
पूर्ण जबतक(0)

अटल काष्ठा desc_काष्ठा bad_bios_desc = GDT_ENTRY_INIT(0x4092,
			(अचिन्हित दीर्घ)__va(0x400UL), PAGE_SIZE - 0x400 - 1);

/*
 * At some poपूर्णांक we want to use this stack frame poपूर्णांकer to unwind
 * after PnP BIOS oopses.
 */

__visible u32 pnp_bios_fault_esp;
__visible u32 pnp_bios_fault_eip;
__visible u32 pnp_bios_is_utter_crap = 0;

अटल DEFINE_SPINLOCK(pnp_bios_lock);

/*
 * Support Functions
 */

अटल अंतरभूत u16 call_pnp_bios(u16 func, u16 arg1, u16 arg2, u16 arg3,
				u16 arg4, u16 arg5, u16 arg6, u16 arg7,
				व्योम *ts1_base, u32 ts1_size,
				व्योम *ts2_base, u32 ts2_size)
अणु
	अचिन्हित दीर्घ flags;
	u16 status;
	काष्ठा desc_काष्ठा save_desc_40;
	पूर्णांक cpu;

	/*
	 * PnP BIOSes are generally not terribly re-entrant.
	 * Also, करोn't rely on them to save everything correctly.
	 */
	अगर (pnp_bios_is_utter_crap)
		वापस PNP_FUNCTION_NOT_SUPPORTED;

	cpu = get_cpu();
	save_desc_40 = get_cpu_gdt_rw(cpu)[0x40 / 8];
	get_cpu_gdt_rw(cpu)[0x40 / 8] = bad_bios_desc;

	/* On some boxes IRQ's during PnP BIOS calls are deadly.  */
	spin_lock_irqsave(&pnp_bios_lock, flags);

	/* The lock prevents us bouncing CPU here */
	अगर (ts1_size)
		Q2_SET_SEL(smp_processor_id(), PNP_TS1, ts1_base, ts1_size);
	अगर (ts2_size)
		Q2_SET_SEL(smp_processor_id(), PNP_TS2, ts2_base, ts2_size);

	__यंत्र__ __अस्थिर__("pushl %%ebp\n\t"
			     "pushl %%edi\n\t"
			     "pushl %%esi\n\t"
			     "pushl %%ds\n\t"
			     "pushl %%es\n\t"
			     "pushl %%fs\n\t"
			     "pushl %%gs\n\t"
			     "pushfl\n\t"
			     "movl %%esp, pnp_bios_fault_esp\n\t"
			     "movl $1f, pnp_bios_fault_eip\n\t"
			     "lcall %5,%6\n\t"
			     "1:popfl\n\t"
			     "popl %%gs\n\t"
			     "popl %%fs\n\t"
			     "popl %%es\n\t"
			     "popl %%ds\n\t"
			     "popl %%esi\n\t"
			     "popl %%edi\n\t"
			     "popl %%ebp\n\t":"=a"(status)
			     :"0"((func) | (((u32) arg1) << 16)),
			     "b"((arg2) | (((u32) arg3) << 16)),
			     "c"((arg4) | (((u32) arg5) << 16)),
			     "d"((arg6) | (((u32) arg7) << 16)),
			     "i"(PNP_CS32), "i"(0)
			     :"memory");
	spin_unlock_irqrestore(&pnp_bios_lock, flags);

	get_cpu_gdt_rw(cpu)[0x40 / 8] = save_desc_40;
	put_cpu();

	/* If we get here and this is set then the PnP BIOS faulted on us. */
	अगर (pnp_bios_is_utter_crap) अणु
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: Warning! Your PnP BIOS caused a fatal error. Attempting to continue\n");
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: You may need to reboot with the \"pnpbios=off\" option to operate stably\n");
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: Check with your vendor for an updated BIOS\n");
	पूर्ण

	वापस status;
पूर्ण

व्योम pnpbios_prपूर्णांक_status(स्थिर अक्षर *module, u16 status)
अणु
	चयन (status) अणु
	हाल PNP_SUCCESS:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: function successful\n", module);
		अवरोध;
	हाल PNP_NOT_SET_STATICALLY:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: unable to set static resources\n",
		       module);
		अवरोध;
	हाल PNP_UNKNOWN_FUNCTION:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: invalid function number passed\n",
		       module);
		अवरोध;
	हाल PNP_FUNCTION_NOT_SUPPORTED:
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: %s: function not supported on this system\n",
		       module);
		अवरोध;
	हाल PNP_INVALID_HANDLE:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: invalid handle\n", module);
		अवरोध;
	हाल PNP_BAD_PARAMETER:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: invalid parameters were passed\n",
		       module);
		अवरोध;
	हाल PNP_SET_FAILED:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: unable to set resources\n",
		       module);
		अवरोध;
	हाल PNP_EVENTS_NOT_PENDING:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: no events are pending\n", module);
		अवरोध;
	हाल PNP_SYSTEM_NOT_DOCKED:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: the system is not docked\n",
		       module);
		अवरोध;
	हाल PNP_NO_ISA_PNP_CARDS:
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: %s: no isapnp cards are installed on this system\n",
		       module);
		अवरोध;
	हाल PNP_UNABLE_TO_DETERMINE_DOCK_CAPABILITIES:
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: %s: cannot determine the capabilities of the docking station\n",
		       module);
		अवरोध;
	हाल PNP_CONFIG_CHANGE_FAILED_NO_BATTERY:
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: %s: unable to undock, the system does not have a battery\n",
		       module);
		अवरोध;
	हाल PNP_CONFIG_CHANGE_FAILED_RESOURCE_CONFLICT:
		prपूर्णांकk(KERN_ERR
		       "PnPBIOS: %s: could not dock due to resource conflicts\n",
		       module);
		अवरोध;
	हाल PNP_BUFFER_TOO_SMALL:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: the buffer passed is too small\n",
		       module);
		अवरोध;
	हाल PNP_USE_ESCD_SUPPORT:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: use ESCD instead\n", module);
		अवरोध;
	हाल PNP_MESSAGE_NOT_SUPPORTED:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: the message is unsupported\n",
		       module);
		अवरोध;
	हाल PNP_HARDWARE_ERROR:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: a hardware failure has occurred\n",
		       module);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "PnPBIOS: %s: unexpected status 0x%x\n", module,
		       status);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * PnP BIOS Low Level Calls
 */

#घोषणा PNP_GET_NUM_SYS_DEV_NODES		0x00
#घोषणा PNP_GET_SYS_DEV_NODE			0x01
#घोषणा PNP_SET_SYS_DEV_NODE			0x02
#घोषणा PNP_GET_EVENT				0x03
#घोषणा PNP_SEND_MESSAGE			0x04
#घोषणा PNP_GET_DOCKING_STATION_INFORMATION	0x05
#घोषणा PNP_SET_STATIC_ALLOCED_RES_INFO		0x09
#घोषणा PNP_GET_STATIC_ALLOCED_RES_INFO		0x0a
#घोषणा PNP_GET_APM_ID_TABLE			0x0b
#घोषणा PNP_GET_PNP_ISA_CONFIG_STRUC		0x40
#घोषणा PNP_GET_ESCD_INFO			0x41
#घोषणा PNP_READ_ESCD				0x42
#घोषणा PNP_WRITE_ESCD				0x43

/*
 * Call PnP BIOS with function 0x00, "get number of system device nodes"
 */
अटल पूर्णांक __pnp_bios_dev_node_info(काष्ठा pnp_dev_node_info *data)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_NUM_SYS_DEV_NODES, 0, PNP_TS1, 2,
			       PNP_TS1, PNP_DS, 0, 0, data,
			       माप(काष्ठा pnp_dev_node_info), शून्य, 0);
	data->no_nodes &= 0xff;
	वापस status;
पूर्ण

पूर्णांक pnp_bios_dev_node_info(काष्ठा pnp_dev_node_info *data)
अणु
	पूर्णांक status = __pnp_bios_dev_node_info(data);

	अगर (status)
		pnpbios_prपूर्णांक_status("dev_node_info", status);
	वापस status;
पूर्ण

/*
 * Note that some PnP BIOSes (e.g., on Sony Vaio laptops) die a horrible
 * death अगर they are asked to access the "current" configuration.
 * Thereक्रमe, अगर it's a matter of indifference, it's better to call
 * get_dev_node() and set_dev_node() with boot=1 rather than with boot=0.
 */

/* 
 * Call PnP BIOS with function 0x01, "get system device node"
 * Input: *nodक्रमागत = desired node,
 *        boot = whether to get nonअस्थिर boot (!=0)
 *               or अस्थिर current (0) config
 * Output: *nodक्रमागत=next node or 0xff अगर no more nodes
 */
अटल पूर्णांक __pnp_bios_get_dev_node(u8 *nodक्रमागत, अक्षर boot,
				   काष्ठा pnp_bios_node *data)
अणु
	u16 status;
	u16 पंचांगp_nodक्रमागत;

	अगर (!pnp_bios_present())
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	अगर (!boot && pnpbios_करोnt_use_current_config)
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	पंचांगp_nodक्रमागत = *nodक्रमागत;
	status = call_pnp_bios(PNP_GET_SYS_DEV_NODE, 0, PNP_TS1, 0, PNP_TS2,
			       boot ? 2 : 1, PNP_DS, 0, &पंचांगp_nodक्रमागत,
			       माप(पंचांगp_nodक्रमागत), data, 65536);
	*nodक्रमागत = पंचांगp_nodक्रमागत;
	वापस status;
पूर्ण

पूर्णांक pnp_bios_get_dev_node(u8 *nodक्रमागत, अक्षर boot, काष्ठा pnp_bios_node *data)
अणु
	पूर्णांक status;

	status = __pnp_bios_get_dev_node(nodक्रमागत, boot, data);
	अगर (status)
		pnpbios_prपूर्णांक_status("get_dev_node", status);
	वापस status;
पूर्ण

/*
 * Call PnP BIOS with function 0x02, "set system device node"
 * Input: *nodक्रमागत = desired node, 
 *        boot = whether to set nonअस्थिर boot (!=0)
 *               or अस्थिर current (0) config
 */
अटल पूर्णांक __pnp_bios_set_dev_node(u8 nodक्रमागत, अक्षर boot,
				   काष्ठा pnp_bios_node *data)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	अगर (!boot && pnpbios_करोnt_use_current_config)
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_SET_SYS_DEV_NODE, nodक्रमागत, 0, PNP_TS1,
			       boot ? 2 : 1, PNP_DS, 0, 0, data, 65536, शून्य,
			       0);
	वापस status;
पूर्ण

पूर्णांक pnp_bios_set_dev_node(u8 nodक्रमागत, अक्षर boot, काष्ठा pnp_bios_node *data)
अणु
	पूर्णांक status;

	status = __pnp_bios_set_dev_node(nodक्रमागत, boot, data);
	अगर (status) अणु
		pnpbios_prपूर्णांक_status("set_dev_node", status);
		वापस status;
	पूर्ण
	अगर (!boot) अणु		/* Update devlist */
		status = pnp_bios_get_dev_node(&nodक्रमागत, boot, data);
		अगर (status)
			वापस status;
	पूर्ण
	वापस status;
पूर्ण

/*
 * Call PnP BIOS with function 0x05, "get docking station information"
 */
पूर्णांक pnp_bios_करोck_station_info(काष्ठा pnp_करोcking_station_info *data)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_DOCKING_STATION_INFORMATION, 0, PNP_TS1,
			       PNP_DS, 0, 0, 0, 0, data,
			       माप(काष्ठा pnp_करोcking_station_info), शून्य,
			       0);
	वापस status;
पूर्ण

/*
 * Call PnP BIOS with function 0x0a, "get अटलally allocated resource
 * inक्रमmation"
 */
अटल पूर्णांक __pnp_bios_get_stat_res(अक्षर *info)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_STATIC_ALLOCED_RES_INFO, 0, PNP_TS1,
			       PNP_DS, 0, 0, 0, 0, info, 65536, शून्य, 0);
	वापस status;
पूर्ण

पूर्णांक pnp_bios_get_stat_res(अक्षर *info)
अणु
	पूर्णांक status;

	status = __pnp_bios_get_stat_res(info);
	अगर (status)
		pnpbios_prपूर्णांक_status("get_stat_res", status);
	वापस status;
पूर्ण

/*
 * Call PnP BIOS with function 0x40, "get isa pnp configuration structure"
 */
अटल पूर्णांक __pnp_bios_isapnp_config(काष्ठा pnp_isa_config_struc *data)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_PNP_ISA_CONFIG_STRUC, 0, PNP_TS1, PNP_DS,
			       0, 0, 0, 0, data,
			       माप(काष्ठा pnp_isa_config_struc), शून्य, 0);
	वापस status;
पूर्ण

पूर्णांक pnp_bios_isapnp_config(काष्ठा pnp_isa_config_struc *data)
अणु
	पूर्णांक status;

	status = __pnp_bios_isapnp_config(data);
	अगर (status)
		pnpbios_prपूर्णांक_status("isapnp_config", status);
	वापस status;
पूर्ण

/*
 * Call PnP BIOS with function 0x41, "get ESCD info"
 */
अटल पूर्णांक __pnp_bios_escd_info(काष्ठा escd_info_struc *data)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस ESCD_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_ESCD_INFO, 0, PNP_TS1, 2, PNP_TS1, 4,
			       PNP_TS1, PNP_DS, data,
			       माप(काष्ठा escd_info_struc), शून्य, 0);
	वापस status;
पूर्ण

पूर्णांक pnp_bios_escd_info(काष्ठा escd_info_struc *data)
अणु
	पूर्णांक status;

	status = __pnp_bios_escd_info(data);
	अगर (status)
		pnpbios_prपूर्णांक_status("escd_info", status);
	वापस status;
पूर्ण

/*
 * Call PnP BIOS function 0x42, "read ESCD"
 * nvram_base is determined by calling escd_info
 */
अटल पूर्णांक __pnp_bios_पढ़ो_escd(अक्षर *data, u32 nvram_base)
अणु
	u16 status;

	अगर (!pnp_bios_present())
		वापस ESCD_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_READ_ESCD, 0, PNP_TS1, PNP_TS2, PNP_DS, 0, 0,
			       0, data, 65536, __va(nvram_base), 65536);
	वापस status;
पूर्ण

पूर्णांक pnp_bios_पढ़ो_escd(अक्षर *data, u32 nvram_base)
अणु
	पूर्णांक status;

	status = __pnp_bios_पढ़ो_escd(data, nvram_base);
	अगर (status)
		pnpbios_prपूर्णांक_status("read_escd", status);
	वापस status;
पूर्ण

व्योम pnpbios_calls_init(जोड़ pnp_bios_install_काष्ठा *header)
अणु
	पूर्णांक i;

	pnp_bios_callpoपूर्णांक.offset = header->fields.pm16offset;
	pnp_bios_callpoपूर्णांक.segment = PNP_CS16;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा desc_काष्ठा *gdt = get_cpu_gdt_rw(i);
		अगर (!gdt)
			जारी;
		set_desc_base(&gdt[GDT_ENTRY_PNPBIOS_CS32],
			 (अचिन्हित दीर्घ)&pnp_bios_callfunc);
		set_desc_base(&gdt[GDT_ENTRY_PNPBIOS_CS16],
			 (अचिन्हित दीर्घ)__va(header->fields.pm16cseg));
		set_desc_base(&gdt[GDT_ENTRY_PNPBIOS_DS],
			 (अचिन्हित दीर्घ)__va(header->fields.pm16dseg));
	पूर्ण
पूर्ण
