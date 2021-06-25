<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __LINUX_ND_H__
#घोषणा __LINUX_ND_H__
#समावेश <linux/fs.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/device.h>
#समावेश <linux/badblocks.h>

क्रमागत nvdimm_event अणु
	NVDIMM_REVALIDATE_POISON,
	NVDIMM_REVALIDATE_REGION,
पूर्ण;

क्रमागत nvdimm_claim_class अणु
	NVDIMM_CCLASS_NONE,
	NVDIMM_CCLASS_BTT,
	NVDIMM_CCLASS_BTT2,
	NVDIMM_CCLASS_PFN,
	NVDIMM_CCLASS_DAX,
	NVDIMM_CCLASS_UNKNOWN,
पूर्ण;

काष्ठा nd_device_driver अणु
	काष्ठा device_driver drv;
	अचिन्हित दीर्घ type;
	पूर्णांक (*probe)(काष्ठा device *dev);
	व्योम (*हटाओ)(काष्ठा device *dev);
	व्योम (*shutकरोwn)(काष्ठा device *dev);
	व्योम (*notअगरy)(काष्ठा device *dev, क्रमागत nvdimm_event event);
पूर्ण;

अटल अंतरभूत काष्ठा nd_device_driver *to_nd_device_driver(
		काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा nd_device_driver, drv);
पूर्ण;

/**
 * काष्ठा nd_namespace_common - core infraकाष्ठाure of a namespace
 * @क्रमce_raw: ignore other personalities क्रम the namespace (e.g. btt)
 * @dev: device model node
 * @claim: when set a another personality has taken ownership of the namespace
 * @claim_class: restrict claim type to a given class
 * @rw_bytes: access the raw namespace capacity with byte-aligned transfers
 */
काष्ठा nd_namespace_common अणु
	पूर्णांक क्रमce_raw;
	काष्ठा device dev;
	काष्ठा device *claim;
	क्रमागत nvdimm_claim_class claim_class;
	पूर्णांक (*rw_bytes)(काष्ठा nd_namespace_common *, resource_माप_प्रकार offset,
			व्योम *buf, माप_प्रकार size, पूर्णांक rw, अचिन्हित दीर्घ flags);
पूर्ण;

अटल अंतरभूत काष्ठा nd_namespace_common *to_ndns(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा nd_namespace_common, dev);
पूर्ण

/**
 * काष्ठा nd_namespace_io - device representation of a persistent memory range
 * @dev: namespace device created by the nd region driver
 * @res: काष्ठा resource conversion of a NFIT SPA table
 * @size: cached resource_size(@res) क्रम fast path size checks
 * @addr: भव address to access the namespace range
 * @bb: badblocks list क्रम the namespace range
 */
काष्ठा nd_namespace_io अणु
	काष्ठा nd_namespace_common common;
	काष्ठा resource res;
	resource_माप_प्रकार size;
	व्योम *addr;
	काष्ठा badblocks bb;
पूर्ण;

/**
 * काष्ठा nd_namespace_pmem - namespace device क्रम dimm-backed पूर्णांकerleaved memory
 * @nsio: device and प्रणाली physical address range to drive
 * @lbasize: logical sector size क्रम the namespace in block-device-mode
 * @alt_name: namespace name supplied in the dimm label
 * @uuid: namespace name supplied in the dimm label
 * @id: ida allocated id
 */
काष्ठा nd_namespace_pmem अणु
	काष्ठा nd_namespace_io nsio;
	अचिन्हित दीर्घ lbasize;
	अक्षर *alt_name;
	u8 *uuid;
	पूर्णांक id;
पूर्ण;

/**
 * काष्ठा nd_namespace_blk - namespace क्रम dimm-bounded persistent memory
 * @alt_name: namespace name supplied in the dimm label
 * @uuid: namespace name supplied in the dimm label
 * @id: ida allocated id
 * @lbasize: blk namespaces have a native sector size when btt not present
 * @size: sum of all the resource ranges allocated to this namespace
 * @num_resources: number of dpa extents to claim
 * @res: discontiguous dpa extents क्रम given dimm
 */
