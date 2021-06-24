<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश "dm_services_types.h"
#समावेश "dc.h"

#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_dm_irq.h"

/**
 * DOC: overview
 *
 * DM provides another layer of IRQ management on top of what the base driver
 * alपढ़ोy provides. This is something that could be cleaned up, and is a
 * future TODO item.
 *
 * The base driver provides IRQ source registration with DRM, handler
 * registration पूर्णांकo the base driver's IRQ table, and a handler callback
 * amdgpu_irq_handler(), with which DRM calls on पूर्णांकerrupts. This generic
 * handler looks up the IRQ table, and calls the respective
 * &amdgpu_irq_src_funcs.process hookups.
 *
 * What DM provides on top are two IRQ tables specअगरically क्रम top-half and
 * bottom-half IRQ handling, with the bottom-half implementing workqueues:
 *
 * - &amdgpu_display_manager.irq_handler_list_high_tab
 * - &amdgpu_display_manager.irq_handler_list_low_tab
 *
 * They override the base driver's IRQ table, and the effect can be seen
 * in the hooks that DM provides क्रम &amdgpu_irq_src_funcs.process. They
 * are all set to the DM generic handler amdgpu_dm_irq_handler(), which looks up
 * DM's IRQ tables. However, in order क्रम base driver to recognize this hook, DM
 * still needs to रेजिस्टर the IRQ with the base driver. See
 * dce110_रेजिस्टर_irq_handlers() and dcn10_रेजिस्टर_irq_handlers().
 *
 * To expose DC's hardware पूर्णांकerrupt toggle to the base driver, DM implements
 * &amdgpu_irq_src_funcs.set hooks. Base driver calls it through
 * amdgpu_irq_update() to enable or disable the पूर्णांकerrupt.
 */

/******************************************************************************
 * Private declarations.
 *****************************************************************************/

/**
 * काष्ठा amdgpu_dm_irq_handler_data - Data क्रम DM पूर्णांकerrupt handlers.
 *
 * @list: Linked list entry referencing the next/previous handler
 * @handler: Handler function
 * @handler_arg: Argument passed to the handler when triggered
 * @dm: DM which this handler beदीर्घs to
 * @irq_source: DC पूर्णांकerrupt source that this handler is रेजिस्टरed क्रम
 * @work: work काष्ठा
 */
काष्ठा amdgpu_dm_irq_handler_data अणु
	काष्ठा list_head list;
	पूर्णांकerrupt_handler handler;
	व्योम *handler_arg;

	काष्ठा amdgpu_display_manager *dm;
	/* DAL irq source which रेजिस्टरed क्रम this पूर्णांकerrupt. */
	क्रमागत dc_irq_source irq_source;
	काष्ठा work_काष्ठा work;
पूर्ण;

#घोषणा DM_IRQ_TABLE_LOCK(adev, flags) \
	spin_lock_irqsave(&adev->dm.irq_handler_list_table_lock, flags)

#घोषणा DM_IRQ_TABLE_UNLOCK(adev, flags) \
	spin_unlock_irqrestore(&adev->dm.irq_handler_list_table_lock, flags)

/******************************************************************************
 * Private functions.
 *****************************************************************************/

अटल व्योम init_handler_common_data(काष्ठा amdgpu_dm_irq_handler_data *hcd,
				     व्योम (*ih)(व्योम *),
				     व्योम *args,
				     काष्ठा amdgpu_display_manager *dm)
अणु
	hcd->handler = ih;
	hcd->handler_arg = args;
	hcd->dm = dm;
पूर्ण

/**
 * dm_irq_work_func() - Handle an IRQ outside of the पूर्णांकerrupt handler proper.
 *
 * @work: work काष्ठा
 */
अटल व्योम dm_irq_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_dm_irq_handler_data *handler_data =
		container_of(work, काष्ठा amdgpu_dm_irq_handler_data, work);

	handler_data->handler(handler_data->handler_arg);

	/* Call a DAL subcomponent which रेजिस्टरed क्रम पूर्णांकerrupt notअगरication
	 * at INTERRUPT_LOW_IRQ_CONTEXT.
	 * (The most common use is HPD पूर्णांकerrupt) */
