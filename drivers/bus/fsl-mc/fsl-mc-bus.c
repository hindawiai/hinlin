<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale Management Complex (MC) bus driver
 *
 * Copyright (C) 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2019-2020 NXP
 * Author: German Rivera <German.Rivera@मुक्तscale.com>
 *
 */

#घोषणा pr_fmt(fmt) "fsl-mc: " fmt

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/bitops.h>
#समावेश <linux/msi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/acpi.h>
#समावेश <linux/iommu.h>

#समावेश "fsl-mc-private.h"

/**
 * Default DMA mask क्रम devices on a fsl-mc bus
 */
#घोषणा FSL_MC_DEFAULT_DMA_MASK	(~0ULL)

अटल काष्ठा fsl_mc_version mc_version;

/**
 * काष्ठा fsl_mc - Private data of a "fsl,qoriq-mc" platक्रमm device
 * @root_mc_bus_dev: fsl-mc device representing the root DPRC
 * @num_translation_ranges: number of entries in addr_translation_ranges
 * @translation_ranges: array of bus to प्रणाली address translation ranges
 */
काष्ठा fsl_mc अणु
	काष्ठा fsl_mc_device *root_mc_bus_dev;
	u8 num_translation_ranges;
	काष्ठा fsl_mc_addr_translation_range *translation_ranges;
	व्योम __iomem *fsl_mc_regs;
पूर्ण;

/**
 * काष्ठा fsl_mc_addr_translation_range - bus to प्रणाली address translation
 * range
 * @mc_region_type: Type of MC region क्रम the range being translated
 * @start_mc_offset: Start MC offset of the range being translated
 * @end_mc_offset: MC offset of the first byte after the range (last MC
 * offset of the range is end_mc_offset - 1)
 * @start_phys_addr: प्रणाली physical address corresponding to start_mc_addr
 */
काष्ठा fsl_mc_addr_translation_range अणु
	क्रमागत dprc_region_type mc_region_type;
	u64 start_mc_offset;
	u64 end_mc_offset;
	phys_addr_t start_phys_addr;
पूर्ण;

#घोषणा FSL_MC_GCR1	0x0
#घोषणा GCR1_P1_STOP	BIT(31)

#घोषणा FSL_MC_FAPR	0x28
#घोषणा MC_FAPR_PL	BIT(18)
#घोषणा MC_FAPR_BMT	BIT(17)

/**
 * fsl_mc_bus_match - device to driver matching callback
 * @dev: the fsl-mc device to match against
 * @drv: the device driver to search क्रम matching fsl-mc object type
 * काष्ठाures
 *
 * Returns 1 on success, 0 otherwise.
 */
अटल पूर्णांक fsl_mc_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा fsl_mc_device_id *id;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	काष्ठा fsl_mc_driver *mc_drv = to_fsl_mc_driver(drv);
	bool found = false;

	/* When driver_override is set, only bind to the matching driver */
	अगर (mc_dev->driver_override) अणु
		found = !म_भेद(mc_dev->driver_override, mc_drv->driver.name);
		जाओ out;
	पूर्ण

	अगर (!mc_drv->match_id_table)
		जाओ out;

	/*
	 * If the object is not 'plugged' don't match.
	 * Only exception is the root DPRC, which is a special हाल.
	 */
	अगर ((mc_dev->obj_desc.state & FSL_MC_OBJ_STATE_PLUGGED) == 0 &&
	    !fsl_mc_is_root_dprc(&mc_dev->dev))
		जाओ out;

	/*
	 * Traverse the match_id table of the given driver, trying to find
	 * a matching क्रम the given device.
	 */
	क्रम (id = mc_drv->match_id_table; id->venकरोr != 0x0; id++) अणु
		अगर (id->venकरोr == mc_dev->obj_desc.venकरोr &&
		    म_भेद(id->obj_type, mc_dev->obj_desc.type) == 0) अणु
			found = true;

			अवरोध;
		पूर्ण
	पूर्ण

out:
	dev_dbg(dev, "%smatched\n", found ? "" : "not ");
	वापस found;
पूर्ण

/**
 * fsl_mc_bus_uevent - callback invoked when a device is added
 */
अटल पूर्णांक fsl_mc_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	अगर (add_uevent_var(env, "MODALIAS=fsl-mc:v%08Xd%s",
			   mc_dev->obj_desc.venकरोr,
			   mc_dev->obj_desc.type))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mc_dma_configure(काष्ठा device *dev)
