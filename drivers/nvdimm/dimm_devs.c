<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/device.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश "nd-core.h"
#समावेश "label.h"
#समावेश "pmem.h"
#समावेश "nd.h"

अटल DEFINE_IDA(dimm_ida);

अटल bool noblk;
module_param(noblk, bool, 0444);
MODULE_PARM_DESC(noblk, "force disable BLK / local alias support");

/*
 * Retrieve bus and dimm handle and वापस अगर this bus supports
 * get_config_data commands
 */
पूर्णांक nvdimm_check_config_data(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	अगर (!nvdimm->cmd_mask ||
	    !test_bit(ND_CMD_GET_CONFIG_DATA, &nvdimm->cmd_mask)) अणु
		अगर (test_bit(NDD_LABELING, &nvdimm->flags))
			वापस -ENXIO;
		अन्यथा
			वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_dimm(काष्ठा nvdimm_drvdata *ndd)
अणु
	पूर्णांक rc;

	अगर (!ndd)
		वापस -EINVAL;

	rc = nvdimm_check_config_data(ndd->dev);
	अगर (rc)
		dev_dbg(ndd->dev, "%ps: %s error: %d\n",
				__builtin_वापस_address(0), __func__, rc);
	वापस rc;
पूर्ण

/**
 * nvdimm_init_nsarea - determine the geometry of a dimm's namespace area
 * @nvdimm: dimm to initialize
 */
पूर्णांक nvdimm_init_nsarea(काष्ठा nvdimm_drvdata *ndd)
अणु
	काष्ठा nd_cmd_get_config_size *cmd = &ndd->nsarea;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(ndd->dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	पूर्णांक rc = validate_dimm(ndd);
	पूर्णांक cmd_rc = 0;

	अगर (rc)
		वापस rc;

	अगर (cmd->config_size)
		वापस 0; /* alपढ़ोy valid */

	स_रखो(cmd, 0, माप(*cmd));
	nd_desc = nvdimm_bus->nd_desc;
	rc = nd_desc->ndctl(nd_desc, to_nvdimm(ndd->dev),
			ND_CMD_GET_CONFIG_SIZE, cmd, माप(*cmd), &cmd_rc);
	अगर (rc < 0)
		वापस rc;
	वापस cmd_rc;
पूर्ण

पूर्णांक nvdimm_get_config_data(काष्ठा nvdimm_drvdata *ndd, व्योम *buf,
			   माप_प्रकार offset, माप_प्रकार len)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(ndd->dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	पूर्णांक rc = validate_dimm(ndd), cmd_rc = 0;
	काष्ठा nd_cmd_get_config_data_hdr *cmd;
	माप_प्रकार max_cmd_size, buf_offset;

	अगर (rc)
		वापस rc;

	अगर (offset + len > ndd->nsarea.config_size)
		वापस -ENXIO;

	max_cmd_size = min_t(u32, len, ndd->nsarea.max_xfer);
	cmd = kvzalloc(max_cmd_size + माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	क्रम (buf_offset = 0; len;
	     len -= cmd->in_length, buf_offset += cmd->in_length) अणु
		माप_प्रकार cmd_size;

		cmd->in_offset = offset + buf_offset;
		cmd->in_length = min(max_cmd_size, len);

		cmd_size = माप(*cmd) + cmd->in_length;

		rc = nd_desc->ndctl(nd_desc, to_nvdimm(ndd->dev),
				ND_CMD_GET_CONFIG_DATA, cmd, cmd_size, &cmd_rc);
		अगर (rc < 0)
			अवरोध;
		अगर (cmd_rc < 0) अणु
			rc = cmd_rc;
			अवरोध;
		पूर्ण

		/* out_buf should be valid, copy it पूर्णांकo our output buffer */
		स_नकल(buf + buf_offset, cmd->out_buf, cmd->in_length);
	पूर्ण
	kvमुक्त(cmd);

	वापस rc;
पूर्ण

पूर्णांक nvdimm_set_config_data(काष्ठा nvdimm_drvdata *ndd, माप_प्रकार offset,
		व्योम *buf, माप_प्रकार len)
अणु
	माप_प्रकार max_cmd_size, buf_offset;
	काष्ठा nd_cmd_set_config_hdr *cmd;
	पूर्णांक rc = validate_dimm(ndd), cmd_rc = 0;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(ndd->dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;

	अगर (rc)
		वापस rc;

	अगर (offset + len > ndd->nsarea.config_size)
		वापस -ENXIO;

	max_cmd_size = min_t(u32, len, ndd->nsarea.max_xfer);
	cmd = kvzalloc(max_cmd_size + माप(*cmd) + माप(u32), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	क्रम (buf_offset = 0; len; len -= cmd->in_length,
			buf_offset += cmd->in_length) अणु
		माप_प्रकार cmd_size;

		cmd->in_offset = offset + buf_offset;
		cmd->in_length = min(max_cmd_size, len);
		स_नकल(cmd->in_buf, buf + buf_offset, cmd->in_length);

		/* status is output in the last 4-bytes of the command buffer */
		cmd_size = माप(*cmd) + cmd->in_length + माप(u32);

		rc = nd_desc->ndctl(nd_desc, to_nvdimm(ndd->dev),
				ND_CMD_SET_CONFIG_DATA, cmd, cmd_size, &cmd_rc);
		अगर (rc < 0)
			अवरोध;
		अगर (cmd_rc < 0) अणु
			rc = cmd_rc;
			अवरोध;
		पूर्ण
	पूर्ण
	kvमुक्त(cmd);

	वापस rc;
पूर्ण

व्योम nvdimm_set_labeling(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	set_bit(NDD_LABELING, &nvdimm->flags);
पूर्ण

व्योम nvdimm_set_locked(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	set_bit(NDD_LOCKED, &nvdimm->flags);
पूर्ण

व्योम nvdimm_clear_locked(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	clear_bit(NDD_LOCKED, &nvdimm->flags);
पूर्ण

अटल व्योम nvdimm_release(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	ida_simple_हटाओ(&dimm_ida, nvdimm->id);
	kमुक्त(nvdimm);
पूर्ण

काष्ठा nvdimm *to_nvdimm(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = container_of(dev, काष्ठा nvdimm, dev);

	WARN_ON(!is_nvdimm(dev));
	वापस nvdimm;
पूर्ण
EXPORT_SYMBOL_GPL(to_nvdimm);

काष्ठा nvdimm *nd_blk_region_to_dimm(काष्ठा nd_blk_region *ndbr)
अणु
	काष्ठा nd_region *nd_region = &ndbr->nd_region;
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];

	वापस nd_mapping->nvdimm;
पूर्ण
EXPORT_SYMBOL_GPL(nd_blk_region_to_dimm);

अचिन्हित दीर्घ nd_blk_memremap_flags(काष्ठा nd_blk_region *ndbr)
अणु
	/* pmem mapping properties are निजी to libnvdimm */
	वापस ARCH_MEMREMAP_PMEM;
पूर्ण
EXPORT_SYMBOL_GPL(nd_blk_memremap_flags);

काष्ठा nvdimm_drvdata *to_ndd(काष्ठा nd_mapping *nd_mapping)
अणु
	काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

	WARN_ON_ONCE(!is_nvdimm_bus_locked(&nvdimm->dev));

	वापस dev_get_drvdata(&nvdimm->dev);
पूर्ण
EXPORT_SYMBOL(to_ndd);

व्योम nvdimm_drvdata_release(काष्ठा kref *kref)
अणु
	काष्ठा nvdimm_drvdata *ndd = container_of(kref, typeof(*ndd), kref);
	काष्ठा device *dev = ndd->dev;
	काष्ठा resource *res, *_r;

	dev_dbg(dev, "trace\n");
	nvdimm_bus_lock(dev);
	क्रम_each_dpa_resource_safe(ndd, res, _r)
		nvdimm_मुक्त_dpa(ndd, res);
	nvdimm_bus_unlock(dev);

	kvमुक्त(ndd->data);
	kमुक्त(ndd);
	put_device(dev);
पूर्ण

व्योम get_ndd(काष्ठा nvdimm_drvdata *ndd)
अणु
	kref_get(&ndd->kref);
पूर्ण

व्योम put_ndd(काष्ठा nvdimm_drvdata *ndd)
अणु
	अगर (ndd)
		kref_put(&ndd->kref, nvdimm_drvdata_release);
पूर्ण

स्थिर अक्षर *nvdimm_name(काष्ठा nvdimm *nvdimm)
अणु
	वापस dev_name(&nvdimm->dev);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_name);

काष्ठा kobject *nvdimm_kobj(काष्ठा nvdimm *nvdimm)
अणु
	वापस &nvdimm->dev.kobj;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_kobj);

अचिन्हित दीर्घ nvdimm_cmd_mask(काष्ठा nvdimm *nvdimm)
अणु
	वापस nvdimm->cmd_mask;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_cmd_mask);

व्योम *nvdimm_provider_data(काष्ठा nvdimm *nvdimm)
अणु
	अगर (nvdimm)
		वापस nvdimm->provider_data;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_provider_data);

अटल sमाप_प्रकार commands_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	पूर्णांक cmd, len = 0;

	अगर (!nvdimm->cmd_mask)
		वापस प्र_लिखो(buf, "\n");

	क्रम_each_set_bit(cmd, &nvdimm->cmd_mask, BITS_PER_LONG)
		len += प्र_लिखो(buf + len, "%s ", nvdimm_cmd_name(cmd));
	len += प्र_लिखो(buf + len, "\n");
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(commands);

अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	वापस प्र_लिखो(buf, "%s%s%s\n",
			test_bit(NDD_ALIASING, &nvdimm->flags) ? "alias " : "",
			test_bit(NDD_LABELING, &nvdimm->flags) ? "label " : "",
			test_bit(NDD_LOCKED, &nvdimm->flags) ? "lock " : "");
पूर्ण
अटल DEVICE_ATTR_RO(flags);

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	/*
	 * The state may be in the process of changing, userspace should
	 * quiesce probing अगर it wants a अटल answer
	 */
	nvdimm_bus_lock(dev);
	nvdimm_bus_unlock(dev);
	वापस प्र_लिखो(buf, "%s\n", atomic_पढ़ो(&nvdimm->busy)
			? "active" : "idle");
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल sमाप_प्रकार __available_slots_show(काष्ठा nvdimm_drvdata *ndd, अक्षर *buf)
अणु
	काष्ठा device *dev;
	sमाप_प्रकार rc;
	u32 nमुक्त;

	अगर (!ndd)
		वापस -ENXIO;

	dev = ndd->dev;
	nvdimm_bus_lock(dev);
	nमुक्त = nd_label_nमुक्त(ndd);
	अगर (nमुक्त - 1 > nमुक्त) अणु
		dev_WARN_ONCE(dev, 1, "we ate our last label?\n");
		nमुक्त = 0;
	पूर्ण अन्यथा
		nमुक्त--;
	rc = प्र_लिखो(buf, "%d\n", nमुक्त);
	nvdimm_bus_unlock(dev);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार available_slots_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	rc = __available_slots_show(dev_get_drvdata(dev), buf);
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(available_slots);

__weak sमाप_प्रकार security_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	अगर (test_bit(NVDIMM_SECURITY_OVERWRITE, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "overwrite\n");
	अगर (test_bit(NVDIMM_SECURITY_DISABLED, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "disabled\n");
	अगर (test_bit(NVDIMM_SECURITY_UNLOCKED, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "unlocked\n");
	अगर (test_bit(NVDIMM_SECURITY_LOCKED, &nvdimm->sec.flags))
		वापस प्र_लिखो(buf, "locked\n");
	वापस -ENOTTY;
पूर्ण

अटल sमाप_प्रकार frozen_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	वापस प्र_लिखो(buf, "%d\n", test_bit(NVDIMM_SECURITY_FROZEN,
				&nvdimm->sec.flags));
पूर्ण
अटल DEVICE_ATTR_RO(frozen);

अटल sमाप_प्रकार security_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)

अणु
	sमाप_प्रकार rc;

	/*
	 * Require all userspace triggered security management to be
	 * करोne जबतक probing is idle and the DIMM is not in active use
	 * in any region.
	 */
	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	rc = nvdimm_security_store(dev, buf, len);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(security);

अटल काष्ठा attribute *nvdimm_attributes[] = अणु
	&dev_attr_state.attr,
	&dev_attr_flags.attr,
	&dev_attr_commands.attr,
	&dev_attr_available_slots.attr,
	&dev_attr_security.attr,
	&dev_attr_frozen.attr,
	शून्य,
पूर्ण;

अटल umode_t nvdimm_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	अगर (a != &dev_attr_security.attr && a != &dev_attr_frozen.attr)
		वापस a->mode;
	अगर (!nvdimm->sec.flags)
		वापस 0;

	अगर (a == &dev_attr_security.attr) अणु
		/* Are there any state mutation ops (make writable)? */
		अगर (nvdimm->sec.ops->मुक्तze || nvdimm->sec.ops->disable
				|| nvdimm->sec.ops->change_key
				|| nvdimm->sec.ops->erase
				|| nvdimm->sec.ops->overग_लिखो)
			वापस a->mode;
		वापस 0444;
	पूर्ण

	अगर (nvdimm->sec.ops->मुक्तze)
		वापस a->mode;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group nvdimm_attribute_group = अणु
	.attrs = nvdimm_attributes,
	.is_visible = nvdimm_visible,
पूर्ण;

अटल sमाप_प्रकार result_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	क्रमागत nvdimm_fwa_result result;

	अगर (!nvdimm->fw_ops)
		वापस -EOPNOTSUPP;

	nvdimm_bus_lock(dev);
	result = nvdimm->fw_ops->activate_result(nvdimm);
	nvdimm_bus_unlock(dev);

	चयन (result) अणु
	हाल NVDIMM_FWA_RESULT_NONE:
		वापस प्र_लिखो(buf, "none\n");
	हाल NVDIMM_FWA_RESULT_SUCCESS:
		वापस प्र_लिखो(buf, "success\n");
	हाल NVDIMM_FWA_RESULT_FAIL:
		वापस प्र_लिखो(buf, "fail\n");
	हाल NVDIMM_FWA_RESULT_NOTSTAGED:
		वापस प्र_लिखो(buf, "not_staged\n");
	हाल NVDIMM_FWA_RESULT_NEEDRESET:
		वापस प्र_लिखो(buf, "need_reset\n");
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(result);

अटल sमाप_प्रकार activate_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	क्रमागत nvdimm_fwa_state state;

	अगर (!nvdimm->fw_ops)
		वापस -EOPNOTSUPP;

	nvdimm_bus_lock(dev);
	state = nvdimm->fw_ops->activate_state(nvdimm);
	nvdimm_bus_unlock(dev);

	चयन (state) अणु
	हाल NVDIMM_FWA_IDLE:
		वापस प्र_लिखो(buf, "idle\n");
	हाल NVDIMM_FWA_BUSY:
		वापस प्र_लिखो(buf, "busy\n");
	हाल NVDIMM_FWA_ARMED:
		वापस प्र_लिखो(buf, "armed\n");
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार activate_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	क्रमागत nvdimm_fwa_trigger arg;
	पूर्णांक rc;

	अगर (!nvdimm->fw_ops)
		वापस -EOPNOTSUPP;

	अगर (sysfs_streq(buf, "arm"))
		arg = NVDIMM_FWA_ARM;
	अन्यथा अगर (sysfs_streq(buf, "disarm"))
		arg = NVDIMM_FWA_DISARM;
	अन्यथा
		वापस -EINVAL;

	nvdimm_bus_lock(dev);
	rc = nvdimm->fw_ops->arm(nvdimm, arg);
	nvdimm_bus_unlock(dev);

	अगर (rc < 0)
		वापस rc;
	वापस len;
पूर्ण
अटल DEVICE_ATTR_ADMIN_RW(activate);

अटल काष्ठा attribute *nvdimm_firmware_attributes[] = अणु
	&dev_attr_activate.attr,
	&dev_attr_result.attr,
	शून्य,
पूर्ण;

अटल umode_t nvdimm_firmware_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	क्रमागत nvdimm_fwa_capability cap;

	अगर (!nd_desc->fw_ops)
		वापस 0;
	अगर (!nvdimm->fw_ops)
		वापस 0;

	nvdimm_bus_lock(dev);
	cap = nd_desc->fw_ops->capability(nd_desc);
	nvdimm_bus_unlock(dev);

	अगर (cap < NVDIMM_FWA_CAP_QUIESCE)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group nvdimm_firmware_attribute_group = अणु
	.name = "firmware",
	.attrs = nvdimm_firmware_attributes,
	.is_visible = nvdimm_firmware_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nvdimm_attribute_groups[] = अणु
	&nd_device_attribute_group,
	&nvdimm_attribute_group,
	&nvdimm_firmware_attribute_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा device_type nvdimm_device_type = अणु
	.name = "nvdimm",
	.release = nvdimm_release,
	.groups = nvdimm_attribute_groups,
पूर्ण;

bool is_nvdimm(काष्ठा device *dev)
अणु
	वापस dev->type == &nvdimm_device_type;
पूर्ण

काष्ठा nvdimm *__nvdimm_create(काष्ठा nvdimm_bus *nvdimm_bus,
		व्योम *provider_data, स्थिर काष्ठा attribute_group **groups,
		अचिन्हित दीर्घ flags, अचिन्हित दीर्घ cmd_mask, पूर्णांक num_flush,
		काष्ठा resource *flush_wpq, स्थिर अक्षर *dimm_id,
		स्थिर काष्ठा nvdimm_security_ops *sec_ops,
		स्थिर काष्ठा nvdimm_fw_ops *fw_ops)
अणु
	काष्ठा nvdimm *nvdimm = kzalloc(माप(*nvdimm), GFP_KERNEL);
	काष्ठा device *dev;

	अगर (!nvdimm)
		वापस शून्य;

	nvdimm->id = ida_simple_get(&dimm_ida, 0, 0, GFP_KERNEL);
	अगर (nvdimm->id < 0) अणु
		kमुक्त(nvdimm);
		वापस शून्य;
	पूर्ण

	nvdimm->dimm_id = dimm_id;
	nvdimm->provider_data = provider_data;
	अगर (noblk)
		flags |= 1 << NDD_NOBLK;
	nvdimm->flags = flags;
	nvdimm->cmd_mask = cmd_mask;
	nvdimm->num_flush = num_flush;
	nvdimm->flush_wpq = flush_wpq;
	atomic_set(&nvdimm->busy, 0);
	dev = &nvdimm->dev;
	dev_set_name(dev, "nmem%d", nvdimm->id);
	dev->parent = &nvdimm_bus->dev;
	dev->type = &nvdimm_device_type;
	dev->devt = MKDEV(nvdimm_major, nvdimm->id);
	dev->groups = groups;
	nvdimm->sec.ops = sec_ops;
	nvdimm->fw_ops = fw_ops;
	nvdimm->sec.overग_लिखो_पंचांगo = 0;
	INIT_DELAYED_WORK(&nvdimm->dwork, nvdimm_security_overग_लिखो_query);
	/*
	 * Security state must be initialized beक्रमe device_add() क्रम
	 * attribute visibility.
	 */
	/* get security state and extended (master) state */
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	nvdimm->sec.ext_flags = nvdimm_security_flags(nvdimm, NVDIMM_MASTER);
	nd_device_रेजिस्टर(dev);

	वापस nvdimm;
पूर्ण
EXPORT_SYMBOL_GPL(__nvdimm_create);

अटल व्योम shutकरोwn_security_notअगरy(व्योम *data)
अणु
	काष्ठा nvdimm *nvdimm = data;

	sysfs_put(nvdimm->sec.overग_लिखो_state);
पूर्ण

पूर्णांक nvdimm_security_setup_events(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	अगर (!nvdimm->sec.flags || !nvdimm->sec.ops
			|| !nvdimm->sec.ops->overग_लिखो)
		वापस 0;
	nvdimm->sec.overग_लिखो_state = sysfs_get_dirent(dev->kobj.sd, "security");
	अगर (!nvdimm->sec.overग_लिखो_state)
		वापस -ENOMEM;

	वापस devm_add_action_or_reset(dev, shutकरोwn_security_notअगरy, nvdimm);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_security_setup_events);

पूर्णांक nvdimm_in_overग_लिखो(काष्ठा nvdimm *nvdimm)
अणु
	वापस test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_in_overग_लिखो);

पूर्णांक nvdimm_security_मुक्तze(काष्ठा nvdimm *nvdimm)
अणु
	पूर्णांक rc;

	WARN_ON_ONCE(!is_nvdimm_bus_locked(&nvdimm->dev));

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->मुक्तze)
		वापस -EOPNOTSUPP;

	अगर (!nvdimm->sec.flags)
		वापस -EIO;

	अगर (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) अणु
		dev_warn(&nvdimm->dev, "Overwrite operation in progress.\n");
		वापस -EBUSY;
	पूर्ण

	rc = nvdimm->sec.ops->मुक्तze(nvdimm);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);

	वापस rc;
पूर्ण

अटल अचिन्हित दीर्घ dpa_align(काष्ठा nd_region *nd_region)
अणु
	काष्ठा device *dev = &nd_region->dev;

	अगर (dev_WARN_ONCE(dev, !is_nvdimm_bus_locked(dev),
				"bus lock required for capacity provision\n"))
		वापस 0;
	अगर (dev_WARN_ONCE(dev, !nd_region->ndr_mappings || nd_region->align
				% nd_region->ndr_mappings,
				"invalid region align %#lx mappings: %d\n",
				nd_region->align, nd_region->ndr_mappings))
		वापस 0;
	वापस nd_region->align / nd_region->ndr_mappings;
पूर्ण

पूर्णांक alias_dpa_busy(काष्ठा device *dev, व्योम *data)
अणु
	resource_माप_प्रकार map_end, blk_start, new;
	काष्ठा blk_alloc_info *info = data;
	काष्ठा nd_mapping *nd_mapping;
	काष्ठा nd_region *nd_region;
	काष्ठा nvdimm_drvdata *ndd;
	काष्ठा resource *res;
	अचिन्हित दीर्घ align;
	पूर्णांक i;

	अगर (!is_memory(dev))
		वापस 0;

	nd_region = to_nd_region(dev);
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		nd_mapping  = &nd_region->mapping[i];
		अगर (nd_mapping->nvdimm == info->nd_mapping->nvdimm)
			अवरोध;
	पूर्ण

	अगर (i >= nd_region->ndr_mappings)
		वापस 0;

	ndd = to_ndd(nd_mapping);
	map_end = nd_mapping->start + nd_mapping->size - 1;
	blk_start = nd_mapping->start;

	/*
	 * In the allocation हाल ->res is set to मुक्त space that we are
	 * looking to validate against PMEM aliasing collision rules
	 * (i.e. BLK is allocated after all aliased PMEM).
	 */
	अगर (info->res) अणु
		अगर (info->res->start >= nd_mapping->start
				&& info->res->start < map_end)
			/* pass */;
		अन्यथा
			वापस 0;
	पूर्ण

 retry:
	/*
	 * Find the मुक्त dpa from the end of the last pmem allocation to
	 * the end of the पूर्णांकerleave-set mapping.
	 */
	align = dpa_align(nd_region);
	अगर (!align)
		वापस 0;

	क्रम_each_dpa_resource(ndd, res) अणु
		resource_माप_प्रकार start, end;

		अगर (म_भेदन(res->name, "pmem", 4) != 0)
			जारी;

		start = ALIGN_DOWN(res->start, align);
		end = ALIGN(res->end + 1, align) - 1;
		अगर ((start >= blk_start && start < map_end)
				|| (end >= blk_start && end <= map_end)) अणु
			new = max(blk_start, min(map_end, end) + 1);
			अगर (new != blk_start) अणु
				blk_start = new;
				जाओ retry;
			पूर्ण
		पूर्ण
	पूर्ण

	/* update the मुक्त space range with the probed blk_start */
	अगर (info->res && blk_start > info->res->start) अणु
		info->res->start = max(info->res->start, blk_start);
		अगर (info->res->start > info->res->end)
			info->res->end = info->res->start - 1;
		वापस 1;
	पूर्ण

	info->available -= blk_start - nd_mapping->start;

	वापस 0;
पूर्ण

/**
 * nd_blk_available_dpa - account the unused dpa of BLK region
 * @nd_mapping: container of dpa-resource-root + labels
 *
 * Unlike PMEM, BLK namespaces can occupy discontiguous DPA ranges, but
 * we arrange क्रम them to never start at an lower dpa than the last
 * PMEM allocation in an aliased region.
 */
resource_माप_प्रकार nd_blk_available_dpa(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा blk_alloc_info info = अणु
		.nd_mapping = nd_mapping,
		.available = nd_mapping->size,
		.res = शून्य,
	पूर्ण;
	काष्ठा resource *res;
	अचिन्हित दीर्घ align;

	अगर (!ndd)
		वापस 0;

	device_क्रम_each_child(&nvdimm_bus->dev, &info, alias_dpa_busy);

	/* now account क्रम busy blk allocations in unaliased dpa */
	align = dpa_align(nd_region);
	अगर (!align)
		वापस 0;
	क्रम_each_dpa_resource(ndd, res) अणु
		resource_माप_प्रकार start, end, size;

		अगर (म_भेदन(res->name, "blk", 3) != 0)
			जारी;
		start = ALIGN_DOWN(res->start, align);
		end = ALIGN(res->end + 1, align) - 1;
		size = end - start + 1;
		अगर (size >= info.available)
			वापस 0;
		info.available -= size;
	पूर्ण

	वापस info.available;
पूर्ण

/**
 * nd_pmem_max_contiguous_dpa - For the given dimm+region, वापस the max
 *			   contiguous unallocated dpa range.
 * @nd_region: स्थिरrain available space check to this reference region
 * @nd_mapping: container of dpa-resource-root + labels
 */
resource_माप_प्रकार nd_pmem_max_contiguous_dpa(काष्ठा nd_region *nd_region,
					   काष्ठा nd_mapping *nd_mapping)
अणु
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nvdimm_bus *nvdimm_bus;
	resource_माप_प्रकार max = 0;
	काष्ठा resource *res;
	अचिन्हित दीर्घ align;

	/* अगर a dimm is disabled the available capacity is zero */
	अगर (!ndd)
		वापस 0;

	align = dpa_align(nd_region);
	अगर (!align)
		वापस 0;

	nvdimm_bus = walk_to_nvdimm_bus(ndd->dev);
	अगर (__reserve_मुक्त_pmem(&nd_region->dev, nd_mapping->nvdimm))
		वापस 0;
	क्रम_each_dpa_resource(ndd, res) अणु
		resource_माप_प्रकार start, end;

		अगर (म_भेद(res->name, "pmem-reserve") != 0)
			जारी;
		/* trim मुक्त space relative to current alignment setting */
		start = ALIGN(res->start, align);
		end = ALIGN_DOWN(res->end + 1, align) - 1;
		अगर (end < start)
			जारी;
		अगर (end - start + 1 > max)
			max = end - start + 1;
	पूर्ण
	release_मुक्त_pmem(nvdimm_bus, nd_mapping);
	वापस max;
पूर्ण

/**
 * nd_pmem_available_dpa - क्रम the given dimm+region account unallocated dpa
 * @nd_mapping: container of dpa-resource-root + labels
 * @nd_region: स्थिरrain available space check to this reference region
 * @overlap: calculate available space assuming this level of overlap
 *
 * Validate that a PMEM label, अगर present, aligns with the start of an
 * पूर्णांकerleave set and truncate the available size at the lowest BLK
 * overlap poपूर्णांक.
 *
 * The expectation is that this routine is called multiple बार as it
 * probes क्रम the largest BLK encroachment क्रम any single member DIMM of
 * the पूर्णांकerleave set.  Once that value is determined the PMEM-limit क्रम
 * the set can be established.
 */
resource_माप_प्रकार nd_pmem_available_dpa(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, resource_माप_प्रकार *overlap)
अणु
	resource_माप_प्रकार map_start, map_end, busy = 0, available, blk_start;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा resource *res;
	स्थिर अक्षर *reason;
	अचिन्हित दीर्घ align;

	अगर (!ndd)
		वापस 0;

	align = dpa_align(nd_region);
	अगर (!align)
		वापस 0;

	map_start = nd_mapping->start;
	map_end = map_start + nd_mapping->size - 1;
	blk_start = max(map_start, map_end + 1 - *overlap);
	क्रम_each_dpa_resource(ndd, res) अणु
		resource_माप_प्रकार start, end;

		start = ALIGN_DOWN(res->start, align);
		end = ALIGN(res->end + 1, align) - 1;
		अगर (start >= map_start && start < map_end) अणु
			अगर (म_भेदन(res->name, "blk", 3) == 0)
				blk_start = min(blk_start,
						max(map_start, start));
			अन्यथा अगर (end > map_end) अणु
				reason = "misaligned to iset";
				जाओ err;
			पूर्ण अन्यथा
				busy += end - start + 1;
		पूर्ण अन्यथा अगर (end >= map_start && end <= map_end) अणु
			अगर (म_भेदन(res->name, "blk", 3) == 0) अणु
				/*
				 * If a BLK allocation overlaps the start of
				 * PMEM the entire पूर्णांकerleave set may now only
				 * be used क्रम BLK.
				 */
				blk_start = map_start;
			पूर्ण अन्यथा
				busy += end - start + 1;
		पूर्ण अन्यथा अगर (map_start > start && map_start < end) अणु
			/* total eclipse of the mapping */
			busy += nd_mapping->size;
			blk_start = map_start;
		पूर्ण
	पूर्ण

	*overlap = map_end + 1 - blk_start;
	available = blk_start - map_start;
	अगर (busy < available)
		वापस ALIGN_DOWN(available - busy, align);
	वापस 0;

 err:
	nd_dbg_dpa(nd_region, ndd, res, "%s\n", reason);
	वापस 0;
पूर्ण

व्योम nvdimm_मुक्त_dpa(काष्ठा nvdimm_drvdata *ndd, काष्ठा resource *res)
अणु
	WARN_ON_ONCE(!is_nvdimm_bus_locked(ndd->dev));
	kमुक्त(res->name);
	__release_region(&ndd->dpa, res->start, resource_size(res));
पूर्ण

काष्ठा resource *nvdimm_allocate_dpa(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_label_id *label_id, resource_माप_प्रकार start,
		resource_माप_प्रकार n)
अणु
	अक्षर *name = kmemdup(label_id, माप(*label_id), GFP_KERNEL);
	काष्ठा resource *res;

	अगर (!name)
		वापस शून्य;

	WARN_ON_ONCE(!is_nvdimm_bus_locked(ndd->dev));
	res = __request_region(&ndd->dpa, start, n, name, 0);
	अगर (!res)
		kमुक्त(name);
	वापस res;
पूर्ण

/**
 * nvdimm_allocated_dpa - sum up the dpa currently allocated to this label_id
 * @nvdimm: container of dpa-resource-root + labels
 * @label_id: dpa resource name of the क्रमm अणुpmem|blkपूर्ण-<human पढ़ोable uuid>
 */
resource_माप_प्रकार nvdimm_allocated_dpa(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_label_id *label_id)
अणु
	resource_माप_प्रकार allocated = 0;
	काष्ठा resource *res;

	क्रम_each_dpa_resource(ndd, res)
		अगर (म_भेद(res->name, label_id->id) == 0)
			allocated += resource_size(res);

	वापस allocated;
पूर्ण

अटल पूर्णांक count_dimms(काष्ठा device *dev, व्योम *c)
अणु
	पूर्णांक *count = c;

	अगर (is_nvdimm(dev))
		(*count)++;
	वापस 0;
पूर्ण

पूर्णांक nvdimm_bus_check_dimm_count(काष्ठा nvdimm_bus *nvdimm_bus, पूर्णांक dimm_count)
अणु
	पूर्णांक count = 0;
	/* Flush any possible dimm registration failures */
	nd_synchronize();

	device_क्रम_each_child(&nvdimm_bus->dev, &count, count_dimms);
	dev_dbg(&nvdimm_bus->dev, "count: %d\n", count);
	अगर (count != dimm_count)
		वापस -ENXIO;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_bus_check_dimm_count);

व्योम __निकास nvdimm_devs_निकास(व्योम)
अणु
	ida_destroy(&dimm_ida);
पूर्ण
