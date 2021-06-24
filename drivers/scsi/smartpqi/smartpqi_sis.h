<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    driver क्रम Microsemi PQI-based storage controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright (c) 2016-2018 Microsemi Corporation
 *    Copyright (c) 2016 PMC-Sierra, Inc.
 *
 *    Questions/Comments/Bugfixes to storagedev@microchip.com
 *
 */

#अगर !defined(_SMARTPQI_SIS_H)
#घोषणा _SMARTPQI_SIS_H

पूर्णांक sis_रुको_क्रम_ctrl_पढ़ोy(काष्ठा pqi_ctrl_info *ctrl_info);
पूर्णांक sis_रुको_क्रम_ctrl_पढ़ोy_resume(काष्ठा pqi_ctrl_info *ctrl_info);
bool sis_is_firmware_running(काष्ठा pqi_ctrl_info *ctrl_info);
bool sis_is_kernel_up(काष्ठा pqi_ctrl_info *ctrl_info);
पूर्णांक sis_get_ctrl_properties(काष्ठा pqi_ctrl_info *ctrl_info);
पूर्णांक sis_get_pqi_capabilities(काष्ठा pqi_ctrl_info *ctrl_info);
पूर्णांक sis_init_base_काष्ठा_addr(काष्ठा pqi_ctrl_info *ctrl_info);
व्योम sis_enable_msix(काष्ठा pqi_ctrl_info *ctrl_info);
व्योम sis_enable_पूर्णांकx(काष्ठा pqi_ctrl_info *ctrl_info);
व्योम sis_shutकरोwn_ctrl(काष्ठा pqi_ctrl_info *ctrl_info);
पूर्णांक sis_pqi_reset_quiesce(काष्ठा pqi_ctrl_info *ctrl_info);
पूर्णांक sis_reenable_sis_mode(काष्ठा pqi_ctrl_info *ctrl_info);
व्योम sis_ग_लिखो_driver_scratch(काष्ठा pqi_ctrl_info *ctrl_info, u32 value);
u32 sis_पढ़ो_driver_scratch(काष्ठा pqi_ctrl_info *ctrl_info);
व्योम sis_soft_reset(काष्ठा pqi_ctrl_info *ctrl_info);
u32 sis_get_product_id(काष्ठा pqi_ctrl_info *ctrl_info);

#पूर्ण_अगर	/* _SMARTPQI_SIS_H */
