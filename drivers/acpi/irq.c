<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI GSI IRQ layer
 *
 * Copyright (C) 2015 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 */
#समावेश <linux/acpi.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>

क्रमागत acpi_irq_model_id acpi_irq_model;

अटल काष्ठा fwnode_handle *acpi_gsi_करोमुख्य_id;

/**
 * acpi_gsi_to_irq() - Retrieve the linux irq number क्रम a given GSI
 * @gsi: GSI IRQ number to map
 * @irq: poपूर्णांकer where linux IRQ number is stored
 *
 * irq location updated with irq value [>0 on success, 0 on failure]
 *
 * Returns: 0 on success
 *          -EINVAL on failure
 */
पूर्णांक acpi_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक *irq)
अणु
	काष्ठा irq_करोमुख्य *d = irq_find_matching_fwnode(acpi_gsi_करोमुख्य_id,
							DOMAIN_BUS_ANY);

	*irq = irq_find_mapping(d, gsi);
	/*
	 * *irq == 0 means no mapping, that should
	 * be reported as a failure
	 */
	वापस (*irq > 0) ? 0 : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_gsi_to_irq);

/**
 * acpi_रेजिस्टर_gsi() - Map a GSI to a linux IRQ number
 * @dev: device क्रम which IRQ has to be mapped
 * @gsi: GSI IRQ number
 * @trigger: trigger type of the GSI number to be mapped
 * @polarity: polarity of the GSI to be mapped
 *
 * Returns: a valid linux IRQ number on success
 *          -EINVAL on failure
 */
पूर्णांक acpi_रेजिस्टर_gsi(काष्ठा device *dev, u32 gsi, पूर्णांक trigger,
		      पूर्णांक polarity)
अणु
	काष्ठा irq_fwspec fwspec;

	अगर (WARN_ON(!acpi_gsi_करोमुख्य_id)) अणु
		pr_warn("GSI: No registered irqchip, giving up\n");
		वापस -EINVAL;
	पूर्ण

	fwspec.fwnode = acpi_gsi_करोमुख्य_id;
	fwspec.param[0] = gsi;
	fwspec.param[1] = acpi_dev_get_irq_type(trigger, polarity);
	fwspec.param_count = 2;

	वापस irq_create_fwspec_mapping(&fwspec);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_रेजिस्टर_gsi);

/**
 * acpi_unरेजिस्टर_gsi() - Free a GSI<->linux IRQ number mapping
 * @gsi: GSI IRQ number
 */
व्योम acpi_unरेजिस्टर_gsi(u32 gsi)
अणु
	काष्ठा irq_करोमुख्य *d = irq_find_matching_fwnode(acpi_gsi_करोमुख्य_id,
							DOMAIN_BUS_ANY);
	पूर्णांक irq;

	अगर (WARN_ON(acpi_irq_model == ACPI_IRQ_MODEL_GIC && gsi < 16))
		वापस;

	irq = irq_find_mapping(d, gsi);
	irq_dispose_mapping(irq);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_unरेजिस्टर_gsi);

/**
 * acpi_get_irq_source_fwhandle() - Retrieve fwhandle from IRQ resource source.
 * @source: acpi_resource_source to use क्रम the lookup.
 *
 * Description:
 * Retrieve the fwhandle of the device referenced by the given IRQ resource
 * source.
 *
 * Return:
 * The referenced device fwhandle or शून्य on failure
 */
अटल काष्ठा fwnode_handle *
acpi_get_irq_source_fwhandle(स्थिर काष्ठा acpi_resource_source *source)
अणु
	काष्ठा fwnode_handle *result;
	काष्ठा acpi_device *device;
	acpi_handle handle;
	acpi_status status;

	अगर (!source->string_length)
		वापस acpi_gsi_करोमुख्य_id;

	status = acpi_get_handle(शून्य, source->string_ptr, &handle);
	अगर (WARN_ON(ACPI_FAILURE(status)))
		वापस शून्य;

	device = acpi_bus_get_acpi_device(handle);
	अगर (WARN_ON(!device))
		वापस शून्य;

	result = &device->fwnode;
	acpi_bus_put_acpi_device(device);
	वापस result;
पूर्ण

/*
 * Context क्रम the resource walk used to lookup IRQ resources.
 * Contains a वापस code, the lookup index, and references to the flags
 * and fwspec where the result is वापसed.
 */
काष्ठा acpi_irq_parse_one_ctx अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ *res_flags;
	काष्ठा irq_fwspec *fwspec;
पूर्ण;

/**
 * acpi_irq_parse_one_match - Handle a matching IRQ resource.
 * @fwnode: matching fwnode
 * @hwirq: hardware IRQ number
 * @triggering: triggering attributes of hwirq
 * @polarity: polarity attributes of hwirq
 * @polarity: polarity attributes of hwirq
 * @shareable: shareable attributes of hwirq
 * @ctx: acpi_irq_parse_one_ctx updated by this function
 *
 * Description:
 * Handle a matching IRQ resource by populating the given ctx with
 * the inक्रमmation passed.
 */
अटल अंतरभूत व्योम acpi_irq_parse_one_match(काष्ठा fwnode_handle *fwnode,
					    u32 hwirq, u8 triggering,
					    u8 polarity, u8 shareable,
					    काष्ठा acpi_irq_parse_one_ctx *ctx)
अणु
	अगर (!fwnode)
		वापस;
	ctx->rc = 0;
	*ctx->res_flags = acpi_dev_irq_flags(triggering, polarity, shareable);
	ctx->fwspec->fwnode = fwnode;
	ctx->fwspec->param[0] = hwirq;
	ctx->fwspec->param[1] = acpi_dev_get_irq_type(triggering, polarity);
	ctx->fwspec->param_count = 2;
पूर्ण

/**
 * acpi_irq_parse_one_cb - Handle the given resource.
 * @ares: resource to handle
 * @context: context क्रम the walk
 *
 * Description:
 * This is called by acpi_walk_resources passing each resource वापसed by
 * the _CRS method. We only inspect IRQ resources. Since IRQ resources
 * might contain multiple पूर्णांकerrupts we check अगर the index is within this
 * one's पूर्णांकerrupt array, otherwise we subtract the current resource IRQ
 * count from the lookup index to prepare क्रम the next resource.
 * Once a match is found we call acpi_irq_parse_one_match to populate
 * the result and end the walk by वापसing AE_CTRL_TERMINATE.
 *
 * Return:
 * AE_OK अगर the walk should जारी, AE_CTRL_TERMINATE अगर a matching
 * IRQ resource was found.
 */
अटल acpi_status acpi_irq_parse_one_cb(काष्ठा acpi_resource *ares,
					 व्योम *context)
अणु
	काष्ठा acpi_irq_parse_one_ctx *ctx = context;
	काष्ठा acpi_resource_irq *irq;
	काष्ठा acpi_resource_extended_irq *eirq;
	काष्ठा fwnode_handle *fwnode;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_IRQ:
		irq = &ares->data.irq;
		अगर (ctx->index >= irq->पूर्णांकerrupt_count) अणु
			ctx->index -= irq->पूर्णांकerrupt_count;
			वापस AE_OK;
		पूर्ण
		fwnode = acpi_gsi_करोमुख्य_id;
		acpi_irq_parse_one_match(fwnode, irq->पूर्णांकerrupts[ctx->index],
					 irq->triggering, irq->polarity,
					 irq->shareable, ctx);
		वापस AE_CTRL_TERMINATE;
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		eirq = &ares->data.extended_irq;
		अगर (eirq->producer_consumer == ACPI_PRODUCER)
			वापस AE_OK;
		अगर (ctx->index >= eirq->पूर्णांकerrupt_count) अणु
			ctx->index -= eirq->पूर्णांकerrupt_count;
			वापस AE_OK;
		पूर्ण
		fwnode = acpi_get_irq_source_fwhandle(&eirq->resource_source);
		acpi_irq_parse_one_match(fwnode, eirq->पूर्णांकerrupts[ctx->index],
					 eirq->triggering, eirq->polarity,
					 eirq->shareable, ctx);
		वापस AE_CTRL_TERMINATE;
	पूर्ण

	वापस AE_OK;
पूर्ण

