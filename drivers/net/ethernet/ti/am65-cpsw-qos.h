<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 */

#अगर_अघोषित AM65_CPSW_QOS_H_
#घोषणा AM65_CPSW_QOS_H_

#समावेश <linux/netdevice.h>
#समावेश <net/pkt_sched.h>

काष्ठा am65_cpsw_est अणु
	पूर्णांक buf;
	/* has to be the last one */
	काष्ठा tc_taprio_qopt_offload taprio;
पूर्ण;

काष्ठा am65_cpsw_qos अणु
	काष्ठा am65_cpsw_est *est_admin;
	काष्ठा am65_cpsw_est *est_oper;
	kसमय_प्रकार link_करोwn_समय;
	पूर्णांक link_speed;
पूर्ण;

पूर्णांक am65_cpsw_qos_nकरो_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
			       व्योम *type_data);
व्योम am65_cpsw_qos_link_up(काष्ठा net_device *ndev, पूर्णांक link_speed);
व्योम am65_cpsw_qos_link_करोwn(काष्ठा net_device *ndev);

#पूर्ण_अगर /* AM65_CPSW_QOS_H_ */