अणु
	काष्ठा device *dma_dev = dev;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	u32 input_id = mc_dev->icid;

	जबतक (dev_is_fsl_mc(dma_dev))
		dma_dev = dma_dev->parent;

	अगर (dev_of_node(dma_dev))
		वापस of_dma_configure_id(dev, dma_dev->of_node, 0, &input_id);

	वापस acpi_dma_configure_id(dev, DEV_DMA_COHERENT, &input_id);
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	वापस प्र_लिखो(buf, "fsl-mc:v%08Xd%s\n", mc_dev->obj_desc.venकरोr,
		       mc_dev->obj_desc.type);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार driver_override_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	अक्षर *driver_override, *old = mc_dev->driver_override;
	अक्षर *cp;

	अगर (WARN_ON(dev->bus != &fsl_mc_bus_type))
		वापस -EINVAL;

	अगर (count >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	cp = म_अक्षर(driver_override, '\n');
	अगर (cp)
		*cp = '\0';

	अगर (म_माप(driver_override)) अणु
		mc_dev->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		kमुक्त(driver_override);
		mc_dev->driver_override = शून्य;
	पूर्ण

	kमुक्त(old);

	वापस count;
पूर्ण

अटल sमाप_प्रकार driver_override_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", mc_dev->driver_override);
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

अटल काष्ठा attribute *fsl_mc_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(fsl_mc_dev);

अटल पूर्णांक scan_fsl_mc_bus(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा fsl_mc_device *root_mc_dev;
	काष्ठा fsl_mc_bus *root_mc_bus;

	अगर (!fsl_mc_is_root_dprc(dev))
		जाओ निकास;

	root_mc_dev = to_fsl_mc_device(dev);
	root_mc_bus = to_fsl_mc_bus(root_mc_dev);
	mutex_lock(&root_mc_bus->scan_mutex);
	dprc_scan_objects(root_mc_dev, शून्य);
	mutex_unlock(&root_mc_bus->scan_mutex);

निकास:
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rescan_store(काष्ठा bus_type *bus,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val)
		bus_क्रम_each_dev(bus, शून्य, शून्य, scan_fsl_mc_bus);

	वापस count;
पूर्ण
अटल BUS_ATTR_WO(rescan);

अटल पूर्णांक fsl_mc_bus_set_स्वतःrescan(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा fsl_mc_device *root_mc_dev;
	अचिन्हित दीर्घ val;
	अक्षर *buf = data;

	अगर (!fsl_mc_is_root_dprc(dev))
		जाओ निकास;

	root_mc_dev = to_fsl_mc_device(dev);

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val)
		enable_dprc_irq(root_mc_dev);
	अन्यथा
		disable_dprc_irq(root_mc_dev);

निकास:
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mc_bus_get_स्वतःrescan(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा fsl_mc_device *root_mc_dev;
	अक्षर *buf = data;

	अगर (!fsl_mc_is_root_dprc(dev))
		जाओ निकास;

	root_mc_dev = to_fsl_mc_device(dev);

	प्र_लिखो(buf, "%d\n", get_dprc_irq_state(root_mc_dev));
निकास:
	वापस 0;
पूर्ण

अटल sमाप_प्रकार स्वतःrescan_store(काष्ठा bus_type *bus,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bus_क्रम_each_dev(bus, शून्य, (व्योम *)buf, fsl_mc_bus_set_स्वतःrescan);

	वापस count;
पूर्ण

अटल sमाप_प्रकार स्वतःrescan_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	bus_क्रम_each_dev(bus, शून्य, (व्योम *)buf, fsl_mc_bus_get_स्वतःrescan);
	वापस म_माप(buf);
पूर्ण

अटल BUS_ATTR_RW(स्वतःrescan);

अटल काष्ठा attribute *fsl_mc_bus_attrs[] = अणु
	&bus_attr_rescan.attr,
	&bus_attr_स्वतःrescan.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(fsl_mc_bus);

काष्ठा bus_type fsl_mc_bus_type = अणु
	.name = "fsl-mc",
	.match = fsl_mc_bus_match,
	.uevent = fsl_mc_bus_uevent,
	.dma_configure  = fsl_mc_dma_configure,
	.dev_groups = fsl_mc_dev_groups,
	.bus_groups = fsl_mc_bus_groups,
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_type);

काष्ठा device_type fsl_mc_bus_dprc_type = अणु
	.name = "fsl_mc_bus_dprc"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dprc_type);

काष्ठा device_type fsl_mc_bus_dpni_type = अणु
	.name = "fsl_mc_bus_dpni"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpni_type);

काष्ठा device_type fsl_mc_bus_dpio_type = अणु
	.name = "fsl_mc_bus_dpio"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpio_type);

काष्ठा device_type fsl_mc_bus_dpsw_type = अणु
	.name = "fsl_mc_bus_dpsw"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpsw_type);

काष्ठा device_type fsl_mc_bus_dpbp_type = अणु
	.name = "fsl_mc_bus_dpbp"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpbp_type);

काष्ठा device_type fsl_mc_bus_dpcon_type = अणु
	.name = "fsl_mc_bus_dpcon"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpcon_type);

काष्ठा device_type fsl_mc_bus_dpmcp_type = अणु
	.name = "fsl_mc_bus_dpmcp"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpmcp_type);

काष्ठा device_type fsl_mc_bus_dpmac_type = अणु
	.name = "fsl_mc_bus_dpmac"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpmac_type);

काष्ठा device_type fsl_mc_bus_dprtc_type = अणु
	.name = "fsl_mc_bus_dprtc"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dprtc_type);

काष्ठा device_type fsl_mc_bus_dpseci_type = अणु
	.name = "fsl_mc_bus_dpseci"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpseci_type);

काष्ठा device_type fsl_mc_bus_dpdmux_type = अणु
	.name = "fsl_mc_bus_dpdmux"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpdmux_type);

काष्ठा device_type fsl_mc_bus_dpdcei_type = अणु
	.name = "fsl_mc_bus_dpdcei"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpdcei_type);

काष्ठा device_type fsl_mc_bus_dpaiop_type = अणु
	.name = "fsl_mc_bus_dpaiop"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpaiop_type);

काष्ठा device_type fsl_mc_bus_dpci_type = अणु
	.name = "fsl_mc_bus_dpci"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpci_type);

