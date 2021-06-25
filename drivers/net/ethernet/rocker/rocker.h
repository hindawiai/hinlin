<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/rocker/rocker.h - Rocker चयन device driver
 * Copyright (c) 2014-2016 Jiri Pirko <jiri@mellanox.com>
 * Copyright (c) 2014 Scott Feldman <sfeldma@gmail.com>
 */

#अगर_अघोषित _ROCKER_H
#घोषणा _ROCKER_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/neighbour.h>
#समावेश <net/चयनdev.h>

#समावेश "rocker_hw.h"

काष्ठा rocker_desc_info अणु
	अक्षर *data; /* mapped */
	माप_प्रकार data_size;
	माप_प्रकार tlv_size;
	काष्ठा rocker_desc *desc;
	dma_addr_t mapaddr;
पूर्ण;

काष्ठा rocker_dma_ring_info अणु
	माप_प्रकार size;
	u32 head;
	u32 tail;
	काष्ठा rocker_desc *desc; /* mapped */
	dma_addr_t mapaddr;
	काष्ठा rocker_desc_info *desc_info;
	अचिन्हित पूर्णांक type;
पूर्ण;

काष्ठा rocker;

काष्ठा rocker_port अणु
	काष्ठा net_device *dev;
	काष्ठा rocker *rocker;
	व्योम *wpriv;
	अचिन्हित पूर्णांक port_number;
	u32 pport;
	काष्ठा napi_काष्ठा napi_tx;
	काष्ठा napi_काष्ठा napi_rx;
	काष्ठा rocker_dma_ring_info tx_ring;
	काष्ठा rocker_dma_ring_info rx_ring;
पूर्ण;

काष्ठा rocker_port *rocker_port_dev_lower_find(काष्ठा net_device *dev,
					       काष्ठा rocker *rocker);

काष्ठा rocker_world_ops;

काष्ठा rocker अणु
	काष्ठा pci_dev *pdev;
	u8 __iomem *hw_addr;
	काष्ठा msix_entry *msix_entries;
	अचिन्हित पूर्णांक port_count;
	काष्ठा rocker_port **ports;
	काष्ठा अणु
		u64 id;
	पूर्ण hw;
	spinlock_t cmd_ring_lock;		/* क्रम cmd ring accesses */
	काष्ठा rocker_dma_ring_info cmd_ring;
	काष्ठा rocker_dma_ring_info event_ring;
	काष्ठा notअगरier_block fib_nb;
	काष्ठा rocker_world_ops *wops;
	काष्ठा workqueue_काष्ठा *rocker_owq;
	व्योम *wpriv;
पूर्ण;

प्रकार पूर्णांक (*rocker_cmd_prep_cb_t)(स्थिर काष्ठा rocker_port *rocker_port,
				    काष्ठा rocker_desc_info *desc_info,
				    व्योम *priv);

प्रकार पूर्णांक (*rocker_cmd_proc_cb_t)(स्थिर काष्ठा rocker_port *rocker_port,
				    स्थिर काष्ठा rocker_desc_info *desc_info,
				    व्योम *priv);

पूर्णांक rocker_cmd_exec(काष्ठा rocker_port *rocker_port, bool noरुको,
		    rocker_cmd_prep_cb_t prepare, व्योम *prepare_priv,
		    rocker_cmd_proc_cb_t process, व्योम *process_priv);

पूर्णांक rocker_port_set_learning(काष्ठा rocker_port *rocker_port,
			     bool learning);

काष्ठा rocker_world_ops अणु
	स्थिर अक्षर *kind;
	माप_प्रकार priv_size;
	माप_प्रकार port_priv_size;
	u8 mode;
	पूर्णांक (*init)(काष्ठा rocker *rocker);
	व्योम (*fini)(काष्ठा rocker *rocker);
	पूर्णांक (*port_pre_init)(काष्ठा rocker_port *rocker_port);
	पूर्णांक (*port_init)(काष्ठा rocker_port *rocker_port);
	व्योम (*port_fini)(काष्ठा rocker_port *rocker_port);
	व्योम (*port_post_fini)(काष्ठा rocker_port *rocker_port);
	पूर्णांक (*port_खोलो)(काष्ठा rocker_port *rocker_port);
	व्योम (*port_stop)(काष्ठा rocker_port *rocker_port);
	पूर्णांक (*port_attr_stp_state_set)(काष्ठा rocker_port *rocker_port,
				       u8 state);
	पूर्णांक (*port_attr_bridge_flags_set)(काष्ठा rocker_port *rocker_port,
					  अचिन्हित दीर्घ brport_flags);
	पूर्णांक (*port_attr_bridge_flags_support_get)(स्थिर काष्ठा rocker_port *
						  rocker_port,
						  अचिन्हित दीर्घ *
						  p_brport_flags);
	पूर्णांक (*port_attr_bridge_ageing_समय_set)(काष्ठा rocker_port *rocker_port,
						u32 ageing_समय);
	पूर्णांक (*port_obj_vlan_add)(काष्ठा rocker_port *rocker_port,
				 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);
	पूर्णांक (*port_obj_vlan_del)(काष्ठा rocker_port *rocker_port,
				 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);
	पूर्णांक (*port_obj_fdb_add)(काष्ठा rocker_port *rocker_port,
				u16 vid, स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*port_obj_fdb_del)(काष्ठा rocker_port *rocker_port,
				u16 vid, स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*port_master_linked)(काष्ठा rocker_port *rocker_port,
				  काष्ठा net_device *master);
	पूर्णांक (*port_master_unlinked)(काष्ठा rocker_port *rocker_port,
				    काष्ठा net_device *master);
	पूर्णांक (*port_neigh_update)(काष्ठा rocker_port *rocker_port,
				 काष्ठा neighbour *n);
	पूर्णांक (*port_neigh_destroy)(काष्ठा rocker_port *rocker_port,
				  काष्ठा neighbour *n);
	पूर्णांक (*port_ev_mac_vlan_seen)(काष्ठा rocker_port *rocker_port,
				     स्थिर अचिन्हित अक्षर *addr,
				     __be16 vlan_id);
	पूर्णांक (*fib4_add)(काष्ठा rocker *rocker,
			स्थिर काष्ठा fib_entry_notअगरier_info *fen_info);
	पूर्णांक (*fib4_del)(काष्ठा rocker *rocker,
			स्थिर काष्ठा fib_entry_notअगरier_info *fen_info);
	व्योम (*fib4_पात)(काष्ठा rocker *rocker);
पूर्ण;

बाह्य काष्ठा rocker_world_ops rocker_ofdpa_ops;

#पूर्ण_अगर
