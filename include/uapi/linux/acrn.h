<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Userspace पूर्णांकerface क्रम /dev/acrn_hsm - ACRN Hypervisor Service Module
 *
 * This file can be used by applications that need to communicate with the HSM
 * via the ioctl पूर्णांकerface.
 *
 * Copyright (C) 2021 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _UAPI_ACRN_H
#घोषणा _UAPI_ACRN_H

#समावेश <linux/types.h>
#समावेश <linux/uuid.h>

#घोषणा ACRN_IO_REQUEST_MAX		16

#घोषणा ACRN_IOREQ_STATE_PENDING	0
#घोषणा ACRN_IOREQ_STATE_COMPLETE	1
#घोषणा ACRN_IOREQ_STATE_PROCESSING	2
#घोषणा ACRN_IOREQ_STATE_FREE		3

#घोषणा ACRN_IOREQ_TYPE_PORTIO		0
#घोषणा ACRN_IOREQ_TYPE_MMIO		1
#घोषणा ACRN_IOREQ_TYPE_PCICFG		2

#घोषणा ACRN_IOREQ_सूची_READ		0
#घोषणा ACRN_IOREQ_सूची_WRITE		1

/**
 * काष्ठा acrn_mmio_request - Info of a MMIO I/O request
 * @direction:	Access direction of this request (ACRN_IOREQ_सूची_*)
 * @reserved:	Reserved क्रम alignment and should be 0
 * @address:	Access address of this MMIO I/O request
 * @size:	Access size of this MMIO I/O request
 * @value:	Read/ग_लिखो value of this MMIO I/O request
 */
काष्ठा acrn_mmio_request अणु
	__u32	direction;
	__u32	reserved;
	__u64	address;
	__u64	size;
	__u64	value;
पूर्ण;

/**
 * काष्ठा acrn_pio_request - Info of a PIO I/O request
 * @direction:	Access direction of this request (ACRN_IOREQ_सूची_*)
 * @reserved:	Reserved क्रम alignment and should be 0
 * @address:	Access address of this PIO I/O request
 * @size:	Access size of this PIO I/O request
 * @value:	Read/ग_लिखो value of this PIO I/O request
 */
काष्ठा acrn_pio_request अणु
	__u32	direction;
	__u32	reserved;
	__u64	address;
	__u64	size;
	__u32	value;
पूर्ण;

/**
 * काष्ठा acrn_pci_request - Info of a PCI I/O request
 * @direction:	Access direction of this request (ACRN_IOREQ_सूची_*)
 * @reserved:	Reserved क्रम alignment and should be 0
 * @size:	Access size of this PCI I/O request
 * @value:	Read/ग_लिखो value of this PIO I/O request
 * @bus:	PCI bus value of this PCI I/O request
 * @dev:	PCI device value of this PCI I/O request
 * @func:	PCI function value of this PCI I/O request
 * @reg:	PCI config space offset of this PCI I/O request
 *
 * Need keep same header layout with &काष्ठा acrn_pio_request.
 */
काष्ठा acrn_pci_request अणु
	__u32	direction;
	__u32	reserved[3];
	__u64	size;
	__u32	value;
	__u32	bus;
	__u32	dev;
	__u32	func;
	__u32	reg;
पूर्ण;

