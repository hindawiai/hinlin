<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __MOCK_REGION_H
#घोषणा __MOCK_REGION_H

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_memory_region;

काष्ठा पूर्णांकel_memory_region *
mock_region_create(काष्ठा drm_i915_निजी *i915,
		   resource_माप_प्रकार start,
		   resource_माप_प्रकार size,
		   resource_माप_प्रकार min_page_size,
		   resource_माप_प्रकार io_start);

#पूर्ण_अगर /* !__MOCK_REGION_H */
