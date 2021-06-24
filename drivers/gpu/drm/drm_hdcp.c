<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Intel Corporation.
 *
 * Authors:
 * Ramalingam C <ramalingam.c@पूर्णांकel.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>

#समावेश <drm/drm_hdcp.h>
#समावेश <drm/drm_sysfs.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_property.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_connector.h>

#समावेश "drm_internal.h"

अटल अंतरभूत व्योम drm_hdcp_prपूर्णांक_ksv(स्थिर u8 *ksv)
अणु
	DRM_DEBUG("\t%#02x, %#02x, %#02x, %#02x, %#02x\n",
		  ksv[0], ksv[1], ksv[2], ksv[3], ksv[4]);
पूर्ण

अटल u32 drm_hdcp_get_revoked_ksv_count(स्थिर u8 *buf, u32 vrls_length)
अणु
	u32 parsed_bytes = 0, ksv_count = 0, vrl_ksv_cnt, vrl_sz;

	जबतक (parsed_bytes < vrls_length) अणु
		vrl_ksv_cnt = *buf;
		ksv_count += vrl_ksv_cnt;

		vrl_sz = (vrl_ksv_cnt * DRM_HDCP_KSV_LEN) + 1;
		buf += vrl_sz;
		parsed_bytes += vrl_sz;
	पूर्ण

	/*
	 * When vrls are not valid, ksvs are not considered.
	 * Hence SRM will be discarded.
	 */
	अगर (parsed_bytes != vrls_length)
		ksv_count = 0;

	वापस ksv_count;
पूर्ण

अटल u32 drm_hdcp_get_revoked_ksvs(स्थिर u8 *buf, u8 **revoked_ksv_list,
				     u32 vrls_length)
अणु
	u32 vrl_ksv_cnt, vrl_ksv_sz, vrl_idx = 0;
	u32 parsed_bytes = 0, ksv_count = 0;

	करो अणु
		vrl_ksv_cnt = *buf;
		vrl_ksv_sz = vrl_ksv_cnt * DRM_HDCP_KSV_LEN;

		buf++;

		DRM_DEBUG("vrl: %d, Revoked KSVs: %d\n", vrl_idx++,
			  vrl_ksv_cnt);
		स_नकल((*revoked_ksv_list) + (ksv_count * DRM_HDCP_KSV_LEN),
		       buf, vrl_ksv_sz);

		ksv_count += vrl_ksv_cnt;
		buf += vrl_ksv_sz;

		parsed_bytes += (vrl_ksv_sz + 1);
	पूर्ण जबतक (parsed_bytes < vrls_length);

	वापस ksv_count;
पूर्ण

अटल अंतरभूत u32 get_vrl_length(स्थिर u8 *buf)
अणु
	वापस drm_hdcp_be24_to_cpu(buf);
पूर्ण

अटल पूर्णांक drm_hdcp_parse_hdcp1_srm(स्थिर u8 *buf, माप_प्रकार count,
				    u8 **revoked_ksv_list, u32 *revoked_ksv_cnt)
अणु
	काष्ठा hdcp_srm_header *header;
	u32 vrl_length, ksv_count;

	अगर (count < (माप(काष्ठा hdcp_srm_header) +
	    DRM_HDCP_1_4_VRL_LENGTH_SIZE + DRM_HDCP_1_4_DCP_SIG_SIZE)) अणु
		DRM_ERROR("Invalid blob length\n");
		वापस -EINVAL;
	पूर्ण

	header = (काष्ठा hdcp_srm_header *)buf;
	DRM_DEBUG("SRM ID: 0x%x, SRM Ver: 0x%x, SRM Gen No: 0x%x\n",
		  header->srm_id,
		  be16_to_cpu(header->srm_version), header->srm_gen_no);

	WARN_ON(header->reserved);

	buf = buf + माप(*header);
	vrl_length = get_vrl_length(buf);
	अगर (count < (माप(काष्ठा hdcp_srm_header) + vrl_length) ||
	    vrl_length < (DRM_HDCP_1_4_VRL_LENGTH_SIZE +
			  DRM_HDCP_1_4_DCP_SIG_SIZE)) अणु
		DRM_ERROR("Invalid blob length or vrl length\n");
		वापस -EINVAL;
	पूर्ण

	/* Length of the all vrls combined */
	vrl_length -= (DRM_HDCP_1_4_VRL_LENGTH_SIZE +
		       DRM_HDCP_1_4_DCP_SIG_SIZE);

	अगर (!vrl_length) अणु
		DRM_ERROR("No vrl found\n");
		वापस -EINVAL;
	पूर्ण

	buf += DRM_HDCP_1_4_VRL_LENGTH_SIZE;
	ksv_count = drm_hdcp_get_revoked_ksv_count(buf, vrl_length);
	अगर (!ksv_count) अणु
		DRM_DEBUG("Revoked KSV count is 0\n");
		वापस 0;
	पूर्ण

	*revoked_ksv_list = kसुस्मृति(ksv_count, DRM_HDCP_KSV_LEN, GFP_KERNEL);
	अगर (!*revoked_ksv_list) अणु
		DRM_ERROR("Out of Memory\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (drm_hdcp_get_revoked_ksvs(buf, revoked_ksv_list,
				      vrl_length) != ksv_count) अणु
		*revoked_ksv_cnt = 0;
		kमुक्त(*revoked_ksv_list);
		वापस -EINVAL;
	पूर्ण

	*revoked_ksv_cnt = ksv_count;
	वापस 0;