/**
 * काष्ठा acrn_io_request - 256-byte ACRN I/O request
 * @type:		Type of this request (ACRN_IOREQ_TYPE_*).
 * @completion_polling:	Polling flag. Hypervisor will poll completion of the
 *			I/O request अगर this flag set.
 * @reserved0:		Reserved fields.
 * @reqs:		Union of dअगरferent types of request. Byte offset: 64.
 * @reqs.pio_request:	PIO request data of the I/O request.
 * @reqs.pci_request:	PCI configuration space request data of the I/O request.
 * @reqs.mmio_request:	MMIO request data of the I/O request.
 * @reqs.data:		Raw data of the I/O request.
 * @reserved1:		Reserved fields.
 * @kernel_handled:	Flag indicates this request need be handled in kernel.
 * @processed:		The status of this request (ACRN_IOREQ_STATE_*).
 *
 * The state transitions of ACRN I/O request:
 *
 *    FREE -> PENDING -> PROCESSING -> COMPLETE -> FREE -> ...
 *
 * An I/O request in COMPLETE or FREE state is owned by the hypervisor. HSM and
 * ACRN userspace are in अक्षरge of processing the others.
 *
 * On basis of the states illustrated above, a typical lअगरecycle of ACRN IO
 * request would look like:
 *
 * Flow                 (assume the initial state is FREE)
 * |
 * |   Service VM vCPU 0     Service VM vCPU x      User vCPU y
 * |
 * |                                             hypervisor:
 * |                                               fills in type, addr, etc.
 * |                                               छोड़ोs the User VM vCPU y
 * |                                               sets the state to PENDING (a)
 * |                                               fires an upcall to Service VM
 * |
 * | HSM:
 * |  scans क्रम PENDING requests
 * |  sets the states to PROCESSING (b)
 * |  assigns the requests to clients (c)
 * V
 * |                     client:
 * |                       scans क्रम the asचिन्हित requests
 * |                       handles the requests (d)
 * |                     HSM:
 * |                       sets states to COMPLETE
 * |                       notअगरies the hypervisor
 * |
 * |                     hypervisor:
 * |                       resumes User VM vCPU y (e)
 * |
 * |                                             hypervisor:
 * |                                               post handling (f)
 * V                                               sets states to FREE
 *
 * Note that the procedures (a) to (f) in the illustration above require to be
 * strictly processed in the order.  One vCPU cannot trigger another request of
 * I/O emulation beक्रमe completing the previous one.
 *
 * Atomic and barriers are required when HSM and hypervisor accessing the state
 * of &काष्ठा acrn_io_request.
 *
 */
काष्ठा acrn_io_request अणु
	__u32	type;
	__u32	completion_polling;
	__u32	reserved0[14];
	जोड़ अणु
		काष्ठा acrn_pio_request		pio_request;
		काष्ठा acrn_pci_request		pci_request;
		काष्ठा acrn_mmio_request	mmio_request;
		__u64				data[8];
	पूर्ण reqs;
	__u32	reserved1;
	__u32	kernel_handled;
	__u32	processed;
पूर्ण __attribute__((aligned(256)));

काष्ठा acrn_io_request_buffer अणु
	जोड़ अणु
		काष्ठा acrn_io_request	req_slot[ACRN_IO_REQUEST_MAX];
		__u8			reserved[4096];
	पूर्ण;
पूर्ण;

/**
 * काष्ठा acrn_ioreq_notअगरy - The काष्ठाure of ioreq completion notअगरication
 * @vmid:	User VM ID
 * @reserved:	Reserved and should be 0
 * @vcpu:	vCPU ID
 */
काष्ठा acrn_ioreq_notअगरy अणु
	__u16	vmid;
	__u16	reserved;
	__u32	vcpu;
पूर्ण;

/**
 * काष्ठा acrn_vm_creation - Info to create a User VM
 * @vmid:		User VM ID वापसed from the hypervisor
 * @reserved0:		Reserved and must be 0
 * @vcpu_num:		Number of vCPU in the VM. Return from hypervisor.
 * @reserved1:		Reserved and must be 0
 * @uuid:		UUID of the VM. Pass to hypervisor directly.
 * @vm_flag:		Flag of the VM creating. Pass to hypervisor directly.
 * @ioreq_buf:		Service VM GPA of I/O request buffer. Pass to
 *			hypervisor directly.
 * @cpu_affinity:	CPU affinity of the VM. Pass to hypervisor directly.
 * 			It's a biपंचांगap which indicates CPUs used by the VM.
 */
काष्ठा acrn_vm_creation अणु
	__u16	vmid;
	__u16	reserved0;
	__u16	vcpu_num;
	__u16	reserved1;
	guid_t	uuid;
	__u64	vm_flag;
	__u64	ioreq_buf;
	__u64	cpu_affinity;
पूर्ण;

