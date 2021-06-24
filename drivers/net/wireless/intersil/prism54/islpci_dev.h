<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright (C) 2003 Herbert Valerio Riedel <hvr@gnu.org>
 *  Copyright (C) 2003 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>
 *  Copyright (C) 2003 Aurelien Alleaume <slts@मुक्त.fr>
 */

#अगर_अघोषित _ISLPCI_DEV_H
#घोषणा _ISLPCI_DEV_H

#समावेश <linux/irqवापस.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#समावेश "isl_38xx.h"
#समावेश "isl_oid.h"
#समावेश "islpci_mgt.h"

/* some states might not be superflous and may be हटाओd when
   design is finalized (hvr) */
प्रकार क्रमागत अणु
	PRV_STATE_OFF = 0,	/* this means hw_unavailable is != 0 */
	PRV_STATE_PREBOOT,	/* we are in a pre-boot state (empty RAM) */
	PRV_STATE_BOOT,		/* boot state (fw upload, run fw) */
	PRV_STATE_POSTBOOT,	/* after boot state, need reset now */
	PRV_STATE_PREINIT,	/* pre-init state */
	PRV_STATE_INIT,		/* init state (restore MIB backup to device) */
	PRV_STATE_READY,	/* driver&device are in operational state */
	PRV_STATE_SLEEP		/* device in sleep mode */
पूर्ण islpci_state_t;

/* ACL using MAC address */
काष्ठा mac_entry अणु
   काष्ठा list_head _list;
   अक्षर addr[ETH_ALEN];
पूर्ण;

काष्ठा islpci_acl अणु
   क्रमागत अणु MAC_POLICY_OPEN=0, MAC_POLICY_ACCEPT=1, MAC_POLICY_REJECT=2 पूर्ण policy;
   काष्ठा list_head mac_list;  /* a list of mac_entry */
   पूर्णांक size;   /* size of queue */
   काष्ठा mutex lock;   /* accessed in ioctls and trap_work */
पूर्ण;

काष्ठा islpci_membuf अणु
	पूर्णांक size;                   /* size of memory */
	व्योम *mem;                  /* address of memory as seen by CPU */
	dma_addr_t pci_addr;        /* address of memory as seen by device */
पूर्ण;

#घोषणा MAX_BSS_WPA_IE_COUNT 64
#घोषणा MAX_WPA_IE_LEN 64
काष्ठा islpci_bss_wpa_ie अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ last_update;
	u8 bssid[ETH_ALEN];
	u8 wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;

पूर्ण;

