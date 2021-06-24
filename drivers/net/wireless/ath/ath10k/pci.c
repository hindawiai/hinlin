<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "coredump.h"

#समावेश "targaddrs.h"
#समावेश "bmi.h"

#समावेश "hif.h"
#समावेश "htc.h"

#समावेश "ce.h"
#समावेश "pci.h"

क्रमागत ath10k_pci_reset_mode अणु
	ATH10K_PCI_RESET_AUTO = 0,
	ATH10K_PCI_RESET_WARM_ONLY = 1,
पूर्ण;

अटल अचिन्हित पूर्णांक ath10k_pci_irq_mode = ATH10K_PCI_IRQ_AUTO;
अटल अचिन्हित पूर्णांक ath10k_pci_reset_mode = ATH10K_PCI_RESET_AUTO;

module_param_named(irq_mode, ath10k_pci_irq_mode, uपूर्णांक, 0644);
MODULE_PARM_DESC(irq_mode, "0: auto, 1: legacy, 2: msi (default: 0)");

module_param_named(reset_mode, ath10k_pci_reset_mode, uपूर्णांक, 0644);
MODULE_PARM_DESC(reset_mode, "0: auto, 1: warm only (default: 0)");

/* how दीर्घ रुको to रुको क्रम target to initialise, in ms */
#घोषणा ATH10K_PCI_TARGET_WAIT 3000
#घोषणा ATH10K_PCI_NUM_WARM_RESET_ATTEMPTS 3

/* Maximum number of bytes that can be handled atomically by
 * diag पढ़ो and ग_लिखो.
 */
#घोषणा ATH10K_DIAG_TRANSFER_LIMIT	0x5000

#घोषणा QCA99X0_PCIE_BAR0_START_REG    0x81030
#घोषणा QCA99X0_CPU_MEM_ADDR_REG       0x4d00c
#घोषणा QCA99X0_CPU_MEM_DATA_REG       0x4d010

अटल स्थिर काष्ठा pci_device_id ath10k_pci_id_table[] = अणु
	/* PCI-E QCA988X V2 (Ubiquiti bअक्रमed) */
	अणु PCI_VDEVICE(UBIQUITI, QCA988X_2_0_DEVICE_ID_UBNT) पूर्ण,

	अणु PCI_VDEVICE(ATHEROS, QCA988X_2_0_DEVICE_ID) पूर्ण, /* PCI-E QCA988X V2 */
	अणु PCI_VDEVICE(ATHEROS, QCA6164_2_1_DEVICE_ID) पूर्ण, /* PCI-E QCA6164 V2.1 */
	अणु PCI_VDEVICE(ATHEROS, QCA6174_2_1_DEVICE_ID) पूर्ण, /* PCI-E QCA6174 V2.1 */
	अणु PCI_VDEVICE(ATHEROS, QCA99X0_2_0_DEVICE_ID) पूर्ण, /* PCI-E QCA99X0 V2 */
	अणु PCI_VDEVICE(ATHEROS, QCA9888_2_0_DEVICE_ID) पूर्ण, /* PCI-E QCA9888 V2 */
	अणु PCI_VDEVICE(ATHEROS, QCA9984_1_0_DEVICE_ID) पूर्ण, /* PCI-E QCA9984 V1 */
	अणु PCI_VDEVICE(ATHEROS, QCA9377_1_0_DEVICE_ID) पूर्ण, /* PCI-E QCA9377 V1 */
	अणु PCI_VDEVICE(ATHEROS, QCA9887_1_0_DEVICE_ID) पूर्ण, /* PCI-E QCA9887 */
	अणु0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ath10k_pci_supp_chip ath10k_pci_supp_chips[] = अणु
	/* QCA988X pre 2.0 chips are not supported because they need some nasty
	 * hacks. ath10k करोesn't have them and these devices crash horribly
	 * because of that.
	 */
	अणु QCA988X_2_0_DEVICE_ID_UBNT, QCA988X_HW_2_0_CHIP_ID_REV पूर्ण,
	अणु QCA988X_2_0_DEVICE_ID, QCA988X_HW_2_0_CHIP_ID_REV पूर्ण,

	अणु QCA6164_2_1_DEVICE_ID, QCA6174_HW_2_1_CHIP_ID_REV पूर्ण,
	अणु QCA6164_2_1_DEVICE_ID, QCA6174_HW_2_2_CHIP_ID_REV पूर्ण,
	अणु QCA6164_2_1_DEVICE_ID, QCA6174_HW_3_0_CHIP_ID_REV पूर्ण,
	अणु QCA6164_2_1_DEVICE_ID, QCA6174_HW_3_1_CHIP_ID_REV पूर्ण,
	अणु QCA6164_2_1_DEVICE_ID, QCA6174_HW_3_2_CHIP_ID_REV पूर्ण,

	अणु QCA6174_2_1_DEVICE_ID, QCA6174_HW_2_1_CHIP_ID_REV पूर्ण,
	अणु QCA6174_2_1_DEVICE_ID, QCA6174_HW_2_2_CHIP_ID_REV पूर्ण,
	अणु QCA6174_2_1_DEVICE_ID, QCA6174_HW_3_0_CHIP_ID_REV पूर्ण,
	अणु QCA6174_2_1_DEVICE_ID, QCA6174_HW_3_1_CHIP_ID_REV पूर्ण,
	अणु QCA6174_2_1_DEVICE_ID, QCA6174_HW_3_2_CHIP_ID_REV पूर्ण,

	अणु QCA99X0_2_0_DEVICE_ID, QCA99X0_HW_2_0_CHIP_ID_REV पूर्ण,

	अणु QCA9984_1_0_DEVICE_ID, QCA9984_HW_1_0_CHIP_ID_REV पूर्ण,

	अणु QCA9888_2_0_DEVICE_ID, QCA9888_HW_2_0_CHIP_ID_REV पूर्ण,

	अणु QCA9377_1_0_DEVICE_ID, QCA9377_HW_1_0_CHIP_ID_REV पूर्ण,
	अणु QCA9377_1_0_DEVICE_ID, QCA9377_HW_1_1_CHIP_ID_REV पूर्ण,

	अणु QCA9887_1_0_DEVICE_ID, QCA9887_HW_1_0_CHIP_ID_REV पूर्ण,
पूर्ण;

अटल व्योम ath10k_pci_buffer_cleanup(काष्ठा ath10k *ar);
अटल पूर्णांक ath10k_pci_cold_reset(काष्ठा ath10k *ar);
अटल पूर्णांक ath10k_pci_safe_chip_reset(काष्ठा ath10k *ar);
अटल पूर्णांक ath10k_pci_init_irq(काष्ठा ath10k *ar);
अटल पूर्णांक ath10k_pci_deinit_irq(काष्ठा ath10k *ar);
अटल पूर्णांक ath10k_pci_request_irq(काष्ठा ath10k *ar);
अटल व्योम ath10k_pci_मुक्त_irq(काष्ठा ath10k *ar);
अटल पूर्णांक ath10k_pci_bmi_रुको(काष्ठा ath10k *ar,
			       काष्ठा ath10k_ce_pipe *tx_pipe,
			       काष्ठा ath10k_ce_pipe *rx_pipe,
			       काष्ठा bmi_xfer *xfer);
अटल पूर्णांक ath10k_pci_qca99x0_chip_reset(काष्ठा ath10k *ar);
अटल व्योम ath10k_pci_htc_tx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_pci_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_pci_htt_tx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_pci_htt_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_pci_htt_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);
अटल व्योम ath10k_pci_pktlog_rx_cb(काष्ठा ath10k_ce_pipe *ce_state);

अटल स्थिर काष्ठा ce_attr pci_host_ce_config_wlan[] = अणु
	/* CE0: host->target HTC control and raw streams */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 16,
		.src_sz_max = 256,
		.dest_nentries = 0,
		.send_cb = ath10k_pci_htc_tx_cb,
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 512,
		.recv_cb = ath10k_pci_htt_htc_rx_cb,
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 128,
		.recv_cb = ath10k_pci_htc_rx_cb,
	पूर्ण,

	/* CE3: host->target WMI */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 32,
		.src_sz_max = 2048,
		.dest_nentries = 0,
		.send_cb = ath10k_pci_htc_tx_cb,
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_DIS_INTR,
		.src_nentries = CE_HTT_H2T_MSG_SRC_NENTRIES,
		.src_sz_max = 256,
		.dest_nentries = 0,
		.send_cb = ath10k_pci_htt_tx_cb,
	पूर्ण,

	/* CE5: target->host HTT (HIF->HTT) */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 512,
		.dest_nentries = 512,
		.recv_cb = ath10k_pci_htt_rx_cb,
	पूर्ण,

	/* CE6: target स्वतःnomous hअगर_स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE7: ce_diag, the Diagnostic Winकरोw */
	अणु
		.flags = CE_ATTR_FLAGS | CE_ATTR_POLL,
		.src_nentries = 2,
		.src_sz_max = DIAG_TRANSFER_LIMIT,
		.dest_nentries = 2,
	पूर्ण,

	/* CE8: target->host pktlog */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 2048,
		.dest_nentries = 128,
		.recv_cb = ath10k_pci_pktlog_rx_cb,
	पूर्ण,

	/* CE9 target स्वतःnomous qcache स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE10: target स्वतःnomous hअगर स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,

	/* CE11: target स्वतःnomous hअगर स_नकल */
	अणु
		.flags = CE_ATTR_FLAGS,
		.src_nentries = 0,
		.src_sz_max = 0,
		.dest_nentries = 0,
	पूर्ण,
पूर्ण;