/**
 * काष्ठा acrn_gp_regs - General रेजिस्टरs of a User VM
 * @rax:	Value of रेजिस्टर RAX
 * @rcx:	Value of रेजिस्टर RCX
 * @rdx:	Value of रेजिस्टर RDX
 * @rbx:	Value of रेजिस्टर RBX
 * @rsp:	Value of रेजिस्टर RSP
 * @rbp:	Value of रेजिस्टर RBP
 * @rsi:	Value of रेजिस्टर RSI
 * @rdi:	Value of रेजिस्टर RDI
 * @r8:		Value of रेजिस्टर R8
 * @r9:		Value of रेजिस्टर R9
 * @r10:	Value of रेजिस्टर R10
 * @r11:	Value of रेजिस्टर R11
 * @r12:	Value of रेजिस्टर R12
 * @r13:	Value of रेजिस्टर R13
 * @r14:	Value of रेजिस्टर R14
 * @r15:	Value of रेजिस्टर R15
 */
काष्ठा acrn_gp_regs अणु
	__le64	rax;
	__le64	rcx;
	__le64	rdx;
	__le64	rbx;
	__le64	rsp;
	__le64	rbp;
	__le64	rsi;
	__le64	rdi;
	__le64	r8;
	__le64	r9;
	__le64	r10;
	__le64	r11;
	__le64	r12;
	__le64	r13;
	__le64	r14;
	__le64	r15;
पूर्ण;

/**
 * काष्ठा acrn_descriptor_ptr - Segment descriptor table of a User VM.
 * @limit:	Limit field.
 * @base:	Base field.
 * @reserved:	Reserved and must be 0.
 */
काष्ठा acrn_descriptor_ptr अणु
	__le16	limit;
	__le64	base;
	__le16	reserved[3];
पूर्ण __attribute__ ((__packed__));

/**
 * काष्ठा acrn_regs - Registers काष्ठाure of a User VM
 * @gprs:		General रेजिस्टरs
 * @gdt:		Global Descriptor Table
 * @idt:		Interrupt Descriptor Table
 * @rip:		Value of रेजिस्टर RIP
 * @cs_base:		Base of code segment selector
 * @cr0:		Value of रेजिस्टर CR0
 * @cr4:		Value of रेजिस्टर CR4
 * @cr3:		Value of रेजिस्टर CR3
 * @ia32_efer:		Value of IA32_EFER MSR
 * @rflags:		Value of regsiter RFLAGS
 * @reserved_64:	Reserved and must be 0
 * @cs_ar:		Attribute field of code segment selector
 * @cs_limit:		Limit field of code segment selector
 * @reserved_32:	Reserved and must be 0
 * @cs_sel:		Value of code segment selector
 * @ss_sel:		Value of stack segment selector
 * @ds_sel:		Value of data segment selector
 * @es_sel:		Value of extra segment selector
 * @fs_sel:		Value of FS selector
 * @gs_sel:		Value of GS selector
 * @ldt_sel:		Value of LDT descriptor selector
 * @tr_sel:		Value of TSS descriptor selector
 */
काष्ठा acrn_regs अणु
	काष्ठा acrn_gp_regs		gprs;
	काष्ठा acrn_descriptor_ptr	gdt;
	काष्ठा acrn_descriptor_ptr	idt;

	__le64				rip;
	__le64				cs_base;
	__le64				cr0;
	__le64				cr4;
	__le64				cr3;
	__le64				ia32_efer;
	__le64				rflags;
	__le64				reserved_64[4];

	__le32				cs_ar;
	__le32				cs_limit;
	__le32				reserved_32[3];

	__le16				cs_sel;
	__le16				ss_sel;
	__le16				ds_sel;
	__le16				es_sel;
	__le16				fs_sel;
	__le16				gs_sel;
	__le16				ldt_sel;
	__le16				tr_sel;
पूर्ण;

/**
 * काष्ठा acrn_vcpu_regs - Info of vCPU रेजिस्टरs state
 * @vcpu_id:	vCPU ID
 * @reserved:	Reserved and must be 0
 * @vcpu_regs:	vCPU रेजिस्टरs state
 *
 * This काष्ठाure will be passed to hypervisor directly.
 */
काष्ठा acrn_vcpu_regs अणु
	__u16			vcpu_id;
	__u16			reserved[3];
	काष्ठा acrn_regs	vcpu_regs;
पूर्ण;

#घोषणा	ACRN_MEM_ACCESS_RIGHT_MASK	0x00000007U
#घोषणा	ACRN_MEM_ACCESS_READ		0x00000001U
#घोषणा	ACRN_MEM_ACCESS_WRITE		0x00000002U
#घोषणा	ACRN_MEM_ACCESS_EXEC		0x00000004U
#घोषणा	ACRN_MEM_ACCESS_RWX		(ACRN_MEM_ACCESS_READ  | \
					 ACRN_MEM_ACCESS_WRITE | \
					 ACRN_MEM_ACCESS_EXEC)

