<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_CFG_H_
#घोषणा ADF_CFG_H_

#समावेश <linux/list.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/debugfs.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_cfg_common.h"
#समावेश "adf_cfg_strings.h"

काष्ठा adf_cfg_key_val अणु
	अक्षर key[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	अक्षर val[ADF_CFG_MAX_VAL_LEN_IN_BYTES];
	क्रमागत adf_cfg_val_type type;
	काष्ठा list_head list;
पूर्ण;

काष्ठा adf_cfg_section अणु
	अक्षर name[ADF_CFG_MAX_SECTION_LEN_IN_BYTES];
	काष्ठा list_head list;
	काष्ठा list_head param_head;
पूर्ण;

काष्ठा adf_cfg_device_data अणु
	काष्ठा list_head sec_list;
	काष्ठा dentry *debug;
	काष्ठा rw_semaphore lock;
पूर्ण;

पूर्णांक adf_cfg_dev_add(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_cfg_dev_हटाओ(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_cfg_section_add(काष्ठा adf_accel_dev *accel_dev, स्थिर अक्षर *name);
व्योम adf_cfg_del_all(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_cfg_add_key_value_param(काष्ठा adf_accel_dev *accel_dev,
				स्थिर अक्षर *section_name,
				स्थिर अक्षर *key, स्थिर व्योम *val,
				क्रमागत adf_cfg_val_type type);
पूर्णांक adf_cfg_get_param_value(काष्ठा adf_accel_dev *accel_dev,
			    स्थिर अक्षर *section, स्थिर अक्षर *name, अक्षर *value);

#पूर्ण_अगर
