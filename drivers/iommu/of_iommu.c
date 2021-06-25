<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OF helpers क्रम IOMMU
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/iommu.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/fsl/mc.h>

#घोषणा NO_IOMMU	1

/**
 * of_get_dma_winकरोw - Parse *dma-winकरोw property and वापसs 0 अगर found.
 *
 * @dn: device node
 * @prefix: prefix क्रम property name अगर any
 * @index: index to start to parse
 * @busno: Returns busno अगर supported. Otherwise pass शून्य
 * @addr: Returns address that DMA starts
 * @size: Returns the range that DMA can handle
 *
 * This supports dअगरferent क्रमmats flexibly. "prefix" can be
 * configured अगर any. "busno" and "index" are optionally
 * specअगरied. Set 0(or शून्य) अगर not used.
 */
पूर्णांक of_get_dma_winकरोw(काष्ठा device_node *dn, स्थिर अक्षर *prefix, पूर्णांक index,
		      अचिन्हित दीर्घ *busno, dma_addr_t *addr, माप_प्रकार *size)
अणु
	स्थिर __be32 *dma_winकरोw, *end;
	पूर्णांक bytes, cur_index = 0;
	अक्षर propname[NAME_MAX], addrname[NAME_MAX], sizename[NAME_MAX];

	अगर (!dn || !addr || !size)
		वापस -EINVAL;

	अगर (!prefix)
		prefix = "";

	snम_लिखो(propname, माप(propname), "%sdma-window", prefix);
	snम_लिखो(addrname, माप(addrname), "%s#dma-address-cells", prefix);
	snम_लिखो(sizename, माप(sizename), "%s#dma-size-cells", prefix);

	dma_winकरोw = of_get_property(dn, propname, &bytes);
	अगर (!dma_winकरोw)
		वापस -ENODEV;
	end = dma_winकरोw + bytes / माप(*dma_winकरोw);

	जबतक (dma_winकरोw < end) अणु
		u32 cells;
		स्थिर व्योम *prop;

		/* busno is one cell अगर supported */
		अगर (busno)
			*busno = be32_to_cpup(dma_winकरोw++);

		prop = of_get_property(dn, addrname, शून्य);
		अगर (!prop)
			prop = of_get_property(dn, "#address-cells", शून्य);

		cells = prop ? be32_to_cpup(prop) : of_n_addr_cells(dn);
		अगर (!cells)
			वापस -EINVAL;
		*addr = of_पढ़ो_number(dma_winकरोw, cells);
		dma_winकरोw += cells;

		prop = of_get_property(dn, sizename, शून्य);
		cells = prop ? be32_to_cpup(prop) : of_n_size_cells(dn);
		अगर (!cells)
			वापस -EINVAL;
		*size = of_पढ़ो_number(dma_winकरोw, cells);
		dma_winकरोw += cells;

		अगर (cur_index++ == index)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_dma_winकरोw);

अटल पूर्णांक of_iommu_xlate(काष्ठा device *dev,
			  काष्ठा of_phandle_args *iommu_spec)
अणु
	स्थिर काष्ठा iommu_ops *ops;
	काष्ठा fwnode_handle *fwnode = &iommu_spec->np->fwnode;
	पूर्णांक ret;

	ops = iommu_ops_from_fwnode(fwnode);
	अगर ((ops && !ops->of_xlate) ||
	    !of_device_is_available(iommu_spec->np))
		वापस NO_IOMMU;

	ret = iommu_fwspec_init(dev, &iommu_spec->np->fwnode, ops);
	अगर (ret)
		वापस ret;
	/*
	 * The otherwise-empty fwspec handily serves to indicate the specअगरic
	 * IOMMU device we're रुकोing क्रम, which will be useful अगर we ever get
	 * a proper probe-ordering dependency mechanism in future.
	 */
	अगर (!ops)
		वापस driver_deferred_probe_check_state(dev);

	अगर (!try_module_get(ops->owner))
		वापस -ENODEV;

	ret = ops->of_xlate(dev, iommu_spec);
	module_put(ops->owner);
	वापस ret;
पूर्ण

अटल पूर्णांक of_iommu_configure_dev_id(काष्ठा device_node *master_np,
				     काष्ठा device *dev,
				     स्थिर u32 *id)