काष्ठा nd_namespace_blk अणु
	काष्ठा nd_namespace_common common;
	अक्षर *alt_name;
	u8 *uuid;
	पूर्णांक id;
	अचिन्हित दीर्घ lbasize;
	resource_माप_प्रकार size;
	पूर्णांक num_resources;
	काष्ठा resource **res;
पूर्ण;

अटल अंतरभूत काष्ठा nd_namespace_io *to_nd_namespace_io(स्थिर काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा nd_namespace_io, common.dev);
पूर्ण

अटल अंतरभूत काष्ठा nd_namespace_pmem *to_nd_namespace_pmem(स्थिर काष्ठा device *dev)
अणु
	काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(dev);

	वापस container_of(nsio, काष्ठा nd_namespace_pmem, nsio);
पूर्ण

अटल अंतरभूत काष्ठा nd_namespace_blk *to_nd_namespace_blk(स्थिर काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा nd_namespace_blk, common.dev);
पूर्ण

/**
 * nvdimm_पढ़ो_bytes() - synchronously पढ़ो bytes from an nvdimm namespace
 * @ndns: device to पढ़ो
 * @offset: namespace-relative starting offset
 * @buf: buffer to fill
 * @size: transfer length
 *
 * @buf is up-to-date upon वापस from this routine.
 */
अटल अंतरभूत पूर्णांक nvdimm_पढ़ो_bytes(काष्ठा nd_namespace_common *ndns,
		resource_माप_प्रकार offset, व्योम *buf, माप_प्रकार size,
		अचिन्हित दीर्घ flags)
अणु
	वापस ndns->rw_bytes(ndns, offset, buf, size, READ, flags);
पूर्ण

/**
 * nvdimm_ग_लिखो_bytes() - synchronously ग_लिखो bytes to an nvdimm namespace
 * @ndns: device to ग_लिखो
 * @offset: namespace-relative starting offset
 * @buf: buffer to drain
 * @size: transfer length
 *
 * NVDIMM Namepaces disks करो not implement sectors पूर्णांकernally.  Depending on
 * the @ndns, the contents of @buf may be in cpu cache, platक्रमm buffers,
 * or on backing memory media upon वापस from this routine.  Flushing
 * to media is handled पूर्णांकernal to the @ndns driver, अगर at all.
 */
अटल अंतरभूत पूर्णांक nvdimm_ग_लिखो_bytes(काष्ठा nd_namespace_common *ndns,
		resource_माप_प्रकार offset, व्योम *buf, माप_प्रकार size,
		अचिन्हित दीर्घ flags)
अणु
	वापस ndns->rw_bytes(ndns, offset, buf, size, WRITE, flags);
पूर्ण

#घोषणा MODULE_ALIAS_ND_DEVICE(type) \
	MODULE_ALIAS("nd:t" __stringअगरy(type) "*")
#घोषणा ND_DEVICE_MODALIAS_FMT "nd:t%d"

काष्ठा nd_region;
व्योम nvdimm_region_notअगरy(काष्ठा nd_region *nd_region, क्रमागत nvdimm_event event);
पूर्णांक __must_check __nd_driver_रेजिस्टर(काष्ठा nd_device_driver *nd_drv,
		काष्ठा module *module, स्थिर अक्षर *mod_name);
अटल अंतरभूत व्योम nd_driver_unरेजिस्टर(काष्ठा nd_device_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण
#घोषणा nd_driver_रेजिस्टर(driver) \
	__nd_driver_रेजिस्टर(driver, THIS_MODULE, KBUILD_MODNAME)
#घोषणा module_nd_driver(driver) \
	module_driver(driver, nd_driver_रेजिस्टर, nd_driver_unरेजिस्टर)
#पूर्ण_अगर /* __LINUX_ND_H__ */
