<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/ndctl.h>
#समावेश <nd-core.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/seq_buf.h>

#समावेश "../watermark.h"
#समावेश "nfit_test.h"
#समावेश "ndtest.h"

क्रमागत अणु
	DIMM_SIZE = SZ_32M,
	LABEL_SIZE = SZ_128K,
	NUM_INSTANCES = 2,
	NUM_DCR = 4,
	NDTEST_MAX_MAPPING = 6,
पूर्ण;

#घोषणा NDTEST_SCM_DIMM_CMD_MASK	   \
	((1ul << ND_CMD_GET_CONFIG_SIZE) | \
	 (1ul << ND_CMD_GET_CONFIG_DATA) | \
	 (1ul << ND_CMD_SET_CONFIG_DATA) | \
	 (1ul << ND_CMD_CALL))

#घोषणा NFIT_DIMM_HANDLE(node, socket, imc, chan, dimm)			\
	(((node & 0xfff) << 16) | ((socket & 0xf) << 12)		\
	 | ((imc & 0xf) << 8) | ((chan & 0xf) << 4) | (dimm & 0xf))

अटल DEFINE_SPINLOCK(ndtest_lock);
अटल काष्ठा ndtest_priv *instances[NUM_INSTANCES];
अटल काष्ठा class *ndtest_dimm_class;
अटल काष्ठा gen_pool *ndtest_pool;

अटल काष्ठा ndtest_dimm dimm_group1[] = अणु
	अणु
		.size = DIMM_SIZE,
		.handle = NFIT_DIMM_HANDLE(0, 0, 0, 0, 0),
		.uuid_str = "1e5c75d2-b618-11ea-9aa3-507b9ddc0f72",
		.physical_id = 0,
		.num_क्रमmats = 2,
	पूर्ण,
	अणु
		.size = DIMM_SIZE,
		.handle = NFIT_DIMM_HANDLE(0, 0, 0, 0, 1),
		.uuid_str = "1c4d43ac-b618-11ea-be80-507b9ddc0f72",
		.physical_id = 1,
		.num_क्रमmats = 2,
	पूर्ण,
	अणु
		.size = DIMM_SIZE,
		.handle = NFIT_DIMM_HANDLE(0, 0, 1, 0, 0),
		.uuid_str = "a9f17ffc-b618-11ea-b36d-507b9ddc0f72",
		.physical_id = 2,
		.num_क्रमmats = 2,
	पूर्ण,
	अणु
		.size = DIMM_SIZE,
		.handle = NFIT_DIMM_HANDLE(0, 0, 1, 0, 1),
		.uuid_str = "b6b83b22-b618-11ea-8aae-507b9ddc0f72",
		.physical_id = 3,
		.num_क्रमmats = 2,
	पूर्ण,
	अणु
		.size = DIMM_SIZE,
		.handle = NFIT_DIMM_HANDLE(0, 1, 0, 0, 0),
		.uuid_str = "bf9baaee-b618-11ea-b181-507b9ddc0f72",
		.physical_id = 4,
		.num_क्रमmats = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_dimm dimm_group2[] = अणु
	अणु
		.size = DIMM_SIZE,
		.handle = NFIT_DIMM_HANDLE(1, 0, 0, 0, 0),
		.uuid_str = "ca0817e2-b618-11ea-9db3-507b9ddc0f72",
		.physical_id = 0,
		.num_क्रमmats = 1,
		.flags = PAPR_PMEM_UNARMED | PAPR_PMEM_EMPTY |
			 PAPR_PMEM_SAVE_FAILED | PAPR_PMEM_SHUTDOWN_सूचीTY |
			 PAPR_PMEM_HEALTH_FATAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_mapping region0_mapping[] = अणु
	अणु
		.dimm = 0,
		.position = 0,
		.start = 0,
		.size = SZ_16M,
	पूर्ण,
	अणु
		.dimm = 1,
		.position = 1,
		.start = 0,
		.size = SZ_16M,
	पूर्ण
पूर्ण;

