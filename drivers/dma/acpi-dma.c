<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI helpers क्रम DMA request / controller
 *
 * Based on of-dma.c
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *	    Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/acpi.h>
#समावेश <linux/acpi_dma.h>
#समावेश <linux/property.h>

अटल LIST_HEAD(acpi_dma_list);
अटल DEFINE_MUTEX(acpi_dma_lock);

/**
 * acpi_dma_parse_resource_group - match device and parse resource group
 * @grp:	CSRT resource group
 * @adev:	ACPI device to match with
 * @adma:	काष्ठा acpi_dma of the given DMA controller
 *
 * In order to match a device from DSDT table to the corresponding CSRT device
 * we use MMIO address and IRQ.
 *
 * Return:
 * 1 on success, 0 when no inक्रमmation is available, or appropriate त्रुटि_सं value
 * on error.
 */
अटल पूर्णांक acpi_dma_parse_resource_group(स्थिर काष्ठा acpi_csrt_group *grp,
		काष्ठा acpi_device *adev, काष्ठा acpi_dma *adma)
अणु
	स्थिर काष्ठा acpi_csrt_shared_info *si;
	काष्ठा list_head resource_list;
	काष्ठा resource_entry *rentry;
	resource_माप_प्रकार mem = 0, irq = 0;
	पूर्णांक ret;

	अगर (grp->shared_info_length != माप(काष्ठा acpi_csrt_shared_info))
		वापस -ENODEV;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list, शून्य, शून्य);
	अगर (ret <= 0)
		वापस 0;

	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		अगर (resource_type(rentry->res) == IORESOURCE_MEM)
			mem = rentry->res->start;
		अन्यथा अगर (resource_type(rentry->res) == IORESOURCE_IRQ)
			irq = rentry->res->start;
	पूर्ण

	acpi_dev_मुक्त_resource_list(&resource_list);

	/* Consider initial zero values as resource not found */
	अगर (mem == 0 && irq == 0)
		वापस 0;

	si = (स्थिर काष्ठा acpi_csrt_shared_info *)&grp[1];

	/* Match device by MMIO and IRQ */
	अगर (si->mmio_base_low != lower_32_bits(mem) ||
	    si->mmio_base_high != upper_32_bits(mem) ||
	    si->gsi_पूर्णांकerrupt != irq)
		वापस 0;

	dev_dbg(&adev->dev, "matches with %.4s%04X (rev %u)\n",
		(अक्षर *)&grp->venकरोr_id, grp->device_id, grp->revision);

	/* Check अगर the request line range is available */
	अगर (si->base_request_line == 0 && si->num_handshake_संकेतs == 0)
		वापस 0;

	/* Set up DMA mask based on value from CSRT */
	ret = dma_coerce_mask_and_coherent(&adev->dev,
					   DMA_BIT_MASK(si->dma_address_width));
	अगर (ret)
		वापस 0;

	adma->base_request_line = si->base_request_line;
	adma->end_request_line = si->base_request_line +
				 si->num_handshake_संकेतs - 1;

	dev_dbg(&adev->dev, "request line base: 0x%04x end: 0x%04x\n",
		adma->base_request_line, adma->end_request_line);

	वापस 1;
पूर्ण

/**
 * acpi_dma_parse_csrt - parse CSRT to exctract additional DMA resources
 * @adev:	ACPI device to match with
 * @adma:	काष्ठा acpi_dma of the given DMA controller
 *
 * CSRT or Core System Resources Table is a proprietary ACPI table
 * पूर्णांकroduced by Microsoft. This table can contain devices that are not in
 * the प्रणाली DSDT table. In particular DMA controllers might be described
 * here.
 *
 * We are using this table to get the request line range of the specअगरic DMA
 * controller to be used later.
 */