काष्ठा device_type fsl_mc_bus_dpdmai_type = अणु
	.name = "fsl_mc_bus_dpdmai"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpdmai_type);

काष्ठा device_type fsl_mc_bus_dpdbg_type = अणु
	.name = "fsl_mc_bus_dpdbg"
पूर्ण;
EXPORT_SYMBOL_GPL(fsl_mc_bus_dpdbg_type);

अटल काष्ठा device_type *fsl_mc_get_device_type(स्थिर अक्षर *type)
अणु
	अटल स्थिर काष्ठा अणु
		काष्ठा device_type *dev_type;
		स्थिर अक्षर *type;
	पूर्ण dev_types[] = अणु
		अणु &fsl_mc_bus_dprc_type, "dprc" पूर्ण,
		अणु &fsl_mc_bus_dpni_type, "dpni" पूर्ण,
		अणु &fsl_mc_bus_dpio_type, "dpio" पूर्ण,
		अणु &fsl_mc_bus_dpsw_type, "dpsw" पूर्ण,
		अणु &fsl_mc_bus_dpbp_type, "dpbp" पूर्ण,
		अणु &fsl_mc_bus_dpcon_type, "dpcon" पूर्ण,
		अणु &fsl_mc_bus_dpmcp_type, "dpmcp" पूर्ण,
		अणु &fsl_mc_bus_dpmac_type, "dpmac" पूर्ण,
		अणु &fsl_mc_bus_dprtc_type, "dprtc" पूर्ण,
		अणु &fsl_mc_bus_dpseci_type, "dpseci" पूर्ण,
		अणु &fsl_mc_bus_dpdmux_type, "dpdmux" पूर्ण,
		अणु &fsl_mc_bus_dpdcei_type, "dpdcei" पूर्ण,
		अणु &fsl_mc_bus_dpaiop_type, "dpaiop" पूर्ण,
		अणु &fsl_mc_bus_dpci_type, "dpci" पूर्ण,
		अणु &fsl_mc_bus_dpdmai_type, "dpdmai" पूर्ण,
		अणु &fsl_mc_bus_dpdbg_type, "dpdbg" पूर्ण,
		अणु शून्य, शून्य पूर्ण
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; dev_types[i].dev_type; i++)
		अगर (!म_भेद(dev_types[i].type, type))
			वापस dev_types[i].dev_type;

	वापस शून्य;
पूर्ण

अटल पूर्णांक fsl_mc_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा fsl_mc_driver *mc_drv;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	पूर्णांक error;

	mc_drv = to_fsl_mc_driver(dev->driver);

	error = mc_drv->probe(mc_dev);
	अगर (error < 0) अणु
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "%s failed: %d\n", __func__, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mc_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा fsl_mc_driver *mc_drv = to_fsl_mc_driver(dev->driver);
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	पूर्णांक error;

	error = mc_drv->हटाओ(mc_dev);
	अगर (error < 0) अणु
		dev_err(dev, "%s failed: %d\n", __func__, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_mc_driver_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा fsl_mc_driver *mc_drv = to_fsl_mc_driver(dev->driver);
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	mc_drv->shutकरोwn(mc_dev);
पूर्ण

/**
 * __fsl_mc_driver_रेजिस्टर - रेजिस्टरs a child device driver with the
 * MC bus
 *
 * This function is implicitly invoked from the registration function of
 * fsl_mc device drivers, which is generated by the
 * module_fsl_mc_driver() macro.
 */
पूर्णांक __fsl_mc_driver_रेजिस्टर(काष्ठा fsl_mc_driver *mc_driver,
			     काष्ठा module *owner)
अणु
	पूर्णांक error;

	mc_driver->driver.owner = owner;
	mc_driver->driver.bus = &fsl_mc_bus_type;

	अगर (mc_driver->probe)
		mc_driver->driver.probe = fsl_mc_driver_probe;

	अगर (mc_driver->हटाओ)
		mc_driver->driver.हटाओ = fsl_mc_driver_हटाओ;

	अगर (mc_driver->shutकरोwn)
		mc_driver->driver.shutकरोwn = fsl_mc_driver_shutकरोwn;

	error = driver_रेजिस्टर(&mc_driver->driver);
	अगर (error < 0) अणु
		pr_err("driver_register() failed for %s: %d\n",
		       mc_driver->driver.name, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__fsl_mc_driver_रेजिस्टर);

/**
 * fsl_mc_driver_unरेजिस्टर - unरेजिस्टरs a device driver from the
 * MC bus
 */
व्योम fsl_mc_driver_unरेजिस्टर(काष्ठा fsl_mc_driver *mc_driver)
अणु
	driver_unरेजिस्टर(&mc_driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_driver_unरेजिस्टर);

/**
 * mc_get_version() - Retrieves the Management Complex firmware
 *			version inक्रमmation
 * @mc_io:		Poपूर्णांकer to opaque I/O object
 * @cmd_flags:		Command flags; one or more of 'MC_CMD_FLAG_'
 * @mc_ver_info:	Returned version inक्रमmation काष्ठाure
 *
 * Return:	'0' on Success; Error code otherwise.
 */
अटल पूर्णांक mc_get_version(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  काष्ठा fsl_mc_version *mc_ver_info)
अणु
	काष्ठा fsl_mc_command cmd = अणु 0 पूर्ण;
	काष्ठा dpmng_rsp_get_version *rsp_params;
	पूर्णांक err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMNG_CMDID_GET_VERSION,
					  cmd_flags,
					  0);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	अगर (err)
		वापस err;

	/* retrieve response parameters */
	rsp_params = (काष्ठा dpmng_rsp_get_version *)cmd.params;
	mc_ver_info->revision = le32_to_cpu(rsp_params->revision);
	mc_ver_info->major = le32_to_cpu(rsp_params->version_major);
	mc_ver_info->minor = le32_to_cpu(rsp_params->version_minor);

	वापस 0;
