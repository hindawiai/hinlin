<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e.h"

#समावेश <linux/firmware.h>

/**
 * i40e_ddp_profiles_eq - checks अगर DDP profiles are the equivalent
 * @a: new profile info
 * @b: old profile info
 *
 * checks अगर DDP profiles are the equivalent.
 * Returns true अगर profiles are the same.
 **/
अटल bool i40e_ddp_profiles_eq(काष्ठा i40e_profile_info *a,
				 काष्ठा i40e_profile_info *b)
अणु
	वापस a->track_id == b->track_id &&
		!स_भेद(&a->version, &b->version, माप(a->version)) &&
		!स_भेद(&a->name, &b->name, I40E_DDP_NAME_SIZE);
पूर्ण

/**
 * i40e_ddp_करोes_profile_exist - checks अगर DDP profile loaded alपढ़ोy
 * @hw: HW data काष्ठाure
 * @pinfo: DDP profile inक्रमmation काष्ठाure
 *
 * checks अगर DDP profile loaded alपढ़ोy.
 * Returns >0 अगर the profile exists.
 * Returns  0 अगर the profile is असलent.
 * Returns <0 अगर error.
 **/
अटल पूर्णांक i40e_ddp_करोes_profile_exist(काष्ठा i40e_hw *hw,
				       काष्ठा i40e_profile_info *pinfo)
अणु
	काष्ठा i40e_ddp_profile_list *profile_list;
	u8 buff[I40E_PROखाता_LIST_SIZE];
	i40e_status status;
	पूर्णांक i;

	status = i40e_aq_get_ddp_list(hw, buff, I40E_PROखाता_LIST_SIZE, 0,
				      शून्य);
	अगर (status)
		वापस -1;

	profile_list = (काष्ठा i40e_ddp_profile_list *)buff;
	क्रम (i = 0; i < profile_list->p_count; i++) अणु
		अगर (i40e_ddp_profiles_eq(pinfo, &profile_list->p_info[i]))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_ddp_profiles_overlap - checks अगर DDP profiles overlap.
 * @new: new profile info
 * @old: old profile info
 *
 * checks अगर DDP profiles overlap.
 * Returns true अगर profiles are overlap.
 **/
अटल bool i40e_ddp_profiles_overlap(काष्ठा i40e_profile_info *new,
				      काष्ठा i40e_profile_info *old)
अणु
	अचिन्हित पूर्णांक group_id_old = (u8)((old->track_id & 0x00FF0000) >> 16);
	अचिन्हित पूर्णांक group_id_new = (u8)((new->track_id & 0x00FF0000) >> 16);

	/* 0x00 group must be only the first */
	अगर (group_id_new == 0)
		वापस true;
	/* 0xFF group is compatible with anything अन्यथा */
	अगर (group_id_new == 0xFF || group_id_old == 0xFF)
		वापस false;
	/* otherwise only profiles from the same group are compatible*/
	वापस group_id_old != group_id_new;
पूर्ण

/**
 * i40e_ddp_करोes_profile_overlap - checks अगर DDP overlaps with existing one.
 * @hw: HW data काष्ठाure
 * @pinfo: DDP profile inक्रमmation काष्ठाure
 *
 * checks अगर DDP profile overlaps with existing one.
 * Returns >0 अगर the profile overlaps.
 * Returns  0 अगर the profile is ok.
 * Returns <0 अगर error.
 **/
अटल पूर्णांक i40e_ddp_करोes_profile_overlap(काष्ठा i40e_hw *hw,
					 काष्ठा i40e_profile_info *pinfo)
अणु
	काष्ठा i40e_ddp_profile_list *profile_list;
	u8 buff[I40E_PROखाता_LIST_SIZE];
	i40e_status status;
	पूर्णांक i;

	status = i40e_aq_get_ddp_list(hw, buff, I40E_PROखाता_LIST_SIZE, 0,
				      शून्य);
	अगर (status)
		वापस -EIO;

	profile_list = (काष्ठा i40e_ddp_profile_list *)buff;
	क्रम (i = 0; i < profile_list->p_count; i++) अणु
		अगर (i40e_ddp_profiles_overlap(pinfo,
					      &profile_list->p_info[i]))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_add_pinfo
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @profile: poपूर्णांकer to the profile segment of the package
 * @profile_info_sec: buffer क्रम inक्रमmation section
 * @track_id: package tracking id
 *
 * Register a profile to the list of loaded profiles.
 */
अटल क्रमागत i40e_status_code
i40e_add_pinfo(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *profile,
	       u8 *profile_info_sec, u32 track_id)