पूर्ण

अटल पूर्णांक drm_hdcp_parse_hdcp2_srm(स्थिर u8 *buf, माप_प्रकार count,
				    u8 **revoked_ksv_list, u32 *revoked_ksv_cnt)
अणु
	काष्ठा hdcp_srm_header *header;
	u32 vrl_length, ksv_count, ksv_sz;

	अगर (count < (माप(काष्ठा hdcp_srm_header) +
	    DRM_HDCP_2_VRL_LENGTH_SIZE + DRM_HDCP_2_DCP_SIG_SIZE)) अणु
		DRM_ERROR("Invalid blob length\n");
		वापस -EINVAL;
	पूर्ण

	header = (काष्ठा hdcp_srm_header *)buf;
	DRM_DEBUG("SRM ID: 0x%x, SRM Ver: 0x%x, SRM Gen No: 0x%x\n",
		  header->srm_id & DRM_HDCP_SRM_ID_MASK,
		  be16_to_cpu(header->srm_version), header->srm_gen_no);

	अगर (header->reserved)
		वापस -EINVAL;

	buf = buf + माप(*header);
	vrl_length = get_vrl_length(buf);

	अगर (count < (माप(काष्ठा hdcp_srm_header) + vrl_length) ||
	    vrl_length < (DRM_HDCP_2_VRL_LENGTH_SIZE +
	    DRM_HDCP_2_DCP_SIG_SIZE)) अणु
		DRM_ERROR("Invalid blob length or vrl length\n");
		वापस -EINVAL;
	पूर्ण

	/* Length of the all vrls combined */
	vrl_length -= (DRM_HDCP_2_VRL_LENGTH_SIZE +
		       DRM_HDCP_2_DCP_SIG_SIZE);

	अगर (!vrl_length) अणु
		DRM_ERROR("No vrl found\n");
		वापस -EINVAL;
	पूर्ण

	buf += DRM_HDCP_2_VRL_LENGTH_SIZE;
	ksv_count = (*buf << 2) | DRM_HDCP_2_KSV_COUNT_2_LSBITS(*(buf + 1));
	अगर (!ksv_count) अणु
		DRM_DEBUG("Revoked KSV count is 0\n");
		वापस 0;
	पूर्ण

	*revoked_ksv_list = kसुस्मृति(ksv_count, DRM_HDCP_KSV_LEN, GFP_KERNEL);
	अगर (!*revoked_ksv_list) अणु
		DRM_ERROR("Out of Memory\n");
		वापस -ENOMEM;
	पूर्ण

	ksv_sz = ksv_count * DRM_HDCP_KSV_LEN;
	buf += DRM_HDCP_2_NO_OF_DEV_PLUS_RESERVED_SZ;

	DRM_DEBUG("Revoked KSVs: %d\n", ksv_count);
	स_नकल(*revoked_ksv_list, buf, ksv_sz);

	*revoked_ksv_cnt = ksv_count;
	वापस 0;
पूर्ण

अटल अंतरभूत bool is_srm_version_hdcp1(स्थिर u8 *buf)
अणु
	वापस *buf == (u8)(DRM_HDCP_1_4_SRM_ID << 4);
पूर्ण

अटल अंतरभूत bool is_srm_version_hdcp2(स्थिर u8 *buf)
अणु
	वापस *buf == (u8)(DRM_HDCP_2_SRM_ID << 4 | DRM_HDCP_2_INDICATOR);
