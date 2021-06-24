<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#अगर_अघोषित _MISC_OCXL_H_
#घोषणा _MISC_OCXL_H_

#समावेश <linux/pci.h>

/*
 * Opencapi drivers all need some common facilities, like parsing the
 * device configuration space, adding a Process Element to the Shared
 * Process Area, etc...
 *
 * The ocxl module provides a kernel API, to allow other drivers to
 * reuse common code. A bit like a in-kernel library.
 */

#घोषणा OCXL_AFU_NAME_SZ      (24+1)  /* add 1 क्रम शून्य termination */


काष्ठा ocxl_afu_config अणु
	u8 idx;
	पूर्णांक dvsec_afu_control_pos; /* offset of AFU control DVSEC */
	अक्षर name[OCXL_AFU_NAME_SZ];
	u8 version_major;
	u8 version_minor;
	u8 afuc_type;
	u8 afum_type;
	u8 profile;
	u8 global_mmio_bar;     /* global MMIO area */
	u64 global_mmio_offset;
	u32 global_mmio_size;
	u8 pp_mmio_bar;         /* per-process MMIO area */
	u64 pp_mmio_offset;
	u32 pp_mmio_stride;
	u64 lpc_mem_offset;
	u64 lpc_mem_size;
	u64 special_purpose_mem_offset;
	u64 special_purpose_mem_size;
	u8 pasid_supported_log;
	u16 actag_supported;
पूर्ण;

काष्ठा ocxl_fn_config अणु
	पूर्णांक dvsec_tl_pos;       /* offset of the Transaction Layer DVSEC */
	पूर्णांक dvsec_function_pos; /* offset of the Function DVSEC */
	पूर्णांक dvsec_afu_info_pos; /* offset of the AFU inक्रमmation DVSEC */
	s8 max_pasid_log;
	s8 max_afu_index;
पूर्ण;

क्रमागत ocxl_endian अणु
	OCXL_BIG_ENDIAN = 0,    /**< AFU data is big-endian */
	OCXL_LITTLE_ENDIAN = 1, /**< AFU data is little-endian */
	OCXL_HOST_ENDIAN = 2,   /**< AFU data is the same endianness as the host */
पूर्ण;

// These are opaque outside the ocxl driver
काष्ठा ocxl_afu;
काष्ठा ocxl_fn;
काष्ठा ocxl_context;

// Device detection & initialisation

/**
 * ocxl_function_खोलो() - Open an OpenCAPI function on an OpenCAPI device
 * @dev: The PCI device that contains the function
 *
 * Returns an opaque poपूर्णांकer to the function, or an error poपूर्णांकer (check with IS_ERR)
 */
काष्ठा ocxl_fn *ocxl_function_खोलो(काष्ठा pci_dev *dev);

/**
 * ocxl_function_afu_list() - Get the list of AFUs associated with a PCI function device
 * Returns a list of काष्ठा ocxl_afu *
 *
 * @fn: The OpenCAPI function containing the AFUs
 */
काष्ठा list_head *ocxl_function_afu_list(काष्ठा ocxl_fn *fn);

/**
 * ocxl_function_fetch_afu() - Fetch an AFU instance from an OpenCAPI function
 * @fn: The OpenCAPI function to get the AFU from
 * @afu_idx: The index of the AFU to get
 *
 * If successful, the AFU should be released with ocxl_afu_put()
 *
 * Returns a poपूर्णांकer to the AFU, or शून्य on error
 */
काष्ठा ocxl_afu *ocxl_function_fetch_afu(काष्ठा ocxl_fn *fn, u8 afu_idx);

/**
 * ocxl_afu_get() - Take a reference to an AFU
 * @afu: The AFU to increment the reference count on
 */
व्योम ocxl_afu_get(काष्ठा ocxl_afu *afu);

/**
 * ocxl_afu_put() - Release a reference to an AFU
 * @afu: The AFU to decrement the reference count on
 */
व्योम ocxl_afu_put(काष्ठा ocxl_afu *afu);


/**
 * ocxl_function_config() - Get the configuration inक्रमmation क्रम an OpenCAPI function
 * @fn: The OpenCAPI function to get the config क्रम
 *
 * Returns the function config, or शून्य on error
 */