#घोषणा	ACRN_MEM_TYPE_MASK		0x000007C0U
#घोषणा	ACRN_MEM_TYPE_WB		0x00000040U
#घोषणा	ACRN_MEM_TYPE_WT		0x00000080U
#घोषणा	ACRN_MEM_TYPE_UC		0x00000100U
#घोषणा	ACRN_MEM_TYPE_WC		0x00000200U
#घोषणा	ACRN_MEM_TYPE_WP		0x00000400U

/* Memory mapping types */
#घोषणा	ACRN_MEMMAP_RAM			0
#घोषणा	ACRN_MEMMAP_MMIO		1

/**
 * काष्ठा acrn_vm_memmap - A EPT memory mapping info क्रम a User VM.
 * @type:		Type of the memory mapping (ACRM_MEMMAP_*).
 *			Pass to hypervisor directly.
 * @attr:		Attribute of the memory mapping.
 *			Pass to hypervisor directly.
 * @user_vm_pa:		Physical address of User VM.
 *			Pass to hypervisor directly.
 * @service_vm_pa:	Physical address of Service VM.
 *			Pass to hypervisor directly.
 * @vma_base:		VMA address of Service VM. Pass to hypervisor directly.
 * @len:		Length of the memory mapping.
 *			Pass to hypervisor directly.
 */
काष्ठा acrn_vm_memmap अणु
	__u32	type;
	__u32	attr;
	__u64	user_vm_pa;
	जोड़ अणु
		__u64	service_vm_pa;
		__u64	vma_base;
	पूर्ण;
	__u64	len;
पूर्ण;

/* Type of पूर्णांकerrupt of a passthrough device */
#घोषणा ACRN_PTDEV_IRQ_INTX	0
#घोषणा ACRN_PTDEV_IRQ_MSI	1
#घोषणा ACRN_PTDEV_IRQ_MSIX	2
/**
 * काष्ठा acrn_ptdev_irq - Interrupt data of a passthrough device.
 * @type:		Type (ACRN_PTDEV_IRQ_*)
 * @virt_bdf:		Virtual Bus/Device/Function
 * @phys_bdf:		Physical Bus/Device/Function
 * @पूर्णांकx:		Info of पूर्णांकerrupt
 * @पूर्णांकx.virt_pin:	Virtual IOAPIC pin
 * @पूर्णांकx.phys_pin:	Physical IOAPIC pin
 * @पूर्णांकx.is_pic_pin:	Is PIC pin or not
 *
 * This काष्ठाure will be passed to hypervisor directly.
 */
काष्ठा acrn_ptdev_irq अणु
	__u32	type;
	__u16	virt_bdf;
	__u16	phys_bdf;

	काष्ठा अणु
		__u32	virt_pin;
		__u32	phys_pin;
		__u32	is_pic_pin;
	पूर्ण पूर्णांकx;
पूर्ण;

/* Type of PCI device assignment */
#घोषणा ACRN_PTDEV_QUIRK_ASSIGN	(1U << 0)

#घोषणा ACRN_PCI_NUM_BARS	6
/**
 * काष्ठा acrn_pcidev - Info क्रम assigning or de-assigning a PCI device
 * @type:	Type of the assignment
 * @virt_bdf:	Virtual Bus/Device/Function
 * @phys_bdf:	Physical Bus/Device/Function
 * @पूर्णांकr_line:	PCI पूर्णांकerrupt line
 * @पूर्णांकr_pin:	PCI पूर्णांकerrupt pin
 * @bar:	PCI BARs.
 *
 * This काष्ठाure will be passed to hypervisor directly.
 */
काष्ठा acrn_pcidev अणु
	__u32	type;
	__u16	virt_bdf;
	__u16	phys_bdf;
	__u8	पूर्णांकr_line;
	__u8	पूर्णांकr_pin;
	__u32	bar[ACRN_PCI_NUM_BARS];
पूर्ण;