पूर्ण

/**
 * fsl_mc_get_version - function to retrieve the MC f/w version inक्रमmation
 *
 * Return:	mc version when called after fsl-mc-bus probe; शून्य otherwise.
 */
काष्ठा fsl_mc_version *fsl_mc_get_version(व्योम)
अणु
	अगर (mc_version.major)
		वापस &mc_version;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_get_version);

/**
 * fsl_mc_get_root_dprc - function to traverse to the root dprc
 */
व्योम fsl_mc_get_root_dprc(काष्ठा device *dev,
			 काष्ठा device **root_dprc_dev)
अणु
	अगर (!dev) अणु
		*root_dprc_dev = शून्य;
	पूर्ण अन्यथा अगर (!dev_is_fsl_mc(dev)) अणु
		*root_dprc_dev = शून्य;
	पूर्ण अन्यथा अणु
		*root_dprc_dev = dev;
		जबतक (dev_is_fsl_mc((*root_dprc_dev)->parent))
			*root_dprc_dev = (*root_dprc_dev)->parent;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dprc_attr(काष्ठा fsl_mc_io *mc_io,
			 पूर्णांक container_id, काष्ठा dprc_attributes *attr)
अणु
	u16 dprc_handle;
	पूर्णांक error;

	error = dprc_खोलो(mc_io, 0, container_id, &dprc_handle);
	अगर (error < 0) अणु
		dev_err(mc_io->dev, "dprc_open() failed: %d\n", error);
		वापस error;
	पूर्ण

	स_रखो(attr, 0, माप(काष्ठा dprc_attributes));
	error = dprc_get_attributes(mc_io, 0, dprc_handle, attr);
	अगर (error < 0) अणु
		dev_err(mc_io->dev, "dprc_get_attributes() failed: %d\n",
			error);
		जाओ common_cleanup;
	पूर्ण

	error = 0;

common_cleanup:
	(व्योम)dprc_बंद(mc_io, 0, dprc_handle);
	वापस error;
पूर्ण

अटल पूर्णांक get_dprc_icid(काष्ठा fsl_mc_io *mc_io,
			 पूर्णांक container_id, u32 *icid)
अणु
	काष्ठा dprc_attributes attr;
	पूर्णांक error;

	error = get_dprc_attr(mc_io, container_id, &attr);
	अगर (error == 0)
		*icid = attr.icid;

	वापस error;
पूर्ण

अटल पूर्णांक translate_mc_addr(काष्ठा fsl_mc_device *mc_dev,
			     क्रमागत dprc_region_type mc_region_type,
			     u64 mc_offset, phys_addr_t *phys_addr)
अणु
	पूर्णांक i;
	काष्ठा device *root_dprc_dev;
	काष्ठा fsl_mc *mc;

	fsl_mc_get_root_dprc(&mc_dev->dev, &root_dprc_dev);
	mc = dev_get_drvdata(root_dprc_dev->parent);

	अगर (mc->num_translation_ranges == 0) अणु
		/*
		 * Do identity mapping:
		 */
		*phys_addr = mc_offset;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < mc->num_translation_ranges; i++) अणु
		काष्ठा fsl_mc_addr_translation_range *range =
			&mc->translation_ranges[i];

		अगर (mc_region_type == range->mc_region_type &&
		    mc_offset >= range->start_mc_offset &&
		    mc_offset < range->end_mc_offset) अणु
			*phys_addr = range->start_phys_addr +
				     (mc_offset - range->start_mc_offset);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EFAULT;
पूर्ण

अटल पूर्णांक fsl_mc_device_get_mmio_regions(काष्ठा fsl_mc_device *mc_dev,
					  काष्ठा fsl_mc_device *mc_bus_dev)
