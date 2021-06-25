<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_POWERPC_PERF_HV_24X7_H_
#घोषणा LINUX_POWERPC_PERF_HV_24X7_H_

#समावेश <linux/types.h>

क्रमागत hv_perf_करोमुख्यs अणु
#घोषणा DOMAIN(n, v, x, c) HV_PERF_DOMAIN_##n = v,
#समावेश "hv-24x7-domains.h"
#अघोषित DOMAIN
	HV_PERF_DOMAIN_MAX,
पूर्ण;

#घोषणा H24x7_REQUEST_SIZE(अगरace_version)	(अगरace_version == 1 ? 16 : 32)

काष्ठा hv_24x7_request अणु
	/* PHYSICAL करोमुख्यs require enabling via phyp/hmc. */
	__u8 perक्रमmance_करोमुख्य;
	__u8 reserved[0x1];

	/* bytes to पढ़ो starting at @data_offset. must be a multiple of 8 */
	__be16 data_size;

	/*
	 * byte offset within the perf करोमुख्य to पढ़ो from. must be 8 byte
	 * aligned
	 */
	__be32 data_offset;

	/*
	 * only valid क्रम VIRTUAL_PROCESSOR करोमुख्यs, ignored क्रम others.
	 * -1 means "current partition only"
	 *  Enabling via phyp/hmc required क्रम non-"-1" values. 0 क्रमbidden
	 *  unless requestor is 0.
	 */
	__be16 starting_lpar_ix;

	/*
	 * Ignored when @starting_lpar_ix == -1
	 * Ignored when @perक्रमmance_करोमुख्य is not VIRTUAL_PROCESSOR_*
	 * -1 means "infinite" or all
	 */
	__be16 max_num_lpars;

	/* chip, core, or भव processor based on @perक्रमmance_करोमुख्य */
	__be16 starting_ix;
	__be16 max_ix;

	/* The following fields were added in v2 of the 24x7 पूर्णांकerface. */

	__u8 starting_thपढ़ो_group_ix;

	/* -1 means all thपढ़ो groups starting at @starting_thपढ़ो_group_ix */
	__u8 max_num_thपढ़ो_groups;

	__u8 reserved2[0xE];
पूर्ण __packed;

काष्ठा hv_24x7_request_buffer अणु
	/* 0 - ? */
	/* 1 - ? */
	__u8 पूर्णांकerface_version;
	__u8 num_requests;
	__u8 reserved[0xE];
	काष्ठा hv_24x7_request requests[];
पूर्ण __packed;

काष्ठा hv_24x7_result_element_v1 अणु
	__be16 lpar_ix;

	/*
	 * represents the core, chip, or भव processor based on the
	 * request's @perक्रमmance_करोमुख्य
	 */
	__be16 करोमुख्य_ix;

	/* -1 अगर @perक्रमmance_करोमुख्य करोes not refer to a भव processor */
	__be32 lpar_cfg_instance_id;

	/* size = @result_element_data_size of containing result. */
	__u64 element_data[];
पूर्ण __packed;

/*
 * We need a separate काष्ठा क्रम v2 because the offset of @element_data changed
 * between versions.
 */
काष्ठा hv_24x7_result_element_v2 अणु
	__be16 lpar_ix;

	/*
	 * represents the core, chip, or भव processor based on the
	 * request's @perक्रमmance_करोमुख्य
	 */
	__be16 करोमुख्य_ix;

	/* -1 अगर @perक्रमmance_करोमुख्य करोes not refer to a भव processor */
	__be32 lpar_cfg_instance_id;

	__u8 thपढ़ो_group_ix;

	__u8 reserved[7];

	/* size = @result_element_data_size of containing result. */
	__u64 element_data[];
पूर्ण __packed;

काष्ठा hv_24x7_result अणु
	/*
	 * The index of the 24x7 Request Structure in the 24x7 Request Buffer
	 * used to request this result.
	 */
	__u8 result_ix;

	/*
	 * 0 = not all result elements fit पूर्णांकo the buffer, additional requests
	 *     required
	 * 1 = all result elements were वापसed
	 */
	__u8 results_complete;
	__be16 num_elements_वापसed;

	/*
	 * This is a copy of @data_size from the corresponding hv_24x7_request
	 *
	 * Warning: to obtain the size of each element in @elements you have
	 * to add the size of the other members of the result_element काष्ठा.
	 */
	__be16 result_element_data_size;
	__u8 reserved[0x2];

	/*
	 * Either
	 *	काष्ठा hv_24x7_result_element_v1[@num_elements_वापसed]
	 * or
	 *	काष्ठा hv_24x7_result_element_v2[@num_elements_वापसed]
	 *
	 * depending on the पूर्णांकerface_version field of the
	 * काष्ठा hv_24x7_data_result_buffer containing this result.
	 */
	अक्षर elements[];
पूर्ण __packed;

काष्ठा hv_24x7_data_result_buffer अणु
	/* See versioning क्रम request buffer */
	__u8 पूर्णांकerface_version;

	__u8 num_results;
	__u8 reserved[0x1];
	__u8 failing_request_ix;
	__be32 detailed_rc;
	__be64 cec_cfg_instance_id;
	__be64 catalog_version_num;
	__u8 reserved2[0x8];
	/* WARNING: only valid क्रम the first result due to variable sizes of
	 *	    results */
	काष्ठा hv_24x7_result results[]; /* [@num_results] */
पूर्ण __packed;

#पूर्ण_अगर
