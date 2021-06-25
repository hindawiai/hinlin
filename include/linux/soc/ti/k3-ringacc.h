<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * K3 Ring Accelerator (RA) subप्रणाली पूर्णांकerface
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 */

#अगर_अघोषित __SOC_TI_K3_RINGACC_API_H_
#घोषणा __SOC_TI_K3_RINGACC_API_H_

#समावेश <linux/types.h>

काष्ठा device_node;

/**
 * क्रमागत k3_ring_mode - &काष्ठा k3_ring_cfg mode
 *
 * RA ring operational modes
 *
 * @K3_RINGACC_RING_MODE_RING: Exposed Ring mode क्रम SW direct access
 * @K3_RINGACC_RING_MODE_MESSAGE: Messaging mode. Messaging mode requires
 *	that all accesses to the queue must go through this IP so that all
 *	accesses to the memory are controlled and ordered. This IP then
 *	controls the entire state of the queue, and SW has no directly control,
 *	such as through करोorbells and cannot access the storage memory directly.
 *	This is particularly useful when more than one SW or HW entity can be
 *	the producer and/or consumer at the same समय
 * @K3_RINGACC_RING_MODE_CREDENTIALS: Credentials mode is message mode plus
 *	stores credentials with each message, requiring the element size to be
 *	द्विगुनd to fit the credentials. Any exposed memory should be रक्षित
 *	by a firewall from unwanted access
 */
क्रमागत k3_ring_mode अणु
	K3_RINGACC_RING_MODE_RING = 0,
	K3_RINGACC_RING_MODE_MESSAGE,
	K3_RINGACC_RING_MODE_CREDENTIALS,
	K3_RINGACC_RING_MODE_INVALID
पूर्ण;

/**
 * क्रमागत k3_ring_size - &काष्ठा k3_ring_cfg elm_size
 *
 * RA ring element's sizes in bytes.
 */
क्रमागत k3_ring_size अणु
	K3_RINGACC_RING_ELSIZE_4 = 0,
	K3_RINGACC_RING_ELSIZE_8,
	K3_RINGACC_RING_ELSIZE_16,
	K3_RINGACC_RING_ELSIZE_32,
	K3_RINGACC_RING_ELSIZE_64,
	K3_RINGACC_RING_ELSIZE_128,
	K3_RINGACC_RING_ELSIZE_256,
	K3_RINGACC_RING_ELSIZE_INVALID
पूर्ण;

काष्ठा k3_ringacc;
काष्ठा k3_ring;

/**
 * क्रमागत k3_ring_cfg - RA ring configuration काष्ठाure
 *
 * @size: Ring size, number of elements
 * @elm_size: Ring element size
 * @mode: Ring operational mode
 * @flags: Ring configuration flags. Possible values:
 *	 @K3_RINGACC_RING_SHARED: when set allows to request the same ring
 *	 few बार. It's usable when the same ring is used as Free Host PD ring
 *	 क्रम dअगरferent flows, क्रम example.
 *	 Note: Locking should be करोne by consumer अगर required
 * @dma_dev: Master device which is using and accessing to the ring
 *	memory when the mode is K3_RINGACC_RING_MODE_RING. Memory allocations
 *	should be करोne using this device.
 * @asel: Address Space Select value क्रम physical addresses
 */
काष्ठा k3_ring_cfg अणु
	u32 size;
	क्रमागत k3_ring_size elm_size;
	क्रमागत k3_ring_mode mode;
#घोषणा K3_RINGACC_RING_SHARED BIT(1)
	u32 flags;

	काष्ठा device *dma_dev;
	u32 asel;
पूर्ण;

#घोषणा K3_RINGACC_RING_ID_ANY (-1)

/**
 * of_k3_ringacc_get_by_phandle - find a RA by phandle property
 * @np: device node
 * @propname: property name containing phandle on RA node
 *
 * Returns poपूर्णांकer on the RA - काष्ठा k3_ringacc
 * or -ENODEV अगर not found,
 * or -EPROBE_DEFER अगर not yet रेजिस्टरed
 */
काष्ठा k3_ringacc *of_k3_ringacc_get_by_phandle(काष्ठा device_node *np,
						स्थिर अक्षर *property);

#घोषणा K3_RINGACC_RING_USE_PROXY BIT(1)

/**
 * k3_ringacc_request_ring - request ring from ringacc
 * @ringacc: poपूर्णांकer on ringacc
 * @id: ring id or K3_RINGACC_RING_ID_ANY क्रम any general purpose ring
 * @flags:
 *	@K3_RINGACC_RING_USE_PROXY: अगर set - proxy will be allocated and
 *		used to access ring memory. Sopported only क्रम rings in
 *		Message/Credentials/Queue mode.
 *
 * Returns poपूर्णांकer on the Ring - काष्ठा k3_ring
 * or शून्य in हाल of failure.
 */
काष्ठा k3_ring *k3_ringacc_request_ring(काष्ठा k3_ringacc *ringacc,
					पूर्णांक id, u32 flags);

पूर्णांक k3_ringacc_request_rings_pair(काष्ठा k3_ringacc *ringacc,
				  पूर्णांक fwd_id, पूर्णांक compl_id,
				  काष्ठा k3_ring **fwd_ring,
				  काष्ठा k3_ring **compl_ring);