अणु
	काष्ठा i40e_profile_section_header *sec;
	काष्ठा i40e_profile_info *pinfo;
	i40e_status status;
	u32 offset = 0, info = 0;

	sec = (काष्ठा i40e_profile_section_header *)profile_info_sec;
	sec->tbl_size = 1;
	sec->data_end = माप(काष्ठा i40e_profile_section_header) +
			माप(काष्ठा i40e_profile_info);
	sec->section.type = SECTION_TYPE_INFO;
	sec->section.offset = माप(काष्ठा i40e_profile_section_header);
	sec->section.size = माप(काष्ठा i40e_profile_info);
	pinfo = (काष्ठा i40e_profile_info *)(profile_info_sec +
					     sec->section.offset);
	pinfo->track_id = track_id;
	pinfo->version = profile->version;
	pinfo->op = I40E_DDP_ADD_TRACKID;

	/* Clear reserved field */
	स_रखो(pinfo->reserved, 0, माप(pinfo->reserved));
	स_नकल(pinfo->name, profile->name, I40E_DDP_NAME_SIZE);

	status = i40e_aq_ग_लिखो_ddp(hw, (व्योम *)sec, sec->data_end,
				   track_id, &offset, &info, शून्य);
	वापस status;
पूर्ण

/**
 * i40e_del_pinfo - delete DDP profile info from NIC
 * @hw: HW data काष्ठाure
 * @profile: DDP profile segment to be deleted
 * @profile_info_sec: DDP profile section header
 * @track_id: track ID of the profile क्रम deletion
 *
 * Removes DDP profile from the NIC.
 **/
अटल क्रमागत i40e_status_code
i40e_del_pinfo(काष्ठा i40e_hw *hw, काष्ठा i40e_profile_segment *profile,
	       u8 *profile_info_sec, u32 track_id)
अणु
	काष्ठा i40e_profile_section_header *sec;
	काष्ठा i40e_profile_info *pinfo;
	i40e_status status;
	u32 offset = 0, info = 0;

	sec = (काष्ठा i40e_profile_section_header *)profile_info_sec;
	sec->tbl_size = 1;
	sec->data_end = माप(काष्ठा i40e_profile_section_header) +
			माप(काष्ठा i40e_profile_info);
	sec->section.type = SECTION_TYPE_INFO;
	sec->section.offset = माप(काष्ठा i40e_profile_section_header);
	sec->section.size = माप(काष्ठा i40e_profile_info);
	pinfo = (काष्ठा i40e_profile_info *)(profile_info_sec +
					     sec->section.offset);
	pinfo->track_id = track_id;
	pinfo->version = profile->version;
	pinfo->op = I40E_DDP_REMOVE_TRACKID;

	/* Clear reserved field */
	स_रखो(pinfo->reserved, 0, माप(pinfo->reserved));
	स_नकल(pinfo->name, profile->name, I40E_DDP_NAME_SIZE);

	status = i40e_aq_ग_लिखो_ddp(hw, (व्योम *)sec, sec->data_end,
				   track_id, &offset, &info, शून्य);
	वापस status;
पूर्ण

/**
 * i40e_ddp_is_pkg_hdr_valid - perक्रमms basic pkg header पूर्णांकegrity checks
 * @netdev: net device काष्ठाure (क्रम logging purposes)
 * @pkg_hdr: poपूर्णांकer to package header
 * @size_huge: size of the whole DDP profile package in माप_प्रकार
 *
 * Checks correctness of pkg header: Version, size too big/small, and
 * all segment offsets alignment and boundaries. This function lets
 * reject non DDP profile file to be loaded by administrator mistake.
 **/
अटल bool i40e_ddp_is_pkg_hdr_valid(काष्ठा net_device *netdev,
				      काष्ठा i40e_package_header *pkg_hdr,
				      माप_प्रकार size_huge)