/**
 * acpi_irq_parse_one - Resolve an पूर्णांकerrupt क्रम a device
 * @handle: the device whose पूर्णांकerrupt is to be resolved
 * @index: index of the पूर्णांकerrupt to resolve
 * @fwspec: काष्ठाure irq_fwspec filled by this function
 * @flags: resource flags filled by this function
 *
 * Description:
 * Resolves an पूर्णांकerrupt क्रम a device by walking its CRS resources to find
 * the appropriate ACPI IRQ resource and populating the given काष्ठा irq_fwspec
 * and flags.
 *
 * Return:
 * The result stored in ctx.rc by the callback, or the शेष -EINVAL value
 * अगर an error occurs.
 */
अटल पूर्णांक acpi_irq_parse_one(acpi_handle handle, अचिन्हित पूर्णांक index,
			      काष्ठा irq_fwspec *fwspec, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा acpi_irq_parse_one_ctx ctx = अणु -EINVAL, index, flags, fwspec पूर्ण;

	acpi_walk_resources(handle, METHOD_NAME__CRS, acpi_irq_parse_one_cb, &ctx);
	वापस ctx.rc;
पूर्ण

/**
 * acpi_irq_get - Lookup an ACPI IRQ resource and use it to initialize resource.
 * @handle: ACPI device handle
 * @index:  ACPI IRQ resource index to lookup
 * @res:    Linux IRQ resource to initialize
 *
 * Description:
 * Look क्रम the ACPI IRQ resource with the given index and use it to initialize
 * the given Linux IRQ resource.
 *
 * Return:
 * 0 on success
 * -EINVAL अगर an error occurs
 * -EPROBE_DEFER अगर the IRQ lookup/conversion failed
 */
पूर्णांक acpi_irq_get(acpi_handle handle, अचिन्हित पूर्णांक index, काष्ठा resource *res)
अणु
	काष्ठा irq_fwspec fwspec;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rc = acpi_irq_parse_one(handle, index, &fwspec, &flags);
	अगर (rc)
		वापस rc;

	करोमुख्य = irq_find_matching_fwnode(fwspec.fwnode, DOMAIN_BUS_ANY);
	अगर (!करोमुख्य)
		वापस -EPROBE_DEFER;

	rc = irq_create_fwspec_mapping(&fwspec);
	अगर (rc <= 0)
		वापस -EINVAL;

	res->start = rc;
	res->end = rc;
	res->flags = flags;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_irq_get);

/**
 * acpi_set_irq_model - Setup the GSI irqकरोमुख्य inक्रमmation
 * @model: the value asचिन्हित to acpi_irq_model
 * @fwnode: the irq_करोमुख्य identअगरier क्रम mapping and looking up
 *          GSI पूर्णांकerrupts
 */
व्योम __init acpi_set_irq_model(क्रमागत acpi_irq_model_id model,
			       काष्ठा fwnode_handle *fwnode)
अणु
	acpi_irq_model = model;
	acpi_gsi_करोमुख्य_id = fwnode;
पूर्ण

/**
 * acpi_irq_create_hierarchy - Create a hierarchical IRQ करोमुख्य with the शेष
 *                             GSI करोमुख्य as its parent.
 * @flags:      Irq करोमुख्य flags associated with the करोमुख्य
 * @size:       Size of the करोमुख्य.
 * @fwnode:     Optional fwnode of the पूर्णांकerrupt controller
 * @ops:        Poपूर्णांकer to the पूर्णांकerrupt करोमुख्य callbacks
 * @host_data:  Controller निजी data poपूर्णांकer
 */
काष्ठा irq_करोमुख्य *acpi_irq_create_hierarchy(अचिन्हित पूर्णांक flags,
					     अचिन्हित पूर्णांक size,
					     काष्ठा fwnode_handle *fwnode,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					     व्योम *host_data)
अणु
	काष्ठा irq_करोमुख्य *d = irq_find_matching_fwnode(acpi_gsi_करोमुख्य_id,
							DOMAIN_BUS_ANY);

	अगर (!d)
		वापस शून्य;

	वापस irq_करोमुख्य_create_hierarchy(d, flags, size, fwnode, ops,
					   host_data);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_irq_create_hierarchy);