/**
 * k3_ringacc_ring_reset - ring reset
 * @ring: poपूर्णांकer on Ring
 *
 * Resets ring पूर्णांकernal state ((hw)occ, (hw)idx).
 */
व्योम k3_ringacc_ring_reset(काष्ठा k3_ring *ring);
/**
 * k3_ringacc_ring_reset - ring reset क्रम DMA rings
 * @ring: poपूर्णांकer on Ring
 *
 * Resets ring पूर्णांकernal state ((hw)occ, (hw)idx). Should be used क्रम rings
 * which are पढ़ो by K3 UDMA, like TX or Free Host PD rings.
 */
व्योम k3_ringacc_ring_reset_dma(काष्ठा k3_ring *ring, u32 occ);

/**
 * k3_ringacc_ring_मुक्त - ring मुक्त
 * @ring: poपूर्णांकer on Ring
 *
 * Resets ring and मुक्त all alocated resources.
 */
पूर्णांक k3_ringacc_ring_मुक्त(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_get_ring_id - Get the Ring ID
 * @ring: poपूर्णांकer on ring
 *
 * Returns the Ring ID
 */
u32 k3_ringacc_get_ring_id(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_get_ring_irq_num - Get the irq number क्रम the ring
 * @ring: poपूर्णांकer on ring
 *
 * Returns the पूर्णांकerrupt number which can be used to request the पूर्णांकerrupt
 */
पूर्णांक k3_ringacc_get_ring_irq_num(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_ring_cfg - ring configure
 * @ring: poपूर्णांकer on ring
 * @cfg: Ring configuration parameters (see &काष्ठा k3_ring_cfg)
 *
 * Configures ring, including ring memory allocation.
 * Returns 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक k3_ringacc_ring_cfg(काष्ठा k3_ring *ring, काष्ठा k3_ring_cfg *cfg);

/**
 * k3_ringacc_ring_get_size - get ring size
 * @ring: poपूर्णांकer on ring
 *
 * Returns ring size in number of elements.
 */
u32 k3_ringacc_ring_get_size(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_ring_get_मुक्त - get मुक्त elements
 * @ring: poपूर्णांकer on ring
 *
 * Returns number of मुक्त elements in the ring.
 */
u32 k3_ringacc_ring_get_मुक्त(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_ring_get_occ - get ring occupancy
 * @ring: poपूर्णांकer on ring
 *
 * Returns total number of valid entries on the ring
 */
u32 k3_ringacc_ring_get_occ(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_ring_is_full - checks अगर ring is full
 * @ring: poपूर्णांकer on ring
 *
 * Returns true अगर the ring is full
 */
u32 k3_ringacc_ring_is_full(काष्ठा k3_ring *ring);

/**
 * k3_ringacc_ring_push - push element to the ring tail
 * @ring: poपूर्णांकer on ring
 * @elem: poपूर्णांकer on ring element buffer
 *
 * Push one ring element to the ring tail. Size of the ring element is
 * determined by ring configuration &काष्ठा k3_ring_cfg elm_size.
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक k3_ringacc_ring_push(काष्ठा k3_ring *ring, व्योम *elem);

/**
 * k3_ringacc_ring_pop - pop element from the ring head
 * @ring: poपूर्णांकer on ring
 * @elem: poपूर्णांकer on ring element buffer
 *
 * Push one ring element from the ring head. Size of the ring element is
 * determined by ring configuration &काष्ठा k3_ring_cfg elm_size..
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक k3_ringacc_ring_pop(काष्ठा k3_ring *ring, व्योम *elem);

/**
 * k3_ringacc_ring_push_head - push element to the ring head
 * @ring: poपूर्णांकer on ring
 * @elem: poपूर्णांकer on ring element buffer
 *
 * Push one ring element to the ring head. Size of the ring element is
 * determined by ring configuration &काष्ठा k3_ring_cfg elm_size.
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 * Not Supported by ring modes: K3_RINGACC_RING_MODE_RING
 */
पूर्णांक k3_ringacc_ring_push_head(काष्ठा k3_ring *ring, व्योम *elem);

/**
 * k3_ringacc_ring_pop_tail - pop element from the ring tail
 * @ring: poपूर्णांकer on ring
 * @elem: poपूर्णांकer on ring element buffer
 *
 * Push one ring element from the ring tail. Size of the ring element is
 * determined by ring configuration &काष्ठा k3_ring_cfg elm_size.
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 * Not Supported by ring modes: K3_RINGACC_RING_MODE_RING
 */
पूर्णांक k3_ringacc_ring_pop_tail(काष्ठा k3_ring *ring, व्योम *elem);

u32 k3_ringacc_get_tisci_dev_id(काष्ठा k3_ring *ring);

/* DMA ring support */
काष्ठा ti_sci_handle;

/**
 * काष्ठा काष्ठा k3_ringacc_init_data - Initialization data क्रम DMA rings
 */
काष्ठा k3_ringacc_init_data अणु
	स्थिर काष्ठा ti_sci_handle *tisci;
	u32 tisci_dev_id;
	u32 num_rings;
पूर्ण;

काष्ठा k3_ringacc *k3_ringacc_dmarings_init(काष्ठा platक्रमm_device *pdev,
					    काष्ठा k3_ringacc_init_data *data);

#पूर्ण_अगर /* __SOC_TI_K3_RINGACC_API_H_ */