अणु
	u32 size = 0xFFFFFFFFU & size_huge;
	u32 pkg_hdr_size;
	u32 segment;

	अगर (!pkg_hdr)
		वापस false;

	अगर (pkg_hdr->version.major > 0) अणु
		काष्ठा i40e_ddp_version ver = pkg_hdr->version;

		netdev_err(netdev, "Unsupported DDP profile version %u.%u.%u.%u",
			   ver.major, ver.minor, ver.update, ver.draft);
		वापस false;
	पूर्ण
	अगर (size_huge > size) अणु
		netdev_err(netdev, "Invalid DDP profile - size is bigger than 4G");
		वापस false;
	पूर्ण
	अगर (size < (माप(काष्ठा i40e_package_header) +
		माप(काष्ठा i40e_metadata_segment) + माप(u32) * 2)) अणु
		netdev_err(netdev, "Invalid DDP profile - size is too small.");
		वापस false;
	पूर्ण

	pkg_hdr_size = माप(u32) * (pkg_hdr->segment_count + 2U);
	अगर (size < pkg_hdr_size) अणु
		netdev_err(netdev, "Invalid DDP profile - too many segments");
		वापस false;
	पूर्ण
	क्रम (segment = 0; segment < pkg_hdr->segment_count; ++segment) अणु
		u32 offset = pkg_hdr->segment_offset[segment];

		अगर (0xFU & offset) अणु
			netdev_err(netdev,
				   "Invalid DDP profile %u segment alignment",
				   segment);
			वापस false;
		पूर्ण
		अगर (pkg_hdr_size > offset || offset >= size) अणु
			netdev_err(netdev,
				   "Invalid DDP profile %u segment offset",
				   segment);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * i40e_ddp_load - perक्रमms DDP loading
 * @netdev: net device काष्ठाure
 * @data: buffer containing recipe file
 * @size: size of the buffer
 * @is_add: true when loading profile, false when rolling back the previous one
 *
 * Checks correctness and loads DDP profile to the NIC. The function is
 * also used क्रम rolling back previously loaded profile.
 **/
पूर्णांक i40e_ddp_load(काष्ठा net_device *netdev, स्थिर u8 *data, माप_प्रकार size,
		  bool is_add)
अणु
	u8 profile_info_sec[माप(काष्ठा i40e_profile_section_header) +
			    माप(काष्ठा i40e_profile_info)];
	काष्ठा i40e_metadata_segment *metadata_hdr;
	काष्ठा i40e_profile_segment *profile_hdr;
	काष्ठा i40e_profile_info pinfo;
	काष्ठा i40e_package_header *pkg_hdr;
	i40e_status status;
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	u32 track_id;
	पूर्णांक istatus;

	pkg_hdr = (काष्ठा i40e_package_header *)data;
	अगर (!i40e_ddp_is_pkg_hdr_valid(netdev, pkg_hdr, size))
		वापस -EINVAL;

	अगर (size < (माप(काष्ठा i40e_package_header) +
		    माप(काष्ठा i40e_metadata_segment) + माप(u32) * 2)) अणु
		netdev_err(netdev, "Invalid DDP recipe size.");
		वापस -EINVAL;
	पूर्ण

	/* Find beginning of segment data in buffer */
	metadata_hdr = (काष्ठा i40e_metadata_segment *)
		i40e_find_segment_in_package(SEGMENT_TYPE_METADATA, pkg_hdr);
	अगर (!metadata_hdr) अणु
		netdev_err(netdev, "Failed to find metadata segment in DDP recipe.");
		वापस -EINVAL;
	पूर्ण

	track_id = metadata_hdr->track_id;
	profile_hdr = (काष्ठा i40e_profile_segment *)
		i40e_find_segment_in_package(SEGMENT_TYPE_I40E, pkg_hdr);
	अगर (!profile_hdr) अणु
		netdev_err(netdev, "Failed to find profile segment in DDP recipe.");
		वापस -EINVAL;
	पूर्ण

	pinfo.track_id = track_id;
	pinfo.version = profile_hdr->version;
	अगर (is_add)
		pinfo.op = I40E_DDP_ADD_TRACKID;
	अन्यथा
		pinfo.op = I40E_DDP_REMOVE_TRACKID;

	स_नकल(pinfo.name, profile_hdr->name, I40E_DDP_NAME_SIZE);

	/* Check अगर profile data alपढ़ोy exists*/
	istatus = i40e_ddp_करोes_profile_exist(&pf->hw, &pinfo);
	अगर (istatus < 0) अणु
		netdev_err(netdev, "Failed to fetch loaded profiles.");
		वापस istatus;
	पूर्ण
	अगर (is_add) अणु
		अगर (istatus > 0) अणु
			netdev_err(netdev, "DDP profile already loaded.");
			वापस -EINVAL;
		पूर्ण
		istatus = i40e_ddp_करोes_profile_overlap(&pf->hw, &pinfo);
		अगर (istatus < 0) अणु
			netdev_err(netdev, "Failed to fetch loaded profiles.");
			वापस istatus;
		पूर्ण
		अगर (istatus > 0) अणु
			netdev_err(netdev, "DDP profile overlaps with existing one.");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (istatus == 0) अणु
			netdev_err(netdev,
				   "DDP profile for deletion does not exist.");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Load profile data */
	अगर (is_add) अणु
		status = i40e_ग_लिखो_profile(&pf->hw, profile_hdr, track_id);
		अगर (status) अणु
			अगर (status == I40E_ERR_DEVICE_NOT_SUPPORTED) अणु
				netdev_err(netdev,
					   "Profile is not supported by the device.");
				वापस -EPERM;
			पूर्ण
			netdev_err(netdev, "Failed to write DDP profile.");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = i40e_rollback_profile(&pf->hw, profile_hdr, track_id);
		अगर (status) अणु
			netdev_err(netdev, "Failed to remove DDP profile.");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Add/हटाओ profile to/from profile list in FW */
	अगर (is_add) अणु
		status = i40e_add_pinfo(&pf->hw, profile_hdr, profile_info_sec,
					track_id);
		अगर (status) अणु
			netdev_err(netdev, "Failed to add DDP profile info.");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = i40e_del_pinfo(&pf->hw, profile_hdr, profile_info_sec,
					track_id);
		अगर (status) अणु
			netdev_err(netdev, "Failed to restore DDP profile info.");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_ddp_restore - restore previously loaded profile and हटाओ from list
 * @pf: PF data काष्ठा
 *
 * Restores previously loaded profile stored on the list in driver memory.
 * After rolling back हटाओs entry from the list.
 **/
