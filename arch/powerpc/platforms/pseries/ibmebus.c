<शैली गुरु>
/*
 * IBM PowerPC IBM eBus Infraकाष्ठाure Support.
 *
 * Copyright (c) 2005 IBM Corporation
 *  Joachim Fenkes <fenkes@de.ibm.com>
 *  Heiko J Schick <schickhj@de.ibm.com>
 *
 * All rights reserved.
 *
 * This source code is distributed under a dual license of GPL v2.0 and OpenIB
 * BSD.
 *
 * OpenIB BSD License
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials
 * provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/console.h>
#समावेश <linux/kobject.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/ibmebus.h>
#समावेश <यंत्र/machdep.h>

अटल काष्ठा device ibmebus_bus_device = अणु /* fake "parent" device */
	.init_name = "ibmebus",
पूर्ण;

काष्ठा bus_type ibmebus_bus_type;

/* These devices will स्वतःmatically be added to the bus during init */
अटल स्थिर काष्ठा of_device_id ibmebus_matches[] __initस्थिर = अणु
	अणु .compatible = "IBM,lhca" पूर्ण,
	अणु .compatible = "IBM,lhea" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम *ibmebus_alloc_coherent(काष्ठा device *dev,
				    माप_प्रकार size,
				    dma_addr_t *dma_handle,
				    gfp_t flag,
				    अचिन्हित दीर्घ attrs)
अणु
	व्योम *mem;

	mem = kदो_स्मृति(size, flag);
	*dma_handle = (dma_addr_t)mem;

	वापस mem;
पूर्ण

अटल व्योम ibmebus_मुक्त_coherent(काष्ठा device *dev,
				  माप_प्रकार size, व्योम *vaddr,
				  dma_addr_t dma_handle,
				  अचिन्हित दीर्घ attrs)
अणु
	kमुक्त(vaddr);
पूर्ण

अटल dma_addr_t ibmebus_map_page(काष्ठा device *dev,
				   काष्ठा page *page,
				   अचिन्हित दीर्घ offset,
				   माप_प्रकार size,
				   क्रमागत dma_data_direction direction,
				   अचिन्हित दीर्घ attrs)
अणु
	वापस (dma_addr_t)(page_address(page) + offset);
पूर्ण

अटल व्योम ibmebus_unmap_page(काष्ठा device *dev,
			       dma_addr_t dma_addr,
			       माप_प्रकार size,
			       क्रमागत dma_data_direction direction,
			       अचिन्हित दीर्घ attrs)
अणु
	वापस;
पूर्ण