स्थिर काष्ठा ocxl_fn_config *ocxl_function_config(काष्ठा ocxl_fn *fn);

/**
 * ocxl_function_बंद() - Close an OpenCAPI function
 * This will मुक्त any AFUs previously retrieved from the function, and
 * detach and associated contexts. The contexts must by मुक्तd by the caller.
 *
 * @fn: The OpenCAPI function to बंद
 *
 */
व्योम ocxl_function_बंद(काष्ठा ocxl_fn *fn);

// Context allocation

/**
 * ocxl_context_alloc() - Allocate an OpenCAPI context
 * @context: The OpenCAPI context to allocate, must be मुक्तd with ocxl_context_मुक्त
 * @afu: The AFU the context beदीर्घs to
 * @mapping: The mapping to unmap when the context is बंदd (may be शून्य)
 */
पूर्णांक ocxl_context_alloc(काष्ठा ocxl_context **context, काष्ठा ocxl_afu *afu,
			काष्ठा address_space *mapping);

/**
 * ocxl_context_मुक्त() - Free an OpenCAPI context
 * @ctx: The OpenCAPI context to मुक्त
 */
व्योम ocxl_context_मुक्त(काष्ठा ocxl_context *ctx);

/**
 * ocxl_context_attach() - Grant access to an MM to an OpenCAPI context
 * @ctx: The OpenCAPI context to attach
 * @amr: The value of the AMR रेजिस्टर to restrict access
 * @mm: The mm to attach to the context
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ocxl_context_attach(काष्ठा ocxl_context *ctx, u64 amr,
				काष्ठा mm_काष्ठा *mm);

/**
 * ocxl_context_detach() - Detach an MM from an OpenCAPI context
 * @ctx: The OpenCAPI context to attach
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ocxl_context_detach(काष्ठा ocxl_context *ctx);

// AFU IRQs

/**
 * ocxl_afu_irq_alloc() - Allocate an IRQ associated with an AFU context
 * @ctx: the AFU context
 * @irq_id: out, the IRQ ID
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ocxl_afu_irq_alloc(काष्ठा ocxl_context *ctx, पूर्णांक *irq_id);

/**
 * ocxl_afu_irq_मुक्त() - Frees an IRQ associated with an AFU context
 * @ctx: the AFU context
 * @irq_id: the IRQ ID
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ocxl_afu_irq_मुक्त(काष्ठा ocxl_context *ctx, पूर्णांक irq_id);

/**
 * ocxl_afu_irq_get_addr() - Gets the address of the trigger page क्रम an IRQ
 * This can then be provided to an AFU which will ग_लिखो to that
 * page to trigger the IRQ.
 * @ctx: The AFU context that the IRQ is associated with
 * @irq_id: The IRQ ID
 *
 * वापसs the trigger page address, or 0 अगर the IRQ is not valid
 */
u64 ocxl_afu_irq_get_addr(काष्ठा ocxl_context *ctx, पूर्णांक irq_id);

/**
 * ocxl_irq_set_handler() - Provide a callback to be called when an IRQ is triggered
 * @ctx: The AFU context that the IRQ is associated with
 * @irq_id: The IRQ ID
 * @handler: the callback to be called when the IRQ is triggered
 * @मुक्त_निजी: the callback to be called when the IRQ is मुक्तd (may be शून्य)
 * @निजी: Private data to be passed to the callbacks
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ocxl_irq_set_handler(काष्ठा ocxl_context *ctx, पूर्णांक irq_id,
		irqवापस_t (*handler)(व्योम *निजी),
		व्योम (*मुक्त_निजी)(व्योम *निजी),
		व्योम *निजी);

// AFU Metadata

/**
 * ocxl_afu_config() - Get a poपूर्णांकer to the config क्रम an AFU
 * @afu: a poपूर्णांकer to the AFU to get the config क्रम
 *
 * Returns a poपूर्णांकer to the AFU config
 */
काष्ठा ocxl_afu_config *ocxl_afu_config(काष्ठा ocxl_afu *afu);

/**
 * ocxl_afu_set_निजी() - Assign opaque hardware specअगरic inक्रमmation to an OpenCAPI AFU.
 * @afu: The OpenCAPI AFU
 * @निजी: the opaque hardware specअगरic inक्रमmation to assign to the driver
 */