पूर्ण

/*
 * Remove a handler and वापस a poपूर्णांकer to handler list from which the
 * handler was हटाओd.
 */
अटल काष्ठा list_head *हटाओ_irq_handler(काष्ठा amdgpu_device *adev,
					    व्योम *ih,
					    स्थिर काष्ठा dc_पूर्णांकerrupt_params *पूर्णांक_params)
अणु
	काष्ठा list_head *hnd_list;
	काष्ठा list_head *entry, *पंचांगp;
	काष्ठा amdgpu_dm_irq_handler_data *handler;
	अचिन्हित दीर्घ irq_table_flags;
	bool handler_हटाओd = false;
	क्रमागत dc_irq_source irq_source;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	irq_source = पूर्णांक_params->irq_source;

	चयन (पूर्णांक_params->पूर्णांक_context) अणु
	हाल INTERRUPT_HIGH_IRQ_CONTEXT:
		hnd_list = &adev->dm.irq_handler_list_high_tab[irq_source];
		अवरोध;
	हाल INTERRUPT_LOW_IRQ_CONTEXT:
	शेष:
		hnd_list = &adev->dm.irq_handler_list_low_tab[irq_source];
		अवरोध;
	पूर्ण

	list_क्रम_each_safe(entry, पंचांगp, hnd_list) अणु

		handler = list_entry(entry, काष्ठा amdgpu_dm_irq_handler_data,
				     list);

		अगर (handler == शून्य)
			जारी;

		अगर (ih == handler->handler) अणु
			/* Found our handler. Remove it from the list. */
			list_del(&handler->list);
			handler_हटाओd = true;
			अवरोध;
		पूर्ण
	पूर्ण

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);

	अगर (handler_हटाओd == false) अणु
		/* Not necessarily an error - caller may not
		 * know the context. */
		वापस शून्य;
	पूर्ण

	kमुक्त(handler);

	DRM_DEBUG_KMS(
	"DM_IRQ: removed irq handler: %p for: dal_src=%d, irq context=%d\n",
		ih, पूर्णांक_params->irq_source, पूर्णांक_params->पूर्णांक_context);

	वापस hnd_list;
पूर्ण

/**
 * unरेजिस्टर_all_irq_handlers() - Cleans up handlers from the DM IRQ table
 * @adev: The base driver device containing the DM device
 *
 * Go through low and high context IRQ tables and deallocate handlers.
 */
अटल व्योम unरेजिस्टर_all_irq_handlers(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा list_head *hnd_list_low;
	काष्ठा list_head *hnd_list_high;
	काष्ठा list_head *entry, *पंचांगp;
	काष्ठा amdgpu_dm_irq_handler_data *handler;
	अचिन्हित दीर्घ irq_table_flags;
	पूर्णांक i;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	क्रम (i = 0; i < DAL_IRQ_SOURCES_NUMBER; i++) अणु
		hnd_list_low = &adev->dm.irq_handler_list_low_tab[i];
		hnd_list_high = &adev->dm.irq_handler_list_high_tab[i];

		list_क्रम_each_safe(entry, पंचांगp, hnd_list_low) अणु

			handler = list_entry(entry, काष्ठा amdgpu_dm_irq_handler_data,
					     list);

			अगर (handler == शून्य || handler->handler == शून्य)
				जारी;

			list_del(&handler->list);
			kमुक्त(handler);
		पूर्ण

		list_क्रम_each_safe(entry, पंचांगp, hnd_list_high) अणु

			handler = list_entry(entry, काष्ठा amdgpu_dm_irq_handler_data,
					     list);

			अगर (handler == शून्य || handler->handler == शून्य)
				जारी;

			list_del(&handler->list);
			kमुक्त(handler);
		पूर्ण
	पूर्ण

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);
पूर्ण

अटल bool
validate_irq_registration_params(काष्ठा dc_पूर्णांकerrupt_params *पूर्णांक_params,
				 व्योम (*ih)(व्योम *))
