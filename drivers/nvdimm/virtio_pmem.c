<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * virtio_pmem.c: Virtio pmem Driver
 *
 * Discovers persistent memory range inक्रमmation
 * from host and रेजिस्टरs the भव pmem device
 * with libnvdimm core.
 */
#समावेश "virtio_pmem.h"
#समावेश "nd.h"

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_PMEM, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

 /* Initialize virt queue */
अटल पूर्णांक init_vq(काष्ठा virtio_pmem *vpmem)
अणु
	/* single vq */
	vpmem->req_vq = virtio_find_single_vq(vpmem->vdev,
					virtio_pmem_host_ack, "flush_queue");
	अगर (IS_ERR(vpmem->req_vq))
		वापस PTR_ERR(vpmem->req_vq);

	spin_lock_init(&vpmem->pmem_lock);
	INIT_LIST_HEAD(&vpmem->req_list);

	वापस 0;
पूर्ण;

अटल पूर्णांक virtio_pmem_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा nd_region_desc ndr_desc = अणुपूर्ण;
	पूर्णांक nid = dev_to_node(&vdev->dev);
	काष्ठा nd_region *nd_region;
	काष्ठा virtio_pmem *vpmem;
	काष्ठा resource res;
	पूर्णांक err = 0;

	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	vpmem = devm_kzalloc(&vdev->dev, माप(*vpmem), GFP_KERNEL);
	अगर (!vpmem) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	vpmem->vdev = vdev;
	vdev->priv = vpmem;
	err = init_vq(vpmem);
	अगर (err) अणु
		dev_err(&vdev->dev, "failed to initialize virtio pmem vq's\n");
		जाओ out_err;
	पूर्ण

	virtio_cपढ़ो_le(vpmem->vdev, काष्ठा virtio_pmem_config,
			start, &vpmem->start);
	virtio_cपढ़ो_le(vpmem->vdev, काष्ठा virtio_pmem_config,
			size, &vpmem->size);

	res.start = vpmem->start;
	res.end   = vpmem->start + vpmem->size - 1;
	vpmem->nd_desc.provider_name = "virtio-pmem";
	vpmem->nd_desc.module = THIS_MODULE;

	vpmem->nvdimm_bus = nvdimm_bus_रेजिस्टर(&vdev->dev,
						&vpmem->nd_desc);
	अगर (!vpmem->nvdimm_bus) अणु
		dev_err(&vdev->dev, "failed to register device with nvdimm_bus\n");
		err = -ENXIO;
		जाओ out_vq;
	पूर्ण

	dev_set_drvdata(&vdev->dev, vpmem->nvdimm_bus);

	ndr_desc.res = &res;
	ndr_desc.numa_node = nid;
	ndr_desc.flush = async_pmem_flush;
	set_bit(ND_REGION_PAGEMAP, &ndr_desc.flags);
	set_bit(ND_REGION_ASYNC, &ndr_desc.flags);
	nd_region = nvdimm_pmem_region_create(vpmem->nvdimm_bus, &ndr_desc);
	अगर (!nd_region) अणु
		dev_err(&vdev->dev, "failed to create nvdimm region\n");
		err = -ENXIO;
		जाओ out_nd;
	पूर्ण
	nd_region->provider_data = dev_to_virtio(nd_region->dev.parent->parent);
	वापस 0;
out_nd:
	nvdimm_bus_unरेजिस्टर(vpmem->nvdimm_bus);
out_vq:
	vdev->config->del_vqs(vdev);
out_err:
	वापस err;
पूर्ण

अटल व्योम virtio_pmem_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = dev_get_drvdata(&vdev->dev);

	nvdimm_bus_unरेजिस्टर(nvdimm_bus);
	vdev->config->del_vqs(vdev);
	vdev->config->reset(vdev);
पूर्ण

अटल काष्ठा virtio_driver virtio_pmem_driver = अणु
	.driver.name		= KBUILD_MODNAME,
	.driver.owner		= THIS_MODULE,
	.id_table		= id_table,
	.probe			= virtio_pmem_probe,
	.हटाओ			= virtio_pmem_हटाओ,
पूर्ण;

module_virtio_driver(virtio_pmem_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio pmem driver");
MODULE_LICENSE("GPL");
