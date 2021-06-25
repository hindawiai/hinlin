<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A sample program to run a User VM on the ACRN hypervisor
 *
 * This sample runs in a Service VM, which is a privileged VM of ACRN.
 * CONFIG_ACRN_HSM need to be enabled in the Service VM.
 *
 * Guest VM code in guest16.s will be executed after the VM launched.
 *
 * Copyright (C) 2020 Intel Corporation. All rights reserved.
 */
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <दो_स्मृति.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <sys/ioctl.h>
#समावेश <linux/acrn.h>

#घोषणा GUEST_MEMORY_SIZE	(1024*1024)
व्योम *guest_memory;

बाह्य स्थिर अचिन्हित अक्षर guest16[], guest16_end[];
अटल अक्षर io_request_page[4096] __attribute__((aligned(4096)));
अटल काष्ठा acrn_io_request *io_req_buf = (काष्ठा acrn_io_request *)io_request_page;

__u16 vcpu_num;
__u16 vmid;
/* POST_STANDARD_VM_UUID1, refer to https://github.com/projectacrn/acrn-hypervisor/blob/master/hypervisor/include/common/vm_uuids.h */
guid_t vm_uuid = GUID_INIT(0x385479d2, 0xd625, 0xe811, 0x86, 0x4e, 0xcb, 0x7a, 0x18, 0xb3, 0x46, 0x43);

पूर्णांक hsm_fd;
पूर्णांक is_running = 1;

व्योम vm_निकास(पूर्णांक sig)
अणु
	sig = sig;

	is_running = 0;
	ioctl(hsm_fd, ACRN_IOCTL_PAUSE_VM, vmid);
	ioctl(hsm_fd, ACRN_IOCTL_DESTROY_IOREQ_CLIENT, 0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक vcpu_id, ret;
	काष्ठा acrn_vm_creation create_vm = अणु0पूर्ण;
	काष्ठा acrn_vm_memmap ram_map = अणु0पूर्ण;
	काष्ठा acrn_vcpu_regs regs;
	काष्ठा acrn_io_request *io_req;
	काष्ठा acrn_ioreq_notअगरy __attribute__((aligned(8))) notअगरy;

	argc = argc;
	argv = argv;

	guest_memory = memalign(4096, GUEST_MEMORY_SIZE);
	अगर (!guest_memory) अणु
		म_लिखो("No enough memory!\n");
		वापस -1;
	पूर्ण
	hsm_fd = खोलो("/dev/acrn_hsm", O_RDWR|O_CLOEXEC);

	स_नकल(&create_vm.uuid, &vm_uuid, 16);
	create_vm.ioreq_buf = (__u64)io_req_buf;
	ret = ioctl(hsm_fd, ACRN_IOCTL_CREATE_VM, &create_vm);
	म_लिखो("Created VM! [%d]\n", ret);
	vcpu_num = create_vm.vcpu_num;
	vmid = create_vm.vmid;

	/* setup guest memory */
	ram_map.type = ACRN_MEMMAP_RAM;
	ram_map.vma_base = (__u64)guest_memory;
	ram_map.len = GUEST_MEMORY_SIZE;
	ram_map.user_vm_pa = 0;
	ram_map.attr = ACRN_MEM_ACCESS_RWX;
	ret = ioctl(hsm_fd, ACRN_IOCTL_SET_MEMSEG, &ram_map);
	म_लिखो("Set up VM memory! [%d]\n", ret);

	स_नकल(guest_memory, guest16, guest16_end-guest16);

	/* setup vcpu रेजिस्टरs */
	स_रखो(&regs, 0, माप(regs));
	regs.vcpu_id = 0;
	regs.vcpu_regs.rip = 0;

	/* CR0_ET | CR0_NE */
	regs.vcpu_regs.cr0 = 0x30U;
	regs.vcpu_regs.cs_ar = 0x009FU;
	regs.vcpu_regs.cs_sel = 0xF000U;
	regs.vcpu_regs.cs_limit = 0xFFFFU;
	regs.vcpu_regs.cs_base = 0 & 0xFFFF0000UL;
	regs.vcpu_regs.rip = 0 & 0xFFFFUL;

	ret = ioctl(hsm_fd, ACRN_IOCTL_SET_VCPU_REGS, &regs);
	म_लिखो("Set up VM BSP registers! [%d]\n", ret);

	/* create an ioreq client क्रम this VM */
	ret = ioctl(hsm_fd, ACRN_IOCTL_CREATE_IOREQ_CLIENT, 0);
	म_लिखो("Created IO request client! [%d]\n", ret);

	/* run vm */
	ret = ioctl(hsm_fd, ACRN_IOCTL_START_VM, vmid);
	म_लिखो("Start VM! [%d]\n", ret);

	संकेत(संक_विघ्न, vm_निकास);
	जबतक (is_running) अणु
		ret = ioctl(hsm_fd, ACRN_IOCTL_ATTACH_IOREQ_CLIENT, 0);

		क्रम (vcpu_id = 0; vcpu_id < vcpu_num; vcpu_id++) अणु
			io_req = &io_req_buf[vcpu_id];
			अगर ((__sync_add_and_fetch(&io_req->processed, 0) == ACRN_IOREQ_STATE_PROCESSING)
					&& (!io_req->kernel_handled))
				अगर (io_req->type == ACRN_IOREQ_TYPE_PORTIO) अणु
					पूर्णांक bytes, port, in;

					port = io_req->reqs.pio_request.address;
					bytes = io_req->reqs.pio_request.size;
					in = (io_req->reqs.pio_request.direction == ACRN_IOREQ_सूची_READ);
					म_लिखो("Guest VM %s PIO[%x] with size[%x]\n", in ? "read" : "write", port, bytes);

					notअगरy.vmid = vmid;
					notअगरy.vcpu = vcpu_id;
					ioctl(hsm_fd, ACRN_IOCTL_NOTIFY_REQUEST_FINISH, &notअगरy);
				पूर्ण
		पूर्ण
	पूर्ण

	ret = ioctl(hsm_fd, ACRN_IOCTL_DESTROY_VM, शून्य);
	म_लिखो("Destroy VM! [%d]\n", ret);
	बंद(hsm_fd);
	मुक्त(guest_memory);
	वापस 0;
पूर्ण
