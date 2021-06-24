<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

#अगर_अघोषित _NE_PCI_DEV_H_
#घोषणा _NE_PCI_DEV_H_

#समावेश <linux/atomic.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/रुको.h>

/**
 * DOC: Nitro Enclaves (NE) PCI device
 */

/**
 * PCI_DEVICE_ID_NE - Nitro Enclaves PCI device id.
 */
#घोषणा PCI_DEVICE_ID_NE	(0xe4c1)
/**
 * PCI_BAR_NE - Nitro Enclaves PCI device MMIO BAR.
 */
#घोषणा PCI_BAR_NE		(0x03)

/**
 * DOC: Device रेजिस्टरs in the NE PCI device MMIO BAR
 */

/**
 * NE_ENABLE - (1 byte) Register to notअगरy the device that the driver is using
 *	       it (Read/Write).
 */
#घोषणा NE_ENABLE		(0x0000)
#घोषणा NE_ENABLE_OFF		(0x00)
#घोषणा NE_ENABLE_ON		(0x01)

/**
 * NE_VERSION - (2 bytes) Register to select the device run-समय version
 *		(Read/Write).
 */
#घोषणा NE_VERSION		(0x0002)
#घोषणा NE_VERSION_MAX		(0x0001)

/**
 * NE_COMMAND - (4 bytes) Register to notअगरy the device what command was
 *		requested (Write-Only).
 */
#घोषणा NE_COMMAND		(0x0004)

/**
 * NE_EVTCNT - (4 bytes) Register to notअगरy the driver that a reply or a device
 *	       event is available (Read-Only):
 *	       - Lower half  - command reply counter
 *	       - Higher half - out-of-band device event counter
 */
#घोषणा NE_EVTCNT		(0x000c)
#घोषणा NE_EVTCNT_REPLY_SHIFT	(0)
#घोषणा NE_EVTCNT_REPLY_MASK	(0x0000ffff)
#घोषणा NE_EVTCNT_REPLY(cnt)	(((cnt) & NE_EVTCNT_REPLY_MASK) >> \
				NE_EVTCNT_REPLY_SHIFT)
#घोषणा NE_EVTCNT_EVENT_SHIFT	(16)
#घोषणा NE_EVTCNT_EVENT_MASK	(0xffff0000)
#घोषणा NE_EVTCNT_EVENT(cnt)	(((cnt) & NE_EVTCNT_EVENT_MASK) >> \
				NE_EVTCNT_EVENT_SHIFT)

/**
 * NE_SEND_DATA - (240 bytes) Buffer क्रम sending the command request payload
 *		  (Read/Write).
 */
#घोषणा NE_SEND_DATA		(0x0010)

/**
 * NE_RECV_DATA - (240 bytes) Buffer क्रम receiving the command reply payload
 *		  (Read-Only).
 */
#घोषणा NE_RECV_DATA		(0x0100)

/**
 * DOC: Device MMIO buffer sizes
 */

/**
 * NE_SEND_DATA_SIZE / NE_RECV_DATA_SIZE - 240 bytes क्रम send / recv buffer.
 */
#घोषणा NE_SEND_DATA_SIZE	(240)
#घोषणा NE_RECV_DATA_SIZE	(240)

/**
 * DOC: MSI-X पूर्णांकerrupt vectors
 */

/**
 * NE_VEC_REPLY - MSI-X vector used क्रम command reply notअगरication.
 */
#घोषणा NE_VEC_REPLY		(0)

/**
 * NE_VEC_EVENT - MSI-X vector used क्रम out-of-band events e.g. enclave crash.
 */
#घोषणा NE_VEC_EVENT		(1)

/**
 * क्रमागत ne_pci_dev_cmd_type - Device command types.
 * @INVALID_CMD:		Invalid command.
 * @ENCLAVE_START:		Start an enclave, after setting its resources.
 * @ENCLAVE_GET_SLOT:		Get the slot uid of an enclave.
 * @ENCLAVE_STOP:		Terminate an enclave.
 * @SLOT_ALLOC :		Allocate a slot क्रम an enclave.
 * @SLOT_FREE:			Free the slot allocated क्रम an enclave
 * @SLOT_ADD_MEM:		Add a memory region to an enclave slot.
 * @SLOT_ADD_VCPU:		Add a vCPU to an enclave slot.
 * @SLOT_COUNT :		Get the number of allocated slots.
 * @NEXT_SLOT:			Get the next slot in the list of allocated slots.
 * @SLOT_INFO:			Get the info क्रम a slot e.g. slot uid, vCPUs count.
 * @SLOT_ADD_BULK_VCPUS:	Add a number of vCPUs, not providing CPU ids.
 * @MAX_CMD:			A gatekeeper क्रम max possible command type.
 */