अणु
	काष्ठा of_phandle_args iommu_spec = अणु .args_count = 1 पूर्ण;
	पूर्णांक err;

	err = of_map_id(master_np, *id, "iommu-map",
			 "iommu-map-mask", &iommu_spec.np,
			 iommu_spec.args);
	अगर (err)
		वापस err == -ENODEV ? NO_IOMMU : err;

	err = of_iommu_xlate(dev, &iommu_spec);
	of_node_put(iommu_spec.np);
	वापस err;
पूर्ण

अटल पूर्णांक of_iommu_configure_dev(काष्ठा device_node *master_np,
				  काष्ठा device *dev)
अणु
	काष्ठा of_phandle_args iommu_spec;
	पूर्णांक err = NO_IOMMU, idx = 0;

	जबतक (!of_parse_phandle_with_args(master_np, "iommus",
					   "#iommu-cells",
					   idx, &iommu_spec)) अणु
		err = of_iommu_xlate(dev, &iommu_spec);
		of_node_put(iommu_spec.np);
		idx++;
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

काष्ठा of_pci_iommu_alias_info अणु
	काष्ठा device *dev;
	काष्ठा device_node *np;
पूर्ण;

अटल पूर्णांक of_pci_iommu_init(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	काष्ठा of_pci_iommu_alias_info *info = data;
	u32 input_id = alias;

	वापस of_iommu_configure_dev_id(info->np, info->dev, &input_id);
पूर्ण

अटल पूर्णांक of_iommu_configure_device(काष्ठा device_node *master_np,
				     काष्ठा device *dev, स्थिर u32 *id)
अणु
	वापस (id) ? of_iommu_configure_dev_id(master_np, dev, id) :
		      of_iommu_configure_dev(master_np, dev);
पूर्ण

स्थिर काष्ठा iommu_ops *of_iommu_configure(काष्ठा device *dev,
					   काष्ठा device_node *master_np,
					   स्थिर u32 *id)
अणु
	स्थिर काष्ठा iommu_ops *ops = शून्य;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	पूर्णांक err = NO_IOMMU;

	अगर (!master_np)
		वापस शून्य;

	अगर (fwspec) अणु
		अगर (fwspec->ops)
			वापस fwspec->ops;

		/* In the deferred हाल, start again from scratch */
		iommu_fwspec_मुक्त(dev);
	पूर्ण

	/*
	 * We करोn't currently walk up the tree looking क्रम a parent IOMMU.
	 * See the `Notes:' section of
	 * Documentation/devicetree/bindings/iommu/iommu.txt
	 */
	अगर (dev_is_pci(dev)) अणु
		काष्ठा of_pci_iommu_alias_info info = अणु
			.dev = dev,
			.np = master_np,
		पूर्ण;

		pci_request_acs();
		err = pci_क्रम_each_dma_alias(to_pci_dev(dev),
					     of_pci_iommu_init, &info);
	पूर्ण अन्यथा अणु
		err = of_iommu_configure_device(master_np, dev, id);
	पूर्ण

	/*
	 * Two success conditions can be represented by non-negative err here:
	 * >0 : there is no IOMMU, or one was unavailable क्रम non-fatal reasons
	 *  0 : we found an IOMMU, and dev->fwspec is initialised appropriately
	 * <0 : any actual error
	 */
	अगर (!err) अणु
		/* The fwspec poपूर्णांकer changed, पढ़ो it again */
		fwspec = dev_iommu_fwspec_get(dev);
		ops    = fwspec->ops;
	पूर्ण
	/*
	 * If we have reason to believe the IOMMU driver missed the initial
	 * probe क्रम dev, replay it to get things in order.
	 */
	अगर (!err && dev->bus && !device_iommu_mapped(dev))
		err = iommu_probe_device(dev);

	/* Ignore all other errors apart from EPROBE_DEFER */
	अगर (err == -EPROBE_DEFER) अणु
		ops = ERR_PTR(err);
	पूर्ण अन्यथा अगर (err < 0) अणु
		dev_dbg(dev, "Adding to IOMMU failed: %d\n", err);
		ops = शून्य;
	पूर्ण

	वापस ops;
पूर्ण
