<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित _NFP_APP_H
#घोषणा _NFP_APP_H 1

#समावेश <net/devlink.h>

#समावेश <trace/events/devlink.h>

#समावेश "nfp_net_repr.h"

#घोषणा NFP_APP_CTRL_MTU_MAX	U32_MAX

काष्ठा bpf_prog;
काष्ठा net_device;
काष्ठा netdev_bpf;
काष्ठा netlink_ext_ack;
काष्ठा pci_dev;
काष्ठा sk_buff;
काष्ठा nfp_app;
काष्ठा nfp_cpp;
काष्ठा nfp_pf;
काष्ठा nfp_repr;
काष्ठा nfp_net;

क्रमागत nfp_app_id अणु
	NFP_APP_CORE_NIC	= 0x1,
	NFP_APP_BPF_NIC		= 0x2,
	NFP_APP_FLOWER_NIC	= 0x3,
	NFP_APP_ACTIVE_BUFFER_MGMT_NIC = 0x4,
पूर्ण;

बाह्य स्थिर काष्ठा nfp_app_type app_nic;
बाह्य स्थिर काष्ठा nfp_app_type app_bpf;
बाह्य स्थिर काष्ठा nfp_app_type app_flower;
बाह्य स्थिर काष्ठा nfp_app_type app_abm;

/**
 * काष्ठा nfp_app_type - application definition
 * @id:		application ID
 * @name:	application name
 * @ctrl_cap_mask:  ctrl vNIC capability mask, allows disabling features like
 *		    IRQMOD which are on by शेष but counter-productive क्रम
 *		    control messages which are often latency-sensitive
 * @ctrl_has_meta:  control messages have prepend of type:5/port:CTRL
 *
 * Callbacks
 * @init:	perक्रमm basic app checks and init
 * @clean:	clean app state
 * @extra_cap:	extra capabilities string
 * @nकरो_init:	vNIC and repr netdev .nकरो_init
 * @nकरो_uninit:	vNIC and repr netdev .nकरो_unपूर्णांक
 * @vnic_alloc:	allocate vNICs (assign port types, etc.)
 * @vnic_मुक्त:	मुक्त up app's vNIC state
 * @vnic_init:	vNIC netdev was रेजिस्टरed
 * @vnic_clean:	vNIC netdev about to be unरेजिस्टरed
 * @repr_init:	representor about to be रेजिस्टरed
 * @repr_preclean:	representor about to unरेजिस्टरed, executed beक्रमe app
 *			reference to the it is हटाओd
 * @repr_clean:	representor about to be unरेजिस्टरed
 * @repr_खोलो:	representor netdev खोलो callback
 * @repr_stop:	representor netdev stop callback
 * @check_mtu:	MTU change request on a netdev (verअगरy it is valid)
 * @repr_change_mtu:	MTU change request on repr (make and verअगरy change)
 * @port_get_stats:		get extra ethtool statistics क्रम a port
 * @port_get_stats_count:	get count of extra statistics क्रम a port
 * @port_get_stats_strings:	get strings क्रम extra statistics
 * @start:	start application logic
 * @stop:	stop application logic
 * @netdev_event:	Netdevice notअगरier event
 * @ctrl_msg_rx:    control message handler
 * @ctrl_msg_rx_raw:	handler क्रम control messages from data queues
 * @setup_tc:	setup TC nकरो
 * @bpf:	BPF nकरो offload-related calls
 * @xdp_offload:    offload an XDP program
 * @eचयन_mode_get:    get SR-IOV eचयन mode
 * @eचयन_mode_set:    set SR-IOV eचयन mode (under pf->lock)
 * @sriov_enable: app-specअगरic sriov initialisation
 * @sriov_disable: app-specअगरic sriov clean-up
 * @dev_get:	get representor or पूर्णांकernal port representing netdev
 */