अटल काष्ठा ndtest_mapping region1_mapping[] = अणु
	अणु
		.dimm = 0,
		.position = 0,
		.start = SZ_16M,
		.size = SZ_16M,
	पूर्ण,
	अणु
		.dimm = 1,
		.position = 1,
		.start = SZ_16M,
		.size = SZ_16M,
	पूर्ण,
	अणु
		.dimm = 2,
		.position = 2,
		.start = SZ_16M,
		.size = SZ_16M,
	पूर्ण,
	अणु
		.dimm = 3,
		.position = 3,
		.start = SZ_16M,
		.size = SZ_16M,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_mapping region2_mapping[] = अणु
	अणु
		.dimm = 0,
		.position = 0,
		.start = 0,
		.size = DIMM_SIZE,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_mapping region3_mapping[] = अणु
	अणु
		.dimm = 1,
		.start = 0,
		.size = DIMM_SIZE,
	पूर्ण
पूर्ण;

अटल काष्ठा ndtest_mapping region4_mapping[] = अणु
	अणु
		.dimm = 2,
		.start = 0,
		.size = DIMM_SIZE,
	पूर्ण
पूर्ण;

अटल काष्ठा ndtest_mapping region5_mapping[] = अणु
	अणु
		.dimm = 3,
		.start = 0,
		.size = DIMM_SIZE,
	पूर्ण
पूर्ण;