पूर्ण

अटल पूर्णांक drm_hdcp_srm_update(स्थिर u8 *buf, माप_प्रकार count,
			       u8 **revoked_ksv_list, u32 *revoked_ksv_cnt)
अणु
	अगर (count < माप(काष्ठा hdcp_srm_header))
		वापस -EINVAL;

	अगर (is_srm_version_hdcp1(buf))
		वापस drm_hdcp_parse_hdcp1_srm(buf, count, revoked_ksv_list,
						revoked_ksv_cnt);
	अन्यथा अगर (is_srm_version_hdcp2(buf))
		वापस drm_hdcp_parse_hdcp2_srm(buf, count, revoked_ksv_list,
						revoked_ksv_cnt);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक drm_hdcp_request_srm(काष्ठा drm_device *drm_dev,
				u8 **revoked_ksv_list, u32 *revoked_ksv_cnt)
अणु
	अक्षर fw_name[36] = "display_hdcp_srm.bin";
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware_direct(&fw, (स्थिर अक्षर *)fw_name,
				      drm_dev->dev);
	अगर (ret < 0) अणु
		*revoked_ksv_cnt = 0;
		*revoked_ksv_list = शून्य;
		ret = 0;
		जाओ निकास;
	पूर्ण

	अगर (fw->size && fw->data)
		ret = drm_hdcp_srm_update(fw->data, fw->size, revoked_ksv_list,
					  revoked_ksv_cnt);

निकास:
	release_firmware(fw);
	वापस ret;
पूर्ण

/**
 * drm_hdcp_check_ksvs_revoked - Check the revoked status of the IDs
 *
 * @drm_dev: drm_device क्रम which HDCP revocation check is requested
 * @ksvs: List of KSVs (HDCP receiver IDs)
 * @ksv_count: KSV count passed in through @ksvs
 *
 * This function पढ़ोs the HDCP System renewability Message(SRM Table)
 * from userspace as a firmware and parses it क्रम the revoked HDCP
 * KSVs(Receiver IDs) detected by DCP LLC. Once the revoked KSVs are known,
 * revoked state of the KSVs in the list passed in by display drivers are
 * decided and response is sent.
 *
 * SRM should be presented in the name of "display_hdcp_srm.bin".
 *
 * Format of the SRM table, that userspace needs to ग_लिखो पूर्णांकo the binary file,
 * is defined at:
 * 1. Renewability chapter on 55th page of HDCP 1.4 specअगरication
 * https://www.digital-cp.com/sites/शेष/files/specअगरications/HDCP%20Specअगरication%20Rev1_4_Secure.pdf
 * 2. Renewability chapter on 63rd page of HDCP 2.2 specअगरication
 * https://www.digital-cp.com/sites/शेष/files/specअगरications/HDCP%20on%20HDMI%20Specअगरication%20Rev2_2_Final1.pdf
 *
 * Returns:
 * Count of the revoked KSVs or -ve error number inहाल of the failure.
 */
पूर्णांक drm_hdcp_check_ksvs_revoked(काष्ठा drm_device *drm_dev, u8 *ksvs,
				u32 ksv_count)
अणु
	u32 revoked_ksv_cnt = 0, i, j;
	u8 *revoked_ksv_list = शून्य;
	पूर्णांक ret = 0;

	ret = drm_hdcp_request_srm(drm_dev, &revoked_ksv_list,
				   &revoked_ksv_cnt);
	अगर (ret)
		वापस ret;

	/* revoked_ksv_cnt will be zero when above function failed */
	क्रम (i = 0; i < revoked_ksv_cnt; i++)
		क्रम  (j = 0; j < ksv_count; j++)
			अगर (!स_भेद(&ksvs[j * DRM_HDCP_KSV_LEN],
				    &revoked_ksv_list[i * DRM_HDCP_KSV_LEN],
				    DRM_HDCP_KSV_LEN)) अणु
				DRM_DEBUG("Revoked KSV is ");
				drm_hdcp_prपूर्णांक_ksv(&ksvs[j * DRM_HDCP_KSV_LEN]);
				ret++;
			पूर्ण

	kमुक्त(revoked_ksv_list);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(drm_hdcp_check_ksvs_revoked);