अटल पूर्णांक ibmebus_map_sg(काष्ठा device *dev,
			  काष्ठा scatterlist *sgl,
			  पूर्णांक nents, क्रमागत dma_data_direction direction,
			  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		sg->dma_address = (dma_addr_t) sg_virt(sg);
		sg->dma_length = sg->length;
	पूर्ण

	वापस nents;
पूर्ण

अटल व्योम ibmebus_unmap_sg(काष्ठा device *dev,
			     काष्ठा scatterlist *sg,
			     पूर्णांक nents, क्रमागत dma_data_direction direction,
			     अचिन्हित दीर्घ attrs)
अणु
	वापस;
पूर्ण

अटल पूर्णांक ibmebus_dma_supported(काष्ठा device *dev, u64 mask)
अणु
	वापस mask == DMA_BIT_MASK(64);
पूर्ण

अटल u64 ibmebus_dma_get_required_mask(काष्ठा device *dev)
अणु
	वापस DMA_BIT_MASK(64);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops ibmebus_dma_ops = अणु
	.alloc              = ibmebus_alloc_coherent,
	.मुक्त               = ibmebus_मुक्त_coherent,
	.map_sg             = ibmebus_map_sg,
	.unmap_sg           = ibmebus_unmap_sg,
	.dma_supported      = ibmebus_dma_supported,
	.get_required_mask  = ibmebus_dma_get_required_mask,
	.map_page           = ibmebus_map_page,
	.unmap_page         = ibmebus_unmap_page,
पूर्ण;

अटल पूर्णांक ibmebus_match_path(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा device_node *dn = to_platक्रमm_device(dev)->dev.of_node;
	वापस (of_find_node_by_path(data) == dn);
पूर्ण

अटल पूर्णांक ibmebus_match_node(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस to_platक्रमm_device(dev)->dev.of_node == data;
पूर्ण

अटल पूर्णांक ibmebus_create_device(काष्ठा device_node *dn)
अणु
	काष्ठा platक्रमm_device *dev;
	पूर्णांक ret;

	dev = of_device_alloc(dn, शून्य, &ibmebus_bus_device);
	अगर (!dev)
		वापस -ENOMEM;

	dev->dev.bus = &ibmebus_bus_type;
	dev->dev.dma_ops = &ibmebus_dma_ops;

	ret = of_device_add(dev);
	अगर (ret)
		platक्रमm_device_put(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ibmebus_create_devices(स्थिर काष्ठा of_device_id *matches)
अणु
	काष्ठा device_node *root, *child;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	root = of_find_node_by_path("/");

	क्रम_each_child_of_node(root, child) अणु
		अगर (!of_match_node(matches, child))
			जारी;

		dev = bus_find_device(&ibmebus_bus_type, शून्य, child,
				      ibmebus_match_node);
		अगर (dev) अणु
			put_device(dev);
			जारी;
		पूर्ण

		ret = ibmebus_create_device(child);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: failed to create device (%i)",
			       __func__, ret);
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	of_node_put(root);
	वापस ret;
पूर्ण

पूर्णांक ibmebus_रेजिस्टर_driver(काष्ठा platक्रमm_driver *drv)
अणु
	/* If the driver uses devices that ibmebus करोesn't know, add them */
	ibmebus_create_devices(drv->driver.of_match_table);

	drv->driver.bus = &ibmebus_bus_type;
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(ibmebus_रेजिस्टर_driver);

व्योम ibmebus_unरेजिस्टर_driver(काष्ठा platक्रमm_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(ibmebus_unरेजिस्टर_driver);

पूर्णांक ibmebus_request_irq(u32 ist, irq_handler_t handler,
			अचिन्हित दीर्घ irq_flags, स्थिर अक्षर *devname,
			व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक irq = irq_create_mapping(शून्य, ist);

	अगर (!irq)
		वापस -EINVAL;

	वापस request_irq(irq, handler, irq_flags, devname, dev_id);
पूर्ण
EXPORT_SYMBOL(ibmebus_request_irq);

व्योम ibmebus_मुक्त_irq(u32 ist, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक irq = irq_find_mapping(शून्य, ist);

	मुक्त_irq(irq, dev_id);
	irq_dispose_mapping(irq);
पूर्ण
EXPORT_SYMBOL(ibmebus_मुक्त_irq);

अटल अक्षर *ibmebus_chomp(स्थिर अक्षर *in, माप_प्रकार count)
अणु
	अक्षर *out = kदो_स्मृति(count + 1, GFP_KERNEL);

	अगर (!out)
		वापस शून्य;

	स_नकल(out, in, count);
	out[count] = '\0';
	अगर (out[count - 1] == '\n')
		out[count - 1] = '\0';

	वापस out;
पूर्ण

अटल sमाप_प्रकार probe_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device_node *dn = शून्य;
	काष्ठा device *dev;
	अक्षर *path;
	sमाप_प्रकार rc = 0;

	path = ibmebus_chomp(buf, count);
	अगर (!path)
		वापस -ENOMEM;

	dev = bus_find_device(&ibmebus_bus_type, शून्य, path,
			      ibmebus_match_path);
	अगर (dev) अणु
		put_device(dev);
		prपूर्णांकk(KERN_WARNING "%s: %s has already been probed\n",
		       __func__, path);
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	अगर ((dn = of_find_node_by_path(path))) अणु
		rc = ibmebus_create_device(dn);
		of_node_put(dn);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "%s: no such device node: %s\n",
		       __func__, path);
		rc = -ENODEV;
	पूर्ण

out:
	kमुक्त(path);
	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण
अटल BUS_ATTR_WO(probe);

अटल sमाप_प्रकार हटाओ_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device *dev;
	अक्षर *path;

	path = ibmebus_chomp(buf, count);
	अगर (!path)
		वापस -ENOMEM;

	अगर ((dev = bus_find_device(&ibmebus_bus_type, शून्य, path,
				   ibmebus_match_path))) अणु
		of_device_unरेजिस्टर(to_platक्रमm_device(dev));
		put_device(dev);

		kमुक्त(path);
		वापस count;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "%s: %s not on the bus\n",
		       __func__, path);

		kमुक्त(path);
		वापस -ENODEV;
	पूर्ण
पूर्ण
अटल BUS_ATTR_WO(हटाओ);

अटल काष्ठा attribute *ibmbus_bus_attrs[] = अणु
	&bus_attr_probe.attr,
	&bus_attr_हटाओ.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ibmbus_bus);

अटल पूर्णांक ibmebus_bus_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा of_device_id *matches = drv->of_match_table;

	अगर (!matches)
		वापस 0;

	वापस of_match_device(matches, dev) != शून्य;
पूर्ण

अटल पूर्णांक ibmebus_bus_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = -ENODEV;
	काष्ठा platक्रमm_driver *drv;
	काष्ठा platक्रमm_device *of_dev;

	drv = to_platक्रमm_driver(dev->driver);
	of_dev = to_platक्रमm_device(dev);

	अगर (!drv->probe)
		वापस error;

	get_device(dev);

	अगर (of_driver_match_device(dev, dev->driver))
		error = drv->probe(of_dev);
	अगर (error)
		put_device(dev);

	वापस error;
पूर्ण

अटल पूर्णांक ibmebus_bus_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *of_dev = to_platक्रमm_device(dev);
	काष्ठा platक्रमm_driver *drv = to_platक्रमm_driver(dev->driver);

	अगर (dev->driver && drv->हटाओ)
		drv->हटाओ(of_dev);
	वापस 0;
पूर्ण

अटल व्योम ibmebus_bus_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *of_dev = to_platक्रमm_device(dev);
	काष्ठा platक्रमm_driver *drv = to_platक्रमm_driver(dev->driver);

	अगर (dev->driver && drv->shutकरोwn)
		drv->shutकरोwn(of_dev);
पूर्ण

/*
 * ibmebus_bus_device_attrs
 */
अटल sमाप_प्रकार devspec_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *ofdev;

	ofdev = to_platक्रमm_device(dev);
	वापस प्र_लिखो(buf, "%pOF\n", ofdev->dev.of_node);
पूर्ण
अटल DEVICE_ATTR_RO(devspec);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *ofdev;

	ofdev = to_platक्रमm_device(dev);
	वापस प्र_लिखो(buf, "%pOFn\n", ofdev->dev.of_node);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस of_device_modalias(dev, buf, PAGE_SIZE);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *ibmebus_bus_device_attrs[] = अणु
	&dev_attr_devspec.attr,
	&dev_attr_name.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ibmebus_bus_device);

काष्ठा bus_type ibmebus_bus_type = अणु
	.name      = "ibmebus",
	.uevent    = of_device_uevent_modalias,
	.bus_groups = ibmbus_bus_groups,
	.match     = ibmebus_bus_bus_match,
	.probe     = ibmebus_bus_device_probe,
	.हटाओ    = ibmebus_bus_device_हटाओ,
	.shutकरोwn  = ibmebus_bus_device_shutकरोwn,
	.dev_groups = ibmebus_bus_device_groups,
पूर्ण;
EXPORT_SYMBOL(ibmebus_bus_type);

अटल पूर्णांक __init ibmebus_bus_init(व्योम)
अणु
	पूर्णांक err;

	prपूर्णांकk(KERN_INFO "IBM eBus Device Driver\n");

	err = bus_रेजिस्टर(&ibmebus_bus_type);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to register IBM eBus.\n",
		       __func__);
		वापस err;
	पूर्ण

	err = device_रेजिस्टर(&ibmebus_bus_device);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: device_register returned %i\n",
		       __func__, err);
		bus_unरेजिस्टर(&ibmebus_bus_type);

		वापस err;
	पूर्ण

	err = ibmebus_create_devices(ibmebus_matches);
	अगर (err) अणु
		device_unरेजिस्टर(&ibmebus_bus_device);
		bus_unरेजिस्टर(&ibmebus_bus_type);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
machine_postcore_initcall(pseries, ibmebus_bus_init);