अटल काष्ठा ndtest_region bus0_regions[] = अणु
	अणु
		.type = ND_DEVICE_NAMESPACE_PMEM,
		.num_mappings = ARRAY_SIZE(region0_mapping),
		.mapping = region0_mapping,
		.size = DIMM_SIZE,
		.range_index = 1,
	पूर्ण,
	अणु
		.type = ND_DEVICE_NAMESPACE_PMEM,
		.num_mappings = ARRAY_SIZE(region1_mapping),
		.mapping = region1_mapping,
		.size = DIMM_SIZE * 2,
		.range_index = 2,
	पूर्ण,
	अणु
		.type = ND_DEVICE_NAMESPACE_BLK,
		.num_mappings = ARRAY_SIZE(region2_mapping),
		.mapping = region2_mapping,
		.size = DIMM_SIZE,
		.range_index = 3,
	पूर्ण,
	अणु
		.type = ND_DEVICE_NAMESPACE_BLK,
		.num_mappings = ARRAY_SIZE(region3_mapping),
		.mapping = region3_mapping,
		.size = DIMM_SIZE,
		.range_index = 4,
	पूर्ण,
	अणु
		.type = ND_DEVICE_NAMESPACE_BLK,
		.num_mappings = ARRAY_SIZE(region4_mapping),
		.mapping = region4_mapping,
		.size = DIMM_SIZE,
		.range_index = 5,
	पूर्ण,
	अणु
		.type = ND_DEVICE_NAMESPACE_BLK,
		.num_mappings = ARRAY_SIZE(region5_mapping),
		.mapping = region5_mapping,
		.size = DIMM_SIZE,
		.range_index = 6,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_mapping region6_mapping[] = अणु
	अणु
		.dimm = 0,
		.position = 0,
		.start = 0,
		.size = DIMM_SIZE,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_region bus1_regions[] = अणु
	अणु
		.type = ND_DEVICE_NAMESPACE_IO,
		.num_mappings = ARRAY_SIZE(region6_mapping),
		.mapping = region6_mapping,
		.size = DIMM_SIZE,
		.range_index = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा ndtest_config bus_configs[NUM_INSTANCES] = अणु
	/* bus 1 */
	अणु
		.dimm_start = 0,
		.dimm_count = ARRAY_SIZE(dimm_group1),
		.dimms = dimm_group1,
		.regions = bus0_regions,
		.num_regions = ARRAY_SIZE(bus0_regions),
	पूर्ण,
	/* bus 2 */
	अणु
		.dimm_start = ARRAY_SIZE(dimm_group1),
		.dimm_count = ARRAY_SIZE(dimm_group2),
		.dimms = dimm_group2,
		.regions = bus1_regions,
		.num_regions = ARRAY_SIZE(bus1_regions),
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा ndtest_priv *to_ndtest_priv(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	वापस container_of(pdev, काष्ठा ndtest_priv, pdev);
पूर्ण

अटल पूर्णांक ndtest_config_get(काष्ठा ndtest_dimm *p, अचिन्हित पूर्णांक buf_len,
			     काष्ठा nd_cmd_get_config_data_hdr *hdr)
अणु
	अचिन्हित पूर्णांक len;

	अगर ((hdr->in_offset + hdr->in_length) > LABEL_SIZE)
		वापस -EINVAL;

	hdr->status = 0;
	len = min(hdr->in_length, LABEL_SIZE - hdr->in_offset);
	स_नकल(hdr->out_buf, p->label_area + hdr->in_offset, len);

	वापस buf_len - len;
पूर्ण

अटल पूर्णांक ndtest_config_set(काष्ठा ndtest_dimm *p, अचिन्हित पूर्णांक buf_len,
			     काष्ठा nd_cmd_set_config_hdr *hdr)
अणु
	अचिन्हित पूर्णांक len;

	अगर ((hdr->in_offset + hdr->in_length) > LABEL_SIZE)
		वापस -EINVAL;

	len = min(hdr->in_length, LABEL_SIZE - hdr->in_offset);
	स_नकल(p->label_area + hdr->in_offset, hdr->in_buf, len);

	वापस buf_len - len;
पूर्ण

अटल पूर्णांक ndtest_get_config_size(काष्ठा ndtest_dimm *dimm, अचिन्हित पूर्णांक buf_len,
				  काष्ठा nd_cmd_get_config_size *size)
अणु
	size->status = 0;
	size->max_xfer = 8;
	size->config_size = dimm->config_size;

	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_ctl(काष्ठा nvdimm_bus_descriptor *nd_desc,
		      काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
		      अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc)
अणु
	काष्ठा ndtest_dimm *dimm;
	पूर्णांक _cmd_rc;

	अगर (!cmd_rc)
		cmd_rc = &_cmd_rc;

	*cmd_rc = 0;

	अगर (!nvdimm)
		वापस -EINVAL;

	dimm = nvdimm_provider_data(nvdimm);
	अगर (!dimm)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल ND_CMD_GET_CONFIG_SIZE:
		*cmd_rc = ndtest_get_config_size(dimm, buf_len, buf);
		अवरोध;
	हाल ND_CMD_GET_CONFIG_DATA:
		*cmd_rc = ndtest_config_get(dimm, buf_len, buf);
		अवरोध;
	हाल ND_CMD_SET_CONFIG_DATA:
		*cmd_rc = ndtest_config_set(dimm, buf_len, buf);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Failures क्रम a DIMM can be injected using fail_cmd and
	 * fail_cmd_code, see the device attributes below
	 */
	अगर ((1 << cmd) & dimm->fail_cmd)
		वापस dimm->fail_cmd_code ? dimm->fail_cmd_code : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_blk_करो_io(काष्ठा nd_blk_region *ndbr, resource_माप_प्रकार dpa,
		व्योम *iobuf, u64 len, पूर्णांक rw)
अणु
	काष्ठा ndtest_dimm *dimm = ndbr->blk_provider_data;
	काष्ठा ndtest_blk_mmio *mmio = dimm->mmio;
	काष्ठा nd_region *nd_region = &ndbr->nd_region;
	अचिन्हित पूर्णांक lane;

	अगर (!mmio)
		वापस -ENOMEM;

	lane = nd_region_acquire_lane(nd_region);
	अगर (rw)
		स_नकल(mmio->base + dpa, iobuf, len);
	अन्यथा अणु
		स_नकल(iobuf, mmio->base + dpa, len);
		arch_invalidate_pmem(mmio->base + dpa, len);
	पूर्ण

	nd_region_release_lane(nd_region, lane);

	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_blk_region_enable(काष्ठा nvdimm_bus *nvdimm_bus,
				    काष्ठा device *dev)
अणु
	काष्ठा nd_blk_region *ndbr = to_nd_blk_region(dev);
	काष्ठा nvdimm *nvdimm;
	काष्ठा ndtest_dimm *dimm;
	काष्ठा ndtest_blk_mmio *mmio;

	nvdimm = nd_blk_region_to_dimm(ndbr);
	dimm = nvdimm_provider_data(nvdimm);

	nd_blk_region_set_provider_data(ndbr, dimm);
	dimm->blk_region = to_nd_region(dev);

	mmio = devm_kzalloc(dev, माप(काष्ठा ndtest_blk_mmio), GFP_KERNEL);
	अगर (!mmio)
		वापस -ENOMEM;

	mmio->base = (व्योम __iomem *) devm_nvdimm_memremap(
		dev, dimm->address, 12, nd_blk_memremap_flags(ndbr));
	अगर (!mmio->base) अणु
		dev_err(dev, "%s failed to map blk dimm\n", nvdimm_name(nvdimm));
		वापस -ENOMEM;
	पूर्ण
	mmio->size = dimm->size;
	mmio->base_offset = 0;

	dimm->mmio = mmio;

	वापस 0;
पूर्ण

अटल काष्ठा nfit_test_resource *ndtest_resource_lookup(resource_माप_प्रकार addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_INSTANCES; i++) अणु
		काष्ठा nfit_test_resource *n, *nfit_res = शून्य;
		काष्ठा ndtest_priv *t = instances[i];

		अगर (!t)
			जारी;
		spin_lock(&ndtest_lock);
		list_क्रम_each_entry(n, &t->resources, list) अणु
			अगर (addr >= n->res.start && (addr < n->res.start
						+ resource_size(&n->res))) अणु
				nfit_res = n;
				अवरोध;
			पूर्ण अन्यथा अगर (addr >= (अचिन्हित दीर्घ) n->buf
					&& (addr < (अचिन्हित दीर्घ) n->buf
						+ resource_size(&n->res))) अणु
				nfit_res = n;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&ndtest_lock);
		अगर (nfit_res)
			वापस nfit_res;
	पूर्ण

	pr_warn("Failed to get resource\n");

	वापस शून्य;