अटल व्योम acpi_dma_parse_csrt(काष्ठा acpi_device *adev, काष्ठा acpi_dma *adma)
अणु
	काष्ठा acpi_csrt_group *grp, *end;
	काष्ठा acpi_table_csrt *csrt;
	acpi_status status;
	पूर्णांक ret;

	status = acpi_get_table(ACPI_SIG_CSRT, 0,
				(काष्ठा acpi_table_header **)&csrt);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			dev_warn(&adev->dev, "failed to get the CSRT table\n");
		वापस;
	पूर्ण

	grp = (काष्ठा acpi_csrt_group *)(csrt + 1);
	end = (काष्ठा acpi_csrt_group *)((व्योम *)csrt + csrt->header.length);

	जबतक (grp < end) अणु
		ret = acpi_dma_parse_resource_group(grp, adev, adma);
		अगर (ret < 0) अणु
			dev_warn(&adev->dev,
				 "error in parsing resource group\n");
			अवरोध;
		पूर्ण

		grp = (काष्ठा acpi_csrt_group *)((व्योम *)grp + grp->length);
	पूर्ण

	acpi_put_table((काष्ठा acpi_table_header *)csrt);
पूर्ण

/**
 * acpi_dma_controller_रेजिस्टर - Register a DMA controller to ACPI DMA helpers
 * @dev:		काष्ठा device of DMA controller
 * @acpi_dma_xlate:	translation function which converts a dma specअगरier
 *			पूर्णांकo a dma_chan काष्ठाure
 * @data:		poपूर्णांकer to controller specअगरic data to be used by
 *			translation function
 *
 * Allocated memory should be मुक्तd with appropriate acpi_dma_controller_मुक्त()
 * call.
 *
 * Return:
 * 0 on success or appropriate त्रुटि_सं value on error.
 */
पूर्णांक acpi_dma_controller_रेजिस्टर(काष्ठा device *dev,
		काष्ठा dma_chan *(*acpi_dma_xlate)
		(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *),
		व्योम *data)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा acpi_dma	*adma;

	अगर (!dev || !acpi_dma_xlate)
		वापस -EINVAL;

	/* Check अगर the device was क्रमागतerated by ACPI */
	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस -EINVAL;

	adma = kzalloc(माप(*adma), GFP_KERNEL);
	अगर (!adma)
		वापस -ENOMEM;

	adma->dev = dev;
	adma->acpi_dma_xlate = acpi_dma_xlate;
	adma->data = data;

	acpi_dma_parse_csrt(adev, adma);

	/* Now queue acpi_dma controller काष्ठाure in list */
	mutex_lock(&acpi_dma_lock);
	list_add_tail(&adma->dma_controllers, &acpi_dma_list);
	mutex_unlock(&acpi_dma_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dma_controller_रेजिस्टर);

/**
 * acpi_dma_controller_मुक्त - Remove a DMA controller from ACPI DMA helpers list
 * @dev:	काष्ठा device of DMA controller
 *
 * Memory allocated by acpi_dma_controller_रेजिस्टर() is मुक्तd here.
 *
 * Return:
 * 0 on success or appropriate त्रुटि_सं value on error.
 */
पूर्णांक acpi_dma_controller_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा acpi_dma *adma;

	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&acpi_dma_lock);

	list_क्रम_each_entry(adma, &acpi_dma_list, dma_controllers)
		अगर (adma->dev == dev) अणु
			list_del(&adma->dma_controllers);
			mutex_unlock(&acpi_dma_lock);
			kमुक्त(adma);
			वापस 0;
		पूर्ण

	mutex_unlock(&acpi_dma_lock);
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dma_controller_मुक्त);

अटल व्योम devm_acpi_dma_release(काष्ठा device *dev, व्योम *res)
अणु
	acpi_dma_controller_मुक्त(dev);
पूर्ण

/**
 * devm_acpi_dma_controller_रेजिस्टर - resource managed acpi_dma_controller_रेजिस्टर()
 * @dev:		device that is रेजिस्टरing this DMA controller
 * @acpi_dma_xlate:	translation function
 * @data:		poपूर्णांकer to controller specअगरic data
 *
 * Managed acpi_dma_controller_रेजिस्टर(). DMA controller रेजिस्टरed by this
 * function are स्वतःmatically मुक्तd on driver detach. See
 * acpi_dma_controller_रेजिस्टर() क्रम more inक्रमmation.
 *
 * Return:
 * 0 on success or appropriate त्रुटि_सं value on error.
 */
पूर्णांक devm_acpi_dma_controller_रेजिस्टर(काष्ठा device *dev,
		काष्ठा dma_chan *(*acpi_dma_xlate)
		(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *),
		व्योम *data)
