<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NITROX_HAL_H
#घोषणा __NITROX_HAL_H

#समावेश "nitrox_dev.h"

व्योम nitrox_config_aqm_rings(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_aqm_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_emu_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_pkt_input_rings(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_pkt_solicit_ports(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_nps_core_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_nps_pkt_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_pom_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_अक्रम_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_efl_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_bmi_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_bmo_unit(काष्ठा nitrox_device *ndev);
व्योम nitrox_config_lbc_unit(काष्ठा nitrox_device *ndev);
व्योम invalidate_lbc(काष्ठा nitrox_device *ndev);
व्योम enable_aqm_ring(काष्ठा nitrox_device *ndev, पूर्णांक qno);
व्योम enable_pkt_input_ring(काष्ठा nitrox_device *ndev, पूर्णांक ring);
व्योम enable_pkt_solicit_port(काष्ठा nitrox_device *ndev, पूर्णांक port);
व्योम config_nps_core_vfcfg_mode(काष्ठा nitrox_device *ndev, क्रमागत vf_mode mode);
व्योम nitrox_get_hwinfo(काष्ठा nitrox_device *ndev);
व्योम enable_pf2vf_mbox_पूर्णांकerrupts(काष्ठा nitrox_device *ndev);
व्योम disable_pf2vf_mbox_पूर्णांकerrupts(काष्ठा nitrox_device *ndev);

#पूर्ण_अगर /* __NITROX_HAL_H */
