<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_DCBX_H
#घोषणा _QED_DCBX_H
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"

#घोषणा DCBX_CONFIG_MAX_APP_PROTOCOL    4

क्रमागत qed_mib_पढ़ो_type अणु
	QED_DCBX_OPERATIONAL_MIB,
	QED_DCBX_REMOTE_MIB,
	QED_DCBX_LOCAL_MIB,
	QED_DCBX_REMOTE_LLDP_MIB,
	QED_DCBX_LOCAL_LLDP_MIB
पूर्ण;

काष्ठा qed_dcbx_app_data अणु
	bool enable;		/* DCB enabled */
	u8 update;		/* Update indication */
	u8 priority;		/* Priority */
	u8 tc;			/* Traffic Class */
	bool करोnt_add_vlan0;	/* Do not insert a vlan tag with id 0 */
पूर्ण;

#घोषणा QED_DCBX_VERSION_DISABLED       0
#घोषणा QED_DCBX_VERSION_IEEE           1
#घोषणा QED_DCBX_VERSION_CEE            2

काष्ठा qed_dcbx_set अणु
#घोषणा QED_DCBX_OVERRIDE_STATE	        BIT(0)
#घोषणा QED_DCBX_OVERRIDE_PFC_CFG       BIT(1)
#घोषणा QED_DCBX_OVERRIDE_ETS_CFG       BIT(2)
#घोषणा QED_DCBX_OVERRIDE_APP_CFG       BIT(3)
#घोषणा QED_DCBX_OVERRIDE_DSCP_CFG      BIT(4)
	u32 override_flags;
	bool enabled;
	काष्ठा qed_dcbx_admin_params config;
	u32 ver_num;
पूर्ण;

काष्ठा qed_dcbx_results अणु
	bool dcbx_enabled;
	u8 pf_id;
	काष्ठा qed_dcbx_app_data arr[DCBX_MAX_PROTOCOL_TYPE];
पूर्ण;

काष्ठा qed_dcbx_app_metadata अणु
	क्रमागत dcbx_protocol_type id;
	अक्षर *name;
	क्रमागत qed_pci_personality personality;
पूर्ण;

काष्ठा qed_dcbx_info अणु
	काष्ठा lldp_status_params_s lldp_remote[LLDP_MAX_LLDP_AGENTS];
	काष्ठा lldp_config_params_s lldp_local[LLDP_MAX_LLDP_AGENTS];
	काष्ठा dcbx_local_params local_admin;
	काष्ठा qed_dcbx_results results;
	काष्ठा dcbx_mib operational;
	काष्ठा dcbx_mib remote;
	काष्ठा qed_dcbx_set set;
	काष्ठा qed_dcbx_get get;
	u8 dcbx_cap;
पूर्ण;

काष्ठा qed_dcbx_mib_meta_data अणु
	काष्ठा lldp_config_params_s *lldp_local;
	काष्ठा lldp_status_params_s *lldp_remote;
	काष्ठा dcbx_local_params *local_admin;
	काष्ठा dcbx_mib *mib;
	माप_प्रकार size;
	u32 addr;
पूर्ण;

बाह्य स्थिर काष्ठा qed_eth_dcbnl_ops qed_dcbnl_ops_pass;

#अगर_घोषित CONFIG_DCB
पूर्णांक qed_dcbx_get_config_params(काष्ठा qed_hwfn *, काष्ठा qed_dcbx_set *);

पूर्णांक qed_dcbx_config_params(काष्ठा qed_hwfn *,
			   काष्ठा qed_ptt *, काष्ठा qed_dcbx_set *, bool);
#पूर्ण_अगर

/* QED local पूर्णांकerface routines */
पूर्णांक
qed_dcbx_mib_update_event(काष्ठा qed_hwfn *,
			  काष्ठा qed_ptt *, क्रमागत qed_mib_पढ़ो_type);

पूर्णांक qed_dcbx_info_alloc(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_dcbx_info_मुक्त(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_dcbx_set_pf_update_params(काष्ठा qed_dcbx_results *p_src,
				   काष्ठा pf_update_ramrod_data *p_dest);

#घोषणा QED_DCBX_DEFAULT_TC	0

u8 qed_dcbx_get_priority_tc(काष्ठा qed_hwfn *p_hwfn, u8 pri);
#पूर्ण_अगर