अणु
	व्योम *res;
	पूर्णांक ret;

	res = devres_alloc(devm_acpi_dma_release, 0, GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	ret = acpi_dma_controller_रेजिस्टर(dev, acpi_dma_xlate, data);
	अगर (ret) अणु
		devres_मुक्त(res);
		वापस ret;
	पूर्ण
	devres_add(dev, res);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_acpi_dma_controller_रेजिस्टर);

/**
 * devm_acpi_dma_controller_मुक्त - resource managed acpi_dma_controller_मुक्त()
 * @dev:	device that is unरेजिस्टरing as DMA controller
 *
 * Unरेजिस्टर a DMA controller रेजिस्टरed with
 * devm_acpi_dma_controller_रेजिस्टर(). Normally this function will not need to
 * be called and the resource management code will ensure that the resource is
 * मुक्तd.
 */
व्योम devm_acpi_dma_controller_मुक्त(काष्ठा device *dev)
अणु
	WARN_ON(devres_release(dev, devm_acpi_dma_release, शून्य, शून्य));
पूर्ण
EXPORT_SYMBOL_GPL(devm_acpi_dma_controller_मुक्त);

/**
 * acpi_dma_update_dma_spec - prepare dma specअगरier to pass to translation function
 * @adma:	काष्ठा acpi_dma of DMA controller
 * @dma_spec:	dma specअगरier to update
 *
 * Accordingly to ACPI 5.0 Specअगरication Table 6-170 "Fixed DMA Resource
 * Descriptor":
 *	DMA Request Line bits is a platक्रमm-relative number uniquely
 *	identअगरying the request line asचिन्हित. Request line-to-Controller
 *	mapping is करोne in a controller-specअगरic OS driver.
 * That's why we can safely adjust slave_id when the appropriate controller is
 * found.
 *
 * Return:
 * 0, अगर no inक्रमmation is avaiable, -1 on mismatch, and 1 otherwise.
 */
अटल पूर्णांक acpi_dma_update_dma_spec(काष्ठा acpi_dma *adma,
		काष्ठा acpi_dma_spec *dma_spec)
अणु
	/* Set link to the DMA controller device */
	dma_spec->dev = adma->dev;

	/* Check अगर the request line range is available */
	अगर (adma->base_request_line == 0 && adma->end_request_line == 0)
		वापस 0;

	/* Check अगर slave_id falls to the range */
	अगर (dma_spec->slave_id < adma->base_request_line ||
	    dma_spec->slave_id > adma->end_request_line)
		वापस -1;

	/*
	 * Here we adjust slave_id. It should be a relative number to the base
	 * request line.
	 */
	dma_spec->slave_id -= adma->base_request_line;

	वापस 1;
पूर्ण

काष्ठा acpi_dma_parser_data अणु
	काष्ठा acpi_dma_spec dma_spec;
	माप_प्रकार index;
	माप_प्रकार n;
पूर्ण;

/**
 * acpi_dma_parse_fixed_dma - Parse FixedDMA ACPI resources to a DMA specअगरier
 * @res:	काष्ठा acpi_resource to get FixedDMA resources from
 * @data:	poपूर्णांकer to a helper काष्ठा acpi_dma_parser_data
 */
अटल पूर्णांक acpi_dma_parse_fixed_dma(काष्ठा acpi_resource *res, व्योम *data)
अणु
	काष्ठा acpi_dma_parser_data *pdata = data;

	अगर (res->type == ACPI_RESOURCE_TYPE_FIXED_DMA) अणु
		काष्ठा acpi_resource_fixed_dma *dma = &res->data.fixed_dma;

		अगर (pdata->n++ == pdata->index) अणु
			pdata->dma_spec.chan_id = dma->channels;
			pdata->dma_spec.slave_id = dma->request_lines;
		पूर्ण
	पूर्ण

	/* Tell the ACPI core to skip this resource */
	वापस 1;
पूर्ण

/**
 * acpi_dma_request_slave_chan_by_index - Get the DMA slave channel
 * @dev:	काष्ठा device to get DMA request from
 * @index:	index of FixedDMA descriptor क्रम @dev
 *
 * Return:
 * Poपूर्णांकer to appropriate dma channel on success or an error poपूर्णांकer.
 */
