<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2019 IBM Corp.
#समावेश <linux/idr.h>
#समावेश "ocxl_internal.h"

अटल काष्ठा ocxl_fn *ocxl_fn_get(काष्ठा ocxl_fn *fn)
अणु
	वापस (get_device(&fn->dev) == शून्य) ? शून्य : fn;
पूर्ण

अटल व्योम ocxl_fn_put(काष्ठा ocxl_fn *fn)
अणु
	put_device(&fn->dev);
पूर्ण

अटल काष्ठा ocxl_afu *alloc_afu(काष्ठा ocxl_fn *fn)
अणु
	काष्ठा ocxl_afu *afu;

	afu = kzalloc(माप(काष्ठा ocxl_afu), GFP_KERNEL);
	अगर (!afu)
		वापस शून्य;

	kref_init(&afu->kref);
	mutex_init(&afu->contexts_lock);
	mutex_init(&afu->afu_control_lock);
	idr_init(&afu->contexts_idr);
	afu->fn = fn;
	ocxl_fn_get(fn);
	वापस afu;
पूर्ण

अटल व्योम मुक्त_afu(काष्ठा kref *kref)
अणु
	काष्ठा ocxl_afu *afu = container_of(kref, काष्ठा ocxl_afu, kref);

	idr_destroy(&afu->contexts_idr);
	ocxl_fn_put(afu->fn);
	kमुक्त(afu);
पूर्ण

व्योम ocxl_afu_get(काष्ठा ocxl_afu *afu)
अणु
	kref_get(&afu->kref);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_get);

व्योम ocxl_afu_put(काष्ठा ocxl_afu *afu)
अणु
	kref_put(&afu->kref, मुक्त_afu);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_put);

