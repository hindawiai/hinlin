<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright(c) 2015-2020 Intel Corporation. */

#अगर_अघोषित __SDW_SYSFS_LOCAL_H
#घोषणा __SDW_SYSFS_LOCAL_H

/*
 * SDW sysfs APIs -
 */

/* basic attributes to report status of Slave (attachment, dev_num) */
बाह्य स्थिर काष्ठा attribute_group *sdw_slave_status_attr_groups[];

/* additional device-managed properties reported after driver probe */
पूर्णांक sdw_slave_sysfs_init(काष्ठा sdw_slave *slave);
पूर्णांक sdw_slave_sysfs_dpn_init(काष्ठा sdw_slave *slave);

#पूर्ण_अगर /* __SDW_SYSFS_LOCAL_H */