पूर्ण

अटल व्योम ndtest_release_resource(व्योम *data)
अणु
	काष्ठा nfit_test_resource *res  = data;

	spin_lock(&ndtest_lock);
	list_del(&res->list);
	spin_unlock(&ndtest_lock);

	अगर (resource_size(&res->res) >= DIMM_SIZE)
		gen_pool_मुक्त(ndtest_pool, res->res.start,
				resource_size(&res->res));
	vमुक्त(res->buf);
	kमुक्त(res);
पूर्ण

अटल व्योम *ndtest_alloc_resource(काष्ठा ndtest_priv *p, माप_प्रकार size,
				   dma_addr_t *dma)
अणु
	dma_addr_t __dma;
	व्योम *buf;
	काष्ठा nfit_test_resource *res;
	काष्ठा genpool_data_align data = अणु
		.align = SZ_128M,
	पूर्ण;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस शून्य;

	buf = vदो_स्मृति(size);
	अगर (size >= DIMM_SIZE)
		__dma = gen_pool_alloc_algo(ndtest_pool, size,
					    gen_pool_first_fit_align, &data);
	अन्यथा
		__dma = (अचिन्हित दीर्घ) buf;

	अगर (!__dma)
		जाओ buf_err;

	INIT_LIST_HEAD(&res->list);
	res->dev = &p->pdev.dev;
	res->buf = buf;
	res->res.start = __dma;
	res->res.end = __dma + size - 1;
	res->res.name = "NFIT";
	spin_lock_init(&res->lock);
	INIT_LIST_HEAD(&res->requests);
	spin_lock(&ndtest_lock);
	list_add(&res->list, &p->resources);
	spin_unlock(&ndtest_lock);

	अगर (dma)
		*dma = __dma;

	अगर (!devm_add_action(&p->pdev.dev, ndtest_release_resource, res))
		वापस res->buf;

buf_err:
	अगर (__dma && size >= DIMM_SIZE)
		gen_pool_मुक्त(ndtest_pool, __dma, size);
	अगर (buf)
		vमुक्त(buf);
	kमुक्त(res);

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार range_index_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	काष्ठा ndtest_region *region = nd_region_provider_data(nd_region);

	वापस प्र_लिखो(buf, "%d\n", region->range_index);
पूर्ण
अटल DEVICE_ATTR_RO(range_index);

अटल काष्ठा attribute *ndtest_region_attributes[] = अणु
	&dev_attr_range_index.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ndtest_region_attribute_group = अणु
	.name = "papr",
	.attrs = ndtest_region_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ndtest_region_attribute_groups[] = अणु
	&ndtest_region_attribute_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ndtest_create_region(काष्ठा ndtest_priv *p,
				काष्ठा ndtest_region *region)