काष्ठा dma_chan *acpi_dma_request_slave_chan_by_index(काष्ठा device *dev,
		माप_प्रकार index)
अणु
	काष्ठा acpi_dma_parser_data pdata;
	काष्ठा acpi_dma_spec *dma_spec = &pdata.dma_spec;
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	काष्ठा list_head resource_list;
	काष्ठा acpi_dma *adma;
	काष्ठा dma_chan *chan = शून्य;
	पूर्णांक found;
	पूर्णांक ret;

	स_रखो(&pdata, 0, माप(pdata));
	pdata.index = index;

	/* Initial values क्रम the request line and channel */
	dma_spec->chan_id = -1;
	dma_spec->slave_id = -1;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     acpi_dma_parse_fixed_dma, &pdata);
	acpi_dev_मुक्त_resource_list(&resource_list);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (dma_spec->slave_id < 0 || dma_spec->chan_id < 0)
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&acpi_dma_lock);

	list_क्रम_each_entry(adma, &acpi_dma_list, dma_controllers) अणु
		/*
		 * We are not going to call translation function अगर slave_id
		 * करोesn't fall to the request range.
		 */
		found = acpi_dma_update_dma_spec(adma, dma_spec);
		अगर (found < 0)
			जारी;
		chan = adma->acpi_dma_xlate(dma_spec, adma);
		/*
		 * Try to get a channel only from the DMA controller that
		 * matches the slave_id. See acpi_dma_update_dma_spec()
		 * description क्रम the details.
		 */
		अगर (found > 0 || chan)
			अवरोध;
	पूर्ण

	mutex_unlock(&acpi_dma_lock);
	वापस chan ? chan : ERR_PTR(-EPROBE_DEFER);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dma_request_slave_chan_by_index);

/**
 * acpi_dma_request_slave_chan_by_name - Get the DMA slave channel
 * @dev:	काष्ठा device to get DMA request from
 * @name:	represents corresponding FixedDMA descriptor क्रम @dev
 *
 * In order to support both Device Tree and ACPI in a single driver we
 * translate the names "tx" and "rx" here based on the most common हाल where
 * the first FixedDMA descriptor is TX and second is RX.
 *
 * If the device has "dma-names" property the FixedDMA descriptor indices
 * are retrieved based on those. Otherwise the function falls back using
 * hardcoded indices.
 *
 * Return:
 * Poपूर्णांकer to appropriate dma channel on success or an error poपूर्णांकer.
 */
काष्ठा dma_chan *acpi_dma_request_slave_chan_by_name(काष्ठा device *dev,
		स्थिर अक्षर *name)
अणु
	पूर्णांक index;

	index = device_property_match_string(dev, "dma-names", name);
	अगर (index < 0) अणु
		अगर (!म_भेद(name, "tx"))
			index = 0;
		अन्यथा अगर (!म_भेद(name, "rx"))
			index = 1;
		अन्यथा
			वापस ERR_PTR(-ENODEV);
	पूर्ण

	dev_dbg(dev, "Looking for DMA channel \"%s\" at index %d...\n", name, index);
	वापस acpi_dma_request_slave_chan_by_index(dev, index);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dma_request_slave_chan_by_name);

/**
 * acpi_dma_simple_xlate - Simple ACPI DMA engine translation helper
 * @dma_spec: poपूर्णांकer to ACPI DMA specअगरier
 * @adma: poपूर्णांकer to ACPI DMA controller data
 *
 * A simple translation function क्रम ACPI based devices. Passes &काष्ठा
 * dma_spec to the DMA controller driver provided filter function.
 *
 * Return:
 * Poपूर्णांकer to the channel अगर found or %शून्य otherwise.
 */
काष्ठा dma_chan *acpi_dma_simple_xlate(काष्ठा acpi_dma_spec *dma_spec,
		काष्ठा acpi_dma *adma)
अणु
	काष्ठा acpi_dma_filter_info *info = adma->data;

	अगर (!info || !info->filter_fn)
		वापस शून्य;

	वापस dma_request_channel(info->dma_cap, info->filter_fn, dma_spec);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dma_simple_xlate);