अणु
	अगर (शून्य == पूर्णांक_params || शून्य == ih) अणु
		DRM_ERROR("DM_IRQ: invalid input!\n");
		वापस false;
	पूर्ण

	अगर (पूर्णांक_params->पूर्णांक_context >= INTERRUPT_CONTEXT_NUMBER) अणु
		DRM_ERROR("DM_IRQ: invalid context: %d!\n",
				पूर्णांक_params->पूर्णांक_context);
		वापस false;
	पूर्ण

	अगर (!DAL_VALID_IRQ_SRC_NUM(पूर्णांक_params->irq_source)) अणु
		DRM_ERROR("DM_IRQ: invalid irq_source: %d!\n",
				पूर्णांक_params->irq_source);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool validate_irq_unregistration_params(क्रमागत dc_irq_source irq_source,
					       irq_handler_idx handler_idx)
अणु
	अगर (DAL_INVALID_IRQ_HANDLER_IDX == handler_idx) अणु
		DRM_ERROR("DM_IRQ: invalid handler_idx==NULL!\n");
		वापस false;
	पूर्ण

	अगर (!DAL_VALID_IRQ_SRC_NUM(irq_source)) अणु
		DRM_ERROR("DM_IRQ: invalid irq_source:%d!\n", irq_source);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
/******************************************************************************
 * Public functions.
 *
 * Note: caller is responsible क्रम input validation.
 *****************************************************************************/

/**
 * amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt() - Register a handler within DM.
 * @adev: The base driver device containing the DM device.
 * @पूर्णांक_params: Interrupt parameters containing the source, and handler context
 * @ih: Function poपूर्णांकer to the पूर्णांकerrupt handler to रेजिस्टर
 * @handler_args: Arguments passed to the handler when the पूर्णांकerrupt occurs
 *
 * Register an पूर्णांकerrupt handler क्रम the given IRQ source, under the given
 * context. The context can either be high or low. High context handlers are
 * executed directly within ISR context, जबतक low context is executed within a
 * workqueue, thereby allowing operations that sleep.
 *
 * Registered handlers are called in a FIFO manner, i.e. the most recently
 * रेजिस्टरed handler will be called first.
 *
 * Return: Handler data &काष्ठा amdgpu_dm_irq_handler_data containing the IRQ
 *         source, handler function, and args
 */
व्योम *amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				       काष्ठा dc_पूर्णांकerrupt_params *पूर्णांक_params,
				       व्योम (*ih)(व्योम *),
				       व्योम *handler_args)
अणु
	काष्ठा list_head *hnd_list;
	काष्ठा amdgpu_dm_irq_handler_data *handler_data;
	अचिन्हित दीर्घ irq_table_flags;
	क्रमागत dc_irq_source irq_source;

	अगर (false == validate_irq_registration_params(पूर्णांक_params, ih))
		वापस DAL_INVALID_IRQ_HANDLER_IDX;

	handler_data = kzalloc(माप(*handler_data), GFP_KERNEL);
	अगर (!handler_data) अणु
		DRM_ERROR("DM_IRQ: failed to allocate irq handler!\n");
		वापस DAL_INVALID_IRQ_HANDLER_IDX;
	पूर्ण

	init_handler_common_data(handler_data, ih, handler_args, &adev->dm);

	irq_source = पूर्णांक_params->irq_source;

	handler_data->irq_source = irq_source;

	/* Lock the list, add the handler. */
	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	चयन (पूर्णांक_params->पूर्णांक_context) अणु
	हाल INTERRUPT_HIGH_IRQ_CONTEXT:
		hnd_list = &adev->dm.irq_handler_list_high_tab[irq_source];
		अवरोध;
	हाल INTERRUPT_LOW_IRQ_CONTEXT:
	शेष:
		hnd_list = &adev->dm.irq_handler_list_low_tab[irq_source];
		INIT_WORK(&handler_data->work, dm_irq_work_func);
		अवरोध;
	पूर्ण

	list_add_tail(&handler_data->list, hnd_list);

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);

	/* This poपूर्णांकer will be stored by code which requested पूर्णांकerrupt
	 * registration.
	 * The same poपूर्णांकer will be needed in order to unरेजिस्टर the
	 * पूर्णांकerrupt. */

	DRM_DEBUG_KMS(
		"DM_IRQ: added irq handler: %p for: dal_src=%d, irq context=%d\n",
		handler_data,
		irq_source,
		पूर्णांक_params->पूर्णांक_context);

	वापस handler_data;