व्योम ocxl_afu_set_निजी(काष्ठा ocxl_afu *afu, व्योम *निजी);

/**
 * ocxl_afu_get_निजी() - Fetch the hardware specअगरic inक्रमmation associated with
 * an बाह्यal OpenCAPI AFU. This may be consumed by an बाह्यal OpenCAPI driver.
 * @afu: The OpenCAPI AFU
 *
 * Returns the opaque poपूर्णांकer associated with the device, or शून्य अगर not set
 */
व्योम *ocxl_afu_get_निजी(काष्ठा ocxl_afu *afu);

// Global MMIO
/**
 * ocxl_global_mmio_पढ़ो32() - Read a 32 bit value from global MMIO
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @val: वापसs the value
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_पढ़ो32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			    क्रमागत ocxl_endian endian, u32 *val);

/**
 * ocxl_global_mmio_पढ़ो64() - Read a 64 bit value from global MMIO
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @val: वापसs the value
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_पढ़ो64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			    क्रमागत ocxl_endian endian, u64 *val);

/**
 * ocxl_global_mmio_ग_लिखो32() - Write a 32 bit value to global MMIO
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @val: The value to ग_लिखो
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_ग_लिखो32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			     क्रमागत ocxl_endian endian, u32 val);

/**
 * ocxl_global_mmio_ग_लिखो64() - Write a 64 bit value to global MMIO
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @val: The value to ग_लिखो
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_ग_लिखो64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			     क्रमागत ocxl_endian endian, u64 val);

/**
 * ocxl_global_mmio_set32() - Set bits in a 32 bit global MMIO रेजिस्टर
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_set32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			   क्रमागत ocxl_endian endian, u32 mask);

/**
 * ocxl_global_mmio_set64() - Set bits in a 64 bit global MMIO रेजिस्टर
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_set64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			   क्रमागत ocxl_endian endian, u64 mask);

/**
 * ocxl_global_mmio_clear32() - Set bits in a 32 bit global MMIO रेजिस्टर
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_clear32(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			     क्रमागत ocxl_endian endian, u32 mask);

/**
 * ocxl_global_mmio_clear64() - Set bits in a 64 bit global MMIO रेजिस्टर
 * @afu: The AFU
 * @offset: The Offset from the start of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Returns 0 क्रम success, negative on error
 */
पूर्णांक ocxl_global_mmio_clear64(काष्ठा ocxl_afu *afu, माप_प्रकार offset,
			     क्रमागत ocxl_endian endian, u64 mask);

// Functions left here are क्रम compatibility with the cxlflash driver

/*
 * Read the configuration space of a function क्रम the AFU specअगरied by
 * the index 'afu_idx'. Fills in a ocxl_afu_config काष्ठाure
 */
पूर्णांक ocxl_config_पढ़ो_afu(काष्ठा pci_dev *dev,
				काष्ठा ocxl_fn_config *fn,
				काष्ठा ocxl_afu_config *afu,
				u8 afu_idx);

/*
 * Tell an AFU, by writing in the configuration space, the PASIDs that
 * it can use. Range starts at 'pasid_base' and its size is a multiple
 * of 2
 *
 * 'afu_control_offset' is the offset of the AFU control DVSEC which
 * can be found in the function configuration
 */
व्योम ocxl_config_set_afu_pasid(काष्ठा pci_dev *dev,
				पूर्णांक afu_control_offset,
				पूर्णांक pasid_base, u32 pasid_count_log);

/*
 * Get the actag configuration क्रम the function:
 * 'base' is the first actag value that can be used.
 * 'enabled' it the number of actags available, starting from base.
 * 'supported' is the total number of actags desired by all the AFUs
 *             of the function.
 */
पूर्णांक ocxl_config_get_actag_info(काष्ठा pci_dev *dev,
				u16 *base, u16 *enabled, u16 *supported);

/*
 * Tell a function, by writing in the configuration space, the actags
 * it can use.
 *
 * 'func_offset' is the offset of the Function DVSEC that can found in
 * the function configuration
 */
व्योम ocxl_config_set_actag(काष्ठा pci_dev *dev, पूर्णांक func_offset,
				u32 actag_base, u32 actag_count);

