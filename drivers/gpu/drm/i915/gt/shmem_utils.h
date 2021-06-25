<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित SHMEM_UTILS_H
#घोषणा SHMEM_UTILS_H

#समावेश <linux/types.h>

काष्ठा drm_i915_gem_object;
काष्ठा file;

काष्ठा file *shmem_create_from_data(स्थिर अक्षर *name, व्योम *data, माप_प्रकार len);
काष्ठा file *shmem_create_from_object(काष्ठा drm_i915_gem_object *obj);

व्योम *shmem_pin_map(काष्ठा file *file);
व्योम shmem_unpin_map(काष्ठा file *file, व्योम *ptr);

पूर्णांक shmem_पढ़ो(काष्ठा file *file, loff_t off, व्योम *dst, माप_प्रकार len);
पूर्णांक shmem_ग_लिखो(काष्ठा file *file, loff_t off, व्योम *src, माप_प्रकार len);

#पूर्ण_अगर /* SHMEM_UTILS_H */
