<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/list_sort.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/module.h>
#समावेश <linux/nospec.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/acpi.h>
#समावेश <linux/sort.h>
#समावेश <linux/पन.स>
#समावेश <linux/nd.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <acpi/nfit.h>
#समावेश "intel.h"
#समावेश "nfit.h"

/*
 * For पढ़ोq() and ग_लिखोq() on 32-bit builds, the hi-lo, lo-hi order is
 * irrelevant.
 */
#समावेश <linux/io-64-nonatomic-hi-lo.h>

अटल bool क्रमce_enable_dimms;
module_param(क्रमce_enable_dimms, bool, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(क्रमce_enable_dimms, "Ignore _STA (ACPI DIMM device) status");

अटल bool disable_venकरोr_specअगरic;
module_param(disable_venकरोr_specअगरic, bool, S_IRUGO);
MODULE_PARM_DESC(disable_venकरोr_specअगरic,
		"Limit commands to the publicly specified set");

अटल अचिन्हित दीर्घ override_dsm_mask;
module_param(override_dsm_mask, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(override_dsm_mask, "Bitmask of allowed NVDIMM DSM functions");

अटल पूर्णांक शेष_dsm_family = -1;
module_param(शेष_dsm_family, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(शेष_dsm_family,
		"Try this DSM type first when identifying NVDIMM family");

अटल bool no_init_ars;
module_param(no_init_ars, bool, 0644);
MODULE_PARM_DESC(no_init_ars, "Skip ARS run at nfit init time");

अटल bool क्रमce_labels;
module_param(क्रमce_labels, bool, 0444);
MODULE_PARM_DESC(क्रमce_labels, "Opt-in to labels despite missing methods");

LIST_HEAD(acpi_descs);
DEFINE_MUTEX(acpi_desc_lock);

अटल काष्ठा workqueue_काष्ठा *nfit_wq;

काष्ठा nfit_table_prev अणु
	काष्ठा list_head spas;
	काष्ठा list_head memdevs;
	काष्ठा list_head dcrs;
	काष्ठा list_head bdws;
	काष्ठा list_head idts;
	काष्ठा list_head flushes;
पूर्ण;

अटल guid_t nfit_uuid[NFIT_UUID_MAX];

स्थिर guid_t *to_nfit_uuid(क्रमागत nfit_uuids id)
अणु
	वापस &nfit_uuid[id];
पूर्ण
EXPORT_SYMBOL(to_nfit_uuid);

अटल स्थिर guid_t *to_nfit_bus_uuid(पूर्णांक family)
अणु
	अगर (WARN_ONCE(family == NVDIMM_BUS_FAMILY_NFIT,
			"only secondary bus families can be translated\n"))
		वापस शून्य;
	/*
	 * The index of bus UUIDs starts immediately following the last
	 * NVDIMM/leaf family.
	 */
	वापस to_nfit_uuid(family + NVDIMM_FAMILY_MAX);
पूर्ण

अटल काष्ठा acpi_device *to_acpi_dev(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;

	/*
	 * If provider == 'ACPI.NFIT' we can assume 'dev' is a काष्ठा
	 * acpi_device.
	 */
	अगर (!nd_desc->provider_name
			|| म_भेद(nd_desc->provider_name, "ACPI.NFIT") != 0)
		वापस शून्य;

	वापस to_acpi_device(acpi_desc->dev);
पूर्ण

अटल पूर्णांक xlat_bus_status(व्योम *buf, अचिन्हित पूर्णांक cmd, u32 status)
अणु
	काष्ठा nd_cmd_clear_error *clear_err;
	काष्ठा nd_cmd_ars_status *ars_status;
	u16 flags;

	चयन (cmd) अणु
	हाल ND_CMD_ARS_CAP:
		अगर ((status & 0xffff) == NFIT_ARS_CAP_NONE)
			वापस -ENOTTY;

		/* Command failed */
		अगर (status & 0xffff)
			वापस -EIO;

		/* No supported scan types क्रम this range */
		flags = ND_ARS_PERSISTENT | ND_ARS_VOLATILE;
		अगर ((status >> 16 & flags) == 0)
			वापस -ENOTTY;
		वापस 0;
	हाल ND_CMD_ARS_START:
		/* ARS is in progress */
		अगर ((status & 0xffff) == NFIT_ARS_START_BUSY)
			वापस -EBUSY;

		/* Command failed */
		अगर (status & 0xffff)
			वापस -EIO;
		वापस 0;
	हाल ND_CMD_ARS_STATUS:
		ars_status = buf;
		/* Command failed */
		अगर (status & 0xffff)
			वापस -EIO;
		/* Check extended status (Upper two bytes) */
		अगर (status == NFIT_ARS_STATUS_DONE)
			वापस 0;

		/* ARS is in progress */
		अगर (status == NFIT_ARS_STATUS_BUSY)
			वापस -EBUSY;

		/* No ARS perक्रमmed क्रम the current boot */
		अगर (status == NFIT_ARS_STATUS_NONE)
			वापस -EAGAIN;

		/*
		 * ARS पूर्णांकerrupted, either we overflowed or some other
		 * agent wants the scan to stop.  If we didn't overflow
		 * then just जारी with the वापसed results.
		 */
		अगर (status == NFIT_ARS_STATUS_INTR) अणु
			अगर (ars_status->out_length >= 40 && (ars_status->flags
						& NFIT_ARS_F_OVERFLOW))
				वापस -ENOSPC;
			वापस 0;
		पूर्ण

		/* Unknown status */
		अगर (status >> 16)
			वापस -EIO;
		वापस 0;
	हाल ND_CMD_CLEAR_ERROR:
		clear_err = buf;
		अगर (status & 0xffff)
			वापस -EIO;
		अगर (!clear_err->cleared)
			वापस -EIO;
		अगर (clear_err->length > clear_err->cleared)
			वापस clear_err->cleared;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	/* all other non-zero status results in an error */
	अगर (status)
		वापस -EIO;
	वापस 0;
पूर्ण

#घोषणा ACPI_LABELS_LOCKED 3

अटल पूर्णांक xlat_nvdimm_status(काष्ठा nvdimm *nvdimm, व्योम *buf, अचिन्हित पूर्णांक cmd,
		u32 status)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	चयन (cmd) अणु
	हाल ND_CMD_GET_CONFIG_SIZE:
		/*
		 * In the _LSI, _LSR, _LSW हाल the locked status is
		 * communicated via the पढ़ो/ग_लिखो commands
		 */
		अगर (test_bit(NFIT_MEM_LSR, &nfit_mem->flags))
			अवरोध;

		अगर (status >> 16 & ND_CONFIG_LOCKED)
			वापस -EACCES;
		अवरोध;
	हाल ND_CMD_GET_CONFIG_DATA:
		अगर (test_bit(NFIT_MEM_LSR, &nfit_mem->flags)
				&& status == ACPI_LABELS_LOCKED)
			वापस -EACCES;
		अवरोध;
	हाल ND_CMD_SET_CONFIG_DATA:
		अगर (test_bit(NFIT_MEM_LSW, &nfit_mem->flags)
				&& status == ACPI_LABELS_LOCKED)
			वापस -EACCES;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* all other non-zero status results in an error */
	अगर (status)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक xlat_status(काष्ठा nvdimm *nvdimm, व्योम *buf, अचिन्हित पूर्णांक cmd,
		u32 status)
अणु
	अगर (!nvdimm)
		वापस xlat_bus_status(buf, cmd, status);
	वापस xlat_nvdimm_status(nvdimm, buf, cmd, status);
पूर्ण

/* convert _LSअणुI,Rपूर्ण packages to the buffer object acpi_nfit_ctl expects */
अटल जोड़ acpi_object *pkg_to_buf(जोड़ acpi_object *pkg)
अणु
	पूर्णांक i;
	व्योम *dst;
	माप_प्रकार size = 0;
	जोड़ acpi_object *buf = शून्य;

	अगर (pkg->type != ACPI_TYPE_PACKAGE) अणु
		WARN_ONCE(1, "BIOS bug, unexpected element type: %d\n",
				pkg->type);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < pkg->package.count; i++) अणु
		जोड़ acpi_object *obj = &pkg->package.elements[i];

		अगर (obj->type == ACPI_TYPE_INTEGER)
			size += 4;
		अन्यथा अगर (obj->type == ACPI_TYPE_BUFFER)
			size += obj->buffer.length;
		अन्यथा अणु
			WARN_ONCE(1, "BIOS bug, unexpected element type: %d\n",
					obj->type);
			जाओ err;
		पूर्ण
	पूर्ण

	buf = ACPI_ALLOCATE(माप(*buf) + size);
	अगर (!buf)
		जाओ err;

	dst = buf + 1;
	buf->type = ACPI_TYPE_BUFFER;
	buf->buffer.length = size;
	buf->buffer.poपूर्णांकer = dst;
	क्रम (i = 0; i < pkg->package.count; i++) अणु
		जोड़ acpi_object *obj = &pkg->package.elements[i];

		अगर (obj->type == ACPI_TYPE_INTEGER) अणु
			स_नकल(dst, &obj->पूर्णांकeger.value, 4);
			dst += 4;
		पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_BUFFER) अणु
			स_नकल(dst, obj->buffer.poपूर्णांकer, obj->buffer.length);
			dst += obj->buffer.length;
		पूर्ण
	पूर्ण
err:
	ACPI_FREE(pkg);
	वापस buf;
पूर्ण

अटल जोड़ acpi_object *पूर्णांक_to_buf(जोड़ acpi_object *पूर्णांकeger)
अणु
	जोड़ acpi_object *buf = शून्य;
	व्योम *dst = शून्य;

	अगर (पूर्णांकeger->type != ACPI_TYPE_INTEGER) अणु
		WARN_ONCE(1, "BIOS bug, unexpected element type: %d\n",
				पूर्णांकeger->type);
		जाओ err;
	पूर्ण

	buf = ACPI_ALLOCATE(माप(*buf) + 4);
	अगर (!buf)
		जाओ err;

	dst = buf + 1;
	buf->type = ACPI_TYPE_BUFFER;
	buf->buffer.length = 4;
	buf->buffer.poपूर्णांकer = dst;
	स_नकल(dst, &पूर्णांकeger->पूर्णांकeger.value, 4);
err:
	ACPI_FREE(पूर्णांकeger);
	वापस buf;
पूर्ण

अटल जोड़ acpi_object *acpi_label_ग_लिखो(acpi_handle handle, u32 offset,
		u32 len, व्योम *data)
अणु
	acpi_status rc;
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_object_list input = अणु
		.count = 3,
		.poपूर्णांकer = (जोड़ acpi_object []) अणु
			[0] = अणु
				.पूर्णांकeger.type = ACPI_TYPE_INTEGER,
				.पूर्णांकeger.value = offset,
			पूर्ण,
			[1] = अणु
				.पूर्णांकeger.type = ACPI_TYPE_INTEGER,
				.पूर्णांकeger.value = len,
			पूर्ण,
			[2] = अणु
				.buffer.type = ACPI_TYPE_BUFFER,
				.buffer.poपूर्णांकer = data,
				.buffer.length = len,
			पूर्ण,
		पूर्ण,
	पूर्ण;

	rc = acpi_evaluate_object(handle, "_LSW", &input, &buf);
	अगर (ACPI_FAILURE(rc))
		वापस शून्य;
	वापस पूर्णांक_to_buf(buf.poपूर्णांकer);
पूर्ण

अटल जोड़ acpi_object *acpi_label_पढ़ो(acpi_handle handle, u32 offset,
		u32 len)
अणु
	acpi_status rc;
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_object_list input = अणु
		.count = 2,
		.poपूर्णांकer = (जोड़ acpi_object []) अणु
			[0] = अणु
				.पूर्णांकeger.type = ACPI_TYPE_INTEGER,
				.पूर्णांकeger.value = offset,
			पूर्ण,
			[1] = अणु
				.पूर्णांकeger.type = ACPI_TYPE_INTEGER,
				.पूर्णांकeger.value = len,
			पूर्ण,
		पूर्ण,
	पूर्ण;

	rc = acpi_evaluate_object(handle, "_LSR", &input, &buf);
	अगर (ACPI_FAILURE(rc))
		वापस शून्य;
	वापस pkg_to_buf(buf.poपूर्णांकer);
पूर्ण

अटल जोड़ acpi_object *acpi_label_info(acpi_handle handle)
अणु
	acpi_status rc;
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	rc = acpi_evaluate_object(handle, "_LSI", शून्य, &buf);
	अगर (ACPI_FAILURE(rc))
		वापस शून्य;
	वापस pkg_to_buf(buf.poपूर्णांकer);
पूर्ण

अटल u8 nfit_dsm_revid(अचिन्हित family, अचिन्हित func)
अणु
	अटल स्थिर u8 revid_table[NVDIMM_FAMILY_MAX+1][NVDIMM_CMD_MAX+1] = अणु
		[NVDIMM_FAMILY_INTEL] = अणु
			[NVDIMM_INTEL_GET_MODES ...
				NVDIMM_INTEL_FW_ACTIVATE_ARM] = 2,
		पूर्ण,
	पूर्ण;
	u8 id;

	अगर (family > NVDIMM_FAMILY_MAX)
		वापस 0;
	अगर (func > NVDIMM_CMD_MAX)
		वापस 0;
	id = revid_table[family][func];
	अगर (id == 0)
		वापस 1; /* शेष */
	वापस id;
पूर्ण

अटल bool payload_dumpable(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक func)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	अगर (nfit_mem && nfit_mem->family == NVDIMM_FAMILY_INTEL
			&& func >= NVDIMM_INTEL_GET_SECURITY_STATE
			&& func <= NVDIMM_INTEL_MASTER_SECURE_ERASE)
		वापस IS_ENABLED(CONFIG_NFIT_SECURITY_DEBUG);
	वापस true;
पूर्ण

अटल पूर्णांक cmd_to_func(काष्ठा nfit_mem *nfit_mem, अचिन्हित पूर्णांक cmd,
		काष्ठा nd_cmd_pkg *call_pkg, पूर्णांक *family)
अणु
	अगर (call_pkg) अणु
		पूर्णांक i;

		अगर (nfit_mem && nfit_mem->family != call_pkg->nd_family)
			वापस -ENOTTY;

		क्रम (i = 0; i < ARRAY_SIZE(call_pkg->nd_reserved2); i++)
			अगर (call_pkg->nd_reserved2[i])
				वापस -EINVAL;
		*family = call_pkg->nd_family;
		वापस call_pkg->nd_command;
	पूर्ण

	/* In the !call_pkg हाल, bus commands == bus functions */
	अगर (!nfit_mem)
		वापस cmd;

	/* Linux ND commands == NVDIMM_FAMILY_INTEL function numbers */
	अगर (nfit_mem->family == NVDIMM_FAMILY_INTEL)
		वापस cmd;

	/*
	 * Force function number validation to fail since 0 is never
	 * published as a valid function in dsm_mask.
	 */
	वापस 0;
पूर्ण

पूर्णांक acpi_nfit_ctl(काष्ठा nvdimm_bus_descriptor *nd_desc, काष्ठा nvdimm *nvdimm,
		अचिन्हित पूर्णांक cmd, व्योम *buf, अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	जोड़ acpi_object in_obj, in_buf, *out_obj;
	स्थिर काष्ठा nd_cmd_desc *desc = शून्य;
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nd_cmd_pkg *call_pkg = शून्य;
	स्थिर अक्षर *cmd_name, *dimm_name;
	अचिन्हित दीर्घ cmd_mask, dsm_mask;
	u32 offset, fw_status = 0;
	acpi_handle handle;
	स्थिर guid_t *guid;
	पूर्णांक func, rc, i;
	पूर्णांक family = 0;

	अगर (cmd_rc)
		*cmd_rc = -EINVAL;

	अगर (cmd == ND_CMD_CALL)
		call_pkg = buf;
	func = cmd_to_func(nfit_mem, cmd, call_pkg, &family);
	अगर (func < 0)
		वापस func;

	अगर (nvdimm) अणु
		काष्ठा acpi_device *adev = nfit_mem->adev;

		अगर (!adev)
			वापस -ENOTTY;

		dimm_name = nvdimm_name(nvdimm);
		cmd_name = nvdimm_cmd_name(cmd);
		cmd_mask = nvdimm_cmd_mask(nvdimm);
		dsm_mask = nfit_mem->dsm_mask;
		desc = nd_cmd_dimm_desc(cmd);
		guid = to_nfit_uuid(nfit_mem->family);
		handle = adev->handle;
	पूर्ण अन्यथा अणु
		काष्ठा acpi_device *adev = to_acpi_dev(acpi_desc);

		cmd_name = nvdimm_bus_cmd_name(cmd);
		cmd_mask = nd_desc->cmd_mask;
		अगर (cmd == ND_CMD_CALL && call_pkg->nd_family) अणु
			family = call_pkg->nd_family;
			अगर (family > NVDIMM_BUS_FAMILY_MAX ||
			    !test_bit(family, &nd_desc->bus_family_mask))
				वापस -EINVAL;
			family = array_index_nospec(family,
						    NVDIMM_BUS_FAMILY_MAX + 1);
			dsm_mask = acpi_desc->family_dsm_mask[family];
			guid = to_nfit_bus_uuid(family);
		पूर्ण अन्यथा अणु
			dsm_mask = acpi_desc->bus_dsm_mask;
			guid = to_nfit_uuid(NFIT_DEV_BUS);
		पूर्ण
		desc = nd_cmd_bus_desc(cmd);
		handle = adev->handle;
		dimm_name = "bus";
	पूर्ण

	अगर (!desc || (cmd && (desc->out_num + desc->in_num == 0)))
		वापस -ENOTTY;

	/*
	 * Check क्रम a valid command.  For ND_CMD_CALL, we also have to
	 * make sure that the DSM function is supported.
	 */
	अगर (cmd == ND_CMD_CALL &&
	    (func > NVDIMM_CMD_MAX || !test_bit(func, &dsm_mask)))
		वापस -ENOTTY;
	अन्यथा अगर (!test_bit(cmd, &cmd_mask))
		वापस -ENOTTY;

	in_obj.type = ACPI_TYPE_PACKAGE;
	in_obj.package.count = 1;
	in_obj.package.elements = &in_buf;
	in_buf.type = ACPI_TYPE_BUFFER;
	in_buf.buffer.poपूर्णांकer = buf;
	in_buf.buffer.length = 0;

	/* libnvdimm has alपढ़ोy validated the input envelope */
	क्रम (i = 0; i < desc->in_num; i++)
		in_buf.buffer.length += nd_cmd_in_size(nvdimm, cmd, desc,
				i, buf);

	अगर (call_pkg) अणु
		/* skip over package wrapper */
		in_buf.buffer.poपूर्णांकer = (व्योम *) &call_pkg->nd_payload;
		in_buf.buffer.length = call_pkg->nd_size_in;
	पूर्ण

	dev_dbg(dev, "%s cmd: %d: family: %d func: %d input length: %d\n",
		dimm_name, cmd, family, func, in_buf.buffer.length);
	अगर (payload_dumpable(nvdimm, func))
		prपूर्णांक_hex_dump_debug("nvdimm in  ", DUMP_PREFIX_OFFSET, 4, 4,
				in_buf.buffer.poपूर्णांकer,
				min_t(u32, 256, in_buf.buffer.length), true);

	/* call the BIOS, prefer the named methods over _DSM अगर available */
	अगर (nvdimm && cmd == ND_CMD_GET_CONFIG_SIZE
			&& test_bit(NFIT_MEM_LSR, &nfit_mem->flags))
		out_obj = acpi_label_info(handle);
	अन्यथा अगर (nvdimm && cmd == ND_CMD_GET_CONFIG_DATA
			&& test_bit(NFIT_MEM_LSR, &nfit_mem->flags)) अणु
		काष्ठा nd_cmd_get_config_data_hdr *p = buf;

		out_obj = acpi_label_पढ़ो(handle, p->in_offset, p->in_length);
	पूर्ण अन्यथा अगर (nvdimm && cmd == ND_CMD_SET_CONFIG_DATA
			&& test_bit(NFIT_MEM_LSW, &nfit_mem->flags)) अणु
		काष्ठा nd_cmd_set_config_hdr *p = buf;

		out_obj = acpi_label_ग_लिखो(handle, p->in_offset, p->in_length,
				p->in_buf);
	पूर्ण अन्यथा अणु
		u8 revid;

		अगर (nvdimm)
			revid = nfit_dsm_revid(nfit_mem->family, func);
		अन्यथा
			revid = 1;
		out_obj = acpi_evaluate_dsm(handle, guid, revid, func, &in_obj);
	पूर्ण

	अगर (!out_obj) अणु
		dev_dbg(dev, "%s _DSM failed cmd: %s\n", dimm_name, cmd_name);
		वापस -EINVAL;
	पूर्ण

	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		dev_dbg(dev, "%s unexpected output object type cmd: %s type: %d\n",
				dimm_name, cmd_name, out_obj->type);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	dev_dbg(dev, "%s cmd: %s output length: %d\n", dimm_name,
			cmd_name, out_obj->buffer.length);
	prपूर्णांक_hex_dump_debug(cmd_name, DUMP_PREFIX_OFFSET, 4, 4,
			out_obj->buffer.poपूर्णांकer,
			min_t(u32, 128, out_obj->buffer.length), true);

	अगर (call_pkg) अणु
		call_pkg->nd_fw_size = out_obj->buffer.length;
		स_नकल(call_pkg->nd_payload + call_pkg->nd_size_in,
			out_obj->buffer.poपूर्णांकer,
			min(call_pkg->nd_fw_size, call_pkg->nd_size_out));

		ACPI_FREE(out_obj);
		/*
		 * Need to support FW function w/o known size in advance.
		 * Caller can determine required size based upon nd_fw_size.
		 * If we वापस an error (like अन्यथाwhere) then caller wouldn't
		 * be able to rely upon data वापसed to make calculation.
		 */
		अगर (cmd_rc)
			*cmd_rc = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0, offset = 0; i < desc->out_num; i++) अणु
		u32 out_size = nd_cmd_out_size(nvdimm, cmd, desc, i, buf,
				(u32 *) out_obj->buffer.poपूर्णांकer,
				out_obj->buffer.length - offset);

		अगर (offset + out_size > out_obj->buffer.length) अणु
			dev_dbg(dev, "%s output object underflow cmd: %s field: %d\n",
					dimm_name, cmd_name, i);
			अवरोध;
		पूर्ण

		अगर (in_buf.buffer.length + offset + out_size > buf_len) अणु
			dev_dbg(dev, "%s output overrun cmd: %s field: %d\n",
					dimm_name, cmd_name, i);
			rc = -ENXIO;
			जाओ out;
		पूर्ण
		स_नकल(buf + in_buf.buffer.length + offset,
				out_obj->buffer.poपूर्णांकer + offset, out_size);
		offset += out_size;
	पूर्ण

	/*
	 * Set fw_status क्रम all the commands with a known क्रमmat to be
	 * later पूर्णांकerpreted by xlat_status().
	 */
	अगर (i >= 1 && ((!nvdimm && cmd >= ND_CMD_ARS_CAP
					&& cmd <= ND_CMD_CLEAR_ERROR)
				|| (nvdimm && cmd >= ND_CMD_SMART
					&& cmd <= ND_CMD_VENDOR)))
		fw_status = *(u32 *) out_obj->buffer.poपूर्णांकer;

	अगर (offset + in_buf.buffer.length < buf_len) अणु
		अगर (i >= 1) अणु
			/*
			 * status valid, वापस the number of bytes left
			 * unfilled in the output buffer
			 */
			rc = buf_len - offset - in_buf.buffer.length;
			अगर (cmd_rc)
				*cmd_rc = xlat_status(nvdimm, buf, cmd,
						fw_status);
		पूर्ण अन्यथा अणु
			dev_err(dev, "%s:%s underrun cmd: %s buf_len: %d out_len: %d\n",
					__func__, dimm_name, cmd_name, buf_len,
					offset);
			rc = -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = 0;
		अगर (cmd_rc)
			*cmd_rc = xlat_status(nvdimm, buf, cmd, fw_status);
	पूर्ण

 out:
	ACPI_FREE(out_obj);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_nfit_ctl);

अटल स्थिर अक्षर *spa_type_name(u16 type)
अणु
	अटल स्थिर अक्षर *to_name[] = अणु
		[NFIT_SPA_VOLATILE] = "volatile",
		[NFIT_SPA_PM] = "pmem",
		[NFIT_SPA_DCR] = "dimm-control-region",
		[NFIT_SPA_BDW] = "block-data-window",
		[NFIT_SPA_VDISK] = "volatile-disk",
		[NFIT_SPA_VCD] = "volatile-cd",
		[NFIT_SPA_PDISK] = "persistent-disk",
		[NFIT_SPA_PCD] = "persistent-cd",

	पूर्ण;

	अगर (type > NFIT_SPA_PCD)
		वापस "unknown";

	वापस to_name[type];
पूर्ण

पूर्णांक nfit_spa_type(काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NFIT_UUID_MAX; i++)
		अगर (guid_equal(to_nfit_uuid(i), (guid_t *)&spa->range_guid))
			वापस i;
	वापस -1;
पूर्ण

अटल माप_प्रकार माप_spa(काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	अगर (spa->flags & ACPI_NFIT_LOCATION_COOKIE_VALID)
		वापस माप(*spa);
	वापस माप(*spa) - 8;
पूर्ण

अटल bool add_spa(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev,
		काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_spa *nfit_spa;

	अगर (spa->header.length != माप_spa(spa))
		वापस false;

	list_क्रम_each_entry(nfit_spa, &prev->spas, list) अणु
		अगर (स_भेद(nfit_spa->spa, spa, माप_spa(spa)) == 0) अणु
			list_move_tail(&nfit_spa->list, &acpi_desc->spas);
			वापस true;
		पूर्ण
	पूर्ण

	nfit_spa = devm_kzalloc(dev, माप(*nfit_spa) + माप_spa(spa),
			GFP_KERNEL);
	अगर (!nfit_spa)
		वापस false;
	INIT_LIST_HEAD(&nfit_spa->list);
	स_नकल(nfit_spa->spa, spa, माप_spa(spa));
	list_add_tail(&nfit_spa->list, &acpi_desc->spas);
	dev_dbg(dev, "spa index: %d type: %s\n",
			spa->range_index,
			spa_type_name(nfit_spa_type(spa)));
	वापस true;
पूर्ण

अटल bool add_memdev(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev,
		काष्ठा acpi_nfit_memory_map *memdev)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_memdev *nfit_memdev;

	अगर (memdev->header.length != माप(*memdev))
		वापस false;

	list_क्रम_each_entry(nfit_memdev, &prev->memdevs, list)
		अगर (स_भेद(nfit_memdev->memdev, memdev, माप(*memdev)) == 0) अणु
			list_move_tail(&nfit_memdev->list, &acpi_desc->memdevs);
			वापस true;
		पूर्ण

	nfit_memdev = devm_kzalloc(dev, माप(*nfit_memdev) + माप(*memdev),
			GFP_KERNEL);
	अगर (!nfit_memdev)
		वापस false;
	INIT_LIST_HEAD(&nfit_memdev->list);
	स_नकल(nfit_memdev->memdev, memdev, माप(*memdev));
	list_add_tail(&nfit_memdev->list, &acpi_desc->memdevs);
	dev_dbg(dev, "memdev handle: %#x spa: %d dcr: %d flags: %#x\n",
			memdev->device_handle, memdev->range_index,
			memdev->region_index, memdev->flags);
	वापस true;
पूर्ण

पूर्णांक nfit_get_smbios_id(u32 device_handle, u16 *flags)
अणु
	काष्ठा acpi_nfit_memory_map *memdev;
	काष्ठा acpi_nfit_desc *acpi_desc;
	काष्ठा nfit_mem *nfit_mem;
	u16 physical_id;

	mutex_lock(&acpi_desc_lock);
	list_क्रम_each_entry(acpi_desc, &acpi_descs, list) अणु
		mutex_lock(&acpi_desc->init_mutex);
		list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list) अणु
			memdev = __to_nfit_memdev(nfit_mem);
			अगर (memdev->device_handle == device_handle) अणु
				*flags = memdev->flags;
				physical_id = memdev->physical_id;
				mutex_unlock(&acpi_desc->init_mutex);
				mutex_unlock(&acpi_desc_lock);
				वापस physical_id;
			पूर्ण
		पूर्ण
		mutex_unlock(&acpi_desc->init_mutex);
	पूर्ण
	mutex_unlock(&acpi_desc_lock);

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(nfit_get_smbios_id);

/*
 * An implementation may provide a truncated control region अगर no block winकरोws
 * are defined.
 */
अटल माप_प्रकार माप_dcr(काष्ठा acpi_nfit_control_region *dcr)
अणु
	अगर (dcr->header.length < दुरत्व(काष्ठा acpi_nfit_control_region,
				winकरोw_size))
		वापस 0;
	अगर (dcr->winकरोws)
		वापस माप(*dcr);
	वापस दुरत्व(काष्ठा acpi_nfit_control_region, winकरोw_size);
पूर्ण

अटल bool add_dcr(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev,
		काष्ठा acpi_nfit_control_region *dcr)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_dcr *nfit_dcr;

	अगर (!माप_dcr(dcr))
		वापस false;

	list_क्रम_each_entry(nfit_dcr, &prev->dcrs, list)
		अगर (स_भेद(nfit_dcr->dcr, dcr, माप_dcr(dcr)) == 0) अणु
			list_move_tail(&nfit_dcr->list, &acpi_desc->dcrs);
			वापस true;
		पूर्ण

	nfit_dcr = devm_kzalloc(dev, माप(*nfit_dcr) + माप(*dcr),
			GFP_KERNEL);
	अगर (!nfit_dcr)
		वापस false;
	INIT_LIST_HEAD(&nfit_dcr->list);
	स_नकल(nfit_dcr->dcr, dcr, माप_dcr(dcr));
	list_add_tail(&nfit_dcr->list, &acpi_desc->dcrs);
	dev_dbg(dev, "dcr index: %d windows: %d\n",
			dcr->region_index, dcr->winकरोws);
	वापस true;
पूर्ण

अटल bool add_bdw(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev,
		काष्ठा acpi_nfit_data_region *bdw)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_bdw *nfit_bdw;

	अगर (bdw->header.length != माप(*bdw))
		वापस false;
	list_क्रम_each_entry(nfit_bdw, &prev->bdws, list)
		अगर (स_भेद(nfit_bdw->bdw, bdw, माप(*bdw)) == 0) अणु
			list_move_tail(&nfit_bdw->list, &acpi_desc->bdws);
			वापस true;
		पूर्ण

	nfit_bdw = devm_kzalloc(dev, माप(*nfit_bdw) + माप(*bdw),
			GFP_KERNEL);
	अगर (!nfit_bdw)
		वापस false;
	INIT_LIST_HEAD(&nfit_bdw->list);
	स_नकल(nfit_bdw->bdw, bdw, माप(*bdw));
	list_add_tail(&nfit_bdw->list, &acpi_desc->bdws);
	dev_dbg(dev, "bdw dcr: %d windows: %d\n",
			bdw->region_index, bdw->winकरोws);
	वापस true;
पूर्ण

अटल माप_प्रकार माप_idt(काष्ठा acpi_nfit_पूर्णांकerleave *idt)
अणु
	अगर (idt->header.length < माप(*idt))
		वापस 0;
	वापस माप(*idt) + माप(u32) * (idt->line_count - 1);
पूर्ण

अटल bool add_idt(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev,
		काष्ठा acpi_nfit_पूर्णांकerleave *idt)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_idt *nfit_idt;

	अगर (!माप_idt(idt))
		वापस false;

	list_क्रम_each_entry(nfit_idt, &prev->idts, list) अणु
		अगर (माप_idt(nfit_idt->idt) != माप_idt(idt))
			जारी;

		अगर (स_भेद(nfit_idt->idt, idt, माप_idt(idt)) == 0) अणु
			list_move_tail(&nfit_idt->list, &acpi_desc->idts);
			वापस true;
		पूर्ण
	पूर्ण

	nfit_idt = devm_kzalloc(dev, माप(*nfit_idt) + माप_idt(idt),
			GFP_KERNEL);
	अगर (!nfit_idt)
		वापस false;
	INIT_LIST_HEAD(&nfit_idt->list);
	स_नकल(nfit_idt->idt, idt, माप_idt(idt));
	list_add_tail(&nfit_idt->list, &acpi_desc->idts);
	dev_dbg(dev, "idt index: %d num_lines: %d\n",
			idt->पूर्णांकerleave_index, idt->line_count);
	वापस true;
पूर्ण

अटल माप_प्रकार माप_flush(काष्ठा acpi_nfit_flush_address *flush)
अणु
	अगर (flush->header.length < माप(*flush))
		वापस 0;
	वापस माप(*flush) + माप(u64) * (flush->hपूर्णांक_count - 1);
पूर्ण

अटल bool add_flush(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev,
		काष्ठा acpi_nfit_flush_address *flush)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_flush *nfit_flush;

	अगर (!माप_flush(flush))
		वापस false;

	list_क्रम_each_entry(nfit_flush, &prev->flushes, list) अणु
		अगर (माप_flush(nfit_flush->flush) != माप_flush(flush))
			जारी;

		अगर (स_भेद(nfit_flush->flush, flush,
					माप_flush(flush)) == 0) अणु
			list_move_tail(&nfit_flush->list, &acpi_desc->flushes);
			वापस true;
		पूर्ण
	पूर्ण

	nfit_flush = devm_kzalloc(dev, माप(*nfit_flush)
			+ माप_flush(flush), GFP_KERNEL);
	अगर (!nfit_flush)
		वापस false;
	INIT_LIST_HEAD(&nfit_flush->list);
	स_नकल(nfit_flush->flush, flush, माप_flush(flush));
	list_add_tail(&nfit_flush->list, &acpi_desc->flushes);
	dev_dbg(dev, "nfit_flush handle: %d hint_count: %d\n",
			flush->device_handle, flush->hपूर्णांक_count);
	वापस true;
पूर्ण

अटल bool add_platक्रमm_cap(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा acpi_nfit_capabilities *pcap)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	u32 mask;

	mask = (1 << (pcap->highest_capability + 1)) - 1;
	acpi_desc->platक्रमm_cap = pcap->capabilities & mask;
	dev_dbg(dev, "cap: %#x\n", acpi_desc->platक्रमm_cap);
	वापस true;
पूर्ण

अटल व्योम *add_table(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev, व्योम *table, स्थिर व्योम *end)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा acpi_nfit_header *hdr;
	व्योम *err = ERR_PTR(-ENOMEM);

	अगर (table >= end)
		वापस शून्य;

	hdr = table;
	अगर (!hdr->length) अणु
		dev_warn(dev, "found a zero length table '%d' parsing nfit\n",
			hdr->type);
		वापस शून्य;
	पूर्ण

	चयन (hdr->type) अणु
	हाल ACPI_NFIT_TYPE_SYSTEM_ADDRESS:
		अगर (!add_spa(acpi_desc, prev, table))
			वापस err;
		अवरोध;
	हाल ACPI_NFIT_TYPE_MEMORY_MAP:
		अगर (!add_memdev(acpi_desc, prev, table))
			वापस err;
		अवरोध;
	हाल ACPI_NFIT_TYPE_CONTROL_REGION:
		अगर (!add_dcr(acpi_desc, prev, table))
			वापस err;
		अवरोध;
	हाल ACPI_NFIT_TYPE_DATA_REGION:
		अगर (!add_bdw(acpi_desc, prev, table))
			वापस err;
		अवरोध;
	हाल ACPI_NFIT_TYPE_INTERLEAVE:
		अगर (!add_idt(acpi_desc, prev, table))
			वापस err;
		अवरोध;
	हाल ACPI_NFIT_TYPE_FLUSH_ADDRESS:
		अगर (!add_flush(acpi_desc, prev, table))
			वापस err;
		अवरोध;
	हाल ACPI_NFIT_TYPE_SMBIOS:
		dev_dbg(dev, "smbios\n");
		अवरोध;
	हाल ACPI_NFIT_TYPE_CAPABILITIES:
		अगर (!add_platक्रमm_cap(acpi_desc, table))
			वापस err;
		अवरोध;
	शेष:
		dev_err(dev, "unknown table '%d' parsing nfit\n", hdr->type);
		अवरोध;
	पूर्ण

	वापस table + hdr->length;
पूर्ण

अटल व्योम nfit_mem_find_spa_bdw(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_mem *nfit_mem)
अणु
	u32 device_handle = __to_nfit_memdev(nfit_mem)->device_handle;
	u16 dcr = nfit_mem->dcr->region_index;
	काष्ठा nfit_spa *nfit_spa;

	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		u16 range_index = nfit_spa->spa->range_index;
		पूर्णांक type = nfit_spa_type(nfit_spa->spa);
		काष्ठा nfit_memdev *nfit_memdev;

		अगर (type != NFIT_SPA_BDW)
			जारी;

		list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list) अणु
			अगर (nfit_memdev->memdev->range_index != range_index)
				जारी;
			अगर (nfit_memdev->memdev->device_handle != device_handle)
				जारी;
			अगर (nfit_memdev->memdev->region_index != dcr)
				जारी;

			nfit_mem->spa_bdw = nfit_spa->spa;
			वापस;
		पूर्ण
	पूर्ण

	dev_dbg(acpi_desc->dev, "SPA-BDW not found for SPA-DCR %d\n",
			nfit_mem->spa_dcr->range_index);
	nfit_mem->bdw = शून्य;
पूर्ण

अटल व्योम nfit_mem_init_bdw(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_mem *nfit_mem, काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	u16 dcr = __to_nfit_memdev(nfit_mem)->region_index;
	काष्ठा nfit_memdev *nfit_memdev;
	काष्ठा nfit_bdw *nfit_bdw;
	काष्ठा nfit_idt *nfit_idt;
	u16 idt_idx, range_index;

	list_क्रम_each_entry(nfit_bdw, &acpi_desc->bdws, list) अणु
		अगर (nfit_bdw->bdw->region_index != dcr)
			जारी;
		nfit_mem->bdw = nfit_bdw->bdw;
		अवरोध;
	पूर्ण

	अगर (!nfit_mem->bdw)
		वापस;

	nfit_mem_find_spa_bdw(acpi_desc, nfit_mem);

	अगर (!nfit_mem->spa_bdw)
		वापस;

	range_index = nfit_mem->spa_bdw->range_index;
	list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list) अणु
		अगर (nfit_memdev->memdev->range_index != range_index ||
				nfit_memdev->memdev->region_index != dcr)
			जारी;
		nfit_mem->memdev_bdw = nfit_memdev->memdev;
		idt_idx = nfit_memdev->memdev->पूर्णांकerleave_index;
		list_क्रम_each_entry(nfit_idt, &acpi_desc->idts, list) अणु
			अगर (nfit_idt->idt->पूर्णांकerleave_index != idt_idx)
				जारी;
			nfit_mem->idt_bdw = nfit_idt->idt;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __nfit_mem_init(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	काष्ठा nfit_mem *nfit_mem, *found;
	काष्ठा nfit_memdev *nfit_memdev;
	पूर्णांक type = spa ? nfit_spa_type(spa) : 0;

	चयन (type) अणु
	हाल NFIT_SPA_DCR:
	हाल NFIT_SPA_PM:
		अवरोध;
	शेष:
		अगर (spa)
			वापस 0;
	पूर्ण

	/*
	 * This loop runs in two modes, when a dimm is mapped the loop
	 * adds memdev associations to an existing dimm, or creates a
	 * dimm. In the unmapped dimm हाल this loop sweeps क्रम memdev
	 * instances with an invalid / zero range_index and adds those
	 * dimms without spa associations.
	 */
	list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list) अणु
		काष्ठा nfit_flush *nfit_flush;
		काष्ठा nfit_dcr *nfit_dcr;
		u32 device_handle;
		u16 dcr;

		अगर (spa && nfit_memdev->memdev->range_index != spa->range_index)
			जारी;
		अगर (!spa && nfit_memdev->memdev->range_index)
			जारी;
		found = शून्य;
		dcr = nfit_memdev->memdev->region_index;
		device_handle = nfit_memdev->memdev->device_handle;
		list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list)
			अगर (__to_nfit_memdev(nfit_mem)->device_handle
					== device_handle) अणु
				found = nfit_mem;
				अवरोध;
			पूर्ण

		अगर (found)
			nfit_mem = found;
		अन्यथा अणु
			nfit_mem = devm_kzalloc(acpi_desc->dev,
					माप(*nfit_mem), GFP_KERNEL);
			अगर (!nfit_mem)
				वापस -ENOMEM;
			INIT_LIST_HEAD(&nfit_mem->list);
			nfit_mem->acpi_desc = acpi_desc;
			list_add(&nfit_mem->list, &acpi_desc->dimms);
		पूर्ण

		list_क्रम_each_entry(nfit_dcr, &acpi_desc->dcrs, list) अणु
			अगर (nfit_dcr->dcr->region_index != dcr)
				जारी;
			/*
			 * Record the control region क्रम the dimm.  For
			 * the ACPI 6.1 हाल, where there are separate
			 * control regions क्रम the pmem vs blk
			 * पूर्णांकerfaces, be sure to record the extended
			 * blk details.
			 */
			अगर (!nfit_mem->dcr)
				nfit_mem->dcr = nfit_dcr->dcr;
			अन्यथा अगर (nfit_mem->dcr->winकरोws == 0
					&& nfit_dcr->dcr->winकरोws)
				nfit_mem->dcr = nfit_dcr->dcr;
			अवरोध;
		पूर्ण

		list_क्रम_each_entry(nfit_flush, &acpi_desc->flushes, list) अणु
			काष्ठा acpi_nfit_flush_address *flush;
			u16 i;

			अगर (nfit_flush->flush->device_handle != device_handle)
				जारी;
			nfit_mem->nfit_flush = nfit_flush;
			flush = nfit_flush->flush;
			nfit_mem->flush_wpq = devm_kसुस्मृति(acpi_desc->dev,
					flush->hपूर्णांक_count,
					माप(काष्ठा resource),
					GFP_KERNEL);
			अगर (!nfit_mem->flush_wpq)
				वापस -ENOMEM;
			क्रम (i = 0; i < flush->hपूर्णांक_count; i++) अणु
				काष्ठा resource *res = &nfit_mem->flush_wpq[i];

				res->start = flush->hपूर्णांक_address[i];
				res->end = res->start + 8 - 1;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (dcr && !nfit_mem->dcr) अणु
			dev_err(acpi_desc->dev, "SPA %d missing DCR %d\n",
					spa->range_index, dcr);
			वापस -ENODEV;
		पूर्ण

		अगर (type == NFIT_SPA_DCR) अणु
			काष्ठा nfit_idt *nfit_idt;
			u16 idt_idx;

			/* multiple dimms may share a SPA when पूर्णांकerleaved */
			nfit_mem->spa_dcr = spa;
			nfit_mem->memdev_dcr = nfit_memdev->memdev;
			idt_idx = nfit_memdev->memdev->पूर्णांकerleave_index;
			list_क्रम_each_entry(nfit_idt, &acpi_desc->idts, list) अणु
				अगर (nfit_idt->idt->पूर्णांकerleave_index != idt_idx)
					जारी;
				nfit_mem->idt_dcr = nfit_idt->idt;
				अवरोध;
			पूर्ण
			nfit_mem_init_bdw(acpi_desc, nfit_mem, spa);
		पूर्ण अन्यथा अगर (type == NFIT_SPA_PM) अणु
			/*
			 * A single dimm may beदीर्घ to multiple SPA-PM
			 * ranges, record at least one in addition to
			 * any SPA-DCR range.
			 */
			nfit_mem->memdev_pmem = nfit_memdev->memdev;
		पूर्ण अन्यथा
			nfit_mem->memdev_dcr = nfit_memdev->memdev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_mem_cmp(व्योम *priv, स्थिर काष्ठा list_head *_a,
		स्थिर काष्ठा list_head *_b)
अणु
	काष्ठा nfit_mem *a = container_of(_a, typeof(*a), list);
	काष्ठा nfit_mem *b = container_of(_b, typeof(*b), list);
	u32 handleA, handleB;

	handleA = __to_nfit_memdev(a)->device_handle;
	handleB = __to_nfit_memdev(b)->device_handle;
	अगर (handleA < handleB)
		वापस -1;
	अन्यथा अगर (handleA > handleB)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक nfit_mem_init(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nfit_spa *nfit_spa;
	पूर्णांक rc;


	/*
	 * For each SPA-DCR or SPA-PMEM address range find its
	 * corresponding MEMDEV(s).  From each MEMDEV find the
	 * corresponding DCR.  Then, अगर we're operating on a SPA-DCR,
	 * try to find a SPA-BDW and a corresponding BDW that references
	 * the DCR.  Throw it all पूर्णांकo an nfit_mem object.  Note, that
	 * BDWs are optional.
	 */
	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		rc = __nfit_mem_init(acpi_desc, nfit_spa->spa);
		अगर (rc)
			वापस rc;
	पूर्ण

	/*
	 * If a DIMM has failed to be mapped पूर्णांकo SPA there will be no
	 * SPA entries above. Find and रेजिस्टर all the unmapped DIMMs
	 * क्रम reporting and recovery purposes.
	 */
	rc = __nfit_mem_init(acpi_desc, शून्य);
	अगर (rc)
		वापस rc;

	list_sort(शून्य, &acpi_desc->dimms, nfit_mem_cmp);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार bus_dsm_mask_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	वापस प्र_लिखो(buf, "%#lx\n", acpi_desc->bus_dsm_mask);
पूर्ण
अटल काष्ठा device_attribute dev_attr_bus_dsm_mask =
		__ATTR(dsm_mask, 0444, bus_dsm_mask_show, शून्य);

अटल sमाप_प्रकार revision_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	वापस प्र_लिखो(buf, "%d\n", acpi_desc->acpi_header.revision);
पूर्ण
अटल DEVICE_ATTR_RO(revision);

अटल sमाप_प्रकार hw_error_scrub_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	वापस प्र_लिखो(buf, "%d\n", acpi_desc->scrub_mode);
पूर्ण

/*
 * The 'hw_error_scrub' attribute can have the following values written to it:
 * '0': Switch to the शेष mode where an exception will only insert
 *      the address of the memory error पूर्णांकo the poison and badblocks lists.
 * '1': Enable a full scrub to happen अगर an exception क्रम a memory error is
 *      received.
 */
अटल sमाप_प्रकार hw_error_scrub_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	sमाप_प्रकार rc;
	दीर्घ val;

	rc = kम_से_दीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	nfit_device_lock(dev);
	nd_desc = dev_get_drvdata(dev);
	अगर (nd_desc) अणु
		काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

		चयन (val) अणु
		हाल HW_ERROR_SCRUB_ON:
			acpi_desc->scrub_mode = HW_ERROR_SCRUB_ON;
			अवरोध;
		हाल HW_ERROR_SCRUB_OFF:
			acpi_desc->scrub_mode = HW_ERROR_SCRUB_OFF;
			अवरोध;
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	nfit_device_unlock(dev);
	अगर (rc)
		वापस rc;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(hw_error_scrub);

/*
 * This shows the number of full Address Range Scrubs that have been
 * completed since driver load समय. Userspace can रुको on this using
 * select/poll etc. A '+' at the end indicates an ARS is in progress
 */
अटल sमाप_प्रकार scrub_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	काष्ठा acpi_nfit_desc *acpi_desc;
	sमाप_प्रकार rc = -ENXIO;
	bool busy;

	nfit_device_lock(dev);
	nd_desc = dev_get_drvdata(dev);
	अगर (!nd_desc) अणु
		nfit_device_unlock(dev);
		वापस rc;
	पूर्ण
	acpi_desc = to_acpi_desc(nd_desc);

	mutex_lock(&acpi_desc->init_mutex);
	busy = test_bit(ARS_BUSY, &acpi_desc->scrub_flags)
		&& !test_bit(ARS_CANCEL, &acpi_desc->scrub_flags);
	rc = प्र_लिखो(buf, "%d%s", acpi_desc->scrub_count, busy ? "+\n" : "\n");
	/* Allow an admin to poll the busy state at a higher rate */
	अगर (busy && capable(CAP_SYS_RAWIO) && !test_and_set_bit(ARS_POLL,
				&acpi_desc->scrub_flags)) अणु
		acpi_desc->scrub_पंचांगo = 1;
		mod_delayed_work(nfit_wq, &acpi_desc->dwork, HZ);
	पूर्ण

	mutex_unlock(&acpi_desc->init_mutex);
	nfit_device_unlock(dev);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार scrub_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	sमाप_प्रकार rc;
	दीर्घ val;

	rc = kम_से_दीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;
	अगर (val != 1)
		वापस -EINVAL;

	nfit_device_lock(dev);
	nd_desc = dev_get_drvdata(dev);
	अगर (nd_desc) अणु
		काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

		rc = acpi_nfit_ars_rescan(acpi_desc, ARS_REQ_LONG);
	पूर्ण
	nfit_device_unlock(dev);
	अगर (rc)
		वापस rc;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(scrub);

अटल bool ars_supported(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	स्थिर अचिन्हित दीर्घ mask = 1 << ND_CMD_ARS_CAP | 1 << ND_CMD_ARS_START
		| 1 << ND_CMD_ARS_STATUS;

	वापस (nd_desc->cmd_mask & mask) == mask;
पूर्ण

अटल umode_t nfit_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	अगर (a == &dev_attr_scrub.attr)
		वापस ars_supported(nvdimm_bus) ? a->mode : 0;

	अगर (a == &dev_attr_firmware_activate_noidle.attr)
		वापस पूर्णांकel_fwa_supported(nvdimm_bus) ? a->mode : 0;

	वापस a->mode;
पूर्ण

अटल काष्ठा attribute *acpi_nfit_attributes[] = अणु
	&dev_attr_revision.attr,
	&dev_attr_scrub.attr,
	&dev_attr_hw_error_scrub.attr,
	&dev_attr_bus_dsm_mask.attr,
	&dev_attr_firmware_activate_noidle.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group acpi_nfit_attribute_group = अणु
	.name = "nfit",
	.attrs = acpi_nfit_attributes,
	.is_visible = nfit_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *acpi_nfit_attribute_groups[] = अणु
	&acpi_nfit_attribute_group,
	शून्य,
पूर्ण;

अटल काष्ठा acpi_nfit_memory_map *to_nfit_memdev(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	वापस __to_nfit_memdev(nfit_mem);
पूर्ण

अटल काष्ठा acpi_nfit_control_region *to_nfit_dcr(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	वापस nfit_mem->dcr;
पूर्ण

अटल sमाप_प्रकार handle_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_memory_map *memdev = to_nfit_memdev(dev);

	वापस प्र_लिखो(buf, "%#x\n", memdev->device_handle);
पूर्ण
अटल DEVICE_ATTR_RO(handle);

अटल sमाप_प्रकार phys_id_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_memory_map *memdev = to_nfit_memdev(dev);

	वापस प्र_लिखो(buf, "%#x\n", memdev->physical_id);
पूर्ण
अटल DEVICE_ATTR_RO(phys_id);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", be16_to_cpu(dcr->venकरोr_id));
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार rev_id_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", be16_to_cpu(dcr->revision_id));
पूर्ण
अटल DEVICE_ATTR_RO(rev_id);

अटल sमाप_प्रकार device_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", be16_to_cpu(dcr->device_id));
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार subप्रणाली_venकरोr_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", be16_to_cpu(dcr->subप्रणाली_venकरोr_id));
पूर्ण
अटल DEVICE_ATTR_RO(subप्रणाली_venकरोr);

अटल sमाप_प्रकार subप्रणाली_rev_id_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n",
			be16_to_cpu(dcr->subप्रणाली_revision_id));
पूर्ण
अटल DEVICE_ATTR_RO(subप्रणाली_rev_id);

अटल sमाप_प्रकार subप्रणाली_device_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", be16_to_cpu(dcr->subप्रणाली_device_id));
पूर्ण
अटल DEVICE_ATTR_RO(subप्रणाली_device);

अटल पूर्णांक num_nvdimm_क्रमmats(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	पूर्णांक क्रमmats = 0;

	अगर (nfit_mem->memdev_pmem)
		क्रमmats++;
	अगर (nfit_mem->memdev_bdw)
		क्रमmats++;
	वापस क्रमmats;
पूर्ण

अटल sमाप_प्रकार क्रमmat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%04x\n", le16_to_cpu(dcr->code));
पूर्ण
अटल DEVICE_ATTR_RO(क्रमmat);

अटल sमाप_प्रकार क्रमmat1_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 handle;
	sमाप_प्रकार rc = -ENXIO;
	काष्ठा nfit_mem *nfit_mem;
	काष्ठा nfit_memdev *nfit_memdev;
	काष्ठा acpi_nfit_desc *acpi_desc;
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	nfit_mem = nvdimm_provider_data(nvdimm);
	acpi_desc = nfit_mem->acpi_desc;
	handle = to_nfit_memdev(dev)->device_handle;

	/* assumes DIMMs have at most 2 published पूर्णांकerface codes */
	mutex_lock(&acpi_desc->init_mutex);
	list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list) अणु
		काष्ठा acpi_nfit_memory_map *memdev = nfit_memdev->memdev;
		काष्ठा nfit_dcr *nfit_dcr;

		अगर (memdev->device_handle != handle)
			जारी;

		list_क्रम_each_entry(nfit_dcr, &acpi_desc->dcrs, list) अणु
			अगर (nfit_dcr->dcr->region_index != memdev->region_index)
				जारी;
			अगर (nfit_dcr->dcr->code == dcr->code)
				जारी;
			rc = प्र_लिखो(buf, "0x%04x\n",
					le16_to_cpu(nfit_dcr->dcr->code));
			अवरोध;
		पूर्ण
		अगर (rc != -ENXIO)
			अवरोध;
	पूर्ण
	mutex_unlock(&acpi_desc->init_mutex);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(क्रमmat1);

अटल sमाप_प्रकार क्रमmats_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

	वापस प्र_लिखो(buf, "%d\n", num_nvdimm_क्रमmats(nvdimm));
पूर्ण
अटल DEVICE_ATTR_RO(क्रमmats);

अटल sमाप_प्रकार serial_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_nfit_control_region *dcr = to_nfit_dcr(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", be32_to_cpu(dcr->serial_number));
पूर्ण
अटल DEVICE_ATTR_RO(serial);

अटल sमाप_प्रकार family_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	अगर (nfit_mem->family < 0)
		वापस -ENXIO;
	वापस प्र_लिखो(buf, "%d\n", nfit_mem->family);
पूर्ण
अटल DEVICE_ATTR_RO(family);

अटल sमाप_प्रकार dsm_mask_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	अगर (nfit_mem->family < 0)
		वापस -ENXIO;
	वापस प्र_लिखो(buf, "%#lx\n", nfit_mem->dsm_mask);
पूर्ण
अटल DEVICE_ATTR_RO(dsm_mask);

अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	u16 flags = __to_nfit_memdev(nfit_mem)->flags;

	अगर (test_bit(NFIT_MEM_सूचीTY, &nfit_mem->flags))
		flags |= ACPI_NFIT_MEM_FLUSH_FAILED;

	वापस प्र_लिखो(buf, "%s%s%s%s%s%s%s\n",
		flags & ACPI_NFIT_MEM_SAVE_FAILED ? "save_fail " : "",
		flags & ACPI_NFIT_MEM_RESTORE_FAILED ? "restore_fail " : "",
		flags & ACPI_NFIT_MEM_FLUSH_FAILED ? "flush_fail " : "",
		flags & ACPI_NFIT_MEM_NOT_ARMED ? "not_armed " : "",
		flags & ACPI_NFIT_MEM_HEALTH_OBSERVED ? "smart_event " : "",
		flags & ACPI_NFIT_MEM_MAP_FAILED ? "map_fail " : "",
		flags & ACPI_NFIT_MEM_HEALTH_ENABLED ? "smart_notify " : "");
पूर्ण
अटल DEVICE_ATTR_RO(flags);

अटल sमाप_प्रकार id_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	वापस प्र_लिखो(buf, "%s\n", nfit_mem->id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार dirty_shutकरोwn_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	वापस प्र_लिखो(buf, "%d\n", nfit_mem->dirty_shutकरोwn);
पूर्ण
अटल DEVICE_ATTR_RO(dirty_shutकरोwn);

अटल काष्ठा attribute *acpi_nfit_dimm_attributes[] = अणु
	&dev_attr_handle.attr,
	&dev_attr_phys_id.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_device.attr,
	&dev_attr_rev_id.attr,
	&dev_attr_subप्रणाली_venकरोr.attr,
	&dev_attr_subप्रणाली_device.attr,
	&dev_attr_subप्रणाली_rev_id.attr,
	&dev_attr_क्रमmat.attr,
	&dev_attr_क्रमmats.attr,
	&dev_attr_क्रमmat1.attr,
	&dev_attr_serial.attr,
	&dev_attr_flags.attr,
	&dev_attr_id.attr,
	&dev_attr_family.attr,
	&dev_attr_dsm_mask.attr,
	&dev_attr_dirty_shutकरोwn.attr,
	शून्य,
पूर्ण;

अटल umode_t acpi_nfit_dimm_attr_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);

	अगर (!to_nfit_dcr(dev)) अणु
		/* Without a dcr only the memdev attributes can be surfaced */
		अगर (a == &dev_attr_handle.attr || a == &dev_attr_phys_id.attr
				|| a == &dev_attr_flags.attr
				|| a == &dev_attr_family.attr
				|| a == &dev_attr_dsm_mask.attr)
			वापस a->mode;
		वापस 0;
	पूर्ण

	अगर (a == &dev_attr_क्रमmat1.attr && num_nvdimm_क्रमmats(nvdimm) <= 1)
		वापस 0;

	अगर (!test_bit(NFIT_MEM_सूचीTY_COUNT, &nfit_mem->flags)
			&& a == &dev_attr_dirty_shutकरोwn.attr)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group acpi_nfit_dimm_attribute_group = अणु
	.name = "nfit",
	.attrs = acpi_nfit_dimm_attributes,
	.is_visible = acpi_nfit_dimm_attr_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *acpi_nfit_dimm_attribute_groups[] = अणु
	&acpi_nfit_dimm_attribute_group,
	शून्य,
पूर्ण;

अटल काष्ठा nvdimm *acpi_nfit_dimm_by_handle(काष्ठा acpi_nfit_desc *acpi_desc,
		u32 device_handle)
अणु
	काष्ठा nfit_mem *nfit_mem;

	list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list)
		अगर (__to_nfit_memdev(nfit_mem)->device_handle == device_handle)
			वापस nfit_mem->nvdimm;

	वापस शून्य;
पूर्ण

व्योम __acpi_nvdimm_notअगरy(काष्ठा device *dev, u32 event)
अणु
	काष्ठा nfit_mem *nfit_mem;
	काष्ठा acpi_nfit_desc *acpi_desc;

	dev_dbg(dev->parent, "%s: event: %d\n", dev_name(dev),
			event);

	अगर (event != NFIT_NOTIFY_DIMM_HEALTH) अणु
		dev_dbg(dev->parent, "%s: unknown event: %d\n", dev_name(dev),
				event);
		वापस;
	पूर्ण

	acpi_desc = dev_get_drvdata(dev->parent);
	अगर (!acpi_desc)
		वापस;

	/*
	 * If we successfully retrieved acpi_desc, then we know nfit_mem data
	 * is still valid.
	 */
	nfit_mem = dev_get_drvdata(dev);
	अगर (nfit_mem && nfit_mem->flags_attr)
		sysfs_notअगरy_dirent(nfit_mem->flags_attr);
पूर्ण
EXPORT_SYMBOL_GPL(__acpi_nvdimm_notअगरy);

अटल व्योम acpi_nvdimm_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा acpi_device *adev = data;
	काष्ठा device *dev = &adev->dev;

	nfit_device_lock(dev->parent);
	__acpi_nvdimm_notअगरy(dev, event);
	nfit_device_unlock(dev->parent);
पूर्ण

अटल bool acpi_nvdimm_has_method(काष्ठा acpi_device *adev, अक्षर *method)
अणु
	acpi_handle handle;
	acpi_status status;

	status = acpi_get_handle(adev->handle, method, &handle);

	अगर (ACPI_SUCCESS(status))
		वापस true;
	वापस false;
पूर्ण

__weak व्योम nfit_पूर्णांकel_shutकरोwn_status(काष्ठा nfit_mem *nfit_mem)
अणु
	काष्ठा device *dev = &nfit_mem->adev->dev;
	काष्ठा nd_पूर्णांकel_smart smart = अणु 0 पूर्ण;
	जोड़ acpi_object in_buf = अणु
		.buffer.type = ACPI_TYPE_BUFFER,
		.buffer.length = 0,
	पूर्ण;
	जोड़ acpi_object in_obj = अणु
		.package.type = ACPI_TYPE_PACKAGE,
		.package.count = 1,
		.package.elements = &in_buf,
	पूर्ण;
	स्थिर u8 func = ND_INTEL_SMART;
	स्थिर guid_t *guid = to_nfit_uuid(nfit_mem->family);
	u8 revid = nfit_dsm_revid(nfit_mem->family, func);
	काष्ठा acpi_device *adev = nfit_mem->adev;
	acpi_handle handle = adev->handle;
	जोड़ acpi_object *out_obj;

	अगर ((nfit_mem->dsm_mask & (1 << func)) == 0)
		वापस;

	out_obj = acpi_evaluate_dsm(handle, guid, revid, func, &in_obj);
	अगर (!out_obj || out_obj->type != ACPI_TYPE_BUFFER
			|| out_obj->buffer.length < माप(smart)) अणु
		dev_dbg(dev->parent, "%s: failed to retrieve initial health\n",
				dev_name(dev));
		ACPI_FREE(out_obj);
		वापस;
	पूर्ण
	स_नकल(&smart, out_obj->buffer.poपूर्णांकer, माप(smart));
	ACPI_FREE(out_obj);

	अगर (smart.flags & ND_INTEL_SMART_SHUTDOWN_VALID) अणु
		अगर (smart.shutकरोwn_state)
			set_bit(NFIT_MEM_सूचीTY, &nfit_mem->flags);
	पूर्ण

	अगर (smart.flags & ND_INTEL_SMART_SHUTDOWN_COUNT_VALID) अणु
		set_bit(NFIT_MEM_सूचीTY_COUNT, &nfit_mem->flags);
		nfit_mem->dirty_shutकरोwn = smart.shutकरोwn_count;
	पूर्ण
पूर्ण

अटल व्योम populate_shutकरोwn_status(काष्ठा nfit_mem *nfit_mem)
अणु
	/*
	 * For DIMMs that provide a dynamic facility to retrieve a
	 * dirty-shutकरोwn status and/or a dirty-shutकरोwn count, cache
	 * these values in nfit_mem.
	 */
	अगर (nfit_mem->family == NVDIMM_FAMILY_INTEL)
		nfit_पूर्णांकel_shutकरोwn_status(nfit_mem);
पूर्ण

अटल पूर्णांक acpi_nfit_add_dimm(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_mem *nfit_mem, u32 device_handle)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;
	काष्ठा acpi_device *adev, *adev_dimm;
	काष्ठा device *dev = acpi_desc->dev;
	अचिन्हित दीर्घ dsm_mask, label_mask;
	स्थिर guid_t *guid;
	पूर्णांक i;
	पूर्णांक family = -1;
	काष्ठा acpi_nfit_control_region *dcr = nfit_mem->dcr;

	/* nfit test assumes 1:1 relationship between commands and dsms */
	nfit_mem->dsm_mask = acpi_desc->dimm_cmd_क्रमce_en;
	nfit_mem->family = NVDIMM_FAMILY_INTEL;
	set_bit(NVDIMM_FAMILY_INTEL, &nd_desc->dimm_family_mask);

	अगर (dcr->valid_fields & ACPI_NFIT_CONTROL_MFG_INFO_VALID)
		प्र_लिखो(nfit_mem->id, "%04x-%02x-%04x-%08x",
				be16_to_cpu(dcr->venकरोr_id),
				dcr->manufacturing_location,
				be16_to_cpu(dcr->manufacturing_date),
				be32_to_cpu(dcr->serial_number));
	अन्यथा
		प्र_लिखो(nfit_mem->id, "%04x-%08x",
				be16_to_cpu(dcr->venकरोr_id),
				be32_to_cpu(dcr->serial_number));

	adev = to_acpi_dev(acpi_desc);
	अगर (!adev) अणु
		/* unit test हाल */
		populate_shutकरोwn_status(nfit_mem);
		वापस 0;
	पूर्ण

	adev_dimm = acpi_find_child_device(adev, device_handle, false);
	nfit_mem->adev = adev_dimm;
	अगर (!adev_dimm) अणु
		dev_err(dev, "no ACPI.NFIT device with _ADR %#x, disabling...\n",
				device_handle);
		वापस क्रमce_enable_dimms ? 0 : -ENODEV;
	पूर्ण

	अगर (ACPI_FAILURE(acpi_install_notअगरy_handler(adev_dimm->handle,
		ACPI_DEVICE_NOTIFY, acpi_nvdimm_notअगरy, adev_dimm))) अणु
		dev_err(dev, "%s: notification registration failed\n",
				dev_name(&adev_dimm->dev));
		वापस -ENXIO;
	पूर्ण
	/*
	 * Record nfit_mem क्रम the notअगरication path to track back to
	 * the nfit sysfs attributes क्रम this dimm device object.
	 */
	dev_set_drvdata(&adev_dimm->dev, nfit_mem);

	/*
	 * There are 4 "legacy" NVDIMM command sets
	 * (NVDIMM_FAMILY_अणुINTEL,MSFT,HPE1,HPE2पूर्ण) that were created beक्रमe
	 * an EFI working group was established to स्थिरrain this
	 * prolअगरeration. The nfit driver probes क्रम the supported command
	 * set by GUID. Note, अगर you're a platक्रमm developer looking to add
	 * a new command set to this probe, consider using an existing set,
	 * or otherwise seek approval to publish the command set at
	 * http://www.uefi.org/RFIC_LIST.
	 *
	 * Note, that checking क्रम function0 (bit0) tells us अगर any commands
	 * are reachable through this GUID.
	 */
	clear_bit(NVDIMM_FAMILY_INTEL, &nd_desc->dimm_family_mask);
	क्रम (i = 0; i <= NVDIMM_FAMILY_MAX; i++)
		अगर (acpi_check_dsm(adev_dimm->handle, to_nfit_uuid(i), 1, 1)) अणु
			set_bit(i, &nd_desc->dimm_family_mask);
			अगर (family < 0 || i == शेष_dsm_family)
				family = i;
		पूर्ण

	/* limit the supported commands to those that are खुलाly करोcumented */
	nfit_mem->family = family;
	अगर (override_dsm_mask && !disable_venकरोr_specअगरic)
		dsm_mask = override_dsm_mask;
	अन्यथा अगर (nfit_mem->family == NVDIMM_FAMILY_INTEL) अणु
		dsm_mask = NVDIMM_INTEL_CMDMASK;
		अगर (disable_venकरोr_specअगरic)
			dsm_mask &= ~(1 << ND_CMD_VENDOR);
	पूर्ण अन्यथा अगर (nfit_mem->family == NVDIMM_FAMILY_HPE1) अणु
		dsm_mask = 0x1c3c76;
	पूर्ण अन्यथा अगर (nfit_mem->family == NVDIMM_FAMILY_HPE2) अणु
		dsm_mask = 0x1fe;
		अगर (disable_venकरोr_specअगरic)
			dsm_mask &= ~(1 << 8);
	पूर्ण अन्यथा अगर (nfit_mem->family == NVDIMM_FAMILY_MSFT) अणु
		dsm_mask = 0xffffffff;
	पूर्ण अन्यथा अगर (nfit_mem->family == NVDIMM_FAMILY_HYPERV) अणु
		dsm_mask = 0x1f;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "unknown dimm command family\n");
		nfit_mem->family = -1;
		/* DSMs are optional, जारी loading the driver... */
		वापस 0;
	पूर्ण

	/*
	 * Function 0 is the command पूर्णांकerrogation function, करोn't
	 * export it to potential userspace use, and enable it to be
	 * used as an error value in acpi_nfit_ctl().
	 */
	dsm_mask &= ~1UL;

	guid = to_nfit_uuid(nfit_mem->family);
	क्रम_each_set_bit(i, &dsm_mask, BITS_PER_LONG)
		अगर (acpi_check_dsm(adev_dimm->handle, guid,
					nfit_dsm_revid(nfit_mem->family, i),
					1ULL << i))
			set_bit(i, &nfit_mem->dsm_mask);

	/*
	 * Prefer the NVDIMM_FAMILY_INTEL label पढ़ो commands अगर present
	 * due to their better semantics handling locked capacity.
	 */
	label_mask = 1 << ND_CMD_GET_CONFIG_SIZE | 1 << ND_CMD_GET_CONFIG_DATA
		| 1 << ND_CMD_SET_CONFIG_DATA;
	अगर (family == NVDIMM_FAMILY_INTEL
			&& (dsm_mask & label_mask) == label_mask)
		/* skip _LSअणुI,R,Wपूर्ण enabling */;
	अन्यथा अणु
		अगर (acpi_nvdimm_has_method(adev_dimm, "_LSI")
				&& acpi_nvdimm_has_method(adev_dimm, "_LSR")) अणु
			dev_dbg(dev, "%s: has _LSR\n", dev_name(&adev_dimm->dev));
			set_bit(NFIT_MEM_LSR, &nfit_mem->flags);
		पूर्ण

		अगर (test_bit(NFIT_MEM_LSR, &nfit_mem->flags)
				&& acpi_nvdimm_has_method(adev_dimm, "_LSW")) अणु
			dev_dbg(dev, "%s: has _LSW\n", dev_name(&adev_dimm->dev));
			set_bit(NFIT_MEM_LSW, &nfit_mem->flags);
		पूर्ण

		/*
		 * Quirk पढ़ो-only label configurations to preserve
		 * access to label-less namespaces by शेष.
		 */
		अगर (!test_bit(NFIT_MEM_LSW, &nfit_mem->flags)
				&& !क्रमce_labels) अणु
			dev_dbg(dev, "%s: No _LSW, disable labels\n",
					dev_name(&adev_dimm->dev));
			clear_bit(NFIT_MEM_LSR, &nfit_mem->flags);
		पूर्ण अन्यथा
			dev_dbg(dev, "%s: Force enable labels\n",
					dev_name(&adev_dimm->dev));
	पूर्ण

	populate_shutकरोwn_status(nfit_mem);

	वापस 0;
पूर्ण

अटल व्योम shutकरोwn_dimm_notअगरy(व्योम *data)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = data;
	काष्ठा nfit_mem *nfit_mem;

	mutex_lock(&acpi_desc->init_mutex);
	/*
	 * Clear out the nfit_mem->flags_attr and shut करोwn dimm event
	 * notअगरications.
	 */
	list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list) अणु
		काष्ठा acpi_device *adev_dimm = nfit_mem->adev;

		अगर (nfit_mem->flags_attr) अणु
			sysfs_put(nfit_mem->flags_attr);
			nfit_mem->flags_attr = शून्य;
		पूर्ण
		अगर (adev_dimm) अणु
			acpi_हटाओ_notअगरy_handler(adev_dimm->handle,
					ACPI_DEVICE_NOTIFY, acpi_nvdimm_notअगरy);
			dev_set_drvdata(&adev_dimm->dev, शून्य);
		पूर्ण
	पूर्ण
	mutex_unlock(&acpi_desc->init_mutex);
पूर्ण

अटल स्थिर काष्ठा nvdimm_security_ops *acpi_nfit_get_security_ops(पूर्णांक family)
अणु
	चयन (family) अणु
	हाल NVDIMM_FAMILY_INTEL:
		वापस पूर्णांकel_security_ops;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvdimm_fw_ops *acpi_nfit_get_fw_ops(
		काष्ठा nfit_mem *nfit_mem)
अणु
	अचिन्हित दीर्घ mask;
	काष्ठा acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;

	अगर (!nd_desc->fw_ops)
		वापस शून्य;

	अगर (nfit_mem->family != NVDIMM_FAMILY_INTEL)
		वापस शून्य;

	mask = nfit_mem->dsm_mask & NVDIMM_INTEL_FW_ACTIVATE_CMDMASK;
	अगर (mask != NVDIMM_INTEL_FW_ACTIVATE_CMDMASK)
		वापस शून्य;

	वापस पूर्णांकel_fw_ops;
पूर्ण

अटल पूर्णांक acpi_nfit_रेजिस्टर_dimms(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nfit_mem *nfit_mem;
	पूर्णांक dimm_count = 0, rc;
	काष्ठा nvdimm *nvdimm;

	list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list) अणु
		काष्ठा acpi_nfit_flush_address *flush;
		अचिन्हित दीर्घ flags = 0, cmd_mask;
		काष्ठा nfit_memdev *nfit_memdev;
		u32 device_handle;
		u16 mem_flags;

		device_handle = __to_nfit_memdev(nfit_mem)->device_handle;
		nvdimm = acpi_nfit_dimm_by_handle(acpi_desc, device_handle);
		अगर (nvdimm) अणु
			dimm_count++;
			जारी;
		पूर्ण

		अगर (nfit_mem->bdw && nfit_mem->memdev_pmem) अणु
			set_bit(NDD_ALIASING, &flags);
			set_bit(NDD_LABELING, &flags);
		पूर्ण

		/* collate flags across all memdevs क्रम this dimm */
		list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list) अणु
			काष्ठा acpi_nfit_memory_map *dimm_memdev;

			dimm_memdev = __to_nfit_memdev(nfit_mem);
			अगर (dimm_memdev->device_handle
					!= nfit_memdev->memdev->device_handle)
				जारी;
			dimm_memdev->flags |= nfit_memdev->memdev->flags;
		पूर्ण

		mem_flags = __to_nfit_memdev(nfit_mem)->flags;
		अगर (mem_flags & ACPI_NFIT_MEM_NOT_ARMED)
			set_bit(NDD_UNARMED, &flags);

		rc = acpi_nfit_add_dimm(acpi_desc, nfit_mem, device_handle);
		अगर (rc)
			जारी;

		/*
		 * TODO: provide translation क्रम non-NVDIMM_FAMILY_INTEL
		 * devices (i.e. from nd_cmd to acpi_dsm) to standardize the
		 * userspace पूर्णांकerface.
		 */
		cmd_mask = 1UL << ND_CMD_CALL;
		अगर (nfit_mem->family == NVDIMM_FAMILY_INTEL) अणु
			/*
			 * These commands have a 1:1 correspondence
			 * between DSM payload and libnvdimm ioctl
			 * payload क्रमmat.
			 */
			cmd_mask |= nfit_mem->dsm_mask & NVDIMM_STANDARD_CMDMASK;
		पूर्ण

		/* Quirk to ignore LOCAL क्रम labels on HYPERV DIMMs */
		अगर (nfit_mem->family == NVDIMM_FAMILY_HYPERV)
			set_bit(NDD_NOBLK, &flags);

		अगर (test_bit(NFIT_MEM_LSR, &nfit_mem->flags)) अणु
			set_bit(ND_CMD_GET_CONFIG_SIZE, &cmd_mask);
			set_bit(ND_CMD_GET_CONFIG_DATA, &cmd_mask);
		पूर्ण
		अगर (test_bit(NFIT_MEM_LSW, &nfit_mem->flags))
			set_bit(ND_CMD_SET_CONFIG_DATA, &cmd_mask);

		flush = nfit_mem->nfit_flush ? nfit_mem->nfit_flush->flush
			: शून्य;
		nvdimm = __nvdimm_create(acpi_desc->nvdimm_bus, nfit_mem,
				acpi_nfit_dimm_attribute_groups,
				flags, cmd_mask, flush ? flush->hपूर्णांक_count : 0,
				nfit_mem->flush_wpq, &nfit_mem->id[0],
				acpi_nfit_get_security_ops(nfit_mem->family),
				acpi_nfit_get_fw_ops(nfit_mem));
		अगर (!nvdimm)
			वापस -ENOMEM;

		nfit_mem->nvdimm = nvdimm;
		dimm_count++;

		अगर ((mem_flags & ACPI_NFIT_MEM_FAILED_MASK) == 0)
			जारी;

		dev_err(acpi_desc->dev, "Error found in NVDIMM %s flags:%s%s%s%s%s\n",
				nvdimm_name(nvdimm),
		  mem_flags & ACPI_NFIT_MEM_SAVE_FAILED ? " save_fail" : "",
		  mem_flags & ACPI_NFIT_MEM_RESTORE_FAILED ? " restore_fail":"",
		  mem_flags & ACPI_NFIT_MEM_FLUSH_FAILED ? " flush_fail" : "",
		  mem_flags & ACPI_NFIT_MEM_NOT_ARMED ? " not_armed" : "",
		  mem_flags & ACPI_NFIT_MEM_MAP_FAILED ? " map_fail" : "");

	पूर्ण

	rc = nvdimm_bus_check_dimm_count(acpi_desc->nvdimm_bus, dimm_count);
	अगर (rc)
		वापस rc;

	/*
	 * Now that dimms are successfully रेजिस्टरed, and async registration
	 * is flushed, attempt to enable event notअगरication.
	 */
	list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list) अणु
		काष्ठा kernfs_node *nfit_kernfs;

		nvdimm = nfit_mem->nvdimm;
		अगर (!nvdimm)
			जारी;

		nfit_kernfs = sysfs_get_dirent(nvdimm_kobj(nvdimm)->sd, "nfit");
		अगर (nfit_kernfs)
			nfit_mem->flags_attr = sysfs_get_dirent(nfit_kernfs,
					"flags");
		sysfs_put(nfit_kernfs);
		अगर (!nfit_mem->flags_attr)
			dev_warn(acpi_desc->dev, "%s: notifications disabled\n",
					nvdimm_name(nvdimm));
	पूर्ण

	वापस devm_add_action_or_reset(acpi_desc->dev, shutकरोwn_dimm_notअगरy,
			acpi_desc);
पूर्ण

/*
 * These स्थिरants are निजी because there are no kernel consumers of
 * these commands.
 */
क्रमागत nfit_aux_cmds अणु
	NFIT_CMD_TRANSLATE_SPA = 5,
	NFIT_CMD_ARS_INJECT_SET = 7,
	NFIT_CMD_ARS_INJECT_CLEAR = 8,
	NFIT_CMD_ARS_INJECT_GET = 9,
पूर्ण;

अटल व्योम acpi_nfit_init_dsms(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;
	स्थिर guid_t *guid = to_nfit_uuid(NFIT_DEV_BUS);
	अचिन्हित दीर्घ dsm_mask, *mask;
	काष्ठा acpi_device *adev;
	पूर्णांक i;

	set_bit(ND_CMD_CALL, &nd_desc->cmd_mask);
	set_bit(NVDIMM_BUS_FAMILY_NFIT, &nd_desc->bus_family_mask);

	/* enable nfit_test to inject bus command emulation */
	अगर (acpi_desc->bus_cmd_क्रमce_en) अणु
		nd_desc->cmd_mask = acpi_desc->bus_cmd_क्रमce_en;
		mask = &nd_desc->bus_family_mask;
		अगर (acpi_desc->family_dsm_mask[NVDIMM_BUS_FAMILY_INTEL]) अणु
			set_bit(NVDIMM_BUS_FAMILY_INTEL, mask);
			nd_desc->fw_ops = पूर्णांकel_bus_fw_ops;
		पूर्ण
	पूर्ण

	adev = to_acpi_dev(acpi_desc);
	अगर (!adev)
		वापस;

	क्रम (i = ND_CMD_ARS_CAP; i <= ND_CMD_CLEAR_ERROR; i++)
		अगर (acpi_check_dsm(adev->handle, guid, 1, 1ULL << i))
			set_bit(i, &nd_desc->cmd_mask);

	dsm_mask =
		(1 << ND_CMD_ARS_CAP) |
		(1 << ND_CMD_ARS_START) |
		(1 << ND_CMD_ARS_STATUS) |
		(1 << ND_CMD_CLEAR_ERROR) |
		(1 << NFIT_CMD_TRANSLATE_SPA) |
		(1 << NFIT_CMD_ARS_INJECT_SET) |
		(1 << NFIT_CMD_ARS_INJECT_CLEAR) |
		(1 << NFIT_CMD_ARS_INJECT_GET);
	क्रम_each_set_bit(i, &dsm_mask, BITS_PER_LONG)
		अगर (acpi_check_dsm(adev->handle, guid, 1, 1ULL << i))
			set_bit(i, &acpi_desc->bus_dsm_mask);

	/* Enumerate allowed NVDIMM_BUS_FAMILY_INTEL commands */
	dsm_mask = NVDIMM_BUS_INTEL_FW_ACTIVATE_CMDMASK;
	guid = to_nfit_bus_uuid(NVDIMM_BUS_FAMILY_INTEL);
	mask = &acpi_desc->family_dsm_mask[NVDIMM_BUS_FAMILY_INTEL];
	क्रम_each_set_bit(i, &dsm_mask, BITS_PER_LONG)
		अगर (acpi_check_dsm(adev->handle, guid, 1, 1ULL << i))
			set_bit(i, mask);

	अगर (*mask == dsm_mask) अणु
		set_bit(NVDIMM_BUS_FAMILY_INTEL, &nd_desc->bus_family_mask);
		nd_desc->fw_ops = पूर्णांकel_bus_fw_ops;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार range_index_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	काष्ठा nfit_spa *nfit_spa = nd_region_provider_data(nd_region);

	वापस प्र_लिखो(buf, "%d\n", nfit_spa->spa->range_index);
पूर्ण
अटल DEVICE_ATTR_RO(range_index);

अटल काष्ठा attribute *acpi_nfit_region_attributes[] = अणु
	&dev_attr_range_index.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group acpi_nfit_region_attribute_group = अणु
	.name = "nfit",
	.attrs = acpi_nfit_region_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *acpi_nfit_region_attribute_groups[] = अणु
	&acpi_nfit_region_attribute_group,
	शून्य,
पूर्ण;

/* enough info to uniquely specअगरy an पूर्णांकerleave set */
काष्ठा nfit_set_info अणु
	u64 region_offset;
	u32 serial_number;
	u32 pad;
पूर्ण;

काष्ठा nfit_set_info2 अणु
	u64 region_offset;
	u32 serial_number;
	u16 venकरोr_id;
	u16 manufacturing_date;
	u8 manufacturing_location;
	u8 reserved[31];
पूर्ण;

अटल पूर्णांक cmp_map_compat(स्थिर व्योम *m0, स्थिर व्योम *m1)
अणु
	स्थिर काष्ठा nfit_set_info *map0 = m0;
	स्थिर काष्ठा nfit_set_info *map1 = m1;

	वापस स_भेद(&map0->region_offset, &map1->region_offset,
			माप(u64));
पूर्ण

अटल पूर्णांक cmp_map(स्थिर व्योम *m0, स्थिर व्योम *m1)
अणु
	स्थिर काष्ठा nfit_set_info *map0 = m0;
	स्थिर काष्ठा nfit_set_info *map1 = m1;

	अगर (map0->region_offset < map1->region_offset)
		वापस -1;
	अन्यथा अगर (map0->region_offset > map1->region_offset)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक cmp_map2(स्थिर व्योम *m0, स्थिर व्योम *m1)
अणु
	स्थिर काष्ठा nfit_set_info2 *map0 = m0;
	स्थिर काष्ठा nfit_set_info2 *map1 = m1;

	अगर (map0->region_offset < map1->region_offset)
		वापस -1;
	अन्यथा अगर (map0->region_offset > map1->region_offset)
		वापस 1;
	वापस 0;
पूर्ण

/* Retrieve the nth entry referencing this spa */
अटल काष्ठा acpi_nfit_memory_map *memdev_from_spa(
		काष्ठा acpi_nfit_desc *acpi_desc, u16 range_index, पूर्णांक n)
अणु
	काष्ठा nfit_memdev *nfit_memdev;

	list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list)
		अगर (nfit_memdev->memdev->range_index == range_index)
			अगर (n-- == 0)
				वापस nfit_memdev->memdev;
	वापस शून्य;
पूर्ण

अटल पूर्णांक acpi_nfit_init_पूर्णांकerleave_set(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nd_region_desc *ndr_desc,
		काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nd_पूर्णांकerleave_set *nd_set;
	u16 nr = ndr_desc->num_mappings;
	काष्ठा nfit_set_info2 *info2;
	काष्ठा nfit_set_info *info;
	पूर्णांक i;

	nd_set = devm_kzalloc(dev, माप(*nd_set), GFP_KERNEL);
	अगर (!nd_set)
		वापस -ENOMEM;
	import_guid(&nd_set->type_guid, spa->range_guid);

	info = devm_kसुस्मृति(dev, nr, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info2 = devm_kसुस्मृति(dev, nr, माप(*info2), GFP_KERNEL);
	अगर (!info2)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा nd_mapping_desc *mapping = &ndr_desc->mapping[i];
		काष्ठा nvdimm *nvdimm = mapping->nvdimm;
		काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
		काष्ठा nfit_set_info *map = &info[i];
		काष्ठा nfit_set_info2 *map2 = &info2[i];
		काष्ठा acpi_nfit_memory_map *memdev =
			memdev_from_spa(acpi_desc, spa->range_index, i);
		काष्ठा acpi_nfit_control_region *dcr = nfit_mem->dcr;

		अगर (!memdev || !nfit_mem->dcr) अणु
			dev_err(dev, "%s: failed to find DCR\n", __func__);
			वापस -ENODEV;
		पूर्ण

		map->region_offset = memdev->region_offset;
		map->serial_number = dcr->serial_number;

		map2->region_offset = memdev->region_offset;
		map2->serial_number = dcr->serial_number;
		map2->venकरोr_id = dcr->venकरोr_id;
		map2->manufacturing_date = dcr->manufacturing_date;
		map2->manufacturing_location = dcr->manufacturing_location;
	पूर्ण

	/* v1.1 namespaces */
	sort(info, nr, माप(*info), cmp_map, शून्य);
	nd_set->cookie1 = nd_fletcher64(info, माप(*info) * nr, 0);

	/* v1.2 namespaces */
	sort(info2, nr, माप(*info2), cmp_map2, शून्य);
	nd_set->cookie2 = nd_fletcher64(info2, माप(*info2) * nr, 0);

	/* support v1.1 namespaces created with the wrong sort order */
	sort(info, nr, माप(*info), cmp_map_compat, शून्य);
	nd_set->altcookie = nd_fletcher64(info, माप(*info) * nr, 0);

	/* record the result of the sort क्रम the mapping position */
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा nfit_set_info2 *map2 = &info2[i];
		पूर्णांक j;

		क्रम (j = 0; j < nr; j++) अणु
			काष्ठा nd_mapping_desc *mapping = &ndr_desc->mapping[j];
			काष्ठा nvdimm *nvdimm = mapping->nvdimm;
			काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
			काष्ठा acpi_nfit_control_region *dcr = nfit_mem->dcr;

			अगर (map2->serial_number == dcr->serial_number &&
			    map2->venकरोr_id == dcr->venकरोr_id &&
			    map2->manufacturing_date == dcr->manufacturing_date &&
			    map2->manufacturing_location
				    == dcr->manufacturing_location) अणु
				mapping->position = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ndr_desc->nd_set = nd_set;
	devm_kमुक्त(dev, info);
	devm_kमुक्त(dev, info2);

	वापस 0;
पूर्ण

अटल u64 to_पूर्णांकerleave_offset(u64 offset, काष्ठा nfit_blk_mmio *mmio)
अणु
	काष्ठा acpi_nfit_पूर्णांकerleave *idt = mmio->idt;
	u32 sub_line_offset, line_index, line_offset;
	u64 line_no, table_skip_count, table_offset;

	line_no = भाग_u64_rem(offset, mmio->line_size, &sub_line_offset);
	table_skip_count = भाग_u64_rem(line_no, mmio->num_lines, &line_index);
	line_offset = idt->line_offset[line_index]
		* mmio->line_size;
	table_offset = table_skip_count * mmio->table_size;

	वापस mmio->base_offset + line_offset + table_offset + sub_line_offset;
पूर्ण

अटल u32 पढ़ो_blk_stat(काष्ठा nfit_blk *nfit_blk, अचिन्हित पूर्णांक bw)
अणु
	काष्ठा nfit_blk_mmio *mmio = &nfit_blk->mmio[DCR];
	u64 offset = nfit_blk->stat_offset + mmio->size * bw;
	स्थिर u32 STATUS_MASK = 0x80000037;

	अगर (mmio->num_lines)
		offset = to_पूर्णांकerleave_offset(offset, mmio);

	वापस पढ़ोl(mmio->addr.base + offset) & STATUS_MASK;
पूर्ण

अटल व्योम ग_लिखो_blk_ctl(काष्ठा nfit_blk *nfit_blk, अचिन्हित पूर्णांक bw,
		resource_माप_प्रकार dpa, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक ग_लिखो)
अणु
	u64 cmd, offset;
	काष्ठा nfit_blk_mmio *mmio = &nfit_blk->mmio[DCR];

	क्रमागत अणु
		BCW_OFFSET_MASK = (1ULL << 48)-1,
		BCW_LEN_SHIFT = 48,
		BCW_LEN_MASK = (1ULL << 8) - 1,
		BCW_CMD_SHIFT = 56,
	पूर्ण;

	cmd = (dpa >> L1_CACHE_SHIFT) & BCW_OFFSET_MASK;
	len = len >> L1_CACHE_SHIFT;
	cmd |= ((u64) len & BCW_LEN_MASK) << BCW_LEN_SHIFT;
	cmd |= ((u64) ग_लिखो) << BCW_CMD_SHIFT;

	offset = nfit_blk->cmd_offset + mmio->size * bw;
	अगर (mmio->num_lines)
		offset = to_पूर्णांकerleave_offset(offset, mmio);

	ग_लिखोq(cmd, mmio->addr.base + offset);
	nvdimm_flush(nfit_blk->nd_region, शून्य);

	अगर (nfit_blk->dimm_flags & NFIT_BLK_DCR_LATCH)
		पढ़ोq(mmio->addr.base + offset);
पूर्ण

अटल पूर्णांक acpi_nfit_blk_single_io(काष्ठा nfit_blk *nfit_blk,
		resource_माप_प्रकार dpa, व्योम *iobuf, माप_प्रकार len, पूर्णांक rw,
		अचिन्हित पूर्णांक lane)
अणु
	काष्ठा nfit_blk_mmio *mmio = &nfit_blk->mmio[BDW];
	अचिन्हित पूर्णांक copied = 0;
	u64 base_offset;
	पूर्णांक rc;

	base_offset = nfit_blk->bdw_offset + dpa % L1_CACHE_BYTES
		+ lane * mmio->size;
	ग_लिखो_blk_ctl(nfit_blk, lane, dpa, len, rw);
	जबतक (len) अणु
		अचिन्हित पूर्णांक c;
		u64 offset;

		अगर (mmio->num_lines) अणु
			u32 line_offset;

			offset = to_पूर्णांकerleave_offset(base_offset + copied,
					mmio);
			भाग_u64_rem(offset, mmio->line_size, &line_offset);
			c = min_t(माप_प्रकार, len, mmio->line_size - line_offset);
		पूर्ण अन्यथा अणु
			offset = base_offset + nfit_blk->bdw_offset;
			c = len;
		पूर्ण

		अगर (rw)
			स_नकल_flushcache(mmio->addr.aperture + offset, iobuf + copied, c);
		अन्यथा अणु
			अगर (nfit_blk->dimm_flags & NFIT_BLK_READ_FLUSH)
				arch_invalidate_pmem((व्योम __क्रमce *)
					mmio->addr.aperture + offset, c);

			स_नकल(iobuf + copied, mmio->addr.aperture + offset, c);
		पूर्ण

		copied += c;
		len -= c;
	पूर्ण

	अगर (rw)
		nvdimm_flush(nfit_blk->nd_region, शून्य);

	rc = पढ़ो_blk_stat(nfit_blk, lane) ? -EIO : 0;
	वापस rc;
पूर्ण

अटल पूर्णांक acpi_nfit_blk_region_करो_io(काष्ठा nd_blk_region *ndbr,
		resource_माप_प्रकार dpa, व्योम *iobuf, u64 len, पूर्णांक rw)
अणु
	काष्ठा nfit_blk *nfit_blk = nd_blk_region_provider_data(ndbr);
	काष्ठा nfit_blk_mmio *mmio = &nfit_blk->mmio[BDW];
	काष्ठा nd_region *nd_region = nfit_blk->nd_region;
	अचिन्हित पूर्णांक lane, copied = 0;
	पूर्णांक rc = 0;

	lane = nd_region_acquire_lane(nd_region);
	जबतक (len) अणु
		u64 c = min(len, mmio->size);

		rc = acpi_nfit_blk_single_io(nfit_blk, dpa + copied,
				iobuf + copied, c, rw, lane);
		अगर (rc)
			अवरोध;

		copied += c;
		len -= c;
	पूर्ण
	nd_region_release_lane(nd_region, lane);

	वापस rc;
पूर्ण

अटल पूर्णांक nfit_blk_init_पूर्णांकerleave(काष्ठा nfit_blk_mmio *mmio,
		काष्ठा acpi_nfit_पूर्णांकerleave *idt, u16 पूर्णांकerleave_ways)
अणु
	अगर (idt) अणु
		mmio->num_lines = idt->line_count;
		mmio->line_size = idt->line_size;
		अगर (पूर्णांकerleave_ways == 0)
			वापस -ENXIO;
		mmio->table_size = mmio->num_lines * पूर्णांकerleave_ways
			* mmio->line_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_nfit_blk_get_flags(काष्ठा nvdimm_bus_descriptor *nd_desc,
		काष्ठा nvdimm *nvdimm, काष्ठा nfit_blk *nfit_blk)
अणु
	काष्ठा nd_cmd_dimm_flags flags;
	पूर्णांक rc;

	स_रखो(&flags, 0, माप(flags));
	rc = nd_desc->ndctl(nd_desc, nvdimm, ND_CMD_DIMM_FLAGS, &flags,
			माप(flags), शून्य);

	अगर (rc >= 0 && flags.status == 0)
		nfit_blk->dimm_flags = flags.flags;
	अन्यथा अगर (rc == -ENOTTY) अणु
		/* fall back to a conservative शेष */
		nfit_blk->dimm_flags = NFIT_BLK_DCR_LATCH | NFIT_BLK_READ_FLUSH;
		rc = 0;
	पूर्ण अन्यथा
		rc = -ENXIO;

	वापस rc;
पूर्ण

अटल पूर्णांक acpi_nfit_blk_region_enable(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा nd_blk_region *ndbr = to_nd_blk_region(dev);
	काष्ठा nfit_blk_mmio *mmio;
	काष्ठा nfit_blk *nfit_blk;
	काष्ठा nfit_mem *nfit_mem;
	काष्ठा nvdimm *nvdimm;
	पूर्णांक rc;

	nvdimm = nd_blk_region_to_dimm(ndbr);
	nfit_mem = nvdimm_provider_data(nvdimm);
	अगर (!nfit_mem || !nfit_mem->dcr || !nfit_mem->bdw) अणु
		dev_dbg(dev, "missing%s%s%s\n",
				nfit_mem ? "" : " nfit_mem",
				(nfit_mem && nfit_mem->dcr) ? "" : " dcr",
				(nfit_mem && nfit_mem->bdw) ? "" : " bdw");
		वापस -ENXIO;
	पूर्ण

	nfit_blk = devm_kzalloc(dev, माप(*nfit_blk), GFP_KERNEL);
	अगर (!nfit_blk)
		वापस -ENOMEM;
	nd_blk_region_set_provider_data(ndbr, nfit_blk);
	nfit_blk->nd_region = to_nd_region(dev);

	/* map block aperture memory */
	nfit_blk->bdw_offset = nfit_mem->bdw->offset;
	mmio = &nfit_blk->mmio[BDW];
	mmio->addr.base = devm_nvdimm_memremap(dev, nfit_mem->spa_bdw->address,
			nfit_mem->spa_bdw->length, nd_blk_memremap_flags(ndbr));
	अगर (!mmio->addr.base) अणु
		dev_dbg(dev, "%s failed to map bdw\n",
				nvdimm_name(nvdimm));
		वापस -ENOMEM;
	पूर्ण
	mmio->size = nfit_mem->bdw->size;
	mmio->base_offset = nfit_mem->memdev_bdw->region_offset;
	mmio->idt = nfit_mem->idt_bdw;
	mmio->spa = nfit_mem->spa_bdw;
	rc = nfit_blk_init_पूर्णांकerleave(mmio, nfit_mem->idt_bdw,
			nfit_mem->memdev_bdw->पूर्णांकerleave_ways);
	अगर (rc) अणु
		dev_dbg(dev, "%s failed to init bdw interleave\n",
				nvdimm_name(nvdimm));
		वापस rc;
	पूर्ण

	/* map block control memory */
	nfit_blk->cmd_offset = nfit_mem->dcr->command_offset;
	nfit_blk->stat_offset = nfit_mem->dcr->status_offset;
	mmio = &nfit_blk->mmio[DCR];
	mmio->addr.base = devm_nvdimm_ioremap(dev, nfit_mem->spa_dcr->address,
			nfit_mem->spa_dcr->length);
	अगर (!mmio->addr.base) अणु
		dev_dbg(dev, "%s failed to map dcr\n",
				nvdimm_name(nvdimm));
		वापस -ENOMEM;
	पूर्ण
	mmio->size = nfit_mem->dcr->winकरोw_size;
	mmio->base_offset = nfit_mem->memdev_dcr->region_offset;
	mmio->idt = nfit_mem->idt_dcr;
	mmio->spa = nfit_mem->spa_dcr;
	rc = nfit_blk_init_पूर्णांकerleave(mmio, nfit_mem->idt_dcr,
			nfit_mem->memdev_dcr->पूर्णांकerleave_ways);
	अगर (rc) अणु
		dev_dbg(dev, "%s failed to init dcr interleave\n",
				nvdimm_name(nvdimm));
		वापस rc;
	पूर्ण

	rc = acpi_nfit_blk_get_flags(nd_desc, nvdimm, nfit_blk);
	अगर (rc < 0) अणु
		dev_dbg(dev, "%s failed get DIMM flags\n",
				nvdimm_name(nvdimm));
		वापस rc;
	पूर्ण

	अगर (nvdimm_has_flush(nfit_blk->nd_region) < 0)
		dev_warn(dev, "unable to guarantee persistence of writes\n");

	अगर (mmio->line_size == 0)
		वापस 0;

	अगर ((u32) nfit_blk->cmd_offset % mmio->line_size
			+ 8 > mmio->line_size) अणु
		dev_dbg(dev, "cmd_offset crosses interleave boundary\n");
		वापस -ENXIO;
	पूर्ण अन्यथा अगर ((u32) nfit_blk->stat_offset % mmio->line_size
			+ 8 > mmio->line_size) अणु
		dev_dbg(dev, "stat_offset crosses interleave boundary\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ars_get_cap(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nd_cmd_ars_cap *cmd, काष्ठा nfit_spa *nfit_spa)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;
	काष्ठा acpi_nfit_प्रणाली_address *spa = nfit_spa->spa;
	पूर्णांक cmd_rc, rc;

	cmd->address = spa->address;
	cmd->length = spa->length;
	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_ARS_CAP, cmd,
			माप(*cmd), &cmd_rc);
	अगर (rc < 0)
		वापस rc;
	वापस cmd_rc;
पूर्ण

अटल पूर्णांक ars_start(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_spa *nfit_spa, क्रमागत nfit_ars_state req_type)
अणु
	पूर्णांक rc;
	पूर्णांक cmd_rc;
	काष्ठा nd_cmd_ars_start ars_start;
	काष्ठा acpi_nfit_प्रणाली_address *spa = nfit_spa->spa;
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;

	स_रखो(&ars_start, 0, माप(ars_start));
	ars_start.address = spa->address;
	ars_start.length = spa->length;
	अगर (req_type == ARS_REQ_SHORT)
		ars_start.flags = ND_ARS_RETURN_PREV_DATA;
	अगर (nfit_spa_type(spa) == NFIT_SPA_PM)
		ars_start.type = ND_ARS_PERSISTENT;
	अन्यथा अगर (nfit_spa_type(spa) == NFIT_SPA_VOLATILE)
		ars_start.type = ND_ARS_VOLATILE;
	अन्यथा
		वापस -ENOTTY;

	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_ARS_START, &ars_start,
			माप(ars_start), &cmd_rc);

	अगर (rc < 0)
		वापस rc;
	अगर (cmd_rc < 0)
		वापस cmd_rc;
	set_bit(ARS_VALID, &acpi_desc->scrub_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ars_जारी(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	पूर्णांक rc, cmd_rc;
	काष्ठा nd_cmd_ars_start ars_start;
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;
	काष्ठा nd_cmd_ars_status *ars_status = acpi_desc->ars_status;

	ars_start = (काष्ठा nd_cmd_ars_start) अणु
		.address = ars_status->restart_address,
		.length = ars_status->restart_length,
		.type = ars_status->type,
	पूर्ण;
	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_ARS_START, &ars_start,
			माप(ars_start), &cmd_rc);
	अगर (rc < 0)
		वापस rc;
	वापस cmd_rc;
पूर्ण

अटल पूर्णांक ars_get_status(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;
	काष्ठा nd_cmd_ars_status *ars_status = acpi_desc->ars_status;
	पूर्णांक rc, cmd_rc;

	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_ARS_STATUS, ars_status,
			acpi_desc->max_ars, &cmd_rc);
	अगर (rc < 0)
		वापस rc;
	वापस cmd_rc;
पूर्ण

अटल व्योम ars_complete(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_spa *nfit_spa)
अणु
	काष्ठा nd_cmd_ars_status *ars_status = acpi_desc->ars_status;
	काष्ठा acpi_nfit_प्रणाली_address *spa = nfit_spa->spa;
	काष्ठा nd_region *nd_region = nfit_spa->nd_region;
	काष्ठा device *dev;

	lockdep_निश्चित_held(&acpi_desc->init_mutex);
	/*
	 * Only advance the ARS state क्रम ARS runs initiated by the
	 * kernel, ignore ARS results from BIOS initiated runs क्रम scrub
	 * completion tracking.
	 */
	अगर (acpi_desc->scrub_spa != nfit_spa)
		वापस;

	अगर ((ars_status->address >= spa->address && ars_status->address
				< spa->address + spa->length)
			|| (ars_status->address < spa->address)) अणु
		/*
		 * Assume that अगर a scrub starts at an offset from the
		 * start of nfit_spa that we are in the continuation
		 * हाल.
		 *
		 * Otherwise, अगर the scrub covers the spa range, mark
		 * any pending request complete.
		 */
		अगर (ars_status->address + ars_status->length
				>= spa->address + spa->length)
				/* complete */;
		अन्यथा
			वापस;
	पूर्ण अन्यथा
		वापस;

	acpi_desc->scrub_spa = शून्य;
	अगर (nd_region) अणु
		dev = nd_region_dev(nd_region);
		nvdimm_region_notअगरy(nd_region, NVDIMM_REVALIDATE_POISON);
	पूर्ण अन्यथा
		dev = acpi_desc->dev;
	dev_dbg(dev, "ARS: range %d complete\n", spa->range_index);
पूर्ण

अटल पूर्णांक ars_status_process_records(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = acpi_desc->nvdimm_bus;
	काष्ठा nd_cmd_ars_status *ars_status = acpi_desc->ars_status;
	पूर्णांक rc;
	u32 i;

	/*
	 * First record starts at 44 byte offset from the start of the
	 * payload.
	 */
	अगर (ars_status->out_length < 44)
		वापस 0;

	/*
	 * Ignore potentially stale results that are only refreshed
	 * after a start-ARS event.
	 */
	अगर (!test_and_clear_bit(ARS_VALID, &acpi_desc->scrub_flags)) अणु
		dev_dbg(acpi_desc->dev, "skip %d stale records\n",
				ars_status->num_records);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ars_status->num_records; i++) अणु
		/* only process full records */
		अगर (ars_status->out_length
				< 44 + माप(काष्ठा nd_ars_record) * (i + 1))
			अवरोध;
		rc = nvdimm_bus_add_badrange(nvdimm_bus,
				ars_status->records[i].err_address,
				ars_status->records[i].length);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर (i < ars_status->num_records)
		dev_warn(acpi_desc->dev, "detected truncated ars results\n");

	वापस 0;
पूर्ण

अटल व्योम acpi_nfit_हटाओ_resource(व्योम *data)
अणु
	काष्ठा resource *res = data;

	हटाओ_resource(res);
पूर्ण

अटल पूर्णांक acpi_nfit_insert_resource(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nd_region_desc *ndr_desc)
अणु
	काष्ठा resource *res, *nd_res = ndr_desc->res;
	पूर्णांक is_pmem, ret;

	/* No operation अगर the region is alपढ़ोy रेजिस्टरed as PMEM */
	is_pmem = region_पूर्णांकersects(nd_res->start, resource_size(nd_res),
				IORESOURCE_MEM, IORES_DESC_PERSISTENT_MEMORY);
	अगर (is_pmem == REGION_INTERSECTS)
		वापस 0;

	res = devm_kzalloc(acpi_desc->dev, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	res->name = "Persistent Memory";
	res->start = nd_res->start;
	res->end = nd_res->end;
	res->flags = IORESOURCE_MEM;
	res->desc = IORES_DESC_PERSISTENT_MEMORY;

	ret = insert_resource(&iomem_resource, res);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(acpi_desc->dev,
					acpi_nfit_हटाओ_resource,
					res);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_nfit_init_mapping(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nd_mapping_desc *mapping, काष्ठा nd_region_desc *ndr_desc,
		काष्ठा acpi_nfit_memory_map *memdev,
		काष्ठा nfit_spa *nfit_spa)
अणु
	काष्ठा nvdimm *nvdimm = acpi_nfit_dimm_by_handle(acpi_desc,
			memdev->device_handle);
	काष्ठा acpi_nfit_प्रणाली_address *spa = nfit_spa->spa;
	काष्ठा nd_blk_region_desc *ndbr_desc;
	काष्ठा nfit_mem *nfit_mem;
	पूर्णांक rc;

	अगर (!nvdimm) अणु
		dev_err(acpi_desc->dev, "spa%d dimm: %#x not found\n",
				spa->range_index, memdev->device_handle);
		वापस -ENODEV;
	पूर्ण

	mapping->nvdimm = nvdimm;
	चयन (nfit_spa_type(spa)) अणु
	हाल NFIT_SPA_PM:
	हाल NFIT_SPA_VOLATILE:
		mapping->start = memdev->address;
		mapping->size = memdev->region_size;
		अवरोध;
	हाल NFIT_SPA_DCR:
		nfit_mem = nvdimm_provider_data(nvdimm);
		अगर (!nfit_mem || !nfit_mem->bdw) अणु
			dev_dbg(acpi_desc->dev, "spa%d %s missing bdw\n",
					spa->range_index, nvdimm_name(nvdimm));
			अवरोध;
		पूर्ण

		mapping->size = nfit_mem->bdw->capacity;
		mapping->start = nfit_mem->bdw->start_address;
		ndr_desc->num_lanes = nfit_mem->bdw->winकरोws;
		ndr_desc->mapping = mapping;
		ndr_desc->num_mappings = 1;
		ndbr_desc = to_blk_region_desc(ndr_desc);
		ndbr_desc->enable = acpi_nfit_blk_region_enable;
		ndbr_desc->करो_io = acpi_desc->blk_करो_io;
		rc = acpi_nfit_init_पूर्णांकerleave_set(acpi_desc, ndr_desc, spa);
		अगर (rc)
			वापस rc;
		nfit_spa->nd_region = nvdimm_blk_region_create(acpi_desc->nvdimm_bus,
				ndr_desc);
		अगर (!nfit_spa->nd_region)
			वापस -ENOMEM;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool nfit_spa_is_भव(काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	वापस (nfit_spa_type(spa) == NFIT_SPA_VDISK ||
		nfit_spa_type(spa) == NFIT_SPA_VCD   ||
		nfit_spa_type(spa) == NFIT_SPA_PDISK ||
		nfit_spa_type(spa) == NFIT_SPA_PCD);
पूर्ण

अटल bool nfit_spa_is_अस्थिर(काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	वापस (nfit_spa_type(spa) == NFIT_SPA_VDISK ||
		nfit_spa_type(spa) == NFIT_SPA_VCD   ||
		nfit_spa_type(spa) == NFIT_SPA_VOLATILE);
पूर्ण

अटल पूर्णांक acpi_nfit_रेजिस्टर_region(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_spa *nfit_spa)
अणु
	अटल काष्ठा nd_mapping_desc mappings[ND_MAX_MAPPINGS];
	काष्ठा acpi_nfit_प्रणाली_address *spa = nfit_spa->spa;
	काष्ठा nd_blk_region_desc ndbr_desc;
	काष्ठा nd_region_desc *ndr_desc;
	काष्ठा nfit_memdev *nfit_memdev;
	काष्ठा nvdimm_bus *nvdimm_bus;
	काष्ठा resource res;
	पूर्णांक count = 0, rc;

	अगर (nfit_spa->nd_region)
		वापस 0;

	अगर (spa->range_index == 0 && !nfit_spa_is_भव(spa)) अणु
		dev_dbg(acpi_desc->dev, "detected invalid spa index\n");
		वापस 0;
	पूर्ण

	स_रखो(&res, 0, माप(res));
	स_रखो(&mappings, 0, माप(mappings));
	स_रखो(&ndbr_desc, 0, माप(ndbr_desc));
	res.start = spa->address;
	res.end = res.start + spa->length - 1;
	ndr_desc = &ndbr_desc.ndr_desc;
	ndr_desc->res = &res;
	ndr_desc->provider_data = nfit_spa;
	ndr_desc->attr_groups = acpi_nfit_region_attribute_groups;
	अगर (spa->flags & ACPI_NFIT_PROXIMITY_VALID) अणु
		ndr_desc->numa_node = pxm_to_online_node(spa->proximity_करोमुख्य);
		ndr_desc->target_node = pxm_to_node(spa->proximity_करोमुख्य);
	पूर्ण अन्यथा अणु
		ndr_desc->numa_node = NUMA_NO_NODE;
		ndr_desc->target_node = NUMA_NO_NODE;
	पूर्ण

	/*
	 * Persistence करोमुख्य bits are hierarchical, अगर
	 * ACPI_NFIT_CAPABILITY_CACHE_FLUSH is set then
	 * ACPI_NFIT_CAPABILITY_MEM_FLUSH is implied.
	 */
	अगर (acpi_desc->platक्रमm_cap & ACPI_NFIT_CAPABILITY_CACHE_FLUSH)
		set_bit(ND_REGION_PERSIST_CACHE, &ndr_desc->flags);
	अन्यथा अगर (acpi_desc->platक्रमm_cap & ACPI_NFIT_CAPABILITY_MEM_FLUSH)
		set_bit(ND_REGION_PERSIST_MEMCTRL, &ndr_desc->flags);

	list_क्रम_each_entry(nfit_memdev, &acpi_desc->memdevs, list) अणु
		काष्ठा acpi_nfit_memory_map *memdev = nfit_memdev->memdev;
		काष्ठा nd_mapping_desc *mapping;

		अगर (memdev->range_index != spa->range_index)
			जारी;
		अगर (count >= ND_MAX_MAPPINGS) अणु
			dev_err(acpi_desc->dev, "spa%d exceeds max mappings %d\n",
					spa->range_index, ND_MAX_MAPPINGS);
			वापस -ENXIO;
		पूर्ण
		mapping = &mappings[count++];
		rc = acpi_nfit_init_mapping(acpi_desc, mapping, ndr_desc,
				memdev, nfit_spa);
		अगर (rc)
			जाओ out;
	पूर्ण

	ndr_desc->mapping = mappings;
	ndr_desc->num_mappings = count;
	rc = acpi_nfit_init_पूर्णांकerleave_set(acpi_desc, ndr_desc, spa);
	अगर (rc)
		जाओ out;

	nvdimm_bus = acpi_desc->nvdimm_bus;
	अगर (nfit_spa_type(spa) == NFIT_SPA_PM) अणु
		rc = acpi_nfit_insert_resource(acpi_desc, ndr_desc);
		अगर (rc) अणु
			dev_warn(acpi_desc->dev,
				"failed to insert pmem resource to iomem: %d\n",
				rc);
			जाओ out;
		पूर्ण

		nfit_spa->nd_region = nvdimm_pmem_region_create(nvdimm_bus,
				ndr_desc);
		अगर (!nfit_spa->nd_region)
			rc = -ENOMEM;
	पूर्ण अन्यथा अगर (nfit_spa_is_अस्थिर(spa)) अणु
		nfit_spa->nd_region = nvdimm_अस्थिर_region_create(nvdimm_bus,
				ndr_desc);
		अगर (!nfit_spa->nd_region)
			rc = -ENOMEM;
	पूर्ण अन्यथा अगर (nfit_spa_is_भव(spa)) अणु
		nfit_spa->nd_region = nvdimm_pmem_region_create(nvdimm_bus,
				ndr_desc);
		अगर (!nfit_spa->nd_region)
			rc = -ENOMEM;
	पूर्ण

 out:
	अगर (rc)
		dev_err(acpi_desc->dev, "failed to register spa range %d\n",
				nfit_spa->spa->range_index);
	वापस rc;
पूर्ण

अटल पूर्णांक ars_status_alloc(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nd_cmd_ars_status *ars_status;

	अगर (acpi_desc->ars_status) अणु
		स_रखो(acpi_desc->ars_status, 0, acpi_desc->max_ars);
		वापस 0;
	पूर्ण

	ars_status = devm_kzalloc(dev, acpi_desc->max_ars, GFP_KERNEL);
	अगर (!ars_status)
		वापस -ENOMEM;
	acpi_desc->ars_status = ars_status;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_nfit_query_poison(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	पूर्णांक rc;

	अगर (ars_status_alloc(acpi_desc))
		वापस -ENOMEM;

	rc = ars_get_status(acpi_desc);

	अगर (rc < 0 && rc != -ENOSPC)
		वापस rc;

	अगर (ars_status_process_records(acpi_desc))
		dev_err(acpi_desc->dev, "Failed to process ARS records\n");

	वापस rc;
पूर्ण

अटल पूर्णांक ars_रेजिस्टर(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_spa *nfit_spa)
अणु
	पूर्णांक rc;

	अगर (test_bit(ARS_FAILED, &nfit_spa->ars_state))
		वापस acpi_nfit_रेजिस्टर_region(acpi_desc, nfit_spa);

	set_bit(ARS_REQ_SHORT, &nfit_spa->ars_state);
	अगर (!no_init_ars)
		set_bit(ARS_REQ_LONG, &nfit_spa->ars_state);

	चयन (acpi_nfit_query_poison(acpi_desc)) अणु
	हाल 0:
	हाल -ENOSPC:
	हाल -EAGAIN:
		rc = ars_start(acpi_desc, nfit_spa, ARS_REQ_SHORT);
		/* shouldn't happen, try again later */
		अगर (rc == -EBUSY)
			अवरोध;
		अगर (rc) अणु
			set_bit(ARS_FAILED, &nfit_spa->ars_state);
			अवरोध;
		पूर्ण
		clear_bit(ARS_REQ_SHORT, &nfit_spa->ars_state);
		rc = acpi_nfit_query_poison(acpi_desc);
		अगर (rc)
			अवरोध;
		acpi_desc->scrub_spa = nfit_spa;
		ars_complete(acpi_desc, nfit_spa);
		/*
		 * If ars_complete() says we didn't complete the
		 * लघु scrub, we'll try again with a दीर्घ
		 * request.
		 */
		acpi_desc->scrub_spa = शून्य;
		अवरोध;
	हाल -EBUSY:
	हाल -ENOMEM:
		/*
		 * BIOS was using ARS, रुको क्रम it to complete (or
		 * resources to become available) and then perक्रमm our
		 * own scrubs.
		 */
		अवरोध;
	शेष:
		set_bit(ARS_FAILED, &nfit_spa->ars_state);
		अवरोध;
	पूर्ण

	वापस acpi_nfit_रेजिस्टर_region(acpi_desc, nfit_spa);
पूर्ण

अटल व्योम ars_complete_all(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nfit_spa *nfit_spa;

	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		अगर (test_bit(ARS_FAILED, &nfit_spa->ars_state))
			जारी;
		ars_complete(acpi_desc, nfit_spa);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक __acpi_nfit_scrub(काष्ठा acpi_nfit_desc *acpi_desc,
		पूर्णांक query_rc)
अणु
	अचिन्हित पूर्णांक पंचांगo = acpi_desc->scrub_पंचांगo;
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_spa *nfit_spa;

	lockdep_निश्चित_held(&acpi_desc->init_mutex);

	अगर (test_bit(ARS_CANCEL, &acpi_desc->scrub_flags))
		वापस 0;

	अगर (query_rc == -EBUSY) अणु
		dev_dbg(dev, "ARS: ARS busy\n");
		वापस min(30U * 60U, पंचांगo * 2);
	पूर्ण
	अगर (query_rc == -ENOSPC) अणु
		dev_dbg(dev, "ARS: ARS continue\n");
		ars_जारी(acpi_desc);
		वापस 1;
	पूर्ण
	अगर (query_rc && query_rc != -EAGAIN) अणु
		अचिन्हित दीर्घ दीर्घ addr, end;

		addr = acpi_desc->ars_status->address;
		end = addr + acpi_desc->ars_status->length;
		dev_dbg(dev, "ARS: %llx-%llx failed (%d)\n", addr, end,
				query_rc);
	पूर्ण

	ars_complete_all(acpi_desc);
	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		क्रमागत nfit_ars_state req_type;
		पूर्णांक rc;

		अगर (test_bit(ARS_FAILED, &nfit_spa->ars_state))
			जारी;

		/* prefer लघु ARS requests first */
		अगर (test_bit(ARS_REQ_SHORT, &nfit_spa->ars_state))
			req_type = ARS_REQ_SHORT;
		अन्यथा अगर (test_bit(ARS_REQ_LONG, &nfit_spa->ars_state))
			req_type = ARS_REQ_LONG;
		अन्यथा
			जारी;
		rc = ars_start(acpi_desc, nfit_spa, req_type);

		dev = nd_region_dev(nfit_spa->nd_region);
		dev_dbg(dev, "ARS: range %d ARS start %s (%d)\n",
				nfit_spa->spa->range_index,
				req_type == ARS_REQ_SHORT ? "short" : "long",
				rc);
		/*
		 * Hmm, we raced someone अन्यथा starting ARS? Try again in
		 * a bit.
		 */
		अगर (rc == -EBUSY)
			वापस 1;
		अगर (rc == 0) अणु
			dev_WARN_ONCE(dev, acpi_desc->scrub_spa,
					"scrub start while range %d active\n",
					acpi_desc->scrub_spa->spa->range_index);
			clear_bit(req_type, &nfit_spa->ars_state);
			acpi_desc->scrub_spa = nfit_spa;
			/*
			 * Consider this spa last क्रम future scrub
			 * requests
			 */
			list_move_tail(&nfit_spa->list, &acpi_desc->spas);
			वापस 1;
		पूर्ण

		dev_err(dev, "ARS: range %d ARS failed (%d)\n",
				nfit_spa->spa->range_index, rc);
		set_bit(ARS_FAILED, &nfit_spa->ars_state);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __sched_ars(काष्ठा acpi_nfit_desc *acpi_desc, अचिन्हित पूर्णांक पंचांगo)
अणु
	lockdep_निश्चित_held(&acpi_desc->init_mutex);

	set_bit(ARS_BUSY, &acpi_desc->scrub_flags);
	/* note this should only be set from within the workqueue */
	अगर (पंचांगo)
		acpi_desc->scrub_पंचांगo = पंचांगo;
	queue_delayed_work(nfit_wq, &acpi_desc->dwork, पंचांगo * HZ);
पूर्ण

अटल व्योम sched_ars(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	__sched_ars(acpi_desc, 0);
पूर्ण

अटल व्योम notअगरy_ars_करोne(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	lockdep_निश्चित_held(&acpi_desc->init_mutex);

	clear_bit(ARS_BUSY, &acpi_desc->scrub_flags);
	acpi_desc->scrub_count++;
	अगर (acpi_desc->scrub_count_state)
		sysfs_notअगरy_dirent(acpi_desc->scrub_count_state);
पूर्ण

अटल व्योम acpi_nfit_scrub(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc;
	अचिन्हित पूर्णांक पंचांगo;
	पूर्णांक query_rc;

	acpi_desc = container_of(work, typeof(*acpi_desc), dwork.work);
	mutex_lock(&acpi_desc->init_mutex);
	query_rc = acpi_nfit_query_poison(acpi_desc);
	पंचांगo = __acpi_nfit_scrub(acpi_desc, query_rc);
	अगर (पंचांगo)
		__sched_ars(acpi_desc, पंचांगo);
	अन्यथा
		notअगरy_ars_करोne(acpi_desc);
	स_रखो(acpi_desc->ars_status, 0, acpi_desc->max_ars);
	clear_bit(ARS_POLL, &acpi_desc->scrub_flags);
	mutex_unlock(&acpi_desc->init_mutex);
पूर्ण

अटल व्योम acpi_nfit_init_ars(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_spa *nfit_spa)
अणु
	पूर्णांक type = nfit_spa_type(nfit_spa->spa);
	काष्ठा nd_cmd_ars_cap ars_cap;
	पूर्णांक rc;

	set_bit(ARS_FAILED, &nfit_spa->ars_state);
	स_रखो(&ars_cap, 0, माप(ars_cap));
	rc = ars_get_cap(acpi_desc, &ars_cap, nfit_spa);
	अगर (rc < 0)
		वापस;
	/* check that the supported scrub types match the spa type */
	अगर (type == NFIT_SPA_VOLATILE && ((ars_cap.status >> 16)
				& ND_ARS_VOLATILE) == 0)
		वापस;
	अगर (type == NFIT_SPA_PM && ((ars_cap.status >> 16)
				& ND_ARS_PERSISTENT) == 0)
		वापस;

	nfit_spa->max_ars = ars_cap.max_ars_out;
	nfit_spa->clear_err_unit = ars_cap.clear_err_unit;
	acpi_desc->max_ars = max(nfit_spa->max_ars, acpi_desc->max_ars);
	clear_bit(ARS_FAILED, &nfit_spa->ars_state);
पूर्ण

अटल पूर्णांक acpi_nfit_रेजिस्टर_regions(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा nfit_spa *nfit_spa;
	पूर्णांक rc, करो_sched_ars = 0;

	set_bit(ARS_VALID, &acpi_desc->scrub_flags);
	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		चयन (nfit_spa_type(nfit_spa->spa)) अणु
		हाल NFIT_SPA_VOLATILE:
		हाल NFIT_SPA_PM:
			acpi_nfit_init_ars(acpi_desc, nfit_spa);
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		चयन (nfit_spa_type(nfit_spa->spa)) अणु
		हाल NFIT_SPA_VOLATILE:
		हाल NFIT_SPA_PM:
			/* रेजिस्टर regions and kick off initial ARS run */
			rc = ars_रेजिस्टर(acpi_desc, nfit_spa);
			अगर (rc)
				वापस rc;

			/*
			 * Kick off background ARS अगर at least one
			 * region successfully रेजिस्टरed ARS
			 */
			अगर (!test_bit(ARS_FAILED, &nfit_spa->ars_state))
				करो_sched_ars++;
			अवरोध;
		हाल NFIT_SPA_BDW:
			/* nothing to रेजिस्टर */
			अवरोध;
		हाल NFIT_SPA_DCR:
		हाल NFIT_SPA_VDISK:
		हाल NFIT_SPA_VCD:
		हाल NFIT_SPA_PDISK:
		हाल NFIT_SPA_PCD:
			/* रेजिस्टर known regions that करोn't support ARS */
			rc = acpi_nfit_रेजिस्टर_region(acpi_desc, nfit_spa);
			अगर (rc)
				वापस rc;
			अवरोध;
		शेष:
			/* करोn't रेजिस्टर unknown regions */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (करो_sched_ars)
		sched_ars(acpi_desc);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_nfit_check_deletions(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nfit_table_prev *prev)
अणु
	काष्ठा device *dev = acpi_desc->dev;

	अगर (!list_empty(&prev->spas) ||
			!list_empty(&prev->memdevs) ||
			!list_empty(&prev->dcrs) ||
			!list_empty(&prev->bdws) ||
			!list_empty(&prev->idts) ||
			!list_empty(&prev->flushes)) अणु
		dev_err(dev, "new nfit deletes entries (unsupported)\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_nfit_desc_init_scrub_attr(काष्ठा acpi_nfit_desc *acpi_desc)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा kernfs_node *nfit;
	काष्ठा device *bus_dev;

	अगर (!ars_supported(acpi_desc->nvdimm_bus))
		वापस 0;

	bus_dev = to_nvdimm_bus_dev(acpi_desc->nvdimm_bus);
	nfit = sysfs_get_dirent(bus_dev->kobj.sd, "nfit");
	अगर (!nfit) अणु
		dev_err(dev, "sysfs_get_dirent 'nfit' failed\n");
		वापस -ENODEV;
	पूर्ण
	acpi_desc->scrub_count_state = sysfs_get_dirent(nfit, "scrub");
	sysfs_put(nfit);
	अगर (!acpi_desc->scrub_count_state) अणु
		dev_err(dev, "sysfs_get_dirent 'scrub' failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम acpi_nfit_unरेजिस्टर(व्योम *data)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = data;

	nvdimm_bus_unरेजिस्टर(acpi_desc->nvdimm_bus);
पूर्ण

पूर्णांक acpi_nfit_init(काष्ठा acpi_nfit_desc *acpi_desc, व्योम *data, acpi_size sz)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	काष्ठा nfit_table_prev prev;
	स्थिर व्योम *end;
	पूर्णांक rc;

	अगर (!acpi_desc->nvdimm_bus) अणु
		acpi_nfit_init_dsms(acpi_desc);

		acpi_desc->nvdimm_bus = nvdimm_bus_रेजिस्टर(dev,
				&acpi_desc->nd_desc);
		अगर (!acpi_desc->nvdimm_bus)
			वापस -ENOMEM;

		rc = devm_add_action_or_reset(dev, acpi_nfit_unरेजिस्टर,
				acpi_desc);
		अगर (rc)
			वापस rc;

		rc = acpi_nfit_desc_init_scrub_attr(acpi_desc);
		अगर (rc)
			वापस rc;

		/* रेजिस्टर this acpi_desc क्रम mce notअगरications */
		mutex_lock(&acpi_desc_lock);
		list_add_tail(&acpi_desc->list, &acpi_descs);
		mutex_unlock(&acpi_desc_lock);
	पूर्ण

	mutex_lock(&acpi_desc->init_mutex);

	INIT_LIST_HEAD(&prev.spas);
	INIT_LIST_HEAD(&prev.memdevs);
	INIT_LIST_HEAD(&prev.dcrs);
	INIT_LIST_HEAD(&prev.bdws);
	INIT_LIST_HEAD(&prev.idts);
	INIT_LIST_HEAD(&prev.flushes);

	list_cut_position(&prev.spas, &acpi_desc->spas,
				acpi_desc->spas.prev);
	list_cut_position(&prev.memdevs, &acpi_desc->memdevs,
				acpi_desc->memdevs.prev);
	list_cut_position(&prev.dcrs, &acpi_desc->dcrs,
				acpi_desc->dcrs.prev);
	list_cut_position(&prev.bdws, &acpi_desc->bdws,
				acpi_desc->bdws.prev);
	list_cut_position(&prev.idts, &acpi_desc->idts,
				acpi_desc->idts.prev);
	list_cut_position(&prev.flushes, &acpi_desc->flushes,
				acpi_desc->flushes.prev);

	end = data + sz;
	जबतक (!IS_ERR_OR_शून्य(data))
		data = add_table(acpi_desc, &prev, data, end);

	अगर (IS_ERR(data)) अणु
		dev_dbg(dev, "nfit table parsing error: %ld\n",	PTR_ERR(data));
		rc = PTR_ERR(data);
		जाओ out_unlock;
	पूर्ण

	rc = acpi_nfit_check_deletions(acpi_desc, &prev);
	अगर (rc)
		जाओ out_unlock;

	rc = nfit_mem_init(acpi_desc);
	अगर (rc)
		जाओ out_unlock;

	rc = acpi_nfit_रेजिस्टर_dimms(acpi_desc);
	अगर (rc)
		जाओ out_unlock;

	rc = acpi_nfit_रेजिस्टर_regions(acpi_desc);

 out_unlock:
	mutex_unlock(&acpi_desc->init_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_nfit_init);

अटल पूर्णांक acpi_nfit_flush_probe(काष्ठा nvdimm_bus_descriptor *nd_desc)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	काष्ठा device *dev = acpi_desc->dev;

	/* Bounce the device lock to flush acpi_nfit_add / acpi_nfit_notअगरy */
	nfit_device_lock(dev);
	nfit_device_unlock(dev);

	/* Bounce the init_mutex to complete initial registration */
	mutex_lock(&acpi_desc->init_mutex);
	mutex_unlock(&acpi_desc->init_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __acpi_nfit_clear_to_send(काष्ठा nvdimm_bus_descriptor *nd_desc,
		काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	अगर (nvdimm)
		वापस 0;
	अगर (cmd != ND_CMD_ARS_START)
		वापस 0;

	/*
	 * The kernel and userspace may race to initiate a scrub, but
	 * the scrub thपढ़ो is prepared to lose that initial race.  It
	 * just needs guarantees that any ARS it initiates are not
	 * पूर्णांकerrupted by any पूर्णांकervening start requests from userspace.
	 */
	अगर (work_busy(&acpi_desc->dwork.work))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/*
 * Prevent security and firmware activate commands from being issued via
 * ioctl.
 */
अटल पूर्णांक acpi_nfit_clear_to_send(काष्ठा nvdimm_bus_descriptor *nd_desc,
		काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf)
अणु
	काष्ठा nd_cmd_pkg *call_pkg = buf;
	अचिन्हित पूर्णांक func;

	अगर (nvdimm && cmd == ND_CMD_CALL &&
			call_pkg->nd_family == NVDIMM_FAMILY_INTEL) अणु
		func = call_pkg->nd_command;
		अगर (func > NVDIMM_CMD_MAX ||
		    (1 << func) & NVDIMM_INTEL_DENY_CMDMASK)
			वापस -EOPNOTSUPP;
	पूर्ण

	/* block all non-nfit bus commands */
	अगर (!nvdimm && cmd == ND_CMD_CALL &&
			call_pkg->nd_family != NVDIMM_BUS_FAMILY_NFIT)
		वापस -EOPNOTSUPP;

	वापस __acpi_nfit_clear_to_send(nd_desc, nvdimm, cmd);
पूर्ण

पूर्णांक acpi_nfit_ars_rescan(काष्ठा acpi_nfit_desc *acpi_desc,
		क्रमागत nfit_ars_state req_type)
अणु
	काष्ठा device *dev = acpi_desc->dev;
	पूर्णांक scheduled = 0, busy = 0;
	काष्ठा nfit_spa *nfit_spa;

	mutex_lock(&acpi_desc->init_mutex);
	अगर (test_bit(ARS_CANCEL, &acpi_desc->scrub_flags)) अणु
		mutex_unlock(&acpi_desc->init_mutex);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
		पूर्णांक type = nfit_spa_type(nfit_spa->spa);

		अगर (type != NFIT_SPA_PM && type != NFIT_SPA_VOLATILE)
			जारी;
		अगर (test_bit(ARS_FAILED, &nfit_spa->ars_state))
			जारी;

		अगर (test_and_set_bit(req_type, &nfit_spa->ars_state))
			busy++;
		अन्यथा
			scheduled++;
	पूर्ण
	अगर (scheduled) अणु
		sched_ars(acpi_desc);
		dev_dbg(dev, "ars_scan triggered\n");
	पूर्ण
	mutex_unlock(&acpi_desc->init_mutex);

	अगर (scheduled)
		वापस 0;
	अगर (busy)
		वापस -EBUSY;
	वापस -ENOTTY;
पूर्ण

व्योम acpi_nfit_desc_init(काष्ठा acpi_nfit_desc *acpi_desc, काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc;

	dev_set_drvdata(dev, acpi_desc);
	acpi_desc->dev = dev;
	acpi_desc->blk_करो_io = acpi_nfit_blk_region_करो_io;
	nd_desc = &acpi_desc->nd_desc;
	nd_desc->provider_name = "ACPI.NFIT";
	nd_desc->module = THIS_MODULE;
	nd_desc->ndctl = acpi_nfit_ctl;
	nd_desc->flush_probe = acpi_nfit_flush_probe;
	nd_desc->clear_to_send = acpi_nfit_clear_to_send;
	nd_desc->attr_groups = acpi_nfit_attribute_groups;

	INIT_LIST_HEAD(&acpi_desc->spas);
	INIT_LIST_HEAD(&acpi_desc->dcrs);
	INIT_LIST_HEAD(&acpi_desc->bdws);
	INIT_LIST_HEAD(&acpi_desc->idts);
	INIT_LIST_HEAD(&acpi_desc->flushes);
	INIT_LIST_HEAD(&acpi_desc->memdevs);
	INIT_LIST_HEAD(&acpi_desc->dimms);
	INIT_LIST_HEAD(&acpi_desc->list);
	mutex_init(&acpi_desc->init_mutex);
	acpi_desc->scrub_पंचांगo = 1;
	INIT_DELAYED_WORK(&acpi_desc->dwork, acpi_nfit_scrub);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_nfit_desc_init);

अटल व्योम acpi_nfit_put_table(व्योम *table)
अणु
	acpi_put_table(table);
पूर्ण

व्योम acpi_nfit_shutकरोwn(व्योम *data)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = data;
	काष्ठा device *bus_dev = to_nvdimm_bus_dev(acpi_desc->nvdimm_bus);

	/*
	 * Deकाष्ठा under acpi_desc_lock so that nfit_handle_mce करोes not
	 * race tearकरोwn
	 */
	mutex_lock(&acpi_desc_lock);
	list_del(&acpi_desc->list);
	mutex_unlock(&acpi_desc_lock);

	mutex_lock(&acpi_desc->init_mutex);
	set_bit(ARS_CANCEL, &acpi_desc->scrub_flags);
	cancel_delayed_work_sync(&acpi_desc->dwork);
	mutex_unlock(&acpi_desc->init_mutex);

	/*
	 * Bounce the nvdimm bus lock to make sure any in-flight
	 * acpi_nfit_ars_rescan() submissions have had a chance to
	 * either submit or see ->cancel set.
	 */
	nfit_device_lock(bus_dev);
	nfit_device_unlock(bus_dev);

	flush_workqueue(nfit_wq);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_nfit_shutकरोwn);

अटल पूर्णांक acpi_nfit_add(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_nfit_desc *acpi_desc;
	काष्ठा device *dev = &adev->dev;
	काष्ठा acpi_table_header *tbl;
	acpi_status status = AE_OK;
	acpi_size sz;
	पूर्णांक rc = 0;

	status = acpi_get_table(ACPI_SIG_NFIT, 0, &tbl);
	अगर (ACPI_FAILURE(status)) अणु
		/* The NVDIMM root device allows OS to trigger क्रमागतeration of
		 * NVDIMMs through NFIT at boot समय and re-क्रमागतeration at
		 * root level via the _FIT method during runसमय.
		 * This is ok to वापस 0 here, we could have an nvdimm
		 * hotplugged later and evaluate _FIT method which वापसs
		 * data in the क्रमmat of a series of NFIT Structures.
		 */
		dev_dbg(dev, "failed to find NFIT at startup\n");
		वापस 0;
	पूर्ण

	rc = devm_add_action_or_reset(dev, acpi_nfit_put_table, tbl);
	अगर (rc)
		वापस rc;
	sz = tbl->length;

	acpi_desc = devm_kzalloc(dev, माप(*acpi_desc), GFP_KERNEL);
	अगर (!acpi_desc)
		वापस -ENOMEM;
	acpi_nfit_desc_init(acpi_desc, &adev->dev);

	/* Save the acpi header क्रम exporting the revision via sysfs */
	acpi_desc->acpi_header = *tbl;

	/* Evaluate _FIT and override with that अगर present */
	status = acpi_evaluate_object(adev->handle, "_FIT", शून्य, &buf);
	अगर (ACPI_SUCCESS(status) && buf.length > 0) अणु
		जोड़ acpi_object *obj = buf.poपूर्णांकer;

		अगर (obj->type == ACPI_TYPE_BUFFER)
			rc = acpi_nfit_init(acpi_desc, obj->buffer.poपूर्णांकer,
					obj->buffer.length);
		अन्यथा
			dev_dbg(dev, "invalid type %d, ignoring _FIT\n",
				(पूर्णांक) obj->type);
		kमुक्त(buf.poपूर्णांकer);
	पूर्ण अन्यथा
		/* skip over the lead-in header table */
		rc = acpi_nfit_init(acpi_desc, (व्योम *) tbl
				+ माप(काष्ठा acpi_table_nfit),
				sz - माप(काष्ठा acpi_table_nfit));

	अगर (rc)
		वापस rc;
	वापस devm_add_action_or_reset(dev, acpi_nfit_shutकरोwn, acpi_desc);
पूर्ण

अटल पूर्णांक acpi_nfit_हटाओ(काष्ठा acpi_device *adev)
अणु
	/* see acpi_nfit_unरेजिस्टर */
	वापस 0;
पूर्ण

अटल व्योम acpi_nfit_update_notअगरy(काष्ठा device *dev, acpi_handle handle)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = dev_get_drvdata(dev);
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक ret;

	अगर (!dev->driver) अणु
		/* dev->driver may be null अगर we're being हटाओd */
		dev_dbg(dev, "no driver found for dev\n");
		वापस;
	पूर्ण

	अगर (!acpi_desc) अणु
		acpi_desc = devm_kzalloc(dev, माप(*acpi_desc), GFP_KERNEL);
		अगर (!acpi_desc)
			वापस;
		acpi_nfit_desc_init(acpi_desc, dev);
	पूर्ण अन्यथा अणु
		/*
		 * Finish previous registration beक्रमe considering new
		 * regions.
		 */
		flush_workqueue(nfit_wq);
	पूर्ण

	/* Evaluate _FIT */
	status = acpi_evaluate_object(handle, "_FIT", शून्य, &buf);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "failed to evaluate _FIT\n");
		वापस;
	पूर्ण

	obj = buf.poपूर्णांकer;
	अगर (obj->type == ACPI_TYPE_BUFFER) अणु
		ret = acpi_nfit_init(acpi_desc, obj->buffer.poपूर्णांकer,
				obj->buffer.length);
		अगर (ret)
			dev_err(dev, "failed to merge updated NFIT\n");
	पूर्ण अन्यथा
		dev_err(dev, "Invalid _FIT\n");
	kमुक्त(buf.poपूर्णांकer);
पूर्ण

अटल व्योम acpi_nfit_uc_error_notअगरy(काष्ठा device *dev, acpi_handle handle)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = dev_get_drvdata(dev);

	अगर (acpi_desc->scrub_mode == HW_ERROR_SCRUB_ON)
		acpi_nfit_ars_rescan(acpi_desc, ARS_REQ_LONG);
	अन्यथा
		acpi_nfit_ars_rescan(acpi_desc, ARS_REQ_SHORT);
पूर्ण

व्योम __acpi_nfit_notअगरy(काष्ठा device *dev, acpi_handle handle, u32 event)
अणु
	dev_dbg(dev, "event: 0x%x\n", event);

	चयन (event) अणु
	हाल NFIT_NOTIFY_UPDATE:
		वापस acpi_nfit_update_notअगरy(dev, handle);
	हाल NFIT_NOTIFY_UC_MEMORY_ERROR:
		वापस acpi_nfit_uc_error_notअगरy(dev, handle);
	शेष:
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__acpi_nfit_notअगरy);

अटल व्योम acpi_nfit_notअगरy(काष्ठा acpi_device *adev, u32 event)
अणु
	nfit_device_lock(&adev->dev);
	__acpi_nfit_notअगरy(&adev->dev, adev->handle, event);
	nfit_device_unlock(&adev->dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id acpi_nfit_ids[] = अणु
	अणु "ACPI0012", 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_nfit_ids);

अटल काष्ठा acpi_driver acpi_nfit_driver = अणु
	.name = KBUILD_MODNAME,
	.ids = acpi_nfit_ids,
	.ops = अणु
		.add = acpi_nfit_add,
		.हटाओ = acpi_nfit_हटाओ,
		.notअगरy = acpi_nfit_notअगरy,
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक nfit_init(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा acpi_table_nfit) != 40);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_प्रणाली_address) != 64);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_memory_map) != 48);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_पूर्णांकerleave) != 20);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_smbios) != 9);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_control_region) != 80);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_data_region) != 40);
	BUILD_BUG_ON(माप(काष्ठा acpi_nfit_capabilities) != 16);

	guid_parse(UUID_VOLATILE_MEMORY, &nfit_uuid[NFIT_SPA_VOLATILE]);
	guid_parse(UUID_PERSISTENT_MEMORY, &nfit_uuid[NFIT_SPA_PM]);
	guid_parse(UUID_CONTROL_REGION, &nfit_uuid[NFIT_SPA_DCR]);
	guid_parse(UUID_DATA_REGION, &nfit_uuid[NFIT_SPA_BDW]);
	guid_parse(UUID_VOLATILE_VIRTUAL_DISK, &nfit_uuid[NFIT_SPA_VDISK]);
	guid_parse(UUID_VOLATILE_VIRTUAL_CD, &nfit_uuid[NFIT_SPA_VCD]);
	guid_parse(UUID_PERSISTENT_VIRTUAL_DISK, &nfit_uuid[NFIT_SPA_PDISK]);
	guid_parse(UUID_PERSISTENT_VIRTUAL_CD, &nfit_uuid[NFIT_SPA_PCD]);
	guid_parse(UUID_NFIT_BUS, &nfit_uuid[NFIT_DEV_BUS]);
	guid_parse(UUID_NFIT_DIMM, &nfit_uuid[NFIT_DEV_DIMM]);
	guid_parse(UUID_NFIT_DIMM_N_HPE1, &nfit_uuid[NFIT_DEV_DIMM_N_HPE1]);
	guid_parse(UUID_NFIT_DIMM_N_HPE2, &nfit_uuid[NFIT_DEV_DIMM_N_HPE2]);
	guid_parse(UUID_NFIT_DIMM_N_MSFT, &nfit_uuid[NFIT_DEV_DIMM_N_MSFT]);
	guid_parse(UUID_NFIT_DIMM_N_HYPERV, &nfit_uuid[NFIT_DEV_DIMM_N_HYPERV]);
	guid_parse(UUID_INTEL_BUS, &nfit_uuid[NFIT_BUS_INTEL]);

	nfit_wq = create_singlethपढ़ो_workqueue("nfit");
	अगर (!nfit_wq)
		वापस -ENOMEM;

	nfit_mce_रेजिस्टर();
	ret = acpi_bus_रेजिस्टर_driver(&acpi_nfit_driver);
	अगर (ret) अणु
		nfit_mce_unरेजिस्टर();
		destroy_workqueue(nfit_wq);
	पूर्ण

	वापस ret;

पूर्ण

अटल __निकास व्योम nfit_निकास(व्योम)
अणु
	nfit_mce_unरेजिस्टर();
	acpi_bus_unरेजिस्टर_driver(&acpi_nfit_driver);
	destroy_workqueue(nfit_wq);
	WARN_ON(!list_empty(&acpi_descs));
पूर्ण

module_init(nfit_init);
module_निकास(nfit_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