/**
 * काष्ठा acrn_msi_entry - Info क्रम injecting a MSI पूर्णांकerrupt to a VM
 * @msi_addr:	MSI addr[19:12] with dest vCPU ID
 * @msi_data:	MSI data[7:0] with vector
 */
काष्ठा acrn_msi_entry अणु
	__u64	msi_addr;
	__u64	msi_data;
पूर्ण;

काष्ठा acrn_acpi_generic_address अणु
	__u8	space_id;
	__u8	bit_width;
	__u8	bit_offset;
	__u8	access_size;
	__u64	address;
पूर्ण __attribute__ ((__packed__));

/**
 * काष्ठा acrn_cstate_data - A C state package defined in ACPI
 * @cx_reg:	Register of the C state object
 * @type:	Type of the C state object
 * @latency:	The worst-हाल latency to enter and निकास this C state
 * @घातer:	The average घातer consumption when in this C state
 */
काष्ठा acrn_cstate_data अणु
	काष्ठा acrn_acpi_generic_address	cx_reg;
	__u8					type;
	__u32					latency;
	__u64					घातer;
पूर्ण;

/**
 * काष्ठा acrn_pstate_data - A P state package defined in ACPI
 * @core_frequency:	CPU frequency (in MHz).
 * @घातer:		Power dissipation (in milliwatts).
 * @transition_latency:	The worst-हाल latency in microseconds that CPU is
 * 			unavailable during a transition from any P state to
 * 			this P state.
 * @bus_master_latency:	The worst-हाल latency in microseconds that Bus Masters
 * 			are prevented from accessing memory during a transition
 * 			from any P state to this P state.
 * @control:		The value to be written to Perक्रमmance Control Register
 * @status:		Transition status.
 */
काष्ठा acrn_pstate_data अणु
	__u64	core_frequency;
	__u64	घातer;
	__u64	transition_latency;
	__u64	bus_master_latency;
	__u64	control;
	__u64	status;
पूर्ण;

#घोषणा PMCMD_TYPE_MASK		0x000000ff
क्रमागत acrn_pm_cmd_type अणु
	ACRN_PMCMD_GET_PX_CNT,
	ACRN_PMCMD_GET_PX_DATA,
	ACRN_PMCMD_GET_CX_CNT,
	ACRN_PMCMD_GET_CX_DATA,
पूर्ण;

#घोषणा ACRN_IOEVENTFD_FLAG_PIO		0x01
#घोषणा ACRN_IOEVENTFD_FLAG_DATAMATCH	0x02
#घोषणा ACRN_IOEVENTFD_FLAG_DEASSIGN	0x04
/**
 * काष्ठा acrn_ioeventfd - Data to operate a &काष्ठा hsm_ioeventfd
 * @fd:		The fd of eventfd associated with a hsm_ioeventfd
 * @flags:	Logical-OR of ACRN_IOEVENTFD_FLAG_*
 * @addr:	The start address of IO range of ioeventfd
 * @len:	The length of IO range of ioeventfd
 * @reserved:	Reserved and should be 0
 * @data:	Data क्रम data matching
 *
 * Without flag ACRN_IOEVENTFD_FLAG_DEASSIGN, ioctl ACRN_IOCTL_IOEVENTFD
 * creates a &काष्ठा hsm_ioeventfd with properties originated from &काष्ठा
 * acrn_ioeventfd. With flag ACRN_IOEVENTFD_FLAG_DEASSIGN, ioctl
 * ACRN_IOCTL_IOEVENTFD destroys the &काष्ठा hsm_ioeventfd matching the fd.
 */
काष्ठा acrn_ioeventfd अणु
	__u32	fd;
	__u32	flags;
	__u64	addr;
	__u32	len;
	__u32	reserved;
	__u64	data;
पूर्ण;

#घोषणा ACRN_IRQFD_FLAG_DEASSIGN	0x01
/**
 * काष्ठा acrn_irqfd - Data to operate a &काष्ठा hsm_irqfd
 * @fd:		The fd of eventfd associated with a hsm_irqfd
 * @flags:	Logical-OR of ACRN_IRQFD_FLAG_*
 * @msi:	Info of MSI associated with the irqfd
 */
काष्ठा acrn_irqfd अणु
	__s32			fd;
	__u32			flags;
	काष्ठा acrn_msi_entry	msi;
