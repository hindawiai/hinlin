<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003-2018, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर_अघोषित _MEI_HBM_H_
#घोषणा _MEI_HBM_H_

काष्ठा mei_device;
काष्ठा mei_msg_hdr;
काष्ठा mei_cl;
काष्ठा mei_dma_data;

/**
 * क्रमागत mei_hbm_state - host bus message protocol state
 *
 * @MEI_HBM_IDLE : protocol not started
 * @MEI_HBM_STARTING : start request message was sent
 * @MEI_HBM_CAP_SETUP : capabilities request message was sent
 * @MEI_HBM_DR_SETUP : dma ring setup request message was sent
 * @MEI_HBM_ENUM_CLIENTS : क्रमागतeration request was sent
 * @MEI_HBM_CLIENT_PROPERTIES : acquiring clients properties
 * @MEI_HBM_STARTED : क्रमागतeration was completed
 * @MEI_HBM_STOPPED : stopping exchange
 */
क्रमागत mei_hbm_state अणु
	MEI_HBM_IDLE = 0,
	MEI_HBM_STARTING,
	MEI_HBM_CAP_SETUP,
	MEI_HBM_DR_SETUP,
	MEI_HBM_ENUM_CLIENTS,
	MEI_HBM_CLIENT_PROPERTIES,
	MEI_HBM_STARTED,
	MEI_HBM_STOPPED,
पूर्ण;

स्थिर अक्षर *mei_hbm_state_str(क्रमागत mei_hbm_state state);

पूर्णांक mei_hbm_dispatch(काष्ठा mei_device *dev, काष्ठा mei_msg_hdr *hdr);

व्योम mei_hbm_idle(काष्ठा mei_device *dev);
व्योम mei_hbm_reset(काष्ठा mei_device *dev);
पूर्णांक mei_hbm_start_req(काष्ठा mei_device *dev);
पूर्णांक mei_hbm_start_रुको(काष्ठा mei_device *dev);
पूर्णांक mei_hbm_cl_flow_control_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl);
पूर्णांक mei_hbm_cl_disconnect_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl);
पूर्णांक mei_hbm_cl_disconnect_rsp(काष्ठा mei_device *dev, काष्ठा mei_cl *cl);
पूर्णांक mei_hbm_cl_connect_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl);
bool mei_hbm_version_is_supported(काष्ठा mei_device *dev);
पूर्णांक mei_hbm_pg(काष्ठा mei_device *dev, u8 pg_cmd);
व्योम mei_hbm_pg_resume(काष्ठा mei_device *dev);
पूर्णांक mei_hbm_cl_notअगरy_req(काष्ठा mei_device *dev,
			  काष्ठा mei_cl *cl, u8 request);
पूर्णांक mei_hbm_cl_dma_map_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl);
पूर्णांक mei_hbm_cl_dma_unmap_req(काष्ठा mei_device *dev, काष्ठा mei_cl *cl);
#पूर्ण_अगर /* _MEI_HBM_H_ */