अणु
	पूर्णांक i;
	पूर्णांक error;
	काष्ठा resource *regions;
	काष्ठा fsl_mc_obj_desc *obj_desc = &mc_dev->obj_desc;
	काष्ठा device *parent_dev = mc_dev->dev.parent;
	क्रमागत dprc_region_type mc_region_type;

	अगर (is_fsl_mc_bus_dprc(mc_dev) ||
	    is_fsl_mc_bus_dpmcp(mc_dev)) अणु
		mc_region_type = DPRC_REGION_TYPE_MC_PORTAL;
	पूर्ण अन्यथा अगर (is_fsl_mc_bus_dpio(mc_dev)) अणु
		mc_region_type = DPRC_REGION_TYPE_QBMAN_PORTAL;
	पूर्ण अन्यथा अणु
		/*
		 * This function should not have been called क्रम this MC object
		 * type, as this object type is not supposed to have MMIO
		 * regions
		 */
		वापस -EINVAL;
	पूर्ण

	regions = kदो_स्मृति_array(obj_desc->region_count,
				माप(regions[0]), GFP_KERNEL);
	अगर (!regions)
		वापस -ENOMEM;

	क्रम (i = 0; i < obj_desc->region_count; i++) अणु
		काष्ठा dprc_region_desc region_desc;

		error = dprc_get_obj_region(mc_bus_dev->mc_io,
					    0,
					    mc_bus_dev->mc_handle,
					    obj_desc->type,
					    obj_desc->id, i, &region_desc);
		अगर (error < 0) अणु
			dev_err(parent_dev,
				"dprc_get_obj_region() failed: %d\n", error);
			जाओ error_cleanup_regions;
		पूर्ण
		/*
		 * Older MC only वापसed region offset and no base address
		 * If base address is in the region_desc use it otherwise
		 * revert to old mechanism
		 */
		अगर (region_desc.base_address)
			regions[i].start = region_desc.base_address +
						region_desc.base_offset;
		अन्यथा
			error = translate_mc_addr(mc_dev, mc_region_type,
					  region_desc.base_offset,
					  &regions[i].start);

		अगर (error < 0) अणु
			dev_err(parent_dev,
				"Invalid MC offset: %#x (for %s.%d\'s region %d)\n",
				region_desc.base_offset,
				obj_desc->type, obj_desc->id, i);
			जाओ error_cleanup_regions;
		पूर्ण

		regions[i].end = regions[i].start + region_desc.size - 1;
		regions[i].name = "fsl-mc object MMIO region";
		regions[i].flags = region_desc.flags & IORESOURCE_BITS;
		regions[i].flags |= IORESOURCE_MEM;
	पूर्ण

	mc_dev->regions = regions;
	वापस 0;

error_cleanup_regions:
	kमुक्त(regions);
	वापस error;
पूर्ण

/**
 * fsl_mc_is_root_dprc - function to check अगर a given device is a root dprc
 */
bool fsl_mc_is_root_dprc(काष्ठा device *dev)
अणु
	काष्ठा device *root_dprc_dev;

	fsl_mc_get_root_dprc(dev, &root_dprc_dev);
	अगर (!root_dprc_dev)
		वापस false;
	वापस dev == root_dprc_dev;
पूर्ण

अटल व्योम fsl_mc_device_release(काष्ठा device *dev)
अणु
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	kमुक्त(mc_dev->regions);

	अगर (is_fsl_mc_bus_dprc(mc_dev))
		kमुक्त(to_fsl_mc_bus(mc_dev));
	अन्यथा
		kमुक्त(mc_dev);
पूर्ण

/**
 * Add a newly discovered fsl-mc device to be visible in Linux
 */
पूर्णांक fsl_mc_device_add(काष्ठा fsl_mc_obj_desc *obj_desc,
		      काष्ठा fsl_mc_io *mc_io,
		      काष्ठा device *parent_dev,
		      काष्ठा fsl_mc_device **new_mc_dev)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device *mc_dev = शून्य;
	काष्ठा fsl_mc_bus *mc_bus = शून्य;
	काष्ठा fsl_mc_device *parent_mc_dev;

	अगर (dev_is_fsl_mc(parent_dev))
		parent_mc_dev = to_fsl_mc_device(parent_dev);
	अन्यथा
		parent_mc_dev = शून्य;

	अगर (म_भेद(obj_desc->type, "dprc") == 0) अणु
		/*
		 * Allocate an MC bus device object:
		 */
		mc_bus = kzalloc(माप(*mc_bus), GFP_KERNEL);
		अगर (!mc_bus)
			वापस -ENOMEM;

		mutex_init(&mc_bus->scan_mutex);
		mc_dev = &mc_bus->mc_dev;
	पूर्ण अन्यथा अणु
		/*
		 * Allocate a regular fsl_mc_device object:
		 */
		mc_dev = kzalloc(माप(*mc_dev), GFP_KERNEL);
		अगर (!mc_dev)
			वापस -ENOMEM;
	पूर्ण

	mc_dev->obj_desc = *obj_desc;
	mc_dev->mc_io = mc_io;
	device_initialize(&mc_dev->dev);
	mc_dev->dev.parent = parent_dev;
	mc_dev->dev.bus = &fsl_mc_bus_type;
	mc_dev->dev.release = fsl_mc_device_release;
	mc_dev->dev.type = fsl_mc_get_device_type(obj_desc->type);
	अगर (!mc_dev->dev.type) अणु
		error = -ENODEV;
		dev_err(parent_dev, "unknown device type %s\n", obj_desc->type);
		जाओ error_cleanup_dev;
	पूर्ण
	dev_set_name(&mc_dev->dev, "%s.%d", obj_desc->type, obj_desc->id);

	अगर (म_भेद(obj_desc->type, "dprc") == 0) अणु
		काष्ठा fsl_mc_io *mc_io2;

		mc_dev->flags |= FSL_MC_IS_DPRC;

		/*
		 * To get the DPRC's ICID, we need to खोलो the DPRC
		 * in get_dprc_icid(). For child DPRCs, we करो so using the
		 * parent DPRC's MC portal instead of the child DPRC's MC
		 * portal, in हाल the child DPRC is alपढ़ोy खोलोed with
		 * its own portal (e.g., the DPRC used by AIOP).
		 *
		 * NOTE: There cannot be more than one active खोलो क्रम a
		 * given MC object, using the same MC portal.
		 */
		अगर (parent_mc_dev) अणु
			/*
			 * device being added is a child DPRC device
			 */
			mc_io2 = parent_mc_dev->mc_io;
		पूर्ण अन्यथा अणु
			/*
			 * device being added is the root DPRC device
			 */
			अगर (!mc_io) अणु
				error = -EINVAL;
				जाओ error_cleanup_dev;
			पूर्ण

			mc_io2 = mc_io;
		पूर्ण

		error = get_dprc_icid(mc_io2, obj_desc->id, &mc_dev->icid);
		अगर (error < 0)
			जाओ error_cleanup_dev;
	पूर्ण अन्यथा अणु
		/*
		 * A non-DPRC object has to be a child of a DPRC, use the
		 * parent's ICID and पूर्णांकerrupt करोमुख्य.
		 */
		mc_dev->icid = parent_mc_dev->icid;
		mc_dev->dma_mask = FSL_MC_DEFAULT_DMA_MASK;
		mc_dev->dev.dma_mask = &mc_dev->dma_mask;
		mc_dev->dev.coherent_dma_mask = mc_dev->dma_mask;
		dev_set_msi_करोमुख्य(&mc_dev->dev,
				   dev_get_msi_करोमुख्य(&parent_mc_dev->dev));
	पूर्ण

	/*
	 * Get MMIO regions क्रम the device from the MC:
	 *
	 * NOTE: the root DPRC is a special हाल as its MMIO region is
	 * obtained from the device tree
	 */
	अगर (parent_mc_dev && obj_desc->region_count != 0) अणु
		error = fsl_mc_device_get_mmio_regions(mc_dev,
						       parent_mc_dev);
		अगर (error < 0)
			जाओ error_cleanup_dev;
	पूर्ण

	/*
	 * The device-specअगरic probe callback will get invoked by device_add()
	 */
	error = device_add(&mc_dev->dev);
	अगर (error < 0) अणु
		dev_err(parent_dev,
			"device_add() failed for device %s: %d\n",
			dev_name(&mc_dev->dev), error);
		जाओ error_cleanup_dev;
	पूर्ण

	dev_dbg(parent_dev, "added %s\n", dev_name(&mc_dev->dev));

	*new_mc_dev = mc_dev;
	वापस 0;

