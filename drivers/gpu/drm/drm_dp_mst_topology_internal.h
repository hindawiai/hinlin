<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *
 * Declarations क्रम DP MST related functions which are only used in selftests
 *
 * Copyright तऊ 2018 Red Hat
 * Authors:
 *     Lyude Paul <lyude@redhat.com>
 */

#अगर_अघोषित _DRM_DP_MST_HELPER_INTERNAL_H_
#घोषणा _DRM_DP_MST_HELPER_INTERNAL_H_

#समावेश <drm/drm_dp_mst_helper.h>

व्योम
drm_dp_encode_sideband_req(स्थिर काष्ठा drm_dp_sideband_msg_req_body *req,
			   काष्ठा drm_dp_sideband_msg_tx *raw);
पूर्णांक drm_dp_decode_sideband_req(स्थिर काष्ठा drm_dp_sideband_msg_tx *raw,
			       काष्ठा drm_dp_sideband_msg_req_body *req);
व्योम
drm_dp_dump_sideband_msg_req_body(स्थिर काष्ठा drm_dp_sideband_msg_req_body *req,
				  पूर्णांक indent, काष्ठा drm_prपूर्णांकer *prपूर्णांकer);

#पूर्ण_अगर /* !_DRM_DP_MST_HELPER_INTERNAL_H_ */