/*
 * Tell an AFU, by writing in the configuration space, the actags it
 * can use.
 *
 * 'afu_control_offset' is the offset of the AFU control DVSEC क्रम the
 * desired AFU. It can be found in the AFU configuration
 */
व्योम ocxl_config_set_afu_actag(काष्ठा pci_dev *dev,
				पूर्णांक afu_control_offset,
				पूर्णांक actag_base, पूर्णांक actag_count);

/*
 * Enable/disable an AFU, by writing in the configuration space.
 *
 * 'afu_control_offset' is the offset of the AFU control DVSEC क्रम the
 * desired AFU. It can be found in the AFU configuration
 */
व्योम ocxl_config_set_afu_state(काष्ठा pci_dev *dev,
				पूर्णांक afu_control_offset, पूर्णांक enable);

/*
 * Set the Transaction Layer configuration in the configuration space.
 * Only needed क्रम function 0.
 *
 * It queries the host TL capabilities, find some common ground
 * between the host and device, and set the Transaction Layer on both
 * accordingly.
 */
पूर्णांक ocxl_config_set_TL(काष्ठा pci_dev *dev, पूर्णांक tl_dvsec);

/*
 * Request an AFU to terminate a PASID.
 * Will वापस once the AFU has acked the request, or an error in हाल
 * of समयout.
 *
 * The hardware can only terminate one PASID at a समय, so caller must
 * guarantee some kind of serialization.
 *
 * 'afu_control_offset' is the offset of the AFU control DVSEC क्रम the
 * desired AFU. It can be found in the AFU configuration
 */
पूर्णांक ocxl_config_terminate_pasid(काष्ठा pci_dev *dev,
				पूर्णांक afu_control_offset, पूर्णांक pasid);

/*
 * Read the configuration space of a function and fill in a
 * ocxl_fn_config काष्ठाure with all the function details
 */
पूर्णांक ocxl_config_पढ़ो_function(काष्ठा pci_dev *dev,
				काष्ठा ocxl_fn_config *fn);

/*
 * Set up the खोलोcapi link क्रम the function.
 *
 * When called क्रम the first समय क्रम a link, it sets up the Shared
 * Process Area क्रम the link and the पूर्णांकerrupt handler to process
 * translation faults.
 *
 * Returns a 'link handle' that should be used क्रम further calls क्रम
 * the link
 */
पूर्णांक ocxl_link_setup(काष्ठा pci_dev *dev, पूर्णांक PE_mask,
			व्योम **link_handle);

/*
 * Remove the association between the function and its link.
 */
व्योम ocxl_link_release(काष्ठा pci_dev *dev, व्योम *link_handle);

/*
 * Add a Process Element to the Shared Process Area क्रम a link.
 * The process is defined by its PASID, pid, tid and its mm_काष्ठा.
 *
 * 'xsl_err_cb' is an optional callback अगर the driver wants to be
 * notअगरied when the translation fault पूर्णांकerrupt handler detects an
 * address error.
 * 'xsl_err_data' is an argument passed to the above callback, अगर
 * defined
 */
पूर्णांक ocxl_link_add_pe(व्योम *link_handle, पूर्णांक pasid, u32 pidr, u32 tidr,
		u64 amr, u16 bdf, काष्ठा mm_काष्ठा *mm,
		व्योम (*xsl_err_cb)(व्योम *data, u64 addr, u64 dsisr),
		व्योम *xsl_err_data);

/*
 * Remove a Process Element from the Shared Process Area क्रम a link
 */
पूर्णांक ocxl_link_हटाओ_pe(व्योम *link_handle, पूर्णांक pasid);

/*
 * Allocate an AFU पूर्णांकerrupt associated to the link.
 *
 * 'hw_irq' is the hardware पूर्णांकerrupt number
 */
पूर्णांक ocxl_link_irq_alloc(व्योम *link_handle, पूर्णांक *hw_irq);

/*
 * Free a previously allocated AFU पूर्णांकerrupt
 */
व्योम ocxl_link_मुक्त_irq(व्योम *link_handle, पूर्णांक hw_irq);

#पूर्ण_अगर /* _MISC_OCXL_H_ */
