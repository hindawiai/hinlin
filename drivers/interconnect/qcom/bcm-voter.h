<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DRIVERS_INTERCONNECT_QCOM_BCM_VOTER_H__
#घोषणा __DRIVERS_INTERCONNECT_QCOM_BCM_VOTER_H__

#समावेश <soc/qcom/cmd-db.h>
#समावेश <soc/qcom/rpmh.h>
#समावेश <soc/qcom/tcs.h>

#समावेश "icc-rpmh.h"

#घोषणा DEFINE_QBCM(_name, _bcmname, _keepalive, ...)			       \
अटल काष्ठा qcom_icc_bcm _name = अणु					       \
	.name = _bcmname,						       \
	.keepalive = _keepalive,					       \
	.num_nodes = ARRAY_SIZE(((काष्ठा qcom_icc_node *[])अणु __VA_ARGS__ पूर्ण)),  \
	.nodes = अणु __VA_ARGS__ पूर्ण,					       \
पूर्ण

काष्ठा bcm_voter *of_bcm_voter_get(काष्ठा device *dev, स्थिर अक्षर *name);
व्योम qcom_icc_bcm_voter_add(काष्ठा bcm_voter *voter, काष्ठा qcom_icc_bcm *bcm);
पूर्णांक qcom_icc_bcm_voter_commit(काष्ठा bcm_voter *voter);

#पूर्ण_अगर
