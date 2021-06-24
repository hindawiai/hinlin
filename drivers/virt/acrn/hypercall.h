<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ACRN HSM: hypercalls of ACRN Hypervisor
 */
#अगर_अघोषित __ACRN_HSM_HYPERCALL_H
#घोषणा __ACRN_HSM_HYPERCALL_H
#समावेश <यंत्र/acrn.h>

/*
 * Hypercall IDs of the ACRN Hypervisor
 */
#घोषणा _HC_ID(x, y) (((x) << 24) | (y))

#घोषणा HC_ID 0x80UL

#घोषणा HC_ID_GEN_BASE			0x0UL
#घोषणा HC_SOS_REMOVE_CPU		_HC_ID(HC_ID, HC_ID_GEN_BASE + 0x01)

#घोषणा HC_ID_VM_BASE			0x10UL
#घोषणा HC_CREATE_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x00)
#घोषणा HC_DESTROY_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x01)
#घोषणा HC_START_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x02)
#घोषणा HC_PAUSE_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x03)
#घोषणा HC_RESET_VM			_HC_ID(HC_ID, HC_ID_VM_BASE + 0x05)
#घोषणा HC_SET_VCPU_REGS		_HC_ID(HC_ID, HC_ID_VM_BASE + 0x06)

#घोषणा HC_ID_IRQ_BASE			0x20UL
#घोषणा HC_INJECT_MSI			_HC_ID(HC_ID, HC_ID_IRQ_BASE + 0x03)
#घोषणा HC_VM_INTR_MONITOR		_HC_ID(HC_ID, HC_ID_IRQ_BASE + 0x04)
#घोषणा HC_SET_IRQLINE			_HC_ID(HC_ID, HC_ID_IRQ_BASE + 0x05)

#घोषणा HC_ID_IOREQ_BASE		0x30UL
#घोषणा HC_SET_IOREQ_BUFFER		_HC_ID(HC_ID, HC_ID_IOREQ_BASE + 0x00)
#घोषणा HC_NOTIFY_REQUEST_FINISH	_HC_ID(HC_ID, HC_ID_IOREQ_BASE + 0x01)

#घोषणा HC_ID_MEM_BASE			0x40UL
#घोषणा HC_VM_SET_MEMORY_REGIONS	_HC_ID(HC_ID, HC_ID_MEM_BASE + 0x02)

#घोषणा HC_ID_PCI_BASE			0x50UL
#घोषणा HC_SET_PTDEV_INTR		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x03)
#घोषणा HC_RESET_PTDEV_INTR		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x04)
#घोषणा HC_ASSIGN_PCIDEV		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x05)
#घोषणा HC_DEASSIGN_PCIDEV		_HC_ID(HC_ID, HC_ID_PCI_BASE + 0x06)

#घोषणा HC_ID_PM_BASE			0x80UL
#घोषणा HC_PM_GET_CPU_STATE		_HC_ID(HC_ID, HC_ID_PM_BASE + 0x00)