error_cleanup_dev:
	kमुक्त(mc_dev->regions);
	kमुक्त(mc_bus);
	kमुक्त(mc_dev);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_device_add);

/**
 * fsl_mc_device_हटाओ - Remove an fsl-mc device from being visible to
 * Linux
 *
 * @mc_dev: Poपूर्णांकer to an fsl-mc device
 */
व्योम fsl_mc_device_हटाओ(काष्ठा fsl_mc_device *mc_dev)
अणु
	kमुक्त(mc_dev->driver_override);
	mc_dev->driver_override = शून्य;

	/*
	 * The device-specअगरic हटाओ callback will get invoked by device_del()
	 */
	device_del(&mc_dev->dev);
	put_device(&mc_dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_device_हटाओ);

काष्ठा fsl_mc_device *fsl_mc_get_endpoपूर्णांक(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_device *mc_bus_dev, *endpoपूर्णांक;
	काष्ठा fsl_mc_obj_desc endpoपूर्णांक_desc = अणुअणु 0 पूर्णपूर्ण;
	काष्ठा dprc_endpoपूर्णांक endpoपूर्णांक1 = अणुअणु 0 पूर्णपूर्ण;
	काष्ठा dprc_endpoपूर्णांक endpoपूर्णांक2 = अणुअणु 0 पूर्णपूर्ण;
	पूर्णांक state, err;

	mc_bus_dev = to_fsl_mc_device(mc_dev->dev.parent);
	म_नकल(endpoपूर्णांक1.type, mc_dev->obj_desc.type);
	endpoपूर्णांक1.id = mc_dev->obj_desc.id;

	err = dprc_get_connection(mc_bus_dev->mc_io, 0,
				  mc_bus_dev->mc_handle,
				  &endpoपूर्णांक1, &endpoपूर्णांक2,
				  &state);

	अगर (err == -ENOTCONN || state == -1)
		वापस ERR_PTR(-ENOTCONN);

	अगर (err < 0) अणु
		dev_err(&mc_bus_dev->dev, "dprc_get_connection() = %d\n", err);
		वापस ERR_PTR(err);
	पूर्ण

	म_नकल(endpoपूर्णांक_desc.type, endpoपूर्णांक2.type);
	endpoपूर्णांक_desc.id = endpoपूर्णांक2.id;
	endpoपूर्णांक = fsl_mc_device_lookup(&endpoपूर्णांक_desc, mc_bus_dev);

	/*
	 * We know that the device has an endpoपूर्णांक because we verअगरied by
	 * पूर्णांकerrogating the firmware. This is the हाल when the device was not
	 * yet discovered by the fsl-mc bus, thus the lookup वापसed शून्य.
	 * Dअगरferentiate this हाल by वापसing EPROBE_DEFER.
	 */
	अगर (!endpoपूर्णांक)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस endpoपूर्णांक;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_get_endpoपूर्णांक);

अटल पूर्णांक parse_mc_ranges(काष्ठा device *dev,
			   पूर्णांक *paddr_cells,
			   पूर्णांक *mc_addr_cells,
			   पूर्णांक *mc_size_cells,
			   स्थिर __be32 **ranges_start)
अणु
	स्थिर __be32 *prop;
	पूर्णांक range_tuple_cell_count;
	पूर्णांक ranges_len;
	पूर्णांक tuple_len;
	काष्ठा device_node *mc_node = dev->of_node;

	*ranges_start = of_get_property(mc_node, "ranges", &ranges_len);
	अगर (!(*ranges_start) || !ranges_len) अणु
		dev_warn(dev,
			 "missing or empty ranges property for device tree node '%pOFn'\n",
			 mc_node);
		वापस 0;
	पूर्ण

	*paddr_cells = of_n_addr_cells(mc_node);

	prop = of_get_property(mc_node, "#address-cells", शून्य);
	अगर (prop)
		*mc_addr_cells = be32_to_cpup(prop);
	अन्यथा
		*mc_addr_cells = *paddr_cells;

	prop = of_get_property(mc_node, "#size-cells", शून्य);
	अगर (prop)
		*mc_size_cells = be32_to_cpup(prop);
	अन्यथा
		*mc_size_cells = of_n_size_cells(mc_node);

	range_tuple_cell_count = *paddr_cells + *mc_addr_cells +
				 *mc_size_cells;

	tuple_len = range_tuple_cell_count * माप(__be32);
	अगर (ranges_len % tuple_len != 0) अणु
		dev_err(dev, "malformed ranges property '%pOFn'\n", mc_node);
		वापस -EINVAL;
	पूर्ण

	वापस ranges_len / tuple_len;
पूर्ण

अटल पूर्णांक get_mc_addr_translation_ranges(काष्ठा device *dev,
					  काष्ठा fsl_mc_addr_translation_range
						**ranges,
					  u8 *num_ranges)
अणु
	पूर्णांक ret;
	पूर्णांक paddr_cells;
	पूर्णांक mc_addr_cells;
	पूर्णांक mc_size_cells;
	पूर्णांक i;
	स्थिर __be32 *ranges_start;
	स्थिर __be32 *cell;

	ret = parse_mc_ranges(dev,
			      &paddr_cells,
			      &mc_addr_cells,
			      &mc_size_cells,
			      &ranges_start);
	अगर (ret < 0)
		वापस ret;

	*num_ranges = ret;
	अगर (!ret) अणु
		/*
		 * Missing or empty ranges property ("ranges;") क्रम the
		 * 'fsl,qoriq-mc' node. In this हाल, identity mapping
		 * will be used.
		 */
		*ranges = शून्य;
		वापस 0;
	पूर्ण

	*ranges = devm_kसुस्मृति(dev, *num_ranges,
			       माप(काष्ठा fsl_mc_addr_translation_range),
			       GFP_KERNEL);
	अगर (!(*ranges))
		वापस -ENOMEM;

	cell = ranges_start;
	क्रम (i = 0; i < *num_ranges; ++i) अणु
		काष्ठा fsl_mc_addr_translation_range *range = &(*ranges)[i];

		range->mc_region_type = of_पढ़ो_number(cell, 1);
		range->start_mc_offset = of_पढ़ो_number(cell + 1,
							mc_addr_cells - 1);
		cell += mc_addr_cells;
		range->start_phys_addr = of_पढ़ो_number(cell, paddr_cells);
		cell += paddr_cells;
		range->end_mc_offset = range->start_mc_offset +
				     of_पढ़ो_number(cell, mc_size_cells);

		cell += mc_size_cells;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fsl_mc_bus_probe - callback invoked when the root MC bus is being
 * added
 */