अणु
	काष्ठा nd_mapping_desc mappings[NDTEST_MAX_MAPPING];
	काष्ठा nd_blk_region_desc ndbr_desc;
	काष्ठा nd_पूर्णांकerleave_set *nd_set;
	काष्ठा nd_region_desc *ndr_desc;
	काष्ठा resource res;
	पूर्णांक i, ndimm = region->mapping[0].dimm;
	u64 uuid[2];

	स_रखो(&res, 0, माप(res));
	स_रखो(&mappings, 0, माप(mappings));
	स_रखो(&ndbr_desc, 0, माप(ndbr_desc));
	ndr_desc = &ndbr_desc.ndr_desc;

	अगर (!ndtest_alloc_resource(p, region->size, &res.start))
		वापस -ENOMEM;

	res.end = res.start + region->size - 1;
	ndr_desc->mapping = mappings;
	ndr_desc->res = &res;
	ndr_desc->provider_data = region;
	ndr_desc->attr_groups = ndtest_region_attribute_groups;

	अगर (uuid_parse(p->config->dimms[ndimm].uuid_str, (uuid_t *)uuid)) अणु
		pr_err("failed to parse UUID\n");
		वापस -ENXIO;
	पूर्ण

	nd_set = devm_kzalloc(&p->pdev.dev, माप(*nd_set), GFP_KERNEL);
	अगर (!nd_set)
		वापस -ENOMEM;

	nd_set->cookie1 = cpu_to_le64(uuid[0]);
	nd_set->cookie2 = cpu_to_le64(uuid[1]);
	nd_set->altcookie = nd_set->cookie1;
	ndr_desc->nd_set = nd_set;

	अगर (region->type == ND_DEVICE_NAMESPACE_BLK) अणु
		mappings[0].start = 0;
		mappings[0].size = DIMM_SIZE;
		mappings[0].nvdimm = p->config->dimms[ndimm].nvdimm;

		ndr_desc->mapping = &mappings[0];
		ndr_desc->num_mappings = 1;
		ndr_desc->num_lanes = 1;
		ndbr_desc.enable = ndtest_blk_region_enable;
		ndbr_desc.करो_io = ndtest_blk_करो_io;
		region->region = nvdimm_blk_region_create(p->bus, ndr_desc);

		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < region->num_mappings; i++) अणु
		ndimm = region->mapping[i].dimm;
		mappings[i].start = region->mapping[i].start;
		mappings[i].size = region->mapping[i].size;
		mappings[i].position = region->mapping[i].position;
		mappings[i].nvdimm = p->config->dimms[ndimm].nvdimm;
	पूर्ण

	ndr_desc->num_mappings = region->num_mappings;
	region->region = nvdimm_pmem_region_create(p->bus, ndr_desc);

करोne:
	अगर (!region->region) अणु
		dev_err(&p->pdev.dev, "Error registering region %pR\n",
			ndr_desc->res);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_init_regions(काष्ठा ndtest_priv *p)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < p->config->num_regions; i++) अणु
		ret = ndtest_create_region(p, &p->config->regions[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम put_dimms(व्योम *data)
अणु
	काष्ठा ndtest_priv *p = data;
	पूर्णांक i;

	क्रम (i = 0; i < p->config->dimm_count; i++)
		अगर (p->config->dimms[i].dev) अणु
			device_unरेजिस्टर(p->config->dimms[i].dev);
			p->config->dimms[i].dev = शून्य;
		पूर्ण
पूर्ण

अटल sमाप_प्रकार handle_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ndtest_dimm *dimm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", dimm->handle);
पूर्ण
अटल DEVICE_ATTR_RO(handle);

अटल sमाप_प्रकार fail_cmd_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ndtest_dimm *dimm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", dimm->fail_cmd);
पूर्ण

अटल sमाप_प्रकार fail_cmd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा ndtest_dimm *dimm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार rc;

	rc = kम_से_दीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	dimm->fail_cmd = val;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(fail_cmd);

अटल sमाप_प्रकार fail_cmd_code_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ndtest_dimm *dimm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dimm->fail_cmd_code);
पूर्ण

अटल sमाप_प्रकार fail_cmd_code_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा ndtest_dimm *dimm = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार rc;

	rc = kम_से_दीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	dimm->fail_cmd_code = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(fail_cmd_code);

अटल काष्ठा attribute *dimm_attributes[] = अणु
	&dev_attr_handle.attr,
	&dev_attr_fail_cmd.attr,
	&dev_attr_fail_cmd_code.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group dimm_attribute_group = अणु
	.attrs = dimm_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dimm_attribute_groups[] = अणु
	&dimm_attribute_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार phys_id_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);

	वापस प्र_लिखो(buf, "%#x\n", dimm->physical_id);