क्रमागत ne_pci_dev_cmd_type अणु
	INVALID_CMD		= 0,
	ENCLAVE_START		= 1,
	ENCLAVE_GET_SLOT	= 2,
	ENCLAVE_STOP		= 3,
	SLOT_ALLOC		= 4,
	SLOT_FREE		= 5,
	SLOT_ADD_MEM		= 6,
	SLOT_ADD_VCPU		= 7,
	SLOT_COUNT		= 8,
	NEXT_SLOT		= 9,
	SLOT_INFO		= 10,
	SLOT_ADD_BULK_VCPUS	= 11,
	MAX_CMD,
पूर्ण;

/**
 * DOC: Device commands - payload काष्ठाure क्रम requests and replies.
 */

/**
 * काष्ठा enclave_start_req - ENCLAVE_START request.
 * @slot_uid:		Slot unique id mapped to the enclave to start.
 * @enclave_cid:	Context ID (CID) क्रम the enclave vsock device.
 *			If 0, CID is स्वतःgenerated.
 * @flags:		Flags क्रम the enclave to start with (e.g. debug mode).
 */
काष्ठा enclave_start_req अणु
	u64	slot_uid;
	u64	enclave_cid;
	u64	flags;
पूर्ण;

/**
 * काष्ठा enclave_get_slot_req - ENCLAVE_GET_SLOT request.
 * @enclave_cid:	Context ID (CID) क्रम the enclave vsock device.
 */
काष्ठा enclave_get_slot_req अणु
	u64	enclave_cid;
पूर्ण;

/**
 * काष्ठा enclave_stop_req - ENCLAVE_STOP request.
 * @slot_uid:	Slot unique id mapped to the enclave to stop.
 */
काष्ठा enclave_stop_req अणु
	u64	slot_uid;
पूर्ण;

/**
 * काष्ठा slot_alloc_req - SLOT_ALLOC request.
 * @unused:	In order to aव्योम weird माप edge हालs.
 */
काष्ठा slot_alloc_req अणु
	u8	unused;
पूर्ण;

/**
 * काष्ठा slot_मुक्त_req - SLOT_FREE request.
 * @slot_uid:	Slot unique id mapped to the slot to मुक्त.
 */
काष्ठा slot_मुक्त_req अणु
	u64	slot_uid;
पूर्ण;

/* TODO: Add flags field to the request to add memory region. */
/**
 * काष्ठा slot_add_mem_req - SLOT_ADD_MEM request.
 * @slot_uid:	Slot unique id mapped to the slot to add the memory region to.
 * @paddr:	Physical address of the memory region to add to the slot.
 * @size:	Memory size, in bytes, of the memory region to add to the slot.
 */
काष्ठा slot_add_mem_req अणु
	u64	slot_uid;
	u64	paddr;
	u64	size;
पूर्ण;

/**
 * काष्ठा slot_add_vcpu_req - SLOT_ADD_VCPU request.
 * @slot_uid:	Slot unique id mapped to the slot to add the vCPU to.
 * @vcpu_id:	vCPU ID of the CPU to add to the enclave.
 * @padding:	Padding क्रम the overall data काष्ठाure.
 */
काष्ठा slot_add_vcpu_req अणु
	u64	slot_uid;
	u32	vcpu_id;
	u8	padding[4];
पूर्ण;

/**
 * काष्ठा slot_count_req - SLOT_COUNT request.
 * @unused:	In order to aव्योम weird माप edge हालs.
 */
काष्ठा slot_count_req अणु
	u8	unused;
पूर्ण;

/**
 * काष्ठा next_slot_req - NEXT_SLOT request.
 * @slot_uid:	Slot unique id of the next slot in the iteration.
 */
काष्ठा next_slot_req अणु
	u64	slot_uid;
पूर्ण;

/**
 * काष्ठा slot_info_req - SLOT_INFO request.
 * @slot_uid:	Slot unique id mapped to the slot to get inक्रमmation about.
 */
काष्ठा slot_info_req अणु
	u64	slot_uid;
पूर्ण;

