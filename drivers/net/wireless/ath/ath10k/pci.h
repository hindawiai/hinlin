<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _PCI_H_
#घोषणा _PCI_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>

#समावेश "hw.h"
#समावेश "ce.h"
#समावेश "ahb.h"

/*
 * maximum number of bytes that can be
 * handled atomically by DiagRead/DiagWrite
 */
#घोषणा DIAG_TRANSFER_LIMIT 2048

काष्ठा bmi_xfer अणु
	bool tx_करोne;
	bool rx_करोne;
	bool रुको_क्रम_resp;
	u32 resp_len;
पूर्ण;

/*
 * PCI-specअगरic Target state
 *
 * NOTE: Structure is shared between Host software and Target firmware!
 *
 * Much of this may be of पूर्णांकerest to the Host so
 * HOST_INTEREST->hi_पूर्णांकerconnect_state poपूर्णांकs here
 * (and all members are 32-bit quantities in order to
 * facilitate Host access). In particular, Host software is
 * required to initialize pipe_cfg_addr and svc_to_pipe_map.
 */
काष्ठा pcie_state अणु
	/* Pipe configuration Target address */
	/* NB: ce_pipe_config[CE_COUNT] */
	u32 pipe_cfg_addr;

	/* Service to pipe map Target address */
	/* NB: service_to_pipe[PIPE_TO_CE_MAP_CN] */
	u32 svc_to_pipe_map;

	/* number of MSI पूर्णांकerrupts requested */
	u32 msi_requested;

	/* number of MSI पूर्णांकerrupts granted */
	u32 msi_granted;

	/* Message Signalled Interrupt address */
	u32 msi_addr;

	/* Base data */
	u32 msi_data;

	/*
	 * Data क्रम firmware पूर्णांकerrupt;
	 * MSI data क्रम other पूर्णांकerrupts are
	 * in various SoC रेजिस्टरs
	 */
	u32 msi_fw_पूर्णांकr_data;

	/* PCIE_PWR_METHOD_* */
	u32 घातer_mgmt_method;

	/* PCIE_CONFIG_FLAG_* */
	u32 config_flags;
पूर्ण;

/* PCIE_CONFIG_FLAG definitions */
#घोषणा PCIE_CONFIG_FLAG_ENABLE_L1  0x0000001

/* Per-pipe state. */
काष्ठा ath10k_pci_pipe अणु
	/* Handle of underlying Copy Engine */
	काष्ठा ath10k_ce_pipe *ce_hdl;

	/* Our pipe number; facilitiates use of pipe_info ptrs. */
	u8 pipe_num;

	/* Convenience back poपूर्णांकer to hअगर_ce_state. */
	काष्ठा ath10k *hअगर_ce_state;

	माप_प्रकार buf_sz;

	/* protects compl_मुक्त and num_send_allowed */
	spinlock_t pipe_lock;
पूर्ण;

काष्ठा ath10k_pci_supp_chip अणु
	u32 dev_id;
	u32 rev_id;
पूर्ण;

क्रमागत ath10k_pci_irq_mode अणु
	ATH10K_PCI_IRQ_AUTO = 0,
	ATH10K_PCI_IRQ_LEGACY = 1,
	ATH10K_PCI_IRQ_MSI = 2,
पूर्ण;

