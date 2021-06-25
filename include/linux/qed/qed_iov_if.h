<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_IOV_IF_H
#घोषणा _QED_IOV_IF_H

#समावेश <linux/qed/qed_अगर.h>

/* Structs used by PF to control and manipulate child VFs */
काष्ठा qed_iov_hv_ops अणु
	पूर्णांक (*configure)(काष्ठा qed_dev *cdev, पूर्णांक num_vfs_param);

	पूर्णांक (*set_mac) (काष्ठा qed_dev *cdev, u8 *mac, पूर्णांक vfid);

	पूर्णांक (*set_vlan) (काष्ठा qed_dev *cdev, u16 vid, पूर्णांक vfid);

	पूर्णांक (*get_config) (काष्ठा qed_dev *cdev, पूर्णांक vf_id,
			   काष्ठा अगरla_vf_info *ivi);

	पूर्णांक (*set_link_state) (काष्ठा qed_dev *cdev, पूर्णांक vf_id,
			       पूर्णांक link_state);

	पूर्णांक (*set_spoof) (काष्ठा qed_dev *cdev, पूर्णांक vfid, bool val);

	पूर्णांक (*set_rate) (काष्ठा qed_dev *cdev, पूर्णांक vfid,
			 u32 min_rate, u32 max_rate);

	पूर्णांक (*set_trust) (काष्ठा qed_dev *cdev, पूर्णांक vfid, bool trust);
पूर्ण;

#पूर्ण_अगर