/**
 * hcall_sos_हटाओ_cpu() - Remove a vCPU of Service VM
 * @cpu: The vCPU to be हटाओd
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_sos_हटाओ_cpu(u64 cpu)
अणु
	वापस acrn_hypercall1(HC_SOS_REMOVE_CPU, cpu);
पूर्ण

/**
 * hcall_create_vm() - Create a User VM
 * @vminfo:	Service VM GPA of info of User VM creation
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_create_vm(u64 vminfo)
अणु
	वापस acrn_hypercall1(HC_CREATE_VM, vminfo);
पूर्ण

/**
 * hcall_start_vm() - Start a User VM
 * @vmid:	User VM ID
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_start_vm(u64 vmid)
अणु
	वापस acrn_hypercall1(HC_START_VM, vmid);
पूर्ण

/**
 * hcall_छोड़ो_vm() - Pause a User VM
 * @vmid:	User VM ID
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_छोड़ो_vm(u64 vmid)
अणु
	वापस acrn_hypercall1(HC_PAUSE_VM, vmid);
पूर्ण

/**
 * hcall_destroy_vm() - Destroy a User VM
 * @vmid:	User VM ID
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_destroy_vm(u64 vmid)
अणु
	वापस acrn_hypercall1(HC_DESTROY_VM, vmid);
पूर्ण

/**
 * hcall_reset_vm() - Reset a User VM
 * @vmid:	User VM ID
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_reset_vm(u64 vmid)
अणु
	वापस acrn_hypercall1(HC_RESET_VM, vmid);
पूर्ण

/**
 * hcall_set_vcpu_regs() - Set up रेजिस्टरs of भव CPU of a User VM
 * @vmid:	User VM ID
 * @regs_state:	Service VM GPA of रेजिस्टरs state
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_set_vcpu_regs(u64 vmid, u64 regs_state)
अणु
	वापस acrn_hypercall2(HC_SET_VCPU_REGS, vmid, regs_state);
पूर्ण

/**
 * hcall_inject_msi() - Deliver a MSI पूर्णांकerrupt to a User VM
 * @vmid:	User VM ID
 * @msi:	Service VM GPA of MSI message
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_inject_msi(u64 vmid, u64 msi)
अणु
	वापस acrn_hypercall2(HC_INJECT_MSI, vmid, msi);
पूर्ण

/**
 * hcall_vm_पूर्णांकr_monitor() - Set a shared page क्रम User VM पूर्णांकerrupt statistics
 * @vmid:	User VM ID
 * @addr:	Service VM GPA of the shared page
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_vm_पूर्णांकr_monitor(u64 vmid, u64 addr)
अणु
	वापस acrn_hypercall2(HC_VM_INTR_MONITOR, vmid, addr);
पूर्ण

/**
 * hcall_set_irqline() - Set or clear an पूर्णांकerrupt line
 * @vmid:	User VM ID
 * @op:		Service VM GPA of पूर्णांकerrupt line operations
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_set_irqline(u64 vmid, u64 op)
अणु
	वापस acrn_hypercall2(HC_SET_IRQLINE, vmid, op);
पूर्ण

/**
 * hcall_set_ioreq_buffer() - Set up the shared buffer क्रम I/O Requests.
 * @vmid:	User VM ID
 * @buffer:	Service VM GPA of the shared buffer
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_set_ioreq_buffer(u64 vmid, u64 buffer)
अणु
	वापस acrn_hypercall2(HC_SET_IOREQ_BUFFER, vmid, buffer);
पूर्ण

/**
 * hcall_notअगरy_req_finish() - Notअगरy ACRN Hypervisor of I/O request completion.
 * @vmid:	User VM ID
 * @vcpu:	The vCPU which initiated the I/O request
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_notअगरy_req_finish(u64 vmid, u64 vcpu)
अणु
	वापस acrn_hypercall2(HC_NOTIFY_REQUEST_FINISH, vmid, vcpu);
पूर्ण

/**
 * hcall_set_memory_regions() - Inक्रमm the hypervisor to set up EPT mappings
 * @regions_pa:	Service VM GPA of &काष्ठा vm_memory_region_batch
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_set_memory_regions(u64 regions_pa)
अणु
	वापस acrn_hypercall1(HC_VM_SET_MEMORY_REGIONS, regions_pa);
पूर्ण

/**
 * hcall_assign_pcidev() - Assign a PCI device to a User VM
 * @vmid:	User VM ID
 * @addr:	Service VM GPA of the &काष्ठा acrn_pcidev
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_assign_pcidev(u64 vmid, u64 addr)
अणु
	वापस acrn_hypercall2(HC_ASSIGN_PCIDEV, vmid, addr);
पूर्ण

/**
 * hcall_deassign_pcidev() - De-assign a PCI device from a User VM
 * @vmid:	User VM ID
 * @addr:	Service VM GPA of the &काष्ठा acrn_pcidev
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_deassign_pcidev(u64 vmid, u64 addr)
अणु
	वापस acrn_hypercall2(HC_DEASSIGN_PCIDEV, vmid, addr);
पूर्ण

/**
 * hcall_set_ptdev_पूर्णांकr() - Configure an पूर्णांकerrupt क्रम an asचिन्हित PCI device.
 * @vmid:	User VM ID
 * @irq:	Service VM GPA of the &काष्ठा acrn_ptdev_irq
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_set_ptdev_पूर्णांकr(u64 vmid, u64 irq)
अणु
	वापस acrn_hypercall2(HC_SET_PTDEV_INTR, vmid, irq);
पूर्ण

/**
 * hcall_reset_ptdev_पूर्णांकr() - Reset an पूर्णांकerrupt क्रम an asचिन्हित PCI device.
 * @vmid:	User VM ID
 * @irq:	Service VM GPA of the &काष्ठा acrn_ptdev_irq
 *
 * Return: 0 on success, <0 on failure
 */
अटल अंतरभूत दीर्घ hcall_reset_ptdev_पूर्णांकr(u64 vmid, u64 irq)
अणु
	वापस acrn_hypercall2(HC_RESET_PTDEV_INTR, vmid, irq);
पूर्ण

/*
 * hcall_get_cpu_state() - Get P-states and C-states info from the hypervisor
 * @state:	Service VM GPA of buffer of P-states and C-states
 */
अटल अंतरभूत दीर्घ hcall_get_cpu_state(u64 cmd, u64 state)
अणु
	वापस acrn_hypercall2(HC_PM_GET_CPU_STATE, cmd, state);
पूर्ण

#पूर्ण_अगर /* __ACRN_HSM_HYPERCALL_H */