काष्ठा ath10k_pci अणु
	काष्ठा pci_dev *pdev;
	काष्ठा device *dev;
	काष्ठा ath10k *ar;
	व्योम __iomem *mem;
	माप_प्रकार mem_len;

	/* Operating पूर्णांकerrupt mode */
	क्रमागत ath10k_pci_irq_mode oper_irq_mode;

	काष्ठा ath10k_pci_pipe pipe_info[CE_COUNT_MAX];

	/* Copy Engine used क्रम Diagnostic Accesses */
	काष्ठा ath10k_ce_pipe *ce_diag;
	/* For protecting ce_diag */
	काष्ठा mutex ce_diag_mutex;

	काष्ठा work_काष्ठा dump_work;

	काष्ठा ath10k_ce ce;
	काष्ठा समयr_list rx_post_retry;

	/* Due to HW quirks it is recommended to disable ASPM during device
	 * bootup. To करो that the original PCI-E Link Control is stored beक्रमe
	 * device bootup is executed and re-programmed later.
	 */
	u16 link_ctl;

	/* Protects ps_awake and ps_wake_refcount */
	spinlock_t ps_lock;

	/* The device has a special घातersave-oriented रेजिस्टर. When device is
	 * considered asleep it drains less घातer and driver is क्रमbidden from
	 * accessing most MMIO रेजिस्टरs. If host were to access them without
	 * waking up the device might scribble over host memory or वापस
	 * 0xdeadbeef पढ़ोouts.
	 */
	अचिन्हित दीर्घ ps_wake_refcount;

	/* Waking up takes some समय (up to 2ms in some हालs) so it can be bad
	 * क्रम latency. To mitigate this the device isn't immediately allowed
	 * to sleep after all references are unकरोne - instead there's a grace
	 * period after which the घातersave रेजिस्टर is updated unless some
	 * activity to/from device happened in the meanसमय.
	 *
	 * Also see comments on ATH10K_PCI_SLEEP_GRACE_PERIOD_MSEC.
	 */
	काष्ठा समयr_list ps_समयr;

	/* MMIO रेजिस्टरs are used to communicate with the device. With
	 * पूर्णांकensive traffic accessing घातersave रेजिस्टर would be a bit
	 * wasteful overhead and would needlessly stall CPU. It is far more
	 * efficient to rely on a variable in RAM and update it only upon
	 * घातersave रेजिस्टर state changes.
	 */
	bool ps_awake;

	/* pci घातer save, disable क्रम QCA988X and QCA99X0.
	 * Writing 'false' to this variable aव्योमs frequent locking
	 * on MMIO पढ़ो/ग_लिखो.
	 */
	bool pci_ps;

	/* Chip specअगरic pci reset routine used to करो a safe reset */
	पूर्णांक (*pci_soft_reset)(काष्ठा ath10k *ar);

	/* Chip specअगरic pci full reset function */
	पूर्णांक (*pci_hard_reset)(काष्ठा ath10k *ar);

	/* chip specअगरic methods क्रम converting target CPU भव address
	 * space to CE address space
	 */
	u32 (*targ_cpu_to_ce_addr)(काष्ठा ath10k *ar, u32 addr);

	काष्ठा ce_attr *attr;
	काष्ठा ce_pipe_config *pipe_config;
	काष्ठा ce_service_to_pipe *serv_to_pipe;

	/* Keep this entry in the last, memory क्रम काष्ठा ath10k_ahb is
	 * allocated (ahb support enabled हाल) in the continuation of
	 * this काष्ठा.
	 */
	काष्ठा ath10k_ahb ahb[];

पूर्ण;

अटल अंतरभूत काष्ठा ath10k_pci *ath10k_pci_priv(काष्ठा ath10k *ar)
अणु
	वापस (काष्ठा ath10k_pci *)ar->drv_priv;
पूर्ण

#घोषणा ATH10K_PCI_RX_POST_RETRY_MS 50
#घोषणा ATH_PCI_RESET_WAIT_MAX 10 /* ms */
#घोषणा PCIE_WAKE_TIMEOUT 30000	/* 30ms */
#घोषणा PCIE_WAKE_LATE_US 10000	/* 10ms */

#घोषणा BAR_NUM 0

#घोषणा CDC_WAR_MAGIC_STR   0xceef0000
#घोषणा CDC_WAR_DATA_CE     4

/* Wait up to this many Ms क्रम a Diagnostic Access CE operation to complete */
#घोषणा DIAG_ACCESS_CE_TIMEOUT_US 10000 /* 10 ms */
#घोषणा DIAG_ACCESS_CE_WAIT_US	50