/* Target firmware's Copy Engine configuration. */
अटल स्थिर काष्ठा ce_pipe_config pci_target_ce_config_wlan[] = अणु
	/* CE0: host->target HTC control and raw streams */
	अणु
		.pipक्रमागत = __cpu_to_le32(0),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(256),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE1: target->host HTT + HTC control */
	अणु
		.pipक्रमागत = __cpu_to_le32(1),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE2: target->host WMI */
	अणु
		.pipक्रमागत = __cpu_to_le32(2),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(64),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE3: host->target WMI */
	अणु
		.pipक्रमागत = __cpu_to_le32(3),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE4: host->target HTT */
	अणु
		.pipक्रमागत = __cpu_to_le32(4),
		.pipedir = __cpu_to_le32(PIPEसूची_OUT),
		.nentries = __cpu_to_le32(256),
		.nbytes_max = __cpu_to_le32(256),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* NB: 50% of src nentries, since tx has 2 frags */

	/* CE5: target->host HTT (HIF->HTT) */
	अणु
		.pipक्रमागत = __cpu_to_le32(5),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(512),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE6: Reserved क्रम target स्वतःnomous hअगर_स_नकल */
	अणु
		.pipक्रमागत = __cpu_to_le32(6),
		.pipedir = __cpu_to_le32(PIPEसूची_INOUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(4096),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE7 used only by Host */
	अणु
		.pipक्रमागत = __cpu_to_le32(7),
		.pipedir = __cpu_to_le32(PIPEसूची_INOUT),
		.nentries = __cpu_to_le32(0),
		.nbytes_max = __cpu_to_le32(0),
		.flags = __cpu_to_le32(0),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE8 target->host packtlog */
	अणु
		.pipक्रमागत = __cpu_to_le32(8),
		.pipedir = __cpu_to_le32(PIPEसूची_IN),
		.nentries = __cpu_to_le32(64),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* CE9 target स्वतःnomous qcache स_नकल */
	अणु
		.pipक्रमागत = __cpu_to_le32(9),
		.pipedir = __cpu_to_le32(PIPEसूची_INOUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	पूर्ण,

	/* It not necessary to send target wlan configuration क्रम CE10 & CE11
	 * as these CEs are not actively used in target.
	 */
पूर्ण;

/*
 * Map from service/endpoपूर्णांक to Copy Engine.
 * This table is derived from the CE_PCI TABLE, above.
 * It is passed to the Target at startup क्रम use by firmware.
 */
अटल स्थिर काष्ठा ce_service_to_pipe pci_target_service_to_ce_map_wlan[] = अणु
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_CONTROL),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_WMI_CONTROL),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_RSVD_CTRL),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(0),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_RSVD_CTRL),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(1),
	पूर्ण,
	अणु /* not used */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(0),
	पूर्ण,
	अणु /* not used */
		__cpu_to_le32(ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(1),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_le32(PIPEसूची_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(4),
	पूर्ण,
	अणु
		__cpu_to_le32(ATH10K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_le32(PIPEसूची_IN),	/* in = DL = target -> host */
		__cpu_to_le32(5),
	पूर्ण,

	/* (Additions here) */

	अणु /* must be last */
		__cpu_to_le32(0),
		__cpu_to_le32(0),
		__cpu_to_le32(0),
	पूर्ण,
पूर्ण;

अटल bool ath10k_pci_is_awake(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 val = ioपढ़ो32(ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
			   RTC_STATE_ADDRESS);

	वापस RTC_STATE_V_GET(val) == RTC_STATE_V_ON;
पूर्ण

अटल व्योम __ath10k_pci_wake(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	lockdep_निश्चित_held(&ar_pci->ps_lock);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps wake reg refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	ioग_लिखो32(PCIE_SOC_WAKE_V_MASK,
		  ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
		  PCIE_SOC_WAKE_ADDRESS);
पूर्ण

अटल व्योम __ath10k_pci_sleep(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	lockdep_निश्चित_held(&ar_pci->ps_lock);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps sleep reg refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	ioग_लिखो32(PCIE_SOC_WAKE_RESET,
		  ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
		  PCIE_SOC_WAKE_ADDRESS);
	ar_pci->ps_awake = false;
पूर्ण

अटल पूर्णांक ath10k_pci_wake_रुको(काष्ठा ath10k *ar)
अणु
	पूर्णांक tot_delay = 0;
	पूर्णांक curr_delay = 5;

	जबतक (tot_delay < PCIE_WAKE_TIMEOUT) अणु
		अगर (ath10k_pci_is_awake(ar)) अणु
			अगर (tot_delay > PCIE_WAKE_LATE_US)
				ath10k_warn(ar, "device wakeup took %d ms which is unusually long, otherwise it works normally.\n",
					    tot_delay / 1000);
			वापस 0;
		पूर्ण

		udelay(curr_delay);
		tot_delay += curr_delay;

		अगर (curr_delay < 50)
			curr_delay += 5;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ath10k_pci_क्रमce_wake(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (ar_pci->pci_ps)
		वापस ret;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	अगर (!ar_pci->ps_awake) अणु
		ioग_लिखो32(PCIE_SOC_WAKE_V_MASK,
			  ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
			  PCIE_SOC_WAKE_ADDRESS);

		ret = ath10k_pci_wake_रुको(ar);
		अगर (ret == 0)
			ar_pci->ps_awake = true;
	पूर्ण

	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ath10k_pci_क्रमce_sleep(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	ioग_लिखो32(PCIE_SOC_WAKE_RESET,
		  ar_pci->mem + PCIE_LOCAL_BASE_ADDRESS +
		  PCIE_SOC_WAKE_ADDRESS);
	ar_pci->ps_awake = false;

	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
पूर्ण

अटल पूर्णांक ath10k_pci_wake(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (ar_pci->pci_ps == 0)
		वापस ret;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps wake refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	/* This function can be called very frequently. To aव्योम excessive
	 * CPU stalls क्रम MMIO पढ़ोs use a cache var to hold the device state.
	 */
	अगर (!ar_pci->ps_awake) अणु
		__ath10k_pci_wake(ar);

		ret = ath10k_pci_wake_रुको(ar);
		अगर (ret == 0)
			ar_pci->ps_awake = true;
	पूर्ण

	अगर (ret == 0) अणु
		ar_pci->ps_wake_refcount++;
		WARN_ON(ar_pci->ps_wake_refcount == 0);
	पूर्ण

	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ath10k_pci_sleep(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ flags;

	अगर (ar_pci->pci_ps == 0)
		वापस;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps sleep refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	अगर (WARN_ON(ar_pci->ps_wake_refcount == 0))
		जाओ skip;

	ar_pci->ps_wake_refcount--;

	mod_समयr(&ar_pci->ps_समयr, jअगरfies +
		  msecs_to_jअगरfies(ATH10K_PCI_SLEEP_GRACE_PERIOD_MSEC));

skip:
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
पूर्ण

अटल व्योम ath10k_pci_ps_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath10k_pci *ar_pci = from_समयr(ar_pci, t, ps_समयr);
	काष्ठा ath10k *ar = ar_pci->ar;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ar_pci->ps_lock, flags);

	ath10k_dbg(ar, ATH10K_DBG_PCI_PS, "pci ps timer refcount %lu awake %d\n",
		   ar_pci->ps_wake_refcount, ar_pci->ps_awake);

	अगर (ar_pci->ps_wake_refcount > 0)
		जाओ skip;

	__ath10k_pci_sleep(ar);

skip:
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
पूर्ण

अटल व्योम ath10k_pci_sleep_sync(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ flags;

	अगर (ar_pci->pci_ps == 0) अणु
		ath10k_pci_क्रमce_sleep(ar);
		वापस;
	पूर्ण

	del_समयr_sync(&ar_pci->ps_समयr);

	spin_lock_irqsave(&ar_pci->ps_lock, flags);
	WARN_ON(ar_pci->ps_wake_refcount > 0);
	__ath10k_pci_sleep(ar);
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
पूर्ण

अटल व्योम ath10k_bus_pci_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret;

	अगर (unlikely(offset + माप(value) > ar_pci->mem_len)) अणु
		ath10k_warn(ar, "refusing to write mmio out of bounds at 0x%08x - 0x%08zx (max 0x%08zx)\n",
			    offset, offset + माप(value), ar_pci->mem_len);
		वापस;
	पूर्ण

	ret = ath10k_pci_wake(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wake target for write32 of 0x%08x at 0x%08x: %d\n",
			    value, offset, ret);
		वापस;
	पूर्ण

	ioग_लिखो32(value, ar_pci->mem + offset);
	ath10k_pci_sleep(ar);
पूर्ण

अटल u32 ath10k_bus_pci_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 val;
	पूर्णांक ret;

	अगर (unlikely(offset + माप(val) > ar_pci->mem_len)) अणु
		ath10k_warn(ar, "refusing to read mmio out of bounds at 0x%08x - 0x%08zx (max 0x%08zx)\n",
			    offset, offset + माप(val), ar_pci->mem_len);
		वापस 0;
	पूर्ण

	ret = ath10k_pci_wake(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wake target for read32 at 0x%08x: %d\n",
			    offset, ret);
		वापस 0xffffffff;
	पूर्ण

	val = ioपढ़ो32(ar_pci->mem + offset);
	ath10k_pci_sleep(ar);

	वापस val;
पूर्ण

अंतरभूत व्योम ath10k_pci_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	ce->bus_ops->ग_लिखो32(ar, offset, value);
पूर्ण

अंतरभूत u32 ath10k_pci_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	वापस ce->bus_ops->पढ़ो32(ar, offset);
पूर्ण

u32 ath10k_pci_soc_पढ़ो32(काष्ठा ath10k *ar, u32 addr)
अणु
	वापस ath10k_pci_पढ़ो32(ar, RTC_SOC_BASE_ADDRESS + addr);
पूर्ण

व्योम ath10k_pci_soc_ग_लिखो32(काष्ठा ath10k *ar, u32 addr, u32 val)
अणु
	ath10k_pci_ग_लिखो32(ar, RTC_SOC_BASE_ADDRESS + addr, val);
पूर्ण

u32 ath10k_pci_reg_पढ़ो32(काष्ठा ath10k *ar, u32 addr)
अणु
	वापस ath10k_pci_पढ़ो32(ar, PCIE_LOCAL_BASE_ADDRESS + addr);
पूर्ण

व्योम ath10k_pci_reg_ग_लिखो32(काष्ठा ath10k *ar, u32 addr, u32 val)
अणु
	ath10k_pci_ग_लिखो32(ar, PCIE_LOCAL_BASE_ADDRESS + addr, val);
पूर्ण

bool ath10k_pci_irq_pending(काष्ठा ath10k *ar)
अणु
	u32 cause;

	/* Check अगर the shared legacy irq is क्रम us */
	cause = ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS +
				  PCIE_INTR_CAUSE_ADDRESS);
	अगर (cause & (PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL))
		वापस true;

	वापस false;
पूर्ण

व्योम ath10k_pci_disable_and_clear_legacy_irq(काष्ठा ath10k *ar)
अणु
	/* IMPORTANT: INTR_CLR रेजिस्टर has to be set after
	 * INTR_ENABLE is set to 0, otherwise पूर्णांकerrupt can not be
	 * really cleared.
	 */
	ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS + PCIE_INTR_ENABLE_ADDRESS,
			   0);
	ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS + PCIE_INTR_CLR_ADDRESS,
			   PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL);

	/* IMPORTANT: this extra पढ़ो transaction is required to
	 * flush the posted ग_लिखो buffer.
	 */
	(व्योम)ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS +
				PCIE_INTR_ENABLE_ADDRESS);
पूर्ण

व्योम ath10k_pci_enable_legacy_irq(काष्ठा ath10k *ar)
अणु
	ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS +
			   PCIE_INTR_ENABLE_ADDRESS,
			   PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL);

	/* IMPORTANT: this extra पढ़ो transaction is required to
	 * flush the posted ग_लिखो buffer.
	 */
	(व्योम)ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS +
				PCIE_INTR_ENABLE_ADDRESS);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *ath10k_pci_get_irq_method(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	अगर (ar_pci->oper_irq_mode == ATH10K_PCI_IRQ_MSI)
		वापस "msi";

	वापस "legacy";
पूर्ण

अटल पूर्णांक __ath10k_pci_rx_post_buf(काष्ठा ath10k_pci_pipe *pipe)
अणु
	काष्ठा ath10k *ar = pipe->hअगर_ce_state;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_pipe = pipe->ce_hdl;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक ret;

	skb = dev_alloc_skb(pipe->buf_sz);
	अगर (!skb)
		वापस -ENOMEM;

	WARN_ONCE((अचिन्हित दीर्घ)skb->data & 3, "unaligned skb");

	paddr = dma_map_single(ar->dev, skb->data,
			       skb->len + skb_tailroom(skb),
			       DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(ar->dev, paddr))) अणु
		ath10k_warn(ar, "failed to dma map pci rx buf\n");
		dev_kमुक्त_skb_any(skb);
		वापस -EIO;
	पूर्ण

	ATH10K_SKB_RXCB(skb)->paddr = paddr;

	spin_lock_bh(&ce->ce_lock);
	ret = ce_pipe->ops->ce_rx_post_buf(ce_pipe, skb, paddr);
	spin_unlock_bh(&ce->ce_lock);
	अगर (ret) अणु
		dma_unmap_single(ar->dev, paddr, skb->len + skb_tailroom(skb),
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_pci_rx_post_pipe(काष्ठा ath10k_pci_pipe *pipe)
अणु
	काष्ठा ath10k *ar = pipe->hअगर_ce_state;
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_pipe = pipe->ce_hdl;
	पूर्णांक ret, num;

	अगर (pipe->buf_sz == 0)
		वापस;

	अगर (!ce_pipe->dest_ring)
		वापस;

	spin_lock_bh(&ce->ce_lock);
	num = __ath10k_ce_rx_num_मुक्त_bufs(ce_pipe);
	spin_unlock_bh(&ce->ce_lock);

	जबतक (num >= 0) अणु
		ret = __ath10k_pci_rx_post_buf(pipe);
		अगर (ret) अणु
			अगर (ret == -ENOSPC)
				अवरोध;
			ath10k_warn(ar, "failed to post pci rx buf: %d\n", ret);
			mod_समयr(&ar_pci->rx_post_retry, jअगरfies +
				  ATH10K_PCI_RX_POST_RETRY_MS);
			अवरोध;
		पूर्ण
		num--;
	पूर्ण
पूर्ण

व्योम ath10k_pci_rx_post(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक i;

	क्रम (i = 0; i < CE_COUNT; i++)
		ath10k_pci_rx_post_pipe(&ar_pci->pipe_info[i]);
पूर्ण

व्योम ath10k_pci_rx_replenish_retry(काष्ठा समयr_list *t)
अणु
	काष्ठा ath10k_pci *ar_pci = from_समयr(ar_pci, t, rx_post_retry);
	काष्ठा ath10k *ar = ar_pci->ar;

	ath10k_pci_rx_post(ar);
पूर्ण

अटल u32 ath10k_pci_qca988x_targ_cpu_to_ce_addr(काष्ठा ath10k *ar, u32 addr)
अणु
	u32 val = 0, region = addr & 0xfffff;

	val = (ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS + CORE_CTRL_ADDRESS)
				 & 0x7ff) << 21;
	val |= 0x100000 | region;
	वापस val;
पूर्ण

/* Refactor from ath10k_pci_qca988x_targ_cpu_to_ce_addr.
 * Support to access target space below 1M क्रम qca6174 and qca9377.
 * If target space is below 1M, the bit[20] of converted CE addr is 0.
 * Otherwise bit[20] of converted CE addr is 1.
 */
अटल u32 ath10k_pci_qca6174_targ_cpu_to_ce_addr(काष्ठा ath10k *ar, u32 addr)
अणु
	u32 val = 0, region = addr & 0xfffff;

	val = (ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS + CORE_CTRL_ADDRESS)
				 & 0x7ff) << 21;
	val |= ((addr >= 0x100000) ? 0x100000 : 0) | region;
	वापस val;
पूर्ण

अटल u32 ath10k_pci_qca99x0_targ_cpu_to_ce_addr(काष्ठा ath10k *ar, u32 addr)
अणु
	u32 val = 0, region = addr & 0xfffff;

	val = ath10k_pci_पढ़ो32(ar, PCIE_BAR_REG_ADDRESS);
	val |= 0x100000 | region;
	वापस val;
पूर्ण

अटल u32 ath10k_pci_targ_cpu_to_ce_addr(काष्ठा ath10k *ar, u32 addr)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	अगर (WARN_ON_ONCE(!ar_pci->targ_cpu_to_ce_addr))
		वापस -ENOTSUPP;

	वापस ar_pci->targ_cpu_to_ce_addr(ar, addr);
पूर्ण

/*
 * Diagnostic पढ़ो/ग_लिखो access is provided क्रम startup/config/debug usage.
 * Caller must guarantee proper alignment, when applicable, and single user
 * at any moment.
 */
अटल पूर्णांक ath10k_pci_diag_पढ़ो_mem(काष्ठा ath10k *ar, u32 address, व्योम *data,
				    पूर्णांक nbytes)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret = 0;
	u32 *buf;
	अचिन्हित पूर्णांक completed_nbytes, alloc_nbytes, reमुख्यing_bytes;
	काष्ठा ath10k_ce_pipe *ce_diag;
	/* Host buffer address in CE space */
	u32 ce_data;
	dma_addr_t ce_data_base = 0;
	व्योम *data_buf;
	पूर्णांक i;

	mutex_lock(&ar_pci->ce_diag_mutex);
	ce_diag = ar_pci->ce_diag;

	/*
	 * Allocate a temporary bounce buffer to hold caller's data
	 * to be DMA'ed from Target. This guarantees
	 *   1) 4-byte alignment
	 *   2) Buffer in DMA-able space
	 */
	alloc_nbytes = min_t(अचिन्हित पूर्णांक, nbytes, DIAG_TRANSFER_LIMIT);

	data_buf = dma_alloc_coherent(ar->dev, alloc_nbytes, &ce_data_base,
				      GFP_ATOMIC);
	अगर (!data_buf) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* The address supplied by the caller is in the
	 * Target CPU भव address space.
	 *
	 * In order to use this address with the diagnostic CE,
	 * convert it from Target CPU भव address space
	 * to CE address space
	 */
	address = ath10k_pci_targ_cpu_to_ce_addr(ar, address);

	reमुख्यing_bytes = nbytes;
	ce_data = ce_data_base;
	जबतक (reमुख्यing_bytes) अणु
		nbytes = min_t(अचिन्हित पूर्णांक, reमुख्यing_bytes,
			       DIAG_TRANSFER_LIMIT);

		ret = ath10k_ce_rx_post_buf(ce_diag, &ce_data, ce_data);
		अगर (ret != 0)
			जाओ करोne;

		/* Request CE to send from Target(!) address to Host buffer */
		ret = ath10k_ce_send(ce_diag, शून्य, (u32)address, nbytes, 0, 0);
		अगर (ret)
			जाओ करोne;

		i = 0;
		जबतक (ath10k_ce_completed_send_next(ce_diag, शून्य) != 0) अणु
			udelay(DIAG_ACCESS_CE_WAIT_US);
			i += DIAG_ACCESS_CE_WAIT_US;

			अगर (i > DIAG_ACCESS_CE_TIMEOUT_US) अणु
				ret = -EBUSY;
				जाओ करोne;
			पूर्ण
		पूर्ण

		i = 0;
		जबतक (ath10k_ce_completed_recv_next(ce_diag, (व्योम **)&buf,
						     &completed_nbytes) != 0) अणु
			udelay(DIAG_ACCESS_CE_WAIT_US);
			i += DIAG_ACCESS_CE_WAIT_US;

			अगर (i > DIAG_ACCESS_CE_TIMEOUT_US) अणु
				ret = -EBUSY;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (nbytes != completed_nbytes) अणु
			ret = -EIO;
			जाओ करोne;
		पूर्ण

		अगर (*buf != ce_data) अणु
			ret = -EIO;
			जाओ करोne;
		पूर्ण

		reमुख्यing_bytes -= nbytes;
		स_नकल(data, data_buf, nbytes);

		address += nbytes;
		data += nbytes;
	पूर्ण

करोne:

	अगर (data_buf)
		dma_मुक्त_coherent(ar->dev, alloc_nbytes, data_buf,
				  ce_data_base);

	mutex_unlock(&ar_pci->ce_diag_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_pci_diag_पढ़ो32(काष्ठा ath10k *ar, u32 address, u32 *value)
अणु
	__le32 val = 0;
	पूर्णांक ret;

	ret = ath10k_pci_diag_पढ़ो_mem(ar, address, &val, माप(val));
	*value = __le32_to_cpu(val);

	वापस ret;
पूर्ण

अटल पूर्णांक __ath10k_pci_diag_पढ़ो_hi(काष्ठा ath10k *ar, व्योम *dest,
				     u32 src, u32 len)
अणु
	u32 host_addr, addr;
	पूर्णांक ret;

	host_addr = host_पूर्णांकerest_item_address(src);

	ret = ath10k_pci_diag_पढ़ो32(ar, host_addr, &addr);
	अगर (ret != 0) अणु
		ath10k_warn(ar, "failed to get memcpy hi address for firmware address %d: %d\n",
			    src, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_diag_पढ़ो_mem(ar, addr, dest, len);
	अगर (ret != 0) अणु
		ath10k_warn(ar, "failed to memcpy firmware memory from %d (%d B): %d\n",
			    addr, len, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ath10k_pci_diag_पढ़ो_hi(ar, dest, src, len)		\
	__ath10k_pci_diag_पढ़ो_hi(ar, dest, HI_ITEM(src), len)

पूर्णांक ath10k_pci_diag_ग_लिखो_mem(काष्ठा ath10k *ar, u32 address,
			      स्थिर व्योम *data, पूर्णांक nbytes)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret = 0;
	u32 *buf;
	अचिन्हित पूर्णांक completed_nbytes, alloc_nbytes, reमुख्यing_bytes;
	काष्ठा ath10k_ce_pipe *ce_diag;
	व्योम *data_buf;
	dma_addr_t ce_data_base = 0;
	पूर्णांक i;

	mutex_lock(&ar_pci->ce_diag_mutex);
	ce_diag = ar_pci->ce_diag;

	/*
	 * Allocate a temporary bounce buffer to hold caller's data
	 * to be DMA'ed to Target. This guarantees
	 *   1) 4-byte alignment
	 *   2) Buffer in DMA-able space
	 */
	alloc_nbytes = min_t(अचिन्हित पूर्णांक, nbytes, DIAG_TRANSFER_LIMIT);

	data_buf = dma_alloc_coherent(ar->dev, alloc_nbytes, &ce_data_base,
				      GFP_ATOMIC);
	अगर (!data_buf) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/*
	 * The address supplied by the caller is in the
	 * Target CPU भव address space.
	 *
	 * In order to use this address with the diagnostic CE,
	 * convert it from
	 *    Target CPU भव address space
	 * to
	 *    CE address space
	 */
	address = ath10k_pci_targ_cpu_to_ce_addr(ar, address);

	reमुख्यing_bytes = nbytes;
	जबतक (reमुख्यing_bytes) अणु
		/* FIXME: check cast */
		nbytes = min_t(पूर्णांक, reमुख्यing_bytes, DIAG_TRANSFER_LIMIT);

		/* Copy caller's data to allocated DMA buf */
		स_नकल(data_buf, data, nbytes);

		/* Set up to receive directly पूर्णांकo Target(!) address */
		ret = ath10k_ce_rx_post_buf(ce_diag, &address, address);
		अगर (ret != 0)
			जाओ करोne;

		/*
		 * Request CE to send caller-supplied data that
		 * was copied to bounce buffer to Target(!) address.
		 */
		ret = ath10k_ce_send(ce_diag, शून्य, ce_data_base, nbytes, 0, 0);
		अगर (ret != 0)
			जाओ करोne;

		i = 0;
		जबतक (ath10k_ce_completed_send_next(ce_diag, शून्य) != 0) अणु
			udelay(DIAG_ACCESS_CE_WAIT_US);
			i += DIAG_ACCESS_CE_WAIT_US;

			अगर (i > DIAG_ACCESS_CE_TIMEOUT_US) अणु
				ret = -EBUSY;
				जाओ करोne;
			पूर्ण
		पूर्ण

		i = 0;
		जबतक (ath10k_ce_completed_recv_next(ce_diag, (व्योम **)&buf,
						     &completed_nbytes) != 0) अणु
			udelay(DIAG_ACCESS_CE_WAIT_US);
			i += DIAG_ACCESS_CE_WAIT_US;

			अगर (i > DIAG_ACCESS_CE_TIMEOUT_US) अणु
				ret = -EBUSY;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (nbytes != completed_nbytes) अणु
			ret = -EIO;
			जाओ करोne;
		पूर्ण

		अगर (*buf != address) अणु
			ret = -EIO;
			जाओ करोne;
		पूर्ण

		reमुख्यing_bytes -= nbytes;
		address += nbytes;
		data += nbytes;
	पूर्ण

करोne:
	अगर (data_buf) अणु
		dma_मुक्त_coherent(ar->dev, alloc_nbytes, data_buf,
				  ce_data_base);
	पूर्ण

	अगर (ret != 0)
		ath10k_warn(ar, "failed to write diag value at 0x%x: %d\n",
			    address, ret);

	mutex_unlock(&ar_pci->ce_diag_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_pci_diag_ग_लिखो32(काष्ठा ath10k *ar, u32 address, u32 value)
अणु
	__le32 val = __cpu_to_le32(value);

	वापस ath10k_pci_diag_ग_लिखो_mem(ar, address, &val, माप(val));
पूर्ण

/* Called by lower (CE) layer when a send to Target completes. */
अटल व्योम ath10k_pci_htc_tx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&list);
	जबतक (ath10k_ce_completed_send_next(ce_state, (व्योम **)&skb) == 0) अणु
		/* no need to call tx completion क्रम शून्य poपूर्णांकers */
		अगर (skb == शून्य)
			जारी;

		__skb_queue_tail(&list, skb);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&list)))
		ath10k_htc_tx_completion_handler(ar, skb);
पूर्ण

अटल व्योम ath10k_pci_process_rx_cb(काष्ठा ath10k_ce_pipe *ce_state,
				     व्योम (*callback)(काष्ठा ath10k *ar,
						      काष्ठा sk_buff *skb))
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_pci_pipe *pipe_info =  &ar_pci->pipe_info[ce_state->id];
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head list;
	व्योम *transfer_context;
	अचिन्हित पूर्णांक nbytes, max_nbytes;

	__skb_queue_head_init(&list);
	जबतक (ath10k_ce_completed_recv_next(ce_state, &transfer_context,
					     &nbytes) == 0) अणु
		skb = transfer_context;
		max_nbytes = skb->len + skb_tailroom(skb);
		dma_unmap_single(ar->dev, ATH10K_SKB_RXCB(skb)->paddr,
				 max_nbytes, DMA_FROM_DEVICE);

		अगर (unlikely(max_nbytes < nbytes)) अणु
			ath10k_warn(ar, "rxed more than expected (nbytes %d, max %d)",
				    nbytes, max_nbytes);
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		skb_put(skb, nbytes);
		__skb_queue_tail(&list, skb);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&list))) अणु
		ath10k_dbg(ar, ATH10K_DBG_PCI, "pci rx ce pipe %d len %d\n",
			   ce_state->id, skb->len);
		ath10k_dbg_dump(ar, ATH10K_DBG_PCI_DUMP, शून्य, "pci rx: ",
				skb->data, skb->len);

		callback(ar, skb);
	पूर्ण

	ath10k_pci_rx_post_pipe(pipe_info);
पूर्ण

अटल व्योम ath10k_pci_process_htt_rx_cb(काष्ठा ath10k_ce_pipe *ce_state,
					 व्योम (*callback)(काष्ठा ath10k *ar,
							  काष्ठा sk_buff *skb))
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_pci_pipe *pipe_info =  &ar_pci->pipe_info[ce_state->id];
	काष्ठा ath10k_ce_pipe *ce_pipe = pipe_info->ce_hdl;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head list;
	व्योम *transfer_context;
	अचिन्हित पूर्णांक nbytes, max_nbytes, nentries;
	पूर्णांक orig_len;

	/* No need to aquire ce_lock क्रम CE5, since this is the only place CE5
	 * is processed other than init and deinit. Beक्रमe releasing CE5
	 * buffers, पूर्णांकerrupts are disabled. Thus CE5 access is serialized.
	 */
	__skb_queue_head_init(&list);
	जबतक (ath10k_ce_completed_recv_next_nolock(ce_state, &transfer_context,
						    &nbytes) == 0) अणु
		skb = transfer_context;
		max_nbytes = skb->len + skb_tailroom(skb);

		अगर (unlikely(max_nbytes < nbytes)) अणु
			ath10k_warn(ar, "rxed more than expected (nbytes %d, max %d)",
				    nbytes, max_nbytes);
			जारी;
		पूर्ण

		dma_sync_single_क्रम_cpu(ar->dev, ATH10K_SKB_RXCB(skb)->paddr,
					max_nbytes, DMA_FROM_DEVICE);
		skb_put(skb, nbytes);
		__skb_queue_tail(&list, skb);
	पूर्ण

	nentries = skb_queue_len(&list);
	जबतक ((skb = __skb_dequeue(&list))) अणु
		ath10k_dbg(ar, ATH10K_DBG_PCI, "pci rx ce pipe %d len %d\n",
			   ce_state->id, skb->len);
		ath10k_dbg_dump(ar, ATH10K_DBG_PCI_DUMP, शून्य, "pci rx: ",
				skb->data, skb->len);

		orig_len = skb->len;
		callback(ar, skb);
		skb_push(skb, orig_len - skb->len);
		skb_reset_tail_poपूर्णांकer(skb);
		skb_trim(skb, 0);

		/*let device gain the buffer again*/
		dma_sync_single_क्रम_device(ar->dev, ATH10K_SKB_RXCB(skb)->paddr,
					   skb->len + skb_tailroom(skb),
					   DMA_FROM_DEVICE);
	पूर्ण
	ath10k_ce_rx_update_ग_लिखो_idx(ce_pipe, nentries);
पूर्ण

/* Called by lower (CE) layer when data is received from the Target. */
अटल व्योम ath10k_pci_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	ath10k_pci_process_rx_cb(ce_state, ath10k_htc_rx_completion_handler);
पूर्ण

अटल व्योम ath10k_pci_htt_htc_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	/* CE4 polling needs to be करोne whenever CE pipe which transports
	 * HTT Rx (target->host) is processed.
	 */
	ath10k_ce_per_engine_service(ce_state->ar, 4);

	ath10k_pci_process_rx_cb(ce_state, ath10k_htc_rx_completion_handler);
पूर्ण

/* Called by lower (CE) layer when data is received from the Target.
 * Only 10.4 firmware uses separate CE to transfer pktlog data.
 */
अटल व्योम ath10k_pci_pktlog_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	ath10k_pci_process_rx_cb(ce_state,
				 ath10k_htt_rx_pktlog_completion_handler);
पूर्ण

/* Called by lower (CE) layer when a send to HTT Target completes. */
अटल व्योम ath10k_pci_htt_tx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा sk_buff *skb;

	जबतक (ath10k_ce_completed_send_next(ce_state, (व्योम **)&skb) == 0) अणु
		/* no need to call tx completion क्रम शून्य poपूर्णांकers */
		अगर (!skb)
			जारी;

		dma_unmap_single(ar->dev, ATH10K_SKB_CB(skb)->paddr,
				 skb->len, DMA_TO_DEVICE);
		ath10k_htt_hअगर_tx_complete(ar, skb);
	पूर्ण
पूर्ण

अटल व्योम ath10k_pci_htt_rx_deliver(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	skb_pull(skb, माप(काष्ठा ath10k_htc_hdr));
	ath10k_htt_t2h_msg_handler(ar, skb);
पूर्ण

/* Called by lower (CE) layer when HTT data is received from the Target. */
अटल व्योम ath10k_pci_htt_rx_cb(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	/* CE4 polling needs to be करोne whenever CE pipe which transports
	 * HTT Rx (target->host) is processed.
	 */
	ath10k_ce_per_engine_service(ce_state->ar, 4);

	ath10k_pci_process_htt_rx_cb(ce_state, ath10k_pci_htt_rx_deliver);
पूर्ण

पूर्णांक ath10k_pci_hअगर_tx_sg(काष्ठा ath10k *ar, u8 pipe_id,
			 काष्ठा ath10k_hअगर_sg_item *items, पूर्णांक n_items)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_pci_pipe *pci_pipe = &ar_pci->pipe_info[pipe_id];
	काष्ठा ath10k_ce_pipe *ce_pipe = pci_pipe->ce_hdl;
	काष्ठा ath10k_ce_ring *src_ring = ce_pipe->src_ring;
	अचिन्हित पूर्णांक nentries_mask;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक ग_लिखो_index;
	पूर्णांक err, i = 0;

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = src_ring->nentries_mask;
	sw_index = src_ring->sw_index;
	ग_लिखो_index = src_ring->ग_लिखो_index;

	अगर (unlikely(CE_RING_DELTA(nentries_mask,
				   ग_लिखो_index, sw_index - 1) < n_items)) अणु
		err = -ENOBUFS;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < n_items - 1; i++) अणु
		ath10k_dbg(ar, ATH10K_DBG_PCI,
			   "pci tx item %d paddr %pad len %d n_items %d\n",
			   i, &items[i].paddr, items[i].len, n_items);
		ath10k_dbg_dump(ar, ATH10K_DBG_PCI_DUMP, शून्य, "pci tx data: ",
				items[i].vaddr, items[i].len);

		err = ath10k_ce_send_nolock(ce_pipe,
					    items[i].transfer_context,
					    items[i].paddr,
					    items[i].len,
					    items[i].transfer_id,
					    CE_SEND_FLAG_GATHER);
		अगर (err)
			जाओ err;
	पूर्ण

	/* `i` is equal to `n_items -1` after क्रम() */

	ath10k_dbg(ar, ATH10K_DBG_PCI,
		   "pci tx item %d paddr %pad len %d n_items %d\n",
		   i, &items[i].paddr, items[i].len, n_items);
	ath10k_dbg_dump(ar, ATH10K_DBG_PCI_DUMP, शून्य, "pci tx data: ",
			items[i].vaddr, items[i].len);

	err = ath10k_ce_send_nolock(ce_pipe,
				    items[i].transfer_context,
				    items[i].paddr,
				    items[i].len,
				    items[i].transfer_id,
				    0);
	अगर (err)
		जाओ err;

	spin_unlock_bh(&ce->ce_lock);
	वापस 0;

err:
	क्रम (; i > 0; i--)
		__ath10k_ce_send_revert(ce_pipe);

	spin_unlock_bh(&ce->ce_lock);
	वापस err;
पूर्ण

पूर्णांक ath10k_pci_hअगर_diag_पढ़ो(काष्ठा ath10k *ar, u32 address, व्योम *buf,
			     माप_प्रकार buf_len)
अणु
	वापस ath10k_pci_diag_पढ़ो_mem(ar, address, buf, buf_len);
पूर्ण

u16 ath10k_pci_hअगर_get_मुक्त_queue_number(काष्ठा ath10k *ar, u8 pipe)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci hif get free queue number\n");

	वापस ath10k_ce_num_मुक्त_src_entries(ar_pci->pipe_info[pipe].ce_hdl);
पूर्ण

अटल व्योम ath10k_pci_dump_रेजिस्टरs(काष्ठा ath10k *ar,
				      काष्ठा ath10k_fw_crash_data *crash_data)
अणु
	__le32 reg_dump_values[REG_DUMP_COUNT_QCA988X] = अणुपूर्ण;
	पूर्णांक i, ret;

	lockdep_निश्चित_held(&ar->dump_mutex);

	ret = ath10k_pci_diag_पढ़ो_hi(ar, &reg_dump_values[0],
				      hi_failure_state,
				      REG_DUMP_COUNT_QCA988X * माप(__le32));
	अगर (ret) अणु
		ath10k_err(ar, "failed to read firmware dump area: %d\n", ret);
		वापस;
	पूर्ण

	BUILD_BUG_ON(REG_DUMP_COUNT_QCA988X % 4);

	ath10k_err(ar, "firmware register dump:\n");
	क्रम (i = 0; i < REG_DUMP_COUNT_QCA988X; i += 4)
		ath10k_err(ar, "[%02d]: 0x%08X 0x%08X 0x%08X 0x%08X\n",
			   i,
			   __le32_to_cpu(reg_dump_values[i]),
			   __le32_to_cpu(reg_dump_values[i + 1]),
			   __le32_to_cpu(reg_dump_values[i + 2]),
			   __le32_to_cpu(reg_dump_values[i + 3]));

	अगर (!crash_data)
		वापस;

	क्रम (i = 0; i < REG_DUMP_COUNT_QCA988X; i++)
		crash_data->रेजिस्टरs[i] = reg_dump_values[i];
पूर्ण

अटल पूर्णांक ath10k_pci_dump_memory_section(काष्ठा ath10k *ar,
					  स्थिर काष्ठा ath10k_mem_region *mem_region,
					  u8 *buf, माप_प्रकार buf_len)
अणु
	स्थिर काष्ठा ath10k_mem_section *cur_section, *next_section;
	अचिन्हित पूर्णांक count, section_size, skip_size;
	पूर्णांक ret, i, j;

	अगर (!mem_region || !buf)
		वापस 0;

	cur_section = &mem_region->section_table.sections[0];

	अगर (mem_region->start > cur_section->start) अणु
		ath10k_warn(ar, "incorrect memdump region 0x%x with section start address 0x%x.\n",
			    mem_region->start, cur_section->start);
		वापस 0;
	पूर्ण

	skip_size = cur_section->start - mem_region->start;

	/* fill the gap between the first रेजिस्टर section and रेजिस्टर
	 * start address
	 */
	क्रम (i = 0; i < skip_size; i++) अणु
		*buf = ATH10K_MAGIC_NOT_COPIED;
		buf++;
	पूर्ण

	count = 0;

	क्रम (i = 0; cur_section != शून्य; i++) अणु
		section_size = cur_section->end - cur_section->start;

		अगर (section_size <= 0) अणु
			ath10k_warn(ar, "incorrect ramdump format with start address 0x%x and stop address 0x%x\n",
				    cur_section->start,
				    cur_section->end);
			अवरोध;
		पूर्ण

		अगर ((i + 1) == mem_region->section_table.size) अणु
			/* last section */
			next_section = शून्य;
			skip_size = 0;
		पूर्ण अन्यथा अणु
			next_section = cur_section + 1;

			अगर (cur_section->end > next_section->start) अणु
				ath10k_warn(ar, "next ramdump section 0x%x is smaller than current end address 0x%x\n",
					    next_section->start,
					    cur_section->end);
				अवरोध;
			पूर्ण

			skip_size = next_section->start - cur_section->end;
		पूर्ण

		अगर (buf_len < (skip_size + section_size)) अणु
			ath10k_warn(ar, "ramdump buffer is too small: %zu\n", buf_len);
			अवरोध;
		पूर्ण

		buf_len -= skip_size + section_size;

		/* पढ़ो section to dest memory */
		ret = ath10k_pci_diag_पढ़ो_mem(ar, cur_section->start,
					       buf, section_size);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to read ramdump from section 0x%x: %d\n",
				    cur_section->start, ret);
			अवरोध;
		पूर्ण

		buf += section_size;
		count += section_size;

		/* fill in the gap between this section and the next */
		क्रम (j = 0; j < skip_size; j++) अणु
			*buf = ATH10K_MAGIC_NOT_COPIED;
			buf++;
		पूर्ण

		count += skip_size;

		अगर (!next_section)
			/* this was the last section */
			अवरोध;

		cur_section = next_section;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक ath10k_pci_set_ram_config(काष्ठा ath10k *ar, u32 config)
अणु
	u32 val;

	ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS +
			   FW_RAM_CONFIG_ADDRESS, config);

	val = ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS +
				FW_RAM_CONFIG_ADDRESS);
	अगर (val != config) अणु
		ath10k_warn(ar, "failed to set RAM config from 0x%x to 0x%x\n",
			    val, config);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Always वापसs the length */
