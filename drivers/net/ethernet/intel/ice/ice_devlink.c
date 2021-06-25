<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Intel Corporation. */

#समावेश "ice.h"
#समावेश "ice_lib.h"
#समावेश "ice_devlink.h"
#समावेश "ice_fw_update.h"

/* context क्रम devlink info version reporting */
काष्ठा ice_info_ctx अणु
	अक्षर buf[128];
	काष्ठा ice_orom_info pending_orom;
	काष्ठा ice_nvm_info pending_nvm;
	काष्ठा ice_netlist_info pending_netlist;
	काष्ठा ice_hw_dev_caps dev_caps;
पूर्ण;

/* The following functions are used to क्रमmat specअगरic strings क्रम various
 * devlink info versions. The ctx parameter is used to provide the storage
 * buffer, as well as any ancillary inक्रमmation calculated when the info
 * request was made.
 *
 * If a version करोes not exist, क्रम example when attempting to get the
 * inactive version of flash when there is no pending update, the function
 * should leave the buffer in the ctx काष्ठाure empty and वापस 0.
 */

अटल व्योम ice_info_get_dsn(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	u8 dsn[8];

	/* Copy the DSN पूर्णांकo an array in Big Endian क्रमmat */
	put_unaligned_be64(pci_get_dsn(pf->pdev), dsn);

	snम_लिखो(ctx->buf, माप(ctx->buf), "%8phD", dsn);
पूर्ण

अटल पूर्णांक ice_info_pba(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;

	status = ice_पढ़ो_pba_string(hw, (u8 *)ctx->buf, माप(ctx->buf));
	अगर (status)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_fw_mgmt(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	snम_लिखो(ctx->buf, माप(ctx->buf), "%u.%u.%u", hw->fw_maj_ver, hw->fw_min_ver,
		 hw->fw_patch);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_fw_api(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	snम_लिखो(ctx->buf, माप(ctx->buf), "%u.%u", hw->api_maj_ver, hw->api_min_ver);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_fw_build(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	snम_लिखो(ctx->buf, माप(ctx->buf), "0x%08x", hw->fw_build);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_orom_ver(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_orom_info *orom = &pf->hw.flash.orom;

	snम_लिखो(ctx->buf, माप(ctx->buf), "%u.%u.%u", orom->major, orom->build, orom->patch);

	वापस 0;
पूर्ण

अटल पूर्णांक
ice_info_pending_orom_ver(काष्ठा ice_pf __always_unused *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_orom_info *orom = &ctx->pending_orom;

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_orom)
		snम_लिखो(ctx->buf, माप(ctx->buf), "%u.%u.%u",
			 orom->major, orom->build, orom->patch);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_nvm_ver(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_nvm_info *nvm = &pf->hw.flash.nvm;

	snम_लिखो(ctx->buf, माप(ctx->buf), "%x.%02x", nvm->major, nvm->minor);

	वापस 0;
पूर्ण

अटल पूर्णांक
ice_info_pending_nvm_ver(काष्ठा ice_pf __always_unused *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_nvm_info *nvm = &ctx->pending_nvm;

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_nvm)
		snम_लिखो(ctx->buf, माप(ctx->buf), "%x.%02x", nvm->major, nvm->minor);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_eetrack(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_nvm_info *nvm = &pf->hw.flash.nvm;

	snम_लिखो(ctx->buf, माप(ctx->buf), "0x%08x", nvm->eetrack);

	वापस 0;
पूर्ण

अटल पूर्णांक
ice_info_pending_eetrack(काष्ठा ice_pf __always_unused *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_nvm_info *nvm = &ctx->pending_nvm;

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_nvm)
		snम_लिखो(ctx->buf, माप(ctx->buf), "0x%08x", nvm->eetrack);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_ddp_pkg_name(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_hw *hw = &pf->hw;

	snम_लिखो(ctx->buf, माप(ctx->buf), "%s", hw->active_pkg_name);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_ddp_pkg_version(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_pkg_ver *pkg = &pf->hw.active_pkg_ver;

	snम_लिखो(ctx->buf, माप(ctx->buf), "%u.%u.%u.%u", pkg->major, pkg->minor, pkg->update,
		 pkg->draft);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_ddp_pkg_bundle_id(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	snम_लिखो(ctx->buf, माप(ctx->buf), "0x%08x", pf->hw.active_track_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_netlist_ver(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_netlist_info *netlist = &pf->hw.flash.netlist;

	/* The netlist version fields are BCD क्रमmatted */
	snम_लिखो(ctx->buf, माप(ctx->buf), "%x.%x.%x-%x.%x.%x", netlist->major, netlist->minor,
		 netlist->type >> 16, netlist->type & 0xFFFF, netlist->rev,
		 netlist->cust_ver);

	वापस 0;
पूर्ण

अटल पूर्णांक ice_info_netlist_build(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_netlist_info *netlist = &pf->hw.flash.netlist;

	snम_लिखो(ctx->buf, माप(ctx->buf), "0x%08x", netlist->hash);

	वापस 0;
पूर्ण

अटल पूर्णांक
ice_info_pending_netlist_ver(काष्ठा ice_pf __always_unused *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_netlist_info *netlist = &ctx->pending_netlist;

	/* The netlist version fields are BCD क्रमmatted */
	अगर (ctx->dev_caps.common_cap.nvm_update_pending_netlist)
		snम_लिखो(ctx->buf, माप(ctx->buf), "%x.%x.%x-%x.%x.%x",
			 netlist->major, netlist->minor,
			 netlist->type >> 16, netlist->type & 0xFFFF, netlist->rev,
			 netlist->cust_ver);

	वापस 0;
पूर्ण

अटल पूर्णांक
ice_info_pending_netlist_build(काष्ठा ice_pf __always_unused *pf, काष्ठा ice_info_ctx *ctx)
अणु
	काष्ठा ice_netlist_info *netlist = &ctx->pending_netlist;

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_netlist)
		snम_लिखो(ctx->buf, माप(ctx->buf), "0x%08x", netlist->hash);

	वापस 0;
पूर्ण

#घोषणा fixed(key, getter) अणु ICE_VERSION_FIXED, key, getter, शून्य पूर्ण
#घोषणा running(key, getter) अणु ICE_VERSION_RUNNING, key, getter, शून्य पूर्ण
#घोषणा stored(key, getter, fallback) अणु ICE_VERSION_STORED, key, getter, fallback पूर्ण

/* The combined() macro inserts both the running entry as well as a stored
 * entry. The running entry will always report the version from the active
 * handler. The stored entry will first try the pending handler, and fallback
 * to the active handler अगर the pending function करोes not report a version.
 * The pending handler should check the status of a pending update क्रम the
 * relevant flash component. It should only fill in the buffer in the हाल
 * where a valid pending version is available. This ensures that the related
 * stored and running versions reमुख्य in sync, and that stored versions are
 * correctly reported as expected.
 */
#घोषणा combined(key, active, pending) \
	running(key, active), \
	stored(key, pending, active)

क्रमागत ice_version_type अणु
	ICE_VERSION_FIXED,
	ICE_VERSION_RUNNING,
	ICE_VERSION_STORED,
पूर्ण;

अटल स्थिर काष्ठा ice_devlink_version अणु
	क्रमागत ice_version_type type;
	स्थिर अक्षर *key;
	पूर्णांक (*getter)(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx);
	पूर्णांक (*fallback)(काष्ठा ice_pf *pf, काष्ठा ice_info_ctx *ctx);
पूर्ण ice_devlink_versions[] = अणु
	fixed(DEVLINK_INFO_VERSION_GENERIC_BOARD_ID, ice_info_pba),
	running(DEVLINK_INFO_VERSION_GENERIC_FW_MGMT, ice_info_fw_mgmt),
	running("fw.mgmt.api", ice_info_fw_api),
	running("fw.mgmt.build", ice_info_fw_build),
	combined(DEVLINK_INFO_VERSION_GENERIC_FW_UNDI, ice_info_orom_ver, ice_info_pending_orom_ver),
	combined("fw.psid.api", ice_info_nvm_ver, ice_info_pending_nvm_ver),
	combined(DEVLINK_INFO_VERSION_GENERIC_FW_BUNDLE_ID, ice_info_eetrack, ice_info_pending_eetrack),
	running("fw.app.name", ice_info_ddp_pkg_name),
	running(DEVLINK_INFO_VERSION_GENERIC_FW_APP, ice_info_ddp_pkg_version),
	running("fw.app.bundle_id", ice_info_ddp_pkg_bundle_id),
	combined("fw.netlist", ice_info_netlist_ver, ice_info_pending_netlist_ver),
	combined("fw.netlist.build", ice_info_netlist_build, ice_info_pending_netlist_build),
पूर्ण;

/**
 * ice_devlink_info_get - .info_get devlink handler
 * @devlink: devlink instance काष्ठाure
 * @req: the devlink info request
 * @extack: extended netdev ack काष्ठाure
 *
 * Callback क्रम the devlink .info_get operation. Reports inक्रमmation about the
 * device.
 *
 * Return: zero on success or an error code on failure.
 */
अटल पूर्णांक ice_devlink_info_get(काष्ठा devlink *devlink,
				काष्ठा devlink_info_req *req,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ice_pf *pf = devlink_priv(devlink);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_info_ctx *ctx;
	क्रमागत ice_status status;
	माप_प्रकार i;
	पूर्णांक err;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	/* discover capabilities first */
	status = ice_discover_dev_caps(hw, &ctx->dev_caps);
	अगर (status) अणु
		err = -EIO;
		जाओ out_मुक्त_ctx;
	पूर्ण

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_orom) अणु
		status = ice_get_inactive_orom_ver(hw, &ctx->pending_orom);
		अगर (status) अणु
			dev_dbg(dev, "Unable to read inactive Option ROM version data, status %s aq_err %s\n",
				ice_stat_str(status), ice_aq_str(hw->adminq.sq_last_status));

			/* disable display of pending Option ROM */
			ctx->dev_caps.common_cap.nvm_update_pending_orom = false;
		पूर्ण
	पूर्ण

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_nvm) अणु
		status = ice_get_inactive_nvm_ver(hw, &ctx->pending_nvm);
		अगर (status) अणु
			dev_dbg(dev, "Unable to read inactive NVM version data, status %s aq_err %s\n",
				ice_stat_str(status), ice_aq_str(hw->adminq.sq_last_status));

			/* disable display of pending Option ROM */
			ctx->dev_caps.common_cap.nvm_update_pending_nvm = false;
		पूर्ण
	पूर्ण

	अगर (ctx->dev_caps.common_cap.nvm_update_pending_netlist) अणु
		status = ice_get_inactive_netlist_ver(hw, &ctx->pending_netlist);
		अगर (status) अणु
			dev_dbg(dev, "Unable to read inactive Netlist version data, status %s aq_err %s\n",
				ice_stat_str(status), ice_aq_str(hw->adminq.sq_last_status));

			/* disable display of pending Option ROM */
			ctx->dev_caps.common_cap.nvm_update_pending_netlist = false;
		पूर्ण
	पूर्ण

	err = devlink_info_driver_name_put(req, KBUILD_MODNAME);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unable to set driver name");
		जाओ out_मुक्त_ctx;
	पूर्ण

	ice_info_get_dsn(pf, ctx);

	err = devlink_info_serial_number_put(req, ctx->buf);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unable to set serial number");
		जाओ out_मुक्त_ctx;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ice_devlink_versions); i++) अणु
		क्रमागत ice_version_type type = ice_devlink_versions[i].type;
		स्थिर अक्षर *key = ice_devlink_versions[i].key;

		स_रखो(ctx->buf, 0, माप(ctx->buf));

		err = ice_devlink_versions[i].getter(pf, ctx);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unable to obtain version info");
			जाओ out_मुक्त_ctx;
		पूर्ण

		/* If the शेष getter करोesn't report a version, use the
		 * fallback function. This is primarily useful in the हाल of
		 * "stored" versions that want to report the same value as the
		 * running version in the normal हाल of no pending update.
		 */
		अगर (ctx->buf[0] == '\0' && ice_devlink_versions[i].fallback) अणु
			err = ice_devlink_versions[i].fallback(pf, ctx);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Unable to obtain version info");
				जाओ out_मुक्त_ctx;
			पूर्ण
		पूर्ण

		/* Do not report missing versions */
		अगर (ctx->buf[0] == '\0')
			जारी;

		चयन (type) अणु
		हाल ICE_VERSION_FIXED:
			err = devlink_info_version_fixed_put(req, key, ctx->buf);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Unable to set fixed version");
				जाओ out_मुक्त_ctx;
			पूर्ण
			अवरोध;
		हाल ICE_VERSION_RUNNING:
			err = devlink_info_version_running_put(req, key, ctx->buf);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Unable to set running version");
				जाओ out_मुक्त_ctx;
			पूर्ण
			अवरोध;
		हाल ICE_VERSION_STORED:
			err = devlink_info_version_stored_put(req, key, ctx->buf);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Unable to set stored version");
				जाओ out_मुक्त_ctx;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

out_मुक्त_ctx:
	kमुक्त(ctx);
	वापस err;
पूर्ण

/**
 * ice_devlink_flash_update - Update firmware stored in flash on the device
 * @devlink: poपूर्णांकer to devlink associated with device to update
 * @params: flash update parameters
 * @extack: netlink extended ACK काष्ठाure
 *
 * Perक्रमm a device flash update. The bulk of the update logic is contained
 * within the ice_flash_pldm_image function.
 *
 * Returns: zero on success, or an error code on failure.
 */
अटल पूर्णांक
ice_devlink_flash_update(काष्ठा devlink *devlink,
			 काष्ठा devlink_flash_update_params *params,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ice_pf *pf = devlink_priv(devlink);
	काष्ठा ice_hw *hw = &pf->hw;
	u8 preservation;
	पूर्णांक err;

	अगर (!params->overग_लिखो_mask) अणु
		/* preserve all settings and identअगरiers */
		preservation = ICE_AQC_NVM_PRESERVE_ALL;
	पूर्ण अन्यथा अगर (params->overग_लिखो_mask == DEVLINK_FLASH_OVERWRITE_SETTINGS) अणु
		/* overग_लिखो settings, but preserve the vital device identअगरiers */
		preservation = ICE_AQC_NVM_PRESERVE_SELECTED;
	पूर्ण अन्यथा अगर (params->overग_लिखो_mask == (DEVLINK_FLASH_OVERWRITE_SETTINGS |
					      DEVLINK_FLASH_OVERWRITE_IDENTIFIERS)) अणु
		/* overग_लिखो both settings and identअगरiers, preserve nothing */
		preservation = ICE_AQC_NVM_NO_PRESERVATION;
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Requested overwrite mask is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!hw->dev_caps.common_cap.nvm_unअगरied_update) अणु
		NL_SET_ERR_MSG_MOD(extack, "Current firmware does not support unified update");
		वापस -EOPNOTSUPP;
	पूर्ण

	err = ice_check_क्रम_pending_update(pf, शून्य, extack);
	अगर (err)
		वापस err;

	devlink_flash_update_status_notअगरy(devlink, "Preparing to flash", शून्य, 0, 0);

	वापस ice_flash_pldm_image(pf, params->fw, preservation, extack);
पूर्ण

अटल स्थिर काष्ठा devlink_ops ice_devlink_ops = अणु
	.supported_flash_update_params = DEVLINK_SUPPORT_FLASH_UPDATE_OVERWRITE_MASK,
	.info_get = ice_devlink_info_get,
	.flash_update = ice_devlink_flash_update,
पूर्ण;

अटल व्योम ice_devlink_मुक्त(व्योम *devlink_ptr)
अणु
	devlink_मुक्त((काष्ठा devlink *)devlink_ptr);
पूर्ण

/**
 * ice_allocate_pf - Allocate devlink and वापस PF काष्ठाure poपूर्णांकer
 * @dev: the device to allocate क्रम
 *
 * Allocate a devlink instance क्रम this device and वापस the निजी area as
 * the PF काष्ठाure. The devlink memory is kept track of through devres by
 * adding an action to हटाओ it when unwinding.
 */
काष्ठा ice_pf *ice_allocate_pf(काष्ठा device *dev)
अणु
	काष्ठा devlink *devlink;

	devlink = devlink_alloc(&ice_devlink_ops, माप(काष्ठा ice_pf));
	अगर (!devlink)
		वापस शून्य;

	/* Add an action to tearकरोwn the devlink when unwinding the driver */
	अगर (devm_add_action(dev, ice_devlink_मुक्त, devlink)) अणु
		devlink_मुक्त(devlink);
		वापस शून्य;
	पूर्ण

	वापस devlink_priv(devlink);
पूर्ण

/**
 * ice_devlink_रेजिस्टर - Register devlink पूर्णांकerface क्रम this PF
 * @pf: the PF to रेजिस्टर the devlink क्रम.
 *
 * Register the devlink instance associated with this physical function.
 *
 * Return: zero on success or an error code on failure.
 */
पूर्णांक ice_devlink_रेजिस्टर(काष्ठा ice_pf *pf)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक err;

	err = devlink_रेजिस्टर(devlink, dev);
	अगर (err) अणु
		dev_err(dev, "devlink registration failed: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_devlink_unरेजिस्टर - Unरेजिस्टर devlink resources क्रम this PF.
 * @pf: the PF काष्ठाure to cleanup
 *
 * Releases resources used by devlink and cleans up associated memory.
 */
व्योम ice_devlink_unरेजिस्टर(काष्ठा ice_pf *pf)
अणु
	devlink_unरेजिस्टर(priv_to_devlink(pf));
पूर्ण

/**
 * ice_devlink_create_port - Create a devlink port क्रम this VSI
 * @vsi: the VSI to create a port क्रम
 *
 * Create and रेजिस्टर a devlink_port क्रम this VSI.
 *
 * Return: zero on success or an error code on failure.
 */
पूर्णांक ice_devlink_create_port(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा ice_port_info *pi;
	काष्ठा devlink *devlink;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	पूर्णांक err;

	/* Currently we only create devlink_port instances क्रम PF VSIs */
	अगर (vsi->type != ICE_VSI_PF)
		वापस -EINVAL;

	pf = vsi->back;
	devlink = priv_to_devlink(pf);
	dev = ice_pf_to_dev(pf);
	pi = pf->hw.port_info;

	attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
	attrs.phys.port_number = pi->lport;
	devlink_port_attrs_set(&vsi->devlink_port, &attrs);
	err = devlink_port_रेजिस्टर(devlink, &vsi->devlink_port, vsi->idx);
	अगर (err) अणु
		dev_err(dev, "devlink_port_register failed: %d\n", err);
		वापस err;
	पूर्ण

	vsi->devlink_port_रेजिस्टरed = true;

	वापस 0;
पूर्ण

/**
 * ice_devlink_destroy_port - Destroy the devlink_port क्रम this VSI
 * @vsi: the VSI to cleanup
 *
 * Unरेजिस्टरs the devlink_port काष्ठाure associated with this VSI.
 */
व्योम ice_devlink_destroy_port(काष्ठा ice_vsi *vsi)
अणु
	अगर (!vsi->devlink_port_रेजिस्टरed)
		वापस;

	devlink_port_type_clear(&vsi->devlink_port);
	devlink_port_unरेजिस्टर(&vsi->devlink_port);

	vsi->devlink_port_रेजिस्टरed = false;
पूर्ण

/**
 * ice_devlink_nvm_snapshot - Capture a snapshot of the Shaकरोw RAM contents
 * @devlink: the devlink instance
 * @ops: the devlink region being snapshotted
 * @extack: extended ACK response काष्ठाure
 * @data: on निकास poपूर्णांकs to snapshot data buffer
 *
 * This function is called in response to the DEVLINK_CMD_REGION_TRIGGER क्रम
 * the shaकरोw-ram devlink region. It captures a snapshot of the shaकरोw ram
 * contents. This snapshot can later be viewed via the devlink-region
 * पूर्णांकerface.
 *
 * @वापसs zero on success, and updates the data poपूर्णांकer. Returns a non-zero
 * error code on failure.
 */
अटल पूर्णांक ice_devlink_nvm_snapshot(काष्ठा devlink *devlink,
				    स्थिर काष्ठा devlink_region_ops *ops,
				    काष्ठा netlink_ext_ack *extack, u8 **data)
अणु
	काष्ठा ice_pf *pf = devlink_priv(devlink);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	व्योम *nvm_data;
	u32 nvm_size;

	nvm_size = hw->flash.flash_size;
	nvm_data = vzalloc(nvm_size);
	अगर (!nvm_data)
		वापस -ENOMEM;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	अगर (status) अणु
		dev_dbg(dev, "ice_acquire_nvm failed, err %d aq_err %d\n",
			status, hw->adminq.sq_last_status);
		NL_SET_ERR_MSG_MOD(extack, "Failed to acquire NVM semaphore");
		vमुक्त(nvm_data);
		वापस -EIO;
	पूर्ण

	status = ice_पढ़ो_flat_nvm(hw, 0, &nvm_size, nvm_data, false);
	अगर (status) अणु
		dev_dbg(dev, "ice_read_flat_nvm failed after reading %u bytes, err %d aq_err %d\n",
			nvm_size, status, hw->adminq.sq_last_status);
		NL_SET_ERR_MSG_MOD(extack, "Failed to read NVM contents");
		ice_release_nvm(hw);
		vमुक्त(nvm_data);
		वापस -EIO;
	पूर्ण

	ice_release_nvm(hw);

	*data = nvm_data;

	वापस 0;
पूर्ण

/**
 * ice_devlink_devcaps_snapshot - Capture snapshot of device capabilities
 * @devlink: the devlink instance
 * @ops: the devlink region being snapshotted
 * @extack: extended ACK response काष्ठाure
 * @data: on निकास poपूर्णांकs to snapshot data buffer
 *
 * This function is called in response to the DEVLINK_CMD_REGION_TRIGGER क्रम
 * the device-caps devlink region. It captures a snapshot of the device
 * capabilities reported by firmware.
 *
 * @वापसs zero on success, and updates the data poपूर्णांकer. Returns a non-zero
 * error code on failure.
 */
अटल पूर्णांक
ice_devlink_devcaps_snapshot(काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_region_ops *ops,
			     काष्ठा netlink_ext_ack *extack, u8 **data)
अणु
	काष्ठा ice_pf *pf = devlink_priv(devlink);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	व्योम *devcaps;

	devcaps = vzalloc(ICE_AQ_MAX_BUF_LEN);
	अगर (!devcaps)
		वापस -ENOMEM;

	status = ice_aq_list_caps(hw, devcaps, ICE_AQ_MAX_BUF_LEN, शून्य,
				  ice_aqc_opc_list_dev_caps, शून्य);
	अगर (status) अणु
		dev_dbg(dev, "ice_aq_list_caps: failed to read device capabilities, err %d aq_err %d\n",
			status, hw->adminq.sq_last_status);
		NL_SET_ERR_MSG_MOD(extack, "Failed to read device capabilities");
		vमुक्त(devcaps);
		वापस -EIO;
	पूर्ण

	*data = (u8 *)devcaps;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_region_ops ice_nvm_region_ops = अणु
	.name = "nvm-flash",
	.deकाष्ठाor = vमुक्त,
	.snapshot = ice_devlink_nvm_snapshot,
पूर्ण;

अटल स्थिर काष्ठा devlink_region_ops ice_devcaps_region_ops = अणु
	.name = "device-caps",
	.deकाष्ठाor = vमुक्त,
	.snapshot = ice_devlink_devcaps_snapshot,
पूर्ण;

/**
 * ice_devlink_init_regions - Initialize devlink regions
 * @pf: the PF device काष्ठाure
 *
 * Create devlink regions used to enable access to dump the contents of the
 * flash memory on the device.
 */
व्योम ice_devlink_init_regions(काष्ठा ice_pf *pf)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	u64 nvm_size;

	nvm_size = pf->hw.flash.flash_size;
	pf->nvm_region = devlink_region_create(devlink, &ice_nvm_region_ops, 1,
					       nvm_size);
	अगर (IS_ERR(pf->nvm_region)) अणु
		dev_err(dev, "failed to create NVM devlink region, err %ld\n",
			PTR_ERR(pf->nvm_region));
		pf->nvm_region = शून्य;
	पूर्ण

	pf->devcaps_region = devlink_region_create(devlink,
						   &ice_devcaps_region_ops, 10,
						   ICE_AQ_MAX_BUF_LEN);
	अगर (IS_ERR(pf->devcaps_region)) अणु
		dev_err(dev, "failed to create device-caps devlink region, err %ld\n",
			PTR_ERR(pf->devcaps_region));
		pf->devcaps_region = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_devlink_destroy_regions - Destroy devlink regions
 * @pf: the PF device काष्ठाure
 *
 * Remove previously created regions क्रम this PF.
 */
व्योम ice_devlink_destroy_regions(काष्ठा ice_pf *pf)
अणु
	अगर (pf->nvm_region)
		devlink_region_destroy(pf->nvm_region);
	अगर (pf->devcaps_region)
		devlink_region_destroy(pf->devcaps_region);
पूर्ण