पूर्ण

/**
 * amdgpu_dm_irq_unरेजिस्टर_पूर्णांकerrupt() - Remove a handler from the DM IRQ table
 * @adev: The base driver device containing the DM device
 * @irq_source: IRQ source to हटाओ the given handler from
 * @ih: Function poपूर्णांकer to the पूर्णांकerrupt handler to unरेजिस्टर
 *
 * Go through both low and high context IRQ tables, and find the given handler
 * क्रम the given irq source. If found, हटाओ it. Otherwise, करो nothing.
 */
व्योम amdgpu_dm_irq_unरेजिस्टर_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
					क्रमागत dc_irq_source irq_source,
					व्योम *ih)
अणु
	काष्ठा list_head *handler_list;
	काष्ठा dc_पूर्णांकerrupt_params पूर्णांक_params;
	पूर्णांक i;

	अगर (false == validate_irq_unregistration_params(irq_source, ih))
		वापस;

	स_रखो(&पूर्णांक_params, 0, माप(पूर्णांक_params));

	पूर्णांक_params.irq_source = irq_source;

	क्रम (i = 0; i < INTERRUPT_CONTEXT_NUMBER; i++) अणु

		पूर्णांक_params.पूर्णांक_context = i;

		handler_list = हटाओ_irq_handler(adev, ih, &पूर्णांक_params);

		अगर (handler_list != शून्य)
			अवरोध;
	पूर्ण

	अगर (handler_list == शून्य) अणु
		/* If we got here, it means we searched all irq contexts
		 * क्रम this irq source, but the handler was not found. */
		DRM_ERROR(
		"DM_IRQ: failed to find irq handler:%p for irq_source:%d!\n",
			ih, irq_source);
	पूर्ण
पूर्ण

/**
 * amdgpu_dm_irq_init() - Initialize DM IRQ management
 * @adev:  The base driver device containing the DM device
 *
 * Initialize DM's high and low context IRQ tables.
 *
 * The N by M table contains N IRQ sources, with M
 * &काष्ठा amdgpu_dm_irq_handler_data hooked together in a linked list. The
 * list_heads are initialized here. When an पूर्णांकerrupt n is triggered, all m
 * handlers are called in sequence, FIFO according to registration order.
 *
 * The low context table requires special steps to initialize, since handlers
 * will be deferred to a workqueue. See &काष्ठा irq_list_head.
 */
पूर्णांक amdgpu_dm_irq_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक src;
	काष्ठा list_head *lh;

	DRM_DEBUG_KMS("DM_IRQ\n");

	spin_lock_init(&adev->dm.irq_handler_list_table_lock);

	क्रम (src = 0; src < DAL_IRQ_SOURCES_NUMBER; src++) अणु
		/* low context handler list init */
		lh = &adev->dm.irq_handler_list_low_tab[src];
		INIT_LIST_HEAD(lh);
		/* high context handler init */
		INIT_LIST_HEAD(&adev->dm.irq_handler_list_high_tab[src]);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_dm_irq_fini() - Tear करोwn DM IRQ management
 * @adev: The base driver device containing the DM device
 *
 * Flush all work within the low context IRQ table.
 */
