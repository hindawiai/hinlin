<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2012 Intel Corporation.  All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित FCOE_SYSFS
#घोषणा FCOE_SYSFS

#समावेश <linux/अगर_ether.h>
#समावेश <linux/device.h>
#समावेश <scsi/fc/fc_fcoe.h>

काष्ठा fcoe_ctlr_device;
काष्ठा fcoe_fcf_device;

काष्ठा fcoe_sysfs_function_ढाँचा अणु
	व्योम (*get_fcoe_ctlr_link_fail)(काष्ठा fcoe_ctlr_device *);
	व्योम (*get_fcoe_ctlr_vlink_fail)(काष्ठा fcoe_ctlr_device *);
	व्योम (*get_fcoe_ctlr_miss_fka)(काष्ठा fcoe_ctlr_device *);
	व्योम (*get_fcoe_ctlr_symb_err)(काष्ठा fcoe_ctlr_device *);
	व्योम (*get_fcoe_ctlr_err_block)(काष्ठा fcoe_ctlr_device *);
	व्योम (*get_fcoe_ctlr_fcs_error)(काष्ठा fcoe_ctlr_device *);
	व्योम (*set_fcoe_ctlr_mode)(काष्ठा fcoe_ctlr_device *);
	पूर्णांक  (*set_fcoe_ctlr_enabled)(काष्ठा fcoe_ctlr_device *);
	व्योम (*get_fcoe_fcf_selected)(काष्ठा fcoe_fcf_device *);
	व्योम (*get_fcoe_fcf_vlan_id)(काष्ठा fcoe_fcf_device *);
पूर्ण;

#घोषणा dev_to_ctlr(d)					\
	container_of((d), काष्ठा fcoe_ctlr_device, dev)

क्रमागत fip_conn_type अणु
	FIP_CONN_TYPE_UNKNOWN,
	FIP_CONN_TYPE_FABRIC,
	FIP_CONN_TYPE_VN2VN,
पूर्ण;

क्रमागत ctlr_enabled_state अणु
	FCOE_CTLR_ENABLED,
	FCOE_CTLR_DISABLED,
	FCOE_CTLR_UNUSED,
पूर्ण;

काष्ठा fcoe_ctlr_device अणु
	u32				id;

	काष्ठा device			dev;
	काष्ठा fcoe_sysfs_function_ढाँचा *f;

	काष्ठा list_head		fcfs;
	अक्षर				work_q_name[20];
	काष्ठा workqueue_काष्ठा		*work_q;
	अक्षर				devloss_work_q_name[20];
	काष्ठा workqueue_काष्ठा		*devloss_work_q;
	काष्ठा mutex			lock;

	पूर्णांक                             fcf_dev_loss_पंचांगo;
	क्रमागत fip_conn_type              mode;

	क्रमागत ctlr_enabled_state         enabled;

	/* expected in host order क्रम displaying */
	काष्ठा fcoe_fc_els_lesb         lesb;
पूर्ण;

अटल अंतरभूत व्योम *fcoe_ctlr_device_priv(स्थिर काष्ठा fcoe_ctlr_device *ctlr)
अणु
	वापस (व्योम *)(ctlr + 1);
पूर्ण

/* fcf states */
क्रमागत fcf_state अणु
	FCOE_FCF_STATE_UNKNOWN,
	FCOE_FCF_STATE_DISCONNECTED,
	FCOE_FCF_STATE_CONNECTED,
	FCOE_FCF_STATE_DELETED,
पूर्ण;

काष्ठा fcoe_fcf_device अणु
	u32		    id;
	काष्ठा device	    dev;
	काष्ठा list_head    peers;
	काष्ठा work_काष्ठा  delete_work;
	काष्ठा delayed_work dev_loss_work;
	u32		    dev_loss_पंचांगo;
	व्योम                *priv;
	क्रमागत fcf_state      state;

	u64                 fabric_name;
	u64                 चयन_name;
	u32                 fc_map;
	u16                 vfid;
	u8                  mac[ETH_ALEN];
	u8                  priority;
	u32                 fka_period;
	u8                  selected;
	u16                 vlan_id;
पूर्ण;

#घोषणा dev_to_fcf(d)					\
	container_of((d), काष्ठा fcoe_fcf_device, dev)
/* parentage should never be missing */
#घोषणा fcoe_fcf_dev_to_ctlr_dev(x)		\
	dev_to_ctlr((x)->dev.parent)
#घोषणा fcoe_fcf_device_priv(x)			\
	((x)->priv)

काष्ठा fcoe_ctlr_device *fcoe_ctlr_device_add(काष्ठा device *parent,
			    काष्ठा fcoe_sysfs_function_ढाँचा *f,
			    पूर्णांक priv_size);
व्योम fcoe_ctlr_device_delete(काष्ठा fcoe_ctlr_device *);
काष्ठा fcoe_fcf_device *fcoe_fcf_device_add(काष्ठा fcoe_ctlr_device *,
					    काष्ठा fcoe_fcf_device *);
व्योम fcoe_fcf_device_delete(काष्ठा fcoe_fcf_device *);

पूर्णांक __init fcoe_sysfs_setup(व्योम);
व्योम __निकास fcoe_sysfs_tearकरोwn(व्योम);

#पूर्ण_अगर /* FCOE_SYSFS */