प्रकार काष्ठा अणु
	spinlock_t slock;	/* generic spinlock; */

	u32 priv_oid;

	/* our mib cache */
	u32 iw_mode;
        काष्ठा rw_semaphore mib_sem;
	व्योम **mib;
	अक्षर nickname[IW_ESSID_MAX_SIZE+1];

	/* Take care of the wireless stats */
	काष्ठा work_काष्ठा stats_work;
	काष्ठा mutex stats_lock;
	/* remember when we last updated the stats */
	अचिन्हित दीर्घ stats_बारtamp;
	/* The first is accessed under semaphore locking.
	 * The second is the clean one we वापस to iwconfig.
	 */
	काष्ठा iw_statistics local_iwstatistics;
	काष्ठा iw_statistics iwstatistics;

	काष्ठा iw_spy_data spy_data; /* iwspy support */

	काष्ठा iw_खुला_data wireless_data;

	पूर्णांक monitor_type; /* ARPHRD_IEEE80211 or ARPHRD_IEEE80211_PRISM */

	काष्ठा islpci_acl acl;

	/* PCI bus allocation & configuration members */
	काष्ठा pci_dev *pdev;	/* PCI काष्ठाure inक्रमmation */
	अक्षर firmware[33];

	व्योम __iomem *device_base;	/* ioremapped device base address */

	/* consistent DMA region */
	व्योम *driver_mem_address;	/* base DMA address */
	dma_addr_t device_host_address;	/* base DMA address (bus address) */
	dma_addr_t device_psm_buffer;	/* host memory क्रम PSM buffering (bus address) */

	/* our network_device काष्ठाure  */
	काष्ठा net_device *ndev;

	/* device queue पूर्णांकerface members */
	काष्ठा isl38xx_cb *control_block;	/* device control block
							   (== driver_mem_address!) */

	/* Each queue has three indexes:
	 *   मुक्त/index_mgmt/data_rx/tx (called index, see below),
	 *   driver_curr_frag, and device_curr_frag (in the control block)
	 * All indexes are ever-increasing, but पूर्णांकerpreted modulo the
	 * device queue size when used.
	 *   index <= device_curr_frag <= driver_curr_frag  at all बार
	 * For rx queues, [index, device_curr_frag) contains fragments
	 * that the पूर्णांकerrupt processing needs to handle (owned by driver).
	 * [device_curr_frag, driver_curr_frag) is the मुक्त space in the
	 * rx queue, रुकोing क्रम data (owned by device).  The driver
	 * increments driver_curr_frag to indicate to the device that more
	 * buffers are available.
	 * If device_curr_frag == driver_curr_frag, no more rx buffers are
	 * available, and the rx DMA engine of the device is halted.
	 * For tx queues, [index, device_curr_frag) contains fragments
	 * where tx is करोne; they need to be मुक्तd (owned by driver).
	 * [device_curr_frag, driver_curr_frag) contains the frames
	 * that are being transferred (owned by device).  The driver
	 * increments driver_curr_frag to indicate that more tx work
	 * needs to be करोne.
	 */
	u32 index_mgmt_rx;              /* real index mgmt rx queue */
	u32 index_mgmt_tx;              /* पढ़ो index mgmt tx queue */
	u32 मुक्त_data_rx;	/* मुक्त poपूर्णांकer data rx queue */
	u32 मुक्त_data_tx;	/* मुक्त poपूर्णांकer data tx queue */
	u32 data_low_tx_full;	/* full detected flag */

	/* frame memory buffers क्रम the device queues */
	काष्ठा islpci_membuf mgmt_tx[ISL38XX_CB_MGMT_QSIZE];
	काष्ठा islpci_membuf mgmt_rx[ISL38XX_CB_MGMT_QSIZE];
	काष्ठा sk_buff *data_low_tx[ISL38XX_CB_TX_QSIZE];
	काष्ठा sk_buff *data_low_rx[ISL38XX_CB_RX_QSIZE];
	dma_addr_t pci_map_tx_address[ISL38XX_CB_TX_QSIZE];
	dma_addr_t pci_map_rx_address[ISL38XX_CB_RX_QSIZE];

	/* रुको क्रम a reset पूर्णांकerrupt */
	रुको_queue_head_t reset_करोne;

	/* used by islpci_mgt_transaction */
	काष्ठा mutex mgmt_lock; /* serialize access to mailbox and wqueue */
	काष्ठा islpci_mgmtframe *mgmt_received;	  /* mbox क्रम incoming frame */
	रुको_queue_head_t mgmt_wqueue;            /* रुकोqueue क्रम mbox */

	/* state machine */
	islpci_state_t state;
	पूर्णांक state_off;		/* क्रमागतeration of off-state, अगर 0 then
				 * we're not in any off-state */

	/* WPA stuff */
	पूर्णांक wpa; /* WPA mode enabled */
	काष्ठा list_head bss_wpa_list;
	पूर्णांक num_bss_wpa;
	काष्ठा mutex wpa_lock;
	u8 wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;

	काष्ठा work_काष्ठा reset_task;
	पूर्णांक reset_task_pending;
पूर्ण islpci_निजी;

अटल अंतरभूत islpci_state_t
islpci_get_state(islpci_निजी *priv)
अणु
	/* lock */
	वापस priv->state;
	/* unlock */
पूर्ण

islpci_state_t islpci_set_state(islpci_निजी *priv, islpci_state_t new_state);

#घोषणा ISLPCI_TX_TIMEOUT               (2*HZ)

irqवापस_t islpci_पूर्णांकerrupt(पूर्णांक, व्योम *);

पूर्णांक prism54_post_setup(islpci_निजी *, पूर्णांक);
पूर्णांक islpci_reset(islpci_निजी *, पूर्णांक);

अटल अंतरभूत व्योम
islpci_trigger(islpci_निजी *priv)
अणु
	isl38xx_trigger_device(islpci_get_state(priv) == PRV_STATE_SLEEP,
			       priv->device_base);
पूर्ण

पूर्णांक islpci_मुक्त_memory(islpci_निजी *);
काष्ठा net_device *islpci_setup(काष्ठा pci_dev *);

#घोषणा DRV_NAME	"prism54"
#घोषणा DRV_VERSION	"1.2"

#पूर्ण_अगर				/* _ISLPCI_DEV_H */
