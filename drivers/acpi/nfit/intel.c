<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2018 Intel Corporation. All rights reserved. */
#समावेश <linux/libnvdimm.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/smp.h>
#समावेश "intel.h"
#समावेश "nfit.h"

अटल sमाप_प्रकार firmware_activate_noidle_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	वापस प्र_लिखो(buf, "%s\n", acpi_desc->fwa_noidle ? "Y" : "N");
पूर्ण

अटल sमाप_प्रकार firmware_activate_noidle_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	sमाप_प्रकार rc;
	bool val;

	rc = kstrtobool(buf, &val);
	अगर (rc)
		वापस rc;
	अगर (val != acpi_desc->fwa_noidle)
		acpi_desc->fwa_cap = NVDIMM_FWA_CAP_INVALID;
	acpi_desc->fwa_noidle = val;
	वापस size;
पूर्ण
DEVICE_ATTR_RW(firmware_activate_noidle);

bool पूर्णांकel_fwa_supported(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	अचिन्हित दीर्घ *mask;

	अगर (!test_bit(NVDIMM_BUS_FAMILY_INTEL, &nd_desc->bus_family_mask))
		वापस false;

	mask = &acpi_desc->family_dsm_mask[NVDIMM_BUS_FAMILY_INTEL];
	वापस *mask == NVDIMM_BUS_INTEL_FW_ACTIVATE_CMDMASK;
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकel_security_flags(काष्ठा nvdimm *nvdimm,
		क्रमागत nvdimm_passphrase_type ptype)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	अचिन्हित दीर्घ security_flags = 0;
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_get_security_state cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_GET_SECURITY_STATE,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_out =
				माप(काष्ठा nd_पूर्णांकel_get_security_state),
			.nd_fw_size =
				माप(काष्ठा nd_पूर्णांकel_get_security_state),
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	अगर (!test_bit(NVDIMM_INTEL_GET_SECURITY_STATE, &nfit_mem->dsm_mask))
		वापस 0;

	/*
	 * Short circuit the state retrieval जबतक we are करोing overग_लिखो.
	 * The DSM spec states that the security state is indeterminate
	 * until the overग_लिखो DSM completes.
	 */
	अगर (nvdimm_in_overग_लिखो(nvdimm) && ptype == NVDIMM_USER)
		वापस BIT(NVDIMM_SECURITY_OVERWRITE);

	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0 || nd_cmd.cmd.status) अणु
		pr_err("%s: security state retrieval failed (%d:%#x)\n",
				nvdimm_name(nvdimm), rc, nd_cmd.cmd.status);
		वापस 0;
	पूर्ण

	/* check and see अगर security is enabled and locked */
	अगर (ptype == NVDIMM_MASTER) अणु
		अगर (nd_cmd.cmd.extended_state & ND_INTEL_SEC_ESTATE_ENABLED)
			set_bit(NVDIMM_SECURITY_UNLOCKED, &security_flags);
		अन्यथा
			set_bit(NVDIMM_SECURITY_DISABLED, &security_flags);
		अगर (nd_cmd.cmd.extended_state & ND_INTEL_SEC_ESTATE_PLIMIT)
			set_bit(NVDIMM_SECURITY_FROZEN, &security_flags);
		वापस security_flags;
	पूर्ण

	अगर (nd_cmd.cmd.state & ND_INTEL_SEC_STATE_UNSUPPORTED)
		वापस 0;

	अगर (nd_cmd.cmd.state & ND_INTEL_SEC_STATE_ENABLED) अणु
		अगर (nd_cmd.cmd.state & ND_INTEL_SEC_STATE_FROZEN ||
		    nd_cmd.cmd.state & ND_INTEL_SEC_STATE_PLIMIT)
			set_bit(NVDIMM_SECURITY_FROZEN, &security_flags);

		अगर (nd_cmd.cmd.state & ND_INTEL_SEC_STATE_LOCKED)
			set_bit(NVDIMM_SECURITY_LOCKED, &security_flags);
		अन्यथा
			set_bit(NVDIMM_SECURITY_UNLOCKED, &security_flags);
	पूर्ण अन्यथा
		set_bit(NVDIMM_SECURITY_DISABLED, &security_flags);

	वापस security_flags;
पूर्ण