काष्ठा nfp_app_type अणु
	क्रमागत nfp_app_id id;
	स्थिर अक्षर *name;

	u32 ctrl_cap_mask;
	bool ctrl_has_meta;

	पूर्णांक (*init)(काष्ठा nfp_app *app);
	व्योम (*clean)(काष्ठा nfp_app *app);

	स्थिर अक्षर *(*extra_cap)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn);

	पूर्णांक (*nकरो_init)(काष्ठा nfp_app *app, काष्ठा net_device *netdev);
	व्योम (*nकरो_uninit)(काष्ठा nfp_app *app, काष्ठा net_device *netdev);

	पूर्णांक (*vnic_alloc)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
			  अचिन्हित पूर्णांक id);
	व्योम (*vnic_मुक्त)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn);
	पूर्णांक (*vnic_init)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn);
	व्योम (*vnic_clean)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn);

	पूर्णांक (*repr_init)(काष्ठा nfp_app *app, काष्ठा net_device *netdev);
	व्योम (*repr_preclean)(काष्ठा nfp_app *app, काष्ठा net_device *netdev);
	व्योम (*repr_clean)(काष्ठा nfp_app *app, काष्ठा net_device *netdev);

	पूर्णांक (*repr_खोलो)(काष्ठा nfp_app *app, काष्ठा nfp_repr *repr);
	पूर्णांक (*repr_stop)(काष्ठा nfp_app *app, काष्ठा nfp_repr *repr);

	पूर्णांक (*check_mtu)(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			 पूर्णांक new_mtu);
	पूर्णांक (*repr_change_mtu)(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			       पूर्णांक new_mtu);

	u64 *(*port_get_stats)(काष्ठा nfp_app *app,
			       काष्ठा nfp_port *port, u64 *data);
	पूर्णांक (*port_get_stats_count)(काष्ठा nfp_app *app, काष्ठा nfp_port *port);
	u8 *(*port_get_stats_strings)(काष्ठा nfp_app *app,
				      काष्ठा nfp_port *port, u8 *data);

	पूर्णांक (*start)(काष्ठा nfp_app *app);
	व्योम (*stop)(काष्ठा nfp_app *app);

	पूर्णांक (*netdev_event)(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			    अचिन्हित दीर्घ event, व्योम *ptr);

	व्योम (*ctrl_msg_rx)(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
	व्योम (*ctrl_msg_rx_raw)(काष्ठा nfp_app *app, स्थिर व्योम *data,
				अचिन्हित पूर्णांक len);

	पूर्णांक (*setup_tc)(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			क्रमागत tc_setup_type type, व्योम *type_data);
	पूर्णांक (*bpf)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
		   काष्ठा netdev_bpf *xdp);
	पूर्णांक (*xdp_offload)(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
			   काष्ठा bpf_prog *prog,
			   काष्ठा netlink_ext_ack *extack);

	पूर्णांक (*sriov_enable)(काष्ठा nfp_app *app, पूर्णांक num_vfs);
	व्योम (*sriov_disable)(काष्ठा nfp_app *app);

	क्रमागत devlink_eचयन_mode (*eचयन_mode_get)(काष्ठा nfp_app *app);
	पूर्णांक (*eचयन_mode_set)(काष्ठा nfp_app *app, u16 mode);
	काष्ठा net_device *(*dev_get)(काष्ठा nfp_app *app, u32 id,
				      bool *redir_egress);
पूर्ण;

/**
 * काष्ठा nfp_app - NFP application container
 * @pdev:	backpoपूर्णांकer to PCI device
 * @pf:		backpoपूर्णांकer to NFP PF काष्ठाure
 * @cpp:	poपूर्णांकer to the CPP handle
 * @ctrl:	poपूर्णांकer to ctrl vNIC काष्ठा
 * @reprs:	array of poपूर्णांकers to representors
 * @type:	poपूर्णांकer to स्थिर application ops and info
 * @ctrl_mtu:	MTU to set on the control vNIC (set in .init())
 * @netdev_nb:	Netdevice notअगरier block
 * @priv:	app-specअगरic priv data
 */
काष्ठा nfp_app अणु
	काष्ठा pci_dev *pdev;
	काष्ठा nfp_pf *pf;
	काष्ठा nfp_cpp *cpp;

	काष्ठा nfp_net *ctrl;
	काष्ठा nfp_reprs __rcu *reprs[NFP_REPR_TYPE_MAX + 1];

	स्थिर काष्ठा nfp_app_type *type;
	अचिन्हित पूर्णांक ctrl_mtu;

	काष्ठा notअगरier_block netdev_nb;

	व्योम *priv;
पूर्ण;

व्योम nfp_check_rhashtable_empty(व्योम *ptr, व्योम *arg);
bool __nfp_ctrl_tx(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb);
bool nfp_ctrl_tx(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb);

अटल अंतरभूत पूर्णांक nfp_app_init(काष्ठा nfp_app *app)
अणु
	अगर (!app->type->init)
		वापस 0;
	वापस app->type->init(app);
पूर्ण

अटल अंतरभूत व्योम nfp_app_clean(काष्ठा nfp_app *app)
अणु
	अगर (app->type->clean)
		app->type->clean(app);
