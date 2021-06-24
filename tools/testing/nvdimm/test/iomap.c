<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/memremap.h>
#समावेश <linux/rculist.h>
#समावेश <linux/export.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश "nfit_test.h"

अटल LIST_HEAD(iomap_head);

अटल काष्ठा iomap_ops अणु
	nfit_test_lookup_fn nfit_test_lookup;
	nfit_test_evaluate_dsm_fn evaluate_dsm;
	काष्ठा list_head list;
पूर्ण iomap_ops = अणु
	.list = LIST_HEAD_INIT(iomap_ops.list),
पूर्ण;

व्योम nfit_test_setup(nfit_test_lookup_fn lookup,
		nfit_test_evaluate_dsm_fn evaluate)
अणु
	iomap_ops.nfit_test_lookup = lookup;
	iomap_ops.evaluate_dsm = evaluate;
	list_add_rcu(&iomap_ops.list, &iomap_head);
पूर्ण
EXPORT_SYMBOL(nfit_test_setup);

व्योम nfit_test_tearकरोwn(व्योम)
अणु
	list_del_rcu(&iomap_ops.list);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(nfit_test_tearकरोwn);

अटल काष्ठा nfit_test_resource *__get_nfit_res(resource_माप_प्रकार resource)
अणु
	काष्ठा iomap_ops *ops;

	ops = list_first_or_null_rcu(&iomap_head, typeof(*ops), list);
	अगर (ops)
		वापस ops->nfit_test_lookup(resource);
	वापस शून्य;
पूर्ण

काष्ठा nfit_test_resource *get_nfit_res(resource_माप_प्रकार resource)
अणु
	काष्ठा nfit_test_resource *res;

	rcu_पढ़ो_lock();
	res = __get_nfit_res(resource);
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण
EXPORT_SYMBOL(get_nfit_res);

अटल व्योम __iomem *__nfit_test_ioremap(resource_माप_प्रकार offset, अचिन्हित दीर्घ size,
		व्योम __iomem *(*fallback_fn)(resource_माप_प्रकार, अचिन्हित दीर्घ))
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res(offset);

	अगर (nfit_res)
		वापस (व्योम __iomem *) nfit_res->buf + offset
			- nfit_res->res.start;
	वापस fallback_fn(offset, size);
पूर्ण

व्योम __iomem *__wrap_devm_ioremap(काष्ठा device *dev,
		resource_माप_प्रकार offset, अचिन्हित दीर्घ size)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res(offset);

	अगर (nfit_res)
		वापस (व्योम __iomem *) nfit_res->buf + offset
			- nfit_res->res.start;
	वापस devm_ioremap(dev, offset, size);
पूर्ण
EXPORT_SYMBOL(__wrap_devm_ioremap);