व्योम amdgpu_dm_irq_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक src;
	काष्ठा list_head *lh;
	काष्ठा list_head *entry, *पंचांगp;
	काष्ठा amdgpu_dm_irq_handler_data *handler;
	अचिन्हित दीर्घ irq_table_flags;

	DRM_DEBUG_KMS("DM_IRQ: releasing resources.\n");
	क्रम (src = 0; src < DAL_IRQ_SOURCES_NUMBER; src++) अणु
		DM_IRQ_TABLE_LOCK(adev, irq_table_flags);
		/* The handler was हटाओd from the table,
		 * it means it is safe to flush all the 'work'
		 * (because no code can schedule a new one). */
		lh = &adev->dm.irq_handler_list_low_tab[src];
		DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);

		अगर (!list_empty(lh)) अणु
			list_क्रम_each_safe(entry, पंचांगp, lh) अणु
				handler = list_entry(
					entry,
					काष्ठा amdgpu_dm_irq_handler_data,
					list);
				flush_work(&handler->work);
			पूर्ण
		पूर्ण
	पूर्ण
	/* Deallocate handlers from the table. */
	unरेजिस्टर_all_irq_handlers(adev);
पूर्ण

पूर्णांक amdgpu_dm_irq_suspend(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक src;
	काष्ठा list_head *hnd_list_h;
	काष्ठा list_head *hnd_list_l;
	अचिन्हित दीर्घ irq_table_flags;
	काष्ठा list_head *entry, *पंचांगp;
	काष्ठा amdgpu_dm_irq_handler_data *handler;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	DRM_DEBUG_KMS("DM_IRQ: suspend\n");

	/**
	 * Disable HW पूर्णांकerrupt  क्रम HPD and HPDRX only since FLIP and VBLANK
	 * will be disabled from manage_dm_पूर्णांकerrupts on disable CRTC.
	 */
	क्रम (src = DC_IRQ_SOURCE_HPD1; src <= DC_IRQ_SOURCE_HPD6RX; src++) अणु
		hnd_list_l = &adev->dm.irq_handler_list_low_tab[src];
		hnd_list_h = &adev->dm.irq_handler_list_high_tab[src];
		अगर (!list_empty(hnd_list_l) || !list_empty(hnd_list_h))
			dc_पूर्णांकerrupt_set(adev->dm.dc, src, false);

		DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);

		अगर (!list_empty(hnd_list_l)) अणु
			list_क्रम_each_safe (entry, पंचांगp, hnd_list_l) अणु
				handler = list_entry(
					entry,
					काष्ठा amdgpu_dm_irq_handler_data,
					list);
				flush_work(&handler->work);
			पूर्ण
		पूर्ण
		DM_IRQ_TABLE_LOCK(adev, irq_table_flags);
	पूर्ण

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);
	वापस 0;
पूर्ण