अटल काष्ठा drm_prop_क्रमागत_list drm_cp_क्रमागत_list[] = अणु
	अणु DRM_MODE_CONTENT_PROTECTION_UNDESIRED, "Undesired" पूर्ण,
	अणु DRM_MODE_CONTENT_PROTECTION_DESIRED, "Desired" पूर्ण,
	अणु DRM_MODE_CONTENT_PROTECTION_ENABLED, "Enabled" पूर्ण,
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_content_protection_name, drm_cp_क्रमागत_list)

अटल काष्ठा drm_prop_क्रमागत_list drm_hdcp_content_type_क्रमागत_list[] = अणु
	अणु DRM_MODE_HDCP_CONTENT_TYPE0, "HDCP Type0" पूर्ण,
	अणु DRM_MODE_HDCP_CONTENT_TYPE1, "HDCP Type1" पूर्ण,
पूर्ण;
DRM_ENUM_NAME_FN(drm_get_hdcp_content_type_name,
		 drm_hdcp_content_type_क्रमागत_list)

/**
 * drm_connector_attach_content_protection_property - attach content protection
 * property
 *
 * @connector: connector to attach CP property on.
 * @hdcp_content_type: is HDCP Content Type property needed क्रम connector
 *
 * This is used to add support क्रम content protection on select connectors.
 * Content Protection is पूर्णांकentionally vague to allow क्रम dअगरferent underlying
 * technologies, however it is most implemented by HDCP.
 *
 * When hdcp_content_type is true क्रमागत property called HDCP Content Type is
 * created (अगर it is not alपढ़ोy) and attached to the connector.
 *
 * This property is used क्रम sending the रक्षित content's stream type
 * from userspace to kernel on selected connectors. Protected content provider
 * will decide their type of their content and declare the same to kernel.
 *
 * Content type will be used during the HDCP 2.2 authentication.
 * Content type will be set to &drm_connector_state.hdcp_content_type.
 *
 * The content protection will be set to &drm_connector_state.content_protection
 *
 * When kernel triggered content protection state change like DESIRED->ENABLED
 * and ENABLED->DESIRED, will use drm_hdcp_update_content_protection() to update
 * the content protection state of a connector.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_connector_attach_content_protection_property(
		काष्ठा drm_connector *connector, bool hdcp_content_type)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_property *prop =
			dev->mode_config.content_protection_property;

	अगर (!prop)
		prop = drm_property_create_क्रमागत(dev, 0, "Content Protection",
						drm_cp_क्रमागत_list,
						ARRAY_SIZE(drm_cp_क्रमागत_list));
	अगर (!prop)
		वापस -ENOMEM;

	drm_object_attach_property(&connector->base, prop,
				   DRM_MODE_CONTENT_PROTECTION_UNDESIRED);
	dev->mode_config.content_protection_property = prop;

	अगर (!hdcp_content_type)
		वापस 0;

	prop = dev->mode_config.hdcp_content_type_property;
	अगर (!prop)
		prop = drm_property_create_क्रमागत(dev, 0, "HDCP Content Type",
					drm_hdcp_content_type_क्रमागत_list,
					ARRAY_SIZE(
					drm_hdcp_content_type_क्रमागत_list));
	अगर (!prop)
		वापस -ENOMEM;

	drm_object_attach_property(&connector->base, prop,
				   DRM_MODE_HDCP_CONTENT_TYPE0);
	dev->mode_config.hdcp_content_type_property = prop;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_connector_attach_content_protection_property);

/**
 * drm_hdcp_update_content_protection - Updates the content protection state
 * of a connector
 *
 * @connector: drm_connector on which content protection state needs an update
 * @val: New state of the content protection property
 *
 * This function can be used by display drivers, to update the kernel triggered
 * content protection state changes of a drm_connector such as DESIRED->ENABLED
 * and ENABLED->DESIRED. No uevent क्रम DESIRED->UNDESIRED or ENABLED->UNDESIRED,
 * as userspace is triggering such state change and kernel perक्रमms it without
 * fail.This function update the new state of the property पूर्णांकo the connector's
 * state and generate an uevent to notअगरy the userspace.
 */
व्योम drm_hdcp_update_content_protection(काष्ठा drm_connector *connector,
					u64 val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_connector_state *state = connector->state;

	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
	अगर (state->content_protection == val)
		वापस;

	state->content_protection = val;
	drm_sysfs_connector_status_event(connector,
				 dev->mode_config.content_protection_property);
पूर्ण
EXPORT_SYMBOL(drm_hdcp_update_content_protection);