व्योम ath10k_pci_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value);
व्योम ath10k_pci_soc_ग_लिखो32(काष्ठा ath10k *ar, u32 addr, u32 val);
व्योम ath10k_pci_reg_ग_लिखो32(काष्ठा ath10k *ar, u32 addr, u32 val);

u32 ath10k_pci_पढ़ो32(काष्ठा ath10k *ar, u32 offset);
u32 ath10k_pci_soc_पढ़ो32(काष्ठा ath10k *ar, u32 addr);
u32 ath10k_pci_reg_पढ़ो32(काष्ठा ath10k *ar, u32 addr);

पूर्णांक ath10k_pci_hअगर_tx_sg(काष्ठा ath10k *ar, u8 pipe_id,
			 काष्ठा ath10k_hअगर_sg_item *items, पूर्णांक n_items);
पूर्णांक ath10k_pci_hअगर_diag_पढ़ो(काष्ठा ath10k *ar, u32 address, व्योम *buf,
			     माप_प्रकार buf_len);
पूर्णांक ath10k_pci_diag_ग_लिखो_mem(काष्ठा ath10k *ar, u32 address,
			      स्थिर व्योम *data, पूर्णांक nbytes);
पूर्णांक ath10k_pci_hअगर_exchange_bmi_msg(काष्ठा ath10k *ar, व्योम *req, u32 req_len,
				    व्योम *resp, u32 *resp_len);
पूर्णांक ath10k_pci_hअगर_map_service_to_pipe(काष्ठा ath10k *ar, u16 service_id,
				       u8 *ul_pipe, u8 *dl_pipe);
व्योम ath10k_pci_hअगर_get_शेष_pipe(काष्ठा ath10k *ar, u8 *ul_pipe,
				     u8 *dl_pipe);
व्योम ath10k_pci_hअगर_send_complete_check(काष्ठा ath10k *ar, u8 pipe,
					पूर्णांक क्रमce);
u16 ath10k_pci_hअगर_get_मुक्त_queue_number(काष्ठा ath10k *ar, u8 pipe);
व्योम ath10k_pci_hअगर_घातer_करोwn(काष्ठा ath10k *ar);
पूर्णांक ath10k_pci_alloc_pipes(काष्ठा ath10k *ar);
व्योम ath10k_pci_मुक्त_pipes(काष्ठा ath10k *ar);
व्योम ath10k_pci_मुक्त_pipes(काष्ठा ath10k *ar);
व्योम ath10k_pci_rx_replenish_retry(काष्ठा समयr_list *t);
व्योम ath10k_pci_ce_deinit(काष्ठा ath10k *ar);
व्योम ath10k_pci_init_napi(काष्ठा ath10k *ar);
पूर्णांक ath10k_pci_init_pipes(काष्ठा ath10k *ar);
पूर्णांक ath10k_pci_init_config(काष्ठा ath10k *ar);
व्योम ath10k_pci_rx_post(काष्ठा ath10k *ar);
व्योम ath10k_pci_flush(काष्ठा ath10k *ar);
व्योम ath10k_pci_enable_legacy_irq(काष्ठा ath10k *ar);
bool ath10k_pci_irq_pending(काष्ठा ath10k *ar);
व्योम ath10k_pci_disable_and_clear_legacy_irq(काष्ठा ath10k *ar);
व्योम ath10k_pci_irq_msi_fw_mask(काष्ठा ath10k *ar);
पूर्णांक ath10k_pci_रुको_क्रम_target_init(काष्ठा ath10k *ar);
पूर्णांक ath10k_pci_setup_resource(काष्ठा ath10k *ar);
व्योम ath10k_pci_release_resource(काष्ठा ath10k *ar);

/* QCA6174 is known to have Tx/Rx issues when SOC_WAKE रेजिस्टर is poked too
 * frequently. To aव्योम this put SoC to sleep after a very conservative grace
 * period. Adjust with great care.
 */
#घोषणा ATH10K_PCI_SLEEP_GRACE_PERIOD_MSEC 60

#पूर्ण_अगर /* _PCI_H_ */
