<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015 Quantenna Communications. All rights reserved. */

#अगर_अघोषित QTNFMAC_BUS_H
#घोषणा QTNFMAC_BUS_H

#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>

#समावेश "trans.h"
#समावेश "core.h"

#घोषणा QTNF_MAX_MAC		3

#घोषणा HBM_FRAME_META_MAGIC_PATTERN_S	0xAB
#घोषणा HBM_FRAME_META_MAGIC_PATTERN_E	0xBA

काष्ठा qtnf_frame_meta_info अणु
	u8 magic_s;
	u8 अगरidx;
	u8 macid;
	u8 magic_e;
पूर्ण __packed;

क्रमागत qtnf_fw_state अणु
	QTNF_FW_STATE_DETACHED,
	QTNF_FW_STATE_BOOT_DONE,
	QTNF_FW_STATE_ACTIVE,
	QTNF_FW_STATE_RUNNING,
	QTNF_FW_STATE_DEAD,
पूर्ण;

काष्ठा qtnf_bus;

काष्ठा qtnf_bus_ops अणु
	/* mgmt methods */
	पूर्णांक (*preinit)(काष्ठा qtnf_bus *);
	व्योम (*stop)(काष्ठा qtnf_bus *);

	/* control path methods */
	पूर्णांक (*control_tx)(काष्ठा qtnf_bus *, काष्ठा sk_buff *);

	/* data xfer methods */
	पूर्णांक (*data_tx)(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक macid, अचिन्हित पूर्णांक vअगरid);
	व्योम (*data_tx_समयout)(काष्ठा qtnf_bus *, काष्ठा net_device *);
	व्योम (*data_tx_use_meta_set)(काष्ठा qtnf_bus *bus, bool use_meta);
	व्योम (*data_rx_start)(काष्ठा qtnf_bus *);
	व्योम (*data_rx_stop)(काष्ठा qtnf_bus *);
पूर्ण;

काष्ठा qtnf_bus अणु
	काष्ठा device *dev;
	क्रमागत qtnf_fw_state fw_state;
	u32 chip;
	u32 chiprev;
	काष्ठा qtnf_bus_ops *bus_ops;
	काष्ठा qtnf_wmac *mac[QTNF_MAX_MAC];
	काष्ठा qtnf_qlink_transport trans;
	काष्ठा qtnf_hw_info hw_info;
	काष्ठा napi_काष्ठा mux_napi;
	काष्ठा net_device mux_dev;
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा workqueue_काष्ठा *hprio_workqueue;
	काष्ठा work_काष्ठा fw_work;
	काष्ठा work_काष्ठा event_work;
	काष्ठा mutex bus_lock; /* lock during command/event processing */
	काष्ठा dentry *dbg_dir;
	काष्ठा notअगरier_block netdev_nb;
	u8 hw_id[ETH_ALEN];
	/* bus निजी data */
	अक्षर bus_priv[] __aligned(माप(व्योम *));
पूर्ण;

अटल अंतरभूत bool qtnf_fw_is_up(काष्ठा qtnf_bus *bus)
अणु
	क्रमागत qtnf_fw_state state = bus->fw_state;

	वापस ((state == QTNF_FW_STATE_ACTIVE) ||
		(state == QTNF_FW_STATE_RUNNING));
पूर्ण

अटल अंतरभूत bool qtnf_fw_is_attached(काष्ठा qtnf_bus *bus)
अणु
	क्रमागत qtnf_fw_state state = bus->fw_state;

	वापस ((state == QTNF_FW_STATE_ACTIVE) ||
		(state == QTNF_FW_STATE_RUNNING) ||
		(state == QTNF_FW_STATE_DEAD));
पूर्ण

अटल अंतरभूत व्योम *get_bus_priv(काष्ठा qtnf_bus *bus)
अणु
	अगर (WARN(!bus, "qtnfmac: invalid bus pointer"))
		वापस शून्य;

	वापस &bus->bus_priv;
पूर्ण

/* callback wrappers */

अटल अंतरभूत पूर्णांक qtnf_bus_preinit(काष्ठा qtnf_bus *bus)
अणु
	अगर (!bus->bus_ops->preinit)
		वापस 0;
	वापस bus->bus_ops->preinit(bus);
पूर्ण

अटल अंतरभूत व्योम qtnf_bus_stop(काष्ठा qtnf_bus *bus)
अणु
	अगर (!bus->bus_ops->stop)
		वापस;
	bus->bus_ops->stop(bus);
पूर्ण

अटल अंतरभूत पूर्णांक qtnf_bus_data_tx(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb,
				   अचिन्हित पूर्णांक macid, अचिन्हित पूर्णांक vअगरid)
अणु
	वापस bus->bus_ops->data_tx(bus, skb, macid, vअगरid);
पूर्ण

अटल अंतरभूत व्योम
qtnf_bus_data_tx_समयout(काष्ठा qtnf_bus *bus, काष्ठा net_device *ndev)
अणु
	वापस bus->bus_ops->data_tx_समयout(bus, ndev);
पूर्ण

अटल अंतरभूत पूर्णांक qtnf_bus_control_tx(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	वापस bus->bus_ops->control_tx(bus, skb);
पूर्ण

अटल अंतरभूत व्योम qtnf_bus_data_rx_start(काष्ठा qtnf_bus *bus)
अणु
	वापस bus->bus_ops->data_rx_start(bus);
पूर्ण

अटल अंतरभूत व्योम qtnf_bus_data_rx_stop(काष्ठा qtnf_bus *bus)
अणु
	वापस bus->bus_ops->data_rx_stop(bus);
पूर्ण

अटल __always_अंतरभूत व्योम qtnf_bus_lock(काष्ठा qtnf_bus *bus)
अणु
	mutex_lock(&bus->bus_lock);
पूर्ण

अटल __always_अंतरभूत व्योम qtnf_bus_unlock(काष्ठा qtnf_bus *bus)
अणु
	mutex_unlock(&bus->bus_lock);
पूर्ण

/* पूर्णांकerface functions from common layer */

पूर्णांक qtnf_core_attach(काष्ठा qtnf_bus *bus);
व्योम qtnf_core_detach(काष्ठा qtnf_bus *bus);

#पूर्ण_अगर /* QTNFMAC_BUS_H */