अटल पूर्णांक assign_afu_actag(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा ocxl_fn *fn = afu->fn;
	पूर्णांक actag_count, actag_offset;
	काष्ठा pci_dev *pci_dev = to_pci_dev(fn->dev.parent);

	/*
	 * अगर there were not enough actags क्रम the function, each afu
	 * reduces its count as well
	 */
	actag_count = afu->config.actag_supported *
		fn->actag_enabled / fn->actag_supported;
	actag_offset = ocxl_actag_afu_alloc(fn, actag_count);
	अगर (actag_offset < 0) अणु
		dev_err(&pci_dev->dev, "Can't allocate %d actags for AFU: %d\n",
			actag_count, actag_offset);
		वापस actag_offset;
	पूर्ण
	afu->actag_base = fn->actag_base + actag_offset;
	afu->actag_enabled = actag_count;

	ocxl_config_set_afu_actag(pci_dev, afu->config.dvsec_afu_control_pos,
				afu->actag_base, afu->actag_enabled);
	dev_dbg(&pci_dev->dev, "actag base=%d enabled=%d\n",
		afu->actag_base, afu->actag_enabled);
	वापस 0;
पूर्ण

अटल व्योम reclaim_afu_actag(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा ocxl_fn *fn = afu->fn;
	पूर्णांक start_offset, size;

	start_offset = afu->actag_base - fn->actag_base;
	size = afu->actag_enabled;
	ocxl_actag_afu_मुक्त(afu->fn, start_offset, size);
पूर्ण

अटल पूर्णांक assign_afu_pasid(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा ocxl_fn *fn = afu->fn;
	पूर्णांक pasid_count, pasid_offset;
	काष्ठा pci_dev *pci_dev = to_pci_dev(fn->dev.parent);

	/*
	 * We only support the हाल where the function configuration
	 * requested enough PASIDs to cover all AFUs.
	 */
	pasid_count = 1 << afu->config.pasid_supported_log;
	pasid_offset = ocxl_pasid_afu_alloc(fn, pasid_count);
	अगर (pasid_offset < 0) अणु
		dev_err(&pci_dev->dev, "Can't allocate %d PASIDs for AFU: %d\n",
			pasid_count, pasid_offset);
		वापस pasid_offset;
	पूर्ण
	afu->pasid_base = fn->pasid_base + pasid_offset;
	afu->pasid_count = 0;
	afu->pasid_max = pasid_count;

	ocxl_config_set_afu_pasid(pci_dev, afu->config.dvsec_afu_control_pos,
				afu->pasid_base,
				afu->config.pasid_supported_log);
	dev_dbg(&pci_dev->dev, "PASID base=%d, enabled=%d\n",
		afu->pasid_base, pasid_count);
	वापस 0;
पूर्ण

अटल व्योम reclaim_afu_pasid(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा ocxl_fn *fn = afu->fn;
	पूर्णांक start_offset, size;

	start_offset = afu->pasid_base - fn->pasid_base;
	size = 1 << afu->config.pasid_supported_log;
	ocxl_pasid_afu_मुक्त(afu->fn, start_offset, size);
पूर्ण

अटल पूर्णांक reserve_fn_bar(काष्ठा ocxl_fn *fn, पूर्णांक bar)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(fn->dev.parent);
	पूर्णांक rc, idx;

	अगर (bar != 0 && bar != 2 && bar != 4)
		वापस -EINVAL;

	idx = bar >> 1;
	अगर (fn->bar_used[idx]++ == 0) अणु
		rc = pci_request_region(dev, bar, "ocxl");
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम release_fn_bar(काष्ठा ocxl_fn *fn, पूर्णांक bar)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(fn->dev.parent);
	पूर्णांक idx;

	अगर (bar != 0 && bar != 2 && bar != 4)
		वापस;

	idx = bar >> 1;
	अगर (--fn->bar_used[idx] == 0)
		pci_release_region(dev, bar);
	WARN_ON(fn->bar_used[idx] < 0);
पूर्ण

अटल पूर्णांक map_mmio_areas(काष्ठा ocxl_afu *afu)
अणु
	पूर्णांक rc;
	काष्ठा pci_dev *pci_dev = to_pci_dev(afu->fn->dev.parent);

	rc = reserve_fn_bar(afu->fn, afu->config.global_mmio_bar);
	अगर (rc)
		वापस rc;

	rc = reserve_fn_bar(afu->fn, afu->config.pp_mmio_bar);
	अगर (rc) अणु
		release_fn_bar(afu->fn, afu->config.global_mmio_bar);
		वापस rc;
	पूर्ण

	afu->global_mmio_start =
		pci_resource_start(pci_dev, afu->config.global_mmio_bar) +
		afu->config.global_mmio_offset;
	afu->pp_mmio_start =
		pci_resource_start(pci_dev, afu->config.pp_mmio_bar) +
		afu->config.pp_mmio_offset;

	afu->global_mmio_ptr = ioremap(afu->global_mmio_start,
				afu->config.global_mmio_size);
	अगर (!afu->global_mmio_ptr) अणु
		release_fn_bar(afu->fn, afu->config.pp_mmio_bar);
		release_fn_bar(afu->fn, afu->config.global_mmio_bar);
		dev_err(&pci_dev->dev, "Error mapping global mmio area\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Leave an empty page between the per-process mmio area and
	 * the AFU पूर्णांकerrupt mappings
	 */
	afu->irq_base_offset = afu->config.pp_mmio_stride + PAGE_SIZE;
	वापस 0;
पूर्ण

अटल व्योम unmap_mmio_areas(काष्ठा ocxl_afu *afu)
अणु
	अगर (afu->global_mmio_ptr) अणु
		iounmap(afu->global_mmio_ptr);
		afu->global_mmio_ptr = शून्य;
	पूर्ण
	afu->global_mmio_start = 0;
	afu->pp_mmio_start = 0;
	release_fn_bar(afu->fn, afu->config.pp_mmio_bar);
	release_fn_bar(afu->fn, afu->config.global_mmio_bar);
पूर्ण

अटल पूर्णांक configure_afu(काष्ठा ocxl_afu *afu, u8 afu_idx, काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	rc = ocxl_config_पढ़ो_afu(dev, &afu->fn->config, &afu->config, afu_idx);
	अगर (rc)
		वापस rc;

	rc = assign_afu_actag(afu);
	अगर (rc)
		वापस rc;

	rc = assign_afu_pasid(afu);
	अगर (rc)
		जाओ err_मुक्त_actag;

	rc = map_mmio_areas(afu);
	अगर (rc)
		जाओ err_मुक्त_pasid;

	वापस 0;

err_मुक्त_pasid:
	reclaim_afu_pasid(afu);
err_मुक्त_actag:
	reclaim_afu_actag(afu);
	वापस rc;
पूर्ण

अटल व्योम deconfigure_afu(काष्ठा ocxl_afu *afu)
अणु
	unmap_mmio_areas(afu);
	reclaim_afu_pasid(afu);
	reclaim_afu_actag(afu);
पूर्ण

अटल पूर्णांक activate_afu(काष्ठा pci_dev *dev, काष्ठा ocxl_afu *afu)
अणु
	ocxl_config_set_afu_state(dev, afu->config.dvsec_afu_control_pos, 1);

	वापस 0;
पूर्ण

अटल व्योम deactivate_afu(काष्ठा ocxl_afu *afu)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(afu->fn->dev.parent);

	ocxl_config_set_afu_state(dev, afu->config.dvsec_afu_control_pos, 0);
पूर्ण

अटल पूर्णांक init_afu(काष्ठा pci_dev *dev, काष्ठा ocxl_fn *fn, u8 afu_idx)
अणु
	पूर्णांक rc;
	काष्ठा ocxl_afu *afu;

	afu = alloc_afu(fn);
	अगर (!afu)
		वापस -ENOMEM;

	rc = configure_afu(afu, afu_idx, dev);
	अगर (rc) अणु
		ocxl_afu_put(afu);
		वापस rc;
	पूर्ण

	rc = activate_afu(dev, afu);
	अगर (rc) अणु
		deconfigure_afu(afu);
		ocxl_afu_put(afu);
		वापस rc;
	पूर्ण

	list_add_tail(&afu->list, &fn->afu_list);

	वापस 0;
पूर्ण

अटल व्योम हटाओ_afu(काष्ठा ocxl_afu *afu)
अणु
	list_del(&afu->list);
	ocxl_context_detach_all(afu);
	deactivate_afu(afu);
	deconfigure_afu(afu);
	ocxl_afu_put(afu); // matches the implicit get in alloc_afu
पूर्ण

अटल काष्ठा ocxl_fn *alloc_function(व्योम)
अणु
	काष्ठा ocxl_fn *fn;

	fn = kzalloc(माप(काष्ठा ocxl_fn), GFP_KERNEL);
	अगर (!fn)
		वापस शून्य;

	INIT_LIST_HEAD(&fn->afu_list);
	INIT_LIST_HEAD(&fn->pasid_list);
	INIT_LIST_HEAD(&fn->actag_list);

	वापस fn;
पूर्ण

अटल व्योम मुक्त_function(काष्ठा ocxl_fn *fn)
अणु
	WARN_ON(!list_empty(&fn->afu_list));
	WARN_ON(!list_empty(&fn->pasid_list));
	kमुक्त(fn);
पूर्ण

अटल व्योम मुक्त_function_dev(काष्ठा device *dev)
अणु
	काष्ठा ocxl_fn *fn = container_of(dev, काष्ठा ocxl_fn, dev);

	मुक्त_function(fn);
पूर्ण

अटल पूर्णांक set_function_device(काष्ठा ocxl_fn *fn, काष्ठा pci_dev *dev)
अणु
	fn->dev.parent = &dev->dev;
	fn->dev.release = मुक्त_function_dev;
	वापस dev_set_name(&fn->dev, "ocxlfn.%s", dev_name(&dev->dev));
पूर्ण

अटल पूर्णांक assign_function_actag(काष्ठा ocxl_fn *fn)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(fn->dev.parent);
	u16 base, enabled, supported;
	पूर्णांक rc;

	rc = ocxl_config_get_actag_info(dev, &base, &enabled, &supported);
	अगर (rc)
		वापस rc;

	fn->actag_base = base;
	fn->actag_enabled = enabled;
	fn->actag_supported = supported;

	ocxl_config_set_actag(dev, fn->config.dvsec_function_pos,
			fn->actag_base,	fn->actag_enabled);
	dev_dbg(&fn->dev, "actag range starting at %d, enabled %d\n",
		fn->actag_base, fn->actag_enabled);
	वापस 0;
पूर्ण

अटल पूर्णांक set_function_pasid(काष्ठा ocxl_fn *fn)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(fn->dev.parent);
	पूर्णांक rc, desired_count, max_count;

	/* A function may not require any PASID */
	अगर (fn->config.max_pasid_log < 0)
		वापस 0;

	rc = ocxl_config_get_pasid_info(dev, &max_count);
	अगर (rc)
		वापस rc;

	desired_count = 1 << fn->config.max_pasid_log;

	अगर (desired_count > max_count) अणु
		dev_err(&fn->dev,
			"Function requires more PASIDs than is available (%d vs. %d)\n",
			desired_count, max_count);
		वापस -ENOSPC;
	पूर्ण

	fn->pasid_base = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक configure_function(काष्ठा ocxl_fn *fn, काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	rc = pci_enable_device(dev);
	अगर (rc) अणु
		dev_err(&dev->dev, "pci_enable_device failed: %d\n", rc);
		वापस rc;
	पूर्ण

	/*
	 * Once it has been confirmed to work on our hardware, we
	 * should reset the function, to क्रमce the adapter to restart
	 * from scratch.
	 * A function reset would also reset all its AFUs.
	 *
	 * Some hपूर्णांकs क्रम implementation:
	 *
	 * - there's not status bit to know when the reset is करोne. We
	 *   should try पढ़ोing the config space to know when it's
	 *   करोne.
	 * - probably something like:
	 *	Reset
	 *	रुको 100ms
	 *	issue config पढ़ो
	 *	allow device up to 1 sec to वापस success on config
	 *	पढ़ो beक्रमe declaring it broken
	 *
	 * Some shared logic on the card (CFG, TLX) won't be reset, so
	 * there's no guarantee that it will be enough.
	 */
	rc = ocxl_config_पढ़ो_function(dev, &fn->config);
	अगर (rc)
		वापस rc;

	rc = set_function_device(fn, dev);
	अगर (rc)
		वापस rc;

	rc = assign_function_actag(fn);
	अगर (rc)
		वापस rc;

	rc = set_function_pasid(fn);
	अगर (rc)
		वापस rc;

	rc = ocxl_link_setup(dev, 0, &fn->link);
	अगर (rc)
		वापस rc;

	rc = ocxl_config_set_TL(dev, fn->config.dvsec_tl_pos);
	अगर (rc) अणु
		ocxl_link_release(dev, fn->link);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम deconfigure_function(काष्ठा ocxl_fn *fn)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(fn->dev.parent);

	ocxl_link_release(dev, fn->link);
	pci_disable_device(dev);
पूर्ण

अटल काष्ठा ocxl_fn *init_function(काष्ठा pci_dev *dev)
अणु
	काष्ठा ocxl_fn *fn;
	पूर्णांक rc;

	fn = alloc_function();
	अगर (!fn)
		वापस ERR_PTR(-ENOMEM);

	rc = configure_function(fn, dev);
	अगर (rc) अणु
		मुक्त_function(fn);
		वापस ERR_PTR(rc);
	पूर्ण

	rc = device_रेजिस्टर(&fn->dev);
	अगर (rc) अणु
		deconfigure_function(fn);
		put_device(&fn->dev);
		वापस ERR_PTR(rc);
	पूर्ण
	वापस fn;
पूर्ण

// Device detection & initialisation

काष्ठा ocxl_fn *ocxl_function_खोलो(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc, afu_count = 0;
	u8 afu;
	काष्ठा ocxl_fn *fn;

	अगर (!radix_enabled()) अणु
		dev_err(&dev->dev, "Unsupported memory model (hash)\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	fn = init_function(dev);
	अगर (IS_ERR(fn)) अणु
		dev_err(&dev->dev, "function init failed: %li\n",
			PTR_ERR(fn));
		वापस fn;
	पूर्ण

	क्रम (afu = 0; afu <= fn->config.max_afu_index; afu++) अणु
		rc = ocxl_config_check_afu_index(dev, &fn->config, afu);
		अगर (rc > 0) अणु
			rc = init_afu(dev, fn, afu);
			अगर (rc) अणु
				dev_err(&dev->dev,
					"Can't initialize AFU index %d\n", afu);
				जारी;
			पूर्ण
			afu_count++;
		पूर्ण
	पूर्ण
	dev_info(&dev->dev, "%d AFU(s) configured\n", afu_count);
	वापस fn;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_function_खोलो);

काष्ठा list_head *ocxl_function_afu_list(काष्ठा ocxl_fn *fn)
अणु
	वापस &fn->afu_list;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_function_afu_list);

काष्ठा ocxl_afu *ocxl_function_fetch_afu(काष्ठा ocxl_fn *fn, u8 afu_idx)
अणु
	काष्ठा ocxl_afu *afu;

	list_क्रम_each_entry(afu, &fn->afu_list, list) अणु
		अगर (afu->config.idx == afu_idx)
			वापस afu;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_function_fetch_afu);

स्थिर काष्ठा ocxl_fn_config *ocxl_function_config(काष्ठा ocxl_fn *fn)
अणु
	वापस &fn->config;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_function_config);

व्योम ocxl_function_बंद(काष्ठा ocxl_fn *fn)
अणु
	काष्ठा ocxl_afu *afu, *पंचांगp;

	list_क्रम_each_entry_safe(afu, पंचांगp, &fn->afu_list, list) अणु
		हटाओ_afu(afu);
	पूर्ण

	deconfigure_function(fn);
	device_unरेजिस्टर(&fn->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_function_बंद);

// AFU Metadata

काष्ठा ocxl_afu_config *ocxl_afu_config(काष्ठा ocxl_afu *afu)
अणु
	वापस &afu->config;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_config);

व्योम ocxl_afu_set_निजी(काष्ठा ocxl_afu *afu, व्योम *निजी)
अणु
	afu->निजी = निजी;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_set_निजी);

व्योम *ocxl_afu_get_निजी(काष्ठा ocxl_afu *afu)
अणु
	अगर (afu)
		वापस afu->निजी;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ocxl_afu_get_निजी);