व्योम *__wrap_devm_memremap(काष्ठा device *dev, resource_माप_प्रकार offset,
		माप_प्रकार size, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res(offset);

	अगर (nfit_res)
		वापस nfit_res->buf + offset - nfit_res->res.start;
	वापस devm_memremap(dev, offset, size, flags);
पूर्ण
EXPORT_SYMBOL(__wrap_devm_memremap);

अटल व्योम nfit_test_समाप्त(व्योम *_pgmap)
अणु
	काष्ठा dev_pagemap *pgmap = _pgmap;

	WARN_ON(!pgmap || !pgmap->ref);

	अगर (pgmap->ops && pgmap->ops->समाप्त)
		pgmap->ops->समाप्त(pgmap);
	अन्यथा
		percpu_ref_समाप्त(pgmap->ref);

	अगर (pgmap->ops && pgmap->ops->cleanup) अणु
		pgmap->ops->cleanup(pgmap);
	पूर्ण अन्यथा अणु
		रुको_क्रम_completion(&pgmap->करोne);
		percpu_ref_निकास(pgmap->ref);
	पूर्ण
पूर्ण

अटल व्योम dev_pagemap_percpu_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा dev_pagemap *pgmap =
		container_of(ref, काष्ठा dev_pagemap, पूर्णांकernal_ref);

	complete(&pgmap->करोne);
पूर्ण

व्योम *__wrap_devm_memremap_pages(काष्ठा device *dev, काष्ठा dev_pagemap *pgmap)
अणु
	पूर्णांक error;
	resource_माप_प्रकार offset = pgmap->range.start;
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res(offset);

	अगर (!nfit_res)
		वापस devm_memremap_pages(dev, pgmap);

	अगर (!pgmap->ref) अणु
		अगर (pgmap->ops && (pgmap->ops->समाप्त || pgmap->ops->cleanup))
			वापस ERR_PTR(-EINVAL);

		init_completion(&pgmap->करोne);
		error = percpu_ref_init(&pgmap->पूर्णांकernal_ref,
				dev_pagemap_percpu_release, 0, GFP_KERNEL);
		अगर (error)
			वापस ERR_PTR(error);
		pgmap->ref = &pgmap->पूर्णांकernal_ref;
	पूर्ण अन्यथा अणु
		अगर (!pgmap->ops || !pgmap->ops->समाप्त || !pgmap->ops->cleanup) अणु
			WARN(1, "Missing reference count teardown definition\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	error = devm_add_action_or_reset(dev, nfit_test_समाप्त, pgmap);
	अगर (error)
		वापस ERR_PTR(error);
	वापस nfit_res->buf + offset - nfit_res->res.start;
पूर्ण
EXPORT_SYMBOL_GPL(__wrap_devm_memremap_pages);

pfn_t __wrap_phys_to_pfn_t(phys_addr_t addr, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res(addr);

	अगर (nfit_res)
		flags &= ~PFN_MAP;
        वापस phys_to_pfn_t(addr, flags);
पूर्ण
EXPORT_SYMBOL(__wrap_phys_to_pfn_t);

व्योम *__wrap_memremap(resource_माप_प्रकार offset, माप_प्रकार size,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res(offset);

	अगर (nfit_res)
		वापस nfit_res->buf + offset - nfit_res->res.start;
	वापस memremap(offset, size, flags);
पूर्ण
EXPORT_SYMBOL(__wrap_memremap);

व्योम __wrap_devm_memunmap(काष्ठा device *dev, व्योम *addr)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res((दीर्घ) addr);

	अगर (nfit_res)
		वापस;
	वापस devm_memunmap(dev, addr);
पूर्ण
EXPORT_SYMBOL(__wrap_devm_memunmap);

व्योम __iomem *__wrap_ioremap(resource_माप_प्रकार offset, अचिन्हित दीर्घ size)
अणु
	वापस __nfit_test_ioremap(offset, size, ioremap);
पूर्ण
EXPORT_SYMBOL(__wrap_ioremap);

व्योम __iomem *__wrap_ioremap_wc(resource_माप_प्रकार offset, अचिन्हित दीर्घ size)
अणु
	वापस __nfit_test_ioremap(offset, size, ioremap_wc);
पूर्ण
EXPORT_SYMBOL(__wrap_ioremap_wc);

व्योम __wrap_iounmap(अस्थिर व्योम __iomem *addr)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res((दीर्घ) addr);
	अगर (nfit_res)
		वापस;
	वापस iounmap(addr);
पूर्ण
EXPORT_SYMBOL(__wrap_iounmap);

व्योम __wrap_memunmap(व्योम *addr)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res((दीर्घ) addr);

	अगर (nfit_res)
		वापस;
	वापस memunmap(addr);
पूर्ण
EXPORT_SYMBOL(__wrap_memunmap);

अटल bool nfit_test_release_region(काष्ठा device *dev,
		काष्ठा resource *parent, resource_माप_प्रकार start,
		resource_माप_प्रकार n);

अटल व्योम nfit_devres_release(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा resource *res = *((काष्ठा resource **) data);

	WARN_ON(!nfit_test_release_region(शून्य, &iomem_resource, res->start,
			resource_size(res)));
पूर्ण

अटल पूर्णांक match(काष्ठा device *dev, व्योम *__res, व्योम *match_data)
अणु
	काष्ठा resource *res = *((काष्ठा resource **) __res);
	resource_माप_प्रकार start = *((resource_माप_प्रकार *) match_data);

	वापस res->start == start;
पूर्ण

अटल bool nfit_test_release_region(काष्ठा device *dev,
		काष्ठा resource *parent, resource_माप_प्रकार start,
		resource_माप_प्रकार n)
अणु
	अगर (parent == &iomem_resource) अणु
		काष्ठा nfit_test_resource *nfit_res = get_nfit_res(start);

		अगर (nfit_res) अणु
			काष्ठा nfit_test_request *req;
			काष्ठा resource *res = शून्य;

			अगर (dev) अणु
				devres_release(dev, nfit_devres_release, match,
						&start);
				वापस true;
			पूर्ण

			spin_lock(&nfit_res->lock);
			list_क्रम_each_entry(req, &nfit_res->requests, list)
				अगर (req->res.start == start) अणु
					res = &req->res;
					list_del(&req->list);
					अवरोध;
				पूर्ण
			spin_unlock(&nfit_res->lock);

			WARN(!res || resource_size(res) != n,
					"%s: start: %llx n: %llx mismatch: %pr\n",
						__func__, start, n, res);
			अगर (res)
				kमुक्त(req);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा resource *nfit_test_request_region(काष्ठा device *dev,
		काष्ठा resource *parent, resource_माप_प्रकार start,
		resource_माप_प्रकार n, स्थिर अक्षर *name, पूर्णांक flags)
अणु
	काष्ठा nfit_test_resource *nfit_res;

	अगर (parent == &iomem_resource) अणु
		nfit_res = get_nfit_res(start);
		अगर (nfit_res) अणु
			काष्ठा nfit_test_request *req;
			काष्ठा resource *res = शून्य;

			अगर (start + n > nfit_res->res.start
					+ resource_size(&nfit_res->res)) अणु
				pr_debug("%s: start: %llx n: %llx overflow: %pr\n",
						__func__, start, n,
						&nfit_res->res);
				वापस शून्य;
			पूर्ण

			spin_lock(&nfit_res->lock);
			list_क्रम_each_entry(req, &nfit_res->requests, list)
				अगर (start == req->res.start) अणु
					res = &req->res;
					अवरोध;
				पूर्ण
			spin_unlock(&nfit_res->lock);

			अगर (res) अणु
				WARN(1, "%pr already busy\n", res);
				वापस शून्य;
			पूर्ण

			req = kzalloc(माप(*req), GFP_KERNEL);
			अगर (!req)
				वापस शून्य;
			INIT_LIST_HEAD(&req->list);
			res = &req->res;

			res->start = start;
			res->end = start + n - 1;
			res->name = name;
			res->flags = resource_type(parent);
			res->flags |= IORESOURCE_BUSY | flags;
			spin_lock(&nfit_res->lock);
			list_add(&req->list, &nfit_res->requests);
			spin_unlock(&nfit_res->lock);

			अगर (dev) अणु
				काष्ठा resource **d;

				d = devres_alloc(nfit_devres_release,
						माप(काष्ठा resource *),
						GFP_KERNEL);
				अगर (!d)
					वापस शून्य;
				*d = res;
				devres_add(dev, d);
			पूर्ण

			pr_debug("%s: %pr\n", __func__, res);
			वापस res;
		पूर्ण
	पूर्ण
	अगर (dev)
		वापस __devm_request_region(dev, parent, start, n, name);
	वापस __request_region(parent, start, n, name, flags);
पूर्ण

काष्ठा resource *__wrap___request_region(काष्ठा resource *parent,
		resource_माप_प्रकार start, resource_माप_प्रकार n, स्थिर अक्षर *name,
		पूर्णांक flags)
अणु
	वापस nfit_test_request_region(शून्य, parent, start, n, name, flags);
पूर्ण
EXPORT_SYMBOL(__wrap___request_region);

पूर्णांक __wrap_insert_resource(काष्ठा resource *parent, काष्ठा resource *res)
अणु
	अगर (get_nfit_res(res->start))
		वापस 0;
	वापस insert_resource(parent, res);
पूर्ण
EXPORT_SYMBOL(__wrap_insert_resource);

पूर्णांक __wrap_हटाओ_resource(काष्ठा resource *res)
अणु
	अगर (get_nfit_res(res->start))
		वापस 0;
	वापस हटाओ_resource(res);
पूर्ण
EXPORT_SYMBOL(__wrap_हटाओ_resource);

काष्ठा resource *__wrap___devm_request_region(काष्ठा device *dev,
		काष्ठा resource *parent, resource_माप_प्रकार start,
		resource_माप_प्रकार n, स्थिर अक्षर *name)
अणु
	अगर (!dev)
		वापस शून्य;
	वापस nfit_test_request_region(dev, parent, start, n, name, 0);
पूर्ण
EXPORT_SYMBOL(__wrap___devm_request_region);

व्योम __wrap___release_region(काष्ठा resource *parent, resource_माप_प्रकार start,
		resource_माप_प्रकार n)
अणु
	अगर (!nfit_test_release_region(शून्य, parent, start, n))
		__release_region(parent, start, n);
पूर्ण
EXPORT_SYMBOL(__wrap___release_region);

व्योम __wrap___devm_release_region(काष्ठा device *dev, काष्ठा resource *parent,
		resource_माप_प्रकार start, resource_माप_प्रकार n)
अणु
	अगर (!nfit_test_release_region(dev, parent, start, n))
		__devm_release_region(dev, parent, start, n);
पूर्ण
EXPORT_SYMBOL(__wrap___devm_release_region);

acpi_status __wrap_acpi_evaluate_object(acpi_handle handle, acpi_string path,
		काष्ठा acpi_object_list *p, काष्ठा acpi_buffer *buf)
अणु
	काष्ठा nfit_test_resource *nfit_res = get_nfit_res((दीर्घ) handle);
	जोड़ acpi_object **obj;

	अगर (!nfit_res || म_भेद(path, "_FIT") || !buf)
		वापस acpi_evaluate_object(handle, path, p, buf);

	obj = nfit_res->buf;
	buf->length = माप(जोड़ acpi_object);
	buf->poपूर्णांकer = *obj;
	वापस AE_OK;
पूर्ण
EXPORT_SYMBOL(__wrap_acpi_evaluate_object);

जोड़ acpi_object * __wrap_acpi_evaluate_dsm(acpi_handle handle, स्थिर guid_t *guid,
		u64 rev, u64 func, जोड़ acpi_object *argv4)
अणु
	जोड़ acpi_object *obj = ERR_PTR(-ENXIO);
	काष्ठा iomap_ops *ops;

	rcu_पढ़ो_lock();
	ops = list_first_or_null_rcu(&iomap_head, typeof(*ops), list);
	अगर (ops)
		obj = ops->evaluate_dsm(handle, guid, rev, func, argv4);
	rcu_पढ़ो_unlock();

	अगर (IS_ERR(obj))
		वापस acpi_evaluate_dsm(handle, guid, rev, func, argv4);
	वापस obj;
पूर्ण
EXPORT_SYMBOL(__wrap_acpi_evaluate_dsm);

MODULE_LICENSE("GPL v2");
