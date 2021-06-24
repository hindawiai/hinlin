<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अगर_अघोषित RNBD_SRV_H
#घोषणा RNBD_SRV_H

#समावेश <linux/types.h>
#समावेश <linux/idr.h>
#समावेश <linux/kref.h>

#समावेश <rtrs.h>
#समावेश "rnbd-proto.h"
#समावेश "rnbd-log.h"

काष्ठा rnbd_srv_session अणु
	/* Entry inside global sess_list */
	काष्ठा list_head        list;
	काष्ठा rtrs_srv		*rtrs;
	अक्षर			sessname[NAME_MAX];
	पूर्णांक			queue_depth;
	काष्ठा bio_set		sess_bio_set;

	काष्ठा xarray		index_idr;
	/* List of काष्ठा rnbd_srv_sess_dev */
	काष्ठा list_head        sess_dev_list;
	काष्ठा mutex		lock;
	u8			ver;
पूर्ण;

काष्ठा rnbd_srv_dev अणु
	/* Entry inside global dev_list */
	काष्ठा list_head                list;
	काष्ठा kobject                  dev_kobj;
	काष्ठा kobject                  *dev_sessions_kobj;
	काष्ठा kref                     kref;
	अक्षर				id[NAME_MAX];
	/* List of rnbd_srv_sess_dev काष्ठाs */
	काष्ठा list_head		sess_dev_list;
	काष्ठा mutex			lock;
	पूर्णांक				खोलो_ग_लिखो_cnt;
पूर्ण;

/* Structure which binds N devices and N sessions */
काष्ठा rnbd_srv_sess_dev अणु
	/* Entry inside rnbd_srv_dev काष्ठा */
	काष्ठा list_head		dev_list;
	/* Entry inside rnbd_srv_session काष्ठा */
	काष्ठा list_head		sess_list;
	काष्ठा rnbd_dev			*rnbd_dev;
	काष्ठा rnbd_srv_session		*sess;
	काष्ठा rnbd_srv_dev		*dev;
	काष्ठा kobject                  kobj;
	u32                             device_id;
	bool				keep_id;
	भ_शेषe_t                         खोलो_flags;
	काष्ठा kref			kref;
	काष्ठा completion               *destroy_comp;
	अक्षर				pathname[NAME_MAX];
	क्रमागत rnbd_access_mode		access_mode;
पूर्ण;

व्योम rnbd_srv_sess_dev_क्रमce_बंद(काष्ठा rnbd_srv_sess_dev *sess_dev,
				   काष्ठा kobj_attribute *attr);
/* rnbd-srv-sysfs.c */

पूर्णांक rnbd_srv_create_dev_sysfs(काष्ठा rnbd_srv_dev *dev,
			      काष्ठा block_device *bdev,
			      स्थिर अक्षर *dir_name);
व्योम rnbd_srv_destroy_dev_sysfs(काष्ठा rnbd_srv_dev *dev);
पूर्णांक rnbd_srv_create_dev_session_sysfs(काष्ठा rnbd_srv_sess_dev *sess_dev);
व्योम rnbd_srv_destroy_dev_session_sysfs(काष्ठा rnbd_srv_sess_dev *sess_dev);
पूर्णांक rnbd_srv_create_sysfs_files(व्योम);
व्योम rnbd_srv_destroy_sysfs_files(व्योम);
व्योम rnbd_destroy_sess_dev(काष्ठा rnbd_srv_sess_dev *sess_dev, bool keep_id);

#पूर्ण_अगर /* RNBD_SRV_H */