पूर्णांक amdgpu_dm_irq_resume_early(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक src;
	काष्ठा list_head *hnd_list_h, *hnd_list_l;
	अचिन्हित दीर्घ irq_table_flags;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	DRM_DEBUG_KMS("DM_IRQ: early resume\n");

	/* re-enable लघु pulse पूर्णांकerrupts HW पूर्णांकerrupt */
	क्रम (src = DC_IRQ_SOURCE_HPD1RX; src <= DC_IRQ_SOURCE_HPD6RX; src++) अणु
		hnd_list_l = &adev->dm.irq_handler_list_low_tab[src];
		hnd_list_h = &adev->dm.irq_handler_list_high_tab[src];
		अगर (!list_empty(hnd_list_l) || !list_empty(hnd_list_h))
			dc_पूर्णांकerrupt_set(adev->dm.dc, src, true);
	पूर्ण

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_dm_irq_resume_late(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक src;
	काष्ठा list_head *hnd_list_h, *hnd_list_l;
	अचिन्हित दीर्घ irq_table_flags;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	DRM_DEBUG_KMS("DM_IRQ: resume\n");

	/**
	 * Renable HW पूर्णांकerrupt  क्रम HPD and only since FLIP and VBLANK
	 * will be enabled from manage_dm_पूर्णांकerrupts on enable CRTC.
	 */
	क्रम (src = DC_IRQ_SOURCE_HPD1; src <= DC_IRQ_SOURCE_HPD6; src++) अणु
		hnd_list_l = &adev->dm.irq_handler_list_low_tab[src];
		hnd_list_h = &adev->dm.irq_handler_list_high_tab[src];
		अगर (!list_empty(hnd_list_l) || !list_empty(hnd_list_h))
			dc_पूर्णांकerrupt_set(adev->dm.dc, src, true);
	पूर्ण

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);
	वापस 0;
पूर्ण

/*
 * amdgpu_dm_irq_schedule_work - schedule all work items रेजिस्टरed क्रम the
 * "irq_source".
 */
अटल व्योम amdgpu_dm_irq_schedule_work(काष्ठा amdgpu_device *adev,
					क्रमागत dc_irq_source irq_source)
अणु
	काष्ठा  list_head *handler_list = &adev->dm.irq_handler_list_low_tab[irq_source];
	काष्ठा  amdgpu_dm_irq_handler_data *handler_data;
	bool    work_queued = false;

	अगर (list_empty(handler_list))
		वापस;

	list_क्रम_each_entry (handler_data, handler_list, list) अणु
		अगर (queue_work(प्रणाली_highpri_wq, &handler_data->work)) अणु
			work_queued = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!work_queued) अणु
		काष्ठा  amdgpu_dm_irq_handler_data *handler_data_add;
		/*get the amdgpu_dm_irq_handler_data of first item poपूर्णांकed by handler_list*/
		handler_data = container_of(handler_list->next, काष्ठा amdgpu_dm_irq_handler_data, list);

		/*allocate a new amdgpu_dm_irq_handler_data*/
		handler_data_add = kzalloc(माप(*handler_data), GFP_KERNEL);
		अगर (!handler_data_add) अणु
			DRM_ERROR("DM_IRQ: failed to allocate irq handler!\n");
			वापस;
		पूर्ण

		/*copy new amdgpu_dm_irq_handler_data members from handler_data*/
		handler_data_add->handler       = handler_data->handler;
		handler_data_add->handler_arg   = handler_data->handler_arg;
		handler_data_add->dm            = handler_data->dm;
		handler_data_add->irq_source    = irq_source;

		list_add_tail(&handler_data_add->list, handler_list);

		INIT_WORK(&handler_data_add->work, dm_irq_work_func);

		अगर (queue_work(प्रणाली_highpri_wq, &handler_data_add->work))
			DRM_DEBUG("Queued work for handling interrupt from "
				  "display for IRQ source %d\n",
				  irq_source);
		अन्यथा
			DRM_ERROR("Failed to queue work for handling interrupt "
				  "from display for IRQ source %d\n",
				  irq_source);
	पूर्ण
पूर्ण

/*
 * amdgpu_dm_irq_immediate_work
 * Callback high irq work immediately, करोn't send to work queue
 */
अटल व्योम amdgpu_dm_irq_immediate_work(काष्ठा amdgpu_device *adev,
					 क्रमागत dc_irq_source irq_source)
अणु
	काष्ठा amdgpu_dm_irq_handler_data *handler_data;
	अचिन्हित दीर्घ irq_table_flags;

	DM_IRQ_TABLE_LOCK(adev, irq_table_flags);

	list_क्रम_each_entry(handler_data,
			    &adev->dm.irq_handler_list_high_tab[irq_source],
			    list) अणु
		/* Call a subcomponent which रेजिस्टरed क्रम immediate
		 * पूर्णांकerrupt notअगरication */
		handler_data->handler(handler_data->handler_arg);
	पूर्ण

	DM_IRQ_TABLE_UNLOCK(adev, irq_table_flags);
पूर्ण

/**
 * amdgpu_dm_irq_handler - Generic DM IRQ handler
 * @adev: amdgpu base driver device containing the DM device
 * @source: Unused
 * @entry: Data about the triggered पूर्णांकerrupt
 *
 * Calls all रेजिस्टरed high irq work immediately, and schedules work क्रम low
 * irq. The DM IRQ table is used to find the corresponding handlers.
 */
अटल पूर्णांक amdgpu_dm_irq_handler(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_irq_src *source,
				 काष्ठा amdgpu_iv_entry *entry)