पूर्ण

पूर्णांक nfp_app_nकरो_init(काष्ठा net_device *netdev);
व्योम nfp_app_nकरो_uninit(काष्ठा net_device *netdev);

अटल अंतरभूत पूर्णांक nfp_app_vnic_alloc(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
				     अचिन्हित पूर्णांक id)
अणु
	वापस app->type->vnic_alloc(app, nn, id);
पूर्ण

अटल अंतरभूत व्योम nfp_app_vnic_मुक्त(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	अगर (app->type->vnic_मुक्त)
		app->type->vnic_मुक्त(app, nn);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_vnic_init(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	अगर (!app->type->vnic_init)
		वापस 0;
	वापस app->type->vnic_init(app, nn);
पूर्ण

अटल अंतरभूत व्योम nfp_app_vnic_clean(काष्ठा nfp_app *app, काष्ठा nfp_net *nn)
अणु
	अगर (app->type->vnic_clean)
		app->type->vnic_clean(app, nn);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_repr_खोलो(काष्ठा nfp_app *app, काष्ठा nfp_repr *repr)
अणु
	अगर (!app->type->repr_खोलो)
		वापस -EINVAL;
	वापस app->type->repr_खोलो(app, repr);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_repr_stop(काष्ठा nfp_app *app, काष्ठा nfp_repr *repr)
अणु
	अगर (!app->type->repr_stop)
		वापस -EINVAL;
	वापस app->type->repr_stop(app, repr);
पूर्ण

अटल अंतरभूत पूर्णांक
nfp_app_repr_init(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	अगर (!app->type->repr_init)
		वापस 0;
	वापस app->type->repr_init(app, netdev);
पूर्ण

अटल अंतरभूत व्योम
nfp_app_repr_preclean(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	अगर (app->type->repr_preclean)
		app->type->repr_preclean(app, netdev);
पूर्ण

अटल अंतरभूत व्योम
nfp_app_repr_clean(काष्ठा nfp_app *app, काष्ठा net_device *netdev)
अणु
	अगर (app->type->repr_clean)
		app->type->repr_clean(app, netdev);
पूर्ण

अटल अंतरभूत पूर्णांक
nfp_app_check_mtu(काष्ठा nfp_app *app, काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	अगर (!app || !app->type->check_mtu)
		वापस 0;
	वापस app->type->check_mtu(app, netdev, new_mtu);
पूर्ण

अटल अंतरभूत पूर्णांक
nfp_app_repr_change_mtu(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			पूर्णांक new_mtu)
अणु
	अगर (!app || !app->type->repr_change_mtu)
		वापस 0;
	वापस app->type->repr_change_mtu(app, netdev, new_mtu);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *nfp_app_name(काष्ठा nfp_app *app)
अणु
	अगर (!app)
		वापस "";
	वापस app->type->name;
पूर्ण

अटल अंतरभूत bool nfp_app_needs_ctrl_vnic(काष्ठा nfp_app *app)
अणु
	वापस app && app->type->ctrl_msg_rx;
पूर्ण

अटल अंतरभूत bool nfp_app_ctrl_has_meta(काष्ठा nfp_app *app)
अणु
	वापस app->type->ctrl_has_meta;
पूर्ण

अटल अंतरभूत bool nfp_app_ctrl_uses_data_vnics(काष्ठा nfp_app *app)
अणु
	वापस app && app->type->ctrl_msg_rx_raw;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *nfp_app_extra_cap(काष्ठा nfp_app *app,
					    काष्ठा nfp_net *nn)
अणु
	अगर (!app || !app->type->extra_cap)
		वापस "";
	वापस app->type->extra_cap(app, nn);
पूर्ण

अटल अंतरभूत bool nfp_app_has_tc(काष्ठा nfp_app *app)
अणु
	वापस app && app->type->setup_tc;
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_setup_tc(काष्ठा nfp_app *app,
				   काष्ठा net_device *netdev,
				   क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	अगर (!app || !app->type->setup_tc)
		वापस -EOPNOTSUPP;
	वापस app->type->setup_tc(app, netdev, type, type_data);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_bpf(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
			      काष्ठा netdev_bpf *bpf)
अणु
	अगर (!app || !app->type->bpf)
		वापस -EINVAL;
	वापस app->type->bpf(app, nn, bpf);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_xdp_offload(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
				      काष्ठा bpf_prog *prog,
				      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!app || !app->type->xdp_offload)
		वापस -EOPNOTSUPP;
	वापस app->type->xdp_offload(app, nn, prog, extack);
पूर्ण

अटल अंतरभूत bool __nfp_app_ctrl_tx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	trace_devlink_hwmsg(priv_to_devlink(app->pf), false, 0,
			    skb->data, skb->len);

	वापस __nfp_ctrl_tx(app->ctrl, skb);
पूर्ण

अटल अंतरभूत bool nfp_app_ctrl_tx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	trace_devlink_hwmsg(priv_to_devlink(app->pf), false, 0,
			    skb->data, skb->len);

	वापस nfp_ctrl_tx(app->ctrl, skb);
पूर्ण

अटल अंतरभूत व्योम nfp_app_ctrl_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	trace_devlink_hwmsg(priv_to_devlink(app->pf), true, 0,
			    skb->data, skb->len);

	app->type->ctrl_msg_rx(app, skb);
पूर्ण

अटल अंतरभूत व्योम
nfp_app_ctrl_rx_raw(काष्ठा nfp_app *app, स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	अगर (!app || !app->type->ctrl_msg_rx_raw)
		वापस;

	trace_devlink_hwmsg(priv_to_devlink(app->pf), true, 0, data, len);
	app->type->ctrl_msg_rx_raw(app, data, len);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_eचयन_mode_get(काष्ठा nfp_app *app, u16 *mode)
अणु
	अगर (!app->type->eचयन_mode_get)
		वापस -EOPNOTSUPP;

	*mode = app->type->eचयन_mode_get(app);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_eचयन_mode_set(काष्ठा nfp_app *app, u16 mode)
अणु
	अगर (!app->type->eचयन_mode_set)
		वापस -EOPNOTSUPP;
	वापस app->type->eचयन_mode_set(app, mode);
पूर्ण

अटल अंतरभूत पूर्णांक nfp_app_sriov_enable(काष्ठा nfp_app *app, पूर्णांक num_vfs)
अणु
	अगर (!app || !app->type->sriov_enable)
		वापस -EOPNOTSUPP;
	वापस app->type->sriov_enable(app, num_vfs);
पूर्ण

अटल अंतरभूत व्योम nfp_app_sriov_disable(काष्ठा nfp_app *app)
अणु
	अगर (app && app->type->sriov_disable)
		app->type->sriov_disable(app);
पूर्ण

अटल अंतरभूत
काष्ठा net_device *nfp_app_dev_get(काष्ठा nfp_app *app, u32 id,
				   bool *redir_egress)
अणु
	अगर (unlikely(!app || !app->type->dev_get))
		वापस शून्य;

	वापस app->type->dev_get(app, id, redir_egress);
पूर्ण

काष्ठा nfp_app *nfp_app_from_netdev(काष्ठा net_device *netdev);

u64 *nfp_app_port_get_stats(काष्ठा nfp_port *port, u64 *data);
पूर्णांक nfp_app_port_get_stats_count(काष्ठा nfp_port *port);
u8 *nfp_app_port_get_stats_strings(काष्ठा nfp_port *port, u8 *data);

काष्ठा nfp_reprs *
nfp_reprs_get_locked(काष्ठा nfp_app *app, क्रमागत nfp_repr_type type);
काष्ठा nfp_reprs *
nfp_app_reprs_set(काष्ठा nfp_app *app, क्रमागत nfp_repr_type type,
		  काष्ठा nfp_reprs *reprs);

स्थिर अक्षर *nfp_app_mip_name(काष्ठा nfp_app *app);
काष्ठा sk_buff *
nfp_app_ctrl_msg_alloc(काष्ठा nfp_app *app, अचिन्हित पूर्णांक size, gfp_t priority);

काष्ठा nfp_app *nfp_app_alloc(काष्ठा nfp_pf *pf, क्रमागत nfp_app_id id);
व्योम nfp_app_मुक्त(काष्ठा nfp_app *app);
पूर्णांक nfp_app_start(काष्ठा nfp_app *app, काष्ठा nfp_net *ctrl);
व्योम nfp_app_stop(काष्ठा nfp_app *app);

/* Callbacks shared between apps */

पूर्णांक nfp_app_nic_vnic_alloc(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
			   अचिन्हित पूर्णांक id);
पूर्णांक nfp_app_nic_vnic_init_phy_port(काष्ठा nfp_pf *pf, काष्ठा nfp_app *app,
				   काष्ठा nfp_net *nn, अचिन्हित पूर्णांक id);

काष्ठा devlink_port *nfp_devlink_get_devlink_port(काष्ठा net_device *netdev);

#पूर्ण_अगर