अटल पूर्णांक पूर्णांकel_security_मुक्तze(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_मुक्तze_lock cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_FREEZE_LOCK,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	अगर (!test_bit(NVDIMM_INTEL_FREEZE_LOCK, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;
	अगर (nd_cmd.cmd.status)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_security_change_key(काष्ठा nvdimm *nvdimm,
		स्थिर काष्ठा nvdimm_key_data *old_data,
		स्थिर काष्ठा nvdimm_key_data *new_data,
		क्रमागत nvdimm_passphrase_type ptype)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	अचिन्हित पूर्णांक cmd = ptype == NVDIMM_MASTER ?
		NVDIMM_INTEL_SET_MASTER_PASSPHRASE :
		NVDIMM_INTEL_SET_PASSPHRASE;
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_set_passphrase cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_in = ND_INTEL_PASSPHRASE_SIZE * 2,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
			.nd_command = cmd,
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	अगर (!test_bit(cmd, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	स_नकल(nd_cmd.cmd.old_pass, old_data->data,
			माप(nd_cmd.cmd.old_pass));
	स_नकल(nd_cmd.cmd.new_pass, new_data->data,
			माप(nd_cmd.cmd.new_pass));
	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;

	चयन (nd_cmd.cmd.status) अणु
	हाल 0:
		वापस 0;
	हाल ND_INTEL_STATUS_INVALID_PASS:
		वापस -EINVAL;
	हाल ND_INTEL_STATUS_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	हाल ND_INTEL_STATUS_INVALID_STATE:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम nvdimm_invalidate_cache(व्योम);

अटल पूर्णांक __maybe_unused पूर्णांकel_security_unlock(काष्ठा nvdimm *nvdimm,
		स्थिर काष्ठा nvdimm_key_data *key_data)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_unlock_unit cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_UNLOCK_UNIT,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_in = ND_INTEL_PASSPHRASE_SIZE,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	अगर (!test_bit(NVDIMM_INTEL_UNLOCK_UNIT, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	स_नकल(nd_cmd.cmd.passphrase, key_data->data,
			माप(nd_cmd.cmd.passphrase));
	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;
	चयन (nd_cmd.cmd.status) अणु
	हाल 0:
		अवरोध;
	हाल ND_INTEL_STATUS_INVALID_PASS:
		वापस -EINVAL;
	शेष:
		वापस -EIO;
	पूर्ण

	/* DIMM unlocked, invalidate all CPU caches beक्रमe we पढ़ो it */
	nvdimm_invalidate_cache();

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_security_disable(काष्ठा nvdimm *nvdimm,
		स्थिर काष्ठा nvdimm_key_data *key_data)
अणु
	पूर्णांक rc;
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_disable_passphrase cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_DISABLE_PASSPHRASE,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_in = ND_INTEL_PASSPHRASE_SIZE,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
		पूर्ण,
	पूर्ण;

	अगर (!test_bit(NVDIMM_INTEL_DISABLE_PASSPHRASE, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	स_नकल(nd_cmd.cmd.passphrase, key_data->data,
			माप(nd_cmd.cmd.passphrase));
	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;

	चयन (nd_cmd.cmd.status) अणु
	हाल 0:
		अवरोध;
	हाल ND_INTEL_STATUS_INVALID_PASS:
		वापस -EINVAL;
	हाल ND_INTEL_STATUS_INVALID_STATE:
	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_security_erase(काष्ठा nvdimm *nvdimm,
		स्थिर काष्ठा nvdimm_key_data *key,
		क्रमागत nvdimm_passphrase_type ptype)
अणु
	पूर्णांक rc;
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	अचिन्हित पूर्णांक cmd = ptype == NVDIMM_MASTER ?
		NVDIMM_INTEL_MASTER_SECURE_ERASE : NVDIMM_INTEL_SECURE_ERASE;
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_secure_erase cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_in = ND_INTEL_PASSPHRASE_SIZE,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
			.nd_command = cmd,
		पूर्ण,
	पूर्ण;

	अगर (!test_bit(cmd, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	/* flush all cache beक्रमe we erase DIMM */
	nvdimm_invalidate_cache();
	स_नकल(nd_cmd.cmd.passphrase, key->data,
			माप(nd_cmd.cmd.passphrase));
	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;

	चयन (nd_cmd.cmd.status) अणु
	हाल 0:
		अवरोध;
	हाल ND_INTEL_STATUS_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	हाल ND_INTEL_STATUS_INVALID_PASS:
		वापस -EINVAL;
	हाल ND_INTEL_STATUS_INVALID_STATE:
	शेष:
		वापस -ENXIO;
	पूर्ण

	/* DIMM erased, invalidate all CPU caches beक्रमe we पढ़ो it */
	nvdimm_invalidate_cache();
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_security_query_overग_लिखो(काष्ठा nvdimm *nvdimm)
अणु
	पूर्णांक rc;
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_query_overग_लिखो cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_QUERY_OVERWRITE,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
		पूर्ण,
	पूर्ण;

	अगर (!test_bit(NVDIMM_INTEL_QUERY_OVERWRITE, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;

	चयन (nd_cmd.cmd.status) अणु
	हाल 0:
		अवरोध;
	हाल ND_INTEL_STATUS_OQUERY_INPROGRESS:
		वापस -EBUSY;
	शेष:
		वापस -ENXIO;
	पूर्ण

	/* flush all cache beक्रमe we make the nvdimms available */
	nvdimm_invalidate_cache();
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_security_overग_लिखो(काष्ठा nvdimm *nvdimm,
		स्थिर काष्ठा nvdimm_key_data *nkey)
अणु
	पूर्णांक rc;
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_overग_लिखो cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_OVERWRITE,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_in = ND_INTEL_PASSPHRASE_SIZE,
			.nd_size_out = ND_INTEL_STATUS_SIZE,
			.nd_fw_size = ND_INTEL_STATUS_SIZE,
		पूर्ण,
	पूर्ण;

	अगर (!test_bit(NVDIMM_INTEL_OVERWRITE, &nfit_mem->dsm_mask))
		वापस -ENOTTY;

	/* flush all cache beक्रमe we erase DIMM */
	nvdimm_invalidate_cache();
	स_नकल(nd_cmd.cmd.passphrase, nkey->data,
			माप(nd_cmd.cmd.passphrase));
	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	अगर (rc < 0)
		वापस rc;

	चयन (nd_cmd.cmd.status) अणु
	हाल 0:
		वापस 0;
	हाल ND_INTEL_STATUS_OVERWRITE_UNSUPPORTED:
		वापस -ENOTSUPP;
	हाल ND_INTEL_STATUS_INVALID_PASS:
		वापस -EINVAL;
	हाल ND_INTEL_STATUS_INVALID_STATE:
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण

/*
 * TODO: define a cross arch wbinvd equivalent when/अगर
 * NVDIMM_FAMILY_INTEL command support arrives on another arch.
 */
#अगर_घोषित CONFIG_X86
अटल व्योम nvdimm_invalidate_cache(व्योम)
अणु
	wbinvd_on_all_cpus();
पूर्ण
#अन्यथा
अटल व्योम nvdimm_invalidate_cache(व्योम)
अणु
	WARN_ON_ONCE("cache invalidation required after unlock\n");
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा nvdimm_security_ops __पूर्णांकel_security_ops = अणु
	.get_flags = पूर्णांकel_security_flags,
	.मुक्तze = पूर्णांकel_security_मुक्तze,
	.change_key = पूर्णांकel_security_change_key,
	.disable = पूर्णांकel_security_disable,
#अगर_घोषित CONFIG_X86
	.unlock = पूर्णांकel_security_unlock,
	.erase = पूर्णांकel_security_erase,
	.overग_लिखो = पूर्णांकel_security_overग_लिखो,
	.query_overग_लिखो = पूर्णांकel_security_query_overग_लिखो,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा nvdimm_security_ops *पूर्णांकel_security_ops = &__पूर्णांकel_security_ops;

अटल पूर्णांक पूर्णांकel_bus_fwa_businfo(काष्ठा nvdimm_bus_descriptor *nd_desc,
		काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo *info)
अणु
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_BUS_INTEL_FW_ACTIVATE_BUSINFO,
			.nd_family = NVDIMM_BUS_FAMILY_INTEL,
			.nd_size_out =
				माप(काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo),
			.nd_fw_size =
				माप(काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo),
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_CALL, &nd_cmd, माप(nd_cmd),
			शून्य);
	*info = nd_cmd.cmd;
	वापस rc;
पूर्ण

/* The fw_ops expect to be called with the nvdimm_bus_lock() held */
अटल क्रमागत nvdimm_fwa_state पूर्णांकel_bus_fwa_state(
		काष्ठा nvdimm_bus_descriptor *nd_desc)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo info;
	काष्ठा device *dev = acpi_desc->dev;
	क्रमागत nvdimm_fwa_state state;
	पूर्णांक rc;

	/*
	 * It should not be possible क्रम platक्रमm firmware to वापस
	 * busy because activate is a synchronous operation. Treat it
	 * similar to invalid, i.e. always refresh / poll the status.
	 */
	चयन (acpi_desc->fwa_state) अणु
	हाल NVDIMM_FWA_INVALID:
	हाल NVDIMM_FWA_BUSY:
		अवरोध;
	शेष:
		/* check अगर capability needs to be refreshed */
		अगर (acpi_desc->fwa_cap == NVDIMM_FWA_CAP_INVALID)
			अवरोध;
		वापस acpi_desc->fwa_state;
	पूर्ण

	/* Refresh with platक्रमm firmware */
	rc = पूर्णांकel_bus_fwa_businfo(nd_desc, &info);
	अगर (rc)
		वापस NVDIMM_FWA_INVALID;

	चयन (info.state) अणु
	हाल ND_INTEL_FWA_IDLE:
		state = NVDIMM_FWA_IDLE;
		अवरोध;
	हाल ND_INTEL_FWA_BUSY:
		state = NVDIMM_FWA_BUSY;
		अवरोध;
	हाल ND_INTEL_FWA_ARMED:
		अगर (info.activate_पंचांगo > info.max_quiesce_पंचांगo)
			state = NVDIMM_FWA_ARM_OVERFLOW;
		अन्यथा
			state = NVDIMM_FWA_ARMED;
		अवरोध;
	शेष:
		dev_err_once(dev, "invalid firmware activate state %d\n",
				info.state);
		वापस NVDIMM_FWA_INVALID;
	पूर्ण

	/*
	 * Capability data is available in the same payload as state. It
	 * is expected to be अटल.
	 */
	अगर (acpi_desc->fwa_cap == NVDIMM_FWA_CAP_INVALID) अणु
		अगर (info.capability & ND_INTEL_BUS_FWA_CAP_FWQUIESCE)
			acpi_desc->fwa_cap = NVDIMM_FWA_CAP_QUIESCE;
		अन्यथा अगर (info.capability & ND_INTEL_BUS_FWA_CAP_OSQUIESCE) अणु
			/*
			 * Skip hibernate cycle by शेष अगर platक्रमm
			 * indicates that it करोes not need devices to be
			 * quiesced.
			 */
			acpi_desc->fwa_cap = NVDIMM_FWA_CAP_LIVE;
		पूर्ण अन्यथा
			acpi_desc->fwa_cap = NVDIMM_FWA_CAP_NONE;
	पूर्ण

	acpi_desc->fwa_state = state;

	वापस state;
पूर्ण

अटल क्रमागत nvdimm_fwa_capability पूर्णांकel_bus_fwa_capability(
		काष्ठा nvdimm_bus_descriptor *nd_desc)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	अगर (acpi_desc->fwa_cap > NVDIMM_FWA_CAP_INVALID)
		वापस acpi_desc->fwa_cap;

	अगर (पूर्णांकel_bus_fwa_state(nd_desc) > NVDIMM_FWA_INVALID)
		वापस acpi_desc->fwa_cap;

	वापस NVDIMM_FWA_CAP_INVALID;
पूर्ण

अटल पूर्णांक पूर्णांकel_bus_fwa_activate(काष्ठा nvdimm_bus_descriptor *nd_desc)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_bus_fw_activate cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_BUS_INTEL_FW_ACTIVATE,
			.nd_family = NVDIMM_BUS_FAMILY_INTEL,
			.nd_size_in = माप(nd_cmd.cmd.iodev_state),
			.nd_size_out =
				माप(काष्ठा nd_पूर्णांकel_bus_fw_activate),
			.nd_fw_size =
				माप(काष्ठा nd_पूर्णांकel_bus_fw_activate),
		पूर्ण,
		/*
		 * Even though activate is run from a suspended context,
		 * क्रम safety, still ask platक्रमm firmware to क्रमce
		 * quiesce devices by शेष. Let a module
		 * parameter override that policy.
		 */
		.cmd = अणु
			.iodev_state = acpi_desc->fwa_noidle
				? ND_INTEL_BUS_FWA_IODEV_OS_IDLE
				: ND_INTEL_BUS_FWA_IODEV_FORCE_IDLE,
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	चयन (पूर्णांकel_bus_fwa_state(nd_desc)) अणु
	हाल NVDIMM_FWA_ARMED:
	हाल NVDIMM_FWA_ARM_OVERFLOW:
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_CALL, &nd_cmd, माप(nd_cmd),
			शून्य);

	/*
	 * Whether the command succeeded, or failed, the agent checking
	 * क्रम the result needs to query the DIMMs inभागidually.
	 * Increment the activation count to invalidate all the DIMM
	 * states at once (it's otherwise not possible to take
	 * acpi_desc->init_mutex in this context)
	 */
	acpi_desc->fwa_state = NVDIMM_FWA_INVALID;
	acpi_desc->fwa_count++;

	dev_dbg(acpi_desc->dev, "result: %d\n", rc);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा nvdimm_bus_fw_ops __पूर्णांकel_bus_fw_ops = अणु
	.activate_state = पूर्णांकel_bus_fwa_state,
	.capability = पूर्णांकel_bus_fwa_capability,
	.activate = पूर्णांकel_bus_fwa_activate,
पूर्ण;

स्थिर काष्ठा nvdimm_bus_fw_ops *पूर्णांकel_bus_fw_ops = &__पूर्णांकel_bus_fw_ops;

अटल पूर्णांक पूर्णांकel_fwa_dimminfo(काष्ठा nvdimm *nvdimm,
		काष्ठा nd_पूर्णांकel_fw_activate_dimminfo *info)
अणु
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_fw_activate_dimminfo cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_FW_ACTIVATE_DIMMINFO,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_out =
				माप(काष्ठा nd_पूर्णांकel_fw_activate_dimminfo),
			.nd_fw_size =
				माप(काष्ठा nd_पूर्णांकel_fw_activate_dimminfo),
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);
	*info = nd_cmd.cmd;
	वापस rc;
पूर्ण

अटल क्रमागत nvdimm_fwa_state पूर्णांकel_fwa_state(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;
	काष्ठा nd_पूर्णांकel_fw_activate_dimminfo info;
	पूर्णांक rc;

	/*
	 * Similar to the bus state, since activate is synchronous the
	 * busy state should resolve within the context of 'activate'.
	 */
	चयन (nfit_mem->fwa_state) अणु
	हाल NVDIMM_FWA_INVALID:
	हाल NVDIMM_FWA_BUSY:
		अवरोध;
	शेष:
		/* If no activations occurred the old state is still valid */
		अगर (nfit_mem->fwa_count == acpi_desc->fwa_count)
			वापस nfit_mem->fwa_state;
	पूर्ण

	rc = पूर्णांकel_fwa_dimminfo(nvdimm, &info);
	अगर (rc)
		वापस NVDIMM_FWA_INVALID;

	चयन (info.state) अणु
	हाल ND_INTEL_FWA_IDLE:
		nfit_mem->fwa_state = NVDIMM_FWA_IDLE;
		अवरोध;
	हाल ND_INTEL_FWA_BUSY:
		nfit_mem->fwa_state = NVDIMM_FWA_BUSY;
		अवरोध;
	हाल ND_INTEL_FWA_ARMED:
		nfit_mem->fwa_state = NVDIMM_FWA_ARMED;
		अवरोध;
	शेष:
		nfit_mem->fwa_state = NVDIMM_FWA_INVALID;
		अवरोध;
	पूर्ण

	चयन (info.result) अणु
	हाल ND_INTEL_DIMM_FWA_NONE:
		nfit_mem->fwa_result = NVDIMM_FWA_RESULT_NONE;
		अवरोध;
	हाल ND_INTEL_DIMM_FWA_SUCCESS:
		nfit_mem->fwa_result = NVDIMM_FWA_RESULT_SUCCESS;
		अवरोध;
	हाल ND_INTEL_DIMM_FWA_NOTSTAGED:
		nfit_mem->fwa_result = NVDIMM_FWA_RESULT_NOTSTAGED;
		अवरोध;
	हाल ND_INTEL_DIMM_FWA_NEEDRESET:
		nfit_mem->fwa_result = NVDIMM_FWA_RESULT_NEEDRESET;
		अवरोध;
	हाल ND_INTEL_DIMM_FWA_MEDIAFAILED:
	हाल ND_INTEL_DIMM_FWA_ABORT:
	हाल ND_INTEL_DIMM_FWA_NOTSUPP:
	हाल ND_INTEL_DIMM_FWA_ERROR:
	शेष:
		nfit_mem->fwa_result = NVDIMM_FWA_RESULT_FAIL;
		अवरोध;
	पूर्ण

	nfit_mem->fwa_count = acpi_desc->fwa_count;

	वापस nfit_mem->fwa_state;
पूर्ण

अटल क्रमागत nvdimm_fwa_result पूर्णांकel_fwa_result(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;

	अगर (nfit_mem->fwa_count == acpi_desc->fwa_count
			&& nfit_mem->fwa_result > NVDIMM_FWA_RESULT_INVALID)
		वापस nfit_mem->fwa_result;

	अगर (पूर्णांकel_fwa_state(nvdimm) > NVDIMM_FWA_INVALID)
		वापस nfit_mem->fwa_result;

	वापस NVDIMM_FWA_RESULT_INVALID;
पूर्ण

अटल पूर्णांक पूर्णांकel_fwa_arm(काष्ठा nvdimm *nvdimm, क्रमागत nvdimm_fwa_trigger arm)
अणु
	काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
	काष्ठा acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;
	काष्ठा अणु
		काष्ठा nd_cmd_pkg pkg;
		काष्ठा nd_पूर्णांकel_fw_activate_arm cmd;
	पूर्ण nd_cmd = अणु
		.pkg = अणु
			.nd_command = NVDIMM_INTEL_FW_ACTIVATE_ARM,
			.nd_family = NVDIMM_FAMILY_INTEL,
			.nd_size_in = माप(nd_cmd.cmd.activate_arm),
			.nd_size_out =
				माप(काष्ठा nd_पूर्णांकel_fw_activate_arm),
			.nd_fw_size =
				माप(काष्ठा nd_पूर्णांकel_fw_activate_arm),
		पूर्ण,
		.cmd = अणु
			.activate_arm = arm == NVDIMM_FWA_ARM
				? ND_INTEL_DIMM_FWA_ARM
				: ND_INTEL_DIMM_FWA_DISARM,
		पूर्ण,
	पूर्ण;
	पूर्णांक rc;

	चयन (पूर्णांकel_fwa_state(nvdimm)) अणु
	हाल NVDIMM_FWA_INVALID:
		वापस -ENXIO;
	हाल NVDIMM_FWA_BUSY:
		वापस -EBUSY;
	हाल NVDIMM_FWA_IDLE:
		अगर (arm == NVDIMM_FWA_DISARM)
			वापस 0;
		अवरोध;
	हाल NVDIMM_FWA_ARMED:
		अगर (arm == NVDIMM_FWA_ARM)
			वापस 0;
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	/*
	 * Invalidate the bus-level state, now that we're committed to
	 * changing the 'arm' state.
	 */
	acpi_desc->fwa_state = NVDIMM_FWA_INVALID;
	nfit_mem->fwa_state = NVDIMM_FWA_INVALID;

	rc = nvdimm_ctl(nvdimm, ND_CMD_CALL, &nd_cmd, माप(nd_cmd), शून्य);

	dev_dbg(acpi_desc->dev, "%s result: %d\n", arm == NVDIMM_FWA_ARM
			? "arm" : "disarm", rc);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा nvdimm_fw_ops __पूर्णांकel_fw_ops = अणु
	.activate_state = पूर्णांकel_fwa_state,
	.activate_result = पूर्णांकel_fwa_result,
	.arm = पूर्णांकel_fwa_arm,
पूर्ण;

स्थिर काष्ठा nvdimm_fw_ops *पूर्णांकel_fw_ops = &__पूर्णांकel_fw_ops;