अणु

	क्रमागत dc_irq_source src =
		dc_पूर्णांकerrupt_to_irq_source(
			adev->dm.dc,
			entry->src_id,
			entry->src_data[0]);

	dc_पूर्णांकerrupt_ack(adev->dm.dc, src);

	/* Call high irq work immediately */
	amdgpu_dm_irq_immediate_work(adev, src);
	/*Schedule low_irq work */
	amdgpu_dm_irq_schedule_work(adev, src);

	वापस 0;
पूर्ण

अटल क्रमागत dc_irq_source amdgpu_dm_hpd_to_dal_irq_source(अचिन्हित type)
अणु
	चयन (type) अणु
	हाल AMDGPU_HPD_1:
		वापस DC_IRQ_SOURCE_HPD1;
	हाल AMDGPU_HPD_2:
		वापस DC_IRQ_SOURCE_HPD2;
	हाल AMDGPU_HPD_3:
		वापस DC_IRQ_SOURCE_HPD3;
	हाल AMDGPU_HPD_4:
		वापस DC_IRQ_SOURCE_HPD4;
	हाल AMDGPU_HPD_5:
		वापस DC_IRQ_SOURCE_HPD5;
	हाल AMDGPU_HPD_6:
		वापस DC_IRQ_SOURCE_HPD6;
	शेष:
		वापस DC_IRQ_SOURCE_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_dm_set_hpd_irq_state(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_irq_src *source,
				       अचिन्हित type,
				       क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	क्रमागत dc_irq_source src = amdgpu_dm_hpd_to_dal_irq_source(type);
	bool st = (state == AMDGPU_IRQ_STATE_ENABLE);

	dc_पूर्णांकerrupt_set(adev->dm.dc, src, st);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dm_irq_state(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_irq_src *source,
			       अचिन्हित crtc_id,
			       क्रमागत amdgpu_पूर्णांकerrupt_state state,
			       स्थिर क्रमागत irq_type dal_irq_type,
			       स्थिर अक्षर *func)
अणु
	bool st;
	क्रमागत dc_irq_source irq_source;

	काष्ठा amdgpu_crtc *acrtc = adev->mode_info.crtcs[crtc_id];

	अगर (!acrtc) अणु
		DRM_ERROR(
			"%s: crtc is NULL at id :%d\n",
			func,
			crtc_id);
		वापस 0;
	पूर्ण

	अगर (acrtc->otg_inst == -1)
		वापस 0;

	irq_source = dal_irq_type + acrtc->otg_inst;

	st = (state == AMDGPU_IRQ_STATE_ENABLE);

	dc_पूर्णांकerrupt_set(adev->dm.dc, irq_source, st);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_dm_set_pflip_irq_state(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_irq_src *source,
					 अचिन्हित crtc_id,
					 क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस dm_irq_state(
		adev,
		source,
		crtc_id,
		state,
		IRQ_TYPE_PFLIP,
		__func__);
पूर्ण

अटल पूर्णांक amdgpu_dm_set_crtc_irq_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित crtc_id,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस dm_irq_state(
		adev,
		source,
		crtc_id,
		state,
		IRQ_TYPE_VBLANK,
		__func__);
पूर्ण

अटल पूर्णांक amdgpu_dm_set_vline0_irq_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित पूर्णांक crtc_id,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस dm_irq_state(
		adev,
		source,
		crtc_id,
		state,
		IRQ_TYPE_VLINE0,
		__func__);
पूर्ण

अटल पूर्णांक amdgpu_dm_set_vupdate_irq_state(काष्ठा amdgpu_device *adev,
					   काष्ठा amdgpu_irq_src *source,
					   अचिन्हित पूर्णांक crtc_id,
					   क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस dm_irq_state(
		adev,
		source,
		crtc_id,
		state,
		IRQ_TYPE_VUPDATE,
		__func__);
पूर्ण

अटल पूर्णांक amdgpu_dm_set_dmub_trace_irq_state(काष्ठा amdgpu_device *adev,
					   काष्ठा amdgpu_irq_src *source,
					   अचिन्हित पूर्णांक type,
					   क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	क्रमागत dc_irq_source irq_source = DC_IRQ_SOURCE_DMCUB_OUTBOX0;
	bool st = (state == AMDGPU_IRQ_STATE_ENABLE);

	dc_पूर्णांकerrupt_set(adev->dm.dc, irq_source, st);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dm_crtc_irq_funcs = अणु
	.set = amdgpu_dm_set_crtc_irq_state,
	.process = amdgpu_dm_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dm_vline0_irq_funcs = अणु
	.set = amdgpu_dm_set_vline0_irq_state,
	.process = amdgpu_dm_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dm_vupdate_irq_funcs = अणु
	.set = amdgpu_dm_set_vupdate_irq_state,
	.process = amdgpu_dm_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dm_dmub_trace_irq_funcs = अणु
	.set = amdgpu_dm_set_dmub_trace_irq_state,
	.process = amdgpu_dm_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dm_pageflip_irq_funcs = अणु
	.set = amdgpu_dm_set_pflip_irq_state,
	.process = amdgpu_dm_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs dm_hpd_irq_funcs = अणु
	.set = amdgpu_dm_set_hpd_irq_state,
	.process = amdgpu_dm_irq_handler,
पूर्ण;

व्योम amdgpu_dm_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु

	adev->crtc_irq.num_types = adev->mode_info.num_crtc;
	adev->crtc_irq.funcs = &dm_crtc_irq_funcs;

	adev->vline0_irq.num_types = adev->mode_info.num_crtc;
	adev->vline0_irq.funcs = &dm_vline0_irq_funcs;

	adev->vupdate_irq.num_types = adev->mode_info.num_crtc;
	adev->vupdate_irq.funcs = &dm_vupdate_irq_funcs;

	adev->dmub_trace_irq.num_types = 1;
	adev->dmub_trace_irq.funcs = &dm_dmub_trace_irq_funcs;

	adev->pageflip_irq.num_types = adev->mode_info.num_crtc;
	adev->pageflip_irq.funcs = &dm_pageflip_irq_funcs;

	adev->hpd_irq.num_types = adev->mode_info.num_hpd;
	adev->hpd_irq.funcs = &dm_hpd_irq_funcs;
पूर्ण

/**
 * amdgpu_dm_hpd_init - hpd setup callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup the hpd pins used by the card (evergreen+).
 * Enable the pin, set the polarity, and enable the hpd पूर्णांकerrupts.
 */
व्योम amdgpu_dm_hpd_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
				to_amdgpu_dm_connector(connector);

		स्थिर काष्ठा dc_link *dc_link = amdgpu_dm_connector->dc_link;

		अगर (DC_IRQ_SOURCE_INVALID != dc_link->irq_source_hpd) अणु
			dc_पूर्णांकerrupt_set(adev->dm.dc,
					dc_link->irq_source_hpd,
					true);
		पूर्ण

		अगर (DC_IRQ_SOURCE_INVALID != dc_link->irq_source_hpd_rx) अणु
			dc_पूर्णांकerrupt_set(adev->dm.dc,
					dc_link->irq_source_hpd_rx,
					true);
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण

/**
 * amdgpu_dm_hpd_fini - hpd tear करोwn callback.
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tear करोwn the hpd pins used by the card (evergreen+).
 * Disable the hpd पूर्णांकerrupts.
 */
व्योम amdgpu_dm_hpd_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
				to_amdgpu_dm_connector(connector);
		स्थिर काष्ठा dc_link *dc_link = amdgpu_dm_connector->dc_link;

		dc_पूर्णांकerrupt_set(adev->dm.dc, dc_link->irq_source_hpd, false);

		अगर (DC_IRQ_SOURCE_INVALID != dc_link->irq_source_hpd_rx) अणु
			dc_पूर्णांकerrupt_set(adev->dm.dc,
					dc_link->irq_source_hpd_rx,
					false);
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण
