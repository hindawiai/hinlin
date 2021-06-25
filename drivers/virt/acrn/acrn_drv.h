<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ACRN_HSM_DRV_H
#घोषणा __ACRN_HSM_DRV_H

#समावेश <linux/acrn.h>
#समावेश <linux/dev_prपूर्णांकk.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/types.h>

#समावेश "hypercall.h"

बाह्य काष्ठा miscdevice acrn_dev;

#घोषणा ACRN_NAME_LEN		16
#घोषणा ACRN_MEM_MAPPING_MAX	256

#घोषणा ACRN_MEM_REGION_ADD	0
#घोषणा ACRN_MEM_REGION_DEL	2

काष्ठा acrn_vm;
काष्ठा acrn_ioreq_client;

/**
 * काष्ठा vm_memory_region_op - Hypervisor memory operation
 * @type:		Operation type (ACRN_MEM_REGION_*)
 * @attr:		Memory attribute (ACRN_MEM_TYPE_* | ACRN_MEM_ACCESS_*)
 * @user_vm_pa:		Physical address of User VM to be mapped.
 * @service_vm_pa:	Physical address of Service VM to be mapped.
 * @size:		Size of this region.
 *
 * Structure containing needed inक्रमmation that is provided to ACRN Hypervisor
 * to manage the EPT mappings of a single memory region of the User VM. Several
 * &काष्ठा vm_memory_region_op can be batched to ACRN Hypervisor, see &काष्ठा
 * vm_memory_region_batch.
 */
काष्ठा vm_memory_region_op अणु
	u32	type;
	u32	attr;
	u64	user_vm_pa;
	u64	service_vm_pa;
	u64	size;
पूर्ण;

/**
 * काष्ठा vm_memory_region_batch - A batch of vm_memory_region_op.
 * @vmid:		A User VM ID.
 * @reserved:		Reserved.
 * @regions_num:	The number of vm_memory_region_op.
 * @regions_gpa:	Physical address of a vm_memory_region_op array.
 *
 * HC_VM_SET_MEMORY_REGIONS uses this काष्ठाure to manage EPT mappings of
 * multiple memory regions of a User VM. A &काष्ठा vm_memory_region_batch
 * contains multiple &काष्ठा vm_memory_region_op क्रम batch processing in the
 * ACRN Hypervisor.
 */
काष्ठा vm_memory_region_batch अणु
	u16	vmid;
	u16	reserved[3];
	u32	regions_num;
	u64	regions_gpa;
पूर्ण;

/**
 * काष्ठा vm_memory_mapping - Memory map between a User VM and the Service VM
 * @pages:		Pages in Service VM kernel.
 * @npages:		Number of pages.
 * @service_vm_va:	Virtual address in Service VM kernel.
 * @user_vm_pa:		Physical address in User VM.
 * @size:		Size of this memory region.
 *
 * HSM मुख्यtains memory mappings between a User VM GPA and the Service VM
 * kernel VA क्रम accelerating the User VM GPA translation.
 */
काष्ठा vm_memory_mapping अणु
	काष्ठा page	**pages;
	पूर्णांक		npages;
	व्योम		*service_vm_va;
	u64		user_vm_pa;
	माप_प्रकार		size;
पूर्ण;

/**
 * काष्ठा acrn_ioreq_buffer - Data क्रम setting the ioreq buffer of User VM
 * @ioreq_buf:	The GPA of the IO request shared buffer of a VM
 *
 * The parameter क्रम the HC_SET_IOREQ_BUFFER hypercall used to set up
 * the shared I/O request buffer between Service VM and ACRN hypervisor.
 */
काष्ठा acrn_ioreq_buffer अणु
	u64	ioreq_buf;
पूर्ण;

काष्ठा acrn_ioreq_range अणु
	काष्ठा list_head	list;
	u32			type;
	u64			start;
	u64			end;
पूर्ण;

