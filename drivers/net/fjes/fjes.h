<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015 FUJITSU LIMITED
 */

#अगर_अघोषित FJES_H_
#घोषणा FJES_H_

#समावेश <linux/acpi.h>

#समावेश "fjes_hw.h"

#घोषणा FJES_ACPI_SYMBOL	"Extended Socket"
#घोषणा FJES_MAX_QUEUES		1
#घोषणा FJES_TX_RETRY_INTERVAL	(20 * HZ)
#घोषणा FJES_TX_RETRY_TIMEOUT	(100)
#घोषणा FJES_TX_TX_STALL_TIMEOUT	(FJES_TX_RETRY_INTERVAL / 2)
#घोषणा FJES_OPEN_ZONE_UPDATE_WAIT	(300) /* msec */
#घोषणा FJES_IRQ_WATCH_DELAY	(HZ)

/* board specअगरic निजी data काष्ठाure */
काष्ठा fjes_adapter अणु
	काष्ठा net_device *netdev;
	काष्ठा platक्रमm_device *plat_dev;

	काष्ठा napi_काष्ठा napi;
	काष्ठा rtnl_link_stats64 stats64;

	अचिन्हित पूर्णांक tx_retry_count;
	अचिन्हित दीर्घ tx_start_jअगरfies;
	अचिन्हित दीर्घ rx_last_jअगरfies;
	bool unset_rx_last;

	काष्ठा work_काष्ठा क्रमce_बंद_task;
	bool क्रमce_reset;
	bool खोलो_guard;

	bool irq_रेजिस्टरed;

	काष्ठा workqueue_काष्ठा *txrx_wq;
	काष्ठा workqueue_काष्ठा *control_wq;

	काष्ठा work_काष्ठा tx_stall_task;
	काष्ठा work_काष्ठा उठाओ_पूर्णांकr_rxdata_task;

	काष्ठा work_काष्ठा unshare_watch_task;
	अचिन्हित दीर्घ unshare_watch_biपंचांगask;

	काष्ठा delayed_work पूर्णांकerrupt_watch_task;
	bool पूर्णांकerrupt_watch_enable;

	काष्ठा fjes_hw hw;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dbg_adapter;
#पूर्ण_अगर
पूर्ण;

बाह्य अक्षर fjes_driver_name[];
बाह्य अक्षर fjes_driver_version[];
बाह्य स्थिर u32 fjes_support_mtu[];

व्योम fjes_set_ethtool_ops(काष्ठा net_device *);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम fjes_dbg_adapter_init(काष्ठा fjes_adapter *adapter);
व्योम fjes_dbg_adapter_निकास(काष्ठा fjes_adapter *adapter);
व्योम fjes_dbg_init(व्योम);
व्योम fjes_dbg_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम fjes_dbg_adapter_init(काष्ठा fjes_adapter *adapter) अणुपूर्ण
अटल अंतरभूत व्योम fjes_dbg_adapter_निकास(काष्ठा fjes_adapter *adapter) अणुपूर्ण
अटल अंतरभूत व्योम fjes_dbg_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम fjes_dbg_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* FJES_H_ */