पूर्ण
अटल DEVICE_ATTR_RO(phys_id);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x1234567\n");
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार id_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);

	वापस प्र_लिखो(buf, "%04x-%02x-%04x-%08x", 0xabcd,
		       0xa, 2016, ~(dimm->handle));
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार nvdimm_handle_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);

	वापस प्र_लिखो(buf, "%#x\n", dimm->handle);
पूर्ण

अटल काष्ठा device_attribute dev_attr_nvdimm_show_handle =  अणु
	.attr	= अणु .name = "handle", .mode = 0444 पूर्ण,
	.show	= nvdimm_handle_show,
पूर्ण;

अटल sमाप_प्रकार subप्रणाली_venकरोr_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%04x\n", 0);
पूर्ण
अटल DEVICE_ATTR_RO(subप्रणाली_venकरोr);

अटल sमाप_प्रकार dirty_shutकरोwn_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", 42);
पूर्ण
अटल DEVICE_ATTR_RO(dirty_shutकरोwn);

अटल sमाप_प्रकार क्रमmats_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);

	वापस प्र_लिखो(buf, "%d\n", dimm->num_क्रमmats);
पूर्ण
अटल DEVICE_ATTR_RO(क्रमmats);

अटल sमाप_प्रकार क्रमmat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);

	अगर (dimm->num_क्रमmats > 1)
		वापस प्र_लिखो(buf, "0x201\n");

	वापस प्र_लिखो(buf, "0x101\n");
पूर्ण
अटल DEVICE_ATTR_RO(क्रमmat);

अटल sमाप_प्रकार क्रमmat1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x301\n");
पूर्ण
अटल DEVICE_ATTR_RO(क्रमmat1);

अटल umode_t ndtest_nvdimm_attr_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);

	अगर (a == &dev_attr_क्रमmat1.attr && dimm->num_क्रमmats <= 1)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा ndtest_dimm *dimm = nvdimm_provider_data(nvdimm);
	काष्ठा seq_buf s;
	u64 flags;

	flags = dimm->flags;

	seq_buf_init(&s, buf, PAGE_SIZE);
	अगर (flags & PAPR_PMEM_UNARMED_MASK)
		seq_buf_म_लिखो(&s, "not_armed ");

	अगर (flags & PAPR_PMEM_BAD_SHUTDOWN_MASK)
		seq_buf_म_लिखो(&s, "flush_fail ");

	अगर (flags & PAPR_PMEM_BAD_RESTORE_MASK)
		seq_buf_म_लिखो(&s, "restore_fail ");

	अगर (flags & PAPR_PMEM_SAVE_MASK)
		seq_buf_म_लिखो(&s, "save_fail ");

	अगर (flags & PAPR_PMEM_SMART_EVENT_MASK)
		seq_buf_म_लिखो(&s, "smart_notify ");


	अगर (seq_buf_used(&s))
		seq_buf_म_लिखो(&s, "\n");

	वापस seq_buf_used(&s);
पूर्ण
अटल DEVICE_ATTR_RO(flags);

अटल काष्ठा attribute *ndtest_nvdimm_attributes[] = अणु
	&dev_attr_nvdimm_show_handle.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_id.attr,
	&dev_attr_phys_id.attr,
	&dev_attr_subप्रणाली_venकरोr.attr,
	&dev_attr_dirty_shutकरोwn.attr,
	&dev_attr_क्रमmats.attr,
	&dev_attr_क्रमmat.attr,
	&dev_attr_क्रमmat1.attr,
	&dev_attr_flags.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ndtest_nvdimm_attribute_group = अणु
	.name = "papr",
	.attrs = ndtest_nvdimm_attributes,
	.is_visible = ndtest_nvdimm_attr_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ndtest_nvdimm_attribute_groups[] = अणु
	&ndtest_nvdimm_attribute_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ndtest_dimm_रेजिस्टर(काष्ठा ndtest_priv *priv,
				काष्ठा ndtest_dimm *dimm, पूर्णांक id)