अटल पूर्णांक i40e_ddp_restore(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_ddp_old_profile_list *entry;
	काष्ठा net_device *netdev = pf->vsi[pf->lan_vsi]->netdev;
	पूर्णांक status = 0;

	अगर (!list_empty(&pf->ddp_old_prof)) अणु
		entry = list_first_entry(&pf->ddp_old_prof,
					 काष्ठा i40e_ddp_old_profile_list,
					 list);
		status = i40e_ddp_load(netdev, entry->old_ddp_buf,
				       entry->old_ddp_size, false);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_ddp_flash - callback function क्रम ethtool flash feature
 * @netdev: net device काष्ठाure
 * @flash: kernel flash काष्ठाure
 *
 * Ethtool callback function used क्रम loading and unloading DDP profiles.
 **/
पूर्णांक i40e_ddp_flash(काष्ठा net_device *netdev, काष्ठा ethtool_flash *flash)
अणु
	स्थिर काष्ठा firmware *ddp_config;
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक status = 0;

	/* Check क्रम valid region first */
	अगर (flash->region != I40_DDP_FLASH_REGION) अणु
		netdev_err(netdev, "Requested firmware region is not recognized by this driver.");
		वापस -EINVAL;
	पूर्ण
	अगर (pf->hw.bus.func != 0) अणु
		netdev_err(netdev, "Any DDP operation is allowed only on Phy0 NIC interface");
		वापस -EINVAL;
	पूर्ण

	/* If the user supplied "-" instead of file name rollback previously
	 * stored profile.
	 */
	अगर (म_भेदन(flash->data, "-", 2) != 0) अणु
		काष्ठा i40e_ddp_old_profile_list *list_entry;
		अक्षर profile_name[माप(I40E_DDP_PROखाता_PATH)
				  + I40E_DDP_PROखाता_NAME_MAX];

		profile_name[माप(profile_name) - 1] = 0;
		म_नकलन(profile_name, I40E_DDP_PROखाता_PATH,
			माप(profile_name) - 1);
		म_जोड़न(profile_name, flash->data, I40E_DDP_PROखाता_NAME_MAX);
		/* Load DDP recipe. */
		status = request_firmware(&ddp_config, profile_name,
					  &netdev->dev);
		अगर (status) अणु
			netdev_err(netdev, "DDP recipe file request failed.");
			वापस status;
		पूर्ण

		status = i40e_ddp_load(netdev, ddp_config->data,
				       ddp_config->size, true);

		अगर (!status) अणु
			list_entry =
			  kzalloc(माप(काष्ठा i40e_ddp_old_profile_list) +
				  ddp_config->size, GFP_KERNEL);
			अगर (!list_entry) अणु
				netdev_info(netdev, "Failed to allocate memory for previous DDP profile data.");
				netdev_info(netdev, "New profile loaded but roll-back will be impossible.");
			पूर्ण अन्यथा अणु
				स_नकल(list_entry->old_ddp_buf,
				       ddp_config->data, ddp_config->size);
				list_entry->old_ddp_size = ddp_config->size;
				list_add(&list_entry->list, &pf->ddp_old_prof);
			पूर्ण
		पूर्ण

		release_firmware(ddp_config);
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&pf->ddp_old_prof)) अणु
			status = i40e_ddp_restore(pf);
		पूर्ण अन्यथा अणु
			netdev_warn(netdev, "There is no DDP profile to restore.");
			status = -ENOENT;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण
