<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

#समावेश "ipa.h"
#समावेश "ipa_data.h"
#समावेश "ipa_reg.h"
#समावेश "ipa_resource.h"

/**
 * DOC: IPA Resources
 *
 * The IPA manages a set of resources पूर्णांकernally क्रम various purposes.
 * A given IPA version has a fixed number of resource types, and a fixed
 * total number of resources of each type.  "Source" resource types
 * are separate from "destination" resource types.
 *
 * Each version of IPA also has some number of resource groups.  Each
 * endpoपूर्णांक is asचिन्हित to a resource group, and all endpoपूर्णांकs in the
 * same group share pools of each type of resource.  A subset of the
 * total resources of each type is asचिन्हित क्रम use by each group.
 */

अटल bool ipa_resource_limits_valid(काष्ठा ipa *ipa,
				      स्थिर काष्ठा ipa_resource_data *data)
अणु
#अगर_घोषित IPA_VALIDATION
	u32 group_count;
	u32 i;
	u32 j;

	/* We program at most 8 source or destination resource group limits */
	BUILD_BUG_ON(IPA_RESOURCE_GROUP_MAX > 8);

	group_count = data->rsrc_group_src_count;
	अगर (!group_count || group_count > IPA_RESOURCE_GROUP_MAX)
		वापस false;

	/* Return an error अगर a non-zero resource limit is specअगरied
	 * क्रम a resource group not supported by hardware.
	 */
	क्रम (i = 0; i < data->resource_src_count; i++) अणु
		स्थिर काष्ठा ipa_resource *resource;

		resource = &data->resource_src[i];
		क्रम (j = group_count; j < IPA_RESOURCE_GROUP_MAX; j++)
			अगर (resource->limits[j].min || resource->limits[j].max)
				वापस false;
	पूर्ण

	group_count = data->rsrc_group_src_count;
	अगर (!group_count || group_count > IPA_RESOURCE_GROUP_MAX)
		वापस false;

	क्रम (i = 0; i < data->resource_dst_count; i++) अणु
		स्थिर काष्ठा ipa_resource *resource;

		resource = &data->resource_dst[i];
		क्रम (j = group_count; j < IPA_RESOURCE_GROUP_MAX; j++)
			अगर (resource->limits[j].min || resource->limits[j].max)
				वापस false;
	पूर्ण
#पूर्ण_अगर /* !IPA_VALIDATION */
	वापस true;
पूर्ण

अटल व्योम
ipa_resource_config_common(काष्ठा ipa *ipa, u32 offset,
			   स्थिर काष्ठा ipa_resource_limits *xlimits,
			   स्थिर काष्ठा ipa_resource_limits *ylimits)
अणु
	u32 val;

	val = u32_encode_bits(xlimits->min, X_MIN_LIM_FMASK);
	val |= u32_encode_bits(xlimits->max, X_MAX_LIM_FMASK);
	अगर (ylimits) अणु
		val |= u32_encode_bits(ylimits->min, Y_MIN_LIM_FMASK);
		val |= u32_encode_bits(ylimits->max, Y_MAX_LIM_FMASK);
	पूर्ण

	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_resource_config_src(काष्ठा ipa *ipa, u32 resource_type,
				    स्थिर काष्ठा ipa_resource_data *data)
अणु
	u32 group_count = data->rsrc_group_src_count;
	स्थिर काष्ठा ipa_resource_limits *ylimits;
	स्थिर काष्ठा ipa_resource *resource;
	u32 offset;

	resource = &data->resource_src[resource_type];

	offset = IPA_REG_SRC_RSRC_GRP_01_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 1 ? शून्य : &resource->limits[1];
	ipa_resource_config_common(ipa, offset, &resource->limits[0], ylimits);

	अगर (group_count < 3)
		वापस;

	offset = IPA_REG_SRC_RSRC_GRP_23_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 3 ? शून्य : &resource->limits[3];
	ipa_resource_config_common(ipa, offset, &resource->limits[2], ylimits);

	अगर (group_count < 5)
		वापस;

	offset = IPA_REG_SRC_RSRC_GRP_45_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 5 ? शून्य : &resource->limits[5];
	ipa_resource_config_common(ipa, offset, &resource->limits[4], ylimits);

	अगर (group_count < 7)
		वापस;

	offset = IPA_REG_SRC_RSRC_GRP_67_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 7 ? शून्य : &resource->limits[7];
	ipa_resource_config_common(ipa, offset, &resource->limits[6], ylimits);
पूर्ण

अटल व्योम ipa_resource_config_dst(काष्ठा ipa *ipa, u32 resource_type,
				    स्थिर काष्ठा ipa_resource_data *data)
अणु
	u32 group_count = data->rsrc_group_dst_count;
	स्थिर काष्ठा ipa_resource_limits *ylimits;
	स्थिर काष्ठा ipa_resource *resource;
	u32 offset;

	resource = &data->resource_dst[resource_type];

	offset = IPA_REG_DST_RSRC_GRP_01_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 1 ? शून्य : &resource->limits[1];
	ipa_resource_config_common(ipa, offset, &resource->limits[0], ylimits);

	अगर (group_count < 3)
		वापस;

	offset = IPA_REG_DST_RSRC_GRP_23_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 3 ? शून्य : &resource->limits[3];
	ipa_resource_config_common(ipa, offset, &resource->limits[2], ylimits);

	अगर (group_count < 5)
		वापस;

	offset = IPA_REG_DST_RSRC_GRP_45_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 5 ? शून्य : &resource->limits[5];
	ipa_resource_config_common(ipa, offset, &resource->limits[4], ylimits);

	अगर (group_count < 7)
		वापस;

	offset = IPA_REG_DST_RSRC_GRP_67_RSRC_TYPE_N_OFFSET(resource_type);
	ylimits = group_count == 7 ? शून्य : &resource->limits[7];
	ipa_resource_config_common(ipa, offset, &resource->limits[6], ylimits);
पूर्ण

/* Configure resources; there is no ipa_resource_deconfig() */
पूर्णांक ipa_resource_config(काष्ठा ipa *ipa, स्थिर काष्ठा ipa_resource_data *data)
अणु
	u32 i;

	अगर (!ipa_resource_limits_valid(ipa, data))
		वापस -EINVAL;

	क्रम (i = 0; i < data->resource_src_count; i++)
		ipa_resource_config_src(ipa, i, data);

	क्रम (i = 0; i < data->resource_dst_count; i++)
		ipa_resource_config_dst(ipa, i, data);

	वापस 0;
पूर्ण