अटल पूर्णांक ath10k_pci_dump_memory_sram(काष्ठा ath10k *ar,
				       स्थिर काष्ठा ath10k_mem_region *region,
				       u8 *buf)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 base_addr, i;

	base_addr = ioपढ़ो32(ar_pci->mem + QCA99X0_PCIE_BAR0_START_REG);
	base_addr += region->start;

	क्रम (i = 0; i < region->len; i += 4) अणु
		ioग_लिखो32(base_addr + i, ar_pci->mem + QCA99X0_CPU_MEM_ADDR_REG);
		*(u32 *)(buf + i) = ioपढ़ो32(ar_pci->mem + QCA99X0_CPU_MEM_DATA_REG);
	पूर्ण

	वापस region->len;
पूर्ण

/* अगर an error happened वापसs < 0, otherwise the length */
अटल पूर्णांक ath10k_pci_dump_memory_reg(काष्ठा ath10k *ar,
				      स्थिर काष्ठा ath10k_mem_region *region,
				      u8 *buf)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 i;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH10K_STATE_ON) अणु
		ath10k_warn(ar, "Skipping pci_dump_memory_reg invalid state\n");
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < region->len; i += 4)
		*(u32 *)(buf + i) = ioपढ़ो32(ar_pci->mem + region->start + i);

	ret = region->len;
करोne:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

/* अगर an error happened वापसs < 0, otherwise the length */
अटल पूर्णांक ath10k_pci_dump_memory_generic(काष्ठा ath10k *ar,
					  स्थिर काष्ठा ath10k_mem_region *current_region,
					  u8 *buf)
अणु
	पूर्णांक ret;

	अगर (current_region->section_table.size > 0)
		/* Copy each section inभागidually. */
		वापस ath10k_pci_dump_memory_section(ar,
						      current_region,
						      buf,
						      current_region->len);

	/* No inभागidiual memory sections defined so we can
	 * copy the entire memory region.
	 */
	ret = ath10k_pci_diag_पढ़ो_mem(ar,
				       current_region->start,
				       buf,
				       current_region->len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to copy ramdump region %s: %d\n",
			    current_region->name, ret);
		वापस ret;
	पूर्ण

	वापस current_region->len;
पूर्ण

अटल व्योम ath10k_pci_dump_memory(काष्ठा ath10k *ar,
				   काष्ठा ath10k_fw_crash_data *crash_data)
अणु
	स्थिर काष्ठा ath10k_hw_mem_layout *mem_layout;
	स्थिर काष्ठा ath10k_mem_region *current_region;
	काष्ठा ath10k_dump_ram_data_hdr *hdr;
	u32 count, shअगरt;
	माप_प्रकार buf_len;
	पूर्णांक ret, i;
	u8 *buf;

	lockdep_निश्चित_held(&ar->dump_mutex);

	अगर (!crash_data)
		वापस;

	mem_layout = ath10k_coredump_get_mem_layout(ar);
	अगर (!mem_layout)
		वापस;

	current_region = &mem_layout->region_table.regions[0];

	buf = crash_data->ramdump_buf;
	buf_len = crash_data->ramdump_buf_len;

	स_रखो(buf, 0, buf_len);

	क्रम (i = 0; i < mem_layout->region_table.size; i++) अणु
		count = 0;

		अगर (current_region->len > buf_len) अणु
			ath10k_warn(ar, "memory region %s size %d is larger that remaining ramdump buffer size %zu\n",
				    current_region->name,
				    current_region->len,
				    buf_len);
			अवरोध;
		पूर्ण

		/* To get IRAM dump, the host driver needs to चयन target
		 * ram config from DRAM to IRAM.
		 */
		अगर (current_region->type == ATH10K_MEM_REGION_TYPE_IRAM1 ||
		    current_region->type == ATH10K_MEM_REGION_TYPE_IRAM2) अणु
			shअगरt = current_region->start >> 20;

			ret = ath10k_pci_set_ram_config(ar, shअगरt);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to switch ram config to IRAM for section %s: %d\n",
					    current_region->name, ret);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Reserve space क्रम the header. */
		hdr = (व्योम *)buf;
		buf += माप(*hdr);
		buf_len -= माप(*hdr);

		चयन (current_region->type) अणु
		हाल ATH10K_MEM_REGION_TYPE_IOSRAM:
			count = ath10k_pci_dump_memory_sram(ar, current_region, buf);
			अवरोध;
		हाल ATH10K_MEM_REGION_TYPE_IOREG:
			ret = ath10k_pci_dump_memory_reg(ar, current_region, buf);
			अगर (ret < 0)
				अवरोध;

			count = ret;
			अवरोध;
		शेष:
			ret = ath10k_pci_dump_memory_generic(ar, current_region, buf);
			अगर (ret < 0)
				अवरोध;

			count = ret;
			अवरोध;
		पूर्ण

		hdr->region_type = cpu_to_le32(current_region->type);
		hdr->start = cpu_to_le32(current_region->start);
		hdr->length = cpu_to_le32(count);

		अगर (count == 0)
			/* Note: the header reमुख्यs, just with zero length. */
			अवरोध;

		buf += count;
		buf_len -= count;

		current_region++;
	पूर्ण
पूर्ण

अटल व्योम ath10k_pci_fw_dump_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_pci *ar_pci = container_of(work, काष्ठा ath10k_pci,
						 dump_work);
	काष्ठा ath10k_fw_crash_data *crash_data;
	काष्ठा ath10k *ar = ar_pci->ar;
	अक्षर guid[UUID_STRING_LEN + 1];

	mutex_lock(&ar->dump_mutex);

	spin_lock_bh(&ar->data_lock);
	ar->stats.fw_crash_counter++;
	spin_unlock_bh(&ar->data_lock);

	crash_data = ath10k_coredump_new(ar);

	अगर (crash_data)
		scnम_लिखो(guid, माप(guid), "%pUl", &crash_data->guid);
	अन्यथा
		scnम_लिखो(guid, माप(guid), "n/a");

	ath10k_err(ar, "firmware crashed! (guid %s)\n", guid);
	ath10k_prपूर्णांक_driver_info(ar);
	ath10k_pci_dump_रेजिस्टरs(ar, crash_data);
	ath10k_ce_dump_रेजिस्टरs(ar, crash_data);
	ath10k_pci_dump_memory(ar, crash_data);

	mutex_unlock(&ar->dump_mutex);

	ath10k_core_start_recovery(ar);
पूर्ण

अटल व्योम ath10k_pci_fw_crashed_dump(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	queue_work(ar->workqueue, &ar_pci->dump_work);
पूर्ण

व्योम ath10k_pci_hअगर_send_complete_check(काष्ठा ath10k *ar, u8 pipe,
					पूर्णांक क्रमce)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci hif send complete check\n");

	अगर (!क्रमce) अणु
		पूर्णांक resources;
		/*
		 * Decide whether to actually poll क्रम completions, or just
		 * रुको क्रम a later chance.
		 * If there seem to be plenty of resources left, then just रुको
		 * since checking involves पढ़ोing a CE रेजिस्टर, which is a
		 * relatively expensive operation.
		 */
		resources = ath10k_pci_hअगर_get_मुक्त_queue_number(ar, pipe);

		/*
		 * If at least 50% of the total resources are still available,
		 * करोn't bother checking again yet.
		 */
		अगर (resources > (ar_pci->attr[pipe].src_nentries >> 1))
			वापस;
	पूर्ण
	ath10k_ce_per_engine_service(ar, pipe);
पूर्ण

अटल व्योम ath10k_pci_rx_retry_sync(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	del_समयr_sync(&ar_pci->rx_post_retry);
पूर्ण

पूर्णांक ath10k_pci_hअगर_map_service_to_pipe(काष्ठा ath10k *ar, u16 service_id,
				       u8 *ul_pipe, u8 *dl_pipe)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	स्थिर काष्ठा ce_service_to_pipe *entry;
	bool ul_set = false, dl_set = false;
	पूर्णांक i;

	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci hif map service\n");

	क्रम (i = 0; i < ARRAY_SIZE(pci_target_service_to_ce_map_wlan); i++) अणु
		entry = &ar_pci->serv_to_pipe[i];

		अगर (__le32_to_cpu(entry->service_id) != service_id)
			जारी;

		चयन (__le32_to_cpu(entry->pipedir)) अणु
		हाल PIPEसूची_NONE:
			अवरोध;
		हाल PIPEसूची_IN:
			WARN_ON(dl_set);
			*dl_pipe = __le32_to_cpu(entry->pipक्रमागत);
			dl_set = true;
			अवरोध;
		हाल PIPEसूची_OUT:
			WARN_ON(ul_set);
			*ul_pipe = __le32_to_cpu(entry->pipक्रमागत);
			ul_set = true;
			अवरोध;
		हाल PIPEसूची_INOUT:
			WARN_ON(dl_set);
			WARN_ON(ul_set);
			*dl_pipe = __le32_to_cpu(entry->pipक्रमागत);
			*ul_pipe = __le32_to_cpu(entry->pipक्रमागत);
			dl_set = true;
			ul_set = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ul_set || !dl_set)
		वापस -ENOENT;

	वापस 0;
पूर्ण

व्योम ath10k_pci_hअगर_get_शेष_pipe(काष्ठा ath10k *ar,
				     u8 *ul_pipe, u8 *dl_pipe)
अणु
	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci hif get default pipe\n");

	(व्योम)ath10k_pci_hअगर_map_service_to_pipe(ar,
						 ATH10K_HTC_SVC_ID_RSVD_CTRL,
						 ul_pipe, dl_pipe);
पूर्ण

व्योम ath10k_pci_irq_msi_fw_mask(काष्ठा ath10k *ar)
अणु
	u32 val;

	चयन (ar->hw_rev) अणु
	हाल ATH10K_HW_QCA988X:
	हाल ATH10K_HW_QCA9887:
	हाल ATH10K_HW_QCA6174:
	हाल ATH10K_HW_QCA9377:
		val = ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS +
					CORE_CTRL_ADDRESS);
		val &= ~CORE_CTRL_PCIE_REG_31_MASK;
		ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS +
				   CORE_CTRL_ADDRESS, val);
		अवरोध;
	हाल ATH10K_HW_QCA99X0:
	हाल ATH10K_HW_QCA9984:
	हाल ATH10K_HW_QCA9888:
	हाल ATH10K_HW_QCA4019:
		/* TODO: Find appropriate रेजिस्टर configuration क्रम QCA99X0
		 *  to mask irq/MSI.
		 */
		अवरोध;
	हाल ATH10K_HW_WCN3990:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath10k_pci_irq_msi_fw_unmask(काष्ठा ath10k *ar)
अणु
	u32 val;

	चयन (ar->hw_rev) अणु
	हाल ATH10K_HW_QCA988X:
	हाल ATH10K_HW_QCA9887:
	हाल ATH10K_HW_QCA6174:
	हाल ATH10K_HW_QCA9377:
		val = ath10k_pci_पढ़ो32(ar, SOC_CORE_BASE_ADDRESS +
					CORE_CTRL_ADDRESS);
		val |= CORE_CTRL_PCIE_REG_31_MASK;
		ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS +
				   CORE_CTRL_ADDRESS, val);
		अवरोध;
	हाल ATH10K_HW_QCA99X0:
	हाल ATH10K_HW_QCA9984:
	हाल ATH10K_HW_QCA9888:
	हाल ATH10K_HW_QCA4019:
		/* TODO: Find appropriate रेजिस्टर configuration क्रम QCA99X0
		 *  to unmask irq/MSI.
		 */
		अवरोध;
	हाल ATH10K_HW_WCN3990:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath10k_pci_irq_disable(काष्ठा ath10k *ar)
अणु
	ath10k_ce_disable_पूर्णांकerrupts(ar);
	ath10k_pci_disable_and_clear_legacy_irq(ar);
	ath10k_pci_irq_msi_fw_mask(ar);
पूर्ण

अटल व्योम ath10k_pci_irq_sync(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	synchronize_irq(ar_pci->pdev->irq);
पूर्ण

अटल व्योम ath10k_pci_irq_enable(काष्ठा ath10k *ar)
अणु
	ath10k_ce_enable_पूर्णांकerrupts(ar);
	ath10k_pci_enable_legacy_irq(ar);
	ath10k_pci_irq_msi_fw_unmask(ar);
पूर्ण

अटल पूर्णांक ath10k_pci_hअगर_start(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif start\n");

	ath10k_core_napi_enable(ar);

	ath10k_pci_irq_enable(ar);
	ath10k_pci_rx_post(ar);

	pcie_capability_ग_लिखो_word(ar_pci->pdev, PCI_EXP_LNKCTL,
				   ar_pci->link_ctl);

	वापस 0;
पूर्ण

अटल व्योम ath10k_pci_rx_pipe_cleanup(काष्ठा ath10k_pci_pipe *pci_pipe)
अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_ce_pipe *ce_pipe;
	काष्ठा ath10k_ce_ring *ce_ring;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	ar = pci_pipe->hअगर_ce_state;
	ce_pipe = pci_pipe->ce_hdl;
	ce_ring = ce_pipe->dest_ring;

	अगर (!ce_ring)
		वापस;

	अगर (!pci_pipe->buf_sz)
		वापस;

	क्रम (i = 0; i < ce_ring->nentries; i++) अणु
		skb = ce_ring->per_transfer_context[i];
		अगर (!skb)
			जारी;

		ce_ring->per_transfer_context[i] = शून्य;

		dma_unmap_single(ar->dev, ATH10K_SKB_RXCB(skb)->paddr,
				 skb->len + skb_tailroom(skb),
				 DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम ath10k_pci_tx_pipe_cleanup(काष्ठा ath10k_pci_pipe *pci_pipe)
अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_ce_pipe *ce_pipe;
	काष्ठा ath10k_ce_ring *ce_ring;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	ar = pci_pipe->hअगर_ce_state;
	ce_pipe = pci_pipe->ce_hdl;
	ce_ring = ce_pipe->src_ring;

	अगर (!ce_ring)
		वापस;

	अगर (!pci_pipe->buf_sz)
		वापस;

	क्रम (i = 0; i < ce_ring->nentries; i++) अणु
		skb = ce_ring->per_transfer_context[i];
		अगर (!skb)
			जारी;

		ce_ring->per_transfer_context[i] = शून्य;

		ath10k_htc_tx_completion_handler(ar, skb);
	पूर्ण
पूर्ण

/*
 * Cleanup residual buffers क्रम device shutकरोwn:
 *    buffers that were enqueued क्रम receive
 *    buffers that were to be sent
 * Note: Buffers that had completed but which were
 * not yet processed are on a completion queue. They
 * are handled when the completion thपढ़ो shuts करोwn.
 */
अटल व्योम ath10k_pci_buffer_cleanup(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक pipe_num;

	क्रम (pipe_num = 0; pipe_num < CE_COUNT; pipe_num++) अणु
		काष्ठा ath10k_pci_pipe *pipe_info;

		pipe_info = &ar_pci->pipe_info[pipe_num];
		ath10k_pci_rx_pipe_cleanup(pipe_info);
		ath10k_pci_tx_pipe_cleanup(pipe_info);
	पूर्ण
पूर्ण

व्योम ath10k_pci_ce_deinit(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CE_COUNT; i++)
		ath10k_ce_deinit_pipe(ar, i);
पूर्ण

व्योम ath10k_pci_flush(काष्ठा ath10k *ar)
अणु
	ath10k_pci_rx_retry_sync(ar);
	ath10k_pci_buffer_cleanup(ar);
पूर्ण

अटल व्योम ath10k_pci_hअगर_stop(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ flags;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif stop\n");

	ath10k_pci_irq_disable(ar);
	ath10k_pci_irq_sync(ar);

	ath10k_core_napi_sync_disable(ar);

	cancel_work_sync(&ar_pci->dump_work);

	/* Most likely the device has HTT Rx ring configured. The only way to
	 * prevent the device from accessing (and possible corrupting) host
	 * memory is to reset the chip now.
	 *
	 * There's also no known way of masking MSI पूर्णांकerrupts on the device.
	 * For ranged MSI the CE-related पूर्णांकerrupts can be masked. However
	 * regardless how many MSI पूर्णांकerrupts are asचिन्हित the first one
	 * is always used क्रम firmware indications (crashes) and cannot be
	 * masked. To prevent the device from निश्चितing the पूर्णांकerrupt reset it
	 * beक्रमe proceeding with cleanup.
	 */
	ath10k_pci_safe_chip_reset(ar);

	ath10k_pci_flush(ar);

	spin_lock_irqsave(&ar_pci->ps_lock, flags);
	WARN_ON(ar_pci->ps_wake_refcount > 0);
	spin_unlock_irqrestore(&ar_pci->ps_lock, flags);
पूर्ण

पूर्णांक ath10k_pci_hअगर_exchange_bmi_msg(काष्ठा ath10k *ar,
				    व्योम *req, u32 req_len,
				    व्योम *resp, u32 *resp_len)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_pci_pipe *pci_tx = &ar_pci->pipe_info[BMI_CE_NUM_TO_TARG];
	काष्ठा ath10k_pci_pipe *pci_rx = &ar_pci->pipe_info[BMI_CE_NUM_TO_HOST];
	काष्ठा ath10k_ce_pipe *ce_tx = pci_tx->ce_hdl;
	काष्ठा ath10k_ce_pipe *ce_rx = pci_rx->ce_hdl;
	dma_addr_t req_paddr = 0;
	dma_addr_t resp_paddr = 0;
	काष्ठा bmi_xfer xfer = अणुपूर्ण;
	व्योम *treq, *tresp = शून्य;
	पूर्णांक ret = 0;

	might_sleep();

	अगर (resp && !resp_len)
		वापस -EINVAL;

	अगर (resp && resp_len && *resp_len == 0)
		वापस -EINVAL;

	treq = kmemdup(req, req_len, GFP_KERNEL);
	अगर (!treq)
		वापस -ENOMEM;

	req_paddr = dma_map_single(ar->dev, treq, req_len, DMA_TO_DEVICE);
	ret = dma_mapping_error(ar->dev, req_paddr);
	अगर (ret) अणु
		ret = -EIO;
		जाओ err_dma;
	पूर्ण

	अगर (resp && resp_len) अणु
		tresp = kzalloc(*resp_len, GFP_KERNEL);
		अगर (!tresp) अणु
			ret = -ENOMEM;
			जाओ err_req;
		पूर्ण

		resp_paddr = dma_map_single(ar->dev, tresp, *resp_len,
					    DMA_FROM_DEVICE);
		ret = dma_mapping_error(ar->dev, resp_paddr);
		अगर (ret) अणु
			ret = -EIO;
			जाओ err_req;
		पूर्ण

		xfer.रुको_क्रम_resp = true;
		xfer.resp_len = 0;

		ath10k_ce_rx_post_buf(ce_rx, &xfer, resp_paddr);
	पूर्ण

	ret = ath10k_ce_send(ce_tx, &xfer, req_paddr, req_len, -1, 0);
	अगर (ret)
		जाओ err_resp;

	ret = ath10k_pci_bmi_रुको(ar, ce_tx, ce_rx, &xfer);
	अगर (ret) अणु
		dma_addr_t unused_buffer;
		अचिन्हित पूर्णांक unused_nbytes;
		अचिन्हित पूर्णांक unused_id;

		ath10k_ce_cancel_send_next(ce_tx, शून्य, &unused_buffer,
					   &unused_nbytes, &unused_id);
	पूर्ण अन्यथा अणु
		/* non-zero means we did not समय out */
		ret = 0;
	पूर्ण

err_resp:
	अगर (resp) अणु
		dma_addr_t unused_buffer;

		ath10k_ce_revoke_recv_next(ce_rx, शून्य, &unused_buffer);
		dma_unmap_single(ar->dev, resp_paddr,
				 *resp_len, DMA_FROM_DEVICE);
	पूर्ण
err_req:
	dma_unmap_single(ar->dev, req_paddr, req_len, DMA_TO_DEVICE);

	अगर (ret == 0 && resp_len) अणु
		*resp_len = min(*resp_len, xfer.resp_len);
		स_नकल(resp, tresp, *resp_len);
	पूर्ण
err_dma:
	kमुक्त(treq);
	kमुक्त(tresp);

	वापस ret;
पूर्ण

अटल व्योम ath10k_pci_bmi_send_करोne(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	काष्ठा bmi_xfer *xfer;

	अगर (ath10k_ce_completed_send_next(ce_state, (व्योम **)&xfer))
		वापस;

	xfer->tx_करोne = true;
पूर्ण

अटल व्योम ath10k_pci_bmi_recv_data(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा bmi_xfer *xfer;
	अचिन्हित पूर्णांक nbytes;

	अगर (ath10k_ce_completed_recv_next(ce_state, (व्योम **)&xfer,
					  &nbytes))
		वापस;

	अगर (WARN_ON_ONCE(!xfer))
		वापस;

	अगर (!xfer->रुको_क्रम_resp) अणु
		ath10k_warn(ar, "unexpected: BMI data received; ignoring\n");
		वापस;
	पूर्ण

	xfer->resp_len = nbytes;
	xfer->rx_करोne = true;
पूर्ण

अटल पूर्णांक ath10k_pci_bmi_रुको(काष्ठा ath10k *ar,
			       काष्ठा ath10k_ce_pipe *tx_pipe,
			       काष्ठा ath10k_ce_pipe *rx_pipe,
			       काष्ठा bmi_xfer *xfer)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + BMI_COMMUNICATION_TIMEOUT_HZ;
	अचिन्हित दीर्घ started = jअगरfies;
	अचिन्हित दीर्घ dur;
	पूर्णांक ret;

	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		ath10k_pci_bmi_send_करोne(tx_pipe);
		ath10k_pci_bmi_recv_data(rx_pipe);

		अगर (xfer->tx_करोne && (xfer->rx_करोne == xfer->रुको_क्रम_resp)) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		schedule();
	पूर्ण

	ret = -ETIMEDOUT;

out:
	dur = jअगरfies - started;
	अगर (dur > HZ)
		ath10k_dbg(ar, ATH10K_DBG_BMI,
			   "bmi cmd took %lu jiffies hz %d ret %d\n",
			   dur, HZ, ret);
	वापस ret;
पूर्ण

/*
 * Send an पूर्णांकerrupt to the device to wake up the Target CPU
 * so it has an opportunity to notice any changed state.
 */
अटल पूर्णांक ath10k_pci_wake_target_cpu(काष्ठा ath10k *ar)
अणु
	u32 addr, val;

	addr = SOC_CORE_BASE_ADDRESS + CORE_CTRL_ADDRESS;
	val = ath10k_pci_पढ़ो32(ar, addr);
	val |= CORE_CTRL_CPU_INTR_MASK;
	ath10k_pci_ग_लिखो32(ar, addr, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_get_num_banks(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	चयन (ar_pci->pdev->device) अणु
	हाल QCA988X_2_0_DEVICE_ID_UBNT:
	हाल QCA988X_2_0_DEVICE_ID:
	हाल QCA99X0_2_0_DEVICE_ID:
	हाल QCA9888_2_0_DEVICE_ID:
	हाल QCA9984_1_0_DEVICE_ID:
	हाल QCA9887_1_0_DEVICE_ID:
		वापस 1;
	हाल QCA6164_2_1_DEVICE_ID:
	हाल QCA6174_2_1_DEVICE_ID:
		चयन (MS(ar->bus_param.chip_id, SOC_CHIP_ID_REV)) अणु
		हाल QCA6174_HW_1_0_CHIP_ID_REV:
		हाल QCA6174_HW_1_1_CHIP_ID_REV:
		हाल QCA6174_HW_2_1_CHIP_ID_REV:
		हाल QCA6174_HW_2_2_CHIP_ID_REV:
			वापस 3;
		हाल QCA6174_HW_1_3_CHIP_ID_REV:
			वापस 2;
		हाल QCA6174_HW_3_0_CHIP_ID_REV:
		हाल QCA6174_HW_3_1_CHIP_ID_REV:
		हाल QCA6174_HW_3_2_CHIP_ID_REV:
			वापस 9;
		पूर्ण
		अवरोध;
	हाल QCA9377_1_0_DEVICE_ID:
		वापस 9;
	पूर्ण

	ath10k_warn(ar, "unknown number of banks, assuming 1\n");
	वापस 1;
पूर्ण

अटल पूर्णांक ath10k_bus_get_num_banks(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	वापस ce->bus_ops->get_num_banks(ar);
पूर्ण

पूर्णांक ath10k_pci_init_config(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 पूर्णांकerconnect_targ_addr;
	u32 pcie_state_targ_addr = 0;
	u32 pipe_cfg_targ_addr = 0;
	u32 svc_to_pipe_map = 0;
	u32 pcie_config_flags = 0;
	u32 ealloc_value;
	u32 ealloc_targ_addr;
	u32 flag2_value;
	u32 flag2_targ_addr;
	पूर्णांक ret = 0;

	/* Download to Target the CE Config and the service-to-CE map */
	पूर्णांकerconnect_targ_addr =
		host_पूर्णांकerest_item_address(HI_ITEM(hi_पूर्णांकerconnect_state));

	/* Supply Target-side CE configuration */
	ret = ath10k_pci_diag_पढ़ो32(ar, पूर्णांकerconnect_targ_addr,
				     &pcie_state_targ_addr);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to get pcie state addr: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pcie_state_targ_addr == 0) अणु
		ret = -EIO;
		ath10k_err(ar, "Invalid pcie state addr\n");
		वापस ret;
	पूर्ण

	ret = ath10k_pci_diag_पढ़ो32(ar, (pcie_state_targ_addr +
					  दुरत्व(काष्ठा pcie_state,
						   pipe_cfg_addr)),
				     &pipe_cfg_targ_addr);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to get pipe cfg addr: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pipe_cfg_targ_addr == 0) अणु
		ret = -EIO;
		ath10k_err(ar, "Invalid pipe cfg addr\n");
		वापस ret;
	पूर्ण

	ret = ath10k_pci_diag_ग_लिखो_mem(ar, pipe_cfg_targ_addr,
					ar_pci->pipe_config,
					माप(काष्ठा ce_pipe_config) *
					NUM_TARGET_CE_CONFIG_WLAN);

	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to write pipe cfg: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_diag_पढ़ो32(ar, (pcie_state_targ_addr +
					  दुरत्व(काष्ठा pcie_state,
						   svc_to_pipe_map)),
				     &svc_to_pipe_map);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to get svc/pipe map: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (svc_to_pipe_map == 0) अणु
		ret = -EIO;
		ath10k_err(ar, "Invalid svc_to_pipe map\n");
		वापस ret;
	पूर्ण

	ret = ath10k_pci_diag_ग_लिखो_mem(ar, svc_to_pipe_map,
					ar_pci->serv_to_pipe,
					माप(pci_target_service_to_ce_map_wlan));
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to write svc/pipe map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_diag_पढ़ो32(ar, (pcie_state_targ_addr +
					  दुरत्व(काष्ठा pcie_state,
						   config_flags)),
				     &pcie_config_flags);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to get pcie config_flags: %d\n", ret);
		वापस ret;
	पूर्ण

	pcie_config_flags &= ~PCIE_CONFIG_FLAG_ENABLE_L1;

	ret = ath10k_pci_diag_ग_लिखो32(ar, (pcie_state_targ_addr +
					   दुरत्व(काष्ठा pcie_state,
						    config_flags)),
				      pcie_config_flags);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to write pcie config_flags: %d\n", ret);
		वापस ret;
	पूर्ण

	/* configure early allocation */
	ealloc_targ_addr = host_पूर्णांकerest_item_address(HI_ITEM(hi_early_alloc));

	ret = ath10k_pci_diag_पढ़ो32(ar, ealloc_targ_addr, &ealloc_value);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to get early alloc val: %d\n", ret);
		वापस ret;
	पूर्ण

	/* first bank is चयनed to IRAM */
	ealloc_value |= ((HI_EARLY_ALLOC_MAGIC << HI_EARLY_ALLOC_MAGIC_SHIFT) &
			 HI_EARLY_ALLOC_MAGIC_MASK);
	ealloc_value |= ((ath10k_bus_get_num_banks(ar) <<
			  HI_EARLY_ALLOC_IRAM_BANKS_SHIFT) &
			 HI_EARLY_ALLOC_IRAM_BANKS_MASK);

	ret = ath10k_pci_diag_ग_लिखो32(ar, ealloc_targ_addr, ealloc_value);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to set early alloc val: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Tell Target to proceed with initialization */
	flag2_targ_addr = host_पूर्णांकerest_item_address(HI_ITEM(hi_option_flag2));

	ret = ath10k_pci_diag_पढ़ो32(ar, flag2_targ_addr, &flag2_value);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to get option val: %d\n", ret);
		वापस ret;
	पूर्ण

	flag2_value |= HI_OPTION_EARLY_CFG_DONE;

	ret = ath10k_pci_diag_ग_लिखो32(ar, flag2_targ_addr, flag2_value);
	अगर (ret != 0) अणु
		ath10k_err(ar, "Failed to set option val: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_pci_override_ce_config(काष्ठा ath10k *ar)
अणु
	काष्ठा ce_attr *attr;
	काष्ठा ce_pipe_config *config;
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	/* For QCA6174 we're overriding the Copy Engine 5 configuration,
	 * since it is currently used क्रम other feature.
	 */

	/* Override Host's Copy Engine 5 configuration */
	attr = &ar_pci->attr[5];
	attr->src_sz_max = 0;
	attr->dest_nentries = 0;

	/* Override Target firmware's Copy Engine configuration */
	config = &ar_pci->pipe_config[5];
	config->pipedir = __cpu_to_le32(PIPEसूची_OUT);
	config->nbytes_max = __cpu_to_le32(2048);

	/* Map from service/endpoपूर्णांक to Copy Engine */
	ar_pci->serv_to_pipe[15].pipक्रमागत = __cpu_to_le32(1);
पूर्ण

पूर्णांक ath10k_pci_alloc_pipes(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_pci_pipe *pipe;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक i, ret;

	क्रम (i = 0; i < CE_COUNT; i++) अणु
		pipe = &ar_pci->pipe_info[i];
		pipe->ce_hdl = &ce->ce_states[i];
		pipe->pipe_num = i;
		pipe->hअगर_ce_state = ar;

		ret = ath10k_ce_alloc_pipe(ar, i, &ar_pci->attr[i]);
		अगर (ret) अणु
			ath10k_err(ar, "failed to allocate copy engine pipe %d: %d\n",
				   i, ret);
			वापस ret;
		पूर्ण

		/* Last CE is Diagnostic Winकरोw */
		अगर (i == CE_DIAG_PIPE) अणु
			ar_pci->ce_diag = pipe->ce_hdl;
			जारी;
		पूर्ण

		pipe->buf_sz = (माप_प्रकार)(ar_pci->attr[i].src_sz_max);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_pci_मुक्त_pipes(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CE_COUNT; i++)
		ath10k_ce_मुक्त_pipe(ar, i);
पूर्ण

पूर्णांक ath10k_pci_init_pipes(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक i, ret;

	क्रम (i = 0; i < CE_COUNT; i++) अणु
		ret = ath10k_ce_init_pipe(ar, i, &ar_pci->attr[i]);
		अगर (ret) अणु
			ath10k_err(ar, "failed to initialize copy engine pipe %d: %d\n",
				   i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ath10k_pci_has_fw_crashed(काष्ठा ath10k *ar)
अणु
	वापस ath10k_pci_पढ़ो32(ar, FW_INDICATOR_ADDRESS) &
	       FW_IND_EVENT_PENDING;
पूर्ण

अटल व्योम ath10k_pci_fw_crashed_clear(काष्ठा ath10k *ar)
अणु
	u32 val;

	val = ath10k_pci_पढ़ो32(ar, FW_INDICATOR_ADDRESS);
	val &= ~FW_IND_EVENT_PENDING;
	ath10k_pci_ग_लिखो32(ar, FW_INDICATOR_ADDRESS, val);
पूर्ण

अटल bool ath10k_pci_has_device_gone(काष्ठा ath10k *ar)
अणु
	u32 val;

	val = ath10k_pci_पढ़ो32(ar, FW_INDICATOR_ADDRESS);
	वापस (val == 0xffffffff);
पूर्ण

/* this function effectively clears target memory controller निश्चित line */
अटल व्योम ath10k_pci_warm_reset_si0(काष्ठा ath10k *ar)
अणु
	u32 val;

	val = ath10k_pci_soc_पढ़ो32(ar, SOC_RESET_CONTROL_ADDRESS);
	ath10k_pci_soc_ग_लिखो32(ar, SOC_RESET_CONTROL_ADDRESS,
			       val | SOC_RESET_CONTROL_SI0_RST_MASK);
	val = ath10k_pci_soc_पढ़ो32(ar, SOC_RESET_CONTROL_ADDRESS);

	msleep(10);

	val = ath10k_pci_soc_पढ़ो32(ar, SOC_RESET_CONTROL_ADDRESS);
	ath10k_pci_soc_ग_लिखो32(ar, SOC_RESET_CONTROL_ADDRESS,
			       val & ~SOC_RESET_CONTROL_SI0_RST_MASK);
	val = ath10k_pci_soc_पढ़ो32(ar, SOC_RESET_CONTROL_ADDRESS);

	msleep(10);
पूर्ण

अटल व्योम ath10k_pci_warm_reset_cpu(काष्ठा ath10k *ar)
अणु
	u32 val;

	ath10k_pci_ग_लिखो32(ar, FW_INDICATOR_ADDRESS, 0);

	val = ath10k_pci_soc_पढ़ो32(ar, SOC_RESET_CONTROL_ADDRESS);
	ath10k_pci_soc_ग_लिखो32(ar, SOC_RESET_CONTROL_ADDRESS,
			       val | SOC_RESET_CONTROL_CPU_WARM_RST_MASK);
पूर्ण

अटल व्योम ath10k_pci_warm_reset_ce(काष्ठा ath10k *ar)
अणु
	u32 val;

	val = ath10k_pci_soc_पढ़ो32(ar, SOC_RESET_CONTROL_ADDRESS);

	ath10k_pci_soc_ग_लिखो32(ar, SOC_RESET_CONTROL_ADDRESS,
			       val | SOC_RESET_CONTROL_CE_RST_MASK);
	msleep(10);
	ath10k_pci_soc_ग_लिखो32(ar, SOC_RESET_CONTROL_ADDRESS,
			       val & ~SOC_RESET_CONTROL_CE_RST_MASK);
पूर्ण

अटल व्योम ath10k_pci_warm_reset_clear_lf(काष्ठा ath10k *ar)
अणु
	u32 val;

	val = ath10k_pci_soc_पढ़ो32(ar, SOC_LF_TIMER_CONTROL0_ADDRESS);
	ath10k_pci_soc_ग_लिखो32(ar, SOC_LF_TIMER_CONTROL0_ADDRESS,
			       val & ~SOC_LF_TIMER_CONTROL0_ENABLE_MASK);
पूर्ण

अटल पूर्णांक ath10k_pci_warm_reset(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot warm reset\n");

	spin_lock_bh(&ar->data_lock);
	ar->stats.fw_warm_reset_counter++;
	spin_unlock_bh(&ar->data_lock);

	ath10k_pci_irq_disable(ar);

	/* Make sure the target CPU is not करोing anything dangerous, e.g. अगर it
	 * were to access copy engine जबतक host perक्रमms copy engine reset
	 * then it is possible क्रम the device to confuse pci-e controller to
	 * the poपूर्णांक of bringing host प्रणाली to a complete stop (i.e. hang).
	 */
	ath10k_pci_warm_reset_si0(ar);
	ath10k_pci_warm_reset_cpu(ar);
	ath10k_pci_init_pipes(ar);
	ath10k_pci_रुको_क्रम_target_init(ar);

	ath10k_pci_warm_reset_clear_lf(ar);
	ath10k_pci_warm_reset_ce(ar);
	ath10k_pci_warm_reset_cpu(ar);
	ath10k_pci_init_pipes(ar);

	ret = ath10k_pci_रुको_क्रम_target_init(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wait for target init: %d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot warm reset complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_qca99x0_soft_chip_reset(काष्ठा ath10k *ar)
अणु
	ath10k_pci_irq_disable(ar);
	वापस ath10k_pci_qca99x0_chip_reset(ar);
पूर्ण

अटल पूर्णांक ath10k_pci_safe_chip_reset(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	अगर (!ar_pci->pci_soft_reset)
		वापस -ENOTSUPP;

	वापस ar_pci->pci_soft_reset(ar);
पूर्ण

अटल पूर्णांक ath10k_pci_qca988x_chip_reset(काष्ठा ath10k *ar)
अणु
	पूर्णांक i, ret;
	u32 val;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot 988x chip reset\n");

	/* Some hardware revisions (e.g. CUS223v2) has issues with cold reset.
	 * It is thus preferred to use warm reset which is safer but may not be
	 * able to recover the device from all possible fail scenarios.
	 *
	 * Warm reset करोesn't always work on first try so attempt it a few
	 * बार beक्रमe giving up.
	 */
	क्रम (i = 0; i < ATH10K_PCI_NUM_WARM_RESET_ATTEMPTS; i++) अणु
		ret = ath10k_pci_warm_reset(ar);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to warm reset attempt %d of %d: %d\n",
				    i + 1, ATH10K_PCI_NUM_WARM_RESET_ATTEMPTS,
				    ret);
			जारी;
		पूर्ण

		/* FIXME: Someबार copy engine करोesn't recover after warm
		 * reset. In most हालs this needs cold reset. In some of these
		 * हालs the device is in such a state that a cold reset may
		 * lock up the host.
		 *
		 * Reading any host पूर्णांकerest रेजिस्टर via copy engine is
		 * sufficient to verअगरy अगर device is capable of booting
		 * firmware blob.
		 */
		ret = ath10k_pci_init_pipes(ar);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to init copy engine: %d\n",
				    ret);
			जारी;
		पूर्ण

		ret = ath10k_pci_diag_पढ़ो32(ar, QCA988X_HOST_INTEREST_ADDRESS,
					     &val);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to poke copy engine: %d\n",
				    ret);
			जारी;
		पूर्ण

		ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot chip reset complete (warm)\n");
		वापस 0;
	पूर्ण

	अगर (ath10k_pci_reset_mode == ATH10K_PCI_RESET_WARM_ONLY) अणु
		ath10k_warn(ar, "refusing cold reset as requested\n");
		वापस -EPERM;
	पूर्ण

	ret = ath10k_pci_cold_reset(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to cold reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_रुको_क्रम_target_init(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wait for target after cold reset: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca988x chip reset complete (cold)\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_qca6174_chip_reset(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca6174 chip reset\n");

	/* FIXME: QCA6174 requires cold + warm reset to work. */

	ret = ath10k_pci_cold_reset(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to cold reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_रुको_क्रम_target_init(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wait for target after cold reset: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_warm_reset(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to warm reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca6174 chip reset complete (cold)\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_qca99x0_chip_reset(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca99x0 chip reset\n");

	ret = ath10k_pci_cold_reset(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to cold reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_pci_रुको_क्रम_target_init(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wait for target after cold reset: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot qca99x0 chip reset complete (cold)\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_chip_reset(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	अगर (WARN_ON(!ar_pci->pci_hard_reset))
		वापस -ENOTSUPP;

	वापस ar_pci->pci_hard_reset(ar);
पूर्ण

अटल पूर्णांक ath10k_pci_hअगर_घातer_up(काष्ठा ath10k *ar,
				   क्रमागत ath10k_firmware_mode fw_mode)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif power up\n");

	pcie_capability_पढ़ो_word(ar_pci->pdev, PCI_EXP_LNKCTL,
				  &ar_pci->link_ctl);
	pcie_capability_ग_लिखो_word(ar_pci->pdev, PCI_EXP_LNKCTL,
				   ar_pci->link_ctl & ~PCI_EXP_LNKCTL_ASPMC);

	/*
	 * Bring the target up cleanly.
	 *
	 * The target may be in an undefined state with an AUX-घातered Target
	 * and a Host in WoW mode. If the Host crashes, loses घातer, or is
	 * restarted (without unloading the driver) then the Target is left
	 * (aux) घातered and running. On a subsequent driver load, the Target
	 * is in an unexpected state. We try to catch that here in order to
	 * reset the Target and retry the probe.
	 */
	ret = ath10k_pci_chip_reset(ar);
	अगर (ret) अणु
		अगर (ath10k_pci_has_fw_crashed(ar)) अणु
			ath10k_warn(ar, "firmware crashed during chip reset\n");
			ath10k_pci_fw_crashed_clear(ar);
			ath10k_pci_fw_crashed_dump(ar);
		पूर्ण

		ath10k_err(ar, "failed to reset chip: %d\n", ret);
		जाओ err_sleep;
	पूर्ण

	ret = ath10k_pci_init_pipes(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to initialize CE: %d\n", ret);
		जाओ err_sleep;
	पूर्ण

	ret = ath10k_pci_init_config(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to setup init config: %d\n", ret);
		जाओ err_ce;
	पूर्ण

	ret = ath10k_pci_wake_target_cpu(ar);
	अगर (ret) अणु
		ath10k_err(ar, "could not wake up target CPU: %d\n", ret);
		जाओ err_ce;
	पूर्ण

	वापस 0;

err_ce:
	ath10k_pci_ce_deinit(ar);

err_sleep:
	वापस ret;
पूर्ण

व्योम ath10k_pci_hअगर_घातer_करोwn(काष्ठा ath10k *ar)
अणु
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif power down\n");

	/* Currently hअगर_घातer_up perक्रमms effectively a reset and hअगर_stop
	 * resets the chip as well so there's no poपूर्णांक in resetting here.
	 */
पूर्ण

अटल पूर्णांक ath10k_pci_hअगर_suspend(काष्ठा ath10k *ar)
अणु
	/* Nothing to करो; the important stuff is in the driver suspend. */
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_suspend(काष्ठा ath10k *ar)
अणु
	/* The grace समयr can still be counting करोwn and ar->ps_awake be true.
	 * It is known that the device may be asleep after resuming regardless
	 * of the SoC घातersave state beक्रमe suspending. Hence make sure the
	 * device is asleep beक्रमe proceeding.
	 */
	ath10k_pci_sleep_sync(ar);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_hअगर_resume(काष्ठा ath10k *ar)
अणु
	/* Nothing to करो; the important stuff is in the driver resume. */
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_resume(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा pci_dev *pdev = ar_pci->pdev;
	u32 val;
	पूर्णांक ret = 0;

	ret = ath10k_pci_क्रमce_wake(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to wake up target: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Suspend/Resume resets the PCI configuration space, so we have to
	 * re-disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep PCI Tx retries
	 * from पूर्णांकerfering with C3 CPU state. pci_restore_state won't help
	 * here since it only restores the first 64 bytes pci config header.
	 */
	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	अगर ((val & 0x0000ff00) != 0)
		pci_ग_लिखो_config_dword(pdev, 0x40, val & 0xffff00ff);

	वापस ret;
पूर्ण

अटल bool ath10k_pci_validate_cal(व्योम *data, माप_प्रकार size)
अणु
	__le16 *cal_words = data;
	u16 checksum = 0;
	माप_प्रकार i;

	अगर (size % 2 != 0)
		वापस false;

	क्रम (i = 0; i < size / 2; i++)
		checksum ^= le16_to_cpu(cal_words[i]);

	वापस checksum == 0xffff;
पूर्ण

अटल व्योम ath10k_pci_enable_eeprom(काष्ठा ath10k *ar)
अणु
	/* Enable SI घड़ी */
	ath10k_pci_soc_ग_लिखो32(ar, CLOCK_CONTROL_OFFSET, 0x0);

	/* Configure GPIOs क्रम I2C operation */
	ath10k_pci_ग_लिखो32(ar,
			   GPIO_BASE_ADDRESS + GPIO_PIN0_OFFSET +
			   4 * QCA9887_1_0_I2C_SDA_GPIO_PIN,
			   SM(QCA9887_1_0_I2C_SDA_PIN_CONFIG,
			      GPIO_PIN0_CONFIG) |
			   SM(1, GPIO_PIN0_PAD_PULL));

	ath10k_pci_ग_लिखो32(ar,
			   GPIO_BASE_ADDRESS + GPIO_PIN0_OFFSET +
			   4 * QCA9887_1_0_SI_CLK_GPIO_PIN,
			   SM(QCA9887_1_0_SI_CLK_PIN_CONFIG, GPIO_PIN0_CONFIG) |
			   SM(1, GPIO_PIN0_PAD_PULL));

	ath10k_pci_ग_लिखो32(ar,
			   GPIO_BASE_ADDRESS +
			   QCA9887_1_0_GPIO_ENABLE_W1TS_LOW_ADDRESS,
			   1u << QCA9887_1_0_SI_CLK_GPIO_PIN);

	/* In Swअगरt ASIC - EEPROM घड़ी will be (110MHz/512) = 214KHz */
	ath10k_pci_ग_लिखो32(ar,
			   SI_BASE_ADDRESS + SI_CONFIG_OFFSET,
			   SM(1, SI_CONFIG_ERR_INT) |
			   SM(1, SI_CONFIG_BIसूची_OD_DATA) |
			   SM(1, SI_CONFIG_I2C) |
			   SM(1, SI_CONFIG_POS_SAMPLE) |
			   SM(1, SI_CONFIG_INACTIVE_DATA) |
			   SM(1, SI_CONFIG_INACTIVE_CLK) |
			   SM(8, SI_CONFIG_DIVIDER));
पूर्ण

अटल पूर्णांक ath10k_pci_पढ़ो_eeprom(काष्ठा ath10k *ar, u16 addr, u8 *out)
अणु
	u32 reg;
	पूर्णांक रुको_limit;

	/* set device select byte and क्रम the पढ़ो operation */
	reg = QCA9887_EEPROM_SELECT_READ |
	      SM(addr, QCA9887_EEPROM_ADDR_LO) |
	      SM(addr >> 8, QCA9887_EEPROM_ADDR_HI);
	ath10k_pci_ग_लिखो32(ar, SI_BASE_ADDRESS + SI_TX_DATA0_OFFSET, reg);

	/* ग_लिखो transmit data, transfer length, and START bit */
	ath10k_pci_ग_लिखो32(ar, SI_BASE_ADDRESS + SI_CS_OFFSET,
			   SM(1, SI_CS_START) | SM(1, SI_CS_RX_CNT) |
			   SM(4, SI_CS_TX_CNT));

	/* रुको max 1 sec */
	रुको_limit = 100000;

	/* रुको क्रम SI_CS_DONE_INT */
	करो अणु
		reg = ath10k_pci_पढ़ो32(ar, SI_BASE_ADDRESS + SI_CS_OFFSET);
		अगर (MS(reg, SI_CS_DONE_INT))
			अवरोध;

		रुको_limit--;
		udelay(10);
	पूर्ण जबतक (रुको_limit > 0);

	अगर (!MS(reg, SI_CS_DONE_INT)) अणु
		ath10k_err(ar, "timeout while reading device EEPROM at %04x\n",
			   addr);
		वापस -ETIMEDOUT;
	पूर्ण

	/* clear SI_CS_DONE_INT */
	ath10k_pci_ग_लिखो32(ar, SI_BASE_ADDRESS + SI_CS_OFFSET, reg);

	अगर (MS(reg, SI_CS_DONE_ERR)) अणु
		ath10k_err(ar, "failed to read device EEPROM at %04x\n", addr);
		वापस -EIO;
	पूर्ण

	/* extract receive data */
	reg = ath10k_pci_पढ़ो32(ar, SI_BASE_ADDRESS + SI_RX_DATA0_OFFSET);
	*out = reg;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_hअगर_fetch_cal_eeprom(काष्ठा ath10k *ar, व्योम **data,
					   माप_प्रकार *data_len)
अणु
	u8 *caldata = शून्य;
	माप_प्रकार calsize, i;
	पूर्णांक ret;

	अगर (!QCA_REV_9887(ar))
		वापस -EOPNOTSUPP;

	calsize = ar->hw_params.cal_data_len;
	caldata = kदो_स्मृति(calsize, GFP_KERNEL);
	अगर (!caldata)
		वापस -ENOMEM;

	ath10k_pci_enable_eeprom(ar);

	क्रम (i = 0; i < calsize; i++) अणु
		ret = ath10k_pci_पढ़ो_eeprom(ar, i, &caldata[i]);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण

	अगर (!ath10k_pci_validate_cal(caldata, calsize))
		जाओ err_मुक्त;

	*data = caldata;
	*data_len = calsize;

	वापस 0;

err_मुक्त:
	kमुक्त(caldata);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ath10k_hअगर_ops ath10k_pci_hअगर_ops = अणु
	.tx_sg			= ath10k_pci_hअगर_tx_sg,
	.diag_पढ़ो		= ath10k_pci_hअगर_diag_पढ़ो,
	.diag_ग_लिखो		= ath10k_pci_diag_ग_लिखो_mem,
	.exchange_bmi_msg	= ath10k_pci_hअगर_exchange_bmi_msg,
	.start			= ath10k_pci_hअगर_start,
	.stop			= ath10k_pci_hअगर_stop,
	.map_service_to_pipe	= ath10k_pci_hअगर_map_service_to_pipe,
	.get_शेष_pipe	= ath10k_pci_hअगर_get_शेष_pipe,
	.send_complete_check	= ath10k_pci_hअगर_send_complete_check,
	.get_मुक्त_queue_number	= ath10k_pci_hअगर_get_मुक्त_queue_number,
	.घातer_up		= ath10k_pci_hअगर_घातer_up,
	.घातer_करोwn		= ath10k_pci_hअगर_घातer_करोwn,
	.पढ़ो32			= ath10k_pci_पढ़ो32,
	.ग_लिखो32		= ath10k_pci_ग_लिखो32,
	.suspend		= ath10k_pci_hअगर_suspend,
	.resume			= ath10k_pci_hअगर_resume,
	.fetch_cal_eeprom	= ath10k_pci_hअगर_fetch_cal_eeprom,
पूर्ण;

/*
 * Top-level पूर्णांकerrupt handler क्रम all PCI पूर्णांकerrupts from a Target.
 * When a block of MSI पूर्णांकerrupts is allocated, this top-level handler
 * is not used; instead, we directly call the correct sub-handler.
 */
अटल irqवापस_t ath10k_pci_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath10k *ar = arg;
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret;

	अगर (ath10k_pci_has_device_gone(ar))
		वापस IRQ_NONE;

	ret = ath10k_pci_क्रमce_wake(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wake device up on irq: %d\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	अगर ((ar_pci->oper_irq_mode == ATH10K_PCI_IRQ_LEGACY) &&
	    !ath10k_pci_irq_pending(ar))
		वापस IRQ_NONE;

	ath10k_pci_disable_and_clear_legacy_irq(ar);
	ath10k_pci_irq_msi_fw_mask(ar);
	napi_schedule(&ar->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ath10k_pci_napi_poll(काष्ठा napi_काष्ठा *ctx, पूर्णांक budget)
अणु
	काष्ठा ath10k *ar = container_of(ctx, काष्ठा ath10k, napi);
	पूर्णांक करोne = 0;

	अगर (ath10k_pci_has_fw_crashed(ar)) अणु
		ath10k_pci_fw_crashed_clear(ar);
		ath10k_pci_fw_crashed_dump(ar);
		napi_complete(ctx);
		वापस करोne;
	पूर्ण

	ath10k_ce_per_engine_service_any(ar);

	करोne = ath10k_htt_txrx_compl_task(ar, budget);

	अगर (करोne < budget) अणु
		napi_complete_करोne(ctx, करोne);
		/* In हाल of MSI, it is possible that पूर्णांकerrupts are received
		 * जबतक NAPI poll is inprogress. So pending पूर्णांकerrupts that are
		 * received after processing all copy engine pipes by NAPI poll
		 * will not be handled again. This is causing failure to
		 * complete boot sequence in x86 platक्रमm. So beक्रमe enabling
		 * पूर्णांकerrupts safer to check क्रम pending पूर्णांकerrupts क्रम
		 * immediate servicing.
		 */
		अगर (ath10k_ce_पूर्णांकerrupt_summary(ar)) अणु
			napi_reschedule(ctx);
			जाओ out;
		पूर्ण
		ath10k_pci_enable_legacy_irq(ar);
		ath10k_pci_irq_msi_fw_unmask(ar);
	पूर्ण

out:
	वापस करोne;
पूर्ण

अटल पूर्णांक ath10k_pci_request_irq_msi(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret;

	ret = request_irq(ar_pci->pdev->irq,
			  ath10k_pci_पूर्णांकerrupt_handler,
			  IRQF_SHARED, "ath10k_pci", ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request MSI irq %d: %d\n",
			    ar_pci->pdev->irq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_request_irq_legacy(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret;

	ret = request_irq(ar_pci->pdev->irq,
			  ath10k_pci_पूर्णांकerrupt_handler,
			  IRQF_SHARED, "ath10k_pci", ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request legacy irq %d: %d\n",
			    ar_pci->pdev->irq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_request_irq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	चयन (ar_pci->oper_irq_mode) अणु
	हाल ATH10K_PCI_IRQ_LEGACY:
		वापस ath10k_pci_request_irq_legacy(ar);
	हाल ATH10K_PCI_IRQ_MSI:
		वापस ath10k_pci_request_irq_msi(ar);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ath10k_pci_मुक्त_irq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	मुक्त_irq(ar_pci->pdev->irq, ar);
पूर्ण

व्योम ath10k_pci_init_napi(काष्ठा ath10k *ar)
अणु
	netअगर_napi_add(&ar->napi_dev, &ar->napi, ath10k_pci_napi_poll,
		       ATH10K_NAPI_BUDGET);
पूर्ण

अटल पूर्णांक ath10k_pci_init_irq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	पूर्णांक ret;

	ath10k_pci_init_napi(ar);

	अगर (ath10k_pci_irq_mode != ATH10K_PCI_IRQ_AUTO)
		ath10k_info(ar, "limiting irq mode to: %d\n",
			    ath10k_pci_irq_mode);

	/* Try MSI */
	अगर (ath10k_pci_irq_mode != ATH10K_PCI_IRQ_LEGACY) अणु
		ar_pci->oper_irq_mode = ATH10K_PCI_IRQ_MSI;
		ret = pci_enable_msi(ar_pci->pdev);
		अगर (ret == 0)
			वापस 0;

		/* MHI failed, try legacy irq next */
	पूर्ण

	/* Try legacy irq
	 *
	 * A potential race occurs here: The CORE_BASE ग_लिखो
	 * depends on target correctly decoding AXI address but
	 * host won't know when target ग_लिखोs BAR to CORE_CTRL.
	 * This ग_लिखो might get lost अगर target has NOT written BAR.
	 * For now, fix the race by repeating the ग_लिखो in below
	 * synchronization checking.
	 */
	ar_pci->oper_irq_mode = ATH10K_PCI_IRQ_LEGACY;

	ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS + PCIE_INTR_ENABLE_ADDRESS,
			   PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL);

	वापस 0;
पूर्ण

अटल व्योम ath10k_pci_deinit_irq_legacy(काष्ठा ath10k *ar)
अणु
	ath10k_pci_ग_लिखो32(ar, SOC_CORE_BASE_ADDRESS + PCIE_INTR_ENABLE_ADDRESS,
			   0);
पूर्ण

अटल पूर्णांक ath10k_pci_deinit_irq(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	चयन (ar_pci->oper_irq_mode) अणु
	हाल ATH10K_PCI_IRQ_LEGACY:
		ath10k_pci_deinit_irq_legacy(ar);
		अवरोध;
	शेष:
		pci_disable_msi(ar_pci->pdev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_pci_रुको_क्रम_target_init(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	अचिन्हित दीर्घ समयout;
	u32 val;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot waiting target to initialise\n");

	समयout = jअगरfies + msecs_to_jअगरfies(ATH10K_PCI_TARGET_WAIT);

	करो अणु
		val = ath10k_pci_पढ़ो32(ar, FW_INDICATOR_ADDRESS);

		ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot target indicator %x\n",
			   val);

		/* target should never वापस this */
		अगर (val == 0xffffffff)
			जारी;

		/* the device has crashed so करोn't bother trying anymore */
		अगर (val & FW_IND_EVENT_PENDING)
			अवरोध;

		अगर (val & FW_IND_INITIALIZED)
			अवरोध;

		अगर (ar_pci->oper_irq_mode == ATH10K_PCI_IRQ_LEGACY)
			/* Fix potential race by repeating CORE_BASE ग_लिखोs */
			ath10k_pci_enable_legacy_irq(ar);

		mdelay(10);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	ath10k_pci_disable_and_clear_legacy_irq(ar);
	ath10k_pci_irq_msi_fw_mask(ar);

	अगर (val == 0xffffffff) अणु
		ath10k_err(ar, "failed to read device register, device is gone\n");
		वापस -EIO;
	पूर्ण

	अगर (val & FW_IND_EVENT_PENDING) अणु
		ath10k_warn(ar, "device has crashed during init\n");
		वापस -ECOMM;
	पूर्ण

	अगर (!(val & FW_IND_INITIALIZED)) अणु
		ath10k_err(ar, "failed to receive initialized event from target: %08x\n",
			   val);
		वापस -ETIMEDOUT;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot target initialised\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_cold_reset(काष्ठा ath10k *ar)
अणु
	u32 val;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot cold reset\n");

	spin_lock_bh(&ar->data_lock);

	ar->stats.fw_cold_reset_counter++;

	spin_unlock_bh(&ar->data_lock);

	/* Put Target, including PCIe, पूर्णांकo RESET. */
	val = ath10k_pci_reg_पढ़ो32(ar, SOC_GLOBAL_RESET_ADDRESS);
	val |= 1;
	ath10k_pci_reg_ग_लिखो32(ar, SOC_GLOBAL_RESET_ADDRESS, val);

	/* After writing पूर्णांकo SOC_GLOBAL_RESET to put device पूर्णांकo
	 * reset and pulling out of reset pcie may not be stable
	 * क्रम any immediate pcie रेजिस्टर access and cause bus error,
	 * add delay beक्रमe any pcie access request to fix this issue.
	 */
	msleep(20);

	/* Pull Target, including PCIe, out of RESET. */
	val &= ~1;
	ath10k_pci_reg_ग_लिखो32(ar, SOC_GLOBAL_RESET_ADDRESS, val);

	msleep(20);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot cold reset complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_pci_claim(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा pci_dev *pdev = ar_pci->pdev;
	पूर्णांक ret;

	pci_set_drvdata(pdev, ar);

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		ath10k_err(ar, "failed to enable pci device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pci_request_region(pdev, BAR_NUM, "ath");
	अगर (ret) अणु
		ath10k_err(ar, "failed to request region BAR%d: %d\n", BAR_NUM,
			   ret);
		जाओ err_device;
	पूर्ण

	/* Target expects 32 bit DMA. Enक्रमce it. */
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		ath10k_err(ar, "failed to set dma mask to 32-bit: %d\n", ret);
		जाओ err_region;
	पूर्ण

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		ath10k_err(ar, "failed to set consistent dma mask to 32-bit: %d\n",
			   ret);
		जाओ err_region;
	पूर्ण

	pci_set_master(pdev);

	/* Arrange क्रम access to Target SoC रेजिस्टरs. */
	ar_pci->mem_len = pci_resource_len(pdev, BAR_NUM);
	ar_pci->mem = pci_iomap(pdev, BAR_NUM, 0);
	अगर (!ar_pci->mem) अणु
		ath10k_err(ar, "failed to iomap BAR%d\n", BAR_NUM);
		ret = -EIO;
		जाओ err_master;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot pci_mem 0x%pK\n", ar_pci->mem);
	वापस 0;

err_master:
	pci_clear_master(pdev);

err_region:
	pci_release_region(pdev, BAR_NUM);

err_device:
	pci_disable_device(pdev);

	वापस ret;
पूर्ण

अटल व्योम ath10k_pci_release(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा pci_dev *pdev = ar_pci->pdev;

	pci_iounmap(pdev, ar_pci->mem);
	pci_release_region(pdev, BAR_NUM);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल bool ath10k_pci_chip_is_supported(u32 dev_id, u32 chip_id)
अणु
	स्थिर काष्ठा ath10k_pci_supp_chip *supp_chip;
	पूर्णांक i;
	u32 rev_id = MS(chip_id, SOC_CHIP_ID_REV);

	क्रम (i = 0; i < ARRAY_SIZE(ath10k_pci_supp_chips); i++) अणु
		supp_chip = &ath10k_pci_supp_chips[i];

		अगर (supp_chip->dev_id == dev_id &&
		    supp_chip->rev_id == rev_id)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक ath10k_pci_setup_resource(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक ret;

	spin_lock_init(&ce->ce_lock);
	spin_lock_init(&ar_pci->ps_lock);
	mutex_init(&ar_pci->ce_diag_mutex);

	INIT_WORK(&ar_pci->dump_work, ath10k_pci_fw_dump_work);

	समयr_setup(&ar_pci->rx_post_retry, ath10k_pci_rx_replenish_retry, 0);

	ar_pci->attr = kmemdup(pci_host_ce_config_wlan,
			       माप(pci_host_ce_config_wlan),
			       GFP_KERNEL);
	अगर (!ar_pci->attr)
		वापस -ENOMEM;

	ar_pci->pipe_config = kmemdup(pci_target_ce_config_wlan,
				      माप(pci_target_ce_config_wlan),
				      GFP_KERNEL);
	अगर (!ar_pci->pipe_config) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_attr;
	पूर्ण

	ar_pci->serv_to_pipe = kmemdup(pci_target_service_to_ce_map_wlan,
				       माप(pci_target_service_to_ce_map_wlan),
				       GFP_KERNEL);
	अगर (!ar_pci->serv_to_pipe) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_pipe_config;
	पूर्ण

	अगर (QCA_REV_6174(ar) || QCA_REV_9377(ar))
		ath10k_pci_override_ce_config(ar);

	ret = ath10k_pci_alloc_pipes(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to allocate copy engine pipes: %d\n",
			   ret);
		जाओ err_मुक्त_serv_to_pipe;
	पूर्ण

	वापस 0;

err_मुक्त_serv_to_pipe:
	kमुक्त(ar_pci->serv_to_pipe);
err_मुक्त_pipe_config:
	kमुक्त(ar_pci->pipe_config);
err_मुक्त_attr:
	kमुक्त(ar_pci->attr);
	वापस ret;
पूर्ण

व्योम ath10k_pci_release_resource(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_pci *ar_pci = ath10k_pci_priv(ar);

	ath10k_pci_rx_retry_sync(ar);
	netअगर_napi_del(&ar->napi);
	ath10k_pci_ce_deinit(ar);
	ath10k_pci_मुक्त_pipes(ar);
	kमुक्त(ar_pci->attr);
	kमुक्त(ar_pci->pipe_config);
	kमुक्त(ar_pci->serv_to_pipe);
पूर्ण

अटल स्थिर काष्ठा ath10k_bus_ops ath10k_pci_bus_ops = अणु
	.पढ़ो32		= ath10k_bus_pci_पढ़ो32,
	.ग_लिखो32	= ath10k_bus_pci_ग_लिखो32,
	.get_num_banks	= ath10k_pci_get_num_banks,
पूर्ण;

अटल पूर्णांक ath10k_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *pci_dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा ath10k *ar;
	काष्ठा ath10k_pci *ar_pci;
	क्रमागत ath10k_hw_rev hw_rev;
	काष्ठा ath10k_bus_params bus_params = अणुपूर्ण;
	bool pci_ps, is_qca988x = false;
	पूर्णांक (*pci_soft_reset)(काष्ठा ath10k *ar);
	पूर्णांक (*pci_hard_reset)(काष्ठा ath10k *ar);
	u32 (*targ_cpu_to_ce_addr)(काष्ठा ath10k *ar, u32 addr);

	चयन (pci_dev->device) अणु
	हाल QCA988X_2_0_DEVICE_ID_UBNT:
	हाल QCA988X_2_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA988X;
		pci_ps = false;
		is_qca988x = true;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca988x_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca988x_targ_cpu_to_ce_addr;
		अवरोध;
	हाल QCA9887_1_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9887;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca988x_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca988x_targ_cpu_to_ce_addr;
		अवरोध;
	हाल QCA6164_2_1_DEVICE_ID:
	हाल QCA6174_2_1_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA6174;
		pci_ps = true;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca6174_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca6174_targ_cpu_to_ce_addr;
		अवरोध;
	हाल QCA99X0_2_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA99X0;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_qca99x0_soft_chip_reset;
		pci_hard_reset = ath10k_pci_qca99x0_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca99x0_targ_cpu_to_ce_addr;
		अवरोध;
	हाल QCA9984_1_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9984;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_qca99x0_soft_chip_reset;
		pci_hard_reset = ath10k_pci_qca99x0_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca99x0_targ_cpu_to_ce_addr;
		अवरोध;
	हाल QCA9888_2_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9888;
		pci_ps = false;
		pci_soft_reset = ath10k_pci_qca99x0_soft_chip_reset;
		pci_hard_reset = ath10k_pci_qca99x0_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca99x0_targ_cpu_to_ce_addr;
		अवरोध;
	हाल QCA9377_1_0_DEVICE_ID:
		hw_rev = ATH10K_HW_QCA9377;
		pci_ps = true;
		pci_soft_reset = ath10k_pci_warm_reset;
		pci_hard_reset = ath10k_pci_qca6174_chip_reset;
		targ_cpu_to_ce_addr = ath10k_pci_qca6174_targ_cpu_to_ce_addr;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -ENOTSUPP;
	पूर्ण

	ar = ath10k_core_create(माप(*ar_pci), &pdev->dev, ATH10K_BUS_PCI,
				hw_rev, &ath10k_pci_hअगर_ops);
	अगर (!ar) अणु
		dev_err(&pdev->dev, "failed to allocate core\n");
		वापस -ENOMEM;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "pci probe %04x:%04x %04x:%04x\n",
		   pdev->venकरोr, pdev->device,
		   pdev->subप्रणाली_venकरोr, pdev->subप्रणाली_device);

	ar_pci = ath10k_pci_priv(ar);
	ar_pci->pdev = pdev;
	ar_pci->dev = &pdev->dev;
	ar_pci->ar = ar;
	ar->dev_id = pci_dev->device;
	ar_pci->pci_ps = pci_ps;
	ar_pci->ce.bus_ops = &ath10k_pci_bus_ops;
	ar_pci->pci_soft_reset = pci_soft_reset;
	ar_pci->pci_hard_reset = pci_hard_reset;
	ar_pci->targ_cpu_to_ce_addr = targ_cpu_to_ce_addr;
	ar->ce_priv = &ar_pci->ce;

	ar->id.venकरोr = pdev->venकरोr;
	ar->id.device = pdev->device;
	ar->id.subप्रणाली_venकरोr = pdev->subप्रणाली_venकरोr;
	ar->id.subप्रणाली_device = pdev->subप्रणाली_device;

	समयr_setup(&ar_pci->ps_समयr, ath10k_pci_ps_समयr, 0);

	ret = ath10k_pci_setup_resource(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to setup resource: %d\n", ret);
		जाओ err_core_destroy;
	पूर्ण

	ret = ath10k_pci_claim(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to claim device: %d\n", ret);
		जाओ err_मुक्त_pipes;
	पूर्ण

	ret = ath10k_pci_क्रमce_wake(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wake up device : %d\n", ret);
		जाओ err_sleep;
	पूर्ण

	ath10k_pci_ce_deinit(ar);
	ath10k_pci_irq_disable(ar);

	ret = ath10k_pci_init_irq(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to init irqs: %d\n", ret);
		जाओ err_sleep;
	पूर्ण

	ath10k_info(ar, "pci irq %s oper_irq_mode %d irq_mode %d reset_mode %d\n",
		    ath10k_pci_get_irq_method(ar), ar_pci->oper_irq_mode,
		    ath10k_pci_irq_mode, ath10k_pci_reset_mode);

	ret = ath10k_pci_request_irq(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request irqs: %d\n", ret);
		जाओ err_deinit_irq;
	पूर्ण

	bus_params.dev_type = ATH10K_DEV_TYPE_LL;
	bus_params.link_can_suspend = true;
	/* Read CHIP_ID beक्रमe reset to catch QCA9880-AR1A v1 devices that
	 * fall off the bus during chip_reset. These chips have the same pci
	 * device id as the QCA9880 BR4A or 2R4E. So that's why the check.
	 */
	अगर (is_qca988x) अणु
		bus_params.chip_id =
			ath10k_pci_soc_पढ़ो32(ar, SOC_CHIP_ID_ADDRESS);
		अगर (bus_params.chip_id != 0xffffffff) अणु
			अगर (!ath10k_pci_chip_is_supported(pdev->device,
							  bus_params.chip_id))
				जाओ err_unsupported;
		पूर्ण
	पूर्ण

	ret = ath10k_pci_chip_reset(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to reset chip: %d\n", ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	bus_params.chip_id = ath10k_pci_soc_पढ़ो32(ar, SOC_CHIP_ID_ADDRESS);
	अगर (bus_params.chip_id == 0xffffffff)
		जाओ err_unsupported;

	अगर (!ath10k_pci_chip_is_supported(pdev->device, bus_params.chip_id))
		जाओ err_मुक्त_irq;

	ret = ath10k_core_रेजिस्टर(ar, &bus_params);
	अगर (ret) अणु
		ath10k_err(ar, "failed to register driver core: %d\n", ret);
		जाओ err_मुक्त_irq;
	पूर्ण

	वापस 0;

err_unsupported:
	ath10k_err(ar, "device %04x with chip_id %08x isn't supported\n",
		   pdev->device, bus_params.chip_id);

err_मुक्त_irq:
	ath10k_pci_मुक्त_irq(ar);

err_deinit_irq:
	ath10k_pci_release_resource(ar);

err_sleep:
	ath10k_pci_sleep_sync(ar);
	ath10k_pci_release(ar);

err_मुक्त_pipes:
	ath10k_pci_मुक्त_pipes(ar);

err_core_destroy:
	ath10k_core_destroy(ar);

	वापस ret;
पूर्ण

अटल व्योम ath10k_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ath10k *ar = pci_get_drvdata(pdev);

	ath10k_dbg(ar, ATH10K_DBG_PCI, "pci remove\n");

	अगर (!ar)
		वापस;

	ath10k_core_unरेजिस्टर(ar);
	ath10k_pci_मुक्त_irq(ar);
	ath10k_pci_deinit_irq(ar);
	ath10k_pci_release_resource(ar);
	ath10k_pci_sleep_sync(ar);
	ath10k_pci_release(ar);
	ath10k_core_destroy(ar);
पूर्ण

MODULE_DEVICE_TABLE(pci, ath10k_pci_id_table);

अटल __maybe_unused पूर्णांक ath10k_pci_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ath10k *ar = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = ath10k_pci_suspend(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to suspend hif: %d\n", ret);

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक ath10k_pci_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा ath10k *ar = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = ath10k_pci_resume(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to resume hif: %d\n", ret);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ath10k_pci_pm_ops,
			 ath10k_pci_pm_suspend,
			 ath10k_pci_pm_resume);

अटल काष्ठा pci_driver ath10k_pci_driver = अणु
	.name = "ath10k_pci",
	.id_table = ath10k_pci_id_table,
	.probe = ath10k_pci_probe,
	.हटाओ = ath10k_pci_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver.pm = &ath10k_pci_pm_ops,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init ath10k_pci_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&ath10k_pci_driver);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "failed to register ath10k pci driver: %d\n",
		       ret);

	ret = ath10k_ahb_init();
	अगर (ret)
		prपूर्णांकk(KERN_ERR "ahb init failed: %d\n", ret);

	वापस ret;
पूर्ण
module_init(ath10k_pci_init);

अटल व्योम __निकास ath10k_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ath10k_pci_driver);
	ath10k_ahb_निकास();
पूर्ण

module_निकास(ath10k_pci_निकास);

MODULE_AUTHOR("Qualcomm Atheros");
MODULE_DESCRIPTION("Driver support for Qualcomm Atheros 802.11ac WLAN PCIe/AHB devices");
MODULE_LICENSE("Dual BSD/GPL");

/* QCA988x 2.0 firmware files */
MODULE_FIRMWARE(QCA988X_HW_2_0_FW_सूची "/" ATH10K_FW_API2_खाता);
MODULE_FIRMWARE(QCA988X_HW_2_0_FW_सूची "/" ATH10K_FW_API3_खाता);
MODULE_FIRMWARE(QCA988X_HW_2_0_FW_सूची "/" ATH10K_FW_API4_खाता);
MODULE_FIRMWARE(QCA988X_HW_2_0_FW_सूची "/" ATH10K_FW_API5_खाता);
MODULE_FIRMWARE(QCA988X_HW_2_0_FW_सूची "/" QCA988X_HW_2_0_BOARD_DATA_खाता);
MODULE_FIRMWARE(QCA988X_HW_2_0_FW_सूची "/" ATH10K_BOARD_API2_खाता);

/* QCA9887 1.0 firmware files */
MODULE_FIRMWARE(QCA9887_HW_1_0_FW_सूची "/" ATH10K_FW_API5_खाता);
MODULE_FIRMWARE(QCA9887_HW_1_0_FW_सूची "/" QCA9887_HW_1_0_BOARD_DATA_खाता);
MODULE_FIRMWARE(QCA9887_HW_1_0_FW_सूची "/" ATH10K_BOARD_API2_खाता);

/* QCA6174 2.1 firmware files */
MODULE_FIRMWARE(QCA6174_HW_2_1_FW_सूची "/" ATH10K_FW_API4_खाता);
MODULE_FIRMWARE(QCA6174_HW_2_1_FW_सूची "/" ATH10K_FW_API5_खाता);
MODULE_FIRMWARE(QCA6174_HW_2_1_FW_सूची "/" QCA6174_HW_2_1_BOARD_DATA_खाता);
MODULE_FIRMWARE(QCA6174_HW_2_1_FW_सूची "/" ATH10K_BOARD_API2_खाता);

/* QCA6174 3.1 firmware files */
MODULE_FIRMWARE(QCA6174_HW_3_0_FW_सूची "/" ATH10K_FW_API4_खाता);
MODULE_FIRMWARE(QCA6174_HW_3_0_FW_सूची "/" ATH10K_FW_API5_खाता);
MODULE_FIRMWARE(QCA6174_HW_3_0_FW_सूची "/" ATH10K_FW_API6_खाता);
MODULE_FIRMWARE(QCA6174_HW_3_0_FW_सूची "/" QCA6174_HW_3_0_BOARD_DATA_खाता);
MODULE_FIRMWARE(QCA6174_HW_3_0_FW_सूची "/" ATH10K_BOARD_API2_खाता);

/* QCA9377 1.0 firmware files */
MODULE_FIRMWARE(QCA9377_HW_1_0_FW_सूची "/" ATH10K_FW_API6_खाता);
MODULE_FIRMWARE(QCA9377_HW_1_0_FW_सूची "/" ATH10K_FW_API5_खाता);
MODULE_FIRMWARE(QCA9377_HW_1_0_FW_सूची "/" QCA9377_HW_1_0_BOARD_DATA_खाता);