अटल पूर्णांक fsl_mc_bus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_mc_obj_desc obj_desc;
	पूर्णांक error;
	काष्ठा fsl_mc *mc;
	काष्ठा fsl_mc_device *mc_bus_dev = शून्य;
	काष्ठा fsl_mc_io *mc_io = शून्य;
	पूर्णांक container_id;
	phys_addr_t mc_portal_phys_addr;
	u32 mc_portal_size, mc_stream_id;
	काष्ठा resource *plat_res;

	mc = devm_kzalloc(&pdev->dev, माप(*mc), GFP_KERNEL);
	अगर (!mc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mc);

	plat_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (plat_res) अणु
		mc->fsl_mc_regs = devm_ioremap_resource(&pdev->dev, plat_res);
		अगर (IS_ERR(mc->fsl_mc_regs))
			वापस PTR_ERR(mc->fsl_mc_regs);
	पूर्ण

	अगर (mc->fsl_mc_regs) अणु
		/*
		 * Some bootloaders छोड़ो the MC firmware beक्रमe booting the
		 * kernel so that MC will not cause faults as soon as the
		 * SMMU probes due to the fact that there's no configuration
		 * in place क्रम MC.
		 * At this poपूर्णांक MC should have all its SMMU setup करोne so make
		 * sure it is resumed.
		 */
		ग_लिखोl(पढ़ोl(mc->fsl_mc_regs + FSL_MC_GCR1) & (~GCR1_P1_STOP),
		       mc->fsl_mc_regs + FSL_MC_GCR1);

		अगर (IS_ENABLED(CONFIG_ACPI) && !dev_of_node(&pdev->dev)) अणु
			mc_stream_id = पढ़ोl(mc->fsl_mc_regs + FSL_MC_FAPR);
			/*
			 * HW ORs the PL and BMT bit, places the result in bit
			 * 14 of the StreamID and ORs in the ICID. Calculate it
			 * accordingly.
			 */
			mc_stream_id = (mc_stream_id & 0xffff) |
				((mc_stream_id & (MC_FAPR_PL | MC_FAPR_BMT)) ?
					BIT(14) : 0);
			error = acpi_dma_configure_id(&pdev->dev,
						      DEV_DMA_COHERENT,
						      &mc_stream_id);
			अगर (error)
				dev_warn(&pdev->dev,
					 "failed to configure dma: %d.\n",
					 error);
		पूर्ण
	पूर्ण

	/*
	 * Get physical address of MC portal क्रम the root DPRC:
	 */
	plat_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mc_portal_phys_addr = plat_res->start;
	mc_portal_size = resource_size(plat_res);
	error = fsl_create_mc_io(&pdev->dev, mc_portal_phys_addr,
				 mc_portal_size, शून्य,
				 FSL_MC_IO_ATOMIC_CONTEXT_PORTAL, &mc_io);
	अगर (error < 0)
		वापस error;

	error = mc_get_version(mc_io, 0, &mc_version);
	अगर (error != 0) अणु
		dev_err(&pdev->dev,
			"mc_get_version() failed with error %d\n", error);
		जाओ error_cleanup_mc_io;
	पूर्ण

	dev_info(&pdev->dev, "MC firmware version: %u.%u.%u\n",
		 mc_version.major, mc_version.minor, mc_version.revision);

	अगर (dev_of_node(&pdev->dev)) अणु
		error = get_mc_addr_translation_ranges(&pdev->dev,
						&mc->translation_ranges,
						&mc->num_translation_ranges);
		अगर (error < 0)
			जाओ error_cleanup_mc_io;
	पूर्ण

	error = dprc_get_container_id(mc_io, 0, &container_id);
	अगर (error < 0) अणु
		dev_err(&pdev->dev,
			"dprc_get_container_id() failed: %d\n", error);
		जाओ error_cleanup_mc_io;
	पूर्ण

	स_रखो(&obj_desc, 0, माप(काष्ठा fsl_mc_obj_desc));
	error = dprc_get_api_version(mc_io, 0,
				     &obj_desc.ver_major,
				     &obj_desc.ver_minor);
	अगर (error < 0)
		जाओ error_cleanup_mc_io;

	obj_desc.venकरोr = FSL_MC_VENDOR_FREESCALE;
	म_नकल(obj_desc.type, "dprc");
	obj_desc.id = container_id;
	obj_desc.irq_count = 1;
	obj_desc.region_count = 0;

	error = fsl_mc_device_add(&obj_desc, mc_io, &pdev->dev, &mc_bus_dev);
	अगर (error < 0)
		जाओ error_cleanup_mc_io;

	mc->root_mc_bus_dev = mc_bus_dev;
	mc_bus_dev->dev.fwnode = pdev->dev.fwnode;
	वापस 0;

error_cleanup_mc_io:
	fsl_destroy_mc_io(mc_io);
	वापस error;
पूर्ण

/**
 * fsl_mc_bus_हटाओ - callback invoked when the root MC bus is being
 * हटाओd
 */
अटल पूर्णांक fsl_mc_bus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_mc *mc = platक्रमm_get_drvdata(pdev);

	अगर (!fsl_mc_is_root_dprc(&mc->root_mc_bus_dev->dev))
		वापस -EINVAL;

	fsl_mc_device_हटाओ(mc->root_mc_bus_dev);

	fsl_destroy_mc_io(mc->root_mc_bus_dev->mc_io);
	mc->root_mc_bus_dev->mc_io = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_mc_bus_match_table[] = अणु
	अणु.compatible = "fsl,qoriq-mc",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, fsl_mc_bus_match_table);

अटल स्थिर काष्ठा acpi_device_id fsl_mc_bus_acpi_match_table[] = अणु
	अणु"NXP0008", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fsl_mc_bus_acpi_match_table);

अटल काष्ठा platक्रमm_driver fsl_mc_bus_driver = अणु
	.driver = अणु
		   .name = "fsl_mc_bus",
		   .pm = शून्य,
		   .of_match_table = fsl_mc_bus_match_table,
		   .acpi_match_table = fsl_mc_bus_acpi_match_table,
		   पूर्ण,
	.probe = fsl_mc_bus_probe,
	.हटाओ = fsl_mc_bus_हटाओ,
पूर्ण;

अटल पूर्णांक __init fsl_mc_bus_driver_init(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर(&fsl_mc_bus_type);
	अगर (error < 0) अणु
		pr_err("bus type registration failed: %d\n", error);
		जाओ error_cleanup_cache;
	पूर्ण

	error = platक्रमm_driver_रेजिस्टर(&fsl_mc_bus_driver);
	अगर (error < 0) अणु
		pr_err("platform_driver_register() failed: %d\n", error);
		जाओ error_cleanup_bus;
	पूर्ण

	error = dprc_driver_init();
	अगर (error < 0)
		जाओ error_cleanup_driver;

	error = fsl_mc_allocator_driver_init();
	अगर (error < 0)
		जाओ error_cleanup_dprc_driver;

	वापस 0;

error_cleanup_dprc_driver:
	dprc_driver_निकास();

error_cleanup_driver:
	platक्रमm_driver_unरेजिस्टर(&fsl_mc_bus_driver);

error_cleanup_bus:
	bus_unरेजिस्टर(&fsl_mc_bus_type);

error_cleanup_cache:
	वापस error;
पूर्ण
postcore_initcall(fsl_mc_bus_driver_init);