#घोषणा ACRN_IOREQ_CLIENT_DESTROYING	0U
प्रकार	पूर्णांक (*ioreq_handler_t)(काष्ठा acrn_ioreq_client *client,
			       काष्ठा acrn_io_request *req);
/**
 * काष्ठा acrn_ioreq_client - Structure of I/O client.
 * @name:	Client name
 * @vm:		The VM that the client beदीर्घs to
 * @list:	List node क्रम this acrn_ioreq_client
 * @is_शेष:	If this client is the शेष one
 * @flags:	Flags (ACRN_IOREQ_CLIENT_*)
 * @range_list:	I/O ranges
 * @range_lock:	Lock to protect range_list
 * @ioreqs_map:	The pending I/O requests biपंचांगap.
 * @handler:	I/O requests handler of this client
 * @thपढ़ो:	The thपढ़ो which executes the handler
 * @wq:		The रुको queue क्रम the handler thपढ़ो parking
 * @priv:	Data क्रम the thपढ़ो
 */
काष्ठा acrn_ioreq_client अणु
	अक्षर			name[ACRN_NAME_LEN];
	काष्ठा acrn_vm		*vm;
	काष्ठा list_head	list;
	bool			is_शेष;
	अचिन्हित दीर्घ		flags;
	काष्ठा list_head	range_list;
	rwlock_t		range_lock;
	DECLARE_BITMAP(ioreqs_map, ACRN_IO_REQUEST_MAX);
	ioreq_handler_t		handler;
	काष्ठा task_काष्ठा	*thपढ़ो;
	रुको_queue_head_t	wq;
	व्योम			*priv;
पूर्ण;

#घोषणा ACRN_INVALID_VMID (0xffffU)

#घोषणा ACRN_VM_FLAG_DESTROYED		0U
#घोषणा ACRN_VM_FLAG_CLEARING_IOREQ	1U
बाह्य काष्ठा list_head acrn_vm_list;
बाह्य rwlock_t acrn_vm_list_lock;
/**
 * काष्ठा acrn_vm - Properties of ACRN User VM.
 * @list:			Entry within global list of all VMs.
 * @vmid:			User VM ID.
 * @vcpu_num:			Number of भव CPUs in the VM.
 * @flags:			Flags (ACRN_VM_FLAG_*) of the VM. This is VM
 *				flag management in HSM which is dअगरferent
 *				from the &acrn_vm_creation.vm_flag.
 * @regions_mapping_lock:	Lock to protect &acrn_vm.regions_mapping and
 *				&acrn_vm.regions_mapping_count.
 * @regions_mapping:		Memory mappings of this VM.
 * @regions_mapping_count:	Number of memory mapping of this VM.
 * @ioreq_clients_lock:		Lock to protect ioreq_clients and शेष_client
 * @ioreq_clients:		The I/O request clients list of this VM
 * @शेष_client:		The शेष I/O request client
 * @ioreq_buf:			I/O request shared buffer
 * @ioreq_page:			The page of the I/O request shared buffer
 * @pci_conf_addr:		Address of a PCI configuration access emulation
 * @monitor_page:		Page of पूर्णांकerrupt statistics of User VM
 * @ioeventfds_lock:		Lock to protect ioeventfds list
 * @ioeventfds:			List to link all hsm_ioeventfd
 * @ioeventfd_client:		I/O client क्रम ioeventfds of the VM
 * @irqfds_lock:		Lock to protect irqfds list
 * @irqfds:			List to link all hsm_irqfd
 * @irqfd_wq:			Workqueue क्रम irqfd async shutकरोwn
 */
काष्ठा acrn_vm अणु
	काष्ठा list_head		list;
	u16				vmid;
	पूर्णांक				vcpu_num;
	अचिन्हित दीर्घ			flags;
	काष्ठा mutex			regions_mapping_lock;
	काष्ठा vm_memory_mapping	regions_mapping[ACRN_MEM_MAPPING_MAX];
	पूर्णांक				regions_mapping_count;
	spinlock_t			ioreq_clients_lock;
	काष्ठा list_head		ioreq_clients;
	काष्ठा acrn_ioreq_client	*शेष_client;
	काष्ठा acrn_io_request_buffer	*ioreq_buf;
	काष्ठा page			*ioreq_page;
	u32				pci_conf_addr;
	काष्ठा page			*monitor_page;
	काष्ठा mutex			ioeventfds_lock;
	काष्ठा list_head		ioeventfds;
	काष्ठा acrn_ioreq_client	*ioeventfd_client;
	काष्ठा mutex			irqfds_lock;
	काष्ठा list_head		irqfds;
	काष्ठा workqueue_काष्ठा		*irqfd_wq;
पूर्ण;

काष्ठा acrn_vm *acrn_vm_create(काष्ठा acrn_vm *vm,
			       काष्ठा acrn_vm_creation *vm_param);
पूर्णांक acrn_vm_destroy(काष्ठा acrn_vm *vm);
पूर्णांक acrn_mm_region_add(काष्ठा acrn_vm *vm, u64 user_gpa, u64 service_gpa,
		       u64 size, u32 mem_type, u32 mem_access_right);
पूर्णांक acrn_mm_region_del(काष्ठा acrn_vm *vm, u64 user_gpa, u64 size);
पूर्णांक acrn_vm_memseg_map(काष्ठा acrn_vm *vm, काष्ठा acrn_vm_memmap *memmap);
पूर्णांक acrn_vm_memseg_unmap(काष्ठा acrn_vm *vm, काष्ठा acrn_vm_memmap *memmap);
पूर्णांक acrn_vm_ram_map(काष्ठा acrn_vm *vm, काष्ठा acrn_vm_memmap *memmap);
व्योम acrn_vm_all_ram_unmap(काष्ठा acrn_vm *vm);

पूर्णांक acrn_ioreq_init(काष्ठा acrn_vm *vm, u64 buf_vma);
व्योम acrn_ioreq_deinit(काष्ठा acrn_vm *vm);
पूर्णांक acrn_ioreq_पूर्णांकr_setup(व्योम);
व्योम acrn_ioreq_पूर्णांकr_हटाओ(व्योम);
व्योम acrn_ioreq_request_clear(काष्ठा acrn_vm *vm);
पूर्णांक acrn_ioreq_client_रुको(काष्ठा acrn_ioreq_client *client);
पूर्णांक acrn_ioreq_request_शेष_complete(काष्ठा acrn_vm *vm, u16 vcpu);
काष्ठा acrn_ioreq_client *acrn_ioreq_client_create(काष्ठा acrn_vm *vm,
						   ioreq_handler_t handler,
						   व्योम *data, bool is_शेष,
						   स्थिर अक्षर *name);
व्योम acrn_ioreq_client_destroy(काष्ठा acrn_ioreq_client *client);
पूर्णांक acrn_ioreq_range_add(काष्ठा acrn_ioreq_client *client,
			 u32 type, u64 start, u64 end);
व्योम acrn_ioreq_range_del(काष्ठा acrn_ioreq_client *client,
			  u32 type, u64 start, u64 end);

पूर्णांक acrn_msi_inject(काष्ठा acrn_vm *vm, u64 msi_addr, u64 msi_data);

पूर्णांक acrn_ioeventfd_init(काष्ठा acrn_vm *vm);
पूर्णांक acrn_ioeventfd_config(काष्ठा acrn_vm *vm, काष्ठा acrn_ioeventfd *args);
व्योम acrn_ioeventfd_deinit(काष्ठा acrn_vm *vm);

पूर्णांक acrn_irqfd_init(काष्ठा acrn_vm *vm);
पूर्णांक acrn_irqfd_config(काष्ठा acrn_vm *vm, काष्ठा acrn_irqfd *args);
व्योम acrn_irqfd_deinit(काष्ठा acrn_vm *vm);

#पूर्ण_अगर /* __ACRN_HSM_DRV_H */