/**
 * काष्ठा slot_add_bulk_vcpus_req - SLOT_ADD_BULK_VCPUS request.
 * @slot_uid:	Slot unique id mapped to the slot to add vCPUs to.
 * @nr_vcpus:	Number of vCPUs to add to the slot.
 */
काष्ठा slot_add_bulk_vcpus_req अणु
	u64	slot_uid;
	u64	nr_vcpus;
पूर्ण;

/**
 * काष्ठा ne_pci_dev_cmd_reply - NE PCI device command reply.
 * @rc :		Return code of the logic that processed the request.
 * @padding0:		Padding क्रम the overall data काष्ठाure.
 * @slot_uid:		Valid क्रम all commands except SLOT_COUNT.
 * @enclave_cid:	Valid क्रम ENCLAVE_START command.
 * @slot_count :	Valid क्रम SLOT_COUNT command.
 * @mem_regions:	Valid क्रम SLOT_ALLOC and SLOT_INFO commands.
 * @mem_size:		Valid क्रम SLOT_INFO command.
 * @nr_vcpus:		Valid क्रम SLOT_INFO command.
 * @flags:		Valid क्रम SLOT_INFO command.
 * @state:		Valid क्रम SLOT_INFO command.
 * @padding1:		Padding क्रम the overall data काष्ठाure.
 */
काष्ठा ne_pci_dev_cmd_reply अणु
	s32	rc;
	u8	padding0[4];
	u64	slot_uid;
	u64	enclave_cid;
	u64	slot_count;
	u64	mem_regions;
	u64	mem_size;
	u64	nr_vcpus;
	u64	flags;
	u16	state;
	u8	padding1[6];
पूर्ण;

/**
 * काष्ठा ne_pci_dev - Nitro Enclaves (NE) PCI device.
 * @cmd_reply_avail:		Variable set अगर a reply has been sent by the
 *				PCI device.
 * @cmd_reply_रुको_q:		Wait queue क्रम handling command reply from the
 *				PCI device.
 * @enclaves_list:		List of the enclaves managed by the PCI device.
 * @enclaves_list_mutex:	Mutex क्रम accessing the list of enclaves.
 * @event_wq:			Work queue क्रम handling out-of-band events
 *				triggered by the Nitro Hypervisor which require
 *				enclave state scanning and propagation to the
 *				enclave process.
 * @iomem_base :		MMIO region of the PCI device.
 * @notअगरy_work:		Work item क्रम every received out-of-band event.
 * @pci_dev_mutex:		Mutex क्रम accessing the PCI device MMIO space.
 * @pdev:			PCI device data काष्ठाure.
 */
काष्ठा ne_pci_dev अणु
	atomic_t		cmd_reply_avail;
	रुको_queue_head_t	cmd_reply_रुको_q;
	काष्ठा list_head	enclaves_list;
	काष्ठा mutex		enclaves_list_mutex;
	काष्ठा workqueue_काष्ठा	*event_wq;
	व्योम __iomem		*iomem_base;
	काष्ठा work_काष्ठा	notअगरy_work;
	काष्ठा mutex		pci_dev_mutex;
	काष्ठा pci_dev		*pdev;
पूर्ण;

/**
 * ne_करो_request() - Submit command request to the PCI device based on the command
 *		     type and retrieve the associated reply.
 * @pdev:		PCI device to send the command to and receive the reply from.
 * @cmd_type:		Command type of the request sent to the PCI device.
 * @cmd_request:	Command request payload.
 * @cmd_request_size:	Size of the command request payload.
 * @cmd_reply:		Command reply payload.
 * @cmd_reply_size:	Size of the command reply payload.
 *
 * Context: Process context. This function uses the ne_pci_dev mutex to handle
 *	    one command at a समय.
 * Return:
 * * 0 on success.
 * * Negative वापस value on failure.
 */
पूर्णांक ne_करो_request(काष्ठा pci_dev *pdev, क्रमागत ne_pci_dev_cmd_type cmd_type,
		  व्योम *cmd_request, माप_प्रकार cmd_request_size,
		  काष्ठा ne_pci_dev_cmd_reply *cmd_reply,
		  माप_प्रकार cmd_reply_size);

/* Nitro Enclaves (NE) PCI device driver */
बाह्य काष्ठा pci_driver ne_pci_driver;

#पूर्ण_अगर /* _NE_PCI_DEV_H_ */