पूर्ण;

/* The ioctl type, करोcumented in ioctl-number.rst */
#घोषणा ACRN_IOCTL_TYPE			0xA2

/*
 * Common IOCTL IDs definition क्रम ACRN userspace
 */
#घोषणा ACRN_IOCTL_CREATE_VM		\
	_IOWR(ACRN_IOCTL_TYPE, 0x10, काष्ठा acrn_vm_creation)
#घोषणा ACRN_IOCTL_DESTROY_VM		\
	_IO(ACRN_IOCTL_TYPE, 0x11)
#घोषणा ACRN_IOCTL_START_VM		\
	_IO(ACRN_IOCTL_TYPE, 0x12)
#घोषणा ACRN_IOCTL_PAUSE_VM		\
	_IO(ACRN_IOCTL_TYPE, 0x13)
#घोषणा ACRN_IOCTL_RESET_VM		\
	_IO(ACRN_IOCTL_TYPE, 0x15)
#घोषणा ACRN_IOCTL_SET_VCPU_REGS	\
	_IOW(ACRN_IOCTL_TYPE, 0x16, काष्ठा acrn_vcpu_regs)

#घोषणा ACRN_IOCTL_INJECT_MSI		\
	_IOW(ACRN_IOCTL_TYPE, 0x23, काष्ठा acrn_msi_entry)
#घोषणा ACRN_IOCTL_VM_INTR_MONITOR	\
	_IOW(ACRN_IOCTL_TYPE, 0x24, अचिन्हित दीर्घ)
#घोषणा ACRN_IOCTL_SET_IRQLINE		\
	_IOW(ACRN_IOCTL_TYPE, 0x25, __u64)

#घोषणा ACRN_IOCTL_NOTIFY_REQUEST_FINISH \
	_IOW(ACRN_IOCTL_TYPE, 0x31, काष्ठा acrn_ioreq_notअगरy)
#घोषणा ACRN_IOCTL_CREATE_IOREQ_CLIENT	\
	_IO(ACRN_IOCTL_TYPE, 0x32)
#घोषणा ACRN_IOCTL_ATTACH_IOREQ_CLIENT	\
	_IO(ACRN_IOCTL_TYPE, 0x33)
#घोषणा ACRN_IOCTL_DESTROY_IOREQ_CLIENT	\
	_IO(ACRN_IOCTL_TYPE, 0x34)
#घोषणा ACRN_IOCTL_CLEAR_VM_IOREQ	\
	_IO(ACRN_IOCTL_TYPE, 0x35)

#घोषणा ACRN_IOCTL_SET_MEMSEG		\
	_IOW(ACRN_IOCTL_TYPE, 0x41, काष्ठा acrn_vm_memmap)
#घोषणा ACRN_IOCTL_UNSET_MEMSEG		\
	_IOW(ACRN_IOCTL_TYPE, 0x42, काष्ठा acrn_vm_memmap)

#घोषणा ACRN_IOCTL_SET_PTDEV_INTR	\
	_IOW(ACRN_IOCTL_TYPE, 0x53, काष्ठा acrn_ptdev_irq)
#घोषणा ACRN_IOCTL_RESET_PTDEV_INTR	\
	_IOW(ACRN_IOCTL_TYPE, 0x54, काष्ठा acrn_ptdev_irq)
#घोषणा ACRN_IOCTL_ASSIGN_PCIDEV	\
	_IOW(ACRN_IOCTL_TYPE, 0x55, काष्ठा acrn_pcidev)
#घोषणा ACRN_IOCTL_DEASSIGN_PCIDEV	\
	_IOW(ACRN_IOCTL_TYPE, 0x56, काष्ठा acrn_pcidev)

#घोषणा ACRN_IOCTL_PM_GET_CPU_STATE	\
	_IOWR(ACRN_IOCTL_TYPE, 0x60, __u64)

#घोषणा ACRN_IOCTL_IOEVENTFD		\
	_IOW(ACRN_IOCTL_TYPE, 0x70, काष्ठा acrn_ioeventfd)
#घोषणा ACRN_IOCTL_IRQFD		\
	_IOW(ACRN_IOCTL_TYPE, 0x71, काष्ठा acrn_irqfd)

#पूर्ण_अगर /* _UAPI_ACRN_H */
