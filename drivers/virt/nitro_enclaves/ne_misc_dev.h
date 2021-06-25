<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

#अगर_अघोषित _NE_MISC_DEV_H_
#घोषणा _NE_MISC_DEV_H_

#समावेश <linux/cpumask.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>

#समावेश "ne_pci_dev.h"

/**
 * काष्ठा ne_mem_region - Entry in the enclave user space memory regions list.
 * @mem_region_list_entry:	Entry in the list of enclave memory regions.
 * @memory_size:		Size of the user space memory region.
 * @nr_pages:			Number of pages that make up the memory region.
 * @pages:			Pages that make up the user space memory region.
 * @userspace_addr:		User space address of the memory region.
 */
काष्ठा ne_mem_region अणु
	काष्ठा list_head	mem_region_list_entry;
	u64			memory_size;
	अचिन्हित दीर्घ		nr_pages;
	काष्ठा page		**pages;
	u64			userspace_addr;
पूर्ण;

/**
 * काष्ठा ne_enclave - Per-enclave data used क्रम enclave lअगरeसमय management.
 * @enclave_info_mutex :	Mutex क्रम accessing this पूर्णांकernal state.
 * @enclave_list_entry :	Entry in the list of created enclaves.
 * @eventq:			Wait queue used क्रम out-of-band event notअगरications
 *				triggered from the PCI device event handler to
 *				the enclave process via the poll function.
 * @has_event:			Variable used to determine अगर the out-of-band event
 *				was triggered.
 * @max_mem_regions:		The maximum number of memory regions that can be
 *				handled by the hypervisor.
 * @mem_regions_list:		Enclave user space memory regions list.
 * @mem_size:			Enclave memory size.
 * @mm :			Enclave process असलtraction mm data काष्ठा.
 * @nr_mem_regions:		Number of memory regions associated with the enclave.
 * @nr_parent_vm_cores :	The size of the thपढ़ोs per core array. The
 *				total number of CPU cores available on the
 *				parent / primary VM.
 * @nr_thपढ़ोs_per_core:	The number of thपढ़ोs that a full CPU core has.
 * @nr_vcpus:			Number of vcpus associated with the enclave.
 * @numa_node:			NUMA node of the enclave memory and CPUs.
 * @slot_uid:			Slot unique id mapped to the enclave.
 * @state:			Enclave state, updated during enclave lअगरeसमय.
 * @thपढ़ोs_per_core:		Enclave full CPU cores array, indexed by core id,
 *				consisting of cpumasks with all their thपढ़ोs.
 *				Full CPU cores are taken from the NE CPU pool
 *				and are available to the enclave.
 * @vcpu_ids:			Cpumask of the vCPUs that are set क्रम the enclave.
 */
काष्ठा ne_enclave अणु
	काष्ठा mutex		enclave_info_mutex;
	काष्ठा list_head	enclave_list_entry;
	रुको_queue_head_t	eventq;
	bool			has_event;
	u64			max_mem_regions;
	काष्ठा list_head	mem_regions_list;
	u64			mem_size;
	काष्ठा mm_काष्ठा	*mm;
	अचिन्हित पूर्णांक		nr_mem_regions;
	अचिन्हित पूर्णांक		nr_parent_vm_cores;
	अचिन्हित पूर्णांक		nr_thपढ़ोs_per_core;
	अचिन्हित पूर्णांक		nr_vcpus;
	पूर्णांक			numa_node;
	u64			slot_uid;
	u16			state;
	cpumask_var_t		*thपढ़ोs_per_core;
	cpumask_var_t		vcpu_ids;
पूर्ण;

/**
 * क्रमागत ne_state - States available क्रम an enclave.
 * @NE_STATE_INIT:	The enclave has not been started yet.
 * @NE_STATE_RUNNING:	The enclave was started and is running as expected.
 * @NE_STATE_STOPPED:	The enclave निकासed without userspace पूर्णांकeraction.
 */
क्रमागत ne_state अणु
	NE_STATE_INIT		= 0,
	NE_STATE_RUNNING	= 2,
	NE_STATE_STOPPED	= U16_MAX,
पूर्ण;

/**
 * काष्ठा ne_devs - Data काष्ठाure to keep refs to the NE misc and PCI devices.
 * @ne_misc_dev:	Nitro Enclaves misc device.
 * @ne_pci_dev :	Nitro Enclaves PCI device.
 */
काष्ठा ne_devs अणु
	काष्ठा miscdevice	*ne_misc_dev;
	काष्ठा ne_pci_dev	*ne_pci_dev;
पूर्ण;

/* Nitro Enclaves (NE) data काष्ठाure क्रम keeping refs to the NE misc and PCI devices. */
बाह्य काष्ठा ne_devs ne_devs;

#पूर्ण_अगर /* _NE_MISC_DEV_H_ */