अणु
	काष्ठा device *dev = &priv->pdev.dev;
	अचिन्हित दीर्घ dimm_flags = dimm->flags;

	अगर (dimm->num_क्रमmats > 1) अणु
		set_bit(NDD_ALIASING, &dimm_flags);
		set_bit(NDD_LABELING, &dimm_flags);
	पूर्ण

	अगर (dimm->flags & PAPR_PMEM_UNARMED_MASK)
		set_bit(NDD_UNARMED, &dimm_flags);

	dimm->nvdimm = nvdimm_create(priv->bus, dimm,
				    ndtest_nvdimm_attribute_groups, dimm_flags,
				    NDTEST_SCM_DIMM_CMD_MASK, 0, शून्य);
	अगर (!dimm->nvdimm) अणु
		dev_err(dev, "Error creating DIMM object for %pOF\n", priv->dn);
		वापस -ENXIO;
	पूर्ण

	dimm->dev = device_create_with_groups(ndtest_dimm_class,
					     &priv->pdev.dev,
					     0, dimm, dimm_attribute_groups,
					     "test_dimm%d", id);
	अगर (!dimm->dev) अणु
		pr_err("Could not create dimm device attributes\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_nvdimm_init(काष्ठा ndtest_priv *p)
अणु
	काष्ठा ndtest_dimm *d;
	व्योम *res;
	पूर्णांक i, id;

	क्रम (i = 0; i < p->config->dimm_count; i++) अणु
		d = &p->config->dimms[i];
		d->id = id = p->config->dimm_start + i;
		res = ndtest_alloc_resource(p, LABEL_SIZE, शून्य);
		अगर (!res)
			वापस -ENOMEM;

		d->label_area = res;
		प्र_लिखो(d->label_area, "label%d", id);
		d->config_size = LABEL_SIZE;

		अगर (!ndtest_alloc_resource(p, d->size,
					   &p->dimm_dma[id]))
			वापस -ENOMEM;

		अगर (!ndtest_alloc_resource(p, LABEL_SIZE,
					   &p->label_dma[id]))
			वापस -ENOMEM;

		अगर (!ndtest_alloc_resource(p, LABEL_SIZE,
					   &p->dcr_dma[id]))
			वापस -ENOMEM;

		d->address = p->dimm_dma[id];

		ndtest_dimm_रेजिस्टर(p, d, id);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार compatible_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "nvdimm_test");
पूर्ण
अटल DEVICE_ATTR_RO(compatible);

अटल काष्ठा attribute *of_node_attributes[] = अणु
	&dev_attr_compatible.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group of_node_attribute_group = अणु
	.name = "of_node",
	.attrs = of_node_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ndtest_attribute_groups[] = अणु
	&of_node_attribute_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ndtest_bus_रेजिस्टर(काष्ठा ndtest_priv *p)
अणु
	p->config = &bus_configs[p->pdev.id];

	p->bus_desc.ndctl = ndtest_ctl;
	p->bus_desc.module = THIS_MODULE;
	p->bus_desc.provider_name = शून्य;
	p->bus_desc.attr_groups = ndtest_attribute_groups;

	p->bus = nvdimm_bus_रेजिस्टर(&p->pdev.dev, &p->bus_desc);
	अगर (!p->bus) अणु
		dev_err(&p->pdev.dev, "Error creating nvdimm bus %pOF\n", p->dn);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ndtest_priv *p = to_ndtest_priv(&pdev->dev);

	nvdimm_bus_unरेजिस्टर(p->bus);
	वापस 0;
पूर्ण

