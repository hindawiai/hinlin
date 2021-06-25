<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_DCB_NL_H_
#घोषणा _ICE_DCB_NL_H_

#अगर_घोषित CONFIG_DCB
व्योम ice_dcbnl_setup(काष्ठा ice_vsi *vsi);
व्योम ice_dcbnl_set_all(काष्ठा ice_vsi *vsi);
व्योम
ice_dcbnl_flush_apps(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *old_cfg,
		     काष्ठा ice_dcbx_cfg *new_cfg);
#अन्यथा
#घोषणा ice_dcbnl_setup(vsi) करो अणुपूर्ण जबतक (0)
#घोषणा ice_dcbnl_set_all(vsi) करो अणुपूर्ण जबतक (0)
#घोषणा ice_dcbnl_flush_apps(pf, old_cfg, new_cfg) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_DCB */

#पूर्ण_अगर /* _ICE_DCB_NL_H_ */