अटल पूर्णांक ndtest_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ndtest_priv *p;
	पूर्णांक rc;

	p = to_ndtest_priv(&pdev->dev);
	अगर (ndtest_bus_रेजिस्टर(p))
		वापस -ENOMEM;

	p->dcr_dma = devm_kसुस्मृति(&p->pdev.dev, NUM_DCR,
				 माप(dma_addr_t), GFP_KERNEL);
	p->label_dma = devm_kसुस्मृति(&p->pdev.dev, NUM_DCR,
				   माप(dma_addr_t), GFP_KERNEL);
	p->dimm_dma = devm_kसुस्मृति(&p->pdev.dev, NUM_DCR,
				  माप(dma_addr_t), GFP_KERNEL);

	rc = ndtest_nvdimm_init(p);
	अगर (rc)
		जाओ err;

	rc = ndtest_init_regions(p);
	अगर (rc)
		जाओ err;

	rc = devm_add_action_or_reset(&pdev->dev, put_dimms, p);
	अगर (rc)
		जाओ err;

	platक्रमm_set_drvdata(pdev, p);

	वापस 0;

err:
	pr_err("%s:%d Failed nvdimm init\n", __func__, __LINE__);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ndtest_id[] = अणु
	अणु KBUILD_MODNAME पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ndtest_driver = अणु
	.probe = ndtest_probe,
	.हटाओ = ndtest_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
	पूर्ण,
	.id_table = ndtest_id,
पूर्ण;

अटल व्योम ndtest_release(काष्ठा device *dev)
अणु
	काष्ठा ndtest_priv *p = to_ndtest_priv(dev);

	kमुक्त(p);
पूर्ण

अटल व्योम cleanup_devices(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_INSTANCES; i++)
		अगर (instances[i])
			platक्रमm_device_unरेजिस्टर(&instances[i]->pdev);

	nfit_test_tearकरोwn();

	अगर (ndtest_pool)
		gen_pool_destroy(ndtest_pool);


	अगर (ndtest_dimm_class)
		class_destroy(ndtest_dimm_class);
पूर्ण

अटल __init पूर्णांक ndtest_init(व्योम)
अणु
	पूर्णांक rc, i;

	pmem_test();
	libnvdimm_test();
	device_dax_test();
	dax_pmem_test();
	dax_pmem_core_test();
#अगर_घोषित CONFIG_DEV_DAX_PMEM_COMPAT
	dax_pmem_compat_test();
#पूर्ण_अगर

	nfit_test_setup(ndtest_resource_lookup, शून्य);

	ndtest_dimm_class = class_create(THIS_MODULE, "nfit_test_dimm");
	अगर (IS_ERR(ndtest_dimm_class)) अणु
		rc = PTR_ERR(ndtest_dimm_class);
		जाओ err_रेजिस्टर;
	पूर्ण

	ndtest_pool = gen_pool_create(ilog2(SZ_4M), NUMA_NO_NODE);
	अगर (!ndtest_pool) अणु
		rc = -ENOMEM;
		जाओ err_रेजिस्टर;
	पूर्ण

	अगर (gen_pool_add(ndtest_pool, SZ_4G, SZ_4G, NUMA_NO_NODE)) अणु
		rc = -ENOMEM;
		जाओ err_रेजिस्टर;
	पूर्ण

	/* Each instance can be taken as a bus, which can have multiple dimms */
	क्रम (i = 0; i < NUM_INSTANCES; i++) अणु
		काष्ठा ndtest_priv *priv;
		काष्ठा platक्रमm_device *pdev;

		priv = kzalloc(माप(*priv), GFP_KERNEL);
		अगर (!priv) अणु
			rc = -ENOMEM;
			जाओ err_रेजिस्टर;
		पूर्ण

		INIT_LIST_HEAD(&priv->resources);
		pdev = &priv->pdev;
		pdev->name = KBUILD_MODNAME;
		pdev->id = i;
		pdev->dev.release = ndtest_release;
		rc = platक्रमm_device_रेजिस्टर(pdev);
		अगर (rc) अणु
			put_device(&pdev->dev);
			जाओ err_रेजिस्टर;
		पूर्ण
		get_device(&pdev->dev);

		instances[i] = priv;
	पूर्ण

	rc = platक्रमm_driver_रेजिस्टर(&ndtest_driver);
	अगर (rc)
		जाओ err_रेजिस्टर;

	वापस 0;

err_रेजिस्टर:
	pr_err("Error registering platform device\n");
	cleanup_devices();

	वापस rc;
पूर्ण

अटल __निकास व्योम ndtest_निकास(व्योम)
अणु
	cleanup_devices();
	platक्रमm_driver_unरेजिस्टर(&ndtest_driver);
पूर्ण

module_init(ndtest_init);
module_निकास(ndtest_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("IBM Corporation");
